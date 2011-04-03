/**
 * Atom class definition
 *
 * Basic class that define interface for ref counting and
 * serialization.
 *
 * \file atom.hpp
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

#ifndef __CYTOSKELAB_ATOM__
#define __CYTOSKELAB_ATOM__

#define CTSKL_DEFC(X)			\
namespace cytoskelab {			\
  class X;				\
}

CTSKL_DEFC (Atom);
BOOST_IPTR_DEF (cytoskelab::Atom);

namespace cytoskelab {

#define DEF_ATOM(TYPE)						\
public:                                                         \
 typedef boost::intrusive_ptr<TYPE > Ptr;                       \
 typedef TYPE Self;                                             \
								\
protected:							\
 BOOST_SERIALIZE_ACCESS

#if 1
#define APTR(TYPE) boost::intrusive_ptr<TYPE >
#else
#define APTR(TYPE) typename TYPE::Ptr
#endif

#define GETTRN(NAME) Get ## NAME 
#define SETTRN(NAME) Set ## NAME

#define DEF_TTR(TYPE, NAME)			\
  void SETTRN (NAME) (TYPE & _) { NAME = _; }	\
  TYPE const & GETTRN (NAME) () { return NAME; } 

#define GETTR(INSTANCE, NAME) INSTANCE->GETTRN(NAME) ()
#define SETTR(INSTANCE, NAME, VAL) INSTANCE->SETTRN(NAME) (VAL)

  /**
   * Declaration of class Atom
   * 
   * Predecestor of all classes that need ref counting and
   * serialization. Every succesor need to define Atom basic
   * definition by DEF_ATOM(TYPE) in declaration part.
   **/

  class Atom {
    DEF_ATOM(Atom);

  protected:
    typedef unsigned long ref_t;
    
    ref_t               ref_counter;
    
    inline void ref ()
    { ref_counter ++; }
    
    inline ref_t unref ()
    { return --ref_counter; }
  
    inline ref_t get_ref ()
    { return ref_counter; }

    Atom ()
      : ref_counter (0)
    {}

    BOOST_IPTR_FRIEND(cytoskelab::Atom);

  public:
    virtual ~Atom () {};

  };
}; // namespace cytoskelab

BOOST_IPTR(cytoskelab::Atom);

#endif
