/**
 * @file RGBAPixel.cpp
 * Implementation of the RGBAPixel class for use in with the PNG library.
 *
 * @author CS 225: Data Structures
 * @version 2018r1
 * 
 * Color difference functions adapted from pam.h (copyright notice below)
 * 
 * Copyright (C) 1989, 1991 by Jef Poskanzer.
 * Copyright (C) 1997 by Greg Roelofs.
 * 
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for any purpose and without fee is hereby granted, provided
 * that the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation.  This software is provided "as is" without express or
 * implied warranty.
 */

#include "RGBAPixel.h"
#include <cmath>
#include <iostream>
using namespace std;

namespace cs221util {
  RGBAPixel::RGBAPixel() {
    r = 0;
    g = 0;
    b = 0;
    a = 1.0;
  }

  RGBAPixel::RGBAPixel(int red, int green, int blue){
    r = red;
    g = green;
    b = blue;
    a = 1.0;
  }
  RGBAPixel::RGBAPixel(int red, int green, int blue, double alpha){
    r = red;
    g = green;
    b = blue;
    a = alpha;
  }

  void RGBAPixel::copy(const RGBAPixel& p){
    r = p.r;
    g = p.g;
    b = p.b;
    a = p.a;
  }


  //RGBAPixel & RGBAPixel::operator=(RGBAPixel const & other) {
  //  this->r = other.r;
  //  this->g = other.g;
  //  this->b = other.b;
  //  this->a = other.a;
  //  return *this;
  //}

  bool RGBAPixel::operator== (RGBAPixel const & other) const {
    // thank/blame Wade for the following function
    // adapted by cinda to allow for slight deviations in RGB

    if ( a == 0 ) { return true; }
    if (fabs(a - other.a) > 0.01) { return false; }

    if (fabs(r - other.r) > 2) { return false; } 
    if (fabs(g - other.g) > 2) { return false; } 
    if (fabs(b - other.b) > 2) { return false; } 

    return true;
}

  bool RGBAPixel::operator!= (RGBAPixel const & other) const {
    return !(*this == other);
  }

  bool RGBAPixel::operator<  (RGBAPixel const & other) const {
    // Cinda is not sure where this is used. Fairly arb total
    // order is reflected here. R->G->B.
      if (*this == other) { return false; }

      if (r < other.r)
          return true;
      else if ((r == other.r) && (g < other.g))
          return true;
      else if ((r == other.r) && (g == other.g) && (b < other.b))
          return true;

      return false;
  }

  std::ostream & operator<<(std::ostream & out, RGBAPixel const & pixel) {
    out << "(" << (int)pixel.r << ", " << (int)pixel.g << ", " << (int)pixel.b << (pixel.a != 1 ? ", " + std::to_string(pixel.a) : "") << ")";

    return out;
  }


}
