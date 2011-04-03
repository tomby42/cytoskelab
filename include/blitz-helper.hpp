/**
 * Blitz helper function and classes
 *
 * \file blitz-helper.hpp
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

#ifndef __CYTOSKELAB_BLITZ_HELPER__
#define __CYTOSKELAB_BLITZ_HELPER__

#include <blitz/array.h>
#include <blitz/tinyvec-et.h>

namespace cytoskelab {

  /***
   * Helper functions for comparison of blitz::TinyVectors
   */

  template<typename type, int dim>
  inline bool eq_index (const blitz::TinyVector<type, dim>& i1, const blitz::TinyVector<type, dim>& i2)
  {
    typedef typename blitz::TinyVector<type, dim>::iterator iterator;
    iterator it1 = const_cast<iterator> (i1.begin());
    iterator it2 = const_cast<iterator> (i2.begin());

    for (; it1 != i1.end (); ++it1, ++it2)
      if (*it1 != *it2)
	return false;

    return true;
  }

  template<typename type, int dim>
  inline bool neq_index (const blitz::TinyVector<type, dim>& i1, const blitz::TinyVector<type, dim>& i2)
  {
    typedef typename blitz::TinyVector<type, dim>::iterator iterator;
    iterator it1 = const_cast<iterator> (i1.begin());
    iterator it2 = const_cast<iterator> (i2.begin());
    
    for (; it1 != i1.end (); ++it1, ++it2)
      if (*it1 != *it2)
	return true;

    return false;
  }

  template<typename type, int dim>
  inline blitz::TinyVector<type, dim>
  lshift_ub (const blitz::TinyVector<type, dim>& v, int l)
  { return (v + ((1 << l) - 1)) >> l; }

  template<typename type, int dim>
  class axlex_less_index
  {
  public:
    inline bool operator() (const blitz::TinyVector<type, dim>& i1, const blitz::TinyVector<type, dim>& i2) const
    {
      typedef typename blitz::TinyVector<type, dim>::iterator iterator;
      iterator it1 = const_cast<iterator> (i1.begin());
      iterator it2 = const_cast<iterator> (i2.begin());
    
      for (; it1 != i1.end (); ++it1, ++it2)
	{
	  if (*it1 < *it2)
	    return true;
	  else if (*it1 > *it2)
	    return false;
	}
    
      return false;
    }
  };

  template<typename type, int dim>
  void
  print_dbg (blitz::TinyVector<type, dim>& v)
  { 
    typename blitz::TinyVector<type, dim>::iterator it;
      
    std::cout << "( ";
    for (it = v.begin (); it != v.end (); ++it)
      std::cout << *it << " ";

    std::cout << ")";
  }

  /***
   * Helper functions for comparison of blitz::RectDomains
   */

  template<int dim>
  inline bool eq_rect_dom (const blitz::RectDomain<dim>& d1, const blitz::RectDomain<dim>& d2)
  {
    if (neq_index<int, dim> (d1.lbound (), d2.lbound ()))
      return false;

    if (neq_index<int, dim> (d1.ubound (), d2.ubound ()))
      return false;

    return true;
  }

  template<int dim>
  inline bool neq_rect_dom (const blitz::RectDomain<dim>& d1, const blitz::RectDomain<dim>& d2)
  {
    if (neq_index<int, dim> (d1.lbound (), d2.lbound ()))
      return true;

    if (neq_index<int, dim> (d1.ubound (), d2.ubound ()))
      return true;

    return false;
  }

  template<int dim>
  inline bool rect_dom_empty_p (const blitz::RectDomain<dim>& d)
  {
    typedef typename blitz::TinyVector<int, dim>::iterator iterator;
    iterator it1 = const_cast<iterator> (d.lbound ().begin ());
    iterator it2 = const_cast<iterator> (d.ubound ().begin ());

    for (; it1 != d.lbound ().end (); ++it1, ++it2)
      if (*it1 >= *it2)
	return true;

    return false;
  }

  template<int dim>
  inline blitz::RectDomain<dim> 
  rect_dom_intersection (const blitz::TinyVector<int, dim>& lb1, 
			 const blitz::TinyVector<int, dim>& ub1, 
			 const blitz::TinyVector<int, dim>& lb2, 
			 const blitz::TinyVector<int, dim>& ub2)
  {
    typedef typename blitz::TinyVector<int, dim>::iterator iterator;
    blitz::RectDomain<dim> d;
    iterator itl1 = const_cast<iterator> (lb1.begin ());
    iterator itu1 = const_cast<iterator> (ub1.begin ());
    iterator itl2 = const_cast<iterator> (lb2.begin ());
    iterator itu2 = const_cast<iterator> (ub2.begin ());
    iterator itl = d.lbound ().begin ();
    iterator itu = d.ubound ().begin ();
    
    for (; itl1 != lb1.end (); ++itl1, ++itu1, ++itl2, ++itu2, ++itl, ++itu)
      {
	if (*itl1 > *itu2)
	  *itl = *itu = 0;
	else if (*itu1 < *itl2)
	  *itl = *itu = 0;
	else
	  {
	    *itl = std::max (*itl1, *itl2);
	    *itu = std::min (*itu1, *itu2);
	  }
      }

    return d;
  }
  
  template<int dim>
  inline blitz::RectDomain<dim> 
  rect_dom_intersection (const blitz::RectDomain<dim>& d1, 
			 const blitz::TinyVector<int, dim>& lb2, 
			 const blitz::TinyVector<int, dim>& ub2)
  { return rect_dom_intersection (d1.lbound (), d1.ubound (), lb2, ub2); }

  template<int dim>
  inline blitz::RectDomain<dim> 
  rect_dom_intersection (const blitz::RectDomain<dim>& d1, const blitz::RectDomain<dim>& d2)
  { return rect_dom_intersection (d1, d2.lbound (), d2.ubound ()); }

  template<int Dim>
  blitz::TinyVector<int, Dim>
  rect_dom_min_rel_coord (const blitz::RectDomain<Dim>& p1, const blitz::RectDomain<Dim>& p2)
  {
    blitz::TinyVector<int, Dim> dist;

    for (int i = 0; i < Dim; ++i)
      {
	if (p1.ubound () [i] <= p2.lbound () [i])
	  dist [i] = p2.lbound () [i] - p1.ubound () [i] + 1;
	else if (p2.ubound () [i] <= p1.lbound () [i])
	  dist [i] = p2.ubound () [i] - p1.lbound () [i] - 1;
	else
	  dist [i] = 0;
      }

    return dist;
  }

  template<int Dim>
  bool
  rect_dom_in_p (const blitz::RectDomain<Dim>& d, const blitz::TinyVector<int, Dim>& p)
  {
    const blitz::TinyVector<int, Dim>& lb = d.lbound ();
    const blitz::TinyVector<int, Dim>& ub = d.ubound ();

    for (int i = 0; i < Dim; ++i)
      if ((lb [i] > p [i]) || (p [i] > ub [i]))
	return false;
	
    return true;
  }

  template<int Dim>
  void
  print_dbg (blitz::RectDomain<Dim>& d)
  {
    std::cout << "lbound: ";
    print_dbg (d.lbound ());
    std::cout << " ubound: ";
    print_dbg (d.ubound ());
  }

  /***
   * Helper class for blitz::RectDomain iteration
   */

  template<int dim>
  class RectDomIterator
  {
  public:
    typedef blitz::TinyVector<int, dim> IndexType;
    typedef blitz::RectDomain<dim> RectDomType;

  protected:
    RectDomType rect_dom;
    IndexType	pos;
    
  public:
    RectDomIterator ();
    RectDomIterator (RectDomType& irec_dom, bool end = false);
    RectDomIterator (IndexType lbound, IndexType ubound, bool end = false);
    RectDomIterator (const RectDomIterator& it);

    RectDomIterator& operator++ ();
    RectDomIterator& operator+= (int);
    IndexType& operator* ();
    bool operator== (const RectDomIterator&);
    bool operator!= (const RectDomIterator&);

    bool end_p ();
    bool empty_p ();
    RectDomType& domain ();

    void print_dbg ();
  };

  /// Implementation
  
  
  template<int dim>
  RectDomIterator<dim>::RectDomIterator ()
    : pos (0)
  { rect_dom = blitz::RectDomain<dim> (blitz::TinyVector<int, dim> (0), blitz::TinyVector<int, dim> (0)); }


  template<int dim>
  RectDomIterator<dim>::RectDomIterator (RectDomType& irect_dom, bool end)
    : rect_dom (irect_dom), pos (end ? irect_dom.ubound () : irect_dom.lbound ())
  {}

  template<int dim>
  RectDomIterator<dim>::RectDomIterator (IndexType lbound, IndexType ubound, bool end)
    : rect_dom (lbound, ubound), pos (end ? ubound : lbound)
  {}

  template<int dim>
  RectDomIterator<dim>::RectDomIterator (const RectDomIterator<dim>& it)
    : rect_dom (it.rect_dom), pos (it.pos)
  {}

  template<int dim>
  RectDomIterator<dim>&
  RectDomIterator<dim>::operator++ ()
  {
    int i = dim - 1;

    pos [i] ++;
    while (pos [i] == rect_dom.ubound () [i])
      {
	pos [i] = rect_dom.lbound () [i];
	i --;
	if (i < 0)
	  {
	    pos = rect_dom.ubound ();
	    break;
	  }
	pos [i] ++;
      }

    return *this;
  }

  template<int dim>
  RectDomIterator<dim>&
  RectDomIterator<dim>::operator+= (int hop)
  {
    int i = dim - 1;

    pos [i] += hop;
    while (pos [i] >= rect_dom.ubound () [i])
      {
	pos [i] = rect_dom.lbound () [i];
	i --;
	if (i < 0)
	  {
	    pos = rect_dom.ubound ();
	    break;
	  }
	pos [i] += hop;
      }

    return *this;
  }

  template<int dim>
  typename RectDomIterator<dim>::IndexType&
  RectDomIterator<dim>::operator* ()
  { return pos; }

  template<int dim>
  bool
  RectDomIterator<dim>::operator== (const RectDomIterator& it)
  {
    if (neq_rect_dom<dim> (rect_dom, it.recr_dom))
      return false;

    if (neq_index<int, dim> (pos, it.pos))
      return false;

    return true;
  }

  template<int dim>
  bool
  RectDomIterator<dim>::operator!= (const RectDomIterator& it)
  {
    if (neq_rect_dom<dim> (rect_dom, it.rect_dom))
      return true;

    if (neq_index<int, dim> (pos, it.pos))
      return true;

    return false;
  }

  template<int dim>
  bool
  RectDomIterator<dim>::end_p ()
  { return eq_index<int, dim> (pos, rect_dom.ubound ()); }

  template<int dim>
  bool
  RectDomIterator<dim>::empty_p ()
  { return rect_dom_empty_p<dim> (rect_dom); }

  template<int dim>
  blitz::RectDomain<dim>&
  RectDomIterator<dim>::domain ()
  { return rect_dom; }

  template<int dim>
  void
  RectDomIterator<dim>::print_dbg ()
  {
    std::cout << "rect: ";
    print_dbg (rect_dom);
    std::cout << "  pos: ";
    print_dbg (pos);
  }

  /***
   * Helper functions for blitz::Array
   */

  /**
   * Compute offset (distance from begining of array in 
   * linear ordering) of index "index" in array "array". 
   * Can be used to obtain poiter to index by array.dataZero() + offset.
   * 
   * \param array - array where to compute offset
   * \param index - index into array that we can compute offset
   * \return offset of index
   */

  template<typename type, int dim>
  inline int a_offset (const blitz::Array<type, dim>& array, const blitz::TinyVector<int, dim>& index)
  { return blitz::dot (array.stride(), index); }

  /**
   * Compute pointer into array "array" at position "index".
   *
   * \param array - array where to compute pointer
   * \param index - position index
   * \return Pointer into array at position index
   */

  template<typename type, int dim>
  inline type* a_pointer (const blitz::Array<type, dim>& array, const blitz::TinyVector<int, dim>& index)
  { return array.dataZero() + a_offset<type, dim> (array, index); }


  /**
   * Compute pointer into array "array" with offset "offset".
   *
   * \param array - array where to compute pointer
   * \param offset - offset of site
   * \return Pointer into array at offset site
   */

  template<typename type, int dim>
  inline type* a_pointer (const blitz::Array<type, dim>& array, int offset)
  { return array.dataZero() + offset; }

}; // namespace cytoskelab

#include <boost/functional/hash.hpp>

namespace boost {

  template<typename type, int dim> 
  inline std::size_t hash_value(const blitz::TinyVector<type, dim>& v)
  { return hash_range<blitz::TinyVector<type, dim>::iteration> (v.begin (), v.end ()); }

}; // namespace boost

#endif
