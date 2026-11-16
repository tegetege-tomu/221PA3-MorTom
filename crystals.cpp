/**
 * @file crystals.cpp
 *
 * @author CS 221: Basic Algorithms and Data Structures
**/

#include "crystals.h"
#include "heap.h"

std::vector<Seed> seedsFrom(const PNG& img, const std::vector<Block>& blocks) {
    std::vector<Seed> seeds;
    for (const Block& b : blocks) {
        int x = b.x + b.w / 2, y = b.y + b.h / 2;
        seeds.push_back(Seed{x, y, *img.getPixel(x, y)});
    }
    return seeds;
}

long colourDist2(const RGBAPixel& a, const RGBAPixel& b) {
    long dr = (long) a.r - b.r, dg = (long) a.g - b.g, db = (long) a.b - b.b;
    return dr * dr + dg * dg + db * db;
}

bool operator<(const Frontier& a, const Frontier& b) {
    // Your code here
    return false;   // replace this line
}

Crystals::Crystals(const PNG& img, const std::vector<Seed>& seeds)
    : img_(img), seeds_(seeds), width_(img.width()), height_(img.height()),
      owner_(img.width() * img.height(), -1) {}

int Crystals::owner(int x, int y) const {
    return owner_[y * width_ + x];
}

void Crystals::grow() {
    // Your code here
}
