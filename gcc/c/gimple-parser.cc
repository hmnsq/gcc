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

#అన్తర్భావ "config.h"
#అన్తర్భావ "system.h"
#అన్తర్భావ "coretypes.h"
#అన్తర్భావ "target.h"
#అన్తర్భావ "function.h"
#అన్తర్భావ "c-tree.h"
#అన్తర్భావ "timevar.h"
#అన్తర్భావ "stringpool.h"
#అన్తర్భావ "cgraph.h"
#అన్తర్భావ "attribs.h"
#అన్తర్భావ "stor-layout.h"
#అన్తర్భావ "varasm.h"
#అన్తర్భావ "trans-mem.h"
#అన్తర్భావ "c-family/c-pragma.h"
#అన్తర్భావ "c-lang.h"
#అన్తర్భావ "c-family/c-objc.h"
#అన్తర్భావ "plugin.h"
#అన్తర్భావ "builtins.h"
#అన్తర్భావ "gomp-constants.h"
#అన్తర్భావ "c-family/c-indentation.h"
#అన్తర్భావ "gimple-expr.h"
#అన్తర్భావ "context.h"
#అన్తర్భావ "gcc-rich-location.h"
#అన్తర్భావ "c-parser.h"
#అన్తర్భావ "tree-vrp.h"
#అన్తర్భావ "tree-pass.h"
#అన్తర్భావ "tree-pretty-print.h"
#అన్తర్భావ "tree.h"
#అన్తర్భావ "basic-block.h"
#అన్తర్భావ "gimple.h"
#అన్తర్భావ "gimple-pretty-print.h"
#అన్తర్భావ "tree-ssa.h"
#అన్తర్భావ "pass_manager.h"
#అన్తర్భావ "tree-ssanames.h"
#అన్తర్భావ "gimple-ssa.h"
#అన్తర్భావ "tree-dfa.h"
#అన్తర్భావ "internal-fn.h"
#అన్తర్భావ "cfg.h"
#అన్తర్భావ "cfghooks.h"
#అన్తర్భావ "bitmap.h"
#అన్తర్భావ "cfganal.h"
#అన్తర్భావ "tree-cfg.h"
#అన్తర్భావ "gimple-iterator.h"
#అన్తర్భావ "cfgloop.h"
#అన్తర్భావ "tree-phinodes.h"
#అన్తర్భావ "tree-into-ssa.h"


/* GIMPLE parser state.  */

తరగతి gimple_parser
{
బహిరంగ:
  gimple_parser (c_parser *p) : parser (p), అంచులు(), current_bb(ఖాళీ) {}
  /* c_parser is not visible here, use composition and fake inheritance
     via a conversion operator.  */
  క్రియాకారకం c_parser *() { తిరిగి parser; }
  c_parser *parser;

  /* CFG build state.  */
  తరగతి gimple_parser_అంచు
  {
  బహిరంగ:
    పూర్ణాంకం src;
    పూర్ణాంకం dest;
    పూర్ణాంకం flags;
    profile_probability probability;
  };
  auto_vec<gimple_parser_అంచు> అంచులు;
  basic_ఖండం current_bb;

  శూన్య నెట్టు_అంచు (పూర్ణాంకం, పూర్ణాంకం, పూర్ణాంకం, profile_probability);
};

శూన్య
gimple_parser::నెట్టు_అంచు (పూర్ణాంకం src, పూర్ణాంకం dest, పూర్ణాంకం flags,
			  profile_probability prob)
{
  gimple_parser_అంచు e;
  e.src = src;
  e.dest = dest;
  e.flags = flags;
  e.probability = prob;
  అంచులు.సురక్షిత_నెట్టు (e);
}


/* Gimple parsing functions.  */
స్థిర తార్కిక c_parser_gimple_compound_statement (gimple_parser &, gimple_seq *);
స్థిర శూన్య c_parser_gimple_label (gimple_parser &, gimple_seq *);
స్థిర శూన్య c_parser_gimple_statement (gimple_parser &, gimple_seq *);
స్థిర నిర్మాణం c_సమాసం c_parser_gimple_ద్విమాన_వ్యక్తీకరణ (gimple_parser &, వృక్షం);
స్థిర నిర్మాణం c_సమాసం c_parser_gimple_unary_వ్యక్తీకరణ (gimple_parser &);
స్థిర నిర్మాణం c_సమాసం c_parser_gimple_postfix_వ్యక్తీకరణ
			(gimple_parser &, వృక్షం = error_mark_కణుపు);
స్థిర నిర్మాణం c_సమాసం c_parser_gimple_postfix_వ్యక్తీకరణ_after_primary
			(gimple_parser &, location_t, నిర్మాణం c_సమాసం);
స్థిర శూన్య c_parser_gimple_declaration (gimple_parser &);
స్థిర శూన్య c_parser_gimple_goto_stmt (gimple_parser &, location_t,
				       వృక్షం, gimple_seq *);
స్థిర శూన్య c_parser_gimple_try_stmt (gimple_parser &, gimple_seq *);
స్థిర శూన్య c_parser_gimple_if_stmt (gimple_parser &, gimple_seq *);
స్థిర శూన్య c_parser_gimple_switch_stmt (gimple_parser &, gimple_seq *);
స్థిర శూన్య c_parser_gimple_return_stmt (gimple_parser &, gimple_seq *);
స్థిర శూన్య c_ముగింపు_gimple_return (location_t, వృక్షం);
స్థిర వృక్షం c_parser_gimple_paren_condition (gimple_parser &);
స్థిర శూన్య c_parser_gimple_సమాసం_list (gimple_parser &, vec<వృక్షం> *);


/* Much like parser_build_unary_op, but avoid applying default conversions.  */

స్థిర c_సమాసం
gimple_parser_build_unary_op (location_t loc,
			      గణన వృక్షం_సంకేతం_2 సంకేతం_2, నిర్మాణం c_సమాసం arg)
{
  నిర్మాణం c_సమాసం ఫలితం;

  ఫలితం.original_సంకేతం = సంకేతం_2;
  ఫలితం.original_type = ఖాళీ;
  ఫలితం.m_decimal = 0;

  ఒకవేళ (reject_gcc_builtin (arg.విలువ))
    {
      ఫలితం.విలువ = error_mark_కణుపు;
    }
  లేకపోతే
    {
      ఫలితం.విలువ = build_unary_op (loc, సంకేతం_2, arg.విలువ, నిజం);

      ఒకవేళ (వృక్షం_అధికప్రవాహం_P (ఫలితం.విలువ) && !వృక్షం_అధికప్రవాహం_P (arg.విలువ))
	అధికప్రవాహం_warning (loc, ఫలితం.విలువ, arg.విలువ);
    }

  /* We are typically called when parsing a prefix token at LOC acting on
     ARG.  Reflect this by updating the source range of the result to
     start at LOC and end at the end of ARG.  */
  సమితి_c_సమాసం_ఆధారం_range (&ఫలితం,
			   loc, arg.get_ముగింపు ());

  తిరిగి ఫలితం;
}

/* See if VAL is an identifier matching __BB<num> and return <num>
   in *INDEX.  */

స్థిర తార్కిక
c_parser_gimple_parse_bb_spec (వృక్షం val, పూర్ణాంకం *సూచీ)
{
  ఒకవేళ (!startswith (IDENTIFIER_సూచిక (val), "__BB"))
    తిరిగి అబద్ధం;

  స్థిరరాశి అక్షరం *bb = IDENTIFIER_సూచిక (val) + 4;
  ఒకవేళ (! ISDIGIT (*bb))
    తిరిగి అబద్ధం;

  అక్షరం *pend;
  errno = 0;
  స్థిరరాశి గుర్తులేని దీర్ఘ సంఖ్య = strtoul (bb, &pend, 10);
  ఒకవేళ (errno == ERANGE
      || *pend != '\0'
      || సంఖ్య > గరిష్ఠ_పూర్ణాంకం)
    తిరిగి అబద్ధం;

  *సూచీ = సంఖ్య;
  తిరిగి నిజం;
}

/* See if VAL is an identifier matching __BB<num> and return <num>
   in *INDEX.  Return true if so and parse also FREQUENCY of
   the edge.  */


స్థిర తార్కిక
c_parser_gimple_parse_bb_spec_అంచు_probability (వృక్షం val,
						gimple_parser &parser,
						పూర్ణాంకం *సూచీ,
						profile_probability
						*probability)
{
  తార్కిక return_p = c_parser_gimple_parse_bb_spec (val, సూచీ);
  ఒకవేళ (return_p)
    {
      *probability = profile_probability::uninitialized ();
      /* Parse frequency if provided.  */
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_OPEN_PAREN))
	{
	  వృక్షం f;
	  c_parser_consume_token (parser);
	  ఒకవేళ (!c_parser_తదుపరి_token_is (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected frequency quality");
	      తిరిగి అబద్ధం;
	    }

	  profile_quality quality;
	  స్థిరరాశి అక్షరం *v
	    = IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ);
	  ఒకవేళ (!parse_profile_quality (v, &quality))
	    {
	      c_parser_error (parser, "unknown profile quality");
	      తిరిగి అబద్ధం;
	    }

	  c_parser_consume_token (parser);
	  ఒకవేళ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    తిరిగి అబద్ధం;

	  ఒకవేళ (!c_parser_తదుపరి_token_is (parser, CPP_సంఖ్య)
	      || (వృక్షం_సంకేతం (f = c_parser_peek_token (parser)->విలువ)
		  != INTEGER_CST))
	    {
	      c_parser_error (parser, "expected frequency value");
	      తిరిగి అబద్ధం;
	    }

	  గుర్తులేని పూర్ణాంకం విలువ = వృక్షం_INT_CST_దిగువ (f);
	  *probability = profile_probability (విలువ, quality);

	  c_parser_consume_token (parser);
	  ఒకవేళ (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    తిరిగి అబద్ధం;

	  ఒకవేళ (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    తిరిగి అబద్ధం;
	}

      తిరిగి నిజం;
    }

  తిరిగి అబద్ధం;

}

/* Parse the body of a function declaration marked with "__GIMPLE".  */

