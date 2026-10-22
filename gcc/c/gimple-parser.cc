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

वर्ग gimple_parser
{
सार्वजनिक:
  gimple_parser (c_parser *p) : parser (p), edges(), current_bb(रिक्त) {}
  /* c_parser is not visible here, use composition and fake inheritance
     via a conversion operator.  */
  operator c_parser *() { प्रत्यागम parser; }
  c_parser *parser;

  /* CFG build state.  */
  वर्ग gimple_parser_edge
  {
  सार्वजनिक:
    पूर्णाङ्क src;
    पूर्णाङ्क dest;
    पूर्णाङ्क flags;
    profile_probability probability;
  };
  auto_vec<gimple_parser_edge> edges;
  basic_block current_bb;

  शून्य ढकला_edge (पूर्णाङ्क, पूर्णाङ्क, पूर्णाङ्क, profile_probability);
};

शून्य
gimple_parser::ढकला_edge (पूर्णाङ्क src, पूर्णाङ्क dest, पूर्णाङ्क flags,
			  profile_probability prob)
{
  gimple_parser_edge e;
  e.src = src;
  e.dest = dest;
  e.flags = flags;
  e.probability = prob;
  edges.safe_ढकला (e);
}


/* Gimple parsing functions.  */
स्थिर तार्किक c_parser_gimple_compound_statement (gimple_parser &, gimple_seq *);
स्थिर शून्य c_parser_gimple_label (gimple_parser &, gimple_seq *);
स्थिर शून्य c_parser_gimple_statement (gimple_parser &, gimple_seq *);
स्थिर संरचना c_अभिव्यक्ती c_parser_gimple_द्विमान_expression (gimple_parser &, वृक्ष);
स्थिर संरचना c_अभिव्यक्ती c_parser_gimple_unary_expression (gimple_parser &);
स्थिर संरचना c_अभिव्यक्ती c_parser_gimple_postfix_expression
			(gimple_parser &, वृक्ष = error_mark_गाठ);
स्थिर संरचना c_अभिव्यक्ती c_parser_gimple_postfix_expression_after_primary
			(gimple_parser &, location_t, संरचना c_अभिव्यक्ती);
स्थिर शून्य c_parser_gimple_declaration (gimple_parser &);
स्थिर शून्य c_parser_gimple_goto_stmt (gimple_parser &, location_t,
				       वृक्ष, gimple_seq *);
स्थिर शून्य c_parser_gimple_try_stmt (gimple_parser &, gimple_seq *);
स्थिर शून्य c_parser_gimple_if_stmt (gimple_parser &, gimple_seq *);
स्थिर शून्य c_parser_gimple_switch_stmt (gimple_parser &, gimple_seq *);
स्थिर शून्य c_parser_gimple_return_stmt (gimple_parser &, gimple_seq *);
स्थिर शून्य c_finish_gimple_return (location_t, वृक्ष);
स्थिर वृक्ष c_parser_gimple_paren_condition (gimple_parser &);
स्थिर शून्य c_parser_gimple_अभिव्यक्ती_list (gimple_parser &, vec<वृक्ष> *);


/* Much like parser_build_unary_op, but avoid applying default conversions.  */

स्थिर c_अभिव्यक्ती
gimple_parser_build_unary_op (location_t loc,
			      गणना वृक्ष_code code, संरचना c_अभिव्यक्ती arg)
{
  संरचना c_अभिव्यक्ती result;

  result.original_code = code;
  result.original_type = रिक्त;
  result.m_decimal = 0;

  यदि (reject_gcc_builtin (arg.मूल्य))
    {
      result.मूल्य = error_mark_गाठ;
    }
  अन्यथा
    {
      result.मूल्य = build_unary_op (loc, code, arg.मूल्य, सत्य);

      यदि (वृक्ष_OVERFLOW_P (result.मूल्य) && !वृक्ष_OVERFLOW_P (arg.मूल्य))
	overflow_warning (loc, result.मूल्य, arg.मूल्य);
    }

  /* We are typically called when parsing a prefix token at LOC acting on
     ARG.  Reflect this by updating the source range of the result to
     start at LOC and end at the end of ARG.  */
  set_c_अभिव्यक्ती_source_range (&result,
			   loc, arg.get_finish ());

  प्रत्यागम result;
}

/* See if VAL is an identifier matching __BB<num> and return <num>
   in *INDEX.  */

स्थिर तार्किक
c_parser_gimple_parse_bb_spec (वृक्ष val, पूर्णाङ्क *index)
{
  यदि (!startswith (IDENTIFIER_POINTER (val), "__BB"))
    प्रत्यागम असत्य;

  ध्रुव वर्ण *bb = IDENTIFIER_POINTER (val) + 4;
  यदि (! ISDIGIT (*bb))
    प्रत्यागम असत्य;

  वर्ण *pend;
  errno = 0;
  ध्रुव unsigned long संख्या = strtoul (bb, &pend, 10);
  यदि (errno == ERANGE
      || *pend != '\0'
      || संख्या > INT_MAX)
    प्रत्यागम असत्य;

  *index = संख्या;
  प्रत्यागम सत्य;
}

/* See if VAL is an identifier matching __BB<num> and return <num>
   in *INDEX.  Return true if so and parse also FREQUENCY of
   the edge.  */


