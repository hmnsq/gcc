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

#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "system.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "coretypes.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "target.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "function.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "c-tree.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "timevar.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "stringpool.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "cgraph.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "attribs.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "stor-layout.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "varasm.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "trans-mem.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "c-family/c-pragma.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "c-lang.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "c-family/c-objc.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "plugin.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "builtins.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "gomp-constants.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "c-family/c-indentation.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "gimple-expr.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "context.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "gcc-rich-location.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "c-parser.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "tree-vrp.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "tree-pass.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "tree-pretty-print.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "tree.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "basic-block.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "gimple.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "gimple-pretty-print.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "tree-ssa.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "pass_manager.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "tree-ssanames.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "gimple-ssa.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "tree-dfa.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "internal-fn.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "cfg.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "cfghooks.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "bitmap.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "cfganal.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "tree-cfg.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "gimple-iterator.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "cfgloop.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "tree-phinodes.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "tree-into-ssa.h"


/* GIMPLE parser state.  */

ਵਰਗ gimple_parser
{
ਜਨਤਕ:
  gimple_parser (c_parser *p) : parser (p), ਕਿਨਾਰੇ(), current_bb(ਨਿਰਾ) {}
  /* c_parser is not visible here, use composition and fake inheritance
     via a conversion operator.  */
  ਸੰਚਾਲਕ c_parser *() { ਵਾਪਸ parser; }
  c_parser *parser;

  /* CFG build state.  */
  ਵਰਗ gimple_parser_ਕਿਨਾਰਾ
  {
  ਜਨਤਕ:
    ਪੂਰਨ src;
    ਪੂਰਨ dest;
    ਪੂਰਨ flags;
    profile_probability probability;
  };
  auto_vec<gimple_parser_ਕਿਨਾਰਾ> ਕਿਨਾਰੇ;
  basic_ਖੰਡ current_bb;

  ਖਾਲੀ ਧੱਕੋ_ਕਿਨਾਰਾ (ਪੂਰਨ, ਪੂਰਨ, ਪੂਰਨ, profile_probability);
};

ਖਾਲੀ
gimple_parser::ਧੱਕੋ_ਕਿਨਾਰਾ (ਪੂਰਨ src, ਪੂਰਨ dest, ਪੂਰਨ flags,
			  profile_probability prob)
{
  gimple_parser_ਕਿਨਾਰਾ e;
  e.src = src;
  e.dest = dest;
  e.flags = flags;
  e.probability = prob;
  ਕਿਨਾਰੇ.ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (e);
}


/* Gimple parsing functions.  */
ਸਥਿਰ ਤਾਰਕਿਕ c_parser_gimple_compound_statement (gimple_parser &, gimple_seq *);
ਸਥਿਰ ਖਾਲੀ c_parser_gimple_label (gimple_parser &, gimple_seq *);
ਸਥਿਰ ਖਾਲੀ c_parser_gimple_statement (gimple_parser &, gimple_seq *);
ਸਥਿਰ ਬਣਤਰ c_ਵਿਅੰਜਕ c_parser_gimple_ਦੁਆਧਾਰੀ_ਵਿਅੰਜਕ (gimple_parser &, ਰੁੱਖ);
ਸਥਿਰ ਬਣਤਰ c_ਵਿਅੰਜਕ c_parser_gimple_unary_ਵਿਅੰਜਕ (gimple_parser &);
ਸਥਿਰ ਬਣਤਰ c_ਵਿਅੰਜਕ c_parser_gimple_postfix_ਵਿਅੰਜਕ
			(gimple_parser &, ਰੁੱਖ = error_mark_ਗੰਢ);
ਸਥਿਰ ਬਣਤਰ c_ਵਿਅੰਜਕ c_parser_gimple_postfix_ਵਿਅੰਜਕ_after_primary
			(gimple_parser &, location_t, ਬਣਤਰ c_ਵਿਅੰਜਕ);
ਸਥਿਰ ਖਾਲੀ c_parser_gimple_declaration (gimple_parser &);
ਸਥਿਰ ਖਾਲੀ c_parser_gimple_goto_stmt (gimple_parser &, location_t,
				       ਰੁੱਖ, gimple_seq *);
ਸਥਿਰ ਖਾਲੀ c_parser_gimple_try_stmt (gimple_parser &, gimple_seq *);
ਸਥਿਰ ਖਾਲੀ c_parser_gimple_if_stmt (gimple_parser &, gimple_seq *);
ਸਥਿਰ ਖਾਲੀ c_parser_gimple_switch_stmt (gimple_parser &, gimple_seq *);
ਸਥਿਰ ਖਾਲੀ c_parser_gimple_return_stmt (gimple_parser &, gimple_seq *);
ਸਥਿਰ ਖਾਲੀ c_ਅੰਤ_gimple_return (location_t, ਰੁੱਖ);
ਸਥਿਰ ਰੁੱਖ c_parser_gimple_paren_condition (gimple_parser &);
ਸਥਿਰ ਖਾਲੀ c_parser_gimple_ਵਿਅੰਜਕ_list (gimple_parser &, vec<ਰੁੱਖ> *);


/* Much like parser_build_unary_op, but avoid applying default conversions.  */

ਸਥਿਰ c_ਵਿਅੰਜਕ
gimple_parser_build_unary_op (location_t loc,
			      ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 ਕੋਡ, ਬਣਤਰ c_ਵਿਅੰਜਕ arg)
{
  ਬਣਤਰ c_ਵਿਅੰਜਕ ਨਤੀਜਾ;

  ਨਤੀਜਾ.original_ਕੋਡ = ਕੋਡ;
  ਨਤੀਜਾ.original_type = ਨਿਰਾ;
  ਨਤੀਜਾ.m_decimal = 0;

  ਜੇ (reject_gcc_builtin (arg.ਮੁੱਲ))
    {
      ਨਤੀਜਾ.ਮੁੱਲ = error_mark_ਗੰਢ;
    }
  ਨਹੀਂਤਾਂ
    {
      ਨਤੀਜਾ.ਮੁੱਲ = build_unary_op (loc, ਕੋਡ, arg.ਮੁੱਲ, ਸੱਚ);

      ਜੇ (ਰੁੱਖ_ਉਛਾਲ_P (ਨਤੀਜਾ.ਮੁੱਲ) && !ਰੁੱਖ_ਉਛਾਲ_P (arg.ਮੁੱਲ))
	ਉਛਾਲ_warning (loc, ਨਤੀਜਾ.ਮੁੱਲ, arg.ਮੁੱਲ);
    }

  /* We are typically called when parsing a prefix token at LOC acting on
     ARG.  Reflect this by updating the source range of the result to
     start at LOC and end at the end of ARG.  */
  ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ਨਤੀਜਾ,
			   loc, arg.get_ਅੰਤ ());

  ਵਾਪਸ ਨਤੀਜਾ;
}

/* See if VAL is an identifier matching __BB<num> and return <num>
   in *INDEX.  */

ਸਥਿਰ ਤਾਰਕਿਕ
c_parser_gimple_parse_bb_spec (ਰੁੱਖ val, ਪੂਰਨ *ਸੂਚਕਾਂਕ)
{
  ਜੇ (!startswith (IDENTIFIER_ਸੂਚਕ (val), "__BB"))
    ਵਾਪਸ ਝੂਠ;

  ਅਚਲ ਅੱਖਰ *bb = IDENTIFIER_ਸੂਚਕ (val) + 4;
  ਜੇ (! ISDIGIT (*bb))
    ਵਾਪਸ ਝੂਠ;

  ਅੱਖਰ *pend;
  errno = 0;
  ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਲੰਮਾ ਸੰਖਿਆ = strtoul (bb, &pend, 10);
  ਜੇ (errno == ERANGE
      || *pend != '\0'
      || ਸੰਖਿਆ > ਵੱਧ_ਤੋਂ_ਵੱਧ_ਅੰਕ)
    ਵਾਪਸ ਝੂਠ;

  *ਸੂਚਕਾਂਕ = ਸੰਖਿਆ;
  ਵਾਪਸ ਸੱਚ;
}

/* See if VAL is an identifier matching __BB<num> and return <num>
   in *INDEX.  Return true if so and parse also FREQUENCY of
   the edge.  */


ਸਥਿਰ ਤਾਰਕਿਕ
c_parser_gimple_parse_bb_spec_ਕਿਨਾਰਾ_probability (ਰੁੱਖ val,
						gimple_parser &parser,
						ਪੂਰਨ *ਸੂਚਕਾਂਕ,
						profile_probability
						*probability)
{
  ਤਾਰਕਿਕ return_p = c_parser_gimple_parse_bb_spec (val, ਸੂਚਕਾਂਕ);
  ਜੇ (return_p)
    {
      *probability = profile_probability::uninitialized ();
      /* Parse frequency if provided.  */
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_OPEN_PAREN))
	{
	  ਰੁੱਖ f;
	  c_parser_consume_token (parser);
	  ਜੇ (!c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected frequency quality");
	      ਵਾਪਸ ਝੂਠ;
	    }

	  profile_quality quality;
	  ਅਚਲ ਅੱਖਰ *v
	    = IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ);
	  ਜੇ (!parse_profile_quality (v, &quality))
	    {
	      c_parser_error (parser, "unknown profile quality");
	      ਵਾਪਸ ਝੂਠ;
	    }

	  c_parser_consume_token (parser);
	  ਜੇ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    ਵਾਪਸ ਝੂਠ;

	  ਜੇ (!c_parser_ਅਗਲਾ_token_is (parser, CPP_ਸੰਖਿਆ)
	      || (ਰੁੱਖ_ਕੋਡ (f = c_parser_peek_token (parser)->ਮੁੱਲ)
		  != INTEGER_CST))
	    {
	      c_parser_error (parser, "expected frequency value");
	      ਵਾਪਸ ਝੂਠ;
	    }

	  ਬਿਨਾਨਿਸ਼ਾਨੀ ਪੂਰਨ ਮੁੱਲ = ਰੁੱਖ_INT_CST_ਨੀਵਾਂ (f);
	  *probability = profile_probability (ਮੁੱਲ, quality);

	  c_parser_consume_token (parser);
	  ਜੇ (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    ਵਾਪਸ ਝੂਠ;

	  ਜੇ (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    ਵਾਪਸ ਝੂਠ;
	}

      ਵਾਪਸ ਸੱਚ;
    }

  ਵਾਪਸ ਝੂਠ;

}

/* Parse the body of a function declaration marked with "__GIMPLE".  */

