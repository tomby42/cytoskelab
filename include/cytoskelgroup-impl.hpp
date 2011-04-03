/**
 * CytoskelGroup class implemetation
 *
 * \file cytoskelsolver-impl.hpp
 * \author jarda, tomby
 * \date 7-12-2010
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


#include <iostream>


#ifndef __CYTOSKELAB_CYTOSKELGROUP_IMPL__
#define __CYTOSKELAB_CYTOSKELGROUP_IMPL__


namespace cytoskelab {


	template<int dim> 
	CytoskelGroup<dim>::CytoskelGroup() {
		this->messages = message_queue_ptr_t ( new std::queue< APTR(Message) > );
		this->cytoskelModels = cytoskel_vect_ptr_t( new std::vector< APTR(CytoskelModel<dim>) > );
	}

	template<int dim> 
	CytoskelGroup<dim>::~CytoskelGroup() {
		
	}



	template<int dim> 
	void CytoskelGroup<dim>::processComputeExternalForces() {
		
		while ( messages->empty() != true &&
			( messages->front() )->type == Message::M_COMPUTE_EXTERNAL_FORCE ){
			
			//send message to Eq solver
			//send(  );
			
			//
			std::cout << "compute external forces for particle" << std::endl;
			//

			messages->pop();
			
		}
	}
    
    
	template<int dim> 
	void CytoskelGroup<dim>::processComputeNewParticlePositions( ) {
	
		while ( messages->empty() != true &&
			( messages->front() )->type == Message::M_COMPUTE_NEW_PARTICLE_POSITION ){
			
			//send message to Eq solver
			//send(  );
			//
			std::cout << "compute new particle position" << std::endl;
			//


			messages->pop();
		
		}
	}


	template<int dim> 
	void CytoskelGroup<dim>::receive( APTR(Message) message ) {
		
		switch(message->type){
			case Message::M_RECOMPUTE_EXTERNAL_FORCES:
				propagateDown(message);
				//processComputeExternalForces();
				break;
			case Message::M_RECOMPUTE_INTERNAL_FORCES:
				propagateDown(message);
				//processComputeExternalForces();
				break;
			case Message::M_RECOMPUTE_PARTICLE_POSITIONS:
				propagateDown(message);
				//processComputeNewParticlePositions();
				break;
			case Message::M_COMPUTE_NEW_PARTICLE_POSITION:
				messages->push(message);
				break;	
		
		}	
	}
    

    template<int dim> 
	void CytoskelGroup<dim>::send( APTR (CytoskelModel<dim>) to, APTR (Message) message ) {
		to->receive(message);
	
	}


	template<int dim>
	void CytoskelGroup<dim>::addCytoskelModel( APTR( CytoskelModel<dim> ) ctsklModel ) {
		cytoskelModels->push_back( ctsklModel );
	}

    
    template<int dim>
	void CytoskelGroup<dim>::recomputeParticlePositions( double step, Message::time_stamp_t tm ) {
		std::vector< APTR( CytoskelModel<dim> ) >::iterator = 
			cytoskelModels->begin();

		APTR(Message) message( new MRecomputeParticlePositions<dim>() );

		message->step = step;
		message->timeStamp = tm;

		while (p != cytoskelModels->end() ){
			send(p, message );
			++p;	
		}
	
	}

	
	template<int dim>
	void CytoskelGroup<dim>::propagateDown( APTR( Message ) message ) {
		std::vector< APTR( CytoskelModel<dim> ) >::iterator p = 
			cytoskelModels->begin();

		while (p != cytoskelModels->end() ){
			send( *p, message );
			++p;	
		}
	}


	template<int dim>
	void CytoskelGroup<dim>::test(){
		std::cout << cytoskelModels->size() << std::endl;
	
	}

	template<int dim>
	CytoskelRepr<dim> CytoskelGroup<dim>::output(){
		CytoskelRepr<dim> ret;
		
		std::vector< APTR(CytoskelModel<dim>) >::iterator c_it=
		cytoskelModels->begin();

		while( c_it != cytoskelModels->end() ){
			ret.join( (*c_it)->output() );
			++c_it;
		}

		return ret;
	}

    template<int dim>
	void CytoskelGroup<dim>::setEqSolver() {
		std::vector< APTR( CytoskelModel<dim> ) >::iterator p = 
			cytoskelModels->begin();

		while (p != cytoskelModels->end() ){
			p->setEqSolver();
			++p;	
		}
	
	}

};

#endif