स्थिर तार्किक
c_parser_gimple_parse_bb_spec_edge_probability (वृक्ष val,
						gimple_parser &parser,
						पूर्णाङ्क *index,
						profile_probability
						*probability)
{
  तार्किक return_p = c_parser_gimple_parse_bb_spec (val, index);
  यदि (return_p)
    {
      *probability = profile_probability::uninitialized ();
      /* Parse frequency if provided.  */
      यदि (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	{
	  वृक्ष f;
	  c_parser_consume_token (parser);
	  यदि (!c_parser_next_token_is (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected frequency quality");
	      प्रत्यागम असत्य;
	    }

	  profile_quality quality;
	  ध्रुव वर्ण *v
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य);
	  यदि (!parse_profile_quality (v, &quality))
	    {
	      c_parser_error (parser, "unknown profile quality");
	      प्रत्यागम असत्य;
	    }

	  c_parser_consume_token (parser);
	  यदि (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    प्रत्यागम असत्य;

	  यदि (!c_parser_next_token_is (parser, CPP_संख्या)
	      || (वृक्ष_CODE (f = c_parser_peek_token (parser)->मूल्य)
		  != INTEGER_CST))
	    {
	      c_parser_error (parser, "expected frequency value");
	      प्रत्यागम असत्य;
	    }

	  unsigned पूर्णाङ्क मूल्य = वृक्ष_INT_CST_खालचा (f);
	  *probability = profile_probability (मूल्य, quality);

	  c_parser_consume_token (parser);
	  यदि (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    प्रत्यागम असत्य;

	  यदि (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    प्रत्यागम असत्य;
	}

      प्रत्यागम सत्य;
    }

  प्रत्यागम असत्य;

}

/* Parse the body of a function declaration marked with "__GIMPLE".  */

शून्य
c_parser_parse_gimple_body (c_parser *cparser, वर्ण *gimple_pass,
			    गणना c_declspec_il cdil,
			    profile_मोजणी entry_bb_मोजणी)
{
  gimple_parser parser (cparser);
  gimple_seq seq = रिक्त;
  gimple_seq body = रिक्त;
  वृक्ष stmt = ढकला_stmt_list ();
  ढकला_scope ();
  location_t loc1 = c_parser_peek_token (parser)->location;

  cfun->pass_startwith = gimple_pass;
  init_वृक्ष_ssa (cfun);

  यदि (cdil == cdil_gimple)
    /* While we have SSA names in the IL we do not have a CFG built yet
       and PHIs are represented using a PHI internal function.  We do
       have lowered control flow and exception handling (well, we do not
       have parser support for EH yet).  But as we still have BINDs
       we have to go through lowering again.  */
    cfun->curr_properties = PROP_gimple_any;
  अन्यथा
    {
      /* We have at least cdil_gimple_cfg.  */
      gimple_register_cfg_hooks ();
      init_empty_वृक्ष_cfg ();
      parser.current_bb = ENTRY_BLOCK_PTR_FOR_FN (cfun);
      /* Initialize the bare loop structure - we are going to only
         mark headers and leave the rest to fixup.  */
      set_loops_for_fn (cfun, ggc_cleared_alloc<संरचना loops> ());
      init_loops_structure (cfun, loops_for_fn (cfun), 1);
      loops_state_set (cfun, LOOPS_NEED_FIXUP|LOOPS_MAY_HAVE_MULTIPLE_LATCHES);
      cfun->curr_properties
	|= PROP_gimple_lcf | PROP_gimple_leh | PROP_cfg | PROP_loops;
      यदि (cdil == cdil_gimple_ssa)
	{
	  init_ssa_operands (cfun);
	  cfun->curr_properties |= PROP_ssa;
	}
    }

  यदि (! c_parser_gimple_compound_statement (parser, &seq)
      && cdil == cdil_gimple)
    {
      gimple *ret = gimple_build_return (रिक्त);
      gimple_seq_add_stmt_without_update (&seq, ret);
    }

  वृक्ष block = काढा_scope ();
  stmt = काढा_stmt_list (stmt);
  stmt = c_build_bind_अभिव्यक्ती (loc1, block, stmt);

  block = DECL_INITIAL (current_function_decl);
  BLOCK_SUBBLOCKS (block) = NULL_वृक्ष;
  BLOCK_CHAIN (block) = NULL_वृक्ष;
  वृक्ष_ASM_WRITTEN (block) = 1;

  यदि (cdil == cdil_gimple)
    {
      gbind *bind_stmt = gimple_build_bind (BIND_अभिव्यक्ती_VARS (stmt), रिक्त,
					    BIND_अभिव्यक्ती_BLOCK (stmt));
      gimple_bind_set_body (bind_stmt, seq);
      gimple_seq_add_stmt_without_update (&body, bind_stmt);
      gimple_set_body (current_function_decl, body);
    }
  अन्यथा
    {
      /* Control-flow and binds are lowered, record local decls.  */
      प्रति (वृक्ष var = BIND_अभिव्यक्ती_VARS (stmt); var; var = DECL_CHAIN (var))
	यदि (VAR_P (var)
	    && !DECL_EXTERNAL (var))
	  {
	    add_local_decl (cfun, var);
	    /* When the middle-end re-gimplifies any expression we might
	       run into the assertion that we've seen the decl in a BIND.  */
	    यदि (!वृक्ष_STATIC (var))
	      DECL_SEEN_IN_BIND_अभिव्यक्ती_P (var) = 1;
	  }
      /* We have a CFG.  Build the edges.  */
      प्रति (unsigned i = 0; i < parser.edges.length (); ++i)
	{
	  edge e = make_edge (BASIC_BLOCK_FOR_FN (cfun, parser.edges[i].src),
			      BASIC_BLOCK_FOR_FN (cfun, parser.edges[i].dest),
			      parser.edges[i].flags);
	  e->probability = parser.edges[i].probability;
	}
      /* Add edges for case labels.  */
      basic_block bb;
      FOR_EACH_BB_FN (bb, cfun)
	यदि (EDGE_मोजणी (bb->succs) == 0)
	  {
	    यदि (gswitch *sw = safe_dyn_cast <gswitch *> (*gsi_last_bb (bb)))
	      प्रति (unsigned i = 0; i < gimple_switch_अंक_labels (sw); ++i)
		{
		  basic_block label_bb = gimple_switch_label_bb (cfun, sw, i);
		  make_edge (bb, label_bb, 0);
		}
	  }
      /* Need those for loop fixup.  */
      calculate_dominance_info (CDI_DOMINATORS);
      /* With SSA lower PHIs parsed as internal function calls and
	 update stmts.  */
      यदि (cdil == cdil_gimple_ssa)
	{
	  /* Create PHI nodes, they are parsed into __PHI internal calls
	     and update SSA operands.  */
	  FOR_EACH_BB_FN (bb, cfun)
	    {
	      gimple_stmt_iterator gsi;
	      प्रति (gsi = gsi_start_bb (bb); !gsi_end_p (gsi);)
		{
		  gimple *stmt = gsi_stmt (gsi);
		  यदि (!gimple_call_internal_p (stmt, IFN_PHI))
		    भङ्ग;

		  gphi *phi = create_phi_गाठ (gimple_call_lhs (stmt), bb);
		  प्रति (unsigned i = 0; i < gimple_call_अंक_args (stmt); i += 2)
		    {
		      पूर्णाङ्क srcidx = वृक्ष_INT_CST_खालचा (gimple_call_arg (stmt, i));
		      edge e = find_edge (BASIC_BLOCK_FOR_FN (cfun, srcidx), bb);
		      यदि (!e)
			c_parser_error (parser, "edge not found");
		      अन्यथा
			add_phi_arg (phi, gimple_call_arg (stmt, i + 1), e,
				     UNKNOWN_LOCATION);
		    }
		  gsi_remove (&gsi, सत्य);
		}
	      प्रति (; !gsi_end_p (gsi); gsi_next (&gsi))
		update_stmt (gsi_stmt (gsi));
	    }
	  /* Fill SSA name gaps, putting them on the freelist and diagnose
	     SSA names without definition.  */
	  प्रति (unsigned i = 1; i < अंक_ssa_names; ++i)
	    यदि (!ssa_name (i))
	      {
		वृक्ष name = make_ssa_name_fn (cfun, integer_type_गाठ, रिक्त, i);
		release_ssa_name_fn (cfun, name);
	      }
	    अन्यथा यदि (!SSA_NAME_DEF_STMT (ssa_name (i)))
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

  यदि (cfun->curr_properties & PROP_cfg)
    {
      ENTRY_BLOCK_PTR_FOR_FN (cfun)->मोजणी = entry_bb_मोजणी;
      gcov_type t = param_gimple_fe_computed_hot_bb_threshold;
      set_hot_bb_threshold (t);
      update_max_bb_मोजणी ();
      cgraph_गाठ::get_create (cfun->decl);
      cgraph_edge::rebuild_edges ();
    }

  /* Perform IL validation and if any error is found abort compilation
     of this function by zapping its body.  */
  यदि ((cfun->curr_properties & PROP_cfg)
      && verify_gimple_in_cfg (cfun, असत्य, असत्य))
    init_empty_वृक्ष_cfg ();
  अन्यथा यदि (!(cfun->curr_properties & PROP_cfg)
	   && verify_gimple_in_seq (gimple_body (current_function_decl), असत्य))
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
  तार्किक return_p = असत्य;

  यदि (! c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    प्रत्यागम असत्य;

  /* A compound statement starts with optional declarations.  */
  यावत् (c_parser_next_tokens_start_declaration (parser))
    {
      c_parser_gimple_declaration (parser);
      यदि (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	प्रत्यागम असत्य;
    }

  यावत् (c_parser_next_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      यदि (c_parser_error (parser))
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_BRACE, रिक्त);
	  प्रत्यागम return_p;
	}
      अन्यथा यदि (c_parser_next_token_is (parser, CPP_EOF))
	{
	  c_parser_error (parser, "expected declaration or statement");
	  प्रत्यागम return_p;
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
		यदि (c_parser_next_token_is (parser, CPP_NAME))
		  {
		    वृक्ष label = c_parser_peek_token (parser)->मूल्य;
		    c_parser_consume_token (parser);
		    c_parser_gimple_goto_stmt (parser, loc, label, seq);
		    यदि (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      प्रत्यागम return_p;
		  }
		}
	      भङ्ग;
	    पक्ष RID_RETURN:
	      return_p = सत्य;
	      c_parser_gimple_return_stmt (parser, seq);
	      यदि (! c_parser_require (parser, CPP_SEMICOLON,
				      "expected %<;%>"))
		प्रत्यागम return_p;
	      यदि (cfun->curr_properties & PROP_cfg)
		parser.ढकला_edge (parser.current_bb->index, EXIT_BLOCK, 0,
				  profile_probability::uninitialized ());
	      भङ्ग;
	    स्वभाव:
	      गच्छ अभिव्यक्ती_stmt;
	    }
	  भङ्ग;
	पक्ष CPP_NAME:
	  यदि (c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_gimple_label (parser, seq);
	      भङ्ग;
	    }
	  यदि (c_parser_next_token_is (parser, CPP_NAME)
	      && c_parser_peek_token (parser)->id_kind == C_ID_ID
	      && strcmp (IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य),
			 "try") == 0)
	    {
	      c_parser_gimple_try_stmt (parser, seq);
	      भङ्ग;
	    }
	  /* Basic block specification.
	     __BB (index, ...)  */
	  यदि ((cfun->curr_properties & PROP_cfg)
	      && !strcmp (IDENTIFIER_POINTER
			    (c_parser_peek_token (parser)->मूल्य), "__BB"))
	    {
	      c_parser_consume_token (parser);
	      यदि (! c_parser_require (parser, CPP_OPEN_PAREN,
				      "expected %<(%>"))
		प्रत्यागम return_p;
	      यदि (c_parser_next_token_is_not (parser, CPP_संख्या))
		{
		  c_parser_error (parser, "expected block index");
		  प्रत्यागम return_p;
		}
	      वृक्ष tnum = c_parser_peek_token (parser)->मूल्य;
	      यदि (वृक्ष_CODE (tnum) != INTEGER_CST)
		{
		  c_parser_error (parser, "expected block index");
		  प्रत्यागम return_p;
		}
	      पूर्णाङ्क index = वृक्ष_INT_CST_खालचा (tnum);
	      यदि (index < अंक_FIXED_BLOCKS
		  || (index < last_basic_block_for_fn (cfun)
		      && BASIC_BLOCK_FOR_FN (cfun, index) != रिक्त))
		{
		  c_parser_error (parser, "invalid block index");
		  प्रत्यागम return_p;
		}
	      पूर्णाङ्क is_loop_header_of = -1;
	      profile_मोजणी bb_मोजणी = profile_मोजणी::uninitialized ();
	      c_parser_consume_token (parser);
	      यावत् (c_parser_next_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  यदि (! c_parser_next_token_is (parser, CPP_NAME))
		    {
		      c_parser_error (parser, "expected block specifier");
		      प्रत्यागम return_p;
		    }
		  /* loop_header (NUM)  */
		  यदि (!strcmp (IDENTIFIER_POINTER
			         (c_parser_peek_token (parser)->मूल्य),
			       "loop_header"))
		    {
		      c_parser_consume_token (parser);
		      यदि (! c_parser_require (parser, CPP_OPEN_PAREN,
					      "expected %<(%>"))
			प्रत्यागम return_p;
		      वृक्ष loop_अंक;
		      यदि (! c_parser_next_token_is (parser, CPP_संख्या)
			  || वृक्ष_CODE (loop_अंक
					  = c_parser_peek_token (parser)->मूल्य)
			       != INTEGER_CST)
			{
			  c_parser_error (parser, "expected loop number");
			  प्रत्यागम return_p;
			}
		      c_parser_consume_token (parser);
		      is_loop_header_of = वृक्ष_INT_CST_खालचा (loop_अंक);
		      यदि (! c_parser_require (parser, CPP_CLOSE_PAREN,
					      "expected %<)%>"))
			प्रत्यागम return_p;
		    }
		  /* Parse profile: quality(value) */
		  अन्यथा
		    {
		      वृक्ष q;
		      profile_quality quality;
		      वृक्ष v = c_parser_peek_token (parser)->मूल्य;
		      यदि (!parse_profile_quality (IDENTIFIER_POINTER (v),
						  &quality))
			{
			  c_parser_error (parser, "unknown block specifier");
			  प्रत्यागम असत्य;
			}

		      c_parser_consume_token (parser);
		      यदि (!c_parser_require (parser, CPP_OPEN_PAREN,
					     "expected %<(%>"))
			प्रत्यागम असत्य;

		      यदि (!c_parser_next_token_is (parser, CPP_संख्या)
			  || (वृक्ष_CODE (q = c_parser_peek_token (parser)->मूल्य)
			      != INTEGER_CST))
			{
			  c_parser_error (parser, "expected count value");
			  प्रत्यागम असत्य;
			}

		      bb_मोजणी
			= profile_मोजणी::from_gcov_type (वृक्ष_INT_CST_खालचा (q),
							 quality);
		      c_parser_consume_token (parser);
		      यदि (! c_parser_require (parser, CPP_CLOSE_PAREN,
					      "expected %<)%>"))
			प्रत्यागम return_p;
		    }
		}
	      यदि (! c_parser_require (parser, CPP_CLOSE_PAREN,
				      "expected %<)%>")
		  || ! c_parser_require (parser, CPP_COLON,
					 "expected %<:%>"))
		प्रत्यागम return_p;

	      /* Put stmts parsed in the current block.  */
	      यदि (!gimple_seq_empty_p (*seq))
		{
		  यदि (!parser.current_bb)
		    c_parser_error (parser, "stmts without block");
		  अन्यथा
		    {
		      gimple_stmt_iterator gsi
			= gsi_start_bb (parser.current_bb);
		      gsi_घाला_seq_after_without_update (&gsi, *seq,
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
	      यदि (basic_block_info_for_fn (cfun)->length () <= (size_t)index)
		vec_safe_grow_cleared (basic_block_info_for_fn (cfun),
				       index + 1, सत्य);
	      SET_BASIC_BLOCK_FOR_FN (cfun, index, bb);
	      यदि (last_basic_block_for_fn (cfun) <= index)
		last_basic_block_for_fn (cfun) = index + 1;
	      n_basic_blocks_for_fn (cfun)++;
	      यदि (parser.current_bb->index == ENTRY_BLOCK)
		parser.ढकला_edge (ENTRY_BLOCK, bb->index, EDGE_FALLTHRU,
				  profile_probability::always ());

	      /* We leave the proper setting to fixup.  */
	      वर्ग loop *loop_father = loops_for_fn (cfun)->वृक्ष_मूळ;
	      /* If the new block is a loop header, allocate a loop
		 struct.  Fixup will take care of proper placement within
		 the loop tree.  */
	      यदि (is_loop_header_of != -1)
		{
		  यदि (संख्या_of_loops (cfun) > (unsigned)is_loop_header_of
		      && get_loop (cfun, is_loop_header_of) != रिक्त)
		    {
		      c_parser_error (parser, "duplicate loop header");
		    }
		  अन्यथा
		    {
		      वर्ग loop *loop = alloc_loop ();
		      loop->अंक = is_loop_header_of;
		      loop->header = bb;
		      यदि (संख्या_of_loops (cfun) <= (unsigned)is_loop_header_of)
			vec_safe_grow_cleared (loops_for_fn (cfun)->larray,
					       is_loop_header_of + 1, सत्य);
		      (*loops_for_fn (cfun)->larray)[is_loop_header_of] = loop;
		      flow_loop_वृक्ष_गाठ_add (loops_for_fn (cfun)->वृक्ष_मूळ,
					       loop);
		    }
		  loop_father = get_loop (cfun, is_loop_header_of);
		}
	      bb->loop_father = loop_father;
	      bb->मोजणी = bb_मोजणी;

	      /* Stmts now go to the new block.  */
	      parser.current_bb = bb;
	      भङ्ग;
	    }
	  गच्छ अभिव्यक्ती_stmt;

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
अभिव्यक्ती_stmt:
	  c_parser_gimple_statement (parser, seq);
	  यदि (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	    c_parser_skip_until_found (parser, CPP_SEMICOLON, रिक्त);
	}
    }
  c_parser_consume_token (parser);

  /* Put stmts parsed in the current block.  */
  यदि ((cfun->curr_properties & PROP_cfg)
      && !gimple_seq_empty_p (*seq))
    {
      यदि (!parser.current_bb)
	c_parser_error (parser, "stmts without block");
      अन्यथा
	{
	  gimple_stmt_iterator gsi = gsi_start_bb (parser.current_bb);
	  gsi_घाला_seq_after_without_update (&gsi, *seq,
					       GSI_CONTINUE_LINKING);
	}
      *seq = रिक्त;
    }

  प्रत्यागम return_p;
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
  संरचना c_अभिव्यक्ती lhs, rhs;
  gimple *assign = रिक्त;
  location_t loc;
  वृक्ष arg = NULL_वृक्ष;
  auto_vec<वृक्ष> vargs;

  lhs = c_parser_gimple_unary_expression (parser);
  loc = अभिव्यक्ती_LOCATION (lhs.मूल्य);
  rhs.set_error ();

  /* GIMPLE call statement without LHS.  */
  यदि (c_parser_next_token_is (parser, CPP_SEMICOLON)
      && वृक्ष_CODE (lhs.मूल्य) == CALL_अभिव्यक्ती)
    {
      gimple *call;
      call = gimple_build_call_from_वृक्ष (lhs.मूल्य, रिक्त);
      gimple_seq_add_stmt_without_update (seq, call);
      gimple_set_location (call, loc);
      प्रत्यागम;
    }

  /* All following cases are statements with LHS.  */
  यदि (! c_parser_require (parser, CPP_EQ, "expected %<=%>"))
    प्रत्यागम;

  /* Eat and ignore {v} right after the =, the has_volatile_ops is
     redundant and re-computed by the operand scanner.  */
  यदि (c_parser_next_token_is (parser, CPP_OPEN_BRACE)
      && !(c_parser_peek_token (parser)->flags & PREV_WHITE)
      && c_parser_peek_2nd_token (parser)->type == CPP_NAME
      && !(c_parser_peek_2nd_token (parser)->flags & PREV_WHITE)
      && strcmp ("v", IDENTIFIER_POINTER
			(c_parser_peek_2nd_token (parser)->मूल्य)) == 0
      && c_parser_peek_nth_token (parser, 3)->type == CPP_CLOSE_BRACE
      && !(c_parser_peek_nth_token (parser, 3)->flags & PREV_WHITE))
    {
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }

  /* Cast expression.  */
  यदि (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_typename (c_parser_peek_2nd_token (parser)))
    {
      c_parser_consume_token (parser);
      संरचना c_type_name *type_name = c_parser_type_name (parser);
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      यदि (type_name == रिक्त)
	प्रत्यागम;
      /* ???  The actual type used in the cast expression is ignored as
         in GIMPLE it is encoded by the type of the LHS.  */
      rhs = c_parser_gimple_postfix_expression (parser);
      यदि (lhs.मूल्य != error_mark_गाठ
	  && rhs.मूल्य != error_mark_गाठ)
	{
	  गणना वृक्ष_code code = NOP_अभिव्यक्ती;
	  यदि (FLOAT_TYPE_P (वृक्ष_TYPE (lhs.मूल्य))
	      && ! FLOAT_TYPE_P (वृक्ष_TYPE (rhs.मूल्य)))
	    code = FLOAT_अभिव्यक्ती;
	  अन्यथा यदि (! FLOAT_TYPE_P (वृक्ष_TYPE (lhs.मूल्य))
		   && FLOAT_TYPE_P (वृक्ष_TYPE (rhs.मूल्य)))
	    code = FIX_TRUNC_अभिव्यक्ती;
	  assign = gimple_build_assign (lhs.मूल्य, code, rhs.मूल्य);
	  gimple_seq_add_stmt_without_update (seq, assign);
	  gimple_set_location (assign, loc);
	  प्रत्यागम;
	}
    }

  /* Unary expression.  */
  विकल्प (c_parser_peek_token (parser)->type)
    {
    पक्ष CPP_NAME:
      {
	वृक्ष id = c_parser_peek_token (parser)->मूल्य;
	यदि (strcmp (IDENTIFIER_POINTER (id), "__ABS") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__ABSU") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__MIN") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__MAX") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__BIT_INSERT") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__VEC_PERM") == 0)
	  गच्छ build_unary_अभिव्यक्ती;
	भङ्ग;
      }
    पक्ष CPP_KEYWORD:
      यदि (c_parser_peek_token (parser)->keyword != RID_REALPART
	  && c_parser_peek_token (parser)->keyword != RID_IMAGPART)
	भङ्ग;
      /* Fallthru.  */
    पक्ष CPP_AND:
    पक्ष CPP_PLUS:
    पक्ष CPP_MINUS:
    पक्ष CPP_COMPL:
    पक्ष CPP_NOT:
    पक्ष CPP_MULT: /* pointer deref */
    build_unary_अभिव्यक्ती:
      rhs = c_parser_gimple_unary_expression (parser);
      यदि (rhs.मूल्य != error_mark_गाठ)
	{
	  assign = gimple_build_assign (lhs.मूल्य, rhs.मूल्य);
	  gimple_set_location (assign, loc);
	  gimple_seq_add_stmt_without_update (seq, assign);
	}
      प्रत्यागम;

    स्वभाव:;
    }

  /* GIMPLE PHI statement.  */
  यदि (c_parser_next_token_is_keyword (parser, RID_PHI))
    {
      c_parser_consume_token (parser);

      यदि (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	प्रत्यागम;

      यदि (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	c_parser_consume_token (parser);

      यावत् (c_parser_next_token_is_not (parser, CPP_CLOSE_PAREN))
	{
	  यदि (c_parser_next_token_is (parser, CPP_NAME)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      arg = c_parser_peek_token (parser)->मूल्य;
	      c_parser_consume_token (parser);
	      यदि (c_parser_next_token_is (parser, CPP_COLON))
		c_parser_consume_token (parser);
	      पूर्णाङ्क src_index = -1;
	      यदि (!c_parser_gimple_parse_bb_spec (arg, &src_index))
		c_parser_error (parser, "invalid source block specification");
	      vargs.safe_ढकला (size_int (src_index));
	    }
	  अन्यथा यदि (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  अन्यथा
	    {
	      arg = c_parser_gimple_unary_expression (parser).मूल्य;
	      vargs.safe_ढकला (arg);
	    }
	}

      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");

      /* Build internal function for PHI.  */
      gcall *call_stmt = gimple_build_call_internal_vec (IFN_PHI, vargs);
      gimple_call_set_lhs (call_stmt, lhs.मूल्य);
      gimple_set_location (call_stmt, UNKNOWN_LOCATION);
      gimple_seq_add_stmt_without_update (seq, call_stmt);
      प्रत्यागम;
    }

  /* GIMPLE call with lhs.  */
  यदि (c_parser_next_token_is (parser, CPP_DOT)
      || (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN
	  && lookup_name (c_parser_peek_token (parser)->मूल्य)))
    {
      rhs = c_parser_gimple_unary_expression (parser);
      यदि (rhs.मूल्य != error_mark_गाठ)
	{
	  gimple *call = gimple_build_call_from_वृक्ष (rhs.मूल्य, रिक्त);
	  gimple_call_set_lhs (call, lhs.मूल्य);
	  gimple_seq_add_stmt_without_update (seq, call);
	  gimple_set_location (call, loc);
	}
      प्रत्यागम;
    }

  rhs = c_parser_gimple_द्विमान_expression (parser, वृक्ष_TYPE (lhs.मूल्य));
  यदि (lhs.मूल्य != error_mark_गाठ
      && rhs.मूल्य != error_mark_गाठ)
    {
      /* If we parsed an identifier and the next token  is a '?' then parse
	 a conditional expression.  */
      यदि (SSA_VAR_P (rhs.मूल्य) && c_parser_next_token_is (parser, CPP_QUERY))
	{
	  संरचना c_अभिव्यक्ती trueval, falseval;
	  c_parser_consume_token (parser);
	  trueval = c_parser_gimple_postfix_expression (parser);
	  falseval.set_error ();
	  यदि (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    falseval = c_parser_gimple_postfix_expression (parser);
	  यदि (trueval.मूल्य == error_mark_गाठ
	      || falseval.मूल्य == error_mark_गाठ)
	    प्रत्यागम;
	  rhs.मूल्य = build3_loc (loc,
				  VECTOR_TYPE_P (वृक्ष_TYPE (rhs.मूल्य))
				  ? VEC_COND_अभिव्यक्ती : COND_अभिव्यक्ती,
				  वृक्ष_TYPE (trueval.मूल्य),
				  rhs.मूल्य, trueval.मूल्य, falseval.मूल्य);
	}
      यदि (get_gimple_rhs_class (वृक्ष_CODE (rhs.मूल्य)) == GIMPLE_INVALID_RHS)
	{
	  c_parser_error (parser, "unexpected RHS for assignment");
	  प्रत्यागम;
	}
      assign = gimple_build_assign (lhs.मूल्य, rhs.मूल्य);
      gimple_seq_add_stmt_without_update (seq, assign);
      gimple_set_location (assign, loc);
    }
  प्रत्यागम;
}

/* A mapping between an identifier to a tree code for binary operations. */
स्थिर ध्रुव std::pair<ध्रुव वर्ण *, वृक्ष_code> gimple_द्विमान_identifier_code[] =
  {
    {"__MULT_HIGHPART", MULT_HIGHPART_अभिव्यक्ती},
    {"__UNLT", UNLT_अभिव्यक्ती},
    {"__UNLE", UNLE_अभिव्यक्ती},
    {"__UNGT", UNGT_अभिव्यक्ती},
    {"__UNGE", UNGE_अभिव्यक्ती},
    {"__UNEQ", UNEQ_अभिव्यक्ती},
    {"__UNORDERED", UNORDERED_अभिव्यक्ती},
    {"__ORDERED", ORDERED_अभिव्यक्ती},
    {"__LTGT", LTGT_अभिव्यक्ती},
    {"__FLOOR_DIV", FLOOR_DIV_अभिव्यक्ती},
    {"__ROUND_DIV", ROUND_DIV_अभिव्यक्ती},
    {"__EXACT_DIV", EXACT_DIV_अभिव्यक्ती},
    {"__CEIL_DIV", CEIL_DIV_अभिव्यक्ती},
    {"__FLOOR_MOD", FLOOR_MOD_अभिव्यक्ती},
    {"__ROUND_MOD", ROUND_MOD_अभिव्यक्ती},
    {"__CEIL_MOD", CEIL_MOD_अभिव्यक्ती},
    {"__ROTATE_LEFT", LROTATE_अभिव्यक्ती},
    {"__ROTATE_RIGHT", RROTATE_अभिव्यक्ती},
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

स्थिर c_अभिव्यक्ती
c_parser_gimple_द्विमान_expression (gimple_parser &parser, वृक्ष ret_type)
{
  /* Location of the binary operator.  */
  संरचना c_अभिव्यक्ती ret, lhs, rhs;
  गणना वृक्ष_code code = ERROR_MARK;
  ret.set_error ();
  lhs = c_parser_gimple_postfix_expression (parser, ret_type);
  यदि (c_parser_error (parser))
    प्रत्यागम ret;
  विकल्प (c_parser_peek_token (parser)->type)
    {
    पक्ष CPP_MULT:
      code = MULT_अभिव्यक्ती;
      भङ्ग;
    पक्ष CPP_DIV:
      code = TRUNC_DIV_अभिव्यक्ती;
      भङ्ग;
    पक्ष CPP_MOD:
      code = TRUNC_MOD_अभिव्यक्ती;
      भङ्ग;
    पक्ष CPP_PLUS:
      यदि (POINTER_TYPE_P (वृक्ष_TYPE (lhs.मूल्य)))
	code = POINTER_PLUS_अभिव्यक्ती;
      अन्यथा
	code = PLUS_अभिव्यक्ती;
      भङ्ग;
    पक्ष CPP_MINUS:
      यदि (POINTER_TYPE_P (वृक्ष_TYPE (lhs.मूल्य)))
	code = POINTER_DIFF_अभिव्यक्ती;
      अन्यथा
	code = MINUS_अभिव्यक्ती;
      भङ्ग;
    पक्ष CPP_LSHIFT:
      code = LSHIFT_अभिव्यक्ती;
      भङ्ग;
    पक्ष CPP_RSHIFT:
      code = RSHIFT_अभिव्यक्ती;
      भङ्ग;
    पक्ष CPP_LESS:
      code = LT_अभिव्यक्ती;
      भङ्ग;
    पक्ष CPP_GREATER:
      code = GT_अभिव्यक्ती;
      भङ्ग;
    पक्ष CPP_LESS_EQ:
      code = LE_अभिव्यक्ती;
      भङ्ग;
    पक्ष CPP_GREATER_EQ:
      code = GE_अभिव्यक्ती;
      भङ्ग;
    पक्ष CPP_EQ_EQ:
      code = EQ_अभिव्यक्ती;
      भङ्ग;
    पक्ष CPP_NOT_EQ:
      code = NE_अभिव्यक्ती;
      भङ्ग;
    पक्ष CPP_AND:
      code = BIT_AND_अभिव्यक्ती;
      भङ्ग;
    पक्ष CPP_XOR:
      code = BIT_XOR_अभिव्यक्ती;
      भङ्ग;
    पक्ष CPP_OR:
      code = BIT_IOR_अभिव्यक्ती;
      भङ्ग;
    पक्ष CPP_AND_AND:
      c_parser_error (parser, "%<&&%> not valid in GIMPLE");
      प्रत्यागम ret;
    पक्ष CPP_OR_OR:
      c_parser_error (parser, "%<||%> not valid in GIMPLE");
      प्रत्यागम ret;
    पक्ष CPP_NAME:
      {
	वृक्ष id = c_parser_peek_token (parser)->मूल्य;
	प्रति (auto &p : gimple_द्विमान_identifier_code)
	  {
	    यदि (strcmp (IDENTIFIER_POINTER (id), p.first) == 0)
	      {
		code = p.second;
		भङ्ग;
	      }
	  }
	यदि (code != ERROR_MARK)
	  भङ्ग;
      }
      /* Fallthru.  */
    स्वभाव:
      /* Not a binary expression.  */
      प्रत्यागम lhs;
    }
  location_t ret_loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  rhs = c_parser_gimple_postfix_expression (parser);
  यदि (lhs.मूल्य != error_mark_गाठ && rhs.मूल्य != error_mark_गाठ)
    ret.मूल्य = build2_loc (ret_loc, code, ret_type, lhs.मूल्य, rhs.मूल्य);
  प्रत्यागम ret;
}

/* Parse a gimple parentized binary expression.  */

स्थिर c_अभिव्यक्ती
c_parser_gimple_parentized_द्विमान_expression (gimple_parser &parser,
					      location_t op_loc,
					      वृक्ष_code code)
{
  संरचना c_अभिव्यक्ती ret;
  ret.set_error ();

  c_parser_consume_token (parser);
  यदि (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    प्रत्यागम ret;
  c_अभिव्यक्ती op1 = c_parser_gimple_postfix_expression (parser);
  यदि (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    प्रत्यागम ret;
  c_अभिव्यक्ती op2 = c_parser_gimple_postfix_expression (parser);
  यदि (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    प्रत्यागम ret;

  यदि (op1.मूल्य != error_mark_गाठ && op2.मूल्य != error_mark_गाठ)
    ret.मूल्य = build2_loc (op_loc,
			    code, वृक्ष_TYPE (op1.मूल्य), op1.मूल्य, op2.मूल्य);
  प्रत्यागम ret;
}

/* Parse a gimple parentized binary expression.  */

स्थिर c_अभिव्यक्ती
c_parser_gimple_parentized_ternary_expression (gimple_parser &parser,
					       location_t op_loc,
					       वृक्ष_code code)
{
  संरचना c_अभिव्यक्ती ret;
  ret.set_error ();

  c_parser_consume_token (parser);
  यदि (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    प्रत्यागम ret;
  c_अभिव्यक्ती op1 = c_parser_gimple_postfix_expression (parser);
  यदि (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    प्रत्यागम ret;
  c_अभिव्यक्ती op2 = c_parser_gimple_postfix_expression (parser);
  यदि (!c_parser_require (parser, CPP_COMMA, "expected %<)%>"))
    प्रत्यागम ret;
  c_अभिव्यक्ती op3 = c_parser_gimple_postfix_expression (parser);
  यदि (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    प्रत्यागम ret;

  यदि (op1.मूल्य != error_mark_गाठ
      && op2.मूल्य != error_mark_गाठ
      && op3.मूल्य != error_mark_गाठ)
    ret.मूल्य = build3_loc (op_loc,
			    code, वृक्ष_TYPE (op1.मूल्य),
			    op1.मूल्य, op2.मूल्य, op3.मूल्य);
  प्रत्यागम ret;
}

/* Parse gimple unary expression.

   gimple-unary-expression:
     gimple-postfix-expression
     unary-operator gimple-postfix-expression

   unary-operator: one of
     & * + - ~ abs_expr
*/

स्थिर c_अभिव्यक्ती
c_parser_gimple_unary_expression (gimple_parser &parser)
{
  संरचना c_अभिव्यक्ती ret, op;
  location_t op_loc = c_parser_peek_token (parser)->location;
  location_t finish;
  ret.set_error ();
  विकल्प (c_parser_peek_token (parser)->type)
    {
    पक्ष CPP_AND:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      mark_exp_read (op.मूल्य);
      प्रत्यागम gimple_parser_build_unary_op (op_loc, ADDR_अभिव्यक्ती, op);
    पक्ष CPP_MULT:
      {
	c_parser_consume_token (parser);
	op = c_parser_gimple_postfix_expression (parser);
	यदि (op.मूल्य == error_mark_गाठ)
	  प्रत्यागम ret;
	यदि (! POINTER_TYPE_P (वृक्ष_TYPE (op.मूल्य)))
	  {
	    error_at (op_loc, "expected pointer as argument of unary %<*%>");
	    प्रत्यागम ret;
	  }
	finish = op.get_finish ();
	location_t combined_loc = make_location (op_loc, op_loc, finish);
	ret.मूल्य = build_simple_mem_ref_loc (combined_loc, op.मूल्य);
	वृक्ष_SIDE_EFFECTS (ret.मूल्य)
	  = वृक्ष_THIS_VOLATILE (ret.मूल्य)
	  = TYPE_VOLATILE (वृक्ष_TYPE (वृक्ष_TYPE (op.मूल्य)));
	ret.src_range.m_start = op_loc;
	ret.src_range.m_finish = finish;
	प्रत्यागम ret;
      }
    पक्ष CPP_PLUS:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      प्रत्यागम gimple_parser_build_unary_op (op_loc, CONVERT_अभिव्यक्ती, op);
    पक्ष CPP_MINUS:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      प्रत्यागम gimple_parser_build_unary_op (op_loc, NEGATE_अभिव्यक्ती, op);
    पक्ष CPP_COMPL:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      प्रत्यागम gimple_parser_build_unary_op (op_loc, BIT_NOT_अभिव्यक्ती, op);
    पक्ष CPP_NOT:
      c_parser_error (parser, "%<!%> not valid in GIMPLE");
      प्रत्यागम ret;
    पक्ष CPP_KEYWORD:
      विकल्प (c_parser_peek_token (parser)->keyword)
	{
	पक्ष RID_REALPART:
	  c_parser_consume_token (parser);
	  op = c_parser_gimple_postfix_expression (parser);
	  प्रत्यागम gimple_parser_build_unary_op (op_loc, REALPART_अभिव्यक्ती, op);
	पक्ष RID_IMAGPART:
	  c_parser_consume_token (parser);
	  op = c_parser_gimple_postfix_expression (parser);
	  प्रत्यागम gimple_parser_build_unary_op (op_loc, IMAGPART_अभिव्यक्ती, op);
	स्वभाव:
	  प्रत्यागम c_parser_gimple_postfix_expression (parser);
	}
    पक्ष CPP_NAME:
	{
	  वृक्ष id = c_parser_peek_token (parser)->मूल्य;
	  यदि (strcmp (IDENTIFIER_POINTER (id), "__ABS") == 0)
	    {
	      c_parser_consume_token (parser);
	      op = c_parser_gimple_postfix_expression (parser);
	      प्रत्यागम gimple_parser_build_unary_op (op_loc, ABS_अभिव्यक्ती, op);
	    }
	  अन्यथा यदि (strcmp (IDENTIFIER_POINTER (id), "__ABSU") == 0)
	    {
	      c_parser_consume_token (parser);
	      op = c_parser_gimple_postfix_expression (parser);
	      प्रत्यागम gimple_parser_build_unary_op (op_loc, ABSU_अभिव्यक्ती, op);
	    }
	  अन्यथा यदि (strcmp (IDENTIFIER_POINTER (id), "__MIN") == 0)
	    प्रत्यागम c_parser_gimple_parentized_द्विमान_expression (parser,
								 op_loc,
								 MIN_अभिव्यक्ती);
	  अन्यथा यदि (strcmp (IDENTIFIER_POINTER (id), "__MAX") == 0)
	    प्रत्यागम c_parser_gimple_parentized_द्विमान_expression (parser,
								 op_loc,
								 MAX_अभिव्यक्ती);
	  अन्यथा यदि (strcmp (IDENTIFIER_POINTER (id), "__VEC_PERM") == 0)
	    प्रत्यागम c_parser_gimple_parentized_ternary_expression
			(parser, op_loc, VEC_PERM_अभिव्यक्ती);
	  अन्यथा यदि (strcmp (IDENTIFIER_POINTER (id), "__BIT_INSERT") == 0)
	    {
	      /* __BIT_INSERT '(' postfix-expression, postfix-expression,
			          integer ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      यदि (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_अभिव्यक्ती op0 = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_अभिव्यक्ती op1 = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_अभिव्यक्ती op2 = c_parser_gimple_postfix_expression (parser);
		  यदि (वृक्ष_CODE (op2.मूल्य) != INTEGER_CST
		      || !int_fits_type_p (op2.मूल्य, bitsizetype))
		    c_parser_error (parser, "expected constant offset");
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  यदि (op0.मूल्य != error_mark_गाठ
		      && op1.मूल्य != error_mark_गाठ
		      && वृक्ष_CODE (op2.मूल्य) == INTEGER_CST)
		    ret.मूल्य = build3_loc (loc, BIT_घाला_अभिव्यक्ती,
					    वृक्ष_TYPE (op0.मूल्य),
					    op0.मूल्य, op1.मूल्य,
					    fold_convert (bitsizetype,
							  op2.मूल्य));
		}
	      प्रत्यागम ret;
	    }
	  अन्यथा
	    प्रत्यागम c_parser_gimple_postfix_expression (parser);
	}
    स्वभाव:
      प्रत्यागम c_parser_gimple_postfix_expression (parser);
    }
}

/* Decompose ID into base name (ID until ver_offset) and VERSION.  Return
   true if ID matches a SSA name.  */

स्थिर तार्किक
c_parser_parse_ssa_name_id (वृक्ष id, unsigned *version, unsigned *ver_offset)
{
  ध्रुव वर्ण *token = IDENTIFIER_POINTER (id);
  ध्रुव वर्ण *var_version = strrchr (token, '_');
  यदि (! var_version)
    प्रत्यागम असत्य;

  *ver_offset = var_version - token;
  प्रति (ध्रुव वर्ण *p = var_version + 1; *p; ++p)
    यदि (! ISDIGIT (*p))
      प्रत्यागम असत्य;
  *version = atoi (var_version + 1);
  प्रत्यागम *version > 0;
}

/* Get at the actual SSA name ID with VERSION starting at VER_OFFSET.
   TYPE is the type if the SSA name is being declared.  */

स्थिर वृक्ष
c_parser_parse_ssa_name (gimple_parser &parser,
			 वृक्ष id, वृक्ष type, unsigned version,
			 unsigned ver_offset)
{
  वृक्ष name = NULL_वृक्ष;
  ध्रुव वर्ण *token = IDENTIFIER_POINTER (id);

  यदि (ver_offset == 0)
    {
      /* Anonymous unnamed SSA name.  */
      यदि (version < अंक_ssa_names)
	name = ssa_name (version);
      यदि (! name)
	{
	  यदि (! type)
	    {
	      c_parser_error (parser, "SSA name undeclared");
	      प्रत्यागम error_mark_गाठ;
	    }
	  name = make_ssa_name_fn (cfun, type, रिक्त, version);
	}
    }
  अन्यथा
    {
      यदि (version < अंक_ssa_names)
	name = ssa_name (version);
      यदि (! name)
	{
	  /* Separate var name from version.  */
	  वर्ण *var_name = XNEWVEC (वर्ण, ver_offset + 1);
	  memcpy (var_name, token, ver_offset);
	  var_name[ver_offset] = '\0';
	  /* lookup for parent decl.  */
	  id = get_identifier (var_name);
	  वृक्ष parent = lookup_name (id);
	  XDELETEVEC (var_name);
	  यदि (! parent || parent == error_mark_गाठ)
	    {
	      c_parser_error (parser, "base variable or SSA name undeclared");
	      प्रत्यागम error_mark_गाठ;
	    }
	  यदि (!(VAR_P (parent)
		|| वृक्ष_CODE (parent) == PARM_DECL
		|| वृक्ष_CODE (parent) == RESULT_DECL))
	    {
	      error ("invalid base %qE for SSA name", parent);
	      प्रत्यागम error_mark_गाठ;
	    }
	  name = make_ssa_name_fn (cfun, parent,
				   gimple_build_nop (), version);
	}
    }

  प्रत्यागम name;
}

/* Parse a gimple call to an internal function.

   gimple-call-internal:
     . identifier ( gimple-argument-expression-list[opt] )  */

स्थिर संरचना c_अभिव्यक्ती
c_parser_gimple_call_internal (gimple_parser &parser)
{
  संरचना c_अभिव्यक्ती अभिव्यक्ती;
  अभिव्यक्ती.set_error ();

  gcc_assert (c_parser_next_token_is (parser, CPP_DOT));
  c_parser_consume_token (parser);
  location_t loc = c_parser_peek_token (parser)->location;
  यदि (!c_parser_next_token_is (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_kind != C_ID_ID)
    {
      c_parser_error (parser, "expecting internal function name");
      प्रत्यागम अभिव्यक्ती;
    }
  वृक्ष id = c_parser_peek_token (parser)->मूल्य;
  internal_fn ifn = lookup_internal_fn (IDENTIFIER_POINTER (id));
  c_parser_consume_token (parser);
  यदि (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    {
      auto_vec<वृक्ष> exprlist;
      यदि (!c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_gimple_अभिव्यक्ती_list (parser, &exprlist);
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      यदि (ifn == IFN_LAST)
	error_at (loc, "unknown internal function %qE", id);
      अन्यथा
	{
	  अभिव्यक्ती.मूल्य = build_call_अभिव्यक्ती_internal_loc_array
	    (loc, ifn, void_type_गाठ, exprlist.length (),
	     exprlist.address ());
	  अभिव्यक्ती.original_code = ERROR_MARK;
	  अभिव्यक्ती.original_type = रिक्त;
	  अभिव्यक्ती.m_decimal = 0;
	}
    }
  प्रत्यागम अभिव्यक्ती;
}

/* Parse '<' type [',' alignment] '>' and return a type on success
   and NULL_TREE on error.  */

स्थिर वृक्ष
c_parser_gimple_typespec (gimple_parser &parser)
{
  संरचना c_type_name *type_name = रिक्त;
  वृक्ष alignment = NULL_वृक्ष;
  यदि (c_parser_require (parser, CPP_LESS, "expected %<<%>"))
    {
      type_name = c_parser_type_name (parser);
      /* Optional alignment.  */
      यदि (c_parser_next_token_is (parser, CPP_COMMA))
	{
	  c_parser_consume_token (parser);
	  alignment
	      = c_parser_gimple_postfix_expression (parser).मूल्य;
	}
      c_parser_skip_until_found (parser,
				 CPP_GREATER, "expected %<>%>");
    }
  यदि (!type_name)
    प्रत्यागम NULL_वृक्ष;
  वृक्ष tem;
  वृक्ष type = groktypename (type_name, &tem, रिक्त);
  यदि (alignment)
    type = build_aligned_type (type, वृक्ष_to_uhwi (alignment));
  प्रत्यागम type;
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

स्थिर संरचना c_अभिव्यक्ती
c_parser_gimple_postfix_expression (gimple_parser &parser, वृक्ष ret_type)
{
  location_t loc = c_parser_peek_token (parser)->location;
  source_range tok_range = c_parser_peek_token (parser)->get_range ();
  संरचना c_अभिव्यक्ती अभिव्यक्ती;
  अभिव्यक्ती.set_error ();
  विकल्प (c_parser_peek_token (parser)->type)
    {
    पक्ष CPP_संख्या:
      अभिव्यक्ती.मूल्य = c_parser_peek_token (parser)->मूल्य;
      set_c_अभिव्यक्ती_source_range (&अभिव्यक्ती, tok_range);
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      भङ्ग;
    पक्ष CPP_CHAR:
    पक्ष CPP_CHAR16:
    पक्ष CPP_CHAR32:
    पक्ष CPP_UTF8CHAR:
    पक्ष CPP_WCHAR:
      अभिव्यक्ती.मूल्य = c_parser_peek_token (parser)->मूल्य;
      set_c_अभिव्यक्ती_source_range (&अभिव्यक्ती, tok_range);
      c_parser_consume_token (parser);
      भङ्ग;
    पक्ष CPP_STRING:
    पक्ष CPP_STRING16:
    पक्ष CPP_STRING32:
    पक्ष CPP_WSTRING:
    पक्ष CPP_UTF8STRING:
      अभिव्यक्ती = c_parser_string_literal (parser, असत्य, सत्य);
      भङ्ग;
    पक्ष CPP_DOT:
      अभिव्यक्ती = c_parser_gimple_call_internal (parser);
      भङ्ग;
    पक्ष CPP_NAME:
      यदि (c_parser_peek_token (parser)->id_kind == C_ID_ID)
	{
	  वृक्ष id = c_parser_peek_token (parser)->मूल्य;
	  यदि (strcmp (IDENTIFIER_POINTER (id), "__MEM") == 0)
	    {
	      /* __MEM '<' type-name [ ',' number ] '>'
	               '(' [ '(' type-name ')' ] unary-expression
			   [ '+' number ]
			   [ ',' number ]
			   [ ',' number ':' number ] ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      वृक्ष type = c_parser_gimple_typespec (parser);
	      संरचना c_अभिव्यक्ती ptr, alias_off, step, index, index2;
	      ptr.मूल्य = error_mark_गाठ;
	      alias_off.मूल्य = NULL_वृक्ष;
	      step.मूल्य = NULL_वृक्ष;
	      index.मूल्य = NULL_वृक्ष;
	      index2.मूल्य = NULL_वृक्ष;
	      unsigned short clique = 0;
	      unsigned short base = 0;
	      तार्किक reverse_order = असत्य;
	      संरचना c_अभिव्यक्ती ro;
	      यदि (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  वृक्ष alias_type = NULL_वृक्ष;
		  /* Optional alias-type cast.  */
		  यदि (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
		    {
		      c_parser_consume_token (parser);
		      संरचना c_type_name *alias_type_name
			= c_parser_type_name (parser);
		      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
						 "expected %<)%>");
		      यदि (alias_type_name)
			{
			  वृक्ष tem;
			  alias_type = groktypename (alias_type_name,
						     &tem, रिक्त);
			}
		    }
		  ptr = c_parser_gimple_unary_expression (parser);
		  यदि (ptr.मूल्य == error_mark_गाठ
		      || ! POINTER_TYPE_P (वृक्ष_TYPE (ptr.मूल्य)))
		    {
		      यदि (ptr.मूल्य != error_mark_गाठ)
			error_at (ptr.get_start (),
				  "invalid type of %<__MEM%> operand");
		      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
						 "expected %<)%>");
		      प्रत्यागम अभिव्यक्ती;
		    }
		  यदि (! alias_type)
		    alias_type = वृक्ष_TYPE (ptr.मूल्य);
		  /* Optional constant offset.  */
		  यदि (c_parser_next_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      alias_off = c_parser_gimple_postfix_expression (parser);
		    }
		  यदि (c_parser_next_token_is (parser, CPP_MULT))
		    {
		      std::swap (index, alias_off);
		      c_parser_consume_token (parser);
		      step = c_parser_gimple_postfix_expression (parser);
		    }
		  अन्यथा यदि (c_parser_next_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      index = c_parser_gimple_postfix_expression (parser);
		      यदि (c_parser_next_token_is (parser, CPP_MULT))
			{
			  c_parser_consume_token (parser);
			  step = c_parser_gimple_postfix_expression (parser);
			}
		      अन्यथा
			std::swap (index, index2);
		    }
		  अन्यथा यदि (alias_off.मूल्य
			   && वृक्ष_CODE (alias_off.मूल्य) != INTEGER_CST)
		    std::swap (alias_off, index2);
		  यदि (c_parser_next_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      index2 = c_parser_gimple_postfix_expression (parser);
		    }
		  यदि (alias_off.मूल्य)
		    {
		      यदि (वृक्ष_CODE (alias_off.मूल्य) != INTEGER_CST)
			error_at (alias_off.get_start (),
				  "expected constant offset for %<__MEM%> "
				  "operand");
		      alias_off.मूल्य = fold_convert (alias_type,
						      alias_off.मूल्य);
		    }
		  अन्यथा
		    alias_off.मूल्य = build_int_cst (alias_type, 0);
		  यदि (step.मूल्य)
		    {
		      यदि (वृक्ष_CODE (step.मूल्य) != INTEGER_CST)
			error_at (step.get_start (),
				  "expected constant step for %<__MEM%> "
				  "operand");
		    }
		  यदि (c_parser_next_token_is (parser, CPP_COMMA))
		    {
		      संरचना c_अभिव्यक्ती cl, ba;
		      तार्किक has_clb = सत्य;
		      c_parser_consume_token (parser);
		      cl = c_parser_gimple_postfix_expression (parser);
		      यदि (!c_parser_next_token_is (parser, CPP_COLON))
			{
			  ro = cl;
			  unsigned HOST_WIDE_INT tmp = 0;
			  यदि (!वृक्ष_fits_uhwi_p (ro.मूल्य)
			      || (tmp = वृक्ष_to_uhwi (ro.मूल्य)) > 1)
			    error_at (ro.get_start (),
				      "invalid reverse order value");
			  reverse_order = tmp;
			  has_clb = असत्य;
			  यदि (c_parser_next_token_is (parser, CPP_COMMA))
			    {
			      c_parser_consume_token (parser);
			      cl = c_parser_gimple_postfix_expression (parser);
		              has_clb = सत्य;
			    }
			}
		      यदि (has_clb
			  && c_parser_require (parser,
					       CPP_COLON, "expected %<:%>"))
			{
			  ba = c_parser_gimple_postfix_expression (parser);
			  यदि (!वृक्ष_fits_uhwi_p (cl.मूल्य)
			      || !वृक्ष_fits_uhwi_p (ba.मूल्य)
			      || compare_वृक्ष_int (cl.मूल्य,
						   (clique = वृक्ष_to_uhwi
								(cl.मूल्य)))
			      || compare_वृक्ष_int (ba.मूल्य,
						   (base = वृक्ष_to_uhwi
								 (ba.मूल्य))))
			    error_at (cl.get_start (),
				      "invalid clique/base pair");
			}
		    }
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      यदि (! type || c_parser_error (parser))
		{
		  c_parser_set_error (parser, असत्य);
		  प्रत्यागम अभिव्यक्ती;
		}
	      यदि (index.मूल्य || step.मूल्य || index2.मूल्य)
		अभिव्यक्ती.मूल्य = build5_loc (loc, TARGET_MEM_REF,
					 type, ptr.मूल्य, alias_off.मूल्य,
					 index.मूल्य, step.मूल्य, index2.मूल्य);
	      अन्यथा
		अभिव्यक्ती.मूल्य = build2_loc (loc, MEM_REF,
					 type, ptr.मूल्य, alias_off.मूल्य);
	      यदि (clique != 0)
		{
		  cfun->last_clique = MAX (cfun->last_clique, clique);
		  MR_DEPENDENCE_CLIQUE (अभिव्यक्ती.मूल्य) = clique;
		  MR_DEPENDENCE_BASE (अभिव्यक्ती.मूल्य) = base;
		}
	      यदि (reverse_order)
		{
		  यदि (वृक्ष_CODE (अभिव्यक्ती.मूल्य) == MEM_REF)
		    REF_REVERSE_STORAGE_ORDER (अभिव्यक्ती.मूल्य) = reverse_order;
		  अन्यथा
		    error_at (ro.get_start (),
			      "target mem ref cannot have reverse order");
		}
	      भङ्ग;
	    }
	  अन्यथा यदि (strcmp (IDENTIFIER_POINTER (id), "__VIEW_CONVERT") == 0)
	    {
	      /* __VIEW_CONVERT '<' type-name [ ',' number ] '>'
	                        '(' postfix-expression ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      वृक्ष type = c_parser_gimple_typespec (parser);
	      यदि (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_अभिव्यक्ती op = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  यदि (type && op.मूल्य != error_mark_गाठ)
		    अभिव्यक्ती.मूल्य = build1_loc (loc, VIEW_CONVERT_अभिव्यक्ती,
					     type, op.मूल्य);
		}
	      भङ्ग;
	    }
	  अन्यथा यदि (strcmp (IDENTIFIER_POINTER (id), "__BIT_FIELD_REF") == 0)
	    {
	      /* __BIT_FIELD_REF '<' type-name [ ',' number ] '>'
	                        '(' postfix-expression, integer, integer ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      वृक्ष type = c_parser_gimple_typespec (parser);
	      यदि (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_अभिव्यक्ती op0 = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_अभिव्यक्ती op1 = c_parser_gimple_postfix_expression (parser);
		  यदि (वृक्ष_CODE (op1.मूल्य) != INTEGER_CST
		      || !int_fits_type_p (op1.मूल्य, bitsizetype))
		    c_parser_error (parser, "expected constant size");
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_अभिव्यक्ती op2 = c_parser_gimple_postfix_expression (parser);
		  यदि (वृक्ष_CODE (op2.मूल्य) != INTEGER_CST
		      || !int_fits_type_p (op2.मूल्य, bitsizetype))
		    c_parser_error (parser, "expected constant offset");
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  यदि (type
		      && op0.मूल्य != error_mark_गाठ
		      && वृक्ष_CODE (op1.मूल्य) == INTEGER_CST
		      && वृक्ष_CODE (op2.मूल्य) == INTEGER_CST)
		    अभिव्यक्ती.मूल्य = build3_loc (loc, BIT_FIELD_REF, type,
					     op0.मूल्य,
					     fold_convert (bitsizetype,
							   op1.मूल्य),
					     fold_convert (bitsizetype,
							   op2.मूल्य));
		}
	      भङ्ग;
	    }
	  अन्यथा यदि (strcmp (IDENTIFIER_POINTER (id), "__CLOBBER") == 0)
	    {
	      /* __CLOBBER [ '(' bob | eob | bos | eos ')' ]  */
	      clobber_kind kind = CLOBBER_UNDEF;
	      c_parser_consume_token (parser);
	      यदि (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
		{
		  c_parser_consume_token (parser);
		  auto tok = c_parser_peek_token (parser);
		  यदि (c_parser_require (parser, CPP_NAME,
					"expected clobber kind"))
		    {
		      ध्रुव वर्ण *kind_str = IDENTIFIER_POINTER (tok->मूल्य);
		      यदि (strcmp (kind_str, "bos") == 0)
			kind = CLOBBER_STORAGE_BEGIN;
		      अन्यथा यदि (strcmp (kind_str, "bob") == 0)
			kind = CLOBBER_OBJECT_BEGIN;
		      अन्यथा यदि (strcmp (kind_str, "eob") == 0)
			kind = CLOBBER_OBJECT_END;
		      अन्यथा यदि (strcmp (kind_str, "eos") == 0)
			kind = CLOBBER_STORAGE_END;
		      अन्यथा
			c_parser_error (parser, "expected one of %<bos%>, "
					"%<eos%>, %<bob>, %<eob%>");
		    }
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      /* We infer the (redundant) type from the LHS.  */
	      अभिव्यक्ती.मूल्य = build_clobber (ret_type, kind);
	      भङ्ग;
	    }
	  अन्यथा यदि (strcmp (IDENTIFIER_POINTER (id), "_Literal") == 0)
	    {
	      /* _Literal '(' type-name ')' ( [ '-' ] constant | constructor ) */
	      c_parser_consume_token (parser);
	      वृक्ष type = NULL_वृक्ष;
	      यदि (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  संरचना c_type_name *type_name = c_parser_type_name (parser);
		  वृक्ष tem;
		  यदि (type_name)
		    type = groktypename (type_name, &tem, रिक्त);
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      यदि (! type)
		{
		  c_parser_error (parser, "invalid _Literal");
		  प्रत्यागम अभिव्यक्ती;
		}
	      यदि (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
		{
		  c_parser_consume_token (parser);
		  यदि (!AGGREGATE_TYPE_P (type)
		      && !VECTOR_TYPE_P (type))
		    {
		      c_parser_error (parser, "invalid type for _Literal with "
				      "constructor");
		      c_parser_skip_until_found (parser, CPP_CLOSE_BRACE,
						 "expected %<}%>");
		      प्रत्यागम अभिव्यक्ती;
		    }
		  vec<constructor_elt, va_gc> *v = रिक्त;
		  तार्किक constant_p = सत्य;
		  यदि (VECTOR_TYPE_P (type)
		      && !c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
		    {
		      vec_alloc (v, TYPE_VECTOR_SUBPARTS (type).to_constant ());
		      कुरु
			{
			  वृक्ष val
			    = c_parser_gimple_postfix_expression (parser).मूल्य;
			  यदि (! val
			      || val == error_mark_गाठ
			      || (! CONSTANT_CLASS_P (val)
				  && ! SSA_VAR_P (val)))
			    {
			      c_parser_error (parser, "invalid _Literal");
			      प्रत्यागम अभिव्यक्ती;
			    }
			  CONSTRUCTOR_APPEND_ELT (v, NULL_वृक्ष, val);
			  यदि (! CONSTANT_CLASS_P (val))
			    constant_p = असत्य;
			  यदि (c_parser_next_token_is (parser, CPP_COMMA))
			    c_parser_consume_token (parser);
			  अन्यथा
			    भङ्ग;
			}
		      यावत् (1);
		    }
		  यदि (c_parser_require (parser, CPP_CLOSE_BRACE,
					"expected %<}%>"))
		    {
		      यदि (v && constant_p)
			अभिव्यक्ती.मूल्य = build_vector_from_ctor (type, v);
		      अन्यथा
			अभिव्यक्ती.मूल्य = build_constructor (type, v);
		    }
		  अन्यथा
		    {
		      c_parser_skip_until_found (parser, CPP_CLOSE_BRACE,
						 "expected %<}%>");
		      प्रत्यागम अभिव्यक्ती;
		    }
		}
	      अन्यथा
		{
		  तार्किक neg_p, addr_p;
		  यदि ((neg_p = c_parser_next_token_is (parser, CPP_MINUS)))
		    c_parser_consume_token (parser);
		  यदि ((addr_p = c_parser_next_token_is (parser, CPP_AND)))
		    c_parser_consume_token (parser);
		  वृक्ष val = c_parser_gimple_postfix_expression (parser).मूल्य;
		  यदि (! val
		      || val == error_mark_गाठ
		      || (!CONSTANT_CLASS_P (val) && !addr_p))
		    {
		      c_parser_error (parser, "invalid _Literal");
		      प्रत्यागम अभिव्यक्ती;
		    }
		  यदि (addr_p)
		    {
		      val = build1 (ADDR_अभिव्यक्ती, type, val);
		      यदि (!is_gimple_invariant_address (val))
			{
			  c_parser_error (parser, "invalid _Literal");
			  प्रत्यागम अभिव्यक्ती;
			}
		    }
		  यदि (neg_p)
		    {
		      val = const_unop (NEGATE_अभिव्यक्ती, वृक्ष_TYPE (val), val);
		      यदि (! val)
			{
			  c_parser_error (parser, "invalid _Literal");
			  प्रत्यागम अभिव्यक्ती;
			}
		    }
		  अभिव्यक्ती.मूल्य = fold_convert (type, val);
		}
	      प्रत्यागम अभिव्यक्ती;
	    }

	  /* SSA name.  */
	  unsigned version, ver_offset;
	  यदि (! lookup_name (id)
	      && c_parser_parse_ssa_name_id (id, &version, &ver_offset))
	    {
	      c_parser_consume_token (parser);
	      अभिव्यक्ती.मूल्य = c_parser_parse_ssa_name (parser, id, NULL_वृक्ष,
						    version, ver_offset);
	      यदि (अभिव्यक्ती.मूल्य == error_mark_गाठ)
		प्रत्यागम अभिव्यक्ती;
	      set_c_अभिव्यक्ती_source_range (&अभिव्यक्ती, tok_range);
	      /* For default definition SSA names.  */
	      यदि (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
		  && c_parser_peek_2nd_token (parser)->type == CPP_NAME
		  && strcmp ("D",
			     IDENTIFIER_POINTER
			       (c_parser_peek_2nd_token (parser)->मूल्य)) == 0
		  && c_parser_peek_nth_token (parser, 3)->type == CPP_CLOSE_PAREN)
		{
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		  यदि (! SSA_NAME_IS_DEFAULT_DEF (अभिव्यक्ती.मूल्य))
		    {
		      यदि (!SSA_NAME_VAR (अभिव्यक्ती.मूल्य))
			{
			  error_at (loc, "anonymous SSA name cannot have"
				    " default definition");
			  अभिव्यक्ती.मूल्य = error_mark_गाठ;
			  प्रत्यागम अभिव्यक्ती;
			}
		      set_ssa_default_def (cfun, SSA_NAME_VAR (अभिव्यक्ती.मूल्य),
					   अभिव्यक्ती.मूल्य);
		      SSA_NAME_DEF_STMT (अभिव्यक्ती.मूल्य) = gimple_build_nop ();
		    }
		}
	    }
	  अन्यथा
	    {
	      c_parser_consume_token (parser);
	      अभिव्यक्ती.मूल्य
		= build_external_ref (loc, id,
				      (c_parser_peek_token (parser)->type
				       == CPP_OPEN_PAREN), &अभिव्यक्ती.original_type);
	      set_c_अभिव्यक्ती_source_range (&अभिव्यक्ती, tok_range);
	    }
	  भङ्ग;
	}
      /* Fallthru.  */
    स्वभाव:
      c_parser_error (parser, "expected expression");
      अभिव्यक्ती.set_error ();
      भङ्ग;
    }
  यदि (अभिव्यक्ती.मूल्य == error_mark_गाठ)
    प्रत्यागम अभिव्यक्ती;
  प्रत्यागम c_parser_gimple_postfix_expression_after_primary
    (parser, अभिव्यक्ती_LOC_OR_LOC (अभिव्यक्ती.मूल्य, loc), अभिव्यक्ती);
}

/* Parse a gimple postfix expression after the initial primary or compound
   literal.  */

स्थिर संरचना c_अभिव्यक्ती
c_parser_gimple_postfix_expression_after_primary (gimple_parser &parser,
						  location_t अभिव्यक्ती_loc,
						  संरचना c_अभिव्यक्ती अभिव्यक्ती)
{
  location_t start;
  location_t finish;
  वृक्ष ident;
  location_t comp_loc;

  यावत् (सत्य)
    {
      location_t op_loc = c_parser_peek_token (parser)->location;
      विकल्प (c_parser_peek_token (parser)->type)
	{
	पक्ष CPP_OPEN_SQUARE:
	  {
	    c_parser_consume_token (parser);
	    वृक्ष idx = c_parser_gimple_unary_expression (parser).मूल्य;

	    यदि (! c_parser_require (parser, CPP_CLOSE_SQUARE, "expected %<]%>"))
	      {
		c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE, रिक्त);
		भङ्ग;
	      }

	    start = अभिव्यक्ती.get_start ();
	    finish = c_parser_tokens_buf (parser, 0)->location;
	    अभिव्यक्ती.मूल्य = build_array_ref (op_loc, अभिव्यक्ती.मूल्य, idx);
	    set_c_अभिव्यक्ती_source_range (&अभिव्यक्ती, start, finish);
	    अभिव्यक्ती.m_decimal = 0;

	    अभिव्यक्ती.original_code = ERROR_MARK;
	    अभिव्यक्ती.original_type = रिक्त;
	    भङ्ग;
	  }
	पक्ष CPP_OPEN_PAREN:
	  {
	    /* Function call.  */
	    c_parser_consume_token (parser);
	    auto_vec<वृक्ष> exprlist;
	    यदि (! c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	      c_parser_gimple_अभिव्यक्ती_list (parser, &exprlist);
	    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    यदि (!FUNC_OR_METHOD_TYPE_P (वृक्ष_TYPE (अभिव्यक्ती.मूल्य)))
	      {
		c_parser_error (parser, "invalid call to non-function");
		अभिव्यक्ती.set_error ();
		भङ्ग;
	      }
	    अभिव्यक्ती.मूल्य = build_call_array_loc
		(अभिव्यक्ती_loc, वृक्ष_TYPE (वृक्ष_TYPE (अभिव्यक्ती.मूल्य)),
		 अभिव्यक्ती.मूल्य, exprlist.length (), exprlist.address ());
	    अभिव्यक्ती.m_decimal = 0;
	    अभिव्यक्ती.original_code = ERROR_MARK;
	    अभिव्यक्ती.original_type = रिक्त;
	    भङ्ग;
	  }
	पक्ष CPP_DOT:
	  {
	    /* Structure element reference.  */
	    c_parser_consume_token (parser);
	    यदि (c_parser_next_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		ident = comp_tok->मूल्य;
		comp_loc = comp_tok->location;
	      }
	    अन्यथा
	      {
		c_parser_error (parser, "expected identifier");
		अभिव्यक्ती.set_error ();
		अभिव्यक्ती.original_code = ERROR_MARK;
		अभिव्यक्ती.original_type = रिक्त;
		प्रत्यागम अभिव्यक्ती;
	      }
	    start = अभिव्यक्ती.get_start ();
	    finish = c_parser_peek_token (parser)->get_finish ();
	    c_parser_consume_token (parser);
	    अभिव्यक्ती.मूल्य = build_component_ref (op_loc, अभिव्यक्ती.मूल्य, ident,
					      comp_loc, UNKNOWN_LOCATION);
	    set_c_अभिव्यक्ती_source_range (&अभिव्यक्ती, start, finish);
	    अभिव्यक्ती.m_decimal = 0;
	    अभिव्यक्ती.original_code = ERROR_MARK;
	    यदि (वृक्ष_CODE (अभिव्यक्ती.मूल्य) != COMPONENT_REF)
	      अभिव्यक्ती.original_type = रिक्त;
	    अन्यथा
	      {
		/* Remember the original type of a bitfield.  */
		वृक्ष field = वृक्ष_OPERAND (अभिव्यक्ती.मूल्य, 1);
		यदि (वृक्ष_CODE (field) != FIELD_DECL)
		  अभिव्यक्ती.original_type = रिक्त;
		अन्यथा
		  अभिव्यक्ती.original_type = DECL_BIT_FIELD_TYPE (field);
	      }
	    भङ्ग;
	  }
	पक्ष CPP_DEREF:
	  {
	    /* Structure element reference.  */
	    यदि (!POINTER_TYPE_P (वृक्ष_TYPE (अभिव्यक्ती.मूल्य)))
	      {
		c_parser_error (parser, "dereference of non-pointer");
		अभिव्यक्ती.set_error ();
		अभिव्यक्ती.original_code = ERROR_MARK;
		अभिव्यक्ती.original_type = रिक्त;
		प्रत्यागम अभिव्यक्ती;
	      }
	    c_parser_consume_token (parser);
	    यदि (c_parser_next_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		ident = comp_tok->मूल्य;
		comp_loc = comp_tok->location;
	      }
	    अन्यथा
	      {
		c_parser_error (parser, "expected identifier");
		अभिव्यक्ती.set_error ();
		अभिव्यक्ती.original_code = ERROR_MARK;
		अभिव्यक्ती.original_type = रिक्त;
		प्रत्यागम अभिव्यक्ती;
	      }
	    start = अभिव्यक्ती.get_start ();
	    finish = c_parser_peek_token (parser)->get_finish ();
	    c_parser_consume_token (parser);
	    अभिव्यक्ती.मूल्य = build_component_ref (op_loc,
					      build_simple_mem_ref_loc
					        (op_loc, अभिव्यक्ती.मूल्य),
					      ident, comp_loc,
					      अभिव्यक्ती.get_location ());
	    set_c_अभिव्यक्ती_source_range (&अभिव्यक्ती, start, finish);
	    अभिव्यक्ती.m_decimal = 0;
	    अभिव्यक्ती.original_code = ERROR_MARK;
	    यदि (वृक्ष_CODE (अभिव्यक्ती.मूल्य) != COMPONENT_REF)
	      अभिव्यक्ती.original_type = रिक्त;
	    अन्यथा
	      {
		/* Remember the original type of a bitfield.  */
		वृक्ष field = वृक्ष_OPERAND (अभिव्यक्ती.मूल्य, 1);
		यदि (वृक्ष_CODE (field) != FIELD_DECL)
		  अभिव्यक्ती.original_type = रिक्त;
		अन्यथा
		  अभिव्यक्ती.original_type = DECL_BIT_FIELD_TYPE (field);
	      }
	    भङ्ग;
	  }
	स्वभाव:
	  प्रत्यागम अभिव्यक्ती;
	}
    }
}

/* Parse expression list.

   gimple-expr-list:
     gimple-unary-expression
     gimple-expr-list , gimple-unary-expression

 */

स्थिर शून्य
c_parser_gimple_अभिव्यक्ती_list (gimple_parser &parser, vec<वृक्ष> *ret)
{
  संरचना c_अभिव्यक्ती अभिव्यक्ती;

  अभिव्यक्ती = c_parser_gimple_unary_expression (parser);
  ret->safe_ढकला (अभिव्यक्ती.मूल्य);
  यावत् (c_parser_next_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      अभिव्यक्ती = c_parser_gimple_unary_expression (parser);
      ret->safe_ढकला (अभिव्यक्ती.मूल्य);
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
  वृक्ष name = c_parser_peek_token (parser)->मूल्य;
  location_t loc1 = c_parser_peek_token (parser)->location;
  gcc_assert (c_parser_next_token_is (parser, CPP_NAME));
  c_parser_consume_token (parser);
  gcc_assert (c_parser_next_token_is (parser, CPP_COLON));
  c_parser_consume_token (parser);
  वृक्ष label = define_label (loc1, name);
  यदि (label)
    gimple_seq_add_stmt_without_update (seq, gimple_build_label (label));
  प्रत्यागम;
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
  यदि (c_parser_next_token_is_not (parser, CPP_OPEN_PAREN))
    प्रत्यागम;
  c_parser_consume_token (parser);

  specs->entry_bb_मोजणी = profile_मोजणी::uninitialized ();
  यावत् (c_parser_next_token_is (parser, CPP_NAME))
    {
      profile_quality quality;
      ध्रुव वर्ण *op = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य);
      c_parser_consume_token (parser);
      यदि (! strcmp (op, "startwith"))
	{
	  यदि (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    प्रत्यागम;
	  यदि (c_parser_next_token_is_not (parser, CPP_STRING))
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"expected pass name");
	      प्रत्यागम;
	    }
	  pass = xstrdup (वृक्ष_STRING_POINTER
			  (c_parser_string_literal (parser, असत्य,
						    असत्य).मूल्य));
	  यदि (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<(%>"))
	    प्रत्यागम;
	}
      अन्यथा यदि (parse_profile_quality (op, &quality))
	{
	  वृक्ष q;
	  यदि (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    प्रत्यागम;

	  यदि (!c_parser_next_token_is (parser, CPP_संख्या)
	      || (वृक्ष_CODE (q = c_parser_peek_token (parser)->मूल्य)
		  != INTEGER_CST))
	    {
	      c_parser_error (parser, "expected count value");
	      प्रत्यागम;
	    }

	  specs->entry_bb_मोजणी
	    = profile_मोजणी::from_gcov_type (वृक्ष_INT_CST_खालचा (q), quality);
	  c_parser_consume_token (parser);
	  यदि (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    प्रत्यागम;
	}
      अन्यथा यदि (specs->declspec_il != cdil_gimple)
	/* Allow only one IL specifier and none on RTL.  */
	;
      अन्यथा यदि (! strcmp (op, "cfg"))
	specs->declspec_il = cdil_gimple_cfg;
      अन्यथा यदि (! strcmp (op, "ssa"))
	specs->declspec_il = cdil_gimple_ssa;
      अन्यथा
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "invalid operation");
	  प्रत्यागम;
	}
     यदि (c_parser_next_token_is (parser, CPP_COMMA))
       c_parser_consume_token (parser);
    }

  यदि (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    प्रत्यागम;

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
  c_parser_declspecs (parser, specs, सत्य, सत्य, सत्य,
		      सत्य, सत्य, सत्य, सत्य, cla_nonabstract_decl);
  finish_declspecs (specs);

  /* Provide better error recovery.  Note that a type name here is usually
     better diagnosed as a redeclaration.  */
  यदि (c_parser_next_token_starts_declspecs (parser)
      && ! c_parser_next_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<;%>");
      c_parser_set_error (parser, असत्य);
      प्रत्यागम;
    }

  तार्किक dummy = असत्य;
  declarator = c_parser_declarator (parser,
				    specs->typespec_kind != ctsk_none,
				    C_DTR_NORMAL, &dummy);

  यदि (!c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_error (parser, "expected %<;%>");
      प्रत्यागम;
    }
  यदि (declarator)
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
      यावत् (id_declarator->kind == cdk_pointer)
	id_declarator = id_declarator->declarator;
      यदि (id_declarator->kind == cdk_id
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
	  वृक्ष type = specs->type;
	  यावत् (p->kind == cdk_pointer)
	    {
	      type = build_pointer_type (type);
	      p = p->declarator;
	    }
	  c_parser_parse_ssa_name (parser, id_declarator->u.id.id, type,
				   version, ver_offset);
	}
      अन्यथा
	{
	  वृक्ष postfix_attrs = NULL_वृक्ष;
	  वृक्ष all_prefix_attrs = specs->attrs;
	  specs->attrs = रिक्त;
	  वृक्ष decl = start_decl (declarator, specs, असत्य,
				  chainon (postfix_attrs, all_prefix_attrs));
	  यदि (decl)
	    finish_decl (decl, UNKNOWN_LOCATION, NULL_वृक्ष, NULL_वृक्ष,
			 NULL_वृक्ष);
	}
    }
}

/* Parse gimple goto statement.  */

स्थिर शून्य
c_parser_gimple_goto_stmt (gimple_parser &parser,
			   location_t loc, वृक्ष label, gimple_seq *seq)
{
  यदि (cfun->curr_properties & PROP_cfg)
    {
      पूर्णाङ्क dest_index;
      profile_probability prob;
      यदि (c_parser_gimple_parse_bb_spec_edge_probability (label, parser,
							  &dest_index, &prob))
	{
	  parser.ढकला_edge (parser.current_bb->index, dest_index,
			    EDGE_FALLTHRU, prob);
	  प्रत्यागम;
	}
    }
  वृक्ष decl = lookup_label_for_goto (loc, label);
  gimple_seq_add_stmt_without_update (seq, gimple_build_goto (decl));
}

/* Parse a parenthesized condition.
   gimple-condition:
     ( gimple-binary-expression )    */

स्थिर वृक्ष
c_parser_gimple_paren_condition (gimple_parser &parser)
{
  यदि (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    प्रत्यागम error_mark_गाठ;
  वृक्ष cond
    = c_parser_gimple_द्विमान_expression (parser, boolean_type_गाठ).मूल्य;
  यदि (cond != error_mark_गाठ
      && ! COMPARISON_CLASS_P (cond)
      && ! CONSTANT_CLASS_P (cond)
      && ! SSA_VAR_P (cond))
    {
      c_parser_error (parser, "comparison required");
      cond = error_mark_गाठ;
    }
  यदि (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    प्रत्यागम error_mark_गाठ;
  प्रत्यागम cond;
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

  यदि ((c_parser_next_token_is (parser, CPP_KEYWORD)
       && c_parser_peek_token (parser)->keyword == RID_AT_FINALLY)
      || (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_token (parser)->id_kind == C_ID_ID
	  && strcmp (IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य),
		     "finally") == 0))
    {
      gimple_seq finseq = रिक्त;
      c_parser_consume_token (parser);
      c_parser_gimple_compound_statement (parser, &finseq);

      यदि (c_parser_next_token_is (parser, CPP_KEYWORD)
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
  अन्यथा यदि (c_parser_next_token_is (parser, CPP_KEYWORD)
      && c_parser_peek_token (parser)->keyword == RID_AT_CATCH)
    c_parser_error (parser, "%<catch%> is not supported");
  अन्यथा
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
  वृक्ष t_label = NULL_वृक्ष, f_label = NULL_वृक्ष, label;
  location_t loc;
  c_parser_consume_token (parser);
  वृक्ष cond = c_parser_gimple_paren_condition (parser);

  यदि (c_parser_next_token_is_keyword (parser, RID_GOTO))
    {
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      यदि (! c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected label");
	  प्रत्यागम;
	}
      label = c_parser_peek_token (parser)->मूल्य;
      c_parser_consume_token (parser);
      पूर्णाङ्क dest_index;
      profile_probability prob;
      यदि ((cfun->curr_properties & PROP_cfg)
	  && c_parser_gimple_parse_bb_spec_edge_probability (label, parser,
							     &dest_index, &prob))
	parser.ढकला_edge (parser.current_bb->index, dest_index,
			  EDGE_TRUE_मूल्य, prob);
      अन्यथा
	t_label = lookup_label_for_goto (loc, label);
      यदि (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	प्रत्यागम;
    }
  अन्यथा
    {
      c_parser_error (parser, "expected goto expression");
      प्रत्यागम;
    }

  यदि (c_parser_next_token_is_keyword (parser, RID_ELSE))
    c_parser_consume_token (parser);
  अन्यथा
    {
      c_parser_error (parser, "expected else statement");
      प्रत्यागम;
    }

  यदि (c_parser_next_token_is_keyword (parser, RID_GOTO))
    {
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      यदि (! c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected label");
	  प्रत्यागम;
	}
      label = c_parser_peek_token (parser)->मूल्य;
      c_parser_consume_token (parser);
      पूर्णाङ्क dest_index;
      profile_probability prob;
      यदि ((cfun->curr_properties & PROP_cfg)
	  && c_parser_gimple_parse_bb_spec_edge_probability (label, parser,
							     &dest_index, &prob))
	parser.ढकला_edge (parser.current_bb->index, dest_index,
			  EDGE_FALSE_मूल्य, prob);
      अन्यथा
	f_label = lookup_label_for_goto (loc, label);
      यदि (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	प्रत्यागम;
    }
  अन्यथा
    {
      c_parser_error (parser, "expected goto expression");
      प्रत्यागम;
    }

  यदि (cond != error_mark_गाठ)
    gimple_seq_add_stmt_without_update (seq, gimple_build_cond_from_वृक्ष (cond, t_label,
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
  c_अभिव्यक्ती cond_अभिव्यक्ती;
  वृक्ष case_label, label;
  auto_vec<वृक्ष> labels;
  वृक्ष default_label = NULL_वृक्ष;
  c_parser_consume_token (parser);

  यदि (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    प्रत्यागम;
  cond_अभिव्यक्ती = c_parser_gimple_postfix_expression (parser);
  यदि (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    प्रत्यागम;

  यदि (! c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    प्रत्यागम;

  यावत् (c_parser_next_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      यदि (c_parser_next_token_is (parser, CPP_EOF))
	{
	  c_parser_error (parser, "expected statement");
	  प्रत्यागम;
	}

      विकल्प (c_parser_peek_token (parser)->keyword)
	{
	पक्ष RID_CASE:
	  {
	    c_अभिव्यक्ती exp1;
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);

	    यदि (c_parser_next_token_is (parser, CPP_NAME)
		|| c_parser_peek_token (parser)->type == CPP_संख्या)
	      exp1 = c_parser_gimple_postfix_expression (parser);
	    अन्यथा
	      {
		c_parser_error (parser, "expected expression");
		प्रत्यागम;
	      }

	    यदि (c_parser_next_token_is (parser, CPP_COLON))
	      {
		c_parser_consume_token (parser);
		यदि (c_parser_next_token_is (parser, CPP_NAME))
		  {
		    label = c_parser_peek_token (parser)->मूल्य;
		    c_parser_consume_token (parser);
		    वृक्ष decl = lookup_label_for_goto (loc, label);
		    case_label = build_case_label (exp1.मूल्य, NULL_वृक्ष,
						   decl);
		    labels.safe_ढकला (case_label);
		    यदि (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      प्रत्यागम;
		  }
		अन्यथा यदि (! c_parser_require (parser, CPP_NAME,
					     "expected label"))
		  प्रत्यागम;
	      }
	    अन्यथा यदि (! c_parser_require (parser, CPP_SEMICOLON,
					 "expected %<:%>"))
	      प्रत्यागम;
	    भङ्ग;
	  }
	पक्ष RID_DEFAULT:
	  {
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);
	    यदि (c_parser_next_token_is (parser, CPP_COLON))
	      {
		c_parser_consume_token (parser);
		यदि (c_parser_next_token_is (parser, CPP_NAME))
		  {
		    label = c_parser_peek_token (parser)->मूल्य;
		    c_parser_consume_token (parser);
		    वृक्ष decl = lookup_label_for_goto (loc, label);
		    default_label = build_case_label (NULL_वृक्ष, NULL_वृक्ष,
						      decl);
		    यदि (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      प्रत्यागम;
		  }
		अन्यथा यदि (! c_parser_require (parser, CPP_NAME,
					     "expected label"))
		  प्रत्यागम;
	      }
	    अन्यथा यदि (! c_parser_require (parser, CPP_SEMICOLON,
					 "expected %<:%>"))
	      प्रत्यागम;
	    भङ्ग;
	  }
	स्वभाव:
	  c_parser_error (parser, "expected case label");
	  प्रत्यागम;
	}

    }
  यदि (! c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>"))
    प्रत्यागम;

  यदि (cond_अभिव्यक्ती.मूल्य != error_mark_गाठ)
    {
      gswitch *s = gimple_build_switch (cond_अभिव्यक्ती.मूल्य, default_label, labels);
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
  यदि (c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      c_finish_gimple_return (loc, NULL_वृक्ष);
      ret = gimple_build_return (रिक्त);
      gimple_seq_add_stmt_without_update (seq, ret);
    }
  अन्यथा
    {
      location_t xloc = c_parser_peek_token (parser)->location;
      c_अभिव्यक्ती अभिव्यक्ती = c_parser_gimple_unary_expression (parser);
      यदि (अभिव्यक्ती.मूल्य != error_mark_गाठ)
	{
	  c_finish_gimple_return (xloc, अभिव्यक्ती.मूल्य);
	  ret = gimple_build_return (अभिव्यक्ती.मूल्य);
	  gimple_seq_add_stmt_without_update (seq, ret);
	}
    }
}

/* Support function for c_parser_gimple_return_stmt.  */

स्थिर शून्य
c_finish_gimple_return (location_t loc, वृक्ष retval)
{
  वृक्ष valtype = वृक्ष_TYPE (वृक्ष_TYPE (current_function_decl));

  /* Use the expansion point to handle cases such as returning NULL
     in a function returning void.  */
  location_t xloc = expansion_point_location_if_in_system_header (loc);

  यदि (वृक्ष_THIS_VOLATILE (current_function_decl))
    warning_at (xloc, 0,
		"function declared %<noreturn%> has a %<return%> statement");

  यदि (! retval)
    current_function_returns_null = 1;
  अन्यथा यदि (valtype == 0 || VOID_TYPE_P (valtype))
    {
      current_function_returns_null = 1;
      यदि (वृक्ष_CODE (वृक्ष_TYPE (retval)) != VOID_TYPE)
	{
	  error_at
	    (xloc, "%<return%> with a value, in function returning void");
	  inform (DECL_SOURCE_LOCATION (current_function_decl),
		  "declared here");
	}
    }
  अन्यथा यदि (वृक्ष_CODE (valtype) != वृक्ष_CODE (वृक्ष_TYPE (retval)))
    {
      error_at
	(xloc, "invalid conversion in return statement");
      inform (DECL_SOURCE_LOCATION (current_function_decl),
	      "declared here");
    }
  प्रत्यागम;
}
