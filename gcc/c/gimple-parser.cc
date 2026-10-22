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

#അന്തര്ഭാവ "config.h"
#അന്തര്ഭാവ "system.h"
#അന്തര്ഭാവ "coretypes.h"
#അന്തര്ഭാവ "target.h"
#അന്തര്ഭാവ "function.h"
#അന്തര്ഭാവ "c-tree.h"
#അന്തര്ഭാവ "timevar.h"
#അന്തര്ഭാവ "stringpool.h"
#അന്തര്ഭാവ "cgraph.h"
#അന്തര്ഭാവ "attribs.h"
#അന്തര്ഭാവ "stor-layout.h"
#അന്തര്ഭാവ "varasm.h"
#അന്തര്ഭാവ "trans-mem.h"
#അന്തര്ഭാവ "c-family/c-pragma.h"
#അന്തര്ഭാവ "c-lang.h"
#അന്തര്ഭാവ "c-family/c-objc.h"
#അന്തര്ഭാവ "plugin.h"
#അന്തര്ഭാവ "builtins.h"
#അന്തര്ഭാവ "gomp-constants.h"
#അന്തര്ഭാവ "c-family/c-indentation.h"
#അന്തര്ഭാവ "gimple-expr.h"
#അന്തര്ഭാവ "context.h"
#അന്തര്ഭാവ "gcc-rich-location.h"
#അന്തര്ഭാവ "c-parser.h"
#അന്തര്ഭാവ "tree-vrp.h"
#അന്തര്ഭാവ "tree-pass.h"
#അന്തര്ഭാവ "tree-pretty-print.h"
#അന്തര്ഭാവ "tree.h"
#അന്തര്ഭാവ "basic-block.h"
#അന്തര്ഭാവ "gimple.h"
#അന്തര്ഭാവ "gimple-pretty-print.h"
#അന്തര്ഭാവ "tree-ssa.h"
#അന്തര്ഭാവ "pass_manager.h"
#അന്തര്ഭാവ "tree-ssanames.h"
#അന്തര്ഭാവ "gimple-ssa.h"
#അന്തര്ഭാവ "tree-dfa.h"
#അന്തര്ഭാവ "internal-fn.h"
#അന്തര്ഭാവ "cfg.h"
#അന്തര്ഭാവ "cfghooks.h"
#അന്തര്ഭാവ "bitmap.h"
#അന്തര്ഭാവ "cfganal.h"
#അന്തര്ഭാവ "tree-cfg.h"
#അന്തര്ഭാവ "gimple-iterator.h"
#അന്തര്ഭാവ "cfgloop.h"
#അന്തര്ഭാവ "tree-phinodes.h"
#അന്തര്ഭാവ "tree-into-ssa.h"


/* GIMPLE parser state.  */

വർഗ്ഗം gimple_parser
{
പൊതു:
  gimple_parser (c_parser *p) : parser (p), edges(), current_bb(ശൂന്യ) {}
  /* c_parser is not visible here, use composition and fake inheritance
     via a conversion operator.  */
  operator c_parser *() { തിരികെ parser; }
  c_parser *parser;

  /* CFG build state.  */
  വർഗ്ഗം gimple_parser_edge
  {
  പൊതു:
    പൂർണ്ണസംഖ്യ src;
    പൂർണ്ണസംഖ്യ dest;
    പൂർണ്ണസംഖ്യ flags;
    profile_probability probability;
  };
  auto_vec<gimple_parser_edge> edges;
  basic_block current_bb;

  ശൂന്യം തള്ളുക_edge (പൂർണ്ണസംഖ്യ, പൂർണ്ണസംഖ്യ, പൂർണ്ണസംഖ്യ, profile_probability);
};

ശൂന്യം
gimple_parser::തള്ളുക_edge (പൂർണ്ണസംഖ്യ src, പൂർണ്ണസംഖ്യ dest, പൂർണ്ണസംഖ്യ flags,
			  profile_probability prob)
{
  gimple_parser_edge e;
  e.src = src;
  e.dest = dest;
  e.flags = flags;
  e.probability = prob;
  edges.safe_തള്ളുക (e);
}


/* Gimple parsing functions.  */
സ്ഥിതം തർക്കം c_parser_gimple_compound_statement (gimple_parser &, gimple_seq *);
സ്ഥിതം ശൂന്യം c_parser_gimple_label (gimple_parser &, gimple_seq *);
സ്ഥിതം ശൂന്യം c_parser_gimple_statement (gimple_parser &, gimple_seq *);
സ്ഥിതം ഘടന c_വ്യഞ്ജകം c_parser_gimple_ദ്വിമാന_expression (gimple_parser &, വൃക്ഷം);
സ്ഥിതം ഘടന c_വ്യഞ്ജകം c_parser_gimple_unary_expression (gimple_parser &);
സ്ഥിതം ഘടന c_വ്യഞ്ജകം c_parser_gimple_postfix_expression
			(gimple_parser &, വൃക്ഷം = error_mark_കണ്ണി);
സ്ഥിതം ഘടന c_വ്യഞ്ജകം c_parser_gimple_postfix_expression_after_primary
			(gimple_parser &, location_t, ഘടന c_വ്യഞ്ജകം);
സ്ഥിതം ശൂന്യം c_parser_gimple_declaration (gimple_parser &);
സ്ഥിതം ശൂന്യം c_parser_gimple_goto_stmt (gimple_parser &, location_t,
				       വൃക്ഷം, gimple_seq *);
സ്ഥിതം ശൂന്യം c_parser_gimple_try_stmt (gimple_parser &, gimple_seq *);
സ്ഥിതം ശൂന്യം c_parser_gimple_if_stmt (gimple_parser &, gimple_seq *);
സ്ഥിതം ശൂന്യം c_parser_gimple_switch_stmt (gimple_parser &, gimple_seq *);
സ്ഥിതം ശൂന്യം c_parser_gimple_return_stmt (gimple_parser &, gimple_seq *);
സ്ഥിതം ശൂന്യം c_finish_gimple_return (location_t, വൃക്ഷം);
സ്ഥിതം വൃക്ഷം c_parser_gimple_paren_condition (gimple_parser &);
സ്ഥിതം ശൂന്യം c_parser_gimple_വ്യഞ്ജകം_list (gimple_parser &, vec<വൃക്ഷം> *);


/* Much like parser_build_unary_op, but avoid applying default conversions.  */

സ്ഥിതം c_വ്യഞ്ജകം
gimple_parser_build_unary_op (location_t loc,
			      എണ്ണൽ വൃക്ഷം_code code, ഘടന c_വ്യഞ്ജകം arg)
{
  ഘടന c_വ്യഞ്ജകം result;

  result.original_code = code;
  result.original_type = ശൂന്യ;
  result.m_decimal = 0;

  എങ്കിൽ (reject_gcc_builtin (arg.മൂല്യം))
    {
      result.മൂല്യം = error_mark_കണ്ണി;
    }
  അല്ലെങ്കിൽ
    {
      result.മൂല്യം = build_unary_op (loc, code, arg.മൂല്യം, സത്യം);

      എങ്കിൽ (വൃക്ഷം_OVERFLOW_P (result.മൂല്യം) && !വൃക്ഷം_OVERFLOW_P (arg.മൂല്യം))
	overflow_warning (loc, result.മൂല്യം, arg.മൂല്യം);
    }

  /* We are typically called when parsing a prefix token at LOC acting on
     ARG.  Reflect this by updating the source range of the result to
     start at LOC and end at the end of ARG.  */
  set_c_വ്യഞ്ജകം_source_range (&result,
			   loc, arg.get_finish ());

  തിരികെ result;
}

/* See if VAL is an identifier matching __BB<num> and return <num>
   in *INDEX.  */

സ്ഥിതം തർക്കം
c_parser_gimple_parse_bb_spec (വൃക്ഷം val, പൂർണ്ണസംഖ്യ *index)
{
  എങ്കിൽ (!startswith (IDENTIFIER_POINTER (val), "__BB"))
    തിരികെ അസത്യം;

  സ്ഥിരം അക്ഷരം *bb = IDENTIFIER_POINTER (val) + 4;
  എങ്കിൽ (! ISDIGIT (*bb))
    തിരികെ അസത്യം;

  അക്ഷരം *pend;
  errno = 0;
  സ്ഥിരം unsigned long സംഖ്യ = strtoul (bb, &pend, 10);
  എങ്കിൽ (errno == ERANGE
      || *pend != '\0'
      || സംഖ്യ > INT_MAX)
    തിരികെ അസത്യം;

  *index = സംഖ്യ;
  തിരികെ സത്യം;
}

/* See if VAL is an identifier matching __BB<num> and return <num>
   in *INDEX.  Return true if so and parse also FREQUENCY of
   the edge.  */


