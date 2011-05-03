/**
 * SimSystem class definition
 *
 * \file sim-system.hpp
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

#ifndef __CYTOSKELAB_SIM_SYSTEM__
#define __CYTOSKELAB_SIM_SYSTEM__

namespace cytoskelab {

  template<int dim>
  class SimSystem : public Atom {
    DEF_ATOM (SimSystem<dim>);

  public:
    typedef std::vector<APTR(ParticleGroup<dim>)> group_vec_t;
    typedef std::vector<APTR(Force<dim>)> force_vec_t;
    typedef std::vector<APTR(Action<dim>)> action_vec_t;

    typedef boost::shared_ptr<group_vec_t> group_vec_ptr_t;
    typedef boost::shared_ptr<force_vec_t> force_vec_ptr_t;
    typedef boost::shared_ptr<action_vec_t> action_vec_ptr_t;

  protected:
    group_vec_ptr_t groups;
    force_vec_ptr_t forces;
    action_vec_ptr_t actions;

  public:

    virtual bool init () = 0;
    virtual double sim (double t) = 0;
    virtual double updSys () = 0;

    void addGroup (ParticleGroup<dim>* group);
    void addForce (Force<dim>* force);
    void addAction (Action<dim>* action);
    void applyForces ();
    
    DEF_TTR(group_vec_ptr_t, groups);
    DEF_TTR(force_vec_ptr_t, forces);
    DEF_TTR(action_vec_ptr_t, actions);

  protected:
    void init_ ();
  };

}; // cytoskelab

#endif // __CYTOSKELAB_SIM_SYSTEM__
