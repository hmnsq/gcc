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

#شامل "config.h"
#شامل "system.h"
#شامل "coretypes.h"
#شامل "target.h"
#شامل "function.h"
#شامل "c-tree.h"
#شامل "timevar.h"
#شامل "stringpool.h"
#شامل "cgraph.h"
#شامل "attribs.h"
#شامل "stor-layout.h"
#شامل "varasm.h"
#شامل "trans-mem.h"
#شامل "c-family/c-pragma.h"
#شامل "c-lang.h"
#شامل "c-family/c-objc.h"
#شامل "plugin.h"
#شامل "builtins.h"
#شامل "gomp-constants.h"
#شامل "c-family/c-indentation.h"
#شامل "gimple-expr.h"
#شامل "context.h"
#شامل "gcc-rich-location.h"
#شامل "c-parser.h"
#شامل "tree-vrp.h"
#شامل "tree-pass.h"
#شامل "tree-pretty-print.h"
#شامل "tree.h"
#شامل "basic-block.h"
#شامل "gimple.h"
#شامل "gimple-pretty-print.h"
#شامل "tree-ssa.h"
#شامل "pass_manager.h"
#شامل "tree-ssanames.h"
#شامل "gimple-ssa.h"
#شامل "tree-dfa.h"
#شامل "internal-fn.h"
#شامل "cfg.h"
#شامل "cfghooks.h"
#شامل "bitmap.h"
#شامل "cfganal.h"
#شامل "tree-cfg.h"
#شامل "gimple-iterator.h"
#شامل "cfgloop.h"
#شامل "tree-phinodes.h"
#شامل "tree-into-ssa.h"


/* GIMPLE parser state.  */

رده gimple_parser
{
عمومی:
  gimple_parser (c_parser *p) : parser (p), edges(), current_bb(پوچ) {}
  /* c_parser is not visible here, use composition and fake inheritance
     via a conversion operator.  */
  operator c_parser *() { بازگشت parser; }
  c_parser *parser;

  /* CFG build state.  */
  رده gimple_parser_edge
  {
  عمومی:
    صحیح src;
    صحیح dest;
    صحیح flags;
    profile_probability probability;
  };
  auto_vec<gimple_parser_edge> edges;
  basic_block current_bb;

  تهی افزودن_edge (صحیح, صحیح, صحیح, profile_probability);
};

تهی
gimple_parser::افزودن_edge (صحیح src, صحیح dest, صحیح flags,
			  profile_probability prob)
{
  gimple_parser_edge e;
  e.src = src;
  e.dest = dest;
  e.flags = flags;
  e.probability = prob;
  edges.safe_افزودن (e);
}


/* Gimple parsing functions.  */
ایستا منطقی c_parser_gimple_compound_statement (gimple_parser &, gimple_seq *);
ایستا تهی c_parser_gimple_label (gimple_parser &, gimple_seq *);
ایستا تهی c_parser_gimple_statement (gimple_parser &, gimple_seq *);
ایستا ساختار c_عبارت c_parser_gimple_دودویی_expression (gimple_parser &, درخت);
ایستا ساختار c_عبارت c_parser_gimple_unary_expression (gimple_parser &);
ایستا ساختار c_عبارت c_parser_gimple_postfix_expression
			(gimple_parser &, درخت = error_mark_گره);
ایستا ساختار c_عبارت c_parser_gimple_postfix_expression_after_primary
			(gimple_parser &, location_t, ساختار c_عبارت);
ایستا تهی c_parser_gimple_declaration (gimple_parser &);
ایستا تهی c_parser_gimple_goto_stmt (gimple_parser &, location_t,
				       درخت, gimple_seq *);
ایستا تهی c_parser_gimple_try_stmt (gimple_parser &, gimple_seq *);
ایستا تهی c_parser_gimple_if_stmt (gimple_parser &, gimple_seq *);
ایستا تهی c_parser_gimple_switch_stmt (gimple_parser &, gimple_seq *);
ایستا تهی c_parser_gimple_return_stmt (gimple_parser &, gimple_seq *);
ایستا تهی c_finish_gimple_return (location_t, درخت);
ایستا درخت c_parser_gimple_paren_condition (gimple_parser &);
ایستا تهی c_parser_gimple_عبارت_list (gimple_parser &, vec<درخت> *);


/* Much like parser_build_unary_op, but avoid applying default conversions.  */

ایستا c_عبارت
gimple_parser_build_unary_op (location_t loc,
			      شمارش درخت_code code, ساختار c_عبارت arg)
{
  ساختار c_عبارت result;

  result.original_code = code;
  result.original_type = پوچ;
  result.m_decimal = 0;

  اگر (reject_gcc_builtin (arg.مقدار))
    {
      result.مقدار = error_mark_گره;
    }
  وگرنه
    {
      result.مقدار = build_unary_op (loc, code, arg.مقدار, درست);

      اگر (درخت_OVERFLOW_P (result.مقدار) && !درخت_OVERFLOW_P (arg.مقدار))
	overflow_warning (loc, result.مقدار, arg.مقدار);
    }

  /* We are typically called when parsing a prefix token at LOC acting on
     ARG.  Reflect this by updating the source range of the result to
     start at LOC and end at the end of ARG.  */
  set_c_عبارت_source_range (&result,
			   loc, arg.get_finish ());

  بازگشت result;
}

/* See if VAL is an identifier matching __BB<num> and return <num>
   in *INDEX.  */

ایستا منطقی
c_parser_gimple_parse_bb_spec (درخت val, صحیح *index)
{
  اگر (!startswith (IDENTIFIER_POINTER (val), "__BB"))
    بازگشت نادرست;

  ثابت نویسه *bb = IDENTIFIER_POINTER (val) + 4;
  اگر (! ISDIGIT (*bb))
    بازگشت نادرست;

  نویسه *pend;
  errno = 0;
  ثابت unsigned long عدد = strtoul (bb, &pend, 10);
  اگر (errno == ERANGE
      || *pend != '\0'
      || عدد > INT_MAX)
    بازگشت نادرست;

  *index = عدد;
  بازگشت درست;
}

/* See if VAL is an identifier matching __BB<num> and return <num>
   in *INDEX.  Return true if so and parse also FREQUENCY of
   the edge.  */


