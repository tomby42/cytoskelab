/**
 * Equation Solver definition
 *
 * \file eq-solver.hpp
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

#ifndef __CYTOSKELAB_EQ_SOLVER__
#define __CYTOSKELAB_EQ_SOLVER__

namespace cytoskelab {

  typedef Registry<std::string>::twin_t EqId;
  typedef Registry<EqId>::twin_t Gid;

  /**
   *
   **/

  class EqInstance : public Atom {
    DEF_ATOM (EqInstance);

  protected:
    EqId	eq_id;
    Gid		gid;

  public:
    EqInstance ();
    virtual ~EqInstance ();
    
    DEF_TTR (EqId, eq_id);
    DEF_TTR (Gid, gid);

  };

  /**
   *
   **/

  class EqSolver : public Atom {
    DEF_ATOM (EqSolver);

  protected:
    EqId	eq_id;

  public:
    EqSolver ();
    virtual ~EqSolver ();

    virtual bool init ();
    virtual bool solve (double step_time);
  };

  /**
   *
   **/

  class EqSolverReg : public Atom {
    DEF_ATOM (EqSolver);

  protected:
    typedef std::vector<EqInstance>		vec_inst_t;
    typedef boost::shared_ptr <vec_inst_t>	vec_inst_p_t;

    struct Group {
      vec_inst_p_t instances;
      EqSolver::Ptr solver;
    };

  protected:
    typedef std::vector<Group>		 vec_grp_t;
    typedef boost::shared_ptr<vec_grp_t> vec_grp_p_t;

    Registry<std::string>::Ptr	eq_reg;
    Registry<EqId>::Ptr		group_reg;
    vec_grp_p_t			groups;

  public:
    EqSolverReg ();
    virtual ~EqSolverReg ();

    EqId reg_eq (std::string* desc);
    Gid new_group (EqId& eq_id);
    void reg_solver (EqId& eq_id, Gid& gid, APTR (EqSolver) solver);
    void reg_instance (EqId& eq_id, Gid& gid, APTR (EqInstance) e_instance);
  };

}; // cytoskelab

#endif
