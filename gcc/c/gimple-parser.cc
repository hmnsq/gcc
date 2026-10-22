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
  gimple_parser (c_parser *p) : parser (p), یالها(), current_bb(عدم) {}
  /* c_parser is not visible here, use composition and fake inheritance
     via a conversion operator.  */
  عملگر c_parser *() { أرجع parser; }
  c_parser *parser;

  /* CFG build state.  */
  صنف gimple_parser_یال
  {
  عام:
    صحيح src;
    صحيح dest;
    صحيح flags;
    profile_probability probability;
  };
  auto_vec<gimple_parser_یال> یالها;
  basic_بلوک current_bb;

  فراغ افزودن_یال (صحيح, صحيح, صحيح, profile_probability);
};

فراغ
gimple_parser::افزودن_یال (صحيح src, صحيح dest, صحيح flags,
			  profile_probability prob)
{
  gimple_parser_یال e;
  e.src = src;
  e.dest = dest;
  e.flags = flags;
  e.probability = prob;
  یالها.امن_افزودن (e);
}


/* Gimple parsing functions.  */
ساكن منطقي c_parser_gimple_compound_statement (gimple_parser &, gimple_seq *);
ساكن فراغ c_parser_gimple_label (gimple_parser &, gimple_seq *);
ساكن فراغ c_parser_gimple_statement (gimple_parser &, gimple_seq *);
ساكن بنية c_عبارت c_parser_gimple_دودویی_عبارت (gimple_parser &, درخت);
ساكن بنية c_عبارت c_parser_gimple_unary_عبارت (gimple_parser &);
ساكن بنية c_عبارت c_parser_gimple_postfix_عبارت
			(gimple_parser &, درخت = error_mark_گره);
ساكن بنية c_عبارت c_parser_gimple_postfix_عبارت_after_primary
			(gimple_parser &, location_t, بنية c_عبارت);
ساكن فراغ c_parser_gimple_declaration (gimple_parser &);
ساكن فراغ c_parser_gimple_goto_stmt (gimple_parser &, location_t,
				       درخت, gimple_seq *);
ساكن فراغ c_parser_gimple_try_stmt (gimple_parser &, gimple_seq *);
ساكن فراغ c_parser_gimple_if_stmt (gimple_parser &, gimple_seq *);
ساكن فراغ c_parser_gimple_switch_stmt (gimple_parser &, gimple_seq *);
ساكن فراغ c_parser_gimple_return_stmt (gimple_parser &, gimple_seq *);
ساكن فراغ c_پایان_gimple_return (location_t, درخت);
ساكن درخت c_parser_gimple_paren_condition (gimple_parser &);
ساكن فراغ c_parser_gimple_عبارت_list (gimple_parser &, vec<درخت> *);


/* Much like parser_build_unary_op, but avoid applying default conversions.  */

ساكن c_عبارت
gimple_parser_build_unary_op (location_t loc,
			      تعداد درخت_کد_2 کد, بنية c_عبارت arg)
{
  بنية c_عبارت نتیجه;

  نتیجه.original_کد = کد;
  نتیجه.original_type = عدم;
  نتیجه.m_decimal = 0;

  إذا (reject_gcc_builtin (arg.مقدار))
    {
      نتیجه.مقدار = error_mark_گره;
    }
  وإلا
    {
      نتیجه.مقدار = build_unary_op (loc, کد, arg.مقدار, درست);

      إذا (درخت_سرریز_P (نتیجه.مقدار) && !درخت_سرریز_P (arg.مقدار))
	سرریز_warning (loc, نتیجه.مقدار, arg.مقدار);
    }

  /* We are typically called when parsing a prefix token at LOC acting on
     ARG.  Reflect this by updating the source range of the result to
     start at LOC and end at the end of ARG.  */
  مجموعه_c_عبارت_منبع_range (&نتیجه,
			   loc, arg.get_پایان ());

  أرجع نتیجه;
}

/* See if VAL is an identifier matching __BB<num> and return <num>
   in *INDEX.  */

ساكن منطقي
c_parser_gimple_parse_bb_spec (درخت val, صحيح *شاخص)
{
  إذا (!startswith (IDENTIFIER_اشاره_گر (val), "__BB"))
    أرجع خطأ;

  ثابت حرف *bb = IDENTIFIER_اشاره_گر (val) + 4;
  إذا (! ISDIGIT (*bb))
    أرجع خطأ;

  حرف *pend;
  errno = 0;
  ثابت بیعلامت دراز عدد = strtoul (bb, &pend, 10);
  إذا (errno == ERANGE
      || *pend != '\0'
      || عدد > بیشترین_صحیح)
    أرجع خطأ;

  *شاخص = عدد;
  أرجع درست;
}

/* See if VAL is an identifier matching __BB<num> and return <num>
   in *INDEX.  Return true if so and parse also FREQUENCY of
   the edge.  */


