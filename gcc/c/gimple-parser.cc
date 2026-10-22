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

#अन्तर्भाव "config.h"
#अन्तर्भाव "system.h"
#अन्तर्भाव "coretypes.h"
#अन्तर्भाव "target.h"
#अन्तर्भाव "function.h"
#अन्तर्भाव "c-tree.h"
#अन्तर्भाव "timevar.h"
#अन्तर्भाव "stringpool.h"
#अन्तर्भाव "cgraph.h"
#अन्तर्भाव "attribs.h"
#अन्तर्भाव "stor-layout.h"
#अन्तर्भाव "varasm.h"
#अन्तर्भाव "trans-mem.h"
#अन्तर्भाव "c-family/c-pragma.h"
#अन्तर्भाव "c-lang.h"
#अन्तर्भाव "c-family/c-objc.h"
#अन्तर्भाव "plugin.h"
#अन्तर्भाव "builtins.h"
#अन्तर्भाव "gomp-constants.h"
#अन्तर्भाव "c-family/c-indentation.h"
#अन्तर्भाव "gimple-expr.h"
#अन्तर्भाव "context.h"
#अन्तर्भाव "gcc-rich-location.h"
#अन्तर्भाव "c-parser.h"
#अन्तर्भाव "tree-vrp.h"
#अन्तर्भाव "tree-pass.h"
#अन्तर्भाव "tree-pretty-print.h"
#अन्तर्भाव "tree.h"
#अन्तर्भाव "basic-block.h"
#अन्तर्भाव "gimple.h"
#अन्तर्भाव "gimple-pretty-print.h"
#अन्तर्भाव "tree-ssa.h"
#अन्तर्भाव "pass_manager.h"
#अन्तर्भाव "tree-ssanames.h"
#अन्तर्भाव "gimple-ssa.h"
#अन्तर्भाव "tree-dfa.h"
#अन्तर्भाव "internal-fn.h"
#अन्तर्भाव "cfg.h"
#अन्तर्भाव "cfghooks.h"
#अन्तर्भाव "bitmap.h"
#अन्तर्भाव "cfganal.h"
#अन्तर्भाव "tree-cfg.h"
#अन्तर्भाव "gimple-iterator.h"
#अन्तर्भाव "cfgloop.h"
#अन्तर्भाव "tree-phinodes.h"
#अन्तर्भाव "tree-into-ssa.h"


/* GIMPLE parser state.  */

वर्ग gimple_parser
{
सार्वजनिक:
  gimple_parser (c_parser *p) : parser (p), धाराः(), current_bb(रिक्त) {}
  /* c_parser is not visible here, use composition and fake inheritance
     via a conversion operator.  */
  संक्रियकः c_parser *() { प्रत्यागम parser; }
  c_parser *parser;

  /* CFG build state.  */
  वर्ग gimple_parser_edge
  {
  सार्वजनिक:
    पूर्णाङ्क src;
    पूर्णाङ्क dest;
    पूर्णाङ्क flags;
    profile_probability probability;
  };
  auto_vec<gimple_parser_edge> धाराः;
  basic_खण्डम् current_bb;

  शून्य प्रक्षिप_edge (पूर्णाङ्क, पूर्णाङ्क, पूर्णाङ्क, profile_probability);
};

शून्य
gimple_parser::प्रक्षिप_edge (पूर्णाङ्क src, पूर्णाङ्क dest, पूर्णाङ्क flags,
			  profile_probability prob)
{
  gimple_parser_edge e;
  e.src = src;
  e.dest = dest;
  e.flags = flags;
  e.probability = prob;
  धाराः.safe_प्रक्षिप (e);
}


/* Gimple parsing functions.  */
स्थिर तार्किक c_parser_gimple_compound_statement (gimple_parser &, gimple_seq *);
स्थिर शून्य c_parser_gimple_label (gimple_parser &, gimple_seq *);
स्थिर शून्य c_parser_gimple_statement (gimple_parser &, gimple_seq *);
स्थिर संरचना c_व्यञ्जकम् c_parser_gimple_द्विमान_expression (gimple_parser &, वृक्षः);
स्थिर संरचना c_व्यञ्जकम् c_parser_gimple_unary_expression (gimple_parser &);
स्थिर संरचना c_व्यञ्जकम् c_parser_gimple_postfix_expression
			(gimple_parser &, वृक्षः = error_mark_ग्रन्थिः);
स्थिर संरचना c_व्यञ्जकम् c_parser_gimple_postfix_expression_after_primary
			(gimple_parser &, location_t, संरचना c_व्यञ्जकम्);
स्थिर शून्य c_parser_gimple_declaration (gimple_parser &);
स्थिर शून्य c_parser_gimple_goto_stmt (gimple_parser &, location_t,
				       वृक्षः, gimple_seq *);
स्थिर शून्य c_parser_gimple_try_stmt (gimple_parser &, gimple_seq *);
स्थिर शून्य c_parser_gimple_if_stmt (gimple_parser &, gimple_seq *);
स्थिर शून्य c_parser_gimple_switch_stmt (gimple_parser &, gimple_seq *);
स्थिर शून्य c_parser_gimple_return_stmt (gimple_parser &, gimple_seq *);
स्थिर शून्य c_finish_gimple_return (location_t, वृक्षः);
स्थिर वृक्षः c_parser_gimple_paren_condition (gimple_parser &);
स्थिर शून्य c_parser_gimple_व्यञ्जकम्_list (gimple_parser &, vec<वृक्षः> *);


/* Much like parser_build_unary_op, but avoid applying default conversions.  */

स्थिर c_व्यञ्जकम्
gimple_parser_build_unary_op (location_t loc,
			      गणना वृक्षः_संहिता_2 संहिता, संरचना c_व्यञ्जकम् arg)
{
  संरचना c_व्यञ्जकम् परिणाम;

  परिणाम.original_संहिता = संहिता;
  परिणाम.original_type = रिक्त;
  परिणाम.m_decimal = 0;

  यदि (reject_gcc_builtin (arg.मानम्))
    {
      परिणाम.मानम् = error_mark_ग्रन्थिः;
    }
  अन्यथा
    {
      परिणाम.मानम् = build_unary_op (loc, संहिता, arg.मानम्, सत्य);

      यदि (वृक्षः_अतिप्रवाहः_P (परिणाम.मानम्) && !वृक्षः_अतिप्रवाहः_P (arg.मानम्))
	अतिप्रवाहः_warning (loc, परिणाम.मानम्, arg.मानम्);
    }

  /* We are typically called when parsing a prefix token at LOC acting on
     ARG.  Reflect this by updating the source range of the result to
     start at LOC and end at the end of ARG.  */
  समुच्चयः_c_व्यञ्जकम्_source_range (&परिणाम,
			   loc, arg.get_finish ());

  प्रत्यागम परिणाम;
}

/* See if VAL is an identifier matching __BB<num> and return <num>
   in *INDEX.  */

स्थिर तार्किक
c_parser_gimple_parse_bb_spec (वृक्षः val, पूर्णाङ्क *सूचकांक)
{
  यदि (!startswith (IDENTIFIER_POINTER (val), "__BB"))
    प्रत्यागम असत्य;

  ध्रुव वर्ण *bb = IDENTIFIER_POINTER (val) + 4;
  यदि (! ISDIGIT (*bb))
    प्रत्यागम असत्य;

  वर्ण *pend;
  errno = 0;
  ध्रुव अचिह्नित दीर्घ सङ्ख्या = strtoul (bb, &pend, 10);
  यदि (errno == ERANGE
      || *pend != '\0'
      || सङ्ख्या > अधिकतम_पूर्णाङ्कः)
    प्रत्यागम असत्य;

  *सूचकांक = सङ्ख्या;
  प्रत्यागम सत्य;
}

/* See if VAL is an identifier matching __BB<num> and return <num>
   in *INDEX.  Return true if so and parse also FREQUENCY of
   the edge.  */


