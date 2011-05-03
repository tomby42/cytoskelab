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

#ifndef __CYTOSKELAB_SIMTK_SIM_SYSTEM__
#define __CYTOSKELAB_SIMTK_SIM_SYSTEM__

#include "SimTKsimbody.h"
#include "SimTKsimbody_aux.h"
#include "simbody/internal/ForceSubsystemGuts.h"

namespace cytoskelab {

  class SimTkSimSystem;

  class SimTkSimSystemImpl : public SimTK::ForceSubsystem::Guts {

  public:
    typedef boost::unordered_map<std::pair<int, int>, int> bmap_t;
    typedef boost::shared_ptr<bmap_t> bmap_ptr_t;

  private:
    mutable SimTK::DiscreteVariableIndex simSysIdx;
    mutable SimTK::DiscreteVariableIndex glueonsIdx;

  public:
    SimTkSimSystemImpl ();
    SimTK::Subsystem::Guts* cloneImpl() const;

    int realizeSubsystemTopologyImpl(SimTK::State& state) const;
    int realizeSubsystemDynamicsImpl(const SimTK::State& state) const;
    SimTK::Real calcPotentialEnergy(const SimTK::State& state) const;

    void setSimSystem(SimTK::State&, APTR(SimTkSimSystem));
    APTR(SimTkSimSystem) getSimSystem(const SimTK::State&) const;

  protected:
    void setGluons(SimTK::State&, bmap_ptr_t);
    bmap_ptr_t getGluons(const SimTK::State&) const;

  private:
    void init_props (const SimTK::State& state, SimTkSimSystem* simsys);
    void init_group (const SimTK::State& state, SimTkSimSystem* simsys, 
		     const APTR(ParticleGroup<3>)& pg);
    void comp_forces (const SimTK::State& state, SimTkSimSystem* simsys); 
    void update_forces (const SimTK::State& state, SimTkSimSystem* simsys,
			const APTR(ParticleGroup<3>)& pg, 
			SimTK::Vector_<SimTK::SpatialVec>& sforces);

  public:
    friend class SimTkSimSystem;
  };


  class SimTkSimSystem : public SimSystem<3>, public SimTK::ForceSubsystem {
  public:
    typedef SimTK::MultibodySystem* mbody_sys_ptr_t;
    typedef SimTK::SimbodyMatterSubsystem* sbody_sub_ptr_t;
    typedef SimTK::Array_<SimTK::Body::Rigid*> rbody_vec_t;
    typedef boost::shared_ptr<rbody_vec_t> rbody_vec_ptr_t;
    typedef SimTK::Array_<SimTK::MobilizedBody::Free*> mbody_vec_t;
    typedef boost::shared_ptr<mbody_vec_t> mbody_vec_ptr_t;
    typedef SimTK::RungeKuttaMersonIntegrator* rkmint_ptr_t;
    typedef SimTK::TimeStepper* ts_ptr_t;

  protected:
    mbody_sys_ptr_t system;
    sbody_sub_ptr_t matter;
    rbody_vec_ptr_t rbodies;
    mbody_vec_ptr_t mbodies;
    rkmint_ptr_t    integrator;
    ts_ptr_t	    ts;

  public:
    SimTkSimSystem (SimTK::MultibodySystem* system_, SimTK::SimbodyMatterSubsystem* matter_);
    
    virtual bool init ();
    virtual double sim (double t);
    virtual double updSys ();

    DEF_TTR(mbody_vec_ptr_t, mbodies);

  private:
    inline SimTkSimSystemImpl& updImpl()
    { return dynamic_cast<SimTkSimSystemImpl&>(updRep()); }
  
    const inline SimTkSimSystemImpl& getImpl() const
    { return dynamic_cast<const SimTkSimSystemImpl&>(getRep()); }

    void init_rbodies (const ParticleGroup<3>::particle_prop_vec_ptr_t& pp);
    void init_mbodies (const ParticleGroup<3>::particle_vec_ptr_t& p, int rb_start, SimTkSimSystemImpl::bmap_t* bmap);
  };

}; // cytoskelab

#endif // __CYTOSKELAB_SIMTK_SIM_SYSTEM__
