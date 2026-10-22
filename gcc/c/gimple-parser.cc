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
  चालक c_parser *() { फर्काऊ parser; }
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

  शून्य थप_edge (पूर्णाङ्क, पूर्णाङ्क, पूर्णाङ्क, profile_probability);
};

शून्य
gimple_parser::थप_edge (पूर्णाङ्क src, पूर्णाङ्क dest, पूर्णाङ्क flags,
			  profile_probability prob)
{
  gimple_parser_edge e;
  e.src = src;
  e.dest = dest;
  e.flags = flags;
  e.probability = prob;
  edges.safe_थप (e);
}


/* Gimple parsing functions.  */
स्थिर तार्किक c_parser_gimple_compound_statement (gimple_parser &, gimple_seq *);
स्थिर शून्य c_parser_gimple_label (gimple_parser &, gimple_seq *);
स्थिर शून्य c_parser_gimple_statement (gimple_parser &, gimple_seq *);
स्थिर संरचना c_अभिव्यक्ति c_parser_gimple_द्विआधारी_expression (gimple_parser &, रूख);
स्थिर संरचना c_अभिव्यक्ति c_parser_gimple_unary_expression (gimple_parser &);
स्थिर संरचना c_अभिव्यक्ति c_parser_gimple_postfix_expression
			(gimple_parser &, रूख = error_mark_गाँठो);
स्थिर संरचना c_अभिव्यक्ति c_parser_gimple_postfix_expression_after_primary
			(gimple_parser &, location_t, संरचना c_अभिव्यक्ति);
स्थिर शून्य c_parser_gimple_declaration (gimple_parser &);
स्थिर शून्य c_parser_gimple_goto_stmt (gimple_parser &, location_t,
				       रूख, gimple_seq *);
स्थिर शून्य c_parser_gimple_try_stmt (gimple_parser &, gimple_seq *);
स्थिर शून्य c_parser_gimple_if_stmt (gimple_parser &, gimple_seq *);
स्थिर शून्य c_parser_gimple_switch_stmt (gimple_parser &, gimple_seq *);
स्थिर शून्य c_parser_gimple_return_stmt (gimple_parser &, gimple_seq *);
स्थिर शून्य c_finish_gimple_return (location_t, रूख);
स्थिर रूख c_parser_gimple_paren_condition (gimple_parser &);
स्थिर शून्य c_parser_gimple_अभिव्यक्ति_list (gimple_parser &, vec<रूख> *);


/* Much like parser_build_unary_op, but avoid applying default conversions.  */

स्थिर c_अभिव्यक्ति
gimple_parser_build_unary_op (location_t loc,
			      गणना रूख_code code, संरचना c_अभिव्यक्ति arg)
{
  संरचना c_अभिव्यक्ति result;

  result.original_code = code;
  result.original_type = रिक्त;
  result.m_decimal = 0;

  यदि (reject_gcc_builtin (arg.मान))
    {
      result.मान = error_mark_गाँठो;
    }
  अन्यथा
    {
      result.मान = build_unary_op (loc, code, arg.मान, सत्य);

      यदि (रूख_OVERFLOW_P (result.मान) && !रूख_OVERFLOW_P (arg.मान))
	overflow_warning (loc, result.मान, arg.मान);
    }

  /* We are typically called when parsing a prefix token at LOC acting on
     ARG.  Reflect this by updating the source range of the result to
     start at LOC and end at the end of ARG.  */
  set_c_अभिव्यक्ति_source_range (&result,
			   loc, arg.get_finish ());

  फर्काऊ result;
}

/* See if VAL is an identifier matching __BB<num> and return <num>
   in *INDEX.  */

स्थिर तार्किक
c_parser_gimple_parse_bb_spec (रूख val, पूर्णाङ्क *index)
{
  यदि (!startswith (IDENTIFIER_POINTER (val), "__BB"))
    फर्काऊ असत्य;

  अचर वर्ण *bb = IDENTIFIER_POINTER (val) + 4;
  यदि (! ISDIGIT (*bb))
    फर्काऊ असत्य;

  वर्ण *pend;
  त्रुटि_सं = 0;
  अचर अचिन्हित दीर्घ सङ्ख्या = म_से_अदीर्घ (bb, &pend, 10);
  यदि (त्रुटि_सं == दुस्फल
      || *pend != '\0'
      || सङ्ख्या > पूर्णांक_उच्च)
    फर्काऊ असत्य;

  *index = सङ्ख्या;
  फर्काऊ सत्य;
}

/* See if VAL is an identifier matching __BB<num> and return <num>
   in *INDEX.  Return true if so and parse also FREQUENCY of
   the edge.  */


