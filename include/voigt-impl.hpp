/**
 * Voigt class implemantation
 *
 * \file voigt-impl.hpp
 * \author jarda, tomby
 * \date 27-11-2010
 **/

/*  Copyright (C) 2010  Tomas 'tomby' Bily, Jaroslav Horacek

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

#ifndef __CYTOSKELAB_VOIGT_IMPL__
#define __CYTOSKELAB_VOIGT_IMPL__

namespace cytoskelab {

  template<int dim>
  Voigt<dim>::Voigt ()
  {}

  template<int dim>
  Voigt<dim>::Voigt 
  (APTR(Particle<dim>) _start, 
   APTR(Particle<dim>) _end,
   double _springConst,
   double _restLength,
   double _viscosityConst,
   voigt_type_t t)
    : start (_start), end (_end), springConst (_springConst), restLength (_restLength),
      viscosityConst (_viscosityConst), type(t)
  {}

  template<int dim>
  Voigt<dim>::~Voigt ()
  {}

  template<int dim>
  typename Voigt<dim>::vec_t
  Voigt<dim>::force (APTR (Particle<dim>) p) 
  { 
	  APTR(Particle<dim>) x1;
	  APTR(Particle<dim>) x2;

	  //wrong pointer to particle
	  if( p != start && p != end ){
		return vec_t(0.);
	  }
	  
	  //force on starting particle
	  if( p == start ) {
		x1 = start;
		x2 = end;
	  }

	  //force on ending particle
	  if( p == end ){
		x1 = end;
		x2 = start;
	  }

	  /**********************************************************
	  * according to formula:
	  *                          
	  *                           (length of voigt) - restLength
	  * F(x1,x2) = springConst * ------------------------------- *
	  *                              (length of voigt)
	  *
	  *
	  *   * ( position(x1) - position(x2) ) +
	  *
	  *
	  *   + viscosityConst * ( velocity(x1) - velocity(x2) )
	  *
	  ***********************************************************/

	  double len = this->getLength();
	  vec_t F = springConst * (len - restLength) / len * (x1->getX() - x2->getX() );
	  F = F + viscosityConst * (x1->getV() - x2->getV() ); 
		  
	  return F;
  }


  template<int dim>
  typename Voigt<dim>::voigt_type_t
  Voigt<dim>::getType() {
	return type;  
  }


  template<int dim>
  APTR(Particle<dim>) Voigt<dim>::getStart() {
	return this->start;
  }

  template<int dim>
  APTR(Particle<dim>) Voigt<dim>::getEnd() {
	  return this->end;
  }

  template<int dim>
  double Voigt<dim>::getSpringConst() {
	  return this->springConst;
  }

  template<int dim>
  double Voigt<dim>::getRestLength() {
	  return this->restLength;
  }

  template<int dim>
  double Voigt<dim>::getViscosityConst() {
	  return this->viscosityConst; 
  }

  template<int dim>
  double Voigt<dim>::getLength() {
		vec_t x1 = start->getX();
		vec_t x2 = end->getX();

		//according to formula for distance of two
		//points in n-dimensional space
		vec_t x = x1 - x2;
		x = x*x;
		double res = sum(x);

		return sqrt(res);
  }


  template<int dim>
  void Voigt<dim>::spreadIntForce(){
	  start->addInternalForce( force(start) );
	  end->addInternalForce( force(end) );
  
  }


  template<int dim>
  void Voigt<dim>::spreadExtForce(){
	  start->addExternalForce( force(start) );
	  end->addExternalForce( force(end) );
  
  }


};

#endif
