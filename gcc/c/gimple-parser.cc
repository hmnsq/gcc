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

#ಅನ್ತರ್ಭಾವ "config.h"
#ಅನ್ತರ್ಭಾವ "system.h"
#ಅನ್ತರ್ಭಾವ "coretypes.h"
#ಅನ್ತರ್ಭಾವ "target.h"
#ಅನ್ತರ್ಭಾವ "function.h"
#ಅನ್ತರ್ಭಾವ "c-tree.h"
#ಅನ್ತರ್ಭಾವ "timevar.h"
#ಅನ್ತರ್ಭಾವ "stringpool.h"
#ಅನ್ತರ್ಭಾವ "cgraph.h"
#ಅನ್ತರ್ಭಾವ "attribs.h"
#ಅನ್ತರ್ಭಾವ "stor-layout.h"
#ಅನ್ತರ್ಭಾವ "varasm.h"
#ಅನ್ತರ್ಭಾವ "trans-mem.h"
#ಅನ್ತರ್ಭಾವ "c-family/c-pragma.h"
#ಅನ್ತರ್ಭಾವ "c-lang.h"
#ಅನ್ತರ್ಭಾವ "c-family/c-objc.h"
#ಅನ್ತರ್ಭಾವ "plugin.h"
#ಅನ್ತರ್ಭಾವ "builtins.h"
#ಅನ್ತರ್ಭಾವ "gomp-constants.h"
#ಅನ್ತರ್ಭಾವ "c-family/c-indentation.h"
#ಅನ್ತರ್ಭಾವ "gimple-expr.h"
#ಅನ್ತರ್ಭಾವ "context.h"
#ಅನ್ತರ್ಭಾವ "gcc-rich-location.h"
#ಅನ್ತರ್ಭಾವ "c-parser.h"
#ಅನ್ತರ್ಭಾವ "tree-vrp.h"
#ಅನ್ತರ್ಭಾವ "tree-pass.h"
#ಅನ್ತರ್ಭಾವ "tree-pretty-print.h"
#ಅನ್ತರ್ಭಾವ "tree.h"
#ಅನ್ತರ್ಭಾವ "basic-block.h"
#ಅನ್ತರ್ಭಾವ "gimple.h"
#ಅನ್ತರ್ಭಾವ "gimple-pretty-print.h"
#ಅನ್ತರ್ಭಾವ "tree-ssa.h"
#ಅನ್ತರ್ಭಾವ "pass_manager.h"
#ಅನ್ತರ್ಭಾವ "tree-ssanames.h"
#ಅನ್ತರ್ಭಾವ "gimple-ssa.h"
#ಅನ್ತರ್ಭಾವ "tree-dfa.h"
#ಅನ್ತರ್ಭಾವ "internal-fn.h"
#ಅನ್ತರ್ಭಾವ "cfg.h"
#ಅನ್ತರ್ಭಾವ "cfghooks.h"
#ಅನ್ತರ್ಭಾವ "bitmap.h"
#ಅನ್ತರ್ಭಾವ "cfganal.h"
#ಅನ್ತರ್ಭಾವ "tree-cfg.h"
#ಅನ್ತರ್ಭಾವ "gimple-iterator.h"
#ಅನ್ತರ್ಭಾವ "cfgloop.h"
#ಅನ್ತರ್ಭಾವ "tree-phinodes.h"
#ಅನ್ತರ್ಭಾವ "tree-into-ssa.h"


/* GIMPLE parser state.  */

ವರ್ಗ gimple_parser
{
ಸಾರ್ವಜನಿಕ:
  gimple_parser (c_parser *p) : parser (p), ಅಂಚುಗಳು(), current_bb(ಖಾಲಿ) {}
  /* c_parser is not visible here, use composition and fake inheritance
     via a conversion operator.  */
  ಕ್ರಿಯಾಕಾರಕ c_parser *() { ಹಿಂತಿರುಗಿ parser; }
  c_parser *parser;

  /* CFG build state.  */
  ವರ್ಗ gimple_parser_ಅಂಚು
  {
  ಸಾರ್ವಜನಿಕ:
    ಪೂರ್ಣಾಂಕ src;
    ಪೂರ್ಣಾಂಕ dest;
    ಪೂರ್ಣಾಂಕ flags;
    profile_probability probability;
  };
  auto_vec<gimple_parser_ಅಂಚು> ಅಂಚುಗಳು;
  basic_ಖಂಡ current_bb;

  ಶೂನ್ಯ ತಳ್ಳು_ಅಂಚು (ಪೂರ್ಣಾಂಕ, ಪೂರ್ಣಾಂಕ, ಪೂರ್ಣಾಂಕ, profile_probability);
};

ಶೂನ್ಯ
gimple_parser::ತಳ್ಳು_ಅಂಚು (ಪೂರ್ಣಾಂಕ src, ಪೂರ್ಣಾಂಕ dest, ಪೂರ್ಣಾಂಕ flags,
			  profile_probability prob)
{
  gimple_parser_ಅಂಚು e;
  e.src = src;
  e.dest = dest;
  e.flags = flags;
  e.probability = prob;
  ಅಂಚುಗಳು.ಸುರಕ್ಷಿತ_ತಳ್ಳು (e);
}


/* Gimple parsing functions.  */
ಸ್ಥಿರ ತಾರ್ಕಿಕ c_parser_gimple_compound_statement (gimple_parser &, gimple_seq *);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_gimple_label (gimple_parser &, gimple_seq *);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_gimple_statement (gimple_parser &, gimple_seq *);
ಸ್ಥಿರ ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ c_parser_gimple_ದ್ವಿಮಾನ_ಅಭಿವ್ಯಕ್ತಿ (gimple_parser &, ವೃಕ್ಷ);
ಸ್ಥಿರ ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ c_parser_gimple_unary_ಅಭಿವ್ಯಕ್ತಿ (gimple_parser &);
ಸ್ಥಿರ ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ c_parser_gimple_postfix_ಅಭಿವ್ಯಕ್ತಿ
			(gimple_parser &, ವೃಕ್ಷ = error_mark_ಗಂಟು);
