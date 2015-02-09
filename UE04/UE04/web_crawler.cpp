#include <iostream>
#include <sstream>
#include <set>
#include <boost/asio.hpp>
#include <boost/regex.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/algorithm/string/predicate.hpp>

// linking:  -lboost_system (linux), -lboost_system-mt (macports)


class web_crawler {
public:
    web_crawler(const std::string& rootUrl) : m_rootUrl(rootUrl) {}

    void crawl(int depth);
    void write_xml(const std::string& filename);
private:
    static const boost::regex hrefPattern;
    static const boost::regex httpPattern;

    std::string m_rootUrl;
    std::set<std::string> m_visitedUrls;
    boost::property_tree::ptree m_tree;

    std::string get_url(const std::string& line);
    boost::property_tree::ptree crawl(const std::string& m_rootUrl, int depth);
};

const boost::regex web_crawler::hrefPattern("<a\\s+(.*?\\s)?href=[\"\']http://.*?[\"\']");
const boost::regex web_crawler::httpPattern("[\"\']http://.*?[\"\']");

std::string web_crawler::get_url(const std::string& line) {
    boost::smatch hrefMatch;
    bool containsHrefPattern = boost::regex_search(line, hrefMatch, hrefPattern);
    if (!containsHrefPattern) {
        return "";
    }
    boost::smatch httpMatch;
    boost::regex_search(hrefMatch[0].first, hrefMatch[0].second, httpMatch, httpPattern);
    std::string url(httpMatch[0].first + 1, httpMatch[0].second - 1);
    return m_visitedUrls.find(url) == m_visitedUrls.end() ? url : "";
}

boost::property_tree::ptree web_crawler::crawl(const std::string& rootUrl, int depth) {
    m_visitedUrls.insert(rootUrl);
    boost::property_tree::ptree tree;
    tree.put("url", rootUrl);

    if (depth > 0) {
        std::string host = boost::starts_with(rootUrl, "http://") ? rootUrl.substr(7, rootUrl.length()) : rootUrl;
        boost::asio::ip::tcp::iostream tcp_io(host, "http");
        tcp_io << "GET /" << /*query << */ " HTTP/1.1\r\n";
        tcp_io << "Host: " << host;
        tcp_io << "\r\n\r\n" << std::flush;

        for (std::string line; std::getline(tcp_io, line); ) {
            std::string url = get_url(line);
            if (url != "") {
                boost::property_tree::ptree child = crawl(url, depth-1);
                tree.add_child("links.page", child);

                std::cout << ".";
                std::cout.flush();
            }
        }
    }
    return tree;
}

void web_crawler::crawl(int depth) {
    std::cout << "Start crawling at " << m_rootUrl << " with a depth of " << depth << std::endl;

    boost::property_tree::ptree child = crawl(m_rootUrl, depth);
    m_tree.add_child("page", child);

    std::cout << std::endl;
    std::cout << "Found " << m_visitedUrls.size() << " URLs." << std::endl;
}

void web_crawler::write_xml(const std::string& filename) {
    boost::property_tree::xml_writer_settings<std::string> settings(' ', 4);
    boost::property_tree::write_xml(filename, m_tree, std::locale(), settings);
}


int main(int arg_num, char* args[]) {
    if (arg_num != 3) {
        std::cerr << "usage: web_crawler <url> <depth>" << std::endl;
        return 1;
    }
    std::string rootUrl = args[1];
    int depth = atoi(args[2]);

//    std::string rootUrl = "http://www.boost.org";
//    int depth = 3;

    web_crawler crawler(rootUrl);
    crawler.crawl(depth);
    crawler.write_xml("found_urls.xml");
}