स्थिर तार्किक
c_parser_gimple_parse_bb_spec_edge_probability (रूख val,
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
	  रूख f;
	  c_parser_consume_token (parser);
	  यदि (!c_parser_next_token_is (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected frequency quality");
	      फर्काऊ असत्य;
	    }

	  profile_quality quality;
	  अचर वर्ण *v
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान);
	  यदि (!parse_profile_quality (v, &quality))
	    {
	      c_parser_error (parser, "unknown profile quality");
	      फर्काऊ असत्य;
	    }

	  c_parser_consume_token (parser);
	  यदि (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    फर्काऊ असत्य;

	  यदि (!c_parser_next_token_is (parser, CPP_सङ्ख्या)
	      || (रूख_CODE (f = c_parser_peek_token (parser)->मान)
		  != INTEGER_CST))
	    {
	      c_parser_error (parser, "expected frequency value");
	      फर्काऊ असत्य;
	    }

	  अचिन्हित पूर्णाङ्क मान = रूख_INT_CST_तल्लो (f);
	  *probability = profile_probability (मान, quality);

	  c_parser_consume_token (parser);
	  यदि (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    फर्काऊ असत्य;

	  यदि (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    फर्काऊ असत्य;
	}

      फर्काऊ सत्य;
    }

  फर्काऊ असत्य;

}

/* Parse the body of a function declaration marked with "__GIMPLE".  */

शून्य
c_parser_parse_gimple_body (c_parser *cparser, वर्ण *gimple_pass,
			    गणना c_declspec_il cdil,
			    profile_गन्ती entry_bb_गन्ती)
{
  gimple_parser parser (cparser);
  gimple_seq seq = रिक्त;
  gimple_seq body = रिक्त;
  रूख stmt = थप_stmt_list ();
  थप_scope ();
  location_t loc1 = c_parser_peek_token (parser)->location;

  cfun->pass_startwith = gimple_pass;
  init_रूख_ssa (cfun);

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
      init_empty_रूख_cfg ();
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

  रूख block = झिक_scope ();
  stmt = झिक_stmt_list (stmt);
  stmt = c_build_bind_अभिव्यक्ति (loc1, block, stmt);

  block = DECL_INITIAL (current_function_decl);
  BLOCK_SUBBLOCKS (block) = NULL_रूख;
  BLOCK_CHAIN (block) = NULL_रूख;
  रूख_ASM_WRITTEN (block) = 1;

  यदि (cdil == cdil_gimple)
    {
      gbind *bind_stmt = gimple_build_bind (BIND_अभिव्यक्ति_VARS (stmt), रिक्त,
					    BIND_अभिव्यक्ति_BLOCK (stmt));
      gimple_bind_set_body (bind_stmt, seq);
      gimple_seq_add_stmt_without_update (&body, bind_stmt);
      gimple_set_body (current_function_decl, body);
    }
  अन्यथा
    {
      /* Control-flow and binds are lowered, record local decls.  */
      लागि (रूख var = BIND_अभिव्यक्ति_VARS (stmt); var; var = DECL_CHAIN (var))
	यदि (VAR_P (var)
	    && !DECL_EXTERNAL (var))
	  {
	    add_local_decl (cfun, var);
	    /* When the middle-end re-gimplifies any expression we might
	       run into the assertion that we've seen the decl in a BIND.  */
	    यदि (!रूख_STATIC (var))
	      DECL_SEEN_IN_BIND_अभिव्यक्ति_P (var) = 1;
	  }
      /* We have a CFG.  Build the edges.  */
      लागि (अचिन्हित i = 0; i < parser.edges.length (); ++i)
	{
	  edge e = make_edge (BASIC_BLOCK_FOR_FN (cfun, parser.edges[i].src),
			      BASIC_BLOCK_FOR_FN (cfun, parser.edges[i].dest),
			      parser.edges[i].flags);
	  e->probability = parser.edges[i].probability;
	}
      /* Add edges for case labels.  */
      basic_block bb;
      FOR_EACH_BB_FN (bb, cfun)
	यदि (EDGE_गन्ती (bb->succs) == 0)
	  {
	    यदि (gswitch *sw = safe_dyn_cast <gswitch *> (*gsi_last_bb (bb)))
	      लागि (अचिन्हित i = 0; i < gimple_switch_अङ्क_labels (sw); ++i)
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
	      लागि (gsi = gsi_start_bb (bb); !gsi_end_p (gsi);)
		{
		  gimple *stmt = gsi_stmt (gsi);
		  यदि (!gimple_call_internal_p (stmt, IFN_PHI))
		    रोक;

		  gphi *phi = create_phi_गाँठो (gimple_call_lhs (stmt), bb);
		  लागि (अचिन्हित i = 0; i < gimple_call_अङ्क_args (stmt); i += 2)
		    {
		      पूर्णाङ्क srcidx = रूख_INT_CST_तल्लो (gimple_call_arg (stmt, i));
		      edge e = find_edge (BASIC_BLOCK_FOR_FN (cfun, srcidx), bb);
		      यदि (!e)
			c_parser_error (parser, "edge not found");
		      अन्यथा
			add_phi_arg (phi, gimple_call_arg (stmt, i + 1), e,
				     UNKNOWN_LOCATION);
		    }
		  gsi_remove (&gsi, सत्य);
		}
	      लागि (; !gsi_end_p (gsi); gsi_next (&gsi))
		update_stmt (gsi_stmt (gsi));
	    }
	  /* Fill SSA name gaps, putting them on the freelist and diagnose
	     SSA names without definition.  */
	  लागि (अचिन्हित i = 1; i < अङ्क_ssa_names; ++i)
	    यदि (!ssa_name (i))
	      {
		रूख name = make_ssa_name_fn (cfun, integer_type_गाँठो, रिक्त, i);
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
      ENTRY_BLOCK_PTR_FOR_FN (cfun)->गन्ती = entry_bb_गन्ती;
      gcov_type t = param_gimple_fe_computed_hot_bb_threshold;
      set_hot_bb_threshold (t);
      update_max_bb_गन्ती ();
      cgraph_गाँठो::get_create (cfun->decl);
      cgraph_edge::rebuild_edges ();
    }

  /* Perform IL validation and if any error is found abort compilation
     of this function by zapping its body.  */
  यदि ((cfun->curr_properties & PROP_cfg)
      && verify_gimple_in_cfg (cfun, असत्य, असत्य))
    init_empty_रूख_cfg ();
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
    फर्काऊ असत्य;

  /* A compound statement starts with optional declarations.  */
  जबसम्म (c_parser_next_tokens_start_declaration (parser))
    {
      c_parser_gimple_declaration (parser);
      यदि (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	फर्काऊ असत्य;
    }

  जबसम्म (c_parser_next_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      यदि (c_parser_error (parser))
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_BRACE, रिक्त);
	  फर्काऊ return_p;
	}
      अन्यथा यदि (c_parser_next_token_is (parser, CPP_EOF))
	{
	  c_parser_error (parser, "expected declaration or statement");
	  फर्काऊ return_p;
	}

      विकल्प (c_parser_peek_token (parser)->type)
	{
	पक्ष CPP_KEYWORD:
	  विकल्प (c_parser_peek_token (parser)->keyword)
	    {
	    पक्ष RID_AT_TRY:
	      c_parser_gimple_try_stmt (parser, seq);
	      रोक;
	    पक्ष RID_IF:
	      c_parser_gimple_if_stmt (parser, seq);
	      रोक;
	    पक्ष RID_SWITCH:
	      c_parser_gimple_switch_stmt (parser, seq);
	      रोक;
	    पक्ष RID_GOTO:
	      {
		location_t loc = c_parser_peek_token (parser)->location;
		c_parser_consume_token (parser);
		यदि (c_parser_next_token_is (parser, CPP_NAME))
		  {
		    रूख label = c_parser_peek_token (parser)->मान;
		    c_parser_consume_token (parser);
		    c_parser_gimple_goto_stmt (parser, loc, label, seq);
		    यदि (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      फर्काऊ return_p;
		  }
		}
	      रोक;
	    पक्ष RID_RETURN:
	      return_p = सत्य;
	      c_parser_gimple_return_stmt (parser, seq);
	      यदि (! c_parser_require (parser, CPP_SEMICOLON,
				      "expected %<;%>"))
		फर्काऊ return_p;
	      यदि (cfun->curr_properties & PROP_cfg)
		parser.थप_edge (parser.current_bb->index, EXIT_BLOCK, 0,
				  profile_probability::uninitialized ());
	      रोक;
	    स्वभाव:
	      गच्छ अभिव्यक्ति_stmt;
	    }
	  रोक;
	पक्ष CPP_NAME:
	  यदि (c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_gimple_label (parser, seq);
	      रोक;
	    }
	  यदि (c_parser_next_token_is (parser, CPP_NAME)
	      && c_parser_peek_token (parser)->id_kind == C_ID_ID
	      && म_भेद (IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान),
			 "try") == 0)
	    {
	      c_parser_gimple_try_stmt (parser, seq);
	      रोक;
	    }
	  /* Basic block specification.
	     __BB (index, ...)  */
	  यदि ((cfun->curr_properties & PROP_cfg)
	      && !म_भेद (IDENTIFIER_POINTER
			    (c_parser_peek_token (parser)->मान), "__BB"))
	    {
	      c_parser_consume_token (parser);
	      यदि (! c_parser_require (parser, CPP_OPEN_PAREN,
				      "expected %<(%>"))
		फर्काऊ return_p;
	      यदि (c_parser_next_token_is_not (parser, CPP_सङ्ख्या))
		{
		  c_parser_error (parser, "expected block index");
		  फर्काऊ return_p;
		}
	      रूख tnum = c_parser_peek_token (parser)->मान;
	      यदि (रूख_CODE (tnum) != INTEGER_CST)
		{
		  c_parser_error (parser, "expected block index");
		  फर्काऊ return_p;
		}
	      पूर्णाङ्क index = रूख_INT_CST_तल्लो (tnum);
	      यदि (index < अङ्क_FIXED_BLOCKS
		  || (index < last_basic_block_for_fn (cfun)
		      && BASIC_BLOCK_FOR_FN (cfun, index) != रिक्त))
		{
		  c_parser_error (parser, "invalid block index");
		  फर्काऊ return_p;
		}
	      पूर्णाङ्क is_loop_header_of = -1;
	      profile_गन्ती bb_गन्ती = profile_गन्ती::uninitialized ();
	      c_parser_consume_token (parser);
	      जबसम्म (c_parser_next_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  यदि (! c_parser_next_token_is (parser, CPP_NAME))
		    {
		      c_parser_error (parser, "expected block specifier");
		      फर्काऊ return_p;
		    }
		  /* loop_header (NUM)  */
		  यदि (!म_भेद (IDENTIFIER_POINTER
			         (c_parser_peek_token (parser)->मान),
			       "loop_header"))
		    {
		      c_parser_consume_token (parser);
		      यदि (! c_parser_require (parser, CPP_OPEN_PAREN,
					      "expected %<(%>"))
			फर्काऊ return_p;
		      रूख loop_अङ्क;
		      यदि (! c_parser_next_token_is (parser, CPP_सङ्ख्या)
			  || रूख_CODE (loop_अङ्क
					  = c_parser_peek_token (parser)->मान)
			       != INTEGER_CST)
			{
			  c_parser_error (parser, "expected loop number");
			  फर्काऊ return_p;
			}
		      c_parser_consume_token (parser);
		      is_loop_header_of = रूख_INT_CST_तल्लो (loop_अङ्क);
		      यदि (! c_parser_require (parser, CPP_CLOSE_PAREN,
					      "expected %<)%>"))
			फर्काऊ return_p;
		    }
		  /* Parse profile: quality(value) */
		  अन्यथा
		    {
		      रूख q;
		      profile_quality quality;
		      रूख v = c_parser_peek_token (parser)->मान;
		      यदि (!parse_profile_quality (IDENTIFIER_POINTER (v),
						  &quality))
			{
			  c_parser_error (parser, "unknown block specifier");
			  फर्काऊ असत्य;
			}

		      c_parser_consume_token (parser);
		      यदि (!c_parser_require (parser, CPP_OPEN_PAREN,
					     "expected %<(%>"))
			फर्काऊ असत्य;

		      यदि (!c_parser_next_token_is (parser, CPP_सङ्ख्या)
			  || (रूख_CODE (q = c_parser_peek_token (parser)->मान)
			      != INTEGER_CST))
			{
			  c_parser_error (parser, "expected count value");
			  फर्काऊ असत्य;
			}

		      bb_गन्ती
			= profile_गन्ती::from_gcov_type (रूख_INT_CST_तल्लो (q),
							 quality);
		      c_parser_consume_token (parser);
		      यदि (! c_parser_require (parser, CPP_CLOSE_PAREN,
					      "expected %<)%>"))
			फर्काऊ return_p;
		    }
		}
	      यदि (! c_parser_require (parser, CPP_CLOSE_PAREN,
				      "expected %<)%>")
		  || ! c_parser_require (parser, CPP_COLON,
					 "expected %<:%>"))
		फर्काऊ return_p;

	      /* Put stmts parsed in the current block.  */
	      यदि (!gimple_seq_empty_p (*seq))
		{
		  यदि (!parser.current_bb)
		    c_parser_error (parser, "stmts without block");
		  अन्यथा
		    {
		      gimple_stmt_iterator gsi
			= gsi_start_bb (parser.current_bb);
		      gsi_घुसाउ_seq_after_without_update (&gsi, *seq,
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
	      यदि (basic_block_info_for_fn (cfun)->length () <= (माप_प्रकार)index)
		vec_safe_grow_cleared (basic_block_info_for_fn (cfun),
				       index + 1, सत्य);
	      SET_BASIC_BLOCK_FOR_FN (cfun, index, bb);
	      यदि (last_basic_block_for_fn (cfun) <= index)
		last_basic_block_for_fn (cfun) = index + 1;
	      n_basic_blocks_for_fn (cfun)++;
	      यदि (parser.current_bb->index == ENTRY_BLOCK)
		parser.थप_edge (ENTRY_BLOCK, bb->index, EDGE_FALLTHRU,
				  profile_probability::always ());

	      /* We leave the proper setting to fixup.  */
	      वर्ग loop *loop_father = loops_for_fn (cfun)->रूख_जरा;
	      /* If the new block is a loop header, allocate a loop
		 struct.  Fixup will take care of proper placement within
		 the loop tree.  */
	      यदि (is_loop_header_of != -1)
		{
		  यदि (सङ्ख्या_of_loops (cfun) > (अचिन्हित)is_loop_header_of
		      && get_loop (cfun, is_loop_header_of) != रिक्त)
		    {
		      c_parser_error (parser, "duplicate loop header");
		    }
		  अन्यथा
		    {
		      वर्ग loop *loop = alloc_loop ();
		      loop->अङ्क = is_loop_header_of;
		      loop->header = bb;
		      यदि (सङ्ख्या_of_loops (cfun) <= (अचिन्हित)is_loop_header_of)
			vec_safe_grow_cleared (loops_for_fn (cfun)->larray,
					       is_loop_header_of + 1, सत्य);
		      (*loops_for_fn (cfun)->larray)[is_loop_header_of] = loop;
		      flow_loop_रूख_गाँठो_add (loops_for_fn (cfun)->रूख_जरा,
					       loop);
		    }
		  loop_father = get_loop (cfun, is_loop_header_of);
		}
	      bb->loop_father = loop_father;
	      bb->गन्ती = bb_गन्ती;

	      /* Stmts now go to the new block.  */
	      parser.current_bb = bb;
	      रोक;
	    }
	  गच्छ अभिव्यक्ति_stmt;

	पक्ष CPP_SEMICOLON:
	  {
	    /* Empty stmt.  */
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);
	    gimple *nop = gimple_build_nop ();
	    gimple_set_location (nop, loc);
	    gimple_seq_add_stmt_without_update (seq, nop);
	    रोक;
	  }

	पक्ष CPP_CLOSE_PAREN:
	पक्ष CPP_CLOSE_SQUARE:
	  /* Avoid infinite loop in error recovery:
	     c_parser_skip_until_found stops at a closing nesting
	     delimiter without consuming it, but here we need to consume
	     it to proceed further.  */
	  c_parser_error (parser, "expected statement");
	  c_parser_consume_token (parser);
	रोक;

	स्वभाव:
अभिव्यक्ति_stmt:
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
	  gsi_घुसाउ_seq_after_without_update (&gsi, *seq,
					       GSI_CONTINUE_LINKING);
	}
      *seq = रिक्त;
    }

  फर्काऊ return_p;
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
  संरचना c_अभिव्यक्ति lhs, rhs;
  gimple *assign = रिक्त;
  location_t loc;
  रूख arg = NULL_रूख;
  auto_vec<रूख> vargs;

  lhs = c_parser_gimple_unary_expression (parser);
  loc = अभिव्यक्ति_LOCATION (lhs.मान);
  rhs.set_error ();

  /* GIMPLE call statement without LHS.  */
  यदि (c_parser_next_token_is (parser, CPP_SEMICOLON)
      && रूख_CODE (lhs.मान) == CALL_अभिव्यक्ति)
    {
      gimple *call;
      call = gimple_build_call_from_रूख (lhs.मान, रिक्त);
      gimple_seq_add_stmt_without_update (seq, call);
      gimple_set_location (call, loc);
      फर्काऊ;
    }

  /* All following cases are statements with LHS.  */
  यदि (! c_parser_require (parser, CPP_EQ, "expected %<=%>"))
    फर्काऊ;

  /* Eat and ignore {v} right after the =, the has_volatile_ops is
     redundant and re-computed by the operand scanner.  */
  यदि (c_parser_next_token_is (parser, CPP_OPEN_BRACE)
      && !(c_parser_peek_token (parser)->flags & PREV_WHITE)
      && c_parser_peek_2nd_token (parser)->type == CPP_NAME
      && !(c_parser_peek_2nd_token (parser)->flags & PREV_WHITE)
      && म_भेद ("v", IDENTIFIER_POINTER
			(c_parser_peek_2nd_token (parser)->मान)) == 0
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
	फर्काऊ;
      /* ???  The actual type used in the cast expression is ignored as
         in GIMPLE it is encoded by the type of the LHS.  */
      rhs = c_parser_gimple_postfix_expression (parser);
      यदि (lhs.मान != error_mark_गाँठो
	  && rhs.मान != error_mark_गाँठो)
	{
	  गणना रूख_code code = NOP_अभिव्यक्ति;
	  यदि (FLOAT_TYPE_P (रूख_TYPE (lhs.मान))
	      && ! FLOAT_TYPE_P (रूख_TYPE (rhs.मान)))
	    code = FLOAT_अभिव्यक्ति;
	  अन्यथा यदि (! FLOAT_TYPE_P (रूख_TYPE (lhs.मान))
		   && FLOAT_TYPE_P (रूख_TYPE (rhs.मान)))
	    code = FIX_TRUNC_अभिव्यक्ति;
	  assign = gimple_build_assign (lhs.मान, code, rhs.मान);
	  gimple_seq_add_stmt_without_update (seq, assign);
	  gimple_set_location (assign, loc);
	  फर्काऊ;
	}
    }

  /* Unary expression.  */
  विकल्प (c_parser_peek_token (parser)->type)
    {
    पक्ष CPP_NAME:
      {
	रूख id = c_parser_peek_token (parser)->मान;
	यदि (म_भेद (IDENTIFIER_POINTER (id), "__ABS") == 0
	    || म_भेद (IDENTIFIER_POINTER (id), "__ABSU") == 0
	    || म_भेद (IDENTIFIER_POINTER (id), "__MIN") == 0
	    || म_भेद (IDENTIFIER_POINTER (id), "__MAX") == 0
	    || म_भेद (IDENTIFIER_POINTER (id), "__BIT_INSERT") == 0
	    || म_भेद (IDENTIFIER_POINTER (id), "__VEC_PERM") == 0)
	  गच्छ build_unary_अभिव्यक्ति;
	रोक;
      }
    पक्ष CPP_KEYWORD:
      यदि (c_parser_peek_token (parser)->keyword != RID_REALPART
	  && c_parser_peek_token (parser)->keyword != RID_IMAGPART)
	रोक;
      /* Fallthru.  */
    पक्ष CPP_AND:
    पक्ष CPP_PLUS:
    पक्ष CPP_MINUS:
    पक्ष CPP_COMPL:
    पक्ष CPP_NOT:
    पक्ष CPP_MULT: /* pointer deref */
    build_unary_अभिव्यक्ति:
      rhs = c_parser_gimple_unary_expression (parser);
      यदि (rhs.मान != error_mark_गाँठो)
	{
	  assign = gimple_build_assign (lhs.मान, rhs.मान);
	  gimple_set_location (assign, loc);
	  gimple_seq_add_stmt_without_update (seq, assign);
	}
      फर्काऊ;

    स्वभाव:;
    }

  /* GIMPLE PHI statement.  */
  यदि (c_parser_next_token_is_keyword (parser, RID_PHI))
    {
      c_parser_consume_token (parser);

      यदि (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	फर्काऊ;

      यदि (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	c_parser_consume_token (parser);

      जबसम्म (c_parser_next_token_is_not (parser, CPP_CLOSE_PAREN))
	{
	  यदि (c_parser_next_token_is (parser, CPP_NAME)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      arg = c_parser_peek_token (parser)->मान;
	      c_parser_consume_token (parser);
	      यदि (c_parser_next_token_is (parser, CPP_COLON))
		c_parser_consume_token (parser);
	      पूर्णाङ्क src_index = -1;
	      यदि (!c_parser_gimple_parse_bb_spec (arg, &src_index))
		c_parser_error (parser, "invalid source block specification");
	      vargs.safe_थप (size_int (src_index));
	    }
	  अन्यथा यदि (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  अन्यथा
	    {
	      arg = c_parser_gimple_unary_expression (parser).मान;
	      vargs.safe_थप (arg);
	    }
	}

      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");

      /* Build internal function for PHI.  */
      gcall *call_stmt = gimple_build_call_internal_vec (IFN_PHI, vargs);
      gimple_call_set_lhs (call_stmt, lhs.मान);
      gimple_set_location (call_stmt, UNKNOWN_LOCATION);
      gimple_seq_add_stmt_without_update (seq, call_stmt);
      फर्काऊ;
    }

  /* GIMPLE call with lhs.  */
  यदि (c_parser_next_token_is (parser, CPP_DOT)
      || (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN
	  && lookup_name (c_parser_peek_token (parser)->मान)))
    {
      rhs = c_parser_gimple_unary_expression (parser);
      यदि (rhs.मान != error_mark_गाँठो)
	{
	  gimple *call = gimple_build_call_from_रूख (rhs.मान, रिक्त);
	  gimple_call_set_lhs (call, lhs.मान);
	  gimple_seq_add_stmt_without_update (seq, call);
	  gimple_set_location (call, loc);
	}
      फर्काऊ;
    }

  rhs = c_parser_gimple_द्विआधारी_expression (parser, रूख_TYPE (lhs.मान));
  यदि (lhs.मान != error_mark_गाँठो
      && rhs.मान != error_mark_गाँठो)
    {
      /* If we parsed an identifier and the next token  is a '?' then parse
	 a conditional expression.  */
      यदि (SSA_VAR_P (rhs.मान) && c_parser_next_token_is (parser, CPP_QUERY))
	{
	  संरचना c_अभिव्यक्ति trueval, falseval;
	  c_parser_consume_token (parser);
	  trueval = c_parser_gimple_postfix_expression (parser);
	  falseval.set_error ();
	  यदि (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    falseval = c_parser_gimple_postfix_expression (parser);
	  यदि (trueval.मान == error_mark_गाँठो
	      || falseval.मान == error_mark_गाँठो)
	    फर्काऊ;
	  rhs.मान = build3_loc (loc,
				  VECTOR_TYPE_P (रूख_TYPE (rhs.मान))
				  ? VEC_COND_अभिव्यक्ति : COND_अभिव्यक्ति,
				  रूख_TYPE (trueval.मान),
				  rhs.मान, trueval.मान, falseval.मान);
	}
      यदि (get_gimple_rhs_class (रूख_CODE (rhs.मान)) == GIMPLE_INVALID_RHS)
	{
	  c_parser_error (parser, "unexpected RHS for assignment");
	  फर्काऊ;
	}
      assign = gimple_build_assign (lhs.मान, rhs.मान);
      gimple_seq_add_stmt_without_update (seq, assign);
      gimple_set_location (assign, loc);
    }
  फर्काऊ;
}

/* A mapping between an identifier to a tree code for binary operations. */
स्थिर अचर std::pair<अचर वर्ण *, रूख_code> gimple_द्विआधारी_identifier_code[] =
  {
    {"__MULT_HIGHPART", MULT_HIGHPART_अभिव्यक्ति},
    {"__UNLT", UNLT_अभिव्यक्ति},
    {"__UNLE", UNLE_अभिव्यक्ति},
    {"__UNGT", UNGT_अभिव्यक्ति},
    {"__UNGE", UNGE_अभिव्यक्ति},
    {"__UNEQ", UNEQ_अभिव्यक्ति},
    {"__UNORDERED", UNORDERED_अभिव्यक्ति},
    {"__ORDERED", ORDERED_अभिव्यक्ति},
    {"__LTGT", LTGT_अभिव्यक्ति},
    {"__FLOOR_DIV", FLOOR_DIV_अभिव्यक्ति},
    {"__ROUND_DIV", ROUND_DIV_अभिव्यक्ति},
    {"__EXACT_DIV", EXACT_DIV_अभिव्यक्ति},
    {"__CEIL_DIV", CEIL_DIV_अभिव्यक्ति},
    {"__FLOOR_MOD", FLOOR_MOD_अभिव्यक्ति},
    {"__ROUND_MOD", ROUND_MOD_अभिव्यक्ति},
    {"__CEIL_MOD", CEIL_MOD_अभिव्यक्ति},
    {"__ROTATE_LEFT", LROTATE_अभिव्यक्ति},
    {"__ROTATE_RIGHT", RROTATE_अभिव्यक्ति},
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

स्थिर c_अभिव्यक्ति
c_parser_gimple_द्विआधारी_expression (gimple_parser &parser, रूख ret_type)
{
  /* Location of the binary operator.  */
  संरचना c_अभिव्यक्ति ret, lhs, rhs;
  गणना रूख_code code = ERROR_MARK;
  ret.set_error ();
  lhs = c_parser_gimple_postfix_expression (parser, ret_type);
  यदि (c_parser_error (parser))
    फर्काऊ ret;
  विकल्प (c_parser_peek_token (parser)->type)
    {
    पक्ष CPP_MULT:
      code = MULT_अभिव्यक्ति;
      रोक;
    पक्ष CPP_DIV:
      code = TRUNC_DIV_अभिव्यक्ति;
      रोक;
    पक्ष CPP_MOD:
      code = TRUNC_MOD_अभिव्यक्ति;
      रोक;
    पक्ष CPP_PLUS:
      यदि (POINTER_TYPE_P (रूख_TYPE (lhs.मान)))
	code = POINTER_PLUS_अभिव्यक्ति;
      अन्यथा
	code = PLUS_अभिव्यक्ति;
      रोक;
    पक्ष CPP_MINUS:
      यदि (POINTER_TYPE_P (रूख_TYPE (lhs.मान)))
	code = POINTER_DIFF_अभिव्यक्ति;
      अन्यथा
	code = MINUS_अभिव्यक्ति;
      रोक;
    पक्ष CPP_LSHIFT:
      code = LSHIFT_अभिव्यक्ति;
      रोक;
    पक्ष CPP_RSHIFT:
      code = RSHIFT_अभिव्यक्ति;
      रोक;
    पक्ष CPP_LESS:
      code = LT_अभिव्यक्ति;
      रोक;
    पक्ष CPP_GREATER:
      code = GT_अभिव्यक्ति;
      रोक;
    पक्ष CPP_LESS_EQ:
      code = LE_अभिव्यक्ति;
      रोक;
    पक्ष CPP_GREATER_EQ:
      code = GE_अभिव्यक्ति;
      रोक;
    पक्ष CPP_EQ_EQ:
      code = EQ_अभिव्यक्ति;
      रोक;
    पक्ष CPP_NOT_EQ:
      code = NE_अभिव्यक्ति;
      रोक;
    पक्ष CPP_AND:
      code = BIT_AND_अभिव्यक्ति;
      रोक;
    पक्ष CPP_XOR:
      code = BIT_XOR_अभिव्यक्ति;
      रोक;
    पक्ष CPP_OR:
      code = BIT_IOR_अभिव्यक्ति;
      रोक;
    पक्ष CPP_AND_AND:
      c_parser_error (parser, "%<&&%> not valid in GIMPLE");
      फर्काऊ ret;
    पक्ष CPP_OR_OR:
      c_parser_error (parser, "%<||%> not valid in GIMPLE");
      फर्काऊ ret;
    पक्ष CPP_NAME:
      {
	रूख id = c_parser_peek_token (parser)->मान;
	लागि (स्वतः &p : gimple_द्विआधारी_identifier_code)
	  {
	    यदि (म_भेद (IDENTIFIER_POINTER (id), p.first) == 0)
	      {
		code = p.second;
		रोक;
	      }
	  }
	यदि (code != ERROR_MARK)
	  रोक;
      }
      /* Fallthru.  */
    स्वभाव:
      /* Not a binary expression.  */
      फर्काऊ lhs;
    }
  location_t ret_loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  rhs = c_parser_gimple_postfix_expression (parser);
  यदि (lhs.मान != error_mark_गाँठो && rhs.मान != error_mark_गाँठो)
    ret.मान = build2_loc (ret_loc, code, ret_type, lhs.मान, rhs.मान);
  फर्काऊ ret;
}

/* Parse a gimple parentized binary expression.  */

स्थिर c_अभिव्यक्ति
c_parser_gimple_parentized_द्विआधारी_expression (gimple_parser &parser,
					      location_t op_loc,
					      रूख_code code)
{
  संरचना c_अभिव्यक्ति ret;
  ret.set_error ();

  c_parser_consume_token (parser);
  यदि (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    फर्काऊ ret;
  c_अभिव्यक्ति op1 = c_parser_gimple_postfix_expression (parser);
  यदि (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    फर्काऊ ret;
  c_अभिव्यक्ति op2 = c_parser_gimple_postfix_expression (parser);
  यदि (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    फर्काऊ ret;

  यदि (op1.मान != error_mark_गाँठो && op2.मान != error_mark_गाँठो)
    ret.मान = build2_loc (op_loc,
			    code, रूख_TYPE (op1.मान), op1.मान, op2.मान);
  फर्काऊ ret;
}

/* Parse a gimple parentized binary expression.  */

स्थिर c_अभिव्यक्ति
c_parser_gimple_parentized_ternary_expression (gimple_parser &parser,
					       location_t op_loc,
					       रूख_code code)
{
  संरचना c_अभिव्यक्ति ret;
  ret.set_error ();

  c_parser_consume_token (parser);
  यदि (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    फर्काऊ ret;
  c_अभिव्यक्ति op1 = c_parser_gimple_postfix_expression (parser);
  यदि (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    फर्काऊ ret;
  c_अभिव्यक्ति op2 = c_parser_gimple_postfix_expression (parser);
  यदि (!c_parser_require (parser, CPP_COMMA, "expected %<)%>"))
    फर्काऊ ret;
  c_अभिव्यक्ति op3 = c_parser_gimple_postfix_expression (parser);
  यदि (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    फर्काऊ ret;

  यदि (op1.मान != error_mark_गाँठो
      && op2.मान != error_mark_गाँठो
      && op3.मान != error_mark_गाँठो)
    ret.मान = build3_loc (op_loc,
			    code, रूख_TYPE (op1.मान),
			    op1.मान, op2.मान, op3.मान);
  फर्काऊ ret;
}

/* Parse gimple unary expression.

   gimple-unary-expression:
     gimple-postfix-expression
     unary-operator gimple-postfix-expression

   unary-operator: one of
     & * + - ~ abs_expr
*/

स्थिर c_अभिव्यक्ति
c_parser_gimple_unary_expression (gimple_parser &parser)
{
  संरचना c_अभिव्यक्ति ret, op;
  location_t op_loc = c_parser_peek_token (parser)->location;
  location_t finish;
  ret.set_error ();
  विकल्प (c_parser_peek_token (parser)->type)
    {
    पक्ष CPP_AND:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      mark_exp_read (op.मान);
      फर्काऊ gimple_parser_build_unary_op (op_loc, ADDR_अभिव्यक्ति, op);
    पक्ष CPP_MULT:
      {
	c_parser_consume_token (parser);
	op = c_parser_gimple_postfix_expression (parser);
	यदि (op.मान == error_mark_गाँठो)
	  फर्काऊ ret;
	यदि (! POINTER_TYPE_P (रूख_TYPE (op.मान)))
	  {
	    error_at (op_loc, "expected pointer as argument of unary %<*%>");
	    फर्काऊ ret;
	  }
	finish = op.get_finish ();
	location_t combined_loc = make_location (op_loc, op_loc, finish);
	ret.मान = build_simple_mem_ref_loc (combined_loc, op.मान);
	रूख_SIDE_EFFECTS (ret.मान)
	  = रूख_THIS_VOLATILE (ret.मान)
	  = TYPE_VOLATILE (रूख_TYPE (रूख_TYPE (op.मान)));
	ret.src_range.m_start = op_loc;
	ret.src_range.m_finish = finish;
	फर्काऊ ret;
      }
    पक्ष CPP_PLUS:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      फर्काऊ gimple_parser_build_unary_op (op_loc, CONVERT_अभिव्यक्ति, op);
    पक्ष CPP_MINUS:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      फर्काऊ gimple_parser_build_unary_op (op_loc, NEGATE_अभिव्यक्ति, op);
    पक्ष CPP_COMPL:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      फर्काऊ gimple_parser_build_unary_op (op_loc, BIT_NOT_अभिव्यक्ति, op);
    पक्ष CPP_NOT:
      c_parser_error (parser, "%<!%> not valid in GIMPLE");
      फर्काऊ ret;
    पक्ष CPP_KEYWORD:
      विकल्प (c_parser_peek_token (parser)->keyword)
	{
	पक्ष RID_REALPART:
	  c_parser_consume_token (parser);
	  op = c_parser_gimple_postfix_expression (parser);
	  फर्काऊ gimple_parser_build_unary_op (op_loc, REALPART_अभिव्यक्ति, op);
	पक्ष RID_IMAGPART:
	  c_parser_consume_token (parser);
	  op = c_parser_gimple_postfix_expression (parser);
	  फर्काऊ gimple_parser_build_unary_op (op_loc, IMAGPART_अभिव्यक्ति, op);
	स्वभाव:
	  फर्काऊ c_parser_gimple_postfix_expression (parser);
	}
    पक्ष CPP_NAME:
	{
	  रूख id = c_parser_peek_token (parser)->मान;
	  यदि (म_भेद (IDENTIFIER_POINTER (id), "__ABS") == 0)
	    {
	      c_parser_consume_token (parser);
	      op = c_parser_gimple_postfix_expression (parser);
	      फर्काऊ gimple_parser_build_unary_op (op_loc, ABS_अभिव्यक्ति, op);
	    }
	  अन्यथा यदि (म_भेद (IDENTIFIER_POINTER (id), "__ABSU") == 0)
	    {
	      c_parser_consume_token (parser);
	      op = c_parser_gimple_postfix_expression (parser);
	      फर्काऊ gimple_parser_build_unary_op (op_loc, ABSU_अभिव्यक्ति, op);
	    }
	  अन्यथा यदि (म_भेद (IDENTIFIER_POINTER (id), "__MIN") == 0)
	    फर्काऊ c_parser_gimple_parentized_द्विआधारी_expression (parser,
								 op_loc,
								 MIN_अभिव्यक्ति);
	  अन्यथा यदि (म_भेद (IDENTIFIER_POINTER (id), "__MAX") == 0)
	    फर्काऊ c_parser_gimple_parentized_द्विआधारी_expression (parser,
								 op_loc,
								 MAX_अभिव्यक्ति);
	  अन्यथा यदि (म_भेद (IDENTIFIER_POINTER (id), "__VEC_PERM") == 0)
	    फर्काऊ c_parser_gimple_parentized_ternary_expression
			(parser, op_loc, VEC_PERM_अभिव्यक्ति);
	  अन्यथा यदि (म_भेद (IDENTIFIER_POINTER (id), "__BIT_INSERT") == 0)
	    {
	      /* __BIT_INSERT '(' postfix-expression, postfix-expression,
			          integer ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      यदि (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_अभिव्यक्ति op0 = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_अभिव्यक्ति op1 = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_अभिव्यक्ति op2 = c_parser_gimple_postfix_expression (parser);
		  यदि (रूख_CODE (op2.मान) != INTEGER_CST
		      || !int_fits_type_p (op2.मान, bitsizetype))
		    c_parser_error (parser, "expected constant offset");
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  यदि (op0.मान != error_mark_गाँठो
		      && op1.मान != error_mark_गाँठो
		      && रूख_CODE (op2.मान) == INTEGER_CST)
		    ret.मान = build3_loc (loc, BIT_घुसाउ_अभिव्यक्ति,
					    रूख_TYPE (op0.मान),
					    op0.मान, op1.मान,
					    fold_convert (bitsizetype,
							  op2.मान));
		}
	      फर्काऊ ret;
	    }
	  अन्यथा
	    फर्काऊ c_parser_gimple_postfix_expression (parser);
	}
    स्वभाव:
      फर्काऊ c_parser_gimple_postfix_expression (parser);
    }
}

/* Decompose ID into base name (ID until ver_offset) and VERSION.  Return
   true if ID matches a SSA name.  */

स्थिर तार्किक
c_parser_parse_ssa_name_id (रूख id, अचिन्हित *version, अचिन्हित *ver_offset)
{
  अचर वर्ण *token = IDENTIFIER_POINTER (id);
  अचर वर्ण *var_version = म_खोजप (token, '_');
  यदि (! var_version)
    फर्काऊ असत्य;

  *ver_offset = var_version - token;
  लागि (अचर वर्ण *p = var_version + 1; *p; ++p)
    यदि (! ISDIGIT (*p))
      फर्काऊ असत्य;
  *version = म_से_प (var_version + 1);
  फर्काऊ *version > 0;
}

/* Get at the actual SSA name ID with VERSION starting at VER_OFFSET.
   TYPE is the type if the SSA name is being declared.  */

स्थिर रूख
c_parser_parse_ssa_name (gimple_parser &parser,
			 रूख id, रूख type, अचिन्हित version,
			 अचिन्हित ver_offset)
{
  रूख name = NULL_रूख;
  अचर वर्ण *token = IDENTIFIER_POINTER (id);

  यदि (ver_offset == 0)
    {
      /* Anonymous unnamed SSA name.  */
      यदि (version < अङ्क_ssa_names)
	name = ssa_name (version);
      यदि (! name)
	{
	  यदि (! type)
	    {
	      c_parser_error (parser, "SSA name undeclared");
	      फर्काऊ error_mark_गाँठो;
	    }
	  name = make_ssa_name_fn (cfun, type, रिक्त, version);
	}
    }
  अन्यथा
    {
      यदि (version < अङ्क_ssa_names)
	name = ssa_name (version);
      यदि (! name)
	{
	  /* Separate var name from version.  */
	  वर्ण *var_name = XNEWVEC (वर्ण, ver_offset + 1);
	  स_नकल (var_name, token, ver_offset);
	  var_name[ver_offset] = '\0';
	  /* lookup for parent decl.  */
	  id = get_identifier (var_name);
	  रूख parent = lookup_name (id);
	  XDELETEVEC (var_name);
	  यदि (! parent || parent == error_mark_गाँठो)
	    {
	      c_parser_error (parser, "base variable or SSA name undeclared");
	      फर्काऊ error_mark_गाँठो;
	    }
	  यदि (!(VAR_P (parent)
		|| रूख_CODE (parent) == PARM_DECL
		|| रूख_CODE (parent) == RESULT_DECL))
	    {
	      error ("invalid base %qE for SSA name", parent);
	      फर्काऊ error_mark_गाँठो;
	    }
	  name = make_ssa_name_fn (cfun, parent,
				   gimple_build_nop (), version);
	}
    }

  फर्काऊ name;
}

/* Parse a gimple call to an internal function.

   gimple-call-internal:
     . identifier ( gimple-argument-expression-list[opt] )  */

स्थिर संरचना c_अभिव्यक्ति
c_parser_gimple_call_internal (gimple_parser &parser)
{
  संरचना c_अभिव्यक्ति अभिव्यक्ति;
  अभिव्यक्ति.set_error ();

  gcc_assert (c_parser_next_token_is (parser, CPP_DOT));
  c_parser_consume_token (parser);
  location_t loc = c_parser_peek_token (parser)->location;
  यदि (!c_parser_next_token_is (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_kind != C_ID_ID)
    {
      c_parser_error (parser, "expecting internal function name");
      फर्काऊ अभिव्यक्ति;
    }
  रूख id = c_parser_peek_token (parser)->मान;
  internal_fn ifn = lookup_internal_fn (IDENTIFIER_POINTER (id));
  c_parser_consume_token (parser);
  यदि (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    {
      auto_vec<रूख> exprlist;
      यदि (!c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_gimple_अभिव्यक्ति_list (parser, &exprlist);
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      यदि (ifn == IFN_LAST)
	error_at (loc, "unknown internal function %qE", id);
      अन्यथा
	{
	  अभिव्यक्ति.मान = build_call_अभिव्यक्ति_internal_loc_array
	    (loc, ifn, void_type_गाँठो, exprlist.length (),
	     exprlist.address ());
	  अभिव्यक्ति.original_code = ERROR_MARK;
	  अभिव्यक्ति.original_type = रिक्त;
	  अभिव्यक्ति.m_decimal = 0;
	}
    }
  फर्काऊ अभिव्यक्ति;
}

/* Parse '<' type [',' alignment] '>' and return a type on success
   and NULL_TREE on error.  */

स्थिर रूख
c_parser_gimple_typespec (gimple_parser &parser)
{
  संरचना c_type_name *type_name = रिक्त;
  रूख alignment = NULL_रूख;
  यदि (c_parser_require (parser, CPP_LESS, "expected %<<%>"))
    {
      type_name = c_parser_type_name (parser);
      /* Optional alignment.  */
      यदि (c_parser_next_token_is (parser, CPP_COMMA))
	{
	  c_parser_consume_token (parser);
	  alignment
	      = c_parser_gimple_postfix_expression (parser).मान;
	}
      c_parser_skip_until_found (parser,
				 CPP_GREATER, "expected %<>%>");
    }
  यदि (!type_name)
    फर्काऊ NULL_रूख;
  रूख tem;
  रूख type = groktypename (type_name, &tem, रिक्त);
  यदि (alignment)
    type = build_aligned_type (type, रूख_to_uhwi (alignment));
  फर्काऊ type;
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

स्थिर संरचना c_अभिव्यक्ति
c_parser_gimple_postfix_expression (gimple_parser &parser, रूख ret_type)
{
  location_t loc = c_parser_peek_token (parser)->location;
  source_range tok_range = c_parser_peek_token (parser)->get_range ();
  संरचना c_अभिव्यक्ति अभिव्यक्ति;
  अभिव्यक्ति.set_error ();
  विकल्प (c_parser_peek_token (parser)->type)
    {
    पक्ष CPP_सङ्ख्या:
      अभिव्यक्ति.मान = c_parser_peek_token (parser)->मान;
      set_c_अभिव्यक्ति_source_range (&अभिव्यक्ति, tok_range);
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      रोक;
    पक्ष CPP_CHAR:
    पक्ष CPP_CHAR16:
    पक्ष CPP_CHAR32:
    पक्ष CPP_UTF8CHAR:
    पक्ष CPP_WCHAR:
      अभिव्यक्ति.मान = c_parser_peek_token (parser)->मान;
      set_c_अभिव्यक्ति_source_range (&अभिव्यक्ति, tok_range);
      c_parser_consume_token (parser);
      रोक;
    पक्ष CPP_STRING:
    पक्ष CPP_STRING16:
    पक्ष CPP_STRING32:
    पक्ष CPP_WSTRING:
    पक्ष CPP_UTF8STRING:
      अभिव्यक्ति = c_parser_string_literal (parser, असत्य, सत्य);
      रोक;
    पक्ष CPP_DOT:
      अभिव्यक्ति = c_parser_gimple_call_internal (parser);
      रोक;
    पक्ष CPP_NAME:
      यदि (c_parser_peek_token (parser)->id_kind == C_ID_ID)
	{
	  रूख id = c_parser_peek_token (parser)->मान;
	  यदि (म_भेद (IDENTIFIER_POINTER (id), "__MEM") == 0)
	    {
	      /* __MEM '<' type-name [ ',' number ] '>'
	               '(' [ '(' type-name ')' ] unary-expression
			   [ '+' number ]
			   [ ',' number ]
			   [ ',' number ':' number ] ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      रूख type = c_parser_gimple_typespec (parser);
	      संरचना c_अभिव्यक्ति ptr, alias_off, step, index, index2;
	      ptr.मान = error_mark_गाँठो;
	      alias_off.मान = NULL_रूख;
	      step.मान = NULL_रूख;
	      index.मान = NULL_रूख;
	      index2.मान = NULL_रूख;
	      अचिन्हित लघु clique = 0;
	      अचिन्हित लघु base = 0;
	      तार्किक reverse_order = असत्य;
	      संरचना c_अभिव्यक्ति ro;
	      यदि (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  रूख alias_type = NULL_रूख;
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
			  रूख tem;
			  alias_type = groktypename (alias_type_name,
						     &tem, रिक्त);
			}
		    }
		  ptr = c_parser_gimple_unary_expression (parser);
		  यदि (ptr.मान == error_mark_गाँठो
		      || ! POINTER_TYPE_P (रूख_TYPE (ptr.मान)))
		    {
		      यदि (ptr.मान != error_mark_गाँठो)
			error_at (ptr.get_start (),
				  "invalid type of %<__MEM%> operand");
		      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
						 "expected %<)%>");
		      फर्काऊ अभिव्यक्ति;
		    }
		  यदि (! alias_type)
		    alias_type = रूख_TYPE (ptr.मान);
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
		  अन्यथा यदि (alias_off.मान
			   && रूख_CODE (alias_off.मान) != INTEGER_CST)
		    std::swap (alias_off, index2);
		  यदि (c_parser_next_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      index2 = c_parser_gimple_postfix_expression (parser);
		    }
		  यदि (alias_off.मान)
		    {
		      यदि (रूख_CODE (alias_off.मान) != INTEGER_CST)
			error_at (alias_off.get_start (),
				  "expected constant offset for %<__MEM%> "
				  "operand");
		      alias_off.मान = fold_convert (alias_type,
						      alias_off.मान);
		    }
		  अन्यथा
		    alias_off.मान = build_int_cst (alias_type, 0);
		  यदि (step.मान)
		    {
		      यदि (रूख_CODE (step.मान) != INTEGER_CST)
			error_at (step.get_start (),
				  "expected constant step for %<__MEM%> "
				  "operand");
		    }
		  यदि (c_parser_next_token_is (parser, CPP_COMMA))
		    {
		      संरचना c_अभिव्यक्ति cl, ba;
		      तार्किक has_clb = सत्य;
		      c_parser_consume_token (parser);
		      cl = c_parser_gimple_postfix_expression (parser);
		      यदि (!c_parser_next_token_is (parser, CPP_COLON))
			{
			  ro = cl;
			  अचिन्हित HOST_WIDE_INT tmp = 0;
			  यदि (!रूख_fits_uhwi_p (ro.मान)
			      || (tmp = रूख_to_uhwi (ro.मान)) > 1)
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
			  यदि (!रूख_fits_uhwi_p (cl.मान)
			      || !रूख_fits_uhwi_p (ba.मान)
			      || compare_रूख_int (cl.मान,
						   (clique = रूख_to_uhwi
								(cl.मान)))
			      || compare_रूख_int (ba.मान,
						   (base = रूख_to_uhwi
								 (ba.मान))))
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
		  फर्काऊ अभिव्यक्ति;
		}
	      यदि (index.मान || step.मान || index2.मान)
		अभिव्यक्ति.मान = build5_loc (loc, TARGET_MEM_REF,
					 type, ptr.मान, alias_off.मान,
					 index.मान, step.मान, index2.मान);
	      अन्यथा
		अभिव्यक्ति.मान = build2_loc (loc, MEM_REF,
					 type, ptr.मान, alias_off.मान);
	      यदि (clique != 0)
		{
		  cfun->last_clique = MAX (cfun->last_clique, clique);
		  MR_DEPENDENCE_CLIQUE (अभिव्यक्ति.मान) = clique;
		  MR_DEPENDENCE_BASE (अभिव्यक्ति.मान) = base;
		}
	      यदि (reverse_order)
		{
		  यदि (रूख_CODE (अभिव्यक्ति.मान) == MEM_REF)
		    REF_REVERSE_STORAGE_ORDER (अभिव्यक्ति.मान) = reverse_order;
		  अन्यथा
		    error_at (ro.get_start (),
			      "target mem ref cannot have reverse order");
		}
	      रोक;
	    }
	  अन्यथा यदि (म_भेद (IDENTIFIER_POINTER (id), "__VIEW_CONVERT") == 0)
	    {
	      /* __VIEW_CONVERT '<' type-name [ ',' number ] '>'
	                        '(' postfix-expression ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      रूख type = c_parser_gimple_typespec (parser);
	      यदि (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_अभिव्यक्ति op = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  यदि (type && op.मान != error_mark_गाँठो)
		    अभिव्यक्ति.मान = build1_loc (loc, VIEW_CONVERT_अभिव्यक्ति,
					     type, op.मान);
		}
	      रोक;
	    }
	  अन्यथा यदि (म_भेद (IDENTIFIER_POINTER (id), "__BIT_FIELD_REF") == 0)
	    {
	      /* __BIT_FIELD_REF '<' type-name [ ',' number ] '>'
	                        '(' postfix-expression, integer, integer ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      रूख type = c_parser_gimple_typespec (parser);
	      यदि (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_अभिव्यक्ति op0 = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_अभिव्यक्ति op1 = c_parser_gimple_postfix_expression (parser);
		  यदि (रूख_CODE (op1.मान) != INTEGER_CST
		      || !int_fits_type_p (op1.मान, bitsizetype))
		    c_parser_error (parser, "expected constant size");
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_अभिव्यक्ति op2 = c_parser_gimple_postfix_expression (parser);
		  यदि (रूख_CODE (op2.मान) != INTEGER_CST
		      || !int_fits_type_p (op2.मान, bitsizetype))
		    c_parser_error (parser, "expected constant offset");
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  यदि (type
		      && op0.मान != error_mark_गाँठो
		      && रूख_CODE (op1.मान) == INTEGER_CST
		      && रूख_CODE (op2.मान) == INTEGER_CST)
		    अभिव्यक्ति.मान = build3_loc (loc, BIT_FIELD_REF, type,
					     op0.मान,
					     fold_convert (bitsizetype,
							   op1.मान),
					     fold_convert (bitsizetype,
							   op2.मान));
		}
	      रोक;
	    }
	  अन्यथा यदि (म_भेद (IDENTIFIER_POINTER (id), "__CLOBBER") == 0)
	    {
	      /* __CLOBBER [ '(' bob | eob | bos | eos ')' ]  */
	      clobber_kind kind = CLOBBER_UNDEF;
	      c_parser_consume_token (parser);
	      यदि (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
		{
		  c_parser_consume_token (parser);
		  स्वतः tok = c_parser_peek_token (parser);
		  यदि (c_parser_require (parser, CPP_NAME,
					"expected clobber kind"))
		    {
		      अचर वर्ण *kind_str = IDENTIFIER_POINTER (tok->मान);
		      यदि (म_भेद (kind_str, "bos") == 0)
			kind = CLOBBER_STORAGE_BEGIN;
		      अन्यथा यदि (म_भेद (kind_str, "bob") == 0)
			kind = CLOBBER_OBJECT_BEGIN;
		      अन्यथा यदि (म_भेद (kind_str, "eob") == 0)
			kind = CLOBBER_OBJECT_END;
		      अन्यथा यदि (म_भेद (kind_str, "eos") == 0)
			kind = CLOBBER_STORAGE_END;
		      अन्यथा
			c_parser_error (parser, "expected one of %<bos%>, "
					"%<eos%>, %<bob>, %<eob%>");
		    }
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      /* We infer the (redundant) type from the LHS.  */
	      अभिव्यक्ति.मान = build_clobber (ret_type, kind);
	      रोक;
	    }
	  अन्यथा यदि (म_भेद (IDENTIFIER_POINTER (id), "_Literal") == 0)
	    {
	      /* _Literal '(' type-name ')' ( [ '-' ] constant | constructor ) */
	      c_parser_consume_token (parser);
	      रूख type = NULL_रूख;
	      यदि (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  संरचना c_type_name *type_name = c_parser_type_name (parser);
		  रूख tem;
		  यदि (type_name)
		    type = groktypename (type_name, &tem, रिक्त);
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      यदि (! type)
		{
		  c_parser_error (parser, "invalid _Literal");
		  फर्काऊ अभिव्यक्ति;
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
		      फर्काऊ अभिव्यक्ति;
		    }
		  vec<constructor_elt, va_gc> *v = रिक्त;
		  तार्किक constant_p = सत्य;
		  यदि (VECTOR_TYPE_P (type)
		      && !c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
		    {
		      vec_alloc (v, TYPE_VECTOR_SUBPARTS (type).to_constant ());
		      गर
			{
			  रूख val
			    = c_parser_gimple_postfix_expression (parser).मान;
			  यदि (! val
			      || val == error_mark_गाँठो
			      || (! CONSTANT_CLASS_P (val)
				  && ! SSA_VAR_P (val)))
			    {
			      c_parser_error (parser, "invalid _Literal");
			      फर्काऊ अभिव्यक्ति;
			    }
			  CONSTRUCTOR_APPEND_ELT (v, NULL_रूख, val);
			  यदि (! CONSTANT_CLASS_P (val))
			    constant_p = असत्य;
			  यदि (c_parser_next_token_is (parser, CPP_COMMA))
			    c_parser_consume_token (parser);
			  अन्यथा
			    रोक;
			}
		      जबसम्म (1);
		    }
		  यदि (c_parser_require (parser, CPP_CLOSE_BRACE,
					"expected %<}%>"))
		    {
		      यदि (v && constant_p)
			अभिव्यक्ति.मान = build_vector_from_ctor (type, v);
		      अन्यथा
			अभिव्यक्ति.मान = build_constructor (type, v);
		    }
		  अन्यथा
		    {
		      c_parser_skip_until_found (parser, CPP_CLOSE_BRACE,
						 "expected %<}%>");
		      फर्काऊ अभिव्यक्ति;
		    }
		}
	      अन्यथा
		{
		  तार्किक neg_p, addr_p;
		  यदि ((neg_p = c_parser_next_token_is (parser, CPP_MINUS)))
		    c_parser_consume_token (parser);
		  यदि ((addr_p = c_parser_next_token_is (parser, CPP_AND)))
		    c_parser_consume_token (parser);
		  रूख val = c_parser_gimple_postfix_expression (parser).मान;
		  यदि (! val
		      || val == error_mark_गाँठो
		      || (!CONSTANT_CLASS_P (val) && !addr_p))
		    {
		      c_parser_error (parser, "invalid _Literal");
		      फर्काऊ अभिव्यक्ति;
		    }
		  यदि (addr_p)
		    {
		      val = build1 (ADDR_अभिव्यक्ति, type, val);
		      यदि (!is_gimple_invariant_address (val))
			{
			  c_parser_error (parser, "invalid _Literal");
			  फर्काऊ अभिव्यक्ति;
			}
		    }
		  यदि (neg_p)
		    {
		      val = const_unop (NEGATE_अभिव्यक्ति, रूख_TYPE (val), val);
		      यदि (! val)
			{
			  c_parser_error (parser, "invalid _Literal");
			  फर्काऊ अभिव्यक्ति;
			}
		    }
		  अभिव्यक्ति.मान = fold_convert (type, val);
		}
	      फर्काऊ अभिव्यक्ति;
	    }

	  /* SSA name.  */
	  अचिन्हित version, ver_offset;
	  यदि (! lookup_name (id)
	      && c_parser_parse_ssa_name_id (id, &version, &ver_offset))
	    {
	      c_parser_consume_token (parser);
	      अभिव्यक्ति.मान = c_parser_parse_ssa_name (parser, id, NULL_रूख,
						    version, ver_offset);
	      यदि (अभिव्यक्ति.मान == error_mark_गाँठो)
		फर्काऊ अभिव्यक्ति;
	      set_c_अभिव्यक्ति_source_range (&अभिव्यक्ति, tok_range);
	      /* For default definition SSA names.  */
	      यदि (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
		  && c_parser_peek_2nd_token (parser)->type == CPP_NAME
		  && म_भेद ("D",
			     IDENTIFIER_POINTER
			       (c_parser_peek_2nd_token (parser)->मान)) == 0
		  && c_parser_peek_nth_token (parser, 3)->type == CPP_CLOSE_PAREN)
		{
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		  यदि (! SSA_NAME_IS_DEFAULT_DEF (अभिव्यक्ति.मान))
		    {
		      यदि (!SSA_NAME_VAR (अभिव्यक्ति.मान))
			{
			  error_at (loc, "anonymous SSA name cannot have"
				    " default definition");
			  अभिव्यक्ति.मान = error_mark_गाँठो;
			  फर्काऊ अभिव्यक्ति;
			}
		      set_ssa_default_def (cfun, SSA_NAME_VAR (अभिव्यक्ति.मान),
					   अभिव्यक्ति.मान);
		      SSA_NAME_DEF_STMT (अभिव्यक्ति.मान) = gimple_build_nop ();
		    }
		}
	    }
	  अन्यथा
	    {
	      c_parser_consume_token (parser);
	      अभिव्यक्ति.मान
		= build_external_ref (loc, id,
				      (c_parser_peek_token (parser)->type
				       == CPP_OPEN_PAREN), &अभिव्यक्ति.original_type);
	      set_c_अभिव्यक्ति_source_range (&अभिव्यक्ति, tok_range);
	    }
	  रोक;
	}
      /* Fallthru.  */
    स्वभाव:
      c_parser_error (parser, "expected expression");
      अभिव्यक्ति.set_error ();
      रोक;
    }
  यदि (अभिव्यक्ति.मान == error_mark_गाँठो)
    फर्काऊ अभिव्यक्ति;
  फर्काऊ c_parser_gimple_postfix_expression_after_primary
    (parser, अभिव्यक्ति_LOC_OR_LOC (अभिव्यक्ति.मान, loc), अभिव्यक्ति);
}

/* Parse a gimple postfix expression after the initial primary or compound
   literal.  */

स्थिर संरचना c_अभिव्यक्ति
c_parser_gimple_postfix_expression_after_primary (gimple_parser &parser,
						  location_t अभिव्यक्ति_loc,
						  संरचना c_अभिव्यक्ति अभिव्यक्ति)
{
  location_t start;
  location_t finish;
  रूख ident;
  location_t comp_loc;

  जबसम्म (सत्य)
    {
      location_t op_loc = c_parser_peek_token (parser)->location;
      विकल्प (c_parser_peek_token (parser)->type)
	{
	पक्ष CPP_OPEN_SQUARE:
	  {
	    c_parser_consume_token (parser);
	    रूख idx = c_parser_gimple_unary_expression (parser).मान;

	    यदि (! c_parser_require (parser, CPP_CLOSE_SQUARE, "expected %<]%>"))
	      {
		c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE, रिक्त);
		रोक;
	      }

	    start = अभिव्यक्ति.get_start ();
	    finish = c_parser_tokens_buf (parser, 0)->location;
	    अभिव्यक्ति.मान = build_array_ref (op_loc, अभिव्यक्ति.मान, idx);
	    set_c_अभिव्यक्ति_source_range (&अभिव्यक्ति, start, finish);
	    अभिव्यक्ति.m_decimal = 0;

	    अभिव्यक्ति.original_code = ERROR_MARK;
	    अभिव्यक्ति.original_type = रिक्त;
	    रोक;
	  }
	पक्ष CPP_OPEN_PAREN:
	  {
	    /* Function call.  */
	    c_parser_consume_token (parser);
	    auto_vec<रूख> exprlist;
	    यदि (! c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	      c_parser_gimple_अभिव्यक्ति_list (parser, &exprlist);
	    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    यदि (!FUNC_OR_METHOD_TYPE_P (रूख_TYPE (अभिव्यक्ति.मान)))
	      {
		c_parser_error (parser, "invalid call to non-function");
		अभिव्यक्ति.set_error ();
		रोक;
	      }
	    अभिव्यक्ति.मान = build_call_array_loc
		(अभिव्यक्ति_loc, रूख_TYPE (रूख_TYPE (अभिव्यक्ति.मान)),
		 अभिव्यक्ति.मान, exprlist.length (), exprlist.address ());
	    अभिव्यक्ति.m_decimal = 0;
	    अभिव्यक्ति.original_code = ERROR_MARK;
	    अभिव्यक्ति.original_type = रिक्त;
	    रोक;
	  }
	पक्ष CPP_DOT:
	  {
	    /* Structure element reference.  */
	    c_parser_consume_token (parser);
	    यदि (c_parser_next_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		ident = comp_tok->मान;
		comp_loc = comp_tok->location;
	      }
	    अन्यथा
	      {
		c_parser_error (parser, "expected identifier");
		अभिव्यक्ति.set_error ();
		अभिव्यक्ति.original_code = ERROR_MARK;
		अभिव्यक्ति.original_type = रिक्त;
		फर्काऊ अभिव्यक्ति;
	      }
	    start = अभिव्यक्ति.get_start ();
	    finish = c_parser_peek_token (parser)->get_finish ();
	    c_parser_consume_token (parser);
	    अभिव्यक्ति.मान = build_component_ref (op_loc, अभिव्यक्ति.मान, ident,
					      comp_loc, UNKNOWN_LOCATION);
	    set_c_अभिव्यक्ति_source_range (&अभिव्यक्ति, start, finish);
	    अभिव्यक्ति.m_decimal = 0;
	    अभिव्यक्ति.original_code = ERROR_MARK;
	    यदि (रूख_CODE (अभिव्यक्ति.मान) != COMPONENT_REF)
	      अभिव्यक्ति.original_type = रिक्त;
	    अन्यथा
	      {
		/* Remember the original type of a bitfield.  */
		रूख field = रूख_OPERAND (अभिव्यक्ति.मान, 1);
		यदि (रूख_CODE (field) != FIELD_DECL)
		  अभिव्यक्ति.original_type = रिक्त;
		अन्यथा
		  अभिव्यक्ति.original_type = DECL_BIT_FIELD_TYPE (field);
	      }
	    रोक;
	  }
	पक्ष CPP_DEREF:
	  {
	    /* Structure element reference.  */
	    यदि (!POINTER_TYPE_P (रूख_TYPE (अभिव्यक्ति.मान)))
	      {
		c_parser_error (parser, "dereference of non-pointer");
		अभिव्यक्ति.set_error ();
		अभिव्यक्ति.original_code = ERROR_MARK;
		अभिव्यक्ति.original_type = रिक्त;
		फर्काऊ अभिव्यक्ति;
	      }
	    c_parser_consume_token (parser);
	    यदि (c_parser_next_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		ident = comp_tok->मान;
		comp_loc = comp_tok->location;
	      }
	    अन्यथा
	      {
		c_parser_error (parser, "expected identifier");
		अभिव्यक्ति.set_error ();
		अभिव्यक्ति.original_code = ERROR_MARK;
		अभिव्यक्ति.original_type = रिक्त;
		फर्काऊ अभिव्यक्ति;
	      }
	    start = अभिव्यक्ति.get_start ();
	    finish = c_parser_peek_token (parser)->get_finish ();
	    c_parser_consume_token (parser);
	    अभिव्यक्ति.मान = build_component_ref (op_loc,
					      build_simple_mem_ref_loc
					        (op_loc, अभिव्यक्ति.मान),
					      ident, comp_loc,
					      अभिव्यक्ति.get_location ());
	    set_c_अभिव्यक्ति_source_range (&अभिव्यक्ति, start, finish);
	    अभिव्यक्ति.m_decimal = 0;
	    अभिव्यक्ति.original_code = ERROR_MARK;
	    यदि (रूख_CODE (अभिव्यक्ति.मान) != COMPONENT_REF)
	      अभिव्यक्ति.original_type = रिक्त;
	    अन्यथा
	      {
		/* Remember the original type of a bitfield.  */
		रूख field = रूख_OPERAND (अभिव्यक्ति.मान, 1);
		यदि (रूख_CODE (field) != FIELD_DECL)
		  अभिव्यक्ति.original_type = रिक्त;
		अन्यथा
		  अभिव्यक्ति.original_type = DECL_BIT_FIELD_TYPE (field);
	      }
	    रोक;
	  }
	स्वभाव:
	  फर्काऊ अभिव्यक्ति;
	}
    }
}

/* Parse expression list.

   gimple-expr-list:
     gimple-unary-expression
     gimple-expr-list , gimple-unary-expression

 */

स्थिर शून्य
c_parser_gimple_अभिव्यक्ति_list (gimple_parser &parser, vec<रूख> *ret)
{
  संरचना c_अभिव्यक्ति अभिव्यक्ति;

  अभिव्यक्ति = c_parser_gimple_unary_expression (parser);
  ret->safe_थप (अभिव्यक्ति.मान);
  जबसम्म (c_parser_next_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      अभिव्यक्ति = c_parser_gimple_unary_expression (parser);
      ret->safe_थप (अभिव्यक्ति.मान);
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
  रूख name = c_parser_peek_token (parser)->मान;
  location_t loc1 = c_parser_peek_token (parser)->location;
  gcc_assert (c_parser_next_token_is (parser, CPP_NAME));
  c_parser_consume_token (parser);
  gcc_assert (c_parser_next_token_is (parser, CPP_COLON));
  c_parser_consume_token (parser);
  रूख label = define_label (loc1, name);
  यदि (label)
    gimple_seq_add_stmt_without_update (seq, gimple_build_label (label));
  फर्काऊ;
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
    फर्काऊ;
  c_parser_consume_token (parser);

  specs->entry_bb_गन्ती = profile_गन्ती::uninitialized ();
  जबसम्म (c_parser_next_token_is (parser, CPP_NAME))
    {
      profile_quality quality;
      अचर वर्ण *op = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान);
      c_parser_consume_token (parser);
      यदि (! म_भेद (op, "startwith"))
	{
	  यदि (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    फर्काऊ;
	  यदि (c_parser_next_token_is_not (parser, CPP_STRING))
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"expected pass name");
	      फर्काऊ;
	    }
	  pass = xstrdup (रूख_STRING_POINTER
			  (c_parser_string_literal (parser, असत्य,
						    असत्य).मान));
	  यदि (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<(%>"))
	    फर्काऊ;
	}
      अन्यथा यदि (parse_profile_quality (op, &quality))
	{
	  रूख q;
	  यदि (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    फर्काऊ;

	  यदि (!c_parser_next_token_is (parser, CPP_सङ्ख्या)
	      || (रूख_CODE (q = c_parser_peek_token (parser)->मान)
		  != INTEGER_CST))
	    {
	      c_parser_error (parser, "expected count value");
	      फर्काऊ;
	    }

	  specs->entry_bb_गन्ती
	    = profile_गन्ती::from_gcov_type (रूख_INT_CST_तल्लो (q), quality);
	  c_parser_consume_token (parser);
	  यदि (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    फर्काऊ;
	}
      अन्यथा यदि (specs->declspec_il != cdil_gimple)
	/* Allow only one IL specifier and none on RTL.  */
	;
      अन्यथा यदि (! म_भेद (op, "cfg"))
	specs->declspec_il = cdil_gimple_cfg;
      अन्यथा यदि (! म_भेद (op, "ssa"))
	specs->declspec_il = cdil_gimple_ssa;
      अन्यथा
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "invalid operation");
	  फर्काऊ;
	}
     यदि (c_parser_next_token_is (parser, CPP_COMMA))
       c_parser_consume_token (parser);
    }

  यदि (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    फर्काऊ;

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
      फर्काऊ;
    }

  तार्किक dummy = असत्य;
  declarator = c_parser_declarator (parser,
				    specs->typespec_kind != ctsk_none,
				    C_DTR_NORMAL, &dummy);

  यदि (!c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_error (parser, "expected %<;%>");
      फर्काऊ;
    }
  यदि (declarator)
    {
      /* Handle SSA name decls specially, they do not go into the identifier
         table but we simply build the SSA name for later lookup.  */
      अचिन्हित version, ver_offset;
      /* Handle SSA pointer declarations in a very simplistic ways, we
	 probably would like to call grokdeclarator in a special mode to
	 just build the type of the decl - start_decl already pushes
	 the identifier to the bindings for lookup, something we do not
	 want.  */
      संरचना c_declarator *id_declarator = declarator;
      जबसम्म (id_declarator->kind == cdk_pointer)
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
	  रूख type = specs->type;
	  जबसम्म (p->kind == cdk_pointer)
	    {
	      type = build_pointer_type (type);
	      p = p->declarator;
	    }
	  c_parser_parse_ssa_name (parser, id_declarator->u.id.id, type,
				   version, ver_offset);
	}
      अन्यथा
	{
	  रूख postfix_attrs = NULL_रूख;
	  रूख all_prefix_attrs = specs->attrs;
	  specs->attrs = रिक्त;
	  रूख decl = start_decl (declarator, specs, असत्य,
				  chainon (postfix_attrs, all_prefix_attrs));
	  यदि (decl)
	    finish_decl (decl, UNKNOWN_LOCATION, NULL_रूख, NULL_रूख,
			 NULL_रूख);
	}
    }
}

/* Parse gimple goto statement.  */

स्थिर शून्य
c_parser_gimple_goto_stmt (gimple_parser &parser,
			   location_t loc, रूख label, gimple_seq *seq)
{
  यदि (cfun->curr_properties & PROP_cfg)
    {
      पूर्णाङ्क dest_index;
      profile_probability prob;
      यदि (c_parser_gimple_parse_bb_spec_edge_probability (label, parser,
							  &dest_index, &prob))
	{
	  parser.थप_edge (parser.current_bb->index, dest_index,
			    EDGE_FALLTHRU, prob);
	  फर्काऊ;
	}
    }
  रूख decl = lookup_label_for_goto (loc, label);
  gimple_seq_add_stmt_without_update (seq, gimple_build_goto (decl));
}

/* Parse a parenthesized condition.
   gimple-condition:
     ( gimple-binary-expression )    */

स्थिर रूख
c_parser_gimple_paren_condition (gimple_parser &parser)
{
  यदि (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    फर्काऊ error_mark_गाँठो;
  रूख cond
    = c_parser_gimple_द्विआधारी_expression (parser, boolean_type_गाँठो).मान;
  यदि (cond != error_mark_गाँठो
      && ! COMPARISON_CLASS_P (cond)
      && ! CONSTANT_CLASS_P (cond)
      && ! SSA_VAR_P (cond))
    {
      c_parser_error (parser, "comparison required");
      cond = error_mark_गाँठो;
    }
  यदि (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    फर्काऊ error_mark_गाँठो;
  फर्काऊ cond;
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
	  && म_भेद (IDENTIFIER_POINTER (c_parser_peek_token (parser)->मान),
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
  रूख t_label = NULL_रूख, f_label = NULL_रूख, label;
  location_t loc;
  c_parser_consume_token (parser);
  रूख cond = c_parser_gimple_paren_condition (parser);

  यदि (c_parser_next_token_is_keyword (parser, RID_GOTO))
    {
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      यदि (! c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected label");
	  फर्काऊ;
	}
      label = c_parser_peek_token (parser)->मान;
      c_parser_consume_token (parser);
      पूर्णाङ्क dest_index;
      profile_probability prob;
      यदि ((cfun->curr_properties & PROP_cfg)
	  && c_parser_gimple_parse_bb_spec_edge_probability (label, parser,
							     &dest_index, &prob))
	parser.थप_edge (parser.current_bb->index, dest_index,
			  EDGE_TRUE_मान, prob);
      अन्यथा
	t_label = lookup_label_for_goto (loc, label);
      यदि (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	फर्काऊ;
    }
  अन्यथा
    {
      c_parser_error (parser, "expected goto expression");
      फर्काऊ;
    }

  यदि (c_parser_next_token_is_keyword (parser, RID_ELSE))
    c_parser_consume_token (parser);
  अन्यथा
    {
      c_parser_error (parser, "expected else statement");
      फर्काऊ;
    }

  यदि (c_parser_next_token_is_keyword (parser, RID_GOTO))
    {
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      यदि (! c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected label");
	  फर्काऊ;
	}
      label = c_parser_peek_token (parser)->मान;
      c_parser_consume_token (parser);
      पूर्णाङ्क dest_index;
      profile_probability prob;
      यदि ((cfun->curr_properties & PROP_cfg)
	  && c_parser_gimple_parse_bb_spec_edge_probability (label, parser,
							     &dest_index, &prob))
	parser.थप_edge (parser.current_bb->index, dest_index,
			  EDGE_FALSE_मान, prob);
      अन्यथा
	f_label = lookup_label_for_goto (loc, label);
      यदि (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	फर्काऊ;
    }
  अन्यथा
    {
      c_parser_error (parser, "expected goto expression");
      फर्काऊ;
    }

  यदि (cond != error_mark_गाँठो)
    gimple_seq_add_stmt_without_update (seq, gimple_build_cond_from_रूख (cond, t_label,
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
  c_अभिव्यक्ति cond_अभिव्यक्ति;
  रूख case_label, label;
  auto_vec<रूख> labels;
  रूख default_label = NULL_रूख;
  c_parser_consume_token (parser);

  यदि (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    फर्काऊ;
  cond_अभिव्यक्ति = c_parser_gimple_postfix_expression (parser);
  यदि (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    फर्काऊ;

  यदि (! c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    फर्काऊ;

  जबसम्म (c_parser_next_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      यदि (c_parser_next_token_is (parser, CPP_EOF))
	{
	  c_parser_error (parser, "expected statement");
	  फर्काऊ;
	}

      विकल्प (c_parser_peek_token (parser)->keyword)
	{
	पक्ष RID_CASE:
	  {
	    c_अभिव्यक्ति exp1;
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);

	    यदि (c_parser_next_token_is (parser, CPP_NAME)
		|| c_parser_peek_token (parser)->type == CPP_सङ्ख्या)
	      exp1 = c_parser_gimple_postfix_expression (parser);
	    अन्यथा
	      {
		c_parser_error (parser, "expected expression");
		फर्काऊ;
	      }

	    यदि (c_parser_next_token_is (parser, CPP_COLON))
	      {
		c_parser_consume_token (parser);
		यदि (c_parser_next_token_is (parser, CPP_NAME))
		  {
		    label = c_parser_peek_token (parser)->मान;
		    c_parser_consume_token (parser);
		    रूख decl = lookup_label_for_goto (loc, label);
		    case_label = build_case_label (exp1.मान, NULL_रूख,
						   decl);
		    labels.safe_थप (case_label);
		    यदि (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      फर्काऊ;
		  }
		अन्यथा यदि (! c_parser_require (parser, CPP_NAME,
					     "expected label"))
		  फर्काऊ;
	      }
	    अन्यथा यदि (! c_parser_require (parser, CPP_SEMICOLON,
					 "expected %<:%>"))
	      फर्काऊ;
	    रोक;
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
		    label = c_parser_peek_token (parser)->मान;
		    c_parser_consume_token (parser);
		    रूख decl = lookup_label_for_goto (loc, label);
		    default_label = build_case_label (NULL_रूख, NULL_रूख,
						      decl);
		    यदि (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      फर्काऊ;
		  }
		अन्यथा यदि (! c_parser_require (parser, CPP_NAME,
					     "expected label"))
		  फर्काऊ;
	      }
	    अन्यथा यदि (! c_parser_require (parser, CPP_SEMICOLON,
					 "expected %<:%>"))
	      फर्काऊ;
	    रोक;
	  }
	स्वभाव:
	  c_parser_error (parser, "expected case label");
	  फर्काऊ;
	}

    }
  यदि (! c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>"))
    फर्काऊ;

  यदि (cond_अभिव्यक्ति.मान != error_mark_गाँठो)
    {
      gswitch *s = gimple_build_switch (cond_अभिव्यक्ति.मान, default_label, labels);
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
      c_finish_gimple_return (loc, NULL_रूख);
      ret = gimple_build_return (रिक्त);
      gimple_seq_add_stmt_without_update (seq, ret);
    }
  अन्यथा
    {
      location_t xloc = c_parser_peek_token (parser)->location;
      c_अभिव्यक्ति अभिव्यक्ति = c_parser_gimple_unary_expression (parser);
      यदि (अभिव्यक्ति.मान != error_mark_गाँठो)
	{
	  c_finish_gimple_return (xloc, अभिव्यक्ति.मान);
	  ret = gimple_build_return (अभिव्यक्ति.मान);
	  gimple_seq_add_stmt_without_update (seq, ret);
	}
    }
}

/* Support function for c_parser_gimple_return_stmt.  */

स्थिर शून्य
c_finish_gimple_return (location_t loc, रूख retval)
{
  रूख valtype = रूख_TYPE (रूख_TYPE (current_function_decl));

  /* Use the expansion point to handle cases such as returning NULL
     in a function returning void.  */
  location_t xloc = expansion_point_location_if_in_system_header (loc);

  यदि (रूख_THIS_VOLATILE (current_function_decl))
    warning_at (xloc, 0,
		"function declared %<noreturn%> has a %<return%> statement");

  यदि (! retval)
    current_function_returns_null = 1;
  अन्यथा यदि (valtype == 0 || VOID_TYPE_P (valtype))
    {
      current_function_returns_null = 1;
      यदि (रूख_CODE (रूख_TYPE (retval)) != VOID_TYPE)
	{
	  error_at
	    (xloc, "%<return%> with a value, in function returning void");
	  inform (DECL_SOURCE_LOCATION (current_function_decl),
		  "declared here");
	}
    }
  अन्यथा यदि (रूख_CODE (valtype) != रूख_CODE (रूख_TYPE (retval)))
    {
      error_at
	(xloc, "invalid conversion in return statement");
      inform (DECL_SOURCE_LOCATION (current_function_decl),
	      "declared here");
    }
  फर्काऊ;
}
