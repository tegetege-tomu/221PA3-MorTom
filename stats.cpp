/**
 * @file stats.cpp
 *
 * @author CS 221: Basic Algorithms and Data Structures
**/

#include "stats.h"

Stats::Stats(const RGBAPixel& p)
    : n(1), r(p.r), g(p.g), b(p.b), rr(p.r * p.r), gg(p.g * p.g), bb(p.b * p.b) {}

void Stats::add(const Stats& other) {
    n += other.n;
    r += other.r;   g += other.g;   b += other.b;
    rr += other.rr; gg += other.gg; bb += other.bb;
}

double Stats::error() const {
    if (n == 0) return 0;
    double dn = n;
    return (rr - r * (double) r / dn) + (gg - g * (double) g / dn) + (bb - b * (double) b / dn);
}

RGBAPixel Stats::average() const {
    if (n == 0) return RGBAPixel();
    return RGBAPixel((r + n / 2) / n, (g + n / 2) / n, (b + n / 2) / n);
}