శూన్య
c_parser_parse_gimple_body (c_parser *cparser, అక్షరం *gimple_pass,
			    గణన c_declspec_il cdil,
			    profile_లెక్క నమోదు_bb_లెక్క)
{
  gimple_parser parser (cparser);
  gimple_seq seq = ఖాళీ;
  gimple_seq body = ఖాళీ;
  వృక్షం stmt = నెట్టు_stmt_list ();
  నెట్టు_scope ();
  location_t loc1 = c_parser_peek_token (parser)->location;

  cfun->pass_startwith = gimple_pass;
  init_వృక్షం_ssa (cfun);

  ఒకవేళ (cdil == cdil_gimple)
    /* While we have SSA names in the IL we do not have a CFG built yet
       and PHIs are represented using a PHI internal function.  We do
       have lowered control flow and exception handling (well, we do not
       have parser support for EH yet).  But as we still have BINDs
       we have to go through lowering again.  */
    cfun->curr_properties = PROP_gimple_any;
  లేకపోతే
    {
      /* We have at least cdil_gimple_cfg.  */
      gimple_రిజిస్టరు_cfg_hooks ();
      init_ఖాళీలు_వృక్షం_cfg ();
      parser.current_bb = నమోదు_ఖండం_PTR_FOR_FN (cfun);
      /* Initialize the bare loop structure - we are going to only
         mark headers and leave the rest to fixup.  */
      సమితి_loops_for_fn (cfun, ggc_cleared_alloc<నిర్మాణం loops> ());
      init_loops_structure (cfun, loops_for_fn (cfun), 1);
      loops_state_సమితి (cfun, LOOPS_NEED_FIXUP|LOOPS_MAY_HAVE_గుణిజం_LATCHES);
      cfun->curr_properties
	|= PROP_gimple_lcf | PROP_gimple_leh | PROP_cfg | PROP_loops;
      ఒకవేళ (cdil == cdil_gimple_ssa)
	{
	  init_ssa_operands (cfun);
	  cfun->curr_properties |= PROP_ssa;
	}
    }

  ఒకవేళ (! c_parser_gimple_compound_statement (parser, &seq)
      && cdil == cdil_gimple)
    {
      gimple *ret = gimple_build_return (ఖాళీ);
      gimple_seq_కూడు_stmt_without_update (&seq, ret);
    }

  వృక్షం ఖండం = తీయి_scope ();
  stmt = తీయి_stmt_list (stmt);
  stmt = c_build_bind_సమాసం (loc1, ఖండం, stmt);

  ఖండం = DECL_INITIAL (current_function_decl);
  ఖండం_SUBBLOCKS (ఖండం) = NULL_వృక్షం;
  ఖండం_CHAIN (ఖండం) = NULL_వృక్షం;
  వృక్షం_ASM_WRITTEN (ఖండం) = 1;

  ఒకవేళ (cdil == cdil_gimple)
    {
      gbind *bind_stmt = gimple_build_bind (BIND_సమాసం_VARS (stmt), ఖాళీ,
					    BIND_సమాసం_ఖండం (stmt));
      gimple_bind_సమితి_body (bind_stmt, seq);
      gimple_seq_కూడు_stmt_without_update (&body, bind_stmt);
      gimple_సమితి_body (current_function_decl, body);
    }
  లేకపోతే
    {
      /* Control-flow and binds are lowered, record local decls.  */
      కొరకు (వృక్షం var = BIND_సమాసం_VARS (stmt); var; var = DECL_CHAIN (var))
	ఒకవేళ (VAR_P (var)
	    && !DECL_EXTERNAL (var))
	  {
	    కూడు_local_decl (cfun, var);
	    /* When the middle-end re-gimplifies any expression we might
	       run into the assertion that we've seen the decl in a BIND.  */
	    ఒకవేళ (!వృక్షం_STATIC (var))
	      DECL_చూసిన_లోపల_BIND_సమాసం_P (var) = 1;
	  }
      /* We have a CFG.  Build the edges.  */
      కొరకు (గుర్తులేని i = 0; i < parser.అంచులు.నిడివి (); ++i)
	{
	  అంచు e = make_అంచు (BASIC_ఖండం_FOR_FN (cfun, parser.అంచులు[i].src),
			      BASIC_ఖండం_FOR_FN (cfun, parser.అంచులు[i].dest),
			      parser.అంచులు[i].flags);
	  e->probability = parser.అంచులు[i].probability;
	}
      /* Add edges for case labels.  */
      basic_ఖండం bb;
      FOR_EACH_BB_FN (bb, cfun)
	ఒకవేళ (అంచు_లెక్క (bb->succs) == 0)
	  {
	    ఒకవేళ (gswitch *sw = సురక్షిత_dyn_cast <gswitch *> (*gsi_చివరి_bb (bb)))
	      కొరకు (గుర్తులేని i = 0; i < gimple_switch_అంకె_labels (sw); ++i)
		{
		  basic_ఖండం label_bb = gimple_switch_label_bb (cfun, sw, i);
		  make_అంచు (bb, label_bb, 0);
		}
	  }
      /* Need those for loop fixup.  */
      calculate_dominance_info (CDI_DOMINATORS);
      /* With SSA lower PHIs parsed as internal function calls and
	 update stmts.  */
      ఒకవేళ (cdil == cdil_gimple_ssa)
	{
	  /* Create PHI nodes, they are parsed into __PHI internal calls
	     and update SSA operands.  */
	  FOR_EACH_BB_FN (bb, cfun)
	    {
	      gimple_stmt_iterator gsi;
	      కొరకు (gsi = gsi_ప్రారంభం_bb (bb); !gsi_చివర_p (gsi);)
		{
		  gimple *stmt = gsi_stmt (gsi);
		  ఒకవేళ (!gimple_call_అంతర్గత_p (stmt, IFN_PHI))
		    ఆపు;

		  gphi *phi = create_phi_కణుపు (gimple_call_lhs (stmt), bb);
		  కొరకు (గుర్తులేని i = 0; i < gimple_call_అంకె_వాదనలు (stmt); i += 2)
		    {
		      పూర్ణాంకం srcidx = వృక్షం_INT_CST_దిగువ (gimple_call_arg (stmt, i));
		      అంచు e = కనుగొను_అంచు (BASIC_ఖండం_FOR_FN (cfun, srcidx), bb);
		      ఒకవేళ (!e)
			c_parser_error (parser, "edge not found");
		      లేకపోతే
			కూడు_phi_arg (phi, gimple_call_arg (stmt, i + 1), e,
				     UNKNOWN_LOCATION);
		    }
		  gsi_remove (&gsi, నిజం);
		}
	      కొరకు (; !gsi_చివర_p (gsi); gsi_తదుపరి (&gsi))
		update_stmt (gsi_stmt (gsi));
	    }
	  /* Fill SSA name gaps, putting them on the freelist and diagnose
	     SSA names without definition.  */
	  కొరకు (గుర్తులేని i = 1; i < అంకె_ssa_పేర్లు; ++i)
	    ఒకవేళ (!ssa_name (i))
	      {
		వృక్షం name = make_ssa_name_fn (cfun, integer_type_కణుపు, ఖాళీ, i);
		release_ssa_name_fn (cfun, name);
	      }
	    లేకపోతే ఒకవేళ (!SSA_NAME_DEF_STMT (ssa_name (i)))
	      error ("SSA name %qE with version %d has no definition",
		     ssa_name (i), i);
	  /* No explicit virtual operands (yet).  */
	  bitmap_obstack_initialize (ఖాళీ);
	  update_ssa (TODO_update_ssa_only_virtuals);
	  bitmap_obstack_release (ఖాళీ);
	  /* ???  By flushing the freelist after virtual operand SSA rewrite
	     we keep the gaps available for re-use like needed for the
	     PR89595 testcase but then usually virtual operands would have
	     taken most of them.  The fix is obviously to make virtual
	     operands explicit in the SSA IL.  */
	  flush_ssaname_freelist ();
	}
      fix_loop_structure (ఖాళీ);
    }

  ఒకవేళ (cfun->curr_properties & PROP_cfg)
    {
      నమోదు_ఖండం_PTR_FOR_FN (cfun)->లెక్క = నమోదు_bb_లెక్క;
      gcov_type t = param_gimple_fe_computed_hot_bb_పరిమితి;
      సమితి_hot_bb_పరిమితి (t);
      update_max_bb_లెక్క ();
      cgraph_కణుపు::get_create (cfun->decl);
      cgraph_అంచు::rebuild_అంచులు ();
    }

  /* Perform IL validation and if any error is found abort compilation
     of this function by zapping its body.  */
  ఒకవేళ ((cfun->curr_properties & PROP_cfg)
      && verify_gimple_లోపల_cfg (cfun, అబద్ధం, అబద్ధం))
    init_ఖాళీలు_వృక్షం_cfg ();
  లేకపోతే ఒకవేళ (!(cfun->curr_properties & PROP_cfg)
	   && verify_gimple_లోపల_seq (gimple_body (current_function_decl), అబద్ధం))
    gimple_సమితి_body (current_function_decl, ఖాళీ);

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

స్థిర తార్కిక
c_parser_gimple_compound_statement (gimple_parser &parser, gimple_seq *seq)
{
  తార్కిక return_p = అబద్ధం;

  ఒకవేళ (! c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    తిరిగి అబద్ధం;

  /* A compound statement starts with optional declarations.  */
  అయితే (c_parser_తదుపరి_టోకెన్లు_ప్రారంభం_declaration (parser))
    {
      c_parser_gimple_declaration (parser);
      ఒకవేళ (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	తిరిగి అబద్ధం;
    }

  అయితే (c_parser_తదుపరి_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      ఒకవేళ (c_parser_error (parser))
	{
	  c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_BRACE, ఖాళీ);
	  తిరిగి return_p;
	}
      లేకపోతే ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_EOF))
	{
	  c_parser_error (parser, "expected declaration or statement");
	  తిరిగి return_p;
	}

      ఎంపిక (c_parser_peek_token (parser)->type)
	{
	స్థితి CPP_KEYWORD:
	  ఎంపిక (c_parser_peek_token (parser)->keyword)
	    {
	    స్థితి RID_AT_TRY:
	      c_parser_gimple_try_stmt (parser, seq);
	      ఆపు;
	    స్థితి RID_IF:
	      c_parser_gimple_if_stmt (parser, seq);
	      ఆపు;
	    స్థితి RID_SWITCH:
	      c_parser_gimple_switch_stmt (parser, seq);
	      ఆపు;
	    స్థితి RID_GOTO:
	      {
		location_t loc = c_parser_peek_token (parser)->location;
		c_parser_consume_token (parser);
		ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME))
		  {
		    వృక్షం label = c_parser_peek_token (parser)->విలువ;
		    c_parser_consume_token (parser);
		    c_parser_gimple_goto_stmt (parser, loc, label, seq);
		    ఒకవేళ (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      తిరిగి return_p;
		  }
		}
	      ఆపు;
	    స్థితి RID_RETURN:
	      return_p = నిజం;
	      c_parser_gimple_return_stmt (parser, seq);
	      ఒకవేళ (! c_parser_require (parser, CPP_SEMICOLON,
				      "expected %<;%>"))
		తిరిగి return_p;
	      ఒకవేళ (cfun->curr_properties & PROP_cfg)
		parser.నెట్టు_అంచు (parser.current_bb->సూచీ, EXIT_ఖండం, 0,
				  profile_probability::uninitialized ());
	      ఆపు;
	    అప్రమేయ:
	      వెళ్ళు సమాసం_stmt;
	    }
	  ఆపు;
	స్థితి CPP_NAME:
	  ఒకవేళ (c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_gimple_label (parser, seq);
	      ఆపు;
	    }
	  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME)
	      && c_parser_peek_token (parser)->id_రకం == C_ID_ID
	      && strcmp (IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ),
			 "try") == 0)
	    {
	      c_parser_gimple_try_stmt (parser, seq);
	      ఆపు;
	    }
	  /* Basic block specification.
	     __BB (index, ...)  */
	  ఒకవేళ ((cfun->curr_properties & PROP_cfg)
	      && !strcmp (IDENTIFIER_సూచిక
			    (c_parser_peek_token (parser)->విలువ), "__BB"))
	    {
	      c_parser_consume_token (parser);
	      ఒకవేళ (! c_parser_require (parser, CPP_OPEN_PAREN,
				      "expected %<(%>"))
		తిరిగి return_p;
	      ఒకవేళ (c_parser_తదుపరి_token_is_not (parser, CPP_సంఖ్య))
		{
		  c_parser_error (parser, "expected block index");
		  తిరిగి return_p;
		}
	      వృక్షం tnum = c_parser_peek_token (parser)->విలువ;
	      ఒకవేళ (వృక్షం_సంకేతం (tnum) != INTEGER_CST)
		{
		  c_parser_error (parser, "expected block index");
		  తిరిగి return_p;
		}
	      పూర్ణాంకం సూచీ = వృక్షం_INT_CST_దిగువ (tnum);
	      ఒకవేళ (సూచీ < అంకె_FIXED_ఖండాలు
		  || (సూచీ < చివరి_basic_ఖండం_for_fn (cfun)
		      && BASIC_ఖండం_FOR_FN (cfun, సూచీ) != ఖాళీ))
		{
		  c_parser_error (parser, "invalid block index");
		  తిరిగి return_p;
		}
	      పూర్ణాంకం is_loop_శీర్షిక_యొక్క = -1;
	      profile_లెక్క bb_లెక్క = profile_లెక్క::uninitialized ();
	      c_parser_consume_token (parser);
	      అయితే (c_parser_తదుపరి_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  ఒకవేళ (! c_parser_తదుపరి_token_is (parser, CPP_NAME))
		    {
		      c_parser_error (parser, "expected block specifier");
		      తిరిగి return_p;
		    }
		  /* loop_header (NUM)  */
		  ఒకవేళ (!strcmp (IDENTIFIER_సూచిక
			         (c_parser_peek_token (parser)->విలువ),
			       "loop_header"))
		    {
		      c_parser_consume_token (parser);
		      ఒకవేళ (! c_parser_require (parser, CPP_OPEN_PAREN,
					      "expected %<(%>"))
			తిరిగి return_p;
		      వృక్షం loop_అంకె;
		      ఒకవేళ (! c_parser_తదుపరి_token_is (parser, CPP_సంఖ్య)
			  || వృక్షం_సంకేతం (loop_అంకె
					  = c_parser_peek_token (parser)->విలువ)
			       != INTEGER_CST)
			{
			  c_parser_error (parser, "expected loop number");
			  తిరిగి return_p;
			}
		      c_parser_consume_token (parser);
		      is_loop_శీర్షిక_యొక్క = వృక్షం_INT_CST_దిగువ (loop_అంకె);
		      ఒకవేళ (! c_parser_require (parser, CPP_CLOSE_PAREN,
					      "expected %<)%>"))
			తిరిగి return_p;
		    }
		  /* Parse profile: quality(value) */
		  లేకపోతే
		    {
		      వృక్షం q;
		      profile_quality quality;
		      వృక్షం v = c_parser_peek_token (parser)->విలువ;
		      ఒకవేళ (!parse_profile_quality (IDENTIFIER_సూచిక (v),
						  &quality))
			{
			  c_parser_error (parser, "unknown block specifier");
			  తిరిగి అబద్ధం;
			}

		      c_parser_consume_token (parser);
		      ఒకవేళ (!c_parser_require (parser, CPP_OPEN_PAREN,
					     "expected %<(%>"))
			తిరిగి అబద్ధం;

		      ఒకవేళ (!c_parser_తదుపరి_token_is (parser, CPP_సంఖ్య)
			  || (వృక్షం_సంకేతం (q = c_parser_peek_token (parser)->విలువ)
			      != INTEGER_CST))
			{
			  c_parser_error (parser, "expected count value");
			  తిరిగి అబద్ధం;
			}

		      bb_లెక్క
			= profile_లెక్క::from_gcov_type (వృక్షం_INT_CST_దిగువ (q),
							 quality);
		      c_parser_consume_token (parser);
		      ఒకవేళ (! c_parser_require (parser, CPP_CLOSE_PAREN,
					      "expected %<)%>"))
			తిరిగి return_p;
		    }
		}
	      ఒకవేళ (! c_parser_require (parser, CPP_CLOSE_PAREN,
				      "expected %<)%>")
		  || ! c_parser_require (parser, CPP_COLON,
					 "expected %<:%>"))
		తిరిగి return_p;

	      /* Put stmts parsed in the current block.  */
	      ఒకవేళ (!gimple_seq_ఖాళీలు_p (*seq))
		{
		  ఒకవేళ (!parser.current_bb)
		    c_parser_error (parser, "stmts without block");
		  లేకపోతే
		    {
		      gimple_stmt_iterator gsi
			= gsi_ప్రారంభం_bb (parser.current_bb);
		      gsi_చొప్పించు_seq_after_without_update (&gsi, *seq,
							   GSI_CONTINUE_LINKING);
		    }
		  *seq = ఖాళీ;
		}

	      /* Build an empty block with specified index, linking them
		 in source order.  */
	      basic_ఖండం bb = alloc_ఖండం ();
	      bb->సూచీ = సూచీ;
	      link_ఖండం (bb, (parser.current_bb ? parser.current_bb
			       : నమోదు_ఖండం_PTR_FOR_FN (cfun)));
	      ఒకవేళ (basic_ఖండం_info_for_fn (cfun)->నిడివి () <= (కొలత_t)సూచీ)
		vec_సురక్షిత_grow_cleared (basic_ఖండం_info_for_fn (cfun),
				       సూచీ + 1, నిజం);
	      సమితి_BASIC_ఖండం_FOR_FN (cfun, సూచీ, bb);
	      ఒకవేళ (చివరి_basic_ఖండం_for_fn (cfun) <= సూచీ)
		చివరి_basic_ఖండం_for_fn (cfun) = సూచీ + 1;
	      n_basic_ఖండాలు_for_fn (cfun)++;
	      ఒకవేళ (parser.current_bb->సూచీ == నమోదు_ఖండం)
		parser.నెట్టు_అంచు (నమోదు_ఖండం, bb->సూచీ, అంచు_FALLTHRU,
				  profile_probability::always ());

	      /* We leave the proper setting to fixup.  */
	      తరగతి loop *loop_father = loops_for_fn (cfun)->వృక్షం_మూలం;
	      /* If the new block is a loop header, allocate a loop
		 struct.  Fixup will take care of proper placement within
		 the loop tree.  */
	      ఒకవేళ (is_loop_శీర్షిక_యొక్క != -1)
		{
		  ఒకవేళ (సంఖ్య_యొక్క_loops (cfun) > (గుర్తులేని)is_loop_శీర్షిక_యొక్క
		      && get_loop (cfun, is_loop_శీర్షిక_యొక్క) != ఖాళీ)
		    {
		      c_parser_error (parser, "duplicate loop header");
		    }
		  లేకపోతే
		    {
		      తరగతి loop *loop = alloc_loop ();
		      loop->అంకె = is_loop_శీర్షిక_యొక్క;
		      loop->శీర్షిక = bb;
		      ఒకవేళ (సంఖ్య_యొక్క_loops (cfun) <= (గుర్తులేని)is_loop_శీర్షిక_యొక్క)
			vec_సురక్షిత_grow_cleared (loops_for_fn (cfun)->larray,
					       is_loop_శీర్షిక_యొక్క + 1, నిజం);
		      (*loops_for_fn (cfun)->larray)[is_loop_శీర్షిక_యొక్క] = loop;
		      flow_loop_వృక్షం_కణుపు_కూడు (loops_for_fn (cfun)->వృక్షం_మూలం,
					       loop);
		    }
		  loop_father = get_loop (cfun, is_loop_శీర్షిక_యొక్క);
		}
	      bb->loop_father = loop_father;
	      bb->లెక్క = bb_లెక్క;

	      /* Stmts now go to the new block.  */
	      parser.current_bb = bb;
	      ఆపు;
	    }
	  వెళ్ళు సమాసం_stmt;

	స్థితి CPP_SEMICOLON:
	  {
	    /* Empty stmt.  */
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);
	    gimple *nop = gimple_build_nop ();
	    gimple_సమితి_location (nop, loc);
	    gimple_seq_కూడు_stmt_without_update (seq, nop);
	    ఆపు;
	  }

	స్థితి CPP_CLOSE_PAREN:
	స్థితి CPP_CLOSE_వర్గం:
	  /* Avoid infinite loop in error recovery:
	     c_parser_skip_until_found stops at a closing nesting
	     delimiter without consuming it, but here we need to consume
	     it to proceed further.  */
	  c_parser_error (parser, "expected statement");
	  c_parser_consume_token (parser);
	ఆపు;

	అప్రమేయ:
