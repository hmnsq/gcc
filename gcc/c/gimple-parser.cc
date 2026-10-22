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
  operator c_parser *() { إرجاع parser; }
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

  فراغ ادفع_edge (صحيح, صحيح, صحيح, profile_probability);
};

فراغ
gimple_parser::ادفع_edge (صحيح src, صحيح dest, صحيح flags,
			  profile_probability prob)
{
  gimple_parser_edge e;
  e.src = src;
  e.dest = dest;
  e.flags = flags;
  e.probability = prob;
  edges.safe_ادفع (e);
}


/* Gimple parsing functions.  */
ساكن منطقي c_parser_gimple_compound_statement (gimple_parser &, gimple_seq *);
ساكن فراغ c_parser_gimple_label (gimple_parser &, gimple_seq *);
ساكن فراغ c_parser_gimple_statement (gimple_parser &, gimple_seq *);
ساكن بنية c_تعبير c_parser_gimple_ثنائي_expression (gimple_parser &, شجرة);
ساكن بنية c_تعبير c_parser_gimple_unary_expression (gimple_parser &);
ساكن بنية c_تعبير c_parser_gimple_postfix_expression
			(gimple_parser &, شجرة = error_mark_عقدة);
ساكن بنية c_تعبير c_parser_gimple_postfix_expression_after_primary
			(gimple_parser &, location_t, بنية c_تعبير);
ساكن فراغ c_parser_gimple_declaration (gimple_parser &);
ساكن فراغ c_parser_gimple_goto_stmt (gimple_parser &, location_t,
				       شجرة, gimple_seq *);
ساكن فراغ c_parser_gimple_try_stmt (gimple_parser &, gimple_seq *);
ساكن فراغ c_parser_gimple_if_stmt (gimple_parser &, gimple_seq *);
ساكن فراغ c_parser_gimple_switch_stmt (gimple_parser &, gimple_seq *);
ساكن فراغ c_parser_gimple_return_stmt (gimple_parser &, gimple_seq *);
ساكن فراغ c_finish_gimple_return (location_t, شجرة);
ساكن شجرة c_parser_gimple_paren_condition (gimple_parser &);
ساكن فراغ c_parser_gimple_تعبير_list (gimple_parser &, vec<شجرة> *);


/* Much like parser_build_unary_op, but avoid applying default conversions.  */

ساكن c_تعبير
gimple_parser_build_unary_op (location_t loc,
			      تعداد شجرة_code code, بنية c_تعبير arg)
{
  بنية c_تعبير result;

  result.original_code = code;
  result.original_type = عدم;
  result.m_decimal = 0;

  إذا (reject_gcc_builtin (arg.قيمة))
    {
      result.قيمة = error_mark_عقدة;
    }
  وإلا
    {
      result.قيمة = build_unary_op (loc, code, arg.قيمة, true);

      إذا (شجرة_OVERFLOW_P (result.قيمة) && !شجرة_OVERFLOW_P (arg.قيمة))
	overflow_warning (loc, result.قيمة, arg.قيمة);
    }

  /* We are typically called when parsing a prefix token at LOC acting on
     ARG.  Reflect this by updating the source range of the result to
     start at LOC and end at the end of ARG.  */
  set_c_تعبير_source_range (&result,
			   loc, arg.get_finish ());

  إرجاع result;
}

/* See if VAL is an identifier matching __BB<num> and return <num>
   in *INDEX.  */

ساكن منطقي
c_parser_gimple_parse_bb_spec (شجرة val, صحيح *index)
{
  إذا (!startswith (IDENTIFIER_POINTER (val), "__BB"))
    إرجاع خطأ;

  ثابت حرف *bb = IDENTIFIER_POINTER (val) + 4;
  إذا (! ISDIGIT (*bb))
    إرجاع خطأ;

  حرف *pend;
  errno = 0;
  ثابت unsigned long العدد = strtoul (bb, &pend, 10);
  إذا (errno == ERANGE
      || *pend != '\0'
      || العدد > INT_MAX)
    إرجاع خطأ;

  *index = العدد;
  إرجاع true;
}

/* See if VAL is an identifier matching __BB<num> and return <num>
   in *INDEX.  Return true if so and parse also FREQUENCY of
   the edge.  */


