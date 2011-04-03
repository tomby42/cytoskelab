/**
 * Representation of cytoskelgroups in "real" world
 * \file cytoskelrepr.hpp
 * \author jarda
 * \date 20-12-2010
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

#ifndef __CYTOSKELAB_CYTOSKELREPR__
#define __CYTOSKELAB_CYTOSKELREPR__

namespace cytoskelab {


	/** class representing particle*/
	template<int dim>
	class ParticleRepr {
	public:
		typedef blitz::TinyVector<double, dim> vec_t;

		/** position of particle */
		vec_t x;
		
		/** id of particle */
		int id;

		/** id of cytoskelmodel*/
		int c_id;

		ParticleRepr();
		ParticleRepr( int c_id, int id, vec_t x );
		~ParticleRepr();
	
	};


//------------------------------------------------------------

	/** class representing voigt */
	template<int dim>
	class ForceonRepr {
	public:
		
		/** id of cytoskelmodel*/
		int c_id;

		/** start of voigt */
		int start;

		/** end of voigt*/
		int end;

		//constructors
		ForceonRepr();
		ForceonRepr( int c_id, int start, int end );
		~ForceonRepr();
	};


//---------------------------------------------------------


	/**
	 * Class representing output from force cytoskeleton model 
	 */
	template<int dim>
	class CytoskelRepr {
	public:
		typedef blitz::TinyVector<double, dim> vec_t;

		typedef boost::shared_ptr <std::vector<ParticleRepr<dim> > > particle_vect_ptr_t;
		typedef boost::shared_ptr <std::vector<ForceonRepr<dim> > > forceon_vect_ptr_t;

		particle_vect_ptr_t particlesRepr;
		forceon_vect_ptr_t forceonsRepr;


		/** adds new particle representation 
		 * if there already particle is, it will not be added
		 */
		void add( ParticleRepr<dim> p);

		/** adds new voigt representation 
		 * if there already voigt is, it will not be added
		 */
		void add( ForceonRepr<dim> v );

		/** takes another cytoskelet representation and joins it 
		 * to this representation
		 * duplicities are ommitted
		 */
		void join( CytoskelRepr<dim> & ctskl);


		/** constructor */
		CytoskelRepr();

		/** destructor */
		~CytoskelRepr();


		/** test print method */
		void print();


	};




};

#endif