/**
 * c2c class implementation
 *
 * \file c2c-impl.hpp
 * \author jarda
 * \date 27-11-2010
 **/

/*  Copyright (C) 2010  Jaroslav Horacek

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


#ifndef __CYTOSKELAB_C2C_IMPL__
#define __CYTOSKELAB_C2C_IMPL__


namespace cytoskelab {


	template<int dim>
	void C2C::addParticle( APTR( Particle<dim> ) particle ) {
		particles->push_back( particle );
	}


	template<int dim>
	void C2C::addVoigt( APTR( Particle<dim>) voigt ) {
		voigts->push_back( voigt );
	}

	
	template<int dim>
	typedef C2C::vec_t C2C::getForce( APTR(Particle<dim>) particle ) {
		//browses whole list of voigts and looks for specified particle
		//provides addition of all forces found
		
		return vec_t(0.0);
	}

	
	template<int dim>
	void C2C::recomputeExternalForces() {
		vector< forceon_t >::iterator p =
		this->forceons->begin();

		while( p != this->forceons->end() ) {
			
			//force from every forceon is spread to 
			//both endings (start and end)
			p->spreadExtForce();

			++p;
		} 
	}



	template<int dim>
	void C2C::recomputeInternalForces() {
		//nothing happens
		//no internal forces in outer space
	}


	template<int dim>
	void C2C::recomputeParticlePositions(){
		vector< particle_t >::iterator p =
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
	void C2C::receive() {
		
		switch( message->type ){
			case Message::M_RECOMPUTE_EXTERNAL_FORCES:
				this->recomputeExternalForces();
				break;

			case Message::M_RECOMPUTE_INTERNAL_FORCES:
				this->recomputeInternalForces();
				break;
			case Message::M_RECOMPUTE_PARTICLE_POSITIONS:
				this->recomputeParticlePositions();
				break;
		
		} 
	}


	template<int dim>
	void C2C::send() {
	
	}

};


#endif