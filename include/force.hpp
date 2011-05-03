/**
 * Force classes definition
 *
 * \file force.hpp
 * \author tomby
 * \date 27-11-2010
 **/

/*  Copyright (C) 2010  Tomas 'tomby' Bily

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

#ifndef __CYTOSKELAB_FORCE__
#define __CYTOSKELAB_FORCE__

namespace cytoskelab {

  template<int dim>
  class Force : public Atom {
    DEF_ATOM (Force<dim>);

  public:
    
    virtual bool update (ParticleGroup<dim>&) = 0;
  };

  template<int dim>
  class Voigt : public Force<dim> {
    DEF_ATOM (Voigt<dim>);

  public:

    virtual bool update (ParticleGroup<dim>&);
  };

}; // cytoskelab


#endif
