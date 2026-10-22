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

صنف gimple_parser
{
عام:
  gimple_parser (c_parser *p) : parser (p), edges(), current_bb(عدم) {}
  /* c_parser is not visible here, use composition and fake inheritance
     via a conversion operator.  */
  operator c_parser *() { أرجع parser; }
  c_parser *parser;

  /* CFG build state.  */
  صنف gimple_parser_edge
  {
  عام:
    صحيح src;
    صحيح dest;
    صحيح flags;
    profile_probability probability;
  };
  auto_vec<gimple_parser_edge> edges;
  basic_block current_bb;

  فراغ ئىتتىرىش_edge (صحيح, صحيح, صحيح, profile_probability);
};

فراغ
gimple_parser::ئىتتىرىش_edge (صحيح src, صحيح dest, صحيح flags,
			  profile_probability prob)
{
  gimple_parser_edge e;
  e.src = src;
  e.dest = dest;
  e.flags = flags;
  e.probability = prob;
  edges.safe_ئىتتىرىش (e);
}


/* Gimple parsing functions.  */
ساكن منطقي c_parser_gimple_compound_statement (gimple_parser &, gimple_seq *);
ساكن فراغ c_parser_gimple_label (gimple_parser &, gimple_seq *);
ساكن فراغ c_parser_gimple_statement (gimple_parser &, gimple_seq *);
ساكن بنية c_ئىپادە c_parser_gimple_ئىككىلىك_expression (gimple_parser &, دەرەخ);
ساكن بنية c_ئىپادە c_parser_gimple_unary_expression (gimple_parser &);
ساكن بنية c_ئىپادە c_parser_gimple_postfix_expression
			(gimple_parser &, دەرەخ = error_mark_تۈگۈن);
ساكن بنية c_ئىپادە c_parser_gimple_postfix_expression_after_primary
			(gimple_parser &, location_t, بنية c_ئىپادە);
ساكن فراغ c_parser_gimple_declaration (gimple_parser &);
ساكن فراغ c_parser_gimple_goto_stmt (gimple_parser &, location_t,
				       دەرەخ, gimple_seq *);
ساكن فراغ c_parser_gimple_try_stmt (gimple_parser &, gimple_seq *);
ساكن فراغ c_parser_gimple_if_stmt (gimple_parser &, gimple_seq *);
ساكن فراغ c_parser_gimple_switch_stmt (gimple_parser &, gimple_seq *);
ساكن فراغ c_parser_gimple_return_stmt (gimple_parser &, gimple_seq *);
ساكن فراغ c_finish_gimple_return (location_t, دەرەخ);
ساكن دەرەخ c_parser_gimple_paren_condition (gimple_parser &);
ساكن فراغ c_parser_gimple_ئىپادە_list (gimple_parser &, vec<دەرەخ> *);


/* Much like parser_build_unary_op, but avoid applying default conversions.  */

ساكن c_ئىپادە
gimple_parser_build_unary_op (location_t loc,
			      تعداد دەرەخ_code code, بنية c_ئىپادە arg)
{
  بنية c_ئىپادە result;

  result.original_code = code;
  result.original_type = عدم;
  result.m_decimal = 0;

  إذا (reject_gcc_builtin (arg.قىممەت))
    {
      result.قىممەت = error_mark_تۈگۈن;
    }
  وإلا
    {
      result.قىممەت = build_unary_op (loc, code, arg.قىممەت, true);

      إذا (دەرەخ_OVERFLOW_P (result.قىممەت) && !دەرەخ_OVERFLOW_P (arg.قىممەت))
	overflow_warning (loc, result.قىممەت, arg.قىممەت);
    }

  /* We are typically called when parsing a prefix token at LOC acting on
     ARG.  Reflect this by updating the source range of the result to
     start at LOC and end at the end of ARG.  */
  set_c_ئىپادە_source_range (&result,
			   loc, arg.get_finish ());

  أرجع result;
}

/* See if VAL is an identifier matching __BB<num> and return <num>
   in *INDEX.  */

ساكن منطقي
c_parser_gimple_parse_bb_spec (دەرەخ val, صحيح *index)
{
  إذا (!startswith (IDENTIFIER_POINTER (val), "__BB"))
    أرجع خطأ;

  ثابت حرف *bb = IDENTIFIER_POINTER (val) + 4;
  إذا (! ISDIGIT (*bb))
    أرجع خطأ;

  حرف *pend;
  errno = 0;
  ثابت unsigned long سان = strtoul (bb, &pend, 10);
  إذا (errno == ERANGE
      || *pend != '\0'
      || سان > INT_MAX)
    أرجع خطأ;

  *index = سان;
  أرجع true;
}

/* See if VAL is an identifier matching __BB<num> and return <num>
   in *INDEX.  Return true if so and parse also FREQUENCY of
   the edge.  */


