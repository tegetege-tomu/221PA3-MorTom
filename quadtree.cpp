/**
 * @file quadtree.cpp
 *
 * @author CS 221: Basic Algorithms and Data Structures
**/

#include "quadtree.h"

QuadTree::QuadTree(const PNG& img) {
    root_ = build(img, 0, 0, img.width(), img.height());
}

QuadTree::~QuadTree() {
    clear(root_);
}

void QuadTree::prune(double tol) {
    prune(root_, tol);
}

std::vector<Block> QuadTree::leaves() const {
    std::vector<Block> out;
    leaves(root_, out);
    return out;
}

int QuadTree::size() const {
    return size(root_);
}

Stats QuadTree::rootStats() const {
    return root_ ? root_->block.stats : Stats();
}

QuadTree::Node* QuadTree::build(const PNG& img, int x, int y, int w, int h) {
    // Your code here
    return nullptr;   // replace this line
}

void QuadTree::clear(Node*& nd) {
    // Your code here
}

void QuadTree::prune(Node* nd, double tol) {
    // Your code here
}

void QuadTree::leaves(const Node* nd, std::vector<Block>& out) const {
    // Your code here
}

int QuadTree::size(const Node* nd) const {
    // Your code here
    return 0;   // replace this line
}
