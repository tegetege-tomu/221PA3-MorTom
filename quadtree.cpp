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
  Node *nd = new Node(x, y, w, h);

  if (w == 1 && h == 1) {
    nd->block.stats = Stats(*img.getPixel(x, y));
    return nd;
  }

  int leftish = (w + 1) / 2;
  int rightish = w - leftish;
  int topish = (h + 1) / 2;
  int bottomish = h - topish;

  nd->kids[NW] = build(img, x, y, leftish, topish);

  if (rightish > 0)
    nd->kids[NE] = build(img, x + leftish, y, rightish, topish);

  if (bottomish > 0)
    nd->kids[SW] = build(img, x, y + topish, leftish, bottomish);

  if (rightish > 0 && bottomish > 0)
    nd->kids[SE] = build(img, x + leftish, y + topish, rightish, bottomish);

  if (nd->kids[NW])
    nd->block.stats.add(nd->kids[NW]->block.stats);
  if (nd->kids[NE])
    nd->block.stats.add(nd->kids[NE]->block.stats);
  if (nd->kids[SW])
    nd->block.stats.add(nd->kids[SW]->block.stats);
  if (nd->kids[SE])
    nd->block.stats.add(nd->kids[SE]->block.stats);

  return nd;
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
  if (!nd->kids[NW] && !nd->kids[NE] && !nd->kids[SW] && !nd->kids[SE]) {
    out.push_back(nd->block);
    return;
  }
  if (nd->kids[NW]) {
    QuadTree::leaves(nd->kids[NW], out);
  }
  if (nd->kids[NE]) {
    QuadTree::leaves(nd->kids[NE], out);
  }
  if (nd->kids[SW]) {
    QuadTree::leaves(nd->kids[SW], out);
  }
  if (nd->kids[SE]) {
    QuadTree::leaves(nd->kids[SE], out);
  }
}

/** Number of nodes in the subtree rooted at nd. */
int QuadTree::size(const Node *nd) const { return size(nd, 0); }

/** Number of nodes in the subtree rooted at nd: accumulator. */
int QuadTree::size(const Node *nd, int sum) const {
  if (!nd)
    return sum;

  int s = sum + 1;

  if (nd->kids[NW])
    s = QuadTree::size(nd->kids[NW], s);
  if (nd->kids[NE])
    s = QuadTree::size(nd->kids[NE], s);
  if (nd->kids[SW])
    s = QuadTree::size(nd->kids[SW], s);
  if (nd->kids[SE])
    s = QuadTree::size(nd->kids[SE], s);

  return s;
}
