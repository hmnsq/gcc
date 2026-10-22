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

#ضمن "config.h"
#ضمن "system.h"
#ضمن "coretypes.h"
#ضمن "target.h"
#ضمن "function.h"
#ضمن "c-tree.h"
#ضمن "timevar.h"
#ضمن "stringpool.h"
#ضمن "cgraph.h"
#ضمن "attribs.h"
#ضمن "stor-layout.h"
#ضمن "varasm.h"
#ضمن "trans-mem.h"
#ضمن "c-family/c-pragma.h"
#ضمن "c-lang.h"
#ضمن "c-family/c-objc.h"
#ضمن "plugin.h"
#ضمن "builtins.h"
#ضمن "gomp-constants.h"
#ضمن "c-family/c-indentation.h"
#ضمن "gimple-expr.h"
#ضمن "context.h"
#ضمن "gcc-rich-location.h"
#ضمن "c-parser.h"
#ضمن "tree-vrp.h"
#ضمن "tree-pass.h"
#ضمن "tree-pretty-print.h"
#ضمن "tree.h"
#ضمن "basic-block.h"
#ضمن "gimple.h"
#ضمن "gimple-pretty-print.h"
#ضمن "tree-ssa.h"
#ضمن "pass_manager.h"
#ضمن "tree-ssanames.h"
#ضمن "gimple-ssa.h"
#ضمن "tree-dfa.h"
#ضمن "internal-fn.h"
#ضمن "cfg.h"
#ضمن "cfghooks.h"
#ضمن "bitmap.h"
#ضمن "cfganal.h"
#ضمن "tree-cfg.h"
#ضمن "gimple-iterator.h"
#ضمن "cfgloop.h"
#ضمن "tree-phinodes.h"
#ضمن "tree-into-ssa.h"


/* GIMPLE parser state.  */

מחלקה gimple_parser
{
عام:
  gimple_parser (c_parser *p) : parser (p), edges(), current_bb(عدم) {}
  /* c_parser is not visible here, use composition and fake inheritance
     via a conversion operator.  */
  operator c_parser *() { החזר parser; }
  c_parser *parser;

  /* CFG build state.  */
  מחלקה gimple_parser_edge
  {
  عام:
    صحيح src;
    صحيح dest;
    صحيح flags;
    profile_probability probability;
  };
  auto_vec<gimple_parser_edge> edges;
  basic_block current_bb;

  فراغ push_edge (صحيح, صحيح, صحيح, profile_probability);
};

فراغ
gimple_parser::push_edge (صحيح src, صحيح dest, صحيح flags,
			  profile_probability prob)
{
  gimple_parser_edge e;
  e.src = src;
  e.dest = dest;
  e.flags = flags;
  e.probability = prob;
  edges.safe_push (e);
}


/* Gimple parsing functions.  */
ساكن منطقي c_parser_gimple_compound_statement (gimple_parser &, gimple_seq *);
ساكن فراغ c_parser_gimple_label (gimple_parser &, gimple_seq *);
ساكن فراغ c_parser_gimple_statement (gimple_parser &, gimple_seq *);
ساكن بنية c_expr c_parser_gimple_binary_expression (gimple_parser &, tree);
ساكن بنية c_expr c_parser_gimple_unary_expression (gimple_parser &);
ساكن بنية c_expr c_parser_gimple_postfix_expression
			(gimple_parser &, tree = error_mark_node);
ساكن بنية c_expr c_parser_gimple_postfix_expression_after_primary
			(gimple_parser &, location_t, بنية c_expr);
ساكن فراغ c_parser_gimple_declaration (gimple_parser &);
ساكن فراغ c_parser_gimple_goto_stmt (gimple_parser &, location_t,
				       tree, gimple_seq *);
ساكن فراغ c_parser_gimple_try_stmt (gimple_parser &, gimple_seq *);
ساكن فراغ c_parser_gimple_if_stmt (gimple_parser &, gimple_seq *);
ساكن فراغ c_parser_gimple_switch_stmt (gimple_parser &, gimple_seq *);
ساكن فراغ c_parser_gimple_return_stmt (gimple_parser &, gimple_seq *);
ساكن فراغ c_finish_gimple_return (location_t, tree);
ساكن tree c_parser_gimple_paren_condition (gimple_parser &);
ساكن فراغ c_parser_gimple_expr_list (gimple_parser &, vec<tree> *);


/* Much like parser_build_unary_op, but avoid applying default conversions.  */

ساكن c_expr
gimple_parser_build_unary_op (location_t loc,
			      تعداد tree_code code, بنية c_expr arg)
{
  بنية c_expr result;

  result.original_code = code;
  result.original_type = عدم;
  result.m_decimal = 0;

  אם (reject_gcc_builtin (arg.value))
    {
      result.value = error_mark_node;
    }
  אחרת
    {
      result.value = build_unary_op (loc, code, arg.value, אמת);

      אם (TREE_OVERFLOW_P (result.value) && !TREE_OVERFLOW_P (arg.value))
	overflow_warning (loc, result.value, arg.value);
    }

  /* We are typically called when parsing a prefix token at LOC acting on
     ARG.  Reflect this by updating the source range of the result to
     start at LOC and end at the end of ARG.  */
  set_c_expr_source_range (&result,
			   loc, arg.get_finish ());

  החזר result;
}

/* See if VAL is an identifier matching __BB<num> and return <num>
   in *INDEX.  */

ساكن منطقي
c_parser_gimple_parse_bb_spec (tree val, صحيح *index)
{
  אם (!startswith (IDENTIFIER_POINTER (val), "__BB"))
    החזר שקר;

  ثابت حرف *bb = IDENTIFIER_POINTER (val) + 4;
  אם (! ISDIGIT (*bb))
    החזר שקר;

  حرف *pend;
  errno = 0;
  ثابت unsigned long number = strtoul (bb, &pend, 10);
  אם (errno == ERANGE
      || *pend != '\0'
      || number > INT_MAX)
    החזר שקר;

  *index = number;
  החזר אמת;
}

/* See if VAL is an identifier matching __BB<num> and return <num>
   in *INDEX.  Return true if so and parse also FREQUENCY of
   the edge.  */