ਖਾਲੀ
c_parser_parse_gimple_body (c_parser *cparser, ਅੱਖਰ *gimple_pass,
			    ਗਿਣਤੀ c_declspec_il cdil,
			    profile_ਗਿਣਤੀ ਇੰਦਰਾਜ_bb_ਗਿਣਤੀ)
{
  gimple_parser parser (cparser);
  gimple_seq seq = ਨਿਰਾ;
  gimple_seq body = ਨਿਰਾ;
  ਰੁੱਖ stmt = ਧੱਕੋ_stmt_list ();
  ਧੱਕੋ_scope ();
  location_t loc1 = c_parser_peek_token (parser)->location;

  cfun->pass_startwith = gimple_pass;
  init_ਰੁੱਖ_ssa (cfun);

  ਜੇ (cdil == cdil_gimple)
    /* While we have SSA names in the IL we do not have a CFG built yet
       and PHIs are represented using a PHI internal function.  We do
       have lowered control flow and exception handling (well, we do not
       have parser support for EH yet).  But as we still have BINDs
       we have to go through lowering again.  */
    cfun->curr_properties = PROP_gimple_any;
  ਨਹੀਂਤਾਂ
    {
      /* We have at least cdil_gimple_cfg.  */
      gimple_ਰਜਿਸਟਰ_cfg_hooks ();
      init_ਖਾਲੀ_ਥਾਵਾਂ_ਰੁੱਖ_cfg ();
      parser.current_bb = ਇੰਦਰਾਜ_ਖੰਡ_PTR_FOR_FN (cfun);
      /* Initialize the bare loop structure - we are going to only
         mark headers and leave the rest to fixup.  */
      ਸੈੱਟ_loops_for_fn (cfun, ggc_cleared_alloc<ਬਣਤਰ loops> ());
      init_loops_structure (cfun, loops_for_fn (cfun), 1);
      loops_state_ਸੈੱਟ (cfun, LOOPS_NEED_FIXUP|LOOPS_MAY_HAVE_ਗੁਣਜ_LATCHES);
      cfun->curr_properties
	|= PROP_gimple_lcf | PROP_gimple_leh | PROP_cfg | PROP_loops;
      ਜੇ (cdil == cdil_gimple_ssa)
	{
	  init_ssa_operands (cfun);
	  cfun->curr_properties |= PROP_ssa;
	}
    }

  ਜੇ (! c_parser_gimple_compound_statement (parser, &seq)
      && cdil == cdil_gimple)
    {
      gimple *ret = gimple_build_return (ਨਿਰਾ);
      gimple_seq_ਜੋੜੋ_stmt_without_update (&seq, ret);
    }

  ਰੁੱਖ ਖੰਡ = ਕੱਢੋ_scope ();
  stmt = ਕੱਢੋ_stmt_list (stmt);
  stmt = c_build_bind_ਵਿਅੰਜਕ (loc1, ਖੰਡ, stmt);

  ਖੰਡ = DECL_INITIAL (current_function_decl);
  ਖੰਡ_SUBBLOCKS (ਖੰਡ) = NULL_ਰੁੱਖ;
  ਖੰਡ_CHAIN (ਖੰਡ) = NULL_ਰੁੱਖ;
  ਰੁੱਖ_ASM_WRITTEN (ਖੰਡ) = 1;

  ਜੇ (cdil == cdil_gimple)
    {
      gbind *bind_stmt = gimple_build_bind (BIND_ਵਿਅੰਜਕ_VARS (stmt), ਨਿਰਾ,
					    BIND_ਵਿਅੰਜਕ_ਖੰਡ (stmt));
      gimple_bind_ਸੈੱਟ_body (bind_stmt, seq);
      gimple_seq_ਜੋੜੋ_stmt_without_update (&body, bind_stmt);
      gimple_ਸੈੱਟ_body (current_function_decl, body);
    }
  ਨਹੀਂਤਾਂ
    {
      /* Control-flow and binds are lowered, record local decls.  */
      ਲਈ (ਰੁੱਖ var = BIND_ਵਿਅੰਜਕ_VARS (stmt); var; var = DECL_CHAIN (var))
	ਜੇ (VAR_P (var)
	    && !DECL_EXTERNAL (var))
	  {
	    ਜੋੜੋ_local_decl (cfun, var);
	    /* When the middle-end re-gimplifies any expression we might
	       run into the assertion that we've seen the decl in a BIND.  */
	    ਜੇ (!ਰੁੱਖ_STATIC (var))
	      DECL_ਵੇਖਿਆ_ਵਿੱਚ_BIND_ਵਿਅੰਜਕ_P (var) = 1;
	  }
      /* We have a CFG.  Build the edges.  */
      ਲਈ (ਬਿਨਾਨਿਸ਼ਾਨੀ i = 0; i < parser.ਕਿਨਾਰੇ.ਲੰਮਾਈ (); ++i)
	{
	  ਕਿਨਾਰਾ e = make_ਕਿਨਾਰਾ (BASIC_ਖੰਡ_FOR_FN (cfun, parser.ਕਿਨਾਰੇ[i].src),
			      BASIC_ਖੰਡ_FOR_FN (cfun, parser.ਕਿਨਾਰੇ[i].dest),
			      parser.ਕਿਨਾਰੇ[i].flags);
	  e->probability = parser.ਕਿਨਾਰੇ[i].probability;
	}
      /* Add edges for case labels.  */
      basic_ਖੰਡ bb;
      FOR_EACH_BB_FN (bb, cfun)
	ਜੇ (ਕਿਨਾਰਾ_ਗਿਣਤੀ (bb->succs) == 0)
	  {
	    ਜੇ (gswitch *sw = ਸੁਰੱਖਿਅਤ_dyn_cast <gswitch *> (*gsi_ਆਖਰੀ_bb (bb)))
	      ਲਈ (ਬਿਨਾਨਿਸ਼ਾਨੀ i = 0; i < gimple_switch_ਅੰਕ_labels (sw); ++i)
		{
		  basic_ਖੰਡ label_bb = gimple_switch_label_bb (cfun, sw, i);
		  make_ਕਿਨਾਰਾ (bb, label_bb, 0);
		}
	  }
      /* Need those for loop fixup.  */
      calculate_dominance_info (CDI_DOMINATORS);
      /* With SSA lower PHIs parsed as internal function calls and
	 update stmts.  */
      ਜੇ (cdil == cdil_gimple_ssa)
	{
	  /* Create PHI nodes, they are parsed into __PHI internal calls
	     and update SSA operands.  */
	  FOR_EACH_BB_FN (bb, cfun)
	    {
	      gimple_stmt_iterator gsi;
	      ਲਈ (gsi = gsi_ਸ਼ੁਰੂ_bb (bb); !gsi_ਸਿਰਾ_p (gsi);)
		{
		  gimple *stmt = gsi_stmt (gsi);
		  ਜੇ (!gimple_call_ਅੰਦਰੂਨੀ_p (stmt, IFN_PHI))
		    ਰੋਕੋ;

		  gphi *phi = create_phi_ਗੰਢ (gimple_call_lhs (stmt), bb);
		  ਲਈ (ਬਿਨਾਨਿਸ਼ਾਨੀ i = 0; i < gimple_call_ਅੰਕ_ਦਲੀਲਾਂ (stmt); i += 2)
		    {
		      ਪੂਰਨ srcidx = ਰੁੱਖ_INT_CST_ਨੀਵਾਂ (gimple_call_arg (stmt, i));
		      ਕਿਨਾਰਾ e = ਲੱਭੋ_ਕਿਨਾਰਾ (BASIC_ਖੰਡ_FOR_FN (cfun, srcidx), bb);
		      ਜੇ (!e)
			c_parser_error (parser, "edge not found");
		      ਨਹੀਂਤਾਂ
			ਜੋੜੋ_phi_arg (phi, gimple_call_arg (stmt, i + 1), e,
				     UNKNOWN_LOCATION);
		    }
		  gsi_remove (&gsi, ਸੱਚ);
		}
	      ਲਈ (; !gsi_ਸਿਰਾ_p (gsi); gsi_ਅਗਲਾ (&gsi))
		update_stmt (gsi_stmt (gsi));
	    }
	  /* Fill SSA name gaps, putting them on the freelist and diagnose
	     SSA names without definition.  */
	  ਲਈ (ਬਿਨਾਨਿਸ਼ਾਨੀ i = 1; i < ਅੰਕ_ssa_ਨਾਂ; ++i)
	    ਜੇ (!ssa_name (i))
	      {
		ਰੁੱਖ name = make_ssa_name_fn (cfun, integer_type_ਗੰਢ, ਨਿਰਾ, i);
		release_ssa_name_fn (cfun, name);
	      }
	    ਨਹੀਂਤਾਂ ਜੇ (!SSA_NAME_DEF_STMT (ssa_name (i)))
	      error ("SSA name %qE with version %d has no definition",
		     ssa_name (i), i);
	  /* No explicit virtual operands (yet).  */
	  bitmap_obstack_initialize (ਨਿਰਾ);
	  update_ssa (TODO_update_ssa_only_virtuals);
	  bitmap_obstack_release (ਨਿਰਾ);
	  /* ???  By flushing the freelist after virtual operand SSA rewrite
	     we keep the gaps available for re-use like needed for the
	     PR89595 testcase but then usually virtual operands would have
	     taken most of them.  The fix is obviously to make virtual
	     operands explicit in the SSA IL.  */
	  flush_ssaname_freelist ();
	}
      fix_loop_structure (ਨਿਰਾ);
    }

  ਜੇ (cfun->curr_properties & PROP_cfg)
    {
      ਇੰਦਰਾਜ_ਖੰਡ_PTR_FOR_FN (cfun)->ਗਿਣਤੀ_2 = ਇੰਦਰਾਜ_bb_ਗਿਣਤੀ;
      gcov_type t = param_gimple_fe_computed_hot_bb_ਹੱਦ;
      ਸੈੱਟ_hot_bb_ਹੱਦ (t);
      update_max_bb_ਗਿਣਤੀ ();
      cgraph_ਗੰਢ::get_create (cfun->decl);
      cgraph_ਕਿਨਾਰਾ::rebuild_ਕਿਨਾਰੇ ();
    }

  /* Perform IL validation and if any error is found abort compilation
     of this function by zapping its body.  */
  ਜੇ ((cfun->curr_properties & PROP_cfg)
      && verify_gimple_ਵਿੱਚ_cfg (cfun, ਝੂਠ, ਝੂਠ))
    init_ਖਾਲੀ_ਥਾਵਾਂ_ਰੁੱਖ_cfg ();
  ਨਹੀਂਤਾਂ ਜੇ (!(cfun->curr_properties & PROP_cfg)
	   && verify_gimple_ਵਿੱਚ_seq (gimple_body (current_function_decl), ਝੂਠ))
    gimple_ਸੈੱਟ_body (current_function_decl, ਨਿਰਾ);

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

ਸਥਿਰ ਤਾਰਕਿਕ
c_parser_gimple_compound_statement (gimple_parser &parser, gimple_seq *seq)
{
  ਤਾਰਕਿਕ return_p = ਝੂਠ;

  ਜੇ (! c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    ਵਾਪਸ ਝੂਠ;

  /* A compound statement starts with optional declarations.  */
  ਜਦੋਂ (c_parser_ਅਗਲਾ_ਟੋਕਨ_ਸ਼ੁਰੂ_declaration (parser))
    {
      c_parser_gimple_declaration (parser);
      ਜੇ (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	ਵਾਪਸ ਝੂਠ;
    }

  ਜਦੋਂ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      ਜੇ (c_parser_error (parser))
	{
	  c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_BRACE, ਨਿਰਾ);
	  ਵਾਪਸ return_p;
	}
      ਨਹੀਂਤਾਂ ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_EOF))
	{
	  c_parser_error (parser, "expected declaration or statement");
	  ਵਾਪਸ return_p;
	}

      ਚੋਣ (c_parser_peek_token (parser)->type)
	{
	ਹਾਲਤ CPP_KEYWORD:
	  ਚੋਣ (c_parser_peek_token (parser)->keyword)
	    {
	    ਹਾਲਤ RID_AT_TRY:
	      c_parser_gimple_try_stmt (parser, seq);
	      ਰੋਕੋ;
	    ਹਾਲਤ RID_IF:
	      c_parser_gimple_if_stmt (parser, seq);
	      ਰੋਕੋ;
	    ਹਾਲਤ RID_SWITCH:
	      c_parser_gimple_switch_stmt (parser, seq);
	      ਰੋਕੋ;
	    ਹਾਲਤ RID_GOTO:
	      {
		location_t loc = c_parser_peek_token (parser)->location;
		c_parser_consume_token (parser);
		ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
		  {
		    ਰੁੱਖ label = c_parser_peek_token (parser)->ਮੁੱਲ;
		    c_parser_consume_token (parser);
		    c_parser_gimple_goto_stmt (parser, loc, label, seq);
		    ਜੇ (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      ਵਾਪਸ return_p;
		  }
		}
	      ਰੋਕੋ;
	    ਹਾਲਤ RID_RETURN:
	      return_p = ਸੱਚ;
	      c_parser_gimple_return_stmt (parser, seq);
	      ਜੇ (! c_parser_require (parser, CPP_SEMICOLON,
				      "expected %<;%>"))
		ਵਾਪਸ return_p;
	      ਜੇ (cfun->curr_properties & PROP_cfg)
		parser.ਧੱਕੋ_ਕਿਨਾਰਾ (parser.current_bb->ਸੂਚਕਾਂਕ, EXIT_ਖੰਡ, 0,
				  profile_probability::uninitialized ());
	      ਰੋਕੋ;
	    ਮੂਲ:
	      ਜਾਓ ਵਿਅੰਜਕ_stmt;
	    }
	  ਰੋਕੋ;
	ਹਾਲਤ CPP_NAME:
	  ਜੇ (c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_gimple_label (parser, seq);
	      ਰੋਕੋ;
	    }
	  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME)
	      && c_parser_peek_token (parser)->id_ਕਿਸਮ == C_ID_ID
	      && strcmp (IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ),
			 "try") == 0)
	    {
	      c_parser_gimple_try_stmt (parser, seq);
	      ਰੋਕੋ;
	    }
	  /* Basic block specification.
	     __BB (index, ...)  */
	  ਜੇ ((cfun->curr_properties & PROP_cfg)
	      && !strcmp (IDENTIFIER_ਸੂਚਕ
			    (c_parser_peek_token (parser)->ਮੁੱਲ), "__BB"))
	    {
	      c_parser_consume_token (parser);
	      ਜੇ (! c_parser_require (parser, CPP_OPEN_PAREN,
				      "expected %<(%>"))
		ਵਾਪਸ return_p;
	      ਜੇ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_ਸੰਖਿਆ))
		{
		  c_parser_error (parser, "expected block index");
		  ਵਾਪਸ return_p;
		}
	      ਰੁੱਖ tnum = c_parser_peek_token (parser)->ਮੁੱਲ;
	      ਜੇ (ਰੁੱਖ_ਕੋਡ (tnum) != INTEGER_CST)
		{
		  c_parser_error (parser, "expected block index");
		  ਵਾਪਸ return_p;
		}
	      ਪੂਰਨ ਸੂਚਕਾਂਕ = ਰੁੱਖ_INT_CST_ਨੀਵਾਂ (tnum);
	      ਜੇ (ਸੂਚਕਾਂਕ < ਅੰਕ_FIXED_ਖੰਡਾਂ
		  || (ਸੂਚਕਾਂਕ < ਆਖਰੀ_basic_ਖੰਡ_for_fn (cfun)
		      && BASIC_ਖੰਡ_FOR_FN (cfun, ਸੂਚਕਾਂਕ) != ਨਿਰਾ))
		{
		  c_parser_error (parser, "invalid block index");
		  ਵਾਪਸ return_p;
		}
	      ਪੂਰਨ is_loop_ਸਿਰਲੇਖ_ਦਾ = -1;
	      profile_ਗਿਣਤੀ bb_ਗਿਣਤੀ = profile_ਗਿਣਤੀ::uninitialized ();
	      c_parser_consume_token (parser);
	      ਜਦੋਂ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  ਜੇ (! c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
		    {
		      c_parser_error (parser, "expected block specifier");
		      ਵਾਪਸ return_p;
		    }
		  /* loop_header (NUM)  */
		  ਜੇ (!strcmp (IDENTIFIER_ਸੂਚਕ
			         (c_parser_peek_token (parser)->ਮੁੱਲ),
			       "loop_header"))
		    {
		      c_parser_consume_token (parser);
		      ਜੇ (! c_parser_require (parser, CPP_OPEN_PAREN,
					      "expected %<(%>"))
			ਵਾਪਸ return_p;
		      ਰੁੱਖ loop_ਅੰਕ;
		      ਜੇ (! c_parser_ਅਗਲਾ_token_is (parser, CPP_ਸੰਖਿਆ)
			  || ਰੁੱਖ_ਕੋਡ (loop_ਅੰਕ
					  = c_parser_peek_token (parser)->ਮੁੱਲ)
			       != INTEGER_CST)
			{
			  c_parser_error (parser, "expected loop number");
			  ਵਾਪਸ return_p;
			}
		      c_parser_consume_token (parser);
		      is_loop_ਸਿਰਲੇਖ_ਦਾ = ਰੁੱਖ_INT_CST_ਨੀਵਾਂ (loop_ਅੰਕ);
		      ਜੇ (! c_parser_require (parser, CPP_CLOSE_PAREN,
					      "expected %<)%>"))
			ਵਾਪਸ return_p;
		    }
		  /* Parse profile: quality(value) */
		  ਨਹੀਂਤਾਂ
		    {
		      ਰੁੱਖ q;
		      profile_quality quality;
		      ਰੁੱਖ v = c_parser_peek_token (parser)->ਮੁੱਲ;
		      ਜੇ (!parse_profile_quality (IDENTIFIER_ਸੂਚਕ (v),
						  &quality))
			{
			  c_parser_error (parser, "unknown block specifier");
			  ਵਾਪਸ ਝੂਠ;
			}

		      c_parser_consume_token (parser);
		      ਜੇ (!c_parser_require (parser, CPP_OPEN_PAREN,
					     "expected %<(%>"))
			ਵਾਪਸ ਝੂਠ;

		      ਜੇ (!c_parser_ਅਗਲਾ_token_is (parser, CPP_ਸੰਖਿਆ)
			  || (ਰੁੱਖ_ਕੋਡ (q = c_parser_peek_token (parser)->ਮੁੱਲ)
			      != INTEGER_CST))
			{
			  c_parser_error (parser, "expected count value");
			  ਵਾਪਸ ਝੂਠ;
			}

		      bb_ਗਿਣਤੀ
			= profile_ਗਿਣਤੀ::from_gcov_type (ਰੁੱਖ_INT_CST_ਨੀਵਾਂ (q),
							 quality);
		      c_parser_consume_token (parser);
		      ਜੇ (! c_parser_require (parser, CPP_CLOSE_PAREN,
					      "expected %<)%>"))
			ਵਾਪਸ return_p;
		    }
		}
	      ਜੇ (! c_parser_require (parser, CPP_CLOSE_PAREN,
				      "expected %<)%>")
		  || ! c_parser_require (parser, CPP_COLON,
					 "expected %<:%>"))
		ਵਾਪਸ return_p;

	      /* Put stmts parsed in the current block.  */
	      ਜੇ (!gimple_seq_ਖਾਲੀ_ਥਾਵਾਂ_p (*seq))
		{
		  ਜੇ (!parser.current_bb)
		    c_parser_error (parser, "stmts without block");
		  ਨਹੀਂਤਾਂ
		    {
		      gimple_stmt_iterator gsi
			= gsi_ਸ਼ੁਰੂ_bb (parser.current_bb);
		      gsi_ਪਾਓ_seq_after_without_update (&gsi, *seq,
							   GSI_CONTINUE_LINKING);
		    }
		  *seq = ਨਿਰਾ;
		}

	      /* Build an empty block with specified index, linking them
		 in source order.  */
	      basic_ਖੰਡ bb = alloc_ਖੰਡ ();
	      bb->ਸੂਚਕਾਂਕ = ਸੂਚਕਾਂਕ;
	      link_ਖੰਡ (bb, (parser.current_bb ? parser.current_bb
			       : ਇੰਦਰਾਜ_ਖੰਡ_PTR_FOR_FN (cfun)));
	      ਜੇ (basic_ਖੰਡ_info_for_fn (cfun)->ਲੰਮਾਈ () <= (ਮਾਪ_t)ਸੂਚਕਾਂਕ)
		vec_ਸੁਰੱਖਿਅਤ_grow_cleared (basic_ਖੰਡ_info_for_fn (cfun),
				       ਸੂਚਕਾਂਕ + 1, ਸੱਚ);
	      ਸੈੱਟ_BASIC_ਖੰਡ_FOR_FN (cfun, ਸੂਚਕਾਂਕ, bb);
	      ਜੇ (ਆਖਰੀ_basic_ਖੰਡ_for_fn (cfun) <= ਸੂਚਕਾਂਕ)
		ਆਖਰੀ_basic_ਖੰਡ_for_fn (cfun) = ਸੂਚਕਾਂਕ + 1;
	      n_basic_ਖੰਡਾਂ_for_fn (cfun)++;
	      ਜੇ (parser.current_bb->ਸੂਚਕਾਂਕ == ਇੰਦਰਾਜ_ਖੰਡ)
		parser.ਧੱਕੋ_ਕਿਨਾਰਾ (ਇੰਦਰਾਜ_ਖੰਡ, bb->ਸੂਚਕਾਂਕ, ਕਿਨਾਰਾ_FALLTHRU,
				  profile_probability::always ());

	      /* We leave the proper setting to fixup.  */
	      ਵਰਗ loop *loop_father = loops_for_fn (cfun)->ਰੁੱਖ_ਜੜ੍ਹ;
	      /* If the new block is a loop header, allocate a loop
		 struct.  Fixup will take care of proper placement within
		 the loop tree.  */
	      ਜੇ (is_loop_ਸਿਰਲੇਖ_ਦਾ != -1)
		{
		  ਜੇ (ਸੰਖਿਆ_ਦਾ_loops (cfun) > (ਬਿਨਾਨਿਸ਼ਾਨੀ)is_loop_ਸਿਰਲੇਖ_ਦਾ
		      && get_loop (cfun, is_loop_ਸਿਰਲੇਖ_ਦਾ) != ਨਿਰਾ)
		    {
		      c_parser_error (parser, "duplicate loop header");
		    }
		  ਨਹੀਂਤਾਂ
		    {
		      ਵਰਗ loop *loop = alloc_loop ();
		      loop->ਅੰਕ = is_loop_ਸਿਰਲੇਖ_ਦਾ;
		      loop->ਸਿਰਲੇਖ = bb;
		      ਜੇ (ਸੰਖਿਆ_ਦਾ_loops (cfun) <= (ਬਿਨਾਨਿਸ਼ਾਨੀ)is_loop_ਸਿਰਲੇਖ_ਦਾ)
			vec_ਸੁਰੱਖਿਅਤ_grow_cleared (loops_for_fn (cfun)->larray,
					       is_loop_ਸਿਰਲੇਖ_ਦਾ + 1, ਸੱਚ);
		      (*loops_for_fn (cfun)->larray)[is_loop_ਸਿਰਲੇਖ_ਦਾ] = loop;
		      flow_loop_ਰੁੱਖ_ਗੰਢ_ਜੋੜੋ (loops_for_fn (cfun)->ਰੁੱਖ_ਜੜ੍ਹ,
					       loop);
		    }
		  loop_father = get_loop (cfun, is_loop_ਸਿਰਲੇਖ_ਦਾ);
		}
	      bb->loop_father = loop_father;
	      bb->ਗਿਣਤੀ_2 = bb_ਗਿਣਤੀ;

	      /* Stmts now go to the new block.  */
	      parser.current_bb = bb;
	      ਰੋਕੋ;
	    }
	  ਜਾਓ ਵਿਅੰਜਕ_stmt;

	ਹਾਲਤ CPP_SEMICOLON:
	  {
	    /* Empty stmt.  */
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);
	    gimple *nop = gimple_build_nop ();
	    gimple_ਸੈੱਟ_location (nop, loc);
	    gimple_seq_ਜੋੜੋ_stmt_without_update (seq, nop);
	    ਰੋਕੋ;
	  }

	ਹਾਲਤ CPP_CLOSE_PAREN:
	ਹਾਲਤ CPP_CLOSE_ਵਰਗਫਲ:
	  /* Avoid infinite loop in error recovery:
	     c_parser_skip_until_found stops at a closing nesting
	     delimiter without consuming it, but here we need to consume
	     it to proceed further.  */
	  c_parser_error (parser, "expected statement");
	  c_parser_consume_token (parser);
	ਰੋਕੋ;

	ਮੂਲ:
