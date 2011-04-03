/**
 * Forceon class definition
 *
 * \file forceon.hpp
 * \author tomby, jarda
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

#ifndef __CYTOSKELAB_FORCEON__
#define __CYTOSKELAB_FORCEON__

namespace cytoskelab {

  template<int dim> class Particle;

  template <int dim>
  class Forceon : public Atom {
    DEF_ATOM (Forceon);

  public:
    typedef blitz::TinyVector<double, dim> vec_t;

  private:
	 BOOST_SERIALIZE_BEGIN;
		BOOST_SERIALIZE_BASE(Atom);
        
		BOOST_SERIALIZE(start);
        BOOST_SERIALIZE(end);
    BOOST_SERIALIZE_END;	

	APTR(Particle<dim>) start; 
	APTR(Particle<dim>) end;

  public:
    Forceon () {};
    virtual ~Forceon () {};

    /* \param p vector of particles where we need to compute force
     * \return vector of forces at particle p
     */
    virtual vec_t force (APTR(Particle<dim>) p) { return vec_t (0.); };


	///POKUS
	/** adds force caused with this forceon to particles
	 * making forceon
	 * as internal force
	 */
	virtual void spreadIntForce(){}; 

	/** adds force caused with this forceon to particles
	 * making forceon
	 * as external force
	 */
	virtual void spreadExtForce(){};

	/** returns start point */
	virtual APTR(Particle<dim>) getStart() { return start; };

	/** returns end point */
	virtual APTR(Particle<dim>) getEnd() { return end; };

  };

};

#endif
