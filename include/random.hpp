/**
 * Global random generators def
 *
 * \file random.hpp
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

#ifndef __CYTOSKELAB_RANDOM__
#define __CYTOSKELAB_RANDOM__

#include <boost/random.hpp>
#include "blitz-helper.hpp"

namespace cytoskelab {

  typedef boost::mt19937 base_generator_type;

  extern base_generator_type global_generator;

  template<int dim>
  class RandomPointGen
  {
  public:
    typedef blitz::TinyVector<int, dim> IndexType;
    typedef blitz::TinyVector<boost::uniform_int<>, dim> UniformVector;
    typedef blitz::TinyVector<boost::variate_generator<base_generator_type&, boost::uniform_int<> >, dim> UrnVector;

  protected:
    UniformVector un;
    UrnVector urns;

  public:
    RandomPointGen (blitz::RectDomain<dim>& boundary)
    {
      for (int i = 0; i < dim; ++i)
	{
	  un [i] = boost::uniform_int<> (boundary.lbound () [i], boundary.ubound () [i]);
	  urns [i] = boost::variate_generator<base_generator_type&, boost::uniform_int<> > (global_generator, un [i]);
	}
    }

    IndexType operator() ()
    {
      IndexType p;

      for (int i = 0; i < dim; ++i)
	p [i] = urns [i] ();

      return p;
    }
  };
}; // namespace cytoskelab

#endif
