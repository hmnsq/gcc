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

#অন্তর্ভাব "config.h"
#অন্তর্ভাব "system.h"
#অন্তর্ভাব "coretypes.h"
#অন্তর্ভাব "target.h"
#অন্তর্ভাব "function.h"
#অন্তর্ভাব "c-tree.h"
#অন্তর্ভাব "timevar.h"
#অন্তর্ভাব "stringpool.h"
#অন্তর্ভাব "cgraph.h"
#অন্তর্ভাব "attribs.h"
#অন্তর্ভাব "stor-layout.h"
#অন্তর্ভাব "varasm.h"
#অন্তর্ভাব "trans-mem.h"
#অন্তর্ভাব "c-family/c-pragma.h"
#অন্তর্ভাব "c-lang.h"
#অন্তর্ভাব "c-family/c-objc.h"
#অন্তর্ভাব "plugin.h"
#অন্তর্ভাব "builtins.h"
#অন্তর্ভাব "gomp-constants.h"
#অন্তর্ভাব "c-family/c-indentation.h"
#অন্তর্ভাব "gimple-expr.h"
#অন্তর্ভাব "context.h"
#অন্তর্ভাব "gcc-rich-location.h"
#অন্তর্ভাব "c-parser.h"
#অন্তর্ভাব "tree-vrp.h"
#অন্তর্ভাব "tree-pass.h"
#অন্তর্ভাব "tree-pretty-print.h"
#অন্তর্ভাব "tree.h"
#অন্তর্ভাব "basic-block.h"
#অন্তর্ভাব "gimple.h"
#অন্তর্ভাব "gimple-pretty-print.h"
#অন্তর্ভাব "tree-ssa.h"
#অন্তর্ভাব "pass_manager.h"
#অন্তর্ভাব "tree-ssanames.h"
#অন্তর্ভাব "gimple-ssa.h"
#অন্তর্ভাব "tree-dfa.h"
#অন্তর্ভাব "internal-fn.h"
#অন্তর্ভাব "cfg.h"
#অন্তর্ভাব "cfghooks.h"
#অন্তর্ভাব "bitmap.h"
#অন্তর্ভাব "cfganal.h"
#অন্তর্ভাব "tree-cfg.h"
#অন্তর্ভাব "gimple-iterator.h"
#অন্তর্ভাব "cfgloop.h"
#অন্তর্ভাব "tree-phinodes.h"
#অন্তর্ভাব "tree-into-ssa.h"


/* GIMPLE parser state.  */

শ্রেণী gimple_parser
{
সর্বজনীন:
  gimple_parser (c_parser *p) : parser (p), edges(), current_bb(ফাঁকা) {}
  /* c_parser is not visible here, use composition and fake inheritance
     via a conversion operator.  */
  operator c_parser *() { ফেরত parser; }
  c_parser *parser;

  /* CFG build state.  */
  শ্রেণী gimple_parser_edge
  {
  সর্বজনীন:
    পূর্ণসংখ্যা src;
    পূর্ণসংখ্যা dest;
    পূর্ণসংখ্যা flags;
    profile_probability probability;
  };
  auto_vec<gimple_parser_edge> edges;
  basic_block current_bb;

  শূন্য ঠেলো_edge (পূর্ণসংখ্যা, পূর্ণসংখ্যা, পূর্ণসংখ্যা, profile_probability);
};

