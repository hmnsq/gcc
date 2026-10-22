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

#समावेश "config.h"
#समावेश "system.h"
#समावेश "coretypes.h"
#समावेश "target.h"
#समावेश "function.h"
#समावेश "c-tree.h"
#समावेश "timevar.h"
#समावेश "stringpool.h"
#समावेश "cgraph.h"
#समावेश "attribs.h"
#समावेश "stor-layout.h"
#समावेश "varasm.h"
#समावेश "trans-mem.h"
#समावेश "c-family/c-pragma.h"
#समावेश "c-lang.h"
#समावेश "c-family/c-objc.h"
#समावेश "plugin.h"
#समावेश "builtins.h"
#समावेश "gomp-constants.h"
#समावेश "c-family/c-indentation.h"
#समावेश "gimple-expr.h"
#समावेश "context.h"
#समावेश "gcc-rich-location.h"
#समावेश "c-parser.h"
#समावेश "tree-vrp.h"
#समावेश "tree-pass.h"
#समावेश "tree-pretty-print.h"
#समावेश "tree.h"
#समावेश "basic-block.h"
#समावेश "gimple.h"
#समावेश "gimple-pretty-print.h"
#समावेश "tree-ssa.h"
#समावेश "pass_manager.h"
#समावेश "tree-ssanames.h"
#समावेश "gimple-ssa.h"
#समावेश "tree-dfa.h"
#समावेश "internal-fn.h"
#समावेश "cfg.h"
#समावेश "cfghooks.h"
#समावेश "bitmap.h"
#समावेश "cfganal.h"
#समावेश "tree-cfg.h"
#समावेश "gimple-iterator.h"
#समावेश "cfgloop.h"
#समावेश "tree-phinodes.h"
#समावेश "tree-into-ssa.h"


/* GIMPLE parser state.  */

श्रेणी gimple_parser
{
खुला:
  gimple_parser (c_parser *p) : parser (p), edges(), current_bb(शून्य) {}
  /* c_parser is not visible here, use composition and fake inheritance
     via a conversion operator.  */
  चालक c_parser *() { वापस parser; }
  c_parser *parser;

  /* CFG build state.  */
  श्रेणी gimple_parser_edge
  {
  खुला:
    पूर्णांक src;
    पूर्णांक dest;
    पूर्णांक flags;
    profile_probability probability;
  };
  auto_vec<gimple_parser_edge> edges;
  basic_block current_bb;

  व्योम धकेलो_edge (पूर्णांक, पूर्णांक, पूर्णांक, profile_probability);
};

व्योम
gimple_parser::धकेलो_edge (पूर्णांक src, पूर्णांक dest, पूर्णांक flags,
			  profile_probability prob)
{
  gimple_parser_edge e;
  e.src = src;
  e.dest = dest;
  e.flags = flags;
  e.probability = prob;
  edges.safe_धकेलो (e);
}


/* Gimple parsing functions.  */
अटल bool c_parser_gimple_compound_statement (gimple_parser &, gimple_seq *);
अटल व्योम c_parser_gimple_label (gimple_parser &, gimple_seq *);
अटल व्योम c_parser_gimple_statement (gimple_parser &, gimple_seq *);
अटल काष्ठा c_व्यंजक c_parser_gimple_द्विआधारी_expression (gimple_parser &, वृक्ष);
अटल काष्ठा c_व्यंजक c_parser_gimple_unary_expression (gimple_parser &);
अटल काष्ठा c_व्यंजक c_parser_gimple_postfix_expression
			(gimple_parser &, वृक्ष = error_mark_गाँठ);
अटल काष्ठा c_व्यंजक c_parser_gimple_postfix_expression_after_primary
			(gimple_parser &, location_t, काष्ठा c_व्यंजक);
अटल व्योम c_parser_gimple_declaration (gimple_parser &);
अटल व्योम c_parser_gimple_goto_stmt (gimple_parser &, location_t,
				       वृक्ष, gimple_seq *);
अटल व्योम c_parser_gimple_try_stmt (gimple_parser &, gimple_seq *);
अटल व्योम c_parser_gimple_if_stmt (gimple_parser &, gimple_seq *);
अटल व्योम c_parser_gimple_switch_stmt (gimple_parser &, gimple_seq *);
अटल व्योम c_parser_gimple_return_stmt (gimple_parser &, gimple_seq *);
अटल व्योम c_finish_gimple_return (location_t, वृक्ष);
अटल वृक्ष c_parser_gimple_paren_condition (gimple_parser &);
अटल व्योम c_parser_gimple_व्यंजक_list (gimple_parser &, vec<वृक्ष> *);


/* Much like parser_build_unary_op, but avoid applying default conversions.  */

अटल c_व्यंजक
gimple_parser_build_unary_op (location_t loc,
			      क्रमागत वृक्ष_code code, काष्ठा c_व्यंजक arg)
{
  काष्ठा c_व्यंजक परिणाम;

  परिणाम.original_code = code;
  परिणाम.original_type = शून्य;
  परिणाम.m_decimal = 0;

  अगर (reject_gcc_builtin (arg.मूल्य))
    {
      परिणाम.मूल्य = error_mark_गाँठ;
    }
  अन्यथा
    {
      परिणाम.मूल्य = build_unary_op (loc, code, arg.मूल्य, true);

      अगर (वृक्ष_OVERFLOW_P (परिणाम.मूल्य) && !वृक्ष_OVERFLOW_P (arg.मूल्य))
	overflow_warning (loc, परिणाम.मूल्य, arg.मूल्य);
    }

  /* We are typically called when parsing a prefix token at LOC acting on
     ARG.  Reflect this by updating the source range of the result to
     start at LOC and end at the end of ARG.  */
  set_c_व्यंजक_source_range (&परिणाम,
			   loc, arg.get_finish ());

  वापस परिणाम;
}

/* See if VAL is an identifier matching __BB<num> and return <num>
   in *INDEX.  */

अटल bool
c_parser_gimple_parse_bb_spec (वृक्ष val, पूर्णांक *सूचकांक)
{
  अगर (!startswith (IDENTIFIER_POINTER (val), "__BB"))
    वापस false;

  स्थिर अक्षर *bb = IDENTIFIER_POINTER (val) + 4;
  अगर (! ISDIGIT (*bb))
    वापस false;

  अक्षर *pend;
  त्रुटि_सं = 0;
  स्थिर अचिन्हित दीर्घ संख्या = म_से_अदीर्घ (bb, &pend, 10);
  अगर (त्रुटि_सं == दुस्फल
      || *pend != '\0'
      || संख्या > पूर्णांक_उच्च)
    वापस false;

  *सूचकांक = संख्या;
  वापस true;
}

/* See if VAL is an identifier matching __BB<num> and return <num>
   in *INDEX.  Return true if so and parse also FREQUENCY of
   the edge.  */


