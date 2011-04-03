/**
 * c2c class definition
 *
 * \file c2c.hpp
 * \author jarda
 * \date 26-12-2010
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


#ifndef __CYTOSKELAB_C2C__
#define __CYTOSKELAB_C2C__


namespace cytoskelab {


	/** Class representing relations between cytoskelmodels
	 * it holds information about force influence of cytoskelmodels
	 *
	 */
	template< int dim>
	class C2C: public Atom {
		DEF_ATOM (C2C<dim>);

	protected:
		BOOST_SERIALIZE_ACCESS;

	
	public:
		typedef Particle<dim> particle_t;
		typedef Forceon<dim> forceon_t;
		typedef boost::shared_ptr <std::vector<particle_t> > particle_vect_ptr_t;
		typedef boost::shared_ptr <std::vector<forceon_t> > forceon_vect_ptr_t;
		typedef blitz::TinyVector<double, dim> vec_t;

	private:

		BOOST_SERIALIZE_BEGIN;
			BOOST_SERIALIZE_BASE(Atom);
        
			BOOST_SERIALIZE(particles);
			BOOST_SERIALIZE(forceons);

		BOOST_SERIALIZE_END;


		/** partiles of outer space */
		particle_vect_ptr_t particles;

		/** voigts between cytoskel models */
		forceon_vect_ptr_t forceons;

		/** recomputes external forces */
		void recomputeExternalForces();

		/** recomputes internal forces */
		void recomputeInternalForces();

		/** recompute new particle positions */
		void recomputeParticlePositions();


	public:

		/** adds new particle */
		void addParticle( APTR( Particle<dim> ) particle );

		/** adds new voigt */
		void addVoigt( APTR( Particle<dim>) voigt );

		/** returns sum of all forces applied to specified particle */
		vec_t getForce( APTR(Particle<dim>) particle );

		void receive( APTR(Message) message );

		void send();

		

	};

};


#endif