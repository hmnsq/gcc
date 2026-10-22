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

#अन्तर्भाव "config.h"
#अन्तर्भाव "system.h"
#अन्तर्भाव "coretypes.h"
#अन्तर्भाव "target.h"
#अन्तर्भाव "function.h"
#अन्तर्भाव "c-tree.h"
#अन्तर्भाव "timevar.h"
#अन्तर्भाव "stringpool.h"
#अन्तर्भाव "cgraph.h"
#अन्तर्भाव "attribs.h"
#अन्तर्भाव "stor-layout.h"
#अन्तर्भाव "varasm.h"
#अन्तर्भाव "trans-mem.h"
#अन्तर्भाव "c-family/c-pragma.h"
#अन्तर्भाव "c-lang.h"
#अन्तर्भाव "c-family/c-objc.h"
#अन्तर्भाव "plugin.h"
#अन्तर्भाव "builtins.h"
#अन्तर्भाव "gomp-constants.h"
#अन्तर्भाव "c-family/c-indentation.h"
#अन्तर्भाव "gimple-expr.h"
#अन्तर्भाव "context.h"
#अन्तर्भाव "gcc-rich-location.h"
#अन्तर्भाव "c-parser.h"
#अन्तर्भाव "tree-vrp.h"
#अन्तर्भाव "tree-pass.h"
#अन्तर्भाव "tree-pretty-print.h"
#अन्तर्भाव "tree.h"
#अन्तर्भाव "basic-block.h"
#अन्तर्भाव "gimple.h"
#अन्तर्भाव "gimple-pretty-print.h"
#अन्तर्भाव "tree-ssa.h"
#अन्तर्भाव "pass_manager.h"
#अन्तर्भाव "tree-ssanames.h"
#अन्तर्भाव "gimple-ssa.h"
#अन्तर्भाव "tree-dfa.h"
#अन्तर्भाव "internal-fn.h"
#अन्तर्भाव "cfg.h"
#अन्तर्भाव "cfghooks.h"
#अन्तर्भाव "bitmap.h"
#अन्तर्भाव "cfganal.h"
#अन्तर्भाव "tree-cfg.h"
#अन्तर्भाव "gimple-iterator.h"
#अन्तर्भाव "cfgloop.h"
#अन्तर्भाव "tree-phinodes.h"
#अन्तर्भाव "tree-into-ssa.h"


/* GIMPLE parser state.  */

वग्ग gimple_parser
{
सार्वजनिक:
  gimple_parser (c_parser *p) : parser (p), edges(), current_bb(रिक्त) {}
  /* c_parser is not visible here, use composition and fake inheritance
     via a conversion operator.  */
  operator c_parser *() { पटिनिवत्त parser; }
  c_parser *parser;

  /* CFG build state.  */
  वग्ग gimple_parser_edge
  {
  सार्वजनिक:
    पूर्णाङ्क src;
    पूर्णाङ्क dest;
    पूर्णाङ्क flags;
    profile_probability probability;
  };
  auto_vec<gimple_parser_edge> edges;
  basic_block current_bb;

  शून्य प्रक्षिप_edge (पूर्णाङ्क, पूर्णाङ्क, पूर्णाङ्क, profile_probability);
};

शून्य
gimple_parser::प्रक्षिप_edge (पूर्णाङ्क src, पूर्णाङ्क dest, पूर्णाङ्क flags,
			  profile_probability prob)
{
  gimple_parser_edge e;
  e.src = src;
  e.dest = dest;
  e.flags = flags;
  e.probability = prob;
  edges.safe_प्रक्षिप (e);
}


/* Gimple parsing functions.  */
स्थिर तार्किक c_parser_gimple_compound_statement (gimple_parser &, gimple_seq *);
स्थिर शून्य c_parser_gimple_label (gimple_parser &, gimple_seq *);
स्थिर शून्य c_parser_gimple_statement (gimple_parser &, gimple_seq *);
स्थिर संरचना c_व्यञ्जकम् c_parser_gimple_द्विमान_expression (gimple_parser &, वृक्षः);
स्थिर संरचना c_व्यञ्जकम् c_parser_gimple_unary_expression (gimple_parser &);
स्थिर संरचना c_व्यञ्जकम् c_parser_gimple_postfix_expression
			(gimple_parser &, वृक्षः = error_mark_ग्रन्थिः);
स्थिर संरचना c_व्यञ्जकम् c_parser_gimple_postfix_expression_after_primary
			(gimple_parser &, location_t, संरचना c_व्यञ्जकम्);
स्थिर शून्य c_parser_gimple_declaration (gimple_parser &);
स्थिर शून्य c_parser_gimple_goto_stmt (gimple_parser &, location_t,
				       वृक्षः, gimple_seq *);
स्थिर शून्य c_parser_gimple_try_stmt (gimple_parser &, gimple_seq *);
स्थिर शून्य c_parser_gimple_if_stmt (gimple_parser &, gimple_seq *);
स्थिर शून्य c_parser_gimple_switch_stmt (gimple_parser &, gimple_seq *);
स्थिर शून्य c_parser_gimple_return_stmt (gimple_parser &, gimple_seq *);
स्थिर शून्य c_finish_gimple_return (location_t, वृक्षः);
स्थिर वृक्षः c_parser_gimple_paren_condition (gimple_parser &);
स्थिर शून्य c_parser_gimple_व्यञ्जकम्_list (gimple_parser &, vec<वृक्षः> *);


/* Much like parser_build_unary_op, but avoid applying default conversions.  */

स्थिर c_व्यञ्जकम्
gimple_parser_build_unary_op (location_t loc,
			      गणना वृक्षः_code code, संरचना c_व्यञ्जकम् arg)
{
  संरचना c_व्यञ्जकम् result;

  result.original_code = code;
  result.original_type = रिक्त;
  result.m_decimal = 0;

  सचे (reject_gcc_builtin (arg.मानम्))
    {
      result.मानम् = error_mark_ग्रन्थिः;
    }
  अञ्ञथा
    {
      result.मानम् = build_unary_op (loc, code, arg.मानम्, सच्च);

      सचे (वृक्षः_OVERFLOW_P (result.मानम्) && !वृक्षः_OVERFLOW_P (arg.मानम्))
	overflow_warning (loc, result.मानम्, arg.मानम्);
    }

  /* We are typically called when parsing a prefix token at LOC acting on
     ARG.  Reflect this by updating the source range of the result to
     start at LOC and end at the end of ARG.  */
  set_c_व्यञ्जकम्_source_range (&result,
			   loc, arg.get_finish ());

  पटिनिवत्त result;
}

/* See if VAL is an identifier matching __BB<num> and return <num>
   in *INDEX.  */

स्थिर तार्किक
c_parser_gimple_parse_bb_spec (वृक्षः val, पूर्णाङ्क *index)
{
  सचे (!startswith (IDENTIFIER_POINTER (val), "__BB"))
    पटिनिवत्त मिच्छा;

  ध्रुव वर्ण *bb = IDENTIFIER_POINTER (val) + 4;
  सचे (! ISDIGIT (*bb))
    पटिनिवत्त मिच्छा;

  वर्ण *pend;
  errno = 0;
  ध्रुव unsigned long सङ्ख्या = strtoul (bb, &pend, 10);
  सचे (errno == ERANGE
      || *pend != '\0'
      || सङ्ख्या > INT_MAX)
    पटिनिवत्त मिच्छा;

  *index = सङ्ख्या;
  पटिनिवत्त सच्च;
}

/* See if VAL is an identifier matching __BB<num> and return <num>
   in *INDEX.  Return true if so and parse also FREQUENCY of
   the edge.  */