ਵਿਅੰਜਕ_stmt:
	  c_parser_gimple_statement (parser, seq);
	  ਜੇ (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	    c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_SEMICOLON, ਨਿਰਾ);
	}
    }
  c_parser_consume_token (parser);

  /* Put stmts parsed in the current block.  */
  ਜੇ ((cfun->curr_properties & PROP_cfg)
      && !gimple_seq_ਖਾਲੀ_ਥਾਵਾਂ_p (*seq))
    {
      ਜੇ (!parser.current_bb)
	c_parser_error (parser, "stmts without block");
      ਨਹੀਂਤਾਂ
	{
	  gimple_stmt_iterator gsi = gsi_ਸ਼ੁਰੂ_bb (parser.current_bb);
	  gsi_ਪਾਓ_seq_after_without_update (&gsi, *seq,
					       GSI_CONTINUE_LINKING);
	}
      *seq = ਨਿਰਾ;
    }

  ਵਾਪਸ return_p;
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

ਸਥਿਰ ਖਾਲੀ
c_parser_gimple_statement (gimple_parser &parser, gimple_seq *seq)
{
  ਬਣਤਰ c_ਵਿਅੰਜਕ lhs, rhs;
  gimple *ਸੌਂਪੋ = ਨਿਰਾ;
  location_t loc;
  ਰੁੱਖ arg = NULL_ਰੁੱਖ;
  auto_vec<ਰੁੱਖ> vargs;

  lhs = c_parser_gimple_unary_ਵਿਅੰਜਕ (parser);
  loc = ਵਿਅੰਜਕ_LOCATION (lhs.ਮੁੱਲ);
  rhs.ਸੈੱਟ_error ();

  /* GIMPLE call statement without LHS.  */
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_SEMICOLON)
      && ਰੁੱਖ_ਕੋਡ (lhs.ਮੁੱਲ) == CALL_ਵਿਅੰਜਕ)
    {
      gimple *call;
      call = gimple_build_call_from_ਰੁੱਖ (lhs.ਮੁੱਲ, ਨਿਰਾ);
      gimple_seq_ਜੋੜੋ_stmt_without_update (seq, call);
      gimple_ਸੈੱਟ_location (call, loc);
      ਵਾਪਸ;
    }

  /* All following cases are statements with LHS.  */
  ਜੇ (! c_parser_require (parser, CPP_EQ, "expected %<=%>"))
    ਵਾਪਸ;

  /* Eat and ignore {v} right after the =, the has_volatile_ops is
     redundant and re-computed by the operand scanner.  */
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_OPEN_BRACE)
      && !(c_parser_peek_token (parser)->flags & PREV_WHITE)
      && c_parser_peek_2nd_token (parser)->type == CPP_NAME
      && !(c_parser_peek_2nd_token (parser)->flags & PREV_WHITE)
      && strcmp ("v", IDENTIFIER_ਸੂਚਕ
			(c_parser_peek_2nd_token (parser)->ਮੁੱਲ)) == 0
      && c_parser_peek_nth_token (parser, 3)->type == CPP_CLOSE_BRACE
      && !(c_parser_peek_nth_token (parser, 3)->flags & PREV_WHITE))
    {
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }

  /* Cast expression.  */
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_typename (c_parser_peek_2nd_token (parser)))
    {
      c_parser_consume_token (parser);
      ਬਣਤਰ c_type_name *type_name = c_parser_type_name (parser);
      c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      ਜੇ (type_name == ਨਿਰਾ)
	ਵਾਪਸ;
      /* ???  The actual type used in the cast expression is ignored as
         in GIMPLE it is encoded by the type of the LHS.  */
      rhs = c_parser_gimple_postfix_ਵਿਅੰਜਕ (parser);
      ਜੇ (lhs.ਮੁੱਲ != error_mark_ਗੰਢ
	  && rhs.ਮੁੱਲ != error_mark_ਗੰਢ)
	{
	  ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 ਕੋਡ = NOP_ਵਿਅੰਜਕ;
	  ਜੇ (FLOAT_TYPE_P (ਰੁੱਖ_TYPE (lhs.ਮੁੱਲ))
	      && ! FLOAT_TYPE_P (ਰੁੱਖ_TYPE (rhs.ਮੁੱਲ)))
	    ਕੋਡ = FLOAT_ਵਿਅੰਜਕ;
	  ਨਹੀਂਤਾਂ ਜੇ (! FLOAT_TYPE_P (ਰੁੱਖ_TYPE (lhs.ਮੁੱਲ))
		   && FLOAT_TYPE_P (ਰੁੱਖ_TYPE (rhs.ਮੁੱਲ)))
	    ਕੋਡ = FIX_TRUNC_ਵਿਅੰਜਕ;
	  ਸੌਂਪੋ = gimple_build_ਸੌਂਪੋ (lhs.ਮੁੱਲ, ਕੋਡ, rhs.ਮੁੱਲ);
	  gimple_seq_ਜੋੜੋ_stmt_without_update (seq, ਸੌਂਪੋ);
	  gimple_ਸੈੱਟ_location (ਸੌਂਪੋ, loc);
	  ਵਾਪਸ;
	}
    }

  /* Unary expression.  */
  ਚੋਣ (c_parser_peek_token (parser)->type)
    {
    ਹਾਲਤ CPP_NAME:
      {
	ਰੁੱਖ id = c_parser_peek_token (parser)->ਮੁੱਲ;
	ਜੇ (strcmp (IDENTIFIER_ਸੂਚਕ (id), "__ABS") == 0
	    || strcmp (IDENTIFIER_ਸੂਚਕ (id), "__ABSU") == 0
	    || strcmp (IDENTIFIER_ਸੂਚਕ (id), "__MIN") == 0
	    || strcmp (IDENTIFIER_ਸੂਚਕ (id), "__MAX") == 0
	    || strcmp (IDENTIFIER_ਸੂਚਕ (id), "__BIT_INSERT") == 0
	    || strcmp (IDENTIFIER_ਸੂਚਕ (id), "__VEC_PERM") == 0)
	  ਜਾਓ build_unary_ਵਿਅੰਜਕ;
	ਰੋਕੋ;
      }
    ਹਾਲਤ CPP_KEYWORD:
      ਜੇ (c_parser_peek_token (parser)->keyword != RID_REALPART
	  && c_parser_peek_token (parser)->keyword != RID_IMAGPART)
	ਰੋਕੋ;
      /* Fallthru.  */
    ਹਾਲਤ CPP_AND:
    ਹਾਲਤ CPP_PLUS:
    ਹਾਲਤ CPP_MINUS:
    ਹਾਲਤ CPP_COMPL:
    ਹਾਲਤ CPP_NOT:
    ਹਾਲਤ CPP_MULT: /* pointer deref */
    build_unary_ਵਿਅੰਜਕ:
      rhs = c_parser_gimple_unary_ਵਿਅੰਜਕ (parser);
      ਜੇ (rhs.ਮੁੱਲ != error_mark_ਗੰਢ)
	{
	  ਸੌਂਪੋ = gimple_build_ਸੌਂਪੋ (lhs.ਮੁੱਲ, rhs.ਮੁੱਲ);
	  gimple_ਸੈੱਟ_location (ਸੌਂਪੋ, loc);
	  gimple_seq_ਜੋੜੋ_stmt_without_update (seq, ਸੌਂਪੋ);
	}
      ਵਾਪਸ;

    ਮੂਲ:;
    }

  /* GIMPLE PHI statement.  */
  ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_PHI))
    {
      c_parser_consume_token (parser);

      ਜੇ (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	ਵਾਪਸ;

      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_OPEN_PAREN))
	c_parser_consume_token (parser);

      ਜਦੋਂ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_CLOSE_PAREN))
	{
	  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      arg = c_parser_peek_token (parser)->ਮੁੱਲ;
	      c_parser_consume_token (parser);
	      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COLON))
		c_parser_consume_token (parser);
	      ਪੂਰਨ src_ਸੂਚਕਾਂਕ = -1;
	      ਜੇ (!c_parser_gimple_parse_bb_spec (arg, &src_ਸੂਚਕਾਂਕ))
		c_parser_error (parser, "invalid source block specification");
	      vargs.ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (ਮਾਪ_int (src_ਸੂਚਕਾਂਕ));
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  ਨਹੀਂਤਾਂ
	    {
	      arg = c_parser_gimple_unary_ਵਿਅੰਜਕ (parser).ਮੁੱਲ;
	      vargs.ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (arg);
	    }
	}

      c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");

      /* Build internal function for PHI.  */
      gcall *call_stmt = gimple_build_call_ਅੰਦਰੂਨੀ_vec (IFN_PHI, vargs);
      gimple_call_ਸੈੱਟ_lhs (call_stmt, lhs.ਮੁੱਲ);
      gimple_ਸੈੱਟ_location (call_stmt, UNKNOWN_LOCATION);
      gimple_seq_ਜੋੜੋ_stmt_without_update (seq, call_stmt);
      ਵਾਪਸ;
    }

  /* GIMPLE call with lhs.  */
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_DOT)
      || (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN
	  && lookup_name (c_parser_peek_token (parser)->ਮੁੱਲ)))
    {
      rhs = c_parser_gimple_unary_ਵਿਅੰਜਕ (parser);
      ਜੇ (rhs.ਮੁੱਲ != error_mark_ਗੰਢ)
	{
	  gimple *call = gimple_build_call_from_ਰੁੱਖ (rhs.ਮੁੱਲ, ਨਿਰਾ);
	  gimple_call_ਸੈੱਟ_lhs (call, lhs.ਮੁੱਲ);
	  gimple_seq_ਜੋੜੋ_stmt_without_update (seq, call);
	  gimple_ਸੈੱਟ_location (call, loc);
	}
      ਵਾਪਸ;
    }

  rhs = c_parser_gimple_ਦੁਆਧਾਰੀ_ਵਿਅੰਜਕ (parser, ਰੁੱਖ_TYPE (lhs.ਮੁੱਲ));
  ਜੇ (lhs.ਮੁੱਲ != error_mark_ਗੰਢ
      && rhs.ਮੁੱਲ != error_mark_ਗੰਢ)
    {
      /* If we parsed an identifier and the next token  is a '?' then parse
	 a conditional expression.  */
      ਜੇ (SSA_VAR_P (rhs.ਮੁੱਲ) && c_parser_ਅਗਲਾ_token_is (parser, CPP_QUERY))
	{
	  ਬਣਤਰ c_ਵਿਅੰਜਕ trueval, falseval;
	  c_parser_consume_token (parser);
	  trueval = c_parser_gimple_postfix_ਵਿਅੰਜਕ (parser);
	  falseval.ਸੈੱਟ_error ();
	  ਜੇ (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    falseval = c_parser_gimple_postfix_ਵਿਅੰਜਕ (parser);
	  ਜੇ (trueval.ਮੁੱਲ == error_mark_ਗੰਢ
	      || falseval.ਮੁੱਲ == error_mark_ਗੰਢ)
	    ਵਾਪਸ;
	  rhs.ਮੁੱਲ = build3_loc (loc,
				  ਸਦਿਸ਼_TYPE_P (ਰੁੱਖ_TYPE (rhs.ਮੁੱਲ))
				  ? VEC_COND_ਵਿਅੰਜਕ : COND_ਵਿਅੰਜਕ,
				  ਰੁੱਖ_TYPE (trueval.ਮੁੱਲ),
				  rhs.ਮੁੱਲ, trueval.ਮੁੱਲ, falseval.ਮੁੱਲ);
	}
      ਜੇ (get_gimple_rhs_class (ਰੁੱਖ_ਕੋਡ (rhs.ਮੁੱਲ)) == GIMPLE_INVALID_RHS)
	{
	  c_parser_error (parser, "unexpected RHS for assignment");
	  ਵਾਪਸ;
	}
      ਸੌਂਪੋ = gimple_build_ਸੌਂਪੋ (lhs.ਮੁੱਲ, rhs.ਮੁੱਲ);
      gimple_seq_ਜੋੜੋ_stmt_without_update (seq, ਸੌਂਪੋ);
      gimple_ਸੈੱਟ_location (ਸੌਂਪੋ, loc);
    }
  ਵਾਪਸ;
}

