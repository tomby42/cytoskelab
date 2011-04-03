/**
 * CytoskelSolver class definition
 *
 * \file cytoskelsolver.hpp
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


#ifndef __CYTOSKEL_GROUP__
#define __CYTOSKEL_GROUP__

namespace cytoskelab {

  template <int> class CytoskelRepr;

  /** 
   * class CytoskelGroup
   * Cytoskelgroup can possibly be holder of
   * many cytoskelmodels
   * it is used like an abstraction
   * it provides some part of communication of cells 
   * with outer world
   * there can be more cytoskelgroups for possible paralelization
   */
  template<int dim>
  class CytoskelGroup: public Atom {
  DEF_ATOM (CytoskelGroup<dim>);  
  
  public:
	  typedef boost::shared_ptr< std::vector< APTR(CytoskelModel<dim> ) > > 
		  cytoskel_vect_ptr_t;

	  typedef boost::shared_ptr<std::queue <APTR(Message)> > message_queue_ptr_t;
  
  
  private:

    BOOST_SERIALIZE_BEGIN;
		BOOST_SERIALIZE_BASE(Atom);
        
		BOOST_SERIALIZE(cytoskelModels);
     
    BOOST_SERIALIZE_END;
    
    /** queue for incoming messages */
    message_queue_ptr_t messages;
    
	/** list of cytoskelmodels handled by this cytoskelsolver */
	cytoskel_vect_ptr_t cytoskelModels;
    
    
    //------------------------------------------------
    // Processing only one message
    //------------------------------------------------

    /** process one external force message */
    void processComputeExternalForces();
    
    /** process one new particle position message */
    void processComputeNewParticlePositions();
    
    /** 
     * recomputes particle positions according applied 
     * internal and external forces
     */
    void recomputeParticlePositions( double step, Message::time_stamp_t tm );

	/** propagates message down in hierachy */
	void propagateDown( APTR( Message ) message );
	
    
  public:
    
	/** constructor */
	CytoskelGroup();

	/** destructor */
	~CytoskelGroup();

    /** cellsolver accepts message from cell 
     * @param message message
     * @param from pointer to cell who sent message
     */
    void receive( APTR(Message) message );
    
    /** send to cell model 
     * @param to cell to send message to
     * @param message message 
     */
    void send( APTR (CytoskelModel<dim>) to, APTR (Message) message );
    

	/** adding new cytoskel model to be handled by this solver */
	void addCytoskelModel( APTR( CytoskelModel<dim> ) ctsklModel );

    /**********************************************
     *   methodts for processing all messages
     *   processGrow()
     *	 processForces()
     *   ...
     *********************************************/
    
	/////
	/////  test method
	/////
	void test();

	/**
	 * method returns output from power model
	 * for further usage 
	 * it returns coordinations of the net of cytoskelgroup
	 * vertices are particles
	 * edges are voigths elements
	 */
	CytoskelRepr<dim> output();

	/** sets equation solver to all cytoskelmodels in group */
	void setEqSolver();


    
    
  };
  
};


#endif // __CYTOSKEL_GROUP__
