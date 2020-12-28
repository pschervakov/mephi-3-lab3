#ifndef LAB2_HASHTABLE
#define LAB2_HASHTABLE


#include <iostream>
#include "DynamicArray.h"
#include <string>
#include "IDictionary.h"

using namespace std;
using std::string;


template<class K, class V>
struct Pair {
    K key;
    V value;
};

class HashTableException : public std::exception {
private:
    std::string error;

public:
    explicit HashTableException(std::string error)
            : error(error) {}

    string getError() { return error; }
};


template<class K, class V>
class HashTable : public IDictionary<K, V> {
private:
    struct HashTablePair;

    int capacity;
    int size;
    const double coef = 0.7;
    DynamicArray<HashTablePair> data;

    int getHasH1(K);

    int getHash2(K);

    void resize(int);


public:
    class HashTableIterator;

    explicit HashTable(int);

    void add(K, V) override;

    void remove(K) override;

    int getCapacity();

    int getCount();

    V &at(K) override;

    V get(K) override;

    V &operator[](K) override;

    bool find(K) override;


    HashTableIterator getIterator();

    bool operator==(IDictionary<K, V> &) override;

    void print(ostream &strm) override;

};

template<class K, class V>
HashTable<K, V>::HashTable(int cap)
        : data(DynamicArray<HashTablePair>(cap)), capacity(cap), size(0) {}


template<class K, class V>
struct HashTable<K, V>::HashTablePair {
    K key;
    V value;
    bool is_present;

    HashTablePair() : is_present(false) {};

    HashTablePair(K key, V value)
            : key(key), value(value), is_present(true) {};


};


template<class K, class V>
int HashTable<K, V>::getHasH1(K key) {
    return sizeof(key) % capacity;
}

template<class K, class V>
int HashTable<K, V>::getHash2(K) {
    return 1;
}

template<class K, class V>
void HashTable<K, V>::add(K key, V value) {
    if (size > int(capacity * coef)) {
        resize(size * 2);
    }

    int n = getHasH1(key);
    int m = getHash2(key);
    int i = 0;
    while (i < capacity and data[n].is_present) {
        if (data[n].key == key) {
            break;
        }
        n = (n + m) % capacity;
        ++i;
    }
    data[n] = HashTablePair(key, value);
    ++size;
}

template<class K, class V>
void HashTable<K, V>::remove(K key) {
    int n = getHasH1(key);
    int m = getHash2(key);
    int i = 0;
    while (i < capacity) {
        if (data[n].key == key and data[n].is_present) {
            data[n].is_present = false;
            --size;
            return;
        }
        n = (n + m) % capacity;
        ++i;
    }
    throw HashTableException("element not found");
}


template<class K, class V>
V &HashTable<K, V>::at(K key) {
    int n = getHasH1(key);
    int m = getHash2(key);
    int i = 0;
    while (i < capacity) {
        if (data[n].key == key and data[n].is_present) {
            return data[n].value;
        }
        n = (n + m) % capacity;
        ++i;

    }
    throw HashTableException("element not found");
}

template<class K, class V>
V HashTable<K, V>::get(K key) {
    return at(key);
}


template<class K, class V>
bool HashTable<K, V>::find(K key) {
    try {
        this->at(key);
        return true;

    }
    catch (HashTableException &) {
        return false;
    }
}


template<class K, class V>
void HashTable<K, V>::resize(int new_size) {
    data.resize(new_size);
    size = new_size;
}

template<class K, class V>
int HashTable<K, V>::getCapacity() {
    return capacity;
}

template<class K, class V>
int HashTable<K, V>::getCount() {
    return size;
}

template<class K, class V>
class HashTable<K, V>::HashTableIterator {
private:
    int idx;
    int table_size;
    HashTable<K, V> *table;

public:
    explicit HashTableIterator(HashTable<K, V> *table) {
        this->table = table;
        table_size = table->capacity;
        idx = 0;
    }

    bool hasNext() {
        for (int i = idx; i < table_size; ++i) {
            if (table->data[i].is_present) return true;
        }
        return false;

    }

    Pair<K, V> next() {
        while (table->data[idx].is_present != true) {
            if (idx >= table_size - 1) throw HashTableException("end of collection");
            ++idx;
        }
        Pair<K, V> pair = Pair<K, V>{.key=table->data[idx].key, .value=table->data[idx].value};
        ++idx;
        return pair;
    }
};

template<class K, class V>
typename HashTable<K, V>::HashTableIterator HashTable<K, V>::getIterator() {
    return HashTable::HashTableIterator(this);
}

template<class K, class V>
bool HashTable<K, V>::operator==(IDictionary<K, V> &table) {
    if (this->size != table.getCount() or this->capacity != table.getCapacity()) return false;
    HashTable<K, V>::HashTableIterator iter = this->getIterator();
    for (; iter.hasNext();) {
        Pair<K, V> pair = iter.next();
        K key = pair.key;
        V value = pair.value;
        if (not table.find(key) or table.at(key) != this->at(key)) {
            return false;
        }
    }
    return true;
}

template<class K, class V>
void HashTable<K, V>::print(ostream &strm) {
    strm << "{ ";
    for (int i = 0; i < this->capacity; ++i) {
        if (this->data[i].is_present) {
            strm << this->data[i].key << ":" << this->data[i].value << " ";
        }
    }
    strm << "}";
}

template<class K, class V>
V &HashTable<K, V>::operator[](const K key) {
    return at(key);
}


template<class K, class V>
std::ostream &operator<<(ostream &strm, IDictionary<K, V> &table) {
    table.print(strm);
    return strm;
}

#endif //LAB2_HASHTABLE






