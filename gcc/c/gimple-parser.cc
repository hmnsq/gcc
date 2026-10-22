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
  gimple_parser (c_parser *p) : parser (p), کنارے(), current_bb(عدم) {}
  /* c_parser is not visible here, use composition and fake inheritance
     via a conversion operator.  */
  عامل c_parser *() { أرجع parser; }
  c_parser *parser;

  /* CFG build state.  */
  صنف gimple_parser_کنارا
  {
  عام:
    صحيح src;
    صحيح dest;
    صحيح flags;
    profile_probability probability;
  };
  auto_vec<gimple_parser_کنارا> کنارے;
  basic_بلاک current_bb;

  فراغ ڈالو_کنارا (صحيح, صحيح, صحيح, profile_probability);
};

فراغ
gimple_parser::ڈالو_کنارا (صحيح src, صحيح dest, صحيح flags,
			  profile_probability prob)
{
  gimple_parser_کنارا e;
  e.src = src;
  e.dest = dest;
  e.flags = flags;
  e.probability = prob;
  کنارے.محفوظ_ڈالو (e);
}


/* Gimple parsing functions.  */
ساكن منطقي c_parser_gimple_compound_statement (gimple_parser &, gimple_seq *);
ساكن فراغ c_parser_gimple_label (gimple_parser &, gimple_seq *);
ساكن فراغ c_parser_gimple_statement (gimple_parser &, gimple_seq *);
ساكن بنية c_اظہاریہ c_parser_gimple_ثنائی_عبارت (gimple_parser &, درخت);
ساكن بنية c_اظہاریہ c_parser_gimple_unary_عبارت (gimple_parser &);
ساكن بنية c_اظہاریہ c_parser_gimple_postfix_عبارت
			(gimple_parser &, درخت = error_mark_گرہ);
ساكن بنية c_اظہاریہ c_parser_gimple_postfix_عبارت_after_primary
			(gimple_parser &, location_t, بنية c_اظہاریہ);
ساكن فراغ c_parser_gimple_declaration (gimple_parser &);
ساكن فراغ c_parser_gimple_goto_stmt (gimple_parser &, location_t,
				       درخت, gimple_seq *);
ساكن فراغ c_parser_gimple_try_stmt (gimple_parser &, gimple_seq *);
ساكن فراغ c_parser_gimple_if_stmt (gimple_parser &, gimple_seq *);
ساكن فراغ c_parser_gimple_switch_stmt (gimple_parser &, gimple_seq *);
ساكن فراغ c_parser_gimple_return_stmt (gimple_parser &, gimple_seq *);
ساكن فراغ c_انت_gimple_return (location_t, درخت);
ساكن درخت c_parser_gimple_paren_condition (gimple_parser &);
ساكن فراغ c_parser_gimple_اظہاریہ_list (gimple_parser &, vec<درخت> *);


/* Much like parser_build_unary_op, but avoid applying default conversions.  */

ساكن c_اظہاریہ
gimple_parser_build_unary_op (location_t loc,
			      تعداد درخت_کوڈ_2 کوڈ, بنية c_اظہاریہ arg)
{
  بنية c_اظہاریہ نتیجہ;

  نتیجہ.original_کوڈ = کوڈ;
  نتیجہ.original_type = عدم;
  نتیجہ.m_decimal = 0;

  إذا (reject_gcc_builtin (arg.قدر))
    {
      نتیجہ.قدر = error_mark_گرہ;
    }
  وإلا
    {
      نتیجہ.قدر = build_unary_op (loc, کوڈ, arg.قدر, سچ);

      إذا (درخت_حد_توں_ودھ_P (نتیجہ.قدر) && !درخت_حد_توں_ودھ_P (arg.قدر))
	حد_توں_ودھ_warning (loc, نتیجہ.قدر, arg.قدر);
    }

  /* We are typically called when parsing a prefix token at LOC acting on
     ARG.  Reflect this by updating the source range of the result to
     start at LOC and end at the end of ARG.  */
  سیٹ_c_اظہاریہ_سروت_range (&نتیجہ,
			   loc, arg.get_انت ());

  أرجع نتیجہ;
}

/* See if VAL is an identifier matching __BB<num> and return <num>
   in *INDEX.  */

ساكن منطقي
c_parser_gimple_parse_bb_spec (درخت val, صحيح *اشاریہ)
{
  إذا (!startswith (IDENTIFIER_اشارہ_گر (val), "__BB"))
    أرجع خطأ;

  ثابت حرف *bb = IDENTIFIER_اشارہ_گر (val) + 4;
  إذا (! ISDIGIT (*bb))
    أرجع خطأ;

  حرف *pend;
  errno = 0;
  ثابت بنانشانی لما نمبر = strtoul (bb, &pend, 10);
  إذا (errno == ERANGE
      || *pend != '\0'
      || نمبر > ودھ_توں_ودھ_عدد)
    أرجع خطأ;

  *اشاریہ = نمبر;
  أرجع سچ;
}

/* See if VAL is an identifier matching __BB<num> and return <num>
   in *INDEX.  Return true if so and parse also FREQUENCY of
   the edge.  */


