/**
 * Simulation class definition
 *
 * \file simulation.hpp
 * \author jarda
 * \date 30-01-2011
 **/

/*  Copyright (C) 2011  Jaroslav Horacek, Tomas 'tomby' Bily

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


#ifndef __CYTOSKELAB_SIMULATION__
#define __CYTOSKELAB_SIMULATION__

namespace cytoskelab {


  template <int> class CytoskelGroup;
  template <int> class C2C;
  class EqSolver;


/** 
 * class Simulation
 * Contemporary class holding whole information
 * about simulation
 * contains methods to start, stop, save, load
 * current simulation
 * the highest class of cytoskelab hierarchy
 */
	class Simulation: public Atom {
	
	protected:
		BOOST_SERIALIZE_ACCESS;

	private:

		BOOST_SERIALIZE_BEGIN;
			BOOST_SERIALIZE_BASE(Atom);
        
			BOOST_SERIALIZE(cytoskelSolver);
			BOOST_SERIALIZE(c2c);
			BOOST_SERIALIZE(eqSolver);
		BOOST_SERIALIZE_END;

		//Cytoskel group
		CytoskelGroup cytoskelGroup;
		
		//C2C model
		C2C c2c;

		//eqSolver
		EqSolver eqSolver;


	public:
	
	
	};



};

#endif // __CYTOSKELAB_SIMULATION__