సమాసం_stmt:
	  c_parser_gimple_statement (parser, seq);
	  ఒకవేళ (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	    c_parser_skip_until_దొరికింది (parser, CPP_SEMICOLON, ఖాళీ);
	}
    }
  c_parser_consume_token (parser);

  /* Put stmts parsed in the current block.  */
  ఒకవేళ ((cfun->curr_properties & PROP_cfg)
      && !gimple_seq_ఖాళీలు_p (*seq))
    {
      ఒకవేళ (!parser.current_bb)
	c_parser_error (parser, "stmts without block");
      లేకపోతే
	{
	  gimple_stmt_iterator gsi = gsi_ప్రారంభం_bb (parser.current_bb);
	  gsi_చొప్పించు_seq_after_without_update (&gsi, *seq,
					       GSI_CONTINUE_LINKING);
	}
      *seq = ఖాళీ;
    }

  తిరిగి return_p;
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

స్థిర శూన్య
c_parser_gimple_statement (gimple_parser &parser, gimple_seq *seq)
{
  నిర్మాణం c_సమాసం lhs, rhs;
  gimple *కేటాయించు = ఖాళీ;
  location_t loc;
  వృక్షం arg = NULL_వృక్షం;
  auto_vec<వృక్షం> vargs;

  lhs = c_parser_gimple_unary_వ్యక్తీకరణ (parser);
  loc = సమాసం_LOCATION (lhs.విలువ);
  rhs.సమితి_error ();

  /* GIMPLE call statement without LHS.  */
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_SEMICOLON)
      && వృక్షం_సంకేతం (lhs.విలువ) == CALL_సమాసం)
    {
      gimple *call;
      call = gimple_build_call_from_వృక్షం (lhs.విలువ, ఖాళీ);
      gimple_seq_కూడు_stmt_without_update (seq, call);
      gimple_సమితి_location (call, loc);
      తిరిగి;
    }

  /* All following cases are statements with LHS.  */
  ఒకవేళ (! c_parser_require (parser, CPP_EQ, "expected %<=%>"))
    తిరిగి;

  /* Eat and ignore {v} right after the =, the has_volatile_ops is
     redundant and re-computed by the operand scanner.  */
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_OPEN_BRACE)
      && !(c_parser_peek_token (parser)->flags & PREV_WHITE)
      && c_parser_peek_2nd_token (parser)->type == CPP_NAME
      && !(c_parser_peek_2nd_token (parser)->flags & PREV_WHITE)
      && strcmp ("v", IDENTIFIER_సూచిక
			(c_parser_peek_2nd_token (parser)->విలువ)) == 0
      && c_parser_peek_nth_token (parser, 3)->type == CPP_CLOSE_BRACE
      && !(c_parser_peek_nth_token (parser, 3)->flags & PREV_WHITE))
    {
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }

  /* Cast expression.  */
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_typename (c_parser_peek_2nd_token (parser)))
    {
      c_parser_consume_token (parser);
      నిర్మాణం c_type_name *type_name = c_parser_type_name (parser);
      c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      ఒకవేళ (type_name == ఖాళీ)
	తిరిగి;
      /* ???  The actual type used in the cast expression is ignored as
         in GIMPLE it is encoded by the type of the LHS.  */
      rhs = c_parser_gimple_postfix_వ్యక్తీకరణ (parser);
      ఒకవేళ (lhs.విలువ != error_mark_కణుపు
	  && rhs.విలువ != error_mark_కణుపు)
	{
	  గణన వృక్షం_సంకేతం_2 సంకేతం_2 = NOP_సమాసం;
	  ఒకవేళ (FLOAT_TYPE_P (వృక్షం_TYPE (lhs.విలువ))
	      && ! FLOAT_TYPE_P (వృక్షం_TYPE (rhs.విలువ)))
	    సంకేతం_2 = FLOAT_సమాసం;
	  లేకపోతే ఒకవేళ (! FLOAT_TYPE_P (వృక్షం_TYPE (lhs.విలువ))
		   && FLOAT_TYPE_P (వృక్షం_TYPE (rhs.విలువ)))
	    సంకేతం_2 = FIX_TRUNC_సమాసం;
	  కేటాయించు = gimple_build_కేటాయించు (lhs.విలువ, సంకేతం_2, rhs.విలువ);
	  gimple_seq_కూడు_stmt_without_update (seq, కేటాయించు);
	  gimple_సమితి_location (కేటాయించు, loc);
	  తిరిగి;
	}
    }

  /* Unary expression.  */
  ఎంపిక (c_parser_peek_token (parser)->type)
    {
    స్థితి CPP_NAME:
      {
	వృక్షం id = c_parser_peek_token (parser)->విలువ;
	ఒకవేళ (strcmp (IDENTIFIER_సూచిక (id), "__ABS") == 0
	    || strcmp (IDENTIFIER_సూచిక (id), "__ABSU") == 0
	    || strcmp (IDENTIFIER_సూచిక (id), "__MIN") == 0
	    || strcmp (IDENTIFIER_సూచిక (id), "__MAX") == 0
	    || strcmp (IDENTIFIER_సూచిక (id), "__BIT_INSERT") == 0
	    || strcmp (IDENTIFIER_సూచిక (id), "__VEC_PERM") == 0)
	  వెళ్ళు build_unary_సమాసం;
	ఆపు;
      }
    స్థితి CPP_KEYWORD:
      ఒకవేళ (c_parser_peek_token (parser)->keyword != RID_REALPART
	  && c_parser_peek_token (parser)->keyword != RID_IMAGPART)
	ఆపు;
      /* Fallthru.  */
    స్థితి CPP_AND:
    స్థితి CPP_PLUS:
    స్థితి CPP_MINUS:
    స్థితి CPP_COMPL:
    స్థితి CPP_NOT:
    స్థితి CPP_MULT: /* pointer deref */
    build_unary_సమాసం:
      rhs = c_parser_gimple_unary_వ్యక్తీకరణ (parser);
      ఒకవేళ (rhs.విలువ != error_mark_కణుపు)
	{
	  కేటాయించు = gimple_build_కేటాయించు (lhs.విలువ, rhs.విలువ);
	  gimple_సమితి_location (కేటాయించు, loc);
	  gimple_seq_కూడు_stmt_without_update (seq, కేటాయించు);
	}
      తిరిగి;

    అప్రమేయ:;
    }

  /* GIMPLE PHI statement.  */
  ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, RID_PHI))
    {
      c_parser_consume_token (parser);

      ఒకవేళ (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	తిరిగి;

      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_OPEN_PAREN))
	c_parser_consume_token (parser);

      అయితే (c_parser_తదుపరి_token_is_not (parser, CPP_CLOSE_PAREN))
	{
	  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      arg = c_parser_peek_token (parser)->విలువ;
	      c_parser_consume_token (parser);
	      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COLON))
		c_parser_consume_token (parser);
	      పూర్ణాంకం src_సూచీ = -1;
	      ఒకవేళ (!c_parser_gimple_parse_bb_spec (arg, &src_సూచీ))
		c_parser_error (parser, "invalid source block specification");
	      vargs.సురక్షిత_నెట్టు (కొలత_int (src_సూచీ));
	    }
	  లేకపోతే ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  లేకపోతే
	    {
	      arg = c_parser_gimple_unary_వ్యక్తీకరణ (parser).విలువ;
	      vargs.సురక్షిత_నెట్టు (arg);
	    }
	}

      c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");

      /* Build internal function for PHI.  */
      gcall *call_stmt = gimple_build_call_అంతర్గత_vec (IFN_PHI, vargs);
      gimple_call_సమితి_lhs (call_stmt, lhs.విలువ);
      gimple_సమితి_location (call_stmt, UNKNOWN_LOCATION);
      gimple_seq_కూడు_stmt_without_update (seq, call_stmt);
      తిరిగి;
    }

  /* GIMPLE call with lhs.  */
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_DOT)
      || (c_parser_తదుపరి_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN
	  && lookup_name (c_parser_peek_token (parser)->విలువ)))
    {
      rhs = c_parser_gimple_unary_వ్యక్తీకరణ (parser);
      ఒకవేళ (rhs.విలువ != error_mark_కణుపు)
	{
	  gimple *call = gimple_build_call_from_వృక్షం (rhs.విలువ, ఖాళీ);
	  gimple_call_సమితి_lhs (call, lhs.విలువ);
	  gimple_seq_కూడు_stmt_without_update (seq, call);
	  gimple_సమితి_location (call, loc);
	}
      తిరిగి;
    }

  rhs = c_parser_gimple_ద్విమాన_వ్యక్తీకరణ (parser, వృక్షం_TYPE (lhs.విలువ));
  ఒకవేళ (lhs.విలువ != error_mark_కణుపు
      && rhs.విలువ != error_mark_కణుపు)
    {
      /* If we parsed an identifier and the next token  is a '?' then parse
	 a conditional expression.  */
      ఒకవేళ (SSA_VAR_P (rhs.విలువ) && c_parser_తదుపరి_token_is (parser, CPP_QUERY))
	{
	  నిర్మాణం c_సమాసం trueval, falseval;
	  c_parser_consume_token (parser);
	  trueval = c_parser_gimple_postfix_వ్యక్తీకరణ (parser);
	  falseval.సమితి_error ();
	  ఒకవేళ (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    falseval = c_parser_gimple_postfix_వ్యక్తీకరణ (parser);
	  ఒకవేళ (trueval.విలువ == error_mark_కణుపు
	      || falseval.విలువ == error_mark_కణుపు)
	    తిరిగి;
	  rhs.విలువ = build3_loc (loc,
				  సదిశ_TYPE_P (వృక్షం_TYPE (rhs.విలువ))
				  ? VEC_COND_సమాసం : COND_సమాసం,
				  వృక్షం_TYPE (trueval.విలువ),
				  rhs.విలువ, trueval.విలువ, falseval.విలువ);
	}
      ఒకవేళ (get_gimple_rhs_class (వృక్షం_సంకేతం (rhs.విలువ)) == GIMPLE_INVALID_RHS)
	{
	  c_parser_error (parser, "unexpected RHS for assignment");
	  తిరిగి;
	}
      కేటాయించు = gimple_build_కేటాయించు (lhs.విలువ, rhs.విలువ);
      gimple_seq_కూడు_stmt_without_update (seq, కేటాయించు);
      gimple_సమితి_location (కేటాయించు, loc);
    }
  తిరిగి;
}

