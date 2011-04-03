/**
 * Binary Heap 
 *
 * \file bheap.hpp
 * \author tomby
 * \date 04-01-2009
 **/

/*  Copyright (C) 2009  Tomas 'tomby' Bily

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


#ifndef __CYTOSKELAB_BIN_HEAP__
#define __CYTOSKELAB_BIN_HEAP__

namespace cytoskelab {

    template <typename type>
    class FingerFreeCmp
    {
    public:
      typedef type PriorityType;

    public:
      static inline type get_priority (type& s) 
      { return s; }

      static inline int get_finger (type& s)
      { throw "Not implemented"; }

      static inline void set_finger (type& s, int pos)
      {}
      
      static inline bool less (type& s1, type& s2)
      { return s1 < s2; }
    };

  /***
   * cmp must support get_priority (), get/set_finger (),
   * PriorityType, bool less () - true if arg1 < arg2
   */
  template <typename prior_obj, typename cmp>
  class BinHeap
  {
  public:
    typedef std::vector<prior_obj> array_type;
    typedef int position_type;

  private:
    position_type size;
    array_type	  array;

  public:
    class min_iterator
    {
      BinHeap*		heap;
      unsigned long	path;
      char		depth;
      position_type	pos;
    public:  
      min_iterator (BinHeap<prior_obj, cmp>* h = 0);

      const prior_obj& operator* ();
      bool next ();
    };

    friend class min_iterator;

  public:
    BinHeap ()
      : size (0)
    {}

    void insert (prior_obj& obj);
    
    const prior_obj& min ();

    inline min_iterator min_iter ()
    { return min_iterator (this); }

    prior_obj pop_min ();
    
    inline bool empty () const
    { return size == 0; }

    void remove (prior_obj& obj);
    
    void build ();
    
    void add (prior_obj& obj);
    
    void inc_priority (prior_obj& obj);
    
    void flush ();
    
    inline typename array_type::iterator begin ()
    { if (size) return array.at (1); else array.end (); }
    
    inline typename array_type::iterator end ()
    { if (size) return array.at (size+1); else array.end (); }
 
  private:
    void percolate_down (position_type hole);
    void remove (position_type hole);
    
    inline void resize ()
    { 
      if ((size + 1) >= position_type (array.size ())) 
	array.resize ((size + 1) * 2); 
    }
  };

  template<typename prior_obj, typename cmp>
  BinHeap<prior_obj, cmp>::min_iterator::min_iterator (BinHeap<prior_obj, cmp>* h)
    : heap (h), path (0), depth (0), pos (1)
  {}

  template<typename prior_obj, typename cmp>
  const prior_obj& BinHeap<prior_obj, cmp>::min_iterator::operator* ()
  { return heap->array[pos]; }

  template<typename prior_obj, typename cmp>
  bool BinHeap<prior_obj, cmp>::min_iterator::next ()
  {
    position_type child = pos << 1;
    unsigned long mask = (1 << depth);

    if (child <= heap->size)
      {
	if (! cmp::less (heap->array [pos], heap->array [child]))
	  {
	    pos = child;
	    depth ++;
	    path &= ~mask;
	    return true;
	  }
	if (child < heap->size)
	  {
	    if (! cmp::less (heap->array [pos], heap->array [child + 1]))
	      {
		pos = child + 1;
		depth ++;
		path |= mask;
		return true;
	      }
	  }
      }

    if (pos == heap->size)
      {
	depth --;
	pos >>= 1;
	mask >>= 1;
      }
    
    while (depth >= 0)
      {
	do
	  {
	    depth --;
	    pos >>= 1;
	    mask >>= 1;
	  }
	while ((path & mask) && depth >= 0);
	
	child = (pos << 1) + 1;
	
	if (depth >= 0 && child <= heap->size)
	  {
	    if (! cmp::less (heap->array [pos], heap->array [child]))
	      {
		pos = child;
		depth ++;
		path |= mask;
		return true;
	      }
	  }
      }

    return false;
  }

  template<typename prior_obj, typename cmp>
  void BinHeap<prior_obj, cmp>::insert (prior_obj& obj)
  {
    resize ();
    position_type hole = ++size;
    typename cmp::PriorityType& prior = cmp::get_priority (obj);

    for (; hole > 1 && cmp::less (prior, cmp::get_priority (array [hole >> 1])); hole >>= 1)
      {
	array [hole] = array [hole >> 1];
	cmp::set_finger (array [hole], hole);
      }

    array [hole] = obj;
    cmp::set_finger (obj, hole);
  }

  template<typename prior_obj, typename cmp>
  const prior_obj& BinHeap<prior_obj, cmp>::min ()
  { return array [1]; }

  template<typename prior_obj, typename cmp>
  prior_obj BinHeap<prior_obj, cmp>::pop_min ()
  {
    prior_obj min = array [1];

    remove (1);
    return min;
  }

  template<typename prior_obj, typename cmp>
  void BinHeap<prior_obj, cmp>::remove (prior_obj& obj)
  {
    position_type hole = cmp::get_finger (obj);

    if (hole != size)
      remove (hole);
    else
      array [size--] = prior_obj ();
  }

  template<typename prior_obj, typename cmp>
  void BinHeap<prior_obj, cmp>::build ()
  {
    for (position_type i = size >> 1; i > 0; i--)
      percolate_down (i);
  }

  template<typename prior_obj, typename cmp>
  void BinHeap<prior_obj, cmp>::add (prior_obj& obj)
  {
    resize ();
    array [++size] = obj;
    cmp::set_finger (obj, size);
  }

  template<typename prior_obj, typename cmp>
  void BinHeap<prior_obj, cmp>::percolate_down (position_type hole)
  {
    position_type child;
    prior_obj tmp = array [hole];
    typename cmp::PriorityType prior = cmp::get_priority (tmp);

    for (; 2*hole <= size; hole = child)
      {
	child = hole << 1;
	if (child != size && 
	    cmp::less (array [child + 1], array [child]))
	  child++;
	if (cmp::less (array [child], prior))
	  {
	    array [hole] = array [child];
	    array [hole]->get_stamp ().set_position (hole);
	  }
	else
	  break;
      }

    array [hole] = tmp;
    cmp::set_finger (array[hole], hole);
  }

  template<typename prior_obj, typename cmp>
  void BinHeap<prior_obj, cmp>::remove (position_type hole)
  {
    array [hole] = array [size--];
    cmp::set_finger (array [hole],  hole);
    cmp::init (array [size + 1]);
    percolate_down (hole);
  }

  template<typename prior_obj, typename cmp>
  void BinHeap<prior_obj, cmp>::inc_priority (prior_obj& obj)
  {
    position_type hole = cmp::get_finger (obj);

    percolate_down (hole);
  }
 
  template<typename prior_obj, typename cmp>
  void BinHeap<prior_obj, cmp>::flush ()
  {
    for (position_type i = 1; i <= size; i++)
      cmp::init (array [i]);

    size = 0;
  }
 
}; // namespace cytoskelab

#endif
