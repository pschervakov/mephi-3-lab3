#ifndef MEPHI_3_LAB2_IDICTIONARY_H
#define MEPHI_3_LAB2_IDICTIONARY_H

#include <iostream>
#include "string"

using namespace std;
using std::string;

template<class K, class V>
class IDictionary {
public:
    virtual void add(K, V) = 0;

    virtual void remove(K) = 0;

    virtual V &at(K) = 0;

    virtual V get(K) = 0;

    virtual V &operator[](K) = 0;

    virtual bool find(K) = 0;

    virtual int getCount() = 0;

    virtual int getCapacity() = 0;


    virtual bool operator==(IDictionary<K, V> &) = 0;


    virtual void print(ostream &strm) = 0;


};


#endif //MEPHI_3_LAB2_IDICTIONARY_H

