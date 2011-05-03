/**
 * Force classes definition
 *
 * \file force-impl.hpp
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

#ifndef __CYTOSKELAB_FORCE_IMPL__
#define __CYTOSKELAB_FORCE_IMPL__

namespace cytoskelab {

  template<int dim>
  bool
  Voigt<dim>::update (ParticleGroup<dim>& pg)
  {
    const typename ParticleGroup<dim>::connection_vec_ptr_t& connections = GETTr (pg, connections);

    for (typename ParticleGroup<dim>::connection_vec_t::iterator i = connections->begin ();
	 i < connections->end (); ++i)
      {
	typename ParticleGroup<dim>::Connection&  c = *i;
	typename ParticleGroup<dim>::ConnectionProp& cp = (*GETTr (pg, connectionsProp)) [GETTr (c, cpid)];
	typename ParticleGroup<dim>::Particle& p1 = pg.getParticle (GETTr (c, gid1), GETTr (c, pid1));
	typename ParticleGroup<dim>::Particle& p2 = pg.getParticle (GETTr (c, gid2), GETTr (c, pid2));
	
	typename ParticleGroup<dim>::vec_t r = GETTr (p1, pos) - GETTr (p2, pos);
	typename ParticleGroup<dim>::vec_t u = GETTr (p1, vel) - GETTr (p2, vel);

	double dist = sqrt (blitz::dot (r, r));

	if (fabs (dist) < 1e-15)
	  continue;
	
	double fp = GETTr (cp, springConst) * ((dist - GETTr (cp, restLength)) / dist);
	typename ParticleGroup<dim>::vec_t f = - fp * r 
	  - GETTr (cp, viscosityConst) * u;

	SETTr (p1, Facc, GETTr (p1, Facc) + f + GETTr (p1, Fext));
	SETTr (p2, Facc, GETTr (p2, Facc) - f + GETTr (p2, Fext));
      }

    return true;
  }

}; // cytoskelab

#endif
