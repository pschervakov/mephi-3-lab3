//
// Created by philip on 4/20/20.
//
//
#ifndef LABA2_SEQUENCE_H
#define LABA2_SEQUENCE_H


template<typename T>
class Sequence {
private:

public:
    Sequence() = default;

    virtual int get_size() = 0;

    virtual void append(T) = 0;

    virtual void prepend(T) = 0;

    virtual void remove(int) = 0;

    virtual T get_first() = 0;

    virtual T get_last() = 0;

    virtual void insert_at(int, T) = 0;

    virtual T get(int index) const = 0;

    virtual T &operator[](const int index) = 0;

    virtual Sequence<T> *get_sub_sequence(int start_index, int end_index) = 0;

    virtual Sequence<T> *concat(Sequence<T> *list) = 0;

    virtual void set_elem(int, T) = 0;

    virtual void print_seq() = 0;

    virtual bool operator==(Sequence<T> &) = 0;

    virtual bool operator!=(Sequence<T> &) = 0;

};

#endif //LABA2_SEQUENCE_H