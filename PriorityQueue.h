
#ifndef LABA3_BINARYHEAP_H
#define LABA3_BINARYHEAP_H


#include <iostream>
#include "DynamicArray.h"

using std::cout;


template<class T, class P>
class PriorityQueue {

    int size;
    const int capacity = 100;
public:
    struct Pair {
        T value;
        P priority;
    };

    PriorityQueue(int capacity);

    PriorityQueue();

    PriorityQueue(DynamicArray<T> values, DynamicArray<P> priors);

    DynamicArray<Pair> data;

    void enqueue(T, P);

    void decreaseKey(T, P);

    void del(T);

    int search(T);

    void print();

    void heapify(int i);

    T dequeue();
};

template<class T, class P>
PriorityQueue<T, P>::PriorityQueue(int cap):capacity(cap) {
    data = DynamicArray<Pair>(capacity);
    size = 0;
}
template<class T, class P>
PriorityQueue<T, P>::PriorityQueue() {
    data = DynamicArray<Pair>(capacity);
    size = 0;
}

template<class T, class P>
void PriorityQueue<T, P>::decreaseKey(T elem, P prior) {
    int i = search(elem);
    if (data[i].priority<prior) throw std::runtime_error("new priority is bigger than old ");
    data[i] = Pair{.value=elem, .priority=prior};
    int parent = (i - 1) / 2;
    while (data[i].priority < data[parent].priority and i > 0) {
        Pair temp = data[i];
        data[i] = data[parent];
        data[parent] = temp;
        i = parent;
        parent = (i - 1) / 2;
    }

}

template<class T, class P>
void PriorityQueue<T, P>::enqueue(T elem, P prior) {
    if (size>capacity*0.7){
        data.resize(size*2);
    }
    int i = size;
    data[i] = Pair{.value=elem, .priority=prior};
    int parent = (i - 1) / 2;
    while (data[i].priority < data[parent].priority and i > 0) {
        Pair temp = data[i];
        data[i] = data[parent];
        data[parent] = temp;
        i = parent;
        parent = (i - 1) / 2;
    }
    ++size;
}

template<class T, class P>
void PriorityQueue<T, P>::heapify(int i) {

    int left, right;
    Pair temp;
    left = 2 * i + 1;
    right = 2 * i + 2;
    if (left < size) {
        if (data[i].priority > data[left].priority) {
            temp = data[i];
            data[i] = data[left];
            data[left] = temp;
            heapify(left);
        }
    }
    if (right < size) {
        if (data[i].priority > data[right].priority) {
            temp = data[i];
            data[i] = data[right];
            data[right] = temp;
            heapify(right);
        }
    }
}

template<class T, class P>
int PriorityQueue<T, P>::search(T value) {
    for (int i = 0; i < size; ++i) {
        if (data[i].value == value) {
            return i;
        }
    }
    return -1;

}

template<class T, class P>
void PriorityQueue<T, P>::del(T value) {
    int idx = search(value);
    data[idx] = data[size - 1];
    --size;
    heapify(idx);
}

template<class T, class P>
void PriorityQueue<T, P>::print() {
    for (int i = 0; i < size; ++i) {
        cout << data[i] << " ";
    }

}

template<class T, class P>
T PriorityQueue<T, P>::dequeue() {
    T min = data[0].value;
    data[0] = data[size - 1];
    --size;
    heapify(0);
    return min;

}

template<class T, class P>
PriorityQueue<T, P>::PriorityQueue(DynamicArray<T> values, DynamicArray<P> priors) {
    size=0;
    data = DynamicArray<Pair>(capacity);
    for (int i = 0; i < values.get_count(); ++i) {
        this->enqueue(values[i], priors[i]);
    }
}



#endif //LABA3_BINARYHEAP_H