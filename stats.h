/**
 * @file stats.h
 *
 * Colour totals for a block of pixels. Two blocks' totals combine by adding,
 * so a quadtree node's Stats is the sum of its children's.
 *
 * @author CS 221: Basic Algorithms and Data Structures
**/

#ifndef STATS_H
#define STATS_H

#include "cs221util/RGBAPixel.h"

using namespace cs221util;

class Stats {
public:
    long n = 0;                  // number of pixels
    long r = 0, g = 0, b = 0;    // sums of each channel
    long rr = 0, gg = 0, bb = 0; // sums of the squares of each channel's values

    Stats() {}

    /** Totals for a single pixel. */
    explicit Stats(const RGBAPixel& p);

    /** Adds another block's totals to these. */
    void add(const Stats& other);

    /**
     * Total squared colour error: the sum, over every pixel and channel, of
     * (value - channel mean)^2. Equivalently, variance times area. A block of
     * one colour has error 0.
     */
    double error() const;

    /** The block's average colour, each channel rounded to the nearest int. */
    RGBAPixel average() const;
};

#endif
