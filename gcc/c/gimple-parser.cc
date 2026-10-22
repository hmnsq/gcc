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
  gimple_parser (c_parser *p) : parser (p), څنډې(), current_bb(عدم) {}
  /* c_parser is not visible here, use composition and fake inheritance
     via a conversion operator.  */
  چلوونکی c_parser *() { أرجع parser; }
  c_parser *parser;

  /* CFG build state.  */
  صنف gimple_parser_څنډه
  {
  عام:
    صحيح src;
    صحيح dest;
    صحيح flags;
    profile_probability probability;
  };
  auto_vec<gimple_parser_څنډه> څنډې;
  basic_بلاک current_bb;

  فراغ ټېل_څنډه (صحيح, صحيح, صحيح, profile_probability);
};

فراغ
gimple_parser::ټېل_څنډه (صحيح src, صحيح dest, صحيح flags,
			  profile_probability prob)
{
  gimple_parser_څنډه e;
  e.src = src;
  e.dest = dest;
  e.flags = flags;
  e.probability = prob;
  څنډې.خوندي_ټېل (e);
}


/* Gimple parsing functions.  */
ساكن منطقي c_parser_gimple_compound_statement (gimple_parser &, gimple_seq *);
ساكن فراغ c_parser_gimple_label (gimple_parser &, gimple_seq *);
ساكن فراغ c_parser_gimple_statement (gimple_parser &, gimple_seq *);
ساكن بنية c_بیان c_parser_gimple_دوګونی_افاده (gimple_parser &, ونه);
ساكن بنية c_بیان c_parser_gimple_unary_افاده (gimple_parser &);
ساكن بنية c_بیان c_parser_gimple_postfix_افاده
			(gimple_parser &, ونه = error_mark_غوټه);
ساكن بنية c_بیان c_parser_gimple_postfix_افاده_after_primary
			(gimple_parser &, location_t, بنية c_بیان);
ساكن فراغ c_parser_gimple_declaration (gimple_parser &);
ساكن فراغ c_parser_gimple_goto_stmt (gimple_parser &, location_t,
				       ونه, gimple_seq *);
ساكن فراغ c_parser_gimple_try_stmt (gimple_parser &, gimple_seq *);
ساكن فراغ c_parser_gimple_if_stmt (gimple_parser &, gimple_seq *);
ساكن فراغ c_parser_gimple_switch_stmt (gimple_parser &, gimple_seq *);
ساكن فراغ c_parser_gimple_return_stmt (gimple_parser &, gimple_seq *);
ساكن فراغ c_پای_gimple_return (location_t, ونه);
ساكن ونه c_parser_gimple_paren_condition (gimple_parser &);
ساكن فراغ c_parser_gimple_بیان_list (gimple_parser &, vec<ونه> *);


/* Much like parser_build_unary_op, but avoid applying default conversions.  */

ساكن c_بیان
gimple_parser_build_unary_op (location_t loc,
			      تعداد ونه_کوډ_2 کوډ, بنية c_بیان arg)
{
  بنية c_بیان پایله;

  پایله.original_کوډ = کوډ;
  پایله.original_type = عدم;
  پایله.m_decimal = 0;

  إذا (reject_gcc_builtin (arg.ارزښت))
    {
      پایله.ارزښت = error_mark_غوټه;
    }
  وإلا
    {
      پایله.ارزښت = build_unary_op (loc, کوډ, arg.ارزښت, ریښتیا);

      إذا (ونه_ډکېدنه_P (پایله.ارزښت) && !ونه_ډکېدنه_P (arg.ارزښت))
	ډکېدنه_warning (loc, پایله.ارزښت, arg.ارزښت);
    }

  /* We are typically called when parsing a prefix token at LOC acting on
     ARG.  Reflect this by updating the source range of the result to
     start at LOC and end at the end of ARG.  */
  سېټ_c_بیان_سرچینه_range (&پایله,
			   loc, arg.get_پای ());

  أرجع پایله;
}

/* See if VAL is an identifier matching __BB<num> and return <num>
   in *INDEX.  */

ساكن منطقي
c_parser_gimple_parse_bb_spec (ونه val, صحيح *شاخص)
{
  إذا (!startswith (IDENTIFIER_اشاره_ګر (val), "__BB"))
    أرجع خطأ;

  ثابت حرف *bb = IDENTIFIER_اشاره_ګر (val) + 4;
  إذا (! ISDIGIT (*bb))
    أرجع خطأ;

  حرف *pend;
  errno = 0;
  ثابت بینښه اوږد شمېره = strtoul (bb, &pend, 10);
  إذا (errno == ERANGE
      || *pend != '\0'
      || شمېره > لوی_عدد)
    أرجع خطأ;

  *شاخص = شمېره;
  أرجع ریښتیا;
}

/* See if VAL is an identifier matching __BB<num> and return <num>
   in *INDEX.  Return true if so and parse also FREQUENCY of
   the edge.  */


