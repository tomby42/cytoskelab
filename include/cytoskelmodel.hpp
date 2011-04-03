/**
 * Cytoskel model class definition
 *
 * \file cytoskelmodel.hpp
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


#ifndef __CYTOSKELAB_MODEL__
#define __CYTOSKELAB_MODEL__

namespace cytoskelab {
	
  template <int> class CytoskelGroup;
  template <int> class CytoskelRepr;
  template <int> class ForceonRepr;
  template <int> class ParticleRepr;
  class EqSolver;
  
  
  /**
   * class Cell 
   * defines the inner environment of cell
   * cell handles everything inside itself
   * if more information is required it asks
   * cellSolver modul which provides required 
   * data and compuation
   */
  template<int dim>
  class CytoskelModel : public Atom {
    DEF_ATOM (CytoskelModel<dim>);

  public:
	   typedef boost::shared_ptr< std::vector< APTR(Particle<dim> ) > > 
		  particle_vect_ptr_t;
	    typedef boost::shared_ptr< std::vector< APTR(Forceon<dim> ) > > 
		  forceon_vect_ptr_t;
 
  private:
	
	BOOST_SERIALIZE_BEGIN;
		BOOST_SERIALIZE_BASE(Atom);
        
		BOOST_SERIALIZE(cellId);
        BOOST_SERIALIZE(comment);
		BOOST_SERIALIZE(cytoskelGroup);
		BOOST_SERIALIZE(eqSolver);
		BOOST_SERIALIZE(particles);
		BOOST_SERIALIZE(forceons);
    BOOST_SERIALIZE_END;

    /** unique id of cell */
    int cellId;
    
    /** possible comment if needed */
    boost::shared_ptr <std::string> comment;
    
    /** 
     * pointer to cell solver  
     * it provides the only connection to outer world
     * of simulation 
     */
    APTR(CytoskelGroup<dim>) cytoskelGroup;


	APTR( EqSolver ) eqSolver;
    
    /** list of particles */
     boost::shared_ptr <std::vector< APTR( Particle<dim> ) > > particles;
    
    /** list of voigts */
    boost::shared_ptr <std::vector< APTR( Forceon<dim> )> > forceons;
    
    
    
    /**********************************************
     * private methods:
     **********************************************/
    
    
    /** adds new membrane particle */ 
    void addParticle( APTR( Particle<dim> ) particle );
    
    /** checks if the step is from interval (0,1) */
    bool stepIsOk( double step );
    
    /** returns true if particle is inner particle */
    bool isInnerParticle( APTR(Particle<dim>) particle );
    
    
    /**********************************************
     * lifecycle methods (used by recompute):
     **********************************************/
    
    /** cytoskelmodel sends requests to compute 
	 * external force for every particle from cell solver */
    void recomputeExternalForces();


	/** cytoskelmodel sends requests to compute 
	 * internal force for every particle from cell solver */
    void recomputeInternalForces();
    
    /** 
     * recomputes particle positions according applied 
     * internal and external forces
     */
    void recomputeParticlePositions( double step, Message::time_stamp_t tm );
    
    /** moves particle to desired position 
     * @param message
     */
    void updateParticlePosition( APTR(Message) message );
	
    /** updates external force of particle */
    void updateParticleExtForce( APTR(Message) message );
    
    
  public:
    
    /** Constructor  TODO hide as private*/
    CytoskelModel();
    
    /** Constructor */
    CytoskelModel( int cellId, std::string comment, APTR(CytoskelGroup<dim>) ctsklGroup );
    
    /** Destructor */
    ~CytoskelModel();
    
    
    /** 
     * adds new particle 
     */
    void addNewParticle( APTR(Particle<dim>) particle );
    
    /** 
     * adds new voigt element between two particles
     * @param start id of starting particle
     * @param end id of ending particle
     * @param springConst spring constant
     * @param restLength rest length of spring
     * @param viscosityConst viscosity constant
     * @param length length of voigt
     */
    void addNewForceon( APTR(Forceon<dim>) forceon );
    
    
    /** set new cell solver to cell */
    void setCytoskelGroup( APTR(CytoskelGroup<dim>) ctsklGroup );

	/** sets equation solver for this cytoskelmodel */
	void setEqSolver( APTR( EqSolver ) eqs );
    
    
    /******************************************************
     * communication methods
     ******************************************************/
    
    /** 
     * main mean of communication between cell and 
     * cellsolvers( other modules) 
     * message is always sent to cell solver attached to cell
     * @param cellsolver cell solver helping cell solve computation
     * @param message message to send 
     */
    void send( APTR(Message) message );
    
    /**
     * processing of reveived message
     * directly or in queue
     */
    void receive( APTR(Message) message );
    

	/**
	 * method returns output from power model
	 * for further usage 
	 * it returns coordinations of the net of cytoskelgroup
	 * vertices are particles
	 * edges are voigths elements
	 */
	CytoskelRepr<dim> output();
    
  };
  
};


#endif // __CYTOSKELAB_MODEL__
