/**
 * Main
 *
 * \file main.cpp
 * \author tomby
 * \date 27-11-2010
 **/

/*  Copyright (C) 2010  Tomas 'tomby' Bily

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
#include "cytoskelab-sys.hpp"

#include "particles.hpp"
#include "particles-impl.hpp"
#include "messages.hpp"
#include "forceon.hpp"
#include "voigt.hpp"
#include "voigt-impl.hpp"
#include "cytoskelmodel.hpp"
#include "cytoskelmodel-impl.hpp"
#include "cytoskelgroup.hpp"
#include "cytoskelgroup-impl.hpp"

#include "registry.hpp"
#include "registry-impl.hpp"
#include "eq-solver.hpp"


#include "cytoskelrepr.hpp" 
#include "cytoskelrepr-impl.hpp"


/* FOR LATER USE do not forget to 
   include hpps for serialization 
*/


using namespace cytoskelab;

#define PASS(X) std::cout << #X << "... pass\n"


static void
test0 ()
{
  Particle<2>::Ptr p11 (new Particle<2> ());
  PASS(test1);
  
  Message::Ptr m11 (new Message (Message::M_UPDATE_PARTICLE_POSITION, 0));
  PASS(test2);
  
  Voigt<2>::Ptr v11 (new Voigt<2> ());
  PASS(test3);
  
  EqInstance::Ptr eqi1 (new EqInstance ());
  EqId id1 (std::string ("e1"), 1);
  EqId id2;

  SETTR(eqi1, eq_id, id1);
  id2 = GETTR(eqi1, eq_id);
  PASS(test4);
}

static void
test1 ()
{
  	/*Particle<2>::Ptr p1 (new Particle<2> ());
	Particle<2>::Ptr p2 (new Particle<2> ());

	CytoskelModel<2>::Ptr c1 (new CytoskelModel<2>() ); 
   
	c1->addNewParticle(p1);
	c1->addNewParticle(p2);*/

#if 0  
	Particle<2>::Ptr p1 (new Particle<2> ());
	Particle<2>::Ptr p2 (new Particle<2> ());

	CytoskelModel<2>::Ptr c1 (new CytoskelModel<2>() );
	CytoskelModel<2>::Ptr c2 (new CytoskelModel<2>() );

	c1->addNewParticle( p1 );
	c2->addNewParticle( p2 );

	Message::Ptr m1 ( new MRecomputeParticlePositions<2> );	
	Message::Ptr m2 ( new MRecomputeExternalForces<2> );

	CytoskelSolver<2>::Ptr cs1 (new CytoskelSolver<2>() ); 

	cs1->addCytoskelModel( c1 );
	//cs1->addCytoskelModel( c2 );

	c1->setCytoskelSolver( cs1 );
	//c2->setCytoskelSolver( cs1 );


	cs1->receive( m2 );

	//cs1->test();
#endif
}


static void
test2() {
 
	ParticleRepr<2> p1 (1,1,ParticleRepr<2>::vec_t(0.0));
	ParticleRepr<2> p2 (1,2,ParticleRepr<2>::vec_t(0.0));
	ParticleRepr<2> p3 (1,3,ParticleRepr<2>::vec_t(0.0));
	ParticleRepr<2> p4 (1,4,ParticleRepr<2>::vec_t(0.0));

	CytoskelRepr<2> cr1;
	CytoskelRepr<2> cr2;

	cr1.add( p1 );
	cr1.add( p2 );
	
	cr1.print();

	cr2.add( p3 );
	cr2.add( p4 );

	cr2.print();

	cr1.join( cr2 );

	cr1.print();

	PASS(test2);

}
/*
static void 
test3(){
	typedef blitz::TinyVector<double, 2> vec_t;
	
	Particle<2>::Ptr p1 (new Particle<2> ( vec_t(1.0, 1.0), 1, 1, Particle<2>::INNER));
	Particle<2>::Ptr p2 (new Particle<2> ( vec_t(2.0, 2.0), 2, 1, Particle<2>::INNER));
	Forceon<2>::Ptr v1 (new Voigt<2> (p1, p2, 0.1, 0.5, 0.2, Voigt<2>::INNER ));

	std::cout << v1->force(p2) << std::endl;

	PASS(test3);
	
}


static void 
test4(){
	typedef blitz::TinyVector<double, 2> vec_t;
	Particle<2>::Ptr p1 (new Particle<2> ( vec_t(1.0, 1.0), 1, 1, Particle<2>::INNER));
	Particle<2>::Ptr p2 (new Particle<2> ( vec_t(2.0, 2.0), 2, 1, Particle<2>::INNER));

	Forceon<2>::Ptr v1 (new Voigt<2> (p1, p2, 0.1, 0.5, 0.2, Voigt<2>::INNER ));

	CytoskelModel<2>::Ptr c1 (new CytoskelModel<2>() );

	c1->addNewParticle( p1 );
	c1->addNewParticle( p2 );

	c1->addNewForceon( v1 ); 

	CytoskelGroup<2>::Ptr cg1( new CytoskelGroup<2>() );
	cg1->addCytoskelModel(c1);

	CytoskelRepr<2> rep;
	rep = cg1->output();
	rep.print();

	PASS(test4);
}
*/


int main (int argc, char** argv)
{
  std::cout << "CYTOSKELAB ver. 0.1 alpha \n";
  std::cout << "BOOTING...\n";

  //test0 ();
  //test1 ();
  //test2 ();
  //test3();
//  test4();

  std::cout << "...BOOT SUCCESFULL\n";

  return 0;
}
