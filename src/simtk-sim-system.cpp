/**
 * SimTkSimSystem class definition
 *
 * \file simtk-sim-system.hpp
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

#include "cytoskelab-sys.hpp"

#include "particle-group.hpp"
#include "particle-group-impl.hpp"

#include "force.hpp"
#include "force-impl.hpp"

#include "action.hpp"

#include "sim-system.hpp"
#include "sim-system-impl.hpp"

#include "simtk-sim-system.hpp"

using namespace cytoskelab;

SimTkSimSystemImpl::SimTkSimSystemImpl()
  : SimTK::ForceSubsystem::Guts("SimTkSimSystem", "1.0")
{}

SimTK::Subsystem::Guts*
SimTkSimSystemImpl::cloneImpl() const
{ return new SimTkSimSystemImpl(); }

int
SimTkSimSystemImpl::realizeSubsystemTopologyImpl(SimTK::State& state) const
{
  simSysIdx = allocateDiscreteVariable(state, SimTK::Stage::Dynamics,
				       new SimTK::Value<APTR(SimTkSimSystem)>());

  
  glueonsIdx = allocateDiscreteVariable(state, SimTK::Stage::Dynamics,
					new SimTK::Value<SimTkSimSystemImpl::bmap_ptr_t>(bmap_ptr_t (new SimTkSimSystemImpl::bmap_t)));
  return 0;
}

int
SimTkSimSystemImpl::realizeSubsystemDynamicsImpl(const SimTK::State& state) const
{
  APTR(SimTkSimSystem) simsys (getSimSystem (state));
  const_cast<SimTkSimSystemImpl*> (this)->init_props (state, const_cast<SimTkSimSystem*> (&(*simsys)));
  const_cast<SimTkSimSystemImpl*> (this)->comp_forces (state, const_cast<SimTkSimSystem*> (&(*simsys)));

  return 0;
}

void
SimTkSimSystemImpl::init_props (const SimTK::State& state, SimTkSimSystem* simsys) 
{
  const SimSystem<3>::group_vec_ptr_t groups = GETTR (simsys, groups);

  for (SimSystem<3>::group_vec_t::iterator i = groups->begin ();
       i != groups->end(); ++i)
    init_group (state, simsys, *i);
}

void
SimTkSimSystemImpl::comp_forces (const SimTK::State& state, SimTkSimSystem* simsys)
{
  const SimTK::MultibodySystem& system = SimTK::MultibodySystem::downcast(getSystem());
  // const SimTK::SimbodyMatterSubsystem& matter = system.getMatterSubsystem();
  SimTK::Vector_<SimTK::SpatialVec>& sforces = 
    system.updRigidBodyForces(state, SimTK::Stage::Dynamics);

  simsys->applyForces ();

  const SimSystem<3>::group_vec_ptr_t groups = GETTR (simsys, groups);
  for (SimSystem<3>::group_vec_t::iterator i = groups->begin ();
       i != groups->end(); ++i)
    update_forces (state, simsys, *i, sforces);
}

void
SimTkSimSystemImpl::update_forces 
(const SimTK::State& state, SimTkSimSystem* simsys,
 const APTR(ParticleGroup<3>)& pg, 
 SimTK::Vector_<SimTK::SpatialVec>& sforces)
{
  SimTkSimSystemImpl::bmap_ptr_t bmap = getGluons (state);
  const ParticleGroup<3>::particle_vec_ptr_t& p = GETTR (pg, particles);
  const SimTkSimSystem::mbody_vec_ptr_t& mbodies = GETTR (simsys, mbodies);

  for (ParticleGroup<3>::particle_vec_t::iterator i = p->begin ();
       i != p->end (); ++i)
    {
      const SimTK::MobilizedBody::Free* fb = (*mbodies)[(*bmap)[std::pair<int,int>(GETTr (*i, gid), GETTr (*i, pid))]];
      SimTK::MobilizedBodyIndex j = fb->getMobilizedBodyIndex();
      ParticleGroup<3>::vec_t f = GETTr (*i, Facc);
      sforces[j][1] += SimTK::Vec3 (f(0), f(1), f(2));
    }
}

void
SimTkSimSystemImpl::init_group 
(const SimTK::State& state, SimTkSimSystem* simsys, 
 const APTR(ParticleGroup<3>)& pg)
{
  SimTkSimSystemImpl::bmap_ptr_t bmap = getGluons (state);
  const SimTkSimSystem::mbody_vec_ptr_t& mbodies = GETTR (simsys, mbodies);
  const ParticleGroup<3>::particle_vec_ptr_t& p = GETTR (pg, particles);  

  for (ParticleGroup<3>::particle_vec_t::iterator i = p->begin ();
       i != p->end (); ++i)
    {
      const SimTK::MobilizedBody::Free* fb = (*mbodies)[(*bmap)[std::pair<int,int>(GETTr (*i, gid), GETTr (*i, pid))]];
      SimTK::Vec3 pos = fb->getBodyOriginLocation(state);
      SimTK::Vec3 vel = fb->getBodyOriginVelocity(state);
      SETTr (*i, Facc, ParticleGroup<3>::vec_t (0.));
      SETTr (*i, pos, ParticleGroup<3>::vec_t (pos[0], pos[1], pos[2]));
      SETTr (*i, vel, ParticleGroup<3>::vec_t (vel[0], vel[1], vel[2]));
    }
}

SimTK::Real
SimTkSimSystemImpl::calcPotentialEnergy(const SimTK::State& state) const
{ return 0.; }

void
SimTkSimSystemImpl::setSimSystem(SimTK::State& state, APTR(SimTkSimSystem) s)
{
  SimTK::Value<APTR(SimTkSimSystem)>::updDowncast(updDiscreteVariable(state,
								      simSysIdx)) = s;
}

APTR(SimTkSimSystem)
SimTkSimSystemImpl::getSimSystem(const SimTK::State& state) const
{
  return SimTK::Value<APTR(SimTkSimSystem)>::downcast(getDiscreteVariable(state,
									  simSysIdx));
}

void
SimTkSimSystemImpl::setGluons(SimTK::State& state, SimTkSimSystemImpl::bmap_ptr_t g)
{
  SimTK::Value<SimTkSimSystemImpl::bmap_ptr_t>::updDowncast(updDiscreteVariable(state,
										glueonsIdx)) = g;
}

SimTkSimSystemImpl::bmap_ptr_t
SimTkSimSystemImpl::getGluons(const SimTK::State& state) const
{
  return SimTK::Value<SimTkSimSystemImpl::bmap_ptr_t>::downcast(getDiscreteVariable(state,
										    glueonsIdx));
}

/// 

SimTkSimSystem::SimTkSimSystem (SimTK::MultibodySystem* system_, SimTK::SimbodyMatterSubsystem* matter_)
{
  init_ ();
  system = mbody_sys_ptr_t (system_);
  matter = sbody_sub_ptr_t (matter_);
  adoptSubsystemGuts(new SimTkSimSystemImpl());
  system->addForceSubsystem(*this);
}

bool
SimTkSimSystem::init()
{
  system->updDefaultSubsystem().addEventReporter(new SimTK::VTKEventReporter(*system, 0.01));

  int start = 0;
  rbodies = rbody_vec_ptr_t (new rbody_vec_t ());
  mbodies = mbody_vec_ptr_t (new mbody_vec_t ());
  SimTkSimSystemImpl::bmap_t* bmap = new SimTkSimSystemImpl::bmap_t ();

  for (ParticleGroup<3>::group_vec_t::iterator i = groups->begin();
       i != groups->end(); ++i)
    {
      const ParticleGroup<3>::particle_prop_vec_ptr_t& pp = GETTR (*i, particlesProp);
      const ParticleGroup<3>::particle_vec_ptr_t& p = GETTR (*i, particles);
      start = rbodies->size ();
      init_rbodies (pp);
      init_mbodies (p, start, bmap);
    }

  system->realizeTopology();
  SimTK::State state = system->getDefaultState();
  updImpl().setSimSystem (state, APTR(SimTkSimSystem) (this));
  updImpl().setGluons (state, SimTkSimSystemImpl::bmap_ptr_t (bmap));

  integrator = SimTkSimSystem::rkmint_ptr_t (new SimTK::RungeKuttaMersonIntegrator (*system));
  ts = SimTkSimSystem::ts_ptr_t (new SimTK::TimeStepper (*system, *integrator));
  ts->initialize (state);

  return true;
}

void
SimTkSimSystem::init_rbodies (const ParticleGroup<3>::particle_prop_vec_ptr_t& pp)
{
  for (ParticleGroup<3>::particle_prop_vec_t::iterator i = pp->begin ();
       i != pp->end (); ++i)
    {
      // const ParticleGroup<3>::mat_t& inertia = GETTr (*i, inertia);
      const ParticleGroup<3>::vec_t& center = GETTr (*i, center);
      int mass = GETTr (*i, mass);
      /*SimTK::Mat33P m (inertia(0,0), inertia(1,0), inertia(2,0),
		       inertia(0,1), inertia(1,1), inertia(2,1),
		       inertia(0,2), inertia(1,2), inertia(2,2));*/
      SimTK::Body::Rigid* b = new SimTK::Body::Rigid (SimTK::MassProperties
			    (mass, SimTK::Vec3 (center(0), center(1), center(2)), 
			     SimTK::Inertia (1.)));
      b->addDecoration(SimTK::Transform(), SimTK::DecorativeSphere(0.1));
      rbodies->push_back (b);
    }
}

void
SimTkSimSystem::init_mbodies (const ParticleGroup<3>::particle_vec_ptr_t& p, int rb_start, SimTkSimSystemImpl::bmap_t* bmap)
{
  for (ParticleGroup<3>::particle_vec_t::iterator i = p->begin ();
       i != p->end (); ++i) 
    {
      SimTK::Body::Rigid* rb = (*rbodies)[rb_start + GETTr (*i, ppid)];
      SimTK::MobilizedBody::Free* fb = new SimTK::MobilizedBody::Free (matter->Ground (), *rb);
      const ParticleGroup<3>::vec_t& pos = GETTr (*i, pos);
      fb->setDefaultTranslation (SimTK::Vec3 (pos(0), pos(1), pos(2)));
      (*bmap)[std::pair<int,int>(GETTr (*i, gid), GETTr (*i, pid))] = mbodies->size ();
      mbodies->push_back (fb);
    }
}

double
SimTkSimSystem::sim (double t)
{
  ts->stepTo(t);

  return t; 
}

double
SimTkSimSystem::updSys ()
{ return 0.; }