/* A mapping between an identifier to a tree code for binary operations. */
స్థిర స్థిరరాశి std::pair<స్థిరరాశి అక్షరం *, వృక్షం_సంకేతం_2> gimple_ద్విమాన_identifier_సంకేతం[] =
  {
    {"__MULT_HIGHPART", MULT_HIGHPART_సమాసం},
    {"__UNLT", UNLT_సమాసం},
    {"__UNLE", UNLE_సమాసం},
    {"__UNGT", UNGT_సమాసం},
    {"__UNGE", UNGE_సమాసం},
    {"__UNEQ", UNEQ_సమాసం},
    {"__UNORDERED", UNORDERED_సమాసం},
    {"__ORDERED", ORDERED_సమాసం},
    {"__LTGT", LTGT_సమాసం},
    {"__FLOOR_DIV", FLOOR_DIV_సమాసం},
    {"__ROUND_DIV", విడత_DIV_సమాసం},
    {"__EXACT_DIV", EXACT_DIV_సమాసం},
    {"__CEIL_DIV", CEIL_DIV_సమాసం},
    {"__FLOOR_MOD", FLOOR_MOD_సమాసం},
    {"__ROUND_MOD", విడత_MOD_సమాసం},
    {"__CEIL_MOD", CEIL_MOD_సమాసం},
    {"__ROTATE_LEFT", LROTATE_సమాసం},
    {"__ROTATE_RIGHT", RROTATE_సమాసం},
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

స్థిర c_సమాసం
c_parser_gimple_ద్విమాన_వ్యక్తీకరణ (gimple_parser &parser, వృక్షం ret_type)
{
  /* Location of the binary operator.  */
  నిర్మాణం c_సమాసం ret, lhs, rhs;
  గణన వృక్షం_సంకేతం_2 సంకేతం_2 = ERROR_MARK;
  ret.సమితి_error ();
  lhs = c_parser_gimple_postfix_వ్యక్తీకరణ (parser, ret_type);
  ఒకవేళ (c_parser_error (parser))
    తిరిగి ret;
  ఎంపిక (c_parser_peek_token (parser)->type)
    {
    స్థితి CPP_MULT:
      సంకేతం_2 = MULT_సమాసం;
      ఆపు;
    స్థితి CPP_DIV:
      సంకేతం_2 = TRUNC_DIV_సమాసం;
      ఆపు;
    స్థితి CPP_MOD:
      సంకేతం_2 = TRUNC_MOD_సమాసం;
      ఆపు;
    స్థితి CPP_PLUS:
      ఒకవేళ (సూచిక_TYPE_P (వృక్షం_TYPE (lhs.విలువ)))
	సంకేతం_2 = సూచిక_PLUS_సమాసం;
      లేకపోతే
	సంకేతం_2 = PLUS_సమాసం;
      ఆపు;
    స్థితి CPP_MINUS:
      ఒకవేళ (సూచిక_TYPE_P (వృక్షం_TYPE (lhs.విలువ)))
	సంకేతం_2 = సూచిక_DIFF_సమాసం;
      లేకపోతే
	సంకేతం_2 = MINUS_సమాసం;
      ఆపు;
    స్థితి CPP_LSHIFT:
      సంకేతం_2 = LSHIFT_సమాసం;
      ఆపు;
    స్థితి CPP_RSHIFT:
      సంకేతం_2 = RSHIFT_సమాసం;
      ఆపు;
    స్థితి CPP_LESS:
      సంకేతం_2 = LT_సమాసం;
      ఆపు;
    స్థితి CPP_GREATER:
      సంకేతం_2 = GT_సమాసం;
      ఆపు;
    స్థితి CPP_LESS_EQ:
      సంకేతం_2 = LE_సమాసం;
      ఆపు;
    స్థితి CPP_GREATER_EQ:
      సంకేతం_2 = GE_సమాసం;
      ఆపు;
    స్థితి CPP_EQ_EQ:
      సంకేతం_2 = EQ_సమాసం;
      ఆపు;
    స్థితి CPP_NOT_EQ:
      సంకేతం_2 = NE_సమాసం;
      ఆపు;
    స్థితి CPP_AND:
      సంకేతం_2 = బిట్టు_AND_సమాసం;
      ఆపు;
    స్థితి CPP_XOR:
      సంకేతం_2 = బిట్టు_XOR_సమాసం;
      ఆపు;
    స్థితి CPP_OR:
      సంకేతం_2 = బిట్టు_IOR_సమాసం;
      ఆపు;
    స్థితి CPP_AND_AND:
      c_parser_error (parser, "%<&&%> not valid in GIMPLE");
      తిరిగి ret;
    స్థితి CPP_OR_OR:
      c_parser_error (parser, "%<||%> not valid in GIMPLE");
      తిరిగి ret;
    స్థితి CPP_NAME:
      {
	వృక్షం id = c_parser_peek_token (parser)->విలువ;
	కొరకు (స్వయంచాలక &p : gimple_ద్విమాన_identifier_సంకేతం)
	  {
	    ఒకవేళ (strcmp (IDENTIFIER_సూచిక (id), p.మొదటి) == 0)
	      {
		సంకేతం_2 = p.రెండవ;
		ఆపు;
	      }
	  }
	ఒకవేళ (సంకేతం_2 != ERROR_MARK)
	  ఆపు;
      }
      /* Fallthru.  */
    అప్రమేయ:
      /* Not a binary expression.  */
      తిరిగి lhs;
    }
  location_t ret_loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  rhs = c_parser_gimple_postfix_వ్యక్తీకరణ (parser);
  ఒకవేళ (lhs.విలువ != error_mark_కణుపు && rhs.విలువ != error_mark_కణుపు)
    ret.విలువ = build2_loc (ret_loc, సంకేతం_2, ret_type, lhs.విలువ, rhs.విలువ);
  తిరిగి ret;
}

/* Parse a gimple parentized binary expression.  */

స్థిర c_సమాసం
c_parser_gimple_parentized_ద్విమాన_వ్యక్తీకరణ (gimple_parser &parser,
					      location_t op_loc,
					      వృక్షం_సంకేతం_2 సంకేతం_2)
{
  నిర్మాణం c_సమాసం ret;
  ret.సమితి_error ();

  c_parser_consume_token (parser);
  ఒకవేళ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    తిరిగి ret;
  c_సమాసం op1 = c_parser_gimple_postfix_వ్యక్తీకరణ (parser);
  ఒకవేళ (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    తిరిగి ret;
  c_సమాసం op2 = c_parser_gimple_postfix_వ్యక్తీకరణ (parser);
  ఒకవేళ (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    తిరిగి ret;

  ఒకవేళ (op1.విలువ != error_mark_కణుపు && op2.విలువ != error_mark_కణుపు)
    ret.విలువ = build2_loc (op_loc,
			    సంకేతం_2, వృక్షం_TYPE (op1.విలువ), op1.విలువ, op2.విలువ);
  తిరిగి ret;
}

/* Parse a gimple parentized binary expression.  */

స్థిర c_సమాసం
c_parser_gimple_parentized_ternary_వ్యక్తీకరణ (gimple_parser &parser,
					       location_t op_loc,
					       వృక్షం_సంకేతం_2 సంకేతం_2)
{
  నిర్మాణం c_సమాసం ret;
  ret.సమితి_error ();

  c_parser_consume_token (parser);
  ఒకవేళ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    తిరిగి ret;
  c_సమాసం op1 = c_parser_gimple_postfix_వ్యక్తీకరణ (parser);
  ఒకవేళ (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    తిరిగి ret;
  c_సమాసం op2 = c_parser_gimple_postfix_వ్యక్తీకరణ (parser);
  ఒకవేళ (!c_parser_require (parser, CPP_COMMA, "expected %<)%>"))
    తిరిగి ret;
  c_సమాసం op3 = c_parser_gimple_postfix_వ్యక్తీకరణ (parser);
  ఒకవేళ (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    తిరిగి ret;

  ఒకవేళ (op1.విలువ != error_mark_కణుపు
      && op2.విలువ != error_mark_కణుపు
      && op3.విలువ != error_mark_కణుపు)
    ret.విలువ = build3_loc (op_loc,
			    సంకేతం_2, వృక్షం_TYPE (op1.విలువ),
			    op1.విలువ, op2.విలువ, op3.విలువ);
  తిరిగి ret;
}

/* Parse gimple unary expression.

   gimple-unary-expression:
     gimple-postfix-expression
     unary-operator gimple-postfix-expression

   unary-operator: one of
     & * + - ~ abs_expr
*/

స్థిర c_సమాసం
c_parser_gimple_unary_వ్యక్తీకరణ (gimple_parser &parser)
{
  నిర్మాణం c_సమాసం ret, op;
  location_t op_loc = c_parser_peek_token (parser)->location;
  location_t ముగింపు;
  ret.సమితి_error ();
  ఎంపిక (c_parser_peek_token (parser)->type)
    {
    స్థితి CPP_AND:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_వ్యక్తీకరణ (parser);
      mark_exp_read (op.విలువ);
      తిరిగి gimple_parser_build_unary_op (op_loc, ADDR_సమాసం, op);
    స్థితి CPP_MULT:
      {
	c_parser_consume_token (parser);
	op = c_parser_gimple_postfix_వ్యక్తీకరణ (parser);
	ఒకవేళ (op.విలువ == error_mark_కణుపు)
	  తిరిగి ret;
	ఒకవేళ (! సూచిక_TYPE_P (వృక్షం_TYPE (op.విలువ)))
	  {
	    error_at (op_loc, "expected pointer as argument of unary %<*%>");
	    తిరిగి ret;
	  }
	ముగింపు = op.get_ముగింపు ();
	location_t combined_loc = make_location (op_loc, op_loc, ముగింపు);
	ret.విలువ = build_simple_mem_ref_loc (combined_loc, op.విలువ);
	వృక్షం_SIDE_EFFECTS (ret.విలువ)
	  = వృక్షం_THIS_VOLATILE (ret.విలువ)
	  = TYPE_VOLATILE (వృక్షం_TYPE (వృక్షం_TYPE (op.విలువ)));
	ret.src_range.m_ప్రారంభం = op_loc;
	ret.src_range.m_ముగింపు = ముగింపు;
	తిరిగి ret;
      }
    స్థితి CPP_PLUS:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_వ్యక్తీకరణ (parser);
      తిరిగి gimple_parser_build_unary_op (op_loc, CONVERT_సమాసం, op);
    స్థితి CPP_MINUS:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_వ్యక్తీకరణ (parser);
      తిరిగి gimple_parser_build_unary_op (op_loc, NEGATE_సమాసం, op);
    స్థితి CPP_COMPL:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_వ్యక్తీకరణ (parser);
      తిరిగి gimple_parser_build_unary_op (op_loc, బిట్టు_NOT_సమాసం, op);
    స్థితి CPP_NOT:
      c_parser_error (parser, "%<!%> not valid in GIMPLE");
      తిరిగి ret;
    స్థితి CPP_KEYWORD:
      ఎంపిక (c_parser_peek_token (parser)->keyword)
	{
	స్థితి RID_REALPART:
	  c_parser_consume_token (parser);
	  op = c_parser_gimple_postfix_వ్యక్తీకరణ (parser);
	  తిరిగి gimple_parser_build_unary_op (op_loc, REALPART_సమాసం, op);
	స్థితి RID_IMAGPART:
	  c_parser_consume_token (parser);
	  op = c_parser_gimple_postfix_వ్యక్తీకరణ (parser);
	  తిరిగి gimple_parser_build_unary_op (op_loc, IMAGPART_సమాసం, op);
	అప్రమేయ:
	  తిరిగి c_parser_gimple_postfix_వ్యక్తీకరణ (parser);
	}
    స్థితి CPP_NAME:
	{
	  వృక్షం id = c_parser_peek_token (parser)->విలువ;
	  ఒకవేళ (strcmp (IDENTIFIER_సూచిక (id), "__ABS") == 0)
	    {
	      c_parser_consume_token (parser);
	      op = c_parser_gimple_postfix_వ్యక్తీకరణ (parser);
	      తిరిగి gimple_parser_build_unary_op (op_loc, ABS_సమాసం, op);
	    }
	  లేకపోతే ఒకవేళ (strcmp (IDENTIFIER_సూచిక (id), "__ABSU") == 0)
	    {
	      c_parser_consume_token (parser);
	      op = c_parser_gimple_postfix_వ్యక్తీకరణ (parser);
	      తిరిగి gimple_parser_build_unary_op (op_loc, ABSU_సమాసం, op);
	    }
	  లేకపోతే ఒకవేళ (strcmp (IDENTIFIER_సూచిక (id), "__MIN") == 0)
	    తిరిగి c_parser_gimple_parentized_ద్విమాన_వ్యక్తీకరణ (parser,
								 op_loc,
								 MIN_సమాసం);
	  లేకపోతే ఒకవేళ (strcmp (IDENTIFIER_సూచిక (id), "__MAX") == 0)
	    తిరిగి c_parser_gimple_parentized_ద్విమాన_వ్యక్తీకరణ (parser,
								 op_loc,
								 MAX_సమాసం);
	  లేకపోతే ఒకవేళ (strcmp (IDENTIFIER_సూచిక (id), "__VEC_PERM") == 0)
	    తిరిగి c_parser_gimple_parentized_ternary_వ్యక్తీకరణ
			(parser, op_loc, VEC_PERM_సమాసం);
	  లేకపోతే ఒకవేళ (strcmp (IDENTIFIER_సూచిక (id), "__BIT_INSERT") == 0)
	    {
	      /* __BIT_INSERT '(' postfix-expression, postfix-expression,
			          integer ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      ఒకవేళ (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_సమాసం op0 = c_parser_gimple_postfix_వ్యక్తీకరణ (parser);
		  c_parser_skip_until_దొరికింది (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_సమాసం op1 = c_parser_gimple_postfix_వ్యక్తీకరణ (parser);
		  c_parser_skip_until_దొరికింది (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_సమాసం op2 = c_parser_gimple_postfix_వ్యక్తీకరణ (parser);
		  ఒకవేళ (వృక్షం_సంకేతం (op2.విలువ) != INTEGER_CST
		      || !int_సరిపోతుంది_type_p (op2.విలువ, bitsizetype))
		    c_parser_error (parser, "expected constant offset");
		  c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  ఒకవేళ (op0.విలువ != error_mark_కణుపు
		      && op1.విలువ != error_mark_కణుపు
		      && వృక్షం_సంకేతం (op2.విలువ) == INTEGER_CST)
		    ret.విలువ = build3_loc (loc, బిట్టు_చొప్పించు_సమాసం,
					    వృక్షం_TYPE (op0.విలువ),
					    op0.విలువ, op1.విలువ,
					    fold_convert (bitsizetype,
							  op2.విలువ));
		}
	      తిరిగి ret;
	    }
	  లేకపోతే
	    తిరిగి c_parser_gimple_postfix_వ్యక్తీకరణ (parser);
	}
    అప్రమేయ:
      తిరిగి c_parser_gimple_postfix_వ్యక్తీకరణ (parser);
    }
}

/* Decompose ID into base name (ID until ver_offset) and VERSION.  Return
   true if ID matches a SSA name.  */

స్థిర తార్కిక
c_parser_parse_ssa_name_id (వృక్షం id, గుర్తులేని *సంస్కరణ, గుర్తులేని *ver_స్థానభ్రంశం)
{
  స్థిరరాశి అక్షరం *token = IDENTIFIER_సూచిక (id);
  స్థిరరాశి అక్షరం *var_సంస్కరణ = strrchr (token, '_');
  ఒకవేళ (! var_సంస్కరణ)
    తిరిగి అబద్ధం;

  *ver_స్థానభ్రంశం = var_సంస్కరణ - token;
  కొరకు (స్థిరరాశి అక్షరం *p = var_సంస్కరణ + 1; *p; ++p)
    ఒకవేళ (! ISDIGIT (*p))
      తిరిగి అబద్ధం;
  *సంస్కరణ = atoi (var_సంస్కరణ + 1);
  తిరిగి *సంస్కరణ > 0;
}

/* Get at the actual SSA name ID with VERSION starting at VER_OFFSET.
   TYPE is the type if the SSA name is being declared.  */

స్థిర వృక్షం
c_parser_parse_ssa_name (gimple_parser &parser,
			 వృక్షం id, వృక్షం type, గుర్తులేని సంస్కరణ,
			 గుర్తులేని ver_స్థానభ్రంశం)
{
  వృక్షం name = NULL_వృక్షం;
  స్థిరరాశి అక్షరం *token = IDENTIFIER_సూచిక (id);

  ఒకవేళ (ver_స్థానభ్రంశం == 0)
    {
      /* Anonymous unnamed SSA name.  */
      ఒకవేళ (సంస్కరణ < అంకె_ssa_పేర్లు)
	name = ssa_name (సంస్కరణ);
      ఒకవేళ (! name)
	{
	  ఒకవేళ (! type)
	    {
	      c_parser_error (parser, "SSA name undeclared");
	      తిరిగి error_mark_కణుపు;
	    }
	  name = make_ssa_name_fn (cfun, type, ఖాళీ, సంస్కరణ);
	}
    }
  లేకపోతే
    {
      ఒకవేళ (సంస్కరణ < అంకె_ssa_పేర్లు)
	name = ssa_name (సంస్కరణ);
      ఒకవేళ (! name)
	{
	  /* Separate var name from version.  */
	  అక్షరం *var_name = XNEWVEC (అక్షరం, ver_స్థానభ్రంశం + 1);
	  జ్ఞాపకం_నకలు (var_name, token, ver_స్థానభ్రంశం);
	  var_name[ver_స్థానభ్రంశం] = '\0';
	  /* lookup for parent decl.  */
	  id = get_identifier (var_name);
	  వృక్షం మాతృ = lookup_name (id);
	  XDELETEVEC (var_name);
	  ఒకవేళ (! మాతృ || మాతృ == error_mark_కణుపు)
	    {
	      c_parser_error (parser, "base variable or SSA name undeclared");
	      తిరిగి error_mark_కణుపు;
	    }
	  ఒకవేళ (!(VAR_P (మాతృ)
		|| వృక్షం_సంకేతం (మాతృ) == PARM_DECL
		|| వృక్షం_సంకేతం (మాతృ) == ఫలితం_DECL))
	    {
	      error ("invalid base %qE for SSA name", మాతృ);
	      తిరిగి error_mark_కణుపు;
	    }
	  name = make_ssa_name_fn (cfun, మాతృ,
				   gimple_build_nop (), సంస్కరణ);
	}
    }

  తిరిగి name;
}

/* Parse a gimple call to an internal function.

   gimple-call-internal:
     . identifier ( gimple-argument-expression-list[opt] )  */

స్థిర నిర్మాణం c_సమాసం
c_parser_gimple_call_అంతర్గత (gimple_parser &parser)
{
  నిర్మాణం c_సమాసం సమాసం;
  సమాసం.సమితి_error ();

  gcc_assert (c_parser_తదుపరి_token_is (parser, CPP_DOT));
  c_parser_consume_token (parser);
  location_t loc = c_parser_peek_token (parser)->location;
  ఒకవేళ (!c_parser_తదుపరి_token_is (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_రకం != C_ID_ID)
    {
      c_parser_error (parser, "expecting internal function name");
      తిరిగి సమాసం;
    }
  వృక్షం id = c_parser_peek_token (parser)->విలువ;
  అంతర్గత_fn ifn = lookup_అంతర్గత_fn (IDENTIFIER_సూచిక (id));
  c_parser_consume_token (parser);
  ఒకవేళ (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    {
      auto_vec<వృక్షం> exprlist;
      ఒకవేళ (!c_parser_తదుపరి_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_gimple_సమాసం_list (parser, &exprlist);
      c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      ఒకవేళ (ifn == IFN_చివరి)
	error_at (loc, "unknown internal function %qE", id);
      లేకపోతే
	{
	  సమాసం.విలువ = build_call_సమాసం_అంతర్గత_loc_array
	    (loc, ifn, void_type_కణుపు, exprlist.నిడివి (),
	     exprlist.చిరునామా ());
	  సమాసం.original_సంకేతం = ERROR_MARK;
	  సమాసం.original_type = ఖాళీ;
	  సమాసం.m_decimal = 0;
	}
    }
  తిరిగి సమాసం;
}

/* Parse '<' type [',' alignment] '>' and return a type on success
   and NULL_TREE on error.  */

స్థిర వృక్షం
c_parser_gimple_typespec (gimple_parser &parser)
{
  నిర్మాణం c_type_name *type_name = ఖాళీ;
  వృక్షం alignment = NULL_వృక్షం;
  ఒకవేళ (c_parser_require (parser, CPP_LESS, "expected %<<%>"))
    {
      type_name = c_parser_type_name (parser);
      /* Optional alignment.  */
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COMMA))
	{
	  c_parser_consume_token (parser);
	  alignment
	      = c_parser_gimple_postfix_వ్యక్తీకరణ (parser).విలువ;
	}
      c_parser_skip_until_దొరికింది (parser,
				 CPP_GREATER, "expected %<>%>");
    }
  ఒకవేళ (!type_name)
    తిరిగి NULL_వృక్షం;
  వృక్షం tem;
  వృక్షం type = groktypename (type_name, &tem, ఖాళీ);
  ఒకవేళ (alignment)
    type = build_aligned_type (type, వృక్షం_గమ్యం_uhwi (alignment));
  తిరిగి type;
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

స్థిర నిర్మాణం c_సమాసం
c_parser_gimple_postfix_వ్యక్తీకరణ (gimple_parser &parser, వృక్షం ret_type)
{
  location_t loc = c_parser_peek_token (parser)->location;
  ఆధారం_range tok_range = c_parser_peek_token (parser)->get_range ();
  నిర్మాణం c_సమాసం సమాసం;
  సమాసం.సమితి_error ();
  ఎంపిక (c_parser_peek_token (parser)->type)
    {
    స్థితి CPP_సంఖ్య:
      సమాసం.విలువ = c_parser_peek_token (parser)->విలువ;
      సమితి_c_సమాసం_ఆధారం_range (&సమాసం, tok_range);
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      ఆపు;
    స్థితి CPP_CHAR:
    స్థితి CPP_CHAR16:
    స్థితి CPP_CHAR32:
    స్థితి CPP_UTF8CHAR:
    స్థితి CPP_WCHAR:
      సమాసం.విలువ = c_parser_peek_token (parser)->విలువ;
      సమితి_c_సమాసం_ఆధారం_range (&సమాసం, tok_range);
      c_parser_consume_token (parser);
      ఆపు;
    స్థితి CPP_STRING:
    స్థితి CPP_STRING16:
    స్థితి CPP_STRING32:
    స్థితి CPP_WSTRING:
    స్థితి CPP_UTF8STRING:
      సమాసం = c_parser_string_literal (parser, అబద్ధం, నిజం);
      ఆపు;
    స్థితి CPP_DOT:
      సమాసం = c_parser_gimple_call_అంతర్గత (parser);
      ఆపు;
    స్థితి CPP_NAME:
      ఒకవేళ (c_parser_peek_token (parser)->id_రకం == C_ID_ID)
	{
	  వృక్షం id = c_parser_peek_token (parser)->విలువ;
	  ఒకవేళ (strcmp (IDENTIFIER_సూచిక (id), "__MEM") == 0)
	    {
	      /* __MEM '<' type-name [ ',' number ] '>'
	               '(' [ '(' type-name ')' ] unary-expression
			   [ '+' number ]
			   [ ',' number ]
			   [ ',' number ':' number ] ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      వృక్షం type = c_parser_gimple_typespec (parser);
	      నిర్మాణం c_సమాసం ptr, alias_off, అడుగు, సూచీ, index2;
	      ptr.విలువ = error_mark_కణుపు;
	      alias_off.విలువ = NULL_వృక్షం;
	      అడుగు.విలువ = NULL_వృక్షం;
	      సూచీ.విలువ = NULL_వృక్షం;
	      index2.విలువ = NULL_వృక్షం;
	      గుర్తులేని పొట్టి clique = 0;
	      గుర్తులేని పొట్టి పునాది = 0;
	      తార్కిక తిరగేయి_క్రమం = అబద్ధం;
	      నిర్మాణం c_సమాసం ro;
	      ఒకవేళ (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  వృక్షం alias_type = NULL_వృక్షం;
		  /* Optional alias-type cast.  */
		  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_OPEN_PAREN))
		    {
		      c_parser_consume_token (parser);
		      నిర్మాణం c_type_name *alias_type_name
			= c_parser_type_name (parser);
		      c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN,
						 "expected %<)%>");
		      ఒకవేళ (alias_type_name)
			{
			  వృక్షం tem;
			  alias_type = groktypename (alias_type_name,
						     &tem, ఖాళీ);
			}
		    }
		  ptr = c_parser_gimple_unary_వ్యక్తీకరణ (parser);
		  ఒకవేళ (ptr.విలువ == error_mark_కణుపు
		      || ! సూచిక_TYPE_P (వృక్షం_TYPE (ptr.విలువ)))
		    {
		      ఒకవేళ (ptr.విలువ != error_mark_కణుపు)
			error_at (ptr.get_ప్రారంభం (),
				  "invalid type of %<__MEM%> operand");
		      c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN,
						 "expected %<)%>");
		      తిరిగి సమాసం;
		    }
		  ఒకవేళ (! alias_type)
		    alias_type = వృక్షం_TYPE (ptr.విలువ);
		  /* Optional constant offset.  */
		  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      alias_off = c_parser_gimple_postfix_వ్యక్తీకరణ (parser);
		    }
		  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_MULT))
		    {
		      std::మార్పిడి (సూచీ, alias_off);
		      c_parser_consume_token (parser);
		      అడుగు = c_parser_gimple_postfix_వ్యక్తీకరణ (parser);
		    }
		  లేకపోతే ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      సూచీ = c_parser_gimple_postfix_వ్యక్తీకరణ (parser);
		      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_MULT))
			{
			  c_parser_consume_token (parser);
			  అడుగు = c_parser_gimple_postfix_వ్యక్తీకరణ (parser);
			}
		      లేకపోతే
			std::మార్పిడి (సూచీ, index2);
		    }
		  లేకపోతే ఒకవేళ (alias_off.విలువ
			   && వృక్షం_సంకేతం (alias_off.విలువ) != INTEGER_CST)
		    std::మార్పిడి (alias_off, index2);
		  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      index2 = c_parser_gimple_postfix_వ్యక్తీకరణ (parser);
		    }
		  ఒకవేళ (alias_off.విలువ)
		    {
		      ఒకవేళ (వృక్షం_సంకేతం (alias_off.విలువ) != INTEGER_CST)
			error_at (alias_off.get_ప్రారంభం (),
				  "expected constant offset for %<__MEM%> "
				  "operand");
		      alias_off.విలువ = fold_convert (alias_type,
						      alias_off.విలువ);
		    }
		  లేకపోతే
		    alias_off.విలువ = build_int_cst (alias_type, 0);
		  ఒకవేళ (అడుగు.విలువ)
		    {
		      ఒకవేళ (వృక్షం_సంకేతం (అడుగు.విలువ) != INTEGER_CST)
			error_at (అడుగు.get_ప్రారంభం (),
				  "expected constant step for %<__MEM%> "
				  "operand");
		    }
		  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COMMA))
		    {
		      నిర్మాణం c_సమాసం cl, ba;
		      తార్కిక has_clb = నిజం;
		      c_parser_consume_token (parser);
		      cl = c_parser_gimple_postfix_వ్యక్తీకరణ (parser);
		      ఒకవేళ (!c_parser_తదుపరి_token_is (parser, CPP_COLON))
			{
			  ro = cl;
			  గుర్తులేని HOST_WIDE_INT tmp = 0;
			  ఒకవేళ (!వృక్షం_సరిపోతుంది_uhwi_p (ro.విలువ)
			      || (tmp = వృక్షం_గమ్యం_uhwi (ro.విలువ)) > 1)
			    error_at (ro.get_ప్రారంభం (),
				      "invalid reverse order value");
			  తిరగేయి_క్రమం = tmp;
			  has_clb = అబద్ధం;
			  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COMMA))
			    {
			      c_parser_consume_token (parser);
			      cl = c_parser_gimple_postfix_వ్యక్తీకరణ (parser);
		              has_clb = నిజం;
			    }
			}
		      ఒకవేళ (has_clb
			  && c_parser_require (parser,
					       CPP_COLON, "expected %<:%>"))
			{
			  ba = c_parser_gimple_postfix_వ్యక్తీకరణ (parser);
			  ఒకవేళ (!వృక్షం_సరిపోతుంది_uhwi_p (cl.విలువ)
			      || !వృక్షం_సరిపోతుంది_uhwi_p (ba.విలువ)
			      || compare_వృక్షం_int (cl.విలువ,
						   (clique = వృక్షం_గమ్యం_uhwi
								(cl.విలువ)))
			      || compare_వృక్షం_int (ba.విలువ,
						   (పునాది = వృక్షం_గమ్యం_uhwi
								 (ba.విలువ))))
			    error_at (cl.get_ప్రారంభం (),
				      "invalid clique/base pair");
			}
		    }
		  c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      ఒకవేళ (! type || c_parser_error (parser))
		{
		  c_parser_సమితి_error (parser, అబద్ధం);
		  తిరిగి సమాసం;
		}
	      ఒకవేళ (సూచీ.విలువ || అడుగు.విలువ || index2.విలువ)
		సమాసం.విలువ = build5_loc (loc, లక్ష్యం_MEM_REF,
					 type, ptr.విలువ, alias_off.విలువ,
					 సూచీ.విలువ, అడుగు.విలువ, index2.విలువ);
	      లేకపోతే
		సమాసం.విలువ = build2_loc (loc, MEM_REF,
					 type, ptr.విలువ, alias_off.విలువ);
	      ఒకవేళ (clique != 0)
		{
		  cfun->చివరి_clique = MAX (cfun->చివరి_clique, clique);
		  MR_DEPENDENCE_CLIQUE (సమాసం.విలువ) = clique;
		  MR_DEPENDENCE_పునాది (సమాసం.విలువ) = పునాది;
		}
	      ఒకవేళ (తిరగేయి_క్రమం)
		{
		  ఒకవేళ (వృక్షం_సంకేతం (సమాసం.విలువ) == MEM_REF)
		    REF_తిరగేయి_STORAGE_క్రమం (సమాసం.విలువ) = తిరగేయి_క్రమం;
		  లేకపోతే
		    error_at (ro.get_ప్రారంభం (),
			      "target mem ref cannot have reverse order");
		}
	      ఆపు;
	    }
	  లేకపోతే ఒకవేళ (strcmp (IDENTIFIER_సూచిక (id), "__VIEW_CONVERT") == 0)
	    {
	      /* __VIEW_CONVERT '<' type-name [ ',' number ] '>'
	                        '(' postfix-expression ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      వృక్షం type = c_parser_gimple_typespec (parser);
	      ఒకవేళ (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_సమాసం op = c_parser_gimple_postfix_వ్యక్తీకరణ (parser);
		  c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  ఒకవేళ (type && op.విలువ != error_mark_కణుపు)
		    సమాసం.విలువ = build1_loc (loc, VIEW_CONVERT_సమాసం,
					     type, op.విలువ);
		}
	      ఆపు;
	    }
	  లేకపోతే ఒకవేళ (strcmp (IDENTIFIER_సూచిక (id), "__BIT_FIELD_REF") == 0)
	    {
	      /* __BIT_FIELD_REF '<' type-name [ ',' number ] '>'
	                        '(' postfix-expression, integer, integer ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      వృక్షం type = c_parser_gimple_typespec (parser);
	      ఒకవేళ (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_సమాసం op0 = c_parser_gimple_postfix_వ్యక్తీకరణ (parser);
		  c_parser_skip_until_దొరికింది (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_సమాసం op1 = c_parser_gimple_postfix_వ్యక్తీకరణ (parser);
		  ఒకవేళ (వృక్షం_సంకేతం (op1.విలువ) != INTEGER_CST
		      || !int_సరిపోతుంది_type_p (op1.విలువ, bitsizetype))
		    c_parser_error (parser, "expected constant size");
		  c_parser_skip_until_దొరికింది (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_సమాసం op2 = c_parser_gimple_postfix_వ్యక్తీకరణ (parser);
		  ఒకవేళ (వృక్షం_సంకేతం (op2.విలువ) != INTEGER_CST
		      || !int_సరిపోతుంది_type_p (op2.విలువ, bitsizetype))
		    c_parser_error (parser, "expected constant offset");
		  c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  ఒకవేళ (type
		      && op0.విలువ != error_mark_కణుపు
		      && వృక్షం_సంకేతం (op1.విలువ) == INTEGER_CST
		      && వృక్షం_సంకేతం (op2.విలువ) == INTEGER_CST)
		    సమాసం.విలువ = build3_loc (loc, బిట్టు_క్షేత్రం_REF, type,
					     op0.విలువ,
					     fold_convert (bitsizetype,
							   op1.విలువ),
					     fold_convert (bitsizetype,
							   op2.విలువ));
		}
	      ఆపు;
	    }
	  లేకపోతే ఒకవేళ (strcmp (IDENTIFIER_సూచిక (id), "__CLOBBER") == 0)
	    {
	      /* __CLOBBER [ '(' bob | eob | bos | eos ')' ]  */
	      clobber_రకం రకం = CLOBBER_UNDEF;
	      c_parser_consume_token (parser);
	      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_OPEN_PAREN))
		{
		  c_parser_consume_token (parser);
		  స్వయంచాలక tok = c_parser_peek_token (parser);
		  ఒకవేళ (c_parser_require (parser, CPP_NAME,
					"expected clobber kind"))
		    {
		      స్థిరరాశి అక్షరం *రకం_str = IDENTIFIER_సూచిక (tok->విలువ);
		      ఒకవేళ (strcmp (రకం_str, "bos") == 0)
			రకం = CLOBBER_STORAGE_BEGIN;
		      లేకపోతే ఒకవేళ (strcmp (రకం_str, "bob") == 0)
			రకం = CLOBBER_OBJECT_BEGIN;
		      లేకపోతే ఒకవేళ (strcmp (రకం_str, "eob") == 0)
			రకం = CLOBBER_OBJECT_చివర;
		      లేకపోతే ఒకవేళ (strcmp (రకం_str, "eos") == 0)
			రకం = CLOBBER_STORAGE_చివర;
		      లేకపోతే
			c_parser_error (parser, "expected one of %<bos%>, "
					"%<eos%>, %<bob>, %<eob%>");
		    }
		  c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      /* We infer the (redundant) type from the LHS.  */
	      సమాసం.విలువ = build_clobber (ret_type, రకం);
	      ఆపు;
	    }
	  లేకపోతే ఒకవేళ (strcmp (IDENTIFIER_సూచిక (id), "_Literal") == 0)
	    {
	      /* _Literal '(' type-name ')' ( [ '-' ] constant | constructor ) */
	      c_parser_consume_token (parser);
	      వృక్షం type = NULL_వృక్షం;
	      ఒకవేళ (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  నిర్మాణం c_type_name *type_name = c_parser_type_name (parser);
		  వృక్షం tem;
		  ఒకవేళ (type_name)
		    type = groktypename (type_name, &tem, ఖాళీ);
		  c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      ఒకవేళ (! type)
		{
		  c_parser_error (parser, "invalid _Literal");
		  తిరిగి సమాసం;
		}
	      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_OPEN_BRACE))
		{
		  c_parser_consume_token (parser);
		  ఒకవేళ (!AGGREGATE_TYPE_P (type)
		      && !సదిశ_TYPE_P (type))
		    {
		      c_parser_error (parser, "invalid type for _Literal with "
				      "constructor");
		      c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_BRACE,
						 "expected %<}%>");
		      తిరిగి సమాసం;
		    }
		  vec<constructor_elt, va_gc> *v = ఖాళీ;
		  తార్కిక constant_p = నిజం;
		  ఒకవేళ (సదిశ_TYPE_P (type)
		      && !c_parser_తదుపరి_token_is (parser, CPP_CLOSE_BRACE))
		    {
		      vec_alloc (v, TYPE_సదిశ_SUBPARTS (type).గమ్యం_constant ());
		      చేయి
			{
			  వృక్షం val
			    = c_parser_gimple_postfix_వ్యక్తీకరణ (parser).విలువ;
			  ఒకవేళ (! val
			      || val == error_mark_కణుపు
			      || (! CONSTANT_CLASS_P (val)
				  && ! SSA_VAR_P (val)))
			    {
			      c_parser_error (parser, "invalid _Literal");
			      తిరిగి సమాసం;
			    }
			  CONSTRUCTOR_APPEND_ELT (v, NULL_వృక్షం, val);
			  ఒకవేళ (! CONSTANT_CLASS_P (val))
			    constant_p = అబద్ధం;
			  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COMMA))
			    c_parser_consume_token (parser);
			  లేకపోతే
			    ఆపు;
			}
		      అయితే (1);
		    }
		  ఒకవేళ (c_parser_require (parser, CPP_CLOSE_BRACE,
					"expected %<}%>"))
		    {
		      ఒకవేళ (v && constant_p)
			సమాసం.విలువ = build_సదిశ_from_ctor (type, v);
		      లేకపోతే
			సమాసం.విలువ = build_constructor (type, v);
		    }
		  లేకపోతే
		    {
		      c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_BRACE,
						 "expected %<}%>");
		      తిరిగి సమాసం;
		    }
		}
	      లేకపోతే
		{
		  తార్కిక neg_p, addr_p;
		  ఒకవేళ ((neg_p = c_parser_తదుపరి_token_is (parser, CPP_MINUS)))
		    c_parser_consume_token (parser);
		  ఒకవేళ ((addr_p = c_parser_తదుపరి_token_is (parser, CPP_AND)))
		    c_parser_consume_token (parser);
		  వృక్షం val = c_parser_gimple_postfix_వ్యక్తీకరణ (parser).విలువ;
		  ఒకవేళ (! val
		      || val == error_mark_కణుపు
		      || (!CONSTANT_CLASS_P (val) && !addr_p))
		    {
		      c_parser_error (parser, "invalid _Literal");
		      తిరిగి సమాసం;
		    }
		  ఒకవేళ (addr_p)
		    {
		      val = build1 (ADDR_సమాసం, type, val);
		      ఒకవేళ (!is_gimple_invariant_చిరునామా (val))
			{
			  c_parser_error (parser, "invalid _Literal");
			  తిరిగి సమాసం;
			}
		    }
		  ఒకవేళ (neg_p)
		    {
		      val = const_unop (NEGATE_సమాసం, వృక్షం_TYPE (val), val);
		      ఒకవేళ (! val)
			{
			  c_parser_error (parser, "invalid _Literal");
			  తిరిగి సమాసం;
			}
		    }
		  సమాసం.విలువ = fold_convert (type, val);
		}
	      తిరిగి సమాసం;
	    }

	  /* SSA name.  */
	  గుర్తులేని సంస్కరణ, ver_స్థానభ్రంశం;
	  ఒకవేళ (! lookup_name (id)
	      && c_parser_parse_ssa_name_id (id, &సంస్కరణ, &ver_స్థానభ్రంశం))
	    {
	      c_parser_consume_token (parser);
	      సమాసం.విలువ = c_parser_parse_ssa_name (parser, id, NULL_వృక్షం,
						    సంస్కరణ, ver_స్థానభ్రంశం);
	      ఒకవేళ (సమాసం.విలువ == error_mark_కణుపు)
		తిరిగి సమాసం;
	      సమితి_c_సమాసం_ఆధారం_range (&సమాసం, tok_range);
	      /* For default definition SSA names.  */
	      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_OPEN_PAREN)
		  && c_parser_peek_2nd_token (parser)->type == CPP_NAME
		  && strcmp ("D",
			     IDENTIFIER_సూచిక
			       (c_parser_peek_2nd_token (parser)->విలువ)) == 0
		  && c_parser_peek_nth_token (parser, 3)->type == CPP_CLOSE_PAREN)
		{
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		  ఒకవేళ (! SSA_NAME_IS_DEFAULT_DEF (సమాసం.విలువ))
		    {
		      ఒకవేళ (!SSA_NAME_VAR (సమాసం.విలువ))
			{
			  error_at (loc, "anonymous SSA name cannot have"
				    " default definition");
			  సమాసం.విలువ = error_mark_కణుపు;
			  తిరిగి సమాసం;
			}
		      సమితి_ssa_default_def (cfun, SSA_NAME_VAR (సమాసం.విలువ),
					   సమాసం.విలువ);
		      SSA_NAME_DEF_STMT (సమాసం.విలువ) = gimple_build_nop ();
		    }
		}
	    }
	  లేకపోతే
	    {
	      c_parser_consume_token (parser);
	      సమాసం.విలువ
		= build_external_ref (loc, id,
				      (c_parser_peek_token (parser)->type
				       == CPP_OPEN_PAREN), &సమాసం.original_type);
	      సమితి_c_సమాసం_ఆధారం_range (&సమాసం, tok_range);
	    }
	  ఆపు;
	}
      /* Fallthru.  */
    అప్రమేయ:
      c_parser_error (parser, "expected expression");
      సమాసం.సమితి_error ();
      ఆపు;
    }
  ఒకవేళ (సమాసం.విలువ == error_mark_కణుపు)
    తిరిగి సమాసం;
  తిరిగి c_parser_gimple_postfix_వ్యక్తీకరణ_after_primary
    (parser, సమాసం_LOC_OR_LOC (సమాసం.విలువ, loc), సమాసం);
}