শূন্য
gimple_parser::ঠেলো_edge (পূর্ণসংখ্যা src, পূর্ণসংখ্যা dest, পূর্ণসংখ্যা flags,
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
স্থির যৌক্তিক c_parser_gimple_compound_statement (gimple_parser &, gimple_seq *);
স্থির শূন্য c_parser_gimple_label (gimple_parser &, gimple_seq *);
স্থির শূন্য c_parser_gimple_statement (gimple_parser &, gimple_seq *);
স্থির কাঠামো c_রাশিমালা c_parser_gimple_দ্বিমিক_expression (gimple_parser &, বৃক্ষ);
স্থির কাঠামো c_রাশিমালা c_parser_gimple_unary_expression (gimple_parser &);
স্থির কাঠামো c_রাশিমালা c_parser_gimple_postfix_expression
			(gimple_parser &, বৃক্ষ = error_mark_গ্রন্থি);
স্থির কাঠামো c_রাশিমালা c_parser_gimple_postfix_expression_after_primary
			(gimple_parser &, location_t, কাঠামো c_রাশিমালা);
স্থির শূন্য c_parser_gimple_declaration (gimple_parser &);
স্থির শূন্য c_parser_gimple_goto_stmt (gimple_parser &, location_t,
				       বৃক্ষ, gimple_seq *);
স্থির শূন্য c_parser_gimple_try_stmt (gimple_parser &, gimple_seq *);
স্থির শূন্য c_parser_gimple_if_stmt (gimple_parser &, gimple_seq *);
স্থির শূন্য c_parser_gimple_switch_stmt (gimple_parser &, gimple_seq *);
স্থির শূন্য c_parser_gimple_return_stmt (gimple_parser &, gimple_seq *);
স্থির শূন্য c_finish_gimple_return (location_t, বৃক্ষ);
স্থির বৃক্ষ c_parser_gimple_paren_condition (gimple_parser &);
স্থির শূন্য c_parser_gimple_রাশিমালা_list (gimple_parser &, vec<বৃক্ষ> *);


/* Much like parser_build_unary_op, but avoid applying default conversions.  */

স্থির c_রাশিমালা
gimple_parser_build_unary_op (location_t loc,
			      গণনা বৃক্ষ_code code, কাঠামো c_রাশিমালা arg)
{
  কাঠামো c_রাশিমালা ফলাফল;

  ফলাফল.original_code = code;
  ফলাফল.original_type = ফাঁকা;
  ফলাফল.m_decimal = 0;

  যদি (reject_gcc_builtin (arg.মান))
    {
      ফলাফল.মান = error_mark_গ্রন্থি;
    }
  অন্যথা
    {
      ফলাফল.মান = build_unary_op (loc, code, arg.মান, সত্য);

      যদি (বৃক্ষ_OVERFLOW_P (ফলাফল.মান) && !বৃক্ষ_OVERFLOW_P (arg.মান))
	overflow_warning (loc, ফলাফল.মান, arg.মান);
    }

  /* We are typically called when parsing a prefix token at LOC acting on
     ARG.  Reflect this by updating the source range of the result to
     start at LOC and end at the end of ARG.  */
  set_c_রাশিমালা_source_range (&ফলাফল,
			   loc, arg.get_finish ());

  ফেরত ফলাফল;
}

/* See if VAL is an identifier matching __BB<num> and return <num>
   in *INDEX.  */

স্থির যৌক্তিক
c_parser_gimple_parse_bb_spec (বৃক্ষ val, পূর্ণসংখ্যা *সূচক)
{
  যদি (!startswith (IDENTIFIER_POINTER (val), "__BB"))
    ফেরত মিথ্যা;

  ধ্রুবক অক্ষর *bb = IDENTIFIER_POINTER (val) + 4;
  যদি (! ISDIGIT (*bb))
    ফেরত মিথ্যা;

  অক্ষর *pend;
  errno = 0;
  ধ্রুবক unsigned long সংখ্যা = strtoul (bb, &pend, 10);
  যদি (errno == ERANGE
      || *pend != '\0'
      || সংখ্যা > INT_MAX)
    ফেরত মিথ্যা;

  *সূচক = সংখ্যা;
  ফেরত সত্য;
}

/* See if VAL is an identifier matching __BB<num> and return <num>
   in *INDEX.  Return true if so and parse also FREQUENCY of
   the edge.  */


স্থির যৌক্তিক
c_parser_gimple_parse_bb_spec_edge_probability (বৃক্ষ val,
						gimple_parser &parser,
						পূর্ণসংখ্যা *সূচক,
						profile_probability
						*probability)
{
  যৌক্তিক return_p = c_parser_gimple_parse_bb_spec (val, সূচক);
  যদি (return_p)
    {
      *probability = profile_probability::uninitialized ();
      /* Parse frequency if provided.  */
      যদি (c_parser_পরবর্তী_token_is (parser, CPP_OPEN_PAREN))
	{
	  বৃক্ষ f;
	  c_parser_consume_token (parser);
	  যদি (!c_parser_পরবর্তী_token_is (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected frequency quality");
	      ফেরত মিথ্যা;
	    }

	  profile_quality quality;
	  ধ্রুবক অক্ষর *v
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান);
	  যদি (!parse_profile_quality (v, &quality))
	    {
	      c_parser_error (parser, "unknown profile quality");
	      ফেরত মিথ্যা;
	    }

	  c_parser_consume_token (parser);
	  যদি (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    ফেরত মিথ্যা;

	  যদি (!c_parser_পরবর্তী_token_is (parser, CPP_সংখ্যা)
	      || (বৃক্ষ_CODE (f = c_parser_peek_token (parser)->মান)
		  != INTEGER_CST))
	    {
	      c_parser_error (parser, "expected frequency value");
	      ফেরত মিথ্যা;
	    }

	  unsigned পূর্ণসংখ্যা মান = বৃক্ষ_INT_CST_নিচের (f);
	  *probability = profile_probability (মান, quality);

	  c_parser_consume_token (parser);
	  যদি (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    ফেরত মিথ্যা;

	  যদি (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    ফেরত মিথ্যা;
	}

      ফেরত সত্য;
    }

  ফেরত মিথ্যা;

}

/* Parse the body of a function declaration marked with "__GIMPLE".  */

শূন্য
c_parser_parse_gimple_body (c_parser *cparser, অক্ষর *gimple_pass,
			    গণনা c_declspec_il cdil,
			    profile_গুনতি entry_bb_গুনতি)
{
  gimple_parser parser (cparser);
  gimple_seq seq = ফাঁকা;
  gimple_seq body = ফাঁকা;
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
      set_loops_for_fn (cfun, ggc_cleared_alloc<কাঠামো loops> ());
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
      gimple *ret = gimple_build_return (ফাঁকা);
      gimple_seq_add_stmt_without_update (&seq, ret);
    }

  বৃক্ষ block = বের_করো_scope ();
  stmt = বের_করো_stmt_list (stmt);
  stmt = c_build_bind_রাশিমালা (loc1, block, stmt);

  block = DECL_INITIAL (current_function_decl);
  BLOCK_SUBBLOCKS (block) = NULL_বৃক্ষ;
  BLOCK_CHAIN (block) = NULL_বৃক্ষ;
  বৃক্ষ_ASM_WRITTEN (block) = 1;

  যদি (cdil == cdil_gimple)
    {
      gbind *bind_stmt = gimple_build_bind (BIND_রাশিমালা_VARS (stmt), ফাঁকা,
					    BIND_রাশিমালা_BLOCK (stmt));
      gimple_bind_set_body (bind_stmt, seq);
      gimple_seq_add_stmt_without_update (&body, bind_stmt);
      gimple_set_body (current_function_decl, body);
    }
  অন্যথা
    {
      /* Control-flow and binds are lowered, record local decls.  */
      জন্য (বৃক্ষ var = BIND_রাশিমালা_VARS (stmt); var; var = DECL_CHAIN (var))
	যদি (VAR_P (var)
	    && !DECL_EXTERNAL (var))
	  {
	    add_local_decl (cfun, var);
	    /* When the middle-end re-gimplifies any expression we might
	       run into the assertion that we've seen the decl in a BIND.  */
	    যদি (!বৃক্ষ_STATIC (var))
	      DECL_SEEN_IN_BIND_রাশিমালা_P (var) = 1;
	  }
      /* We have a CFG.  Build the edges.  */
      জন্য (unsigned i = 0; i < parser.edges.দৈর্ঘ্য (); ++i)
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
	      জন্য (unsigned i = 0; i < gimple_switch_অঙ্ক_labels (sw); ++i)
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
	      জন্য (gsi = gsi_start_bb (bb); !gsi_end_p (gsi);)
		{
		  gimple *stmt = gsi_stmt (gsi);
		  যদি (!gimple_call_internal_p (stmt, IFN_PHI))
		    বিরতি;

		  gphi *phi = create_phi_গ্রন্থি (gimple_call_lhs (stmt), bb);
		  জন্য (unsigned i = 0; i < gimple_call_অঙ্ক_args (stmt); i += 2)
		    {
		      পূর্ণসংখ্যা srcidx = বৃক্ষ_INT_CST_নিচের (gimple_call_arg (stmt, i));
		      edge e = find_edge (BASIC_BLOCK_FOR_FN (cfun, srcidx), bb);
		      যদি (!e)
			c_parser_error (parser, "edge not found");
		      অন্যথা
			add_phi_arg (phi, gimple_call_arg (stmt, i + 1), e,
				     UNKNOWN_LOCATION);
		    }
		  gsi_remove (&gsi, সত্য);
		}
	      জন্য (; !gsi_end_p (gsi); gsi_পরবর্তী (&gsi))
		update_stmt (gsi_stmt (gsi));
	    }
	  /* Fill SSA name gaps, putting them on the freelist and diagnose
	     SSA names without definition.  */
	  জন্য (unsigned i = 1; i < অঙ্ক_ssa_names; ++i)
	    যদি (!ssa_name (i))
	      {
		বৃক্ষ name = make_ssa_name_fn (cfun, integer_type_গ্রন্থি, ফাঁকা, i);
		release_ssa_name_fn (cfun, name);
	      }
	    অন্যথা যদি (!SSA_NAME_DEF_STMT (ssa_name (i)))
	      error ("SSA name %qE with version %d has no definition",
		     ssa_name (i), i);
	  /* No explicit virtual operands (yet).  */
	  bitmap_obstack_initialize (ফাঁকা);
	  update_ssa (TODO_update_ssa_only_virtuals);
	  bitmap_obstack_release (ফাঁকা);
	  /* ???  By flushing the freelist after virtual operand SSA rewrite
	     we keep the gaps available for re-use like needed for the
	     PR89595 testcase but then usually virtual operands would have
	     taken most of them.  The fix is obviously to make virtual
	     operands explicit in the SSA IL.  */
	  flush_ssaname_freelist ();
	}
      fix_loop_structure (ফাঁকা);
    }

  যদি (cfun->curr_properties & PROP_cfg)
    {
      ENTRY_BLOCK_PTR_FOR_FN (cfun)->গুনতি = entry_bb_গুনতি;
      gcov_type t = param_gimple_fe_computed_hot_bb_threshold;
      set_hot_bb_threshold (t);
      update_max_bb_গুনতি ();
      cgraph_গ্রন্থি::get_create (cfun->decl);
      cgraph_edge::rebuild_edges ();
    }

  /* Perform IL validation and if any error is found abort compilation
     of this function by zapping its body.  */
  যদি ((cfun->curr_properties & PROP_cfg)
      && verify_gimple_in_cfg (cfun, মিথ্যা, মিথ্যা))
    init_empty_বৃক্ষ_cfg ();
  অন্যথা যদি (!(cfun->curr_properties & PROP_cfg)
	   && verify_gimple_in_seq (gimple_body (current_function_decl), মিথ্যা))
    gimple_set_body (current_function_decl, ফাঁকা);

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

স্থির যৌক্তিক
c_parser_gimple_compound_statement (gimple_parser &parser, gimple_seq *seq)
{
  যৌক্তিক return_p = মিথ্যা;

  যদি (! c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    ফেরত মিথ্যা;

  /* A compound statement starts with optional declarations.  */
  যখন (c_parser_পরবর্তী_tokens_start_declaration (parser))
    {
      c_parser_gimple_declaration (parser);
      যদি (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	ফেরত মিথ্যা;
    }

  যখন (c_parser_পরবর্তী_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      যদি (c_parser_error (parser))
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_BRACE, ফাঁকা);
	  ফেরত return_p;
	}
      অন্যথা যদি (c_parser_পরবর্তী_token_is (parser, CPP_EOF))
	{
	  c_parser_error (parser, "expected declaration or statement");
	  ফেরত return_p;
	}

      নির্বাচন (c_parser_peek_token (parser)->type)
	{
	ক্ষেত্র CPP_KEYWORD:
	  নির্বাচন (c_parser_peek_token (parser)->keyword)
	    {
	    ক্ষেত্র RID_AT_TRY:
	      c_parser_gimple_try_stmt (parser, seq);
	      বিরতি;
	    ক্ষেত্র RID_IF:
	      c_parser_gimple_if_stmt (parser, seq);
	      বিরতি;
	    ক্ষেত্র RID_SWITCH:
	      c_parser_gimple_switch_stmt (parser, seq);
	      বিরতি;
	    ক্ষেত্র RID_GOTO:
	      {
		location_t loc = c_parser_peek_token (parser)->location;
		c_parser_consume_token (parser);
		যদি (c_parser_পরবর্তী_token_is (parser, CPP_NAME))
		  {
		    বৃক্ষ label = c_parser_peek_token (parser)->মান;
		    c_parser_consume_token (parser);
		    c_parser_gimple_goto_stmt (parser, loc, label, seq);
		    যদি (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      ফেরত return_p;
		  }
		}
	      বিরতি;
	    ক্ষেত্র RID_RETURN:
	      return_p = সত্য;
	      c_parser_gimple_return_stmt (parser, seq);
	      যদি (! c_parser_require (parser, CPP_SEMICOLON,
				      "expected %<;%>"))
		ফেরত return_p;
	      যদি (cfun->curr_properties & PROP_cfg)
		parser.ঠেলো_edge (parser.current_bb->সূচক, EXIT_BLOCK, 0,
				  profile_probability::uninitialized ());
	      বিরতি;
	    পূর্বনির্ধারিত:
	      যাও রাশিমালা_stmt;
	    }
	  বিরতি;
	ক্ষেত্র CPP_NAME:
	  যদি (c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_gimple_label (parser, seq);
	      বিরতি;
	    }
	  যদি (c_parser_পরবর্তী_token_is (parser, CPP_NAME)
	      && c_parser_peek_token (parser)->id_kind == C_ID_ID
	      && strcmp (IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান),
			 "try") == 0)
	    {
	      c_parser_gimple_try_stmt (parser, seq);
	      বিরতি;
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
		ফেরত return_p;
	      যদি (c_parser_পরবর্তী_token_is_not (parser, CPP_সংখ্যা))
		{
		  c_parser_error (parser, "expected block index");
		  ফেরত return_p;
		}
	      বৃক্ষ tnum = c_parser_peek_token (parser)->মান;
	      যদি (বৃক্ষ_CODE (tnum) != INTEGER_CST)
		{
		  c_parser_error (parser, "expected block index");
		  ফেরত return_p;
		}
	      পূর্ণসংখ্যা সূচক = বৃক্ষ_INT_CST_নিচের (tnum);
	      যদি (সূচক < অঙ্ক_FIXED_BLOCKS
		  || (সূচক < last_basic_block_for_fn (cfun)
		      && BASIC_BLOCK_FOR_FN (cfun, সূচক) != ফাঁকা))
		{
		  c_parser_error (parser, "invalid block index");
		  ফেরত return_p;
		}
	      পূর্ণসংখ্যা is_loop_header_of = -1;
	      profile_গুনতি bb_গুনতি = profile_গুনতি::uninitialized ();
	      c_parser_consume_token (parser);
	      যখন (c_parser_পরবর্তী_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  যদি (! c_parser_পরবর্তী_token_is (parser, CPP_NAME))
		    {
		      c_parser_error (parser, "expected block specifier");
		      ফেরত return_p;
		    }
		  /* loop_header (NUM)  */
		  যদি (!strcmp (IDENTIFIER_POINTER
			         (c_parser_peek_token (parser)->মান),
			       "loop_header"))
		    {
		      c_parser_consume_token (parser);
		      যদি (! c_parser_require (parser, CPP_OPEN_PAREN,
					      "expected %<(%>"))
			ফেরত return_p;
		      বৃক্ষ loop_অঙ্ক;
		      যদি (! c_parser_পরবর্তী_token_is (parser, CPP_সংখ্যা)
			  || বৃক্ষ_CODE (loop_অঙ্ক
					  = c_parser_peek_token (parser)->মান)
			       != INTEGER_CST)
			{
			  c_parser_error (parser, "expected loop number");
			  ফেরত return_p;
			}
		      c_parser_consume_token (parser);
		      is_loop_header_of = বৃক্ষ_INT_CST_নিচের (loop_অঙ্ক);
		      যদি (! c_parser_require (parser, CPP_CLOSE_PAREN,
					      "expected %<)%>"))
			ফেরত return_p;
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
			  ফেরত মিথ্যা;
			}

		      c_parser_consume_token (parser);
		      যদি (!c_parser_require (parser, CPP_OPEN_PAREN,
					     "expected %<(%>"))
			ফেরত মিথ্যা;

		      যদি (!c_parser_পরবর্তী_token_is (parser, CPP_সংখ্যা)
			  || (বৃক্ষ_CODE (q = c_parser_peek_token (parser)->মান)
			      != INTEGER_CST))
			{
			  c_parser_error (parser, "expected count value");
			  ফেরত মিথ্যা;
			}

		      bb_গুনতি
			= profile_গুনতি::from_gcov_type (বৃক্ষ_INT_CST_নিচের (q),
							 quality);
		      c_parser_consume_token (parser);
		      যদি (! c_parser_require (parser, CPP_CLOSE_PAREN,
					      "expected %<)%>"))
			ফেরত return_p;
		    }
		}
	      যদি (! c_parser_require (parser, CPP_CLOSE_PAREN,
				      "expected %<)%>")
		  || ! c_parser_require (parser, CPP_COLON,
					 "expected %<:%>"))
		ফেরত return_p;

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
		  *seq = ফাঁকা;
		}

	      /* Build an empty block with specified index, linking them
		 in source order.  */
	      basic_block bb = alloc_block ();
	      bb->সূচক = সূচক;
	      link_block (bb, (parser.current_bb ? parser.current_bb
			       : ENTRY_BLOCK_PTR_FOR_FN (cfun)));
	      যদি (basic_block_info_for_fn (cfun)->দৈর্ঘ্য () <= (আকার_t)সূচক)
		vec_safe_grow_cleared (basic_block_info_for_fn (cfun),
				       সূচক + 1, সত্য);
	      SET_BASIC_BLOCK_FOR_FN (cfun, সূচক, bb);
	      যদি (last_basic_block_for_fn (cfun) <= সূচক)
		last_basic_block_for_fn (cfun) = সূচক + 1;
	      n_basic_blocks_for_fn (cfun)++;
	      যদি (parser.current_bb->সূচক == ENTRY_BLOCK)
		parser.ঠেলো_edge (ENTRY_BLOCK, bb->সূচক, EDGE_FALLTHRU,
				  profile_probability::always ());

	      /* We leave the proper setting to fixup.  */
	      শ্রেণী loop *loop_father = loops_for_fn (cfun)->বৃক্ষ_মূল;
	      /* If the new block is a loop header, allocate a loop
		 struct.  Fixup will take care of proper placement within
		 the loop tree.  */
	      যদি (is_loop_header_of != -1)
		{
		  যদি (সংখ্যা_of_loops (cfun) > (unsigned)is_loop_header_of
		      && get_loop (cfun, is_loop_header_of) != ফাঁকা)
		    {
		      c_parser_error (parser, "duplicate loop header");
		    }
		  অন্যথা
		    {
		      শ্রেণী loop *loop = alloc_loop ();
		      loop->অঙ্ক = is_loop_header_of;
		      loop->header = bb;
		      যদি (সংখ্যা_of_loops (cfun) <= (unsigned)is_loop_header_of)
			vec_safe_grow_cleared (loops_for_fn (cfun)->larray,
					       is_loop_header_of + 1, সত্য);
		      (*loops_for_fn (cfun)->larray)[is_loop_header_of] = loop;
		      flow_loop_বৃক্ষ_গ্রন্থি_add (loops_for_fn (cfun)->বৃক্ষ_মূল,
					       loop);
		    }
		  loop_father = get_loop (cfun, is_loop_header_of);
		}
	      bb->loop_father = loop_father;
	      bb->গুনতি = bb_গুনতি;

	      /* Stmts now go to the new block.  */
	      parser.current_bb = bb;
	      বিরতি;
	    }
	  যাও রাশিমালা_stmt;

	ক্ষেত্র CPP_SEMICOLON:
	  {
	    /* Empty stmt.  */
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);
	    gimple *nop = gimple_build_nop ();
	    gimple_set_location (nop, loc);
	    gimple_seq_add_stmt_without_update (seq, nop);
	    বিরতি;
	  }

	ক্ষেত্র CPP_CLOSE_PAREN:
	ক্ষেত্র CPP_CLOSE_SQUARE:
	  /* Avoid infinite loop in error recovery:
	     c_parser_skip_until_found stops at a closing nesting
	     delimiter without consuming it, but here we need to consume
	     it to proceed further.  */
	  c_parser_error (parser, "expected statement");
	  c_parser_consume_token (parser);
	বিরতি;

	পূর্বনির্ধারিত:
রাশিমালা_stmt:
	  c_parser_gimple_statement (parser, seq);
	  যদি (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	    c_parser_skip_until_found (parser, CPP_SEMICOLON, ফাঁকা);
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
      *seq = ফাঁকা;
    }

  ফেরত return_p;
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
  কাঠামো c_রাশিমালা lhs, rhs;
  gimple *assign = ফাঁকা;
  location_t loc;
  বৃক্ষ arg = NULL_বৃক্ষ;
  auto_vec<বৃক্ষ> vargs;

  lhs = c_parser_gimple_unary_expression (parser);
  loc = রাশিমালা_LOCATION (lhs.মান);
  rhs.set_error ();

  /* GIMPLE call statement without LHS.  */
  যদি (c_parser_পরবর্তী_token_is (parser, CPP_SEMICOLON)
      && বৃক্ষ_CODE (lhs.মান) == CALL_রাশিমালা)
    {
      gimple *call;
      call = gimple_build_call_from_বৃক্ষ (lhs.মান, ফাঁকা);
      gimple_seq_add_stmt_without_update (seq, call);
      gimple_set_location (call, loc);
      ফেরত;
    }

  /* All following cases are statements with LHS.  */
  যদি (! c_parser_require (parser, CPP_EQ, "expected %<=%>"))
    ফেরত;

  /* Eat and ignore {v} right after the =, the has_volatile_ops is
     redundant and re-computed by the operand scanner.  */
  যদি (c_parser_পরবর্তী_token_is (parser, CPP_OPEN_BRACE)
      && !(c_parser_peek_token (parser)->flags & পূর্ব_WHITE)
      && c_parser_peek_2nd_token (parser)->type == CPP_NAME
      && !(c_parser_peek_2nd_token (parser)->flags & পূর্ব_WHITE)
      && strcmp ("v", IDENTIFIER_POINTER
			(c_parser_peek_2nd_token (parser)->মান)) == 0
      && c_parser_peek_nth_token (parser, 3)->type == CPP_CLOSE_BRACE
      && !(c_parser_peek_nth_token (parser, 3)->flags & পূর্ব_WHITE))
    {
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }

  /* Cast expression.  */
  যদি (c_parser_পরবর্তী_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_typename (c_parser_peek_2nd_token (parser)))
    {
      c_parser_consume_token (parser);
      কাঠামো c_type_name *type_name = c_parser_type_name (parser);
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      যদি (type_name == ফাঁকা)
	ফেরত;
      /* ???  The actual type used in the cast expression is ignored as
         in GIMPLE it is encoded by the type of the LHS.  */
      rhs = c_parser_gimple_postfix_expression (parser);
      যদি (lhs.মান != error_mark_গ্রন্থি
	  && rhs.মান != error_mark_গ্রন্থি)
	{
	  গণনা বৃক্ষ_code code = NOP_রাশিমালা;
	  যদি (FLOAT_TYPE_P (বৃক্ষ_TYPE (lhs.মান))
	      && ! FLOAT_TYPE_P (বৃক্ষ_TYPE (rhs.মান)))
	    code = FLOAT_রাশিমালা;
	  অন্যথা যদি (! FLOAT_TYPE_P (বৃক্ষ_TYPE (lhs.মান))
		   && FLOAT_TYPE_P (বৃক্ষ_TYPE (rhs.মান)))
	    code = FIX_TRUNC_রাশিমালা;
	  assign = gimple_build_assign (lhs.মান, code, rhs.মান);
	  gimple_seq_add_stmt_without_update (seq, assign);
	  gimple_set_location (assign, loc);
	  ফেরত;
	}
    }

  /* Unary expression.  */
  নির্বাচন (c_parser_peek_token (parser)->type)
    {
    ক্ষেত্র CPP_NAME:
      {
	বৃক্ষ id = c_parser_peek_token (parser)->মান;
	যদি (strcmp (IDENTIFIER_POINTER (id), "__ABS") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__ABSU") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__MIN") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__MAX") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__BIT_INSERT") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__VEC_PERM") == 0)
	  যাও build_unary_রাশিমালা;
	বিরতি;
      }
    ক্ষেত্র CPP_KEYWORD:
      যদি (c_parser_peek_token (parser)->keyword != RID_REALPART
	  && c_parser_peek_token (parser)->keyword != RID_IMAGPART)
	বিরতি;
      /* Fallthru.  */
    ক্ষেত্র CPP_AND:
    ক্ষেত্র CPP_PLUS:
    ক্ষেত্র CPP_MINUS:
    ক্ষেত্র CPP_COMPL:
    ক্ষেত্র CPP_NOT:
    ক্ষেত্র CPP_MULT: /* pointer deref */
    build_unary_রাশিমালা:
      rhs = c_parser_gimple_unary_expression (parser);
      যদি (rhs.মান != error_mark_গ্রন্থি)
	{
	  assign = gimple_build_assign (lhs.মান, rhs.মান);
	  gimple_set_location (assign, loc);
	  gimple_seq_add_stmt_without_update (seq, assign);
	}
      ফেরত;

    পূর্বনির্ধারিত:;
    }

  /* GIMPLE PHI statement.  */
  যদি (c_parser_পরবর্তী_token_is_keyword (parser, RID_PHI))
    {
      c_parser_consume_token (parser);

      যদি (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	ফেরত;

      যদি (c_parser_পরবর্তী_token_is (parser, CPP_OPEN_PAREN))
	c_parser_consume_token (parser);

      যখন (c_parser_পরবর্তী_token_is_not (parser, CPP_CLOSE_PAREN))
	{
	  যদি (c_parser_পরবর্তী_token_is (parser, CPP_NAME)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      arg = c_parser_peek_token (parser)->মান;
	      c_parser_consume_token (parser);
	      যদি (c_parser_পরবর্তী_token_is (parser, CPP_COLON))
		c_parser_consume_token (parser);
	      পূর্ণসংখ্যা src_সূচক = -1;
	      যদি (!c_parser_gimple_parse_bb_spec (arg, &src_সূচক))
		c_parser_error (parser, "invalid source block specification");
	      vargs.safe_ঠেলো (আকার_int (src_সূচক));
	    }
	  অন্যথা যদি (c_parser_পরবর্তী_token_is (parser, CPP_COMMA))
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
      ফেরত;
    }

  /* GIMPLE call with lhs.  */
  যদি (c_parser_পরবর্তী_token_is (parser, CPP_DOT)
      || (c_parser_পরবর্তী_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN
	  && lookup_name (c_parser_peek_token (parser)->মান)))
    {
      rhs = c_parser_gimple_unary_expression (parser);
      যদি (rhs.মান != error_mark_গ্রন্থি)
	{
	  gimple *call = gimple_build_call_from_বৃক্ষ (rhs.মান, ফাঁকা);
	  gimple_call_set_lhs (call, lhs.মান);
	  gimple_seq_add_stmt_without_update (seq, call);
	  gimple_set_location (call, loc);
	}
      ফেরত;
    }

  rhs = c_parser_gimple_দ্বিমিক_expression (parser, বৃক্ষ_TYPE (lhs.মান));
  যদি (lhs.মান != error_mark_গ্রন্থি
      && rhs.মান != error_mark_গ্রন্থি)
    {
      /* If we parsed an identifier and the next token  is a '?' then parse
	 a conditional expression.  */
      যদি (SSA_VAR_P (rhs.মান) && c_parser_পরবর্তী_token_is (parser, CPP_QUERY))
	{
	  কাঠামো c_রাশিমালা trueval, falseval;
	  c_parser_consume_token (parser);
	  trueval = c_parser_gimple_postfix_expression (parser);
	  falseval.set_error ();
	  যদি (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    falseval = c_parser_gimple_postfix_expression (parser);
	  যদি (trueval.মান == error_mark_গ্রন্থি
	      || falseval.মান == error_mark_গ্রন্থি)
	    ফেরত;
	  rhs.মান = build3_loc (loc,
				  VECTOR_TYPE_P (বৃক্ষ_TYPE (rhs.মান))
				  ? VEC_COND_রাশিমালা : COND_রাশিমালা,
				  বৃক্ষ_TYPE (trueval.মান),
				  rhs.মান, trueval.মান, falseval.মান);
	}
      যদি (get_gimple_rhs_class (বৃক্ষ_CODE (rhs.মান)) == GIMPLE_INVALID_RHS)
	{
	  c_parser_error (parser, "unexpected RHS for assignment");
	  ফেরত;
	}
      assign = gimple_build_assign (lhs.মান, rhs.মান);
      gimple_seq_add_stmt_without_update (seq, assign);
      gimple_set_location (assign, loc);
    }
  ফেরত;
}

/* A mapping between an identifier to a tree code for binary operations. */
স্থির ধ্রুবক std::pair<ধ্রুবক অক্ষর *, বৃক্ষ_code> gimple_দ্বিমিক_identifier_code[] =
  {
    {"__MULT_HIGHPART", MULT_HIGHPART_রাশিমালা},
    {"__UNLT", UNLT_রাশিমালা},
    {"__UNLE", UNLE_রাশিমালা},
    {"__UNGT", UNGT_রাশিমালা},
    {"__UNGE", UNGE_রাশিমালা},
    {"__UNEQ", UNEQ_রাশিমালা},
    {"__UNORDERED", UNORDERED_রাশিমালা},
    {"__ORDERED", ORDERED_রাশিমালা},
    {"__LTGT", LTGT_রাশিমালা},
    {"__FLOOR_DIV", FLOOR_DIV_রাশিমালা},
    {"__ROUND_DIV", ROUND_DIV_রাশিমালা},
    {"__EXACT_DIV", EXACT_DIV_রাশিমালা},
    {"__CEIL_DIV", CEIL_DIV_রাশিমালা},
    {"__FLOOR_MOD", FLOOR_MOD_রাশিমালা},
    {"__ROUND_MOD", ROUND_MOD_রাশিমালা},
    {"__CEIL_MOD", CEIL_MOD_রাশিমালা},
    {"__ROTATE_LEFT", LROTATE_রাশিমালা},
    {"__ROTATE_RIGHT", RROTATE_রাশিমালা},
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

স্থির c_রাশিমালা
c_parser_gimple_দ্বিমিক_expression (gimple_parser &parser, বৃক্ষ ret_type)
{
  /* Location of the binary operator.  */
  কাঠামো c_রাশিমালা ret, lhs, rhs;
  গণনা বৃক্ষ_code code = ERROR_MARK;
  ret.set_error ();
  lhs = c_parser_gimple_postfix_expression (parser, ret_type);
  যদি (c_parser_error (parser))
    ফেরত ret;
  নির্বাচন (c_parser_peek_token (parser)->type)
    {
    ক্ষেত্র CPP_MULT:
      code = MULT_রাশিমালা;
      বিরতি;
    ক্ষেত্র CPP_DIV:
      code = TRUNC_DIV_রাশিমালা;
      বিরতি;
    ক্ষেত্র CPP_MOD:
      code = TRUNC_MOD_রাশিমালা;
      বিরতি;
    ক্ষেত্র CPP_PLUS:
      যদি (POINTER_TYPE_P (বৃক্ষ_TYPE (lhs.মান)))
	code = POINTER_PLUS_রাশিমালা;
      অন্যথা
	code = PLUS_রাশিমালা;
      বিরতি;
    ক্ষেত্র CPP_MINUS:
      যদি (POINTER_TYPE_P (বৃক্ষ_TYPE (lhs.মান)))
	code = POINTER_DIFF_রাশিমালা;
      অন্যথা
	code = MINUS_রাশিমালা;
      বিরতি;
    ক্ষেত্র CPP_LSHIFT:
      code = LSHIFT_রাশিমালা;
      বিরতি;
    ক্ষেত্র CPP_RSHIFT:
      code = RSHIFT_রাশিমালা;
      বিরতি;
    ক্ষেত্র CPP_LESS:
      code = LT_রাশিমালা;
      বিরতি;
    ক্ষেত্র CPP_GREATER:
      code = GT_রাশিমালা;
      বিরতি;
    ক্ষেত্র CPP_LESS_EQ:
      code = LE_রাশিমালা;
      বিরতি;
    ক্ষেত্র CPP_GREATER_EQ:
      code = GE_রাশিমালা;
      বিরতি;
    ক্ষেত্র CPP_EQ_EQ:
      code = EQ_রাশিমালা;
      বিরতি;
    ক্ষেত্র CPP_NOT_EQ:
      code = NE_রাশিমালা;
      বিরতি;
    ক্ষেত্র CPP_AND:
      code = BIT_AND_রাশিমালা;
      বিরতি;
    ক্ষেত্র CPP_XOR:
      code = BIT_XOR_রাশিমালা;
      বিরতি;
    ক্ষেত্র CPP_OR:
      code = BIT_IOR_রাশিমালা;
      বিরতি;
    ক্ষেত্র CPP_AND_AND:
      c_parser_error (parser, "%<&&%> not valid in GIMPLE");
      ফেরত ret;
    ক্ষেত্র CPP_OR_OR:
      c_parser_error (parser, "%<||%> not valid in GIMPLE");
      ফেরত ret;
    ক্ষেত্র CPP_NAME:
      {
	বৃক্ষ id = c_parser_peek_token (parser)->মান;
	জন্য (auto &p : gimple_দ্বিমিক_identifier_code)
	  {
	    যদি (strcmp (IDENTIFIER_POINTER (id), p.first) == 0)
	      {
		code = p.second;
		বিরতি;
	      }
	  }
	যদি (code != ERROR_MARK)
	  বিরতি;
      }
      /* Fallthru.  */
    পূর্বনির্ধারিত:
      /* Not a binary expression.  */
      ফেরত lhs;
    }
  location_t ret_loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  rhs = c_parser_gimple_postfix_expression (parser);
  যদি (lhs.মান != error_mark_গ্রন্থি && rhs.মান != error_mark_গ্রন্থি)
    ret.মান = build2_loc (ret_loc, code, ret_type, lhs.মান, rhs.মান);
  ফেরত ret;
}

/* Parse a gimple parentized binary expression.  */

স্থির c_রাশিমালা
c_parser_gimple_parentized_দ্বিমিক_expression (gimple_parser &parser,
					      location_t op_loc,
					      বৃক্ষ_code code)
{
  কাঠামো c_রাশিমালা ret;
  ret.set_error ();

  c_parser_consume_token (parser);
  যদি (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    ফেরত ret;
  c_রাশিমালা op1 = c_parser_gimple_postfix_expression (parser);
  যদি (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    ফেরত ret;
  c_রাশিমালা op2 = c_parser_gimple_postfix_expression (parser);
  যদি (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    ফেরত ret;

  যদি (op1.মান != error_mark_গ্রন্থি && op2.মান != error_mark_গ্রন্থি)
    ret.মান = build2_loc (op_loc,
			    code, বৃক্ষ_TYPE (op1.মান), op1.মান, op2.মান);
  ফেরত ret;
}

/* Parse a gimple parentized binary expression.  */

স্থির c_রাশিমালা
c_parser_gimple_parentized_ternary_expression (gimple_parser &parser,
					       location_t op_loc,
					       বৃক্ষ_code code)
{
  কাঠামো c_রাশিমালা ret;
  ret.set_error ();

  c_parser_consume_token (parser);
  যদি (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    ফেরত ret;
  c_রাশিমালা op1 = c_parser_gimple_postfix_expression (parser);
  যদি (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    ফেরত ret;
  c_রাশিমালা op2 = c_parser_gimple_postfix_expression (parser);
  যদি (!c_parser_require (parser, CPP_COMMA, "expected %<)%>"))
    ফেরত ret;
  c_রাশিমালা op3 = c_parser_gimple_postfix_expression (parser);
  যদি (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    ফেরত ret;

  যদি (op1.মান != error_mark_গ্রন্থি
      && op2.মান != error_mark_গ্রন্থি
      && op3.মান != error_mark_গ্রন্থি)
    ret.মান = build3_loc (op_loc,
			    code, বৃক্ষ_TYPE (op1.মান),
			    op1.মান, op2.মান, op3.মান);
  ফেরত ret;
}

/* Parse gimple unary expression.

   gimple-unary-expression:
     gimple-postfix-expression
     unary-operator gimple-postfix-expression

   unary-operator: one of
     & * + - ~ abs_expr
*/

স্থির c_রাশিমালা
c_parser_gimple_unary_expression (gimple_parser &parser)
{
  কাঠামো c_রাশিমালা ret, op;
  location_t op_loc = c_parser_peek_token (parser)->location;
  location_t finish;
  ret.set_error ();
  নির্বাচন (c_parser_peek_token (parser)->type)
    {
    ক্ষেত্র CPP_AND:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      mark_exp_read (op.মান);
      ফেরত gimple_parser_build_unary_op (op_loc, ADDR_রাশিমালা, op);
    ক্ষেত্র CPP_MULT:
      {
	c_parser_consume_token (parser);
	op = c_parser_gimple_postfix_expression (parser);
	যদি (op.মান == error_mark_গ্রন্থি)
	  ফেরত ret;
	যদি (! POINTER_TYPE_P (বৃক্ষ_TYPE (op.মান)))
	  {
	    error_at (op_loc, "expected pointer as argument of unary %<*%>");
	    ফেরত ret;
	  }
	finish = op.get_finish ();
	location_t combined_loc = make_location (op_loc, op_loc, finish);
	ret.মান = build_simple_mem_ref_loc (combined_loc, op.মান);
	বৃক্ষ_SIDE_EFFECTS (ret.মান)
	  = বৃক্ষ_THIS_VOLATILE (ret.মান)
	  = TYPE_VOLATILE (বৃক্ষ_TYPE (বৃক্ষ_TYPE (op.মান)));
	ret.src_range.m_start = op_loc;
	ret.src_range.m_finish = finish;
	ফেরত ret;
      }
    ক্ষেত্র CPP_PLUS:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      ফেরত gimple_parser_build_unary_op (op_loc, CONVERT_রাশিমালা, op);
    ক্ষেত্র CPP_MINUS:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      ফেরত gimple_parser_build_unary_op (op_loc, NEGATE_রাশিমালা, op);
    ক্ষেত্র CPP_COMPL:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      ফেরত gimple_parser_build_unary_op (op_loc, BIT_NOT_রাশিমালা, op);
    ক্ষেত্র CPP_NOT:
      c_parser_error (parser, "%<!%> not valid in GIMPLE");
      ফেরত ret;
    ক্ষেত্র CPP_KEYWORD:
      নির্বাচন (c_parser_peek_token (parser)->keyword)
	{
	ক্ষেত্র RID_REALPART:
	  c_parser_consume_token (parser);
	  op = c_parser_gimple_postfix_expression (parser);
	  ফেরত gimple_parser_build_unary_op (op_loc, REALPART_রাশিমালা, op);
	ক্ষেত্র RID_IMAGPART:
	  c_parser_consume_token (parser);
	  op = c_parser_gimple_postfix_expression (parser);
	  ফেরত gimple_parser_build_unary_op (op_loc, IMAGPART_রাশিমালা, op);
	পূর্বনির্ধারিত:
	  ফেরত c_parser_gimple_postfix_expression (parser);
	}
    ক্ষেত্র CPP_NAME:
	{
	  বৃক্ষ id = c_parser_peek_token (parser)->মান;
	  যদি (strcmp (IDENTIFIER_POINTER (id), "__ABS") == 0)
	    {
	      c_parser_consume_token (parser);
	      op = c_parser_gimple_postfix_expression (parser);
	      ফেরত gimple_parser_build_unary_op (op_loc, ABS_রাশিমালা, op);
	    }
	  অন্যথা যদি (strcmp (IDENTIFIER_POINTER (id), "__ABSU") == 0)
	    {
	      c_parser_consume_token (parser);
	      op = c_parser_gimple_postfix_expression (parser);
	      ফেরত gimple_parser_build_unary_op (op_loc, ABSU_রাশিমালা, op);
	    }
	  অন্যথা যদি (strcmp (IDENTIFIER_POINTER (id), "__MIN") == 0)
	    ফেরত c_parser_gimple_parentized_দ্বিমিক_expression (parser,
								 op_loc,
								 MIN_রাশিমালা);
	  অন্যথা যদি (strcmp (IDENTIFIER_POINTER (id), "__MAX") == 0)
	    ফেরত c_parser_gimple_parentized_দ্বিমিক_expression (parser,
								 op_loc,
								 MAX_রাশিমালা);
	  অন্যথা যদি (strcmp (IDENTIFIER_POINTER (id), "__VEC_PERM") == 0)
	    ফেরত c_parser_gimple_parentized_ternary_expression
			(parser, op_loc, VEC_PERM_রাশিমালা);
	  অন্যথা যদি (strcmp (IDENTIFIER_POINTER (id), "__BIT_INSERT") == 0)
	    {
	      /* __BIT_INSERT '(' postfix-expression, postfix-expression,
			          integer ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      যদি (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_রাশিমালা op0 = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_রাশিমালা op1 = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_রাশিমালা op2 = c_parser_gimple_postfix_expression (parser);
		  যদি (বৃক্ষ_CODE (op2.মান) != INTEGER_CST
		      || !int_fits_type_p (op2.মান, bitsizetype))
		    c_parser_error (parser, "expected constant offset");
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  যদি (op0.মান != error_mark_গ্রন্থি
		      && op1.মান != error_mark_গ্রন্থি
		      && বৃক্ষ_CODE (op2.মান) == INTEGER_CST)
		    ret.মান = build3_loc (loc, BIT_ঢোকাও_রাশিমালা,
					    বৃক্ষ_TYPE (op0.মান),
					    op0.মান, op1.মান,
					    fold_convert (bitsizetype,
							  op2.মান));
		}
	      ফেরত ret;
	    }
	  অন্যথা
	    ফেরত c_parser_gimple_postfix_expression (parser);
	}
    পূর্বনির্ধারিত:
      ফেরত c_parser_gimple_postfix_expression (parser);
    }
}

/* Decompose ID into base name (ID until ver_offset) and VERSION.  Return
   true if ID matches a SSA name.  */

স্থির যৌক্তিক
c_parser_parse_ssa_name_id (বৃক্ষ id, unsigned *version, unsigned *ver_offset)
{
  ধ্রুবক অক্ষর *token = IDENTIFIER_POINTER (id);
  ধ্রুবক অক্ষর *var_version = strrchr (token, '_');
  যদি (! var_version)
    ফেরত মিথ্যা;

  *ver_offset = var_version - token;
  জন্য (ধ্রুবক অক্ষর *p = var_version + 1; *p; ++p)
    যদি (! ISDIGIT (*p))
      ফেরত মিথ্যা;
  *version = atoi (var_version + 1);
  ফেরত *version > 0;
}

/* Get at the actual SSA name ID with VERSION starting at VER_OFFSET.
   TYPE is the type if the SSA name is being declared.  */

স্থির বৃক্ষ
c_parser_parse_ssa_name (gimple_parser &parser,
			 বৃক্ষ id, বৃক্ষ type, unsigned version,
			 unsigned ver_offset)
{
  বৃক্ষ name = NULL_বৃক্ষ;
  ধ্রুবক অক্ষর *token = IDENTIFIER_POINTER (id);

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
	      ফেরত error_mark_গ্রন্থি;
	    }
	  name = make_ssa_name_fn (cfun, type, ফাঁকা, version);
	}
    }
  অন্যথা
    {
      যদি (version < অঙ্ক_ssa_names)
	name = ssa_name (version);
      যদি (! name)
	{
	  /* Separate var name from version.  */
	  অক্ষর *var_name = XNEWVEC (অক্ষর, ver_offset + 1);
	  memcpy (var_name, token, ver_offset);
	  var_name[ver_offset] = '\0';
	  /* lookup for parent decl.  */
	  id = get_identifier (var_name);
	  বৃক্ষ parent = lookup_name (id);
	  XDELETEVEC (var_name);
	  যদি (! parent || parent == error_mark_গ্রন্থি)
	    {
	      c_parser_error (parser, "base variable or SSA name undeclared");
	      ফেরত error_mark_গ্রন্থি;
	    }
	  যদি (!(VAR_P (parent)
		|| বৃক্ষ_CODE (parent) == PARM_DECL
		|| বৃক্ষ_CODE (parent) == ফলাফল_DECL))
	    {
	      error ("invalid base %qE for SSA name", parent);
	      ফেরত error_mark_গ্রন্থি;
	    }
	  name = make_ssa_name_fn (cfun, parent,
				   gimple_build_nop (), version);
	}
    }

  ফেরত name;
}

/* Parse a gimple call to an internal function.

   gimple-call-internal:
     . identifier ( gimple-argument-expression-list[opt] )  */

স্থির কাঠামো c_রাশিমালা
c_parser_gimple_call_internal (gimple_parser &parser)
{
  কাঠামো c_রাশিমালা রাশিমালা;
  রাশিমালা.set_error ();

  gcc_assert (c_parser_পরবর্তী_token_is (parser, CPP_DOT));
  c_parser_consume_token (parser);
  location_t loc = c_parser_peek_token (parser)->location;
  যদি (!c_parser_পরবর্তী_token_is (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_kind != C_ID_ID)
    {
      c_parser_error (parser, "expecting internal function name");
      ফেরত রাশিমালা;
    }
  বৃক্ষ id = c_parser_peek_token (parser)->মান;
  internal_fn ifn = lookup_internal_fn (IDENTIFIER_POINTER (id));
  c_parser_consume_token (parser);
  যদি (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    {
      auto_vec<বৃক্ষ> exprlist;
      যদি (!c_parser_পরবর্তী_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_gimple_রাশিমালা_list (parser, &exprlist);
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      যদি (ifn == IFN_LAST)
	error_at (loc, "unknown internal function %qE", id);
      অন্যথা
	{
	  রাশিমালা.মান = build_call_রাশিমালা_internal_loc_array
	    (loc, ifn, void_type_গ্রন্থি, exprlist.দৈর্ঘ্য (),
	     exprlist.address ());
	  রাশিমালা.original_code = ERROR_MARK;
	  রাশিমালা.original_type = ফাঁকা;
	  রাশিমালা.m_decimal = 0;
	}
    }
  ফেরত রাশিমালা;
}

/* Parse '<' type [',' alignment] '>' and return a type on success
   and NULL_TREE on error.  */

স্থির বৃক্ষ
c_parser_gimple_typespec (gimple_parser &parser)
{
  কাঠামো c_type_name *type_name = ফাঁকা;
  বৃক্ষ alignment = NULL_বৃক্ষ;
  যদি (c_parser_require (parser, CPP_LESS, "expected %<<%>"))
    {
      type_name = c_parser_type_name (parser);
      /* Optional alignment.  */
      যদি (c_parser_পরবর্তী_token_is (parser, CPP_COMMA))
	{
	  c_parser_consume_token (parser);
	  alignment
	      = c_parser_gimple_postfix_expression (parser).মান;
	}
      c_parser_skip_until_found (parser,
				 CPP_GREATER, "expected %<>%>");
    }
  যদি (!type_name)
    ফেরত NULL_বৃক্ষ;
  বৃক্ষ tem;
  বৃক্ষ type = groktypename (type_name, &tem, ফাঁকা);
  যদি (alignment)
    type = build_aligned_type (type, বৃক্ষ_to_uhwi (alignment));
  ফেরত type;
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

স্থির কাঠামো c_রাশিমালা
c_parser_gimple_postfix_expression (gimple_parser &parser, বৃক্ষ ret_type)
{
  location_t loc = c_parser_peek_token (parser)->location;
  source_range tok_range = c_parser_peek_token (parser)->get_range ();
  কাঠামো c_রাশিমালা রাশিমালা;
  রাশিমালা.set_error ();
  নির্বাচন (c_parser_peek_token (parser)->type)
    {
    ক্ষেত্র CPP_সংখ্যা:
      রাশিমালা.মান = c_parser_peek_token (parser)->মান;
      set_c_রাশিমালা_source_range (&রাশিমালা, tok_range);
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      বিরতি;
    ক্ষেত্র CPP_CHAR:
    ক্ষেত্র CPP_CHAR16:
    ক্ষেত্র CPP_CHAR32:
    ক্ষেত্র CPP_UTF8CHAR:
    ক্ষেত্র CPP_WCHAR:
      রাশিমালা.মান = c_parser_peek_token (parser)->মান;
      set_c_রাশিমালা_source_range (&রাশিমালা, tok_range);
      c_parser_consume_token (parser);
      বিরতি;
    ক্ষেত্র CPP_STRING:
    ক্ষেত্র CPP_STRING16:
    ক্ষেত্র CPP_STRING32:
    ক্ষেত্র CPP_WSTRING:
    ক্ষেত্র CPP_UTF8STRING:
      রাশিমালা = c_parser_string_literal (parser, মিথ্যা, সত্য);
      বিরতি;
    ক্ষেত্র CPP_DOT:
      রাশিমালা = c_parser_gimple_call_internal (parser);
      বিরতি;
    ক্ষেত্র CPP_NAME:
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
	      কাঠামো c_রাশিমালা ptr, alias_off, step, সূচক, index2;
	      ptr.মান = error_mark_গ্রন্থি;
	      alias_off.মান = NULL_বৃক্ষ;
	      step.মান = NULL_বৃক্ষ;
	      সূচক.মান = NULL_বৃক্ষ;
	      index2.মান = NULL_বৃক্ষ;
	      unsigned short clique = 0;
	      unsigned short base = 0;
	      যৌক্তিক reverse_order = মিথ্যা;
	      কাঠামো c_রাশিমালা ro;
	      যদি (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  বৃক্ষ alias_type = NULL_বৃক্ষ;
		  /* Optional alias-type cast.  */
		  যদি (c_parser_পরবর্তী_token_is (parser, CPP_OPEN_PAREN))
		    {
		      c_parser_consume_token (parser);
		      কাঠামো c_type_name *alias_type_name
			= c_parser_type_name (parser);
		      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
						 "expected %<)%>");
		      যদি (alias_type_name)
			{
			  বৃক্ষ tem;
			  alias_type = groktypename (alias_type_name,
						     &tem, ফাঁকা);
			}
		    }
		  ptr = c_parser_gimple_unary_expression (parser);
		  যদি (ptr.মান == error_mark_গ্রন্থি
		      || ! POINTER_TYPE_P (বৃক্ষ_TYPE (ptr.মান)))
		    {
		      যদি (ptr.মান != error_mark_গ্রন্থি)
			error_at (ptr.get_start (),
				  "invalid type of %<__MEM%> operand");
		      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
						 "expected %<)%>");
		      ফেরত রাশিমালা;
		    }
		  যদি (! alias_type)
		    alias_type = বৃক্ষ_TYPE (ptr.মান);
		  /* Optional constant offset.  */
		  যদি (c_parser_পরবর্তী_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      alias_off = c_parser_gimple_postfix_expression (parser);
		    }
		  যদি (c_parser_পরবর্তী_token_is (parser, CPP_MULT))
		    {
		      std::swap (সূচক, alias_off);
		      c_parser_consume_token (parser);
		      step = c_parser_gimple_postfix_expression (parser);
		    }
		  অন্যথা যদি (c_parser_পরবর্তী_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      সূচক = c_parser_gimple_postfix_expression (parser);
		      যদি (c_parser_পরবর্তী_token_is (parser, CPP_MULT))
			{
			  c_parser_consume_token (parser);
			  step = c_parser_gimple_postfix_expression (parser);
			}
		      অন্যথা
			std::swap (সূচক, index2);
		    }
		  অন্যথা যদি (alias_off.মান
			   && বৃক্ষ_CODE (alias_off.মান) != INTEGER_CST)
		    std::swap (alias_off, index2);
		  যদি (c_parser_পরবর্তী_token_is (parser, CPP_PLUS))
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
		  যদি (c_parser_পরবর্তী_token_is (parser, CPP_COMMA))
		    {
		      কাঠামো c_রাশিমালা cl, ba;
		      যৌক্তিক has_clb = সত্য;
		      c_parser_consume_token (parser);
		      cl = c_parser_gimple_postfix_expression (parser);
		      যদি (!c_parser_পরবর্তী_token_is (parser, CPP_COLON))
			{
			  ro = cl;
			  unsigned HOST_WIDE_INT tmp = 0;
			  যদি (!বৃক্ষ_fits_uhwi_p (ro.মান)
			      || (tmp = বৃক্ষ_to_uhwi (ro.মান)) > 1)
			    error_at (ro.get_start (),
				      "invalid reverse order value");
			  reverse_order = tmp;
			  has_clb = মিথ্যা;
			  যদি (c_parser_পরবর্তী_token_is (parser, CPP_COMMA))
			    {
			      c_parser_consume_token (parser);
			      cl = c_parser_gimple_postfix_expression (parser);
		              has_clb = সত্য;
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
		  c_parser_set_error (parser, মিথ্যা);
		  ফেরত রাশিমালা;
		}
	      যদি (সূচক.মান || step.মান || index2.মান)
		রাশিমালা.মান = build5_loc (loc, TARGET_MEM_REF,
					 type, ptr.মান, alias_off.মান,
					 সূচক.মান, step.মান, index2.মান);
	      অন্যথা
		রাশিমালা.মান = build2_loc (loc, MEM_REF,
					 type, ptr.মান, alias_off.মান);
	      যদি (clique != 0)
		{
		  cfun->last_clique = MAX (cfun->last_clique, clique);
		  MR_DEPENDENCE_CLIQUE (রাশিমালা.মান) = clique;
		  MR_DEPENDENCE_BASE (রাশিমালা.মান) = base;
		}
	      যদি (reverse_order)
		{
		  যদি (বৃক্ষ_CODE (রাশিমালা.মান) == MEM_REF)
		    REF_REVERSE_STORAGE_ORDER (রাশিমালা.মান) = reverse_order;
		  অন্যথা
		    error_at (ro.get_start (),
			      "target mem ref cannot have reverse order");
		}
	      বিরতি;
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
		  c_রাশিমালা op = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  যদি (type && op.মান != error_mark_গ্রন্থি)
		    রাশিমালা.মান = build1_loc (loc, VIEW_CONVERT_রাশিমালা,
					     type, op.মান);
		}
	      বিরতি;
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
		  c_রাশিমালা op0 = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_রাশিমালা op1 = c_parser_gimple_postfix_expression (parser);
		  যদি (বৃক্ষ_CODE (op1.মান) != INTEGER_CST
		      || !int_fits_type_p (op1.মান, bitsizetype))
		    c_parser_error (parser, "expected constant size");
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_রাশিমালা op2 = c_parser_gimple_postfix_expression (parser);
		  যদি (বৃক্ষ_CODE (op2.মান) != INTEGER_CST
		      || !int_fits_type_p (op2.মান, bitsizetype))
		    c_parser_error (parser, "expected constant offset");
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  যদি (type
		      && op0.মান != error_mark_গ্রন্থি
		      && বৃক্ষ_CODE (op1.মান) == INTEGER_CST
		      && বৃক্ষ_CODE (op2.মান) == INTEGER_CST)
		    রাশিমালা.মান = build3_loc (loc, BIT_FIELD_REF, type,
					     op0.মান,
					     fold_convert (bitsizetype,
							   op1.মান),
					     fold_convert (bitsizetype,
							   op2.মান));
		}
	      বিরতি;
	    }
	  অন্যথা যদি (strcmp (IDENTIFIER_POINTER (id), "__CLOBBER") == 0)
	    {
	      /* __CLOBBER [ '(' bob | eob | bos | eos ')' ]  */
	      clobber_kind kind = CLOBBER_UNDEF;
	      c_parser_consume_token (parser);
	      যদি (c_parser_পরবর্তী_token_is (parser, CPP_OPEN_PAREN))
		{
		  c_parser_consume_token (parser);
		  auto tok = c_parser_peek_token (parser);
		  যদি (c_parser_require (parser, CPP_NAME,
					"expected clobber kind"))
		    {
		      ধ্রুবক অক্ষর *kind_str = IDENTIFIER_POINTER (tok->মান);
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
	      রাশিমালা.মান = build_clobber (ret_type, kind);
	      বিরতি;
	    }
	  অন্যথা যদি (strcmp (IDENTIFIER_POINTER (id), "_Literal") == 0)
	    {
	      /* _Literal '(' type-name ')' ( [ '-' ] constant | constructor ) */
	      c_parser_consume_token (parser);
	      বৃক্ষ type = NULL_বৃক্ষ;
	      যদি (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  কাঠামো c_type_name *type_name = c_parser_type_name (parser);
		  বৃক্ষ tem;
		  যদি (type_name)
		    type = groktypename (type_name, &tem, ফাঁকা);
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      যদি (! type)
		{
		  c_parser_error (parser, "invalid _Literal");
		  ফেরত রাশিমালা;
		}
	      যদি (c_parser_পরবর্তী_token_is (parser, CPP_OPEN_BRACE))
		{
		  c_parser_consume_token (parser);
		  যদি (!AGGREGATE_TYPE_P (type)
		      && !VECTOR_TYPE_P (type))
		    {
		      c_parser_error (parser, "invalid type for _Literal with "
				      "constructor");
		      c_parser_skip_until_found (parser, CPP_CLOSE_BRACE,
						 "expected %<}%>");
		      ফেরত রাশিমালা;
		    }
		  vec<constructor_elt, va_gc> *v = ফাঁকা;
		  যৌক্তিক constant_p = সত্য;
		  যদি (VECTOR_TYPE_P (type)
		      && !c_parser_পরবর্তী_token_is (parser, CPP_CLOSE_BRACE))
		    {
		      vec_alloc (v, TYPE_VECTOR_SUBPARTS (type).to_constant ());
		      করো
			{
			  বৃক্ষ val
			    = c_parser_gimple_postfix_expression (parser).মান;
			  যদি (! val
			      || val == error_mark_গ্রন্থি
			      || (! CONSTANT_CLASS_P (val)
				  && ! SSA_VAR_P (val)))
			    {
			      c_parser_error (parser, "invalid _Literal");
			      ফেরত রাশিমালা;
			    }
			  CONSTRUCTOR_APPEND_ELT (v, NULL_বৃক্ষ, val);
			  যদি (! CONSTANT_CLASS_P (val))
			    constant_p = মিথ্যা;
			  যদি (c_parser_পরবর্তী_token_is (parser, CPP_COMMA))
			    c_parser_consume_token (parser);
			  অন্যথা
			    বিরতি;
			}
		      যখন (1);
		    }
		  যদি (c_parser_require (parser, CPP_CLOSE_BRACE,
					"expected %<}%>"))
		    {
		      যদি (v && constant_p)
			রাশিমালা.মান = build_vector_from_ctor (type, v);
		      অন্যথা
			রাশিমালা.মান = build_constructor (type, v);
		    }
		  অন্যথা
		    {
		      c_parser_skip_until_found (parser, CPP_CLOSE_BRACE,
						 "expected %<}%>");
		      ফেরত রাশিমালা;
		    }
		}
	      অন্যথা
		{
		  যৌক্তিক neg_p, addr_p;
		  যদি ((neg_p = c_parser_পরবর্তী_token_is (parser, CPP_MINUS)))
		    c_parser_consume_token (parser);
		  যদি ((addr_p = c_parser_পরবর্তী_token_is (parser, CPP_AND)))
		    c_parser_consume_token (parser);
		  বৃক্ষ val = c_parser_gimple_postfix_expression (parser).মান;
		  যদি (! val
		      || val == error_mark_গ্রন্থি
		      || (!CONSTANT_CLASS_P (val) && !addr_p))
		    {
		      c_parser_error (parser, "invalid _Literal");
		      ফেরত রাশিমালা;
		    }
		  যদি (addr_p)
		    {
		      val = build1 (ADDR_রাশিমালা, type, val);
		      যদি (!is_gimple_invariant_address (val))
			{
			  c_parser_error (parser, "invalid _Literal");
			  ফেরত রাশিমালা;
			}
		    }
		  যদি (neg_p)
		    {
		      val = const_unop (NEGATE_রাশিমালা, বৃক্ষ_TYPE (val), val);
		      যদি (! val)
			{
			  c_parser_error (parser, "invalid _Literal");
			  ফেরত রাশিমালা;
			}
		    }
		  রাশিমালা.মান = fold_convert (type, val);
		}
	      ফেরত রাশিমালা;
	    }

	  /* SSA name.  */
	  unsigned version, ver_offset;
	  যদি (! lookup_name (id)
	      && c_parser_parse_ssa_name_id (id, &version, &ver_offset))
	    {
	      c_parser_consume_token (parser);
	      রাশিমালা.মান = c_parser_parse_ssa_name (parser, id, NULL_বৃক্ষ,
						    version, ver_offset);
	      যদি (রাশিমালা.মান == error_mark_গ্রন্থি)
		ফেরত রাশিমালা;
	      set_c_রাশিমালা_source_range (&রাশিমালা, tok_range);
	      /* For default definition SSA names.  */
	      যদি (c_parser_পরবর্তী_token_is (parser, CPP_OPEN_PAREN)
		  && c_parser_peek_2nd_token (parser)->type == CPP_NAME
		  && strcmp ("D",
			     IDENTIFIER_POINTER
			       (c_parser_peek_2nd_token (parser)->মান)) == 0
		  && c_parser_peek_nth_token (parser, 3)->type == CPP_CLOSE_PAREN)
		{
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		  যদি (! SSA_NAME_IS_DEFAULT_DEF (রাশিমালা.মান))
		    {
		      যদি (!SSA_NAME_VAR (রাশিমালা.মান))
			{
			  error_at (loc, "anonymous SSA name cannot have"
				    " default definition");
			  রাশিমালা.মান = error_mark_গ্রন্থি;
			  ফেরত রাশিমালা;
			}
		      set_ssa_default_def (cfun, SSA_NAME_VAR (রাশিমালা.মান),
					   রাশিমালা.মান);
		      SSA_NAME_DEF_STMT (রাশিমালা.মান) = gimple_build_nop ();
		    }
		}
	    }
	  অন্যথা
	    {
	      c_parser_consume_token (parser);
	      রাশিমালা.মান
		= build_external_ref (loc, id,
				      (c_parser_peek_token (parser)->type
				       == CPP_OPEN_PAREN), &রাশিমালা.original_type);
	      set_c_রাশিমালা_source_range (&রাশিমালা, tok_range);
	    }
	  বিরতি;
	}
      /* Fallthru.  */
    পূর্বনির্ধারিত:
      c_parser_error (parser, "expected expression");
      রাশিমালা.set_error ();
      বিরতি;
    }
  যদি (রাশিমালা.মান == error_mark_গ্রন্থি)
    ফেরত রাশিমালা;
  ফেরত c_parser_gimple_postfix_expression_after_primary
    (parser, রাশিমালা_LOC_OR_LOC (রাশিমালা.মান, loc), রাশিমালা);
}

/* Parse a gimple postfix expression after the initial primary or compound
   literal.  */

স্থির কাঠামো c_রাশিমালা
c_parser_gimple_postfix_expression_after_primary (gimple_parser &parser,
						  location_t রাশিমালা_loc,
						  কাঠামো c_রাশিমালা রাশিমালা)
{
  location_t start;
  location_t finish;
  বৃক্ষ ident;
  location_t comp_loc;

  যখন (সত্য)
    {
      location_t op_loc = c_parser_peek_token (parser)->location;
      নির্বাচন (c_parser_peek_token (parser)->type)
	{
	ক্ষেত্র CPP_OPEN_SQUARE:
	  {
	    c_parser_consume_token (parser);
	    বৃক্ষ idx = c_parser_gimple_unary_expression (parser).মান;

	    যদি (! c_parser_require (parser, CPP_CLOSE_SQUARE, "expected %<]%>"))
	      {
		c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE, ফাঁকা);
		বিরতি;
	      }

	    start = রাশিমালা.get_start ();
	    finish = c_parser_tokens_buf (parser, 0)->location;
	    রাশিমালা.মান = build_array_ref (op_loc, রাশিমালা.মান, idx);
	    set_c_রাশিমালা_source_range (&রাশিমালা, start, finish);
	    রাশিমালা.m_decimal = 0;

	    রাশিমালা.original_code = ERROR_MARK;
	    রাশিমালা.original_type = ফাঁকা;
	    বিরতি;
	  }
	ক্ষেত্র CPP_OPEN_PAREN:
	  {
	    /* Function call.  */
	    c_parser_consume_token (parser);
	    auto_vec<বৃক্ষ> exprlist;
	    যদি (! c_parser_পরবর্তী_token_is (parser, CPP_CLOSE_PAREN))
	      c_parser_gimple_রাশিমালা_list (parser, &exprlist);
	    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    যদি (!FUNC_OR_METHOD_TYPE_P (বৃক্ষ_TYPE (রাশিমালা.মান)))
	      {
		c_parser_error (parser, "invalid call to non-function");
		রাশিমালা.set_error ();
		বিরতি;
	      }
	    রাশিমালা.মান = build_call_array_loc
		(রাশিমালা_loc, বৃক্ষ_TYPE (বৃক্ষ_TYPE (রাশিমালা.মান)),
		 রাশিমালা.মান, exprlist.দৈর্ঘ্য (), exprlist.address ());
	    রাশিমালা.m_decimal = 0;
	    রাশিমালা.original_code = ERROR_MARK;
	    রাশিমালা.original_type = ফাঁকা;
	    বিরতি;
	  }
	ক্ষেত্র CPP_DOT:
	  {
	    /* Structure element reference.  */
	    c_parser_consume_token (parser);
	    যদি (c_parser_পরবর্তী_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		ident = comp_tok->মান;
		comp_loc = comp_tok->location;
	      }
	    অন্যথা
	      {
		c_parser_error (parser, "expected identifier");
		রাশিমালা.set_error ();
		রাশিমালা.original_code = ERROR_MARK;
		রাশিমালা.original_type = ফাঁকা;
		ফেরত রাশিমালা;
	      }
	    start = রাশিমালা.get_start ();
	    finish = c_parser_peek_token (parser)->get_finish ();
	    c_parser_consume_token (parser);
	    রাশিমালা.মান = build_component_ref (op_loc, রাশিমালা.মান, ident,
					      comp_loc, UNKNOWN_LOCATION);
	    set_c_রাশিমালা_source_range (&রাশিমালা, start, finish);
	    রাশিমালা.m_decimal = 0;
	    রাশিমালা.original_code = ERROR_MARK;
	    যদি (বৃক্ষ_CODE (রাশিমালা.মান) != COMPONENT_REF)
	      রাশিমালা.original_type = ফাঁকা;
	    অন্যথা
	      {
		/* Remember the original type of a bitfield.  */
		বৃক্ষ field = বৃক্ষ_OPERAND (রাশিমালা.মান, 1);
		যদি (বৃক্ষ_CODE (field) != FIELD_DECL)
		  রাশিমালা.original_type = ফাঁকা;
		অন্যথা
		  রাশিমালা.original_type = DECL_BIT_FIELD_TYPE (field);
	      }
	    বিরতি;
	  }
	ক্ষেত্র CPP_DEREF:
	  {
	    /* Structure element reference.  */
	    যদি (!POINTER_TYPE_P (বৃক্ষ_TYPE (রাশিমালা.মান)))
	      {
		c_parser_error (parser, "dereference of non-pointer");
		রাশিমালা.set_error ();
		রাশিমালা.original_code = ERROR_MARK;
		রাশিমালা.original_type = ফাঁকা;
		ফেরত রাশিমালা;
	      }
	    c_parser_consume_token (parser);
	    যদি (c_parser_পরবর্তী_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		ident = comp_tok->মান;
		comp_loc = comp_tok->location;
	      }
	    অন্যথা
	      {
		c_parser_error (parser, "expected identifier");
		রাশিমালা.set_error ();
		রাশিমালা.original_code = ERROR_MARK;
		রাশিমালা.original_type = ফাঁকা;
		ফেরত রাশিমালা;
	      }
	    start = রাশিমালা.get_start ();
	    finish = c_parser_peek_token (parser)->get_finish ();
	    c_parser_consume_token (parser);
	    রাশিমালা.মান = build_component_ref (op_loc,
					      build_simple_mem_ref_loc
					        (op_loc, রাশিমালা.মান),
					      ident, comp_loc,
					      রাশিমালা.get_location ());
	    set_c_রাশিমালা_source_range (&রাশিমালা, start, finish);
	    রাশিমালা.m_decimal = 0;
	    রাশিমালা.original_code = ERROR_MARK;
	    যদি (বৃক্ষ_CODE (রাশিমালা.মান) != COMPONENT_REF)
	      রাশিমালা.original_type = ফাঁকা;
	    অন্যথা
	      {
		/* Remember the original type of a bitfield.  */
		বৃক্ষ field = বৃক্ষ_OPERAND (রাশিমালা.মান, 1);
		যদি (বৃক্ষ_CODE (field) != FIELD_DECL)
		  রাশিমালা.original_type = ফাঁকা;
		অন্যথা
		  রাশিমালা.original_type = DECL_BIT_FIELD_TYPE (field);
	      }
	    বিরতি;
	  }
	পূর্বনির্ধারিত:
	  ফেরত রাশিমালা;
	}
    }
}

/* Parse expression list.

   gimple-expr-list:
     gimple-unary-expression
     gimple-expr-list , gimple-unary-expression

 */

স্থির শূন্য
c_parser_gimple_রাশিমালা_list (gimple_parser &parser, vec<বৃক্ষ> *ret)
{
  কাঠামো c_রাশিমালা রাশিমালা;

  রাশিমালা = c_parser_gimple_unary_expression (parser);
  ret->safe_ঠেলো (রাশিমালা.মান);
  যখন (c_parser_পরবর্তী_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      রাশিমালা = c_parser_gimple_unary_expression (parser);
      ret->safe_ঠেলো (রাশিমালা.মান);
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
  gcc_assert (c_parser_পরবর্তী_token_is (parser, CPP_NAME));
  c_parser_consume_token (parser);
  gcc_assert (c_parser_পরবর্তী_token_is (parser, CPP_COLON));
  c_parser_consume_token (parser);
  বৃক্ষ label = define_label (loc1, name);
  যদি (label)
    gimple_seq_add_stmt_without_update (seq, gimple_build_label (label));
  ফেরত;
}

/* Parse gimple/RTL pass list.

   gimple-or-rtl-pass-list:
     startwith("pass-name")[,{cfg,ssa}]
 */

শূন্য
c_parser_gimple_or_rtl_pass_list (c_parser *parser, c_declspecs *specs)
{
  অক্ষর *pass = ফাঁকা;

  /* Accept __GIMPLE/__RTL.  */
  যদি (c_parser_পরবর্তী_token_is_not (parser, CPP_OPEN_PAREN))
    ফেরত;
  c_parser_consume_token (parser);

  specs->entry_bb_গুনতি = profile_গুনতি::uninitialized ();
  যখন (c_parser_পরবর্তী_token_is (parser, CPP_NAME))
    {
      profile_quality quality;
      ধ্রুবক অক্ষর *op = IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান);
      c_parser_consume_token (parser);
      যদি (! strcmp (op, "startwith"))
	{
	  যদি (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    ফেরত;
	  যদি (c_parser_পরবর্তী_token_is_not (parser, CPP_STRING))
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"expected pass name");
	      ফেরত;
	    }
	  pass = xstrdup (বৃক্ষ_STRING_POINTER
			  (c_parser_string_literal (parser, মিথ্যা,
						    মিথ্যা).মান));
	  যদি (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<(%>"))
	    ফেরত;
	}
      অন্যথা যদি (parse_profile_quality (op, &quality))
	{
	  বৃক্ষ q;
	  যদি (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    ফেরত;

	  যদি (!c_parser_পরবর্তী_token_is (parser, CPP_সংখ্যা)
	      || (বৃক্ষ_CODE (q = c_parser_peek_token (parser)->মান)
		  != INTEGER_CST))
	    {
	      c_parser_error (parser, "expected count value");
	      ফেরত;
	    }

	  specs->entry_bb_গুনতি
	    = profile_গুনতি::from_gcov_type (বৃক্ষ_INT_CST_নিচের (q), quality);
	  c_parser_consume_token (parser);
	  যদি (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    ফেরত;
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
	  ফেরত;
	}
     যদি (c_parser_পরবর্তী_token_is (parser, CPP_COMMA))
       c_parser_consume_token (parser);
    }

  যদি (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    ফেরত;

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
  কাঠামো c_declarator *declarator;
  কাঠামো c_declspecs *specs = build_null_declspecs ();
  c_parser_declspecs (parser, specs, সত্য, সত্য, সত্য,
		      সত্য, সত্য, সত্য, সত্য, cla_nonabstract_decl);
  finish_declspecs (specs);

  /* Provide better error recovery.  Note that a type name here is usually
     better diagnosed as a redeclaration.  */
  যদি (c_parser_পরবর্তী_token_starts_declspecs (parser)
      && ! c_parser_পরবর্তী_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<;%>");
      c_parser_set_error (parser, মিথ্যা);
      ফেরত;
    }

  যৌক্তিক dummy = মিথ্যা;
  declarator = c_parser_declarator (parser,
				    specs->typespec_kind != ctsk_none,
				    C_DTR_NORMAL, &dummy);

  যদি (!c_parser_পরবর্তী_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_error (parser, "expected %<;%>");
      ফেরত;
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
      কাঠামো c_declarator *id_declarator = declarator;
      যখন (id_declarator->kind == cdk_pointer)
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
	  কাঠামো c_declarator *p = declarator;
	  বৃক্ষ type = specs->type;
	  যখন (p->kind == cdk_pointer)
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
	  specs->attrs = ফাঁকা;
	  বৃক্ষ decl = start_decl (declarator, specs, মিথ্যা,
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
      পূর্ণসংখ্যা dest_সূচক;
      profile_probability prob;
      যদি (c_parser_gimple_parse_bb_spec_edge_probability (label, parser,
							  &dest_সূচক, &prob))
	{
	  parser.ঠেলো_edge (parser.current_bb->সূচক, dest_সূচক,
			    EDGE_FALLTHRU, prob);
	  ফেরত;
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
    ফেরত error_mark_গ্রন্থি;
  বৃক্ষ cond
    = c_parser_gimple_দ্বিমিক_expression (parser, boolean_type_গ্রন্থি).মান;
  যদি (cond != error_mark_গ্রন্থি
      && ! COMPARISON_CLASS_P (cond)
      && ! CONSTANT_CLASS_P (cond)
      && ! SSA_VAR_P (cond))
    {
      c_parser_error (parser, "comparison required");
      cond = error_mark_গ্রন্থি;
    }
  যদি (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    ফেরত error_mark_গ্রন্থি;
  ফেরত cond;
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
  gimple_seq tryseq = ফাঁকা;
  c_parser_consume_token (parser);
  c_parser_gimple_compound_statement (parser, &tryseq);

  যদি ((c_parser_পরবর্তী_token_is (parser, CPP_KEYWORD)
       && c_parser_peek_token (parser)->keyword == RID_AT_FINALLY)
      || (c_parser_পরবর্তী_token_is (parser, CPP_NAME)
	  && c_parser_peek_token (parser)->id_kind == C_ID_ID
	  && strcmp (IDENTIFIER_POINTER (c_parser_peek_token (parser)->মান),
		     "finally") == 0))
    {
      gimple_seq finseq = ফাঁকা;
      c_parser_consume_token (parser);
      c_parser_gimple_compound_statement (parser, &finseq);

      যদি (c_parser_পরবর্তী_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_ELSE)
	{
	  gimple_seq elsseq = ফাঁকা;
	  c_parser_consume_token (parser);
	  c_parser_gimple_compound_statement (parser, &elsseq);

	  geh_else *stmt = gimple_build_eh_else (finseq, elsseq);
	  finseq = ফাঁকা;
	  gimple_seq_add_stmt_without_update (&finseq, stmt);
	}

      gtry *stmt = gimple_build_try (tryseq, finseq, GIMPLE_TRY_FINALLY);
      gimple_seq_add_stmt_without_update (seq, stmt);
    }
  অন্যথা যদি (c_parser_পরবর্তী_token_is (parser, CPP_KEYWORD)
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

  যদি (c_parser_পরবর্তী_token_is_keyword (parser, RID_GOTO))
    {
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      যদি (! c_parser_পরবর্তী_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected label");
	  ফেরত;
	}
      label = c_parser_peek_token (parser)->মান;
      c_parser_consume_token (parser);
      পূর্ণসংখ্যা dest_সূচক;
      profile_probability prob;
      যদি ((cfun->curr_properties & PROP_cfg)
	  && c_parser_gimple_parse_bb_spec_edge_probability (label, parser,
							     &dest_সূচক, &prob))
	parser.ঠেলো_edge (parser.current_bb->সূচক, dest_সূচক,
			  EDGE_TRUE_মান, prob);
      অন্যথা
	t_label = lookup_label_for_goto (loc, label);
      যদি (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	ফেরত;
    }
  অন্যথা
    {
      c_parser_error (parser, "expected goto expression");
      ফেরত;
    }

  যদি (c_parser_পরবর্তী_token_is_keyword (parser, RID_ELSE))
    c_parser_consume_token (parser);
  অন্যথা
    {
      c_parser_error (parser, "expected else statement");
      ফেরত;
    }

  যদি (c_parser_পরবর্তী_token_is_keyword (parser, RID_GOTO))
    {
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      যদি (! c_parser_পরবর্তী_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected label");
	  ফেরত;
	}
      label = c_parser_peek_token (parser)->মান;
      c_parser_consume_token (parser);
      পূর্ণসংখ্যা dest_সূচক;
      profile_probability prob;
      যদি ((cfun->curr_properties & PROP_cfg)
	  && c_parser_gimple_parse_bb_spec_edge_probability (label, parser,
							     &dest_সূচক, &prob))
	parser.ঠেলো_edge (parser.current_bb->সূচক, dest_সূচক,
			  EDGE_FALSE_মান, prob);
      অন্যথা
	f_label = lookup_label_for_goto (loc, label);
      যদি (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	ফেরত;
    }
  অন্যথা
    {
      c_parser_error (parser, "expected goto expression");
      ফেরত;
    }

  যদি (cond != error_mark_গ্রন্থি)
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
  c_রাশিমালা cond_রাশিমালা;
  বৃক্ষ case_label, label;
  auto_vec<বৃক্ষ> labels;
  বৃক্ষ default_label = NULL_বৃক্ষ;
  c_parser_consume_token (parser);

  যদি (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    ফেরত;
  cond_রাশিমালা = c_parser_gimple_postfix_expression (parser);
  যদি (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    ফেরত;

  যদি (! c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    ফেরত;

  যখন (c_parser_পরবর্তী_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      যদি (c_parser_পরবর্তী_token_is (parser, CPP_EOF))
	{
	  c_parser_error (parser, "expected statement");
	  ফেরত;
	}

      নির্বাচন (c_parser_peek_token (parser)->keyword)
	{
	ক্ষেত্র RID_CASE:
	  {
	    c_রাশিমালা exp1;
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);

	    যদি (c_parser_পরবর্তী_token_is (parser, CPP_NAME)
		|| c_parser_peek_token (parser)->type == CPP_সংখ্যা)
	      exp1 = c_parser_gimple_postfix_expression (parser);
	    অন্যথা
	      {
		c_parser_error (parser, "expected expression");
		ফেরত;
	      }

	    যদি (c_parser_পরবর্তী_token_is (parser, CPP_COLON))
	      {
		c_parser_consume_token (parser);
		যদি (c_parser_পরবর্তী_token_is (parser, CPP_NAME))
		  {
		    label = c_parser_peek_token (parser)->মান;
		    c_parser_consume_token (parser);
		    বৃক্ষ decl = lookup_label_for_goto (loc, label);
		    case_label = build_case_label (exp1.মান, NULL_বৃক্ষ,
						   decl);
		    labels.safe_ঠেলো (case_label);
		    যদি (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      ফেরত;
		  }
		অন্যথা যদি (! c_parser_require (parser, CPP_NAME,
					     "expected label"))
		  ফেরত;
	      }
	    অন্যথা যদি (! c_parser_require (parser, CPP_SEMICOLON,
					 "expected %<:%>"))
	      ফেরত;
	    বিরতি;
	  }
	ক্ষেত্র RID_DEFAULT:
	  {
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);
	    যদি (c_parser_পরবর্তী_token_is (parser, CPP_COLON))
	      {
		c_parser_consume_token (parser);
		যদি (c_parser_পরবর্তী_token_is (parser, CPP_NAME))
		  {
		    label = c_parser_peek_token (parser)->মান;
		    c_parser_consume_token (parser);
		    বৃক্ষ decl = lookup_label_for_goto (loc, label);
		    default_label = build_case_label (NULL_বৃক্ষ, NULL_বৃক্ষ,
						      decl);
		    যদি (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      ফেরত;
		  }
		অন্যথা যদি (! c_parser_require (parser, CPP_NAME,
					     "expected label"))
		  ফেরত;
	      }
	    অন্যথা যদি (! c_parser_require (parser, CPP_SEMICOLON,
					 "expected %<:%>"))
	      ফেরত;
	    বিরতি;
	  }
	পূর্বনির্ধারিত:
	  c_parser_error (parser, "expected case label");
	  ফেরত;
	}

    }
  যদি (! c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>"))
    ফেরত;

  যদি (cond_রাশিমালা.মান != error_mark_গ্রন্থি)
    {
      gswitch *s = gimple_build_switch (cond_রাশিমালা.মান, default_label, labels);
      gimple_seq_add_stmt_without_update (seq, s);
    }
}

/* Parse gimple return statement.  */

স্থির শূন্য
c_parser_gimple_return_stmt (gimple_parser &parser, gimple_seq *seq)
{
  location_t loc = c_parser_peek_token (parser)->location;
  gimple *ret = ফাঁকা;
  c_parser_consume_token (parser);
  যদি (c_parser_পরবর্তী_token_is (parser, CPP_SEMICOLON))
    {
      c_finish_gimple_return (loc, NULL_বৃক্ষ);
      ret = gimple_build_return (ফাঁকা);
      gimple_seq_add_stmt_without_update (seq, ret);
    }
  অন্যথা
    {
      location_t xloc = c_parser_peek_token (parser)->location;
      c_রাশিমালা রাশিমালা = c_parser_gimple_unary_expression (parser);
      যদি (রাশিমালা.মান != error_mark_গ্রন্থি)
	{
	  c_finish_gimple_return (xloc, রাশিমালা.মান);
	  ret = gimple_build_return (রাশিমালা.মান);
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
  ফেরত;
}
