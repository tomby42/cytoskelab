/**
 * Messages class definition
 *
 * \file messages.hpp
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


#ifndef __CYTOSKELAB_MESSAGES__
#define __CYTOSKELAB_MESSAGES__


/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 * SHORT INFO about message naming
 *
 * Every message class name starts with M...
 * Then it is followed with word
 * COMPUTE, UPDATE, RECOMPUTE

 * COMPUTE is request from lower object to object higher 
  in hierarchy to compute some data for it

 * RECOMPUTE is request from higher object to lower, to recompute 
  something in its structure 

 * UPDATE is request from higher object to lower object when it 
  is sending data the lower object requested

* then the name is followed by part saying what the content of message is

 +++++++++++++++++++++++++++++++++++++++*/


namespace cytoskelab {

  template <int> class CytoskelModel;


 //--------------------------------------------------------------------

  /** 
   * class Message
   * Ancestor of all messages 
   * message can be varius request for data
   * or computation
   */
  class Message : public Atom {
    DEF_ATOM (Message);

  protected:
    BOOST_SERIALIZE_BEGIN;
    BOOST_SERIALIZE (type);
    BOOST_SERIALIZE (time_stamp);
    BOOST_SERIALIZE_END;

  public:
    //typedef unsigned long message_type_t;
    typedef unsigned long time_stamp_t;

	/** type of the message */
    typedef enum message_type {
	  M_UPDATE_PARTICLE_POSITION,
	  M_UPDATE_PARTICLE_EXTERNAL_FORCE,
	  M_COMPUTE_NEW_PARTICLE_POSITION,
	  M_COMPUTE_EXTERNAL_FORCE,
	  M_RECOMPUTE_EXTERNAL_FORCES,
	  M_RECOMPUTE_INTERNAL_FORCES,
	  M_RECOMPUTE_PARTICLE_POSITIONS 
	} message_type_t;
    
    message_type_t type;
    time_stamp_t time_stamp;

	virtual double getStep(){ return 0; };

	Message() {}
    
    Message (message_type_t t, time_stamp_t tm)
      : type (t), time_stamp (tm)
    {}
  };


 //--------------------------------------------------------------------
  

  //**********************************************************
  //   MESSAGES CELLSOLVER TO CELL
  //**********************************************************  
  //					||
  //				   \||/
  //					\/


  /** 
   * Message for cell to recompute its specific particle position 
   */
  template<int dim>
  class MUpdateParticlePosition: public Message {
  public:
    typedef blitz::TinyVector<double, dim> vec_t;
    
    APTR(Particle<dim>) particle;
    vec_t x;
  };

//--------------------------------------------------------------------
  
  /**
   * Message for updating particle external force
   */
  template<int dim>
  class MUpdateParticleExternalForce: public Message {
  public:
    typedef blitz::TinyVector<double, dim> vec_t;
    
    APTR(Particle<dim>) particle;
    vec_t f;
    
  };

//--------------------------------------------------------------------

   /** 
   * request for cells to ask them to provide their needs
   * of external forces computation 
   */
  template<int dim>
  class MRecomputeInternalForces: public Message {
  public:
	 time_stamp_t timestamp;
	 double step;

	 MRecomputeInternalForces():
	 Message(M_RECOMPUTE_INTERNAL_FORCES, -1)
	 {}

	 MRecomputeInternalForces( time_stamp_t tm, double step ): 
		Message(M_RECOMPUTE_INTERNAL_FORCES, tm)
	 {
		this->step = step;
	 }


	 ~MRecomputeInternalForces() {}	

	 virtual double getStep(){ return step; };
    
  };	

//--------------------------------------------------------------------

  /** 
   * request for cells to ask them to provide their needs
   * of external forces computation 
   */
  template<int dim>
  class MRecomputeExternalForces: public Message {
  public:
	 time_stamp_t timestamp;
	 double step;

	 MRecomputeExternalForces():
	 Message(M_RECOMPUTE_EXTERNAL_FORCES, -1)
	 {}

	 MRecomputeExternalForces( time_stamp_t tm, double step ): 
		Message(M_RECOMPUTE_EXTERNAL_FORCES, tm)
	 {
		this->step = step;
	 }


	 ~MRecomputeExternalForces() {}	

	 virtual double getStep(){ return step; };
    
  };	

//--------------------------------------------------------------------

  /** 
   * request for cells to ask them to provide their needs
   * of particle position recomputation
   */
  template<int dim>
  class MRecomputeParticlePositions: public Message {
  public:
	 time_stamp_t timestamp;
	 double step;

	 MRecomputeParticlePositions():
		Message(M_RECOMPUTE_PARTICLE_POSITIONS, -1)
	 {}

	 MRecomputeParticlePositions( time_stamp_t tm, double step ): 
		Message(M_RECOMPUTE_PARTICLE_POSITIONS, tm)
	 {
		this->step = step;
	 }


	 ~MRecomputeParticlePositions() {}	

	 virtual double getStep(){ return step; };
    
  };	

//--------------------------------------------------------------------
  
  
  //*********************************************************
  //    MESSAGES CELL TO CELLSOLVER
  //*********************************************************
  //					||
  //				   \||/
  //					\/


  /** 
   * Message - cell asks to recompute new position of 
   * specified particle 
   */ 
  template<int dim>
  class MComputeNewParticlePosition: public Message {
  public:
    typedef blitz::TinyVector<double, dim> vec_t;
    
    APTR(Particle<dim>) particle;
    
    //vec_t x;
    //vec_t f;
    //vec_t v;
    
    double step;


	MComputeNewParticlePosition():
		Message(M_COMPUTE_NEW_PARTICLE_POSITION, -1)
	{}

	MComputeNewParticlePosition( time_stamp_t tm, double step, APTR(Particle<dim>) particle ):
		Message(M_COMPUTE_NEW_PARTICLE_POSITION, tm)
	{
		this->step = step;	
		this->particle = particle;
	}

	~MComputeNewParticlePosition() {}

	virtual double getStep(){ return step; };
    
  };
  
//--------------------------------------------------------------------
  
  /** 
   * request to recompute external force applied to 
   * one particle
   */
  template<int dim>
  class MComputeExternalForce: public Message {
  public:

	double step;

    APTR(Particle<dim>) particle;

	MComputeExternalForce():
	Message( M_COMPUTE_EXTERNAL_FORCE, -1 )
	{}

	MComputeExternalForce( time_stamp_t tm, double step, APTR(Particle<dim>) particle ):
		Message( M_COMPUTE_EXTERNAL_FORCE, tm )	
	{
		this->step = step;	
		this->particle = particle;
	}

	~MComputeExternalForce() {}

	virtual double getStep(){ return step; };
    
  };


//--------------------------------------------------------------------



};

#endif // __CYTOSKELAB_MESSAGES__
