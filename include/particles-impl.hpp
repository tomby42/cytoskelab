/**
 * Pacticle class implemetation
 *
 * \file particle-impl.hpp
 * \author jarda, tomby
 * \date 27-11-2010
 **/

/*  Copyright (C) 2010  Jaroslav Horacek, Tomas 'tomby' Bily

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

#ifndef __CYTOSKELAB_PARTICLES_IMPL__
#define __CYTOSKELAB_PARTICLES_IMPL__

namespace cytoskelab {

  template<int dim>
  Particle<dim>::Particle ()
    : id (-1), ctsklId (-1), x (0.), v (0.), type(INNER), 
	internalF(0.), externalF (0.)
  {}

  template<int dim>
  Particle<dim>::Particle 
  ( typename Particle<dim>::vec_t& _x, 
	int _id, 
	int _ctsklId, 
	typename Particle<dim>::particle_type_t t 
  )
  : id (_id), ctsklId (_ctsklId), x (_x), v (0.), type(t), 
    internalF(0.), externalF (0.)
  {}

  template<int dim>
  Particle<dim>::~Particle ()
  {}

  template<int dim>
  void
  Particle<dim>::setX(vec_t& _x)
  { x = _x; }

  template<int dim>
  void
  Particle<dim>::setV(vec_t& _v)
  { v = _v; }

  template<int dim>
  void
  Particle<dim>::setExtF(vec_t& _f)
  { externalF = _f; }

  template<int dim>
  int
  Particle<dim>::getId()
  { return id; }

  template<int dim>
  int
  Particle<dim>::getCytoskelId ()
  { return ctsklId; }

  template<int dim>
  typename Particle<dim>::vec_t&
  Particle<dim>::getX () //const
  { return x; }

  template<int dim>
  typename Particle<dim>::particle_type_t Particle<dim>::getType() {
	return type;
  }

  
  template<int dim>
  typename Particle<dim>::vec_t&
  Particle<dim>::getV ()// const
  { return v; }

  
  template<int dim>
  typename Particle<dim>::vec_t&
  Particle<dim>::getExtF ()// const
  { return externalF; }


  template<int dim>
  void Particle<dim>::addInternalForce( typename Particle<dim>::vec_t & f ) {
	  this->internalF += f;
  }



  template<int dim>
  void Particle<dim>::addExternalForce( typename Particle<dim>::vec_t & f ) {
	  this->externalF += f;
  }


  template<int dim>
  void Particle<dim>::computeNewPosition( APTR( EqSolver) eqs ) {
	
    // TODO !!!!!!!
	//here it should be connection with 
    //instance of equation for this particle
    //ad using this equation we should be able to 
	//compute new position of particle

  }

};

#endif
