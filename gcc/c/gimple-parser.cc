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

#ଅନ୍ତର୍ଭାଵ "config.h"
#ଅନ୍ତର୍ଭାଵ "system.h"
#ଅନ୍ତର୍ଭାଵ "coretypes.h"
#ଅନ୍ତର୍ଭାଵ "target.h"
#ଅନ୍ତର୍ଭାଵ "function.h"
#ଅନ୍ତର୍ଭାଵ "c-tree.h"
#ଅନ୍ତର୍ଭାଵ "timevar.h"
#ଅନ୍ତର୍ଭାଵ "stringpool.h"
#ଅନ୍ତର୍ଭାଵ "cgraph.h"
#ଅନ୍ତର୍ଭାଵ "attribs.h"
#ଅନ୍ତର୍ଭାଵ "stor-layout.h"
#ଅନ୍ତର୍ଭାଵ "varasm.h"
#ଅନ୍ତର୍ଭାଵ "trans-mem.h"
#ଅନ୍ତର୍ଭାଵ "c-family/c-pragma.h"
#ଅନ୍ତର୍ଭାଵ "c-lang.h"
#ଅନ୍ତର୍ଭାଵ "c-family/c-objc.h"
#ଅନ୍ତର୍ଭାଵ "plugin.h"
#ଅନ୍ତର୍ଭାଵ "builtins.h"
#ଅନ୍ତର୍ଭାଵ "gomp-constants.h"
#ଅନ୍ତର୍ଭାଵ "c-family/c-indentation.h"
#ଅନ୍ତର୍ଭାଵ "gimple-expr.h"
#ଅନ୍ତର୍ଭାଵ "context.h"
#ଅନ୍ତର୍ଭାଵ "gcc-rich-location.h"
#ଅନ୍ତର୍ଭାଵ "c-parser.h"
#ଅନ୍ତର୍ଭାଵ "tree-vrp.h"
#ଅନ୍ତର୍ଭାଵ "tree-pass.h"
#ଅନ୍ତର୍ଭାଵ "tree-pretty-print.h"
#ଅନ୍ତର୍ଭାଵ "tree.h"
#ଅନ୍ତର୍ଭାଵ "basic-block.h"
#ଅନ୍ତର୍ଭାଵ "gimple.h"
#ଅନ୍ତର୍ଭାଵ "gimple-pretty-print.h"
#ଅନ୍ତର୍ଭାଵ "tree-ssa.h"
#ଅନ୍ତର୍ଭାଵ "pass_manager.h"
#ଅନ୍ତର୍ଭାଵ "tree-ssanames.h"
#ଅନ୍ତର୍ଭାଵ "gimple-ssa.h"
#ଅନ୍ତର୍ଭାଵ "tree-dfa.h"
#ଅନ୍ତର୍ଭାଵ "internal-fn.h"
#ଅନ୍ତର୍ଭାଵ "cfg.h"
#ଅନ୍ତର୍ଭାଵ "cfghooks.h"
#ଅନ୍ତର୍ଭାଵ "bitmap.h"
#ଅନ୍ତର୍ଭାଵ "cfganal.h"
#ଅନ୍ତର୍ଭାଵ "tree-cfg.h"
#ଅନ୍ତର୍ଭାଵ "gimple-iterator.h"
#ଅନ୍ତର୍ଭାଵ "cfgloop.h"
#ଅନ୍ତର୍ଭାଵ "tree-phinodes.h"
#ଅନ୍ତର୍ଭାଵ "tree-into-ssa.h"


/* GIMPLE parser state.  */

ଶ୍ରେଣୀ gimple_parser
{
ସର୍ବସାଧାରଣ:
  gimple_parser (c_parser *p) : parser (p), edges(), current_bb(ଖାଲି) {}
  /* c_parser is not visible here, use composition and fake inheritance
     via a conversion operator.  */
  operator c_parser *() { ଫେରନ୍ତୁ parser; }
  c_parser *parser;

  /* CFG build state.  */
  ଶ୍ରେଣୀ gimple_parser_edge
  {
  ସର୍ବସାଧାରଣ:
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା src;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା dest;
    ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags;
    profile_probability probability;
  };
  auto_vec<gimple_parser_edge> edges;
  basic_block current_bb;

  ଶୂନ୍ୟ ଠେଲ_edge (ପୂର୍ଣ୍ଣସଂଖ୍ୟା, ପୂର୍ଣ୍ଣସଂଖ୍ୟା, ପୂର୍ଣ୍ଣସଂଖ୍ୟା, profile_probability);
};

ଶୂନ୍ୟ
gimple_parser::ଠେଲ_edge (ପୂର୍ଣ୍ଣସଂଖ୍ୟା src, ପୂର୍ଣ୍ଣସଂଖ୍ୟା dest, ପୂର୍ଣ୍ଣସଂଖ୍ୟା flags,
			  profile_probability prob)
{
  gimple_parser_edge e;
  e.src = src;
  e.dest = dest;
  e.flags = flags;
  e.probability = prob;
  edges.safe_ଠେଲ (e);
}


/* Gimple parsing functions.  */
ସ୍ଥିର ତାର୍କିକ c_parser_gimple_compound_statement (gimple_parser &, gimple_seq *);
ସ୍ଥିର ଶୂନ୍ୟ c_parser_gimple_label (gimple_parser &, gimple_seq *);
ସ୍ଥିର ଶୂନ୍ୟ c_parser_gimple_statement (gimple_parser &, gimple_seq *);
ସ୍ଥିର ସଂରଚନା c_ପଦସମଷ୍ଟି c_parser_gimple_ଦ୍ୱିମିକ_expression (gimple_parser &, ବୃକ୍ଷ);
ସ୍ଥିର ସଂରଚନା c_ପଦସମଷ୍ଟି c_parser_gimple_unary_expression (gimple_parser &);
ସ୍ଥିର ସଂରଚନା c_ପଦସମଷ୍ଟି c_parser_gimple_postfix_expression
			(gimple_parser &, ବୃକ୍ଷ = error_mark_ଗଣ୍ଠି);
ସ୍ଥିର ସଂରଚନା c_ପଦସମଷ୍ଟି c_parser_gimple_postfix_expression_after_primary
			(gimple_parser &, location_t, ସଂରଚନା c_ପଦସମଷ୍ଟି);
ସ୍ଥିର ଶୂନ୍ୟ c_parser_gimple_declaration (gimple_parser &);
ସ୍ଥିର ଶୂନ୍ୟ c_parser_gimple_goto_stmt (gimple_parser &, location_t,
				       ବୃକ୍ଷ, gimple_seq *);
ସ୍ଥିର ଶୂନ୍ୟ c_parser_gimple_try_stmt (gimple_parser &, gimple_seq *);
ସ୍ଥିର ଶୂନ୍ୟ c_parser_gimple_if_stmt (gimple_parser &, gimple_seq *);
ସ୍ଥିର ଶୂନ୍ୟ c_parser_gimple_switch_stmt (gimple_parser &, gimple_seq *);
ସ୍ଥିର ଶୂନ୍ୟ c_parser_gimple_return_stmt (gimple_parser &, gimple_seq *);
ସ୍ଥିର ଶୂନ୍ୟ c_finish_gimple_return (location_t, ବୃକ୍ଷ);
ସ୍ଥିର ବୃକ୍ଷ c_parser_gimple_paren_condition (gimple_parser &);
ସ୍ଥିର ଶୂନ୍ୟ c_parser_gimple_ପଦସମଷ୍ଟି_list (gimple_parser &, vec<ବୃକ୍ଷ> *);


/* Much like parser_build_unary_op, but avoid applying default conversions.  */

ସ୍ଥିର c_ପଦସମଷ୍ଟି
gimple_parser_build_unary_op (location_t loc,
			      ଗଣନା ବୃକ୍ଷ_code code, ସଂରଚନା c_ପଦସମଷ୍ଟି arg)
{
  ସଂରଚନା c_ପଦସମଷ୍ଟି result;

  result.original_code = code;
  result.original_type = ଖାଲି;
  result.m_decimal = 0;

  ଯଦି (reject_gcc_builtin (arg.ମୂଲ୍ୟ))
    {
      result.ମୂଲ୍ୟ = error_mark_ଗଣ୍ଠି;
    }
  ଅନ୍ୟଥା
    {
      result.ମୂଲ୍ୟ = build_unary_op (loc, code, arg.ମୂଲ୍ୟ, ସତ୍ୟ);

      ଯଦି (ବୃକ୍ଷ_OVERFLOW_P (result.ମୂଲ୍ୟ) && !ବୃକ୍ଷ_OVERFLOW_P (arg.ମୂଲ୍ୟ))
	overflow_warning (loc, result.ମୂଲ୍ୟ, arg.ମୂଲ୍ୟ);
    }

  /* We are typically called when parsing a prefix token at LOC acting on
     ARG.  Reflect this by updating the source range of the result to
     start at LOC and end at the end of ARG.  */
  set_c_ପଦସମଷ୍ଟି_source_range (&result,
			   loc, arg.get_finish ());

  ଫେରନ୍ତୁ result;
}

/* See if VAL is an identifier matching __BB<num> and return <num>
   in *INDEX.  */

ସ୍ଥିର ତାର୍କିକ
c_parser_gimple_parse_bb_spec (ବୃକ୍ଷ val, ପୂର୍ଣ୍ଣସଂଖ୍ୟା *index)
{
  ଯଦି (!startswith (IDENTIFIER_POINTER (val), "__BB"))
    ଫେରନ୍ତୁ ମିଥ୍ୟା;

  ଅଚଳ ଅକ୍ଷର *bb = IDENTIFIER_POINTER (val) + 4;
  ଯଦି (! ISDIGIT (*bb))
    ଫେରନ୍ତୁ ମିଥ୍ୟା;

  ଅକ୍ଷର *pend;
  errno = 0;
  ଅଚଳ unsigned long ସଂଖ୍ୟା = strtoul (bb, &pend, 10);
  ଯଦି (errno == ERANGE
      || *pend != '\0'
      || ସଂଖ୍ୟା > INT_MAX)
    ଫେରନ୍ତୁ ମିଥ୍ୟା;

  *index = ସଂଖ୍ୟା;
  ଫେରନ୍ତୁ ସତ୍ୟ;
}

/* See if VAL is an identifier matching __BB<num> and return <num>
   in *INDEX.  Return true if so and parse also FREQUENCY of
   the edge.  */


