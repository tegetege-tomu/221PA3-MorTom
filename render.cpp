/**
 * @file render.cpp
 *
 * @author CS 221: Basic Algorithms and Data Structures
**/

#include "render.h"

PNG* render(const PNG& img, const Crystals& crystals, int scale, bool fill, bool lines) {
    int w = crystals.width(), h = crystals.height();

    // each crystal's average colour, over the pixels it claimed
    std::vector<Stats> totals(crystals.count());
    for (int y = 0; y < h; y++)
        for (int x = 0; x < w; x++) {
            int c = crystals.owner(x, y);
            if (c >= 0) totals[c].add(Stats(*img.getPixel(x, y)));
        }

    const RGBAPixel white(255, 255, 255), ink(35, 35, 35);
    PNG* out = new PNG(w * scale, h * scale);
    for (int Y = 0; Y < h * scale; Y++)
        for (int X = 0; X < w * scale; X++) {
            int c = crystals.owner(X / scale, Y / scale);
            bool edge = lines &&
                ((X > 0 && crystals.owner((X - 1) / scale, Y / scale) != c) ||
                 (Y > 0 && crystals.owner(X / scale, (Y - 1) / scale) != c));
            RGBAPixel* p = out->getPixel(X, Y);
            if (edge) *p = ink;
            else if (fill && c >= 0) *p = totals[c].average();
            else *p = white;
        }
    return out;
}
