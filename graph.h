#ifndef MEPHI_3_LAB3_GRAPH_H
#define MEPHI_3_LAB3_GRAPH_H

#include "HashTable.h"
#include "DynamicArray.h"
#include "ArraySequence.h"
#include "PriorityQueue.h"
#include <limits>


template<class E, class V>
class Edge;

template<class V, class E>
class Vertex {
    V id;

public:
    V getId() {
        return id;
    }

    Vertex(V id) : id(id) {};

    Vertex() {};
    ArraySequence<Edge<E, V> *> edges_out = ArraySequence<Edge<E, V> *>();

    ArraySequence<Edge<E, V> *> edges_in = ArraySequence<Edge<E, V> *>();

    bool operator>(const Vertex<V, E> &ver) {
        return this->id > ver.id;
    }

    bool operator<(const Vertex<V, E> &ver) {
        return this->id < ver.id;
    }

    bool operator==(const Vertex<V, E> &ver) {
        return this->id == ver.id;
    };

    bool operator!=(const Vertex<V, E> &ver) {
        return this->id != ver.id;
    }
};

template<class E, class V>
class Edge {


public:
    Vertex<V, E> from;
    Vertex<V, E> to;
    E weight;

    Edge(Vertex<V, E> from, Vertex<V, E> to, E w) :
            from(from), to(to), weight(w) {};

    Edge() {};

};

template<class E, class V>
class Graph {
    HashTable<V, Vertex<V, E>> table = HashTable<V, Vertex<V, E>>(100);


public:
    void createVertex(V id);

    void makeEdge(V vertex1, V vertex2, E weight);

    void removeVertex(V);

    void removeEdge(V, V);

    ArraySequence<V> getNeighbours(V);

    HashTable<V, E> dijkstra(V);

};

template<class E, class V>
void Graph<E, V>::createVertex(V id) {
    if (table.find(id)) throw std::runtime_error("vertex already exists");
    table.add(id, Vertex<V, E>(id));
}

template<class E, class V>
void Graph<E, V>::makeEdge(V vertex1, V vertex2, E weight) {
    if (not(table.find(vertex2) and table.find(vertex1))) throw std::runtime_error("vertex not found");
    auto *edge = new Edge<E, V>(vertex1, vertex2, weight);
    Vertex<V, E> &ver1 = table[vertex1];
    Vertex<V, E> &ver2 = table[vertex2];
    ver1.edges_out.append(edge);
    ver2.edges_in.append(edge);


}

template<class E, class V>
HashTable<V, E> Graph<E, V>::dijkstra(V ver) {
    if (not table.find(ver)) throw runtime_error("vertex not found");
    HashTable<V, E> labels = HashTable<V, E>(100);
    PriorityQueue<V, E> queue = PriorityQueue<V, E>(100);
    auto iter = table.getIterator();
    for (; iter.hasNext();) {
        V id = iter.next().value.getId();
        queue.enqueue(id, std::numeric_limits<E>::max());
        labels.add(id, std::numeric_limits<E>::max());
    }
    queue.decreaseKey(ver, 0);
    labels[ver] = 0;
    for (int j = 0; j < table.getCount(); ++j) {
        V min_v = queue.dequeue();
        Vertex<V, E> &vertex = table[min_v];
        for (int i = 0; i < vertex.edges_out.get_size(); ++i) {
            auto edge = vertex.edges_out[i];
            if (labels[min_v] < labels[edge->to.getId()] - edge->weight) {
                labels[edge->to.getId()] = edge->weight + labels[min_v];
                auto id = edge->to.getId();
                queue.decreaseKey(edge->to.getId(), edge->weight + labels[min_v]);
            };
        }
    }
    return labels;
}

template<class E, class V>
ArraySequence<V> Graph<E, V>::getNeighbours(V vertex) {
    ArraySequence<V> arr{};
    Vertex<V, E> &ver = table[vertex];
    for (int i = 0; i < ver.edges_out.get_size(); ++i) {
        arr.append(ver.edges_out[i]->to.getId());
    }
    return arr;
}

template<class E, class V>
void Graph<E, V>::removeVertex(V id) {
    Vertex<V, E> &vertex = table[id];
    int c = vertex.edges_out.get_size();;
    for (int i = 0; i < c; ++i) {
        this->removeEdge(id, vertex.edges_out[0]->to.getId());
    }
    c = vertex.edges_in.get_size();
    for (int i = 0; i < c; ++i) {
        this->removeEdge(vertex.edges_in[0]->from.getId(), id);
    }
    table.remove(id);
}

template<class E, class V>
void Graph<E, V>::removeEdge(V vertex1, V vertex2) {
    for (int i = 0; i < table[vertex1].edges_out.get_size(); ++i) {
        if (table[vertex1].edges_out[i]->to == table[vertex2]) {
            table[vertex1].edges_out.remove(i);
        }
    }
    for (int i = 0; i < table[vertex2].edges_in.get_size(); ++i) {
        if (table[vertex2].edges_in[i]->from == table[vertex1]) {
            table[vertex2].edges_in.remove(i);
        }
    }
}

template<class V, class E>
std::ostream &operator<<(ostream &strm, Vertex<V, E> &vertex) {
    strm << vertex.getId();
    return strm;
}

#endif //MEPHI_3_LAB3_GRAPH_H
