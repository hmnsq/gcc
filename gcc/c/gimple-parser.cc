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

#அந்தர்பாவ "config.h"
#அந்தர்பாவ "system.h"
#அந்தர்பாவ "coretypes.h"
#அந்தர்பாவ "target.h"
#அந்தர்பாவ "function.h"
#அந்தர்பாவ "c-tree.h"
#அந்தர்பாவ "timevar.h"
#அந்தர்பாவ "stringpool.h"
#அந்தர்பாவ "cgraph.h"
#அந்தர்பாவ "attribs.h"
#அந்தர்பாவ "stor-layout.h"
#அந்தர்பாவ "varasm.h"
#அந்தர்பாவ "trans-mem.h"
#அந்தர்பாவ "c-family/c-pragma.h"
#அந்தர்பாவ "c-lang.h"
#அந்தர்பாவ "c-family/c-objc.h"
#அந்தர்பாவ "plugin.h"
#அந்தர்பாவ "builtins.h"
#அந்தர்பாவ "gomp-constants.h"
#அந்தர்பாவ "c-family/c-indentation.h"
#அந்தர்பாவ "gimple-expr.h"
#அந்தர்பாவ "context.h"
#அந்தர்பாவ "gcc-rich-location.h"
#அந்தர்பாவ "c-parser.h"
#அந்தர்பாவ "tree-vrp.h"
#அந்தர்பாவ "tree-pass.h"
#அந்தர்பாவ "tree-pretty-print.h"
#அந்தர்பாவ "tree.h"
#அந்தர்பாவ "basic-block.h"
#அந்தர்பாவ "gimple.h"
#அந்தர்பாவ "gimple-pretty-print.h"
#அந்தர்பாவ "tree-ssa.h"
#அந்தர்பாவ "pass_manager.h"
#அந்தர்பாவ "tree-ssanames.h"
#அந்தர்பாவ "gimple-ssa.h"
#அந்தர்பாவ "tree-dfa.h"
#அந்தர்பாவ "internal-fn.h"
#அந்தர்பாவ "cfg.h"
#அந்தர்பாவ "cfghooks.h"
#அந்தர்பாவ "bitmap.h"
#அந்தர்பாவ "cfganal.h"
#அந்தர்பாவ "tree-cfg.h"
#அந்தர்பாவ "gimple-iterator.h"
#அந்தர்பாவ "cfgloop.h"
#அந்தர்பாவ "tree-phinodes.h"
#அந்தர்பாவ "tree-into-ssa.h"


/* GIMPLE parser state.  */

வகுப்பு gimple_parser
{
பொது:
  gimple_parser (c_parser *p) : parser (p), edges(), current_bb(வெற்று) {}
  /* c_parser is not visible here, use composition and fake inheritance
     via a conversion operator.  */
  operator c_parser *() { திரும்பு parser; }
  c_parser *parser;

  /* CFG build state.  */
  வகுப்பு gimple_parser_edge
  {
  பொது:
    முழு src;
    முழு dest;
    முழு flags;
    profile_probability probability;
  };
  auto_vec<gimple_parser_edge> edges;
  basic_block current_bb;

  வெறுமை தள்ளு_edge (முழு, முழு, முழு, profile_probability);
};

வெறுமை
gimple_parser::தள்ளு_edge (முழு src, முழு dest, முழு flags,
			  profile_probability prob)
{
  gimple_parser_edge e;
  e.src = src;
  e.dest = dest;
  e.flags = flags;
  e.probability = prob;
  edges.safe_தள்ளு (e);
}


/* Gimple parsing functions.  */
நிலையான தருக்க c_parser_gimple_compound_statement (gimple_parser &, gimple_seq *);
நிலையான வெறுமை c_parser_gimple_label (gimple_parser &, gimple_seq *);
நிலையான வெறுமை c_parser_gimple_statement (gimple_parser &, gimple_seq *);
நிலையான கட்டமைப்பு c_கோவை c_parser_gimple_இருமம்_expression (gimple_parser &, மரம்);
நிலையான கட்டமைப்பு c_கோவை c_parser_gimple_unary_expression (gimple_parser &);
நிலையான கட்டமைப்பு c_கோவை c_parser_gimple_postfix_expression
			(gimple_parser &, மரம் = error_mark_முனை);
நிலையான கட்டமைப்பு c_கோவை c_parser_gimple_postfix_expression_after_primary
			(gimple_parser &, location_t, கட்டமைப்பு c_கோவை);
நிலையான வெறுமை c_parser_gimple_declaration (gimple_parser &);
நிலையான வெறுமை c_parser_gimple_goto_stmt (gimple_parser &, location_t,
				       மரம், gimple_seq *);
நிலையான வெறுமை c_parser_gimple_try_stmt (gimple_parser &, gimple_seq *);
நிலையான வெறுமை c_parser_gimple_if_stmt (gimple_parser &, gimple_seq *);
நிலையான வெறுமை c_parser_gimple_switch_stmt (gimple_parser &, gimple_seq *);
நிலையான வெறுமை c_parser_gimple_return_stmt (gimple_parser &, gimple_seq *);
நிலையான வெறுமை c_finish_gimple_return (location_t, மரம்);
நிலையான மரம் c_parser_gimple_paren_condition (gimple_parser &);
நிலையான வெறுமை c_parser_gimple_கோவை_list (gimple_parser &, vec<மரம்> *);


/* Much like parser_build_unary_op, but avoid applying default conversions.  */

நிலையான c_கோவை
gimple_parser_build_unary_op (location_t loc,
			      எண்ணிக்கை மரம்_code code, கட்டமைப்பு c_கோவை arg)
{
  கட்டமைப்பு c_கோவை result;

  result.original_code = code;
  result.original_type = வெற்று;
  result.m_decimal = 0;

  எனில் (reject_gcc_builtin (arg.மதிப்பு))
    {
      result.மதிப்பு = error_mark_முனை;
    }
  இல்லையெனில்
    {
      result.மதிப்பு = build_unary_op (loc, code, arg.மதிப்பு, உண்மை);

      எனில் (மரம்_OVERFLOW_P (result.மதிப்பு) && !மரம்_OVERFLOW_P (arg.மதிப்பு))
	overflow_warning (loc, result.மதிப்பு, arg.மதிப்பு);
    }

  /* We are typically called when parsing a prefix token at LOC acting on
     ARG.  Reflect this by updating the source range of the result to
     start at LOC and end at the end of ARG.  */
  set_c_கோவை_source_range (&result,
			   loc, arg.get_finish ());

  திரும்பு result;
}

/* See if VAL is an identifier matching __BB<num> and return <num>
   in *INDEX.  */

நிலையான தருக்க
c_parser_gimple_parse_bb_spec (மரம் val, முழு *index)
{
  எனில் (!startswith (IDENTIFIER_POINTER (val), "__BB"))
    திரும்பு பொய்;

  மாறிலி எழுத்து *bb = IDENTIFIER_POINTER (val) + 4;
  எனில் (! ISDIGIT (*bb))
    திரும்பு பொய்;

  எழுத்து *pend;
  errno = 0;
  மாறிலி unsigned long எண் = strtoul (bb, &pend, 10);
  எனில் (errno == ERANGE
      || *pend != '\0'
      || எண் > INT_MAX)
    திரும்பு பொய்;

  *index = எண்;
  திரும்பு உண்மை;
}

/* See if VAL is an identifier matching __BB<num> and return <num>
   in *INDEX.  Return true if so and parse also FREQUENCY of
   the edge.  */


