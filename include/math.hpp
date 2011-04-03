/**
 * Math routines definition
 *
 * \file math.hpp
 * \author tomby
 * \date 04-01-2009
 **/

/*  Copyright (C) 2009  Tomas 'tomby' Bily

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>. */

#ifndef __CYTOSKELAB_MATH__
#define __CYTOSKELAB_MATH__

// @todo Solve it for non gnu compilers
#include <ext/numeric>

namespace cytoskelab {

  inline int power (int x, int pow)
  { return __gnu_cxx::power (x, pow); }

}; // namespace cytoskelab

#endif