ساكن منطقي
c_parser_gimple_parse_bb_spec_یال_probability (درخت val,
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
      إذا (c_parser_بعدی_token_is (parser, CPP_OPEN_PAREN))
	{
	  درخت f;
	  c_parser_consume_token (parser);
	  إذا (!c_parser_بعدی_token_is (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected frequency quality");
	      أرجع خطأ;
	    }

	  profile_quality quality;
	  ثابت حرف *v
	    = IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار);
	  إذا (!parse_profile_quality (v, &quality))
	    {
	      c_parser_error (parser, "unknown profile quality");
	      أرجع خطأ;
	    }

	  c_parser_consume_token (parser);
	  إذا (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    أرجع خطأ;

	  إذا (!c_parser_بعدی_token_is (parser, CPP_عدد)
	      || (درخت_کد (f = c_parser_peek_token (parser)->مقدار)
		  != INTEGER_CST))
	    {
	      c_parser_error (parser, "expected frequency value");
	      أرجع خطأ;
	    }

	  بیعلامت صحيح مقدار = درخت_INT_CST_کم (f);
	  *probability = profile_probability (مقدار, quality);

	  c_parser_consume_token (parser);
	  إذا (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    أرجع خطأ;

	  إذا (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    أرجع خطأ;
	}

      أرجع درست;
    }

  أرجع خطأ;

}

/* Parse the body of a function declaration marked with "__GIMPLE".  */

فراغ
c_parser_parse_gimple_body (c_parser *cparser, حرف *gimple_pass,
			    تعداد c_declspec_il cdil,
			    profile_شمار مدخل_bb_شمار)
{
  gimple_parser parser (cparser);
  gimple_seq seq = عدم;
  gimple_seq body = عدم;
  درخت stmt = افزودن_stmt_list ();
  افزودن_scope ();
  location_t loc1 = c_parser_peek_token (parser)->location;

  cfun->pass_startwith = gimple_pass;
  init_درخت_ssa (cfun);

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
      gimple_ثبات_cfg_hooks ();
      init_خالی_درخت_cfg ();
      parser.current_bb = مدخل_بلوک_PTR_FOR_FN (cfun);
      /* Initialize the bare loop structure - we are going to only
         mark headers and leave the rest to fixup.  */
      مجموعه_loops_for_fn (cfun, ggc_cleared_alloc<بنية loops> ());
      init_loops_structure (cfun, loops_for_fn (cfun), 1);
      loops_state_مجموعه (cfun, LOOPS_NEED_FIXUP|LOOPS_MAY_HAVE_مضرب_LATCHES);
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
      gimple_seq_جمع_کن_stmt_without_update (&seq, ret);
    }

  درخت بلوک = برداشت_scope ();
  stmt = برداشت_stmt_list (stmt);
  stmt = c_build_bind_عبارت (loc1, بلوک, stmt);

  بلوک = DECL_INITIAL (current_function_decl);
  بلوک_SUBBLOCKS (بلوک) = NULL_درخت;
  بلوک_CHAIN (بلوک) = NULL_درخت;
  درخت_ASM_WRITTEN (بلوک) = 1;

  إذا (cdil == cdil_gimple)
    {
      gbind *bind_stmt = gimple_build_bind (BIND_عبارت_VARS (stmt), عدم,
					    BIND_عبارت_بلوک (stmt));
      gimple_bind_مجموعه_body (bind_stmt, seq);
      gimple_seq_جمع_کن_stmt_without_update (&body, bind_stmt);
      gimple_مجموعه_body (current_function_decl, body);
    }
  وإلا
    {
      /* Control-flow and binds are lowered, record local decls.  */
      لكل (درخت var = BIND_عبارت_VARS (stmt); var; var = DECL_CHAIN (var))
	إذا (VAR_P (var)
	    && !DECL_EXTERNAL (var))
	  {
	    جمع_کن_local_decl (cfun, var);
	    /* When the middle-end re-gimplifies any expression we might
	       run into the assertion that we've seen the decl in a BIND.  */
	    إذا (!درخت_STATIC (var))
	      DECL_دیده_درون_BIND_عبارت_P (var) = 1;
	  }
      /* We have a CFG.  Build the edges.  */
      لكل (بیعلامت i = 0; i < parser.یالها.درازی (); ++i)
	{
	  یال e = make_یال (BASIC_بلوک_FOR_FN (cfun, parser.یالها[i].src),
			      BASIC_بلوک_FOR_FN (cfun, parser.یالها[i].dest),
			      parser.یالها[i].flags);
	  e->probability = parser.یالها[i].probability;
	}
      /* Add edges for case labels.  */
      basic_بلوک bb;
      FOR_EACH_BB_FN (bb, cfun)
	إذا (یال_شمار (bb->succs) == 0)
	  {
	    إذا (gswitch *sw = امن_dyn_cast <gswitch *> (*gsi_آخرین_bb (bb)))
	      لكل (بیعلامت i = 0; i < gimple_switch_رقم_labels (sw); ++i)
		{
		  basic_بلوک label_bb = gimple_switch_label_bb (cfun, sw, i);
		  make_یال (bb, label_bb, 0);
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
	      لكل (gsi = gsi_شروع_bb (bb); !gsi_انتها_p (gsi);)
		{
		  gimple *stmt = gsi_stmt (gsi);
		  إذا (!gimple_call_داخلی_p (stmt, IFN_PHI))
		    اكسر;

		  gphi *phi = create_phi_گره (gimple_call_lhs (stmt), bb);
		  لكل (بیعلامت i = 0; i < gimple_call_رقم_آرگومانها (stmt); i += 2)
		    {
		      صحيح srcidx = درخت_INT_CST_کم (gimple_call_arg (stmt, i));
		      یال e = پیدا_کن_یال (BASIC_بلوک_FOR_FN (cfun, srcidx), bb);
		      إذا (!e)
			c_parser_error (parser, "edge not found");
		      وإلا
			جمع_کن_phi_arg (phi, gimple_call_arg (stmt, i + 1), e,
				     UNKNOWN_LOCATION);
		    }
		  gsi_remove (&gsi, درست);
		}
	      لكل (; !gsi_انتها_p (gsi); gsi_بعدی (&gsi))
		update_stmt (gsi_stmt (gsi));
	    }
	  /* Fill SSA name gaps, putting them on the freelist and diagnose
	     SSA names without definition.  */
	  لكل (بیعلامت i = 1; i < رقم_ssa_نامها; ++i)
	    إذا (!ssa_name (i))
	      {
		درخت name = make_ssa_name_fn (cfun, integer_type_گره, عدم, i);
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
      مدخل_بلوک_PTR_FOR_FN (cfun)->شمار = مدخل_bb_شمار;
      gcov_type t = param_gimple_fe_computed_hot_bb_آستانه;
      مجموعه_hot_bb_آستانه (t);
      update_max_bb_شمار ();
      cgraph_گره::get_create (cfun->decl);
      cgraph_یال::rebuild_یالها ();
    }

  /* Perform IL validation and if any error is found abort compilation
     of this function by zapping its body.  */
  إذا ((cfun->curr_properties & PROP_cfg)
      && verify_gimple_درون_cfg (cfun, خطأ, خطأ))
    init_خالی_درخت_cfg ();
  وإلا إذا (!(cfun->curr_properties & PROP_cfg)
	   && verify_gimple_درون_seq (gimple_body (current_function_decl), خطأ))
    gimple_مجموعه_body (current_function_decl, عدم);

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
  طالما (c_parser_بعدی_نشانهها_شروع_declaration (parser))
    {
      c_parser_gimple_declaration (parser);
      إذا (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	أرجع خطأ;
    }

  طالما (c_parser_بعدی_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      إذا (c_parser_error (parser))
	{
	  c_parser_skip_until_یافت (parser, CPP_CLOSE_BRACE, عدم);
	  أرجع return_p;
	}
      وإلا إذا (c_parser_بعدی_token_is (parser, CPP_EOF))
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
		إذا (c_parser_بعدی_token_is (parser, CPP_NAME))
		  {
		    درخت label = c_parser_peek_token (parser)->مقدار;
		    c_parser_consume_token (parser);
		    c_parser_gimple_goto_stmt (parser, loc, label, seq);
		    إذا (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      أرجع return_p;
		  }
		}
	      اكسر;
	    حالة RID_RETURN:
	      return_p = درست;
	      c_parser_gimple_return_stmt (parser, seq);
	      إذا (! c_parser_require (parser, CPP_SEMICOLON,
				      "expected %<;%>"))
		أرجع return_p;
	      إذا (cfun->curr_properties & PROP_cfg)
		parser.افزودن_یال (parser.current_bb->شاخص, EXIT_بلوک, 0,
				  profile_probability::uninitialized ());
	      اكسر;
	    افتراضي:
	      اذهب عبارت_stmt;
	    }
	  اكسر;
	حالة CPP_NAME:
	  إذا (c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_gimple_label (parser, seq);
	      اكسر;
	    }
	  إذا (c_parser_بعدی_token_is (parser, CPP_NAME)
	      && c_parser_peek_token (parser)->id_نوع == C_ID_ID
	      && strcmp (IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار),
			 "try") == 0)
	    {
	      c_parser_gimple_try_stmt (parser, seq);
	      اكسر;
	    }
	  /* Basic block specification.
	     __BB (index, ...)  */
	  إذا ((cfun->curr_properties & PROP_cfg)
	      && !strcmp (IDENTIFIER_اشاره_گر
			    (c_parser_peek_token (parser)->مقدار), "__BB"))
	    {
	      c_parser_consume_token (parser);
	      إذا (! c_parser_require (parser, CPP_OPEN_PAREN,
				      "expected %<(%>"))
		أرجع return_p;
	      إذا (c_parser_بعدی_token_is_not (parser, CPP_عدد))
		{
		  c_parser_error (parser, "expected block index");
		  أرجع return_p;
		}
	      درخت tnum = c_parser_peek_token (parser)->مقدار;
	      إذا (درخت_کد (tnum) != INTEGER_CST)
		{
		  c_parser_error (parser, "expected block index");
		  أرجع return_p;
		}
	      صحيح شاخص = درخت_INT_CST_کم (tnum);
	      إذا (شاخص < رقم_FIXED_بلوکها
		  || (شاخص < آخرین_basic_بلوک_for_fn (cfun)
		      && BASIC_بلوک_FOR_FN (cfun, شاخص) != عدم))
		{
		  c_parser_error (parser, "invalid block index");
		  أرجع return_p;
		}
	      صحيح is_loop_سرآیند_از = -1;
	      profile_شمار bb_شمار = profile_شمار::uninitialized ();
	      c_parser_consume_token (parser);
	      طالما (c_parser_بعدی_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  إذا (! c_parser_بعدی_token_is (parser, CPP_NAME))
		    {
		      c_parser_error (parser, "expected block specifier");
		      أرجع return_p;
		    }
		  /* loop_header (NUM)  */
		  إذا (!strcmp (IDENTIFIER_اشاره_گر
			         (c_parser_peek_token (parser)->مقدار),
			       "loop_header"))
		    {
		      c_parser_consume_token (parser);
		      إذا (! c_parser_require (parser, CPP_OPEN_PAREN,
					      "expected %<(%>"))
			أرجع return_p;
		      درخت loop_رقم;
		      إذا (! c_parser_بعدی_token_is (parser, CPP_عدد)
			  || درخت_کد (loop_رقم
					  = c_parser_peek_token (parser)->مقدار)
			       != INTEGER_CST)
			{
			  c_parser_error (parser, "expected loop number");
			  أرجع return_p;
			}
		      c_parser_consume_token (parser);
		      is_loop_سرآیند_از = درخت_INT_CST_کم (loop_رقم);
		      إذا (! c_parser_require (parser, CPP_CLOSE_PAREN,
					      "expected %<)%>"))
			أرجع return_p;
		    }
		  /* Parse profile: quality(value) */
		  وإلا
		    {
		      درخت q;
		      profile_quality quality;
		      درخت v = c_parser_peek_token (parser)->مقدار;
		      إذا (!parse_profile_quality (IDENTIFIER_اشاره_گر (v),
						  &quality))
			{
			  c_parser_error (parser, "unknown block specifier");
			  أرجع خطأ;
			}

		      c_parser_consume_token (parser);
		      إذا (!c_parser_require (parser, CPP_OPEN_PAREN,
					     "expected %<(%>"))
			أرجع خطأ;

		      إذا (!c_parser_بعدی_token_is (parser, CPP_عدد)
			  || (درخت_کد (q = c_parser_peek_token (parser)->مقدار)
			      != INTEGER_CST))
			{
			  c_parser_error (parser, "expected count value");
			  أرجع خطأ;
			}

		      bb_شمار
			= profile_شمار::from_gcov_type (درخت_INT_CST_کم (q),
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
	      إذا (!gimple_seq_خالی_p (*seq))
		{
		  إذا (!parser.current_bb)
		    c_parser_error (parser, "stmts without block");
		  وإلا
		    {
		      gimple_stmt_iterator gsi
			= gsi_شروع_bb (parser.current_bb);
		      gsi_درج_seq_after_without_update (&gsi, *seq,
							   GSI_CONTINUE_LINKING);
		    }
		  *seq = عدم;
		}

	      /* Build an empty block with specified index, linking them
		 in source order.  */
	      basic_بلوک bb = alloc_بلوک ();
	      bb->شاخص = شاخص;
	      link_بلوک (bb, (parser.current_bb ? parser.current_bb
			       : مدخل_بلوک_PTR_FOR_FN (cfun)));
	      إذا (basic_بلوک_info_for_fn (cfun)->درازی () <= (اندازه_t)شاخص)
		vec_امن_grow_cleared (basic_بلوک_info_for_fn (cfun),
				       شاخص + 1, درست);
	      مجموعه_BASIC_بلوک_FOR_FN (cfun, شاخص, bb);
	      إذا (آخرین_basic_بلوک_for_fn (cfun) <= شاخص)
		آخرین_basic_بلوک_for_fn (cfun) = شاخص + 1;
	      n_basic_بلوکها_for_fn (cfun)++;
	      إذا (parser.current_bb->شاخص == مدخل_بلوک)
		parser.افزودن_یال (مدخل_بلوک, bb->شاخص, یال_FALLTHRU,
				  profile_probability::always ());

	      /* We leave the proper setting to fixup.  */
	      صنف loop *loop_father = loops_for_fn (cfun)->درخت_ریشه;
	      /* If the new block is a loop header, allocate a loop
		 struct.  Fixup will take care of proper placement within
		 the loop tree.  */
	      إذا (is_loop_سرآیند_از != -1)
		{
		  إذا (عدد_از_loops (cfun) > (بیعلامت)is_loop_سرآیند_از
		      && get_loop (cfun, is_loop_سرآیند_از) != عدم)
		    {
		      c_parser_error (parser, "duplicate loop header");
		    }
		  وإلا
		    {
		      صنف loop *loop = alloc_loop ();
		      loop->رقم = is_loop_سرآیند_از;
		      loop->سرآیند = bb;
		      إذا (عدد_از_loops (cfun) <= (بیعلامت)is_loop_سرآیند_از)
			vec_امن_grow_cleared (loops_for_fn (cfun)->larray,
					       is_loop_سرآیند_از + 1, درست);
		      (*loops_for_fn (cfun)->larray)[is_loop_سرآیند_از] = loop;
		      flow_loop_درخت_گره_جمع_کن (loops_for_fn (cfun)->درخت_ریشه,
					       loop);
		    }
		  loop_father = get_loop (cfun, is_loop_سرآیند_از);
		}
	      bb->loop_father = loop_father;
	      bb->شمار = bb_شمار;

	      /* Stmts now go to the new block.  */
	      parser.current_bb = bb;
	      اكسر;
	    }
	  اذهب عبارت_stmt;

	حالة CPP_SEMICOLON:
	  {
	    /* Empty stmt.  */
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);
	    gimple *nop = gimple_build_nop ();
	    gimple_مجموعه_location (nop, loc);
	    gimple_seq_جمع_کن_stmt_without_update (seq, nop);
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
عبارت_stmt:
	  c_parser_gimple_statement (parser, seq);
	  إذا (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	    c_parser_skip_until_یافت (parser, CPP_SEMICOLON, عدم);
	}
    }
  c_parser_consume_token (parser);

  /* Put stmts parsed in the current block.  */
  إذا ((cfun->curr_properties & PROP_cfg)
      && !gimple_seq_خالی_p (*seq))
    {
      إذا (!parser.current_bb)
	c_parser_error (parser, "stmts without block");
      وإلا
	{
	  gimple_stmt_iterator gsi = gsi_شروع_bb (parser.current_bb);
	  gsi_درج_seq_after_without_update (&gsi, *seq,
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
  بنية c_عبارت lhs, rhs;
  gimple *تخصیص_بده = عدم;
  location_t loc;
  درخت arg = NULL_درخت;
  auto_vec<درخت> vargs;

  lhs = c_parser_gimple_unary_عبارت (parser);
  loc = عبارت_LOCATION (lhs.مقدار);
  rhs.مجموعه_error ();

  /* GIMPLE call statement without LHS.  */
  إذا (c_parser_بعدی_token_is (parser, CPP_SEMICOLON)
      && درخت_کد (lhs.مقدار) == CALL_عبارت)
    {
      gimple *call;
      call = gimple_build_call_from_درخت (lhs.مقدار, عدم);
      gimple_seq_جمع_کن_stmt_without_update (seq, call);
      gimple_مجموعه_location (call, loc);
      أرجع;
    }

  /* All following cases are statements with LHS.  */
  إذا (! c_parser_require (parser, CPP_EQ, "expected %<=%>"))
    أرجع;

  /* Eat and ignore {v} right after the =, the has_volatile_ops is
     redundant and re-computed by the operand scanner.  */
  إذا (c_parser_بعدی_token_is (parser, CPP_OPEN_BRACE)
      && !(c_parser_peek_token (parser)->flags & PREV_WHITE)
      && c_parser_peek_2nd_token (parser)->type == CPP_NAME
      && !(c_parser_peek_2nd_token (parser)->flags & PREV_WHITE)
      && strcmp ("v", IDENTIFIER_اشاره_گر
			(c_parser_peek_2nd_token (parser)->مقدار)) == 0
      && c_parser_peek_nth_token (parser, 3)->type == CPP_CLOSE_BRACE
      && !(c_parser_peek_nth_token (parser, 3)->flags & PREV_WHITE))
    {
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }

  /* Cast expression.  */
  إذا (c_parser_بعدی_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_typename (c_parser_peek_2nd_token (parser)))
    {
      c_parser_consume_token (parser);
      بنية c_type_name *type_name = c_parser_type_name (parser);
      c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      إذا (type_name == عدم)
	أرجع;
      /* ???  The actual type used in the cast expression is ignored as
         in GIMPLE it is encoded by the type of the LHS.  */
      rhs = c_parser_gimple_postfix_عبارت (parser);
      إذا (lhs.مقدار != error_mark_گره
	  && rhs.مقدار != error_mark_گره)
	{
	  تعداد درخت_کد_2 کد = NOP_عبارت;
	  إذا (FLOAT_TYPE_P (درخت_TYPE (lhs.مقدار))
	      && ! FLOAT_TYPE_P (درخت_TYPE (rhs.مقدار)))
	    کد = FLOAT_عبارت;
	  وإلا إذا (! FLOAT_TYPE_P (درخت_TYPE (lhs.مقدار))
		   && FLOAT_TYPE_P (درخت_TYPE (rhs.مقدار)))
	    کد = FIX_TRUNC_عبارت;
	  تخصیص_بده = gimple_build_تخصیص_بده (lhs.مقدار, کد, rhs.مقدار);
	  gimple_seq_جمع_کن_stmt_without_update (seq, تخصیص_بده);
	  gimple_مجموعه_location (تخصیص_بده, loc);
	  أرجع;
	}
    }

  /* Unary expression.  */
  بدل (c_parser_peek_token (parser)->type)
    {
    حالة CPP_NAME:
      {
	درخت id = c_parser_peek_token (parser)->مقدار;
	إذا (strcmp (IDENTIFIER_اشاره_گر (id), "__ABS") == 0
	    || strcmp (IDENTIFIER_اشاره_گر (id), "__ABSU") == 0
	    || strcmp (IDENTIFIER_اشاره_گر (id), "__MIN") == 0
	    || strcmp (IDENTIFIER_اشاره_گر (id), "__MAX") == 0
	    || strcmp (IDENTIFIER_اشاره_گر (id), "__BIT_INSERT") == 0
	    || strcmp (IDENTIFIER_اشاره_گر (id), "__VEC_PERM") == 0)
	  اذهب build_unary_عبارت;
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
    build_unary_عبارت:
      rhs = c_parser_gimple_unary_عبارت (parser);
      إذا (rhs.مقدار != error_mark_گره)
	{
	  تخصیص_بده = gimple_build_تخصیص_بده (lhs.مقدار, rhs.مقدار);
	  gimple_مجموعه_location (تخصیص_بده, loc);
	  gimple_seq_جمع_کن_stmt_without_update (seq, تخصیص_بده);
	}
      أرجع;

    افتراضي:;
    }

  /* GIMPLE PHI statement.  */
  إذا (c_parser_بعدی_token_is_keyword (parser, RID_PHI))
    {
      c_parser_consume_token (parser);

      إذا (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	أرجع;

      إذا (c_parser_بعدی_token_is (parser, CPP_OPEN_PAREN))
	c_parser_consume_token (parser);

      طالما (c_parser_بعدی_token_is_not (parser, CPP_CLOSE_PAREN))
	{
	  إذا (c_parser_بعدی_token_is (parser, CPP_NAME)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      arg = c_parser_peek_token (parser)->مقدار;
	      c_parser_consume_token (parser);
	      إذا (c_parser_بعدی_token_is (parser, CPP_COLON))
		c_parser_consume_token (parser);
	      صحيح src_شاخص = -1;
	      إذا (!c_parser_gimple_parse_bb_spec (arg, &src_شاخص))
		c_parser_error (parser, "invalid source block specification");
	      vargs.امن_افزودن (اندازه_int (src_شاخص));
	    }
	  وإلا إذا (c_parser_بعدی_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  وإلا
	    {
	      arg = c_parser_gimple_unary_عبارت (parser).مقدار;
	      vargs.امن_افزودن (arg);
	    }
	}

      c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");

      /* Build internal function for PHI.  */
      gcall *call_stmt = gimple_build_call_داخلی_vec (IFN_PHI, vargs);
      gimple_call_مجموعه_lhs (call_stmt, lhs.مقدار);
      gimple_مجموعه_location (call_stmt, UNKNOWN_LOCATION);
      gimple_seq_جمع_کن_stmt_without_update (seq, call_stmt);
      أرجع;
    }

  /* GIMPLE call with lhs.  */
  إذا (c_parser_بعدی_token_is (parser, CPP_DOT)
      || (c_parser_بعدی_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN
	  && lookup_name (c_parser_peek_token (parser)->مقدار)))
    {
      rhs = c_parser_gimple_unary_عبارت (parser);
      إذا (rhs.مقدار != error_mark_گره)
	{
	  gimple *call = gimple_build_call_from_درخت (rhs.مقدار, عدم);
	  gimple_call_مجموعه_lhs (call, lhs.مقدار);
	  gimple_seq_جمع_کن_stmt_without_update (seq, call);
	  gimple_مجموعه_location (call, loc);
	}
      أرجع;
    }

  rhs = c_parser_gimple_دودویی_عبارت (parser, درخت_TYPE (lhs.مقدار));
  إذا (lhs.مقدار != error_mark_گره
      && rhs.مقدار != error_mark_گره)
    {
      /* If we parsed an identifier and the next token  is a '?' then parse
	 a conditional expression.  */
      إذا (SSA_VAR_P (rhs.مقدار) && c_parser_بعدی_token_is (parser, CPP_QUERY))
	{
	  بنية c_عبارت trueval, falseval;
	  c_parser_consume_token (parser);
	  trueval = c_parser_gimple_postfix_عبارت (parser);
	  falseval.مجموعه_error ();
	  إذا (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    falseval = c_parser_gimple_postfix_عبارت (parser);
	  إذا (trueval.مقدار == error_mark_گره
	      || falseval.مقدار == error_mark_گره)
	    أرجع;
	  rhs.مقدار = build3_loc (loc,
				  وکتور_TYPE_P (درخت_TYPE (rhs.مقدار))
				  ? VEC_COND_عبارت : COND_عبارت,
				  درخت_TYPE (trueval.مقدار),
				  rhs.مقدار, trueval.مقدار, falseval.مقدار);
	}
      إذا (get_gimple_rhs_class (درخت_کد (rhs.مقدار)) == GIMPLE_INVALID_RHS)
	{
	  c_parser_error (parser, "unexpected RHS for assignment");
	  أرجع;
	}
      تخصیص_بده = gimple_build_تخصیص_بده (lhs.مقدار, rhs.مقدار);
      gimple_seq_جمع_کن_stmt_without_update (seq, تخصیص_بده);
      gimple_مجموعه_location (تخصیص_بده, loc);
    }
  أرجع;
}

/* A mapping between an identifier to a tree code for binary operations. */
ساكن ثابت std::pair<ثابت حرف *, درخت_کد_2> gimple_دودویی_identifier_کد[] =
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
    {"__ROUND_DIV", دور_DIV_عبارت},
    {"__EXACT_DIV", EXACT_DIV_عبارت},
    {"__CEIL_DIV", CEIL_DIV_عبارت},
    {"__FLOOR_MOD", FLOOR_MOD_عبارت},
    {"__ROUND_MOD", دور_MOD_عبارت},
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

ساكن c_عبارت
c_parser_gimple_دودویی_عبارت (gimple_parser &parser, درخت ret_type)
{
  /* Location of the binary operator.  */
  بنية c_عبارت ret, lhs, rhs;
  تعداد درخت_کد_2 کد = ERROR_MARK;
  ret.مجموعه_error ();
  lhs = c_parser_gimple_postfix_عبارت (parser, ret_type);
  إذا (c_parser_error (parser))
    أرجع ret;
  بدل (c_parser_peek_token (parser)->type)
    {
    حالة CPP_MULT:
      کد = MULT_عبارت;
      اكسر;
    حالة CPP_DIV:
      کد = TRUNC_DIV_عبارت;
      اكسر;
    حالة CPP_MOD:
      کد = TRUNC_MOD_عبارت;
      اكسر;
    حالة CPP_PLUS:
      إذا (اشاره_گر_TYPE_P (درخت_TYPE (lhs.مقدار)))
	کد = اشاره_گر_PLUS_عبارت;
      وإلا
	کد = PLUS_عبارت;
      اكسر;
    حالة CPP_MINUS:
      إذا (اشاره_گر_TYPE_P (درخت_TYPE (lhs.مقدار)))
	کد = اشاره_گر_DIFF_عبارت;
      وإلا
	کد = MINUS_عبارت;
      اكسر;
    حالة CPP_LSHIFT:
      کد = LSHIFT_عبارت;
      اكسر;
    حالة CPP_RSHIFT:
      کد = RSHIFT_عبارت;
      اكسر;
    حالة CPP_LESS:
      کد = LT_عبارت;
      اكسر;
    حالة CPP_GREATER:
      کد = GT_عبارت;
      اكسر;
    حالة CPP_LESS_EQ:
      کد = LE_عبارت;
      اكسر;
    حالة CPP_GREATER_EQ:
      کد = GE_عبارت;
      اكسر;
    حالة CPP_EQ_EQ:
      کد = EQ_عبارت;
      اكسر;
    حالة CPP_NOT_EQ:
      کد = NE_عبارت;
      اكسر;
    حالة CPP_AND:
      کد = بیت_AND_عبارت;
      اكسر;
    حالة CPP_XOR:
      کد = بیت_XOR_عبارت;
      اكسر;
    حالة CPP_OR:
      کد = بیت_IOR_عبارت;
      اكسر;
    حالة CPP_AND_AND:
      c_parser_error (parser, "%<&&%> not valid in GIMPLE");
      أرجع ret;
    حالة CPP_OR_OR:
      c_parser_error (parser, "%<||%> not valid in GIMPLE");
      أرجع ret;
    حالة CPP_NAME:
      {
	درخت id = c_parser_peek_token (parser)->مقدار;
	لكل (خودکار &p : gimple_دودویی_identifier_کد)
	  {
	    إذا (strcmp (IDENTIFIER_اشاره_گر (id), p.اولی) == 0)
	      {
		کد = p.دومی;
		اكسر;
	      }
	  }
	إذا (کد != ERROR_MARK)
	  اكسر;
      }
      /* Fallthru.  */
    افتراضي:
      /* Not a binary expression.  */
      أرجع lhs;
    }
  location_t ret_loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  rhs = c_parser_gimple_postfix_عبارت (parser);
  إذا (lhs.مقدار != error_mark_گره && rhs.مقدار != error_mark_گره)
    ret.مقدار = build2_loc (ret_loc, کد, ret_type, lhs.مقدار, rhs.مقدار);
  أرجع ret;
}

/* Parse a gimple parentized binary expression.  */

ساكن c_عبارت
c_parser_gimple_parentized_دودویی_عبارت (gimple_parser &parser,
					      location_t op_loc,
					      درخت_کد_2 کد)
{
  بنية c_عبارت ret;
  ret.مجموعه_error ();

  c_parser_consume_token (parser);
  إذا (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    أرجع ret;
  c_عبارت op1 = c_parser_gimple_postfix_عبارت (parser);
  إذا (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    أرجع ret;
  c_عبارت op2 = c_parser_gimple_postfix_عبارت (parser);
  إذا (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    أرجع ret;

  إذا (op1.مقدار != error_mark_گره && op2.مقدار != error_mark_گره)
    ret.مقدار = build2_loc (op_loc,
			    کد, درخت_TYPE (op1.مقدار), op1.مقدار, op2.مقدار);
  أرجع ret;
}

/* Parse a gimple parentized binary expression.  */

ساكن c_عبارت
c_parser_gimple_parentized_ternary_عبارت (gimple_parser &parser,
					       location_t op_loc,
					       درخت_کد_2 کد)
{
  بنية c_عبارت ret;
  ret.مجموعه_error ();

  c_parser_consume_token (parser);
  إذا (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    أرجع ret;
  c_عبارت op1 = c_parser_gimple_postfix_عبارت (parser);
  إذا (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    أرجع ret;
  c_عبارت op2 = c_parser_gimple_postfix_عبارت (parser);
  إذا (!c_parser_require (parser, CPP_COMMA, "expected %<)%>"))
    أرجع ret;
  c_عبارت op3 = c_parser_gimple_postfix_عبارت (parser);
  إذا (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    أرجع ret;

  إذا (op1.مقدار != error_mark_گره
      && op2.مقدار != error_mark_گره
      && op3.مقدار != error_mark_گره)
    ret.مقدار = build3_loc (op_loc,
			    کد, درخت_TYPE (op1.مقدار),
			    op1.مقدار, op2.مقدار, op3.مقدار);
  أرجع ret;
}

/* Parse gimple unary expression.

   gimple-unary-expression:
     gimple-postfix-expression
     unary-operator gimple-postfix-expression

   unary-operator: one of
     & * + - ~ abs_expr
*/

ساكن c_عبارت
c_parser_gimple_unary_عبارت (gimple_parser &parser)
{
  بنية c_عبارت ret, op;
  location_t op_loc = c_parser_peek_token (parser)->location;
  location_t پایان;
  ret.مجموعه_error ();
  بدل (c_parser_peek_token (parser)->type)
    {
    حالة CPP_AND:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_عبارت (parser);
      mark_exp_read (op.مقدار);
      أرجع gimple_parser_build_unary_op (op_loc, ADDR_عبارت, op);
    حالة CPP_MULT:
      {
	c_parser_consume_token (parser);
	op = c_parser_gimple_postfix_عبارت (parser);
	إذا (op.مقدار == error_mark_گره)
	  أرجع ret;
	إذا (! اشاره_گر_TYPE_P (درخت_TYPE (op.مقدار)))
	  {
	    error_at (op_loc, "expected pointer as argument of unary %<*%>");
	    أرجع ret;
	  }
	پایان = op.get_پایان ();
	location_t combined_loc = make_location (op_loc, op_loc, پایان);
	ret.مقدار = build_simple_mem_ref_loc (combined_loc, op.مقدار);
	درخت_SIDE_EFFECTS (ret.مقدار)
	  = درخت_THIS_VOLATILE (ret.مقدار)
	  = TYPE_VOLATILE (درخت_TYPE (درخت_TYPE (op.مقدار)));
	ret.src_range.m_شروع = op_loc;
	ret.src_range.m_پایان = پایان;
	أرجع ret;
      }
    حالة CPP_PLUS:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_عبارت (parser);
      أرجع gimple_parser_build_unary_op (op_loc, CONVERT_عبارت, op);
    حالة CPP_MINUS:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_عبارت (parser);
      أرجع gimple_parser_build_unary_op (op_loc, NEGATE_عبارت, op);
    حالة CPP_COMPL:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_عبارت (parser);
      أرجع gimple_parser_build_unary_op (op_loc, بیت_NOT_عبارت, op);
    حالة CPP_NOT:
      c_parser_error (parser, "%<!%> not valid in GIMPLE");
      أرجع ret;
    حالة CPP_KEYWORD:
      بدل (c_parser_peek_token (parser)->keyword)
	{
	حالة RID_REALPART:
	  c_parser_consume_token (parser);
	  op = c_parser_gimple_postfix_عبارت (parser);
	  أرجع gimple_parser_build_unary_op (op_loc, REALPART_عبارت, op);
	حالة RID_IMAGPART:
	  c_parser_consume_token (parser);
	  op = c_parser_gimple_postfix_عبارت (parser);
	  أرجع gimple_parser_build_unary_op (op_loc, IMAGPART_عبارت, op);
	افتراضي:
	  أرجع c_parser_gimple_postfix_عبارت (parser);
	}
    حالة CPP_NAME:
	{
	  درخت id = c_parser_peek_token (parser)->مقدار;
	  إذا (strcmp (IDENTIFIER_اشاره_گر (id), "__ABS") == 0)
	    {
	      c_parser_consume_token (parser);
	      op = c_parser_gimple_postfix_عبارت (parser);
	      أرجع gimple_parser_build_unary_op (op_loc, ABS_عبارت, op);
	    }
	  وإلا إذا (strcmp (IDENTIFIER_اشاره_گر (id), "__ABSU") == 0)
	    {
	      c_parser_consume_token (parser);
	      op = c_parser_gimple_postfix_عبارت (parser);
	      أرجع gimple_parser_build_unary_op (op_loc, ABSU_عبارت, op);
	    }
	  وإلا إذا (strcmp (IDENTIFIER_اشاره_گر (id), "__MIN") == 0)
	    أرجع c_parser_gimple_parentized_دودویی_عبارت (parser,
								 op_loc,
								 MIN_عبارت);
	  وإلا إذا (strcmp (IDENTIFIER_اشاره_گر (id), "__MAX") == 0)
	    أرجع c_parser_gimple_parentized_دودویی_عبارت (parser,
								 op_loc,
								 MAX_عبارت);
	  وإلا إذا (strcmp (IDENTIFIER_اشاره_گر (id), "__VEC_PERM") == 0)
	    أرجع c_parser_gimple_parentized_ternary_عبارت
			(parser, op_loc, VEC_PERM_عبارت);
	  وإلا إذا (strcmp (IDENTIFIER_اشاره_گر (id), "__BIT_INSERT") == 0)
	    {
	      /* __BIT_INSERT '(' postfix-expression, postfix-expression,
			          integer ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      إذا (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_عبارت op0 = c_parser_gimple_postfix_عبارت (parser);
		  c_parser_skip_until_یافت (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_عبارت op1 = c_parser_gimple_postfix_عبارت (parser);
		  c_parser_skip_until_یافت (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_عبارت op2 = c_parser_gimple_postfix_عبارت (parser);
		  إذا (درخت_کد (op2.مقدار) != INTEGER_CST
		      || !int_میگنجد_type_p (op2.مقدار, bitsizetype))
		    c_parser_error (parser, "expected constant offset");
		  c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  إذا (op0.مقدار != error_mark_گره
		      && op1.مقدار != error_mark_گره
		      && درخت_کد (op2.مقدار) == INTEGER_CST)
		    ret.مقدار = build3_loc (loc, بیت_درج_عبارت,
					    درخت_TYPE (op0.مقدار),
					    op0.مقدار, op1.مقدار,
					    fold_convert (bitsizetype,
							  op2.مقدار));
		}
	      أرجع ret;
	    }
	  وإلا
	    أرجع c_parser_gimple_postfix_عبارت (parser);
	}
    افتراضي:
      أرجع c_parser_gimple_postfix_عبارت (parser);
    }
}

/* Decompose ID into base name (ID until ver_offset) and VERSION.  Return
   true if ID matches a SSA name.  */

ساكن منطقي
c_parser_parse_ssa_name_id (درخت id, بیعلامت *نسخه, بیعلامت *ver_جابه_جایی)
{
  ثابت حرف *token = IDENTIFIER_اشاره_گر (id);
  ثابت حرف *var_نسخه = strrchr (token, '_');
  إذا (! var_نسخه)
    أرجع خطأ;

  *ver_جابه_جایی = var_نسخه - token;
  لكل (ثابت حرف *p = var_نسخه + 1; *p; ++p)
    إذا (! ISDIGIT (*p))
      أرجع خطأ;
  *نسخه = atoi (var_نسخه + 1);
  أرجع *نسخه > 0;
}

/* Get at the actual SSA name ID with VERSION starting at VER_OFFSET.
   TYPE is the type if the SSA name is being declared.  */

ساكن درخت
c_parser_parse_ssa_name (gimple_parser &parser,
			 درخت id, درخت type, بیعلامت نسخه,
			 بیعلامت ver_جابه_جایی)
{
  درخت name = NULL_درخت;
  ثابت حرف *token = IDENTIFIER_اشاره_گر (id);

  إذا (ver_جابه_جایی == 0)
    {
      /* Anonymous unnamed SSA name.  */
      إذا (نسخه < رقم_ssa_نامها)
	name = ssa_name (نسخه);
      إذا (! name)
	{
	  إذا (! type)
	    {
	      c_parser_error (parser, "SSA name undeclared");
	      أرجع error_mark_گره;
	    }
	  name = make_ssa_name_fn (cfun, type, عدم, نسخه);
	}
    }
  وإلا
    {
      إذا (نسخه < رقم_ssa_نامها)
	name = ssa_name (نسخه);
      إذا (! name)
	{
	  /* Separate var name from version.  */
	  حرف *var_name = XNEWVEC (حرف, ver_جابه_جایی + 1);
	  کپی_حافظه (var_name, token, ver_جابه_جایی);
	  var_name[ver_جابه_جایی] = '\0';
	  /* lookup for parent decl.  */
	  id = get_identifier (var_name);
	  درخت والد = lookup_name (id);
	  XDELETEVEC (var_name);
	  إذا (! والد || والد == error_mark_گره)
	    {
	      c_parser_error (parser, "base variable or SSA name undeclared");
	      أرجع error_mark_گره;
	    }
	  إذا (!(VAR_P (والد)
		|| درخت_کد (والد) == PARM_DECL
		|| درخت_کد (والد) == نتیجه_DECL))
	    {
	      error ("invalid base %qE for SSA name", والد);
	      أرجع error_mark_گره;
	    }
	  name = make_ssa_name_fn (cfun, والد,
				   gimple_build_nop (), نسخه);
	}
    }

  أرجع name;
}

/* Parse a gimple call to an internal function.

   gimple-call-internal:
     . identifier ( gimple-argument-expression-list[opt] )  */

ساكن بنية c_عبارت
c_parser_gimple_call_داخلی (gimple_parser &parser)
{
  بنية c_عبارت عبارت;
  عبارت.مجموعه_error ();

  gcc_assert (c_parser_بعدی_token_is (parser, CPP_DOT));
  c_parser_consume_token (parser);
  location_t loc = c_parser_peek_token (parser)->location;
  إذا (!c_parser_بعدی_token_is (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_نوع != C_ID_ID)
    {
      c_parser_error (parser, "expecting internal function name");
      أرجع عبارت;
    }
  درخت id = c_parser_peek_token (parser)->مقدار;
  داخلی_fn ifn = lookup_داخلی_fn (IDENTIFIER_اشاره_گر (id));
  c_parser_consume_token (parser);
  إذا (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    {
      auto_vec<درخت> exprlist;
      إذا (!c_parser_بعدی_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_gimple_عبارت_list (parser, &exprlist);
      c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      إذا (ifn == IFN_آخرین)
	error_at (loc, "unknown internal function %qE", id);
      وإلا
	{
	  عبارت.مقدار = build_call_عبارت_داخلی_loc_array
	    (loc, ifn, void_type_گره, exprlist.درازی (),
	     exprlist.آدرس ());
	  عبارت.original_کد = ERROR_MARK;
	  عبارت.original_type = عدم;
	  عبارت.m_decimal = 0;
	}
    }
  أرجع عبارت;
}

/* Parse '<' type [',' alignment] '>' and return a type on success
   and NULL_TREE on error.  */

ساكن درخت
c_parser_gimple_typespec (gimple_parser &parser)
{
  بنية c_type_name *type_name = عدم;
  درخت alignment = NULL_درخت;
  إذا (c_parser_require (parser, CPP_LESS, "expected %<<%>"))
    {
      type_name = c_parser_type_name (parser);
      /* Optional alignment.  */
      إذا (c_parser_بعدی_token_is (parser, CPP_COMMA))
	{
	  c_parser_consume_token (parser);
	  alignment
	      = c_parser_gimple_postfix_عبارت (parser).مقدار;
	}
      c_parser_skip_until_یافت (parser,
				 CPP_GREATER, "expected %<>%>");
    }
  إذا (!type_name)
    أرجع NULL_درخت;
  درخت tem;
  درخت type = groktypename (type_name, &tem, عدم);
  إذا (alignment)
    type = build_aligned_type (type, درخت_مقصد_uhwi (alignment));
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

ساكن بنية c_عبارت
c_parser_gimple_postfix_عبارت (gimple_parser &parser, درخت ret_type)
{
  location_t loc = c_parser_peek_token (parser)->location;
  منبع_range tok_range = c_parser_peek_token (parser)->get_range ();
  بنية c_عبارت عبارت;
  عبارت.مجموعه_error ();
  بدل (c_parser_peek_token (parser)->type)
    {
    حالة CPP_عدد:
      عبارت.مقدار = c_parser_peek_token (parser)->مقدار;
      مجموعه_c_عبارت_منبع_range (&عبارت, tok_range);
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      اكسر;
    حالة CPP_CHAR:
    حالة CPP_CHAR16:
    حالة CPP_CHAR32:
    حالة CPP_UTF8CHAR:
    حالة CPP_WCHAR:
      عبارت.مقدار = c_parser_peek_token (parser)->مقدار;
      مجموعه_c_عبارت_منبع_range (&عبارت, tok_range);
      c_parser_consume_token (parser);
      اكسر;
    حالة CPP_STRING:
    حالة CPP_STRING16:
    حالة CPP_STRING32:
    حالة CPP_WSTRING:
    حالة CPP_UTF8STRING:
      عبارت = c_parser_string_literal (parser, خطأ, درست);
      اكسر;
    حالة CPP_DOT:
      عبارت = c_parser_gimple_call_داخلی (parser);
      اكسر;
    حالة CPP_NAME:
      إذا (c_parser_peek_token (parser)->id_نوع == C_ID_ID)
	{
	  درخت id = c_parser_peek_token (parser)->مقدار;
	  إذا (strcmp (IDENTIFIER_اشاره_گر (id), "__MEM") == 0)
	    {
	      /* __MEM '<' type-name [ ',' number ] '>'
	               '(' [ '(' type-name ')' ] unary-expression
			   [ '+' number ]
			   [ ',' number ]
			   [ ',' number ':' number ] ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      درخت type = c_parser_gimple_typespec (parser);
	      بنية c_عبارت ptr, alias_off, گام, شاخص, index2;
	      ptr.مقدار = error_mark_گره;
	      alias_off.مقدار = NULL_درخت;
	      گام.مقدار = NULL_درخت;
	      شاخص.مقدار = NULL_درخت;
	      index2.مقدار = NULL_درخت;
	      بیعلامت کوتاه clique = 0;
	      بیعلامت کوتاه پایه = 0;
	      منطقي معکوس_ترتیب = خطأ;
	      بنية c_عبارت ro;
	      إذا (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  درخت alias_type = NULL_درخت;
		  /* Optional alias-type cast.  */
		  إذا (c_parser_بعدی_token_is (parser, CPP_OPEN_PAREN))
		    {
		      c_parser_consume_token (parser);
		      بنية c_type_name *alias_type_name
			= c_parser_type_name (parser);
		      c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN,
						 "expected %<)%>");
		      إذا (alias_type_name)
			{
			  درخت tem;
			  alias_type = groktypename (alias_type_name,
						     &tem, عدم);
			}
		    }
		  ptr = c_parser_gimple_unary_عبارت (parser);
		  إذا (ptr.مقدار == error_mark_گره
		      || ! اشاره_گر_TYPE_P (درخت_TYPE (ptr.مقدار)))
		    {
		      إذا (ptr.مقدار != error_mark_گره)
			error_at (ptr.get_شروع (),
				  "invalid type of %<__MEM%> operand");
		      c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN,
						 "expected %<)%>");
		      أرجع عبارت;
		    }
		  إذا (! alias_type)
		    alias_type = درخت_TYPE (ptr.مقدار);
		  /* Optional constant offset.  */
		  إذا (c_parser_بعدی_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      alias_off = c_parser_gimple_postfix_عبارت (parser);
		    }
		  إذا (c_parser_بعدی_token_is (parser, CPP_MULT))
		    {
		      std::جابجا (شاخص, alias_off);
		      c_parser_consume_token (parser);
		      گام = c_parser_gimple_postfix_عبارت (parser);
		    }
		  وإلا إذا (c_parser_بعدی_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      شاخص = c_parser_gimple_postfix_عبارت (parser);
		      إذا (c_parser_بعدی_token_is (parser, CPP_MULT))
			{
			  c_parser_consume_token (parser);
			  گام = c_parser_gimple_postfix_عبارت (parser);
			}
		      وإلا
			std::جابجا (شاخص, index2);
		    }
		  وإلا إذا (alias_off.مقدار
			   && درخت_کد (alias_off.مقدار) != INTEGER_CST)
		    std::جابجا (alias_off, index2);
		  إذا (c_parser_بعدی_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      index2 = c_parser_gimple_postfix_عبارت (parser);
		    }
		  إذا (alias_off.مقدار)
		    {
		      إذا (درخت_کد (alias_off.مقدار) != INTEGER_CST)
			error_at (alias_off.get_شروع (),
				  "expected constant offset for %<__MEM%> "
				  "operand");
		      alias_off.مقدار = fold_convert (alias_type,
						      alias_off.مقدار);
		    }
		  وإلا
		    alias_off.مقدار = build_int_cst (alias_type, 0);
		  إذا (گام.مقدار)
		    {
		      إذا (درخت_کد (گام.مقدار) != INTEGER_CST)
			error_at (گام.get_شروع (),
				  "expected constant step for %<__MEM%> "
				  "operand");
		    }
		  إذا (c_parser_بعدی_token_is (parser, CPP_COMMA))
		    {
		      بنية c_عبارت cl, ba;
		      منطقي has_clb = درست;
		      c_parser_consume_token (parser);
		      cl = c_parser_gimple_postfix_عبارت (parser);
		      إذا (!c_parser_بعدی_token_is (parser, CPP_COLON))
			{
			  ro = cl;
			  بیعلامت HOST_WIDE_INT tmp = 0;
			  إذا (!درخت_میگنجد_uhwi_p (ro.مقدار)
			      || (tmp = درخت_مقصد_uhwi (ro.مقدار)) > 1)
			    error_at (ro.get_شروع (),
				      "invalid reverse order value");
			  معکوس_ترتیب = tmp;
			  has_clb = خطأ;
			  إذا (c_parser_بعدی_token_is (parser, CPP_COMMA))
			    {
			      c_parser_consume_token (parser);
			      cl = c_parser_gimple_postfix_عبارت (parser);
		              has_clb = درست;
			    }
			}
		      إذا (has_clb
			  && c_parser_require (parser,
					       CPP_COLON, "expected %<:%>"))
			{
			  ba = c_parser_gimple_postfix_عبارت (parser);
			  إذا (!درخت_میگنجد_uhwi_p (cl.مقدار)
			      || !درخت_میگنجد_uhwi_p (ba.مقدار)
			      || compare_درخت_int (cl.مقدار,
						   (clique = درخت_مقصد_uhwi
								(cl.مقدار)))
			      || compare_درخت_int (ba.مقدار,
						   (پایه = درخت_مقصد_uhwi
								 (ba.مقدار))))
			    error_at (cl.get_شروع (),
				      "invalid clique/base pair");
			}
		    }
		  c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      إذا (! type || c_parser_error (parser))
		{
		  c_parser_مجموعه_error (parser, خطأ);
		  أرجع عبارت;
		}
	      إذا (شاخص.مقدار || گام.مقدار || index2.مقدار)
		عبارت.مقدار = build5_loc (loc, هدف_MEM_REF,
					 type, ptr.مقدار, alias_off.مقدار,
					 شاخص.مقدار, گام.مقدار, index2.مقدار);
	      وإلا
		عبارت.مقدار = build2_loc (loc, MEM_REF,
					 type, ptr.مقدار, alias_off.مقدار);
	      إذا (clique != 0)
		{
		  cfun->آخرین_clique = MAX (cfun->آخرین_clique, clique);
		  MR_DEPENDENCE_CLIQUE (عبارت.مقدار) = clique;
		  MR_DEPENDENCE_پایه (عبارت.مقدار) = پایه;
		}
	      إذا (معکوس_ترتیب)
		{
		  إذا (درخت_کد (عبارت.مقدار) == MEM_REF)
		    REF_معکوس_STORAGE_ترتیب (عبارت.مقدار) = معکوس_ترتیب;
		  وإلا
		    error_at (ro.get_شروع (),
			      "target mem ref cannot have reverse order");
		}
	      اكسر;
	    }
	  وإلا إذا (strcmp (IDENTIFIER_اشاره_گر (id), "__VIEW_CONVERT") == 0)
	    {
	      /* __VIEW_CONVERT '<' type-name [ ',' number ] '>'
	                        '(' postfix-expression ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      درخت type = c_parser_gimple_typespec (parser);
	      إذا (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_عبارت op = c_parser_gimple_postfix_عبارت (parser);
		  c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  إذا (type && op.مقدار != error_mark_گره)
		    عبارت.مقدار = build1_loc (loc, VIEW_CONVERT_عبارت,
					     type, op.مقدار);
		}
	      اكسر;
	    }
	  وإلا إذا (strcmp (IDENTIFIER_اشاره_گر (id), "__BIT_FIELD_REF") == 0)
	    {
	      /* __BIT_FIELD_REF '<' type-name [ ',' number ] '>'
	                        '(' postfix-expression, integer, integer ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      درخت type = c_parser_gimple_typespec (parser);
	      إذا (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_عبارت op0 = c_parser_gimple_postfix_عبارت (parser);
		  c_parser_skip_until_یافت (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_عبارت op1 = c_parser_gimple_postfix_عبارت (parser);
		  إذا (درخت_کد (op1.مقدار) != INTEGER_CST
		      || !int_میگنجد_type_p (op1.مقدار, bitsizetype))
		    c_parser_error (parser, "expected constant size");
		  c_parser_skip_until_یافت (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_عبارت op2 = c_parser_gimple_postfix_عبارت (parser);
		  إذا (درخت_کد (op2.مقدار) != INTEGER_CST
		      || !int_میگنجد_type_p (op2.مقدار, bitsizetype))
		    c_parser_error (parser, "expected constant offset");
		  c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  إذا (type
		      && op0.مقدار != error_mark_گره
		      && درخت_کد (op1.مقدار) == INTEGER_CST
		      && درخت_کد (op2.مقدار) == INTEGER_CST)
		    عبارت.مقدار = build3_loc (loc, بیت_فیلد_REF, type,
					     op0.مقدار,
					     fold_convert (bitsizetype,
							   op1.مقدار),
					     fold_convert (bitsizetype,
							   op2.مقدار));
		}
	      اكسر;
	    }
	  وإلا إذا (strcmp (IDENTIFIER_اشاره_گر (id), "__CLOBBER") == 0)
	    {
	      /* __CLOBBER [ '(' bob | eob | bos | eos ')' ]  */
	      clobber_نوع نوع = CLOBBER_UNDEF;
	      c_parser_consume_token (parser);
	      إذا (c_parser_بعدی_token_is (parser, CPP_OPEN_PAREN))
		{
		  c_parser_consume_token (parser);
		  خودکار tok = c_parser_peek_token (parser);
		  إذا (c_parser_require (parser, CPP_NAME,
					"expected clobber kind"))
		    {
		      ثابت حرف *نوع_str = IDENTIFIER_اشاره_گر (tok->مقدار);
		      إذا (strcmp (نوع_str, "bos") == 0)
			نوع = CLOBBER_STORAGE_BEGIN;
		      وإلا إذا (strcmp (نوع_str, "bob") == 0)
			نوع = CLOBBER_OBJECT_BEGIN;
		      وإلا إذا (strcmp (نوع_str, "eob") == 0)
			نوع = CLOBBER_OBJECT_انتها;
		      وإلا إذا (strcmp (نوع_str, "eos") == 0)
			نوع = CLOBBER_STORAGE_انتها;
		      وإلا
			c_parser_error (parser, "expected one of %<bos%>, "
					"%<eos%>, %<bob>, %<eob%>");
		    }
		  c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      /* We infer the (redundant) type from the LHS.  */
	      عبارت.مقدار = build_clobber (ret_type, نوع);
	      اكسر;
	    }
	  وإلا إذا (strcmp (IDENTIFIER_اشاره_گر (id), "_Literal") == 0)
	    {
	      /* _Literal '(' type-name ')' ( [ '-' ] constant | constructor ) */
	      c_parser_consume_token (parser);
	      درخت type = NULL_درخت;
	      إذا (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  بنية c_type_name *type_name = c_parser_type_name (parser);
		  درخت tem;
		  إذا (type_name)
		    type = groktypename (type_name, &tem, عدم);
		  c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      إذا (! type)
		{
		  c_parser_error (parser, "invalid _Literal");
		  أرجع عبارت;
		}
	      إذا (c_parser_بعدی_token_is (parser, CPP_OPEN_BRACE))
		{
		  c_parser_consume_token (parser);
		  إذا (!AGGREGATE_TYPE_P (type)
		      && !وکتور_TYPE_P (type))
		    {
		      c_parser_error (parser, "invalid type for _Literal with "
				      "constructor");
		      c_parser_skip_until_یافت (parser, CPP_CLOSE_BRACE,
						 "expected %<}%>");
		      أرجع عبارت;
		    }
		  vec<constructor_elt, va_gc> *v = عدم;
		  منطقي constant_p = درست;
		  إذا (وکتور_TYPE_P (type)
		      && !c_parser_بعدی_token_is (parser, CPP_CLOSE_BRACE))
		    {
		      vec_alloc (v, TYPE_وکتور_SUBPARTS (type).مقصد_constant ());
		      افعل
			{
			  درخت val
			    = c_parser_gimple_postfix_عبارت (parser).مقدار;
			  إذا (! val
			      || val == error_mark_گره
			      || (! CONSTANT_CLASS_P (val)
				  && ! SSA_VAR_P (val)))
			    {
			      c_parser_error (parser, "invalid _Literal");
			      أرجع عبارت;
			    }
			  CONSTRUCTOR_APPEND_ELT (v, NULL_درخت, val);
			  إذا (! CONSTANT_CLASS_P (val))
			    constant_p = خطأ;
			  إذا (c_parser_بعدی_token_is (parser, CPP_COMMA))
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
			عبارت.مقدار = build_وکتور_from_ctor (type, v);
		      وإلا
			عبارت.مقدار = build_constructor (type, v);
		    }
		  وإلا
		    {
		      c_parser_skip_until_یافت (parser, CPP_CLOSE_BRACE,
						 "expected %<}%>");
		      أرجع عبارت;
		    }
		}
	      وإلا
		{
		  منطقي neg_p, addr_p;
		  إذا ((neg_p = c_parser_بعدی_token_is (parser, CPP_MINUS)))
		    c_parser_consume_token (parser);
		  إذا ((addr_p = c_parser_بعدی_token_is (parser, CPP_AND)))
		    c_parser_consume_token (parser);
		  درخت val = c_parser_gimple_postfix_عبارت (parser).مقدار;
		  إذا (! val
		      || val == error_mark_گره
		      || (!CONSTANT_CLASS_P (val) && !addr_p))
		    {
		      c_parser_error (parser, "invalid _Literal");
		      أرجع عبارت;
		    }
		  إذا (addr_p)
		    {
		      val = build1 (ADDR_عبارت, type, val);
		      إذا (!is_gimple_invariant_آدرس (val))
			{
			  c_parser_error (parser, "invalid _Literal");
			  أرجع عبارت;
			}
		    }
		  إذا (neg_p)
		    {
		      val = const_unop (NEGATE_عبارت, درخت_TYPE (val), val);
		      إذا (! val)
			{
			  c_parser_error (parser, "invalid _Literal");
			  أرجع عبارت;
			}
		    }
		  عبارت.مقدار = fold_convert (type, val);
		}
	      أرجع عبارت;
	    }

	  /* SSA name.  */
	  بیعلامت نسخه, ver_جابه_جایی;
	  إذا (! lookup_name (id)
	      && c_parser_parse_ssa_name_id (id, &نسخه, &ver_جابه_جایی))
	    {
	      c_parser_consume_token (parser);
	      عبارت.مقدار = c_parser_parse_ssa_name (parser, id, NULL_درخت,
						    نسخه, ver_جابه_جایی);
	      إذا (عبارت.مقدار == error_mark_گره)
		أرجع عبارت;
	      مجموعه_c_عبارت_منبع_range (&عبارت, tok_range);
	      /* For default definition SSA names.  */
	      إذا (c_parser_بعدی_token_is (parser, CPP_OPEN_PAREN)
		  && c_parser_peek_2nd_token (parser)->type == CPP_NAME
		  && strcmp ("D",
			     IDENTIFIER_اشاره_گر
			       (c_parser_peek_2nd_token (parser)->مقدار)) == 0
		  && c_parser_peek_nth_token (parser, 3)->type == CPP_CLOSE_PAREN)
		{
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		  إذا (! SSA_NAME_IS_DEFAULT_DEF (عبارت.مقدار))
		    {
		      إذا (!SSA_NAME_VAR (عبارت.مقدار))
			{
			  error_at (loc, "anonymous SSA name cannot have"
				    " default definition");
			  عبارت.مقدار = error_mark_گره;
			  أرجع عبارت;
			}
		      مجموعه_ssa_default_def (cfun, SSA_NAME_VAR (عبارت.مقدار),
					   عبارت.مقدار);
		      SSA_NAME_DEF_STMT (عبارت.مقدار) = gimple_build_nop ();
		    }
		}
	    }
	  وإلا
	    {
	      c_parser_consume_token (parser);
	      عبارت.مقدار
		= build_external_ref (loc, id,
				      (c_parser_peek_token (parser)->type
				       == CPP_OPEN_PAREN), &عبارت.original_type);
	      مجموعه_c_عبارت_منبع_range (&عبارت, tok_range);
	    }
	  اكسر;
	}
      /* Fallthru.  */
    افتراضي:
      c_parser_error (parser, "expected expression");
      عبارت.مجموعه_error ();
      اكسر;
    }
  إذا (عبارت.مقدار == error_mark_گره)
    أرجع عبارت;
  أرجع c_parser_gimple_postfix_عبارت_after_primary
    (parser, عبارت_LOC_OR_LOC (عبارت.مقدار, loc), عبارت);
}

/* Parse a gimple postfix expression after the initial primary or compound
   literal.  */

ساكن بنية c_عبارت
c_parser_gimple_postfix_عبارت_after_primary (gimple_parser &parser,
						  location_t عبارت_loc,
						  بنية c_عبارت عبارت)
{
  location_t شروع;
  location_t پایان;
  درخت ident;
  location_t comp_loc;

  طالما (درست)
    {
      location_t op_loc = c_parser_peek_token (parser)->location;
      بدل (c_parser_peek_token (parser)->type)
	{
	حالة CPP_OPEN_مربع:
	  {
	    c_parser_consume_token (parser);
	    درخت idx = c_parser_gimple_unary_عبارت (parser).مقدار;

	    إذا (! c_parser_require (parser, CPP_CLOSE_مربع, "expected %<]%>"))
	      {
		c_parser_skip_until_یافت (parser, CPP_CLOSE_مربع, عدم);
		اكسر;
	      }

	    شروع = عبارت.get_شروع ();
	    پایان = c_parser_نشانهها_buf (parser, 0)->location;
	    عبارت.مقدار = build_array_ref (op_loc, عبارت.مقدار, idx);
	    مجموعه_c_عبارت_منبع_range (&عبارت, شروع, پایان);
	    عبارت.m_decimal = 0;

	    عبارت.original_کد = ERROR_MARK;
	    عبارت.original_type = عدم;
	    اكسر;
	  }
	حالة CPP_OPEN_PAREN:
	  {
	    /* Function call.  */
	    c_parser_consume_token (parser);
	    auto_vec<درخت> exprlist;
	    إذا (! c_parser_بعدی_token_is (parser, CPP_CLOSE_PAREN))
	      c_parser_gimple_عبارت_list (parser, &exprlist);
	    c_parser_skip_until_یافت (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    إذا (!FUNC_OR_روش_TYPE_P (درخت_TYPE (عبارت.مقدار)))
	      {
		c_parser_error (parser, "invalid call to non-function");
		عبارت.مجموعه_error ();
		اكسر;
	      }
	    عبارت.مقدار = build_call_array_loc
		(عبارت_loc, درخت_TYPE (درخت_TYPE (عبارت.مقدار)),
		 عبارت.مقدار, exprlist.درازی (), exprlist.آدرس ());
	    عبارت.m_decimal = 0;
	    عبارت.original_کد = ERROR_MARK;
	    عبارت.original_type = عدم;
	    اكسر;
	  }
	حالة CPP_DOT:
	  {
	    /* Structure element reference.  */
	    c_parser_consume_token (parser);
	    إذا (c_parser_بعدی_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		ident = comp_tok->مقدار;
		comp_loc = comp_tok->location;
	      }
	    وإلا
	      {
		c_parser_error (parser, "expected identifier");
		عبارت.مجموعه_error ();
		عبارت.original_کد = ERROR_MARK;
		عبارت.original_type = عدم;
		أرجع عبارت;
	      }
	    شروع = عبارت.get_شروع ();
	    پایان = c_parser_peek_token (parser)->get_پایان ();
	    c_parser_consume_token (parser);
	    عبارت.مقدار = build_component_ref (op_loc, عبارت.مقدار, ident,
					      comp_loc, UNKNOWN_LOCATION);
	    مجموعه_c_عبارت_منبع_range (&عبارت, شروع, پایان);
	    عبارت.m_decimal = 0;
	    عبارت.original_کد = ERROR_MARK;
	    إذا (درخت_کد (عبارت.مقدار) != COMPONENT_REF)
	      عبارت.original_type = عدم;
	    وإلا
	      {
		/* Remember the original type of a bitfield.  */
		درخت فیلد_2 = درخت_عملوند (عبارت.مقدار, 1);
		إذا (درخت_کد (فیلد_2) != فیلد_DECL)
		  عبارت.original_type = عدم;
		وإلا
		  عبارت.original_type = DECL_بیت_فیلد_TYPE (فیلد_2);
	      }
	    اكسر;
	  }
	حالة CPP_DEREF:
	  {
	    /* Structure element reference.  */
	    إذا (!اشاره_گر_TYPE_P (درخت_TYPE (عبارت.مقدار)))
	      {
		c_parser_error (parser, "dereference of non-pointer");
		عبارت.مجموعه_error ();
		عبارت.original_کد = ERROR_MARK;
		عبارت.original_type = عدم;
		أرجع عبارت;
	      }
	    c_parser_consume_token (parser);
	    إذا (c_parser_بعدی_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		ident = comp_tok->مقدار;
		comp_loc = comp_tok->location;
	      }
	    وإلا
	      {
		c_parser_error (parser, "expected identifier");
		عبارت.مجموعه_error ();
		عبارت.original_کد = ERROR_MARK;
		عبارت.original_type = عدم;
		أرجع عبارت;
	      }
	    شروع = عبارت.get_شروع ();
	    پایان = c_parser_peek_token (parser)->get_پایان ();
	    c_parser_consume_token (parser);
	    عبارت.مقدار = build_component_ref (op_loc,
					      build_simple_mem_ref_loc
					        (op_loc, عبارت.مقدار),
					      ident, comp_loc,
					      عبارت.get_location ());
	    مجموعه_c_عبارت_منبع_range (&عبارت, شروع, پایان);
	    عبارت.m_decimal = 0;
	    عبارت.original_کد = ERROR_MARK;
	    إذا (درخت_کد (عبارت.مقدار) != COMPONENT_REF)
	      عبارت.original_type = عدم;
	    وإلا
	      {
		/* Remember the original type of a bitfield.  */
		درخت فیلد_2 = درخت_عملوند (عبارت.مقدار, 1);
		إذا (درخت_کد (فیلد_2) != فیلد_DECL)
		  عبارت.original_type = عدم;
		وإلا
		  عبارت.original_type = DECL_بیت_فیلد_TYPE (فیلد_2);
	      }
	    اكسر;
	  }
	افتراضي:
	  أرجع عبارت;
	}
    }
}

/* Parse expression list.

   gimple-expr-list:
     gimple-unary-expression
     gimple-expr-list , gimple-unary-expression

 */

ساكن فراغ
c_parser_gimple_عبارت_list (gimple_parser &parser, vec<درخت> *ret)
{
  بنية c_عبارت عبارت;

  عبارت = c_parser_gimple_unary_عبارت (parser);
  ret->امن_افزودن (عبارت.مقدار);
  طالما (c_parser_بعدی_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      عبارت = c_parser_gimple_unary_عبارت (parser);
      ret->امن_افزودن (عبارت.مقدار);
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
  درخت name = c_parser_peek_token (parser)->مقدار;
  location_t loc1 = c_parser_peek_token (parser)->location;
  gcc_assert (c_parser_بعدی_token_is (parser, CPP_NAME));
  c_parser_consume_token (parser);
  gcc_assert (c_parser_بعدی_token_is (parser, CPP_COLON));
  c_parser_consume_token (parser);
  درخت label = define_label (loc1, name);
  إذا (label)
    gimple_seq_جمع_کن_stmt_without_update (seq, gimple_build_label (label));
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
  إذا (c_parser_بعدی_token_is_not (parser, CPP_OPEN_PAREN))
    أرجع;
  c_parser_consume_token (parser);

  specs->مدخل_bb_شمار = profile_شمار::uninitialized ();
  طالما (c_parser_بعدی_token_is (parser, CPP_NAME))
    {
      profile_quality quality;
      ثابت حرف *op = IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار);
      c_parser_consume_token (parser);
      إذا (! strcmp (op, "startwith"))
	{
	  إذا (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    أرجع;
	  إذا (c_parser_بعدی_token_is_not (parser, CPP_STRING))
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"expected pass name");
	      أرجع;
	    }
	  pass = xstrdup (درخت_STRING_اشاره_گر
			  (c_parser_string_literal (parser, خطأ,
						    خطأ).مقدار));
	  إذا (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<(%>"))
	    أرجع;
	}
      وإلا إذا (parse_profile_quality (op, &quality))
	{
	  درخت q;
	  إذا (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    أرجع;

	  إذا (!c_parser_بعدی_token_is (parser, CPP_عدد)
	      || (درخت_کد (q = c_parser_peek_token (parser)->مقدار)
		  != INTEGER_CST))
	    {
	      c_parser_error (parser, "expected count value");
	      أرجع;
	    }

	  specs->مدخل_bb_شمار
	    = profile_شمار::from_gcov_type (درخت_INT_CST_کم (q), quality);
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
     إذا (c_parser_بعدی_token_is (parser, CPP_COMMA))
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
ثبات

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
  c_parser_declspecs (parser, specs, درست, درست, درست,
		      درست, درست, درست, درست, cla_nonabstract_decl);
  پایان_declspecs (specs);

  /* Provide better error recovery.  Note that a type name here is usually
     better diagnosed as a redeclaration.  */
  إذا (c_parser_بعدی_token_starts_declspecs (parser)
      && ! c_parser_بعدی_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<;%>");
      c_parser_مجموعه_error (parser, خطأ);
      أرجع;
    }

  منطقي dummy = خطأ;
  declarator = c_parser_declarator (parser,
				    specs->typespec_نوع != ctsk_none,
				    C_DTR_نرمال, &dummy);

  إذا (!c_parser_بعدی_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_error (parser, "expected %<;%>");
      أرجع;
    }
  إذا (declarator)
    {
      /* Handle SSA name decls specially, they do not go into the identifier
         table but we simply build the SSA name for later lookup.  */
      بیعلامت نسخه, ver_جابه_جایی;
      /* Handle SSA pointer declarations in a very simplistic ways, we
	 probably would like to call grokdeclarator in a special mode to
	 just build the type of the decl - start_decl already pushes
	 the identifier to the bindings for lookup, something we do not
	 want.  */
      بنية c_declarator *id_declarator = declarator;
      طالما (id_declarator->نوع == cdk_اشاره_گر)
	id_declarator = id_declarator->declarator;
      إذا (id_declarator->نوع == cdk_id
	  && (declarator->نوع == cdk_اشاره_گر
	      || is_gimple_reg_type (specs->type))
	  && c_parser_parse_ssa_name_id (id_declarator->u.id.id,
					 &نسخه, &ver_جابه_جایی)
	  /* The following restricts it to unnamed anonymous SSA names
	     which fails parsing of named ones in dumps (we could
	     decide to not dump their name for -gimple).  */
	  && ver_جابه_جایی == 0)
	{
	  بنية c_declarator *p = declarator;
	  درخت type = specs->type;
	  طالما (p->نوع == cdk_اشاره_گر)
	    {
	      type = build_اشاره_گر_type (type);
	      p = p->declarator;
	    }
	  c_parser_parse_ssa_name (parser, id_declarator->u.id.id, type,
				   نسخه, ver_جابه_جایی);
	}
      وإلا
	{
	  درخت postfix_attrs = NULL_درخت;
	  درخت all_پیشوند_attrs = specs->attrs;
	  specs->attrs = عدم;
	  درخت decl = شروع_decl (declarator, specs, خطأ,
				  chainon (postfix_attrs, all_پیشوند_attrs));
	  إذا (decl)
	    پایان_decl (decl, UNKNOWN_LOCATION, NULL_درخت, NULL_درخت,
			 NULL_درخت);
	}
    }
}

/* Parse gimple goto statement.  */

ساكن فراغ
c_parser_gimple_goto_stmt (gimple_parser &parser,
			   location_t loc, درخت label, gimple_seq *seq)
{
  إذا (cfun->curr_properties & PROP_cfg)
    {
      صحيح dest_شاخص;
      profile_probability prob;
      إذا (c_parser_gimple_parse_bb_spec_یال_probability (label, parser,
							  &dest_شاخص, &prob))
	{
	  parser.افزودن_یال (parser.current_bb->شاخص, dest_شاخص,
			    یال_FALLTHRU, prob);
	  أرجع;
	}
    }
  درخت decl = lookup_label_for_goto (loc, label);
  gimple_seq_جمع_کن_stmt_without_update (seq, gimple_build_goto (decl));
}

/* Parse a parenthesized condition.
   gimple-condition:
     ( gimple-binary-expression )    */

ساكن درخت
c_parser_gimple_paren_condition (gimple_parser &parser)
{
  إذا (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    أرجع error_mark_گره;
  درخت cond
    = c_parser_gimple_دودویی_عبارت (parser, boolean_type_گره).مقدار;
  إذا (cond != error_mark_گره
      && ! COMPARISON_CLASS_P (cond)
      && ! CONSTANT_CLASS_P (cond)
      && ! SSA_VAR_P (cond))
    {
      c_parser_error (parser, "comparison required");
      cond = error_mark_گره;
    }
  إذا (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    أرجع error_mark_گره;
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

  إذا ((c_parser_بعدی_token_is (parser, CPP_KEYWORD)
       && c_parser_peek_token (parser)->keyword == RID_AT_FINALLY)
      || (c_parser_بعدی_token_is (parser, CPP_NAME)
	  && c_parser_peek_token (parser)->id_نوع == C_ID_ID
	  && strcmp (IDENTIFIER_اشاره_گر (c_parser_peek_token (parser)->مقدار),
		     "finally") == 0))
    {
      gimple_seq finseq = عدم;
      c_parser_consume_token (parser);
      c_parser_gimple_compound_statement (parser, &finseq);

      إذا (c_parser_بعدی_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_ELSE)
	{
	  gimple_seq elsseq = عدم;
	  c_parser_consume_token (parser);
	  c_parser_gimple_compound_statement (parser, &elsseq);

	  geh_else *stmt = gimple_build_eh_else (finseq, elsseq);
	  finseq = عدم;
	  gimple_seq_جمع_کن_stmt_without_update (&finseq, stmt);
	}

      gtry *stmt = gimple_build_try (tryseq, finseq, GIMPLE_TRY_FINALLY);
      gimple_seq_جمع_کن_stmt_without_update (seq, stmt);
    }
  وإلا إذا (c_parser_بعدی_token_is (parser, CPP_KEYWORD)
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
  درخت t_label = NULL_درخت, f_label = NULL_درخت, label;
  location_t loc;
  c_parser_consume_token (parser);
  درخت cond = c_parser_gimple_paren_condition (parser);

  إذا (c_parser_بعدی_token_is_keyword (parser, RID_GOTO))
    {
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      إذا (! c_parser_بعدی_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected label");
	  أرجع;
	}
      label = c_parser_peek_token (parser)->مقدار;
      c_parser_consume_token (parser);
      صحيح dest_شاخص;
      profile_probability prob;
      إذا ((cfun->curr_properties & PROP_cfg)
	  && c_parser_gimple_parse_bb_spec_یال_probability (label, parser,
							     &dest_شاخص, &prob))
	parser.افزودن_یال (parser.current_bb->شاخص, dest_شاخص,
			  یال_TRUE_مقدار, prob);
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

  إذا (c_parser_بعدی_token_is_keyword (parser, RID_ELSE))
    c_parser_consume_token (parser);
  وإلا
    {
      c_parser_error (parser, "expected else statement");
      أرجع;
    }

  إذا (c_parser_بعدی_token_is_keyword (parser, RID_GOTO))
    {
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      إذا (! c_parser_بعدی_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected label");
	  أرجع;
	}
      label = c_parser_peek_token (parser)->مقدار;
      c_parser_consume_token (parser);
      صحيح dest_شاخص;
      profile_probability prob;
      إذا ((cfun->curr_properties & PROP_cfg)
	  && c_parser_gimple_parse_bb_spec_یال_probability (label, parser,
							     &dest_شاخص, &prob))
	parser.افزودن_یال (parser.current_bb->شاخص, dest_شاخص,
			  یال_FALSE_مقدار, prob);
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

  إذا (cond != error_mark_گره)
    gimple_seq_جمع_کن_stmt_without_update (seq, gimple_build_cond_from_درخت (cond, t_label,
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
  c_عبارت cond_عبارت;
  درخت case_label, label;
  auto_vec<درخت> labels;
  درخت default_label = NULL_درخت;
  c_parser_consume_token (parser);

  إذا (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    أرجع;
  cond_عبارت = c_parser_gimple_postfix_عبارت (parser);
  إذا (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    أرجع;

  إذا (! c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    أرجع;

  طالما (c_parser_بعدی_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      إذا (c_parser_بعدی_token_is (parser, CPP_EOF))
	{
	  c_parser_error (parser, "expected statement");
	  أرجع;
	}

      بدل (c_parser_peek_token (parser)->keyword)
	{
	حالة RID_CASE:
	  {
	    c_عبارت exp1;
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);

	    إذا (c_parser_بعدی_token_is (parser, CPP_NAME)
		|| c_parser_peek_token (parser)->type == CPP_عدد)
	      exp1 = c_parser_gimple_postfix_عبارت (parser);
	    وإلا
	      {
		c_parser_error (parser, "expected expression");
		أرجع;
	      }

	    إذا (c_parser_بعدی_token_is (parser, CPP_COLON))
	      {
		c_parser_consume_token (parser);
		إذا (c_parser_بعدی_token_is (parser, CPP_NAME))
		  {
		    label = c_parser_peek_token (parser)->مقدار;
		    c_parser_consume_token (parser);
		    درخت decl = lookup_label_for_goto (loc, label);
		    case_label = build_case_label (exp1.مقدار, NULL_درخت,
						   decl);
		    labels.امن_افزودن (case_label);
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
	    إذا (c_parser_بعدی_token_is (parser, CPP_COLON))
	      {
		c_parser_consume_token (parser);
		إذا (c_parser_بعدی_token_is (parser, CPP_NAME))
		  {
		    label = c_parser_peek_token (parser)->مقدار;
		    c_parser_consume_token (parser);
		    درخت decl = lookup_label_for_goto (loc, label);
		    default_label = build_case_label (NULL_درخت, NULL_درخت,
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

  إذا (cond_عبارت.مقدار != error_mark_گره)
    {
      gswitch *s = gimple_build_switch (cond_عبارت.مقدار, default_label, labels);
      gimple_seq_جمع_کن_stmt_without_update (seq, s);
    }
}

/* Parse gimple return statement.  */

ساكن فراغ
c_parser_gimple_return_stmt (gimple_parser &parser, gimple_seq *seq)
{
  location_t loc = c_parser_peek_token (parser)->location;
  gimple *ret = عدم;
  c_parser_consume_token (parser);
  إذا (c_parser_بعدی_token_is (parser, CPP_SEMICOLON))
    {
      c_پایان_gimple_return (loc, NULL_درخت);
      ret = gimple_build_return (عدم);
      gimple_seq_جمع_کن_stmt_without_update (seq, ret);
    }
  وإلا
    {
      location_t xloc = c_parser_peek_token (parser)->location;
      c_عبارت عبارت = c_parser_gimple_unary_عبارت (parser);
      إذا (عبارت.مقدار != error_mark_گره)
	{
	  c_پایان_gimple_return (xloc, عبارت.مقدار);
	  ret = gimple_build_return (عبارت.مقدار);
	  gimple_seq_جمع_کن_stmt_without_update (seq, ret);
	}
    }
}

/* Support function for c_parser_gimple_return_stmt.  */

ساكن فراغ
c_پایان_gimple_return (location_t loc, درخت retval)
{
  درخت valtype = درخت_TYPE (درخت_TYPE (current_function_decl));

  /* Use the expansion point to handle cases such as returning NULL
     in a function returning void.  */
  location_t xloc = expansion_نقطه_location_if_درون_system_سرآیند (loc);

  إذا (درخت_THIS_VOLATILE (current_function_decl))
    warning_at (xloc, 0,
		"function declared %<noreturn%> has a %<return%> statement");

  إذا (! retval)
    current_function_returns_null = 1;
  وإلا إذا (valtype == 0 || VOID_TYPE_P (valtype))
    {
      current_function_returns_null = 1;
      إذا (درخت_کد (درخت_TYPE (retval)) != VOID_TYPE)
	{
	  error_at
	    (xloc, "%<return%> with a value, in function returning void");
	  inform (DECL_منبع_LOCATION (current_function_decl),
		  "declared here");
	}
    }
  وإلا إذا (درخت_کد (valtype) != درخت_کد (درخت_TYPE (retval)))
    {
      error_at
	(xloc, "invalid conversion in return statement");
      inform (DECL_منبع_LOCATION (current_function_decl),
	      "declared here");
    }
  أرجع;
}
