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

#ifndef __CYTOSKELAB_PARTICLE_GROUP__
#define __CYTOSKELAB_PARTICLE_GROUP__

namespace cytoskelab {

  template<int dim>
  class ParticleGroup : public Atom {
    DEF_ATOM (ParticleGroup<dim>);

  public:
    typedef blitz::TinyVector<double, dim> vec_t;
    typedef blitz::TinyMatrix<double, dim, dim> mat_t;

    enum PositionType {
      NONE,
      INNER,
      OUTER,
      BOUNDARY
    };

  public:
    class ParticleProp {
      int ppid;
      double mass;
      vec_t  center;
      mat_t  inertia;

    public:
      ParticleProp ();
      ParticleProp (int ppid, double mass_, vec_t& center_, mat_t& inertia_);

      DEF_TTR(int, ppid);
      DEF_TTR(double, mass);
      DEF_TTR(vec_t, center);
      DEF_TTR(mat_t, inertia);
    };

    class Particle {
      int	pid;	// particle id
      int	gid;	// particle group id
      int	ppid;	// particle property id
      vec_t	pos;	// position
      vec_t	vel;	// velocity
      vec_t	Fext;	// external forces
      vec_t	Facc;   // current accumulated force 
      PositionType ptype;

    public:
      Particle ();
      Particle (int pid_, int gid_, int ppid_, vec_t& pos_, vec_t& vel_, 
		vec_t& Fext_, vec_t& Facc_, PositionType ptype_);

      DEF_TTR(int, pid);
      DEF_TTR(int, gid);
      DEF_TTR(int, ppid);
      DEF_TTR(vec_t, pos);
      DEF_TTR(vec_t, vel);
      DEF_TTR(vec_t, Fext);
      DEF_TTR(vec_t, Facc);
      DEF_TTR(PositionType, ptype);
    };

    class ConnectionProp {
      double springConst;
      double restLength;
      double viscosityConst;
      int    cpid;

    public:
      ConnectionProp ();
      ConnectionProp (double springConst_, double restLength_, double viscosityConst_, int cpid_);

      DEF_TTR(double, springConst);
      DEF_TTR(double, restLength);
      DEF_TTR(double, viscosityConst);
      DEF_TTR(int, cpid);
    };
    
    class Connection {
      int cid;
      int gid1, pid1;
      int gid2, pid2;
      int cpid;
      PositionType ptype;
      
    public:
      Connection ();
      Connection (int cid_, int gid1_, int pid1_, int gid2_, int pid2_, int cpid_, PositionType ptype_);

      DEF_TTR(int, cid);
      DEF_TTR(int, gid1);
      DEF_TTR(int, pid1);
      DEF_TTR(int, gid2);
      DEF_TTR(int, pid2);
      DEF_TTR(int, cpid);
      DEF_TTR(PositionType, ptype);
    };

  public: 
    typedef std::vector<Particle> particle_vec_t;
    typedef std::vector<ParticleProp> particle_prop_vec_t;
    typedef std::vector<APTR(ParticleGroup)> group_vec_t; 
    typedef std::vector<Connection> connection_vec_t;
    typedef std::vector<ConnectionProp> connection_prop_vec_t;
    typedef boost::unordered_map<int, int> imap;

    typedef boost::shared_ptr<particle_vec_t> particle_vec_ptr_t;
    typedef boost::shared_ptr<particle_prop_vec_t> particle_prop_vec_ptr_t;
    typedef boost::shared_ptr<group_vec_t> group_vec_ptr_t;
    typedef boost::shared_ptr<connection_vec_t> connection_vec_ptr_t;
    typedef boost::shared_ptr<connection_prop_vec_t> connection_prop_vec_ptr_t;
    typedef boost::shared_ptr<imap> imap_ptr_t;

  protected:
    int				gid;
    particle_vec_ptr_t		particles;
    particle_prop_vec_ptr_t	particlesProp;
    group_vec_ptr_t		groups;
    connection_vec_ptr_t	connections;
    connection_prop_vec_ptr_t	connectionsProp;
    imap_ptr_t			groupsMapping;

  public:
    ParticleGroup ();
    ParticleGroup (int gid_);

    void preAllocParticleProps (int n);
    ParticleProp& allocParticleProp ();
    void preAllocParticles (int n);
    Particle& allocParticle ();
    void preAllocConnectionProps (int n);
    ConnectionProp& allocConnectionProp ();
    void preAllocConnections (int n);
    Connection& allocConnection ();
    void addGroup (APTR(ParticleGroup) group);

    Particle& getParticle (int gid, int pid);

    DEF_TTR(particle_vec_ptr_t, particles);
    DEF_TTR(particle_prop_vec_ptr_t, particlesProp);
    DEF_TTR(group_vec_ptr_t, groups);
    DEF_TTR(connection_vec_ptr_t, connections);
    DEF_TTR(connection_prop_vec_ptr_t, connectionsProp);
    DEF_TTR(imap_ptr_t, groupsMapping);
    DEF_TTR(int, gid);

  private:
    void init_ ();
    Particle& allocParticle_ ();
  };

}; // cytoskelab

#endif // __CYTOSKELAB_PARTICLE_GROUP__
