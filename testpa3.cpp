/**
 * @file testpa3.cpp
 *
 * Starter tests for PA3. Build with `make tests`, then run ./testpa3
 * (all tests) or, for example, ./testpa3 "[heap]" (one group).
 *
 * These are a start, not the grader: passing them does not mean your code is
 * correct. Add your own.
 *
 * @author CS 221: Basic Algorithms and Data Structures
**/

#define CATCH_CONFIG_MAIN
#include "cs221util/catch.hpp"

#include <vector>
#include "cs221util/PNG.h"
#include "heap.h"
#include "quadtree.h"
#include "crystals.h"
#include "render.h"

using namespace cs221util;
using namespace std;

// ---------------------------------------------------------------- heap

TEST_CASE("heap: pops in order", "[heap]") {
    MinHeap<int> h;
    for (int v : {5, 3, 8, 1, 9, 2, 7}) h.push(v);
    REQUIRE(h.size() == 7);
    REQUIRE(h.peek() == 1);
    vector<int> out;
    while (!h.empty()) out.push_back(h.pop());
    REQUIRE(out == vector<int>({1, 2, 3, 5, 7, 8, 9}));
}

// Ordered by its own operator<, which here means "larger": the heap must
// compare items only with <.
struct Big {
    int v;
    bool operator<(const Big& o) const { return v > o.v; }
};

TEST_CASE("heap: the item's < decides the order", "[heap]") {
    MinHeap<Big> h;
    for (int v : {5, 3, 8, 1}) h.push(Big{v});
    REQUIRE(h.pop().v == 8);
    REQUIRE(h.pop().v == 5);
}

TEST_CASE("heap: pushes and pops mixed", "[heap]") {
    MinHeap<int> h;
    h.push(4); h.push(2);
    REQUIRE(h.pop() == 2);
    h.push(1); h.push(3);
    REQUIRE(h.pop() == 1);
    REQUIRE(h.pop() == 3);
    REQUIRE(h.pop() == 4);
    REQUIRE(h.empty());
}

// ---------------------------------------------------------------- quadtree

// A w x h image, every pixel the given colour.
static PNG solid(int w, int h, RGBAPixel c) {
    PNG img(w, h);
    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++) *img.getPixel(x, y) = c;
    return img;
}

TEST_CASE("quadtree: a 4x4 image has 21 nodes and 16 leaves", "[quadtree]") {
    PNG img = solid(4, 4, RGBAPixel(10, 20, 30));
    QuadTree t(img);
    REQUIRE(t.size() == 1 + 4 + 16);
    REQUIRE(t.leaves().size() == 16);
    REQUIRE(t.rootStats().n == 16);
    REQUIRE(t.rootStats().r == 160);
}

TEST_CASE("quadtree: odd sizes split with the extra row and column to the top left", "[quadtree]") {
    PNG img = solid(3, 1, RGBAPixel(0, 0, 0));
    QuadTree t(img);
    // 3x1 -> NW 2x1, NE 1x1; 2x1 -> NW 1x1, NE 1x1
    REQUIRE(t.size() == 5);
    vector<Block> L = t.leaves();
    REQUIRE(L.size() == 3);
    REQUIRE(L[0].x == 0);
    REQUIRE(L[1].x == 1);
    REQUIRE(L[2].x == 2);
}

TEST_CASE("quadtree: a solid image prunes to one leaf", "[quadtree]") {
    PNG img = solid(8, 6, RGBAPixel(200, 100, 50));
    QuadTree t(img);
    t.prune(0);
    REQUIRE(t.size() == 1);
    vector<Block> L = t.leaves();
    REQUIRE(L.size() == 1);
    REQUIRE(L[0].w == 8);
    REQUIRE(L[0].h == 6);
}

TEST_CASE("quadtree: prune keeps the blocks that are not one colour", "[quadtree]") {
    // left half black, right half white, 4x4
    PNG img = solid(4, 4, RGBAPixel(0, 0, 0));
    for (int y = 0; y < 4; y++)
        for (int x = 2; x < 4; x++) *img.getPixel(x, y) = RGBAPixel(255, 255, 255);
    QuadTree t(img);
    t.prune(0);
    // the root has error; each 2x2 quadrant is solid
    REQUIRE(t.size() == 5);
    vector<Block> L = t.leaves();
    REQUIRE(L.size() == 4);
    REQUIRE(L[0].stats.average() == RGBAPixel(0, 0, 0));       // NW
    REQUIRE(L[1].stats.average() == RGBAPixel(255, 255, 255)); // NE
}

// ---------------------------------------------------------------- crystals

TEST_CASE("crystals: two seeds split a two-colour image along the colours", "[crystals]") {
    PNG img = solid(6, 2, RGBAPixel(0, 0, 0));
    for (int y = 0; y < 2; y++)
        for (int x = 3; x < 6; x++) *img.getPixel(x, y) = RGBAPixel(255, 0, 0);
    vector<Seed> seeds = {{0, 0, RGBAPixel(0, 0, 0)}, {5, 1, RGBAPixel(255, 0, 0)}};
    Crystals c(img, seeds);
    c.grow();
    for (int y = 0; y < 2; y++)
        for (int x = 0; x < 6; x++) REQUIRE(c.owner(x, y) == (x < 3 ? 0 : 1));
}

TEST_CASE("crystals: seeds keep their own pixels; ties go to the smaller crystal", "[crystals]") {
    PNG img = solid(3, 1, RGBAPixel(50, 50, 50));
    // both seeds want the middle pixel at the same key; crystal 0 wins it
    vector<Seed> seeds = {{0, 0, RGBAPixel(50, 50, 50)}, {2, 0, RGBAPixel(50, 50, 50)}};
    Crystals c(img, seeds);
    c.grow();
    REQUIRE(c.owner(0, 0) == 0);
    REQUIRE(c.owner(1, 0) == 0);
    REQUIRE(c.owner(2, 0) == 1);
}

// ---------------------------------------------------------------- the whole thing

TEST_CASE("pa3: astronaut matches the solution image", "[whole]") {
    PNG img;
    img.readFromFile("eg_images/astronaut_300x300.png");
    QuadTree t(img);
    t.prune(1200000);
    vector<Seed> seeds = seedsFrom(img, t.leaves());
    REQUIRE(seeds.size() == 778);
    Crystals c(img, seeds);
    c.grow();
    PNG* out = render(img, c, 1, true, true);
    PNG soln;
    soln.readFromFile("soln_images/astronaut_crystals_1x.png");
    REQUIRE(*out == soln);
    delete out;
}
