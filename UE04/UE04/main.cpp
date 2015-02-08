//#include <iostream>
//#include <string>
//#include <set>
//#include <boost/regex.hpp>
//#include <boost/property_tree/ptree.hpp>
//#include <boost/property_tree/xml_parser.hpp>

//using namespace std;

//void regexDemo() {
//    std::string s = "<a href=\"http://www.gotw.ca/\" class=\"external\">";
//    static const boost::regex pattern1("<a\\s+href=[\"\']https?://.*?[\"\'].*?");
//    static const boost::regex pattern2("[\"\']https?://.*?[\"\']");
//    //    static const boost::regex pattern("<a\\s+href=[\"\']([\\-:\\w\\d\\.\\/]+)[\"\'].*>");

//    cout << boost::regex_match(s, pattern1) << endl;
//    boost::smatch result1;
//    if (boost::regex_search(s, result1, pattern1)) {
//        string submatch1(result1[0].first, result1[0].second);
//        boost::smatch result2;
//        boost::regex_search(result1[0].first, result1[0].second, result2, pattern2);
////        boost::regex_search(submatch1, result2, pattern2);
//        string submatch2(result2[0].first, result2[0].second);
//        cout << submatch2 << endl;
//        cout << submatch2.substr(1, submatch2.length()-2) << endl;
//    }
//}

//void treeDemo() {
//    boost::property_tree::ptree tree;
//    tree.put("father", "dad");
//    tree.put("father.child", "kid");
//    auto res = tree.get<std::string>("father.child", "default");
//    tree.put_value<std::string>("root");
//    auto res2 = tree.get_value<std::string>();
//    auto res3 = tree.get_child("").get_value<std::string>();
//    tree.put("father.another_child", "kiddo");
//    auto dad = tree.get_child("father");
////    dad.put("another_child", "kiddo");
//    auto res4 = dad.get_child("child").get_value<std::string>();
//    auto res5 = dad.get_child("another_child").get_value<std::string>();
//    auto res6 = dad.get<std::string>("another_child", "not found");
//    auto res7 = tree.get<std::string>("father.another_child", "not found");

//    cout << res << endl;
//    cout << res2 << endl;
//    cout << res3 << endl;
//    cout << res4 << endl;
//    cout << res5 << endl;
//    cout << res6 << endl;
//    cout << res7 << endl;

//    std::set<std::string> children;
//    children.insert("Alice");
//    children.insert("Bob");
//    children.insert("Carla");

//    for (const auto& item : children) {
//        tree.add("father.children.child", item);
//    }

////    cout << tree.get("father.children", "nonono") << endl;
////    cout << tree.get_child("father.children").get_value<std::string>() << endl;

//    for (const auto& child : tree.get_child("father.children")) {
//        cout << child.second.data() << endl;
//    }

//    cout << endl;

//    boost::property_tree::ptree tree2;
//    tree2.add_child("root2", tree);

//    for (const auto& child : tree2.get_child("root2.father.children")) {
//        cout << child.second.data() << endl;
//    }

//    cout << endl;
//    cout << "Done." << endl;
//}

//void treeDemo2() {
//    boost::property_tree::ptree tree;
//    tree.put("url", "http://www.abc.de");

//    boost::property_tree::ptree sub_tree_a;
//    sub_tree_a.put("url", "http://www.aaa.de");
//    sub_tree_a.put("url", "http://www.aab.de");

//    boost::property_tree::ptree sub_tree_b;
//    sub_tree_b.put("url", "http://www.bbb.de");
//    sub_tree_b.put("url", "http://www.bbc.de");

//    tree.add_child("links.page", sub_tree_a);
//    tree.add_child("links.page", sub_tree_b);
////    tree.add("page.links.page", "b");

//    boost::property_tree::ptree root;
//    root.add_child("page", tree);

//    boost::property_tree::write_xml("found_urls.xml", root);
//    cout << "Done." << endl;
//}

//int main()
//{
//    regexDemo();
////    treeDemo();
////    treeDemo2();
//    return 0;
//}
