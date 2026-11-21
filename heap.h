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

#include <algorithm>
#include <cstddef>
#include <stdexcept>
#include <vector>

template <class T> class MinHeap {
public:
  MinHeap() : data_(1) {} // data_[0] is the unused slot

  /** Adds t to the heap. */
  void push(const T &t) {
    data_.push_back(t);
    heapifyUp(size());
  }

  /** Removes and returns the smallest item. */
  T pop() {
    if (empty())
      throw std::out_of_range("pop from an empty heap");
    T minVal = data_[1];
    data_[1] = data_.back();
    data_.pop_back(); // convenient!
    if (!empty())
      heapifyDown(1);
    return minVal;
  }

  /** Returns the smallest item, without removing it. */
  const T &peek() const {
    if (empty())
      throw std::out_of_range("peek at an empty heap");
    // Your code here
    // //NO NEED! // //
    return data_[1]; // replace this line //NO NEED //
  }

  unsigned int size() const { return data_.size() - 1; }

  bool empty() const { return data_.size() == 1; }

private:
  std::vector<T> data_;

  static size_t parent(size_t i) { return i / 2; }
  static size_t left(size_t i) { return 2 * i; }
  static size_t right(size_t i) { return 2 * i + 1; }

  //================HELPERS=====================
  bool hasAChild(size_t i) const { return 2 * i <= size(); }

  size_t minChild(size_t i) const {
    // assume already checked hasAChild(i).
    if (right(i) <= size() && data_[right(i)] < data_[left(i)])
      return right(i);
    return left(i);
  }
  //================HINDERERS===================

  /** Moves data_[i] up until it is not smaller than its parent. */
  void heapifyUp(size_t i) {
    if (i > 1) {
      if (data_[i] < data_[parent(i)]) {
        std::swap(data_[i], data_[parent(i)]);
        heapifyUp(parent(i));
      }
    }
  }

  /** Moves data_[i] down until neither child is smaller than it. */
  void heapifyDown(size_t i) {
    if (hasAChild(i)) {
      size_t minChildIndex = minChild(i);
      if (data_[minChildIndex] < data_[i]) {
        std::swap(data_[i], data_[minChildIndex]);
        heapifyDown(minChildIndex);
      }
    }
  }
};

#endif
