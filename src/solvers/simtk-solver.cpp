/**
 * SimTK Equation Solver implementation
 *
 * \file simtk-solver.cpp
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
#include "eq-solver.hpp"
#include "solvers/simtk-solver.hpp"

using namespace cytoskelab.simtk;
using namespace SimTK;

CytoskelSubsystemImpl::CytoskelSubsystemImpl(APTR(SimTKSolver) isolver)
  : ForceSubsystem::Guts("Cytoskel", "1.0"), solver (isolver) 
{}

Subsystem::Guts* 
CytoskelSubsystemImpl::cloneImpl() const
{ return new CytoskelSubsystemImpl(); }

int
CytoskelSubsystemImpl::realizeSubsystemTopologyImpl(State& state) const
{}

int
CytoskelSubsystemImpl::realizeSubsystemDynamicsImpl(const State& state) const 
{}

Real
CytoskelSubsystemImpl::calcPotentialEnergy(const State& state) const 
{}

CytoskelSubsystem::CytoskelSubsystem (MultibodySystem& system)
{ 
  adoptSubsystemGuts(new CytoskelSubsystemImpl());
  system.addForceSubsystem(*this);
}
