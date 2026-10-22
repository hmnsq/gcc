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

#અન્તર્ભાવ "config.h"
#અન્તર્ભાવ "system.h"
#અન્તર્ભાવ "coretypes.h"
#અન્તર્ભાવ "target.h"
#અન્તર્ભાવ "function.h"
#અન્તર્ભાવ "c-tree.h"
#અન્તર્ભાવ "timevar.h"
#અન્તર્ભાવ "stringpool.h"
#અન્તર્ભાવ "cgraph.h"
#અન્તર્ભાવ "attribs.h"
#અન્તર્ભાવ "stor-layout.h"
#અન્તર્ભાવ "varasm.h"
#અન્તર્ભાવ "trans-mem.h"
#અન્તર્ભાવ "c-family/c-pragma.h"
#અન્તર્ભાવ "c-lang.h"
#અન્તર્ભાવ "c-family/c-objc.h"
#અન્તર્ભાવ "plugin.h"
#અન્તર્ભાવ "builtins.h"
#અન્તર્ભાવ "gomp-constants.h"
#અન્તર્ભાવ "c-family/c-indentation.h"
#અન્તર્ભાવ "gimple-expr.h"
#અન્તર્ભાવ "context.h"
#અન્તર્ભાવ "gcc-rich-location.h"
#અન્તર્ભાવ "c-parser.h"
#અન્તર્ભાવ "tree-vrp.h"
#અન્તર્ભાવ "tree-pass.h"
#અન્તર્ભાવ "tree-pretty-print.h"
#અન્તર્ભાવ "tree.h"
#અન્તર્ભાવ "basic-block.h"
#અન્તર્ભાવ "gimple.h"
#અન્તર્ભાવ "gimple-pretty-print.h"
#અન્તર્ભાવ "tree-ssa.h"
#અન્તર્ભાવ "pass_manager.h"
#અન્તર્ભાવ "tree-ssanames.h"
#અન્તર્ભાવ "gimple-ssa.h"
#અન્તર્ભાવ "tree-dfa.h"
#અન્તર્ભાવ "internal-fn.h"
#અન્તર્ભાવ "cfg.h"
#અન્તર્ભાવ "cfghooks.h"
#અન્તર્ભાવ "bitmap.h"
#અન્તર્ભાવ "cfganal.h"
#અન્તર્ભાવ "tree-cfg.h"
#અન્તર્ભાવ "gimple-iterator.h"
#અન્તર્ભાવ "cfgloop.h"
#અન્તર્ભાવ "tree-phinodes.h"
#અન્તર્ભાવ "tree-into-ssa.h"


/* GIMPLE parser state.  */

વર્ગ gimple_parser
{
જાહેર:
  gimple_parser (c_parser *p) : parser (p), edges(), current_bb(ખાલી) {}
  /* c_parser is not visible here, use composition and fake inheritance
     via a conversion operator.  */
  operator c_parser *() { પાછા parser; }
  c_parser *parser;

  /* CFG build state.  */
  વર્ગ gimple_parser_edge
  {
  જાહેર:
    પૂર્ણાંક src;
    પૂર્ણાંક dest;
    પૂર્ણાંક flags;
    profile_probability probability;
  };
  auto_vec<gimple_parser_edge> edges;
  basic_block current_bb;

  શૂન્ય ધકેલો_edge (પૂર્ણાંક, પૂર્ણાંક, પૂર્ણાંક, profile_probability);
};

શૂન્ય
gimple_parser::ધકેલો_edge (પૂર્ણાંક src, પૂર્ણાંક dest, પૂર્ણાંક flags,
			  profile_probability prob)
{
  gimple_parser_edge e;
  e.src = src;
  e.dest = dest;
  e.flags = flags;
  e.probability = prob;
  edges.safe_ધકેલો (e);
}


/* Gimple parsing functions.  */
સ્થિર તાર્કિક c_parser_gimple_compound_statement (gimple_parser &, gimple_seq *);
સ્થિર શૂન્ય c_parser_gimple_label (gimple_parser &, gimple_seq *);
સ્થિર શૂન્ય c_parser_gimple_statement (gimple_parser &, gimple_seq *);
સ્થિર સંરચના c_પદાવલિ c_parser_gimple_દ્વિઅંકી_expression (gimple_parser &, વૃક્ષ);
સ્થિર સંરચના c_પદાવલિ c_parser_gimple_unary_expression (gimple_parser &);
સ્થિર સંરચના c_પદાવલિ c_parser_gimple_postfix_expression
			(gimple_parser &, વૃક્ષ = error_mark_ગાંઠ);
સ્થિર સંરચના c_પદાવલિ c_parser_gimple_postfix_expression_after_primary
			(gimple_parser &, location_t, સંરચના c_પદાવલિ);
સ્થિર શૂન્ય c_parser_gimple_declaration (gimple_parser &);
સ્થિર શૂન્ય c_parser_gimple_goto_stmt (gimple_parser &, location_t,
				       વૃક્ષ, gimple_seq *);
સ્થિર શૂન્ય c_parser_gimple_try_stmt (gimple_parser &, gimple_seq *);
સ્થિર શૂન્ય c_parser_gimple_if_stmt (gimple_parser &, gimple_seq *);
સ્થિર શૂન્ય c_parser_gimple_switch_stmt (gimple_parser &, gimple_seq *);
સ્થિર શૂન્ય c_parser_gimple_return_stmt (gimple_parser &, gimple_seq *);
સ્થિર શૂન્ય c_finish_gimple_return (location_t, વૃક્ષ);
સ્થિર વૃક્ષ c_parser_gimple_paren_condition (gimple_parser &);
સ્થિર શૂન્ય c_parser_gimple_પદાવલિ_list (gimple_parser &, vec<વૃક્ષ> *);


/* Much like parser_build_unary_op, but avoid applying default conversions.  */

સ્થિર c_પદાવલિ
gimple_parser_build_unary_op (location_t loc,
			      ગણના વૃક્ષ_code code, સંરચના c_પદાવલિ arg)
{
  સંરચના c_પદાવલિ result;

  result.original_code = code;
  result.original_type = ખાલી;
  result.m_decimal = 0;

  જો (reject_gcc_builtin (arg.કિંમત))
    {
      result.કિંમત = error_mark_ગાંઠ;
    }
  નહીંતર
    {
      result.કિંમત = build_unary_op (loc, code, arg.કિંમત, સાચું);

      જો (વૃક્ષ_OVERFLOW_P (result.કિંમત) && !વૃક્ષ_OVERFLOW_P (arg.કિંમત))
	overflow_warning (loc, result.કિંમત, arg.કિંમત);
    }

  /* We are typically called when parsing a prefix token at LOC acting on
     ARG.  Reflect this by updating the source range of the result to
     start at LOC and end at the end of ARG.  */
  set_c_પદાવલિ_source_range (&result,
			   loc, arg.get_finish ());

  પાછા result;
}

/* See if VAL is an identifier matching __BB<num> and return <num>
   in *INDEX.  */

સ્થિર તાર્કિક
c_parser_gimple_parse_bb_spec (વૃક્ષ val, પૂર્ણાંક *index)
{
  જો (!startswith (IDENTIFIER_POINTER (val), "__BB"))
    પાછા ખોટું;

  અચલ અક્ષર *bb = IDENTIFIER_POINTER (val) + 4;
  જો (! ISDIGIT (*bb))
    પાછા ખોટું;

  અક્ષર *pend;
  errno = 0;
  અચલ unsigned long સંખ્યા = strtoul (bb, &pend, 10);
  જો (errno == ERANGE
      || *pend != '\0'
      || સંખ્યા > INT_MAX)
    પાછા ખોટું;

  *index = સંખ્યા;
  પાછા સાચું;
}

/* See if VAL is an identifier matching __BB<num> and return <num>
   in *INDEX.  Return true if so and parse also FREQUENCY of
   the edge.  */


