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

جماعت gimple_parser
{
عوامی:
  gimple_parser (c_parser *p) : parser (p), کنارے(), current_bb(تہی) {}
  /* c_parser is not visible here, use composition and fake inheritance
     via a conversion operator.  */
  عامل c_parser *() { واپس parser; }
  c_parser *parser;

  /* CFG build state.  */
  جماعت gimple_parser_کنارہ
  {
  عوامی:
    صحیح src;
    صحیح dest;
    صحیح flags;
    profile_probability probability;
  };
  auto_vec<gimple_parser_کنارہ> کنارے;
  basic_بلاک current_bb;

  خالی ڈالو_کنارہ (صحیح, صحیح, صحیح, profile_probability);
};

خالی
gimple_parser::ڈالو_کنارہ (صحیح src, صحیح dest, صحیح flags,
			  profile_probability prob)
{
  gimple_parser_کنارہ e;
  e.src = src;
  e.dest = dest;
  e.flags = flags;
  e.probability = prob;
  کنارے.محفوظ_ڈالو (e);
}


/* Gimple parsing functions.  */
ساکن منطقی c_parser_gimple_compound_statement (gimple_parser &, gimple_seq *);
ساکن خالی c_parser_gimple_label (gimple_parser &, gimple_seq *);
ساکن خالی c_parser_gimple_statement (gimple_parser &, gimple_seq *);
ساکن ساخت c_اظہاریہ c_parser_gimple_ثنائی_عبارت (gimple_parser &, درخت);
ساکن ساخت c_اظہاریہ c_parser_gimple_unary_عبارت (gimple_parser &);
ساکن ساخت c_اظہاریہ c_parser_gimple_postfix_عبارت
			(gimple_parser &, درخت = error_mark_گرہ);
ساکن ساخت c_اظہاریہ c_parser_gimple_postfix_عبارت_after_primary
			(gimple_parser &, location_t, ساخت c_اظہاریہ);
ساکن خالی c_parser_gimple_declaration (gimple_parser &);
ساکن خالی c_parser_gimple_goto_stmt (gimple_parser &, location_t,
				       درخت, gimple_seq *);
ساکن خالی c_parser_gimple_try_stmt (gimple_parser &, gimple_seq *);
ساکن خالی c_parser_gimple_if_stmt (gimple_parser &, gimple_seq *);
ساکن خالی c_parser_gimple_switch_stmt (gimple_parser &, gimple_seq *);
ساکن خالی c_parser_gimple_return_stmt (gimple_parser &, gimple_seq *);
ساکن خالی c_اختتام_gimple_return (location_t, درخت);
ساکن درخت c_parser_gimple_paren_condition (gimple_parser &);
ساکن خالی c_parser_gimple_اظہاریہ_list (gimple_parser &, vec<درخت> *);


/* Much like parser_build_unary_op, but avoid applying default conversions.  */

ساکن c_اظہاریہ
gimple_parser_build_unary_op (location_t loc,
			      شمار درخت_رمز_2 رمز, ساخت c_اظہاریہ arg)
{
  ساخت c_اظہاریہ نتیجہ;

  نتیجہ.original_رمز = رمز;
  نتیجہ.original_type = تہی;
  نتیجہ.m_decimal = 0;

  اگر (reject_gcc_builtin (arg.قدر))
    {
      نتیجہ.قدر = error_mark_گرہ;
    }
  ورنہ
    {
      نتیجہ.قدر = build_unary_op (loc, رمز, arg.قدر, سچ);

      اگر (درخت_حد_سے_تجاوز_P (نتیجہ.قدر) && !درخت_حد_سے_تجاوز_P (arg.قدر))
	حد_سے_تجاوز_warning (loc, نتیجہ.قدر, arg.قدر);
    }

  /* We are typically called when parsing a prefix token at LOC acting on
     ARG.  Reflect this by updating the source range of the result to
     start at LOC and end at the end of ARG.  */
  سیٹ_c_اظہاریہ_ماخذ_range (&نتیجہ,
			   loc, arg.get_اختتام ());

  واپس نتیجہ;
}

/* See if VAL is an identifier matching __BB<num> and return <num>
   in *INDEX.  */

ساکن منطقی
c_parser_gimple_parse_bb_spec (درخت val, صحیح *اشاریہ)
{
  اگر (!startswith (IDENTIFIER_اشارہ_گر (val), "__BB"))
    واپس جھوٹ;

  ثابت حرف *bb = IDENTIFIER_اشارہ_گر (val) + 4;
  اگر (! ISDIGIT (*bb))
    واپس جھوٹ;

  حرف *pend;
  errno = 0;
  ثابت غیرعلامتی طویل نمبر = strtoul (bb, &pend, 10);
  اگر (errno == ERANGE
      || *pend != '\0'
      || نمبر > زیادہ_سے_زیادہ_عدد)
    واپس جھوٹ;

  *اشاریہ = نمبر;
  واپس سچ;
}

/* See if VAL is an identifier matching __BB<num> and return <num>
   in *INDEX.  Return true if so and parse also FREQUENCY of
   the edge.  */


