/**
 * SimTK Equation Solver definition
 *
 * \file simtk-solver.hpp
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

#ifndef __CYTOSKELAB_SIM_TK_SOLVER__
#define __CYTOSKELAB_SIM_TK_SOLVER__

#include "SimTKsimbody.h"
#include "simbody/internal/ForceSubsystemGuts.h"

using namespace SimTK;

namespace cytoskelab {
  namespace simtk {

    class SimTKSolver : public EqSolver {
    public:
      DEF_ATOM(SimTKSolver);
    };

    class CytoskelSubsystemImpl : public SimTK.ForceSubsystem::Guts {
      
      APTR(SimTKSolver) solver;
      
    public:
      
      CytoskelSubsystemImpl(APTR (SimTKSolver));
      Subsystem::Guts* cloneImpl() const;
      int realizeSubsystemTopologyImpl(State& state) const;
      int realizeSubsystemDynamicsImpl(const State& state) const;
      Real calcPotentialEnergy(const State& state) const;
      
    };
    
    class CytoskelSubsystem : public ForceSubsystem {
    public:
      CytoskelSubsystem (MultibodySystem& system);
      
    private:
      inline CytoskelSubsystemImpl& updImpl() 
      { return dynamic_cast<CytoskelSubsystemImpl&>(updRep()); }
      
      const inline CytoskelSubsystemImpl& getImpl() const 
      { return dynamic_cast<const CytoskelSubsystemImpl&>(getRep()); }
    };
  
  }; // simtk  
}; // cytoskelab
  
#endif
