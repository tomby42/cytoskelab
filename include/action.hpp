/**
 * Action class definition
 *
 * \file action.hpp
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

#ifndef __CYTOSKELAB_ACTION__
#define __CYTOSKELAB_ACTION__

namespace cytoskelab {

  template<int dim> class SimSystem;

  template<int dim>
  class Action : public Atom {
    DEF_ATOM (Action<dim>);

  public:
    virtual double act (SimSystem<dim>&) = 0;
  };

}; // cytoskelab

#endif // __CYTOSKELAB_ACTION__
