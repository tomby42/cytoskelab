/**
 * Main
 *
 * \file main.cpp
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

#include <iostream>
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

void
test ()
{
  ParticleGroup<3>* pg = new ParticleGroup<3> (1);

  ParticleGroup<3>::ParticleProp& pp = pg->allocParticleProp ();
  ParticleGroup<3>::mat_t iner;
  iner = 1, 0, 0,
    0, 1, 0,
    0, 0, 1;

  SETTr (pp, mass, 1.);
  SETTr (pp, inertia,  iner);

  pg->preAllocParticles (3);
  ParticleGroup<3>::Particle& p1 = pg->allocParticle ();
  SETTr (p1, ppid, GETTr (pp, ppid));
  SETTr (p1, pos, ParticleGroup<3>::vec_t (0, 0, 0));
  SETTr (p1, ptype, ParticleGroup<3>::BOUNDARY);

  ParticleGroup<3>::Particle& p2 = pg->allocParticle ();
  SETTr (p2, ppid, GETTr (pp, ppid));
  SETTr (p2, pos, ParticleGroup<3>::vec_t (1.5, 0, 0));
  SETTr (p2, ptype, ParticleGroup<3>::BOUNDARY);

  ParticleGroup<3>::Particle& p3 = pg->allocParticle ();
  SETTr (p3, ppid, GETTr (pp, ppid));
  SETTr (p3, pos, ParticleGroup<3>::vec_t (0, 1.5, 0));
  SETTr (p3, ptype, ParticleGroup<3>::BOUNDARY);

  ParticleGroup<3>::ConnectionProp& cp = pg->allocConnectionProp ();
  ParticleGroup<3>::Connection& c1 = pg->allocConnection ();
  
  SETTr (cp, springConst, 0.5);
  SETTr (cp, restLength, 1.);
  SETTr (cp, viscosityConst, .25);

  SETTr (c1, cpid, GETTr (cp, cpid));
  SETTr (c1, gid1, -1);
  SETTr (c1, pid1, GETTr (p1, pid));
  SETTr (c1, gid2, -1);
  SETTr (c1, pid2, GETTr (p2, pid));
  SETTr (c1, ptype, ParticleGroup<3>::BOUNDARY);
  
  ParticleGroup<3>::Connection& c2 = pg->allocConnection ();
  SETTr (c2, cpid, GETTr (cp, cpid));
  SETTr (c2, gid1, -1);
  SETTr (c2, pid1, GETTr (p1, pid));
  SETTr (c2, gid2, -1);
  SETTr (c2, pid2, GETTr (p3, pid));
  SETTr (c2, ptype, ParticleGroup<3>::BOUNDARY);

  ParticleGroup<3>::Connection& c3 = pg->allocConnection ();
  SETTr (c3, cpid, GETTr (cp, cpid));
  SETTr (c3, gid1, -1);
  SETTr (c3, pid1, GETTr (p2, pid));
  SETTr (c3, gid2, -1);
  SETTr (c3, pid2, GETTr (p3, pid));
  SETTr (c3, ptype, ParticleGroup<3>::BOUNDARY);


  Voigt<3>*  vg = new Voigt<3>;
  //vg.update (pg);

  SimTK::MultibodySystem* system = new SimTK::MultibodySystem ();
  SimTK::SimbodyMatterSubsystem* matter = new SimTK::SimbodyMatterSubsystem(*system);
  SimTkSimSystem sts (system, matter);

  sts.addGroup (pg);
  sts.addForce (vg);
  sts.init ();
  sts.sim (50.);
}

int main (int argc, char** argv)
{       
  std::cout << "CYTOSKELAB ver. 0.1 alpha \n";
  std::cout << "BOOTING...\n";

  test ();

  std::cout << "...BOOT SUCCESFULL\n";

  return 0;
} 
