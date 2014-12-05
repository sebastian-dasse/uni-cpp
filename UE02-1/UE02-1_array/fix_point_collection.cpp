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
    delete[] m_coll;
}

/**
 * Pushes an element to the end of the collection.
 */
void fix_point_collection::push_back(fix_point val) {
    m_size++;
    fix_point *old = m_coll;
    m_coll = new fix_point[m_size];
    for (int i = 0; i < m_size-1; i++) {
        m_coll[i] = old[i];
    }
    m_coll[m_size - 1] = val;
    delete[] old;
}

/**
 * Removes the element from the end of the collection and returns it.
 */
fix_point fix_point_collection::pop_back() {
    if (m_size == 0) {
        throw "Underflow: cannot pop baack from an empty collection";
    }
    m_size--;
    fix_point *old = m_coll;
    m_coll = new fix_point[m_size];
    for (int i = 0; i < m_size; i++) {
        m_coll[i] = old[i];
    }
    fix_point fp = old[m_size];
    delete[] old;
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
    return m_coll[index];
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
    int left = index.floor();
    int right = left + 1;
    fix_point f = index.frac();
    return (fix_point(1.f) - f) * (*this)[left] + f * (*this)[right];
}

/**
 * Returns the element at the specified index for read and write access.
 */
fix_point& fix_point_collection::operator[](int index) {
    if (index < 0 || m_size <= index) {
        throw "Index out of bounds";
    }
    return m_coll[index];
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
    int size = int(coll.size());
    for (int i = 0; i < size; i++) {
        if (coll[i] == value) {
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
    int size = int(coll.size());
    for (int i = 0; i < size; i++) {
        sum += coll[i];
    }
    return sum;
}
