/* Parser for GIMPLE.
   Copyright (C) 2016-2026 Free Software Foundation, Inc.

This file is part of GCC.

GCC is free software; you can redistribute it and/or modify it under
the terms of the GNU General Public License as published by the Free
Software Foundation; either version 3, or (at your option) any later
version.

GCC is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
for more details.

You should have received a copy of the GNU General Public License
along with GCC; see the file COPYING3.  If not see
<http://www.gnu.org/licenses/>.  */

#ಅನ್ತರ್ಭಾವ "config.h"
#ಅನ್ತರ್ಭಾವ "system.h"
#ಅನ್ತರ್ಭಾವ "coretypes.h"
#ಅನ್ತರ್ಭಾವ "target.h"
#ಅನ್ತರ್ಭಾವ "function.h"
#ಅನ್ತರ್ಭಾವ "c-tree.h"
#ಅನ್ತರ್ಭಾವ "timevar.h"
#ಅನ್ತರ್ಭಾವ "stringpool.h"
#ಅನ್ತರ್ಭಾವ "cgraph.h"
#ಅನ್ತರ್ಭಾವ "attribs.h"
#ಅನ್ತರ್ಭಾವ "stor-layout.h"
#ಅನ್ತರ್ಭಾವ "varasm.h"
#ಅನ್ತರ್ಭಾವ "trans-mem.h"
#ಅನ್ತರ್ಭಾವ "c-family/c-pragma.h"
#ಅನ್ತರ್ಭಾವ "c-lang.h"
#ಅನ್ತರ್ಭಾವ "c-family/c-objc.h"
#ಅನ್ತರ್ಭಾವ "plugin.h"
#ಅನ್ತರ್ಭಾವ "builtins.h"
#ಅನ್ತರ್ಭಾವ "gomp-constants.h"
#ಅನ್ತರ್ಭಾವ "c-family/c-indentation.h"
#ಅನ್ತರ್ಭಾವ "gimple-expr.h"
#ಅನ್ತರ್ಭಾವ "context.h"
#ಅನ್ತರ್ಭಾವ "gcc-rich-location.h"
#ಅನ್ತರ್ಭಾವ "c-parser.h"
#ಅನ್ತರ್ಭಾವ "tree-vrp.h"
#ಅನ್ತರ್ಭಾವ "tree-pass.h"
#ಅನ್ತರ್ಭಾವ "tree-pretty-print.h"
#ಅನ್ತರ್ಭಾವ "tree.h"
#ಅನ್ತರ್ಭಾವ "basic-block.h"
#ಅನ್ತರ್ಭಾವ "gimple.h"
#ಅನ್ತರ್ಭಾವ "gimple-pretty-print.h"
#ಅನ್ತರ್ಭಾವ "tree-ssa.h"
#ಅನ್ತರ್ಭಾವ "pass_manager.h"
#ಅನ್ತರ್ಭಾವ "tree-ssanames.h"
#ಅನ್ತರ್ಭಾವ "gimple-ssa.h"
#ಅನ್ತರ್ಭಾವ "tree-dfa.h"
#ಅನ್ತರ್ಭಾವ "internal-fn.h"
#ಅನ್ತರ್ಭಾವ "cfg.h"
#ಅನ್ತರ್ಭಾವ "cfghooks.h"
#ಅನ್ತರ್ಭಾವ "bitmap.h"
#ಅನ್ತರ್ಭಾವ "cfganal.h"
#ಅನ್ತರ್ಭಾವ "tree-cfg.h"
#ಅನ್ತರ್ಭಾವ "gimple-iterator.h"
#ಅನ್ತರ್ಭಾವ "cfgloop.h"
#ಅನ್ತರ್ಭಾವ "tree-phinodes.h"
#ಅನ್ತರ್ಭಾವ "tree-into-ssa.h"


/* GIMPLE parser state.  */

ವರ್ಗ gimple_parser
{
ಸಾರ್ವಜನಿಕ:
  gimple_parser (c_parser *p) : parser (p), edges(), current_bb(ರಿಕ್ತ) {}
  /* c_parser is not visible here, use composition and fake inheritance
     via a conversion operator.  */
  operator c_parser *() { ಪ್ರತ್ಯಾಗಮ parser; }
  c_parser *parser;

  /* CFG build state.  */
  ವರ್ಗ gimple_parser_edge
  {
  ಸಾರ್ವಜನಿಕ:
    ಪೂರ್ಣಾಙ್ಕ src;
    ಪೂರ್ಣಾಙ್ಕ dest;
    ಪೂರ್ಣಾಙ್ಕ flags;
    profile_probability probability;
  };
  auto_vec<gimple_parser_edge> edges;
  basic_block current_bb;

  ಶೂನ್ಯ ತಳ್ಳು_edge (ಪೂರ್ಣಾಙ್ಕ, ಪೂರ್ಣಾಙ್ಕ, ಪೂರ್ಣಾಙ್ಕ, profile_probability);
};

ಶೂನ್ಯ
gimple_parser::ತಳ್ಳು_edge (ಪೂರ್ಣಾಙ್ಕ src, ಪೂರ್ಣಾಙ್ಕ dest, ಪೂರ್ಣಾಙ್ಕ flags,
			  profile_probability prob)
{
  gimple_parser_edge e;
  e.src = src;
  e.dest = dest;
  e.flags = flags;
  e.probability = prob;
  edges.safe_ತಳ್ಳು (e);
}


/* Gimple parsing functions.  */
ಸ್ಥಿರ ತಾರ್ಕಿಕ c_parser_gimple_compound_statement (gimple_parser &, gimple_seq *);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_gimple_label (gimple_parser &, gimple_seq *);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_gimple_statement (gimple_parser &, gimple_seq *);
ಸ್ಥಿರ ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ c_parser_gimple_ದ್ವಿಮಾನ_expression (gimple_parser &, ವೃಕ್ಷ);
ಸ್ಥಿರ ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ c_parser_gimple_unary_expression (gimple_parser &);
ಸ್ಥಿರ ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ c_parser_gimple_postfix_expression
			(gimple_parser &, ವೃಕ್ಷ = error_mark_ಗಂಟು);
ಸ್ಥಿರ ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ c_parser_gimple_postfix_expression_after_primary
			(gimple_parser &, location_t, ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_gimple_declaration (gimple_parser &);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_gimple_goto_stmt (gimple_parser &, location_t,
				       ವೃಕ್ಷ, gimple_seq *);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_gimple_try_stmt (gimple_parser &, gimple_seq *);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_gimple_if_stmt (gimple_parser &, gimple_seq *);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_gimple_switch_stmt (gimple_parser &, gimple_seq *);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_gimple_return_stmt (gimple_parser &, gimple_seq *);
ಸ್ಥಿರ ಶೂನ್ಯ c_finish_gimple_return (location_t, ವೃಕ್ಷ);
ಸ್ಥಿರ ವೃಕ್ಷ c_parser_gimple_paren_condition (gimple_parser &);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_gimple_ಅಭಿವ್ಯಕ್ತಿ_list (gimple_parser &, vec<ವೃಕ್ಷ> *);


/* Much like parser_build_unary_op, but avoid applying default conversions.  */

ಸ್ಥಿರ c_ಅಭಿವ್ಯಕ್ತಿ
gimple_parser_build_unary_op (location_t loc,
			      ಗಣನಾ ವೃಕ್ಷ_code code, ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ arg)
{
  ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ result;

  result.original_code = code;
  result.original_type = ರಿಕ್ತ;
  result.m_decimal = 0;

  ಯದಿ (reject_gcc_builtin (arg.ಮೌಲ್ಯ))
    {
      result.ಮೌಲ್ಯ = error_mark_ಗಂಟು;
    }
  ಅನ್ಯಥಾ
    {
      result.ಮೌಲ್ಯ = build_unary_op (loc, code, arg.ಮೌಲ್ಯ, ಸತ್ಯ);

      ಯದಿ (ವೃಕ್ಷ_OVERFLOW_P (result.ಮೌಲ್ಯ) && !ವೃಕ್ಷ_OVERFLOW_P (arg.ಮೌಲ್ಯ))
	overflow_warning (loc, result.ಮೌಲ್ಯ, arg.ಮೌಲ್ಯ);
    }

  /* We are typically called when parsing a prefix token at LOC acting on
     ARG.  Reflect this by updating the source range of the result to
     start at LOC and end at the end of ARG.  */
  set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&result,
			   loc, arg.get_finish ());

  ಪ್ರತ್ಯಾಗಮ result;
}

/* See if VAL is an identifier matching __BB<num> and return <num>
   in *INDEX.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
c_parser_gimple_parse_bb_spec (ವೃಕ್ಷ val, ಪೂರ್ಣಾಙ್ಕ *index)
{
  ಯದಿ (!startswith (IDENTIFIER_POINTER (val), "__BB"))
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

  ಧ್ರುವ ವರ್ಣ *bb = IDENTIFIER_POINTER (val) + 4;
  ಯದಿ (! ISDIGIT (*bb))
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

  ವರ್ಣ *pend;
  errno = 0;
  ಧ್ರುವ unsigned long ಸಂಖ್ಯೆ = strtoul (bb, &pend, 10);
  ಯದಿ (errno == ERANGE
      || *pend != '\0'
      || ಸಂಖ್ಯೆ > INT_MAX)
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

  *index = ಸಂಖ್ಯೆ;
  ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
}

/* See if VAL is an identifier matching __BB<num> and return <num>
   in *INDEX.  Return true if so and parse also FREQUENCY of
   the edge.  */


