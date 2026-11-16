/**
 * @file main.cpp
 *
 * Usage:
 *   ./pa3                                   the examples below
 *   ./pa3 in.png out.png tol [scale] [lines]
 *
 * tol is the pruning tolerance: larger means fewer, bigger crystals. Try
 * values around a million, then adjust. The number of crystals
 * is printed. Add "lines" to draw only the edges, colouring-book style.
 *
 * @author CS 221: Basic Algorithms and Data Structures
**/

#include <cstdlib>
#include <iostream>
#include <string>
#include "cs221util/PNG.h"
#include "quadtree.h"
#include "crystals.h"
#include "render.h"

using namespace cs221util;
using namespace std;

/** Crystallizes in_file into out_file, and returns the number of crystals. */
int crystallize(string in_file, string out_file, double tol, int scale, bool fill) {
    PNG img;
    if (!img.readFromFile(in_file)) {
        cerr << "could not read " << in_file << endl;
        return 0;
    }
    QuadTree tree(img);
    tree.prune(tol);
    vector<Seed> seeds = seedsFrom(img, tree.leaves());

    Crystals crystals(img, seeds);
    crystals.grow();

    PNG* out = render(img, crystals, scale, fill, true);
    out->writeToFile(out_file);
    delete out;
    return seeds.size();
}

int main(int argc, char* argv[]) {
    if (argc >= 4) {
        int scale = argc >= 5 ? atoi(argv[4]) : 1;
        bool fill = !(argc >= 6 && string(argv[5]) == "lines");
        int n = crystallize(argv[1], argv[2], atof(argv[3]), scale, fill);
        cout << argv[2] << ": " << n << " crystals" << endl;
        return 0;
    }
    if (argc != 1) {
        cerr << "usage: " << argv[0] << " [in.png out.png tol [scale] [lines]]" << endl;
        return 1;
    }

    // the examples
    struct { string in, out; double tol; int scale; bool fill; } eg[] = {
        {"eg_images/astronaut_300x300.png", "eg_outs/astronaut_crystals.png", 1200000, 3, true},
        {"eg_images/astronaut_300x300.png", "eg_outs/astronaut_lines.png",    1200000, 3, false},
        {"eg_images/astronaut_300x300.png", "eg_outs/astronaut_fewer.png",    4000000, 3, true},
        {"eg_images/maple_800x600.png",     "eg_outs/maple_crystals.png",     6000000, 1, true},
        {"eg_images/pumpkins_800x533.png",  "eg_outs/pumpkins_crystals.png",  3000000, 1, true},
        {"eg_images/ballpark_800x600.png",  "eg_outs/ballpark_crystals.png",  3500000, 1, true},
    };
    for (auto& e : eg) {
        int n = crystallize(e.in, e.out, e.tol, e.scale, e.fill);
        cout << e.out << ": " << n << " crystals" << endl;
    }
    return 0;
}