/* Parse a gimple postfix expression after the initial primary or compound
   literal.  */

స్థిర నిర్మాణం c_సమాసం
c_parser_gimple_postfix_వ్యక్తీకరణ_after_primary (gimple_parser &parser,
						  location_t సమాసం_loc,
						  నిర్మాణం c_సమాసం సమాసం)
{
  location_t ప్రారంభం;
  location_t ముగింపు;
  వృక్షం ident;
  location_t comp_loc;

  అయితే (నిజం)
    {
      location_t op_loc = c_parser_peek_token (parser)->location;
      ఎంపిక (c_parser_peek_token (parser)->type)
	{
	స్థితి CPP_OPEN_వర్గం:
	  {
	    c_parser_consume_token (parser);
	    వృక్షం idx = c_parser_gimple_unary_వ్యక్తీకరణ (parser).విలువ;

	    ఒకవేళ (! c_parser_require (parser, CPP_CLOSE_వర్గం, "expected %<]%>"))
	      {
		c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_వర్గం, ఖాళీ);
		ఆపు;
	      }

	    ప్రారంభం = సమాసం.get_ప్రారంభం ();
	    ముగింపు = c_parser_టోకెన్లు_buf (parser, 0)->location;
	    సమాసం.విలువ = build_array_ref (op_loc, సమాసం.విలువ, idx);
	    సమితి_c_సమాసం_ఆధారం_range (&సమాసం, ప్రారంభం, ముగింపు);
	    సమాసం.m_decimal = 0;

	    సమాసం.original_సంకేతం = ERROR_MARK;
	    సమాసం.original_type = ఖాళీ;
	    ఆపు;
	  }
	స్థితి CPP_OPEN_PAREN:
	  {
	    /* Function call.  */
	    c_parser_consume_token (parser);
	    auto_vec<వృక్షం> exprlist;
	    ఒకవేళ (! c_parser_తదుపరి_token_is (parser, CPP_CLOSE_PAREN))
	      c_parser_gimple_సమాసం_list (parser, &exprlist);
	    c_parser_skip_until_దొరికింది (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    ఒకవేళ (!FUNC_OR_పద్ధతి_TYPE_P (వృక్షం_TYPE (సమాసం.విలువ)))
	      {
		c_parser_error (parser, "invalid call to non-function");
		సమాసం.సమితి_error ();
		ఆపు;
	      }
	    సమాసం.విలువ = build_call_array_loc
		(సమాసం_loc, వృక్షం_TYPE (వృక్షం_TYPE (సమాసం.విలువ)),
		 సమాసం.విలువ, exprlist.నిడివి (), exprlist.చిరునామా ());
	    సమాసం.m_decimal = 0;
	    సమాసం.original_సంకేతం = ERROR_MARK;
	    సమాసం.original_type = ఖాళీ;
	    ఆపు;
	  }
	స్థితి CPP_DOT:
	  {
	    /* Structure element reference.  */
	    c_parser_consume_token (parser);
	    ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		ident = comp_tok->విలువ;
		comp_loc = comp_tok->location;
	      }
	    లేకపోతే
	      {
		c_parser_error (parser, "expected identifier");
		సమాసం.సమితి_error ();
		సమాసం.original_సంకేతం = ERROR_MARK;
		సమాసం.original_type = ఖాళీ;
		తిరిగి సమాసం;
	      }
	    ప్రారంభం = సమాసం.get_ప్రారంభం ();
	    ముగింపు = c_parser_peek_token (parser)->get_ముగింపు ();
	    c_parser_consume_token (parser);
	    సమాసం.విలువ = build_component_ref (op_loc, సమాసం.విలువ, ident,
					      comp_loc, UNKNOWN_LOCATION);
	    సమితి_c_సమాసం_ఆధారం_range (&సమాసం, ప్రారంభం, ముగింపు);
	    సమాసం.m_decimal = 0;
	    సమాసం.original_సంకేతం = ERROR_MARK;
	    ఒకవేళ (వృక్షం_సంకేతం (సమాసం.విలువ) != COMPONENT_REF)
	      సమాసం.original_type = ఖాళీ;
	    లేకపోతే
	      {
		/* Remember the original type of a bitfield.  */
		వృక్షం క్షేత్రం_2 = వృక్షం_నిర్వాహ్యం (సమాసం.విలువ, 1);
		ఒకవేళ (వృక్షం_సంకేతం (క్షేత్రం_2) != క్షేత్రం_DECL)
		  సమాసం.original_type = ఖాళీ;
		లేకపోతే
		  సమాసం.original_type = DECL_బిట్టు_క్షేత్రం_TYPE (క్షేత్రం_2);
	      }
	    ఆపు;
	  }
	స్థితి CPP_DEREF:
	  {
	    /* Structure element reference.  */
	    ఒకవేళ (!సూచిక_TYPE_P (వృక్షం_TYPE (సమాసం.విలువ)))
	      {
		c_parser_error (parser, "dereference of non-pointer");
		సమాసం.సమితి_error ();
		సమాసం.original_సంకేతం = ERROR_MARK;
		సమాసం.original_type = ఖాళీ;
		తిరిగి సమాసం;
	      }
	    c_parser_consume_token (parser);
	    ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		ident = comp_tok->విలువ;
		comp_loc = comp_tok->location;
	      }
	    లేకపోతే
	      {
		c_parser_error (parser, "expected identifier");
		సమాసం.సమితి_error ();
		సమాసం.original_సంకేతం = ERROR_MARK;
		సమాసం.original_type = ఖాళీ;
		తిరిగి సమాసం;
	      }
	    ప్రారంభం = సమాసం.get_ప్రారంభం ();
	    ముగింపు = c_parser_peek_token (parser)->get_ముగింపు ();
	    c_parser_consume_token (parser);
	    సమాసం.విలువ = build_component_ref (op_loc,
					      build_simple_mem_ref_loc
					        (op_loc, సమాసం.విలువ),
					      ident, comp_loc,
					      సమాసం.get_location ());
	    సమితి_c_సమాసం_ఆధారం_range (&సమాసం, ప్రారంభం, ముగింపు);
	    సమాసం.m_decimal = 0;
	    సమాసం.original_సంకేతం = ERROR_MARK;
	    ఒకవేళ (వృక్షం_సంకేతం (సమాసం.విలువ) != COMPONENT_REF)
	      సమాసం.original_type = ఖాళీ;
	    లేకపోతే
	      {
		/* Remember the original type of a bitfield.  */
		వృక్షం క్షేత్రం_2 = వృక్షం_నిర్వాహ్యం (సమాసం.విలువ, 1);
		ఒకవేళ (వృక్షం_సంకేతం (క్షేత్రం_2) != క్షేత్రం_DECL)
		  సమాసం.original_type = ఖాళీ;
		లేకపోతే
		  సమాసం.original_type = DECL_బిట్టు_క్షేత్రం_TYPE (క్షేత్రం_2);
	      }
	    ఆపు;
	  }
	అప్రమేయ:
	  తిరిగి సమాసం;
	}
    }
}