ساكن منطقي
c_parser_gimple_parse_bb_spec_edge_probability (دەرەخ val,
						gimple_parser &parser,
						صحيح *index,
						profile_probability
						*probability)
{
  منطقي return_p = c_parser_gimple_parse_bb_spec (val, index);
  إذا (return_p)
    {
      *probability = profile_probability::uninitialized ();
      /* Parse frequency if provided.  */
      إذا (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	{
	  دەرەخ f;
	  c_parser_consume_token (parser);
	  إذا (!c_parser_next_token_is (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected frequency quality");
	      أرجع خطأ;
	    }

	  profile_quality quality;
	  ثابت حرف *v
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->قىممەت);
	  إذا (!parse_profile_quality (v, &quality))
	    {
	      c_parser_error (parser, "unknown profile quality");
	      أرجع خطأ;
	    }

	  c_parser_consume_token (parser);
	  إذا (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    أرجع خطأ;

	  إذا (!c_parser_next_token_is (parser, CPP_سان)
	      || (دەرەخ_CODE (f = c_parser_peek_token (parser)->قىممەت)
		  != INTEGER_CST))
	    {
	      c_parser_error (parser, "expected frequency value");
	      أرجع خطأ;
	    }

	  unsigned صحيح قىممەت = دەرەخ_INT_CST_تۆۋەن (f);
	  *probability = profile_probability (قىممەت, quality);

	  c_parser_consume_token (parser);
	  إذا (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    أرجع خطأ;

	  إذا (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    أرجع خطأ;
	}

      أرجع true;
    }

  أرجع خطأ;

}

/* Parse the body of a function declaration marked with "__GIMPLE".  */

فراغ
c_parser_parse_gimple_body (c_parser *cparser, حرف *gimple_pass,
			    تعداد c_declspec_il cdil,
			    profile_سانى entry_bb_سانى)
{
  gimple_parser parser (cparser);
  gimple_seq seq = عدم;
  gimple_seq body = عدم;
  دەرەخ stmt = ئىتتىرىش_stmt_list ();
  ئىتتىرىش_scope ();
  location_t loc1 = c_parser_peek_token (parser)->location;

  cfun->pass_startwith = gimple_pass;
  init_دەرەخ_ssa (cfun);

  إذا (cdil == cdil_gimple)
    /* While we have SSA names in the IL we do not have a CFG built yet
       and PHIs are represented using a PHI internal function.  We do
       have lowered control flow and exception handling (well, we do not
       have parser support for EH yet).  But as we still have BINDs
       we have to go through lowering again.  */
    cfun->curr_properties = PROP_gimple_any;
  وإلا
    {
      /* We have at least cdil_gimple_cfg.  */
      gimple_register_cfg_hooks ();
      init_empty_دەرەخ_cfg ();
      parser.current_bb = ENTRY_BLOCK_PTR_FOR_FN (cfun);
      /* Initialize the bare loop structure - we are going to only
         mark headers and leave the rest to fixup.  */
      set_loops_for_fn (cfun, ggc_cleared_alloc<بنية loops> ());
      init_loops_structure (cfun, loops_for_fn (cfun), 1);
      loops_state_set (cfun, LOOPS_NEED_FIXUP|LOOPS_MAY_HAVE_MULTIPLE_LATCHES);
      cfun->curr_properties
	|= PROP_gimple_lcf | PROP_gimple_leh | PROP_cfg | PROP_loops;
      إذا (cdil == cdil_gimple_ssa)
	{
	  init_ssa_operands (cfun);
	  cfun->curr_properties |= PROP_ssa;
	}
    }

  إذا (! c_parser_gimple_compound_statement (parser, &seq)
      && cdil == cdil_gimple)
    {
      gimple *ret = gimple_build_return (عدم);
      gimple_seq_add_stmt_without_update (&seq, ret);
    }

  دەرەخ block = چىقىرىش_scope ();
  stmt = چىقىرىش_stmt_list (stmt);
  stmt = c_build_bind_ئىپادە (loc1, block, stmt);

  block = DECL_INITIAL (current_function_decl);
  BLOCK_SUBBLOCKS (block) = NULL_دەرەخ;
  BLOCK_CHAIN (block) = NULL_دەرەخ;
  دەرەخ_ASM_WRITTEN (block) = 1;

  إذا (cdil == cdil_gimple)
    {
      gbind *bind_stmt = gimple_build_bind (BIND_ئىپادە_VARS (stmt), عدم,
					    BIND_ئىپادە_BLOCK (stmt));
      gimple_bind_set_body (bind_stmt, seq);
      gimple_seq_add_stmt_without_update (&body, bind_stmt);
      gimple_set_body (current_function_decl, body);
    }
  وإلا
    {
      /* Control-flow and binds are lowered, record local decls.  */
      لكل (دەرەخ var = BIND_ئىپادە_VARS (stmt); var; var = DECL_CHAIN (var))
	إذا (VAR_P (var)
	    && !DECL_EXTERNAL (var))
	  {
	    add_local_decl (cfun, var);
	    /* When the middle-end re-gimplifies any expression we might
	       run into the assertion that we've seen the decl in a BIND.  */
	    إذا (!دەرەخ_STATIC (var))
	      DECL_SEEN_IN_BIND_ئىپادە_P (var) = 1;
	  }
      /* We have a CFG.  Build the edges.  */
      لكل (unsigned i = 0; i < parser.edges.length (); ++i)
	{
	  edge e = make_edge (BASIC_BLOCK_FOR_FN (cfun, parser.edges[i].src),
			      BASIC_BLOCK_FOR_FN (cfun, parser.edges[i].dest),
			      parser.edges[i].flags);
	  e->probability = parser.edges[i].probability;
	}
      /* Add edges for case labels.  */
      basic_block bb;
      FOR_EACH_BB_FN (bb, cfun)
	إذا (EDGE_سانى (bb->succs) == 0)
	  {
	    إذا (gswitch *sw = safe_dyn_cast <gswitch *> (*gsi_last_bb (bb)))
	      لكل (unsigned i = 0; i < gimple_switch_رەقەم_labels (sw); ++i)
		{
		  basic_block label_bb = gimple_switch_label_bb (cfun, sw, i);
		  make_edge (bb, label_bb, 0);
		}
	  }
      /* Need those for loop fixup.  */
      calculate_dominance_info (CDI_DOMINATORS);
      /* With SSA lower PHIs parsed as internal function calls and
	 update stmts.  */
      إذا (cdil == cdil_gimple_ssa)
	{
	  /* Create PHI nodes, they are parsed into __PHI internal calls
	     and update SSA operands.  */
	  FOR_EACH_BB_FN (bb, cfun)
	    {
	      gimple_stmt_iterator gsi;
	      لكل (gsi = gsi_start_bb (bb); !gsi_end_p (gsi);)
		{
		  gimple *stmt = gsi_stmt (gsi);
		  إذا (!gimple_call_internal_p (stmt, IFN_PHI))
		    اكسر;

		  gphi *phi = create_phi_تۈگۈن (gimple_call_lhs (stmt), bb);
		  لكل (unsigned i = 0; i < gimple_call_رەقەم_args (stmt); i += 2)
		    {
		      صحيح srcidx = دەرەخ_INT_CST_تۆۋەن (gimple_call_arg (stmt, i));
		      edge e = find_edge (BASIC_BLOCK_FOR_FN (cfun, srcidx), bb);
		      إذا (!e)
			c_parser_error (parser, "edge not found");
		      وإلا
			add_phi_arg (phi, gimple_call_arg (stmt, i + 1), e,
				     UNKNOWN_LOCATION);
		    }
		  gsi_remove (&gsi, true);
		}
	      لكل (; !gsi_end_p (gsi); gsi_next (&gsi))
		update_stmt (gsi_stmt (gsi));
	    }
	  /* Fill SSA name gaps, putting them on the freelist and diagnose
	     SSA names without definition.  */
	  لكل (unsigned i = 1; i < رەقەم_ssa_names; ++i)
	    إذا (!ssa_name (i))
	      {
		دەرەخ name = make_ssa_name_fn (cfun, integer_type_تۈگۈن, عدم, i);
		release_ssa_name_fn (cfun, name);
	      }
	    وإلا إذا (!SSA_NAME_DEF_STMT (ssa_name (i)))
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

  إذا (cfun->curr_properties & PROP_cfg)
    {
      ENTRY_BLOCK_PTR_FOR_FN (cfun)->سانى = entry_bb_سانى;
      gcov_type t = param_gimple_fe_computed_hot_bb_threshold;
      set_hot_bb_threshold (t);
      update_max_bb_سانى ();
      cgraph_تۈگۈن::get_create (cfun->decl);
      cgraph_edge::rebuild_edges ();
    }

  /* Perform IL validation and if any error is found abort compilation
     of this function by zapping its body.  */
  إذا ((cfun->curr_properties & PROP_cfg)
      && verify_gimple_in_cfg (cfun, خطأ, خطأ))
    init_empty_دەرەخ_cfg ();
  وإلا إذا (!(cfun->curr_properties & PROP_cfg)
	   && verify_gimple_in_seq (gimple_body (current_function_decl), خطأ))
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
  منطقي return_p = خطأ;

  إذا (! c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    أرجع خطأ;

  /* A compound statement starts with optional declarations.  */
  طالما (c_parser_next_tokens_start_declaration (parser))
    {
      c_parser_gimple_declaration (parser);
      إذا (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	أرجع خطأ;
    }

  طالما (c_parser_next_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      إذا (c_parser_error (parser))
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_BRACE, عدم);
	  أرجع return_p;
	}
      وإلا إذا (c_parser_next_token_is (parser, CPP_EOF))
	{
	  c_parser_error (parser, "expected declaration or statement");
	  أرجع return_p;
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
		إذا (c_parser_next_token_is (parser, CPP_NAME))
		  {
		    دەرەخ label = c_parser_peek_token (parser)->قىممەت;
		    c_parser_consume_token (parser);
		    c_parser_gimple_goto_stmt (parser, loc, label, seq);
		    إذا (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      أرجع return_p;
		  }
		}
	      اكسر;
	    حالة RID_RETURN:
	      return_p = true;
	      c_parser_gimple_return_stmt (parser, seq);
	      إذا (! c_parser_require (parser, CPP_SEMICOLON,
				      "expected %<;%>"))
		أرجع return_p;
	      إذا (cfun->curr_properties & PROP_cfg)
		parser.ئىتتىرىش_edge (parser.current_bb->index, EXIT_BLOCK, 0,
				  profile_probability::uninitialized ());
	      اكسر;
	    افتراضي:
	      اذهب ئىپادە_stmt;
	    }
	  اكسر;
	حالة CPP_NAME:
	  إذا (c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_gimple_label (parser, seq);
	      اكسر;
	    }
	  إذا (c_parser_next_token_is (parser, CPP_NAME)
	      && c_parser_peek_token (parser)->id_kind == C_ID_ID
	      && strcmp (IDENTIFIER_POINTER (c_parser_peek_token (parser)->قىممەت),
			 "try") == 0)
	    {
	      c_parser_gimple_try_stmt (parser, seq);
	      اكسر;
	    }
	  /* Basic block specification.
	     __BB (index, ...)  */
	  إذا ((cfun->curr_properties & PROP_cfg)
	      && !strcmp (IDENTIFIER_POINTER
			    (c_parser_peek_token (parser)->قىممەت), "__BB"))
	    {
	      c_parser_consume_token (parser);
	      إذا (! c_parser_require (parser, CPP_OPEN_PAREN,
				      "expected %<(%>"))
		أرجع return_p;
	      إذا (c_parser_next_token_is_not (parser, CPP_سان))
		{
		  c_parser_error (parser, "expected block index");
		  أرجع return_p;
		}
	      دەرەخ tnum = c_parser_peek_token (parser)->قىممەت;
	      إذا (دەرەخ_CODE (tnum) != INTEGER_CST)
		{
		  c_parser_error (parser, "expected block index");
		  أرجع return_p;
		}
	      صحيح index = دەرەخ_INT_CST_تۆۋەن (tnum);
	      إذا (index < رەقەم_FIXED_BLOCKS
		  || (index < last_basic_block_for_fn (cfun)
		      && BASIC_BLOCK_FOR_FN (cfun, index) != عدم))
		{
		  c_parser_error (parser, "invalid block index");
		  أرجع return_p;
		}
	      صحيح is_loop_header_of = -1;
	      profile_سانى bb_سانى = profile_سانى::uninitialized ();
	      c_parser_consume_token (parser);
	      طالما (c_parser_next_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  إذا (! c_parser_next_token_is (parser, CPP_NAME))
		    {
		      c_parser_error (parser, "expected block specifier");
		      أرجع return_p;
		    }
		  /* loop_header (NUM)  */
		  إذا (!strcmp (IDENTIFIER_POINTER
			         (c_parser_peek_token (parser)->قىممەت),
			       "loop_header"))
		    {
		      c_parser_consume_token (parser);
		      إذا (! c_parser_require (parser, CPP_OPEN_PAREN,
					      "expected %<(%>"))
			أرجع return_p;
		      دەرەخ loop_رەقەم;
		      إذا (! c_parser_next_token_is (parser, CPP_سان)
			  || دەرەخ_CODE (loop_رەقەم
					  = c_parser_peek_token (parser)->قىممەت)
			       != INTEGER_CST)
			{
			  c_parser_error (parser, "expected loop number");
			  أرجع return_p;
			}
		      c_parser_consume_token (parser);
		      is_loop_header_of = دەرەخ_INT_CST_تۆۋەن (loop_رەقەم);
		      إذا (! c_parser_require (parser, CPP_CLOSE_PAREN,
					      "expected %<)%>"))
			أرجع return_p;
		    }
		  /* Parse profile: quality(value) */
		  وإلا
		    {
		      دەرەخ q;
		      profile_quality quality;
		      دەرەخ v = c_parser_peek_token (parser)->قىممەت;
		      إذا (!parse_profile_quality (IDENTIFIER_POINTER (v),
						  &quality))
			{
			  c_parser_error (parser, "unknown block specifier");
			  أرجع خطأ;
			}

		      c_parser_consume_token (parser);
		      إذا (!c_parser_require (parser, CPP_OPEN_PAREN,
					     "expected %<(%>"))
			أرجع خطأ;

		      إذا (!c_parser_next_token_is (parser, CPP_سان)
			  || (دەرەخ_CODE (q = c_parser_peek_token (parser)->قىممەت)
			      != INTEGER_CST))
			{
			  c_parser_error (parser, "expected count value");
			  أرجع خطأ;
			}

		      bb_سانى
			= profile_سانى::from_gcov_type (دەرەخ_INT_CST_تۆۋەن (q),
							 quality);
		      c_parser_consume_token (parser);
		      إذا (! c_parser_require (parser, CPP_CLOSE_PAREN,
					      "expected %<)%>"))
			أرجع return_p;
		    }
		}
	      إذا (! c_parser_require (parser, CPP_CLOSE_PAREN,
				      "expected %<)%>")
		  || ! c_parser_require (parser, CPP_COLON,
					 "expected %<:%>"))
		أرجع return_p;

	      /* Put stmts parsed in the current block.  */
	      إذا (!gimple_seq_empty_p (*seq))
		{
		  إذا (!parser.current_bb)
		    c_parser_error (parser, "stmts without block");
		  وإلا
		    {
		      gimple_stmt_iterator gsi
			= gsi_start_bb (parser.current_bb);
		      gsi_قىستۇرۇش_seq_after_without_update (&gsi, *seq,
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
	      إذا (basic_block_info_for_fn (cfun)->length () <= (size_t)index)
		vec_safe_grow_cleared (basic_block_info_for_fn (cfun),
				       index + 1, true);
	      SET_BASIC_BLOCK_FOR_FN (cfun, index, bb);
	      إذا (last_basic_block_for_fn (cfun) <= index)
		last_basic_block_for_fn (cfun) = index + 1;
	      n_basic_blocks_for_fn (cfun)++;
	      إذا (parser.current_bb->index == ENTRY_BLOCK)
		parser.ئىتتىرىش_edge (ENTRY_BLOCK, bb->index, EDGE_FALLTHRU,
				  profile_probability::always ());

	      /* We leave the proper setting to fixup.  */
	      صنف loop *loop_father = loops_for_fn (cfun)->دەرەخ_يىلتىز;
	      /* If the new block is a loop header, allocate a loop
		 struct.  Fixup will take care of proper placement within
		 the loop tree.  */
	      إذا (is_loop_header_of != -1)
		{
		  إذا (سان_of_loops (cfun) > (unsigned)is_loop_header_of
		      && get_loop (cfun, is_loop_header_of) != عدم)
		    {
		      c_parser_error (parser, "duplicate loop header");
		    }
		  وإلا
		    {
		      صنف loop *loop = alloc_loop ();
		      loop->رەقەم = is_loop_header_of;
		      loop->header = bb;
		      إذا (سان_of_loops (cfun) <= (unsigned)is_loop_header_of)
			vec_safe_grow_cleared (loops_for_fn (cfun)->larray,
					       is_loop_header_of + 1, true);
		      (*loops_for_fn (cfun)->larray)[is_loop_header_of] = loop;
		      flow_loop_دەرەخ_تۈگۈن_add (loops_for_fn (cfun)->دەرەخ_يىلتىز,
					       loop);
		    }
		  loop_father = get_loop (cfun, is_loop_header_of);
		}
	      bb->loop_father = loop_father;
	      bb->سانى = bb_سانى;

	      /* Stmts now go to the new block.  */
	      parser.current_bb = bb;
	      اكسر;
	    }
	  اذهب ئىپادە_stmt;

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
ئىپادە_stmt:
	  c_parser_gimple_statement (parser, seq);
	  إذا (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	    c_parser_skip_until_found (parser, CPP_SEMICOLON, عدم);
	}
    }
  c_parser_consume_token (parser);

  /* Put stmts parsed in the current block.  */
  إذا ((cfun->curr_properties & PROP_cfg)
      && !gimple_seq_empty_p (*seq))
    {
      إذا (!parser.current_bb)
	c_parser_error (parser, "stmts without block");
      وإلا
	{
	  gimple_stmt_iterator gsi = gsi_start_bb (parser.current_bb);
	  gsi_قىستۇرۇش_seq_after_without_update (&gsi, *seq,
					       GSI_CONTINUE_LINKING);
	}
      *seq = عدم;
    }

  أرجع return_p;
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
  بنية c_ئىپادە lhs, rhs;
  gimple *assign = عدم;
  location_t loc;
  دەرەخ arg = NULL_دەرەخ;
  auto_vec<دەرەخ> vargs;

  lhs = c_parser_gimple_unary_expression (parser);
  loc = ئىپادە_LOCATION (lhs.قىممەت);
  rhs.set_error ();

  /* GIMPLE call statement without LHS.  */
  إذا (c_parser_next_token_is (parser, CPP_SEMICOLON)
      && دەرەخ_CODE (lhs.قىممەت) == CALL_ئىپادە)
    {
      gimple *call;
      call = gimple_build_call_from_دەرەخ (lhs.قىممەت, عدم);
      gimple_seq_add_stmt_without_update (seq, call);
      gimple_set_location (call, loc);
      أرجع;
    }

  /* All following cases are statements with LHS.  */
  إذا (! c_parser_require (parser, CPP_EQ, "expected %<=%>"))
    أرجع;

  /* Eat and ignore {v} right after the =, the has_volatile_ops is
     redundant and re-computed by the operand scanner.  */
  إذا (c_parser_next_token_is (parser, CPP_OPEN_BRACE)
      && !(c_parser_peek_token (parser)->flags & PREV_WHITE)
      && c_parser_peek_2nd_token (parser)->type == CPP_NAME
      && !(c_parser_peek_2nd_token (parser)->flags & PREV_WHITE)
      && strcmp ("v", IDENTIFIER_POINTER
			(c_parser_peek_2nd_token (parser)->قىممەت)) == 0
      && c_parser_peek_nth_token (parser, 3)->type == CPP_CLOSE_BRACE
      && !(c_parser_peek_nth_token (parser, 3)->flags & PREV_WHITE))
    {
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }

  /* Cast expression.  */
  إذا (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_typename (c_parser_peek_2nd_token (parser)))
    {
      c_parser_consume_token (parser);
      بنية c_type_name *type_name = c_parser_type_name (parser);
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      إذا (type_name == عدم)
	أرجع;
      /* ???  The actual type used in the cast expression is ignored as
         in GIMPLE it is encoded by the type of the LHS.  */
      rhs = c_parser_gimple_postfix_expression (parser);
      إذا (lhs.قىممەت != error_mark_تۈگۈن
	  && rhs.قىممەت != error_mark_تۈگۈن)
	{
	  تعداد دەرەخ_code code = NOP_ئىپادە;
	  إذا (FLOAT_TYPE_P (دەرەخ_TYPE (lhs.قىممەت))
	      && ! FLOAT_TYPE_P (دەرەخ_TYPE (rhs.قىممەت)))
	    code = FLOAT_ئىپادە;
	  وإلا إذا (! FLOAT_TYPE_P (دەرەخ_TYPE (lhs.قىممەت))
		   && FLOAT_TYPE_P (دەرەخ_TYPE (rhs.قىممەت)))
	    code = FIX_TRUNC_ئىپادە;
	  assign = gimple_build_assign (lhs.قىممەت, code, rhs.قىممەت);
	  gimple_seq_add_stmt_without_update (seq, assign);
	  gimple_set_location (assign, loc);
	  أرجع;
	}
    }

  /* Unary expression.  */
  بدل (c_parser_peek_token (parser)->type)
    {
    حالة CPP_NAME:
      {
	دەرەخ id = c_parser_peek_token (parser)->قىممەت;
	إذا (strcmp (IDENTIFIER_POINTER (id), "__ABS") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__ABSU") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__MIN") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__MAX") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__BIT_INSERT") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__VEC_PERM") == 0)
	  اذهب build_unary_ئىپادە;
	اكسر;
      }
    حالة CPP_KEYWORD:
      إذا (c_parser_peek_token (parser)->keyword != RID_REALPART
	  && c_parser_peek_token (parser)->keyword != RID_IMAGPART)
	اكسر;
      /* Fallthru.  */
    حالة CPP_AND:
    حالة CPP_PLUS:
    حالة CPP_MINUS:
    حالة CPP_COMPL:
    حالة CPP_NOT:
    حالة CPP_MULT: /* pointer deref */
    build_unary_ئىپادە:
      rhs = c_parser_gimple_unary_expression (parser);
      إذا (rhs.قىممەت != error_mark_تۈگۈن)
	{
	  assign = gimple_build_assign (lhs.قىممەت, rhs.قىممەت);
	  gimple_set_location (assign, loc);
	  gimple_seq_add_stmt_without_update (seq, assign);
	}
      أرجع;

    افتراضي:;
    }

  /* GIMPLE PHI statement.  */
  إذا (c_parser_next_token_is_keyword (parser, RID_PHI))
    {
      c_parser_consume_token (parser);

      إذا (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	أرجع;

      إذا (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	c_parser_consume_token (parser);

      طالما (c_parser_next_token_is_not (parser, CPP_CLOSE_PAREN))
	{
	  إذا (c_parser_next_token_is (parser, CPP_NAME)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      arg = c_parser_peek_token (parser)->قىممەت;
	      c_parser_consume_token (parser);
	      إذا (c_parser_next_token_is (parser, CPP_COLON))
		c_parser_consume_token (parser);
	      صحيح src_index = -1;
	      إذا (!c_parser_gimple_parse_bb_spec (arg, &src_index))
		c_parser_error (parser, "invalid source block specification");
	      vargs.safe_ئىتتىرىش (size_int (src_index));
	    }
	  وإلا إذا (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  وإلا
	    {
	      arg = c_parser_gimple_unary_expression (parser).قىممەت;
	      vargs.safe_ئىتتىرىش (arg);
	    }
	}

      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");

      /* Build internal function for PHI.  */
      gcall *call_stmt = gimple_build_call_internal_vec (IFN_PHI, vargs);
      gimple_call_set_lhs (call_stmt, lhs.قىممەت);
      gimple_set_location (call_stmt, UNKNOWN_LOCATION);
      gimple_seq_add_stmt_without_update (seq, call_stmt);
      أرجع;
    }

  /* GIMPLE call with lhs.  */
  إذا (c_parser_next_token_is (parser, CPP_DOT)
      || (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN
	  && lookup_name (c_parser_peek_token (parser)->قىممەت)))
    {
      rhs = c_parser_gimple_unary_expression (parser);
      إذا (rhs.قىممەت != error_mark_تۈگۈن)
	{
	  gimple *call = gimple_build_call_from_دەرەخ (rhs.قىممەت, عدم);
	  gimple_call_set_lhs (call, lhs.قىممەت);
	  gimple_seq_add_stmt_without_update (seq, call);
	  gimple_set_location (call, loc);
	}
      أرجع;
    }

  rhs = c_parser_gimple_ئىككىلىك_expression (parser, دەرەخ_TYPE (lhs.قىممەت));
  إذا (lhs.قىممەت != error_mark_تۈگۈن
      && rhs.قىممەت != error_mark_تۈگۈن)
    {
      /* If we parsed an identifier and the next token  is a '?' then parse
	 a conditional expression.  */
      إذا (SSA_VAR_P (rhs.قىممەت) && c_parser_next_token_is (parser, CPP_QUERY))
	{
	  بنية c_ئىپادە trueval, falseval;
	  c_parser_consume_token (parser);
	  trueval = c_parser_gimple_postfix_expression (parser);
	  falseval.set_error ();
	  إذا (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    falseval = c_parser_gimple_postfix_expression (parser);
	  إذا (trueval.قىممەت == error_mark_تۈگۈن
	      || falseval.قىممەت == error_mark_تۈگۈن)
	    أرجع;
	  rhs.قىممەت = build3_loc (loc,
				  VECTOR_TYPE_P (دەرەخ_TYPE (rhs.قىممەت))
				  ? VEC_COND_ئىپادە : COND_ئىپادە,
				  دەرەخ_TYPE (trueval.قىممەت),
				  rhs.قىممەت, trueval.قىممەت, falseval.قىممەت);
	}
      إذا (get_gimple_rhs_class (دەرەخ_CODE (rhs.قىممەت)) == GIMPLE_INVALID_RHS)
	{
	  c_parser_error (parser, "unexpected RHS for assignment");
	  أرجع;
	}
      assign = gimple_build_assign (lhs.قىممەت, rhs.قىممەت);
      gimple_seq_add_stmt_without_update (seq, assign);
      gimple_set_location (assign, loc);
    }
  أرجع;
}

/* A mapping between an identifier to a tree code for binary operations. */
ساكن ثابت std::pair<ثابت حرف *, دەرەخ_code> gimple_ئىككىلىك_identifier_code[] =
  {
    {"__MULT_HIGHPART", MULT_HIGHPART_ئىپادە},
    {"__UNLT", UNLT_ئىپادە},
    {"__UNLE", UNLE_ئىپادە},
    {"__UNGT", UNGT_ئىپادە},
    {"__UNGE", UNGE_ئىپادە},
    {"__UNEQ", UNEQ_ئىپادە},
    {"__UNORDERED", UNORDERED_ئىپادە},
    {"__ORDERED", ORDERED_ئىپادە},
    {"__LTGT", LTGT_ئىپادە},
    {"__FLOOR_DIV", FLOOR_DIV_ئىپادە},
    {"__ROUND_DIV", ROUND_DIV_ئىپادە},
    {"__EXACT_DIV", EXACT_DIV_ئىپادە},
    {"__CEIL_DIV", CEIL_DIV_ئىپادە},
    {"__FLOOR_MOD", FLOOR_MOD_ئىپادە},
    {"__ROUND_MOD", ROUND_MOD_ئىپادە},
    {"__CEIL_MOD", CEIL_MOD_ئىپادە},
    {"__ROTATE_LEFT", LROTATE_ئىپادە},
    {"__ROTATE_RIGHT", RROTATE_ئىپادە},
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

ساكن c_ئىپادە
c_parser_gimple_ئىككىلىك_expression (gimple_parser &parser, دەرەخ ret_type)
{
  /* Location of the binary operator.  */
  بنية c_ئىپادە ret, lhs, rhs;
  تعداد دەرەخ_code code = ERROR_MARK;
  ret.set_error ();
  lhs = c_parser_gimple_postfix_expression (parser, ret_type);
  إذا (c_parser_error (parser))
    أرجع ret;
  بدل (c_parser_peek_token (parser)->type)
    {
    حالة CPP_MULT:
      code = MULT_ئىپادە;
      اكسر;
    حالة CPP_DIV:
      code = TRUNC_DIV_ئىپادە;
      اكسر;
    حالة CPP_MOD:
      code = TRUNC_MOD_ئىپادە;
      اكسر;
    حالة CPP_PLUS:
      إذا (POINTER_TYPE_P (دەرەخ_TYPE (lhs.قىممەت)))
	code = POINTER_PLUS_ئىپادە;
      وإلا
	code = PLUS_ئىپادە;
      اكسر;
    حالة CPP_MINUS:
      إذا (POINTER_TYPE_P (دەرەخ_TYPE (lhs.قىممەت)))
	code = POINTER_DIFF_ئىپادە;
      وإلا
	code = MINUS_ئىپادە;
      اكسر;
    حالة CPP_LSHIFT:
      code = LSHIFT_ئىپادە;
      اكسر;
    حالة CPP_RSHIFT:
      code = RSHIFT_ئىپادە;
      اكسر;
    حالة CPP_LESS:
      code = LT_ئىپادە;
      اكسر;
    حالة CPP_GREATER:
      code = GT_ئىپادە;
      اكسر;
    حالة CPP_LESS_EQ:
      code = LE_ئىپادە;
      اكسر;
    حالة CPP_GREATER_EQ:
      code = GE_ئىپادە;
      اكسر;
    حالة CPP_EQ_EQ:
      code = EQ_ئىپادە;
      اكسر;
    حالة CPP_NOT_EQ:
      code = NE_ئىپادە;
      اكسر;
    حالة CPP_AND:
      code = BIT_AND_ئىپادە;
      اكسر;
    حالة CPP_XOR:
      code = BIT_XOR_ئىپادە;
      اكسر;
    حالة CPP_OR:
      code = BIT_IOR_ئىپادە;
      اكسر;
    حالة CPP_AND_AND:
      c_parser_error (parser, "%<&&%> not valid in GIMPLE");
      أرجع ret;
    حالة CPP_OR_OR:
      c_parser_error (parser, "%<||%> not valid in GIMPLE");
      أرجع ret;
    حالة CPP_NAME:
      {
	دەرەخ id = c_parser_peek_token (parser)->قىممەت;
	لكل (auto &p : gimple_ئىككىلىك_identifier_code)
	  {
	    إذا (strcmp (IDENTIFIER_POINTER (id), p.first) == 0)
	      {
		code = p.second;
		اكسر;
	      }
	  }
	إذا (code != ERROR_MARK)
	  اكسر;
      }
      /* Fallthru.  */
    افتراضي:
      /* Not a binary expression.  */
      أرجع lhs;
    }
  location_t ret_loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  rhs = c_parser_gimple_postfix_expression (parser);
  إذا (lhs.قىممەت != error_mark_تۈگۈن && rhs.قىممەت != error_mark_تۈگۈن)
    ret.قىممەت = build2_loc (ret_loc, code, ret_type, lhs.قىممەت, rhs.قىممەت);
  أرجع ret;
}

/* Parse a gimple parentized binary expression.  */

ساكن c_ئىپادە
c_parser_gimple_parentized_ئىككىلىك_expression (gimple_parser &parser,
					      location_t op_loc,
					      دەرەخ_code code)
{
  بنية c_ئىپادە ret;
  ret.set_error ();

  c_parser_consume_token (parser);
  إذا (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    أرجع ret;
  c_ئىپادە op1 = c_parser_gimple_postfix_expression (parser);
  إذا (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    أرجع ret;
  c_ئىپادە op2 = c_parser_gimple_postfix_expression (parser);
  إذا (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    أرجع ret;

  إذا (op1.قىممەت != error_mark_تۈگۈن && op2.قىممەت != error_mark_تۈگۈن)
    ret.قىممەت = build2_loc (op_loc,
			    code, دەرەخ_TYPE (op1.قىممەت), op1.قىممەت, op2.قىممەت);
  أرجع ret;
}

/* Parse a gimple parentized binary expression.  */

ساكن c_ئىپادە
c_parser_gimple_parentized_ternary_expression (gimple_parser &parser,
					       location_t op_loc,
					       دەرەخ_code code)
{
  بنية c_ئىپادە ret;
  ret.set_error ();

  c_parser_consume_token (parser);
  إذا (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    أرجع ret;
  c_ئىپادە op1 = c_parser_gimple_postfix_expression (parser);
  إذا (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    أرجع ret;
  c_ئىپادە op2 = c_parser_gimple_postfix_expression (parser);
  إذا (!c_parser_require (parser, CPP_COMMA, "expected %<)%>"))
    أرجع ret;
  c_ئىپادە op3 = c_parser_gimple_postfix_expression (parser);
  إذا (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    أرجع ret;

  إذا (op1.قىممەت != error_mark_تۈگۈن
      && op2.قىممەت != error_mark_تۈگۈن
      && op3.قىممەت != error_mark_تۈگۈن)
    ret.قىممەت = build3_loc (op_loc,
			    code, دەرەخ_TYPE (op1.قىممەت),
			    op1.قىممەت, op2.قىممەت, op3.قىممەت);
  أرجع ret;
}

/* Parse gimple unary expression.

   gimple-unary-expression:
     gimple-postfix-expression
     unary-operator gimple-postfix-expression

   unary-operator: one of
     & * + - ~ abs_expr
*/

ساكن c_ئىپادە
c_parser_gimple_unary_expression (gimple_parser &parser)
{
  بنية c_ئىپادە ret, op;
  location_t op_loc = c_parser_peek_token (parser)->location;
  location_t finish;
  ret.set_error ();
  بدل (c_parser_peek_token (parser)->type)
    {
    حالة CPP_AND:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      mark_exp_read (op.قىممەت);
      أرجع gimple_parser_build_unary_op (op_loc, ADDR_ئىپادە, op);
    حالة CPP_MULT:
      {
	c_parser_consume_token (parser);
	op = c_parser_gimple_postfix_expression (parser);
	إذا (op.قىممەت == error_mark_تۈگۈن)
	  أرجع ret;
	إذا (! POINTER_TYPE_P (دەرەخ_TYPE (op.قىممەت)))
	  {
	    error_at (op_loc, "expected pointer as argument of unary %<*%>");
	    أرجع ret;
	  }
	finish = op.get_finish ();
	location_t combined_loc = make_location (op_loc, op_loc, finish);
	ret.قىممەت = build_simple_mem_ref_loc (combined_loc, op.قىممەت);
	دەرەخ_SIDE_EFFECTS (ret.قىممەت)
	  = دەرەخ_THIS_VOLATILE (ret.قىممەت)
	  = TYPE_VOLATILE (دەرەخ_TYPE (دەرەخ_TYPE (op.قىممەت)));
	ret.src_range.m_start = op_loc;
	ret.src_range.m_finish = finish;
	أرجع ret;
      }
    حالة CPP_PLUS:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      أرجع gimple_parser_build_unary_op (op_loc, CONVERT_ئىپادە, op);
    حالة CPP_MINUS:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      أرجع gimple_parser_build_unary_op (op_loc, NEGATE_ئىپادە, op);
    حالة CPP_COMPL:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      أرجع gimple_parser_build_unary_op (op_loc, BIT_NOT_ئىپادە, op);
    حالة CPP_NOT:
      c_parser_error (parser, "%<!%> not valid in GIMPLE");
      أرجع ret;
    حالة CPP_KEYWORD:
      بدل (c_parser_peek_token (parser)->keyword)
	{
	حالة RID_REALPART:
	  c_parser_consume_token (parser);
	  op = c_parser_gimple_postfix_expression (parser);
	  أرجع gimple_parser_build_unary_op (op_loc, REALPART_ئىپادە, op);
	حالة RID_IMAGPART:
	  c_parser_consume_token (parser);
	  op = c_parser_gimple_postfix_expression (parser);
	  أرجع gimple_parser_build_unary_op (op_loc, IMAGPART_ئىپادە, op);
	افتراضي:
	  أرجع c_parser_gimple_postfix_expression (parser);
	}
    حالة CPP_NAME:
	{
	  دەرەخ id = c_parser_peek_token (parser)->قىممەت;
	  إذا (strcmp (IDENTIFIER_POINTER (id), "__ABS") == 0)
	    {
	      c_parser_consume_token (parser);
	      op = c_parser_gimple_postfix_expression (parser);
	      أرجع gimple_parser_build_unary_op (op_loc, ABS_ئىپادە, op);
	    }
	  وإلا إذا (strcmp (IDENTIFIER_POINTER (id), "__ABSU") == 0)
	    {
	      c_parser_consume_token (parser);
	      op = c_parser_gimple_postfix_expression (parser);
	      أرجع gimple_parser_build_unary_op (op_loc, ABSU_ئىپادە, op);
	    }
	  وإلا إذا (strcmp (IDENTIFIER_POINTER (id), "__MIN") == 0)
	    أرجع c_parser_gimple_parentized_ئىككىلىك_expression (parser,
								 op_loc,
								 MIN_ئىپادە);
	  وإلا إذا (strcmp (IDENTIFIER_POINTER (id), "__MAX") == 0)
	    أرجع c_parser_gimple_parentized_ئىككىلىك_expression (parser,
								 op_loc,
								 MAX_ئىپادە);
	  وإلا إذا (strcmp (IDENTIFIER_POINTER (id), "__VEC_PERM") == 0)
	    أرجع c_parser_gimple_parentized_ternary_expression
			(parser, op_loc, VEC_PERM_ئىپادە);
	  وإلا إذا (strcmp (IDENTIFIER_POINTER (id), "__BIT_INSERT") == 0)
	    {
	      /* __BIT_INSERT '(' postfix-expression, postfix-expression,
			          integer ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      إذا (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_ئىپادە op0 = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_ئىپادە op1 = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_ئىپادە op2 = c_parser_gimple_postfix_expression (parser);
		  إذا (دەرەخ_CODE (op2.قىممەت) != INTEGER_CST
		      || !int_fits_type_p (op2.قىممەت, bitsizetype))
		    c_parser_error (parser, "expected constant offset");
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  إذا (op0.قىممەت != error_mark_تۈگۈن
		      && op1.قىممەت != error_mark_تۈگۈن
		      && دەرەخ_CODE (op2.قىممەت) == INTEGER_CST)
		    ret.قىممەت = build3_loc (loc, BIT_قىستۇرۇش_ئىپادە,
					    دەرەخ_TYPE (op0.قىممەت),
					    op0.قىممەت, op1.قىممەت,
					    fold_convert (bitsizetype,
							  op2.قىممەت));
		}
	      أرجع ret;
	    }
	  وإلا
	    أرجع c_parser_gimple_postfix_expression (parser);
	}
    افتراضي:
      أرجع c_parser_gimple_postfix_expression (parser);
    }
}

/* Decompose ID into base name (ID until ver_offset) and VERSION.  Return
   true if ID matches a SSA name.  */

ساكن منطقي
c_parser_parse_ssa_name_id (دەرەخ id, unsigned *version, unsigned *ver_offset)
{
  ثابت حرف *token = IDENTIFIER_POINTER (id);
  ثابت حرف *var_version = strrchr (token, '_');
  إذا (! var_version)
    أرجع خطأ;

  *ver_offset = var_version - token;
  لكل (ثابت حرف *p = var_version + 1; *p; ++p)
    إذا (! ISDIGIT (*p))
      أرجع خطأ;
  *version = atoi (var_version + 1);
  أرجع *version > 0;
}

/* Get at the actual SSA name ID with VERSION starting at VER_OFFSET.
   TYPE is the type if the SSA name is being declared.  */

ساكن دەرەخ
c_parser_parse_ssa_name (gimple_parser &parser,
			 دەرەخ id, دەرەخ type, unsigned version,
			 unsigned ver_offset)
{
  دەرەخ name = NULL_دەرەخ;
  ثابت حرف *token = IDENTIFIER_POINTER (id);

  إذا (ver_offset == 0)
    {
      /* Anonymous unnamed SSA name.  */
      إذا (version < رەقەم_ssa_names)
	name = ssa_name (version);
      إذا (! name)
	{
	  إذا (! type)
	    {
	      c_parser_error (parser, "SSA name undeclared");
	      أرجع error_mark_تۈگۈن;
	    }
	  name = make_ssa_name_fn (cfun, type, عدم, version);
	}
    }
  وإلا
    {
      إذا (version < رەقەم_ssa_names)
	name = ssa_name (version);
      إذا (! name)
	{
	  /* Separate var name from version.  */
	  حرف *var_name = XNEWVEC (حرف, ver_offset + 1);
	  memcpy (var_name, token, ver_offset);
	  var_name[ver_offset] = '\0';
	  /* lookup for parent decl.  */
	  id = get_identifier (var_name);
	  دەرەخ parent = lookup_name (id);
	  XDELETEVEC (var_name);
	  إذا (! parent || parent == error_mark_تۈگۈن)
	    {
	      c_parser_error (parser, "base variable or SSA name undeclared");
	      أرجع error_mark_تۈگۈن;
	    }
	  إذا (!(VAR_P (parent)
		|| دەرەخ_CODE (parent) == PARM_DECL
		|| دەرەخ_CODE (parent) == RESULT_DECL))
	    {
	      error ("invalid base %qE for SSA name", parent);
	      أرجع error_mark_تۈگۈن;
	    }
	  name = make_ssa_name_fn (cfun, parent,
				   gimple_build_nop (), version);
	}
    }

  أرجع name;
}

/* Parse a gimple call to an internal function.

   gimple-call-internal:
     . identifier ( gimple-argument-expression-list[opt] )  */

ساكن بنية c_ئىپادە
c_parser_gimple_call_internal (gimple_parser &parser)
{
  بنية c_ئىپادە ئىپادە;
  ئىپادە.set_error ();

  gcc_assert (c_parser_next_token_is (parser, CPP_DOT));
  c_parser_consume_token (parser);
  location_t loc = c_parser_peek_token (parser)->location;
  إذا (!c_parser_next_token_is (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_kind != C_ID_ID)
    {
      c_parser_error (parser, "expecting internal function name");
      أرجع ئىپادە;
    }
  دەرەخ id = c_parser_peek_token (parser)->قىممەت;
  internal_fn ifn = lookup_internal_fn (IDENTIFIER_POINTER (id));
  c_parser_consume_token (parser);
  إذا (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    {
      auto_vec<دەرەخ> exprlist;
      إذا (!c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_gimple_ئىپادە_list (parser, &exprlist);
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      إذا (ifn == IFN_LAST)
	error_at (loc, "unknown internal function %qE", id);
      وإلا
	{
	  ئىپادە.قىممەت = build_call_ئىپادە_internal_loc_array
	    (loc, ifn, void_type_تۈگۈن, exprlist.length (),
	     exprlist.address ());
	  ئىپادە.original_code = ERROR_MARK;
	  ئىپادە.original_type = عدم;
	  ئىپادە.m_decimal = 0;
	}
    }
  أرجع ئىپادە;
}

/* Parse '<' type [',' alignment] '>' and return a type on success
   and NULL_TREE on error.  */

ساكن دەرەخ
c_parser_gimple_typespec (gimple_parser &parser)
{
  بنية c_type_name *type_name = عدم;
  دەرەخ alignment = NULL_دەرەخ;
  إذا (c_parser_require (parser, CPP_LESS, "expected %<<%>"))
    {
      type_name = c_parser_type_name (parser);
      /* Optional alignment.  */
      إذا (c_parser_next_token_is (parser, CPP_COMMA))
	{
	  c_parser_consume_token (parser);
	  alignment
	      = c_parser_gimple_postfix_expression (parser).قىممەت;
	}
      c_parser_skip_until_found (parser,
				 CPP_GREATER, "expected %<>%>");
    }
  إذا (!type_name)
    أرجع NULL_دەرەخ;
  دەرەخ tem;
  دەرەخ type = groktypename (type_name, &tem, عدم);
  إذا (alignment)
    type = build_aligned_type (type, دەرەخ_to_uhwi (alignment));
  أرجع type;
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

ساكن بنية c_ئىپادە
c_parser_gimple_postfix_expression (gimple_parser &parser, دەرەخ ret_type)
{
  location_t loc = c_parser_peek_token (parser)->location;
  source_range tok_range = c_parser_peek_token (parser)->get_range ();
  بنية c_ئىپادە ئىپادە;
  ئىپادە.set_error ();
  بدل (c_parser_peek_token (parser)->type)
    {
    حالة CPP_سان:
      ئىپادە.قىممەت = c_parser_peek_token (parser)->قىممەت;
      set_c_ئىپادە_source_range (&ئىپادە, tok_range);
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      اكسر;
    حالة CPP_CHAR:
    حالة CPP_CHAR16:
    حالة CPP_CHAR32:
    حالة CPP_UTF8CHAR:
    حالة CPP_WCHAR:
      ئىپادە.قىممەت = c_parser_peek_token (parser)->قىممەت;
      set_c_ئىپادە_source_range (&ئىپادە, tok_range);
      c_parser_consume_token (parser);
      اكسر;
    حالة CPP_STRING:
    حالة CPP_STRING16:
    حالة CPP_STRING32:
    حالة CPP_WSTRING:
    حالة CPP_UTF8STRING:
      ئىپادە = c_parser_string_literal (parser, خطأ, true);
      اكسر;
    حالة CPP_DOT:
      ئىپادە = c_parser_gimple_call_internal (parser);
      اكسر;
    حالة CPP_NAME:
      إذا (c_parser_peek_token (parser)->id_kind == C_ID_ID)
	{
	  دەرەخ id = c_parser_peek_token (parser)->قىممەت;
	  إذا (strcmp (IDENTIFIER_POINTER (id), "__MEM") == 0)
	    {
	      /* __MEM '<' type-name [ ',' number ] '>'
	               '(' [ '(' type-name ')' ] unary-expression
			   [ '+' number ]
			   [ ',' number ]
			   [ ',' number ':' number ] ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      دەرەخ type = c_parser_gimple_typespec (parser);
	      بنية c_ئىپادە ptr, alias_off, step, index, index2;
	      ptr.قىممەت = error_mark_تۈگۈن;
	      alias_off.قىممەت = NULL_دەرەخ;
	      step.قىممەت = NULL_دەرەخ;
	      index.قىممەت = NULL_دەرەخ;
	      index2.قىممەت = NULL_دەرەخ;
	      unsigned short clique = 0;
	      unsigned short base = 0;
	      منطقي reverse_order = خطأ;
	      بنية c_ئىپادە ro;
	      إذا (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  دەرەخ alias_type = NULL_دەرەخ;
		  /* Optional alias-type cast.  */
		  إذا (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
		    {
		      c_parser_consume_token (parser);
		      بنية c_type_name *alias_type_name
			= c_parser_type_name (parser);
		      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
						 "expected %<)%>");
		      إذا (alias_type_name)
			{
			  دەرەخ tem;
			  alias_type = groktypename (alias_type_name,
						     &tem, عدم);
			}
		    }
		  ptr = c_parser_gimple_unary_expression (parser);
		  إذا (ptr.قىممەت == error_mark_تۈگۈن
		      || ! POINTER_TYPE_P (دەرەخ_TYPE (ptr.قىممەت)))
		    {
		      إذا (ptr.قىممەت != error_mark_تۈگۈن)
			error_at (ptr.get_start (),
				  "invalid type of %<__MEM%> operand");
		      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
						 "expected %<)%>");
		      أرجع ئىپادە;
		    }
		  إذا (! alias_type)
		    alias_type = دەرەخ_TYPE (ptr.قىممەت);
		  /* Optional constant offset.  */
		  إذا (c_parser_next_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      alias_off = c_parser_gimple_postfix_expression (parser);
		    }
		  إذا (c_parser_next_token_is (parser, CPP_MULT))
		    {
		      std::swap (index, alias_off);
		      c_parser_consume_token (parser);
		      step = c_parser_gimple_postfix_expression (parser);
		    }
		  وإلا إذا (c_parser_next_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      index = c_parser_gimple_postfix_expression (parser);
		      إذا (c_parser_next_token_is (parser, CPP_MULT))
			{
			  c_parser_consume_token (parser);
			  step = c_parser_gimple_postfix_expression (parser);
			}
		      وإلا
			std::swap (index, index2);
		    }
		  وإلا إذا (alias_off.قىممەت
			   && دەرەخ_CODE (alias_off.قىممەت) != INTEGER_CST)
		    std::swap (alias_off, index2);
		  إذا (c_parser_next_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      index2 = c_parser_gimple_postfix_expression (parser);
		    }
		  إذا (alias_off.قىممەت)
		    {
		      إذا (دەرەخ_CODE (alias_off.قىممەت) != INTEGER_CST)
			error_at (alias_off.get_start (),
				  "expected constant offset for %<__MEM%> "
				  "operand");
		      alias_off.قىممەت = fold_convert (alias_type,
						      alias_off.قىممەت);
		    }
		  وإلا
		    alias_off.قىممەت = build_int_cst (alias_type, 0);
		  إذا (step.قىممەت)
		    {
		      إذا (دەرەخ_CODE (step.قىممەت) != INTEGER_CST)
			error_at (step.get_start (),
				  "expected constant step for %<__MEM%> "
				  "operand");
		    }
		  إذا (c_parser_next_token_is (parser, CPP_COMMA))
		    {
		      بنية c_ئىپادە cl, ba;
		      منطقي has_clb = true;
		      c_parser_consume_token (parser);
		      cl = c_parser_gimple_postfix_expression (parser);
		      إذا (!c_parser_next_token_is (parser, CPP_COLON))
			{
			  ro = cl;
			  unsigned HOST_WIDE_INT tmp = 0;
			  إذا (!دەرەخ_fits_uhwi_p (ro.قىممەت)
			      || (tmp = دەرەخ_to_uhwi (ro.قىممەت)) > 1)
			    error_at (ro.get_start (),
				      "invalid reverse order value");
			  reverse_order = tmp;
			  has_clb = خطأ;
			  إذا (c_parser_next_token_is (parser, CPP_COMMA))
			    {
			      c_parser_consume_token (parser);
			      cl = c_parser_gimple_postfix_expression (parser);
		              has_clb = true;
			    }
			}
		      إذا (has_clb
			  && c_parser_require (parser,
					       CPP_COLON, "expected %<:%>"))
			{
			  ba = c_parser_gimple_postfix_expression (parser);
			  إذا (!دەرەخ_fits_uhwi_p (cl.قىممەت)
			      || !دەرەخ_fits_uhwi_p (ba.قىممەت)
			      || compare_دەرەخ_int (cl.قىممەت,
						   (clique = دەرەخ_to_uhwi
								(cl.قىممەت)))
			      || compare_دەرەخ_int (ba.قىممەت,
						   (base = دەرەخ_to_uhwi
								 (ba.قىممەت))))
			    error_at (cl.get_start (),
				      "invalid clique/base pair");
			}
		    }
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      إذا (! type || c_parser_error (parser))
		{
		  c_parser_set_error (parser, خطأ);
		  أرجع ئىپادە;
		}
	      إذا (index.قىممەت || step.قىممەت || index2.قىممەت)
		ئىپادە.قىممەت = build5_loc (loc, TARGET_MEM_REF,
					 type, ptr.قىممەت, alias_off.قىممەت,
					 index.قىممەت, step.قىممەت, index2.قىممەت);
	      وإلا
		ئىپادە.قىممەت = build2_loc (loc, MEM_REF,
					 type, ptr.قىممەت, alias_off.قىممەت);
	      إذا (clique != 0)
		{
		  cfun->last_clique = MAX (cfun->last_clique, clique);
		  MR_DEPENDENCE_CLIQUE (ئىپادە.قىممەت) = clique;
		  MR_DEPENDENCE_BASE (ئىپادە.قىممەت) = base;
		}
	      إذا (reverse_order)
		{
		  إذا (دەرەخ_CODE (ئىپادە.قىممەت) == MEM_REF)
		    REF_REVERSE_STORAGE_ORDER (ئىپادە.قىممەت) = reverse_order;
		  وإلا
		    error_at (ro.get_start (),
			      "target mem ref cannot have reverse order");
		}
	      اكسر;
	    }
	  وإلا إذا (strcmp (IDENTIFIER_POINTER (id), "__VIEW_CONVERT") == 0)
	    {
	      /* __VIEW_CONVERT '<' type-name [ ',' number ] '>'
	                        '(' postfix-expression ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      دەرەخ type = c_parser_gimple_typespec (parser);
	      إذا (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_ئىپادە op = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  إذا (type && op.قىممەت != error_mark_تۈگۈن)
		    ئىپادە.قىممەت = build1_loc (loc, VIEW_CONVERT_ئىپادە,
					     type, op.قىممەت);
		}
	      اكسر;
	    }
	  وإلا إذا (strcmp (IDENTIFIER_POINTER (id), "__BIT_FIELD_REF") == 0)
	    {
	      /* __BIT_FIELD_REF '<' type-name [ ',' number ] '>'
	                        '(' postfix-expression, integer, integer ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      دەرەخ type = c_parser_gimple_typespec (parser);
	      إذا (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_ئىپادە op0 = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_ئىپادە op1 = c_parser_gimple_postfix_expression (parser);
		  إذا (دەرەخ_CODE (op1.قىممەت) != INTEGER_CST
		      || !int_fits_type_p (op1.قىممەت, bitsizetype))
		    c_parser_error (parser, "expected constant size");
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_ئىپادە op2 = c_parser_gimple_postfix_expression (parser);
		  إذا (دەرەخ_CODE (op2.قىممەت) != INTEGER_CST
		      || !int_fits_type_p (op2.قىممەت, bitsizetype))
		    c_parser_error (parser, "expected constant offset");
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  إذا (type
		      && op0.قىممەت != error_mark_تۈگۈن
		      && دەرەخ_CODE (op1.قىممەت) == INTEGER_CST
		      && دەرەخ_CODE (op2.قىممەت) == INTEGER_CST)
		    ئىپادە.قىممەت = build3_loc (loc, BIT_FIELD_REF, type,
					     op0.قىممەت,
					     fold_convert (bitsizetype,
							   op1.قىممەت),
					     fold_convert (bitsizetype,
							   op2.قىممەت));
		}
	      اكسر;
	    }
	  وإلا إذا (strcmp (IDENTIFIER_POINTER (id), "__CLOBBER") == 0)
	    {
	      /* __CLOBBER [ '(' bob | eob | bos | eos ')' ]  */
	      clobber_kind kind = CLOBBER_UNDEF;
	      c_parser_consume_token (parser);
	      إذا (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
		{
		  c_parser_consume_token (parser);
		  auto tok = c_parser_peek_token (parser);
		  إذا (c_parser_require (parser, CPP_NAME,
					"expected clobber kind"))
		    {
		      ثابت حرف *kind_str = IDENTIFIER_POINTER (tok->قىممەت);
		      إذا (strcmp (kind_str, "bos") == 0)
			kind = CLOBBER_STORAGE_BEGIN;
		      وإلا إذا (strcmp (kind_str, "bob") == 0)
			kind = CLOBBER_OBJECT_BEGIN;
		      وإلا إذا (strcmp (kind_str, "eob") == 0)
			kind = CLOBBER_OBJECT_END;
		      وإلا إذا (strcmp (kind_str, "eos") == 0)
			kind = CLOBBER_STORAGE_END;
		      وإلا
			c_parser_error (parser, "expected one of %<bos%>, "
					"%<eos%>, %<bob>, %<eob%>");
		    }
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      /* We infer the (redundant) type from the LHS.  */
	      ئىپادە.قىممەت = build_clobber (ret_type, kind);
	      اكسر;
	    }
	  وإلا إذا (strcmp (IDENTIFIER_POINTER (id), "_Literal") == 0)
	    {
	      /* _Literal '(' type-name ')' ( [ '-' ] constant | constructor ) */
	      c_parser_consume_token (parser);
	      دەرەخ type = NULL_دەرەخ;
	      إذا (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  بنية c_type_name *type_name = c_parser_type_name (parser);
		  دەرەخ tem;
		  إذا (type_name)
		    type = groktypename (type_name, &tem, عدم);
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      إذا (! type)
		{
		  c_parser_error (parser, "invalid _Literal");
		  أرجع ئىپادە;
		}
	      إذا (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
		{
		  c_parser_consume_token (parser);
		  إذا (!AGGREGATE_TYPE_P (type)
		      && !VECTOR_TYPE_P (type))
		    {
		      c_parser_error (parser, "invalid type for _Literal with "
				      "constructor");
		      c_parser_skip_until_found (parser, CPP_CLOSE_BRACE,
						 "expected %<}%>");
		      أرجع ئىپادە;
		    }
		  vec<constructor_elt, va_gc> *v = عدم;
		  منطقي constant_p = true;
		  إذا (VECTOR_TYPE_P (type)
		      && !c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
		    {
		      vec_alloc (v, TYPE_VECTOR_SUBPARTS (type).to_constant ());
		      افعل
			{
			  دەرەخ val
			    = c_parser_gimple_postfix_expression (parser).قىممەت;
			  إذا (! val
			      || val == error_mark_تۈگۈن
			      || (! CONSTANT_CLASS_P (val)
				  && ! SSA_VAR_P (val)))
			    {
			      c_parser_error (parser, "invalid _Literal");
			      أرجع ئىپادە;
			    }
			  CONSTRUCTOR_APPEND_ELT (v, NULL_دەرەخ, val);
			  إذا (! CONSTANT_CLASS_P (val))
			    constant_p = خطأ;
			  إذا (c_parser_next_token_is (parser, CPP_COMMA))
			    c_parser_consume_token (parser);
			  وإلا
			    اكسر;
			}
		      طالما (1);
		    }
		  إذا (c_parser_require (parser, CPP_CLOSE_BRACE,
					"expected %<}%>"))
		    {
		      إذا (v && constant_p)
			ئىپادە.قىممەت = build_vector_from_ctor (type, v);
		      وإلا
			ئىپادە.قىممەت = build_constructor (type, v);
		    }
		  وإلا
		    {
		      c_parser_skip_until_found (parser, CPP_CLOSE_BRACE,
						 "expected %<}%>");
		      أرجع ئىپادە;
		    }
		}
	      وإلا
		{
		  منطقي neg_p, addr_p;
		  إذا ((neg_p = c_parser_next_token_is (parser, CPP_MINUS)))
		    c_parser_consume_token (parser);
		  إذا ((addr_p = c_parser_next_token_is (parser, CPP_AND)))
		    c_parser_consume_token (parser);
		  دەرەخ val = c_parser_gimple_postfix_expression (parser).قىممەت;
		  إذا (! val
		      || val == error_mark_تۈگۈن
		      || (!CONSTANT_CLASS_P (val) && !addr_p))
		    {
		      c_parser_error (parser, "invalid _Literal");
		      أرجع ئىپادە;
		    }
		  إذا (addr_p)
		    {
		      val = build1 (ADDR_ئىپادە, type, val);
		      إذا (!is_gimple_invariant_address (val))
			{
			  c_parser_error (parser, "invalid _Literal");
			  أرجع ئىپادە;
			}
		    }
		  إذا (neg_p)
		    {
		      val = const_unop (NEGATE_ئىپادە, دەرەخ_TYPE (val), val);
		      إذا (! val)
			{
			  c_parser_error (parser, "invalid _Literal");
			  أرجع ئىپادە;
			}
		    }
		  ئىپادە.قىممەت = fold_convert (type, val);
		}
	      أرجع ئىپادە;
	    }

	  /* SSA name.  */
	  unsigned version, ver_offset;
	  إذا (! lookup_name (id)
	      && c_parser_parse_ssa_name_id (id, &version, &ver_offset))
	    {
	      c_parser_consume_token (parser);
	      ئىپادە.قىممەت = c_parser_parse_ssa_name (parser, id, NULL_دەرەخ,
						    version, ver_offset);
	      إذا (ئىپادە.قىممەت == error_mark_تۈگۈن)
		أرجع ئىپادە;
	      set_c_ئىپادە_source_range (&ئىپادە, tok_range);
	      /* For default definition SSA names.  */
	      إذا (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
		  && c_parser_peek_2nd_token (parser)->type == CPP_NAME
		  && strcmp ("D",
			     IDENTIFIER_POINTER
			       (c_parser_peek_2nd_token (parser)->قىممەت)) == 0
		  && c_parser_peek_nth_token (parser, 3)->type == CPP_CLOSE_PAREN)
		{
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		  إذا (! SSA_NAME_IS_DEFAULT_DEF (ئىپادە.قىممەت))
		    {
		      إذا (!SSA_NAME_VAR (ئىپادە.قىممەت))
			{
			  error_at (loc, "anonymous SSA name cannot have"
				    " default definition");
			  ئىپادە.قىممەت = error_mark_تۈگۈن;
			  أرجع ئىپادە;
			}
		      set_ssa_default_def (cfun, SSA_NAME_VAR (ئىپادە.قىممەت),
					   ئىپادە.قىممەت);
		      SSA_NAME_DEF_STMT (ئىپادە.قىممەت) = gimple_build_nop ();
		    }
		}
	    }
	  وإلا
	    {
	      c_parser_consume_token (parser);
	      ئىپادە.قىممەت
		= build_external_ref (loc, id,
				      (c_parser_peek_token (parser)->type
				       == CPP_OPEN_PAREN), &ئىپادە.original_type);
	      set_c_ئىپادە_source_range (&ئىپادە, tok_range);
	    }
	  اكسر;
	}
      /* Fallthru.  */
    افتراضي:
      c_parser_error (parser, "expected expression");
      ئىپادە.set_error ();
      اكسر;
    }
  إذا (ئىپادە.قىممەت == error_mark_تۈگۈن)
    أرجع ئىپادە;
  أرجع c_parser_gimple_postfix_expression_after_primary
    (parser, ئىپادە_LOC_OR_LOC (ئىپادە.قىممەت, loc), ئىپادە);
}

/* Parse a gimple postfix expression after the initial primary or compound
   literal.  */

ساكن بنية c_ئىپادە
c_parser_gimple_postfix_expression_after_primary (gimple_parser &parser,
						  location_t ئىپادە_loc,
						  بنية c_ئىپادە ئىپادە)
{
  location_t start;
  location_t finish;
  دەرەخ ident;
  location_t comp_loc;

  طالما (true)
    {
      location_t op_loc = c_parser_peek_token (parser)->location;
      بدل (c_parser_peek_token (parser)->type)
	{
	حالة CPP_OPEN_SQUARE:
	  {
	    c_parser_consume_token (parser);
	    دەرەخ idx = c_parser_gimple_unary_expression (parser).قىممەت;

	    إذا (! c_parser_require (parser, CPP_CLOSE_SQUARE, "expected %<]%>"))
	      {
		c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE, عدم);
		اكسر;
	      }

	    start = ئىپادە.get_start ();
	    finish = c_parser_tokens_buf (parser, 0)->location;
	    ئىپادە.قىممەت = build_array_ref (op_loc, ئىپادە.قىممەت, idx);
	    set_c_ئىپادە_source_range (&ئىپادە, start, finish);
	    ئىپادە.m_decimal = 0;

	    ئىپادە.original_code = ERROR_MARK;
	    ئىپادە.original_type = عدم;
	    اكسر;
	  }
	حالة CPP_OPEN_PAREN:
	  {
	    /* Function call.  */
	    c_parser_consume_token (parser);
	    auto_vec<دەرەخ> exprlist;
	    إذا (! c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	      c_parser_gimple_ئىپادە_list (parser, &exprlist);
	    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    إذا (!FUNC_OR_METHOD_TYPE_P (دەرەخ_TYPE (ئىپادە.قىممەت)))
	      {
		c_parser_error (parser, "invalid call to non-function");
		ئىپادە.set_error ();
		اكسر;
	      }
	    ئىپادە.قىممەت = build_call_array_loc
		(ئىپادە_loc, دەرەخ_TYPE (دەرەخ_TYPE (ئىپادە.قىممەت)),
		 ئىپادە.قىممەت, exprlist.length (), exprlist.address ());
	    ئىپادە.m_decimal = 0;
	    ئىپادە.original_code = ERROR_MARK;
	    ئىپادە.original_type = عدم;
	    اكسر;
	  }
	حالة CPP_DOT:
	  {
	    /* Structure element reference.  */
	    c_parser_consume_token (parser);
	    إذا (c_parser_next_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		ident = comp_tok->قىممەت;
		comp_loc = comp_tok->location;
	      }
	    وإلا
	      {
		c_parser_error (parser, "expected identifier");
		ئىپادە.set_error ();
		ئىپادە.original_code = ERROR_MARK;
		ئىپادە.original_type = عدم;
		أرجع ئىپادە;
	      }
	    start = ئىپادە.get_start ();
	    finish = c_parser_peek_token (parser)->get_finish ();
	    c_parser_consume_token (parser);
	    ئىپادە.قىممەت = build_component_ref (op_loc, ئىپادە.قىممەت, ident,
					      comp_loc, UNKNOWN_LOCATION);
	    set_c_ئىپادە_source_range (&ئىپادە, start, finish);
	    ئىپادە.m_decimal = 0;
	    ئىپادە.original_code = ERROR_MARK;
	    إذا (دەرەخ_CODE (ئىپادە.قىممەت) != COMPONENT_REF)
	      ئىپادە.original_type = عدم;
	    وإلا
	      {
		/* Remember the original type of a bitfield.  */
		دەرەخ field = دەرەخ_OPERAND (ئىپادە.قىممەت, 1);
		إذا (دەرەخ_CODE (field) != FIELD_DECL)
		  ئىپادە.original_type = عدم;
		وإلا
		  ئىپادە.original_type = DECL_BIT_FIELD_TYPE (field);
	      }
	    اكسر;
	  }
	حالة CPP_DEREF:
	  {
	    /* Structure element reference.  */
	    إذا (!POINTER_TYPE_P (دەرەخ_TYPE (ئىپادە.قىممەت)))
	      {
		c_parser_error (parser, "dereference of non-pointer");
		ئىپادە.set_error ();
		ئىپادە.original_code = ERROR_MARK;
		ئىپادە.original_type = عدم;
		أرجع ئىپادە;
	      }
	    c_parser_consume_token (parser);
	    إذا (c_parser_next_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		ident = comp_tok->قىممەت;
		comp_loc = comp_tok->location;
	      }
	    وإلا
	      {
		c_parser_error (parser, "expected identifier");
		ئىپادە.set_error ();
		ئىپادە.original_code = ERROR_MARK;
		ئىپادە.original_type = عدم;
		أرجع ئىپادە;
	      }
	    start = ئىپادە.get_start ();
	    finish = c_parser_peek_token (parser)->get_finish ();
	    c_parser_consume_token (parser);
	    ئىپادە.قىممەت = build_component_ref (op_loc,
					      build_simple_mem_ref_loc
					        (op_loc, ئىپادە.قىممەت),
					      ident, comp_loc,
					      ئىپادە.get_location ());
	    set_c_ئىپادە_source_range (&ئىپادە, start, finish);
	    ئىپادە.m_decimal = 0;
	    ئىپادە.original_code = ERROR_MARK;
	    إذا (دەرەخ_CODE (ئىپادە.قىممەت) != COMPONENT_REF)
	      ئىپادە.original_type = عدم;
	    وإلا
	      {
		/* Remember the original type of a bitfield.  */
		دەرەخ field = دەرەخ_OPERAND (ئىپادە.قىممەت, 1);
		إذا (دەرەخ_CODE (field) != FIELD_DECL)
		  ئىپادە.original_type = عدم;
		وإلا
		  ئىپادە.original_type = DECL_BIT_FIELD_TYPE (field);
	      }
	    اكسر;
	  }
	افتراضي:
	  أرجع ئىپادە;
	}
    }
}

/* Parse expression list.

   gimple-expr-list:
     gimple-unary-expression
     gimple-expr-list , gimple-unary-expression

 */

ساكن فراغ
c_parser_gimple_ئىپادە_list (gimple_parser &parser, vec<دەرەخ> *ret)
{
  بنية c_ئىپادە ئىپادە;

  ئىپادە = c_parser_gimple_unary_expression (parser);
  ret->safe_ئىتتىرىش (ئىپادە.قىممەت);
  طالما (c_parser_next_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      ئىپادە = c_parser_gimple_unary_expression (parser);
      ret->safe_ئىتتىرىش (ئىپادە.قىممەت);
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
  دەرەخ name = c_parser_peek_token (parser)->قىممەت;
  location_t loc1 = c_parser_peek_token (parser)->location;
  gcc_assert (c_parser_next_token_is (parser, CPP_NAME));
  c_parser_consume_token (parser);
  gcc_assert (c_parser_next_token_is (parser, CPP_COLON));
  c_parser_consume_token (parser);
  دەرەخ label = define_label (loc1, name);
  إذا (label)
    gimple_seq_add_stmt_without_update (seq, gimple_build_label (label));
  أرجع;
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
  إذا (c_parser_next_token_is_not (parser, CPP_OPEN_PAREN))
    أرجع;
  c_parser_consume_token (parser);

  specs->entry_bb_سانى = profile_سانى::uninitialized ();
  طالما (c_parser_next_token_is (parser, CPP_NAME))
    {
      profile_quality quality;
      ثابت حرف *op = IDENTIFIER_POINTER (c_parser_peek_token (parser)->قىممەت);
      c_parser_consume_token (parser);
      إذا (! strcmp (op, "startwith"))
	{
	  إذا (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    أرجع;
	  إذا (c_parser_next_token_is_not (parser, CPP_STRING))
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"expected pass name");
	      أرجع;
	    }
	  pass = xstrdup (دەرەخ_STRING_POINTER
			  (c_parser_string_literal (parser, خطأ,
						    خطأ).قىممەت));
	  إذا (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<(%>"))
	    أرجع;
	}
      وإلا إذا (parse_profile_quality (op, &quality))
	{
	  دەرەخ q;
	  إذا (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    أرجع;

	  إذا (!c_parser_next_token_is (parser, CPP_سان)
	      || (دەرەخ_CODE (q = c_parser_peek_token (parser)->قىممەت)
		  != INTEGER_CST))
	    {
	      c_parser_error (parser, "expected count value");
	      أرجع;
	    }

	  specs->entry_bb_سانى
	    = profile_سانى::from_gcov_type (دەرەخ_INT_CST_تۆۋەن (q), quality);
	  c_parser_consume_token (parser);
	  إذا (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    أرجع;
	}
      وإلا إذا (specs->declspec_il != cdil_gimple)
	/* Allow only one IL specifier and none on RTL.  */
	;
      وإلا إذا (! strcmp (op, "cfg"))
	specs->declspec_il = cdil_gimple_cfg;
      وإلا إذا (! strcmp (op, "ssa"))
	specs->declspec_il = cdil_gimple_ssa;
      وإلا
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "invalid operation");
	  أرجع;
	}
     إذا (c_parser_next_token_is (parser, CPP_COMMA))
       c_parser_consume_token (parser);
    }

  إذا (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    أرجع;

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
  c_parser_declspecs (parser, specs, true, true, true,
		      true, true, true, true, cla_nonabstract_decl);
  finish_declspecs (specs);

  /* Provide better error recovery.  Note that a type name here is usually
     better diagnosed as a redeclaration.  */
  إذا (c_parser_next_token_starts_declspecs (parser)
      && ! c_parser_next_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<;%>");
      c_parser_set_error (parser, خطأ);
      أرجع;
    }

  منطقي dummy = خطأ;
  declarator = c_parser_declarator (parser,
				    specs->typespec_kind != ctsk_none,
				    C_DTR_NORMAL, &dummy);

  إذا (!c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_error (parser, "expected %<;%>");
      أرجع;
    }
  إذا (declarator)
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
      طالما (id_declarator->kind == cdk_pointer)
	id_declarator = id_declarator->declarator;
      إذا (id_declarator->kind == cdk_id
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
	  دەرەخ type = specs->type;
	  طالما (p->kind == cdk_pointer)
	    {
	      type = build_pointer_type (type);
	      p = p->declarator;
	    }
	  c_parser_parse_ssa_name (parser, id_declarator->u.id.id, type,
				   version, ver_offset);
	}
      وإلا
	{
	  دەرەخ postfix_attrs = NULL_دەرەخ;
	  دەرەخ all_prefix_attrs = specs->attrs;
	  specs->attrs = عدم;
	  دەرەخ decl = start_decl (declarator, specs, خطأ,
				  chainon (postfix_attrs, all_prefix_attrs));
	  إذا (decl)
	    finish_decl (decl, UNKNOWN_LOCATION, NULL_دەرەخ, NULL_دەرەخ,
			 NULL_دەرەخ);
	}
    }
}

/* Parse gimple goto statement.  */

ساكن فراغ
c_parser_gimple_goto_stmt (gimple_parser &parser,
			   location_t loc, دەرەخ label, gimple_seq *seq)
{
  إذا (cfun->curr_properties & PROP_cfg)
    {
      صحيح dest_index;
      profile_probability prob;
      إذا (c_parser_gimple_parse_bb_spec_edge_probability (label, parser,
							  &dest_index, &prob))
	{
	  parser.ئىتتىرىش_edge (parser.current_bb->index, dest_index,
			    EDGE_FALLTHRU, prob);
	  أرجع;
	}
    }
  دەرەخ decl = lookup_label_for_goto (loc, label);
  gimple_seq_add_stmt_without_update (seq, gimple_build_goto (decl));
}

/* Parse a parenthesized condition.
   gimple-condition:
     ( gimple-binary-expression )    */

ساكن دەرەخ
c_parser_gimple_paren_condition (gimple_parser &parser)
{
  إذا (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    أرجع error_mark_تۈگۈن;
  دەرەخ cond
    = c_parser_gimple_ئىككىلىك_expression (parser, boolean_type_تۈگۈن).قىممەت;
  إذا (cond != error_mark_تۈگۈن
      && ! COMPARISON_CLASS_P (cond)
      && ! CONSTANT_CLASS_P (cond)
      && ! SSA_VAR_P (cond))
    {
      c_parser_error (parser, "comparison required");
      cond = error_mark_تۈگۈن;
    }
  إذا (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    أرجع error_mark_تۈگۈن;
  أرجع cond;
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

  إذا ((c_parser_next_token_is (parser, CPP_KEYWORD)
       && c_parser_peek_token (parser)->keyword == RID_AT_FINALLY)
      || (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_token (parser)->id_kind == C_ID_ID
	  && strcmp (IDENTIFIER_POINTER (c_parser_peek_token (parser)->قىممەت),
		     "finally") == 0))
    {
      gimple_seq finseq = عدم;
      c_parser_consume_token (parser);
      c_parser_gimple_compound_statement (parser, &finseq);

      إذا (c_parser_next_token_is (parser, CPP_KEYWORD)
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
  وإلا إذا (c_parser_next_token_is (parser, CPP_KEYWORD)
      && c_parser_peek_token (parser)->keyword == RID_AT_CATCH)
    c_parser_error (parser, "%<catch%> is not supported");
  وإلا
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
  دەرەخ t_label = NULL_دەرەخ, f_label = NULL_دەرەخ, label;
  location_t loc;
  c_parser_consume_token (parser);
  دەرەخ cond = c_parser_gimple_paren_condition (parser);

  إذا (c_parser_next_token_is_keyword (parser, RID_GOTO))
    {
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      إذا (! c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected label");
	  أرجع;
	}
      label = c_parser_peek_token (parser)->قىممەت;
      c_parser_consume_token (parser);
      صحيح dest_index;
      profile_probability prob;
      إذا ((cfun->curr_properties & PROP_cfg)
	  && c_parser_gimple_parse_bb_spec_edge_probability (label, parser,
							     &dest_index, &prob))
	parser.ئىتتىرىش_edge (parser.current_bb->index, dest_index,
			  EDGE_TRUE_قىممەت, prob);
      وإلا
	t_label = lookup_label_for_goto (loc, label);
      إذا (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	أرجع;
    }
  وإلا
    {
      c_parser_error (parser, "expected goto expression");
      أرجع;
    }

  إذا (c_parser_next_token_is_keyword (parser, RID_ELSE))
    c_parser_consume_token (parser);
  وإلا
    {
      c_parser_error (parser, "expected else statement");
      أرجع;
    }

  إذا (c_parser_next_token_is_keyword (parser, RID_GOTO))
    {
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      إذا (! c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected label");
	  أرجع;
	}
      label = c_parser_peek_token (parser)->قىممەت;
      c_parser_consume_token (parser);
      صحيح dest_index;
      profile_probability prob;
      إذا ((cfun->curr_properties & PROP_cfg)
	  && c_parser_gimple_parse_bb_spec_edge_probability (label, parser,
							     &dest_index, &prob))
	parser.ئىتتىرىش_edge (parser.current_bb->index, dest_index,
			  EDGE_FALSE_قىممەت, prob);
      وإلا
	f_label = lookup_label_for_goto (loc, label);
      إذا (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	أرجع;
    }
  وإلا
    {
      c_parser_error (parser, "expected goto expression");
      أرجع;
    }

  إذا (cond != error_mark_تۈگۈن)
    gimple_seq_add_stmt_without_update (seq, gimple_build_cond_from_دەرەخ (cond, t_label,
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
  c_ئىپادە cond_ئىپادە;
  دەرەخ case_label, label;
  auto_vec<دەرەخ> labels;
  دەرەخ default_label = NULL_دەرەخ;
  c_parser_consume_token (parser);

  إذا (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    أرجع;
  cond_ئىپادە = c_parser_gimple_postfix_expression (parser);
  إذا (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    أرجع;

  إذا (! c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    أرجع;

  طالما (c_parser_next_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      إذا (c_parser_next_token_is (parser, CPP_EOF))
	{
	  c_parser_error (parser, "expected statement");
	  أرجع;
	}

      بدل (c_parser_peek_token (parser)->keyword)
	{
	حالة RID_CASE:
	  {
	    c_ئىپادە exp1;
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);

	    إذا (c_parser_next_token_is (parser, CPP_NAME)
		|| c_parser_peek_token (parser)->type == CPP_سان)
	      exp1 = c_parser_gimple_postfix_expression (parser);
	    وإلا
	      {
		c_parser_error (parser, "expected expression");
		أرجع;
	      }

	    إذا (c_parser_next_token_is (parser, CPP_COLON))
	      {
		c_parser_consume_token (parser);
		إذا (c_parser_next_token_is (parser, CPP_NAME))
		  {
		    label = c_parser_peek_token (parser)->قىممەت;
		    c_parser_consume_token (parser);
		    دەرەخ decl = lookup_label_for_goto (loc, label);
		    case_label = build_case_label (exp1.قىممەت, NULL_دەرەخ,
						   decl);
		    labels.safe_ئىتتىرىش (case_label);
		    إذا (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      أرجع;
		  }
		وإلا إذا (! c_parser_require (parser, CPP_NAME,
					     "expected label"))
		  أرجع;
	      }
	    وإلا إذا (! c_parser_require (parser, CPP_SEMICOLON,
					 "expected %<:%>"))
	      أرجع;
	    اكسر;
	  }
	حالة RID_DEFAULT:
	  {
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);
	    إذا (c_parser_next_token_is (parser, CPP_COLON))
	      {
		c_parser_consume_token (parser);
		إذا (c_parser_next_token_is (parser, CPP_NAME))
		  {
		    label = c_parser_peek_token (parser)->قىممەت;
		    c_parser_consume_token (parser);
		    دەرەخ decl = lookup_label_for_goto (loc, label);
		    default_label = build_case_label (NULL_دەرەخ, NULL_دەرەخ,
						      decl);
		    إذا (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      أرجع;
		  }
		وإلا إذا (! c_parser_require (parser, CPP_NAME,
					     "expected label"))
		  أرجع;
	      }
	    وإلا إذا (! c_parser_require (parser, CPP_SEMICOLON,
					 "expected %<:%>"))
	      أرجع;
	    اكسر;
	  }
	افتراضي:
	  c_parser_error (parser, "expected case label");
	  أرجع;
	}

    }
  إذا (! c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>"))
    أرجع;

  إذا (cond_ئىپادە.قىممەت != error_mark_تۈگۈن)
    {
      gswitch *s = gimple_build_switch (cond_ئىپادە.قىممەت, default_label, labels);
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
  إذا (c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      c_finish_gimple_return (loc, NULL_دەرەخ);
      ret = gimple_build_return (عدم);
      gimple_seq_add_stmt_without_update (seq, ret);
    }
  وإلا
    {
      location_t xloc = c_parser_peek_token (parser)->location;
      c_ئىپادە ئىپادە = c_parser_gimple_unary_expression (parser);
      إذا (ئىپادە.قىممەت != error_mark_تۈگۈن)
	{
	  c_finish_gimple_return (xloc, ئىپادە.قىممەت);
	  ret = gimple_build_return (ئىپادە.قىممەت);
	  gimple_seq_add_stmt_without_update (seq, ret);
	}
    }
}

/* Support function for c_parser_gimple_return_stmt.  */

ساكن فراغ
c_finish_gimple_return (location_t loc, دەرەخ retval)
{
  دەرەخ valtype = دەرەخ_TYPE (دەرەخ_TYPE (current_function_decl));

  /* Use the expansion point to handle cases such as returning NULL
     in a function returning void.  */
  location_t xloc = expansion_point_location_if_in_system_header (loc);

  إذا (دەرەخ_THIS_VOLATILE (current_function_decl))
    warning_at (xloc, 0,
		"function declared %<noreturn%> has a %<return%> statement");

  إذا (! retval)
    current_function_returns_null = 1;
  وإلا إذا (valtype == 0 || VOID_TYPE_P (valtype))
    {
      current_function_returns_null = 1;
      إذا (دەرەخ_CODE (دەرەخ_TYPE (retval)) != VOID_TYPE)
	{
	  error_at
	    (xloc, "%<return%> with a value, in function returning void");
	  inform (DECL_SOURCE_LOCATION (current_function_decl),
		  "declared here");
	}
    }
  وإلا إذا (دەرەخ_CODE (valtype) != دەرەخ_CODE (دەرەخ_TYPE (retval)))
    {
      error_at
	(xloc, "invalid conversion in return statement");
      inform (DECL_SOURCE_LOCATION (current_function_decl),
	      "declared here");
    }
  أرجع;
}
