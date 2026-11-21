/**
 * @file quadtree.cpp
 *
 * @author CS 221: Basic Algorithms and Data Structures
 **/

#include "quadtree.h"

QuadTree::QuadTree(const PNG &img) {
  root_ = build(img, 0, 0, img.width(), img.height());
}

QuadTree::~QuadTree() { clear(root_); }

void QuadTree::prune(double tol) { prune(root_, tol); }

std::vector<Block> QuadTree::leaves() const {
  std::vector<Block> out;
  leaves(root_, out);
  return out;
}

int QuadTree::size() const { return size(root_); }

Stats QuadTree::rootStats() const {
  return root_ ? root_->block.stats : Stats();
}

/**
 * Returns a new subtree for the w x h block at (x, y), built down to
 * single pixels, with every node's stats filled in. w and h are at
 */
QuadTree::Node *QuadTree::build(const PNG &img, int x, int y, int w, int h) {
  // Your code here
  return nullptr; // replace this line
}

/** Frees the subtree rooted at nd and sets nd to nullptr. */
void QuadTree::clear(Node *&nd) {
  if (!nd)
    return;

  for (int i = 0; i < 4; i++) {
    clear(nd->kids[i]);
  }
  delete nd;
  nd = nullptr;
}

/** prune() for the subtree rooted at nd. */
void QuadTree::prune(Node *nd, double tol) {
  if (!nd)
    return;
  if (nd->block.stats.error() > tol) {
    for (int i = 0; i < 4; i++) {
      prune(nd->kids[i], tol);
    }
  } else {
    for (int i = 0; i < 4; i++) {
      clear(nd->kids[i]);
    }
  }
}

/** Appends the leaves under nd to out, in preorder. */
void QuadTree::leaves(const Node *nd, std::vector<Block> &out) const {
  if (!nd)
    return;
  // homefor (int i = 0; i < 4; i++) {
  //   if (!1)
  // }
  //  Your code here
}

/** Number of nodes in the subtree rooted at nd. */
int QuadTree::size(const Node *nd) const {
  // Your code here
  return 0; // replace this line
}