ସ୍ଥିର ତାର୍କିକ
c_parser_gimple_parse_bb_spec_edge_probability (ବୃକ୍ଷ val,
						gimple_parser &parser,
						ପୂର୍ଣ୍ଣସଂଖ୍ୟା *index,
						profile_probability
						*probability)
{
  ତାର୍କିକ return_p = c_parser_gimple_parse_bb_spec (val, index);
  ଯଦି (return_p)
    {
      *probability = profile_probability::uninitialized ();
      /* Parse frequency if provided.  */
      ଯଦି (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	{
	  ବୃକ୍ଷ f;
	  c_parser_consume_token (parser);
	  ଯଦି (!c_parser_next_token_is (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected frequency quality");
	      ଫେରନ୍ତୁ ମିଥ୍ୟା;
	    }

	  profile_quality quality;
	  ଅଚଳ ଅକ୍ଷର *v
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ);
	  ଯଦି (!parse_profile_quality (v, &quality))
	    {
	      c_parser_error (parser, "unknown profile quality");
	      ଫେରନ୍ତୁ ମିଥ୍ୟା;
	    }

	  c_parser_consume_token (parser);
	  ଯଦି (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    ଫେରନ୍ତୁ ମିଥ୍ୟା;

	  ଯଦି (!c_parser_next_token_is (parser, CPP_ସଂଖ୍ୟା)
	      || (ବୃକ୍ଷ_CODE (f = c_parser_peek_token (parser)->ମୂଲ୍ୟ)
		  != INTEGER_CST))
	    {
	      c_parser_error (parser, "expected frequency value");
	      ଫେରନ୍ତୁ ମିଥ୍ୟା;
	    }

	  unsigned ପୂର୍ଣ୍ଣସଂଖ୍ୟା ମୂଲ୍ୟ = ବୃକ୍ଷ_INT_CST_ତଳ (f);
	  *probability = profile_probability (ମୂଲ୍ୟ, quality);

	  c_parser_consume_token (parser);
	  ଯଦି (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    ଫେରନ୍ତୁ ମିଥ୍ୟା;

	  ଯଦି (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    ଫେରନ୍ତୁ ମିଥ୍ୟା;
	}

      ଫେରନ୍ତୁ ସତ୍ୟ;
    }

  ଫେରନ୍ତୁ ମିଥ୍ୟା;

}

/* Parse the body of a function declaration marked with "__GIMPLE".  */

ଶୂନ୍ୟ
c_parser_parse_gimple_body (c_parser *cparser, ଅକ୍ଷର *gimple_pass,
			    ଗଣନା c_declspec_il cdil,
			    profile_ଗଣନା entry_bb_ଗଣନା)
{
  gimple_parser parser (cparser);
  gimple_seq seq = ଖାଲି;
  gimple_seq body = ଖାଲି;
  ବୃକ୍ଷ stmt = ଠେଲ_stmt_list ();
  ଠେଲ_scope ();
  location_t loc1 = c_parser_peek_token (parser)->location;

  cfun->pass_startwith = gimple_pass;
  init_ବୃକ୍ଷ_ssa (cfun);

  ଯଦି (cdil == cdil_gimple)
    /* While we have SSA names in the IL we do not have a CFG built yet
       and PHIs are represented using a PHI internal function.  We do
       have lowered control flow and exception handling (well, we do not
       have parser support for EH yet).  But as we still have BINDs
       we have to go through lowering again.  */
    cfun->curr_properties = PROP_gimple_any;
  ଅନ୍ୟଥା
    {
      /* We have at least cdil_gimple_cfg.  */
      gimple_register_cfg_hooks ();
      init_empty_ବୃକ୍ଷ_cfg ();
      parser.current_bb = ENTRY_BLOCK_PTR_FOR_FN (cfun);
      /* Initialize the bare loop structure - we are going to only
         mark headers and leave the rest to fixup.  */
      set_loops_for_fn (cfun, ggc_cleared_alloc<ସଂରଚନା loops> ());
      init_loops_structure (cfun, loops_for_fn (cfun), 1);
      loops_state_set (cfun, LOOPS_NEED_FIXUP|LOOPS_MAY_HAVE_MULTIPLE_LATCHES);
      cfun->curr_properties
	|= PROP_gimple_lcf | PROP_gimple_leh | PROP_cfg | PROP_loops;
      ଯଦି (cdil == cdil_gimple_ssa)
	{
	  init_ssa_operands (cfun);
	  cfun->curr_properties |= PROP_ssa;
	}
    }

  ଯଦି (! c_parser_gimple_compound_statement (parser, &seq)
      && cdil == cdil_gimple)
    {
      gimple *ret = gimple_build_return (ଖାଲି);
      gimple_seq_add_stmt_without_update (&seq, ret);
    }

  ବୃକ୍ଷ block = କାଢ଼_scope ();
  stmt = କାଢ଼_stmt_list (stmt);
  stmt = c_build_bind_ପଦସମଷ୍ଟି (loc1, block, stmt);

  block = DECL_INITIAL (current_function_decl);
  BLOCK_SUBBLOCKS (block) = NULL_ବୃକ୍ଷ;
  BLOCK_CHAIN (block) = NULL_ବୃକ୍ଷ;
  ବୃକ୍ଷ_ASM_WRITTEN (block) = 1;

  ଯଦି (cdil == cdil_gimple)
    {
      gbind *bind_stmt = gimple_build_bind (BIND_ପଦସମଷ୍ଟି_VARS (stmt), ଖାଲି,
					    BIND_ପଦସମଷ୍ଟି_BLOCK (stmt));
      gimple_bind_set_body (bind_stmt, seq);
      gimple_seq_add_stmt_without_update (&body, bind_stmt);
      gimple_set_body (current_function_decl, body);
    }
  ଅନ୍ୟଥା
    {
      /* Control-flow and binds are lowered, record local decls.  */
      ପାଇଁ (ବୃକ୍ଷ var = BIND_ପଦସମଷ୍ଟି_VARS (stmt); var; var = DECL_CHAIN (var))
	ଯଦି (VAR_P (var)
	    && !DECL_EXTERNAL (var))
	  {
	    add_local_decl (cfun, var);
	    /* When the middle-end re-gimplifies any expression we might
	       run into the assertion that we've seen the decl in a BIND.  */
	    ଯଦି (!ବୃକ୍ଷ_STATIC (var))
	      DECL_SEEN_IN_BIND_ପଦସମଷ୍ଟି_P (var) = 1;
	  }
      /* We have a CFG.  Build the edges.  */
      ପାଇଁ (unsigned i = 0; i < parser.edges.length (); ++i)
	{
	  edge e = make_edge (BASIC_BLOCK_FOR_FN (cfun, parser.edges[i].src),
			      BASIC_BLOCK_FOR_FN (cfun, parser.edges[i].dest),
			      parser.edges[i].flags);
	  e->probability = parser.edges[i].probability;
	}
      /* Add edges for case labels.  */
      basic_block bb;
      FOR_EACH_BB_FN (bb, cfun)
	ଯଦି (EDGE_ଗଣନା (bb->succs) == 0)
	  {
	    ଯଦି (gswitch *sw = safe_dyn_cast <gswitch *> (*gsi_last_bb (bb)))
	      ପାଇଁ (unsigned i = 0; i < gimple_switch_ଅଙ୍କ_labels (sw); ++i)
		{
		  basic_block label_bb = gimple_switch_label_bb (cfun, sw, i);
		  make_edge (bb, label_bb, 0);
		}
	  }
      /* Need those for loop fixup.  */
      calculate_dominance_info (CDI_DOMINATORS);
      /* With SSA lower PHIs parsed as internal function calls and
	 update stmts.  */
      ଯଦି (cdil == cdil_gimple_ssa)
	{
	  /* Create PHI nodes, they are parsed into __PHI internal calls
	     and update SSA operands.  */
	  FOR_EACH_BB_FN (bb, cfun)
	    {
	      gimple_stmt_iterator gsi;
	      ପାଇଁ (gsi = gsi_start_bb (bb); !gsi_end_p (gsi);)
		{
		  gimple *stmt = gsi_stmt (gsi);
		  ଯଦି (!gimple_call_internal_p (stmt, IFN_PHI))
		    ଭାଙ୍ଗ;

		  gphi *phi = create_phi_ଗଣ୍ଠି (gimple_call_lhs (stmt), bb);
		  ପାଇଁ (unsigned i = 0; i < gimple_call_ଅଙ୍କ_args (stmt); i += 2)
		    {
		      ପୂର୍ଣ୍ଣସଂଖ୍ୟା srcidx = ବୃକ୍ଷ_INT_CST_ତଳ (gimple_call_arg (stmt, i));
		      edge e = find_edge (BASIC_BLOCK_FOR_FN (cfun, srcidx), bb);
		      ଯଦି (!e)
			c_parser_error (parser, "edge not found");
		      ଅନ୍ୟଥା
			add_phi_arg (phi, gimple_call_arg (stmt, i + 1), e,
				     UNKNOWN_LOCATION);
		    }
		  gsi_remove (&gsi, ସତ୍ୟ);
		}
	      ପାଇଁ (; !gsi_end_p (gsi); gsi_next (&gsi))
		update_stmt (gsi_stmt (gsi));
	    }
	  /* Fill SSA name gaps, putting them on the freelist and diagnose
	     SSA names without definition.  */
	  ପାଇଁ (unsigned i = 1; i < ଅଙ୍କ_ssa_names; ++i)
	    ଯଦି (!ssa_name (i))
	      {
		ବୃକ୍ଷ name = make_ssa_name_fn (cfun, integer_type_ଗଣ୍ଠି, ଖାଲି, i);
		release_ssa_name_fn (cfun, name);
	      }
	    ଅନ୍ୟଥା ଯଦି (!SSA_NAME_DEF_STMT (ssa_name (i)))
	      error ("SSA name %qE with version %d has no definition",
		     ssa_name (i), i);
	  /* No explicit virtual operands (yet).  */
	  bitmap_obstack_initialize (ଖାଲି);
	  update_ssa (TODO_update_ssa_only_virtuals);
	  bitmap_obstack_release (ଖାଲି);
	  /* ???  By flushing the freelist after virtual operand SSA rewrite
	     we keep the gaps available for re-use like needed for the
	     PR89595 testcase but then usually virtual operands would have
	     taken most of them.  The fix is obviously to make virtual
	     operands explicit in the SSA IL.  */
	  flush_ssaname_freelist ();
	}
      fix_loop_structure (ଖାଲି);
    }

  ଯଦି (cfun->curr_properties & PROP_cfg)
    {
      ENTRY_BLOCK_PTR_FOR_FN (cfun)->ଗଣନା_2 = entry_bb_ଗଣନା;
      gcov_type t = param_gimple_fe_computed_hot_bb_threshold;
      set_hot_bb_threshold (t);
      update_max_bb_ଗଣନା ();
      cgraph_ଗଣ୍ଠି::get_create (cfun->decl);
      cgraph_edge::rebuild_edges ();
    }

  /* Perform IL validation and if any error is found abort compilation
     of this function by zapping its body.  */
  ଯଦି ((cfun->curr_properties & PROP_cfg)
      && verify_gimple_in_cfg (cfun, ମିଥ୍ୟା, ମିଥ୍ୟା))
    init_empty_ବୃକ୍ଷ_cfg ();
  ଅନ୍ୟଥା ଯଦି (!(cfun->curr_properties & PROP_cfg)
	   && verify_gimple_in_seq (gimple_body (current_function_decl), ମିଥ୍ୟା))
    gimple_set_body (current_function_decl, ଖାଲି);

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

ସ୍ଥିର ତାର୍କିକ
c_parser_gimple_compound_statement (gimple_parser &parser, gimple_seq *seq)
{
  ତାର୍କିକ return_p = ମିଥ୍ୟା;

  ଯଦି (! c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    ଫେରନ୍ତୁ ମିଥ୍ୟା;

  /* A compound statement starts with optional declarations.  */
  ଯେତେବେଳେ (c_parser_next_tokens_start_declaration (parser))
    {
      c_parser_gimple_declaration (parser);
      ଯଦି (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	ଫେରନ୍ତୁ ମିଥ୍ୟା;
    }

  ଯେତେବେଳେ (c_parser_next_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      ଯଦି (c_parser_error (parser))
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_BRACE, ଖାଲି);
	  ଫେରନ୍ତୁ return_p;
	}
      ଅନ୍ୟଥା ଯଦି (c_parser_next_token_is (parser, CPP_EOF))
	{
	  c_parser_error (parser, "expected declaration or statement");
	  ଫେରନ୍ତୁ return_p;
	}

      ବାଛ (c_parser_peek_token (parser)->type)
	{
	ସ୍ଥିତି CPP_KEYWORD:
	  ବାଛ (c_parser_peek_token (parser)->keyword)
	    {
	    ସ୍ଥିତି RID_AT_TRY:
	      c_parser_gimple_try_stmt (parser, seq);
	      ଭାଙ୍ଗ;
	    ସ୍ଥିତି RID_IF:
	      c_parser_gimple_if_stmt (parser, seq);
	      ଭାଙ୍ଗ;
	    ସ୍ଥିତି RID_SWITCH:
	      c_parser_gimple_switch_stmt (parser, seq);
	      ଭାଙ୍ଗ;
	    ସ୍ଥିତି RID_GOTO:
	      {
		location_t loc = c_parser_peek_token (parser)->location;
		c_parser_consume_token (parser);
		ଯଦି (c_parser_next_token_is (parser, CPP_NAME))
		  {
		    ବୃକ୍ଷ label = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
		    c_parser_consume_token (parser);
		    c_parser_gimple_goto_stmt (parser, loc, label, seq);
		    ଯଦି (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      ଫେରନ୍ତୁ return_p;
		  }
		}
	      ଭାଙ୍ଗ;
	    ସ୍ଥିତି RID_RETURN:
	      return_p = ସତ୍ୟ;
	      c_parser_gimple_return_stmt (parser, seq);
	      ଯଦି (! c_parser_require (parser, CPP_SEMICOLON,
				      "expected %<;%>"))
		ଫେରନ୍ତୁ return_p;
	      ଯଦି (cfun->curr_properties & PROP_cfg)
		parser.ଠେଲ_edge (parser.current_bb->index, EXIT_BLOCK, 0,
				  profile_probability::uninitialized ());
	      ଭାଙ୍ଗ;
	    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	      ଯାଅ ପଦସମଷ୍ଟି_stmt;
	    }
	  ଭାଙ୍ଗ;
	ସ୍ଥିତି CPP_NAME:
	  ଯଦି (c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_gimple_label (parser, seq);
	      ଭାଙ୍ଗ;
	    }
	  ଯଦି (c_parser_next_token_is (parser, CPP_NAME)
	      && c_parser_peek_token (parser)->id_kind == C_ID_ID
	      && strcmp (IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ),
			 "try") == 0)
	    {
	      c_parser_gimple_try_stmt (parser, seq);
	      ଭାଙ୍ଗ;
	    }
	  /* Basic block specification.
	     __BB (index, ...)  */
	  ଯଦି ((cfun->curr_properties & PROP_cfg)
	      && !strcmp (IDENTIFIER_POINTER
			    (c_parser_peek_token (parser)->ମୂଲ୍ୟ), "__BB"))
	    {
	      c_parser_consume_token (parser);
	      ଯଦି (! c_parser_require (parser, CPP_OPEN_PAREN,
				      "expected %<(%>"))
		ଫେରନ୍ତୁ return_p;
	      ଯଦି (c_parser_next_token_is_not (parser, CPP_ସଂଖ୍ୟା))
		{
		  c_parser_error (parser, "expected block index");
		  ଫେରନ୍ତୁ return_p;
		}
	      ବୃକ୍ଷ tnum = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
	      ଯଦି (ବୃକ୍ଷ_CODE (tnum) != INTEGER_CST)
		{
		  c_parser_error (parser, "expected block index");
		  ଫେରନ୍ତୁ return_p;
		}
	      ପୂର୍ଣ୍ଣସଂଖ୍ୟା index = ବୃକ୍ଷ_INT_CST_ତଳ (tnum);
	      ଯଦି (index < ଅଙ୍କ_FIXED_BLOCKS
		  || (index < last_basic_block_for_fn (cfun)
		      && BASIC_BLOCK_FOR_FN (cfun, index) != ଖାଲି))
		{
		  c_parser_error (parser, "invalid block index");
		  ଫେରନ୍ତୁ return_p;
		}
	      ପୂର୍ଣ୍ଣସଂଖ୍ୟା is_loop_header_of = -1;
	      profile_ଗଣନା bb_ଗଣନା = profile_ଗଣନା::uninitialized ();
	      c_parser_consume_token (parser);
	      ଯେତେବେଳେ (c_parser_next_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  ଯଦି (! c_parser_next_token_is (parser, CPP_NAME))
		    {
		      c_parser_error (parser, "expected block specifier");
		      ଫେରନ୍ତୁ return_p;
		    }
		  /* loop_header (NUM)  */
		  ଯଦି (!strcmp (IDENTIFIER_POINTER
			         (c_parser_peek_token (parser)->ମୂଲ୍ୟ),
			       "loop_header"))
		    {
		      c_parser_consume_token (parser);
		      ଯଦି (! c_parser_require (parser, CPP_OPEN_PAREN,
					      "expected %<(%>"))
			ଫେରନ୍ତୁ return_p;
		      ବୃକ୍ଷ loop_ଅଙ୍କ;
		      ଯଦି (! c_parser_next_token_is (parser, CPP_ସଂଖ୍ୟା)
			  || ବୃକ୍ଷ_CODE (loop_ଅଙ୍କ
					  = c_parser_peek_token (parser)->ମୂଲ୍ୟ)
			       != INTEGER_CST)
			{
			  c_parser_error (parser, "expected loop number");
			  ଫେରନ୍ତୁ return_p;
			}
		      c_parser_consume_token (parser);
		      is_loop_header_of = ବୃକ୍ଷ_INT_CST_ତଳ (loop_ଅଙ୍କ);
		      ଯଦି (! c_parser_require (parser, CPP_CLOSE_PAREN,
					      "expected %<)%>"))
			ଫେରନ୍ତୁ return_p;
		    }
		  /* Parse profile: quality(value) */
		  ଅନ୍ୟଥା
		    {
		      ବୃକ୍ଷ q;
		      profile_quality quality;
		      ବୃକ୍ଷ v = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
		      ଯଦି (!parse_profile_quality (IDENTIFIER_POINTER (v),
						  &quality))
			{
			  c_parser_error (parser, "unknown block specifier");
			  ଫେରନ୍ତୁ ମିଥ୍ୟା;
			}

		      c_parser_consume_token (parser);
		      ଯଦି (!c_parser_require (parser, CPP_OPEN_PAREN,
					     "expected %<(%>"))
			ଫେରନ୍ତୁ ମିଥ୍ୟା;

		      ଯଦି (!c_parser_next_token_is (parser, CPP_ସଂଖ୍ୟା)
			  || (ବୃକ୍ଷ_CODE (q = c_parser_peek_token (parser)->ମୂଲ୍ୟ)
			      != INTEGER_CST))
			{
			  c_parser_error (parser, "expected count value");
			  ଫେରନ୍ତୁ ମିଥ୍ୟା;
			}

		      bb_ଗଣନା
			= profile_ଗଣନା::from_gcov_type (ବୃକ୍ଷ_INT_CST_ତଳ (q),
							 quality);
		      c_parser_consume_token (parser);
		      ଯଦି (! c_parser_require (parser, CPP_CLOSE_PAREN,
					      "expected %<)%>"))
			ଫେରନ୍ତୁ return_p;
		    }
		}
	      ଯଦି (! c_parser_require (parser, CPP_CLOSE_PAREN,
				      "expected %<)%>")
		  || ! c_parser_require (parser, CPP_COLON,
					 "expected %<:%>"))
		ଫେରନ୍ତୁ return_p;

	      /* Put stmts parsed in the current block.  */
	      ଯଦି (!gimple_seq_empty_p (*seq))
		{
		  ଯଦି (!parser.current_bb)
		    c_parser_error (parser, "stmts without block");
		  ଅନ୍ୟଥା
		    {
		      gimple_stmt_iterator gsi
			= gsi_start_bb (parser.current_bb);
		      gsi_ଭର୍ତ୍ତି_seq_after_without_update (&gsi, *seq,
							   GSI_CONTINUE_LINKING);
		    }
		  *seq = ଖାଲି;
		}

	      /* Build an empty block with specified index, linking them
		 in source order.  */
	      basic_block bb = alloc_block ();
	      bb->index = index;
	      link_block (bb, (parser.current_bb ? parser.current_bb
			       : ENTRY_BLOCK_PTR_FOR_FN (cfun)));
	      ଯଦି (basic_block_info_for_fn (cfun)->length () <= (size_t)index)
		vec_safe_grow_cleared (basic_block_info_for_fn (cfun),
				       index + 1, ସତ୍ୟ);
	      SET_BASIC_BLOCK_FOR_FN (cfun, index, bb);
	      ଯଦି (last_basic_block_for_fn (cfun) <= index)
		last_basic_block_for_fn (cfun) = index + 1;
	      n_basic_blocks_for_fn (cfun)++;
	      ଯଦି (parser.current_bb->index == ENTRY_BLOCK)
		parser.ଠେଲ_edge (ENTRY_BLOCK, bb->index, EDGE_FALLTHRU,
				  profile_probability::always ());

	      /* We leave the proper setting to fixup.  */
	      ଶ୍ରେଣୀ loop *loop_father = loops_for_fn (cfun)->ବୃକ୍ଷ_ମୂଳ;
	      /* If the new block is a loop header, allocate a loop
		 struct.  Fixup will take care of proper placement within
		 the loop tree.  */
	      ଯଦି (is_loop_header_of != -1)
		{
		  ଯଦି (ସଂଖ୍ୟା_of_loops (cfun) > (unsigned)is_loop_header_of
		      && get_loop (cfun, is_loop_header_of) != ଖାଲି)
		    {
		      c_parser_error (parser, "duplicate loop header");
		    }
		  ଅନ୍ୟଥା
		    {
		      ଶ୍ରେଣୀ loop *loop = alloc_loop ();
		      loop->ଅଙ୍କ = is_loop_header_of;
		      loop->header = bb;
		      ଯଦି (ସଂଖ୍ୟା_of_loops (cfun) <= (unsigned)is_loop_header_of)
			vec_safe_grow_cleared (loops_for_fn (cfun)->larray,
					       is_loop_header_of + 1, ସତ୍ୟ);
		      (*loops_for_fn (cfun)->larray)[is_loop_header_of] = loop;
		      flow_loop_ବୃକ୍ଷ_ଗଣ୍ଠି_add (loops_for_fn (cfun)->ବୃକ୍ଷ_ମୂଳ,
					       loop);
		    }
		  loop_father = get_loop (cfun, is_loop_header_of);
		}
	      bb->loop_father = loop_father;
	      bb->ଗଣନା_2 = bb_ଗଣନା;

	      /* Stmts now go to the new block.  */
	      parser.current_bb = bb;
	      ଭାଙ୍ଗ;
	    }
	  ଯାଅ ପଦସମଷ୍ଟି_stmt;

	ସ୍ଥିତି CPP_SEMICOLON:
	  {
	    /* Empty stmt.  */
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);
	    gimple *nop = gimple_build_nop ();
	    gimple_set_location (nop, loc);
	    gimple_seq_add_stmt_without_update (seq, nop);
	    ଭାଙ୍ଗ;
	  }

	ସ୍ଥିତି CPP_CLOSE_PAREN:
	ସ୍ଥିତି CPP_CLOSE_SQUARE:
	  /* Avoid infinite loop in error recovery:
	     c_parser_skip_until_found stops at a closing nesting
	     delimiter without consuming it, but here we need to consume
	     it to proceed further.  */
	  c_parser_error (parser, "expected statement");
	  c_parser_consume_token (parser);
	ଭାଙ୍ଗ;

	ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
ପଦସମଷ୍ଟି_stmt:
	  c_parser_gimple_statement (parser, seq);
	  ଯଦି (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	    c_parser_skip_until_found (parser, CPP_SEMICOLON, ଖାଲି);
	}
    }
  c_parser_consume_token (parser);

  /* Put stmts parsed in the current block.  */
  ଯଦି ((cfun->curr_properties & PROP_cfg)
      && !gimple_seq_empty_p (*seq))
    {
      ଯଦି (!parser.current_bb)
	c_parser_error (parser, "stmts without block");
      ଅନ୍ୟଥା
	{
	  gimple_stmt_iterator gsi = gsi_start_bb (parser.current_bb);
	  gsi_ଭର୍ତ୍ତି_seq_after_without_update (&gsi, *seq,
					       GSI_CONTINUE_LINKING);
	}
      *seq = ଖାଲି;
    }

  ଫେରନ୍ତୁ return_p;
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

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_gimple_statement (gimple_parser &parser, gimple_seq *seq)
{
  ସଂରଚନା c_ପଦସମଷ୍ଟି lhs, rhs;
  gimple *assign = ଖାଲି;
  location_t loc;
  ବୃକ୍ଷ arg = NULL_ବୃକ୍ଷ;
  auto_vec<ବୃକ୍ଷ> vargs;

  lhs = c_parser_gimple_unary_expression (parser);
  loc = ପଦସମଷ୍ଟି_LOCATION (lhs.ମୂଲ୍ୟ);
  rhs.set_error ();

  /* GIMPLE call statement without LHS.  */
  ଯଦି (c_parser_next_token_is (parser, CPP_SEMICOLON)
      && ବୃକ୍ଷ_CODE (lhs.ମୂଲ୍ୟ) == CALL_ପଦସମଷ୍ଟି)
    {
      gimple *call;
      call = gimple_build_call_from_ବୃକ୍ଷ (lhs.ମୂଲ୍ୟ, ଖାଲି);
      gimple_seq_add_stmt_without_update (seq, call);
      gimple_set_location (call, loc);
      ଫେରନ୍ତୁ;
    }

  /* All following cases are statements with LHS.  */
  ଯଦି (! c_parser_require (parser, CPP_EQ, "expected %<=%>"))
    ଫେରନ୍ତୁ;

  /* Eat and ignore {v} right after the =, the has_volatile_ops is
     redundant and re-computed by the operand scanner.  */
  ଯଦି (c_parser_next_token_is (parser, CPP_OPEN_BRACE)
      && !(c_parser_peek_token (parser)->flags & PREV_WHITE)
      && c_parser_peek_2nd_token (parser)->type == CPP_NAME
      && !(c_parser_peek_2nd_token (parser)->flags & PREV_WHITE)
      && strcmp ("v", IDENTIFIER_POINTER
			(c_parser_peek_2nd_token (parser)->ମୂଲ୍ୟ)) == 0
      && c_parser_peek_nth_token (parser, 3)->type == CPP_CLOSE_BRACE
      && !(c_parser_peek_nth_token (parser, 3)->flags & PREV_WHITE))
    {
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }

  /* Cast expression.  */
  ଯଦି (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_typename (c_parser_peek_2nd_token (parser)))
    {
      c_parser_consume_token (parser);
      ସଂରଚନା c_type_name *type_name = c_parser_type_name (parser);
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      ଯଦି (type_name == ଖାଲି)
	ଫେରନ୍ତୁ;
      /* ???  The actual type used in the cast expression is ignored as
         in GIMPLE it is encoded by the type of the LHS.  */
      rhs = c_parser_gimple_postfix_expression (parser);
      ଯଦି (lhs.ମୂଲ୍ୟ != error_mark_ଗଣ୍ଠି
	  && rhs.ମୂଲ୍ୟ != error_mark_ଗଣ୍ଠି)
	{
	  ଗଣନା ବୃକ୍ଷ_code code = NOP_ପଦସମଷ୍ଟି;
	  ଯଦି (FLOAT_TYPE_P (ବୃକ୍ଷ_TYPE (lhs.ମୂଲ୍ୟ))
	      && ! FLOAT_TYPE_P (ବୃକ୍ଷ_TYPE (rhs.ମୂଲ୍ୟ)))
	    code = FLOAT_ପଦସମଷ୍ଟି;
	  ଅନ୍ୟଥା ଯଦି (! FLOAT_TYPE_P (ବୃକ୍ଷ_TYPE (lhs.ମୂଲ୍ୟ))
		   && FLOAT_TYPE_P (ବୃକ୍ଷ_TYPE (rhs.ମୂଲ୍ୟ)))
	    code = FIX_TRUNC_ପଦସମଷ୍ଟି;
	  assign = gimple_build_assign (lhs.ମୂଲ୍ୟ, code, rhs.ମୂଲ୍ୟ);
	  gimple_seq_add_stmt_without_update (seq, assign);
	  gimple_set_location (assign, loc);
	  ଫେରନ୍ତୁ;
	}
    }

  /* Unary expression.  */
  ବାଛ (c_parser_peek_token (parser)->type)
    {
    ସ୍ଥିତି CPP_NAME:
      {
	ବୃକ୍ଷ id = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
	ଯଦି (strcmp (IDENTIFIER_POINTER (id), "__ABS") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__ABSU") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__MIN") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__MAX") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__BIT_INSERT") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__VEC_PERM") == 0)
	  ଯାଅ build_unary_ପଦସମଷ୍ଟି;
	ଭାଙ୍ଗ;
      }
    ସ୍ଥିତି CPP_KEYWORD:
      ଯଦି (c_parser_peek_token (parser)->keyword != RID_REALPART
	  && c_parser_peek_token (parser)->keyword != RID_IMAGPART)
	ଭାଙ୍ଗ;
      /* Fallthru.  */
    ସ୍ଥିତି CPP_AND:
    ସ୍ଥିତି CPP_PLUS:
    ସ୍ଥିତି CPP_MINUS:
    ସ୍ଥିତି CPP_COMPL:
    ସ୍ଥିତି CPP_NOT:
    ସ୍ଥିତି CPP_MULT: /* pointer deref */
    build_unary_ପଦସମଷ୍ଟି:
      rhs = c_parser_gimple_unary_expression (parser);
      ଯଦି (rhs.ମୂଲ୍ୟ != error_mark_ଗଣ୍ଠି)
	{
	  assign = gimple_build_assign (lhs.ମୂଲ୍ୟ, rhs.ମୂଲ୍ୟ);
	  gimple_set_location (assign, loc);
	  gimple_seq_add_stmt_without_update (seq, assign);
	}
      ଫେରନ୍ତୁ;

    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:;
    }

  /* GIMPLE PHI statement.  */
  ଯଦି (c_parser_next_token_is_keyword (parser, RID_PHI))
    {
      c_parser_consume_token (parser);

      ଯଦି (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	ଫେରନ୍ତୁ;

      ଯଦି (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	c_parser_consume_token (parser);

      ଯେତେବେଳେ (c_parser_next_token_is_not (parser, CPP_CLOSE_PAREN))
	{
	  ଯଦି (c_parser_next_token_is (parser, CPP_NAME)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      arg = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
	      c_parser_consume_token (parser);
	      ଯଦି (c_parser_next_token_is (parser, CPP_COLON))
		c_parser_consume_token (parser);
	      ପୂର୍ଣ୍ଣସଂଖ୍ୟା src_index = -1;
	      ଯଦି (!c_parser_gimple_parse_bb_spec (arg, &src_index))
		c_parser_error (parser, "invalid source block specification");
	      vargs.safe_ଠେଲ (size_int (src_index));
	    }
	  ଅନ୍ୟଥା ଯଦି (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  ଅନ୍ୟଥା
	    {
	      arg = c_parser_gimple_unary_expression (parser).ମୂଲ୍ୟ;
	      vargs.safe_ଠେଲ (arg);
	    }
	}

      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");

      /* Build internal function for PHI.  */
      gcall *call_stmt = gimple_build_call_internal_vec (IFN_PHI, vargs);
      gimple_call_set_lhs (call_stmt, lhs.ମୂଲ୍ୟ);
      gimple_set_location (call_stmt, UNKNOWN_LOCATION);
      gimple_seq_add_stmt_without_update (seq, call_stmt);
      ଫେରନ୍ତୁ;
    }

  /* GIMPLE call with lhs.  */
  ଯଦି (c_parser_next_token_is (parser, CPP_DOT)
      || (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN
	  && lookup_name (c_parser_peek_token (parser)->ମୂଲ୍ୟ)))
    {
      rhs = c_parser_gimple_unary_expression (parser);
      ଯଦି (rhs.ମୂଲ୍ୟ != error_mark_ଗଣ୍ଠି)
	{
	  gimple *call = gimple_build_call_from_ବୃକ୍ଷ (rhs.ମୂଲ୍ୟ, ଖାଲି);
	  gimple_call_set_lhs (call, lhs.ମୂଲ୍ୟ);
	  gimple_seq_add_stmt_without_update (seq, call);
	  gimple_set_location (call, loc);
	}
      ଫେରନ୍ତୁ;
    }

  rhs = c_parser_gimple_ଦ୍ୱିମିକ_expression (parser, ବୃକ୍ଷ_TYPE (lhs.ମୂଲ୍ୟ));
  ଯଦି (lhs.ମୂଲ୍ୟ != error_mark_ଗଣ୍ଠି
      && rhs.ମୂଲ୍ୟ != error_mark_ଗଣ୍ଠି)
    {
      /* If we parsed an identifier and the next token  is a '?' then parse
	 a conditional expression.  */
      ଯଦି (SSA_VAR_P (rhs.ମୂଲ୍ୟ) && c_parser_next_token_is (parser, CPP_QUERY))
	{
	  ସଂରଚନା c_ପଦସମଷ୍ଟି trueval, falseval;
	  c_parser_consume_token (parser);
	  trueval = c_parser_gimple_postfix_expression (parser);
	  falseval.set_error ();
	  ଯଦି (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    falseval = c_parser_gimple_postfix_expression (parser);
	  ଯଦି (trueval.ମୂଲ୍ୟ == error_mark_ଗଣ୍ଠି
	      || falseval.ମୂଲ୍ୟ == error_mark_ଗଣ୍ଠି)
	    ଫେରନ୍ତୁ;
	  rhs.ମୂଲ୍ୟ = build3_loc (loc,
				  VECTOR_TYPE_P (ବୃକ୍ଷ_TYPE (rhs.ମୂଲ୍ୟ))
				  ? VEC_COND_ପଦସମଷ୍ଟି : COND_ପଦସମଷ୍ଟି,
				  ବୃକ୍ଷ_TYPE (trueval.ମୂଲ୍ୟ),
				  rhs.ମୂଲ୍ୟ, trueval.ମୂଲ୍ୟ, falseval.ମୂଲ୍ୟ);
	}
      ଯଦି (get_gimple_rhs_class (ବୃକ୍ଷ_CODE (rhs.ମୂଲ୍ୟ)) == GIMPLE_INVALID_RHS)
	{
	  c_parser_error (parser, "unexpected RHS for assignment");
	  ଫେରନ୍ତୁ;
	}
      assign = gimple_build_assign (lhs.ମୂଲ୍ୟ, rhs.ମୂଲ୍ୟ);
      gimple_seq_add_stmt_without_update (seq, assign);
      gimple_set_location (assign, loc);
    }
  ଫେରନ୍ତୁ;
}

/* A mapping between an identifier to a tree code for binary operations. */
ସ୍ଥିର ଅଚଳ std::pair<ଅଚଳ ଅକ୍ଷର *, ବୃକ୍ଷ_code> gimple_ଦ୍ୱିମିକ_identifier_code[] =
  {
    {"__MULT_HIGHPART", MULT_HIGHPART_ପଦସମଷ୍ଟି},
    {"__UNLT", UNLT_ପଦସମଷ୍ଟି},
    {"__UNLE", UNLE_ପଦସମଷ୍ଟି},
    {"__UNGT", UNGT_ପଦସମଷ୍ଟି},
    {"__UNGE", UNGE_ପଦସମଷ୍ଟି},
    {"__UNEQ", UNEQ_ପଦସମଷ୍ଟି},
    {"__UNORDERED", UNORDERED_ପଦସମଷ୍ଟି},
    {"__ORDERED", ORDERED_ପଦସମଷ୍ଟି},
    {"__LTGT", LTGT_ପଦସମଷ୍ଟି},
    {"__FLOOR_DIV", FLOOR_DIV_ପଦସମଷ୍ଟି},
    {"__ROUND_DIV", ROUND_DIV_ପଦସମଷ୍ଟି},
    {"__EXACT_DIV", EXACT_DIV_ପଦସମଷ୍ଟି},
    {"__CEIL_DIV", CEIL_DIV_ପଦସମଷ୍ଟି},
    {"__FLOOR_MOD", FLOOR_MOD_ପଦସମଷ୍ଟି},
    {"__ROUND_MOD", ROUND_MOD_ପଦସମଷ୍ଟି},
    {"__CEIL_MOD", CEIL_MOD_ପଦସମଷ୍ଟି},
    {"__ROTATE_LEFT", LROTATE_ପଦସମଷ୍ଟି},
    {"__ROTATE_RIGHT", RROTATE_ପଦସମଷ୍ଟି},
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

ସ୍ଥିର c_ପଦସମଷ୍ଟି
c_parser_gimple_ଦ୍ୱିମିକ_expression (gimple_parser &parser, ବୃକ୍ଷ ret_type)
{
  /* Location of the binary operator.  */
  ସଂରଚନା c_ପଦସମଷ୍ଟି ret, lhs, rhs;
  ଗଣନା ବୃକ୍ଷ_code code = ERROR_MARK;
  ret.set_error ();
  lhs = c_parser_gimple_postfix_expression (parser, ret_type);
  ଯଦି (c_parser_error (parser))
    ଫେରନ୍ତୁ ret;
  ବାଛ (c_parser_peek_token (parser)->type)
    {
    ସ୍ଥିତି CPP_MULT:
      code = MULT_ପଦସମଷ୍ଟି;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି CPP_DIV:
      code = TRUNC_DIV_ପଦସମଷ୍ଟି;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି CPP_MOD:
      code = TRUNC_MOD_ପଦସମଷ୍ଟି;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି CPP_PLUS:
      ଯଦି (POINTER_TYPE_P (ବୃକ୍ଷ_TYPE (lhs.ମୂଲ୍ୟ)))
	code = POINTER_PLUS_ପଦସମଷ୍ଟି;
      ଅନ୍ୟଥା
	code = PLUS_ପଦସମଷ୍ଟି;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି CPP_MINUS:
      ଯଦି (POINTER_TYPE_P (ବୃକ୍ଷ_TYPE (lhs.ମୂଲ୍ୟ)))
	code = POINTER_DIFF_ପଦସମଷ୍ଟି;
      ଅନ୍ୟଥା
	code = MINUS_ପଦସମଷ୍ଟି;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି CPP_LSHIFT:
      code = LSHIFT_ପଦସମଷ୍ଟି;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି CPP_RSHIFT:
      code = RSHIFT_ପଦସମଷ୍ଟି;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି CPP_LESS:
      code = LT_ପଦସମଷ୍ଟି;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି CPP_GREATER:
      code = GT_ପଦସମଷ୍ଟି;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି CPP_LESS_EQ:
      code = LE_ପଦସମଷ୍ଟି;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି CPP_GREATER_EQ:
      code = GE_ପଦସମଷ୍ଟି;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି CPP_EQ_EQ:
      code = EQ_ପଦସମଷ୍ଟି;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି CPP_NOT_EQ:
      code = NE_ପଦସମଷ୍ଟି;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି CPP_AND:
      code = BIT_AND_ପଦସମଷ୍ଟି;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି CPP_XOR:
      code = BIT_XOR_ପଦସମଷ୍ଟି;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି CPP_OR:
      code = BIT_IOR_ପଦସମଷ୍ଟି;
      ଭାଙ୍ଗ;
    ସ୍ଥିତି CPP_AND_AND:
      c_parser_error (parser, "%<&&%> not valid in GIMPLE");
      ଫେରନ୍ତୁ ret;
    ସ୍ଥିତି CPP_OR_OR:
      c_parser_error (parser, "%<||%> not valid in GIMPLE");
      ଫେରନ୍ତୁ ret;
    ସ୍ଥିତି CPP_NAME:
      {
	ବୃକ୍ଷ id = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
	ପାଇଁ (auto &p : gimple_ଦ୍ୱିମିକ_identifier_code)
	  {
	    ଯଦି (strcmp (IDENTIFIER_POINTER (id), p.first) == 0)
	      {
		code = p.second;
		ଭାଙ୍ଗ;
	      }
	  }
	ଯଦି (code != ERROR_MARK)
	  ଭାଙ୍ଗ;
      }
      /* Fallthru.  */
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
      /* Not a binary expression.  */
      ଫେରନ୍ତୁ lhs;
    }
  location_t ret_loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  rhs = c_parser_gimple_postfix_expression (parser);
  ଯଦି (lhs.ମୂଲ୍ୟ != error_mark_ଗଣ୍ଠି && rhs.ମୂଲ୍ୟ != error_mark_ଗଣ୍ଠି)
    ret.ମୂଲ୍ୟ = build2_loc (ret_loc, code, ret_type, lhs.ମୂଲ୍ୟ, rhs.ମୂଲ୍ୟ);
  ଫେରନ୍ତୁ ret;
}

/* Parse a gimple parentized binary expression.  */

ସ୍ଥିର c_ପଦସମଷ୍ଟି
c_parser_gimple_parentized_ଦ୍ୱିମିକ_expression (gimple_parser &parser,
					      location_t op_loc,
					      ବୃକ୍ଷ_code code)
{
  ସଂରଚନା c_ପଦସମଷ୍ଟି ret;
  ret.set_error ();

  c_parser_consume_token (parser);
  ଯଦି (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    ଫେରନ୍ତୁ ret;
  c_ପଦସମଷ୍ଟି op1 = c_parser_gimple_postfix_expression (parser);
  ଯଦି (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    ଫେରନ୍ତୁ ret;
  c_ପଦସମଷ୍ଟି op2 = c_parser_gimple_postfix_expression (parser);
  ଯଦି (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    ଫେରନ୍ତୁ ret;

  ଯଦି (op1.ମୂଲ୍ୟ != error_mark_ଗଣ୍ଠି && op2.ମୂଲ୍ୟ != error_mark_ଗଣ୍ଠି)
    ret.ମୂଲ୍ୟ = build2_loc (op_loc,
			    code, ବୃକ୍ଷ_TYPE (op1.ମୂଲ୍ୟ), op1.ମୂଲ୍ୟ, op2.ମୂଲ୍ୟ);
  ଫେରନ୍ତୁ ret;
}

/* Parse a gimple parentized binary expression.  */

ସ୍ଥିର c_ପଦସମଷ୍ଟି
c_parser_gimple_parentized_ternary_expression (gimple_parser &parser,
					       location_t op_loc,
					       ବୃକ୍ଷ_code code)
{
  ସଂରଚନା c_ପଦସମଷ୍ଟି ret;
  ret.set_error ();

  c_parser_consume_token (parser);
  ଯଦି (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    ଫେରନ୍ତୁ ret;
  c_ପଦସମଷ୍ଟି op1 = c_parser_gimple_postfix_expression (parser);
  ଯଦି (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    ଫେରନ୍ତୁ ret;
  c_ପଦସମଷ୍ଟି op2 = c_parser_gimple_postfix_expression (parser);
  ଯଦି (!c_parser_require (parser, CPP_COMMA, "expected %<)%>"))
    ଫେରନ୍ତୁ ret;
  c_ପଦସମଷ୍ଟି op3 = c_parser_gimple_postfix_expression (parser);
  ଯଦି (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    ଫେରନ୍ତୁ ret;

  ଯଦି (op1.ମୂଲ୍ୟ != error_mark_ଗଣ୍ଠି
      && op2.ମୂଲ୍ୟ != error_mark_ଗଣ୍ଠି
      && op3.ମୂଲ୍ୟ != error_mark_ଗଣ୍ଠି)
    ret.ମୂଲ୍ୟ = build3_loc (op_loc,
			    code, ବୃକ୍ଷ_TYPE (op1.ମୂଲ୍ୟ),
			    op1.ମୂଲ୍ୟ, op2.ମୂଲ୍ୟ, op3.ମୂଲ୍ୟ);
  ଫେରନ୍ତୁ ret;
}

/* Parse gimple unary expression.

   gimple-unary-expression:
     gimple-postfix-expression
     unary-operator gimple-postfix-expression

   unary-operator: one of
     & * + - ~ abs_expr
*/

ସ୍ଥିର c_ପଦସମଷ୍ଟି
c_parser_gimple_unary_expression (gimple_parser &parser)
{
  ସଂରଚନା c_ପଦସମଷ୍ଟି ret, op;
  location_t op_loc = c_parser_peek_token (parser)->location;
  location_t finish;
  ret.set_error ();
  ବାଛ (c_parser_peek_token (parser)->type)
    {
    ସ୍ଥିତି CPP_AND:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      mark_exp_read (op.ମୂଲ୍ୟ);
      ଫେରନ୍ତୁ gimple_parser_build_unary_op (op_loc, ADDR_ପଦସମଷ୍ଟି, op);
    ସ୍ଥିତି CPP_MULT:
      {
	c_parser_consume_token (parser);
	op = c_parser_gimple_postfix_expression (parser);
	ଯଦି (op.ମୂଲ୍ୟ == error_mark_ଗଣ୍ଠି)
	  ଫେରନ୍ତୁ ret;
	ଯଦି (! POINTER_TYPE_P (ବୃକ୍ଷ_TYPE (op.ମୂଲ୍ୟ)))
	  {
	    error_at (op_loc, "expected pointer as argument of unary %<*%>");
	    ଫେରନ୍ତୁ ret;
	  }
	finish = op.get_finish ();
	location_t combined_loc = make_location (op_loc, op_loc, finish);
	ret.ମୂଲ୍ୟ = build_simple_mem_ref_loc (combined_loc, op.ମୂଲ୍ୟ);
	ବୃକ୍ଷ_SIDE_EFFECTS (ret.ମୂଲ୍ୟ)
	  = ବୃକ୍ଷ_THIS_VOLATILE (ret.ମୂଲ୍ୟ)
	  = TYPE_VOLATILE (ବୃକ୍ଷ_TYPE (ବୃକ୍ଷ_TYPE (op.ମୂଲ୍ୟ)));
	ret.src_range.m_start = op_loc;
	ret.src_range.m_finish = finish;
	ଫେରନ୍ତୁ ret;
      }
    ସ୍ଥିତି CPP_PLUS:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      ଫେରନ୍ତୁ gimple_parser_build_unary_op (op_loc, CONVERT_ପଦସମଷ୍ଟି, op);
    ସ୍ଥିତି CPP_MINUS:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      ଫେରନ୍ତୁ gimple_parser_build_unary_op (op_loc, NEGATE_ପଦସମଷ୍ଟି, op);
    ସ୍ଥିତି CPP_COMPL:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      ଫେରନ୍ତୁ gimple_parser_build_unary_op (op_loc, BIT_NOT_ପଦସମଷ୍ଟି, op);
    ସ୍ଥିତି CPP_NOT:
      c_parser_error (parser, "%<!%> not valid in GIMPLE");
      ଫେରନ୍ତୁ ret;
    ସ୍ଥିତି CPP_KEYWORD:
      ବାଛ (c_parser_peek_token (parser)->keyword)
	{
	ସ୍ଥିତି RID_REALPART:
	  c_parser_consume_token (parser);
	  op = c_parser_gimple_postfix_expression (parser);
	  ଫେରନ୍ତୁ gimple_parser_build_unary_op (op_loc, REALPART_ପଦସମଷ୍ଟି, op);
	ସ୍ଥିତି RID_IMAGPART:
	  c_parser_consume_token (parser);
	  op = c_parser_gimple_postfix_expression (parser);
	  ଫେରନ୍ତୁ gimple_parser_build_unary_op (op_loc, IMAGPART_ପଦସମଷ୍ଟି, op);
	ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	  ଫେରନ୍ତୁ c_parser_gimple_postfix_expression (parser);
	}
    ସ୍ଥିତି CPP_NAME:
	{
	  ବୃକ୍ଷ id = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
	  ଯଦି (strcmp (IDENTIFIER_POINTER (id), "__ABS") == 0)
	    {
	      c_parser_consume_token (parser);
	      op = c_parser_gimple_postfix_expression (parser);
	      ଫେରନ୍ତୁ gimple_parser_build_unary_op (op_loc, ABS_ପଦସମଷ୍ଟି, op);
	    }
	  ଅନ୍ୟଥା ଯଦି (strcmp (IDENTIFIER_POINTER (id), "__ABSU") == 0)
	    {
	      c_parser_consume_token (parser);
	      op = c_parser_gimple_postfix_expression (parser);
	      ଫେରନ୍ତୁ gimple_parser_build_unary_op (op_loc, ABSU_ପଦସମଷ୍ଟି, op);
	    }
	  ଅନ୍ୟଥା ଯଦି (strcmp (IDENTIFIER_POINTER (id), "__MIN") == 0)
	    ଫେରନ୍ତୁ c_parser_gimple_parentized_ଦ୍ୱିମିକ_expression (parser,
								 op_loc,
								 MIN_ପଦସମଷ୍ଟି);
	  ଅନ୍ୟଥା ଯଦି (strcmp (IDENTIFIER_POINTER (id), "__MAX") == 0)
	    ଫେରନ୍ତୁ c_parser_gimple_parentized_ଦ୍ୱିମିକ_expression (parser,
								 op_loc,
								 MAX_ପଦସମଷ୍ଟି);
	  ଅନ୍ୟଥା ଯଦି (strcmp (IDENTIFIER_POINTER (id), "__VEC_PERM") == 0)
	    ଫେରନ୍ତୁ c_parser_gimple_parentized_ternary_expression
			(parser, op_loc, VEC_PERM_ପଦସମଷ୍ଟି);
	  ଅନ୍ୟଥା ଯଦି (strcmp (IDENTIFIER_POINTER (id), "__BIT_INSERT") == 0)
	    {
	      /* __BIT_INSERT '(' postfix-expression, postfix-expression,
			          integer ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      ଯଦି (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_ପଦସମଷ୍ଟି op0 = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_ପଦସମଷ୍ଟି op1 = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_ପଦସମଷ୍ଟି op2 = c_parser_gimple_postfix_expression (parser);
		  ଯଦି (ବୃକ୍ଷ_CODE (op2.ମୂଲ୍ୟ) != INTEGER_CST
		      || !int_fits_type_p (op2.ମୂଲ୍ୟ, bitsizetype))
		    c_parser_error (parser, "expected constant offset");
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  ଯଦି (op0.ମୂଲ୍ୟ != error_mark_ଗଣ୍ଠି
		      && op1.ମୂଲ୍ୟ != error_mark_ଗଣ୍ଠି
		      && ବୃକ୍ଷ_CODE (op2.ମୂଲ୍ୟ) == INTEGER_CST)
		    ret.ମୂଲ୍ୟ = build3_loc (loc, BIT_ଭର୍ତ୍ତି_ପଦସମଷ୍ଟି,
					    ବୃକ୍ଷ_TYPE (op0.ମୂଲ୍ୟ),
					    op0.ମୂଲ୍ୟ, op1.ମୂଲ୍ୟ,
					    fold_convert (bitsizetype,
							  op2.ମୂଲ୍ୟ));
		}
	      ଫେରନ୍ତୁ ret;
	    }
	  ଅନ୍ୟଥା
	    ଫେରନ୍ତୁ c_parser_gimple_postfix_expression (parser);
	}
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
      ଫେରନ୍ତୁ c_parser_gimple_postfix_expression (parser);
    }
}

/* Decompose ID into base name (ID until ver_offset) and VERSION.  Return
   true if ID matches a SSA name.  */

ସ୍ଥିର ତାର୍କିକ
c_parser_parse_ssa_name_id (ବୃକ୍ଷ id, unsigned *version, unsigned *ver_offset)
{
  ଅଚଳ ଅକ୍ଷର *token = IDENTIFIER_POINTER (id);
  ଅଚଳ ଅକ୍ଷର *var_version = strrchr (token, '_');
  ଯଦି (! var_version)
    ଫେରନ୍ତୁ ମିଥ୍ୟା;

  *ver_offset = var_version - token;
  ପାଇଁ (ଅଚଳ ଅକ୍ଷର *p = var_version + 1; *p; ++p)
    ଯଦି (! ISDIGIT (*p))
      ଫେରନ୍ତୁ ମିଥ୍ୟା;
  *version = atoi (var_version + 1);
  ଫେରନ୍ତୁ *version > 0;
}

/* Get at the actual SSA name ID with VERSION starting at VER_OFFSET.
   TYPE is the type if the SSA name is being declared.  */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_parse_ssa_name (gimple_parser &parser,
			 ବୃକ୍ଷ id, ବୃକ୍ଷ type, unsigned version,
			 unsigned ver_offset)
{
  ବୃକ୍ଷ name = NULL_ବୃକ୍ଷ;
  ଅଚଳ ଅକ୍ଷର *token = IDENTIFIER_POINTER (id);

  ଯଦି (ver_offset == 0)
    {
      /* Anonymous unnamed SSA name.  */
      ଯଦି (version < ଅଙ୍କ_ssa_names)
	name = ssa_name (version);
      ଯଦି (! name)
	{
	  ଯଦି (! type)
	    {
	      c_parser_error (parser, "SSA name undeclared");
	      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	    }
	  name = make_ssa_name_fn (cfun, type, ଖାଲି, version);
	}
    }
  ଅନ୍ୟଥା
    {
      ଯଦି (version < ଅଙ୍କ_ssa_names)
	name = ssa_name (version);
      ଯଦି (! name)
	{
	  /* Separate var name from version.  */
	  ଅକ୍ଷର *var_name = XNEWVEC (ଅକ୍ଷର, ver_offset + 1);
	  memcpy (var_name, token, ver_offset);
	  var_name[ver_offset] = '\0';
	  /* lookup for parent decl.  */
	  id = get_identifier (var_name);
	  ବୃକ୍ଷ parent = lookup_name (id);
	  XDELETEVEC (var_name);
	  ଯଦି (! parent || parent == error_mark_ଗଣ୍ଠି)
	    {
	      c_parser_error (parser, "base variable or SSA name undeclared");
	      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	    }
	  ଯଦି (!(VAR_P (parent)
		|| ବୃକ୍ଷ_CODE (parent) == PARM_DECL
		|| ବୃକ୍ଷ_CODE (parent) == RESULT_DECL))
	    {
	      error ("invalid base %qE for SSA name", parent);
	      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
	    }
	  name = make_ssa_name_fn (cfun, parent,
				   gimple_build_nop (), version);
	}
    }

  ଫେରନ୍ତୁ name;
}

/* Parse a gimple call to an internal function.

   gimple-call-internal:
     . identifier ( gimple-argument-expression-list[opt] )  */

ସ୍ଥିର ସଂରଚନା c_ପଦସମଷ୍ଟି
c_parser_gimple_call_internal (gimple_parser &parser)
{
  ସଂରଚନା c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି;
  ପଦସମଷ୍ଟି.set_error ();

  gcc_assert (c_parser_next_token_is (parser, CPP_DOT));
  c_parser_consume_token (parser);
  location_t loc = c_parser_peek_token (parser)->location;
  ଯଦି (!c_parser_next_token_is (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_kind != C_ID_ID)
    {
      c_parser_error (parser, "expecting internal function name");
      ଫେରନ୍ତୁ ପଦସମଷ୍ଟି;
    }
  ବୃକ୍ଷ id = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
  internal_fn ifn = lookup_internal_fn (IDENTIFIER_POINTER (id));
  c_parser_consume_token (parser);
  ଯଦି (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    {
      auto_vec<ବୃକ୍ଷ> exprlist;
      ଯଦି (!c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_gimple_ପଦସମଷ୍ଟି_list (parser, &exprlist);
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      ଯଦି (ifn == IFN_LAST)
	error_at (loc, "unknown internal function %qE", id);
      ଅନ୍ୟଥା
	{
	  ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = build_call_ପଦସମଷ୍ଟି_internal_loc_array
	    (loc, ifn, void_type_ଗଣ୍ଠି, exprlist.length (),
	     exprlist.address ());
	  ପଦସମଷ୍ଟି.original_code = ERROR_MARK;
	  ପଦସମଷ୍ଟି.original_type = ଖାଲି;
	  ପଦସମଷ୍ଟି.m_decimal = 0;
	}
    }
  ଫେରନ୍ତୁ ପଦସମଷ୍ଟି;
}

/* Parse '<' type [',' alignment] '>' and return a type on success
   and NULL_TREE on error.  */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_gimple_typespec (gimple_parser &parser)
{
  ସଂରଚନା c_type_name *type_name = ଖାଲି;
  ବୃକ୍ଷ alignment = NULL_ବୃକ୍ଷ;
  ଯଦି (c_parser_require (parser, CPP_LESS, "expected %<<%>"))
    {
      type_name = c_parser_type_name (parser);
      /* Optional alignment.  */
      ଯଦି (c_parser_next_token_is (parser, CPP_COMMA))
	{
	  c_parser_consume_token (parser);
	  alignment
	      = c_parser_gimple_postfix_expression (parser).ମୂଲ୍ୟ;
	}
      c_parser_skip_until_found (parser,
				 CPP_GREATER, "expected %<>%>");
    }
  ଯଦି (!type_name)
    ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;
  ବୃକ୍ଷ tem;
  ବୃକ୍ଷ type = groktypename (type_name, &tem, ଖାଲି);
  ଯଦି (alignment)
    type = build_aligned_type (type, ବୃକ୍ଷ_to_uhwi (alignment));
  ଫେରନ୍ତୁ type;
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

ସ୍ଥିର ସଂରଚନା c_ପଦସମଷ୍ଟି
c_parser_gimple_postfix_expression (gimple_parser &parser, ବୃକ୍ଷ ret_type)
{
  location_t loc = c_parser_peek_token (parser)->location;
  source_range tok_range = c_parser_peek_token (parser)->get_range ();
  ସଂରଚନା c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି;
  ପଦସମଷ୍ଟି.set_error ();
  ବାଛ (c_parser_peek_token (parser)->type)
    {
    ସ୍ଥିତି CPP_ସଂଖ୍ୟା:
      ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
      set_c_ପଦସମଷ୍ଟି_source_range (&ପଦସମଷ୍ଟି, tok_range);
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      ଭାଙ୍ଗ;
    ସ୍ଥିତି CPP_CHAR:
    ସ୍ଥିତି CPP_CHAR16:
    ସ୍ଥିତି CPP_CHAR32:
    ସ୍ଥିତି CPP_UTF8CHAR:
    ସ୍ଥିତି CPP_WCHAR:
      ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
      set_c_ପଦସମଷ୍ଟି_source_range (&ପଦସମଷ୍ଟି, tok_range);
      c_parser_consume_token (parser);
      ଭାଙ୍ଗ;
    ସ୍ଥିତି CPP_STRING:
    ସ୍ଥିତି CPP_STRING16:
    ସ୍ଥିତି CPP_STRING32:
    ସ୍ଥିତି CPP_WSTRING:
    ସ୍ଥିତି CPP_UTF8STRING:
      ପଦସମଷ୍ଟି = c_parser_string_literal (parser, ମିଥ୍ୟା, ସତ୍ୟ);
      ଭାଙ୍ଗ;
    ସ୍ଥିତି CPP_DOT:
      ପଦସମଷ୍ଟି = c_parser_gimple_call_internal (parser);
      ଭାଙ୍ଗ;
    ସ୍ଥିତି CPP_NAME:
      ଯଦି (c_parser_peek_token (parser)->id_kind == C_ID_ID)
	{
	  ବୃକ୍ଷ id = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
	  ଯଦି (strcmp (IDENTIFIER_POINTER (id), "__MEM") == 0)
	    {
	      /* __MEM '<' type-name [ ',' number ] '>'
	               '(' [ '(' type-name ')' ] unary-expression
			   [ '+' number ]
			   [ ',' number ]
			   [ ',' number ':' number ] ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      ବୃକ୍ଷ type = c_parser_gimple_typespec (parser);
	      ସଂରଚନା c_ପଦସମଷ୍ଟି ptr, alias_off, step, index, index2;
	      ptr.ମୂଲ୍ୟ = error_mark_ଗଣ୍ଠି;
	      alias_off.ମୂଲ୍ୟ = NULL_ବୃକ୍ଷ;
	      step.ମୂଲ୍ୟ = NULL_ବୃକ୍ଷ;
	      index.ମୂଲ୍ୟ = NULL_ବୃକ୍ଷ;
	      index2.ମୂଲ୍ୟ = NULL_ବୃକ୍ଷ;
	      unsigned short clique = 0;
	      unsigned short base = 0;
	      ତାର୍କିକ reverse_order = ମିଥ୍ୟା;
	      ସଂରଚନା c_ପଦସମଷ୍ଟି ro;
	      ଯଦି (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  ବୃକ୍ଷ alias_type = NULL_ବୃକ୍ଷ;
		  /* Optional alias-type cast.  */
		  ଯଦି (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
		    {
		      c_parser_consume_token (parser);
		      ସଂରଚନା c_type_name *alias_type_name
			= c_parser_type_name (parser);
		      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
						 "expected %<)%>");
		      ଯଦି (alias_type_name)
			{
			  ବୃକ୍ଷ tem;
			  alias_type = groktypename (alias_type_name,
						     &tem, ଖାଲି);
			}
		    }
		  ptr = c_parser_gimple_unary_expression (parser);
		  ଯଦି (ptr.ମୂଲ୍ୟ == error_mark_ଗଣ୍ଠି
		      || ! POINTER_TYPE_P (ବୃକ୍ଷ_TYPE (ptr.ମୂଲ୍ୟ)))
		    {
		      ଯଦି (ptr.ମୂଲ୍ୟ != error_mark_ଗଣ୍ଠି)
			error_at (ptr.get_start (),
				  "invalid type of %<__MEM%> operand");
		      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
						 "expected %<)%>");
		      ଫେରନ୍ତୁ ପଦସମଷ୍ଟି;
		    }
		  ଯଦି (! alias_type)
		    alias_type = ବୃକ୍ଷ_TYPE (ptr.ମୂଲ୍ୟ);
		  /* Optional constant offset.  */
		  ଯଦି (c_parser_next_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      alias_off = c_parser_gimple_postfix_expression (parser);
		    }
		  ଯଦି (c_parser_next_token_is (parser, CPP_MULT))
		    {
		      std::swap (index, alias_off);
		      c_parser_consume_token (parser);
		      step = c_parser_gimple_postfix_expression (parser);
		    }
		  ଅନ୍ୟଥା ଯଦି (c_parser_next_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      index = c_parser_gimple_postfix_expression (parser);
		      ଯଦି (c_parser_next_token_is (parser, CPP_MULT))
			{
			  c_parser_consume_token (parser);
			  step = c_parser_gimple_postfix_expression (parser);
			}
		      ଅନ୍ୟଥା
			std::swap (index, index2);
		    }
		  ଅନ୍ୟଥା ଯଦି (alias_off.ମୂଲ୍ୟ
			   && ବୃକ୍ଷ_CODE (alias_off.ମୂଲ୍ୟ) != INTEGER_CST)
		    std::swap (alias_off, index2);
		  ଯଦି (c_parser_next_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      index2 = c_parser_gimple_postfix_expression (parser);
		    }
		  ଯଦି (alias_off.ମୂଲ୍ୟ)
		    {
		      ଯଦି (ବୃକ୍ଷ_CODE (alias_off.ମୂଲ୍ୟ) != INTEGER_CST)
			error_at (alias_off.get_start (),
				  "expected constant offset for %<__MEM%> "
				  "operand");
		      alias_off.ମୂଲ୍ୟ = fold_convert (alias_type,
						      alias_off.ମୂଲ୍ୟ);
		    }
		  ଅନ୍ୟଥା
		    alias_off.ମୂଲ୍ୟ = build_int_cst (alias_type, 0);
		  ଯଦି (step.ମୂଲ୍ୟ)
		    {
		      ଯଦି (ବୃକ୍ଷ_CODE (step.ମୂଲ୍ୟ) != INTEGER_CST)
			error_at (step.get_start (),
				  "expected constant step for %<__MEM%> "
				  "operand");
		    }
		  ଯଦି (c_parser_next_token_is (parser, CPP_COMMA))
		    {
		      ସଂରଚନା c_ପଦସମଷ୍ଟି cl, ba;
		      ତାର୍କିକ has_clb = ସତ୍ୟ;
		      c_parser_consume_token (parser);
		      cl = c_parser_gimple_postfix_expression (parser);
		      ଯଦି (!c_parser_next_token_is (parser, CPP_COLON))
			{
			  ro = cl;
			  unsigned HOST_WIDE_INT tmp = 0;
			  ଯଦି (!ବୃକ୍ଷ_fits_uhwi_p (ro.ମୂଲ୍ୟ)
			      || (tmp = ବୃକ୍ଷ_to_uhwi (ro.ମୂଲ୍ୟ)) > 1)
			    error_at (ro.get_start (),
				      "invalid reverse order value");
			  reverse_order = tmp;
			  has_clb = ମିଥ୍ୟା;
			  ଯଦି (c_parser_next_token_is (parser, CPP_COMMA))
			    {
			      c_parser_consume_token (parser);
			      cl = c_parser_gimple_postfix_expression (parser);
		              has_clb = ସତ୍ୟ;
			    }
			}
		      ଯଦି (has_clb
			  && c_parser_require (parser,
					       CPP_COLON, "expected %<:%>"))
			{
			  ba = c_parser_gimple_postfix_expression (parser);
			  ଯଦି (!ବୃକ୍ଷ_fits_uhwi_p (cl.ମୂଲ୍ୟ)
			      || !ବୃକ୍ଷ_fits_uhwi_p (ba.ମୂଲ୍ୟ)
			      || compare_ବୃକ୍ଷ_int (cl.ମୂଲ୍ୟ,
						   (clique = ବୃକ୍ଷ_to_uhwi
								(cl.ମୂଲ୍ୟ)))
			      || compare_ବୃକ୍ଷ_int (ba.ମୂଲ୍ୟ,
						   (base = ବୃକ୍ଷ_to_uhwi
								 (ba.ମୂଲ୍ୟ))))
			    error_at (cl.get_start (),
				      "invalid clique/base pair");
			}
		    }
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      ଯଦି (! type || c_parser_error (parser))
		{
		  c_parser_set_error (parser, ମିଥ୍ୟା);
		  ଫେରନ୍ତୁ ପଦସମଷ୍ଟି;
		}
	      ଯଦି (index.ମୂଲ୍ୟ || step.ମୂଲ୍ୟ || index2.ମୂଲ୍ୟ)
		ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = build5_loc (loc, TARGET_MEM_REF,
					 type, ptr.ମୂଲ୍ୟ, alias_off.ମୂଲ୍ୟ,
					 index.ମୂଲ୍ୟ, step.ମୂଲ୍ୟ, index2.ମୂଲ୍ୟ);
	      ଅନ୍ୟଥା
		ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = build2_loc (loc, MEM_REF,
					 type, ptr.ମୂଲ୍ୟ, alias_off.ମୂଲ୍ୟ);
	      ଯଦି (clique != 0)
		{
		  cfun->last_clique = MAX (cfun->last_clique, clique);
		  MR_DEPENDENCE_CLIQUE (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ) = clique;
		  MR_DEPENDENCE_BASE (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ) = base;
		}
	      ଯଦି (reverse_order)
		{
		  ଯଦି (ବୃକ୍ଷ_CODE (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ) == MEM_REF)
		    REF_REVERSE_STORAGE_ORDER (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ) = reverse_order;
		  ଅନ୍ୟଥା
		    error_at (ro.get_start (),
			      "target mem ref cannot have reverse order");
		}
	      ଭାଙ୍ଗ;
	    }
	  ଅନ୍ୟଥା ଯଦି (strcmp (IDENTIFIER_POINTER (id), "__VIEW_CONVERT") == 0)
	    {
	      /* __VIEW_CONVERT '<' type-name [ ',' number ] '>'
	                        '(' postfix-expression ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      ବୃକ୍ଷ type = c_parser_gimple_typespec (parser);
	      ଯଦି (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_ପଦସମଷ୍ଟି op = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  ଯଦି (type && op.ମୂଲ୍ୟ != error_mark_ଗଣ୍ଠି)
		    ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = build1_loc (loc, VIEW_CONVERT_ପଦସମଷ୍ଟି,
					     type, op.ମୂଲ୍ୟ);
		}
	      ଭାଙ୍ଗ;
	    }
	  ଅନ୍ୟଥା ଯଦି (strcmp (IDENTIFIER_POINTER (id), "__BIT_FIELD_REF") == 0)
	    {
	      /* __BIT_FIELD_REF '<' type-name [ ',' number ] '>'
	                        '(' postfix-expression, integer, integer ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      ବୃକ୍ଷ type = c_parser_gimple_typespec (parser);
	      ଯଦି (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_ପଦସମଷ୍ଟି op0 = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_ପଦସମଷ୍ଟି op1 = c_parser_gimple_postfix_expression (parser);
		  ଯଦି (ବୃକ୍ଷ_CODE (op1.ମୂଲ୍ୟ) != INTEGER_CST
		      || !int_fits_type_p (op1.ମୂଲ୍ୟ, bitsizetype))
		    c_parser_error (parser, "expected constant size");
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_ପଦସମଷ୍ଟି op2 = c_parser_gimple_postfix_expression (parser);
		  ଯଦି (ବୃକ୍ଷ_CODE (op2.ମୂଲ୍ୟ) != INTEGER_CST
		      || !int_fits_type_p (op2.ମୂଲ୍ୟ, bitsizetype))
		    c_parser_error (parser, "expected constant offset");
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  ଯଦି (type
		      && op0.ମୂଲ୍ୟ != error_mark_ଗଣ୍ଠି
		      && ବୃକ୍ଷ_CODE (op1.ମୂଲ୍ୟ) == INTEGER_CST
		      && ବୃକ୍ଷ_CODE (op2.ମୂଲ୍ୟ) == INTEGER_CST)
		    ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = build3_loc (loc, BIT_FIELD_REF, type,
					     op0.ମୂଲ୍ୟ,
					     fold_convert (bitsizetype,
							   op1.ମୂଲ୍ୟ),
					     fold_convert (bitsizetype,
							   op2.ମୂଲ୍ୟ));
		}
	      ଭାଙ୍ଗ;
	    }
	  ଅନ୍ୟଥା ଯଦି (strcmp (IDENTIFIER_POINTER (id), "__CLOBBER") == 0)
	    {
	      /* __CLOBBER [ '(' bob | eob | bos | eos ')' ]  */
	      clobber_kind kind = CLOBBER_UNDEF;
	      c_parser_consume_token (parser);
	      ଯଦି (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
		{
		  c_parser_consume_token (parser);
		  auto tok = c_parser_peek_token (parser);
		  ଯଦି (c_parser_require (parser, CPP_NAME,
					"expected clobber kind"))
		    {
		      ଅଚଳ ଅକ୍ଷର *kind_str = IDENTIFIER_POINTER (tok->ମୂଲ୍ୟ);
		      ଯଦି (strcmp (kind_str, "bos") == 0)
			kind = CLOBBER_STORAGE_BEGIN;
		      ଅନ୍ୟଥା ଯଦି (strcmp (kind_str, "bob") == 0)
			kind = CLOBBER_OBJECT_BEGIN;
		      ଅନ୍ୟଥା ଯଦି (strcmp (kind_str, "eob") == 0)
			kind = CLOBBER_OBJECT_END;
		      ଅନ୍ୟଥା ଯଦି (strcmp (kind_str, "eos") == 0)
			kind = CLOBBER_STORAGE_END;
		      ଅନ୍ୟଥା
			c_parser_error (parser, "expected one of %<bos%>, "
					"%<eos%>, %<bob>, %<eob%>");
		    }
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      /* We infer the (redundant) type from the LHS.  */
	      ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = build_clobber (ret_type, kind);
	      ଭାଙ୍ଗ;
	    }
	  ଅନ୍ୟଥା ଯଦି (strcmp (IDENTIFIER_POINTER (id), "_Literal") == 0)
	    {
	      /* _Literal '(' type-name ')' ( [ '-' ] constant | constructor ) */
	      c_parser_consume_token (parser);
	      ବୃକ୍ଷ type = NULL_ବୃକ୍ଷ;
	      ଯଦି (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  ସଂରଚନା c_type_name *type_name = c_parser_type_name (parser);
		  ବୃକ୍ଷ tem;
		  ଯଦି (type_name)
		    type = groktypename (type_name, &tem, ଖାଲି);
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      ଯଦି (! type)
		{
		  c_parser_error (parser, "invalid _Literal");
		  ଫେରନ୍ତୁ ପଦସମଷ୍ଟି;
		}
	      ଯଦି (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
		{
		  c_parser_consume_token (parser);
		  ଯଦି (!AGGREGATE_TYPE_P (type)
		      && !VECTOR_TYPE_P (type))
		    {
		      c_parser_error (parser, "invalid type for _Literal with "
				      "constructor");
		      c_parser_skip_until_found (parser, CPP_CLOSE_BRACE,
						 "expected %<}%>");
		      ଫେରନ୍ତୁ ପଦସମଷ୍ଟି;
		    }
		  vec<constructor_elt, va_gc> *v = ଖାଲି;
		  ତାର୍କିକ constant_p = ସତ୍ୟ;
		  ଯଦି (VECTOR_TYPE_P (type)
		      && !c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
		    {
		      vec_alloc (v, TYPE_VECTOR_SUBPARTS (type).to_constant ());
		      କର
			{
			  ବୃକ୍ଷ val
			    = c_parser_gimple_postfix_expression (parser).ମୂଲ୍ୟ;
			  ଯଦି (! val
			      || val == error_mark_ଗଣ୍ଠି
			      || (! CONSTANT_CLASS_P (val)
				  && ! SSA_VAR_P (val)))
			    {
			      c_parser_error (parser, "invalid _Literal");
			      ଫେରନ୍ତୁ ପଦସମଷ୍ଟି;
			    }
			  CONSTRUCTOR_APPEND_ELT (v, NULL_ବୃକ୍ଷ, val);
			  ଯଦି (! CONSTANT_CLASS_P (val))
			    constant_p = ମିଥ୍ୟା;
			  ଯଦି (c_parser_next_token_is (parser, CPP_COMMA))
			    c_parser_consume_token (parser);
			  ଅନ୍ୟଥା
			    ଭାଙ୍ଗ;
			}
		      ଯେତେବେଳେ (1);
		    }
		  ଯଦି (c_parser_require (parser, CPP_CLOSE_BRACE,
					"expected %<}%>"))
		    {
		      ଯଦି (v && constant_p)
			ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = build_vector_from_ctor (type, v);
		      ଅନ୍ୟଥା
			ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = build_constructor (type, v);
		    }
		  ଅନ୍ୟଥା
		    {
		      c_parser_skip_until_found (parser, CPP_CLOSE_BRACE,
						 "expected %<}%>");
		      ଫେରନ୍ତୁ ପଦସମଷ୍ଟି;
		    }
		}
	      ଅନ୍ୟଥା
		{
		  ତାର୍କିକ neg_p, addr_p;
		  ଯଦି ((neg_p = c_parser_next_token_is (parser, CPP_MINUS)))
		    c_parser_consume_token (parser);
		  ଯଦି ((addr_p = c_parser_next_token_is (parser, CPP_AND)))
		    c_parser_consume_token (parser);
		  ବୃକ୍ଷ val = c_parser_gimple_postfix_expression (parser).ମୂଲ୍ୟ;
		  ଯଦି (! val
		      || val == error_mark_ଗଣ୍ଠି
		      || (!CONSTANT_CLASS_P (val) && !addr_p))
		    {
		      c_parser_error (parser, "invalid _Literal");
		      ଫେରନ୍ତୁ ପଦସମଷ୍ଟି;
		    }
		  ଯଦି (addr_p)
		    {
		      val = build1 (ADDR_ପଦସମଷ୍ଟି, type, val);
		      ଯଦି (!is_gimple_invariant_address (val))
			{
			  c_parser_error (parser, "invalid _Literal");
			  ଫେରନ୍ତୁ ପଦସମଷ୍ଟି;
			}
		    }
		  ଯଦି (neg_p)
		    {
		      val = const_unop (NEGATE_ପଦସମଷ୍ଟି, ବୃକ୍ଷ_TYPE (val), val);
		      ଯଦି (! val)
			{
			  c_parser_error (parser, "invalid _Literal");
			  ଫେରନ୍ତୁ ପଦସମଷ୍ଟି;
			}
		    }
		  ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = fold_convert (type, val);
		}
	      ଫେରନ୍ତୁ ପଦସମଷ୍ଟି;
	    }

	  /* SSA name.  */
	  unsigned version, ver_offset;
	  ଯଦି (! lookup_name (id)
	      && c_parser_parse_ssa_name_id (id, &version, &ver_offset))
	    {
	      c_parser_consume_token (parser);
	      ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = c_parser_parse_ssa_name (parser, id, NULL_ବୃକ୍ଷ,
						    version, ver_offset);
	      ଯଦି (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ == error_mark_ଗଣ୍ଠି)
		ଫେରନ୍ତୁ ପଦସମଷ୍ଟି;
	      set_c_ପଦସମଷ୍ଟି_source_range (&ପଦସମଷ୍ଟି, tok_range);
	      /* For default definition SSA names.  */
	      ଯଦି (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
		  && c_parser_peek_2nd_token (parser)->type == CPP_NAME
		  && strcmp ("D",
			     IDENTIFIER_POINTER
			       (c_parser_peek_2nd_token (parser)->ମୂଲ୍ୟ)) == 0
		  && c_parser_peek_nth_token (parser, 3)->type == CPP_CLOSE_PAREN)
		{
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		  ଯଦି (! SSA_NAME_IS_DEFAULT_DEF (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ))
		    {
		      ଯଦି (!SSA_NAME_VAR (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ))
			{
			  error_at (loc, "anonymous SSA name cannot have"
				    " default definition");
			  ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = error_mark_ଗଣ୍ଠି;
			  ଫେରନ୍ତୁ ପଦସମଷ୍ଟି;
			}
		      set_ssa_default_def (cfun, SSA_NAME_VAR (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ),
					   ପଦସମଷ୍ଟି.ମୂଲ୍ୟ);
		      SSA_NAME_DEF_STMT (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ) = gimple_build_nop ();
		    }
		}
	    }
	  ଅନ୍ୟଥା
	    {
	      c_parser_consume_token (parser);
	      ପଦସମଷ୍ଟି.ମୂଲ୍ୟ
		= build_external_ref (loc, id,
				      (c_parser_peek_token (parser)->type
				       == CPP_OPEN_PAREN), &ପଦସମଷ୍ଟି.original_type);
	      set_c_ପଦସମଷ୍ଟି_source_range (&ପଦସମଷ୍ଟି, tok_range);
	    }
	  ଭାଙ୍ଗ;
	}
      /* Fallthru.  */
    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
      c_parser_error (parser, "expected expression");
      ପଦସମଷ୍ଟି.set_error ();
      ଭାଙ୍ଗ;
    }
  ଯଦି (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ == error_mark_ଗଣ୍ଠି)
    ଫେରନ୍ତୁ ପଦସମଷ୍ଟି;
  ଫେରନ୍ତୁ c_parser_gimple_postfix_expression_after_primary
    (parser, ପଦସମଷ୍ଟି_LOC_OR_LOC (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ, loc), ପଦସମଷ୍ଟି);
}

/* Parse a gimple postfix expression after the initial primary or compound
   literal.  */

ସ୍ଥିର ସଂରଚନା c_ପଦସମଷ୍ଟି
c_parser_gimple_postfix_expression_after_primary (gimple_parser &parser,
						  location_t ପଦସମଷ୍ଟି_loc,
						  ସଂରଚନା c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି)
{
  location_t start;
  location_t finish;
  ବୃକ୍ଷ ident;
  location_t comp_loc;

  ଯେତେବେଳେ (ସତ୍ୟ)
    {
      location_t op_loc = c_parser_peek_token (parser)->location;
      ବାଛ (c_parser_peek_token (parser)->type)
	{
	ସ୍ଥିତି CPP_OPEN_SQUARE:
	  {
	    c_parser_consume_token (parser);
	    ବୃକ୍ଷ idx = c_parser_gimple_unary_expression (parser).ମୂଲ୍ୟ;

	    ଯଦି (! c_parser_require (parser, CPP_CLOSE_SQUARE, "expected %<]%>"))
	      {
		c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE, ଖାଲି);
		ଭାଙ୍ଗ;
	      }

	    start = ପଦସମଷ୍ଟି.get_start ();
	    finish = c_parser_tokens_buf (parser, 0)->location;
	    ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = build_array_ref (op_loc, ପଦସମଷ୍ଟି.ମୂଲ୍ୟ, idx);
	    set_c_ପଦସମଷ୍ଟି_source_range (&ପଦସମଷ୍ଟି, start, finish);
	    ପଦସମଷ୍ଟି.m_decimal = 0;

	    ପଦସମଷ୍ଟି.original_code = ERROR_MARK;
	    ପଦସମଷ୍ଟି.original_type = ଖାଲି;
	    ଭାଙ୍ଗ;
	  }
	ସ୍ଥିତି CPP_OPEN_PAREN:
	  {
	    /* Function call.  */
	    c_parser_consume_token (parser);
	    auto_vec<ବୃକ୍ଷ> exprlist;
	    ଯଦି (! c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	      c_parser_gimple_ପଦସମଷ୍ଟି_list (parser, &exprlist);
	    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    ଯଦି (!FUNC_OR_METHOD_TYPE_P (ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ)))
	      {
		c_parser_error (parser, "invalid call to non-function");
		ପଦସମଷ୍ଟି.set_error ();
		ଭାଙ୍ଗ;
	      }
	    ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = build_call_array_loc
		(ପଦସମଷ୍ଟି_loc, ବୃକ୍ଷ_TYPE (ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ)),
		 ପଦସମଷ୍ଟି.ମୂଲ୍ୟ, exprlist.length (), exprlist.address ());
	    ପଦସମଷ୍ଟି.m_decimal = 0;
	    ପଦସମଷ୍ଟି.original_code = ERROR_MARK;
	    ପଦସମଷ୍ଟି.original_type = ଖାଲି;
	    ଭାଙ୍ଗ;
	  }
	ସ୍ଥିତି CPP_DOT:
	  {
	    /* Structure element reference.  */
	    c_parser_consume_token (parser);
	    ଯଦି (c_parser_next_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		ident = comp_tok->ମୂଲ୍ୟ;
		comp_loc = comp_tok->location;
	      }
	    ଅନ୍ୟଥା
	      {
		c_parser_error (parser, "expected identifier");
		ପଦସମଷ୍ଟି.set_error ();
		ପଦସମଷ୍ଟି.original_code = ERROR_MARK;
		ପଦସମଷ୍ଟି.original_type = ଖାଲି;
		ଫେରନ୍ତୁ ପଦସମଷ୍ଟି;
	      }
	    start = ପଦସମଷ୍ଟି.get_start ();
	    finish = c_parser_peek_token (parser)->get_finish ();
	    c_parser_consume_token (parser);
	    ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = build_component_ref (op_loc, ପଦସମଷ୍ଟି.ମୂଲ୍ୟ, ident,
					      comp_loc, UNKNOWN_LOCATION);
	    set_c_ପଦସମଷ୍ଟି_source_range (&ପଦସମଷ୍ଟି, start, finish);
	    ପଦସମଷ୍ଟି.m_decimal = 0;
	    ପଦସମଷ୍ଟି.original_code = ERROR_MARK;
	    ଯଦି (ବୃକ୍ଷ_CODE (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ) != COMPONENT_REF)
	      ପଦସମଷ୍ଟି.original_type = ଖାଲି;
	    ଅନ୍ୟଥା
	      {
		/* Remember the original type of a bitfield.  */
		ବୃକ୍ଷ field = ବୃକ୍ଷ_OPERAND (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ, 1);
		ଯଦି (ବୃକ୍ଷ_CODE (field) != FIELD_DECL)
		  ପଦସମଷ୍ଟି.original_type = ଖାଲି;
		ଅନ୍ୟଥା
		  ପଦସମଷ୍ଟି.original_type = DECL_BIT_FIELD_TYPE (field);
	      }
	    ଭାଙ୍ଗ;
	  }
	ସ୍ଥିତି CPP_DEREF:
	  {
	    /* Structure element reference.  */
	    ଯଦି (!POINTER_TYPE_P (ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ)))
	      {
		c_parser_error (parser, "dereference of non-pointer");
		ପଦସମଷ୍ଟି.set_error ();
		ପଦସମଷ୍ଟି.original_code = ERROR_MARK;
		ପଦସମଷ୍ଟି.original_type = ଖାଲି;
		ଫେରନ୍ତୁ ପଦସମଷ୍ଟି;
	      }
	    c_parser_consume_token (parser);
	    ଯଦି (c_parser_next_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		ident = comp_tok->ମୂଲ୍ୟ;
		comp_loc = comp_tok->location;
	      }
	    ଅନ୍ୟଥା
	      {
		c_parser_error (parser, "expected identifier");
		ପଦସମଷ୍ଟି.set_error ();
		ପଦସମଷ୍ଟି.original_code = ERROR_MARK;
		ପଦସମଷ୍ଟି.original_type = ଖାଲି;
		ଫେରନ୍ତୁ ପଦସମଷ୍ଟି;
	      }
	    start = ପଦସମଷ୍ଟି.get_start ();
	    finish = c_parser_peek_token (parser)->get_finish ();
	    c_parser_consume_token (parser);
	    ପଦସମଷ୍ଟି.ମୂଲ୍ୟ = build_component_ref (op_loc,
					      build_simple_mem_ref_loc
					        (op_loc, ପଦସମଷ୍ଟି.ମୂଲ୍ୟ),
					      ident, comp_loc,
					      ପଦସମଷ୍ଟି.get_location ());
	    set_c_ପଦସମଷ୍ଟି_source_range (&ପଦସମଷ୍ଟି, start, finish);
	    ପଦସମଷ୍ଟି.m_decimal = 0;
	    ପଦସମଷ୍ଟି.original_code = ERROR_MARK;
	    ଯଦି (ବୃକ୍ଷ_CODE (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ) != COMPONENT_REF)
	      ପଦସମଷ୍ଟି.original_type = ଖାଲି;
	    ଅନ୍ୟଥା
	      {
		/* Remember the original type of a bitfield.  */
		ବୃକ୍ଷ field = ବୃକ୍ଷ_OPERAND (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ, 1);
		ଯଦି (ବୃକ୍ଷ_CODE (field) != FIELD_DECL)
		  ପଦସମଷ୍ଟି.original_type = ଖାଲି;
		ଅନ୍ୟଥା
		  ପଦସମଷ୍ଟି.original_type = DECL_BIT_FIELD_TYPE (field);
	      }
	    ଭାଙ୍ଗ;
	  }
	ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	  ଫେରନ୍ତୁ ପଦସମଷ୍ଟି;
	}
    }
}

/* Parse expression list.

   gimple-expr-list:
     gimple-unary-expression
     gimple-expr-list , gimple-unary-expression

 */

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_gimple_ପଦସମଷ୍ଟି_list (gimple_parser &parser, vec<ବୃକ୍ଷ> *ret)
{
  ସଂରଚନା c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି;

  ପଦସମଷ୍ଟି = c_parser_gimple_unary_expression (parser);
  ret->safe_ଠେଲ (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ);
  ଯେତେବେଳେ (c_parser_next_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      ପଦସମଷ୍ଟି = c_parser_gimple_unary_expression (parser);
      ret->safe_ଠେଲ (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ);
    }
}

/* Parse gimple label.

   gimple-label:
     identifier :
     case constant-expression :
     default :

*/

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_gimple_label (gimple_parser &parser, gimple_seq *seq)
{
  ବୃକ୍ଷ name = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
  location_t loc1 = c_parser_peek_token (parser)->location;
  gcc_assert (c_parser_next_token_is (parser, CPP_NAME));
  c_parser_consume_token (parser);
  gcc_assert (c_parser_next_token_is (parser, CPP_COLON));
  c_parser_consume_token (parser);
  ବୃକ୍ଷ label = define_label (loc1, name);
  ଯଦି (label)
    gimple_seq_add_stmt_without_update (seq, gimple_build_label (label));
  ଫେରନ୍ତୁ;
}

/* Parse gimple/RTL pass list.

   gimple-or-rtl-pass-list:
     startwith("pass-name")[,{cfg,ssa}]
 */

ଶୂନ୍ୟ
c_parser_gimple_or_rtl_pass_list (c_parser *parser, c_declspecs *specs)
{
  ଅକ୍ଷର *pass = ଖାଲି;

  /* Accept __GIMPLE/__RTL.  */
  ଯଦି (c_parser_next_token_is_not (parser, CPP_OPEN_PAREN))
    ଫେରନ୍ତୁ;
  c_parser_consume_token (parser);

  specs->entry_bb_ଗଣନା = profile_ଗଣନା::uninitialized ();
  ଯେତେବେଳେ (c_parser_next_token_is (parser, CPP_NAME))
    {
      profile_quality quality;
      ଅଚଳ ଅକ୍ଷର *op = IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ);
      c_parser_consume_token (parser);
      ଯଦି (! strcmp (op, "startwith"))
	{
	  ଯଦି (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    ଫେରନ୍ତୁ;
	  ଯଦି (c_parser_next_token_is_not (parser, CPP_STRING))
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"expected pass name");
	      ଫେରନ୍ତୁ;
	    }
	  pass = xstrdup (ବୃକ୍ଷ_STRING_POINTER
			  (c_parser_string_literal (parser, ମିଥ୍ୟା,
						    ମିଥ୍ୟା).ମୂଲ୍ୟ));
	  ଯଦି (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<(%>"))
	    ଫେରନ୍ତୁ;
	}
      ଅନ୍ୟଥା ଯଦି (parse_profile_quality (op, &quality))
	{
	  ବୃକ୍ଷ q;
	  ଯଦି (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    ଫେରନ୍ତୁ;

	  ଯଦି (!c_parser_next_token_is (parser, CPP_ସଂଖ୍ୟା)
	      || (ବୃକ୍ଷ_CODE (q = c_parser_peek_token (parser)->ମୂଲ୍ୟ)
		  != INTEGER_CST))
	    {
	      c_parser_error (parser, "expected count value");
	      ଫେରନ୍ତୁ;
	    }

	  specs->entry_bb_ଗଣନା
	    = profile_ଗଣନା::from_gcov_type (ବୃକ୍ଷ_INT_CST_ତଳ (q), quality);
	  c_parser_consume_token (parser);
	  ଯଦି (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    ଫେରନ୍ତୁ;
	}
      ଅନ୍ୟଥା ଯଦି (specs->declspec_il != cdil_gimple)
	/* Allow only one IL specifier and none on RTL.  */
	;
      ଅନ୍ୟଥା ଯଦି (! strcmp (op, "cfg"))
	specs->declspec_il = cdil_gimple_cfg;
      ଅନ୍ୟଥା ଯଦି (! strcmp (op, "ssa"))
	specs->declspec_il = cdil_gimple_ssa;
      ଅନ୍ୟଥା
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "invalid operation");
	  ଫେରନ୍ତୁ;
	}
     ଯଦି (c_parser_next_token_is (parser, CPP_COMMA))
       c_parser_consume_token (parser);
    }

  ଯଦି (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    ଫେରନ୍ତୁ;

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

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_gimple_declaration (gimple_parser &parser)
{
  ସଂରଚନା c_declarator *declarator;
  ସଂରଚନା c_declspecs *specs = build_null_declspecs ();
  c_parser_declspecs (parser, specs, ସତ୍ୟ, ସତ୍ୟ, ସତ୍ୟ,
		      ସତ୍ୟ, ସତ୍ୟ, ସତ୍ୟ, ସତ୍ୟ, cla_nonabstract_decl);
  finish_declspecs (specs);

  /* Provide better error recovery.  Note that a type name here is usually
     better diagnosed as a redeclaration.  */
  ଯଦି (c_parser_next_token_starts_declspecs (parser)
      && ! c_parser_next_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<;%>");
      c_parser_set_error (parser, ମିଥ୍ୟା);
      ଫେରନ୍ତୁ;
    }

  ତାର୍କିକ dummy = ମିଥ୍ୟା;
  declarator = c_parser_declarator (parser,
				    specs->typespec_kind != ctsk_none,
				    C_DTR_NORMAL, &dummy);

  ଯଦି (!c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_error (parser, "expected %<;%>");
      ଫେରନ୍ତୁ;
    }
  ଯଦି (declarator)
    {
      /* Handle SSA name decls specially, they do not go into the identifier
         table but we simply build the SSA name for later lookup.  */
      unsigned version, ver_offset;
      /* Handle SSA pointer declarations in a very simplistic ways, we
	 probably would like to call grokdeclarator in a special mode to
	 just build the type of the decl - start_decl already pushes
	 the identifier to the bindings for lookup, something we do not
	 want.  */
      ସଂରଚନା c_declarator *id_declarator = declarator;
      ଯେତେବେଳେ (id_declarator->kind == cdk_pointer)
	id_declarator = id_declarator->declarator;
      ଯଦି (id_declarator->kind == cdk_id
	  && (declarator->kind == cdk_pointer
	      || is_gimple_reg_type (specs->type))
	  && c_parser_parse_ssa_name_id (id_declarator->u.id.id,
					 &version, &ver_offset)
	  /* The following restricts it to unnamed anonymous SSA names
	     which fails parsing of named ones in dumps (we could
	     decide to not dump their name for -gimple).  */
	  && ver_offset == 0)
	{
	  ସଂରଚନା c_declarator *p = declarator;
	  ବୃକ୍ଷ type = specs->type;
	  ଯେତେବେଳେ (p->kind == cdk_pointer)
	    {
	      type = build_pointer_type (type);
	      p = p->declarator;
	    }
	  c_parser_parse_ssa_name (parser, id_declarator->u.id.id, type,
				   version, ver_offset);
	}
      ଅନ୍ୟଥା
	{
	  ବୃକ୍ଷ postfix_attrs = NULL_ବୃକ୍ଷ;
	  ବୃକ୍ଷ all_prefix_attrs = specs->attrs;
	  specs->attrs = ଖାଲି;
	  ବୃକ୍ଷ decl = start_decl (declarator, specs, ମିଥ୍ୟା,
				  chainon (postfix_attrs, all_prefix_attrs));
	  ଯଦି (decl)
	    finish_decl (decl, UNKNOWN_LOCATION, NULL_ବୃକ୍ଷ, NULL_ବୃକ୍ଷ,
			 NULL_ବୃକ୍ଷ);
	}
    }
}

/* Parse gimple goto statement.  */

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_gimple_goto_stmt (gimple_parser &parser,
			   location_t loc, ବୃକ୍ଷ label, gimple_seq *seq)
{
  ଯଦି (cfun->curr_properties & PROP_cfg)
    {
      ପୂର୍ଣ୍ଣସଂଖ୍ୟା dest_index;
      profile_probability prob;
      ଯଦି (c_parser_gimple_parse_bb_spec_edge_probability (label, parser,
							  &dest_index, &prob))
	{
	  parser.ଠେଲ_edge (parser.current_bb->index, dest_index,
			    EDGE_FALLTHRU, prob);
	  ଫେରନ୍ତୁ;
	}
    }
  ବୃକ୍ଷ decl = lookup_label_for_goto (loc, label);
  gimple_seq_add_stmt_without_update (seq, gimple_build_goto (decl));
}

/* Parse a parenthesized condition.
   gimple-condition:
     ( gimple-binary-expression )    */

ସ୍ଥିର ବୃକ୍ଷ
c_parser_gimple_paren_condition (gimple_parser &parser)
{
  ଯଦି (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
  ବୃକ୍ଷ cond
    = c_parser_gimple_ଦ୍ୱିମିକ_expression (parser, boolean_type_ଗଣ୍ଠି).ମୂଲ୍ୟ;
  ଯଦି (cond != error_mark_ଗଣ୍ଠି
      && ! COMPARISON_CLASS_P (cond)
      && ! CONSTANT_CLASS_P (cond)
      && ! SSA_VAR_P (cond))
    {
      c_parser_error (parser, "comparison required");
      cond = error_mark_ଗଣ୍ଠି;
    }
  ଯଦି (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
  ଫେରନ୍ତୁ cond;
}

/* Parse gimple try statement.

   try-statement:
     try { ... } finally { ... }
     try { ... } finally { ... } else { ... }

   This could support try/catch as well, but it's not implemented yet.
 */

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_gimple_try_stmt (gimple_parser &parser, gimple_seq *seq)
{
  gimple_seq tryseq = ଖାଲି;
  c_parser_consume_token (parser);
  c_parser_gimple_compound_statement (parser, &tryseq);

  ଯଦି ((c_parser_next_token_is (parser, CPP_KEYWORD)
       && c_parser_peek_token (parser)->keyword == RID_AT_FINALLY)
      || (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_token (parser)->id_kind == C_ID_ID
	  && strcmp (IDENTIFIER_POINTER (c_parser_peek_token (parser)->ମୂଲ୍ୟ),
		     "finally") == 0))
    {
      gimple_seq finseq = ଖାଲି;
      c_parser_consume_token (parser);
      c_parser_gimple_compound_statement (parser, &finseq);

      ଯଦି (c_parser_next_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_ELSE)
	{
	  gimple_seq elsseq = ଖାଲି;
	  c_parser_consume_token (parser);
	  c_parser_gimple_compound_statement (parser, &elsseq);

	  geh_else *stmt = gimple_build_eh_else (finseq, elsseq);
	  finseq = ଖାଲି;
	  gimple_seq_add_stmt_without_update (&finseq, stmt);
	}

      gtry *stmt = gimple_build_try (tryseq, finseq, GIMPLE_TRY_FINALLY);
      gimple_seq_add_stmt_without_update (seq, stmt);
    }
  ଅନ୍ୟଥା ଯଦି (c_parser_next_token_is (parser, CPP_KEYWORD)
      && c_parser_peek_token (parser)->keyword == RID_AT_CATCH)
    c_parser_error (parser, "%<catch%> is not supported");
  ଅନ୍ୟଥା
    c_parser_error (parser, "expected %<finally%> or %<catch%>");
}

/* Parse gimple if-else statement.

   if-statement:
     if ( gimple-binary-expression ) gimple-goto-statement
     if ( gimple-binary-expression ) gimple-goto-statement \
					else gimple-goto-statement
 */

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_gimple_if_stmt (gimple_parser &parser, gimple_seq *seq)
{
  ବୃକ୍ଷ t_label = NULL_ବୃକ୍ଷ, f_label = NULL_ବୃକ୍ଷ, label;
  location_t loc;
  c_parser_consume_token (parser);
  ବୃକ୍ଷ cond = c_parser_gimple_paren_condition (parser);

  ଯଦି (c_parser_next_token_is_keyword (parser, RID_GOTO))
    {
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      ଯଦି (! c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected label");
	  ଫେରନ୍ତୁ;
	}
      label = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
      c_parser_consume_token (parser);
      ପୂର୍ଣ୍ଣସଂଖ୍ୟା dest_index;
      profile_probability prob;
      ଯଦି ((cfun->curr_properties & PROP_cfg)
	  && c_parser_gimple_parse_bb_spec_edge_probability (label, parser,
							     &dest_index, &prob))
	parser.ଠେଲ_edge (parser.current_bb->index, dest_index,
			  EDGE_TRUE_ମୂଲ୍ୟ, prob);
      ଅନ୍ୟଥା
	t_label = lookup_label_for_goto (loc, label);
      ଯଦି (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	ଫେରନ୍ତୁ;
    }
  ଅନ୍ୟଥା
    {
      c_parser_error (parser, "expected goto expression");
      ଫେରନ୍ତୁ;
    }

  ଯଦି (c_parser_next_token_is_keyword (parser, RID_ELSE))
    c_parser_consume_token (parser);
  ଅନ୍ୟଥା
    {
      c_parser_error (parser, "expected else statement");
      ଫେରନ୍ତୁ;
    }

  ଯଦି (c_parser_next_token_is_keyword (parser, RID_GOTO))
    {
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      ଯଦି (! c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected label");
	  ଫେରନ୍ତୁ;
	}
      label = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
      c_parser_consume_token (parser);
      ପୂର୍ଣ୍ଣସଂଖ୍ୟା dest_index;
      profile_probability prob;
      ଯଦି ((cfun->curr_properties & PROP_cfg)
	  && c_parser_gimple_parse_bb_spec_edge_probability (label, parser,
							     &dest_index, &prob))
	parser.ଠେଲ_edge (parser.current_bb->index, dest_index,
			  EDGE_FALSE_ମୂଲ୍ୟ, prob);
      ଅନ୍ୟଥା
	f_label = lookup_label_for_goto (loc, label);
      ଯଦି (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	ଫେରନ୍ତୁ;
    }
  ଅନ୍ୟଥା
    {
      c_parser_error (parser, "expected goto expression");
      ଫେରନ୍ତୁ;
    }

  ଯଦି (cond != error_mark_ଗଣ୍ଠି)
    gimple_seq_add_stmt_without_update (seq, gimple_build_cond_from_ବୃକ୍ଷ (cond, t_label,
							   f_label));
}

/* Parse gimple switch-statement.

   gimple-switch-statement:
     switch (gimple-postfix-expression) gimple-case-statement

   gimple-case-statement:
     gimple-case-statement
     gimple-label-statement : gimple-goto-statement
*/

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_gimple_switch_stmt (gimple_parser &parser, gimple_seq *seq)
{
  c_ପଦସମଷ୍ଟି cond_ପଦସମଷ୍ଟି;
  ବୃକ୍ଷ case_label, label;
  auto_vec<ବୃକ୍ଷ> labels;
  ବୃକ୍ଷ default_label = NULL_ବୃକ୍ଷ;
  c_parser_consume_token (parser);

  ଯଦି (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    ଫେରନ୍ତୁ;
  cond_ପଦସମଷ୍ଟି = c_parser_gimple_postfix_expression (parser);
  ଯଦି (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    ଫେରନ୍ତୁ;

  ଯଦି (! c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    ଫେରନ୍ତୁ;

  ଯେତେବେଳେ (c_parser_next_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      ଯଦି (c_parser_next_token_is (parser, CPP_EOF))
	{
	  c_parser_error (parser, "expected statement");
	  ଫେରନ୍ତୁ;
	}

      ବାଛ (c_parser_peek_token (parser)->keyword)
	{
	ସ୍ଥିତି RID_CASE:
	  {
	    c_ପଦସମଷ୍ଟି exp1;
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);

	    ଯଦି (c_parser_next_token_is (parser, CPP_NAME)
		|| c_parser_peek_token (parser)->type == CPP_ସଂଖ୍ୟା)
	      exp1 = c_parser_gimple_postfix_expression (parser);
	    ଅନ୍ୟଥା
	      {
		c_parser_error (parser, "expected expression");
		ଫେରନ୍ତୁ;
	      }

	    ଯଦି (c_parser_next_token_is (parser, CPP_COLON))
	      {
		c_parser_consume_token (parser);
		ଯଦି (c_parser_next_token_is (parser, CPP_NAME))
		  {
		    label = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
		    c_parser_consume_token (parser);
		    ବୃକ୍ଷ decl = lookup_label_for_goto (loc, label);
		    case_label = build_case_label (exp1.ମୂଲ୍ୟ, NULL_ବୃକ୍ଷ,
						   decl);
		    labels.safe_ଠେଲ (case_label);
		    ଯଦି (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      ଫେରନ୍ତୁ;
		  }
		ଅନ୍ୟଥା ଯଦି (! c_parser_require (parser, CPP_NAME,
					     "expected label"))
		  ଫେରନ୍ତୁ;
	      }
	    ଅନ୍ୟଥା ଯଦି (! c_parser_require (parser, CPP_SEMICOLON,
					 "expected %<:%>"))
	      ଫେରନ୍ତୁ;
	    ଭାଙ୍ଗ;
	  }
	ସ୍ଥିତି RID_DEFAULT:
	  {
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);
	    ଯଦି (c_parser_next_token_is (parser, CPP_COLON))
	      {
		c_parser_consume_token (parser);
		ଯଦି (c_parser_next_token_is (parser, CPP_NAME))
		  {
		    label = c_parser_peek_token (parser)->ମୂଲ୍ୟ;
		    c_parser_consume_token (parser);
		    ବୃକ୍ଷ decl = lookup_label_for_goto (loc, label);
		    default_label = build_case_label (NULL_ବୃକ୍ଷ, NULL_ବୃକ୍ଷ,
						      decl);
		    ଯଦି (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      ଫେରନ୍ତୁ;
		  }
		ଅନ୍ୟଥା ଯଦି (! c_parser_require (parser, CPP_NAME,
					     "expected label"))
		  ଫେରନ୍ତୁ;
	      }
	    ଅନ୍ୟଥା ଯଦି (! c_parser_require (parser, CPP_SEMICOLON,
					 "expected %<:%>"))
	      ଫେରନ୍ତୁ;
	    ଭାଙ୍ଗ;
	  }
	ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	  c_parser_error (parser, "expected case label");
	  ଫେରନ୍ତୁ;
	}

    }
  ଯଦି (! c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>"))
    ଫେରନ୍ତୁ;

  ଯଦି (cond_ପଦସମଷ୍ଟି.ମୂଲ୍ୟ != error_mark_ଗଣ୍ଠି)
    {
      gswitch *s = gimple_build_switch (cond_ପଦସମଷ୍ଟି.ମୂଲ୍ୟ, default_label, labels);
      gimple_seq_add_stmt_without_update (seq, s);
    }
}

/* Parse gimple return statement.  */

ସ୍ଥିର ଶୂନ୍ୟ
c_parser_gimple_return_stmt (gimple_parser &parser, gimple_seq *seq)
{
  location_t loc = c_parser_peek_token (parser)->location;
  gimple *ret = ଖାଲି;
  c_parser_consume_token (parser);
  ଯଦି (c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      c_finish_gimple_return (loc, NULL_ବୃକ୍ଷ);
      ret = gimple_build_return (ଖାଲି);
      gimple_seq_add_stmt_without_update (seq, ret);
    }
  ଅନ୍ୟଥା
    {
      location_t xloc = c_parser_peek_token (parser)->location;
      c_ପଦସମଷ୍ଟି ପଦସମଷ୍ଟି = c_parser_gimple_unary_expression (parser);
      ଯଦି (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ != error_mark_ଗଣ୍ଠି)
	{
	  c_finish_gimple_return (xloc, ପଦସମଷ୍ଟି.ମୂଲ୍ୟ);
	  ret = gimple_build_return (ପଦସମଷ୍ଟି.ମୂଲ୍ୟ);
	  gimple_seq_add_stmt_without_update (seq, ret);
	}
    }
}

/* Support function for c_parser_gimple_return_stmt.  */

ସ୍ଥିର ଶୂନ୍ୟ
c_finish_gimple_return (location_t loc, ବୃକ୍ଷ retval)
{
  ବୃକ୍ଷ valtype = ବୃକ୍ଷ_TYPE (ବୃକ୍ଷ_TYPE (current_function_decl));

  /* Use the expansion point to handle cases such as returning NULL
     in a function returning void.  */
  location_t xloc = expansion_point_location_if_in_system_header (loc);

  ଯଦି (ବୃକ୍ଷ_THIS_VOLATILE (current_function_decl))
    warning_at (xloc, 0,
		"function declared %<noreturn%> has a %<return%> statement");

  ଯଦି (! retval)
    current_function_returns_null = 1;
  ଅନ୍ୟଥା ଯଦି (valtype == 0 || VOID_TYPE_P (valtype))
    {
      current_function_returns_null = 1;
      ଯଦି (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (retval)) != VOID_TYPE)
	{
	  error_at
	    (xloc, "%<return%> with a value, in function returning void");
	  inform (DECL_SOURCE_LOCATION (current_function_decl),
		  "declared here");
	}
    }
  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (valtype) != ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (retval)))
    {
      error_at
	(xloc, "invalid conversion in return statement");
      inform (DECL_SOURCE_LOCATION (current_function_decl),
	      "declared here");
    }
  ଫେରନ୍ତୁ;
}