ಸ್ಥಿರ ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ c_parser_gimple_postfix_ಅಭಿವ್ಯಕ್ತಿ_after_primary
			(gimple_parser &, location_t, ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_gimple_declaration (gimple_parser &);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_gimple_goto_stmt (gimple_parser &, location_t,
				       ವೃಕ್ಷ, gimple_seq *);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_gimple_try_stmt (gimple_parser &, gimple_seq *);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_gimple_if_stmt (gimple_parser &, gimple_seq *);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_gimple_switch_stmt (gimple_parser &, gimple_seq *);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_gimple_return_stmt (gimple_parser &, gimple_seq *);
ಸ್ಥಿರ ಶೂನ್ಯ c_ಮುಕ್ತಾಯ_gimple_return (location_t, ವೃಕ್ಷ);
ಸ್ಥಿರ ವೃಕ್ಷ c_parser_gimple_paren_condition (gimple_parser &);
ಸ್ಥಿರ ಶೂನ್ಯ c_parser_gimple_ಅಭಿವ್ಯಕ್ತಿ_list (gimple_parser &, vec<ವೃಕ್ಷ> *);


/* Much like parser_build_unary_op, but avoid applying default conversions.  */

ಸ್ಥಿರ c_ಅಭಿವ್ಯಕ್ತಿ
gimple_parser_build_unary_op (location_t loc,
			      ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_2 ಸಂಕೇತ_2, ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ arg)
{
  ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ ಫಲಿತಾಂಶ;

  ಫಲಿತಾಂಶ.original_ಸಂಕೇತ = ಸಂಕೇತ_2;
  ಫಲಿತಾಂಶ.original_type = ಖಾಲಿ;
  ಫಲಿತಾಂಶ.m_decimal = 0;

  ಆದರೆ (reject_gcc_builtin (arg.ಮೌಲ್ಯ))
    {
      ಫಲಿತಾಂಶ.ಮೌಲ್ಯ = error_mark_ಗಂಟು;
    }
  ಇಲ್ಲದಿದ್ದರೆ
    {
      ಫಲಿತಾಂಶ.ಮೌಲ್ಯ = build_unary_op (loc, ಸಂಕೇತ_2, arg.ಮೌಲ್ಯ, ನಿಜ);

      ಆದರೆ (ವೃಕ್ಷ_ಅತಿಪ್ರವಾಹ_P (ಫಲಿತಾಂಶ.ಮೌಲ್ಯ) && !ವೃಕ್ಷ_ಅತಿಪ್ರವಾಹ_P (arg.ಮೌಲ್ಯ))
	ಅತಿಪ್ರವಾಹ_warning (loc, ಫಲಿತಾಂಶ.ಮೌಲ್ಯ, arg.ಮೌಲ್ಯ);
    }

  /* We are typically called when parsing a prefix token at LOC acting on
     ARG.  Reflect this by updating the source range of the result to
     start at LOC and end at the end of ARG.  */
  ಗಣ_c_ಅಭಿವ್ಯಕ್ತಿ_ಮೂಲ_range (&ಫಲಿತಾಂಶ,
			   loc, arg.get_ಮುಕ್ತಾಯ ());

  ಹಿಂತಿರುಗಿ ಫಲಿತಾಂಶ;
}

/* See if VAL is an identifier matching __BB<num> and return <num>
   in *INDEX.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
c_parser_gimple_parse_bb_spec (ವೃಕ್ಷ val, ಪೂರ್ಣಾಂಕ *ಸೂಚ್ಯಂಕ)
{
  ಆದರೆ (!startswith (IDENTIFIER_ಸೂಚಕ (val), "__BB"))
    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *bb = IDENTIFIER_ಸೂಚಕ (val) + 4;
  ಆದರೆ (! ISDIGIT (*bb))
    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

  ಅಕ್ಷರ *pend;
  errno = 0;
  ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ದೀರ್ಘ ಸಂಖ್ಯೆ = strtoul (bb, &pend, 10);
  ಆದರೆ (errno == ERANGE
      || *pend != '\0'
      || ಸಂಖ್ಯೆ > ಗರಿಷ್ಠ_ಪೂರ್ಣಾಂಕ)
    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

  *ಸೂಚ್ಯಂಕ = ಸಂಖ್ಯೆ;
  ಹಿಂತಿರುಗಿ ನಿಜ;
}

/* See if VAL is an identifier matching __BB<num> and return <num>
   in *INDEX.  Return true if so and parse also FREQUENCY of
   the edge.  */


ಸ್ಥಿರ ತಾರ್ಕಿಕ
c_parser_gimple_parse_bb_spec_ಅಂಚು_probability (ವೃಕ್ಷ val,
						gimple_parser &parser,
						ಪೂರ್ಣಾಂಕ *ಸೂಚ್ಯಂಕ,
						profile_probability
						*probability)
{
  ತಾರ್ಕಿಕ return_p = c_parser_gimple_parse_bb_spec (val, ಸೂಚ್ಯಂಕ);
  ಆದರೆ (return_p)
    {
      *probability = profile_probability::uninitialized ();
      /* Parse frequency if provided.  */
      ಆದರೆ (c_parser_ಮುಂದಿನ_token_is (parser, CPP_OPEN_PAREN))
	{
	  ವೃಕ್ಷ f;
	  c_parser_consume_token (parser);
	  ಆದರೆ (!c_parser_ಮುಂದಿನ_token_is (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected frequency quality");
	      ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
	    }

	  profile_quality quality;
	  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *v
	    = IDENTIFIER_ಸೂಚಕ (c_parser_peek_token (parser)->ಮೌಲ್ಯ);
	  ಆದರೆ (!parse_profile_quality (v, &quality))
	    {
	      c_parser_error (parser, "unknown profile quality");
	      ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
	    }

	  c_parser_consume_token (parser);
	  ಆದರೆ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

	  ಆದರೆ (!c_parser_ಮುಂದಿನ_token_is (parser, CPP_ಸಂಖ್ಯೆ)
	      || (ವೃಕ್ಷ_ಸಂಕೇತ (f = c_parser_peek_token (parser)->ಮೌಲ್ಯ)
		  != INTEGER_CST))
	    {
	      c_parser_error (parser, "expected frequency value");
	      ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
	    }

	  ಚಿಹ್ನೆರಹಿತ ಪೂರ್ಣಾಂಕ ಮೌಲ್ಯ = ವೃಕ್ಷ_INT_CST_ಕೆಳಗಿನ (f);
	  *probability = profile_probability (ಮೌಲ್ಯ, quality);

	  c_parser_consume_token (parser);
	  ಆದರೆ (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

	  ಆದರೆ (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
	}

      ಹಿಂತಿರುಗಿ ನಿಜ;
    }

  ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

}

/* Parse the body of a function declaration marked with "__GIMPLE".  */

ಶೂನ್ಯ
c_parser_parse_gimple_body (c_parser *cparser, ಅಕ್ಷರ *gimple_pass,
			    ಎಣಿಕೆ c_declspec_il cdil,
			    profile_ಎಣಿಕೆ ನಮೂದು_bb_ಎಣಿಕೆ)
{
  gimple_parser parser (cparser);
  gimple_seq seq = ಖಾಲಿ;
  gimple_seq body = ಖಾಲಿ;
  ವೃಕ್ಷ stmt = ತಳ್ಳು_stmt_list ();
  ತಳ್ಳು_scope ();
  location_t loc1 = c_parser_peek_token (parser)->location;

  cfun->pass_startwith = gimple_pass;
  init_ವೃಕ್ಷ_ssa (cfun);

  ಆದರೆ (cdil == cdil_gimple)
    /* While we have SSA names in the IL we do not have a CFG built yet
       and PHIs are represented using a PHI internal function.  We do
       have lowered control flow and exception handling (well, we do not
       have parser support for EH yet).  But as we still have BINDs
       we have to go through lowering again.  */
    cfun->curr_properties = PROP_gimple_any;
  ಇಲ್ಲದಿದ್ದರೆ
    {
      /* We have at least cdil_gimple_cfg.  */
      gimple_ರಿಜಿಸ್ಟರ್_cfg_hooks ();
      init_ಖಾಲಿಗಳು_ವೃಕ್ಷ_cfg ();
      parser.current_bb = ನಮೂದು_ಖಂಡ_PTR_FOR_FN (cfun);
      /* Initialize the bare loop structure - we are going to only
         mark headers and leave the rest to fixup.  */
      ಗಣ_loops_for_fn (cfun, ggc_cleared_alloc<ರಚನೆ loops> ());
      init_loops_structure (cfun, loops_for_fn (cfun), 1);
      loops_state_ಗಣ (cfun, LOOPS_NEED_FIXUP|LOOPS_MAY_HAVE_ಅಪವರ್ತ್ಯ_LATCHES);
      cfun->curr_properties
	|= PROP_gimple_lcf | PROP_gimple_leh | PROP_cfg | PROP_loops;
      ಆದರೆ (cdil == cdil_gimple_ssa)
	{
	  init_ssa_operands (cfun);
	  cfun->curr_properties |= PROP_ssa;
	}
    }

  ಆದರೆ (! c_parser_gimple_compound_statement (parser, &seq)
      && cdil == cdil_gimple)
    {
      gimple *ret = gimple_build_return (ಖಾಲಿ);
      gimple_seq_ಕೂಡಿಸು_stmt_without_update (&seq, ret);
    }

  ವೃಕ್ಷ ಖಂಡ = ತೆಗೆ_scope ();
  stmt = ತೆಗೆ_stmt_list (stmt);
  stmt = c_build_bind_ಅಭಿವ್ಯಕ್ತಿ (loc1, ಖಂಡ, stmt);

  ಖಂಡ = DECL_INITIAL (current_function_decl);
  ಖಂಡ_SUBBLOCKS (ಖಂಡ) = NULL_ವೃಕ್ಷ;
  ಖಂಡ_CHAIN (ಖಂಡ) = NULL_ವೃಕ್ಷ;
  ವೃಕ್ಷ_ASM_WRITTEN (ಖಂಡ) = 1;

  ಆದರೆ (cdil == cdil_gimple)
    {
      gbind *bind_stmt = gimple_build_bind (BIND_ಅಭಿವ್ಯಕ್ತಿ_VARS (stmt), ಖಾಲಿ,
					    BIND_ಅಭಿವ್ಯಕ್ತಿ_ಖಂಡ (stmt));
      gimple_bind_ಗಣ_body (bind_stmt, seq);
      gimple_seq_ಕೂಡಿಸು_stmt_without_update (&body, bind_stmt);
      gimple_ಗಣ_body (current_function_decl, body);
    }
  ಇಲ್ಲದಿದ್ದರೆ
    {
      /* Control-flow and binds are lowered, record local decls.  */
      ಗಾಗಿ (ವೃಕ್ಷ var = BIND_ಅಭಿವ್ಯಕ್ತಿ_VARS (stmt); var; var = DECL_CHAIN (var))
	ಆದರೆ (VAR_P (var)
	    && !DECL_EXTERNAL (var))
	  {
	    ಕೂಡಿಸು_local_decl (cfun, var);
	    /* When the middle-end re-gimplifies any expression we might
	       run into the assertion that we've seen the decl in a BIND.  */
	    ಆದರೆ (!ವೃಕ್ಷ_STATIC (var))
	      DECL_ನೋಡಿದ_ಒಳ_BIND_ಅಭಿವ್ಯಕ್ತಿ_P (var) = 1;
	  }
      /* We have a CFG.  Build the edges.  */
      ಗಾಗಿ (ಚಿಹ್ನೆರಹಿತ i = 0; i < parser.ಅಂಚುಗಳು.ಉದ್ದಳತೆ (); ++i)
	{
	  ಅಂಚು e = make_ಅಂಚು (BASIC_ಖಂಡ_FOR_FN (cfun, parser.ಅಂಚುಗಳು[i].src),
			      BASIC_ಖಂಡ_FOR_FN (cfun, parser.ಅಂಚುಗಳು[i].dest),
			      parser.ಅಂಚುಗಳು[i].flags);
	  e->probability = parser.ಅಂಚುಗಳು[i].probability;
	}
      /* Add edges for case labels.  */
      basic_ಖಂಡ bb;
      FOR_EACH_BB_FN (bb, cfun)
	ಆದರೆ (ಅಂಚು_ಎಣಿಕೆ (bb->succs) == 0)
	  {
	    ಆದರೆ (gswitch *sw = ಸುರಕ್ಷಿತ_dyn_cast <gswitch *> (*gsi_ಕೊನೆಯ_bb (bb)))
	      ಗಾಗಿ (ಚಿಹ್ನೆರಹಿತ i = 0; i < gimple_switch_ಅಂಕೆ_labels (sw); ++i)
		{
		  basic_ಖಂಡ label_bb = gimple_switch_label_bb (cfun, sw, i);
		  make_ಅಂಚು (bb, label_bb, 0);
		}
	  }
      /* Need those for loop fixup.  */
      calculate_dominance_info (CDI_DOMINATORS);
      /* With SSA lower PHIs parsed as internal function calls and
	 update stmts.  */
      ಆದರೆ (cdil == cdil_gimple_ssa)
	{
	  /* Create PHI nodes, they are parsed into __PHI internal calls
	     and update SSA operands.  */
	  FOR_EACH_BB_FN (bb, cfun)
	    {
	      gimple_stmt_iterator gsi;
	      ಗಾಗಿ (gsi = gsi_ಆರಂಭ_bb (bb); !gsi_ಕೊನೆ_p (gsi);)
		{
		  gimple *stmt = gsi_stmt (gsi);
		  ಆದರೆ (!gimple_call_ಆಂತರಿಕ_p (stmt, IFN_PHI))
		    ನಿಲ್ಲಿಸು;

		  gphi *phi = create_phi_ಗಂಟು (gimple_call_lhs (stmt), bb);
		  ಗಾಗಿ (ಚಿಹ್ನೆರಹಿತ i = 0; i < gimple_call_ಅಂಕೆ_ವಾದಗಳು (stmt); i += 2)
		    {
		      ಪೂರ್ಣಾಂಕ srcidx = ವೃಕ್ಷ_INT_CST_ಕೆಳಗಿನ (gimple_call_arg (stmt, i));
		      ಅಂಚು e = ಕಂಡುಹಿಡಿ_ಅಂಚು (BASIC_ಖಂಡ_FOR_FN (cfun, srcidx), bb);
		      ಆದರೆ (!e)
			c_parser_error (parser, "edge not found");
		      ಇಲ್ಲದಿದ್ದರೆ
			ಕೂಡಿಸು_phi_arg (phi, gimple_call_arg (stmt, i + 1), e,
				     UNKNOWN_LOCATION);
		    }
		  gsi_remove (&gsi, ನಿಜ);
		}
	      ಗಾಗಿ (; !gsi_ಕೊನೆ_p (gsi); gsi_ಮುಂದಿನ (&gsi))
		update_stmt (gsi_stmt (gsi));
	    }
	  /* Fill SSA name gaps, putting them on the freelist and diagnose
	     SSA names without definition.  */
	  ಗಾಗಿ (ಚಿಹ್ನೆರಹಿತ i = 1; i < ಅಂಕೆ_ssa_ಹೆಸರುಗಳು; ++i)
	    ಆದರೆ (!ssa_name (i))
	      {
		ವೃಕ್ಷ name = make_ssa_name_fn (cfun, integer_type_ಗಂಟು, ಖಾಲಿ, i);
		release_ssa_name_fn (cfun, name);
	      }
	    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!SSA_NAME_DEF_STMT (ssa_name (i)))
	      error ("SSA name %qE with version %d has no definition",
		     ssa_name (i), i);
	  /* No explicit virtual operands (yet).  */
	  bitmap_obstack_initialize (ಖಾಲಿ);
	  update_ssa (TODO_update_ssa_only_virtuals);
	  bitmap_obstack_release (ಖಾಲಿ);
	  /* ???  By flushing the freelist after virtual operand SSA rewrite
	     we keep the gaps available for re-use like needed for the
	     PR89595 testcase but then usually virtual operands would have
	     taken most of them.  The fix is obviously to make virtual
	     operands explicit in the SSA IL.  */
	  flush_ssaname_freelist ();
	}
      fix_loop_structure (ಖಾಲಿ);
    }

  ಆದರೆ (cfun->curr_properties & PROP_cfg)
    {
      ನಮೂದು_ಖಂಡ_PTR_FOR_FN (cfun)->ಎಣಿಕೆ_2 = ನಮೂದು_bb_ಎಣಿಕೆ;
      gcov_type t = param_gimple_fe_computed_hot_bb_ಮಿತಿ;
      ಗಣ_hot_bb_ಮಿತಿ (t);
      update_max_bb_ಎಣಿಕೆ ();
      cgraph_ಗಂಟು::get_create (cfun->decl);
      cgraph_ಅಂಚು::rebuild_ಅಂಚುಗಳು ();
    }

  /* Perform IL validation and if any error is found abort compilation
     of this function by zapping its body.  */
  ಆದರೆ ((cfun->curr_properties & PROP_cfg)
      && verify_gimple_ಒಳ_cfg (cfun, ಸುಳ್ಳು, ಸುಳ್ಳು))
    init_ಖಾಲಿಗಳು_ವೃಕ್ಷ_cfg ();
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (!(cfun->curr_properties & PROP_cfg)
	   && verify_gimple_ಒಳ_seq (gimple_body (current_function_decl), ಸುಳ್ಳು))
    gimple_ಗಣ_body (current_function_decl, ಖಾಲಿ);

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

ಸ್ಥಿರ ತಾರ್ಕಿಕ
c_parser_gimple_compound_statement (gimple_parser &parser, gimple_seq *seq)
{
  ತಾರ್ಕಿಕ return_p = ಸುಳ್ಳು;

  ಆದರೆ (! c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

  /* A compound statement starts with optional declarations.  */
  ಆಗ (c_parser_ಮುಂದಿನ_ಟೋಕನುಗಳು_ಆರಂಭ_declaration (parser))
    {
      c_parser_gimple_declaration (parser);
      ಆದರೆ (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
    }

  ಆಗ (c_parser_ಮುಂದಿನ_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      ಆದರೆ (c_parser_error (parser))
	{
	  c_parser_skip_until_ಸಿಕ್ಕಿತು (parser, CPP_CLOSE_BRACE, ಖಾಲಿ);
	  ಹಿಂತಿರುಗಿ return_p;
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (c_parser_ಮುಂದಿನ_token_is (parser, CPP_EOF))
	{
	  c_parser_error (parser, "expected declaration or statement");
	  ಹಿಂತಿರುಗಿ return_p;
	}

      ಆಯ್ಕೆ (c_parser_peek_token (parser)->type)
	{
	ಸ್ಥಿತಿ CPP_KEYWORD:
	  ಆಯ್ಕೆ (c_parser_peek_token (parser)->keyword)
	    {
	    ಸ್ಥಿತಿ RID_AT_TRY:
	      c_parser_gimple_try_stmt (parser, seq);
	      ನಿಲ್ಲಿಸು;
	    ಸ್ಥಿತಿ RID_IF:
	      c_parser_gimple_if_stmt (parser, seq);
	      ನಿಲ್ಲಿಸು;
	    ಸ್ಥಿತಿ RID_SWITCH:
	      c_parser_gimple_switch_stmt (parser, seq);
	      ನಿಲ್ಲಿಸು;
	    ಸ್ಥಿತಿ RID_GOTO:
	      {
		location_t loc = c_parser_peek_token (parser)->location;
		c_parser_consume_token (parser);
		ಆದರೆ (c_parser_ಮುಂದಿನ_token_is (parser, CPP_NAME))
		  {
		    ವೃಕ್ಷ label = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
		    c_parser_consume_token (parser);
		    c_parser_gimple_goto_stmt (parser, loc, label, seq);
		    ಆದರೆ (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      ಹಿಂತಿರುಗಿ return_p;
		  }
		}
	      ನಿಲ್ಲಿಸು;
	    ಸ್ಥಿತಿ RID_RETURN:
	      return_p = ನಿಜ;
	      c_parser_gimple_return_stmt (parser, seq);
	      ಆದರೆ (! c_parser_require (parser, CPP_SEMICOLON,
				      "expected %<;%>"))
		ಹಿಂತಿರುಗಿ return_p;
	      ಆದರೆ (cfun->curr_properties & PROP_cfg)
		parser.ತಳ್ಳು_ಅಂಚು (parser.current_bb->ಸೂಚ್ಯಂಕ, EXIT_ಖಂಡ, 0,
				  profile_probability::uninitialized ());
	      ನಿಲ್ಲಿಸು;
	    ಪೂರ್ವನಿಯೋಜಿತ:
	      ಹೋಗು ಅಭಿವ್ಯಕ್ತಿ_stmt;
	    }
	  ನಿಲ್ಲಿಸು;
	ಸ್ಥಿತಿ CPP_NAME:
	  ಆದರೆ (c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_gimple_label (parser, seq);
	      ನಿಲ್ಲಿಸು;
	    }
	  ಆದರೆ (c_parser_ಮುಂದಿನ_token_is (parser, CPP_NAME)
	      && c_parser_peek_token (parser)->id_ಬಗೆ == C_ID_ID
	      && strcmp (IDENTIFIER_ಸೂಚಕ (c_parser_peek_token (parser)->ಮೌಲ್ಯ),
			 "try") == 0)
	    {
	      c_parser_gimple_try_stmt (parser, seq);
	      ನಿಲ್ಲಿಸು;
	    }
	  /* Basic block specification.
	     __BB (index, ...)  */
	  ಆದರೆ ((cfun->curr_properties & PROP_cfg)
	      && !strcmp (IDENTIFIER_ಸೂಚಕ
			    (c_parser_peek_token (parser)->ಮೌಲ್ಯ), "__BB"))
	    {
	      c_parser_consume_token (parser);
	      ಆದರೆ (! c_parser_require (parser, CPP_OPEN_PAREN,
				      "expected %<(%>"))
		ಹಿಂತಿರುಗಿ return_p;
	      ಆದರೆ (c_parser_ಮುಂದಿನ_token_is_not (parser, CPP_ಸಂಖ್ಯೆ))
		{
		  c_parser_error (parser, "expected block index");
		  ಹಿಂತಿರುಗಿ return_p;
		}
	      ವೃಕ್ಷ tnum = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
	      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (tnum) != INTEGER_CST)
		{
		  c_parser_error (parser, "expected block index");
		  ಹಿಂತಿರುಗಿ return_p;
		}
	      ಪೂರ್ಣಾಂಕ ಸೂಚ್ಯಂಕ = ವೃಕ್ಷ_INT_CST_ಕೆಳಗಿನ (tnum);
	      ಆದರೆ (ಸೂಚ್ಯಂಕ < ಅಂಕೆ_FIXED_ಖಂಡಗಳು
		  || (ಸೂಚ್ಯಂಕ < ಕೊನೆಯ_basic_ಖಂಡ_for_fn (cfun)
		      && BASIC_ಖಂಡ_FOR_FN (cfun, ಸೂಚ್ಯಂಕ) != ಖಾಲಿ))
		{
		  c_parser_error (parser, "invalid block index");
		  ಹಿಂತಿರುಗಿ return_p;
		}
	      ಪೂರ್ಣಾಂಕ is_loop_ಶೀರ್ಷಿಕೆ_ದ = -1;
	      profile_ಎಣಿಕೆ bb_ಎಣಿಕೆ = profile_ಎಣಿಕೆ::uninitialized ();
	      c_parser_consume_token (parser);
	      ಆಗ (c_parser_ಮುಂದಿನ_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  ಆದರೆ (! c_parser_ಮುಂದಿನ_token_is (parser, CPP_NAME))
		    {
		      c_parser_error (parser, "expected block specifier");
		      ಹಿಂತಿರುಗಿ return_p;
		    }
		  /* loop_header (NUM)  */
		  ಆದರೆ (!strcmp (IDENTIFIER_ಸೂಚಕ
			         (c_parser_peek_token (parser)->ಮೌಲ್ಯ),
			       "loop_header"))
		    {
		      c_parser_consume_token (parser);
		      ಆದರೆ (! c_parser_require (parser, CPP_OPEN_PAREN,
					      "expected %<(%>"))
			ಹಿಂತಿರುಗಿ return_p;
		      ವೃಕ್ಷ loop_ಅಂಕೆ;
		      ಆದರೆ (! c_parser_ಮುಂದಿನ_token_is (parser, CPP_ಸಂಖ್ಯೆ)
			  || ವೃಕ್ಷ_ಸಂಕೇತ (loop_ಅಂಕೆ
					  = c_parser_peek_token (parser)->ಮೌಲ್ಯ)
			       != INTEGER_CST)
			{
			  c_parser_error (parser, "expected loop number");
			  ಹಿಂತಿರುಗಿ return_p;
			}
		      c_parser_consume_token (parser);
		      is_loop_ಶೀರ್ಷಿಕೆ_ದ = ವೃಕ್ಷ_INT_CST_ಕೆಳಗಿನ (loop_ಅಂಕೆ);
		      ಆದರೆ (! c_parser_require (parser, CPP_CLOSE_PAREN,
					      "expected %<)%>"))
			ಹಿಂತಿರುಗಿ return_p;
		    }
		  /* Parse profile: quality(value) */
		  ಇಲ್ಲದಿದ್ದರೆ
		    {
		      ವೃಕ್ಷ q;
		      profile_quality quality;
		      ವೃಕ್ಷ v = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
		      ಆದರೆ (!parse_profile_quality (IDENTIFIER_ಸೂಚಕ (v),
						  &quality))
			{
			  c_parser_error (parser, "unknown block specifier");
			  ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
			}

		      c_parser_consume_token (parser);
		      ಆದರೆ (!c_parser_require (parser, CPP_OPEN_PAREN,
					     "expected %<(%>"))
			ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

		      ಆದರೆ (!c_parser_ಮುಂದಿನ_token_is (parser, CPP_ಸಂಖ್ಯೆ)
			  || (ವೃಕ್ಷ_ಸಂಕೇತ (q = c_parser_peek_token (parser)->ಮೌಲ್ಯ)
			      != INTEGER_CST))
			{
			  c_parser_error (parser, "expected count value");
			  ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
			}

		      bb_ಎಣಿಕೆ
			= profile_ಎಣಿಕೆ::from_gcov_type (ವೃಕ್ಷ_INT_CST_ಕೆಳಗಿನ (q),
							 quality);
		      c_parser_consume_token (parser);
		      ಆದರೆ (! c_parser_require (parser, CPP_CLOSE_PAREN,
					      "expected %<)%>"))
			ಹಿಂತಿರುಗಿ return_p;
		    }
		}
	      ಆದರೆ (! c_parser_require (parser, CPP_CLOSE_PAREN,
				      "expected %<)%>")
		  || ! c_parser_require (parser, CPP_COLON,
					 "expected %<:%>"))
		ಹಿಂತಿರುಗಿ return_p;

	      /* Put stmts parsed in the current block.  */
	      ಆದರೆ (!gimple_seq_ಖಾಲಿಗಳು_p (*seq))
		{
		  ಆದರೆ (!parser.current_bb)
		    c_parser_error (parser, "stmts without block");
		  ಇಲ್ಲದಿದ್ದರೆ
		    {
		      gimple_stmt_iterator gsi
			= gsi_ಆರಂಭ_bb (parser.current_bb);
		      gsi_ಸೇರಿಸು_seq_after_without_update (&gsi, *seq,
							   GSI_CONTINUE_LINKING);
		    }
		  *seq = ಖಾಲಿ;
		}

	      /* Build an empty block with specified index, linking them
		 in source order.  */
	      basic_ಖಂಡ bb = alloc_ಖಂಡ ();
	      bb->ಸೂಚ್ಯಂಕ = ಸೂಚ್ಯಂಕ;
	      link_ಖಂಡ (bb, (parser.current_bb ? parser.current_bb
			       : ನಮೂದು_ಖಂಡ_PTR_FOR_FN (cfun)));
	      ಆದರೆ (basic_ಖಂಡ_info_for_fn (cfun)->ಉದ್ದಳತೆ () <= (ಗಾತ್ರ_t)ಸೂಚ್ಯಂಕ)
		vec_ಸುರಕ್ಷಿತ_grow_cleared (basic_ಖಂಡ_info_for_fn (cfun),
				       ಸೂಚ್ಯಂಕ + 1, ನಿಜ);
	      ಗಣ_BASIC_ಖಂಡ_FOR_FN (cfun, ಸೂಚ್ಯಂಕ, bb);
	      ಆದರೆ (ಕೊನೆಯ_basic_ಖಂಡ_for_fn (cfun) <= ಸೂಚ್ಯಂಕ)
		ಕೊನೆಯ_basic_ಖಂಡ_for_fn (cfun) = ಸೂಚ್ಯಂಕ + 1;
	      n_basic_ಖಂಡಗಳು_for_fn (cfun)++;
	      ಆದರೆ (parser.current_bb->ಸೂಚ್ಯಂಕ == ನಮೂದು_ಖಂಡ)
		parser.ತಳ್ಳು_ಅಂಚು (ನಮೂದು_ಖಂಡ, bb->ಸೂಚ್ಯಂಕ, ಅಂಚು_FALLTHRU,
				  profile_probability::always ());

	      /* We leave the proper setting to fixup.  */
	      ವರ್ಗ loop *loop_father = loops_for_fn (cfun)->ವೃಕ್ಷ_ಬೇರು;
	      /* If the new block is a loop header, allocate a loop
		 struct.  Fixup will take care of proper placement within
		 the loop tree.  */
	      ಆದರೆ (is_loop_ಶೀರ್ಷಿಕೆ_ದ != -1)
		{
		  ಆದರೆ (ಸಂಖ್ಯೆ_ದ_loops (cfun) > (ಚಿಹ್ನೆರಹಿತ)is_loop_ಶೀರ್ಷಿಕೆ_ದ
		      && get_loop (cfun, is_loop_ಶೀರ್ಷಿಕೆ_ದ) != ಖಾಲಿ)
		    {
		      c_parser_error (parser, "duplicate loop header");
		    }
		  ಇಲ್ಲದಿದ್ದರೆ
		    {
		      ವರ್ಗ loop *loop = alloc_loop ();
		      loop->ಅಂಕೆ = is_loop_ಶೀರ್ಷಿಕೆ_ದ;
		      loop->ಶೀರ್ಷಿಕೆ = bb;
		      ಆದರೆ (ಸಂಖ್ಯೆ_ದ_loops (cfun) <= (ಚಿಹ್ನೆರಹಿತ)is_loop_ಶೀರ್ಷಿಕೆ_ದ)
			vec_ಸುರಕ್ಷಿತ_grow_cleared (loops_for_fn (cfun)->larray,
					       is_loop_ಶೀರ್ಷಿಕೆ_ದ + 1, ನಿಜ);
		      (*loops_for_fn (cfun)->larray)[is_loop_ಶೀರ್ಷಿಕೆ_ದ] = loop;
		      flow_loop_ವೃಕ್ಷ_ಗಂಟು_ಕೂಡಿಸು (loops_for_fn (cfun)->ವೃಕ್ಷ_ಬೇರು,
					       loop);
		    }
		  loop_father = get_loop (cfun, is_loop_ಶೀರ್ಷಿಕೆ_ದ);
		}
	      bb->loop_father = loop_father;
	      bb->ಎಣಿಕೆ_2 = bb_ಎಣಿಕೆ;

	      /* Stmts now go to the new block.  */
	      parser.current_bb = bb;
	      ನಿಲ್ಲಿಸು;
	    }
	  ಹೋಗು ಅಭಿವ್ಯಕ್ತಿ_stmt;

	ಸ್ಥಿತಿ CPP_SEMICOLON:
	  {
	    /* Empty stmt.  */
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);
	    gimple *nop = gimple_build_nop ();
	    gimple_ಗಣ_location (nop, loc);
	    gimple_seq_ಕೂಡಿಸು_stmt_without_update (seq, nop);
	    ನಿಲ್ಲಿಸು;
	  }

	ಸ್ಥಿತಿ CPP_CLOSE_PAREN:
	ಸ್ಥಿತಿ CPP_CLOSE_ವರ್ಗಫಲ:
	  /* Avoid infinite loop in error recovery:
	     c_parser_skip_until_found stops at a closing nesting
	     delimiter without consuming it, but here we need to consume
	     it to proceed further.  */
	  c_parser_error (parser, "expected statement");
	  c_parser_consume_token (parser);
	ನಿಲ್ಲಿಸು;

	ಪೂರ್ವನಿಯೋಜಿತ:
ಅಭಿವ್ಯಕ್ತಿ_stmt:
	  c_parser_gimple_statement (parser, seq);
	  ಆದರೆ (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	    c_parser_skip_until_ಸಿಕ್ಕಿತು (parser, CPP_SEMICOLON, ಖಾಲಿ);
	}
    }
  c_parser_consume_token (parser);

  /* Put stmts parsed in the current block.  */
  ಆದರೆ ((cfun->curr_properties & PROP_cfg)
      && !gimple_seq_ಖಾಲಿಗಳು_p (*seq))
    {
      ಆದರೆ (!parser.current_bb)
	c_parser_error (parser, "stmts without block");
      ಇಲ್ಲದಿದ್ದರೆ
	{
	  gimple_stmt_iterator gsi = gsi_ಆರಂಭ_bb (parser.current_bb);
	  gsi_ಸೇರಿಸು_seq_after_without_update (&gsi, *seq,
					       GSI_CONTINUE_LINKING);
	}
      *seq = ಖಾಲಿ;
    }

  ಹಿಂತಿರುಗಿ return_p;
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

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_gimple_statement (gimple_parser &parser, gimple_seq *seq)
{
  ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ lhs, rhs;
  gimple *ನಿಯೋಜಿಸು = ಖಾಲಿ;
  location_t loc;
  ವೃಕ್ಷ arg = NULL_ವೃಕ್ಷ;
  auto_vec<ವೃಕ್ಷ> vargs;

  lhs = c_parser_gimple_unary_ಅಭಿವ್ಯಕ್ತಿ (parser);
  loc = ಅಭಿವ್ಯಕ್ತಿ_LOCATION (lhs.ಮೌಲ್ಯ);
  rhs.ಗಣ_error ();

  /* GIMPLE call statement without LHS.  */
  ಆದರೆ (c_parser_ಮುಂದಿನ_token_is (parser, CPP_SEMICOLON)
      && ವೃಕ್ಷ_ಸಂಕೇತ (lhs.ಮೌಲ್ಯ) == CALL_ಅಭಿವ್ಯಕ್ತಿ)
    {
      gimple *call;
      call = gimple_build_call_from_ವೃಕ್ಷ (lhs.ಮೌಲ್ಯ, ಖಾಲಿ);
      gimple_seq_ಕೂಡಿಸು_stmt_without_update (seq, call);
      gimple_ಗಣ_location (call, loc);
      ಹಿಂತಿರುಗಿ;
    }

  /* All following cases are statements with LHS.  */
  ಆದರೆ (! c_parser_require (parser, CPP_EQ, "expected %<=%>"))
    ಹಿಂತಿರುಗಿ;

  /* Eat and ignore {v} right after the =, the has_volatile_ops is
     redundant and re-computed by the operand scanner.  */
  ಆದರೆ (c_parser_ಮುಂದಿನ_token_is (parser, CPP_OPEN_BRACE)
      && !(c_parser_peek_token (parser)->flags & PREV_WHITE)
      && c_parser_peek_2nd_token (parser)->type == CPP_NAME
      && !(c_parser_peek_2nd_token (parser)->flags & PREV_WHITE)
      && strcmp ("v", IDENTIFIER_ಸೂಚಕ
			(c_parser_peek_2nd_token (parser)->ಮೌಲ್ಯ)) == 0
      && c_parser_peek_nth_token (parser, 3)->type == CPP_CLOSE_BRACE
      && !(c_parser_peek_nth_token (parser, 3)->flags & PREV_WHITE))
    {
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }

  /* Cast expression.  */
  ಆದರೆ (c_parser_ಮುಂದಿನ_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_typename (c_parser_peek_2nd_token (parser)))
    {
      c_parser_consume_token (parser);
      ರಚನೆ c_type_name *type_name = c_parser_type_name (parser);
      c_parser_skip_until_ಸಿಕ್ಕಿತು (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      ಆದರೆ (type_name == ಖಾಲಿ)
	ಹಿಂತಿರುಗಿ;
      /* ???  The actual type used in the cast expression is ignored as
         in GIMPLE it is encoded by the type of the LHS.  */
      rhs = c_parser_gimple_postfix_ಅಭಿವ್ಯಕ್ತಿ (parser);
      ಆದರೆ (lhs.ಮೌಲ್ಯ != error_mark_ಗಂಟು
	  && rhs.ಮೌಲ್ಯ != error_mark_ಗಂಟು)
	{
	  ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_2 ಸಂಕೇತ_2 = NOP_ಅಭಿವ್ಯಕ್ತಿ;
	  ಆದರೆ (FLOAT_TYPE_P (ವೃಕ್ಷ_TYPE (lhs.ಮೌಲ್ಯ))
	      && ! FLOAT_TYPE_P (ವೃಕ್ಷ_TYPE (rhs.ಮೌಲ್ಯ)))
	    ಸಂಕೇತ_2 = FLOAT_ಅಭಿವ್ಯಕ್ತಿ;
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (! FLOAT_TYPE_P (ವೃಕ್ಷ_TYPE (lhs.ಮೌಲ್ಯ))
		   && FLOAT_TYPE_P (ವೃಕ್ಷ_TYPE (rhs.ಮೌಲ್ಯ)))
	    ಸಂಕೇತ_2 = FIX_TRUNC_ಅಭಿವ್ಯಕ್ತಿ;
	  ನಿಯೋಜಿಸು = gimple_build_ನಿಯೋಜಿಸು (lhs.ಮೌಲ್ಯ, ಸಂಕೇತ_2, rhs.ಮೌಲ್ಯ);
	  gimple_seq_ಕೂಡಿಸು_stmt_without_update (seq, ನಿಯೋಜಿಸು);
	  gimple_ಗಣ_location (ನಿಯೋಜಿಸು, loc);
	  ಹಿಂತಿರುಗಿ;
	}
    }

  /* Unary expression.  */
  ಆಯ್ಕೆ (c_parser_peek_token (parser)->type)
    {
    ಸ್ಥಿತಿ CPP_NAME:
      {
	ವೃಕ್ಷ id = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
	ಆದರೆ (strcmp (IDENTIFIER_ಸೂಚಕ (id), "__ABS") == 0
	    || strcmp (IDENTIFIER_ಸೂಚಕ (id), "__ABSU") == 0
	    || strcmp (IDENTIFIER_ಸೂಚಕ (id), "__MIN") == 0
	    || strcmp (IDENTIFIER_ಸೂಚಕ (id), "__MAX") == 0
	    || strcmp (IDENTIFIER_ಸೂಚಕ (id), "__BIT_INSERT") == 0
	    || strcmp (IDENTIFIER_ಸೂಚಕ (id), "__VEC_PERM") == 0)
	  ಹೋಗು build_unary_ಅಭಿವ್ಯಕ್ತಿ;
	ನಿಲ್ಲಿಸು;
      }
    ಸ್ಥಿತಿ CPP_KEYWORD:
      ಆದರೆ (c_parser_peek_token (parser)->keyword != RID_REALPART
	  && c_parser_peek_token (parser)->keyword != RID_IMAGPART)
	ನಿಲ್ಲಿಸು;
      /* Fallthru.  */
    ಸ್ಥಿತಿ CPP_AND:
    ಸ್ಥಿತಿ CPP_PLUS:
    ಸ್ಥಿತಿ CPP_MINUS:
    ಸ್ಥಿತಿ CPP_COMPL:
    ಸ್ಥಿತಿ CPP_NOT:
    ಸ್ಥಿತಿ CPP_MULT: /* pointer deref */
    build_unary_ಅಭಿವ್ಯಕ್ತಿ:
      rhs = c_parser_gimple_unary_ಅಭಿವ್ಯಕ್ತಿ (parser);
      ಆದರೆ (rhs.ಮೌಲ್ಯ != error_mark_ಗಂಟು)
	{
	  ನಿಯೋಜಿಸು = gimple_build_ನಿಯೋಜಿಸು (lhs.ಮೌಲ್ಯ, rhs.ಮೌಲ್ಯ);
	  gimple_ಗಣ_location (ನಿಯೋಜಿಸು, loc);
	  gimple_seq_ಕೂಡಿಸು_stmt_without_update (seq, ನಿಯೋಜಿಸು);
	}
      ಹಿಂತಿರುಗಿ;

    ಪೂರ್ವನಿಯೋಜಿತ:;
    }

  /* GIMPLE PHI statement.  */
  ಆದರೆ (c_parser_ಮುಂದಿನ_token_is_keyword (parser, RID_PHI))
    {
      c_parser_consume_token (parser);

      ಆದರೆ (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	ಹಿಂತಿರುಗಿ;

      ಆದರೆ (c_parser_ಮುಂದಿನ_token_is (parser, CPP_OPEN_PAREN))
	c_parser_consume_token (parser);

      ಆಗ (c_parser_ಮುಂದಿನ_token_is_not (parser, CPP_CLOSE_PAREN))
	{
	  ಆದರೆ (c_parser_ಮುಂದಿನ_token_is (parser, CPP_NAME)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      arg = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
	      c_parser_consume_token (parser);
	      ಆದರೆ (c_parser_ಮುಂದಿನ_token_is (parser, CPP_COLON))
		c_parser_consume_token (parser);
	      ಪೂರ್ಣಾಂಕ src_ಸೂಚ್ಯಂಕ = -1;
	      ಆದರೆ (!c_parser_gimple_parse_bb_spec (arg, &src_ಸೂಚ್ಯಂಕ))
		c_parser_error (parser, "invalid source block specification");
	      vargs.ಸುರಕ್ಷಿತ_ತಳ್ಳು (ಗಾತ್ರ_int (src_ಸೂಚ್ಯಂಕ));
	    }
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (c_parser_ಮುಂದಿನ_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  ಇಲ್ಲದಿದ್ದರೆ
	    {
	      arg = c_parser_gimple_unary_ಅಭಿವ್ಯಕ್ತಿ (parser).ಮೌಲ್ಯ;
	      vargs.ಸುರಕ್ಷಿತ_ತಳ್ಳು (arg);
	    }
	}

      c_parser_skip_until_ಸಿಕ್ಕಿತು (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");

      /* Build internal function for PHI.  */
      gcall *call_stmt = gimple_build_call_ಆಂತರಿಕ_vec (IFN_PHI, vargs);
      gimple_call_ಗಣ_lhs (call_stmt, lhs.ಮೌಲ್ಯ);
      gimple_ಗಣ_location (call_stmt, UNKNOWN_LOCATION);
      gimple_seq_ಕೂಡಿಸು_stmt_without_update (seq, call_stmt);
      ಹಿಂತಿರುಗಿ;
    }

  /* GIMPLE call with lhs.  */
  ಆದರೆ (c_parser_ಮುಂದಿನ_token_is (parser, CPP_DOT)
      || (c_parser_ಮುಂದಿನ_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN
	  && lookup_name (c_parser_peek_token (parser)->ಮೌಲ್ಯ)))
    {
      rhs = c_parser_gimple_unary_ಅಭಿವ್ಯಕ್ತಿ (parser);
      ಆದರೆ (rhs.ಮೌಲ್ಯ != error_mark_ಗಂಟು)
	{
	  gimple *call = gimple_build_call_from_ವೃಕ್ಷ (rhs.ಮೌಲ್ಯ, ಖಾಲಿ);
	  gimple_call_ಗಣ_lhs (call, lhs.ಮೌಲ್ಯ);
	  gimple_seq_ಕೂಡಿಸು_stmt_without_update (seq, call);
	  gimple_ಗಣ_location (call, loc);
	}
      ಹಿಂತಿರುಗಿ;
    }

  rhs = c_parser_gimple_ದ್ವಿಮಾನ_ಅಭಿವ್ಯಕ್ತಿ (parser, ವೃಕ್ಷ_TYPE (lhs.ಮೌಲ್ಯ));
  ಆದರೆ (lhs.ಮೌಲ್ಯ != error_mark_ಗಂಟು
      && rhs.ಮೌಲ್ಯ != error_mark_ಗಂಟು)
    {
      /* If we parsed an identifier and the next token  is a '?' then parse
	 a conditional expression.  */
      ಆದರೆ (SSA_VAR_P (rhs.ಮೌಲ್ಯ) && c_parser_ಮುಂದಿನ_token_is (parser, CPP_QUERY))
	{
	  ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ trueval, falseval;
	  c_parser_consume_token (parser);
	  trueval = c_parser_gimple_postfix_ಅಭಿವ್ಯಕ್ತಿ (parser);
	  falseval.ಗಣ_error ();
	  ಆದರೆ (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    falseval = c_parser_gimple_postfix_ಅಭಿವ್ಯಕ್ತಿ (parser);
	  ಆದರೆ (trueval.ಮೌಲ್ಯ == error_mark_ಗಂಟು
	      || falseval.ಮೌಲ್ಯ == error_mark_ಗಂಟು)
	    ಹಿಂತಿರುಗಿ;
	  rhs.ಮೌಲ್ಯ = build3_loc (loc,
				  ಸದಿಶ_TYPE_P (ವೃಕ್ಷ_TYPE (rhs.ಮೌಲ್ಯ))
				  ? VEC_COND_ಅಭಿವ್ಯಕ್ತಿ : COND_ಅಭಿವ್ಯಕ್ತಿ,
				  ವೃಕ್ಷ_TYPE (trueval.ಮೌಲ್ಯ),
				  rhs.ಮೌಲ್ಯ, trueval.ಮೌಲ್ಯ, falseval.ಮೌಲ್ಯ);
	}
      ಆದರೆ (get_gimple_rhs_class (ವೃಕ್ಷ_ಸಂಕೇತ (rhs.ಮೌಲ್ಯ)) == GIMPLE_INVALID_RHS)
	{
	  c_parser_error (parser, "unexpected RHS for assignment");
	  ಹಿಂತಿರುಗಿ;
	}
      ನಿಯೋಜಿಸು = gimple_build_ನಿಯೋಜಿಸು (lhs.ಮೌಲ್ಯ, rhs.ಮೌಲ್ಯ);
      gimple_seq_ಕೂಡಿಸು_stmt_without_update (seq, ನಿಯೋಜಿಸು);
      gimple_ಗಣ_location (ನಿಯೋಜಿಸು, loc);
    }
  ಹಿಂತಿರುಗಿ;
}

/* A mapping between an identifier to a tree code for binary operations. */
ಸ್ಥಿರ ಸ್ಥಿರಾಂಕ std::pair<ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *, ವೃಕ್ಷ_ಸಂಕೇತ_2> gimple_ದ್ವಿಮಾನ_identifier_ಸಂಕೇತ[] =
  {
    {"__MULT_HIGHPART", MULT_HIGHPART_ಅಭಿವ್ಯಕ್ತಿ},
    {"__UNLT", UNLT_ಅಭಿವ್ಯಕ್ತಿ},
    {"__UNLE", UNLE_ಅಭಿವ್ಯಕ್ತಿ},
    {"__UNGT", UNGT_ಅಭಿವ್ಯಕ್ತಿ},
    {"__UNGE", UNGE_ಅಭಿವ್ಯಕ್ತಿ},
    {"__UNEQ", UNEQ_ಅಭಿವ್ಯಕ್ತಿ},
    {"__UNORDERED", UNORDERED_ಅಭಿವ್ಯಕ್ತಿ},
    {"__ORDERED", ORDERED_ಅಭಿವ್ಯಕ್ತಿ},
    {"__LTGT", LTGT_ಅಭಿವ್ಯಕ್ತಿ},
    {"__FLOOR_DIV", FLOOR_DIV_ಅಭಿವ್ಯಕ್ತಿ},
    {"__ROUND_DIV", ಸುತ್ತು_DIV_ಅಭಿವ್ಯಕ್ತಿ},
    {"__EXACT_DIV", EXACT_DIV_ಅಭಿವ್ಯಕ್ತಿ},
    {"__CEIL_DIV", CEIL_DIV_ಅಭಿವ್ಯಕ್ತಿ},
    {"__FLOOR_MOD", FLOOR_MOD_ಅಭಿವ್ಯಕ್ತಿ},
    {"__ROUND_MOD", ಸುತ್ತು_MOD_ಅಭಿವ್ಯಕ್ತಿ},
    {"__CEIL_MOD", CEIL_MOD_ಅಭಿವ್ಯಕ್ತಿ},
    {"__ROTATE_LEFT", LROTATE_ಅಭಿವ್ಯಕ್ತಿ},
    {"__ROTATE_RIGHT", RROTATE_ಅಭಿವ್ಯಕ್ತಿ},
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

ಸ್ಥಿರ c_ಅಭಿವ್ಯಕ್ತಿ
c_parser_gimple_ದ್ವಿಮಾನ_ಅಭಿವ್ಯಕ್ತಿ (gimple_parser &parser, ವೃಕ್ಷ ret_type)
{
  /* Location of the binary operator.  */
  ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ ret, lhs, rhs;
  ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_2 ಸಂಕೇತ_2 = ERROR_MARK;
  ret.ಗಣ_error ();
  lhs = c_parser_gimple_postfix_ಅಭಿವ್ಯಕ್ತಿ (parser, ret_type);
  ಆದರೆ (c_parser_error (parser))
    ಹಿಂತಿರುಗಿ ret;
  ಆಯ್ಕೆ (c_parser_peek_token (parser)->type)
    {
    ಸ್ಥಿತಿ CPP_MULT:
      ಸಂಕೇತ_2 = MULT_ಅಭಿವ್ಯಕ್ತಿ;
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ CPP_DIV:
      ಸಂಕೇತ_2 = TRUNC_DIV_ಅಭಿವ್ಯಕ್ತಿ;
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ CPP_MOD:
      ಸಂಕೇತ_2 = TRUNC_MOD_ಅಭಿವ್ಯಕ್ತಿ;
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ CPP_PLUS:
      ಆದರೆ (ಸೂಚಕ_TYPE_P (ವೃಕ್ಷ_TYPE (lhs.ಮೌಲ್ಯ)))
	ಸಂಕೇತ_2 = ಸೂಚಕ_PLUS_ಅಭಿವ್ಯಕ್ತಿ;
      ಇಲ್ಲದಿದ್ದರೆ
	ಸಂಕೇತ_2 = PLUS_ಅಭಿವ್ಯಕ್ತಿ;
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ CPP_MINUS:
      ಆದರೆ (ಸೂಚಕ_TYPE_P (ವೃಕ್ಷ_TYPE (lhs.ಮೌಲ್ಯ)))
	ಸಂಕೇತ_2 = ಸೂಚಕ_DIFF_ಅಭಿವ್ಯಕ್ತಿ;
      ಇಲ್ಲದಿದ್ದರೆ
	ಸಂಕೇತ_2 = MINUS_ಅಭಿವ್ಯಕ್ತಿ;
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ CPP_LSHIFT:
      ಸಂಕೇತ_2 = LSHIFT_ಅಭಿವ್ಯಕ್ತಿ;
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ CPP_RSHIFT:
      ಸಂಕೇತ_2 = RSHIFT_ಅಭಿವ್ಯಕ್ತಿ;
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ CPP_LESS:
      ಸಂಕೇತ_2 = LT_ಅಭಿವ್ಯಕ್ತಿ;
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ CPP_GREATER:
      ಸಂಕೇತ_2 = GT_ಅಭಿವ್ಯಕ್ತಿ;
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ CPP_LESS_EQ:
      ಸಂಕೇತ_2 = LE_ಅಭಿವ್ಯಕ್ತಿ;
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ CPP_GREATER_EQ:
      ಸಂಕೇತ_2 = GE_ಅಭಿವ್ಯಕ್ತಿ;
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ CPP_EQ_EQ:
      ಸಂಕೇತ_2 = EQ_ಅಭಿವ್ಯಕ್ತಿ;
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ CPP_NOT_EQ:
      ಸಂಕೇತ_2 = NE_ಅಭಿವ್ಯಕ್ತಿ;
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ CPP_AND:
      ಸಂಕೇತ_2 = ಬಿಟ್_AND_ಅಭಿವ್ಯಕ್ತಿ;
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ CPP_XOR:
      ಸಂಕೇತ_2 = ಬಿಟ್_XOR_ಅಭಿವ್ಯಕ್ತಿ;
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ CPP_OR:
      ಸಂಕೇತ_2 = ಬಿಟ್_IOR_ಅಭಿವ್ಯಕ್ತಿ;
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ CPP_AND_AND:
      c_parser_error (parser, "%<&&%> not valid in GIMPLE");
      ಹಿಂತಿರುಗಿ ret;
    ಸ್ಥಿತಿ CPP_OR_OR:
      c_parser_error (parser, "%<||%> not valid in GIMPLE");
      ಹಿಂತಿರುಗಿ ret;
    ಸ್ಥಿತಿ CPP_NAME:
      {
	ವೃಕ್ಷ id = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
	ಗಾಗಿ (ಸ್ವಯಂಚಾಲಿತ &p : gimple_ದ್ವಿಮಾನ_identifier_ಸಂಕೇತ)
	  {
	    ಆದರೆ (strcmp (IDENTIFIER_ಸೂಚಕ (id), p.ಮೊದಲ) == 0)
	      {
		ಸಂಕೇತ_2 = p.ಎರಡನೇ;
		ನಿಲ್ಲಿಸು;
	      }
	  }
	ಆದರೆ (ಸಂಕೇತ_2 != ERROR_MARK)
	  ನಿಲ್ಲಿಸು;
      }
      /* Fallthru.  */
    ಪೂರ್ವನಿಯೋಜಿತ:
      /* Not a binary expression.  */
      ಹಿಂತಿರುಗಿ lhs;
    }
  location_t ret_loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  rhs = c_parser_gimple_postfix_ಅಭಿವ್ಯಕ್ತಿ (parser);
  ಆದರೆ (lhs.ಮೌಲ್ಯ != error_mark_ಗಂಟು && rhs.ಮೌಲ್ಯ != error_mark_ಗಂಟು)
    ret.ಮೌಲ್ಯ = build2_loc (ret_loc, ಸಂಕೇತ_2, ret_type, lhs.ಮೌಲ್ಯ, rhs.ಮೌಲ್ಯ);
  ಹಿಂತಿರುಗಿ ret;
}

/* Parse a gimple parentized binary expression.  */

ಸ್ಥಿರ c_ಅಭಿವ್ಯಕ್ತಿ
c_parser_gimple_parentized_ದ್ವಿಮಾನ_ಅಭಿವ್ಯಕ್ತಿ (gimple_parser &parser,
					      location_t op_loc,
					      ವೃಕ್ಷ_ಸಂಕೇತ_2 ಸಂಕೇತ_2)
{
  ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ ret;
  ret.ಗಣ_error ();

  c_parser_consume_token (parser);
  ಆದರೆ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    ಹಿಂತಿರುಗಿ ret;
  c_ಅಭಿವ್ಯಕ್ತಿ op1 = c_parser_gimple_postfix_ಅಭಿವ್ಯಕ್ತಿ (parser);
  ಆದರೆ (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    ಹಿಂತಿರುಗಿ ret;
  c_ಅಭಿವ್ಯಕ್ತಿ op2 = c_parser_gimple_postfix_ಅಭಿವ್ಯಕ್ತಿ (parser);
  ಆದರೆ (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    ಹಿಂತಿರುಗಿ ret;

  ಆದರೆ (op1.ಮೌಲ್ಯ != error_mark_ಗಂಟು && op2.ಮೌಲ್ಯ != error_mark_ಗಂಟು)
    ret.ಮೌಲ್ಯ = build2_loc (op_loc,
			    ಸಂಕೇತ_2, ವೃಕ್ಷ_TYPE (op1.ಮೌಲ್ಯ), op1.ಮೌಲ್ಯ, op2.ಮೌಲ್ಯ);
  ಹಿಂತಿರುಗಿ ret;
}

/* Parse a gimple parentized binary expression.  */

ಸ್ಥಿರ c_ಅಭಿವ್ಯಕ್ತಿ
c_parser_gimple_parentized_ternary_ಅಭಿವ್ಯಕ್ತಿ (gimple_parser &parser,
					       location_t op_loc,
					       ವೃಕ್ಷ_ಸಂಕೇತ_2 ಸಂಕೇತ_2)
{
  ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ ret;
  ret.ಗಣ_error ();

  c_parser_consume_token (parser);
  ಆದರೆ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    ಹಿಂತಿರುಗಿ ret;
  c_ಅಭಿವ್ಯಕ್ತಿ op1 = c_parser_gimple_postfix_ಅಭಿವ್ಯಕ್ತಿ (parser);
  ಆದರೆ (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    ಹಿಂತಿರುಗಿ ret;
  c_ಅಭಿವ್ಯಕ್ತಿ op2 = c_parser_gimple_postfix_ಅಭಿವ್ಯಕ್ತಿ (parser);
  ಆದರೆ (!c_parser_require (parser, CPP_COMMA, "expected %<)%>"))
    ಹಿಂತಿರುಗಿ ret;
  c_ಅಭಿವ್ಯಕ್ತಿ op3 = c_parser_gimple_postfix_ಅಭಿವ್ಯಕ್ತಿ (parser);
  ಆದರೆ (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    ಹಿಂತಿರುಗಿ ret;

  ಆದರೆ (op1.ಮೌಲ್ಯ != error_mark_ಗಂಟು
      && op2.ಮೌಲ್ಯ != error_mark_ಗಂಟು
      && op3.ಮೌಲ್ಯ != error_mark_ಗಂಟು)
    ret.ಮೌಲ್ಯ = build3_loc (op_loc,
			    ಸಂಕೇತ_2, ವೃಕ್ಷ_TYPE (op1.ಮೌಲ್ಯ),
			    op1.ಮೌಲ್ಯ, op2.ಮೌಲ್ಯ, op3.ಮೌಲ್ಯ);
  ಹಿಂತಿರುಗಿ ret;
}

/* Parse gimple unary expression.

   gimple-unary-expression:
     gimple-postfix-expression
     unary-operator gimple-postfix-expression

   unary-operator: one of
     & * + - ~ abs_expr
*/

ಸ್ಥಿರ c_ಅಭಿವ್ಯಕ್ತಿ
c_parser_gimple_unary_ಅಭಿವ್ಯಕ್ತಿ (gimple_parser &parser)
{
  ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ ret, op;
  location_t op_loc = c_parser_peek_token (parser)->location;
  location_t ಮುಕ್ತಾಯ;
  ret.ಗಣ_error ();
  ಆಯ್ಕೆ (c_parser_peek_token (parser)->type)
    {
    ಸ್ಥಿತಿ CPP_AND:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_ಅಭಿವ್ಯಕ್ತಿ (parser);
      mark_exp_read (op.ಮೌಲ್ಯ);
      ಹಿಂತಿರುಗಿ gimple_parser_build_unary_op (op_loc, ADDR_ಅಭಿವ್ಯಕ್ತಿ, op);
    ಸ್ಥಿತಿ CPP_MULT:
      {
	c_parser_consume_token (parser);
	op = c_parser_gimple_postfix_ಅಭಿವ್ಯಕ್ತಿ (parser);
	ಆದರೆ (op.ಮೌಲ್ಯ == error_mark_ಗಂಟು)
	  ಹಿಂತಿರುಗಿ ret;
	ಆದರೆ (! ಸೂಚಕ_TYPE_P (ವೃಕ್ಷ_TYPE (op.ಮೌಲ್ಯ)))
	  {
	    error_at (op_loc, "expected pointer as argument of unary %<*%>");
	    ಹಿಂತಿರುಗಿ ret;
	  }
	ಮುಕ್ತಾಯ = op.get_ಮುಕ್ತಾಯ ();
	location_t combined_loc = make_location (op_loc, op_loc, ಮುಕ್ತಾಯ);
	ret.ಮೌಲ್ಯ = build_simple_mem_ref_loc (combined_loc, op.ಮೌಲ್ಯ);
	ವೃಕ್ಷ_SIDE_EFFECTS (ret.ಮೌಲ್ಯ)
	  = ವೃಕ್ಷ_THIS_VOLATILE (ret.ಮೌಲ್ಯ)
	  = TYPE_VOLATILE (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (op.ಮೌಲ್ಯ)));
	ret.src_range.m_ಆರಂಭ = op_loc;
	ret.src_range.m_ಮುಕ್ತಾಯ = ಮುಕ್ತಾಯ;
	ಹಿಂತಿರುಗಿ ret;
      }
    ಸ್ಥಿತಿ CPP_PLUS:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_ಅಭಿವ್ಯಕ್ತಿ (parser);
      ಹಿಂತಿರುಗಿ gimple_parser_build_unary_op (op_loc, CONVERT_ಅಭಿವ್ಯಕ್ತಿ, op);
    ಸ್ಥಿತಿ CPP_MINUS:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_ಅಭಿವ್ಯಕ್ತಿ (parser);
      ಹಿಂತಿರುಗಿ gimple_parser_build_unary_op (op_loc, NEGATE_ಅಭಿವ್ಯಕ್ತಿ, op);
    ಸ್ಥಿತಿ CPP_COMPL:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_ಅಭಿವ್ಯಕ್ತಿ (parser);
      ಹಿಂತಿರುಗಿ gimple_parser_build_unary_op (op_loc, ಬಿಟ್_NOT_ಅಭಿವ್ಯಕ್ತಿ, op);
    ಸ್ಥಿತಿ CPP_NOT:
      c_parser_error (parser, "%<!%> not valid in GIMPLE");
      ಹಿಂತಿರುಗಿ ret;
    ಸ್ಥಿತಿ CPP_KEYWORD:
      ಆಯ್ಕೆ (c_parser_peek_token (parser)->keyword)
	{
	ಸ್ಥಿತಿ RID_REALPART:
	  c_parser_consume_token (parser);
	  op = c_parser_gimple_postfix_ಅಭಿವ್ಯಕ್ತಿ (parser);
	  ಹಿಂತಿರುಗಿ gimple_parser_build_unary_op (op_loc, REALPART_ಅಭಿವ್ಯಕ್ತಿ, op);
	ಸ್ಥಿತಿ RID_IMAGPART:
	  c_parser_consume_token (parser);
	  op = c_parser_gimple_postfix_ಅಭಿವ್ಯಕ್ತಿ (parser);
	  ಹಿಂತಿರುಗಿ gimple_parser_build_unary_op (op_loc, IMAGPART_ಅಭಿವ್ಯಕ್ತಿ, op);
	ಪೂರ್ವನಿಯೋಜಿತ:
	  ಹಿಂತಿರುಗಿ c_parser_gimple_postfix_ಅಭಿವ್ಯಕ್ತಿ (parser);
	}
    ಸ್ಥಿತಿ CPP_NAME:
	{
	  ವೃಕ್ಷ id = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
	  ಆದರೆ (strcmp (IDENTIFIER_ಸೂಚಕ (id), "__ABS") == 0)
	    {
	      c_parser_consume_token (parser);
	      op = c_parser_gimple_postfix_ಅಭಿವ್ಯಕ್ತಿ (parser);
	      ಹಿಂತಿರುಗಿ gimple_parser_build_unary_op (op_loc, ABS_ಅಭಿವ್ಯಕ್ತಿ, op);
	    }
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strcmp (IDENTIFIER_ಸೂಚಕ (id), "__ABSU") == 0)
	    {
	      c_parser_consume_token (parser);
	      op = c_parser_gimple_postfix_ಅಭಿವ್ಯಕ್ತಿ (parser);
	      ಹಿಂತಿರುಗಿ gimple_parser_build_unary_op (op_loc, ABSU_ಅಭಿವ್ಯಕ್ತಿ, op);
	    }
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strcmp (IDENTIFIER_ಸೂಚಕ (id), "__MIN") == 0)
	    ಹಿಂತಿರುಗಿ c_parser_gimple_parentized_ದ್ವಿಮಾನ_ಅಭಿವ್ಯಕ್ತಿ (parser,
								 op_loc,
								 MIN_ಅಭಿವ್ಯಕ್ತಿ);
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strcmp (IDENTIFIER_ಸೂಚಕ (id), "__MAX") == 0)
	    ಹಿಂತಿರುಗಿ c_parser_gimple_parentized_ದ್ವಿಮಾನ_ಅಭಿವ್ಯಕ್ತಿ (parser,
								 op_loc,
								 MAX_ಅಭಿವ್ಯಕ್ತಿ);
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strcmp (IDENTIFIER_ಸೂಚಕ (id), "__VEC_PERM") == 0)
	    ಹಿಂತಿರುಗಿ c_parser_gimple_parentized_ternary_ಅಭಿವ್ಯಕ್ತಿ
			(parser, op_loc, VEC_PERM_ಅಭಿವ್ಯಕ್ತಿ);
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strcmp (IDENTIFIER_ಸೂಚಕ (id), "__BIT_INSERT") == 0)
	    {
	      /* __BIT_INSERT '(' postfix-expression, postfix-expression,
			          integer ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      ಆದರೆ (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_ಅಭಿವ್ಯಕ್ತಿ op0 = c_parser_gimple_postfix_ಅಭಿವ್ಯಕ್ತಿ (parser);
		  c_parser_skip_until_ಸಿಕ್ಕಿತು (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_ಅಭಿವ್ಯಕ್ತಿ op1 = c_parser_gimple_postfix_ಅಭಿವ್ಯಕ್ತಿ (parser);
		  c_parser_skip_until_ಸಿಕ್ಕಿತು (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_ಅಭಿವ್ಯಕ್ತಿ op2 = c_parser_gimple_postfix_ಅಭಿವ್ಯಕ್ತಿ (parser);
		  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (op2.ಮೌಲ್ಯ) != INTEGER_CST
		      || !int_ಹೊಂದುತ್ತದೆ_type_p (op2.ಮೌಲ್ಯ, bitsizetype))
		    c_parser_error (parser, "expected constant offset");
		  c_parser_skip_until_ಸಿಕ್ಕಿತು (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  ಆದರೆ (op0.ಮೌಲ್ಯ != error_mark_ಗಂಟು
		      && op1.ಮೌಲ್ಯ != error_mark_ಗಂಟು
		      && ವೃಕ್ಷ_ಸಂಕೇತ (op2.ಮೌಲ್ಯ) == INTEGER_CST)
		    ret.ಮೌಲ್ಯ = build3_loc (loc, ಬಿಟ್_ಸೇರಿಸು_ಅಭಿವ್ಯಕ್ತಿ,
					    ವೃಕ್ಷ_TYPE (op0.ಮೌಲ್ಯ),
					    op0.ಮೌಲ್ಯ, op1.ಮೌಲ್ಯ,
					    fold_convert (bitsizetype,
							  op2.ಮೌಲ್ಯ));
		}
	      ಹಿಂತಿರುಗಿ ret;
	    }
	  ಇಲ್ಲದಿದ್ದರೆ
	    ಹಿಂತಿರುಗಿ c_parser_gimple_postfix_ಅಭಿವ್ಯಕ್ತಿ (parser);
	}
    ಪೂರ್ವನಿಯೋಜಿತ:
      ಹಿಂತಿರುಗಿ c_parser_gimple_postfix_ಅಭಿವ್ಯಕ್ತಿ (parser);
    }
}

/* Decompose ID into base name (ID until ver_offset) and VERSION.  Return
   true if ID matches a SSA name.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
c_parser_parse_ssa_name_id (ವೃಕ್ಷ id, ಚಿಹ್ನೆರಹಿತ *ಆವೃತ್ತಿ, ಚಿಹ್ನೆರಹಿತ *ver_ಸ್ಥಾನಾಂತರ)
{
  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *token = IDENTIFIER_ಸೂಚಕ (id);
  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *var_ಆವೃತ್ತಿ = strrchr (token, '_');
  ಆದರೆ (! var_ಆವೃತ್ತಿ)
    ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;

  *ver_ಸ್ಥಾನಾಂತರ = var_ಆವೃತ್ತಿ - token;
  ಗಾಗಿ (ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *p = var_ಆವೃತ್ತಿ + 1; *p; ++p)
    ಆದರೆ (! ISDIGIT (*p))
      ಹಿಂತಿರುಗಿ ಸುಳ್ಳು;
  *ಆವೃತ್ತಿ = atoi (var_ಆವೃತ್ತಿ + 1);
  ಹಿಂತಿರುಗಿ *ಆವೃತ್ತಿ > 0;
}

/* Get at the actual SSA name ID with VERSION starting at VER_OFFSET.
   TYPE is the type if the SSA name is being declared.  */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_parse_ssa_name (gimple_parser &parser,
			 ವೃಕ್ಷ id, ವೃಕ್ಷ type, ಚಿಹ್ನೆರಹಿತ ಆವೃತ್ತಿ,
			 ಚಿಹ್ನೆರಹಿತ ver_ಸ್ಥಾನಾಂತರ)
{
  ವೃಕ್ಷ name = NULL_ವೃಕ್ಷ;
  ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *token = IDENTIFIER_ಸೂಚಕ (id);

  ಆದರೆ (ver_ಸ್ಥಾನಾಂತರ == 0)
    {
      /* Anonymous unnamed SSA name.  */
      ಆದರೆ (ಆವೃತ್ತಿ < ಅಂಕೆ_ssa_ಹೆಸರುಗಳು)
	name = ssa_name (ಆವೃತ್ತಿ);
      ಆದರೆ (! name)
	{
	  ಆದರೆ (! type)
	    {
	      c_parser_error (parser, "SSA name undeclared");
	      ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
	    }
	  name = make_ssa_name_fn (cfun, type, ಖಾಲಿ, ಆವೃತ್ತಿ);
	}
    }
  ಇಲ್ಲದಿದ್ದರೆ
    {
      ಆದರೆ (ಆವೃತ್ತಿ < ಅಂಕೆ_ssa_ಹೆಸರುಗಳು)
	name = ssa_name (ಆವೃತ್ತಿ);
      ಆದರೆ (! name)
	{
	  /* Separate var name from version.  */
	  ಅಕ್ಷರ *var_name = XNEWVEC (ಅಕ್ಷರ, ver_ಸ್ಥಾನಾಂತರ + 1);
	  ಸ್ಮರಣೆ_ನಕಲು (var_name, token, ver_ಸ್ಥಾನಾಂತರ);
	  var_name[ver_ಸ್ಥಾನಾಂತರ] = '\0';
	  /* lookup for parent decl.  */
	  id = get_identifier (var_name);
	  ವೃಕ್ಷ ಪೋಷಕ = lookup_name (id);
	  XDELETEVEC (var_name);
	  ಆದರೆ (! ಪೋಷಕ || ಪೋಷಕ == error_mark_ಗಂಟು)
	    {
	      c_parser_error (parser, "base variable or SSA name undeclared");
	      ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
	    }
	  ಆದರೆ (!(VAR_P (ಪೋಷಕ)
		|| ವೃಕ್ಷ_ಸಂಕೇತ (ಪೋಷಕ) == PARM_DECL
		|| ವೃಕ್ಷ_ಸಂಕೇತ (ಪೋಷಕ) == ಫಲಿತಾಂಶ_DECL))
	    {
	      error ("invalid base %qE for SSA name", ಪೋಷಕ);
	      ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
	    }
	  name = make_ssa_name_fn (cfun, ಪೋಷಕ,
				   gimple_build_nop (), ಆವೃತ್ತಿ);
	}
    }

  ಹಿಂತಿರುಗಿ name;
}

/* Parse a gimple call to an internal function.

   gimple-call-internal:
     . identifier ( gimple-argument-expression-list[opt] )  */

ಸ್ಥಿರ ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ
c_parser_gimple_call_ಆಂತರಿಕ (gimple_parser &parser)
{
  ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ;
  ಅಭಿವ್ಯಕ್ತಿ.ಗಣ_error ();

  gcc_assert (c_parser_ಮುಂದಿನ_token_is (parser, CPP_DOT));
  c_parser_consume_token (parser);
  location_t loc = c_parser_peek_token (parser)->location;
  ಆದರೆ (!c_parser_ಮುಂದಿನ_token_is (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_ಬಗೆ != C_ID_ID)
    {
      c_parser_error (parser, "expecting internal function name");
      ಹಿಂತಿರುಗಿ ಅಭಿವ್ಯಕ್ತಿ;
    }
  ವೃಕ್ಷ id = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
  ಆಂತರಿಕ_fn ifn = lookup_ಆಂತರಿಕ_fn (IDENTIFIER_ಸೂಚಕ (id));
  c_parser_consume_token (parser);
  ಆದರೆ (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    {
      auto_vec<ವೃಕ್ಷ> exprlist;
      ಆದರೆ (!c_parser_ಮುಂದಿನ_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_gimple_ಅಭಿವ್ಯಕ್ತಿ_list (parser, &exprlist);
      c_parser_skip_until_ಸಿಕ್ಕಿತು (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      ಆದರೆ (ifn == IFN_ಕೊನೆಯ)
	error_at (loc, "unknown internal function %qE", id);
      ಇಲ್ಲದಿದ್ದರೆ
	{
	  ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = build_call_ಅಭಿವ್ಯಕ್ತಿ_ಆಂತರಿಕ_loc_array
	    (loc, ifn, void_type_ಗಂಟು, exprlist.ಉದ್ದಳತೆ (),
	     exprlist.ವಿಳಾಸ ());
	  ಅಭಿವ್ಯಕ್ತಿ.original_ಸಂಕೇತ = ERROR_MARK;
	  ಅಭಿವ್ಯಕ್ತಿ.original_type = ಖಾಲಿ;
	  ಅಭಿವ್ಯಕ್ತಿ.m_decimal = 0;
	}
    }
  ಹಿಂತಿರುಗಿ ಅಭಿವ್ಯಕ್ತಿ;
}

/* Parse '<' type [',' alignment] '>' and return a type on success
   and NULL_TREE on error.  */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_gimple_typespec (gimple_parser &parser)
{
  ರಚನೆ c_type_name *type_name = ಖಾಲಿ;
  ವೃಕ್ಷ alignment = NULL_ವೃಕ್ಷ;
  ಆದರೆ (c_parser_require (parser, CPP_LESS, "expected %<<%>"))
    {
      type_name = c_parser_type_name (parser);
      /* Optional alignment.  */
      ಆದರೆ (c_parser_ಮುಂದಿನ_token_is (parser, CPP_COMMA))
	{
	  c_parser_consume_token (parser);
	  alignment
	      = c_parser_gimple_postfix_ಅಭಿವ್ಯಕ್ತಿ (parser).ಮೌಲ್ಯ;
	}
      c_parser_skip_until_ಸಿಕ್ಕಿತು (parser,
				 CPP_GREATER, "expected %<>%>");
    }
  ಆದರೆ (!type_name)
    ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;
  ವೃಕ್ಷ tem;
  ವೃಕ್ಷ type = groktypename (type_name, &tem, ಖಾಲಿ);
  ಆದರೆ (alignment)
    type = build_aligned_type (type, ವೃಕ್ಷ_ಗಮ್ಯ_uhwi (alignment));
  ಹಿಂತಿರುಗಿ type;
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

ಸ್ಥಿರ ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ
c_parser_gimple_postfix_ಅಭಿವ್ಯಕ್ತಿ (gimple_parser &parser, ವೃಕ್ಷ ret_type)
{
  location_t loc = c_parser_peek_token (parser)->location;
  ಮೂಲ_range tok_range = c_parser_peek_token (parser)->get_range ();
  ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ;
  ಅಭಿವ್ಯಕ್ತಿ.ಗಣ_error ();
  ಆಯ್ಕೆ (c_parser_peek_token (parser)->type)
    {
    ಸ್ಥಿತಿ CPP_ಸಂಖ್ಯೆ:
      ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
      ಗಣ_c_ಅಭಿವ್ಯಕ್ತಿ_ಮೂಲ_range (&ಅಭಿವ್ಯಕ್ತಿ, tok_range);
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ CPP_CHAR:
    ಸ್ಥಿತಿ CPP_CHAR16:
    ಸ್ಥಿತಿ CPP_CHAR32:
    ಸ್ಥಿತಿ CPP_UTF8CHAR:
    ಸ್ಥಿತಿ CPP_WCHAR:
      ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
      ಗಣ_c_ಅಭಿವ್ಯಕ್ತಿ_ಮೂಲ_range (&ಅಭಿವ್ಯಕ್ತಿ, tok_range);
      c_parser_consume_token (parser);
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ CPP_STRING:
    ಸ್ಥಿತಿ CPP_STRING16:
    ಸ್ಥಿತಿ CPP_STRING32:
    ಸ್ಥಿತಿ CPP_WSTRING:
    ಸ್ಥಿತಿ CPP_UTF8STRING:
      ಅಭಿವ್ಯಕ್ತಿ = c_parser_string_literal (parser, ಸುಳ್ಳು, ನಿಜ);
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ CPP_DOT:
      ಅಭಿವ್ಯಕ್ತಿ = c_parser_gimple_call_ಆಂತರಿಕ (parser);
      ನಿಲ್ಲಿಸು;
    ಸ್ಥಿತಿ CPP_NAME:
      ಆದರೆ (c_parser_peek_token (parser)->id_ಬಗೆ == C_ID_ID)
	{
	  ವೃಕ್ಷ id = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
	  ಆದರೆ (strcmp (IDENTIFIER_ಸೂಚಕ (id), "__MEM") == 0)
	    {
	      /* __MEM '<' type-name [ ',' number ] '>'
	               '(' [ '(' type-name ')' ] unary-expression
			   [ '+' number ]
			   [ ',' number ]
			   [ ',' number ':' number ] ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      ವೃಕ್ಷ type = c_parser_gimple_typespec (parser);
	      ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ ptr, alias_off, ಹೆಜ್ಜೆ, ಸೂಚ್ಯಂಕ, index2;
	      ptr.ಮೌಲ್ಯ = error_mark_ಗಂಟು;
	      alias_off.ಮೌಲ್ಯ = NULL_ವೃಕ್ಷ;
	      ಹೆಜ್ಜೆ.ಮೌಲ್ಯ = NULL_ವೃಕ್ಷ;
	      ಸೂಚ್ಯಂಕ.ಮೌಲ್ಯ = NULL_ವೃಕ್ಷ;
	      index2.ಮೌಲ್ಯ = NULL_ವೃಕ್ಷ;
	      ಚಿಹ್ನೆರಹಿತ ಗಿಡ್ಡ clique = 0;
	      ಚಿಹ್ನೆರಹಿತ ಗಿಡ್ಡ ತಳ = 0;
	      ತಾರ್ಕಿಕ ಹಿಮ್ಮುಖ_ಕ್ರಮ = ಸುಳ್ಳು;
	      ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ ro;
	      ಆದರೆ (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  ವೃಕ್ಷ alias_type = NULL_ವೃಕ್ಷ;
		  /* Optional alias-type cast.  */
		  ಆದರೆ (c_parser_ಮುಂದಿನ_token_is (parser, CPP_OPEN_PAREN))
		    {
		      c_parser_consume_token (parser);
		      ರಚನೆ c_type_name *alias_type_name
			= c_parser_type_name (parser);
		      c_parser_skip_until_ಸಿಕ್ಕಿತು (parser, CPP_CLOSE_PAREN,
						 "expected %<)%>");
		      ಆದರೆ (alias_type_name)
			{
			  ವೃಕ್ಷ tem;
			  alias_type = groktypename (alias_type_name,
						     &tem, ಖಾಲಿ);
			}
		    }
		  ptr = c_parser_gimple_unary_ಅಭಿವ್ಯಕ್ತಿ (parser);
		  ಆದರೆ (ptr.ಮೌಲ್ಯ == error_mark_ಗಂಟು
		      || ! ಸೂಚಕ_TYPE_P (ವೃಕ್ಷ_TYPE (ptr.ಮೌಲ್ಯ)))
		    {
		      ಆದರೆ (ptr.ಮೌಲ್ಯ != error_mark_ಗಂಟು)
			error_at (ptr.get_ಆರಂಭ (),
				  "invalid type of %<__MEM%> operand");
		      c_parser_skip_until_ಸಿಕ್ಕಿತು (parser, CPP_CLOSE_PAREN,
						 "expected %<)%>");
		      ಹಿಂತಿರುಗಿ ಅಭಿವ್ಯಕ್ತಿ;
		    }
		  ಆದರೆ (! alias_type)
		    alias_type = ವೃಕ್ಷ_TYPE (ptr.ಮೌಲ್ಯ);
		  /* Optional constant offset.  */
		  ಆದರೆ (c_parser_ಮುಂದಿನ_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      alias_off = c_parser_gimple_postfix_ಅಭಿವ್ಯಕ್ತಿ (parser);
		    }
		  ಆದರೆ (c_parser_ಮುಂದಿನ_token_is (parser, CPP_MULT))
		    {
		      std::ಅದಲುಬದಲು (ಸೂಚ್ಯಂಕ, alias_off);
		      c_parser_consume_token (parser);
		      ಹೆಜ್ಜೆ = c_parser_gimple_postfix_ಅಭಿವ್ಯಕ್ತಿ (parser);
		    }
		  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (c_parser_ಮುಂದಿನ_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      ಸೂಚ್ಯಂಕ = c_parser_gimple_postfix_ಅಭಿವ್ಯಕ್ತಿ (parser);
		      ಆದರೆ (c_parser_ಮುಂದಿನ_token_is (parser, CPP_MULT))
			{
			  c_parser_consume_token (parser);
			  ಹೆಜ್ಜೆ = c_parser_gimple_postfix_ಅಭಿವ್ಯಕ್ತಿ (parser);
			}
		      ಇಲ್ಲದಿದ್ದರೆ
			std::ಅದಲುಬದಲು (ಸೂಚ್ಯಂಕ, index2);
		    }
		  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (alias_off.ಮೌಲ್ಯ
			   && ವೃಕ್ಷ_ಸಂಕೇತ (alias_off.ಮೌಲ್ಯ) != INTEGER_CST)
		    std::ಅದಲುಬದಲು (alias_off, index2);
		  ಆದರೆ (c_parser_ಮುಂದಿನ_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      index2 = c_parser_gimple_postfix_ಅಭಿವ್ಯಕ್ತಿ (parser);
		    }
		  ಆದರೆ (alias_off.ಮೌಲ್ಯ)
		    {
		      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (alias_off.ಮೌಲ್ಯ) != INTEGER_CST)
			error_at (alias_off.get_ಆರಂಭ (),
				  "expected constant offset for %<__MEM%> "
				  "operand");
		      alias_off.ಮೌಲ್ಯ = fold_convert (alias_type,
						      alias_off.ಮೌಲ್ಯ);
		    }
		  ಇಲ್ಲದಿದ್ದರೆ
		    alias_off.ಮೌಲ್ಯ = build_int_cst (alias_type, 0);
		  ಆದರೆ (ಹೆಜ್ಜೆ.ಮೌಲ್ಯ)
		    {
		      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಹೆಜ್ಜೆ.ಮೌಲ್ಯ) != INTEGER_CST)
			error_at (ಹೆಜ್ಜೆ.get_ಆರಂಭ (),
				  "expected constant step for %<__MEM%> "
				  "operand");
		    }
		  ಆದರೆ (c_parser_ಮುಂದಿನ_token_is (parser, CPP_COMMA))
		    {
		      ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ cl, ba;
		      ತಾರ್ಕಿಕ has_clb = ನಿಜ;
		      c_parser_consume_token (parser);
		      cl = c_parser_gimple_postfix_ಅಭಿವ್ಯಕ್ತಿ (parser);
		      ಆದರೆ (!c_parser_ಮುಂದಿನ_token_is (parser, CPP_COLON))
			{
			  ro = cl;
			  ಚಿಹ್ನೆರಹಿತ HOST_WIDE_INT tmp = 0;
			  ಆದರೆ (!ವೃಕ್ಷ_ಹೊಂದುತ್ತದೆ_uhwi_p (ro.ಮೌಲ್ಯ)
			      || (tmp = ವೃಕ್ಷ_ಗಮ್ಯ_uhwi (ro.ಮೌಲ್ಯ)) > 1)
			    error_at (ro.get_ಆರಂಭ (),
				      "invalid reverse order value");
			  ಹಿಮ್ಮುಖ_ಕ್ರಮ = tmp;
			  has_clb = ಸುಳ್ಳು;
			  ಆದರೆ (c_parser_ಮುಂದಿನ_token_is (parser, CPP_COMMA))
			    {
			      c_parser_consume_token (parser);
			      cl = c_parser_gimple_postfix_ಅಭಿವ್ಯಕ್ತಿ (parser);
		              has_clb = ನಿಜ;
			    }
			}
		      ಆದರೆ (has_clb
			  && c_parser_require (parser,
					       CPP_COLON, "expected %<:%>"))
			{
			  ba = c_parser_gimple_postfix_ಅಭಿವ್ಯಕ್ತಿ (parser);
			  ಆದರೆ (!ವೃಕ್ಷ_ಹೊಂದುತ್ತದೆ_uhwi_p (cl.ಮೌಲ್ಯ)
			      || !ವೃಕ್ಷ_ಹೊಂದುತ್ತದೆ_uhwi_p (ba.ಮೌಲ್ಯ)
			      || compare_ವೃಕ್ಷ_int (cl.ಮೌಲ್ಯ,
						   (clique = ವೃಕ್ಷ_ಗಮ್ಯ_uhwi
								(cl.ಮೌಲ್ಯ)))
			      || compare_ವೃಕ್ಷ_int (ba.ಮೌಲ್ಯ,
						   (ತಳ = ವೃಕ್ಷ_ಗಮ್ಯ_uhwi
								 (ba.ಮೌಲ್ಯ))))
			    error_at (cl.get_ಆರಂಭ (),
				      "invalid clique/base pair");
			}
		    }
		  c_parser_skip_until_ಸಿಕ್ಕಿತು (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      ಆದರೆ (! type || c_parser_error (parser))
		{
		  c_parser_ಗಣ_error (parser, ಸುಳ್ಳು);
		  ಹಿಂತಿರುಗಿ ಅಭಿವ್ಯಕ್ತಿ;
		}
	      ಆದರೆ (ಸೂಚ್ಯಂಕ.ಮೌಲ್ಯ || ಹೆಜ್ಜೆ.ಮೌಲ್ಯ || index2.ಮೌಲ್ಯ)
		ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = build5_loc (loc, ಗುರಿ_MEM_REF,
					 type, ptr.ಮೌಲ್ಯ, alias_off.ಮೌಲ್ಯ,
					 ಸೂಚ್ಯಂಕ.ಮೌಲ್ಯ, ಹೆಜ್ಜೆ.ಮೌಲ್ಯ, index2.ಮೌಲ್ಯ);
	      ಇಲ್ಲದಿದ್ದರೆ
		ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = build2_loc (loc, MEM_REF,
					 type, ptr.ಮೌಲ್ಯ, alias_off.ಮೌಲ್ಯ);
	      ಆದರೆ (clique != 0)
		{
		  cfun->ಕೊನೆಯ_clique = MAX (cfun->ಕೊನೆಯ_clique, clique);
		  MR_DEPENDENCE_CLIQUE (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ) = clique;
		  MR_DEPENDENCE_ತಳ (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ) = ತಳ;
		}
	      ಆದರೆ (ಹಿಮ್ಮುಖ_ಕ್ರಮ)
		{
		  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ) == MEM_REF)
		    REF_ಹಿಮ್ಮುಖ_STORAGE_ಕ್ರಮ (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ) = ಹಿಮ್ಮುಖ_ಕ್ರಮ;
		  ಇಲ್ಲದಿದ್ದರೆ
		    error_at (ro.get_ಆರಂಭ (),
			      "target mem ref cannot have reverse order");
		}
	      ನಿಲ್ಲಿಸು;
	    }
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strcmp (IDENTIFIER_ಸೂಚಕ (id), "__VIEW_CONVERT") == 0)
	    {
	      /* __VIEW_CONVERT '<' type-name [ ',' number ] '>'
	                        '(' postfix-expression ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      ವೃಕ್ಷ type = c_parser_gimple_typespec (parser);
	      ಆದರೆ (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_ಅಭಿವ್ಯಕ್ತಿ op = c_parser_gimple_postfix_ಅಭಿವ್ಯಕ್ತಿ (parser);
		  c_parser_skip_until_ಸಿಕ್ಕಿತು (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  ಆದರೆ (type && op.ಮೌಲ್ಯ != error_mark_ಗಂಟು)
		    ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = build1_loc (loc, VIEW_CONVERT_ಅಭಿವ್ಯಕ್ತಿ,
					     type, op.ಮೌಲ್ಯ);
		}
	      ನಿಲ್ಲಿಸು;
	    }
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strcmp (IDENTIFIER_ಸೂಚಕ (id), "__BIT_FIELD_REF") == 0)
	    {
	      /* __BIT_FIELD_REF '<' type-name [ ',' number ] '>'
	                        '(' postfix-expression, integer, integer ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      ವೃಕ್ಷ type = c_parser_gimple_typespec (parser);
	      ಆದರೆ (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_ಅಭಿವ್ಯಕ್ತಿ op0 = c_parser_gimple_postfix_ಅಭಿವ್ಯಕ್ತಿ (parser);
		  c_parser_skip_until_ಸಿಕ್ಕಿತು (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_ಅಭಿವ್ಯಕ್ತಿ op1 = c_parser_gimple_postfix_ಅಭಿವ್ಯಕ್ತಿ (parser);
		  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (op1.ಮೌಲ್ಯ) != INTEGER_CST
		      || !int_ಹೊಂದುತ್ತದೆ_type_p (op1.ಮೌಲ್ಯ, bitsizetype))
		    c_parser_error (parser, "expected constant size");
		  c_parser_skip_until_ಸಿಕ್ಕಿತು (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_ಅಭಿವ್ಯಕ್ತಿ op2 = c_parser_gimple_postfix_ಅಭಿವ್ಯಕ್ತಿ (parser);
		  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (op2.ಮೌಲ್ಯ) != INTEGER_CST
		      || !int_ಹೊಂದುತ್ತದೆ_type_p (op2.ಮೌಲ್ಯ, bitsizetype))
		    c_parser_error (parser, "expected constant offset");
		  c_parser_skip_until_ಸಿಕ್ಕಿತು (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  ಆದರೆ (type
		      && op0.ಮೌಲ್ಯ != error_mark_ಗಂಟು
		      && ವೃಕ್ಷ_ಸಂಕೇತ (op1.ಮೌಲ್ಯ) == INTEGER_CST
		      && ವೃಕ್ಷ_ಸಂಕೇತ (op2.ಮೌಲ್ಯ) == INTEGER_CST)
		    ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = build3_loc (loc, ಬಿಟ್_ಕ್ಷೇತ್ರ_REF, type,
					     op0.ಮೌಲ್ಯ,
					     fold_convert (bitsizetype,
							   op1.ಮೌಲ್ಯ),
					     fold_convert (bitsizetype,
							   op2.ಮೌಲ್ಯ));
		}
	      ನಿಲ್ಲಿಸು;
	    }
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strcmp (IDENTIFIER_ಸೂಚಕ (id), "__CLOBBER") == 0)
	    {
	      /* __CLOBBER [ '(' bob | eob | bos | eos ')' ]  */
	      clobber_ಬಗೆ ಬಗೆ = CLOBBER_UNDEF;
	      c_parser_consume_token (parser);
	      ಆದರೆ (c_parser_ಮುಂದಿನ_token_is (parser, CPP_OPEN_PAREN))
		{
		  c_parser_consume_token (parser);
		  ಸ್ವಯಂಚಾಲಿತ tok = c_parser_peek_token (parser);
		  ಆದರೆ (c_parser_require (parser, CPP_NAME,
					"expected clobber kind"))
		    {
		      ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *ಬಗೆ_str = IDENTIFIER_ಸೂಚಕ (tok->ಮೌಲ್ಯ);
		      ಆದರೆ (strcmp (ಬಗೆ_str, "bos") == 0)
			ಬಗೆ = CLOBBER_STORAGE_BEGIN;
		      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strcmp (ಬಗೆ_str, "bob") == 0)
			ಬಗೆ = CLOBBER_OBJECT_BEGIN;
		      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strcmp (ಬಗೆ_str, "eob") == 0)
			ಬಗೆ = CLOBBER_OBJECT_ಕೊನೆ;
		      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strcmp (ಬಗೆ_str, "eos") == 0)
			ಬಗೆ = CLOBBER_STORAGE_ಕೊನೆ;
		      ಇಲ್ಲದಿದ್ದರೆ
			c_parser_error (parser, "expected one of %<bos%>, "
					"%<eos%>, %<bob>, %<eob%>");
		    }
		  c_parser_skip_until_ಸಿಕ್ಕಿತು (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      /* We infer the (redundant) type from the LHS.  */
	      ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = build_clobber (ret_type, ಬಗೆ);
	      ನಿಲ್ಲಿಸು;
	    }
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (strcmp (IDENTIFIER_ಸೂಚಕ (id), "_Literal") == 0)
	    {
	      /* _Literal '(' type-name ')' ( [ '-' ] constant | constructor ) */
	      c_parser_consume_token (parser);
	      ವೃಕ್ಷ type = NULL_ವೃಕ್ಷ;
	      ಆದರೆ (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  ರಚನೆ c_type_name *type_name = c_parser_type_name (parser);
		  ವೃಕ್ಷ tem;
		  ಆದರೆ (type_name)
		    type = groktypename (type_name, &tem, ಖಾಲಿ);
		  c_parser_skip_until_ಸಿಕ್ಕಿತು (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      ಆದರೆ (! type)
		{
		  c_parser_error (parser, "invalid _Literal");
		  ಹಿಂತಿರುಗಿ ಅಭಿವ್ಯಕ್ತಿ;
		}
	      ಆದರೆ (c_parser_ಮುಂದಿನ_token_is (parser, CPP_OPEN_BRACE))
		{
		  c_parser_consume_token (parser);
		  ಆದರೆ (!AGGREGATE_TYPE_P (type)
		      && !ಸದಿಶ_TYPE_P (type))
		    {
		      c_parser_error (parser, "invalid type for _Literal with "
				      "constructor");
		      c_parser_skip_until_ಸಿಕ್ಕಿತು (parser, CPP_CLOSE_BRACE,
						 "expected %<}%>");
		      ಹಿಂತಿರುಗಿ ಅಭಿವ್ಯಕ್ತಿ;
		    }
		  vec<constructor_elt, va_gc> *v = ಖಾಲಿ;
		  ತಾರ್ಕಿಕ constant_p = ನಿಜ;
		  ಆದರೆ (ಸದಿಶ_TYPE_P (type)
		      && !c_parser_ಮುಂದಿನ_token_is (parser, CPP_CLOSE_BRACE))
		    {
		      vec_alloc (v, TYPE_ಸದಿಶ_SUBPARTS (type).ಗಮ್ಯ_constant ());
		      ಮಾಡು
			{
			  ವೃಕ್ಷ val
			    = c_parser_gimple_postfix_ಅಭಿವ್ಯಕ್ತಿ (parser).ಮೌಲ್ಯ;
			  ಆದರೆ (! val
			      || val == error_mark_ಗಂಟು
			      || (! CONSTANT_CLASS_P (val)
				  && ! SSA_VAR_P (val)))
			    {
			      c_parser_error (parser, "invalid _Literal");
			      ಹಿಂತಿರುಗಿ ಅಭಿವ್ಯಕ್ತಿ;
			    }
			  CONSTRUCTOR_APPEND_ELT (v, NULL_ವೃಕ್ಷ, val);
			  ಆದರೆ (! CONSTANT_CLASS_P (val))
			    constant_p = ಸುಳ್ಳು;
			  ಆದರೆ (c_parser_ಮುಂದಿನ_token_is (parser, CPP_COMMA))
			    c_parser_consume_token (parser);
			  ಇಲ್ಲದಿದ್ದರೆ
			    ನಿಲ್ಲಿಸು;
			}
		      ಆಗ (1);
		    }
		  ಆದರೆ (c_parser_require (parser, CPP_CLOSE_BRACE,
					"expected %<}%>"))
		    {
		      ಆದರೆ (v && constant_p)
			ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = build_ಸದಿಶ_from_ctor (type, v);
		      ಇಲ್ಲದಿದ್ದರೆ
			ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = build_constructor (type, v);
		    }
		  ಇಲ್ಲದಿದ್ದರೆ
		    {
		      c_parser_skip_until_ಸಿಕ್ಕಿತು (parser, CPP_CLOSE_BRACE,
						 "expected %<}%>");
		      ಹಿಂತಿರುಗಿ ಅಭಿವ್ಯಕ್ತಿ;
		    }
		}
	      ಇಲ್ಲದಿದ್ದರೆ
		{
		  ತಾರ್ಕಿಕ neg_p, addr_p;
		  ಆದರೆ ((neg_p = c_parser_ಮುಂದಿನ_token_is (parser, CPP_MINUS)))
		    c_parser_consume_token (parser);
		  ಆದರೆ ((addr_p = c_parser_ಮುಂದಿನ_token_is (parser, CPP_AND)))
		    c_parser_consume_token (parser);
		  ವೃಕ್ಷ val = c_parser_gimple_postfix_ಅಭಿವ್ಯಕ್ತಿ (parser).ಮೌಲ್ಯ;
		  ಆದರೆ (! val
		      || val == error_mark_ಗಂಟು
		      || (!CONSTANT_CLASS_P (val) && !addr_p))
		    {
		      c_parser_error (parser, "invalid _Literal");
		      ಹಿಂತಿರುಗಿ ಅಭಿವ್ಯಕ್ತಿ;
		    }
		  ಆದರೆ (addr_p)
		    {
		      val = build1 (ADDR_ಅಭಿವ್ಯಕ್ತಿ, type, val);
		      ಆದರೆ (!is_gimple_invariant_ವಿಳಾಸ (val))
			{
			  c_parser_error (parser, "invalid _Literal");
			  ಹಿಂತಿರುಗಿ ಅಭಿವ್ಯಕ್ತಿ;
			}
		    }
		  ಆದರೆ (neg_p)
		    {
		      val = const_unop (NEGATE_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (val), val);
		      ಆದರೆ (! val)
			{
			  c_parser_error (parser, "invalid _Literal");
			  ಹಿಂತಿರುಗಿ ಅಭಿವ್ಯಕ್ತಿ;
			}
		    }
		  ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = fold_convert (type, val);
		}
	      ಹಿಂತಿರುಗಿ ಅಭಿವ್ಯಕ್ತಿ;
	    }

	  /* SSA name.  */
	  ಚಿಹ್ನೆರಹಿತ ಆವೃತ್ತಿ, ver_ಸ್ಥಾನಾಂತರ;
	  ಆದರೆ (! lookup_name (id)
	      && c_parser_parse_ssa_name_id (id, &ಆವೃತ್ತಿ, &ver_ಸ್ಥಾನಾಂತರ))
	    {
	      c_parser_consume_token (parser);
	      ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = c_parser_parse_ssa_name (parser, id, NULL_ವೃಕ್ಷ,
						    ಆವೃತ್ತಿ, ver_ಸ್ಥಾನಾಂತರ);
	      ಆದರೆ (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ == error_mark_ಗಂಟು)
		ಹಿಂತಿರುಗಿ ಅಭಿವ್ಯಕ್ತಿ;
	      ಗಣ_c_ಅಭಿವ್ಯಕ್ತಿ_ಮೂಲ_range (&ಅಭಿವ್ಯಕ್ತಿ, tok_range);
	      /* For default definition SSA names.  */
	      ಆದರೆ (c_parser_ಮುಂದಿನ_token_is (parser, CPP_OPEN_PAREN)
		  && c_parser_peek_2nd_token (parser)->type == CPP_NAME
		  && strcmp ("D",
			     IDENTIFIER_ಸೂಚಕ
			       (c_parser_peek_2nd_token (parser)->ಮೌಲ್ಯ)) == 0
		  && c_parser_peek_nth_token (parser, 3)->type == CPP_CLOSE_PAREN)
		{
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		  ಆದರೆ (! SSA_NAME_IS_DEFAULT_DEF (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ))
		    {
		      ಆದರೆ (!SSA_NAME_VAR (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ))
			{
			  error_at (loc, "anonymous SSA name cannot have"
				    " default definition");
			  ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = error_mark_ಗಂಟು;
			  ಹಿಂತಿರುಗಿ ಅಭಿವ್ಯಕ್ತಿ;
			}
		      ಗಣ_ssa_default_def (cfun, SSA_NAME_VAR (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ),
					   ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ);
		      SSA_NAME_DEF_STMT (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ) = gimple_build_nop ();
		    }
		}
	    }
	  ಇಲ್ಲದಿದ್ದರೆ
	    {
	      c_parser_consume_token (parser);
	      ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ
		= build_external_ref (loc, id,
				      (c_parser_peek_token (parser)->type
				       == CPP_OPEN_PAREN), &ಅಭಿವ್ಯಕ್ತಿ.original_type);
	      ಗಣ_c_ಅಭಿವ್ಯಕ್ತಿ_ಮೂಲ_range (&ಅಭಿವ್ಯಕ್ತಿ, tok_range);
	    }
	  ನಿಲ್ಲಿಸು;
	}
      /* Fallthru.  */
    ಪೂರ್ವನಿಯೋಜಿತ:
      c_parser_error (parser, "expected expression");
      ಅಭಿವ್ಯಕ್ತಿ.ಗಣ_error ();
      ನಿಲ್ಲಿಸು;
    }
  ಆದರೆ (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ == error_mark_ಗಂಟು)
    ಹಿಂತಿರುಗಿ ಅಭಿವ್ಯಕ್ತಿ;
  ಹಿಂತಿರುಗಿ c_parser_gimple_postfix_ಅಭಿವ್ಯಕ್ತಿ_after_primary
    (parser, ಅಭಿವ್ಯಕ್ತಿ_LOC_OR_LOC (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, loc), ಅಭಿವ್ಯಕ್ತಿ);
}

/* Parse a gimple postfix expression after the initial primary or compound
   literal.  */

ಸ್ಥಿರ ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ
c_parser_gimple_postfix_ಅಭಿವ್ಯಕ್ತಿ_after_primary (gimple_parser &parser,
						  location_t ಅಭಿವ್ಯಕ್ತಿ_loc,
						  ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ)
{
  location_t ಆರಂಭ;
  location_t ಮುಕ್ತಾಯ;
  ವೃಕ್ಷ ident;
  location_t comp_loc;

  ಆಗ (ನಿಜ)
    {
      location_t op_loc = c_parser_peek_token (parser)->location;
      ಆಯ್ಕೆ (c_parser_peek_token (parser)->type)
	{
	ಸ್ಥಿತಿ CPP_OPEN_ವರ್ಗಫಲ:
	  {
	    c_parser_consume_token (parser);
	    ವೃಕ್ಷ idx = c_parser_gimple_unary_ಅಭಿವ್ಯಕ್ತಿ (parser).ಮೌಲ್ಯ;

	    ಆದರೆ (! c_parser_require (parser, CPP_CLOSE_ವರ್ಗಫಲ, "expected %<]%>"))
	      {
		c_parser_skip_until_ಸಿಕ್ಕಿತು (parser, CPP_CLOSE_ವರ್ಗಫಲ, ಖಾಲಿ);
		ನಿಲ್ಲಿಸು;
	      }

	    ಆರಂಭ = ಅಭಿವ್ಯಕ್ತಿ.get_ಆರಂಭ ();
	    ಮುಕ್ತಾಯ = c_parser_ಟೋಕನುಗಳು_buf (parser, 0)->location;
	    ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = build_array_ref (op_loc, ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, idx);
	    ಗಣ_c_ಅಭಿವ್ಯಕ್ತಿ_ಮೂಲ_range (&ಅಭಿವ್ಯಕ್ತಿ, ಆರಂಭ, ಮುಕ್ತಾಯ);
	    ಅಭಿವ್ಯಕ್ತಿ.m_decimal = 0;

	    ಅಭಿವ್ಯಕ್ತಿ.original_ಸಂಕೇತ = ERROR_MARK;
	    ಅಭಿವ್ಯಕ್ತಿ.original_type = ಖಾಲಿ;
	    ನಿಲ್ಲಿಸು;
	  }
	ಸ್ಥಿತಿ CPP_OPEN_PAREN:
	  {
	    /* Function call.  */
	    c_parser_consume_token (parser);
	    auto_vec<ವೃಕ್ಷ> exprlist;
	    ಆದರೆ (! c_parser_ಮುಂದಿನ_token_is (parser, CPP_CLOSE_PAREN))
	      c_parser_gimple_ಅಭಿವ್ಯಕ್ತಿ_list (parser, &exprlist);
	    c_parser_skip_until_ಸಿಕ್ಕಿತು (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    ಆದರೆ (!FUNC_OR_ವಿಧಾನ_TYPE_P (ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ)))
	      {
		c_parser_error (parser, "invalid call to non-function");
		ಅಭಿವ್ಯಕ್ತಿ.ಗಣ_error ();
		ನಿಲ್ಲಿಸು;
	      }
	    ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = build_call_array_loc
		(ಅಭಿವ್ಯಕ್ತಿ_loc, ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ)),
		 ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, exprlist.ಉದ್ದಳತೆ (), exprlist.ವಿಳಾಸ ());
	    ಅಭಿವ್ಯಕ್ತಿ.m_decimal = 0;
	    ಅಭಿವ್ಯಕ್ತಿ.original_ಸಂಕೇತ = ERROR_MARK;
	    ಅಭಿವ್ಯಕ್ತಿ.original_type = ಖಾಲಿ;
	    ನಿಲ್ಲಿಸು;
	  }
	ಸ್ಥಿತಿ CPP_DOT:
	  {
	    /* Structure element reference.  */
	    c_parser_consume_token (parser);
	    ಆದರೆ (c_parser_ಮುಂದಿನ_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		ident = comp_tok->ಮೌಲ್ಯ;
		comp_loc = comp_tok->location;
	      }
	    ಇಲ್ಲದಿದ್ದರೆ
	      {
		c_parser_error (parser, "expected identifier");
		ಅಭಿವ್ಯಕ್ತಿ.ಗಣ_error ();
		ಅಭಿವ್ಯಕ್ತಿ.original_ಸಂಕೇತ = ERROR_MARK;
		ಅಭಿವ್ಯಕ್ತಿ.original_type = ಖಾಲಿ;
		ಹಿಂತಿರುಗಿ ಅಭಿವ್ಯಕ್ತಿ;
	      }
	    ಆರಂಭ = ಅಭಿವ್ಯಕ್ತಿ.get_ಆರಂಭ ();
	    ಮುಕ್ತಾಯ = c_parser_peek_token (parser)->get_ಮುಕ್ತಾಯ ();
	    c_parser_consume_token (parser);
	    ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = build_component_ref (op_loc, ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, ident,
					      comp_loc, UNKNOWN_LOCATION);
	    ಗಣ_c_ಅಭಿವ್ಯಕ್ತಿ_ಮೂಲ_range (&ಅಭಿವ್ಯಕ್ತಿ, ಆರಂಭ, ಮುಕ್ತಾಯ);
	    ಅಭಿವ್ಯಕ್ತಿ.m_decimal = 0;
	    ಅಭಿವ್ಯಕ್ತಿ.original_ಸಂಕೇತ = ERROR_MARK;
	    ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ) != COMPONENT_REF)
	      ಅಭಿವ್ಯಕ್ತಿ.original_type = ಖಾಲಿ;
	    ಇಲ್ಲದಿದ್ದರೆ
	      {
		/* Remember the original type of a bitfield.  */
		ವೃಕ್ಷ ಕ್ಷೇತ್ರ_2 = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, 1);
		ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಕ್ಷೇತ್ರ_2) != ಕ್ಷೇತ್ರ_DECL)
		  ಅಭಿವ್ಯಕ್ತಿ.original_type = ಖಾಲಿ;
		ಇಲ್ಲದಿದ್ದರೆ
		  ಅಭಿವ್ಯಕ್ತಿ.original_type = DECL_ಬಿಟ್_ಕ್ಷೇತ್ರ_TYPE (ಕ್ಷೇತ್ರ_2);
	      }
	    ನಿಲ್ಲಿಸು;
	  }
	ಸ್ಥಿತಿ CPP_DEREF:
	  {
	    /* Structure element reference.  */
	    ಆದರೆ (!ಸೂಚಕ_TYPE_P (ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ)))
	      {
		c_parser_error (parser, "dereference of non-pointer");
		ಅಭಿವ್ಯಕ್ತಿ.ಗಣ_error ();
		ಅಭಿವ್ಯಕ್ತಿ.original_ಸಂಕೇತ = ERROR_MARK;
		ಅಭಿವ್ಯಕ್ತಿ.original_type = ಖಾಲಿ;
		ಹಿಂತಿರುಗಿ ಅಭಿವ್ಯಕ್ತಿ;
	      }
	    c_parser_consume_token (parser);
	    ಆದರೆ (c_parser_ಮುಂದಿನ_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		ident = comp_tok->ಮೌಲ್ಯ;
		comp_loc = comp_tok->location;
	      }
	    ಇಲ್ಲದಿದ್ದರೆ
	      {
		c_parser_error (parser, "expected identifier");
		ಅಭಿವ್ಯಕ್ತಿ.ಗಣ_error ();
		ಅಭಿವ್ಯಕ್ತಿ.original_ಸಂಕೇತ = ERROR_MARK;
		ಅಭಿವ್ಯಕ್ತಿ.original_type = ಖಾಲಿ;
		ಹಿಂತಿರುಗಿ ಅಭಿವ್ಯಕ್ತಿ;
	      }
	    ಆರಂಭ = ಅಭಿವ್ಯಕ್ತಿ.get_ಆರಂಭ ();
	    ಮುಕ್ತಾಯ = c_parser_peek_token (parser)->get_ಮುಕ್ತಾಯ ();
	    c_parser_consume_token (parser);
	    ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = build_component_ref (op_loc,
					      build_simple_mem_ref_loc
					        (op_loc, ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ),
					      ident, comp_loc,
					      ಅಭಿವ್ಯಕ್ತಿ.get_location ());
	    ಗಣ_c_ಅಭಿವ್ಯಕ್ತಿ_ಮೂಲ_range (&ಅಭಿವ್ಯಕ್ತಿ, ಆರಂಭ, ಮುಕ್ತಾಯ);
	    ಅಭಿವ್ಯಕ್ತಿ.m_decimal = 0;
	    ಅಭಿವ್ಯಕ್ತಿ.original_ಸಂಕೇತ = ERROR_MARK;
	    ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ) != COMPONENT_REF)
	      ಅಭಿವ್ಯಕ್ತಿ.original_type = ಖಾಲಿ;
	    ಇಲ್ಲದಿದ್ದರೆ
	      {
		/* Remember the original type of a bitfield.  */
		ವೃಕ್ಷ ಕ್ಷೇತ್ರ_2 = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, 1);
		ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಕ್ಷೇತ್ರ_2) != ಕ್ಷೇತ್ರ_DECL)
		  ಅಭಿವ್ಯಕ್ತಿ.original_type = ಖಾಲಿ;
		ಇಲ್ಲದಿದ್ದರೆ
		  ಅಭಿವ್ಯಕ್ತಿ.original_type = DECL_ಬಿಟ್_ಕ್ಷೇತ್ರ_TYPE (ಕ್ಷೇತ್ರ_2);
	      }
	    ನಿಲ್ಲಿಸು;
	  }
	ಪೂರ್ವನಿಯೋಜಿತ:
	  ಹಿಂತಿರುಗಿ ಅಭಿವ್ಯಕ್ತಿ;
	}
    }
}

/* Parse expression list.

   gimple-expr-list:
     gimple-unary-expression
     gimple-expr-list , gimple-unary-expression

 */

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_gimple_ಅಭಿವ್ಯಕ್ತಿ_list (gimple_parser &parser, vec<ವೃಕ್ಷ> *ret)
{
  ರಚನೆ c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ;

  ಅಭಿವ್ಯಕ್ತಿ = c_parser_gimple_unary_ಅಭಿವ್ಯಕ್ತಿ (parser);
  ret->ಸುರಕ್ಷಿತ_ತಳ್ಳು (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ);
  ಆಗ (c_parser_ಮುಂದಿನ_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      ಅಭಿವ್ಯಕ್ತಿ = c_parser_gimple_unary_ಅಭಿವ್ಯಕ್ತಿ (parser);
      ret->ಸುರಕ್ಷಿತ_ತಳ್ಳು (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ);
    }
}

/* Parse gimple label.

   gimple-label:
     identifier :
     case constant-expression :
     default :

*/

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_gimple_label (gimple_parser &parser, gimple_seq *seq)
{
  ವೃಕ್ಷ name = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
  location_t loc1 = c_parser_peek_token (parser)->location;
  gcc_assert (c_parser_ಮುಂದಿನ_token_is (parser, CPP_NAME));
  c_parser_consume_token (parser);
  gcc_assert (c_parser_ಮುಂದಿನ_token_is (parser, CPP_COLON));
  c_parser_consume_token (parser);
  ವೃಕ್ಷ label = define_label (loc1, name);
  ಆದರೆ (label)
    gimple_seq_ಕೂಡಿಸು_stmt_without_update (seq, gimple_build_label (label));
  ಹಿಂತಿರುಗಿ;
}

/* Parse gimple/RTL pass list.

   gimple-or-rtl-pass-list:
     startwith("pass-name")[,{cfg,ssa}]
 */

ಶೂನ್ಯ
c_parser_gimple_or_rtl_pass_list (c_parser *parser, c_declspecs *specs)
{
  ಅಕ್ಷರ *pass = ಖಾಲಿ;

  /* Accept __GIMPLE/__RTL.  */
  ಆದರೆ (c_parser_ಮುಂದಿನ_token_is_not (parser, CPP_OPEN_PAREN))
    ಹಿಂತಿರುಗಿ;
  c_parser_consume_token (parser);

  specs->ನಮೂದು_bb_ಎಣಿಕೆ = profile_ಎಣಿಕೆ::uninitialized ();
  ಆಗ (c_parser_ಮುಂದಿನ_token_is (parser, CPP_NAME))
    {
      profile_quality quality;
      ಸ್ಥಿರಾಂಕ ಅಕ್ಷರ *op = IDENTIFIER_ಸೂಚಕ (c_parser_peek_token (parser)->ಮೌಲ್ಯ);
      c_parser_consume_token (parser);
      ಆದರೆ (! strcmp (op, "startwith"))
	{
	  ಆದರೆ (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    ಹಿಂತಿರುಗಿ;
	  ಆದರೆ (c_parser_ಮುಂದಿನ_token_is_not (parser, CPP_STRING))
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"expected pass name");
	      ಹಿಂತಿರುಗಿ;
	    }
	  pass = xstrdup (ವೃಕ್ಷ_STRING_ಸೂಚಕ
			  (c_parser_string_literal (parser, ಸುಳ್ಳು,
						    ಸುಳ್ಳು).ಮೌಲ್ಯ));
	  ಆದರೆ (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<(%>"))
	    ಹಿಂತಿರುಗಿ;
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (parse_profile_quality (op, &quality))
	{
	  ವೃಕ್ಷ q;
	  ಆದರೆ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    ಹಿಂತಿರುಗಿ;

	  ಆದರೆ (!c_parser_ಮುಂದಿನ_token_is (parser, CPP_ಸಂಖ್ಯೆ)
	      || (ವೃಕ್ಷ_ಸಂಕೇತ (q = c_parser_peek_token (parser)->ಮೌಲ್ಯ)
		  != INTEGER_CST))
	    {
	      c_parser_error (parser, "expected count value");
	      ಹಿಂತಿರುಗಿ;
	    }

	  specs->ನಮೂದು_bb_ಎಣಿಕೆ
	    = profile_ಎಣಿಕೆ::from_gcov_type (ವೃಕ್ಷ_INT_CST_ಕೆಳಗಿನ (q), quality);
	  c_parser_consume_token (parser);
	  ಆದರೆ (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    ಹಿಂತಿರುಗಿ;
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (specs->declspec_il != cdil_gimple)
	/* Allow only one IL specifier and none on RTL.  */
	;
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (! strcmp (op, "cfg"))
	specs->declspec_il = cdil_gimple_cfg;
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (! strcmp (op, "ssa"))
	specs->declspec_il = cdil_gimple_ssa;
      ಇಲ್ಲದಿದ್ದರೆ
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "invalid operation");
	  ಹಿಂತಿರುಗಿ;
	}
     ಆದರೆ (c_parser_ಮುಂದಿನ_token_is (parser, CPP_COMMA))
       c_parser_consume_token (parser);
    }

  ಆದರೆ (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    ಹಿಂತಿರುಗಿ;

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
ರಿಜಿಸ್ಟರ್

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

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_gimple_declaration (gimple_parser &parser)
{
  ರಚನೆ c_declarator *declarator;
  ರಚನೆ c_declspecs *specs = build_null_declspecs ();
  c_parser_declspecs (parser, specs, ನಿಜ, ನಿಜ, ನಿಜ,
		      ನಿಜ, ನಿಜ, ನಿಜ, ನಿಜ, cla_nonabstract_decl);
  ಮುಕ್ತಾಯ_declspecs (specs);

  /* Provide better error recovery.  Note that a type name here is usually
     better diagnosed as a redeclaration.  */
  ಆದರೆ (c_parser_ಮುಂದಿನ_token_starts_declspecs (parser)
      && ! c_parser_ಮುಂದಿನ_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<;%>");
      c_parser_ಗಣ_error (parser, ಸುಳ್ಳು);
      ಹಿಂತಿರುಗಿ;
    }

  ತಾರ್ಕಿಕ dummy = ಸುಳ್ಳು;
  declarator = c_parser_declarator (parser,
				    specs->typespec_ಬಗೆ != ctsk_none,
				    C_DTR_ಸಾಮಾನ್ಯ, &dummy);

  ಆದರೆ (!c_parser_ಮುಂದಿನ_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_error (parser, "expected %<;%>");
      ಹಿಂತಿರುಗಿ;
    }
  ಆದರೆ (declarator)
    {
      /* Handle SSA name decls specially, they do not go into the identifier
         table but we simply build the SSA name for later lookup.  */
      ಚಿಹ್ನೆರಹಿತ ಆವೃತ್ತಿ, ver_ಸ್ಥಾನಾಂತರ;
      /* Handle SSA pointer declarations in a very simplistic ways, we
	 probably would like to call grokdeclarator in a special mode to
	 just build the type of the decl - start_decl already pushes
	 the identifier to the bindings for lookup, something we do not
	 want.  */
      ರಚನೆ c_declarator *id_declarator = declarator;
      ಆಗ (id_declarator->ಬಗೆ == cdk_ಸೂಚಕ)
	id_declarator = id_declarator->declarator;
      ಆದರೆ (id_declarator->ಬಗೆ == cdk_id
	  && (declarator->ಬಗೆ == cdk_ಸೂಚಕ
	      || is_gimple_reg_type (specs->type))
	  && c_parser_parse_ssa_name_id (id_declarator->u.id.id,
					 &ಆವೃತ್ತಿ, &ver_ಸ್ಥಾನಾಂತರ)
	  /* The following restricts it to unnamed anonymous SSA names
	     which fails parsing of named ones in dumps (we could
	     decide to not dump their name for -gimple).  */
	  && ver_ಸ್ಥಾನಾಂತರ == 0)
	{
	  ರಚನೆ c_declarator *p = declarator;
	  ವೃಕ್ಷ type = specs->type;
	  ಆಗ (p->ಬಗೆ == cdk_ಸೂಚಕ)
	    {
	      type = build_ಸೂಚಕ_type (type);
	      p = p->declarator;
	    }
	  c_parser_parse_ssa_name (parser, id_declarator->u.id.id, type,
				   ಆವೃತ್ತಿ, ver_ಸ್ಥಾನಾಂತರ);
	}
      ಇಲ್ಲದಿದ್ದರೆ
	{
	  ವೃಕ್ಷ postfix_attrs = NULL_ವೃಕ್ಷ;
	  ವೃಕ್ಷ all_ಪೂರ್ವಪ್ರತ್ಯಯ_attrs = specs->attrs;
	  specs->attrs = ಖಾಲಿ;
	  ವೃಕ್ಷ decl = ಆರಂಭ_decl (declarator, specs, ಸುಳ್ಳು,
				  chainon (postfix_attrs, all_ಪೂರ್ವಪ್ರತ್ಯಯ_attrs));
	  ಆದರೆ (decl)
	    ಮುಕ್ತಾಯ_decl (decl, UNKNOWN_LOCATION, NULL_ವೃಕ್ಷ, NULL_ವೃಕ್ಷ,
			 NULL_ವೃಕ್ಷ);
	}
    }
}

/* Parse gimple goto statement.  */

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_gimple_goto_stmt (gimple_parser &parser,
			   location_t loc, ವೃಕ್ಷ label, gimple_seq *seq)
{
  ಆದರೆ (cfun->curr_properties & PROP_cfg)
    {
      ಪೂರ್ಣಾಂಕ dest_ಸೂಚ್ಯಂಕ;
      profile_probability prob;
      ಆದರೆ (c_parser_gimple_parse_bb_spec_ಅಂಚು_probability (label, parser,
							  &dest_ಸೂಚ್ಯಂಕ, &prob))
	{
	  parser.ತಳ್ಳು_ಅಂಚು (parser.current_bb->ಸೂಚ್ಯಂಕ, dest_ಸೂಚ್ಯಂಕ,
			    ಅಂಚು_FALLTHRU, prob);
	  ಹಿಂತಿರುಗಿ;
	}
    }
  ವೃಕ್ಷ decl = lookup_label_for_goto (loc, label);
  gimple_seq_ಕೂಡಿಸು_stmt_without_update (seq, gimple_build_goto (decl));
}

/* Parse a parenthesized condition.
   gimple-condition:
     ( gimple-binary-expression )    */

ಸ್ಥಿರ ವೃಕ್ಷ
c_parser_gimple_paren_condition (gimple_parser &parser)
{
  ಆದರೆ (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
  ವೃಕ್ಷ cond
    = c_parser_gimple_ದ್ವಿಮಾನ_ಅಭಿವ್ಯಕ್ತಿ (parser, boolean_type_ಗಂಟು).ಮೌಲ್ಯ;
  ಆದರೆ (cond != error_mark_ಗಂಟು
      && ! COMPARISON_CLASS_P (cond)
      && ! CONSTANT_CLASS_P (cond)
      && ! SSA_VAR_P (cond))
    {
      c_parser_error (parser, "comparison required");
      cond = error_mark_ಗಂಟು;
    }
  ಆದರೆ (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    ಹಿಂತಿರುಗಿ error_mark_ಗಂಟು;
  ಹಿಂತಿರುಗಿ cond;
}

/* Parse gimple try statement.

   try-statement:
     try { ... } finally { ... }
     try { ... } finally { ... } else { ... }

   This could support try/catch as well, but it's not implemented yet.
 */

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_gimple_try_stmt (gimple_parser &parser, gimple_seq *seq)
{
  gimple_seq tryseq = ಖಾಲಿ;
  c_parser_consume_token (parser);
  c_parser_gimple_compound_statement (parser, &tryseq);

  ಆದರೆ ((c_parser_ಮುಂದಿನ_token_is (parser, CPP_KEYWORD)
       && c_parser_peek_token (parser)->keyword == RID_AT_FINALLY)
      || (c_parser_ಮುಂದಿನ_token_is (parser, CPP_NAME)
	  && c_parser_peek_token (parser)->id_ಬಗೆ == C_ID_ID
	  && strcmp (IDENTIFIER_ಸೂಚಕ (c_parser_peek_token (parser)->ಮೌಲ್ಯ),
		     "finally") == 0))
    {
      gimple_seq finseq = ಖಾಲಿ;
      c_parser_consume_token (parser);
      c_parser_gimple_compound_statement (parser, &finseq);

      ಆದರೆ (c_parser_ಮುಂದಿನ_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_ELSE)
	{
	  gimple_seq elsseq = ಖಾಲಿ;
	  c_parser_consume_token (parser);
	  c_parser_gimple_compound_statement (parser, &elsseq);

	  geh_else *stmt = gimple_build_eh_else (finseq, elsseq);
	  finseq = ಖಾಲಿ;
	  gimple_seq_ಕೂಡಿಸು_stmt_without_update (&finseq, stmt);
	}

      gtry *stmt = gimple_build_try (tryseq, finseq, GIMPLE_TRY_FINALLY);
      gimple_seq_ಕೂಡಿಸು_stmt_without_update (seq, stmt);
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (c_parser_ಮುಂದಿನ_token_is (parser, CPP_KEYWORD)
      && c_parser_peek_token (parser)->keyword == RID_AT_CATCH)
    c_parser_error (parser, "%<catch%> is not supported");
  ಇಲ್ಲದಿದ್ದರೆ
    c_parser_error (parser, "expected %<finally%> or %<catch%>");
}

/* Parse gimple if-else statement.

   if-statement:
     if ( gimple-binary-expression ) gimple-goto-statement
     if ( gimple-binary-expression ) gimple-goto-statement \
					else gimple-goto-statement
 */

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_gimple_if_stmt (gimple_parser &parser, gimple_seq *seq)
{
  ವೃಕ್ಷ t_label = NULL_ವೃಕ್ಷ, f_label = NULL_ವೃಕ್ಷ, label;
  location_t loc;
  c_parser_consume_token (parser);
  ವೃಕ್ಷ cond = c_parser_gimple_paren_condition (parser);

  ಆದರೆ (c_parser_ಮುಂದಿನ_token_is_keyword (parser, RID_GOTO))
    {
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      ಆದರೆ (! c_parser_ಮುಂದಿನ_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected label");
	  ಹಿಂತಿರುಗಿ;
	}
      label = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
      c_parser_consume_token (parser);
      ಪೂರ್ಣಾಂಕ dest_ಸೂಚ್ಯಂಕ;
      profile_probability prob;
      ಆದರೆ ((cfun->curr_properties & PROP_cfg)
	  && c_parser_gimple_parse_bb_spec_ಅಂಚು_probability (label, parser,
							     &dest_ಸೂಚ್ಯಂಕ, &prob))
	parser.ತಳ್ಳು_ಅಂಚು (parser.current_bb->ಸೂಚ್ಯಂಕ, dest_ಸೂಚ್ಯಂಕ,
			  ಅಂಚು_TRUE_ಮೌಲ್ಯ, prob);
      ಇಲ್ಲದಿದ್ದರೆ
	t_label = lookup_label_for_goto (loc, label);
      ಆದರೆ (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	ಹಿಂತಿರುಗಿ;
    }
  ಇಲ್ಲದಿದ್ದರೆ
    {
      c_parser_error (parser, "expected goto expression");
      ಹಿಂತಿರುಗಿ;
    }

  ಆದರೆ (c_parser_ಮುಂದಿನ_token_is_keyword (parser, RID_ELSE))
    c_parser_consume_token (parser);
  ಇಲ್ಲದಿದ್ದರೆ
    {
      c_parser_error (parser, "expected else statement");
      ಹಿಂತಿರುಗಿ;
    }

  ಆದರೆ (c_parser_ಮುಂದಿನ_token_is_keyword (parser, RID_GOTO))
    {
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      ಆದರೆ (! c_parser_ಮುಂದಿನ_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected label");
	  ಹಿಂತಿರುಗಿ;
	}
      label = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
      c_parser_consume_token (parser);
      ಪೂರ್ಣಾಂಕ dest_ಸೂಚ್ಯಂಕ;
      profile_probability prob;
      ಆದರೆ ((cfun->curr_properties & PROP_cfg)
	  && c_parser_gimple_parse_bb_spec_ಅಂಚು_probability (label, parser,
							     &dest_ಸೂಚ್ಯಂಕ, &prob))
	parser.ತಳ್ಳು_ಅಂಚು (parser.current_bb->ಸೂಚ್ಯಂಕ, dest_ಸೂಚ್ಯಂಕ,
			  ಅಂಚು_FALSE_ಮೌಲ್ಯ, prob);
      ಇಲ್ಲದಿದ್ದರೆ
	f_label = lookup_label_for_goto (loc, label);
      ಆದರೆ (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	ಹಿಂತಿರುಗಿ;
    }
  ಇಲ್ಲದಿದ್ದರೆ
    {
      c_parser_error (parser, "expected goto expression");
      ಹಿಂತಿರುಗಿ;
    }

  ಆದರೆ (cond != error_mark_ಗಂಟು)
    gimple_seq_ಕೂಡಿಸು_stmt_without_update (seq, gimple_build_cond_from_ವೃಕ್ಷ (cond, t_label,
							   f_label));
}

/* Parse gimple switch-statement.

   gimple-switch-statement:
     switch (gimple-postfix-expression) gimple-case-statement

   gimple-case-statement:
     gimple-case-statement
     gimple-label-statement : gimple-goto-statement
*/

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_gimple_switch_stmt (gimple_parser &parser, gimple_seq *seq)
{
  c_ಅಭಿವ್ಯಕ್ತಿ cond_ಅಭಿವ್ಯಕ್ತಿ;
  ವೃಕ್ಷ case_label, label;
  auto_vec<ವೃಕ್ಷ> labels;
  ವೃಕ್ಷ default_label = NULL_ವೃಕ್ಷ;
  c_parser_consume_token (parser);

  ಆದರೆ (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    ಹಿಂತಿರುಗಿ;
  cond_ಅಭಿವ್ಯಕ್ತಿ = c_parser_gimple_postfix_ಅಭಿವ್ಯಕ್ತಿ (parser);
  ಆದರೆ (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    ಹಿಂತಿರುಗಿ;

  ಆದರೆ (! c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    ಹಿಂತಿರುಗಿ;

  ಆಗ (c_parser_ಮುಂದಿನ_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      ಆದರೆ (c_parser_ಮುಂದಿನ_token_is (parser, CPP_EOF))
	{
	  c_parser_error (parser, "expected statement");
	  ಹಿಂತಿರುಗಿ;
	}

      ಆಯ್ಕೆ (c_parser_peek_token (parser)->keyword)
	{
	ಸ್ಥಿತಿ RID_CASE:
	  {
	    c_ಅಭಿವ್ಯಕ್ತಿ exp1;
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);

	    ಆದರೆ (c_parser_ಮುಂದಿನ_token_is (parser, CPP_NAME)
		|| c_parser_peek_token (parser)->type == CPP_ಸಂಖ್ಯೆ)
	      exp1 = c_parser_gimple_postfix_ಅಭಿವ್ಯಕ್ತಿ (parser);
	    ಇಲ್ಲದಿದ್ದರೆ
	      {
		c_parser_error (parser, "expected expression");
		ಹಿಂತಿರುಗಿ;
	      }

	    ಆದರೆ (c_parser_ಮುಂದಿನ_token_is (parser, CPP_COLON))
	      {
		c_parser_consume_token (parser);
		ಆದರೆ (c_parser_ಮುಂದಿನ_token_is (parser, CPP_NAME))
		  {
		    label = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
		    c_parser_consume_token (parser);
		    ವೃಕ್ಷ decl = lookup_label_for_goto (loc, label);
		    case_label = build_case_label (exp1.ಮೌಲ್ಯ, NULL_ವೃಕ್ಷ,
						   decl);
		    labels.ಸುರಕ್ಷಿತ_ತಳ್ಳು (case_label);
		    ಆದರೆ (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      ಹಿಂತಿರುಗಿ;
		  }
		ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (! c_parser_require (parser, CPP_NAME,
					     "expected label"))
		  ಹಿಂತಿರುಗಿ;
	      }
	    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (! c_parser_require (parser, CPP_SEMICOLON,
					 "expected %<:%>"))
	      ಹಿಂತಿರುಗಿ;
	    ನಿಲ್ಲಿಸು;
	  }
	ಸ್ಥಿತಿ RID_DEFAULT:
	  {
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);
	    ಆದರೆ (c_parser_ಮುಂದಿನ_token_is (parser, CPP_COLON))
	      {
		c_parser_consume_token (parser);
		ಆದರೆ (c_parser_ಮುಂದಿನ_token_is (parser, CPP_NAME))
		  {
		    label = c_parser_peek_token (parser)->ಮೌಲ್ಯ;
		    c_parser_consume_token (parser);
		    ವೃಕ್ಷ decl = lookup_label_for_goto (loc, label);
		    default_label = build_case_label (NULL_ವೃಕ್ಷ, NULL_ವೃಕ್ಷ,
						      decl);
		    ಆದರೆ (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      ಹಿಂತಿರುಗಿ;
		  }
		ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (! c_parser_require (parser, CPP_NAME,
					     "expected label"))
		  ಹಿಂತಿರುಗಿ;
	      }
	    ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (! c_parser_require (parser, CPP_SEMICOLON,
					 "expected %<:%>"))
	      ಹಿಂತಿರುಗಿ;
	    ನಿಲ್ಲಿಸು;
	  }
	ಪೂರ್ವನಿಯೋಜಿತ:
	  c_parser_error (parser, "expected case label");
	  ಹಿಂತಿರುಗಿ;
	}

    }
  ಆದರೆ (! c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>"))
    ಹಿಂತಿರುಗಿ;

  ಆದರೆ (cond_ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ != error_mark_ಗಂಟು)
    {
      gswitch *s = gimple_build_switch (cond_ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, default_label, labels);
      gimple_seq_ಕೂಡಿಸು_stmt_without_update (seq, s);
    }
}

/* Parse gimple return statement.  */

ಸ್ಥಿರ ಶೂನ್ಯ
c_parser_gimple_return_stmt (gimple_parser &parser, gimple_seq *seq)
{
  location_t loc = c_parser_peek_token (parser)->location;
  gimple *ret = ಖಾಲಿ;
  c_parser_consume_token (parser);
  ಆದರೆ (c_parser_ಮುಂದಿನ_token_is (parser, CPP_SEMICOLON))
    {
      c_ಮುಕ್ತಾಯ_gimple_return (loc, NULL_ವೃಕ್ಷ);
      ret = gimple_build_return (ಖಾಲಿ);
      gimple_seq_ಕೂಡಿಸು_stmt_without_update (seq, ret);
    }
  ಇಲ್ಲದಿದ್ದರೆ
    {
      location_t xloc = c_parser_peek_token (parser)->location;
      c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ = c_parser_gimple_unary_ಅಭಿವ್ಯಕ್ತಿ (parser);
      ಆದರೆ (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ != error_mark_ಗಂಟು)
	{
	  c_ಮುಕ್ತಾಯ_gimple_return (xloc, ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ);
	  ret = gimple_build_return (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ);
	  gimple_seq_ಕೂಡಿಸು_stmt_without_update (seq, ret);
	}
    }
}

/* Support function for c_parser_gimple_return_stmt.  */

ಸ್ಥಿರ ಶೂನ್ಯ
c_ಮುಕ್ತಾಯ_gimple_return (location_t loc, ವೃಕ್ಷ retval)
{
  ವೃಕ್ಷ valtype = ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (current_function_decl));

  /* Use the expansion point to handle cases such as returning NULL
     in a function returning void.  */
  location_t xloc = expansion_ಬಿಂದು_location_if_ಒಳ_system_ಶೀರ್ಷಿಕೆ (loc);

  ಆದರೆ (ವೃಕ್ಷ_THIS_VOLATILE (current_function_decl))
    warning_at (xloc, 0,
		"function declared %<noreturn%> has a %<return%> statement");

  ಆದರೆ (! retval)
    current_function_returns_null = 1;
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (valtype == 0 || VOID_TYPE_P (valtype))
    {
      current_function_returns_null = 1;
      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (retval)) != VOID_TYPE)
	{
	  error_at
	    (xloc, "%<return%> with a value, in function returning void");
	  inform (DECL_ಮೂಲ_LOCATION (current_function_decl),
		  "declared here");
	}
    }
  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (valtype) != ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (retval)))
    {
      error_at
	(xloc, "invalid conversion in return statement");
      inform (DECL_ಮೂಲ_LOCATION (current_function_decl),
	      "declared here");
    }
  ಹಿಂತಿರುಗಿ;
}