/* Parse expression list.

   gimple-expr-list:
     gimple-unary-expression
     gimple-expr-list , gimple-unary-expression

 */

స్థిర శూన్య
c_parser_gimple_సమాసం_list (gimple_parser &parser, vec<వృక్షం> *ret)
{
  నిర్మాణం c_సమాసం సమాసం;

  సమాసం = c_parser_gimple_unary_వ్యక్తీకరణ (parser);
  ret->సురక్షిత_నెట్టు (సమాసం.విలువ);
  అయితే (c_parser_తదుపరి_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      సమాసం = c_parser_gimple_unary_వ్యక్తీకరణ (parser);
      ret->సురక్షిత_నెట్టు (సమాసం.విలువ);
    }
}

/* Parse gimple label.

   gimple-label:
     identifier :
     case constant-expression :
     default :

*/

స్థిర శూన్య
c_parser_gimple_label (gimple_parser &parser, gimple_seq *seq)
{
  వృక్షం name = c_parser_peek_token (parser)->విలువ;
  location_t loc1 = c_parser_peek_token (parser)->location;
  gcc_assert (c_parser_తదుపరి_token_is (parser, CPP_NAME));
  c_parser_consume_token (parser);
  gcc_assert (c_parser_తదుపరి_token_is (parser, CPP_COLON));
  c_parser_consume_token (parser);
  వృక్షం label = define_label (loc1, name);
  ఒకవేళ (label)
    gimple_seq_కూడు_stmt_without_update (seq, gimple_build_label (label));
  తిరిగి;
}

