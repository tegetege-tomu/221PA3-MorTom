/**
 * @file render.h
 *
 * Draws grown crystals as an image.
 *
 * @author CS 221: Basic Algorithms and Data Structures
**/

#ifndef RENDER_H
#define RENDER_H

#include "cs221util/PNG.h"
#include "crystals.h"

using namespace cs221util;

/**
 * Returns a new image, scale times the size of img. Each crystal is filled
 * with the average colour of the pixels it claimed (or left white, if fill is
 * false), and the edges between crystals are drawn as 1-pixel dark lines (if
 * lines is true). The caller deletes the result.
 */
PNG* render(const PNG& img, const Crystals& crystals, int scale, bool fill, bool lines);

#endif
