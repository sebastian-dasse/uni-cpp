#include "fix_point_collection.h"


/**
 * Constructs an empty collection.
 */
fix_point_collection::fix_point_collection()
    : m_coll(nullptr), m_size(0) {}

/**
 * Destructs the collection and releases all its resources.
 */
fix_point_collection::~fix_point_collection() {
    node *n = m_coll;
    while(n != nullptr) {
        node *old = n;
        n = n->next;
        delete old;
    }
}

/**
 * Pushes an element to the end of the collection.
 */
void fix_point_collection::push_back(fix_point val) {
    node *newNode = new node;
    newNode->val = val;
    newNode->next = m_coll;
    m_coll = newNode;
    m_size++;
}

/**
 * Removes the element from the end of the collection and returns it.
 */
fix_point fix_point_collection::pop_back() {
    if (m_size == 0) {
        throw "Underflow: cannot pop back from an empty collection";
    }
    fix_point fp = m_coll->val;
    node *oldNode = m_coll;
    m_coll = m_coll->next;
    delete oldNode;
    m_size--;
    return fp;
}

/**
 * Returns the element at the specified index for read access only.
 * This method is available for a const fix_point_collection.
 */
const fix_point& fix_point_collection::operator[](int index) const {

    // QUESTION how to delegate duplicate code of overloaded const
    //          function to a non-public helper function?
    // TODO -> const_cast<*>(this)operator[]
    //          oder so ähnlich

    if (index < 0 || m_size <= index) {
        throw "Index out of bounds";
    }
    node *n = m_coll;
    index++;
    for ( ; index < m_size; index++) {
        n = n->next;
    }
    return n->val;
}

node* fix_point_collection::getPtrFor(int index) const {
    if (index < 0 || m_size <= index) {
        throw "Index out of bounds";
    }
    node *n = m_coll;
    index++;
    for ( ; index < m_size; index++) {
        n = n->next;
    }
    return n;
}

/**
 * Returns the value resulting from linear interpolation between
 * the two elements at the indices closest to the specified
 * fix_point index.
 */
fix_point fix_point_collection::operator[](fix_point index) const {
    if (index < fix_point(0.f) || fix_point(m_size-1.f) < index) {
        throw "Index out of bounds";
    }
    int leftIndex = index.floor();
    fix_point factor = index.frac();
    node* right = getPtrFor(leftIndex + 1);
    node* left = right->next;
    return (fix_point(1.f) - factor) * left->val + factor * right->val;

    //-- the inefficient way to do it:
//    return (fix_point(1.f) - f) * (*this)[left] + f * (*this)[right];
}

/**
 * Returns the element at the specified index for read and write access.
 */
fix_point& fix_point_collection::operator[](int index) {
    if (index < 0 || m_size <= index) {
        throw "Index out of bounds";
    }
    node *n = m_coll;
    index++;
    for ( ; index < m_size; index++) {
        n = n->next;
    }
    return n->val;
}

/**
 * Returns the size of the collection.
 */
size_t fix_point_collection::size() const {
    return m_size;
}

/**
 * Returns the number of occurrences of the specified value in the
 * collection.
 */
size_t count_value(fix_point_collection &coll, fix_point value) {
    int count = 0;
    for (node *n = coll.m_coll; n != nullptr; n = n->next) {
        if (n->val == value) {
            count++;
        }
    }
    return count;
}

/**
 * Returns the sum of all elements of the collection.
 */
fix_point sum(fix_point_collection &coll) {
    fix_point sum = 0.f;
    for (node *n = coll.m_coll; n != nullptr; n = n->next) {
        sum += n->val;
    }
    return sum;
}
