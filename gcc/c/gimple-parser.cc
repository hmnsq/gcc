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

#অন্তর্ভাৱ "config.h"
#অন্তর্ভাৱ "system.h"
#অন্তর্ভাৱ "coretypes.h"
#অন্তর্ভাৱ "target.h"
#অন্তর্ভাৱ "function.h"
#অন্তর্ভাৱ "c-tree.h"
#অন্তর্ভাৱ "timevar.h"
#অন্তর্ভাৱ "stringpool.h"
#অন্তর্ভাৱ "cgraph.h"
#অন্তর্ভাৱ "attribs.h"
#অন্তর্ভাৱ "stor-layout.h"
#অন্তর্ভাৱ "varasm.h"
#অন্তর্ভাৱ "trans-mem.h"
#অন্তর্ভাৱ "c-family/c-pragma.h"
#অন্তর্ভাৱ "c-lang.h"
#অন্তর্ভাৱ "c-family/c-objc.h"
#অন্তর্ভাৱ "plugin.h"
#অন্তর্ভাৱ "builtins.h"
#অন্তর্ভাৱ "gomp-constants.h"
#অন্তর্ভাৱ "c-family/c-indentation.h"
#অন্তর্ভাৱ "gimple-expr.h"
#অন্তর্ভাৱ "context.h"
#অন্তর্ভাৱ "gcc-rich-location.h"
#অন্তর্ভাৱ "c-parser.h"
#অন্তর্ভাৱ "tree-vrp.h"
#অন্তর্ভাৱ "tree-pass.h"
#অন্তর্ভাৱ "tree-pretty-print.h"
#অন্তর্ভাৱ "tree.h"
#অন্তর্ভাৱ "basic-block.h"
#অন্তর্ভাৱ "gimple.h"
#অন্তর্ভাৱ "gimple-pretty-print.h"
#অন্তর্ভাৱ "tree-ssa.h"
#অন্তর্ভাৱ "pass_manager.h"
#অন্তর্ভাৱ "tree-ssanames.h"
#অন্তর্ভাৱ "gimple-ssa.h"
#অন্তর্ভাৱ "tree-dfa.h"
#অন্তর্ভাৱ "internal-fn.h"
#অন্তর্ভাৱ "cfg.h"
#অন্তর্ভাৱ "cfghooks.h"
#অন্তর্ভাৱ "bitmap.h"
#অন্তর্ভাৱ "cfganal.h"
#অন্তর্ভাৱ "tree-cfg.h"
#অন্তর্ভাৱ "gimple-iterator.h"
#অন্তর্ভাৱ "cfgloop.h"
#অন্তর্ভাৱ "tree-phinodes.h"
#অন্তর্ভাৱ "tree-into-ssa.h"


/* GIMPLE parser state.  */

শ্ৰেণী gimple_parser
{
সার্ৱজনিক:
  gimple_parser (c_parser *p) : parser (p), edges(), current_bb(রিক্ত) {}
  /* c_parser is not visible here, use composition and fake inheritance
     via a conversion operator.  */
  operator c_parser *() { ঘূৰাই parser; }
  c_parser *parser;

  /* CFG build state.  */
  শ্ৰেণী gimple_parser_edge
  {
  সার্ৱজনিক:
    পূর্ণাঙ্ক src;
    পূর্ণাঙ্ক dest;
    পূর্ণাঙ্ক flags;
    profile_probability probability;
  };
  auto_vec<gimple_parser_edge> edges;
  basic_block current_bb;

  শূন্য ঠেলো_edge (পূর্ণাঙ্ক, পূর্ণাঙ্ক, পূর্ণাঙ্ক, profile_probability);
};

শূন্য
gimple_parser::ঠেলো_edge (পূর্ণাঙ্ক src, পূর্ণাঙ্ক dest, পূর্ণাঙ্ক flags,
			  profile_probability prob)
{
  gimple_parser_edge e;
  e.src = src;
  e.dest = dest;
  e.flags = flags;
  e.probability = prob;
  edges.safe_ঠেলো (e);
}


/* Gimple parsing functions.  */
স্থির তার্কিক c_parser_gimple_compound_statement (gimple_parser &, gimple_seq *);
স্থির শূন্য c_parser_gimple_label (gimple_parser &, gimple_seq *);
স্থির শূন্য c_parser_gimple_statement (gimple_parser &, gimple_seq *);
স্থির সংরচনা c_ৰাশিমালা c_parser_gimple_দ্বিমিক_expression (gimple_parser &, বৃক্ষ);
স্থির সংরচনা c_ৰাশিমালা c_parser_gimple_unary_expression (gimple_parser &);
স্থির সংরচনা c_ৰাশিমালা c_parser_gimple_postfix_expression
			(gimple_parser &, বৃক্ষ = error_mark_গ্ৰন্থি);
স্থির সংরচনা c_ৰাশিমালা c_parser_gimple_postfix_expression_after_primary
			(gimple_parser &, location_t, সংরচনা c_ৰাশিমালা);
স্থির শূন্য c_parser_gimple_declaration (gimple_parser &);
স্থির শূন্য c_parser_gimple_goto_stmt (gimple_parser &, location_t,
				       বৃক্ষ, gimple_seq *);
স্থির শূন্য c_parser_gimple_try_stmt (gimple_parser &, gimple_seq *);
স্থির শূন্য c_parser_gimple_if_stmt (gimple_parser &, gimple_seq *);
স্থির শূন্য c_parser_gimple_switch_stmt (gimple_parser &, gimple_seq *);
স্থির শূন্য c_parser_gimple_return_stmt (gimple_parser &, gimple_seq *);
স্থির শূন্য c_finish_gimple_return (location_t, বৃক্ষ);
স্থির বৃক্ষ c_parser_gimple_paren_condition (gimple_parser &);
স্থির শূন্য c_parser_gimple_ৰাশিমালা_list (gimple_parser &, vec<বৃক্ষ> *);


/* Much like parser_build_unary_op, but avoid applying default conversions.  */

স্থির c_ৰাশিমালা
gimple_parser_build_unary_op (location_t loc,
			      গণনা বৃক্ষ_code code, সংরচনা c_ৰাশিমালা arg)
{
  সংরচনা c_ৰাশিমালা result;

  result.original_code = code;
  result.original_type = রিক্ত;
  result.m_decimal = 0;

  যদি (reject_gcc_builtin (arg.মান))
    {
      result.মান = error_mark_গ্ৰন্থি;
    }
  অন্যথা
    {
      result.মান = build_unary_op (loc, code, arg.মান, সঁচা);

      যদি (বৃক্ষ_OVERFLOW_P (result.মান) && !বৃক্ষ_OVERFLOW_P (arg.মান))
	overflow_warning (loc, result.মান, arg.মান);
    }

  /* We are typically called when parsing a prefix token at LOC acting on
     ARG.  Reflect this by updating the source range of the result to
     start at LOC and end at the end of ARG.  */
  set_c_ৰাশিমালা_source_range (&result,
			   loc, arg.get_finish ());

  ঘূৰাই result;
}

/* See if VAL is an identifier matching __BB<num> and return <num>
   in *INDEX.  */

স্থির তার্কিক
c_parser_gimple_parse_bb_spec (বৃক্ষ val, পূর্ণাঙ্ক *index)
{
  যদি (!startswith (IDENTIFIER_POINTER (val), "__BB"))
    ঘূৰাই মিছা;

  ধ্রুৱ ৱর্ণ *bb = IDENTIFIER_POINTER (val) + 4;
  যদি (! ISDIGIT (*bb))
    ঘূৰাই মিছা;

  ৱর্ণ *pend;
  errno = 0;
  ধ্রুৱ unsigned long সংখ্যা = strtoul (bb, &pend, 10);
  যদি (errno == ERANGE
      || *pend != '\0'
      || সংখ্যা > INT_MAX)
    ঘূৰাই মিছা;

  *index = সংখ্যা;
  ঘূৰাই সঁচা;
}

/* See if VAL is an identifier matching __BB<num> and return <num>
   in *INDEX.  Return true if so and parse also FREQUENCY of
   the edge.  */