/* A mapping between an identifier to a tree code for binary operations. */
ਸਥਿਰ ਅਚਲ std::pair<ਅਚਲ ਅੱਖਰ *, ਰੁੱਖ_ਕੋਡ_2> gimple_ਦੁਆਧਾਰੀ_identifier_ਕੋਡ[] =
  {
    {"__MULT_HIGHPART", MULT_HIGHPART_ਵਿਅੰਜਕ},
    {"__UNLT", UNLT_ਵਿਅੰਜਕ},
    {"__UNLE", UNLE_ਵਿਅੰਜਕ},
    {"__UNGT", UNGT_ਵਿਅੰਜਕ},
    {"__UNGE", UNGE_ਵਿਅੰਜਕ},
    {"__UNEQ", UNEQ_ਵਿਅੰਜਕ},
    {"__UNORDERED", UNORDERED_ਵਿਅੰਜਕ},
    {"__ORDERED", ORDERED_ਵਿਅੰਜਕ},
    {"__LTGT", LTGT_ਵਿਅੰਜਕ},
    {"__FLOOR_DIV", FLOOR_DIV_ਵਿਅੰਜਕ},
    {"__ROUND_DIV", ਗੇੜਾ_DIV_ਵਿਅੰਜਕ},
    {"__EXACT_DIV", EXACT_DIV_ਵਿਅੰਜਕ},
    {"__CEIL_DIV", CEIL_DIV_ਵਿਅੰਜਕ},
    {"__FLOOR_MOD", FLOOR_MOD_ਵਿਅੰਜਕ},
    {"__ROUND_MOD", ਗੇੜਾ_MOD_ਵਿਅੰਜਕ},
    {"__CEIL_MOD", CEIL_MOD_ਵਿਅੰਜਕ},
    {"__ROTATE_LEFT", LROTATE_ਵਿਅੰਜਕ},
    {"__ROTATE_RIGHT", RROTATE_ਵਿਅੰਜਕ},
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

ਸਥਿਰ c_ਵਿਅੰਜਕ
c_parser_gimple_ਦੁਆਧਾਰੀ_ਵਿਅੰਜਕ (gimple_parser &parser, ਰੁੱਖ ret_type)
{
  /* Location of the binary operator.  */
  ਬਣਤਰ c_ਵਿਅੰਜਕ ret, lhs, rhs;
  ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 ਕੋਡ = ERROR_MARK;
  ret.ਸੈੱਟ_error ();
  lhs = c_parser_gimple_postfix_ਵਿਅੰਜਕ (parser, ret_type);
  ਜੇ (c_parser_error (parser))
    ਵਾਪਸ ret;
  ਚੋਣ (c_parser_peek_token (parser)->type)
    {
    ਹਾਲਤ CPP_MULT:
      ਕੋਡ = MULT_ਵਿਅੰਜਕ;
      ਰੋਕੋ;
    ਹਾਲਤ CPP_DIV:
      ਕੋਡ = TRUNC_DIV_ਵਿਅੰਜਕ;
      ਰੋਕੋ;
    ਹਾਲਤ CPP_MOD:
      ਕੋਡ = TRUNC_MOD_ਵਿਅੰਜਕ;
      ਰੋਕੋ;
    ਹਾਲਤ CPP_PLUS:
      ਜੇ (ਸੂਚਕ_TYPE_P (ਰੁੱਖ_TYPE (lhs.ਮੁੱਲ)))
	ਕੋਡ = ਸੂਚਕ_PLUS_ਵਿਅੰਜਕ;
      ਨਹੀਂਤਾਂ
	ਕੋਡ = PLUS_ਵਿਅੰਜਕ;
      ਰੋਕੋ;
    ਹਾਲਤ CPP_MINUS:
      ਜੇ (ਸੂਚਕ_TYPE_P (ਰੁੱਖ_TYPE (lhs.ਮੁੱਲ)))
	ਕੋਡ = ਸੂਚਕ_DIFF_ਵਿਅੰਜਕ;
      ਨਹੀਂਤਾਂ
	ਕੋਡ = MINUS_ਵਿਅੰਜਕ;
      ਰੋਕੋ;
    ਹਾਲਤ CPP_LSHIFT:
      ਕੋਡ = LSHIFT_ਵਿਅੰਜਕ;
      ਰੋਕੋ;
    ਹਾਲਤ CPP_RSHIFT:
      ਕੋਡ = RSHIFT_ਵਿਅੰਜਕ;
      ਰੋਕੋ;
    ਹਾਲਤ CPP_LESS:
      ਕੋਡ = LT_ਵਿਅੰਜਕ;
      ਰੋਕੋ;
    ਹਾਲਤ CPP_GREATER:
      ਕੋਡ = GT_ਵਿਅੰਜਕ;
      ਰੋਕੋ;
    ਹਾਲਤ CPP_LESS_EQ:
      ਕੋਡ = LE_ਵਿਅੰਜਕ;
      ਰੋਕੋ;
    ਹਾਲਤ CPP_GREATER_EQ:
      ਕੋਡ = GE_ਵਿਅੰਜਕ;
      ਰੋਕੋ;
    ਹਾਲਤ CPP_EQ_EQ:
      ਕੋਡ = EQ_ਵਿਅੰਜਕ;
      ਰੋਕੋ;
    ਹਾਲਤ CPP_NOT_EQ:
      ਕੋਡ = NE_ਵਿਅੰਜਕ;
      ਰੋਕੋ;
    ਹਾਲਤ CPP_AND:
      ਕੋਡ = ਦੋਆਧਾਰੀ_ਅੰਕ_AND_ਵਿਅੰਜਕ;
      ਰੋਕੋ;
    ਹਾਲਤ CPP_XOR:
      ਕੋਡ = ਦੋਆਧਾਰੀ_ਅੰਕ_XOR_ਵਿਅੰਜਕ;
      ਰੋਕੋ;
    ਹਾਲਤ CPP_OR:
      ਕੋਡ = ਦੋਆਧਾਰੀ_ਅੰਕ_IOR_ਵਿਅੰਜਕ;
      ਰੋਕੋ;
    ਹਾਲਤ CPP_AND_AND:
      c_parser_error (parser, "%<&&%> not valid in GIMPLE");
      ਵਾਪਸ ret;
    ਹਾਲਤ CPP_OR_OR:
      c_parser_error (parser, "%<||%> not valid in GIMPLE");
      ਵਾਪਸ ret;
    ਹਾਲਤ CPP_NAME:
      {
	ਰੁੱਖ id = c_parser_peek_token (parser)->ਮੁੱਲ;
	ਲਈ (ਸਵੈਚਾਲਿਤ &p : gimple_ਦੁਆਧਾਰੀ_identifier_ਕੋਡ)
	  {
	    ਜੇ (strcmp (IDENTIFIER_ਸੂਚਕ (id), p.ਪਹਿਲਾ) == 0)
	      {
		ਕੋਡ = p.ਦੂਜਾ;
		ਰੋਕੋ;
	      }
	  }
	ਜੇ (ਕੋਡ != ERROR_MARK)
	  ਰੋਕੋ;
      }
      /* Fallthru.  */
    ਮੂਲ:
      /* Not a binary expression.  */
      ਵਾਪਸ lhs;
    }
  location_t ret_loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  rhs = c_parser_gimple_postfix_ਵਿਅੰਜਕ (parser);
  ਜੇ (lhs.ਮੁੱਲ != error_mark_ਗੰਢ && rhs.ਮੁੱਲ != error_mark_ਗੰਢ)
    ret.ਮੁੱਲ = build2_loc (ret_loc, ਕੋਡ, ret_type, lhs.ਮੁੱਲ, rhs.ਮੁੱਲ);
  ਵਾਪਸ ret;
}

/* Parse a gimple parentized binary expression.  */

ਸਥਿਰ c_ਵਿਅੰਜਕ
c_parser_gimple_parentized_ਦੁਆਧਾਰੀ_ਵਿਅੰਜਕ (gimple_parser &parser,
					      location_t op_loc,
					      ਰੁੱਖ_ਕੋਡ_2 ਕੋਡ)
{
  ਬਣਤਰ c_ਵਿਅੰਜਕ ret;
  ret.ਸੈੱਟ_error ();

  c_parser_consume_token (parser);
  ਜੇ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    ਵਾਪਸ ret;
  c_ਵਿਅੰਜਕ op1 = c_parser_gimple_postfix_ਵਿਅੰਜਕ (parser);
  ਜੇ (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    ਵਾਪਸ ret;
  c_ਵਿਅੰਜਕ op2 = c_parser_gimple_postfix_ਵਿਅੰਜਕ (parser);
  ਜੇ (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    ਵਾਪਸ ret;

  ਜੇ (op1.ਮੁੱਲ != error_mark_ਗੰਢ && op2.ਮੁੱਲ != error_mark_ਗੰਢ)
    ret.ਮੁੱਲ = build2_loc (op_loc,
			    ਕੋਡ, ਰੁੱਖ_TYPE (op1.ਮੁੱਲ), op1.ਮੁੱਲ, op2.ਮੁੱਲ);
  ਵਾਪਸ ret;
}

/* Parse a gimple parentized binary expression.  */

ਸਥਿਰ c_ਵਿਅੰਜਕ
c_parser_gimple_parentized_ternary_ਵਿਅੰਜਕ (gimple_parser &parser,
					       location_t op_loc,
					       ਰੁੱਖ_ਕੋਡ_2 ਕੋਡ)
{
  ਬਣਤਰ c_ਵਿਅੰਜਕ ret;
  ret.ਸੈੱਟ_error ();

  c_parser_consume_token (parser);
  ਜੇ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    ਵਾਪਸ ret;
  c_ਵਿਅੰਜਕ op1 = c_parser_gimple_postfix_ਵਿਅੰਜਕ (parser);
  ਜੇ (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    ਵਾਪਸ ret;
  c_ਵਿਅੰਜਕ op2 = c_parser_gimple_postfix_ਵਿਅੰਜਕ (parser);
  ਜੇ (!c_parser_require (parser, CPP_COMMA, "expected %<)%>"))
    ਵਾਪਸ ret;
  c_ਵਿਅੰਜਕ op3 = c_parser_gimple_postfix_ਵਿਅੰਜਕ (parser);
  ਜੇ (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    ਵਾਪਸ ret;

  ਜੇ (op1.ਮੁੱਲ != error_mark_ਗੰਢ
      && op2.ਮੁੱਲ != error_mark_ਗੰਢ
      && op3.ਮੁੱਲ != error_mark_ਗੰਢ)
    ret.ਮੁੱਲ = build3_loc (op_loc,
			    ਕੋਡ, ਰੁੱਖ_TYPE (op1.ਮੁੱਲ),
			    op1.ਮੁੱਲ, op2.ਮੁੱਲ, op3.ਮੁੱਲ);
  ਵਾਪਸ ret;
}

/* Parse gimple unary expression.

   gimple-unary-expression:
     gimple-postfix-expression
     unary-operator gimple-postfix-expression

   unary-operator: one of
     & * + - ~ abs_expr
*/

ਸਥਿਰ c_ਵਿਅੰਜਕ
c_parser_gimple_unary_ਵਿਅੰਜਕ (gimple_parser &parser)
{
  ਬਣਤਰ c_ਵਿਅੰਜਕ ret, op;
  location_t op_loc = c_parser_peek_token (parser)->location;
  location_t ਅੰਤ;
  ret.ਸੈੱਟ_error ();
  ਚੋਣ (c_parser_peek_token (parser)->type)
    {
    ਹਾਲਤ CPP_AND:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_ਵਿਅੰਜਕ (parser);
      mark_exp_read (op.ਮੁੱਲ);
      ਵਾਪਸ gimple_parser_build_unary_op (op_loc, ADDR_ਵਿਅੰਜਕ, op);
    ਹਾਲਤ CPP_MULT:
      {
	c_parser_consume_token (parser);
	op = c_parser_gimple_postfix_ਵਿਅੰਜਕ (parser);
	ਜੇ (op.ਮੁੱਲ == error_mark_ਗੰਢ)
	  ਵਾਪਸ ret;
	ਜੇ (! ਸੂਚਕ_TYPE_P (ਰੁੱਖ_TYPE (op.ਮੁੱਲ)))
	  {
	    error_at (op_loc, "expected pointer as argument of unary %<*%>");
	    ਵਾਪਸ ret;
	  }
	ਅੰਤ = op.get_ਅੰਤ ();
	location_t combined_loc = make_location (op_loc, op_loc, ਅੰਤ);
	ret.ਮੁੱਲ = build_simple_mem_ref_loc (combined_loc, op.ਮੁੱਲ);
	ਰੁੱਖ_SIDE_EFFECTS (ret.ਮੁੱਲ)
	  = ਰੁੱਖ_THIS_VOLATILE (ret.ਮੁੱਲ)
	  = TYPE_VOLATILE (ਰੁੱਖ_TYPE (ਰੁੱਖ_TYPE (op.ਮੁੱਲ)));
	ret.src_range.m_ਸ਼ੁਰੂ = op_loc;
	ret.src_range.m_ਅੰਤ = ਅੰਤ;
	ਵਾਪਸ ret;
      }
    ਹਾਲਤ CPP_PLUS:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_ਵਿਅੰਜਕ (parser);
      ਵਾਪਸ gimple_parser_build_unary_op (op_loc, CONVERT_ਵਿਅੰਜਕ, op);
    ਹਾਲਤ CPP_MINUS:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_ਵਿਅੰਜਕ (parser);
      ਵਾਪਸ gimple_parser_build_unary_op (op_loc, NEGATE_ਵਿਅੰਜਕ, op);
    ਹਾਲਤ CPP_COMPL:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_ਵਿਅੰਜਕ (parser);
      ਵਾਪਸ gimple_parser_build_unary_op (op_loc, ਦੋਆਧਾਰੀ_ਅੰਕ_NOT_ਵਿਅੰਜਕ, op);
    ਹਾਲਤ CPP_NOT:
      c_parser_error (parser, "%<!%> not valid in GIMPLE");
      ਵਾਪਸ ret;
    ਹਾਲਤ CPP_KEYWORD:
      ਚੋਣ (c_parser_peek_token (parser)->keyword)
	{
	ਹਾਲਤ RID_REALPART:
	  c_parser_consume_token (parser);
	  op = c_parser_gimple_postfix_ਵਿਅੰਜਕ (parser);
	  ਵਾਪਸ gimple_parser_build_unary_op (op_loc, REALPART_ਵਿਅੰਜਕ, op);
	ਹਾਲਤ RID_IMAGPART:
	  c_parser_consume_token (parser);
	  op = c_parser_gimple_postfix_ਵਿਅੰਜਕ (parser);
	  ਵਾਪਸ gimple_parser_build_unary_op (op_loc, IMAGPART_ਵਿਅੰਜਕ, op);
	ਮੂਲ:
	  ਵਾਪਸ c_parser_gimple_postfix_ਵਿਅੰਜਕ (parser);
	}
    ਹਾਲਤ CPP_NAME:
	{
	  ਰੁੱਖ id = c_parser_peek_token (parser)->ਮੁੱਲ;
	  ਜੇ (strcmp (IDENTIFIER_ਸੂਚਕ (id), "__ABS") == 0)
	    {
	      c_parser_consume_token (parser);
	      op = c_parser_gimple_postfix_ਵਿਅੰਜਕ (parser);
	      ਵਾਪਸ gimple_parser_build_unary_op (op_loc, ABS_ਵਿਅੰਜਕ, op);
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (strcmp (IDENTIFIER_ਸੂਚਕ (id), "__ABSU") == 0)
	    {
	      c_parser_consume_token (parser);
	      op = c_parser_gimple_postfix_ਵਿਅੰਜਕ (parser);
	      ਵਾਪਸ gimple_parser_build_unary_op (op_loc, ABSU_ਵਿਅੰਜਕ, op);
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (strcmp (IDENTIFIER_ਸੂਚਕ (id), "__MIN") == 0)
	    ਵਾਪਸ c_parser_gimple_parentized_ਦੁਆਧਾਰੀ_ਵਿਅੰਜਕ (parser,
								 op_loc,
								 MIN_ਵਿਅੰਜਕ);
	  ਨਹੀਂਤਾਂ ਜੇ (strcmp (IDENTIFIER_ਸੂਚਕ (id), "__MAX") == 0)
	    ਵਾਪਸ c_parser_gimple_parentized_ਦੁਆਧਾਰੀ_ਵਿਅੰਜਕ (parser,
								 op_loc,
								 MAX_ਵਿਅੰਜਕ);
	  ਨਹੀਂਤਾਂ ਜੇ (strcmp (IDENTIFIER_ਸੂਚਕ (id), "__VEC_PERM") == 0)
	    ਵਾਪਸ c_parser_gimple_parentized_ternary_ਵਿਅੰਜਕ
			(parser, op_loc, VEC_PERM_ਵਿਅੰਜਕ);
	  ਨਹੀਂਤਾਂ ਜੇ (strcmp (IDENTIFIER_ਸੂਚਕ (id), "__BIT_INSERT") == 0)
	    {
	      /* __BIT_INSERT '(' postfix-expression, postfix-expression,
			          integer ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      ਜੇ (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_ਵਿਅੰਜਕ op0 = c_parser_gimple_postfix_ਵਿਅੰਜਕ (parser);
		  c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_ਵਿਅੰਜਕ op1 = c_parser_gimple_postfix_ਵਿਅੰਜਕ (parser);
		  c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_ਵਿਅੰਜਕ op2 = c_parser_gimple_postfix_ਵਿਅੰਜਕ (parser);
		  ਜੇ (ਰੁੱਖ_ਕੋਡ (op2.ਮੁੱਲ) != INTEGER_CST
		      || !int_ਸਮਾਉਂਦਾ_type_p (op2.ਮੁੱਲ, bitsizetype))
		    c_parser_error (parser, "expected constant offset");
		  c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  ਜੇ (op0.ਮੁੱਲ != error_mark_ਗੰਢ
		      && op1.ਮੁੱਲ != error_mark_ਗੰਢ
		      && ਰੁੱਖ_ਕੋਡ (op2.ਮੁੱਲ) == INTEGER_CST)
		    ret.ਮੁੱਲ = build3_loc (loc, ਦੋਆਧਾਰੀ_ਅੰਕ_ਪਾਓ_ਵਿਅੰਜਕ,
					    ਰੁੱਖ_TYPE (op0.ਮੁੱਲ),
					    op0.ਮੁੱਲ, op1.ਮੁੱਲ,
					    fold_convert (bitsizetype,
							  op2.ਮੁੱਲ));
		}
	      ਵਾਪਸ ret;
	    }
	  ਨਹੀਂਤਾਂ
	    ਵਾਪਸ c_parser_gimple_postfix_ਵਿਅੰਜਕ (parser);
	}
    ਮੂਲ:
      ਵਾਪਸ c_parser_gimple_postfix_ਵਿਅੰਜਕ (parser);
    }
}

/* Decompose ID into base name (ID until ver_offset) and VERSION.  Return
   true if ID matches a SSA name.  */

ਸਥਿਰ ਤਾਰਕਿਕ
c_parser_parse_ssa_name_id (ਰੁੱਖ id, ਬਿਨਾਨਿਸ਼ਾਨੀ *ਸੰਸਕਰਣ, ਬਿਨਾਨਿਸ਼ਾਨੀ *ver_ਵਿੱਥ)
{
  ਅਚਲ ਅੱਖਰ *token = IDENTIFIER_ਸੂਚਕ (id);
  ਅਚਲ ਅੱਖਰ *var_ਸੰਸਕਰਣ = strrchr (token, '_');
  ਜੇ (! var_ਸੰਸਕਰਣ)
    ਵਾਪਸ ਝੂਠ;

  *ver_ਵਿੱਥ = var_ਸੰਸਕਰਣ - token;
  ਲਈ (ਅਚਲ ਅੱਖਰ *p = var_ਸੰਸਕਰਣ + 1; *p; ++p)
    ਜੇ (! ISDIGIT (*p))
      ਵਾਪਸ ਝੂਠ;
  *ਸੰਸਕਰਣ = atoi (var_ਸੰਸਕਰਣ + 1);
  ਵਾਪਸ *ਸੰਸਕਰਣ > 0;
}

/* Get at the actual SSA name ID with VERSION starting at VER_OFFSET.
   TYPE is the type if the SSA name is being declared.  */

ਸਥਿਰ ਰੁੱਖ
c_parser_parse_ssa_name (gimple_parser &parser,
			 ਰੁੱਖ id, ਰੁੱਖ type, ਬਿਨਾਨਿਸ਼ਾਨੀ ਸੰਸਕਰਣ,
			 ਬਿਨਾਨਿਸ਼ਾਨੀ ver_ਵਿੱਥ)
{
  ਰੁੱਖ name = NULL_ਰੁੱਖ;
  ਅਚਲ ਅੱਖਰ *token = IDENTIFIER_ਸੂਚਕ (id);

  ਜੇ (ver_ਵਿੱਥ == 0)
    {
      /* Anonymous unnamed SSA name.  */
      ਜੇ (ਸੰਸਕਰਣ < ਅੰਕ_ssa_ਨਾਂ)
	name = ssa_name (ਸੰਸਕਰਣ);
      ਜੇ (! name)
	{
	  ਜੇ (! type)
	    {
	      c_parser_error (parser, "SSA name undeclared");
	      ਵਾਪਸ error_mark_ਗੰਢ;
	    }
	  name = make_ssa_name_fn (cfun, type, ਨਿਰਾ, ਸੰਸਕਰਣ);
	}
    }
  ਨਹੀਂਤਾਂ
    {
      ਜੇ (ਸੰਸਕਰਣ < ਅੰਕ_ssa_ਨਾਂ)
	name = ssa_name (ਸੰਸਕਰਣ);
      ਜੇ (! name)
	{
	  /* Separate var name from version.  */
	  ਅੱਖਰ *var_name = XNEWVEC (ਅੱਖਰ, ver_ਵਿੱਥ + 1);
	  ਸਮ੍ਰਿਤੀ_ਨਕਲ (var_name, token, ver_ਵਿੱਥ);
	  var_name[ver_ਵਿੱਥ] = '\0';
	  /* lookup for parent decl.  */
	  id = get_identifier (var_name);
	  ਰੁੱਖ ਮਾਪਾ = lookup_name (id);
	  XDELETEVEC (var_name);
	  ਜੇ (! ਮਾਪਾ || ਮਾਪਾ == error_mark_ਗੰਢ)
	    {
	      c_parser_error (parser, "base variable or SSA name undeclared");
	      ਵਾਪਸ error_mark_ਗੰਢ;
	    }
	  ਜੇ (!(VAR_P (ਮਾਪਾ)
		|| ਰੁੱਖ_ਕੋਡ (ਮਾਪਾ) == PARM_DECL
		|| ਰੁੱਖ_ਕੋਡ (ਮਾਪਾ) == ਨਤੀਜਾ_DECL))
	    {
	      error ("invalid base %qE for SSA name", ਮਾਪਾ);
	      ਵਾਪਸ error_mark_ਗੰਢ;
	    }
	  name = make_ssa_name_fn (cfun, ਮਾਪਾ,
				   gimple_build_nop (), ਸੰਸਕਰਣ);
	}
    }

  ਵਾਪਸ name;
}

/* Parse a gimple call to an internal function.

   gimple-call-internal:
     . identifier ( gimple-argument-expression-list[opt] )  */

ਸਥਿਰ ਬਣਤਰ c_ਵਿਅੰਜਕ
c_parser_gimple_call_ਅੰਦਰੂਨੀ (gimple_parser &parser)
{
  ਬਣਤਰ c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ;
  ਵਿਅੰਜਕ.ਸੈੱਟ_error ();

  gcc_assert (c_parser_ਅਗਲਾ_token_is (parser, CPP_DOT));
  c_parser_consume_token (parser);
  location_t loc = c_parser_peek_token (parser)->location;
  ਜੇ (!c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_ਕਿਸਮ != C_ID_ID)
    {
      c_parser_error (parser, "expecting internal function name");
      ਵਾਪਸ ਵਿਅੰਜਕ;
    }
  ਰੁੱਖ id = c_parser_peek_token (parser)->ਮੁੱਲ;
  ਅੰਦਰੂਨੀ_fn ifn = lookup_ਅੰਦਰੂਨੀ_fn (IDENTIFIER_ਸੂਚਕ (id));
  c_parser_consume_token (parser);
  ਜੇ (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    {
      auto_vec<ਰੁੱਖ> exprlist;
      ਜੇ (!c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_gimple_ਵਿਅੰਜਕ_list (parser, &exprlist);
      c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      ਜੇ (ifn == IFN_ਆਖਰੀ)
	error_at (loc, "unknown internal function %qE", id);
      ਨਹੀਂਤਾਂ
	{
	  ਵਿਅੰਜਕ.ਮੁੱਲ = build_call_ਵਿਅੰਜਕ_ਅੰਦਰੂਨੀ_loc_array
	    (loc, ifn, void_type_ਗੰਢ, exprlist.ਲੰਮਾਈ (),
	     exprlist.ਪਤਾ ());
	  ਵਿਅੰਜਕ.original_ਕੋਡ = ERROR_MARK;
	  ਵਿਅੰਜਕ.original_type = ਨਿਰਾ;
	  ਵਿਅੰਜਕ.m_decimal = 0;
	}
    }
  ਵਾਪਸ ਵਿਅੰਜਕ;
}

/* Parse '<' type [',' alignment] '>' and return a type on success
   and NULL_TREE on error.  */

ਸਥਿਰ ਰੁੱਖ
c_parser_gimple_typespec (gimple_parser &parser)
{
  ਬਣਤਰ c_type_name *type_name = ਨਿਰਾ;
  ਰੁੱਖ alignment = NULL_ਰੁੱਖ;
  ਜੇ (c_parser_require (parser, CPP_LESS, "expected %<<%>"))
    {
      type_name = c_parser_type_name (parser);
      /* Optional alignment.  */
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA))
	{
	  c_parser_consume_token (parser);
	  alignment
	      = c_parser_gimple_postfix_ਵਿਅੰਜਕ (parser).ਮੁੱਲ;
	}
      c_parser_skip_until_ਮਿਲਿਆ (parser,
				 CPP_GREATER, "expected %<>%>");
    }
  ਜੇ (!type_name)
    ਵਾਪਸ NULL_ਰੁੱਖ;
  ਰੁੱਖ tem;
  ਰੁੱਖ type = groktypename (type_name, &tem, ਨਿਰਾ);
  ਜੇ (alignment)
    type = build_aligned_type (type, ਰੁੱਖ_ਮੰਜ਼ਿਲ_uhwi (alignment));
  ਵਾਪਸ type;
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

ਸਥਿਰ ਬਣਤਰ c_ਵਿਅੰਜਕ
c_parser_gimple_postfix_ਵਿਅੰਜਕ (gimple_parser &parser, ਰੁੱਖ ret_type)
{
  location_t loc = c_parser_peek_token (parser)->location;
  ਸਰੋਤ_range tok_range = c_parser_peek_token (parser)->get_range ();
  ਬਣਤਰ c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ;
  ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
  ਚੋਣ (c_parser_peek_token (parser)->type)
    {
    ਹਾਲਤ CPP_ਸੰਖਿਆ:
      ਵਿਅੰਜਕ.ਮੁੱਲ = c_parser_peek_token (parser)->ਮੁੱਲ;
      ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ਵਿਅੰਜਕ, tok_range);
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      ਰੋਕੋ;
    ਹਾਲਤ CPP_CHAR:
    ਹਾਲਤ CPP_CHAR16:
    ਹਾਲਤ CPP_CHAR32:
    ਹਾਲਤ CPP_UTF8CHAR:
    ਹਾਲਤ CPP_WCHAR:
      ਵਿਅੰਜਕ.ਮੁੱਲ = c_parser_peek_token (parser)->ਮੁੱਲ;
      ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ਵਿਅੰਜਕ, tok_range);
      c_parser_consume_token (parser);
      ਰੋਕੋ;
    ਹਾਲਤ CPP_STRING:
    ਹਾਲਤ CPP_STRING16:
    ਹਾਲਤ CPP_STRING32:
    ਹਾਲਤ CPP_WSTRING:
    ਹਾਲਤ CPP_UTF8STRING:
      ਵਿਅੰਜਕ = c_parser_string_literal (parser, ਝੂਠ, ਸੱਚ);
      ਰੋਕੋ;
    ਹਾਲਤ CPP_DOT:
      ਵਿਅੰਜਕ = c_parser_gimple_call_ਅੰਦਰੂਨੀ (parser);
      ਰੋਕੋ;
    ਹਾਲਤ CPP_NAME:
      ਜੇ (c_parser_peek_token (parser)->id_ਕਿਸਮ == C_ID_ID)
	{
	  ਰੁੱਖ id = c_parser_peek_token (parser)->ਮੁੱਲ;
	  ਜੇ (strcmp (IDENTIFIER_ਸੂਚਕ (id), "__MEM") == 0)
	    {
	      /* __MEM '<' type-name [ ',' number ] '>'
	               '(' [ '(' type-name ')' ] unary-expression
			   [ '+' number ]
			   [ ',' number ]
			   [ ',' number ':' number ] ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      ਰੁੱਖ type = c_parser_gimple_typespec (parser);
	      ਬਣਤਰ c_ਵਿਅੰਜਕ ptr, alias_off, ਕਦਮ, ਸੂਚਕਾਂਕ, index2;
	      ptr.ਮੁੱਲ = error_mark_ਗੰਢ;
	      alias_off.ਮੁੱਲ = NULL_ਰੁੱਖ;
	      ਕਦਮ.ਮੁੱਲ = NULL_ਰੁੱਖ;
	      ਸੂਚਕਾਂਕ.ਮੁੱਲ = NULL_ਰੁੱਖ;
	      index2.ਮੁੱਲ = NULL_ਰੁੱਖ;
	      ਬਿਨਾਨਿਸ਼ਾਨੀ ਛੋਟਾ clique = 0;
	      ਬਿਨਾਨਿਸ਼ਾਨੀ ਛੋਟਾ ਅਧਾਰ = 0;
	      ਤਾਰਕਿਕ ਉਲਟ_ਕ੍ਰਮ = ਝੂਠ;
	      ਬਣਤਰ c_ਵਿਅੰਜਕ ro;
	      ਜੇ (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  ਰੁੱਖ alias_type = NULL_ਰੁੱਖ;
		  /* Optional alias-type cast.  */
		  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_OPEN_PAREN))
		    {
		      c_parser_consume_token (parser);
		      ਬਣਤਰ c_type_name *alias_type_name
			= c_parser_type_name (parser);
		      c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN,
						 "expected %<)%>");
		      ਜੇ (alias_type_name)
			{
			  ਰੁੱਖ tem;
			  alias_type = groktypename (alias_type_name,
						     &tem, ਨਿਰਾ);
			}
		    }
		  ptr = c_parser_gimple_unary_ਵਿਅੰਜਕ (parser);
		  ਜੇ (ptr.ਮੁੱਲ == error_mark_ਗੰਢ
		      || ! ਸੂਚਕ_TYPE_P (ਰੁੱਖ_TYPE (ptr.ਮੁੱਲ)))
		    {
		      ਜੇ (ptr.ਮੁੱਲ != error_mark_ਗੰਢ)
			error_at (ptr.get_ਸ਼ੁਰੂ (),
				  "invalid type of %<__MEM%> operand");
		      c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN,
						 "expected %<)%>");
		      ਵਾਪਸ ਵਿਅੰਜਕ;
		    }
		  ਜੇ (! alias_type)
		    alias_type = ਰੁੱਖ_TYPE (ptr.ਮੁੱਲ);
		  /* Optional constant offset.  */
		  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      alias_off = c_parser_gimple_postfix_ਵਿਅੰਜਕ (parser);
		    }
		  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_MULT))
		    {
		      std::ਅਦਲਾ_ਬਦਲੀ (ਸੂਚਕਾਂਕ, alias_off);
		      c_parser_consume_token (parser);
		      ਕਦਮ = c_parser_gimple_postfix_ਵਿਅੰਜਕ (parser);
		    }
		  ਨਹੀਂਤਾਂ ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      ਸੂਚਕਾਂਕ = c_parser_gimple_postfix_ਵਿਅੰਜਕ (parser);
		      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_MULT))
			{
			  c_parser_consume_token (parser);
			  ਕਦਮ = c_parser_gimple_postfix_ਵਿਅੰਜਕ (parser);
			}
		      ਨਹੀਂਤਾਂ
			std::ਅਦਲਾ_ਬਦਲੀ (ਸੂਚਕਾਂਕ, index2);
		    }
		  ਨਹੀਂਤਾਂ ਜੇ (alias_off.ਮੁੱਲ
			   && ਰੁੱਖ_ਕੋਡ (alias_off.ਮੁੱਲ) != INTEGER_CST)
		    std::ਅਦਲਾ_ਬਦਲੀ (alias_off, index2);
		  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      index2 = c_parser_gimple_postfix_ਵਿਅੰਜਕ (parser);
		    }
		  ਜੇ (alias_off.ਮੁੱਲ)
		    {
		      ਜੇ (ਰੁੱਖ_ਕੋਡ (alias_off.ਮੁੱਲ) != INTEGER_CST)
			error_at (alias_off.get_ਸ਼ੁਰੂ (),
				  "expected constant offset for %<__MEM%> "
				  "operand");
		      alias_off.ਮੁੱਲ = fold_convert (alias_type,
						      alias_off.ਮੁੱਲ);
		    }
		  ਨਹੀਂਤਾਂ
		    alias_off.ਮੁੱਲ = build_int_cst (alias_type, 0);
		  ਜੇ (ਕਦਮ.ਮੁੱਲ)
		    {
		      ਜੇ (ਰੁੱਖ_ਕੋਡ (ਕਦਮ.ਮੁੱਲ) != INTEGER_CST)
			error_at (ਕਦਮ.get_ਸ਼ੁਰੂ (),
				  "expected constant step for %<__MEM%> "
				  "operand");
		    }
		  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA))
		    {
		      ਬਣਤਰ c_ਵਿਅੰਜਕ cl, ba;
		      ਤਾਰਕਿਕ has_clb = ਸੱਚ;
		      c_parser_consume_token (parser);
		      cl = c_parser_gimple_postfix_ਵਿਅੰਜਕ (parser);
		      ਜੇ (!c_parser_ਅਗਲਾ_token_is (parser, CPP_COLON))
			{
			  ro = cl;
			  ਬਿਨਾਨਿਸ਼ਾਨੀ HOST_WIDE_INT tmp = 0;
			  ਜੇ (!ਰੁੱਖ_ਸਮਾਉਂਦਾ_uhwi_p (ro.ਮੁੱਲ)
			      || (tmp = ਰੁੱਖ_ਮੰਜ਼ਿਲ_uhwi (ro.ਮੁੱਲ)) > 1)
			    error_at (ro.get_ਸ਼ੁਰੂ (),
				      "invalid reverse order value");
			  ਉਲਟ_ਕ੍ਰਮ = tmp;
			  has_clb = ਝੂਠ;
			  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA))
			    {
			      c_parser_consume_token (parser);
			      cl = c_parser_gimple_postfix_ਵਿਅੰਜਕ (parser);
		              has_clb = ਸੱਚ;
			    }
			}
		      ਜੇ (has_clb
			  && c_parser_require (parser,
					       CPP_COLON, "expected %<:%>"))
			{
			  ba = c_parser_gimple_postfix_ਵਿਅੰਜਕ (parser);
			  ਜੇ (!ਰੁੱਖ_ਸਮਾਉਂਦਾ_uhwi_p (cl.ਮੁੱਲ)
			      || !ਰੁੱਖ_ਸਮਾਉਂਦਾ_uhwi_p (ba.ਮੁੱਲ)
			      || compare_ਰੁੱਖ_int (cl.ਮੁੱਲ,
						   (clique = ਰੁੱਖ_ਮੰਜ਼ਿਲ_uhwi
								(cl.ਮੁੱਲ)))
			      || compare_ਰੁੱਖ_int (ba.ਮੁੱਲ,
						   (ਅਧਾਰ = ਰੁੱਖ_ਮੰਜ਼ਿਲ_uhwi
								 (ba.ਮੁੱਲ))))
			    error_at (cl.get_ਸ਼ੁਰੂ (),
				      "invalid clique/base pair");
			}
		    }
		  c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      ਜੇ (! type || c_parser_error (parser))
		{
		  c_parser_ਸੈੱਟ_error (parser, ਝੂਠ);
		  ਵਾਪਸ ਵਿਅੰਜਕ;
		}
	      ਜੇ (ਸੂਚਕਾਂਕ.ਮੁੱਲ || ਕਦਮ.ਮੁੱਲ || index2.ਮੁੱਲ)
		ਵਿਅੰਜਕ.ਮੁੱਲ = build5_loc (loc, ਨਿਸ਼ਾਨਾ_MEM_REF,
					 type, ptr.ਮੁੱਲ, alias_off.ਮੁੱਲ,
					 ਸੂਚਕਾਂਕ.ਮੁੱਲ, ਕਦਮ.ਮੁੱਲ, index2.ਮੁੱਲ);
	      ਨਹੀਂਤਾਂ
		ਵਿਅੰਜਕ.ਮੁੱਲ = build2_loc (loc, MEM_REF,
					 type, ptr.ਮੁੱਲ, alias_off.ਮੁੱਲ);
	      ਜੇ (clique != 0)
		{
		  cfun->ਆਖਰੀ_clique = MAX (cfun->ਆਖਰੀ_clique, clique);
		  MR_DEPENDENCE_CLIQUE (ਵਿਅੰਜਕ.ਮੁੱਲ) = clique;
		  MR_DEPENDENCE_ਅਧਾਰ (ਵਿਅੰਜਕ.ਮੁੱਲ) = ਅਧਾਰ;
		}
	      ਜੇ (ਉਲਟ_ਕ੍ਰਮ)
		{
		  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਵਿਅੰਜਕ.ਮੁੱਲ) == MEM_REF)
		    REF_ਉਲਟ_STORAGE_ਕ੍ਰਮ (ਵਿਅੰਜਕ.ਮੁੱਲ) = ਉਲਟ_ਕ੍ਰਮ;
		  ਨਹੀਂਤਾਂ
		    error_at (ro.get_ਸ਼ੁਰੂ (),
			      "target mem ref cannot have reverse order");
		}
	      ਰੋਕੋ;
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (strcmp (IDENTIFIER_ਸੂਚਕ (id), "__VIEW_CONVERT") == 0)
	    {
	      /* __VIEW_CONVERT '<' type-name [ ',' number ] '>'
	                        '(' postfix-expression ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      ਰੁੱਖ type = c_parser_gimple_typespec (parser);
	      ਜੇ (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_ਵਿਅੰਜਕ op = c_parser_gimple_postfix_ਵਿਅੰਜਕ (parser);
		  c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  ਜੇ (type && op.ਮੁੱਲ != error_mark_ਗੰਢ)
		    ਵਿਅੰਜਕ.ਮੁੱਲ = build1_loc (loc, VIEW_CONVERT_ਵਿਅੰਜਕ,
					     type, op.ਮੁੱਲ);
		}
	      ਰੋਕੋ;
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (strcmp (IDENTIFIER_ਸੂਚਕ (id), "__BIT_FIELD_REF") == 0)
	    {
	      /* __BIT_FIELD_REF '<' type-name [ ',' number ] '>'
	                        '(' postfix-expression, integer, integer ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      ਰੁੱਖ type = c_parser_gimple_typespec (parser);
	      ਜੇ (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_ਵਿਅੰਜਕ op0 = c_parser_gimple_postfix_ਵਿਅੰਜਕ (parser);
		  c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_ਵਿਅੰਜਕ op1 = c_parser_gimple_postfix_ਵਿਅੰਜਕ (parser);
		  ਜੇ (ਰੁੱਖ_ਕੋਡ (op1.ਮੁੱਲ) != INTEGER_CST
		      || !int_ਸਮਾਉਂਦਾ_type_p (op1.ਮੁੱਲ, bitsizetype))
		    c_parser_error (parser, "expected constant size");
		  c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_ਵਿਅੰਜਕ op2 = c_parser_gimple_postfix_ਵਿਅੰਜਕ (parser);
		  ਜੇ (ਰੁੱਖ_ਕੋਡ (op2.ਮੁੱਲ) != INTEGER_CST
		      || !int_ਸਮਾਉਂਦਾ_type_p (op2.ਮੁੱਲ, bitsizetype))
		    c_parser_error (parser, "expected constant offset");
		  c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  ਜੇ (type
		      && op0.ਮੁੱਲ != error_mark_ਗੰਢ
		      && ਰੁੱਖ_ਕੋਡ (op1.ਮੁੱਲ) == INTEGER_CST
		      && ਰੁੱਖ_ਕੋਡ (op2.ਮੁੱਲ) == INTEGER_CST)
		    ਵਿਅੰਜਕ.ਮੁੱਲ = build3_loc (loc, ਦੋਆਧਾਰੀ_ਅੰਕ_ਖੇਤਰ_REF, type,
					     op0.ਮੁੱਲ,
					     fold_convert (bitsizetype,
							   op1.ਮੁੱਲ),
					     fold_convert (bitsizetype,
							   op2.ਮੁੱਲ));
		}
	      ਰੋਕੋ;
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (strcmp (IDENTIFIER_ਸੂਚਕ (id), "__CLOBBER") == 0)
	    {
	      /* __CLOBBER [ '(' bob | eob | bos | eos ')' ]  */
	      clobber_ਕਿਸਮ ਕਿਸਮ = CLOBBER_UNDEF;
	      c_parser_consume_token (parser);
	      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_OPEN_PAREN))
		{
		  c_parser_consume_token (parser);
		  ਸਵੈਚਾਲਿਤ tok = c_parser_peek_token (parser);
		  ਜੇ (c_parser_require (parser, CPP_NAME,
					"expected clobber kind"))
		    {
		      ਅਚਲ ਅੱਖਰ *ਕਿਸਮ_str = IDENTIFIER_ਸੂਚਕ (tok->ਮੁੱਲ);
		      ਜੇ (strcmp (ਕਿਸਮ_str, "bos") == 0)
			ਕਿਸਮ = CLOBBER_STORAGE_BEGIN;
		      ਨਹੀਂਤਾਂ ਜੇ (strcmp (ਕਿਸਮ_str, "bob") == 0)
			ਕਿਸਮ = CLOBBER_OBJECT_BEGIN;
		      ਨਹੀਂਤਾਂ ਜੇ (strcmp (ਕਿਸਮ_str, "eob") == 0)
			ਕਿਸਮ = CLOBBER_OBJECT_ਸਿਰਾ;
		      ਨਹੀਂਤਾਂ ਜੇ (strcmp (ਕਿਸਮ_str, "eos") == 0)
			ਕਿਸਮ = CLOBBER_STORAGE_ਸਿਰਾ;
		      ਨਹੀਂਤਾਂ
			c_parser_error (parser, "expected one of %<bos%>, "
					"%<eos%>, %<bob>, %<eob%>");
		    }
		  c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      /* We infer the (redundant) type from the LHS.  */
	      ਵਿਅੰਜਕ.ਮੁੱਲ = build_clobber (ret_type, ਕਿਸਮ);
	      ਰੋਕੋ;
	    }
	  ਨਹੀਂਤਾਂ ਜੇ (strcmp (IDENTIFIER_ਸੂਚਕ (id), "_Literal") == 0)
	    {
	      /* _Literal '(' type-name ')' ( [ '-' ] constant | constructor ) */
	      c_parser_consume_token (parser);
	      ਰੁੱਖ type = NULL_ਰੁੱਖ;
	      ਜੇ (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  ਬਣਤਰ c_type_name *type_name = c_parser_type_name (parser);
		  ਰੁੱਖ tem;
		  ਜੇ (type_name)
		    type = groktypename (type_name, &tem, ਨਿਰਾ);
		  c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      ਜੇ (! type)
		{
		  c_parser_error (parser, "invalid _Literal");
		  ਵਾਪਸ ਵਿਅੰਜਕ;
		}
	      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_OPEN_BRACE))
		{
		  c_parser_consume_token (parser);
		  ਜੇ (!AGGREGATE_TYPE_P (type)
		      && !ਸਦਿਸ਼_TYPE_P (type))
		    {
		      c_parser_error (parser, "invalid type for _Literal with "
				      "constructor");
		      c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_BRACE,
						 "expected %<}%>");
		      ਵਾਪਸ ਵਿਅੰਜਕ;
		    }
		  vec<constructor_elt, va_gc> *v = ਨਿਰਾ;
		  ਤਾਰਕਿਕ constant_p = ਸੱਚ;
		  ਜੇ (ਸਦਿਸ਼_TYPE_P (type)
		      && !c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_BRACE))
		    {
		      vec_alloc (v, TYPE_ਸਦਿਸ਼_SUBPARTS (type).ਮੰਜ਼ਿਲ_constant ());
		      ਕਰੋ
			{
			  ਰੁੱਖ val
			    = c_parser_gimple_postfix_ਵਿਅੰਜਕ (parser).ਮੁੱਲ;
			  ਜੇ (! val
			      || val == error_mark_ਗੰਢ
			      || (! CONSTANT_CLASS_P (val)
				  && ! SSA_VAR_P (val)))
			    {
			      c_parser_error (parser, "invalid _Literal");
			      ਵਾਪਸ ਵਿਅੰਜਕ;
			    }
			  CONSTRUCTOR_APPEND_ELT (v, NULL_ਰੁੱਖ, val);
			  ਜੇ (! CONSTANT_CLASS_P (val))
			    constant_p = ਝੂਠ;
			  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA))
			    c_parser_consume_token (parser);
			  ਨਹੀਂਤਾਂ
			    ਰੋਕੋ;
			}
		      ਜਦੋਂ (1);
		    }
		  ਜੇ (c_parser_require (parser, CPP_CLOSE_BRACE,
					"expected %<}%>"))
		    {
		      ਜੇ (v && constant_p)
			ਵਿਅੰਜਕ.ਮੁੱਲ = build_ਸਦਿਸ਼_from_ctor (type, v);
		      ਨਹੀਂਤਾਂ
			ਵਿਅੰਜਕ.ਮੁੱਲ = build_constructor (type, v);
		    }
		  ਨਹੀਂਤਾਂ
		    {
		      c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_BRACE,
						 "expected %<}%>");
		      ਵਾਪਸ ਵਿਅੰਜਕ;
		    }
		}
	      ਨਹੀਂਤਾਂ
		{
		  ਤਾਰਕਿਕ neg_p, addr_p;
		  ਜੇ ((neg_p = c_parser_ਅਗਲਾ_token_is (parser, CPP_MINUS)))
		    c_parser_consume_token (parser);
		  ਜੇ ((addr_p = c_parser_ਅਗਲਾ_token_is (parser, CPP_AND)))
		    c_parser_consume_token (parser);
		  ਰੁੱਖ val = c_parser_gimple_postfix_ਵਿਅੰਜਕ (parser).ਮੁੱਲ;
		  ਜੇ (! val
		      || val == error_mark_ਗੰਢ
		      || (!CONSTANT_CLASS_P (val) && !addr_p))
		    {
		      c_parser_error (parser, "invalid _Literal");
		      ਵਾਪਸ ਵਿਅੰਜਕ;
		    }
		  ਜੇ (addr_p)
		    {
		      val = build1 (ADDR_ਵਿਅੰਜਕ, type, val);
		      ਜੇ (!is_gimple_invariant_ਪਤਾ (val))
			{
			  c_parser_error (parser, "invalid _Literal");
			  ਵਾਪਸ ਵਿਅੰਜਕ;
			}
		    }
		  ਜੇ (neg_p)
		    {
		      val = const_unop (NEGATE_ਵਿਅੰਜਕ, ਰੁੱਖ_TYPE (val), val);
		      ਜੇ (! val)
			{
			  c_parser_error (parser, "invalid _Literal");
			  ਵਾਪਸ ਵਿਅੰਜਕ;
			}
		    }
		  ਵਿਅੰਜਕ.ਮੁੱਲ = fold_convert (type, val);
		}
	      ਵਾਪਸ ਵਿਅੰਜਕ;
	    }

	  /* SSA name.  */
	  ਬਿਨਾਨਿਸ਼ਾਨੀ ਸੰਸਕਰਣ, ver_ਵਿੱਥ;
	  ਜੇ (! lookup_name (id)
	      && c_parser_parse_ssa_name_id (id, &ਸੰਸਕਰਣ, &ver_ਵਿੱਥ))
	    {
	      c_parser_consume_token (parser);
	      ਵਿਅੰਜਕ.ਮੁੱਲ = c_parser_parse_ssa_name (parser, id, NULL_ਰੁੱਖ,
						    ਸੰਸਕਰਣ, ver_ਵਿੱਥ);
	      ਜੇ (ਵਿਅੰਜਕ.ਮੁੱਲ == error_mark_ਗੰਢ)
		ਵਾਪਸ ਵਿਅੰਜਕ;
	      ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ਵਿਅੰਜਕ, tok_range);
	      /* For default definition SSA names.  */
	      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_OPEN_PAREN)
		  && c_parser_peek_2nd_token (parser)->type == CPP_NAME
		  && strcmp ("D",
			     IDENTIFIER_ਸੂਚਕ
			       (c_parser_peek_2nd_token (parser)->ਮੁੱਲ)) == 0
		  && c_parser_peek_nth_token (parser, 3)->type == CPP_CLOSE_PAREN)
		{
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		  ਜੇ (! SSA_NAME_IS_DEFAULT_DEF (ਵਿਅੰਜਕ.ਮੁੱਲ))
		    {
		      ਜੇ (!SSA_NAME_VAR (ਵਿਅੰਜਕ.ਮੁੱਲ))
			{
			  error_at (loc, "anonymous SSA name cannot have"
				    " default definition");
			  ਵਿਅੰਜਕ.ਮੁੱਲ = error_mark_ਗੰਢ;
			  ਵਾਪਸ ਵਿਅੰਜਕ;
			}
		      ਸੈੱਟ_ssa_default_def (cfun, SSA_NAME_VAR (ਵਿਅੰਜਕ.ਮੁੱਲ),
					   ਵਿਅੰਜਕ.ਮੁੱਲ);
		      SSA_NAME_DEF_STMT (ਵਿਅੰਜਕ.ਮੁੱਲ) = gimple_build_nop ();
		    }
		}
	    }
	  ਨਹੀਂਤਾਂ
	    {
	      c_parser_consume_token (parser);
	      ਵਿਅੰਜਕ.ਮੁੱਲ
		= build_external_ref (loc, id,
				      (c_parser_peek_token (parser)->type
				       == CPP_OPEN_PAREN), &ਵਿਅੰਜਕ.original_type);
	      ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ਵਿਅੰਜਕ, tok_range);
	    }
	  ਰੋਕੋ;
	}
      /* Fallthru.  */
    ਮੂਲ:
      c_parser_error (parser, "expected expression");
      ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
      ਰੋਕੋ;
    }
  ਜੇ (ਵਿਅੰਜਕ.ਮੁੱਲ == error_mark_ਗੰਢ)
    ਵਾਪਸ ਵਿਅੰਜਕ;
  ਵਾਪਸ c_parser_gimple_postfix_ਵਿਅੰਜਕ_after_primary
    (parser, ਵਿਅੰਜਕ_LOC_OR_LOC (ਵਿਅੰਜਕ.ਮੁੱਲ, loc), ਵਿਅੰਜਕ);
}