ساکن منطقی
c_parser_gimple_parse_bb_spec_کنارہ_probability (درخت val,
						gimple_parser &parser,
						صحیح *اشاریہ,
						profile_probability
						*probability)
{
  منطقی return_p = c_parser_gimple_parse_bb_spec (val, اشاریہ);
  اگر (return_p)
    {
      *probability = profile_probability::uninitialized ();
      /* Parse frequency if provided.  */
      اگر (c_parser_اگلا_token_is (parser, CPP_OPEN_PAREN))
	{
	  درخت f;
	  c_parser_consume_token (parser);
	  اگر (!c_parser_اگلا_token_is (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected frequency quality");
	      واپس جھوٹ;
	    }

	  profile_quality quality;
	  ثابت حرف *v
	    = IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر);
	  اگر (!parse_profile_quality (v, &quality))
	    {
	      c_parser_error (parser, "unknown profile quality");
	      واپس جھوٹ;
	    }

	  c_parser_consume_token (parser);
	  اگر (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    واپس جھوٹ;

	  اگر (!c_parser_اگلا_token_is (parser, CPP_نمبر)
	      || (درخت_رمز (f = c_parser_peek_token (parser)->قدر)
		  != INTEGER_CST))
	    {
	      c_parser_error (parser, "expected frequency value");
	      واپس جھوٹ;
	    }

	  غیرعلامتی صحیح قدر = درخت_INT_CST_کم (f);
	  *probability = profile_probability (قدر, quality);

	  c_parser_consume_token (parser);
	  اگر (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    واپس جھوٹ;

	  اگر (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    واپس جھوٹ;
	}

      واپس سچ;
    }

  واپس جھوٹ;

}

/* Parse the body of a function declaration marked with "__GIMPLE".  */

خالی
c_parser_parse_gimple_body (c_parser *cparser, حرف *gimple_pass,
			    شمار c_declspec_il cdil,
			    profile_گنتی اندراج_bb_گنتی)
{
  gimple_parser parser (cparser);
  gimple_seq seq = تہی;
  gimple_seq body = تہی;
  درخت stmt = ڈالو_stmt_list ();
  ڈالو_scope ();
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
  ورنہ
    {
      /* We have at least cdil_gimple_cfg.  */
      gimple_رجسٹر_cfg_hooks ();
      init_خالی_خانے_درخت_cfg ();
      parser.current_bb = اندراج_بلاک_PTR_FOR_FN (cfun);
      /* Initialize the bare loop structure - we are going to only
         mark headers and leave the rest to fixup.  */
      سیٹ_loops_for_fn (cfun, ggc_cleared_alloc<ساخت loops> ());
      init_loops_structure (cfun, loops_for_fn (cfun), 1);
      loops_state_سیٹ (cfun, LOOPS_NEED_FIXUP|LOOPS_MAY_HAVE_مضرب_LATCHES);
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
      gimple *ret = gimple_build_return (تہی);
      gimple_seq_جوڑو_stmt_without_update (&seq, ret);
    }

  درخت بلاک = نکالو_scope ();
  stmt = نکالو_stmt_list (stmt);
  stmt = c_build_bind_اظہاریہ (loc1, بلاک, stmt);

  بلاک = DECL_INITIAL (current_function_decl);
  بلاک_SUBBLOCKS (بلاک) = NULL_درخت;
  بلاک_CHAIN (بلاک) = NULL_درخت;
  درخت_ASM_WRITTEN (بلاک) = 1;

  اگر (cdil == cdil_gimple)
    {
      gbind *bind_stmt = gimple_build_bind (BIND_اظہاریہ_VARS (stmt), تہی,
					    BIND_اظہاریہ_بلاک (stmt));
      gimple_bind_سیٹ_body (bind_stmt, seq);
      gimple_seq_جوڑو_stmt_without_update (&body, bind_stmt);
      gimple_سیٹ_body (current_function_decl, body);
    }
  ورنہ
    {
      /* Control-flow and binds are lowered, record local decls.  */
      برائے (درخت var = BIND_اظہاریہ_VARS (stmt); var; var = DECL_CHAIN (var))
	اگر (VAR_P (var)
	    && !DECL_EXTERNAL (var))
	  {
	    جوڑو_local_decl (cfun, var);
	    /* When the middle-end re-gimplifies any expression we might
	       run into the assertion that we've seen the decl in a BIND.  */
	    اگر (!درخت_STATIC (var))
	      DECL_نظر_آیا_اندر_BIND_اظہاریہ_P (var) = 1;
	  }
      /* We have a CFG.  Build the edges.  */
      برائے (غیرعلامتی i = 0; i < parser.کنارے.لمبائی (); ++i)
	{
	  کنارہ e = make_کنارہ (BASIC_بلاک_FOR_FN (cfun, parser.کنارے[i].src),
			      BASIC_بلاک_FOR_FN (cfun, parser.کنارے[i].dest),
			      parser.کنارے[i].flags);
	  e->probability = parser.کنارے[i].probability;
	}
      /* Add edges for case labels.  */
      basic_بلاک bb;
      FOR_EACH_BB_FN (bb, cfun)
	اگر (کنارہ_گنتی (bb->succs) == 0)
	  {
	    اگر (gswitch *sw = محفوظ_dyn_cast <gswitch *> (*gsi_آخری_bb (bb)))
	      برائے (غیرعلامتی i = 0; i < gimple_switch_عدد_labels (sw); ++i)
		{
		  basic_بلاک label_bb = gimple_switch_label_bb (cfun, sw, i);
		  make_کنارہ (bb, label_bb, 0);
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
	      برائے (gsi = gsi_آغاز_bb (bb); !gsi_انتہا_p (gsi);)
		{
		  gimple *stmt = gsi_stmt (gsi);
		  اگر (!gimple_call_اندرونی_p (stmt, IFN_PHI))
		    توڑو;

		  gphi *phi = create_phi_گرہ (gimple_call_lhs (stmt), bb);
		  برائے (غیرعلامتی i = 0; i < gimple_call_عدد_دلائل (stmt); i += 2)
		    {
		      صحیح srcidx = درخت_INT_CST_کم (gimple_call_arg (stmt, i));
		      کنارہ e = ڈھونڈو_کنارہ (BASIC_بلاک_FOR_FN (cfun, srcidx), bb);
		      اگر (!e)
			c_parser_error (parser, "edge not found");
		      ورنہ
			جوڑو_phi_arg (phi, gimple_call_arg (stmt, i + 1), e,
				     UNKNOWN_LOCATION);
		    }
		  gsi_remove (&gsi, سچ);
		}
	      برائے (; !gsi_انتہا_p (gsi); gsi_اگلا (&gsi))
		update_stmt (gsi_stmt (gsi));
	    }
	  /* Fill SSA name gaps, putting them on the freelist and diagnose
	     SSA names without definition.  */
	  برائے (غیرعلامتی i = 1; i < عدد_ssa_نام; ++i)
	    اگر (!ssa_name (i))
	      {
		درخت name = make_ssa_name_fn (cfun, integer_type_گرہ, تہی, i);
		release_ssa_name_fn (cfun, name);
	      }
	    ورنہ اگر (!SSA_NAME_DEF_STMT (ssa_name (i)))
	      error ("SSA name %qE with version %d has no definition",
		     ssa_name (i), i);
	  /* No explicit virtual operands (yet).  */
	  bitmap_obstack_initialize (تہی);
	  update_ssa (TODO_update_ssa_only_virtuals);
	  bitmap_obstack_release (تہی);
	  /* ???  By flushing the freelist after virtual operand SSA rewrite
	     we keep the gaps available for re-use like needed for the
	     PR89595 testcase but then usually virtual operands would have
	     taken most of them.  The fix is obviously to make virtual
	     operands explicit in the SSA IL.  */
	  flush_ssaname_freelist ();
	}
      fix_loop_structure (تہی);
    }

  اگر (cfun->curr_properties & PROP_cfg)
    {
      اندراج_بلاک_PTR_FOR_FN (cfun)->گنتی = اندراج_bb_گنتی;
      gcov_type t = param_gimple_fe_computed_hot_bb_حد;
      سیٹ_hot_bb_حد (t);
      update_max_bb_گنتی ();
      cgraph_گرہ::get_create (cfun->decl);
      cgraph_کنارہ::rebuild_کنارے ();
    }

  /* Perform IL validation and if any error is found abort compilation
     of this function by zapping its body.  */
  اگر ((cfun->curr_properties & PROP_cfg)
      && verify_gimple_اندر_cfg (cfun, جھوٹ, جھوٹ))
    init_خالی_خانے_درخت_cfg ();
  ورنہ اگر (!(cfun->curr_properties & PROP_cfg)
	   && verify_gimple_اندر_seq (gimple_body (current_function_decl), جھوٹ))
    gimple_سیٹ_body (current_function_decl, تہی);

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

ساکن منطقی
c_parser_gimple_compound_statement (gimple_parser &parser, gimple_seq *seq)
{
  منطقی return_p = جھوٹ;

  اگر (! c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    واپس جھوٹ;

  /* A compound statement starts with optional declarations.  */
  جب (c_parser_اگلا_علامات_آغاز_declaration (parser))
    {
      c_parser_gimple_declaration (parser);
      اگر (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	واپس جھوٹ;
    }

  جب (c_parser_اگلا_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      اگر (c_parser_error (parser))
	{
	  c_parser_skip_until_ملا (parser, CPP_CLOSE_BRACE, تہی);
	  واپس return_p;
	}
      ورنہ اگر (c_parser_اگلا_token_is (parser, CPP_EOF))
	{
	  c_parser_error (parser, "expected declaration or statement");
	  واپس return_p;
	}

      انتخاب (c_parser_peek_token (parser)->type)
	{
	حالت CPP_KEYWORD:
	  انتخاب (c_parser_peek_token (parser)->keyword)
	    {
	    حالت RID_AT_TRY:
	      c_parser_gimple_try_stmt (parser, seq);
	      توڑو;
	    حالت RID_IF:
	      c_parser_gimple_if_stmt (parser, seq);
	      توڑو;
	    حالت RID_SWITCH:
	      c_parser_gimple_switch_stmt (parser, seq);
	      توڑو;
	    حالت RID_GOTO:
	      {
		location_t loc = c_parser_peek_token (parser)->location;
		c_parser_consume_token (parser);
		اگر (c_parser_اگلا_token_is (parser, CPP_NAME))
		  {
		    درخت label = c_parser_peek_token (parser)->قدر;
		    c_parser_consume_token (parser);
		    c_parser_gimple_goto_stmt (parser, loc, label, seq);
		    اگر (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      واپس return_p;
		  }
		}
	      توڑو;
	    حالت RID_RETURN:
	      return_p = سچ;
	      c_parser_gimple_return_stmt (parser, seq);
	      اگر (! c_parser_require (parser, CPP_SEMICOLON,
				      "expected %<;%>"))
		واپس return_p;
	      اگر (cfun->curr_properties & PROP_cfg)
		parser.ڈالو_کنارہ (parser.current_bb->اشاریہ, EXIT_بلاک, 0,
				  profile_probability::uninitialized ());
	      توڑو;
	    طےشدہ:
	      جاؤ اظہاریہ_stmt;
	    }
	  توڑو;
	حالت CPP_NAME:
	  اگر (c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_gimple_label (parser, seq);
	      توڑو;
	    }
	  اگر (c_parser_اگلا_token_is (parser, CPP_NAME)
	      && c_parser_peek_token (parser)->id_قسم == C_ID_ID
	      && strcmp (IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر),
			 "try") == 0)
	    {
	      c_parser_gimple_try_stmt (parser, seq);
	      توڑو;
	    }
	  /* Basic block specification.
	     __BB (index, ...)  */
	  اگر ((cfun->curr_properties & PROP_cfg)
	      && !strcmp (IDENTIFIER_اشارہ_گر
			    (c_parser_peek_token (parser)->قدر), "__BB"))
	    {
	      c_parser_consume_token (parser);
	      اگر (! c_parser_require (parser, CPP_OPEN_PAREN,
				      "expected %<(%>"))
		واپس return_p;
	      اگر (c_parser_اگلا_token_is_not (parser, CPP_نمبر))
		{
		  c_parser_error (parser, "expected block index");
		  واپس return_p;
		}
	      درخت tnum = c_parser_peek_token (parser)->قدر;
	      اگر (درخت_رمز (tnum) != INTEGER_CST)
		{
		  c_parser_error (parser, "expected block index");
		  واپس return_p;
		}
	      صحیح اشاریہ = درخت_INT_CST_کم (tnum);
	      اگر (اشاریہ < عدد_FIXED_بلاکیں
		  || (اشاریہ < آخری_basic_بلاک_for_fn (cfun)
		      && BASIC_بلاک_FOR_FN (cfun, اشاریہ) != تہی))
		{
		  c_parser_error (parser, "invalid block index");
		  واپس return_p;
		}
	      صحیح is_loop_سرخی_کا = -1;
	      profile_گنتی bb_گنتی = profile_گنتی::uninitialized ();
	      c_parser_consume_token (parser);
	      جب (c_parser_اگلا_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  اگر (! c_parser_اگلا_token_is (parser, CPP_NAME))
		    {
		      c_parser_error (parser, "expected block specifier");
		      واپس return_p;
		    }
		  /* loop_header (NUM)  */
		  اگر (!strcmp (IDENTIFIER_اشارہ_گر
			         (c_parser_peek_token (parser)->قدر),
			       "loop_header"))
		    {
		      c_parser_consume_token (parser);
		      اگر (! c_parser_require (parser, CPP_OPEN_PAREN,
					      "expected %<(%>"))
			واپس return_p;
		      درخت loop_عدد;
		      اگر (! c_parser_اگلا_token_is (parser, CPP_نمبر)
			  || درخت_رمز (loop_عدد
					  = c_parser_peek_token (parser)->قدر)
			       != INTEGER_CST)
			{
			  c_parser_error (parser, "expected loop number");
			  واپس return_p;
			}
		      c_parser_consume_token (parser);
		      is_loop_سرخی_کا = درخت_INT_CST_کم (loop_عدد);
		      اگر (! c_parser_require (parser, CPP_CLOSE_PAREN,
					      "expected %<)%>"))
			واپس return_p;
		    }
		  /* Parse profile: quality(value) */
		  ورنہ
		    {
		      درخت q;
		      profile_quality quality;
		      درخت v = c_parser_peek_token (parser)->قدر;
		      اگر (!parse_profile_quality (IDENTIFIER_اشارہ_گر (v),
						  &quality))
			{
			  c_parser_error (parser, "unknown block specifier");
			  واپس جھوٹ;
			}

		      c_parser_consume_token (parser);
		      اگر (!c_parser_require (parser, CPP_OPEN_PAREN,
					     "expected %<(%>"))
			واپس جھوٹ;

		      اگر (!c_parser_اگلا_token_is (parser, CPP_نمبر)
			  || (درخت_رمز (q = c_parser_peek_token (parser)->قدر)
			      != INTEGER_CST))
			{
			  c_parser_error (parser, "expected count value");
			  واپس جھوٹ;
			}

		      bb_گنتی
			= profile_گنتی::from_gcov_type (درخت_INT_CST_کم (q),
							 quality);
		      c_parser_consume_token (parser);
		      اگر (! c_parser_require (parser, CPP_CLOSE_PAREN,
					      "expected %<)%>"))
			واپس return_p;
		    }
		}
	      اگر (! c_parser_require (parser, CPP_CLOSE_PAREN,
				      "expected %<)%>")
		  || ! c_parser_require (parser, CPP_COLON,
					 "expected %<:%>"))
		واپس return_p;

	      /* Put stmts parsed in the current block.  */
	      اگر (!gimple_seq_خالی_خانے_p (*seq))
		{
		  اگر (!parser.current_bb)
		    c_parser_error (parser, "stmts without block");
		  ورنہ
		    {
		      gimple_stmt_iterator gsi
			= gsi_آغاز_bb (parser.current_bb);
		      gsi_داخل_کرو_seq_after_without_update (&gsi, *seq,
							   GSI_CONTINUE_LINKING);
		    }
		  *seq = تہی;
		}

	      /* Build an empty block with specified index, linking them
		 in source order.  */
	      basic_بلاک bb = alloc_بلاک ();
	      bb->اشاریہ = اشاریہ;
	      link_بلاک (bb, (parser.current_bb ? parser.current_bb
			       : اندراج_بلاک_PTR_FOR_FN (cfun)));
	      اگر (basic_بلاک_info_for_fn (cfun)->لمبائی () <= (سائز_t)اشاریہ)
		vec_محفوظ_grow_cleared (basic_بلاک_info_for_fn (cfun),
				       اشاریہ + 1, سچ);
	      سیٹ_BASIC_بلاک_FOR_FN (cfun, اشاریہ, bb);
	      اگر (آخری_basic_بلاک_for_fn (cfun) <= اشاریہ)
		آخری_basic_بلاک_for_fn (cfun) = اشاریہ + 1;
	      n_basic_بلاکیں_for_fn (cfun)++;
	      اگر (parser.current_bb->اشاریہ == اندراج_بلاک)
		parser.ڈالو_کنارہ (اندراج_بلاک, bb->اشاریہ, کنارہ_FALLTHRU,
				  profile_probability::always ());

	      /* We leave the proper setting to fixup.  */
	      جماعت loop *loop_father = loops_for_fn (cfun)->درخت_جڑ;
	      /* If the new block is a loop header, allocate a loop
		 struct.  Fixup will take care of proper placement within
		 the loop tree.  */
	      اگر (is_loop_سرخی_کا != -1)
		{
		  اگر (نمبر_کا_loops (cfun) > (غیرعلامتی)is_loop_سرخی_کا
		      && get_loop (cfun, is_loop_سرخی_کا) != تہی)
		    {
		      c_parser_error (parser, "duplicate loop header");
		    }
		  ورنہ
		    {
		      جماعت loop *loop = alloc_loop ();
		      loop->عدد = is_loop_سرخی_کا;
		      loop->سرخی = bb;
		      اگر (نمبر_کا_loops (cfun) <= (غیرعلامتی)is_loop_سرخی_کا)
			vec_محفوظ_grow_cleared (loops_for_fn (cfun)->larray,
					       is_loop_سرخی_کا + 1, سچ);
		      (*loops_for_fn (cfun)->larray)[is_loop_سرخی_کا] = loop;
		      flow_loop_درخت_گرہ_جوڑو (loops_for_fn (cfun)->درخت_جڑ,
					       loop);
		    }
		  loop_father = get_loop (cfun, is_loop_سرخی_کا);
		}
	      bb->loop_father = loop_father;
	      bb->گنتی = bb_گنتی;

	      /* Stmts now go to the new block.  */
	      parser.current_bb = bb;
	      توڑو;
	    }
	  جاؤ اظہاریہ_stmt;

	حالت CPP_SEMICOLON:
	  {
	    /* Empty stmt.  */
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);
	    gimple *nop = gimple_build_nop ();
	    gimple_سیٹ_location (nop, loc);
	    gimple_seq_جوڑو_stmt_without_update (seq, nop);
	    توڑو;
	  }

	حالت CPP_CLOSE_PAREN:
	حالت CPP_CLOSE_مربع:
	  /* Avoid infinite loop in error recovery:
	     c_parser_skip_until_found stops at a closing nesting
	     delimiter without consuming it, but here we need to consume
	     it to proceed further.  */
	  c_parser_error (parser, "expected statement");
	  c_parser_consume_token (parser);
	توڑو;

	طےشدہ:
اظہاریہ_stmt:
	  c_parser_gimple_statement (parser, seq);
	  اگر (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	    c_parser_skip_until_ملا (parser, CPP_SEMICOLON, تہی);
	}
    }
  c_parser_consume_token (parser);

  /* Put stmts parsed in the current block.  */
  اگر ((cfun->curr_properties & PROP_cfg)
      && !gimple_seq_خالی_خانے_p (*seq))
    {
      اگر (!parser.current_bb)
	c_parser_error (parser, "stmts without block");
      ورنہ
	{
	  gimple_stmt_iterator gsi = gsi_آغاز_bb (parser.current_bb);
	  gsi_داخل_کرو_seq_after_without_update (&gsi, *seq,
					       GSI_CONTINUE_LINKING);
	}
      *seq = تہی;
    }

  واپس return_p;
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

ساکن خالی
c_parser_gimple_statement (gimple_parser &parser, gimple_seq *seq)
{
  ساخت c_اظہاریہ lhs, rhs;
  gimple *تفویض = تہی;
  location_t loc;
  درخت arg = NULL_درخت;
  auto_vec<درخت> vargs;

  lhs = c_parser_gimple_unary_عبارت (parser);
  loc = اظہاریہ_LOCATION (lhs.قدر);
  rhs.سیٹ_error ();

  /* GIMPLE call statement without LHS.  */
  اگر (c_parser_اگلا_token_is (parser, CPP_SEMICOLON)
      && درخت_رمز (lhs.قدر) == CALL_اظہاریہ)
    {
      gimple *call;
      call = gimple_build_call_from_درخت (lhs.قدر, تہی);
      gimple_seq_جوڑو_stmt_without_update (seq, call);
      gimple_سیٹ_location (call, loc);
      واپس;
    }

  /* All following cases are statements with LHS.  */
  اگر (! c_parser_require (parser, CPP_EQ, "expected %<=%>"))
    واپس;

  /* Eat and ignore {v} right after the =, the has_volatile_ops is
     redundant and re-computed by the operand scanner.  */
  اگر (c_parser_اگلا_token_is (parser, CPP_OPEN_BRACE)
      && !(c_parser_peek_token (parser)->flags & پچھلا_WHITE)
      && c_parser_peek_2nd_token (parser)->type == CPP_NAME
      && !(c_parser_peek_2nd_token (parser)->flags & پچھلا_WHITE)
      && strcmp ("v", IDENTIFIER_اشارہ_گر
			(c_parser_peek_2nd_token (parser)->قدر)) == 0
      && c_parser_peek_nth_token (parser, 3)->type == CPP_CLOSE_BRACE
      && !(c_parser_peek_nth_token (parser, 3)->flags & پچھلا_WHITE))
    {
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }

  /* Cast expression.  */
  اگر (c_parser_اگلا_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_typename (c_parser_peek_2nd_token (parser)))
    {
      c_parser_consume_token (parser);
      ساخت c_type_name *type_name = c_parser_type_name (parser);
      c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      اگر (type_name == تہی)
	واپس;
      /* ???  The actual type used in the cast expression is ignored as
         in GIMPLE it is encoded by the type of the LHS.  */
      rhs = c_parser_gimple_postfix_عبارت (parser);
      اگر (lhs.قدر != error_mark_گرہ
	  && rhs.قدر != error_mark_گرہ)
	{
	  شمار درخت_رمز_2 رمز = NOP_اظہاریہ;
	  اگر (FLOAT_TYPE_P (درخت_TYPE (lhs.قدر))
	      && ! FLOAT_TYPE_P (درخت_TYPE (rhs.قدر)))
	    رمز = FLOAT_اظہاریہ;
	  ورنہ اگر (! FLOAT_TYPE_P (درخت_TYPE (lhs.قدر))
		   && FLOAT_TYPE_P (درخت_TYPE (rhs.قدر)))
	    رمز = FIX_TRUNC_اظہاریہ;
	  تفویض = gimple_build_تفویض (lhs.قدر, رمز, rhs.قدر);
	  gimple_seq_جوڑو_stmt_without_update (seq, تفویض);
	  gimple_سیٹ_location (تفویض, loc);
	  واپس;
	}
    }

  /* Unary expression.  */
  انتخاب (c_parser_peek_token (parser)->type)
    {
    حالت CPP_NAME:
      {
	درخت id = c_parser_peek_token (parser)->قدر;
	اگر (strcmp (IDENTIFIER_اشارہ_گر (id), "__ABS") == 0
	    || strcmp (IDENTIFIER_اشارہ_گر (id), "__ABSU") == 0
	    || strcmp (IDENTIFIER_اشارہ_گر (id), "__MIN") == 0
	    || strcmp (IDENTIFIER_اشارہ_گر (id), "__MAX") == 0
	    || strcmp (IDENTIFIER_اشارہ_گر (id), "__BIT_INSERT") == 0
	    || strcmp (IDENTIFIER_اشارہ_گر (id), "__VEC_PERM") == 0)
	  جاؤ build_unary_اظہاریہ;
	توڑو;
      }
    حالت CPP_KEYWORD:
      اگر (c_parser_peek_token (parser)->keyword != RID_REALPART
	  && c_parser_peek_token (parser)->keyword != RID_IMAGPART)
	توڑو;
      /* Fallthru.  */
    حالت CPP_AND:
    حالت CPP_PLUS:
    حالت CPP_MINUS:
    حالت CPP_COMPL:
    حالت CPP_NOT:
    حالت CPP_MULT: /* pointer deref */
    build_unary_اظہاریہ:
      rhs = c_parser_gimple_unary_عبارت (parser);
      اگر (rhs.قدر != error_mark_گرہ)
	{
	  تفویض = gimple_build_تفویض (lhs.قدر, rhs.قدر);
	  gimple_سیٹ_location (تفویض, loc);
	  gimple_seq_جوڑو_stmt_without_update (seq, تفویض);
	}
      واپس;

    طےشدہ:;
    }

  /* GIMPLE PHI statement.  */
  اگر (c_parser_اگلا_token_is_keyword (parser, RID_PHI))
    {
      c_parser_consume_token (parser);

      اگر (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	واپس;

      اگر (c_parser_اگلا_token_is (parser, CPP_OPEN_PAREN))
	c_parser_consume_token (parser);

      جب (c_parser_اگلا_token_is_not (parser, CPP_CLOSE_PAREN))
	{
	  اگر (c_parser_اگلا_token_is (parser, CPP_NAME)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      arg = c_parser_peek_token (parser)->قدر;
	      c_parser_consume_token (parser);
	      اگر (c_parser_اگلا_token_is (parser, CPP_COLON))
		c_parser_consume_token (parser);
	      صحیح src_اشاریہ = -1;
	      اگر (!c_parser_gimple_parse_bb_spec (arg, &src_اشاریہ))
		c_parser_error (parser, "invalid source block specification");
	      vargs.محفوظ_ڈالو (سائز_int (src_اشاریہ));
	    }
	  ورنہ اگر (c_parser_اگلا_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  ورنہ
	    {
	      arg = c_parser_gimple_unary_عبارت (parser).قدر;
	      vargs.محفوظ_ڈالو (arg);
	    }
	}

      c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");

      /* Build internal function for PHI.  */
      gcall *call_stmt = gimple_build_call_اندرونی_vec (IFN_PHI, vargs);
      gimple_call_سیٹ_lhs (call_stmt, lhs.قدر);
      gimple_سیٹ_location (call_stmt, UNKNOWN_LOCATION);
      gimple_seq_جوڑو_stmt_without_update (seq, call_stmt);
      واپس;
    }

  /* GIMPLE call with lhs.  */
  اگر (c_parser_اگلا_token_is (parser, CPP_DOT)
      || (c_parser_اگلا_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN
	  && lookup_name (c_parser_peek_token (parser)->قدر)))
    {
      rhs = c_parser_gimple_unary_عبارت (parser);
      اگر (rhs.قدر != error_mark_گرہ)
	{
	  gimple *call = gimple_build_call_from_درخت (rhs.قدر, تہی);
	  gimple_call_سیٹ_lhs (call, lhs.قدر);
	  gimple_seq_جوڑو_stmt_without_update (seq, call);
	  gimple_سیٹ_location (call, loc);
	}
      واپس;
    }

  rhs = c_parser_gimple_ثنائی_عبارت (parser, درخت_TYPE (lhs.قدر));
  اگر (lhs.قدر != error_mark_گرہ
      && rhs.قدر != error_mark_گرہ)
    {
      /* If we parsed an identifier and the next token  is a '?' then parse
	 a conditional expression.  */
      اگر (SSA_VAR_P (rhs.قدر) && c_parser_اگلا_token_is (parser, CPP_QUERY))
	{
	  ساخت c_اظہاریہ trueval, falseval;
	  c_parser_consume_token (parser);
	  trueval = c_parser_gimple_postfix_عبارت (parser);
	  falseval.سیٹ_error ();
	  اگر (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    falseval = c_parser_gimple_postfix_عبارت (parser);
	  اگر (trueval.قدر == error_mark_گرہ
	      || falseval.قدر == error_mark_گرہ)
	    واپس;
	  rhs.قدر = build3_loc (loc,
				  سمتیہ_TYPE_P (درخت_TYPE (rhs.قدر))
				  ? VEC_COND_اظہاریہ : COND_اظہاریہ,
				  درخت_TYPE (trueval.قدر),
				  rhs.قدر, trueval.قدر, falseval.قدر);
	}
      اگر (get_gimple_rhs_class (درخت_رمز (rhs.قدر)) == GIMPLE_INVALID_RHS)
	{
	  c_parser_error (parser, "unexpected RHS for assignment");
	  واپس;
	}
      تفویض = gimple_build_تفویض (lhs.قدر, rhs.قدر);
      gimple_seq_جوڑو_stmt_without_update (seq, تفویض);
      gimple_سیٹ_location (تفویض, loc);
    }
  واپس;
}

/* A mapping between an identifier to a tree code for binary operations. */
ساکن ثابت std::pair<ثابت حرف *, درخت_رمز_2> gimple_ثنائی_identifier_رمز[] =
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
    {"__ROUND_DIV", باری_DIV_اظہاریہ},
    {"__EXACT_DIV", EXACT_DIV_اظہاریہ},
    {"__CEIL_DIV", CEIL_DIV_اظہاریہ},
    {"__FLOOR_MOD", FLOOR_MOD_اظہاریہ},
    {"__ROUND_MOD", باری_MOD_اظہاریہ},
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

ساکن c_اظہاریہ
c_parser_gimple_ثنائی_عبارت (gimple_parser &parser, درخت ret_type)
{
  /* Location of the binary operator.  */
  ساخت c_اظہاریہ ret, lhs, rhs;
  شمار درخت_رمز_2 رمز = ERROR_MARK;
  ret.سیٹ_error ();
  lhs = c_parser_gimple_postfix_عبارت (parser, ret_type);
  اگر (c_parser_error (parser))
    واپس ret;
  انتخاب (c_parser_peek_token (parser)->type)
    {
    حالت CPP_MULT:
      رمز = MULT_اظہاریہ;
      توڑو;
    حالت CPP_DIV:
      رمز = TRUNC_DIV_اظہاریہ;
      توڑو;
    حالت CPP_MOD:
      رمز = TRUNC_MOD_اظہاریہ;
      توڑو;
    حالت CPP_PLUS:
      اگر (اشارہ_گر_TYPE_P (درخت_TYPE (lhs.قدر)))
	رمز = اشارہ_گر_PLUS_اظہاریہ;
      ورنہ
	رمز = PLUS_اظہاریہ;
      توڑو;
    حالت CPP_MINUS:
      اگر (اشارہ_گر_TYPE_P (درخت_TYPE (lhs.قدر)))
	رمز = اشارہ_گر_DIFF_اظہاریہ;
      ورنہ
	رمز = MINUS_اظہاریہ;
      توڑو;
    حالت CPP_LSHIFT:
      رمز = LSHIFT_اظہاریہ;
      توڑو;
    حالت CPP_RSHIFT:
      رمز = RSHIFT_اظہاریہ;
      توڑو;
    حالت CPP_LESS:
      رمز = LT_اظہاریہ;
      توڑو;
    حالت CPP_GREATER:
      رمز = GT_اظہاریہ;
      توڑو;
    حالت CPP_LESS_EQ:
      رمز = LE_اظہاریہ;
      توڑو;
    حالت CPP_GREATER_EQ:
      رمز = GE_اظہاریہ;
      توڑو;
    حالت CPP_EQ_EQ:
      رمز = EQ_اظہاریہ;
      توڑو;
    حالت CPP_NOT_EQ:
      رمز = NE_اظہاریہ;
      توڑو;
    حالت CPP_AND:
      رمز = ثنائی_ہندسہ_AND_اظہاریہ;
      توڑو;
    حالت CPP_XOR:
      رمز = ثنائی_ہندسہ_XOR_اظہاریہ;
      توڑو;
    حالت CPP_OR:
      رمز = ثنائی_ہندسہ_IOR_اظہاریہ;
      توڑو;
    حالت CPP_AND_AND:
      c_parser_error (parser, "%<&&%> not valid in GIMPLE");
      واپس ret;
    حالت CPP_OR_OR:
      c_parser_error (parser, "%<||%> not valid in GIMPLE");
      واپس ret;
    حالت CPP_NAME:
      {
	درخت id = c_parser_peek_token (parser)->قدر;
	برائے (خودکار &p : gimple_ثنائی_identifier_رمز)
	  {
	    اگر (strcmp (IDENTIFIER_اشارہ_گر (id), p.پہلا) == 0)
	      {
		رمز = p.دوسرا;
		توڑو;
	      }
	  }
	اگر (رمز != ERROR_MARK)
	  توڑو;
      }
      /* Fallthru.  */
    طےشدہ:
      /* Not a binary expression.  */
      واپس lhs;
    }
  location_t ret_loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  rhs = c_parser_gimple_postfix_عبارت (parser);
  اگر (lhs.قدر != error_mark_گرہ && rhs.قدر != error_mark_گرہ)
    ret.قدر = build2_loc (ret_loc, رمز, ret_type, lhs.قدر, rhs.قدر);
  واپس ret;
}

/* Parse a gimple parentized binary expression.  */

ساکن c_اظہاریہ
c_parser_gimple_parentized_ثنائی_عبارت (gimple_parser &parser,
					      location_t op_loc,
					      درخت_رمز_2 رمز)
{
  ساخت c_اظہاریہ ret;
  ret.سیٹ_error ();

  c_parser_consume_token (parser);
  اگر (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    واپس ret;
  c_اظہاریہ op1 = c_parser_gimple_postfix_عبارت (parser);
  اگر (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    واپس ret;
  c_اظہاریہ op2 = c_parser_gimple_postfix_عبارت (parser);
  اگر (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    واپس ret;

  اگر (op1.قدر != error_mark_گرہ && op2.قدر != error_mark_گرہ)
    ret.قدر = build2_loc (op_loc,
			    رمز, درخت_TYPE (op1.قدر), op1.قدر, op2.قدر);
  واپس ret;
}

/* Parse a gimple parentized binary expression.  */

ساکن c_اظہاریہ
c_parser_gimple_parentized_ternary_عبارت (gimple_parser &parser,
					       location_t op_loc,
					       درخت_رمز_2 رمز)
{
  ساخت c_اظہاریہ ret;
  ret.سیٹ_error ();

  c_parser_consume_token (parser);
  اگر (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    واپس ret;
  c_اظہاریہ op1 = c_parser_gimple_postfix_عبارت (parser);
  اگر (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    واپس ret;
  c_اظہاریہ op2 = c_parser_gimple_postfix_عبارت (parser);
  اگر (!c_parser_require (parser, CPP_COMMA, "expected %<)%>"))
    واپس ret;
  c_اظہاریہ op3 = c_parser_gimple_postfix_عبارت (parser);
  اگر (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    واپس ret;

  اگر (op1.قدر != error_mark_گرہ
      && op2.قدر != error_mark_گرہ
      && op3.قدر != error_mark_گرہ)
    ret.قدر = build3_loc (op_loc,
			    رمز, درخت_TYPE (op1.قدر),
			    op1.قدر, op2.قدر, op3.قدر);
  واپس ret;
}

/* Parse gimple unary expression.

   gimple-unary-expression:
     gimple-postfix-expression
     unary-operator gimple-postfix-expression

   unary-operator: one of
     & * + - ~ abs_expr
*/

ساکن c_اظہاریہ
c_parser_gimple_unary_عبارت (gimple_parser &parser)
{
  ساخت c_اظہاریہ ret, op;
  location_t op_loc = c_parser_peek_token (parser)->location;
  location_t اختتام;
  ret.سیٹ_error ();
  انتخاب (c_parser_peek_token (parser)->type)
    {
    حالت CPP_AND:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_عبارت (parser);
      mark_exp_read (op.قدر);
      واپس gimple_parser_build_unary_op (op_loc, ADDR_اظہاریہ, op);
    حالت CPP_MULT:
      {
	c_parser_consume_token (parser);
	op = c_parser_gimple_postfix_عبارت (parser);
	اگر (op.قدر == error_mark_گرہ)
	  واپس ret;
	اگر (! اشارہ_گر_TYPE_P (درخت_TYPE (op.قدر)))
	  {
	    error_at (op_loc, "expected pointer as argument of unary %<*%>");
	    واپس ret;
	  }
	اختتام = op.get_اختتام ();
	location_t combined_loc = make_location (op_loc, op_loc, اختتام);
	ret.قدر = build_simple_mem_ref_loc (combined_loc, op.قدر);
	درخت_SIDE_EFFECTS (ret.قدر)
	  = درخت_THIS_VOLATILE (ret.قدر)
	  = TYPE_VOLATILE (درخت_TYPE (درخت_TYPE (op.قدر)));
	ret.src_range.m_آغاز = op_loc;
	ret.src_range.m_اختتام = اختتام;
	واپس ret;
      }
    حالت CPP_PLUS:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_عبارت (parser);
      واپس gimple_parser_build_unary_op (op_loc, CONVERT_اظہاریہ, op);
    حالت CPP_MINUS:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_عبارت (parser);
      واپس gimple_parser_build_unary_op (op_loc, NEGATE_اظہاریہ, op);
    حالت CPP_COMPL:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_عبارت (parser);
      واپس gimple_parser_build_unary_op (op_loc, ثنائی_ہندسہ_NOT_اظہاریہ, op);
    حالت CPP_NOT:
      c_parser_error (parser, "%<!%> not valid in GIMPLE");
      واپس ret;
    حالت CPP_KEYWORD:
      انتخاب (c_parser_peek_token (parser)->keyword)
	{
	حالت RID_REALPART:
	  c_parser_consume_token (parser);
	  op = c_parser_gimple_postfix_عبارت (parser);
	  واپس gimple_parser_build_unary_op (op_loc, REALPART_اظہاریہ, op);
	حالت RID_IMAGPART:
	  c_parser_consume_token (parser);
	  op = c_parser_gimple_postfix_عبارت (parser);
	  واپس gimple_parser_build_unary_op (op_loc, IMAGPART_اظہاریہ, op);
	طےشدہ:
	  واپس c_parser_gimple_postfix_عبارت (parser);
	}
    حالت CPP_NAME:
	{
	  درخت id = c_parser_peek_token (parser)->قدر;
	  اگر (strcmp (IDENTIFIER_اشارہ_گر (id), "__ABS") == 0)
	    {
	      c_parser_consume_token (parser);
	      op = c_parser_gimple_postfix_عبارت (parser);
	      واپس gimple_parser_build_unary_op (op_loc, ABS_اظہاریہ, op);
	    }
	  ورنہ اگر (strcmp (IDENTIFIER_اشارہ_گر (id), "__ABSU") == 0)
	    {
	      c_parser_consume_token (parser);
	      op = c_parser_gimple_postfix_عبارت (parser);
	      واپس gimple_parser_build_unary_op (op_loc, ABSU_اظہاریہ, op);
	    }
	  ورنہ اگر (strcmp (IDENTIFIER_اشارہ_گر (id), "__MIN") == 0)
	    واپس c_parser_gimple_parentized_ثنائی_عبارت (parser,
								 op_loc,
								 MIN_اظہاریہ);
	  ورنہ اگر (strcmp (IDENTIFIER_اشارہ_گر (id), "__MAX") == 0)
	    واپس c_parser_gimple_parentized_ثنائی_عبارت (parser,
								 op_loc,
								 MAX_اظہاریہ);
	  ورنہ اگر (strcmp (IDENTIFIER_اشارہ_گر (id), "__VEC_PERM") == 0)
	    واپس c_parser_gimple_parentized_ternary_عبارت
			(parser, op_loc, VEC_PERM_اظہاریہ);
	  ورنہ اگر (strcmp (IDENTIFIER_اشارہ_گر (id), "__BIT_INSERT") == 0)
	    {
	      /* __BIT_INSERT '(' postfix-expression, postfix-expression,
			          integer ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      اگر (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_اظہاریہ op0 = c_parser_gimple_postfix_عبارت (parser);
		  c_parser_skip_until_ملا (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_اظہاریہ op1 = c_parser_gimple_postfix_عبارت (parser);
		  c_parser_skip_until_ملا (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_اظہاریہ op2 = c_parser_gimple_postfix_عبارت (parser);
		  اگر (درخت_رمز (op2.قدر) != INTEGER_CST
		      || !int_سماتا_type_p (op2.قدر, bitsizetype))
		    c_parser_error (parser, "expected constant offset");
		  c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  اگر (op0.قدر != error_mark_گرہ
		      && op1.قدر != error_mark_گرہ
		      && درخت_رمز (op2.قدر) == INTEGER_CST)
		    ret.قدر = build3_loc (loc, ثنائی_ہندسہ_داخل_کرو_اظہاریہ,
					    درخت_TYPE (op0.قدر),
					    op0.قدر, op1.قدر,
					    fold_convert (bitsizetype,
							  op2.قدر));
		}
	      واپس ret;
	    }
	  ورنہ
	    واپس c_parser_gimple_postfix_عبارت (parser);
	}
    طےشدہ:
      واپس c_parser_gimple_postfix_عبارت (parser);
    }
}

/* Decompose ID into base name (ID until ver_offset) and VERSION.  Return
   true if ID matches a SSA name.  */

ساکن منطقی
c_parser_parse_ssa_name_id (درخت id, غیرعلامتی *نسخہ, غیرعلامتی *ver_انحراف)
{
  ثابت حرف *token = IDENTIFIER_اشارہ_گر (id);
  ثابت حرف *var_نسخہ = strrchr (token, '_');
  اگر (! var_نسخہ)
    واپس جھوٹ;

  *ver_انحراف = var_نسخہ - token;
  برائے (ثابت حرف *p = var_نسخہ + 1; *p; ++p)
    اگر (! ISDIGIT (*p))
      واپس جھوٹ;
  *نسخہ = atoi (var_نسخہ + 1);
  واپس *نسخہ > 0;
}

/* Get at the actual SSA name ID with VERSION starting at VER_OFFSET.
   TYPE is the type if the SSA name is being declared.  */

ساکن درخت
c_parser_parse_ssa_name (gimple_parser &parser,
			 درخت id, درخت type, غیرعلامتی نسخہ,
			 غیرعلامتی ver_انحراف)
{
  درخت name = NULL_درخت;
  ثابت حرف *token = IDENTIFIER_اشارہ_گر (id);

  اگر (ver_انحراف == 0)
    {
      /* Anonymous unnamed SSA name.  */
      اگر (نسخہ < عدد_ssa_نام)
	name = ssa_name (نسخہ);
      اگر (! name)
	{
	  اگر (! type)
	    {
	      c_parser_error (parser, "SSA name undeclared");
	      واپس error_mark_گرہ;
	    }
	  name = make_ssa_name_fn (cfun, type, تہی, نسخہ);
	}
    }
  ورنہ
    {
      اگر (نسخہ < عدد_ssa_نام)
	name = ssa_name (نسخہ);
      اگر (! name)
	{
	  /* Separate var name from version.  */
	  حرف *var_name = XNEWVEC (حرف, ver_انحراف + 1);
	  حافظہ_نقل (var_name, token, ver_انحراف);
	  var_name[ver_انحراف] = '\0';
	  /* lookup for parent decl.  */
	  id = get_identifier (var_name);
	  درخت والد = lookup_name (id);
	  XDELETEVEC (var_name);
	  اگر (! والد || والد == error_mark_گرہ)
	    {
	      c_parser_error (parser, "base variable or SSA name undeclared");
	      واپس error_mark_گرہ;
	    }
	  اگر (!(VAR_P (والد)
		|| درخت_رمز (والد) == PARM_DECL
		|| درخت_رمز (والد) == نتیجہ_DECL))
	    {
	      error ("invalid base %qE for SSA name", والد);
	      واپس error_mark_گرہ;
	    }
	  name = make_ssa_name_fn (cfun, والد,
				   gimple_build_nop (), نسخہ);
	}
    }

  واپس name;
}

/* Parse a gimple call to an internal function.

   gimple-call-internal:
     . identifier ( gimple-argument-expression-list[opt] )  */

ساکن ساخت c_اظہاریہ
c_parser_gimple_call_اندرونی (gimple_parser &parser)
{
  ساخت c_اظہاریہ اظہاریہ;
  اظہاریہ.سیٹ_error ();

  gcc_assert (c_parser_اگلا_token_is (parser, CPP_DOT));
  c_parser_consume_token (parser);
  location_t loc = c_parser_peek_token (parser)->location;
  اگر (!c_parser_اگلا_token_is (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_قسم != C_ID_ID)
    {
      c_parser_error (parser, "expecting internal function name");
      واپس اظہاریہ;
    }
  درخت id = c_parser_peek_token (parser)->قدر;
  اندرونی_fn ifn = lookup_اندرونی_fn (IDENTIFIER_اشارہ_گر (id));
  c_parser_consume_token (parser);
  اگر (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    {
      auto_vec<درخت> exprlist;
      اگر (!c_parser_اگلا_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_gimple_اظہاریہ_list (parser, &exprlist);
      c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      اگر (ifn == IFN_آخری)
	error_at (loc, "unknown internal function %qE", id);
      ورنہ
	{
	  اظہاریہ.قدر = build_call_اظہاریہ_اندرونی_loc_array
	    (loc, ifn, void_type_گرہ, exprlist.لمبائی (),
	     exprlist.پتہ ());
	  اظہاریہ.original_رمز = ERROR_MARK;
	  اظہاریہ.original_type = تہی;
	  اظہاریہ.m_decimal = 0;
	}
    }
  واپس اظہاریہ;
}

/* Parse '<' type [',' alignment] '>' and return a type on success
   and NULL_TREE on error.  */

ساکن درخت
c_parser_gimple_typespec (gimple_parser &parser)
{
  ساخت c_type_name *type_name = تہی;
  درخت alignment = NULL_درخت;
  اگر (c_parser_require (parser, CPP_LESS, "expected %<<%>"))
    {
      type_name = c_parser_type_name (parser);
      /* Optional alignment.  */
      اگر (c_parser_اگلا_token_is (parser, CPP_COMMA))
	{
	  c_parser_consume_token (parser);
	  alignment
	      = c_parser_gimple_postfix_عبارت (parser).قدر;
	}
      c_parser_skip_until_ملا (parser,
				 CPP_GREATER, "expected %<>%>");
    }
  اگر (!type_name)
    واپس NULL_درخت;
  درخت tem;
  درخت type = groktypename (type_name, &tem, تہی);
  اگر (alignment)
    type = build_aligned_type (type, درخت_مقصد_uhwi (alignment));
  واپس type;
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

ساکن ساخت c_اظہاریہ
c_parser_gimple_postfix_عبارت (gimple_parser &parser, درخت ret_type)
{
  location_t loc = c_parser_peek_token (parser)->location;
  ماخذ_range tok_range = c_parser_peek_token (parser)->get_range ();
  ساخت c_اظہاریہ اظہاریہ;
  اظہاریہ.سیٹ_error ();
  انتخاب (c_parser_peek_token (parser)->type)
    {
    حالت CPP_نمبر:
      اظہاریہ.قدر = c_parser_peek_token (parser)->قدر;
      سیٹ_c_اظہاریہ_ماخذ_range (&اظہاریہ, tok_range);
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      توڑو;
    حالت CPP_CHAR:
    حالت CPP_CHAR16:
    حالت CPP_CHAR32:
    حالت CPP_UTF8CHAR:
    حالت CPP_WCHAR:
      اظہاریہ.قدر = c_parser_peek_token (parser)->قدر;
      سیٹ_c_اظہاریہ_ماخذ_range (&اظہاریہ, tok_range);
      c_parser_consume_token (parser);
      توڑو;
    حالت CPP_STRING:
    حالت CPP_STRING16:
    حالت CPP_STRING32:
    حالت CPP_WSTRING:
    حالت CPP_UTF8STRING:
      اظہاریہ = c_parser_string_literal (parser, جھوٹ, سچ);
      توڑو;
    حالت CPP_DOT:
      اظہاریہ = c_parser_gimple_call_اندرونی (parser);
      توڑو;
    حالت CPP_NAME:
      اگر (c_parser_peek_token (parser)->id_قسم == C_ID_ID)
	{
	  درخت id = c_parser_peek_token (parser)->قدر;
	  اگر (strcmp (IDENTIFIER_اشارہ_گر (id), "__MEM") == 0)
	    {
	      /* __MEM '<' type-name [ ',' number ] '>'
	               '(' [ '(' type-name ')' ] unary-expression
			   [ '+' number ]
			   [ ',' number ]
			   [ ',' number ':' number ] ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      درخت type = c_parser_gimple_typespec (parser);
	      ساخت c_اظہاریہ ptr, alias_off, قدم, اشاریہ, index2;
	      ptr.قدر = error_mark_گرہ;
	      alias_off.قدر = NULL_درخت;
	      قدم.قدر = NULL_درخت;
	      اشاریہ.قدر = NULL_درخت;
	      index2.قدر = NULL_درخت;
	      غیرعلامتی مختصر clique = 0;
	      غیرعلامتی مختصر بنیاد = 0;
	      منطقی الٹ_ترتیب = جھوٹ;
	      ساخت c_اظہاریہ ro;
	      اگر (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  درخت alias_type = NULL_درخت;
		  /* Optional alias-type cast.  */
		  اگر (c_parser_اگلا_token_is (parser, CPP_OPEN_PAREN))
		    {
		      c_parser_consume_token (parser);
		      ساخت c_type_name *alias_type_name
			= c_parser_type_name (parser);
		      c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN,
						 "expected %<)%>");
		      اگر (alias_type_name)
			{
			  درخت tem;
			  alias_type = groktypename (alias_type_name,
						     &tem, تہی);
			}
		    }
		  ptr = c_parser_gimple_unary_عبارت (parser);
		  اگر (ptr.قدر == error_mark_گرہ
		      || ! اشارہ_گر_TYPE_P (درخت_TYPE (ptr.قدر)))
		    {
		      اگر (ptr.قدر != error_mark_گرہ)
			error_at (ptr.get_آغاز (),
				  "invalid type of %<__MEM%> operand");
		      c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN,
						 "expected %<)%>");
		      واپس اظہاریہ;
		    }
		  اگر (! alias_type)
		    alias_type = درخت_TYPE (ptr.قدر);
		  /* Optional constant offset.  */
		  اگر (c_parser_اگلا_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      alias_off = c_parser_gimple_postfix_عبارت (parser);
		    }
		  اگر (c_parser_اگلا_token_is (parser, CPP_MULT))
		    {
		      std::تبادلہ (اشاریہ, alias_off);
		      c_parser_consume_token (parser);
		      قدم = c_parser_gimple_postfix_عبارت (parser);
		    }
		  ورنہ اگر (c_parser_اگلا_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      اشاریہ = c_parser_gimple_postfix_عبارت (parser);
		      اگر (c_parser_اگلا_token_is (parser, CPP_MULT))
			{
			  c_parser_consume_token (parser);
			  قدم = c_parser_gimple_postfix_عبارت (parser);
			}
		      ورنہ
			std::تبادلہ (اشاریہ, index2);
		    }
		  ورنہ اگر (alias_off.قدر
			   && درخت_رمز (alias_off.قدر) != INTEGER_CST)
		    std::تبادلہ (alias_off, index2);
		  اگر (c_parser_اگلا_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      index2 = c_parser_gimple_postfix_عبارت (parser);
		    }
		  اگر (alias_off.قدر)
		    {
		      اگر (درخت_رمز (alias_off.قدر) != INTEGER_CST)
			error_at (alias_off.get_آغاز (),
				  "expected constant offset for %<__MEM%> "
				  "operand");
		      alias_off.قدر = fold_convert (alias_type,
						      alias_off.قدر);
		    }
		  ورنہ
		    alias_off.قدر = build_int_cst (alias_type, 0);
		  اگر (قدم.قدر)
		    {
		      اگر (درخت_رمز (قدم.قدر) != INTEGER_CST)
			error_at (قدم.get_آغاز (),
				  "expected constant step for %<__MEM%> "
				  "operand");
		    }
		  اگر (c_parser_اگلا_token_is (parser, CPP_COMMA))
		    {
		      ساخت c_اظہاریہ cl, ba;
		      منطقی has_clb = سچ;
		      c_parser_consume_token (parser);
		      cl = c_parser_gimple_postfix_عبارت (parser);
		      اگر (!c_parser_اگلا_token_is (parser, CPP_COLON))
			{
			  ro = cl;
			  غیرعلامتی HOST_WIDE_INT tmp = 0;
			  اگر (!درخت_سماتا_uhwi_p (ro.قدر)
			      || (tmp = درخت_مقصد_uhwi (ro.قدر)) > 1)
			    error_at (ro.get_آغاز (),
				      "invalid reverse order value");
			  الٹ_ترتیب = tmp;
			  has_clb = جھوٹ;
			  اگر (c_parser_اگلا_token_is (parser, CPP_COMMA))
			    {
			      c_parser_consume_token (parser);
			      cl = c_parser_gimple_postfix_عبارت (parser);
		              has_clb = سچ;
			    }
			}
		      اگر (has_clb
			  && c_parser_require (parser,
					       CPP_COLON, "expected %<:%>"))
			{
			  ba = c_parser_gimple_postfix_عبارت (parser);
			  اگر (!درخت_سماتا_uhwi_p (cl.قدر)
			      || !درخت_سماتا_uhwi_p (ba.قدر)
			      || compare_درخت_int (cl.قدر,
						   (clique = درخت_مقصد_uhwi
								(cl.قدر)))
			      || compare_درخت_int (ba.قدر,
						   (بنیاد = درخت_مقصد_uhwi
								 (ba.قدر))))
			    error_at (cl.get_آغاز (),
				      "invalid clique/base pair");
			}
		    }
		  c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      اگر (! type || c_parser_error (parser))
		{
		  c_parser_سیٹ_error (parser, جھوٹ);
		  واپس اظہاریہ;
		}
	      اگر (اشاریہ.قدر || قدم.قدر || index2.قدر)
		اظہاریہ.قدر = build5_loc (loc, ہدف_MEM_REF,
					 type, ptr.قدر, alias_off.قدر,
					 اشاریہ.قدر, قدم.قدر, index2.قدر);
	      ورنہ
		اظہاریہ.قدر = build2_loc (loc, MEM_REF,
					 type, ptr.قدر, alias_off.قدر);
	      اگر (clique != 0)
		{
		  cfun->آخری_clique = MAX (cfun->آخری_clique, clique);
		  MR_DEPENDENCE_CLIQUE (اظہاریہ.قدر) = clique;
		  MR_DEPENDENCE_بنیاد (اظہاریہ.قدر) = بنیاد;
		}
	      اگر (الٹ_ترتیب)
		{
		  اگر (درخت_رمز (اظہاریہ.قدر) == MEM_REF)
		    REF_الٹ_STORAGE_ترتیب (اظہاریہ.قدر) = الٹ_ترتیب;
		  ورنہ
		    error_at (ro.get_آغاز (),
			      "target mem ref cannot have reverse order");
		}
	      توڑو;
	    }
	  ورنہ اگر (strcmp (IDENTIFIER_اشارہ_گر (id), "__VIEW_CONVERT") == 0)
	    {
	      /* __VIEW_CONVERT '<' type-name [ ',' number ] '>'
	                        '(' postfix-expression ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      درخت type = c_parser_gimple_typespec (parser);
	      اگر (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_اظہاریہ op = c_parser_gimple_postfix_عبارت (parser);
		  c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  اگر (type && op.قدر != error_mark_گرہ)
		    اظہاریہ.قدر = build1_loc (loc, VIEW_CONVERT_اظہاریہ,
					     type, op.قدر);
		}
	      توڑو;
	    }
	  ورنہ اگر (strcmp (IDENTIFIER_اشارہ_گر (id), "__BIT_FIELD_REF") == 0)
	    {
	      /* __BIT_FIELD_REF '<' type-name [ ',' number ] '>'
	                        '(' postfix-expression, integer, integer ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      درخت type = c_parser_gimple_typespec (parser);
	      اگر (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_اظہاریہ op0 = c_parser_gimple_postfix_عبارت (parser);
		  c_parser_skip_until_ملا (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_اظہاریہ op1 = c_parser_gimple_postfix_عبارت (parser);
		  اگر (درخت_رمز (op1.قدر) != INTEGER_CST
		      || !int_سماتا_type_p (op1.قدر, bitsizetype))
		    c_parser_error (parser, "expected constant size");
		  c_parser_skip_until_ملا (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_اظہاریہ op2 = c_parser_gimple_postfix_عبارت (parser);
		  اگر (درخت_رمز (op2.قدر) != INTEGER_CST
		      || !int_سماتا_type_p (op2.قدر, bitsizetype))
		    c_parser_error (parser, "expected constant offset");
		  c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  اگر (type
		      && op0.قدر != error_mark_گرہ
		      && درخت_رمز (op1.قدر) == INTEGER_CST
		      && درخت_رمز (op2.قدر) == INTEGER_CST)
		    اظہاریہ.قدر = build3_loc (loc, ثنائی_ہندسہ_میدان_REF, type,
					     op0.قدر,
					     fold_convert (bitsizetype,
							   op1.قدر),
					     fold_convert (bitsizetype,
							   op2.قدر));
		}
	      توڑو;
	    }
	  ورنہ اگر (strcmp (IDENTIFIER_اشارہ_گر (id), "__CLOBBER") == 0)
	    {
	      /* __CLOBBER [ '(' bob | eob | bos | eos ')' ]  */
	      clobber_قسم قسم = CLOBBER_UNDEF;
	      c_parser_consume_token (parser);
	      اگر (c_parser_اگلا_token_is (parser, CPP_OPEN_PAREN))
		{
		  c_parser_consume_token (parser);
		  خودکار tok = c_parser_peek_token (parser);
		  اگر (c_parser_require (parser, CPP_NAME,
					"expected clobber kind"))
		    {
		      ثابت حرف *قسم_str = IDENTIFIER_اشارہ_گر (tok->قدر);
		      اگر (strcmp (قسم_str, "bos") == 0)
			قسم = CLOBBER_STORAGE_BEGIN;
		      ورنہ اگر (strcmp (قسم_str, "bob") == 0)
			قسم = CLOBBER_OBJECT_BEGIN;
		      ورنہ اگر (strcmp (قسم_str, "eob") == 0)
			قسم = CLOBBER_OBJECT_انتہا;
		      ورنہ اگر (strcmp (قسم_str, "eos") == 0)
			قسم = CLOBBER_STORAGE_انتہا;
		      ورنہ
			c_parser_error (parser, "expected one of %<bos%>, "
					"%<eos%>, %<bob>, %<eob%>");
		    }
		  c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      /* We infer the (redundant) type from the LHS.  */
	      اظہاریہ.قدر = build_clobber (ret_type, قسم);
	      توڑو;
	    }
	  ورنہ اگر (strcmp (IDENTIFIER_اشارہ_گر (id), "_Literal") == 0)
	    {
	      /* _Literal '(' type-name ')' ( [ '-' ] constant | constructor ) */
	      c_parser_consume_token (parser);
	      درخت type = NULL_درخت;
	      اگر (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  ساخت c_type_name *type_name = c_parser_type_name (parser);
		  درخت tem;
		  اگر (type_name)
		    type = groktypename (type_name, &tem, تہی);
		  c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      اگر (! type)
		{
		  c_parser_error (parser, "invalid _Literal");
		  واپس اظہاریہ;
		}
	      اگر (c_parser_اگلا_token_is (parser, CPP_OPEN_BRACE))
		{
		  c_parser_consume_token (parser);
		  اگر (!AGGREGATE_TYPE_P (type)
		      && !سمتیہ_TYPE_P (type))
		    {
		      c_parser_error (parser, "invalid type for _Literal with "
				      "constructor");
		      c_parser_skip_until_ملا (parser, CPP_CLOSE_BRACE,
						 "expected %<}%>");
		      واپس اظہاریہ;
		    }
		  vec<constructor_elt, va_gc> *v = تہی;
		  منطقی constant_p = سچ;
		  اگر (سمتیہ_TYPE_P (type)
		      && !c_parser_اگلا_token_is (parser, CPP_CLOSE_BRACE))
		    {
		      vec_alloc (v, TYPE_سمتیہ_SUBPARTS (type).مقصد_constant ());
		      کرو
			{
			  درخت val
			    = c_parser_gimple_postfix_عبارت (parser).قدر;
			  اگر (! val
			      || val == error_mark_گرہ
			      || (! CONSTANT_CLASS_P (val)
				  && ! SSA_VAR_P (val)))
			    {
			      c_parser_error (parser, "invalid _Literal");
			      واپس اظہاریہ;
			    }
			  CONSTRUCTOR_APPEND_ELT (v, NULL_درخت, val);
			  اگر (! CONSTANT_CLASS_P (val))
			    constant_p = جھوٹ;
			  اگر (c_parser_اگلا_token_is (parser, CPP_COMMA))
			    c_parser_consume_token (parser);
			  ورنہ
			    توڑو;
			}
		      جب (1);
		    }
		  اگر (c_parser_require (parser, CPP_CLOSE_BRACE,
					"expected %<}%>"))
		    {
		      اگر (v && constant_p)
			اظہاریہ.قدر = build_سمتیہ_from_ctor (type, v);
		      ورنہ
			اظہاریہ.قدر = build_constructor (type, v);
		    }
		  ورنہ
		    {
		      c_parser_skip_until_ملا (parser, CPP_CLOSE_BRACE,
						 "expected %<}%>");
		      واپس اظہاریہ;
		    }
		}
	      ورنہ
		{
		  منطقی neg_p, addr_p;
		  اگر ((neg_p = c_parser_اگلا_token_is (parser, CPP_MINUS)))
		    c_parser_consume_token (parser);
		  اگر ((addr_p = c_parser_اگلا_token_is (parser, CPP_AND)))
		    c_parser_consume_token (parser);
		  درخت val = c_parser_gimple_postfix_عبارت (parser).قدر;
		  اگر (! val
		      || val == error_mark_گرہ
		      || (!CONSTANT_CLASS_P (val) && !addr_p))
		    {
		      c_parser_error (parser, "invalid _Literal");
		      واپس اظہاریہ;
		    }
		  اگر (addr_p)
		    {
		      val = build1 (ADDR_اظہاریہ, type, val);
		      اگر (!is_gimple_invariant_پتہ (val))
			{
			  c_parser_error (parser, "invalid _Literal");
			  واپس اظہاریہ;
			}
		    }
		  اگر (neg_p)
		    {
		      val = const_unop (NEGATE_اظہاریہ, درخت_TYPE (val), val);
		      اگر (! val)
			{
			  c_parser_error (parser, "invalid _Literal");
			  واپس اظہاریہ;
			}
		    }
		  اظہاریہ.قدر = fold_convert (type, val);
		}
	      واپس اظہاریہ;
	    }

	  /* SSA name.  */
	  غیرعلامتی نسخہ, ver_انحراف;
	  اگر (! lookup_name (id)
	      && c_parser_parse_ssa_name_id (id, &نسخہ, &ver_انحراف))
	    {
	      c_parser_consume_token (parser);
	      اظہاریہ.قدر = c_parser_parse_ssa_name (parser, id, NULL_درخت,
						    نسخہ, ver_انحراف);
	      اگر (اظہاریہ.قدر == error_mark_گرہ)
		واپس اظہاریہ;
	      سیٹ_c_اظہاریہ_ماخذ_range (&اظہاریہ, tok_range);
	      /* For default definition SSA names.  */
	      اگر (c_parser_اگلا_token_is (parser, CPP_OPEN_PAREN)
		  && c_parser_peek_2nd_token (parser)->type == CPP_NAME
		  && strcmp ("D",
			     IDENTIFIER_اشارہ_گر
			       (c_parser_peek_2nd_token (parser)->قدر)) == 0
		  && c_parser_peek_nth_token (parser, 3)->type == CPP_CLOSE_PAREN)
		{
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		  اگر (! SSA_NAME_IS_DEFAULT_DEF (اظہاریہ.قدر))
		    {
		      اگر (!SSA_NAME_VAR (اظہاریہ.قدر))
			{
			  error_at (loc, "anonymous SSA name cannot have"
				    " default definition");
			  اظہاریہ.قدر = error_mark_گرہ;
			  واپس اظہاریہ;
			}
		      سیٹ_ssa_default_def (cfun, SSA_NAME_VAR (اظہاریہ.قدر),
					   اظہاریہ.قدر);
		      SSA_NAME_DEF_STMT (اظہاریہ.قدر) = gimple_build_nop ();
		    }
		}
	    }
	  ورنہ
	    {
	      c_parser_consume_token (parser);
	      اظہاریہ.قدر
		= build_external_ref (loc, id,
				      (c_parser_peek_token (parser)->type
				       == CPP_OPEN_PAREN), &اظہاریہ.original_type);
	      سیٹ_c_اظہاریہ_ماخذ_range (&اظہاریہ, tok_range);
	    }
	  توڑو;
	}
      /* Fallthru.  */
    طےشدہ:
      c_parser_error (parser, "expected expression");
      اظہاریہ.سیٹ_error ();
      توڑو;
    }
  اگر (اظہاریہ.قدر == error_mark_گرہ)
    واپس اظہاریہ;
  واپس c_parser_gimple_postfix_عبارت_after_primary
    (parser, اظہاریہ_LOC_OR_LOC (اظہاریہ.قدر, loc), اظہاریہ);
}

/* Parse a gimple postfix expression after the initial primary or compound
   literal.  */

ساکن ساخت c_اظہاریہ
c_parser_gimple_postfix_عبارت_after_primary (gimple_parser &parser,
						  location_t اظہاریہ_loc,
						  ساخت c_اظہاریہ اظہاریہ)
{
  location_t آغاز;
  location_t اختتام;
  درخت ident;
  location_t comp_loc;

  جب (سچ)
    {
      location_t op_loc = c_parser_peek_token (parser)->location;
      انتخاب (c_parser_peek_token (parser)->type)
	{
	حالت CPP_OPEN_مربع:
	  {
	    c_parser_consume_token (parser);
	    درخت idx = c_parser_gimple_unary_عبارت (parser).قدر;

	    اگر (! c_parser_require (parser, CPP_CLOSE_مربع, "expected %<]%>"))
	      {
		c_parser_skip_until_ملا (parser, CPP_CLOSE_مربع, تہی);
		توڑو;
	      }

	    آغاز = اظہاریہ.get_آغاز ();
	    اختتام = c_parser_علامات_buf (parser, 0)->location;
	    اظہاریہ.قدر = build_array_ref (op_loc, اظہاریہ.قدر, idx);
	    سیٹ_c_اظہاریہ_ماخذ_range (&اظہاریہ, آغاز, اختتام);
	    اظہاریہ.m_decimal = 0;

	    اظہاریہ.original_رمز = ERROR_MARK;
	    اظہاریہ.original_type = تہی;
	    توڑو;
	  }
	حالت CPP_OPEN_PAREN:
	  {
	    /* Function call.  */
	    c_parser_consume_token (parser);
	    auto_vec<درخت> exprlist;
	    اگر (! c_parser_اگلا_token_is (parser, CPP_CLOSE_PAREN))
	      c_parser_gimple_اظہاریہ_list (parser, &exprlist);
	    c_parser_skip_until_ملا (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    اگر (!FUNC_OR_طریقہ_TYPE_P (درخت_TYPE (اظہاریہ.قدر)))
	      {
		c_parser_error (parser, "invalid call to non-function");
		اظہاریہ.سیٹ_error ();
		توڑو;
	      }
	    اظہاریہ.قدر = build_call_array_loc
		(اظہاریہ_loc, درخت_TYPE (درخت_TYPE (اظہاریہ.قدر)),
		 اظہاریہ.قدر, exprlist.لمبائی (), exprlist.پتہ ());
	    اظہاریہ.m_decimal = 0;
	    اظہاریہ.original_رمز = ERROR_MARK;
	    اظہاریہ.original_type = تہی;
	    توڑو;
	  }
	حالت CPP_DOT:
	  {
	    /* Structure element reference.  */
	    c_parser_consume_token (parser);
	    اگر (c_parser_اگلا_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		ident = comp_tok->قدر;
		comp_loc = comp_tok->location;
	      }
	    ورنہ
	      {
		c_parser_error (parser, "expected identifier");
		اظہاریہ.سیٹ_error ();
		اظہاریہ.original_رمز = ERROR_MARK;
		اظہاریہ.original_type = تہی;
		واپس اظہاریہ;
	      }
	    آغاز = اظہاریہ.get_آغاز ();
	    اختتام = c_parser_peek_token (parser)->get_اختتام ();
	    c_parser_consume_token (parser);
	    اظہاریہ.قدر = build_component_ref (op_loc, اظہاریہ.قدر, ident,
					      comp_loc, UNKNOWN_LOCATION);
	    سیٹ_c_اظہاریہ_ماخذ_range (&اظہاریہ, آغاز, اختتام);
	    اظہاریہ.m_decimal = 0;
	    اظہاریہ.original_رمز = ERROR_MARK;
	    اگر (درخت_رمز (اظہاریہ.قدر) != COMPONENT_REF)
	      اظہاریہ.original_type = تہی;
	    ورنہ
	      {
		/* Remember the original type of a bitfield.  */
		درخت میدان_2 = درخت_عملیہ (اظہاریہ.قدر, 1);
		اگر (درخت_رمز (میدان_2) != میدان_DECL)
		  اظہاریہ.original_type = تہی;
		ورنہ
		  اظہاریہ.original_type = DECL_ثنائی_ہندسہ_میدان_TYPE (میدان_2);
	      }
	    توڑو;
	  }
	حالت CPP_DEREF:
	  {
	    /* Structure element reference.  */
	    اگر (!اشارہ_گر_TYPE_P (درخت_TYPE (اظہاریہ.قدر)))
	      {
		c_parser_error (parser, "dereference of non-pointer");
		اظہاریہ.سیٹ_error ();
		اظہاریہ.original_رمز = ERROR_MARK;
		اظہاریہ.original_type = تہی;
		واپس اظہاریہ;
	      }
	    c_parser_consume_token (parser);
	    اگر (c_parser_اگلا_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		ident = comp_tok->قدر;
		comp_loc = comp_tok->location;
	      }
	    ورنہ
	      {
		c_parser_error (parser, "expected identifier");
		اظہاریہ.سیٹ_error ();
		اظہاریہ.original_رمز = ERROR_MARK;
		اظہاریہ.original_type = تہی;
		واپس اظہاریہ;
	      }
	    آغاز = اظہاریہ.get_آغاز ();
	    اختتام = c_parser_peek_token (parser)->get_اختتام ();
	    c_parser_consume_token (parser);
	    اظہاریہ.قدر = build_component_ref (op_loc,
					      build_simple_mem_ref_loc
					        (op_loc, اظہاریہ.قدر),
					      ident, comp_loc,
					      اظہاریہ.get_location ());
	    سیٹ_c_اظہاریہ_ماخذ_range (&اظہاریہ, آغاز, اختتام);
	    اظہاریہ.m_decimal = 0;
	    اظہاریہ.original_رمز = ERROR_MARK;
	    اگر (درخت_رمز (اظہاریہ.قدر) != COMPONENT_REF)
	      اظہاریہ.original_type = تہی;
	    ورنہ
	      {
		/* Remember the original type of a bitfield.  */
		درخت میدان_2 = درخت_عملیہ (اظہاریہ.قدر, 1);
		اگر (درخت_رمز (میدان_2) != میدان_DECL)
		  اظہاریہ.original_type = تہی;
		ورنہ
		  اظہاریہ.original_type = DECL_ثنائی_ہندسہ_میدان_TYPE (میدان_2);
	      }
	    توڑو;
	  }
	طےشدہ:
	  واپس اظہاریہ;
	}
    }
}

/* Parse expression list.

   gimple-expr-list:
     gimple-unary-expression
     gimple-expr-list , gimple-unary-expression

 */

ساکن خالی
c_parser_gimple_اظہاریہ_list (gimple_parser &parser, vec<درخت> *ret)
{
  ساخت c_اظہاریہ اظہاریہ;

  اظہاریہ = c_parser_gimple_unary_عبارت (parser);
  ret->محفوظ_ڈالو (اظہاریہ.قدر);
  جب (c_parser_اگلا_token_is (parser, CPP_COMMA))
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

ساکن خالی
c_parser_gimple_label (gimple_parser &parser, gimple_seq *seq)
{
  درخت name = c_parser_peek_token (parser)->قدر;
  location_t loc1 = c_parser_peek_token (parser)->location;
  gcc_assert (c_parser_اگلا_token_is (parser, CPP_NAME));
  c_parser_consume_token (parser);
  gcc_assert (c_parser_اگلا_token_is (parser, CPP_COLON));
  c_parser_consume_token (parser);
  درخت label = define_label (loc1, name);
  اگر (label)
    gimple_seq_جوڑو_stmt_without_update (seq, gimple_build_label (label));
  واپس;
}

/* Parse gimple/RTL pass list.

   gimple-or-rtl-pass-list:
     startwith("pass-name")[,{cfg,ssa}]
 */

خالی
c_parser_gimple_or_rtl_pass_list (c_parser *parser, c_declspecs *specs)
{
  حرف *pass = تہی;

  /* Accept __GIMPLE/__RTL.  */
  اگر (c_parser_اگلا_token_is_not (parser, CPP_OPEN_PAREN))
    واپس;
  c_parser_consume_token (parser);

  specs->اندراج_bb_گنتی = profile_گنتی::uninitialized ();
  جب (c_parser_اگلا_token_is (parser, CPP_NAME))
    {
      profile_quality quality;
      ثابت حرف *op = IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر);
      c_parser_consume_token (parser);
      اگر (! strcmp (op, "startwith"))
	{
	  اگر (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    واپس;
	  اگر (c_parser_اگلا_token_is_not (parser, CPP_STRING))
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"expected pass name");
	      واپس;
	    }
	  pass = xstrdup (درخت_STRING_اشارہ_گر
			  (c_parser_string_literal (parser, جھوٹ,
						    جھوٹ).قدر));
	  اگر (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<(%>"))
	    واپس;
	}
      ورنہ اگر (parse_profile_quality (op, &quality))
	{
	  درخت q;
	  اگر (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    واپس;

	  اگر (!c_parser_اگلا_token_is (parser, CPP_نمبر)
	      || (درخت_رمز (q = c_parser_peek_token (parser)->قدر)
		  != INTEGER_CST))
	    {
	      c_parser_error (parser, "expected count value");
	      واپس;
	    }

	  specs->اندراج_bb_گنتی
	    = profile_گنتی::from_gcov_type (درخت_INT_CST_کم (q), quality);
	  c_parser_consume_token (parser);
	  اگر (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    واپس;
	}
      ورنہ اگر (specs->declspec_il != cdil_gimple)
	/* Allow only one IL specifier and none on RTL.  */
	;
      ورنہ اگر (! strcmp (op, "cfg"))
	specs->declspec_il = cdil_gimple_cfg;
      ورنہ اگر (! strcmp (op, "ssa"))
	specs->declspec_il = cdil_gimple_ssa;
      ورنہ
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "invalid operation");
	  واپس;
	}
     اگر (c_parser_اگلا_token_is (parser, CPP_COMMA))
       c_parser_consume_token (parser);
    }

  اگر (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    واپس;

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

ساکن خالی
c_parser_gimple_declaration (gimple_parser &parser)
{
  ساخت c_declarator *declarator;
  ساخت c_declspecs *specs = build_null_declspecs ();
  c_parser_declspecs (parser, specs, سچ, سچ, سچ,
		      سچ, سچ, سچ, سچ, cla_nonabstract_decl);
  اختتام_declspecs (specs);

  /* Provide better error recovery.  Note that a type name here is usually
     better diagnosed as a redeclaration.  */
  اگر (c_parser_اگلا_token_starts_declspecs (parser)
      && ! c_parser_اگلا_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<;%>");
      c_parser_سیٹ_error (parser, جھوٹ);
      واپس;
    }

  منطقی dummy = جھوٹ;
  declarator = c_parser_declarator (parser,
				    specs->typespec_قسم != ctsk_none,
				    C_DTR_معمول, &dummy);

  اگر (!c_parser_اگلا_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_error (parser, "expected %<;%>");
      واپس;
    }
  اگر (declarator)
    {
      /* Handle SSA name decls specially, they do not go into the identifier
         table but we simply build the SSA name for later lookup.  */
      غیرعلامتی نسخہ, ver_انحراف;
      /* Handle SSA pointer declarations in a very simplistic ways, we
	 probably would like to call grokdeclarator in a special mode to
	 just build the type of the decl - start_decl already pushes
	 the identifier to the bindings for lookup, something we do not
	 want.  */
      ساخت c_declarator *id_declarator = declarator;
      جب (id_declarator->قسم == cdk_اشارہ_گر)
	id_declarator = id_declarator->declarator;
      اگر (id_declarator->قسم == cdk_id
	  && (declarator->قسم == cdk_اشارہ_گر
	      || is_gimple_reg_type (specs->type))
	  && c_parser_parse_ssa_name_id (id_declarator->u.id.id,
					 &نسخہ, &ver_انحراف)
	  /* The following restricts it to unnamed anonymous SSA names
	     which fails parsing of named ones in dumps (we could
	     decide to not dump their name for -gimple).  */
	  && ver_انحراف == 0)
	{
	  ساخت c_declarator *p = declarator;
	  درخت type = specs->type;
	  جب (p->قسم == cdk_اشارہ_گر)
	    {
	      type = build_اشارہ_گر_type (type);
	      p = p->declarator;
	    }
	  c_parser_parse_ssa_name (parser, id_declarator->u.id.id, type,
				   نسخہ, ver_انحراف);
	}
      ورنہ
	{
	  درخت postfix_attrs = NULL_درخت;
	  درخت all_سابقہ_attrs = specs->attrs;
	  specs->attrs = تہی;
	  درخت decl = آغاز_decl (declarator, specs, جھوٹ,
				  chainon (postfix_attrs, all_سابقہ_attrs));
	  اگر (decl)
	    اختتام_decl (decl, UNKNOWN_LOCATION, NULL_درخت, NULL_درخت,
			 NULL_درخت);
	}
    }
}

/* Parse gimple goto statement.  */

ساکن خالی
c_parser_gimple_goto_stmt (gimple_parser &parser,
			   location_t loc, درخت label, gimple_seq *seq)
{
  اگر (cfun->curr_properties & PROP_cfg)
    {
      صحیح dest_اشاریہ;
      profile_probability prob;
      اگر (c_parser_gimple_parse_bb_spec_کنارہ_probability (label, parser,
							  &dest_اشاریہ, &prob))
	{
	  parser.ڈالو_کنارہ (parser.current_bb->اشاریہ, dest_اشاریہ,
			    کنارہ_FALLTHRU, prob);
	  واپس;
	}
    }
  درخت decl = lookup_label_for_goto (loc, label);
  gimple_seq_جوڑو_stmt_without_update (seq, gimple_build_goto (decl));
}

/* Parse a parenthesized condition.
   gimple-condition:
     ( gimple-binary-expression )    */

ساکن درخت
c_parser_gimple_paren_condition (gimple_parser &parser)
{
  اگر (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    واپس error_mark_گرہ;
  درخت cond
    = c_parser_gimple_ثنائی_عبارت (parser, boolean_type_گرہ).قدر;
  اگر (cond != error_mark_گرہ
      && ! COMPARISON_CLASS_P (cond)
      && ! CONSTANT_CLASS_P (cond)
      && ! SSA_VAR_P (cond))
    {
      c_parser_error (parser, "comparison required");
      cond = error_mark_گرہ;
    }
  اگر (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    واپس error_mark_گرہ;
  واپس cond;
}

/* Parse gimple try statement.

   try-statement:
     try { ... } finally { ... }
     try { ... } finally { ... } else { ... }

   This could support try/catch as well, but it's not implemented yet.
 */

ساکن خالی
c_parser_gimple_try_stmt (gimple_parser &parser, gimple_seq *seq)
{
  gimple_seq tryseq = تہی;
  c_parser_consume_token (parser);
  c_parser_gimple_compound_statement (parser, &tryseq);

  اگر ((c_parser_اگلا_token_is (parser, CPP_KEYWORD)
       && c_parser_peek_token (parser)->keyword == RID_AT_FINALLY)
      || (c_parser_اگلا_token_is (parser, CPP_NAME)
	  && c_parser_peek_token (parser)->id_قسم == C_ID_ID
	  && strcmp (IDENTIFIER_اشارہ_گر (c_parser_peek_token (parser)->قدر),
		     "finally") == 0))
    {
      gimple_seq finseq = تہی;
      c_parser_consume_token (parser);
      c_parser_gimple_compound_statement (parser, &finseq);

      اگر (c_parser_اگلا_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_ELSE)
	{
	  gimple_seq elsseq = تہی;
	  c_parser_consume_token (parser);
	  c_parser_gimple_compound_statement (parser, &elsseq);

	  geh_else *stmt = gimple_build_eh_else (finseq, elsseq);
	  finseq = تہی;
	  gimple_seq_جوڑو_stmt_without_update (&finseq, stmt);
	}

      gtry *stmt = gimple_build_try (tryseq, finseq, GIMPLE_TRY_FINALLY);
      gimple_seq_جوڑو_stmt_without_update (seq, stmt);
    }
  ورنہ اگر (c_parser_اگلا_token_is (parser, CPP_KEYWORD)
      && c_parser_peek_token (parser)->keyword == RID_AT_CATCH)
    c_parser_error (parser, "%<catch%> is not supported");
  ورنہ
    c_parser_error (parser, "expected %<finally%> or %<catch%>");
}

/* Parse gimple if-else statement.

   if-statement:
     if ( gimple-binary-expression ) gimple-goto-statement
     if ( gimple-binary-expression ) gimple-goto-statement \
					else gimple-goto-statement
 */

ساکن خالی
c_parser_gimple_if_stmt (gimple_parser &parser, gimple_seq *seq)
{
  درخت t_label = NULL_درخت, f_label = NULL_درخت, label;
  location_t loc;
  c_parser_consume_token (parser);
  درخت cond = c_parser_gimple_paren_condition (parser);

  اگر (c_parser_اگلا_token_is_keyword (parser, RID_GOTO))
    {
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      اگر (! c_parser_اگلا_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected label");
	  واپس;
	}
      label = c_parser_peek_token (parser)->قدر;
      c_parser_consume_token (parser);
      صحیح dest_اشاریہ;
      profile_probability prob;
      اگر ((cfun->curr_properties & PROP_cfg)
	  && c_parser_gimple_parse_bb_spec_کنارہ_probability (label, parser,
							     &dest_اشاریہ, &prob))
	parser.ڈالو_کنارہ (parser.current_bb->اشاریہ, dest_اشاریہ,
			  کنارہ_TRUE_قدر, prob);
      ورنہ
	t_label = lookup_label_for_goto (loc, label);
      اگر (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	واپس;
    }
  ورنہ
    {
      c_parser_error (parser, "expected goto expression");
      واپس;
    }

  اگر (c_parser_اگلا_token_is_keyword (parser, RID_ELSE))
    c_parser_consume_token (parser);
  ورنہ
    {
      c_parser_error (parser, "expected else statement");
      واپس;
    }

  اگر (c_parser_اگلا_token_is_keyword (parser, RID_GOTO))
    {
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      اگر (! c_parser_اگلا_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected label");
	  واپس;
	}
      label = c_parser_peek_token (parser)->قدر;
      c_parser_consume_token (parser);
      صحیح dest_اشاریہ;
      profile_probability prob;
      اگر ((cfun->curr_properties & PROP_cfg)
	  && c_parser_gimple_parse_bb_spec_کنارہ_probability (label, parser,
							     &dest_اشاریہ, &prob))
	parser.ڈالو_کنارہ (parser.current_bb->اشاریہ, dest_اشاریہ,
			  کنارہ_FALSE_قدر, prob);
      ورنہ
	f_label = lookup_label_for_goto (loc, label);
      اگر (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	واپس;
    }
  ورنہ
    {
      c_parser_error (parser, "expected goto expression");
      واپس;
    }

  اگر (cond != error_mark_گرہ)
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

ساکن خالی
c_parser_gimple_switch_stmt (gimple_parser &parser, gimple_seq *seq)
{
  c_اظہاریہ cond_اظہاریہ;
  درخت case_label, label;
  auto_vec<درخت> labels;
  درخت default_label = NULL_درخت;
  c_parser_consume_token (parser);

  اگر (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    واپس;
  cond_اظہاریہ = c_parser_gimple_postfix_عبارت (parser);
  اگر (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    واپس;

  اگر (! c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    واپس;

  جب (c_parser_اگلا_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      اگر (c_parser_اگلا_token_is (parser, CPP_EOF))
	{
	  c_parser_error (parser, "expected statement");
	  واپس;
	}

      انتخاب (c_parser_peek_token (parser)->keyword)
	{
	حالت RID_CASE:
	  {
	    c_اظہاریہ exp1;
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);

	    اگر (c_parser_اگلا_token_is (parser, CPP_NAME)
		|| c_parser_peek_token (parser)->type == CPP_نمبر)
	      exp1 = c_parser_gimple_postfix_عبارت (parser);
	    ورنہ
	      {
		c_parser_error (parser, "expected expression");
		واپس;
	      }

	    اگر (c_parser_اگلا_token_is (parser, CPP_COLON))
	      {
		c_parser_consume_token (parser);
		اگر (c_parser_اگلا_token_is (parser, CPP_NAME))
		  {
		    label = c_parser_peek_token (parser)->قدر;
		    c_parser_consume_token (parser);
		    درخت decl = lookup_label_for_goto (loc, label);
		    case_label = build_case_label (exp1.قدر, NULL_درخت,
						   decl);
		    labels.محفوظ_ڈالو (case_label);
		    اگر (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      واپس;
		  }
		ورنہ اگر (! c_parser_require (parser, CPP_NAME,
					     "expected label"))
		  واپس;
	      }
	    ورنہ اگر (! c_parser_require (parser, CPP_SEMICOLON,
					 "expected %<:%>"))
	      واپس;
	    توڑو;
	  }
	حالت RID_DEFAULT:
	  {
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);
	    اگر (c_parser_اگلا_token_is (parser, CPP_COLON))
	      {
		c_parser_consume_token (parser);
		اگر (c_parser_اگلا_token_is (parser, CPP_NAME))
		  {
		    label = c_parser_peek_token (parser)->قدر;
		    c_parser_consume_token (parser);
		    درخت decl = lookup_label_for_goto (loc, label);
		    default_label = build_case_label (NULL_درخت, NULL_درخت,
						      decl);
		    اگر (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      واپس;
		  }
		ورنہ اگر (! c_parser_require (parser, CPP_NAME,
					     "expected label"))
		  واپس;
	      }
	    ورنہ اگر (! c_parser_require (parser, CPP_SEMICOLON,
					 "expected %<:%>"))
	      واپس;
	    توڑو;
	  }
	طےشدہ:
	  c_parser_error (parser, "expected case label");
	  واپس;
	}

    }
  اگر (! c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>"))
    واپس;

  اگر (cond_اظہاریہ.قدر != error_mark_گرہ)
    {
      gswitch *s = gimple_build_switch (cond_اظہاریہ.قدر, default_label, labels);
      gimple_seq_جوڑو_stmt_without_update (seq, s);
    }
}

/* Parse gimple return statement.  */

ساکن خالی
c_parser_gimple_return_stmt (gimple_parser &parser, gimple_seq *seq)
{
  location_t loc = c_parser_peek_token (parser)->location;
  gimple *ret = تہی;
  c_parser_consume_token (parser);
  اگر (c_parser_اگلا_token_is (parser, CPP_SEMICOLON))
    {
      c_اختتام_gimple_return (loc, NULL_درخت);
      ret = gimple_build_return (تہی);
      gimple_seq_جوڑو_stmt_without_update (seq, ret);
    }
  ورنہ
    {
      location_t xloc = c_parser_peek_token (parser)->location;
      c_اظہاریہ اظہاریہ = c_parser_gimple_unary_عبارت (parser);
      اگر (اظہاریہ.قدر != error_mark_گرہ)
	{
	  c_اختتام_gimple_return (xloc, اظہاریہ.قدر);
	  ret = gimple_build_return (اظہاریہ.قدر);
	  gimple_seq_جوڑو_stmt_without_update (seq, ret);
	}
    }
}

/* Support function for c_parser_gimple_return_stmt.  */

ساکن خالی
c_اختتام_gimple_return (location_t loc, درخت retval)
{
  درخت valtype = درخت_TYPE (درخت_TYPE (current_function_decl));

  /* Use the expansion point to handle cases such as returning NULL
     in a function returning void.  */
  location_t xloc = expansion_نقطہ_location_if_اندر_system_سرخی (loc);

  اگر (درخت_THIS_VOLATILE (current_function_decl))
    warning_at (xloc, 0,
		"function declared %<noreturn%> has a %<return%> statement");

  اگر (! retval)
    current_function_returns_null = 1;
  ورنہ اگر (valtype == 0 || VOID_TYPE_P (valtype))
    {
      current_function_returns_null = 1;
      اگر (درخت_رمز (درخت_TYPE (retval)) != VOID_TYPE)
	{
	  error_at
	    (xloc, "%<return%> with a value, in function returning void");
	  inform (DECL_ماخذ_LOCATION (current_function_decl),
		  "declared here");
	}
    }
  ورنہ اگر (درخت_رمز (valtype) != درخت_رمز (درخت_TYPE (retval)))
    {
      error_at
	(xloc, "invalid conversion in return statement");
      inform (DECL_ماخذ_LOCATION (current_function_decl),
	      "declared here");
    }
  واپس;
}