ساكن منطقي
c_parser_gimple_parse_bb_spec_څنډه_probability (ونه val,
						gimple_parser &parser,
						صحيح *شاخص,
						profile_probability
						*probability)
{
  منطقي return_p = c_parser_gimple_parse_bb_spec (val, شاخص);
  إذا (return_p)
    {
      *probability = profile_probability::uninitialized ();
      /* Parse frequency if provided.  */
      إذا (c_parser_بل_token_is (parser, CPP_OPEN_PAREN))
	{
	  ونه f;
	  c_parser_consume_token (parser);
	  إذا (!c_parser_بل_token_is (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected frequency quality");
	      أرجع خطأ;
	    }

	  profile_quality quality;
	  ثابت حرف *v
	    = IDENTIFIER_اشاره_ګر (c_parser_peek_token (parser)->ارزښت);
	  إذا (!parse_profile_quality (v, &quality))
	    {
	      c_parser_error (parser, "unknown profile quality");
	      أرجع خطأ;
	    }

	  c_parser_consume_token (parser);
	  إذا (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    أرجع خطأ;

	  إذا (!c_parser_بل_token_is (parser, CPP_شمېره)
	      || (ونه_کوډ (f = c_parser_peek_token (parser)->ارزښت)
		  != INTEGER_CST))
	    {
	      c_parser_error (parser, "expected frequency value");
	      أرجع خطأ;
	    }

	  بینښه صحيح ارزښت = ونه_INT_CST_ټیټ (f);
	  *probability = profile_probability (ارزښت, quality);

	  c_parser_consume_token (parser);
	  إذا (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    أرجع خطأ;

	  إذا (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    أرجع خطأ;
	}

      أرجع ریښتیا;
    }

  أرجع خطأ;

}

/* Parse the body of a function declaration marked with "__GIMPLE".  */

فراغ
c_parser_parse_gimple_body (c_parser *cparser, حرف *gimple_pass,
			    تعداد c_declspec_il cdil,
			    profile_شمېر ثبت_bb_شمېر)
{
  gimple_parser parser (cparser);
  gimple_seq seq = عدم;
  gimple_seq body = عدم;
  ونه stmt = ټېل_stmt_list ();
  ټېل_scope ();
  location_t loc1 = c_parser_peek_token (parser)->location;

  cfun->pass_startwith = gimple_pass;
  init_ونه_ssa (cfun);

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
      gimple_ثبتوونکی_cfg_hooks ();
      init_تشه_ونه_cfg ();
      parser.current_bb = ثبت_بلاک_PTR_FOR_FN (cfun);
      /* Initialize the bare loop structure - we are going to only
         mark headers and leave the rest to fixup.  */
      سېټ_loops_for_fn (cfun, ggc_cleared_alloc<بنية loops> ());
      init_loops_structure (cfun, loops_for_fn (cfun), 1);
      loops_state_سېټ (cfun, LOOPS_NEED_FIXUP|LOOPS_MAY_HAVE_مضرب_LATCHES);
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
      gimple_seq_جمع_کړه_stmt_without_update (&seq, ret);
    }

  ونه بلاک = راوباسه_scope ();
  stmt = راوباسه_stmt_list (stmt);
  stmt = c_build_bind_بیان (loc1, بلاک, stmt);

  بلاک = DECL_INITIAL (current_function_decl);
  بلاک_SUBBLOCKS (بلاک) = NULL_ونه;
  بلاک_CHAIN (بلاک) = NULL_ونه;
  ونه_ASM_WRITTEN (بلاک) = 1;

  إذا (cdil == cdil_gimple)
    {
      gbind *bind_stmt = gimple_build_bind (BIND_بیان_VARS (stmt), عدم,
					    BIND_بیان_بلاک (stmt));
      gimple_bind_سېټ_body (bind_stmt, seq);
      gimple_seq_جمع_کړه_stmt_without_update (&body, bind_stmt);
      gimple_سېټ_body (current_function_decl, body);
    }
  وإلا
    {
      /* Control-flow and binds are lowered, record local decls.  */
      لكل (ونه var = BIND_بیان_VARS (stmt); var; var = DECL_CHAIN (var))
	إذا (VAR_P (var)
	    && !DECL_EXTERNAL (var))
	  {
	    جمع_کړه_local_decl (cfun, var);
	    /* When the middle-end re-gimplifies any expression we might
	       run into the assertion that we've seen the decl in a BIND.  */
	    إذا (!ونه_STATIC (var))
	      DECL_کتل_شوی_دننه_BIND_بیان_P (var) = 1;
	  }
      /* We have a CFG.  Build the edges.  */
      لكل (بینښه i = 0; i < parser.څنډې.اوږدتیا (); ++i)
	{
	  څنډه e = make_څنډه (BASIC_بلاک_FOR_FN (cfun, parser.څنډې[i].src),
			      BASIC_بلاک_FOR_FN (cfun, parser.څنډې[i].dest),
			      parser.څنډې[i].flags);
	  e->probability = parser.څنډې[i].probability;
	}
      /* Add edges for case labels.  */
      basic_بلاک bb;
      FOR_EACH_BB_FN (bb, cfun)
	إذا (څنډه_شمېر (bb->succs) == 0)
	  {
	    إذا (gswitch *sw = خوندي_dyn_cast <gswitch *> (*gsi_وروستی_bb (bb)))
	      لكل (بینښه i = 0; i < gimple_switch_عدد_labels (sw); ++i)
		{
		  basic_بلاک label_bb = gimple_switch_label_bb (cfun, sw, i);
		  make_څنډه (bb, label_bb, 0);
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
	      لكل (gsi = gsi_پیل_bb (bb); !gsi_پای_ټکی_p (gsi);)
		{
		  gimple *stmt = gsi_stmt (gsi);
		  إذا (!gimple_call_دننی_p (stmt, IFN_PHI))
		    اكسر;

		  gphi *phi = create_phi_غوټه (gimple_call_lhs (stmt), bb);
		  لكل (بینښه i = 0; i < gimple_call_عدد_دلیلونه (stmt); i += 2)
		    {
		      صحيح srcidx = ونه_INT_CST_ټیټ (gimple_call_arg (stmt, i));
		      څنډه e = پیدا_کړه_څنډه (BASIC_بلاک_FOR_FN (cfun, srcidx), bb);
		      إذا (!e)
			c_parser_error (parser, "edge not found");
		      وإلا
			جمع_کړه_phi_arg (phi, gimple_call_arg (stmt, i + 1), e,
				     UNKNOWN_LOCATION);
		    }
		  gsi_remove (&gsi, ریښتیا);
		}
	      لكل (; !gsi_پای_ټکی_p (gsi); gsi_بل (&gsi))
		update_stmt (gsi_stmt (gsi));
	    }
	  /* Fill SSA name gaps, putting them on the freelist and diagnose
	     SSA names without definition.  */
	  لكل (بینښه i = 1; i < عدد_ssa_نومونه; ++i)
	    إذا (!ssa_name (i))
	      {
		ونه name = make_ssa_name_fn (cfun, integer_type_غوټه, عدم, i);
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
      ثبت_بلاک_PTR_FOR_FN (cfun)->شمېر = ثبت_bb_شمېر;
      gcov_type t = param_gimple_fe_computed_hot_bb_پوله;
      سېټ_hot_bb_پوله (t);
      update_max_bb_شمېر ();
      cgraph_غوټه::get_create (cfun->decl);
      cgraph_څنډه::rebuild_څنډې ();
    }

  /* Perform IL validation and if any error is found abort compilation
     of this function by zapping its body.  */
  إذا ((cfun->curr_properties & PROP_cfg)
      && verify_gimple_دننه_cfg (cfun, خطأ, خطأ))
    init_تشه_ونه_cfg ();
  وإلا إذا (!(cfun->curr_properties & PROP_cfg)
	   && verify_gimple_دننه_seq (gimple_body (current_function_decl), خطأ))
    gimple_سېټ_body (current_function_decl, عدم);

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
  طالما (c_parser_بل_نښې_پیل_declaration (parser))
    {
      c_parser_gimple_declaration (parser);
      إذا (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	أرجع خطأ;
    }

  طالما (c_parser_بل_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      إذا (c_parser_error (parser))
	{
	  c_parser_skip_until_وموندل (parser, CPP_CLOSE_BRACE, عدم);
	  أرجع return_p;
	}
      وإلا إذا (c_parser_بل_token_is (parser, CPP_EOF))
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
		إذا (c_parser_بل_token_is (parser, CPP_NAME))
		  {
		    ونه label = c_parser_peek_token (parser)->ارزښت;
		    c_parser_consume_token (parser);
		    c_parser_gimple_goto_stmt (parser, loc, label, seq);
		    إذا (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      أرجع return_p;
		  }
		}
	      اكسر;
	    حالة RID_RETURN:
	      return_p = ریښتیا;
	      c_parser_gimple_return_stmt (parser, seq);
	      إذا (! c_parser_require (parser, CPP_SEMICOLON,
				      "expected %<;%>"))
		أرجع return_p;
	      إذا (cfun->curr_properties & PROP_cfg)
		parser.ټېل_څنډه (parser.current_bb->شاخص, EXIT_بلاک, 0,
				  profile_probability::uninitialized ());
	      اكسر;
	    افتراضي:
	      اذهب بیان_stmt;
	    }
	  اكسر;
	حالة CPP_NAME:
	  إذا (c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_gimple_label (parser, seq);
	      اكسر;
	    }
	  إذا (c_parser_بل_token_is (parser, CPP_NAME)
	      && c_parser_peek_token (parser)->id_ډول == C_ID_ID
	      && strcmp (IDENTIFIER_اشاره_ګر (c_parser_peek_token (parser)->ارزښت),
			 "try") == 0)
	    {
	      c_parser_gimple_try_stmt (parser, seq);
	      اكسر;
	    }
	  /* Basic block specification.
	     __BB (index, ...)  */
	  إذا ((cfun->curr_properties & PROP_cfg)
	      && !strcmp (IDENTIFIER_اشاره_ګر
			    (c_parser_peek_token (parser)->ارزښت), "__BB"))
	    {
	      c_parser_consume_token (parser);
	      إذا (! c_parser_require (parser, CPP_OPEN_PAREN,
				      "expected %<(%>"))
		أرجع return_p;
	      إذا (c_parser_بل_token_is_not (parser, CPP_شمېره))
		{
		  c_parser_error (parser, "expected block index");
		  أرجع return_p;
		}
	      ونه tnum = c_parser_peek_token (parser)->ارزښت;
	      إذا (ونه_کوډ (tnum) != INTEGER_CST)
		{
		  c_parser_error (parser, "expected block index");
		  أرجع return_p;
		}
	      صحيح شاخص = ونه_INT_CST_ټیټ (tnum);
	      إذا (شاخص < عدد_FIXED_بلاکونه
		  || (شاخص < وروستی_basic_بلاک_for_fn (cfun)
		      && BASIC_بلاک_FOR_FN (cfun, شاخص) != عدم))
		{
		  c_parser_error (parser, "invalid block index");
		  أرجع return_p;
		}
	      صحيح is_loop_سرلیک_د = -1;
	      profile_شمېر bb_شمېر = profile_شمېر::uninitialized ();
	      c_parser_consume_token (parser);
	      طالما (c_parser_بل_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  إذا (! c_parser_بل_token_is (parser, CPP_NAME))
		    {
		      c_parser_error (parser, "expected block specifier");
		      أرجع return_p;
		    }
		  /* loop_header (NUM)  */
		  إذا (!strcmp (IDENTIFIER_اشاره_ګر
			         (c_parser_peek_token (parser)->ارزښت),
			       "loop_header"))
		    {
		      c_parser_consume_token (parser);
		      إذا (! c_parser_require (parser, CPP_OPEN_PAREN,
					      "expected %<(%>"))
			أرجع return_p;
		      ونه loop_عدد;
		      إذا (! c_parser_بل_token_is (parser, CPP_شمېره)
			  || ونه_کوډ (loop_عدد
					  = c_parser_peek_token (parser)->ارزښت)
			       != INTEGER_CST)
			{
			  c_parser_error (parser, "expected loop number");
			  أرجع return_p;
			}
		      c_parser_consume_token (parser);
		      is_loop_سرلیک_د = ونه_INT_CST_ټیټ (loop_عدد);
		      إذا (! c_parser_require (parser, CPP_CLOSE_PAREN,
					      "expected %<)%>"))
			أرجع return_p;
		    }
		  /* Parse profile: quality(value) */
		  وإلا
		    {
		      ونه q;
		      profile_quality quality;
		      ونه v = c_parser_peek_token (parser)->ارزښت;
		      إذا (!parse_profile_quality (IDENTIFIER_اشاره_ګر (v),
						  &quality))
			{
			  c_parser_error (parser, "unknown block specifier");
			  أرجع خطأ;
			}

		      c_parser_consume_token (parser);
		      إذا (!c_parser_require (parser, CPP_OPEN_PAREN,
					     "expected %<(%>"))
			أرجع خطأ;

		      إذا (!c_parser_بل_token_is (parser, CPP_شمېره)
			  || (ونه_کوډ (q = c_parser_peek_token (parser)->ارزښت)
			      != INTEGER_CST))
			{
			  c_parser_error (parser, "expected count value");
			  أرجع خطأ;
			}

		      bb_شمېر
			= profile_شمېر::from_gcov_type (ونه_INT_CST_ټیټ (q),
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
	      إذا (!gimple_seq_تشه_p (*seq))
		{
		  إذا (!parser.current_bb)
		    c_parser_error (parser, "stmts without block");
		  وإلا
		    {
		      gimple_stmt_iterator gsi
			= gsi_پیل_bb (parser.current_bb);
		      gsi_ورننباسه_seq_after_without_update (&gsi, *seq,
							   GSI_CONTINUE_LINKING);
		    }
		  *seq = عدم;
		}

	      /* Build an empty block with specified index, linking them
		 in source order.  */
	      basic_بلاک bb = alloc_بلاک ();
	      bb->شاخص = شاخص;
	      link_بلاک (bb, (parser.current_bb ? parser.current_bb
			       : ثبت_بلاک_PTR_FOR_FN (cfun)));
	      إذا (basic_بلاک_info_for_fn (cfun)->اوږدتیا () <= (اندازه_t)شاخص)
		vec_خوندي_grow_cleared (basic_بلاک_info_for_fn (cfun),
				       شاخص + 1, ریښتیا);
	      سېټ_BASIC_بلاک_FOR_FN (cfun, شاخص, bb);
	      إذا (وروستی_basic_بلاک_for_fn (cfun) <= شاخص)
		وروستی_basic_بلاک_for_fn (cfun) = شاخص + 1;
	      n_basic_بلاکونه_for_fn (cfun)++;
	      إذا (parser.current_bb->شاخص == ثبت_بلاک)
		parser.ټېل_څنډه (ثبت_بلاک, bb->شاخص, څنډه_FALLTHRU,
				  profile_probability::always ());

	      /* We leave the proper setting to fixup.  */
	      صنف loop *loop_father = loops_for_fn (cfun)->ونه_ریښه;
	      /* If the new block is a loop header, allocate a loop
		 struct.  Fixup will take care of proper placement within
		 the loop tree.  */
	      إذا (is_loop_سرلیک_د != -1)
		{
		  إذا (شمېره_د_loops (cfun) > (بینښه)is_loop_سرلیک_د
		      && get_loop (cfun, is_loop_سرلیک_د) != عدم)
		    {
		      c_parser_error (parser, "duplicate loop header");
		    }
		  وإلا
		    {
		      صنف loop *loop = alloc_loop ();
		      loop->عدد = is_loop_سرلیک_د;
		      loop->سرلیک = bb;
		      إذا (شمېره_د_loops (cfun) <= (بینښه)is_loop_سرلیک_د)
			vec_خوندي_grow_cleared (loops_for_fn (cfun)->larray,
					       is_loop_سرلیک_د + 1, ریښتیا);
		      (*loops_for_fn (cfun)->larray)[is_loop_سرلیک_د] = loop;
		      flow_loop_ونه_غوټه_جمع_کړه (loops_for_fn (cfun)->ونه_ریښه,
					       loop);
		    }
		  loop_father = get_loop (cfun, is_loop_سرلیک_د);
		}
	      bb->loop_father = loop_father;
	      bb->شمېر = bb_شمېر;

	      /* Stmts now go to the new block.  */
	      parser.current_bb = bb;
	      اكسر;
	    }
	  اذهب بیان_stmt;

	حالة CPP_SEMICOLON:
	  {
	    /* Empty stmt.  */
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);
	    gimple *nop = gimple_build_nop ();
	    gimple_سېټ_location (nop, loc);
	    gimple_seq_جمع_کړه_stmt_without_update (seq, nop);
	    اكسر;
	  }

	حالة CPP_CLOSE_PAREN:
	حالة CPP_CLOSE_مربع:
	  /* Avoid infinite loop in error recovery:
	     c_parser_skip_until_found stops at a closing nesting
	     delimiter without consuming it, but here we need to consume
	     it to proceed further.  */
	  c_parser_error (parser, "expected statement");
	  c_parser_consume_token (parser);
	اكسر;

	افتراضي:
بیان_stmt:
	  c_parser_gimple_statement (parser, seq);
	  إذا (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	    c_parser_skip_until_وموندل (parser, CPP_SEMICOLON, عدم);
	}
    }
  c_parser_consume_token (parser);

  /* Put stmts parsed in the current block.  */
  إذا ((cfun->curr_properties & PROP_cfg)
      && !gimple_seq_تشه_p (*seq))
    {
      إذا (!parser.current_bb)
	c_parser_error (parser, "stmts without block");
      وإلا
	{
	  gimple_stmt_iterator gsi = gsi_پیل_bb (parser.current_bb);
	  gsi_ورننباسه_seq_after_without_update (&gsi, *seq,
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
  بنية c_بیان lhs, rhs;
  gimple *ټاکل = عدم;
  location_t loc;
  ونه arg = NULL_ونه;
  auto_vec<ونه> vargs;

  lhs = c_parser_gimple_unary_افاده (parser);
  loc = بیان_LOCATION (lhs.ارزښت);
  rhs.سېټ_error ();

  /* GIMPLE call statement without LHS.  */
  إذا (c_parser_بل_token_is (parser, CPP_SEMICOLON)
      && ونه_کوډ (lhs.ارزښت) == CALL_بیان)
    {
      gimple *call;
      call = gimple_build_call_from_ونه (lhs.ارزښت, عدم);
      gimple_seq_جمع_کړه_stmt_without_update (seq, call);
      gimple_سېټ_location (call, loc);
      أرجع;
    }

  /* All following cases are statements with LHS.  */
  إذا (! c_parser_require (parser, CPP_EQ, "expected %<=%>"))
    أرجع;

  /* Eat and ignore {v} right after the =, the has_volatile_ops is
     redundant and re-computed by the operand scanner.  */
  إذا (c_parser_بل_token_is (parser, CPP_OPEN_BRACE)
      && !(c_parser_peek_token (parser)->flags & PREV_WHITE)
      && c_parser_peek_2nd_token (parser)->type == CPP_NAME
      && !(c_parser_peek_2nd_token (parser)->flags & PREV_WHITE)
      && strcmp ("v", IDENTIFIER_اشاره_ګر
			(c_parser_peek_2nd_token (parser)->ارزښت)) == 0
      && c_parser_peek_nth_token (parser, 3)->type == CPP_CLOSE_BRACE
      && !(c_parser_peek_nth_token (parser, 3)->flags & PREV_WHITE))
    {
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }

  /* Cast expression.  */
  إذا (c_parser_بل_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_typename (c_parser_peek_2nd_token (parser)))
    {
      c_parser_consume_token (parser);
      بنية c_type_name *type_name = c_parser_type_name (parser);
      c_parser_skip_until_وموندل (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      إذا (type_name == عدم)
	أرجع;
      /* ???  The actual type used in the cast expression is ignored as
         in GIMPLE it is encoded by the type of the LHS.  */
      rhs = c_parser_gimple_postfix_افاده (parser);
      إذا (lhs.ارزښت != error_mark_غوټه
	  && rhs.ارزښت != error_mark_غوټه)
	{
	  تعداد ونه_کوډ_2 کوډ = NOP_بیان;
	  إذا (FLOAT_TYPE_P (ونه_TYPE (lhs.ارزښت))
	      && ! FLOAT_TYPE_P (ونه_TYPE (rhs.ارزښت)))
	    کوډ = FLOAT_بیان;
	  وإلا إذا (! FLOAT_TYPE_P (ونه_TYPE (lhs.ارزښت))
		   && FLOAT_TYPE_P (ونه_TYPE (rhs.ارزښت)))
	    کوډ = FIX_TRUNC_بیان;
	  ټاکل = gimple_build_ټاکل (lhs.ارزښت, کوډ, rhs.ارزښت);
	  gimple_seq_جمع_کړه_stmt_without_update (seq, ټاکل);
	  gimple_سېټ_location (ټاکل, loc);
	  أرجع;
	}
    }

  /* Unary expression.  */
  بدل (c_parser_peek_token (parser)->type)
    {
    حالة CPP_NAME:
      {
	ونه id = c_parser_peek_token (parser)->ارزښت;
	إذا (strcmp (IDENTIFIER_اشاره_ګر (id), "__ABS") == 0
	    || strcmp (IDENTIFIER_اشاره_ګر (id), "__ABSU") == 0
	    || strcmp (IDENTIFIER_اشاره_ګر (id), "__MIN") == 0
	    || strcmp (IDENTIFIER_اشاره_ګر (id), "__MAX") == 0
	    || strcmp (IDENTIFIER_اشاره_ګر (id), "__BIT_INSERT") == 0
	    || strcmp (IDENTIFIER_اشاره_ګر (id), "__VEC_PERM") == 0)
	  اذهب build_unary_بیان;
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
    build_unary_بیان:
      rhs = c_parser_gimple_unary_افاده (parser);
      إذا (rhs.ارزښت != error_mark_غوټه)
	{
	  ټاکل = gimple_build_ټاکل (lhs.ارزښت, rhs.ارزښت);
	  gimple_سېټ_location (ټاکل, loc);
	  gimple_seq_جمع_کړه_stmt_without_update (seq, ټاکل);
	}
      أرجع;

    افتراضي:;
    }

  /* GIMPLE PHI statement.  */
  إذا (c_parser_بل_token_is_keyword (parser, RID_PHI))
    {
      c_parser_consume_token (parser);

      إذا (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	أرجع;

      إذا (c_parser_بل_token_is (parser, CPP_OPEN_PAREN))
	c_parser_consume_token (parser);

      طالما (c_parser_بل_token_is_not (parser, CPP_CLOSE_PAREN))
	{
	  إذا (c_parser_بل_token_is (parser, CPP_NAME)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      arg = c_parser_peek_token (parser)->ارزښت;
	      c_parser_consume_token (parser);
	      إذا (c_parser_بل_token_is (parser, CPP_COLON))
		c_parser_consume_token (parser);
	      صحيح src_شاخص = -1;
	      إذا (!c_parser_gimple_parse_bb_spec (arg, &src_شاخص))
		c_parser_error (parser, "invalid source block specification");
	      vargs.خوندي_ټېل (اندازه_int (src_شاخص));
	    }
	  وإلا إذا (c_parser_بل_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  وإلا
	    {
	      arg = c_parser_gimple_unary_افاده (parser).ارزښت;
	      vargs.خوندي_ټېل (arg);
	    }
	}

      c_parser_skip_until_وموندل (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");

      /* Build internal function for PHI.  */
      gcall *call_stmt = gimple_build_call_دننی_vec (IFN_PHI, vargs);
      gimple_call_سېټ_lhs (call_stmt, lhs.ارزښت);
      gimple_سېټ_location (call_stmt, UNKNOWN_LOCATION);
      gimple_seq_جمع_کړه_stmt_without_update (seq, call_stmt);
      أرجع;
    }

  /* GIMPLE call with lhs.  */
  إذا (c_parser_بل_token_is (parser, CPP_DOT)
      || (c_parser_بل_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN
	  && lookup_name (c_parser_peek_token (parser)->ارزښت)))
    {
      rhs = c_parser_gimple_unary_افاده (parser);
      إذا (rhs.ارزښت != error_mark_غوټه)
	{
	  gimple *call = gimple_build_call_from_ونه (rhs.ارزښت, عدم);
	  gimple_call_سېټ_lhs (call, lhs.ارزښت);
	  gimple_seq_جمع_کړه_stmt_without_update (seq, call);
	  gimple_سېټ_location (call, loc);
	}
      أرجع;
    }

  rhs = c_parser_gimple_دوګونی_افاده (parser, ونه_TYPE (lhs.ارزښت));
  إذا (lhs.ارزښت != error_mark_غوټه
      && rhs.ارزښت != error_mark_غوټه)
    {
      /* If we parsed an identifier and the next token  is a '?' then parse
	 a conditional expression.  */
      إذا (SSA_VAR_P (rhs.ارزښت) && c_parser_بل_token_is (parser, CPP_QUERY))
	{
	  بنية c_بیان trueval, falseval;
	  c_parser_consume_token (parser);
	  trueval = c_parser_gimple_postfix_افاده (parser);
	  falseval.سېټ_error ();
	  إذا (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    falseval = c_parser_gimple_postfix_افاده (parser);
	  إذا (trueval.ارزښت == error_mark_غوټه
	      || falseval.ارزښت == error_mark_غوټه)
	    أرجع;
	  rhs.ارزښت = build3_loc (loc,
				  ویکټور_TYPE_P (ونه_TYPE (rhs.ارزښت))
				  ? VEC_COND_بیان : COND_بیان,
				  ونه_TYPE (trueval.ارزښت),
				  rhs.ارزښت, trueval.ارزښت, falseval.ارزښت);
	}
      إذا (get_gimple_rhs_class (ونه_کوډ (rhs.ارزښت)) == GIMPLE_INVALID_RHS)
	{
	  c_parser_error (parser, "unexpected RHS for assignment");
	  أرجع;
	}
      ټاکل = gimple_build_ټاکل (lhs.ارزښت, rhs.ارزښت);
      gimple_seq_جمع_کړه_stmt_without_update (seq, ټاکل);
      gimple_سېټ_location (ټاکل, loc);
    }
  أرجع;
}

/* A mapping between an identifier to a tree code for binary operations. */
ساكن ثابت std::pair<ثابت حرف *, ونه_کوډ_2> gimple_دوګونی_identifier_کوډ[] =
  {
    {"__MULT_HIGHPART", MULT_HIGHPART_بیان},
    {"__UNLT", UNLT_بیان},
    {"__UNLE", UNLE_بیان},
    {"__UNGT", UNGT_بیان},
    {"__UNGE", UNGE_بیان},
    {"__UNEQ", UNEQ_بیان},
    {"__UNORDERED", UNORDERED_بیان},
    {"__ORDERED", ORDERED_بیان},
    {"__LTGT", LTGT_بیان},
    {"__FLOOR_DIV", FLOOR_DIV_بیان},
    {"__ROUND_DIV", پړاو_DIV_بیان},
    {"__EXACT_DIV", EXACT_DIV_بیان},
    {"__CEIL_DIV", CEIL_DIV_بیان},
    {"__FLOOR_MOD", FLOOR_MOD_بیان},
    {"__ROUND_MOD", پړاو_MOD_بیان},
    {"__CEIL_MOD", CEIL_MOD_بیان},
    {"__ROTATE_LEFT", LROTATE_بیان},
    {"__ROTATE_RIGHT", RROTATE_بیان},
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

ساكن c_بیان
c_parser_gimple_دوګونی_افاده (gimple_parser &parser, ونه ret_type)
{
  /* Location of the binary operator.  */
  بنية c_بیان ret, lhs, rhs;
  تعداد ونه_کوډ_2 کوډ = ERROR_MARK;
  ret.سېټ_error ();
  lhs = c_parser_gimple_postfix_افاده (parser, ret_type);
  إذا (c_parser_error (parser))
    أرجع ret;
  بدل (c_parser_peek_token (parser)->type)
    {
    حالة CPP_MULT:
      کوډ = MULT_بیان;
      اكسر;
    حالة CPP_DIV:
      کوډ = TRUNC_DIV_بیان;
      اكسر;
    حالة CPP_MOD:
      کوډ = TRUNC_MOD_بیان;
      اكسر;
    حالة CPP_PLUS:
      إذا (اشاره_ګر_TYPE_P (ونه_TYPE (lhs.ارزښت)))
	کوډ = اشاره_ګر_PLUS_بیان;
      وإلا
	کوډ = PLUS_بیان;
      اكسر;
    حالة CPP_MINUS:
      إذا (اشاره_ګر_TYPE_P (ونه_TYPE (lhs.ارزښت)))
	کوډ = اشاره_ګر_DIFF_بیان;
      وإلا
	کوډ = MINUS_بیان;
      اكسر;
    حالة CPP_LSHIFT:
      کوډ = LSHIFT_بیان;
      اكسر;
    حالة CPP_RSHIFT:
      کوډ = RSHIFT_بیان;
      اكسر;
    حالة CPP_LESS:
      کوډ = LT_بیان;
      اكسر;
    حالة CPP_GREATER:
      کوډ = GT_بیان;
      اكسر;
    حالة CPP_LESS_EQ:
      کوډ = LE_بیان;
      اكسر;
    حالة CPP_GREATER_EQ:
      کوډ = GE_بیان;
      اكسر;
    حالة CPP_EQ_EQ:
      کوډ = EQ_بیان;
      اكسر;
    حالة CPP_NOT_EQ:
      کوډ = NE_بیان;
      اكسر;
    حالة CPP_AND:
      کوډ = بټ_AND_بیان;
      اكسر;
    حالة CPP_XOR:
      کوډ = بټ_XOR_بیان;
      اكسر;
    حالة CPP_OR:
      کوډ = بټ_IOR_بیان;
      اكسر;
    حالة CPP_AND_AND:
      c_parser_error (parser, "%<&&%> not valid in GIMPLE");
      أرجع ret;
    حالة CPP_OR_OR:
      c_parser_error (parser, "%<||%> not valid in GIMPLE");
      أرجع ret;
    حالة CPP_NAME:
      {
	ونه id = c_parser_peek_token (parser)->ارزښت;
	لكل (خپلکاری &p : gimple_دوګونی_identifier_کوډ)
	  {
	    إذا (strcmp (IDENTIFIER_اشاره_ګر (id), p.لومړی) == 0)
	      {
		کوډ = p.دوهم;
		اكسر;
	      }
	  }
	إذا (کوډ != ERROR_MARK)
	  اكسر;
      }
      /* Fallthru.  */
    افتراضي:
      /* Not a binary expression.  */
      أرجع lhs;
    }
  location_t ret_loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  rhs = c_parser_gimple_postfix_افاده (parser);
  إذا (lhs.ارزښت != error_mark_غوټه && rhs.ارزښت != error_mark_غوټه)
    ret.ارزښت = build2_loc (ret_loc, کوډ, ret_type, lhs.ارزښت, rhs.ارزښت);
  أرجع ret;
}

/* Parse a gimple parentized binary expression.  */

ساكن c_بیان
c_parser_gimple_parentized_دوګونی_افاده (gimple_parser &parser,
					      location_t op_loc,
					      ونه_کوډ_2 کوډ)
{
  بنية c_بیان ret;
  ret.سېټ_error ();

  c_parser_consume_token (parser);
  إذا (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    أرجع ret;
  c_بیان op1 = c_parser_gimple_postfix_افاده (parser);
  إذا (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    أرجع ret;
  c_بیان op2 = c_parser_gimple_postfix_افاده (parser);
  إذا (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    أرجع ret;

  إذا (op1.ارزښت != error_mark_غوټه && op2.ارزښت != error_mark_غوټه)
    ret.ارزښت = build2_loc (op_loc,
			    کوډ, ونه_TYPE (op1.ارزښت), op1.ارزښت, op2.ارزښت);
  أرجع ret;
}

/* Parse a gimple parentized binary expression.  */

ساكن c_بیان
c_parser_gimple_parentized_ternary_افاده (gimple_parser &parser,
					       location_t op_loc,
					       ونه_کوډ_2 کوډ)
{
  بنية c_بیان ret;
  ret.سېټ_error ();

  c_parser_consume_token (parser);
  إذا (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    أرجع ret;
  c_بیان op1 = c_parser_gimple_postfix_افاده (parser);
  إذا (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    أرجع ret;
  c_بیان op2 = c_parser_gimple_postfix_افاده (parser);
  إذا (!c_parser_require (parser, CPP_COMMA, "expected %<)%>"))
    أرجع ret;
  c_بیان op3 = c_parser_gimple_postfix_افاده (parser);
  إذا (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    أرجع ret;

  إذا (op1.ارزښت != error_mark_غوټه
      && op2.ارزښت != error_mark_غوټه
      && op3.ارزښت != error_mark_غوټه)
    ret.ارزښت = build3_loc (op_loc,
			    کوډ, ونه_TYPE (op1.ارزښت),
			    op1.ارزښت, op2.ارزښت, op3.ارزښت);
  أرجع ret;
}

/* Parse gimple unary expression.

   gimple-unary-expression:
     gimple-postfix-expression
     unary-operator gimple-postfix-expression

   unary-operator: one of
     & * + - ~ abs_expr
*/

ساكن c_بیان
c_parser_gimple_unary_افاده (gimple_parser &parser)
{
  بنية c_بیان ret, op;
  location_t op_loc = c_parser_peek_token (parser)->location;
  location_t پای;
  ret.سېټ_error ();
  بدل (c_parser_peek_token (parser)->type)
    {
    حالة CPP_AND:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_افاده (parser);
      mark_exp_read (op.ارزښت);
      أرجع gimple_parser_build_unary_op (op_loc, ADDR_بیان, op);
    حالة CPP_MULT:
      {
	c_parser_consume_token (parser);
	op = c_parser_gimple_postfix_افاده (parser);
	إذا (op.ارزښت == error_mark_غوټه)
	  أرجع ret;
	إذا (! اشاره_ګر_TYPE_P (ونه_TYPE (op.ارزښت)))
	  {
	    error_at (op_loc, "expected pointer as argument of unary %<*%>");
	    أرجع ret;
	  }
	پای = op.get_پای ();
	location_t combined_loc = make_location (op_loc, op_loc, پای);
	ret.ارزښت = build_simple_mem_ref_loc (combined_loc, op.ارزښت);
	ونه_SIDE_EFFECTS (ret.ارزښت)
	  = ونه_THIS_VOLATILE (ret.ارزښت)
	  = TYPE_VOLATILE (ونه_TYPE (ونه_TYPE (op.ارزښت)));
	ret.src_range.m_پیل = op_loc;
	ret.src_range.m_پای = پای;
	أرجع ret;
      }
    حالة CPP_PLUS:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_افاده (parser);
      أرجع gimple_parser_build_unary_op (op_loc, CONVERT_بیان, op);
    حالة CPP_MINUS:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_افاده (parser);
      أرجع gimple_parser_build_unary_op (op_loc, NEGATE_بیان, op);
    حالة CPP_COMPL:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_افاده (parser);
      أرجع gimple_parser_build_unary_op (op_loc, بټ_NOT_بیان, op);
    حالة CPP_NOT:
      c_parser_error (parser, "%<!%> not valid in GIMPLE");
      أرجع ret;
    حالة CPP_KEYWORD:
      بدل (c_parser_peek_token (parser)->keyword)
	{
	حالة RID_REALPART:
	  c_parser_consume_token (parser);
	  op = c_parser_gimple_postfix_افاده (parser);
	  أرجع gimple_parser_build_unary_op (op_loc, REALPART_بیان, op);
	حالة RID_IMAGPART:
	  c_parser_consume_token (parser);
	  op = c_parser_gimple_postfix_افاده (parser);
	  أرجع gimple_parser_build_unary_op (op_loc, IMAGPART_بیان, op);
	افتراضي:
	  أرجع c_parser_gimple_postfix_افاده (parser);
	}
    حالة CPP_NAME:
	{
	  ونه id = c_parser_peek_token (parser)->ارزښت;
	  إذا (strcmp (IDENTIFIER_اشاره_ګر (id), "__ABS") == 0)
	    {
	      c_parser_consume_token (parser);
	      op = c_parser_gimple_postfix_افاده (parser);
	      أرجع gimple_parser_build_unary_op (op_loc, ABS_بیان, op);
	    }
	  وإلا إذا (strcmp (IDENTIFIER_اشاره_ګر (id), "__ABSU") == 0)
	    {
	      c_parser_consume_token (parser);
	      op = c_parser_gimple_postfix_افاده (parser);
	      أرجع gimple_parser_build_unary_op (op_loc, ABSU_بیان, op);
	    }
	  وإلا إذا (strcmp (IDENTIFIER_اشاره_ګر (id), "__MIN") == 0)
	    أرجع c_parser_gimple_parentized_دوګونی_افاده (parser,
								 op_loc,
								 MIN_بیان);
	  وإلا إذا (strcmp (IDENTIFIER_اشاره_ګر (id), "__MAX") == 0)
	    أرجع c_parser_gimple_parentized_دوګونی_افاده (parser,
								 op_loc,
								 MAX_بیان);
	  وإلا إذا (strcmp (IDENTIFIER_اشاره_ګر (id), "__VEC_PERM") == 0)
	    أرجع c_parser_gimple_parentized_ternary_افاده
			(parser, op_loc, VEC_PERM_بیان);
	  وإلا إذا (strcmp (IDENTIFIER_اشاره_ګر (id), "__BIT_INSERT") == 0)
	    {
	      /* __BIT_INSERT '(' postfix-expression, postfix-expression,
			          integer ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      إذا (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_بیان op0 = c_parser_gimple_postfix_افاده (parser);
		  c_parser_skip_until_وموندل (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_بیان op1 = c_parser_gimple_postfix_افاده (parser);
		  c_parser_skip_until_وموندل (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_بیان op2 = c_parser_gimple_postfix_افاده (parser);
		  إذا (ونه_کوډ (op2.ارزښت) != INTEGER_CST
		      || !int_ځاییږي_type_p (op2.ارزښت, bitsizetype))
		    c_parser_error (parser, "expected constant offset");
		  c_parser_skip_until_وموندل (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  إذا (op0.ارزښت != error_mark_غوټه
		      && op1.ارزښت != error_mark_غوټه
		      && ونه_کوډ (op2.ارزښت) == INTEGER_CST)
		    ret.ارزښت = build3_loc (loc, بټ_ورننباسه_بیان,
					    ونه_TYPE (op0.ارزښت),
					    op0.ارزښت, op1.ارزښت,
					    fold_convert (bitsizetype,
							  op2.ارزښت));
		}
	      أرجع ret;
	    }
	  وإلا
	    أرجع c_parser_gimple_postfix_افاده (parser);
	}
    افتراضي:
      أرجع c_parser_gimple_postfix_افاده (parser);
    }
}

/* Decompose ID into base name (ID until ver_offset) and VERSION.  Return
   true if ID matches a SSA name.  */

ساكن منطقي
c_parser_parse_ssa_name_id (ونه id, بینښه *نسخه, بینښه *ver_دننه_واټن)
{
  ثابت حرف *token = IDENTIFIER_اشاره_ګر (id);
  ثابت حرف *var_نسخه = strrchr (token, '_');
  إذا (! var_نسخه)
    أرجع خطأ;

  *ver_دننه_واټن = var_نسخه - token;
  لكل (ثابت حرف *p = var_نسخه + 1; *p; ++p)
    إذا (! ISDIGIT (*p))
      أرجع خطأ;
  *نسخه = atoi (var_نسخه + 1);
  أرجع *نسخه > 0;
}

/* Get at the actual SSA name ID with VERSION starting at VER_OFFSET.
   TYPE is the type if the SSA name is being declared.  */

ساكن ونه
c_parser_parse_ssa_name (gimple_parser &parser,
			 ونه id, ونه type, بینښه نسخه,
			 بینښه ver_دننه_واټن)
{
  ونه name = NULL_ونه;
  ثابت حرف *token = IDENTIFIER_اشاره_ګر (id);

  إذا (ver_دننه_واټن == 0)
    {
      /* Anonymous unnamed SSA name.  */
      إذا (نسخه < عدد_ssa_نومونه)
	name = ssa_name (نسخه);
      إذا (! name)
	{
	  إذا (! type)
	    {
	      c_parser_error (parser, "SSA name undeclared");
	      أرجع error_mark_غوټه;
	    }
	  name = make_ssa_name_fn (cfun, type, عدم, نسخه);
	}
    }
  وإلا
    {
      إذا (نسخه < عدد_ssa_نومونه)
	name = ssa_name (نسخه);
      إذا (! name)
	{
	  /* Separate var name from version.  */
	  حرف *var_name = XNEWVEC (حرف, ver_دننه_واټن + 1);
	  حافظه_نقل (var_name, token, ver_دننه_واټن);
	  var_name[ver_دننه_واټن] = '\0';
	  /* lookup for parent decl.  */
	  id = get_identifier (var_name);
	  ونه پلار = lookup_name (id);
	  XDELETEVEC (var_name);
	  إذا (! پلار || پلار == error_mark_غوټه)
	    {
	      c_parser_error (parser, "base variable or SSA name undeclared");
	      أرجع error_mark_غوټه;
	    }
	  إذا (!(VAR_P (پلار)
		|| ونه_کوډ (پلار) == PARM_DECL
		|| ونه_کوډ (پلار) == پایله_DECL))
	    {
	      error ("invalid base %qE for SSA name", پلار);
	      أرجع error_mark_غوټه;
	    }
	  name = make_ssa_name_fn (cfun, پلار,
				   gimple_build_nop (), نسخه);
	}
    }

  أرجع name;
}

/* Parse a gimple call to an internal function.

   gimple-call-internal:
     . identifier ( gimple-argument-expression-list[opt] )  */

ساكن بنية c_بیان
c_parser_gimple_call_دننی (gimple_parser &parser)
{
  بنية c_بیان بیان;
  بیان.سېټ_error ();

  gcc_assert (c_parser_بل_token_is (parser, CPP_DOT));
  c_parser_consume_token (parser);
  location_t loc = c_parser_peek_token (parser)->location;
  إذا (!c_parser_بل_token_is (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_ډول != C_ID_ID)
    {
      c_parser_error (parser, "expecting internal function name");
      أرجع بیان;
    }
  ونه id = c_parser_peek_token (parser)->ارزښت;
  دننی_fn ifn = lookup_دننی_fn (IDENTIFIER_اشاره_ګر (id));
  c_parser_consume_token (parser);
  إذا (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    {
      auto_vec<ونه> exprlist;
      إذا (!c_parser_بل_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_gimple_بیان_list (parser, &exprlist);
      c_parser_skip_until_وموندل (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      إذا (ifn == IFN_وروستی)
	error_at (loc, "unknown internal function %qE", id);
      وإلا
	{
	  بیان.ارزښت = build_call_بیان_دننی_loc_array
	    (loc, ifn, void_type_غوټه, exprlist.اوږدتیا (),
	     exprlist.پته ());
	  بیان.original_کوډ = ERROR_MARK;
	  بیان.original_type = عدم;
	  بیان.m_decimal = 0;
	}
    }
  أرجع بیان;
}

/* Parse '<' type [',' alignment] '>' and return a type on success
   and NULL_TREE on error.  */

ساكن ونه
c_parser_gimple_typespec (gimple_parser &parser)
{
  بنية c_type_name *type_name = عدم;
  ونه alignment = NULL_ونه;
  إذا (c_parser_require (parser, CPP_LESS, "expected %<<%>"))
    {
      type_name = c_parser_type_name (parser);
      /* Optional alignment.  */
      إذا (c_parser_بل_token_is (parser, CPP_COMMA))
	{
	  c_parser_consume_token (parser);
	  alignment
	      = c_parser_gimple_postfix_افاده (parser).ارزښت;
	}
      c_parser_skip_until_وموندل (parser,
				 CPP_GREATER, "expected %<>%>");
    }
  إذا (!type_name)
    أرجع NULL_ونه;
  ونه tem;
  ونه type = groktypename (type_name, &tem, عدم);
  إذا (alignment)
    type = build_aligned_type (type, ونه_منزل_uhwi (alignment));
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

ساكن بنية c_بیان
c_parser_gimple_postfix_افاده (gimple_parser &parser, ونه ret_type)
{
  location_t loc = c_parser_peek_token (parser)->location;
  سرچینه_range tok_range = c_parser_peek_token (parser)->get_range ();
  بنية c_بیان بیان;
  بیان.سېټ_error ();
  بدل (c_parser_peek_token (parser)->type)
    {
    حالة CPP_شمېره:
      بیان.ارزښت = c_parser_peek_token (parser)->ارزښت;
      سېټ_c_بیان_سرچینه_range (&بیان, tok_range);
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      اكسر;
    حالة CPP_CHAR:
    حالة CPP_CHAR16:
    حالة CPP_CHAR32:
    حالة CPP_UTF8CHAR:
    حالة CPP_WCHAR:
      بیان.ارزښت = c_parser_peek_token (parser)->ارزښت;
      سېټ_c_بیان_سرچینه_range (&بیان, tok_range);
      c_parser_consume_token (parser);
      اكسر;
    حالة CPP_STRING:
    حالة CPP_STRING16:
    حالة CPP_STRING32:
    حالة CPP_WSTRING:
    حالة CPP_UTF8STRING:
      بیان = c_parser_string_literal (parser, خطأ, ریښتیا);
      اكسر;
    حالة CPP_DOT:
      بیان = c_parser_gimple_call_دننی (parser);
      اكسر;
    حالة CPP_NAME:
      إذا (c_parser_peek_token (parser)->id_ډول == C_ID_ID)
	{
	  ونه id = c_parser_peek_token (parser)->ارزښت;
	  إذا (strcmp (IDENTIFIER_اشاره_ګر (id), "__MEM") == 0)
	    {
	      /* __MEM '<' type-name [ ',' number ] '>'
	               '(' [ '(' type-name ')' ] unary-expression
			   [ '+' number ]
			   [ ',' number ]
			   [ ',' number ':' number ] ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      ونه type = c_parser_gimple_typespec (parser);
	      بنية c_بیان ptr, alias_off, ګام, شاخص, index2;
	      ptr.ارزښت = error_mark_غوټه;
	      alias_off.ارزښت = NULL_ونه;
	      ګام.ارزښت = NULL_ونه;
	      شاخص.ارزښت = NULL_ونه;
	      index2.ارزښت = NULL_ونه;
	      بینښه لنډ clique = 0;
	      بینښه لنډ بنسټ = 0;
	      منطقي سرچپه_ترتیب = خطأ;
	      بنية c_بیان ro;
	      إذا (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  ونه alias_type = NULL_ونه;
		  /* Optional alias-type cast.  */
		  إذا (c_parser_بل_token_is (parser, CPP_OPEN_PAREN))
		    {
		      c_parser_consume_token (parser);
		      بنية c_type_name *alias_type_name
			= c_parser_type_name (parser);
		      c_parser_skip_until_وموندل (parser, CPP_CLOSE_PAREN,
						 "expected %<)%>");
		      إذا (alias_type_name)
			{
			  ونه tem;
			  alias_type = groktypename (alias_type_name,
						     &tem, عدم);
			}
		    }
		  ptr = c_parser_gimple_unary_افاده (parser);
		  إذا (ptr.ارزښت == error_mark_غوټه
		      || ! اشاره_ګر_TYPE_P (ونه_TYPE (ptr.ارزښت)))
		    {
		      إذا (ptr.ارزښت != error_mark_غوټه)
			error_at (ptr.get_پیل (),
				  "invalid type of %<__MEM%> operand");
		      c_parser_skip_until_وموندل (parser, CPP_CLOSE_PAREN,
						 "expected %<)%>");
		      أرجع بیان;
		    }
		  إذا (! alias_type)
		    alias_type = ونه_TYPE (ptr.ارزښت);
		  /* Optional constant offset.  */
		  إذا (c_parser_بل_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      alias_off = c_parser_gimple_postfix_افاده (parser);
		    }
		  إذا (c_parser_بل_token_is (parser, CPP_MULT))
		    {
		      std::بدلون (شاخص, alias_off);
		      c_parser_consume_token (parser);
		      ګام = c_parser_gimple_postfix_افاده (parser);
		    }
		  وإلا إذا (c_parser_بل_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      شاخص = c_parser_gimple_postfix_افاده (parser);
		      إذا (c_parser_بل_token_is (parser, CPP_MULT))
			{
			  c_parser_consume_token (parser);
			  ګام = c_parser_gimple_postfix_افاده (parser);
			}
		      وإلا
			std::بدلون (شاخص, index2);
		    }
		  وإلا إذا (alias_off.ارزښت
			   && ونه_کوډ (alias_off.ارزښت) != INTEGER_CST)
		    std::بدلون (alias_off, index2);
		  إذا (c_parser_بل_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      index2 = c_parser_gimple_postfix_افاده (parser);
		    }
		  إذا (alias_off.ارزښت)
		    {
		      إذا (ونه_کوډ (alias_off.ارزښت) != INTEGER_CST)
			error_at (alias_off.get_پیل (),
				  "expected constant offset for %<__MEM%> "
				  "operand");
		      alias_off.ارزښت = fold_convert (alias_type,
						      alias_off.ارزښت);
		    }
		  وإلا
		    alias_off.ارزښت = build_int_cst (alias_type, 0);
		  إذا (ګام.ارزښت)
		    {
		      إذا (ونه_کوډ (ګام.ارزښت) != INTEGER_CST)
			error_at (ګام.get_پیل (),
				  "expected constant step for %<__MEM%> "
				  "operand");
		    }
		  إذا (c_parser_بل_token_is (parser, CPP_COMMA))
		    {
		      بنية c_بیان cl, ba;
		      منطقي has_clb = ریښتیا;
		      c_parser_consume_token (parser);
		      cl = c_parser_gimple_postfix_افاده (parser);
		      إذا (!c_parser_بل_token_is (parser, CPP_COLON))
			{
			  ro = cl;
			  بینښه HOST_WIDE_INT tmp = 0;
			  إذا (!ونه_ځاییږي_uhwi_p (ro.ارزښت)
			      || (tmp = ونه_منزل_uhwi (ro.ارزښت)) > 1)
			    error_at (ro.get_پیل (),
				      "invalid reverse order value");
			  سرچپه_ترتیب = tmp;
			  has_clb = خطأ;
			  إذا (c_parser_بل_token_is (parser, CPP_COMMA))
			    {
			      c_parser_consume_token (parser);
			      cl = c_parser_gimple_postfix_افاده (parser);
		              has_clb = ریښتیا;
			    }
			}
		      إذا (has_clb
			  && c_parser_require (parser,
					       CPP_COLON, "expected %<:%>"))
			{
			  ba = c_parser_gimple_postfix_افاده (parser);
			  إذا (!ونه_ځاییږي_uhwi_p (cl.ارزښت)
			      || !ونه_ځاییږي_uhwi_p (ba.ارزښت)
			      || compare_ونه_int (cl.ارزښت,
						   (clique = ونه_منزل_uhwi
								(cl.ارزښت)))
			      || compare_ونه_int (ba.ارزښت,
						   (بنسټ = ونه_منزل_uhwi
								 (ba.ارزښت))))
			    error_at (cl.get_پیل (),
				      "invalid clique/base pair");
			}
		    }
		  c_parser_skip_until_وموندل (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      إذا (! type || c_parser_error (parser))
		{
		  c_parser_سېټ_error (parser, خطأ);
		  أرجع بیان;
		}
	      إذا (شاخص.ارزښت || ګام.ارزښت || index2.ارزښت)
		بیان.ارزښت = build5_loc (loc, موخه_MEM_REF,
					 type, ptr.ارزښت, alias_off.ارزښت,
					 شاخص.ارزښت, ګام.ارزښت, index2.ارزښت);
	      وإلا
		بیان.ارزښت = build2_loc (loc, MEM_REF,
					 type, ptr.ارزښت, alias_off.ارزښت);
	      إذا (clique != 0)
		{
		  cfun->وروستی_clique = MAX (cfun->وروستی_clique, clique);
		  MR_DEPENDENCE_CLIQUE (بیان.ارزښت) = clique;
		  MR_DEPENDENCE_بنسټ (بیان.ارزښت) = بنسټ;
		}
	      إذا (سرچپه_ترتیب)
		{
		  إذا (ونه_کوډ (بیان.ارزښت) == MEM_REF)
		    REF_سرچپه_STORAGE_ترتیب (بیان.ارزښت) = سرچپه_ترتیب;
		  وإلا
		    error_at (ro.get_پیل (),
			      "target mem ref cannot have reverse order");
		}
	      اكسر;
	    }
	  وإلا إذا (strcmp (IDENTIFIER_اشاره_ګر (id), "__VIEW_CONVERT") == 0)
	    {
	      /* __VIEW_CONVERT '<' type-name [ ',' number ] '>'
	                        '(' postfix-expression ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      ونه type = c_parser_gimple_typespec (parser);
	      إذا (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_بیان op = c_parser_gimple_postfix_افاده (parser);
		  c_parser_skip_until_وموندل (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  إذا (type && op.ارزښت != error_mark_غوټه)
		    بیان.ارزښت = build1_loc (loc, VIEW_CONVERT_بیان,
					     type, op.ارزښت);
		}
	      اكسر;
	    }
	  وإلا إذا (strcmp (IDENTIFIER_اشاره_ګر (id), "__BIT_FIELD_REF") == 0)
	    {
	      /* __BIT_FIELD_REF '<' type-name [ ',' number ] '>'
	                        '(' postfix-expression, integer, integer ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      ونه type = c_parser_gimple_typespec (parser);
	      إذا (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_بیان op0 = c_parser_gimple_postfix_افاده (parser);
		  c_parser_skip_until_وموندل (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_بیان op1 = c_parser_gimple_postfix_افاده (parser);
		  إذا (ونه_کوډ (op1.ارزښت) != INTEGER_CST
		      || !int_ځاییږي_type_p (op1.ارزښت, bitsizetype))
		    c_parser_error (parser, "expected constant size");
		  c_parser_skip_until_وموندل (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_بیان op2 = c_parser_gimple_postfix_افاده (parser);
		  إذا (ونه_کوډ (op2.ارزښت) != INTEGER_CST
		      || !int_ځاییږي_type_p (op2.ارزښت, bitsizetype))
		    c_parser_error (parser, "expected constant offset");
		  c_parser_skip_until_وموندل (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  إذا (type
		      && op0.ارزښت != error_mark_غوټه
		      && ونه_کوډ (op1.ارزښت) == INTEGER_CST
		      && ونه_کوډ (op2.ارزښت) == INTEGER_CST)
		    بیان.ارزښت = build3_loc (loc, بټ_ډګر_REF, type,
					     op0.ارزښت,
					     fold_convert (bitsizetype,
							   op1.ارزښت),
					     fold_convert (bitsizetype,
							   op2.ارزښت));
		}
	      اكسر;
	    }
	  وإلا إذا (strcmp (IDENTIFIER_اشاره_ګر (id), "__CLOBBER") == 0)
	    {
	      /* __CLOBBER [ '(' bob | eob | bos | eos ')' ]  */
	      clobber_ډول ډول = CLOBBER_UNDEF;
	      c_parser_consume_token (parser);
	      إذا (c_parser_بل_token_is (parser, CPP_OPEN_PAREN))
		{
		  c_parser_consume_token (parser);
		  خپلکاری tok = c_parser_peek_token (parser);
		  إذا (c_parser_require (parser, CPP_NAME,
					"expected clobber kind"))
		    {
		      ثابت حرف *ډول_str = IDENTIFIER_اشاره_ګر (tok->ارزښت);
		      إذا (strcmp (ډول_str, "bos") == 0)
			ډول = CLOBBER_STORAGE_BEGIN;
		      وإلا إذا (strcmp (ډول_str, "bob") == 0)
			ډول = CLOBBER_OBJECT_BEGIN;
		      وإلا إذا (strcmp (ډول_str, "eob") == 0)
			ډول = CLOBBER_OBJECT_پای_ټکی;
		      وإلا إذا (strcmp (ډول_str, "eos") == 0)
			ډول = CLOBBER_STORAGE_پای_ټکی;
		      وإلا
			c_parser_error (parser, "expected one of %<bos%>, "
					"%<eos%>, %<bob>, %<eob%>");
		    }
		  c_parser_skip_until_وموندل (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      /* We infer the (redundant) type from the LHS.  */
	      بیان.ارزښت = build_clobber (ret_type, ډول);
	      اكسر;
	    }
	  وإلا إذا (strcmp (IDENTIFIER_اشاره_ګر (id), "_Literal") == 0)
	    {
	      /* _Literal '(' type-name ')' ( [ '-' ] constant | constructor ) */
	      c_parser_consume_token (parser);
	      ونه type = NULL_ونه;
	      إذا (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  بنية c_type_name *type_name = c_parser_type_name (parser);
		  ونه tem;
		  إذا (type_name)
		    type = groktypename (type_name, &tem, عدم);
		  c_parser_skip_until_وموندل (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      إذا (! type)
		{
		  c_parser_error (parser, "invalid _Literal");
		  أرجع بیان;
		}
	      إذا (c_parser_بل_token_is (parser, CPP_OPEN_BRACE))
		{
		  c_parser_consume_token (parser);
		  إذا (!AGGREGATE_TYPE_P (type)
		      && !ویکټور_TYPE_P (type))
		    {
		      c_parser_error (parser, "invalid type for _Literal with "
				      "constructor");
		      c_parser_skip_until_وموندل (parser, CPP_CLOSE_BRACE,
						 "expected %<}%>");
		      أرجع بیان;
		    }
		  vec<constructor_elt, va_gc> *v = عدم;
		  منطقي constant_p = ریښتیا;
		  إذا (ویکټور_TYPE_P (type)
		      && !c_parser_بل_token_is (parser, CPP_CLOSE_BRACE))
		    {
		      vec_alloc (v, TYPE_ویکټور_SUBPARTS (type).منزل_constant ());
		      افعل
			{
			  ونه val
			    = c_parser_gimple_postfix_افاده (parser).ارزښت;
			  إذا (! val
			      || val == error_mark_غوټه
			      || (! CONSTANT_CLASS_P (val)
				  && ! SSA_VAR_P (val)))
			    {
			      c_parser_error (parser, "invalid _Literal");
			      أرجع بیان;
			    }
			  CONSTRUCTOR_APPEND_ELT (v, NULL_ونه, val);
			  إذا (! CONSTANT_CLASS_P (val))
			    constant_p = خطأ;
			  إذا (c_parser_بل_token_is (parser, CPP_COMMA))
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
			بیان.ارزښت = build_ویکټور_from_ctor (type, v);
		      وإلا
			بیان.ارزښت = build_constructor (type, v);
		    }
		  وإلا
		    {
		      c_parser_skip_until_وموندل (parser, CPP_CLOSE_BRACE,
						 "expected %<}%>");
		      أرجع بیان;
		    }
		}
	      وإلا
		{
		  منطقي neg_p, addr_p;
		  إذا ((neg_p = c_parser_بل_token_is (parser, CPP_MINUS)))
		    c_parser_consume_token (parser);
		  إذا ((addr_p = c_parser_بل_token_is (parser, CPP_AND)))
		    c_parser_consume_token (parser);
		  ونه val = c_parser_gimple_postfix_افاده (parser).ارزښت;
		  إذا (! val
		      || val == error_mark_غوټه
		      || (!CONSTANT_CLASS_P (val) && !addr_p))
		    {
		      c_parser_error (parser, "invalid _Literal");
		      أرجع بیان;
		    }
		  إذا (addr_p)
		    {
		      val = build1 (ADDR_بیان, type, val);
		      إذا (!is_gimple_invariant_پته (val))
			{
			  c_parser_error (parser, "invalid _Literal");
			  أرجع بیان;
			}
		    }
		  إذا (neg_p)
		    {
		      val = const_unop (NEGATE_بیان, ونه_TYPE (val), val);
		      إذا (! val)
			{
			  c_parser_error (parser, "invalid _Literal");
			  أرجع بیان;
			}
		    }
		  بیان.ارزښت = fold_convert (type, val);
		}
	      أرجع بیان;
	    }

	  /* SSA name.  */
	  بینښه نسخه, ver_دننه_واټن;
	  إذا (! lookup_name (id)
	      && c_parser_parse_ssa_name_id (id, &نسخه, &ver_دننه_واټن))
	    {
	      c_parser_consume_token (parser);
	      بیان.ارزښت = c_parser_parse_ssa_name (parser, id, NULL_ونه,
						    نسخه, ver_دننه_واټن);
	      إذا (بیان.ارزښت == error_mark_غوټه)
		أرجع بیان;
	      سېټ_c_بیان_سرچینه_range (&بیان, tok_range);
	      /* For default definition SSA names.  */
	      إذا (c_parser_بل_token_is (parser, CPP_OPEN_PAREN)
		  && c_parser_peek_2nd_token (parser)->type == CPP_NAME
		  && strcmp ("D",
			     IDENTIFIER_اشاره_ګر
			       (c_parser_peek_2nd_token (parser)->ارزښت)) == 0
		  && c_parser_peek_nth_token (parser, 3)->type == CPP_CLOSE_PAREN)
		{
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		  إذا (! SSA_NAME_IS_DEFAULT_DEF (بیان.ارزښت))
		    {
		      إذا (!SSA_NAME_VAR (بیان.ارزښت))
			{
			  error_at (loc, "anonymous SSA name cannot have"
				    " default definition");
			  بیان.ارزښت = error_mark_غوټه;
			  أرجع بیان;
			}
		      سېټ_ssa_default_def (cfun, SSA_NAME_VAR (بیان.ارزښت),
					   بیان.ارزښت);
		      SSA_NAME_DEF_STMT (بیان.ارزښت) = gimple_build_nop ();
		    }
		}
	    }
	  وإلا
	    {
	      c_parser_consume_token (parser);
	      بیان.ارزښت
		= build_external_ref (loc, id,
				      (c_parser_peek_token (parser)->type
				       == CPP_OPEN_PAREN), &بیان.original_type);
	      سېټ_c_بیان_سرچینه_range (&بیان, tok_range);
	    }
	  اكسر;
	}
      /* Fallthru.  */
    افتراضي:
      c_parser_error (parser, "expected expression");
      بیان.سېټ_error ();
      اكسر;
    }
  إذا (بیان.ارزښت == error_mark_غوټه)
    أرجع بیان;
  أرجع c_parser_gimple_postfix_افاده_after_primary
    (parser, بیان_LOC_OR_LOC (بیان.ارزښت, loc), بیان);
}

/* Parse a gimple postfix expression after the initial primary or compound
   literal.  */

ساكن بنية c_بیان
c_parser_gimple_postfix_افاده_after_primary (gimple_parser &parser,
						  location_t بیان_loc,
						  بنية c_بیان بیان)
{
  location_t پیل;
  location_t پای;
  ونه ident;
  location_t comp_loc;

  طالما (ریښتیا)
    {
      location_t op_loc = c_parser_peek_token (parser)->location;
      بدل (c_parser_peek_token (parser)->type)
	{
	حالة CPP_OPEN_مربع:
	  {
	    c_parser_consume_token (parser);
	    ونه idx = c_parser_gimple_unary_افاده (parser).ارزښت;

	    إذا (! c_parser_require (parser, CPP_CLOSE_مربع, "expected %<]%>"))
	      {
		c_parser_skip_until_وموندل (parser, CPP_CLOSE_مربع, عدم);
		اكسر;
	      }

	    پیل = بیان.get_پیل ();
	    پای = c_parser_نښې_buf (parser, 0)->location;
	    بیان.ارزښت = build_array_ref (op_loc, بیان.ارزښت, idx);
	    سېټ_c_بیان_سرچینه_range (&بیان, پیل, پای);
	    بیان.m_decimal = 0;

	    بیان.original_کوډ = ERROR_MARK;
	    بیان.original_type = عدم;
	    اكسر;
	  }
	حالة CPP_OPEN_PAREN:
	  {
	    /* Function call.  */
	    c_parser_consume_token (parser);
	    auto_vec<ونه> exprlist;
	    إذا (! c_parser_بل_token_is (parser, CPP_CLOSE_PAREN))
	      c_parser_gimple_بیان_list (parser, &exprlist);
	    c_parser_skip_until_وموندل (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    إذا (!FUNC_OR_لاره_TYPE_P (ونه_TYPE (بیان.ارزښت)))
	      {
		c_parser_error (parser, "invalid call to non-function");
		بیان.سېټ_error ();
		اكسر;
	      }
	    بیان.ارزښت = build_call_array_loc
		(بیان_loc, ونه_TYPE (ونه_TYPE (بیان.ارزښت)),
		 بیان.ارزښت, exprlist.اوږدتیا (), exprlist.پته ());
	    بیان.m_decimal = 0;
	    بیان.original_کوډ = ERROR_MARK;
	    بیان.original_type = عدم;
	    اكسر;
	  }
	حالة CPP_DOT:
	  {
	    /* Structure element reference.  */
	    c_parser_consume_token (parser);
	    إذا (c_parser_بل_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		ident = comp_tok->ارزښت;
		comp_loc = comp_tok->location;
	      }
	    وإلا
	      {
		c_parser_error (parser, "expected identifier");
		بیان.سېټ_error ();
		بیان.original_کوډ = ERROR_MARK;
		بیان.original_type = عدم;
		أرجع بیان;
	      }
	    پیل = بیان.get_پیل ();
	    پای = c_parser_peek_token (parser)->get_پای ();
	    c_parser_consume_token (parser);
	    بیان.ارزښت = build_component_ref (op_loc, بیان.ارزښت, ident,
					      comp_loc, UNKNOWN_LOCATION);
	    سېټ_c_بیان_سرچینه_range (&بیان, پیل, پای);
	    بیان.m_decimal = 0;
	    بیان.original_کوډ = ERROR_MARK;
	    إذا (ونه_کوډ (بیان.ارزښت) != COMPONENT_REF)
	      بیان.original_type = عدم;
	    وإلا
	      {
		/* Remember the original type of a bitfield.  */
		ونه ډګر_2 = ونه_عملوند (بیان.ارزښت, 1);
		إذا (ونه_کوډ (ډګر_2) != ډګر_DECL)
		  بیان.original_type = عدم;
		وإلا
		  بیان.original_type = DECL_بټ_ډګر_TYPE (ډګر_2);
	      }
	    اكسر;
	  }
	حالة CPP_DEREF:
	  {
	    /* Structure element reference.  */
	    إذا (!اشاره_ګر_TYPE_P (ونه_TYPE (بیان.ارزښت)))
	      {
		c_parser_error (parser, "dereference of non-pointer");
		بیان.سېټ_error ();
		بیان.original_کوډ = ERROR_MARK;
		بیان.original_type = عدم;
		أرجع بیان;
	      }
	    c_parser_consume_token (parser);
	    إذا (c_parser_بل_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		ident = comp_tok->ارزښت;
		comp_loc = comp_tok->location;
	      }
	    وإلا
	      {
		c_parser_error (parser, "expected identifier");
		بیان.سېټ_error ();
		بیان.original_کوډ = ERROR_MARK;
		بیان.original_type = عدم;
		أرجع بیان;
	      }
	    پیل = بیان.get_پیل ();
	    پای = c_parser_peek_token (parser)->get_پای ();
	    c_parser_consume_token (parser);
	    بیان.ارزښت = build_component_ref (op_loc,
					      build_simple_mem_ref_loc
					        (op_loc, بیان.ارزښت),
					      ident, comp_loc,
					      بیان.get_location ());
	    سېټ_c_بیان_سرچینه_range (&بیان, پیل, پای);
	    بیان.m_decimal = 0;
	    بیان.original_کوډ = ERROR_MARK;
	    إذا (ونه_کوډ (بیان.ارزښت) != COMPONENT_REF)
	      بیان.original_type = عدم;
	    وإلا
	      {
		/* Remember the original type of a bitfield.  */
		ونه ډګر_2 = ونه_عملوند (بیان.ارزښت, 1);
		إذا (ونه_کوډ (ډګر_2) != ډګر_DECL)
		  بیان.original_type = عدم;
		وإلا
		  بیان.original_type = DECL_بټ_ډګر_TYPE (ډګر_2);
	      }
	    اكسر;
	  }
	افتراضي:
	  أرجع بیان;
	}
    }
}

/* Parse expression list.

   gimple-expr-list:
     gimple-unary-expression
     gimple-expr-list , gimple-unary-expression

 */

ساكن فراغ
c_parser_gimple_بیان_list (gimple_parser &parser, vec<ونه> *ret)
{
  بنية c_بیان بیان;

  بیان = c_parser_gimple_unary_افاده (parser);
  ret->خوندي_ټېل (بیان.ارزښت);
  طالما (c_parser_بل_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      بیان = c_parser_gimple_unary_افاده (parser);
      ret->خوندي_ټېل (بیان.ارزښت);
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
  ونه name = c_parser_peek_token (parser)->ارزښت;
  location_t loc1 = c_parser_peek_token (parser)->location;
  gcc_assert (c_parser_بل_token_is (parser, CPP_NAME));
  c_parser_consume_token (parser);
  gcc_assert (c_parser_بل_token_is (parser, CPP_COLON));
  c_parser_consume_token (parser);
  ونه label = define_label (loc1, name);
  إذا (label)
    gimple_seq_جمع_کړه_stmt_without_update (seq, gimple_build_label (label));
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
  إذا (c_parser_بل_token_is_not (parser, CPP_OPEN_PAREN))
    أرجع;
  c_parser_consume_token (parser);

  specs->ثبت_bb_شمېر = profile_شمېر::uninitialized ();
  طالما (c_parser_بل_token_is (parser, CPP_NAME))
    {
      profile_quality quality;
      ثابت حرف *op = IDENTIFIER_اشاره_ګر (c_parser_peek_token (parser)->ارزښت);
      c_parser_consume_token (parser);
      إذا (! strcmp (op, "startwith"))
	{
	  إذا (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    أرجع;
	  إذا (c_parser_بل_token_is_not (parser, CPP_STRING))
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"expected pass name");
	      أرجع;
	    }
	  pass = xstrdup (ونه_STRING_اشاره_ګر
			  (c_parser_string_literal (parser, خطأ,
						    خطأ).ارزښت));
	  إذا (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<(%>"))
	    أرجع;
	}
      وإلا إذا (parse_profile_quality (op, &quality))
	{
	  ونه q;
	  إذا (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    أرجع;

	  إذا (!c_parser_بل_token_is (parser, CPP_شمېره)
	      || (ونه_کوډ (q = c_parser_peek_token (parser)->ارزښت)
		  != INTEGER_CST))
	    {
	      c_parser_error (parser, "expected count value");
	      أرجع;
	    }

	  specs->ثبت_bb_شمېر
	    = profile_شمېر::from_gcov_type (ونه_INT_CST_ټیټ (q), quality);
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
     إذا (c_parser_بل_token_is (parser, CPP_COMMA))
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
ثبتوونکی

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
  c_parser_declspecs (parser, specs, ریښتیا, ریښتیا, ریښتیا,
		      ریښتیا, ریښتیا, ریښتیا, ریښتیا, cla_nonabstract_decl);
  پای_declspecs (specs);

  /* Provide better error recovery.  Note that a type name here is usually
     better diagnosed as a redeclaration.  */
  إذا (c_parser_بل_token_starts_declspecs (parser)
      && ! c_parser_بل_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<;%>");
      c_parser_سېټ_error (parser, خطأ);
      أرجع;
    }

  منطقي dummy = خطأ;
  declarator = c_parser_declarator (parser,
				    specs->typespec_ډول != ctsk_none,
				    C_DTR_نورمال, &dummy);

  إذا (!c_parser_بل_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_error (parser, "expected %<;%>");
      أرجع;
    }
  إذا (declarator)
    {
      /* Handle SSA name decls specially, they do not go into the identifier
         table but we simply build the SSA name for later lookup.  */
      بینښه نسخه, ver_دننه_واټن;
      /* Handle SSA pointer declarations in a very simplistic ways, we
	 probably would like to call grokdeclarator in a special mode to
	 just build the type of the decl - start_decl already pushes
	 the identifier to the bindings for lookup, something we do not
	 want.  */
      بنية c_declarator *id_declarator = declarator;
      طالما (id_declarator->ډول == cdk_اشاره_ګر)
	id_declarator = id_declarator->declarator;
      إذا (id_declarator->ډول == cdk_id
	  && (declarator->ډول == cdk_اشاره_ګر
	      || is_gimple_reg_type (specs->type))
	  && c_parser_parse_ssa_name_id (id_declarator->u.id.id,
					 &نسخه, &ver_دننه_واټن)
	  /* The following restricts it to unnamed anonymous SSA names
	     which fails parsing of named ones in dumps (we could
	     decide to not dump their name for -gimple).  */
	  && ver_دننه_واټن == 0)
	{
	  بنية c_declarator *p = declarator;
	  ونه type = specs->type;
	  طالما (p->ډول == cdk_اشاره_ګر)
	    {
	      type = build_اشاره_ګر_type (type);
	      p = p->declarator;
	    }
	  c_parser_parse_ssa_name (parser, id_declarator->u.id.id, type,
				   نسخه, ver_دننه_واټن);
	}
      وإلا
	{
	  ونه postfix_attrs = NULL_ونه;
	  ونه all_مختاړی_attrs = specs->attrs;
	  specs->attrs = عدم;
	  ونه decl = پیل_decl (declarator, specs, خطأ,
				  chainon (postfix_attrs, all_مختاړی_attrs));
	  إذا (decl)
	    پای_decl (decl, UNKNOWN_LOCATION, NULL_ونه, NULL_ونه,
			 NULL_ونه);
	}
    }
}

/* Parse gimple goto statement.  */

ساكن فراغ
c_parser_gimple_goto_stmt (gimple_parser &parser,
			   location_t loc, ونه label, gimple_seq *seq)
{
  إذا (cfun->curr_properties & PROP_cfg)
    {
      صحيح dest_شاخص;
      profile_probability prob;
      إذا (c_parser_gimple_parse_bb_spec_څنډه_probability (label, parser,
							  &dest_شاخص, &prob))
	{
	  parser.ټېل_څنډه (parser.current_bb->شاخص, dest_شاخص,
			    څنډه_FALLTHRU, prob);
	  أرجع;
	}
    }
  ونه decl = lookup_label_for_goto (loc, label);
  gimple_seq_جمع_کړه_stmt_without_update (seq, gimple_build_goto (decl));
}

/* Parse a parenthesized condition.
   gimple-condition:
     ( gimple-binary-expression )    */

ساكن ونه
c_parser_gimple_paren_condition (gimple_parser &parser)
{
  إذا (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    أرجع error_mark_غوټه;
  ونه cond
    = c_parser_gimple_دوګونی_افاده (parser, boolean_type_غوټه).ارزښت;
  إذا (cond != error_mark_غوټه
      && ! COMPARISON_CLASS_P (cond)
      && ! CONSTANT_CLASS_P (cond)
      && ! SSA_VAR_P (cond))
    {
      c_parser_error (parser, "comparison required");
      cond = error_mark_غوټه;
    }
  إذا (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    أرجع error_mark_غوټه;
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

  إذا ((c_parser_بل_token_is (parser, CPP_KEYWORD)
       && c_parser_peek_token (parser)->keyword == RID_AT_FINALLY)
      || (c_parser_بل_token_is (parser, CPP_NAME)
	  && c_parser_peek_token (parser)->id_ډول == C_ID_ID
	  && strcmp (IDENTIFIER_اشاره_ګر (c_parser_peek_token (parser)->ارزښت),
		     "finally") == 0))
    {
      gimple_seq finseq = عدم;
      c_parser_consume_token (parser);
      c_parser_gimple_compound_statement (parser, &finseq);

      إذا (c_parser_بل_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_ELSE)
	{
	  gimple_seq elsseq = عدم;
	  c_parser_consume_token (parser);
	  c_parser_gimple_compound_statement (parser, &elsseq);

	  geh_else *stmt = gimple_build_eh_else (finseq, elsseq);
	  finseq = عدم;
	  gimple_seq_جمع_کړه_stmt_without_update (&finseq, stmt);
	}

      gtry *stmt = gimple_build_try (tryseq, finseq, GIMPLE_TRY_FINALLY);
      gimple_seq_جمع_کړه_stmt_without_update (seq, stmt);
    }
  وإلا إذا (c_parser_بل_token_is (parser, CPP_KEYWORD)
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
  ونه t_label = NULL_ونه, f_label = NULL_ونه, label;
  location_t loc;
  c_parser_consume_token (parser);
  ونه cond = c_parser_gimple_paren_condition (parser);

  إذا (c_parser_بل_token_is_keyword (parser, RID_GOTO))
    {
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      إذا (! c_parser_بل_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected label");
	  أرجع;
	}
      label = c_parser_peek_token (parser)->ارزښت;
      c_parser_consume_token (parser);
      صحيح dest_شاخص;
      profile_probability prob;
      إذا ((cfun->curr_properties & PROP_cfg)
	  && c_parser_gimple_parse_bb_spec_څنډه_probability (label, parser,
							     &dest_شاخص, &prob))
	parser.ټېل_څنډه (parser.current_bb->شاخص, dest_شاخص,
			  څنډه_TRUE_ارزښت, prob);
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

  إذا (c_parser_بل_token_is_keyword (parser, RID_ELSE))
    c_parser_consume_token (parser);
  وإلا
    {
      c_parser_error (parser, "expected else statement");
      أرجع;
    }

  إذا (c_parser_بل_token_is_keyword (parser, RID_GOTO))
    {
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      إذا (! c_parser_بل_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected label");
	  أرجع;
	}
      label = c_parser_peek_token (parser)->ارزښت;
      c_parser_consume_token (parser);
      صحيح dest_شاخص;
      profile_probability prob;
      إذا ((cfun->curr_properties & PROP_cfg)
	  && c_parser_gimple_parse_bb_spec_څنډه_probability (label, parser,
							     &dest_شاخص, &prob))
	parser.ټېل_څنډه (parser.current_bb->شاخص, dest_شاخص,
			  څنډه_FALSE_ارزښت, prob);
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

  إذا (cond != error_mark_غوټه)
    gimple_seq_جمع_کړه_stmt_without_update (seq, gimple_build_cond_from_ونه (cond, t_label,
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
  c_بیان cond_بیان;
  ونه case_label, label;
  auto_vec<ونه> labels;
  ونه default_label = NULL_ونه;
  c_parser_consume_token (parser);

  إذا (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    أرجع;
  cond_بیان = c_parser_gimple_postfix_افاده (parser);
  إذا (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    أرجع;

  إذا (! c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    أرجع;

  طالما (c_parser_بل_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      إذا (c_parser_بل_token_is (parser, CPP_EOF))
	{
	  c_parser_error (parser, "expected statement");
	  أرجع;
	}

      بدل (c_parser_peek_token (parser)->keyword)
	{
	حالة RID_CASE:
	  {
	    c_بیان exp1;
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);

	    إذا (c_parser_بل_token_is (parser, CPP_NAME)
		|| c_parser_peek_token (parser)->type == CPP_شمېره)
	      exp1 = c_parser_gimple_postfix_افاده (parser);
	    وإلا
	      {
		c_parser_error (parser, "expected expression");
		أرجع;
	      }

	    إذا (c_parser_بل_token_is (parser, CPP_COLON))
	      {
		c_parser_consume_token (parser);
		إذا (c_parser_بل_token_is (parser, CPP_NAME))
		  {
		    label = c_parser_peek_token (parser)->ارزښت;
		    c_parser_consume_token (parser);
		    ونه decl = lookup_label_for_goto (loc, label);
		    case_label = build_case_label (exp1.ارزښت, NULL_ونه,
						   decl);
		    labels.خوندي_ټېل (case_label);
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
	    إذا (c_parser_بل_token_is (parser, CPP_COLON))
	      {
		c_parser_consume_token (parser);
		إذا (c_parser_بل_token_is (parser, CPP_NAME))
		  {
		    label = c_parser_peek_token (parser)->ارزښت;
		    c_parser_consume_token (parser);
		    ونه decl = lookup_label_for_goto (loc, label);
		    default_label = build_case_label (NULL_ونه, NULL_ونه,
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

  إذا (cond_بیان.ارزښت != error_mark_غوټه)
    {
      gswitch *s = gimple_build_switch (cond_بیان.ارزښت, default_label, labels);
      gimple_seq_جمع_کړه_stmt_without_update (seq, s);
    }
}

/* Parse gimple return statement.  */

ساكن فراغ
c_parser_gimple_return_stmt (gimple_parser &parser, gimple_seq *seq)
{
  location_t loc = c_parser_peek_token (parser)->location;
  gimple *ret = عدم;
  c_parser_consume_token (parser);
  إذا (c_parser_بل_token_is (parser, CPP_SEMICOLON))
    {
      c_پای_gimple_return (loc, NULL_ونه);
      ret = gimple_build_return (عدم);
      gimple_seq_جمع_کړه_stmt_without_update (seq, ret);
    }
  وإلا
    {
      location_t xloc = c_parser_peek_token (parser)->location;
      c_بیان بیان = c_parser_gimple_unary_افاده (parser);
      إذا (بیان.ارزښت != error_mark_غوټه)
	{
	  c_پای_gimple_return (xloc, بیان.ارزښت);
	  ret = gimple_build_return (بیان.ارزښت);
	  gimple_seq_جمع_کړه_stmt_without_update (seq, ret);
	}
    }
}

/* Support function for c_parser_gimple_return_stmt.  */

ساكن فراغ
c_پای_gimple_return (location_t loc, ونه retval)
{
  ونه valtype = ونه_TYPE (ونه_TYPE (current_function_decl));

  /* Use the expansion point to handle cases such as returning NULL
     in a function returning void.  */
  location_t xloc = expansion_ټکی_location_if_دننه_system_سرلیک (loc);

  إذا (ونه_THIS_VOLATILE (current_function_decl))
    warning_at (xloc, 0,
		"function declared %<noreturn%> has a %<return%> statement");

  إذا (! retval)
    current_function_returns_null = 1;
  وإلا إذا (valtype == 0 || VOID_TYPE_P (valtype))
    {
      current_function_returns_null = 1;
      إذا (ونه_کوډ (ونه_TYPE (retval)) != VOID_TYPE)
	{
	  error_at
	    (xloc, "%<return%> with a value, in function returning void");
	  inform (DECL_سرچینه_LOCATION (current_function_decl),
		  "declared here");
	}
    }
  وإلا إذا (ونه_کوډ (valtype) != ونه_کوډ (ونه_TYPE (retval)))
    {
      error_at
	(xloc, "invalid conversion in return statement");
      inform (DECL_سرچینه_LOCATION (current_function_decl),
	      "declared here");
    }
  أرجع;
}
