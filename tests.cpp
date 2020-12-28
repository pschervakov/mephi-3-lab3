#include "gtest/gtest.h"
#include "PriorityQueue.h"
#include "graph.h"
#include "ArraySequence.h"

using namespace std;


class TestQueue : public ::testing::Test {
public:
    void SetUp() {
        DynamicArray<int> values = {1, 10, 8, 9, 5, 15, 16, 3};
        DynamicArray<int> priors = {130, 41, 20, 100, 30, 50, 70, 80};
        queue = new PriorityQueue<int, int>(values, priors);
    }


    PriorityQueue<int, int> *queue;
};

class TestGraph : public ::testing::Test {
public:
    void SetUp() {
        graph = new Graph<int, int>();
        for (int n:{1, 2, 3, 4, 5, 6}) {
            graph->createVertex(n);
        }
        graph->makeEdge(1, 2, 7);
        graph->makeEdge(1, 3, 9);
        graph->makeEdge(1, 6, 14);
        graph->makeEdge(2, 3, 10);
        graph->makeEdge(2, 4, 15);
        graph->makeEdge(3, 4, 11);
        graph->makeEdge(4, 5, 6);
        graph->makeEdge(3, 6, 2);
        graph->makeEdge(6, 5, 9);
    }

    Graph<int, int> *graph;
};


TEST_F(TestQueue, dequeue1) {
    EXPECT_EQ(queue->dequeue(), 8);
}

TEST_F(TestQueue, dequeue2) {
    EXPECT_EQ(queue->dequeue(), 8);
    EXPECT_EQ(queue->dequeue(), 5);
}

TEST_F(TestQueue, enqueue) {
    queue->enqueue(4, 10);
    EXPECT_EQ(queue->dequeue(), 4);
}

TEST_F(TestQueue, decrease) {
    queue->decreaseKey(1, 10);
    EXPECT_EQ(queue->dequeue(), 1);
}

TEST_F(TestQueue, decrease2) {
    EXPECT_THROW(queue->decreaseKey(8, 100), std::runtime_error);
}

TEST_F(TestGraph, simple) {
    ArraySequence<int> arr({2, 3, 6});
    EXPECT_TRUE(graph->getNeighbours(1) == arr);
}

TEST_F(TestGraph, removeVertex) {
    graph->removeVertex(2);
    ArraySequence<int> arr({3, 6});
    EXPECT_TRUE(graph->getNeighbours(1) == arr);
}

TEST_F(TestGraph, removeEdge) {
    graph->removeEdge(1,2);
    ArraySequence<int> arr({3, 6});
    EXPECT_TRUE(graph->getNeighbours(1) == arr);
}

TEST_F(TestGraph, dijcstra) {
    HashTable<int, int> table(100);
    table.add(1, 0);
    table.add(2, 7);
    table.add(3, 9);
    table.add(4, 20);
    table.add(5, 20);
    table.add(6, 11);
    EXPECT_TRUE(graph->dijkstra(1) == table);
}