ساكن منطقي
c_parser_gimple_parse_bb_spec_کنارا_probability (درخت val,
						gimple_parser &parser,
						صحيح *اشاریہ,
						profile_probability
						*probability)
{
  منطقي return_p = c_parser_gimple_parse_bb_spec (val, اشاریہ);
  إذا (return_p)
    {
      *probability = profile_probability::uninitialized ();
      /* Parse frequency if provided.  */
      إذا (c_parser_اگلا_token_is (parser, CPP_OPEN_PAREN))
	{
	  درخت f;
	  c_parser_consume_token (parser);
	  إذا (!c_parser_اگلا_token_is (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected frequency quality");
	      أرجع خطأ;
	    }

	  profile_quality quality;
	  ثابت حرف *v
	    = IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر);
	  إذا (!parse_profile_quality (v, &quality))
	    {
	      c_parser_error (parser, "unknown profile quality");
	      أرجع خطأ;
	    }

	  c_parser_consume_token (parser);
	  إذا (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    أرجع خطأ;

	  إذا (!c_parser_اگلا_token_is (parser, CPP_نمبر)
	      || (درخت_کوڈ (f = c_parser_peek_token (parser)->قدر)
		  != INTEGER_CST))
	    {
	      c_parser_error (parser, "expected frequency value");
	      أرجع خطأ;
	    }

	  بنانشانی صحيح قدر = درخت_INT_CST_کم (f);
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
			    profile_گنتی اندراج_bb_گنتی)
{
  gimple_parser parser (cparser);
  gimple_seq seq = عدم;
  gimple_seq body = عدم;
  درخت stmt = ڈالو_stmt_list ();
  ڈالو_scope ();
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
      gimple_رجسٹر_cfg_hooks ();
      init_خالی_تھاواں_درخت_cfg ();
      parser.current_bb = اندراج_بلاک_PTR_FOR_FN (cfun);
      /* Initialize the bare loop structure - we are going to only
         mark headers and leave the rest to fixup.  */
      سیٹ_loops_for_fn (cfun, ggc_cleared_alloc<بنية loops> ());
      init_loops_structure (cfun, loops_for_fn (cfun), 1);
      loops_state_سیٹ (cfun, LOOPS_NEED_FIXUP|LOOPS_MAY_HAVE_مضرب_LATCHES);
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
      gimple_seq_جوڑو_stmt_without_update (&seq, ret);
    }

  درخت بلاک = نکالو_scope ();
  stmt = نکالو_stmt_list (stmt);
  stmt = c_build_bind_اظہاریہ (loc1, بلاک, stmt);

  بلاک = DECL_INITIAL (current_function_decl);
  بلاک_SUBBLOCKS (بلاک) = NULL_درخت;
  بلاک_CHAIN (بلاک) = NULL_درخت;
  درخت_ASM_WRITTEN (بلاک) = 1;

  إذا (cdil == cdil_gimple)
    {
      gbind *bind_stmt = gimple_build_bind (BIND_اظہاریہ_VARS (stmt), عدم,
					    BIND_اظہاریہ_بلاک (stmt));
      gimple_bind_سیٹ_body (bind_stmt, seq);
      gimple_seq_جوڑو_stmt_without_update (&body, bind_stmt);
      gimple_سیٹ_body (current_function_decl, body);
    }
  وإلا
    {
      /* Control-flow and binds are lowered, record local decls.  */
      لكل (درخت var = BIND_اظہاریہ_VARS (stmt); var; var = DECL_CHAIN (var))
	إذا (VAR_P (var)
	    && !DECL_EXTERNAL (var))
	  {
	    جوڑو_local_decl (cfun, var);
	    /* When the middle-end re-gimplifies any expression we might
	       run into the assertion that we've seen the decl in a BIND.  */
	    إذا (!درخت_STATIC (var))
	      DECL_تکیا_وچ_BIND_اظہاریہ_P (var) = 1;
	  }
      /* We have a CFG.  Build the edges.  */
      لكل (بنانشانی i = 0; i < parser.کنارے.لمائی (); ++i)
	{
	  کنارا e = make_کنارا (BASIC_بلاک_FOR_FN (cfun, parser.کنارے[i].src),
			      BASIC_بلاک_FOR_FN (cfun, parser.کنارے[i].dest),
			      parser.کنارے[i].flags);
	  e->probability = parser.کنارے[i].probability;
	}
      /* Add edges for case labels.  */
      basic_بلاک bb;
      FOR_EACH_BB_FN (bb, cfun)
	إذا (کنارا_گنتی (bb->succs) == 0)
	  {
	    إذا (gswitch *sw = محفوظ_dyn_cast <gswitch *> (*gsi_آخری_bb (bb)))
	      لكل (بنانشانی i = 0; i < gimple_switch_عدد_labels (sw); ++i)
		{
		  basic_بلاک label_bb = gimple_switch_label_bb (cfun, sw, i);
		  make_کنارا (bb, label_bb, 0);
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
	      لكل (gsi = gsi_شروع_bb (bb); !gsi_سرا_p (gsi);)
		{
		  gimple *stmt = gsi_stmt (gsi);
		  إذا (!gimple_call_اندرونی_p (stmt, IFN_PHI))
		    اكسر;

		  gphi *phi = create_phi_گرہ (gimple_call_lhs (stmt), bb);
		  لكل (بنانشانی i = 0; i < gimple_call_عدد_دلیلاں (stmt); i += 2)
		    {
		      صحيح srcidx = درخت_INT_CST_کم (gimple_call_arg (stmt, i));
		      کنارا e = لبھو_کنارا (BASIC_بلاک_FOR_FN (cfun, srcidx), bb);
		      إذا (!e)
			c_parser_error (parser, "edge not found");
		      وإلا
			جوڑو_phi_arg (phi, gimple_call_arg (stmt, i + 1), e,
				     UNKNOWN_LOCATION);
		    }
		  gsi_remove (&gsi, سچ);
		}
	      لكل (; !gsi_سرا_p (gsi); gsi_اگلا (&gsi))
		update_stmt (gsi_stmt (gsi));
	    }
	  /* Fill SSA name gaps, putting them on the freelist and diagnose
	     SSA names without definition.  */
	  لكل (بنانشانی i = 1; i < عدد_ssa_ناں; ++i)
	    إذا (!ssa_name (i))
	      {
		درخت name = make_ssa_name_fn (cfun, integer_type_گرہ, عدم, i);
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
      اندراج_بلاک_PTR_FOR_FN (cfun)->گنتی = اندراج_bb_گنتی;
      gcov_type t = param_gimple_fe_computed_hot_bb_حد;
      سیٹ_hot_bb_حد (t);
      update_max_bb_گنتی ();
      cgraph_گرہ::get_create (cfun->decl);
      cgraph_کنارا::rebuild_کنارے ();
    }

  /* Perform IL validation and if any error is found abort compilation
     of this function by zapping its body.  */
  إذا ((cfun->curr_properties & PROP_cfg)
      && verify_gimple_وچ_cfg (cfun, خطأ, خطأ))
    init_خالی_تھاواں_درخت_cfg ();
  وإلا إذا (!(cfun->curr_properties & PROP_cfg)
	   && verify_gimple_وچ_seq (gimple_body (current_function_decl), خطأ))
    gimple_سیٹ_body (current_function_decl, عدم);

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
  طالما (c_parser_اگلا_ٹوکن_شروع_declaration (parser))
    {
      c_parser_gimple_declaration (parser);
      إذا (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	أرجع خطأ;
    }

  طالما (c_parser_اگلا_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      إذا (c_parser_error (parser))
	{
	  c_parser_skip_until_لبھیا (parser, CPP_CLOSE_BRACE, عدم);
	  أرجع return_p;
	}
      وإلا إذا (c_parser_اگلا_token_is (parser, CPP_EOF))
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
		إذا (c_parser_اگلا_token_is (parser, CPP_NAME))
		  {
		    درخت label = c_parser_peek_token (parser)->قدر;
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
		parser.ڈالو_کنارا (parser.current_bb->اشاریہ, EXIT_بلاک, 0,
				  profile_probability::uninitialized ());
	      اكسر;
	    افتراضي:
	      اذهب اظہاریہ_stmt;
	    }
	  اكسر;
	حالة CPP_NAME:
	  إذا (c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_gimple_label (parser, seq);
	      اكسر;
	    }
	  إذا (c_parser_اگلا_token_is (parser, CPP_NAME)
	      && c_parser_peek_token (parser)->id_قسم == C_ID_ID
	      && strcmp (IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر),
			 "try") == 0)
	    {
	      c_parser_gimple_try_stmt (parser, seq);
	      اكسر;
	    }
	  /* Basic block specification.
	     __BB (index, ...)  */
	  إذا ((cfun->curr_properties & PROP_cfg)
	      && !strcmp (IDENTIFIER_اشارہ_گر
			    (c_parser_peek_token (parser)->قدر), "__BB"))
	    {
	      c_parser_consume_token (parser);
	      إذا (! c_parser_require (parser, CPP_OPEN_PAREN,
				      "expected %<(%>"))
		أرجع return_p;
	      إذا (c_parser_اگلا_token_is_not (parser, CPP_نمبر))
		{
		  c_parser_error (parser, "expected block index");
		  أرجع return_p;
		}
	      درخت tnum = c_parser_peek_token (parser)->قدر;
	      إذا (درخت_کوڈ (tnum) != INTEGER_CST)
		{
		  c_parser_error (parser, "expected block index");
		  أرجع return_p;
		}
	      صحيح اشاریہ = درخت_INT_CST_کم (tnum);
	      إذا (اشاریہ < عدد_FIXED_بلاکاں
		  || (اشاریہ < آخری_basic_بلاک_for_fn (cfun)
		      && BASIC_بلاک_FOR_FN (cfun, اشاریہ) != عدم))
		{
		  c_parser_error (parser, "invalid block index");
		  أرجع return_p;
		}
	      صحيح is_loop_سرخی_دا = -1;
	      profile_گنتی bb_گنتی = profile_گنتی::uninitialized ();
	      c_parser_consume_token (parser);
	      طالما (c_parser_اگلا_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  إذا (! c_parser_اگلا_token_is (parser, CPP_NAME))
		    {
		      c_parser_error (parser, "expected block specifier");
		      أرجع return_p;
		    }
		  /* loop_header (NUM)  */
		  إذا (!strcmp (IDENTIFIER_اشارہ_گر
			         (c_parser_peek_token (parser)->قدر),
			       "loop_header"))
		    {
		      c_parser_consume_token (parser);
		      إذا (! c_parser_require (parser, CPP_OPEN_PAREN,
					      "expected %<(%>"))
			أرجع return_p;
		      درخت loop_عدد;
		      إذا (! c_parser_اگلا_token_is (parser, CPP_نمبر)
			  || درخت_کوڈ (loop_عدد
					  = c_parser_peek_token (parser)->قدر)
			       != INTEGER_CST)
			{
			  c_parser_error (parser, "expected loop number");
			  أرجع return_p;
			}
		      c_parser_consume_token (parser);
		      is_loop_سرخی_دا = درخت_INT_CST_کم (loop_عدد);
		      إذا (! c_parser_require (parser, CPP_CLOSE_PAREN,
					      "expected %<)%>"))
			أرجع return_p;
		    }
		  /* Parse profile: quality(value) */
		  وإلا
		    {
		      درخت q;
		      profile_quality quality;
		      درخت v = c_parser_peek_token (parser)->قدر;
		      إذا (!parse_profile_quality (IDENTIFIER_اشارہ_گر (v),
						  &quality))
			{
			  c_parser_error (parser, "unknown block specifier");
			  أرجع خطأ;
			}

		      c_parser_consume_token (parser);
		      إذا (!c_parser_require (parser, CPP_OPEN_PAREN,
					     "expected %<(%>"))
			أرجع خطأ;

		      إذا (!c_parser_اگلا_token_is (parser, CPP_نمبر)
			  || (درخت_کوڈ (q = c_parser_peek_token (parser)->قدر)
			      != INTEGER_CST))
			{
			  c_parser_error (parser, "expected count value");
			  أرجع خطأ;
			}

		      bb_گنتی
			= profile_گنتی::from_gcov_type (درخت_INT_CST_کم (q),
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
	      إذا (!gimple_seq_خالی_تھاواں_p (*seq))
		{
		  إذا (!parser.current_bb)
		    c_parser_error (parser, "stmts without block");
		  وإلا
		    {
		      gimple_stmt_iterator gsi
			= gsi_شروع_bb (parser.current_bb);
		      gsi_داخل_کرو_seq_after_without_update (&gsi, *seq,
							   GSI_CONTINUE_LINKING);
		    }
		  *seq = عدم;
		}

	      /* Build an empty block with specified index, linking them
		 in source order.  */
	      basic_بلاک bb = alloc_بلاک ();
	      bb->اشاریہ = اشاریہ;
	      link_بلاک (bb, (parser.current_bb ? parser.current_bb
			       : اندراج_بلاک_PTR_FOR_FN (cfun)));
	      إذا (basic_بلاک_info_for_fn (cfun)->لمائی () <= (ناپ_t)اشاریہ)
		vec_محفوظ_grow_cleared (basic_بلاک_info_for_fn (cfun),
				       اشاریہ + 1, سچ);
	      سیٹ_BASIC_بلاک_FOR_FN (cfun, اشاریہ, bb);
	      إذا (آخری_basic_بلاک_for_fn (cfun) <= اشاریہ)
		آخری_basic_بلاک_for_fn (cfun) = اشاریہ + 1;
	      n_basic_بلاکاں_for_fn (cfun)++;
	      إذا (parser.current_bb->اشاریہ == اندراج_بلاک)
		parser.ڈالو_کنارا (اندراج_بلاک, bb->اشاریہ, کنارا_FALLTHRU,
				  profile_probability::always ());

	      /* We leave the proper setting to fixup.  */
	      صنف loop *loop_father = loops_for_fn (cfun)->درخت_جڑ;
	      /* If the new block is a loop header, allocate a loop
		 struct.  Fixup will take care of proper placement within
		 the loop tree.  */
	      إذا (is_loop_سرخی_دا != -1)
		{
		  إذا (نمبر_دا_loops (cfun) > (بنانشانی)is_loop_سرخی_دا
		      && get_loop (cfun, is_loop_سرخی_دا) != عدم)
		    {
		      c_parser_error (parser, "duplicate loop header");
		    }
		  وإلا
		    {
		      صنف loop *loop = alloc_loop ();
		      loop->عدد = is_loop_سرخی_دا;
		      loop->سرخی = bb;
		      إذا (نمبر_دا_loops (cfun) <= (بنانشانی)is_loop_سرخی_دا)
			vec_محفوظ_grow_cleared (loops_for_fn (cfun)->larray,
					       is_loop_سرخی_دا + 1, سچ);
		      (*loops_for_fn (cfun)->larray)[is_loop_سرخی_دا] = loop;
		      flow_loop_درخت_گرہ_جوڑو (loops_for_fn (cfun)->درخت_جڑ,
					       loop);
		    }
		  loop_father = get_loop (cfun, is_loop_سرخی_دا);
		}
	      bb->loop_father = loop_father;
	      bb->گنتی = bb_گنتی;

	      /* Stmts now go to the new block.  */
	      parser.current_bb = bb;
	      اكسر;
	    }
	  اذهب اظہاریہ_stmt;

	حالة CPP_SEMICOLON:
	  {
	    /* Empty stmt.  */
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);
	    gimple *nop = gimple_build_nop ();
	    gimple_سیٹ_location (nop, loc);
	    gimple_seq_جوڑو_stmt_without_update (seq, nop);
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
اظہاریہ_stmt:
	  c_parser_gimple_statement (parser, seq);
	  إذا (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	    c_parser_skip_until_لبھیا (parser, CPP_SEMICOLON, عدم);
	}
    }
  c_parser_consume_token (parser);

  /* Put stmts parsed in the current block.  */
  إذا ((cfun->curr_properties & PROP_cfg)
      && !gimple_seq_خالی_تھاواں_p (*seq))
    {
      إذا (!parser.current_bb)
	c_parser_error (parser, "stmts without block");
      وإلا
	{
	  gimple_stmt_iterator gsi = gsi_شروع_bb (parser.current_bb);
	  gsi_داخل_کرو_seq_after_without_update (&gsi, *seq,
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
  بنية c_اظہاریہ lhs, rhs;
  gimple *سونپو = عدم;
  location_t loc;
  درخت arg = NULL_درخت;
  auto_vec<درخت> vargs;

  lhs = c_parser_gimple_unary_عبارت (parser);
  loc = اظہاریہ_LOCATION (lhs.قدر);
  rhs.سیٹ_error ();

  /* GIMPLE call statement without LHS.  */
  إذا (c_parser_اگلا_token_is (parser, CPP_SEMICOLON)
      && درخت_کوڈ (lhs.قدر) == CALL_اظہاریہ)
    {
      gimple *call;
      call = gimple_build_call_from_درخت (lhs.قدر, عدم);
      gimple_seq_جوڑو_stmt_without_update (seq, call);
      gimple_سیٹ_location (call, loc);
      أرجع;
    }

  /* All following cases are statements with LHS.  */
  إذا (! c_parser_require (parser, CPP_EQ, "expected %<=%>"))
    أرجع;

  /* Eat and ignore {v} right after the =, the has_volatile_ops is
     redundant and re-computed by the operand scanner.  */
  إذا (c_parser_اگلا_token_is (parser, CPP_OPEN_BRACE)
      && !(c_parser_peek_token (parser)->flags & PREV_WHITE)
      && c_parser_peek_2nd_token (parser)->type == CPP_NAME
      && !(c_parser_peek_2nd_token (parser)->flags & PREV_WHITE)
      && strcmp ("v", IDENTIFIER_اشارہ_گر
			(c_parser_peek_2nd_token (parser)->قدر)) == 0
      && c_parser_peek_nth_token (parser, 3)->type == CPP_CLOSE_BRACE
      && !(c_parser_peek_nth_token (parser, 3)->flags & PREV_WHITE))
    {
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }

  /* Cast expression.  */
  إذا (c_parser_اگلا_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_typename (c_parser_peek_2nd_token (parser)))
    {
      c_parser_consume_token (parser);
      بنية c_type_name *type_name = c_parser_type_name (parser);
      c_parser_skip_until_لبھیا (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      إذا (type_name == عدم)
	أرجع;
      /* ???  The actual type used in the cast expression is ignored as
         in GIMPLE it is encoded by the type of the LHS.  */
      rhs = c_parser_gimple_postfix_عبارت (parser);
      إذا (lhs.قدر != error_mark_گرہ
	  && rhs.قدر != error_mark_گرہ)
	{
	  تعداد درخت_کوڈ_2 کوڈ = NOP_اظہاریہ;
	  إذا (FLOAT_TYPE_P (درخت_TYPE (lhs.قدر))
	      && ! FLOAT_TYPE_P (درخت_TYPE (rhs.قدر)))
	    کوڈ = FLOAT_اظہاریہ;
	  وإلا إذا (! FLOAT_TYPE_P (درخت_TYPE (lhs.قدر))
		   && FLOAT_TYPE_P (درخت_TYPE (rhs.قدر)))
	    کوڈ = FIX_TRUNC_اظہاریہ;
	  سونپو = gimple_build_سونپو (lhs.قدر, کوڈ, rhs.قدر);
	  gimple_seq_جوڑو_stmt_without_update (seq, سونپو);
	  gimple_سیٹ_location (سونپو, loc);
	  أرجع;
	}
    }

  /* Unary expression.  */
  بدل (c_parser_peek_token (parser)->type)
    {
    حالة CPP_NAME:
      {
	درخت id = c_parser_peek_token (parser)->قدر;
	إذا (strcmp (IDENTIFIER_اشارہ_گر (id), "__ABS") == 0
	    || strcmp (IDENTIFIER_اشارہ_گر (id), "__ABSU") == 0
	    || strcmp (IDENTIFIER_اشارہ_گر (id), "__MIN") == 0
	    || strcmp (IDENTIFIER_اشارہ_گر (id), "__MAX") == 0
	    || strcmp (IDENTIFIER_اشارہ_گر (id), "__BIT_INSERT") == 0
	    || strcmp (IDENTIFIER_اشارہ_گر (id), "__VEC_PERM") == 0)
	  اذهب build_unary_اظہاریہ;
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
    build_unary_اظہاریہ:
      rhs = c_parser_gimple_unary_عبارت (parser);
      إذا (rhs.قدر != error_mark_گرہ)
	{
	  سونپو = gimple_build_سونپو (lhs.قدر, rhs.قدر);
	  gimple_سیٹ_location (سونپو, loc);
	  gimple_seq_جوڑو_stmt_without_update (seq, سونپو);
	}
      أرجع;

    افتراضي:;
    }

  /* GIMPLE PHI statement.  */
  إذا (c_parser_اگلا_token_is_keyword (parser, RID_PHI))
    {
      c_parser_consume_token (parser);

      إذا (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	أرجع;

      إذا (c_parser_اگلا_token_is (parser, CPP_OPEN_PAREN))
	c_parser_consume_token (parser);

      طالما (c_parser_اگلا_token_is_not (parser, CPP_CLOSE_PAREN))
	{
	  إذا (c_parser_اگلا_token_is (parser, CPP_NAME)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      arg = c_parser_peek_token (parser)->قدر;
	      c_parser_consume_token (parser);
	      إذا (c_parser_اگلا_token_is (parser, CPP_COLON))
		c_parser_consume_token (parser);
	      صحيح src_اشاریہ = -1;
	      إذا (!c_parser_gimple_parse_bb_spec (arg, &src_اشاریہ))
		c_parser_error (parser, "invalid source block specification");
	      vargs.محفوظ_ڈالو (ناپ_int (src_اشاریہ));
	    }
	  وإلا إذا (c_parser_اگلا_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  وإلا
	    {
	      arg = c_parser_gimple_unary_عبارت (parser).قدر;
	      vargs.محفوظ_ڈالو (arg);
	    }
	}

      c_parser_skip_until_لبھیا (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");

      /* Build internal function for PHI.  */
      gcall *call_stmt = gimple_build_call_اندرونی_vec (IFN_PHI, vargs);
      gimple_call_سیٹ_lhs (call_stmt, lhs.قدر);
      gimple_سیٹ_location (call_stmt, UNKNOWN_LOCATION);
      gimple_seq_جوڑو_stmt_without_update (seq, call_stmt);
      أرجع;
    }

  /* GIMPLE call with lhs.  */
  إذا (c_parser_اگلا_token_is (parser, CPP_DOT)
      || (c_parser_اگلا_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN
	  && lookup_name (c_parser_peek_token (parser)->قدر)))
    {
      rhs = c_parser_gimple_unary_عبارت (parser);
      إذا (rhs.قدر != error_mark_گرہ)
	{
	  gimple *call = gimple_build_call_from_درخت (rhs.قدر, عدم);
	  gimple_call_سیٹ_lhs (call, lhs.قدر);
	  gimple_seq_جوڑو_stmt_without_update (seq, call);
	  gimple_سیٹ_location (call, loc);
	}
      أرجع;
    }

  rhs = c_parser_gimple_ثنائی_عبارت (parser, درخت_TYPE (lhs.قدر));
  إذا (lhs.قدر != error_mark_گرہ
      && rhs.قدر != error_mark_گرہ)
    {
      /* If we parsed an identifier and the next token  is a '?' then parse
	 a conditional expression.  */
      إذا (SSA_VAR_P (rhs.قدر) && c_parser_اگلا_token_is (parser, CPP_QUERY))
	{
	  بنية c_اظہاریہ trueval, falseval;
	  c_parser_consume_token (parser);
	  trueval = c_parser_gimple_postfix_عبارت (parser);
	  falseval.سیٹ_error ();
	  إذا (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    falseval = c_parser_gimple_postfix_عبارت (parser);
	  إذا (trueval.قدر == error_mark_گرہ
	      || falseval.قدر == error_mark_گرہ)
	    أرجع;
	  rhs.قدر = build3_loc (loc,
				  سمتیہ_TYPE_P (درخت_TYPE (rhs.قدر))
				  ? VEC_COND_اظہاریہ : COND_اظہاریہ,
				  درخت_TYPE (trueval.قدر),
				  rhs.قدر, trueval.قدر, falseval.قدر);
	}
      إذا (get_gimple_rhs_class (درخت_کوڈ (rhs.قدر)) == GIMPLE_INVALID_RHS)
	{
	  c_parser_error (parser, "unexpected RHS for assignment");
	  أرجع;
	}
      سونپو = gimple_build_سونپو (lhs.قدر, rhs.قدر);
      gimple_seq_جوڑو_stmt_without_update (seq, سونپو);
      gimple_سیٹ_location (سونپو, loc);
    }
  أرجع;
}

/* A mapping between an identifier to a tree code for binary operations. */
ساكن ثابت std::pair<ثابت حرف *, درخت_کوڈ_2> gimple_ثنائی_identifier_کوڈ[] =
  {
    {"__MULT_HIGHPART", MULT_HIGHPART_اظہاریہ},
    {"__UNLT", UNLT_اظہاریہ},
    {"__UNLE", UNLE_اظہاریہ},
    {"__UNGT", UNGT_اظہاریہ},
    {"__UNGE", UNGE_اظہاریہ},
    {"__UNEQ", UNEQ_اظہاریہ},
    {"__UNORDERED", UNORDERED_اظہاریہ},
    {"__ORDERED", ORDERED_اظہاریہ},
    {"__LTGT", LTGT_اظہاریہ},
    {"__FLOOR_DIV", FLOOR_DIV_اظہاریہ},
    {"__ROUND_DIV", گیڑا_DIV_اظہاریہ},
    {"__EXACT_DIV", EXACT_DIV_اظہاریہ},
    {"__CEIL_DIV", CEIL_DIV_اظہاریہ},
    {"__FLOOR_MOD", FLOOR_MOD_اظہاریہ},
    {"__ROUND_MOD", گیڑا_MOD_اظہاریہ},
    {"__CEIL_MOD", CEIL_MOD_اظہاریہ},
    {"__ROTATE_LEFT", LROTATE_اظہاریہ},
    {"__ROTATE_RIGHT", RROTATE_اظہاریہ},
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

ساكن c_اظہاریہ
c_parser_gimple_ثنائی_عبارت (gimple_parser &parser, درخت ret_type)
{
  /* Location of the binary operator.  */
  بنية c_اظہاریہ ret, lhs, rhs;
  تعداد درخت_کوڈ_2 کوڈ = ERROR_MARK;
  ret.سیٹ_error ();
  lhs = c_parser_gimple_postfix_عبارت (parser, ret_type);
  إذا (c_parser_error (parser))
    أرجع ret;
  بدل (c_parser_peek_token (parser)->type)
    {
    حالة CPP_MULT:
      کوڈ = MULT_اظہاریہ;
      اكسر;
    حالة CPP_DIV:
      کوڈ = TRUNC_DIV_اظہاریہ;
      اكسر;
    حالة CPP_MOD:
      کوڈ = TRUNC_MOD_اظہاریہ;
      اكسر;
    حالة CPP_PLUS:
      إذا (اشارہ_گر_TYPE_P (درخت_TYPE (lhs.قدر)))
	کوڈ = اشارہ_گر_PLUS_اظہاریہ;
      وإلا
	کوڈ = PLUS_اظہاریہ;
      اكسر;
    حالة CPP_MINUS:
      إذا (اشارہ_گر_TYPE_P (درخت_TYPE (lhs.قدر)))
	کوڈ = اشارہ_گر_DIFF_اظہاریہ;
      وإلا
	کوڈ = MINUS_اظہاریہ;
      اكسر;
    حالة CPP_LSHIFT:
      کوڈ = LSHIFT_اظہاریہ;
      اكسر;
    حالة CPP_RSHIFT:
      کوڈ = RSHIFT_اظہاریہ;
      اكسر;
    حالة CPP_LESS:
      کوڈ = LT_اظہاریہ;
      اكسر;
    حالة CPP_GREATER:
      کوڈ = GT_اظہاریہ;
      اكسر;
    حالة CPP_LESS_EQ:
      کوڈ = LE_اظہاریہ;
      اكسر;
    حالة CPP_GREATER_EQ:
      کوڈ = GE_اظہاریہ;
      اكسر;
    حالة CPP_EQ_EQ:
      کوڈ = EQ_اظہاریہ;
      اكسر;
    حالة CPP_NOT_EQ:
      کوڈ = NE_اظہاریہ;
      اكسر;
    حالة CPP_AND:
      کوڈ = ثنائی_ہندسہ_AND_اظہاریہ;
      اكسر;
    حالة CPP_XOR:
      کوڈ = ثنائی_ہندسہ_XOR_اظہاریہ;
      اكسر;
    حالة CPP_OR:
      کوڈ = ثنائی_ہندسہ_IOR_اظہاریہ;
      اكسر;
    حالة CPP_AND_AND:
      c_parser_error (parser, "%<&&%> not valid in GIMPLE");
      أرجع ret;
    حالة CPP_OR_OR:
      c_parser_error (parser, "%<||%> not valid in GIMPLE");
      أرجع ret;
    حالة CPP_NAME:
      {
	درخت id = c_parser_peek_token (parser)->قدر;
	لكل (خودکار &p : gimple_ثنائی_identifier_کوڈ)
	  {
	    إذا (strcmp (IDENTIFIER_اشارہ_گر (id), p.پہلا) == 0)
	      {
		کوڈ = p.دوجا;
		اكسر;
	      }
	  }
	إذا (کوڈ != ERROR_MARK)
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
  إذا (lhs.قدر != error_mark_گرہ && rhs.قدر != error_mark_گرہ)
    ret.قدر = build2_loc (ret_loc, کوڈ, ret_type, lhs.قدر, rhs.قدر);
  أرجع ret;
}

/* Parse a gimple parentized binary expression.  */

ساكن c_اظہاریہ
c_parser_gimple_parentized_ثنائی_عبارت (gimple_parser &parser,
					      location_t op_loc,
					      درخت_کوڈ_2 کوڈ)
{
  بنية c_اظہاریہ ret;
  ret.سیٹ_error ();

  c_parser_consume_token (parser);
  إذا (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    أرجع ret;
  c_اظہاریہ op1 = c_parser_gimple_postfix_عبارت (parser);
  إذا (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    أرجع ret;
  c_اظہاریہ op2 = c_parser_gimple_postfix_عبارت (parser);
  إذا (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    أرجع ret;

  إذا (op1.قدر != error_mark_گرہ && op2.قدر != error_mark_گرہ)
    ret.قدر = build2_loc (op_loc,
			    کوڈ, درخت_TYPE (op1.قدر), op1.قدر, op2.قدر);
  أرجع ret;
}

/* Parse a gimple parentized binary expression.  */

ساكن c_اظہاریہ
c_parser_gimple_parentized_ternary_عبارت (gimple_parser &parser,
					       location_t op_loc,
					       درخت_کوڈ_2 کوڈ)
{
  بنية c_اظہاریہ ret;
  ret.سیٹ_error ();

  c_parser_consume_token (parser);
  إذا (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    أرجع ret;
  c_اظہاریہ op1 = c_parser_gimple_postfix_عبارت (parser);
  إذا (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    أرجع ret;
  c_اظہاریہ op2 = c_parser_gimple_postfix_عبارت (parser);
  إذا (!c_parser_require (parser, CPP_COMMA, "expected %<)%>"))
    أرجع ret;
  c_اظہاریہ op3 = c_parser_gimple_postfix_عبارت (parser);
  إذا (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    أرجع ret;

  إذا (op1.قدر != error_mark_گرہ
      && op2.قدر != error_mark_گرہ
      && op3.قدر != error_mark_گرہ)
    ret.قدر = build3_loc (op_loc,
			    کوڈ, درخت_TYPE (op1.قدر),
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

ساكن c_اظہاریہ
c_parser_gimple_unary_عبارت (gimple_parser &parser)
{
  بنية c_اظہاریہ ret, op;
  location_t op_loc = c_parser_peek_token (parser)->location;
  location_t انت;
  ret.سیٹ_error ();
  بدل (c_parser_peek_token (parser)->type)
    {
    حالة CPP_AND:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_عبارت (parser);
      mark_exp_read (op.قدر);
      أرجع gimple_parser_build_unary_op (op_loc, ADDR_اظہاریہ, op);
    حالة CPP_MULT:
      {
	c_parser_consume_token (parser);
	op = c_parser_gimple_postfix_عبارت (parser);
	إذا (op.قدر == error_mark_گرہ)
	  أرجع ret;
	إذا (! اشارہ_گر_TYPE_P (درخت_TYPE (op.قدر)))
	  {
	    error_at (op_loc, "expected pointer as argument of unary %<*%>");
	    أرجع ret;
	  }
	انت = op.get_انت ();
	location_t combined_loc = make_location (op_loc, op_loc, انت);
	ret.قدر = build_simple_mem_ref_loc (combined_loc, op.قدر);
	درخت_SIDE_EFFECTS (ret.قدر)
	  = درخت_THIS_VOLATILE (ret.قدر)
	  = TYPE_VOLATILE (درخت_TYPE (درخت_TYPE (op.قدر)));
	ret.src_range.m_شروع = op_loc;
	ret.src_range.m_انت = انت;
	أرجع ret;
      }
    حالة CPP_PLUS:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_عبارت (parser);
      أرجع gimple_parser_build_unary_op (op_loc, CONVERT_اظہاریہ, op);
    حالة CPP_MINUS:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_عبارت (parser);
      أرجع gimple_parser_build_unary_op (op_loc, NEGATE_اظہاریہ, op);
    حالة CPP_COMPL:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_عبارت (parser);
      أرجع gimple_parser_build_unary_op (op_loc, ثنائی_ہندسہ_NOT_اظہاریہ, op);
    حالة CPP_NOT:
      c_parser_error (parser, "%<!%> not valid in GIMPLE");
      أرجع ret;
    حالة CPP_KEYWORD:
      بدل (c_parser_peek_token (parser)->keyword)
	{
	حالة RID_REALPART:
	  c_parser_consume_token (parser);
	  op = c_parser_gimple_postfix_عبارت (parser);
	  أرجع gimple_parser_build_unary_op (op_loc, REALPART_اظہاریہ, op);
	حالة RID_IMAGPART:
	  c_parser_consume_token (parser);
	  op = c_parser_gimple_postfix_عبارت (parser);
	  أرجع gimple_parser_build_unary_op (op_loc, IMAGPART_اظہاریہ, op);
	افتراضي:
	  أرجع c_parser_gimple_postfix_عبارت (parser);
	}
    حالة CPP_NAME:
	{
	  درخت id = c_parser_peek_token (parser)->قدر;
	  إذا (strcmp (IDENTIFIER_اشارہ_گر (id), "__ABS") == 0)
	    {
	      c_parser_consume_token (parser);
	      op = c_parser_gimple_postfix_عبارت (parser);
	      أرجع gimple_parser_build_unary_op (op_loc, ABS_اظہاریہ, op);
	    }
	  وإلا إذا (strcmp (IDENTIFIER_اشارہ_گر (id), "__ABSU") == 0)
	    {
	      c_parser_consume_token (parser);
	      op = c_parser_gimple_postfix_عبارت (parser);
	      أرجع gimple_parser_build_unary_op (op_loc, ABSU_اظہاریہ, op);
	    }
	  وإلا إذا (strcmp (IDENTIFIER_اشارہ_گر (id), "__MIN") == 0)
	    أرجع c_parser_gimple_parentized_ثنائی_عبارت (parser,
								 op_loc,
								 MIN_اظہاریہ);
	  وإلا إذا (strcmp (IDENTIFIER_اشارہ_گر (id), "__MAX") == 0)
	    أرجع c_parser_gimple_parentized_ثنائی_عبارت (parser,
								 op_loc,
								 MAX_اظہاریہ);
	  وإلا إذا (strcmp (IDENTIFIER_اشارہ_گر (id), "__VEC_PERM") == 0)
	    أرجع c_parser_gimple_parentized_ternary_عبارت
			(parser, op_loc, VEC_PERM_اظہاریہ);
	  وإلا إذا (strcmp (IDENTIFIER_اشارہ_گر (id), "__BIT_INSERT") == 0)
	    {
	      /* __BIT_INSERT '(' postfix-expression, postfix-expression,
			          integer ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      إذا (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_اظہاریہ op0 = c_parser_gimple_postfix_عبارت (parser);
		  c_parser_skip_until_لبھیا (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_اظہاریہ op1 = c_parser_gimple_postfix_عبارت (parser);
		  c_parser_skip_until_لبھیا (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_اظہاریہ op2 = c_parser_gimple_postfix_عبارت (parser);
		  إذا (درخت_کوڈ (op2.قدر) != INTEGER_CST
		      || !int_سماندا_type_p (op2.قدر, bitsizetype))
		    c_parser_error (parser, "expected constant offset");
		  c_parser_skip_until_لبھیا (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  إذا (op0.قدر != error_mark_گرہ
		      && op1.قدر != error_mark_گرہ
		      && درخت_کوڈ (op2.قدر) == INTEGER_CST)
		    ret.قدر = build3_loc (loc, ثنائی_ہندسہ_داخل_کرو_اظہاریہ,
					    درخت_TYPE (op0.قدر),
					    op0.قدر, op1.قدر,
					    fold_convert (bitsizetype,
							  op2.قدر));
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
c_parser_parse_ssa_name_id (درخت id, بنانشانی *نسخہ, بنانشانی *ver_وتھ)
{
  ثابت حرف *token = IDENTIFIER_اشارہ_گر (id);
  ثابت حرف *var_نسخہ = strrchr (token, '_');
  إذا (! var_نسخہ)
    أرجع خطأ;

  *ver_وتھ = var_نسخہ - token;
  لكل (ثابت حرف *p = var_نسخہ + 1; *p; ++p)
    إذا (! ISDIGIT (*p))
      أرجع خطأ;
  *نسخہ = atoi (var_نسخہ + 1);
  أرجع *نسخہ > 0;
}

/* Get at the actual SSA name ID with VERSION starting at VER_OFFSET.
   TYPE is the type if the SSA name is being declared.  */

ساكن درخت
c_parser_parse_ssa_name (gimple_parser &parser,
			 درخت id, درخت type, بنانشانی نسخہ,
			 بنانشانی ver_وتھ)
{
  درخت name = NULL_درخت;
  ثابت حرف *token = IDENTIFIER_اشارہ_گر (id);

  إذا (ver_وتھ == 0)
    {
      /* Anonymous unnamed SSA name.  */
      إذا (نسخہ < عدد_ssa_ناں)
	name = ssa_name (نسخہ);
      إذا (! name)
	{
	  إذا (! type)
	    {
	      c_parser_error (parser, "SSA name undeclared");
	      أرجع error_mark_گرہ;
	    }
	  name = make_ssa_name_fn (cfun, type, عدم, نسخہ);
	}
    }
  وإلا
    {
      إذا (نسخہ < عدد_ssa_ناں)
	name = ssa_name (نسخہ);
      إذا (! name)
	{
	  /* Separate var name from version.  */
	  حرف *var_name = XNEWVEC (حرف, ver_وتھ + 1);
	  حافظہ_نقل (var_name, token, ver_وتھ);
	  var_name[ver_وتھ] = '\0';
	  /* lookup for parent decl.  */
	  id = get_identifier (var_name);
	  درخت ماپا = lookup_name (id);
	  XDELETEVEC (var_name);
	  إذا (! ماپا || ماپا == error_mark_گرہ)
	    {
	      c_parser_error (parser, "base variable or SSA name undeclared");
	      أرجع error_mark_گرہ;
	    }
	  إذا (!(VAR_P (ماپا)
		|| درخت_کوڈ (ماپا) == PARM_DECL
		|| درخت_کوڈ (ماپا) == نتیجہ_DECL))
	    {
	      error ("invalid base %qE for SSA name", ماپا);
	      أرجع error_mark_گرہ;
	    }
	  name = make_ssa_name_fn (cfun, ماپا,
				   gimple_build_nop (), نسخہ);
	}
    }

  أرجع name;
}

/* Parse a gimple call to an internal function.

   gimple-call-internal:
     . identifier ( gimple-argument-expression-list[opt] )  */

ساكن بنية c_اظہاریہ
c_parser_gimple_call_اندرونی (gimple_parser &parser)
{
  بنية c_اظہاریہ اظہاریہ;
  اظہاریہ.سیٹ_error ();

  gcc_assert (c_parser_اگلا_token_is (parser, CPP_DOT));
  c_parser_consume_token (parser);
  location_t loc = c_parser_peek_token (parser)->location;
  إذا (!c_parser_اگلا_token_is (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_قسم != C_ID_ID)
    {
      c_parser_error (parser, "expecting internal function name");
      أرجع اظہاریہ;
    }
  درخت id = c_parser_peek_token (parser)->قدر;
  اندرونی_fn ifn = lookup_اندرونی_fn (IDENTIFIER_اشارہ_گر (id));
  c_parser_consume_token (parser);
  إذا (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    {
      auto_vec<درخت> exprlist;
      إذا (!c_parser_اگلا_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_gimple_اظہاریہ_list (parser, &exprlist);
      c_parser_skip_until_لبھیا (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      إذا (ifn == IFN_آخری)
	error_at (loc, "unknown internal function %qE", id);
      وإلا
	{
	  اظہاریہ.قدر = build_call_اظہاریہ_اندرونی_loc_array
	    (loc, ifn, void_type_گرہ, exprlist.لمائی (),
	     exprlist.پتہ ());
	  اظہاریہ.original_کوڈ = ERROR_MARK;
	  اظہاریہ.original_type = عدم;
	  اظہاریہ.m_decimal = 0;
	}
    }
  أرجع اظہاریہ;
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
      إذا (c_parser_اگلا_token_is (parser, CPP_COMMA))
	{
	  c_parser_consume_token (parser);
	  alignment
	      = c_parser_gimple_postfix_عبارت (parser).قدر;
	}
      c_parser_skip_until_لبھیا (parser,
				 CPP_GREATER, "expected %<>%>");
    }
  إذا (!type_name)
    أرجع NULL_درخت;
  درخت tem;
  درخت type = groktypename (type_name, &tem, عدم);
  إذا (alignment)
    type = build_aligned_type (type, درخت_منزل_uhwi (alignment));
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

ساكن بنية c_اظہاریہ
c_parser_gimple_postfix_عبارت (gimple_parser &parser, درخت ret_type)
{
  location_t loc = c_parser_peek_token (parser)->location;
  سروت_range tok_range = c_parser_peek_token (parser)->get_range ();
  بنية c_اظہاریہ اظہاریہ;
  اظہاریہ.سیٹ_error ();
  بدل (c_parser_peek_token (parser)->type)
    {
    حالة CPP_نمبر:
      اظہاریہ.قدر = c_parser_peek_token (parser)->قدر;
      سیٹ_c_اظہاریہ_سروت_range (&اظہاریہ, tok_range);
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      اكسر;
    حالة CPP_CHAR:
    حالة CPP_CHAR16:
    حالة CPP_CHAR32:
    حالة CPP_UTF8CHAR:
    حالة CPP_WCHAR:
      اظہاریہ.قدر = c_parser_peek_token (parser)->قدر;
      سیٹ_c_اظہاریہ_سروت_range (&اظہاریہ, tok_range);
      c_parser_consume_token (parser);
      اكسر;
    حالة CPP_STRING:
    حالة CPP_STRING16:
    حالة CPP_STRING32:
    حالة CPP_WSTRING:
    حالة CPP_UTF8STRING:
      اظہاریہ = c_parser_string_literal (parser, خطأ, سچ);
      اكسر;
    حالة CPP_DOT:
      اظہاریہ = c_parser_gimple_call_اندرونی (parser);
      اكسر;
    حالة CPP_NAME:
      إذا (c_parser_peek_token (parser)->id_قسم == C_ID_ID)
	{
	  درخت id = c_parser_peek_token (parser)->قدر;
	  إذا (strcmp (IDENTIFIER_اشارہ_گر (id), "__MEM") == 0)
	    {
	      /* __MEM '<' type-name [ ',' number ] '>'
	               '(' [ '(' type-name ')' ] unary-expression
			   [ '+' number ]
			   [ ',' number ]
			   [ ',' number ':' number ] ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      درخت type = c_parser_gimple_typespec (parser);
	      بنية c_اظہاریہ ptr, alias_off, قدم, اشاریہ, index2;
	      ptr.قدر = error_mark_گرہ;
	      alias_off.قدر = NULL_درخت;
	      قدم.قدر = NULL_درخت;
	      اشاریہ.قدر = NULL_درخت;
	      index2.قدر = NULL_درخت;
	      بنانشانی چھوٹا clique = 0;
	      بنانشانی چھوٹا ادھار = 0;
	      منطقي الٹ_ترتیب = خطأ;
	      بنية c_اظہاریہ ro;
	      إذا (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  درخت alias_type = NULL_درخت;
		  /* Optional alias-type cast.  */
		  إذا (c_parser_اگلا_token_is (parser, CPP_OPEN_PAREN))
		    {
		      c_parser_consume_token (parser);
		      بنية c_type_name *alias_type_name
			= c_parser_type_name (parser);
		      c_parser_skip_until_لبھیا (parser, CPP_CLOSE_PAREN,
						 "expected %<)%>");
		      إذا (alias_type_name)
			{
			  درخت tem;
			  alias_type = groktypename (alias_type_name,
						     &tem, عدم);
			}
		    }
		  ptr = c_parser_gimple_unary_عبارت (parser);
		  إذا (ptr.قدر == error_mark_گرہ
		      || ! اشارہ_گر_TYPE_P (درخت_TYPE (ptr.قدر)))
		    {
		      إذا (ptr.قدر != error_mark_گرہ)
			error_at (ptr.get_شروع (),
				  "invalid type of %<__MEM%> operand");
		      c_parser_skip_until_لبھیا (parser, CPP_CLOSE_PAREN,
						 "expected %<)%>");
		      أرجع اظہاریہ;
		    }
		  إذا (! alias_type)
		    alias_type = درخت_TYPE (ptr.قدر);
		  /* Optional constant offset.  */
		  إذا (c_parser_اگلا_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      alias_off = c_parser_gimple_postfix_عبارت (parser);
		    }
		  إذا (c_parser_اگلا_token_is (parser, CPP_MULT))
		    {
		      std::وٹاندرا (اشاریہ, alias_off);
		      c_parser_consume_token (parser);
		      قدم = c_parser_gimple_postfix_عبارت (parser);
		    }
		  وإلا إذا (c_parser_اگلا_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      اشاریہ = c_parser_gimple_postfix_عبارت (parser);
		      إذا (c_parser_اگلا_token_is (parser, CPP_MULT))
			{
			  c_parser_consume_token (parser);
			  قدم = c_parser_gimple_postfix_عبارت (parser);
			}
		      وإلا
			std::وٹاندرا (اشاریہ, index2);
		    }
		  وإلا إذا (alias_off.قدر
			   && درخت_کوڈ (alias_off.قدر) != INTEGER_CST)
		    std::وٹاندرا (alias_off, index2);
		  إذا (c_parser_اگلا_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      index2 = c_parser_gimple_postfix_عبارت (parser);
		    }
		  إذا (alias_off.قدر)
		    {
		      إذا (درخت_کوڈ (alias_off.قدر) != INTEGER_CST)
			error_at (alias_off.get_شروع (),
				  "expected constant offset for %<__MEM%> "
				  "operand");
		      alias_off.قدر = fold_convert (alias_type,
						      alias_off.قدر);
		    }
		  وإلا
		    alias_off.قدر = build_int_cst (alias_type, 0);
		  إذا (قدم.قدر)
		    {
		      إذا (درخت_کوڈ (قدم.قدر) != INTEGER_CST)
			error_at (قدم.get_شروع (),
				  "expected constant step for %<__MEM%> "
				  "operand");
		    }
		  إذا (c_parser_اگلا_token_is (parser, CPP_COMMA))
		    {
		      بنية c_اظہاریہ cl, ba;
		      منطقي has_clb = سچ;
		      c_parser_consume_token (parser);
		      cl = c_parser_gimple_postfix_عبارت (parser);
		      إذا (!c_parser_اگلا_token_is (parser, CPP_COLON))
			{
			  ro = cl;
			  بنانشانی HOST_WIDE_INT tmp = 0;
			  إذا (!درخت_سماندا_uhwi_p (ro.قدر)
			      || (tmp = درخت_منزل_uhwi (ro.قدر)) > 1)
			    error_at (ro.get_شروع (),
				      "invalid reverse order value");
			  الٹ_ترتیب = tmp;
			  has_clb = خطأ;
			  إذا (c_parser_اگلا_token_is (parser, CPP_COMMA))
			    {
			      c_parser_consume_token (parser);
			      cl = c_parser_gimple_postfix_عبارت (parser);
		              has_clb = سچ;
			    }
			}
		      إذا (has_clb
			  && c_parser_require (parser,
					       CPP_COLON, "expected %<:%>"))
			{
			  ba = c_parser_gimple_postfix_عبارت (parser);
			  إذا (!درخت_سماندا_uhwi_p (cl.قدر)
			      || !درخت_سماندا_uhwi_p (ba.قدر)
			      || compare_درخت_int (cl.قدر,
						   (clique = درخت_منزل_uhwi
								(cl.قدر)))
			      || compare_درخت_int (ba.قدر,
						   (ادھار = درخت_منزل_uhwi
								 (ba.قدر))))
			    error_at (cl.get_شروع (),
				      "invalid clique/base pair");
			}
		    }
		  c_parser_skip_until_لبھیا (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      إذا (! type || c_parser_error (parser))
		{
		  c_parser_سیٹ_error (parser, خطأ);
		  أرجع اظہاریہ;
		}
	      إذا (اشاریہ.قدر || قدم.قدر || index2.قدر)
		اظہاریہ.قدر = build5_loc (loc, نشانہ_MEM_REF,
					 type, ptr.قدر, alias_off.قدر,
					 اشاریہ.قدر, قدم.قدر, index2.قدر);
	      وإلا
		اظہاریہ.قدر = build2_loc (loc, MEM_REF,
					 type, ptr.قدر, alias_off.قدر);
	      إذا (clique != 0)
		{
		  cfun->آخری_clique = MAX (cfun->آخری_clique, clique);
		  MR_DEPENDENCE_CLIQUE (اظہاریہ.قدر) = clique;
		  MR_DEPENDENCE_ادھار (اظہاریہ.قدر) = ادھار;
		}
	      إذا (الٹ_ترتیب)
		{
		  إذا (درخت_کوڈ (اظہاریہ.قدر) == MEM_REF)
		    REF_الٹ_STORAGE_ترتیب (اظہاریہ.قدر) = الٹ_ترتیب;
		  وإلا
		    error_at (ro.get_شروع (),
			      "target mem ref cannot have reverse order");
		}
	      اكسر;
	    }
	  وإلا إذا (strcmp (IDENTIFIER_اشارہ_گر (id), "__VIEW_CONVERT") == 0)
	    {
	      /* __VIEW_CONVERT '<' type-name [ ',' number ] '>'
	                        '(' postfix-expression ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      درخت type = c_parser_gimple_typespec (parser);
	      إذا (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_اظہاریہ op = c_parser_gimple_postfix_عبارت (parser);
		  c_parser_skip_until_لبھیا (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  إذا (type && op.قدر != error_mark_گرہ)
		    اظہاریہ.قدر = build1_loc (loc, VIEW_CONVERT_اظہاریہ,
					     type, op.قدر);
		}
	      اكسر;
	    }
	  وإلا إذا (strcmp (IDENTIFIER_اشارہ_گر (id), "__BIT_FIELD_REF") == 0)
	    {
	      /* __BIT_FIELD_REF '<' type-name [ ',' number ] '>'
	                        '(' postfix-expression, integer, integer ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      درخت type = c_parser_gimple_typespec (parser);
	      إذا (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_اظہاریہ op0 = c_parser_gimple_postfix_عبارت (parser);
		  c_parser_skip_until_لبھیا (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_اظہاریہ op1 = c_parser_gimple_postfix_عبارت (parser);
		  إذا (درخت_کوڈ (op1.قدر) != INTEGER_CST
		      || !int_سماندا_type_p (op1.قدر, bitsizetype))
		    c_parser_error (parser, "expected constant size");
		  c_parser_skip_until_لبھیا (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_اظہاریہ op2 = c_parser_gimple_postfix_عبارت (parser);
		  إذا (درخت_کوڈ (op2.قدر) != INTEGER_CST
		      || !int_سماندا_type_p (op2.قدر, bitsizetype))
		    c_parser_error (parser, "expected constant offset");
		  c_parser_skip_until_لبھیا (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  إذا (type
		      && op0.قدر != error_mark_گرہ
		      && درخت_کوڈ (op1.قدر) == INTEGER_CST
		      && درخت_کوڈ (op2.قدر) == INTEGER_CST)
		    اظہاریہ.قدر = build3_loc (loc, ثنائی_ہندسہ_میدان_REF, type,
					     op0.قدر,
					     fold_convert (bitsizetype,
							   op1.قدر),
					     fold_convert (bitsizetype,
							   op2.قدر));
		}
	      اكسر;
	    }
	  وإلا إذا (strcmp (IDENTIFIER_اشارہ_گر (id), "__CLOBBER") == 0)
	    {
	      /* __CLOBBER [ '(' bob | eob | bos | eos ')' ]  */
	      clobber_قسم قسم = CLOBBER_UNDEF;
	      c_parser_consume_token (parser);
	      إذا (c_parser_اگلا_token_is (parser, CPP_OPEN_PAREN))
		{
		  c_parser_consume_token (parser);
		  خودکار tok = c_parser_peek_token (parser);
		  إذا (c_parser_require (parser, CPP_NAME,
					"expected clobber kind"))
		    {
		      ثابت حرف *قسم_str = IDENTIFIER_اشارہ_گر (tok->قدر);
		      إذا (strcmp (قسم_str, "bos") == 0)
			قسم = CLOBBER_STORAGE_BEGIN;
		      وإلا إذا (strcmp (قسم_str, "bob") == 0)
			قسم = CLOBBER_OBJECT_BEGIN;
		      وإلا إذا (strcmp (قسم_str, "eob") == 0)
			قسم = CLOBBER_OBJECT_سرا;
		      وإلا إذا (strcmp (قسم_str, "eos") == 0)
			قسم = CLOBBER_STORAGE_سرا;
		      وإلا
			c_parser_error (parser, "expected one of %<bos%>, "
					"%<eos%>, %<bob>, %<eob%>");
		    }
		  c_parser_skip_until_لبھیا (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      /* We infer the (redundant) type from the LHS.  */
	      اظہاریہ.قدر = build_clobber (ret_type, قسم);
	      اكسر;
	    }
	  وإلا إذا (strcmp (IDENTIFIER_اشارہ_گر (id), "_Literal") == 0)
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
		  c_parser_skip_until_لبھیا (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      إذا (! type)
		{
		  c_parser_error (parser, "invalid _Literal");
		  أرجع اظہاریہ;
		}
	      إذا (c_parser_اگلا_token_is (parser, CPP_OPEN_BRACE))
		{
		  c_parser_consume_token (parser);
		  إذا (!AGGREGATE_TYPE_P (type)
		      && !سمتیہ_TYPE_P (type))
		    {
		      c_parser_error (parser, "invalid type for _Literal with "
				      "constructor");
		      c_parser_skip_until_لبھیا (parser, CPP_CLOSE_BRACE,
						 "expected %<}%>");
		      أرجع اظہاریہ;
		    }
		  vec<constructor_elt, va_gc> *v = عدم;
		  منطقي constant_p = سچ;
		  إذا (سمتیہ_TYPE_P (type)
		      && !c_parser_اگلا_token_is (parser, CPP_CLOSE_BRACE))
		    {
		      vec_alloc (v, TYPE_سمتیہ_SUBPARTS (type).منزل_constant ());
		      افعل
			{
			  درخت val
			    = c_parser_gimple_postfix_عبارت (parser).قدر;
			  إذا (! val
			      || val == error_mark_گرہ
			      || (! CONSTANT_CLASS_P (val)
				  && ! SSA_VAR_P (val)))
			    {
			      c_parser_error (parser, "invalid _Literal");
			      أرجع اظہاریہ;
			    }
			  CONSTRUCTOR_APPEND_ELT (v, NULL_درخت, val);
			  إذا (! CONSTANT_CLASS_P (val))
			    constant_p = خطأ;
			  إذا (c_parser_اگلا_token_is (parser, CPP_COMMA))
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
			اظہاریہ.قدر = build_سمتیہ_from_ctor (type, v);
		      وإلا
			اظہاریہ.قدر = build_constructor (type, v);
		    }
		  وإلا
		    {
		      c_parser_skip_until_لبھیا (parser, CPP_CLOSE_BRACE,
						 "expected %<}%>");
		      أرجع اظہاریہ;
		    }
		}
	      وإلا
		{
		  منطقي neg_p, addr_p;
		  إذا ((neg_p = c_parser_اگلا_token_is (parser, CPP_MINUS)))
		    c_parser_consume_token (parser);
		  إذا ((addr_p = c_parser_اگلا_token_is (parser, CPP_AND)))
		    c_parser_consume_token (parser);
		  درخت val = c_parser_gimple_postfix_عبارت (parser).قدر;
		  إذا (! val
		      || val == error_mark_گرہ
		      || (!CONSTANT_CLASS_P (val) && !addr_p))
		    {
		      c_parser_error (parser, "invalid _Literal");
		      أرجع اظہاریہ;
		    }
		  إذا (addr_p)
		    {
		      val = build1 (ADDR_اظہاریہ, type, val);
		      إذا (!is_gimple_invariant_پتہ (val))
			{
			  c_parser_error (parser, "invalid _Literal");
			  أرجع اظہاریہ;
			}
		    }
		  إذا (neg_p)
		    {
		      val = const_unop (NEGATE_اظہاریہ, درخت_TYPE (val), val);
		      إذا (! val)
			{
			  c_parser_error (parser, "invalid _Literal");
			  أرجع اظہاریہ;
			}
		    }
		  اظہاریہ.قدر = fold_convert (type, val);
		}
	      أرجع اظہاریہ;
	    }

	  /* SSA name.  */
	  بنانشانی نسخہ, ver_وتھ;
	  إذا (! lookup_name (id)
	      && c_parser_parse_ssa_name_id (id, &نسخہ, &ver_وتھ))
	    {
	      c_parser_consume_token (parser);
	      اظہاریہ.قدر = c_parser_parse_ssa_name (parser, id, NULL_درخت,
						    نسخہ, ver_وتھ);
	      إذا (اظہاریہ.قدر == error_mark_گرہ)
		أرجع اظہاریہ;
	      سیٹ_c_اظہاریہ_سروت_range (&اظہاریہ, tok_range);
	      /* For default definition SSA names.  */
	      إذا (c_parser_اگلا_token_is (parser, CPP_OPEN_PAREN)
		  && c_parser_peek_2nd_token (parser)->type == CPP_NAME
		  && strcmp ("D",
			     IDENTIFIER_اشارہ_گر
			       (c_parser_peek_2nd_token (parser)->قدر)) == 0
		  && c_parser_peek_nth_token (parser, 3)->type == CPP_CLOSE_PAREN)
		{
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		  إذا (! SSA_NAME_IS_DEFAULT_DEF (اظہاریہ.قدر))
		    {
		      إذا (!SSA_NAME_VAR (اظہاریہ.قدر))
			{
			  error_at (loc, "anonymous SSA name cannot have"
				    " default definition");
			  اظہاریہ.قدر = error_mark_گرہ;
			  أرجع اظہاریہ;
			}
		      سیٹ_ssa_default_def (cfun, SSA_NAME_VAR (اظہاریہ.قدر),
					   اظہاریہ.قدر);
		      SSA_NAME_DEF_STMT (اظہاریہ.قدر) = gimple_build_nop ();
		    }
		}
	    }
	  وإلا
	    {
	      c_parser_consume_token (parser);
	      اظہاریہ.قدر
		= build_external_ref (loc, id,
				      (c_parser_peek_token (parser)->type
				       == CPP_OPEN_PAREN), &اظہاریہ.original_type);
	      سیٹ_c_اظہاریہ_سروت_range (&اظہاریہ, tok_range);
	    }
	  اكسر;
	}
      /* Fallthru.  */
    افتراضي:
      c_parser_error (parser, "expected expression");
      اظہاریہ.سیٹ_error ();
      اكسر;
    }
  إذا (اظہاریہ.قدر == error_mark_گرہ)
    أرجع اظہاریہ;
  أرجع c_parser_gimple_postfix_عبارت_after_primary
    (parser, اظہاریہ_LOC_OR_LOC (اظہاریہ.قدر, loc), اظہاریہ);
}

/* Parse a gimple postfix expression after the initial primary or compound
   literal.  */

ساكن بنية c_اظہاریہ
c_parser_gimple_postfix_عبارت_after_primary (gimple_parser &parser,
						  location_t اظہاریہ_loc,
						  بنية c_اظہاریہ اظہاریہ)
{
  location_t شروع;
  location_t انت;
  درخت ident;
  location_t comp_loc;

  طالما (سچ)
    {
      location_t op_loc = c_parser_peek_token (parser)->location;
      بدل (c_parser_peek_token (parser)->type)
	{
	حالة CPP_OPEN_مربع:
	  {
	    c_parser_consume_token (parser);
	    درخت idx = c_parser_gimple_unary_عبارت (parser).قدر;

	    إذا (! c_parser_require (parser, CPP_CLOSE_مربع, "expected %<]%>"))
	      {
		c_parser_skip_until_لبھیا (parser, CPP_CLOSE_مربع, عدم);
		اكسر;
	      }

	    شروع = اظہاریہ.get_شروع ();
	    انت = c_parser_ٹوکن_buf (parser, 0)->location;
	    اظہاریہ.قدر = build_array_ref (op_loc, اظہاریہ.قدر, idx);
	    سیٹ_c_اظہاریہ_سروت_range (&اظہاریہ, شروع, انت);
	    اظہاریہ.m_decimal = 0;

	    اظہاریہ.original_کوڈ = ERROR_MARK;
	    اظہاریہ.original_type = عدم;
	    اكسر;
	  }
	حالة CPP_OPEN_PAREN:
	  {
	    /* Function call.  */
	    c_parser_consume_token (parser);
	    auto_vec<درخت> exprlist;
	    إذا (! c_parser_اگلا_token_is (parser, CPP_CLOSE_PAREN))
	      c_parser_gimple_اظہاریہ_list (parser, &exprlist);
	    c_parser_skip_until_لبھیا (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    إذا (!FUNC_OR_طریقہ_TYPE_P (درخت_TYPE (اظہاریہ.قدر)))
	      {
		c_parser_error (parser, "invalid call to non-function");
		اظہاریہ.سیٹ_error ();
		اكسر;
	      }
	    اظہاریہ.قدر = build_call_array_loc
		(اظہاریہ_loc, درخت_TYPE (درخت_TYPE (اظہاریہ.قدر)),
		 اظہاریہ.قدر, exprlist.لمائی (), exprlist.پتہ ());
	    اظہاریہ.m_decimal = 0;
	    اظہاریہ.original_کوڈ = ERROR_MARK;
	    اظہاریہ.original_type = عدم;
	    اكسر;
	  }
	حالة CPP_DOT:
	  {
	    /* Structure element reference.  */
	    c_parser_consume_token (parser);
	    إذا (c_parser_اگلا_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		ident = comp_tok->قدر;
		comp_loc = comp_tok->location;
	      }
	    وإلا
	      {
		c_parser_error (parser, "expected identifier");
		اظہاریہ.سیٹ_error ();
		اظہاریہ.original_کوڈ = ERROR_MARK;
		اظہاریہ.original_type = عدم;
		أرجع اظہاریہ;
	      }
	    شروع = اظہاریہ.get_شروع ();
	    انت = c_parser_peek_token (parser)->get_انت ();
	    c_parser_consume_token (parser);
	    اظہاریہ.قدر = build_component_ref (op_loc, اظہاریہ.قدر, ident,
					      comp_loc, UNKNOWN_LOCATION);
	    سیٹ_c_اظہاریہ_سروت_range (&اظہاریہ, شروع, انت);
	    اظہاریہ.m_decimal = 0;
	    اظہاریہ.original_کوڈ = ERROR_MARK;
	    إذا (درخت_کوڈ (اظہاریہ.قدر) != COMPONENT_REF)
	      اظہاریہ.original_type = عدم;
	    وإلا
	      {
		/* Remember the original type of a bitfield.  */
		درخت میدان_2 = درخت_عملیہ (اظہاریہ.قدر, 1);
		إذا (درخت_کوڈ (میدان_2) != میدان_DECL)
		  اظہاریہ.original_type = عدم;
		وإلا
		  اظہاریہ.original_type = DECL_ثنائی_ہندسہ_میدان_TYPE (میدان_2);
	      }
	    اكسر;
	  }
	حالة CPP_DEREF:
	  {
	    /* Structure element reference.  */
	    إذا (!اشارہ_گر_TYPE_P (درخت_TYPE (اظہاریہ.قدر)))
	      {
		c_parser_error (parser, "dereference of non-pointer");
		اظہاریہ.سیٹ_error ();
		اظہاریہ.original_کوڈ = ERROR_MARK;
		اظہاریہ.original_type = عدم;
		أرجع اظہاریہ;
	      }
	    c_parser_consume_token (parser);
	    إذا (c_parser_اگلا_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		ident = comp_tok->قدر;
		comp_loc = comp_tok->location;
	      }
	    وإلا
	      {
		c_parser_error (parser, "expected identifier");
		اظہاریہ.سیٹ_error ();
		اظہاریہ.original_کوڈ = ERROR_MARK;
		اظہاریہ.original_type = عدم;
		أرجع اظہاریہ;
	      }
	    شروع = اظہاریہ.get_شروع ();
	    انت = c_parser_peek_token (parser)->get_انت ();
	    c_parser_consume_token (parser);
	    اظہاریہ.قدر = build_component_ref (op_loc,
					      build_simple_mem_ref_loc
					        (op_loc, اظہاریہ.قدر),
					      ident, comp_loc,
					      اظہاریہ.get_location ());
	    سیٹ_c_اظہاریہ_سروت_range (&اظہاریہ, شروع, انت);
	    اظہاریہ.m_decimal = 0;
	    اظہاریہ.original_کوڈ = ERROR_MARK;
	    إذا (درخت_کوڈ (اظہاریہ.قدر) != COMPONENT_REF)
	      اظہاریہ.original_type = عدم;
	    وإلا
	      {
		/* Remember the original type of a bitfield.  */
		درخت میدان_2 = درخت_عملیہ (اظہاریہ.قدر, 1);
		إذا (درخت_کوڈ (میدان_2) != میدان_DECL)
		  اظہاریہ.original_type = عدم;
		وإلا
		  اظہاریہ.original_type = DECL_ثنائی_ہندسہ_میدان_TYPE (میدان_2);
	      }
	    اكسر;
	  }
	افتراضي:
	  أرجع اظہاریہ;
	}
    }
}

/* Parse expression list.

   gimple-expr-list:
     gimple-unary-expression
     gimple-expr-list , gimple-unary-expression

 */

ساكن فراغ
c_parser_gimple_اظہاریہ_list (gimple_parser &parser, vec<درخت> *ret)
{
  بنية c_اظہاریہ اظہاریہ;

  اظہاریہ = c_parser_gimple_unary_عبارت (parser);
  ret->محفوظ_ڈالو (اظہاریہ.قدر);
  طالما (c_parser_اگلا_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      اظہاریہ = c_parser_gimple_unary_عبارت (parser);
      ret->محفوظ_ڈالو (اظہاریہ.قدر);
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
  درخت name = c_parser_peek_token (parser)->قدر;
  location_t loc1 = c_parser_peek_token (parser)->location;
  gcc_assert (c_parser_اگلا_token_is (parser, CPP_NAME));
  c_parser_consume_token (parser);
  gcc_assert (c_parser_اگلا_token_is (parser, CPP_COLON));
  c_parser_consume_token (parser);
  درخت label = define_label (loc1, name);
  إذا (label)
    gimple_seq_جوڑو_stmt_without_update (seq, gimple_build_label (label));
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
  إذا (c_parser_اگلا_token_is_not (parser, CPP_OPEN_PAREN))
    أرجع;
  c_parser_consume_token (parser);

  specs->اندراج_bb_گنتی = profile_گنتی::uninitialized ();
  طالما (c_parser_اگلا_token_is (parser, CPP_NAME))
    {
      profile_quality quality;
      ثابت حرف *op = IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر);
      c_parser_consume_token (parser);
      إذا (! strcmp (op, "startwith"))
	{
	  إذا (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    أرجع;
	  إذا (c_parser_اگلا_token_is_not (parser, CPP_STRING))
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"expected pass name");
	      أرجع;
	    }
	  pass = xstrdup (درخت_STRING_اشارہ_گر
			  (c_parser_string_literal (parser, خطأ,
						    خطأ).قدر));
	  إذا (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<(%>"))
	    أرجع;
	}
      وإلا إذا (parse_profile_quality (op, &quality))
	{
	  درخت q;
	  إذا (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    أرجع;

	  إذا (!c_parser_اگلا_token_is (parser, CPP_نمبر)
	      || (درخت_کوڈ (q = c_parser_peek_token (parser)->قدر)
		  != INTEGER_CST))
	    {
	      c_parser_error (parser, "expected count value");
	      أرجع;
	    }

	  specs->اندراج_bb_گنتی
	    = profile_گنتی::from_gcov_type (درخت_INT_CST_کم (q), quality);
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
     إذا (c_parser_اگلا_token_is (parser, CPP_COMMA))
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
رجسٹر

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
  انت_declspecs (specs);

  /* Provide better error recovery.  Note that a type name here is usually
     better diagnosed as a redeclaration.  */
  إذا (c_parser_اگلا_token_starts_declspecs (parser)
      && ! c_parser_اگلا_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<;%>");
      c_parser_سیٹ_error (parser, خطأ);
      أرجع;
    }

  منطقي dummy = خطأ;
  declarator = c_parser_declarator (parser,
				    specs->typespec_قسم != ctsk_none,
				    C_DTR_عام, &dummy);

  إذا (!c_parser_اگلا_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_error (parser, "expected %<;%>");
      أرجع;
    }
  إذا (declarator)
    {
      /* Handle SSA name decls specially, they do not go into the identifier
         table but we simply build the SSA name for later lookup.  */
      بنانشانی نسخہ, ver_وتھ;
      /* Handle SSA pointer declarations in a very simplistic ways, we
	 probably would like to call grokdeclarator in a special mode to
	 just build the type of the decl - start_decl already pushes
	 the identifier to the bindings for lookup, something we do not
	 want.  */
      بنية c_declarator *id_declarator = declarator;
      طالما (id_declarator->قسم == cdk_اشارہ_گر)
	id_declarator = id_declarator->declarator;
      إذا (id_declarator->قسم == cdk_id
	  && (declarator->قسم == cdk_اشارہ_گر
	      || is_gimple_reg_type (specs->type))
	  && c_parser_parse_ssa_name_id (id_declarator->u.id.id,
					 &نسخہ, &ver_وتھ)
	  /* The following restricts it to unnamed anonymous SSA names
	     which fails parsing of named ones in dumps (we could
	     decide to not dump their name for -gimple).  */
	  && ver_وتھ == 0)
	{
	  بنية c_declarator *p = declarator;
	  درخت type = specs->type;
	  طالما (p->قسم == cdk_اشارہ_گر)
	    {
	      type = build_اشارہ_گر_type (type);
	      p = p->declarator;
	    }
	  c_parser_parse_ssa_name (parser, id_declarator->u.id.id, type,
				   نسخہ, ver_وتھ);
	}
      وإلا
	{
	  درخت postfix_attrs = NULL_درخت;
	  درخت all_اگیتر_attrs = specs->attrs;
	  specs->attrs = عدم;
	  درخت decl = شروع_decl (declarator, specs, خطأ,
				  chainon (postfix_attrs, all_اگیتر_attrs));
	  إذا (decl)
	    انت_decl (decl, UNKNOWN_LOCATION, NULL_درخت, NULL_درخت,
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
      صحيح dest_اشاریہ;
      profile_probability prob;
      إذا (c_parser_gimple_parse_bb_spec_کنارا_probability (label, parser,
							  &dest_اشاریہ, &prob))
	{
	  parser.ڈالو_کنارا (parser.current_bb->اشاریہ, dest_اشاریہ,
			    کنارا_FALLTHRU, prob);
	  أرجع;
	}
    }
  درخت decl = lookup_label_for_goto (loc, label);
  gimple_seq_جوڑو_stmt_without_update (seq, gimple_build_goto (decl));
}

/* Parse a parenthesized condition.
   gimple-condition:
     ( gimple-binary-expression )    */

ساكن درخت
c_parser_gimple_paren_condition (gimple_parser &parser)
{
  إذا (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    أرجع error_mark_گرہ;
  درخت cond
    = c_parser_gimple_ثنائی_عبارت (parser, boolean_type_گرہ).قدر;
  إذا (cond != error_mark_گرہ
      && ! COMPARISON_CLASS_P (cond)
      && ! CONSTANT_CLASS_P (cond)
      && ! SSA_VAR_P (cond))
    {
      c_parser_error (parser, "comparison required");
      cond = error_mark_گرہ;
    }
  إذا (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    أرجع error_mark_گرہ;
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

  إذا ((c_parser_اگلا_token_is (parser, CPP_KEYWORD)
       && c_parser_peek_token (parser)->keyword == RID_AT_FINALLY)
      || (c_parser_اگلا_token_is (parser, CPP_NAME)
	  && c_parser_peek_token (parser)->id_قسم == C_ID_ID
	  && strcmp (IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر),
		     "finally") == 0))
    {
      gimple_seq finseq = عدم;
      c_parser_consume_token (parser);
      c_parser_gimple_compound_statement (parser, &finseq);

      إذا (c_parser_اگلا_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_ELSE)
	{
	  gimple_seq elsseq = عدم;
	  c_parser_consume_token (parser);
	  c_parser_gimple_compound_statement (parser, &elsseq);

	  geh_else *stmt = gimple_build_eh_else (finseq, elsseq);
	  finseq = عدم;
	  gimple_seq_جوڑو_stmt_without_update (&finseq, stmt);
	}

      gtry *stmt = gimple_build_try (tryseq, finseq, GIMPLE_TRY_FINALLY);
      gimple_seq_جوڑو_stmt_without_update (seq, stmt);
    }
  وإلا إذا (c_parser_اگلا_token_is (parser, CPP_KEYWORD)
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

  إذا (c_parser_اگلا_token_is_keyword (parser, RID_GOTO))
    {
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      إذا (! c_parser_اگلا_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected label");
	  أرجع;
	}
      label = c_parser_peek_token (parser)->قدر;
      c_parser_consume_token (parser);
      صحيح dest_اشاریہ;
      profile_probability prob;
      إذا ((cfun->curr_properties & PROP_cfg)
	  && c_parser_gimple_parse_bb_spec_کنارا_probability (label, parser,
							     &dest_اشاریہ, &prob))
	parser.ڈالو_کنارا (parser.current_bb->اشاریہ, dest_اشاریہ,
			  کنارا_TRUE_قدر, prob);
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

  إذا (c_parser_اگلا_token_is_keyword (parser, RID_ELSE))
    c_parser_consume_token (parser);
  وإلا
    {
      c_parser_error (parser, "expected else statement");
      أرجع;
    }

  إذا (c_parser_اگلا_token_is_keyword (parser, RID_GOTO))
    {
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      إذا (! c_parser_اگلا_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected label");
	  أرجع;
	}
      label = c_parser_peek_token (parser)->قدر;
      c_parser_consume_token (parser);
      صحيح dest_اشاریہ;
      profile_probability prob;
      إذا ((cfun->curr_properties & PROP_cfg)
	  && c_parser_gimple_parse_bb_spec_کنارا_probability (label, parser,
							     &dest_اشاریہ, &prob))
	parser.ڈالو_کنارا (parser.current_bb->اشاریہ, dest_اشاریہ,
			  کنارا_FALSE_قدر, prob);
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

  إذا (cond != error_mark_گرہ)
    gimple_seq_جوڑو_stmt_without_update (seq, gimple_build_cond_from_درخت (cond, t_label,
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
  c_اظہاریہ cond_اظہاریہ;
  درخت case_label, label;
  auto_vec<درخت> labels;
  درخت default_label = NULL_درخت;
  c_parser_consume_token (parser);

  إذا (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    أرجع;
  cond_اظہاریہ = c_parser_gimple_postfix_عبارت (parser);
  إذا (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    أرجع;

  إذا (! c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    أرجع;

  طالما (c_parser_اگلا_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      إذا (c_parser_اگلا_token_is (parser, CPP_EOF))
	{
	  c_parser_error (parser, "expected statement");
	  أرجع;
	}

      بدل (c_parser_peek_token (parser)->keyword)
	{
	حالة RID_CASE:
	  {
	    c_اظہاریہ exp1;
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);

	    إذا (c_parser_اگلا_token_is (parser, CPP_NAME)
		|| c_parser_peek_token (parser)->type == CPP_نمبر)
	      exp1 = c_parser_gimple_postfix_عبارت (parser);
	    وإلا
	      {
		c_parser_error (parser, "expected expression");
		أرجع;
	      }

	    إذا (c_parser_اگلا_token_is (parser, CPP_COLON))
	      {
		c_parser_consume_token (parser);
		إذا (c_parser_اگلا_token_is (parser, CPP_NAME))
		  {
		    label = c_parser_peek_token (parser)->قدر;
		    c_parser_consume_token (parser);
		    درخت decl = lookup_label_for_goto (loc, label);
		    case_label = build_case_label (exp1.قدر, NULL_درخت,
						   decl);
		    labels.محفوظ_ڈالو (case_label);
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
	    إذا (c_parser_اگلا_token_is (parser, CPP_COLON))
	      {
		c_parser_consume_token (parser);
		إذا (c_parser_اگلا_token_is (parser, CPP_NAME))
		  {
		    label = c_parser_peek_token (parser)->قدر;
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

  إذا (cond_اظہاریہ.قدر != error_mark_گرہ)
    {
      gswitch *s = gimple_build_switch (cond_اظہاریہ.قدر, default_label, labels);
      gimple_seq_جوڑو_stmt_without_update (seq, s);
    }
}

/* Parse gimple return statement.  */

ساكن فراغ
c_parser_gimple_return_stmt (gimple_parser &parser, gimple_seq *seq)
{
  location_t loc = c_parser_peek_token (parser)->location;
  gimple *ret = عدم;
  c_parser_consume_token (parser);
  إذا (c_parser_اگلا_token_is (parser, CPP_SEMICOLON))
    {
      c_انت_gimple_return (loc, NULL_درخت);
      ret = gimple_build_return (عدم);
      gimple_seq_جوڑو_stmt_without_update (seq, ret);
    }
  وإلا
    {
      location_t xloc = c_parser_peek_token (parser)->location;
      c_اظہاریہ اظہاریہ = c_parser_gimple_unary_عبارت (parser);
      إذا (اظہاریہ.قدر != error_mark_گرہ)
	{
	  c_انت_gimple_return (xloc, اظہاریہ.قدر);
	  ret = gimple_build_return (اظہاریہ.قدر);
	  gimple_seq_جوڑو_stmt_without_update (seq, ret);
	}
    }
}

/* Support function for c_parser_gimple_return_stmt.  */

ساكن فراغ
c_انت_gimple_return (location_t loc, درخت retval)
{
  درخت valtype = درخت_TYPE (درخت_TYPE (current_function_decl));

  /* Use the expansion point to handle cases such as returning NULL
     in a function returning void.  */
  location_t xloc = expansion_نقطہ_location_if_وچ_system_سرخی (loc);

  إذا (درخت_THIS_VOLATILE (current_function_decl))
    warning_at (xloc, 0,
		"function declared %<noreturn%> has a %<return%> statement");

  إذا (! retval)
    current_function_returns_null = 1;
  وإلا إذا (valtype == 0 || VOID_TYPE_P (valtype))
    {
      current_function_returns_null = 1;
      إذا (درخت_کوڈ (درخت_TYPE (retval)) != VOID_TYPE)
	{
	  error_at
	    (xloc, "%<return%> with a value, in function returning void");
	  inform (DECL_سروت_LOCATION (current_function_decl),
		  "declared here");
	}
    }
  وإلا إذا (درخت_کوڈ (valtype) != درخت_کوڈ (درخت_TYPE (retval)))
    {
      error_at
	(xloc, "invalid conversion in return statement");
      inform (DECL_سروت_LOCATION (current_function_decl),
	      "declared here");
    }
  أرجع;
}
