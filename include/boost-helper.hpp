/**
 * Boost helper function and classes
 *
 * \file boost-helper.hpp
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

#ifndef __CYTOSKELAB_BOOST_HELPER__
#define __CYTOSKELAB_BOOST_HELPER__

/*
 * Wrapper for making intrusive boost ptr definitions.
 * It is expected that class has methods ref () / unref ().
 */
#define BOOST_IPTR(KLASS) namespace boost {		\
  inline void intrusive_ptr_add_ref (KLASS* e) \
  { e->ref (); }					\
							\
  inline void intrusive_ptr_release (KLASS* e)		\
  { if (!e->unref ()) checked_delete (e); }		\
}

#define BOOST_IPTR_DEF(KLASS) namespace boost {		\
  inline void intrusive_ptr_add_ref (KLASS* e);		\
  inline void intrusive_ptr_release (KLASS* e);		\
}

#define BOOST_IPTR_FRIEND(KLASS)				\
  friend inline void boost::intrusive_ptr_add_ref (KLASS*);	\
  friend inline void boost::intrusive_ptr_release (KLASS*)

#define BOOST_SERIALIZE_BEGIN				\
  template<class Archive>				\
  void serialize(Archive &ar, const unsigned int version)\
    {

#define BOOST_SERIALIZE_END }
#define BOOST_SERIALIZE(X) ar & X
#define BOOST_SERIALIZE_BASE(KLASS) ar & boost::serialization::base_object<KLASS >(*this)

#define BOOST_SERIALIZE_REG_PTYPE(KLASS) ar.register_type(static_cast<KLASS *>(NULL))
#define BOOST_SERIALIZE_ACCESS friend class boost::serialization::access

#endif