ساكن منطقي
c_parser_gimple_parse_bb_spec_edge_probability (شجرة val,
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
	  شجرة f;
	  c_parser_consume_token (parser);
	  إذا (!c_parser_next_token_is (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected frequency quality");
	      إرجاع خطأ;
	    }

	  profile_quality quality;
	  ثابت حرف *v
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->قيمة);
	  إذا (!parse_profile_quality (v, &quality))
	    {
	      c_parser_error (parser, "unknown profile quality");
	      إرجاع خطأ;
	    }

	  c_parser_consume_token (parser);
	  إذا (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    إرجاع خطأ;

	  إذا (!c_parser_next_token_is (parser, CPP_العدد)
	      || (شجرة_CODE (f = c_parser_peek_token (parser)->قيمة)
		  != INTEGER_CST))
	    {
	      c_parser_error (parser, "expected frequency value");
	      إرجاع خطأ;
	    }

	  unsigned صحيح قيمة = شجرة_INT_CST_أدنى (f);
	  *probability = profile_probability (قيمة, quality);

	  c_parser_consume_token (parser);
	  إذا (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    إرجاع خطأ;

	  إذا (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    إرجاع خطأ;
	}

      إرجاع true;
    }

  إرجاع خطأ;

}

/* Parse the body of a function declaration marked with "__GIMPLE".  */

فراغ
c_parser_parse_gimple_body (c_parser *cparser, حرف *gimple_pass,
			    تعداد c_declspec_il cdil,
			    profile_تعداد entry_bb_تعداد)
{
  gimple_parser parser (cparser);
  gimple_seq seq = عدم;
  gimple_seq body = عدم;
  شجرة stmt = ادفع_stmt_list ();
  ادفع_scope ();
  location_t loc1 = c_parser_peek_token (parser)->location;

  cfun->pass_startwith = gimple_pass;
  init_شجرة_ssa (cfun);

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
      init_empty_شجرة_cfg ();
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

  شجرة block = اسحب_scope ();
  stmt = اسحب_stmt_list (stmt);
  stmt = c_build_bind_تعبير (loc1, block, stmt);

  block = DECL_INITIAL (current_function_decl);
  BLOCK_SUBBLOCKS (block) = NULL_شجرة;
  BLOCK_CHAIN (block) = NULL_شجرة;
  شجرة_ASM_WRITTEN (block) = 1;

  إذا (cdil == cdil_gimple)
    {
      gbind *bind_stmt = gimple_build_bind (BIND_تعبير_VARS (stmt), عدم,
					    BIND_تعبير_BLOCK (stmt));
      gimple_bind_set_body (bind_stmt, seq);
      gimple_seq_add_stmt_without_update (&body, bind_stmt);
      gimple_set_body (current_function_decl, body);
    }
  وإلا
    {
      /* Control-flow and binds are lowered, record local decls.  */
      لكل (شجرة var = BIND_تعبير_VARS (stmt); var; var = DECL_CHAIN (var))
	إذا (VAR_P (var)
	    && !DECL_EXTERNAL (var))
	  {
	    add_local_decl (cfun, var);
	    /* When the middle-end re-gimplifies any expression we might
	       run into the assertion that we've seen the decl in a BIND.  */
	    إذا (!شجرة_STATIC (var))
	      DECL_SEEN_IN_BIND_تعبير_P (var) = 1;
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
	إذا (EDGE_تعداد (bb->succs) == 0)
	  {
	    إذا (gswitch *sw = safe_dyn_cast <gswitch *> (*gsi_last_bb (bb)))
	      لكل (unsigned i = 0; i < gimple_switch_رقم_labels (sw); ++i)
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

		  gphi *phi = create_phi_عقدة (gimple_call_lhs (stmt), bb);
		  لكل (unsigned i = 0; i < gimple_call_رقم_args (stmt); i += 2)
		    {
		      صحيح srcidx = شجرة_INT_CST_أدنى (gimple_call_arg (stmt, i));
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
	  لكل (unsigned i = 1; i < رقم_ssa_names; ++i)
	    إذا (!ssa_name (i))
	      {
		شجرة name = make_ssa_name_fn (cfun, integer_type_عقدة, عدم, i);
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
      ENTRY_BLOCK_PTR_FOR_FN (cfun)->تعداد_2 = entry_bb_تعداد;
      gcov_type t = param_gimple_fe_computed_hot_bb_threshold;
      set_hot_bb_threshold (t);
      update_max_bb_تعداد ();
      cgraph_عقدة::get_create (cfun->decl);
      cgraph_edge::rebuild_edges ();
    }

  /* Perform IL validation and if any error is found abort compilation
     of this function by zapping its body.  */
  إذا ((cfun->curr_properties & PROP_cfg)
      && verify_gimple_in_cfg (cfun, خطأ, خطأ))
    init_empty_شجرة_cfg ();
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
    إرجاع خطأ;

  /* A compound statement starts with optional declarations.  */
  بينما (c_parser_next_tokens_start_declaration (parser))
    {
      c_parser_gimple_declaration (parser);
      إذا (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	إرجاع خطأ;
    }

  بينما (c_parser_next_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      إذا (c_parser_error (parser))
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_BRACE, عدم);
	  إرجاع return_p;
	}
      وإلا إذا (c_parser_next_token_is (parser, CPP_EOF))
	{
	  c_parser_error (parser, "expected declaration or statement");
	  إرجاع return_p;
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
		    شجرة label = c_parser_peek_token (parser)->قيمة;
		    c_parser_consume_token (parser);
		    c_parser_gimple_goto_stmt (parser, loc, label, seq);
		    إذا (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      إرجاع return_p;
		  }
		}
	      اكسر;
	    حالة RID_RETURN:
	      return_p = true;
	      c_parser_gimple_return_stmt (parser, seq);
	      إذا (! c_parser_require (parser, CPP_SEMICOLON,
				      "expected %<;%>"))
		إرجاع return_p;
	      إذا (cfun->curr_properties & PROP_cfg)
		parser.ادفع_edge (parser.current_bb->index, EXIT_BLOCK, 0,
				  profile_probability::uninitialized ());
	      اكسر;
	    افتراضي:
	      اذهب تعبير_stmt;
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
	      && strcmp (IDENTIFIER_POINTER (c_parser_peek_token (parser)->قيمة),
			 "try") == 0)
	    {
	      c_parser_gimple_try_stmt (parser, seq);
	      اكسر;
	    }
	  /* Basic block specification.
	     __BB (index, ...)  */
	  إذا ((cfun->curr_properties & PROP_cfg)
	      && !strcmp (IDENTIFIER_POINTER
			    (c_parser_peek_token (parser)->قيمة), "__BB"))
	    {
	      c_parser_consume_token (parser);
	      إذا (! c_parser_require (parser, CPP_OPEN_PAREN,
				      "expected %<(%>"))
		إرجاع return_p;
	      إذا (c_parser_next_token_is_not (parser, CPP_العدد))
		{
		  c_parser_error (parser, "expected block index");
		  إرجاع return_p;
		}
	      شجرة tnum = c_parser_peek_token (parser)->قيمة;
	      إذا (شجرة_CODE (tnum) != INTEGER_CST)
		{
		  c_parser_error (parser, "expected block index");
		  إرجاع return_p;
		}
	      صحيح index = شجرة_INT_CST_أدنى (tnum);
	      إذا (index < رقم_FIXED_BLOCKS
		  || (index < last_basic_block_for_fn (cfun)
		      && BASIC_BLOCK_FOR_FN (cfun, index) != عدم))
		{
		  c_parser_error (parser, "invalid block index");
		  إرجاع return_p;
		}
	      صحيح is_loop_header_of = -1;
	      profile_تعداد bb_تعداد = profile_تعداد::uninitialized ();
	      c_parser_consume_token (parser);
	      بينما (c_parser_next_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  إذا (! c_parser_next_token_is (parser, CPP_NAME))
		    {
		      c_parser_error (parser, "expected block specifier");
		      إرجاع return_p;
		    }
		  /* loop_header (NUM)  */
		  إذا (!strcmp (IDENTIFIER_POINTER
			         (c_parser_peek_token (parser)->قيمة),
			       "loop_header"))
		    {
		      c_parser_consume_token (parser);
		      إذا (! c_parser_require (parser, CPP_OPEN_PAREN,
					      "expected %<(%>"))
			إرجاع return_p;
		      شجرة loop_رقم;
		      إذا (! c_parser_next_token_is (parser, CPP_العدد)
			  || شجرة_CODE (loop_رقم
					  = c_parser_peek_token (parser)->قيمة)
			       != INTEGER_CST)
			{
			  c_parser_error (parser, "expected loop number");
			  إرجاع return_p;
			}
		      c_parser_consume_token (parser);
		      is_loop_header_of = شجرة_INT_CST_أدنى (loop_رقم);
		      إذا (! c_parser_require (parser, CPP_CLOSE_PAREN,
					      "expected %<)%>"))
			إرجاع return_p;
		    }
		  /* Parse profile: quality(value) */
		  وإلا
		    {
		      شجرة q;
		      profile_quality quality;
		      شجرة v = c_parser_peek_token (parser)->قيمة;
		      إذا (!parse_profile_quality (IDENTIFIER_POINTER (v),
						  &quality))
			{
			  c_parser_error (parser, "unknown block specifier");
			  إرجاع خطأ;
			}

		      c_parser_consume_token (parser);
		      إذا (!c_parser_require (parser, CPP_OPEN_PAREN,
					     "expected %<(%>"))
			إرجاع خطأ;

		      إذا (!c_parser_next_token_is (parser, CPP_العدد)
			  || (شجرة_CODE (q = c_parser_peek_token (parser)->قيمة)
			      != INTEGER_CST))
			{
			  c_parser_error (parser, "expected count value");
			  إرجاع خطأ;
			}

		      bb_تعداد
			= profile_تعداد::from_gcov_type (شجرة_INT_CST_أدنى (q),
							 quality);
		      c_parser_consume_token (parser);
		      إذا (! c_parser_require (parser, CPP_CLOSE_PAREN,
					      "expected %<)%>"))
			إرجاع return_p;
		    }
		}
	      إذا (! c_parser_require (parser, CPP_CLOSE_PAREN,
				      "expected %<)%>")
		  || ! c_parser_require (parser, CPP_COLON,
					 "expected %<:%>"))
		إرجاع return_p;

	      /* Put stmts parsed in the current block.  */
	      إذا (!gimple_seq_empty_p (*seq))
		{
		  إذا (!parser.current_bb)
		    c_parser_error (parser, "stmts without block");
		  وإلا
		    {
		      gimple_stmt_iterator gsi
			= gsi_start_bb (parser.current_bb);
		      gsi_أدرج_seq_after_without_update (&gsi, *seq,
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
		parser.ادفع_edge (ENTRY_BLOCK, bb->index, EDGE_FALLTHRU,
				  profile_probability::always ());

	      /* We leave the proper setting to fixup.  */
	      صنف loop *loop_father = loops_for_fn (cfun)->شجرة_جذر;
	      /* If the new block is a loop header, allocate a loop
		 struct.  Fixup will take care of proper placement within
		 the loop tree.  */
	      إذا (is_loop_header_of != -1)
		{
		  إذا (العدد_of_loops (cfun) > (unsigned)is_loop_header_of
		      && get_loop (cfun, is_loop_header_of) != عدم)
		    {
		      c_parser_error (parser, "duplicate loop header");
		    }
		  وإلا
		    {
		      صنف loop *loop = alloc_loop ();
		      loop->رقم = is_loop_header_of;
		      loop->header = bb;
		      إذا (العدد_of_loops (cfun) <= (unsigned)is_loop_header_of)
			vec_safe_grow_cleared (loops_for_fn (cfun)->larray,
					       is_loop_header_of + 1, true);
		      (*loops_for_fn (cfun)->larray)[is_loop_header_of] = loop;
		      flow_loop_شجرة_عقدة_add (loops_for_fn (cfun)->شجرة_جذر,
					       loop);
		    }
		  loop_father = get_loop (cfun, is_loop_header_of);
		}
	      bb->loop_father = loop_father;
	      bb->تعداد_2 = bb_تعداد;

	      /* Stmts now go to the new block.  */
	      parser.current_bb = bb;
	      اكسر;
	    }
	  اذهب تعبير_stmt;

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
تعبير_stmt:
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
	  gsi_أدرج_seq_after_without_update (&gsi, *seq,
					       GSI_CONTINUE_LINKING);
	}
      *seq = عدم;
    }

  إرجاع return_p;
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
  بنية c_تعبير lhs, rhs;
  gimple *assign = عدم;
  location_t loc;
  شجرة arg = NULL_شجرة;
  auto_vec<شجرة> vargs;

  lhs = c_parser_gimple_unary_expression (parser);
  loc = تعبير_LOCATION (lhs.قيمة);
  rhs.set_error ();

  /* GIMPLE call statement without LHS.  */
  إذا (c_parser_next_token_is (parser, CPP_SEMICOLON)
      && شجرة_CODE (lhs.قيمة) == CALL_تعبير)
    {
      gimple *call;
      call = gimple_build_call_from_شجرة (lhs.قيمة, عدم);
      gimple_seq_add_stmt_without_update (seq, call);
      gimple_set_location (call, loc);
      إرجاع;
    }

  /* All following cases are statements with LHS.  */
  إذا (! c_parser_require (parser, CPP_EQ, "expected %<=%>"))
    إرجاع;

  /* Eat and ignore {v} right after the =, the has_volatile_ops is
     redundant and re-computed by the operand scanner.  */
  إذا (c_parser_next_token_is (parser, CPP_OPEN_BRACE)
      && !(c_parser_peek_token (parser)->flags & PREV_WHITE)
      && c_parser_peek_2nd_token (parser)->type == CPP_NAME
      && !(c_parser_peek_2nd_token (parser)->flags & PREV_WHITE)
      && strcmp ("v", IDENTIFIER_POINTER
			(c_parser_peek_2nd_token (parser)->قيمة)) == 0
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
	إرجاع;
      /* ???  The actual type used in the cast expression is ignored as
         in GIMPLE it is encoded by the type of the LHS.  */
      rhs = c_parser_gimple_postfix_expression (parser);
      إذا (lhs.قيمة != error_mark_عقدة
	  && rhs.قيمة != error_mark_عقدة)
	{
	  تعداد شجرة_code code = NOP_تعبير;
	  إذا (FLOAT_TYPE_P (شجرة_TYPE (lhs.قيمة))
	      && ! FLOAT_TYPE_P (شجرة_TYPE (rhs.قيمة)))
	    code = FLOAT_تعبير;
	  وإلا إذا (! FLOAT_TYPE_P (شجرة_TYPE (lhs.قيمة))
		   && FLOAT_TYPE_P (شجرة_TYPE (rhs.قيمة)))
	    code = FIX_TRUNC_تعبير;
	  assign = gimple_build_assign (lhs.قيمة, code, rhs.قيمة);
	  gimple_seq_add_stmt_without_update (seq, assign);
	  gimple_set_location (assign, loc);
	  إرجاع;
	}
    }

  /* Unary expression.  */
  بدل (c_parser_peek_token (parser)->type)
    {
    حالة CPP_NAME:
      {
	شجرة id = c_parser_peek_token (parser)->قيمة;
	إذا (strcmp (IDENTIFIER_POINTER (id), "__ABS") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__ABSU") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__MIN") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__MAX") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__BIT_INSERT") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__VEC_PERM") == 0)
	  اذهب build_unary_تعبير;
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
    build_unary_تعبير:
      rhs = c_parser_gimple_unary_expression (parser);
      إذا (rhs.قيمة != error_mark_عقدة)
	{
	  assign = gimple_build_assign (lhs.قيمة, rhs.قيمة);
	  gimple_set_location (assign, loc);
	  gimple_seq_add_stmt_without_update (seq, assign);
	}
      إرجاع;

    افتراضي:;
    }

  /* GIMPLE PHI statement.  */
  إذا (c_parser_next_token_is_keyword (parser, RID_PHI))
    {
      c_parser_consume_token (parser);

      إذا (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	إرجاع;

      إذا (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	c_parser_consume_token (parser);

      بينما (c_parser_next_token_is_not (parser, CPP_CLOSE_PAREN))
	{
	  إذا (c_parser_next_token_is (parser, CPP_NAME)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      arg = c_parser_peek_token (parser)->قيمة;
	      c_parser_consume_token (parser);
	      إذا (c_parser_next_token_is (parser, CPP_COLON))
		c_parser_consume_token (parser);
	      صحيح src_index = -1;
	      إذا (!c_parser_gimple_parse_bb_spec (arg, &src_index))
		c_parser_error (parser, "invalid source block specification");
	      vargs.safe_ادفع (size_int (src_index));
	    }
	  وإلا إذا (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  وإلا
	    {
	      arg = c_parser_gimple_unary_expression (parser).قيمة;
	      vargs.safe_ادفع (arg);
	    }
	}

      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");

      /* Build internal function for PHI.  */
      gcall *call_stmt = gimple_build_call_internal_vec (IFN_PHI, vargs);
      gimple_call_set_lhs (call_stmt, lhs.قيمة);
      gimple_set_location (call_stmt, UNKNOWN_LOCATION);
      gimple_seq_add_stmt_without_update (seq, call_stmt);
      إرجاع;
    }

  /* GIMPLE call with lhs.  */
  إذا (c_parser_next_token_is (parser, CPP_DOT)
      || (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN
	  && lookup_name (c_parser_peek_token (parser)->قيمة)))
    {
      rhs = c_parser_gimple_unary_expression (parser);
      إذا (rhs.قيمة != error_mark_عقدة)
	{
	  gimple *call = gimple_build_call_from_شجرة (rhs.قيمة, عدم);
	  gimple_call_set_lhs (call, lhs.قيمة);
	  gimple_seq_add_stmt_without_update (seq, call);
	  gimple_set_location (call, loc);
	}
      إرجاع;
    }

  rhs = c_parser_gimple_ثنائي_expression (parser, شجرة_TYPE (lhs.قيمة));
  إذا (lhs.قيمة != error_mark_عقدة
      && rhs.قيمة != error_mark_عقدة)
    {
      /* If we parsed an identifier and the next token  is a '?' then parse
	 a conditional expression.  */
      إذا (SSA_VAR_P (rhs.قيمة) && c_parser_next_token_is (parser, CPP_QUERY))
	{
	  بنية c_تعبير trueval, falseval;
	  c_parser_consume_token (parser);
	  trueval = c_parser_gimple_postfix_expression (parser);
	  falseval.set_error ();
	  إذا (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    falseval = c_parser_gimple_postfix_expression (parser);
	  إذا (trueval.قيمة == error_mark_عقدة
	      || falseval.قيمة == error_mark_عقدة)
	    إرجاع;
	  rhs.قيمة = build3_loc (loc,
				  VECTOR_TYPE_P (شجرة_TYPE (rhs.قيمة))
				  ? VEC_COND_تعبير : COND_تعبير,
				  شجرة_TYPE (trueval.قيمة),
				  rhs.قيمة, trueval.قيمة, falseval.قيمة);
	}
      إذا (get_gimple_rhs_class (شجرة_CODE (rhs.قيمة)) == GIMPLE_INVALID_RHS)
	{
	  c_parser_error (parser, "unexpected RHS for assignment");
	  إرجاع;
	}
      assign = gimple_build_assign (lhs.قيمة, rhs.قيمة);
      gimple_seq_add_stmt_without_update (seq, assign);
      gimple_set_location (assign, loc);
    }
  إرجاع;
}

/* A mapping between an identifier to a tree code for binary operations. */
ساكن ثابت std::pair<ثابت حرف *, شجرة_code> gimple_ثنائي_identifier_code[] =
  {
    {"__MULT_HIGHPART", MULT_HIGHPART_تعبير},
    {"__UNLT", UNLT_تعبير},
    {"__UNLE", UNLE_تعبير},
    {"__UNGT", UNGT_تعبير},
    {"__UNGE", UNGE_تعبير},
    {"__UNEQ", UNEQ_تعبير},
    {"__UNORDERED", UNORDERED_تعبير},
    {"__ORDERED", ORDERED_تعبير},
    {"__LTGT", LTGT_تعبير},
    {"__FLOOR_DIV", FLOOR_DIV_تعبير},
    {"__ROUND_DIV", ROUND_DIV_تعبير},
    {"__EXACT_DIV", EXACT_DIV_تعبير},
    {"__CEIL_DIV", CEIL_DIV_تعبير},
    {"__FLOOR_MOD", FLOOR_MOD_تعبير},
    {"__ROUND_MOD", ROUND_MOD_تعبير},
    {"__CEIL_MOD", CEIL_MOD_تعبير},
    {"__ROTATE_LEFT", LROTATE_تعبير},
    {"__ROTATE_RIGHT", RROTATE_تعبير},
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

ساكن c_تعبير
c_parser_gimple_ثنائي_expression (gimple_parser &parser, شجرة ret_type)
{
  /* Location of the binary operator.  */
  بنية c_تعبير ret, lhs, rhs;
  تعداد شجرة_code code = ERROR_MARK;
  ret.set_error ();
  lhs = c_parser_gimple_postfix_expression (parser, ret_type);
  إذا (c_parser_error (parser))
    إرجاع ret;
  بدل (c_parser_peek_token (parser)->type)
    {
    حالة CPP_MULT:
      code = MULT_تعبير;
      اكسر;
    حالة CPP_DIV:
      code = TRUNC_DIV_تعبير;
      اكسر;
    حالة CPP_MOD:
      code = TRUNC_MOD_تعبير;
      اكسر;
    حالة CPP_PLUS:
      إذا (POINTER_TYPE_P (شجرة_TYPE (lhs.قيمة)))
	code = POINTER_PLUS_تعبير;
      وإلا
	code = PLUS_تعبير;
      اكسر;
    حالة CPP_MINUS:
      إذا (POINTER_TYPE_P (شجرة_TYPE (lhs.قيمة)))
	code = POINTER_DIFF_تعبير;
      وإلا
	code = MINUS_تعبير;
      اكسر;
    حالة CPP_LSHIFT:
      code = LSHIFT_تعبير;
      اكسر;
    حالة CPP_RSHIFT:
      code = RSHIFT_تعبير;
      اكسر;
    حالة CPP_LESS:
      code = LT_تعبير;
      اكسر;
    حالة CPP_GREATER:
      code = GT_تعبير;
      اكسر;
    حالة CPP_LESS_EQ:
      code = LE_تعبير;
      اكسر;
    حالة CPP_GREATER_EQ:
      code = GE_تعبير;
      اكسر;
    حالة CPP_EQ_EQ:
      code = EQ_تعبير;
      اكسر;
    حالة CPP_NOT_EQ:
      code = NE_تعبير;
      اكسر;
    حالة CPP_AND:
      code = BIT_AND_تعبير;
      اكسر;
    حالة CPP_XOR:
      code = BIT_XOR_تعبير;
      اكسر;
    حالة CPP_OR:
      code = BIT_IOR_تعبير;
      اكسر;
    حالة CPP_AND_AND:
      c_parser_error (parser, "%<&&%> not valid in GIMPLE");
      إرجاع ret;
    حالة CPP_OR_OR:
      c_parser_error (parser, "%<||%> not valid in GIMPLE");
      إرجاع ret;
    حالة CPP_NAME:
      {
	شجرة id = c_parser_peek_token (parser)->قيمة;
	لكل (auto &p : gimple_ثنائي_identifier_code)
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
      إرجاع lhs;
    }
  location_t ret_loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  rhs = c_parser_gimple_postfix_expression (parser);
  إذا (lhs.قيمة != error_mark_عقدة && rhs.قيمة != error_mark_عقدة)
    ret.قيمة = build2_loc (ret_loc, code, ret_type, lhs.قيمة, rhs.قيمة);
  إرجاع ret;
}

/* Parse a gimple parentized binary expression.  */

ساكن c_تعبير
c_parser_gimple_parentized_ثنائي_expression (gimple_parser &parser,
					      location_t op_loc,
					      شجرة_code code)
{
  بنية c_تعبير ret;
  ret.set_error ();

  c_parser_consume_token (parser);
  إذا (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    إرجاع ret;
  c_تعبير op1 = c_parser_gimple_postfix_expression (parser);
  إذا (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    إرجاع ret;
  c_تعبير op2 = c_parser_gimple_postfix_expression (parser);
  إذا (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    إرجاع ret;

  إذا (op1.قيمة != error_mark_عقدة && op2.قيمة != error_mark_عقدة)
    ret.قيمة = build2_loc (op_loc,
			    code, شجرة_TYPE (op1.قيمة), op1.قيمة, op2.قيمة);
  إرجاع ret;
}

/* Parse a gimple parentized binary expression.  */

ساكن c_تعبير
c_parser_gimple_parentized_ternary_expression (gimple_parser &parser,
					       location_t op_loc,
					       شجرة_code code)
{
  بنية c_تعبير ret;
  ret.set_error ();

  c_parser_consume_token (parser);
  إذا (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    إرجاع ret;
  c_تعبير op1 = c_parser_gimple_postfix_expression (parser);
  إذا (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    إرجاع ret;
  c_تعبير op2 = c_parser_gimple_postfix_expression (parser);
  إذا (!c_parser_require (parser, CPP_COMMA, "expected %<)%>"))
    إرجاع ret;
  c_تعبير op3 = c_parser_gimple_postfix_expression (parser);
  إذا (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    إرجاع ret;

  إذا (op1.قيمة != error_mark_عقدة
      && op2.قيمة != error_mark_عقدة
      && op3.قيمة != error_mark_عقدة)
    ret.قيمة = build3_loc (op_loc,
			    code, شجرة_TYPE (op1.قيمة),
			    op1.قيمة, op2.قيمة, op3.قيمة);
  إرجاع ret;
}

/* Parse gimple unary expression.

   gimple-unary-expression:
     gimple-postfix-expression
     unary-operator gimple-postfix-expression

   unary-operator: one of
     & * + - ~ abs_expr
*/

ساكن c_تعبير
c_parser_gimple_unary_expression (gimple_parser &parser)
{
  بنية c_تعبير ret, op;
  location_t op_loc = c_parser_peek_token (parser)->location;
  location_t finish;
  ret.set_error ();
  بدل (c_parser_peek_token (parser)->type)
    {
    حالة CPP_AND:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      mark_exp_read (op.قيمة);
      إرجاع gimple_parser_build_unary_op (op_loc, ADDR_تعبير, op);
    حالة CPP_MULT:
      {
	c_parser_consume_token (parser);
	op = c_parser_gimple_postfix_expression (parser);
	إذا (op.قيمة == error_mark_عقدة)
	  إرجاع ret;
	إذا (! POINTER_TYPE_P (شجرة_TYPE (op.قيمة)))
	  {
	    error_at (op_loc, "expected pointer as argument of unary %<*%>");
	    إرجاع ret;
	  }
	finish = op.get_finish ();
	location_t combined_loc = make_location (op_loc, op_loc, finish);
	ret.قيمة = build_simple_mem_ref_loc (combined_loc, op.قيمة);
	شجرة_SIDE_EFFECTS (ret.قيمة)
	  = شجرة_THIS_VOLATILE (ret.قيمة)
	  = TYPE_VOLATILE (شجرة_TYPE (شجرة_TYPE (op.قيمة)));
	ret.src_range.m_start = op_loc;
	ret.src_range.m_finish = finish;
	إرجاع ret;
      }
    حالة CPP_PLUS:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      إرجاع gimple_parser_build_unary_op (op_loc, CONVERT_تعبير, op);
    حالة CPP_MINUS:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      إرجاع gimple_parser_build_unary_op (op_loc, NEGATE_تعبير, op);
    حالة CPP_COMPL:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      إرجاع gimple_parser_build_unary_op (op_loc, BIT_NOT_تعبير, op);
    حالة CPP_NOT:
      c_parser_error (parser, "%<!%> not valid in GIMPLE");
      إرجاع ret;
    حالة CPP_KEYWORD:
      بدل (c_parser_peek_token (parser)->keyword)
	{
	حالة RID_REALPART:
	  c_parser_consume_token (parser);
	  op = c_parser_gimple_postfix_expression (parser);
	  إرجاع gimple_parser_build_unary_op (op_loc, REALPART_تعبير, op);
	حالة RID_IMAGPART:
	  c_parser_consume_token (parser);
	  op = c_parser_gimple_postfix_expression (parser);
	  إرجاع gimple_parser_build_unary_op (op_loc, IMAGPART_تعبير, op);
	افتراضي:
	  إرجاع c_parser_gimple_postfix_expression (parser);
	}
    حالة CPP_NAME:
	{
	  شجرة id = c_parser_peek_token (parser)->قيمة;
	  إذا (strcmp (IDENTIFIER_POINTER (id), "__ABS") == 0)
	    {
	      c_parser_consume_token (parser);
	      op = c_parser_gimple_postfix_expression (parser);
	      إرجاع gimple_parser_build_unary_op (op_loc, ABS_تعبير, op);
	    }
	  وإلا إذا (strcmp (IDENTIFIER_POINTER (id), "__ABSU") == 0)
	    {
	      c_parser_consume_token (parser);
	      op = c_parser_gimple_postfix_expression (parser);
	      إرجاع gimple_parser_build_unary_op (op_loc, ABSU_تعبير, op);
	    }
	  وإلا إذا (strcmp (IDENTIFIER_POINTER (id), "__MIN") == 0)
	    إرجاع c_parser_gimple_parentized_ثنائي_expression (parser,
								 op_loc,
								 MIN_تعبير);
	  وإلا إذا (strcmp (IDENTIFIER_POINTER (id), "__MAX") == 0)
	    إرجاع c_parser_gimple_parentized_ثنائي_expression (parser,
								 op_loc,
								 MAX_تعبير);
	  وإلا إذا (strcmp (IDENTIFIER_POINTER (id), "__VEC_PERM") == 0)
	    إرجاع c_parser_gimple_parentized_ternary_expression
			(parser, op_loc, VEC_PERM_تعبير);
	  وإلا إذا (strcmp (IDENTIFIER_POINTER (id), "__BIT_INSERT") == 0)
	    {
	      /* __BIT_INSERT '(' postfix-expression, postfix-expression,
			          integer ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      إذا (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_تعبير op0 = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_تعبير op1 = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_تعبير op2 = c_parser_gimple_postfix_expression (parser);
		  إذا (شجرة_CODE (op2.قيمة) != INTEGER_CST
		      || !int_fits_type_p (op2.قيمة, bitsizetype))
		    c_parser_error (parser, "expected constant offset");
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  إذا (op0.قيمة != error_mark_عقدة
		      && op1.قيمة != error_mark_عقدة
		      && شجرة_CODE (op2.قيمة) == INTEGER_CST)
		    ret.قيمة = build3_loc (loc, BIT_أدرج_تعبير,
					    شجرة_TYPE (op0.قيمة),
					    op0.قيمة, op1.قيمة,
					    fold_convert (bitsizetype,
							  op2.قيمة));
		}
	      إرجاع ret;
	    }
	  وإلا
	    إرجاع c_parser_gimple_postfix_expression (parser);
	}
    افتراضي:
      إرجاع c_parser_gimple_postfix_expression (parser);
    }
}

/* Decompose ID into base name (ID until ver_offset) and VERSION.  Return
   true if ID matches a SSA name.  */

ساكن منطقي
c_parser_parse_ssa_name_id (شجرة id, unsigned *version, unsigned *ver_offset)
{
  ثابت حرف *token = IDENTIFIER_POINTER (id);
  ثابت حرف *var_version = strrchr (token, '_');
  إذا (! var_version)
    إرجاع خطأ;

  *ver_offset = var_version - token;
  لكل (ثابت حرف *p = var_version + 1; *p; ++p)
    إذا (! ISDIGIT (*p))
      إرجاع خطأ;
  *version = atoi (var_version + 1);
  إرجاع *version > 0;
}

/* Get at the actual SSA name ID with VERSION starting at VER_OFFSET.
   TYPE is the type if the SSA name is being declared.  */

ساكن شجرة
c_parser_parse_ssa_name (gimple_parser &parser,
			 شجرة id, شجرة type, unsigned version,
			 unsigned ver_offset)
{
  شجرة name = NULL_شجرة;
  ثابت حرف *token = IDENTIFIER_POINTER (id);

  إذا (ver_offset == 0)
    {
      /* Anonymous unnamed SSA name.  */
      إذا (version < رقم_ssa_names)
	name = ssa_name (version);
      إذا (! name)
	{
	  إذا (! type)
	    {
	      c_parser_error (parser, "SSA name undeclared");
	      إرجاع error_mark_عقدة;
	    }
	  name = make_ssa_name_fn (cfun, type, عدم, version);
	}
    }
  وإلا
    {
      إذا (version < رقم_ssa_names)
	name = ssa_name (version);
      إذا (! name)
	{
	  /* Separate var name from version.  */
	  حرف *var_name = XNEWVEC (حرف, ver_offset + 1);
	  memcpy (var_name, token, ver_offset);
	  var_name[ver_offset] = '\0';
	  /* lookup for parent decl.  */
	  id = get_identifier (var_name);
	  شجرة parent = lookup_name (id);
	  XDELETEVEC (var_name);
	  إذا (! parent || parent == error_mark_عقدة)
	    {
	      c_parser_error (parser, "base variable or SSA name undeclared");
	      إرجاع error_mark_عقدة;
	    }
	  إذا (!(VAR_P (parent)
		|| شجرة_CODE (parent) == PARM_DECL
		|| شجرة_CODE (parent) == RESULT_DECL))
	    {
	      error ("invalid base %qE for SSA name", parent);
	      إرجاع error_mark_عقدة;
	    }
	  name = make_ssa_name_fn (cfun, parent,
				   gimple_build_nop (), version);
	}
    }

  إرجاع name;
}

/* Parse a gimple call to an internal function.

   gimple-call-internal:
     . identifier ( gimple-argument-expression-list[opt] )  */

ساكن بنية c_تعبير
c_parser_gimple_call_internal (gimple_parser &parser)
{
  بنية c_تعبير تعبير;
  تعبير.set_error ();

  gcc_assert (c_parser_next_token_is (parser, CPP_DOT));
  c_parser_consume_token (parser);
  location_t loc = c_parser_peek_token (parser)->location;
  إذا (!c_parser_next_token_is (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_kind != C_ID_ID)
    {
      c_parser_error (parser, "expecting internal function name");
      إرجاع تعبير;
    }
  شجرة id = c_parser_peek_token (parser)->قيمة;
  internal_fn ifn = lookup_internal_fn (IDENTIFIER_POINTER (id));
  c_parser_consume_token (parser);
  إذا (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    {
      auto_vec<شجرة> exprlist;
      إذا (!c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_gimple_تعبير_list (parser, &exprlist);
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      إذا (ifn == IFN_LAST)
	error_at (loc, "unknown internal function %qE", id);
      وإلا
	{
	  تعبير.قيمة = build_call_تعبير_internal_loc_array
	    (loc, ifn, void_type_عقدة, exprlist.length (),
	     exprlist.address ());
	  تعبير.original_code = ERROR_MARK;
	  تعبير.original_type = عدم;
	  تعبير.m_decimal = 0;
	}
    }
  إرجاع تعبير;
}

/* Parse '<' type [',' alignment] '>' and return a type on success
   and NULL_TREE on error.  */

ساكن شجرة
c_parser_gimple_typespec (gimple_parser &parser)
{
  بنية c_type_name *type_name = عدم;
  شجرة alignment = NULL_شجرة;
  إذا (c_parser_require (parser, CPP_LESS, "expected %<<%>"))
    {
      type_name = c_parser_type_name (parser);
      /* Optional alignment.  */
      إذا (c_parser_next_token_is (parser, CPP_COMMA))
	{
	  c_parser_consume_token (parser);
	  alignment
	      = c_parser_gimple_postfix_expression (parser).قيمة;
	}
      c_parser_skip_until_found (parser,
				 CPP_GREATER, "expected %<>%>");
    }
  إذا (!type_name)
    إرجاع NULL_شجرة;
  شجرة tem;
  شجرة type = groktypename (type_name, &tem, عدم);
  إذا (alignment)
    type = build_aligned_type (type, شجرة_to_uhwi (alignment));
  إرجاع type;
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

ساكن بنية c_تعبير
c_parser_gimple_postfix_expression (gimple_parser &parser, شجرة ret_type)
{
  location_t loc = c_parser_peek_token (parser)->location;
  source_range tok_range = c_parser_peek_token (parser)->get_range ();
  بنية c_تعبير تعبير;
  تعبير.set_error ();
  بدل (c_parser_peek_token (parser)->type)
    {
    حالة CPP_العدد:
      تعبير.قيمة = c_parser_peek_token (parser)->قيمة;
      set_c_تعبير_source_range (&تعبير, tok_range);
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      اكسر;
    حالة CPP_CHAR:
    حالة CPP_CHAR16:
    حالة CPP_CHAR32:
    حالة CPP_UTF8CHAR:
    حالة CPP_WCHAR:
      تعبير.قيمة = c_parser_peek_token (parser)->قيمة;
      set_c_تعبير_source_range (&تعبير, tok_range);
      c_parser_consume_token (parser);
      اكسر;
    حالة CPP_STRING:
    حالة CPP_STRING16:
    حالة CPP_STRING32:
    حالة CPP_WSTRING:
    حالة CPP_UTF8STRING:
      تعبير = c_parser_string_literal (parser, خطأ, true);
      اكسر;
    حالة CPP_DOT:
      تعبير = c_parser_gimple_call_internal (parser);
      اكسر;
    حالة CPP_NAME:
      إذا (c_parser_peek_token (parser)->id_kind == C_ID_ID)
	{
	  شجرة id = c_parser_peek_token (parser)->قيمة;
	  إذا (strcmp (IDENTIFIER_POINTER (id), "__MEM") == 0)
	    {
	      /* __MEM '<' type-name [ ',' number ] '>'
	               '(' [ '(' type-name ')' ] unary-expression
			   [ '+' number ]
			   [ ',' number ]
			   [ ',' number ':' number ] ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      شجرة type = c_parser_gimple_typespec (parser);
	      بنية c_تعبير ptr, alias_off, step, index, index2;
	      ptr.قيمة = error_mark_عقدة;
	      alias_off.قيمة = NULL_شجرة;
	      step.قيمة = NULL_شجرة;
	      index.قيمة = NULL_شجرة;
	      index2.قيمة = NULL_شجرة;
	      unsigned short clique = 0;
	      unsigned short base = 0;
	      منطقي reverse_order = خطأ;
	      بنية c_تعبير ro;
	      إذا (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  شجرة alias_type = NULL_شجرة;
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
			  شجرة tem;
			  alias_type = groktypename (alias_type_name,
						     &tem, عدم);
			}
		    }
		  ptr = c_parser_gimple_unary_expression (parser);
		  إذا (ptr.قيمة == error_mark_عقدة
		      || ! POINTER_TYPE_P (شجرة_TYPE (ptr.قيمة)))
		    {
		      إذا (ptr.قيمة != error_mark_عقدة)
			error_at (ptr.get_start (),
				  "invalid type of %<__MEM%> operand");
		      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
						 "expected %<)%>");
		      إرجاع تعبير;
		    }
		  إذا (! alias_type)
		    alias_type = شجرة_TYPE (ptr.قيمة);
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
		  وإلا إذا (alias_off.قيمة
			   && شجرة_CODE (alias_off.قيمة) != INTEGER_CST)
		    std::swap (alias_off, index2);
		  إذا (c_parser_next_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      index2 = c_parser_gimple_postfix_expression (parser);
		    }
		  إذا (alias_off.قيمة)
		    {
		      إذا (شجرة_CODE (alias_off.قيمة) != INTEGER_CST)
			error_at (alias_off.get_start (),
				  "expected constant offset for %<__MEM%> "
				  "operand");
		      alias_off.قيمة = fold_convert (alias_type,
						      alias_off.قيمة);
		    }
		  وإلا
		    alias_off.قيمة = build_int_cst (alias_type, 0);
		  إذا (step.قيمة)
		    {
		      إذا (شجرة_CODE (step.قيمة) != INTEGER_CST)
			error_at (step.get_start (),
				  "expected constant step for %<__MEM%> "
				  "operand");
		    }
		  إذا (c_parser_next_token_is (parser, CPP_COMMA))
		    {
		      بنية c_تعبير cl, ba;
		      منطقي has_clb = true;
		      c_parser_consume_token (parser);
		      cl = c_parser_gimple_postfix_expression (parser);
		      إذا (!c_parser_next_token_is (parser, CPP_COLON))
			{
			  ro = cl;
			  unsigned HOST_WIDE_INT tmp = 0;
			  إذا (!شجرة_fits_uhwi_p (ro.قيمة)
			      || (tmp = شجرة_to_uhwi (ro.قيمة)) > 1)
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
			  إذا (!شجرة_fits_uhwi_p (cl.قيمة)
			      || !شجرة_fits_uhwi_p (ba.قيمة)
			      || compare_شجرة_int (cl.قيمة,
						   (clique = شجرة_to_uhwi
								(cl.قيمة)))
			      || compare_شجرة_int (ba.قيمة,
						   (base = شجرة_to_uhwi
								 (ba.قيمة))))
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
		  إرجاع تعبير;
		}
	      إذا (index.قيمة || step.قيمة || index2.قيمة)
		تعبير.قيمة = build5_loc (loc, TARGET_MEM_REF,
					 type, ptr.قيمة, alias_off.قيمة,
					 index.قيمة, step.قيمة, index2.قيمة);
	      وإلا
		تعبير.قيمة = build2_loc (loc, MEM_REF,
					 type, ptr.قيمة, alias_off.قيمة);
	      إذا (clique != 0)
		{
		  cfun->last_clique = MAX (cfun->last_clique, clique);
		  MR_DEPENDENCE_CLIQUE (تعبير.قيمة) = clique;
		  MR_DEPENDENCE_BASE (تعبير.قيمة) = base;
		}
	      إذا (reverse_order)
		{
		  إذا (شجرة_CODE (تعبير.قيمة) == MEM_REF)
		    REF_REVERSE_STORAGE_ORDER (تعبير.قيمة) = reverse_order;
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
	      شجرة type = c_parser_gimple_typespec (parser);
	      إذا (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_تعبير op = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  إذا (type && op.قيمة != error_mark_عقدة)
		    تعبير.قيمة = build1_loc (loc, VIEW_CONVERT_تعبير,
					     type, op.قيمة);
		}
	      اكسر;
	    }
	  وإلا إذا (strcmp (IDENTIFIER_POINTER (id), "__BIT_FIELD_REF") == 0)
	    {
	      /* __BIT_FIELD_REF '<' type-name [ ',' number ] '>'
	                        '(' postfix-expression, integer, integer ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      شجرة type = c_parser_gimple_typespec (parser);
	      إذا (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_تعبير op0 = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_تعبير op1 = c_parser_gimple_postfix_expression (parser);
		  إذا (شجرة_CODE (op1.قيمة) != INTEGER_CST
		      || !int_fits_type_p (op1.قيمة, bitsizetype))
		    c_parser_error (parser, "expected constant size");
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_تعبير op2 = c_parser_gimple_postfix_expression (parser);
		  إذا (شجرة_CODE (op2.قيمة) != INTEGER_CST
		      || !int_fits_type_p (op2.قيمة, bitsizetype))
		    c_parser_error (parser, "expected constant offset");
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  إذا (type
		      && op0.قيمة != error_mark_عقدة
		      && شجرة_CODE (op1.قيمة) == INTEGER_CST
		      && شجرة_CODE (op2.قيمة) == INTEGER_CST)
		    تعبير.قيمة = build3_loc (loc, BIT_FIELD_REF, type,
					     op0.قيمة,
					     fold_convert (bitsizetype,
							   op1.قيمة),
					     fold_convert (bitsizetype,
							   op2.قيمة));
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
		      ثابت حرف *kind_str = IDENTIFIER_POINTER (tok->قيمة);
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
	      تعبير.قيمة = build_clobber (ret_type, kind);
	      اكسر;
	    }
	  وإلا إذا (strcmp (IDENTIFIER_POINTER (id), "_Literal") == 0)
	    {
	      /* _Literal '(' type-name ')' ( [ '-' ] constant | constructor ) */
	      c_parser_consume_token (parser);
	      شجرة type = NULL_شجرة;
	      إذا (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  بنية c_type_name *type_name = c_parser_type_name (parser);
		  شجرة tem;
		  إذا (type_name)
		    type = groktypename (type_name, &tem, عدم);
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      إذا (! type)
		{
		  c_parser_error (parser, "invalid _Literal");
		  إرجاع تعبير;
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
		      إرجاع تعبير;
		    }
		  vec<constructor_elt, va_gc> *v = عدم;
		  منطقي constant_p = true;
		  إذا (VECTOR_TYPE_P (type)
		      && !c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
		    {
		      vec_alloc (v, TYPE_VECTOR_SUBPARTS (type).to_constant ());
		      افعل
			{
			  شجرة val
			    = c_parser_gimple_postfix_expression (parser).قيمة;
			  إذا (! val
			      || val == error_mark_عقدة
			      || (! CONSTANT_CLASS_P (val)
				  && ! SSA_VAR_P (val)))
			    {
			      c_parser_error (parser, "invalid _Literal");
			      إرجاع تعبير;
			    }
			  CONSTRUCTOR_APPEND_ELT (v, NULL_شجرة, val);
			  إذا (! CONSTANT_CLASS_P (val))
			    constant_p = خطأ;
			  إذا (c_parser_next_token_is (parser, CPP_COMMA))
			    c_parser_consume_token (parser);
			  وإلا
			    اكسر;
			}
		      بينما (1);
		    }
		  إذا (c_parser_require (parser, CPP_CLOSE_BRACE,
					"expected %<}%>"))
		    {
		      إذا (v && constant_p)
			تعبير.قيمة = build_vector_from_ctor (type, v);
		      وإلا
			تعبير.قيمة = build_constructor (type, v);
		    }
		  وإلا
		    {
		      c_parser_skip_until_found (parser, CPP_CLOSE_BRACE,
						 "expected %<}%>");
		      إرجاع تعبير;
		    }
		}
	      وإلا
		{
		  منطقي neg_p, addr_p;
		  إذا ((neg_p = c_parser_next_token_is (parser, CPP_MINUS)))
		    c_parser_consume_token (parser);
		  إذا ((addr_p = c_parser_next_token_is (parser, CPP_AND)))
		    c_parser_consume_token (parser);
		  شجرة val = c_parser_gimple_postfix_expression (parser).قيمة;
		  إذا (! val
		      || val == error_mark_عقدة
		      || (!CONSTANT_CLASS_P (val) && !addr_p))
		    {
		      c_parser_error (parser, "invalid _Literal");
		      إرجاع تعبير;
		    }
		  إذا (addr_p)
		    {
		      val = build1 (ADDR_تعبير, type, val);
		      إذا (!is_gimple_invariant_address (val))
			{
			  c_parser_error (parser, "invalid _Literal");
			  إرجاع تعبير;
			}
		    }
		  إذا (neg_p)
		    {
		      val = const_unop (NEGATE_تعبير, شجرة_TYPE (val), val);
		      إذا (! val)
			{
			  c_parser_error (parser, "invalid _Literal");
			  إرجاع تعبير;
			}
		    }
		  تعبير.قيمة = fold_convert (type, val);
		}
	      إرجاع تعبير;
	    }

	  /* SSA name.  */
	  unsigned version, ver_offset;
	  إذا (! lookup_name (id)
	      && c_parser_parse_ssa_name_id (id, &version, &ver_offset))
	    {
	      c_parser_consume_token (parser);
	      تعبير.قيمة = c_parser_parse_ssa_name (parser, id, NULL_شجرة,
						    version, ver_offset);
	      إذا (تعبير.قيمة == error_mark_عقدة)
		إرجاع تعبير;
	      set_c_تعبير_source_range (&تعبير, tok_range);
	      /* For default definition SSA names.  */
	      إذا (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
		  && c_parser_peek_2nd_token (parser)->type == CPP_NAME
		  && strcmp ("D",
			     IDENTIFIER_POINTER
			       (c_parser_peek_2nd_token (parser)->قيمة)) == 0
		  && c_parser_peek_nth_token (parser, 3)->type == CPP_CLOSE_PAREN)
		{
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		  إذا (! SSA_NAME_IS_DEFAULT_DEF (تعبير.قيمة))
		    {
		      إذا (!SSA_NAME_VAR (تعبير.قيمة))
			{
			  error_at (loc, "anonymous SSA name cannot have"
				    " default definition");
			  تعبير.قيمة = error_mark_عقدة;
			  إرجاع تعبير;
			}
		      set_ssa_default_def (cfun, SSA_NAME_VAR (تعبير.قيمة),
					   تعبير.قيمة);
		      SSA_NAME_DEF_STMT (تعبير.قيمة) = gimple_build_nop ();
		    }
		}
	    }
	  وإلا
	    {
	      c_parser_consume_token (parser);
	      تعبير.قيمة
		= build_external_ref (loc, id,
				      (c_parser_peek_token (parser)->type
				       == CPP_OPEN_PAREN), &تعبير.original_type);
	      set_c_تعبير_source_range (&تعبير, tok_range);
	    }
	  اكسر;
	}
      /* Fallthru.  */
    افتراضي:
      c_parser_error (parser, "expected expression");
      تعبير.set_error ();
      اكسر;
    }
  إذا (تعبير.قيمة == error_mark_عقدة)
    إرجاع تعبير;
  إرجاع c_parser_gimple_postfix_expression_after_primary
    (parser, تعبير_LOC_OR_LOC (تعبير.قيمة, loc), تعبير);
}

/* Parse a gimple postfix expression after the initial primary or compound
   literal.  */

ساكن بنية c_تعبير
c_parser_gimple_postfix_expression_after_primary (gimple_parser &parser,
						  location_t تعبير_loc,
						  بنية c_تعبير تعبير)
{
  location_t start;
  location_t finish;
  شجرة ident;
  location_t comp_loc;

  بينما (true)
    {
      location_t op_loc = c_parser_peek_token (parser)->location;
      بدل (c_parser_peek_token (parser)->type)
	{
	حالة CPP_OPEN_SQUARE:
	  {
	    c_parser_consume_token (parser);
	    شجرة idx = c_parser_gimple_unary_expression (parser).قيمة;

	    إذا (! c_parser_require (parser, CPP_CLOSE_SQUARE, "expected %<]%>"))
	      {
		c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE, عدم);
		اكسر;
	      }

	    start = تعبير.get_start ();
	    finish = c_parser_tokens_buf (parser, 0)->location;
	    تعبير.قيمة = build_array_ref (op_loc, تعبير.قيمة, idx);
	    set_c_تعبير_source_range (&تعبير, start, finish);
	    تعبير.m_decimal = 0;

	    تعبير.original_code = ERROR_MARK;
	    تعبير.original_type = عدم;
	    اكسر;
	  }
	حالة CPP_OPEN_PAREN:
	  {
	    /* Function call.  */
	    c_parser_consume_token (parser);
	    auto_vec<شجرة> exprlist;
	    إذا (! c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	      c_parser_gimple_تعبير_list (parser, &exprlist);
	    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    إذا (!FUNC_OR_METHOD_TYPE_P (شجرة_TYPE (تعبير.قيمة)))
	      {
		c_parser_error (parser, "invalid call to non-function");
		تعبير.set_error ();
		اكسر;
	      }
	    تعبير.قيمة = build_call_array_loc
		(تعبير_loc, شجرة_TYPE (شجرة_TYPE (تعبير.قيمة)),
		 تعبير.قيمة, exprlist.length (), exprlist.address ());
	    تعبير.m_decimal = 0;
	    تعبير.original_code = ERROR_MARK;
	    تعبير.original_type = عدم;
	    اكسر;
	  }
	حالة CPP_DOT:
	  {
	    /* Structure element reference.  */
	    c_parser_consume_token (parser);
	    إذا (c_parser_next_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		ident = comp_tok->قيمة;
		comp_loc = comp_tok->location;
	      }
	    وإلا
	      {
		c_parser_error (parser, "expected identifier");
		تعبير.set_error ();
		تعبير.original_code = ERROR_MARK;
		تعبير.original_type = عدم;
		إرجاع تعبير;
	      }
	    start = تعبير.get_start ();
	    finish = c_parser_peek_token (parser)->get_finish ();
	    c_parser_consume_token (parser);
	    تعبير.قيمة = build_component_ref (op_loc, تعبير.قيمة, ident,
					      comp_loc, UNKNOWN_LOCATION);
	    set_c_تعبير_source_range (&تعبير, start, finish);
	    تعبير.m_decimal = 0;
	    تعبير.original_code = ERROR_MARK;
	    إذا (شجرة_CODE (تعبير.قيمة) != COMPONENT_REF)
	      تعبير.original_type = عدم;
	    وإلا
	      {
		/* Remember the original type of a bitfield.  */
		شجرة field = شجرة_OPERAND (تعبير.قيمة, 1);
		إذا (شجرة_CODE (field) != FIELD_DECL)
		  تعبير.original_type = عدم;
		وإلا
		  تعبير.original_type = DECL_BIT_FIELD_TYPE (field);
	      }
	    اكسر;
	  }
	حالة CPP_DEREF:
	  {
	    /* Structure element reference.  */
	    إذا (!POINTER_TYPE_P (شجرة_TYPE (تعبير.قيمة)))
	      {
		c_parser_error (parser, "dereference of non-pointer");
		تعبير.set_error ();
		تعبير.original_code = ERROR_MARK;
		تعبير.original_type = عدم;
		إرجاع تعبير;
	      }
	    c_parser_consume_token (parser);
	    إذا (c_parser_next_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		ident = comp_tok->قيمة;
		comp_loc = comp_tok->location;
	      }
	    وإلا
	      {
		c_parser_error (parser, "expected identifier");
		تعبير.set_error ();
		تعبير.original_code = ERROR_MARK;
		تعبير.original_type = عدم;
		إرجاع تعبير;
	      }
	    start = تعبير.get_start ();
	    finish = c_parser_peek_token (parser)->get_finish ();
	    c_parser_consume_token (parser);
	    تعبير.قيمة = build_component_ref (op_loc,
					      build_simple_mem_ref_loc
					        (op_loc, تعبير.قيمة),
					      ident, comp_loc,
					      تعبير.get_location ());
	    set_c_تعبير_source_range (&تعبير, start, finish);
	    تعبير.m_decimal = 0;
	    تعبير.original_code = ERROR_MARK;
	    إذا (شجرة_CODE (تعبير.قيمة) != COMPONENT_REF)
	      تعبير.original_type = عدم;
	    وإلا
	      {
		/* Remember the original type of a bitfield.  */
		شجرة field = شجرة_OPERAND (تعبير.قيمة, 1);
		إذا (شجرة_CODE (field) != FIELD_DECL)
		  تعبير.original_type = عدم;
		وإلا
		  تعبير.original_type = DECL_BIT_FIELD_TYPE (field);
	      }
	    اكسر;
	  }
	افتراضي:
	  إرجاع تعبير;
	}
    }
}

/* Parse expression list.

   gimple-expr-list:
     gimple-unary-expression
     gimple-expr-list , gimple-unary-expression

 */

ساكن فراغ
c_parser_gimple_تعبير_list (gimple_parser &parser, vec<شجرة> *ret)
{
  بنية c_تعبير تعبير;

  تعبير = c_parser_gimple_unary_expression (parser);
  ret->safe_ادفع (تعبير.قيمة);
  بينما (c_parser_next_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      تعبير = c_parser_gimple_unary_expression (parser);
      ret->safe_ادفع (تعبير.قيمة);
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
  شجرة name = c_parser_peek_token (parser)->قيمة;
  location_t loc1 = c_parser_peek_token (parser)->location;
  gcc_assert (c_parser_next_token_is (parser, CPP_NAME));
  c_parser_consume_token (parser);
  gcc_assert (c_parser_next_token_is (parser, CPP_COLON));
  c_parser_consume_token (parser);
  شجرة label = define_label (loc1, name);
  إذا (label)
    gimple_seq_add_stmt_without_update (seq, gimple_build_label (label));
  إرجاع;
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
    إرجاع;
  c_parser_consume_token (parser);

  specs->entry_bb_تعداد = profile_تعداد::uninitialized ();
  بينما (c_parser_next_token_is (parser, CPP_NAME))
    {
      profile_quality quality;
      ثابت حرف *op = IDENTIFIER_POINTER (c_parser_peek_token (parser)->قيمة);
      c_parser_consume_token (parser);
      إذا (! strcmp (op, "startwith"))
	{
	  إذا (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    إرجاع;
	  إذا (c_parser_next_token_is_not (parser, CPP_STRING))
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"expected pass name");
	      إرجاع;
	    }
	  pass = xstrdup (شجرة_STRING_POINTER
			  (c_parser_string_literal (parser, خطأ,
						    خطأ).قيمة));
	  إذا (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<(%>"))
	    إرجاع;
	}
      وإلا إذا (parse_profile_quality (op, &quality))
	{
	  شجرة q;
	  إذا (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    إرجاع;

	  إذا (!c_parser_next_token_is (parser, CPP_العدد)
	      || (شجرة_CODE (q = c_parser_peek_token (parser)->قيمة)
		  != INTEGER_CST))
	    {
	      c_parser_error (parser, "expected count value");
	      إرجاع;
	    }

	  specs->entry_bb_تعداد
	    = profile_تعداد::from_gcov_type (شجرة_INT_CST_أدنى (q), quality);
	  c_parser_consume_token (parser);
	  إذا (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    إرجاع;
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
	  إرجاع;
	}
     إذا (c_parser_next_token_is (parser, CPP_COMMA))
       c_parser_consume_token (parser);
    }

  إذا (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    إرجاع;

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
      إرجاع;
    }

  منطقي dummy = خطأ;
  declarator = c_parser_declarator (parser,
				    specs->typespec_kind != ctsk_none,
				    C_DTR_NORMAL, &dummy);

  إذا (!c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_error (parser, "expected %<;%>");
      إرجاع;
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
      بينما (id_declarator->kind == cdk_pointer)
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
	  شجرة type = specs->type;
	  بينما (p->kind == cdk_pointer)
	    {
	      type = build_pointer_type (type);
	      p = p->declarator;
	    }
	  c_parser_parse_ssa_name (parser, id_declarator->u.id.id, type,
				   version, ver_offset);
	}
      وإلا
	{
	  شجرة postfix_attrs = NULL_شجرة;
	  شجرة all_prefix_attrs = specs->attrs;
	  specs->attrs = عدم;
	  شجرة decl = start_decl (declarator, specs, خطأ,
				  chainon (postfix_attrs, all_prefix_attrs));
	  إذا (decl)
	    finish_decl (decl, UNKNOWN_LOCATION, NULL_شجرة, NULL_شجرة,
			 NULL_شجرة);
	}
    }
}

/* Parse gimple goto statement.  */

ساكن فراغ
c_parser_gimple_goto_stmt (gimple_parser &parser,
			   location_t loc, شجرة label, gimple_seq *seq)
{
  إذا (cfun->curr_properties & PROP_cfg)
    {
      صحيح dest_index;
      profile_probability prob;
      إذا (c_parser_gimple_parse_bb_spec_edge_probability (label, parser,
							  &dest_index, &prob))
	{
	  parser.ادفع_edge (parser.current_bb->index, dest_index,
			    EDGE_FALLTHRU, prob);
	  إرجاع;
	}
    }
  شجرة decl = lookup_label_for_goto (loc, label);
  gimple_seq_add_stmt_without_update (seq, gimple_build_goto (decl));
}

/* Parse a parenthesized condition.
   gimple-condition:
     ( gimple-binary-expression )    */

ساكن شجرة
c_parser_gimple_paren_condition (gimple_parser &parser)
{
  إذا (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    إرجاع error_mark_عقدة;
  شجرة cond
    = c_parser_gimple_ثنائي_expression (parser, boolean_type_عقدة).قيمة;
  إذا (cond != error_mark_عقدة
      && ! COMPARISON_CLASS_P (cond)
      && ! CONSTANT_CLASS_P (cond)
      && ! SSA_VAR_P (cond))
    {
      c_parser_error (parser, "comparison required");
      cond = error_mark_عقدة;
    }
  إذا (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    إرجاع error_mark_عقدة;
  إرجاع cond;
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
	  && strcmp (IDENTIFIER_POINTER (c_parser_peek_token (parser)->قيمة),
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
  شجرة t_label = NULL_شجرة, f_label = NULL_شجرة, label;
  location_t loc;
  c_parser_consume_token (parser);
  شجرة cond = c_parser_gimple_paren_condition (parser);

  إذا (c_parser_next_token_is_keyword (parser, RID_GOTO))
    {
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      إذا (! c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected label");
	  إرجاع;
	}
      label = c_parser_peek_token (parser)->قيمة;
      c_parser_consume_token (parser);
      صحيح dest_index;
      profile_probability prob;
      إذا ((cfun->curr_properties & PROP_cfg)
	  && c_parser_gimple_parse_bb_spec_edge_probability (label, parser,
							     &dest_index, &prob))
	parser.ادفع_edge (parser.current_bb->index, dest_index,
			  EDGE_TRUE_قيمة, prob);
      وإلا
	t_label = lookup_label_for_goto (loc, label);
      إذا (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	إرجاع;
    }
  وإلا
    {
      c_parser_error (parser, "expected goto expression");
      إرجاع;
    }

  إذا (c_parser_next_token_is_keyword (parser, RID_ELSE))
    c_parser_consume_token (parser);
  وإلا
    {
      c_parser_error (parser, "expected else statement");
      إرجاع;
    }

  إذا (c_parser_next_token_is_keyword (parser, RID_GOTO))
    {
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      إذا (! c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected label");
	  إرجاع;
	}
      label = c_parser_peek_token (parser)->قيمة;
      c_parser_consume_token (parser);
      صحيح dest_index;
      profile_probability prob;
      إذا ((cfun->curr_properties & PROP_cfg)
	  && c_parser_gimple_parse_bb_spec_edge_probability (label, parser,
							     &dest_index, &prob))
	parser.ادفع_edge (parser.current_bb->index, dest_index,
			  EDGE_FALSE_قيمة, prob);
      وإلا
	f_label = lookup_label_for_goto (loc, label);
      إذا (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	إرجاع;
    }
  وإلا
    {
      c_parser_error (parser, "expected goto expression");
      إرجاع;
    }

  إذا (cond != error_mark_عقدة)
    gimple_seq_add_stmt_without_update (seq, gimple_build_cond_from_شجرة (cond, t_label,
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
  c_تعبير cond_تعبير;
  شجرة case_label, label;
  auto_vec<شجرة> labels;
  شجرة default_label = NULL_شجرة;
  c_parser_consume_token (parser);

  إذا (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    إرجاع;
  cond_تعبير = c_parser_gimple_postfix_expression (parser);
  إذا (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    إرجاع;

  إذا (! c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    إرجاع;

  بينما (c_parser_next_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      إذا (c_parser_next_token_is (parser, CPP_EOF))
	{
	  c_parser_error (parser, "expected statement");
	  إرجاع;
	}

      بدل (c_parser_peek_token (parser)->keyword)
	{
	حالة RID_CASE:
	  {
	    c_تعبير exp1;
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);

	    إذا (c_parser_next_token_is (parser, CPP_NAME)
		|| c_parser_peek_token (parser)->type == CPP_العدد)
	      exp1 = c_parser_gimple_postfix_expression (parser);
	    وإلا
	      {
		c_parser_error (parser, "expected expression");
		إرجاع;
	      }

	    إذا (c_parser_next_token_is (parser, CPP_COLON))
	      {
		c_parser_consume_token (parser);
		إذا (c_parser_next_token_is (parser, CPP_NAME))
		  {
		    label = c_parser_peek_token (parser)->قيمة;
		    c_parser_consume_token (parser);
		    شجرة decl = lookup_label_for_goto (loc, label);
		    case_label = build_case_label (exp1.قيمة, NULL_شجرة,
						   decl);
		    labels.safe_ادفع (case_label);
		    إذا (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      إرجاع;
		  }
		وإلا إذا (! c_parser_require (parser, CPP_NAME,
					     "expected label"))
		  إرجاع;
	      }
	    وإلا إذا (! c_parser_require (parser, CPP_SEMICOLON,
					 "expected %<:%>"))
	      إرجاع;
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
		    label = c_parser_peek_token (parser)->قيمة;
		    c_parser_consume_token (parser);
		    شجرة decl = lookup_label_for_goto (loc, label);
		    default_label = build_case_label (NULL_شجرة, NULL_شجرة,
						      decl);
		    إذا (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      إرجاع;
		  }
		وإلا إذا (! c_parser_require (parser, CPP_NAME,
					     "expected label"))
		  إرجاع;
	      }
	    وإلا إذا (! c_parser_require (parser, CPP_SEMICOLON,
					 "expected %<:%>"))
	      إرجاع;
	    اكسر;
	  }
	افتراضي:
	  c_parser_error (parser, "expected case label");
	  إرجاع;
	}

    }
  إذا (! c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>"))
    إرجاع;

  إذا (cond_تعبير.قيمة != error_mark_عقدة)
    {
      gswitch *s = gimple_build_switch (cond_تعبير.قيمة, default_label, labels);
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
      c_finish_gimple_return (loc, NULL_شجرة);
      ret = gimple_build_return (عدم);
      gimple_seq_add_stmt_without_update (seq, ret);
    }
  وإلا
    {
      location_t xloc = c_parser_peek_token (parser)->location;
      c_تعبير تعبير = c_parser_gimple_unary_expression (parser);
      إذا (تعبير.قيمة != error_mark_عقدة)
	{
	  c_finish_gimple_return (xloc, تعبير.قيمة);
	  ret = gimple_build_return (تعبير.قيمة);
	  gimple_seq_add_stmt_without_update (seq, ret);
	}
    }
}

/* Support function for c_parser_gimple_return_stmt.  */

ساكن فراغ
c_finish_gimple_return (location_t loc, شجرة retval)
{
  شجرة valtype = شجرة_TYPE (شجرة_TYPE (current_function_decl));

  /* Use the expansion point to handle cases such as returning NULL
     in a function returning void.  */
  location_t xloc = expansion_point_location_if_in_system_header (loc);

  إذا (شجرة_THIS_VOLATILE (current_function_decl))
    warning_at (xloc, 0,
		"function declared %<noreturn%> has a %<return%> statement");

  إذا (! retval)
    current_function_returns_null = 1;
  وإلا إذا (valtype == 0 || VOID_TYPE_P (valtype))
    {
      current_function_returns_null = 1;
      إذا (شجرة_CODE (شجرة_TYPE (retval)) != VOID_TYPE)
	{
	  error_at
	    (xloc, "%<return%> with a value, in function returning void");
	  inform (DECL_SOURCE_LOCATION (current_function_decl),
		  "declared here");
	}
    }
  وإلا إذا (شجرة_CODE (valtype) != شجرة_CODE (شجرة_TYPE (retval)))
    {
      error_at
	(xloc, "invalid conversion in return statement");
      inform (DECL_SOURCE_LOCATION (current_function_decl),
	      "declared here");
    }
  إرجاع;
}
