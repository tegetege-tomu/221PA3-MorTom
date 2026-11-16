/**
 * @file crystals.h
 *
 * Grows one crystal from every seed at once. Crystal i grows from seeds[i].
 * The frontier is a priority queue of pixels that touch a crystal but are not
 * yet claimed; the pixel that best matches the crystal reaching for it is
 * claimed next, anywhere in the image.
 *
 * @author CS 221: Basic Algorithms and Data Structures
**/

#ifndef CRYSTALS_H
#define CRYSTALS_H

#include <vector>
#include "cs221util/PNG.h"
#include "quadtree.h"

using namespace cs221util;

/** Where a crystal starts, and the colour it grows toward. */
struct Seed {
    int x, y;
    RGBAPixel colour;
};

/**
 * One seed per block, at the block's centre pixel (x + w/2, y + h/2), with
 * that pixel's colour.
 */
std::vector<Seed> seedsFrom(const PNG& img, const std::vector<Block>& blocks);

/** Squared distance between two colours: dr^2 + dg^2 + db^2. Alpha is ignored. */
long colourDist2(const RGBAPixel& a, const RGBAPixel& b);

/** A pixel on the frontier: crystal wants to claim pixel, at cost key. */
struct Frontier {
    long key;      // colourDist2(the pixel, the crystal's seed colour)
    int pixel;     // y * width + x
    int crystal;   // index into the seeds
};

/**
 * The order of the frontier: a < b when a should come out of the frontier
 * first. Smaller key first; for equal keys, smaller pixel first; for equal
 * keys and pixels, smaller crystal first.
 */
bool operator<(const Frontier& a, const Frontier& b);

class Crystals {
public:
    /**
     * Sets up crystals for img, one per seed. Nothing is claimed yet.
     * No two seeds are at the same pixel (seedsFrom guarantees this).
     */
    Crystals(const PNG& img, const std::vector<Seed>& seeds);

    /**
     * Claims every pixel of the image for some crystal.
     *
     * First, every seed claims its own pixel. Then each seed, from seeds[0]
     * upward, puts its pixel's unclaimed 4-neighbours (up, down, left, right)
     * on the frontier. Then, until the frontier is empty: take the first entry
     * out of the frontier; if its pixel is already claimed, skip it; otherwise
     * give the pixel to that entry's crystal and put the pixel's unclaimed
     * 4-neighbours on the frontier for the same crystal.
     *
     * A neighbour's key is colourDist2(the neighbour, the crystal's seed colour).
     */
    void grow();

    /** The crystal that owns (x, y), or -1 if it is unclaimed. */
    int owner(int x, int y) const;

    int width() const { return width_; }
    int height() const { return height_; }
    int count() const { return seeds_.size(); }

private:
    const PNG& img_;
    std::vector<Seed> seeds_;
    int width_, height_;
    std::vector<int> owner_;   // owner_[y * width_ + x]; -1 means unclaimed
};

#endif
