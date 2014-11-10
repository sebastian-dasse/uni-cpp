#ifndef FIX_POINT_COLLECTION_H
#define FIX_POINT_COLLECTION_H

#include <cstdint>
#include "fix_point.h"

using std::size_t;

struct node {
    fix_point val;
    node *next;
};

struct fix_point_collection {
    fix_point_collection();
    ~fix_point_collection();

    fix_point push_back(float val);
    fix_point pop_back();
    fix_point operator[](int index) const;
    fix_point operator[](fix_point index) const;
    fix_point operator[](int index);
    size_t size() const;

private:
    node *coll;
};

fix_point sum(fix_point_collection coll);
size_t count_value(fix_point_collection coll, float f);


#endif // FIX_POINT_COLLECTION_H
