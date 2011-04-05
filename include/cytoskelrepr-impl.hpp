/**
 * DESCRIPTION
 *
 * \file cytoskelrepr-impl.cpp
 * \author jarda
 * \date 20-10-2010
 **/

/*  Copyright (C) 2010 Jaroslav Horacek

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



#ifndef __CYTOSKELAB_CYTOSKELREPR_IMPL__
#define __CYTOSKELAB_CYTOSKELREPR_IMPL__

#include <iostream>


namespace cytoskelab {

	
	template< int dim>
	ParticleRepr<dim>::ParticleRepr(){
		this->id = -1;
		this->c_id = -1;
		this->x = vec_t( 0.0 );
	}

	template<int dim>
	ParticleRepr<dim>::ParticleRepr( int c_id, int id, vec_t x ){
		this->id = id;
		this->c_id = c_id;
		this->x = x;
	}

	template<int dim>
	ParticleRepr<dim>::~ParticleRepr(){
	
	}


//========================================================	
	
	
	template<int dim>
	ForceonRepr<dim>::ForceonRepr(){
		this->c_id = -1;
		this->start = -1;
		this->end = -1;
	}


	template<int dim>
	ForceonRepr<dim>::ForceonRepr( int c_id, int start, int end ){
		this->c_id = c_id;
		this->start = start;
		this->end = end;
	}


	template<int dim>
	ForceonRepr<dim>::~ForceonRepr(){
	
	}


//========================================================


	template<int dim>
	CytoskelRepr<dim>::CytoskelRepr(){
		this->particlesRepr = particle_vect_ptr_t ( new std::vector< ParticleRepr<dim> >() );
		this->forceonsRepr = forceon_vect_ptr_t ( new std::vector< ForceonRepr<dim> >() );
	
	}

	template<int dim>
	CytoskelRepr<dim>::~CytoskelRepr(){
	
	}

	template<int dim>
	void CytoskelRepr<dim>::add( ParticleRepr<dim> p ) {
		typename std::vector< ParticleRepr<dim > >::iterator it =
			particlesRepr->begin();

		while( it != particlesRepr->end() ){
			if( (it->id == p.id) && (it->c_id == p.c_id) )
				return;
			++it;
		}
		particlesRepr->push_back( p );
	
	}


	template<int dim>
	void CytoskelRepr<dim>::add( ForceonRepr<dim> v) {
		typename std::vector< ForceonRepr<dim > >::iterator it =
			forceonsRepr->begin();

		while( it != forceonsRepr->end() ){
			if( (it->start == v.start) && (it->end == v.end) && (it->c_id == v.c_id) )
				return;
			++it;
		}

		forceonsRepr->push_back( v );
	}


	template<int dim>
	void CytoskelRepr<dim>::join( CytoskelRepr<dim> & ctskl) {
		
		//joining new voigts
		typename std::vector< ForceonRepr<dim> >::iterator v_it = 
			ctskl.forceonsRepr->begin();

		while( v_it != ctskl.forceonsRepr->end() ){
			add( *v_it );
			++v_it;
		}

		//joining new particles
		typename std::vector< ParticleRepr<dim> >::iterator p_it = 
			ctskl.particlesRepr->begin();

		while( p_it != ctskl.particlesRepr->end() ){
			add( *p_it );
			++p_it;
		}
	
	}

	template<int dim>
	void CytoskelRepr<dim>::print(){
		//joining new particles
		typename std::vector< ParticleRepr<dim> >::iterator p_it = 
			particlesRepr->begin();

		while( p_it != particlesRepr->end() ){
			std::cout<< p_it->c_id << " " << p_it->id << std::endl;
			++p_it;
		}
		std::cout<< std::endl<< std::endl;

		typename std::vector< ForceonRepr<dim> >::iterator f_it = 
			forceonsRepr->begin();

		while( f_it != forceonsRepr->end() ){
			std::cout<< f_it->c_id << " " << f_it->start << " " << f_it->end << std::endl;
			++f_it;
		}
		std::cout<< std::endl<< std::endl;
	
	}

};

#endif
