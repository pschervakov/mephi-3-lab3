#ifndef LABA2_DYNAMICARRAY_H
#define LABA2_DYNAMICARRAY_H
//

#include <iostream>

using std::cout;
using std::cin;


template<class T>
class DynamicArray {
private:
    int size;
    int count;
    T *data;
public:
    DynamicArray();

    ~DynamicArray();

    DynamicArray(int len);

    DynamicArray(std::initializer_list<T> l);

    DynamicArray(T *items, int count);

    DynamicArray(const DynamicArray<T> &darray);

    T get(int index) const;

    void remove(int index);

    T &operator[](const int index);

    void set(int index, T value);

    void resize(int new_size);

    int get_size();

    int get_count();


    void print_arr();

    DynamicArray<T> *slice(int start_index, int end_index);

    DynamicArray<T> *concat(DynamicArray<T> &darray);

    bool operator==(const DynamicArray<T> &arr);


};

template<class T>
DynamicArray<T>::DynamicArray() {
    data = nullptr;
    size = 0;
    count = 0;
}

template<class T>
DynamicArray<T>::DynamicArray(int len) {
    size = len;
    count = 0;
    data = new T[size];

}

template<class T>
DynamicArray<T>::DynamicArray(std::initializer_list<T> l) {
    count = l.size();
    size = count;
    data = new T[size];
    int i = 0;
    for (const T &item:l) {
        data[i] = item;
        ++i;
    }

}

template<class T>
DynamicArray<T>::DynamicArray(T *items, int count) {
    size = count;
    this->count = count;
    data = new T[size];
    for (int i = 0; i < count; ++i) {
        data[i] = items[i];
    }
}

template<class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T> &darray) {
    size = darray.size;
    count = darray.count;
    data = new T[size];
    for (int i = 0; i < size; ++i) {
        data[i] = darray.data[i];
    }
}

template<class T>
DynamicArray<T>::~DynamicArray() {
    if (size > 0) {
        delete[] data;
        size = 0;
    }
};

template<class T>
int DynamicArray<T>::get_size() {
    return size;
}

template<class T>
int DynamicArray<T>::get_count() {
    return count;
}

template<class T>
T DynamicArray<T>::get(int index) const {
    if (index < 0 or index > (size - 1)) {
        cout << "index out of range";

    } else {
        return data[index];
    }
}

template<class T>
T &DynamicArray<T>::operator[](const int index) {
    if (index < 0 or index > (size - 1)) {
        cout << "index out of range";

    } else {
        return data[index];
    }
}


template<class T>
void DynamicArray<T>::set(int index, T value) {
    if (index < 0 or index > (size - 1)) {
        cout << "index out of range";
    } else {
        data[index] = value;
        count += 1;
    }
}

template<class T>
void DynamicArray<T>::resize(int new_size) {
    DynamicArray<T> buff_arr(*this);
    delete[] data;
    size = new_size;
    data = new T[new_size];
    for (int i = 0; i < size; ++i) {
        data[i] = buff_arr.data[i];
    }
}

template<class T>
DynamicArray<T> *DynamicArray<T>::slice(int start_index, int end_index) {
    DynamicArray<T> *arr = new DynamicArray<T>(end_index - start_index + 1);
    for (int i = 0; i <= end_index - start_index; ++i) {
        arr->set(i, this->get(i + start_index));
    }
    return arr;
}

template<class T>
DynamicArray<T> *DynamicArray<T>::concat(DynamicArray<T> &darray) {
    DynamicArray<T> *result = new DynamicArray<T>(this->size + darray.size);
    result->data = new T[this->size + darray.size];
    std::copy(this->data, this->data + this->size, result->data);
    std::copy(darray.data, darray, data + darray.size, result->data + this->size);
    result->size = darray.size + this->size;
    return result;
}

template<class T>
void DynamicArray<T>::print_arr() {
    for (int i = 0; i < size; ++i) {
        cout << data[i] << " ";
    }
}

template<class T>
bool DynamicArray<T>::operator==(const DynamicArray<T> &arr) {
    if (this->size != arr.size) return false;

    for (int i = 0; i < this->size; i++)
        if (this->get(i) != arr.get(i)) return false;

    return true;
}

template<class T>
void DynamicArray<T>::remove(int index) {
    for (int i = index; i < 3; ++i) {
        data[i] = data[i + 1];
    }
    this->resize(size - 1);
}



#endif //LABA2_DYNAMICARRAY_H