स्थिर तार्किक
c_parser_gimple_parse_bb_spec_edge_probability (वृक्षः val,
						gimple_parser &parser,
						पूर्णाङ्क *सूचकांक,
						profile_probability
						*probability)
{
  तार्किक return_p = c_parser_gimple_parse_bb_spec (val, सूचकांक);
  यदि (return_p)
    {
      *probability = profile_probability::uninitialized ();
      /* Parse frequency if provided.  */
      यदि (c_parser_अग्र_token_is (parser, CPP_OPEN_PAREN))
	{
	  वृक्षः f;
	  c_parser_consume_token (parser);
	  यदि (!c_parser_अग्र_token_is (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected frequency quality");
	      प्रत्यागम असत्य;
	    }

	  profile_quality quality;
	  ध्रुव वर्ण *v
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्);
	  यदि (!parse_profile_quality (v, &quality))
	    {
	      c_parser_error (parser, "unknown profile quality");
	      प्रत्यागम असत्य;
	    }

	  c_parser_consume_token (parser);
	  यदि (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    प्रत्यागम असत्य;

	  यदि (!c_parser_अग्र_token_is (parser, CPP_सङ्ख्या)
	      || (वृक्षः_संहिता (f = c_parser_peek_token (parser)->मानम्)
		  != INTEGER_CST))
	    {
	      c_parser_error (parser, "expected frequency value");
	      प्रत्यागम असत्य;
	    }

	  अचिह्नित पूर्णाङ्क मानम् = वृक्षः_INT_CST_नीचः (f);
	  *probability = profile_probability (मानम्, quality);

	  c_parser_consume_token (parser);
	  यदि (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    प्रत्यागम असत्य;

	  यदि (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    प्रत्यागम असत्य;
	}

      प्रत्यागम सत्य;
    }

  प्रत्यागम असत्य;

}

/* Parse the body of a function declaration marked with "__GIMPLE".  */

शून्य
c_parser_parse_gimple_body (c_parser *cparser, वर्ण *gimple_pass,
			    गणना c_declspec_il cdil,
			    profile_गणनम् प्रविष्टिः_bb_गणनम्)
{
  gimple_parser parser (cparser);
  gimple_seq seq = रिक्त;
  gimple_seq body = रिक्त;
  वृक्षः stmt = प्रक्षिप_stmt_list ();
  प्रक्षिप_scope ();
  location_t loc1 = c_parser_peek_token (parser)->location;

  cfun->pass_startwith = gimple_pass;
  init_वृक्षः_ssa (cfun);

  यदि (cdil == cdil_gimple)
    /* While we have SSA names in the IL we do not have a CFG built yet
       and PHIs are represented using a PHI internal function.  We do
       have lowered control flow and exception handling (well, we do not
       have parser support for EH yet).  But as we still have BINDs
       we have to go through lowering again.  */
    cfun->curr_properties = PROP_gimple_any;
  अन्यथा
    {
      /* We have at least cdil_gimple_cfg.  */
      gimple_पञ्जिकाकोशः_cfg_hooks ();
      init_रिक्तानि_वृक्षः_cfg ();
      parser.current_bb = प्रविष्टिः_खण्डम्_PTR_FOR_FN (cfun);
      /* Initialize the bare loop structure - we are going to only
         mark headers and leave the rest to fixup.  */
      समुच्चयः_loops_for_fn (cfun, ggc_cleared_alloc<संरचना loops> ());
      init_loops_structure (cfun, loops_for_fn (cfun), 1);
      loops_state_समुच्चयः (cfun, LOOPS_NEED_FIXUP|LOOPS_MAY_HAVE_गुणजः_LATCHES);
      cfun->curr_properties
	|= PROP_gimple_lcf | PROP_gimple_leh | PROP_cfg | PROP_loops;
      यदि (cdil == cdil_gimple_ssa)
	{
	  init_ssa_operands (cfun);
	  cfun->curr_properties |= PROP_ssa;
	}
    }

  यदि (! c_parser_gimple_compound_statement (parser, &seq)
      && cdil == cdil_gimple)
    {
      gimple *ret = gimple_build_return (रिक्त);
      gimple_seq_सङ्कलय_stmt_without_update (&seq, ret);
    }

  वृक्षः खण्डम् = निष्कासय_scope ();
  stmt = निष्कासय_stmt_list (stmt);
  stmt = c_build_bind_व्यञ्जकम् (loc1, खण्डम्, stmt);

  खण्डम् = DECL_INITIAL (current_function_decl);
  खण्डम्_SUBBLOCKS (खण्डम्) = NULL_वृक्षः;
  खण्डम्_CHAIN (खण्डम्) = NULL_वृक्षः;
  वृक्षः_ASM_WRITTEN (खण्डम्) = 1;

  यदि (cdil == cdil_gimple)
    {
      gbind *bind_stmt = gimple_build_bind (BIND_व्यञ्जकम्_VARS (stmt), रिक्त,
					    BIND_व्यञ्जकम्_खण्डम् (stmt));
      gimple_bind_समुच्चयः_body (bind_stmt, seq);
      gimple_seq_सङ्कलय_stmt_without_update (&body, bind_stmt);
      gimple_समुच्चयः_body (current_function_decl, body);
    }
  अन्यथा
    {
      /* Control-flow and binds are lowered, record local decls.  */
      प्रति (वृक्षः var = BIND_व्यञ्जकम्_VARS (stmt); var; var = DECL_CHAIN (var))
	यदि (VAR_P (var)
	    && !DECL_EXTERNAL (var))
	  {
	    सङ्कलय_local_decl (cfun, var);
	    /* When the middle-end re-gimplifies any expression we might
	       run into the assertion that we've seen the decl in a BIND.  */
	    यदि (!वृक्षः_STATIC (var))
	      DECL_आलोकितम्_अन्तर्_BIND_व्यञ्जकम्_P (var) = 1;
	  }
      /* We have a CFG.  Build the edges.  */
      प्रति (अचिह्नित i = 0; i < parser.धाराः.दीर्घता (); ++i)
	{
	  edge e = make_edge (BASIC_खण्डम्_FOR_FN (cfun, parser.धाराः[i].src),
			      BASIC_खण्डम्_FOR_FN (cfun, parser.धाराः[i].dest),
			      parser.धाराः[i].flags);
	  e->probability = parser.धाराः[i].probability;
	}
      /* Add edges for case labels.  */
      basic_खण्डम् bb;
      FOR_EACH_BB_FN (bb, cfun)
	यदि (EDGE_गणनम् (bb->succs) == 0)
	  {
	    यदि (gswitch *sw = safe_dyn_cast <gswitch *> (*gsi_चरमः_bb (bb)))
	      प्रति (अचिह्नित i = 0; i < gimple_switch_अङ्कः_labels (sw); ++i)
		{
		  basic_खण्डम् label_bb = gimple_switch_label_bb (cfun, sw, i);
		  make_edge (bb, label_bb, 0);
		}
	  }
      /* Need those for loop fixup.  */
      calculate_dominance_info (CDI_DOMINATORS);
      /* With SSA lower PHIs parsed as internal function calls and
	 update stmts.  */
      यदि (cdil == cdil_gimple_ssa)
	{
	  /* Create PHI nodes, they are parsed into __PHI internal calls
	     and update SSA operands.  */
	  FOR_EACH_BB_FN (bb, cfun)
	    {
	      gimple_stmt_iterator gsi;
	      प्रति (gsi = gsi_start_bb (bb); !gsi_अन्तः_p (gsi);)
		{
		  gimple *stmt = gsi_stmt (gsi);
		  यदि (!gimple_call_आन्तरिकम्_p (stmt, IFN_PHI))
		    भङ्ग;

		  gphi *phi = create_phi_ग्रन्थिः (gimple_call_lhs (stmt), bb);
		  प्रति (अचिह्नित i = 0; i < gimple_call_अङ्कः_तर्काः (stmt); i += 2)
		    {
		      पूर्णाङ्क srcidx = वृक्षः_INT_CST_नीचः (gimple_call_arg (stmt, i));
		      edge e = find_edge (BASIC_खण्डम्_FOR_FN (cfun, srcidx), bb);
		      यदि (!e)
			c_parser_error (parser, "edge not found");
		      अन्यथा
			सङ्कलय_phi_arg (phi, gimple_call_arg (stmt, i + 1), e,
				     UNKNOWN_LOCATION);
		    }
		  gsi_remove (&gsi, सत्य);
		}
	      प्रति (; !gsi_अन्तः_p (gsi); gsi_अग्र (&gsi))
		update_stmt (gsi_stmt (gsi));
	    }
	  /* Fill SSA name gaps, putting them on the freelist and diagnose
	     SSA names without definition.  */
	  प्रति (अचिह्नित i = 1; i < अङ्कः_ssa_नामानि; ++i)
	    यदि (!ssa_name (i))
	      {
		वृक्षः name = make_ssa_name_fn (cfun, integer_type_ग्रन्थिः, रिक्त, i);
		release_ssa_name_fn (cfun, name);
	      }
	    अन्यथा यदि (!SSA_NAME_DEF_STMT (ssa_name (i)))
	      error ("SSA name %qE with version %d has no definition",
		     ssa_name (i), i);
	  /* No explicit virtual operands (yet).  */
	  bitmap_obstack_initialize (रिक्त);
	  update_ssa (TODO_update_ssa_only_virtuals);
	  bitmap_obstack_release (रिक्त);
	  /* ???  By flushing the freelist after virtual operand SSA rewrite
	     we keep the gaps available for re-use like needed for the
	     PR89595 testcase but then usually virtual operands would have
	     taken most of them.  The fix is obviously to make virtual
	     operands explicit in the SSA IL.  */
	  flush_ssaname_freelist ();
	}
      fix_loop_structure (रिक्त);
    }

  यदि (cfun->curr_properties & PROP_cfg)
    {
      प्रविष्टिः_खण्डम्_PTR_FOR_FN (cfun)->गणनम् = प्रविष्टिः_bb_गणनम्;
      gcov_type t = param_gimple_fe_computed_hot_bb_देहली;
      समुच्चयः_hot_bb_देहली (t);
      update_max_bb_गणनम् ();
      cgraph_ग्रन्थिः::get_create (cfun->decl);
      cgraph_edge::rebuild_धाराः ();
    }

  /* Perform IL validation and if any error is found abort compilation
     of this function by zapping its body.  */
  यदि ((cfun->curr_properties & PROP_cfg)
      && verify_gimple_अन्तर्_cfg (cfun, असत्य, असत्य))
    init_रिक्तानि_वृक्षः_cfg ();
  अन्यथा यदि (!(cfun->curr_properties & PROP_cfg)
	   && verify_gimple_अन्तर्_seq (gimple_body (current_function_decl), असत्य))
    gimple_समुच्चयः_body (current_function_decl, रिक्त);

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

स्थिर तार्किक
c_parser_gimple_compound_statement (gimple_parser &parser, gimple_seq *seq)
{
  तार्किक return_p = असत्य;

  यदि (! c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    प्रत्यागम असत्य;

  /* A compound statement starts with optional declarations.  */
  यावत् (c_parser_अग्र_tokens_start_declaration (parser))
    {
      c_parser_gimple_declaration (parser);
      यदि (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	प्रत्यागम असत्य;
    }

  यावत् (c_parser_अग्र_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      यदि (c_parser_error (parser))
	{
	  c_parser_skip_until_प्राप्तम् (parser, CPP_CLOSE_BRACE, रिक्त);
	  प्रत्यागम return_p;
	}
      अन्यथा यदि (c_parser_अग्र_token_is (parser, CPP_EOF))
	{
	  c_parser_error (parser, "expected declaration or statement");
	  प्रत्यागम return_p;
	}

      विकल्प (c_parser_peek_token (parser)->type)
	{
	पक्ष CPP_KEYWORD:
	  विकल्प (c_parser_peek_token (parser)->keyword)
	    {
	    पक्ष RID_AT_TRY:
	      c_parser_gimple_try_stmt (parser, seq);
	      भङ्ग;
	    पक्ष RID_IF:
	      c_parser_gimple_if_stmt (parser, seq);
	      भङ्ग;
	    पक्ष RID_SWITCH:
	      c_parser_gimple_switch_stmt (parser, seq);
	      भङ्ग;
	    पक्ष RID_GOTO:
	      {
		location_t loc = c_parser_peek_token (parser)->location;
		c_parser_consume_token (parser);
		यदि (c_parser_अग्र_token_is (parser, CPP_NAME))
		  {
		    वृक्षः label = c_parser_peek_token (parser)->मानम्;
		    c_parser_consume_token (parser);
		    c_parser_gimple_goto_stmt (parser, loc, label, seq);
		    यदि (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      प्रत्यागम return_p;
		  }
		}
	      भङ्ग;
	    पक्ष RID_RETURN:
	      return_p = सत्य;
	      c_parser_gimple_return_stmt (parser, seq);
	      यदि (! c_parser_require (parser, CPP_SEMICOLON,
				      "expected %<;%>"))
		प्रत्यागम return_p;
	      यदि (cfun->curr_properties & PROP_cfg)
		parser.प्रक्षिप_edge (parser.current_bb->सूचकांक, EXIT_खण्डम्, 0,
				  profile_probability::uninitialized ());
	      भङ्ग;
	    स्वभाव:
	      गच्छ व्यञ्जकम्_stmt;
	    }
	  भङ्ग;
	पक्ष CPP_NAME:
	  यदि (c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_gimple_label (parser, seq);
	      भङ्ग;
	    }
	  यदि (c_parser_अग्र_token_is (parser, CPP_NAME)
	      && c_parser_peek_token (parser)->id_विधा == C_ID_ID
	      && वाक्यं_तुलय (IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्),
			 "try") == 0)
	    {
	      c_parser_gimple_try_stmt (parser, seq);
	      भङ्ग;
	    }
	  /* Basic block specification.
	     __BB (index, ...)  */
	  यदि ((cfun->curr_properties & PROP_cfg)
	      && !वाक्यं_तुलय (IDENTIFIER_POINTER
			    (c_parser_peek_token (parser)->मानम्), "__BB"))
	    {
	      c_parser_consume_token (parser);
	      यदि (! c_parser_require (parser, CPP_OPEN_PAREN,
				      "expected %<(%>"))
		प्रत्यागम return_p;
	      यदि (c_parser_अग्र_token_is_not (parser, CPP_सङ्ख्या))
		{
		  c_parser_error (parser, "expected block index");
		  प्रत्यागम return_p;
		}
	      वृक्षः tnum = c_parser_peek_token (parser)->मानम्;
	      यदि (वृक्षः_संहिता (tnum) != INTEGER_CST)
		{
		  c_parser_error (parser, "expected block index");
		  प्रत्यागम return_p;
		}
	      पूर्णाङ्क सूचकांक = वृक्षः_INT_CST_नीचः (tnum);
	      यदि (सूचकांक < अङ्कः_FIXED_खण्डानि
		  || (सूचकांक < चरमः_basic_खण्डम्_for_fn (cfun)
		      && BASIC_खण्डम्_FOR_FN (cfun, सूचकांक) != रिक्त))
		{
		  c_parser_error (parser, "invalid block index");
		  प्रत्यागम return_p;
		}
	      पूर्णाङ्क is_loop_शीर्षकम्_सम्बन्धि = -1;
	      profile_गणनम् bb_गणनम् = profile_गणनम्::uninitialized ();
	      c_parser_consume_token (parser);
	      यावत् (c_parser_अग्र_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  यदि (! c_parser_अग्र_token_is (parser, CPP_NAME))
		    {
		      c_parser_error (parser, "expected block specifier");
		      प्रत्यागम return_p;
		    }
		  /* loop_header (NUM)  */
		  यदि (!वाक्यं_तुलय (IDENTIFIER_POINTER
			         (c_parser_peek_token (parser)->मानम्),
			       "loop_header"))
		    {
		      c_parser_consume_token (parser);
		      यदि (! c_parser_require (parser, CPP_OPEN_PAREN,
					      "expected %<(%>"))
			प्रत्यागम return_p;
		      वृक्षः loop_अङ्कः;
		      यदि (! c_parser_अग्र_token_is (parser, CPP_सङ्ख्या)
			  || वृक्षः_संहिता (loop_अङ्कः
					  = c_parser_peek_token (parser)->मानम्)
			       != INTEGER_CST)
			{
			  c_parser_error (parser, "expected loop number");
			  प्रत्यागम return_p;
			}
		      c_parser_consume_token (parser);
		      is_loop_शीर्षकम्_सम्बन्धि = वृक्षः_INT_CST_नीचः (loop_अङ्कः);
		      यदि (! c_parser_require (parser, CPP_CLOSE_PAREN,
					      "expected %<)%>"))
			प्रत्यागम return_p;
		    }
		  /* Parse profile: quality(value) */
		  अन्यथा
		    {
		      वृक्षः q;
		      profile_quality quality;
		      वृक्षः v = c_parser_peek_token (parser)->मानम्;
		      यदि (!parse_profile_quality (IDENTIFIER_POINTER (v),
						  &quality))
			{
			  c_parser_error (parser, "unknown block specifier");
			  प्रत्यागम असत्य;
			}

		      c_parser_consume_token (parser);
		      यदि (!c_parser_require (parser, CPP_OPEN_PAREN,
					     "expected %<(%>"))
			प्रत्यागम असत्य;

		      यदि (!c_parser_अग्र_token_is (parser, CPP_सङ्ख्या)
			  || (वृक्षः_संहिता (q = c_parser_peek_token (parser)->मानम्)
			      != INTEGER_CST))
			{
			  c_parser_error (parser, "expected count value");
			  प्रत्यागम असत्य;
			}

		      bb_गणनम्
			= profile_गणनम्::from_gcov_type (वृक्षः_INT_CST_नीचः (q),
							 quality);
		      c_parser_consume_token (parser);
		      यदि (! c_parser_require (parser, CPP_CLOSE_PAREN,
					      "expected %<)%>"))
			प्रत्यागम return_p;
		    }
		}
	      यदि (! c_parser_require (parser, CPP_CLOSE_PAREN,
				      "expected %<)%>")
		  || ! c_parser_require (parser, CPP_COLON,
					 "expected %<:%>"))
		प्रत्यागम return_p;

	      /* Put stmts parsed in the current block.  */
	      यदि (!gimple_seq_रिक्तानि_p (*seq))
		{
		  यदि (!parser.current_bb)
		    c_parser_error (parser, "stmts without block");
		  अन्यथा
		    {
		      gimple_stmt_iterator gsi
			= gsi_start_bb (parser.current_bb);
		      gsi_निवेशय_seq_after_without_update (&gsi, *seq,
							   GSI_CONTINUE_LINKING);
		    }
		  *seq = रिक्त;
		}

	      /* Build an empty block with specified index, linking them
		 in source order.  */
	      basic_खण्डम् bb = alloc_खण्डम् ();
	      bb->सूचकांक = सूचकांक;
	      link_खण्डम् (bb, (parser.current_bb ? parser.current_bb
			       : प्रविष्टिः_खण्डम्_PTR_FOR_FN (cfun)));
	      यदि (basic_खण्डम्_info_for_fn (cfun)->दीर्घता () <= (आकार_t)सूचकांक)
		vec_safe_grow_cleared (basic_खण्डम्_info_for_fn (cfun),
				       सूचकांक + 1, सत्य);
	      समुच्चयः_BASIC_खण्डम्_FOR_FN (cfun, सूचकांक, bb);
	      यदि (चरमः_basic_खण्डम्_for_fn (cfun) <= सूचकांक)
		चरमः_basic_खण्डम्_for_fn (cfun) = सूचकांक + 1;
	      n_basic_खण्डानि_for_fn (cfun)++;
	      यदि (parser.current_bb->सूचकांक == प्रविष्टिः_खण्डम्)
		parser.प्रक्षिप_edge (प्रविष्टिः_खण्डम्, bb->सूचकांक, EDGE_FALLTHRU,
				  profile_probability::always ());

	      /* We leave the proper setting to fixup.  */
	      वर्ग loop *loop_father = loops_for_fn (cfun)->वृक्षः_मूलम्;
	      /* If the new block is a loop header, allocate a loop
		 struct.  Fixup will take care of proper placement within
		 the loop tree.  */
	      यदि (is_loop_शीर्षकम्_सम्बन्धि != -1)
		{
		  यदि (सङ्ख्या_सम्बन्धि_loops (cfun) > (अचिह्नित)is_loop_शीर्षकम्_सम्बन्धि
		      && get_loop (cfun, is_loop_शीर्षकम्_सम्बन्धि) != रिक्त)
		    {
		      c_parser_error (parser, "duplicate loop header");
		    }
		  अन्यथा
		    {
		      वर्ग loop *loop = alloc_loop ();
		      loop->अङ्कः = is_loop_शीर्षकम्_सम्बन्धि;
		      loop->शीर्षकम् = bb;
		      यदि (सङ्ख्या_सम्बन्धि_loops (cfun) <= (अचिह्नित)is_loop_शीर्षकम्_सम्बन्धि)
			vec_safe_grow_cleared (loops_for_fn (cfun)->larray,
					       is_loop_शीर्षकम्_सम्बन्धि + 1, सत्य);
		      (*loops_for_fn (cfun)->larray)[is_loop_शीर्षकम्_सम्बन्धि] = loop;
		      flow_loop_वृक्षः_ग्रन्थिः_सङ्कलय (loops_for_fn (cfun)->वृक्षः_मूलम्,
					       loop);
		    }
		  loop_father = get_loop (cfun, is_loop_शीर्षकम्_सम्बन्धि);
		}
	      bb->loop_father = loop_father;
	      bb->गणनम् = bb_गणनम्;

	      /* Stmts now go to the new block.  */
	      parser.current_bb = bb;
	      भङ्ग;
	    }
	  गच्छ व्यञ्जकम्_stmt;

	पक्ष CPP_SEMICOLON:
	  {
	    /* Empty stmt.  */
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);
	    gimple *nop = gimple_build_nop ();
	    gimple_समुच्चयः_location (nop, loc);
	    gimple_seq_सङ्कलय_stmt_without_update (seq, nop);
	    भङ्ग;
	  }

	पक्ष CPP_CLOSE_PAREN:
	पक्ष CPP_CLOSE_वर्गफलम्:
	  /* Avoid infinite loop in error recovery:
	     c_parser_skip_until_found stops at a closing nesting
	     delimiter without consuming it, but here we need to consume
	     it to proceed further.  */
	  c_parser_error (parser, "expected statement");
	  c_parser_consume_token (parser);
	भङ्ग;

	स्वभाव:
व्यञ्जकम्_stmt:
	  c_parser_gimple_statement (parser, seq);
	  यदि (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	    c_parser_skip_until_प्राप्तम् (parser, CPP_SEMICOLON, रिक्त);
	}
    }
  c_parser_consume_token (parser);

  /* Put stmts parsed in the current block.  */
  यदि ((cfun->curr_properties & PROP_cfg)
      && !gimple_seq_रिक्तानि_p (*seq))
    {
      यदि (!parser.current_bb)
	c_parser_error (parser, "stmts without block");
      अन्यथा
	{
	  gimple_stmt_iterator gsi = gsi_start_bb (parser.current_bb);
	  gsi_निवेशय_seq_after_without_update (&gsi, *seq,
					       GSI_CONTINUE_LINKING);
	}
      *seq = रिक्त;
    }

  प्रत्यागम return_p;
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

स्थिर शून्य
c_parser_gimple_statement (gimple_parser &parser, gimple_seq *seq)
{
  संरचना c_व्यञ्जकम् lhs, rhs;
  gimple *नियोजय = रिक्त;
  location_t loc;
  वृक्षः arg = NULL_वृक्षः;
  auto_vec<वृक्षः> vargs;

  lhs = c_parser_gimple_unary_expression (parser);
  loc = व्यञ्जकम्_LOCATION (lhs.मानम्);
  rhs.समुच्चयः_error ();

  /* GIMPLE call statement without LHS.  */
  यदि (c_parser_अग्र_token_is (parser, CPP_SEMICOLON)
      && वृक्षः_संहिता (lhs.मानम्) == CALL_व्यञ्जकम्)
    {
      gimple *call;
      call = gimple_build_call_from_वृक्षः (lhs.मानम्, रिक्त);
      gimple_seq_सङ्कलय_stmt_without_update (seq, call);
      gimple_समुच्चयः_location (call, loc);
      प्रत्यागम;
    }

  /* All following cases are statements with LHS.  */
  यदि (! c_parser_require (parser, CPP_EQ, "expected %<=%>"))
    प्रत्यागम;

  /* Eat and ignore {v} right after the =, the has_volatile_ops is
     redundant and re-computed by the operand scanner.  */
  यदि (c_parser_अग्र_token_is (parser, CPP_OPEN_BRACE)
      && !(c_parser_peek_token (parser)->flags & पूर्व_WHITE)
      && c_parser_peek_2nd_token (parser)->type == CPP_NAME
      && !(c_parser_peek_2nd_token (parser)->flags & पूर्व_WHITE)
      && वाक्यं_तुलय ("v", IDENTIFIER_POINTER
			(c_parser_peek_2nd_token (parser)->मानम्)) == 0
      && c_parser_peek_nth_token (parser, 3)->type == CPP_CLOSE_BRACE
      && !(c_parser_peek_nth_token (parser, 3)->flags & पूर्व_WHITE))
    {
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }

  /* Cast expression.  */
  यदि (c_parser_अग्र_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_typename (c_parser_peek_2nd_token (parser)))
    {
      c_parser_consume_token (parser);
      संरचना c_type_name *type_name = c_parser_type_name (parser);
      c_parser_skip_until_प्राप्तम् (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      यदि (type_name == रिक्त)
	प्रत्यागम;
      /* ???  The actual type used in the cast expression is ignored as
         in GIMPLE it is encoded by the type of the LHS.  */
      rhs = c_parser_gimple_postfix_expression (parser);
      यदि (lhs.मानम् != error_mark_ग्रन्थिः
	  && rhs.मानम् != error_mark_ग्रन्थिः)
	{
	  गणना वृक्षः_संहिता_2 संहिता = NOP_व्यञ्जकम्;
	  यदि (FLOAT_TYPE_P (वृक्षः_TYPE (lhs.मानम्))
	      && ! FLOAT_TYPE_P (वृक्षः_TYPE (rhs.मानम्)))
	    संहिता = FLOAT_व्यञ्जकम्;
	  अन्यथा यदि (! FLOAT_TYPE_P (वृक्षः_TYPE (lhs.मानम्))
		   && FLOAT_TYPE_P (वृक्षः_TYPE (rhs.मानम्)))
	    संहिता = FIX_TRUNC_व्यञ्जकम्;
	  नियोजय = gimple_build_नियोजय (lhs.मानम्, संहिता, rhs.मानम्);
	  gimple_seq_सङ्कलय_stmt_without_update (seq, नियोजय);
	  gimple_समुच्चयः_location (नियोजय, loc);
	  प्रत्यागम;
	}
    }

  /* Unary expression.  */
  विकल्प (c_parser_peek_token (parser)->type)
    {
    पक्ष CPP_NAME:
      {
	वृक्षः id = c_parser_peek_token (parser)->मानम्;
	यदि (वाक्यं_तुलय (IDENTIFIER_POINTER (id), "__ABS") == 0
	    || वाक्यं_तुलय (IDENTIFIER_POINTER (id), "__ABSU") == 0
	    || वाक्यं_तुलय (IDENTIFIER_POINTER (id), "__MIN") == 0
	    || वाक्यं_तुलय (IDENTIFIER_POINTER (id), "__MAX") == 0
	    || वाक्यं_तुलय (IDENTIFIER_POINTER (id), "__BIT_INSERT") == 0
	    || वाक्यं_तुलय (IDENTIFIER_POINTER (id), "__VEC_PERM") == 0)
	  गच्छ build_unary_व्यञ्जकम्;
	भङ्ग;
      }
    पक्ष CPP_KEYWORD:
      यदि (c_parser_peek_token (parser)->keyword != RID_REALPART
	  && c_parser_peek_token (parser)->keyword != RID_IMAGPART)
	भङ्ग;
      /* Fallthru.  */
    पक्ष CPP_AND:
    पक्ष CPP_PLUS:
    पक्ष CPP_MINUS:
    पक्ष CPP_COMPL:
    पक्ष CPP_NOT:
    पक्ष CPP_MULT: /* pointer deref */
    build_unary_व्यञ्जकम्:
      rhs = c_parser_gimple_unary_expression (parser);
      यदि (rhs.मानम् != error_mark_ग्रन्थिः)
	{
	  नियोजय = gimple_build_नियोजय (lhs.मानम्, rhs.मानम्);
	  gimple_समुच्चयः_location (नियोजय, loc);
	  gimple_seq_सङ्कलय_stmt_without_update (seq, नियोजय);
	}
      प्रत्यागम;

    स्वभाव:;
    }

  /* GIMPLE PHI statement.  */
  यदि (c_parser_अग्र_token_is_keyword (parser, RID_PHI))
    {
      c_parser_consume_token (parser);

      यदि (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	प्रत्यागम;

      यदि (c_parser_अग्र_token_is (parser, CPP_OPEN_PAREN))
	c_parser_consume_token (parser);

      यावत् (c_parser_अग्र_token_is_not (parser, CPP_CLOSE_PAREN))
	{
	  यदि (c_parser_अग्र_token_is (parser, CPP_NAME)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      arg = c_parser_peek_token (parser)->मानम्;
	      c_parser_consume_token (parser);
	      यदि (c_parser_अग्र_token_is (parser, CPP_COLON))
		c_parser_consume_token (parser);
	      पूर्णाङ्क src_सूचकांक = -1;
	      यदि (!c_parser_gimple_parse_bb_spec (arg, &src_सूचकांक))
		c_parser_error (parser, "invalid source block specification");
	      vargs.safe_प्रक्षिप (आकार_int (src_सूचकांक));
	    }
	  अन्यथा यदि (c_parser_अग्र_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  अन्यथा
	    {
	      arg = c_parser_gimple_unary_expression (parser).मानम्;
	      vargs.safe_प्रक्षिप (arg);
	    }
	}

      c_parser_skip_until_प्राप्तम् (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");

      /* Build internal function for PHI.  */
      gcall *call_stmt = gimple_build_call_आन्तरिकम्_vec (IFN_PHI, vargs);
      gimple_call_समुच्चयः_lhs (call_stmt, lhs.मानम्);
      gimple_समुच्चयः_location (call_stmt, UNKNOWN_LOCATION);
      gimple_seq_सङ्कलय_stmt_without_update (seq, call_stmt);
      प्रत्यागम;
    }

  /* GIMPLE call with lhs.  */
  यदि (c_parser_अग्र_token_is (parser, CPP_DOT)
      || (c_parser_अग्र_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN
	  && lookup_name (c_parser_peek_token (parser)->मानम्)))
    {
      rhs = c_parser_gimple_unary_expression (parser);
      यदि (rhs.मानम् != error_mark_ग्रन्थिः)
	{
	  gimple *call = gimple_build_call_from_वृक्षः (rhs.मानम्, रिक्त);
	  gimple_call_समुच्चयः_lhs (call, lhs.मानम्);
	  gimple_seq_सङ्कलय_stmt_without_update (seq, call);
	  gimple_समुच्चयः_location (call, loc);
	}
      प्रत्यागम;
    }

  rhs = c_parser_gimple_द्विमान_expression (parser, वृक्षः_TYPE (lhs.मानम्));
  यदि (lhs.मानम् != error_mark_ग्रन्थिः
      && rhs.मानम् != error_mark_ग्रन्थिः)
    {
      /* If we parsed an identifier and the next token  is a '?' then parse
	 a conditional expression.  */
      यदि (SSA_VAR_P (rhs.मानम्) && c_parser_अग्र_token_is (parser, CPP_QUERY))
	{
	  संरचना c_व्यञ्जकम् trueval, falseval;
	  c_parser_consume_token (parser);
	  trueval = c_parser_gimple_postfix_expression (parser);
	  falseval.समुच्चयः_error ();
	  यदि (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    falseval = c_parser_gimple_postfix_expression (parser);
	  यदि (trueval.मानम् == error_mark_ग्रन्थिः
	      || falseval.मानम् == error_mark_ग्रन्थिः)
	    प्रत्यागम;
	  rhs.मानम् = build3_loc (loc,
				  सदिशम्_TYPE_P (वृक्षः_TYPE (rhs.मानम्))
				  ? VEC_COND_व्यञ्जकम् : COND_व्यञ्जकम्,
				  वृक्षः_TYPE (trueval.मानम्),
				  rhs.मानम्, trueval.मानम्, falseval.मानम्);
	}
      यदि (get_gimple_rhs_class (वृक्षः_संहिता (rhs.मानम्)) == GIMPLE_INVALID_RHS)
	{
	  c_parser_error (parser, "unexpected RHS for assignment");
	  प्रत्यागम;
	}
      नियोजय = gimple_build_नियोजय (lhs.मानम्, rhs.मानम्);
      gimple_seq_सङ्कलय_stmt_without_update (seq, नियोजय);
      gimple_समुच्चयः_location (नियोजय, loc);
    }
  प्रत्यागम;
}

/* A mapping between an identifier to a tree code for binary operations. */
स्थिर ध्रुव std::pair<ध्रुव वर्ण *, वृक्षः_संहिता_2> gimple_द्विमान_identifier_संहिता[] =
  {
    {"__MULT_HIGHPART", MULT_HIGHPART_व्यञ्जकम्},
    {"__UNLT", UNLT_व्यञ्जकम्},
    {"__UNLE", UNLE_व्यञ्जकम्},
    {"__UNGT", UNGT_व्यञ्जकम्},
    {"__UNGE", UNGE_व्यञ्जकम्},
    {"__UNEQ", UNEQ_व्यञ्जकम्},
    {"__UNORDERED", UNORDERED_व्यञ्जकम्},
    {"__ORDERED", ORDERED_व्यञ्जकम्},
    {"__LTGT", LTGT_व्यञ्जकम्},
    {"__FLOOR_DIV", FLOOR_DIV_व्यञ्जकम्},
    {"__ROUND_DIV", आवर्तनम्_DIV_व्यञ्जकम्},
    {"__EXACT_DIV", EXACT_DIV_व्यञ्जकम्},
    {"__CEIL_DIV", CEIL_DIV_व्यञ्जकम्},
    {"__FLOOR_MOD", FLOOR_MOD_व्यञ्जकम्},
    {"__ROUND_MOD", आवर्तनम्_MOD_व्यञ्जकम्},
    {"__CEIL_MOD", CEIL_MOD_व्यञ्जकम्},
    {"__ROTATE_LEFT", LROTATE_व्यञ्जकम्},
    {"__ROTATE_RIGHT", RROTATE_व्यञ्जकम्},
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

स्थिर c_व्यञ्जकम्
c_parser_gimple_द्विमान_expression (gimple_parser &parser, वृक्षः ret_type)
{
  /* Location of the binary operator.  */
  संरचना c_व्यञ्जकम् ret, lhs, rhs;
  गणना वृक्षः_संहिता_2 संहिता = ERROR_MARK;
  ret.समुच्चयः_error ();
  lhs = c_parser_gimple_postfix_expression (parser, ret_type);
  यदि (c_parser_error (parser))
    प्रत्यागम ret;
  विकल्प (c_parser_peek_token (parser)->type)
    {
    पक्ष CPP_MULT:
      संहिता = MULT_व्यञ्जकम्;
      भङ्ग;
    पक्ष CPP_DIV:
      संहिता = TRUNC_DIV_व्यञ्जकम्;
      भङ्ग;
    पक्ष CPP_MOD:
      संहिता = TRUNC_MOD_व्यञ्जकम्;
      भङ्ग;
    पक्ष CPP_PLUS:
      यदि (POINTER_TYPE_P (वृक्षः_TYPE (lhs.मानम्)))
	संहिता = POINTER_PLUS_व्यञ्जकम्;
      अन्यथा
	संहिता = PLUS_व्यञ्जकम्;
      भङ्ग;
    पक्ष CPP_MINUS:
      यदि (POINTER_TYPE_P (वृक्षः_TYPE (lhs.मानम्)))
	संहिता = POINTER_DIFF_व्यञ्जकम्;
      अन्यथा
	संहिता = MINUS_व्यञ्जकम्;
      भङ्ग;
    पक्ष CPP_LSHIFT:
      संहिता = LSHIFT_व्यञ्जकम्;
      भङ्ग;
    पक्ष CPP_RSHIFT:
      संहिता = RSHIFT_व्यञ्जकम्;
      भङ्ग;
    पक्ष CPP_LESS:
      संहिता = LT_व्यञ्जकम्;
      भङ्ग;
    पक्ष CPP_GREATER:
      संहिता = GT_व्यञ्जकम्;
      भङ्ग;
    पक्ष CPP_LESS_EQ:
      संहिता = LE_व्यञ्जकम्;
      भङ्ग;
    पक्ष CPP_GREATER_EQ:
      संहिता = GE_व्यञ्जकम्;
      भङ्ग;
    पक्ष CPP_EQ_EQ:
      संहिता = EQ_व्यञ्जकम्;
      भङ्ग;
    पक्ष CPP_NOT_EQ:
      संहिता = NE_व्यञ्जकम्;
      भङ्ग;
    पक्ष CPP_AND:
      संहिता = BIT_AND_व्यञ्जकम्;
      भङ्ग;
    पक्ष CPP_XOR:
      संहिता = BIT_XOR_व्यञ्जकम्;
      भङ्ग;
    पक्ष CPP_OR:
      संहिता = BIT_IOR_व्यञ्जकम्;
      भङ्ग;
    पक्ष CPP_AND_AND:
      c_parser_error (parser, "%<&&%> not valid in GIMPLE");
      प्रत्यागम ret;
    पक्ष CPP_OR_OR:
      c_parser_error (parser, "%<||%> not valid in GIMPLE");
      प्रत्यागम ret;
    पक्ष CPP_NAME:
      {
	वृक्षः id = c_parser_peek_token (parser)->मानम्;
	प्रति (स्वचालित &p : gimple_द्विमान_identifier_संहिता)
	  {
	    यदि (वाक्यं_तुलय (IDENTIFIER_POINTER (id), p.first) == 0)
	      {
		संहिता = p.second;
		भङ्ग;
	      }
	  }
	यदि (संहिता != ERROR_MARK)
	  भङ्ग;
      }
      /* Fallthru.  */
    स्वभाव:
      /* Not a binary expression.  */
      प्रत्यागम lhs;
    }
  location_t ret_loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  rhs = c_parser_gimple_postfix_expression (parser);
  यदि (lhs.मानम् != error_mark_ग्रन्थिः && rhs.मानम् != error_mark_ग्रन्थिः)
    ret.मानम् = build2_loc (ret_loc, संहिता, ret_type, lhs.मानम्, rhs.मानम्);
  प्रत्यागम ret;
}

/* Parse a gimple parentized binary expression.  */

स्थिर c_व्यञ्जकम्
c_parser_gimple_parentized_द्विमान_expression (gimple_parser &parser,
					      location_t op_loc,
					      वृक्षः_संहिता_2 संहिता)
{
  संरचना c_व्यञ्जकम् ret;
  ret.समुच्चयः_error ();

  c_parser_consume_token (parser);
  यदि (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    प्रत्यागम ret;
  c_व्यञ्जकम् op1 = c_parser_gimple_postfix_expression (parser);
  यदि (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    प्रत्यागम ret;
  c_व्यञ्जकम् op2 = c_parser_gimple_postfix_expression (parser);
  यदि (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    प्रत्यागम ret;

  यदि (op1.मानम् != error_mark_ग्रन्थिः && op2.मानम् != error_mark_ग्रन्थिः)
    ret.मानम् = build2_loc (op_loc,
			    संहिता, वृक्षः_TYPE (op1.मानम्), op1.मानम्, op2.मानम्);
  प्रत्यागम ret;
}

/* Parse a gimple parentized binary expression.  */

स्थिर c_व्यञ्जकम्
c_parser_gimple_parentized_ternary_expression (gimple_parser &parser,
					       location_t op_loc,
					       वृक्षः_संहिता_2 संहिता)
{
  संरचना c_व्यञ्जकम् ret;
  ret.समुच्चयः_error ();

  c_parser_consume_token (parser);
  यदि (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    प्रत्यागम ret;
  c_व्यञ्जकम् op1 = c_parser_gimple_postfix_expression (parser);
  यदि (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    प्रत्यागम ret;
  c_व्यञ्जकम् op2 = c_parser_gimple_postfix_expression (parser);
  यदि (!c_parser_require (parser, CPP_COMMA, "expected %<)%>"))
    प्रत्यागम ret;
  c_व्यञ्जकम् op3 = c_parser_gimple_postfix_expression (parser);
  यदि (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    प्रत्यागम ret;

  यदि (op1.मानम् != error_mark_ग्रन्थिः
      && op2.मानम् != error_mark_ग्रन्थिः
      && op3.मानम् != error_mark_ग्रन्थिः)
    ret.मानम् = build3_loc (op_loc,
			    संहिता, वृक्षः_TYPE (op1.मानम्),
			    op1.मानम्, op2.मानम्, op3.मानम्);
  प्रत्यागम ret;
}

/* Parse gimple unary expression.

   gimple-unary-expression:
     gimple-postfix-expression
     unary-operator gimple-postfix-expression

   unary-operator: one of
     & * + - ~ abs_expr
*/

स्थिर c_व्यञ्जकम्
c_parser_gimple_unary_expression (gimple_parser &parser)
{
  संरचना c_व्यञ्जकम् ret, op;
  location_t op_loc = c_parser_peek_token (parser)->location;
  location_t finish;
  ret.समुच्चयः_error ();
  विकल्प (c_parser_peek_token (parser)->type)
    {
    पक्ष CPP_AND:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      mark_exp_read (op.मानम्);
      प्रत्यागम gimple_parser_build_unary_op (op_loc, ADDR_व्यञ्जकम्, op);
    पक्ष CPP_MULT:
      {
	c_parser_consume_token (parser);
	op = c_parser_gimple_postfix_expression (parser);
	यदि (op.मानम् == error_mark_ग्रन्थिः)
	  प्रत्यागम ret;
	यदि (! POINTER_TYPE_P (वृक्षः_TYPE (op.मानम्)))
	  {
	    error_at (op_loc, "expected pointer as argument of unary %<*%>");
	    प्रत्यागम ret;
	  }
	finish = op.get_finish ();
	location_t combined_loc = make_location (op_loc, op_loc, finish);
	ret.मानम् = build_simple_mem_ref_loc (combined_loc, op.मानम्);
	वृक्षः_SIDE_EFFECTS (ret.मानम्)
	  = वृक्षः_THIS_VOLATILE (ret.मानम्)
	  = TYPE_VOLATILE (वृक्षः_TYPE (वृक्षः_TYPE (op.मानम्)));
	ret.src_range.m_start = op_loc;
	ret.src_range.m_finish = finish;
	प्रत्यागम ret;
      }
    पक्ष CPP_PLUS:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      प्रत्यागम gimple_parser_build_unary_op (op_loc, CONVERT_व्यञ्जकम्, op);
    पक्ष CPP_MINUS:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      प्रत्यागम gimple_parser_build_unary_op (op_loc, NEGATE_व्यञ्जकम्, op);
    पक्ष CPP_COMPL:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      प्रत्यागम gimple_parser_build_unary_op (op_loc, BIT_NOT_व्यञ्जकम्, op);
    पक्ष CPP_NOT:
      c_parser_error (parser, "%<!%> not valid in GIMPLE");
      प्रत्यागम ret;
    पक्ष CPP_KEYWORD:
      विकल्प (c_parser_peek_token (parser)->keyword)
	{
	पक्ष RID_REALPART:
	  c_parser_consume_token (parser);
	  op = c_parser_gimple_postfix_expression (parser);
	  प्रत्यागम gimple_parser_build_unary_op (op_loc, REALPART_व्यञ्जकम्, op);
	पक्ष RID_IMAGPART:
	  c_parser_consume_token (parser);
	  op = c_parser_gimple_postfix_expression (parser);
	  प्रत्यागम gimple_parser_build_unary_op (op_loc, IMAGPART_व्यञ्जकम्, op);
	स्वभाव:
	  प्रत्यागम c_parser_gimple_postfix_expression (parser);
	}
    पक्ष CPP_NAME:
	{
	  वृक्षः id = c_parser_peek_token (parser)->मानम्;
	  यदि (वाक्यं_तुलय (IDENTIFIER_POINTER (id), "__ABS") == 0)
	    {
	      c_parser_consume_token (parser);
	      op = c_parser_gimple_postfix_expression (parser);
	      प्रत्यागम gimple_parser_build_unary_op (op_loc, ABS_व्यञ्जकम्, op);
	    }
	  अन्यथा यदि (वाक्यं_तुलय (IDENTIFIER_POINTER (id), "__ABSU") == 0)
	    {
	      c_parser_consume_token (parser);
	      op = c_parser_gimple_postfix_expression (parser);
	      प्रत्यागम gimple_parser_build_unary_op (op_loc, ABSU_व्यञ्जकम्, op);
	    }
	  अन्यथा यदि (वाक्यं_तुलय (IDENTIFIER_POINTER (id), "__MIN") == 0)
	    प्रत्यागम c_parser_gimple_parentized_द्विमान_expression (parser,
								 op_loc,
								 MIN_व्यञ्जकम्);
	  अन्यथा यदि (वाक्यं_तुलय (IDENTIFIER_POINTER (id), "__MAX") == 0)
	    प्रत्यागम c_parser_gimple_parentized_द्विमान_expression (parser,
								 op_loc,
								 MAX_व्यञ्जकम्);
	  अन्यथा यदि (वाक्यं_तुलय (IDENTIFIER_POINTER (id), "__VEC_PERM") == 0)
	    प्रत्यागम c_parser_gimple_parentized_ternary_expression
			(parser, op_loc, VEC_PERM_व्यञ्जकम्);
	  अन्यथा यदि (वाक्यं_तुलय (IDENTIFIER_POINTER (id), "__BIT_INSERT") == 0)
	    {
	      /* __BIT_INSERT '(' postfix-expression, postfix-expression,
			          integer ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      यदि (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_व्यञ्जकम् op0 = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_प्राप्तम् (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_व्यञ्जकम् op1 = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_प्राप्तम् (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_व्यञ्जकम् op2 = c_parser_gimple_postfix_expression (parser);
		  यदि (वृक्षः_संहिता (op2.मानम्) != INTEGER_CST
		      || !int_माति_type_p (op2.मानम्, bitsizetype))
		    c_parser_error (parser, "expected constant offset");
		  c_parser_skip_until_प्राप्तम् (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  यदि (op0.मानम् != error_mark_ग्रन्थिः
		      && op1.मानम् != error_mark_ग्रन्थिः
		      && वृक्षः_संहिता (op2.मानम्) == INTEGER_CST)
		    ret.मानम् = build3_loc (loc, BIT_निवेशय_व्यञ्जकम्,
					    वृक्षः_TYPE (op0.मानम्),
					    op0.मानम्, op1.मानम्,
					    fold_convert (bitsizetype,
							  op2.मानम्));
		}
	      प्रत्यागम ret;
	    }
	  अन्यथा
	    प्रत्यागम c_parser_gimple_postfix_expression (parser);
	}
    स्वभाव:
      प्रत्यागम c_parser_gimple_postfix_expression (parser);
    }
}

/* Decompose ID into base name (ID until ver_offset) and VERSION.  Return
   true if ID matches a SSA name.  */

स्थिर तार्किक
c_parser_parse_ssa_name_id (वृक्षः id, अचिह्नित *संस्करणम्, अचिह्नित *ver_विस्थापनम्)
{
  ध्रुव वर्ण *token = IDENTIFIER_POINTER (id);
  ध्रुव वर्ण *var_संस्करणम् = strrchr (token, '_');
  यदि (! var_संस्करणम्)
    प्रत्यागम असत्य;

  *ver_विस्थापनम् = var_संस्करणम् - token;
  प्रति (ध्रुव वर्ण *p = var_संस्करणम् + 1; *p; ++p)
    यदि (! ISDIGIT (*p))
      प्रत्यागम असत्य;
  *संस्करणम् = atoi (var_संस्करणम् + 1);
  प्रत्यागम *संस्करणम् > 0;
}

/* Get at the actual SSA name ID with VERSION starting at VER_OFFSET.
   TYPE is the type if the SSA name is being declared.  */

स्थिर वृक्षः
c_parser_parse_ssa_name (gimple_parser &parser,
			 वृक्षः id, वृक्षः type, अचिह्नित संस्करणम्,
			 अचिह्नित ver_विस्थापनम्)
{
  वृक्षः name = NULL_वृक्षः;
  ध्रुव वर्ण *token = IDENTIFIER_POINTER (id);

  यदि (ver_विस्थापनम् == 0)
    {
      /* Anonymous unnamed SSA name.  */
      यदि (संस्करणम् < अङ्कः_ssa_नामानि)
	name = ssa_name (संस्करणम्);
      यदि (! name)
	{
	  यदि (! type)
	    {
	      c_parser_error (parser, "SSA name undeclared");
	      प्रत्यागम error_mark_ग्रन्थिः;
	    }
	  name = make_ssa_name_fn (cfun, type, रिक्त, संस्करणम्);
	}
    }
  अन्यथा
    {
      यदि (संस्करणम् < अङ्कः_ssa_नामानि)
	name = ssa_name (संस्करणम्);
      यदि (! name)
	{
	  /* Separate var name from version.  */
	  वर्ण *var_name = XNEWVEC (वर्ण, ver_विस्थापनम् + 1);
	  स्मृतिं_प्रतिलिख (var_name, token, ver_विस्थापनम्);
	  var_name[ver_विस्थापनम्] = '\0';
	  /* lookup for parent decl.  */
	  id = get_identifier (var_name);
	  वृक्षः parent = lookup_name (id);
	  XDELETEVEC (var_name);
	  यदि (! parent || parent == error_mark_ग्रन्थिः)
	    {
	      c_parser_error (parser, "base variable or SSA name undeclared");
	      प्रत्यागम error_mark_ग्रन्थिः;
	    }
	  यदि (!(VAR_P (parent)
		|| वृक्षः_संहिता (parent) == PARM_DECL
		|| वृक्षः_संहिता (parent) == परिणाम_DECL))
	    {
	      error ("invalid base %qE for SSA name", parent);
	      प्रत्यागम error_mark_ग्रन्थिः;
	    }
	  name = make_ssa_name_fn (cfun, parent,
				   gimple_build_nop (), संस्करणम्);
	}
    }

  प्रत्यागम name;
}

/* Parse a gimple call to an internal function.

   gimple-call-internal:
     . identifier ( gimple-argument-expression-list[opt] )  */

स्थिर संरचना c_व्यञ्जकम्
c_parser_gimple_call_आन्तरिकम् (gimple_parser &parser)
{
  संरचना c_व्यञ्जकम् व्यञ्जकम्;
  व्यञ्जकम्.समुच्चयः_error ();

  gcc_assert (c_parser_अग्र_token_is (parser, CPP_DOT));
  c_parser_consume_token (parser);
  location_t loc = c_parser_peek_token (parser)->location;
  यदि (!c_parser_अग्र_token_is (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_विधा != C_ID_ID)
    {
      c_parser_error (parser, "expecting internal function name");
      प्रत्यागम व्यञ्जकम्;
    }
  वृक्षः id = c_parser_peek_token (parser)->मानम्;
  आन्तरिकम्_fn ifn = lookup_आन्तरिकम्_fn (IDENTIFIER_POINTER (id));
  c_parser_consume_token (parser);
  यदि (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    {
      auto_vec<वृक्षः> exprlist;
      यदि (!c_parser_अग्र_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_gimple_व्यञ्जकम्_list (parser, &exprlist);
      c_parser_skip_until_प्राप्तम् (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      यदि (ifn == IFN_चरमः)
	error_at (loc, "unknown internal function %qE", id);
      अन्यथा
	{
	  व्यञ्जकम्.मानम् = build_call_व्यञ्जकम्_आन्तरिकम्_loc_array
	    (loc, ifn, void_type_ग्रन्थिः, exprlist.दीर्घता (),
	     exprlist.स्थानाङ्कः ());
	  व्यञ्जकम्.original_संहिता = ERROR_MARK;
	  व्यञ्जकम्.original_type = रिक्त;
	  व्यञ्जकम्.m_decimal = 0;
	}
    }
  प्रत्यागम व्यञ्जकम्;
}

/* Parse '<' type [',' alignment] '>' and return a type on success
   and NULL_TREE on error.  */

स्थिर वृक्षः
c_parser_gimple_typespec (gimple_parser &parser)
{
  संरचना c_type_name *type_name = रिक्त;
  वृक्षः alignment = NULL_वृक्षः;
  यदि (c_parser_require (parser, CPP_LESS, "expected %<<%>"))
    {
      type_name = c_parser_type_name (parser);
      /* Optional alignment.  */
      यदि (c_parser_अग्र_token_is (parser, CPP_COMMA))
	{
	  c_parser_consume_token (parser);
	  alignment
	      = c_parser_gimple_postfix_expression (parser).मानम्;
	}
      c_parser_skip_until_प्राप्तम् (parser,
				 CPP_GREATER, "expected %<>%>");
    }
  यदि (!type_name)
    प्रत्यागम NULL_वृक्षः;
  वृक्षः tem;
  वृक्षः type = groktypename (type_name, &tem, रिक्त);
  यदि (alignment)
    type = build_aligned_type (type, वृक्षः_गन्तव्यम्_uhwi (alignment));
  प्रत्यागम type;
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

स्थिर संरचना c_व्यञ्जकम्
c_parser_gimple_postfix_expression (gimple_parser &parser, वृक्षः ret_type)
{
  location_t loc = c_parser_peek_token (parser)->location;
  source_range tok_range = c_parser_peek_token (parser)->get_range ();
  संरचना c_व्यञ्जकम् व्यञ्जकम्;
  व्यञ्जकम्.समुच्चयः_error ();
  विकल्प (c_parser_peek_token (parser)->type)
    {
    पक्ष CPP_सङ्ख्या:
      व्यञ्जकम्.मानम् = c_parser_peek_token (parser)->मानम्;
      समुच्चयः_c_व्यञ्जकम्_source_range (&व्यञ्जकम्, tok_range);
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      भङ्ग;
    पक्ष CPP_CHAR:
    पक्ष CPP_CHAR16:
    पक्ष CPP_CHAR32:
    पक्ष CPP_UTF8CHAR:
    पक्ष CPP_WCHAR:
      व्यञ्जकम्.मानम् = c_parser_peek_token (parser)->मानम्;
      समुच्चयः_c_व्यञ्जकम्_source_range (&व्यञ्जकम्, tok_range);
      c_parser_consume_token (parser);
      भङ्ग;
    पक्ष CPP_STRING:
    पक्ष CPP_STRING16:
    पक्ष CPP_STRING32:
    पक्ष CPP_WSTRING:
    पक्ष CPP_UTF8STRING:
      व्यञ्जकम् = c_parser_string_literal (parser, असत्य, सत्य);
      भङ्ग;
    पक्ष CPP_DOT:
      व्यञ्जकम् = c_parser_gimple_call_आन्तरिकम् (parser);
      भङ्ग;
    पक्ष CPP_NAME:
      यदि (c_parser_peek_token (parser)->id_विधा == C_ID_ID)
	{
	  वृक्षः id = c_parser_peek_token (parser)->मानम्;
	  यदि (वाक्यं_तुलय (IDENTIFIER_POINTER (id), "__MEM") == 0)
	    {
	      /* __MEM '<' type-name [ ',' number ] '>'
	               '(' [ '(' type-name ')' ] unary-expression
			   [ '+' number ]
			   [ ',' number ]
			   [ ',' number ':' number ] ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      वृक्षः type = c_parser_gimple_typespec (parser);
	      संरचना c_व्यञ्जकम् ptr, alias_off, चरणः, सूचकांक, index2;
	      ptr.मानम् = error_mark_ग्रन्थिः;
	      alias_off.मानम् = NULL_वृक्षः;
	      चरणः.मानम् = NULL_वृक्षः;
	      सूचकांक.मानम् = NULL_वृक्षः;
	      index2.मानम् = NULL_वृक्षः;
	      अचिह्नित ह्रस्व clique = 0;
	      अचिह्नित ह्रस्व आधारः = 0;
	      तार्किक reverse_क्रमः = असत्य;
	      संरचना c_व्यञ्जकम् ro;
	      यदि (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  वृक्षः alias_type = NULL_वृक्षः;
		  /* Optional alias-type cast.  */
		  यदि (c_parser_अग्र_token_is (parser, CPP_OPEN_PAREN))
		    {
		      c_parser_consume_token (parser);
		      संरचना c_type_name *alias_type_name
			= c_parser_type_name (parser);
		      c_parser_skip_until_प्राप्तम् (parser, CPP_CLOSE_PAREN,
						 "expected %<)%>");
		      यदि (alias_type_name)
			{
			  वृक्षः tem;
			  alias_type = groktypename (alias_type_name,
						     &tem, रिक्त);
			}
		    }
		  ptr = c_parser_gimple_unary_expression (parser);
		  यदि (ptr.मानम् == error_mark_ग्रन्थिः
		      || ! POINTER_TYPE_P (वृक्षः_TYPE (ptr.मानम्)))
		    {
		      यदि (ptr.मानम् != error_mark_ग्रन्थिः)
			error_at (ptr.get_start (),
				  "invalid type of %<__MEM%> operand");
		      c_parser_skip_until_प्राप्तम् (parser, CPP_CLOSE_PAREN,
						 "expected %<)%>");
		      प्रत्यागम व्यञ्जकम्;
		    }
		  यदि (! alias_type)
		    alias_type = वृक्षः_TYPE (ptr.मानम्);
		  /* Optional constant offset.  */
		  यदि (c_parser_अग्र_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      alias_off = c_parser_gimple_postfix_expression (parser);
		    }
		  यदि (c_parser_अग्र_token_is (parser, CPP_MULT))
		    {
		      std::swap (सूचकांक, alias_off);
		      c_parser_consume_token (parser);
		      चरणः = c_parser_gimple_postfix_expression (parser);
		    }
		  अन्यथा यदि (c_parser_अग्र_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      सूचकांक = c_parser_gimple_postfix_expression (parser);
		      यदि (c_parser_अग्र_token_is (parser, CPP_MULT))
			{
			  c_parser_consume_token (parser);
			  चरणः = c_parser_gimple_postfix_expression (parser);
			}
		      अन्यथा
			std::swap (सूचकांक, index2);
		    }
		  अन्यथा यदि (alias_off.मानम्
			   && वृक्षः_संहिता (alias_off.मानम्) != INTEGER_CST)
		    std::swap (alias_off, index2);
		  यदि (c_parser_अग्र_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      index2 = c_parser_gimple_postfix_expression (parser);
		    }
		  यदि (alias_off.मानम्)
		    {
		      यदि (वृक्षः_संहिता (alias_off.मानम्) != INTEGER_CST)
			error_at (alias_off.get_start (),
				  "expected constant offset for %<__MEM%> "
				  "operand");
		      alias_off.मानम् = fold_convert (alias_type,
						      alias_off.मानम्);
		    }
		  अन्यथा
		    alias_off.मानम् = build_int_cst (alias_type, 0);
		  यदि (चरणः.मानम्)
		    {
		      यदि (वृक्षः_संहिता (चरणः.मानम्) != INTEGER_CST)
			error_at (चरणः.get_start (),
				  "expected constant step for %<__MEM%> "
				  "operand");
		    }
		  यदि (c_parser_अग्र_token_is (parser, CPP_COMMA))
		    {
		      संरचना c_व्यञ्जकम् cl, ba;
		      तार्किक has_clb = सत्य;
		      c_parser_consume_token (parser);
		      cl = c_parser_gimple_postfix_expression (parser);
		      यदि (!c_parser_अग्र_token_is (parser, CPP_COLON))
			{
			  ro = cl;
			  अचिह्नित HOST_WIDE_INT tmp = 0;
			  यदि (!वृक्षः_माति_uhwi_p (ro.मानम्)
			      || (tmp = वृक्षः_गन्तव्यम्_uhwi (ro.मानम्)) > 1)
			    error_at (ro.get_start (),
				      "invalid reverse order value");
			  reverse_क्रमः = tmp;
			  has_clb = असत्य;
			  यदि (c_parser_अग्र_token_is (parser, CPP_COMMA))
			    {
			      c_parser_consume_token (parser);
			      cl = c_parser_gimple_postfix_expression (parser);
		              has_clb = सत्य;
			    }
			}
		      यदि (has_clb
			  && c_parser_require (parser,
					       CPP_COLON, "expected %<:%>"))
			{
			  ba = c_parser_gimple_postfix_expression (parser);
			  यदि (!वृक्षः_माति_uhwi_p (cl.मानम्)
			      || !वृक्षः_माति_uhwi_p (ba.मानम्)
			      || compare_वृक्षः_int (cl.मानम्,
						   (clique = वृक्षः_गन्तव्यम्_uhwi
								(cl.मानम्)))
			      || compare_वृक्षः_int (ba.मानम्,
						   (आधारः = वृक्षः_गन्तव्यम्_uhwi
								 (ba.मानम्))))
			    error_at (cl.get_start (),
				      "invalid clique/base pair");
			}
		    }
		  c_parser_skip_until_प्राप्तम् (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      यदि (! type || c_parser_error (parser))
		{
		  c_parser_समुच्चयः_error (parser, असत्य);
		  प्रत्यागम व्यञ्जकम्;
		}
	      यदि (सूचकांक.मानम् || चरणः.मानम् || index2.मानम्)
		व्यञ्जकम्.मानम् = build5_loc (loc, TARGET_MEM_REF,
					 type, ptr.मानम्, alias_off.मानम्,
					 सूचकांक.मानम्, चरणः.मानम्, index2.मानम्);
	      अन्यथा
		व्यञ्जकम्.मानम् = build2_loc (loc, MEM_REF,
					 type, ptr.मानम्, alias_off.मानम्);
	      यदि (clique != 0)
		{
		  cfun->चरमः_clique = MAX (cfun->चरमः_clique, clique);
		  MR_DEPENDENCE_CLIQUE (व्यञ्जकम्.मानम्) = clique;
		  MR_DEPENDENCE_आधारः (व्यञ्जकम्.मानम्) = आधारः;
		}
	      यदि (reverse_क्रमः)
		{
		  यदि (वृक्षः_संहिता (व्यञ्जकम्.मानम्) == MEM_REF)
		    REF_REVERSE_STORAGE_क्रमः (व्यञ्जकम्.मानम्) = reverse_क्रमः;
		  अन्यथा
		    error_at (ro.get_start (),
			      "target mem ref cannot have reverse order");
		}
	      भङ्ग;
	    }
	  अन्यथा यदि (वाक्यं_तुलय (IDENTIFIER_POINTER (id), "__VIEW_CONVERT") == 0)
	    {
	      /* __VIEW_CONVERT '<' type-name [ ',' number ] '>'
	                        '(' postfix-expression ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      वृक्षः type = c_parser_gimple_typespec (parser);
	      यदि (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_व्यञ्जकम् op = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_प्राप्तम् (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  यदि (type && op.मानम् != error_mark_ग्रन्थिः)
		    व्यञ्जकम्.मानम् = build1_loc (loc, VIEW_CONVERT_व्यञ्जकम्,
					     type, op.मानम्);
		}
	      भङ्ग;
	    }
	  अन्यथा यदि (वाक्यं_तुलय (IDENTIFIER_POINTER (id), "__BIT_FIELD_REF") == 0)
	    {
	      /* __BIT_FIELD_REF '<' type-name [ ',' number ] '>'
	                        '(' postfix-expression, integer, integer ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      वृक्षः type = c_parser_gimple_typespec (parser);
	      यदि (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_व्यञ्जकम् op0 = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_प्राप्तम् (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_व्यञ्जकम् op1 = c_parser_gimple_postfix_expression (parser);
		  यदि (वृक्षः_संहिता (op1.मानम्) != INTEGER_CST
		      || !int_माति_type_p (op1.मानम्, bitsizetype))
		    c_parser_error (parser, "expected constant size");
		  c_parser_skip_until_प्राप्तम् (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_व्यञ्जकम् op2 = c_parser_gimple_postfix_expression (parser);
		  यदि (वृक्षः_संहिता (op2.मानम्) != INTEGER_CST
		      || !int_माति_type_p (op2.मानम्, bitsizetype))
		    c_parser_error (parser, "expected constant offset");
		  c_parser_skip_until_प्राप्तम् (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  यदि (type
		      && op0.मानम् != error_mark_ग्रन्थिः
		      && वृक्षः_संहिता (op1.मानम्) == INTEGER_CST
		      && वृक्षः_संहिता (op2.मानम्) == INTEGER_CST)
		    व्यञ्जकम्.मानम् = build3_loc (loc, BIT_क्षेत्रम्_REF, type,
					     op0.मानम्,
					     fold_convert (bitsizetype,
							   op1.मानम्),
					     fold_convert (bitsizetype,
							   op2.मानम्));
		}
	      भङ्ग;
	    }
	  अन्यथा यदि (वाक्यं_तुलय (IDENTIFIER_POINTER (id), "__CLOBBER") == 0)
	    {
	      /* __CLOBBER [ '(' bob | eob | bos | eos ')' ]  */
	      clobber_विधा विधा = CLOBBER_UNDEF;
	      c_parser_consume_token (parser);
	      यदि (c_parser_अग्र_token_is (parser, CPP_OPEN_PAREN))
		{
		  c_parser_consume_token (parser);
		  स्वचालित tok = c_parser_peek_token (parser);
		  यदि (c_parser_require (parser, CPP_NAME,
					"expected clobber kind"))
		    {
		      ध्रुव वर्ण *विधा_str = IDENTIFIER_POINTER (tok->मानम्);
		      यदि (वाक्यं_तुलय (विधा_str, "bos") == 0)
			विधा = CLOBBER_STORAGE_BEGIN;
		      अन्यथा यदि (वाक्यं_तुलय (विधा_str, "bob") == 0)
			विधा = CLOBBER_OBJECT_BEGIN;
		      अन्यथा यदि (वाक्यं_तुलय (विधा_str, "eob") == 0)
			विधा = CLOBBER_OBJECT_अन्तः;
		      अन्यथा यदि (वाक्यं_तुलय (विधा_str, "eos") == 0)
			विधा = CLOBBER_STORAGE_अन्तः;
		      अन्यथा
			c_parser_error (parser, "expected one of %<bos%>, "
					"%<eos%>, %<bob>, %<eob%>");
		    }
		  c_parser_skip_until_प्राप्तम् (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      /* We infer the (redundant) type from the LHS.  */
	      व्यञ्जकम्.मानम् = build_clobber (ret_type, विधा);
	      भङ्ग;
	    }
	  अन्यथा यदि (वाक्यं_तुलय (IDENTIFIER_POINTER (id), "_Literal") == 0)
	    {
	      /* _Literal '(' type-name ')' ( [ '-' ] constant | constructor ) */
	      c_parser_consume_token (parser);
	      वृक्षः type = NULL_वृक्षः;
	      यदि (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  संरचना c_type_name *type_name = c_parser_type_name (parser);
		  वृक्षः tem;
		  यदि (type_name)
		    type = groktypename (type_name, &tem, रिक्त);
		  c_parser_skip_until_प्राप्तम् (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      यदि (! type)
		{
		  c_parser_error (parser, "invalid _Literal");
		  प्रत्यागम व्यञ्जकम्;
		}
	      यदि (c_parser_अग्र_token_is (parser, CPP_OPEN_BRACE))
		{
		  c_parser_consume_token (parser);
		  यदि (!AGGREGATE_TYPE_P (type)
		      && !सदिशम्_TYPE_P (type))
		    {
		      c_parser_error (parser, "invalid type for _Literal with "
				      "constructor");
		      c_parser_skip_until_प्राप्तम् (parser, CPP_CLOSE_BRACE,
						 "expected %<}%>");
		      प्रत्यागम व्यञ्जकम्;
		    }
		  vec<constructor_elt, va_gc> *v = रिक्त;
		  तार्किक constant_p = सत्य;
		  यदि (सदिशम्_TYPE_P (type)
		      && !c_parser_अग्र_token_is (parser, CPP_CLOSE_BRACE))
		    {
		      vec_alloc (v, TYPE_सदिशम्_SUBPARTS (type).गन्तव्यम्_constant ());
		      कुरु
			{
			  वृक्षः val
			    = c_parser_gimple_postfix_expression (parser).मानम्;
			  यदि (! val
			      || val == error_mark_ग्रन्थिः
			      || (! CONSTANT_CLASS_P (val)
				  && ! SSA_VAR_P (val)))
			    {
			      c_parser_error (parser, "invalid _Literal");
			      प्रत्यागम व्यञ्जकम्;
			    }
			  CONSTRUCTOR_APPEND_ELT (v, NULL_वृक्षः, val);
			  यदि (! CONSTANT_CLASS_P (val))
			    constant_p = असत्य;
			  यदि (c_parser_अग्र_token_is (parser, CPP_COMMA))
			    c_parser_consume_token (parser);
			  अन्यथा
			    भङ्ग;
			}
		      यावत् (1);
		    }
		  यदि (c_parser_require (parser, CPP_CLOSE_BRACE,
					"expected %<}%>"))
		    {
		      यदि (v && constant_p)
			व्यञ्जकम्.मानम् = build_सदिशम्_from_ctor (type, v);
		      अन्यथा
			व्यञ्जकम्.मानम् = build_constructor (type, v);
		    }
		  अन्यथा
		    {
		      c_parser_skip_until_प्राप्तम् (parser, CPP_CLOSE_BRACE,
						 "expected %<}%>");
		      प्रत्यागम व्यञ्जकम्;
		    }
		}
	      अन्यथा
		{
		  तार्किक neg_p, addr_p;
		  यदि ((neg_p = c_parser_अग्र_token_is (parser, CPP_MINUS)))
		    c_parser_consume_token (parser);
		  यदि ((addr_p = c_parser_अग्र_token_is (parser, CPP_AND)))
		    c_parser_consume_token (parser);
		  वृक्षः val = c_parser_gimple_postfix_expression (parser).मानम्;
		  यदि (! val
		      || val == error_mark_ग्रन्थिः
		      || (!CONSTANT_CLASS_P (val) && !addr_p))
		    {
		      c_parser_error (parser, "invalid _Literal");
		      प्रत्यागम व्यञ्जकम्;
		    }
		  यदि (addr_p)
		    {
		      val = build1 (ADDR_व्यञ्जकम्, type, val);
		      यदि (!is_gimple_invariant_स्थानाङ्कः (val))
			{
			  c_parser_error (parser, "invalid _Literal");
			  प्रत्यागम व्यञ्जकम्;
			}
		    }
		  यदि (neg_p)
		    {
		      val = const_unop (NEGATE_व्यञ्जकम्, वृक्षः_TYPE (val), val);
		      यदि (! val)
			{
			  c_parser_error (parser, "invalid _Literal");
			  प्रत्यागम व्यञ्जकम्;
			}
		    }
		  व्यञ्जकम्.मानम् = fold_convert (type, val);
		}
	      प्रत्यागम व्यञ्जकम्;
	    }

	  /* SSA name.  */
	  अचिह्नित संस्करणम्, ver_विस्थापनम्;
	  यदि (! lookup_name (id)
	      && c_parser_parse_ssa_name_id (id, &संस्करणम्, &ver_विस्थापनम्))
	    {
	      c_parser_consume_token (parser);
	      व्यञ्जकम्.मानम् = c_parser_parse_ssa_name (parser, id, NULL_वृक्षः,
						    संस्करणम्, ver_विस्थापनम्);
	      यदि (व्यञ्जकम्.मानम् == error_mark_ग्रन्थिः)
		प्रत्यागम व्यञ्जकम्;
	      समुच्चयः_c_व्यञ्जकम्_source_range (&व्यञ्जकम्, tok_range);
	      /* For default definition SSA names.  */
	      यदि (c_parser_अग्र_token_is (parser, CPP_OPEN_PAREN)
		  && c_parser_peek_2nd_token (parser)->type == CPP_NAME
		  && वाक्यं_तुलय ("D",
			     IDENTIFIER_POINTER
			       (c_parser_peek_2nd_token (parser)->मानम्)) == 0
		  && c_parser_peek_nth_token (parser, 3)->type == CPP_CLOSE_PAREN)
		{
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		  यदि (! SSA_NAME_IS_DEFAULT_DEF (व्यञ्जकम्.मानम्))
		    {
		      यदि (!SSA_NAME_VAR (व्यञ्जकम्.मानम्))
			{
			  error_at (loc, "anonymous SSA name cannot have"
				    " default definition");
			  व्यञ्जकम्.मानम् = error_mark_ग्रन्थिः;
			  प्रत्यागम व्यञ्जकम्;
			}
		      समुच्चयः_ssa_default_def (cfun, SSA_NAME_VAR (व्यञ्जकम्.मानम्),
					   व्यञ्जकम्.मानम्);
		      SSA_NAME_DEF_STMT (व्यञ्जकम्.मानम्) = gimple_build_nop ();
		    }
		}
	    }
	  अन्यथा
	    {
	      c_parser_consume_token (parser);
	      व्यञ्जकम्.मानम्
		= build_external_ref (loc, id,
				      (c_parser_peek_token (parser)->type
				       == CPP_OPEN_PAREN), &व्यञ्जकम्.original_type);
	      समुच्चयः_c_व्यञ्जकम्_source_range (&व्यञ्जकम्, tok_range);
	    }
	  भङ्ग;
	}
      /* Fallthru.  */
    स्वभाव:
      c_parser_error (parser, "expected expression");
      व्यञ्जकम्.समुच्चयः_error ();
      भङ्ग;
    }
  यदि (व्यञ्जकम्.मानम् == error_mark_ग्रन्थिः)
    प्रत्यागम व्यञ्जकम्;
  प्रत्यागम c_parser_gimple_postfix_expression_after_primary
    (parser, व्यञ्जकम्_LOC_OR_LOC (व्यञ्जकम्.मानम्, loc), व्यञ्जकम्);
}

/* Parse a gimple postfix expression after the initial primary or compound
   literal.  */

स्थिर संरचना c_व्यञ्जकम्
c_parser_gimple_postfix_expression_after_primary (gimple_parser &parser,
						  location_t व्यञ्जकम्_loc,
						  संरचना c_व्यञ्जकम् व्यञ्जकम्)
{
  location_t start;
  location_t finish;
  वृक्षः ident;
  location_t comp_loc;

  यावत् (सत्य)
    {
      location_t op_loc = c_parser_peek_token (parser)->location;
      विकल्प (c_parser_peek_token (parser)->type)
	{
	पक्ष CPP_OPEN_वर्गफलम्:
	  {
	    c_parser_consume_token (parser);
	    वृक्षः idx = c_parser_gimple_unary_expression (parser).मानम्;

	    यदि (! c_parser_require (parser, CPP_CLOSE_वर्गफलम्, "expected %<]%>"))
	      {
		c_parser_skip_until_प्राप्तम् (parser, CPP_CLOSE_वर्गफलम्, रिक्त);
		भङ्ग;
	      }

	    start = व्यञ्जकम्.get_start ();
	    finish = c_parser_tokens_buf (parser, 0)->location;
	    व्यञ्जकम्.मानम् = build_array_ref (op_loc, व्यञ्जकम्.मानम्, idx);
	    समुच्चयः_c_व्यञ्जकम्_source_range (&व्यञ्जकम्, start, finish);
	    व्यञ्जकम्.m_decimal = 0;

	    व्यञ्जकम्.original_संहिता = ERROR_MARK;
	    व्यञ्जकम्.original_type = रिक्त;
	    भङ्ग;
	  }
	पक्ष CPP_OPEN_PAREN:
	  {
	    /* Function call.  */
	    c_parser_consume_token (parser);
	    auto_vec<वृक्षः> exprlist;
	    यदि (! c_parser_अग्र_token_is (parser, CPP_CLOSE_PAREN))
	      c_parser_gimple_व्यञ्जकम्_list (parser, &exprlist);
	    c_parser_skip_until_प्राप्तम् (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    यदि (!FUNC_OR_विधानम्_TYPE_P (वृक्षः_TYPE (व्यञ्जकम्.मानम्)))
	      {
		c_parser_error (parser, "invalid call to non-function");
		व्यञ्जकम्.समुच्चयः_error ();
		भङ्ग;
	      }
	    व्यञ्जकम्.मानम् = build_call_array_loc
		(व्यञ्जकम्_loc, वृक्षः_TYPE (वृक्षः_TYPE (व्यञ्जकम्.मानम्)),
		 व्यञ्जकम्.मानम्, exprlist.दीर्घता (), exprlist.स्थानाङ्कः ());
	    व्यञ्जकम्.m_decimal = 0;
	    व्यञ्जकम्.original_संहिता = ERROR_MARK;
	    व्यञ्जकम्.original_type = रिक्त;
	    भङ्ग;
	  }
	पक्ष CPP_DOT:
	  {
	    /* Structure element reference.  */
	    c_parser_consume_token (parser);
	    यदि (c_parser_अग्र_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		ident = comp_tok->मानम्;
		comp_loc = comp_tok->location;
	      }
	    अन्यथा
	      {
		c_parser_error (parser, "expected identifier");
		व्यञ्जकम्.समुच्चयः_error ();
		व्यञ्जकम्.original_संहिता = ERROR_MARK;
		व्यञ्जकम्.original_type = रिक्त;
		प्रत्यागम व्यञ्जकम्;
	      }
	    start = व्यञ्जकम्.get_start ();
	    finish = c_parser_peek_token (parser)->get_finish ();
	    c_parser_consume_token (parser);
	    व्यञ्जकम्.मानम् = build_component_ref (op_loc, व्यञ्जकम्.मानम्, ident,
					      comp_loc, UNKNOWN_LOCATION);
	    समुच्चयः_c_व्यञ्जकम्_source_range (&व्यञ्जकम्, start, finish);
	    व्यञ्जकम्.m_decimal = 0;
	    व्यञ्जकम्.original_संहिता = ERROR_MARK;
	    यदि (वृक्षः_संहिता (व्यञ्जकम्.मानम्) != COMPONENT_REF)
	      व्यञ्जकम्.original_type = रिक्त;
	    अन्यथा
	      {
		/* Remember the original type of a bitfield.  */
		वृक्षः क्षेत्रम्_2 = वृक्षः_सङ्कार्यम् (व्यञ्जकम्.मानम्, 1);
		यदि (वृक्षः_संहिता (क्षेत्रम्_2) != क्षेत्रम्_DECL)
		  व्यञ्जकम्.original_type = रिक्त;
		अन्यथा
		  व्यञ्जकम्.original_type = DECL_BIT_क्षेत्रम्_TYPE (क्षेत्रम्_2);
	      }
	    भङ्ग;
	  }
	पक्ष CPP_DEREF:
	  {
	    /* Structure element reference.  */
	    यदि (!POINTER_TYPE_P (वृक्षः_TYPE (व्यञ्जकम्.मानम्)))
	      {
		c_parser_error (parser, "dereference of non-pointer");
		व्यञ्जकम्.समुच्चयः_error ();
		व्यञ्जकम्.original_संहिता = ERROR_MARK;
		व्यञ्जकम्.original_type = रिक्त;
		प्रत्यागम व्यञ्जकम्;
	      }
	    c_parser_consume_token (parser);
	    यदि (c_parser_अग्र_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		ident = comp_tok->मानम्;
		comp_loc = comp_tok->location;
	      }
	    अन्यथा
	      {
		c_parser_error (parser, "expected identifier");
		व्यञ्जकम्.समुच्चयः_error ();
		व्यञ्जकम्.original_संहिता = ERROR_MARK;
		व्यञ्जकम्.original_type = रिक्त;
		प्रत्यागम व्यञ्जकम्;
	      }
	    start = व्यञ्जकम्.get_start ();
	    finish = c_parser_peek_token (parser)->get_finish ();
	    c_parser_consume_token (parser);
	    व्यञ्जकम्.मानम् = build_component_ref (op_loc,
					      build_simple_mem_ref_loc
					        (op_loc, व्यञ्जकम्.मानम्),
					      ident, comp_loc,
					      व्यञ्जकम्.get_location ());
	    समुच्चयः_c_व्यञ्जकम्_source_range (&व्यञ्जकम्, start, finish);
	    व्यञ्जकम्.m_decimal = 0;
	    व्यञ्जकम्.original_संहिता = ERROR_MARK;
	    यदि (वृक्षः_संहिता (व्यञ्जकम्.मानम्) != COMPONENT_REF)
	      व्यञ्जकम्.original_type = रिक्त;
	    अन्यथा
	      {
		/* Remember the original type of a bitfield.  */
		वृक्षः क्षेत्रम्_2 = वृक्षः_सङ्कार्यम् (व्यञ्जकम्.मानम्, 1);
		यदि (वृक्षः_संहिता (क्षेत्रम्_2) != क्षेत्रम्_DECL)
		  व्यञ्जकम्.original_type = रिक्त;
		अन्यथा
		  व्यञ्जकम्.original_type = DECL_BIT_क्षेत्रम्_TYPE (क्षेत्रम्_2);
	      }
	    भङ्ग;
	  }
	स्वभाव:
	  प्रत्यागम व्यञ्जकम्;
	}
    }
}

/* Parse expression list.

   gimple-expr-list:
     gimple-unary-expression
     gimple-expr-list , gimple-unary-expression

 */

स्थिर शून्य
c_parser_gimple_व्यञ्जकम्_list (gimple_parser &parser, vec<वृक्षः> *ret)
{
  संरचना c_व्यञ्जकम् व्यञ्जकम्;

  व्यञ्जकम् = c_parser_gimple_unary_expression (parser);
  ret->safe_प्रक्षिप (व्यञ्जकम्.मानम्);
  यावत् (c_parser_अग्र_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      व्यञ्जकम् = c_parser_gimple_unary_expression (parser);
      ret->safe_प्रक्षिप (व्यञ्जकम्.मानम्);
    }
}

/* Parse gimple label.

   gimple-label:
     identifier :
     case constant-expression :
     default :

*/

स्थिर शून्य
c_parser_gimple_label (gimple_parser &parser, gimple_seq *seq)
{
  वृक्षः name = c_parser_peek_token (parser)->मानम्;
  location_t loc1 = c_parser_peek_token (parser)->location;
  gcc_assert (c_parser_अग्र_token_is (parser, CPP_NAME));
  c_parser_consume_token (parser);
  gcc_assert (c_parser_अग्र_token_is (parser, CPP_COLON));
  c_parser_consume_token (parser);
  वृक्षः label = define_label (loc1, name);
  यदि (label)
    gimple_seq_सङ्कलय_stmt_without_update (seq, gimple_build_label (label));
  प्रत्यागम;
}

/* Parse gimple/RTL pass list.

   gimple-or-rtl-pass-list:
     startwith("pass-name")[,{cfg,ssa}]
 */

शून्य
c_parser_gimple_or_rtl_pass_list (c_parser *parser, c_declspecs *specs)
{
  वर्ण *pass = रिक्त;

  /* Accept __GIMPLE/__RTL.  */
  यदि (c_parser_अग्र_token_is_not (parser, CPP_OPEN_PAREN))
    प्रत्यागम;
  c_parser_consume_token (parser);

  specs->प्रविष्टिः_bb_गणनम् = profile_गणनम्::uninitialized ();
  यावत् (c_parser_अग्र_token_is (parser, CPP_NAME))
    {
      profile_quality quality;
      ध्रुव वर्ण *op = IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्);
      c_parser_consume_token (parser);
      यदि (! वाक्यं_तुलय (op, "startwith"))
	{
	  यदि (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    प्रत्यागम;
	  यदि (c_parser_अग्र_token_is_not (parser, CPP_STRING))
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"expected pass name");
	      प्रत्यागम;
	    }
	  pass = xstrdup (वृक्षः_STRING_POINTER
			  (c_parser_string_literal (parser, असत्य,
						    असत्य).मानम्));
	  यदि (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<(%>"))
	    प्रत्यागम;
	}
      अन्यथा यदि (parse_profile_quality (op, &quality))
	{
	  वृक्षः q;
	  यदि (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    प्रत्यागम;

	  यदि (!c_parser_अग्र_token_is (parser, CPP_सङ्ख्या)
	      || (वृक्षः_संहिता (q = c_parser_peek_token (parser)->मानम्)
		  != INTEGER_CST))
	    {
	      c_parser_error (parser, "expected count value");
	      प्रत्यागम;
	    }

	  specs->प्रविष्टिः_bb_गणनम्
	    = profile_गणनम्::from_gcov_type (वृक्षः_INT_CST_नीचः (q), quality);
	  c_parser_consume_token (parser);
	  यदि (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    प्रत्यागम;
	}
      अन्यथा यदि (specs->declspec_il != cdil_gimple)
	/* Allow only one IL specifier and none on RTL.  */
	;
      अन्यथा यदि (! वाक्यं_तुलय (op, "cfg"))
	specs->declspec_il = cdil_gimple_cfg;
      अन्यथा यदि (! वाक्यं_तुलय (op, "ssa"))
	specs->declspec_il = cdil_gimple_ssa;
      अन्यथा
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "invalid operation");
	  प्रत्यागम;
	}
     यदि (c_parser_अग्र_token_is (parser, CPP_COMMA))
       c_parser_consume_token (parser);
    }

  यदि (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    प्रत्यागम;

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
पञ्जिकाकोशः

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

स्थिर शून्य
c_parser_gimple_declaration (gimple_parser &parser)
{
  संरचना c_declarator *declarator;
  संरचना c_declspecs *specs = build_null_declspecs ();
  c_parser_declspecs (parser, specs, सत्य, सत्य, सत्य,
		      सत्य, सत्य, सत्य, सत्य, cla_nonabstract_decl);
  finish_declspecs (specs);

  /* Provide better error recovery.  Note that a type name here is usually
     better diagnosed as a redeclaration.  */
  यदि (c_parser_अग्र_token_starts_declspecs (parser)
      && ! c_parser_अग्र_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<;%>");
      c_parser_समुच्चयः_error (parser, असत्य);
      प्रत्यागम;
    }

  तार्किक dummy = असत्य;
  declarator = c_parser_declarator (parser,
				    specs->typespec_विधा != ctsk_none,
				    C_DTR_प्रसामान्यम्, &dummy);

  यदि (!c_parser_अग्र_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_error (parser, "expected %<;%>");
      प्रत्यागम;
    }
  यदि (declarator)
    {
      /* Handle SSA name decls specially, they do not go into the identifier
         table but we simply build the SSA name for later lookup.  */
      अचिह्नित संस्करणम्, ver_विस्थापनम्;
      /* Handle SSA pointer declarations in a very simplistic ways, we
	 probably would like to call grokdeclarator in a special mode to
	 just build the type of the decl - start_decl already pushes
	 the identifier to the bindings for lookup, something we do not
	 want.  */
      संरचना c_declarator *id_declarator = declarator;
      यावत् (id_declarator->विधा == cdk_pointer)
	id_declarator = id_declarator->declarator;
      यदि (id_declarator->विधा == cdk_id
	  && (declarator->विधा == cdk_pointer
	      || is_gimple_reg_type (specs->type))
	  && c_parser_parse_ssa_name_id (id_declarator->u.id.id,
					 &संस्करणम्, &ver_विस्थापनम्)
	  /* The following restricts it to unnamed anonymous SSA names
	     which fails parsing of named ones in dumps (we could
	     decide to not dump their name for -gimple).  */
	  && ver_विस्थापनम् == 0)
	{
	  संरचना c_declarator *p = declarator;
	  वृक्षः type = specs->type;
	  यावत् (p->विधा == cdk_pointer)
	    {
	      type = build_pointer_type (type);
	      p = p->declarator;
	    }
	  c_parser_parse_ssa_name (parser, id_declarator->u.id.id, type,
				   संस्करणम्, ver_विस्थापनम्);
	}
      अन्यथा
	{
	  वृक्षः postfix_attrs = NULL_वृक्षः;
	  वृक्षः all_उपसर्गः_attrs = specs->attrs;
	  specs->attrs = रिक्त;
	  वृक्षः decl = start_decl (declarator, specs, असत्य,
				  chainon (postfix_attrs, all_उपसर्गः_attrs));
	  यदि (decl)
	    finish_decl (decl, UNKNOWN_LOCATION, NULL_वृक्षः, NULL_वृक्षः,
			 NULL_वृक्षः);
	}
    }
}

/* Parse gimple goto statement.  */

स्थिर शून्य
c_parser_gimple_goto_stmt (gimple_parser &parser,
			   location_t loc, वृक्षः label, gimple_seq *seq)
{
  यदि (cfun->curr_properties & PROP_cfg)
    {
      पूर्णाङ्क dest_सूचकांक;
      profile_probability prob;
      यदि (c_parser_gimple_parse_bb_spec_edge_probability (label, parser,
							  &dest_सूचकांक, &prob))
	{
	  parser.प्रक्षिप_edge (parser.current_bb->सूचकांक, dest_सूचकांक,
			    EDGE_FALLTHRU, prob);
	  प्रत्यागम;
	}
    }
  वृक्षः decl = lookup_label_for_goto (loc, label);
  gimple_seq_सङ्कलय_stmt_without_update (seq, gimple_build_goto (decl));
}

/* Parse a parenthesized condition.
   gimple-condition:
     ( gimple-binary-expression )    */

स्थिर वृक्षः
c_parser_gimple_paren_condition (gimple_parser &parser)
{
  यदि (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    प्रत्यागम error_mark_ग्रन्थिः;
  वृक्षः cond
    = c_parser_gimple_द्विमान_expression (parser, boolean_type_ग्रन्थिः).मानम्;
  यदि (cond != error_mark_ग्रन्थिः
      && ! COMPARISON_CLASS_P (cond)
      && ! CONSTANT_CLASS_P (cond)
      && ! SSA_VAR_P (cond))
    {
      c_parser_error (parser, "comparison required");
      cond = error_mark_ग्रन्थिः;
    }
  यदि (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    प्रत्यागम error_mark_ग्रन्थिः;
  प्रत्यागम cond;
}

/* Parse gimple try statement.

   try-statement:
     try { ... } finally { ... }
     try { ... } finally { ... } else { ... }

   This could support try/catch as well, but it's not implemented yet.
 */

स्थिर शून्य
c_parser_gimple_try_stmt (gimple_parser &parser, gimple_seq *seq)
{
  gimple_seq tryseq = रिक्त;
  c_parser_consume_token (parser);
  c_parser_gimple_compound_statement (parser, &tryseq);

  यदि ((c_parser_अग्र_token_is (parser, CPP_KEYWORD)
       && c_parser_peek_token (parser)->keyword == RID_AT_FINALLY)
      || (c_parser_अग्र_token_is (parser, CPP_NAME)
	  && c_parser_peek_token (parser)->id_विधा == C_ID_ID
	  && वाक्यं_तुलय (IDENTIFIER_POINTER (c_parser_peek_token (parser)->मानम्),
		     "finally") == 0))
    {
      gimple_seq finseq = रिक्त;
      c_parser_consume_token (parser);
      c_parser_gimple_compound_statement (parser, &finseq);

      यदि (c_parser_अग्र_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_ELSE)
	{
	  gimple_seq elsseq = रिक्त;
	  c_parser_consume_token (parser);
	  c_parser_gimple_compound_statement (parser, &elsseq);

	  geh_else *stmt = gimple_build_eh_else (finseq, elsseq);
	  finseq = रिक्त;
	  gimple_seq_सङ्कलय_stmt_without_update (&finseq, stmt);
	}

      gtry *stmt = gimple_build_try (tryseq, finseq, GIMPLE_TRY_FINALLY);
      gimple_seq_सङ्कलय_stmt_without_update (seq, stmt);
    }
  अन्यथा यदि (c_parser_अग्र_token_is (parser, CPP_KEYWORD)
      && c_parser_peek_token (parser)->keyword == RID_AT_CATCH)
    c_parser_error (parser, "%<catch%> is not supported");
  अन्यथा
    c_parser_error (parser, "expected %<finally%> or %<catch%>");
}

/* Parse gimple if-else statement.

   if-statement:
     if ( gimple-binary-expression ) gimple-goto-statement
     if ( gimple-binary-expression ) gimple-goto-statement \
					else gimple-goto-statement
 */

स्थिर शून्य
c_parser_gimple_if_stmt (gimple_parser &parser, gimple_seq *seq)
{
  वृक्षः t_label = NULL_वृक्षः, f_label = NULL_वृक्षः, label;
  location_t loc;
  c_parser_consume_token (parser);
  वृक्षः cond = c_parser_gimple_paren_condition (parser);

  यदि (c_parser_अग्र_token_is_keyword (parser, RID_GOTO))
    {
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      यदि (! c_parser_अग्र_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected label");
	  प्रत्यागम;
	}
      label = c_parser_peek_token (parser)->मानम्;
      c_parser_consume_token (parser);
      पूर्णाङ्क dest_सूचकांक;
      profile_probability prob;
      यदि ((cfun->curr_properties & PROP_cfg)
	  && c_parser_gimple_parse_bb_spec_edge_probability (label, parser,
							     &dest_सूचकांक, &prob))
	parser.प्रक्षिप_edge (parser.current_bb->सूचकांक, dest_सूचकांक,
			  EDGE_TRUE_मानम्, prob);
      अन्यथा
	t_label = lookup_label_for_goto (loc, label);
      यदि (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	प्रत्यागम;
    }
  अन्यथा
    {
      c_parser_error (parser, "expected goto expression");
      प्रत्यागम;
    }

  यदि (c_parser_अग्र_token_is_keyword (parser, RID_ELSE))
    c_parser_consume_token (parser);
  अन्यथा
    {
      c_parser_error (parser, "expected else statement");
      प्रत्यागम;
    }

  यदि (c_parser_अग्र_token_is_keyword (parser, RID_GOTO))
    {
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      यदि (! c_parser_अग्र_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected label");
	  प्रत्यागम;
	}
      label = c_parser_peek_token (parser)->मानम्;
      c_parser_consume_token (parser);
      पूर्णाङ्क dest_सूचकांक;
      profile_probability prob;
      यदि ((cfun->curr_properties & PROP_cfg)
	  && c_parser_gimple_parse_bb_spec_edge_probability (label, parser,
							     &dest_सूचकांक, &prob))
	parser.प्रक्षिप_edge (parser.current_bb->सूचकांक, dest_सूचकांक,
			  EDGE_FALSE_मानम्, prob);
      अन्यथा
	f_label = lookup_label_for_goto (loc, label);
      यदि (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	प्रत्यागम;
    }
  अन्यथा
    {
      c_parser_error (parser, "expected goto expression");
      प्रत्यागम;
    }

  यदि (cond != error_mark_ग्रन्थिः)
    gimple_seq_सङ्कलय_stmt_without_update (seq, gimple_build_cond_from_वृक्षः (cond, t_label,
							   f_label));
}

/* Parse gimple switch-statement.

   gimple-switch-statement:
     switch (gimple-postfix-expression) gimple-case-statement

   gimple-case-statement:
     gimple-case-statement
     gimple-label-statement : gimple-goto-statement
*/

स्थिर शून्य
c_parser_gimple_switch_stmt (gimple_parser &parser, gimple_seq *seq)
{
  c_व्यञ्जकम् cond_व्यञ्जकम्;
  वृक्षः case_label, label;
  auto_vec<वृक्षः> labels;
  वृक्षः default_label = NULL_वृक्षः;
  c_parser_consume_token (parser);

  यदि (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    प्रत्यागम;
  cond_व्यञ्जकम् = c_parser_gimple_postfix_expression (parser);
  यदि (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    प्रत्यागम;

  यदि (! c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    प्रत्यागम;

  यावत् (c_parser_अग्र_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      यदि (c_parser_अग्र_token_is (parser, CPP_EOF))
	{
	  c_parser_error (parser, "expected statement");
	  प्रत्यागम;
	}

      विकल्प (c_parser_peek_token (parser)->keyword)
	{
	पक्ष RID_CASE:
	  {
	    c_व्यञ्जकम् exp1;
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);

	    यदि (c_parser_अग्र_token_is (parser, CPP_NAME)
		|| c_parser_peek_token (parser)->type == CPP_सङ्ख्या)
	      exp1 = c_parser_gimple_postfix_expression (parser);
	    अन्यथा
	      {
		c_parser_error (parser, "expected expression");
		प्रत्यागम;
	      }

	    यदि (c_parser_अग्र_token_is (parser, CPP_COLON))
	      {
		c_parser_consume_token (parser);
		यदि (c_parser_अग्र_token_is (parser, CPP_NAME))
		  {
		    label = c_parser_peek_token (parser)->मानम्;
		    c_parser_consume_token (parser);
		    वृक्षः decl = lookup_label_for_goto (loc, label);
		    case_label = build_case_label (exp1.मानम्, NULL_वृक्षः,
						   decl);
		    labels.safe_प्रक्षिप (case_label);
		    यदि (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      प्रत्यागम;
		  }
		अन्यथा यदि (! c_parser_require (parser, CPP_NAME,
					     "expected label"))
		  प्रत्यागम;
	      }
	    अन्यथा यदि (! c_parser_require (parser, CPP_SEMICOLON,
					 "expected %<:%>"))
	      प्रत्यागम;
	    भङ्ग;
	  }
	पक्ष RID_DEFAULT:
	  {
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);
	    यदि (c_parser_अग्र_token_is (parser, CPP_COLON))
	      {
		c_parser_consume_token (parser);
		यदि (c_parser_अग्र_token_is (parser, CPP_NAME))
		  {
		    label = c_parser_peek_token (parser)->मानम्;
		    c_parser_consume_token (parser);
		    वृक्षः decl = lookup_label_for_goto (loc, label);
		    default_label = build_case_label (NULL_वृक्षः, NULL_वृक्षः,
						      decl);
		    यदि (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      प्रत्यागम;
		  }
		अन्यथा यदि (! c_parser_require (parser, CPP_NAME,
					     "expected label"))
		  प्रत्यागम;
	      }
	    अन्यथा यदि (! c_parser_require (parser, CPP_SEMICOLON,
					 "expected %<:%>"))
	      प्रत्यागम;
	    भङ्ग;
	  }
	स्वभाव:
	  c_parser_error (parser, "expected case label");
	  प्रत्यागम;
	}

    }
  यदि (! c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>"))
    प्रत्यागम;

  यदि (cond_व्यञ्जकम्.मानम् != error_mark_ग्रन्थिः)
    {
      gswitch *s = gimple_build_switch (cond_व्यञ्जकम्.मानम्, default_label, labels);
      gimple_seq_सङ्कलय_stmt_without_update (seq, s);
    }
}

/* Parse gimple return statement.  */

स्थिर शून्य
c_parser_gimple_return_stmt (gimple_parser &parser, gimple_seq *seq)
{
  location_t loc = c_parser_peek_token (parser)->location;
  gimple *ret = रिक्त;
  c_parser_consume_token (parser);
  यदि (c_parser_अग्र_token_is (parser, CPP_SEMICOLON))
    {
      c_finish_gimple_return (loc, NULL_वृक्षः);
      ret = gimple_build_return (रिक्त);
      gimple_seq_सङ्कलय_stmt_without_update (seq, ret);
    }
  अन्यथा
    {
      location_t xloc = c_parser_peek_token (parser)->location;
      c_व्यञ्जकम् व्यञ्जकम् = c_parser_gimple_unary_expression (parser);
      यदि (व्यञ्जकम्.मानम् != error_mark_ग्रन्थिः)
	{
	  c_finish_gimple_return (xloc, व्यञ्जकम्.मानम्);
	  ret = gimple_build_return (व्यञ्जकम्.मानम्);
	  gimple_seq_सङ्कलय_stmt_without_update (seq, ret);
	}
    }
}

/* Support function for c_parser_gimple_return_stmt.  */

स्थिर शून्य
c_finish_gimple_return (location_t loc, वृक्षः retval)
{
  वृक्षः valtype = वृक्षः_TYPE (वृक्षः_TYPE (current_function_decl));

  /* Use the expansion point to handle cases such as returning NULL
     in a function returning void.  */
  location_t xloc = expansion_point_location_if_अन्तर्_system_शीर्षकम् (loc);

  यदि (वृक्षः_THIS_VOLATILE (current_function_decl))
    warning_at (xloc, 0,
		"function declared %<noreturn%> has a %<return%> statement");

  यदि (! retval)
    current_function_returns_null = 1;
  अन्यथा यदि (valtype == 0 || VOID_TYPE_P (valtype))
    {
      current_function_returns_null = 1;
      यदि (वृक्षः_संहिता (वृक्षः_TYPE (retval)) != VOID_TYPE)
	{
	  error_at
	    (xloc, "%<return%> with a value, in function returning void");
	  inform (DECL_SOURCE_LOCATION (current_function_decl),
		  "declared here");
	}
    }
  अन्यथा यदि (वृक्षः_संहिता (valtype) != वृक्षः_संहिता (वृक्षः_TYPE (retval)))
    {
      error_at
	(xloc, "invalid conversion in return statement");
      inform (DECL_SOURCE_LOCATION (current_function_decl),
	      "declared here");
    }
  प्रत्यागम;
}