/* Parse a gimple postfix expression after the initial primary or compound
   literal.  */

ਸਥਿਰ ਬਣਤਰ c_ਵਿਅੰਜਕ
c_parser_gimple_postfix_ਵਿਅੰਜਕ_after_primary (gimple_parser &parser,
						  location_t ਵਿਅੰਜਕ_loc,
						  ਬਣਤਰ c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ)
{
  location_t ਸ਼ੁਰੂ;
  location_t ਅੰਤ;
  ਰੁੱਖ ident;
  location_t comp_loc;

  ਜਦੋਂ (ਸੱਚ)
    {
      location_t op_loc = c_parser_peek_token (parser)->location;
      ਚੋਣ (c_parser_peek_token (parser)->type)
	{
	ਹਾਲਤ CPP_OPEN_ਵਰਗਫਲ:
	  {
	    c_parser_consume_token (parser);
	    ਰੁੱਖ idx = c_parser_gimple_unary_ਵਿਅੰਜਕ (parser).ਮੁੱਲ;

	    ਜੇ (! c_parser_require (parser, CPP_CLOSE_ਵਰਗਫਲ, "expected %<]%>"))
	      {
		c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_ਵਰਗਫਲ, ਨਿਰਾ);
		ਰੋਕੋ;
	      }

	    ਸ਼ੁਰੂ = ਵਿਅੰਜਕ.get_ਸ਼ੁਰੂ ();
	    ਅੰਤ = c_parser_ਟੋਕਨ_buf (parser, 0)->location;
	    ਵਿਅੰਜਕ.ਮੁੱਲ = build_array_ref (op_loc, ਵਿਅੰਜਕ.ਮੁੱਲ, idx);
	    ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ਵਿਅੰਜਕ, ਸ਼ੁਰੂ, ਅੰਤ);
	    ਵਿਅੰਜਕ.m_decimal = 0;

	    ਵਿਅੰਜਕ.original_ਕੋਡ = ERROR_MARK;
	    ਵਿਅੰਜਕ.original_type = ਨਿਰਾ;
	    ਰੋਕੋ;
	  }
	ਹਾਲਤ CPP_OPEN_PAREN:
	  {
	    /* Function call.  */
	    c_parser_consume_token (parser);
	    auto_vec<ਰੁੱਖ> exprlist;
	    ਜੇ (! c_parser_ਅਗਲਾ_token_is (parser, CPP_CLOSE_PAREN))
	      c_parser_gimple_ਵਿਅੰਜਕ_list (parser, &exprlist);
	    c_parser_skip_until_ਮਿਲਿਆ (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    ਜੇ (!FUNC_OR_ਵਿਧੀ_TYPE_P (ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ.ਮੁੱਲ)))
	      {
		c_parser_error (parser, "invalid call to non-function");
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		ਰੋਕੋ;
	      }
	    ਵਿਅੰਜਕ.ਮੁੱਲ = build_call_array_loc
		(ਵਿਅੰਜਕ_loc, ਰੁੱਖ_TYPE (ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ.ਮੁੱਲ)),
		 ਵਿਅੰਜਕ.ਮੁੱਲ, exprlist.ਲੰਮਾਈ (), exprlist.ਪਤਾ ());
	    ਵਿਅੰਜਕ.m_decimal = 0;
	    ਵਿਅੰਜਕ.original_ਕੋਡ = ERROR_MARK;
	    ਵਿਅੰਜਕ.original_type = ਨਿਰਾ;
	    ਰੋਕੋ;
	  }
	ਹਾਲਤ CPP_DOT:
	  {
	    /* Structure element reference.  */
	    c_parser_consume_token (parser);
	    ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		ident = comp_tok->ਮੁੱਲ;
		comp_loc = comp_tok->location;
	      }
	    ਨਹੀਂਤਾਂ
	      {
		c_parser_error (parser, "expected identifier");
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		ਵਿਅੰਜਕ.original_ਕੋਡ = ERROR_MARK;
		ਵਿਅੰਜਕ.original_type = ਨਿਰਾ;
		ਵਾਪਸ ਵਿਅੰਜਕ;
	      }
	    ਸ਼ੁਰੂ = ਵਿਅੰਜਕ.get_ਸ਼ੁਰੂ ();
	    ਅੰਤ = c_parser_peek_token (parser)->get_ਅੰਤ ();
	    c_parser_consume_token (parser);
	    ਵਿਅੰਜਕ.ਮੁੱਲ = build_component_ref (op_loc, ਵਿਅੰਜਕ.ਮੁੱਲ, ident,
					      comp_loc, UNKNOWN_LOCATION);
	    ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ਵਿਅੰਜਕ, ਸ਼ੁਰੂ, ਅੰਤ);
	    ਵਿਅੰਜਕ.m_decimal = 0;
	    ਵਿਅੰਜਕ.original_ਕੋਡ = ERROR_MARK;
	    ਜੇ (ਰੁੱਖ_ਕੋਡ (ਵਿਅੰਜਕ.ਮੁੱਲ) != COMPONENT_REF)
	      ਵਿਅੰਜਕ.original_type = ਨਿਰਾ;
	    ਨਹੀਂਤਾਂ
	      {
		/* Remember the original type of a bitfield.  */
		ਰੁੱਖ ਖੇਤਰ_2 = ਰੁੱਖ_ਸੰਕਾਰਜ (ਵਿਅੰਜਕ.ਮੁੱਲ, 1);
		ਜੇ (ਰੁੱਖ_ਕੋਡ (ਖੇਤਰ_2) != ਖੇਤਰ_DECL)
		  ਵਿਅੰਜਕ.original_type = ਨਿਰਾ;
		ਨਹੀਂਤਾਂ
		  ਵਿਅੰਜਕ.original_type = DECL_ਦੋਆਧਾਰੀ_ਅੰਕ_ਖੇਤਰ_TYPE (ਖੇਤਰ_2);
	      }
	    ਰੋਕੋ;
	  }
	ਹਾਲਤ CPP_DEREF:
	  {
	    /* Structure element reference.  */
	    ਜੇ (!ਸੂਚਕ_TYPE_P (ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ.ਮੁੱਲ)))
	      {
		c_parser_error (parser, "dereference of non-pointer");
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		ਵਿਅੰਜਕ.original_ਕੋਡ = ERROR_MARK;
		ਵਿਅੰਜਕ.original_type = ਨਿਰਾ;
		ਵਾਪਸ ਵਿਅੰਜਕ;
	      }
	    c_parser_consume_token (parser);
	    ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		ident = comp_tok->ਮੁੱਲ;
		comp_loc = comp_tok->location;
	      }
	    ਨਹੀਂਤਾਂ
	      {
		c_parser_error (parser, "expected identifier");
		ਵਿਅੰਜਕ.ਸੈੱਟ_error ();
		ਵਿਅੰਜਕ.original_ਕੋਡ = ERROR_MARK;
		ਵਿਅੰਜਕ.original_type = ਨਿਰਾ;
		ਵਾਪਸ ਵਿਅੰਜਕ;
	      }
	    ਸ਼ੁਰੂ = ਵਿਅੰਜਕ.get_ਸ਼ੁਰੂ ();
	    ਅੰਤ = c_parser_peek_token (parser)->get_ਅੰਤ ();
	    c_parser_consume_token (parser);
	    ਵਿਅੰਜਕ.ਮੁੱਲ = build_component_ref (op_loc,
					      build_simple_mem_ref_loc
					        (op_loc, ਵਿਅੰਜਕ.ਮੁੱਲ),
					      ident, comp_loc,
					      ਵਿਅੰਜਕ.get_location ());
	    ਸੈੱਟ_c_ਵਿਅੰਜਕ_ਸਰੋਤ_range (&ਵਿਅੰਜਕ, ਸ਼ੁਰੂ, ਅੰਤ);
	    ਵਿਅੰਜਕ.m_decimal = 0;
	    ਵਿਅੰਜਕ.original_ਕੋਡ = ERROR_MARK;
	    ਜੇ (ਰੁੱਖ_ਕੋਡ (ਵਿਅੰਜਕ.ਮੁੱਲ) != COMPONENT_REF)
	      ਵਿਅੰਜਕ.original_type = ਨਿਰਾ;
	    ਨਹੀਂਤਾਂ
	      {
		/* Remember the original type of a bitfield.  */
		ਰੁੱਖ ਖੇਤਰ_2 = ਰੁੱਖ_ਸੰਕਾਰਜ (ਵਿਅੰਜਕ.ਮੁੱਲ, 1);
		ਜੇ (ਰੁੱਖ_ਕੋਡ (ਖੇਤਰ_2) != ਖੇਤਰ_DECL)
		  ਵਿਅੰਜਕ.original_type = ਨਿਰਾ;
		ਨਹੀਂਤਾਂ
		  ਵਿਅੰਜਕ.original_type = DECL_ਦੋਆਧਾਰੀ_ਅੰਕ_ਖੇਤਰ_TYPE (ਖੇਤਰ_2);
	      }
	    ਰੋਕੋ;
	  }
	ਮੂਲ:
	  ਵਾਪਸ ਵਿਅੰਜਕ;
	}
    }
}

