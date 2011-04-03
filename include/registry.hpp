/**
 * Registry definition
 *
 * \file registry.hpp
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

#ifndef __CYTOSKELAB_REGISTRY__
#define __CYTOSKELAB_REGISTRY__

namespace cytoskelab {

  typedef unsigned long id_t;

  template <typename desc_t>
  class Registry : public Atom {
    DEF_ATOM (Registry);

  public:
    class twin_t : public std::pair<desc_t, id_t>
    {
    protected:
      typedef std::pair<desc_t, id_t> pair;

      BOOST_SERIALIZE_ACCESS;
      BOOST_SERIALIZE_BEGIN;
      BOOST_SERIALIZE_BASE (pair);
      BOOST_SERIALIZE_END;

    public:
      twin_t () 
      {}

      twin_t (desc_t fst, id_t snd)
	: std::pair<desc_t, id_t> (fst, snd)
      {}

      twin_t (desc_t* fst, id_t snd)
	: std::pair<desc_t, id_t> (*fst, snd)
      {}

      desc_t& desc ()
      { return this->first; }

      id_t& id ()
      { return this->second; }
	
    };

  protected:
    typedef boost::unordered_map<desc_t, id_t> map;
    typedef boost::shared_ptr<map> map_ptr_t;

    id_t	id_cnt;
    map_ptr_t	registry;

    BOOST_SERIALIZE_BEGIN;
    BOOST_SERIALIZE (id_cnt);
    BOOST_SERIALIZE (registry);
    BOOST_SERIALIZE_END;

  public:

    Registry();
    virtual ~Registry ();

    twin_t reg (desc_t* name);
    
  };


}; // cytoskelab

#endif