/* Parse gimple/RTL pass list.

   gimple-or-rtl-pass-list:
     startwith("pass-name")[,{cfg,ssa}]
 */

శూన్య
c_parser_gimple_or_rtl_pass_list (c_parser *parser, c_declspecs *specs)
{
  అక్షరం *pass = ఖాళీ;

  /* Accept __GIMPLE/__RTL.  */
  ఒకవేళ (c_parser_తదుపరి_token_is_not (parser, CPP_OPEN_PAREN))
    తిరిగి;
  c_parser_consume_token (parser);

  specs->నమోదు_bb_లెక్క = profile_లెక్క::uninitialized ();
  అయితే (c_parser_తదుపరి_token_is (parser, CPP_NAME))
    {
      profile_quality quality;
      స్థిరరాశి అక్షరం *op = IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ);
      c_parser_consume_token (parser);
      ఒకవేళ (! strcmp (op, "startwith"))
	{
	  ఒకవేళ (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    తిరిగి;
	  ఒకవేళ (c_parser_తదుపరి_token_is_not (parser, CPP_STRING))
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"expected pass name");
	      తిరిగి;
	    }
	  pass = xstrdup (వృక్షం_STRING_సూచిక
			  (c_parser_string_literal (parser, అబద్ధం,
						    అబద్ధం).విలువ));
	  ఒకవేళ (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<(%>"))
	    తిరిగి;
	}
      లేకపోతే ఒకవేళ (parse_profile_quality (op, &quality))
	{
	  వృక్షం q;
	  ఒకవేళ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    తిరిగి;

	  ఒకవేళ (!c_parser_తదుపరి_token_is (parser, CPP_సంఖ్య)
	      || (వృక్షం_సంకేతం (q = c_parser_peek_token (parser)->విలువ)
		  != INTEGER_CST))
	    {
	      c_parser_error (parser, "expected count value");
	      తిరిగి;
	    }

	  specs->నమోదు_bb_లెక్క
	    = profile_లెక్క::from_gcov_type (వృక్షం_INT_CST_దిగువ (q), quality);
	  c_parser_consume_token (parser);
	  ఒకవేళ (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    తిరిగి;
	}
      లేకపోతే ఒకవేళ (specs->declspec_il != cdil_gimple)
	/* Allow only one IL specifier and none on RTL.  */
	;
      లేకపోతే ఒకవేళ (! strcmp (op, "cfg"))
	specs->declspec_il = cdil_gimple_cfg;
      లేకపోతే ఒకవేళ (! strcmp (op, "ssa"))
	specs->declspec_il = cdil_gimple_ssa;
      లేకపోతే
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "invalid operation");
	  తిరిగి;
	}
     ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COMMA))
       c_parser_consume_token (parser);
    }

  ఒకవేళ (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    తిరిగి;

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
రిజిస్టరు

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

స్థిర శూన్య
c_parser_gimple_declaration (gimple_parser &parser)
{
  నిర్మాణం c_declarator *declarator;
  నిర్మాణం c_declspecs *specs = build_null_declspecs ();
  c_parser_declspecs (parser, specs, నిజం, నిజం, నిజం,
		      నిజం, నిజం, నిజం, నిజం, cla_nonabstract_decl);
  ముగింపు_declspecs (specs);

  /* Provide better error recovery.  Note that a type name here is usually
     better diagnosed as a redeclaration.  */
  ఒకవేళ (c_parser_తదుపరి_token_starts_declspecs (parser)
      && ! c_parser_తదుపరి_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<;%>");
      c_parser_సమితి_error (parser, అబద్ధం);
      తిరిగి;
    }

  తార్కిక dummy = అబద్ధం;
  declarator = c_parser_declarator (parser,
				    specs->typespec_రకం != ctsk_none,
				    C_DTR_సాధారణ, &dummy);

  ఒకవేళ (!c_parser_తదుపరి_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_error (parser, "expected %<;%>");
      తిరిగి;
    }
  ఒకవేళ (declarator)
    {
      /* Handle SSA name decls specially, they do not go into the identifier
         table but we simply build the SSA name for later lookup.  */
      గుర్తులేని సంస్కరణ, ver_స్థానభ్రంశం;
      /* Handle SSA pointer declarations in a very simplistic ways, we
	 probably would like to call grokdeclarator in a special mode to
	 just build the type of the decl - start_decl already pushes
	 the identifier to the bindings for lookup, something we do not
	 want.  */
      నిర్మాణం c_declarator *id_declarator = declarator;
      అయితే (id_declarator->రకం == cdk_సూచిక)
	id_declarator = id_declarator->declarator;
      ఒకవేళ (id_declarator->రకం == cdk_id
	  && (declarator->రకం == cdk_సూచిక
	      || is_gimple_reg_type (specs->type))
	  && c_parser_parse_ssa_name_id (id_declarator->u.id.id,
					 &సంస్కరణ, &ver_స్థానభ్రంశం)
	  /* The following restricts it to unnamed anonymous SSA names
	     which fails parsing of named ones in dumps (we could
	     decide to not dump their name for -gimple).  */
	  && ver_స్థానభ్రంశం == 0)
	{
	  నిర్మాణం c_declarator *p = declarator;
	  వృక్షం type = specs->type;
	  అయితే (p->రకం == cdk_సూచిక)
	    {
	      type = build_సూచిక_type (type);
	      p = p->declarator;
	    }
	  c_parser_parse_ssa_name (parser, id_declarator->u.id.id, type,
				   సంస్కరణ, ver_స్థానభ్రంశం);
	}
      లేకపోతే
	{
	  వృక్షం postfix_attrs = NULL_వృక్షం;
	  వృక్షం all_ఉపసర్గ_attrs = specs->attrs;
	  specs->attrs = ఖాళీ;
	  వృక్షం decl = ప్రారంభం_decl (declarator, specs, అబద్ధం,
				  chainon (postfix_attrs, all_ఉపసర్గ_attrs));
	  ఒకవేళ (decl)
	    ముగింపు_decl (decl, UNKNOWN_LOCATION, NULL_వృక్షం, NULL_వృక్షం,
			 NULL_వృక్షం);
	}
    }
}

/* Parse gimple goto statement.  */

స్థిర శూన్య
c_parser_gimple_goto_stmt (gimple_parser &parser,
			   location_t loc, వృక్షం label, gimple_seq *seq)
{
  ఒకవేళ (cfun->curr_properties & PROP_cfg)
    {
      పూర్ణాంకం dest_సూచీ;
      profile_probability prob;
      ఒకవేళ (c_parser_gimple_parse_bb_spec_అంచు_probability (label, parser,
							  &dest_సూచీ, &prob))
	{
	  parser.నెట్టు_అంచు (parser.current_bb->సూచీ, dest_సూచీ,
			    అంచు_FALLTHRU, prob);
	  తిరిగి;
	}
    }
  వృక్షం decl = lookup_label_for_goto (loc, label);
  gimple_seq_కూడు_stmt_without_update (seq, gimple_build_goto (decl));
}

/* Parse a parenthesized condition.
   gimple-condition:
     ( gimple-binary-expression )    */

స్థిర వృక్షం
c_parser_gimple_paren_condition (gimple_parser &parser)
{
  ఒకవేళ (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    తిరిగి error_mark_కణుపు;
  వృక్షం cond
    = c_parser_gimple_ద్విమాన_వ్యక్తీకరణ (parser, boolean_type_కణుపు).విలువ;
  ఒకవేళ (cond != error_mark_కణుపు
      && ! COMPARISON_CLASS_P (cond)
      && ! CONSTANT_CLASS_P (cond)
      && ! SSA_VAR_P (cond))
    {
      c_parser_error (parser, "comparison required");
      cond = error_mark_కణుపు;
    }
  ఒకవేళ (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    తిరిగి error_mark_కణుపు;
  తిరిగి cond;
}

/* Parse gimple try statement.

   try-statement:
     try { ... } finally { ... }
     try { ... } finally { ... } else { ... }

   This could support try/catch as well, but it's not implemented yet.
 */

స్థిర శూన్య
c_parser_gimple_try_stmt (gimple_parser &parser, gimple_seq *seq)
{
  gimple_seq tryseq = ఖాళీ;
  c_parser_consume_token (parser);
  c_parser_gimple_compound_statement (parser, &tryseq);

  ఒకవేళ ((c_parser_తదుపరి_token_is (parser, CPP_KEYWORD)
       && c_parser_peek_token (parser)->keyword == RID_AT_FINALLY)
      || (c_parser_తదుపరి_token_is (parser, CPP_NAME)
	  && c_parser_peek_token (parser)->id_రకం == C_ID_ID
	  && strcmp (IDENTIFIER_సూచిక (c_parser_peek_token (parser)->విలువ),
		     "finally") == 0))
    {
      gimple_seq finseq = ఖాళీ;
      c_parser_consume_token (parser);
      c_parser_gimple_compound_statement (parser, &finseq);

      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_ELSE)
	{
	  gimple_seq elsseq = ఖాళీ;
	  c_parser_consume_token (parser);
	  c_parser_gimple_compound_statement (parser, &elsseq);

	  geh_else *stmt = gimple_build_eh_else (finseq, elsseq);
	  finseq = ఖాళీ;
	  gimple_seq_కూడు_stmt_without_update (&finseq, stmt);
	}

      gtry *stmt = gimple_build_try (tryseq, finseq, GIMPLE_TRY_FINALLY);
      gimple_seq_కూడు_stmt_without_update (seq, stmt);
    }
  లేకపోతే ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_KEYWORD)
      && c_parser_peek_token (parser)->keyword == RID_AT_CATCH)
    c_parser_error (parser, "%<catch%> is not supported");
  లేకపోతే
    c_parser_error (parser, "expected %<finally%> or %<catch%>");
}