நிலையான தருக்க
c_parser_gimple_parse_bb_spec_edge_probability (மரம் val,
						gimple_parser &parser,
						முழு *index,
						profile_probability
						*probability)
{
  தருக்க return_p = c_parser_gimple_parse_bb_spec (val, index);
  எனில் (return_p)
    {
      *probability = profile_probability::uninitialized ();
      /* Parse frequency if provided.  */
      எனில் (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	{
	  மரம் f;
	  c_parser_consume_token (parser);
	  எனில் (!c_parser_next_token_is (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected frequency quality");
	      திரும்பு பொய்;
	    }

	  profile_quality quality;
	  மாறிலி எழுத்து *v
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு);
	  எனில் (!parse_profile_quality (v, &quality))
	    {
	      c_parser_error (parser, "unknown profile quality");
	      திரும்பு பொய்;
	    }

	  c_parser_consume_token (parser);
	  எனில் (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    திரும்பு பொய்;

	  எனில் (!c_parser_next_token_is (parser, CPP_எண்)
	      || (மரம்_CODE (f = c_parser_peek_token (parser)->மதிப்பு)
		  != INTEGER_CST))
	    {
	      c_parser_error (parser, "expected frequency value");
	      திரும்பு பொய்;
	    }

	  unsigned முழு மதிப்பு = மரம்_INT_CST_கீழ் (f);
	  *probability = profile_probability (மதிப்பு, quality);

	  c_parser_consume_token (parser);
	  எனில் (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    திரும்பு பொய்;

	  எனில் (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    திரும்பு பொய்;
	}

      திரும்பு உண்மை;
    }

  திரும்பு பொய்;

}

/* Parse the body of a function declaration marked with "__GIMPLE".  */

வெறுமை
c_parser_parse_gimple_body (c_parser *cparser, எழுத்து *gimple_pass,
			    எண்ணிக்கை c_declspec_il cdil,
			    profile_மொத்தம் entry_bb_மொத்தம்)
{
  gimple_parser parser (cparser);
  gimple_seq seq = வெற்று;
  gimple_seq body = வெற்று;
  மரம் stmt = தள்ளு_stmt_list ();
  தள்ளு_scope ();
  location_t loc1 = c_parser_peek_token (parser)->location;

  cfun->pass_startwith = gimple_pass;
  init_மரம்_ssa (cfun);

  எனில் (cdil == cdil_gimple)
    /* While we have SSA names in the IL we do not have a CFG built yet
       and PHIs are represented using a PHI internal function.  We do
       have lowered control flow and exception handling (well, we do not
       have parser support for EH yet).  But as we still have BINDs
       we have to go through lowering again.  */
    cfun->curr_properties = PROP_gimple_any;
  இல்லையெனில்
    {
      /* We have at least cdil_gimple_cfg.  */
      gimple_register_cfg_hooks ();
      init_empty_மரம்_cfg ();
      parser.current_bb = ENTRY_BLOCK_PTR_FOR_FN (cfun);
      /* Initialize the bare loop structure - we are going to only
         mark headers and leave the rest to fixup.  */
      set_loops_for_fn (cfun, ggc_cleared_alloc<கட்டமைப்பு loops> ());
      init_loops_structure (cfun, loops_for_fn (cfun), 1);
      loops_state_set (cfun, LOOPS_NEED_FIXUP|LOOPS_MAY_HAVE_MULTIPLE_LATCHES);
      cfun->curr_properties
	|= PROP_gimple_lcf | PROP_gimple_leh | PROP_cfg | PROP_loops;
      எனில் (cdil == cdil_gimple_ssa)
	{
	  init_ssa_operands (cfun);
	  cfun->curr_properties |= PROP_ssa;
	}
    }

  எனில் (! c_parser_gimple_compound_statement (parser, &seq)
      && cdil == cdil_gimple)
    {
      gimple *ret = gimple_build_return (வெற்று);
      gimple_seq_add_stmt_without_update (&seq, ret);
    }

  மரம் block = எடு_scope ();
  stmt = எடு_stmt_list (stmt);
  stmt = c_build_bind_கோவை (loc1, block, stmt);

  block = DECL_INITIAL (current_function_decl);
  BLOCK_SUBBLOCKS (block) = NULL_மரம்;
  BLOCK_CHAIN (block) = NULL_மரம்;
  மரம்_ASM_WRITTEN (block) = 1;

  எனில் (cdil == cdil_gimple)
    {
      gbind *bind_stmt = gimple_build_bind (BIND_கோவை_VARS (stmt), வெற்று,
					    BIND_கோவை_BLOCK (stmt));
      gimple_bind_set_body (bind_stmt, seq);
      gimple_seq_add_stmt_without_update (&body, bind_stmt);
      gimple_set_body (current_function_decl, body);
    }
  இல்லையெனில்
    {
      /* Control-flow and binds are lowered, record local decls.  */
      க்கு (மரம் var = BIND_கோவை_VARS (stmt); var; var = DECL_CHAIN (var))
	எனில் (VAR_P (var)
	    && !DECL_EXTERNAL (var))
	  {
	    add_local_decl (cfun, var);
	    /* When the middle-end re-gimplifies any expression we might
	       run into the assertion that we've seen the decl in a BIND.  */
	    எனில் (!மரம்_STATIC (var))
	      DECL_SEEN_IN_BIND_கோவை_P (var) = 1;
	  }
      /* We have a CFG.  Build the edges.  */
      க்கு (unsigned i = 0; i < parser.edges.length (); ++i)
	{
	  edge e = make_edge (BASIC_BLOCK_FOR_FN (cfun, parser.edges[i].src),
			      BASIC_BLOCK_FOR_FN (cfun, parser.edges[i].dest),
			      parser.edges[i].flags);
	  e->probability = parser.edges[i].probability;
	}
      /* Add edges for case labels.  */
      basic_block bb;
      FOR_EACH_BB_FN (bb, cfun)
	எனில் (EDGE_மொத்தம் (bb->succs) == 0)
	  {
	    எனில் (gswitch *sw = safe_dyn_cast <gswitch *> (*gsi_last_bb (bb)))
	      க்கு (unsigned i = 0; i < gimple_switch_இலக்கம்_labels (sw); ++i)
		{
		  basic_block label_bb = gimple_switch_label_bb (cfun, sw, i);
		  make_edge (bb, label_bb, 0);
		}
	  }
      /* Need those for loop fixup.  */
      calculate_dominance_info (CDI_DOMINATORS);
      /* With SSA lower PHIs parsed as internal function calls and
	 update stmts.  */
      எனில் (cdil == cdil_gimple_ssa)
	{
	  /* Create PHI nodes, they are parsed into __PHI internal calls
	     and update SSA operands.  */
	  FOR_EACH_BB_FN (bb, cfun)
	    {
	      gimple_stmt_iterator gsi;
	      க்கு (gsi = gsi_start_bb (bb); !gsi_end_p (gsi);)
		{
		  gimple *stmt = gsi_stmt (gsi);
		  எனில் (!gimple_call_internal_p (stmt, IFN_PHI))
		    நிறுத்து;

		  gphi *phi = create_phi_முனை (gimple_call_lhs (stmt), bb);
		  க்கு (unsigned i = 0; i < gimple_call_இலக்கம்_args (stmt); i += 2)
		    {
		      முழு srcidx = மரம்_INT_CST_கீழ் (gimple_call_arg (stmt, i));
		      edge e = find_edge (BASIC_BLOCK_FOR_FN (cfun, srcidx), bb);
		      எனில் (!e)
			c_parser_error (parser, "edge not found");
		      இல்லையெனில்
			add_phi_arg (phi, gimple_call_arg (stmt, i + 1), e,
				     UNKNOWN_LOCATION);
		    }
		  gsi_remove (&gsi, உண்மை);
		}
	      க்கு (; !gsi_end_p (gsi); gsi_next (&gsi))
		update_stmt (gsi_stmt (gsi));
	    }
	  /* Fill SSA name gaps, putting them on the freelist and diagnose
	     SSA names without definition.  */
	  க்கு (unsigned i = 1; i < இலக்கம்_ssa_names; ++i)
	    எனில் (!ssa_name (i))
	      {
		மரம் name = make_ssa_name_fn (cfun, integer_type_முனை, வெற்று, i);
		release_ssa_name_fn (cfun, name);
	      }
	    இல்லையெனில் எனில் (!SSA_NAME_DEF_STMT (ssa_name (i)))
	      error ("SSA name %qE with version %d has no definition",
		     ssa_name (i), i);
	  /* No explicit virtual operands (yet).  */
	  bitmap_obstack_initialize (வெற்று);
	  update_ssa (TODO_update_ssa_only_virtuals);
	  bitmap_obstack_release (வெற்று);
	  /* ???  By flushing the freelist after virtual operand SSA rewrite
	     we keep the gaps available for re-use like needed for the
	     PR89595 testcase but then usually virtual operands would have
	     taken most of them.  The fix is obviously to make virtual
	     operands explicit in the SSA IL.  */
	  flush_ssaname_freelist ();
	}
      fix_loop_structure (வெற்று);
    }

  எனில் (cfun->curr_properties & PROP_cfg)
    {
      ENTRY_BLOCK_PTR_FOR_FN (cfun)->மொத்தம் = entry_bb_மொத்தம்;
      gcov_type t = param_gimple_fe_computed_hot_bb_threshold;
      set_hot_bb_threshold (t);
      update_max_bb_மொத்தம் ();
      cgraph_முனை::get_create (cfun->decl);
      cgraph_edge::rebuild_edges ();
    }

  /* Perform IL validation and if any error is found abort compilation
     of this function by zapping its body.  */
  எனில் ((cfun->curr_properties & PROP_cfg)
      && verify_gimple_in_cfg (cfun, பொய், பொய்))
    init_empty_மரம்_cfg ();
  இல்லையெனில் எனில் (!(cfun->curr_properties & PROP_cfg)
	   && verify_gimple_in_seq (gimple_body (current_function_decl), பொய்))
    gimple_set_body (current_function_decl, வெற்று);

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

நிலையான தருக்க
c_parser_gimple_compound_statement (gimple_parser &parser, gimple_seq *seq)
{
  தருக்க return_p = பொய்;

  எனில் (! c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    திரும்பு பொய்;

  /* A compound statement starts with optional declarations.  */
  போது (c_parser_next_tokens_start_declaration (parser))
    {
      c_parser_gimple_declaration (parser);
      எனில் (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	திரும்பு பொய்;
    }

  போது (c_parser_next_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      எனில் (c_parser_error (parser))
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_BRACE, வெற்று);
	  திரும்பு return_p;
	}
      இல்லையெனில் எனில் (c_parser_next_token_is (parser, CPP_EOF))
	{
	  c_parser_error (parser, "expected declaration or statement");
	  திரும்பு return_p;
	}

      தேர்வு (c_parser_peek_token (parser)->type)
	{
	நிலை CPP_KEYWORD:
	  தேர்வு (c_parser_peek_token (parser)->keyword)
	    {
	    நிலை RID_AT_TRY:
	      c_parser_gimple_try_stmt (parser, seq);
	      நிறுத்து;
	    நிலை RID_IF:
	      c_parser_gimple_if_stmt (parser, seq);
	      நிறுத்து;
	    நிலை RID_SWITCH:
	      c_parser_gimple_switch_stmt (parser, seq);
	      நிறுத்து;
	    நிலை RID_GOTO:
	      {
		location_t loc = c_parser_peek_token (parser)->location;
		c_parser_consume_token (parser);
		எனில் (c_parser_next_token_is (parser, CPP_NAME))
		  {
		    மரம் label = c_parser_peek_token (parser)->மதிப்பு;
		    c_parser_consume_token (parser);
		    c_parser_gimple_goto_stmt (parser, loc, label, seq);
		    எனில் (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      திரும்பு return_p;
		  }
		}
	      நிறுத்து;
	    நிலை RID_RETURN:
	      return_p = உண்மை;
	      c_parser_gimple_return_stmt (parser, seq);
	      எனில் (! c_parser_require (parser, CPP_SEMICOLON,
				      "expected %<;%>"))
		திரும்பு return_p;
	      எனில் (cfun->curr_properties & PROP_cfg)
		parser.தள்ளு_edge (parser.current_bb->index, EXIT_BLOCK, 0,
				  profile_probability::uninitialized ());
	      நிறுத்து;
	    இயல்பு:
	      செல் கோவை_stmt;
	    }
	  நிறுத்து;
	நிலை CPP_NAME:
	  எனில் (c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_gimple_label (parser, seq);
	      நிறுத்து;
	    }
	  எனில் (c_parser_next_token_is (parser, CPP_NAME)
	      && c_parser_peek_token (parser)->id_kind == C_ID_ID
	      && strcmp (IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு),
			 "try") == 0)
	    {
	      c_parser_gimple_try_stmt (parser, seq);
	      நிறுத்து;
	    }
	  /* Basic block specification.
	     __BB (index, ...)  */
	  எனில் ((cfun->curr_properties & PROP_cfg)
	      && !strcmp (IDENTIFIER_POINTER
			    (c_parser_peek_token (parser)->மதிப்பு), "__BB"))
	    {
	      c_parser_consume_token (parser);
	      எனில் (! c_parser_require (parser, CPP_OPEN_PAREN,
				      "expected %<(%>"))
		திரும்பு return_p;
	      எனில் (c_parser_next_token_is_not (parser, CPP_எண்))
		{
		  c_parser_error (parser, "expected block index");
		  திரும்பு return_p;
		}
	      மரம் tnum = c_parser_peek_token (parser)->மதிப்பு;
	      எனில் (மரம்_CODE (tnum) != INTEGER_CST)
		{
		  c_parser_error (parser, "expected block index");
		  திரும்பு return_p;
		}
	      முழு index = மரம்_INT_CST_கீழ் (tnum);
	      எனில் (index < இலக்கம்_FIXED_BLOCKS
		  || (index < last_basic_block_for_fn (cfun)
		      && BASIC_BLOCK_FOR_FN (cfun, index) != வெற்று))
		{
		  c_parser_error (parser, "invalid block index");
		  திரும்பு return_p;
		}
	      முழு is_loop_header_of = -1;
	      profile_மொத்தம் bb_மொத்தம் = profile_மொத்தம்::uninitialized ();
	      c_parser_consume_token (parser);
	      போது (c_parser_next_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  எனில் (! c_parser_next_token_is (parser, CPP_NAME))
		    {
		      c_parser_error (parser, "expected block specifier");
		      திரும்பு return_p;
		    }
		  /* loop_header (NUM)  */
		  எனில் (!strcmp (IDENTIFIER_POINTER
			         (c_parser_peek_token (parser)->மதிப்பு),
			       "loop_header"))
		    {
		      c_parser_consume_token (parser);
		      எனில் (! c_parser_require (parser, CPP_OPEN_PAREN,
					      "expected %<(%>"))
			திரும்பு return_p;
		      மரம் loop_இலக்கம்;
		      எனில் (! c_parser_next_token_is (parser, CPP_எண்)
			  || மரம்_CODE (loop_இலக்கம்
					  = c_parser_peek_token (parser)->மதிப்பு)
			       != INTEGER_CST)
			{
			  c_parser_error (parser, "expected loop number");
			  திரும்பு return_p;
			}
		      c_parser_consume_token (parser);
		      is_loop_header_of = மரம்_INT_CST_கீழ் (loop_இலக்கம்);
		      எனில் (! c_parser_require (parser, CPP_CLOSE_PAREN,
					      "expected %<)%>"))
			திரும்பு return_p;
		    }
		  /* Parse profile: quality(value) */
		  இல்லையெனில்
		    {
		      மரம் q;
		      profile_quality quality;
		      மரம் v = c_parser_peek_token (parser)->மதிப்பு;
		      எனில் (!parse_profile_quality (IDENTIFIER_POINTER (v),
						  &quality))
			{
			  c_parser_error (parser, "unknown block specifier");
			  திரும்பு பொய்;
			}

		      c_parser_consume_token (parser);
		      எனில் (!c_parser_require (parser, CPP_OPEN_PAREN,
					     "expected %<(%>"))
			திரும்பு பொய்;

		      எனில் (!c_parser_next_token_is (parser, CPP_எண்)
			  || (மரம்_CODE (q = c_parser_peek_token (parser)->மதிப்பு)
			      != INTEGER_CST))
			{
			  c_parser_error (parser, "expected count value");
			  திரும்பு பொய்;
			}

		      bb_மொத்தம்
			= profile_மொத்தம்::from_gcov_type (மரம்_INT_CST_கீழ் (q),
							 quality);
		      c_parser_consume_token (parser);
		      எனில் (! c_parser_require (parser, CPP_CLOSE_PAREN,
					      "expected %<)%>"))
			திரும்பு return_p;
		    }
		}
	      எனில் (! c_parser_require (parser, CPP_CLOSE_PAREN,
				      "expected %<)%>")
		  || ! c_parser_require (parser, CPP_COLON,
					 "expected %<:%>"))
		திரும்பு return_p;

	      /* Put stmts parsed in the current block.  */
	      எனில் (!gimple_seq_empty_p (*seq))
		{
		  எனில் (!parser.current_bb)
		    c_parser_error (parser, "stmts without block");
		  இல்லையெனில்
		    {
		      gimple_stmt_iterator gsi
			= gsi_start_bb (parser.current_bb);
		      gsi_செருகு_seq_after_without_update (&gsi, *seq,
							   GSI_CONTINUE_LINKING);
		    }
		  *seq = வெற்று;
		}

	      /* Build an empty block with specified index, linking them
		 in source order.  */
	      basic_block bb = alloc_block ();
	      bb->index = index;
	      link_block (bb, (parser.current_bb ? parser.current_bb
			       : ENTRY_BLOCK_PTR_FOR_FN (cfun)));
	      எனில் (basic_block_info_for_fn (cfun)->length () <= (size_t)index)
		vec_safe_grow_cleared (basic_block_info_for_fn (cfun),
				       index + 1, உண்மை);
	      SET_BASIC_BLOCK_FOR_FN (cfun, index, bb);
	      எனில் (last_basic_block_for_fn (cfun) <= index)
		last_basic_block_for_fn (cfun) = index + 1;
	      n_basic_blocks_for_fn (cfun)++;
	      எனில் (parser.current_bb->index == ENTRY_BLOCK)
		parser.தள்ளு_edge (ENTRY_BLOCK, bb->index, EDGE_FALLTHRU,
				  profile_probability::always ());

	      /* We leave the proper setting to fixup.  */
	      வகுப்பு loop *loop_father = loops_for_fn (cfun)->மரம்_வேர்;
	      /* If the new block is a loop header, allocate a loop
		 struct.  Fixup will take care of proper placement within
		 the loop tree.  */
	      எனில் (is_loop_header_of != -1)
		{
		  எனில் (எண்_of_loops (cfun) > (unsigned)is_loop_header_of
		      && get_loop (cfun, is_loop_header_of) != வெற்று)
		    {
		      c_parser_error (parser, "duplicate loop header");
		    }
		  இல்லையெனில்
		    {
		      வகுப்பு loop *loop = alloc_loop ();
		      loop->இலக்கம் = is_loop_header_of;
		      loop->header = bb;
		      எனில் (எண்_of_loops (cfun) <= (unsigned)is_loop_header_of)
			vec_safe_grow_cleared (loops_for_fn (cfun)->larray,
					       is_loop_header_of + 1, உண்மை);
		      (*loops_for_fn (cfun)->larray)[is_loop_header_of] = loop;
		      flow_loop_மரம்_முனை_add (loops_for_fn (cfun)->மரம்_வேர்,
					       loop);
		    }
		  loop_father = get_loop (cfun, is_loop_header_of);
		}
	      bb->loop_father = loop_father;
	      bb->மொத்தம் = bb_மொத்தம்;

	      /* Stmts now go to the new block.  */
	      parser.current_bb = bb;
	      நிறுத்து;
	    }
	  செல் கோவை_stmt;

	நிலை CPP_SEMICOLON:
	  {
	    /* Empty stmt.  */
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);
	    gimple *nop = gimple_build_nop ();
	    gimple_set_location (nop, loc);
	    gimple_seq_add_stmt_without_update (seq, nop);
	    நிறுத்து;
	  }

	நிலை CPP_CLOSE_PAREN:
	நிலை CPP_CLOSE_SQUARE:
	  /* Avoid infinite loop in error recovery:
	     c_parser_skip_until_found stops at a closing nesting
	     delimiter without consuming it, but here we need to consume
	     it to proceed further.  */
	  c_parser_error (parser, "expected statement");
	  c_parser_consume_token (parser);
	நிறுத்து;

	இயல்பு:
கோவை_stmt:
	  c_parser_gimple_statement (parser, seq);
	  எனில் (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	    c_parser_skip_until_found (parser, CPP_SEMICOLON, வெற்று);
	}
    }
  c_parser_consume_token (parser);

  /* Put stmts parsed in the current block.  */
  எனில் ((cfun->curr_properties & PROP_cfg)
      && !gimple_seq_empty_p (*seq))
    {
      எனில் (!parser.current_bb)
	c_parser_error (parser, "stmts without block");
      இல்லையெனில்
	{
	  gimple_stmt_iterator gsi = gsi_start_bb (parser.current_bb);
	  gsi_செருகு_seq_after_without_update (&gsi, *seq,
					       GSI_CONTINUE_LINKING);
	}
      *seq = வெற்று;
    }

  திரும்பு return_p;
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

நிலையான வெறுமை
c_parser_gimple_statement (gimple_parser &parser, gimple_seq *seq)
{
  கட்டமைப்பு c_கோவை lhs, rhs;
  gimple *assign = வெற்று;
  location_t loc;
  மரம் arg = NULL_மரம்;
  auto_vec<மரம்> vargs;

  lhs = c_parser_gimple_unary_expression (parser);
  loc = கோவை_LOCATION (lhs.மதிப்பு);
  rhs.set_error ();

  /* GIMPLE call statement without LHS.  */
  எனில் (c_parser_next_token_is (parser, CPP_SEMICOLON)
      && மரம்_CODE (lhs.மதிப்பு) == CALL_கோவை)
    {
      gimple *call;
      call = gimple_build_call_from_மரம் (lhs.மதிப்பு, வெற்று);
      gimple_seq_add_stmt_without_update (seq, call);
      gimple_set_location (call, loc);
      திரும்பு;
    }

  /* All following cases are statements with LHS.  */
  எனில் (! c_parser_require (parser, CPP_EQ, "expected %<=%>"))
    திரும்பு;

  /* Eat and ignore {v} right after the =, the has_volatile_ops is
     redundant and re-computed by the operand scanner.  */
  எனில் (c_parser_next_token_is (parser, CPP_OPEN_BRACE)
      && !(c_parser_peek_token (parser)->flags & PREV_WHITE)
      && c_parser_peek_2nd_token (parser)->type == CPP_NAME
      && !(c_parser_peek_2nd_token (parser)->flags & PREV_WHITE)
      && strcmp ("v", IDENTIFIER_POINTER
			(c_parser_peek_2nd_token (parser)->மதிப்பு)) == 0
      && c_parser_peek_nth_token (parser, 3)->type == CPP_CLOSE_BRACE
      && !(c_parser_peek_nth_token (parser, 3)->flags & PREV_WHITE))
    {
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }

  /* Cast expression.  */
  எனில் (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_typename (c_parser_peek_2nd_token (parser)))
    {
      c_parser_consume_token (parser);
      கட்டமைப்பு c_type_name *type_name = c_parser_type_name (parser);
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      எனில் (type_name == வெற்று)
	திரும்பு;
      /* ???  The actual type used in the cast expression is ignored as
         in GIMPLE it is encoded by the type of the LHS.  */
      rhs = c_parser_gimple_postfix_expression (parser);
      எனில் (lhs.மதிப்பு != error_mark_முனை
	  && rhs.மதிப்பு != error_mark_முனை)
	{
	  எண்ணிக்கை மரம்_code code = NOP_கோவை;
	  எனில் (FLOAT_TYPE_P (மரம்_TYPE (lhs.மதிப்பு))
	      && ! FLOAT_TYPE_P (மரம்_TYPE (rhs.மதிப்பு)))
	    code = FLOAT_கோவை;
	  இல்லையெனில் எனில் (! FLOAT_TYPE_P (மரம்_TYPE (lhs.மதிப்பு))
		   && FLOAT_TYPE_P (மரம்_TYPE (rhs.மதிப்பு)))
	    code = FIX_TRUNC_கோவை;
	  assign = gimple_build_assign (lhs.மதிப்பு, code, rhs.மதிப்பு);
	  gimple_seq_add_stmt_without_update (seq, assign);
	  gimple_set_location (assign, loc);
	  திரும்பு;
	}
    }

  /* Unary expression.  */
  தேர்வு (c_parser_peek_token (parser)->type)
    {
    நிலை CPP_NAME:
      {
	மரம் id = c_parser_peek_token (parser)->மதிப்பு;
	எனில் (strcmp (IDENTIFIER_POINTER (id), "__ABS") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__ABSU") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__MIN") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__MAX") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__BIT_INSERT") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__VEC_PERM") == 0)
	  செல் build_unary_கோவை;
	நிறுத்து;
      }
    நிலை CPP_KEYWORD:
      எனில் (c_parser_peek_token (parser)->keyword != RID_REALPART
	  && c_parser_peek_token (parser)->keyword != RID_IMAGPART)
	நிறுத்து;
      /* Fallthru.  */
    நிலை CPP_AND:
    நிலை CPP_PLUS:
    நிலை CPP_MINUS:
    நிலை CPP_COMPL:
    நிலை CPP_NOT:
    நிலை CPP_MULT: /* pointer deref */
    build_unary_கோவை:
      rhs = c_parser_gimple_unary_expression (parser);
      எனில் (rhs.மதிப்பு != error_mark_முனை)
	{
	  assign = gimple_build_assign (lhs.மதிப்பு, rhs.மதிப்பு);
	  gimple_set_location (assign, loc);
	  gimple_seq_add_stmt_without_update (seq, assign);
	}
      திரும்பு;

    இயல்பு:;
    }

  /* GIMPLE PHI statement.  */
  எனில் (c_parser_next_token_is_keyword (parser, RID_PHI))
    {
      c_parser_consume_token (parser);

      எனில் (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	திரும்பு;

      எனில் (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	c_parser_consume_token (parser);

      போது (c_parser_next_token_is_not (parser, CPP_CLOSE_PAREN))
	{
	  எனில் (c_parser_next_token_is (parser, CPP_NAME)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      arg = c_parser_peek_token (parser)->மதிப்பு;
	      c_parser_consume_token (parser);
	      எனில் (c_parser_next_token_is (parser, CPP_COLON))
		c_parser_consume_token (parser);
	      முழு src_index = -1;
	      எனில் (!c_parser_gimple_parse_bb_spec (arg, &src_index))
		c_parser_error (parser, "invalid source block specification");
	      vargs.safe_தள்ளு (size_int (src_index));
	    }
	  இல்லையெனில் எனில் (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  இல்லையெனில்
	    {
	      arg = c_parser_gimple_unary_expression (parser).மதிப்பு;
	      vargs.safe_தள்ளு (arg);
	    }
	}

      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");

      /* Build internal function for PHI.  */
      gcall *call_stmt = gimple_build_call_internal_vec (IFN_PHI, vargs);
      gimple_call_set_lhs (call_stmt, lhs.மதிப்பு);
      gimple_set_location (call_stmt, UNKNOWN_LOCATION);
      gimple_seq_add_stmt_without_update (seq, call_stmt);
      திரும்பு;
    }

  /* GIMPLE call with lhs.  */
  எனில் (c_parser_next_token_is (parser, CPP_DOT)
      || (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN
	  && lookup_name (c_parser_peek_token (parser)->மதிப்பு)))
    {
      rhs = c_parser_gimple_unary_expression (parser);
      எனில் (rhs.மதிப்பு != error_mark_முனை)
	{
	  gimple *call = gimple_build_call_from_மரம் (rhs.மதிப்பு, வெற்று);
	  gimple_call_set_lhs (call, lhs.மதிப்பு);
	  gimple_seq_add_stmt_without_update (seq, call);
	  gimple_set_location (call, loc);
	}
      திரும்பு;
    }

  rhs = c_parser_gimple_இருமம்_expression (parser, மரம்_TYPE (lhs.மதிப்பு));
  எனில் (lhs.மதிப்பு != error_mark_முனை
      && rhs.மதிப்பு != error_mark_முனை)
    {
      /* If we parsed an identifier and the next token  is a '?' then parse
	 a conditional expression.  */
      எனில் (SSA_VAR_P (rhs.மதிப்பு) && c_parser_next_token_is (parser, CPP_QUERY))
	{
	  கட்டமைப்பு c_கோவை trueval, falseval;
	  c_parser_consume_token (parser);
	  trueval = c_parser_gimple_postfix_expression (parser);
	  falseval.set_error ();
	  எனில் (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    falseval = c_parser_gimple_postfix_expression (parser);
	  எனில் (trueval.மதிப்பு == error_mark_முனை
	      || falseval.மதிப்பு == error_mark_முனை)
	    திரும்பு;
	  rhs.மதிப்பு = build3_loc (loc,
				  VECTOR_TYPE_P (மரம்_TYPE (rhs.மதிப்பு))
				  ? VEC_COND_கோவை : COND_கோவை,
				  மரம்_TYPE (trueval.மதிப்பு),
				  rhs.மதிப்பு, trueval.மதிப்பு, falseval.மதிப்பு);
	}
      எனில் (get_gimple_rhs_class (மரம்_CODE (rhs.மதிப்பு)) == GIMPLE_INVALID_RHS)
	{
	  c_parser_error (parser, "unexpected RHS for assignment");
	  திரும்பு;
	}
      assign = gimple_build_assign (lhs.மதிப்பு, rhs.மதிப்பு);
      gimple_seq_add_stmt_without_update (seq, assign);
      gimple_set_location (assign, loc);
    }
  திரும்பு;
}

/* A mapping between an identifier to a tree code for binary operations. */
நிலையான மாறிலி std::pair<மாறிலி எழுத்து *, மரம்_code> gimple_இருமம்_identifier_code[] =
  {
    {"__MULT_HIGHPART", MULT_HIGHPART_கோவை},
    {"__UNLT", UNLT_கோவை},
    {"__UNLE", UNLE_கோவை},
    {"__UNGT", UNGT_கோவை},
    {"__UNGE", UNGE_கோவை},
    {"__UNEQ", UNEQ_கோவை},
    {"__UNORDERED", UNORDERED_கோவை},
    {"__ORDERED", ORDERED_கோவை},
    {"__LTGT", LTGT_கோவை},
    {"__FLOOR_DIV", FLOOR_DIV_கோவை},
    {"__ROUND_DIV", ROUND_DIV_கோவை},
    {"__EXACT_DIV", EXACT_DIV_கோவை},
    {"__CEIL_DIV", CEIL_DIV_கோவை},
    {"__FLOOR_MOD", FLOOR_MOD_கோவை},
    {"__ROUND_MOD", ROUND_MOD_கோவை},
    {"__CEIL_MOD", CEIL_MOD_கோவை},
    {"__ROTATE_LEFT", LROTATE_கோவை},
    {"__ROTATE_RIGHT", RROTATE_கோவை},
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

நிலையான c_கோவை
c_parser_gimple_இருமம்_expression (gimple_parser &parser, மரம் ret_type)
{
  /* Location of the binary operator.  */
  கட்டமைப்பு c_கோவை ret, lhs, rhs;
  எண்ணிக்கை மரம்_code code = ERROR_MARK;
  ret.set_error ();
  lhs = c_parser_gimple_postfix_expression (parser, ret_type);
  எனில் (c_parser_error (parser))
    திரும்பு ret;
  தேர்வு (c_parser_peek_token (parser)->type)
    {
    நிலை CPP_MULT:
      code = MULT_கோவை;
      நிறுத்து;
    நிலை CPP_DIV:
      code = TRUNC_DIV_கோவை;
      நிறுத்து;
    நிலை CPP_MOD:
      code = TRUNC_MOD_கோவை;
      நிறுத்து;
    நிலை CPP_PLUS:
      எனில் (POINTER_TYPE_P (மரம்_TYPE (lhs.மதிப்பு)))
	code = POINTER_PLUS_கோவை;
      இல்லையெனில்
	code = PLUS_கோவை;
      நிறுத்து;
    நிலை CPP_MINUS:
      எனில் (POINTER_TYPE_P (மரம்_TYPE (lhs.மதிப்பு)))
	code = POINTER_DIFF_கோவை;
      இல்லையெனில்
	code = MINUS_கோவை;
      நிறுத்து;
    நிலை CPP_LSHIFT:
      code = LSHIFT_கோவை;
      நிறுத்து;
    நிலை CPP_RSHIFT:
      code = RSHIFT_கோவை;
      நிறுத்து;
    நிலை CPP_LESS:
      code = LT_கோவை;
      நிறுத்து;
    நிலை CPP_GREATER:
      code = GT_கோவை;
      நிறுத்து;
    நிலை CPP_LESS_EQ:
      code = LE_கோவை;
      நிறுத்து;
    நிலை CPP_GREATER_EQ:
      code = GE_கோவை;
      நிறுத்து;
    நிலை CPP_EQ_EQ:
      code = EQ_கோவை;
      நிறுத்து;
    நிலை CPP_NOT_EQ:
      code = NE_கோவை;
      நிறுத்து;
    நிலை CPP_AND:
      code = BIT_AND_கோவை;
      நிறுத்து;
    நிலை CPP_XOR:
      code = BIT_XOR_கோவை;
      நிறுத்து;
    நிலை CPP_OR:
      code = BIT_IOR_கோவை;
      நிறுத்து;
    நிலை CPP_AND_AND:
      c_parser_error (parser, "%<&&%> not valid in GIMPLE");
      திரும்பு ret;
    நிலை CPP_OR_OR:
      c_parser_error (parser, "%<||%> not valid in GIMPLE");
      திரும்பு ret;
    நிலை CPP_NAME:
      {
	மரம் id = c_parser_peek_token (parser)->மதிப்பு;
	க்கு (auto &p : gimple_இருமம்_identifier_code)
	  {
	    எனில் (strcmp (IDENTIFIER_POINTER (id), p.first) == 0)
	      {
		code = p.second;
		நிறுத்து;
	      }
	  }
	எனில் (code != ERROR_MARK)
	  நிறுத்து;
      }
      /* Fallthru.  */
    இயல்பு:
      /* Not a binary expression.  */
      திரும்பு lhs;
    }
  location_t ret_loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  rhs = c_parser_gimple_postfix_expression (parser);
  எனில் (lhs.மதிப்பு != error_mark_முனை && rhs.மதிப்பு != error_mark_முனை)
    ret.மதிப்பு = build2_loc (ret_loc, code, ret_type, lhs.மதிப்பு, rhs.மதிப்பு);
  திரும்பு ret;
}

/* Parse a gimple parentized binary expression.  */

நிலையான c_கோவை
c_parser_gimple_parentized_இருமம்_expression (gimple_parser &parser,
					      location_t op_loc,
					      மரம்_code code)
{
  கட்டமைப்பு c_கோவை ret;
  ret.set_error ();

  c_parser_consume_token (parser);
  எனில் (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    திரும்பு ret;
  c_கோவை op1 = c_parser_gimple_postfix_expression (parser);
  எனில் (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    திரும்பு ret;
  c_கோவை op2 = c_parser_gimple_postfix_expression (parser);
  எனில் (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    திரும்பு ret;

  எனில் (op1.மதிப்பு != error_mark_முனை && op2.மதிப்பு != error_mark_முனை)
    ret.மதிப்பு = build2_loc (op_loc,
			    code, மரம்_TYPE (op1.மதிப்பு), op1.மதிப்பு, op2.மதிப்பு);
  திரும்பு ret;
}

/* Parse a gimple parentized binary expression.  */

நிலையான c_கோவை
c_parser_gimple_parentized_ternary_expression (gimple_parser &parser,
					       location_t op_loc,
					       மரம்_code code)
{
  கட்டமைப்பு c_கோவை ret;
  ret.set_error ();

  c_parser_consume_token (parser);
  எனில் (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    திரும்பு ret;
  c_கோவை op1 = c_parser_gimple_postfix_expression (parser);
  எனில் (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    திரும்பு ret;
  c_கோவை op2 = c_parser_gimple_postfix_expression (parser);
  எனில் (!c_parser_require (parser, CPP_COMMA, "expected %<)%>"))
    திரும்பு ret;
  c_கோவை op3 = c_parser_gimple_postfix_expression (parser);
  எனில் (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    திரும்பு ret;

  எனில் (op1.மதிப்பு != error_mark_முனை
      && op2.மதிப்பு != error_mark_முனை
      && op3.மதிப்பு != error_mark_முனை)
    ret.மதிப்பு = build3_loc (op_loc,
			    code, மரம்_TYPE (op1.மதிப்பு),
			    op1.மதிப்பு, op2.மதிப்பு, op3.மதிப்பு);
  திரும்பு ret;
}

/* Parse gimple unary expression.

   gimple-unary-expression:
     gimple-postfix-expression
     unary-operator gimple-postfix-expression

   unary-operator: one of
     & * + - ~ abs_expr
*/

நிலையான c_கோவை
c_parser_gimple_unary_expression (gimple_parser &parser)
{
  கட்டமைப்பு c_கோவை ret, op;
  location_t op_loc = c_parser_peek_token (parser)->location;
  location_t finish;
  ret.set_error ();
  தேர்வு (c_parser_peek_token (parser)->type)
    {
    நிலை CPP_AND:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      mark_exp_read (op.மதிப்பு);
      திரும்பு gimple_parser_build_unary_op (op_loc, ADDR_கோவை, op);
    நிலை CPP_MULT:
      {
	c_parser_consume_token (parser);
	op = c_parser_gimple_postfix_expression (parser);
	எனில் (op.மதிப்பு == error_mark_முனை)
	  திரும்பு ret;
	எனில் (! POINTER_TYPE_P (மரம்_TYPE (op.மதிப்பு)))
	  {
	    error_at (op_loc, "expected pointer as argument of unary %<*%>");
	    திரும்பு ret;
	  }
	finish = op.get_finish ();
	location_t combined_loc = make_location (op_loc, op_loc, finish);
	ret.மதிப்பு = build_simple_mem_ref_loc (combined_loc, op.மதிப்பு);
	மரம்_SIDE_EFFECTS (ret.மதிப்பு)
	  = மரம்_THIS_VOLATILE (ret.மதிப்பு)
	  = TYPE_VOLATILE (மரம்_TYPE (மரம்_TYPE (op.மதிப்பு)));
	ret.src_range.m_start = op_loc;
	ret.src_range.m_finish = finish;
	திரும்பு ret;
      }
    நிலை CPP_PLUS:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      திரும்பு gimple_parser_build_unary_op (op_loc, CONVERT_கோவை, op);
    நிலை CPP_MINUS:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      திரும்பு gimple_parser_build_unary_op (op_loc, NEGATE_கோவை, op);
    நிலை CPP_COMPL:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      திரும்பு gimple_parser_build_unary_op (op_loc, BIT_NOT_கோவை, op);
    நிலை CPP_NOT:
      c_parser_error (parser, "%<!%> not valid in GIMPLE");
      திரும்பு ret;
    நிலை CPP_KEYWORD:
      தேர்வு (c_parser_peek_token (parser)->keyword)
	{
	நிலை RID_REALPART:
	  c_parser_consume_token (parser);
	  op = c_parser_gimple_postfix_expression (parser);
	  திரும்பு gimple_parser_build_unary_op (op_loc, REALPART_கோவை, op);
	நிலை RID_IMAGPART:
	  c_parser_consume_token (parser);
	  op = c_parser_gimple_postfix_expression (parser);
	  திரும்பு gimple_parser_build_unary_op (op_loc, IMAGPART_கோவை, op);
	இயல்பு:
	  திரும்பு c_parser_gimple_postfix_expression (parser);
	}
    நிலை CPP_NAME:
	{
	  மரம் id = c_parser_peek_token (parser)->மதிப்பு;
	  எனில் (strcmp (IDENTIFIER_POINTER (id), "__ABS") == 0)
	    {
	      c_parser_consume_token (parser);
	      op = c_parser_gimple_postfix_expression (parser);
	      திரும்பு gimple_parser_build_unary_op (op_loc, ABS_கோவை, op);
	    }
	  இல்லையெனில் எனில் (strcmp (IDENTIFIER_POINTER (id), "__ABSU") == 0)
	    {
	      c_parser_consume_token (parser);
	      op = c_parser_gimple_postfix_expression (parser);
	      திரும்பு gimple_parser_build_unary_op (op_loc, ABSU_கோவை, op);
	    }
	  இல்லையெனில் எனில் (strcmp (IDENTIFIER_POINTER (id), "__MIN") == 0)
	    திரும்பு c_parser_gimple_parentized_இருமம்_expression (parser,
								 op_loc,
								 MIN_கோவை);
	  இல்லையெனில் எனில் (strcmp (IDENTIFIER_POINTER (id), "__MAX") == 0)
	    திரும்பு c_parser_gimple_parentized_இருமம்_expression (parser,
								 op_loc,
								 MAX_கோவை);
	  இல்லையெனில் எனில் (strcmp (IDENTIFIER_POINTER (id), "__VEC_PERM") == 0)
	    திரும்பு c_parser_gimple_parentized_ternary_expression
			(parser, op_loc, VEC_PERM_கோவை);
	  இல்லையெனில் எனில் (strcmp (IDENTIFIER_POINTER (id), "__BIT_INSERT") == 0)
	    {
	      /* __BIT_INSERT '(' postfix-expression, postfix-expression,
			          integer ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      எனில் (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_கோவை op0 = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_கோவை op1 = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_கோவை op2 = c_parser_gimple_postfix_expression (parser);
		  எனில் (மரம்_CODE (op2.மதிப்பு) != INTEGER_CST
		      || !int_fits_type_p (op2.மதிப்பு, bitsizetype))
		    c_parser_error (parser, "expected constant offset");
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  எனில் (op0.மதிப்பு != error_mark_முனை
		      && op1.மதிப்பு != error_mark_முனை
		      && மரம்_CODE (op2.மதிப்பு) == INTEGER_CST)
		    ret.மதிப்பு = build3_loc (loc, BIT_செருகு_கோவை,
					    மரம்_TYPE (op0.மதிப்பு),
					    op0.மதிப்பு, op1.மதிப்பு,
					    fold_convert (bitsizetype,
							  op2.மதிப்பு));
		}
	      திரும்பு ret;
	    }
	  இல்லையெனில்
	    திரும்பு c_parser_gimple_postfix_expression (parser);
	}
    இயல்பு:
      திரும்பு c_parser_gimple_postfix_expression (parser);
    }
}

/* Decompose ID into base name (ID until ver_offset) and VERSION.  Return
   true if ID matches a SSA name.  */

நிலையான தருக்க
c_parser_parse_ssa_name_id (மரம் id, unsigned *version, unsigned *ver_offset)
{
  மாறிலி எழுத்து *token = IDENTIFIER_POINTER (id);
  மாறிலி எழுத்து *var_version = strrchr (token, '_');
  எனில் (! var_version)
    திரும்பு பொய்;

  *ver_offset = var_version - token;
  க்கு (மாறிலி எழுத்து *p = var_version + 1; *p; ++p)
    எனில் (! ISDIGIT (*p))
      திரும்பு பொய்;
  *version = atoi (var_version + 1);
  திரும்பு *version > 0;
}

/* Get at the actual SSA name ID with VERSION starting at VER_OFFSET.
   TYPE is the type if the SSA name is being declared.  */

நிலையான மரம்
c_parser_parse_ssa_name (gimple_parser &parser,
			 மரம் id, மரம் type, unsigned version,
			 unsigned ver_offset)
{
  மரம் name = NULL_மரம்;
  மாறிலி எழுத்து *token = IDENTIFIER_POINTER (id);

  எனில் (ver_offset == 0)
    {
      /* Anonymous unnamed SSA name.  */
      எனில் (version < இலக்கம்_ssa_names)
	name = ssa_name (version);
      எனில் (! name)
	{
	  எனில் (! type)
	    {
	      c_parser_error (parser, "SSA name undeclared");
	      திரும்பு error_mark_முனை;
	    }
	  name = make_ssa_name_fn (cfun, type, வெற்று, version);
	}
    }
  இல்லையெனில்
    {
      எனில் (version < இலக்கம்_ssa_names)
	name = ssa_name (version);
      எனில் (! name)
	{
	  /* Separate var name from version.  */
	  எழுத்து *var_name = XNEWVEC (எழுத்து, ver_offset + 1);
	  memcpy (var_name, token, ver_offset);
	  var_name[ver_offset] = '\0';
	  /* lookup for parent decl.  */
	  id = get_identifier (var_name);
	  மரம் parent = lookup_name (id);
	  XDELETEVEC (var_name);
	  எனில் (! parent || parent == error_mark_முனை)
	    {
	      c_parser_error (parser, "base variable or SSA name undeclared");
	      திரும்பு error_mark_முனை;
	    }
	  எனில் (!(VAR_P (parent)
		|| மரம்_CODE (parent) == PARM_DECL
		|| மரம்_CODE (parent) == RESULT_DECL))
	    {
	      error ("invalid base %qE for SSA name", parent);
	      திரும்பு error_mark_முனை;
	    }
	  name = make_ssa_name_fn (cfun, parent,
				   gimple_build_nop (), version);
	}
    }

  திரும்பு name;
}

/* Parse a gimple call to an internal function.

   gimple-call-internal:
     . identifier ( gimple-argument-expression-list[opt] )  */

நிலையான கட்டமைப்பு c_கோவை
c_parser_gimple_call_internal (gimple_parser &parser)
{
  கட்டமைப்பு c_கோவை கோவை;
  கோவை.set_error ();

  gcc_assert (c_parser_next_token_is (parser, CPP_DOT));
  c_parser_consume_token (parser);
  location_t loc = c_parser_peek_token (parser)->location;
  எனில் (!c_parser_next_token_is (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_kind != C_ID_ID)
    {
      c_parser_error (parser, "expecting internal function name");
      திரும்பு கோவை;
    }
  மரம் id = c_parser_peek_token (parser)->மதிப்பு;
  internal_fn ifn = lookup_internal_fn (IDENTIFIER_POINTER (id));
  c_parser_consume_token (parser);
  எனில் (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    {
      auto_vec<மரம்> exprlist;
      எனில் (!c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_gimple_கோவை_list (parser, &exprlist);
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      எனில் (ifn == IFN_LAST)
	error_at (loc, "unknown internal function %qE", id);
      இல்லையெனில்
	{
	  கோவை.மதிப்பு = build_call_கோவை_internal_loc_array
	    (loc, ifn, void_type_முனை, exprlist.length (),
	     exprlist.address ());
	  கோவை.original_code = ERROR_MARK;
	  கோவை.original_type = வெற்று;
	  கோவை.m_decimal = 0;
	}
    }
  திரும்பு கோவை;
}

/* Parse '<' type [',' alignment] '>' and return a type on success
   and NULL_TREE on error.  */

நிலையான மரம்
c_parser_gimple_typespec (gimple_parser &parser)
{
  கட்டமைப்பு c_type_name *type_name = வெற்று;
  மரம் alignment = NULL_மரம்;
  எனில் (c_parser_require (parser, CPP_LESS, "expected %<<%>"))
    {
      type_name = c_parser_type_name (parser);
      /* Optional alignment.  */
      எனில் (c_parser_next_token_is (parser, CPP_COMMA))
	{
	  c_parser_consume_token (parser);
	  alignment
	      = c_parser_gimple_postfix_expression (parser).மதிப்பு;
	}
      c_parser_skip_until_found (parser,
				 CPP_GREATER, "expected %<>%>");
    }
  எனில் (!type_name)
    திரும்பு NULL_மரம்;
  மரம் tem;
  மரம் type = groktypename (type_name, &tem, வெற்று);
  எனில் (alignment)
    type = build_aligned_type (type, மரம்_to_uhwi (alignment));
  திரும்பு type;
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

நிலையான கட்டமைப்பு c_கோவை
c_parser_gimple_postfix_expression (gimple_parser &parser, மரம் ret_type)
{
  location_t loc = c_parser_peek_token (parser)->location;
  source_range tok_range = c_parser_peek_token (parser)->get_range ();
  கட்டமைப்பு c_கோவை கோவை;
  கோவை.set_error ();
  தேர்வு (c_parser_peek_token (parser)->type)
    {
    நிலை CPP_எண்:
      கோவை.மதிப்பு = c_parser_peek_token (parser)->மதிப்பு;
      set_c_கோவை_source_range (&கோவை, tok_range);
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      நிறுத்து;
    நிலை CPP_CHAR:
    நிலை CPP_CHAR16:
    நிலை CPP_CHAR32:
    நிலை CPP_UTF8CHAR:
    நிலை CPP_WCHAR:
      கோவை.மதிப்பு = c_parser_peek_token (parser)->மதிப்பு;
      set_c_கோவை_source_range (&கோவை, tok_range);
      c_parser_consume_token (parser);
      நிறுத்து;
    நிலை CPP_STRING:
    நிலை CPP_STRING16:
    நிலை CPP_STRING32:
    நிலை CPP_WSTRING:
    நிலை CPP_UTF8STRING:
      கோவை = c_parser_string_literal (parser, பொய், உண்மை);
      நிறுத்து;
    நிலை CPP_DOT:
      கோவை = c_parser_gimple_call_internal (parser);
      நிறுத்து;
    நிலை CPP_NAME:
      எனில் (c_parser_peek_token (parser)->id_kind == C_ID_ID)
	{
	  மரம் id = c_parser_peek_token (parser)->மதிப்பு;
	  எனில் (strcmp (IDENTIFIER_POINTER (id), "__MEM") == 0)
	    {
	      /* __MEM '<' type-name [ ',' number ] '>'
	               '(' [ '(' type-name ')' ] unary-expression
			   [ '+' number ]
			   [ ',' number ]
			   [ ',' number ':' number ] ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      மரம் type = c_parser_gimple_typespec (parser);
	      கட்டமைப்பு c_கோவை ptr, alias_off, step, index, index2;
	      ptr.மதிப்பு = error_mark_முனை;
	      alias_off.மதிப்பு = NULL_மரம்;
	      step.மதிப்பு = NULL_மரம்;
	      index.மதிப்பு = NULL_மரம்;
	      index2.மதிப்பு = NULL_மரம்;
	      unsigned short clique = 0;
	      unsigned short base = 0;
	      தருக்க reverse_order = பொய்;
	      கட்டமைப்பு c_கோவை ro;
	      எனில் (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  மரம் alias_type = NULL_மரம்;
		  /* Optional alias-type cast.  */
		  எனில் (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
		    {
		      c_parser_consume_token (parser);
		      கட்டமைப்பு c_type_name *alias_type_name
			= c_parser_type_name (parser);
		      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
						 "expected %<)%>");
		      எனில் (alias_type_name)
			{
			  மரம் tem;
			  alias_type = groktypename (alias_type_name,
						     &tem, வெற்று);
			}
		    }
		  ptr = c_parser_gimple_unary_expression (parser);
		  எனில் (ptr.மதிப்பு == error_mark_முனை
		      || ! POINTER_TYPE_P (மரம்_TYPE (ptr.மதிப்பு)))
		    {
		      எனில் (ptr.மதிப்பு != error_mark_முனை)
			error_at (ptr.get_start (),
				  "invalid type of %<__MEM%> operand");
		      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
						 "expected %<)%>");
		      திரும்பு கோவை;
		    }
		  எனில் (! alias_type)
		    alias_type = மரம்_TYPE (ptr.மதிப்பு);
		  /* Optional constant offset.  */
		  எனில் (c_parser_next_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      alias_off = c_parser_gimple_postfix_expression (parser);
		    }
		  எனில் (c_parser_next_token_is (parser, CPP_MULT))
		    {
		      std::swap (index, alias_off);
		      c_parser_consume_token (parser);
		      step = c_parser_gimple_postfix_expression (parser);
		    }
		  இல்லையெனில் எனில் (c_parser_next_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      index = c_parser_gimple_postfix_expression (parser);
		      எனில் (c_parser_next_token_is (parser, CPP_MULT))
			{
			  c_parser_consume_token (parser);
			  step = c_parser_gimple_postfix_expression (parser);
			}
		      இல்லையெனில்
			std::swap (index, index2);
		    }
		  இல்லையெனில் எனில் (alias_off.மதிப்பு
			   && மரம்_CODE (alias_off.மதிப்பு) != INTEGER_CST)
		    std::swap (alias_off, index2);
		  எனில் (c_parser_next_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      index2 = c_parser_gimple_postfix_expression (parser);
		    }
		  எனில் (alias_off.மதிப்பு)
		    {
		      எனில் (மரம்_CODE (alias_off.மதிப்பு) != INTEGER_CST)
			error_at (alias_off.get_start (),
				  "expected constant offset for %<__MEM%> "
				  "operand");
		      alias_off.மதிப்பு = fold_convert (alias_type,
						      alias_off.மதிப்பு);
		    }
		  இல்லையெனில்
		    alias_off.மதிப்பு = build_int_cst (alias_type, 0);
		  எனில் (step.மதிப்பு)
		    {
		      எனில் (மரம்_CODE (step.மதிப்பு) != INTEGER_CST)
			error_at (step.get_start (),
				  "expected constant step for %<__MEM%> "
				  "operand");
		    }
		  எனில் (c_parser_next_token_is (parser, CPP_COMMA))
		    {
		      கட்டமைப்பு c_கோவை cl, ba;
		      தருக்க has_clb = உண்மை;
		      c_parser_consume_token (parser);
		      cl = c_parser_gimple_postfix_expression (parser);
		      எனில் (!c_parser_next_token_is (parser, CPP_COLON))
			{
			  ro = cl;
			  unsigned HOST_WIDE_INT tmp = 0;
			  எனில் (!மரம்_fits_uhwi_p (ro.மதிப்பு)
			      || (tmp = மரம்_to_uhwi (ro.மதிப்பு)) > 1)
			    error_at (ro.get_start (),
				      "invalid reverse order value");
			  reverse_order = tmp;
			  has_clb = பொய்;
			  எனில் (c_parser_next_token_is (parser, CPP_COMMA))
			    {
			      c_parser_consume_token (parser);
			      cl = c_parser_gimple_postfix_expression (parser);
		              has_clb = உண்மை;
			    }
			}
		      எனில் (has_clb
			  && c_parser_require (parser,
					       CPP_COLON, "expected %<:%>"))
			{
			  ba = c_parser_gimple_postfix_expression (parser);
			  எனில் (!மரம்_fits_uhwi_p (cl.மதிப்பு)
			      || !மரம்_fits_uhwi_p (ba.மதிப்பு)
			      || compare_மரம்_int (cl.மதிப்பு,
						   (clique = மரம்_to_uhwi
								(cl.மதிப்பு)))
			      || compare_மரம்_int (ba.மதிப்பு,
						   (base = மரம்_to_uhwi
								 (ba.மதிப்பு))))
			    error_at (cl.get_start (),
				      "invalid clique/base pair");
			}
		    }
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      எனில் (! type || c_parser_error (parser))
		{
		  c_parser_set_error (parser, பொய்);
		  திரும்பு கோவை;
		}
	      எனில் (index.மதிப்பு || step.மதிப்பு || index2.மதிப்பு)
		கோவை.மதிப்பு = build5_loc (loc, TARGET_MEM_REF,
					 type, ptr.மதிப்பு, alias_off.மதிப்பு,
					 index.மதிப்பு, step.மதிப்பு, index2.மதிப்பு);
	      இல்லையெனில்
		கோவை.மதிப்பு = build2_loc (loc, MEM_REF,
					 type, ptr.மதிப்பு, alias_off.மதிப்பு);
	      எனில் (clique != 0)
		{
		  cfun->last_clique = MAX (cfun->last_clique, clique);
		  MR_DEPENDENCE_CLIQUE (கோவை.மதிப்பு) = clique;
		  MR_DEPENDENCE_BASE (கோவை.மதிப்பு) = base;
		}
	      எனில் (reverse_order)
		{
		  எனில் (மரம்_CODE (கோவை.மதிப்பு) == MEM_REF)
		    REF_REVERSE_STORAGE_ORDER (கோவை.மதிப்பு) = reverse_order;
		  இல்லையெனில்
		    error_at (ro.get_start (),
			      "target mem ref cannot have reverse order");
		}
	      நிறுத்து;
	    }
	  இல்லையெனில் எனில் (strcmp (IDENTIFIER_POINTER (id), "__VIEW_CONVERT") == 0)
	    {
	      /* __VIEW_CONVERT '<' type-name [ ',' number ] '>'
	                        '(' postfix-expression ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      மரம் type = c_parser_gimple_typespec (parser);
	      எனில் (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_கோவை op = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  எனில் (type && op.மதிப்பு != error_mark_முனை)
		    கோவை.மதிப்பு = build1_loc (loc, VIEW_CONVERT_கோவை,
					     type, op.மதிப்பு);
		}
	      நிறுத்து;
	    }
	  இல்லையெனில் எனில் (strcmp (IDENTIFIER_POINTER (id), "__BIT_FIELD_REF") == 0)
	    {
	      /* __BIT_FIELD_REF '<' type-name [ ',' number ] '>'
	                        '(' postfix-expression, integer, integer ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      மரம் type = c_parser_gimple_typespec (parser);
	      எனில் (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_கோவை op0 = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_கோவை op1 = c_parser_gimple_postfix_expression (parser);
		  எனில் (மரம்_CODE (op1.மதிப்பு) != INTEGER_CST
		      || !int_fits_type_p (op1.மதிப்பு, bitsizetype))
		    c_parser_error (parser, "expected constant size");
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_கோவை op2 = c_parser_gimple_postfix_expression (parser);
		  எனில் (மரம்_CODE (op2.மதிப்பு) != INTEGER_CST
		      || !int_fits_type_p (op2.மதிப்பு, bitsizetype))
		    c_parser_error (parser, "expected constant offset");
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  எனில் (type
		      && op0.மதிப்பு != error_mark_முனை
		      && மரம்_CODE (op1.மதிப்பு) == INTEGER_CST
		      && மரம்_CODE (op2.மதிப்பு) == INTEGER_CST)
		    கோவை.மதிப்பு = build3_loc (loc, BIT_FIELD_REF, type,
					     op0.மதிப்பு,
					     fold_convert (bitsizetype,
							   op1.மதிப்பு),
					     fold_convert (bitsizetype,
							   op2.மதிப்பு));
		}
	      நிறுத்து;
	    }
	  இல்லையெனில் எனில் (strcmp (IDENTIFIER_POINTER (id), "__CLOBBER") == 0)
	    {
	      /* __CLOBBER [ '(' bob | eob | bos | eos ')' ]  */
	      clobber_kind kind = CLOBBER_UNDEF;
	      c_parser_consume_token (parser);
	      எனில் (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
		{
		  c_parser_consume_token (parser);
		  auto tok = c_parser_peek_token (parser);
		  எனில் (c_parser_require (parser, CPP_NAME,
					"expected clobber kind"))
		    {
		      மாறிலி எழுத்து *kind_str = IDENTIFIER_POINTER (tok->மதிப்பு);
		      எனில் (strcmp (kind_str, "bos") == 0)
			kind = CLOBBER_STORAGE_BEGIN;
		      இல்லையெனில் எனில் (strcmp (kind_str, "bob") == 0)
			kind = CLOBBER_OBJECT_BEGIN;
		      இல்லையெனில் எனில் (strcmp (kind_str, "eob") == 0)
			kind = CLOBBER_OBJECT_END;
		      இல்லையெனில் எனில் (strcmp (kind_str, "eos") == 0)
			kind = CLOBBER_STORAGE_END;
		      இல்லையெனில்
			c_parser_error (parser, "expected one of %<bos%>, "
					"%<eos%>, %<bob>, %<eob%>");
		    }
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      /* We infer the (redundant) type from the LHS.  */
	      கோவை.மதிப்பு = build_clobber (ret_type, kind);
	      நிறுத்து;
	    }
	  இல்லையெனில் எனில் (strcmp (IDENTIFIER_POINTER (id), "_Literal") == 0)
	    {
	      /* _Literal '(' type-name ')' ( [ '-' ] constant | constructor ) */
	      c_parser_consume_token (parser);
	      மரம் type = NULL_மரம்;
	      எனில் (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  கட்டமைப்பு c_type_name *type_name = c_parser_type_name (parser);
		  மரம் tem;
		  எனில் (type_name)
		    type = groktypename (type_name, &tem, வெற்று);
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      எனில் (! type)
		{
		  c_parser_error (parser, "invalid _Literal");
		  திரும்பு கோவை;
		}
	      எனில் (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
		{
		  c_parser_consume_token (parser);
		  எனில் (!AGGREGATE_TYPE_P (type)
		      && !VECTOR_TYPE_P (type))
		    {
		      c_parser_error (parser, "invalid type for _Literal with "
				      "constructor");
		      c_parser_skip_until_found (parser, CPP_CLOSE_BRACE,
						 "expected %<}%>");
		      திரும்பு கோவை;
		    }
		  vec<constructor_elt, va_gc> *v = வெற்று;
		  தருக்க constant_p = உண்மை;
		  எனில் (VECTOR_TYPE_P (type)
		      && !c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
		    {
		      vec_alloc (v, TYPE_VECTOR_SUBPARTS (type).to_constant ());
		      செய்
			{
			  மரம் val
			    = c_parser_gimple_postfix_expression (parser).மதிப்பு;
			  எனில் (! val
			      || val == error_mark_முனை
			      || (! CONSTANT_CLASS_P (val)
				  && ! SSA_VAR_P (val)))
			    {
			      c_parser_error (parser, "invalid _Literal");
			      திரும்பு கோவை;
			    }
			  CONSTRUCTOR_APPEND_ELT (v, NULL_மரம், val);
			  எனில் (! CONSTANT_CLASS_P (val))
			    constant_p = பொய்;
			  எனில் (c_parser_next_token_is (parser, CPP_COMMA))
			    c_parser_consume_token (parser);
			  இல்லையெனில்
			    நிறுத்து;
			}
		      போது (1);
		    }
		  எனில் (c_parser_require (parser, CPP_CLOSE_BRACE,
					"expected %<}%>"))
		    {
		      எனில் (v && constant_p)
			கோவை.மதிப்பு = build_vector_from_ctor (type, v);
		      இல்லையெனில்
			கோவை.மதிப்பு = build_constructor (type, v);
		    }
		  இல்லையெனில்
		    {
		      c_parser_skip_until_found (parser, CPP_CLOSE_BRACE,
						 "expected %<}%>");
		      திரும்பு கோவை;
		    }
		}
	      இல்லையெனில்
		{
		  தருக்க neg_p, addr_p;
		  எனில் ((neg_p = c_parser_next_token_is (parser, CPP_MINUS)))
		    c_parser_consume_token (parser);
		  எனில் ((addr_p = c_parser_next_token_is (parser, CPP_AND)))
		    c_parser_consume_token (parser);
		  மரம் val = c_parser_gimple_postfix_expression (parser).மதிப்பு;
		  எனில் (! val
		      || val == error_mark_முனை
		      || (!CONSTANT_CLASS_P (val) && !addr_p))
		    {
		      c_parser_error (parser, "invalid _Literal");
		      திரும்பு கோவை;
		    }
		  எனில் (addr_p)
		    {
		      val = build1 (ADDR_கோவை, type, val);
		      எனில் (!is_gimple_invariant_address (val))
			{
			  c_parser_error (parser, "invalid _Literal");
			  திரும்பு கோவை;
			}
		    }
		  எனில் (neg_p)
		    {
		      val = const_unop (NEGATE_கோவை, மரம்_TYPE (val), val);
		      எனில் (! val)
			{
			  c_parser_error (parser, "invalid _Literal");
			  திரும்பு கோவை;
			}
		    }
		  கோவை.மதிப்பு = fold_convert (type, val);
		}
	      திரும்பு கோவை;
	    }

	  /* SSA name.  */
	  unsigned version, ver_offset;
	  எனில் (! lookup_name (id)
	      && c_parser_parse_ssa_name_id (id, &version, &ver_offset))
	    {
	      c_parser_consume_token (parser);
	      கோவை.மதிப்பு = c_parser_parse_ssa_name (parser, id, NULL_மரம்,
						    version, ver_offset);
	      எனில் (கோவை.மதிப்பு == error_mark_முனை)
		திரும்பு கோவை;
	      set_c_கோவை_source_range (&கோவை, tok_range);
	      /* For default definition SSA names.  */
	      எனில் (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
		  && c_parser_peek_2nd_token (parser)->type == CPP_NAME
		  && strcmp ("D",
			     IDENTIFIER_POINTER
			       (c_parser_peek_2nd_token (parser)->மதிப்பு)) == 0
		  && c_parser_peek_nth_token (parser, 3)->type == CPP_CLOSE_PAREN)
		{
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		  எனில் (! SSA_NAME_IS_DEFAULT_DEF (கோவை.மதிப்பு))
		    {
		      எனில் (!SSA_NAME_VAR (கோவை.மதிப்பு))
			{
			  error_at (loc, "anonymous SSA name cannot have"
				    " default definition");
			  கோவை.மதிப்பு = error_mark_முனை;
			  திரும்பு கோவை;
			}
		      set_ssa_default_def (cfun, SSA_NAME_VAR (கோவை.மதிப்பு),
					   கோவை.மதிப்பு);
		      SSA_NAME_DEF_STMT (கோவை.மதிப்பு) = gimple_build_nop ();
		    }
		}
	    }
	  இல்லையெனில்
	    {
	      c_parser_consume_token (parser);
	      கோவை.மதிப்பு
		= build_external_ref (loc, id,
				      (c_parser_peek_token (parser)->type
				       == CPP_OPEN_PAREN), &கோவை.original_type);
	      set_c_கோவை_source_range (&கோவை, tok_range);
	    }
	  நிறுத்து;
	}
      /* Fallthru.  */
    இயல்பு:
      c_parser_error (parser, "expected expression");
      கோவை.set_error ();
      நிறுத்து;
    }
  எனில் (கோவை.மதிப்பு == error_mark_முனை)
    திரும்பு கோவை;
  திரும்பு c_parser_gimple_postfix_expression_after_primary
    (parser, கோவை_LOC_OR_LOC (கோவை.மதிப்பு, loc), கோவை);
}

/* Parse a gimple postfix expression after the initial primary or compound
   literal.  */

நிலையான கட்டமைப்பு c_கோவை
c_parser_gimple_postfix_expression_after_primary (gimple_parser &parser,
						  location_t கோவை_loc,
						  கட்டமைப்பு c_கோவை கோவை)
{
  location_t start;
  location_t finish;
  மரம் ident;
  location_t comp_loc;

  போது (உண்மை)
    {
      location_t op_loc = c_parser_peek_token (parser)->location;
      தேர்வு (c_parser_peek_token (parser)->type)
	{
	நிலை CPP_OPEN_SQUARE:
	  {
	    c_parser_consume_token (parser);
	    மரம் idx = c_parser_gimple_unary_expression (parser).மதிப்பு;

	    எனில் (! c_parser_require (parser, CPP_CLOSE_SQUARE, "expected %<]%>"))
	      {
		c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE, வெற்று);
		நிறுத்து;
	      }

	    start = கோவை.get_start ();
	    finish = c_parser_tokens_buf (parser, 0)->location;
	    கோவை.மதிப்பு = build_array_ref (op_loc, கோவை.மதிப்பு, idx);
	    set_c_கோவை_source_range (&கோவை, start, finish);
	    கோவை.m_decimal = 0;

	    கோவை.original_code = ERROR_MARK;
	    கோவை.original_type = வெற்று;
	    நிறுத்து;
	  }
	நிலை CPP_OPEN_PAREN:
	  {
	    /* Function call.  */
	    c_parser_consume_token (parser);
	    auto_vec<மரம்> exprlist;
	    எனில் (! c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	      c_parser_gimple_கோவை_list (parser, &exprlist);
	    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    எனில் (!FUNC_OR_METHOD_TYPE_P (மரம்_TYPE (கோவை.மதிப்பு)))
	      {
		c_parser_error (parser, "invalid call to non-function");
		கோவை.set_error ();
		நிறுத்து;
	      }
	    கோவை.மதிப்பு = build_call_array_loc
		(கோவை_loc, மரம்_TYPE (மரம்_TYPE (கோவை.மதிப்பு)),
		 கோவை.மதிப்பு, exprlist.length (), exprlist.address ());
	    கோவை.m_decimal = 0;
	    கோவை.original_code = ERROR_MARK;
	    கோவை.original_type = வெற்று;
	    நிறுத்து;
	  }
	நிலை CPP_DOT:
	  {
	    /* Structure element reference.  */
	    c_parser_consume_token (parser);
	    எனில் (c_parser_next_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		ident = comp_tok->மதிப்பு;
		comp_loc = comp_tok->location;
	      }
	    இல்லையெனில்
	      {
		c_parser_error (parser, "expected identifier");
		கோவை.set_error ();
		கோவை.original_code = ERROR_MARK;
		கோவை.original_type = வெற்று;
		திரும்பு கோவை;
	      }
	    start = கோவை.get_start ();
	    finish = c_parser_peek_token (parser)->get_finish ();
	    c_parser_consume_token (parser);
	    கோவை.மதிப்பு = build_component_ref (op_loc, கோவை.மதிப்பு, ident,
					      comp_loc, UNKNOWN_LOCATION);
	    set_c_கோவை_source_range (&கோவை, start, finish);
	    கோவை.m_decimal = 0;
	    கோவை.original_code = ERROR_MARK;
	    எனில் (மரம்_CODE (கோவை.மதிப்பு) != COMPONENT_REF)
	      கோவை.original_type = வெற்று;
	    இல்லையெனில்
	      {
		/* Remember the original type of a bitfield.  */
		மரம் field = மரம்_OPERAND (கோவை.மதிப்பு, 1);
		எனில் (மரம்_CODE (field) != FIELD_DECL)
		  கோவை.original_type = வெற்று;
		இல்லையெனில்
		  கோவை.original_type = DECL_BIT_FIELD_TYPE (field);
	      }
	    நிறுத்து;
	  }
	நிலை CPP_DEREF:
	  {
	    /* Structure element reference.  */
	    எனில் (!POINTER_TYPE_P (மரம்_TYPE (கோவை.மதிப்பு)))
	      {
		c_parser_error (parser, "dereference of non-pointer");
		கோவை.set_error ();
		கோவை.original_code = ERROR_MARK;
		கோவை.original_type = வெற்று;
		திரும்பு கோவை;
	      }
	    c_parser_consume_token (parser);
	    எனில் (c_parser_next_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		ident = comp_tok->மதிப்பு;
		comp_loc = comp_tok->location;
	      }
	    இல்லையெனில்
	      {
		c_parser_error (parser, "expected identifier");
		கோவை.set_error ();
		கோவை.original_code = ERROR_MARK;
		கோவை.original_type = வெற்று;
		திரும்பு கோவை;
	      }
	    start = கோவை.get_start ();
	    finish = c_parser_peek_token (parser)->get_finish ();
	    c_parser_consume_token (parser);
	    கோவை.மதிப்பு = build_component_ref (op_loc,
					      build_simple_mem_ref_loc
					        (op_loc, கோவை.மதிப்பு),
					      ident, comp_loc,
					      கோவை.get_location ());
	    set_c_கோவை_source_range (&கோவை, start, finish);
	    கோவை.m_decimal = 0;
	    கோவை.original_code = ERROR_MARK;
	    எனில் (மரம்_CODE (கோவை.மதிப்பு) != COMPONENT_REF)
	      கோவை.original_type = வெற்று;
	    இல்லையெனில்
	      {
		/* Remember the original type of a bitfield.  */
		மரம் field = மரம்_OPERAND (கோவை.மதிப்பு, 1);
		எனில் (மரம்_CODE (field) != FIELD_DECL)
		  கோவை.original_type = வெற்று;
		இல்லையெனில்
		  கோவை.original_type = DECL_BIT_FIELD_TYPE (field);
	      }
	    நிறுத்து;
	  }
	இயல்பு:
	  திரும்பு கோவை;
	}
    }
}

/* Parse expression list.

   gimple-expr-list:
     gimple-unary-expression
     gimple-expr-list , gimple-unary-expression

 */

நிலையான வெறுமை
c_parser_gimple_கோவை_list (gimple_parser &parser, vec<மரம்> *ret)
{
  கட்டமைப்பு c_கோவை கோவை;

  கோவை = c_parser_gimple_unary_expression (parser);
  ret->safe_தள்ளு (கோவை.மதிப்பு);
  போது (c_parser_next_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      கோவை = c_parser_gimple_unary_expression (parser);
      ret->safe_தள்ளு (கோவை.மதிப்பு);
    }
}

/* Parse gimple label.

   gimple-label:
     identifier :
     case constant-expression :
     default :

*/

நிலையான வெறுமை
c_parser_gimple_label (gimple_parser &parser, gimple_seq *seq)
{
  மரம் name = c_parser_peek_token (parser)->மதிப்பு;
  location_t loc1 = c_parser_peek_token (parser)->location;
  gcc_assert (c_parser_next_token_is (parser, CPP_NAME));
  c_parser_consume_token (parser);
  gcc_assert (c_parser_next_token_is (parser, CPP_COLON));
  c_parser_consume_token (parser);
  மரம் label = define_label (loc1, name);
  எனில் (label)
    gimple_seq_add_stmt_without_update (seq, gimple_build_label (label));
  திரும்பு;
}

/* Parse gimple/RTL pass list.

   gimple-or-rtl-pass-list:
     startwith("pass-name")[,{cfg,ssa}]
 */

வெறுமை
c_parser_gimple_or_rtl_pass_list (c_parser *parser, c_declspecs *specs)
{
  எழுத்து *pass = வெற்று;

  /* Accept __GIMPLE/__RTL.  */
  எனில் (c_parser_next_token_is_not (parser, CPP_OPEN_PAREN))
    திரும்பு;
  c_parser_consume_token (parser);

  specs->entry_bb_மொத்தம் = profile_மொத்தம்::uninitialized ();
  போது (c_parser_next_token_is (parser, CPP_NAME))
    {
      profile_quality quality;
      மாறிலி எழுத்து *op = IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு);
      c_parser_consume_token (parser);
      எனில் (! strcmp (op, "startwith"))
	{
	  எனில் (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    திரும்பு;
	  எனில் (c_parser_next_token_is_not (parser, CPP_STRING))
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"expected pass name");
	      திரும்பு;
	    }
	  pass = xstrdup (மரம்_STRING_POINTER
			  (c_parser_string_literal (parser, பொய்,
						    பொய்).மதிப்பு));
	  எனில் (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<(%>"))
	    திரும்பு;
	}
      இல்லையெனில் எனில் (parse_profile_quality (op, &quality))
	{
	  மரம் q;
	  எனில் (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    திரும்பு;

	  எனில் (!c_parser_next_token_is (parser, CPP_எண்)
	      || (மரம்_CODE (q = c_parser_peek_token (parser)->மதிப்பு)
		  != INTEGER_CST))
	    {
	      c_parser_error (parser, "expected count value");
	      திரும்பு;
	    }

	  specs->entry_bb_மொத்தம்
	    = profile_மொத்தம்::from_gcov_type (மரம்_INT_CST_கீழ் (q), quality);
	  c_parser_consume_token (parser);
	  எனில் (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    திரும்பு;
	}
      இல்லையெனில் எனில் (specs->declspec_il != cdil_gimple)
	/* Allow only one IL specifier and none on RTL.  */
	;
      இல்லையெனில் எனில் (! strcmp (op, "cfg"))
	specs->declspec_il = cdil_gimple_cfg;
      இல்லையெனில் எனில் (! strcmp (op, "ssa"))
	specs->declspec_il = cdil_gimple_ssa;
      இல்லையெனில்
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "invalid operation");
	  திரும்பு;
	}
     எனில் (c_parser_next_token_is (parser, CPP_COMMA))
       c_parser_consume_token (parser);
    }

  எனில் (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    திரும்பு;

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

நிலையான வெறுமை
c_parser_gimple_declaration (gimple_parser &parser)
{
  கட்டமைப்பு c_declarator *declarator;
  கட்டமைப்பு c_declspecs *specs = build_null_declspecs ();
  c_parser_declspecs (parser, specs, உண்மை, உண்மை, உண்மை,
		      உண்மை, உண்மை, உண்மை, உண்மை, cla_nonabstract_decl);
  finish_declspecs (specs);

  /* Provide better error recovery.  Note that a type name here is usually
     better diagnosed as a redeclaration.  */
  எனில் (c_parser_next_token_starts_declspecs (parser)
      && ! c_parser_next_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<;%>");
      c_parser_set_error (parser, பொய்);
      திரும்பு;
    }

  தருக்க dummy = பொய்;
  declarator = c_parser_declarator (parser,
				    specs->typespec_kind != ctsk_none,
				    C_DTR_NORMAL, &dummy);

  எனில் (!c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_error (parser, "expected %<;%>");
      திரும்பு;
    }
  எனில் (declarator)
    {
      /* Handle SSA name decls specially, they do not go into the identifier
         table but we simply build the SSA name for later lookup.  */
      unsigned version, ver_offset;
      /* Handle SSA pointer declarations in a very simplistic ways, we
	 probably would like to call grokdeclarator in a special mode to
	 just build the type of the decl - start_decl already pushes
	 the identifier to the bindings for lookup, something we do not
	 want.  */
      கட்டமைப்பு c_declarator *id_declarator = declarator;
      போது (id_declarator->kind == cdk_pointer)
	id_declarator = id_declarator->declarator;
      எனில் (id_declarator->kind == cdk_id
	  && (declarator->kind == cdk_pointer
	      || is_gimple_reg_type (specs->type))
	  && c_parser_parse_ssa_name_id (id_declarator->u.id.id,
					 &version, &ver_offset)
	  /* The following restricts it to unnamed anonymous SSA names
	     which fails parsing of named ones in dumps (we could
	     decide to not dump their name for -gimple).  */
	  && ver_offset == 0)
	{
	  கட்டமைப்பு c_declarator *p = declarator;
	  மரம் type = specs->type;
	  போது (p->kind == cdk_pointer)
	    {
	      type = build_pointer_type (type);
	      p = p->declarator;
	    }
	  c_parser_parse_ssa_name (parser, id_declarator->u.id.id, type,
				   version, ver_offset);
	}
      இல்லையெனில்
	{
	  மரம் postfix_attrs = NULL_மரம்;
	  மரம் all_prefix_attrs = specs->attrs;
	  specs->attrs = வெற்று;
	  மரம் decl = start_decl (declarator, specs, பொய்,
				  chainon (postfix_attrs, all_prefix_attrs));
	  எனில் (decl)
	    finish_decl (decl, UNKNOWN_LOCATION, NULL_மரம், NULL_மரம்,
			 NULL_மரம்);
	}
    }
}

/* Parse gimple goto statement.  */

நிலையான வெறுமை
c_parser_gimple_goto_stmt (gimple_parser &parser,
			   location_t loc, மரம் label, gimple_seq *seq)
{
  எனில் (cfun->curr_properties & PROP_cfg)
    {
      முழு dest_index;
      profile_probability prob;
      எனில் (c_parser_gimple_parse_bb_spec_edge_probability (label, parser,
							  &dest_index, &prob))
	{
	  parser.தள்ளு_edge (parser.current_bb->index, dest_index,
			    EDGE_FALLTHRU, prob);
	  திரும்பு;
	}
    }
  மரம் decl = lookup_label_for_goto (loc, label);
  gimple_seq_add_stmt_without_update (seq, gimple_build_goto (decl));
}

/* Parse a parenthesized condition.
   gimple-condition:
     ( gimple-binary-expression )    */

நிலையான மரம்
c_parser_gimple_paren_condition (gimple_parser &parser)
{
  எனில் (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    திரும்பு error_mark_முனை;
  மரம் cond
    = c_parser_gimple_இருமம்_expression (parser, boolean_type_முனை).மதிப்பு;
  எனில் (cond != error_mark_முனை
      && ! COMPARISON_CLASS_P (cond)
      && ! CONSTANT_CLASS_P (cond)
      && ! SSA_VAR_P (cond))
    {
      c_parser_error (parser, "comparison required");
      cond = error_mark_முனை;
    }
  எனில் (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    திரும்பு error_mark_முனை;
  திரும்பு cond;
}

/* Parse gimple try statement.

   try-statement:
     try { ... } finally { ... }
     try { ... } finally { ... } else { ... }

   This could support try/catch as well, but it's not implemented yet.
 */

நிலையான வெறுமை
c_parser_gimple_try_stmt (gimple_parser &parser, gimple_seq *seq)
{
  gimple_seq tryseq = வெற்று;
  c_parser_consume_token (parser);
  c_parser_gimple_compound_statement (parser, &tryseq);

  எனில் ((c_parser_next_token_is (parser, CPP_KEYWORD)
       && c_parser_peek_token (parser)->keyword == RID_AT_FINALLY)
      || (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_token (parser)->id_kind == C_ID_ID
	  && strcmp (IDENTIFIER_POINTER (c_parser_peek_token (parser)->மதிப்பு),
		     "finally") == 0))
    {
      gimple_seq finseq = வெற்று;
      c_parser_consume_token (parser);
      c_parser_gimple_compound_statement (parser, &finseq);

      எனில் (c_parser_next_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_ELSE)
	{
	  gimple_seq elsseq = வெற்று;
	  c_parser_consume_token (parser);
	  c_parser_gimple_compound_statement (parser, &elsseq);

	  geh_else *stmt = gimple_build_eh_else (finseq, elsseq);
	  finseq = வெற்று;
	  gimple_seq_add_stmt_without_update (&finseq, stmt);
	}

      gtry *stmt = gimple_build_try (tryseq, finseq, GIMPLE_TRY_FINALLY);
      gimple_seq_add_stmt_without_update (seq, stmt);
    }
  இல்லையெனில் எனில் (c_parser_next_token_is (parser, CPP_KEYWORD)
      && c_parser_peek_token (parser)->keyword == RID_AT_CATCH)
    c_parser_error (parser, "%<catch%> is not supported");
  இல்லையெனில்
    c_parser_error (parser, "expected %<finally%> or %<catch%>");
}

/* Parse gimple if-else statement.

   if-statement:
     if ( gimple-binary-expression ) gimple-goto-statement
     if ( gimple-binary-expression ) gimple-goto-statement \
					else gimple-goto-statement
 */

நிலையான வெறுமை
c_parser_gimple_if_stmt (gimple_parser &parser, gimple_seq *seq)
{
  மரம் t_label = NULL_மரம், f_label = NULL_மரம், label;
  location_t loc;
  c_parser_consume_token (parser);
  மரம் cond = c_parser_gimple_paren_condition (parser);

  எனில் (c_parser_next_token_is_keyword (parser, RID_GOTO))
    {
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      எனில் (! c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected label");
	  திரும்பு;
	}
      label = c_parser_peek_token (parser)->மதிப்பு;
      c_parser_consume_token (parser);
      முழு dest_index;
      profile_probability prob;
      எனில் ((cfun->curr_properties & PROP_cfg)
	  && c_parser_gimple_parse_bb_spec_edge_probability (label, parser,
							     &dest_index, &prob))
	parser.தள்ளு_edge (parser.current_bb->index, dest_index,
			  EDGE_TRUE_மதிப்பு, prob);
      இல்லையெனில்
	t_label = lookup_label_for_goto (loc, label);
      எனில் (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	திரும்பு;
    }
  இல்லையெனில்
    {
      c_parser_error (parser, "expected goto expression");
      திரும்பு;
    }

  எனில் (c_parser_next_token_is_keyword (parser, RID_ELSE))
    c_parser_consume_token (parser);
  இல்லையெனில்
    {
      c_parser_error (parser, "expected else statement");
      திரும்பு;
    }

  எனில் (c_parser_next_token_is_keyword (parser, RID_GOTO))
    {
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      எனில் (! c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected label");
	  திரும்பு;
	}
      label = c_parser_peek_token (parser)->மதிப்பு;
      c_parser_consume_token (parser);
      முழு dest_index;
      profile_probability prob;
      எனில் ((cfun->curr_properties & PROP_cfg)
	  && c_parser_gimple_parse_bb_spec_edge_probability (label, parser,
							     &dest_index, &prob))
	parser.தள்ளு_edge (parser.current_bb->index, dest_index,
			  EDGE_FALSE_மதிப்பு, prob);
      இல்லையெனில்
	f_label = lookup_label_for_goto (loc, label);
      எனில் (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	திரும்பு;
    }
  இல்லையெனில்
    {
      c_parser_error (parser, "expected goto expression");
      திரும்பு;
    }

  எனில் (cond != error_mark_முனை)
    gimple_seq_add_stmt_without_update (seq, gimple_build_cond_from_மரம் (cond, t_label,
							   f_label));
}

/* Parse gimple switch-statement.

   gimple-switch-statement:
     switch (gimple-postfix-expression) gimple-case-statement

   gimple-case-statement:
     gimple-case-statement
     gimple-label-statement : gimple-goto-statement
*/

நிலையான வெறுமை
c_parser_gimple_switch_stmt (gimple_parser &parser, gimple_seq *seq)
{
  c_கோவை cond_கோவை;
  மரம் case_label, label;
  auto_vec<மரம்> labels;
  மரம் default_label = NULL_மரம்;
  c_parser_consume_token (parser);

  எனில் (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    திரும்பு;
  cond_கோவை = c_parser_gimple_postfix_expression (parser);
  எனில் (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    திரும்பு;

  எனில் (! c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    திரும்பு;

  போது (c_parser_next_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      எனில் (c_parser_next_token_is (parser, CPP_EOF))
	{
	  c_parser_error (parser, "expected statement");
	  திரும்பு;
	}

      தேர்வு (c_parser_peek_token (parser)->keyword)
	{
	நிலை RID_CASE:
	  {
	    c_கோவை exp1;
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);

	    எனில் (c_parser_next_token_is (parser, CPP_NAME)
		|| c_parser_peek_token (parser)->type == CPP_எண்)
	      exp1 = c_parser_gimple_postfix_expression (parser);
	    இல்லையெனில்
	      {
		c_parser_error (parser, "expected expression");
		திரும்பு;
	      }

	    எனில் (c_parser_next_token_is (parser, CPP_COLON))
	      {
		c_parser_consume_token (parser);
		எனில் (c_parser_next_token_is (parser, CPP_NAME))
		  {
		    label = c_parser_peek_token (parser)->மதிப்பு;
		    c_parser_consume_token (parser);
		    மரம் decl = lookup_label_for_goto (loc, label);
		    case_label = build_case_label (exp1.மதிப்பு, NULL_மரம்,
						   decl);
		    labels.safe_தள்ளு (case_label);
		    எனில் (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      திரும்பு;
		  }
		இல்லையெனில் எனில் (! c_parser_require (parser, CPP_NAME,
					     "expected label"))
		  திரும்பு;
	      }
	    இல்லையெனில் எனில் (! c_parser_require (parser, CPP_SEMICOLON,
					 "expected %<:%>"))
	      திரும்பு;
	    நிறுத்து;
	  }
	நிலை RID_DEFAULT:
	  {
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);
	    எனில் (c_parser_next_token_is (parser, CPP_COLON))
	      {
		c_parser_consume_token (parser);
		எனில் (c_parser_next_token_is (parser, CPP_NAME))
		  {
		    label = c_parser_peek_token (parser)->மதிப்பு;
		    c_parser_consume_token (parser);
		    மரம் decl = lookup_label_for_goto (loc, label);
		    default_label = build_case_label (NULL_மரம், NULL_மரம்,
						      decl);
		    எனில் (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      திரும்பு;
		  }
		இல்லையெனில் எனில் (! c_parser_require (parser, CPP_NAME,
					     "expected label"))
		  திரும்பு;
	      }
	    இல்லையெனில் எனில் (! c_parser_require (parser, CPP_SEMICOLON,
					 "expected %<:%>"))
	      திரும்பு;
	    நிறுத்து;
	  }
	இயல்பு:
	  c_parser_error (parser, "expected case label");
	  திரும்பு;
	}

    }
  எனில் (! c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>"))
    திரும்பு;

  எனில் (cond_கோவை.மதிப்பு != error_mark_முனை)
    {
      gswitch *s = gimple_build_switch (cond_கோவை.மதிப்பு, default_label, labels);
      gimple_seq_add_stmt_without_update (seq, s);
    }
}

/* Parse gimple return statement.  */

நிலையான வெறுமை
c_parser_gimple_return_stmt (gimple_parser &parser, gimple_seq *seq)
{
  location_t loc = c_parser_peek_token (parser)->location;
  gimple *ret = வெற்று;
  c_parser_consume_token (parser);
  எனில் (c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      c_finish_gimple_return (loc, NULL_மரம்);
      ret = gimple_build_return (வெற்று);
      gimple_seq_add_stmt_without_update (seq, ret);
    }
  இல்லையெனில்
    {
      location_t xloc = c_parser_peek_token (parser)->location;
      c_கோவை கோவை = c_parser_gimple_unary_expression (parser);
      எனில் (கோவை.மதிப்பு != error_mark_முனை)
	{
	  c_finish_gimple_return (xloc, கோவை.மதிப்பு);
	  ret = gimple_build_return (கோவை.மதிப்பு);
	  gimple_seq_add_stmt_without_update (seq, ret);
	}
    }
}

/* Support function for c_parser_gimple_return_stmt.  */

நிலையான வெறுமை
c_finish_gimple_return (location_t loc, மரம் retval)
{
  மரம் valtype = மரம்_TYPE (மரம்_TYPE (current_function_decl));

  /* Use the expansion point to handle cases such as returning NULL
     in a function returning void.  */
  location_t xloc = expansion_point_location_if_in_system_header (loc);

  எனில் (மரம்_THIS_VOLATILE (current_function_decl))
    warning_at (xloc, 0,
		"function declared %<noreturn%> has a %<return%> statement");

  எனில் (! retval)
    current_function_returns_null = 1;
  இல்லையெனில் எனில் (valtype == 0 || VOID_TYPE_P (valtype))
    {
      current_function_returns_null = 1;
      எனில் (மரம்_CODE (மரம்_TYPE (retval)) != VOID_TYPE)
	{
	  error_at
	    (xloc, "%<return%> with a value, in function returning void");
	  inform (DECL_SOURCE_LOCATION (current_function_decl),
		  "declared here");
	}
    }
  இல்லையெனில் எனில் (மரம்_CODE (valtype) != மரம்_CODE (மரம்_TYPE (retval)))
    {
      error_at
	(xloc, "invalid conversion in return statement");
      inform (DECL_SOURCE_LOCATION (current_function_decl),
	      "declared here");
    }
  திரும்பு;
}
