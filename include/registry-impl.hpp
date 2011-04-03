/**
 * Registry implementation
 *
 * \file registry-impl.hpp
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

#ifndef __CYTOSKELAB_REGISTRY_IMPL__
#define __CYTOSKELAB_REGISTRY_IMPL__

namespace cytoskelab {

  template<typename desc_t>
  Registry<desc_t>::Registry ()
    : id_cnt (0)
  { registry = typename Registry<desc_t>::map_ptr_t (new typename Registry<desc_t>::map ()); }

  template<typename desc_t>
  Registry<desc_t>::~Registry ()
  {}

  template<typename desc_t>
  typename Registry<desc_t>::twin_t
  Registry<desc_t>::reg (desc_t* name)
  {
    id_t id = id_cnt++;
    
    (*registry) [*name] = id;
    
    return Registry<desc_t>::twin_t (*name, id);
  }

}; // cytoskelab

#endif
