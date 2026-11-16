/**
 * @file quadtree.h
 *
 * A quadtree over the pixels of an image. The constructor builds the tree all
 * the way down to single pixels; prune() then collapses every subtree whose
 * block is already close to one colour.
 *
 * Coordinates: (x, y) is column x, row y, as in PNG::getPixel(x, y). x runs
 * from 0 to width-1, left to right; y runs from 0 to height-1, top to bottom;
 * (0, 0) is the upper-left pixel.
 *
 * Splitting a w x h block at (x, y): the left children get wl = (w+1)/2
 * columns and the right children the rest; the top children get ht = (h+1)/2
 * rows and the bottom children the rest. The children are
 *
 *   kids[NW]  upper left   at (x,      y),       wl     x  ht
 *   kids[NE]  upper right  at (x + wl, y),       w - wl x  ht
 *   kids[SW]  lower left   at (x,      y + ht),  wl     x  h - ht
 *   kids[SE]  lower right  at (x + wl, y + ht),  w - wl x  h - ht
 *
 * A child with no rows or no columns is not created (its pointer is nullptr),
 * so a 1-pixel-wide block has only NW and SW children.
 *
 * @author CS 221: Basic Algorithms and Data Structures
**/

#ifndef QUADTREE_H
#define QUADTREE_H

#include <vector>
#include "cs221util/PNG.h"
#include "stats.h"

using namespace cs221util;

/** A rectangle of the image, with the colour totals of its pixels. */
struct Block {
    int x, y;    // upper-left corner: column x, row y
    int w, h;    // width and height in pixels
    Stats stats;
};

class QuadTree {
public:
    enum Child { NW = 0, NE = 1, SW = 2, SE = 3 };

    /** Builds the full tree for img, down to single pixels. */
    QuadTree(const PNG& img);

    ~QuadTree();

    // A quadtree is not copied in this assignment.
    QuadTree(const QuadTree&) = delete;
    QuadTree& operator=(const QuadTree&) = delete;

    /**
     * Collapses every node whose stats.error() is at most tol into a leaf,
     * freeing everything below it. Nodes are checked from the root down, so
     * a node's subtree is only examined if the node itself is not pruned.
     */
    void prune(double tol);

    /** The leaves' blocks, in preorder: a node's NW subtree, then NE, SW, SE. */
    std::vector<Block> leaves() const;

    /** Number of nodes in the tree. */
    int size() const;

    /** Totals for the whole image. */
    Stats rootStats() const;

private:
    struct Node {
        Block block;
        Node* kids[4];   // indexed by Child; nullptr when absent
        Node(int x, int y, int w, int h) : block{x, y, w, h, Stats()}, kids{nullptr, nullptr, nullptr, nullptr} {}
    };

    Node* root_;

    /**
     * Returns a new subtree for the w x h block at (x, y), built down to
     * single pixels, with every node's stats filled in. w and h are at least 1.
     */
    Node* build(const PNG& img, int x, int y, int w, int h);

    /** Frees the subtree rooted at nd and sets nd to nullptr. */
    void clear(Node*& nd);

    /** prune() for the subtree rooted at nd. */
    void prune(Node* nd, double tol);

    /** Appends the leaves under nd to out, in preorder. */
    void leaves(const Node* nd, std::vector<Block>& out) const;

    /** Number of nodes in the subtree rooted at nd. */
    int size(const Node* nd) const;
};

#endif
