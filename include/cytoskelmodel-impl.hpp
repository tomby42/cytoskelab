/**
 * CytoskelModel class implemetation
 *
 * \file cytoskelmodel-impl.hpp
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

#ifndef __CYTOSKELAB_CYTOSKELMODEL_IMPL__
#define __CYTOSKELAB_CYTOSKELMODEL_IMPL__

namespace cytoskelab {


	template<int dim>
	CytoskelModel<dim>::CytoskelModel() {
		this->cellId = -1;
		this->particles = particle_vect_ptr_t ( new std::vector< APTR( Particle<dim> ) >() );
		this->forceons = forceon_vect_ptr_t ( new std::vector< APTR( Forceon<dim> ) >() );
	}


    template<int dim>
	CytoskelModel<dim>::CytoskelModel(
		int cellId,
		std::string comment,
		APTR(CytoskelGroup<dim>) ctsklGroup ) {

		this->cellId = cellId;
		this->comment = comment;
		this->cytoskelGroup = ctsklGroup;

		this->particles = particle_vect_ptr_t ( new std::vector< APTR(Particle<dim>) >() );
		this->forceons = forceon_vect_ptr_t ( new std::vector< APTR( Forceon<dim> ) >() );
	}


	template<int dim>
	CytoskelModel<dim>::~CytoskelModel() {

	};


	template<int dim>
	void CytoskelModel<dim>::send( APTR(Message) message ) {
		cytoskelGroup->receive( message);
	}


	template<int dim>
	void CytoskelModel<dim>::receive( APTR(Message) message ) {

		Message::time_stamp_t tm = message->time_stamp;
		double step = 0;

		switch( message->type ){
			case Message::M_RECOMPUTE_EXTERNAL_FORCES:
				step = message->getStep();
				this->recomputeExternalForces(step, tm);
				break;

			case Message::M_RECOMPUTE_INTERNAL_FORCES:
				step = message->getStep();
				this->recomputeInternalForces(step, tm);
				break;

			case Message::M_RECOMPUTE_PARTICLE_POSITIONS:
				step = message->getStep();
				this->recomputeParticlePositions(step, tm);
				break;

		}
	}


	template<int dim>
	void CytoskelModel<dim>::addParticle( APTR(Particle<dim>) particle ) {
		this->particles->push_back( particle );
	}


    template<int dim>
	bool CytoskelModel<dim>::stepIsOk( double step ) {
		return ( step > 0 && step < 1 );
	}


    template<int dim>
	bool CytoskelModel<dim>::isInnerParticle( APTR(Particle<dim>) particle ) {
		//TODO
		return true;
	}


	template<int dim>
	void CytoskelModel<dim>::addNewParticle( APTR(Particle<dim>) particle ) {
		particles->push_back( particle );
	}


	template<int dim>
	void CytoskelModel<dim>::addNewForceon( APTR(Forceon<dim>) forceon) {
		forceons->push_back( forceon );
	}

	template<int dim>
	void CytoskelModel<dim>::setCytoskelGroup(
		APTR(CytoskelGroup<dim>) ctsklGroup ) {

		this->cytoskelGroup = ctsklGroup;

	}


	template<int dim>
	void CytoskelModel<dim>::setEqSolver( APTR( EqSolver ) eqs ) {
		this->eqSolver = eqs;
	}


	template<int dim>
	void CytoskelModel<dim>::recomputeInternalForces() {
	  typename std::vector< APTR(Forceon<dim>) >::iterator p =
		this->forceons->begin();

		while( p != this->forceons->end() ) {

			//force from every forceon is spread to
			//both endings (start and end)
			p->spreadIntForce();

			++p;
		}
	}


	template<int dim>
	void CytoskelModel<dim>::recomputeExternalForces() {
		//nothing happens
		//no external forces inside cell
	}





    template<int dim>
	void CytoskelModel<dim>::recomputeParticlePositions( double step, Message::time_stamp_t tm ) {
      typename std::vector< APTR(Particle<dim>) >::iterator p =
		this->particles->begin();

		//method computeNewPosition() of all particles is called
		//this method connects to EQSolver which provides
		//position recomputation
		while( p != this->particles->end() ) {
			p->computeNewPosition( eqSolver );
			++p;
		}
	}


    template<int dim>
	void CytoskelModel<dim>::updateParticlePosition( APTR(Message) message ){
		//vec_t newPosition = message->x;
		//message->particle->setPosition( newPosition );

	}


    template<int dim>
	void CytoskelModel<dim>::updateParticleExtForce( APTR(Message) message ){
		//vec_t newExtF = message->f;
		//message->particle->setExternalForce( newExtF );
	}

	/*
	template<int dim>
	CytoskelRepr<dim> CytoskelModel<dim>::output() {
		CytoskelRepr<dim> ret;

		//output particles
		typename std::vector< APTR(Particle<dim>) >::iterator p_it =
		particles->begin();

		while( p_it != particles->end() ){
			ret.add( ParticleRepr<dim>( (*p_it)->getCytoskelId(), (*p_it)->getId(), (*p_it)->getX() ) );

			++p_it;
		}

		//output forceons
		typename std::vector< APTR(Forceon<dim>) >::iterator v_it =
			forceons->begin();

		while (v_it != forceons->end() ){
			ret.add( ForceonRepr<dim>( (*v_it)->getStart()->getCytoskelId(), (*v_it)->getStart()->getId(),
				(*v_it)->getEnd()->getId() ) );
			++v_it;
		}

		return ret;
	}*/

};

#endif