ایستا منطقی
c_parser_gimple_parse_bb_spec_edge_probability (درخت val,
						gimple_parser &parser,
						صحیح *index,
						profile_probability
						*probability)
{
  منطقی return_p = c_parser_gimple_parse_bb_spec (val, index);
  اگر (return_p)
    {
      *probability = profile_probability::uninitialized ();
      /* Parse frequency if provided.  */
      اگر (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	{
	  درخت f;
	  c_parser_consume_token (parser);
	  اگر (!c_parser_next_token_is (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected frequency quality");
	      بازگشت نادرست;
	    }

	  profile_quality quality;
	  ثابت نویسه *v
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار);
	  اگر (!parse_profile_quality (v, &quality))
	    {
	      c_parser_error (parser, "unknown profile quality");
	      بازگشت نادرست;
	    }

	  c_parser_consume_token (parser);
	  اگر (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    بازگشت نادرست;

	  اگر (!c_parser_next_token_is (parser, CPP_عدد)
	      || (درخت_CODE (f = c_parser_peek_token (parser)->مقدار)
		  != INTEGER_CST))
	    {
	      c_parser_error (parser, "expected frequency value");
	      بازگشت نادرست;
	    }

	  unsigned صحیح مقدار = درخت_INT_CST_کم (f);
	  *probability = profile_probability (مقدار, quality);

	  c_parser_consume_token (parser);
	  اگر (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    بازگشت نادرست;

	  اگر (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    بازگشت نادرست;
	}

      بازگشت درست;
    }

  بازگشت نادرست;

}

/* Parse the body of a function declaration marked with "__GIMPLE".  */

تهی
c_parser_parse_gimple_body (c_parser *cparser, نویسه *gimple_pass,
			    شمارش c_declspec_il cdil,
			    profile_شمار entry_bb_شمار)
{
  gimple_parser parser (cparser);
  gimple_seq seq = پوچ;
  gimple_seq body = پوچ;
  درخت stmt = افزودن_stmt_list ();
  افزودن_scope ();
  location_t loc1 = c_parser_peek_token (parser)->location;

  cfun->pass_startwith = gimple_pass;
  init_درخت_ssa (cfun);

  اگر (cdil == cdil_gimple)
    /* While we have SSA names in the IL we do not have a CFG built yet
       and PHIs are represented using a PHI internal function.  We do
       have lowered control flow and exception handling (well, we do not
       have parser support for EH yet).  But as we still have BINDs
       we have to go through lowering again.  */
    cfun->curr_properties = PROP_gimple_any;
  وگرنه
    {
      /* We have at least cdil_gimple_cfg.  */
      gimple_register_cfg_hooks ();
      init_empty_درخت_cfg ();
      parser.current_bb = ENTRY_BLOCK_PTR_FOR_FN (cfun);
      /* Initialize the bare loop structure - we are going to only
         mark headers and leave the rest to fixup.  */
      set_loops_for_fn (cfun, ggc_cleared_alloc<ساختار loops> ());
      init_loops_structure (cfun, loops_for_fn (cfun), 1);
      loops_state_set (cfun, LOOPS_NEED_FIXUP|LOOPS_MAY_HAVE_MULTIPLE_LATCHES);
      cfun->curr_properties
	|= PROP_gimple_lcf | PROP_gimple_leh | PROP_cfg | PROP_loops;
      اگر (cdil == cdil_gimple_ssa)
	{
	  init_ssa_operands (cfun);
	  cfun->curr_properties |= PROP_ssa;
	}
    }

  اگر (! c_parser_gimple_compound_statement (parser, &seq)
      && cdil == cdil_gimple)
    {
      gimple *ret = gimple_build_return (پوچ);
      gimple_seq_add_stmt_without_update (&seq, ret);
    }

  درخت block = برداشت_scope ();
  stmt = برداشت_stmt_list (stmt);
  stmt = c_build_bind_عبارت (loc1, block, stmt);

  block = DECL_INITIAL (current_function_decl);
  BLOCK_SUBBLOCKS (block) = NULL_درخت;
  BLOCK_CHAIN (block) = NULL_درخت;
  درخت_ASM_WRITTEN (block) = 1;

  اگر (cdil == cdil_gimple)
    {
      gbind *bind_stmt = gimple_build_bind (BIND_عبارت_VARS (stmt), پوچ,
					    BIND_عبارت_BLOCK (stmt));
      gimple_bind_set_body (bind_stmt, seq);
      gimple_seq_add_stmt_without_update (&body, bind_stmt);
      gimple_set_body (current_function_decl, body);
    }
  وگرنه
    {
      /* Control-flow and binds are lowered, record local decls.  */
      برای (درخت var = BIND_عبارت_VARS (stmt); var; var = DECL_CHAIN (var))
	اگر (VAR_P (var)
	    && !DECL_EXTERNAL (var))
	  {
	    add_local_decl (cfun, var);
	    /* When the middle-end re-gimplifies any expression we might
	       run into the assertion that we've seen the decl in a BIND.  */
	    اگر (!درخت_STATIC (var))
	      DECL_SEEN_IN_BIND_عبارت_P (var) = 1;
	  }
      /* We have a CFG.  Build the edges.  */
      برای (unsigned i = 0; i < parser.edges.length (); ++i)
	{
	  edge e = make_edge (BASIC_BLOCK_FOR_FN (cfun, parser.edges[i].src),
			      BASIC_BLOCK_FOR_FN (cfun, parser.edges[i].dest),
			      parser.edges[i].flags);
	  e->probability = parser.edges[i].probability;
	}
      /* Add edges for case labels.  */
      basic_block bb;
      FOR_EACH_BB_FN (bb, cfun)
	اگر (EDGE_شمار (bb->succs) == 0)
	  {
	    اگر (gswitch *sw = safe_dyn_cast <gswitch *> (*gsi_last_bb (bb)))
	      برای (unsigned i = 0; i < gimple_switch_رقم_labels (sw); ++i)
		{
		  basic_block label_bb = gimple_switch_label_bb (cfun, sw, i);
		  make_edge (bb, label_bb, 0);
		}
	  }
      /* Need those for loop fixup.  */
      calculate_dominance_info (CDI_DOMINATORS);
      /* With SSA lower PHIs parsed as internal function calls and
	 update stmts.  */
      اگر (cdil == cdil_gimple_ssa)
	{
	  /* Create PHI nodes, they are parsed into __PHI internal calls
	     and update SSA operands.  */
	  FOR_EACH_BB_FN (bb, cfun)
	    {
	      gimple_stmt_iterator gsi;
	      برای (gsi = gsi_start_bb (bb); !gsi_end_p (gsi);)
		{
		  gimple *stmt = gsi_stmt (gsi);
		  اگر (!gimple_call_internal_p (stmt, IFN_PHI))
		    بشکن;

		  gphi *phi = create_phi_گره (gimple_call_lhs (stmt), bb);
		  برای (unsigned i = 0; i < gimple_call_رقم_args (stmt); i += 2)
		    {
		      صحیح srcidx = درخت_INT_CST_کم (gimple_call_arg (stmt, i));
		      edge e = find_edge (BASIC_BLOCK_FOR_FN (cfun, srcidx), bb);
		      اگر (!e)
			c_parser_error (parser, "edge not found");
		      وگرنه
			add_phi_arg (phi, gimple_call_arg (stmt, i + 1), e,
				     UNKNOWN_LOCATION);
		    }
		  gsi_remove (&gsi, درست);
		}
	      برای (; !gsi_end_p (gsi); gsi_next (&gsi))
		update_stmt (gsi_stmt (gsi));
	    }
	  /* Fill SSA name gaps, putting them on the freelist and diagnose
	     SSA names without definition.  */
	  برای (unsigned i = 1; i < رقم_ssa_names; ++i)
	    اگر (!ssa_name (i))
	      {
		درخت name = make_ssa_name_fn (cfun, integer_type_گره, پوچ, i);
		release_ssa_name_fn (cfun, name);
	      }
	    وگرنه اگر (!SSA_NAME_DEF_STMT (ssa_name (i)))
	      error ("SSA name %qE with version %d has no definition",
		     ssa_name (i), i);
	  /* No explicit virtual operands (yet).  */
	  bitmap_obstack_initialize (پوچ);
	  update_ssa (TODO_update_ssa_only_virtuals);
	  bitmap_obstack_release (پوچ);
	  /* ???  By flushing the freelist after virtual operand SSA rewrite
	     we keep the gaps available for re-use like needed for the
	     PR89595 testcase but then usually virtual operands would have
	     taken most of them.  The fix is obviously to make virtual
	     operands explicit in the SSA IL.  */
	  flush_ssaname_freelist ();
	}
      fix_loop_structure (پوچ);
    }

  اگر (cfun->curr_properties & PROP_cfg)
    {
      ENTRY_BLOCK_PTR_FOR_FN (cfun)->شمار = entry_bb_شمار;
      gcov_type t = param_gimple_fe_computed_hot_bb_threshold;
      set_hot_bb_threshold (t);
      update_max_bb_شمار ();
      cgraph_گره::get_create (cfun->decl);
      cgraph_edge::rebuild_edges ();
    }

  /* Perform IL validation and if any error is found abort compilation
     of this function by zapping its body.  */
  اگر ((cfun->curr_properties & PROP_cfg)
      && verify_gimple_in_cfg (cfun, نادرست, نادرست))
    init_empty_درخت_cfg ();
  وگرنه اگر (!(cfun->curr_properties & PROP_cfg)
	   && verify_gimple_in_seq (gimple_body (current_function_decl), نادرست))
    gimple_set_body (current_function_decl, پوچ);

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

ایستا منطقی
c_parser_gimple_compound_statement (gimple_parser &parser, gimple_seq *seq)
{
  منطقی return_p = نادرست;

  اگر (! c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    بازگشت نادرست;

  /* A compound statement starts with optional declarations.  */
  وقتی (c_parser_next_tokens_start_declaration (parser))
    {
      c_parser_gimple_declaration (parser);
      اگر (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	بازگشت نادرست;
    }

  وقتی (c_parser_next_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      اگر (c_parser_error (parser))
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_BRACE, پوچ);
	  بازگشت return_p;
	}
      وگرنه اگر (c_parser_next_token_is (parser, CPP_EOF))
	{
	  c_parser_error (parser, "expected declaration or statement");
	  بازگشت return_p;
	}

      انتخاب (c_parser_peek_token (parser)->type)
	{
	حالت CPP_KEYWORD:
	  انتخاب (c_parser_peek_token (parser)->keyword)
	    {
	    حالت RID_AT_TRY:
	      c_parser_gimple_try_stmt (parser, seq);
	      بشکن;
	    حالت RID_IF:
	      c_parser_gimple_if_stmt (parser, seq);
	      بشکن;
	    حالت RID_SWITCH:
	      c_parser_gimple_switch_stmt (parser, seq);
	      بشکن;
	    حالت RID_GOTO:
	      {
		location_t loc = c_parser_peek_token (parser)->location;
		c_parser_consume_token (parser);
		اگر (c_parser_next_token_is (parser, CPP_NAME))
		  {
		    درخت label = c_parser_peek_token (parser)->مقدار;
		    c_parser_consume_token (parser);
		    c_parser_gimple_goto_stmt (parser, loc, label, seq);
		    اگر (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      بازگشت return_p;
		  }
		}
	      بشکن;
	    حالت RID_RETURN:
	      return_p = درست;
	      c_parser_gimple_return_stmt (parser, seq);
	      اگر (! c_parser_require (parser, CPP_SEMICOLON,
				      "expected %<;%>"))
		بازگشت return_p;
	      اگر (cfun->curr_properties & PROP_cfg)
		parser.افزودن_edge (parser.current_bb->index, EXIT_BLOCK, 0,
				  profile_probability::uninitialized ());
	      بشکن;
	    پیشفرض:
	      برو عبارت_stmt;
	    }
	  بشکن;
	حالت CPP_NAME:
	  اگر (c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_gimple_label (parser, seq);
	      بشکن;
	    }
	  اگر (c_parser_next_token_is (parser, CPP_NAME)
	      && c_parser_peek_token (parser)->id_kind == C_ID_ID
	      && strcmp (IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار),
			 "try") == 0)
	    {
	      c_parser_gimple_try_stmt (parser, seq);
	      بشکن;
	    }
	  /* Basic block specification.
	     __BB (index, ...)  */
	  اگر ((cfun->curr_properties & PROP_cfg)
	      && !strcmp (IDENTIFIER_POINTER
			    (c_parser_peek_token (parser)->مقدار), "__BB"))
	    {
	      c_parser_consume_token (parser);
	      اگر (! c_parser_require (parser, CPP_OPEN_PAREN,
				      "expected %<(%>"))
		بازگشت return_p;
	      اگر (c_parser_next_token_is_not (parser, CPP_عدد))
		{
		  c_parser_error (parser, "expected block index");
		  بازگشت return_p;
		}
	      درخت tnum = c_parser_peek_token (parser)->مقدار;
	      اگر (درخت_CODE (tnum) != INTEGER_CST)
		{
		  c_parser_error (parser, "expected block index");
		  بازگشت return_p;
		}
	      صحیح index = درخت_INT_CST_کم (tnum);
	      اگر (index < رقم_FIXED_BLOCKS
		  || (index < last_basic_block_for_fn (cfun)
		      && BASIC_BLOCK_FOR_FN (cfun, index) != پوچ))
		{
		  c_parser_error (parser, "invalid block index");
		  بازگشت return_p;
		}
	      صحیح is_loop_header_of = -1;
	      profile_شمار bb_شمار = profile_شمار::uninitialized ();
	      c_parser_consume_token (parser);
	      وقتی (c_parser_next_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  اگر (! c_parser_next_token_is (parser, CPP_NAME))
		    {
		      c_parser_error (parser, "expected block specifier");
		      بازگشت return_p;
		    }
		  /* loop_header (NUM)  */
		  اگر (!strcmp (IDENTIFIER_POINTER
			         (c_parser_peek_token (parser)->مقدار),
			       "loop_header"))
		    {
		      c_parser_consume_token (parser);
		      اگر (! c_parser_require (parser, CPP_OPEN_PAREN,
					      "expected %<(%>"))
			بازگشت return_p;
		      درخت loop_رقم;
		      اگر (! c_parser_next_token_is (parser, CPP_عدد)
			  || درخت_CODE (loop_رقم
					  = c_parser_peek_token (parser)->مقدار)
			       != INTEGER_CST)
			{
			  c_parser_error (parser, "expected loop number");
			  بازگشت return_p;
			}
		      c_parser_consume_token (parser);
		      is_loop_header_of = درخت_INT_CST_کم (loop_رقم);
		      اگر (! c_parser_require (parser, CPP_CLOSE_PAREN,
					      "expected %<)%>"))
			بازگشت return_p;
		    }
		  /* Parse profile: quality(value) */
		  وگرنه
		    {
		      درخت q;
		      profile_quality quality;
		      درخت v = c_parser_peek_token (parser)->مقدار;
		      اگر (!parse_profile_quality (IDENTIFIER_POINTER (v),
						  &quality))
			{
			  c_parser_error (parser, "unknown block specifier");
			  بازگشت نادرست;
			}

		      c_parser_consume_token (parser);
		      اگر (!c_parser_require (parser, CPP_OPEN_PAREN,
					     "expected %<(%>"))
			بازگشت نادرست;

		      اگر (!c_parser_next_token_is (parser, CPP_عدد)
			  || (درخت_CODE (q = c_parser_peek_token (parser)->مقدار)
			      != INTEGER_CST))
			{
			  c_parser_error (parser, "expected count value");
			  بازگشت نادرست;
			}

		      bb_شمار
			= profile_شمار::from_gcov_type (درخت_INT_CST_کم (q),
							 quality);
		      c_parser_consume_token (parser);
		      اگر (! c_parser_require (parser, CPP_CLOSE_PAREN,
					      "expected %<)%>"))
			بازگشت return_p;
		    }
		}
	      اگر (! c_parser_require (parser, CPP_CLOSE_PAREN,
				      "expected %<)%>")
		  || ! c_parser_require (parser, CPP_COLON,
					 "expected %<:%>"))
		بازگشت return_p;

	      /* Put stmts parsed in the current block.  */
	      اگر (!gimple_seq_empty_p (*seq))
		{
		  اگر (!parser.current_bb)
		    c_parser_error (parser, "stmts without block");
		  وگرنه
		    {
		      gimple_stmt_iterator gsi
			= gsi_start_bb (parser.current_bb);
		      gsi_درج_seq_after_without_update (&gsi, *seq,
							   GSI_CONTINUE_LINKING);
		    }
		  *seq = پوچ;
		}

	      /* Build an empty block with specified index, linking them
		 in source order.  */
	      basic_block bb = alloc_block ();
	      bb->index = index;
	      link_block (bb, (parser.current_bb ? parser.current_bb
			       : ENTRY_BLOCK_PTR_FOR_FN (cfun)));
	      اگر (basic_block_info_for_fn (cfun)->length () <= (size_t)index)
		vec_safe_grow_cleared (basic_block_info_for_fn (cfun),
				       index + 1, درست);
	      SET_BASIC_BLOCK_FOR_FN (cfun, index, bb);
	      اگر (last_basic_block_for_fn (cfun) <= index)
		last_basic_block_for_fn (cfun) = index + 1;
	      n_basic_blocks_for_fn (cfun)++;
	      اگر (parser.current_bb->index == ENTRY_BLOCK)
		parser.افزودن_edge (ENTRY_BLOCK, bb->index, EDGE_FALLTHRU,
				  profile_probability::always ());

	      /* We leave the proper setting to fixup.  */
	      رده loop *loop_father = loops_for_fn (cfun)->درخت_ریشه;
	      /* If the new block is a loop header, allocate a loop
		 struct.  Fixup will take care of proper placement within
		 the loop tree.  */
	      اگر (is_loop_header_of != -1)
		{
		  اگر (عدد_of_loops (cfun) > (unsigned)is_loop_header_of
		      && get_loop (cfun, is_loop_header_of) != پوچ)
		    {
		      c_parser_error (parser, "duplicate loop header");
		    }
		  وگرنه
		    {
		      رده loop *loop = alloc_loop ();
		      loop->رقم = is_loop_header_of;
		      loop->header = bb;
		      اگر (عدد_of_loops (cfun) <= (unsigned)is_loop_header_of)
			vec_safe_grow_cleared (loops_for_fn (cfun)->larray,
					       is_loop_header_of + 1, درست);
		      (*loops_for_fn (cfun)->larray)[is_loop_header_of] = loop;
		      flow_loop_درخت_گره_add (loops_for_fn (cfun)->درخت_ریشه,
					       loop);
		    }
		  loop_father = get_loop (cfun, is_loop_header_of);
		}
	      bb->loop_father = loop_father;
	      bb->شمار = bb_شمار;

	      /* Stmts now go to the new block.  */
	      parser.current_bb = bb;
	      بشکن;
	    }
	  برو عبارت_stmt;

	حالت CPP_SEMICOLON:
	  {
	    /* Empty stmt.  */
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);
	    gimple *nop = gimple_build_nop ();
	    gimple_set_location (nop, loc);
	    gimple_seq_add_stmt_without_update (seq, nop);
	    بشکن;
	  }

	حالت CPP_CLOSE_PAREN:
	حالت CPP_CLOSE_SQUARE:
	  /* Avoid infinite loop in error recovery:
	     c_parser_skip_until_found stops at a closing nesting
	     delimiter without consuming it, but here we need to consume
	     it to proceed further.  */
	  c_parser_error (parser, "expected statement");
	  c_parser_consume_token (parser);
	بشکن;

	پیشفرض:
عبارت_stmt:
	  c_parser_gimple_statement (parser, seq);
	  اگر (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	    c_parser_skip_until_found (parser, CPP_SEMICOLON, پوچ);
	}
    }
  c_parser_consume_token (parser);

  /* Put stmts parsed in the current block.  */
  اگر ((cfun->curr_properties & PROP_cfg)
      && !gimple_seq_empty_p (*seq))
    {
      اگر (!parser.current_bb)
	c_parser_error (parser, "stmts without block");
      وگرنه
	{
	  gimple_stmt_iterator gsi = gsi_start_bb (parser.current_bb);
	  gsi_درج_seq_after_without_update (&gsi, *seq,
					       GSI_CONTINUE_LINKING);
	}
      *seq = پوچ;
    }

  بازگشت return_p;
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

ایستا تهی
c_parser_gimple_statement (gimple_parser &parser, gimple_seq *seq)
{
  ساختار c_عبارت lhs, rhs;
  gimple *assign = پوچ;
  location_t loc;
  درخت arg = NULL_درخت;
  auto_vec<درخت> vargs;

  lhs = c_parser_gimple_unary_expression (parser);
  loc = عبارت_LOCATION (lhs.مقدار);
  rhs.set_error ();

  /* GIMPLE call statement without LHS.  */
  اگر (c_parser_next_token_is (parser, CPP_SEMICOLON)
      && درخت_CODE (lhs.مقدار) == CALL_عبارت)
    {
      gimple *call;
      call = gimple_build_call_from_درخت (lhs.مقدار, پوچ);
      gimple_seq_add_stmt_without_update (seq, call);
      gimple_set_location (call, loc);
      بازگشت;
    }

  /* All following cases are statements with LHS.  */
  اگر (! c_parser_require (parser, CPP_EQ, "expected %<=%>"))
    بازگشت;

  /* Eat and ignore {v} right after the =, the has_volatile_ops is
     redundant and re-computed by the operand scanner.  */
  اگر (c_parser_next_token_is (parser, CPP_OPEN_BRACE)
      && !(c_parser_peek_token (parser)->flags & PREV_WHITE)
      && c_parser_peek_2nd_token (parser)->type == CPP_NAME
      && !(c_parser_peek_2nd_token (parser)->flags & PREV_WHITE)
      && strcmp ("v", IDENTIFIER_POINTER
			(c_parser_peek_2nd_token (parser)->مقدار)) == 0
      && c_parser_peek_nth_token (parser, 3)->type == CPP_CLOSE_BRACE
      && !(c_parser_peek_nth_token (parser, 3)->flags & PREV_WHITE))
    {
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }

  /* Cast expression.  */
  اگر (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_typename (c_parser_peek_2nd_token (parser)))
    {
      c_parser_consume_token (parser);
      ساختار c_type_name *type_name = c_parser_type_name (parser);
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      اگر (type_name == پوچ)
	بازگشت;
      /* ???  The actual type used in the cast expression is ignored as
         in GIMPLE it is encoded by the type of the LHS.  */
      rhs = c_parser_gimple_postfix_expression (parser);
      اگر (lhs.مقدار != error_mark_گره
	  && rhs.مقدار != error_mark_گره)
	{
	  شمارش درخت_code code = NOP_عبارت;
	  اگر (FLOAT_TYPE_P (درخت_TYPE (lhs.مقدار))
	      && ! FLOAT_TYPE_P (درخت_TYPE (rhs.مقدار)))
	    code = FLOAT_عبارت;
	  وگرنه اگر (! FLOAT_TYPE_P (درخت_TYPE (lhs.مقدار))
		   && FLOAT_TYPE_P (درخت_TYPE (rhs.مقدار)))
	    code = FIX_TRUNC_عبارت;
	  assign = gimple_build_assign (lhs.مقدار, code, rhs.مقدار);
	  gimple_seq_add_stmt_without_update (seq, assign);
	  gimple_set_location (assign, loc);
	  بازگشت;
	}
    }

  /* Unary expression.  */
  انتخاب (c_parser_peek_token (parser)->type)
    {
    حالت CPP_NAME:
      {
	درخت id = c_parser_peek_token (parser)->مقدار;
	اگر (strcmp (IDENTIFIER_POINTER (id), "__ABS") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__ABSU") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__MIN") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__MAX") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__BIT_INSERT") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__VEC_PERM") == 0)
	  برو build_unary_عبارت;
	بشکن;
      }
    حالت CPP_KEYWORD:
      اگر (c_parser_peek_token (parser)->keyword != RID_REALPART
	  && c_parser_peek_token (parser)->keyword != RID_IMAGPART)
	بشکن;
      /* Fallthru.  */
    حالت CPP_AND:
    حالت CPP_PLUS:
    حالت CPP_MINUS:
    حالت CPP_COMPL:
    حالت CPP_NOT:
    حالت CPP_MULT: /* pointer deref */
    build_unary_عبارت:
      rhs = c_parser_gimple_unary_expression (parser);
      اگر (rhs.مقدار != error_mark_گره)
	{
	  assign = gimple_build_assign (lhs.مقدار, rhs.مقدار);
	  gimple_set_location (assign, loc);
	  gimple_seq_add_stmt_without_update (seq, assign);
	}
      بازگشت;

    پیشفرض:;
    }

  /* GIMPLE PHI statement.  */
  اگر (c_parser_next_token_is_keyword (parser, RID_PHI))
    {
      c_parser_consume_token (parser);

      اگر (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	بازگشت;

      اگر (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	c_parser_consume_token (parser);

      وقتی (c_parser_next_token_is_not (parser, CPP_CLOSE_PAREN))
	{
	  اگر (c_parser_next_token_is (parser, CPP_NAME)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      arg = c_parser_peek_token (parser)->مقدار;
	      c_parser_consume_token (parser);
	      اگر (c_parser_next_token_is (parser, CPP_COLON))
		c_parser_consume_token (parser);
	      صحیح src_index = -1;
	      اگر (!c_parser_gimple_parse_bb_spec (arg, &src_index))
		c_parser_error (parser, "invalid source block specification");
	      vargs.safe_افزودن (size_int (src_index));
	    }
	  وگرنه اگر (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  وگرنه
	    {
	      arg = c_parser_gimple_unary_expression (parser).مقدار;
	      vargs.safe_افزودن (arg);
	    }
	}

      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");

      /* Build internal function for PHI.  */
      gcall *call_stmt = gimple_build_call_internal_vec (IFN_PHI, vargs);
      gimple_call_set_lhs (call_stmt, lhs.مقدار);
      gimple_set_location (call_stmt, UNKNOWN_LOCATION);
      gimple_seq_add_stmt_without_update (seq, call_stmt);
      بازگشت;
    }

  /* GIMPLE call with lhs.  */
  اگر (c_parser_next_token_is (parser, CPP_DOT)
      || (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN
	  && lookup_name (c_parser_peek_token (parser)->مقدار)))
    {
      rhs = c_parser_gimple_unary_expression (parser);
      اگر (rhs.مقدار != error_mark_گره)
	{
	  gimple *call = gimple_build_call_from_درخت (rhs.مقدار, پوچ);
	  gimple_call_set_lhs (call, lhs.مقدار);
	  gimple_seq_add_stmt_without_update (seq, call);
	  gimple_set_location (call, loc);
	}
      بازگشت;
    }

  rhs = c_parser_gimple_دودویی_expression (parser, درخت_TYPE (lhs.مقدار));
  اگر (lhs.مقدار != error_mark_گره
      && rhs.مقدار != error_mark_گره)
    {
      /* If we parsed an identifier and the next token  is a '?' then parse
	 a conditional expression.  */
      اگر (SSA_VAR_P (rhs.مقدار) && c_parser_next_token_is (parser, CPP_QUERY))
	{
	  ساختار c_عبارت trueval, falseval;
	  c_parser_consume_token (parser);
	  trueval = c_parser_gimple_postfix_expression (parser);
	  falseval.set_error ();
	  اگر (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    falseval = c_parser_gimple_postfix_expression (parser);
	  اگر (trueval.مقدار == error_mark_گره
	      || falseval.مقدار == error_mark_گره)
	    بازگشت;
	  rhs.مقدار = build3_loc (loc,
				  VECTOR_TYPE_P (درخت_TYPE (rhs.مقدار))
				  ? VEC_COND_عبارت : COND_عبارت,
				  درخت_TYPE (trueval.مقدار),
				  rhs.مقدار, trueval.مقدار, falseval.مقدار);
	}
      اگر (get_gimple_rhs_class (درخت_CODE (rhs.مقدار)) == GIMPLE_INVALID_RHS)
	{
	  c_parser_error (parser, "unexpected RHS for assignment");
	  بازگشت;
	}
      assign = gimple_build_assign (lhs.مقدار, rhs.مقدار);
      gimple_seq_add_stmt_without_update (seq, assign);
      gimple_set_location (assign, loc);
    }
  بازگشت;
}

/* A mapping between an identifier to a tree code for binary operations. */
ایستا ثابت std::pair<ثابت نویسه *, درخت_code> gimple_دودویی_identifier_code[] =
  {
    {"__MULT_HIGHPART", MULT_HIGHPART_عبارت},
    {"__UNLT", UNLT_عبارت},
    {"__UNLE", UNLE_عبارت},
    {"__UNGT", UNGT_عبارت},
    {"__UNGE", UNGE_عبارت},
    {"__UNEQ", UNEQ_عبارت},
    {"__UNORDERED", UNORDERED_عبارت},
    {"__ORDERED", ORDERED_عبارت},
    {"__LTGT", LTGT_عبارت},
    {"__FLOOR_DIV", FLOOR_DIV_عبارت},
    {"__ROUND_DIV", ROUND_DIV_عبارت},
    {"__EXACT_DIV", EXACT_DIV_عبارت},
    {"__CEIL_DIV", CEIL_DIV_عبارت},
    {"__FLOOR_MOD", FLOOR_MOD_عبارت},
    {"__ROUND_MOD", ROUND_MOD_عبارت},
    {"__CEIL_MOD", CEIL_MOD_عبارت},
    {"__ROTATE_LEFT", LROTATE_عبارت},
    {"__ROTATE_RIGHT", RROTATE_عبارت},
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

ایستا c_عبارت
c_parser_gimple_دودویی_expression (gimple_parser &parser, درخت ret_type)
{
  /* Location of the binary operator.  */
  ساختار c_عبارت ret, lhs, rhs;
  شمارش درخت_code code = ERROR_MARK;
  ret.set_error ();
  lhs = c_parser_gimple_postfix_expression (parser, ret_type);
  اگر (c_parser_error (parser))
    بازگشت ret;
  انتخاب (c_parser_peek_token (parser)->type)
    {
    حالت CPP_MULT:
      code = MULT_عبارت;
      بشکن;
    حالت CPP_DIV:
      code = TRUNC_DIV_عبارت;
      بشکن;
    حالت CPP_MOD:
      code = TRUNC_MOD_عبارت;
      بشکن;
    حالت CPP_PLUS:
      اگر (POINTER_TYPE_P (درخت_TYPE (lhs.مقدار)))
	code = POINTER_PLUS_عبارت;
      وگرنه
	code = PLUS_عبارت;
      بشکن;
    حالت CPP_MINUS:
      اگر (POINTER_TYPE_P (درخت_TYPE (lhs.مقدار)))
	code = POINTER_DIFF_عبارت;
      وگرنه
	code = MINUS_عبارت;
      بشکن;
    حالت CPP_LSHIFT:
      code = LSHIFT_عبارت;
      بشکن;
    حالت CPP_RSHIFT:
      code = RSHIFT_عبارت;
      بشکن;
    حالت CPP_LESS:
      code = LT_عبارت;
      بشکن;
    حالت CPP_GREATER:
      code = GT_عبارت;
      بشکن;
    حالت CPP_LESS_EQ:
      code = LE_عبارت;
      بشکن;
    حالت CPP_GREATER_EQ:
      code = GE_عبارت;
      بشکن;
    حالت CPP_EQ_EQ:
      code = EQ_عبارت;
      بشکن;
    حالت CPP_NOT_EQ:
      code = NE_عبارت;
      بشکن;
    حالت CPP_AND:
      code = BIT_AND_عبارت;
      بشکن;
    حالت CPP_XOR:
      code = BIT_XOR_عبارت;
      بشکن;
    حالت CPP_OR:
      code = BIT_IOR_عبارت;
      بشکن;
    حالت CPP_AND_AND:
      c_parser_error (parser, "%<&&%> not valid in GIMPLE");
      بازگشت ret;
    حالت CPP_OR_OR:
      c_parser_error (parser, "%<||%> not valid in GIMPLE");
      بازگشت ret;
    حالت CPP_NAME:
      {
	درخت id = c_parser_peek_token (parser)->مقدار;
	برای (auto &p : gimple_دودویی_identifier_code)
	  {
	    اگر (strcmp (IDENTIFIER_POINTER (id), p.first) == 0)
	      {
		code = p.second;
		بشکن;
	      }
	  }
	اگر (code != ERROR_MARK)
	  بشکن;
      }
      /* Fallthru.  */
    پیشفرض:
      /* Not a binary expression.  */
      بازگشت lhs;
    }
  location_t ret_loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  rhs = c_parser_gimple_postfix_expression (parser);
  اگر (lhs.مقدار != error_mark_گره && rhs.مقدار != error_mark_گره)
    ret.مقدار = build2_loc (ret_loc, code, ret_type, lhs.مقدار, rhs.مقدار);
  بازگشت ret;
}

/* Parse a gimple parentized binary expression.  */

ایستا c_عبارت
c_parser_gimple_parentized_دودویی_expression (gimple_parser &parser,
					      location_t op_loc,
					      درخت_code code)
{
  ساختار c_عبارت ret;
  ret.set_error ();

  c_parser_consume_token (parser);
  اگر (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    بازگشت ret;
  c_عبارت op1 = c_parser_gimple_postfix_expression (parser);
  اگر (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    بازگشت ret;
  c_عبارت op2 = c_parser_gimple_postfix_expression (parser);
  اگر (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    بازگشت ret;

  اگر (op1.مقدار != error_mark_گره && op2.مقدار != error_mark_گره)
    ret.مقدار = build2_loc (op_loc,
			    code, درخت_TYPE (op1.مقدار), op1.مقدار, op2.مقدار);
  بازگشت ret;
}

/* Parse a gimple parentized binary expression.  */

ایستا c_عبارت
c_parser_gimple_parentized_ternary_expression (gimple_parser &parser,
					       location_t op_loc,
					       درخت_code code)
{
  ساختار c_عبارت ret;
  ret.set_error ();

  c_parser_consume_token (parser);
  اگر (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    بازگشت ret;
  c_عبارت op1 = c_parser_gimple_postfix_expression (parser);
  اگر (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    بازگشت ret;
  c_عبارت op2 = c_parser_gimple_postfix_expression (parser);
  اگر (!c_parser_require (parser, CPP_COMMA, "expected %<)%>"))
    بازگشت ret;
  c_عبارت op3 = c_parser_gimple_postfix_expression (parser);
  اگر (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    بازگشت ret;

  اگر (op1.مقدار != error_mark_گره
      && op2.مقدار != error_mark_گره
      && op3.مقدار != error_mark_گره)
    ret.مقدار = build3_loc (op_loc,
			    code, درخت_TYPE (op1.مقدار),
			    op1.مقدار, op2.مقدار, op3.مقدار);
  بازگشت ret;
}

/* Parse gimple unary expression.

   gimple-unary-expression:
     gimple-postfix-expression
     unary-operator gimple-postfix-expression

   unary-operator: one of
     & * + - ~ abs_expr
*/

ایستا c_عبارت
c_parser_gimple_unary_expression (gimple_parser &parser)
{
  ساختار c_عبارت ret, op;
  location_t op_loc = c_parser_peek_token (parser)->location;
  location_t finish;
  ret.set_error ();
  انتخاب (c_parser_peek_token (parser)->type)
    {
    حالت CPP_AND:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      mark_exp_read (op.مقدار);
      بازگشت gimple_parser_build_unary_op (op_loc, ADDR_عبارت, op);
    حالت CPP_MULT:
      {
	c_parser_consume_token (parser);
	op = c_parser_gimple_postfix_expression (parser);
	اگر (op.مقدار == error_mark_گره)
	  بازگشت ret;
	اگر (! POINTER_TYPE_P (درخت_TYPE (op.مقدار)))
	  {
	    error_at (op_loc, "expected pointer as argument of unary %<*%>");
	    بازگشت ret;
	  }
	finish = op.get_finish ();
	location_t combined_loc = make_location (op_loc, op_loc, finish);
	ret.مقدار = build_simple_mem_ref_loc (combined_loc, op.مقدار);
	درخت_SIDE_EFFECTS (ret.مقدار)
	  = درخت_THIS_VOLATILE (ret.مقدار)
	  = TYPE_VOLATILE (درخت_TYPE (درخت_TYPE (op.مقدار)));
	ret.src_range.m_start = op_loc;
	ret.src_range.m_finish = finish;
	بازگشت ret;
      }
    حالت CPP_PLUS:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      بازگشت gimple_parser_build_unary_op (op_loc, CONVERT_عبارت, op);
    حالت CPP_MINUS:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      بازگشت gimple_parser_build_unary_op (op_loc, NEGATE_عبارت, op);
    حالت CPP_COMPL:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      بازگشت gimple_parser_build_unary_op (op_loc, BIT_NOT_عبارت, op);
    حالت CPP_NOT:
      c_parser_error (parser, "%<!%> not valid in GIMPLE");
      بازگشت ret;
    حالت CPP_KEYWORD:
      انتخاب (c_parser_peek_token (parser)->keyword)
	{
	حالت RID_REALPART:
	  c_parser_consume_token (parser);
	  op = c_parser_gimple_postfix_expression (parser);
	  بازگشت gimple_parser_build_unary_op (op_loc, REALPART_عبارت, op);
	حالت RID_IMAGPART:
	  c_parser_consume_token (parser);
	  op = c_parser_gimple_postfix_expression (parser);
	  بازگشت gimple_parser_build_unary_op (op_loc, IMAGPART_عبارت, op);
	پیشفرض:
	  بازگشت c_parser_gimple_postfix_expression (parser);
	}
    حالت CPP_NAME:
	{
	  درخت id = c_parser_peek_token (parser)->مقدار;
	  اگر (strcmp (IDENTIFIER_POINTER (id), "__ABS") == 0)
	    {
	      c_parser_consume_token (parser);
	      op = c_parser_gimple_postfix_expression (parser);
	      بازگشت gimple_parser_build_unary_op (op_loc, ABS_عبارت, op);
	    }
	  وگرنه اگر (strcmp (IDENTIFIER_POINTER (id), "__ABSU") == 0)
	    {
	      c_parser_consume_token (parser);
	      op = c_parser_gimple_postfix_expression (parser);
	      بازگشت gimple_parser_build_unary_op (op_loc, ABSU_عبارت, op);
	    }
	  وگرنه اگر (strcmp (IDENTIFIER_POINTER (id), "__MIN") == 0)
	    بازگشت c_parser_gimple_parentized_دودویی_expression (parser,
								 op_loc,
								 MIN_عبارت);
	  وگرنه اگر (strcmp (IDENTIFIER_POINTER (id), "__MAX") == 0)
	    بازگشت c_parser_gimple_parentized_دودویی_expression (parser,
								 op_loc,
								 MAX_عبارت);
	  وگرنه اگر (strcmp (IDENTIFIER_POINTER (id), "__VEC_PERM") == 0)
	    بازگشت c_parser_gimple_parentized_ternary_expression
			(parser, op_loc, VEC_PERM_عبارت);
	  وگرنه اگر (strcmp (IDENTIFIER_POINTER (id), "__BIT_INSERT") == 0)
	    {
	      /* __BIT_INSERT '(' postfix-expression, postfix-expression,
			          integer ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      اگر (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_عبارت op0 = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_عبارت op1 = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_عبارت op2 = c_parser_gimple_postfix_expression (parser);
		  اگر (درخت_CODE (op2.مقدار) != INTEGER_CST
		      || !int_fits_type_p (op2.مقدار, bitsizetype))
		    c_parser_error (parser, "expected constant offset");
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  اگر (op0.مقدار != error_mark_گره
		      && op1.مقدار != error_mark_گره
		      && درخت_CODE (op2.مقدار) == INTEGER_CST)
		    ret.مقدار = build3_loc (loc, BIT_درج_عبارت,
					    درخت_TYPE (op0.مقدار),
					    op0.مقدار, op1.مقدار,
					    fold_convert (bitsizetype,
							  op2.مقدار));
		}
	      بازگشت ret;
	    }
	  وگرنه
	    بازگشت c_parser_gimple_postfix_expression (parser);
	}
    پیشفرض:
      بازگشت c_parser_gimple_postfix_expression (parser);
    }
}

/* Decompose ID into base name (ID until ver_offset) and VERSION.  Return
   true if ID matches a SSA name.  */

ایستا منطقی
c_parser_parse_ssa_name_id (درخت id, unsigned *version, unsigned *ver_offset)
{
  ثابت نویسه *token = IDENTIFIER_POINTER (id);
  ثابت نویسه *var_version = strrchr (token, '_');
  اگر (! var_version)
    بازگشت نادرست;

  *ver_offset = var_version - token;
  برای (ثابت نویسه *p = var_version + 1; *p; ++p)
    اگر (! ISDIGIT (*p))
      بازگشت نادرست;
  *version = atoi (var_version + 1);
  بازگشت *version > 0;
}

/* Get at the actual SSA name ID with VERSION starting at VER_OFFSET.
   TYPE is the type if the SSA name is being declared.  */

ایستا درخت
c_parser_parse_ssa_name (gimple_parser &parser,
			 درخت id, درخت type, unsigned version,
			 unsigned ver_offset)
{
  درخت name = NULL_درخت;
  ثابت نویسه *token = IDENTIFIER_POINTER (id);

  اگر (ver_offset == 0)
    {
      /* Anonymous unnamed SSA name.  */
      اگر (version < رقم_ssa_names)
	name = ssa_name (version);
      اگر (! name)
	{
	  اگر (! type)
	    {
	      c_parser_error (parser, "SSA name undeclared");
	      بازگشت error_mark_گره;
	    }
	  name = make_ssa_name_fn (cfun, type, پوچ, version);
	}
    }
  وگرنه
    {
      اگر (version < رقم_ssa_names)
	name = ssa_name (version);
      اگر (! name)
	{
	  /* Separate var name from version.  */
	  نویسه *var_name = XNEWVEC (نویسه, ver_offset + 1);
	  memcpy (var_name, token, ver_offset);
	  var_name[ver_offset] = '\0';
	  /* lookup for parent decl.  */
	  id = get_identifier (var_name);
	  درخت parent = lookup_name (id);
	  XDELETEVEC (var_name);
	  اگر (! parent || parent == error_mark_گره)
	    {
	      c_parser_error (parser, "base variable or SSA name undeclared");
	      بازگشت error_mark_گره;
	    }
	  اگر (!(VAR_P (parent)
		|| درخت_CODE (parent) == PARM_DECL
		|| درخت_CODE (parent) == RESULT_DECL))
	    {
	      error ("invalid base %qE for SSA name", parent);
	      بازگشت error_mark_گره;
	    }
	  name = make_ssa_name_fn (cfun, parent,
				   gimple_build_nop (), version);
	}
    }

  بازگشت name;
}

/* Parse a gimple call to an internal function.

   gimple-call-internal:
     . identifier ( gimple-argument-expression-list[opt] )  */

ایستا ساختار c_عبارت
c_parser_gimple_call_internal (gimple_parser &parser)
{
  ساختار c_عبارت عبارت;
  عبارت.set_error ();

  gcc_assert (c_parser_next_token_is (parser, CPP_DOT));
  c_parser_consume_token (parser);
  location_t loc = c_parser_peek_token (parser)->location;
  اگر (!c_parser_next_token_is (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_kind != C_ID_ID)
    {
      c_parser_error (parser, "expecting internal function name");
      بازگشت عبارت;
    }
  درخت id = c_parser_peek_token (parser)->مقدار;
  internal_fn ifn = lookup_internal_fn (IDENTIFIER_POINTER (id));
  c_parser_consume_token (parser);
  اگر (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    {
      auto_vec<درخت> exprlist;
      اگر (!c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_gimple_عبارت_list (parser, &exprlist);
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      اگر (ifn == IFN_LAST)
	error_at (loc, "unknown internal function %qE", id);
      وگرنه
	{
	  عبارت.مقدار = build_call_عبارت_internal_loc_array
	    (loc, ifn, void_type_گره, exprlist.length (),
	     exprlist.address ());
	  عبارت.original_code = ERROR_MARK;
	  عبارت.original_type = پوچ;
	  عبارت.m_decimal = 0;
	}
    }
  بازگشت عبارت;
}

/* Parse '<' type [',' alignment] '>' and return a type on success
   and NULL_TREE on error.  */

ایستا درخت
c_parser_gimple_typespec (gimple_parser &parser)
{
  ساختار c_type_name *type_name = پوچ;
  درخت alignment = NULL_درخت;
  اگر (c_parser_require (parser, CPP_LESS, "expected %<<%>"))
    {
      type_name = c_parser_type_name (parser);
      /* Optional alignment.  */
      اگر (c_parser_next_token_is (parser, CPP_COMMA))
	{
	  c_parser_consume_token (parser);
	  alignment
	      = c_parser_gimple_postfix_expression (parser).مقدار;
	}
      c_parser_skip_until_found (parser,
				 CPP_GREATER, "expected %<>%>");
    }
  اگر (!type_name)
    بازگشت NULL_درخت;
  درخت tem;
  درخت type = groktypename (type_name, &tem, پوچ);
  اگر (alignment)
    type = build_aligned_type (type, درخت_to_uhwi (alignment));
  بازگشت type;
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

ایستا ساختار c_عبارت
c_parser_gimple_postfix_expression (gimple_parser &parser, درخت ret_type)
{
  location_t loc = c_parser_peek_token (parser)->location;
  source_range tok_range = c_parser_peek_token (parser)->get_range ();
  ساختار c_عبارت عبارت;
  عبارت.set_error ();
  انتخاب (c_parser_peek_token (parser)->type)
    {
    حالت CPP_عدد:
      عبارت.مقدار = c_parser_peek_token (parser)->مقدار;
      set_c_عبارت_source_range (&عبارت, tok_range);
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      بشکن;
    حالت CPP_CHAR:
    حالت CPP_CHAR16:
    حالت CPP_CHAR32:
    حالت CPP_UTF8CHAR:
    حالت CPP_WCHAR:
      عبارت.مقدار = c_parser_peek_token (parser)->مقدار;
      set_c_عبارت_source_range (&عبارت, tok_range);
      c_parser_consume_token (parser);
      بشکن;
    حالت CPP_STRING:
    حالت CPP_STRING16:
    حالت CPP_STRING32:
    حالت CPP_WSTRING:
    حالت CPP_UTF8STRING:
      عبارت = c_parser_string_literal (parser, نادرست, درست);
      بشکن;
    حالت CPP_DOT:
      عبارت = c_parser_gimple_call_internal (parser);
      بشکن;
    حالت CPP_NAME:
      اگر (c_parser_peek_token (parser)->id_kind == C_ID_ID)
	{
	  درخت id = c_parser_peek_token (parser)->مقدار;
	  اگر (strcmp (IDENTIFIER_POINTER (id), "__MEM") == 0)
	    {
	      /* __MEM '<' type-name [ ',' number ] '>'
	               '(' [ '(' type-name ')' ] unary-expression
			   [ '+' number ]
			   [ ',' number ]
			   [ ',' number ':' number ] ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      درخت type = c_parser_gimple_typespec (parser);
	      ساختار c_عبارت ptr, alias_off, step, index, index2;
	      ptr.مقدار = error_mark_گره;
	      alias_off.مقدار = NULL_درخت;
	      step.مقدار = NULL_درخت;
	      index.مقدار = NULL_درخت;
	      index2.مقدار = NULL_درخت;
	      unsigned short clique = 0;
	      unsigned short base = 0;
	      منطقی reverse_order = نادرست;
	      ساختار c_عبارت ro;
	      اگر (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  درخت alias_type = NULL_درخت;
		  /* Optional alias-type cast.  */
		  اگر (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
		    {
		      c_parser_consume_token (parser);
		      ساختار c_type_name *alias_type_name
			= c_parser_type_name (parser);
		      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
						 "expected %<)%>");
		      اگر (alias_type_name)
			{
			  درخت tem;
			  alias_type = groktypename (alias_type_name,
						     &tem, پوچ);
			}
		    }
		  ptr = c_parser_gimple_unary_expression (parser);
		  اگر (ptr.مقدار == error_mark_گره
		      || ! POINTER_TYPE_P (درخت_TYPE (ptr.مقدار)))
		    {
		      اگر (ptr.مقدار != error_mark_گره)
			error_at (ptr.get_start (),
				  "invalid type of %<__MEM%> operand");
		      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
						 "expected %<)%>");
		      بازگشت عبارت;
		    }
		  اگر (! alias_type)
		    alias_type = درخت_TYPE (ptr.مقدار);
		  /* Optional constant offset.  */
		  اگر (c_parser_next_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      alias_off = c_parser_gimple_postfix_expression (parser);
		    }
		  اگر (c_parser_next_token_is (parser, CPP_MULT))
		    {
		      std::swap (index, alias_off);
		      c_parser_consume_token (parser);
		      step = c_parser_gimple_postfix_expression (parser);
		    }
		  وگرنه اگر (c_parser_next_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      index = c_parser_gimple_postfix_expression (parser);
		      اگر (c_parser_next_token_is (parser, CPP_MULT))
			{
			  c_parser_consume_token (parser);
			  step = c_parser_gimple_postfix_expression (parser);
			}
		      وگرنه
			std::swap (index, index2);
		    }
		  وگرنه اگر (alias_off.مقدار
			   && درخت_CODE (alias_off.مقدار) != INTEGER_CST)
		    std::swap (alias_off, index2);
		  اگر (c_parser_next_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      index2 = c_parser_gimple_postfix_expression (parser);
		    }
		  اگر (alias_off.مقدار)
		    {
		      اگر (درخت_CODE (alias_off.مقدار) != INTEGER_CST)
			error_at (alias_off.get_start (),
				  "expected constant offset for %<__MEM%> "
				  "operand");
		      alias_off.مقدار = fold_convert (alias_type,
						      alias_off.مقدار);
		    }
		  وگرنه
		    alias_off.مقدار = build_int_cst (alias_type, 0);
		  اگر (step.مقدار)
		    {
		      اگر (درخت_CODE (step.مقدار) != INTEGER_CST)
			error_at (step.get_start (),
				  "expected constant step for %<__MEM%> "
				  "operand");
		    }
		  اگر (c_parser_next_token_is (parser, CPP_COMMA))
		    {
		      ساختار c_عبارت cl, ba;
		      منطقی has_clb = درست;
		      c_parser_consume_token (parser);
		      cl = c_parser_gimple_postfix_expression (parser);
		      اگر (!c_parser_next_token_is (parser, CPP_COLON))
			{
			  ro = cl;
			  unsigned HOST_WIDE_INT tmp = 0;
			  اگر (!درخت_fits_uhwi_p (ro.مقدار)
			      || (tmp = درخت_to_uhwi (ro.مقدار)) > 1)
			    error_at (ro.get_start (),
				      "invalid reverse order value");
			  reverse_order = tmp;
			  has_clb = نادرست;
			  اگر (c_parser_next_token_is (parser, CPP_COMMA))
			    {
			      c_parser_consume_token (parser);
			      cl = c_parser_gimple_postfix_expression (parser);
		              has_clb = درست;
			    }
			}
		      اگر (has_clb
			  && c_parser_require (parser,
					       CPP_COLON, "expected %<:%>"))
			{
			  ba = c_parser_gimple_postfix_expression (parser);
			  اگر (!درخت_fits_uhwi_p (cl.مقدار)
			      || !درخت_fits_uhwi_p (ba.مقدار)
			      || compare_درخت_int (cl.مقدار,
						   (clique = درخت_to_uhwi
								(cl.مقدار)))
			      || compare_درخت_int (ba.مقدار,
						   (base = درخت_to_uhwi
								 (ba.مقدار))))
			    error_at (cl.get_start (),
				      "invalid clique/base pair");
			}
		    }
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      اگر (! type || c_parser_error (parser))
		{
		  c_parser_set_error (parser, نادرست);
		  بازگشت عبارت;
		}
	      اگر (index.مقدار || step.مقدار || index2.مقدار)
		عبارت.مقدار = build5_loc (loc, TARGET_MEM_REF,
					 type, ptr.مقدار, alias_off.مقدار,
					 index.مقدار, step.مقدار, index2.مقدار);
	      وگرنه
		عبارت.مقدار = build2_loc (loc, MEM_REF,
					 type, ptr.مقدار, alias_off.مقدار);
	      اگر (clique != 0)
		{
		  cfun->last_clique = MAX (cfun->last_clique, clique);
		  MR_DEPENDENCE_CLIQUE (عبارت.مقدار) = clique;
		  MR_DEPENDENCE_BASE (عبارت.مقدار) = base;
		}
	      اگر (reverse_order)
		{
		  اگر (درخت_CODE (عبارت.مقدار) == MEM_REF)
		    REF_REVERSE_STORAGE_ORDER (عبارت.مقدار) = reverse_order;
		  وگرنه
		    error_at (ro.get_start (),
			      "target mem ref cannot have reverse order");
		}
	      بشکن;
	    }
	  وگرنه اگر (strcmp (IDENTIFIER_POINTER (id), "__VIEW_CONVERT") == 0)
	    {
	      /* __VIEW_CONVERT '<' type-name [ ',' number ] '>'
	                        '(' postfix-expression ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      درخت type = c_parser_gimple_typespec (parser);
	      اگر (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_عبارت op = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  اگر (type && op.مقدار != error_mark_گره)
		    عبارت.مقدار = build1_loc (loc, VIEW_CONVERT_عبارت,
					     type, op.مقدار);
		}
	      بشکن;
	    }
	  وگرنه اگر (strcmp (IDENTIFIER_POINTER (id), "__BIT_FIELD_REF") == 0)
	    {
	      /* __BIT_FIELD_REF '<' type-name [ ',' number ] '>'
	                        '(' postfix-expression, integer, integer ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      درخت type = c_parser_gimple_typespec (parser);
	      اگر (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_عبارت op0 = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_عبارت op1 = c_parser_gimple_postfix_expression (parser);
		  اگر (درخت_CODE (op1.مقدار) != INTEGER_CST
		      || !int_fits_type_p (op1.مقدار, bitsizetype))
		    c_parser_error (parser, "expected constant size");
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_عبارت op2 = c_parser_gimple_postfix_expression (parser);
		  اگر (درخت_CODE (op2.مقدار) != INTEGER_CST
		      || !int_fits_type_p (op2.مقدار, bitsizetype))
		    c_parser_error (parser, "expected constant offset");
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  اگر (type
		      && op0.مقدار != error_mark_گره
		      && درخت_CODE (op1.مقدار) == INTEGER_CST
		      && درخت_CODE (op2.مقدار) == INTEGER_CST)
		    عبارت.مقدار = build3_loc (loc, BIT_FIELD_REF, type,
					     op0.مقدار,
					     fold_convert (bitsizetype,
							   op1.مقدار),
					     fold_convert (bitsizetype,
							   op2.مقدار));
		}
	      بشکن;
	    }
	  وگرنه اگر (strcmp (IDENTIFIER_POINTER (id), "__CLOBBER") == 0)
	    {
	      /* __CLOBBER [ '(' bob | eob | bos | eos ')' ]  */
	      clobber_kind kind = CLOBBER_UNDEF;
	      c_parser_consume_token (parser);
	      اگر (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
		{
		  c_parser_consume_token (parser);
		  auto tok = c_parser_peek_token (parser);
		  اگر (c_parser_require (parser, CPP_NAME,
					"expected clobber kind"))
		    {
		      ثابت نویسه *kind_str = IDENTIFIER_POINTER (tok->مقدار);
		      اگر (strcmp (kind_str, "bos") == 0)
			kind = CLOBBER_STORAGE_BEGIN;
		      وگرنه اگر (strcmp (kind_str, "bob") == 0)
			kind = CLOBBER_OBJECT_BEGIN;
		      وگرنه اگر (strcmp (kind_str, "eob") == 0)
			kind = CLOBBER_OBJECT_END;
		      وگرنه اگر (strcmp (kind_str, "eos") == 0)
			kind = CLOBBER_STORAGE_END;
		      وگرنه
			c_parser_error (parser, "expected one of %<bos%>, "
					"%<eos%>, %<bob>, %<eob%>");
		    }
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      /* We infer the (redundant) type from the LHS.  */
	      عبارت.مقدار = build_clobber (ret_type, kind);
	      بشکن;
	    }
	  وگرنه اگر (strcmp (IDENTIFIER_POINTER (id), "_Literal") == 0)
	    {
	      /* _Literal '(' type-name ')' ( [ '-' ] constant | constructor ) */
	      c_parser_consume_token (parser);
	      درخت type = NULL_درخت;
	      اگر (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  ساختار c_type_name *type_name = c_parser_type_name (parser);
		  درخت tem;
		  اگر (type_name)
		    type = groktypename (type_name, &tem, پوچ);
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      اگر (! type)
		{
		  c_parser_error (parser, "invalid _Literal");
		  بازگشت عبارت;
		}
	      اگر (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
		{
		  c_parser_consume_token (parser);
		  اگر (!AGGREGATE_TYPE_P (type)
		      && !VECTOR_TYPE_P (type))
		    {
		      c_parser_error (parser, "invalid type for _Literal with "
				      "constructor");
		      c_parser_skip_until_found (parser, CPP_CLOSE_BRACE,
						 "expected %<}%>");
		      بازگشت عبارت;
		    }
		  vec<constructor_elt, va_gc> *v = پوچ;
		  منطقی constant_p = درست;
		  اگر (VECTOR_TYPE_P (type)
		      && !c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
		    {
		      vec_alloc (v, TYPE_VECTOR_SUBPARTS (type).to_constant ());
		      انجامبده
			{
			  درخت val
			    = c_parser_gimple_postfix_expression (parser).مقدار;
			  اگر (! val
			      || val == error_mark_گره
			      || (! CONSTANT_CLASS_P (val)
				  && ! SSA_VAR_P (val)))
			    {
			      c_parser_error (parser, "invalid _Literal");
			      بازگشت عبارت;
			    }
			  CONSTRUCTOR_APPEND_ELT (v, NULL_درخت, val);
			  اگر (! CONSTANT_CLASS_P (val))
			    constant_p = نادرست;
			  اگر (c_parser_next_token_is (parser, CPP_COMMA))
			    c_parser_consume_token (parser);
			  وگرنه
			    بشکن;
			}
		      وقتی (1);
		    }
		  اگر (c_parser_require (parser, CPP_CLOSE_BRACE,
					"expected %<}%>"))
		    {
		      اگر (v && constant_p)
			عبارت.مقدار = build_vector_from_ctor (type, v);
		      وگرنه
			عبارت.مقدار = build_constructor (type, v);
		    }
		  وگرنه
		    {
		      c_parser_skip_until_found (parser, CPP_CLOSE_BRACE,
						 "expected %<}%>");
		      بازگشت عبارت;
		    }
		}
	      وگرنه
		{
		  منطقی neg_p, addr_p;
		  اگر ((neg_p = c_parser_next_token_is (parser, CPP_MINUS)))
		    c_parser_consume_token (parser);
		  اگر ((addr_p = c_parser_next_token_is (parser, CPP_AND)))
		    c_parser_consume_token (parser);
		  درخت val = c_parser_gimple_postfix_expression (parser).مقدار;
		  اگر (! val
		      || val == error_mark_گره
		      || (!CONSTANT_CLASS_P (val) && !addr_p))
		    {
		      c_parser_error (parser, "invalid _Literal");
		      بازگشت عبارت;
		    }
		  اگر (addr_p)
		    {
		      val = build1 (ADDR_عبارت, type, val);
		      اگر (!is_gimple_invariant_address (val))
			{
			  c_parser_error (parser, "invalid _Literal");
			  بازگشت عبارت;
			}
		    }
		  اگر (neg_p)
		    {
		      val = const_unop (NEGATE_عبارت, درخت_TYPE (val), val);
		      اگر (! val)
			{
			  c_parser_error (parser, "invalid _Literal");
			  بازگشت عبارت;
			}
		    }
		  عبارت.مقدار = fold_convert (type, val);
		}
	      بازگشت عبارت;
	    }

	  /* SSA name.  */
	  unsigned version, ver_offset;
	  اگر (! lookup_name (id)
	      && c_parser_parse_ssa_name_id (id, &version, &ver_offset))
	    {
	      c_parser_consume_token (parser);
	      عبارت.مقدار = c_parser_parse_ssa_name (parser, id, NULL_درخت,
						    version, ver_offset);
	      اگر (عبارت.مقدار == error_mark_گره)
		بازگشت عبارت;
	      set_c_عبارت_source_range (&عبارت, tok_range);
	      /* For default definition SSA names.  */
	      اگر (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
		  && c_parser_peek_2nd_token (parser)->type == CPP_NAME
		  && strcmp ("D",
			     IDENTIFIER_POINTER
			       (c_parser_peek_2nd_token (parser)->مقدار)) == 0
		  && c_parser_peek_nth_token (parser, 3)->type == CPP_CLOSE_PAREN)
		{
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		  اگر (! SSA_NAME_IS_DEFAULT_DEF (عبارت.مقدار))
		    {
		      اگر (!SSA_NAME_VAR (عبارت.مقدار))
			{
			  error_at (loc, "anonymous SSA name cannot have"
				    " default definition");
			  عبارت.مقدار = error_mark_گره;
			  بازگشت عبارت;
			}
		      set_ssa_default_def (cfun, SSA_NAME_VAR (عبارت.مقدار),
					   عبارت.مقدار);
		      SSA_NAME_DEF_STMT (عبارت.مقدار) = gimple_build_nop ();
		    }
		}
	    }
	  وگرنه
	    {
	      c_parser_consume_token (parser);
	      عبارت.مقدار
		= build_external_ref (loc, id,
				      (c_parser_peek_token (parser)->type
				       == CPP_OPEN_PAREN), &عبارت.original_type);
	      set_c_عبارت_source_range (&عبارت, tok_range);
	    }
	  بشکن;
	}
      /* Fallthru.  */
    پیشفرض:
      c_parser_error (parser, "expected expression");
      عبارت.set_error ();
      بشکن;
    }
  اگر (عبارت.مقدار == error_mark_گره)
    بازگشت عبارت;
  بازگشت c_parser_gimple_postfix_expression_after_primary
    (parser, عبارت_LOC_OR_LOC (عبارت.مقدار, loc), عبارت);
}

/* Parse a gimple postfix expression after the initial primary or compound
   literal.  */

ایستا ساختار c_عبارت
c_parser_gimple_postfix_expression_after_primary (gimple_parser &parser,
						  location_t عبارت_loc,
						  ساختار c_عبارت عبارت)
{
  location_t start;
  location_t finish;
  درخت ident;
  location_t comp_loc;

  وقتی (درست)
    {
      location_t op_loc = c_parser_peek_token (parser)->location;
      انتخاب (c_parser_peek_token (parser)->type)
	{
	حالت CPP_OPEN_SQUARE:
	  {
	    c_parser_consume_token (parser);
	    درخت idx = c_parser_gimple_unary_expression (parser).مقدار;

	    اگر (! c_parser_require (parser, CPP_CLOSE_SQUARE, "expected %<]%>"))
	      {
		c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE, پوچ);
		بشکن;
	      }

	    start = عبارت.get_start ();
	    finish = c_parser_tokens_buf (parser, 0)->location;
	    عبارت.مقدار = build_array_ref (op_loc, عبارت.مقدار, idx);
	    set_c_عبارت_source_range (&عبارت, start, finish);
	    عبارت.m_decimal = 0;

	    عبارت.original_code = ERROR_MARK;
	    عبارت.original_type = پوچ;
	    بشکن;
	  }
	حالت CPP_OPEN_PAREN:
	  {
	    /* Function call.  */
	    c_parser_consume_token (parser);
	    auto_vec<درخت> exprlist;
	    اگر (! c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	      c_parser_gimple_عبارت_list (parser, &exprlist);
	    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    اگر (!FUNC_OR_METHOD_TYPE_P (درخت_TYPE (عبارت.مقدار)))
	      {
		c_parser_error (parser, "invalid call to non-function");
		عبارت.set_error ();
		بشکن;
	      }
	    عبارت.مقدار = build_call_array_loc
		(عبارت_loc, درخت_TYPE (درخت_TYPE (عبارت.مقدار)),
		 عبارت.مقدار, exprlist.length (), exprlist.address ());
	    عبارت.m_decimal = 0;
	    عبارت.original_code = ERROR_MARK;
	    عبارت.original_type = پوچ;
	    بشکن;
	  }
	حالت CPP_DOT:
	  {
	    /* Structure element reference.  */
	    c_parser_consume_token (parser);
	    اگر (c_parser_next_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		ident = comp_tok->مقدار;
		comp_loc = comp_tok->location;
	      }
	    وگرنه
	      {
		c_parser_error (parser, "expected identifier");
		عبارت.set_error ();
		عبارت.original_code = ERROR_MARK;
		عبارت.original_type = پوچ;
		بازگشت عبارت;
	      }
	    start = عبارت.get_start ();
	    finish = c_parser_peek_token (parser)->get_finish ();
	    c_parser_consume_token (parser);
	    عبارت.مقدار = build_component_ref (op_loc, عبارت.مقدار, ident,
					      comp_loc, UNKNOWN_LOCATION);
	    set_c_عبارت_source_range (&عبارت, start, finish);
	    عبارت.m_decimal = 0;
	    عبارت.original_code = ERROR_MARK;
	    اگر (درخت_CODE (عبارت.مقدار) != COMPONENT_REF)
	      عبارت.original_type = پوچ;
	    وگرنه
	      {
		/* Remember the original type of a bitfield.  */
		درخت field = درخت_OPERAND (عبارت.مقدار, 1);
		اگر (درخت_CODE (field) != FIELD_DECL)
		  عبارت.original_type = پوچ;
		وگرنه
		  عبارت.original_type = DECL_BIT_FIELD_TYPE (field);
	      }
	    بشکن;
	  }
	حالت CPP_DEREF:
	  {
	    /* Structure element reference.  */
	    اگر (!POINTER_TYPE_P (درخت_TYPE (عبارت.مقدار)))
	      {
		c_parser_error (parser, "dereference of non-pointer");
		عبارت.set_error ();
		عبارت.original_code = ERROR_MARK;
		عبارت.original_type = پوچ;
		بازگشت عبارت;
	      }
	    c_parser_consume_token (parser);
	    اگر (c_parser_next_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		ident = comp_tok->مقدار;
		comp_loc = comp_tok->location;
	      }
	    وگرنه
	      {
		c_parser_error (parser, "expected identifier");
		عبارت.set_error ();
		عبارت.original_code = ERROR_MARK;
		عبارت.original_type = پوچ;
		بازگشت عبارت;
	      }
	    start = عبارت.get_start ();
	    finish = c_parser_peek_token (parser)->get_finish ();
	    c_parser_consume_token (parser);
	    عبارت.مقدار = build_component_ref (op_loc,
					      build_simple_mem_ref_loc
					        (op_loc, عبارت.مقدار),
					      ident, comp_loc,
					      عبارت.get_location ());
	    set_c_عبارت_source_range (&عبارت, start, finish);
	    عبارت.m_decimal = 0;
	    عبارت.original_code = ERROR_MARK;
	    اگر (درخت_CODE (عبارت.مقدار) != COMPONENT_REF)
	      عبارت.original_type = پوچ;
	    وگرنه
	      {
		/* Remember the original type of a bitfield.  */
		درخت field = درخت_OPERAND (عبارت.مقدار, 1);
		اگر (درخت_CODE (field) != FIELD_DECL)
		  عبارت.original_type = پوچ;
		وگرنه
		  عبارت.original_type = DECL_BIT_FIELD_TYPE (field);
	      }
	    بشکن;
	  }
	پیشفرض:
	  بازگشت عبارت;
	}
    }
}

/* Parse expression list.

   gimple-expr-list:
     gimple-unary-expression
     gimple-expr-list , gimple-unary-expression

 */

ایستا تهی
c_parser_gimple_عبارت_list (gimple_parser &parser, vec<درخت> *ret)
{
  ساختار c_عبارت عبارت;

  عبارت = c_parser_gimple_unary_expression (parser);
  ret->safe_افزودن (عبارت.مقدار);
  وقتی (c_parser_next_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      عبارت = c_parser_gimple_unary_expression (parser);
      ret->safe_افزودن (عبارت.مقدار);
    }
}

/* Parse gimple label.

   gimple-label:
     identifier :
     case constant-expression :
     default :

*/

ایستا تهی
c_parser_gimple_label (gimple_parser &parser, gimple_seq *seq)
{
  درخت name = c_parser_peek_token (parser)->مقدار;
  location_t loc1 = c_parser_peek_token (parser)->location;
  gcc_assert (c_parser_next_token_is (parser, CPP_NAME));
  c_parser_consume_token (parser);
  gcc_assert (c_parser_next_token_is (parser, CPP_COLON));
  c_parser_consume_token (parser);
  درخت label = define_label (loc1, name);
  اگر (label)
    gimple_seq_add_stmt_without_update (seq, gimple_build_label (label));
  بازگشت;
}

/* Parse gimple/RTL pass list.

   gimple-or-rtl-pass-list:
     startwith("pass-name")[,{cfg,ssa}]
 */

تهی
c_parser_gimple_or_rtl_pass_list (c_parser *parser, c_declspecs *specs)
{
  نویسه *pass = پوچ;

  /* Accept __GIMPLE/__RTL.  */
  اگر (c_parser_next_token_is_not (parser, CPP_OPEN_PAREN))
    بازگشت;
  c_parser_consume_token (parser);

  specs->entry_bb_شمار = profile_شمار::uninitialized ();
  وقتی (c_parser_next_token_is (parser, CPP_NAME))
    {
      profile_quality quality;
      ثابت نویسه *op = IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار);
      c_parser_consume_token (parser);
      اگر (! strcmp (op, "startwith"))
	{
	  اگر (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    بازگشت;
	  اگر (c_parser_next_token_is_not (parser, CPP_STRING))
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"expected pass name");
	      بازگشت;
	    }
	  pass = xstrdup (درخت_STRING_POINTER
			  (c_parser_string_literal (parser, نادرست,
						    نادرست).مقدار));
	  اگر (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<(%>"))
	    بازگشت;
	}
      وگرنه اگر (parse_profile_quality (op, &quality))
	{
	  درخت q;
	  اگر (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    بازگشت;

	  اگر (!c_parser_next_token_is (parser, CPP_عدد)
	      || (درخت_CODE (q = c_parser_peek_token (parser)->مقدار)
		  != INTEGER_CST))
	    {
	      c_parser_error (parser, "expected count value");
	      بازگشت;
	    }

	  specs->entry_bb_شمار
	    = profile_شمار::from_gcov_type (درخت_INT_CST_کم (q), quality);
	  c_parser_consume_token (parser);
	  اگر (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    بازگشت;
	}
      وگرنه اگر (specs->declspec_il != cdil_gimple)
	/* Allow only one IL specifier and none on RTL.  */
	;
      وگرنه اگر (! strcmp (op, "cfg"))
	specs->declspec_il = cdil_gimple_cfg;
      وگرنه اگر (! strcmp (op, "ssa"))
	specs->declspec_il = cdil_gimple_ssa;
      وگرنه
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "invalid operation");
	  بازگشت;
	}
     اگر (c_parser_next_token_is (parser, CPP_COMMA))
       c_parser_consume_token (parser);
    }

  اگر (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    بازگشت;

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

ایستا تهی
c_parser_gimple_declaration (gimple_parser &parser)
{
  ساختار c_declarator *declarator;
  ساختار c_declspecs *specs = build_null_declspecs ();
  c_parser_declspecs (parser, specs, درست, درست, درست,
		      درست, درست, درست, درست, cla_nonabstract_decl);
  finish_declspecs (specs);

  /* Provide better error recovery.  Note that a type name here is usually
     better diagnosed as a redeclaration.  */
  اگر (c_parser_next_token_starts_declspecs (parser)
      && ! c_parser_next_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<;%>");
      c_parser_set_error (parser, نادرست);
      بازگشت;
    }

  منطقی dummy = نادرست;
  declarator = c_parser_declarator (parser,
				    specs->typespec_kind != ctsk_none,
				    C_DTR_NORMAL, &dummy);

  اگر (!c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_error (parser, "expected %<;%>");
      بازگشت;
    }
  اگر (declarator)
    {
      /* Handle SSA name decls specially, they do not go into the identifier
         table but we simply build the SSA name for later lookup.  */
      unsigned version, ver_offset;
      /* Handle SSA pointer declarations in a very simplistic ways, we
	 probably would like to call grokdeclarator in a special mode to
	 just build the type of the decl - start_decl already pushes
	 the identifier to the bindings for lookup, something we do not
	 want.  */
      ساختار c_declarator *id_declarator = declarator;
      وقتی (id_declarator->kind == cdk_pointer)
	id_declarator = id_declarator->declarator;
      اگر (id_declarator->kind == cdk_id
	  && (declarator->kind == cdk_pointer
	      || is_gimple_reg_type (specs->type))
	  && c_parser_parse_ssa_name_id (id_declarator->u.id.id,
					 &version, &ver_offset)
	  /* The following restricts it to unnamed anonymous SSA names
	     which fails parsing of named ones in dumps (we could
	     decide to not dump their name for -gimple).  */
	  && ver_offset == 0)
	{
	  ساختار c_declarator *p = declarator;
	  درخت type = specs->type;
	  وقتی (p->kind == cdk_pointer)
	    {
	      type = build_pointer_type (type);
	      p = p->declarator;
	    }
	  c_parser_parse_ssa_name (parser, id_declarator->u.id.id, type,
				   version, ver_offset);
	}
      وگرنه
	{
	  درخت postfix_attrs = NULL_درخت;
	  درخت all_prefix_attrs = specs->attrs;
	  specs->attrs = پوچ;
	  درخت decl = start_decl (declarator, specs, نادرست,
				  chainon (postfix_attrs, all_prefix_attrs));
	  اگر (decl)
	    finish_decl (decl, UNKNOWN_LOCATION, NULL_درخت, NULL_درخت,
			 NULL_درخت);
	}
    }
}

/* Parse gimple goto statement.  */

ایستا تهی
c_parser_gimple_goto_stmt (gimple_parser &parser,
			   location_t loc, درخت label, gimple_seq *seq)
{
  اگر (cfun->curr_properties & PROP_cfg)
    {
      صحیح dest_index;
      profile_probability prob;
      اگر (c_parser_gimple_parse_bb_spec_edge_probability (label, parser,
							  &dest_index, &prob))
	{
	  parser.افزودن_edge (parser.current_bb->index, dest_index,
			    EDGE_FALLTHRU, prob);
	  بازگشت;
	}
    }
  درخت decl = lookup_label_for_goto (loc, label);
  gimple_seq_add_stmt_without_update (seq, gimple_build_goto (decl));
}

/* Parse a parenthesized condition.
   gimple-condition:
     ( gimple-binary-expression )    */

ایستا درخت
c_parser_gimple_paren_condition (gimple_parser &parser)
{
  اگر (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    بازگشت error_mark_گره;
  درخت cond
    = c_parser_gimple_دودویی_expression (parser, boolean_type_گره).مقدار;
  اگر (cond != error_mark_گره
      && ! COMPARISON_CLASS_P (cond)
      && ! CONSTANT_CLASS_P (cond)
      && ! SSA_VAR_P (cond))
    {
      c_parser_error (parser, "comparison required");
      cond = error_mark_گره;
    }
  اگر (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    بازگشت error_mark_گره;
  بازگشت cond;
}

/* Parse gimple try statement.

   try-statement:
     try { ... } finally { ... }
     try { ... } finally { ... } else { ... }

   This could support try/catch as well, but it's not implemented yet.
 */

ایستا تهی
c_parser_gimple_try_stmt (gimple_parser &parser, gimple_seq *seq)
{
  gimple_seq tryseq = پوچ;
  c_parser_consume_token (parser);
  c_parser_gimple_compound_statement (parser, &tryseq);

  اگر ((c_parser_next_token_is (parser, CPP_KEYWORD)
       && c_parser_peek_token (parser)->keyword == RID_AT_FINALLY)
      || (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_token (parser)->id_kind == C_ID_ID
	  && strcmp (IDENTIFIER_POINTER (c_parser_peek_token (parser)->مقدار),
		     "finally") == 0))
    {
      gimple_seq finseq = پوچ;
      c_parser_consume_token (parser);
      c_parser_gimple_compound_statement (parser, &finseq);

      اگر (c_parser_next_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_ELSE)
	{
	  gimple_seq elsseq = پوچ;
	  c_parser_consume_token (parser);
	  c_parser_gimple_compound_statement (parser, &elsseq);

	  geh_else *stmt = gimple_build_eh_else (finseq, elsseq);
	  finseq = پوچ;
	  gimple_seq_add_stmt_without_update (&finseq, stmt);
	}

      gtry *stmt = gimple_build_try (tryseq, finseq, GIMPLE_TRY_FINALLY);
      gimple_seq_add_stmt_without_update (seq, stmt);
    }
  وگرنه اگر (c_parser_next_token_is (parser, CPP_KEYWORD)
      && c_parser_peek_token (parser)->keyword == RID_AT_CATCH)
    c_parser_error (parser, "%<catch%> is not supported");
  وگرنه
    c_parser_error (parser, "expected %<finally%> or %<catch%>");
}

/* Parse gimple if-else statement.

   if-statement:
     if ( gimple-binary-expression ) gimple-goto-statement
     if ( gimple-binary-expression ) gimple-goto-statement \
					else gimple-goto-statement
 */

ایستا تهی
c_parser_gimple_if_stmt (gimple_parser &parser, gimple_seq *seq)
{
  درخت t_label = NULL_درخت, f_label = NULL_درخت, label;
  location_t loc;
  c_parser_consume_token (parser);
  درخت cond = c_parser_gimple_paren_condition (parser);

  اگر (c_parser_next_token_is_keyword (parser, RID_GOTO))
    {
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      اگر (! c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected label");
	  بازگشت;
	}
      label = c_parser_peek_token (parser)->مقدار;
      c_parser_consume_token (parser);
      صحیح dest_index;
      profile_probability prob;
      اگر ((cfun->curr_properties & PROP_cfg)
	  && c_parser_gimple_parse_bb_spec_edge_probability (label, parser,
							     &dest_index, &prob))
	parser.افزودن_edge (parser.current_bb->index, dest_index,
			  EDGE_TRUE_مقدار, prob);
      وگرنه
	t_label = lookup_label_for_goto (loc, label);
      اگر (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	بازگشت;
    }
  وگرنه
    {
      c_parser_error (parser, "expected goto expression");
      بازگشت;
    }

  اگر (c_parser_next_token_is_keyword (parser, RID_ELSE))
    c_parser_consume_token (parser);
  وگرنه
    {
      c_parser_error (parser, "expected else statement");
      بازگشت;
    }

  اگر (c_parser_next_token_is_keyword (parser, RID_GOTO))
    {
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      اگر (! c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected label");
	  بازگشت;
	}
      label = c_parser_peek_token (parser)->مقدار;
      c_parser_consume_token (parser);
      صحیح dest_index;
      profile_probability prob;
      اگر ((cfun->curr_properties & PROP_cfg)
	  && c_parser_gimple_parse_bb_spec_edge_probability (label, parser,
							     &dest_index, &prob))
	parser.افزودن_edge (parser.current_bb->index, dest_index,
			  EDGE_FALSE_مقدار, prob);
      وگرنه
	f_label = lookup_label_for_goto (loc, label);
      اگر (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	بازگشت;
    }
  وگرنه
    {
      c_parser_error (parser, "expected goto expression");
      بازگشت;
    }

  اگر (cond != error_mark_گره)
    gimple_seq_add_stmt_without_update (seq, gimple_build_cond_from_درخت (cond, t_label,
							   f_label));
}

/* Parse gimple switch-statement.

   gimple-switch-statement:
     switch (gimple-postfix-expression) gimple-case-statement

   gimple-case-statement:
     gimple-case-statement
     gimple-label-statement : gimple-goto-statement
*/

ایستا تهی
c_parser_gimple_switch_stmt (gimple_parser &parser, gimple_seq *seq)
{
  c_عبارت cond_عبارت;
  درخت case_label, label;
  auto_vec<درخت> labels;
  درخت default_label = NULL_درخت;
  c_parser_consume_token (parser);

  اگر (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    بازگشت;
  cond_عبارت = c_parser_gimple_postfix_expression (parser);
  اگر (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    بازگشت;

  اگر (! c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    بازگشت;

  وقتی (c_parser_next_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      اگر (c_parser_next_token_is (parser, CPP_EOF))
	{
	  c_parser_error (parser, "expected statement");
	  بازگشت;
	}

      انتخاب (c_parser_peek_token (parser)->keyword)
	{
	حالت RID_CASE:
	  {
	    c_عبارت exp1;
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);

	    اگر (c_parser_next_token_is (parser, CPP_NAME)
		|| c_parser_peek_token (parser)->type == CPP_عدد)
	      exp1 = c_parser_gimple_postfix_expression (parser);
	    وگرنه
	      {
		c_parser_error (parser, "expected expression");
		بازگشت;
	      }

	    اگر (c_parser_next_token_is (parser, CPP_COLON))
	      {
		c_parser_consume_token (parser);
		اگر (c_parser_next_token_is (parser, CPP_NAME))
		  {
		    label = c_parser_peek_token (parser)->مقدار;
		    c_parser_consume_token (parser);
		    درخت decl = lookup_label_for_goto (loc, label);
		    case_label = build_case_label (exp1.مقدار, NULL_درخت,
						   decl);
		    labels.safe_افزودن (case_label);
		    اگر (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      بازگشت;
		  }
		وگرنه اگر (! c_parser_require (parser, CPP_NAME,
					     "expected label"))
		  بازگشت;
	      }
	    وگرنه اگر (! c_parser_require (parser, CPP_SEMICOLON,
					 "expected %<:%>"))
	      بازگشت;
	    بشکن;
	  }
	حالت RID_DEFAULT:
	  {
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);
	    اگر (c_parser_next_token_is (parser, CPP_COLON))
	      {
		c_parser_consume_token (parser);
		اگر (c_parser_next_token_is (parser, CPP_NAME))
		  {
		    label = c_parser_peek_token (parser)->مقدار;
		    c_parser_consume_token (parser);
		    درخت decl = lookup_label_for_goto (loc, label);
		    default_label = build_case_label (NULL_درخت, NULL_درخت,
						      decl);
		    اگر (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      بازگشت;
		  }
		وگرنه اگر (! c_parser_require (parser, CPP_NAME,
					     "expected label"))
		  بازگشت;
	      }
	    وگرنه اگر (! c_parser_require (parser, CPP_SEMICOLON,
					 "expected %<:%>"))
	      بازگشت;
	    بشکن;
	  }
	پیشفرض:
	  c_parser_error (parser, "expected case label");
	  بازگشت;
	}

    }
  اگر (! c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>"))
    بازگشت;

  اگر (cond_عبارت.مقدار != error_mark_گره)
    {
      gswitch *s = gimple_build_switch (cond_عبارت.مقدار, default_label, labels);
      gimple_seq_add_stmt_without_update (seq, s);
    }
}

/* Parse gimple return statement.  */

ایستا تهی
c_parser_gimple_return_stmt (gimple_parser &parser, gimple_seq *seq)
{
  location_t loc = c_parser_peek_token (parser)->location;
  gimple *ret = پوچ;
  c_parser_consume_token (parser);
  اگر (c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      c_finish_gimple_return (loc, NULL_درخت);
      ret = gimple_build_return (پوچ);
      gimple_seq_add_stmt_without_update (seq, ret);
    }
  وگرنه
    {
      location_t xloc = c_parser_peek_token (parser)->location;
      c_عبارت عبارت = c_parser_gimple_unary_expression (parser);
      اگر (عبارت.مقدار != error_mark_گره)
	{
	  c_finish_gimple_return (xloc, عبارت.مقدار);
	  ret = gimple_build_return (عبارت.مقدار);
	  gimple_seq_add_stmt_without_update (seq, ret);
	}
    }
}

/* Support function for c_parser_gimple_return_stmt.  */

ایستا تهی
c_finish_gimple_return (location_t loc, درخت retval)
{
  درخت valtype = درخت_TYPE (درخت_TYPE (current_function_decl));

  /* Use the expansion point to handle cases such as returning NULL
     in a function returning void.  */
  location_t xloc = expansion_point_location_if_in_system_header (loc);

  اگر (درخت_THIS_VOLATILE (current_function_decl))
    warning_at (xloc, 0,
		"function declared %<noreturn%> has a %<return%> statement");

  اگر (! retval)
    current_function_returns_null = 1;
  وگرنه اگر (valtype == 0 || VOID_TYPE_P (valtype))
    {
      current_function_returns_null = 1;
      اگر (درخت_CODE (درخت_TYPE (retval)) != VOID_TYPE)
	{
	  error_at
	    (xloc, "%<return%> with a value, in function returning void");
	  inform (DECL_SOURCE_LOCATION (current_function_decl),
		  "declared here");
	}
    }
  وگرنه اگر (درخت_CODE (valtype) != درخت_CODE (درخت_TYPE (retval)))
    {
      error_at
	(xloc, "invalid conversion in return statement");
      inform (DECL_SOURCE_LOCATION (current_function_decl),
	      "declared here");
    }
  بازگشت;
}
