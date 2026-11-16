/**
 * @file heap.h
 *
 * A min-heap, used as a priority queue: the smallest item comes out first.
 * It is stored in a vector with the root at index 1. Index 0 is never used,
 * so the parent of i is i/2 and its children are 2i and 2i+1.
 *
 * Items are compared ONLY with <: a < b means a is smaller than b, so a comes
 * out of the heap first. T can be any type that has a < operator (int,
 * double, or a struct that defines operator<, like Frontier in crystals.h).
 *
 * @author CS 221: Basic Algorithms and Data Structures
**/

#ifndef HEAP_H
#define HEAP_H

#include <vector>
#include <stdexcept>

template <class T>
class MinHeap {
public:
    MinHeap() : data_(1) {}   // data_[0] is the unused slot

    /** Adds t to the heap. */
    void push(const T& t) {
        // Your code here
    }

    /** Removes and returns the smallest item. */
    T pop() {
        if (empty()) throw std::out_of_range("pop from an empty heap");
        // Your code here
        return data_[1];   // replace this line
    }

    /** Returns the smallest item, without removing it. */
    const T& peek() const {
        if (empty()) throw std::out_of_range("peek at an empty heap");
        // Your code here
        return data_[1];   // replace this line
    }

    unsigned int size() const { return data_.size() - 1; }

    bool empty() const { return data_.size() == 1; }

private:
    std::vector<T> data_;

    static size_t parent(size_t i) { return i / 2; }
    static size_t left(size_t i) { return 2 * i; }
    static size_t right(size_t i) { return 2 * i + 1; }

    /** Moves data_[i] up until it is not smaller than its parent. */
    void heapifyUp(size_t i) {
        // Your code here
    }

    /** Moves data_[i] down until neither child is smaller than it. */
    void heapifyDown(size_t i) {
        // Your code here
    }
};

#endif