अटल bool
c_parser_gimple_parse_bb_spec_edge_probability (वृक्ष val,
						gimple_parser &parser,
						पूर्णांक *सूचकांक,
						profile_probability
						*probability)
{
  bool return_p = c_parser_gimple_parse_bb_spec (val, सूचकांक);
  अगर (return_p)
    {
      *probability = profile_probability::uninitialized ();
      /* Parse frequency if provided.  */
      अगर (c_parser_अग्र_token_is (parser, CPP_OPEN_PAREN))
	{
	  वृक्ष f;
	  c_parser_consume_token (parser);
	  अगर (!c_parser_अग्र_token_is (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected frequency quality");
	      वापस false;
	    }

	  profile_quality quality;
	  स्थिर अक्षर *v
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य);
	  अगर (!parse_profile_quality (v, &quality))
	    {
	      c_parser_error (parser, "unknown profile quality");
	      वापस false;
	    }

	  c_parser_consume_token (parser);
	  अगर (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    वापस false;

	  अगर (!c_parser_अग्र_token_is (parser, CPP_संख्या)
	      || (वृक्ष_CODE (f = c_parser_peek_token (parser)->मूल्य)
		  != INTEGER_CST))
	    {
	      c_parser_error (parser, "expected frequency value");
	      वापस false;
	    }

	  अचिन्हित पूर्णांक मूल्य = वृक्ष_INT_CST_निचला (f);
	  *probability = profile_probability (मूल्य, quality);

	  c_parser_consume_token (parser);
	  अगर (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    वापस false;

	  अगर (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    वापस false;
	}

      वापस true;
    }

  वापस false;

}

/* Parse the body of a function declaration marked with "__GIMPLE".  */

व्योम
c_parser_parse_gimple_body (c_parser *cparser, अक्षर *gimple_pass,
			    क्रमागत c_declspec_il cdil,
			    profile_गिनती entry_bb_गिनती)
{
  gimple_parser parser (cparser);
  gimple_seq seq = शून्य;
  gimple_seq body = शून्य;
  वृक्ष stmt = धकेलो_stmt_list ();
  धकेलो_scope ();
  location_t loc1 = c_parser_peek_token (parser)->location;

  cfun->pass_startwith = gimple_pass;
  init_वृक्ष_ssa (cfun);

  अगर (cdil == cdil_gimple)
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
      set_loops_for_fn (cfun, ggc_cleared_alloc<काष्ठा loops> ());
      init_loops_structure (cfun, loops_for_fn (cfun), 1);
      loops_state_set (cfun, LOOPS_NEED_FIXUP|LOOPS_MAY_HAVE_MULTIPLE_LATCHES);
      cfun->curr_properties
	|= PROP_gimple_lcf | PROP_gimple_leh | PROP_cfg | PROP_loops;
      अगर (cdil == cdil_gimple_ssa)
	{
	  init_ssa_operands (cfun);
	  cfun->curr_properties |= PROP_ssa;
	}
    }

  अगर (! c_parser_gimple_compound_statement (parser, &seq)
      && cdil == cdil_gimple)
    {
      gimple *ret = gimple_build_return (शून्य);
      gimple_seq_add_stmt_without_update (&seq, ret);
    }

  वृक्ष block = निकालो_scope ();
  stmt = निकालो_stmt_list (stmt);
  stmt = c_build_bind_व्यंजक (loc1, block, stmt);

  block = DECL_INITIAL (current_function_decl);
  BLOCK_SUBBLOCKS (block) = NULL_वृक्ष;
  BLOCK_CHAIN (block) = NULL_वृक्ष;
  वृक्ष_ASM_WRITTEN (block) = 1;

  अगर (cdil == cdil_gimple)
    {
      gbind *bind_stmt = gimple_build_bind (BIND_व्यंजक_VARS (stmt), शून्य,
					    BIND_व्यंजक_BLOCK (stmt));
      gimple_bind_set_body (bind_stmt, seq);
      gimple_seq_add_stmt_without_update (&body, bind_stmt);
      gimple_set_body (current_function_decl, body);
    }
  अन्यथा
    {
      /* Control-flow and binds are lowered, record local decls.  */
      क्रम (वृक्ष var = BIND_व्यंजक_VARS (stmt); var; var = DECL_CHAIN (var))
	अगर (VAR_P (var)
	    && !DECL_EXTERNAL (var))
	  {
	    add_local_decl (cfun, var);
	    /* When the middle-end re-gimplifies any expression we might
	       run into the assertion that we've seen the decl in a BIND.  */
	    अगर (!वृक्ष_STATIC (var))
	      DECL_SEEN_IN_BIND_व्यंजक_P (var) = 1;
	  }
      /* We have a CFG.  Build the edges.  */
      क्रम (अचिन्हित i = 0; i < parser.edges.लंबाई (); ++i)
	{
	  edge e = make_edge (BASIC_BLOCK_FOR_FN (cfun, parser.edges[i].src),
			      BASIC_BLOCK_FOR_FN (cfun, parser.edges[i].dest),
			      parser.edges[i].flags);
	  e->probability = parser.edges[i].probability;
	}
      /* Add edges for case labels.  */
      basic_block bb;
      FOR_EACH_BB_FN (bb, cfun)
	अगर (EDGE_गिनती (bb->succs) == 0)
	  {
	    अगर (gswitch *sw = safe_dyn_cast <gswitch *> (*gsi_last_bb (bb)))
	      क्रम (अचिन्हित i = 0; i < gimple_switch_अंक_labels (sw); ++i)
		{
		  basic_block label_bb = gimple_switch_label_bb (cfun, sw, i);
		  make_edge (bb, label_bb, 0);
		}
	  }
      /* Need those for loop fixup.  */
      calculate_dominance_info (CDI_DOMINATORS);
      /* With SSA lower PHIs parsed as internal function calls and
	 update stmts.  */
      अगर (cdil == cdil_gimple_ssa)
	{
	  /* Create PHI nodes, they are parsed into __PHI internal calls
	     and update SSA operands.  */
	  FOR_EACH_BB_FN (bb, cfun)
	    {
	      gimple_stmt_iterator gsi;
	      क्रम (gsi = gsi_start_bb (bb); !gsi_end_p (gsi);)
		{
		  gimple *stmt = gsi_stmt (gsi);
		  अगर (!gimple_call_internal_p (stmt, IFN_PHI))
		    अवरोध;

		  gphi *phi = create_phi_गाँठ (gimple_call_lhs (stmt), bb);
		  क्रम (अचिन्हित i = 0; i < gimple_call_अंक_args (stmt); i += 2)
		    {
		      पूर्णांक srcidx = वृक्ष_INT_CST_निचला (gimple_call_arg (stmt, i));
		      edge e = find_edge (BASIC_BLOCK_FOR_FN (cfun, srcidx), bb);
		      अगर (!e)
			c_parser_error (parser, "edge not found");
		      अन्यथा
			add_phi_arg (phi, gimple_call_arg (stmt, i + 1), e,
				     UNKNOWN_LOCATION);
		    }
		  gsi_remove (&gsi, true);
		}
	      क्रम (; !gsi_end_p (gsi); gsi_अग्र (&gsi))
		update_stmt (gsi_stmt (gsi));
	    }
	  /* Fill SSA name gaps, putting them on the freelist and diagnose
	     SSA names without definition.  */
	  क्रम (अचिन्हित i = 1; i < अंक_ssa_names; ++i)
	    अगर (!ssa_name (i))
	      {
		वृक्ष name = make_ssa_name_fn (cfun, integer_type_गाँठ, शून्य, i);
		release_ssa_name_fn (cfun, name);
	      }
	    अन्यथा अगर (!SSA_NAME_DEF_STMT (ssa_name (i)))
	      error ("SSA name %qE with version %d has no definition",
		     ssa_name (i), i);
	  /* No explicit virtual operands (yet).  */
	  bitmap_obstack_initialize (शून्य);
	  update_ssa (TODO_update_ssa_only_virtuals);
	  bitmap_obstack_release (शून्य);
	  /* ???  By flushing the freelist after virtual operand SSA rewrite
	     we keep the gaps available for re-use like needed for the
	     PR89595 testcase but then usually virtual operands would have
	     taken most of them.  The fix is obviously to make virtual
	     operands explicit in the SSA IL.  */
	  flush_ssaname_freelist ();
	}
      fix_loop_structure (शून्य);
    }

  अगर (cfun->curr_properties & PROP_cfg)
    {
      ENTRY_BLOCK_PTR_FOR_FN (cfun)->गिनती = entry_bb_गिनती;
      gcov_type t = param_gimple_fe_computed_hot_bb_threshold;
      set_hot_bb_threshold (t);
      update_max_bb_गिनती ();
      cgraph_गाँठ::get_create (cfun->decl);
      cgraph_edge::rebuild_edges ();
    }

  /* Perform IL validation and if any error is found abort compilation
     of this function by zapping its body.  */
  अगर ((cfun->curr_properties & PROP_cfg)
      && verify_gimple_in_cfg (cfun, false, false))
    init_empty_वृक्ष_cfg ();
  अन्यथा अगर (!(cfun->curr_properties & PROP_cfg)
	   && verify_gimple_in_seq (gimple_body (current_function_decl), false))
    gimple_set_body (current_function_decl, शून्य);

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

अटल bool
c_parser_gimple_compound_statement (gimple_parser &parser, gimple_seq *seq)
{
  bool return_p = false;

  अगर (! c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    वापस false;

  /* A compound statement starts with optional declarations.  */
  जबतक (c_parser_अग्र_tokens_start_declaration (parser))
    {
      c_parser_gimple_declaration (parser);
      अगर (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	वापस false;
    }

  जबतक (c_parser_अग्र_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      अगर (c_parser_error (parser))
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_BRACE, शून्य);
	  वापस return_p;
	}
      अन्यथा अगर (c_parser_अग्र_token_is (parser, CPP_EOF))
	{
	  c_parser_error (parser, "expected declaration or statement");
	  वापस return_p;
	}

      चयन (c_parser_peek_token (parser)->type)
	{
	हाल CPP_KEYWORD:
	  चयन (c_parser_peek_token (parser)->keyword)
	    {
	    हाल RID_AT_TRY:
	      c_parser_gimple_try_stmt (parser, seq);
	      अवरोध;
	    हाल RID_IF:
	      c_parser_gimple_if_stmt (parser, seq);
	      अवरोध;
	    हाल RID_SWITCH:
	      c_parser_gimple_switch_stmt (parser, seq);
	      अवरोध;
	    हाल RID_GOTO:
	      {
		location_t loc = c_parser_peek_token (parser)->location;
		c_parser_consume_token (parser);
		अगर (c_parser_अग्र_token_is (parser, CPP_NAME))
		  {
		    वृक्ष label = c_parser_peek_token (parser)->मूल्य;
		    c_parser_consume_token (parser);
		    c_parser_gimple_goto_stmt (parser, loc, label, seq);
		    अगर (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      वापस return_p;
		  }
		}
	      अवरोध;
	    हाल RID_RETURN:
	      return_p = true;
	      c_parser_gimple_return_stmt (parser, seq);
	      अगर (! c_parser_require (parser, CPP_SEMICOLON,
				      "expected %<;%>"))
		वापस return_p;
	      अगर (cfun->curr_properties & PROP_cfg)
		parser.धकेलो_edge (parser.current_bb->सूचकांक, EXIT_BLOCK, 0,
				  profile_probability::uninitialized ());
	      अवरोध;
	    शेष:
	      जाओ व्यंजक_stmt;
	    }
	  अवरोध;
	हाल CPP_NAME:
	  अगर (c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_gimple_label (parser, seq);
	      अवरोध;
	    }
	  अगर (c_parser_अग्र_token_is (parser, CPP_NAME)
	      && c_parser_peek_token (parser)->id_kind == C_ID_ID
	      && म_भेद (IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य),
			 "try") == 0)
	    {
	      c_parser_gimple_try_stmt (parser, seq);
	      अवरोध;
	    }
	  /* Basic block specification.
	     __BB (index, ...)  */
	  अगर ((cfun->curr_properties & PROP_cfg)
	      && !म_भेद (IDENTIFIER_POINTER
			    (c_parser_peek_token (parser)->मूल्य), "__BB"))
	    {
	      c_parser_consume_token (parser);
	      अगर (! c_parser_require (parser, CPP_OPEN_PAREN,
				      "expected %<(%>"))
		वापस return_p;
	      अगर (c_parser_अग्र_token_is_not (parser, CPP_संख्या))
		{
		  c_parser_error (parser, "expected block index");
		  वापस return_p;
		}
	      वृक्ष tnum = c_parser_peek_token (parser)->मूल्य;
	      अगर (वृक्ष_CODE (tnum) != INTEGER_CST)
		{
		  c_parser_error (parser, "expected block index");
		  वापस return_p;
		}
	      पूर्णांक सूचकांक = वृक्ष_INT_CST_निचला (tnum);
	      अगर (सूचकांक < अंक_FIXED_BLOCKS
		  || (सूचकांक < last_basic_block_for_fn (cfun)
		      && BASIC_BLOCK_FOR_FN (cfun, सूचकांक) != शून्य))
		{
		  c_parser_error (parser, "invalid block index");
		  वापस return_p;
		}
	      पूर्णांक is_loop_header_of = -1;
	      profile_गिनती bb_गिनती = profile_गिनती::uninitialized ();
	      c_parser_consume_token (parser);
	      जबतक (c_parser_अग्र_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  अगर (! c_parser_अग्र_token_is (parser, CPP_NAME))
		    {
		      c_parser_error (parser, "expected block specifier");
		      वापस return_p;
		    }
		  /* loop_header (NUM)  */
		  अगर (!म_भेद (IDENTIFIER_POINTER
			         (c_parser_peek_token (parser)->मूल्य),
			       "loop_header"))
		    {
		      c_parser_consume_token (parser);
		      अगर (! c_parser_require (parser, CPP_OPEN_PAREN,
					      "expected %<(%>"))
			वापस return_p;
		      वृक्ष loop_अंक;
		      अगर (! c_parser_अग्र_token_is (parser, CPP_संख्या)
			  || वृक्ष_CODE (loop_अंक
					  = c_parser_peek_token (parser)->मूल्य)
			       != INTEGER_CST)
			{
			  c_parser_error (parser, "expected loop number");
			  वापस return_p;
			}
		      c_parser_consume_token (parser);
		      is_loop_header_of = वृक्ष_INT_CST_निचला (loop_अंक);
		      अगर (! c_parser_require (parser, CPP_CLOSE_PAREN,
					      "expected %<)%>"))
			वापस return_p;
		    }
		  /* Parse profile: quality(value) */
		  अन्यथा
		    {
		      वृक्ष q;
		      profile_quality quality;
		      वृक्ष v = c_parser_peek_token (parser)->मूल्य;
		      अगर (!parse_profile_quality (IDENTIFIER_POINTER (v),
						  &quality))
			{
			  c_parser_error (parser, "unknown block specifier");
			  वापस false;
			}

		      c_parser_consume_token (parser);
		      अगर (!c_parser_require (parser, CPP_OPEN_PAREN,
					     "expected %<(%>"))
			वापस false;

		      अगर (!c_parser_अग्र_token_is (parser, CPP_संख्या)
			  || (वृक्ष_CODE (q = c_parser_peek_token (parser)->मूल्य)
			      != INTEGER_CST))
			{
			  c_parser_error (parser, "expected count value");
			  वापस false;
			}

		      bb_गिनती
			= profile_गिनती::from_gcov_type (वृक्ष_INT_CST_निचला (q),
							 quality);
		      c_parser_consume_token (parser);
		      अगर (! c_parser_require (parser, CPP_CLOSE_PAREN,
					      "expected %<)%>"))
			वापस return_p;
		    }
		}
	      अगर (! c_parser_require (parser, CPP_CLOSE_PAREN,
				      "expected %<)%>")
		  || ! c_parser_require (parser, CPP_COLON,
					 "expected %<:%>"))
		वापस return_p;

	      /* Put stmts parsed in the current block.  */
	      अगर (!gimple_seq_empty_p (*seq))
		{
		  अगर (!parser.current_bb)
		    c_parser_error (parser, "stmts without block");
		  अन्यथा
		    {
		      gimple_stmt_iterator gsi
			= gsi_start_bb (parser.current_bb);
		      gsi_जोड़ो_seq_after_without_update (&gsi, *seq,
							   GSI_CONTINUE_LINKING);
		    }
		  *seq = शून्य;
		}

	      /* Build an empty block with specified index, linking them
		 in source order.  */
	      basic_block bb = alloc_block ();
	      bb->सूचकांक = सूचकांक;
	      link_block (bb, (parser.current_bb ? parser.current_bb
			       : ENTRY_BLOCK_PTR_FOR_FN (cfun)));
	      अगर (basic_block_info_for_fn (cfun)->लंबाई () <= (माप_प्रकार)सूचकांक)
		vec_safe_grow_cleared (basic_block_info_for_fn (cfun),
				       सूचकांक + 1, true);
	      SET_BASIC_BLOCK_FOR_FN (cfun, सूचकांक, bb);
	      अगर (last_basic_block_for_fn (cfun) <= सूचकांक)
		last_basic_block_for_fn (cfun) = सूचकांक + 1;
	      n_basic_blocks_for_fn (cfun)++;
	      अगर (parser.current_bb->सूचकांक == ENTRY_BLOCK)
		parser.धकेलो_edge (ENTRY_BLOCK, bb->सूचकांक, EDGE_FALLTHRU,
				  profile_probability::always ());

	      /* We leave the proper setting to fixup.  */
	      श्रेणी loop *loop_father = loops_for_fn (cfun)->वृक्ष_मूल;
	      /* If the new block is a loop header, allocate a loop
		 struct.  Fixup will take care of proper placement within
		 the loop tree.  */
	      अगर (is_loop_header_of != -1)
		{
		  अगर (संख्या_of_loops (cfun) > (अचिन्हित)is_loop_header_of
		      && get_loop (cfun, is_loop_header_of) != शून्य)
		    {
		      c_parser_error (parser, "duplicate loop header");
		    }
		  अन्यथा
		    {
		      श्रेणी loop *loop = alloc_loop ();
		      loop->अंक = is_loop_header_of;
		      loop->header = bb;
		      अगर (संख्या_of_loops (cfun) <= (अचिन्हित)is_loop_header_of)
			vec_safe_grow_cleared (loops_for_fn (cfun)->larray,
					       is_loop_header_of + 1, true);
		      (*loops_for_fn (cfun)->larray)[is_loop_header_of] = loop;
		      flow_loop_वृक्ष_गाँठ_add (loops_for_fn (cfun)->वृक्ष_मूल,
					       loop);
		    }
		  loop_father = get_loop (cfun, is_loop_header_of);
		}
	      bb->loop_father = loop_father;
	      bb->गिनती = bb_गिनती;

	      /* Stmts now go to the new block.  */
	      parser.current_bb = bb;
	      अवरोध;
	    }
	  जाओ व्यंजक_stmt;

	हाल CPP_SEMICOLON:
	  {
	    /* Empty stmt.  */
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);
	    gimple *nop = gimple_build_nop ();
	    gimple_set_location (nop, loc);
	    gimple_seq_add_stmt_without_update (seq, nop);
	    अवरोध;
	  }

	हाल CPP_CLOSE_PAREN:
	हाल CPP_CLOSE_SQUARE:
	  /* Avoid infinite loop in error recovery:
	     c_parser_skip_until_found stops at a closing nesting
	     delimiter without consuming it, but here we need to consume
	     it to proceed further.  */
	  c_parser_error (parser, "expected statement");
	  c_parser_consume_token (parser);
	अवरोध;

	शेष:
व्यंजक_stmt:
	  c_parser_gimple_statement (parser, seq);
	  अगर (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	    c_parser_skip_until_found (parser, CPP_SEMICOLON, शून्य);
	}
    }
  c_parser_consume_token (parser);

  /* Put stmts parsed in the current block.  */
  अगर ((cfun->curr_properties & PROP_cfg)
      && !gimple_seq_empty_p (*seq))
    {
      अगर (!parser.current_bb)
	c_parser_error (parser, "stmts without block");
      अन्यथा
	{
	  gimple_stmt_iterator gsi = gsi_start_bb (parser.current_bb);
	  gsi_जोड़ो_seq_after_without_update (&gsi, *seq,
					       GSI_CONTINUE_LINKING);
	}
      *seq = शून्य;
    }

  वापस return_p;
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

अटल व्योम
c_parser_gimple_statement (gimple_parser &parser, gimple_seq *seq)
{
  काष्ठा c_व्यंजक lhs, rhs;
  gimple *assign = शून्य;
  location_t loc;
  वृक्ष arg = NULL_वृक्ष;
  auto_vec<वृक्ष> vargs;

  lhs = c_parser_gimple_unary_expression (parser);
  loc = व्यंजक_LOCATION (lhs.मूल्य);
  rhs.set_error ();

  /* GIMPLE call statement without LHS.  */
  अगर (c_parser_अग्र_token_is (parser, CPP_SEMICOLON)
      && वृक्ष_CODE (lhs.मूल्य) == CALL_व्यंजक)
    {
      gimple *call;
      call = gimple_build_call_from_वृक्ष (lhs.मूल्य, शून्य);
      gimple_seq_add_stmt_without_update (seq, call);
      gimple_set_location (call, loc);
      वापस;
    }

  /* All following cases are statements with LHS.  */
  अगर (! c_parser_require (parser, CPP_EQ, "expected %<=%>"))
    वापस;

  /* Eat and ignore {v} right after the =, the has_volatile_ops is
     redundant and re-computed by the operand scanner.  */
  अगर (c_parser_अग्र_token_is (parser, CPP_OPEN_BRACE)
      && !(c_parser_peek_token (parser)->flags & पूर्व_WHITE)
      && c_parser_peek_2nd_token (parser)->type == CPP_NAME
      && !(c_parser_peek_2nd_token (parser)->flags & पूर्व_WHITE)
      && म_भेद ("v", IDENTIFIER_POINTER
			(c_parser_peek_2nd_token (parser)->मूल्य)) == 0
      && c_parser_peek_nth_token (parser, 3)->type == CPP_CLOSE_BRACE
      && !(c_parser_peek_nth_token (parser, 3)->flags & पूर्व_WHITE))
    {
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }

  /* Cast expression.  */
  अगर (c_parser_अग्र_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_typename (c_parser_peek_2nd_token (parser)))
    {
      c_parser_consume_token (parser);
      काष्ठा c_type_name *type_name = c_parser_type_name (parser);
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      अगर (type_name == शून्य)
	वापस;
      /* ???  The actual type used in the cast expression is ignored as
         in GIMPLE it is encoded by the type of the LHS.  */
      rhs = c_parser_gimple_postfix_expression (parser);
      अगर (lhs.मूल्य != error_mark_गाँठ
	  && rhs.मूल्य != error_mark_गाँठ)
	{
	  क्रमागत वृक्ष_code code = NOP_व्यंजक;
	  अगर (FLOAT_TYPE_P (वृक्ष_TYPE (lhs.मूल्य))
	      && ! FLOAT_TYPE_P (वृक्ष_TYPE (rhs.मूल्य)))
	    code = FLOAT_व्यंजक;
	  अन्यथा अगर (! FLOAT_TYPE_P (वृक्ष_TYPE (lhs.मूल्य))
		   && FLOAT_TYPE_P (वृक्ष_TYPE (rhs.मूल्य)))
	    code = FIX_TRUNC_व्यंजक;
	  assign = gimple_build_assign (lhs.मूल्य, code, rhs.मूल्य);
	  gimple_seq_add_stmt_without_update (seq, assign);
	  gimple_set_location (assign, loc);
	  वापस;
	}
    }

  /* Unary expression.  */
  चयन (c_parser_peek_token (parser)->type)
    {
    हाल CPP_NAME:
      {
	वृक्ष id = c_parser_peek_token (parser)->मूल्य;
	अगर (म_भेद (IDENTIFIER_POINTER (id), "__ABS") == 0
	    || म_भेद (IDENTIFIER_POINTER (id), "__ABSU") == 0
	    || म_भेद (IDENTIFIER_POINTER (id), "__MIN") == 0
	    || म_भेद (IDENTIFIER_POINTER (id), "__MAX") == 0
	    || म_भेद (IDENTIFIER_POINTER (id), "__BIT_INSERT") == 0
	    || म_भेद (IDENTIFIER_POINTER (id), "__VEC_PERM") == 0)
	  जाओ build_unary_व्यंजक;
	अवरोध;
      }
    हाल CPP_KEYWORD:
      अगर (c_parser_peek_token (parser)->keyword != RID_REALPART
	  && c_parser_peek_token (parser)->keyword != RID_IMAGPART)
	अवरोध;
      /* Fallthru.  */
    हाल CPP_AND:
    हाल CPP_PLUS:
    हाल CPP_MINUS:
    हाल CPP_COMPL:
    हाल CPP_NOT:
    हाल CPP_MULT: /* pointer deref */
    build_unary_व्यंजक:
      rhs = c_parser_gimple_unary_expression (parser);
      अगर (rhs.मूल्य != error_mark_गाँठ)
	{
	  assign = gimple_build_assign (lhs.मूल्य, rhs.मूल्य);
	  gimple_set_location (assign, loc);
	  gimple_seq_add_stmt_without_update (seq, assign);
	}
      वापस;

    शेष:;
    }

  /* GIMPLE PHI statement.  */
  अगर (c_parser_अग्र_token_is_keyword (parser, RID_PHI))
    {
      c_parser_consume_token (parser);

      अगर (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	वापस;

      अगर (c_parser_अग्र_token_is (parser, CPP_OPEN_PAREN))
	c_parser_consume_token (parser);

      जबतक (c_parser_अग्र_token_is_not (parser, CPP_CLOSE_PAREN))
	{
	  अगर (c_parser_अग्र_token_is (parser, CPP_NAME)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      arg = c_parser_peek_token (parser)->मूल्य;
	      c_parser_consume_token (parser);
	      अगर (c_parser_अग्र_token_is (parser, CPP_COLON))
		c_parser_consume_token (parser);
	      पूर्णांक src_सूचकांक = -1;
	      अगर (!c_parser_gimple_parse_bb_spec (arg, &src_सूचकांक))
		c_parser_error (parser, "invalid source block specification");
	      vargs.safe_धकेलो (आकार_int (src_सूचकांक));
	    }
	  अन्यथा अगर (c_parser_अग्र_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  अन्यथा
	    {
	      arg = c_parser_gimple_unary_expression (parser).मूल्य;
	      vargs.safe_धकेलो (arg);
	    }
	}

      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");

      /* Build internal function for PHI.  */
      gcall *call_stmt = gimple_build_call_internal_vec (IFN_PHI, vargs);
      gimple_call_set_lhs (call_stmt, lhs.मूल्य);
      gimple_set_location (call_stmt, UNKNOWN_LOCATION);
      gimple_seq_add_stmt_without_update (seq, call_stmt);
      वापस;
    }

  /* GIMPLE call with lhs.  */
  अगर (c_parser_अग्र_token_is (parser, CPP_DOT)
      || (c_parser_अग्र_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN
	  && lookup_name (c_parser_peek_token (parser)->मूल्य)))
    {
      rhs = c_parser_gimple_unary_expression (parser);
      अगर (rhs.मूल्य != error_mark_गाँठ)
	{
	  gimple *call = gimple_build_call_from_वृक्ष (rhs.मूल्य, शून्य);
	  gimple_call_set_lhs (call, lhs.मूल्य);
	  gimple_seq_add_stmt_without_update (seq, call);
	  gimple_set_location (call, loc);
	}
      वापस;
    }

  rhs = c_parser_gimple_द्विआधारी_expression (parser, वृक्ष_TYPE (lhs.मूल्य));
  अगर (lhs.मूल्य != error_mark_गाँठ
      && rhs.मूल्य != error_mark_गाँठ)
    {
      /* If we parsed an identifier and the next token  is a '?' then parse
	 a conditional expression.  */
      अगर (SSA_VAR_P (rhs.मूल्य) && c_parser_अग्र_token_is (parser, CPP_QUERY))
	{
	  काष्ठा c_व्यंजक trueval, falseval;
	  c_parser_consume_token (parser);
	  trueval = c_parser_gimple_postfix_expression (parser);
	  falseval.set_error ();
	  अगर (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    falseval = c_parser_gimple_postfix_expression (parser);
	  अगर (trueval.मूल्य == error_mark_गाँठ
	      || falseval.मूल्य == error_mark_गाँठ)
	    वापस;
	  rhs.मूल्य = build3_loc (loc,
				  VECTOR_TYPE_P (वृक्ष_TYPE (rhs.मूल्य))
				  ? VEC_COND_व्यंजक : COND_व्यंजक,
				  वृक्ष_TYPE (trueval.मूल्य),
				  rhs.मूल्य, trueval.मूल्य, falseval.मूल्य);
	}
      अगर (get_gimple_rhs_class (वृक्ष_CODE (rhs.मूल्य)) == GIMPLE_INVALID_RHS)
	{
	  c_parser_error (parser, "unexpected RHS for assignment");
	  वापस;
	}
      assign = gimple_build_assign (lhs.मूल्य, rhs.मूल्य);
      gimple_seq_add_stmt_without_update (seq, assign);
      gimple_set_location (assign, loc);
    }
  वापस;
}

/* A mapping between an identifier to a tree code for binary operations. */
अटल स्थिर std::pair<स्थिर अक्षर *, वृक्ष_code> gimple_द्विआधारी_identifier_code[] =
  {
    {"__MULT_HIGHPART", MULT_HIGHPART_व्यंजक},
    {"__UNLT", UNLT_व्यंजक},
    {"__UNLE", UNLE_व्यंजक},
    {"__UNGT", UNGT_व्यंजक},
    {"__UNGE", UNGE_व्यंजक},
    {"__UNEQ", UNEQ_व्यंजक},
    {"__UNORDERED", UNORDERED_व्यंजक},
    {"__ORDERED", ORDERED_व्यंजक},
    {"__LTGT", LTGT_व्यंजक},
    {"__FLOOR_DIV", FLOOR_DIV_व्यंजक},
    {"__ROUND_DIV", ROUND_DIV_व्यंजक},
    {"__EXACT_DIV", EXACT_DIV_व्यंजक},
    {"__CEIL_DIV", CEIL_DIV_व्यंजक},
    {"__FLOOR_MOD", FLOOR_MOD_व्यंजक},
    {"__ROUND_MOD", ROUND_MOD_व्यंजक},
    {"__CEIL_MOD", CEIL_MOD_व्यंजक},
    {"__ROTATE_LEFT", LROTATE_व्यंजक},
    {"__ROTATE_RIGHT", RROTATE_व्यंजक},
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

अटल c_व्यंजक
c_parser_gimple_द्विआधारी_expression (gimple_parser &parser, वृक्ष ret_type)
{
  /* Location of the binary operator.  */
  काष्ठा c_व्यंजक ret, lhs, rhs;
  क्रमागत वृक्ष_code code = ERROR_MARK;
  ret.set_error ();
  lhs = c_parser_gimple_postfix_expression (parser, ret_type);
  अगर (c_parser_error (parser))
    वापस ret;
  चयन (c_parser_peek_token (parser)->type)
    {
    हाल CPP_MULT:
      code = MULT_व्यंजक;
      अवरोध;
    हाल CPP_DIV:
      code = TRUNC_DIV_व्यंजक;
      अवरोध;
    हाल CPP_MOD:
      code = TRUNC_MOD_व्यंजक;
      अवरोध;
    हाल CPP_PLUS:
      अगर (POINTER_TYPE_P (वृक्ष_TYPE (lhs.मूल्य)))
	code = POINTER_PLUS_व्यंजक;
      अन्यथा
	code = PLUS_व्यंजक;
      अवरोध;
    हाल CPP_MINUS:
      अगर (POINTER_TYPE_P (वृक्ष_TYPE (lhs.मूल्य)))
	code = POINTER_DIFF_व्यंजक;
      अन्यथा
	code = MINUS_व्यंजक;
      अवरोध;
    हाल CPP_LSHIFT:
      code = LSHIFT_व्यंजक;
      अवरोध;
    हाल CPP_RSHIFT:
      code = RSHIFT_व्यंजक;
      अवरोध;
    हाल CPP_LESS:
      code = LT_व्यंजक;
      अवरोध;
    हाल CPP_GREATER:
      code = GT_व्यंजक;
      अवरोध;
    हाल CPP_LESS_EQ:
      code = LE_व्यंजक;
      अवरोध;
    हाल CPP_GREATER_EQ:
      code = GE_व्यंजक;
      अवरोध;
    हाल CPP_EQ_EQ:
      code = EQ_व्यंजक;
      अवरोध;
    हाल CPP_NOT_EQ:
      code = NE_व्यंजक;
      अवरोध;
    हाल CPP_AND:
      code = BIT_AND_व्यंजक;
      अवरोध;
    हाल CPP_XOR:
      code = BIT_XOR_व्यंजक;
      अवरोध;
    हाल CPP_OR:
      code = BIT_IOR_व्यंजक;
      अवरोध;
    हाल CPP_AND_AND:
      c_parser_error (parser, "%<&&%> not valid in GIMPLE");
      वापस ret;
    हाल CPP_OR_OR:
      c_parser_error (parser, "%<||%> not valid in GIMPLE");
      वापस ret;
    हाल CPP_NAME:
      {
	वृक्ष id = c_parser_peek_token (parser)->मूल्य;
	क्रम (स्वतः &p : gimple_द्विआधारी_identifier_code)
	  {
	    अगर (म_भेद (IDENTIFIER_POINTER (id), p.first) == 0)
	      {
		code = p.second;
		अवरोध;
	      }
	  }
	अगर (code != ERROR_MARK)
	  अवरोध;
      }
      /* Fallthru.  */
    शेष:
      /* Not a binary expression.  */
      वापस lhs;
    }
  location_t ret_loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  rhs = c_parser_gimple_postfix_expression (parser);
  अगर (lhs.मूल्य != error_mark_गाँठ && rhs.मूल्य != error_mark_गाँठ)
    ret.मूल्य = build2_loc (ret_loc, code, ret_type, lhs.मूल्य, rhs.मूल्य);
  वापस ret;
}

/* Parse a gimple parentized binary expression.  */

अटल c_व्यंजक
c_parser_gimple_parentized_द्विआधारी_expression (gimple_parser &parser,
					      location_t op_loc,
					      वृक्ष_code code)
{
  काष्ठा c_व्यंजक ret;
  ret.set_error ();

  c_parser_consume_token (parser);
  अगर (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    वापस ret;
  c_व्यंजक op1 = c_parser_gimple_postfix_expression (parser);
  अगर (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    वापस ret;
  c_व्यंजक op2 = c_parser_gimple_postfix_expression (parser);
  अगर (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    वापस ret;

  अगर (op1.मूल्य != error_mark_गाँठ && op2.मूल्य != error_mark_गाँठ)
    ret.मूल्य = build2_loc (op_loc,
			    code, वृक्ष_TYPE (op1.मूल्य), op1.मूल्य, op2.मूल्य);
  वापस ret;
}

/* Parse a gimple parentized binary expression.  */

अटल c_व्यंजक
c_parser_gimple_parentized_ternary_expression (gimple_parser &parser,
					       location_t op_loc,
					       वृक्ष_code code)
{
  काष्ठा c_व्यंजक ret;
  ret.set_error ();

  c_parser_consume_token (parser);
  अगर (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    वापस ret;
  c_व्यंजक op1 = c_parser_gimple_postfix_expression (parser);
  अगर (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    वापस ret;
  c_व्यंजक op2 = c_parser_gimple_postfix_expression (parser);
  अगर (!c_parser_require (parser, CPP_COMMA, "expected %<)%>"))
    वापस ret;
  c_व्यंजक op3 = c_parser_gimple_postfix_expression (parser);
  अगर (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    वापस ret;

  अगर (op1.मूल्य != error_mark_गाँठ
      && op2.मूल्य != error_mark_गाँठ
      && op3.मूल्य != error_mark_गाँठ)
    ret.मूल्य = build3_loc (op_loc,
			    code, वृक्ष_TYPE (op1.मूल्य),
			    op1.मूल्य, op2.मूल्य, op3.मूल्य);
  वापस ret;
}

/* Parse gimple unary expression.

   gimple-unary-expression:
     gimple-postfix-expression
     unary-operator gimple-postfix-expression

   unary-operator: one of
     & * + - ~ abs_expr
*/

अटल c_व्यंजक
c_parser_gimple_unary_expression (gimple_parser &parser)
{
  काष्ठा c_व्यंजक ret, op;
  location_t op_loc = c_parser_peek_token (parser)->location;
  location_t finish;
  ret.set_error ();
  चयन (c_parser_peek_token (parser)->type)
    {
    हाल CPP_AND:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      mark_exp_read (op.मूल्य);
      वापस gimple_parser_build_unary_op (op_loc, ADDR_व्यंजक, op);
    हाल CPP_MULT:
      {
	c_parser_consume_token (parser);
	op = c_parser_gimple_postfix_expression (parser);
	अगर (op.मूल्य == error_mark_गाँठ)
	  वापस ret;
	अगर (! POINTER_TYPE_P (वृक्ष_TYPE (op.मूल्य)))
	  {
	    error_at (op_loc, "expected pointer as argument of unary %<*%>");
	    वापस ret;
	  }
	finish = op.get_finish ();
	location_t combined_loc = make_location (op_loc, op_loc, finish);
	ret.मूल्य = build_simple_mem_ref_loc (combined_loc, op.मूल्य);
	वृक्ष_SIDE_EFFECTS (ret.मूल्य)
	  = वृक्ष_THIS_VOLATILE (ret.मूल्य)
	  = TYPE_VOLATILE (वृक्ष_TYPE (वृक्ष_TYPE (op.मूल्य)));
	ret.src_range.m_start = op_loc;
	ret.src_range.m_finish = finish;
	वापस ret;
      }
    हाल CPP_PLUS:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      वापस gimple_parser_build_unary_op (op_loc, CONVERT_व्यंजक, op);
    हाल CPP_MINUS:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      वापस gimple_parser_build_unary_op (op_loc, NEGATE_व्यंजक, op);
    हाल CPP_COMPL:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      वापस gimple_parser_build_unary_op (op_loc, BIT_NOT_व्यंजक, op);
    हाल CPP_NOT:
      c_parser_error (parser, "%<!%> not valid in GIMPLE");
      वापस ret;
    हाल CPP_KEYWORD:
      चयन (c_parser_peek_token (parser)->keyword)
	{
	हाल RID_REALPART:
	  c_parser_consume_token (parser);
	  op = c_parser_gimple_postfix_expression (parser);
	  वापस gimple_parser_build_unary_op (op_loc, REALPART_व्यंजक, op);
	हाल RID_IMAGPART:
	  c_parser_consume_token (parser);
	  op = c_parser_gimple_postfix_expression (parser);
	  वापस gimple_parser_build_unary_op (op_loc, IMAGPART_व्यंजक, op);
	शेष:
	  वापस c_parser_gimple_postfix_expression (parser);
	}
    हाल CPP_NAME:
	{
	  वृक्ष id = c_parser_peek_token (parser)->मूल्य;
	  अगर (म_भेद (IDENTIFIER_POINTER (id), "__ABS") == 0)
	    {
	      c_parser_consume_token (parser);
	      op = c_parser_gimple_postfix_expression (parser);
	      वापस gimple_parser_build_unary_op (op_loc, ABS_व्यंजक, op);
	    }
	  अन्यथा अगर (म_भेद (IDENTIFIER_POINTER (id), "__ABSU") == 0)
	    {
	      c_parser_consume_token (parser);
	      op = c_parser_gimple_postfix_expression (parser);
	      वापस gimple_parser_build_unary_op (op_loc, ABSU_व्यंजक, op);
	    }
	  अन्यथा अगर (म_भेद (IDENTIFIER_POINTER (id), "__MIN") == 0)
	    वापस c_parser_gimple_parentized_द्विआधारी_expression (parser,
								 op_loc,
								 MIN_व्यंजक);
	  अन्यथा अगर (म_भेद (IDENTIFIER_POINTER (id), "__MAX") == 0)
	    वापस c_parser_gimple_parentized_द्विआधारी_expression (parser,
								 op_loc,
								 MAX_व्यंजक);
	  अन्यथा अगर (म_भेद (IDENTIFIER_POINTER (id), "__VEC_PERM") == 0)
	    वापस c_parser_gimple_parentized_ternary_expression
			(parser, op_loc, VEC_PERM_व्यंजक);
	  अन्यथा अगर (म_भेद (IDENTIFIER_POINTER (id), "__BIT_INSERT") == 0)
	    {
	      /* __BIT_INSERT '(' postfix-expression, postfix-expression,
			          integer ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      अगर (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_व्यंजक op0 = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_व्यंजक op1 = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_व्यंजक op2 = c_parser_gimple_postfix_expression (parser);
		  अगर (वृक्ष_CODE (op2.मूल्य) != INTEGER_CST
		      || !int_fits_type_p (op2.मूल्य, bitsizetype))
		    c_parser_error (parser, "expected constant offset");
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  अगर (op0.मूल्य != error_mark_गाँठ
		      && op1.मूल्य != error_mark_गाँठ
		      && वृक्ष_CODE (op2.मूल्य) == INTEGER_CST)
		    ret.मूल्य = build3_loc (loc, BIT_जोड़ो_व्यंजक,
					    वृक्ष_TYPE (op0.मूल्य),
					    op0.मूल्य, op1.मूल्य,
					    fold_convert (bitsizetype,
							  op2.मूल्य));
		}
	      वापस ret;
	    }
	  अन्यथा
	    वापस c_parser_gimple_postfix_expression (parser);
	}
    शेष:
      वापस c_parser_gimple_postfix_expression (parser);
    }
}

/* Decompose ID into base name (ID until ver_offset) and VERSION.  Return
   true if ID matches a SSA name.  */

अटल bool
c_parser_parse_ssa_name_id (वृक्ष id, अचिन्हित *version, अचिन्हित *ver_offset)
{
  स्थिर अक्षर *token = IDENTIFIER_POINTER (id);
  स्थिर अक्षर *var_version = म_खोजप (token, '_');
  अगर (! var_version)
    वापस false;

  *ver_offset = var_version - token;
  क्रम (स्थिर अक्षर *p = var_version + 1; *p; ++p)
    अगर (! ISDIGIT (*p))
      वापस false;
  *version = म_से_प (var_version + 1);
  वापस *version > 0;
}

/* Get at the actual SSA name ID with VERSION starting at VER_OFFSET.
   TYPE is the type if the SSA name is being declared.  */

अटल वृक्ष
c_parser_parse_ssa_name (gimple_parser &parser,
			 वृक्ष id, वृक्ष type, अचिन्हित version,
			 अचिन्हित ver_offset)
{
  वृक्ष name = NULL_वृक्ष;
  स्थिर अक्षर *token = IDENTIFIER_POINTER (id);

  अगर (ver_offset == 0)
    {
      /* Anonymous unnamed SSA name.  */
      अगर (version < अंक_ssa_names)
	name = ssa_name (version);
      अगर (! name)
	{
	  अगर (! type)
	    {
	      c_parser_error (parser, "SSA name undeclared");
	      वापस error_mark_गाँठ;
	    }
	  name = make_ssa_name_fn (cfun, type, शून्य, version);
	}
    }
  अन्यथा
    {
      अगर (version < अंक_ssa_names)
	name = ssa_name (version);
      अगर (! name)
	{
	  /* Separate var name from version.  */
	  अक्षर *var_name = XNEWVEC (अक्षर, ver_offset + 1);
	  स_नकल (var_name, token, ver_offset);
	  var_name[ver_offset] = '\0';
	  /* lookup for parent decl.  */
	  id = get_identifier (var_name);
	  वृक्ष parent = lookup_name (id);
	  XDELETEVEC (var_name);
	  अगर (! parent || parent == error_mark_गाँठ)
	    {
	      c_parser_error (parser, "base variable or SSA name undeclared");
	      वापस error_mark_गाँठ;
	    }
	  अगर (!(VAR_P (parent)
		|| वृक्ष_CODE (parent) == PARM_DECL
		|| वृक्ष_CODE (parent) == परिणाम_DECL))
	    {
	      error ("invalid base %qE for SSA name", parent);
	      वापस error_mark_गाँठ;
	    }
	  name = make_ssa_name_fn (cfun, parent,
				   gimple_build_nop (), version);
	}
    }

  वापस name;
}

/* Parse a gimple call to an internal function.

   gimple-call-internal:
     . identifier ( gimple-argument-expression-list[opt] )  */

अटल काष्ठा c_व्यंजक
c_parser_gimple_call_internal (gimple_parser &parser)
{
  काष्ठा c_व्यंजक व्यंजक;
  व्यंजक.set_error ();

  gcc_assert (c_parser_अग्र_token_is (parser, CPP_DOT));
  c_parser_consume_token (parser);
  location_t loc = c_parser_peek_token (parser)->location;
  अगर (!c_parser_अग्र_token_is (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_kind != C_ID_ID)
    {
      c_parser_error (parser, "expecting internal function name");
      वापस व्यंजक;
    }
  वृक्ष id = c_parser_peek_token (parser)->मूल्य;
  internal_fn ifn = lookup_internal_fn (IDENTIFIER_POINTER (id));
  c_parser_consume_token (parser);
  अगर (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    {
      auto_vec<वृक्ष> exprlist;
      अगर (!c_parser_अग्र_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_gimple_व्यंजक_list (parser, &exprlist);
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      अगर (ifn == IFN_LAST)
	error_at (loc, "unknown internal function %qE", id);
      अन्यथा
	{
	  व्यंजक.मूल्य = build_call_व्यंजक_internal_loc_array
	    (loc, ifn, void_type_गाँठ, exprlist.लंबाई (),
	     exprlist.address ());
	  व्यंजक.original_code = ERROR_MARK;
	  व्यंजक.original_type = शून्य;
	  व्यंजक.m_decimal = 0;
	}
    }
  वापस व्यंजक;
}

/* Parse '<' type [',' alignment] '>' and return a type on success
   and NULL_TREE on error.  */

अटल वृक्ष
c_parser_gimple_typespec (gimple_parser &parser)
{
  काष्ठा c_type_name *type_name = शून्य;
  वृक्ष alignment = NULL_वृक्ष;
  अगर (c_parser_require (parser, CPP_LESS, "expected %<<%>"))
    {
      type_name = c_parser_type_name (parser);
      /* Optional alignment.  */
      अगर (c_parser_अग्र_token_is (parser, CPP_COMMA))
	{
	  c_parser_consume_token (parser);
	  alignment
	      = c_parser_gimple_postfix_expression (parser).मूल्य;
	}
      c_parser_skip_until_found (parser,
				 CPP_GREATER, "expected %<>%>");
    }
  अगर (!type_name)
    वापस NULL_वृक्ष;
  वृक्ष tem;
  वृक्ष type = groktypename (type_name, &tem, शून्य);
  अगर (alignment)
    type = build_aligned_type (type, वृक्ष_to_uhwi (alignment));
  वापस type;
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

अटल काष्ठा c_व्यंजक
c_parser_gimple_postfix_expression (gimple_parser &parser, वृक्ष ret_type)
{
  location_t loc = c_parser_peek_token (parser)->location;
  source_range tok_range = c_parser_peek_token (parser)->get_range ();
  काष्ठा c_व्यंजक व्यंजक;
  व्यंजक.set_error ();
  चयन (c_parser_peek_token (parser)->type)
    {
    हाल CPP_संख्या:
      व्यंजक.मूल्य = c_parser_peek_token (parser)->मूल्य;
      set_c_व्यंजक_source_range (&व्यंजक, tok_range);
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      अवरोध;
    हाल CPP_CHAR:
    हाल CPP_CHAR16:
    हाल CPP_CHAR32:
    हाल CPP_UTF8CHAR:
    हाल CPP_WCHAR:
      व्यंजक.मूल्य = c_parser_peek_token (parser)->मूल्य;
      set_c_व्यंजक_source_range (&व्यंजक, tok_range);
      c_parser_consume_token (parser);
      अवरोध;
    हाल CPP_STRING:
    हाल CPP_STRING16:
    हाल CPP_STRING32:
    हाल CPP_WSTRING:
    हाल CPP_UTF8STRING:
      व्यंजक = c_parser_string_literal (parser, false, true);
      अवरोध;
    हाल CPP_DOT:
      व्यंजक = c_parser_gimple_call_internal (parser);
      अवरोध;
    हाल CPP_NAME:
      अगर (c_parser_peek_token (parser)->id_kind == C_ID_ID)
	{
	  वृक्ष id = c_parser_peek_token (parser)->मूल्य;
	  अगर (म_भेद (IDENTIFIER_POINTER (id), "__MEM") == 0)
	    {
	      /* __MEM '<' type-name [ ',' number ] '>'
	               '(' [ '(' type-name ')' ] unary-expression
			   [ '+' number ]
			   [ ',' number ]
			   [ ',' number ':' number ] ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      वृक्ष type = c_parser_gimple_typespec (parser);
	      काष्ठा c_व्यंजक ptr, alias_off, step, सूचकांक, index2;
	      ptr.मूल्य = error_mark_गाँठ;
	      alias_off.मूल्य = NULL_वृक्ष;
	      step.मूल्य = NULL_वृक्ष;
	      सूचकांक.मूल्य = NULL_वृक्ष;
	      index2.मूल्य = NULL_वृक्ष;
	      अचिन्हित लघु clique = 0;
	      अचिन्हित लघु base = 0;
	      bool reverse_order = false;
	      काष्ठा c_व्यंजक ro;
	      अगर (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  वृक्ष alias_type = NULL_वृक्ष;
		  /* Optional alias-type cast.  */
		  अगर (c_parser_अग्र_token_is (parser, CPP_OPEN_PAREN))
		    {
		      c_parser_consume_token (parser);
		      काष्ठा c_type_name *alias_type_name
			= c_parser_type_name (parser);
		      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
						 "expected %<)%>");
		      अगर (alias_type_name)
			{
			  वृक्ष tem;
			  alias_type = groktypename (alias_type_name,
						     &tem, शून्य);
			}
		    }
		  ptr = c_parser_gimple_unary_expression (parser);
		  अगर (ptr.मूल्य == error_mark_गाँठ
		      || ! POINTER_TYPE_P (वृक्ष_TYPE (ptr.मूल्य)))
		    {
		      अगर (ptr.मूल्य != error_mark_गाँठ)
			error_at (ptr.get_start (),
				  "invalid type of %<__MEM%> operand");
		      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
						 "expected %<)%>");
		      वापस व्यंजक;
		    }
		  अगर (! alias_type)
		    alias_type = वृक्ष_TYPE (ptr.मूल्य);
		  /* Optional constant offset.  */
		  अगर (c_parser_अग्र_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      alias_off = c_parser_gimple_postfix_expression (parser);
		    }
		  अगर (c_parser_अग्र_token_is (parser, CPP_MULT))
		    {
		      std::swap (सूचकांक, alias_off);
		      c_parser_consume_token (parser);
		      step = c_parser_gimple_postfix_expression (parser);
		    }
		  अन्यथा अगर (c_parser_अग्र_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      सूचकांक = c_parser_gimple_postfix_expression (parser);
		      अगर (c_parser_अग्र_token_is (parser, CPP_MULT))
			{
			  c_parser_consume_token (parser);
			  step = c_parser_gimple_postfix_expression (parser);
			}
		      अन्यथा
			std::swap (सूचकांक, index2);
		    }
		  अन्यथा अगर (alias_off.मूल्य
			   && वृक्ष_CODE (alias_off.मूल्य) != INTEGER_CST)
		    std::swap (alias_off, index2);
		  अगर (c_parser_अग्र_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      index2 = c_parser_gimple_postfix_expression (parser);
		    }
		  अगर (alias_off.मूल्य)
		    {
		      अगर (वृक्ष_CODE (alias_off.मूल्य) != INTEGER_CST)
			error_at (alias_off.get_start (),
				  "expected constant offset for %<__MEM%> "
				  "operand");
		      alias_off.मूल्य = fold_convert (alias_type,
						      alias_off.मूल्य);
		    }
		  अन्यथा
		    alias_off.मूल्य = build_int_cst (alias_type, 0);
		  अगर (step.मूल्य)
		    {
		      अगर (वृक्ष_CODE (step.मूल्य) != INTEGER_CST)
			error_at (step.get_start (),
				  "expected constant step for %<__MEM%> "
				  "operand");
		    }
		  अगर (c_parser_अग्र_token_is (parser, CPP_COMMA))
		    {
		      काष्ठा c_व्यंजक cl, ba;
		      bool has_clb = true;
		      c_parser_consume_token (parser);
		      cl = c_parser_gimple_postfix_expression (parser);
		      अगर (!c_parser_अग्र_token_is (parser, CPP_COLON))
			{
			  ro = cl;
			  अचिन्हित HOST_WIDE_INT tmp = 0;
			  अगर (!वृक्ष_fits_uhwi_p (ro.मूल्य)
			      || (tmp = वृक्ष_to_uhwi (ro.मूल्य)) > 1)
			    error_at (ro.get_start (),
				      "invalid reverse order value");
			  reverse_order = tmp;
			  has_clb = false;
			  अगर (c_parser_अग्र_token_is (parser, CPP_COMMA))
			    {
			      c_parser_consume_token (parser);
			      cl = c_parser_gimple_postfix_expression (parser);
		              has_clb = true;
			    }
			}
		      अगर (has_clb
			  && c_parser_require (parser,
					       CPP_COLON, "expected %<:%>"))
			{
			  ba = c_parser_gimple_postfix_expression (parser);
			  अगर (!वृक्ष_fits_uhwi_p (cl.मूल्य)
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
	      अगर (! type || c_parser_error (parser))
		{
		  c_parser_set_error (parser, false);
		  वापस व्यंजक;
		}
	      अगर (सूचकांक.मूल्य || step.मूल्य || index2.मूल्य)
		व्यंजक.मूल्य = build5_loc (loc, TARGET_MEM_REF,
					 type, ptr.मूल्य, alias_off.मूल्य,
					 सूचकांक.मूल्य, step.मूल्य, index2.मूल्य);
	      अन्यथा
		व्यंजक.मूल्य = build2_loc (loc, MEM_REF,
					 type, ptr.मूल्य, alias_off.मूल्य);
	      अगर (clique != 0)
		{
		  cfun->last_clique = MAX (cfun->last_clique, clique);
		  MR_DEPENDENCE_CLIQUE (व्यंजक.मूल्य) = clique;
		  MR_DEPENDENCE_BASE (व्यंजक.मूल्य) = base;
		}
	      अगर (reverse_order)
		{
		  अगर (वृक्ष_CODE (व्यंजक.मूल्य) == MEM_REF)
		    REF_REVERSE_STORAGE_ORDER (व्यंजक.मूल्य) = reverse_order;
		  अन्यथा
		    error_at (ro.get_start (),
			      "target mem ref cannot have reverse order");
		}
	      अवरोध;
	    }
	  अन्यथा अगर (म_भेद (IDENTIFIER_POINTER (id), "__VIEW_CONVERT") == 0)
	    {
	      /* __VIEW_CONVERT '<' type-name [ ',' number ] '>'
	                        '(' postfix-expression ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      वृक्ष type = c_parser_gimple_typespec (parser);
	      अगर (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_व्यंजक op = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  अगर (type && op.मूल्य != error_mark_गाँठ)
		    व्यंजक.मूल्य = build1_loc (loc, VIEW_CONVERT_व्यंजक,
					     type, op.मूल्य);
		}
	      अवरोध;
	    }
	  अन्यथा अगर (म_भेद (IDENTIFIER_POINTER (id), "__BIT_FIELD_REF") == 0)
	    {
	      /* __BIT_FIELD_REF '<' type-name [ ',' number ] '>'
	                        '(' postfix-expression, integer, integer ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      वृक्ष type = c_parser_gimple_typespec (parser);
	      अगर (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_व्यंजक op0 = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_व्यंजक op1 = c_parser_gimple_postfix_expression (parser);
		  अगर (वृक्ष_CODE (op1.मूल्य) != INTEGER_CST
		      || !int_fits_type_p (op1.मूल्य, bitsizetype))
		    c_parser_error (parser, "expected constant size");
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_व्यंजक op2 = c_parser_gimple_postfix_expression (parser);
		  अगर (वृक्ष_CODE (op2.मूल्य) != INTEGER_CST
		      || !int_fits_type_p (op2.मूल्य, bitsizetype))
		    c_parser_error (parser, "expected constant offset");
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  अगर (type
		      && op0.मूल्य != error_mark_गाँठ
		      && वृक्ष_CODE (op1.मूल्य) == INTEGER_CST
		      && वृक्ष_CODE (op2.मूल्य) == INTEGER_CST)
		    व्यंजक.मूल्य = build3_loc (loc, BIT_FIELD_REF, type,
					     op0.मूल्य,
					     fold_convert (bitsizetype,
							   op1.मूल्य),
					     fold_convert (bitsizetype,
							   op2.मूल्य));
		}
	      अवरोध;
	    }
	  अन्यथा अगर (म_भेद (IDENTIFIER_POINTER (id), "__CLOBBER") == 0)
	    {
	      /* __CLOBBER [ '(' bob | eob | bos | eos ')' ]  */
	      clobber_kind kind = CLOBBER_UNDEF;
	      c_parser_consume_token (parser);
	      अगर (c_parser_अग्र_token_is (parser, CPP_OPEN_PAREN))
		{
		  c_parser_consume_token (parser);
		  स्वतः tok = c_parser_peek_token (parser);
		  अगर (c_parser_require (parser, CPP_NAME,
					"expected clobber kind"))
		    {
		      स्थिर अक्षर *kind_str = IDENTIFIER_POINTER (tok->मूल्य);
		      अगर (म_भेद (kind_str, "bos") == 0)
			kind = CLOBBER_STORAGE_BEGIN;
		      अन्यथा अगर (म_भेद (kind_str, "bob") == 0)
			kind = CLOBBER_OBJECT_BEGIN;
		      अन्यथा अगर (म_भेद (kind_str, "eob") == 0)
			kind = CLOBBER_OBJECT_END;
		      अन्यथा अगर (म_भेद (kind_str, "eos") == 0)
			kind = CLOBBER_STORAGE_END;
		      अन्यथा
			c_parser_error (parser, "expected one of %<bos%>, "
					"%<eos%>, %<bob>, %<eob%>");
		    }
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      /* We infer the (redundant) type from the LHS.  */
	      व्यंजक.मूल्य = build_clobber (ret_type, kind);
	      अवरोध;
	    }
	  अन्यथा अगर (म_भेद (IDENTIFIER_POINTER (id), "_Literal") == 0)
	    {
	      /* _Literal '(' type-name ')' ( [ '-' ] constant | constructor ) */
	      c_parser_consume_token (parser);
	      वृक्ष type = NULL_वृक्ष;
	      अगर (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  काष्ठा c_type_name *type_name = c_parser_type_name (parser);
		  वृक्ष tem;
		  अगर (type_name)
		    type = groktypename (type_name, &tem, शून्य);
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      अगर (! type)
		{
		  c_parser_error (parser, "invalid _Literal");
		  वापस व्यंजक;
		}
	      अगर (c_parser_अग्र_token_is (parser, CPP_OPEN_BRACE))
		{
		  c_parser_consume_token (parser);
		  अगर (!AGGREGATE_TYPE_P (type)
		      && !VECTOR_TYPE_P (type))
		    {
		      c_parser_error (parser, "invalid type for _Literal with "
				      "constructor");
		      c_parser_skip_until_found (parser, CPP_CLOSE_BRACE,
						 "expected %<}%>");
		      वापस व्यंजक;
		    }
		  vec<constructor_elt, va_gc> *v = शून्य;
		  bool constant_p = true;
		  अगर (VECTOR_TYPE_P (type)
		      && !c_parser_अग्र_token_is (parser, CPP_CLOSE_BRACE))
		    {
		      vec_alloc (v, TYPE_VECTOR_SUBPARTS (type).to_constant ());
		      करो
			{
			  वृक्ष val
			    = c_parser_gimple_postfix_expression (parser).मूल्य;
			  अगर (! val
			      || val == error_mark_गाँठ
			      || (! CONSTANT_CLASS_P (val)
				  && ! SSA_VAR_P (val)))
			    {
			      c_parser_error (parser, "invalid _Literal");
			      वापस व्यंजक;
			    }
			  CONSTRUCTOR_APPEND_ELT (v, NULL_वृक्ष, val);
			  अगर (! CONSTANT_CLASS_P (val))
			    constant_p = false;
			  अगर (c_parser_अग्र_token_is (parser, CPP_COMMA))
			    c_parser_consume_token (parser);
			  अन्यथा
			    अवरोध;
			}
		      जबतक (1);
		    }
		  अगर (c_parser_require (parser, CPP_CLOSE_BRACE,
					"expected %<}%>"))
		    {
		      अगर (v && constant_p)
			व्यंजक.मूल्य = build_vector_from_ctor (type, v);
		      अन्यथा
			व्यंजक.मूल्य = build_constructor (type, v);
		    }
		  अन्यथा
		    {
		      c_parser_skip_until_found (parser, CPP_CLOSE_BRACE,
						 "expected %<}%>");
		      वापस व्यंजक;
		    }
		}
	      अन्यथा
		{
		  bool neg_p, addr_p;
		  अगर ((neg_p = c_parser_अग्र_token_is (parser, CPP_MINUS)))
		    c_parser_consume_token (parser);
		  अगर ((addr_p = c_parser_अग्र_token_is (parser, CPP_AND)))
		    c_parser_consume_token (parser);
		  वृक्ष val = c_parser_gimple_postfix_expression (parser).मूल्य;
		  अगर (! val
		      || val == error_mark_गाँठ
		      || (!CONSTANT_CLASS_P (val) && !addr_p))
		    {
		      c_parser_error (parser, "invalid _Literal");
		      वापस व्यंजक;
		    }
		  अगर (addr_p)
		    {
		      val = build1 (ADDR_व्यंजक, type, val);
		      अगर (!is_gimple_invariant_address (val))
			{
			  c_parser_error (parser, "invalid _Literal");
			  वापस व्यंजक;
			}
		    }
		  अगर (neg_p)
		    {
		      val = const_unop (NEGATE_व्यंजक, वृक्ष_TYPE (val), val);
		      अगर (! val)
			{
			  c_parser_error (parser, "invalid _Literal");
			  वापस व्यंजक;
			}
		    }
		  व्यंजक.मूल्य = fold_convert (type, val);
		}
	      वापस व्यंजक;
	    }

	  /* SSA name.  */
	  अचिन्हित version, ver_offset;
	  अगर (! lookup_name (id)
	      && c_parser_parse_ssa_name_id (id, &version, &ver_offset))
	    {
	      c_parser_consume_token (parser);
	      व्यंजक.मूल्य = c_parser_parse_ssa_name (parser, id, NULL_वृक्ष,
						    version, ver_offset);
	      अगर (व्यंजक.मूल्य == error_mark_गाँठ)
		वापस व्यंजक;
	      set_c_व्यंजक_source_range (&व्यंजक, tok_range);
	      /* For default definition SSA names.  */
	      अगर (c_parser_अग्र_token_is (parser, CPP_OPEN_PAREN)
		  && c_parser_peek_2nd_token (parser)->type == CPP_NAME
		  && म_भेद ("D",
			     IDENTIFIER_POINTER
			       (c_parser_peek_2nd_token (parser)->मूल्य)) == 0
		  && c_parser_peek_nth_token (parser, 3)->type == CPP_CLOSE_PAREN)
		{
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		  अगर (! SSA_NAME_IS_DEFAULT_DEF (व्यंजक.मूल्य))
		    {
		      अगर (!SSA_NAME_VAR (व्यंजक.मूल्य))
			{
			  error_at (loc, "anonymous SSA name cannot have"
				    " default definition");
			  व्यंजक.मूल्य = error_mark_गाँठ;
			  वापस व्यंजक;
			}
		      set_ssa_default_def (cfun, SSA_NAME_VAR (व्यंजक.मूल्य),
					   व्यंजक.मूल्य);
		      SSA_NAME_DEF_STMT (व्यंजक.मूल्य) = gimple_build_nop ();
		    }
		}
	    }
	  अन्यथा
	    {
	      c_parser_consume_token (parser);
	      व्यंजक.मूल्य
		= build_external_ref (loc, id,
				      (c_parser_peek_token (parser)->type
				       == CPP_OPEN_PAREN), &व्यंजक.original_type);
	      set_c_व्यंजक_source_range (&व्यंजक, tok_range);
	    }
	  अवरोध;
	}
      /* Fallthru.  */
    शेष:
      c_parser_error (parser, "expected expression");
      व्यंजक.set_error ();
      अवरोध;
    }
  अगर (व्यंजक.मूल्य == error_mark_गाँठ)
    वापस व्यंजक;
  वापस c_parser_gimple_postfix_expression_after_primary
    (parser, व्यंजक_LOC_OR_LOC (व्यंजक.मूल्य, loc), व्यंजक);
}

/* Parse a gimple postfix expression after the initial primary or compound
   literal.  */

अटल काष्ठा c_व्यंजक
c_parser_gimple_postfix_expression_after_primary (gimple_parser &parser,
						  location_t व्यंजक_loc,
						  काष्ठा c_व्यंजक व्यंजक)
{
  location_t start;
  location_t finish;
  वृक्ष ident;
  location_t comp_loc;

  जबतक (true)
    {
      location_t op_loc = c_parser_peek_token (parser)->location;
      चयन (c_parser_peek_token (parser)->type)
	{
	हाल CPP_OPEN_SQUARE:
	  {
	    c_parser_consume_token (parser);
	    वृक्ष idx = c_parser_gimple_unary_expression (parser).मूल्य;

	    अगर (! c_parser_require (parser, CPP_CLOSE_SQUARE, "expected %<]%>"))
	      {
		c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE, शून्य);
		अवरोध;
	      }

	    start = व्यंजक.get_start ();
	    finish = c_parser_tokens_buf (parser, 0)->location;
	    व्यंजक.मूल्य = build_array_ref (op_loc, व्यंजक.मूल्य, idx);
	    set_c_व्यंजक_source_range (&व्यंजक, start, finish);
	    व्यंजक.m_decimal = 0;

	    व्यंजक.original_code = ERROR_MARK;
	    व्यंजक.original_type = शून्य;
	    अवरोध;
	  }
	हाल CPP_OPEN_PAREN:
	  {
	    /* Function call.  */
	    c_parser_consume_token (parser);
	    auto_vec<वृक्ष> exprlist;
	    अगर (! c_parser_अग्र_token_is (parser, CPP_CLOSE_PAREN))
	      c_parser_gimple_व्यंजक_list (parser, &exprlist);
	    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    अगर (!FUNC_OR_METHOD_TYPE_P (वृक्ष_TYPE (व्यंजक.मूल्य)))
	      {
		c_parser_error (parser, "invalid call to non-function");
		व्यंजक.set_error ();
		अवरोध;
	      }
	    व्यंजक.मूल्य = build_call_array_loc
		(व्यंजक_loc, वृक्ष_TYPE (वृक्ष_TYPE (व्यंजक.मूल्य)),
		 व्यंजक.मूल्य, exprlist.लंबाई (), exprlist.address ());
	    व्यंजक.m_decimal = 0;
	    व्यंजक.original_code = ERROR_MARK;
	    व्यंजक.original_type = शून्य;
	    अवरोध;
	  }
	हाल CPP_DOT:
	  {
	    /* Structure element reference.  */
	    c_parser_consume_token (parser);
	    अगर (c_parser_अग्र_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		ident = comp_tok->मूल्य;
		comp_loc = comp_tok->location;
	      }
	    अन्यथा
	      {
		c_parser_error (parser, "expected identifier");
		व्यंजक.set_error ();
		व्यंजक.original_code = ERROR_MARK;
		व्यंजक.original_type = शून्य;
		वापस व्यंजक;
	      }
	    start = व्यंजक.get_start ();
	    finish = c_parser_peek_token (parser)->get_finish ();
	    c_parser_consume_token (parser);
	    व्यंजक.मूल्य = build_component_ref (op_loc, व्यंजक.मूल्य, ident,
					      comp_loc, UNKNOWN_LOCATION);
	    set_c_व्यंजक_source_range (&व्यंजक, start, finish);
	    व्यंजक.m_decimal = 0;
	    व्यंजक.original_code = ERROR_MARK;
	    अगर (वृक्ष_CODE (व्यंजक.मूल्य) != COMPONENT_REF)
	      व्यंजक.original_type = शून्य;
	    अन्यथा
	      {
		/* Remember the original type of a bitfield.  */
		वृक्ष field = वृक्ष_OPERAND (व्यंजक.मूल्य, 1);
		अगर (वृक्ष_CODE (field) != FIELD_DECL)
		  व्यंजक.original_type = शून्य;
		अन्यथा
		  व्यंजक.original_type = DECL_BIT_FIELD_TYPE (field);
	      }
	    अवरोध;
	  }
	हाल CPP_DEREF:
	  {
	    /* Structure element reference.  */
	    अगर (!POINTER_TYPE_P (वृक्ष_TYPE (व्यंजक.मूल्य)))
	      {
		c_parser_error (parser, "dereference of non-pointer");
		व्यंजक.set_error ();
		व्यंजक.original_code = ERROR_MARK;
		व्यंजक.original_type = शून्य;
		वापस व्यंजक;
	      }
	    c_parser_consume_token (parser);
	    अगर (c_parser_अग्र_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		ident = comp_tok->मूल्य;
		comp_loc = comp_tok->location;
	      }
	    अन्यथा
	      {
		c_parser_error (parser, "expected identifier");
		व्यंजक.set_error ();
		व्यंजक.original_code = ERROR_MARK;
		व्यंजक.original_type = शून्य;
		वापस व्यंजक;
	      }
	    start = व्यंजक.get_start ();
	    finish = c_parser_peek_token (parser)->get_finish ();
	    c_parser_consume_token (parser);
	    व्यंजक.मूल्य = build_component_ref (op_loc,
					      build_simple_mem_ref_loc
					        (op_loc, व्यंजक.मूल्य),
					      ident, comp_loc,
					      व्यंजक.get_location ());
	    set_c_व्यंजक_source_range (&व्यंजक, start, finish);
	    व्यंजक.m_decimal = 0;
	    व्यंजक.original_code = ERROR_MARK;
	    अगर (वृक्ष_CODE (व्यंजक.मूल्य) != COMPONENT_REF)
	      व्यंजक.original_type = शून्य;
	    अन्यथा
	      {
		/* Remember the original type of a bitfield.  */
		वृक्ष field = वृक्ष_OPERAND (व्यंजक.मूल्य, 1);
		अगर (वृक्ष_CODE (field) != FIELD_DECL)
		  व्यंजक.original_type = शून्य;
		अन्यथा
		  व्यंजक.original_type = DECL_BIT_FIELD_TYPE (field);
	      }
	    अवरोध;
	  }
	शेष:
	  वापस व्यंजक;
	}
    }
}

/* Parse expression list.

   gimple-expr-list:
     gimple-unary-expression
     gimple-expr-list , gimple-unary-expression

 */

अटल व्योम
c_parser_gimple_व्यंजक_list (gimple_parser &parser, vec<वृक्ष> *ret)
{
  काष्ठा c_व्यंजक व्यंजक;

  व्यंजक = c_parser_gimple_unary_expression (parser);
  ret->safe_धकेलो (व्यंजक.मूल्य);
  जबतक (c_parser_अग्र_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      व्यंजक = c_parser_gimple_unary_expression (parser);
      ret->safe_धकेलो (व्यंजक.मूल्य);
    }
}

/* Parse gimple label.

   gimple-label:
     identifier :
     case constant-expression :
     default :

*/

अटल व्योम
c_parser_gimple_label (gimple_parser &parser, gimple_seq *seq)
{
  वृक्ष name = c_parser_peek_token (parser)->मूल्य;
  location_t loc1 = c_parser_peek_token (parser)->location;
  gcc_assert (c_parser_अग्र_token_is (parser, CPP_NAME));
  c_parser_consume_token (parser);
  gcc_assert (c_parser_अग्र_token_is (parser, CPP_COLON));
  c_parser_consume_token (parser);
  वृक्ष label = define_label (loc1, name);
  अगर (label)
    gimple_seq_add_stmt_without_update (seq, gimple_build_label (label));
  वापस;
}

/* Parse gimple/RTL pass list.

   gimple-or-rtl-pass-list:
     startwith("pass-name")[,{cfg,ssa}]
 */

व्योम
c_parser_gimple_or_rtl_pass_list (c_parser *parser, c_declspecs *specs)
{
  अक्षर *pass = शून्य;

  /* Accept __GIMPLE/__RTL.  */
  अगर (c_parser_अग्र_token_is_not (parser, CPP_OPEN_PAREN))
    वापस;
  c_parser_consume_token (parser);

  specs->entry_bb_गिनती = profile_गिनती::uninitialized ();
  जबतक (c_parser_अग्र_token_is (parser, CPP_NAME))
    {
      profile_quality quality;
      स्थिर अक्षर *op = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य);
      c_parser_consume_token (parser);
      अगर (! म_भेद (op, "startwith"))
	{
	  अगर (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    वापस;
	  अगर (c_parser_अग्र_token_is_not (parser, CPP_STRING))
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"expected pass name");
	      वापस;
	    }
	  pass = xstrdup (वृक्ष_STRING_POINTER
			  (c_parser_string_literal (parser, false,
						    false).मूल्य));
	  अगर (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<(%>"))
	    वापस;
	}
      अन्यथा अगर (parse_profile_quality (op, &quality))
	{
	  वृक्ष q;
	  अगर (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    वापस;

	  अगर (!c_parser_अग्र_token_is (parser, CPP_संख्या)
	      || (वृक्ष_CODE (q = c_parser_peek_token (parser)->मूल्य)
		  != INTEGER_CST))
	    {
	      c_parser_error (parser, "expected count value");
	      वापस;
	    }

	  specs->entry_bb_गिनती
	    = profile_गिनती::from_gcov_type (वृक्ष_INT_CST_निचला (q), quality);
	  c_parser_consume_token (parser);
	  अगर (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    वापस;
	}
      अन्यथा अगर (specs->declspec_il != cdil_gimple)
	/* Allow only one IL specifier and none on RTL.  */
	;
      अन्यथा अगर (! म_भेद (op, "cfg"))
	specs->declspec_il = cdil_gimple_cfg;
      अन्यथा अगर (! म_भेद (op, "ssa"))
	specs->declspec_il = cdil_gimple_ssa;
      अन्यथा
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "invalid operation");
	  वापस;
	}
     अगर (c_parser_अग्र_token_is (parser, CPP_COMMA))
       c_parser_consume_token (parser);
    }

  अगर (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    वापस;

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

अटल व्योम
c_parser_gimple_declaration (gimple_parser &parser)
{
  काष्ठा c_declarator *declarator;
  काष्ठा c_declspecs *specs = build_null_declspecs ();
  c_parser_declspecs (parser, specs, true, true, true,
		      true, true, true, true, cla_nonabstract_decl);
  finish_declspecs (specs);

  /* Provide better error recovery.  Note that a type name here is usually
     better diagnosed as a redeclaration.  */
  अगर (c_parser_अग्र_token_starts_declspecs (parser)
      && ! c_parser_अग्र_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<;%>");
      c_parser_set_error (parser, false);
      वापस;
    }

  bool dummy = false;
  declarator = c_parser_declarator (parser,
				    specs->typespec_kind != ctsk_none,
				    C_DTR_NORMAL, &dummy);

  अगर (!c_parser_अग्र_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_error (parser, "expected %<;%>");
      वापस;
    }
  अगर (declarator)
    {
      /* Handle SSA name decls specially, they do not go into the identifier
         table but we simply build the SSA name for later lookup.  */
      अचिन्हित version, ver_offset;
      /* Handle SSA pointer declarations in a very simplistic ways, we
	 probably would like to call grokdeclarator in a special mode to
	 just build the type of the decl - start_decl already pushes
	 the identifier to the bindings for lookup, something we do not
	 want.  */
      काष्ठा c_declarator *id_declarator = declarator;
      जबतक (id_declarator->kind == cdk_pointer)
	id_declarator = id_declarator->declarator;
      अगर (id_declarator->kind == cdk_id
	  && (declarator->kind == cdk_pointer
	      || is_gimple_reg_type (specs->type))
	  && c_parser_parse_ssa_name_id (id_declarator->u.id.id,
					 &version, &ver_offset)
	  /* The following restricts it to unnamed anonymous SSA names
	     which fails parsing of named ones in dumps (we could
	     decide to not dump their name for -gimple).  */
	  && ver_offset == 0)
	{
	  काष्ठा c_declarator *p = declarator;
	  वृक्ष type = specs->type;
	  जबतक (p->kind == cdk_pointer)
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
	  specs->attrs = शून्य;
	  वृक्ष decl = start_decl (declarator, specs, false,
				  chainon (postfix_attrs, all_prefix_attrs));
	  अगर (decl)
	    finish_decl (decl, UNKNOWN_LOCATION, NULL_वृक्ष, NULL_वृक्ष,
			 NULL_वृक्ष);
	}
    }
}

/* Parse gimple goto statement.  */

अटल व्योम
c_parser_gimple_goto_stmt (gimple_parser &parser,
			   location_t loc, वृक्ष label, gimple_seq *seq)
{
  अगर (cfun->curr_properties & PROP_cfg)
    {
      पूर्णांक dest_सूचकांक;
      profile_probability prob;
      अगर (c_parser_gimple_parse_bb_spec_edge_probability (label, parser,
							  &dest_सूचकांक, &prob))
	{
	  parser.धकेलो_edge (parser.current_bb->सूचकांक, dest_सूचकांक,
			    EDGE_FALLTHRU, prob);
	  वापस;
	}
    }
  वृक्ष decl = lookup_label_for_goto (loc, label);
  gimple_seq_add_stmt_without_update (seq, gimple_build_goto (decl));
}

/* Parse a parenthesized condition.
   gimple-condition:
     ( gimple-binary-expression )    */

अटल वृक्ष
c_parser_gimple_paren_condition (gimple_parser &parser)
{
  अगर (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    वापस error_mark_गाँठ;
  वृक्ष cond
    = c_parser_gimple_द्विआधारी_expression (parser, boolean_type_गाँठ).मूल्य;
  अगर (cond != error_mark_गाँठ
      && ! COMPARISON_CLASS_P (cond)
      && ! CONSTANT_CLASS_P (cond)
      && ! SSA_VAR_P (cond))
    {
      c_parser_error (parser, "comparison required");
      cond = error_mark_गाँठ;
    }
  अगर (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    वापस error_mark_गाँठ;
  वापस cond;
}

/* Parse gimple try statement.

   try-statement:
     try { ... } finally { ... }
     try { ... } finally { ... } else { ... }

   This could support try/catch as well, but it's not implemented yet.
 */

अटल व्योम
c_parser_gimple_try_stmt (gimple_parser &parser, gimple_seq *seq)
{
  gimple_seq tryseq = शून्य;
  c_parser_consume_token (parser);
  c_parser_gimple_compound_statement (parser, &tryseq);

  अगर ((c_parser_अग्र_token_is (parser, CPP_KEYWORD)
       && c_parser_peek_token (parser)->keyword == RID_AT_FINALLY)
      || (c_parser_अग्र_token_is (parser, CPP_NAME)
	  && c_parser_peek_token (parser)->id_kind == C_ID_ID
	  && म_भेद (IDENTIFIER_POINTER (c_parser_peek_token (parser)->मूल्य),
		     "finally") == 0))
    {
      gimple_seq finseq = शून्य;
      c_parser_consume_token (parser);
      c_parser_gimple_compound_statement (parser, &finseq);

      अगर (c_parser_अग्र_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_ELSE)
	{
	  gimple_seq elsseq = शून्य;
	  c_parser_consume_token (parser);
	  c_parser_gimple_compound_statement (parser, &elsseq);

	  geh_else *stmt = gimple_build_eh_else (finseq, elsseq);
	  finseq = शून्य;
	  gimple_seq_add_stmt_without_update (&finseq, stmt);
	}

      gtry *stmt = gimple_build_try (tryseq, finseq, GIMPLE_TRY_FINALLY);
      gimple_seq_add_stmt_without_update (seq, stmt);
    }
  अन्यथा अगर (c_parser_अग्र_token_is (parser, CPP_KEYWORD)
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

अटल व्योम
c_parser_gimple_if_stmt (gimple_parser &parser, gimple_seq *seq)
{
  वृक्ष t_label = NULL_वृक्ष, f_label = NULL_वृक्ष, label;
  location_t loc;
  c_parser_consume_token (parser);
  वृक्ष cond = c_parser_gimple_paren_condition (parser);

  अगर (c_parser_अग्र_token_is_keyword (parser, RID_GOTO))
    {
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      अगर (! c_parser_अग्र_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected label");
	  वापस;
	}
      label = c_parser_peek_token (parser)->मूल्य;
      c_parser_consume_token (parser);
      पूर्णांक dest_सूचकांक;
      profile_probability prob;
      अगर ((cfun->curr_properties & PROP_cfg)
	  && c_parser_gimple_parse_bb_spec_edge_probability (label, parser,
							     &dest_सूचकांक, &prob))
	parser.धकेलो_edge (parser.current_bb->सूचकांक, dest_सूचकांक,
			  EDGE_TRUE_मूल्य, prob);
      अन्यथा
	t_label = lookup_label_for_goto (loc, label);
      अगर (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	वापस;
    }
  अन्यथा
    {
      c_parser_error (parser, "expected goto expression");
      वापस;
    }

  अगर (c_parser_अग्र_token_is_keyword (parser, RID_ELSE))
    c_parser_consume_token (parser);
  अन्यथा
    {
      c_parser_error (parser, "expected else statement");
      वापस;
    }

  अगर (c_parser_अग्र_token_is_keyword (parser, RID_GOTO))
    {
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      अगर (! c_parser_अग्र_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected label");
	  वापस;
	}
      label = c_parser_peek_token (parser)->मूल्य;
      c_parser_consume_token (parser);
      पूर्णांक dest_सूचकांक;
      profile_probability prob;
      अगर ((cfun->curr_properties & PROP_cfg)
	  && c_parser_gimple_parse_bb_spec_edge_probability (label, parser,
							     &dest_सूचकांक, &prob))
	parser.धकेलो_edge (parser.current_bb->सूचकांक, dest_सूचकांक,
			  EDGE_FALSE_मूल्य, prob);
      अन्यथा
	f_label = lookup_label_for_goto (loc, label);
      अगर (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	वापस;
    }
  अन्यथा
    {
      c_parser_error (parser, "expected goto expression");
      वापस;
    }

  अगर (cond != error_mark_गाँठ)
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

अटल व्योम
c_parser_gimple_switch_stmt (gimple_parser &parser, gimple_seq *seq)
{
  c_व्यंजक cond_व्यंजक;
  वृक्ष case_label, label;
  auto_vec<वृक्ष> labels;
  वृक्ष default_label = NULL_वृक्ष;
  c_parser_consume_token (parser);

  अगर (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    वापस;
  cond_व्यंजक = c_parser_gimple_postfix_expression (parser);
  अगर (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    वापस;

  अगर (! c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    वापस;

  जबतक (c_parser_अग्र_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      अगर (c_parser_अग्र_token_is (parser, CPP_EOF))
	{
	  c_parser_error (parser, "expected statement");
	  वापस;
	}

      चयन (c_parser_peek_token (parser)->keyword)
	{
	हाल RID_CASE:
	  {
	    c_व्यंजक exp1;
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);

	    अगर (c_parser_अग्र_token_is (parser, CPP_NAME)
		|| c_parser_peek_token (parser)->type == CPP_संख्या)
	      exp1 = c_parser_gimple_postfix_expression (parser);
	    अन्यथा
	      {
		c_parser_error (parser, "expected expression");
		वापस;
	      }

	    अगर (c_parser_अग्र_token_is (parser, CPP_COLON))
	      {
		c_parser_consume_token (parser);
		अगर (c_parser_अग्र_token_is (parser, CPP_NAME))
		  {
		    label = c_parser_peek_token (parser)->मूल्य;
		    c_parser_consume_token (parser);
		    वृक्ष decl = lookup_label_for_goto (loc, label);
		    case_label = build_case_label (exp1.मूल्य, NULL_वृक्ष,
						   decl);
		    labels.safe_धकेलो (case_label);
		    अगर (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      वापस;
		  }
		अन्यथा अगर (! c_parser_require (parser, CPP_NAME,
					     "expected label"))
		  वापस;
	      }
	    अन्यथा अगर (! c_parser_require (parser, CPP_SEMICOLON,
					 "expected %<:%>"))
	      वापस;
	    अवरोध;
	  }
	हाल RID_DEFAULT:
	  {
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);
	    अगर (c_parser_अग्र_token_is (parser, CPP_COLON))
	      {
		c_parser_consume_token (parser);
		अगर (c_parser_अग्र_token_is (parser, CPP_NAME))
		  {
		    label = c_parser_peek_token (parser)->मूल्य;
		    c_parser_consume_token (parser);
		    वृक्ष decl = lookup_label_for_goto (loc, label);
		    default_label = build_case_label (NULL_वृक्ष, NULL_वृक्ष,
						      decl);
		    अगर (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      वापस;
		  }
		अन्यथा अगर (! c_parser_require (parser, CPP_NAME,
					     "expected label"))
		  वापस;
	      }
	    अन्यथा अगर (! c_parser_require (parser, CPP_SEMICOLON,
					 "expected %<:%>"))
	      वापस;
	    अवरोध;
	  }
	शेष:
	  c_parser_error (parser, "expected case label");
	  वापस;
	}

    }
  अगर (! c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>"))
    वापस;

  अगर (cond_व्यंजक.मूल्य != error_mark_गाँठ)
    {
      gswitch *s = gimple_build_switch (cond_व्यंजक.मूल्य, default_label, labels);
      gimple_seq_add_stmt_without_update (seq, s);
    }
}

/* Parse gimple return statement.  */

अटल व्योम
c_parser_gimple_return_stmt (gimple_parser &parser, gimple_seq *seq)
{
  location_t loc = c_parser_peek_token (parser)->location;
  gimple *ret = शून्य;
  c_parser_consume_token (parser);
  अगर (c_parser_अग्र_token_is (parser, CPP_SEMICOLON))
    {
      c_finish_gimple_return (loc, NULL_वृक्ष);
      ret = gimple_build_return (शून्य);
      gimple_seq_add_stmt_without_update (seq, ret);
    }
  अन्यथा
    {
      location_t xloc = c_parser_peek_token (parser)->location;
      c_व्यंजक व्यंजक = c_parser_gimple_unary_expression (parser);
      अगर (व्यंजक.मूल्य != error_mark_गाँठ)
	{
	  c_finish_gimple_return (xloc, व्यंजक.मूल्य);
	  ret = gimple_build_return (व्यंजक.मूल्य);
	  gimple_seq_add_stmt_without_update (seq, ret);
	}
    }
}

/* Support function for c_parser_gimple_return_stmt.  */

अटल व्योम
c_finish_gimple_return (location_t loc, वृक्ष retval)
{
  वृक्ष valtype = वृक्ष_TYPE (वृक्ष_TYPE (current_function_decl));

  /* Use the expansion point to handle cases such as returning NULL
     in a function returning void.  */
  location_t xloc = expansion_point_location_if_in_system_header (loc);

  अगर (वृक्ष_THIS_VOLATILE (current_function_decl))
    warning_at (xloc, 0,
		"function declared %<noreturn%> has a %<return%> statement");

  अगर (! retval)
    current_function_returns_null = 1;
  अन्यथा अगर (valtype == 0 || VOID_TYPE_P (valtype))
    {
      current_function_returns_null = 1;
      अगर (वृक्ष_CODE (वृक्ष_TYPE (retval)) != VOID_TYPE)
	{
	  error_at
	    (xloc, "%<return%> with a value, in function returning void");
	  inform (DECL_SOURCE_LOCATION (current_function_decl),
		  "declared here");
	}
    }
  अन्यथा अगर (वृक्ष_CODE (valtype) != वृक्ष_CODE (वृक्ष_TYPE (retval)))
    {
      error_at
	(xloc, "invalid conversion in return statement");
      inform (DECL_SOURCE_LOCATION (current_function_decl),
	      "declared here");
    }
  वापस;
}
