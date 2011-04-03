/**
 * Voigt class definition
 *
 * \file voigt.hpp
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

#ifndef __CYTOSKELAB_VOIGT__
#define __CYTOSKELAB_VOIGT__

namespace cytoskelab {

  /**
   * class Voigt
   * represents one viscoelastic element
   * consisting of parallel spring and piston
   * it can be connected only between two particles
   *
   * there are 3 types of voigts
   * INNER - voigts inside cytoskelmodel
   * MEMBRANE - voigts on membrane of cytoskelmodel
   * OUTER - voigts representing force joins between cytoskelmodels
   */ 
  template <int dim>
  class Voigt : public Forceon<dim> {
  DEF_ATOM (Voigt); 

  public:
    typedef blitz::TinyVector<double, dim> vec_t;
	typedef enum voigt_type{ 
		MEMBRANE, 
		INNER,
		OUTER
	} voigt_type_t;

  private:

	BOOST_SERIALIZE_BEGIN;
	    BOOST_SERIALIZE_BASE(Forceon);

        BOOST_SERIALIZE(start);
        BOOST_SERIALIZE(end);
		BOOST_SERIALIZE(springConst);
		BOOST_SERIALIZE(restLength);
		BOOST_SERIALIZE(viscosityConst);
		BOOST_SERIALIZE(length);
		BOOST_SERIALIZE(type);
    BOOST_SERIALIZE_END;
   


	/* TODO: POZOR redundantni start a end je jiz v Forceon 
	 => opravit
	*/

    /** id of start particle */
    APTR(Particle<dim>) start;
    
    /** id of end particle */
    APTR(Particle<dim>) end;
    
    /** spring constant */
    double springConst;
    
    /** spring rest length */
    double restLength;
    
    /** viscosity constant */
    double viscosityConst;
    
    /** length of voigt*/
    double length;

	/** type of voigt */
	voigt_type_t type;
    
  public:
    
    /** constructor */
    Voigt();
    
    /** 
     * param constructor 
     * @param startId id of starting particle
     * @param endId id of ending particle
     * @param springConst spring constant
     * @param restLength rest length of spring
     * @param viscosityConst viscosity constant
     */
    Voigt( 
	  APTR(Particle<dim>) start, 
	  APTR(Particle<dim>) end,
	  double springConst,
	  double restLength,
	  double viscosityConst,
	  voigt_type_t t);
    
    /** destructor */
    virtual ~Voigt();
    
    virtual vec_t force (APTR (Particle<dim>) p);


	/** adds force caused with this forceon to particles
	 * making forceon
	 * as internal force
	 */
	virtual void spreadIntForce(); 

	/** adds force caused with this forceon to particles
	 * making forceon
	 * as external force
	 */
	virtual void spreadExtForce();


	/** return start of voigt */
	virtual APTR(Particle<dim>) getStart();

	/** return end of voigt */
	virtual APTR(Particle<dim>) getEnd();


	/** return spring constant */
	double getSpringConst();

	/** return rest length */
	double getRestLength();

	/** return viscosity constant */
	double getViscosityConst();

	/** return length */
	double getLength();

	/** returns type of voigt */
	voigt_type_t getType();
    
  };
  
};


#endif // __CYTOSKELAB_VOIGT__