ساكن منطقي
c_parser_gimple_parse_bb_spec_edge_probability (tree val,
						gimple_parser &parser,
						صحيح *index,
						profile_probability
						*probability)
{
  منطقي return_p = c_parser_gimple_parse_bb_spec (val, index);
  אם (return_p)
    {
      *probability = profile_probability::uninitialized ();
      /* Parse frequency if provided.  */
      אם (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	{
	  tree f;
	  c_parser_consume_token (parser);
	  אם (!c_parser_next_token_is (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected frequency quality");
	      החזר שקר;
	    }

	  profile_quality quality;
	  ثابت حرف *v
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->value);
	  אם (!parse_profile_quality (v, &quality))
	    {
	      c_parser_error (parser, "unknown profile quality");
	      החזר שקר;
	    }

	  c_parser_consume_token (parser);
	  אם (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    החזר שקר;

	  אם (!c_parser_next_token_is (parser, CPP_NUMBER)
	      || (TREE_CODE (f = c_parser_peek_token (parser)->value)
		  != INTEGER_CST))
	    {
	      c_parser_error (parser, "expected frequency value");
	      החזר שקר;
	    }

	  unsigned صحيح value = TREE_INT_CST_LOW (f);
	  *probability = profile_probability (value, quality);

	  c_parser_consume_token (parser);
	  אם (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    החזר שקר;

	  אם (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    החזר שקר;
	}

      החזר אמת;
    }

  החזר שקר;

}

/* Parse the body of a function declaration marked with "__GIMPLE".  */

فراغ
c_parser_parse_gimple_body (c_parser *cparser, حرف *gimple_pass,
			    تعداد c_declspec_il cdil,
			    profile_count entry_bb_count)
{
  gimple_parser parser (cparser);
  gimple_seq seq = عدم;
  gimple_seq body = عدم;
  tree stmt = push_stmt_list ();
  push_scope ();
  location_t loc1 = c_parser_peek_token (parser)->location;

  cfun->pass_startwith = gimple_pass;
  init_tree_ssa (cfun);

  אם (cdil == cdil_gimple)
    /* While we have SSA names in the IL we do not have a CFG built yet
       and PHIs are represented using a PHI internal function.  We do
       have lowered control flow and exception handling (well, we do not
       have parser support for EH yet).  But as we still have BINDs
       we have to go through lowering again.  */
    cfun->curr_properties = PROP_gimple_any;
  אחרת
    {
      /* We have at least cdil_gimple_cfg.  */
      gimple_register_cfg_hooks ();
      init_empty_tree_cfg ();
      parser.current_bb = ENTRY_BLOCK_PTR_FOR_FN (cfun);
      /* Initialize the bare loop structure - we are going to only
         mark headers and leave the rest to fixup.  */
      set_loops_for_fn (cfun, ggc_cleared_alloc<بنية loops> ());
      init_loops_structure (cfun, loops_for_fn (cfun), 1);
      loops_state_set (cfun, LOOPS_NEED_FIXUP|LOOPS_MAY_HAVE_MULTIPLE_LATCHES);
      cfun->curr_properties
	|= PROP_gimple_lcf | PROP_gimple_leh | PROP_cfg | PROP_loops;
      אם (cdil == cdil_gimple_ssa)
	{
	  init_ssa_operands (cfun);
	  cfun->curr_properties |= PROP_ssa;
	}
    }

  אם (! c_parser_gimple_compound_statement (parser, &seq)
      && cdil == cdil_gimple)
    {
      gimple *ret = gimple_build_return (عدم);
      gimple_seq_add_stmt_without_update (&seq, ret);
    }

  tree block = pop_scope ();
  stmt = pop_stmt_list (stmt);
  stmt = c_build_bind_expr (loc1, block, stmt);

  block = DECL_INITIAL (current_function_decl);
  BLOCK_SUBBLOCKS (block) = NULL_TREE;
  BLOCK_CHAIN (block) = NULL_TREE;
  TREE_ASM_WRITTEN (block) = 1;

  אם (cdil == cdil_gimple)
    {
      gbind *bind_stmt = gimple_build_bind (BIND_EXPR_VARS (stmt), عدم,
					    BIND_EXPR_BLOCK (stmt));
      gimple_bind_set_body (bind_stmt, seq);
      gimple_seq_add_stmt_without_update (&body, bind_stmt);
      gimple_set_body (current_function_decl, body);
    }
  אחרת
    {
      /* Control-flow and binds are lowered, record local decls.  */
      עבור (tree var = BIND_EXPR_VARS (stmt); var; var = DECL_CHAIN (var))
	אם (VAR_P (var)
	    && !DECL_EXTERNAL (var))
	  {
	    add_local_decl (cfun, var);
	    /* When the middle-end re-gimplifies any expression we might
	       run into the assertion that we've seen the decl in a BIND.  */
	    אם (!TREE_STATIC (var))
	      DECL_SEEN_IN_BIND_EXPR_P (var) = 1;
	  }
      /* We have a CFG.  Build the edges.  */
      עבור (unsigned i = 0; i < parser.edges.length (); ++i)
	{
	  edge e = make_edge (BASIC_BLOCK_FOR_FN (cfun, parser.edges[i].src),
			      BASIC_BLOCK_FOR_FN (cfun, parser.edges[i].dest),
			      parser.edges[i].flags);
	  e->probability = parser.edges[i].probability;
	}
      /* Add edges for case labels.  */
      basic_block bb;
      FOR_EACH_BB_FN (bb, cfun)
	אם (EDGE_COUNT (bb->succs) == 0)
	  {
	    אם (gswitch *sw = safe_dyn_cast <gswitch *> (*gsi_last_bb (bb)))
	      עבור (unsigned i = 0; i < gimple_switch_num_labels (sw); ++i)
		{
		  basic_block label_bb = gimple_switch_label_bb (cfun, sw, i);
		  make_edge (bb, label_bb, 0);
		}
	  }
      /* Need those for loop fixup.  */
      calculate_dominance_info (CDI_DOMINATORS);
      /* With SSA lower PHIs parsed as internal function calls and
	 update stmts.  */
      אם (cdil == cdil_gimple_ssa)
	{
	  /* Create PHI nodes, they are parsed into __PHI internal calls
	     and update SSA operands.  */
	  FOR_EACH_BB_FN (bb, cfun)
	    {
	      gimple_stmt_iterator gsi;
	      עבור (gsi = gsi_start_bb (bb); !gsi_end_p (gsi);)
		{
		  gimple *stmt = gsi_stmt (gsi);
		  אם (!gimple_call_internal_p (stmt, IFN_PHI))
		    اكسر;

		  gphi *phi = create_phi_node (gimple_call_lhs (stmt), bb);
		  עבור (unsigned i = 0; i < gimple_call_num_args (stmt); i += 2)
		    {
		      صحيح srcidx = TREE_INT_CST_LOW (gimple_call_arg (stmt, i));
		      edge e = find_edge (BASIC_BLOCK_FOR_FN (cfun, srcidx), bb);
		      אם (!e)
			c_parser_error (parser, "edge not found");
		      אחרת
			add_phi_arg (phi, gimple_call_arg (stmt, i + 1), e,
				     UNKNOWN_LOCATION);
		    }
		  gsi_remove (&gsi, אמת);
		}
	      עבור (; !gsi_end_p (gsi); gsi_next (&gsi))
		update_stmt (gsi_stmt (gsi));
	    }
	  /* Fill SSA name gaps, putting them on the freelist and diagnose
	     SSA names without definition.  */
	  עבור (unsigned i = 1; i < num_ssa_names; ++i)
	    אם (!ssa_name (i))
	      {
		tree name = make_ssa_name_fn (cfun, integer_type_node, عدم, i);
		release_ssa_name_fn (cfun, name);
	      }
	    אחרת אם (!SSA_NAME_DEF_STMT (ssa_name (i)))
	      error ("SSA name %qE with version %d has no definition",
		     ssa_name (i), i);
	  /* No explicit virtual operands (yet).  */
	  bitmap_obstack_initialize (عدم);
	  update_ssa (TODO_update_ssa_only_virtuals);
	  bitmap_obstack_release (عدم);
	  /* ???  By flushing the freelist after virtual operand SSA rewrite
	     we keep the gaps available for re-use like needed for the
	     PR89595 testcase but then usually virtual operands would have
	     taken most of them.  The fix is obviously to make virtual
	     operands explicit in the SSA IL.  */
	  flush_ssaname_freelist ();
	}
      fix_loop_structure (عدم);
    }

  אם (cfun->curr_properties & PROP_cfg)
    {
      ENTRY_BLOCK_PTR_FOR_FN (cfun)->count = entry_bb_count;
      gcov_type t = param_gimple_fe_computed_hot_bb_threshold;
      set_hot_bb_threshold (t);
      update_max_bb_count ();
      cgraph_node::get_create (cfun->decl);
      cgraph_edge::rebuild_edges ();
    }

  /* Perform IL validation and if any error is found abort compilation
     of this function by zapping its body.  */
  אם ((cfun->curr_properties & PROP_cfg)
      && verify_gimple_in_cfg (cfun, שקר, שקר))
    init_empty_tree_cfg ();
  אחרת אם (!(cfun->curr_properties & PROP_cfg)
	   && verify_gimple_in_seq (gimple_body (current_function_decl), שקר))
    gimple_set_body (current_function_decl, عدم);

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

ساكن منطقي
c_parser_gimple_compound_statement (gimple_parser &parser, gimple_seq *seq)
{
  منطقي return_p = שקר;

  אם (! c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    החזר שקר;

  /* A compound statement starts with optional declarations.  */
  כלעוד (c_parser_next_tokens_start_declaration (parser))
    {
      c_parser_gimple_declaration (parser);
      אם (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	החזר שקר;
    }

  כלעוד (c_parser_next_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      אם (c_parser_error (parser))
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_BRACE, عدم);
	  החזר return_p;
	}
      אחרת אם (c_parser_next_token_is (parser, CPP_EOF))
	{
	  c_parser_error (parser, "expected declaration or statement");
	  החזר return_p;
	}

      بدل (c_parser_peek_token (parser)->type)
	{
	حالة CPP_KEYWORD:
	  بدل (c_parser_peek_token (parser)->keyword)
	    {
	    حالة RID_AT_TRY:
	      c_parser_gimple_try_stmt (parser, seq);
	      اكسر;
	    حالة RID_IF:
	      c_parser_gimple_if_stmt (parser, seq);
	      اكسر;
	    حالة RID_SWITCH:
	      c_parser_gimple_switch_stmt (parser, seq);
	      اكسر;
	    حالة RID_GOTO:
	      {
		location_t loc = c_parser_peek_token (parser)->location;
		c_parser_consume_token (parser);
		אם (c_parser_next_token_is (parser, CPP_NAME))
		  {
		    tree label = c_parser_peek_token (parser)->value;
		    c_parser_consume_token (parser);
		    c_parser_gimple_goto_stmt (parser, loc, label, seq);
		    אם (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      החזר return_p;
		  }
		}
	      اكسر;
	    حالة RID_RETURN:
	      return_p = אמת;
	      c_parser_gimple_return_stmt (parser, seq);
	      אם (! c_parser_require (parser, CPP_SEMICOLON,
				      "expected %<;%>"))
		החזר return_p;
	      אם (cfun->curr_properties & PROP_cfg)
		parser.push_edge (parser.current_bb->index, EXIT_BLOCK, 0,
				  profile_probability::uninitialized ());
	      اكسر;
	    افتراضي:
	      اذهب expr_stmt;
	    }
	  اكسر;
	حالة CPP_NAME:
	  אם (c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_gimple_label (parser, seq);
	      اكسر;
	    }
	  אם (c_parser_next_token_is (parser, CPP_NAME)
	      && c_parser_peek_token (parser)->id_kind == C_ID_ID
	      && strcmp (IDENTIFIER_POINTER (c_parser_peek_token (parser)->value),
			 "try") == 0)
	    {
	      c_parser_gimple_try_stmt (parser, seq);
	      اكسر;
	    }
	  /* Basic block specification.
	     __BB (index, ...)  */
	  אם ((cfun->curr_properties & PROP_cfg)
	      && !strcmp (IDENTIFIER_POINTER
			    (c_parser_peek_token (parser)->value), "__BB"))
	    {
	      c_parser_consume_token (parser);
	      אם (! c_parser_require (parser, CPP_OPEN_PAREN,
				      "expected %<(%>"))
		החזר return_p;
	      אם (c_parser_next_token_is_not (parser, CPP_NUMBER))
		{
		  c_parser_error (parser, "expected block index");
		  החזר return_p;
		}
	      tree tnum = c_parser_peek_token (parser)->value;
	      אם (TREE_CODE (tnum) != INTEGER_CST)
		{
		  c_parser_error (parser, "expected block index");
		  החזר return_p;
		}
	      صحيح index = TREE_INT_CST_LOW (tnum);
	      אם (index < NUM_FIXED_BLOCKS
		  || (index < last_basic_block_for_fn (cfun)
		      && BASIC_BLOCK_FOR_FN (cfun, index) != عدم))
		{
		  c_parser_error (parser, "invalid block index");
		  החזר return_p;
		}
	      صحيح is_loop_header_of = -1;
	      profile_count bb_count = profile_count::uninitialized ();
	      c_parser_consume_token (parser);
	      כלעוד (c_parser_next_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  אם (! c_parser_next_token_is (parser, CPP_NAME))
		    {
		      c_parser_error (parser, "expected block specifier");
		      החזר return_p;
		    }
		  /* loop_header (NUM)  */
		  אם (!strcmp (IDENTIFIER_POINTER
			         (c_parser_peek_token (parser)->value),
			       "loop_header"))
		    {
		      c_parser_consume_token (parser);
		      אם (! c_parser_require (parser, CPP_OPEN_PAREN,
					      "expected %<(%>"))
			החזר return_p;
		      tree loop_num;
		      אם (! c_parser_next_token_is (parser, CPP_NUMBER)
			  || TREE_CODE (loop_num
					  = c_parser_peek_token (parser)->value)
			       != INTEGER_CST)
			{
			  c_parser_error (parser, "expected loop number");
			  החזר return_p;
			}
		      c_parser_consume_token (parser);
		      is_loop_header_of = TREE_INT_CST_LOW (loop_num);
		      אם (! c_parser_require (parser, CPP_CLOSE_PAREN,
					      "expected %<)%>"))
			החזר return_p;
		    }
		  /* Parse profile: quality(value) */
		  אחרת
		    {
		      tree q;
		      profile_quality quality;
		      tree v = c_parser_peek_token (parser)->value;
		      אם (!parse_profile_quality (IDENTIFIER_POINTER (v),
						  &quality))
			{
			  c_parser_error (parser, "unknown block specifier");
			  החזר שקר;
			}

		      c_parser_consume_token (parser);
		      אם (!c_parser_require (parser, CPP_OPEN_PAREN,
					     "expected %<(%>"))
			החזר שקר;

		      אם (!c_parser_next_token_is (parser, CPP_NUMBER)
			  || (TREE_CODE (q = c_parser_peek_token (parser)->value)
			      != INTEGER_CST))
			{
			  c_parser_error (parser, "expected count value");
			  החזר שקר;
			}

		      bb_count
			= profile_count::from_gcov_type (TREE_INT_CST_LOW (q),
							 quality);
		      c_parser_consume_token (parser);
		      אם (! c_parser_require (parser, CPP_CLOSE_PAREN,
					      "expected %<)%>"))
			החזר return_p;
		    }
		}
	      אם (! c_parser_require (parser, CPP_CLOSE_PAREN,
				      "expected %<)%>")
		  || ! c_parser_require (parser, CPP_COLON,
					 "expected %<:%>"))
		החזר return_p;

	      /* Put stmts parsed in the current block.  */
	      אם (!gimple_seq_empty_p (*seq))
		{
		  אם (!parser.current_bb)
		    c_parser_error (parser, "stmts without block");
		  אחרת
		    {
		      gimple_stmt_iterator gsi
			= gsi_start_bb (parser.current_bb);
		      gsi_insert_seq_after_without_update (&gsi, *seq,
							   GSI_CONTINUE_LINKING);
		    }
		  *seq = عدم;
		}

	      /* Build an empty block with specified index, linking them
		 in source order.  */
	      basic_block bb = alloc_block ();
	      bb->index = index;
	      link_block (bb, (parser.current_bb ? parser.current_bb
			       : ENTRY_BLOCK_PTR_FOR_FN (cfun)));
	      אם (basic_block_info_for_fn (cfun)->length () <= (size_t)index)
		vec_safe_grow_cleared (basic_block_info_for_fn (cfun),
				       index + 1, אמת);
	      SET_BASIC_BLOCK_FOR_FN (cfun, index, bb);
	      אם (last_basic_block_for_fn (cfun) <= index)
		last_basic_block_for_fn (cfun) = index + 1;
	      n_basic_blocks_for_fn (cfun)++;
	      אם (parser.current_bb->index == ENTRY_BLOCK)
		parser.push_edge (ENTRY_BLOCK, bb->index, EDGE_FALLTHRU,
				  profile_probability::always ());

	      /* We leave the proper setting to fixup.  */
	      מחלקה loop *loop_father = loops_for_fn (cfun)->tree_root;
	      /* If the new block is a loop header, allocate a loop
		 struct.  Fixup will take care of proper placement within
		 the loop tree.  */
	      אם (is_loop_header_of != -1)
		{
		  אם (number_of_loops (cfun) > (unsigned)is_loop_header_of
		      && get_loop (cfun, is_loop_header_of) != عدم)
		    {
		      c_parser_error (parser, "duplicate loop header");
		    }
		  אחרת
		    {
		      מחלקה loop *loop = alloc_loop ();
		      loop->num = is_loop_header_of;
		      loop->header = bb;
		      אם (number_of_loops (cfun) <= (unsigned)is_loop_header_of)
			vec_safe_grow_cleared (loops_for_fn (cfun)->larray,
					       is_loop_header_of + 1, אמת);
		      (*loops_for_fn (cfun)->larray)[is_loop_header_of] = loop;
		      flow_loop_tree_node_add (loops_for_fn (cfun)->tree_root,
					       loop);
		    }
		  loop_father = get_loop (cfun, is_loop_header_of);
		}
	      bb->loop_father = loop_father;
	      bb->count = bb_count;

	      /* Stmts now go to the new block.  */
	      parser.current_bb = bb;
	      اكسر;
	    }
	  اذهب expr_stmt;

	حالة CPP_SEMICOLON:
	  {
	    /* Empty stmt.  */
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);
	    gimple *nop = gimple_build_nop ();
	    gimple_set_location (nop, loc);
	    gimple_seq_add_stmt_without_update (seq, nop);
	    اكسر;
	  }

	حالة CPP_CLOSE_PAREN:
	حالة CPP_CLOSE_SQUARE:
	  /* Avoid infinite loop in error recovery:
	     c_parser_skip_until_found stops at a closing nesting
	     delimiter without consuming it, but here we need to consume
	     it to proceed further.  */
	  c_parser_error (parser, "expected statement");
	  c_parser_consume_token (parser);
	اكسر;

	افتراضي:
expr_stmt:
	  c_parser_gimple_statement (parser, seq);
	  אם (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	    c_parser_skip_until_found (parser, CPP_SEMICOLON, عدم);
	}
    }
  c_parser_consume_token (parser);

  /* Put stmts parsed in the current block.  */
  אם ((cfun->curr_properties & PROP_cfg)
      && !gimple_seq_empty_p (*seq))
    {
      אם (!parser.current_bb)
	c_parser_error (parser, "stmts without block");
      אחרת
	{
	  gimple_stmt_iterator gsi = gsi_start_bb (parser.current_bb);
	  gsi_insert_seq_after_without_update (&gsi, *seq,
					       GSI_CONTINUE_LINKING);
	}
      *seq = عدم;
    }

  החזר return_p;
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

ساكن فراغ
c_parser_gimple_statement (gimple_parser &parser, gimple_seq *seq)
{
  بنية c_expr lhs, rhs;
  gimple *assign = عدم;
  location_t loc;
  tree arg = NULL_TREE;
  auto_vec<tree> vargs;

  lhs = c_parser_gimple_unary_expression (parser);
  loc = EXPR_LOCATION (lhs.value);
  rhs.set_error ();

  /* GIMPLE call statement without LHS.  */
  אם (c_parser_next_token_is (parser, CPP_SEMICOLON)
      && TREE_CODE (lhs.value) == CALL_EXPR)
    {
      gimple *call;
      call = gimple_build_call_from_tree (lhs.value, عدم);
      gimple_seq_add_stmt_without_update (seq, call);
      gimple_set_location (call, loc);
      החזר;
    }

  /* All following cases are statements with LHS.  */
  אם (! c_parser_require (parser, CPP_EQ, "expected %<=%>"))
    החזר;

  /* Eat and ignore {v} right after the =, the has_volatile_ops is
     redundant and re-computed by the operand scanner.  */
  אם (c_parser_next_token_is (parser, CPP_OPEN_BRACE)
      && !(c_parser_peek_token (parser)->flags & PREV_WHITE)
      && c_parser_peek_2nd_token (parser)->type == CPP_NAME
      && !(c_parser_peek_2nd_token (parser)->flags & PREV_WHITE)
      && strcmp ("v", IDENTIFIER_POINTER
			(c_parser_peek_2nd_token (parser)->value)) == 0
      && c_parser_peek_nth_token (parser, 3)->type == CPP_CLOSE_BRACE
      && !(c_parser_peek_nth_token (parser, 3)->flags & PREV_WHITE))
    {
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }

  /* Cast expression.  */
  אם (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_typename (c_parser_peek_2nd_token (parser)))
    {
      c_parser_consume_token (parser);
      بنية c_type_name *type_name = c_parser_type_name (parser);
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      אם (type_name == عدم)
	החזר;
      /* ???  The actual type used in the cast expression is ignored as
         in GIMPLE it is encoded by the type of the LHS.  */
      rhs = c_parser_gimple_postfix_expression (parser);
      אם (lhs.value != error_mark_node
	  && rhs.value != error_mark_node)
	{
	  تعداد tree_code code = NOP_EXPR;
	  אם (FLOAT_TYPE_P (TREE_TYPE (lhs.value))
	      && ! FLOAT_TYPE_P (TREE_TYPE (rhs.value)))
	    code = FLOAT_EXPR;
	  אחרת אם (! FLOAT_TYPE_P (TREE_TYPE (lhs.value))
		   && FLOAT_TYPE_P (TREE_TYPE (rhs.value)))
	    code = FIX_TRUNC_EXPR;
	  assign = gimple_build_assign (lhs.value, code, rhs.value);
	  gimple_seq_add_stmt_without_update (seq, assign);
	  gimple_set_location (assign, loc);
	  החזר;
	}
    }

  /* Unary expression.  */
  بدل (c_parser_peek_token (parser)->type)
    {
    حالة CPP_NAME:
      {
	tree id = c_parser_peek_token (parser)->value;
	אם (strcmp (IDENTIFIER_POINTER (id), "__ABS") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__ABSU") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__MIN") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__MAX") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__BIT_INSERT") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__VEC_PERM") == 0)
	  اذهب build_unary_expr;
	اكسر;
      }
    حالة CPP_KEYWORD:
      אם (c_parser_peek_token (parser)->keyword != RID_REALPART
	  && c_parser_peek_token (parser)->keyword != RID_IMAGPART)
	اكسر;
      /* Fallthru.  */
    حالة CPP_AND:
    حالة CPP_PLUS:
    حالة CPP_MINUS:
    حالة CPP_COMPL:
    حالة CPP_NOT:
    حالة CPP_MULT: /* pointer deref */
    build_unary_expr:
      rhs = c_parser_gimple_unary_expression (parser);
      אם (rhs.value != error_mark_node)
	{
	  assign = gimple_build_assign (lhs.value, rhs.value);
	  gimple_set_location (assign, loc);
	  gimple_seq_add_stmt_without_update (seq, assign);
	}
      החזר;

    افتراضي:;
    }

  /* GIMPLE PHI statement.  */
  אם (c_parser_next_token_is_keyword (parser, RID_PHI))
    {
      c_parser_consume_token (parser);

      אם (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	החזר;

      אם (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	c_parser_consume_token (parser);

      כלעוד (c_parser_next_token_is_not (parser, CPP_CLOSE_PAREN))
	{
	  אם (c_parser_next_token_is (parser, CPP_NAME)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      arg = c_parser_peek_token (parser)->value;
	      c_parser_consume_token (parser);
	      אם (c_parser_next_token_is (parser, CPP_COLON))
		c_parser_consume_token (parser);
	      صحيح src_index = -1;
	      אם (!c_parser_gimple_parse_bb_spec (arg, &src_index))
		c_parser_error (parser, "invalid source block specification");
	      vargs.safe_push (size_int (src_index));
	    }
	  אחרת אם (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  אחרת
	    {
	      arg = c_parser_gimple_unary_expression (parser).value;
	      vargs.safe_push (arg);
	    }
	}

      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");

      /* Build internal function for PHI.  */
      gcall *call_stmt = gimple_build_call_internal_vec (IFN_PHI, vargs);
      gimple_call_set_lhs (call_stmt, lhs.value);
      gimple_set_location (call_stmt, UNKNOWN_LOCATION);
      gimple_seq_add_stmt_without_update (seq, call_stmt);
      החזר;
    }

  /* GIMPLE call with lhs.  */
  אם (c_parser_next_token_is (parser, CPP_DOT)
      || (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN
	  && lookup_name (c_parser_peek_token (parser)->value)))
    {
      rhs = c_parser_gimple_unary_expression (parser);
      אם (rhs.value != error_mark_node)
	{
	  gimple *call = gimple_build_call_from_tree (rhs.value, عدم);
	  gimple_call_set_lhs (call, lhs.value);
	  gimple_seq_add_stmt_without_update (seq, call);
	  gimple_set_location (call, loc);
	}
      החזר;
    }

  rhs = c_parser_gimple_binary_expression (parser, TREE_TYPE (lhs.value));
  אם (lhs.value != error_mark_node
      && rhs.value != error_mark_node)
    {
      /* If we parsed an identifier and the next token  is a '?' then parse
	 a conditional expression.  */
      אם (SSA_VAR_P (rhs.value) && c_parser_next_token_is (parser, CPP_QUERY))
	{
	  بنية c_expr trueval, falseval;
	  c_parser_consume_token (parser);
	  trueval = c_parser_gimple_postfix_expression (parser);
	  falseval.set_error ();
	  אם (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    falseval = c_parser_gimple_postfix_expression (parser);
	  אם (trueval.value == error_mark_node
	      || falseval.value == error_mark_node)
	    החזר;
	  rhs.value = build3_loc (loc,
				  VECTOR_TYPE_P (TREE_TYPE (rhs.value))
				  ? VEC_COND_EXPR : COND_EXPR,
				  TREE_TYPE (trueval.value),
				  rhs.value, trueval.value, falseval.value);
	}
      אם (get_gimple_rhs_class (TREE_CODE (rhs.value)) == GIMPLE_INVALID_RHS)
	{
	  c_parser_error (parser, "unexpected RHS for assignment");
	  החזר;
	}
      assign = gimple_build_assign (lhs.value, rhs.value);
      gimple_seq_add_stmt_without_update (seq, assign);
      gimple_set_location (assign, loc);
    }
  החזר;
}

/* A mapping between an identifier to a tree code for binary operations. */
ساكن ثابت std::pair<ثابت حرف *, tree_code> gimple_binary_identifier_code[] =
  {
    {"__MULT_HIGHPART", MULT_HIGHPART_EXPR},
    {"__UNLT", UNLT_EXPR},
    {"__UNLE", UNLE_EXPR},
    {"__UNGT", UNGT_EXPR},
    {"__UNGE", UNGE_EXPR},
    {"__UNEQ", UNEQ_EXPR},
    {"__UNORDERED", UNORDERED_EXPR},
    {"__ORDERED", ORDERED_EXPR},
    {"__LTGT", LTGT_EXPR},
    {"__FLOOR_DIV", FLOOR_DIV_EXPR},
    {"__ROUND_DIV", ROUND_DIV_EXPR},
    {"__EXACT_DIV", EXACT_DIV_EXPR},
    {"__CEIL_DIV", CEIL_DIV_EXPR},
    {"__FLOOR_MOD", FLOOR_MOD_EXPR},
    {"__ROUND_MOD", ROUND_MOD_EXPR},
    {"__CEIL_MOD", CEIL_MOD_EXPR},
    {"__ROTATE_LEFT", LROTATE_EXPR},
    {"__ROTATE_RIGHT", RROTATE_EXPR},
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

ساكن c_expr
c_parser_gimple_binary_expression (gimple_parser &parser, tree ret_type)
{
  /* Location of the binary operator.  */
  بنية c_expr ret, lhs, rhs;
  تعداد tree_code code = ERROR_MARK;
  ret.set_error ();
  lhs = c_parser_gimple_postfix_expression (parser, ret_type);
  אם (c_parser_error (parser))
    החזר ret;
  بدل (c_parser_peek_token (parser)->type)
    {
    حالة CPP_MULT:
      code = MULT_EXPR;
      اكسر;
    حالة CPP_DIV:
      code = TRUNC_DIV_EXPR;
      اكسر;
    حالة CPP_MOD:
      code = TRUNC_MOD_EXPR;
      اكسر;
    حالة CPP_PLUS:
      אם (POINTER_TYPE_P (TREE_TYPE (lhs.value)))
	code = POINTER_PLUS_EXPR;
      אחרת
	code = PLUS_EXPR;
      اكسر;
    حالة CPP_MINUS:
      אם (POINTER_TYPE_P (TREE_TYPE (lhs.value)))
	code = POINTER_DIFF_EXPR;
      אחרת
	code = MINUS_EXPR;
      اكسر;
    حالة CPP_LSHIFT:
      code = LSHIFT_EXPR;
      اكسر;
    حالة CPP_RSHIFT:
      code = RSHIFT_EXPR;
      اكسر;
    حالة CPP_LESS:
      code = LT_EXPR;
      اكسر;
    حالة CPP_GREATER:
      code = GT_EXPR;
      اكسر;
    حالة CPP_LESS_EQ:
      code = LE_EXPR;
      اكسر;
    حالة CPP_GREATER_EQ:
      code = GE_EXPR;
      اكسر;
    حالة CPP_EQ_EQ:
      code = EQ_EXPR;
      اكسر;
    حالة CPP_NOT_EQ:
      code = NE_EXPR;
      اكسر;
    حالة CPP_AND:
      code = BIT_AND_EXPR;
      اكسر;
    حالة CPP_XOR:
      code = BIT_XOR_EXPR;
      اكسر;
    حالة CPP_OR:
      code = BIT_IOR_EXPR;
      اكسر;
    حالة CPP_AND_AND:
      c_parser_error (parser, "%<&&%> not valid in GIMPLE");
      החזר ret;
    حالة CPP_OR_OR:
      c_parser_error (parser, "%<||%> not valid in GIMPLE");
      החזר ret;
    حالة CPP_NAME:
      {
	tree id = c_parser_peek_token (parser)->value;
	עבור (auto &p : gimple_binary_identifier_code)
	  {
	    אם (strcmp (IDENTIFIER_POINTER (id), p.first) == 0)
	      {
		code = p.second;
		اكسر;
	      }
	  }
	אם (code != ERROR_MARK)
	  اكسر;
      }
      /* Fallthru.  */
    افتراضي:
      /* Not a binary expression.  */
      החזר lhs;
    }
  location_t ret_loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  rhs = c_parser_gimple_postfix_expression (parser);
  אם (lhs.value != error_mark_node && rhs.value != error_mark_node)
    ret.value = build2_loc (ret_loc, code, ret_type, lhs.value, rhs.value);
  החזר ret;
}

/* Parse a gimple parentized binary expression.  */

ساكن c_expr
c_parser_gimple_parentized_binary_expression (gimple_parser &parser,
					      location_t op_loc,
					      tree_code code)
{
  بنية c_expr ret;
  ret.set_error ();

  c_parser_consume_token (parser);
  אם (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    החזר ret;
  c_expr op1 = c_parser_gimple_postfix_expression (parser);
  אם (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    החזר ret;
  c_expr op2 = c_parser_gimple_postfix_expression (parser);
  אם (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    החזר ret;

  אם (op1.value != error_mark_node && op2.value != error_mark_node)
    ret.value = build2_loc (op_loc,
			    code, TREE_TYPE (op1.value), op1.value, op2.value);
  החזר ret;
}

/* Parse a gimple parentized binary expression.  */

ساكن c_expr
c_parser_gimple_parentized_ternary_expression (gimple_parser &parser,
					       location_t op_loc,
					       tree_code code)
{
  بنية c_expr ret;
  ret.set_error ();

  c_parser_consume_token (parser);
  אם (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    החזר ret;
  c_expr op1 = c_parser_gimple_postfix_expression (parser);
  אם (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    החזר ret;
  c_expr op2 = c_parser_gimple_postfix_expression (parser);
  אם (!c_parser_require (parser, CPP_COMMA, "expected %<)%>"))
    החזר ret;
  c_expr op3 = c_parser_gimple_postfix_expression (parser);
  אם (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    החזר ret;

  אם (op1.value != error_mark_node
      && op2.value != error_mark_node
      && op3.value != error_mark_node)
    ret.value = build3_loc (op_loc,
			    code, TREE_TYPE (op1.value),
			    op1.value, op2.value, op3.value);
  החזר ret;
}

/* Parse gimple unary expression.

   gimple-unary-expression:
     gimple-postfix-expression
     unary-operator gimple-postfix-expression

   unary-operator: one of
     & * + - ~ abs_expr
*/

ساكن c_expr
c_parser_gimple_unary_expression (gimple_parser &parser)
{
  بنية c_expr ret, op;
  location_t op_loc = c_parser_peek_token (parser)->location;
  location_t finish;
  ret.set_error ();
  بدل (c_parser_peek_token (parser)->type)
    {
    حالة CPP_AND:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      mark_exp_read (op.value);
      החזר gimple_parser_build_unary_op (op_loc, ADDR_EXPR, op);
    حالة CPP_MULT:
      {
	c_parser_consume_token (parser);
	op = c_parser_gimple_postfix_expression (parser);
	אם (op.value == error_mark_node)
	  החזר ret;
	אם (! POINTER_TYPE_P (TREE_TYPE (op.value)))
	  {
	    error_at (op_loc, "expected pointer as argument of unary %<*%>");
	    החזר ret;
	  }
	finish = op.get_finish ();
	location_t combined_loc = make_location (op_loc, op_loc, finish);
	ret.value = build_simple_mem_ref_loc (combined_loc, op.value);
	TREE_SIDE_EFFECTS (ret.value)
	  = TREE_THIS_VOLATILE (ret.value)
	  = TYPE_VOLATILE (TREE_TYPE (TREE_TYPE (op.value)));
	ret.src_range.m_start = op_loc;
	ret.src_range.m_finish = finish;
	החזר ret;
      }
    حالة CPP_PLUS:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      החזר gimple_parser_build_unary_op (op_loc, CONVERT_EXPR, op);
    حالة CPP_MINUS:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      החזר gimple_parser_build_unary_op (op_loc, NEGATE_EXPR, op);
    حالة CPP_COMPL:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      החזר gimple_parser_build_unary_op (op_loc, BIT_NOT_EXPR, op);
    حالة CPP_NOT:
      c_parser_error (parser, "%<!%> not valid in GIMPLE");
      החזר ret;
    حالة CPP_KEYWORD:
      بدل (c_parser_peek_token (parser)->keyword)
	{
	حالة RID_REALPART:
	  c_parser_consume_token (parser);
	  op = c_parser_gimple_postfix_expression (parser);
	  החזר gimple_parser_build_unary_op (op_loc, REALPART_EXPR, op);
	حالة RID_IMAGPART:
	  c_parser_consume_token (parser);
	  op = c_parser_gimple_postfix_expression (parser);
	  החזר gimple_parser_build_unary_op (op_loc, IMAGPART_EXPR, op);
	افتراضي:
	  החזר c_parser_gimple_postfix_expression (parser);
	}
    حالة CPP_NAME:
	{
	  tree id = c_parser_peek_token (parser)->value;
	  אם (strcmp (IDENTIFIER_POINTER (id), "__ABS") == 0)
	    {
	      c_parser_consume_token (parser);
	      op = c_parser_gimple_postfix_expression (parser);
	      החזר gimple_parser_build_unary_op (op_loc, ABS_EXPR, op);
	    }
	  אחרת אם (strcmp (IDENTIFIER_POINTER (id), "__ABSU") == 0)
	    {
	      c_parser_consume_token (parser);
	      op = c_parser_gimple_postfix_expression (parser);
	      החזר gimple_parser_build_unary_op (op_loc, ABSU_EXPR, op);
	    }
	  אחרת אם (strcmp (IDENTIFIER_POINTER (id), "__MIN") == 0)
	    החזר c_parser_gimple_parentized_binary_expression (parser,
								 op_loc,
								 MIN_EXPR);
	  אחרת אם (strcmp (IDENTIFIER_POINTER (id), "__MAX") == 0)
	    החזר c_parser_gimple_parentized_binary_expression (parser,
								 op_loc,
								 MAX_EXPR);
	  אחרת אם (strcmp (IDENTIFIER_POINTER (id), "__VEC_PERM") == 0)
	    החזר c_parser_gimple_parentized_ternary_expression
			(parser, op_loc, VEC_PERM_EXPR);
	  אחרת אם (strcmp (IDENTIFIER_POINTER (id), "__BIT_INSERT") == 0)
	    {
	      /* __BIT_INSERT '(' postfix-expression, postfix-expression,
			          integer ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      אם (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_expr op0 = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_expr op1 = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_expr op2 = c_parser_gimple_postfix_expression (parser);
		  אם (TREE_CODE (op2.value) != INTEGER_CST
		      || !int_fits_type_p (op2.value, bitsizetype))
		    c_parser_error (parser, "expected constant offset");
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  אם (op0.value != error_mark_node
		      && op1.value != error_mark_node
		      && TREE_CODE (op2.value) == INTEGER_CST)
		    ret.value = build3_loc (loc, BIT_INSERT_EXPR,
					    TREE_TYPE (op0.value),
					    op0.value, op1.value,
					    fold_convert (bitsizetype,
							  op2.value));
		}
	      החזר ret;
	    }
	  אחרת
	    החזר c_parser_gimple_postfix_expression (parser);
	}
    افتراضي:
      החזר c_parser_gimple_postfix_expression (parser);
    }
}

/* Decompose ID into base name (ID until ver_offset) and VERSION.  Return
   true if ID matches a SSA name.  */

ساكن منطقي
c_parser_parse_ssa_name_id (tree id, unsigned *version, unsigned *ver_offset)
{
  ثابت حرف *token = IDENTIFIER_POINTER (id);
  ثابت حرف *var_version = strrchr (token, '_');
  אם (! var_version)
    החזר שקר;

  *ver_offset = var_version - token;
  עבור (ثابت حرف *p = var_version + 1; *p; ++p)
    אם (! ISDIGIT (*p))
      החזר שקר;
  *version = atoi (var_version + 1);
  החזר *version > 0;
}

/* Get at the actual SSA name ID with VERSION starting at VER_OFFSET.
   TYPE is the type if the SSA name is being declared.  */

ساكن tree
c_parser_parse_ssa_name (gimple_parser &parser,
			 tree id, tree type, unsigned version,
			 unsigned ver_offset)
{
  tree name = NULL_TREE;
  ثابت حرف *token = IDENTIFIER_POINTER (id);

  אם (ver_offset == 0)
    {
      /* Anonymous unnamed SSA name.  */
      אם (version < num_ssa_names)
	name = ssa_name (version);
      אם (! name)
	{
	  אם (! type)
	    {
	      c_parser_error (parser, "SSA name undeclared");
	      החזר error_mark_node;
	    }
	  name = make_ssa_name_fn (cfun, type, عدم, version);
	}
    }
  אחרת
    {
      אם (version < num_ssa_names)
	name = ssa_name (version);
      אם (! name)
	{
	  /* Separate var name from version.  */
	  حرف *var_name = XNEWVEC (حرف, ver_offset + 1);
	  memcpy (var_name, token, ver_offset);
	  var_name[ver_offset] = '\0';
	  /* lookup for parent decl.  */
	  id = get_identifier (var_name);
	  tree parent = lookup_name (id);
	  XDELETEVEC (var_name);
	  אם (! parent || parent == error_mark_node)
	    {
	      c_parser_error (parser, "base variable or SSA name undeclared");
	      החזר error_mark_node;
	    }
	  אם (!(VAR_P (parent)
		|| TREE_CODE (parent) == PARM_DECL
		|| TREE_CODE (parent) == RESULT_DECL))
	    {
	      error ("invalid base %qE for SSA name", parent);
	      החזר error_mark_node;
	    }
	  name = make_ssa_name_fn (cfun, parent,
				   gimple_build_nop (), version);
	}
    }

  החזר name;
}

/* Parse a gimple call to an internal function.

   gimple-call-internal:
     . identifier ( gimple-argument-expression-list[opt] )  */

ساكن بنية c_expr
c_parser_gimple_call_internal (gimple_parser &parser)
{
  بنية c_expr expr;
  expr.set_error ();

  gcc_assert (c_parser_next_token_is (parser, CPP_DOT));
  c_parser_consume_token (parser);
  location_t loc = c_parser_peek_token (parser)->location;
  אם (!c_parser_next_token_is (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_kind != C_ID_ID)
    {
      c_parser_error (parser, "expecting internal function name");
      החזר expr;
    }
  tree id = c_parser_peek_token (parser)->value;
  internal_fn ifn = lookup_internal_fn (IDENTIFIER_POINTER (id));
  c_parser_consume_token (parser);
  אם (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    {
      auto_vec<tree> exprlist;
      אם (!c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_gimple_expr_list (parser, &exprlist);
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      אם (ifn == IFN_LAST)
	error_at (loc, "unknown internal function %qE", id);
      אחרת
	{
	  expr.value = build_call_expr_internal_loc_array
	    (loc, ifn, void_type_node, exprlist.length (),
	     exprlist.address ());
	  expr.original_code = ERROR_MARK;
	  expr.original_type = عدم;
	  expr.m_decimal = 0;
	}
    }
  החזר expr;
}

/* Parse '<' type [',' alignment] '>' and return a type on success
   and NULL_TREE on error.  */

ساكن tree
c_parser_gimple_typespec (gimple_parser &parser)
{
  بنية c_type_name *type_name = عدم;
  tree alignment = NULL_TREE;
  אם (c_parser_require (parser, CPP_LESS, "expected %<<%>"))
    {
      type_name = c_parser_type_name (parser);
      /* Optional alignment.  */
      אם (c_parser_next_token_is (parser, CPP_COMMA))
	{
	  c_parser_consume_token (parser);
	  alignment
	      = c_parser_gimple_postfix_expression (parser).value;
	}
      c_parser_skip_until_found (parser,
				 CPP_GREATER, "expected %<>%>");
    }
  אם (!type_name)
    החזר NULL_TREE;
  tree tem;
  tree type = groktypename (type_name, &tem, عدم);
  אם (alignment)
    type = build_aligned_type (type, tree_to_uhwi (alignment));
  החזר type;
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

ساكن بنية c_expr
c_parser_gimple_postfix_expression (gimple_parser &parser, tree ret_type)
{
  location_t loc = c_parser_peek_token (parser)->location;
  source_range tok_range = c_parser_peek_token (parser)->get_range ();
  بنية c_expr expr;
  expr.set_error ();
  بدل (c_parser_peek_token (parser)->type)
    {
    حالة CPP_NUMBER:
      expr.value = c_parser_peek_token (parser)->value;
      set_c_expr_source_range (&expr, tok_range);
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      اكسر;
    حالة CPP_CHAR:
    حالة CPP_CHAR16:
    حالة CPP_CHAR32:
    حالة CPP_UTF8CHAR:
    حالة CPP_WCHAR:
      expr.value = c_parser_peek_token (parser)->value;
      set_c_expr_source_range (&expr, tok_range);
      c_parser_consume_token (parser);
      اكسر;
    حالة CPP_STRING:
    حالة CPP_STRING16:
    حالة CPP_STRING32:
    حالة CPP_WSTRING:
    حالة CPP_UTF8STRING:
      expr = c_parser_string_literal (parser, שקר, אמת);
      اكسر;
    حالة CPP_DOT:
      expr = c_parser_gimple_call_internal (parser);
      اكسر;
    حالة CPP_NAME:
      אם (c_parser_peek_token (parser)->id_kind == C_ID_ID)
	{
	  tree id = c_parser_peek_token (parser)->value;
	  אם (strcmp (IDENTIFIER_POINTER (id), "__MEM") == 0)
	    {
	      /* __MEM '<' type-name [ ',' number ] '>'
	               '(' [ '(' type-name ')' ] unary-expression
			   [ '+' number ]
			   [ ',' number ]
			   [ ',' number ':' number ] ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      tree type = c_parser_gimple_typespec (parser);
	      بنية c_expr ptr, alias_off, step, index, index2;
	      ptr.value = error_mark_node;
	      alias_off.value = NULL_TREE;
	      step.value = NULL_TREE;
	      index.value = NULL_TREE;
	      index2.value = NULL_TREE;
	      unsigned short clique = 0;
	      unsigned short base = 0;
	      منطقي reverse_order = שקר;
	      بنية c_expr ro;
	      אם (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  tree alias_type = NULL_TREE;
		  /* Optional alias-type cast.  */
		  אם (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
		    {
		      c_parser_consume_token (parser);
		      بنية c_type_name *alias_type_name
			= c_parser_type_name (parser);
		      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
						 "expected %<)%>");
		      אם (alias_type_name)
			{
			  tree tem;
			  alias_type = groktypename (alias_type_name,
						     &tem, عدم);
			}
		    }
		  ptr = c_parser_gimple_unary_expression (parser);
		  אם (ptr.value == error_mark_node
		      || ! POINTER_TYPE_P (TREE_TYPE (ptr.value)))
		    {
		      אם (ptr.value != error_mark_node)
			error_at (ptr.get_start (),
				  "invalid type of %<__MEM%> operand");
		      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
						 "expected %<)%>");
		      החזר expr;
		    }
		  אם (! alias_type)
		    alias_type = TREE_TYPE (ptr.value);
		  /* Optional constant offset.  */
		  אם (c_parser_next_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      alias_off = c_parser_gimple_postfix_expression (parser);
		    }
		  אם (c_parser_next_token_is (parser, CPP_MULT))
		    {
		      std::swap (index, alias_off);
		      c_parser_consume_token (parser);
		      step = c_parser_gimple_postfix_expression (parser);
		    }
		  אחרת אם (c_parser_next_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      index = c_parser_gimple_postfix_expression (parser);
		      אם (c_parser_next_token_is (parser, CPP_MULT))
			{
			  c_parser_consume_token (parser);
			  step = c_parser_gimple_postfix_expression (parser);
			}
		      אחרת
			std::swap (index, index2);
		    }
		  אחרת אם (alias_off.value
			   && TREE_CODE (alias_off.value) != INTEGER_CST)
		    std::swap (alias_off, index2);
		  אם (c_parser_next_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      index2 = c_parser_gimple_postfix_expression (parser);
		    }
		  אם (alias_off.value)
		    {
		      אם (TREE_CODE (alias_off.value) != INTEGER_CST)
			error_at (alias_off.get_start (),
				  "expected constant offset for %<__MEM%> "
				  "operand");
		      alias_off.value = fold_convert (alias_type,
						      alias_off.value);
		    }
		  אחרת
		    alias_off.value = build_int_cst (alias_type, 0);
		  אם (step.value)
		    {
		      אם (TREE_CODE (step.value) != INTEGER_CST)
			error_at (step.get_start (),
				  "expected constant step for %<__MEM%> "
				  "operand");
		    }
		  אם (c_parser_next_token_is (parser, CPP_COMMA))
		    {
		      بنية c_expr cl, ba;
		      منطقي has_clb = אמת;
		      c_parser_consume_token (parser);
		      cl = c_parser_gimple_postfix_expression (parser);
		      אם (!c_parser_next_token_is (parser, CPP_COLON))
			{
			  ro = cl;
			  unsigned HOST_WIDE_INT tmp = 0;
			  אם (!tree_fits_uhwi_p (ro.value)
			      || (tmp = tree_to_uhwi (ro.value)) > 1)
			    error_at (ro.get_start (),
				      "invalid reverse order value");
			  reverse_order = tmp;
			  has_clb = שקר;
			  אם (c_parser_next_token_is (parser, CPP_COMMA))
			    {
			      c_parser_consume_token (parser);
			      cl = c_parser_gimple_postfix_expression (parser);
		              has_clb = אמת;
			    }
			}
		      אם (has_clb
			  && c_parser_require (parser,
					       CPP_COLON, "expected %<:%>"))
			{
			  ba = c_parser_gimple_postfix_expression (parser);
			  אם (!tree_fits_uhwi_p (cl.value)
			      || !tree_fits_uhwi_p (ba.value)
			      || compare_tree_int (cl.value,
						   (clique = tree_to_uhwi
								(cl.value)))
			      || compare_tree_int (ba.value,
						   (base = tree_to_uhwi
								 (ba.value))))
			    error_at (cl.get_start (),
				      "invalid clique/base pair");
			}
		    }
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      אם (! type || c_parser_error (parser))
		{
		  c_parser_set_error (parser, שקר);
		  החזר expr;
		}
	      אם (index.value || step.value || index2.value)
		expr.value = build5_loc (loc, TARGET_MEM_REF,
					 type, ptr.value, alias_off.value,
					 index.value, step.value, index2.value);
	      אחרת
		expr.value = build2_loc (loc, MEM_REF,
					 type, ptr.value, alias_off.value);
	      אם (clique != 0)
		{
		  cfun->last_clique = MAX (cfun->last_clique, clique);
		  MR_DEPENDENCE_CLIQUE (expr.value) = clique;
		  MR_DEPENDENCE_BASE (expr.value) = base;
		}
	      אם (reverse_order)
		{
		  אם (TREE_CODE (expr.value) == MEM_REF)
		    REF_REVERSE_STORAGE_ORDER (expr.value) = reverse_order;
		  אחרת
		    error_at (ro.get_start (),
			      "target mem ref cannot have reverse order");
		}
	      اكسر;
	    }
	  אחרת אם (strcmp (IDENTIFIER_POINTER (id), "__VIEW_CONVERT") == 0)
	    {
	      /* __VIEW_CONVERT '<' type-name [ ',' number ] '>'
	                        '(' postfix-expression ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      tree type = c_parser_gimple_typespec (parser);
	      אם (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_expr op = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  אם (type && op.value != error_mark_node)
		    expr.value = build1_loc (loc, VIEW_CONVERT_EXPR,
					     type, op.value);
		}
	      اكسر;
	    }
	  אחרת אם (strcmp (IDENTIFIER_POINTER (id), "__BIT_FIELD_REF") == 0)
	    {
	      /* __BIT_FIELD_REF '<' type-name [ ',' number ] '>'
	                        '(' postfix-expression, integer, integer ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      tree type = c_parser_gimple_typespec (parser);
	      אם (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_expr op0 = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_expr op1 = c_parser_gimple_postfix_expression (parser);
		  אם (TREE_CODE (op1.value) != INTEGER_CST
		      || !int_fits_type_p (op1.value, bitsizetype))
		    c_parser_error (parser, "expected constant size");
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_expr op2 = c_parser_gimple_postfix_expression (parser);
		  אם (TREE_CODE (op2.value) != INTEGER_CST
		      || !int_fits_type_p (op2.value, bitsizetype))
		    c_parser_error (parser, "expected constant offset");
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  אם (type
		      && op0.value != error_mark_node
		      && TREE_CODE (op1.value) == INTEGER_CST
		      && TREE_CODE (op2.value) == INTEGER_CST)
		    expr.value = build3_loc (loc, BIT_FIELD_REF, type,
					     op0.value,
					     fold_convert (bitsizetype,
							   op1.value),
					     fold_convert (bitsizetype,
							   op2.value));
		}
	      اكسر;
	    }
	  אחרת אם (strcmp (IDENTIFIER_POINTER (id), "__CLOBBER") == 0)
	    {
	      /* __CLOBBER [ '(' bob | eob | bos | eos ')' ]  */
	      clobber_kind kind = CLOBBER_UNDEF;
	      c_parser_consume_token (parser);
	      אם (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
		{
		  c_parser_consume_token (parser);
		  auto tok = c_parser_peek_token (parser);
		  אם (c_parser_require (parser, CPP_NAME,
					"expected clobber kind"))
		    {
		      ثابت حرف *kind_str = IDENTIFIER_POINTER (tok->value);
		      אם (strcmp (kind_str, "bos") == 0)
			kind = CLOBBER_STORAGE_BEGIN;
		      אחרת אם (strcmp (kind_str, "bob") == 0)
			kind = CLOBBER_OBJECT_BEGIN;
		      אחרת אם (strcmp (kind_str, "eob") == 0)
			kind = CLOBBER_OBJECT_END;
		      אחרת אם (strcmp (kind_str, "eos") == 0)
			kind = CLOBBER_STORAGE_END;
		      אחרת
			c_parser_error (parser, "expected one of %<bos%>, "
					"%<eos%>, %<bob>, %<eob%>");
		    }
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      /* We infer the (redundant) type from the LHS.  */
	      expr.value = build_clobber (ret_type, kind);
	      اكسر;
	    }
	  אחרת אם (strcmp (IDENTIFIER_POINTER (id), "_Literal") == 0)
	    {
	      /* _Literal '(' type-name ')' ( [ '-' ] constant | constructor ) */
	      c_parser_consume_token (parser);
	      tree type = NULL_TREE;
	      אם (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  بنية c_type_name *type_name = c_parser_type_name (parser);
		  tree tem;
		  אם (type_name)
		    type = groktypename (type_name, &tem, عدم);
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      אם (! type)
		{
		  c_parser_error (parser, "invalid _Literal");
		  החזר expr;
		}
	      אם (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
		{
		  c_parser_consume_token (parser);
		  אם (!AGGREGATE_TYPE_P (type)
		      && !VECTOR_TYPE_P (type))
		    {
		      c_parser_error (parser, "invalid type for _Literal with "
				      "constructor");
		      c_parser_skip_until_found (parser, CPP_CLOSE_BRACE,
						 "expected %<}%>");
		      החזר expr;
		    }
		  vec<constructor_elt, va_gc> *v = عدم;
		  منطقي constant_p = אמת;
		  אם (VECTOR_TYPE_P (type)
		      && !c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
		    {
		      vec_alloc (v, TYPE_VECTOR_SUBPARTS (type).to_constant ());
		      עשה
			{
			  tree val
			    = c_parser_gimple_postfix_expression (parser).value;
			  אם (! val
			      || val == error_mark_node
			      || (! CONSTANT_CLASS_P (val)
				  && ! SSA_VAR_P (val)))
			    {
			      c_parser_error (parser, "invalid _Literal");
			      החזר expr;
			    }
			  CONSTRUCTOR_APPEND_ELT (v, NULL_TREE, val);
			  אם (! CONSTANT_CLASS_P (val))
			    constant_p = שקר;
			  אם (c_parser_next_token_is (parser, CPP_COMMA))
			    c_parser_consume_token (parser);
			  אחרת
			    اكسر;
			}
		      כלעוד (1);
		    }
		  אם (c_parser_require (parser, CPP_CLOSE_BRACE,
					"expected %<}%>"))
		    {
		      אם (v && constant_p)
			expr.value = build_vector_from_ctor (type, v);
		      אחרת
			expr.value = build_constructor (type, v);
		    }
		  אחרת
		    {
		      c_parser_skip_until_found (parser, CPP_CLOSE_BRACE,
						 "expected %<}%>");
		      החזר expr;
		    }
		}
	      אחרת
		{
		  منطقي neg_p, addr_p;
		  אם ((neg_p = c_parser_next_token_is (parser, CPP_MINUS)))
		    c_parser_consume_token (parser);
		  אם ((addr_p = c_parser_next_token_is (parser, CPP_AND)))
		    c_parser_consume_token (parser);
		  tree val = c_parser_gimple_postfix_expression (parser).value;
		  אם (! val
		      || val == error_mark_node
		      || (!CONSTANT_CLASS_P (val) && !addr_p))
		    {
		      c_parser_error (parser, "invalid _Literal");
		      החזר expr;
		    }
		  אם (addr_p)
		    {
		      val = build1 (ADDR_EXPR, type, val);
		      אם (!is_gimple_invariant_address (val))
			{
			  c_parser_error (parser, "invalid _Literal");
			  החזר expr;
			}
		    }
		  אם (neg_p)
		    {
		      val = const_unop (NEGATE_EXPR, TREE_TYPE (val), val);
		      אם (! val)
			{
			  c_parser_error (parser, "invalid _Literal");
			  החזר expr;
			}
		    }
		  expr.value = fold_convert (type, val);
		}
	      החזר expr;
	    }

	  /* SSA name.  */
	  unsigned version, ver_offset;
	  אם (! lookup_name (id)
	      && c_parser_parse_ssa_name_id (id, &version, &ver_offset))
	    {
	      c_parser_consume_token (parser);
	      expr.value = c_parser_parse_ssa_name (parser, id, NULL_TREE,
						    version, ver_offset);
	      אם (expr.value == error_mark_node)
		החזר expr;
	      set_c_expr_source_range (&expr, tok_range);
	      /* For default definition SSA names.  */
	      אם (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
		  && c_parser_peek_2nd_token (parser)->type == CPP_NAME
		  && strcmp ("D",
			     IDENTIFIER_POINTER
			       (c_parser_peek_2nd_token (parser)->value)) == 0
		  && c_parser_peek_nth_token (parser, 3)->type == CPP_CLOSE_PAREN)
		{
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		  אם (! SSA_NAME_IS_DEFAULT_DEF (expr.value))
		    {
		      אם (!SSA_NAME_VAR (expr.value))
			{
			  error_at (loc, "anonymous SSA name cannot have"
				    " default definition");
			  expr.value = error_mark_node;
			  החזר expr;
			}
		      set_ssa_default_def (cfun, SSA_NAME_VAR (expr.value),
					   expr.value);
		      SSA_NAME_DEF_STMT (expr.value) = gimple_build_nop ();
		    }
		}
	    }
	  אחרת
	    {
	      c_parser_consume_token (parser);
	      expr.value
		= build_external_ref (loc, id,
				      (c_parser_peek_token (parser)->type
				       == CPP_OPEN_PAREN), &expr.original_type);
	      set_c_expr_source_range (&expr, tok_range);
	    }
	  اكسر;
	}
      /* Fallthru.  */
    افتراضي:
      c_parser_error (parser, "expected expression");
      expr.set_error ();
      اكسر;
    }
  אם (expr.value == error_mark_node)
    החזר expr;
  החזר c_parser_gimple_postfix_expression_after_primary
    (parser, EXPR_LOC_OR_LOC (expr.value, loc), expr);
}

/* Parse a gimple postfix expression after the initial primary or compound
   literal.  */

ساكن بنية c_expr
c_parser_gimple_postfix_expression_after_primary (gimple_parser &parser,
						  location_t expr_loc,
						  بنية c_expr expr)
{
  location_t start;
  location_t finish;
  tree ident;
  location_t comp_loc;

  כלעוד (אמת)
    {
      location_t op_loc = c_parser_peek_token (parser)->location;
      بدل (c_parser_peek_token (parser)->type)
	{
	حالة CPP_OPEN_SQUARE:
	  {
	    c_parser_consume_token (parser);
	    tree idx = c_parser_gimple_unary_expression (parser).value;

	    אם (! c_parser_require (parser, CPP_CLOSE_SQUARE, "expected %<]%>"))
	      {
		c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE, عدم);
		اكسر;
	      }

	    start = expr.get_start ();
	    finish = c_parser_tokens_buf (parser, 0)->location;
	    expr.value = build_array_ref (op_loc, expr.value, idx);
	    set_c_expr_source_range (&expr, start, finish);
	    expr.m_decimal = 0;

	    expr.original_code = ERROR_MARK;
	    expr.original_type = عدم;
	    اكسر;
	  }
	حالة CPP_OPEN_PAREN:
	  {
	    /* Function call.  */
	    c_parser_consume_token (parser);
	    auto_vec<tree> exprlist;
	    אם (! c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	      c_parser_gimple_expr_list (parser, &exprlist);
	    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    אם (!FUNC_OR_METHOD_TYPE_P (TREE_TYPE (expr.value)))
	      {
		c_parser_error (parser, "invalid call to non-function");
		expr.set_error ();
		اكسر;
	      }
	    expr.value = build_call_array_loc
		(expr_loc, TREE_TYPE (TREE_TYPE (expr.value)),
		 expr.value, exprlist.length (), exprlist.address ());
	    expr.m_decimal = 0;
	    expr.original_code = ERROR_MARK;
	    expr.original_type = عدم;
	    اكسر;
	  }
	حالة CPP_DOT:
	  {
	    /* Structure element reference.  */
	    c_parser_consume_token (parser);
	    אם (c_parser_next_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		ident = comp_tok->value;
		comp_loc = comp_tok->location;
	      }
	    אחרת
	      {
		c_parser_error (parser, "expected identifier");
		expr.set_error ();
		expr.original_code = ERROR_MARK;
		expr.original_type = عدم;
		החזר expr;
	      }
	    start = expr.get_start ();
	    finish = c_parser_peek_token (parser)->get_finish ();
	    c_parser_consume_token (parser);
	    expr.value = build_component_ref (op_loc, expr.value, ident,
					      comp_loc, UNKNOWN_LOCATION);
	    set_c_expr_source_range (&expr, start, finish);
	    expr.m_decimal = 0;
	    expr.original_code = ERROR_MARK;
	    אם (TREE_CODE (expr.value) != COMPONENT_REF)
	      expr.original_type = عدم;
	    אחרת
	      {
		/* Remember the original type of a bitfield.  */
		tree field = TREE_OPERAND (expr.value, 1);
		אם (TREE_CODE (field) != FIELD_DECL)
		  expr.original_type = عدم;
		אחרת
		  expr.original_type = DECL_BIT_FIELD_TYPE (field);
	      }
	    اكسر;
	  }
	حالة CPP_DEREF:
	  {
	    /* Structure element reference.  */
	    אם (!POINTER_TYPE_P (TREE_TYPE (expr.value)))
	      {
		c_parser_error (parser, "dereference of non-pointer");
		expr.set_error ();
		expr.original_code = ERROR_MARK;
		expr.original_type = عدم;
		החזר expr;
	      }
	    c_parser_consume_token (parser);
	    אם (c_parser_next_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		ident = comp_tok->value;
		comp_loc = comp_tok->location;
	      }
	    אחרת
	      {
		c_parser_error (parser, "expected identifier");
		expr.set_error ();
		expr.original_code = ERROR_MARK;
		expr.original_type = عدم;
		החזר expr;
	      }
	    start = expr.get_start ();
	    finish = c_parser_peek_token (parser)->get_finish ();
	    c_parser_consume_token (parser);
	    expr.value = build_component_ref (op_loc,
					      build_simple_mem_ref_loc
					        (op_loc, expr.value),
					      ident, comp_loc,
					      expr.get_location ());
	    set_c_expr_source_range (&expr, start, finish);
	    expr.m_decimal = 0;
	    expr.original_code = ERROR_MARK;
	    אם (TREE_CODE (expr.value) != COMPONENT_REF)
	      expr.original_type = عدم;
	    אחרת
	      {
		/* Remember the original type of a bitfield.  */
		tree field = TREE_OPERAND (expr.value, 1);
		אם (TREE_CODE (field) != FIELD_DECL)
		  expr.original_type = عدم;
		אחרת
		  expr.original_type = DECL_BIT_FIELD_TYPE (field);
	      }
	    اكسر;
	  }
	افتراضي:
	  החזר expr;
	}
    }
}

/* Parse expression list.

   gimple-expr-list:
     gimple-unary-expression
     gimple-expr-list , gimple-unary-expression

 */

ساكن فراغ
c_parser_gimple_expr_list (gimple_parser &parser, vec<tree> *ret)
{
  بنية c_expr expr;

  expr = c_parser_gimple_unary_expression (parser);
  ret->safe_push (expr.value);
  כלעוד (c_parser_next_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      expr = c_parser_gimple_unary_expression (parser);
      ret->safe_push (expr.value);
    }
}

/* Parse gimple label.

   gimple-label:
     identifier :
     case constant-expression :
     default :

*/

ساكن فراغ
c_parser_gimple_label (gimple_parser &parser, gimple_seq *seq)
{
  tree name = c_parser_peek_token (parser)->value;
  location_t loc1 = c_parser_peek_token (parser)->location;
  gcc_assert (c_parser_next_token_is (parser, CPP_NAME));
  c_parser_consume_token (parser);
  gcc_assert (c_parser_next_token_is (parser, CPP_COLON));
  c_parser_consume_token (parser);
  tree label = define_label (loc1, name);
  אם (label)
    gimple_seq_add_stmt_without_update (seq, gimple_build_label (label));
  החזר;
}

/* Parse gimple/RTL pass list.

   gimple-or-rtl-pass-list:
     startwith("pass-name")[,{cfg,ssa}]
 */

فراغ
c_parser_gimple_or_rtl_pass_list (c_parser *parser, c_declspecs *specs)
{
  حرف *pass = عدم;

  /* Accept __GIMPLE/__RTL.  */
  אם (c_parser_next_token_is_not (parser, CPP_OPEN_PAREN))
    החזר;
  c_parser_consume_token (parser);

  specs->entry_bb_count = profile_count::uninitialized ();
  כלעוד (c_parser_next_token_is (parser, CPP_NAME))
    {
      profile_quality quality;
      ثابت حرف *op = IDENTIFIER_POINTER (c_parser_peek_token (parser)->value);
      c_parser_consume_token (parser);
      אם (! strcmp (op, "startwith"))
	{
	  אם (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    החזר;
	  אם (c_parser_next_token_is_not (parser, CPP_STRING))
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"expected pass name");
	      החזר;
	    }
	  pass = xstrdup (TREE_STRING_POINTER
			  (c_parser_string_literal (parser, שקר,
						    שקר).value));
	  אם (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<(%>"))
	    החזר;
	}
      אחרת אם (parse_profile_quality (op, &quality))
	{
	  tree q;
	  אם (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    החזר;

	  אם (!c_parser_next_token_is (parser, CPP_NUMBER)
	      || (TREE_CODE (q = c_parser_peek_token (parser)->value)
		  != INTEGER_CST))
	    {
	      c_parser_error (parser, "expected count value");
	      החזר;
	    }

	  specs->entry_bb_count
	    = profile_count::from_gcov_type (TREE_INT_CST_LOW (q), quality);
	  c_parser_consume_token (parser);
	  אם (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    החזר;
	}
      אחרת אם (specs->declspec_il != cdil_gimple)
	/* Allow only one IL specifier and none on RTL.  */
	;
      אחרת אם (! strcmp (op, "cfg"))
	specs->declspec_il = cdil_gimple_cfg;
      אחרת אם (! strcmp (op, "ssa"))
	specs->declspec_il = cdil_gimple_ssa;
      אחרת
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "invalid operation");
	  החזר;
	}
     אם (c_parser_next_token_is (parser, CPP_COMMA))
       c_parser_consume_token (parser);
    }

  אם (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    החזר;

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

ساكن فراغ
c_parser_gimple_declaration (gimple_parser &parser)
{
  بنية c_declarator *declarator;
  بنية c_declspecs *specs = build_null_declspecs ();
  c_parser_declspecs (parser, specs, אמת, אמת, אמת,
		      אמת, אמת, אמת, אמת, cla_nonabstract_decl);
  finish_declspecs (specs);

  /* Provide better error recovery.  Note that a type name here is usually
     better diagnosed as a redeclaration.  */
  אם (c_parser_next_token_starts_declspecs (parser)
      && ! c_parser_next_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<;%>");
      c_parser_set_error (parser, שקר);
      החזר;
    }

  منطقي dummy = שקר;
  declarator = c_parser_declarator (parser,
				    specs->typespec_kind != ctsk_none,
				    C_DTR_NORMAL, &dummy);

  אם (!c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_error (parser, "expected %<;%>");
      החזר;
    }
  אם (declarator)
    {
      /* Handle SSA name decls specially, they do not go into the identifier
         table but we simply build the SSA name for later lookup.  */
      unsigned version, ver_offset;
      /* Handle SSA pointer declarations in a very simplistic ways, we
	 probably would like to call grokdeclarator in a special mode to
	 just build the type of the decl - start_decl already pushes
	 the identifier to the bindings for lookup, something we do not
	 want.  */
      بنية c_declarator *id_declarator = declarator;
      כלעוד (id_declarator->kind == cdk_pointer)
	id_declarator = id_declarator->declarator;
      אם (id_declarator->kind == cdk_id
	  && (declarator->kind == cdk_pointer
	      || is_gimple_reg_type (specs->type))
	  && c_parser_parse_ssa_name_id (id_declarator->u.id.id,
					 &version, &ver_offset)
	  /* The following restricts it to unnamed anonymous SSA names
	     which fails parsing of named ones in dumps (we could
	     decide to not dump their name for -gimple).  */
	  && ver_offset == 0)
	{
	  بنية c_declarator *p = declarator;
	  tree type = specs->type;
	  כלעוד (p->kind == cdk_pointer)
	    {
	      type = build_pointer_type (type);
	      p = p->declarator;
	    }
	  c_parser_parse_ssa_name (parser, id_declarator->u.id.id, type,
				   version, ver_offset);
	}
      אחרת
	{
	  tree postfix_attrs = NULL_TREE;
	  tree all_prefix_attrs = specs->attrs;
	  specs->attrs = عدم;
	  tree decl = start_decl (declarator, specs, שקר,
				  chainon (postfix_attrs, all_prefix_attrs));
	  אם (decl)
	    finish_decl (decl, UNKNOWN_LOCATION, NULL_TREE, NULL_TREE,
			 NULL_TREE);
	}
    }
}

/* Parse gimple goto statement.  */

ساكن فراغ
c_parser_gimple_goto_stmt (gimple_parser &parser,
			   location_t loc, tree label, gimple_seq *seq)
{
  אם (cfun->curr_properties & PROP_cfg)
    {
      صحيح dest_index;
      profile_probability prob;
      אם (c_parser_gimple_parse_bb_spec_edge_probability (label, parser,
							  &dest_index, &prob))
	{
	  parser.push_edge (parser.current_bb->index, dest_index,
			    EDGE_FALLTHRU, prob);
	  החזר;
	}
    }
  tree decl = lookup_label_for_goto (loc, label);
  gimple_seq_add_stmt_without_update (seq, gimple_build_goto (decl));
}

/* Parse a parenthesized condition.
   gimple-condition:
     ( gimple-binary-expression )    */

ساكن tree
c_parser_gimple_paren_condition (gimple_parser &parser)
{
  אם (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    החזר error_mark_node;
  tree cond
    = c_parser_gimple_binary_expression (parser, boolean_type_node).value;
  אם (cond != error_mark_node
      && ! COMPARISON_CLASS_P (cond)
      && ! CONSTANT_CLASS_P (cond)
      && ! SSA_VAR_P (cond))
    {
      c_parser_error (parser, "comparison required");
      cond = error_mark_node;
    }
  אם (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    החזר error_mark_node;
  החזר cond;
}

/* Parse gimple try statement.

   try-statement:
     try { ... } finally { ... }
     try { ... } finally { ... } else { ... }

   This could support try/catch as well, but it's not implemented yet.
 */

ساكن فراغ
c_parser_gimple_try_stmt (gimple_parser &parser, gimple_seq *seq)
{
  gimple_seq tryseq = عدم;
  c_parser_consume_token (parser);
  c_parser_gimple_compound_statement (parser, &tryseq);

  אם ((c_parser_next_token_is (parser, CPP_KEYWORD)
       && c_parser_peek_token (parser)->keyword == RID_AT_FINALLY)
      || (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_token (parser)->id_kind == C_ID_ID
	  && strcmp (IDENTIFIER_POINTER (c_parser_peek_token (parser)->value),
		     "finally") == 0))
    {
      gimple_seq finseq = عدم;
      c_parser_consume_token (parser);
      c_parser_gimple_compound_statement (parser, &finseq);

      אם (c_parser_next_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_ELSE)
	{
	  gimple_seq elsseq = عدم;
	  c_parser_consume_token (parser);
	  c_parser_gimple_compound_statement (parser, &elsseq);

	  geh_else *stmt = gimple_build_eh_else (finseq, elsseq);
	  finseq = عدم;
	  gimple_seq_add_stmt_without_update (&finseq, stmt);
	}

      gtry *stmt = gimple_build_try (tryseq, finseq, GIMPLE_TRY_FINALLY);
      gimple_seq_add_stmt_without_update (seq, stmt);
    }
  אחרת אם (c_parser_next_token_is (parser, CPP_KEYWORD)
      && c_parser_peek_token (parser)->keyword == RID_AT_CATCH)
    c_parser_error (parser, "%<catch%> is not supported");
  אחרת
    c_parser_error (parser, "expected %<finally%> or %<catch%>");
}

/* Parse gimple if-else statement.

   if-statement:
     if ( gimple-binary-expression ) gimple-goto-statement
     if ( gimple-binary-expression ) gimple-goto-statement \
					else gimple-goto-statement
 */

ساكن فراغ
c_parser_gimple_if_stmt (gimple_parser &parser, gimple_seq *seq)
{
  tree t_label = NULL_TREE, f_label = NULL_TREE, label;
  location_t loc;
  c_parser_consume_token (parser);
  tree cond = c_parser_gimple_paren_condition (parser);

  אם (c_parser_next_token_is_keyword (parser, RID_GOTO))
    {
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      אם (! c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected label");
	  החזר;
	}
      label = c_parser_peek_token (parser)->value;
      c_parser_consume_token (parser);
      صحيح dest_index;
      profile_probability prob;
      אם ((cfun->curr_properties & PROP_cfg)
	  && c_parser_gimple_parse_bb_spec_edge_probability (label, parser,
							     &dest_index, &prob))
	parser.push_edge (parser.current_bb->index, dest_index,
			  EDGE_TRUE_VALUE, prob);
      אחרת
	t_label = lookup_label_for_goto (loc, label);
      אם (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	החזר;
    }
  אחרת
    {
      c_parser_error (parser, "expected goto expression");
      החזר;
    }

  אם (c_parser_next_token_is_keyword (parser, RID_ELSE))
    c_parser_consume_token (parser);
  אחרת
    {
      c_parser_error (parser, "expected else statement");
      החזר;
    }

  אם (c_parser_next_token_is_keyword (parser, RID_GOTO))
    {
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      אם (! c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected label");
	  החזר;
	}
      label = c_parser_peek_token (parser)->value;
      c_parser_consume_token (parser);
      صحيح dest_index;
      profile_probability prob;
      אם ((cfun->curr_properties & PROP_cfg)
	  && c_parser_gimple_parse_bb_spec_edge_probability (label, parser,
							     &dest_index, &prob))
	parser.push_edge (parser.current_bb->index, dest_index,
			  EDGE_FALSE_VALUE, prob);
      אחרת
	f_label = lookup_label_for_goto (loc, label);
      אם (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	החזר;
    }
  אחרת
    {
      c_parser_error (parser, "expected goto expression");
      החזר;
    }

  אם (cond != error_mark_node)
    gimple_seq_add_stmt_without_update (seq, gimple_build_cond_from_tree (cond, t_label,
							   f_label));
}

/* Parse gimple switch-statement.

   gimple-switch-statement:
     switch (gimple-postfix-expression) gimple-case-statement

   gimple-case-statement:
     gimple-case-statement
     gimple-label-statement : gimple-goto-statement
*/

ساكن فراغ
c_parser_gimple_switch_stmt (gimple_parser &parser, gimple_seq *seq)
{
  c_expr cond_expr;
  tree case_label, label;
  auto_vec<tree> labels;
  tree default_label = NULL_TREE;
  c_parser_consume_token (parser);

  אם (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    החזר;
  cond_expr = c_parser_gimple_postfix_expression (parser);
  אם (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    החזר;

  אם (! c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    החזר;

  כלעוד (c_parser_next_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      אם (c_parser_next_token_is (parser, CPP_EOF))
	{
	  c_parser_error (parser, "expected statement");
	  החזר;
	}

      بدل (c_parser_peek_token (parser)->keyword)
	{
	حالة RID_CASE:
	  {
	    c_expr exp1;
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);

	    אם (c_parser_next_token_is (parser, CPP_NAME)
		|| c_parser_peek_token (parser)->type == CPP_NUMBER)
	      exp1 = c_parser_gimple_postfix_expression (parser);
	    אחרת
	      {
		c_parser_error (parser, "expected expression");
		החזר;
	      }

	    אם (c_parser_next_token_is (parser, CPP_COLON))
	      {
		c_parser_consume_token (parser);
		אם (c_parser_next_token_is (parser, CPP_NAME))
		  {
		    label = c_parser_peek_token (parser)->value;
		    c_parser_consume_token (parser);
		    tree decl = lookup_label_for_goto (loc, label);
		    case_label = build_case_label (exp1.value, NULL_TREE,
						   decl);
		    labels.safe_push (case_label);
		    אם (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      החזר;
		  }
		אחרת אם (! c_parser_require (parser, CPP_NAME,
					     "expected label"))
		  החזר;
	      }
	    אחרת אם (! c_parser_require (parser, CPP_SEMICOLON,
					 "expected %<:%>"))
	      החזר;
	    اكسر;
	  }
	حالة RID_DEFAULT:
	  {
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);
	    אם (c_parser_next_token_is (parser, CPP_COLON))
	      {
		c_parser_consume_token (parser);
		אם (c_parser_next_token_is (parser, CPP_NAME))
		  {
		    label = c_parser_peek_token (parser)->value;
		    c_parser_consume_token (parser);
		    tree decl = lookup_label_for_goto (loc, label);
		    default_label = build_case_label (NULL_TREE, NULL_TREE,
						      decl);
		    אם (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      החזר;
		  }
		אחרת אם (! c_parser_require (parser, CPP_NAME,
					     "expected label"))
		  החזר;
	      }
	    אחרת אם (! c_parser_require (parser, CPP_SEMICOLON,
					 "expected %<:%>"))
	      החזר;
	    اكسر;
	  }
	افتراضي:
	  c_parser_error (parser, "expected case label");
	  החזר;
	}

    }
  אם (! c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>"))
    החזר;

  אם (cond_expr.value != error_mark_node)
    {
      gswitch *s = gimple_build_switch (cond_expr.value, default_label, labels);
      gimple_seq_add_stmt_without_update (seq, s);
    }
}

/* Parse gimple return statement.  */

ساكن فراغ
c_parser_gimple_return_stmt (gimple_parser &parser, gimple_seq *seq)
{
  location_t loc = c_parser_peek_token (parser)->location;
  gimple *ret = عدم;
  c_parser_consume_token (parser);
  אם (c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      c_finish_gimple_return (loc, NULL_TREE);
      ret = gimple_build_return (عدم);
      gimple_seq_add_stmt_without_update (seq, ret);
    }
  אחרת
    {
      location_t xloc = c_parser_peek_token (parser)->location;
      c_expr expr = c_parser_gimple_unary_expression (parser);
      אם (expr.value != error_mark_node)
	{
	  c_finish_gimple_return (xloc, expr.value);
	  ret = gimple_build_return (expr.value);
	  gimple_seq_add_stmt_without_update (seq, ret);
	}
    }
}

/* Support function for c_parser_gimple_return_stmt.  */

ساكن فراغ
c_finish_gimple_return (location_t loc, tree retval)
{
  tree valtype = TREE_TYPE (TREE_TYPE (current_function_decl));

  /* Use the expansion point to handle cases such as returning NULL
     in a function returning void.  */
  location_t xloc = expansion_point_location_if_in_system_header (loc);

  אם (TREE_THIS_VOLATILE (current_function_decl))
    warning_at (xloc, 0,
		"function declared %<noreturn%> has a %<return%> statement");

  אם (! retval)
    current_function_returns_null = 1;
  אחרת אם (valtype == 0 || VOID_TYPE_P (valtype))
    {
      current_function_returns_null = 1;
      אם (TREE_CODE (TREE_TYPE (retval)) != VOID_TYPE)
	{
	  error_at
	    (xloc, "%<return%> with a value, in function returning void");
	  inform (DECL_SOURCE_LOCATION (current_function_decl),
		  "declared here");
	}
    }
  אחרת אם (TREE_CODE (valtype) != TREE_CODE (TREE_TYPE (retval)))
    {
      error_at
	(xloc, "invalid conversion in return statement");
      inform (DECL_SOURCE_LOCATION (current_function_decl),
	      "declared here");
    }
  החזר;
}