/* Parse expression list.

   gimple-expr-list:
     gimple-unary-expression
     gimple-expr-list , gimple-unary-expression

 */

ਸਥਿਰ ਖਾਲੀ
c_parser_gimple_ਵਿਅੰਜਕ_list (gimple_parser &parser, vec<ਰੁੱਖ> *ret)
{
  ਬਣਤਰ c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ;

  ਵਿਅੰਜਕ = c_parser_gimple_unary_ਵਿਅੰਜਕ (parser);
  ret->ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (ਵਿਅੰਜਕ.ਮੁੱਲ);
  ਜਦੋਂ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      ਵਿਅੰਜਕ = c_parser_gimple_unary_ਵਿਅੰਜਕ (parser);
      ret->ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (ਵਿਅੰਜਕ.ਮੁੱਲ);
    }
}

/* Parse gimple label.

   gimple-label:
     identifier :
     case constant-expression :
     default :

*/

ਸਥਿਰ ਖਾਲੀ
c_parser_gimple_label (gimple_parser &parser, gimple_seq *seq)
{
  ਰੁੱਖ name = c_parser_peek_token (parser)->ਮੁੱਲ;
  location_t loc1 = c_parser_peek_token (parser)->location;
  gcc_assert (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME));
  c_parser_consume_token (parser);
  gcc_assert (c_parser_ਅਗਲਾ_token_is (parser, CPP_COLON));
  c_parser_consume_token (parser);
  ਰੁੱਖ label = define_label (loc1, name);
  ਜੇ (label)
    gimple_seq_ਜੋੜੋ_stmt_without_update (seq, gimple_build_label (label));
  ਵਾਪਸ;
}

