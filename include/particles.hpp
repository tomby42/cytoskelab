/**
 * Particle class definition
 *
 * \file particle.hpp
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


#ifndef __CYTOSKELAB_PARTICLES__
#define __CYTOSKELAB_PARTICLES__

namespace cytoskelab {

class EqSolver;	
	
	
/**
 * class Particle 
 * defines membrane or inner helping particle of cell
 * cell mass is divided between its particles
 * particles are bases for voigt elements
 * which create visco-elastic net between them
 *
 * there are 3 types of particles
 * INNER - particles inside cytoskelmodels
 * MEMBRANE - particles located on membranes of cytoskelmodels
 * OUTER - particles freely distibutes in outer space
 */

//-----------------------------------------------------------
//TODO make different objects for membrane and inner particle?
//-----------------------------------------------------------
  
  template<int dim>
  class Particle : public Atom {
    DEF_ATOM (Particle<dim>);

  public:
    typedef blitz::TinyVector<double, dim> vec_t;
	
	typedef enum particle_type{ 
		MEMBRANE, 
		INNER,
		OUTER
	} particle_type_t;

  private:

    BOOST_SERIALIZE_BEGIN;
		BOOST_SERIALIZE_BASE(Atom);
        
		BOOST_SERIALIZE(id);
        BOOST_SERIALIZE(ctsklId);
		BOOST_SERIALIZE(x);
		BOOST_SERIALIZE(v);
		BOOST_SERIALIZE(externalF);
		BOOST_SERIALIZE(internalF);
		BOOST_SERIALIZE(type);
    BOOST_SERIALIZE_END;

    /** unique id within one cell */
    int id;
    
    /** id of cell in which particle is located */
    int ctsklId;
    
    /** coordinates of particle in dim space */
    vec_t x;
    
    /** velocity */
    vec_t v;
    
    /** 
     * external force vector applied to particle 
     * defautl is zero
     */
    vec_t externalF;

	/**
	 * force from inside of cytoskelmodel
	 */
	vec_t internalF;

	particle_type_t type;
    
    //-------------------------------------------------
    // TODO: something representing cell mass and substances
    //-------------------------------------------------
    
    
  public:

    /** constructor */
    Particle();
    
    /**
     * parametrized constructor
     * @param coordinates
     * @param id wanted id of particle within a cell
     * @param cellId id of mother cell
	 * @param t particle type(MEMBRANE/INNER)
     */
    Particle(vec_t& _x, int id, int cellId, particle_type_t t );
    
    /** destructor */
    virtual ~Particle();
  
    /** set new position of particle */
    void setX(vec_t& _x);
    
    /** set new velocity */
    void setV(vec_t& _v);
    
    /** set external forces */
    void setExtF(vec_t& _f);



	/** adds new component of internal force  */
	void addInternalForce( vec_t & f );

	/** adds new component of external force */
	void addExternalForce( vec_t & f );



	/** uses eqsolver methods to compute new particle position */
	void computeNewPosition( APTR( EqSolver) eqs );



    /** return id of particle */
    int getId();
    
    /** return id of cell in which particle is located */
    int getCytoskelId();

	/** return true if particle is located on membrane */
	particle_type_t getType();
  
    /** get position */
    vec_t& getX(); // const;
    
    /** get velocity vector */
    vec_t& getV(); // const;
    
    /** get x external force vector */
    vec_t& getExtF(); // const;

  };
  
};

#endif // __CYTOSKELAB_PARTICLES__