/* Parse gimple if-else statement.

   if-statement:
     if ( gimple-binary-expression ) gimple-goto-statement
     if ( gimple-binary-expression ) gimple-goto-statement \
					else gimple-goto-statement
 */

స్థిర శూన్య
c_parser_gimple_if_stmt (gimple_parser &parser, gimple_seq *seq)
{
  వృక్షం t_label = NULL_వృక్షం, f_label = NULL_వృక్షం, label;
  location_t loc;
  c_parser_consume_token (parser);
  వృక్షం cond = c_parser_gimple_paren_condition (parser);

  ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, RID_GOTO))
    {
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      ఒకవేళ (! c_parser_తదుపరి_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected label");
	  తిరిగి;
	}
      label = c_parser_peek_token (parser)->విలువ;
      c_parser_consume_token (parser);
      పూర్ణాంకం dest_సూచీ;
      profile_probability prob;
      ఒకవేళ ((cfun->curr_properties & PROP_cfg)
	  && c_parser_gimple_parse_bb_spec_అంచు_probability (label, parser,
							     &dest_సూచీ, &prob))
	parser.నెట్టు_అంచు (parser.current_bb->సూచీ, dest_సూచీ,
			  అంచు_TRUE_విలువ, prob);
      లేకపోతే
	t_label = lookup_label_for_goto (loc, label);
      ఒకవేళ (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	తిరిగి;
    }
  లేకపోతే
    {
      c_parser_error (parser, "expected goto expression");
      తిరిగి;
    }

  ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, RID_ELSE))
    c_parser_consume_token (parser);
  లేకపోతే
    {
      c_parser_error (parser, "expected else statement");
      తిరిగి;
    }

  ఒకవేళ (c_parser_తదుపరి_token_is_keyword (parser, RID_GOTO))
    {
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      ఒకవేళ (! c_parser_తదుపరి_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected label");
	  తిరిగి;
	}
      label = c_parser_peek_token (parser)->విలువ;
      c_parser_consume_token (parser);
      పూర్ణాంకం dest_సూచీ;
      profile_probability prob;
      ఒకవేళ ((cfun->curr_properties & PROP_cfg)
	  && c_parser_gimple_parse_bb_spec_అంచు_probability (label, parser,
							     &dest_సూచీ, &prob))
	parser.నెట్టు_అంచు (parser.current_bb->సూచీ, dest_సూచీ,
			  అంచు_FALSE_విలువ, prob);
      లేకపోతే
	f_label = lookup_label_for_goto (loc, label);
      ఒకవేళ (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	తిరిగి;
    }
  లేకపోతే
    {
      c_parser_error (parser, "expected goto expression");
      తిరిగి;
    }

  ఒకవేళ (cond != error_mark_కణుపు)
    gimple_seq_కూడు_stmt_without_update (seq, gimple_build_cond_from_వృక్షం (cond, t_label,
							   f_label));
}

/* Parse gimple switch-statement.

   gimple-switch-statement:
     switch (gimple-postfix-expression) gimple-case-statement

   gimple-case-statement:
     gimple-case-statement
     gimple-label-statement : gimple-goto-statement
*/

స్థిర శూన్య
c_parser_gimple_switch_stmt (gimple_parser &parser, gimple_seq *seq)
{
  c_సమాసం cond_సమాసం;
  వృక్షం case_label, label;
  auto_vec<వృక్షం> labels;
  వృక్షం default_label = NULL_వృక్షం;
  c_parser_consume_token (parser);

  ఒకవేళ (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    తిరిగి;
  cond_సమాసం = c_parser_gimple_postfix_వ్యక్తీకరణ (parser);
  ఒకవేళ (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    తిరిగి;

  ఒకవేళ (! c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    తిరిగి;

  అయితే (c_parser_తదుపరి_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_EOF))
	{
	  c_parser_error (parser, "expected statement");
	  తిరిగి;
	}

      ఎంపిక (c_parser_peek_token (parser)->keyword)
	{
	స్థితి RID_CASE:
	  {
	    c_సమాసం exp1;
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);

	    ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME)
		|| c_parser_peek_token (parser)->type == CPP_సంఖ్య)
	      exp1 = c_parser_gimple_postfix_వ్యక్తీకరణ (parser);
	    లేకపోతే
	      {
		c_parser_error (parser, "expected expression");
		తిరిగి;
	      }

	    ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COLON))
	      {
		c_parser_consume_token (parser);
		ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME))
		  {
		    label = c_parser_peek_token (parser)->విలువ;
		    c_parser_consume_token (parser);
		    వృక్షం decl = lookup_label_for_goto (loc, label);
		    case_label = build_case_label (exp1.విలువ, NULL_వృక్షం,
						   decl);
		    labels.సురక్షిత_నెట్టు (case_label);
		    ఒకవేళ (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      తిరిగి;
		  }
		లేకపోతే ఒకవేళ (! c_parser_require (parser, CPP_NAME,
					     "expected label"))
		  తిరిగి;
	      }
	    లేకపోతే ఒకవేళ (! c_parser_require (parser, CPP_SEMICOLON,
					 "expected %<:%>"))
	      తిరిగి;
	    ఆపు;
	  }
	స్థితి RID_DEFAULT:
	  {
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);
	    ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_COLON))
	      {
		c_parser_consume_token (parser);
		ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_NAME))
		  {
		    label = c_parser_peek_token (parser)->విలువ;
		    c_parser_consume_token (parser);
		    వృక్షం decl = lookup_label_for_goto (loc, label);
		    default_label = build_case_label (NULL_వృక్షం, NULL_వృక్షం,
						      decl);
		    ఒకవేళ (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      తిరిగి;
		  }
		లేకపోతే ఒకవేళ (! c_parser_require (parser, CPP_NAME,
					     "expected label"))
		  తిరిగి;
	      }
	    లేకపోతే ఒకవేళ (! c_parser_require (parser, CPP_SEMICOLON,
					 "expected %<:%>"))
	      తిరిగి;
	    ఆపు;
	  }
	అప్రమేయ:
	  c_parser_error (parser, "expected case label");
	  తిరిగి;
	}

    }
  ఒకవేళ (! c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>"))
    తిరిగి;

  ఒకవేళ (cond_సమాసం.విలువ != error_mark_కణుపు)
    {
      gswitch *s = gimple_build_switch (cond_సమాసం.విలువ, default_label, labels);
      gimple_seq_కూడు_stmt_without_update (seq, s);
    }
}

/* Parse gimple return statement.  */

స్థిర శూన్య
c_parser_gimple_return_stmt (gimple_parser &parser, gimple_seq *seq)
{
  location_t loc = c_parser_peek_token (parser)->location;
  gimple *ret = ఖాళీ;
  c_parser_consume_token (parser);
  ఒకవేళ (c_parser_తదుపరి_token_is (parser, CPP_SEMICOLON))
    {
      c_ముగింపు_gimple_return (loc, NULL_వృక్షం);
      ret = gimple_build_return (ఖాళీ);
      gimple_seq_కూడు_stmt_without_update (seq, ret);
    }
  లేకపోతే
    {
      location_t xloc = c_parser_peek_token (parser)->location;
      c_సమాసం సమాసం = c_parser_gimple_unary_వ్యక్తీకరణ (parser);
      ఒకవేళ (సమాసం.విలువ != error_mark_కణుపు)
	{
	  c_ముగింపు_gimple_return (xloc, సమాసం.విలువ);
	  ret = gimple_build_return (సమాసం.విలువ);
	  gimple_seq_కూడు_stmt_without_update (seq, ret);
	}
    }
}

/* Support function for c_parser_gimple_return_stmt.  */

స్థిర శూన్య
c_ముగింపు_gimple_return (location_t loc, వృక్షం retval)
{
  వృక్షం valtype = వృక్షం_TYPE (వృక్షం_TYPE (current_function_decl));

  /* Use the expansion point to handle cases such as returning NULL
     in a function returning void.  */
  location_t xloc = expansion_బిందువు_location_if_లోపల_system_శీర్షిక (loc);

  ఒకవేళ (వృక్షం_THIS_VOLATILE (current_function_decl))
    warning_at (xloc, 0,
		"function declared %<noreturn%> has a %<return%> statement");

  ఒకవేళ (! retval)
    current_function_returns_null = 1;
  లేకపోతే ఒకవేళ (valtype == 0 || VOID_TYPE_P (valtype))
    {
      current_function_returns_null = 1;
      ఒకవేళ (వృక్షం_సంకేతం (వృక్షం_TYPE (retval)) != VOID_TYPE)
	{
	  error_at
	    (xloc, "%<return%> with a value, in function returning void");
	  inform (DECL_ఆధారం_LOCATION (current_function_decl),
		  "declared here");
	}
    }
  లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (valtype) != వృక్షం_సంకేతం (వృక్షం_TYPE (retval)))
    {
      error_at
	(xloc, "invalid conversion in return statement");
      inform (DECL_ఆధారం_LOCATION (current_function_decl),
	      "declared here");
    }
  తిరిగి;
}
