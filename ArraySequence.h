//
// Created by philip on 4/20/20.
//

#ifndef LABA2_ARRAYSEQUENCE_H
#define LABA2_ARRAYSEQUENCE_H
//

#include "DynamicArray.h"
#include "Sequence.h"

template<typename T>
class ArraySequence : public Sequence<T> {
private:
    DynamicArray<T> data;

public:
    ArraySequence();

    ArraySequence(T *items, int count);

    ArraySequence(const ArraySequence<T> &arr_seq);

    ArraySequence(std::initializer_list<T> l);

    void append(T) override;

    void prepend(T) override;

    void remove(int) override;

    T get(int) const override;

    T &operator[](const int index) override;


    T get_first() override;

    T get_last() override;

    void set_elem(int index, T value) override;

    void insert_at(int, T) override;

    int get_size() override;

    void print_seq() override;

    Sequence<T> *get_sub_sequence(int start_index, int end_index) override;

    Sequence<T> *concat(Sequence<T> *seq) override;

    bool operator==(Sequence<T> &) override;

    bool operator!=(Sequence<T> &) override;
};

template<typename T>
ArraySequence<T>::ArraySequence():data() {

}

template<typename T>
ArraySequence<T>::ArraySequence(std::initializer_list<T> l):data(l) {

}

template<typename T>
ArraySequence<T>::ArraySequence(const ArraySequence<T> &arr_seq):data(arr_seq.data) {

}

template<typename T>
ArraySequence<T>::ArraySequence(T *items, int count):data(items, count) {

}

template<typename T>
void ArraySequence<T>::append(T value) {
    this->insert_at(this->get_size(), value);
}

template<typename T>
void ArraySequence<T>::prepend(T value) {
    this->insert_at(0, value);
}

template<typename T>
void ArraySequence<T>::remove(int idx) {
    this->data.remove(idx);
}

template<typename T>
T ArraySequence<T>::get(int index) const {
    return data.get(index);
}

template<class T>
T &ArraySequence<T>::operator[](const int index) {
    return data[index];
}

template<typename T>
T ArraySequence<T>::get_first() {
    return data.get(0);
}

template<typename T>
T ArraySequence<T>::get_last() {
    return data.get(data.get_size() - 1);
}

template<typename T>
void ArraySequence<T>::insert_at(int index, T value) {
    data.resize(data.get_size() + 1);
    for (int i = data.get_size() - 2; i >= index; --i) {
        data.set(i + 1, data.get(i));
    }
    data.set(index, value);
}

template<typename T>
int ArraySequence<T>::get_size() {
    return data.get_size();

}

template<typename T>
Sequence<T> *ArraySequence<T>::get_sub_sequence(int start_index, int end_index) {
    ArraySequence<T> *arr = new ArraySequence<T>;
    arr->data = *(this->data.slice(start_index, end_index));
    return arr;

}

template<typename T>
Sequence<T> *ArraySequence<T>::concat(Sequence<T> *seq) {
    ArraySequence<T> *arr = new ArraySequence<T>(*this);
    arr->data.resize(this->get_size() + seq->get_size());
    for (int i = this->get_size(); i < this->get_size() + seq->get_size(); ++i) {
        arr->set_elem(i, seq->get(i));
    }
    return arr;

}


template<typename T>
void ArraySequence<T>::set_elem(int index, T value) {
    data.set(index, value);
}

template<typename T>
void ArraySequence<T>::print_seq() {
    data.print_arr();

}

template<typename T>
bool ArraySequence<T>::operator==(Sequence<T> &arr) {
    if (this->get_size() != arr.get_size()) return false;

    for (int i = 0; i < this->get_size(); i++)
        if (this->get(i) != arr.get(i)) return false;

    return true;
}

template<typename T>
bool ArraySequence<T>::operator!=(Sequence<T> &arr) {
    return not(*this == arr);
}


#endif //LABA2_ARRAYSEQUENCE_H