/* Parse gimple/RTL pass list.

   gimple-or-rtl-pass-list:
     startwith("pass-name")[,{cfg,ssa}]
 */

ਖਾਲੀ
c_parser_gimple_or_rtl_pass_list (c_parser *parser, c_declspecs *specs)
{
  ਅੱਖਰ *pass = ਨਿਰਾ;

  /* Accept __GIMPLE/__RTL.  */
  ਜੇ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_OPEN_PAREN))
    ਵਾਪਸ;
  c_parser_consume_token (parser);

  specs->ਇੰਦਰਾਜ_bb_ਗਿਣਤੀ = profile_ਗਿਣਤੀ::uninitialized ();
  ਜਦੋਂ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
    {
      profile_quality quality;
      ਅਚਲ ਅੱਖਰ *op = IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ);
      c_parser_consume_token (parser);
      ਜੇ (! strcmp (op, "startwith"))
	{
	  ਜੇ (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    ਵਾਪਸ;
	  ਜੇ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_STRING))
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"expected pass name");
	      ਵਾਪਸ;
	    }
	  pass = xstrdup (ਰੁੱਖ_STRING_ਸੂਚਕ
			  (c_parser_string_literal (parser, ਝੂਠ,
						    ਝੂਠ).ਮੁੱਲ));
	  ਜੇ (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<(%>"))
	    ਵਾਪਸ;
	}
      ਨਹੀਂਤਾਂ ਜੇ (parse_profile_quality (op, &quality))
	{
	  ਰੁੱਖ q;
	  ਜੇ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    ਵਾਪਸ;

	  ਜੇ (!c_parser_ਅਗਲਾ_token_is (parser, CPP_ਸੰਖਿਆ)
	      || (ਰੁੱਖ_ਕੋਡ (q = c_parser_peek_token (parser)->ਮੁੱਲ)
		  != INTEGER_CST))
	    {
	      c_parser_error (parser, "expected count value");
	      ਵਾਪਸ;
	    }

	  specs->ਇੰਦਰਾਜ_bb_ਗਿਣਤੀ
	    = profile_ਗਿਣਤੀ::from_gcov_type (ਰੁੱਖ_INT_CST_ਨੀਵਾਂ (q), quality);
	  c_parser_consume_token (parser);
	  ਜੇ (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    ਵਾਪਸ;
	}
      ਨਹੀਂਤਾਂ ਜੇ (specs->declspec_il != cdil_gimple)
	/* Allow only one IL specifier and none on RTL.  */
	;
      ਨਹੀਂਤਾਂ ਜੇ (! strcmp (op, "cfg"))
	specs->declspec_il = cdil_gimple_cfg;
      ਨਹੀਂਤਾਂ ਜੇ (! strcmp (op, "ssa"))
	specs->declspec_il = cdil_gimple_ssa;
      ਨਹੀਂਤਾਂ
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "invalid operation");
	  ਵਾਪਸ;
	}
     ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COMMA))
       c_parser_consume_token (parser);
    }

  ਜੇ (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    ਵਾਪਸ;

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
ਰਜਿਸਟਰ

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

ਸਥਿਰ ਖਾਲੀ
c_parser_gimple_declaration (gimple_parser &parser)
{
  ਬਣਤਰ c_declarator *declarator;
  ਬਣਤਰ c_declspecs *specs = build_null_declspecs ();
  c_parser_declspecs (parser, specs, ਸੱਚ, ਸੱਚ, ਸੱਚ,
		      ਸੱਚ, ਸੱਚ, ਸੱਚ, ਸੱਚ, cla_nonabstract_decl);
  ਅੰਤ_declspecs (specs);

  /* Provide better error recovery.  Note that a type name here is usually
     better diagnosed as a redeclaration.  */
  ਜੇ (c_parser_ਅਗਲਾ_token_starts_declspecs (parser)
      && ! c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<;%>");
      c_parser_ਸੈੱਟ_error (parser, ਝੂਠ);
      ਵਾਪਸ;
    }

  ਤਾਰਕਿਕ dummy = ਝੂਠ;
  declarator = c_parser_declarator (parser,
				    specs->typespec_ਕਿਸਮ != ctsk_none,
				    C_DTR_ਸਾਧਾਰਨ, &dummy);

  ਜੇ (!c_parser_ਅਗਲਾ_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_error (parser, "expected %<;%>");
      ਵਾਪਸ;
    }
  ਜੇ (declarator)
    {
      /* Handle SSA name decls specially, they do not go into the identifier
         table but we simply build the SSA name for later lookup.  */
      ਬਿਨਾਨਿਸ਼ਾਨੀ ਸੰਸਕਰਣ, ver_ਵਿੱਥ;
      /* Handle SSA pointer declarations in a very simplistic ways, we
	 probably would like to call grokdeclarator in a special mode to
	 just build the type of the decl - start_decl already pushes
	 the identifier to the bindings for lookup, something we do not
	 want.  */
      ਬਣਤਰ c_declarator *id_declarator = declarator;
      ਜਦੋਂ (id_declarator->ਕਿਸਮ == cdk_ਸੂਚਕ)
	id_declarator = id_declarator->declarator;
      ਜੇ (id_declarator->ਕਿਸਮ == cdk_id
	  && (declarator->ਕਿਸਮ == cdk_ਸੂਚਕ
	      || is_gimple_reg_type (specs->type))
	  && c_parser_parse_ssa_name_id (id_declarator->u.id.id,
					 &ਸੰਸਕਰਣ, &ver_ਵਿੱਥ)
	  /* The following restricts it to unnamed anonymous SSA names
	     which fails parsing of named ones in dumps (we could
	     decide to not dump their name for -gimple).  */
	  && ver_ਵਿੱਥ == 0)
	{
	  ਬਣਤਰ c_declarator *p = declarator;
	  ਰੁੱਖ type = specs->type;
	  ਜਦੋਂ (p->ਕਿਸਮ == cdk_ਸੂਚਕ)
	    {
	      type = build_ਸੂਚਕ_type (type);
	      p = p->declarator;
	    }
	  c_parser_parse_ssa_name (parser, id_declarator->u.id.id, type,
				   ਸੰਸਕਰਣ, ver_ਵਿੱਥ);
	}
      ਨਹੀਂਤਾਂ
	{
	  ਰੁੱਖ postfix_attrs = NULL_ਰੁੱਖ;
	  ਰੁੱਖ all_ਅਗੇਤਰ_attrs = specs->attrs;
	  specs->attrs = ਨਿਰਾ;
	  ਰੁੱਖ decl = ਸ਼ੁਰੂ_decl (declarator, specs, ਝੂਠ,
				  chainon (postfix_attrs, all_ਅਗੇਤਰ_attrs));
	  ਜੇ (decl)
	    ਅੰਤ_decl (decl, UNKNOWN_LOCATION, NULL_ਰੁੱਖ, NULL_ਰੁੱਖ,
			 NULL_ਰੁੱਖ);
	}
    }
}

/* Parse gimple goto statement.  */

ਸਥਿਰ ਖਾਲੀ
c_parser_gimple_goto_stmt (gimple_parser &parser,
			   location_t loc, ਰੁੱਖ label, gimple_seq *seq)
{
  ਜੇ (cfun->curr_properties & PROP_cfg)
    {
      ਪੂਰਨ dest_ਸੂਚਕਾਂਕ;
      profile_probability prob;
      ਜੇ (c_parser_gimple_parse_bb_spec_ਕਿਨਾਰਾ_probability (label, parser,
							  &dest_ਸੂਚਕਾਂਕ, &prob))
	{
	  parser.ਧੱਕੋ_ਕਿਨਾਰਾ (parser.current_bb->ਸੂਚਕਾਂਕ, dest_ਸੂਚਕਾਂਕ,
			    ਕਿਨਾਰਾ_FALLTHRU, prob);
	  ਵਾਪਸ;
	}
    }
  ਰੁੱਖ decl = lookup_label_for_goto (loc, label);
  gimple_seq_ਜੋੜੋ_stmt_without_update (seq, gimple_build_goto (decl));
}

/* Parse a parenthesized condition.
   gimple-condition:
     ( gimple-binary-expression )    */

ਸਥਿਰ ਰੁੱਖ
c_parser_gimple_paren_condition (gimple_parser &parser)
{
  ਜੇ (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    ਵਾਪਸ error_mark_ਗੰਢ;
  ਰੁੱਖ cond
    = c_parser_gimple_ਦੁਆਧਾਰੀ_ਵਿਅੰਜਕ (parser, boolean_type_ਗੰਢ).ਮੁੱਲ;
  ਜੇ (cond != error_mark_ਗੰਢ
      && ! COMPARISON_CLASS_P (cond)
      && ! CONSTANT_CLASS_P (cond)
      && ! SSA_VAR_P (cond))
    {
      c_parser_error (parser, "comparison required");
      cond = error_mark_ਗੰਢ;
    }
  ਜੇ (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    ਵਾਪਸ error_mark_ਗੰਢ;
  ਵਾਪਸ cond;
}

/* Parse gimple try statement.

   try-statement:
     try { ... } finally { ... }
     try { ... } finally { ... } else { ... }

   This could support try/catch as well, but it's not implemented yet.
 */

ਸਥਿਰ ਖਾਲੀ
c_parser_gimple_try_stmt (gimple_parser &parser, gimple_seq *seq)
{
  gimple_seq tryseq = ਨਿਰਾ;
  c_parser_consume_token (parser);
  c_parser_gimple_compound_statement (parser, &tryseq);

  ਜੇ ((c_parser_ਅਗਲਾ_token_is (parser, CPP_KEYWORD)
       && c_parser_peek_token (parser)->keyword == RID_AT_FINALLY)
      || (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME)
	  && c_parser_peek_token (parser)->id_ਕਿਸਮ == C_ID_ID
	  && strcmp (IDENTIFIER_ਸੂਚਕ (c_parser_peek_token (parser)->ਮੁੱਲ),
		     "finally") == 0))
    {
      gimple_seq finseq = ਨਿਰਾ;
      c_parser_consume_token (parser);
      c_parser_gimple_compound_statement (parser, &finseq);

      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_ELSE)
	{
	  gimple_seq elsseq = ਨਿਰਾ;
	  c_parser_consume_token (parser);
	  c_parser_gimple_compound_statement (parser, &elsseq);

	  geh_else *stmt = gimple_build_eh_else (finseq, elsseq);
	  finseq = ਨਿਰਾ;
	  gimple_seq_ਜੋੜੋ_stmt_without_update (&finseq, stmt);
	}

      gtry *stmt = gimple_build_try (tryseq, finseq, GIMPLE_TRY_FINALLY);
      gimple_seq_ਜੋੜੋ_stmt_without_update (seq, stmt);
    }
  ਨਹੀਂਤਾਂ ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_KEYWORD)
      && c_parser_peek_token (parser)->keyword == RID_AT_CATCH)
    c_parser_error (parser, "%<catch%> is not supported");
  ਨਹੀਂਤਾਂ
    c_parser_error (parser, "expected %<finally%> or %<catch%>");
}

