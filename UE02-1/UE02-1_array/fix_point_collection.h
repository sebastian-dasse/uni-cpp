#ifndef FIX_POINT_COLLECTION_H
#define FIX_POINT_COLLECTION_H

#include <cstdint>
#include "fix_point.h"

using std::size_t;

class fix_point_collection {
public:
    /**
     * Constructs an empty collection.
     */
    fix_point_collection();

    /**
     * Destructs the collection and releases all its resources.
     */
    ~fix_point_collection();

    /**
     * Pushes an element to the end of the collection.
     */
    void push_back(fix_point val);

    /**
     * Removes the element from the end of the collection and returns it.
     */
    fix_point pop_back();

    /**
     * Returns the element at the specified index for read access only.
     * This method is available for a const fix_point_collection.
     */
    const fix_point& operator[](int index) const;

    /**
     * Returns the value resulting from linear interpolation between
     * the two elements at the indices closest to the specified
     * fix_point index.
     */
    fix_point operator[](fix_point index) const;

    /**
     * Returns the element at the specified index for read and write access.
     */
    fix_point& operator[](int index);

    /**
     * Returns the size of the collection.
     */
    size_t size() const;

    friend size_t count_value(fix_point_collection &coll, fix_point value);
    friend fix_point sum(fix_point_collection &coll);

private:
    fix_point *m_coll;
    int m_size;
};

/**
 * Returns the number of occurrences of the specified value in the
 * collection.
 */
size_t count_value(fix_point_collection &coll, fix_point value);

/**
 * Returns the sum of all elements of the collection.
 */
fix_point sum(fix_point_collection &coll);


#endif // FIX_POINT_COLLECTION_H