स्थिर तार्किक
c_parser_gimple_parse_bb_spec_edge_probability (वृक्षः val,
						gimple_parser &parser,
						पूर्णाङ्क *index,
						profile_probability
						*probability)
{
  तार्किक return_p = c_parser_gimple_parse_bb_spec (val, index);
  सचे (return_p)
    {
      *probability = profile_probability::uninitialized ();
      /* Parse frequency if provided.  */
      सचे (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	{
	  वृक्षः f;
	  c_parser_consume_token (parser);
	  सचे (!c_parser_next_token_is (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected frequency quality");
	      पटिनिवत्त मिच्छा;
	    }

	  profile_quality quality;
	  ध्रुव वर्ण *v
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्);
	  सचे (!parse_profile_quality (v, &quality))
	    {
	      c_parser_error (parser, "unknown profile quality");
	      पटिनिवत्त मिच्छा;
	    }

	  c_parser_consume_token (parser);
	  सचे (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    पटिनिवत्त मिच्छा;

	  सचे (!c_parser_next_token_is (parser, CPP_सङ्ख्या)
	      || (वृक्षः_CODE (f = c_parser_peek_token (parser)->मानम्)
		  != INTEGER_CST))
	    {
	      c_parser_error (parser, "expected frequency value");
	      पटिनिवत्त मिच्छा;
	    }

	  unsigned पूर्णाङ्क मानम् = वृक्षः_INT_CST_नीचः (f);
	  *probability = profile_probability (मानम्, quality);

	  c_parser_consume_token (parser);
	  सचे (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    पटिनिवत्त मिच्छा;

	  सचे (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    पटिनिवत्त मिच्छा;
	}

      पटिनिवत्त सच्च;
    }

  पटिनिवत्त मिच्छा;

}

/* Parse the body of a function declaration marked with "__GIMPLE".  */

शून्य
c_parser_parse_gimple_body (c_parser *cparser, वर्ण *gimple_pass,
			    गणना c_declspec_il cdil,
			    profile_गणनम् entry_bb_गणनम्)
{
  gimple_parser parser (cparser);
  gimple_seq seq = रिक्त;
  gimple_seq body = रिक्त;
  वृक्षः stmt = प्रक्षिप_stmt_list ();
  प्रक्षिप_scope ();
  location_t loc1 = c_parser_peek_token (parser)->location;

  cfun->pass_startwith = gimple_pass;
  init_वृक्षः_ssa (cfun);

  सचे (cdil == cdil_gimple)
    /* While we have SSA names in the IL we do not have a CFG built yet
       and PHIs are represented using a PHI internal function.  We do
       have lowered control flow and exception handling (well, we do not
       have parser support for EH yet).  But as we still have BINDs
       we have to go through lowering again.  */
    cfun->curr_properties = PROP_gimple_any;
  अञ्ञथा
    {
      /* We have at least cdil_gimple_cfg.  */
      gimple_register_cfg_hooks ();
      init_empty_वृक्षः_cfg ();
      parser.current_bb = ENTRY_BLOCK_PTR_FOR_FN (cfun);
      /* Initialize the bare loop structure - we are going to only
         mark headers and leave the rest to fixup.  */
      set_loops_for_fn (cfun, ggc_cleared_alloc<संरचना loops> ());
      init_loops_structure (cfun, loops_for_fn (cfun), 1);
      loops_state_set (cfun, LOOPS_NEED_FIXUP|LOOPS_MAY_HAVE_MULTIPLE_LATCHES);
      cfun->curr_properties
	|= PROP_gimple_lcf | PROP_gimple_leh | PROP_cfg | PROP_loops;
      सचे (cdil == cdil_gimple_ssa)
	{
	  init_ssa_operands (cfun);
	  cfun->curr_properties |= PROP_ssa;
	}
    }

  सचे (! c_parser_gimple_compound_statement (parser, &seq)
      && cdil == cdil_gimple)
    {
      gimple *ret = gimple_build_return (रिक्त);
      gimple_seq_add_stmt_without_update (&seq, ret);
    }

  वृक्षः block = निष्कासय_scope ();
  stmt = निष्कासय_stmt_list (stmt);
  stmt = c_build_bind_व्यञ्जकम् (loc1, block, stmt);

  block = DECL_INITIAL (current_function_decl);
  BLOCK_SUBBLOCKS (block) = NULL_वृक्षः;
  BLOCK_CHAIN (block) = NULL_वृक्षः;
  वृक्षः_ASM_WRITTEN (block) = 1;

  सचे (cdil == cdil_gimple)
    {
      gbind *bind_stmt = gimple_build_bind (BIND_व्यञ्जकम्_VARS (stmt), रिक्त,
					    BIND_व्यञ्जकम्_BLOCK (stmt));
      gimple_bind_set_body (bind_stmt, seq);
      gimple_seq_add_stmt_without_update (&body, bind_stmt);
      gimple_set_body (current_function_decl, body);
    }
  अञ्ञथा
    {
      /* Control-flow and binds are lowered, record local decls.  */
      अत्थाय (वृक्षः var = BIND_व्यञ्जकम्_VARS (stmt); var; var = DECL_CHAIN (var))
	सचे (VAR_P (var)
	    && !DECL_EXTERNAL (var))
	  {
	    add_local_decl (cfun, var);
	    /* When the middle-end re-gimplifies any expression we might
	       run into the assertion that we've seen the decl in a BIND.  */
	    सचे (!वृक्षः_STATIC (var))
	      DECL_SEEN_IN_BIND_व्यञ्जकम्_P (var) = 1;
	  }
      /* We have a CFG.  Build the edges.  */
      अत्थाय (unsigned i = 0; i < parser.edges.length (); ++i)
	{
	  edge e = make_edge (BASIC_BLOCK_FOR_FN (cfun, parser.edges[i].src),
			      BASIC_BLOCK_FOR_FN (cfun, parser.edges[i].dest),
			      parser.edges[i].flags);
	  e->probability = parser.edges[i].probability;
	}
      /* Add edges for case labels.  */
      basic_block bb;
      FOR_EACH_BB_FN (bb, cfun)
	सचे (EDGE_गणनम् (bb->succs) == 0)
	  {
	    सचे (gswitch *sw = safe_dyn_cast <gswitch *> (*gsi_last_bb (bb)))
	      अत्थाय (unsigned i = 0; i < gimple_switch_अङ्कः_labels (sw); ++i)
		{
		  basic_block label_bb = gimple_switch_label_bb (cfun, sw, i);
		  make_edge (bb, label_bb, 0);
		}
	  }
      /* Need those for loop fixup.  */
      calculate_dominance_info (CDI_DOMINATORS);
      /* With SSA lower PHIs parsed as internal function calls and
	 update stmts.  */
      सचे (cdil == cdil_gimple_ssa)
	{
	  /* Create PHI nodes, they are parsed into __PHI internal calls
	     and update SSA operands.  */
	  FOR_EACH_BB_FN (bb, cfun)
	    {
	      gimple_stmt_iterator gsi;
	      अत्थाय (gsi = gsi_start_bb (bb); !gsi_end_p (gsi);)
		{
		  gimple *stmt = gsi_stmt (gsi);
		  सचे (!gimple_call_internal_p (stmt, IFN_PHI))
		    भङ्ग;

		  gphi *phi = create_phi_ग्रन्थिः (gimple_call_lhs (stmt), bb);
		  अत्थाय (unsigned i = 0; i < gimple_call_अङ्कः_args (stmt); i += 2)
		    {
		      पूर्णाङ्क srcidx = वृक्षः_INT_CST_नीचः (gimple_call_arg (stmt, i));
		      edge e = find_edge (BASIC_BLOCK_FOR_FN (cfun, srcidx), bb);
		      सचे (!e)
			c_parser_error (parser, "edge not found");
		      अञ्ञथा
			add_phi_arg (phi, gimple_call_arg (stmt, i + 1), e,
				     UNKNOWN_LOCATION);
		    }
		  gsi_remove (&gsi, सच्च);
		}
	      अत्थाय (; !gsi_end_p (gsi); gsi_next (&gsi))
		update_stmt (gsi_stmt (gsi));
	    }
	  /* Fill SSA name gaps, putting them on the freelist and diagnose
	     SSA names without definition.  */
	  अत्थाय (unsigned i = 1; i < अङ्कः_ssa_names; ++i)
	    सचे (!ssa_name (i))
	      {
		वृक्षः name = make_ssa_name_fn (cfun, integer_type_ग्रन्थिः, रिक्त, i);
		release_ssa_name_fn (cfun, name);
	      }
	    अञ्ञथा सचे (!SSA_NAME_DEF_STMT (ssa_name (i)))
	      error ("SSA name %qE with version %d has no definition",
		     ssa_name (i), i);
	  /* No explicit virtual operands (yet).  */
	  bitmap_obstack_initialize (रिक्त);
	  update_ssa (TODO_update_ssa_only_virtuals);
	  bitmap_obstack_release (रिक्त);
	  /* ???  By flushing the freelist after virtual operand SSA rewrite
	     we keep the gaps available for re-use like needed for the
	     PR89595 testcase but then usually virtual operands would have
	     taken most of them.  The fix is obviously to make virtual
	     operands explicit in the SSA IL.  */
	  flush_ssaname_freelist ();
	}
      fix_loop_structure (रिक्त);
    }

  सचे (cfun->curr_properties & PROP_cfg)
    {
      ENTRY_BLOCK_PTR_FOR_FN (cfun)->गणनम् = entry_bb_गणनम्;
      gcov_type t = param_gimple_fe_computed_hot_bb_threshold;
      set_hot_bb_threshold (t);
      update_max_bb_गणनम् ();
      cgraph_ग्रन्थिः::get_create (cfun->decl);
      cgraph_edge::rebuild_edges ();
    }

  /* Perform IL validation and if any error is found abort compilation
     of this function by zapping its body.  */
  सचे ((cfun->curr_properties & PROP_cfg)
      && verify_gimple_in_cfg (cfun, मिच्छा, मिच्छा))
    init_empty_वृक्षः_cfg ();
  अञ्ञथा सचे (!(cfun->curr_properties & PROP_cfg)
	   && verify_gimple_in_seq (gimple_body (current_function_decl), मिच्छा))
    gimple_set_body (current_function_decl, रिक्त);

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

स्थिर तार्किक
c_parser_gimple_compound_statement (gimple_parser &parser, gimple_seq *seq)
{
  तार्किक return_p = मिच्छा;

  सचे (! c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    पटिनिवत्त मिच्छा;

  /* A compound statement starts with optional declarations.  */
  याव (c_parser_next_tokens_start_declaration (parser))
    {
      c_parser_gimple_declaration (parser);
      सचे (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	पटिनिवत्त मिच्छा;
    }

  याव (c_parser_next_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      सचे (c_parser_error (parser))
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_BRACE, रिक्त);
	  पटिनिवत्त return_p;
	}
      अञ्ञथा सचे (c_parser_next_token_is (parser, CPP_EOF))
	{
	  c_parser_error (parser, "expected declaration or statement");
	  पटिनिवत्त return_p;
	}

      विकल्प (c_parser_peek_token (parser)->type)
	{
	पक्ष CPP_KEYWORD:
	  विकल्प (c_parser_peek_token (parser)->keyword)
	    {
	    पक्ष RID_AT_TRY:
	      c_parser_gimple_try_stmt (parser, seq);
	      भङ्ग;
	    पक्ष RID_IF:
	      c_parser_gimple_if_stmt (parser, seq);
	      भङ्ग;
	    पक्ष RID_SWITCH:
	      c_parser_gimple_switch_stmt (parser, seq);
	      भङ्ग;
	    पक्ष RID_GOTO:
	      {
		location_t loc = c_parser_peek_token (parser)->location;
		c_parser_consume_token (parser);
		सचे (c_parser_next_token_is (parser, CPP_NAME))
		  {
		    वृक्षः label = c_parser_peek_token (parser)->मानम्;
		    c_parser_consume_token (parser);
		    c_parser_gimple_goto_stmt (parser, loc, label, seq);
		    सचे (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      पटिनिवत्त return_p;
		  }
		}
	      भङ्ग;
	    पक्ष RID_RETURN:
	      return_p = सच्च;
	      c_parser_gimple_return_stmt (parser, seq);
	      सचे (! c_parser_require (parser, CPP_SEMICOLON,
				      "expected %<;%>"))
		पटिनिवत्त return_p;
	      सचे (cfun->curr_properties & PROP_cfg)
		parser.प्रक्षिप_edge (parser.current_bb->index, EXIT_BLOCK, 0,
				  profile_probability::uninitialized ());
	      भङ्ग;
	    स्वभाव:
	      गच्छ व्यञ्जकम्_stmt;
	    }
	  भङ्ग;
	पक्ष CPP_NAME:
	  सचे (c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_gimple_label (parser, seq);
	      भङ्ग;
	    }
	  सचे (c_parser_next_token_is (parser, CPP_NAME)
	      && c_parser_peek_token (parser)->id_kind == C_ID_ID
	      && strcmp (IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्),
			 "try") == 0)
	    {
	      c_parser_gimple_try_stmt (parser, seq);
	      भङ्ग;
	    }
	  /* Basic block specification.
	     __BB (index, ...)  */
	  सचे ((cfun->curr_properties & PROP_cfg)
	      && !strcmp (IDENTIFIER_POINTER
			    (c_parser_peek_token (parser)->मानम्), "__BB"))
	    {
	      c_parser_consume_token (parser);
	      सचे (! c_parser_require (parser, CPP_OPEN_PAREN,
				      "expected %<(%>"))
		पटिनिवत्त return_p;
	      सचे (c_parser_next_token_is_not (parser, CPP_सङ्ख्या))
		{
		  c_parser_error (parser, "expected block index");
		  पटिनिवत्त return_p;
		}
	      वृक्षः tnum = c_parser_peek_token (parser)->मानम्;
	      सचे (वृक्षः_CODE (tnum) != INTEGER_CST)
		{
		  c_parser_error (parser, "expected block index");
		  पटिनिवत्त return_p;
		}
	      पूर्णाङ्क index = वृक्षः_INT_CST_नीचः (tnum);
	      सचे (index < अङ्कः_FIXED_BLOCKS
		  || (index < last_basic_block_for_fn (cfun)
		      && BASIC_BLOCK_FOR_FN (cfun, index) != रिक्त))
		{
		  c_parser_error (parser, "invalid block index");
		  पटिनिवत्त return_p;
		}
	      पूर्णाङ्क is_loop_header_of = -1;
	      profile_गणनम् bb_गणनम् = profile_गणनम्::uninitialized ();
	      c_parser_consume_token (parser);
	      याव (c_parser_next_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  सचे (! c_parser_next_token_is (parser, CPP_NAME))
		    {
		      c_parser_error (parser, "expected block specifier");
		      पटिनिवत्त return_p;
		    }
		  /* loop_header (NUM)  */
		  सचे (!strcmp (IDENTIFIER_POINTER
			         (c_parser_peek_token (parser)->मानम्),
			       "loop_header"))
		    {
		      c_parser_consume_token (parser);
		      सचे (! c_parser_require (parser, CPP_OPEN_PAREN,
					      "expected %<(%>"))
			पटिनिवत्त return_p;
		      वृक्षः loop_अङ्कः;
		      सचे (! c_parser_next_token_is (parser, CPP_सङ्ख्या)
			  || वृक्षः_CODE (loop_अङ्कः
					  = c_parser_peek_token (parser)->मानम्)
			       != INTEGER_CST)
			{
			  c_parser_error (parser, "expected loop number");
			  पटिनिवत्त return_p;
			}
		      c_parser_consume_token (parser);
		      is_loop_header_of = वृक्षः_INT_CST_नीचः (loop_अङ्कः);
		      सचे (! c_parser_require (parser, CPP_CLOSE_PAREN,
					      "expected %<)%>"))
			पटिनिवत्त return_p;
		    }
		  /* Parse profile: quality(value) */
		  अञ्ञथा
		    {
		      वृक्षः q;
		      profile_quality quality;
		      वृक्षः v = c_parser_peek_token (parser)->मानम्;
		      सचे (!parse_profile_quality (IDENTIFIER_POINTER (v),
						  &quality))
			{
			  c_parser_error (parser, "unknown block specifier");
			  पटिनिवत्त मिच्छा;
			}

		      c_parser_consume_token (parser);
		      सचे (!c_parser_require (parser, CPP_OPEN_PAREN,
					     "expected %<(%>"))
			पटिनिवत्त मिच्छा;

		      सचे (!c_parser_next_token_is (parser, CPP_सङ्ख्या)
			  || (वृक्षः_CODE (q = c_parser_peek_token (parser)->मानम्)
			      != INTEGER_CST))
			{
			  c_parser_error (parser, "expected count value");
			  पटिनिवत्त मिच्छा;
			}

		      bb_गणनम्
			= profile_गणनम्::from_gcov_type (वृक्षः_INT_CST_नीचः (q),
							 quality);
		      c_parser_consume_token (parser);
		      सचे (! c_parser_require (parser, CPP_CLOSE_PAREN,
					      "expected %<)%>"))
			पटिनिवत्त return_p;
		    }
		}
	      सचे (! c_parser_require (parser, CPP_CLOSE_PAREN,
				      "expected %<)%>")
		  || ! c_parser_require (parser, CPP_COLON,
					 "expected %<:%>"))
		पटिनिवत्त return_p;

	      /* Put stmts parsed in the current block.  */
	      सचे (!gimple_seq_empty_p (*seq))
		{
		  सचे (!parser.current_bb)
		    c_parser_error (parser, "stmts without block");
		  अञ्ञथा
		    {
		      gimple_stmt_iterator gsi
			= gsi_start_bb (parser.current_bb);
		      gsi_निवेशय_seq_after_without_update (&gsi, *seq,
							   GSI_CONTINUE_LINKING);
		    }
		  *seq = रिक्त;
		}

	      /* Build an empty block with specified index, linking them
		 in source order.  */
	      basic_block bb = alloc_block ();
	      bb->index = index;
	      link_block (bb, (parser.current_bb ? parser.current_bb
			       : ENTRY_BLOCK_PTR_FOR_FN (cfun)));
	      सचे (basic_block_info_for_fn (cfun)->length () <= (size_t)index)
		vec_safe_grow_cleared (basic_block_info_for_fn (cfun),
				       index + 1, सच्च);
	      SET_BASIC_BLOCK_FOR_FN (cfun, index, bb);
	      सचे (last_basic_block_for_fn (cfun) <= index)
		last_basic_block_for_fn (cfun) = index + 1;
	      n_basic_blocks_for_fn (cfun)++;
	      सचे (parser.current_bb->index == ENTRY_BLOCK)
		parser.प्रक्षिप_edge (ENTRY_BLOCK, bb->index, EDGE_FALLTHRU,
				  profile_probability::always ());

	      /* We leave the proper setting to fixup.  */
	      वग्ग loop *loop_father = loops_for_fn (cfun)->वृक्षः_मूलम्;
	      /* If the new block is a loop header, allocate a loop
		 struct.  Fixup will take care of proper placement within
		 the loop tree.  */
	      सचे (is_loop_header_of != -1)
		{
		  सचे (सङ्ख्या_of_loops (cfun) > (unsigned)is_loop_header_of
		      && get_loop (cfun, is_loop_header_of) != रिक्त)
		    {
		      c_parser_error (parser, "duplicate loop header");
		    }
		  अञ्ञथा
		    {
		      वग्ग loop *loop = alloc_loop ();
		      loop->अङ्कः = is_loop_header_of;
		      loop->header = bb;
		      सचे (सङ्ख्या_of_loops (cfun) <= (unsigned)is_loop_header_of)
			vec_safe_grow_cleared (loops_for_fn (cfun)->larray,
					       is_loop_header_of + 1, सच्च);
		      (*loops_for_fn (cfun)->larray)[is_loop_header_of] = loop;
		      flow_loop_वृक्षः_ग्रन्थिः_add (loops_for_fn (cfun)->वृक्षः_मूलम्,
					       loop);
		    }
		  loop_father = get_loop (cfun, is_loop_header_of);
		}
	      bb->loop_father = loop_father;
	      bb->गणनम् = bb_गणनम्;

	      /* Stmts now go to the new block.  */
	      parser.current_bb = bb;
	      भङ्ग;
	    }
	  गच्छ व्यञ्जकम्_stmt;

	पक्ष CPP_SEMICOLON:
	  {
	    /* Empty stmt.  */
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);
	    gimple *nop = gimple_build_nop ();
	    gimple_set_location (nop, loc);
	    gimple_seq_add_stmt_without_update (seq, nop);
	    भङ्ग;
	  }

	पक्ष CPP_CLOSE_PAREN:
	पक्ष CPP_CLOSE_SQUARE:
	  /* Avoid infinite loop in error recovery:
	     c_parser_skip_until_found stops at a closing nesting
	     delimiter without consuming it, but here we need to consume
	     it to proceed further.  */
	  c_parser_error (parser, "expected statement");
	  c_parser_consume_token (parser);
	भङ्ग;

	स्वभाव:
व्यञ्जकम्_stmt:
	  c_parser_gimple_statement (parser, seq);
	  सचे (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	    c_parser_skip_until_found (parser, CPP_SEMICOLON, रिक्त);
	}
    }
  c_parser_consume_token (parser);

  /* Put stmts parsed in the current block.  */
  सचे ((cfun->curr_properties & PROP_cfg)
      && !gimple_seq_empty_p (*seq))
    {
      सचे (!parser.current_bb)
	c_parser_error (parser, "stmts without block");
      अञ्ञथा
	{
	  gimple_stmt_iterator gsi = gsi_start_bb (parser.current_bb);
	  gsi_निवेशय_seq_after_without_update (&gsi, *seq,
					       GSI_CONTINUE_LINKING);
	}
      *seq = रिक्त;
    }

  पटिनिवत्त return_p;
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

स्थिर शून्य
c_parser_gimple_statement (gimple_parser &parser, gimple_seq *seq)
{
  संरचना c_व्यञ्जकम् lhs, rhs;
  gimple *assign = रिक्त;
  location_t loc;
  वृक्षः arg = NULL_वृक्षः;
  auto_vec<वृक्षः> vargs;

  lhs = c_parser_gimple_unary_expression (parser);
  loc = व्यञ्जकम्_LOCATION (lhs.मानम्);
  rhs.set_error ();

  /* GIMPLE call statement without LHS.  */
  सचे (c_parser_next_token_is (parser, CPP_SEMICOLON)
      && वृक्षः_CODE (lhs.मानम्) == CALL_व्यञ्जकम्)
    {
      gimple *call;
      call = gimple_build_call_from_वृक्षः (lhs.मानम्, रिक्त);
      gimple_seq_add_stmt_without_update (seq, call);
      gimple_set_location (call, loc);
      पटिनिवत्त;
    }

  /* All following cases are statements with LHS.  */
  सचे (! c_parser_require (parser, CPP_EQ, "expected %<=%>"))
    पटिनिवत्त;

  /* Eat and ignore {v} right after the =, the has_volatile_ops is
     redundant and re-computed by the operand scanner.  */
  सचे (c_parser_next_token_is (parser, CPP_OPEN_BRACE)
      && !(c_parser_peek_token (parser)->flags & PREV_WHITE)
      && c_parser_peek_2nd_token (parser)->type == CPP_NAME
      && !(c_parser_peek_2nd_token (parser)->flags & PREV_WHITE)
      && strcmp ("v", IDENTIFIER_POINTER
			(c_parser_peek_2nd_token (parser)->मानम्)) == 0
      && c_parser_peek_nth_token (parser, 3)->type == CPP_CLOSE_BRACE
      && !(c_parser_peek_nth_token (parser, 3)->flags & PREV_WHITE))
    {
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }

  /* Cast expression.  */
  सचे (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_typename (c_parser_peek_2nd_token (parser)))
    {
      c_parser_consume_token (parser);
      संरचना c_type_name *type_name = c_parser_type_name (parser);
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      सचे (type_name == रिक्त)
	पटिनिवत्त;
      /* ???  The actual type used in the cast expression is ignored as
         in GIMPLE it is encoded by the type of the LHS.  */
      rhs = c_parser_gimple_postfix_expression (parser);
      सचे (lhs.मानम् != error_mark_ग्रन्थिः
	  && rhs.मानम् != error_mark_ग्रन्थिः)
	{
	  गणना वृक्षः_code code = NOP_व्यञ्जकम्;
	  सचे (FLOAT_TYPE_P (वृक्षः_TYPE (lhs.मानम्))
	      && ! FLOAT_TYPE_P (वृक्षः_TYPE (rhs.मानम्)))
	    code = FLOAT_व्यञ्जकम्;
	  अञ्ञथा सचे (! FLOAT_TYPE_P (वृक्षः_TYPE (lhs.मानम्))
		   && FLOAT_TYPE_P (वृक्षः_TYPE (rhs.मानम्)))
	    code = FIX_TRUNC_व्यञ्जकम्;
	  assign = gimple_build_assign (lhs.मानम्, code, rhs.मानम्);
	  gimple_seq_add_stmt_without_update (seq, assign);
	  gimple_set_location (assign, loc);
	  पटिनिवत्त;
	}
    }

  /* Unary expression.  */
  विकल्प (c_parser_peek_token (parser)->type)
    {
    पक्ष CPP_NAME:
      {
	वृक्षः id = c_parser_peek_token (parser)->मानम्;
	सचे (strcmp (IDENTIFIER_POINTER (id), "__ABS") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__ABSU") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__MIN") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__MAX") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__BIT_INSERT") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__VEC_PERM") == 0)
	  गच्छ build_unary_व्यञ्जकम्;
	भङ्ग;
      }
    पक्ष CPP_KEYWORD:
      सचे (c_parser_peek_token (parser)->keyword != RID_REALPART
	  && c_parser_peek_token (parser)->keyword != RID_IMAGPART)
	भङ्ग;
      /* Fallthru.  */
    पक्ष CPP_AND:
    पक्ष CPP_PLUS:
    पक्ष CPP_MINUS:
    पक्ष CPP_COMPL:
    पक्ष CPP_NOT:
    पक्ष CPP_MULT: /* pointer deref */
    build_unary_व्यञ्जकम्:
      rhs = c_parser_gimple_unary_expression (parser);
      सचे (rhs.मानम् != error_mark_ग्रन्थिः)
	{
	  assign = gimple_build_assign (lhs.मानम्, rhs.मानम्);
	  gimple_set_location (assign, loc);
	  gimple_seq_add_stmt_without_update (seq, assign);
	}
      पटिनिवत्त;

    स्वभाव:;
    }

  /* GIMPLE PHI statement.  */
  सचे (c_parser_next_token_is_keyword (parser, RID_PHI))
    {
      c_parser_consume_token (parser);

      सचे (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	पटिनिवत्त;

      सचे (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	c_parser_consume_token (parser);

      याव (c_parser_next_token_is_not (parser, CPP_CLOSE_PAREN))
	{
	  सचे (c_parser_next_token_is (parser, CPP_NAME)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      arg = c_parser_peek_token (parser)->मानम्;
	      c_parser_consume_token (parser);
	      सचे (c_parser_next_token_is (parser, CPP_COLON))
		c_parser_consume_token (parser);
	      पूर्णाङ्क src_index = -1;
	      सचे (!c_parser_gimple_parse_bb_spec (arg, &src_index))
		c_parser_error (parser, "invalid source block specification");
	      vargs.safe_प्रक्षिप (size_int (src_index));
	    }
	  अञ्ञथा सचे (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  अञ्ञथा
	    {
	      arg = c_parser_gimple_unary_expression (parser).मानम्;
	      vargs.safe_प्रक्षिप (arg);
	    }
	}

      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");

      /* Build internal function for PHI.  */
      gcall *call_stmt = gimple_build_call_internal_vec (IFN_PHI, vargs);
      gimple_call_set_lhs (call_stmt, lhs.मानम्);
      gimple_set_location (call_stmt, UNKNOWN_LOCATION);
      gimple_seq_add_stmt_without_update (seq, call_stmt);
      पटिनिवत्त;
    }

  /* GIMPLE call with lhs.  */
  सचे (c_parser_next_token_is (parser, CPP_DOT)
      || (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN
	  && lookup_name (c_parser_peek_token (parser)->मानम्)))
    {
      rhs = c_parser_gimple_unary_expression (parser);
      सचे (rhs.मानम् != error_mark_ग्रन्थिः)
	{
	  gimple *call = gimple_build_call_from_वृक्षः (rhs.मानम्, रिक्त);
	  gimple_call_set_lhs (call, lhs.मानम्);
	  gimple_seq_add_stmt_without_update (seq, call);
	  gimple_set_location (call, loc);
	}
      पटिनिवत्त;
    }

  rhs = c_parser_gimple_द्विमान_expression (parser, वृक्षः_TYPE (lhs.मानम्));
  सचे (lhs.मानम् != error_mark_ग्रन्थिः
      && rhs.मानम् != error_mark_ग्रन्थिः)
    {
      /* If we parsed an identifier and the next token  is a '?' then parse
	 a conditional expression.  */
      सचे (SSA_VAR_P (rhs.मानम्) && c_parser_next_token_is (parser, CPP_QUERY))
	{
	  संरचना c_व्यञ्जकम् trueval, falseval;
	  c_parser_consume_token (parser);
	  trueval = c_parser_gimple_postfix_expression (parser);
	  falseval.set_error ();
	  सचे (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    falseval = c_parser_gimple_postfix_expression (parser);
	  सचे (trueval.मानम् == error_mark_ग्रन्थिः
	      || falseval.मानम् == error_mark_ग्रन्थिः)
	    पटिनिवत्त;
	  rhs.मानम् = build3_loc (loc,
				  VECTOR_TYPE_P (वृक्षः_TYPE (rhs.मानम्))
				  ? VEC_COND_व्यञ्जकम् : COND_व्यञ्जकम्,
				  वृक्षः_TYPE (trueval.मानम्),
				  rhs.मानम्, trueval.मानम्, falseval.मानम्);
	}
      सचे (get_gimple_rhs_class (वृक्षः_CODE (rhs.मानम्)) == GIMPLE_INVALID_RHS)
	{
	  c_parser_error (parser, "unexpected RHS for assignment");
	  पटिनिवत्त;
	}
      assign = gimple_build_assign (lhs.मानम्, rhs.मानम्);
      gimple_seq_add_stmt_without_update (seq, assign);
      gimple_set_location (assign, loc);
    }
  पटिनिवत्त;
}

/* A mapping between an identifier to a tree code for binary operations. */
स्थिर ध्रुव std::pair<ध्रुव वर्ण *, वृक्षः_code> gimple_द्विमान_identifier_code[] =
  {
    {"__MULT_HIGHPART", MULT_HIGHPART_व्यञ्जकम्},
    {"__UNLT", UNLT_व्यञ्जकम्},
    {"__UNLE", UNLE_व्यञ्जकम्},
    {"__UNGT", UNGT_व्यञ्जकम्},
    {"__UNGE", UNGE_व्यञ्जकम्},
    {"__UNEQ", UNEQ_व्यञ्जकम्},
    {"__UNORDERED", UNORDERED_व्यञ्जकम्},
    {"__ORDERED", ORDERED_व्यञ्जकम्},
    {"__LTGT", LTGT_व्यञ्जकम्},
    {"__FLOOR_DIV", FLOOR_DIV_व्यञ्जकम्},
    {"__ROUND_DIV", ROUND_DIV_व्यञ्जकम्},
    {"__EXACT_DIV", EXACT_DIV_व्यञ्जकम्},
    {"__CEIL_DIV", CEIL_DIV_व्यञ्जकम्},
    {"__FLOOR_MOD", FLOOR_MOD_व्यञ्जकम्},
    {"__ROUND_MOD", ROUND_MOD_व्यञ्जकम्},
    {"__CEIL_MOD", CEIL_MOD_व्यञ्जकम्},
    {"__ROTATE_LEFT", LROTATE_व्यञ्जकम्},
    {"__ROTATE_RIGHT", RROTATE_व्यञ्जकम्},
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

स्थिर c_व्यञ्जकम्
c_parser_gimple_द्विमान_expression (gimple_parser &parser, वृक्षः ret_type)
{
  /* Location of the binary operator.  */
  संरचना c_व्यञ्जकम् ret, lhs, rhs;
  गणना वृक्षः_code code = ERROR_MARK;
  ret.set_error ();
  lhs = c_parser_gimple_postfix_expression (parser, ret_type);
  सचे (c_parser_error (parser))
    पटिनिवत्त ret;
  विकल्प (c_parser_peek_token (parser)->type)
    {
    पक्ष CPP_MULT:
      code = MULT_व्यञ्जकम्;
      भङ्ग;
    पक्ष CPP_DIV:
      code = TRUNC_DIV_व्यञ्जकम्;
      भङ्ग;
    पक्ष CPP_MOD:
      code = TRUNC_MOD_व्यञ्जकम्;
      भङ्ग;
    पक्ष CPP_PLUS:
      सचे (POINTER_TYPE_P (वृक्षः_TYPE (lhs.मानम्)))
	code = POINTER_PLUS_व्यञ्जकम्;
      अञ्ञथा
	code = PLUS_व्यञ्जकम्;
      भङ्ग;
    पक्ष CPP_MINUS:
      सचे (POINTER_TYPE_P (वृक्षः_TYPE (lhs.मानम्)))
	code = POINTER_DIFF_व्यञ्जकम्;
      अञ्ञथा
	code = MINUS_व्यञ्जकम्;
      भङ्ग;
    पक्ष CPP_LSHIFT:
      code = LSHIFT_व्यञ्जकम्;
      भङ्ग;
    पक्ष CPP_RSHIFT:
      code = RSHIFT_व्यञ्जकम्;
      भङ्ग;
    पक्ष CPP_LESS:
      code = LT_व्यञ्जकम्;
      भङ्ग;
    पक्ष CPP_GREATER:
      code = GT_व्यञ्जकम्;
      भङ्ग;
    पक्ष CPP_LESS_EQ:
      code = LE_व्यञ्जकम्;
      भङ्ग;
    पक्ष CPP_GREATER_EQ:
      code = GE_व्यञ्जकम्;
      भङ्ग;
    पक्ष CPP_EQ_EQ:
      code = EQ_व्यञ्जकम्;
      भङ्ग;
    पक्ष CPP_NOT_EQ:
      code = NE_व्यञ्जकम्;
      भङ्ग;
    पक्ष CPP_AND:
      code = BIT_AND_व्यञ्जकम्;
      भङ्ग;
    पक्ष CPP_XOR:
      code = BIT_XOR_व्यञ्जकम्;
      भङ्ग;
    पक्ष CPP_OR:
      code = BIT_IOR_व्यञ्जकम्;
      भङ्ग;
    पक्ष CPP_AND_AND:
      c_parser_error (parser, "%<&&%> not valid in GIMPLE");
      पटिनिवत्त ret;
    पक्ष CPP_OR_OR:
      c_parser_error (parser, "%<||%> not valid in GIMPLE");
      पटिनिवत्त ret;
    पक्ष CPP_NAME:
      {
	वृक्षः id = c_parser_peek_token (parser)->मानम्;
	अत्थाय (auto &p : gimple_द्विमान_identifier_code)
	  {
	    सचे (strcmp (IDENTIFIER_POINTER (id), p.first) == 0)
	      {
		code = p.second;
		भङ्ग;
	      }
	  }
	सचे (code != ERROR_MARK)
	  भङ्ग;
      }
      /* Fallthru.  */
    स्वभाव:
      /* Not a binary expression.  */
      पटिनिवत्त lhs;
    }
  location_t ret_loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  rhs = c_parser_gimple_postfix_expression (parser);
  सचे (lhs.मानम् != error_mark_ग्रन्थिः && rhs.मानम् != error_mark_ग्रन्थिः)
    ret.मानम् = build2_loc (ret_loc, code, ret_type, lhs.मानम्, rhs.मानम्);
  पटिनिवत्त ret;
}

/* Parse a gimple parentized binary expression.  */

स्थिर c_व्यञ्जकम्
c_parser_gimple_parentized_द्विमान_expression (gimple_parser &parser,
					      location_t op_loc,
					      वृक्षः_code code)
{
  संरचना c_व्यञ्जकम् ret;
  ret.set_error ();

  c_parser_consume_token (parser);
  सचे (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    पटिनिवत्त ret;
  c_व्यञ्जकम् op1 = c_parser_gimple_postfix_expression (parser);
  सचे (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    पटिनिवत्त ret;
  c_व्यञ्जकम् op2 = c_parser_gimple_postfix_expression (parser);
  सचे (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    पटिनिवत्त ret;

  सचे (op1.मानम् != error_mark_ग्रन्थिः && op2.मानम् != error_mark_ग्रन्थिः)
    ret.मानम् = build2_loc (op_loc,
			    code, वृक्षः_TYPE (op1.मानम्), op1.मानम्, op2.मानम्);
  पटिनिवत्त ret;
}

/* Parse a gimple parentized binary expression.  */

स्थिर c_व्यञ्जकम्
c_parser_gimple_parentized_ternary_expression (gimple_parser &parser,
					       location_t op_loc,
					       वृक्षः_code code)
{
  संरचना c_व्यञ्जकम् ret;
  ret.set_error ();

  c_parser_consume_token (parser);
  सचे (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    पटिनिवत्त ret;
  c_व्यञ्जकम् op1 = c_parser_gimple_postfix_expression (parser);
  सचे (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    पटिनिवत्त ret;
  c_व्यञ्जकम् op2 = c_parser_gimple_postfix_expression (parser);
  सचे (!c_parser_require (parser, CPP_COMMA, "expected %<)%>"))
    पटिनिवत्त ret;
  c_व्यञ्जकम् op3 = c_parser_gimple_postfix_expression (parser);
  सचे (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    पटिनिवत्त ret;

  सचे (op1.मानम् != error_mark_ग्रन्थिः
      && op2.मानम् != error_mark_ग्रन्थिः
      && op3.मानम् != error_mark_ग्रन्थिः)
    ret.मानम् = build3_loc (op_loc,
			    code, वृक्षः_TYPE (op1.मानम्),
			    op1.मानम्, op2.मानम्, op3.मानम्);
  पटिनिवत्त ret;
}

/* Parse gimple unary expression.

   gimple-unary-expression:
     gimple-postfix-expression
     unary-operator gimple-postfix-expression

   unary-operator: one of
     & * + - ~ abs_expr
*/

स्थिर c_व्यञ्जकम्
c_parser_gimple_unary_expression (gimple_parser &parser)
{
  संरचना c_व्यञ्जकम् ret, op;
  location_t op_loc = c_parser_peek_token (parser)->location;
  location_t finish;
  ret.set_error ();
  विकल्प (c_parser_peek_token (parser)->type)
    {
    पक्ष CPP_AND:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      mark_exp_read (op.मानम्);
      पटिनिवत्त gimple_parser_build_unary_op (op_loc, ADDR_व्यञ्जकम्, op);
    पक्ष CPP_MULT:
      {
	c_parser_consume_token (parser);
	op = c_parser_gimple_postfix_expression (parser);
	सचे (op.मानम् == error_mark_ग्रन्थिः)
	  पटिनिवत्त ret;
	सचे (! POINTER_TYPE_P (वृक्षः_TYPE (op.मानम्)))
	  {
	    error_at (op_loc, "expected pointer as argument of unary %<*%>");
	    पटिनिवत्त ret;
	  }
	finish = op.get_finish ();
	location_t combined_loc = make_location (op_loc, op_loc, finish);
	ret.मानम् = build_simple_mem_ref_loc (combined_loc, op.मानम्);
	वृक्षः_SIDE_EFFECTS (ret.मानम्)
	  = वृक्षः_THIS_VOLATILE (ret.मानम्)
	  = TYPE_VOLATILE (वृक्षः_TYPE (वृक्षः_TYPE (op.मानम्)));
	ret.src_range.m_start = op_loc;
	ret.src_range.m_finish = finish;
	पटिनिवत्त ret;
      }
    पक्ष CPP_PLUS:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      पटिनिवत्त gimple_parser_build_unary_op (op_loc, CONVERT_व्यञ्जकम्, op);
    पक्ष CPP_MINUS:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      पटिनिवत्त gimple_parser_build_unary_op (op_loc, NEGATE_व्यञ्जकम्, op);
    पक्ष CPP_COMPL:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      पटिनिवत्त gimple_parser_build_unary_op (op_loc, BIT_NOT_व्यञ्जकम्, op);
    पक्ष CPP_NOT:
      c_parser_error (parser, "%<!%> not valid in GIMPLE");
      पटिनिवत्त ret;
    पक्ष CPP_KEYWORD:
      विकल्प (c_parser_peek_token (parser)->keyword)
	{
	पक्ष RID_REALPART:
	  c_parser_consume_token (parser);
	  op = c_parser_gimple_postfix_expression (parser);
	  पटिनिवत्त gimple_parser_build_unary_op (op_loc, REALPART_व्यञ्जकम्, op);
	पक्ष RID_IMAGPART:
	  c_parser_consume_token (parser);
	  op = c_parser_gimple_postfix_expression (parser);
	  पटिनिवत्त gimple_parser_build_unary_op (op_loc, IMAGPART_व्यञ्जकम्, op);
	स्वभाव:
	  पटिनिवत्त c_parser_gimple_postfix_expression (parser);
	}
    पक्ष CPP_NAME:
	{
	  वृक्षः id = c_parser_peek_token (parser)->मानम्;
	  सचे (strcmp (IDENTIFIER_POINTER (id), "__ABS") == 0)
	    {
	      c_parser_consume_token (parser);
	      op = c_parser_gimple_postfix_expression (parser);
	      पटिनिवत्त gimple_parser_build_unary_op (op_loc, ABS_व्यञ्जकम्, op);
	    }
	  अञ्ञथा सचे (strcmp (IDENTIFIER_POINTER (id), "__ABSU") == 0)
	    {
	      c_parser_consume_token (parser);
	      op = c_parser_gimple_postfix_expression (parser);
	      पटिनिवत्त gimple_parser_build_unary_op (op_loc, ABSU_व्यञ्जकम्, op);
	    }
	  अञ्ञथा सचे (strcmp (IDENTIFIER_POINTER (id), "__MIN") == 0)
	    पटिनिवत्त c_parser_gimple_parentized_द्विमान_expression (parser,
								 op_loc,
								 MIN_व्यञ्जकम्);
	  अञ्ञथा सचे (strcmp (IDENTIFIER_POINTER (id), "__MAX") == 0)
	    पटिनिवत्त c_parser_gimple_parentized_द्विमान_expression (parser,
								 op_loc,
								 MAX_व्यञ्जकम्);
	  अञ्ञथा सचे (strcmp (IDENTIFIER_POINTER (id), "__VEC_PERM") == 0)
	    पटिनिवत्त c_parser_gimple_parentized_ternary_expression
			(parser, op_loc, VEC_PERM_व्यञ्जकम्);
	  अञ्ञथा सचे (strcmp (IDENTIFIER_POINTER (id), "__BIT_INSERT") == 0)
	    {
	      /* __BIT_INSERT '(' postfix-expression, postfix-expression,
			          integer ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      सचे (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_व्यञ्जकम् op0 = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_व्यञ्जकम् op1 = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_व्यञ्जकम् op2 = c_parser_gimple_postfix_expression (parser);
		  सचे (वृक्षः_CODE (op2.मानम्) != INTEGER_CST
		      || !int_fits_type_p (op2.मानम्, bitsizetype))
		    c_parser_error (parser, "expected constant offset");
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  सचे (op0.मानम् != error_mark_ग्रन्थिः
		      && op1.मानम् != error_mark_ग्रन्थिः
		      && वृक्षः_CODE (op2.मानम्) == INTEGER_CST)
		    ret.मानम् = build3_loc (loc, BIT_निवेशय_व्यञ्जकम्,
					    वृक्षः_TYPE (op0.मानम्),
					    op0.मानम्, op1.मानम्,
					    fold_convert (bitsizetype,
							  op2.मानम्));
		}
	      पटिनिवत्त ret;
	    }
	  अञ्ञथा
	    पटिनिवत्त c_parser_gimple_postfix_expression (parser);
	}
    स्वभाव:
      पटिनिवत्त c_parser_gimple_postfix_expression (parser);
    }
}

/* Decompose ID into base name (ID until ver_offset) and VERSION.  Return
   true if ID matches a SSA name.  */

स्थिर तार्किक
c_parser_parse_ssa_name_id (वृक्षः id, unsigned *version, unsigned *ver_offset)
{
  ध्रुव वर्ण *token = IDENTIFIER_POINTER (id);
  ध्रुव वर्ण *var_version = strrchr (token, '_');
  सचे (! var_version)
    पटिनिवत्त मिच्छा;

  *ver_offset = var_version - token;
  अत्थाय (ध्रुव वर्ण *p = var_version + 1; *p; ++p)
    सचे (! ISDIGIT (*p))
      पटिनिवत्त मिच्छा;
  *version = atoi (var_version + 1);
  पटिनिवत्त *version > 0;
}

/* Get at the actual SSA name ID with VERSION starting at VER_OFFSET.
   TYPE is the type if the SSA name is being declared.  */

स्थिर वृक्षः
c_parser_parse_ssa_name (gimple_parser &parser,
			 वृक्षः id, वृक्षः type, unsigned version,
			 unsigned ver_offset)
{
  वृक्षः name = NULL_वृक्षः;
  ध्रुव वर्ण *token = IDENTIFIER_POINTER (id);

  सचे (ver_offset == 0)
    {
      /* Anonymous unnamed SSA name.  */
      सचे (version < अङ्कः_ssa_names)
	name = ssa_name (version);
      सचे (! name)
	{
	  सचे (! type)
	    {
	      c_parser_error (parser, "SSA name undeclared");
	      पटिनिवत्त error_mark_ग्रन्थिः;
	    }
	  name = make_ssa_name_fn (cfun, type, रिक्त, version);
	}
    }
  अञ्ञथा
    {
      सचे (version < अङ्कः_ssa_names)
	name = ssa_name (version);
      सचे (! name)
	{
	  /* Separate var name from version.  */
	  वर्ण *var_name = XNEWVEC (वर्ण, ver_offset + 1);
	  memcpy (var_name, token, ver_offset);
	  var_name[ver_offset] = '\0';
	  /* lookup for parent decl.  */
	  id = get_identifier (var_name);
	  वृक्षः parent = lookup_name (id);
	  XDELETEVEC (var_name);
	  सचे (! parent || parent == error_mark_ग्रन्थिः)
	    {
	      c_parser_error (parser, "base variable or SSA name undeclared");
	      पटिनिवत्त error_mark_ग्रन्थिः;
	    }
	  सचे (!(VAR_P (parent)
		|| वृक्षः_CODE (parent) == PARM_DECL
		|| वृक्षः_CODE (parent) == RESULT_DECL))
	    {
	      error ("invalid base %qE for SSA name", parent);
	      पटिनिवत्त error_mark_ग्रन्थिः;
	    }
	  name = make_ssa_name_fn (cfun, parent,
				   gimple_build_nop (), version);
	}
    }

  पटिनिवत्त name;
}

/* Parse a gimple call to an internal function.

   gimple-call-internal:
     . identifier ( gimple-argument-expression-list[opt] )  */

स्थिर संरचना c_व्यञ्जकम्
c_parser_gimple_call_internal (gimple_parser &parser)
{
  संरचना c_व्यञ्जकम् व्यञ्जकम्;
  व्यञ्जकम्.set_error ();

  gcc_assert (c_parser_next_token_is (parser, CPP_DOT));
  c_parser_consume_token (parser);
  location_t loc = c_parser_peek_token (parser)->location;
  सचे (!c_parser_next_token_is (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_kind != C_ID_ID)
    {
      c_parser_error (parser, "expecting internal function name");
      पटिनिवत्त व्यञ्जकम्;
    }
  वृक्षः id = c_parser_peek_token (parser)->मानम्;
  internal_fn ifn = lookup_internal_fn (IDENTIFIER_POINTER (id));
  c_parser_consume_token (parser);
  सचे (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    {
      auto_vec<वृक्षः> exprlist;
      सचे (!c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_gimple_व्यञ्जकम्_list (parser, &exprlist);
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      सचे (ifn == IFN_LAST)
	error_at (loc, "unknown internal function %qE", id);
      अञ्ञथा
	{
	  व्यञ्जकम्.मानम् = build_call_व्यञ्जकम्_internal_loc_array
	    (loc, ifn, void_type_ग्रन्थिः, exprlist.length (),
	     exprlist.address ());
	  व्यञ्जकम्.original_code = ERROR_MARK;
	  व्यञ्जकम्.original_type = रिक्त;
	  व्यञ्जकम्.m_decimal = 0;
	}
    }
  पटिनिवत्त व्यञ्जकम्;
}

/* Parse '<' type [',' alignment] '>' and return a type on success
   and NULL_TREE on error.  */

स्थिर वृक्षः
c_parser_gimple_typespec (gimple_parser &parser)
{
  संरचना c_type_name *type_name = रिक्त;
  वृक्षः alignment = NULL_वृक्षः;
  सचे (c_parser_require (parser, CPP_LESS, "expected %<<%>"))
    {
      type_name = c_parser_type_name (parser);
      /* Optional alignment.  */
      सचे (c_parser_next_token_is (parser, CPP_COMMA))
	{
	  c_parser_consume_token (parser);
	  alignment
	      = c_parser_gimple_postfix_expression (parser).मानम्;
	}
      c_parser_skip_until_found (parser,
				 CPP_GREATER, "expected %<>%>");
    }
  सचे (!type_name)
    पटिनिवत्त NULL_वृक्षः;
  वृक्षः tem;
  वृक्षः type = groktypename (type_name, &tem, रिक्त);
  सचे (alignment)
    type = build_aligned_type (type, वृक्षः_to_uhwi (alignment));
  पटिनिवत्त type;
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

स्थिर संरचना c_व्यञ्जकम्
c_parser_gimple_postfix_expression (gimple_parser &parser, वृक्षः ret_type)
{
  location_t loc = c_parser_peek_token (parser)->location;
  source_range tok_range = c_parser_peek_token (parser)->get_range ();
  संरचना c_व्यञ्जकम् व्यञ्जकम्;
  व्यञ्जकम्.set_error ();
  विकल्प (c_parser_peek_token (parser)->type)
    {
    पक्ष CPP_सङ्ख्या:
      व्यञ्जकम्.मानम् = c_parser_peek_token (parser)->मानम्;
      set_c_व्यञ्जकम्_source_range (&व्यञ्जकम्, tok_range);
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      भङ्ग;
    पक्ष CPP_CHAR:
    पक्ष CPP_CHAR16:
    पक्ष CPP_CHAR32:
    पक्ष CPP_UTF8CHAR:
    पक्ष CPP_WCHAR:
      व्यञ्जकम्.मानम् = c_parser_peek_token (parser)->मानम्;
      set_c_व्यञ्जकम्_source_range (&व्यञ्जकम्, tok_range);
      c_parser_consume_token (parser);
      भङ्ग;
    पक्ष CPP_STRING:
    पक्ष CPP_STRING16:
    पक्ष CPP_STRING32:
    पक्ष CPP_WSTRING:
    पक्ष CPP_UTF8STRING:
      व्यञ्जकम् = c_parser_string_literal (parser, मिच्छा, सच्च);
      भङ्ग;
    पक्ष CPP_DOT:
      व्यञ्जकम् = c_parser_gimple_call_internal (parser);
      भङ्ग;
    पक्ष CPP_NAME:
      सचे (c_parser_peek_token (parser)->id_kind == C_ID_ID)
	{
	  वृक्षः id = c_parser_peek_token (parser)->मानम्;
	  सचे (strcmp (IDENTIFIER_POINTER (id), "__MEM") == 0)
	    {
	      /* __MEM '<' type-name [ ',' number ] '>'
	               '(' [ '(' type-name ')' ] unary-expression
			   [ '+' number ]
			   [ ',' number ]
			   [ ',' number ':' number ] ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      वृक्षः type = c_parser_gimple_typespec (parser);
	      संरचना c_व्यञ्जकम् ptr, alias_off, step, index, index2;
	      ptr.मानम् = error_mark_ग्रन्थिः;
	      alias_off.मानम् = NULL_वृक्षः;
	      step.मानम् = NULL_वृक्षः;
	      index.मानम् = NULL_वृक्षः;
	      index2.मानम् = NULL_वृक्षः;
	      unsigned short clique = 0;
	      unsigned short base = 0;
	      तार्किक reverse_order = मिच्छा;
	      संरचना c_व्यञ्जकम् ro;
	      सचे (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  वृक्षः alias_type = NULL_वृक्षः;
		  /* Optional alias-type cast.  */
		  सचे (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
		    {
		      c_parser_consume_token (parser);
		      संरचना c_type_name *alias_type_name
			= c_parser_type_name (parser);
		      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
						 "expected %<)%>");
		      सचे (alias_type_name)
			{
			  वृक्षः tem;
			  alias_type = groktypename (alias_type_name,
						     &tem, रिक्त);
			}
		    }
		  ptr = c_parser_gimple_unary_expression (parser);
		  सचे (ptr.मानम् == error_mark_ग्रन्थिः
		      || ! POINTER_TYPE_P (वृक्षः_TYPE (ptr.मानम्)))
		    {
		      सचे (ptr.मानम् != error_mark_ग्रन्थिः)
			error_at (ptr.get_start (),
				  "invalid type of %<__MEM%> operand");
		      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
						 "expected %<)%>");
		      पटिनिवत्त व्यञ्जकम्;
		    }
		  सचे (! alias_type)
		    alias_type = वृक्षः_TYPE (ptr.मानम्);
		  /* Optional constant offset.  */
		  सचे (c_parser_next_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      alias_off = c_parser_gimple_postfix_expression (parser);
		    }
		  सचे (c_parser_next_token_is (parser, CPP_MULT))
		    {
		      std::swap (index, alias_off);
		      c_parser_consume_token (parser);
		      step = c_parser_gimple_postfix_expression (parser);
		    }
		  अञ्ञथा सचे (c_parser_next_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      index = c_parser_gimple_postfix_expression (parser);
		      सचे (c_parser_next_token_is (parser, CPP_MULT))
			{
			  c_parser_consume_token (parser);
			  step = c_parser_gimple_postfix_expression (parser);
			}
		      अञ्ञथा
			std::swap (index, index2);
		    }
		  अञ्ञथा सचे (alias_off.मानम्
			   && वृक्षः_CODE (alias_off.मानम्) != INTEGER_CST)
		    std::swap (alias_off, index2);
		  सचे (c_parser_next_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      index2 = c_parser_gimple_postfix_expression (parser);
		    }
		  सचे (alias_off.मानम्)
		    {
		      सचे (वृक्षः_CODE (alias_off.मानम्) != INTEGER_CST)
			error_at (alias_off.get_start (),
				  "expected constant offset for %<__MEM%> "
				  "operand");
		      alias_off.मानम् = fold_convert (alias_type,
						      alias_off.मानम्);
		    }
		  अञ्ञथा
		    alias_off.मानम् = build_int_cst (alias_type, 0);
		  सचे (step.मानम्)
		    {
		      सचे (वृक्षः_CODE (step.मानम्) != INTEGER_CST)
			error_at (step.get_start (),
				  "expected constant step for %<__MEM%> "
				  "operand");
		    }
		  सचे (c_parser_next_token_is (parser, CPP_COMMA))
		    {
		      संरचना c_व्यञ्जकम् cl, ba;
		      तार्किक has_clb = सच्च;
		      c_parser_consume_token (parser);
		      cl = c_parser_gimple_postfix_expression (parser);
		      सचे (!c_parser_next_token_is (parser, CPP_COLON))
			{
			  ro = cl;
			  unsigned HOST_WIDE_INT tmp = 0;
			  सचे (!वृक्षः_fits_uhwi_p (ro.मानम्)
			      || (tmp = वृक्षः_to_uhwi (ro.मानम्)) > 1)
			    error_at (ro.get_start (),
				      "invalid reverse order value");
			  reverse_order = tmp;
			  has_clb = मिच्छा;
			  सचे (c_parser_next_token_is (parser, CPP_COMMA))
			    {
			      c_parser_consume_token (parser);
			      cl = c_parser_gimple_postfix_expression (parser);
		              has_clb = सच्च;
			    }
			}
		      सचे (has_clb
			  && c_parser_require (parser,
					       CPP_COLON, "expected %<:%>"))
			{
			  ba = c_parser_gimple_postfix_expression (parser);
			  सचे (!वृक्षः_fits_uhwi_p (cl.मानम्)
			      || !वृक्षः_fits_uhwi_p (ba.मानम्)
			      || compare_वृक्षः_int (cl.मानम्,
						   (clique = वृक्षः_to_uhwi
								(cl.मानम्)))
			      || compare_वृक्षः_int (ba.मानम्,
						   (base = वृक्षः_to_uhwi
								 (ba.मानम्))))
			    error_at (cl.get_start (),
				      "invalid clique/base pair");
			}
		    }
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      सचे (! type || c_parser_error (parser))
		{
		  c_parser_set_error (parser, मिच्छा);
		  पटिनिवत्त व्यञ्जकम्;
		}
	      सचे (index.मानम् || step.मानम् || index2.मानम्)
		व्यञ्जकम्.मानम् = build5_loc (loc, TARGET_MEM_REF,
					 type, ptr.मानम्, alias_off.मानम्,
					 index.मानम्, step.मानम्, index2.मानम्);
	      अञ्ञथा
		व्यञ्जकम्.मानम् = build2_loc (loc, MEM_REF,
					 type, ptr.मानम्, alias_off.मानम्);
	      सचे (clique != 0)
		{
		  cfun->last_clique = MAX (cfun->last_clique, clique);
		  MR_DEPENDENCE_CLIQUE (व्यञ्जकम्.मानम्) = clique;
		  MR_DEPENDENCE_BASE (व्यञ्जकम्.मानम्) = base;
		}
	      सचे (reverse_order)
		{
		  सचे (वृक्षः_CODE (व्यञ्जकम्.मानम्) == MEM_REF)
		    REF_REVERSE_STORAGE_ORDER (व्यञ्जकम्.मानम्) = reverse_order;
		  अञ्ञथा
		    error_at (ro.get_start (),
			      "target mem ref cannot have reverse order");
		}
	      भङ्ग;
	    }
	  अञ्ञथा सचे (strcmp (IDENTIFIER_POINTER (id), "__VIEW_CONVERT") == 0)
	    {
	      /* __VIEW_CONVERT '<' type-name [ ',' number ] '>'
	                        '(' postfix-expression ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      वृक्षः type = c_parser_gimple_typespec (parser);
	      सचे (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_व्यञ्जकम् op = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  सचे (type && op.मानम् != error_mark_ग्रन्थिः)
		    व्यञ्जकम्.मानम् = build1_loc (loc, VIEW_CONVERT_व्यञ्जकम्,
					     type, op.मानम्);
		}
	      भङ्ग;
	    }
	  अञ्ञथा सचे (strcmp (IDENTIFIER_POINTER (id), "__BIT_FIELD_REF") == 0)
	    {
	      /* __BIT_FIELD_REF '<' type-name [ ',' number ] '>'
	                        '(' postfix-expression, integer, integer ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      वृक्षः type = c_parser_gimple_typespec (parser);
	      सचे (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_व्यञ्जकम् op0 = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_व्यञ्जकम् op1 = c_parser_gimple_postfix_expression (parser);
		  सचे (वृक्षः_CODE (op1.मानम्) != INTEGER_CST
		      || !int_fits_type_p (op1.मानम्, bitsizetype))
		    c_parser_error (parser, "expected constant size");
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_व्यञ्जकम् op2 = c_parser_gimple_postfix_expression (parser);
		  सचे (वृक्षः_CODE (op2.मानम्) != INTEGER_CST
		      || !int_fits_type_p (op2.मानम्, bitsizetype))
		    c_parser_error (parser, "expected constant offset");
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  सचे (type
		      && op0.मानम् != error_mark_ग्रन्थिः
		      && वृक्षः_CODE (op1.मानम्) == INTEGER_CST
		      && वृक्षः_CODE (op2.मानम्) == INTEGER_CST)
		    व्यञ्जकम्.मानम् = build3_loc (loc, BIT_FIELD_REF, type,
					     op0.मानम्,
					     fold_convert (bitsizetype,
							   op1.मानम्),
					     fold_convert (bitsizetype,
							   op2.मानम्));
		}
	      भङ्ग;
	    }
	  अञ्ञथा सचे (strcmp (IDENTIFIER_POINTER (id), "__CLOBBER") == 0)
	    {
	      /* __CLOBBER [ '(' bob | eob | bos | eos ')' ]  */
	      clobber_kind kind = CLOBBER_UNDEF;
	      c_parser_consume_token (parser);
	      सचे (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
		{
		  c_parser_consume_token (parser);
		  auto tok = c_parser_peek_token (parser);
		  सचे (c_parser_require (parser, CPP_NAME,
					"expected clobber kind"))
		    {
		      ध्रुव वर्ण *kind_str = IDENTIFIER_POINTER (tok->मानम्);
		      सचे (strcmp (kind_str, "bos") == 0)
			kind = CLOBBER_STORAGE_BEGIN;
		      अञ्ञथा सचे (strcmp (kind_str, "bob") == 0)
			kind = CLOBBER_OBJECT_BEGIN;
		      अञ्ञथा सचे (strcmp (kind_str, "eob") == 0)
			kind = CLOBBER_OBJECT_END;
		      अञ्ञथा सचे (strcmp (kind_str, "eos") == 0)
			kind = CLOBBER_STORAGE_END;
		      अञ्ञथा
			c_parser_error (parser, "expected one of %<bos%>, "
					"%<eos%>, %<bob>, %<eob%>");
		    }
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      /* We infer the (redundant) type from the LHS.  */
	      व्यञ्जकम्.मानम् = build_clobber (ret_type, kind);
	      भङ्ग;
	    }
	  अञ्ञथा सचे (strcmp (IDENTIFIER_POINTER (id), "_Literal") == 0)
	    {
	      /* _Literal '(' type-name ')' ( [ '-' ] constant | constructor ) */
	      c_parser_consume_token (parser);
	      वृक्षः type = NULL_वृक्षः;
	      सचे (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  संरचना c_type_name *type_name = c_parser_type_name (parser);
		  वृक्षः tem;
		  सचे (type_name)
		    type = groktypename (type_name, &tem, रिक्त);
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      सचे (! type)
		{
		  c_parser_error (parser, "invalid _Literal");
		  पटिनिवत्त व्यञ्जकम्;
		}
	      सचे (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
		{
		  c_parser_consume_token (parser);
		  सचे (!AGGREGATE_TYPE_P (type)
		      && !VECTOR_TYPE_P (type))
		    {
		      c_parser_error (parser, "invalid type for _Literal with "
				      "constructor");
		      c_parser_skip_until_found (parser, CPP_CLOSE_BRACE,
						 "expected %<}%>");
		      पटिनिवत्त व्यञ्जकम्;
		    }
		  vec<constructor_elt, va_gc> *v = रिक्त;
		  तार्किक constant_p = सच्च;
		  सचे (VECTOR_TYPE_P (type)
		      && !c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
		    {
		      vec_alloc (v, TYPE_VECTOR_SUBPARTS (type).to_constant ());
		      करोहि
			{
			  वृक्षः val
			    = c_parser_gimple_postfix_expression (parser).मानम्;
			  सचे (! val
			      || val == error_mark_ग्रन्थिः
			      || (! CONSTANT_CLASS_P (val)
				  && ! SSA_VAR_P (val)))
			    {
			      c_parser_error (parser, "invalid _Literal");
			      पटिनिवत्त व्यञ्जकम्;
			    }
			  CONSTRUCTOR_APPEND_ELT (v, NULL_वृक्षः, val);
			  सचे (! CONSTANT_CLASS_P (val))
			    constant_p = मिच्छा;
			  सचे (c_parser_next_token_is (parser, CPP_COMMA))
			    c_parser_consume_token (parser);
			  अञ्ञथा
			    भङ्ग;
			}
		      याव (1);
		    }
		  सचे (c_parser_require (parser, CPP_CLOSE_BRACE,
					"expected %<}%>"))
		    {
		      सचे (v && constant_p)
			व्यञ्जकम्.मानम् = build_vector_from_ctor (type, v);
		      अञ्ञथा
			व्यञ्जकम्.मानम् = build_constructor (type, v);
		    }
		  अञ्ञथा
		    {
		      c_parser_skip_until_found (parser, CPP_CLOSE_BRACE,
						 "expected %<}%>");
		      पटिनिवत्त व्यञ्जकम्;
		    }
		}
	      अञ्ञथा
		{
		  तार्किक neg_p, addr_p;
		  सचे ((neg_p = c_parser_next_token_is (parser, CPP_MINUS)))
		    c_parser_consume_token (parser);
		  सचे ((addr_p = c_parser_next_token_is (parser, CPP_AND)))
		    c_parser_consume_token (parser);
		  वृक्षः val = c_parser_gimple_postfix_expression (parser).मानम्;
		  सचे (! val
		      || val == error_mark_ग्रन्थिः
		      || (!CONSTANT_CLASS_P (val) && !addr_p))
		    {
		      c_parser_error (parser, "invalid _Literal");
		      पटिनिवत्त व्यञ्जकम्;
		    }
		  सचे (addr_p)
		    {
		      val = build1 (ADDR_व्यञ्जकम्, type, val);
		      सचे (!is_gimple_invariant_address (val))
			{
			  c_parser_error (parser, "invalid _Literal");
			  पटिनिवत्त व्यञ्जकम्;
			}
		    }
		  सचे (neg_p)
		    {
		      val = const_unop (NEGATE_व्यञ्जकम्, वृक्षः_TYPE (val), val);
		      सचे (! val)
			{
			  c_parser_error (parser, "invalid _Literal");
			  पटिनिवत्त व्यञ्जकम्;
			}
		    }
		  व्यञ्जकम्.मानम् = fold_convert (type, val);
		}
	      पटिनिवत्त व्यञ्जकम्;
	    }

	  /* SSA name.  */
	  unsigned version, ver_offset;
	  सचे (! lookup_name (id)
	      && c_parser_parse_ssa_name_id (id, &version, &ver_offset))
	    {
	      c_parser_consume_token (parser);
	      व्यञ्जकम्.मानम् = c_parser_parse_ssa_name (parser, id, NULL_वृक्षः,
						    version, ver_offset);
	      सचे (व्यञ्जकम्.मानम् == error_mark_ग्रन्थिः)
		पटिनिवत्त व्यञ्जकम्;
	      set_c_व्यञ्जकम्_source_range (&व्यञ्जकम्, tok_range);
	      /* For default definition SSA names.  */
	      सचे (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
		  && c_parser_peek_2nd_token (parser)->type == CPP_NAME
		  && strcmp ("D",
			     IDENTIFIER_POINTER
			       (c_parser_peek_2nd_token (parser)->मानम्)) == 0
		  && c_parser_peek_nth_token (parser, 3)->type == CPP_CLOSE_PAREN)
		{
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		  सचे (! SSA_NAME_IS_DEFAULT_DEF (व्यञ्जकम्.मानम्))
		    {
		      सचे (!SSA_NAME_VAR (व्यञ्जकम्.मानम्))
			{
			  error_at (loc, "anonymous SSA name cannot have"
				    " default definition");
			  व्यञ्जकम्.मानम् = error_mark_ग्रन्थिः;
			  पटिनिवत्त व्यञ्जकम्;
			}
		      set_ssa_default_def (cfun, SSA_NAME_VAR (व्यञ्जकम्.मानम्),
					   व्यञ्जकम्.मानम्);
		      SSA_NAME_DEF_STMT (व्यञ्जकम्.मानम्) = gimple_build_nop ();
		    }
		}
	    }
	  अञ्ञथा
	    {
	      c_parser_consume_token (parser);
	      व्यञ्जकम्.मानम्
		= build_external_ref (loc, id,
				      (c_parser_peek_token (parser)->type
				       == CPP_OPEN_PAREN), &व्यञ्जकम्.original_type);
	      set_c_व्यञ्जकम्_source_range (&व्यञ्जकम्, tok_range);
	    }
	  भङ्ग;
	}
      /* Fallthru.  */
    स्वभाव:
      c_parser_error (parser, "expected expression");
      व्यञ्जकम्.set_error ();
      भङ्ग;
    }
  सचे (व्यञ्जकम्.मानम् == error_mark_ग्रन्थिः)
    पटिनिवत्त व्यञ्जकम्;
  पटिनिवत्त c_parser_gimple_postfix_expression_after_primary
    (parser, व्यञ्जकम्_LOC_OR_LOC (व्यञ्जकम्.मानम्, loc), व्यञ्जकम्);
}

/* Parse a gimple postfix expression after the initial primary or compound
   literal.  */

स्थिर संरचना c_व्यञ्जकम्
c_parser_gimple_postfix_expression_after_primary (gimple_parser &parser,
						  location_t व्यञ्जकम्_loc,
						  संरचना c_व्यञ्जकम् व्यञ्जकम्)
{
  location_t start;
  location_t finish;
  वृक्षः ident;
  location_t comp_loc;

  याव (सच्च)
    {
      location_t op_loc = c_parser_peek_token (parser)->location;
      विकल्प (c_parser_peek_token (parser)->type)
	{
	पक्ष CPP_OPEN_SQUARE:
	  {
	    c_parser_consume_token (parser);
	    वृक्षः idx = c_parser_gimple_unary_expression (parser).मानम्;

	    सचे (! c_parser_require (parser, CPP_CLOSE_SQUARE, "expected %<]%>"))
	      {
		c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE, रिक्त);
		भङ्ग;
	      }

	    start = व्यञ्जकम्.get_start ();
	    finish = c_parser_tokens_buf (parser, 0)->location;
	    व्यञ्जकम्.मानम् = build_array_ref (op_loc, व्यञ्जकम्.मानम्, idx);
	    set_c_व्यञ्जकम्_source_range (&व्यञ्जकम्, start, finish);
	    व्यञ्जकम्.m_decimal = 0;

	    व्यञ्जकम्.original_code = ERROR_MARK;
	    व्यञ्जकम्.original_type = रिक्त;
	    भङ्ग;
	  }
	पक्ष CPP_OPEN_PAREN:
	  {
	    /* Function call.  */
	    c_parser_consume_token (parser);
	    auto_vec<वृक्षः> exprlist;
	    सचे (! c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	      c_parser_gimple_व्यञ्जकम्_list (parser, &exprlist);
	    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    सचे (!FUNC_OR_METHOD_TYPE_P (वृक्षः_TYPE (व्यञ्जकम्.मानम्)))
	      {
		c_parser_error (parser, "invalid call to non-function");
		व्यञ्जकम्.set_error ();
		भङ्ग;
	      }
	    व्यञ्जकम्.मानम् = build_call_array_loc
		(व्यञ्जकम्_loc, वृक्षः_TYPE (वृक्षः_TYPE (व्यञ्जकम्.मानम्)),
		 व्यञ्जकम्.मानम्, exprlist.length (), exprlist.address ());
	    व्यञ्जकम्.m_decimal = 0;
	    व्यञ्जकम्.original_code = ERROR_MARK;
	    व्यञ्जकम्.original_type = रिक्त;
	    भङ्ग;
	  }
	पक्ष CPP_DOT:
	  {
	    /* Structure element reference.  */
	    c_parser_consume_token (parser);
	    सचे (c_parser_next_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		ident = comp_tok->मानम्;
		comp_loc = comp_tok->location;
	      }
	    अञ्ञथा
	      {
		c_parser_error (parser, "expected identifier");
		व्यञ्जकम्.set_error ();
		व्यञ्जकम्.original_code = ERROR_MARK;
		व्यञ्जकम्.original_type = रिक्त;
		पटिनिवत्त व्यञ्जकम्;
	      }
	    start = व्यञ्जकम्.get_start ();
	    finish = c_parser_peek_token (parser)->get_finish ();
	    c_parser_consume_token (parser);
	    व्यञ्जकम्.मानम् = build_component_ref (op_loc, व्यञ्जकम्.मानम्, ident,
					      comp_loc, UNKNOWN_LOCATION);
	    set_c_व्यञ्जकम्_source_range (&व्यञ्जकम्, start, finish);
	    व्यञ्जकम्.m_decimal = 0;
	    व्यञ्जकम्.original_code = ERROR_MARK;
	    सचे (वृक्षः_CODE (व्यञ्जकम्.मानम्) != COMPONENT_REF)
	      व्यञ्जकम्.original_type = रिक्त;
	    अञ्ञथा
	      {
		/* Remember the original type of a bitfield.  */
		वृक्षः field = वृक्षः_OPERAND (व्यञ्जकम्.मानम्, 1);
		सचे (वृक्षः_CODE (field) != FIELD_DECL)
		  व्यञ्जकम्.original_type = रिक्त;
		अञ्ञथा
		  व्यञ्जकम्.original_type = DECL_BIT_FIELD_TYPE (field);
	      }
	    भङ्ग;
	  }
	पक्ष CPP_DEREF:
	  {
	    /* Structure element reference.  */
	    सचे (!POINTER_TYPE_P (वृक्षः_TYPE (व्यञ्जकम्.मानम्)))
	      {
		c_parser_error (parser, "dereference of non-pointer");
		व्यञ्जकम्.set_error ();
		व्यञ्जकम्.original_code = ERROR_MARK;
		व्यञ्जकम्.original_type = रिक्त;
		पटिनिवत्त व्यञ्जकम्;
	      }
	    c_parser_consume_token (parser);
	    सचे (c_parser_next_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		ident = comp_tok->मानम्;
		comp_loc = comp_tok->location;
	      }
	    अञ्ञथा
	      {
		c_parser_error (parser, "expected identifier");
		व्यञ्जकम्.set_error ();
		व्यञ्जकम्.original_code = ERROR_MARK;
		व्यञ्जकम्.original_type = रिक्त;
		पटिनिवत्त व्यञ्जकम्;
	      }
	    start = व्यञ्जकम्.get_start ();
	    finish = c_parser_peek_token (parser)->get_finish ();
	    c_parser_consume_token (parser);
	    व्यञ्जकम्.मानम् = build_component_ref (op_loc,
					      build_simple_mem_ref_loc
					        (op_loc, व्यञ्जकम्.मानम्),
					      ident, comp_loc,
					      व्यञ्जकम्.get_location ());
	    set_c_व्यञ्जकम्_source_range (&व्यञ्जकम्, start, finish);
	    व्यञ्जकम्.m_decimal = 0;
	    व्यञ्जकम्.original_code = ERROR_MARK;
	    सचे (वृक्षः_CODE (व्यञ्जकम्.मानम्) != COMPONENT_REF)
	      व्यञ्जकम्.original_type = रिक्त;
	    अञ्ञथा
	      {
		/* Remember the original type of a bitfield.  */
		वृक्षः field = वृक्षः_OPERAND (व्यञ्जकम्.मानम्, 1);
		सचे (वृक्षः_CODE (field) != FIELD_DECL)
		  व्यञ्जकम्.original_type = रिक्त;
		अञ्ञथा
		  व्यञ्जकम्.original_type = DECL_BIT_FIELD_TYPE (field);
	      }
	    भङ्ग;
	  }
	स्वभाव:
	  पटिनिवत्त व्यञ्जकम्;
	}
    }
}

/* Parse expression list.

   gimple-expr-list:
     gimple-unary-expression
     gimple-expr-list , gimple-unary-expression

 */

स्थिर शून्य
c_parser_gimple_व्यञ्जकम्_list (gimple_parser &parser, vec<वृक्षः> *ret)
{
  संरचना c_व्यञ्जकम् व्यञ्जकम्;

  व्यञ्जकम् = c_parser_gimple_unary_expression (parser);
  ret->safe_प्रक्षिप (व्यञ्जकम्.मानम्);
  याव (c_parser_next_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      व्यञ्जकम् = c_parser_gimple_unary_expression (parser);
      ret->safe_प्रक्षिप (व्यञ्जकम्.मानम्);
    }
}

/* Parse gimple label.

   gimple-label:
     identifier :
     case constant-expression :
     default :

*/

स्थिर शून्य
c_parser_gimple_label (gimple_parser &parser, gimple_seq *seq)
{
  वृक्षः name = c_parser_peek_token (parser)->मानम्;
  location_t loc1 = c_parser_peek_token (parser)->location;
  gcc_assert (c_parser_next_token_is (parser, CPP_NAME));
  c_parser_consume_token (parser);
  gcc_assert (c_parser_next_token_is (parser, CPP_COLON));
  c_parser_consume_token (parser);
  वृक्षः label = define_label (loc1, name);
  सचे (label)
    gimple_seq_add_stmt_without_update (seq, gimple_build_label (label));
  पटिनिवत्त;
}

/* Parse gimple/RTL pass list.

   gimple-or-rtl-pass-list:
     startwith("pass-name")[,{cfg,ssa}]
 */

शून्य
c_parser_gimple_or_rtl_pass_list (c_parser *parser, c_declspecs *specs)
{
  वर्ण *pass = रिक्त;

  /* Accept __GIMPLE/__RTL.  */
  सचे (c_parser_next_token_is_not (parser, CPP_OPEN_PAREN))
    पटिनिवत्त;
  c_parser_consume_token (parser);

  specs->entry_bb_गणनम् = profile_गणनम्::uninitialized ();
  याव (c_parser_next_token_is (parser, CPP_NAME))
    {
      profile_quality quality;
      ध्रुव वर्ण *op = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्);
      c_parser_consume_token (parser);
      सचे (! strcmp (op, "startwith"))
	{
	  सचे (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    पटिनिवत्त;
	  सचे (c_parser_next_token_is_not (parser, CPP_STRING))
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"expected pass name");
	      पटिनिवत्त;
	    }
	  pass = xstrdup (वृक्षः_STRING_POINTER
			  (c_parser_string_literal (parser, मिच्छा,
						    मिच्छा).मानम्));
	  सचे (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<(%>"))
	    पटिनिवत्त;
	}
      अञ्ञथा सचे (parse_profile_quality (op, &quality))
	{
	  वृक्षः q;
	  सचे (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    पटिनिवत्त;

	  सचे (!c_parser_next_token_is (parser, CPP_सङ्ख्या)
	      || (वृक्षः_CODE (q = c_parser_peek_token (parser)->मानम्)
		  != INTEGER_CST))
	    {
	      c_parser_error (parser, "expected count value");
	      पटिनिवत्त;
	    }

	  specs->entry_bb_गणनम्
	    = profile_गणनम्::from_gcov_type (वृक्षः_INT_CST_नीचः (q), quality);
	  c_parser_consume_token (parser);
	  सचे (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    पटिनिवत्त;
	}
      अञ्ञथा सचे (specs->declspec_il != cdil_gimple)
	/* Allow only one IL specifier and none on RTL.  */
	;
      अञ्ञथा सचे (! strcmp (op, "cfg"))
	specs->declspec_il = cdil_gimple_cfg;
      अञ्ञथा सचे (! strcmp (op, "ssa"))
	specs->declspec_il = cdil_gimple_ssa;
      अञ्ञथा
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "invalid operation");
	  पटिनिवत्त;
	}
     सचे (c_parser_next_token_is (parser, CPP_COMMA))
       c_parser_consume_token (parser);
    }

  सचे (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    पटिनिवत्त;

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

स्थिर शून्य
c_parser_gimple_declaration (gimple_parser &parser)
{
  संरचना c_declarator *declarator;
  संरचना c_declspecs *specs = build_null_declspecs ();
  c_parser_declspecs (parser, specs, सच्च, सच्च, सच्च,
		      सच्च, सच्च, सच्च, सच्च, cla_nonabstract_decl);
  finish_declspecs (specs);

  /* Provide better error recovery.  Note that a type name here is usually
     better diagnosed as a redeclaration.  */
  सचे (c_parser_next_token_starts_declspecs (parser)
      && ! c_parser_next_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<;%>");
      c_parser_set_error (parser, मिच्छा);
      पटिनिवत्त;
    }

  तार्किक dummy = मिच्छा;
  declarator = c_parser_declarator (parser,
				    specs->typespec_kind != ctsk_none,
				    C_DTR_NORMAL, &dummy);

  सचे (!c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_error (parser, "expected %<;%>");
      पटिनिवत्त;
    }
  सचे (declarator)
    {
      /* Handle SSA name decls specially, they do not go into the identifier
         table but we simply build the SSA name for later lookup.  */
      unsigned version, ver_offset;
      /* Handle SSA pointer declarations in a very simplistic ways, we
	 probably would like to call grokdeclarator in a special mode to
	 just build the type of the decl - start_decl already pushes
	 the identifier to the bindings for lookup, something we do not
	 want.  */
      संरचना c_declarator *id_declarator = declarator;
      याव (id_declarator->kind == cdk_pointer)
	id_declarator = id_declarator->declarator;
      सचे (id_declarator->kind == cdk_id
	  && (declarator->kind == cdk_pointer
	      || is_gimple_reg_type (specs->type))
	  && c_parser_parse_ssa_name_id (id_declarator->u.id.id,
					 &version, &ver_offset)
	  /* The following restricts it to unnamed anonymous SSA names
	     which fails parsing of named ones in dumps (we could
	     decide to not dump their name for -gimple).  */
	  && ver_offset == 0)
	{
	  संरचना c_declarator *p = declarator;
	  वृक्षः type = specs->type;
	  याव (p->kind == cdk_pointer)
	    {
	      type = build_pointer_type (type);
	      p = p->declarator;
	    }
	  c_parser_parse_ssa_name (parser, id_declarator->u.id.id, type,
				   version, ver_offset);
	}
      अञ्ञथा
	{
	  वृक्षः postfix_attrs = NULL_वृक्षः;
	  वृक्षः all_prefix_attrs = specs->attrs;
	  specs->attrs = रिक्त;
	  वृक्षः decl = start_decl (declarator, specs, मिच्छा,
				  chainon (postfix_attrs, all_prefix_attrs));
	  सचे (decl)
	    finish_decl (decl, UNKNOWN_LOCATION, NULL_वृक्षः, NULL_वृक्षः,
			 NULL_वृक्षः);
	}
    }
}

/* Parse gimple goto statement.  */

स्थिर शून्य
c_parser_gimple_goto_stmt (gimple_parser &parser,
			   location_t loc, वृक्षः label, gimple_seq *seq)
{
  सचे (cfun->curr_properties & PROP_cfg)
    {
      पूर्णाङ्क dest_index;
      profile_probability prob;
      सचे (c_parser_gimple_parse_bb_spec_edge_probability (label, parser,
							  &dest_index, &prob))
	{
	  parser.प्रक्षिप_edge (parser.current_bb->index, dest_index,
			    EDGE_FALLTHRU, prob);
	  पटिनिवत्त;
	}
    }
  वृक्षः decl = lookup_label_for_goto (loc, label);
  gimple_seq_add_stmt_without_update (seq, gimple_build_goto (decl));
}

/* Parse a parenthesized condition.
   gimple-condition:
     ( gimple-binary-expression )    */

स्थिर वृक्षः
c_parser_gimple_paren_condition (gimple_parser &parser)
{
  सचे (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    पटिनिवत्त error_mark_ग्रन्थिः;
  वृक्षः cond
    = c_parser_gimple_द्विमान_expression (parser, boolean_type_ग्रन्थिः).मानम्;
  सचे (cond != error_mark_ग्रन्थिः
      && ! COMPARISON_CLASS_P (cond)
      && ! CONSTANT_CLASS_P (cond)
      && ! SSA_VAR_P (cond))
    {
      c_parser_error (parser, "comparison required");
      cond = error_mark_ग्रन्थिः;
    }
  सचे (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    पटिनिवत्त error_mark_ग्रन्थिः;
  पटिनिवत्त cond;
}

/* Parse gimple try statement.

   try-statement:
     try { ... } finally { ... }
     try { ... } finally { ... } else { ... }

   This could support try/catch as well, but it's not implemented yet.
 */

स्थिर शून्य
c_parser_gimple_try_stmt (gimple_parser &parser, gimple_seq *seq)
{
  gimple_seq tryseq = रिक्त;
  c_parser_consume_token (parser);
  c_parser_gimple_compound_statement (parser, &tryseq);

  सचे ((c_parser_next_token_is (parser, CPP_KEYWORD)
       && c_parser_peek_token (parser)->keyword == RID_AT_FINALLY)
      || (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_token (parser)->id_kind == C_ID_ID
	  && strcmp (IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्),
		     "finally") == 0))
    {
      gimple_seq finseq = रिक्त;
      c_parser_consume_token (parser);
      c_parser_gimple_compound_statement (parser, &finseq);

      सचे (c_parser_next_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_ELSE)
	{
	  gimple_seq elsseq = रिक्त;
	  c_parser_consume_token (parser);
	  c_parser_gimple_compound_statement (parser, &elsseq);

	  geh_else *stmt = gimple_build_eh_else (finseq, elsseq);
	  finseq = रिक्त;
	  gimple_seq_add_stmt_without_update (&finseq, stmt);
	}

      gtry *stmt = gimple_build_try (tryseq, finseq, GIMPLE_TRY_FINALLY);
      gimple_seq_add_stmt_without_update (seq, stmt);
    }
  अञ्ञथा सचे (c_parser_next_token_is (parser, CPP_KEYWORD)
      && c_parser_peek_token (parser)->keyword == RID_AT_CATCH)
    c_parser_error (parser, "%<catch%> is not supported");
  अञ्ञथा
    c_parser_error (parser, "expected %<finally%> or %<catch%>");
}

/* Parse gimple if-else statement.

   if-statement:
     if ( gimple-binary-expression ) gimple-goto-statement
     if ( gimple-binary-expression ) gimple-goto-statement \
					else gimple-goto-statement
 */

स्थिर शून्य
c_parser_gimple_if_stmt (gimple_parser &parser, gimple_seq *seq)
{
  वृक्षः t_label = NULL_वृक्षः, f_label = NULL_वृक्षः, label;
  location_t loc;
  c_parser_consume_token (parser);
  वृक्षः cond = c_parser_gimple_paren_condition (parser);

  सचे (c_parser_next_token_is_keyword (parser, RID_GOTO))
    {
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      सचे (! c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected label");
	  पटिनिवत्त;
	}
      label = c_parser_peek_token (parser)->मानम्;
      c_parser_consume_token (parser);
      पूर्णाङ्क dest_index;
      profile_probability prob;
      सचे ((cfun->curr_properties & PROP_cfg)
	  && c_parser_gimple_parse_bb_spec_edge_probability (label, parser,
							     &dest_index, &prob))
	parser.प्रक्षिप_edge (parser.current_bb->index, dest_index,
			  EDGE_TRUE_मानम्, prob);
      अञ्ञथा
	t_label = lookup_label_for_goto (loc, label);
      सचे (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	पटिनिवत्त;
    }
  अञ्ञथा
    {
      c_parser_error (parser, "expected goto expression");
      पटिनिवत्त;
    }

  सचे (c_parser_next_token_is_keyword (parser, RID_ELSE))
    c_parser_consume_token (parser);
  अञ्ञथा
    {
      c_parser_error (parser, "expected else statement");
      पटिनिवत्त;
    }

  सचे (c_parser_next_token_is_keyword (parser, RID_GOTO))
    {
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      सचे (! c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected label");
	  पटिनिवत्त;
	}
      label = c_parser_peek_token (parser)->मानम्;
      c_parser_consume_token (parser);
      पूर्णाङ्क dest_index;
      profile_probability prob;
      सचे ((cfun->curr_properties & PROP_cfg)
	  && c_parser_gimple_parse_bb_spec_edge_probability (label, parser,
							     &dest_index, &prob))
	parser.प्रक्षिप_edge (parser.current_bb->index, dest_index,
			  EDGE_FALSE_मानम्, prob);
      अञ्ञथा
	f_label = lookup_label_for_goto (loc, label);
      सचे (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	पटिनिवत्त;
    }
  अञ्ञथा
    {
      c_parser_error (parser, "expected goto expression");
      पटिनिवत्त;
    }

  सचे (cond != error_mark_ग्रन्थिः)
    gimple_seq_add_stmt_without_update (seq, gimple_build_cond_from_वृक्षः (cond, t_label,
							   f_label));
}

/* Parse gimple switch-statement.

   gimple-switch-statement:
     switch (gimple-postfix-expression) gimple-case-statement

   gimple-case-statement:
     gimple-case-statement
     gimple-label-statement : gimple-goto-statement
*/

स्थिर शून्य
c_parser_gimple_switch_stmt (gimple_parser &parser, gimple_seq *seq)
{
  c_व्यञ्जकम् cond_व्यञ्जकम्;
  वृक्षः case_label, label;
  auto_vec<वृक्षः> labels;
  वृक्षः default_label = NULL_वृक्षः;
  c_parser_consume_token (parser);

  सचे (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    पटिनिवत्त;
  cond_व्यञ्जकम् = c_parser_gimple_postfix_expression (parser);
  सचे (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    पटिनिवत्त;

  सचे (! c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    पटिनिवत्त;

  याव (c_parser_next_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      सचे (c_parser_next_token_is (parser, CPP_EOF))
	{
	  c_parser_error (parser, "expected statement");
	  पटिनिवत्त;
	}

      विकल्प (c_parser_peek_token (parser)->keyword)
	{
	पक्ष RID_CASE:
	  {
	    c_व्यञ्जकम् exp1;
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);

	    सचे (c_parser_next_token_is (parser, CPP_NAME)
		|| c_parser_peek_token (parser)->type == CPP_सङ्ख्या)
	      exp1 = c_parser_gimple_postfix_expression (parser);
	    अञ्ञथा
	      {
		c_parser_error (parser, "expected expression");
		पटिनिवत्त;
	      }

	    सचे (c_parser_next_token_is (parser, CPP_COLON))
	      {
		c_parser_consume_token (parser);
		सचे (c_parser_next_token_is (parser, CPP_NAME))
		  {
		    label = c_parser_peek_token (parser)->मानम्;
		    c_parser_consume_token (parser);
		    वृक्षः decl = lookup_label_for_goto (loc, label);
		    case_label = build_case_label (exp1.मानम्, NULL_वृक्षः,
						   decl);
		    labels.safe_प्रक्षिप (case_label);
		    सचे (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      पटिनिवत्त;
		  }
		अञ्ञथा सचे (! c_parser_require (parser, CPP_NAME,
					     "expected label"))
		  पटिनिवत्त;
	      }
	    अञ्ञथा सचे (! c_parser_require (parser, CPP_SEMICOLON,
					 "expected %<:%>"))
	      पटिनिवत्त;
	    भङ्ग;
	  }
	पक्ष RID_DEFAULT:
	  {
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);
	    सचे (c_parser_next_token_is (parser, CPP_COLON))
	      {
		c_parser_consume_token (parser);
		सचे (c_parser_next_token_is (parser, CPP_NAME))
		  {
		    label = c_parser_peek_token (parser)->मानम्;
		    c_parser_consume_token (parser);
		    वृक्षः decl = lookup_label_for_goto (loc, label);
		    default_label = build_case_label (NULL_वृक्षः, NULL_वृक्षः,
						      decl);
		    सचे (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      पटिनिवत्त;
		  }
		अञ्ञथा सचे (! c_parser_require (parser, CPP_NAME,
					     "expected label"))
		  पटिनिवत्त;
	      }
	    अञ्ञथा सचे (! c_parser_require (parser, CPP_SEMICOLON,
					 "expected %<:%>"))
	      पटिनिवत्त;
	    भङ्ग;
	  }
	स्वभाव:
	  c_parser_error (parser, "expected case label");
	  पटिनिवत्त;
	}

    }
  सचे (! c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>"))
    पटिनिवत्त;

  सचे (cond_व्यञ्जकम्.मानम् != error_mark_ग्रन्थिः)
    {
      gswitch *s = gimple_build_switch (cond_व्यञ्जकम्.मानम्, default_label, labels);
      gimple_seq_add_stmt_without_update (seq, s);
    }
}

/* Parse gimple return statement.  */

स्थिर शून्य
c_parser_gimple_return_stmt (gimple_parser &parser, gimple_seq *seq)
{
  location_t loc = c_parser_peek_token (parser)->location;
  gimple *ret = रिक्त;
  c_parser_consume_token (parser);
  सचे (c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      c_finish_gimple_return (loc, NULL_वृक्षः);
      ret = gimple_build_return (रिक्त);
      gimple_seq_add_stmt_without_update (seq, ret);
    }
  अञ्ञथा
    {
      location_t xloc = c_parser_peek_token (parser)->location;
      c_व्यञ्जकम् व्यञ्जकम् = c_parser_gimple_unary_expression (parser);
      सचे (व्यञ्जकम्.मानम् != error_mark_ग्रन्थिः)
	{
	  c_finish_gimple_return (xloc, व्यञ्जकम्.मानम्);
	  ret = gimple_build_return (व्यञ्जकम्.मानम्);
	  gimple_seq_add_stmt_without_update (seq, ret);
	}
    }
}

/* Support function for c_parser_gimple_return_stmt.  */

स्थिर शून्य
c_finish_gimple_return (location_t loc, वृक्षः retval)
{
  वृक्षः valtype = वृक्षः_TYPE (वृक्षः_TYPE (current_function_decl));

  /* Use the expansion point to handle cases such as returning NULL
     in a function returning void.  */
  location_t xloc = expansion_point_location_if_in_system_header (loc);

  सचे (वृक्षः_THIS_VOLATILE (current_function_decl))
    warning_at (xloc, 0,
		"function declared %<noreturn%> has a %<return%> statement");

  सचे (! retval)
    current_function_returns_null = 1;
  अञ्ञथा सचे (valtype == 0 || VOID_TYPE_P (valtype))
    {
      current_function_returns_null = 1;
      सचे (वृक्षः_CODE (वृक्षः_TYPE (retval)) != VOID_TYPE)
	{
	  error_at
	    (xloc, "%<return%> with a value, in function returning void");
	  inform (DECL_SOURCE_LOCATION (current_function_decl),
		  "declared here");
	}
    }
  अञ्ञथा सचे (वृक्षः_CODE (valtype) != वृक्षः_CODE (वृक्षः_TYPE (retval)))
    {
      error_at
	(xloc, "invalid conversion in return statement");
      inform (DECL_SOURCE_LOCATION (current_function_decl),
	      "declared here");
    }
  पटिनिवत्त;
}