ಸ್ಥಿರ ತಾರ್ಕಿಕ
c_parser_gimple_parse_bb_spec_edge_probability (ವೃಕ್ಷ val,
						gimple_parser &parser,
						ಪೂರ್ಣಾಙ್ಕ *index,
						profile_probability
						*probability)
{
  ತಾರ್ಕಿಕ return_p = c_parser_gimple_parse_bb_spec (val, index);
  ಯದಿ (return_p)
    {
      *probability = profile_probability::uninitialized ();
      /* Parse frequency if provided.  */
      ಯದಿ (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	{
	  ವೃಕ್ಷ f;
	  c_parser_consume_token (parser);
	  ಯದಿ (!c_parser_next_token_is (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected frequency quality");
	      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	    }

	  profile_quality quality;
	  ಧ್ರುವ ವರ್ಣ *v
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ);
	  ಯದಿ (!parse_profile_quality (v, &quality))
	    {
	      c_parser_error (parser, "unknown profile quality");
	      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	    }

	  c_parser_consume_token (parser);
	  ಯದಿ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

	  ಯದಿ (!c_parser_next_token_is (parser, CPP_ಸಂಖ್ಯೆ)
	      || (ವೃಕ್ಷ_CODE (f = c_parser_peek_token (parser)->ಮೌಲ್ಯ)
		  != INTEGER_CST))
	    {
	      c_parser_error (parser, "expected frequency value");
	      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	    }

	  unsigned ಪೂರ್ಣಾಙ್ಕ ಮೌಲ್ಯ = ವೃಕ್ಷ_INT_CST_ಕೆಳಗಿನ (f);
	  *probability = profile_probability (ಮೌಲ್ಯ, quality);

	  c_parser_consume_token (parser);
	  ಯದಿ (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

	  ಯದಿ (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	}

      ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
    }

  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

}

/* Parse the body of a function declaration marked with "__GIMPLE".  */

ಶೂನ್ಯ
c_parser_parse_gimple_body (c_parser *cparser, ವರ್ಣ *gimple_pass,
			    ಗಣನಾ c_declspec_il cdil,
			    profile_ಎಣಿಕೆ entry_bb_ಎಣಿಕೆ)
{
  gimple_parser parser (cparser);
  gimple_seq seq = ರಿಕ್ತ;
  gimple_seq body = ರಿಕ್ತ;
  ವೃಕ್ಷ stmt = ತಳ್ಳು_stmt_list ();
  ತಳ್ಳು_scope ();
  location_t loc1 = c_parser_peek_token (parser)->location;

  cfun->pass_startwith = gimple_pass;
  init_ವೃಕ್ಷ_ssa (cfun);

  ಯದಿ (cdil == cdil_gimple)
    /* While we have SSA names in the IL we do not have a CFG built yet
       and PHIs are represented using a PHI internal function.  We do
       have lowered control flow and exception handling (well, we do not
       have parser support for EH yet).  But as we still have BINDs
       we have to go through lowering again.  */
    cfun->curr_properties = PROP_gimple_any;
  ಅನ್ಯಥಾ
    {
      /* We have at least cdil_gimple_cfg.  */
      gimple_register_cfg_hooks ();
      init_empty_ವೃಕ್ಷ_cfg ();
      parser.current_bb = ENTRY_BLOCK_PTR_FOR_FN (cfun);
      /* Initialize the bare loop structure - we are going to only
         mark headers and leave the rest to fixup.  */
      set_loops_for_fn (cfun, ggc_cleared_alloc<ಸಂರಚನಾ loops> ());
      init_loops_structure (cfun, loops_for_fn (cfun), 1);
      loops_state_set (cfun, LOOPS_NEED_FIXUP|LOOPS_MAY_HAVE_MULTIPLE_LATCHES);
      cfun->curr_properties
	|= PROP_gimple_lcf | PROP_gimple_leh | PROP_cfg | PROP_loops;
      ಯದಿ (cdil == cdil_gimple_ssa)
	{
	  init_ssa_operands (cfun);
	  cfun->curr_properties |= PROP_ssa;
	}
    }

  ಯದಿ (! c_parser_gimple_compound_statement (parser, &seq)
      && cdil == cdil_gimple)
    {
      gimple *ret = gimple_build_return (ರಿಕ್ತ);
      gimple_seq_add_stmt_without_update (&seq, ret);
    }

  ವೃಕ್ಷ block = ತೆಗೆ_scope ();
  stmt = ತೆಗೆ_stmt_list (stmt);
  stmt = c_build_bind_ಅಭಿವ್ಯಕ್ತಿ (loc1, block, stmt);

  block = DECL_INITIAL (current_function_decl);
  BLOCK_SUBBLOCKS (block) = NULL_ವೃಕ್ಷ;
  BLOCK_CHAIN (block) = NULL_ವೃಕ್ಷ;
  ವೃಕ್ಷ_ASM_WRITTEN (block) = 1;

  ಯದಿ (cdil == cdil_gimple)
    {
      gbind *bind_stmt = gimple_build_bind (BIND_ಅಭಿವ್ಯಕ್ತಿ_VARS (stmt), ರಿಕ್ತ,
					    BIND_ಅಭಿವ್ಯಕ್ತಿ_BLOCK (stmt));
      gimple_bind_set_body (bind_stmt, seq);
      gimple_seq_add_stmt_without_update (&body, bind_stmt);
      gimple_set_body (current_function_decl, body);
    }
  ಅನ್ಯಥಾ
    {
      /* Control-flow and binds are lowered, record local decls.  */
      ಪ್ರತಿ (ವೃಕ್ಷ var = BIND_ಅಭಿವ್ಯಕ್ತಿ_VARS (stmt); var; var = DECL_CHAIN (var))
	ಯದಿ (VAR_P (var)
	    && !DECL_EXTERNAL (var))
	  {
	    add_local_decl (cfun, var);
	    /* When the middle-end re-gimplifies any expression we might
	       run into the assertion that we've seen the decl in a BIND.  */
	    ಯದಿ (!ವೃಕ್ಷ_STATIC (var))
	      DECL_SEEN_IN_BIND_ಅಭಿವ್ಯಕ್ತಿ_P (var) = 1;
	  }
      /* We have a CFG.  Build the edges.  */
      ಪ್ರತಿ (unsigned i = 0; i < parser.edges.length (); ++i)
	{
	  edge e = make_edge (BASIC_BLOCK_FOR_FN (cfun, parser.edges[i].src),
			      BASIC_BLOCK_FOR_FN (cfun, parser.edges[i].dest),
			      parser.edges[i].flags);
	  e->probability = parser.edges[i].probability;
	}
      /* Add edges for case labels.  */
      basic_block bb;
      FOR_EACH_BB_FN (bb, cfun)
	ಯದಿ (EDGE_ಎಣಿಕೆ (bb->succs) == 0)
	  {
	    ಯದಿ (gswitch *sw = safe_dyn_cast <gswitch *> (*gsi_last_bb (bb)))
	      ಪ್ರತಿ (unsigned i = 0; i < gimple_switch_ಅಂಕೆ_labels (sw); ++i)
		{
		  basic_block label_bb = gimple_switch_label_bb (cfun, sw, i);
		  make_edge (bb, label_bb, 0);
		}
	  }
      /* Need those for loop fixup.  */
      calculate_dominance_info (CDI_DOMINATORS);
      /* With SSA lower PHIs parsed as internal function calls and
	 update stmts.  */
      ಯದಿ (cdil == cdil_gimple_ssa)
	{
	  /* Create PHI nodes, they are parsed into __PHI internal calls
	     and update SSA operands.  */
	  FOR_EACH_BB_FN (bb, cfun)
	    {
	      gimple_stmt_iterator gsi;
	      ಪ್ರತಿ (gsi = gsi_start_bb (bb); !gsi_end_p (gsi);)
		{
		  gimple *stmt = gsi_stmt (gsi);
		  ಯದಿ (!gimple_call_internal_p (stmt, IFN_PHI))
		    ಭಙ್ಗ;

		  gphi *phi = create_phi_ಗಂಟು (gimple_call_lhs (stmt), bb);
		  ಪ್ರತಿ (unsigned i = 0; i < gimple_call_ಅಂಕೆ_args (stmt); i += 2)
		    {
		      ಪೂರ್ಣಾಙ್ಕ srcidx = ವೃಕ್ಷ_INT_CST_ಕೆಳಗಿನ (gimple_call_arg (stmt, i));
		      edge e = find_edge (BASIC_BLOCK_FOR_FN (cfun, srcidx), bb);
		      ಯದಿ (!e)
			c_parser_error (parser, "edge not found");
		      ಅನ್ಯಥಾ
			add_phi_arg (phi, gimple_call_arg (stmt, i + 1), e,
				     UNKNOWN_LOCATION);
		    }
		  gsi_remove (&gsi, ಸತ್ಯ);
		}
	      ಪ್ರತಿ (; !gsi_end_p (gsi); gsi_next (&gsi))
		update_stmt (gsi_stmt (gsi));
	    }
	  /* Fill SSA name gaps, putting them on the freelist and diagnose
	     SSA names without definition.  */
	  ಪ್ರತಿ (unsigned i = 1; i < ಅಂಕೆ_ssa_names; ++i)
	    ಯದಿ (!ssa_name (i))
	      {
		ವೃಕ್ಷ name = make_ssa_name_fn (cfun, integer_type_ಗಂಟು, ರಿಕ್ತ, i);
		release_ssa_name_fn (cfun, name);
	      }
	    ಅನ್ಯಥಾ ಯದಿ (!SSA_NAME_DEF_STMT (ssa_name (i)))
	      error ("SSA name %qE with version %d has no definition",
		     ssa_name (i), i);
	  /* No explicit virtual operands (yet).  */
	  bitmap_obstack_initialize (ರಿಕ್ತ);
	  update_ssa (TODO_update_ssa_only_virtuals);
	  bitmap_obstack_release (ರಿಕ್ತ);
	  /* ???  By flushing the freelist after virtual operand SSA rewrite
	     we keep the gaps available for re-use like needed for the
	     PR89595 testcase but then usually virtual operands would have
	     taken most of them.  The fix is obviously to make virtual
	     operands explicit in the SSA IL.  */
	  flush_ssaname_freelist ();
	}
      fix_loop_structure (ರಿಕ್ತ);
    }

  ಯದಿ (cfun->curr_properties & PROP_cfg)
    {
      ENTRY_BLOCK_PTR_FOR_FN (cfun)->ಎಣಿಕೆ = entry_bb_ಎಣಿಕೆ;
      gcov_type t = param_gimple_fe_computed_hot_bb_threshold;
      set_hot_bb_threshold (t);
      update_max_bb_ಎಣಿಕೆ ();
      cgraph_ಗಂಟು::get_create (cfun->decl);
      cgraph_edge::rebuild_edges ();
    }

  /* Perform IL validation and if any error is found abort compilation
     of this function by zapping its body.  */
  ಯದಿ ((cfun->curr_properties & PROP_cfg)
      && verify_gimple_in_cfg (cfun, ಅಸತ್ಯ, ಅಸತ್ಯ))
    init_empty_ವೃಕ್ಷ_cfg ();
  ಅನ್ಯಥಾ ಯದಿ (!(cfun->curr_properties & PROP_cfg)
	   && verify_gimple_in_seq (gimple_body (current_function_decl), ಅಸತ್ಯ))
    gimple_set_body (current_function_decl, ರಿಕ್ತ);

  dump_function (TDI_gimple, current_function_decl);
}

/* Parse a compound statement in gimple function body.

   gimple-statement:
     gimple-statement
     gimple-declaration-statement
     gimple-if-statement
     gimple-switch-statement
     gimple-labeled-statement
     gimple-expression-statement
     gimple-goto-statement
     gimple-phi-statement
     gimple-return-statement
*/

ಸ್ಥಿರ ತಾರ್ಕಿಕ
c_parser_gimple_compound_statement (gimple_parser &parser, gimple_seq *seq)
{
  ತಾರ್ಕಿಕ return_p = ಅಸತ್ಯ;

  ಯದಿ (! c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

  /* A compound statement starts with optional declarations.  */
  ಯಾವತ್ (c_parser_next_tokens_start_declaration (parser))
    {
      c_parser_gimple_declaration (parser);
      ಯದಿ (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
    }

  ಯಾವತ್ (c_parser_next_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      ಯದಿ (c_parser_error (parser))
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_BRACE, ರಿಕ್ತ);
	  ಪ್ರತ್ಯಾಗಮ return_p;
	}
      ಅನ್ಯಥಾ ಯದಿ (c_parser_next_token_is (parser, CPP_EOF))
	{
	  c_parser_error (parser, "expected declaration or statement");
	  ಪ್ರತ್ಯಾಗಮ return_p;
	}

      ವಿಕಲ್ಪ (c_parser_peek_token (parser)->type)
	{
	ಪಕ್ಷ CPP_KEYWORD:
	  ವಿಕಲ್ಪ (c_parser_peek_token (parser)->keyword)
	    {
	    ಪಕ್ಷ RID_AT_TRY:
	      c_parser_gimple_try_stmt (parser, seq);
	      ಭಙ್ಗ;
	    ಪಕ್ಷ RID_IF:
	      c_parser_gimple_if_stmt (parser, seq);
	      ಭಙ್ಗ;
	    ಪಕ್ಷ RID_SWITCH:
	      c_parser_gimple_switch_stmt (parser, seq);
	      ಭಙ್ಗ;
	    ಪಕ್ಷ RID_GOTO:
	      {
		location_t loc = c_parser_peek_token (parser)->location;
		c_parser_consume_token (parser);
		ಯದಿ (c_parser_next_token_is (parser, CPP_NAME))
		  {
		    ವೃಕ್ಷ label = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
		    c_parser_consume_token (parser);
		    c_parser_gimple_goto_stmt (parser, loc, label, seq);
		    ಯದಿ (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      ಪ್ರತ್ಯಾಗಮ return_p;
		  }
		}
	      ಭಙ್ಗ;
	    ಪಕ್ಷ RID_RETURN:
	      return_p = ಸತ್ಯ;
	      c_parser_gimple_return_stmt (parser, seq);
	      ಯದಿ (! c_parser_require (parser, CPP_SEMICOLON,
				      "expected %<;%>"))
		ಪ್ರತ್ಯಾಗಮ return_p;
	      ಯದಿ (cfun->curr_properties & PROP_cfg)
		parser.ತಳ್ಳು_edge (parser.current_bb->index, EXIT_BLOCK, 0,
				  profile_probability::uninitialized ());
	      ಭಙ್ಗ;
	    ಸ್ವಭಾವ:
	      ಗಚ್ಛ ಅಭಿವ್ಯಕ್ತಿ_stmt;
	    }
	  ಭಙ್ಗ;
	ಪಕ್ಷ CPP_NAME:
	  ಯದಿ (c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_gimple_label (parser, seq);
	      ಭಙ್ಗ;
	    }
	  ಯದಿ (c_parser_next_token_is (parser, CPP_NAME)
	      && c_parser_peek_token (parser)->id_kind == C_ID_ID
	      && strcmp (IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ),
			 "try") == 0)
	    {
	      c_parser_gimple_try_stmt (parser, seq);
	      ಭಙ್ಗ;
	    }
	  /* Basic block specification.
	     __BB (index, ...)  */
	  ಯದಿ ((cfun->curr_properties & PROP_cfg)
	      && !strcmp (IDENTIFIER_POINTER
			    (c_parser_peek_token (parser)->ಮೌಲ್ಯ), "__BB"))
	    {
	      c_parser_consume_token (parser);
	      ಯದಿ (! c_parser_require (parser, CPP_OPEN_PAREN,
				      "expected %<(%>"))
		ಪ್ರತ್ಯಾಗಮ return_p;
	      ಯದಿ (c_parser_next_token_is_not (parser, CPP_ಸಂಖ್ಯೆ))
		{
		  c_parser_error (parser, "expected block index");
		  ಪ್ರತ್ಯಾಗಮ return_p;
		}
	      ವೃಕ್ಷ tnum = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
	      ಯದಿ (ವೃಕ್ಷ_CODE (tnum) != INTEGER_CST)
		{
		  c_parser_error (parser, "expected block index");
		  ಪ್ರತ್ಯಾಗಮ return_p;
		}
	      ಪೂರ್ಣಾಙ್ಕ index = ವೃಕ್ಷ_INT_CST_ಕೆಳಗಿನ (tnum);
	      ಯದಿ (index < ಅಂಕೆ_FIXED_BLOCKS
		  || (index < last_basic_block_for_fn (cfun)
		      && BASIC_BLOCK_FOR_FN (cfun, index) != ರಿಕ್ತ))
		{
		  c_parser_error (parser, "invalid block index");
		  ಪ್ರತ್ಯಾಗಮ return_p;
		}
	      ಪೂರ್ಣಾಙ್ಕ is_loop_header_of = -1;
	      profile_ಎಣಿಕೆ bb_ಎಣಿಕೆ = profile_ಎಣಿಕೆ::uninitialized ();
	      c_parser_consume_token (parser);
	      ಯಾವತ್ (c_parser_next_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  ಯದಿ (! c_parser_next_token_is (parser, CPP_NAME))
		    {
		      c_parser_error (parser, "expected block specifier");
		      ಪ್ರತ್ಯಾಗಮ return_p;
		    }
		  /* loop_header (NUM)  */
		  ಯದಿ (!strcmp (IDENTIFIER_POINTER
			         (c_parser_peek_token (parser)->ಮೌಲ್ಯ),
			       "loop_header"))
		    {
		      c_parser_consume_token (parser);
		      ಯದಿ (! c_parser_require (parser, CPP_OPEN_PAREN,
					      "expected %<(%>"))
			ಪ್ರತ್ಯಾಗಮ return_p;
		      ವೃಕ್ಷ loop_ಅಂಕೆ;
		      ಯದಿ (! c_parser_next_token_is (parser, CPP_ಸಂಖ್ಯೆ)
			  || ವೃಕ್ಷ_CODE (loop_ಅಂಕೆ
					  = c_parser_peek_token (parser)->ಮೌಲ್ಯ)
			       != INTEGER_CST)
			{
			  c_parser_error (parser, "expected loop number");
			  ಪ್ರತ್ಯಾಗಮ return_p;
			}
		      c_parser_consume_token (parser);
		      is_loop_header_of = ವೃಕ್ಷ_INT_CST_ಕೆಳಗಿನ (loop_ಅಂಕೆ);
		      ಯದಿ (! c_parser_require (parser, CPP_CLOSE_PAREN,
					      "expected %<)%>"))
			ಪ್ರತ್ಯಾಗಮ return_p;
		    }
		  /* Parse profile: quality(value) */
		  ಅನ್ಯಥಾ
		    {
		      ವೃಕ್ಷ q;
		      profile_quality quality;
		      ವೃಕ್ಷ v = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
		      ಯದಿ (!parse_profile_quality (IDENTIFIER_POINTER (v),
						  &quality))
			{
			  c_parser_error (parser, "unknown block specifier");
			  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
			}

		      c_parser_consume_token (parser);
		      ಯದಿ (!c_parser_require (parser, CPP_OPEN_PAREN,
					     "expected %<(%>"))
			ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

		      ಯದಿ (!c_parser_next_token_is (parser, CPP_ಸಂಖ್ಯೆ)
			  || (ವೃಕ್ಷ_CODE (q = c_parser_peek_token (parser)->ಮೌಲ್ಯ)
			      != INTEGER_CST))
			{
			  c_parser_error (parser, "expected count value");
			  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
			}

		      bb_ಎಣಿಕೆ
			= profile_ಎಣಿಕೆ::from_gcov_type (ವೃಕ್ಷ_INT_CST_ಕೆಳಗಿನ (q),
							 quality);
		      c_parser_consume_token (parser);
		      ಯದಿ (! c_parser_require (parser, CPP_CLOSE_PAREN,
					      "expected %<)%>"))
			ಪ್ರತ್ಯಾಗಮ return_p;
		    }
		}
	      ಯದಿ (! c_parser_require (parser, CPP_CLOSE_PAREN,
				      "expected %<)%>")
		  || ! c_parser_require (parser, CPP_COLON,
					 "expected %<:%>"))
		ಪ್ರತ್ಯಾಗಮ return_p;

	      /* Put stmts parsed in the current block.  */
	      ಯದಿ (!gimple_seq_empty_p (*seq))
		{
		  ಯದಿ (!parser.current_bb)
		    c_parser_error (parser, "stmts without block");
		  ಅನ್ಯಥಾ
		    {
		      gimple_stmt_iterator gsi
			= gsi_start_bb (parser.current_bb);
		      gsi_ಸೇರಿಸು_seq_after_without_update (&gsi, *seq,
							   GSI_CONTINUE_LINKING);
		    }
		  *seq = ರಿಕ್ತ;
		}

	      /* Build an empty block with specified index, linking them
		 in source order.  */
	      basic_block bb = alloc_block ();
	      bb->index = index;
	      link_block (bb, (parser.current_bb ? parser.current_bb
			       : ENTRY_BLOCK_PTR_FOR_FN (cfun)));
	      ಯದಿ (basic_block_info_for_fn (cfun)->length () <= (size_t)index)
		vec_safe_grow_cleared (basic_block_info_for_fn (cfun),
				       index + 1, ಸತ್ಯ);
	      SET_BASIC_BLOCK_FOR_FN (cfun, index, bb);
	      ಯದಿ (last_basic_block_for_fn (cfun) <= index)
		last_basic_block_for_fn (cfun) = index + 1;
	      n_basic_blocks_for_fn (cfun)++;
	      ಯದಿ (parser.current_bb->index == ENTRY_BLOCK)
		parser.ತಳ್ಳು_edge (ENTRY_BLOCK, bb->index, EDGE_FALLTHRU,
				  profile_probability::always ());

	      /* We leave the proper setting to fixup.  */
	      ವರ್ಗ loop *loop_father = loops_for_fn (cfun)->ವೃಕ್ಷ_ಬೇರು;
	      /* If the new block is a loop header, allocate a loop
		 struct.  Fixup will take care of proper placement within
		 the loop tree.  */
	      ಯದಿ (is_loop_header_of != -1)
		{
		  ಯದಿ (ಸಂಖ್ಯೆ_of_loops (cfun) > (unsigned)is_loop_header_of
		      && get_loop (cfun, is_loop_header_of) != ರಿಕ್ತ)
		    {
		      c_parser_error (parser, "duplicate loop header");
		    }
		  ಅನ್ಯಥಾ
		    {
		      ವರ್ಗ loop *loop = alloc_loop ();
		      loop->ಅಂಕೆ = is_loop_header_of;
		      loop->header = bb;
		      ಯದಿ (ಸಂಖ್ಯೆ_of_loops (cfun) <= (unsigned)is_loop_header_of)
			vec_safe_grow_cleared (loops_for_fn (cfun)->larray,
					       is_loop_header_of + 1, ಸತ್ಯ);
		      (*loops_for_fn (cfun)->larray)[is_loop_header_of] = loop;
		      flow_loop_ವೃಕ್ಷ_ಗಂಟು_add (loops_for_fn (cfun)->ವೃಕ್ಷ_ಬೇರು,
					       loop);
		    }
		  loop_father = get_loop (cfun, is_loop_header_of);
		}
	      bb->loop_father = loop_father;
	      bb->ಎಣಿಕೆ = bb_ಎಣಿಕೆ;

	      /* Stmts now go to the new block.  */
	      parser.current_bb = bb;
	      ಭಙ್ಗ;
	    }
	  ಗಚ್ಛ ಅಭಿವ್ಯಕ್ತಿ_stmt;

	ಪಕ್ಷ CPP_SEMICOLON:
	  {
	    /* Empty stmt.  */
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);
	    gimple *nop = gimple_build_nop ();
	    gimple_set_location (nop, loc);
	    gimple_seq_add_stmt_without_update (seq, nop);
	    ಭಙ್ಗ;
	  }

	ಪಕ್ಷ CPP_CLOSE_PAREN:
	ಪಕ್ಷ CPP_CLOSE_SQUARE:
	  /* Avoid infinite loop in error recovery:
	     c_parser_skip_until_found stops at a closing nesting
	     delimiter without consuming it, but here we need to consume
	     it to proceed further.  */
	  c_parser_error (parser, "expected statement");
	  c_parser_consume_token (parser);
	ಭಙ್ಗ;

	ಸ್ವಭಾವ:
ಅಭಿವ್ಯಕ್ತಿ_stmt:
	  c_parser_gimple_statement (parser, seq);
	  ಯದಿ (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	    c_parser_skip_until_found (parser, CPP_SEMICOLON, ರಿಕ್ತ);
	}
    }
  c_parser_consume_token (parser);

  /* Put stmts parsed in the current block.  */
  ಯದಿ ((cfun->curr_properties & PROP_cfg)
      && !gimple_seq_empty_p (*seq))
    {
      ಯದಿ (!parser.current_bb)
	c_parser_error (parser, "stmts without block");
      ಅನ್ಯಥಾ
	{
	  gimple_stmt_iterator gsi = gsi_start_bb (parser.current_bb);
	  gsi_ಸೇರಿಸು_seq_after_without_update (&gsi, *seq,
					       GSI_CONTINUE_LINKING);
	}
      *seq = ರಿಕ್ತ;
    }

  ಪ್ರತ್ಯಾಗಮ return_p;
}

/* Parse a gimple statement.

   gimple-statement:
     gimple-call-expression
     gimple-assign-statement
     gimple-phi-statement

   gimple-assign-statement:
     gimple-unary-expression = gimple-assign-rhs

   gimple-assign-rhs:
     gimple-cast-expression
     gimple-unary-expression
     gimple-binary-expression
     gimple-call-expression

   gimple-phi-statement:
     identifier = __PHI ( label : gimple_primary-expression, ... )

   gimple-call-expr:
     gimple-primary-expression ( argument-list )

   gimple-cast-expression:
     ( type-name ) gimple-primary-expression

*/

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_gimple_statement (gimple_parser &parser, gimple_seq *seq)
{
  ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ lhs, rhs;
  gimple *assign = ರಿಕ್ತ;
  location_t loc;
  ವೃಕ್ಷ arg = NULL_ವೃಕ್ಷ;
  auto_vec<ವೃಕ್ಷ> vargs;

  lhs = c_parser_gimple_unary_expression (parser);
  loc = ಅಭಿವ್ಯಕ್ತಿ_LOCATION (lhs.ಮೌಲ್ಯ);
  rhs.set_error ();

  /* GIMPLE call statement without LHS.  */
  ಯದಿ (c_parser_next_token_is (parser, CPP_SEMICOLON)
      && ವೃಕ್ಷ_CODE (lhs.ಮೌಲ್ಯ) == CALL_ಅಭಿವ್ಯಕ್ತಿ)
    {
      gimple *call;
      call = gimple_build_call_from_ವೃಕ್ಷ (lhs.ಮೌಲ್ಯ, ರಿಕ್ತ);
      gimple_seq_add_stmt_without_update (seq, call);
      gimple_set_location (call, loc);
      ಪ್ರತ್ಯಾಗಮ;
    }

  /* All following cases are statements with LHS.  */
  ಯದಿ (! c_parser_require (parser, CPP_EQ, "expected %<=%>"))
    ಪ್ರತ್ಯಾಗಮ;

  /* Eat and ignore {v} right after the =, the has_volatile_ops is
     redundant and re-computed by the operand scanner.  */
  ಯದಿ (c_parser_next_token_is (parser, CPP_OPEN_BRACE)
      && !(c_parser_peek_token (parser)->flags & PREV_WHITE)
      && c_parser_peek_2nd_token (parser)->type == CPP_NAME
      && !(c_parser_peek_2nd_token (parser)->flags & PREV_WHITE)
      && strcmp ("v", IDENTIFIER_POINTER
			(c_parser_peek_2nd_token (parser)->ಮೌಲ್ಯ)) == 0
      && c_parser_peek_nth_token (parser, 3)->type == CPP_CLOSE_BRACE
      && !(c_parser_peek_nth_token (parser, 3)->flags & PREV_WHITE))
    {
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }

  /* Cast expression.  */
  ಯದಿ (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_typename (c_parser_peek_2nd_token (parser)))
    {
      c_parser_consume_token (parser);
      ಸಂರಚನಾ c_type_name *type_name = c_parser_type_name (parser);
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      ಯದಿ (type_name == ರಿಕ್ತ)
	ಪ್ರತ್ಯಾಗಮ;
      /* ???  The actual type used in the cast expression is ignored as
         in GIMPLE it is encoded by the type of the LHS.  */
      rhs = c_parser_gimple_postfix_expression (parser);
      ಯದಿ (lhs.ಮೌಲ್ಯ != error_mark_ಗಂಟು
	  && rhs.ಮೌಲ್ಯ != error_mark_ಗಂಟು)
	{
	  ಗಣನಾ ವೃಕ್ಷ_code code = NOP_ಅಭಿವ್ಯಕ್ತಿ;
	  ಯದಿ (FLOAT_TYPE_P (ವೃಕ್ಷ_TYPE (lhs.ಮೌಲ್ಯ))
	      && ! FLOAT_TYPE_P (ವೃಕ್ಷ_TYPE (rhs.ಮೌಲ್ಯ)))
	    code = FLOAT_ಅಭಿವ್ಯಕ್ತಿ;
	  ಅನ್ಯಥಾ ಯದಿ (! FLOAT_TYPE_P (ವೃಕ್ಷ_TYPE (lhs.ಮೌಲ್ಯ))
		   && FLOAT_TYPE_P (ವೃಕ್ಷ_TYPE (rhs.ಮೌಲ್ಯ)))
	    code = FIX_TRUNC_ಅಭಿವ್ಯಕ್ತಿ;
	  assign = gimple_build_assign (lhs.ಮೌಲ್ಯ, code, rhs.ಮೌಲ್ಯ);
	  gimple_seq_add_stmt_without_update (seq, assign);
	  gimple_set_location (assign, loc);
	  ಪ್ರತ್ಯಾಗಮ;
	}
    }

  /* Unary expression.  */
  ವಿಕಲ್ಪ (c_parser_peek_token (parser)->type)
    {
    ಪಕ್ಷ CPP_NAME:
      {
	ವೃಕ್ಷ id = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
	ಯದಿ (strcmp (IDENTIFIER_POINTER (id), "__ABS") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__ABSU") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__MIN") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__MAX") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__BIT_INSERT") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__VEC_PERM") == 0)
	  ಗಚ್ಛ build_unary_ಅಭಿವ್ಯಕ್ತಿ;
	ಭಙ್ಗ;
      }
    ಪಕ್ಷ CPP_KEYWORD:
      ಯದಿ (c_parser_peek_token (parser)->keyword != RID_REALPART
	  && c_parser_peek_token (parser)->keyword != RID_IMAGPART)
	ಭಙ್ಗ;
      /* Fallthru.  */
    ಪಕ್ಷ CPP_AND:
    ಪಕ್ಷ CPP_PLUS:
    ಪಕ್ಷ CPP_MINUS:
    ಪಕ್ಷ CPP_COMPL:
    ಪಕ್ಷ CPP_NOT:
    ಪಕ್ಷ CPP_MULT: /* pointer deref */
    build_unary_ಅಭಿವ್ಯಕ್ತಿ:
      rhs = c_parser_gimple_unary_expression (parser);
      ಯದಿ (rhs.ಮೌಲ್ಯ != error_mark_ಗಂಟು)
	{
	  assign = gimple_build_assign (lhs.ಮೌಲ್ಯ, rhs.ಮೌಲ್ಯ);
	  gimple_set_location (assign, loc);
	  gimple_seq_add_stmt_without_update (seq, assign);
	}
      ಪ್ರತ್ಯಾಗಮ;

    ಸ್ವಭಾವ:;
    }

  /* GIMPLE PHI statement.  */
  ಯದಿ (c_parser_next_token_is_keyword (parser, RID_PHI))
    {
      c_parser_consume_token (parser);

      ಯದಿ (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	ಪ್ರತ್ಯಾಗಮ;

      ಯದಿ (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	c_parser_consume_token (parser);

      ಯಾವತ್ (c_parser_next_token_is_not (parser, CPP_CLOSE_PAREN))
	{
	  ಯದಿ (c_parser_next_token_is (parser, CPP_NAME)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      arg = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
	      c_parser_consume_token (parser);
	      ಯದಿ (c_parser_next_token_is (parser, CPP_COLON))
		c_parser_consume_token (parser);
	      ಪೂರ್ಣಾಙ್ಕ src_index = -1;
	      ಯದಿ (!c_parser_gimple_parse_bb_spec (arg, &src_index))
		c_parser_error (parser, "invalid source block specification");
	      vargs.safe_ತಳ್ಳು (size_int (src_index));
	    }
	  ಅನ್ಯಥಾ ಯದಿ (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  ಅನ್ಯಥಾ
	    {
	      arg = c_parser_gimple_unary_expression (parser).ಮೌಲ್ಯ;
	      vargs.safe_ತಳ್ಳು (arg);
	    }
	}

      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");

      /* Build internal function for PHI.  */
      gcall *call_stmt = gimple_build_call_internal_vec (IFN_PHI, vargs);
      gimple_call_set_lhs (call_stmt, lhs.ಮೌಲ್ಯ);
      gimple_set_location (call_stmt, UNKNOWN_LOCATION);
      gimple_seq_add_stmt_without_update (seq, call_stmt);
      ಪ್ರತ್ಯಾಗಮ;
    }

  /* GIMPLE call with lhs.  */
  ಯದಿ (c_parser_next_token_is (parser, CPP_DOT)
      || (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN
	  && lookup_name (c_parser_peek_token (parser)->ಮೌಲ್ಯ)))
    {
      rhs = c_parser_gimple_unary_expression (parser);
      ಯದಿ (rhs.ಮೌಲ್ಯ != error_mark_ಗಂಟು)
	{
	  gimple *call = gimple_build_call_from_ವೃಕ್ಷ (rhs.ಮೌಲ್ಯ, ರಿಕ್ತ);
	  gimple_call_set_lhs (call, lhs.ಮೌಲ್ಯ);
	  gimple_seq_add_stmt_without_update (seq, call);
	  gimple_set_location (call, loc);
	}
      ಪ್ರತ್ಯಾಗಮ;
    }

  rhs = c_parser_gimple_ದ್ವಿಮಾನ_expression (parser, ವೃಕ್ಷ_TYPE (lhs.ಮೌಲ್ಯ));
  ಯದಿ (lhs.ಮೌಲ್ಯ != error_mark_ಗಂಟು
      && rhs.ಮೌಲ್ಯ != error_mark_ಗಂಟು)
    {
      /* If we parsed an identifier and the next token  is a '?' then parse
	 a conditional expression.  */
      ಯದಿ (SSA_VAR_P (rhs.ಮೌಲ್ಯ) && c_parser_next_token_is (parser, CPP_QUERY))
	{
	  ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ trueval, falseval;
	  c_parser_consume_token (parser);
	  trueval = c_parser_gimple_postfix_expression (parser);
	  falseval.set_error ();
	  ಯದಿ (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    falseval = c_parser_gimple_postfix_expression (parser);
	  ಯದಿ (trueval.ಮೌಲ್ಯ == error_mark_ಗಂಟು
	      || falseval.ಮೌಲ್ಯ == error_mark_ಗಂಟು)
	    ಪ್ರತ್ಯಾಗಮ;
	  rhs.ಮೌಲ್ಯ = build3_loc (loc,
				  VECTOR_TYPE_P (ವೃಕ್ಷ_TYPE (rhs.ಮೌಲ್ಯ))
				  ? VEC_COND_ಅಭಿವ್ಯಕ್ತಿ : COND_ಅಭಿವ್ಯಕ್ತಿ,
				  ವೃಕ್ಷ_TYPE (trueval.ಮೌಲ್ಯ),
				  rhs.ಮೌಲ್ಯ, trueval.ಮೌಲ್ಯ, falseval.ಮೌಲ್ಯ);
	}
      ಯದಿ (get_gimple_rhs_class (ವೃಕ್ಷ_CODE (rhs.ಮೌಲ್ಯ)) == GIMPLE_INVALID_RHS)
	{
	  c_parser_error (parser, "unexpected RHS for assignment");
	  ಪ್ರತ್ಯಾಗಮ;
	}
      assign = gimple_build_assign (lhs.ಮೌಲ್ಯ, rhs.ಮೌಲ್ಯ);
      gimple_seq_add_stmt_without_update (seq, assign);
      gimple_set_location (assign, loc);
    }
  ಪ್ರತ್ಯಾಗಮ;
}

/* A mapping between an identifier to a tree code for binary operations. */
ಸ್ಥಿರ ಧ್ರುವ std::pair<ಧ್ರುವ ವರ್ಣ *, ವೃಕ್ಷ_code> gimple_ದ್ವಿಮಾನ_identifier_code[] =
  {
    {"__MULT_HIGHPART", MULT_HIGHPART_ಅಭಿವ್ಯಕ್ತಿ},
    {"__UNLT", UNLT_ಅಭಿವ್ಯಕ್ತಿ},
    {"__UNLE", UNLE_ಅಭಿವ್ಯಕ್ತಿ},
    {"__UNGT", UNGT_ಅಭಿವ್ಯಕ್ತಿ},
    {"__UNGE", UNGE_ಅಭಿವ್ಯಕ್ತಿ},
    {"__UNEQ", UNEQ_ಅಭಿವ್ಯಕ್ತಿ},
    {"__UNORDERED", UNORDERED_ಅಭಿವ್ಯಕ್ತಿ},
    {"__ORDERED", ORDERED_ಅಭಿವ್ಯಕ್ತಿ},
    {"__LTGT", LTGT_ಅಭಿವ್ಯಕ್ತಿ},
    {"__FLOOR_DIV", FLOOR_DIV_ಅಭಿವ್ಯಕ್ತಿ},
    {"__ROUND_DIV", ROUND_DIV_ಅಭಿವ್ಯಕ್ತಿ},
    {"__EXACT_DIV", EXACT_DIV_ಅಭಿವ್ಯಕ್ತಿ},
    {"__CEIL_DIV", CEIL_DIV_ಅಭಿವ್ಯಕ್ತಿ},
    {"__FLOOR_MOD", FLOOR_MOD_ಅಭಿವ್ಯಕ್ತಿ},
    {"__ROUND_MOD", ROUND_MOD_ಅಭಿವ್ಯಕ್ತಿ},
    {"__CEIL_MOD", CEIL_MOD_ಅಭಿವ್ಯಕ್ತಿ},
    {"__ROTATE_LEFT", LROTATE_ಅಭಿವ್ಯಕ್ತಿ},
    {"__ROTATE_RIGHT", RROTATE_ಅಭಿವ್ಯಕ್ತಿ},
  };

/* Parse gimple binary expr.

   gimple-binary-expression:
     gimple-unary-expression * gimple-unary-expression
     gimple-unary-expression __MULT_HIGHPART gimple-unary-expression
     gimple-unary-expression / gimple-unary-expression
     gimple-unary-expression % gimple-unary-expression
     gimple-unary-expression + gimple-unary-expression
     gimple-unary-expression - gimple-unary-expression
     gimple-unary-expression << gimple-unary-expression
     gimple-unary-expression >> gimple-unary-expression
     gimple-unary-expression < gimple-unary-expression
     gimple-unary-expression > gimple-unary-expression
     gimple-unary-expression <= gimple-unary-expression
     gimple-unary-expression >= gimple-unary-expression
     gimple-unary-expression == gimple-unary-expression
     gimple-unary-expression != gimple-unary-expression
     gimple-unary-expression & gimple-unary-expression
     gimple-unary-expression ^ gimple-unary-expression
     gimple-unary-expression | gimple-unary-expression

*/

ಸ್ಥಿರ c_ಅಭಿವ್ಯಕ್ತಿ
c_parser_gimple_ದ್ವಿಮಾನ_expression (gimple_parser &parser, ವೃಕ್ಷ ret_type)
{
  /* Location of the binary operator.  */
  ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ ret, lhs, rhs;
  ಗಣನಾ ವೃಕ್ಷ_code code = ERROR_MARK;
  ret.set_error ();
  lhs = c_parser_gimple_postfix_expression (parser, ret_type);
  ಯದಿ (c_parser_error (parser))
    ಪ್ರತ್ಯಾಗಮ ret;
  ವಿಕಲ್ಪ (c_parser_peek_token (parser)->type)
    {
    ಪಕ್ಷ CPP_MULT:
      code = MULT_ಅಭಿವ್ಯಕ್ತಿ;
      ಭಙ್ಗ;
    ಪಕ್ಷ CPP_DIV:
      code = TRUNC_DIV_ಅಭಿವ್ಯಕ್ತಿ;
      ಭಙ್ಗ;
    ಪಕ್ಷ CPP_MOD:
      code = TRUNC_MOD_ಅಭಿವ್ಯಕ್ತಿ;
      ಭಙ್ಗ;
    ಪಕ್ಷ CPP_PLUS:
      ಯದಿ (POINTER_TYPE_P (ವೃಕ್ಷ_TYPE (lhs.ಮೌಲ್ಯ)))
	code = POINTER_PLUS_ಅಭಿವ್ಯಕ್ತಿ;
      ಅನ್ಯಥಾ
	code = PLUS_ಅಭಿವ್ಯಕ್ತಿ;
      ಭಙ್ಗ;
    ಪಕ್ಷ CPP_MINUS:
      ಯದಿ (POINTER_TYPE_P (ವೃಕ್ಷ_TYPE (lhs.ಮೌಲ್ಯ)))
	code = POINTER_DIFF_ಅಭಿವ್ಯಕ್ತಿ;
      ಅನ್ಯಥಾ
	code = MINUS_ಅಭಿವ್ಯಕ್ತಿ;
      ಭಙ್ಗ;
    ಪಕ್ಷ CPP_LSHIFT:
      code = LSHIFT_ಅಭಿವ್ಯಕ್ತಿ;
      ಭಙ್ಗ;
    ಪಕ್ಷ CPP_RSHIFT:
      code = RSHIFT_ಅಭಿವ್ಯಕ್ತಿ;
      ಭಙ್ಗ;
    ಪಕ್ಷ CPP_LESS:
      code = LT_ಅಭಿವ್ಯಕ್ತಿ;
      ಭಙ್ಗ;
    ಪಕ್ಷ CPP_GREATER:
      code = GT_ಅಭಿವ್ಯಕ್ತಿ;
      ಭಙ್ಗ;
    ಪಕ್ಷ CPP_LESS_EQ:
      code = LE_ಅಭಿವ್ಯಕ್ತಿ;
      ಭಙ್ಗ;
    ಪಕ್ಷ CPP_GREATER_EQ:
      code = GE_ಅಭಿವ್ಯಕ್ತಿ;
      ಭಙ್ಗ;
    ಪಕ್ಷ CPP_EQ_EQ:
      code = EQ_ಅಭಿವ್ಯಕ್ತಿ;
      ಭಙ್ಗ;
    ಪಕ್ಷ CPP_NOT_EQ:
      code = NE_ಅಭಿವ್ಯಕ್ತಿ;
      ಭಙ್ಗ;
    ಪಕ್ಷ CPP_AND:
      code = BIT_AND_ಅಭಿವ್ಯಕ್ತಿ;
      ಭಙ್ಗ;
    ಪಕ್ಷ CPP_XOR:
      code = BIT_XOR_ಅಭಿವ್ಯಕ್ತಿ;
      ಭಙ್ಗ;
    ಪಕ್ಷ CPP_OR:
      code = BIT_IOR_ಅಭಿವ್ಯಕ್ತಿ;
      ಭಙ್ಗ;
    ಪಕ್ಷ CPP_AND_AND:
      c_parser_error (parser, "%<&&%> not valid in GIMPLE");
      ಪ್ರತ್ಯಾಗಮ ret;
    ಪಕ್ಷ CPP_OR_OR:
      c_parser_error (parser, "%<||%> not valid in GIMPLE");
      ಪ್ರತ್ಯಾಗಮ ret;
    ಪಕ್ಷ CPP_NAME:
      {
	ವೃಕ್ಷ id = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
	ಪ್ರತಿ (auto &p : gimple_ದ್ವಿಮಾನ_identifier_code)
	  {
	    ಯದಿ (strcmp (IDENTIFIER_POINTER (id), p.first) == 0)
	      {
		code = p.second;
		ಭಙ್ಗ;
	      }
	  }
	ಯದಿ (code != ERROR_MARK)
	  ಭಙ್ಗ;
      }
      /* Fallthru.  */
    ಸ್ವಭಾವ:
      /* Not a binary expression.  */
      ಪ್ರತ್ಯಾಗಮ lhs;
    }
  location_t ret_loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  rhs = c_parser_gimple_postfix_expression (parser);
  ಯದಿ (lhs.ಮೌಲ್ಯ != error_mark_ಗಂಟು && rhs.ಮೌಲ್ಯ != error_mark_ಗಂಟು)
    ret.ಮೌಲ್ಯ = build2_loc (ret_loc, code, ret_type, lhs.ಮೌಲ್ಯ, rhs.ಮೌಲ್ಯ);
  ಪ್ರತ್ಯಾಗಮ ret;
}

/* Parse a gimple parentized binary expression.  */

ಸ್ಥಿರ c_ಅಭಿವ್ಯಕ್ತಿ
c_parser_gimple_parentized_ದ್ವಿಮಾನ_expression (gimple_parser &parser,
					      location_t op_loc,
					      ವೃಕ್ಷ_code code)
{
  ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ ret;
  ret.set_error ();

  c_parser_consume_token (parser);
  ಯದಿ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    ಪ್ರತ್ಯಾಗಮ ret;
  c_ಅಭಿವ್ಯಕ್ತಿ op1 = c_parser_gimple_postfix_expression (parser);
  ಯದಿ (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    ಪ್ರತ್ಯಾಗಮ ret;
  c_ಅಭಿವ್ಯಕ್ತಿ op2 = c_parser_gimple_postfix_expression (parser);
  ಯದಿ (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    ಪ್ರತ್ಯಾಗಮ ret;

  ಯದಿ (op1.ಮೌಲ್ಯ != error_mark_ಗಂಟು && op2.ಮೌಲ್ಯ != error_mark_ಗಂಟು)
    ret.ಮೌಲ್ಯ = build2_loc (op_loc,
			    code, ವೃಕ್ಷ_TYPE (op1.ಮೌಲ್ಯ), op1.ಮೌಲ್ಯ, op2.ಮೌಲ್ಯ);
  ಪ್ರತ್ಯಾಗಮ ret;
}

/* Parse a gimple parentized binary expression.  */

ಸ್ಥಿರ c_ಅಭಿವ್ಯಕ್ತಿ
c_parser_gimple_parentized_ternary_expression (gimple_parser &parser,
					       location_t op_loc,
					       ವೃಕ್ಷ_code code)
{
  ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ ret;
  ret.set_error ();

  c_parser_consume_token (parser);
  ಯದಿ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    ಪ್ರತ್ಯಾಗಮ ret;
  c_ಅಭಿವ್ಯಕ್ತಿ op1 = c_parser_gimple_postfix_expression (parser);
  ಯದಿ (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    ಪ್ರತ್ಯಾಗಮ ret;
  c_ಅಭಿವ್ಯಕ್ತಿ op2 = c_parser_gimple_postfix_expression (parser);
  ಯದಿ (!c_parser_require (parser, CPP_COMMA, "expected %<)%>"))
    ಪ್ರತ್ಯಾಗಮ ret;
  c_ಅಭಿವ್ಯಕ್ತಿ op3 = c_parser_gimple_postfix_expression (parser);
  ಯದಿ (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    ಪ್ರತ್ಯಾಗಮ ret;

  ಯದಿ (op1.ಮೌಲ್ಯ != error_mark_ಗಂಟು
      && op2.ಮೌಲ್ಯ != error_mark_ಗಂಟು
      && op3.ಮೌಲ್ಯ != error_mark_ಗಂಟು)
    ret.ಮೌಲ್ಯ = build3_loc (op_loc,
			    code, ವೃಕ್ಷ_TYPE (op1.ಮೌಲ್ಯ),
			    op1.ಮೌಲ್ಯ, op2.ಮೌಲ್ಯ, op3.ಮೌಲ್ಯ);
  ಪ್ರತ್ಯಾಗಮ ret;
}

/* Parse gimple unary expression.

   gimple-unary-expression:
     gimple-postfix-expression
     unary-operator gimple-postfix-expression

   unary-operator: one of
     & * + - ~ abs_expr
*/

ಸ್ಥಿರ c_ಅಭಿವ್ಯಕ್ತಿ
c_parser_gimple_unary_expression (gimple_parser &parser)
{
  ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ ret, op;
  location_t op_loc = c_parser_peek_token (parser)->location;
  location_t finish;
  ret.set_error ();
  ವಿಕಲ್ಪ (c_parser_peek_token (parser)->type)
    {
    ಪಕ್ಷ CPP_AND:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      mark_exp_read (op.ಮೌಲ್ಯ);
      ಪ್ರತ್ಯಾಗಮ gimple_parser_build_unary_op (op_loc, ADDR_ಅಭಿವ್ಯಕ್ತಿ, op);
    ಪಕ್ಷ CPP_MULT:
      {
	c_parser_consume_token (parser);
	op = c_parser_gimple_postfix_expression (parser);
	ಯದಿ (op.ಮೌಲ್ಯ == error_mark_ಗಂಟು)
	  ಪ್ರತ್ಯಾಗಮ ret;
	ಯದಿ (! POINTER_TYPE_P (ವೃಕ್ಷ_TYPE (op.ಮೌಲ್ಯ)))
	  {
	    error_at (op_loc, "expected pointer as argument of unary %<*%>");
	    ಪ್ರತ್ಯಾಗಮ ret;
	  }
	finish = op.get_finish ();
	location_t combined_loc = make_location (op_loc, op_loc, finish);
	ret.ಮೌಲ್ಯ = build_simple_mem_ref_loc (combined_loc, op.ಮೌಲ್ಯ);
	ವೃಕ್ಷ_SIDE_EFFECTS (ret.ಮೌಲ್ಯ)
	  = ವೃಕ್ಷ_THIS_VOLATILE (ret.ಮೌಲ್ಯ)
	  = TYPE_VOLATILE (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (op.ಮೌಲ್ಯ)));
	ret.src_range.m_start = op_loc;
	ret.src_range.m_finish = finish;
	ಪ್ರತ್ಯಾಗಮ ret;
      }
    ಪಕ್ಷ CPP_PLUS:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      ಪ್ರತ್ಯಾಗಮ gimple_parser_build_unary_op (op_loc, CONVERT_ಅಭಿವ್ಯಕ್ತಿ, op);
    ಪಕ್ಷ CPP_MINUS:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      ಪ್ರತ್ಯಾಗಮ gimple_parser_build_unary_op (op_loc, NEGATE_ಅಭಿವ್ಯಕ್ತಿ, op);
    ಪಕ್ಷ CPP_COMPL:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      ಪ್ರತ್ಯಾಗಮ gimple_parser_build_unary_op (op_loc, BIT_NOT_ಅಭಿವ್ಯಕ್ತಿ, op);
    ಪಕ್ಷ CPP_NOT:
      c_parser_error (parser, "%<!%> not valid in GIMPLE");
      ಪ್ರತ್ಯಾಗಮ ret;
    ಪಕ್ಷ CPP_KEYWORD:
      ವಿಕಲ್ಪ (c_parser_peek_token (parser)->keyword)
	{
	ಪಕ್ಷ RID_REALPART:
	  c_parser_consume_token (parser);
	  op = c_parser_gimple_postfix_expression (parser);
	  ಪ್ರತ್ಯಾಗಮ gimple_parser_build_unary_op (op_loc, REALPART_ಅಭಿವ್ಯಕ್ತಿ, op);
	ಪಕ್ಷ RID_IMAGPART:
	  c_parser_consume_token (parser);
	  op = c_parser_gimple_postfix_expression (parser);
	  ಪ್ರತ್ಯಾಗಮ gimple_parser_build_unary_op (op_loc, IMAGPART_ಅಭಿವ್ಯಕ್ತಿ, op);
	ಸ್ವಭಾವ:
	  ಪ್ರತ್ಯಾಗಮ c_parser_gimple_postfix_expression (parser);
	}
    ಪಕ್ಷ CPP_NAME:
	{
	  ವೃಕ್ಷ id = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
	  ಯದಿ (strcmp (IDENTIFIER_POINTER (id), "__ABS") == 0)
	    {
	      c_parser_consume_token (parser);
	      op = c_parser_gimple_postfix_expression (parser);
	      ಪ್ರತ್ಯಾಗಮ gimple_parser_build_unary_op (op_loc, ABS_ಅಭಿವ್ಯಕ್ತಿ, op);
	    }
	  ಅನ್ಯಥಾ ಯದಿ (strcmp (IDENTIFIER_POINTER (id), "__ABSU") == 0)
	    {
	      c_parser_consume_token (parser);
	      op = c_parser_gimple_postfix_expression (parser);
	      ಪ್ರತ್ಯಾಗಮ gimple_parser_build_unary_op (op_loc, ABSU_ಅಭಿವ್ಯಕ್ತಿ, op);
	    }
	  ಅನ್ಯಥಾ ಯದಿ (strcmp (IDENTIFIER_POINTER (id), "__MIN") == 0)
	    ಪ್ರತ್ಯಾಗಮ c_parser_gimple_parentized_ದ್ವಿಮಾನ_expression (parser,
								 op_loc,
								 MIN_ಅಭಿವ್ಯಕ್ತಿ);
	  ಅನ್ಯಥಾ ಯದಿ (strcmp (IDENTIFIER_POINTER (id), "__MAX") == 0)
	    ಪ್ರತ್ಯಾಗಮ c_parser_gimple_parentized_ದ್ವಿಮಾನ_expression (parser,
								 op_loc,
								 MAX_ಅಭಿವ್ಯಕ್ತಿ);
	  ಅನ್ಯಥಾ ಯದಿ (strcmp (IDENTIFIER_POINTER (id), "__VEC_PERM") == 0)
	    ಪ್ರತ್ಯಾಗಮ c_parser_gimple_parentized_ternary_expression
			(parser, op_loc, VEC_PERM_ಅಭಿವ್ಯಕ್ತಿ);
	  ಅನ್ಯಥಾ ಯದಿ (strcmp (IDENTIFIER_POINTER (id), "__BIT_INSERT") == 0)
	    {
	      /* __BIT_INSERT '(' postfix-expression, postfix-expression,
			          integer ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      ಯದಿ (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_ಅಭಿವ್ಯಕ್ತಿ op0 = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_ಅಭಿವ್ಯಕ್ತಿ op1 = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_ಅಭಿವ್ಯಕ್ತಿ op2 = c_parser_gimple_postfix_expression (parser);
		  ಯದಿ (ವೃಕ್ಷ_CODE (op2.ಮೌಲ್ಯ) != INTEGER_CST
		      || !int_fits_type_p (op2.ಮೌಲ್ಯ, bitsizetype))
		    c_parser_error (parser, "expected constant offset");
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  ಯದಿ (op0.ಮೌಲ್ಯ != error_mark_ಗಂಟು
		      && op1.ಮೌಲ್ಯ != error_mark_ಗಂಟು
		      && ವೃಕ್ಷ_CODE (op2.ಮೌಲ್ಯ) == INTEGER_CST)
		    ret.ಮೌಲ್ಯ = build3_loc (loc, BIT_ಸೇರಿಸು_ಅಭಿವ್ಯಕ್ತಿ,
					    ವೃಕ್ಷ_TYPE (op0.ಮೌಲ್ಯ),
					    op0.ಮೌಲ್ಯ, op1.ಮೌಲ್ಯ,
					    fold_convert (bitsizetype,
							  op2.ಮೌಲ್ಯ));
		}
	      ಪ್ರತ್ಯಾಗಮ ret;
	    }
	  ಅನ್ಯಥಾ
	    ಪ್ರತ್ಯಾಗಮ c_parser_gimple_postfix_expression (parser);
	}
    ಸ್ವಭಾವ:
      ಪ್ರತ್ಯಾಗಮ c_parser_gimple_postfix_expression (parser);
    }
}

/* Decompose ID into base name (ID until ver_offset) and VERSION.  Return
   true if ID matches a SSA name.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
c_parser_parse_ssa_name_id (ವೃಕ್ಷ id, unsigned *version, unsigned *ver_offset)
{
  ಧ್ರುವ ವರ್ಣ *token = IDENTIFIER_POINTER (id);
  ಧ್ರುವ ವರ್ಣ *var_version = strrchr (token, '_');
  ಯದಿ (! var_version)
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

  *ver_offset = var_version - token;
  ಪ್ರತಿ (ಧ್ರುವ ವರ್ಣ *p = var_version + 1; *p; ++p)
    ಯದಿ (! ISDIGIT (*p))
      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
  *version = atoi (var_version + 1);
  ಪ್ರತ್ಯಾಗಮ *version > 0;
}

/* Get at the actual SSA name ID with VERSION starting at VER_OFFSET.
   TYPE is the type if the SSA name is being declared.  */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_parse_ssa_name (gimple_parser &parser,
			 ವೃಕ್ಷ id, ವೃಕ್ಷ type, unsigned version,
			 unsigned ver_offset)
{
  ವೃಕ್ಷ name = NULL_ವೃಕ್ಷ;
  ಧ್ರುವ ವರ್ಣ *token = IDENTIFIER_POINTER (id);

  ಯದಿ (ver_offset == 0)
    {
      /* Anonymous unnamed SSA name.  */
      ಯದಿ (version < ಅಂಕೆ_ssa_names)
	name = ssa_name (version);
      ಯದಿ (! name)
	{
	  ಯದಿ (! type)
	    {
	      c_parser_error (parser, "SSA name undeclared");
	      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	    }
	  name = make_ssa_name_fn (cfun, type, ರಿಕ್ತ, version);
	}
    }
  ಅನ್ಯಥಾ
    {
      ಯದಿ (version < ಅಂಕೆ_ssa_names)
	name = ssa_name (version);
      ಯದಿ (! name)
	{
	  /* Separate var name from version.  */
	  ವರ್ಣ *var_name = XNEWVEC (ವರ್ಣ, ver_offset + 1);
	  memcpy (var_name, token, ver_offset);
	  var_name[ver_offset] = '\0';
	  /* lookup for parent decl.  */
	  id = get_identifier (var_name);
	  ವೃಕ್ಷ parent = lookup_name (id);
	  XDELETEVEC (var_name);
	  ಯದಿ (! parent || parent == error_mark_ಗಂಟು)
	    {
	      c_parser_error (parser, "base variable or SSA name undeclared");
	      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	    }
	  ಯದಿ (!(VAR_P (parent)
		|| ವೃಕ್ಷ_CODE (parent) == PARM_DECL
		|| ವೃಕ್ಷ_CODE (parent) == RESULT_DECL))
	    {
	      error ("invalid base %qE for SSA name", parent);
	      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	    }
	  name = make_ssa_name_fn (cfun, parent,
				   gimple_build_nop (), version);
	}
    }

  ಪ್ರತ್ಯಾಗಮ name;
}

/* Parse a gimple call to an internal function.

   gimple-call-internal:
     . identifier ( gimple-argument-expression-list[opt] )  */

ಸ್ಥಿರ ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ
c_parser_gimple_call_internal (gimple_parser &parser)
{
  ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ;
  ಅಭಿವ್ಯಕ್ತಿ.set_error ();

  gcc_assert (c_parser_next_token_is (parser, CPP_DOT));
  c_parser_consume_token (parser);
  location_t loc = c_parser_peek_token (parser)->location;
  ಯದಿ (!c_parser_next_token_is (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_kind != C_ID_ID)
    {
      c_parser_error (parser, "expecting internal function name");
      ಪ್ರತ್ಯಾಗಮ ಅಭಿವ್ಯಕ್ತಿ;
    }
  ವೃಕ್ಷ id = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
  internal_fn ifn = lookup_internal_fn (IDENTIFIER_POINTER (id));
  c_parser_consume_token (parser);
  ಯದಿ (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    {
      auto_vec<ವೃಕ್ಷ> exprlist;
      ಯದಿ (!c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_gimple_ಅಭಿವ್ಯಕ್ತಿ_list (parser, &exprlist);
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      ಯದಿ (ifn == IFN_LAST)
	error_at (loc, "unknown internal function %qE", id);
      ಅನ್ಯಥಾ
	{
	  ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = build_call_ಅಭಿವ್ಯಕ್ತಿ_internal_loc_array
	    (loc, ifn, void_type_ಗಂಟು, exprlist.length (),
	     exprlist.address ());
	  ಅಭಿವ್ಯಕ್ತಿ.original_code = ERROR_MARK;
	  ಅಭಿವ್ಯಕ್ತಿ.original_type = ರಿಕ್ತ;
	  ಅಭಿವ್ಯಕ್ತಿ.m_decimal = 0;
	}
    }
  ಪ್ರತ್ಯಾಗಮ ಅಭಿವ್ಯಕ್ತಿ;
}

/* Parse '<' type [',' alignment] '>' and return a type on success
   and NULL_TREE on error.  */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_gimple_typespec (gimple_parser &parser)
{
  ಸಂರಚನಾ c_type_name *type_name = ರಿಕ್ತ;
  ವೃಕ್ಷ alignment = NULL_ವೃಕ್ಷ;
  ಯದಿ (c_parser_require (parser, CPP_LESS, "expected %<<%>"))
    {
      type_name = c_parser_type_name (parser);
      /* Optional alignment.  */
      ಯದಿ (c_parser_next_token_is (parser, CPP_COMMA))
	{
	  c_parser_consume_token (parser);
	  alignment
	      = c_parser_gimple_postfix_expression (parser).ಮೌಲ್ಯ;
	}
      c_parser_skip_until_found (parser,
				 CPP_GREATER, "expected %<>%>");
    }
  ಯದಿ (!type_name)
    ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
  ವೃಕ್ಷ tem;
  ವೃಕ್ಷ type = groktypename (type_name, &tem, ರಿಕ್ತ);
  ಯದಿ (alignment)
    type = build_aligned_type (type, ವೃಕ್ಷ_to_uhwi (alignment));
  ಪ್ರತ್ಯಾಗಮ type;
}

/* Parse gimple postfix expression.

   gimple-postfix-expression:
     gimple-primary-expression
     gimple-primary-expression [ gimple-primary-expression ]
     gimple-primary-expression ( gimple-argument-expression-list[opt] )
     gimple-postfix-expression . identifier
     gimple-postfix-expression -> identifier

   gimple-argument-expression-list:
     gimple-unary-expression
     gimple-argument-expression-list , gimple-unary-expression

   gimple-primary-expression:
     identifier
     constant
     string-literal
     constructor
     gimple-call-internal

*/

ಸ್ಥಿರ ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ
c_parser_gimple_postfix_expression (gimple_parser &parser, ವೃಕ್ಷ ret_type)
{
  location_t loc = c_parser_peek_token (parser)->location;
  source_range tok_range = c_parser_peek_token (parser)->get_range ();
  ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ;
  ಅಭಿವ್ಯಕ್ತಿ.set_error ();
  ವಿಕಲ್ಪ (c_parser_peek_token (parser)->type)
    {
    ಪಕ್ಷ CPP_ಸಂಖ್ಯೆ:
      ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
      set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&ಅಭಿವ್ಯಕ್ತಿ, tok_range);
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      ಭಙ್ಗ;
    ಪಕ್ಷ CPP_CHAR:
    ಪಕ್ಷ CPP_CHAR16:
    ಪಕ್ಷ CPP_CHAR32:
    ಪಕ್ಷ CPP_UTF8CHAR:
    ಪಕ್ಷ CPP_WCHAR:
      ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
      set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&ಅಭಿವ್ಯಕ್ತಿ, tok_range);
      c_parser_consume_token (parser);
      ಭಙ್ಗ;
    ಪಕ್ಷ CPP_STRING:
    ಪಕ್ಷ CPP_STRING16:
    ಪಕ್ಷ CPP_STRING32:
    ಪಕ್ಷ CPP_WSTRING:
    ಪಕ್ಷ CPP_UTF8STRING:
      ಅಭಿವ್ಯಕ್ತಿ = c_parser_string_literal (parser, ಅಸತ್ಯ, ಸತ್ಯ);
      ಭಙ್ಗ;
    ಪಕ್ಷ CPP_DOT:
      ಅಭಿವ್ಯಕ್ತಿ = c_parser_gimple_call_internal (parser);
      ಭಙ್ಗ;
    ಪಕ್ಷ CPP_NAME:
      ಯದಿ (c_parser_peek_token (parser)->id_kind == C_ID_ID)
	{
	  ವೃಕ್ಷ id = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
	  ಯದಿ (strcmp (IDENTIFIER_POINTER (id), "__MEM") == 0)
	    {
	      /* __MEM '<' type-name [ ',' number ] '>'
	               '(' [ '(' type-name ')' ] unary-expression
			   [ '+' number ]
			   [ ',' number ]
			   [ ',' number ':' number ] ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      ವೃಕ್ಷ type = c_parser_gimple_typespec (parser);
	      ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ ptr, alias_off, step, index, index2;
	      ptr.ಮೌಲ್ಯ = error_mark_ಗಂಟು;
	      alias_off.ಮೌಲ್ಯ = NULL_ವೃಕ್ಷ;
	      step.ಮೌಲ್ಯ = NULL_ವೃಕ್ಷ;
	      index.ಮೌಲ್ಯ = NULL_ವೃಕ್ಷ;
	      index2.ಮೌಲ್ಯ = NULL_ವೃಕ್ಷ;
	      unsigned short clique = 0;
	      unsigned short base = 0;
	      ತಾರ್ಕಿಕ reverse_order = ಅಸತ್ಯ;
	      ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ ro;
	      ಯದಿ (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  ವೃಕ್ಷ alias_type = NULL_ವೃಕ್ಷ;
		  /* Optional alias-type cast.  */
		  ಯದಿ (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
		    {
		      c_parser_consume_token (parser);
		      ಸಂರಚನಾ c_type_name *alias_type_name
			= c_parser_type_name (parser);
		      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
						 "expected %<)%>");
		      ಯದಿ (alias_type_name)
			{
			  ವೃಕ್ಷ tem;
			  alias_type = groktypename (alias_type_name,
						     &tem, ರಿಕ್ತ);
			}
		    }
		  ptr = c_parser_gimple_unary_expression (parser);
		  ಯದಿ (ptr.ಮೌಲ್ಯ == error_mark_ಗಂಟು
		      || ! POINTER_TYPE_P (ವೃಕ್ಷ_TYPE (ptr.ಮೌಲ್ಯ)))
		    {
		      ಯದಿ (ptr.ಮೌಲ್ಯ != error_mark_ಗಂಟು)
			error_at (ptr.get_start (),
				  "invalid type of %<__MEM%> operand");
		      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
						 "expected %<)%>");
		      ಪ್ರತ್ಯಾಗಮ ಅಭಿವ್ಯಕ್ತಿ;
		    }
		  ಯದಿ (! alias_type)
		    alias_type = ವೃಕ್ಷ_TYPE (ptr.ಮೌಲ್ಯ);
		  /* Optional constant offset.  */
		  ಯದಿ (c_parser_next_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      alias_off = c_parser_gimple_postfix_expression (parser);
		    }
		  ಯದಿ (c_parser_next_token_is (parser, CPP_MULT))
		    {
		      std::swap (index, alias_off);
		      c_parser_consume_token (parser);
		      step = c_parser_gimple_postfix_expression (parser);
		    }
		  ಅನ್ಯಥಾ ಯದಿ (c_parser_next_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      index = c_parser_gimple_postfix_expression (parser);
		      ಯದಿ (c_parser_next_token_is (parser, CPP_MULT))
			{
			  c_parser_consume_token (parser);
			  step = c_parser_gimple_postfix_expression (parser);
			}
		      ಅನ್ಯಥಾ
			std::swap (index, index2);
		    }
		  ಅನ್ಯಥಾ ಯದಿ (alias_off.ಮೌಲ್ಯ
			   && ವೃಕ್ಷ_CODE (alias_off.ಮೌಲ್ಯ) != INTEGER_CST)
		    std::swap (alias_off, index2);
		  ಯದಿ (c_parser_next_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      index2 = c_parser_gimple_postfix_expression (parser);
		    }
		  ಯದಿ (alias_off.ಮೌಲ್ಯ)
		    {
		      ಯದಿ (ವೃಕ್ಷ_CODE (alias_off.ಮೌಲ್ಯ) != INTEGER_CST)
			error_at (alias_off.get_start (),
				  "expected constant offset for %<__MEM%> "
				  "operand");
		      alias_off.ಮೌಲ್ಯ = fold_convert (alias_type,
						      alias_off.ಮೌಲ್ಯ);
		    }
		  ಅನ್ಯಥಾ
		    alias_off.ಮೌಲ್ಯ = build_int_cst (alias_type, 0);
		  ಯದಿ (step.ಮೌಲ್ಯ)
		    {
		      ಯದಿ (ವೃಕ್ಷ_CODE (step.ಮೌಲ್ಯ) != INTEGER_CST)
			error_at (step.get_start (),
				  "expected constant step for %<__MEM%> "
				  "operand");
		    }
		  ಯದಿ (c_parser_next_token_is (parser, CPP_COMMA))
		    {
		      ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ cl, ba;
		      ತಾರ್ಕಿಕ has_clb = ಸತ್ಯ;
		      c_parser_consume_token (parser);
		      cl = c_parser_gimple_postfix_expression (parser);
		      ಯದಿ (!c_parser_next_token_is (parser, CPP_COLON))
			{
			  ro = cl;
			  unsigned HOST_WIDE_INT tmp = 0;
			  ಯದಿ (!ವೃಕ್ಷ_fits_uhwi_p (ro.ಮೌಲ್ಯ)
			      || (tmp = ವೃಕ್ಷ_to_uhwi (ro.ಮೌಲ್ಯ)) > 1)
			    error_at (ro.get_start (),
				      "invalid reverse order value");
			  reverse_order = tmp;
			  has_clb = ಅಸತ್ಯ;
			  ಯದಿ (c_parser_next_token_is (parser, CPP_COMMA))
			    {
			      c_parser_consume_token (parser);
			      cl = c_parser_gimple_postfix_expression (parser);
		              has_clb = ಸತ್ಯ;
			    }
			}
		      ಯದಿ (has_clb
			  && c_parser_require (parser,
					       CPP_COLON, "expected %<:%>"))
			{
			  ba = c_parser_gimple_postfix_expression (parser);
			  ಯದಿ (!ವೃಕ್ಷ_fits_uhwi_p (cl.ಮೌಲ್ಯ)
			      || !ವೃಕ್ಷ_fits_uhwi_p (ba.ಮೌಲ್ಯ)
			      || compare_ವೃಕ್ಷ_int (cl.ಮೌಲ್ಯ,
						   (clique = ವೃಕ್ಷ_to_uhwi
								(cl.ಮೌಲ್ಯ)))
			      || compare_ವೃಕ್ಷ_int (ba.ಮೌಲ್ಯ,
						   (base = ವೃಕ್ಷ_to_uhwi
								 (ba.ಮೌಲ್ಯ))))
			    error_at (cl.get_start (),
				      "invalid clique/base pair");
			}
		    }
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      ಯದಿ (! type || c_parser_error (parser))
		{
		  c_parser_set_error (parser, ಅಸತ್ಯ);
		  ಪ್ರತ್ಯಾಗಮ ಅಭಿವ್ಯಕ್ತಿ;
		}
	      ಯದಿ (index.ಮೌಲ್ಯ || step.ಮೌಲ್ಯ || index2.ಮೌಲ್ಯ)
		ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = build5_loc (loc, TARGET_MEM_REF,
					 type, ptr.ಮೌಲ್ಯ, alias_off.ಮೌಲ್ಯ,
					 index.ಮೌಲ್ಯ, step.ಮೌಲ್ಯ, index2.ಮೌಲ್ಯ);
	      ಅನ್ಯಥಾ
		ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = build2_loc (loc, MEM_REF,
					 type, ptr.ಮೌಲ್ಯ, alias_off.ಮೌಲ್ಯ);
	      ಯದಿ (clique != 0)
		{
		  cfun->last_clique = MAX (cfun->last_clique, clique);
		  MR_DEPENDENCE_CLIQUE (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ) = clique;
		  MR_DEPENDENCE_BASE (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ) = base;
		}
	      ಯದಿ (reverse_order)
		{
		  ಯದಿ (ವೃಕ್ಷ_CODE (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ) == MEM_REF)
		    REF_REVERSE_STORAGE_ORDER (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ) = reverse_order;
		  ಅನ್ಯಥಾ
		    error_at (ro.get_start (),
			      "target mem ref cannot have reverse order");
		}
	      ಭಙ್ಗ;
	    }
	  ಅನ್ಯಥಾ ಯದಿ (strcmp (IDENTIFIER_POINTER (id), "__VIEW_CONVERT") == 0)
	    {
	      /* __VIEW_CONVERT '<' type-name [ ',' number ] '>'
	                        '(' postfix-expression ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      ವೃಕ್ಷ type = c_parser_gimple_typespec (parser);
	      ಯದಿ (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_ಅಭಿವ್ಯಕ್ತಿ op = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  ಯದಿ (type && op.ಮೌಲ್ಯ != error_mark_ಗಂಟು)
		    ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = build1_loc (loc, VIEW_CONVERT_ಅಭಿವ್ಯಕ್ತಿ,
					     type, op.ಮೌಲ್ಯ);
		}
	      ಭಙ್ಗ;
	    }
	  ಅನ್ಯಥಾ ಯದಿ (strcmp (IDENTIFIER_POINTER (id), "__BIT_FIELD_REF") == 0)
	    {
	      /* __BIT_FIELD_REF '<' type-name [ ',' number ] '>'
	                        '(' postfix-expression, integer, integer ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      ವೃಕ್ಷ type = c_parser_gimple_typespec (parser);
	      ಯದಿ (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_ಅಭಿವ್ಯಕ್ತಿ op0 = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_ಅಭಿವ್ಯಕ್ತಿ op1 = c_parser_gimple_postfix_expression (parser);
		  ಯದಿ (ವೃಕ್ಷ_CODE (op1.ಮೌಲ್ಯ) != INTEGER_CST
		      || !int_fits_type_p (op1.ಮೌಲ್ಯ, bitsizetype))
		    c_parser_error (parser, "expected constant size");
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_ಅಭಿವ್ಯಕ್ತಿ op2 = c_parser_gimple_postfix_expression (parser);
		  ಯದಿ (ವೃಕ್ಷ_CODE (op2.ಮೌಲ್ಯ) != INTEGER_CST
		      || !int_fits_type_p (op2.ಮೌಲ್ಯ, bitsizetype))
		    c_parser_error (parser, "expected constant offset");
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  ಯದಿ (type
		      && op0.ಮೌಲ್ಯ != error_mark_ಗಂಟು
		      && ವೃಕ್ಷ_CODE (op1.ಮೌಲ್ಯ) == INTEGER_CST
		      && ವೃಕ್ಷ_CODE (op2.ಮೌಲ್ಯ) == INTEGER_CST)
		    ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = build3_loc (loc, BIT_FIELD_REF, type,
					     op0.ಮೌಲ್ಯ,
					     fold_convert (bitsizetype,
							   op1.ಮೌಲ್ಯ),
					     fold_convert (bitsizetype,
							   op2.ಮೌಲ್ಯ));
		}
	      ಭಙ್ಗ;
	    }
	  ಅನ್ಯಥಾ ಯದಿ (strcmp (IDENTIFIER_POINTER (id), "__CLOBBER") == 0)
	    {
	      /* __CLOBBER [ '(' bob | eob | bos | eos ')' ]  */
	      clobber_kind kind = CLOBBER_UNDEF;
	      c_parser_consume_token (parser);
	      ಯದಿ (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
		{
		  c_parser_consume_token (parser);
		  auto tok = c_parser_peek_token (parser);
		  ಯದಿ (c_parser_require (parser, CPP_NAME,
					"expected clobber kind"))
		    {
		      ಧ್ರುವ ವರ್ಣ *kind_str = IDENTIFIER_POINTER (tok->ಮೌಲ್ಯ);
		      ಯದಿ (strcmp (kind_str, "bos") == 0)
			kind = CLOBBER_STORAGE_BEGIN;
		      ಅನ್ಯಥಾ ಯದಿ (strcmp (kind_str, "bob") == 0)
			kind = CLOBBER_OBJECT_BEGIN;
		      ಅನ್ಯಥಾ ಯದಿ (strcmp (kind_str, "eob") == 0)
			kind = CLOBBER_OBJECT_END;
		      ಅನ್ಯಥಾ ಯದಿ (strcmp (kind_str, "eos") == 0)
			kind = CLOBBER_STORAGE_END;
		      ಅನ್ಯಥಾ
			c_parser_error (parser, "expected one of %<bos%>, "
					"%<eos%>, %<bob>, %<eob%>");
		    }
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      /* We infer the (redundant) type from the LHS.  */
	      ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = build_clobber (ret_type, kind);
	      ಭಙ್ಗ;
	    }
	  ಅನ್ಯಥಾ ಯದಿ (strcmp (IDENTIFIER_POINTER (id), "_Literal") == 0)
	    {
	      /* _Literal '(' type-name ')' ( [ '-' ] constant | constructor ) */
	      c_parser_consume_token (parser);
	      ವೃಕ್ಷ type = NULL_ವೃಕ್ಷ;
	      ಯದಿ (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  ಸಂರಚನಾ c_type_name *type_name = c_parser_type_name (parser);
		  ವೃಕ್ಷ tem;
		  ಯದಿ (type_name)
		    type = groktypename (type_name, &tem, ರಿಕ್ತ);
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      ಯದಿ (! type)
		{
		  c_parser_error (parser, "invalid _Literal");
		  ಪ್ರತ್ಯಾಗಮ ಅಭಿವ್ಯಕ್ತಿ;
		}
	      ಯದಿ (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
		{
		  c_parser_consume_token (parser);
		  ಯದಿ (!AGGREGATE_TYPE_P (type)
		      && !VECTOR_TYPE_P (type))
		    {
		      c_parser_error (parser, "invalid type for _Literal with "
				      "constructor");
		      c_parser_skip_until_found (parser, CPP_CLOSE_BRACE,
						 "expected %<}%>");
		      ಪ್ರತ್ಯಾಗಮ ಅಭಿವ್ಯಕ್ತಿ;
		    }
		  vec<constructor_elt, va_gc> *v = ರಿಕ್ತ;
		  ತಾರ್ಕಿಕ constant_p = ಸತ್ಯ;
		  ಯದಿ (VECTOR_TYPE_P (type)
		      && !c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
		    {
		      vec_alloc (v, TYPE_VECTOR_SUBPARTS (type).to_constant ());
		      ಕುರು
			{
			  ವೃಕ್ಷ val
			    = c_parser_gimple_postfix_expression (parser).ಮೌಲ್ಯ;
			  ಯದಿ (! val
			      || val == error_mark_ಗಂಟು
			      || (! CONSTANT_CLASS_P (val)
				  && ! SSA_VAR_P (val)))
			    {
			      c_parser_error (parser, "invalid _Literal");
			      ಪ್ರತ್ಯಾಗಮ ಅಭಿವ್ಯಕ್ತಿ;
			    }
			  CONSTRUCTOR_APPEND_ELT (v, NULL_ವೃಕ್ಷ, val);
			  ಯದಿ (! CONSTANT_CLASS_P (val))
			    constant_p = ಅಸತ್ಯ;
			  ಯದಿ (c_parser_next_token_is (parser, CPP_COMMA))
			    c_parser_consume_token (parser);
			  ಅನ್ಯಥಾ
			    ಭಙ್ಗ;
			}
		      ಯಾವತ್ (1);
		    }
		  ಯದಿ (c_parser_require (parser, CPP_CLOSE_BRACE,
					"expected %<}%>"))
		    {
		      ಯದಿ (v && constant_p)
			ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = build_vector_from_ctor (type, v);
		      ಅನ್ಯಥಾ
			ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = build_constructor (type, v);
		    }
		  ಅನ್ಯಥಾ
		    {
		      c_parser_skip_until_found (parser, CPP_CLOSE_BRACE,
						 "expected %<}%>");
		      ಪ್ರತ್ಯಾಗಮ ಅಭಿವ್ಯಕ್ತಿ;
		    }
		}
	      ಅನ್ಯಥಾ
		{
		  ತಾರ್ಕಿಕ neg_p, addr_p;
		  ಯದಿ ((neg_p = c_parser_next_token_is (parser, CPP_MINUS)))
		    c_parser_consume_token (parser);
		  ಯದಿ ((addr_p = c_parser_next_token_is (parser, CPP_AND)))
		    c_parser_consume_token (parser);
		  ವೃಕ್ಷ val = c_parser_gimple_postfix_expression (parser).ಮೌಲ್ಯ;
		  ಯದಿ (! val
		      || val == error_mark_ಗಂಟು
		      || (!CONSTANT_CLASS_P (val) && !addr_p))
		    {
		      c_parser_error (parser, "invalid _Literal");
		      ಪ್ರತ್ಯಾಗಮ ಅಭಿವ್ಯಕ್ತಿ;
		    }
		  ಯದಿ (addr_p)
		    {
		      val = build1 (ADDR_ಅಭಿವ್ಯಕ್ತಿ, type, val);
		      ಯದಿ (!is_gimple_invariant_address (val))
			{
			  c_parser_error (parser, "invalid _Literal");
			  ಪ್ರತ್ಯಾಗಮ ಅಭಿವ್ಯಕ್ತಿ;
			}
		    }
		  ಯದಿ (neg_p)
		    {
		      val = const_unop (NEGATE_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (val), val);
		      ಯದಿ (! val)
			{
			  c_parser_error (parser, "invalid _Literal");
			  ಪ್ರತ್ಯಾಗಮ ಅಭಿವ್ಯಕ್ತಿ;
			}
		    }
		  ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = fold_convert (type, val);
		}
	      ಪ್ರತ್ಯಾಗಮ ಅಭಿವ್ಯಕ್ತಿ;
	    }

	  /* SSA name.  */
	  unsigned version, ver_offset;
	  ಯದಿ (! lookup_name (id)
	      && c_parser_parse_ssa_name_id (id, &version, &ver_offset))
	    {
	      c_parser_consume_token (parser);
	      ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = c_parser_parse_ssa_name (parser, id, NULL_ವೃಕ್ಷ,
						    version, ver_offset);
	      ಯದಿ (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ == error_mark_ಗಂಟು)
		ಪ್ರತ್ಯಾಗಮ ಅಭಿವ್ಯಕ್ತಿ;
	      set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&ಅಭಿವ್ಯಕ್ತಿ, tok_range);
	      /* For default definition SSA names.  */
	      ಯದಿ (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
		  && c_parser_peek_2nd_token (parser)->type == CPP_NAME
		  && strcmp ("D",
			     IDENTIFIER_POINTER
			       (c_parser_peek_2nd_token (parser)->ಮೌಲ್ಯ)) == 0
		  && c_parser_peek_nth_token (parser, 3)->type == CPP_CLOSE_PAREN)
		{
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		  ಯದಿ (! SSA_NAME_IS_DEFAULT_DEF (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ))
		    {
		      ಯದಿ (!SSA_NAME_VAR (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ))
			{
			  error_at (loc, "anonymous SSA name cannot have"
				    " default definition");
			  ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = error_mark_ಗಂಟು;
			  ಪ್ರತ್ಯಾಗಮ ಅಭಿವ್ಯಕ್ತಿ;
			}
		      set_ssa_default_def (cfun, SSA_NAME_VAR (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ),
					   ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ);
		      SSA_NAME_DEF_STMT (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ) = gimple_build_nop ();
		    }
		}
	    }
	  ಅನ್ಯಥಾ
	    {
	      c_parser_consume_token (parser);
	      ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ
		= build_external_ref (loc, id,
				      (c_parser_peek_token (parser)->type
				       == CPP_OPEN_PAREN), &ಅಭಿವ್ಯಕ್ತಿ.original_type);
	      set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&ಅಭಿವ್ಯಕ್ತಿ, tok_range);
	    }
	  ಭಙ್ಗ;
	}
      /* Fallthru.  */
    ಸ್ವಭಾವ:
      c_parser_error (parser, "expected expression");
      ಅಭಿವ್ಯಕ್ತಿ.set_error ();
      ಭಙ್ಗ;
    }
  ಯದಿ (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ == error_mark_ಗಂಟು)
    ಪ್ರತ್ಯಾಗಮ ಅಭಿವ್ಯಕ್ತಿ;
  ಪ್ರತ್ಯಾಗಮ c_parser_gimple_postfix_expression_after_primary
    (parser, ಅಭಿವ್ಯಕ್ತಿ_LOC_OR_LOC (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, loc), ಅಭಿವ್ಯಕ್ತಿ);
}

/* Parse a gimple postfix expression after the initial primary or compound
   literal.  */

ಸ್ಥಿರ ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ
c_parser_gimple_postfix_expression_after_primary (gimple_parser &parser,
						  location_t ಅಭಿವ್ಯಕ್ತಿ_loc,
						  ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ)
{
  location_t start;
  location_t finish;
  ವೃಕ್ಷ ident;
  location_t comp_loc;

  ಯಾವತ್ (ಸತ್ಯ)
    {
      location_t op_loc = c_parser_peek_token (parser)->location;
      ವಿಕಲ್ಪ (c_parser_peek_token (parser)->type)
	{
	ಪಕ್ಷ CPP_OPEN_SQUARE:
	  {
	    c_parser_consume_token (parser);
	    ವೃಕ್ಷ idx = c_parser_gimple_unary_expression (parser).ಮೌಲ್ಯ;

	    ಯದಿ (! c_parser_require (parser, CPP_CLOSE_SQUARE, "expected %<]%>"))
	      {
		c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE, ರಿಕ್ತ);
		ಭಙ್ಗ;
	      }

	    start = ಅಭಿವ್ಯಕ್ತಿ.get_start ();
	    finish = c_parser_tokens_buf (parser, 0)->location;
	    ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = build_array_ref (op_loc, ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, idx);
	    set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&ಅಭಿವ್ಯಕ್ತಿ, start, finish);
	    ಅಭಿವ್ಯಕ್ತಿ.m_decimal = 0;

	    ಅಭಿವ್ಯಕ್ತಿ.original_code = ERROR_MARK;
	    ಅಭಿವ್ಯಕ್ತಿ.original_type = ರಿಕ್ತ;
	    ಭಙ್ಗ;
	  }
	ಪಕ್ಷ CPP_OPEN_PAREN:
	  {
	    /* Function call.  */
	    c_parser_consume_token (parser);
	    auto_vec<ವೃಕ್ಷ> exprlist;
	    ಯದಿ (! c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	      c_parser_gimple_ಅಭಿವ್ಯಕ್ತಿ_list (parser, &exprlist);
	    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    ಯದಿ (!FUNC_OR_METHOD_TYPE_P (ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ)))
	      {
		c_parser_error (parser, "invalid call to non-function");
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		ಭಙ್ಗ;
	      }
	    ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = build_call_array_loc
		(ಅಭಿವ್ಯಕ್ತಿ_loc, ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ)),
		 ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, exprlist.length (), exprlist.address ());
	    ಅಭಿವ್ಯಕ್ತಿ.m_decimal = 0;
	    ಅಭಿವ್ಯಕ್ತಿ.original_code = ERROR_MARK;
	    ಅಭಿವ್ಯಕ್ತಿ.original_type = ರಿಕ್ತ;
	    ಭಙ್ಗ;
	  }
	ಪಕ್ಷ CPP_DOT:
	  {
	    /* Structure element reference.  */
	    c_parser_consume_token (parser);
	    ಯದಿ (c_parser_next_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		ident = comp_tok->ಮೌಲ್ಯ;
		comp_loc = comp_tok->location;
	      }
	    ಅನ್ಯಥಾ
	      {
		c_parser_error (parser, "expected identifier");
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		ಅಭಿವ್ಯಕ್ತಿ.original_code = ERROR_MARK;
		ಅಭಿವ್ಯಕ್ತಿ.original_type = ರಿಕ್ತ;
		ಪ್ರತ್ಯಾಗಮ ಅಭಿವ್ಯಕ್ತಿ;
	      }
	    start = ಅಭಿವ್ಯಕ್ತಿ.get_start ();
	    finish = c_parser_peek_token (parser)->get_finish ();
	    c_parser_consume_token (parser);
	    ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = build_component_ref (op_loc, ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, ident,
					      comp_loc, UNKNOWN_LOCATION);
	    set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&ಅಭಿವ್ಯಕ್ತಿ, start, finish);
	    ಅಭಿವ್ಯಕ್ತಿ.m_decimal = 0;
	    ಅಭಿವ್ಯಕ್ತಿ.original_code = ERROR_MARK;
	    ಯದಿ (ವೃಕ್ಷ_CODE (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ) != COMPONENT_REF)
	      ಅಭಿವ್ಯಕ್ತಿ.original_type = ರಿಕ್ತ;
	    ಅನ್ಯಥಾ
	      {
		/* Remember the original type of a bitfield.  */
		ವೃಕ್ಷ field = ವೃಕ್ಷ_OPERAND (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, 1);
		ಯದಿ (ವೃಕ್ಷ_CODE (field) != FIELD_DECL)
		  ಅಭಿವ್ಯಕ್ತಿ.original_type = ರಿಕ್ತ;
		ಅನ್ಯಥಾ
		  ಅಭಿವ್ಯಕ್ತಿ.original_type = DECL_BIT_FIELD_TYPE (field);
	      }
	    ಭಙ್ಗ;
	  }
	ಪಕ್ಷ CPP_DEREF:
	  {
	    /* Structure element reference.  */
	    ಯದಿ (!POINTER_TYPE_P (ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ)))
	      {
		c_parser_error (parser, "dereference of non-pointer");
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		ಅಭಿವ್ಯಕ್ತಿ.original_code = ERROR_MARK;
		ಅಭಿವ್ಯಕ್ತಿ.original_type = ರಿಕ್ತ;
		ಪ್ರತ್ಯಾಗಮ ಅಭಿವ್ಯಕ್ತಿ;
	      }
	    c_parser_consume_token (parser);
	    ಯದಿ (c_parser_next_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		ident = comp_tok->ಮೌಲ್ಯ;
		comp_loc = comp_tok->location;
	      }
	    ಅನ್ಯಥಾ
	      {
		c_parser_error (parser, "expected identifier");
		ಅಭಿವ್ಯಕ್ತಿ.set_error ();
		ಅಭಿವ್ಯಕ್ತಿ.original_code = ERROR_MARK;
		ಅಭಿವ್ಯಕ್ತಿ.original_type = ರಿಕ್ತ;
		ಪ್ರತ್ಯಾಗಮ ಅಭಿವ್ಯಕ್ತಿ;
	      }
	    start = ಅಭಿವ್ಯಕ್ತಿ.get_start ();
	    finish = c_parser_peek_token (parser)->get_finish ();
	    c_parser_consume_token (parser);
	    ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = build_component_ref (op_loc,
					      build_simple_mem_ref_loc
					        (op_loc, ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ),
					      ident, comp_loc,
					      ಅಭಿವ್ಯಕ್ತಿ.get_location ());
	    set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&ಅಭಿವ್ಯಕ್ತಿ, start, finish);
	    ಅಭಿವ್ಯಕ್ತಿ.m_decimal = 0;
	    ಅಭಿವ್ಯಕ್ತಿ.original_code = ERROR_MARK;
	    ಯದಿ (ವೃಕ್ಷ_CODE (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ) != COMPONENT_REF)
	      ಅಭಿವ್ಯಕ್ತಿ.original_type = ರಿಕ್ತ;
	    ಅನ್ಯಥಾ
	      {
		/* Remember the original type of a bitfield.  */
		ವೃಕ್ಷ field = ವೃಕ್ಷ_OPERAND (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, 1);
		ಯದಿ (ವೃಕ್ಷ_CODE (field) != FIELD_DECL)
		  ಅಭಿವ್ಯಕ್ತಿ.original_type = ರಿಕ್ತ;
		ಅನ್ಯಥಾ
		  ಅಭಿವ್ಯಕ್ತಿ.original_type = DECL_BIT_FIELD_TYPE (field);
	      }
	    ಭಙ್ಗ;
	  }
	ಸ್ವಭಾವ:
	  ಪ್ರತ್ಯಾಗಮ ಅಭಿವ್ಯಕ್ತಿ;
	}
    }
}

/* Parse expression list.

   gimple-expr-list:
     gimple-unary-expression
     gimple-expr-list , gimple-unary-expression

 */

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_gimple_ಅಭಿವ್ಯಕ್ತಿ_list (gimple_parser &parser, vec<ವೃಕ್ಷ> *ret)
{
  ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ;

  ಅಭಿವ್ಯಕ್ತಿ = c_parser_gimple_unary_expression (parser);
  ret->safe_ತಳ್ಳು (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ);
  ಯಾವತ್ (c_parser_next_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      ಅಭಿವ್ಯಕ್ತಿ = c_parser_gimple_unary_expression (parser);
      ret->safe_ತಳ್ಳು (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ);
    }
}

/* Parse gimple label.

   gimple-label:
     identifier :
     case constant-expression :
     default :

*/

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_gimple_label (gimple_parser &parser, gimple_seq *seq)
{
  ವೃಕ್ಷ name = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
  location_t loc1 = c_parser_peek_token (parser)->location;
  gcc_assert (c_parser_next_token_is (parser, CPP_NAME));
  c_parser_consume_token (parser);
  gcc_assert (c_parser_next_token_is (parser, CPP_COLON));
  c_parser_consume_token (parser);
  ವೃಕ್ಷ label = define_label (loc1, name);
  ಯದಿ (label)
    gimple_seq_add_stmt_without_update (seq, gimple_build_label (label));
  ಪ್ರತ್ಯಾಗಮ;
}

/* Parse gimple/RTL pass list.

   gimple-or-rtl-pass-list:
     startwith("pass-name")[,{cfg,ssa}]
 */

ಶೂನ್ಯ
c_parser_gimple_or_rtl_pass_list (c_parser *parser, c_declspecs *specs)
{
  ವರ್ಣ *pass = ರಿಕ್ತ;

  /* Accept __GIMPLE/__RTL.  */
  ಯದಿ (c_parser_next_token_is_not (parser, CPP_OPEN_PAREN))
    ಪ್ರತ್ಯಾಗಮ;
  c_parser_consume_token (parser);

  specs->entry_bb_ಎಣಿಕೆ = profile_ಎಣಿಕೆ::uninitialized ();
  ಯಾವತ್ (c_parser_next_token_is (parser, CPP_NAME))
    {
      profile_quality quality;
      ಧ್ರುವ ವರ್ಣ *op = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ);
      c_parser_consume_token (parser);
      ಯದಿ (! strcmp (op, "startwith"))
	{
	  ಯದಿ (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    ಪ್ರತ್ಯಾಗಮ;
	  ಯದಿ (c_parser_next_token_is_not (parser, CPP_STRING))
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"expected pass name");
	      ಪ್ರತ್ಯಾಗಮ;
	    }
	  pass = xstrdup (ವೃಕ್ಷ_STRING_POINTER
			  (c_parser_string_literal (parser, ಅಸತ್ಯ,
						    ಅಸತ್ಯ).ಮೌಲ್ಯ));
	  ಯದಿ (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<(%>"))
	    ಪ್ರತ್ಯಾಗಮ;
	}
      ಅನ್ಯಥಾ ಯದಿ (parse_profile_quality (op, &quality))
	{
	  ವೃಕ್ಷ q;
	  ಯದಿ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    ಪ್ರತ್ಯಾಗಮ;

	  ಯದಿ (!c_parser_next_token_is (parser, CPP_ಸಂಖ್ಯೆ)
	      || (ವೃಕ್ಷ_CODE (q = c_parser_peek_token (parser)->ಮೌಲ್ಯ)
		  != INTEGER_CST))
	    {
	      c_parser_error (parser, "expected count value");
	      ಪ್ರತ್ಯಾಗಮ;
	    }

	  specs->entry_bb_ಎಣಿಕೆ
	    = profile_ಎಣಿಕೆ::from_gcov_type (ವೃಕ್ಷ_INT_CST_ಕೆಳಗಿನ (q), quality);
	  c_parser_consume_token (parser);
	  ಯದಿ (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    ಪ್ರತ್ಯಾಗಮ;
	}
      ಅನ್ಯಥಾ ಯದಿ (specs->declspec_il != cdil_gimple)
	/* Allow only one IL specifier and none on RTL.  */
	;
      ಅನ್ಯಥಾ ಯದಿ (! strcmp (op, "cfg"))
	specs->declspec_il = cdil_gimple_cfg;
      ಅನ್ಯಥಾ ಯದಿ (! strcmp (op, "ssa"))
	specs->declspec_il = cdil_gimple_ssa;
      ಅನ್ಯಥಾ
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "invalid operation");
	  ಪ್ರತ್ಯಾಗಮ;
	}
     ಯದಿ (c_parser_next_token_is (parser, CPP_COMMA))
       c_parser_consume_token (parser);
    }

  ಯದಿ (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    ಪ್ರತ್ಯಾಗಮ;

  specs->gimple_or_rtl_pass = pass;
}

/* Parse gimple local declaration.

   declaration-specifiers:
     storage-class-specifier declaration-specifiers[opt]
     type-specifier declaration-specifiers[opt]
     type-qualifier declaration-specifiers[opt]
     function-specifier declaration-specifiers[opt]
     alignment-specifier declaration-specifiers[opt]

   storage-class-specifier:
     typedef
     extern
     static
     auto
     register

   type-specifier:
     void
     char
     short
     int
     long
     float
     double
     signed
     unsigned
     _Bool
     _Complex

   type-qualifier:
     const
     restrict
     volatile
     address-space-qualifier
     _Atomic

 */

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_gimple_declaration (gimple_parser &parser)
{
  ಸಂರಚನಾ c_declarator *declarator;
  ಸಂರಚನಾ c_declspecs *specs = build_null_declspecs ();
  c_parser_declspecs (parser, specs, ಸತ್ಯ, ಸತ್ಯ, ಸತ್ಯ,
		      ಸತ್ಯ, ಸತ್ಯ, ಸತ್ಯ, ಸತ್ಯ, cla_nonabstract_decl);
  finish_declspecs (specs);

  /* Provide better error recovery.  Note that a type name here is usually
     better diagnosed as a redeclaration.  */
  ಯದಿ (c_parser_next_token_starts_declspecs (parser)
      && ! c_parser_next_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<;%>");
      c_parser_set_error (parser, ಅಸತ್ಯ);
      ಪ್ರತ್ಯಾಗಮ;
    }

  ತಾರ್ಕಿಕ dummy = ಅಸತ್ಯ;
  declarator = c_parser_declarator (parser,
				    specs->typespec_kind != ctsk_none,
				    C_DTR_NORMAL, &dummy);

  ಯದಿ (!c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_error (parser, "expected %<;%>");
      ಪ್ರತ್ಯಾಗಮ;
    }
  ಯದಿ (declarator)
    {
      /* Handle SSA name decls specially, they do not go into the identifier
         table but we simply build the SSA name for later lookup.  */
      unsigned version, ver_offset;
      /* Handle SSA pointer declarations in a very simplistic ways, we
	 probably would like to call grokdeclarator in a special mode to
	 just build the type of the decl - start_decl already pushes
	 the identifier to the bindings for lookup, something we do not
	 want.  */
      ಸಂರಚನಾ c_declarator *id_declarator = declarator;
      ಯಾವತ್ (id_declarator->kind == cdk_pointer)
	id_declarator = id_declarator->declarator;
      ಯದಿ (id_declarator->kind == cdk_id
	  && (declarator->kind == cdk_pointer
	      || is_gimple_reg_type (specs->type))
	  && c_parser_parse_ssa_name_id (id_declarator->u.id.id,
					 &version, &ver_offset)
	  /* The following restricts it to unnamed anonymous SSA names
	     which fails parsing of named ones in dumps (we could
	     decide to not dump their name for -gimple).  */
	  && ver_offset == 0)
	{
	  ಸಂರಚನಾ c_declarator *p = declarator;
	  ವೃಕ್ಷ type = specs->type;
	  ಯಾವತ್ (p->kind == cdk_pointer)
	    {
	      type = build_pointer_type (type);
	      p = p->declarator;
	    }
	  c_parser_parse_ssa_name (parser, id_declarator->u.id.id, type,
				   version, ver_offset);
	}
      ಅನ್ಯಥಾ
	{
	  ವೃಕ್ಷ postfix_attrs = NULL_ವೃಕ್ಷ;
	  ವೃಕ್ಷ all_prefix_attrs = specs->attrs;
	  specs->attrs = ರಿಕ್ತ;
	  ವೃಕ್ಷ decl = start_decl (declarator, specs, ಅಸತ್ಯ,
				  chainon (postfix_attrs, all_prefix_attrs));
	  ಯದಿ (decl)
	    finish_decl (decl, UNKNOWN_LOCATION, NULL_ವೃಕ್ಷ, NULL_ವೃಕ್ಷ,
			 NULL_ವೃಕ್ಷ);
	}
    }
}

/* Parse gimple goto statement.  */

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_gimple_goto_stmt (gimple_parser &parser,
			   location_t loc, ವೃಕ್ಷ label, gimple_seq *seq)
{
  ಯದಿ (cfun->curr_properties & PROP_cfg)
    {
      ಪೂರ್ಣಾಙ್ಕ dest_index;
      profile_probability prob;
      ಯದಿ (c_parser_gimple_parse_bb_spec_edge_probability (label, parser,
							  &dest_index, &prob))
	{
	  parser.ತಳ್ಳು_edge (parser.current_bb->index, dest_index,
			    EDGE_FALLTHRU, prob);
	  ಪ್ರತ್ಯಾಗಮ;
	}
    }
  ವೃಕ್ಷ decl = lookup_label_for_goto (loc, label);
  gimple_seq_add_stmt_without_update (seq, gimple_build_goto (decl));
}

/* Parse a parenthesized condition.
   gimple-condition:
     ( gimple-binary-expression )    */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_gimple_paren_condition (gimple_parser &parser)
{
  ಯದಿ (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
  ವೃಕ್ಷ cond
    = c_parser_gimple_ದ್ವಿಮಾನ_expression (parser, boolean_type_ಗಂಟು).ಮೌಲ್ಯ;
  ಯದಿ (cond != error_mark_ಗಂಟು
      && ! COMPARISON_CLASS_P (cond)
      && ! CONSTANT_CLASS_P (cond)
      && ! SSA_VAR_P (cond))
    {
      c_parser_error (parser, "comparison required");
      cond = error_mark_ಗಂಟು;
    }
  ಯದಿ (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
  ಪ್ರತ್ಯಾಗಮ cond;
}

/* Parse gimple try statement.

   try-statement:
     try { ... } finally { ... }
     try { ... } finally { ... } else { ... }

   This could support try/catch as well, but it's not implemented yet.
 */

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_gimple_try_stmt (gimple_parser &parser, gimple_seq *seq)
{
  gimple_seq tryseq = ರಿಕ್ತ;
  c_parser_consume_token (parser);
  c_parser_gimple_compound_statement (parser, &tryseq);

  ಯದಿ ((c_parser_next_token_is (parser, CPP_KEYWORD)
       && c_parser_peek_token (parser)->keyword == RID_AT_FINALLY)
      || (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_token (parser)->id_kind == C_ID_ID
	  && strcmp (IDENTIFIER_POINTER (c_parser_peek_token (parser)->ಮೌಲ್ಯ),
		     "finally") == 0))
    {
      gimple_seq finseq = ರಿಕ್ತ;
      c_parser_consume_token (parser);
      c_parser_gimple_compound_statement (parser, &finseq);

      ಯದಿ (c_parser_next_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_ELSE)
	{
	  gimple_seq elsseq = ರಿಕ್ತ;
	  c_parser_consume_token (parser);
	  c_parser_gimple_compound_statement (parser, &elsseq);

	  geh_else *stmt = gimple_build_eh_else (finseq, elsseq);
	  finseq = ರಿಕ್ತ;
	  gimple_seq_add_stmt_without_update (&finseq, stmt);
	}

      gtry *stmt = gimple_build_try (tryseq, finseq, GIMPLE_TRY_FINALLY);
      gimple_seq_add_stmt_without_update (seq, stmt);
    }
  ಅನ್ಯಥಾ ಯದಿ (c_parser_next_token_is (parser, CPP_KEYWORD)
      && c_parser_peek_token (parser)->keyword == RID_AT_CATCH)
    c_parser_error (parser, "%<catch%> is not supported");
  ಅನ್ಯಥಾ
    c_parser_error (parser, "expected %<finally%> or %<catch%>");
}

/* Parse gimple if-else statement.

   if-statement:
     if ( gimple-binary-expression ) gimple-goto-statement
     if ( gimple-binary-expression ) gimple-goto-statement \
					else gimple-goto-statement
 */

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_gimple_if_stmt (gimple_parser &parser, gimple_seq *seq)
{
  ವೃಕ್ಷ t_label = NULL_ವೃಕ್ಷ, f_label = NULL_ವೃಕ್ಷ, label;
  location_t loc;
  c_parser_consume_token (parser);
  ವೃಕ್ಷ cond = c_parser_gimple_paren_condition (parser);

  ಯದಿ (c_parser_next_token_is_keyword (parser, RID_GOTO))
    {
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      ಯದಿ (! c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected label");
	  ಪ್ರತ್ಯಾಗಮ;
	}
      label = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
      c_parser_consume_token (parser);
      ಪೂರ್ಣಾಙ್ಕ dest_index;
      profile_probability prob;
      ಯದಿ ((cfun->curr_properties & PROP_cfg)
	  && c_parser_gimple_parse_bb_spec_edge_probability (label, parser,
							     &dest_index, &prob))
	parser.ತಳ್ಳು_edge (parser.current_bb->index, dest_index,
			  EDGE_TRUE_ಮೌಲ್ಯ, prob);
      ಅನ್ಯಥಾ
	t_label = lookup_label_for_goto (loc, label);
      ಯದಿ (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	ಪ್ರತ್ಯಾಗಮ;
    }
  ಅನ್ಯಥಾ
    {
      c_parser_error (parser, "expected goto expression");
      ಪ್ರತ್ಯಾಗಮ;
    }

  ಯದಿ (c_parser_next_token_is_keyword (parser, RID_ELSE))
    c_parser_consume_token (parser);
  ಅನ್ಯಥಾ
    {
      c_parser_error (parser, "expected else statement");
      ಪ್ರತ್ಯಾಗಮ;
    }

  ಯದಿ (c_parser_next_token_is_keyword (parser, RID_GOTO))
    {
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      ಯದಿ (! c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected label");
	  ಪ್ರತ್ಯಾಗಮ;
	}
      label = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
      c_parser_consume_token (parser);
      ಪೂರ್ಣಾಙ್ಕ dest_index;
      profile_probability prob;
      ಯದಿ ((cfun->curr_properties & PROP_cfg)
	  && c_parser_gimple_parse_bb_spec_edge_probability (label, parser,
							     &dest_index, &prob))
	parser.ತಳ್ಳು_edge (parser.current_bb->index, dest_index,
			  EDGE_FALSE_ಮೌಲ್ಯ, prob);
      ಅನ್ಯಥಾ
	f_label = lookup_label_for_goto (loc, label);
      ಯದಿ (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	ಪ್ರತ್ಯಾಗಮ;
    }
  ಅನ್ಯಥಾ
    {
      c_parser_error (parser, "expected goto expression");
      ಪ್ರತ್ಯಾಗಮ;
    }

  ಯದಿ (cond != error_mark_ಗಂಟು)
    gimple_seq_add_stmt_without_update (seq, gimple_build_cond_from_ವೃಕ್ಷ (cond, t_label,
							   f_label));
}

/* Parse gimple switch-statement.

   gimple-switch-statement:
     switch (gimple-postfix-expression) gimple-case-statement

   gimple-case-statement:
     gimple-case-statement
     gimple-label-statement : gimple-goto-statement
*/

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_gimple_switch_stmt (gimple_parser &parser, gimple_seq *seq)
{
  c_ಅಭಿವ್ಯಕ್ತಿ cond_ಅಭಿವ್ಯಕ್ತಿ;
  ವೃಕ್ಷ case_label, label;
  auto_vec<ವೃಕ್ಷ> labels;
  ವೃಕ್ಷ default_label = NULL_ವೃಕ್ಷ;
  c_parser_consume_token (parser);

  ಯದಿ (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    ಪ್ರತ್ಯಾಗಮ;
  cond_ಅಭಿವ್ಯಕ್ತಿ = c_parser_gimple_postfix_expression (parser);
  ಯದಿ (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    ಪ್ರತ್ಯಾಗಮ;

  ಯದಿ (! c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    ಪ್ರತ್ಯಾಗಮ;

  ಯಾವತ್ (c_parser_next_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      ಯದಿ (c_parser_next_token_is (parser, CPP_EOF))
	{
	  c_parser_error (parser, "expected statement");
	  ಪ್ರತ್ಯಾಗಮ;
	}

      ವಿಕಲ್ಪ (c_parser_peek_token (parser)->keyword)
	{
	ಪಕ್ಷ RID_CASE:
	  {
	    c_ಅಭಿವ್ಯಕ್ತಿ exp1;
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);

	    ಯದಿ (c_parser_next_token_is (parser, CPP_NAME)
		|| c_parser_peek_token (parser)->type == CPP_ಸಂಖ್ಯೆ)
	      exp1 = c_parser_gimple_postfix_expression (parser);
	    ಅನ್ಯಥಾ
	      {
		c_parser_error (parser, "expected expression");
		ಪ್ರತ್ಯಾಗಮ;
	      }

	    ಯದಿ (c_parser_next_token_is (parser, CPP_COLON))
	      {
		c_parser_consume_token (parser);
		ಯದಿ (c_parser_next_token_is (parser, CPP_NAME))
		  {
		    label = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
		    c_parser_consume_token (parser);
		    ವೃಕ್ಷ decl = lookup_label_for_goto (loc, label);
		    case_label = build_case_label (exp1.ಮೌಲ್ಯ, NULL_ವೃಕ್ಷ,
						   decl);
		    labels.safe_ತಳ್ಳು (case_label);
		    ಯದಿ (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      ಪ್ರತ್ಯಾಗಮ;
		  }
		ಅನ್ಯಥಾ ಯದಿ (! c_parser_require (parser, CPP_NAME,
					     "expected label"))
		  ಪ್ರತ್ಯಾಗಮ;
	      }
	    ಅನ್ಯಥಾ ಯದಿ (! c_parser_require (parser, CPP_SEMICOLON,
					 "expected %<:%>"))
	      ಪ್ರತ್ಯಾಗಮ;
	    ಭಙ್ಗ;
	  }
	ಪಕ್ಷ RID_DEFAULT:
	  {
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);
	    ಯದಿ (c_parser_next_token_is (parser, CPP_COLON))
	      {
		c_parser_consume_token (parser);
		ಯದಿ (c_parser_next_token_is (parser, CPP_NAME))
		  {
		    label = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
		    c_parser_consume_token (parser);
		    ವೃಕ್ಷ decl = lookup_label_for_goto (loc, label);
		    default_label = build_case_label (NULL_ವೃಕ್ಷ, NULL_ವೃಕ್ಷ,
						      decl);
		    ಯದಿ (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      ಪ್ರತ್ಯಾಗಮ;
		  }
		ಅನ್ಯಥಾ ಯದಿ (! c_parser_require (parser, CPP_NAME,
					     "expected label"))
		  ಪ್ರತ್ಯಾಗಮ;
	      }
	    ಅನ್ಯಥಾ ಯದಿ (! c_parser_require (parser, CPP_SEMICOLON,
					 "expected %<:%>"))
	      ಪ್ರತ್ಯಾಗಮ;
	    ಭಙ್ಗ;
	  }
	ಸ್ವಭಾವ:
	  c_parser_error (parser, "expected case label");
	  ಪ್ರತ್ಯಾಗಮ;
	}

    }
  ಯದಿ (! c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>"))
    ಪ್ರತ್ಯಾಗಮ;

  ಯದಿ (cond_ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ != error_mark_ಗಂಟು)
    {
      gswitch *s = gimple_build_switch (cond_ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, default_label, labels);
      gimple_seq_add_stmt_without_update (seq, s);
    }
}

/* Parse gimple return statement.  */

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_gimple_return_stmt (gimple_parser &parser, gimple_seq *seq)
{
  location_t loc = c_parser_peek_token (parser)->location;
  gimple *ret = ರಿಕ್ತ;
  c_parser_consume_token (parser);
  ಯದಿ (c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      c_finish_gimple_return (loc, NULL_ವೃಕ್ಷ);
      ret = gimple_build_return (ರಿಕ್ತ);
      gimple_seq_add_stmt_without_update (seq, ret);
    }
  ಅನ್ಯಥಾ
    {
      location_t xloc = c_parser_peek_token (parser)->location;
      c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ = c_parser_gimple_unary_expression (parser);
      ಯದಿ (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ != error_mark_ಗಂಟು)
	{
	  c_finish_gimple_return (xloc, ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ);
	  ret = gimple_build_return (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ);
	  gimple_seq_add_stmt_without_update (seq, ret);
	}
    }
}

/* Support function for c_parser_gimple_return_stmt.  */

ಸ್ಥಿರ ಶೂನ್ಯ
c_finish_gimple_return (location_t loc, ವೃಕ್ಷ retval)
{
  ವೃಕ್ಷ valtype = ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (current_function_decl));

  /* Use the expansion point to handle cases such as returning NULL
     in a function returning void.  */
  location_t xloc = expansion_point_location_if_in_system_header (loc);

  ಯದಿ (ವೃಕ್ಷ_THIS_VOLATILE (current_function_decl))
    warning_at (xloc, 0,
		"function declared %<noreturn%> has a %<return%> statement");

  ಯದಿ (! retval)
    current_function_returns_null = 1;
  ಅನ್ಯಥಾ ಯದಿ (valtype == 0 || VOID_TYPE_P (valtype))
    {
      current_function_returns_null = 1;
      ಯದಿ (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (retval)) != VOID_TYPE)
	{
	  error_at
	    (xloc, "%<return%> with a value, in function returning void");
	  inform (DECL_SOURCE_LOCATION (current_function_decl),
		  "declared here");
	}
    }
  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (valtype) != ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (retval)))
    {
      error_at
	(xloc, "invalid conversion in return statement");
      inform (DECL_SOURCE_LOCATION (current_function_decl),
	      "declared here");
    }
  ಪ್ರತ್ಯಾಗಮ;
}