/* Parse gimple if-else statement.

   if-statement:
     if ( gimple-binary-expression ) gimple-goto-statement
     if ( gimple-binary-expression ) gimple-goto-statement \
					else gimple-goto-statement
 */

ਸਥਿਰ ਖਾਲੀ
c_parser_gimple_if_stmt (gimple_parser &parser, gimple_seq *seq)
{
  ਰੁੱਖ t_label = NULL_ਰੁੱਖ, f_label = NULL_ਰੁੱਖ, label;
  location_t loc;
  c_parser_consume_token (parser);
  ਰੁੱਖ cond = c_parser_gimple_paren_condition (parser);

  ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_GOTO))
    {
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      ਜੇ (! c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected label");
	  ਵਾਪਸ;
	}
      label = c_parser_peek_token (parser)->ਮੁੱਲ;
      c_parser_consume_token (parser);
      ਪੂਰਨ dest_ਸੂਚਕਾਂਕ;
      profile_probability prob;
      ਜੇ ((cfun->curr_properties & PROP_cfg)
	  && c_parser_gimple_parse_bb_spec_ਕਿਨਾਰਾ_probability (label, parser,
							     &dest_ਸੂਚਕਾਂਕ, &prob))
	parser.ਧੱਕੋ_ਕਿਨਾਰਾ (parser.current_bb->ਸੂਚਕਾਂਕ, dest_ਸੂਚਕਾਂਕ,
			  ਕਿਨਾਰਾ_TRUE_ਮੁੱਲ, prob);
      ਨਹੀਂਤਾਂ
	t_label = lookup_label_for_goto (loc, label);
      ਜੇ (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	ਵਾਪਸ;
    }
  ਨਹੀਂਤਾਂ
    {
      c_parser_error (parser, "expected goto expression");
      ਵਾਪਸ;
    }

  ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_ELSE))
    c_parser_consume_token (parser);
  ਨਹੀਂਤਾਂ
    {
      c_parser_error (parser, "expected else statement");
      ਵਾਪਸ;
    }

  ਜੇ (c_parser_ਅਗਲਾ_token_is_keyword (parser, RID_GOTO))
    {
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      ਜੇ (! c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected label");
	  ਵਾਪਸ;
	}
      label = c_parser_peek_token (parser)->ਮੁੱਲ;
      c_parser_consume_token (parser);
      ਪੂਰਨ dest_ਸੂਚਕਾਂਕ;
      profile_probability prob;
      ਜੇ ((cfun->curr_properties & PROP_cfg)
	  && c_parser_gimple_parse_bb_spec_ਕਿਨਾਰਾ_probability (label, parser,
							     &dest_ਸੂਚਕਾਂਕ, &prob))
	parser.ਧੱਕੋ_ਕਿਨਾਰਾ (parser.current_bb->ਸੂਚਕਾਂਕ, dest_ਸੂਚਕਾਂਕ,
			  ਕਿਨਾਰਾ_FALSE_ਮੁੱਲ, prob);
      ਨਹੀਂਤਾਂ
	f_label = lookup_label_for_goto (loc, label);
      ਜੇ (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	ਵਾਪਸ;
    }
  ਨਹੀਂਤਾਂ
    {
      c_parser_error (parser, "expected goto expression");
      ਵਾਪਸ;
    }

  ਜੇ (cond != error_mark_ਗੰਢ)
    gimple_seq_ਜੋੜੋ_stmt_without_update (seq, gimple_build_cond_from_ਰੁੱਖ (cond, t_label,
							   f_label));
}

/* Parse gimple switch-statement.

   gimple-switch-statement:
     switch (gimple-postfix-expression) gimple-case-statement

   gimple-case-statement:
     gimple-case-statement
     gimple-label-statement : gimple-goto-statement
*/

ਸਥਿਰ ਖਾਲੀ
c_parser_gimple_switch_stmt (gimple_parser &parser, gimple_seq *seq)
{
  c_ਵਿਅੰਜਕ cond_ਵਿਅੰਜਕ;
  ਰੁੱਖ case_label, label;
  auto_vec<ਰੁੱਖ> labels;
  ਰੁੱਖ default_label = NULL_ਰੁੱਖ;
  c_parser_consume_token (parser);

  ਜੇ (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    ਵਾਪਸ;
  cond_ਵਿਅੰਜਕ = c_parser_gimple_postfix_ਵਿਅੰਜਕ (parser);
  ਜੇ (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    ਵਾਪਸ;

  ਜੇ (! c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    ਵਾਪਸ;

  ਜਦੋਂ (c_parser_ਅਗਲਾ_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_EOF))
	{
	  c_parser_error (parser, "expected statement");
	  ਵਾਪਸ;
	}

      ਚੋਣ (c_parser_peek_token (parser)->keyword)
	{
	ਹਾਲਤ RID_CASE:
	  {
	    c_ਵਿਅੰਜਕ exp1;
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);

	    ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME)
		|| c_parser_peek_token (parser)->type == CPP_ਸੰਖਿਆ)
	      exp1 = c_parser_gimple_postfix_ਵਿਅੰਜਕ (parser);
	    ਨਹੀਂਤਾਂ
	      {
		c_parser_error (parser, "expected expression");
		ਵਾਪਸ;
	      }

	    ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COLON))
	      {
		c_parser_consume_token (parser);
		ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
		  {
		    label = c_parser_peek_token (parser)->ਮੁੱਲ;
		    c_parser_consume_token (parser);
		    ਰੁੱਖ decl = lookup_label_for_goto (loc, label);
		    case_label = build_case_label (exp1.ਮੁੱਲ, NULL_ਰੁੱਖ,
						   decl);
		    labels.ਸੁਰੱਖਿਅਤ_ਧੱਕੋ (case_label);
		    ਜੇ (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      ਵਾਪਸ;
		  }
		ਨਹੀਂਤਾਂ ਜੇ (! c_parser_require (parser, CPP_NAME,
					     "expected label"))
		  ਵਾਪਸ;
	      }
	    ਨਹੀਂਤਾਂ ਜੇ (! c_parser_require (parser, CPP_SEMICOLON,
					 "expected %<:%>"))
	      ਵਾਪਸ;
	    ਰੋਕੋ;
	  }
	ਹਾਲਤ RID_DEFAULT:
	  {
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);
	    ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_COLON))
	      {
		c_parser_consume_token (parser);
		ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_NAME))
		  {
		    label = c_parser_peek_token (parser)->ਮੁੱਲ;
		    c_parser_consume_token (parser);
		    ਰੁੱਖ decl = lookup_label_for_goto (loc, label);
		    default_label = build_case_label (NULL_ਰੁੱਖ, NULL_ਰੁੱਖ,
						      decl);
		    ਜੇ (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      ਵਾਪਸ;
		  }
		ਨਹੀਂਤਾਂ ਜੇ (! c_parser_require (parser, CPP_NAME,
					     "expected label"))
		  ਵਾਪਸ;
	      }
	    ਨਹੀਂਤਾਂ ਜੇ (! c_parser_require (parser, CPP_SEMICOLON,
					 "expected %<:%>"))
	      ਵਾਪਸ;
	    ਰੋਕੋ;
	  }
	ਮੂਲ:
	  c_parser_error (parser, "expected case label");
	  ਵਾਪਸ;
	}

    }
  ਜੇ (! c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>"))
    ਵਾਪਸ;

  ਜੇ (cond_ਵਿਅੰਜਕ.ਮੁੱਲ != error_mark_ਗੰਢ)
    {
      gswitch *s = gimple_build_switch (cond_ਵਿਅੰਜਕ.ਮੁੱਲ, default_label, labels);
      gimple_seq_ਜੋੜੋ_stmt_without_update (seq, s);
    }
}

/* Parse gimple return statement.  */

ਸਥਿਰ ਖਾਲੀ
c_parser_gimple_return_stmt (gimple_parser &parser, gimple_seq *seq)
{
  location_t loc = c_parser_peek_token (parser)->location;
  gimple *ret = ਨਿਰਾ;
  c_parser_consume_token (parser);
  ਜੇ (c_parser_ਅਗਲਾ_token_is (parser, CPP_SEMICOLON))
    {
      c_ਅੰਤ_gimple_return (loc, NULL_ਰੁੱਖ);
      ret = gimple_build_return (ਨਿਰਾ);
      gimple_seq_ਜੋੜੋ_stmt_without_update (seq, ret);
    }
  ਨਹੀਂਤਾਂ
    {
      location_t xloc = c_parser_peek_token (parser)->location;
      c_ਵਿਅੰਜਕ ਵਿਅੰਜਕ = c_parser_gimple_unary_ਵਿਅੰਜਕ (parser);
      ਜੇ (ਵਿਅੰਜਕ.ਮੁੱਲ != error_mark_ਗੰਢ)
	{
	  c_ਅੰਤ_gimple_return (xloc, ਵਿਅੰਜਕ.ਮੁੱਲ);
	  ret = gimple_build_return (ਵਿਅੰਜਕ.ਮੁੱਲ);
	  gimple_seq_ਜੋੜੋ_stmt_without_update (seq, ret);
	}
    }
}

/* Support function for c_parser_gimple_return_stmt.  */

ਸਥਿਰ ਖਾਲੀ
c_ਅੰਤ_gimple_return (location_t loc, ਰੁੱਖ retval)
{
  ਰੁੱਖ valtype = ਰੁੱਖ_TYPE (ਰੁੱਖ_TYPE (current_function_decl));

  /* Use the expansion point to handle cases such as returning NULL
     in a function returning void.  */
  location_t xloc = expansion_ਬਿੰਦੂ_location_if_ਵਿੱਚ_system_ਸਿਰਲੇਖ (loc);

  ਜੇ (ਰੁੱਖ_THIS_VOLATILE (current_function_decl))
    warning_at (xloc, 0,
		"function declared %<noreturn%> has a %<return%> statement");

  ਜੇ (! retval)
    current_function_returns_null = 1;
  ਨਹੀਂਤਾਂ ਜੇ (valtype == 0 || VOID_TYPE_P (valtype))
    {
      current_function_returns_null = 1;
      ਜੇ (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (retval)) != VOID_TYPE)
	{
	  error_at
	    (xloc, "%<return%> with a value, in function returning void");
	  inform (DECL_ਸਰੋਤ_LOCATION (current_function_decl),
		  "declared here");
	}
    }
  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (valtype) != ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (retval)))
    {
      error_at
	(xloc, "invalid conversion in return statement");
      inform (DECL_ਸਰੋਤ_LOCATION (current_function_decl),
	      "declared here");
    }
  ਵਾਪਸ;
}
