/**
 * ParticleGroup & co. classes definition
 *
 * \file particle-group.hpp
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

#ifndef __CYTOSKELAB_PARTICLE_GROUP_IMPL__
#define __CYTOSKELAB_PARTICLE_GROUP_IMPL__

namespace cytoskelab {

  template<int dim>
  ParticleGroup<dim>::ParticleProp::ParticleProp
  (int ppid_, double mass_, vec_t& center_, mat_t& inertia_)
    : ppid (ppid), mass (mass_), center (center_), inertia (inertia_)
  {}

  template<int dim>
  ParticleGroup<dim>::ParticleProp::ParticleProp
  ()
    : ppid (-1), mass (0.), center (0.)
  { inertia.initialize (0); }

  template<int dim>
  ParticleGroup<dim>::Particle::Particle
  (int pid_, int gid_, int ppid_, vec_t& pos_, vec_t& vel_, 
   vec_t& Fext_, vec_t& Facc_, PositionType ptype_)
    : pid (pid_), gid (gid_), ppid (ppid_), pos (pos_), vel (vel_), Fext (Fext_), Facc (Facc_) ,ptype (ptype_)
  {}

  template<int dim>
  ParticleGroup<dim>::Particle::Particle
  ()
    : pid (-1), gid (-1), ppid (-1), 
      pos (typename ParticleGroup<dim>::vec_t (0.)), 
      vel (typename ParticleGroup<dim>::vec_t (0.)), 
      Fext (typename ParticleGroup<dim>::vec_t (0.)), 
      Facc (typename ParticleGroup<dim>::vec_t (0.)) ,
      ptype (ParticleGroup<dim>::NONE)
  {}


  template<int dim>
  ParticleGroup<dim>::ConnectionProp::ConnectionProp
  (double springConst_, double restLength_, double viscosityConst_, int cpid_)
    : springConst (springConst_), restLength (restLength_), viscosityConst (viscosityConst_), cpid (cpid_)
  {}

  template<int dim>
  ParticleGroup<dim>::ConnectionProp::ConnectionProp
  ()
    : springConst (0), restLength (0), viscosityConst (0), cpid (-1)
  {}

  template<int dim>
  ParticleGroup<dim>::Connection::Connection
  (int cid_, int gid1_, int pid1_, int gid2_, int pid2_, int cpid_, PositionType ptype_)
    : cid (cid_), gid1 (gid1_), pid1 (pid1_), gid2 (gid2_), pid2 (pid2_), cpid (cpid_), ptype (ptype_)
  {}

  template<int dim>
  ParticleGroup<dim>::Connection::Connection
  ()
    : cid (-1), gid1 (-1), pid1 (-1), gid2 (-1), pid2 (-1), cpid (-1), ptype (ParticleGroup<dim>::NONE)
  {}

  template<int dim>
  ParticleGroup<dim>::ParticleGroup ()
    : gid (-1)
  {
    init_ ();
  }

  template<int dim>
  ParticleGroup<dim>::ParticleGroup (int gid_)
  {
    init_ ();
    gid = gid_;
  }

  template<int dim>
  void
  ParticleGroup<dim>::init_ ()
  {
    particles =  typename ParticleGroup<dim>::particle_vec_ptr_t (new typename ParticleGroup<dim>::particle_vec_t ());
    particlesProp = typename ParticleGroup<dim>::particle_prop_vec_ptr_t (new typename ParticleGroup<dim>::particle_prop_vec_t ());
    groups = typename ParticleGroup<dim>::group_vec_ptr_t (new typename ParticleGroup<dim>::group_vec_t ());
    connections = typename ParticleGroup<dim>::connection_vec_ptr_t (new typename ParticleGroup<dim>::connection_vec_t ());
    connectionsProp = typename ParticleGroup<dim>::connection_prop_vec_ptr_t (new typename ParticleGroup<dim>::connection_prop_vec_t());
    groupsMapping = typename ParticleGroup<dim>::imap_ptr_t (new typename ParticleGroup<dim>::imap ());
  }

#define ALLOC(TYPE, NAME, POOL)		\
  TYPE t;				\
  int id = (int) (POOL)->size ();	\
  SETTR (&t, NAME, id);			\
  (POOL)->push_back (t);		\
  return (*POOL)[id]

#define PREALLOC(POOL, N) (POOL)->reserve ((POOL)->size () + N)

  template<int dim>
  void
  ParticleGroup<dim>::preAllocParticleProps (int n)
  {
    PREALLOC(particlesProp, n);
  }

  template<int dim>
  typename ParticleGroup<dim>::ParticleProp&
  ParticleGroup<dim>::allocParticleProp ()
  {
    ALLOC(ParticleProp, ppid, particlesProp);
  }

  template<int dim>
  void
  ParticleGroup<dim>::preAllocParticles (int n)
  {
    PREALLOC(particles, n);
  }

  template<int dim>
  typename ParticleGroup<dim>::Particle&
  ParticleGroup<dim>::allocParticle_ ()
  {
    ALLOC(Particle, pid, particles);
  }

  template<int dim>
  typename ParticleGroup<dim>::Particle&
  ParticleGroup<dim>::allocParticle ()
  {
    typename ParticleGroup<dim>::Particle& p = allocParticle_ ();
    SETTr (p, gid, gid);
    return p;
  }

  template<int dim>
  void
  ParticleGroup<dim>::preAllocConnectionProps (int n)
  {
    PREALLOC(connectionsProp, n);
  }

  template<int dim>
  typename ParticleGroup<dim>::ConnectionProp&
  ParticleGroup<dim>::allocConnectionProp ()
  {
    ALLOC(ConnectionProp, cpid, connectionsProp);
  }

  template<int dim>
  void
  ParticleGroup<dim>::preAllocConnections (int n)
  {
    PREALLOC(connections, n);
  }
  
  template<int dim>
  typename ParticleGroup<dim>::Connection&
  ParticleGroup<dim>::allocConnection ()
  {
    ALLOC(Connection, cid, connections);
  }

  template<int dim>
  void
  ParticleGroup<dim>::addGroup (APTR(typename ParticleGroup::ParticleGroup) group)
  {
    int id = groups->size ();
    groups->push_back (group);
    (*groupsMapping)[GETTR(group, gid)] = id;
  }

  template<int dim>
  typename ParticleGroup<dim>::Particle&
  ParticleGroup<dim>::getParticle (int gid_, int pid_)
  {
    if ((gid_ == -1) 
	|| gid_ == gid)
      return (*particles) [pid_];

    int id = (*groupsMapping)[gid_];
    APTR(ParticleGroup) pg = (*groups)[id];

    return pg->getParticle (-1, pid_);
  }

}; // cytoskelab

#endif // __CYTOSKELAB_PARTICLE_GROUP_IMPL__
