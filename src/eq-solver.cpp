/**
 * Equation solver implementation
 *
 * \file eq-solver.cpp
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

#include "registry.hpp"
#include "registry-impl.hpp"
#include "eq-solver.hpp"

using namespace cytoskelab;

EqInstance::EqInstance ()
  : Atom ()
{}

EqInstance::~EqInstance ()
{}

/******************************************************************************/

EqSolverReg::EqSolverReg ()
  : Atom ()
{
  eq_reg = new Registry<std::string> ();
  group_reg = new Registry<EqId> ();
  groups = vec_grp_p_t (new vec_grp_t ());
}

EqSolverReg::~EqSolverReg ()
{}
