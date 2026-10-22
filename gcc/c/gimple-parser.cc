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
  gimple_parser (c_parser *p) : parser (p), ڪنارا(), current_bb(عدم) {}
  /* c_parser is not visible here, use composition and fake inheritance
     via a conversion operator.  */
  عامل c_parser *() { أرجع parser; }
  c_parser *parser;

  /* CFG build state.  */
  صنف gimple_parser_ڪنارو
  {
  عام:
    صحيح src;
    صحيح dest;
    صحيح flags;
    profile_probability probability;
  };
  auto_vec<gimple_parser_ڪنارو> ڪنارا;
  basic_بلاڪ current_bb;

  فراغ ڌڪو_ڪنارو (صحيح, صحيح, صحيح, profile_probability);
};

فراغ
gimple_parser::ڌڪو_ڪنارو (صحيح src, صحيح dest, صحيح flags,
			  profile_probability prob)
{
  gimple_parser_ڪنارو e;
  e.src = src;
  e.dest = dest;
  e.flags = flags;
  e.probability = prob;
  ڪنارا.محفوظ_ڌڪو (e);
}


/* Gimple parsing functions.  */
ساكن منطقي c_parser_gimple_compound_statement (gimple_parser &, gimple_seq *);
ساكن فراغ c_parser_gimple_label (gimple_parser &, gimple_seq *);
ساكن فراغ c_parser_gimple_statement (gimple_parser &, gimple_seq *);
ساكن بنية c_اظهار c_parser_gimple_ٻٽو_اظهار (gimple_parser &, وڻ);
ساكن بنية c_اظهار c_parser_gimple_unary_اظهار (gimple_parser &);
ساكن بنية c_اظهار c_parser_gimple_postfix_اظهار
			(gimple_parser &, وڻ = error_mark_ڳنڍ);
ساكن بنية c_اظهار c_parser_gimple_postfix_اظهار_after_primary
			(gimple_parser &, location_t, بنية c_اظهار);
ساكن فراغ c_parser_gimple_declaration (gimple_parser &);
ساكن فراغ c_parser_gimple_goto_stmt (gimple_parser &, location_t,
				       وڻ, gimple_seq *);
ساكن فراغ c_parser_gimple_try_stmt (gimple_parser &, gimple_seq *);
ساكن فراغ c_parser_gimple_if_stmt (gimple_parser &, gimple_seq *);
ساكن فراغ c_parser_gimple_switch_stmt (gimple_parser &, gimple_seq *);
ساكن فراغ c_parser_gimple_return_stmt (gimple_parser &, gimple_seq *);
ساكن فراغ c_پڄاڻي_gimple_return (location_t, وڻ);
ساكن وڻ c_parser_gimple_paren_condition (gimple_parser &);
ساكن فراغ c_parser_gimple_اظهار_list (gimple_parser &, vec<وڻ> *);


/* Much like parser_build_unary_op, but avoid applying default conversions.  */

ساكن c_اظهار
gimple_parser_build_unary_op (location_t loc,
			      تعداد وڻ_ڪوڊ_2 ڪوڊ, بنية c_اظهار arg)
{
  بنية c_اظهار نتيجو;

  نتيجو.original_ڪوڊ = ڪوڊ;
  نتيجو.original_type = عدم;
  نتيجو.m_decimal = 0;

  إذا (reject_gcc_builtin (arg.قدر))
    {
      نتيجو.قدر = error_mark_ڳنڍ;
    }
  وإلا
    {
      نتيجو.قدر = build_unary_op (loc, ڪوڊ, arg.قدر, سچ);

      إذا (وڻ_حد_کان_مٿي_P (نتيجو.قدر) && !وڻ_حد_کان_مٿي_P (arg.قدر))
	حد_کان_مٿي_warning (loc, نتيجو.قدر, arg.قدر);
    }

  /* We are typically called when parsing a prefix token at LOC acting on
     ARG.  Reflect this by updating the source range of the result to
     start at LOC and end at the end of ARG.  */
  سيٽ_c_اظهار_ذريعو_range (&نتيجو,
			   loc, arg.get_پڄاڻي ());

  أرجع نتيجو;
}

/* See if VAL is an identifier matching __BB<num> and return <num>
   in *INDEX.  */

ساكن منطقي
c_parser_gimple_parse_bb_spec (وڻ val, صحيح *اشاريو)
{
  إذا (!startswith (IDENTIFIER_اشارو (val), "__BB"))
    أرجع خطأ;

  ثابت حرف *bb = IDENTIFIER_اشارو (val) + 4;
  إذا (! ISDIGIT (*bb))
    أرجع خطأ;

  حرف *pend;
  errno = 0;
  ثابت بنانشان ڊگهو عدد = strtoul (bb, &pend, 10);
  إذا (errno == ERANGE
      || *pend != '\0'
      || عدد > وڌ_کان_وڌ_عدد)
    أرجع خطأ;

  *اشاريو = عدد;
  أرجع سچ;
}

/* See if VAL is an identifier matching __BB<num> and return <num>
   in *INDEX.  Return true if so and parse also FREQUENCY of
   the edge.  */