স্থির তার্কিক
c_parser_gimple_parse_bb_spec_edge_probability (বৃক্ষ val,
						gimple_parser &parser,
						পূর্ণাঙ্ক *index,
						profile_probability
						*probability)
{
  তার্কিক return_p = c_parser_gimple_parse_bb_spec (val, index);
  যদি (return_p)
    {
      *probability = profile_probability::uninitialized ();
      /* Parse frequency if provided.  */
      যদি (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	{
	  বৃক্ষ f;
	  c_parser_consume_token (parser);
	  যদি (!c_parser_next_token_is (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected frequency quality");
	      ঘূৰাই মিছা;
	    }

	  profile_quality quality;
	  ধ্রুৱ ৱর্ণ *v
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান);
	  যদি (!parse_profile_quality (v, &quality))
	    {
	      c_parser_error (parser, "unknown profile quality");
	      ঘূৰাই মিছা;
	    }

	  c_parser_consume_token (parser);
	  যদি (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    ঘূৰাই মিছা;

	  যদি (!c_parser_next_token_is (parser, CPP_সংখ্যা)
	      || (বৃক্ষ_CODE (f = c_parser_peek_token (parser)->মান)
		  != INTEGER_CST))
	    {
	      c_parser_error (parser, "expected frequency value");
	      ঘূৰাই মিছা;
	    }

	  unsigned পূর্ণাঙ্ক মান = বৃক্ষ_INT_CST_নিচেৰ (f);
	  *probability = profile_probability (মান, quality);

	  c_parser_consume_token (parser);
	  যদি (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    ঘূৰাই মিছা;

	  যদি (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    ঘূৰাই মিছা;
	}

      ঘূৰাই সঁচা;
    }

  ঘূৰাই মিছা;

}

/* Parse the body of a function declaration marked with "__GIMPLE".  */

শূন্য
c_parser_parse_gimple_body (c_parser *cparser, ৱর্ণ *gimple_pass,
			    গণনা c_declspec_il cdil,
			    profile_গুনতি entry_bb_গুনতি)
{
  gimple_parser parser (cparser);
  gimple_seq seq = রিক্ত;
  gimple_seq body = রিক্ত;
  বৃক্ষ stmt = ঠেলো_stmt_list ();
  ঠেলো_scope ();
  location_t loc1 = c_parser_peek_token (parser)->location;

  cfun->pass_startwith = gimple_pass;
  init_বৃক্ষ_ssa (cfun);

  যদি (cdil == cdil_gimple)
    /* While we have SSA names in the IL we do not have a CFG built yet
       and PHIs are represented using a PHI internal function.  We do
       have lowered control flow and exception handling (well, we do not
       have parser support for EH yet).  But as we still have BINDs
       we have to go through lowering again.  */
    cfun->curr_properties = PROP_gimple_any;
  অন্যথা
    {
      /* We have at least cdil_gimple_cfg.  */
      gimple_register_cfg_hooks ();
      init_empty_বৃক্ষ_cfg ();
      parser.current_bb = ENTRY_BLOCK_PTR_FOR_FN (cfun);
      /* Initialize the bare loop structure - we are going to only
         mark headers and leave the rest to fixup.  */
      set_loops_for_fn (cfun, ggc_cleared_alloc<সংরচনা loops> ());
      init_loops_structure (cfun, loops_for_fn (cfun), 1);
      loops_state_set (cfun, LOOPS_NEED_FIXUP|LOOPS_MAY_HAVE_MULTIPLE_LATCHES);
      cfun->curr_properties
	|= PROP_gimple_lcf | PROP_gimple_leh | PROP_cfg | PROP_loops;
      যদি (cdil == cdil_gimple_ssa)
	{
	  init_ssa_operands (cfun);
	  cfun->curr_properties |= PROP_ssa;
	}
    }

  যদি (! c_parser_gimple_compound_statement (parser, &seq)
      && cdil == cdil_gimple)
    {
      gimple *ret = gimple_build_return (রিক্ত);
      gimple_seq_add_stmt_without_update (&seq, ret);
    }

  বৃক্ষ block = বেৰ_কৰো_scope ();
  stmt = বেৰ_কৰো_stmt_list (stmt);
  stmt = c_build_bind_ৰাশিমালা (loc1, block, stmt);

  block = DECL_INITIAL (current_function_decl);
  BLOCK_SUBBLOCKS (block) = NULL_বৃক্ষ;
  BLOCK_CHAIN (block) = NULL_বৃক্ষ;
  বৃক্ষ_ASM_WRITTEN (block) = 1;

  যদি (cdil == cdil_gimple)
    {
      gbind *bind_stmt = gimple_build_bind (BIND_ৰাশিমালা_VARS (stmt), রিক্ত,
					    BIND_ৰাশিমালা_BLOCK (stmt));
      gimple_bind_set_body (bind_stmt, seq);
      gimple_seq_add_stmt_without_update (&body, bind_stmt);
      gimple_set_body (current_function_decl, body);
    }
  অন্যথা
    {
      /* Control-flow and binds are lowered, record local decls.  */
      বাবে (বৃক্ষ var = BIND_ৰাশিমালা_VARS (stmt); var; var = DECL_CHAIN (var))
	যদি (VAR_P (var)
	    && !DECL_EXTERNAL (var))
	  {
	    add_local_decl (cfun, var);
	    /* When the middle-end re-gimplifies any expression we might
	       run into the assertion that we've seen the decl in a BIND.  */
	    যদি (!বৃক্ষ_STATIC (var))
	      DECL_SEEN_IN_BIND_ৰাশিমালা_P (var) = 1;
	  }
      /* We have a CFG.  Build the edges.  */
      বাবে (unsigned i = 0; i < parser.edges.length (); ++i)
	{
	  edge e = make_edge (BASIC_BLOCK_FOR_FN (cfun, parser.edges[i].src),
			      BASIC_BLOCK_FOR_FN (cfun, parser.edges[i].dest),
			      parser.edges[i].flags);
	  e->probability = parser.edges[i].probability;
	}
      /* Add edges for case labels.  */
      basic_block bb;
      FOR_EACH_BB_FN (bb, cfun)
	যদি (EDGE_গুনতি (bb->succs) == 0)
	  {
	    যদি (gswitch *sw = safe_dyn_cast <gswitch *> (*gsi_last_bb (bb)))
	      বাবে (unsigned i = 0; i < gimple_switch_অঙ্ক_labels (sw); ++i)
		{
		  basic_block label_bb = gimple_switch_label_bb (cfun, sw, i);
		  make_edge (bb, label_bb, 0);
		}
	  }
      /* Need those for loop fixup.  */
      calculate_dominance_info (CDI_DOMINATORS);
      /* With SSA lower PHIs parsed as internal function calls and
	 update stmts.  */
      যদি (cdil == cdil_gimple_ssa)
	{
	  /* Create PHI nodes, they are parsed into __PHI internal calls
	     and update SSA operands.  */
	  FOR_EACH_BB_FN (bb, cfun)
	    {
	      gimple_stmt_iterator gsi;
	      বাবে (gsi = gsi_start_bb (bb); !gsi_end_p (gsi);)
		{
		  gimple *stmt = gsi_stmt (gsi);
		  যদি (!gimple_call_internal_p (stmt, IFN_PHI))
		    ভঙ্গ;

		  gphi *phi = create_phi_গ্ৰন্থি (gimple_call_lhs (stmt), bb);
		  বাবে (unsigned i = 0; i < gimple_call_অঙ্ক_args (stmt); i += 2)
		    {
		      পূর্ণাঙ্ক srcidx = বৃক্ষ_INT_CST_নিচেৰ (gimple_call_arg (stmt, i));
		      edge e = find_edge (BASIC_BLOCK_FOR_FN (cfun, srcidx), bb);
		      যদি (!e)
			c_parser_error (parser, "edge not found");
		      অন্যথা
			add_phi_arg (phi, gimple_call_arg (stmt, i + 1), e,
				     UNKNOWN_LOCATION);
		    }
		  gsi_remove (&gsi, সঁচা);
		}
	      বাবে (; !gsi_end_p (gsi); gsi_next (&gsi))
		update_stmt (gsi_stmt (gsi));
	    }
	  /* Fill SSA name gaps, putting them on the freelist and diagnose
	     SSA names without definition.  */
	  বাবে (unsigned i = 1; i < অঙ্ক_ssa_names; ++i)
	    যদি (!ssa_name (i))
	      {
		বৃক্ষ name = make_ssa_name_fn (cfun, integer_type_গ্ৰন্থি, রিক্ত, i);
		release_ssa_name_fn (cfun, name);
	      }
	    অন্যথা যদি (!SSA_NAME_DEF_STMT (ssa_name (i)))
	      error ("SSA name %qE with version %d has no definition",
		     ssa_name (i), i);
	  /* No explicit virtual operands (yet).  */
	  bitmap_obstack_initialize (রিক্ত);
	  update_ssa (TODO_update_ssa_only_virtuals);
	  bitmap_obstack_release (রিক্ত);
	  /* ???  By flushing the freelist after virtual operand SSA rewrite
	     we keep the gaps available for re-use like needed for the
	     PR89595 testcase but then usually virtual operands would have
	     taken most of them.  The fix is obviously to make virtual
	     operands explicit in the SSA IL.  */
	  flush_ssaname_freelist ();
	}
      fix_loop_structure (রিক্ত);
    }

  যদি (cfun->curr_properties & PROP_cfg)
    {
      ENTRY_BLOCK_PTR_FOR_FN (cfun)->গুনতি = entry_bb_গুনতি;
      gcov_type t = param_gimple_fe_computed_hot_bb_threshold;
      set_hot_bb_threshold (t);
      update_max_bb_গুনতি ();
      cgraph_গ্ৰন্থি::get_create (cfun->decl);
      cgraph_edge::rebuild_edges ();
    }

  /* Perform IL validation and if any error is found abort compilation
     of this function by zapping its body.  */
  যদি ((cfun->curr_properties & PROP_cfg)
      && verify_gimple_in_cfg (cfun, মিছা, মিছা))
    init_empty_বৃক্ষ_cfg ();
  অন্যথা যদি (!(cfun->curr_properties & PROP_cfg)
	   && verify_gimple_in_seq (gimple_body (current_function_decl), মিছা))
    gimple_set_body (current_function_decl, রিক্ত);

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

স্থির তার্কিক
c_parser_gimple_compound_statement (gimple_parser &parser, gimple_seq *seq)
{
  তার্কিক return_p = মিছা;

  যদি (! c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    ঘূৰাই মিছা;

  /* A compound statement starts with optional declarations.  */
  যেতিয়ালৈ (c_parser_next_tokens_start_declaration (parser))
    {
      c_parser_gimple_declaration (parser);
      যদি (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	ঘূৰাই মিছা;
    }

  যেতিয়ালৈ (c_parser_next_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      যদি (c_parser_error (parser))
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_BRACE, রিক্ত);
	  ঘূৰাই return_p;
	}
      অন্যথা যদি (c_parser_next_token_is (parser, CPP_EOF))
	{
	  c_parser_error (parser, "expected declaration or statement");
	  ঘূৰাই return_p;
	}

      ৱিকল্প (c_parser_peek_token (parser)->type)
	{
	পক্ষ CPP_KEYWORD:
	  ৱিকল্প (c_parser_peek_token (parser)->keyword)
	    {
	    পক্ষ RID_AT_TRY:
	      c_parser_gimple_try_stmt (parser, seq);
	      ভঙ্গ;
	    পক্ষ RID_IF:
	      c_parser_gimple_if_stmt (parser, seq);
	      ভঙ্গ;
	    পক্ষ RID_SWITCH:
	      c_parser_gimple_switch_stmt (parser, seq);
	      ভঙ্গ;
	    পক্ষ RID_GOTO:
	      {
		location_t loc = c_parser_peek_token (parser)->location;
		c_parser_consume_token (parser);
		যদি (c_parser_next_token_is (parser, CPP_NAME))
		  {
		    বৃক্ষ label = c_parser_peek_token (parser)->মান;
		    c_parser_consume_token (parser);
		    c_parser_gimple_goto_stmt (parser, loc, label, seq);
		    যদি (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      ঘূৰাই return_p;
		  }
		}
	      ভঙ্গ;
	    পক্ষ RID_RETURN:
	      return_p = সঁচা;
	      c_parser_gimple_return_stmt (parser, seq);
	      যদি (! c_parser_require (parser, CPP_SEMICOLON,
				      "expected %<;%>"))
		ঘূৰাই return_p;
	      যদি (cfun->curr_properties & PROP_cfg)
		parser.ঠেলো_edge (parser.current_bb->index, EXIT_BLOCK, 0,
				  profile_probability::uninitialized ());
	      ভঙ্গ;
	    স্ৱভাৱ:
	      গচ্ছ ৰাশিমালা_stmt;
	    }
	  ভঙ্গ;
	পক্ষ CPP_NAME:
	  যদি (c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_gimple_label (parser, seq);
	      ভঙ্গ;
	    }
	  যদি (c_parser_next_token_is (parser, CPP_NAME)
	      && c_parser_peek_token (parser)->id_kind == C_ID_ID
	      && strcmp (IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান),
			 "try") == 0)
	    {
	      c_parser_gimple_try_stmt (parser, seq);
	      ভঙ্গ;
	    }
	  /* Basic block specification.
	     __BB (index, ...)  */
	  যদি ((cfun->curr_properties & PROP_cfg)
	      && !strcmp (IDENTIFIER_POINTER
			    (c_parser_peek_token (parser)->মান), "__BB"))
	    {
	      c_parser_consume_token (parser);
	      যদি (! c_parser_require (parser, CPP_OPEN_PAREN,
				      "expected %<(%>"))
		ঘূৰাই return_p;
	      যদি (c_parser_next_token_is_not (parser, CPP_সংখ্যা))
		{
		  c_parser_error (parser, "expected block index");
		  ঘূৰাই return_p;
		}
	      বৃক্ষ tnum = c_parser_peek_token (parser)->মান;
	      যদি (বৃক্ষ_CODE (tnum) != INTEGER_CST)
		{
		  c_parser_error (parser, "expected block index");
		  ঘূৰাই return_p;
		}
	      পূর্ণাঙ্ক index = বৃক্ষ_INT_CST_নিচেৰ (tnum);
	      যদি (index < অঙ্ক_FIXED_BLOCKS
		  || (index < last_basic_block_for_fn (cfun)
		      && BASIC_BLOCK_FOR_FN (cfun, index) != রিক্ত))
		{
		  c_parser_error (parser, "invalid block index");
		  ঘূৰাই return_p;
		}
	      পূর্ণাঙ্ক is_loop_header_of = -1;
	      profile_গুনতি bb_গুনতি = profile_গুনতি::uninitialized ();
	      c_parser_consume_token (parser);
	      যেতিয়ালৈ (c_parser_next_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  যদি (! c_parser_next_token_is (parser, CPP_NAME))
		    {
		      c_parser_error (parser, "expected block specifier");
		      ঘূৰাই return_p;
		    }
		  /* loop_header (NUM)  */
		  যদি (!strcmp (IDENTIFIER_POINTER
			         (c_parser_peek_token (parser)->মান),
			       "loop_header"))
		    {
		      c_parser_consume_token (parser);
		      যদি (! c_parser_require (parser, CPP_OPEN_PAREN,
					      "expected %<(%>"))
			ঘূৰাই return_p;
		      বৃক্ষ loop_অঙ্ক;
		      যদি (! c_parser_next_token_is (parser, CPP_সংখ্যা)
			  || বৃক্ষ_CODE (loop_অঙ্ক
					  = c_parser_peek_token (parser)->মান)
			       != INTEGER_CST)
			{
			  c_parser_error (parser, "expected loop number");
			  ঘূৰাই return_p;
			}
		      c_parser_consume_token (parser);
		      is_loop_header_of = বৃক্ষ_INT_CST_নিচেৰ (loop_অঙ্ক);
		      যদি (! c_parser_require (parser, CPP_CLOSE_PAREN,
					      "expected %<)%>"))
			ঘূৰাই return_p;
		    }
		  /* Parse profile: quality(value) */
		  অন্যথা
		    {
		      বৃক্ষ q;
		      profile_quality quality;
		      বৃক্ষ v = c_parser_peek_token (parser)->মান;
		      যদি (!parse_profile_quality (IDENTIFIER_POINTER (v),
						  &quality))
			{
			  c_parser_error (parser, "unknown block specifier");
			  ঘূৰাই মিছা;
			}

		      c_parser_consume_token (parser);
		      যদি (!c_parser_require (parser, CPP_OPEN_PAREN,
					     "expected %<(%>"))
			ঘূৰাই মিছা;

		      যদি (!c_parser_next_token_is (parser, CPP_সংখ্যা)
			  || (বৃক্ষ_CODE (q = c_parser_peek_token (parser)->মান)
			      != INTEGER_CST))
			{
			  c_parser_error (parser, "expected count value");
			  ঘূৰাই মিছা;
			}

		      bb_গুনতি
			= profile_গুনতি::from_gcov_type (বৃক্ষ_INT_CST_নিচেৰ (q),
							 quality);
		      c_parser_consume_token (parser);
		      যদি (! c_parser_require (parser, CPP_CLOSE_PAREN,
					      "expected %<)%>"))
			ঘূৰাই return_p;
		    }
		}
	      যদি (! c_parser_require (parser, CPP_CLOSE_PAREN,
				      "expected %<)%>")
		  || ! c_parser_require (parser, CPP_COLON,
					 "expected %<:%>"))
		ঘূৰাই return_p;

	      /* Put stmts parsed in the current block.  */
	      যদি (!gimple_seq_empty_p (*seq))
		{
		  যদি (!parser.current_bb)
		    c_parser_error (parser, "stmts without block");
		  অন্যথা
		    {
		      gimple_stmt_iterator gsi
			= gsi_start_bb (parser.current_bb);
		      gsi_ঢোকাও_seq_after_without_update (&gsi, *seq,
							   GSI_CONTINUE_LINKING);
		    }
		  *seq = রিক্ত;
		}

	      /* Build an empty block with specified index, linking them
		 in source order.  */
	      basic_block bb = alloc_block ();
	      bb->index = index;
	      link_block (bb, (parser.current_bb ? parser.current_bb
			       : ENTRY_BLOCK_PTR_FOR_FN (cfun)));
	      যদি (basic_block_info_for_fn (cfun)->length () <= (size_t)index)
		vec_safe_grow_cleared (basic_block_info_for_fn (cfun),
				       index + 1, সঁচা);
	      SET_BASIC_BLOCK_FOR_FN (cfun, index, bb);
	      যদি (last_basic_block_for_fn (cfun) <= index)
		last_basic_block_for_fn (cfun) = index + 1;
	      n_basic_blocks_for_fn (cfun)++;
	      যদি (parser.current_bb->index == ENTRY_BLOCK)
		parser.ঠেলো_edge (ENTRY_BLOCK, bb->index, EDGE_FALLTHRU,
				  profile_probability::always ());

	      /* We leave the proper setting to fixup.  */
	      শ্ৰেণী loop *loop_father = loops_for_fn (cfun)->বৃক্ষ_মূল;
	      /* If the new block is a loop header, allocate a loop
		 struct.  Fixup will take care of proper placement within
		 the loop tree.  */
	      যদি (is_loop_header_of != -1)
		{
		  যদি (সংখ্যা_of_loops (cfun) > (unsigned)is_loop_header_of
		      && get_loop (cfun, is_loop_header_of) != রিক্ত)
		    {
		      c_parser_error (parser, "duplicate loop header");
		    }
		  অন্যথা
		    {
		      শ্ৰেণী loop *loop = alloc_loop ();
		      loop->অঙ্ক = is_loop_header_of;
		      loop->header = bb;
		      যদি (সংখ্যা_of_loops (cfun) <= (unsigned)is_loop_header_of)
			vec_safe_grow_cleared (loops_for_fn (cfun)->larray,
					       is_loop_header_of + 1, সঁচা);
		      (*loops_for_fn (cfun)->larray)[is_loop_header_of] = loop;
		      flow_loop_বৃক্ষ_গ্ৰন্থি_add (loops_for_fn (cfun)->বৃক্ষ_মূল,
					       loop);
		    }
		  loop_father = get_loop (cfun, is_loop_header_of);
		}
	      bb->loop_father = loop_father;
	      bb->গুনতি = bb_গুনতি;

	      /* Stmts now go to the new block.  */
	      parser.current_bb = bb;
	      ভঙ্গ;
	    }
	  গচ্ছ ৰাশিমালা_stmt;

	পক্ষ CPP_SEMICOLON:
	  {
	    /* Empty stmt.  */
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);
	    gimple *nop = gimple_build_nop ();
	    gimple_set_location (nop, loc);
	    gimple_seq_add_stmt_without_update (seq, nop);
	    ভঙ্গ;
	  }

	পক্ষ CPP_CLOSE_PAREN:
	পক্ষ CPP_CLOSE_SQUARE:
	  /* Avoid infinite loop in error recovery:
	     c_parser_skip_until_found stops at a closing nesting
	     delimiter without consuming it, but here we need to consume
	     it to proceed further.  */
	  c_parser_error (parser, "expected statement");
	  c_parser_consume_token (parser);
	ভঙ্গ;

	স্ৱভাৱ:
ৰাশিমালা_stmt:
	  c_parser_gimple_statement (parser, seq);
	  যদি (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	    c_parser_skip_until_found (parser, CPP_SEMICOLON, রিক্ত);
	}
    }
  c_parser_consume_token (parser);

  /* Put stmts parsed in the current block.  */
  যদি ((cfun->curr_properties & PROP_cfg)
      && !gimple_seq_empty_p (*seq))
    {
      যদি (!parser.current_bb)
	c_parser_error (parser, "stmts without block");
      অন্যথা
	{
	  gimple_stmt_iterator gsi = gsi_start_bb (parser.current_bb);
	  gsi_ঢোকাও_seq_after_without_update (&gsi, *seq,
					       GSI_CONTINUE_LINKING);
	}
      *seq = রিক্ত;
    }

  ঘূৰাই return_p;
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

স্থির শূন্য
c_parser_gimple_statement (gimple_parser &parser, gimple_seq *seq)
{
  সংরচনা c_ৰাশিমালা lhs, rhs;
  gimple *assign = রিক্ত;
  location_t loc;
  বৃক্ষ arg = NULL_বৃক্ষ;
  auto_vec<বৃক্ষ> vargs;

  lhs = c_parser_gimple_unary_expression (parser);
  loc = ৰাশিমালা_LOCATION (lhs.মান);
  rhs.set_error ();

  /* GIMPLE call statement without LHS.  */
  যদি (c_parser_next_token_is (parser, CPP_SEMICOLON)
      && বৃক্ষ_CODE (lhs.মান) == CALL_ৰাশিমালা)
    {
      gimple *call;
      call = gimple_build_call_from_বৃক্ষ (lhs.মান, রিক্ত);
      gimple_seq_add_stmt_without_update (seq, call);
      gimple_set_location (call, loc);
      ঘূৰাই;
    }

  /* All following cases are statements with LHS.  */
  যদি (! c_parser_require (parser, CPP_EQ, "expected %<=%>"))
    ঘূৰাই;

  /* Eat and ignore {v} right after the =, the has_volatile_ops is
     redundant and re-computed by the operand scanner.  */
  যদি (c_parser_next_token_is (parser, CPP_OPEN_BRACE)
      && !(c_parser_peek_token (parser)->flags & PREV_WHITE)
      && c_parser_peek_2nd_token (parser)->type == CPP_NAME
      && !(c_parser_peek_2nd_token (parser)->flags & PREV_WHITE)
      && strcmp ("v", IDENTIFIER_POINTER
			(c_parser_peek_2nd_token (parser)->মান)) == 0
      && c_parser_peek_nth_token (parser, 3)->type == CPP_CLOSE_BRACE
      && !(c_parser_peek_nth_token (parser, 3)->flags & PREV_WHITE))
    {
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }

  /* Cast expression.  */
  যদি (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_typename (c_parser_peek_2nd_token (parser)))
    {
      c_parser_consume_token (parser);
      সংরচনা c_type_name *type_name = c_parser_type_name (parser);
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      যদি (type_name == রিক্ত)
	ঘূৰাই;
      /* ???  The actual type used in the cast expression is ignored as
         in GIMPLE it is encoded by the type of the LHS.  */
      rhs = c_parser_gimple_postfix_expression (parser);
      যদি (lhs.মান != error_mark_গ্ৰন্থি
	  && rhs.মান != error_mark_গ্ৰন্থি)
	{
	  গণনা বৃক্ষ_code code = NOP_ৰাশিমালা;
	  যদি (FLOAT_TYPE_P (বৃক্ষ_TYPE (lhs.মান))
	      && ! FLOAT_TYPE_P (বৃক্ষ_TYPE (rhs.মান)))
	    code = FLOAT_ৰাশিমালা;
	  অন্যথা যদি (! FLOAT_TYPE_P (বৃক্ষ_TYPE (lhs.মান))
		   && FLOAT_TYPE_P (বৃক্ষ_TYPE (rhs.মান)))
	    code = FIX_TRUNC_ৰাশিমালা;
	  assign = gimple_build_assign (lhs.মান, code, rhs.মান);
	  gimple_seq_add_stmt_without_update (seq, assign);
	  gimple_set_location (assign, loc);
	  ঘূৰাই;
	}
    }

  /* Unary expression.  */
  ৱিকল্প (c_parser_peek_token (parser)->type)
    {
    পক্ষ CPP_NAME:
      {
	বৃক্ষ id = c_parser_peek_token (parser)->মান;
	যদি (strcmp (IDENTIFIER_POINTER (id), "__ABS") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__ABSU") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__MIN") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__MAX") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__BIT_INSERT") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__VEC_PERM") == 0)
	  গচ্ছ build_unary_ৰাশিমালা;
	ভঙ্গ;
      }
    পক্ষ CPP_KEYWORD:
      যদি (c_parser_peek_token (parser)->keyword != RID_REALPART
	  && c_parser_peek_token (parser)->keyword != RID_IMAGPART)
	ভঙ্গ;
      /* Fallthru.  */
    পক্ষ CPP_AND:
    পক্ষ CPP_PLUS:
    পক্ষ CPP_MINUS:
    পক্ষ CPP_COMPL:
    পক্ষ CPP_NOT:
    পক্ষ CPP_MULT: /* pointer deref */
    build_unary_ৰাশিমালা:
      rhs = c_parser_gimple_unary_expression (parser);
      যদি (rhs.মান != error_mark_গ্ৰন্থি)
	{
	  assign = gimple_build_assign (lhs.মান, rhs.মান);
	  gimple_set_location (assign, loc);
	  gimple_seq_add_stmt_without_update (seq, assign);
	}
      ঘূৰাই;

    স্ৱভাৱ:;
    }

  /* GIMPLE PHI statement.  */
  যদি (c_parser_next_token_is_keyword (parser, RID_PHI))
    {
      c_parser_consume_token (parser);

      যদি (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	ঘূৰাই;

      যদি (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	c_parser_consume_token (parser);

      যেতিয়ালৈ (c_parser_next_token_is_not (parser, CPP_CLOSE_PAREN))
	{
	  যদি (c_parser_next_token_is (parser, CPP_NAME)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      arg = c_parser_peek_token (parser)->মান;
	      c_parser_consume_token (parser);
	      যদি (c_parser_next_token_is (parser, CPP_COLON))
		c_parser_consume_token (parser);
	      পূর্ণাঙ্ক src_index = -1;
	      যদি (!c_parser_gimple_parse_bb_spec (arg, &src_index))
		c_parser_error (parser, "invalid source block specification");
	      vargs.safe_ঠেলো (size_int (src_index));
	    }
	  অন্যথা যদি (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  অন্যথা
	    {
	      arg = c_parser_gimple_unary_expression (parser).মান;
	      vargs.safe_ঠেলো (arg);
	    }
	}

      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");

      /* Build internal function for PHI.  */
      gcall *call_stmt = gimple_build_call_internal_vec (IFN_PHI, vargs);
      gimple_call_set_lhs (call_stmt, lhs.মান);
      gimple_set_location (call_stmt, UNKNOWN_LOCATION);
      gimple_seq_add_stmt_without_update (seq, call_stmt);
      ঘূৰাই;
    }

  /* GIMPLE call with lhs.  */
  যদি (c_parser_next_token_is (parser, CPP_DOT)
      || (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN
	  && lookup_name (c_parser_peek_token (parser)->মান)))
    {
      rhs = c_parser_gimple_unary_expression (parser);
      যদি (rhs.মান != error_mark_গ্ৰন্থি)
	{
	  gimple *call = gimple_build_call_from_বৃক্ষ (rhs.মান, রিক্ত);
	  gimple_call_set_lhs (call, lhs.মান);
	  gimple_seq_add_stmt_without_update (seq, call);
	  gimple_set_location (call, loc);
	}
      ঘূৰাই;
    }

  rhs = c_parser_gimple_দ্বিমিক_expression (parser, বৃক্ষ_TYPE (lhs.মান));
  যদি (lhs.মান != error_mark_গ্ৰন্থি
      && rhs.মান != error_mark_গ্ৰন্থি)
    {
      /* If we parsed an identifier and the next token  is a '?' then parse
	 a conditional expression.  */
      যদি (SSA_VAR_P (rhs.মান) && c_parser_next_token_is (parser, CPP_QUERY))
	{
	  সংরচনা c_ৰাশিমালা trueval, falseval;
	  c_parser_consume_token (parser);
	  trueval = c_parser_gimple_postfix_expression (parser);
	  falseval.set_error ();
	  যদি (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    falseval = c_parser_gimple_postfix_expression (parser);
	  যদি (trueval.মান == error_mark_গ্ৰন্থি
	      || falseval.মান == error_mark_গ্ৰন্থি)
	    ঘূৰাই;
	  rhs.মান = build3_loc (loc,
				  VECTOR_TYPE_P (বৃক্ষ_TYPE (rhs.মান))
				  ? VEC_COND_ৰাশিমালা : COND_ৰাশিমালা,
				  বৃক্ষ_TYPE (trueval.মান),
				  rhs.মান, trueval.মান, falseval.মান);
	}
      যদি (get_gimple_rhs_class (বৃক্ষ_CODE (rhs.মান)) == GIMPLE_INVALID_RHS)
	{
	  c_parser_error (parser, "unexpected RHS for assignment");
	  ঘূৰাই;
	}
      assign = gimple_build_assign (lhs.মান, rhs.মান);
      gimple_seq_add_stmt_without_update (seq, assign);
      gimple_set_location (assign, loc);
    }
  ঘূৰাই;
}

/* A mapping between an identifier to a tree code for binary operations. */
স্থির ধ্রুৱ std::pair<ধ্রুৱ ৱর্ণ *, বৃক্ষ_code> gimple_দ্বিমিক_identifier_code[] =
  {
    {"__MULT_HIGHPART", MULT_HIGHPART_ৰাশিমালা},
    {"__UNLT", UNLT_ৰাশিমালা},
    {"__UNLE", UNLE_ৰাশিমালা},
    {"__UNGT", UNGT_ৰাশিমালা},
    {"__UNGE", UNGE_ৰাশিমালা},
    {"__UNEQ", UNEQ_ৰাশিমালা},
    {"__UNORDERED", UNORDERED_ৰাশিমালা},
    {"__ORDERED", ORDERED_ৰাশিমালা},
    {"__LTGT", LTGT_ৰাশিমালা},
    {"__FLOOR_DIV", FLOOR_DIV_ৰাশিমালা},
    {"__ROUND_DIV", ROUND_DIV_ৰাশিমালা},
    {"__EXACT_DIV", EXACT_DIV_ৰাশিমালা},
    {"__CEIL_DIV", CEIL_DIV_ৰাশিমালা},
    {"__FLOOR_MOD", FLOOR_MOD_ৰাশিমালা},
    {"__ROUND_MOD", ROUND_MOD_ৰাশিমালা},
    {"__CEIL_MOD", CEIL_MOD_ৰাশিমালা},
    {"__ROTATE_LEFT", LROTATE_ৰাশিমালা},
    {"__ROTATE_RIGHT", RROTATE_ৰাশিমালা},
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

স্থির c_ৰাশিমালা
c_parser_gimple_দ্বিমিক_expression (gimple_parser &parser, বৃক্ষ ret_type)
{
  /* Location of the binary operator.  */
  সংরচনা c_ৰাশিমালা ret, lhs, rhs;
  গণনা বৃক্ষ_code code = ERROR_MARK;
  ret.set_error ();
  lhs = c_parser_gimple_postfix_expression (parser, ret_type);
  যদি (c_parser_error (parser))
    ঘূৰাই ret;
  ৱিকল্প (c_parser_peek_token (parser)->type)
    {
    পক্ষ CPP_MULT:
      code = MULT_ৰাশিমালা;
      ভঙ্গ;
    পক্ষ CPP_DIV:
      code = TRUNC_DIV_ৰাশিমালা;
      ভঙ্গ;
    পক্ষ CPP_MOD:
      code = TRUNC_MOD_ৰাশিমালা;
      ভঙ্গ;
    পক্ষ CPP_PLUS:
      যদি (POINTER_TYPE_P (বৃক্ষ_TYPE (lhs.মান)))
	code = POINTER_PLUS_ৰাশিমালা;
      অন্যথা
	code = PLUS_ৰাশিমালা;
      ভঙ্গ;
    পক্ষ CPP_MINUS:
      যদি (POINTER_TYPE_P (বৃক্ষ_TYPE (lhs.মান)))
	code = POINTER_DIFF_ৰাশিমালা;
      অন্যথা
	code = MINUS_ৰাশিমালা;
      ভঙ্গ;
    পক্ষ CPP_LSHIFT:
      code = LSHIFT_ৰাশিমালা;
      ভঙ্গ;
    পক্ষ CPP_RSHIFT:
      code = RSHIFT_ৰাশিমালা;
      ভঙ্গ;
    পক্ষ CPP_LESS:
      code = LT_ৰাশিমালা;
      ভঙ্গ;
    পক্ষ CPP_GREATER:
      code = GT_ৰাশিমালা;
      ভঙ্গ;
    পক্ষ CPP_LESS_EQ:
      code = LE_ৰাশিমালা;
      ভঙ্গ;
    পক্ষ CPP_GREATER_EQ:
      code = GE_ৰাশিমালা;
      ভঙ্গ;
    পক্ষ CPP_EQ_EQ:
      code = EQ_ৰাশিমালা;
      ভঙ্গ;
    পক্ষ CPP_NOT_EQ:
      code = NE_ৰাশিমালা;
      ভঙ্গ;
    পক্ষ CPP_AND:
      code = BIT_AND_ৰাশিমালা;
      ভঙ্গ;
    পক্ষ CPP_XOR:
      code = BIT_XOR_ৰাশিমালা;
      ভঙ্গ;
    পক্ষ CPP_OR:
      code = BIT_IOR_ৰাশিমালা;
      ভঙ্গ;
    পক্ষ CPP_AND_AND:
      c_parser_error (parser, "%<&&%> not valid in GIMPLE");
      ঘূৰাই ret;
    পক্ষ CPP_OR_OR:
      c_parser_error (parser, "%<||%> not valid in GIMPLE");
      ঘূৰাই ret;
    পক্ষ CPP_NAME:
      {
	বৃক্ষ id = c_parser_peek_token (parser)->মান;
	বাবে (auto &p : gimple_দ্বিমিক_identifier_code)
	  {
	    যদি (strcmp (IDENTIFIER_POINTER (id), p.first) == 0)
	      {
		code = p.second;
		ভঙ্গ;
	      }
	  }
	যদি (code != ERROR_MARK)
	  ভঙ্গ;
      }
      /* Fallthru.  */
    স্ৱভাৱ:
      /* Not a binary expression.  */
      ঘূৰাই lhs;
    }
  location_t ret_loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  rhs = c_parser_gimple_postfix_expression (parser);
  যদি (lhs.মান != error_mark_গ্ৰন্থি && rhs.মান != error_mark_গ্ৰন্থি)
    ret.মান = build2_loc (ret_loc, code, ret_type, lhs.মান, rhs.মান);
  ঘূৰাই ret;
}

/* Parse a gimple parentized binary expression.  */

স্থির c_ৰাশিমালা
c_parser_gimple_parentized_দ্বিমিক_expression (gimple_parser &parser,
					      location_t op_loc,
					      বৃক্ষ_code code)
{
  সংরচনা c_ৰাশিমালা ret;
  ret.set_error ();

  c_parser_consume_token (parser);
  যদি (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    ঘূৰাই ret;
  c_ৰাশিমালা op1 = c_parser_gimple_postfix_expression (parser);
  যদি (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    ঘূৰাই ret;
  c_ৰাশিমালা op2 = c_parser_gimple_postfix_expression (parser);
  যদি (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    ঘূৰাই ret;

  যদি (op1.মান != error_mark_গ্ৰন্থি && op2.মান != error_mark_গ্ৰন্থি)
    ret.মান = build2_loc (op_loc,
			    code, বৃক্ষ_TYPE (op1.মান), op1.মান, op2.মান);
  ঘূৰাই ret;
}

/* Parse a gimple parentized binary expression.  */

স্থির c_ৰাশিমালা
c_parser_gimple_parentized_ternary_expression (gimple_parser &parser,
					       location_t op_loc,
					       বৃক্ষ_code code)
{
  সংরচনা c_ৰাশিমালা ret;
  ret.set_error ();

  c_parser_consume_token (parser);
  যদি (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    ঘূৰাই ret;
  c_ৰাশিমালা op1 = c_parser_gimple_postfix_expression (parser);
  যদি (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    ঘূৰাই ret;
  c_ৰাশিমালা op2 = c_parser_gimple_postfix_expression (parser);
  যদি (!c_parser_require (parser, CPP_COMMA, "expected %<)%>"))
    ঘূৰাই ret;
  c_ৰাশিমালা op3 = c_parser_gimple_postfix_expression (parser);
  যদি (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    ঘূৰাই ret;

  যদি (op1.মান != error_mark_গ্ৰন্থি
      && op2.মান != error_mark_গ্ৰন্থি
      && op3.মান != error_mark_গ্ৰন্থি)
    ret.মান = build3_loc (op_loc,
			    code, বৃক্ষ_TYPE (op1.মান),
			    op1.মান, op2.মান, op3.মান);
  ঘূৰাই ret;
}

/* Parse gimple unary expression.

   gimple-unary-expression:
     gimple-postfix-expression
     unary-operator gimple-postfix-expression

   unary-operator: one of
     & * + - ~ abs_expr
*/

স্থির c_ৰাশিমালা
c_parser_gimple_unary_expression (gimple_parser &parser)
{
  সংরচনা c_ৰাশিমালা ret, op;
  location_t op_loc = c_parser_peek_token (parser)->location;
  location_t finish;
  ret.set_error ();
  ৱিকল্প (c_parser_peek_token (parser)->type)
    {
    পক্ষ CPP_AND:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      mark_exp_read (op.মান);
      ঘূৰাই gimple_parser_build_unary_op (op_loc, ADDR_ৰাশিমালা, op);
    পক্ষ CPP_MULT:
      {
	c_parser_consume_token (parser);
	op = c_parser_gimple_postfix_expression (parser);
	যদি (op.মান == error_mark_গ্ৰন্থি)
	  ঘূৰাই ret;
	যদি (! POINTER_TYPE_P (বৃক্ষ_TYPE (op.মান)))
	  {
	    error_at (op_loc, "expected pointer as argument of unary %<*%>");
	    ঘূৰাই ret;
	  }
	finish = op.get_finish ();
	location_t combined_loc = make_location (op_loc, op_loc, finish);
	ret.মান = build_simple_mem_ref_loc (combined_loc, op.মান);
	বৃক্ষ_SIDE_EFFECTS (ret.মান)
	  = বৃক্ষ_THIS_VOLATILE (ret.মান)
	  = TYPE_VOLATILE (বৃক্ষ_TYPE (বৃক্ষ_TYPE (op.মান)));
	ret.src_range.m_start = op_loc;
	ret.src_range.m_finish = finish;
	ঘূৰাই ret;
      }
    পক্ষ CPP_PLUS:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      ঘূৰাই gimple_parser_build_unary_op (op_loc, CONVERT_ৰাশিমালা, op);
    পক্ষ CPP_MINUS:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      ঘূৰাই gimple_parser_build_unary_op (op_loc, NEGATE_ৰাশিমালা, op);
    পক্ষ CPP_COMPL:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      ঘূৰাই gimple_parser_build_unary_op (op_loc, BIT_NOT_ৰাশিমালা, op);
    পক্ষ CPP_NOT:
      c_parser_error (parser, "%<!%> not valid in GIMPLE");
      ঘূৰাই ret;
    পক্ষ CPP_KEYWORD:
      ৱিকল্প (c_parser_peek_token (parser)->keyword)
	{
	পক্ষ RID_REALPART:
	  c_parser_consume_token (parser);
	  op = c_parser_gimple_postfix_expression (parser);
	  ঘূৰাই gimple_parser_build_unary_op (op_loc, REALPART_ৰাশিমালা, op);
	পক্ষ RID_IMAGPART:
	  c_parser_consume_token (parser);
	  op = c_parser_gimple_postfix_expression (parser);
	  ঘূৰাই gimple_parser_build_unary_op (op_loc, IMAGPART_ৰাশিমালা, op);
	স্ৱভাৱ:
	  ঘূৰাই c_parser_gimple_postfix_expression (parser);
	}
    পক্ষ CPP_NAME:
	{
	  বৃক্ষ id = c_parser_peek_token (parser)->মান;
	  যদি (strcmp (IDENTIFIER_POINTER (id), "__ABS") == 0)
	    {
	      c_parser_consume_token (parser);
	      op = c_parser_gimple_postfix_expression (parser);
	      ঘূৰাই gimple_parser_build_unary_op (op_loc, ABS_ৰাশিমালা, op);
	    }
	  অন্যথা যদি (strcmp (IDENTIFIER_POINTER (id), "__ABSU") == 0)
	    {
	      c_parser_consume_token (parser);
	      op = c_parser_gimple_postfix_expression (parser);
	      ঘূৰাই gimple_parser_build_unary_op (op_loc, ABSU_ৰাশিমালা, op);
	    }
	  অন্যথা যদি (strcmp (IDENTIFIER_POINTER (id), "__MIN") == 0)
	    ঘূৰাই c_parser_gimple_parentized_দ্বিমিক_expression (parser,
								 op_loc,
								 MIN_ৰাশিমালা);
	  অন্যথা যদি (strcmp (IDENTIFIER_POINTER (id), "__MAX") == 0)
	    ঘূৰাই c_parser_gimple_parentized_দ্বিমিক_expression (parser,
								 op_loc,
								 MAX_ৰাশিমালা);
	  অন্যথা যদি (strcmp (IDENTIFIER_POINTER (id), "__VEC_PERM") == 0)
	    ঘূৰাই c_parser_gimple_parentized_ternary_expression
			(parser, op_loc, VEC_PERM_ৰাশিমালা);
	  অন্যথা যদি (strcmp (IDENTIFIER_POINTER (id), "__BIT_INSERT") == 0)
	    {
	      /* __BIT_INSERT '(' postfix-expression, postfix-expression,
			          integer ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      যদি (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_ৰাশিমালা op0 = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_ৰাশিমালা op1 = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_ৰাশিমালা op2 = c_parser_gimple_postfix_expression (parser);
		  যদি (বৃক্ষ_CODE (op2.মান) != INTEGER_CST
		      || !int_fits_type_p (op2.মান, bitsizetype))
		    c_parser_error (parser, "expected constant offset");
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  যদি (op0.মান != error_mark_গ্ৰন্থি
		      && op1.মান != error_mark_গ্ৰন্থি
		      && বৃক্ষ_CODE (op2.মান) == INTEGER_CST)
		    ret.মান = build3_loc (loc, BIT_ঢোকাও_ৰাশিমালা,
					    বৃক্ষ_TYPE (op0.মান),
					    op0.মান, op1.মান,
					    fold_convert (bitsizetype,
							  op2.মান));
		}
	      ঘূৰাই ret;
	    }
	  অন্যথা
	    ঘূৰাই c_parser_gimple_postfix_expression (parser);
	}
    স্ৱভাৱ:
      ঘূৰাই c_parser_gimple_postfix_expression (parser);
    }
}

/* Decompose ID into base name (ID until ver_offset) and VERSION.  Return
   true if ID matches a SSA name.  */

স্থির তার্কিক
c_parser_parse_ssa_name_id (বৃক্ষ id, unsigned *version, unsigned *ver_offset)
{
  ধ্রুৱ ৱর্ণ *token = IDENTIFIER_POINTER (id);
  ধ্রুৱ ৱর্ণ *var_version = strrchr (token, '_');
  যদি (! var_version)
    ঘূৰাই মিছা;

  *ver_offset = var_version - token;
  বাবে (ধ্রুৱ ৱর্ণ *p = var_version + 1; *p; ++p)
    যদি (! ISDIGIT (*p))
      ঘূৰাই মিছা;
  *version = atoi (var_version + 1);
  ঘূৰাই *version > 0;
}

/* Get at the actual SSA name ID with VERSION starting at VER_OFFSET.
   TYPE is the type if the SSA name is being declared.  */

স্থির বৃক্ষ
c_parser_parse_ssa_name (gimple_parser &parser,
			 বৃক্ষ id, বৃক্ষ type, unsigned version,
			 unsigned ver_offset)
{
  বৃক্ষ name = NULL_বৃক্ষ;
  ধ্রুৱ ৱর্ণ *token = IDENTIFIER_POINTER (id);

  যদি (ver_offset == 0)
    {
      /* Anonymous unnamed SSA name.  */
      যদি (version < অঙ্ক_ssa_names)
	name = ssa_name (version);
      যদি (! name)
	{
	  যদি (! type)
	    {
	      c_parser_error (parser, "SSA name undeclared");
	      ঘূৰাই error_mark_গ্ৰন্থি;
	    }
	  name = make_ssa_name_fn (cfun, type, রিক্ত, version);
	}
    }
  অন্যথা
    {
      যদি (version < অঙ্ক_ssa_names)
	name = ssa_name (version);
      যদি (! name)
	{
	  /* Separate var name from version.  */
	  ৱর্ণ *var_name = XNEWVEC (ৱর্ণ, ver_offset + 1);
	  memcpy (var_name, token, ver_offset);
	  var_name[ver_offset] = '\0';
	  /* lookup for parent decl.  */
	  id = get_identifier (var_name);
	  বৃক্ষ parent = lookup_name (id);
	  XDELETEVEC (var_name);
	  যদি (! parent || parent == error_mark_গ্ৰন্থি)
	    {
	      c_parser_error (parser, "base variable or SSA name undeclared");
	      ঘূৰাই error_mark_গ্ৰন্থি;
	    }
	  যদি (!(VAR_P (parent)
		|| বৃক্ষ_CODE (parent) == PARM_DECL
		|| বৃক্ষ_CODE (parent) == RESULT_DECL))
	    {
	      error ("invalid base %qE for SSA name", parent);
	      ঘূৰাই error_mark_গ্ৰন্থি;
	    }
	  name = make_ssa_name_fn (cfun, parent,
				   gimple_build_nop (), version);
	}
    }

  ঘূৰাই name;
}

/* Parse a gimple call to an internal function.

   gimple-call-internal:
     . identifier ( gimple-argument-expression-list[opt] )  */

স্থির সংরচনা c_ৰাশিমালা
c_parser_gimple_call_internal (gimple_parser &parser)
{
  সংরচনা c_ৰাশিমালা ৰাশিমালা;
  ৰাশিমালা.set_error ();

  gcc_assert (c_parser_next_token_is (parser, CPP_DOT));
  c_parser_consume_token (parser);
  location_t loc = c_parser_peek_token (parser)->location;
  যদি (!c_parser_next_token_is (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_kind != C_ID_ID)
    {
      c_parser_error (parser, "expecting internal function name");
      ঘূৰাই ৰাশিমালা;
    }
  বৃক্ষ id = c_parser_peek_token (parser)->মান;
  internal_fn ifn = lookup_internal_fn (IDENTIFIER_POINTER (id));
  c_parser_consume_token (parser);
  যদি (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    {
      auto_vec<বৃক্ষ> exprlist;
      যদি (!c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_gimple_ৰাশিমালা_list (parser, &exprlist);
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      যদি (ifn == IFN_LAST)
	error_at (loc, "unknown internal function %qE", id);
      অন্যথা
	{
	  ৰাশিমালা.মান = build_call_ৰাশিমালা_internal_loc_array
	    (loc, ifn, void_type_গ্ৰন্থি, exprlist.length (),
	     exprlist.address ());
	  ৰাশিমালা.original_code = ERROR_MARK;
	  ৰাশিমালা.original_type = রিক্ত;
	  ৰাশিমালা.m_decimal = 0;
	}
    }
  ঘূৰাই ৰাশিমালা;
}

/* Parse '<' type [',' alignment] '>' and return a type on success
   and NULL_TREE on error.  */

স্থির বৃক্ষ
c_parser_gimple_typespec (gimple_parser &parser)
{
  সংরচনা c_type_name *type_name = রিক্ত;
  বৃক্ষ alignment = NULL_বৃক্ষ;
  যদি (c_parser_require (parser, CPP_LESS, "expected %<<%>"))
    {
      type_name = c_parser_type_name (parser);
      /* Optional alignment.  */
      যদি (c_parser_next_token_is (parser, CPP_COMMA))
	{
	  c_parser_consume_token (parser);
	  alignment
	      = c_parser_gimple_postfix_expression (parser).মান;
	}
      c_parser_skip_until_found (parser,
				 CPP_GREATER, "expected %<>%>");
    }
  যদি (!type_name)
    ঘূৰাই NULL_বৃক্ষ;
  বৃক্ষ tem;
  বৃক্ষ type = groktypename (type_name, &tem, রিক্ত);
  যদি (alignment)
    type = build_aligned_type (type, বৃক্ষ_to_uhwi (alignment));
  ঘূৰাই type;
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

স্থির সংরচনা c_ৰাশিমালা
c_parser_gimple_postfix_expression (gimple_parser &parser, বৃক্ষ ret_type)
{
  location_t loc = c_parser_peek_token (parser)->location;
  source_range tok_range = c_parser_peek_token (parser)->get_range ();
  সংরচনা c_ৰাশিমালা ৰাশিমালা;
  ৰাশিমালা.set_error ();
  ৱিকল্প (c_parser_peek_token (parser)->type)
    {
    পক্ষ CPP_সংখ্যা:
      ৰাশিমালা.মান = c_parser_peek_token (parser)->মান;
      set_c_ৰাশিমালা_source_range (&ৰাশিমালা, tok_range);
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      ভঙ্গ;
    পক্ষ CPP_CHAR:
    পক্ষ CPP_CHAR16:
    পক্ষ CPP_CHAR32:
    পক্ষ CPP_UTF8CHAR:
    পক্ষ CPP_WCHAR:
      ৰাশিমালা.মান = c_parser_peek_token (parser)->মান;
      set_c_ৰাশিমালা_source_range (&ৰাশিমালা, tok_range);
      c_parser_consume_token (parser);
      ভঙ্গ;
    পক্ষ CPP_STRING:
    পক্ষ CPP_STRING16:
    পক্ষ CPP_STRING32:
    পক্ষ CPP_WSTRING:
    পক্ষ CPP_UTF8STRING:
      ৰাশিমালা = c_parser_string_literal (parser, মিছা, সঁচা);
      ভঙ্গ;
    পক্ষ CPP_DOT:
      ৰাশিমালা = c_parser_gimple_call_internal (parser);
      ভঙ্গ;
    পক্ষ CPP_NAME:
      যদি (c_parser_peek_token (parser)->id_kind == C_ID_ID)
	{
	  বৃক্ষ id = c_parser_peek_token (parser)->মান;
	  যদি (strcmp (IDENTIFIER_POINTER (id), "__MEM") == 0)
	    {
	      /* __MEM '<' type-name [ ',' number ] '>'
	               '(' [ '(' type-name ')' ] unary-expression
			   [ '+' number ]
			   [ ',' number ]
			   [ ',' number ':' number ] ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      বৃক্ষ type = c_parser_gimple_typespec (parser);
	      সংরচনা c_ৰাশিমালা ptr, alias_off, step, index, index2;
	      ptr.মান = error_mark_গ্ৰন্থি;
	      alias_off.মান = NULL_বৃক্ষ;
	      step.মান = NULL_বৃক্ষ;
	      index.মান = NULL_বৃক্ষ;
	      index2.মান = NULL_বৃক্ষ;
	      unsigned short clique = 0;
	      unsigned short base = 0;
	      তার্কিক reverse_order = মিছা;
	      সংরচনা c_ৰাশিমালা ro;
	      যদি (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  বৃক্ষ alias_type = NULL_বৃক্ষ;
		  /* Optional alias-type cast.  */
		  যদি (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
		    {
		      c_parser_consume_token (parser);
		      সংরচনা c_type_name *alias_type_name
			= c_parser_type_name (parser);
		      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
						 "expected %<)%>");
		      যদি (alias_type_name)
			{
			  বৃক্ষ tem;
			  alias_type = groktypename (alias_type_name,
						     &tem, রিক্ত);
			}
		    }
		  ptr = c_parser_gimple_unary_expression (parser);
		  যদি (ptr.মান == error_mark_গ্ৰন্থি
		      || ! POINTER_TYPE_P (বৃক্ষ_TYPE (ptr.মান)))
		    {
		      যদি (ptr.মান != error_mark_গ্ৰন্থি)
			error_at (ptr.get_start (),
				  "invalid type of %<__MEM%> operand");
		      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
						 "expected %<)%>");
		      ঘূৰাই ৰাশিমালা;
		    }
		  যদি (! alias_type)
		    alias_type = বৃক্ষ_TYPE (ptr.মান);
		  /* Optional constant offset.  */
		  যদি (c_parser_next_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      alias_off = c_parser_gimple_postfix_expression (parser);
		    }
		  যদি (c_parser_next_token_is (parser, CPP_MULT))
		    {
		      std::swap (index, alias_off);
		      c_parser_consume_token (parser);
		      step = c_parser_gimple_postfix_expression (parser);
		    }
		  অন্যথা যদি (c_parser_next_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      index = c_parser_gimple_postfix_expression (parser);
		      যদি (c_parser_next_token_is (parser, CPP_MULT))
			{
			  c_parser_consume_token (parser);
			  step = c_parser_gimple_postfix_expression (parser);
			}
		      অন্যথা
			std::swap (index, index2);
		    }
		  অন্যথা যদি (alias_off.মান
			   && বৃক্ষ_CODE (alias_off.মান) != INTEGER_CST)
		    std::swap (alias_off, index2);
		  যদি (c_parser_next_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      index2 = c_parser_gimple_postfix_expression (parser);
		    }
		  যদি (alias_off.মান)
		    {
		      যদি (বৃক্ষ_CODE (alias_off.মান) != INTEGER_CST)
			error_at (alias_off.get_start (),
				  "expected constant offset for %<__MEM%> "
				  "operand");
		      alias_off.মান = fold_convert (alias_type,
						      alias_off.মান);
		    }
		  অন্যথা
		    alias_off.মান = build_int_cst (alias_type, 0);
		  যদি (step.মান)
		    {
		      যদি (বৃক্ষ_CODE (step.মান) != INTEGER_CST)
			error_at (step.get_start (),
				  "expected constant step for %<__MEM%> "
				  "operand");
		    }
		  যদি (c_parser_next_token_is (parser, CPP_COMMA))
		    {
		      সংরচনা c_ৰাশিমালা cl, ba;
		      তার্কিক has_clb = সঁচা;
		      c_parser_consume_token (parser);
		      cl = c_parser_gimple_postfix_expression (parser);
		      যদি (!c_parser_next_token_is (parser, CPP_COLON))
			{
			  ro = cl;
			  unsigned HOST_WIDE_INT tmp = 0;
			  যদি (!বৃক্ষ_fits_uhwi_p (ro.মান)
			      || (tmp = বৃক্ষ_to_uhwi (ro.মান)) > 1)
			    error_at (ro.get_start (),
				      "invalid reverse order value");
			  reverse_order = tmp;
			  has_clb = মিছা;
			  যদি (c_parser_next_token_is (parser, CPP_COMMA))
			    {
			      c_parser_consume_token (parser);
			      cl = c_parser_gimple_postfix_expression (parser);
		              has_clb = সঁচা;
			    }
			}
		      যদি (has_clb
			  && c_parser_require (parser,
					       CPP_COLON, "expected %<:%>"))
			{
			  ba = c_parser_gimple_postfix_expression (parser);
			  যদি (!বৃক্ষ_fits_uhwi_p (cl.মান)
			      || !বৃক্ষ_fits_uhwi_p (ba.মান)
			      || compare_বৃক্ষ_int (cl.মান,
						   (clique = বৃক্ষ_to_uhwi
								(cl.মান)))
			      || compare_বৃক্ষ_int (ba.মান,
						   (base = বৃক্ষ_to_uhwi
								 (ba.মান))))
			    error_at (cl.get_start (),
				      "invalid clique/base pair");
			}
		    }
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      যদি (! type || c_parser_error (parser))
		{
		  c_parser_set_error (parser, মিছা);
		  ঘূৰাই ৰাশিমালা;
		}
	      যদি (index.মান || step.মান || index2.মান)
		ৰাশিমালা.মান = build5_loc (loc, TARGET_MEM_REF,
					 type, ptr.মান, alias_off.মান,
					 index.মান, step.মান, index2.মান);
	      অন্যথা
		ৰাশিমালা.মান = build2_loc (loc, MEM_REF,
					 type, ptr.মান, alias_off.মান);
	      যদি (clique != 0)
		{
		  cfun->last_clique = MAX (cfun->last_clique, clique);
		  MR_DEPENDENCE_CLIQUE (ৰাশিমালা.মান) = clique;
		  MR_DEPENDENCE_BASE (ৰাশিমালা.মান) = base;
		}
	      যদি (reverse_order)
		{
		  যদি (বৃক্ষ_CODE (ৰাশিমালা.মান) == MEM_REF)
		    REF_REVERSE_STORAGE_ORDER (ৰাশিমালা.মান) = reverse_order;
		  অন্যথা
		    error_at (ro.get_start (),
			      "target mem ref cannot have reverse order");
		}
	      ভঙ্গ;
	    }
	  অন্যথা যদি (strcmp (IDENTIFIER_POINTER (id), "__VIEW_CONVERT") == 0)
	    {
	      /* __VIEW_CONVERT '<' type-name [ ',' number ] '>'
	                        '(' postfix-expression ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      বৃক্ষ type = c_parser_gimple_typespec (parser);
	      যদি (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_ৰাশিমালা op = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  যদি (type && op.মান != error_mark_গ্ৰন্থি)
		    ৰাশিমালা.মান = build1_loc (loc, VIEW_CONVERT_ৰাশিমালা,
					     type, op.মান);
		}
	      ভঙ্গ;
	    }
	  অন্যথা যদি (strcmp (IDENTIFIER_POINTER (id), "__BIT_FIELD_REF") == 0)
	    {
	      /* __BIT_FIELD_REF '<' type-name [ ',' number ] '>'
	                        '(' postfix-expression, integer, integer ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      বৃক্ষ type = c_parser_gimple_typespec (parser);
	      যদি (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_ৰাশিমালা op0 = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_ৰাশিমালা op1 = c_parser_gimple_postfix_expression (parser);
		  যদি (বৃক্ষ_CODE (op1.মান) != INTEGER_CST
		      || !int_fits_type_p (op1.মান, bitsizetype))
		    c_parser_error (parser, "expected constant size");
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_ৰাশিমালা op2 = c_parser_gimple_postfix_expression (parser);
		  যদি (বৃক্ষ_CODE (op2.মান) != INTEGER_CST
		      || !int_fits_type_p (op2.মান, bitsizetype))
		    c_parser_error (parser, "expected constant offset");
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  যদি (type
		      && op0.মান != error_mark_গ্ৰন্থি
		      && বৃক্ষ_CODE (op1.মান) == INTEGER_CST
		      && বৃক্ষ_CODE (op2.মান) == INTEGER_CST)
		    ৰাশিমালা.মান = build3_loc (loc, BIT_FIELD_REF, type,
					     op0.মান,
					     fold_convert (bitsizetype,
							   op1.মান),
					     fold_convert (bitsizetype,
							   op2.মান));
		}
	      ভঙ্গ;
	    }
	  অন্যথা যদি (strcmp (IDENTIFIER_POINTER (id), "__CLOBBER") == 0)
	    {
	      /* __CLOBBER [ '(' bob | eob | bos | eos ')' ]  */
	      clobber_kind kind = CLOBBER_UNDEF;
	      c_parser_consume_token (parser);
	      যদি (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
		{
		  c_parser_consume_token (parser);
		  auto tok = c_parser_peek_token (parser);
		  যদি (c_parser_require (parser, CPP_NAME,
					"expected clobber kind"))
		    {
		      ধ্রুৱ ৱর্ণ *kind_str = IDENTIFIER_POINTER (tok->মান);
		      যদি (strcmp (kind_str, "bos") == 0)
			kind = CLOBBER_STORAGE_BEGIN;
		      অন্যথা যদি (strcmp (kind_str, "bob") == 0)
			kind = CLOBBER_OBJECT_BEGIN;
		      অন্যথা যদি (strcmp (kind_str, "eob") == 0)
			kind = CLOBBER_OBJECT_END;
		      অন্যথা যদি (strcmp (kind_str, "eos") == 0)
			kind = CLOBBER_STORAGE_END;
		      অন্যথা
			c_parser_error (parser, "expected one of %<bos%>, "
					"%<eos%>, %<bob>, %<eob%>");
		    }
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      /* We infer the (redundant) type from the LHS.  */
	      ৰাশিমালা.মান = build_clobber (ret_type, kind);
	      ভঙ্গ;
	    }
	  অন্যথা যদি (strcmp (IDENTIFIER_POINTER (id), "_Literal") == 0)
	    {
	      /* _Literal '(' type-name ')' ( [ '-' ] constant | constructor ) */
	      c_parser_consume_token (parser);
	      বৃক্ষ type = NULL_বৃক্ষ;
	      যদি (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  সংরচনা c_type_name *type_name = c_parser_type_name (parser);
		  বৃক্ষ tem;
		  যদি (type_name)
		    type = groktypename (type_name, &tem, রিক্ত);
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      যদি (! type)
		{
		  c_parser_error (parser, "invalid _Literal");
		  ঘূৰাই ৰাশিমালা;
		}
	      যদি (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
		{
		  c_parser_consume_token (parser);
		  যদি (!AGGREGATE_TYPE_P (type)
		      && !VECTOR_TYPE_P (type))
		    {
		      c_parser_error (parser, "invalid type for _Literal with "
				      "constructor");
		      c_parser_skip_until_found (parser, CPP_CLOSE_BRACE,
						 "expected %<}%>");
		      ঘূৰাই ৰাশিমালা;
		    }
		  vec<constructor_elt, va_gc> *v = রিক্ত;
		  তার্কিক constant_p = সঁচা;
		  যদি (VECTOR_TYPE_P (type)
		      && !c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
		    {
		      vec_alloc (v, TYPE_VECTOR_SUBPARTS (type).to_constant ());
		      কৰা
			{
			  বৃক্ষ val
			    = c_parser_gimple_postfix_expression (parser).মান;
			  যদি (! val
			      || val == error_mark_গ্ৰন্থি
			      || (! CONSTANT_CLASS_P (val)
				  && ! SSA_VAR_P (val)))
			    {
			      c_parser_error (parser, "invalid _Literal");
			      ঘূৰাই ৰাশিমালা;
			    }
			  CONSTRUCTOR_APPEND_ELT (v, NULL_বৃক্ষ, val);
			  যদি (! CONSTANT_CLASS_P (val))
			    constant_p = মিছা;
			  যদি (c_parser_next_token_is (parser, CPP_COMMA))
			    c_parser_consume_token (parser);
			  অন্যথা
			    ভঙ্গ;
			}
		      যেতিয়ালৈ (1);
		    }
		  যদি (c_parser_require (parser, CPP_CLOSE_BRACE,
					"expected %<}%>"))
		    {
		      যদি (v && constant_p)
			ৰাশিমালা.মান = build_vector_from_ctor (type, v);
		      অন্যথা
			ৰাশিমালা.মান = build_constructor (type, v);
		    }
		  অন্যথা
		    {
		      c_parser_skip_until_found (parser, CPP_CLOSE_BRACE,
						 "expected %<}%>");
		      ঘূৰাই ৰাশিমালা;
		    }
		}
	      অন্যথা
		{
		  তার্কিক neg_p, addr_p;
		  যদি ((neg_p = c_parser_next_token_is (parser, CPP_MINUS)))
		    c_parser_consume_token (parser);
		  যদি ((addr_p = c_parser_next_token_is (parser, CPP_AND)))
		    c_parser_consume_token (parser);
		  বৃক্ষ val = c_parser_gimple_postfix_expression (parser).মান;
		  যদি (! val
		      || val == error_mark_গ্ৰন্থি
		      || (!CONSTANT_CLASS_P (val) && !addr_p))
		    {
		      c_parser_error (parser, "invalid _Literal");
		      ঘূৰাই ৰাশিমালা;
		    }
		  যদি (addr_p)
		    {
		      val = build1 (ADDR_ৰাশিমালা, type, val);
		      যদি (!is_gimple_invariant_address (val))
			{
			  c_parser_error (parser, "invalid _Literal");
			  ঘূৰাই ৰাশিমালা;
			}
		    }
		  যদি (neg_p)
		    {
		      val = const_unop (NEGATE_ৰাশিমালা, বৃক্ষ_TYPE (val), val);
		      যদি (! val)
			{
			  c_parser_error (parser, "invalid _Literal");
			  ঘূৰাই ৰাশিমালা;
			}
		    }
		  ৰাশিমালা.মান = fold_convert (type, val);
		}
	      ঘূৰাই ৰাশিমালা;
	    }

	  /* SSA name.  */
	  unsigned version, ver_offset;
	  যদি (! lookup_name (id)
	      && c_parser_parse_ssa_name_id (id, &version, &ver_offset))
	    {
	      c_parser_consume_token (parser);
	      ৰাশিমালা.মান = c_parser_parse_ssa_name (parser, id, NULL_বৃক্ষ,
						    version, ver_offset);
	      যদি (ৰাশিমালা.মান == error_mark_গ্ৰন্থি)
		ঘূৰাই ৰাশিমালা;
	      set_c_ৰাশিমালা_source_range (&ৰাশিমালা, tok_range);
	      /* For default definition SSA names.  */
	      যদি (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
		  && c_parser_peek_2nd_token (parser)->type == CPP_NAME
		  && strcmp ("D",
			     IDENTIFIER_POINTER
			       (c_parser_peek_2nd_token (parser)->মান)) == 0
		  && c_parser_peek_nth_token (parser, 3)->type == CPP_CLOSE_PAREN)
		{
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		  যদি (! SSA_NAME_IS_DEFAULT_DEF (ৰাশিমালা.মান))
		    {
		      যদি (!SSA_NAME_VAR (ৰাশিমালা.মান))
			{
			  error_at (loc, "anonymous SSA name cannot have"
				    " default definition");
			  ৰাশিমালা.মান = error_mark_গ্ৰন্থি;
			  ঘূৰাই ৰাশিমালা;
			}
		      set_ssa_default_def (cfun, SSA_NAME_VAR (ৰাশিমালা.মান),
					   ৰাশিমালা.মান);
		      SSA_NAME_DEF_STMT (ৰাশিমালা.মান) = gimple_build_nop ();
		    }
		}
	    }
	  অন্যথা
	    {
	      c_parser_consume_token (parser);
	      ৰাশিমালা.মান
		= build_external_ref (loc, id,
				      (c_parser_peek_token (parser)->type
				       == CPP_OPEN_PAREN), &ৰাশিমালা.original_type);
	      set_c_ৰাশিমালা_source_range (&ৰাশিমালা, tok_range);
	    }
	  ভঙ্গ;
	}
      /* Fallthru.  */
    স্ৱভাৱ:
      c_parser_error (parser, "expected expression");
      ৰাশিমালা.set_error ();
      ভঙ্গ;
    }
  যদি (ৰাশিমালা.মান == error_mark_গ্ৰন্থি)
    ঘূৰাই ৰাশিমালা;
  ঘূৰাই c_parser_gimple_postfix_expression_after_primary
    (parser, ৰাশিমালা_LOC_OR_LOC (ৰাশিমালা.মান, loc), ৰাশিমালা);
}

/* Parse a gimple postfix expression after the initial primary or compound
   literal.  */

স্থির সংরচনা c_ৰাশিমালা
c_parser_gimple_postfix_expression_after_primary (gimple_parser &parser,
						  location_t ৰাশিমালা_loc,
						  সংরচনা c_ৰাশিমালা ৰাশিমালা)
{
  location_t start;
  location_t finish;
  বৃক্ষ ident;
  location_t comp_loc;

  যেতিয়ালৈ (সঁচা)
    {
      location_t op_loc = c_parser_peek_token (parser)->location;
      ৱিকল্প (c_parser_peek_token (parser)->type)
	{
	পক্ষ CPP_OPEN_SQUARE:
	  {
	    c_parser_consume_token (parser);
	    বৃক্ষ idx = c_parser_gimple_unary_expression (parser).মান;

	    যদি (! c_parser_require (parser, CPP_CLOSE_SQUARE, "expected %<]%>"))
	      {
		c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE, রিক্ত);
		ভঙ্গ;
	      }

	    start = ৰাশিমালা.get_start ();
	    finish = c_parser_tokens_buf (parser, 0)->location;
	    ৰাশিমালা.মান = build_array_ref (op_loc, ৰাশিমালা.মান, idx);
	    set_c_ৰাশিমালা_source_range (&ৰাশিমালা, start, finish);
	    ৰাশিমালা.m_decimal = 0;

	    ৰাশিমালা.original_code = ERROR_MARK;
	    ৰাশিমালা.original_type = রিক্ত;
	    ভঙ্গ;
	  }
	পক্ষ CPP_OPEN_PAREN:
	  {
	    /* Function call.  */
	    c_parser_consume_token (parser);
	    auto_vec<বৃক্ষ> exprlist;
	    যদি (! c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	      c_parser_gimple_ৰাশিমালা_list (parser, &exprlist);
	    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    যদি (!FUNC_OR_METHOD_TYPE_P (বৃক্ষ_TYPE (ৰাশিমালা.মান)))
	      {
		c_parser_error (parser, "invalid call to non-function");
		ৰাশিমালা.set_error ();
		ভঙ্গ;
	      }
	    ৰাশিমালা.মান = build_call_array_loc
		(ৰাশিমালা_loc, বৃক্ষ_TYPE (বৃক্ষ_TYPE (ৰাশিমালা.মান)),
		 ৰাশিমালা.মান, exprlist.length (), exprlist.address ());
	    ৰাশিমালা.m_decimal = 0;
	    ৰাশিমালা.original_code = ERROR_MARK;
	    ৰাশিমালা.original_type = রিক্ত;
	    ভঙ্গ;
	  }
	পক্ষ CPP_DOT:
	  {
	    /* Structure element reference.  */
	    c_parser_consume_token (parser);
	    যদি (c_parser_next_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		ident = comp_tok->মান;
		comp_loc = comp_tok->location;
	      }
	    অন্যথা
	      {
		c_parser_error (parser, "expected identifier");
		ৰাশিমালা.set_error ();
		ৰাশিমালা.original_code = ERROR_MARK;
		ৰাশিমালা.original_type = রিক্ত;
		ঘূৰাই ৰাশিমালা;
	      }
	    start = ৰাশিমালা.get_start ();
	    finish = c_parser_peek_token (parser)->get_finish ();
	    c_parser_consume_token (parser);
	    ৰাশিমালা.মান = build_component_ref (op_loc, ৰাশিমালা.মান, ident,
					      comp_loc, UNKNOWN_LOCATION);
	    set_c_ৰাশিমালা_source_range (&ৰাশিমালা, start, finish);
	    ৰাশিমালা.m_decimal = 0;
	    ৰাশিমালা.original_code = ERROR_MARK;
	    যদি (বৃক্ষ_CODE (ৰাশিমালা.মান) != COMPONENT_REF)
	      ৰাশিমালা.original_type = রিক্ত;
	    অন্যথা
	      {
		/* Remember the original type of a bitfield.  */
		বৃক্ষ field = বৃক্ষ_OPERAND (ৰাশিমালা.মান, 1);
		যদি (বৃক্ষ_CODE (field) != FIELD_DECL)
		  ৰাশিমালা.original_type = রিক্ত;
		অন্যথা
		  ৰাশিমালা.original_type = DECL_BIT_FIELD_TYPE (field);
	      }
	    ভঙ্গ;
	  }
	পক্ষ CPP_DEREF:
	  {
	    /* Structure element reference.  */
	    যদি (!POINTER_TYPE_P (বৃক্ষ_TYPE (ৰাশিমালা.মান)))
	      {
		c_parser_error (parser, "dereference of non-pointer");
		ৰাশিমালা.set_error ();
		ৰাশিমালা.original_code = ERROR_MARK;
		ৰাশিমালা.original_type = রিক্ত;
		ঘূৰাই ৰাশিমালা;
	      }
	    c_parser_consume_token (parser);
	    যদি (c_parser_next_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		ident = comp_tok->মান;
		comp_loc = comp_tok->location;
	      }
	    অন্যথা
	      {
		c_parser_error (parser, "expected identifier");
		ৰাশিমালা.set_error ();
		ৰাশিমালা.original_code = ERROR_MARK;
		ৰাশিমালা.original_type = রিক্ত;
		ঘূৰাই ৰাশিমালা;
	      }
	    start = ৰাশিমালা.get_start ();
	    finish = c_parser_peek_token (parser)->get_finish ();
	    c_parser_consume_token (parser);
	    ৰাশিমালা.মান = build_component_ref (op_loc,
					      build_simple_mem_ref_loc
					        (op_loc, ৰাশিমালা.মান),
					      ident, comp_loc,
					      ৰাশিমালা.get_location ());
	    set_c_ৰাশিমালা_source_range (&ৰাশিমালা, start, finish);
	    ৰাশিমালা.m_decimal = 0;
	    ৰাশিমালা.original_code = ERROR_MARK;
	    যদি (বৃক্ষ_CODE (ৰাশিমালা.মান) != COMPONENT_REF)
	      ৰাশিমালা.original_type = রিক্ত;
	    অন্যথা
	      {
		/* Remember the original type of a bitfield.  */
		বৃক্ষ field = বৃক্ষ_OPERAND (ৰাশিমালা.মান, 1);
		যদি (বৃক্ষ_CODE (field) != FIELD_DECL)
		  ৰাশিমালা.original_type = রিক্ত;
		অন্যথা
		  ৰাশিমালা.original_type = DECL_BIT_FIELD_TYPE (field);
	      }
	    ভঙ্গ;
	  }
	স্ৱভাৱ:
	  ঘূৰাই ৰাশিমালা;
	}
    }
}

/* Parse expression list.

   gimple-expr-list:
     gimple-unary-expression
     gimple-expr-list , gimple-unary-expression

 */

স্থির শূন্য
c_parser_gimple_ৰাশিমালা_list (gimple_parser &parser, vec<বৃক্ষ> *ret)
{
  সংরচনা c_ৰাশিমালা ৰাশিমালা;

  ৰাশিমালা = c_parser_gimple_unary_expression (parser);
  ret->safe_ঠেলো (ৰাশিমালা.মান);
  যেতিয়ালৈ (c_parser_next_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      ৰাশিমালা = c_parser_gimple_unary_expression (parser);
      ret->safe_ঠেলো (ৰাশিমালা.মান);
    }
}

/* Parse gimple label.

   gimple-label:
     identifier :
     case constant-expression :
     default :

*/

স্থির শূন্য
c_parser_gimple_label (gimple_parser &parser, gimple_seq *seq)
{
  বৃক্ষ name = c_parser_peek_token (parser)->মান;
  location_t loc1 = c_parser_peek_token (parser)->location;
  gcc_assert (c_parser_next_token_is (parser, CPP_NAME));
  c_parser_consume_token (parser);
  gcc_assert (c_parser_next_token_is (parser, CPP_COLON));
  c_parser_consume_token (parser);
  বৃক্ষ label = define_label (loc1, name);
  যদি (label)
    gimple_seq_add_stmt_without_update (seq, gimple_build_label (label));
  ঘূৰাই;
}

/* Parse gimple/RTL pass list.

   gimple-or-rtl-pass-list:
     startwith("pass-name")[,{cfg,ssa}]
 */

শূন্য
c_parser_gimple_or_rtl_pass_list (c_parser *parser, c_declspecs *specs)
{
  ৱর্ণ *pass = রিক্ত;

  /* Accept __GIMPLE/__RTL.  */
  যদি (c_parser_next_token_is_not (parser, CPP_OPEN_PAREN))
    ঘূৰাই;
  c_parser_consume_token (parser);

  specs->entry_bb_গুনতি = profile_গুনতি::uninitialized ();
  যেতিয়ালৈ (c_parser_next_token_is (parser, CPP_NAME))
    {
      profile_quality quality;
      ধ্রুৱ ৱর্ণ *op = IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান);
      c_parser_consume_token (parser);
      যদি (! strcmp (op, "startwith"))
	{
	  যদি (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    ঘূৰাই;
	  যদি (c_parser_next_token_is_not (parser, CPP_STRING))
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"expected pass name");
	      ঘূৰাই;
	    }
	  pass = xstrdup (বৃক্ষ_STRING_POINTER
			  (c_parser_string_literal (parser, মিছা,
						    মিছা).মান));
	  যদি (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<(%>"))
	    ঘূৰাই;
	}
      অন্যথা যদি (parse_profile_quality (op, &quality))
	{
	  বৃক্ষ q;
	  যদি (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    ঘূৰাই;

	  যদি (!c_parser_next_token_is (parser, CPP_সংখ্যা)
	      || (বৃক্ষ_CODE (q = c_parser_peek_token (parser)->মান)
		  != INTEGER_CST))
	    {
	      c_parser_error (parser, "expected count value");
	      ঘূৰাই;
	    }

	  specs->entry_bb_গুনতি
	    = profile_গুনতি::from_gcov_type (বৃক্ষ_INT_CST_নিচেৰ (q), quality);
	  c_parser_consume_token (parser);
	  যদি (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    ঘূৰাই;
	}
      অন্যথা যদি (specs->declspec_il != cdil_gimple)
	/* Allow only one IL specifier and none on RTL.  */
	;
      অন্যথা যদি (! strcmp (op, "cfg"))
	specs->declspec_il = cdil_gimple_cfg;
      অন্যথা যদি (! strcmp (op, "ssa"))
	specs->declspec_il = cdil_gimple_ssa;
      অন্যথা
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "invalid operation");
	  ঘূৰাই;
	}
     যদি (c_parser_next_token_is (parser, CPP_COMMA))
       c_parser_consume_token (parser);
    }

  যদি (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    ঘূৰাই;

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

স্থির শূন্য
c_parser_gimple_declaration (gimple_parser &parser)
{
  সংরচনা c_declarator *declarator;
  সংরচনা c_declspecs *specs = build_null_declspecs ();
  c_parser_declspecs (parser, specs, সঁচা, সঁচা, সঁচা,
		      সঁচা, সঁচা, সঁচা, সঁচা, cla_nonabstract_decl);
  finish_declspecs (specs);

  /* Provide better error recovery.  Note that a type name here is usually
     better diagnosed as a redeclaration.  */
  যদি (c_parser_next_token_starts_declspecs (parser)
      && ! c_parser_next_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<;%>");
      c_parser_set_error (parser, মিছা);
      ঘূৰাই;
    }

  তার্কিক dummy = মিছা;
  declarator = c_parser_declarator (parser,
				    specs->typespec_kind != ctsk_none,
				    C_DTR_NORMAL, &dummy);

  যদি (!c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_error (parser, "expected %<;%>");
      ঘূৰাই;
    }
  যদি (declarator)
    {
      /* Handle SSA name decls specially, they do not go into the identifier
         table but we simply build the SSA name for later lookup.  */
      unsigned version, ver_offset;
      /* Handle SSA pointer declarations in a very simplistic ways, we
	 probably would like to call grokdeclarator in a special mode to
	 just build the type of the decl - start_decl already pushes
	 the identifier to the bindings for lookup, something we do not
	 want.  */
      সংরচনা c_declarator *id_declarator = declarator;
      যেতিয়ালৈ (id_declarator->kind == cdk_pointer)
	id_declarator = id_declarator->declarator;
      যদি (id_declarator->kind == cdk_id
	  && (declarator->kind == cdk_pointer
	      || is_gimple_reg_type (specs->type))
	  && c_parser_parse_ssa_name_id (id_declarator->u.id.id,
					 &version, &ver_offset)
	  /* The following restricts it to unnamed anonymous SSA names
	     which fails parsing of named ones in dumps (we could
	     decide to not dump their name for -gimple).  */
	  && ver_offset == 0)
	{
	  সংরচনা c_declarator *p = declarator;
	  বৃক্ষ type = specs->type;
	  যেতিয়ালৈ (p->kind == cdk_pointer)
	    {
	      type = build_pointer_type (type);
	      p = p->declarator;
	    }
	  c_parser_parse_ssa_name (parser, id_declarator->u.id.id, type,
				   version, ver_offset);
	}
      অন্যথা
	{
	  বৃক্ষ postfix_attrs = NULL_বৃক্ষ;
	  বৃক্ষ all_prefix_attrs = specs->attrs;
	  specs->attrs = রিক্ত;
	  বৃক্ষ decl = start_decl (declarator, specs, মিছা,
				  chainon (postfix_attrs, all_prefix_attrs));
	  যদি (decl)
	    finish_decl (decl, UNKNOWN_LOCATION, NULL_বৃক্ষ, NULL_বৃক্ষ,
			 NULL_বৃক্ষ);
	}
    }
}

/* Parse gimple goto statement.  */

স্থির শূন্য
c_parser_gimple_goto_stmt (gimple_parser &parser,
			   location_t loc, বৃক্ষ label, gimple_seq *seq)
{
  যদি (cfun->curr_properties & PROP_cfg)
    {
      পূর্ণাঙ্ক dest_index;
      profile_probability prob;
      যদি (c_parser_gimple_parse_bb_spec_edge_probability (label, parser,
							  &dest_index, &prob))
	{
	  parser.ঠেলো_edge (parser.current_bb->index, dest_index,
			    EDGE_FALLTHRU, prob);
	  ঘূৰাই;
	}
    }
  বৃক্ষ decl = lookup_label_for_goto (loc, label);
  gimple_seq_add_stmt_without_update (seq, gimple_build_goto (decl));
}

/* Parse a parenthesized condition.
   gimple-condition:
     ( gimple-binary-expression )    */

স্থির বৃক্ষ
c_parser_gimple_paren_condition (gimple_parser &parser)
{
  যদি (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    ঘূৰাই error_mark_গ্ৰন্থি;
  বৃক্ষ cond
    = c_parser_gimple_দ্বিমিক_expression (parser, boolean_type_গ্ৰন্থি).মান;
  যদি (cond != error_mark_গ্ৰন্থি
      && ! COMPARISON_CLASS_P (cond)
      && ! CONSTANT_CLASS_P (cond)
      && ! SSA_VAR_P (cond))
    {
      c_parser_error (parser, "comparison required");
      cond = error_mark_গ্ৰন্থি;
    }
  যদি (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    ঘূৰাই error_mark_গ্ৰন্থি;
  ঘূৰাই cond;
}

/* Parse gimple try statement.

   try-statement:
     try { ... } finally { ... }
     try { ... } finally { ... } else { ... }

   This could support try/catch as well, but it's not implemented yet.
 */

স্থির শূন্য
c_parser_gimple_try_stmt (gimple_parser &parser, gimple_seq *seq)
{
  gimple_seq tryseq = রিক্ত;
  c_parser_consume_token (parser);
  c_parser_gimple_compound_statement (parser, &tryseq);

  যদি ((c_parser_next_token_is (parser, CPP_KEYWORD)
       && c_parser_peek_token (parser)->keyword == RID_AT_FINALLY)
      || (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_token (parser)->id_kind == C_ID_ID
	  && strcmp (IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান),
		     "finally") == 0))
    {
      gimple_seq finseq = রিক্ত;
      c_parser_consume_token (parser);
      c_parser_gimple_compound_statement (parser, &finseq);

      যদি (c_parser_next_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_ELSE)
	{
	  gimple_seq elsseq = রিক্ত;
	  c_parser_consume_token (parser);
	  c_parser_gimple_compound_statement (parser, &elsseq);

	  geh_else *stmt = gimple_build_eh_else (finseq, elsseq);
	  finseq = রিক্ত;
	  gimple_seq_add_stmt_without_update (&finseq, stmt);
	}

      gtry *stmt = gimple_build_try (tryseq, finseq, GIMPLE_TRY_FINALLY);
      gimple_seq_add_stmt_without_update (seq, stmt);
    }
  অন্যথা যদি (c_parser_next_token_is (parser, CPP_KEYWORD)
      && c_parser_peek_token (parser)->keyword == RID_AT_CATCH)
    c_parser_error (parser, "%<catch%> is not supported");
  অন্যথা
    c_parser_error (parser, "expected %<finally%> or %<catch%>");
}

/* Parse gimple if-else statement.

   if-statement:
     if ( gimple-binary-expression ) gimple-goto-statement
     if ( gimple-binary-expression ) gimple-goto-statement \
					else gimple-goto-statement
 */

স্থির শূন্য
c_parser_gimple_if_stmt (gimple_parser &parser, gimple_seq *seq)
{
  বৃক্ষ t_label = NULL_বৃক্ষ, f_label = NULL_বৃক্ষ, label;
  location_t loc;
  c_parser_consume_token (parser);
  বৃক্ষ cond = c_parser_gimple_paren_condition (parser);

  যদি (c_parser_next_token_is_keyword (parser, RID_GOTO))
    {
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      যদি (! c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected label");
	  ঘূৰাই;
	}
      label = c_parser_peek_token (parser)->মান;
      c_parser_consume_token (parser);
      পূর্ণাঙ্ক dest_index;
      profile_probability prob;
      যদি ((cfun->curr_properties & PROP_cfg)
	  && c_parser_gimple_parse_bb_spec_edge_probability (label, parser,
							     &dest_index, &prob))
	parser.ঠেলো_edge (parser.current_bb->index, dest_index,
			  EDGE_TRUE_মান, prob);
      অন্যথা
	t_label = lookup_label_for_goto (loc, label);
      যদি (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	ঘূৰাই;
    }
  অন্যথা
    {
      c_parser_error (parser, "expected goto expression");
      ঘূৰাই;
    }

  যদি (c_parser_next_token_is_keyword (parser, RID_ELSE))
    c_parser_consume_token (parser);
  অন্যথা
    {
      c_parser_error (parser, "expected else statement");
      ঘূৰাই;
    }

  যদি (c_parser_next_token_is_keyword (parser, RID_GOTO))
    {
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      যদি (! c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected label");
	  ঘূৰাই;
	}
      label = c_parser_peek_token (parser)->মান;
      c_parser_consume_token (parser);
      পূর্ণাঙ্ক dest_index;
      profile_probability prob;
      যদি ((cfun->curr_properties & PROP_cfg)
	  && c_parser_gimple_parse_bb_spec_edge_probability (label, parser,
							     &dest_index, &prob))
	parser.ঠেলো_edge (parser.current_bb->index, dest_index,
			  EDGE_FALSE_মান, prob);
      অন্যথা
	f_label = lookup_label_for_goto (loc, label);
      যদি (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	ঘূৰাই;
    }
  অন্যথা
    {
      c_parser_error (parser, "expected goto expression");
      ঘূৰাই;
    }

  যদি (cond != error_mark_গ্ৰন্থি)
    gimple_seq_add_stmt_without_update (seq, gimple_build_cond_from_বৃক্ষ (cond, t_label,
							   f_label));
}

/* Parse gimple switch-statement.

   gimple-switch-statement:
     switch (gimple-postfix-expression) gimple-case-statement

   gimple-case-statement:
     gimple-case-statement
     gimple-label-statement : gimple-goto-statement
*/

স্থির শূন্য
c_parser_gimple_switch_stmt (gimple_parser &parser, gimple_seq *seq)
{
  c_ৰাশিমালা cond_ৰাশিমালা;
  বৃক্ষ case_label, label;
  auto_vec<বৃক্ষ> labels;
  বৃক্ষ default_label = NULL_বৃক্ষ;
  c_parser_consume_token (parser);

  যদি (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    ঘূৰাই;
  cond_ৰাশিমালা = c_parser_gimple_postfix_expression (parser);
  যদি (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    ঘূৰাই;

  যদি (! c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    ঘূৰাই;

  যেতিয়ালৈ (c_parser_next_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      যদি (c_parser_next_token_is (parser, CPP_EOF))
	{
	  c_parser_error (parser, "expected statement");
	  ঘূৰাই;
	}

      ৱিকল্প (c_parser_peek_token (parser)->keyword)
	{
	পক্ষ RID_CASE:
	  {
	    c_ৰাশিমালা exp1;
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);

	    যদি (c_parser_next_token_is (parser, CPP_NAME)
		|| c_parser_peek_token (parser)->type == CPP_সংখ্যা)
	      exp1 = c_parser_gimple_postfix_expression (parser);
	    অন্যথা
	      {
		c_parser_error (parser, "expected expression");
		ঘূৰাই;
	      }

	    যদি (c_parser_next_token_is (parser, CPP_COLON))
	      {
		c_parser_consume_token (parser);
		যদি (c_parser_next_token_is (parser, CPP_NAME))
		  {
		    label = c_parser_peek_token (parser)->মান;
		    c_parser_consume_token (parser);
		    বৃক্ষ decl = lookup_label_for_goto (loc, label);
		    case_label = build_case_label (exp1.মান, NULL_বৃক্ষ,
						   decl);
		    labels.safe_ঠেলো (case_label);
		    যদি (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      ঘূৰাই;
		  }
		অন্যথা যদি (! c_parser_require (parser, CPP_NAME,
					     "expected label"))
		  ঘূৰাই;
	      }
	    অন্যথা যদি (! c_parser_require (parser, CPP_SEMICOLON,
					 "expected %<:%>"))
	      ঘূৰাই;
	    ভঙ্গ;
	  }
	পক্ষ RID_DEFAULT:
	  {
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);
	    যদি (c_parser_next_token_is (parser, CPP_COLON))
	      {
		c_parser_consume_token (parser);
		যদি (c_parser_next_token_is (parser, CPP_NAME))
		  {
		    label = c_parser_peek_token (parser)->মান;
		    c_parser_consume_token (parser);
		    বৃক্ষ decl = lookup_label_for_goto (loc, label);
		    default_label = build_case_label (NULL_বৃক্ষ, NULL_বৃক্ষ,
						      decl);
		    যদি (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      ঘূৰাই;
		  }
		অন্যথা যদি (! c_parser_require (parser, CPP_NAME,
					     "expected label"))
		  ঘূৰাই;
	      }
	    অন্যথা যদি (! c_parser_require (parser, CPP_SEMICOLON,
					 "expected %<:%>"))
	      ঘূৰাই;
	    ভঙ্গ;
	  }
	স্ৱভাৱ:
	  c_parser_error (parser, "expected case label");
	  ঘূৰাই;
	}

    }
  যদি (! c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>"))
    ঘূৰাই;

  যদি (cond_ৰাশিমালা.মান != error_mark_গ্ৰন্থি)
    {
      gswitch *s = gimple_build_switch (cond_ৰাশিমালা.মান, default_label, labels);
      gimple_seq_add_stmt_without_update (seq, s);
    }
}

/* Parse gimple return statement.  */

স্থির শূন্য
c_parser_gimple_return_stmt (gimple_parser &parser, gimple_seq *seq)
{
  location_t loc = c_parser_peek_token (parser)->location;
  gimple *ret = রিক্ত;
  c_parser_consume_token (parser);
  যদি (c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      c_finish_gimple_return (loc, NULL_বৃক্ষ);
      ret = gimple_build_return (রিক্ত);
      gimple_seq_add_stmt_without_update (seq, ret);
    }
  অন্যথা
    {
      location_t xloc = c_parser_peek_token (parser)->location;
      c_ৰাশিমালা ৰাশিমালা = c_parser_gimple_unary_expression (parser);
      যদি (ৰাশিমালা.মান != error_mark_গ্ৰন্থি)
	{
	  c_finish_gimple_return (xloc, ৰাশিমালা.মান);
	  ret = gimple_build_return (ৰাশিমালা.মান);
	  gimple_seq_add_stmt_without_update (seq, ret);
	}
    }
}

/* Support function for c_parser_gimple_return_stmt.  */

স্থির শূন্য
c_finish_gimple_return (location_t loc, বৃক্ষ retval)
{
  বৃক্ষ valtype = বৃক্ষ_TYPE (বৃক্ষ_TYPE (current_function_decl));

  /* Use the expansion point to handle cases such as returning NULL
     in a function returning void.  */
  location_t xloc = expansion_point_location_if_in_system_header (loc);

  যদি (বৃক্ষ_THIS_VOLATILE (current_function_decl))
    warning_at (xloc, 0,
		"function declared %<noreturn%> has a %<return%> statement");

  যদি (! retval)
    current_function_returns_null = 1;
  অন্যথা যদি (valtype == 0 || VOID_TYPE_P (valtype))
    {
      current_function_returns_null = 1;
      যদি (বৃক্ষ_CODE (বৃক্ষ_TYPE (retval)) != VOID_TYPE)
	{
	  error_at
	    (xloc, "%<return%> with a value, in function returning void");
	  inform (DECL_SOURCE_LOCATION (current_function_decl),
		  "declared here");
	}
    }
  অন্যথা যদি (বৃক্ষ_CODE (valtype) != বৃক্ষ_CODE (বৃক্ষ_TYPE (retval)))
    {
      error_at
	(xloc, "invalid conversion in return statement");
      inform (DECL_SOURCE_LOCATION (current_function_decl),
	      "declared here");
    }
  ঘূৰাই;
}