સ્થિર તાર્કિક
c_parser_gimple_parse_bb_spec_edge_probability (વૃક્ષ val,
						gimple_parser &parser,
						પૂર્ણાંક *index,
						profile_probability
						*probability)
{
  તાર્કિક return_p = c_parser_gimple_parse_bb_spec (val, index);
  જો (return_p)
    {
      *probability = profile_probability::uninitialized ();
      /* Parse frequency if provided.  */
      જો (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	{
	  વૃક્ષ f;
	  c_parser_consume_token (parser);
	  જો (!c_parser_next_token_is (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected frequency quality");
	      પાછા ખોટું;
	    }

	  profile_quality quality;
	  અચલ અક્ષર *v
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત);
	  જો (!parse_profile_quality (v, &quality))
	    {
	      c_parser_error (parser, "unknown profile quality");
	      પાછા ખોટું;
	    }

	  c_parser_consume_token (parser);
	  જો (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    પાછા ખોટું;

	  જો (!c_parser_next_token_is (parser, CPP_સંખ્યા)
	      || (વૃક્ષ_CODE (f = c_parser_peek_token (parser)->કિંમત)
		  != INTEGER_CST))
	    {
	      c_parser_error (parser, "expected frequency value");
	      પાછા ખોટું;
	    }

	  unsigned પૂર્ણાંક કિંમત = વૃક્ષ_INT_CST_નીચલું (f);
	  *probability = profile_probability (કિંમત, quality);

	  c_parser_consume_token (parser);
	  જો (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    પાછા ખોટું;

	  જો (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    પાછા ખોટું;
	}

      પાછા સાચું;
    }

  પાછા ખોટું;

}

/* Parse the body of a function declaration marked with "__GIMPLE".  */

શૂન્ય
c_parser_parse_gimple_body (c_parser *cparser, અક્ષર *gimple_pass,
			    ગણના c_declspec_il cdil,
			    profile_ગણતરી entry_bb_ગણતરી)
{
  gimple_parser parser (cparser);
  gimple_seq seq = ખાલી;
  gimple_seq body = ખાલી;
  વૃક્ષ stmt = ધકેલો_stmt_list ();
  ધકેલો_scope ();
  location_t loc1 = c_parser_peek_token (parser)->location;

  cfun->pass_startwith = gimple_pass;
  init_વૃક્ષ_ssa (cfun);

  જો (cdil == cdil_gimple)
    /* While we have SSA names in the IL we do not have a CFG built yet
       and PHIs are represented using a PHI internal function.  We do
       have lowered control flow and exception handling (well, we do not
       have parser support for EH yet).  But as we still have BINDs
       we have to go through lowering again.  */
    cfun->curr_properties = PROP_gimple_any;
  નહીંતર
    {
      /* We have at least cdil_gimple_cfg.  */
      gimple_register_cfg_hooks ();
      init_empty_વૃક્ષ_cfg ();
      parser.current_bb = ENTRY_BLOCK_PTR_FOR_FN (cfun);
      /* Initialize the bare loop structure - we are going to only
         mark headers and leave the rest to fixup.  */
      set_loops_for_fn (cfun, ggc_cleared_alloc<સંરચના loops> ());
      init_loops_structure (cfun, loops_for_fn (cfun), 1);
      loops_state_set (cfun, LOOPS_NEED_FIXUP|LOOPS_MAY_HAVE_MULTIPLE_LATCHES);
      cfun->curr_properties
	|= PROP_gimple_lcf | PROP_gimple_leh | PROP_cfg | PROP_loops;
      જો (cdil == cdil_gimple_ssa)
	{
	  init_ssa_operands (cfun);
	  cfun->curr_properties |= PROP_ssa;
	}
    }

  જો (! c_parser_gimple_compound_statement (parser, &seq)
      && cdil == cdil_gimple)
    {
      gimple *ret = gimple_build_return (ખાલી);
      gimple_seq_add_stmt_without_update (&seq, ret);
    }

  વૃક્ષ block = કાઢો_scope ();
  stmt = કાઢો_stmt_list (stmt);
  stmt = c_build_bind_પદાવલિ (loc1, block, stmt);

  block = DECL_INITIAL (current_function_decl);
  BLOCK_SUBBLOCKS (block) = NULL_વૃક્ષ;
  BLOCK_CHAIN (block) = NULL_વૃક્ષ;
  વૃક્ષ_ASM_WRITTEN (block) = 1;

  જો (cdil == cdil_gimple)
    {
      gbind *bind_stmt = gimple_build_bind (BIND_પદાવલિ_VARS (stmt), ખાલી,
					    BIND_પદાવલિ_BLOCK (stmt));
      gimple_bind_set_body (bind_stmt, seq);
      gimple_seq_add_stmt_without_update (&body, bind_stmt);
      gimple_set_body (current_function_decl, body);
    }
  નહીંતર
    {
      /* Control-flow and binds are lowered, record local decls.  */
      માટે (વૃક્ષ var = BIND_પદાવલિ_VARS (stmt); var; var = DECL_CHAIN (var))
	જો (VAR_P (var)
	    && !DECL_EXTERNAL (var))
	  {
	    add_local_decl (cfun, var);
	    /* When the middle-end re-gimplifies any expression we might
	       run into the assertion that we've seen the decl in a BIND.  */
	    જો (!વૃક્ષ_STATIC (var))
	      DECL_SEEN_IN_BIND_પદાવલિ_P (var) = 1;
	  }
      /* We have a CFG.  Build the edges.  */
      માટે (unsigned i = 0; i < parser.edges.length (); ++i)
	{
	  edge e = make_edge (BASIC_BLOCK_FOR_FN (cfun, parser.edges[i].src),
			      BASIC_BLOCK_FOR_FN (cfun, parser.edges[i].dest),
			      parser.edges[i].flags);
	  e->probability = parser.edges[i].probability;
	}
      /* Add edges for case labels.  */
      basic_block bb;
      FOR_EACH_BB_FN (bb, cfun)
	જો (EDGE_ગણતરી (bb->succs) == 0)
	  {
	    જો (gswitch *sw = safe_dyn_cast <gswitch *> (*gsi_last_bb (bb)))
	      માટે (unsigned i = 0; i < gimple_switch_અંક_labels (sw); ++i)
		{
		  basic_block label_bb = gimple_switch_label_bb (cfun, sw, i);
		  make_edge (bb, label_bb, 0);
		}
	  }
      /* Need those for loop fixup.  */
      calculate_dominance_info (CDI_DOMINATORS);
      /* With SSA lower PHIs parsed as internal function calls and
	 update stmts.  */
      જો (cdil == cdil_gimple_ssa)
	{
	  /* Create PHI nodes, they are parsed into __PHI internal calls
	     and update SSA operands.  */
	  FOR_EACH_BB_FN (bb, cfun)
	    {
	      gimple_stmt_iterator gsi;
	      માટે (gsi = gsi_start_bb (bb); !gsi_end_p (gsi);)
		{
		  gimple *stmt = gsi_stmt (gsi);
		  જો (!gimple_call_internal_p (stmt, IFN_PHI))
		    તોડો;

		  gphi *phi = create_phi_ગાંઠ (gimple_call_lhs (stmt), bb);
		  માટે (unsigned i = 0; i < gimple_call_અંક_args (stmt); i += 2)
		    {
		      પૂર્ણાંક srcidx = વૃક્ષ_INT_CST_નીચલું (gimple_call_arg (stmt, i));
		      edge e = find_edge (BASIC_BLOCK_FOR_FN (cfun, srcidx), bb);
		      જો (!e)
			c_parser_error (parser, "edge not found");
		      નહીંતર
			add_phi_arg (phi, gimple_call_arg (stmt, i + 1), e,
				     UNKNOWN_LOCATION);
		    }
		  gsi_remove (&gsi, સાચું);
		}
	      માટે (; !gsi_end_p (gsi); gsi_next (&gsi))
		update_stmt (gsi_stmt (gsi));
	    }
	  /* Fill SSA name gaps, putting them on the freelist and diagnose
	     SSA names without definition.  */
	  માટે (unsigned i = 1; i < અંક_ssa_names; ++i)
	    જો (!ssa_name (i))
	      {
		વૃક્ષ name = make_ssa_name_fn (cfun, integer_type_ગાંઠ, ખાલી, i);
		release_ssa_name_fn (cfun, name);
	      }
	    નહીંતર જો (!SSA_NAME_DEF_STMT (ssa_name (i)))
	      error ("SSA name %qE with version %d has no definition",
		     ssa_name (i), i);
	  /* No explicit virtual operands (yet).  */
	  bitmap_obstack_initialize (ખાલી);
	  update_ssa (TODO_update_ssa_only_virtuals);
	  bitmap_obstack_release (ખાલી);
	  /* ???  By flushing the freelist after virtual operand SSA rewrite
	     we keep the gaps available for re-use like needed for the
	     PR89595 testcase but then usually virtual operands would have
	     taken most of them.  The fix is obviously to make virtual
	     operands explicit in the SSA IL.  */
	  flush_ssaname_freelist ();
	}
      fix_loop_structure (ખાલી);
    }

  જો (cfun->curr_properties & PROP_cfg)
    {
      ENTRY_BLOCK_PTR_FOR_FN (cfun)->ગણતરી = entry_bb_ગણતરી;
      gcov_type t = param_gimple_fe_computed_hot_bb_threshold;
      set_hot_bb_threshold (t);
      update_max_bb_ગણતરી ();
      cgraph_ગાંઠ::get_create (cfun->decl);
      cgraph_edge::rebuild_edges ();
    }

  /* Perform IL validation and if any error is found abort compilation
     of this function by zapping its body.  */
  જો ((cfun->curr_properties & PROP_cfg)
      && verify_gimple_in_cfg (cfun, ખોટું, ખોટું))
    init_empty_વૃક્ષ_cfg ();
  નહીંતર જો (!(cfun->curr_properties & PROP_cfg)
	   && verify_gimple_in_seq (gimple_body (current_function_decl), ખોટું))
    gimple_set_body (current_function_decl, ખાલી);

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

સ્થિર તાર્કિક
c_parser_gimple_compound_statement (gimple_parser &parser, gimple_seq *seq)
{
  તાર્કિક return_p = ખોટું;

  જો (! c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    પાછા ખોટું;

  /* A compound statement starts with optional declarations.  */
  જ્યારે (c_parser_next_tokens_start_declaration (parser))
    {
      c_parser_gimple_declaration (parser);
      જો (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	પાછા ખોટું;
    }

  જ્યારે (c_parser_next_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      જો (c_parser_error (parser))
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_BRACE, ખાલી);
	  પાછા return_p;
	}
      નહીંતર જો (c_parser_next_token_is (parser, CPP_EOF))
	{
	  c_parser_error (parser, "expected declaration or statement");
	  પાછા return_p;
	}

      પસંદગી (c_parser_peek_token (parser)->type)
	{
	સ્થિતિ CPP_KEYWORD:
	  પસંદગી (c_parser_peek_token (parser)->keyword)
	    {
	    સ્થિતિ RID_AT_TRY:
	      c_parser_gimple_try_stmt (parser, seq);
	      તોડો;
	    સ્થિતિ RID_IF:
	      c_parser_gimple_if_stmt (parser, seq);
	      તોડો;
	    સ્થિતિ RID_SWITCH:
	      c_parser_gimple_switch_stmt (parser, seq);
	      તોડો;
	    સ્થિતિ RID_GOTO:
	      {
		location_t loc = c_parser_peek_token (parser)->location;
		c_parser_consume_token (parser);
		જો (c_parser_next_token_is (parser, CPP_NAME))
		  {
		    વૃક્ષ label = c_parser_peek_token (parser)->કિંમત;
		    c_parser_consume_token (parser);
		    c_parser_gimple_goto_stmt (parser, loc, label, seq);
		    જો (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      પાછા return_p;
		  }
		}
	      તોડો;
	    સ્થિતિ RID_RETURN:
	      return_p = સાચું;
	      c_parser_gimple_return_stmt (parser, seq);
	      જો (! c_parser_require (parser, CPP_SEMICOLON,
				      "expected %<;%>"))
		પાછા return_p;
	      જો (cfun->curr_properties & PROP_cfg)
		parser.ધકેલો_edge (parser.current_bb->index, EXIT_BLOCK, 0,
				  profile_probability::uninitialized ());
	      તોડો;
	    મૂળભૂત:
	      જાઓ પદાવલિ_stmt;
	    }
	  તોડો;
	સ્થિતિ CPP_NAME:
	  જો (c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_gimple_label (parser, seq);
	      તોડો;
	    }
	  જો (c_parser_next_token_is (parser, CPP_NAME)
	      && c_parser_peek_token (parser)->id_kind == C_ID_ID
	      && strcmp (IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત),
			 "try") == 0)
	    {
	      c_parser_gimple_try_stmt (parser, seq);
	      તોડો;
	    }
	  /* Basic block specification.
	     __BB (index, ...)  */
	  જો ((cfun->curr_properties & PROP_cfg)
	      && !strcmp (IDENTIFIER_POINTER
			    (c_parser_peek_token (parser)->કિંમત), "__BB"))
	    {
	      c_parser_consume_token (parser);
	      જો (! c_parser_require (parser, CPP_OPEN_PAREN,
				      "expected %<(%>"))
		પાછા return_p;
	      જો (c_parser_next_token_is_not (parser, CPP_સંખ્યા))
		{
		  c_parser_error (parser, "expected block index");
		  પાછા return_p;
		}
	      વૃક્ષ tnum = c_parser_peek_token (parser)->કિંમત;
	      જો (વૃક્ષ_CODE (tnum) != INTEGER_CST)
		{
		  c_parser_error (parser, "expected block index");
		  પાછા return_p;
		}
	      પૂર્ણાંક index = વૃક્ષ_INT_CST_નીચલું (tnum);
	      જો (index < અંક_FIXED_BLOCKS
		  || (index < last_basic_block_for_fn (cfun)
		      && BASIC_BLOCK_FOR_FN (cfun, index) != ખાલી))
		{
		  c_parser_error (parser, "invalid block index");
		  પાછા return_p;
		}
	      પૂર્ણાંક is_loop_header_of = -1;
	      profile_ગણતરી bb_ગણતરી = profile_ગણતરી::uninitialized ();
	      c_parser_consume_token (parser);
	      જ્યારે (c_parser_next_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  જો (! c_parser_next_token_is (parser, CPP_NAME))
		    {
		      c_parser_error (parser, "expected block specifier");
		      પાછા return_p;
		    }
		  /* loop_header (NUM)  */
		  જો (!strcmp (IDENTIFIER_POINTER
			         (c_parser_peek_token (parser)->કિંમત),
			       "loop_header"))
		    {
		      c_parser_consume_token (parser);
		      જો (! c_parser_require (parser, CPP_OPEN_PAREN,
					      "expected %<(%>"))
			પાછા return_p;
		      વૃક્ષ loop_અંક;
		      જો (! c_parser_next_token_is (parser, CPP_સંખ્યા)
			  || વૃક્ષ_CODE (loop_અંક
					  = c_parser_peek_token (parser)->કિંમત)
			       != INTEGER_CST)
			{
			  c_parser_error (parser, "expected loop number");
			  પાછા return_p;
			}
		      c_parser_consume_token (parser);
		      is_loop_header_of = વૃક્ષ_INT_CST_નીચલું (loop_અંક);
		      જો (! c_parser_require (parser, CPP_CLOSE_PAREN,
					      "expected %<)%>"))
			પાછા return_p;
		    }
		  /* Parse profile: quality(value) */
		  નહીંતર
		    {
		      વૃક્ષ q;
		      profile_quality quality;
		      વૃક્ષ v = c_parser_peek_token (parser)->કિંમત;
		      જો (!parse_profile_quality (IDENTIFIER_POINTER (v),
						  &quality))
			{
			  c_parser_error (parser, "unknown block specifier");
			  પાછા ખોટું;
			}

		      c_parser_consume_token (parser);
		      જો (!c_parser_require (parser, CPP_OPEN_PAREN,
					     "expected %<(%>"))
			પાછા ખોટું;

		      જો (!c_parser_next_token_is (parser, CPP_સંખ્યા)
			  || (વૃક્ષ_CODE (q = c_parser_peek_token (parser)->કિંમત)
			      != INTEGER_CST))
			{
			  c_parser_error (parser, "expected count value");
			  પાછા ખોટું;
			}

		      bb_ગણતરી
			= profile_ગણતરી::from_gcov_type (વૃક્ષ_INT_CST_નીચલું (q),
							 quality);
		      c_parser_consume_token (parser);
		      જો (! c_parser_require (parser, CPP_CLOSE_PAREN,
					      "expected %<)%>"))
			પાછા return_p;
		    }
		}
	      જો (! c_parser_require (parser, CPP_CLOSE_PAREN,
				      "expected %<)%>")
		  || ! c_parser_require (parser, CPP_COLON,
					 "expected %<:%>"))
		પાછા return_p;

	      /* Put stmts parsed in the current block.  */
	      જો (!gimple_seq_empty_p (*seq))
		{
		  જો (!parser.current_bb)
		    c_parser_error (parser, "stmts without block");
		  નહીંતર
		    {
		      gimple_stmt_iterator gsi
			= gsi_start_bb (parser.current_bb);
		      gsi_ઉમેરો_seq_after_without_update (&gsi, *seq,
							   GSI_CONTINUE_LINKING);
		    }
		  *seq = ખાલી;
		}

	      /* Build an empty block with specified index, linking them
		 in source order.  */
	      basic_block bb = alloc_block ();
	      bb->index = index;
	      link_block (bb, (parser.current_bb ? parser.current_bb
			       : ENTRY_BLOCK_PTR_FOR_FN (cfun)));
	      જો (basic_block_info_for_fn (cfun)->length () <= (size_t)index)
		vec_safe_grow_cleared (basic_block_info_for_fn (cfun),
				       index + 1, સાચું);
	      SET_BASIC_BLOCK_FOR_FN (cfun, index, bb);
	      જો (last_basic_block_for_fn (cfun) <= index)
		last_basic_block_for_fn (cfun) = index + 1;
	      n_basic_blocks_for_fn (cfun)++;
	      જો (parser.current_bb->index == ENTRY_BLOCK)
		parser.ધકેલો_edge (ENTRY_BLOCK, bb->index, EDGE_FALLTHRU,
				  profile_probability::always ());

	      /* We leave the proper setting to fixup.  */
	      વર્ગ loop *loop_father = loops_for_fn (cfun)->વૃક્ષ_મૂળ;
	      /* If the new block is a loop header, allocate a loop
		 struct.  Fixup will take care of proper placement within
		 the loop tree.  */
	      જો (is_loop_header_of != -1)
		{
		  જો (સંખ્યા_of_loops (cfun) > (unsigned)is_loop_header_of
		      && get_loop (cfun, is_loop_header_of) != ખાલી)
		    {
		      c_parser_error (parser, "duplicate loop header");
		    }
		  નહીંતર
		    {
		      વર્ગ loop *loop = alloc_loop ();
		      loop->અંક = is_loop_header_of;
		      loop->header = bb;
		      જો (સંખ્યા_of_loops (cfun) <= (unsigned)is_loop_header_of)
			vec_safe_grow_cleared (loops_for_fn (cfun)->larray,
					       is_loop_header_of + 1, સાચું);
		      (*loops_for_fn (cfun)->larray)[is_loop_header_of] = loop;
		      flow_loop_વૃક્ષ_ગાંઠ_add (loops_for_fn (cfun)->વૃક્ષ_મૂળ,
					       loop);
		    }
		  loop_father = get_loop (cfun, is_loop_header_of);
		}
	      bb->loop_father = loop_father;
	      bb->ગણતરી = bb_ગણતરી;

	      /* Stmts now go to the new block.  */
	      parser.current_bb = bb;
	      તોડો;
	    }
	  જાઓ પદાવલિ_stmt;

	સ્થિતિ CPP_SEMICOLON:
	  {
	    /* Empty stmt.  */
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);
	    gimple *nop = gimple_build_nop ();
	    gimple_set_location (nop, loc);
	    gimple_seq_add_stmt_without_update (seq, nop);
	    તોડો;
	  }

	સ્થિતિ CPP_CLOSE_PAREN:
	સ્થિતિ CPP_CLOSE_SQUARE:
	  /* Avoid infinite loop in error recovery:
	     c_parser_skip_until_found stops at a closing nesting
	     delimiter without consuming it, but here we need to consume
	     it to proceed further.  */
	  c_parser_error (parser, "expected statement");
	  c_parser_consume_token (parser);
	તોડો;

	મૂળભૂત:
પદાવલિ_stmt:
	  c_parser_gimple_statement (parser, seq);
	  જો (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	    c_parser_skip_until_found (parser, CPP_SEMICOLON, ખાલી);
	}
    }
  c_parser_consume_token (parser);

  /* Put stmts parsed in the current block.  */
  જો ((cfun->curr_properties & PROP_cfg)
      && !gimple_seq_empty_p (*seq))
    {
      જો (!parser.current_bb)
	c_parser_error (parser, "stmts without block");
      નહીંતર
	{
	  gimple_stmt_iterator gsi = gsi_start_bb (parser.current_bb);
	  gsi_ઉમેરો_seq_after_without_update (&gsi, *seq,
					       GSI_CONTINUE_LINKING);
	}
      *seq = ખાલી;
    }

  પાછા return_p;
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

સ્થિર શૂન્ય
c_parser_gimple_statement (gimple_parser &parser, gimple_seq *seq)
{
  સંરચના c_પદાવલિ lhs, rhs;
  gimple *assign = ખાલી;
  location_t loc;
  વૃક્ષ arg = NULL_વૃક્ષ;
  auto_vec<વૃક્ષ> vargs;

  lhs = c_parser_gimple_unary_expression (parser);
  loc = પદાવલિ_LOCATION (lhs.કિંમત);
  rhs.set_error ();

  /* GIMPLE call statement without LHS.  */
  જો (c_parser_next_token_is (parser, CPP_SEMICOLON)
      && વૃક્ષ_CODE (lhs.કિંમત) == CALL_પદાવલિ)
    {
      gimple *call;
      call = gimple_build_call_from_વૃક્ષ (lhs.કિંમત, ખાલી);
      gimple_seq_add_stmt_without_update (seq, call);
      gimple_set_location (call, loc);
      પાછા;
    }

  /* All following cases are statements with LHS.  */
  જો (! c_parser_require (parser, CPP_EQ, "expected %<=%>"))
    પાછા;

  /* Eat and ignore {v} right after the =, the has_volatile_ops is
     redundant and re-computed by the operand scanner.  */
  જો (c_parser_next_token_is (parser, CPP_OPEN_BRACE)
      && !(c_parser_peek_token (parser)->flags & PREV_WHITE)
      && c_parser_peek_2nd_token (parser)->type == CPP_NAME
      && !(c_parser_peek_2nd_token (parser)->flags & PREV_WHITE)
      && strcmp ("v", IDENTIFIER_POINTER
			(c_parser_peek_2nd_token (parser)->કિંમત)) == 0
      && c_parser_peek_nth_token (parser, 3)->type == CPP_CLOSE_BRACE
      && !(c_parser_peek_nth_token (parser, 3)->flags & PREV_WHITE))
    {
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }

  /* Cast expression.  */
  જો (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_typename (c_parser_peek_2nd_token (parser)))
    {
      c_parser_consume_token (parser);
      સંરચના c_type_name *type_name = c_parser_type_name (parser);
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      જો (type_name == ખાલી)
	પાછા;
      /* ???  The actual type used in the cast expression is ignored as
         in GIMPLE it is encoded by the type of the LHS.  */
      rhs = c_parser_gimple_postfix_expression (parser);
      જો (lhs.કિંમત != error_mark_ગાંઠ
	  && rhs.કિંમત != error_mark_ગાંઠ)
	{
	  ગણના વૃક્ષ_code code = NOP_પદાવલિ;
	  જો (FLOAT_TYPE_P (વૃક્ષ_TYPE (lhs.કિંમત))
	      && ! FLOAT_TYPE_P (વૃક્ષ_TYPE (rhs.કિંમત)))
	    code = FLOAT_પદાવલિ;
	  નહીંતર જો (! FLOAT_TYPE_P (વૃક્ષ_TYPE (lhs.કિંમત))
		   && FLOAT_TYPE_P (વૃક્ષ_TYPE (rhs.કિંમત)))
	    code = FIX_TRUNC_પદાવલિ;
	  assign = gimple_build_assign (lhs.કિંમત, code, rhs.કિંમત);
	  gimple_seq_add_stmt_without_update (seq, assign);
	  gimple_set_location (assign, loc);
	  પાછા;
	}
    }

  /* Unary expression.  */
  પસંદગી (c_parser_peek_token (parser)->type)
    {
    સ્થિતિ CPP_NAME:
      {
	વૃક્ષ id = c_parser_peek_token (parser)->કિંમત;
	જો (strcmp (IDENTIFIER_POINTER (id), "__ABS") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__ABSU") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__MIN") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__MAX") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__BIT_INSERT") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__VEC_PERM") == 0)
	  જાઓ build_unary_પદાવલિ;
	તોડો;
      }
    સ્થિતિ CPP_KEYWORD:
      જો (c_parser_peek_token (parser)->keyword != RID_REALPART
	  && c_parser_peek_token (parser)->keyword != RID_IMAGPART)
	તોડો;
      /* Fallthru.  */
    સ્થિતિ CPP_AND:
    સ્થિતિ CPP_PLUS:
    સ્થિતિ CPP_MINUS:
    સ્થિતિ CPP_COMPL:
    સ્થિતિ CPP_NOT:
    સ્થિતિ CPP_MULT: /* pointer deref */
    build_unary_પદાવલિ:
      rhs = c_parser_gimple_unary_expression (parser);
      જો (rhs.કિંમત != error_mark_ગાંઠ)
	{
	  assign = gimple_build_assign (lhs.કિંમત, rhs.કિંમત);
	  gimple_set_location (assign, loc);
	  gimple_seq_add_stmt_without_update (seq, assign);
	}
      પાછા;

    મૂળભૂત:;
    }

  /* GIMPLE PHI statement.  */
  જો (c_parser_next_token_is_keyword (parser, RID_PHI))
    {
      c_parser_consume_token (parser);

      જો (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	પાછા;

      જો (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	c_parser_consume_token (parser);

      જ્યારે (c_parser_next_token_is_not (parser, CPP_CLOSE_PAREN))
	{
	  જો (c_parser_next_token_is (parser, CPP_NAME)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      arg = c_parser_peek_token (parser)->કિંમત;
	      c_parser_consume_token (parser);
	      જો (c_parser_next_token_is (parser, CPP_COLON))
		c_parser_consume_token (parser);
	      પૂર્ણાંક src_index = -1;
	      જો (!c_parser_gimple_parse_bb_spec (arg, &src_index))
		c_parser_error (parser, "invalid source block specification");
	      vargs.safe_ધકેલો (size_int (src_index));
	    }
	  નહીંતર જો (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  નહીંતર
	    {
	      arg = c_parser_gimple_unary_expression (parser).કિંમત;
	      vargs.safe_ધકેલો (arg);
	    }
	}

      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");

      /* Build internal function for PHI.  */
      gcall *call_stmt = gimple_build_call_internal_vec (IFN_PHI, vargs);
      gimple_call_set_lhs (call_stmt, lhs.કિંમત);
      gimple_set_location (call_stmt, UNKNOWN_LOCATION);
      gimple_seq_add_stmt_without_update (seq, call_stmt);
      પાછા;
    }

  /* GIMPLE call with lhs.  */
  જો (c_parser_next_token_is (parser, CPP_DOT)
      || (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN
	  && lookup_name (c_parser_peek_token (parser)->કિંમત)))
    {
      rhs = c_parser_gimple_unary_expression (parser);
      જો (rhs.કિંમત != error_mark_ગાંઠ)
	{
	  gimple *call = gimple_build_call_from_વૃક્ષ (rhs.કિંમત, ખાલી);
	  gimple_call_set_lhs (call, lhs.કિંમત);
	  gimple_seq_add_stmt_without_update (seq, call);
	  gimple_set_location (call, loc);
	}
      પાછા;
    }

  rhs = c_parser_gimple_દ્વિઅંકી_expression (parser, વૃક્ષ_TYPE (lhs.કિંમત));
  જો (lhs.કિંમત != error_mark_ગાંઠ
      && rhs.કિંમત != error_mark_ગાંઠ)
    {
      /* If we parsed an identifier and the next token  is a '?' then parse
	 a conditional expression.  */
      જો (SSA_VAR_P (rhs.કિંમત) && c_parser_next_token_is (parser, CPP_QUERY))
	{
	  સંરચના c_પદાવલિ trueval, falseval;
	  c_parser_consume_token (parser);
	  trueval = c_parser_gimple_postfix_expression (parser);
	  falseval.set_error ();
	  જો (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    falseval = c_parser_gimple_postfix_expression (parser);
	  જો (trueval.કિંમત == error_mark_ગાંઠ
	      || falseval.કિંમત == error_mark_ગાંઠ)
	    પાછા;
	  rhs.કિંમત = build3_loc (loc,
				  VECTOR_TYPE_P (વૃક્ષ_TYPE (rhs.કિંમત))
				  ? VEC_COND_પદાવલિ : COND_પદાવલિ,
				  વૃક્ષ_TYPE (trueval.કિંમત),
				  rhs.કિંમત, trueval.કિંમત, falseval.કિંમત);
	}
      જો (get_gimple_rhs_class (વૃક્ષ_CODE (rhs.કિંમત)) == GIMPLE_INVALID_RHS)
	{
	  c_parser_error (parser, "unexpected RHS for assignment");
	  પાછા;
	}
      assign = gimple_build_assign (lhs.કિંમત, rhs.કિંમત);
      gimple_seq_add_stmt_without_update (seq, assign);
      gimple_set_location (assign, loc);
    }
  પાછા;
}

/* A mapping between an identifier to a tree code for binary operations. */
સ્થિર અચલ std::pair<અચલ અક્ષર *, વૃક્ષ_code> gimple_દ્વિઅંકી_identifier_code[] =
  {
    {"__MULT_HIGHPART", MULT_HIGHPART_પદાવલિ},
    {"__UNLT", UNLT_પદાવલિ},
    {"__UNLE", UNLE_પદાવલિ},
    {"__UNGT", UNGT_પદાવલિ},
    {"__UNGE", UNGE_પદાવલિ},
    {"__UNEQ", UNEQ_પદાવલિ},
    {"__UNORDERED", UNORDERED_પદાવલિ},
    {"__ORDERED", ORDERED_પદાવલિ},
    {"__LTGT", LTGT_પદાવલિ},
    {"__FLOOR_DIV", FLOOR_DIV_પદાવલિ},
    {"__ROUND_DIV", ROUND_DIV_પદાવલિ},
    {"__EXACT_DIV", EXACT_DIV_પદાવલિ},
    {"__CEIL_DIV", CEIL_DIV_પદાવલિ},
    {"__FLOOR_MOD", FLOOR_MOD_પદાવલિ},
    {"__ROUND_MOD", ROUND_MOD_પદાવલિ},
    {"__CEIL_MOD", CEIL_MOD_પદાવલિ},
    {"__ROTATE_LEFT", LROTATE_પદાવલિ},
    {"__ROTATE_RIGHT", RROTATE_પદાવલિ},
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

સ્થિર c_પદાવલિ
c_parser_gimple_દ્વિઅંકી_expression (gimple_parser &parser, વૃક્ષ ret_type)
{
  /* Location of the binary operator.  */
  સંરચના c_પદાવલિ ret, lhs, rhs;
  ગણના વૃક્ષ_code code = ERROR_MARK;
  ret.set_error ();
  lhs = c_parser_gimple_postfix_expression (parser, ret_type);
  જો (c_parser_error (parser))
    પાછા ret;
  પસંદગી (c_parser_peek_token (parser)->type)
    {
    સ્થિતિ CPP_MULT:
      code = MULT_પદાવલિ;
      તોડો;
    સ્થિતિ CPP_DIV:
      code = TRUNC_DIV_પદાવલિ;
      તોડો;
    સ્થિતિ CPP_MOD:
      code = TRUNC_MOD_પદાવલિ;
      તોડો;
    સ્થિતિ CPP_PLUS:
      જો (POINTER_TYPE_P (વૃક્ષ_TYPE (lhs.કિંમત)))
	code = POINTER_PLUS_પદાવલિ;
      નહીંતર
	code = PLUS_પદાવલિ;
      તોડો;
    સ્થિતિ CPP_MINUS:
      જો (POINTER_TYPE_P (વૃક્ષ_TYPE (lhs.કિંમત)))
	code = POINTER_DIFF_પદાવલિ;
      નહીંતર
	code = MINUS_પદાવલિ;
      તોડો;
    સ્થિતિ CPP_LSHIFT:
      code = LSHIFT_પદાવલિ;
      તોડો;
    સ્થિતિ CPP_RSHIFT:
      code = RSHIFT_પદાવલિ;
      તોડો;
    સ્થિતિ CPP_LESS:
      code = LT_પદાવલિ;
      તોડો;
    સ્થિતિ CPP_GREATER:
      code = GT_પદાવલિ;
      તોડો;
    સ્થિતિ CPP_LESS_EQ:
      code = LE_પદાવલિ;
      તોડો;
    સ્થિતિ CPP_GREATER_EQ:
      code = GE_પદાવલિ;
      તોડો;
    સ્થિતિ CPP_EQ_EQ:
      code = EQ_પદાવલિ;
      તોડો;
    સ્થિતિ CPP_NOT_EQ:
      code = NE_પદાવલિ;
      તોડો;
    સ્થિતિ CPP_AND:
      code = BIT_AND_પદાવલિ;
      તોડો;
    સ્થિતિ CPP_XOR:
      code = BIT_XOR_પદાવલિ;
      તોડો;
    સ્થિતિ CPP_OR:
      code = BIT_IOR_પદાવલિ;
      તોડો;
    સ્થિતિ CPP_AND_AND:
      c_parser_error (parser, "%<&&%> not valid in GIMPLE");
      પાછા ret;
    સ્થિતિ CPP_OR_OR:
      c_parser_error (parser, "%<||%> not valid in GIMPLE");
      પાછા ret;
    સ્થિતિ CPP_NAME:
      {
	વૃક્ષ id = c_parser_peek_token (parser)->કિંમત;
	માટે (auto &p : gimple_દ્વિઅંકી_identifier_code)
	  {
	    જો (strcmp (IDENTIFIER_POINTER (id), p.first) == 0)
	      {
		code = p.second;
		તોડો;
	      }
	  }
	જો (code != ERROR_MARK)
	  તોડો;
      }
      /* Fallthru.  */
    મૂળભૂત:
      /* Not a binary expression.  */
      પાછા lhs;
    }
  location_t ret_loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  rhs = c_parser_gimple_postfix_expression (parser);
  જો (lhs.કિંમત != error_mark_ગાંઠ && rhs.કિંમત != error_mark_ગાંઠ)
    ret.કિંમત = build2_loc (ret_loc, code, ret_type, lhs.કિંમત, rhs.કિંમત);
  પાછા ret;
}

/* Parse a gimple parentized binary expression.  */

સ્થિર c_પદાવલિ
c_parser_gimple_parentized_દ્વિઅંકી_expression (gimple_parser &parser,
					      location_t op_loc,
					      વૃક્ષ_code code)
{
  સંરચના c_પદાવલિ ret;
  ret.set_error ();

  c_parser_consume_token (parser);
  જો (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    પાછા ret;
  c_પદાવલિ op1 = c_parser_gimple_postfix_expression (parser);
  જો (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    પાછા ret;
  c_પદાવલિ op2 = c_parser_gimple_postfix_expression (parser);
  જો (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    પાછા ret;

  જો (op1.કિંમત != error_mark_ગાંઠ && op2.કિંમત != error_mark_ગાંઠ)
    ret.કિંમત = build2_loc (op_loc,
			    code, વૃક્ષ_TYPE (op1.કિંમત), op1.કિંમત, op2.કિંમત);
  પાછા ret;
}

/* Parse a gimple parentized binary expression.  */

સ્થિર c_પદાવલિ
c_parser_gimple_parentized_ternary_expression (gimple_parser &parser,
					       location_t op_loc,
					       વૃક્ષ_code code)
{
  સંરચના c_પદાવલિ ret;
  ret.set_error ();

  c_parser_consume_token (parser);
  જો (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    પાછા ret;
  c_પદાવલિ op1 = c_parser_gimple_postfix_expression (parser);
  જો (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    પાછા ret;
  c_પદાવલિ op2 = c_parser_gimple_postfix_expression (parser);
  જો (!c_parser_require (parser, CPP_COMMA, "expected %<)%>"))
    પાછા ret;
  c_પદાવલિ op3 = c_parser_gimple_postfix_expression (parser);
  જો (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    પાછા ret;

  જો (op1.કિંમત != error_mark_ગાંઠ
      && op2.કિંમત != error_mark_ગાંઠ
      && op3.કિંમત != error_mark_ગાંઠ)
    ret.કિંમત = build3_loc (op_loc,
			    code, વૃક્ષ_TYPE (op1.કિંમત),
			    op1.કિંમત, op2.કિંમત, op3.કિંમત);
  પાછા ret;
}

/* Parse gimple unary expression.

   gimple-unary-expression:
     gimple-postfix-expression
     unary-operator gimple-postfix-expression

   unary-operator: one of
     & * + - ~ abs_expr
*/

સ્થિર c_પદાવલિ
c_parser_gimple_unary_expression (gimple_parser &parser)
{
  સંરચના c_પદાવલિ ret, op;
  location_t op_loc = c_parser_peek_token (parser)->location;
  location_t finish;
  ret.set_error ();
  પસંદગી (c_parser_peek_token (parser)->type)
    {
    સ્થિતિ CPP_AND:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      mark_exp_read (op.કિંમત);
      પાછા gimple_parser_build_unary_op (op_loc, ADDR_પદાવલિ, op);
    સ્થિતિ CPP_MULT:
      {
	c_parser_consume_token (parser);
	op = c_parser_gimple_postfix_expression (parser);
	જો (op.કિંમત == error_mark_ગાંઠ)
	  પાછા ret;
	જો (! POINTER_TYPE_P (વૃક્ષ_TYPE (op.કિંમત)))
	  {
	    error_at (op_loc, "expected pointer as argument of unary %<*%>");
	    પાછા ret;
	  }
	finish = op.get_finish ();
	location_t combined_loc = make_location (op_loc, op_loc, finish);
	ret.કિંમત = build_simple_mem_ref_loc (combined_loc, op.કિંમત);
	વૃક્ષ_SIDE_EFFECTS (ret.કિંમત)
	  = વૃક્ષ_THIS_VOLATILE (ret.કિંમત)
	  = TYPE_VOLATILE (વૃક્ષ_TYPE (વૃક્ષ_TYPE (op.કિંમત)));
	ret.src_range.m_start = op_loc;
	ret.src_range.m_finish = finish;
	પાછા ret;
      }
    સ્થિતિ CPP_PLUS:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      પાછા gimple_parser_build_unary_op (op_loc, CONVERT_પદાવલિ, op);
    સ્થિતિ CPP_MINUS:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      પાછા gimple_parser_build_unary_op (op_loc, NEGATE_પદાવલિ, op);
    સ્થિતિ CPP_COMPL:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      પાછા gimple_parser_build_unary_op (op_loc, BIT_NOT_પદાવલિ, op);
    સ્થિતિ CPP_NOT:
      c_parser_error (parser, "%<!%> not valid in GIMPLE");
      પાછા ret;
    સ્થિતિ CPP_KEYWORD:
      પસંદગી (c_parser_peek_token (parser)->keyword)
	{
	સ્થિતિ RID_REALPART:
	  c_parser_consume_token (parser);
	  op = c_parser_gimple_postfix_expression (parser);
	  પાછા gimple_parser_build_unary_op (op_loc, REALPART_પદાવલિ, op);
	સ્થિતિ RID_IMAGPART:
	  c_parser_consume_token (parser);
	  op = c_parser_gimple_postfix_expression (parser);
	  પાછા gimple_parser_build_unary_op (op_loc, IMAGPART_પદાવલિ, op);
	મૂળભૂત:
	  પાછા c_parser_gimple_postfix_expression (parser);
	}
    સ્થિતિ CPP_NAME:
	{
	  વૃક્ષ id = c_parser_peek_token (parser)->કિંમત;
	  જો (strcmp (IDENTIFIER_POINTER (id), "__ABS") == 0)
	    {
	      c_parser_consume_token (parser);
	      op = c_parser_gimple_postfix_expression (parser);
	      પાછા gimple_parser_build_unary_op (op_loc, ABS_પદાવલિ, op);
	    }
	  નહીંતર જો (strcmp (IDENTIFIER_POINTER (id), "__ABSU") == 0)
	    {
	      c_parser_consume_token (parser);
	      op = c_parser_gimple_postfix_expression (parser);
	      પાછા gimple_parser_build_unary_op (op_loc, ABSU_પદાવલિ, op);
	    }
	  નહીંતર જો (strcmp (IDENTIFIER_POINTER (id), "__MIN") == 0)
	    પાછા c_parser_gimple_parentized_દ્વિઅંકી_expression (parser,
								 op_loc,
								 MIN_પદાવલિ);
	  નહીંતર જો (strcmp (IDENTIFIER_POINTER (id), "__MAX") == 0)
	    પાછા c_parser_gimple_parentized_દ્વિઅંકી_expression (parser,
								 op_loc,
								 MAX_પદાવલિ);
	  નહીંતર જો (strcmp (IDENTIFIER_POINTER (id), "__VEC_PERM") == 0)
	    પાછા c_parser_gimple_parentized_ternary_expression
			(parser, op_loc, VEC_PERM_પદાવલિ);
	  નહીંતર જો (strcmp (IDENTIFIER_POINTER (id), "__BIT_INSERT") == 0)
	    {
	      /* __BIT_INSERT '(' postfix-expression, postfix-expression,
			          integer ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      જો (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_પદાવલિ op0 = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_પદાવલિ op1 = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_પદાવલિ op2 = c_parser_gimple_postfix_expression (parser);
		  જો (વૃક્ષ_CODE (op2.કિંમત) != INTEGER_CST
		      || !int_fits_type_p (op2.કિંમત, bitsizetype))
		    c_parser_error (parser, "expected constant offset");
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  જો (op0.કિંમત != error_mark_ગાંઠ
		      && op1.કિંમત != error_mark_ગાંઠ
		      && વૃક્ષ_CODE (op2.કિંમત) == INTEGER_CST)
		    ret.કિંમત = build3_loc (loc, BIT_ઉમેરો_પદાવલિ,
					    વૃક્ષ_TYPE (op0.કિંમત),
					    op0.કિંમત, op1.કિંમત,
					    fold_convert (bitsizetype,
							  op2.કિંમત));
		}
	      પાછા ret;
	    }
	  નહીંતર
	    પાછા c_parser_gimple_postfix_expression (parser);
	}
    મૂળભૂત:
      પાછા c_parser_gimple_postfix_expression (parser);
    }
}

/* Decompose ID into base name (ID until ver_offset) and VERSION.  Return
   true if ID matches a SSA name.  */

સ્થિર તાર્કિક
c_parser_parse_ssa_name_id (વૃક્ષ id, unsigned *version, unsigned *ver_offset)
{
  અચલ અક્ષર *token = IDENTIFIER_POINTER (id);
  અચલ અક્ષર *var_version = strrchr (token, '_');
  જો (! var_version)
    પાછા ખોટું;

  *ver_offset = var_version - token;
  માટે (અચલ અક્ષર *p = var_version + 1; *p; ++p)
    જો (! ISDIGIT (*p))
      પાછા ખોટું;
  *version = atoi (var_version + 1);
  પાછા *version > 0;
}

/* Get at the actual SSA name ID with VERSION starting at VER_OFFSET.
   TYPE is the type if the SSA name is being declared.  */

સ્થિર વૃક્ષ
c_parser_parse_ssa_name (gimple_parser &parser,
			 વૃક્ષ id, વૃક્ષ type, unsigned version,
			 unsigned ver_offset)
{
  વૃક્ષ name = NULL_વૃક્ષ;
  અચલ અક્ષર *token = IDENTIFIER_POINTER (id);

  જો (ver_offset == 0)
    {
      /* Anonymous unnamed SSA name.  */
      જો (version < અંક_ssa_names)
	name = ssa_name (version);
      જો (! name)
	{
	  જો (! type)
	    {
	      c_parser_error (parser, "SSA name undeclared");
	      પાછા error_mark_ગાંઠ;
	    }
	  name = make_ssa_name_fn (cfun, type, ખાલી, version);
	}
    }
  નહીંતર
    {
      જો (version < અંક_ssa_names)
	name = ssa_name (version);
      જો (! name)
	{
	  /* Separate var name from version.  */
	  અક્ષર *var_name = XNEWVEC (અક્ષર, ver_offset + 1);
	  memcpy (var_name, token, ver_offset);
	  var_name[ver_offset] = '\0';
	  /* lookup for parent decl.  */
	  id = get_identifier (var_name);
	  વૃક્ષ parent = lookup_name (id);
	  XDELETEVEC (var_name);
	  જો (! parent || parent == error_mark_ગાંઠ)
	    {
	      c_parser_error (parser, "base variable or SSA name undeclared");
	      પાછા error_mark_ગાંઠ;
	    }
	  જો (!(VAR_P (parent)
		|| વૃક્ષ_CODE (parent) == PARM_DECL
		|| વૃક્ષ_CODE (parent) == RESULT_DECL))
	    {
	      error ("invalid base %qE for SSA name", parent);
	      પાછા error_mark_ગાંઠ;
	    }
	  name = make_ssa_name_fn (cfun, parent,
				   gimple_build_nop (), version);
	}
    }

  પાછા name;
}

/* Parse a gimple call to an internal function.

   gimple-call-internal:
     . identifier ( gimple-argument-expression-list[opt] )  */

સ્થિર સંરચના c_પદાવલિ
c_parser_gimple_call_internal (gimple_parser &parser)
{
  સંરચના c_પદાવલિ પદાવલિ;
  પદાવલિ.set_error ();

  gcc_assert (c_parser_next_token_is (parser, CPP_DOT));
  c_parser_consume_token (parser);
  location_t loc = c_parser_peek_token (parser)->location;
  જો (!c_parser_next_token_is (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_kind != C_ID_ID)
    {
      c_parser_error (parser, "expecting internal function name");
      પાછા પદાવલિ;
    }
  વૃક્ષ id = c_parser_peek_token (parser)->કિંમત;
  internal_fn ifn = lookup_internal_fn (IDENTIFIER_POINTER (id));
  c_parser_consume_token (parser);
  જો (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    {
      auto_vec<વૃક્ષ> exprlist;
      જો (!c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_gimple_પદાવલિ_list (parser, &exprlist);
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      જો (ifn == IFN_LAST)
	error_at (loc, "unknown internal function %qE", id);
      નહીંતર
	{
	  પદાવલિ.કિંમત = build_call_પદાવલિ_internal_loc_array
	    (loc, ifn, void_type_ગાંઠ, exprlist.length (),
	     exprlist.address ());
	  પદાવલિ.original_code = ERROR_MARK;
	  પદાવલિ.original_type = ખાલી;
	  પદાવલિ.m_decimal = 0;
	}
    }
  પાછા પદાવલિ;
}

/* Parse '<' type [',' alignment] '>' and return a type on success
   and NULL_TREE on error.  */

સ્થિર વૃક્ષ
c_parser_gimple_typespec (gimple_parser &parser)
{
  સંરચના c_type_name *type_name = ખાલી;
  વૃક્ષ alignment = NULL_વૃક્ષ;
  જો (c_parser_require (parser, CPP_LESS, "expected %<<%>"))
    {
      type_name = c_parser_type_name (parser);
      /* Optional alignment.  */
      જો (c_parser_next_token_is (parser, CPP_COMMA))
	{
	  c_parser_consume_token (parser);
	  alignment
	      = c_parser_gimple_postfix_expression (parser).કિંમત;
	}
      c_parser_skip_until_found (parser,
				 CPP_GREATER, "expected %<>%>");
    }
  જો (!type_name)
    પાછા NULL_વૃક્ષ;
  વૃક્ષ tem;
  વૃક્ષ type = groktypename (type_name, &tem, ખાલી);
  જો (alignment)
    type = build_aligned_type (type, વૃક્ષ_to_uhwi (alignment));
  પાછા type;
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

સ્થિર સંરચના c_પદાવલિ
c_parser_gimple_postfix_expression (gimple_parser &parser, વૃક્ષ ret_type)
{
  location_t loc = c_parser_peek_token (parser)->location;
  source_range tok_range = c_parser_peek_token (parser)->get_range ();
  સંરચના c_પદાવલિ પદાવલિ;
  પદાવલિ.set_error ();
  પસંદગી (c_parser_peek_token (parser)->type)
    {
    સ્થિતિ CPP_સંખ્યા:
      પદાવલિ.કિંમત = c_parser_peek_token (parser)->કિંમત;
      set_c_પદાવલિ_source_range (&પદાવલિ, tok_range);
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      તોડો;
    સ્થિતિ CPP_CHAR:
    સ્થિતિ CPP_CHAR16:
    સ્થિતિ CPP_CHAR32:
    સ્થિતિ CPP_UTF8CHAR:
    સ્થિતિ CPP_WCHAR:
      પદાવલિ.કિંમત = c_parser_peek_token (parser)->કિંમત;
      set_c_પદાવલિ_source_range (&પદાવલિ, tok_range);
      c_parser_consume_token (parser);
      તોડો;
    સ્થિતિ CPP_STRING:
    સ્થિતિ CPP_STRING16:
    સ્થિતિ CPP_STRING32:
    સ્થિતિ CPP_WSTRING:
    સ્થિતિ CPP_UTF8STRING:
      પદાવલિ = c_parser_string_literal (parser, ખોટું, સાચું);
      તોડો;
    સ્થિતિ CPP_DOT:
      પદાવલિ = c_parser_gimple_call_internal (parser);
      તોડો;
    સ્થિતિ CPP_NAME:
      જો (c_parser_peek_token (parser)->id_kind == C_ID_ID)
	{
	  વૃક્ષ id = c_parser_peek_token (parser)->કિંમત;
	  જો (strcmp (IDENTIFIER_POINTER (id), "__MEM") == 0)
	    {
	      /* __MEM '<' type-name [ ',' number ] '>'
	               '(' [ '(' type-name ')' ] unary-expression
			   [ '+' number ]
			   [ ',' number ]
			   [ ',' number ':' number ] ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      વૃક્ષ type = c_parser_gimple_typespec (parser);
	      સંરચના c_પદાવલિ ptr, alias_off, step, index, index2;
	      ptr.કિંમત = error_mark_ગાંઠ;
	      alias_off.કિંમત = NULL_વૃક્ષ;
	      step.કિંમત = NULL_વૃક્ષ;
	      index.કિંમત = NULL_વૃક્ષ;
	      index2.કિંમત = NULL_વૃક્ષ;
	      unsigned short clique = 0;
	      unsigned short base = 0;
	      તાર્કિક reverse_order = ખોટું;
	      સંરચના c_પદાવલિ ro;
	      જો (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  વૃક્ષ alias_type = NULL_વૃક્ષ;
		  /* Optional alias-type cast.  */
		  જો (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
		    {
		      c_parser_consume_token (parser);
		      સંરચના c_type_name *alias_type_name
			= c_parser_type_name (parser);
		      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
						 "expected %<)%>");
		      જો (alias_type_name)
			{
			  વૃક્ષ tem;
			  alias_type = groktypename (alias_type_name,
						     &tem, ખાલી);
			}
		    }
		  ptr = c_parser_gimple_unary_expression (parser);
		  જો (ptr.કિંમત == error_mark_ગાંઠ
		      || ! POINTER_TYPE_P (વૃક્ષ_TYPE (ptr.કિંમત)))
		    {
		      જો (ptr.કિંમત != error_mark_ગાંઠ)
			error_at (ptr.get_start (),
				  "invalid type of %<__MEM%> operand");
		      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
						 "expected %<)%>");
		      પાછા પદાવલિ;
		    }
		  જો (! alias_type)
		    alias_type = વૃક્ષ_TYPE (ptr.કિંમત);
		  /* Optional constant offset.  */
		  જો (c_parser_next_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      alias_off = c_parser_gimple_postfix_expression (parser);
		    }
		  જો (c_parser_next_token_is (parser, CPP_MULT))
		    {
		      std::swap (index, alias_off);
		      c_parser_consume_token (parser);
		      step = c_parser_gimple_postfix_expression (parser);
		    }
		  નહીંતર જો (c_parser_next_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      index = c_parser_gimple_postfix_expression (parser);
		      જો (c_parser_next_token_is (parser, CPP_MULT))
			{
			  c_parser_consume_token (parser);
			  step = c_parser_gimple_postfix_expression (parser);
			}
		      નહીંતર
			std::swap (index, index2);
		    }
		  નહીંતર જો (alias_off.કિંમત
			   && વૃક્ષ_CODE (alias_off.કિંમત) != INTEGER_CST)
		    std::swap (alias_off, index2);
		  જો (c_parser_next_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      index2 = c_parser_gimple_postfix_expression (parser);
		    }
		  જો (alias_off.કિંમત)
		    {
		      જો (વૃક્ષ_CODE (alias_off.કિંમત) != INTEGER_CST)
			error_at (alias_off.get_start (),
				  "expected constant offset for %<__MEM%> "
				  "operand");
		      alias_off.કિંમત = fold_convert (alias_type,
						      alias_off.કિંમત);
		    }
		  નહીંતર
		    alias_off.કિંમત = build_int_cst (alias_type, 0);
		  જો (step.કિંમત)
		    {
		      જો (વૃક્ષ_CODE (step.કિંમત) != INTEGER_CST)
			error_at (step.get_start (),
				  "expected constant step for %<__MEM%> "
				  "operand");
		    }
		  જો (c_parser_next_token_is (parser, CPP_COMMA))
		    {
		      સંરચના c_પદાવલિ cl, ba;
		      તાર્કિક has_clb = સાચું;
		      c_parser_consume_token (parser);
		      cl = c_parser_gimple_postfix_expression (parser);
		      જો (!c_parser_next_token_is (parser, CPP_COLON))
			{
			  ro = cl;
			  unsigned HOST_WIDE_INT tmp = 0;
			  જો (!વૃક્ષ_fits_uhwi_p (ro.કિંમત)
			      || (tmp = વૃક્ષ_to_uhwi (ro.કિંમત)) > 1)
			    error_at (ro.get_start (),
				      "invalid reverse order value");
			  reverse_order = tmp;
			  has_clb = ખોટું;
			  જો (c_parser_next_token_is (parser, CPP_COMMA))
			    {
			      c_parser_consume_token (parser);
			      cl = c_parser_gimple_postfix_expression (parser);
		              has_clb = સાચું;
			    }
			}
		      જો (has_clb
			  && c_parser_require (parser,
					       CPP_COLON, "expected %<:%>"))
			{
			  ba = c_parser_gimple_postfix_expression (parser);
			  જો (!વૃક્ષ_fits_uhwi_p (cl.કિંમત)
			      || !વૃક્ષ_fits_uhwi_p (ba.કિંમત)
			      || compare_વૃક્ષ_int (cl.કિંમત,
						   (clique = વૃક્ષ_to_uhwi
								(cl.કિંમત)))
			      || compare_વૃક્ષ_int (ba.કિંમત,
						   (base = વૃક્ષ_to_uhwi
								 (ba.કિંમત))))
			    error_at (cl.get_start (),
				      "invalid clique/base pair");
			}
		    }
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      જો (! type || c_parser_error (parser))
		{
		  c_parser_set_error (parser, ખોટું);
		  પાછા પદાવલિ;
		}
	      જો (index.કિંમત || step.કિંમત || index2.કિંમત)
		પદાવલિ.કિંમત = build5_loc (loc, TARGET_MEM_REF,
					 type, ptr.કિંમત, alias_off.કિંમત,
					 index.કિંમત, step.કિંમત, index2.કિંમત);
	      નહીંતર
		પદાવલિ.કિંમત = build2_loc (loc, MEM_REF,
					 type, ptr.કિંમત, alias_off.કિંમત);
	      જો (clique != 0)
		{
		  cfun->last_clique = MAX (cfun->last_clique, clique);
		  MR_DEPENDENCE_CLIQUE (પદાવલિ.કિંમત) = clique;
		  MR_DEPENDENCE_BASE (પદાવલિ.કિંમત) = base;
		}
	      જો (reverse_order)
		{
		  જો (વૃક્ષ_CODE (પદાવલિ.કિંમત) == MEM_REF)
		    REF_REVERSE_STORAGE_ORDER (પદાવલિ.કિંમત) = reverse_order;
		  નહીંતર
		    error_at (ro.get_start (),
			      "target mem ref cannot have reverse order");
		}
	      તોડો;
	    }
	  નહીંતર જો (strcmp (IDENTIFIER_POINTER (id), "__VIEW_CONVERT") == 0)
	    {
	      /* __VIEW_CONVERT '<' type-name [ ',' number ] '>'
	                        '(' postfix-expression ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      વૃક્ષ type = c_parser_gimple_typespec (parser);
	      જો (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_પદાવલિ op = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  જો (type && op.કિંમત != error_mark_ગાંઠ)
		    પદાવલિ.કિંમત = build1_loc (loc, VIEW_CONVERT_પદાવલિ,
					     type, op.કિંમત);
		}
	      તોડો;
	    }
	  નહીંતર જો (strcmp (IDENTIFIER_POINTER (id), "__BIT_FIELD_REF") == 0)
	    {
	      /* __BIT_FIELD_REF '<' type-name [ ',' number ] '>'
	                        '(' postfix-expression, integer, integer ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      વૃક્ષ type = c_parser_gimple_typespec (parser);
	      જો (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_પદાવલિ op0 = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_પદાવલિ op1 = c_parser_gimple_postfix_expression (parser);
		  જો (વૃક્ષ_CODE (op1.કિંમત) != INTEGER_CST
		      || !int_fits_type_p (op1.કિંમત, bitsizetype))
		    c_parser_error (parser, "expected constant size");
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_પદાવલિ op2 = c_parser_gimple_postfix_expression (parser);
		  જો (વૃક્ષ_CODE (op2.કિંમત) != INTEGER_CST
		      || !int_fits_type_p (op2.કિંમત, bitsizetype))
		    c_parser_error (parser, "expected constant offset");
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  જો (type
		      && op0.કિંમત != error_mark_ગાંઠ
		      && વૃક્ષ_CODE (op1.કિંમત) == INTEGER_CST
		      && વૃક્ષ_CODE (op2.કિંમત) == INTEGER_CST)
		    પદાવલિ.કિંમત = build3_loc (loc, BIT_FIELD_REF, type,
					     op0.કિંમત,
					     fold_convert (bitsizetype,
							   op1.કિંમત),
					     fold_convert (bitsizetype,
							   op2.કિંમત));
		}
	      તોડો;
	    }
	  નહીંતર જો (strcmp (IDENTIFIER_POINTER (id), "__CLOBBER") == 0)
	    {
	      /* __CLOBBER [ '(' bob | eob | bos | eos ')' ]  */
	      clobber_kind kind = CLOBBER_UNDEF;
	      c_parser_consume_token (parser);
	      જો (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
		{
		  c_parser_consume_token (parser);
		  auto tok = c_parser_peek_token (parser);
		  જો (c_parser_require (parser, CPP_NAME,
					"expected clobber kind"))
		    {
		      અચલ અક્ષર *kind_str = IDENTIFIER_POINTER (tok->કિંમત);
		      જો (strcmp (kind_str, "bos") == 0)
			kind = CLOBBER_STORAGE_BEGIN;
		      નહીંતર જો (strcmp (kind_str, "bob") == 0)
			kind = CLOBBER_OBJECT_BEGIN;
		      નહીંતર જો (strcmp (kind_str, "eob") == 0)
			kind = CLOBBER_OBJECT_END;
		      નહીંતર જો (strcmp (kind_str, "eos") == 0)
			kind = CLOBBER_STORAGE_END;
		      નહીંતર
			c_parser_error (parser, "expected one of %<bos%>, "
					"%<eos%>, %<bob>, %<eob%>");
		    }
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      /* We infer the (redundant) type from the LHS.  */
	      પદાવલિ.કિંમત = build_clobber (ret_type, kind);
	      તોડો;
	    }
	  નહીંતર જો (strcmp (IDENTIFIER_POINTER (id), "_Literal") == 0)
	    {
	      /* _Literal '(' type-name ')' ( [ '-' ] constant | constructor ) */
	      c_parser_consume_token (parser);
	      વૃક્ષ type = NULL_વૃક્ષ;
	      જો (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  સંરચના c_type_name *type_name = c_parser_type_name (parser);
		  વૃક્ષ tem;
		  જો (type_name)
		    type = groktypename (type_name, &tem, ખાલી);
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      જો (! type)
		{
		  c_parser_error (parser, "invalid _Literal");
		  પાછા પદાવલિ;
		}
	      જો (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
		{
		  c_parser_consume_token (parser);
		  જો (!AGGREGATE_TYPE_P (type)
		      && !VECTOR_TYPE_P (type))
		    {
		      c_parser_error (parser, "invalid type for _Literal with "
				      "constructor");
		      c_parser_skip_until_found (parser, CPP_CLOSE_BRACE,
						 "expected %<}%>");
		      પાછા પદાવલિ;
		    }
		  vec<constructor_elt, va_gc> *v = ખાલી;
		  તાર્કિક constant_p = સાચું;
		  જો (VECTOR_TYPE_P (type)
		      && !c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
		    {
		      vec_alloc (v, TYPE_VECTOR_SUBPARTS (type).to_constant ());
		      કરો
			{
			  વૃક્ષ val
			    = c_parser_gimple_postfix_expression (parser).કિંમત;
			  જો (! val
			      || val == error_mark_ગાંઠ
			      || (! CONSTANT_CLASS_P (val)
				  && ! SSA_VAR_P (val)))
			    {
			      c_parser_error (parser, "invalid _Literal");
			      પાછા પદાવલિ;
			    }
			  CONSTRUCTOR_APPEND_ELT (v, NULL_વૃક્ષ, val);
			  જો (! CONSTANT_CLASS_P (val))
			    constant_p = ખોટું;
			  જો (c_parser_next_token_is (parser, CPP_COMMA))
			    c_parser_consume_token (parser);
			  નહીંતર
			    તોડો;
			}
		      જ્યારે (1);
		    }
		  જો (c_parser_require (parser, CPP_CLOSE_BRACE,
					"expected %<}%>"))
		    {
		      જો (v && constant_p)
			પદાવલિ.કિંમત = build_vector_from_ctor (type, v);
		      નહીંતર
			પદાવલિ.કિંમત = build_constructor (type, v);
		    }
		  નહીંતર
		    {
		      c_parser_skip_until_found (parser, CPP_CLOSE_BRACE,
						 "expected %<}%>");
		      પાછા પદાવલિ;
		    }
		}
	      નહીંતર
		{
		  તાર્કિક neg_p, addr_p;
		  જો ((neg_p = c_parser_next_token_is (parser, CPP_MINUS)))
		    c_parser_consume_token (parser);
		  જો ((addr_p = c_parser_next_token_is (parser, CPP_AND)))
		    c_parser_consume_token (parser);
		  વૃક્ષ val = c_parser_gimple_postfix_expression (parser).કિંમત;
		  જો (! val
		      || val == error_mark_ગાંઠ
		      || (!CONSTANT_CLASS_P (val) && !addr_p))
		    {
		      c_parser_error (parser, "invalid _Literal");
		      પાછા પદાવલિ;
		    }
		  જો (addr_p)
		    {
		      val = build1 (ADDR_પદાવલિ, type, val);
		      જો (!is_gimple_invariant_address (val))
			{
			  c_parser_error (parser, "invalid _Literal");
			  પાછા પદાવલિ;
			}
		    }
		  જો (neg_p)
		    {
		      val = const_unop (NEGATE_પદાવલિ, વૃક્ષ_TYPE (val), val);
		      જો (! val)
			{
			  c_parser_error (parser, "invalid _Literal");
			  પાછા પદાવલિ;
			}
		    }
		  પદાવલિ.કિંમત = fold_convert (type, val);
		}
	      પાછા પદાવલિ;
	    }

	  /* SSA name.  */
	  unsigned version, ver_offset;
	  જો (! lookup_name (id)
	      && c_parser_parse_ssa_name_id (id, &version, &ver_offset))
	    {
	      c_parser_consume_token (parser);
	      પદાવલિ.કિંમત = c_parser_parse_ssa_name (parser, id, NULL_વૃક્ષ,
						    version, ver_offset);
	      જો (પદાવલિ.કિંમત == error_mark_ગાંઠ)
		પાછા પદાવલિ;
	      set_c_પદાવલિ_source_range (&પદાવલિ, tok_range);
	      /* For default definition SSA names.  */
	      જો (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
		  && c_parser_peek_2nd_token (parser)->type == CPP_NAME
		  && strcmp ("D",
			     IDENTIFIER_POINTER
			       (c_parser_peek_2nd_token (parser)->કિંમત)) == 0
		  && c_parser_peek_nth_token (parser, 3)->type == CPP_CLOSE_PAREN)
		{
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		  જો (! SSA_NAME_IS_DEFAULT_DEF (પદાવલિ.કિંમત))
		    {
		      જો (!SSA_NAME_VAR (પદાવલિ.કિંમત))
			{
			  error_at (loc, "anonymous SSA name cannot have"
				    " default definition");
			  પદાવલિ.કિંમત = error_mark_ગાંઠ;
			  પાછા પદાવલિ;
			}
		      set_ssa_default_def (cfun, SSA_NAME_VAR (પદાવલિ.કિંમત),
					   પદાવલિ.કિંમત);
		      SSA_NAME_DEF_STMT (પદાવલિ.કિંમત) = gimple_build_nop ();
		    }
		}
	    }
	  નહીંતર
	    {
	      c_parser_consume_token (parser);
	      પદાવલિ.કિંમત
		= build_external_ref (loc, id,
				      (c_parser_peek_token (parser)->type
				       == CPP_OPEN_PAREN), &પદાવલિ.original_type);
	      set_c_પદાવલિ_source_range (&પદાવલિ, tok_range);
	    }
	  તોડો;
	}
      /* Fallthru.  */
    મૂળભૂત:
      c_parser_error (parser, "expected expression");
      પદાવલિ.set_error ();
      તોડો;
    }
  જો (પદાવલિ.કિંમત == error_mark_ગાંઠ)
    પાછા પદાવલિ;
  પાછા c_parser_gimple_postfix_expression_after_primary
    (parser, પદાવલિ_LOC_OR_LOC (પદાવલિ.કિંમત, loc), પદાવલિ);
}

/* Parse a gimple postfix expression after the initial primary or compound
   literal.  */

સ્થિર સંરચના c_પદાવલિ
c_parser_gimple_postfix_expression_after_primary (gimple_parser &parser,
						  location_t પદાવલિ_loc,
						  સંરચના c_પદાવલિ પદાવલિ)
{
  location_t start;
  location_t finish;
  વૃક્ષ ident;
  location_t comp_loc;

  જ્યારે (સાચું)
    {
      location_t op_loc = c_parser_peek_token (parser)->location;
      પસંદગી (c_parser_peek_token (parser)->type)
	{
	સ્થિતિ CPP_OPEN_SQUARE:
	  {
	    c_parser_consume_token (parser);
	    વૃક્ષ idx = c_parser_gimple_unary_expression (parser).કિંમત;

	    જો (! c_parser_require (parser, CPP_CLOSE_SQUARE, "expected %<]%>"))
	      {
		c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE, ખાલી);
		તોડો;
	      }

	    start = પદાવલિ.get_start ();
	    finish = c_parser_tokens_buf (parser, 0)->location;
	    પદાવલિ.કિંમત = build_array_ref (op_loc, પદાવલિ.કિંમત, idx);
	    set_c_પદાવલિ_source_range (&પદાવલિ, start, finish);
	    પદાવલિ.m_decimal = 0;

	    પદાવલિ.original_code = ERROR_MARK;
	    પદાવલિ.original_type = ખાલી;
	    તોડો;
	  }
	સ્થિતિ CPP_OPEN_PAREN:
	  {
	    /* Function call.  */
	    c_parser_consume_token (parser);
	    auto_vec<વૃક્ષ> exprlist;
	    જો (! c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	      c_parser_gimple_પદાવલિ_list (parser, &exprlist);
	    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    જો (!FUNC_OR_METHOD_TYPE_P (વૃક્ષ_TYPE (પદાવલિ.કિંમત)))
	      {
		c_parser_error (parser, "invalid call to non-function");
		પદાવલિ.set_error ();
		તોડો;
	      }
	    પદાવલિ.કિંમત = build_call_array_loc
		(પદાવલિ_loc, વૃક્ષ_TYPE (વૃક્ષ_TYPE (પદાવલિ.કિંમત)),
		 પદાવલિ.કિંમત, exprlist.length (), exprlist.address ());
	    પદાવલિ.m_decimal = 0;
	    પદાવલિ.original_code = ERROR_MARK;
	    પદાવલિ.original_type = ખાલી;
	    તોડો;
	  }
	સ્થિતિ CPP_DOT:
	  {
	    /* Structure element reference.  */
	    c_parser_consume_token (parser);
	    જો (c_parser_next_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		ident = comp_tok->કિંમત;
		comp_loc = comp_tok->location;
	      }
	    નહીંતર
	      {
		c_parser_error (parser, "expected identifier");
		પદાવલિ.set_error ();
		પદાવલિ.original_code = ERROR_MARK;
		પદાવલિ.original_type = ખાલી;
		પાછા પદાવલિ;
	      }
	    start = પદાવલિ.get_start ();
	    finish = c_parser_peek_token (parser)->get_finish ();
	    c_parser_consume_token (parser);
	    પદાવલિ.કિંમત = build_component_ref (op_loc, પદાવલિ.કિંમત, ident,
					      comp_loc, UNKNOWN_LOCATION);
	    set_c_પદાવલિ_source_range (&પદાવલિ, start, finish);
	    પદાવલિ.m_decimal = 0;
	    પદાવલિ.original_code = ERROR_MARK;
	    જો (વૃક્ષ_CODE (પદાવલિ.કિંમત) != COMPONENT_REF)
	      પદાવલિ.original_type = ખાલી;
	    નહીંતર
	      {
		/* Remember the original type of a bitfield.  */
		વૃક્ષ field = વૃક્ષ_OPERAND (પદાવલિ.કિંમત, 1);
		જો (વૃક્ષ_CODE (field) != FIELD_DECL)
		  પદાવલિ.original_type = ખાલી;
		નહીંતર
		  પદાવલિ.original_type = DECL_BIT_FIELD_TYPE (field);
	      }
	    તોડો;
	  }
	સ્થિતિ CPP_DEREF:
	  {
	    /* Structure element reference.  */
	    જો (!POINTER_TYPE_P (વૃક્ષ_TYPE (પદાવલિ.કિંમત)))
	      {
		c_parser_error (parser, "dereference of non-pointer");
		પદાવલિ.set_error ();
		પદાવલિ.original_code = ERROR_MARK;
		પદાવલિ.original_type = ખાલી;
		પાછા પદાવલિ;
	      }
	    c_parser_consume_token (parser);
	    જો (c_parser_next_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		ident = comp_tok->કિંમત;
		comp_loc = comp_tok->location;
	      }
	    નહીંતર
	      {
		c_parser_error (parser, "expected identifier");
		પદાવલિ.set_error ();
		પદાવલિ.original_code = ERROR_MARK;
		પદાવલિ.original_type = ખાલી;
		પાછા પદાવલિ;
	      }
	    start = પદાવલિ.get_start ();
	    finish = c_parser_peek_token (parser)->get_finish ();
	    c_parser_consume_token (parser);
	    પદાવલિ.કિંમત = build_component_ref (op_loc,
					      build_simple_mem_ref_loc
					        (op_loc, પદાવલિ.કિંમત),
					      ident, comp_loc,
					      પદાવલિ.get_location ());
	    set_c_પદાવલિ_source_range (&પદાવલિ, start, finish);
	    પદાવલિ.m_decimal = 0;
	    પદાવલિ.original_code = ERROR_MARK;
	    જો (વૃક્ષ_CODE (પદાવલિ.કિંમત) != COMPONENT_REF)
	      પદાવલિ.original_type = ખાલી;
	    નહીંતર
	      {
		/* Remember the original type of a bitfield.  */
		વૃક્ષ field = વૃક્ષ_OPERAND (પદાવલિ.કિંમત, 1);
		જો (વૃક્ષ_CODE (field) != FIELD_DECL)
		  પદાવલિ.original_type = ખાલી;
		નહીંતર
		  પદાવલિ.original_type = DECL_BIT_FIELD_TYPE (field);
	      }
	    તોડો;
	  }
	મૂળભૂત:
	  પાછા પદાવલિ;
	}
    }
}

/* Parse expression list.

   gimple-expr-list:
     gimple-unary-expression
     gimple-expr-list , gimple-unary-expression

 */

સ્થિર શૂન્ય
c_parser_gimple_પદાવલિ_list (gimple_parser &parser, vec<વૃક્ષ> *ret)
{
  સંરચના c_પદાવલિ પદાવલિ;

  પદાવલિ = c_parser_gimple_unary_expression (parser);
  ret->safe_ધકેલો (પદાવલિ.કિંમત);
  જ્યારે (c_parser_next_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      પદાવલિ = c_parser_gimple_unary_expression (parser);
      ret->safe_ધકેલો (પદાવલિ.કિંમત);
    }
}

/* Parse gimple label.

   gimple-label:
     identifier :
     case constant-expression :
     default :

*/

સ્થિર શૂન્ય
c_parser_gimple_label (gimple_parser &parser, gimple_seq *seq)
{
  વૃક્ષ name = c_parser_peek_token (parser)->કિંમત;
  location_t loc1 = c_parser_peek_token (parser)->location;
  gcc_assert (c_parser_next_token_is (parser, CPP_NAME));
  c_parser_consume_token (parser);
  gcc_assert (c_parser_next_token_is (parser, CPP_COLON));
  c_parser_consume_token (parser);
  વૃક્ષ label = define_label (loc1, name);
  જો (label)
    gimple_seq_add_stmt_without_update (seq, gimple_build_label (label));
  પાછા;
}

/* Parse gimple/RTL pass list.

   gimple-or-rtl-pass-list:
     startwith("pass-name")[,{cfg,ssa}]
 */

શૂન્ય
c_parser_gimple_or_rtl_pass_list (c_parser *parser, c_declspecs *specs)
{
  અક્ષર *pass = ખાલી;

  /* Accept __GIMPLE/__RTL.  */
  જો (c_parser_next_token_is_not (parser, CPP_OPEN_PAREN))
    પાછા;
  c_parser_consume_token (parser);

  specs->entry_bb_ગણતરી = profile_ગણતરી::uninitialized ();
  જ્યારે (c_parser_next_token_is (parser, CPP_NAME))
    {
      profile_quality quality;
      અચલ અક્ષર *op = IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત);
      c_parser_consume_token (parser);
      જો (! strcmp (op, "startwith"))
	{
	  જો (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    પાછા;
	  જો (c_parser_next_token_is_not (parser, CPP_STRING))
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"expected pass name");
	      પાછા;
	    }
	  pass = xstrdup (વૃક્ષ_STRING_POINTER
			  (c_parser_string_literal (parser, ખોટું,
						    ખોટું).કિંમત));
	  જો (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<(%>"))
	    પાછા;
	}
      નહીંતર જો (parse_profile_quality (op, &quality))
	{
	  વૃક્ષ q;
	  જો (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    પાછા;

	  જો (!c_parser_next_token_is (parser, CPP_સંખ્યા)
	      || (વૃક્ષ_CODE (q = c_parser_peek_token (parser)->કિંમત)
		  != INTEGER_CST))
	    {
	      c_parser_error (parser, "expected count value");
	      પાછા;
	    }

	  specs->entry_bb_ગણતરી
	    = profile_ગણતરી::from_gcov_type (વૃક્ષ_INT_CST_નીચલું (q), quality);
	  c_parser_consume_token (parser);
	  જો (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    પાછા;
	}
      નહીંતર જો (specs->declspec_il != cdil_gimple)
	/* Allow only one IL specifier and none on RTL.  */
	;
      નહીંતર જો (! strcmp (op, "cfg"))
	specs->declspec_il = cdil_gimple_cfg;
      નહીંતર જો (! strcmp (op, "ssa"))
	specs->declspec_il = cdil_gimple_ssa;
      નહીંતર
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "invalid operation");
	  પાછા;
	}
     જો (c_parser_next_token_is (parser, CPP_COMMA))
       c_parser_consume_token (parser);
    }

  જો (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    પાછા;

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

સ્થિર શૂન્ય
c_parser_gimple_declaration (gimple_parser &parser)
{
  સંરચના c_declarator *declarator;
  સંરચના c_declspecs *specs = build_null_declspecs ();
  c_parser_declspecs (parser, specs, સાચું, સાચું, સાચું,
		      સાચું, સાચું, સાચું, સાચું, cla_nonabstract_decl);
  finish_declspecs (specs);

  /* Provide better error recovery.  Note that a type name here is usually
     better diagnosed as a redeclaration.  */
  જો (c_parser_next_token_starts_declspecs (parser)
      && ! c_parser_next_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<;%>");
      c_parser_set_error (parser, ખોટું);
      પાછા;
    }

  તાર્કિક dummy = ખોટું;
  declarator = c_parser_declarator (parser,
				    specs->typespec_kind != ctsk_none,
				    C_DTR_NORMAL, &dummy);

  જો (!c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_error (parser, "expected %<;%>");
      પાછા;
    }
  જો (declarator)
    {
      /* Handle SSA name decls specially, they do not go into the identifier
         table but we simply build the SSA name for later lookup.  */
      unsigned version, ver_offset;
      /* Handle SSA pointer declarations in a very simplistic ways, we
	 probably would like to call grokdeclarator in a special mode to
	 just build the type of the decl - start_decl already pushes
	 the identifier to the bindings for lookup, something we do not
	 want.  */
      સંરચના c_declarator *id_declarator = declarator;
      જ્યારે (id_declarator->kind == cdk_pointer)
	id_declarator = id_declarator->declarator;
      જો (id_declarator->kind == cdk_id
	  && (declarator->kind == cdk_pointer
	      || is_gimple_reg_type (specs->type))
	  && c_parser_parse_ssa_name_id (id_declarator->u.id.id,
					 &version, &ver_offset)
	  /* The following restricts it to unnamed anonymous SSA names
	     which fails parsing of named ones in dumps (we could
	     decide to not dump their name for -gimple).  */
	  && ver_offset == 0)
	{
	  સંરચના c_declarator *p = declarator;
	  વૃક્ષ type = specs->type;
	  જ્યારે (p->kind == cdk_pointer)
	    {
	      type = build_pointer_type (type);
	      p = p->declarator;
	    }
	  c_parser_parse_ssa_name (parser, id_declarator->u.id.id, type,
				   version, ver_offset);
	}
      નહીંતર
	{
	  વૃક્ષ postfix_attrs = NULL_વૃક્ષ;
	  વૃક્ષ all_prefix_attrs = specs->attrs;
	  specs->attrs = ખાલી;
	  વૃક્ષ decl = start_decl (declarator, specs, ખોટું,
				  chainon (postfix_attrs, all_prefix_attrs));
	  જો (decl)
	    finish_decl (decl, UNKNOWN_LOCATION, NULL_વૃક્ષ, NULL_વૃક્ષ,
			 NULL_વૃક્ષ);
	}
    }
}

/* Parse gimple goto statement.  */

સ્થિર શૂન્ય
c_parser_gimple_goto_stmt (gimple_parser &parser,
			   location_t loc, વૃક્ષ label, gimple_seq *seq)
{
  જો (cfun->curr_properties & PROP_cfg)
    {
      પૂર્ણાંક dest_index;
      profile_probability prob;
      જો (c_parser_gimple_parse_bb_spec_edge_probability (label, parser,
							  &dest_index, &prob))
	{
	  parser.ધકેલો_edge (parser.current_bb->index, dest_index,
			    EDGE_FALLTHRU, prob);
	  પાછા;
	}
    }
  વૃક્ષ decl = lookup_label_for_goto (loc, label);
  gimple_seq_add_stmt_without_update (seq, gimple_build_goto (decl));
}

/* Parse a parenthesized condition.
   gimple-condition:
     ( gimple-binary-expression )    */

સ્થિર વૃક્ષ
c_parser_gimple_paren_condition (gimple_parser &parser)
{
  જો (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    પાછા error_mark_ગાંઠ;
  વૃક્ષ cond
    = c_parser_gimple_દ્વિઅંકી_expression (parser, boolean_type_ગાંઠ).કિંમત;
  જો (cond != error_mark_ગાંઠ
      && ! COMPARISON_CLASS_P (cond)
      && ! CONSTANT_CLASS_P (cond)
      && ! SSA_VAR_P (cond))
    {
      c_parser_error (parser, "comparison required");
      cond = error_mark_ગાંઠ;
    }
  જો (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    પાછા error_mark_ગાંઠ;
  પાછા cond;
}

/* Parse gimple try statement.

   try-statement:
     try { ... } finally { ... }
     try { ... } finally { ... } else { ... }

   This could support try/catch as well, but it's not implemented yet.
 */

સ્થિર શૂન્ય
c_parser_gimple_try_stmt (gimple_parser &parser, gimple_seq *seq)
{
  gimple_seq tryseq = ખાલી;
  c_parser_consume_token (parser);
  c_parser_gimple_compound_statement (parser, &tryseq);

  જો ((c_parser_next_token_is (parser, CPP_KEYWORD)
       && c_parser_peek_token (parser)->keyword == RID_AT_FINALLY)
      || (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_token (parser)->id_kind == C_ID_ID
	  && strcmp (IDENTIFIER_POINTER (c_parser_peek_token (parser)->કિંમત),
		     "finally") == 0))
    {
      gimple_seq finseq = ખાલી;
      c_parser_consume_token (parser);
      c_parser_gimple_compound_statement (parser, &finseq);

      જો (c_parser_next_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_ELSE)
	{
	  gimple_seq elsseq = ખાલી;
	  c_parser_consume_token (parser);
	  c_parser_gimple_compound_statement (parser, &elsseq);

	  geh_else *stmt = gimple_build_eh_else (finseq, elsseq);
	  finseq = ખાલી;
	  gimple_seq_add_stmt_without_update (&finseq, stmt);
	}

      gtry *stmt = gimple_build_try (tryseq, finseq, GIMPLE_TRY_FINALLY);
      gimple_seq_add_stmt_without_update (seq, stmt);
    }
  નહીંતર જો (c_parser_next_token_is (parser, CPP_KEYWORD)
      && c_parser_peek_token (parser)->keyword == RID_AT_CATCH)
    c_parser_error (parser, "%<catch%> is not supported");
  નહીંતર
    c_parser_error (parser, "expected %<finally%> or %<catch%>");
}

/* Parse gimple if-else statement.

   if-statement:
     if ( gimple-binary-expression ) gimple-goto-statement
     if ( gimple-binary-expression ) gimple-goto-statement \
					else gimple-goto-statement
 */

સ્થિર શૂન્ય
c_parser_gimple_if_stmt (gimple_parser &parser, gimple_seq *seq)
{
  વૃક્ષ t_label = NULL_વૃક્ષ, f_label = NULL_વૃક્ષ, label;
  location_t loc;
  c_parser_consume_token (parser);
  વૃક્ષ cond = c_parser_gimple_paren_condition (parser);

  જો (c_parser_next_token_is_keyword (parser, RID_GOTO))
    {
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      જો (! c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected label");
	  પાછા;
	}
      label = c_parser_peek_token (parser)->કિંમત;
      c_parser_consume_token (parser);
      પૂર્ણાંક dest_index;
      profile_probability prob;
      જો ((cfun->curr_properties & PROP_cfg)
	  && c_parser_gimple_parse_bb_spec_edge_probability (label, parser,
							     &dest_index, &prob))
	parser.ધકેલો_edge (parser.current_bb->index, dest_index,
			  EDGE_TRUE_કિંમત, prob);
      નહીંતર
	t_label = lookup_label_for_goto (loc, label);
      જો (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	પાછા;
    }
  નહીંતર
    {
      c_parser_error (parser, "expected goto expression");
      પાછા;
    }

  જો (c_parser_next_token_is_keyword (parser, RID_ELSE))
    c_parser_consume_token (parser);
  નહીંતર
    {
      c_parser_error (parser, "expected else statement");
      પાછા;
    }

  જો (c_parser_next_token_is_keyword (parser, RID_GOTO))
    {
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      જો (! c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected label");
	  પાછા;
	}
      label = c_parser_peek_token (parser)->કિંમત;
      c_parser_consume_token (parser);
      પૂર્ણાંક dest_index;
      profile_probability prob;
      જો ((cfun->curr_properties & PROP_cfg)
	  && c_parser_gimple_parse_bb_spec_edge_probability (label, parser,
							     &dest_index, &prob))
	parser.ધકેલો_edge (parser.current_bb->index, dest_index,
			  EDGE_FALSE_કિંમત, prob);
      નહીંતર
	f_label = lookup_label_for_goto (loc, label);
      જો (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	પાછા;
    }
  નહીંતર
    {
      c_parser_error (parser, "expected goto expression");
      પાછા;
    }

  જો (cond != error_mark_ગાંઠ)
    gimple_seq_add_stmt_without_update (seq, gimple_build_cond_from_વૃક્ષ (cond, t_label,
							   f_label));
}

/* Parse gimple switch-statement.

   gimple-switch-statement:
     switch (gimple-postfix-expression) gimple-case-statement

   gimple-case-statement:
     gimple-case-statement
     gimple-label-statement : gimple-goto-statement
*/

સ્થિર શૂન્ય
c_parser_gimple_switch_stmt (gimple_parser &parser, gimple_seq *seq)
{
  c_પદાવલિ cond_પદાવલિ;
  વૃક્ષ case_label, label;
  auto_vec<વૃક્ષ> labels;
  વૃક્ષ default_label = NULL_વૃક્ષ;
  c_parser_consume_token (parser);

  જો (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    પાછા;
  cond_પદાવલિ = c_parser_gimple_postfix_expression (parser);
  જો (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    પાછા;

  જો (! c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    પાછા;

  જ્યારે (c_parser_next_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      જો (c_parser_next_token_is (parser, CPP_EOF))
	{
	  c_parser_error (parser, "expected statement");
	  પાછા;
	}

      પસંદગી (c_parser_peek_token (parser)->keyword)
	{
	સ્થિતિ RID_CASE:
	  {
	    c_પદાવલિ exp1;
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);

	    જો (c_parser_next_token_is (parser, CPP_NAME)
		|| c_parser_peek_token (parser)->type == CPP_સંખ્યા)
	      exp1 = c_parser_gimple_postfix_expression (parser);
	    નહીંતર
	      {
		c_parser_error (parser, "expected expression");
		પાછા;
	      }

	    જો (c_parser_next_token_is (parser, CPP_COLON))
	      {
		c_parser_consume_token (parser);
		જો (c_parser_next_token_is (parser, CPP_NAME))
		  {
		    label = c_parser_peek_token (parser)->કિંમત;
		    c_parser_consume_token (parser);
		    વૃક્ષ decl = lookup_label_for_goto (loc, label);
		    case_label = build_case_label (exp1.કિંમત, NULL_વૃક્ષ,
						   decl);
		    labels.safe_ધકેલો (case_label);
		    જો (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      પાછા;
		  }
		નહીંતર જો (! c_parser_require (parser, CPP_NAME,
					     "expected label"))
		  પાછા;
	      }
	    નહીંતર જો (! c_parser_require (parser, CPP_SEMICOLON,
					 "expected %<:%>"))
	      પાછા;
	    તોડો;
	  }
	સ્થિતિ RID_DEFAULT:
	  {
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);
	    જો (c_parser_next_token_is (parser, CPP_COLON))
	      {
		c_parser_consume_token (parser);
		જો (c_parser_next_token_is (parser, CPP_NAME))
		  {
		    label = c_parser_peek_token (parser)->કિંમત;
		    c_parser_consume_token (parser);
		    વૃક્ષ decl = lookup_label_for_goto (loc, label);
		    default_label = build_case_label (NULL_વૃક્ષ, NULL_વૃક્ષ,
						      decl);
		    જો (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      પાછા;
		  }
		નહીંતર જો (! c_parser_require (parser, CPP_NAME,
					     "expected label"))
		  પાછા;
	      }
	    નહીંતર જો (! c_parser_require (parser, CPP_SEMICOLON,
					 "expected %<:%>"))
	      પાછા;
	    તોડો;
	  }
	મૂળભૂત:
	  c_parser_error (parser, "expected case label");
	  પાછા;
	}

    }
  જો (! c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>"))
    પાછા;

  જો (cond_પદાવલિ.કિંમત != error_mark_ગાંઠ)
    {
      gswitch *s = gimple_build_switch (cond_પદાવલિ.કિંમત, default_label, labels);
      gimple_seq_add_stmt_without_update (seq, s);
    }
}

/* Parse gimple return statement.  */

સ્થિર શૂન્ય
c_parser_gimple_return_stmt (gimple_parser &parser, gimple_seq *seq)
{
  location_t loc = c_parser_peek_token (parser)->location;
  gimple *ret = ખાલી;
  c_parser_consume_token (parser);
  જો (c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      c_finish_gimple_return (loc, NULL_વૃક્ષ);
      ret = gimple_build_return (ખાલી);
      gimple_seq_add_stmt_without_update (seq, ret);
    }
  નહીંતર
    {
      location_t xloc = c_parser_peek_token (parser)->location;
      c_પદાવલિ પદાવલિ = c_parser_gimple_unary_expression (parser);
      જો (પદાવલિ.કિંમત != error_mark_ગાંઠ)
	{
	  c_finish_gimple_return (xloc, પદાવલિ.કિંમત);
	  ret = gimple_build_return (પદાવલિ.કિંમત);
	  gimple_seq_add_stmt_without_update (seq, ret);
	}
    }
}

/* Support function for c_parser_gimple_return_stmt.  */

સ્થિર શૂન્ય
c_finish_gimple_return (location_t loc, વૃક્ષ retval)
{
  વૃક્ષ valtype = વૃક્ષ_TYPE (વૃક્ષ_TYPE (current_function_decl));

  /* Use the expansion point to handle cases such as returning NULL
     in a function returning void.  */
  location_t xloc = expansion_point_location_if_in_system_header (loc);

  જો (વૃક્ષ_THIS_VOLATILE (current_function_decl))
    warning_at (xloc, 0,
		"function declared %<noreturn%> has a %<return%> statement");

  જો (! retval)
    current_function_returns_null = 1;
  નહીંતર જો (valtype == 0 || VOID_TYPE_P (valtype))
    {
      current_function_returns_null = 1;
      જો (વૃક્ષ_CODE (વૃક્ષ_TYPE (retval)) != VOID_TYPE)
	{
	  error_at
	    (xloc, "%<return%> with a value, in function returning void");
	  inform (DECL_SOURCE_LOCATION (current_function_decl),
		  "declared here");
	}
    }
  નહીંતર જો (વૃક્ષ_CODE (valtype) != વૃક્ષ_CODE (વૃક્ષ_TYPE (retval)))
    {
      error_at
	(xloc, "invalid conversion in return statement");
      inform (DECL_SOURCE_LOCATION (current_function_decl),
	      "declared here");
    }
  પાછા;
}