സ്ഥിതം തർക്കം
c_parser_gimple_parse_bb_spec_edge_probability (വൃക്ഷം val,
						gimple_parser &parser,
						പൂർണ്ണസംഖ്യ *index,
						profile_probability
						*probability)
{
  തർക്കം return_p = c_parser_gimple_parse_bb_spec (val, index);
  എങ്കിൽ (return_p)
    {
      *probability = profile_probability::uninitialized ();
      /* Parse frequency if provided.  */
      എങ്കിൽ (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	{
	  വൃക്ഷം f;
	  c_parser_consume_token (parser);
	  എങ്കിൽ (!c_parser_next_token_is (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected frequency quality");
	      തിരികെ അസത്യം;
	    }

	  profile_quality quality;
	  സ്ഥിരം അക്ഷരം *v
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->മൂല്യം);
	  എങ്കിൽ (!parse_profile_quality (v, &quality))
	    {
	      c_parser_error (parser, "unknown profile quality");
	      തിരികെ അസത്യം;
	    }

	  c_parser_consume_token (parser);
	  എങ്കിൽ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    തിരികെ അസത്യം;

	  എങ്കിൽ (!c_parser_next_token_is (parser, CPP_സംഖ്യ)
	      || (വൃക്ഷം_CODE (f = c_parser_peek_token (parser)->മൂല്യം)
		  != INTEGER_CST))
	    {
	      c_parser_error (parser, "expected frequency value");
	      തിരികെ അസത്യം;
	    }

	  unsigned പൂർണ്ണസംഖ്യ മൂല്യം = വൃക്ഷം_INT_CST_താഴെയുള്ള (f);
	  *probability = profile_probability (മൂല്യം, quality);

	  c_parser_consume_token (parser);
	  എങ്കിൽ (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    തിരികെ അസത്യം;

	  എങ്കിൽ (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    തിരികെ അസത്യം;
	}

      തിരികെ സത്യം;
    }

  തിരികെ അസത്യം;

}

/* Parse the body of a function declaration marked with "__GIMPLE".  */

ശൂന്യം
c_parser_parse_gimple_body (c_parser *cparser, അക്ഷരം *gimple_pass,
			    എണ്ണൽ c_declspec_il cdil,
			    profile_എണ്ണം entry_bb_എണ്ണം)
{
  gimple_parser parser (cparser);
  gimple_seq seq = ശൂന്യ;
  gimple_seq body = ശൂന്യ;
  വൃക്ഷം stmt = തള്ളുക_stmt_list ();
  തള്ളുക_scope ();
  location_t loc1 = c_parser_peek_token (parser)->location;

  cfun->pass_startwith = gimple_pass;
  init_വൃക്ഷം_ssa (cfun);

  എങ്കിൽ (cdil == cdil_gimple)
    /* While we have SSA names in the IL we do not have a CFG built yet
       and PHIs are represented using a PHI internal function.  We do
       have lowered control flow and exception handling (well, we do not
       have parser support for EH yet).  But as we still have BINDs
       we have to go through lowering again.  */
    cfun->curr_properties = PROP_gimple_any;
  അല്ലെങ്കിൽ
    {
      /* We have at least cdil_gimple_cfg.  */
      gimple_register_cfg_hooks ();
      init_empty_വൃക്ഷം_cfg ();
      parser.current_bb = ENTRY_BLOCK_PTR_FOR_FN (cfun);
      /* Initialize the bare loop structure - we are going to only
         mark headers and leave the rest to fixup.  */
      set_loops_for_fn (cfun, ggc_cleared_alloc<ഘടന loops> ());
      init_loops_structure (cfun, loops_for_fn (cfun), 1);
      loops_state_set (cfun, LOOPS_NEED_FIXUP|LOOPS_MAY_HAVE_MULTIPLE_LATCHES);
      cfun->curr_properties
	|= PROP_gimple_lcf | PROP_gimple_leh | PROP_cfg | PROP_loops;
      എങ്കിൽ (cdil == cdil_gimple_ssa)
	{
	  init_ssa_operands (cfun);
	  cfun->curr_properties |= PROP_ssa;
	}
    }

  എങ്കിൽ (! c_parser_gimple_compound_statement (parser, &seq)
      && cdil == cdil_gimple)
    {
      gimple *ret = gimple_build_return (ശൂന്യ);
      gimple_seq_add_stmt_without_update (&seq, ret);
    }

  വൃക്ഷം block = എടുക്കുക_scope ();
  stmt = എടുക്കുക_stmt_list (stmt);
  stmt = c_build_bind_വ്യഞ്ജകം (loc1, block, stmt);

  block = DECL_INITIAL (current_function_decl);
  BLOCK_SUBBLOCKS (block) = NULL_വൃക്ഷം;
  BLOCK_CHAIN (block) = NULL_വൃക്ഷം;
  വൃക്ഷം_ASM_WRITTEN (block) = 1;

  എങ്കിൽ (cdil == cdil_gimple)
    {
      gbind *bind_stmt = gimple_build_bind (BIND_വ്യഞ്ജകം_VARS (stmt), ശൂന്യ,
					    BIND_വ്യഞ്ജകം_BLOCK (stmt));
      gimple_bind_set_body (bind_stmt, seq);
      gimple_seq_add_stmt_without_update (&body, bind_stmt);
      gimple_set_body (current_function_decl, body);
    }
  അല്ലെങ്കിൽ
    {
      /* Control-flow and binds are lowered, record local decls.  */
      വേണ്ടി (വൃക്ഷം var = BIND_വ്യഞ്ജകം_VARS (stmt); var; var = DECL_CHAIN (var))
	എങ്കിൽ (VAR_P (var)
	    && !DECL_EXTERNAL (var))
	  {
	    add_local_decl (cfun, var);
	    /* When the middle-end re-gimplifies any expression we might
	       run into the assertion that we've seen the decl in a BIND.  */
	    എങ്കിൽ (!വൃക്ഷം_STATIC (var))
	      DECL_SEEN_IN_BIND_വ്യഞ്ജകം_P (var) = 1;
	  }
      /* We have a CFG.  Build the edges.  */
      വേണ്ടി (unsigned i = 0; i < parser.edges.length (); ++i)
	{
	  edge e = make_edge (BASIC_BLOCK_FOR_FN (cfun, parser.edges[i].src),
			      BASIC_BLOCK_FOR_FN (cfun, parser.edges[i].dest),
			      parser.edges[i].flags);
	  e->probability = parser.edges[i].probability;
	}
      /* Add edges for case labels.  */
      basic_block bb;
      FOR_EACH_BB_FN (bb, cfun)
	എങ്കിൽ (EDGE_എണ്ണം (bb->succs) == 0)
	  {
	    എങ്കിൽ (gswitch *sw = safe_dyn_cast <gswitch *> (*gsi_last_bb (bb)))
	      വേണ്ടി (unsigned i = 0; i < gimple_switch_അക്കം_labels (sw); ++i)
		{
		  basic_block label_bb = gimple_switch_label_bb (cfun, sw, i);
		  make_edge (bb, label_bb, 0);
		}
	  }
      /* Need those for loop fixup.  */
      calculate_dominance_info (CDI_DOMINATORS);
      /* With SSA lower PHIs parsed as internal function calls and
	 update stmts.  */
      എങ്കിൽ (cdil == cdil_gimple_ssa)
	{
	  /* Create PHI nodes, they are parsed into __PHI internal calls
	     and update SSA operands.  */
	  FOR_EACH_BB_FN (bb, cfun)
	    {
	      gimple_stmt_iterator gsi;
	      വേണ്ടി (gsi = gsi_start_bb (bb); !gsi_end_p (gsi);)
		{
		  gimple *stmt = gsi_stmt (gsi);
		  എങ്കിൽ (!gimple_call_internal_p (stmt, IFN_PHI))
		    നിർത്തുക;

		  gphi *phi = create_phi_കണ്ണി (gimple_call_lhs (stmt), bb);
		  വേണ്ടി (unsigned i = 0; i < gimple_call_അക്കം_args (stmt); i += 2)
		    {
		      പൂർണ്ണസംഖ്യ srcidx = വൃക്ഷം_INT_CST_താഴെയുള്ള (gimple_call_arg (stmt, i));
		      edge e = find_edge (BASIC_BLOCK_FOR_FN (cfun, srcidx), bb);
		      എങ്കിൽ (!e)
			c_parser_error (parser, "edge not found");
		      അല്ലെങ്കിൽ
			add_phi_arg (phi, gimple_call_arg (stmt, i + 1), e,
				     UNKNOWN_LOCATION);
		    }
		  gsi_remove (&gsi, സത്യം);
		}
	      വേണ്ടി (; !gsi_end_p (gsi); gsi_next (&gsi))
		update_stmt (gsi_stmt (gsi));
	    }
	  /* Fill SSA name gaps, putting them on the freelist and diagnose
	     SSA names without definition.  */
	  വേണ്ടി (unsigned i = 1; i < അക്കം_ssa_names; ++i)
	    എങ്കിൽ (!ssa_name (i))
	      {
		വൃക്ഷം name = make_ssa_name_fn (cfun, integer_type_കണ്ണി, ശൂന്യ, i);
		release_ssa_name_fn (cfun, name);
	      }
	    അല്ലെങ്കിൽ എങ്കിൽ (!SSA_NAME_DEF_STMT (ssa_name (i)))
	      error ("SSA name %qE with version %d has no definition",
		     ssa_name (i), i);
	  /* No explicit virtual operands (yet).  */
	  bitmap_obstack_initialize (ശൂന്യ);
	  update_ssa (TODO_update_ssa_only_virtuals);
	  bitmap_obstack_release (ശൂന്യ);
	  /* ???  By flushing the freelist after virtual operand SSA rewrite
	     we keep the gaps available for re-use like needed for the
	     PR89595 testcase but then usually virtual operands would have
	     taken most of them.  The fix is obviously to make virtual
	     operands explicit in the SSA IL.  */
	  flush_ssaname_freelist ();
	}
      fix_loop_structure (ശൂന്യ);
    }

  എങ്കിൽ (cfun->curr_properties & PROP_cfg)
    {
      ENTRY_BLOCK_PTR_FOR_FN (cfun)->എണ്ണം = entry_bb_എണ്ണം;
      gcov_type t = param_gimple_fe_computed_hot_bb_threshold;
      set_hot_bb_threshold (t);
      update_max_bb_എണ്ണം ();
      cgraph_കണ്ണി::get_create (cfun->decl);
      cgraph_edge::rebuild_edges ();
    }

  /* Perform IL validation and if any error is found abort compilation
     of this function by zapping its body.  */
  എങ്കിൽ ((cfun->curr_properties & PROP_cfg)
      && verify_gimple_in_cfg (cfun, അസത്യം, അസത്യം))
    init_empty_വൃക്ഷം_cfg ();
  അല്ലെങ്കിൽ എങ്കിൽ (!(cfun->curr_properties & PROP_cfg)
	   && verify_gimple_in_seq (gimple_body (current_function_decl), അസത്യം))
    gimple_set_body (current_function_decl, ശൂന്യ);

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

സ്ഥിതം തർക്കം
c_parser_gimple_compound_statement (gimple_parser &parser, gimple_seq *seq)
{
  തർക്കം return_p = അസത്യം;

  എങ്കിൽ (! c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    തിരികെ അസത്യം;

  /* A compound statement starts with optional declarations.  */
  ആകുമ്പോൾ (c_parser_next_tokens_start_declaration (parser))
    {
      c_parser_gimple_declaration (parser);
      എങ്കിൽ (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	തിരികെ അസത്യം;
    }

  ആകുമ്പോൾ (c_parser_next_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      എങ്കിൽ (c_parser_error (parser))
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_BRACE, ശൂന്യ);
	  തിരികെ return_p;
	}
      അല്ലെങ്കിൽ എങ്കിൽ (c_parser_next_token_is (parser, CPP_EOF))
	{
	  c_parser_error (parser, "expected declaration or statement");
	  തിരികെ return_p;
	}

      തിരഞ്ഞെടുപ്പ് (c_parser_peek_token (parser)->type)
	{
	അവസ്ഥ CPP_KEYWORD:
	  തിരഞ്ഞെടുപ്പ് (c_parser_peek_token (parser)->keyword)
	    {
	    അവസ്ഥ RID_AT_TRY:
	      c_parser_gimple_try_stmt (parser, seq);
	      നിർത്തുക;
	    അവസ്ഥ RID_IF:
	      c_parser_gimple_if_stmt (parser, seq);
	      നിർത്തുക;
	    അവസ്ഥ RID_SWITCH:
	      c_parser_gimple_switch_stmt (parser, seq);
	      നിർത്തുക;
	    അവസ്ഥ RID_GOTO:
	      {
		location_t loc = c_parser_peek_token (parser)->location;
		c_parser_consume_token (parser);
		എങ്കിൽ (c_parser_next_token_is (parser, CPP_NAME))
		  {
		    വൃക്ഷം label = c_parser_peek_token (parser)->മൂല്യം;
		    c_parser_consume_token (parser);
		    c_parser_gimple_goto_stmt (parser, loc, label, seq);
		    എങ്കിൽ (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      തിരികെ return_p;
		  }
		}
	      നിർത്തുക;
	    അവസ്ഥ RID_RETURN:
	      return_p = സത്യം;
	      c_parser_gimple_return_stmt (parser, seq);
	      എങ്കിൽ (! c_parser_require (parser, CPP_SEMICOLON,
				      "expected %<;%>"))
		തിരികെ return_p;
	      എങ്കിൽ (cfun->curr_properties & PROP_cfg)
		parser.തള്ളുക_edge (parser.current_bb->index, EXIT_BLOCK, 0,
				  profile_probability::uninitialized ());
	      നിർത്തുക;
	    സ്ഥിരസ്ഥിതി:
	      പോകുക വ്യഞ്ജകം_stmt;
	    }
	  നിർത്തുക;
	അവസ്ഥ CPP_NAME:
	  എങ്കിൽ (c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_gimple_label (parser, seq);
	      നിർത്തുക;
	    }
	  എങ്കിൽ (c_parser_next_token_is (parser, CPP_NAME)
	      && c_parser_peek_token (parser)->id_kind == C_ID_ID
	      && strcmp (IDENTIFIER_POINTER (c_parser_peek_token (parser)->മൂല്യം),
			 "try") == 0)
	    {
	      c_parser_gimple_try_stmt (parser, seq);
	      നിർത്തുക;
	    }
	  /* Basic block specification.
	     __BB (index, ...)  */
	  എങ്കിൽ ((cfun->curr_properties & PROP_cfg)
	      && !strcmp (IDENTIFIER_POINTER
			    (c_parser_peek_token (parser)->മൂല്യം), "__BB"))
	    {
	      c_parser_consume_token (parser);
	      എങ്കിൽ (! c_parser_require (parser, CPP_OPEN_PAREN,
				      "expected %<(%>"))
		തിരികെ return_p;
	      എങ്കിൽ (c_parser_next_token_is_not (parser, CPP_സംഖ്യ))
		{
		  c_parser_error (parser, "expected block index");
		  തിരികെ return_p;
		}
	      വൃക്ഷം tnum = c_parser_peek_token (parser)->മൂല്യം;
	      എങ്കിൽ (വൃക്ഷം_CODE (tnum) != INTEGER_CST)
		{
		  c_parser_error (parser, "expected block index");
		  തിരികെ return_p;
		}
	      പൂർണ്ണസംഖ്യ index = വൃക്ഷം_INT_CST_താഴെയുള്ള (tnum);
	      എങ്കിൽ (index < അക്കം_FIXED_BLOCKS
		  || (index < last_basic_block_for_fn (cfun)
		      && BASIC_BLOCK_FOR_FN (cfun, index) != ശൂന്യ))
		{
		  c_parser_error (parser, "invalid block index");
		  തിരികെ return_p;
		}
	      പൂർണ്ണസംഖ്യ is_loop_header_of = -1;
	      profile_എണ്ണം bb_എണ്ണം = profile_എണ്ണം::uninitialized ();
	      c_parser_consume_token (parser);
	      ആകുമ്പോൾ (c_parser_next_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  എങ്കിൽ (! c_parser_next_token_is (parser, CPP_NAME))
		    {
		      c_parser_error (parser, "expected block specifier");
		      തിരികെ return_p;
		    }
		  /* loop_header (NUM)  */
		  എങ്കിൽ (!strcmp (IDENTIFIER_POINTER
			         (c_parser_peek_token (parser)->മൂല്യം),
			       "loop_header"))
		    {
		      c_parser_consume_token (parser);
		      എങ്കിൽ (! c_parser_require (parser, CPP_OPEN_PAREN,
					      "expected %<(%>"))
			തിരികെ return_p;
		      വൃക്ഷം loop_അക്കം;
		      എങ്കിൽ (! c_parser_next_token_is (parser, CPP_സംഖ്യ)
			  || വൃക്ഷം_CODE (loop_അക്കം
					  = c_parser_peek_token (parser)->മൂല്യം)
			       != INTEGER_CST)
			{
			  c_parser_error (parser, "expected loop number");
			  തിരികെ return_p;
			}
		      c_parser_consume_token (parser);
		      is_loop_header_of = വൃക്ഷം_INT_CST_താഴെയുള്ള (loop_അക്കം);
		      എങ്കിൽ (! c_parser_require (parser, CPP_CLOSE_PAREN,
					      "expected %<)%>"))
			തിരികെ return_p;
		    }
		  /* Parse profile: quality(value) */
		  അല്ലെങ്കിൽ
		    {
		      വൃക്ഷം q;
		      profile_quality quality;
		      വൃക്ഷം v = c_parser_peek_token (parser)->മൂല്യം;
		      എങ്കിൽ (!parse_profile_quality (IDENTIFIER_POINTER (v),
						  &quality))
			{
			  c_parser_error (parser, "unknown block specifier");
			  തിരികെ അസത്യം;
			}

		      c_parser_consume_token (parser);
		      എങ്കിൽ (!c_parser_require (parser, CPP_OPEN_PAREN,
					     "expected %<(%>"))
			തിരികെ അസത്യം;

		      എങ്കിൽ (!c_parser_next_token_is (parser, CPP_സംഖ്യ)
			  || (വൃക്ഷം_CODE (q = c_parser_peek_token (parser)->മൂല്യം)
			      != INTEGER_CST))
			{
			  c_parser_error (parser, "expected count value");
			  തിരികെ അസത്യം;
			}

		      bb_എണ്ണം
			= profile_എണ്ണം::from_gcov_type (വൃക്ഷം_INT_CST_താഴെയുള്ള (q),
							 quality);
		      c_parser_consume_token (parser);
		      എങ്കിൽ (! c_parser_require (parser, CPP_CLOSE_PAREN,
					      "expected %<)%>"))
			തിരികെ return_p;
		    }
		}
	      എങ്കിൽ (! c_parser_require (parser, CPP_CLOSE_PAREN,
				      "expected %<)%>")
		  || ! c_parser_require (parser, CPP_COLON,
					 "expected %<:%>"))
		തിരികെ return_p;

	      /* Put stmts parsed in the current block.  */
	      എങ്കിൽ (!gimple_seq_empty_p (*seq))
		{
		  എങ്കിൽ (!parser.current_bb)
		    c_parser_error (parser, "stmts without block");
		  അല്ലെങ്കിൽ
		    {
		      gimple_stmt_iterator gsi
			= gsi_start_bb (parser.current_bb);
		      gsi_തിരുകുക_seq_after_without_update (&gsi, *seq,
							   GSI_CONTINUE_LINKING);
		    }
		  *seq = ശൂന്യ;
		}

	      /* Build an empty block with specified index, linking them
		 in source order.  */
	      basic_block bb = alloc_block ();
	      bb->index = index;
	      link_block (bb, (parser.current_bb ? parser.current_bb
			       : ENTRY_BLOCK_PTR_FOR_FN (cfun)));
	      എങ്കിൽ (basic_block_info_for_fn (cfun)->length () <= (size_t)index)
		vec_safe_grow_cleared (basic_block_info_for_fn (cfun),
				       index + 1, സത്യം);
	      SET_BASIC_BLOCK_FOR_FN (cfun, index, bb);
	      എങ്കിൽ (last_basic_block_for_fn (cfun) <= index)
		last_basic_block_for_fn (cfun) = index + 1;
	      n_basic_blocks_for_fn (cfun)++;
	      എങ്കിൽ (parser.current_bb->index == ENTRY_BLOCK)
		parser.തള്ളുക_edge (ENTRY_BLOCK, bb->index, EDGE_FALLTHRU,
				  profile_probability::always ());

	      /* We leave the proper setting to fixup.  */
	      വർഗ്ഗം loop *loop_father = loops_for_fn (cfun)->വൃക്ഷം_വേര്;
	      /* If the new block is a loop header, allocate a loop
		 struct.  Fixup will take care of proper placement within
		 the loop tree.  */
	      എങ്കിൽ (is_loop_header_of != -1)
		{
		  എങ്കിൽ (സംഖ്യ_of_loops (cfun) > (unsigned)is_loop_header_of
		      && get_loop (cfun, is_loop_header_of) != ശൂന്യ)
		    {
		      c_parser_error (parser, "duplicate loop header");
		    }
		  അല്ലെങ്കിൽ
		    {
		      വർഗ്ഗം loop *loop = alloc_loop ();
		      loop->അക്കം = is_loop_header_of;
		      loop->header = bb;
		      എങ്കിൽ (സംഖ്യ_of_loops (cfun) <= (unsigned)is_loop_header_of)
			vec_safe_grow_cleared (loops_for_fn (cfun)->larray,
					       is_loop_header_of + 1, സത്യം);
		      (*loops_for_fn (cfun)->larray)[is_loop_header_of] = loop;
		      flow_loop_വൃക്ഷം_കണ്ണി_add (loops_for_fn (cfun)->വൃക്ഷം_വേര്,
					       loop);
		    }
		  loop_father = get_loop (cfun, is_loop_header_of);
		}
	      bb->loop_father = loop_father;
	      bb->എണ്ണം = bb_എണ്ണം;

	      /* Stmts now go to the new block.  */
	      parser.current_bb = bb;
	      നിർത്തുക;
	    }
	  പോകുക വ്യഞ്ജകം_stmt;

	അവസ്ഥ CPP_SEMICOLON:
	  {
	    /* Empty stmt.  */
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);
	    gimple *nop = gimple_build_nop ();
	    gimple_set_location (nop, loc);
	    gimple_seq_add_stmt_without_update (seq, nop);
	    നിർത്തുക;
	  }

	അവസ്ഥ CPP_CLOSE_PAREN:
	അവസ്ഥ CPP_CLOSE_SQUARE:
	  /* Avoid infinite loop in error recovery:
	     c_parser_skip_until_found stops at a closing nesting
	     delimiter without consuming it, but here we need to consume
	     it to proceed further.  */
	  c_parser_error (parser, "expected statement");
	  c_parser_consume_token (parser);
	നിർത്തുക;

	സ്ഥിരസ്ഥിതി:
വ്യഞ്ജകം_stmt:
	  c_parser_gimple_statement (parser, seq);
	  എങ്കിൽ (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	    c_parser_skip_until_found (parser, CPP_SEMICOLON, ശൂന്യ);
	}
    }
  c_parser_consume_token (parser);

  /* Put stmts parsed in the current block.  */
  എങ്കിൽ ((cfun->curr_properties & PROP_cfg)
      && !gimple_seq_empty_p (*seq))
    {
      എങ്കിൽ (!parser.current_bb)
	c_parser_error (parser, "stmts without block");
      അല്ലെങ്കിൽ
	{
	  gimple_stmt_iterator gsi = gsi_start_bb (parser.current_bb);
	  gsi_തിരുകുക_seq_after_without_update (&gsi, *seq,
					       GSI_CONTINUE_LINKING);
	}
      *seq = ശൂന്യ;
    }

  തിരികെ return_p;
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

സ്ഥിതം ശൂന്യം
c_parser_gimple_statement (gimple_parser &parser, gimple_seq *seq)
{
  ഘടന c_വ്യഞ്ജകം lhs, rhs;
  gimple *assign = ശൂന്യ;
  location_t loc;
  വൃക്ഷം arg = NULL_വൃക്ഷം;
  auto_vec<വൃക്ഷം> vargs;

  lhs = c_parser_gimple_unary_expression (parser);
  loc = വ്യഞ്ജകം_LOCATION (lhs.മൂല്യം);
  rhs.set_error ();

  /* GIMPLE call statement without LHS.  */
  എങ്കിൽ (c_parser_next_token_is (parser, CPP_SEMICOLON)
      && വൃക്ഷം_CODE (lhs.മൂല്യം) == CALL_വ്യഞ്ജകം)
    {
      gimple *call;
      call = gimple_build_call_from_വൃക്ഷം (lhs.മൂല്യം, ശൂന്യ);
      gimple_seq_add_stmt_without_update (seq, call);
      gimple_set_location (call, loc);
      തിരികെ;
    }

  /* All following cases are statements with LHS.  */
  എങ്കിൽ (! c_parser_require (parser, CPP_EQ, "expected %<=%>"))
    തിരികെ;

  /* Eat and ignore {v} right after the =, the has_volatile_ops is
     redundant and re-computed by the operand scanner.  */
  എങ്കിൽ (c_parser_next_token_is (parser, CPP_OPEN_BRACE)
      && !(c_parser_peek_token (parser)->flags & PREV_WHITE)
      && c_parser_peek_2nd_token (parser)->type == CPP_NAME
      && !(c_parser_peek_2nd_token (parser)->flags & PREV_WHITE)
      && strcmp ("v", IDENTIFIER_POINTER
			(c_parser_peek_2nd_token (parser)->മൂല്യം)) == 0
      && c_parser_peek_nth_token (parser, 3)->type == CPP_CLOSE_BRACE
      && !(c_parser_peek_nth_token (parser, 3)->flags & PREV_WHITE))
    {
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }

  /* Cast expression.  */
  എങ്കിൽ (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_typename (c_parser_peek_2nd_token (parser)))
    {
      c_parser_consume_token (parser);
      ഘടന c_type_name *type_name = c_parser_type_name (parser);
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      എങ്കിൽ (type_name == ശൂന്യ)
	തിരികെ;
      /* ???  The actual type used in the cast expression is ignored as
         in GIMPLE it is encoded by the type of the LHS.  */
      rhs = c_parser_gimple_postfix_expression (parser);
      എങ്കിൽ (lhs.മൂല്യം != error_mark_കണ്ണി
	  && rhs.മൂല്യം != error_mark_കണ്ണി)
	{
	  എണ്ണൽ വൃക്ഷം_code code = NOP_വ്യഞ്ജകം;
	  എങ്കിൽ (FLOAT_TYPE_P (വൃക്ഷം_TYPE (lhs.മൂല്യം))
	      && ! FLOAT_TYPE_P (വൃക്ഷം_TYPE (rhs.മൂല്യം)))
	    code = FLOAT_വ്യഞ്ജകം;
	  അല്ലെങ്കിൽ എങ്കിൽ (! FLOAT_TYPE_P (വൃക്ഷം_TYPE (lhs.മൂല്യം))
		   && FLOAT_TYPE_P (വൃക്ഷം_TYPE (rhs.മൂല്യം)))
	    code = FIX_TRUNC_വ്യഞ്ജകം;
	  assign = gimple_build_assign (lhs.മൂല്യം, code, rhs.മൂല്യം);
	  gimple_seq_add_stmt_without_update (seq, assign);
	  gimple_set_location (assign, loc);
	  തിരികെ;
	}
    }

  /* Unary expression.  */
  തിരഞ്ഞെടുപ്പ് (c_parser_peek_token (parser)->type)
    {
    അവസ്ഥ CPP_NAME:
      {
	വൃക്ഷം id = c_parser_peek_token (parser)->മൂല്യം;
	എങ്കിൽ (strcmp (IDENTIFIER_POINTER (id), "__ABS") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__ABSU") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__MIN") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__MAX") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__BIT_INSERT") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__VEC_PERM") == 0)
	  പോകുക build_unary_വ്യഞ്ജകം;
	നിർത്തുക;
      }
    അവസ്ഥ CPP_KEYWORD:
      എങ്കിൽ (c_parser_peek_token (parser)->keyword != RID_REALPART
	  && c_parser_peek_token (parser)->keyword != RID_IMAGPART)
	നിർത്തുക;
      /* Fallthru.  */
    അവസ്ഥ CPP_AND:
    അവസ്ഥ CPP_PLUS:
    അവസ്ഥ CPP_MINUS:
    അവസ്ഥ CPP_COMPL:
    അവസ്ഥ CPP_NOT:
    അവസ്ഥ CPP_MULT: /* pointer deref */
    build_unary_വ്യഞ്ജകം:
      rhs = c_parser_gimple_unary_expression (parser);
      എങ്കിൽ (rhs.മൂല്യം != error_mark_കണ്ണി)
	{
	  assign = gimple_build_assign (lhs.മൂല്യം, rhs.മൂല്യം);
	  gimple_set_location (assign, loc);
	  gimple_seq_add_stmt_without_update (seq, assign);
	}
      തിരികെ;

    സ്ഥിരസ്ഥിതി:;
    }

  /* GIMPLE PHI statement.  */
  എങ്കിൽ (c_parser_next_token_is_keyword (parser, RID_PHI))
    {
      c_parser_consume_token (parser);

      എങ്കിൽ (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	തിരികെ;

      എങ്കിൽ (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	c_parser_consume_token (parser);

      ആകുമ്പോൾ (c_parser_next_token_is_not (parser, CPP_CLOSE_PAREN))
	{
	  എങ്കിൽ (c_parser_next_token_is (parser, CPP_NAME)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      arg = c_parser_peek_token (parser)->മൂല്യം;
	      c_parser_consume_token (parser);
	      എങ്കിൽ (c_parser_next_token_is (parser, CPP_COLON))
		c_parser_consume_token (parser);
	      പൂർണ്ണസംഖ്യ src_index = -1;
	      എങ്കിൽ (!c_parser_gimple_parse_bb_spec (arg, &src_index))
		c_parser_error (parser, "invalid source block specification");
	      vargs.safe_തള്ളുക (size_int (src_index));
	    }
	  അല്ലെങ്കിൽ എങ്കിൽ (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  അല്ലെങ്കിൽ
	    {
	      arg = c_parser_gimple_unary_expression (parser).മൂല്യം;
	      vargs.safe_തള്ളുക (arg);
	    }
	}

      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");

      /* Build internal function for PHI.  */
      gcall *call_stmt = gimple_build_call_internal_vec (IFN_PHI, vargs);
      gimple_call_set_lhs (call_stmt, lhs.മൂല്യം);
      gimple_set_location (call_stmt, UNKNOWN_LOCATION);
      gimple_seq_add_stmt_without_update (seq, call_stmt);
      തിരികെ;
    }

  /* GIMPLE call with lhs.  */
  എങ്കിൽ (c_parser_next_token_is (parser, CPP_DOT)
      || (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN
	  && lookup_name (c_parser_peek_token (parser)->മൂല്യം)))
    {
      rhs = c_parser_gimple_unary_expression (parser);
      എങ്കിൽ (rhs.മൂല്യം != error_mark_കണ്ണി)
	{
	  gimple *call = gimple_build_call_from_വൃക്ഷം (rhs.മൂല്യം, ശൂന്യ);
	  gimple_call_set_lhs (call, lhs.മൂല്യം);
	  gimple_seq_add_stmt_without_update (seq, call);
	  gimple_set_location (call, loc);
	}
      തിരികെ;
    }

  rhs = c_parser_gimple_ദ്വിമാന_expression (parser, വൃക്ഷം_TYPE (lhs.മൂല്യം));
  എങ്കിൽ (lhs.മൂല്യം != error_mark_കണ്ണി
      && rhs.മൂല്യം != error_mark_കണ്ണി)
    {
      /* If we parsed an identifier and the next token  is a '?' then parse
	 a conditional expression.  */
      എങ്കിൽ (SSA_VAR_P (rhs.മൂല്യം) && c_parser_next_token_is (parser, CPP_QUERY))
	{
	  ഘടന c_വ്യഞ്ജകം trueval, falseval;
	  c_parser_consume_token (parser);
	  trueval = c_parser_gimple_postfix_expression (parser);
	  falseval.set_error ();
	  എങ്കിൽ (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    falseval = c_parser_gimple_postfix_expression (parser);
	  എങ്കിൽ (trueval.മൂല്യം == error_mark_കണ്ണി
	      || falseval.മൂല്യം == error_mark_കണ്ണി)
	    തിരികെ;
	  rhs.മൂല്യം = build3_loc (loc,
				  VECTOR_TYPE_P (വൃക്ഷം_TYPE (rhs.മൂല്യം))
				  ? VEC_COND_വ്യഞ്ജകം : COND_വ്യഞ്ജകം,
				  വൃക്ഷം_TYPE (trueval.മൂല്യം),
				  rhs.മൂല്യം, trueval.മൂല്യം, falseval.മൂല്യം);
	}
      എങ്കിൽ (get_gimple_rhs_class (വൃക്ഷം_CODE (rhs.മൂല്യം)) == GIMPLE_INVALID_RHS)
	{
	  c_parser_error (parser, "unexpected RHS for assignment");
	  തിരികെ;
	}
      assign = gimple_build_assign (lhs.മൂല്യം, rhs.മൂല്യം);
      gimple_seq_add_stmt_without_update (seq, assign);
      gimple_set_location (assign, loc);
    }
  തിരികെ;
}

/* A mapping between an identifier to a tree code for binary operations. */
സ്ഥിതം സ്ഥിരം std::pair<സ്ഥിരം അക്ഷരം *, വൃക്ഷം_code> gimple_ദ്വിമാന_identifier_code[] =
  {
    {"__MULT_HIGHPART", MULT_HIGHPART_വ്യഞ്ജകം},
    {"__UNLT", UNLT_വ്യഞ്ജകം},
    {"__UNLE", UNLE_വ്യഞ്ജകം},
    {"__UNGT", UNGT_വ്യഞ്ജകം},
    {"__UNGE", UNGE_വ്യഞ്ജകം},
    {"__UNEQ", UNEQ_വ്യഞ്ജകം},
    {"__UNORDERED", UNORDERED_വ്യഞ്ജകം},
    {"__ORDERED", ORDERED_വ്യഞ്ജകം},
    {"__LTGT", LTGT_വ്യഞ്ജകം},
    {"__FLOOR_DIV", FLOOR_DIV_വ്യഞ്ജകം},
    {"__ROUND_DIV", ROUND_DIV_വ്യഞ്ജകം},
    {"__EXACT_DIV", EXACT_DIV_വ്യഞ്ജകം},
    {"__CEIL_DIV", CEIL_DIV_വ്യഞ്ജകം},
    {"__FLOOR_MOD", FLOOR_MOD_വ്യഞ്ജകം},
    {"__ROUND_MOD", ROUND_MOD_വ്യഞ്ജകം},
    {"__CEIL_MOD", CEIL_MOD_വ്യഞ്ജകം},
    {"__ROTATE_LEFT", LROTATE_വ്യഞ്ജകം},
    {"__ROTATE_RIGHT", RROTATE_വ്യഞ്ജകം},
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

സ്ഥിതം c_വ്യഞ്ജകം
c_parser_gimple_ദ്വിമാന_expression (gimple_parser &parser, വൃക്ഷം ret_type)
{
  /* Location of the binary operator.  */
  ഘടന c_വ്യഞ്ജകം ret, lhs, rhs;
  എണ്ണൽ വൃക്ഷം_code code = ERROR_MARK;
  ret.set_error ();
  lhs = c_parser_gimple_postfix_expression (parser, ret_type);
  എങ്കിൽ (c_parser_error (parser))
    തിരികെ ret;
  തിരഞ്ഞെടുപ്പ് (c_parser_peek_token (parser)->type)
    {
    അവസ്ഥ CPP_MULT:
      code = MULT_വ്യഞ്ജകം;
      നിർത്തുക;
    അവസ്ഥ CPP_DIV:
      code = TRUNC_DIV_വ്യഞ്ജകം;
      നിർത്തുക;
    അവസ്ഥ CPP_MOD:
      code = TRUNC_MOD_വ്യഞ്ജകം;
      നിർത്തുക;
    അവസ്ഥ CPP_PLUS:
      എങ്കിൽ (POINTER_TYPE_P (വൃക്ഷം_TYPE (lhs.മൂല്യം)))
	code = POINTER_PLUS_വ്യഞ്ജകം;
      അല്ലെങ്കിൽ
	code = PLUS_വ്യഞ്ജകം;
      നിർത്തുക;
    അവസ്ഥ CPP_MINUS:
      എങ്കിൽ (POINTER_TYPE_P (വൃക്ഷം_TYPE (lhs.മൂല്യം)))
	code = POINTER_DIFF_വ്യഞ്ജകം;
      അല്ലെങ്കിൽ
	code = MINUS_വ്യഞ്ജകം;
      നിർത്തുക;
    അവസ്ഥ CPP_LSHIFT:
      code = LSHIFT_വ്യഞ്ജകം;
      നിർത്തുക;
    അവസ്ഥ CPP_RSHIFT:
      code = RSHIFT_വ്യഞ്ജകം;
      നിർത്തുക;
    അവസ്ഥ CPP_LESS:
      code = LT_വ്യഞ്ജകം;
      നിർത്തുക;
    അവസ്ഥ CPP_GREATER:
      code = GT_വ്യഞ്ജകം;
      നിർത്തുക;
    അവസ്ഥ CPP_LESS_EQ:
      code = LE_വ്യഞ്ജകം;
      നിർത്തുക;
    അവസ്ഥ CPP_GREATER_EQ:
      code = GE_വ്യഞ്ജകം;
      നിർത്തുക;
    അവസ്ഥ CPP_EQ_EQ:
      code = EQ_വ്യഞ്ജകം;
      നിർത്തുക;
    അവസ്ഥ CPP_NOT_EQ:
      code = NE_വ്യഞ്ജകം;
      നിർത്തുക;
    അവസ്ഥ CPP_AND:
      code = BIT_AND_വ്യഞ്ജകം;
      നിർത്തുക;
    അവസ്ഥ CPP_XOR:
      code = BIT_XOR_വ്യഞ്ജകം;
      നിർത്തുക;
    അവസ്ഥ CPP_OR:
      code = BIT_IOR_വ്യഞ്ജകം;
      നിർത്തുക;
    അവസ്ഥ CPP_AND_AND:
      c_parser_error (parser, "%<&&%> not valid in GIMPLE");
      തിരികെ ret;
    അവസ്ഥ CPP_OR_OR:
      c_parser_error (parser, "%<||%> not valid in GIMPLE");
      തിരികെ ret;
    അവസ്ഥ CPP_NAME:
      {
	വൃക്ഷം id = c_parser_peek_token (parser)->മൂല്യം;
	വേണ്ടി (auto &p : gimple_ദ്വിമാന_identifier_code)
	  {
	    എങ്കിൽ (strcmp (IDENTIFIER_POINTER (id), p.first) == 0)
	      {
		code = p.second;
		നിർത്തുക;
	      }
	  }
	എങ്കിൽ (code != ERROR_MARK)
	  നിർത്തുക;
      }
      /* Fallthru.  */
    സ്ഥിരസ്ഥിതി:
      /* Not a binary expression.  */
      തിരികെ lhs;
    }
  location_t ret_loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  rhs = c_parser_gimple_postfix_expression (parser);
  എങ്കിൽ (lhs.മൂല്യം != error_mark_കണ്ണി && rhs.മൂല്യം != error_mark_കണ്ണി)
    ret.മൂല്യം = build2_loc (ret_loc, code, ret_type, lhs.മൂല്യം, rhs.മൂല്യം);
  തിരികെ ret;
}

/* Parse a gimple parentized binary expression.  */

സ്ഥിതം c_വ്യഞ്ജകം
c_parser_gimple_parentized_ദ്വിമാന_expression (gimple_parser &parser,
					      location_t op_loc,
					      വൃക്ഷം_code code)
{
  ഘടന c_വ്യഞ്ജകം ret;
  ret.set_error ();

  c_parser_consume_token (parser);
  എങ്കിൽ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    തിരികെ ret;
  c_വ്യഞ്ജകം op1 = c_parser_gimple_postfix_expression (parser);
  എങ്കിൽ (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    തിരികെ ret;
  c_വ്യഞ്ജകം op2 = c_parser_gimple_postfix_expression (parser);
  എങ്കിൽ (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    തിരികെ ret;

  എങ്കിൽ (op1.മൂല്യം != error_mark_കണ്ണി && op2.മൂല്യം != error_mark_കണ്ണി)
    ret.മൂല്യം = build2_loc (op_loc,
			    code, വൃക്ഷം_TYPE (op1.മൂല്യം), op1.മൂല്യം, op2.മൂല്യം);
  തിരികെ ret;
}

/* Parse a gimple parentized binary expression.  */

സ്ഥിതം c_വ്യഞ്ജകം
c_parser_gimple_parentized_ternary_expression (gimple_parser &parser,
					       location_t op_loc,
					       വൃക്ഷം_code code)
{
  ഘടന c_വ്യഞ്ജകം ret;
  ret.set_error ();

  c_parser_consume_token (parser);
  എങ്കിൽ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    തിരികെ ret;
  c_വ്യഞ്ജകം op1 = c_parser_gimple_postfix_expression (parser);
  എങ്കിൽ (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    തിരികെ ret;
  c_വ്യഞ്ജകം op2 = c_parser_gimple_postfix_expression (parser);
  എങ്കിൽ (!c_parser_require (parser, CPP_COMMA, "expected %<)%>"))
    തിരികെ ret;
  c_വ്യഞ്ജകം op3 = c_parser_gimple_postfix_expression (parser);
  എങ്കിൽ (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    തിരികെ ret;

  എങ്കിൽ (op1.മൂല്യം != error_mark_കണ്ണി
      && op2.മൂല്യം != error_mark_കണ്ണി
      && op3.മൂല്യം != error_mark_കണ്ണി)
    ret.മൂല്യം = build3_loc (op_loc,
			    code, വൃക്ഷം_TYPE (op1.മൂല്യം),
			    op1.മൂല്യം, op2.മൂല്യം, op3.മൂല്യം);
  തിരികെ ret;
}

/* Parse gimple unary expression.

   gimple-unary-expression:
     gimple-postfix-expression
     unary-operator gimple-postfix-expression

   unary-operator: one of
     & * + - ~ abs_expr
*/

സ്ഥിതം c_വ്യഞ്ജകം
c_parser_gimple_unary_expression (gimple_parser &parser)
{
  ഘടന c_വ്യഞ്ജകം ret, op;
  location_t op_loc = c_parser_peek_token (parser)->location;
  location_t finish;
  ret.set_error ();
  തിരഞ്ഞെടുപ്പ് (c_parser_peek_token (parser)->type)
    {
    അവസ്ഥ CPP_AND:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      mark_exp_read (op.മൂല്യം);
      തിരികെ gimple_parser_build_unary_op (op_loc, ADDR_വ്യഞ്ജകം, op);
    അവസ്ഥ CPP_MULT:
      {
	c_parser_consume_token (parser);
	op = c_parser_gimple_postfix_expression (parser);
	എങ്കിൽ (op.മൂല്യം == error_mark_കണ്ണി)
	  തിരികെ ret;
	എങ്കിൽ (! POINTER_TYPE_P (വൃക്ഷം_TYPE (op.മൂല്യം)))
	  {
	    error_at (op_loc, "expected pointer as argument of unary %<*%>");
	    തിരികെ ret;
	  }
	finish = op.get_finish ();
	location_t combined_loc = make_location (op_loc, op_loc, finish);
	ret.മൂല്യം = build_simple_mem_ref_loc (combined_loc, op.മൂല്യം);
	വൃക്ഷം_SIDE_EFFECTS (ret.മൂല്യം)
	  = വൃക്ഷം_THIS_VOLATILE (ret.മൂല്യം)
	  = TYPE_VOLATILE (വൃക്ഷം_TYPE (വൃക്ഷം_TYPE (op.മൂല്യം)));
	ret.src_range.m_start = op_loc;
	ret.src_range.m_finish = finish;
	തിരികെ ret;
      }
    അവസ്ഥ CPP_PLUS:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      തിരികെ gimple_parser_build_unary_op (op_loc, CONVERT_വ്യഞ്ജകം, op);
    അവസ്ഥ CPP_MINUS:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      തിരികെ gimple_parser_build_unary_op (op_loc, NEGATE_വ്യഞ്ജകം, op);
    അവസ്ഥ CPP_COMPL:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      തിരികെ gimple_parser_build_unary_op (op_loc, BIT_NOT_വ്യഞ്ജകം, op);
    അവസ്ഥ CPP_NOT:
      c_parser_error (parser, "%<!%> not valid in GIMPLE");
      തിരികെ ret;
    അവസ്ഥ CPP_KEYWORD:
      തിരഞ്ഞെടുപ്പ് (c_parser_peek_token (parser)->keyword)
	{
	അവസ്ഥ RID_REALPART:
	  c_parser_consume_token (parser);
	  op = c_parser_gimple_postfix_expression (parser);
	  തിരികെ gimple_parser_build_unary_op (op_loc, REALPART_വ്യഞ്ജകം, op);
	അവസ്ഥ RID_IMAGPART:
	  c_parser_consume_token (parser);
	  op = c_parser_gimple_postfix_expression (parser);
	  തിരികെ gimple_parser_build_unary_op (op_loc, IMAGPART_വ്യഞ്ജകം, op);
	സ്ഥിരസ്ഥിതി:
	  തിരികെ c_parser_gimple_postfix_expression (parser);
	}
    അവസ്ഥ CPP_NAME:
	{
	  വൃക്ഷം id = c_parser_peek_token (parser)->മൂല്യം;
	  എങ്കിൽ (strcmp (IDENTIFIER_POINTER (id), "__ABS") == 0)
	    {
	      c_parser_consume_token (parser);
	      op = c_parser_gimple_postfix_expression (parser);
	      തിരികെ gimple_parser_build_unary_op (op_loc, ABS_വ്യഞ്ജകം, op);
	    }
	  അല്ലെങ്കിൽ എങ്കിൽ (strcmp (IDENTIFIER_POINTER (id), "__ABSU") == 0)
	    {
	      c_parser_consume_token (parser);
	      op = c_parser_gimple_postfix_expression (parser);
	      തിരികെ gimple_parser_build_unary_op (op_loc, ABSU_വ്യഞ്ജകം, op);
	    }
	  അല്ലെങ്കിൽ എങ്കിൽ (strcmp (IDENTIFIER_POINTER (id), "__MIN") == 0)
	    തിരികെ c_parser_gimple_parentized_ദ്വിമാന_expression (parser,
								 op_loc,
								 MIN_വ്യഞ്ജകം);
	  അല്ലെങ്കിൽ എങ്കിൽ (strcmp (IDENTIFIER_POINTER (id), "__MAX") == 0)
	    തിരികെ c_parser_gimple_parentized_ദ്വിമാന_expression (parser,
								 op_loc,
								 MAX_വ്യഞ്ജകം);
	  അല്ലെങ്കിൽ എങ്കിൽ (strcmp (IDENTIFIER_POINTER (id), "__VEC_PERM") == 0)
	    തിരികെ c_parser_gimple_parentized_ternary_expression
			(parser, op_loc, VEC_PERM_വ്യഞ്ജകം);
	  അല്ലെങ്കിൽ എങ്കിൽ (strcmp (IDENTIFIER_POINTER (id), "__BIT_INSERT") == 0)
	    {
	      /* __BIT_INSERT '(' postfix-expression, postfix-expression,
			          integer ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      എങ്കിൽ (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_വ്യഞ്ജകം op0 = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_വ്യഞ്ജകം op1 = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_വ്യഞ്ജകം op2 = c_parser_gimple_postfix_expression (parser);
		  എങ്കിൽ (വൃക്ഷം_CODE (op2.മൂല്യം) != INTEGER_CST
		      || !int_fits_type_p (op2.മൂല്യം, bitsizetype))
		    c_parser_error (parser, "expected constant offset");
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  എങ്കിൽ (op0.മൂല്യം != error_mark_കണ്ണി
		      && op1.മൂല്യം != error_mark_കണ്ണി
		      && വൃക്ഷം_CODE (op2.മൂല്യം) == INTEGER_CST)
		    ret.മൂല്യം = build3_loc (loc, BIT_തിരുകുക_വ്യഞ്ജകം,
					    വൃക്ഷം_TYPE (op0.മൂല്യം),
					    op0.മൂല്യം, op1.മൂല്യം,
					    fold_convert (bitsizetype,
							  op2.മൂല്യം));
		}
	      തിരികെ ret;
	    }
	  അല്ലെങ്കിൽ
	    തിരികെ c_parser_gimple_postfix_expression (parser);
	}
    സ്ഥിരസ്ഥിതി:
      തിരികെ c_parser_gimple_postfix_expression (parser);
    }
}

/* Decompose ID into base name (ID until ver_offset) and VERSION.  Return
   true if ID matches a SSA name.  */

സ്ഥിതം തർക്കം
c_parser_parse_ssa_name_id (വൃക്ഷം id, unsigned *version, unsigned *ver_offset)
{
  സ്ഥിരം അക്ഷരം *token = IDENTIFIER_POINTER (id);
  സ്ഥിരം അക്ഷരം *var_version = strrchr (token, '_');
  എങ്കിൽ (! var_version)
    തിരികെ അസത്യം;

  *ver_offset = var_version - token;
  വേണ്ടി (സ്ഥിരം അക്ഷരം *p = var_version + 1; *p; ++p)
    എങ്കിൽ (! ISDIGIT (*p))
      തിരികെ അസത്യം;
  *version = atoi (var_version + 1);
  തിരികെ *version > 0;
}

/* Get at the actual SSA name ID with VERSION starting at VER_OFFSET.
   TYPE is the type if the SSA name is being declared.  */

സ്ഥിതം വൃക്ഷം
c_parser_parse_ssa_name (gimple_parser &parser,
			 വൃക്ഷം id, വൃക്ഷം type, unsigned version,
			 unsigned ver_offset)
{
  വൃക്ഷം name = NULL_വൃക്ഷം;
  സ്ഥിരം അക്ഷരം *token = IDENTIFIER_POINTER (id);

  എങ്കിൽ (ver_offset == 0)
    {
      /* Anonymous unnamed SSA name.  */
      എങ്കിൽ (version < അക്കം_ssa_names)
	name = ssa_name (version);
      എങ്കിൽ (! name)
	{
	  എങ്കിൽ (! type)
	    {
	      c_parser_error (parser, "SSA name undeclared");
	      തിരികെ error_mark_കണ്ണി;
	    }
	  name = make_ssa_name_fn (cfun, type, ശൂന്യ, version);
	}
    }
  അല്ലെങ്കിൽ
    {
      എങ്കിൽ (version < അക്കം_ssa_names)
	name = ssa_name (version);
      എങ്കിൽ (! name)
	{
	  /* Separate var name from version.  */
	  അക്ഷരം *var_name = XNEWVEC (അക്ഷരം, ver_offset + 1);
	  memcpy (var_name, token, ver_offset);
	  var_name[ver_offset] = '\0';
	  /* lookup for parent decl.  */
	  id = get_identifier (var_name);
	  വൃക്ഷം parent = lookup_name (id);
	  XDELETEVEC (var_name);
	  എങ്കിൽ (! parent || parent == error_mark_കണ്ണി)
	    {
	      c_parser_error (parser, "base variable or SSA name undeclared");
	      തിരികെ error_mark_കണ്ണി;
	    }
	  എങ്കിൽ (!(VAR_P (parent)
		|| വൃക്ഷം_CODE (parent) == PARM_DECL
		|| വൃക്ഷം_CODE (parent) == RESULT_DECL))
	    {
	      error ("invalid base %qE for SSA name", parent);
	      തിരികെ error_mark_കണ്ണി;
	    }
	  name = make_ssa_name_fn (cfun, parent,
				   gimple_build_nop (), version);
	}
    }

  തിരികെ name;
}

/* Parse a gimple call to an internal function.

   gimple-call-internal:
     . identifier ( gimple-argument-expression-list[opt] )  */

സ്ഥിതം ഘടന c_വ്യഞ്ജകം
c_parser_gimple_call_internal (gimple_parser &parser)
{
  ഘടന c_വ്യഞ്ജകം വ്യഞ്ജകം;
  വ്യഞ്ജകം.set_error ();

  gcc_assert (c_parser_next_token_is (parser, CPP_DOT));
  c_parser_consume_token (parser);
  location_t loc = c_parser_peek_token (parser)->location;
  എങ്കിൽ (!c_parser_next_token_is (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_kind != C_ID_ID)
    {
      c_parser_error (parser, "expecting internal function name");
      തിരികെ വ്യഞ്ജകം;
    }
  വൃക്ഷം id = c_parser_peek_token (parser)->മൂല്യം;
  internal_fn ifn = lookup_internal_fn (IDENTIFIER_POINTER (id));
  c_parser_consume_token (parser);
  എങ്കിൽ (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    {
      auto_vec<വൃക്ഷം> exprlist;
      എങ്കിൽ (!c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_gimple_വ്യഞ്ജകം_list (parser, &exprlist);
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      എങ്കിൽ (ifn == IFN_LAST)
	error_at (loc, "unknown internal function %qE", id);
      അല്ലെങ്കിൽ
	{
	  വ്യഞ്ജകം.മൂല്യം = build_call_വ്യഞ്ജകം_internal_loc_array
	    (loc, ifn, void_type_കണ്ണി, exprlist.length (),
	     exprlist.address ());
	  വ്യഞ്ജകം.original_code = ERROR_MARK;
	  വ്യഞ്ജകം.original_type = ശൂന്യ;
	  വ്യഞ്ജകം.m_decimal = 0;
	}
    }
  തിരികെ വ്യഞ്ജകം;
}

/* Parse '<' type [',' alignment] '>' and return a type on success
   and NULL_TREE on error.  */

സ്ഥിതം വൃക്ഷം
c_parser_gimple_typespec (gimple_parser &parser)
{
  ഘടന c_type_name *type_name = ശൂന്യ;
  വൃക്ഷം alignment = NULL_വൃക്ഷം;
  എങ്കിൽ (c_parser_require (parser, CPP_LESS, "expected %<<%>"))
    {
      type_name = c_parser_type_name (parser);
      /* Optional alignment.  */
      എങ്കിൽ (c_parser_next_token_is (parser, CPP_COMMA))
	{
	  c_parser_consume_token (parser);
	  alignment
	      = c_parser_gimple_postfix_expression (parser).മൂല്യം;
	}
      c_parser_skip_until_found (parser,
				 CPP_GREATER, "expected %<>%>");
    }
  എങ്കിൽ (!type_name)
    തിരികെ NULL_വൃക്ഷം;
  വൃക്ഷം tem;
  വൃക്ഷം type = groktypename (type_name, &tem, ശൂന്യ);
  എങ്കിൽ (alignment)
    type = build_aligned_type (type, വൃക്ഷം_to_uhwi (alignment));
  തിരികെ type;
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

സ്ഥിതം ഘടന c_വ്യഞ്ജകം
c_parser_gimple_postfix_expression (gimple_parser &parser, വൃക്ഷം ret_type)
{
  location_t loc = c_parser_peek_token (parser)->location;
  source_range tok_range = c_parser_peek_token (parser)->get_range ();
  ഘടന c_വ്യഞ്ജകം വ്യഞ്ജകം;
  വ്യഞ്ജകം.set_error ();
  തിരഞ്ഞെടുപ്പ് (c_parser_peek_token (parser)->type)
    {
    അവസ്ഥ CPP_സംഖ്യ:
      വ്യഞ്ജകം.മൂല്യം = c_parser_peek_token (parser)->മൂല്യം;
      set_c_വ്യഞ്ജകം_source_range (&വ്യഞ്ജകം, tok_range);
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      നിർത്തുക;
    അവസ്ഥ CPP_CHAR:
    അവസ്ഥ CPP_CHAR16:
    അവസ്ഥ CPP_CHAR32:
    അവസ്ഥ CPP_UTF8CHAR:
    അവസ്ഥ CPP_WCHAR:
      വ്യഞ്ജകം.മൂല്യം = c_parser_peek_token (parser)->മൂല്യം;
      set_c_വ്യഞ്ജകം_source_range (&വ്യഞ്ജകം, tok_range);
      c_parser_consume_token (parser);
      നിർത്തുക;
    അവസ്ഥ CPP_STRING:
    അവസ്ഥ CPP_STRING16:
    അവസ്ഥ CPP_STRING32:
    അവസ്ഥ CPP_WSTRING:
    അവസ്ഥ CPP_UTF8STRING:
      വ്യഞ്ജകം = c_parser_string_literal (parser, അസത്യം, സത്യം);
      നിർത്തുക;
    അവസ്ഥ CPP_DOT:
      വ്യഞ്ജകം = c_parser_gimple_call_internal (parser);
      നിർത്തുക;
    അവസ്ഥ CPP_NAME:
      എങ്കിൽ (c_parser_peek_token (parser)->id_kind == C_ID_ID)
	{
	  വൃക്ഷം id = c_parser_peek_token (parser)->മൂല്യം;
	  എങ്കിൽ (strcmp (IDENTIFIER_POINTER (id), "__MEM") == 0)
	    {
	      /* __MEM '<' type-name [ ',' number ] '>'
	               '(' [ '(' type-name ')' ] unary-expression
			   [ '+' number ]
			   [ ',' number ]
			   [ ',' number ':' number ] ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      വൃക്ഷം type = c_parser_gimple_typespec (parser);
	      ഘടന c_വ്യഞ്ജകം ptr, alias_off, step, index, index2;
	      ptr.മൂല്യം = error_mark_കണ്ണി;
	      alias_off.മൂല്യം = NULL_വൃക്ഷം;
	      step.മൂല്യം = NULL_വൃക്ഷം;
	      index.മൂല്യം = NULL_വൃക്ഷം;
	      index2.മൂല്യം = NULL_വൃക്ഷം;
	      unsigned short clique = 0;
	      unsigned short base = 0;
	      തർക്കം reverse_order = അസത്യം;
	      ഘടന c_വ്യഞ്ജകം ro;
	      എങ്കിൽ (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  വൃക്ഷം alias_type = NULL_വൃക്ഷം;
		  /* Optional alias-type cast.  */
		  എങ്കിൽ (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
		    {
		      c_parser_consume_token (parser);
		      ഘടന c_type_name *alias_type_name
			= c_parser_type_name (parser);
		      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
						 "expected %<)%>");
		      എങ്കിൽ (alias_type_name)
			{
			  വൃക്ഷം tem;
			  alias_type = groktypename (alias_type_name,
						     &tem, ശൂന്യ);
			}
		    }
		  ptr = c_parser_gimple_unary_expression (parser);
		  എങ്കിൽ (ptr.മൂല്യം == error_mark_കണ്ണി
		      || ! POINTER_TYPE_P (വൃക്ഷം_TYPE (ptr.മൂല്യം)))
		    {
		      എങ്കിൽ (ptr.മൂല്യം != error_mark_കണ്ണി)
			error_at (ptr.get_start (),
				  "invalid type of %<__MEM%> operand");
		      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
						 "expected %<)%>");
		      തിരികെ വ്യഞ്ജകം;
		    }
		  എങ്കിൽ (! alias_type)
		    alias_type = വൃക്ഷം_TYPE (ptr.മൂല്യം);
		  /* Optional constant offset.  */
		  എങ്കിൽ (c_parser_next_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      alias_off = c_parser_gimple_postfix_expression (parser);
		    }
		  എങ്കിൽ (c_parser_next_token_is (parser, CPP_MULT))
		    {
		      std::swap (index, alias_off);
		      c_parser_consume_token (parser);
		      step = c_parser_gimple_postfix_expression (parser);
		    }
		  അല്ലെങ്കിൽ എങ്കിൽ (c_parser_next_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      index = c_parser_gimple_postfix_expression (parser);
		      എങ്കിൽ (c_parser_next_token_is (parser, CPP_MULT))
			{
			  c_parser_consume_token (parser);
			  step = c_parser_gimple_postfix_expression (parser);
			}
		      അല്ലെങ്കിൽ
			std::swap (index, index2);
		    }
		  അല്ലെങ്കിൽ എങ്കിൽ (alias_off.മൂല്യം
			   && വൃക്ഷം_CODE (alias_off.മൂല്യം) != INTEGER_CST)
		    std::swap (alias_off, index2);
		  എങ്കിൽ (c_parser_next_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      index2 = c_parser_gimple_postfix_expression (parser);
		    }
		  എങ്കിൽ (alias_off.മൂല്യം)
		    {
		      എങ്കിൽ (വൃക്ഷം_CODE (alias_off.മൂല്യം) != INTEGER_CST)
			error_at (alias_off.get_start (),
				  "expected constant offset for %<__MEM%> "
				  "operand");
		      alias_off.മൂല്യം = fold_convert (alias_type,
						      alias_off.മൂല്യം);
		    }
		  അല്ലെങ്കിൽ
		    alias_off.മൂല്യം = build_int_cst (alias_type, 0);
		  എങ്കിൽ (step.മൂല്യം)
		    {
		      എങ്കിൽ (വൃക്ഷം_CODE (step.മൂല്യം) != INTEGER_CST)
			error_at (step.get_start (),
				  "expected constant step for %<__MEM%> "
				  "operand");
		    }
		  എങ്കിൽ (c_parser_next_token_is (parser, CPP_COMMA))
		    {
		      ഘടന c_വ്യഞ്ജകം cl, ba;
		      തർക്കം has_clb = സത്യം;
		      c_parser_consume_token (parser);
		      cl = c_parser_gimple_postfix_expression (parser);
		      എങ്കിൽ (!c_parser_next_token_is (parser, CPP_COLON))
			{
			  ro = cl;
			  unsigned HOST_WIDE_INT tmp = 0;
			  എങ്കിൽ (!വൃക്ഷം_fits_uhwi_p (ro.മൂല്യം)
			      || (tmp = വൃക്ഷം_to_uhwi (ro.മൂല്യം)) > 1)
			    error_at (ro.get_start (),
				      "invalid reverse order value");
			  reverse_order = tmp;
			  has_clb = അസത്യം;
			  എങ്കിൽ (c_parser_next_token_is (parser, CPP_COMMA))
			    {
			      c_parser_consume_token (parser);
			      cl = c_parser_gimple_postfix_expression (parser);
		              has_clb = സത്യം;
			    }
			}
		      എങ്കിൽ (has_clb
			  && c_parser_require (parser,
					       CPP_COLON, "expected %<:%>"))
			{
			  ba = c_parser_gimple_postfix_expression (parser);
			  എങ്കിൽ (!വൃക്ഷം_fits_uhwi_p (cl.മൂല്യം)
			      || !വൃക്ഷം_fits_uhwi_p (ba.മൂല്യം)
			      || compare_വൃക്ഷം_int (cl.മൂല്യം,
						   (clique = വൃക്ഷം_to_uhwi
								(cl.മൂല്യം)))
			      || compare_വൃക്ഷം_int (ba.മൂല്യം,
						   (base = വൃക്ഷം_to_uhwi
								 (ba.മൂല്യം))))
			    error_at (cl.get_start (),
				      "invalid clique/base pair");
			}
		    }
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      എങ്കിൽ (! type || c_parser_error (parser))
		{
		  c_parser_set_error (parser, അസത്യം);
		  തിരികെ വ്യഞ്ജകം;
		}
	      എങ്കിൽ (index.മൂല്യം || step.മൂല്യം || index2.മൂല്യം)
		വ്യഞ്ജകം.മൂല്യം = build5_loc (loc, TARGET_MEM_REF,
					 type, ptr.മൂല്യം, alias_off.മൂല്യം,
					 index.മൂല്യം, step.മൂല്യം, index2.മൂല്യം);
	      അല്ലെങ്കിൽ
		വ്യഞ്ജകം.മൂല്യം = build2_loc (loc, MEM_REF,
					 type, ptr.മൂല്യം, alias_off.മൂല്യം);
	      എങ്കിൽ (clique != 0)
		{
		  cfun->last_clique = MAX (cfun->last_clique, clique);
		  MR_DEPENDENCE_CLIQUE (വ്യഞ്ജകം.മൂല്യം) = clique;
		  MR_DEPENDENCE_BASE (വ്യഞ്ജകം.മൂല്യം) = base;
		}
	      എങ്കിൽ (reverse_order)
		{
		  എങ്കിൽ (വൃക്ഷം_CODE (വ്യഞ്ജകം.മൂല്യം) == MEM_REF)
		    REF_REVERSE_STORAGE_ORDER (വ്യഞ്ജകം.മൂല്യം) = reverse_order;
		  അല്ലെങ്കിൽ
		    error_at (ro.get_start (),
			      "target mem ref cannot have reverse order");
		}
	      നിർത്തുക;
	    }
	  അല്ലെങ്കിൽ എങ്കിൽ (strcmp (IDENTIFIER_POINTER (id), "__VIEW_CONVERT") == 0)
	    {
	      /* __VIEW_CONVERT '<' type-name [ ',' number ] '>'
	                        '(' postfix-expression ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      വൃക്ഷം type = c_parser_gimple_typespec (parser);
	      എങ്കിൽ (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_വ്യഞ്ജകം op = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  എങ്കിൽ (type && op.മൂല്യം != error_mark_കണ്ണി)
		    വ്യഞ്ജകം.മൂല്യം = build1_loc (loc, VIEW_CONVERT_വ്യഞ്ജകം,
					     type, op.മൂല്യം);
		}
	      നിർത്തുക;
	    }
	  അല്ലെങ്കിൽ എങ്കിൽ (strcmp (IDENTIFIER_POINTER (id), "__BIT_FIELD_REF") == 0)
	    {
	      /* __BIT_FIELD_REF '<' type-name [ ',' number ] '>'
	                        '(' postfix-expression, integer, integer ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      വൃക്ഷം type = c_parser_gimple_typespec (parser);
	      എങ്കിൽ (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_വ്യഞ്ജകം op0 = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_വ്യഞ്ജകം op1 = c_parser_gimple_postfix_expression (parser);
		  എങ്കിൽ (വൃക്ഷം_CODE (op1.മൂല്യം) != INTEGER_CST
		      || !int_fits_type_p (op1.മൂല്യം, bitsizetype))
		    c_parser_error (parser, "expected constant size");
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_വ്യഞ്ജകം op2 = c_parser_gimple_postfix_expression (parser);
		  എങ്കിൽ (വൃക്ഷം_CODE (op2.മൂല്യം) != INTEGER_CST
		      || !int_fits_type_p (op2.മൂല്യം, bitsizetype))
		    c_parser_error (parser, "expected constant offset");
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  എങ്കിൽ (type
		      && op0.മൂല്യം != error_mark_കണ്ണി
		      && വൃക്ഷം_CODE (op1.മൂല്യം) == INTEGER_CST
		      && വൃക്ഷം_CODE (op2.മൂല്യം) == INTEGER_CST)
		    വ്യഞ്ജകം.മൂല്യം = build3_loc (loc, BIT_FIELD_REF, type,
					     op0.മൂല്യം,
					     fold_convert (bitsizetype,
							   op1.മൂല്യം),
					     fold_convert (bitsizetype,
							   op2.മൂല്യം));
		}
	      നിർത്തുക;
	    }
	  അല്ലെങ്കിൽ എങ്കിൽ (strcmp (IDENTIFIER_POINTER (id), "__CLOBBER") == 0)
	    {
	      /* __CLOBBER [ '(' bob | eob | bos | eos ')' ]  */
	      clobber_kind kind = CLOBBER_UNDEF;
	      c_parser_consume_token (parser);
	      എങ്കിൽ (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
		{
		  c_parser_consume_token (parser);
		  auto tok = c_parser_peek_token (parser);
		  എങ്കിൽ (c_parser_require (parser, CPP_NAME,
					"expected clobber kind"))
		    {
		      സ്ഥിരം അക്ഷരം *kind_str = IDENTIFIER_POINTER (tok->മൂല്യം);
		      എങ്കിൽ (strcmp (kind_str, "bos") == 0)
			kind = CLOBBER_STORAGE_BEGIN;
		      അല്ലെങ്കിൽ എങ്കിൽ (strcmp (kind_str, "bob") == 0)
			kind = CLOBBER_OBJECT_BEGIN;
		      അല്ലെങ്കിൽ എങ്കിൽ (strcmp (kind_str, "eob") == 0)
			kind = CLOBBER_OBJECT_END;
		      അല്ലെങ്കിൽ എങ്കിൽ (strcmp (kind_str, "eos") == 0)
			kind = CLOBBER_STORAGE_END;
		      അല്ലെങ്കിൽ
			c_parser_error (parser, "expected one of %<bos%>, "
					"%<eos%>, %<bob>, %<eob%>");
		    }
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      /* We infer the (redundant) type from the LHS.  */
	      വ്യഞ്ജകം.മൂല്യം = build_clobber (ret_type, kind);
	      നിർത്തുക;
	    }
	  അല്ലെങ്കിൽ എങ്കിൽ (strcmp (IDENTIFIER_POINTER (id), "_Literal") == 0)
	    {
	      /* _Literal '(' type-name ')' ( [ '-' ] constant | constructor ) */
	      c_parser_consume_token (parser);
	      വൃക്ഷം type = NULL_വൃക്ഷം;
	      എങ്കിൽ (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  ഘടന c_type_name *type_name = c_parser_type_name (parser);
		  വൃക്ഷം tem;
		  എങ്കിൽ (type_name)
		    type = groktypename (type_name, &tem, ശൂന്യ);
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      എങ്കിൽ (! type)
		{
		  c_parser_error (parser, "invalid _Literal");
		  തിരികെ വ്യഞ്ജകം;
		}
	      എങ്കിൽ (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
		{
		  c_parser_consume_token (parser);
		  എങ്കിൽ (!AGGREGATE_TYPE_P (type)
		      && !VECTOR_TYPE_P (type))
		    {
		      c_parser_error (parser, "invalid type for _Literal with "
				      "constructor");
		      c_parser_skip_until_found (parser, CPP_CLOSE_BRACE,
						 "expected %<}%>");
		      തിരികെ വ്യഞ്ജകം;
		    }
		  vec<constructor_elt, va_gc> *v = ശൂന്യ;
		  തർക്കം constant_p = സത്യം;
		  എങ്കിൽ (VECTOR_TYPE_P (type)
		      && !c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
		    {
		      vec_alloc (v, TYPE_VECTOR_SUBPARTS (type).to_constant ());
		      ചെയ്യുക
			{
			  വൃക്ഷം val
			    = c_parser_gimple_postfix_expression (parser).മൂല്യം;
			  എങ്കിൽ (! val
			      || val == error_mark_കണ്ണി
			      || (! CONSTANT_CLASS_P (val)
				  && ! SSA_VAR_P (val)))
			    {
			      c_parser_error (parser, "invalid _Literal");
			      തിരികെ വ്യഞ്ജകം;
			    }
			  CONSTRUCTOR_APPEND_ELT (v, NULL_വൃക്ഷം, val);
			  എങ്കിൽ (! CONSTANT_CLASS_P (val))
			    constant_p = അസത്യം;
			  എങ്കിൽ (c_parser_next_token_is (parser, CPP_COMMA))
			    c_parser_consume_token (parser);
			  അല്ലെങ്കിൽ
			    നിർത്തുക;
			}
		      ആകുമ്പോൾ (1);
		    }
		  എങ്കിൽ (c_parser_require (parser, CPP_CLOSE_BRACE,
					"expected %<}%>"))
		    {
		      എങ്കിൽ (v && constant_p)
			വ്യഞ്ജകം.മൂല്യം = build_vector_from_ctor (type, v);
		      അല്ലെങ്കിൽ
			വ്യഞ്ജകം.മൂല്യം = build_constructor (type, v);
		    }
		  അല്ലെങ്കിൽ
		    {
		      c_parser_skip_until_found (parser, CPP_CLOSE_BRACE,
						 "expected %<}%>");
		      തിരികെ വ്യഞ്ജകം;
		    }
		}
	      അല്ലെങ്കിൽ
		{
		  തർക്കം neg_p, addr_p;
		  എങ്കിൽ ((neg_p = c_parser_next_token_is (parser, CPP_MINUS)))
		    c_parser_consume_token (parser);
		  എങ്കിൽ ((addr_p = c_parser_next_token_is (parser, CPP_AND)))
		    c_parser_consume_token (parser);
		  വൃക്ഷം val = c_parser_gimple_postfix_expression (parser).മൂല്യം;
		  എങ്കിൽ (! val
		      || val == error_mark_കണ്ണി
		      || (!CONSTANT_CLASS_P (val) && !addr_p))
		    {
		      c_parser_error (parser, "invalid _Literal");
		      തിരികെ വ്യഞ്ജകം;
		    }
		  എങ്കിൽ (addr_p)
		    {
		      val = build1 (ADDR_വ്യഞ്ജകം, type, val);
		      എങ്കിൽ (!is_gimple_invariant_address (val))
			{
			  c_parser_error (parser, "invalid _Literal");
			  തിരികെ വ്യഞ്ജകം;
			}
		    }
		  എങ്കിൽ (neg_p)
		    {
		      val = const_unop (NEGATE_വ്യഞ്ജകം, വൃക്ഷം_TYPE (val), val);
		      എങ്കിൽ (! val)
			{
			  c_parser_error (parser, "invalid _Literal");
			  തിരികെ വ്യഞ്ജകം;
			}
		    }
		  വ്യഞ്ജകം.മൂല്യം = fold_convert (type, val);
		}
	      തിരികെ വ്യഞ്ജകം;
	    }

	  /* SSA name.  */
	  unsigned version, ver_offset;
	  എങ്കിൽ (! lookup_name (id)
	      && c_parser_parse_ssa_name_id (id, &version, &ver_offset))
	    {
	      c_parser_consume_token (parser);
	      വ്യഞ്ജകം.മൂല്യം = c_parser_parse_ssa_name (parser, id, NULL_വൃക്ഷം,
						    version, ver_offset);
	      എങ്കിൽ (വ്യഞ്ജകം.മൂല്യം == error_mark_കണ്ണി)
		തിരികെ വ്യഞ്ജകം;
	      set_c_വ്യഞ്ജകം_source_range (&വ്യഞ്ജകം, tok_range);
	      /* For default definition SSA names.  */
	      എങ്കിൽ (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
		  && c_parser_peek_2nd_token (parser)->type == CPP_NAME
		  && strcmp ("D",
			     IDENTIFIER_POINTER
			       (c_parser_peek_2nd_token (parser)->മൂല്യം)) == 0
		  && c_parser_peek_nth_token (parser, 3)->type == CPP_CLOSE_PAREN)
		{
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		  എങ്കിൽ (! SSA_NAME_IS_DEFAULT_DEF (വ്യഞ്ജകം.മൂല്യം))
		    {
		      എങ്കിൽ (!SSA_NAME_VAR (വ്യഞ്ജകം.മൂല്യം))
			{
			  error_at (loc, "anonymous SSA name cannot have"
				    " default definition");
			  വ്യഞ്ജകം.മൂല്യം = error_mark_കണ്ണി;
			  തിരികെ വ്യഞ്ജകം;
			}
		      set_ssa_default_def (cfun, SSA_NAME_VAR (വ്യഞ്ജകം.മൂല്യം),
					   വ്യഞ്ജകം.മൂല്യം);
		      SSA_NAME_DEF_STMT (വ്യഞ്ജകം.മൂല്യം) = gimple_build_nop ();
		    }
		}
	    }
	  അല്ലെങ്കിൽ
	    {
	      c_parser_consume_token (parser);
	      വ്യഞ്ജകം.മൂല്യം
		= build_external_ref (loc, id,
				      (c_parser_peek_token (parser)->type
				       == CPP_OPEN_PAREN), &വ്യഞ്ജകം.original_type);
	      set_c_വ്യഞ്ജകം_source_range (&വ്യഞ്ജകം, tok_range);
	    }
	  നിർത്തുക;
	}
      /* Fallthru.  */
    സ്ഥിരസ്ഥിതി:
      c_parser_error (parser, "expected expression");
      വ്യഞ്ജകം.set_error ();
      നിർത്തുക;
    }
  എങ്കിൽ (വ്യഞ്ജകം.മൂല്യം == error_mark_കണ്ണി)
    തിരികെ വ്യഞ്ജകം;
  തിരികെ c_parser_gimple_postfix_expression_after_primary
    (parser, വ്യഞ്ജകം_LOC_OR_LOC (വ്യഞ്ജകം.മൂല്യം, loc), വ്യഞ്ജകം);
}

/* Parse a gimple postfix expression after the initial primary or compound
   literal.  */

സ്ഥിതം ഘടന c_വ്യഞ്ജകം
c_parser_gimple_postfix_expression_after_primary (gimple_parser &parser,
						  location_t വ്യഞ്ജകം_loc,
						  ഘടന c_വ്യഞ്ജകം വ്യഞ്ജകം)
{
  location_t start;
  location_t finish;
  വൃക്ഷം ident;
  location_t comp_loc;

  ആകുമ്പോൾ (സത്യം)
    {
      location_t op_loc = c_parser_peek_token (parser)->location;
      തിരഞ്ഞെടുപ്പ് (c_parser_peek_token (parser)->type)
	{
	അവസ്ഥ CPP_OPEN_SQUARE:
	  {
	    c_parser_consume_token (parser);
	    വൃക്ഷം idx = c_parser_gimple_unary_expression (parser).മൂല്യം;

	    എങ്കിൽ (! c_parser_require (parser, CPP_CLOSE_SQUARE, "expected %<]%>"))
	      {
		c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE, ശൂന്യ);
		നിർത്തുക;
	      }

	    start = വ്യഞ്ജകം.get_start ();
	    finish = c_parser_tokens_buf (parser, 0)->location;
	    വ്യഞ്ജകം.മൂല്യം = build_array_ref (op_loc, വ്യഞ്ജകം.മൂല്യം, idx);
	    set_c_വ്യഞ്ജകം_source_range (&വ്യഞ്ജകം, start, finish);
	    വ്യഞ്ജകം.m_decimal = 0;

	    വ്യഞ്ജകം.original_code = ERROR_MARK;
	    വ്യഞ്ജകം.original_type = ശൂന്യ;
	    നിർത്തുക;
	  }
	അവസ്ഥ CPP_OPEN_PAREN:
	  {
	    /* Function call.  */
	    c_parser_consume_token (parser);
	    auto_vec<വൃക്ഷം> exprlist;
	    എങ്കിൽ (! c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	      c_parser_gimple_വ്യഞ്ജകം_list (parser, &exprlist);
	    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    എങ്കിൽ (!FUNC_OR_METHOD_TYPE_P (വൃക്ഷം_TYPE (വ്യഞ്ജകം.മൂല്യം)))
	      {
		c_parser_error (parser, "invalid call to non-function");
		വ്യഞ്ജകം.set_error ();
		നിർത്തുക;
	      }
	    വ്യഞ്ജകം.മൂല്യം = build_call_array_loc
		(വ്യഞ്ജകം_loc, വൃക്ഷം_TYPE (വൃക്ഷം_TYPE (വ്യഞ്ജകം.മൂല്യം)),
		 വ്യഞ്ജകം.മൂല്യം, exprlist.length (), exprlist.address ());
	    വ്യഞ്ജകം.m_decimal = 0;
	    വ്യഞ്ജകം.original_code = ERROR_MARK;
	    വ്യഞ്ജകം.original_type = ശൂന്യ;
	    നിർത്തുക;
	  }
	അവസ്ഥ CPP_DOT:
	  {
	    /* Structure element reference.  */
	    c_parser_consume_token (parser);
	    എങ്കിൽ (c_parser_next_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		ident = comp_tok->മൂല്യം;
		comp_loc = comp_tok->location;
	      }
	    അല്ലെങ്കിൽ
	      {
		c_parser_error (parser, "expected identifier");
		വ്യഞ്ജകം.set_error ();
		വ്യഞ്ജകം.original_code = ERROR_MARK;
		വ്യഞ്ജകം.original_type = ശൂന്യ;
		തിരികെ വ്യഞ്ജകം;
	      }
	    start = വ്യഞ്ജകം.get_start ();
	    finish = c_parser_peek_token (parser)->get_finish ();
	    c_parser_consume_token (parser);
	    വ്യഞ്ജകം.മൂല്യം = build_component_ref (op_loc, വ്യഞ്ജകം.മൂല്യം, ident,
					      comp_loc, UNKNOWN_LOCATION);
	    set_c_വ്യഞ്ജകം_source_range (&വ്യഞ്ജകം, start, finish);
	    വ്യഞ്ജകം.m_decimal = 0;
	    വ്യഞ്ജകം.original_code = ERROR_MARK;
	    എങ്കിൽ (വൃക്ഷം_CODE (വ്യഞ്ജകം.മൂല്യം) != COMPONENT_REF)
	      വ്യഞ്ജകം.original_type = ശൂന്യ;
	    അല്ലെങ്കിൽ
	      {
		/* Remember the original type of a bitfield.  */
		വൃക്ഷം field = വൃക്ഷം_OPERAND (വ്യഞ്ജകം.മൂല്യം, 1);
		എങ്കിൽ (വൃക്ഷം_CODE (field) != FIELD_DECL)
		  വ്യഞ്ജകം.original_type = ശൂന്യ;
		അല്ലെങ്കിൽ
		  വ്യഞ്ജകം.original_type = DECL_BIT_FIELD_TYPE (field);
	      }
	    നിർത്തുക;
	  }
	അവസ്ഥ CPP_DEREF:
	  {
	    /* Structure element reference.  */
	    എങ്കിൽ (!POINTER_TYPE_P (വൃക്ഷം_TYPE (വ്യഞ്ജകം.മൂല്യം)))
	      {
		c_parser_error (parser, "dereference of non-pointer");
		വ്യഞ്ജകം.set_error ();
		വ്യഞ്ജകം.original_code = ERROR_MARK;
		വ്യഞ്ജകം.original_type = ശൂന്യ;
		തിരികെ വ്യഞ്ജകം;
	      }
	    c_parser_consume_token (parser);
	    എങ്കിൽ (c_parser_next_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		ident = comp_tok->മൂല്യം;
		comp_loc = comp_tok->location;
	      }
	    അല്ലെങ്കിൽ
	      {
		c_parser_error (parser, "expected identifier");
		വ്യഞ്ജകം.set_error ();
		വ്യഞ്ജകം.original_code = ERROR_MARK;
		വ്യഞ്ജകം.original_type = ശൂന്യ;
		തിരികെ വ്യഞ്ജകം;
	      }
	    start = വ്യഞ്ജകം.get_start ();
	    finish = c_parser_peek_token (parser)->get_finish ();
	    c_parser_consume_token (parser);
	    വ്യഞ്ജകം.മൂല്യം = build_component_ref (op_loc,
					      build_simple_mem_ref_loc
					        (op_loc, വ്യഞ്ജകം.മൂല്യം),
					      ident, comp_loc,
					      വ്യഞ്ജകം.get_location ());
	    set_c_വ്യഞ്ജകം_source_range (&വ്യഞ്ജകം, start, finish);
	    വ്യഞ്ജകം.m_decimal = 0;
	    വ്യഞ്ജകം.original_code = ERROR_MARK;
	    എങ്കിൽ (വൃക്ഷം_CODE (വ്യഞ്ജകം.മൂല്യം) != COMPONENT_REF)
	      വ്യഞ്ജകം.original_type = ശൂന്യ;
	    അല്ലെങ്കിൽ
	      {
		/* Remember the original type of a bitfield.  */
		വൃക്ഷം field = വൃക്ഷം_OPERAND (വ്യഞ്ജകം.മൂല്യം, 1);
		എങ്കിൽ (വൃക്ഷം_CODE (field) != FIELD_DECL)
		  വ്യഞ്ജകം.original_type = ശൂന്യ;
		അല്ലെങ്കിൽ
		  വ്യഞ്ജകം.original_type = DECL_BIT_FIELD_TYPE (field);
	      }
	    നിർത്തുക;
	  }
	സ്ഥിരസ്ഥിതി:
	  തിരികെ വ്യഞ്ജകം;
	}
    }
}

/* Parse expression list.

   gimple-expr-list:
     gimple-unary-expression
     gimple-expr-list , gimple-unary-expression

 */

സ്ഥിതം ശൂന്യം
c_parser_gimple_വ്യഞ്ജകം_list (gimple_parser &parser, vec<വൃക്ഷം> *ret)
{
  ഘടന c_വ്യഞ്ജകം വ്യഞ്ജകം;

  വ്യഞ്ജകം = c_parser_gimple_unary_expression (parser);
  ret->safe_തള്ളുക (വ്യഞ്ജകം.മൂല്യം);
  ആകുമ്പോൾ (c_parser_next_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      വ്യഞ്ജകം = c_parser_gimple_unary_expression (parser);
      ret->safe_തള്ളുക (വ്യഞ്ജകം.മൂല്യം);
    }
}

/* Parse gimple label.

   gimple-label:
     identifier :
     case constant-expression :
     default :

*/

സ്ഥിതം ശൂന്യം
c_parser_gimple_label (gimple_parser &parser, gimple_seq *seq)
{
  വൃക്ഷം name = c_parser_peek_token (parser)->മൂല്യം;
  location_t loc1 = c_parser_peek_token (parser)->location;
  gcc_assert (c_parser_next_token_is (parser, CPP_NAME));
  c_parser_consume_token (parser);
  gcc_assert (c_parser_next_token_is (parser, CPP_COLON));
  c_parser_consume_token (parser);
  വൃക്ഷം label = define_label (loc1, name);
  എങ്കിൽ (label)
    gimple_seq_add_stmt_without_update (seq, gimple_build_label (label));
  തിരികെ;
}

/* Parse gimple/RTL pass list.

   gimple-or-rtl-pass-list:
     startwith("pass-name")[,{cfg,ssa}]
 */

ശൂന്യം
c_parser_gimple_or_rtl_pass_list (c_parser *parser, c_declspecs *specs)
{
  അക്ഷരം *pass = ശൂന്യ;

  /* Accept __GIMPLE/__RTL.  */
  എങ്കിൽ (c_parser_next_token_is_not (parser, CPP_OPEN_PAREN))
    തിരികെ;
  c_parser_consume_token (parser);

  specs->entry_bb_എണ്ണം = profile_എണ്ണം::uninitialized ();
  ആകുമ്പോൾ (c_parser_next_token_is (parser, CPP_NAME))
    {
      profile_quality quality;
      സ്ഥിരം അക്ഷരം *op = IDENTIFIER_POINTER (c_parser_peek_token (parser)->മൂല്യം);
      c_parser_consume_token (parser);
      എങ്കിൽ (! strcmp (op, "startwith"))
	{
	  എങ്കിൽ (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    തിരികെ;
	  എങ്കിൽ (c_parser_next_token_is_not (parser, CPP_STRING))
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"expected pass name");
	      തിരികെ;
	    }
	  pass = xstrdup (വൃക്ഷം_STRING_POINTER
			  (c_parser_string_literal (parser, അസത്യം,
						    അസത്യം).മൂല്യം));
	  എങ്കിൽ (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<(%>"))
	    തിരികെ;
	}
      അല്ലെങ്കിൽ എങ്കിൽ (parse_profile_quality (op, &quality))
	{
	  വൃക്ഷം q;
	  എങ്കിൽ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    തിരികെ;

	  എങ്കിൽ (!c_parser_next_token_is (parser, CPP_സംഖ്യ)
	      || (വൃക്ഷം_CODE (q = c_parser_peek_token (parser)->മൂല്യം)
		  != INTEGER_CST))
	    {
	      c_parser_error (parser, "expected count value");
	      തിരികെ;
	    }

	  specs->entry_bb_എണ്ണം
	    = profile_എണ്ണം::from_gcov_type (വൃക്ഷം_INT_CST_താഴെയുള്ള (q), quality);
	  c_parser_consume_token (parser);
	  എങ്കിൽ (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    തിരികെ;
	}
      അല്ലെങ്കിൽ എങ്കിൽ (specs->declspec_il != cdil_gimple)
	/* Allow only one IL specifier and none on RTL.  */
	;
      അല്ലെങ്കിൽ എങ്കിൽ (! strcmp (op, "cfg"))
	specs->declspec_il = cdil_gimple_cfg;
      അല്ലെങ്കിൽ എങ്കിൽ (! strcmp (op, "ssa"))
	specs->declspec_il = cdil_gimple_ssa;
      അല്ലെങ്കിൽ
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "invalid operation");
	  തിരികെ;
	}
     എങ്കിൽ (c_parser_next_token_is (parser, CPP_COMMA))
       c_parser_consume_token (parser);
    }

  എങ്കിൽ (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    തിരികെ;

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

സ്ഥിതം ശൂന്യം
c_parser_gimple_declaration (gimple_parser &parser)
{
  ഘടന c_declarator *declarator;
  ഘടന c_declspecs *specs = build_null_declspecs ();
  c_parser_declspecs (parser, specs, സത്യം, സത്യം, സത്യം,
		      സത്യം, സത്യം, സത്യം, സത്യം, cla_nonabstract_decl);
  finish_declspecs (specs);

  /* Provide better error recovery.  Note that a type name here is usually
     better diagnosed as a redeclaration.  */
  എങ്കിൽ (c_parser_next_token_starts_declspecs (parser)
      && ! c_parser_next_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<;%>");
      c_parser_set_error (parser, അസത്യം);
      തിരികെ;
    }

  തർക്കം dummy = അസത്യം;
  declarator = c_parser_declarator (parser,
				    specs->typespec_kind != ctsk_none,
				    C_DTR_NORMAL, &dummy);

  എങ്കിൽ (!c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_error (parser, "expected %<;%>");
      തിരികെ;
    }
  എങ്കിൽ (declarator)
    {
      /* Handle SSA name decls specially, they do not go into the identifier
         table but we simply build the SSA name for later lookup.  */
      unsigned version, ver_offset;
      /* Handle SSA pointer declarations in a very simplistic ways, we
	 probably would like to call grokdeclarator in a special mode to
	 just build the type of the decl - start_decl already pushes
	 the identifier to the bindings for lookup, something we do not
	 want.  */
      ഘടന c_declarator *id_declarator = declarator;
      ആകുമ്പോൾ (id_declarator->kind == cdk_pointer)
	id_declarator = id_declarator->declarator;
      എങ്കിൽ (id_declarator->kind == cdk_id
	  && (declarator->kind == cdk_pointer
	      || is_gimple_reg_type (specs->type))
	  && c_parser_parse_ssa_name_id (id_declarator->u.id.id,
					 &version, &ver_offset)
	  /* The following restricts it to unnamed anonymous SSA names
	     which fails parsing of named ones in dumps (we could
	     decide to not dump their name for -gimple).  */
	  && ver_offset == 0)
	{
	  ഘടന c_declarator *p = declarator;
	  വൃക്ഷം type = specs->type;
	  ആകുമ്പോൾ (p->kind == cdk_pointer)
	    {
	      type = build_pointer_type (type);
	      p = p->declarator;
	    }
	  c_parser_parse_ssa_name (parser, id_declarator->u.id.id, type,
				   version, ver_offset);
	}
      അല്ലെങ്കിൽ
	{
	  വൃക്ഷം postfix_attrs = NULL_വൃക്ഷം;
	  വൃക്ഷം all_prefix_attrs = specs->attrs;
	  specs->attrs = ശൂന്യ;
	  വൃക്ഷം decl = start_decl (declarator, specs, അസത്യം,
				  chainon (postfix_attrs, all_prefix_attrs));
	  എങ്കിൽ (decl)
	    finish_decl (decl, UNKNOWN_LOCATION, NULL_വൃക്ഷം, NULL_വൃക്ഷം,
			 NULL_വൃക്ഷം);
	}
    }
}

/* Parse gimple goto statement.  */

സ്ഥിതം ശൂന്യം
c_parser_gimple_goto_stmt (gimple_parser &parser,
			   location_t loc, വൃക്ഷം label, gimple_seq *seq)
{
  എങ്കിൽ (cfun->curr_properties & PROP_cfg)
    {
      പൂർണ്ണസംഖ്യ dest_index;
      profile_probability prob;
      എങ്കിൽ (c_parser_gimple_parse_bb_spec_edge_probability (label, parser,
							  &dest_index, &prob))
	{
	  parser.തള്ളുക_edge (parser.current_bb->index, dest_index,
			    EDGE_FALLTHRU, prob);
	  തിരികെ;
	}
    }
  വൃക്ഷം decl = lookup_label_for_goto (loc, label);
  gimple_seq_add_stmt_without_update (seq, gimple_build_goto (decl));
}

/* Parse a parenthesized condition.
   gimple-condition:
     ( gimple-binary-expression )    */

സ്ഥിതം വൃക്ഷം
c_parser_gimple_paren_condition (gimple_parser &parser)
{
  എങ്കിൽ (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    തിരികെ error_mark_കണ്ണി;
  വൃക്ഷം cond
    = c_parser_gimple_ദ്വിമാന_expression (parser, boolean_type_കണ്ണി).മൂല്യം;
  എങ്കിൽ (cond != error_mark_കണ്ണി
      && ! COMPARISON_CLASS_P (cond)
      && ! CONSTANT_CLASS_P (cond)
      && ! SSA_VAR_P (cond))
    {
      c_parser_error (parser, "comparison required");
      cond = error_mark_കണ്ണി;
    }
  എങ്കിൽ (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    തിരികെ error_mark_കണ്ണി;
  തിരികെ cond;
}

/* Parse gimple try statement.

   try-statement:
     try { ... } finally { ... }
     try { ... } finally { ... } else { ... }

   This could support try/catch as well, but it's not implemented yet.
 */

സ്ഥിതം ശൂന്യം
c_parser_gimple_try_stmt (gimple_parser &parser, gimple_seq *seq)
{
  gimple_seq tryseq = ശൂന്യ;
  c_parser_consume_token (parser);
  c_parser_gimple_compound_statement (parser, &tryseq);

  എങ്കിൽ ((c_parser_next_token_is (parser, CPP_KEYWORD)
       && c_parser_peek_token (parser)->keyword == RID_AT_FINALLY)
      || (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_token (parser)->id_kind == C_ID_ID
	  && strcmp (IDENTIFIER_POINTER (c_parser_peek_token (parser)->മൂല്യം),
		     "finally") == 0))
    {
      gimple_seq finseq = ശൂന്യ;
      c_parser_consume_token (parser);
      c_parser_gimple_compound_statement (parser, &finseq);

      എങ്കിൽ (c_parser_next_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_ELSE)
	{
	  gimple_seq elsseq = ശൂന്യ;
	  c_parser_consume_token (parser);
	  c_parser_gimple_compound_statement (parser, &elsseq);

	  geh_else *stmt = gimple_build_eh_else (finseq, elsseq);
	  finseq = ശൂന്യ;
	  gimple_seq_add_stmt_without_update (&finseq, stmt);
	}

      gtry *stmt = gimple_build_try (tryseq, finseq, GIMPLE_TRY_FINALLY);
      gimple_seq_add_stmt_without_update (seq, stmt);
    }
  അല്ലെങ്കിൽ എങ്കിൽ (c_parser_next_token_is (parser, CPP_KEYWORD)
      && c_parser_peek_token (parser)->keyword == RID_AT_CATCH)
    c_parser_error (parser, "%<catch%> is not supported");
  അല്ലെങ്കിൽ
    c_parser_error (parser, "expected %<finally%> or %<catch%>");
}

/* Parse gimple if-else statement.

   if-statement:
     if ( gimple-binary-expression ) gimple-goto-statement
     if ( gimple-binary-expression ) gimple-goto-statement \
					else gimple-goto-statement
 */

സ്ഥിതം ശൂന്യം
c_parser_gimple_if_stmt (gimple_parser &parser, gimple_seq *seq)
{
  വൃക്ഷം t_label = NULL_വൃക്ഷം, f_label = NULL_വൃക്ഷം, label;
  location_t loc;
  c_parser_consume_token (parser);
  വൃക്ഷം cond = c_parser_gimple_paren_condition (parser);

  എങ്കിൽ (c_parser_next_token_is_keyword (parser, RID_GOTO))
    {
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      എങ്കിൽ (! c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected label");
	  തിരികെ;
	}
      label = c_parser_peek_token (parser)->മൂല്യം;
      c_parser_consume_token (parser);
      പൂർണ്ണസംഖ്യ dest_index;
      profile_probability prob;
      എങ്കിൽ ((cfun->curr_properties & PROP_cfg)
	  && c_parser_gimple_parse_bb_spec_edge_probability (label, parser,
							     &dest_index, &prob))
	parser.തള്ളുക_edge (parser.current_bb->index, dest_index,
			  EDGE_TRUE_മൂല്യം, prob);
      അല്ലെങ്കിൽ
	t_label = lookup_label_for_goto (loc, label);
      എങ്കിൽ (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	തിരികെ;
    }
  അല്ലെങ്കിൽ
    {
      c_parser_error (parser, "expected goto expression");
      തിരികെ;
    }

  എങ്കിൽ (c_parser_next_token_is_keyword (parser, RID_ELSE))
    c_parser_consume_token (parser);
  അല്ലെങ്കിൽ
    {
      c_parser_error (parser, "expected else statement");
      തിരികെ;
    }

  എങ്കിൽ (c_parser_next_token_is_keyword (parser, RID_GOTO))
    {
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      എങ്കിൽ (! c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected label");
	  തിരികെ;
	}
      label = c_parser_peek_token (parser)->മൂല്യം;
      c_parser_consume_token (parser);
      പൂർണ്ണസംഖ്യ dest_index;
      profile_probability prob;
      എങ്കിൽ ((cfun->curr_properties & PROP_cfg)
	  && c_parser_gimple_parse_bb_spec_edge_probability (label, parser,
							     &dest_index, &prob))
	parser.തള്ളുക_edge (parser.current_bb->index, dest_index,
			  EDGE_FALSE_മൂല്യം, prob);
      അല്ലെങ്കിൽ
	f_label = lookup_label_for_goto (loc, label);
      എങ്കിൽ (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	തിരികെ;
    }
  അല്ലെങ്കിൽ
    {
      c_parser_error (parser, "expected goto expression");
      തിരികെ;
    }

  എങ്കിൽ (cond != error_mark_കണ്ണി)
    gimple_seq_add_stmt_without_update (seq, gimple_build_cond_from_വൃക്ഷം (cond, t_label,
							   f_label));
}

/* Parse gimple switch-statement.

   gimple-switch-statement:
     switch (gimple-postfix-expression) gimple-case-statement

   gimple-case-statement:
     gimple-case-statement
     gimple-label-statement : gimple-goto-statement
*/

സ്ഥിതം ശൂന്യം
c_parser_gimple_switch_stmt (gimple_parser &parser, gimple_seq *seq)
{
  c_വ്യഞ്ജകം cond_വ്യഞ്ജകം;
  വൃക്ഷം case_label, label;
  auto_vec<വൃക്ഷം> labels;
  വൃക്ഷം default_label = NULL_വൃക്ഷം;
  c_parser_consume_token (parser);

  എങ്കിൽ (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    തിരികെ;
  cond_വ്യഞ്ജകം = c_parser_gimple_postfix_expression (parser);
  എങ്കിൽ (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    തിരികെ;

  എങ്കിൽ (! c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    തിരികെ;

  ആകുമ്പോൾ (c_parser_next_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      എങ്കിൽ (c_parser_next_token_is (parser, CPP_EOF))
	{
	  c_parser_error (parser, "expected statement");
	  തിരികെ;
	}

      തിരഞ്ഞെടുപ്പ് (c_parser_peek_token (parser)->keyword)
	{
	അവസ്ഥ RID_CASE:
	  {
	    c_വ്യഞ്ജകം exp1;
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);

	    എങ്കിൽ (c_parser_next_token_is (parser, CPP_NAME)
		|| c_parser_peek_token (parser)->type == CPP_സംഖ്യ)
	      exp1 = c_parser_gimple_postfix_expression (parser);
	    അല്ലെങ്കിൽ
	      {
		c_parser_error (parser, "expected expression");
		തിരികെ;
	      }

	    എങ്കിൽ (c_parser_next_token_is (parser, CPP_COLON))
	      {
		c_parser_consume_token (parser);
		എങ്കിൽ (c_parser_next_token_is (parser, CPP_NAME))
		  {
		    label = c_parser_peek_token (parser)->മൂല്യം;
		    c_parser_consume_token (parser);
		    വൃക്ഷം decl = lookup_label_for_goto (loc, label);
		    case_label = build_case_label (exp1.മൂല്യം, NULL_വൃക്ഷം,
						   decl);
		    labels.safe_തള്ളുക (case_label);
		    എങ്കിൽ (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      തിരികെ;
		  }
		അല്ലെങ്കിൽ എങ്കിൽ (! c_parser_require (parser, CPP_NAME,
					     "expected label"))
		  തിരികെ;
	      }
	    അല്ലെങ്കിൽ എങ്കിൽ (! c_parser_require (parser, CPP_SEMICOLON,
					 "expected %<:%>"))
	      തിരികെ;
	    നിർത്തുക;
	  }
	അവസ്ഥ RID_DEFAULT:
	  {
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);
	    എങ്കിൽ (c_parser_next_token_is (parser, CPP_COLON))
	      {
		c_parser_consume_token (parser);
		എങ്കിൽ (c_parser_next_token_is (parser, CPP_NAME))
		  {
		    label = c_parser_peek_token (parser)->മൂല്യം;
		    c_parser_consume_token (parser);
		    വൃക്ഷം decl = lookup_label_for_goto (loc, label);
		    default_label = build_case_label (NULL_വൃക്ഷം, NULL_വൃക്ഷം,
						      decl);
		    എങ്കിൽ (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      തിരികെ;
		  }
		അല്ലെങ്കിൽ എങ്കിൽ (! c_parser_require (parser, CPP_NAME,
					     "expected label"))
		  തിരികെ;
	      }
	    അല്ലെങ്കിൽ എങ്കിൽ (! c_parser_require (parser, CPP_SEMICOLON,
					 "expected %<:%>"))
	      തിരികെ;
	    നിർത്തുക;
	  }
	സ്ഥിരസ്ഥിതി:
	  c_parser_error (parser, "expected case label");
	  തിരികെ;
	}

    }
  എങ്കിൽ (! c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>"))
    തിരികെ;

  എങ്കിൽ (cond_വ്യഞ്ജകം.മൂല്യം != error_mark_കണ്ണി)
    {
      gswitch *s = gimple_build_switch (cond_വ്യഞ്ജകം.മൂല്യം, default_label, labels);
      gimple_seq_add_stmt_without_update (seq, s);
    }
}

/* Parse gimple return statement.  */

സ്ഥിതം ശൂന്യം
c_parser_gimple_return_stmt (gimple_parser &parser, gimple_seq *seq)
{
  location_t loc = c_parser_peek_token (parser)->location;
  gimple *ret = ശൂന്യ;
  c_parser_consume_token (parser);
  എങ്കിൽ (c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      c_finish_gimple_return (loc, NULL_വൃക്ഷം);
      ret = gimple_build_return (ശൂന്യ);
      gimple_seq_add_stmt_without_update (seq, ret);
    }
  അല്ലെങ്കിൽ
    {
      location_t xloc = c_parser_peek_token (parser)->location;
      c_വ്യഞ്ജകം വ്യഞ്ജകം = c_parser_gimple_unary_expression (parser);
      എങ്കിൽ (വ്യഞ്ജകം.മൂല്യം != error_mark_കണ്ണി)
	{
	  c_finish_gimple_return (xloc, വ്യഞ്ജകം.മൂല്യം);
	  ret = gimple_build_return (വ്യഞ്ജകം.മൂല്യം);
	  gimple_seq_add_stmt_without_update (seq, ret);
	}
    }
}

/* Support function for c_parser_gimple_return_stmt.  */

സ്ഥിതം ശൂന്യം
c_finish_gimple_return (location_t loc, വൃക്ഷം retval)
{
  വൃക്ഷം valtype = വൃക്ഷം_TYPE (വൃക്ഷം_TYPE (current_function_decl));

  /* Use the expansion point to handle cases such as returning NULL
     in a function returning void.  */
  location_t xloc = expansion_point_location_if_in_system_header (loc);

  എങ്കിൽ (വൃക്ഷം_THIS_VOLATILE (current_function_decl))
    warning_at (xloc, 0,
		"function declared %<noreturn%> has a %<return%> statement");

  എങ്കിൽ (! retval)
    current_function_returns_null = 1;
  അല്ലെങ്കിൽ എങ്കിൽ (valtype == 0 || VOID_TYPE_P (valtype))
    {
      current_function_returns_null = 1;
      എങ്കിൽ (വൃക്ഷം_CODE (വൃക്ഷം_TYPE (retval)) != VOID_TYPE)
	{
	  error_at
	    (xloc, "%<return%> with a value, in function returning void");
	  inform (DECL_SOURCE_LOCATION (current_function_decl),
		  "declared here");
	}
    }
  അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_CODE (valtype) != വൃക്ഷം_CODE (വൃക്ഷം_TYPE (retval)))
    {
      error_at
	(xloc, "invalid conversion in return statement");
      inform (DECL_SOURCE_LOCATION (current_function_decl),
	      "declared here");
    }
  തിരികെ;
}