ساكن منطقي
c_parser_gimple_parse_bb_spec_ڪنارو_probability (وڻ val,
						gimple_parser &parser,
						صحيح *اشاريو,
						profile_probability
						*probability)
{
  منطقي return_p = c_parser_gimple_parse_bb_spec (val, اشاريو);
  إذا (return_p)
    {
      *probability = profile_probability::uninitialized ();
      /* Parse frequency if provided.  */
      إذا (c_parser_ايندڙ_token_is (parser, CPP_OPEN_PAREN))
	{
	  وڻ f;
	  c_parser_consume_token (parser);
	  إذا (!c_parser_ايندڙ_token_is (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected frequency quality");
	      أرجع خطأ;
	    }

	  profile_quality quality;
	  ثابت حرف *v
	    = IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر);
	  إذا (!parse_profile_quality (v, &quality))
	    {
	      c_parser_error (parser, "unknown profile quality");
	      أرجع خطأ;
	    }

	  c_parser_consume_token (parser);
	  إذا (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    أرجع خطأ;

	  إذا (!c_parser_ايندڙ_token_is (parser, CPP_عدد)
	      || (وڻ_ڪوڊ (f = c_parser_peek_token (parser)->قدر)
		  != INTEGER_CST))
	    {
	      c_parser_error (parser, "expected frequency value");
	      أرجع خطأ;
	    }

	  بنانشان صحيح قدر = وڻ_INT_CST_هيٺيون (f);
	  *probability = profile_probability (قدر, quality);

	  c_parser_consume_token (parser);
	  إذا (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    أرجع خطأ;

	  إذا (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    أرجع خطأ;
	}

      أرجع سچ;
    }

  أرجع خطأ;

}

/* Parse the body of a function declaration marked with "__GIMPLE".  */

فراغ
c_parser_parse_gimple_body (c_parser *cparser, حرف *gimple_pass,
			    تعداد c_declspec_il cdil,
			    profile_ڳڻپ داخلا_bb_ڳڻپ)
{
  gimple_parser parser (cparser);
  gimple_seq seq = عدم;
  gimple_seq body = عدم;
  وڻ stmt = ڌڪو_stmt_list ();
  ڌڪو_scope ();
  location_t loc1 = c_parser_peek_token (parser)->location;

  cfun->pass_startwith = gimple_pass;
  init_وڻ_ssa (cfun);

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
      gimple_رجسٽر_cfg_hooks ();
      init_خالي_جايون_وڻ_cfg ();
      parser.current_bb = داخلا_بلاڪ_PTR_FOR_FN (cfun);
      /* Initialize the bare loop structure - we are going to only
         mark headers and leave the rest to fixup.  */
      سيٽ_loops_for_fn (cfun, ggc_cleared_alloc<بنية loops> ());
      init_loops_structure (cfun, loops_for_fn (cfun), 1);
      loops_state_سيٽ (cfun, LOOPS_NEED_FIXUP|LOOPS_MAY_HAVE_گڻو_LATCHES);
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
      gimple_seq_جوڙيو_stmt_without_update (&seq, ret);
    }

  وڻ بلاڪ = ڪڍو_scope ();
  stmt = ڪڍو_stmt_list (stmt);
  stmt = c_build_bind_اظهار (loc1, بلاڪ, stmt);

  بلاڪ = DECL_INITIAL (current_function_decl);
  بلاڪ_SUBBLOCKS (بلاڪ) = NULL_وڻ;
  بلاڪ_CHAIN (بلاڪ) = NULL_وڻ;
  وڻ_ASM_WRITTEN (بلاڪ) = 1;

  إذا (cdil == cdil_gimple)
    {
      gbind *bind_stmt = gimple_build_bind (BIND_اظهار_VARS (stmt), عدم,
					    BIND_اظهار_بلاڪ (stmt));
      gimple_bind_سيٽ_body (bind_stmt, seq);
      gimple_seq_جوڙيو_stmt_without_update (&body, bind_stmt);
      gimple_سيٽ_body (current_function_decl, body);
    }
  وإلا
    {
      /* Control-flow and binds are lowered, record local decls.  */
      لكل (وڻ var = BIND_اظهار_VARS (stmt); var; var = DECL_CHAIN (var))
	إذا (VAR_P (var)
	    && !DECL_EXTERNAL (var))
	  {
	    جوڙيو_local_decl (cfun, var);
	    /* When the middle-end re-gimplifies any expression we might
	       run into the assertion that we've seen the decl in a BIND.  */
	    إذا (!وڻ_STATIC (var))
	      DECL_ڏٺل_اندريون_BIND_اظهار_P (var) = 1;
	  }
      /* We have a CFG.  Build the edges.  */
      لكل (بنانشان i = 0; i < parser.ڪنارا.ڊيگهائي (); ++i)
	{
	  ڪنارو e = make_ڪنارو (BASIC_بلاڪ_FOR_FN (cfun, parser.ڪنارا[i].src),
			      BASIC_بلاڪ_FOR_FN (cfun, parser.ڪنارا[i].dest),
			      parser.ڪنارا[i].flags);
	  e->probability = parser.ڪنارا[i].probability;
	}
      /* Add edges for case labels.  */
      basic_بلاڪ bb;
      FOR_EACH_BB_FN (bb, cfun)
	إذا (ڪنارو_ڳڻپ (bb->succs) == 0)
	  {
	    إذا (gswitch *sw = محفوظ_dyn_cast <gswitch *> (*gsi_آخري_bb (bb)))
	      لكل (بنانشان i = 0; i < gimple_switch_انگ_labels (sw); ++i)
		{
		  basic_بلاڪ label_bb = gimple_switch_label_bb (cfun, sw, i);
		  make_ڪنارو (bb, label_bb, 0);
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
	      لكل (gsi = gsi_شروعات_bb (bb); !gsi_پڇاڙي_p (gsi);)
		{
		  gimple *stmt = gsi_stmt (gsi);
		  إذا (!gimple_call_اندروني_p (stmt, IFN_PHI))
		    اكسر;

		  gphi *phi = create_phi_ڳنڍ (gimple_call_lhs (stmt), bb);
		  لكل (بنانشان i = 0; i < gimple_call_انگ_دليلون (stmt); i += 2)
		    {
		      صحيح srcidx = وڻ_INT_CST_هيٺيون (gimple_call_arg (stmt, i));
		      ڪنارو e = ڳوليو_ڪنارو (BASIC_بلاڪ_FOR_FN (cfun, srcidx), bb);
		      إذا (!e)
			c_parser_error (parser, "edge not found");
		      وإلا
			جوڙيو_phi_arg (phi, gimple_call_arg (stmt, i + 1), e,
				     UNKNOWN_LOCATION);
		    }
		  gsi_remove (&gsi, سچ);
		}
	      لكل (; !gsi_پڇاڙي_p (gsi); gsi_ايندڙ (&gsi))
		update_stmt (gsi_stmt (gsi));
	    }
	  /* Fill SSA name gaps, putting them on the freelist and diagnose
	     SSA names without definition.  */
	  لكل (بنانشان i = 1; i < انگ_ssa_نالا; ++i)
	    إذا (!ssa_name (i))
	      {
		وڻ name = make_ssa_name_fn (cfun, integer_type_ڳنڍ, عدم, i);
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
      داخلا_بلاڪ_PTR_FOR_FN (cfun)->ڳڻپ = داخلا_bb_ڳڻپ;
      gcov_type t = param_gimple_fe_computed_hot_bb_حد;
      سيٽ_hot_bb_حد (t);
      update_max_bb_ڳڻپ ();
      cgraph_ڳنڍ::get_create (cfun->decl);
      cgraph_ڪنارو::rebuild_ڪنارا ();
    }

  /* Perform IL validation and if any error is found abort compilation
     of this function by zapping its body.  */
  إذا ((cfun->curr_properties & PROP_cfg)
      && verify_gimple_اندريون_cfg (cfun, خطأ, خطأ))
    init_خالي_جايون_وڻ_cfg ();
  وإلا إذا (!(cfun->curr_properties & PROP_cfg)
	   && verify_gimple_اندريون_seq (gimple_body (current_function_decl), خطأ))
    gimple_سيٽ_body (current_function_decl, عدم);

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
  طالما (c_parser_ايندڙ_ٽوڪن_شروعات_declaration (parser))
    {
      c_parser_gimple_declaration (parser);
      إذا (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	أرجع خطأ;
    }

  طالما (c_parser_ايندڙ_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      إذا (c_parser_error (parser))
	{
	  c_parser_skip_until_مليو (parser, CPP_CLOSE_BRACE, عدم);
	  أرجع return_p;
	}
      وإلا إذا (c_parser_ايندڙ_token_is (parser, CPP_EOF))
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
		إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME))
		  {
		    وڻ label = c_parser_peek_token (parser)->قدر;
		    c_parser_consume_token (parser);
		    c_parser_gimple_goto_stmt (parser, loc, label, seq);
		    إذا (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      أرجع return_p;
		  }
		}
	      اكسر;
	    حالة RID_RETURN:
	      return_p = سچ;
	      c_parser_gimple_return_stmt (parser, seq);
	      إذا (! c_parser_require (parser, CPP_SEMICOLON,
				      "expected %<;%>"))
		أرجع return_p;
	      إذا (cfun->curr_properties & PROP_cfg)
		parser.ڌڪو_ڪنارو (parser.current_bb->اشاريو, EXIT_بلاڪ, 0,
				  profile_probability::uninitialized ());
	      اكسر;
	    افتراضي:
	      اذهب اظهار_stmt;
	    }
	  اكسر;
	حالة CPP_NAME:
	  إذا (c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_gimple_label (parser, seq);
	      اكسر;
	    }
	  إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME)
	      && c_parser_peek_token (parser)->id_قسم == C_ID_ID
	      && strcmp (IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر),
			 "try") == 0)
	    {
	      c_parser_gimple_try_stmt (parser, seq);
	      اكسر;
	    }
	  /* Basic block specification.
	     __BB (index, ...)  */
	  إذا ((cfun->curr_properties & PROP_cfg)
	      && !strcmp (IDENTIFIER_اشارو
			    (c_parser_peek_token (parser)->قدر), "__BB"))
	    {
	      c_parser_consume_token (parser);
	      إذا (! c_parser_require (parser, CPP_OPEN_PAREN,
				      "expected %<(%>"))
		أرجع return_p;
	      إذا (c_parser_ايندڙ_token_is_not (parser, CPP_عدد))
		{
		  c_parser_error (parser, "expected block index");
		  أرجع return_p;
		}
	      وڻ tnum = c_parser_peek_token (parser)->قدر;
	      إذا (وڻ_ڪوڊ (tnum) != INTEGER_CST)
		{
		  c_parser_error (parser, "expected block index");
		  أرجع return_p;
		}
	      صحيح اشاريو = وڻ_INT_CST_هيٺيون (tnum);
	      إذا (اشاريو < انگ_FIXED_بلاڪون
		  || (اشاريو < آخري_basic_بلاڪ_for_fn (cfun)
		      && BASIC_بلاڪ_FOR_FN (cfun, اشاريو) != عدم))
		{
		  c_parser_error (parser, "invalid block index");
		  أرجع return_p;
		}
	      صحيح is_loop_سرو_جو = -1;
	      profile_ڳڻپ bb_ڳڻپ = profile_ڳڻپ::uninitialized ();
	      c_parser_consume_token (parser);
	      طالما (c_parser_ايندڙ_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  إذا (! c_parser_ايندڙ_token_is (parser, CPP_NAME))
		    {
		      c_parser_error (parser, "expected block specifier");
		      أرجع return_p;
		    }
		  /* loop_header (NUM)  */
		  إذا (!strcmp (IDENTIFIER_اشارو
			         (c_parser_peek_token (parser)->قدر),
			       "loop_header"))
		    {
		      c_parser_consume_token (parser);
		      إذا (! c_parser_require (parser, CPP_OPEN_PAREN,
					      "expected %<(%>"))
			أرجع return_p;
		      وڻ loop_انگ;
		      إذا (! c_parser_ايندڙ_token_is (parser, CPP_عدد)
			  || وڻ_ڪوڊ (loop_انگ
					  = c_parser_peek_token (parser)->قدر)
			       != INTEGER_CST)
			{
			  c_parser_error (parser, "expected loop number");
			  أرجع return_p;
			}
		      c_parser_consume_token (parser);
		      is_loop_سرو_جو = وڻ_INT_CST_هيٺيون (loop_انگ);
		      إذا (! c_parser_require (parser, CPP_CLOSE_PAREN,
					      "expected %<)%>"))
			أرجع return_p;
		    }
		  /* Parse profile: quality(value) */
		  وإلا
		    {
		      وڻ q;
		      profile_quality quality;
		      وڻ v = c_parser_peek_token (parser)->قدر;
		      إذا (!parse_profile_quality (IDENTIFIER_اشارو (v),
						  &quality))
			{
			  c_parser_error (parser, "unknown block specifier");
			  أرجع خطأ;
			}

		      c_parser_consume_token (parser);
		      إذا (!c_parser_require (parser, CPP_OPEN_PAREN,
					     "expected %<(%>"))
			أرجع خطأ;

		      إذا (!c_parser_ايندڙ_token_is (parser, CPP_عدد)
			  || (وڻ_ڪوڊ (q = c_parser_peek_token (parser)->قدر)
			      != INTEGER_CST))
			{
			  c_parser_error (parser, "expected count value");
			  أرجع خطأ;
			}

		      bb_ڳڻپ
			= profile_ڳڻپ::from_gcov_type (وڻ_INT_CST_هيٺيون (q),
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
	      إذا (!gimple_seq_خالي_جايون_p (*seq))
		{
		  إذا (!parser.current_bb)
		    c_parser_error (parser, "stmts without block");
		  وإلا
		    {
		      gimple_stmt_iterator gsi
			= gsi_شروعات_bb (parser.current_bb);
		      gsi_وجهو_seq_after_without_update (&gsi, *seq,
							   GSI_CONTINUE_LINKING);
		    }
		  *seq = عدم;
		}

	      /* Build an empty block with specified index, linking them
		 in source order.  */
	      basic_بلاڪ bb = alloc_بلاڪ ();
	      bb->اشاريو = اشاريو;
	      link_بلاڪ (bb, (parser.current_bb ? parser.current_bb
			       : داخلا_بلاڪ_PTR_FOR_FN (cfun)));
	      إذا (basic_بلاڪ_info_for_fn (cfun)->ڊيگهائي () <= (سائيز_t)اشاريو)
		vec_محفوظ_grow_cleared (basic_بلاڪ_info_for_fn (cfun),
				       اشاريو + 1, سچ);
	      سيٽ_BASIC_بلاڪ_FOR_FN (cfun, اشاريو, bb);
	      إذا (آخري_basic_بلاڪ_for_fn (cfun) <= اشاريو)
		آخري_basic_بلاڪ_for_fn (cfun) = اشاريو + 1;
	      n_basic_بلاڪون_for_fn (cfun)++;
	      إذا (parser.current_bb->اشاريو == داخلا_بلاڪ)
		parser.ڌڪو_ڪنارو (داخلا_بلاڪ, bb->اشاريو, ڪنارو_FALLTHRU,
				  profile_probability::always ());

	      /* We leave the proper setting to fixup.  */
	      صنف loop *loop_father = loops_for_fn (cfun)->وڻ_پاڙ;
	      /* If the new block is a loop header, allocate a loop
		 struct.  Fixup will take care of proper placement within
		 the loop tree.  */
	      إذا (is_loop_سرو_جو != -1)
		{
		  إذا (عدد_جو_loops (cfun) > (بنانشان)is_loop_سرو_جو
		      && get_loop (cfun, is_loop_سرو_جو) != عدم)
		    {
		      c_parser_error (parser, "duplicate loop header");
		    }
		  وإلا
		    {
		      صنف loop *loop = alloc_loop ();
		      loop->انگ = is_loop_سرو_جو;
		      loop->سرو = bb;
		      إذا (عدد_جو_loops (cfun) <= (بنانشان)is_loop_سرو_جو)
			vec_محفوظ_grow_cleared (loops_for_fn (cfun)->larray,
					       is_loop_سرو_جو + 1, سچ);
		      (*loops_for_fn (cfun)->larray)[is_loop_سرو_جو] = loop;
		      flow_loop_وڻ_ڳنڍ_جوڙيو (loops_for_fn (cfun)->وڻ_پاڙ,
					       loop);
		    }
		  loop_father = get_loop (cfun, is_loop_سرو_جو);
		}
	      bb->loop_father = loop_father;
	      bb->ڳڻپ = bb_ڳڻپ;

	      /* Stmts now go to the new block.  */
	      parser.current_bb = bb;
	      اكسر;
	    }
	  اذهب اظهار_stmt;

	حالة CPP_SEMICOLON:
	  {
	    /* Empty stmt.  */
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);
	    gimple *nop = gimple_build_nop ();
	    gimple_سيٽ_location (nop, loc);
	    gimple_seq_جوڙيو_stmt_without_update (seq, nop);
	    اكسر;
	  }

	حالة CPP_CLOSE_PAREN:
	حالة CPP_CLOSE_چورس:
	  /* Avoid infinite loop in error recovery:
	     c_parser_skip_until_found stops at a closing nesting
	     delimiter without consuming it, but here we need to consume
	     it to proceed further.  */
	  c_parser_error (parser, "expected statement");
	  c_parser_consume_token (parser);
	اكسر;

	افتراضي:
اظهار_stmt:
	  c_parser_gimple_statement (parser, seq);
	  إذا (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	    c_parser_skip_until_مليو (parser, CPP_SEMICOLON, عدم);
	}
    }
  c_parser_consume_token (parser);

  /* Put stmts parsed in the current block.  */
  إذا ((cfun->curr_properties & PROP_cfg)
      && !gimple_seq_خالي_جايون_p (*seq))
    {
      إذا (!parser.current_bb)
	c_parser_error (parser, "stmts without block");
      وإلا
	{
	  gimple_stmt_iterator gsi = gsi_شروعات_bb (parser.current_bb);
	  gsi_وجهو_seq_after_without_update (&gsi, *seq,
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
  بنية c_اظهار lhs, rhs;
  gimple *سونپيو = عدم;
  location_t loc;
  وڻ arg = NULL_وڻ;
  auto_vec<وڻ> vargs;

  lhs = c_parser_gimple_unary_اظهار (parser);
  loc = اظهار_LOCATION (lhs.قدر);
  rhs.سيٽ_error ();

  /* GIMPLE call statement without LHS.  */
  إذا (c_parser_ايندڙ_token_is (parser, CPP_SEMICOLON)
      && وڻ_ڪوڊ (lhs.قدر) == CALL_اظهار)
    {
      gimple *call;
      call = gimple_build_call_from_وڻ (lhs.قدر, عدم);
      gimple_seq_جوڙيو_stmt_without_update (seq, call);
      gimple_سيٽ_location (call, loc);
      أرجع;
    }

  /* All following cases are statements with LHS.  */
  إذا (! c_parser_require (parser, CPP_EQ, "expected %<=%>"))
    أرجع;

  /* Eat and ignore {v} right after the =, the has_volatile_ops is
     redundant and re-computed by the operand scanner.  */
  إذا (c_parser_ايندڙ_token_is (parser, CPP_OPEN_BRACE)
      && !(c_parser_peek_token (parser)->flags & PREV_WHITE)
      && c_parser_peek_2nd_token (parser)->type == CPP_NAME
      && !(c_parser_peek_2nd_token (parser)->flags & PREV_WHITE)
      && strcmp ("v", IDENTIFIER_اشارو
			(c_parser_peek_2nd_token (parser)->قدر)) == 0
      && c_parser_peek_nth_token (parser, 3)->type == CPP_CLOSE_BRACE
      && !(c_parser_peek_nth_token (parser, 3)->flags & PREV_WHITE))
    {
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }

  /* Cast expression.  */
  إذا (c_parser_ايندڙ_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_typename (c_parser_peek_2nd_token (parser)))
    {
      c_parser_consume_token (parser);
      بنية c_type_name *type_name = c_parser_type_name (parser);
      c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      إذا (type_name == عدم)
	أرجع;
      /* ???  The actual type used in the cast expression is ignored as
         in GIMPLE it is encoded by the type of the LHS.  */
      rhs = c_parser_gimple_postfix_اظهار (parser);
      إذا (lhs.قدر != error_mark_ڳنڍ
	  && rhs.قدر != error_mark_ڳنڍ)
	{
	  تعداد وڻ_ڪوڊ_2 ڪوڊ = NOP_اظهار;
	  إذا (FLOAT_TYPE_P (وڻ_TYPE (lhs.قدر))
	      && ! FLOAT_TYPE_P (وڻ_TYPE (rhs.قدر)))
	    ڪوڊ = FLOAT_اظهار;
	  وإلا إذا (! FLOAT_TYPE_P (وڻ_TYPE (lhs.قدر))
		   && FLOAT_TYPE_P (وڻ_TYPE (rhs.قدر)))
	    ڪوڊ = FIX_TRUNC_اظهار;
	  سونپيو = gimple_build_سونپيو (lhs.قدر, ڪوڊ, rhs.قدر);
	  gimple_seq_جوڙيو_stmt_without_update (seq, سونپيو);
	  gimple_سيٽ_location (سونپيو, loc);
	  أرجع;
	}
    }

  /* Unary expression.  */
  بدل (c_parser_peek_token (parser)->type)
    {
    حالة CPP_NAME:
      {
	وڻ id = c_parser_peek_token (parser)->قدر;
	إذا (strcmp (IDENTIFIER_اشارو (id), "__ABS") == 0
	    || strcmp (IDENTIFIER_اشارو (id), "__ABSU") == 0
	    || strcmp (IDENTIFIER_اشارو (id), "__MIN") == 0
	    || strcmp (IDENTIFIER_اشارو (id), "__MAX") == 0
	    || strcmp (IDENTIFIER_اشارو (id), "__BIT_INSERT") == 0
	    || strcmp (IDENTIFIER_اشارو (id), "__VEC_PERM") == 0)
	  اذهب build_unary_اظهار;
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
    build_unary_اظهار:
      rhs = c_parser_gimple_unary_اظهار (parser);
      إذا (rhs.قدر != error_mark_ڳنڍ)
	{
	  سونپيو = gimple_build_سونپيو (lhs.قدر, rhs.قدر);
	  gimple_سيٽ_location (سونپيو, loc);
	  gimple_seq_جوڙيو_stmt_without_update (seq, سونپيو);
	}
      أرجع;

    افتراضي:;
    }

  /* GIMPLE PHI statement.  */
  إذا (c_parser_ايندڙ_token_is_keyword (parser, RID_PHI))
    {
      c_parser_consume_token (parser);

      إذا (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	أرجع;

      إذا (c_parser_ايندڙ_token_is (parser, CPP_OPEN_PAREN))
	c_parser_consume_token (parser);

      طالما (c_parser_ايندڙ_token_is_not (parser, CPP_CLOSE_PAREN))
	{
	  إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      arg = c_parser_peek_token (parser)->قدر;
	      c_parser_consume_token (parser);
	      إذا (c_parser_ايندڙ_token_is (parser, CPP_COLON))
		c_parser_consume_token (parser);
	      صحيح src_اشاريو = -1;
	      إذا (!c_parser_gimple_parse_bb_spec (arg, &src_اشاريو))
		c_parser_error (parser, "invalid source block specification");
	      vargs.محفوظ_ڌڪو (سائيز_int (src_اشاريو));
	    }
	  وإلا إذا (c_parser_ايندڙ_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  وإلا
	    {
	      arg = c_parser_gimple_unary_اظهار (parser).قدر;
	      vargs.محفوظ_ڌڪو (arg);
	    }
	}

      c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");

      /* Build internal function for PHI.  */
      gcall *call_stmt = gimple_build_call_اندروني_vec (IFN_PHI, vargs);
      gimple_call_سيٽ_lhs (call_stmt, lhs.قدر);
      gimple_سيٽ_location (call_stmt, UNKNOWN_LOCATION);
      gimple_seq_جوڙيو_stmt_without_update (seq, call_stmt);
      أرجع;
    }

  /* GIMPLE call with lhs.  */
  إذا (c_parser_ايندڙ_token_is (parser, CPP_DOT)
      || (c_parser_ايندڙ_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN
	  && lookup_name (c_parser_peek_token (parser)->قدر)))
    {
      rhs = c_parser_gimple_unary_اظهار (parser);
      إذا (rhs.قدر != error_mark_ڳنڍ)
	{
	  gimple *call = gimple_build_call_from_وڻ (rhs.قدر, عدم);
	  gimple_call_سيٽ_lhs (call, lhs.قدر);
	  gimple_seq_جوڙيو_stmt_without_update (seq, call);
	  gimple_سيٽ_location (call, loc);
	}
      أرجع;
    }

  rhs = c_parser_gimple_ٻٽو_اظهار (parser, وڻ_TYPE (lhs.قدر));
  إذا (lhs.قدر != error_mark_ڳنڍ
      && rhs.قدر != error_mark_ڳنڍ)
    {
      /* If we parsed an identifier and the next token  is a '?' then parse
	 a conditional expression.  */
      إذا (SSA_VAR_P (rhs.قدر) && c_parser_ايندڙ_token_is (parser, CPP_QUERY))
	{
	  بنية c_اظهار trueval, falseval;
	  c_parser_consume_token (parser);
	  trueval = c_parser_gimple_postfix_اظهار (parser);
	  falseval.سيٽ_error ();
	  إذا (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    falseval = c_parser_gimple_postfix_اظهار (parser);
	  إذا (trueval.قدر == error_mark_ڳنڍ
	      || falseval.قدر == error_mark_ڳنڍ)
	    أرجع;
	  rhs.قدر = build3_loc (loc,
				  ويڪٽر_TYPE_P (وڻ_TYPE (rhs.قدر))
				  ? VEC_COND_اظهار : COND_اظهار,
				  وڻ_TYPE (trueval.قدر),
				  rhs.قدر, trueval.قدر, falseval.قدر);
	}
      إذا (get_gimple_rhs_class (وڻ_ڪوڊ (rhs.قدر)) == GIMPLE_INVALID_RHS)
	{
	  c_parser_error (parser, "unexpected RHS for assignment");
	  أرجع;
	}
      سونپيو = gimple_build_سونپيو (lhs.قدر, rhs.قدر);
      gimple_seq_جوڙيو_stmt_without_update (seq, سونپيو);
      gimple_سيٽ_location (سونپيو, loc);
    }
  أرجع;
}

/* A mapping between an identifier to a tree code for binary operations. */
ساكن ثابت std::pair<ثابت حرف *, وڻ_ڪوڊ_2> gimple_ٻٽو_identifier_ڪوڊ[] =
  {
    {"__MULT_HIGHPART", MULT_HIGHPART_اظهار},
    {"__UNLT", UNLT_اظهار},
    {"__UNLE", UNLE_اظهار},
    {"__UNGT", UNGT_اظهار},
    {"__UNGE", UNGE_اظهار},
    {"__UNEQ", UNEQ_اظهار},
    {"__UNORDERED", UNORDERED_اظهار},
    {"__ORDERED", ORDERED_اظهار},
    {"__LTGT", LTGT_اظهار},
    {"__FLOOR_DIV", FLOOR_DIV_اظهار},
    {"__ROUND_DIV", ڦيرو_DIV_اظهار},
    {"__EXACT_DIV", EXACT_DIV_اظهار},
    {"__CEIL_DIV", CEIL_DIV_اظهار},
    {"__FLOOR_MOD", FLOOR_MOD_اظهار},
    {"__ROUND_MOD", ڦيرو_MOD_اظهار},
    {"__CEIL_MOD", CEIL_MOD_اظهار},
    {"__ROTATE_LEFT", LROTATE_اظهار},
    {"__ROTATE_RIGHT", RROTATE_اظهار},
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

ساكن c_اظهار
c_parser_gimple_ٻٽو_اظهار (gimple_parser &parser, وڻ ret_type)
{
  /* Location of the binary operator.  */
  بنية c_اظهار ret, lhs, rhs;
  تعداد وڻ_ڪوڊ_2 ڪوڊ = ERROR_MARK;
  ret.سيٽ_error ();
  lhs = c_parser_gimple_postfix_اظهار (parser, ret_type);
  إذا (c_parser_error (parser))
    أرجع ret;
  بدل (c_parser_peek_token (parser)->type)
    {
    حالة CPP_MULT:
      ڪوڊ = MULT_اظهار;
      اكسر;
    حالة CPP_DIV:
      ڪوڊ = TRUNC_DIV_اظهار;
      اكسر;
    حالة CPP_MOD:
      ڪوڊ = TRUNC_MOD_اظهار;
      اكسر;
    حالة CPP_PLUS:
      إذا (اشارو_TYPE_P (وڻ_TYPE (lhs.قدر)))
	ڪوڊ = اشارو_PLUS_اظهار;
      وإلا
	ڪوڊ = PLUS_اظهار;
      اكسر;
    حالة CPP_MINUS:
      إذا (اشارو_TYPE_P (وڻ_TYPE (lhs.قدر)))
	ڪوڊ = اشارو_DIFF_اظهار;
      وإلا
	ڪوڊ = MINUS_اظهار;
      اكسر;
    حالة CPP_LSHIFT:
      ڪوڊ = LSHIFT_اظهار;
      اكسر;
    حالة CPP_RSHIFT:
      ڪوڊ = RSHIFT_اظهار;
      اكسر;
    حالة CPP_LESS:
      ڪوڊ = LT_اظهار;
      اكسر;
    حالة CPP_GREATER:
      ڪوڊ = GT_اظهار;
      اكسر;
    حالة CPP_LESS_EQ:
      ڪوڊ = LE_اظهار;
      اكسر;
    حالة CPP_GREATER_EQ:
      ڪوڊ = GE_اظهار;
      اكسر;
    حالة CPP_EQ_EQ:
      ڪوڊ = EQ_اظهار;
      اكسر;
    حالة CPP_NOT_EQ:
      ڪوڊ = NE_اظهار;
      اكسر;
    حالة CPP_AND:
      ڪوڊ = ٻٽو_انگ_AND_اظهار;
      اكسر;
    حالة CPP_XOR:
      ڪوڊ = ٻٽو_انگ_XOR_اظهار;
      اكسر;
    حالة CPP_OR:
      ڪوڊ = ٻٽو_انگ_IOR_اظهار;
      اكسر;
    حالة CPP_AND_AND:
      c_parser_error (parser, "%<&&%> not valid in GIMPLE");
      أرجع ret;
    حالة CPP_OR_OR:
      c_parser_error (parser, "%<||%> not valid in GIMPLE");
      أرجع ret;
    حالة CPP_NAME:
      {
	وڻ id = c_parser_peek_token (parser)->قدر;
	لكل (خودڪار &p : gimple_ٻٽو_identifier_ڪوڊ)
	  {
	    إذا (strcmp (IDENTIFIER_اشارو (id), p.پهريون) == 0)
	      {
		ڪوڊ = p.ٻيو;
		اكسر;
	      }
	  }
	إذا (ڪوڊ != ERROR_MARK)
	  اكسر;
      }
      /* Fallthru.  */
    افتراضي:
      /* Not a binary expression.  */
      أرجع lhs;
    }
  location_t ret_loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  rhs = c_parser_gimple_postfix_اظهار (parser);
  إذا (lhs.قدر != error_mark_ڳنڍ && rhs.قدر != error_mark_ڳنڍ)
    ret.قدر = build2_loc (ret_loc, ڪوڊ, ret_type, lhs.قدر, rhs.قدر);
  أرجع ret;
}

/* Parse a gimple parentized binary expression.  */

ساكن c_اظهار
c_parser_gimple_parentized_ٻٽو_اظهار (gimple_parser &parser,
					      location_t op_loc,
					      وڻ_ڪوڊ_2 ڪوڊ)
{
  بنية c_اظهار ret;
  ret.سيٽ_error ();

  c_parser_consume_token (parser);
  إذا (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    أرجع ret;
  c_اظهار op1 = c_parser_gimple_postfix_اظهار (parser);
  إذا (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    أرجع ret;
  c_اظهار op2 = c_parser_gimple_postfix_اظهار (parser);
  إذا (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    أرجع ret;

  إذا (op1.قدر != error_mark_ڳنڍ && op2.قدر != error_mark_ڳنڍ)
    ret.قدر = build2_loc (op_loc,
			    ڪوڊ, وڻ_TYPE (op1.قدر), op1.قدر, op2.قدر);
  أرجع ret;
}

/* Parse a gimple parentized binary expression.  */

ساكن c_اظهار
c_parser_gimple_parentized_ternary_اظهار (gimple_parser &parser,
					       location_t op_loc,
					       وڻ_ڪوڊ_2 ڪوڊ)
{
  بنية c_اظهار ret;
  ret.سيٽ_error ();

  c_parser_consume_token (parser);
  إذا (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    أرجع ret;
  c_اظهار op1 = c_parser_gimple_postfix_اظهار (parser);
  إذا (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    أرجع ret;
  c_اظهار op2 = c_parser_gimple_postfix_اظهار (parser);
  إذا (!c_parser_require (parser, CPP_COMMA, "expected %<)%>"))
    أرجع ret;
  c_اظهار op3 = c_parser_gimple_postfix_اظهار (parser);
  إذا (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    أرجع ret;

  إذا (op1.قدر != error_mark_ڳنڍ
      && op2.قدر != error_mark_ڳنڍ
      && op3.قدر != error_mark_ڳنڍ)
    ret.قدر = build3_loc (op_loc,
			    ڪوڊ, وڻ_TYPE (op1.قدر),
			    op1.قدر, op2.قدر, op3.قدر);
  أرجع ret;
}

/* Parse gimple unary expression.

   gimple-unary-expression:
     gimple-postfix-expression
     unary-operator gimple-postfix-expression

   unary-operator: one of
     & * + - ~ abs_expr
*/

ساكن c_اظهار
c_parser_gimple_unary_اظهار (gimple_parser &parser)
{
  بنية c_اظهار ret, op;
  location_t op_loc = c_parser_peek_token (parser)->location;
  location_t پڄاڻي;
  ret.سيٽ_error ();
  بدل (c_parser_peek_token (parser)->type)
    {
    حالة CPP_AND:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_اظهار (parser);
      mark_exp_read (op.قدر);
      أرجع gimple_parser_build_unary_op (op_loc, ADDR_اظهار, op);
    حالة CPP_MULT:
      {
	c_parser_consume_token (parser);
	op = c_parser_gimple_postfix_اظهار (parser);
	إذا (op.قدر == error_mark_ڳنڍ)
	  أرجع ret;
	إذا (! اشارو_TYPE_P (وڻ_TYPE (op.قدر)))
	  {
	    error_at (op_loc, "expected pointer as argument of unary %<*%>");
	    أرجع ret;
	  }
	پڄاڻي = op.get_پڄاڻي ();
	location_t combined_loc = make_location (op_loc, op_loc, پڄاڻي);
	ret.قدر = build_simple_mem_ref_loc (combined_loc, op.قدر);
	وڻ_SIDE_EFFECTS (ret.قدر)
	  = وڻ_THIS_VOLATILE (ret.قدر)
	  = TYPE_VOLATILE (وڻ_TYPE (وڻ_TYPE (op.قدر)));
	ret.src_range.m_شروعات = op_loc;
	ret.src_range.m_پڄاڻي = پڄاڻي;
	أرجع ret;
      }
    حالة CPP_PLUS:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_اظهار (parser);
      أرجع gimple_parser_build_unary_op (op_loc, CONVERT_اظهار, op);
    حالة CPP_MINUS:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_اظهار (parser);
      أرجع gimple_parser_build_unary_op (op_loc, NEGATE_اظهار, op);
    حالة CPP_COMPL:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_اظهار (parser);
      أرجع gimple_parser_build_unary_op (op_loc, ٻٽو_انگ_NOT_اظهار, op);
    حالة CPP_NOT:
      c_parser_error (parser, "%<!%> not valid in GIMPLE");
      أرجع ret;
    حالة CPP_KEYWORD:
      بدل (c_parser_peek_token (parser)->keyword)
	{
	حالة RID_REALPART:
	  c_parser_consume_token (parser);
	  op = c_parser_gimple_postfix_اظهار (parser);
	  أرجع gimple_parser_build_unary_op (op_loc, REALPART_اظهار, op);
	حالة RID_IMAGPART:
	  c_parser_consume_token (parser);
	  op = c_parser_gimple_postfix_اظهار (parser);
	  أرجع gimple_parser_build_unary_op (op_loc, IMAGPART_اظهار, op);
	افتراضي:
	  أرجع c_parser_gimple_postfix_اظهار (parser);
	}
    حالة CPP_NAME:
	{
	  وڻ id = c_parser_peek_token (parser)->قدر;
	  إذا (strcmp (IDENTIFIER_اشارو (id), "__ABS") == 0)
	    {
	      c_parser_consume_token (parser);
	      op = c_parser_gimple_postfix_اظهار (parser);
	      أرجع gimple_parser_build_unary_op (op_loc, ABS_اظهار, op);
	    }
	  وإلا إذا (strcmp (IDENTIFIER_اشارو (id), "__ABSU") == 0)
	    {
	      c_parser_consume_token (parser);
	      op = c_parser_gimple_postfix_اظهار (parser);
	      أرجع gimple_parser_build_unary_op (op_loc, ABSU_اظهار, op);
	    }
	  وإلا إذا (strcmp (IDENTIFIER_اشارو (id), "__MIN") == 0)
	    أرجع c_parser_gimple_parentized_ٻٽو_اظهار (parser,
								 op_loc,
								 MIN_اظهار);
	  وإلا إذا (strcmp (IDENTIFIER_اشارو (id), "__MAX") == 0)
	    أرجع c_parser_gimple_parentized_ٻٽو_اظهار (parser,
								 op_loc,
								 MAX_اظهار);
	  وإلا إذا (strcmp (IDENTIFIER_اشارو (id), "__VEC_PERM") == 0)
	    أرجع c_parser_gimple_parentized_ternary_اظهار
			(parser, op_loc, VEC_PERM_اظهار);
	  وإلا إذا (strcmp (IDENTIFIER_اشارو (id), "__BIT_INSERT") == 0)
	    {
	      /* __BIT_INSERT '(' postfix-expression, postfix-expression,
			          integer ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      إذا (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_اظهار op0 = c_parser_gimple_postfix_اظهار (parser);
		  c_parser_skip_until_مليو (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_اظهار op1 = c_parser_gimple_postfix_اظهار (parser);
		  c_parser_skip_until_مليو (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_اظهار op2 = c_parser_gimple_postfix_اظهار (parser);
		  إذا (وڻ_ڪوڊ (op2.قدر) != INTEGER_CST
		      || !int_سمائي_type_p (op2.قدر, bitsizetype))
		    c_parser_error (parser, "expected constant offset");
		  c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  إذا (op0.قدر != error_mark_ڳنڍ
		      && op1.قدر != error_mark_ڳنڍ
		      && وڻ_ڪوڊ (op2.قدر) == INTEGER_CST)
		    ret.قدر = build3_loc (loc, ٻٽو_انگ_وجهو_اظهار,
					    وڻ_TYPE (op0.قدر),
					    op0.قدر, op1.قدر,
					    fold_convert (bitsizetype,
							  op2.قدر));
		}
	      أرجع ret;
	    }
	  وإلا
	    أرجع c_parser_gimple_postfix_اظهار (parser);
	}
    افتراضي:
      أرجع c_parser_gimple_postfix_اظهار (parser);
    }
}

/* Decompose ID into base name (ID until ver_offset) and VERSION.  Return
   true if ID matches a SSA name.  */

ساكن منطقي
c_parser_parse_ssa_name_id (وڻ id, بنانشان *نسخو, بنانشان *ver_وٿي)
{
  ثابت حرف *token = IDENTIFIER_اشارو (id);
  ثابت حرف *var_نسخو = strrchr (token, '_');
  إذا (! var_نسخو)
    أرجع خطأ;

  *ver_وٿي = var_نسخو - token;
  لكل (ثابت حرف *p = var_نسخو + 1; *p; ++p)
    إذا (! ISDIGIT (*p))
      أرجع خطأ;
  *نسخو = atoi (var_نسخو + 1);
  أرجع *نسخو > 0;
}

/* Get at the actual SSA name ID with VERSION starting at VER_OFFSET.
   TYPE is the type if the SSA name is being declared.  */

ساكن وڻ
c_parser_parse_ssa_name (gimple_parser &parser,
			 وڻ id, وڻ type, بنانشان نسخو,
			 بنانشان ver_وٿي)
{
  وڻ name = NULL_وڻ;
  ثابت حرف *token = IDENTIFIER_اشارو (id);

  إذا (ver_وٿي == 0)
    {
      /* Anonymous unnamed SSA name.  */
      إذا (نسخو < انگ_ssa_نالا)
	name = ssa_name (نسخو);
      إذا (! name)
	{
	  إذا (! type)
	    {
	      c_parser_error (parser, "SSA name undeclared");
	      أرجع error_mark_ڳنڍ;
	    }
	  name = make_ssa_name_fn (cfun, type, عدم, نسخو);
	}
    }
  وإلا
    {
      إذا (نسخو < انگ_ssa_نالا)
	name = ssa_name (نسخو);
      إذا (! name)
	{
	  /* Separate var name from version.  */
	  حرف *var_name = XNEWVEC (حرف, ver_وٿي + 1);
	  يادگيري_نقل (var_name, token, ver_وٿي);
	  var_name[ver_وٿي] = '\0';
	  /* lookup for parent decl.  */
	  id = get_identifier (var_name);
	  وڻ والد = lookup_name (id);
	  XDELETEVEC (var_name);
	  إذا (! والد || والد == error_mark_ڳنڍ)
	    {
	      c_parser_error (parser, "base variable or SSA name undeclared");
	      أرجع error_mark_ڳنڍ;
	    }
	  إذا (!(VAR_P (والد)
		|| وڻ_ڪوڊ (والد) == PARM_DECL
		|| وڻ_ڪوڊ (والد) == نتيجو_DECL))
	    {
	      error ("invalid base %qE for SSA name", والد);
	      أرجع error_mark_ڳنڍ;
	    }
	  name = make_ssa_name_fn (cfun, والد,
				   gimple_build_nop (), نسخو);
	}
    }

  أرجع name;
}

/* Parse a gimple call to an internal function.

   gimple-call-internal:
     . identifier ( gimple-argument-expression-list[opt] )  */

ساكن بنية c_اظهار
c_parser_gimple_call_اندروني (gimple_parser &parser)
{
  بنية c_اظهار اظهار;
  اظهار.سيٽ_error ();

  gcc_assert (c_parser_ايندڙ_token_is (parser, CPP_DOT));
  c_parser_consume_token (parser);
  location_t loc = c_parser_peek_token (parser)->location;
  إذا (!c_parser_ايندڙ_token_is (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_قسم != C_ID_ID)
    {
      c_parser_error (parser, "expecting internal function name");
      أرجع اظهار;
    }
  وڻ id = c_parser_peek_token (parser)->قدر;
  اندروني_fn ifn = lookup_اندروني_fn (IDENTIFIER_اشارو (id));
  c_parser_consume_token (parser);
  إذا (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    {
      auto_vec<وڻ> exprlist;
      إذا (!c_parser_ايندڙ_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_gimple_اظهار_list (parser, &exprlist);
      c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      إذا (ifn == IFN_آخري)
	error_at (loc, "unknown internal function %qE", id);
      وإلا
	{
	  اظهار.قدر = build_call_اظهار_اندروني_loc_array
	    (loc, ifn, void_type_ڳنڍ, exprlist.ڊيگهائي (),
	     exprlist.پتو ());
	  اظهار.original_ڪوڊ = ERROR_MARK;
	  اظهار.original_type = عدم;
	  اظهار.m_decimal = 0;
	}
    }
  أرجع اظهار;
}

/* Parse '<' type [',' alignment] '>' and return a type on success
   and NULL_TREE on error.  */

ساكن وڻ
c_parser_gimple_typespec (gimple_parser &parser)
{
  بنية c_type_name *type_name = عدم;
  وڻ alignment = NULL_وڻ;
  إذا (c_parser_require (parser, CPP_LESS, "expected %<<%>"))
    {
      type_name = c_parser_type_name (parser);
      /* Optional alignment.  */
      إذا (c_parser_ايندڙ_token_is (parser, CPP_COMMA))
	{
	  c_parser_consume_token (parser);
	  alignment
	      = c_parser_gimple_postfix_اظهار (parser).قدر;
	}
      c_parser_skip_until_مليو (parser,
				 CPP_GREATER, "expected %<>%>");
    }
  إذا (!type_name)
    أرجع NULL_وڻ;
  وڻ tem;
  وڻ type = groktypename (type_name, &tem, عدم);
  إذا (alignment)
    type = build_aligned_type (type, وڻ_منزل_uhwi (alignment));
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

ساكن بنية c_اظهار
c_parser_gimple_postfix_اظهار (gimple_parser &parser, وڻ ret_type)
{
  location_t loc = c_parser_peek_token (parser)->location;
  ذريعو_range tok_range = c_parser_peek_token (parser)->get_range ();
  بنية c_اظهار اظهار;
  اظهار.سيٽ_error ();
  بدل (c_parser_peek_token (parser)->type)
    {
    حالة CPP_عدد:
      اظهار.قدر = c_parser_peek_token (parser)->قدر;
      سيٽ_c_اظهار_ذريعو_range (&اظهار, tok_range);
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      اكسر;
    حالة CPP_CHAR:
    حالة CPP_CHAR16:
    حالة CPP_CHAR32:
    حالة CPP_UTF8CHAR:
    حالة CPP_WCHAR:
      اظهار.قدر = c_parser_peek_token (parser)->قدر;
      سيٽ_c_اظهار_ذريعو_range (&اظهار, tok_range);
      c_parser_consume_token (parser);
      اكسر;
    حالة CPP_STRING:
    حالة CPP_STRING16:
    حالة CPP_STRING32:
    حالة CPP_WSTRING:
    حالة CPP_UTF8STRING:
      اظهار = c_parser_string_literal (parser, خطأ, سچ);
      اكسر;
    حالة CPP_DOT:
      اظهار = c_parser_gimple_call_اندروني (parser);
      اكسر;
    حالة CPP_NAME:
      إذا (c_parser_peek_token (parser)->id_قسم == C_ID_ID)
	{
	  وڻ id = c_parser_peek_token (parser)->قدر;
	  إذا (strcmp (IDENTIFIER_اشارو (id), "__MEM") == 0)
	    {
	      /* __MEM '<' type-name [ ',' number ] '>'
	               '(' [ '(' type-name ')' ] unary-expression
			   [ '+' number ]
			   [ ',' number ]
			   [ ',' number ':' number ] ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      وڻ type = c_parser_gimple_typespec (parser);
	      بنية c_اظهار ptr, alias_off, قدم, اشاريو, index2;
	      ptr.قدر = error_mark_ڳنڍ;
	      alias_off.قدر = NULL_وڻ;
	      قدم.قدر = NULL_وڻ;
	      اشاريو.قدر = NULL_وڻ;
	      index2.قدر = NULL_وڻ;
	      بنانشان ننڍو clique = 0;
	      بنانشان ننڍو بنياد = 0;
	      منطقي ابتو_ترتيب = خطأ;
	      بنية c_اظهار ro;
	      إذا (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  وڻ alias_type = NULL_وڻ;
		  /* Optional alias-type cast.  */
		  إذا (c_parser_ايندڙ_token_is (parser, CPP_OPEN_PAREN))
		    {
		      c_parser_consume_token (parser);
		      بنية c_type_name *alias_type_name
			= c_parser_type_name (parser);
		      c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN,
						 "expected %<)%>");
		      إذا (alias_type_name)
			{
			  وڻ tem;
			  alias_type = groktypename (alias_type_name,
						     &tem, عدم);
			}
		    }
		  ptr = c_parser_gimple_unary_اظهار (parser);
		  إذا (ptr.قدر == error_mark_ڳنڍ
		      || ! اشارو_TYPE_P (وڻ_TYPE (ptr.قدر)))
		    {
		      إذا (ptr.قدر != error_mark_ڳنڍ)
			error_at (ptr.get_شروعات (),
				  "invalid type of %<__MEM%> operand");
		      c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN,
						 "expected %<)%>");
		      أرجع اظهار;
		    }
		  إذا (! alias_type)
		    alias_type = وڻ_TYPE (ptr.قدر);
		  /* Optional constant offset.  */
		  إذا (c_parser_ايندڙ_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      alias_off = c_parser_gimple_postfix_اظهار (parser);
		    }
		  إذا (c_parser_ايندڙ_token_is (parser, CPP_MULT))
		    {
		      std::مٽا_سٽا (اشاريو, alias_off);
		      c_parser_consume_token (parser);
		      قدم = c_parser_gimple_postfix_اظهار (parser);
		    }
		  وإلا إذا (c_parser_ايندڙ_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      اشاريو = c_parser_gimple_postfix_اظهار (parser);
		      إذا (c_parser_ايندڙ_token_is (parser, CPP_MULT))
			{
			  c_parser_consume_token (parser);
			  قدم = c_parser_gimple_postfix_اظهار (parser);
			}
		      وإلا
			std::مٽا_سٽا (اشاريو, index2);
		    }
		  وإلا إذا (alias_off.قدر
			   && وڻ_ڪوڊ (alias_off.قدر) != INTEGER_CST)
		    std::مٽا_سٽا (alias_off, index2);
		  إذا (c_parser_ايندڙ_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      index2 = c_parser_gimple_postfix_اظهار (parser);
		    }
		  إذا (alias_off.قدر)
		    {
		      إذا (وڻ_ڪوڊ (alias_off.قدر) != INTEGER_CST)
			error_at (alias_off.get_شروعات (),
				  "expected constant offset for %<__MEM%> "
				  "operand");
		      alias_off.قدر = fold_convert (alias_type,
						      alias_off.قدر);
		    }
		  وإلا
		    alias_off.قدر = build_int_cst (alias_type, 0);
		  إذا (قدم.قدر)
		    {
		      إذا (وڻ_ڪوڊ (قدم.قدر) != INTEGER_CST)
			error_at (قدم.get_شروعات (),
				  "expected constant step for %<__MEM%> "
				  "operand");
		    }
		  إذا (c_parser_ايندڙ_token_is (parser, CPP_COMMA))
		    {
		      بنية c_اظهار cl, ba;
		      منطقي has_clb = سچ;
		      c_parser_consume_token (parser);
		      cl = c_parser_gimple_postfix_اظهار (parser);
		      إذا (!c_parser_ايندڙ_token_is (parser, CPP_COLON))
			{
			  ro = cl;
			  بنانشان HOST_WIDE_INT tmp = 0;
			  إذا (!وڻ_سمائي_uhwi_p (ro.قدر)
			      || (tmp = وڻ_منزل_uhwi (ro.قدر)) > 1)
			    error_at (ro.get_شروعات (),
				      "invalid reverse order value");
			  ابتو_ترتيب = tmp;
			  has_clb = خطأ;
			  إذا (c_parser_ايندڙ_token_is (parser, CPP_COMMA))
			    {
			      c_parser_consume_token (parser);
			      cl = c_parser_gimple_postfix_اظهار (parser);
		              has_clb = سچ;
			    }
			}
		      إذا (has_clb
			  && c_parser_require (parser,
					       CPP_COLON, "expected %<:%>"))
			{
			  ba = c_parser_gimple_postfix_اظهار (parser);
			  إذا (!وڻ_سمائي_uhwi_p (cl.قدر)
			      || !وڻ_سمائي_uhwi_p (ba.قدر)
			      || compare_وڻ_int (cl.قدر,
						   (clique = وڻ_منزل_uhwi
								(cl.قدر)))
			      || compare_وڻ_int (ba.قدر,
						   (بنياد = وڻ_منزل_uhwi
								 (ba.قدر))))
			    error_at (cl.get_شروعات (),
				      "invalid clique/base pair");
			}
		    }
		  c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      إذا (! type || c_parser_error (parser))
		{
		  c_parser_سيٽ_error (parser, خطأ);
		  أرجع اظهار;
		}
	      إذا (اشاريو.قدر || قدم.قدر || index2.قدر)
		اظهار.قدر = build5_loc (loc, هدف_MEM_REF,
					 type, ptr.قدر, alias_off.قدر,
					 اشاريو.قدر, قدم.قدر, index2.قدر);
	      وإلا
		اظهار.قدر = build2_loc (loc, MEM_REF,
					 type, ptr.قدر, alias_off.قدر);
	      إذا (clique != 0)
		{
		  cfun->آخري_clique = MAX (cfun->آخري_clique, clique);
		  MR_DEPENDENCE_CLIQUE (اظهار.قدر) = clique;
		  MR_DEPENDENCE_بنياد (اظهار.قدر) = بنياد;
		}
	      إذا (ابتو_ترتيب)
		{
		  إذا (وڻ_ڪوڊ (اظهار.قدر) == MEM_REF)
		    REF_ابتو_STORAGE_ترتيب (اظهار.قدر) = ابتو_ترتيب;
		  وإلا
		    error_at (ro.get_شروعات (),
			      "target mem ref cannot have reverse order");
		}
	      اكسر;
	    }
	  وإلا إذا (strcmp (IDENTIFIER_اشارو (id), "__VIEW_CONVERT") == 0)
	    {
	      /* __VIEW_CONVERT '<' type-name [ ',' number ] '>'
	                        '(' postfix-expression ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      وڻ type = c_parser_gimple_typespec (parser);
	      إذا (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_اظهار op = c_parser_gimple_postfix_اظهار (parser);
		  c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  إذا (type && op.قدر != error_mark_ڳنڍ)
		    اظهار.قدر = build1_loc (loc, VIEW_CONVERT_اظهار,
					     type, op.قدر);
		}
	      اكسر;
	    }
	  وإلا إذا (strcmp (IDENTIFIER_اشارو (id), "__BIT_FIELD_REF") == 0)
	    {
	      /* __BIT_FIELD_REF '<' type-name [ ',' number ] '>'
	                        '(' postfix-expression, integer, integer ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      وڻ type = c_parser_gimple_typespec (parser);
	      إذا (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_اظهار op0 = c_parser_gimple_postfix_اظهار (parser);
		  c_parser_skip_until_مليو (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_اظهار op1 = c_parser_gimple_postfix_اظهار (parser);
		  إذا (وڻ_ڪوڊ (op1.قدر) != INTEGER_CST
		      || !int_سمائي_type_p (op1.قدر, bitsizetype))
		    c_parser_error (parser, "expected constant size");
		  c_parser_skip_until_مليو (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_اظهار op2 = c_parser_gimple_postfix_اظهار (parser);
		  إذا (وڻ_ڪوڊ (op2.قدر) != INTEGER_CST
		      || !int_سمائي_type_p (op2.قدر, bitsizetype))
		    c_parser_error (parser, "expected constant offset");
		  c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  إذا (type
		      && op0.قدر != error_mark_ڳنڍ
		      && وڻ_ڪوڊ (op1.قدر) == INTEGER_CST
		      && وڻ_ڪوڊ (op2.قدر) == INTEGER_CST)
		    اظهار.قدر = build3_loc (loc, ٻٽو_انگ_ميدان_REF, type,
					     op0.قدر,
					     fold_convert (bitsizetype,
							   op1.قدر),
					     fold_convert (bitsizetype,
							   op2.قدر));
		}
	      اكسر;
	    }
	  وإلا إذا (strcmp (IDENTIFIER_اشارو (id), "__CLOBBER") == 0)
	    {
	      /* __CLOBBER [ '(' bob | eob | bos | eos ')' ]  */
	      clobber_قسم قسم = CLOBBER_UNDEF;
	      c_parser_consume_token (parser);
	      إذا (c_parser_ايندڙ_token_is (parser, CPP_OPEN_PAREN))
		{
		  c_parser_consume_token (parser);
		  خودڪار tok = c_parser_peek_token (parser);
		  إذا (c_parser_require (parser, CPP_NAME,
					"expected clobber kind"))
		    {
		      ثابت حرف *قسم_str = IDENTIFIER_اشارو (tok->قدر);
		      إذا (strcmp (قسم_str, "bos") == 0)
			قسم = CLOBBER_STORAGE_BEGIN;
		      وإلا إذا (strcmp (قسم_str, "bob") == 0)
			قسم = CLOBBER_OBJECT_BEGIN;
		      وإلا إذا (strcmp (قسم_str, "eob") == 0)
			قسم = CLOBBER_OBJECT_پڇاڙي;
		      وإلا إذا (strcmp (قسم_str, "eos") == 0)
			قسم = CLOBBER_STORAGE_پڇاڙي;
		      وإلا
			c_parser_error (parser, "expected one of %<bos%>, "
					"%<eos%>, %<bob>, %<eob%>");
		    }
		  c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      /* We infer the (redundant) type from the LHS.  */
	      اظهار.قدر = build_clobber (ret_type, قسم);
	      اكسر;
	    }
	  وإلا إذا (strcmp (IDENTIFIER_اشارو (id), "_Literal") == 0)
	    {
	      /* _Literal '(' type-name ')' ( [ '-' ] constant | constructor ) */
	      c_parser_consume_token (parser);
	      وڻ type = NULL_وڻ;
	      إذا (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  بنية c_type_name *type_name = c_parser_type_name (parser);
		  وڻ tem;
		  إذا (type_name)
		    type = groktypename (type_name, &tem, عدم);
		  c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      إذا (! type)
		{
		  c_parser_error (parser, "invalid _Literal");
		  أرجع اظهار;
		}
	      إذا (c_parser_ايندڙ_token_is (parser, CPP_OPEN_BRACE))
		{
		  c_parser_consume_token (parser);
		  إذا (!AGGREGATE_TYPE_P (type)
		      && !ويڪٽر_TYPE_P (type))
		    {
		      c_parser_error (parser, "invalid type for _Literal with "
				      "constructor");
		      c_parser_skip_until_مليو (parser, CPP_CLOSE_BRACE,
						 "expected %<}%>");
		      أرجع اظهار;
		    }
		  vec<constructor_elt, va_gc> *v = عدم;
		  منطقي constant_p = سچ;
		  إذا (ويڪٽر_TYPE_P (type)
		      && !c_parser_ايندڙ_token_is (parser, CPP_CLOSE_BRACE))
		    {
		      vec_alloc (v, TYPE_ويڪٽر_SUBPARTS (type).منزل_constant ());
		      افعل
			{
			  وڻ val
			    = c_parser_gimple_postfix_اظهار (parser).قدر;
			  إذا (! val
			      || val == error_mark_ڳنڍ
			      || (! CONSTANT_CLASS_P (val)
				  && ! SSA_VAR_P (val)))
			    {
			      c_parser_error (parser, "invalid _Literal");
			      أرجع اظهار;
			    }
			  CONSTRUCTOR_APPEND_ELT (v, NULL_وڻ, val);
			  إذا (! CONSTANT_CLASS_P (val))
			    constant_p = خطأ;
			  إذا (c_parser_ايندڙ_token_is (parser, CPP_COMMA))
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
			اظهار.قدر = build_ويڪٽر_from_ctor (type, v);
		      وإلا
			اظهار.قدر = build_constructor (type, v);
		    }
		  وإلا
		    {
		      c_parser_skip_until_مليو (parser, CPP_CLOSE_BRACE,
						 "expected %<}%>");
		      أرجع اظهار;
		    }
		}
	      وإلا
		{
		  منطقي neg_p, addr_p;
		  إذا ((neg_p = c_parser_ايندڙ_token_is (parser, CPP_MINUS)))
		    c_parser_consume_token (parser);
		  إذا ((addr_p = c_parser_ايندڙ_token_is (parser, CPP_AND)))
		    c_parser_consume_token (parser);
		  وڻ val = c_parser_gimple_postfix_اظهار (parser).قدر;
		  إذا (! val
		      || val == error_mark_ڳنڍ
		      || (!CONSTANT_CLASS_P (val) && !addr_p))
		    {
		      c_parser_error (parser, "invalid _Literal");
		      أرجع اظهار;
		    }
		  إذا (addr_p)
		    {
		      val = build1 (ADDR_اظهار, type, val);
		      إذا (!is_gimple_invariant_پتو (val))
			{
			  c_parser_error (parser, "invalid _Literal");
			  أرجع اظهار;
			}
		    }
		  إذا (neg_p)
		    {
		      val = const_unop (NEGATE_اظهار, وڻ_TYPE (val), val);
		      إذا (! val)
			{
			  c_parser_error (parser, "invalid _Literal");
			  أرجع اظهار;
			}
		    }
		  اظهار.قدر = fold_convert (type, val);
		}
	      أرجع اظهار;
	    }

	  /* SSA name.  */
	  بنانشان نسخو, ver_وٿي;
	  إذا (! lookup_name (id)
	      && c_parser_parse_ssa_name_id (id, &نسخو, &ver_وٿي))
	    {
	      c_parser_consume_token (parser);
	      اظهار.قدر = c_parser_parse_ssa_name (parser, id, NULL_وڻ,
						    نسخو, ver_وٿي);
	      إذا (اظهار.قدر == error_mark_ڳنڍ)
		أرجع اظهار;
	      سيٽ_c_اظهار_ذريعو_range (&اظهار, tok_range);
	      /* For default definition SSA names.  */
	      إذا (c_parser_ايندڙ_token_is (parser, CPP_OPEN_PAREN)
		  && c_parser_peek_2nd_token (parser)->type == CPP_NAME
		  && strcmp ("D",
			     IDENTIFIER_اشارو
			       (c_parser_peek_2nd_token (parser)->قدر)) == 0
		  && c_parser_peek_nth_token (parser, 3)->type == CPP_CLOSE_PAREN)
		{
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		  إذا (! SSA_NAME_IS_DEFAULT_DEF (اظهار.قدر))
		    {
		      إذا (!SSA_NAME_VAR (اظهار.قدر))
			{
			  error_at (loc, "anonymous SSA name cannot have"
				    " default definition");
			  اظهار.قدر = error_mark_ڳنڍ;
			  أرجع اظهار;
			}
		      سيٽ_ssa_default_def (cfun, SSA_NAME_VAR (اظهار.قدر),
					   اظهار.قدر);
		      SSA_NAME_DEF_STMT (اظهار.قدر) = gimple_build_nop ();
		    }
		}
	    }
	  وإلا
	    {
	      c_parser_consume_token (parser);
	      اظهار.قدر
		= build_external_ref (loc, id,
				      (c_parser_peek_token (parser)->type
				       == CPP_OPEN_PAREN), &اظهار.original_type);
	      سيٽ_c_اظهار_ذريعو_range (&اظهار, tok_range);
	    }
	  اكسر;
	}
      /* Fallthru.  */
    افتراضي:
      c_parser_error (parser, "expected expression");
      اظهار.سيٽ_error ();
      اكسر;
    }
  إذا (اظهار.قدر == error_mark_ڳنڍ)
    أرجع اظهار;
  أرجع c_parser_gimple_postfix_اظهار_after_primary
    (parser, اظهار_LOC_OR_LOC (اظهار.قدر, loc), اظهار);
}

/* Parse a gimple postfix expression after the initial primary or compound
   literal.  */

ساكن بنية c_اظهار
c_parser_gimple_postfix_اظهار_after_primary (gimple_parser &parser,
						  location_t اظهار_loc,
						  بنية c_اظهار اظهار)
{
  location_t شروعات;
  location_t پڄاڻي;
  وڻ ident;
  location_t comp_loc;

  طالما (سچ)
    {
      location_t op_loc = c_parser_peek_token (parser)->location;
      بدل (c_parser_peek_token (parser)->type)
	{
	حالة CPP_OPEN_چورس:
	  {
	    c_parser_consume_token (parser);
	    وڻ idx = c_parser_gimple_unary_اظهار (parser).قدر;

	    إذا (! c_parser_require (parser, CPP_CLOSE_چورس, "expected %<]%>"))
	      {
		c_parser_skip_until_مليو (parser, CPP_CLOSE_چورس, عدم);
		اكسر;
	      }

	    شروعات = اظهار.get_شروعات ();
	    پڄاڻي = c_parser_ٽوڪن_buf (parser, 0)->location;
	    اظهار.قدر = build_array_ref (op_loc, اظهار.قدر, idx);
	    سيٽ_c_اظهار_ذريعو_range (&اظهار, شروعات, پڄاڻي);
	    اظهار.m_decimal = 0;

	    اظهار.original_ڪوڊ = ERROR_MARK;
	    اظهار.original_type = عدم;
	    اكسر;
	  }
	حالة CPP_OPEN_PAREN:
	  {
	    /* Function call.  */
	    c_parser_consume_token (parser);
	    auto_vec<وڻ> exprlist;
	    إذا (! c_parser_ايندڙ_token_is (parser, CPP_CLOSE_PAREN))
	      c_parser_gimple_اظهار_list (parser, &exprlist);
	    c_parser_skip_until_مليو (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    إذا (!FUNC_OR_طريقو_TYPE_P (وڻ_TYPE (اظهار.قدر)))
	      {
		c_parser_error (parser, "invalid call to non-function");
		اظهار.سيٽ_error ();
		اكسر;
	      }
	    اظهار.قدر = build_call_array_loc
		(اظهار_loc, وڻ_TYPE (وڻ_TYPE (اظهار.قدر)),
		 اظهار.قدر, exprlist.ڊيگهائي (), exprlist.پتو ());
	    اظهار.m_decimal = 0;
	    اظهار.original_ڪوڊ = ERROR_MARK;
	    اظهار.original_type = عدم;
	    اكسر;
	  }
	حالة CPP_DOT:
	  {
	    /* Structure element reference.  */
	    c_parser_consume_token (parser);
	    إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		ident = comp_tok->قدر;
		comp_loc = comp_tok->location;
	      }
	    وإلا
	      {
		c_parser_error (parser, "expected identifier");
		اظهار.سيٽ_error ();
		اظهار.original_ڪوڊ = ERROR_MARK;
		اظهار.original_type = عدم;
		أرجع اظهار;
	      }
	    شروعات = اظهار.get_شروعات ();
	    پڄاڻي = c_parser_peek_token (parser)->get_پڄاڻي ();
	    c_parser_consume_token (parser);
	    اظهار.قدر = build_component_ref (op_loc, اظهار.قدر, ident,
					      comp_loc, UNKNOWN_LOCATION);
	    سيٽ_c_اظهار_ذريعو_range (&اظهار, شروعات, پڄاڻي);
	    اظهار.m_decimal = 0;
	    اظهار.original_ڪوڊ = ERROR_MARK;
	    إذا (وڻ_ڪوڊ (اظهار.قدر) != COMPONENT_REF)
	      اظهار.original_type = عدم;
	    وإلا
	      {
		/* Remember the original type of a bitfield.  */
		وڻ ميدان_2 = وڻ_عمليو (اظهار.قدر, 1);
		إذا (وڻ_ڪوڊ (ميدان_2) != ميدان_DECL)
		  اظهار.original_type = عدم;
		وإلا
		  اظهار.original_type = DECL_ٻٽو_انگ_ميدان_TYPE (ميدان_2);
	      }
	    اكسر;
	  }
	حالة CPP_DEREF:
	  {
	    /* Structure element reference.  */
	    إذا (!اشارو_TYPE_P (وڻ_TYPE (اظهار.قدر)))
	      {
		c_parser_error (parser, "dereference of non-pointer");
		اظهار.سيٽ_error ();
		اظهار.original_ڪوڊ = ERROR_MARK;
		اظهار.original_type = عدم;
		أرجع اظهار;
	      }
	    c_parser_consume_token (parser);
	    إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		ident = comp_tok->قدر;
		comp_loc = comp_tok->location;
	      }
	    وإلا
	      {
		c_parser_error (parser, "expected identifier");
		اظهار.سيٽ_error ();
		اظهار.original_ڪوڊ = ERROR_MARK;
		اظهار.original_type = عدم;
		أرجع اظهار;
	      }
	    شروعات = اظهار.get_شروعات ();
	    پڄاڻي = c_parser_peek_token (parser)->get_پڄاڻي ();
	    c_parser_consume_token (parser);
	    اظهار.قدر = build_component_ref (op_loc,
					      build_simple_mem_ref_loc
					        (op_loc, اظهار.قدر),
					      ident, comp_loc,
					      اظهار.get_location ());
	    سيٽ_c_اظهار_ذريعو_range (&اظهار, شروعات, پڄاڻي);
	    اظهار.m_decimal = 0;
	    اظهار.original_ڪوڊ = ERROR_MARK;
	    إذا (وڻ_ڪوڊ (اظهار.قدر) != COMPONENT_REF)
	      اظهار.original_type = عدم;
	    وإلا
	      {
		/* Remember the original type of a bitfield.  */
		وڻ ميدان_2 = وڻ_عمليو (اظهار.قدر, 1);
		إذا (وڻ_ڪوڊ (ميدان_2) != ميدان_DECL)
		  اظهار.original_type = عدم;
		وإلا
		  اظهار.original_type = DECL_ٻٽو_انگ_ميدان_TYPE (ميدان_2);
	      }
	    اكسر;
	  }
	افتراضي:
	  أرجع اظهار;
	}
    }
}

/* Parse expression list.

   gimple-expr-list:
     gimple-unary-expression
     gimple-expr-list , gimple-unary-expression

 */

ساكن فراغ
c_parser_gimple_اظهار_list (gimple_parser &parser, vec<وڻ> *ret)
{
  بنية c_اظهار اظهار;

  اظهار = c_parser_gimple_unary_اظهار (parser);
  ret->محفوظ_ڌڪو (اظهار.قدر);
  طالما (c_parser_ايندڙ_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      اظهار = c_parser_gimple_unary_اظهار (parser);
      ret->محفوظ_ڌڪو (اظهار.قدر);
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
  وڻ name = c_parser_peek_token (parser)->قدر;
  location_t loc1 = c_parser_peek_token (parser)->location;
  gcc_assert (c_parser_ايندڙ_token_is (parser, CPP_NAME));
  c_parser_consume_token (parser);
  gcc_assert (c_parser_ايندڙ_token_is (parser, CPP_COLON));
  c_parser_consume_token (parser);
  وڻ label = define_label (loc1, name);
  إذا (label)
    gimple_seq_جوڙيو_stmt_without_update (seq, gimple_build_label (label));
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
  إذا (c_parser_ايندڙ_token_is_not (parser, CPP_OPEN_PAREN))
    أرجع;
  c_parser_consume_token (parser);

  specs->داخلا_bb_ڳڻپ = profile_ڳڻپ::uninitialized ();
  طالما (c_parser_ايندڙ_token_is (parser, CPP_NAME))
    {
      profile_quality quality;
      ثابت حرف *op = IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر);
      c_parser_consume_token (parser);
      إذا (! strcmp (op, "startwith"))
	{
	  إذا (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    أرجع;
	  إذا (c_parser_ايندڙ_token_is_not (parser, CPP_STRING))
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"expected pass name");
	      أرجع;
	    }
	  pass = xstrdup (وڻ_STRING_اشارو
			  (c_parser_string_literal (parser, خطأ,
						    خطأ).قدر));
	  إذا (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<(%>"))
	    أرجع;
	}
      وإلا إذا (parse_profile_quality (op, &quality))
	{
	  وڻ q;
	  إذا (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    أرجع;

	  إذا (!c_parser_ايندڙ_token_is (parser, CPP_عدد)
	      || (وڻ_ڪوڊ (q = c_parser_peek_token (parser)->قدر)
		  != INTEGER_CST))
	    {
	      c_parser_error (parser, "expected count value");
	      أرجع;
	    }

	  specs->داخلا_bb_ڳڻپ
	    = profile_ڳڻپ::from_gcov_type (وڻ_INT_CST_هيٺيون (q), quality);
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
     إذا (c_parser_ايندڙ_token_is (parser, CPP_COMMA))
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
رجسٽر

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
  c_parser_declspecs (parser, specs, سچ, سچ, سچ,
		      سچ, سچ, سچ, سچ, cla_nonabstract_decl);
  پڄاڻي_declspecs (specs);

  /* Provide better error recovery.  Note that a type name here is usually
     better diagnosed as a redeclaration.  */
  إذا (c_parser_ايندڙ_token_starts_declspecs (parser)
      && ! c_parser_ايندڙ_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<;%>");
      c_parser_سيٽ_error (parser, خطأ);
      أرجع;
    }

  منطقي dummy = خطأ;
  declarator = c_parser_declarator (parser,
				    specs->typespec_قسم != ctsk_none,
				    C_DTR_عام, &dummy);

  إذا (!c_parser_ايندڙ_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_error (parser, "expected %<;%>");
      أرجع;
    }
  إذا (declarator)
    {
      /* Handle SSA name decls specially, they do not go into the identifier
         table but we simply build the SSA name for later lookup.  */
      بنانشان نسخو, ver_وٿي;
      /* Handle SSA pointer declarations in a very simplistic ways, we
	 probably would like to call grokdeclarator in a special mode to
	 just build the type of the decl - start_decl already pushes
	 the identifier to the bindings for lookup, something we do not
	 want.  */
      بنية c_declarator *id_declarator = declarator;
      طالما (id_declarator->قسم == cdk_اشارو)
	id_declarator = id_declarator->declarator;
      إذا (id_declarator->قسم == cdk_id
	  && (declarator->قسم == cdk_اشارو
	      || is_gimple_reg_type (specs->type))
	  && c_parser_parse_ssa_name_id (id_declarator->u.id.id,
					 &نسخو, &ver_وٿي)
	  /* The following restricts it to unnamed anonymous SSA names
	     which fails parsing of named ones in dumps (we could
	     decide to not dump their name for -gimple).  */
	  && ver_وٿي == 0)
	{
	  بنية c_declarator *p = declarator;
	  وڻ type = specs->type;
	  طالما (p->قسم == cdk_اشارو)
	    {
	      type = build_اشارو_type (type);
	      p = p->declarator;
	    }
	  c_parser_parse_ssa_name (parser, id_declarator->u.id.id, type,
				   نسخو, ver_وٿي);
	}
      وإلا
	{
	  وڻ postfix_attrs = NULL_وڻ;
	  وڻ all_اڳياڙي_attrs = specs->attrs;
	  specs->attrs = عدم;
	  وڻ decl = شروعات_decl (declarator, specs, خطأ,
				  chainon (postfix_attrs, all_اڳياڙي_attrs));
	  إذا (decl)
	    پڄاڻي_decl (decl, UNKNOWN_LOCATION, NULL_وڻ, NULL_وڻ,
			 NULL_وڻ);
	}
    }
}

/* Parse gimple goto statement.  */

ساكن فراغ
c_parser_gimple_goto_stmt (gimple_parser &parser,
			   location_t loc, وڻ label, gimple_seq *seq)
{
  إذا (cfun->curr_properties & PROP_cfg)
    {
      صحيح dest_اشاريو;
      profile_probability prob;
      إذا (c_parser_gimple_parse_bb_spec_ڪنارو_probability (label, parser,
							  &dest_اشاريو, &prob))
	{
	  parser.ڌڪو_ڪنارو (parser.current_bb->اشاريو, dest_اشاريو,
			    ڪنارو_FALLTHRU, prob);
	  أرجع;
	}
    }
  وڻ decl = lookup_label_for_goto (loc, label);
  gimple_seq_جوڙيو_stmt_without_update (seq, gimple_build_goto (decl));
}

/* Parse a parenthesized condition.
   gimple-condition:
     ( gimple-binary-expression )    */

ساكن وڻ
c_parser_gimple_paren_condition (gimple_parser &parser)
{
  إذا (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    أرجع error_mark_ڳنڍ;
  وڻ cond
    = c_parser_gimple_ٻٽو_اظهار (parser, boolean_type_ڳنڍ).قدر;
  إذا (cond != error_mark_ڳنڍ
      && ! COMPARISON_CLASS_P (cond)
      && ! CONSTANT_CLASS_P (cond)
      && ! SSA_VAR_P (cond))
    {
      c_parser_error (parser, "comparison required");
      cond = error_mark_ڳنڍ;
    }
  إذا (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    أرجع error_mark_ڳنڍ;
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

  إذا ((c_parser_ايندڙ_token_is (parser, CPP_KEYWORD)
       && c_parser_peek_token (parser)->keyword == RID_AT_FINALLY)
      || (c_parser_ايندڙ_token_is (parser, CPP_NAME)
	  && c_parser_peek_token (parser)->id_قسم == C_ID_ID
	  && strcmp (IDENTIFIER_اشارو (c_parser_peek_token (parser)->قدر),
		     "finally") == 0))
    {
      gimple_seq finseq = عدم;
      c_parser_consume_token (parser);
      c_parser_gimple_compound_statement (parser, &finseq);

      إذا (c_parser_ايندڙ_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_ELSE)
	{
	  gimple_seq elsseq = عدم;
	  c_parser_consume_token (parser);
	  c_parser_gimple_compound_statement (parser, &elsseq);

	  geh_else *stmt = gimple_build_eh_else (finseq, elsseq);
	  finseq = عدم;
	  gimple_seq_جوڙيو_stmt_without_update (&finseq, stmt);
	}

      gtry *stmt = gimple_build_try (tryseq, finseq, GIMPLE_TRY_FINALLY);
      gimple_seq_جوڙيو_stmt_without_update (seq, stmt);
    }
  وإلا إذا (c_parser_ايندڙ_token_is (parser, CPP_KEYWORD)
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
  وڻ t_label = NULL_وڻ, f_label = NULL_وڻ, label;
  location_t loc;
  c_parser_consume_token (parser);
  وڻ cond = c_parser_gimple_paren_condition (parser);

  إذا (c_parser_ايندڙ_token_is_keyword (parser, RID_GOTO))
    {
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      إذا (! c_parser_ايندڙ_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected label");
	  أرجع;
	}
      label = c_parser_peek_token (parser)->قدر;
      c_parser_consume_token (parser);
      صحيح dest_اشاريو;
      profile_probability prob;
      إذا ((cfun->curr_properties & PROP_cfg)
	  && c_parser_gimple_parse_bb_spec_ڪنارو_probability (label, parser,
							     &dest_اشاريو, &prob))
	parser.ڌڪو_ڪنارو (parser.current_bb->اشاريو, dest_اشاريو,
			  ڪنارو_TRUE_قدر, prob);
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

  إذا (c_parser_ايندڙ_token_is_keyword (parser, RID_ELSE))
    c_parser_consume_token (parser);
  وإلا
    {
      c_parser_error (parser, "expected else statement");
      أرجع;
    }

  إذا (c_parser_ايندڙ_token_is_keyword (parser, RID_GOTO))
    {
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      إذا (! c_parser_ايندڙ_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected label");
	  أرجع;
	}
      label = c_parser_peek_token (parser)->قدر;
      c_parser_consume_token (parser);
      صحيح dest_اشاريو;
      profile_probability prob;
      إذا ((cfun->curr_properties & PROP_cfg)
	  && c_parser_gimple_parse_bb_spec_ڪنارو_probability (label, parser,
							     &dest_اشاريو, &prob))
	parser.ڌڪو_ڪنارو (parser.current_bb->اشاريو, dest_اشاريو,
			  ڪنارو_FALSE_قدر, prob);
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

  إذا (cond != error_mark_ڳنڍ)
    gimple_seq_جوڙيو_stmt_without_update (seq, gimple_build_cond_from_وڻ (cond, t_label,
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
  c_اظهار cond_اظهار;
  وڻ case_label, label;
  auto_vec<وڻ> labels;
  وڻ default_label = NULL_وڻ;
  c_parser_consume_token (parser);

  إذا (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    أرجع;
  cond_اظهار = c_parser_gimple_postfix_اظهار (parser);
  إذا (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    أرجع;

  إذا (! c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    أرجع;

  طالما (c_parser_ايندڙ_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      إذا (c_parser_ايندڙ_token_is (parser, CPP_EOF))
	{
	  c_parser_error (parser, "expected statement");
	  أرجع;
	}

      بدل (c_parser_peek_token (parser)->keyword)
	{
	حالة RID_CASE:
	  {
	    c_اظهار exp1;
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);

	    إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME)
		|| c_parser_peek_token (parser)->type == CPP_عدد)
	      exp1 = c_parser_gimple_postfix_اظهار (parser);
	    وإلا
	      {
		c_parser_error (parser, "expected expression");
		أرجع;
	      }

	    إذا (c_parser_ايندڙ_token_is (parser, CPP_COLON))
	      {
		c_parser_consume_token (parser);
		إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME))
		  {
		    label = c_parser_peek_token (parser)->قدر;
		    c_parser_consume_token (parser);
		    وڻ decl = lookup_label_for_goto (loc, label);
		    case_label = build_case_label (exp1.قدر, NULL_وڻ,
						   decl);
		    labels.محفوظ_ڌڪو (case_label);
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
	    إذا (c_parser_ايندڙ_token_is (parser, CPP_COLON))
	      {
		c_parser_consume_token (parser);
		إذا (c_parser_ايندڙ_token_is (parser, CPP_NAME))
		  {
		    label = c_parser_peek_token (parser)->قدر;
		    c_parser_consume_token (parser);
		    وڻ decl = lookup_label_for_goto (loc, label);
		    default_label = build_case_label (NULL_وڻ, NULL_وڻ,
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

  إذا (cond_اظهار.قدر != error_mark_ڳنڍ)
    {
      gswitch *s = gimple_build_switch (cond_اظهار.قدر, default_label, labels);
      gimple_seq_جوڙيو_stmt_without_update (seq, s);
    }
}

/* Parse gimple return statement.  */

ساكن فراغ
c_parser_gimple_return_stmt (gimple_parser &parser, gimple_seq *seq)
{
  location_t loc = c_parser_peek_token (parser)->location;
  gimple *ret = عدم;
  c_parser_consume_token (parser);
  إذا (c_parser_ايندڙ_token_is (parser, CPP_SEMICOLON))
    {
      c_پڄاڻي_gimple_return (loc, NULL_وڻ);
      ret = gimple_build_return (عدم);
      gimple_seq_جوڙيو_stmt_without_update (seq, ret);
    }
  وإلا
    {
      location_t xloc = c_parser_peek_token (parser)->location;
      c_اظهار اظهار = c_parser_gimple_unary_اظهار (parser);
      إذا (اظهار.قدر != error_mark_ڳنڍ)
	{
	  c_پڄاڻي_gimple_return (xloc, اظهار.قدر);
	  ret = gimple_build_return (اظهار.قدر);
	  gimple_seq_جوڙيو_stmt_without_update (seq, ret);
	}
    }
}

/* Support function for c_parser_gimple_return_stmt.  */

ساكن فراغ
c_پڄاڻي_gimple_return (location_t loc, وڻ retval)
{
  وڻ valtype = وڻ_TYPE (وڻ_TYPE (current_function_decl));

  /* Use the expansion point to handle cases such as returning NULL
     in a function returning void.  */
  location_t xloc = expansion_نقطو_location_if_اندريون_system_سرو (loc);

  إذا (وڻ_THIS_VOLATILE (current_function_decl))
    warning_at (xloc, 0,
		"function declared %<noreturn%> has a %<return%> statement");

  إذا (! retval)
    current_function_returns_null = 1;
  وإلا إذا (valtype == 0 || VOID_TYPE_P (valtype))
    {
      current_function_returns_null = 1;
      إذا (وڻ_ڪوڊ (وڻ_TYPE (retval)) != VOID_TYPE)
	{
	  error_at
	    (xloc, "%<return%> with a value, in function returning void");
	  inform (DECL_ذريعو_LOCATION (current_function_decl),
		  "declared here");
	}
    }
  وإلا إذا (وڻ_ڪوڊ (valtype) != وڻ_ڪوڊ (وڻ_TYPE (retval)))
    {
      error_at
	(xloc, "invalid conversion in return statement");
      inform (DECL_ذريعو_LOCATION (current_function_decl),
	      "declared here");
    }
  أرجع;
}
