/**
 * SimSystem class definition
 *
 * \file sim-system-impl.hpp
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

#ifndef __CYTOSKELAB_SIM_SYSTEM_IMPL__
#define __CYTOSKELAB_SIM_SYSTEM_IMPL__

namespace cytoskelab {

  template<int dim>
  void
  SimSystem<dim>::addGroup (ParticleGroup<dim>* group)
  { groups->push_back (APTR(ParticleGroup<dim>)(group)); }

  template<int dim>
  void
  SimSystem<dim>::addForce (Force<dim>* force)
  { forces->push_back (APTR(Force<dim>)(force)); }

  template<int dim>
  void
  SimSystem<dim>::addAction (Action<dim>* action)
  { actions->push_back (APTR(Action<dim>)(action)); }

  template<int dim>
  void
  SimSystem<dim>::init_ ()
  {
    groups = typename SimSystem<dim>::group_vec_ptr_t (new typename SimSystem<dim>::group_vec_t ());
    forces = typename SimSystem<dim>::force_vec_ptr_t (new typename SimSystem<dim>::force_vec_t ());
    actions = typename SimSystem<dim>::action_vec_ptr_t (new typename SimSystem<dim>::action_vec_t ());
  }

  template<int dim>
  void
  SimSystem<dim>::applyForces()
  {
    for (typename SimSystem<dim>::force_vec_t::iterator i = forces->begin ();
	 i != forces->end(); ++i)
    {
      for (typename SimSystem<dim>::group_vec_t::iterator j = groups->begin ();
	   j != groups->end(); ++j)
	(*i)->update (**j);
    }
  }

}; // cytoskelab

#endif // __CYTOSKELAB_SIM_SYSTEM_IMPL__
