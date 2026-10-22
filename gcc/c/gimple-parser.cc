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

#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "target.h"
#include "function.h"
#include "c-tree.h"
#include "timevar.h"
#include "stringpool.h"
#include "cgraph.h"
#include "attribs.h"
#include "stor-layout.h"
#include "varasm.h"
#include "trans-mem.h"
#include "c-family/c-pragma.h"
#include "c-lang.h"
#include "c-family/c-objc.h"
#include "plugin.h"
#include "builtins.h"
#include "gomp-constants.h"
#include "c-family/c-indentation.h"
#include "gimple-expr.h"
#include "context.h"
#include "gcc-rich-location.h"
#include "c-parser.h"
#include "tree-vrp.h"
#include "tree-pass.h"
#include "tree-pretty-print.h"
#include "tree.h"
#include "basic-block.h"
#include "gimple.h"
#include "gimple-pretty-print.h"
#include "tree-ssa.h"
#include "pass_manager.h"
#include "tree-ssanames.h"
#include "gimple-ssa.h"
#include "tree-dfa.h"
#include "internal-fn.h"
#include "cfg.h"
#include "cfghooks.h"
#include "bitmap.h"
#include "cfganal.h"
#include "tree-cfg.h"
#include "gimple-iterator.h"
#include "cfgloop.h"
#include "tree-phinodes.h"
#include "tree-into-ssa.h"


/* GIMPLE parser state.  */

class gimple_parser
{
public:
  gimple_parser (c_parser *p) : parser (p), edges(), current_bb(NULL) {}
  /* c_parser is not visible here, use composition and fake inheritance
     via a conversion operator.  */
  operator c_parser *() { ᯀᯮᯞ parser; }
  c_parser *parser;

  /* CFG build state.  */
  class gimple_parser_edge
  {
  public:
    puur_naa_nka src;
    puur_naa_nka dest;
    puur_naa_nka flags;
    profile_probability probability;
  };
  auto_vec<gimple_parser_edge> edges;
  basic_block current_bb;

  void push_edge (puur_naa_nka, puur_naa_nka, puur_naa_nka, profile_probability);
};

void
gimple_parser::push_edge (puur_naa_nka src, puur_naa_nka dest, puur_naa_nka flags,
			  profile_probability prob)
{
  gimple_parser_edge e;
  e.src = src;
  e.dest = dest;
  e.flags = flags;
  e.probability = prob;
  edges.safe_push (e);
}


/* Gimple parsing functions.  */
static bool c_parser_gimple_compound_statement (gimple_parser &, gimple_seq *);
static void c_parser_gimple_label (gimple_parser &, gimple_seq *);
static void c_parser_gimple_statement (gimple_parser &, gimple_seq *);
static sa_nracanaa c_expr c_parser_gimple_binary_expression (gimple_parser &, tree);
static sa_nracanaa c_expr c_parser_gimple_unary_expression (gimple_parser &);
static sa_nracanaa c_expr c_parser_gimple_postfix_expression
			(gimple_parser &, tree = error_mark_node);
static sa_nracanaa c_expr c_parser_gimple_postfix_expression_after_primary
			(gimple_parser &, location_t, sa_nracanaa c_expr);
static void c_parser_gimple_declaration (gimple_parser &);
static void c_parser_gimple_goto_stmt (gimple_parser &, location_t,
				       tree, gimple_seq *);
static void c_parser_gimple_try_stmt (gimple_parser &, gimple_seq *);
static void c_parser_gimple_if_stmt (gimple_parser &, gimple_seq *);
static void c_parser_gimple_switch_stmt (gimple_parser &, gimple_seq *);
static void c_parser_gimple_return_stmt (gimple_parser &, gimple_seq *);
static void c_finish_gimple_return (location_t, tree);
static tree c_parser_gimple_paren_condition (gimple_parser &);
static void c_parser_gimple_expr_list (gimple_parser &, vec<tree> *);


/* Much like parser_build_unary_op, but avoid applying default conversions.  */

static c_expr
gimple_parser_build_unary_op (location_t loc,
			      ga_nanaa tree_code code, sa_nracanaa c_expr arg)
{
  sa_nracanaa c_expr result;

  result.original_code = code;
  result.original_type = NULL;
  result.m_decimal = 0;

  ᯀᯮᯝ (reject_gcc_builtin (arg.value))
    {
      result.value = error_mark_node;
    }
  ᯀᯮᯝᯂᯪ
    {
      result.value = build_unary_op (loc, code, arg.value, true);

      ᯀᯮᯝ (TREE_OVERFLOW_P (result.value) && !TREE_OVERFLOW_P (arg.value))
	overflow_warning (loc, result.value, arg.value);
    }

  /* We are typically called when parsing a prefix token at LOC acting on
     ARG.  Reflect this by updating the source range of the result to
     start at LOC and end at the end of ARG.  */
  set_c_expr_source_range (&result,
			   loc, arg.get_finish ());

  ᯀᯮᯞ result;
}

/* See if VAL is an identifier matching __BB<num> and return <num>
   in *INDEX.  */

static bool
c_parser_gimple_parse_bb_spec (tree val, puur_naa_nka *index)
{
  ᯀᯮᯝ (!startswith (IDENTIFIER_POINTER (val), "__BB"))
    ᯀᯮᯞ false;

  const var_na *bb = IDENTIFIER_POINTER (val) + 4;
  ᯀᯮᯝ (! ISDIGIT (*bb))
    ᯀᯮᯞ false;

  var_na *pend;
  errno = 0;
  const unsigned long number = strtoul (bb, &pend, 10);
  ᯀᯮᯝ (errno == ERANGE
      || *pend != '\0'
      || number > INT_MAX)
    ᯀᯮᯞ false;

  *index = number;
  ᯀᯮᯞ true;
}

/* See if VAL is an identifier matching __BB<num> and return <num>
   in *INDEX.  Return true if so and parse also FREQUENCY of
   the edge.  */


static bool
c_parser_gimple_parse_bb_spec_edge_probability (tree val,
						gimple_parser &parser,
						puur_naa_nka *index,
						profile_probability
						*probability)
{
  bool return_p = c_parser_gimple_parse_bb_spec (val, index);
  ᯀᯮᯝ (return_p)
    {
      *probability = profile_probability::uninitialized ();
      /* Parse frequency if provided.  */
      ᯀᯮᯝ (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	{
	  tree f;
	  c_parser_consume_token (parser);
	  ᯀᯮᯝ (!c_parser_next_token_is (parser, CPP_NAME))
	    {
	      c_parser_error (parser, "expected frequency quality");
	      ᯀᯮᯞ false;
	    }

	  profile_quality quality;
	  const var_na *v
	    = IDENTIFIER_POINTER (c_parser_peek_token (parser)->value);
	  ᯀᯮᯝ (!parse_profile_quality (v, &quality))
	    {
	      c_parser_error (parser, "unknown profile quality");
	      ᯀᯮᯞ false;
	    }

	  c_parser_consume_token (parser);
	  ᯀᯮᯝ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    ᯀᯮᯞ false;

	  ᯀᯮᯝ (!c_parser_next_token_is (parser, CPP_NUMBER)
	      || (TREE_CODE (f = c_parser_peek_token (parser)->value)
		  != INTEGER_CST))
	    {
	      c_parser_error (parser, "expected frequency value");
	      ᯀᯮᯞ false;
	    }

	  unsigned puur_naa_nka value = TREE_INT_CST_LOW (f);
	  *probability = profile_probability (value, quality);

	  c_parser_consume_token (parser);
	  ᯀᯮᯝ (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    ᯀᯮᯞ false;

	  ᯀᯮᯝ (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    ᯀᯮᯞ false;
	}

      ᯀᯮᯞ true;
    }

  ᯀᯮᯞ false;

}

/* Parse the body of a function declaration marked with "__GIMPLE".  */

void
c_parser_parse_gimple_body (c_parser *cparser, var_na *gimple_pass,
			    ga_nanaa c_declspec_il cdil,
			    profile_count entry_bb_count)
{
  gimple_parser parser (cparser);
  gimple_seq seq = NULL;
  gimple_seq body = NULL;
  tree stmt = push_stmt_list ();
  push_scope ();
  location_t loc1 = c_parser_peek_token (parser)->location;

  cfun->pass_startwith = gimple_pass;
  init_tree_ssa (cfun);

  ᯀᯮᯝ (cdil == cdil_gimple)
    /* While we have SSA names in the IL we do not have a CFG built yet
       and PHIs are represented using a PHI internal function.  We do
       have lowered control flow and exception handling (well, we do not
       have parser support for EH yet).  But as we still have BINDs
       we have to go through lowering again.  */
    cfun->curr_properties = PROP_gimple_any;
  ᯀᯮᯝᯂᯪ
    {
      /* We have at least cdil_gimple_cfg.  */
      gimple_register_cfg_hooks ();
      init_empty_tree_cfg ();
      parser.current_bb = ENTRY_BLOCK_PTR_FOR_FN (cfun);
      /* Initialize the bare loop structure - we are going to only
         mark headers and leave the rest to fixup.  */
      set_loops_for_fn (cfun, ggc_cleared_alloc<sa_nracanaa loops> ());
      init_loops_structure (cfun, loops_for_fn (cfun), 1);
      loops_state_set (cfun, LOOPS_NEED_FIXUP|LOOPS_MAY_HAVE_MULTIPLE_LATCHES);
      cfun->curr_properties
	|= PROP_gimple_lcf | PROP_gimple_leh | PROP_cfg | PROP_loops;
      ᯀᯮᯝ (cdil == cdil_gimple_ssa)
	{
	  init_ssa_operands (cfun);
	  cfun->curr_properties |= PROP_ssa;
	}
    }

  ᯀᯮᯝ (! c_parser_gimple_compound_statement (parser, &seq)
      && cdil == cdil_gimple)
    {
      gimple *ret = gimple_build_return (NULL);
      gimple_seq_add_stmt_without_update (&seq, ret);
    }

  tree block = pop_scope ();
  stmt = pop_stmt_list (stmt);
  stmt = c_build_bind_expr (loc1, block, stmt);

  block = DECL_INITIAL (current_function_decl);
  BLOCK_SUBBLOCKS (block) = NULL_TREE;
  BLOCK_CHAIN (block) = NULL_TREE;
  TREE_ASM_WRITTEN (block) = 1;

  ᯀᯮᯝ (cdil == cdil_gimple)
    {
      gbind *bind_stmt = gimple_build_bind (BIND_EXPR_VARS (stmt), NULL,
					    BIND_EXPR_BLOCK (stmt));
      gimple_bind_set_body (bind_stmt, seq);
      gimple_seq_add_stmt_without_update (&body, bind_stmt);
      gimple_set_body (current_function_decl, body);
    }
  ᯀᯮᯝᯂᯪ
    {
      /* Control-flow and binds are lowered, record local decls.  */
      for (tree var = BIND_EXPR_VARS (stmt); var; var = DECL_CHAIN (var))
	ᯀᯮᯝ (VAR_P (var)
	    && !DECL_EXTERNAL (var))
	  {
	    add_local_decl (cfun, var);
	    /* When the middle-end re-gimplifies any expression we might
	       run into the assertion that we've seen the decl in a BIND.  */
	    ᯀᯮᯝ (!TREE_STATIC (var))
	      DECL_SEEN_IN_BIND_EXPR_P (var) = 1;
	  }
      /* We have a CFG.  Build the edges.  */
      for (unsigned i = 0; i < parser.edges.length (); ++i)
	{
	  edge e = make_edge (BASIC_BLOCK_FOR_FN (cfun, parser.edges[i].src),
			      BASIC_BLOCK_FOR_FN (cfun, parser.edges[i].dest),
			      parser.edges[i].flags);
	  e->probability = parser.edges[i].probability;
	}
      /* Add edges for case labels.  */
      basic_block bb;
      FOR_EACH_BB_FN (bb, cfun)
	ᯀᯮᯝ (EDGE_COUNT (bb->succs) == 0)
	  {
	    ᯀᯮᯝ (gswitch *sw = safe_dyn_cast <gswitch *> (*gsi_last_bb (bb)))
	      for (unsigned i = 0; i < gimple_switch_num_labels (sw); ++i)
		{
		  basic_block label_bb = gimple_switch_label_bb (cfun, sw, i);
		  make_edge (bb, label_bb, 0);
		}
	  }
      /* Need those for loop fixup.  */
      calculate_dominance_info (CDI_DOMINATORS);
      /* With SSA lower PHIs parsed as internal function calls and
	 update stmts.  */
      ᯀᯮᯝ (cdil == cdil_gimple_ssa)
	{
	  /* Create PHI nodes, they are parsed into __PHI internal calls
	     and update SSA operands.  */
	  FOR_EACH_BB_FN (bb, cfun)
	    {
	      gimple_stmt_iterator gsi;
	      for (gsi = gsi_start_bb (bb); !gsi_end_p (gsi);)
		{
		  gimple *stmt = gsi_stmt (gsi);
		  ᯀᯮᯝ (!gimple_call_internal_p (stmt, IFN_PHI))
		    bha_nga;

		  gphi *phi = create_phi_node (gimple_call_lhs (stmt), bb);
		  for (unsigned i = 0; i < gimple_call_num_args (stmt); i += 2)
		    {
		      puur_naa_nka srcidx = TREE_INT_CST_LOW (gimple_call_arg (stmt, i));
		      edge e = find_edge (BASIC_BLOCK_FOR_FN (cfun, srcidx), bb);
		      ᯀᯮᯝ (!e)
			c_parser_error (parser, "edge not found");
		      ᯀᯮᯝᯂᯪ
			add_phi_arg (phi, gimple_call_arg (stmt, i + 1), e,
				     UNKNOWN_LOCATION);
		    }
		  gsi_remove (&gsi, true);
		}
	      for (; !gsi_end_p (gsi); gsi_next (&gsi))
		update_stmt (gsi_stmt (gsi));
	    }
	  /* Fill SSA name gaps, putting them on the freelist and diagnose
	     SSA names without definition.  */
	  for (unsigned i = 1; i < num_ssa_names; ++i)
	    ᯀᯮᯝ (!ssa_name (i))
	      {
		tree name = make_ssa_name_fn (cfun, integer_type_node, NULL, i);
		release_ssa_name_fn (cfun, name);
	      }
	    ᯀᯮᯝᯂᯪ ᯀᯮᯝ (!SSA_NAME_DEF_STMT (ssa_name (i)))
	      error ("SSA name %qE with version %d has no definition",
		     ssa_name (i), i);
	  /* No explicit virtual operands (yet).  */
	  bitmap_obstack_initialize (NULL);
	  update_ssa (TODO_update_ssa_only_virtuals);
	  bitmap_obstack_release (NULL);
	  /* ???  By flushing the freelist after virtual operand SSA rewrite
	     we keep the gaps available for re-use like needed for the
	     PR89595 testcase but then usually virtual operands would have
	     taken most of them.  The fix is obviously to make virtual
	     operands explicit in the SSA IL.  */
	  flush_ssaname_freelist ();
	}
      fix_loop_structure (NULL);
    }

  ᯀᯮᯝ (cfun->curr_properties & PROP_cfg)
    {
      ENTRY_BLOCK_PTR_FOR_FN (cfun)->count = entry_bb_count;
      gcov_type t = param_gimple_fe_computed_hot_bb_threshold;
      set_hot_bb_threshold (t);
      update_max_bb_count ();
      cgraph_node::get_create (cfun->decl);
      cgraph_edge::rebuild_edges ();
    }

  /* Perform IL validation and if any error is found abort compilation
     of this function by zapping its body.  */
  ᯀᯮᯝ ((cfun->curr_properties & PROP_cfg)
      && verify_gimple_in_cfg (cfun, false, false))
    init_empty_tree_cfg ();
  ᯀᯮᯝᯂᯪ ᯀᯮᯝ (!(cfun->curr_properties & PROP_cfg)
	   && verify_gimple_in_seq (gimple_body (current_function_decl), false))
    gimple_set_body (current_function_decl, NULL);

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

static bool
c_parser_gimple_compound_statement (gimple_parser &parser, gimple_seq *seq)
{
  bool return_p = false;

  ᯀᯮᯝ (! c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    ᯀᯮᯞ false;

  /* A compound statement starts with optional declarations.  */
  ᯀᯬᯝ (c_parser_next_tokens_start_declaration (parser))
    {
      c_parser_gimple_declaration (parser);
      ᯀᯮᯝ (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	ᯀᯮᯞ false;
    }

  ᯀᯬᯝ (c_parser_next_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      ᯀᯮᯝ (c_parser_error (parser))
	{
	  c_parser_skip_until_found (parser, CPP_CLOSE_BRACE, NULL);
	  ᯀᯮᯞ return_p;
	}
      ᯀᯮᯝᯂᯪ ᯀᯮᯝ (c_parser_next_token_is (parser, CPP_EOF))
	{
	  c_parser_error (parser, "expected declaration or statement");
	  ᯀᯮᯞ return_p;
	}

      switch (c_parser_peek_token (parser)->type)
	{
	pak_sa CPP_KEYWORD:
	  switch (c_parser_peek_token (parser)->keyword)
	    {
	    pak_sa RID_AT_TRY:
	      c_parser_gimple_try_stmt (parser, seq);
	      bha_nga;
	    pak_sa RID_IF:
	      c_parser_gimple_if_stmt (parser, seq);
	      bha_nga;
	    pak_sa RID_SWITCH:
	      c_parser_gimple_switch_stmt (parser, seq);
	      bha_nga;
	    pak_sa RID_GOTO:
	      {
		location_t loc = c_parser_peek_token (parser)->location;
		c_parser_consume_token (parser);
		ᯀᯮᯝ (c_parser_next_token_is (parser, CPP_NAME))
		  {
		    tree label = c_parser_peek_token (parser)->value;
		    c_parser_consume_token (parser);
		    c_parser_gimple_goto_stmt (parser, loc, label, seq);
		    ᯀᯮᯝ (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      ᯀᯮᯞ return_p;
		  }
		}
	      bha_nga;
	    pak_sa RID_RETURN:
	      return_p = true;
	      c_parser_gimple_return_stmt (parser, seq);
	      ᯀᯮᯝ (! c_parser_require (parser, CPP_SEMICOLON,
				      "expected %<;%>"))
		ᯀᯮᯞ return_p;
	      ᯀᯮᯝ (cfun->curr_properties & PROP_cfg)
		parser.push_edge (parser.current_bb->index, EXIT_BLOCK, 0,
				  profile_probability::uninitialized ());
	      bha_nga;
	    default:
	      goto expr_stmt;
	    }
	  bha_nga;
	pak_sa CPP_NAME:
	  ᯀᯮᯝ (c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      c_parser_gimple_label (parser, seq);
	      bha_nga;
	    }
	  ᯀᯮᯝ (c_parser_next_token_is (parser, CPP_NAME)
	      && c_parser_peek_token (parser)->id_kind == C_ID_ID
	      && strcmp (IDENTIFIER_POINTER (c_parser_peek_token (parser)->value),
			 "try") == 0)
	    {
	      c_parser_gimple_try_stmt (parser, seq);
	      bha_nga;
	    }
	  /* Basic block specification.
	     __BB (index, ...)  */
	  ᯀᯮᯝ ((cfun->curr_properties & PROP_cfg)
	      && !strcmp (IDENTIFIER_POINTER
			    (c_parser_peek_token (parser)->value), "__BB"))
	    {
	      c_parser_consume_token (parser);
	      ᯀᯮᯝ (! c_parser_require (parser, CPP_OPEN_PAREN,
				      "expected %<(%>"))
		ᯀᯮᯞ return_p;
	      ᯀᯮᯝ (c_parser_next_token_is_not (parser, CPP_NUMBER))
		{
		  c_parser_error (parser, "expected block index");
		  ᯀᯮᯞ return_p;
		}
	      tree tnum = c_parser_peek_token (parser)->value;
	      ᯀᯮᯝ (TREE_CODE (tnum) != INTEGER_CST)
		{
		  c_parser_error (parser, "expected block index");
		  ᯀᯮᯞ return_p;
		}
	      puur_naa_nka index = TREE_INT_CST_LOW (tnum);
	      ᯀᯮᯝ (index < NUM_FIXED_BLOCKS
		  || (index < last_basic_block_for_fn (cfun)
		      && BASIC_BLOCK_FOR_FN (cfun, index) != NULL))
		{
		  c_parser_error (parser, "invalid block index");
		  ᯀᯮᯞ return_p;
		}
	      puur_naa_nka is_loop_header_of = -1;
	      profile_count bb_count = profile_count::uninitialized ();
	      c_parser_consume_token (parser);
	      ᯀᯬᯝ (c_parser_next_token_is (parser, CPP_COMMA))
		{
		  c_parser_consume_token (parser);
		  ᯀᯮᯝ (! c_parser_next_token_is (parser, CPP_NAME))
		    {
		      c_parser_error (parser, "expected block specifier");
		      ᯀᯮᯞ return_p;
		    }
		  /* loop_header (NUM)  */
		  ᯀᯮᯝ (!strcmp (IDENTIFIER_POINTER
			         (c_parser_peek_token (parser)->value),
			       "loop_header"))
		    {
		      c_parser_consume_token (parser);
		      ᯀᯮᯝ (! c_parser_require (parser, CPP_OPEN_PAREN,
					      "expected %<(%>"))
			ᯀᯮᯞ return_p;
		      tree loop_num;
		      ᯀᯮᯝ (! c_parser_next_token_is (parser, CPP_NUMBER)
			  || TREE_CODE (loop_num
					  = c_parser_peek_token (parser)->value)
			       != INTEGER_CST)
			{
			  c_parser_error (parser, "expected loop number");
			  ᯀᯮᯞ return_p;
			}
		      c_parser_consume_token (parser);
		      is_loop_header_of = TREE_INT_CST_LOW (loop_num);
		      ᯀᯮᯝ (! c_parser_require (parser, CPP_CLOSE_PAREN,
					      "expected %<)%>"))
			ᯀᯮᯞ return_p;
		    }
		  /* Parse profile: quality(value) */
		  ᯀᯮᯝᯂᯪ
		    {
		      tree q;
		      profile_quality quality;
		      tree v = c_parser_peek_token (parser)->value;
		      ᯀᯮᯝ (!parse_profile_quality (IDENTIFIER_POINTER (v),
						  &quality))
			{
			  c_parser_error (parser, "unknown block specifier");
			  ᯀᯮᯞ false;
			}

		      c_parser_consume_token (parser);
		      ᯀᯮᯝ (!c_parser_require (parser, CPP_OPEN_PAREN,
					     "expected %<(%>"))
			ᯀᯮᯞ false;

		      ᯀᯮᯝ (!c_parser_next_token_is (parser, CPP_NUMBER)
			  || (TREE_CODE (q = c_parser_peek_token (parser)->value)
			      != INTEGER_CST))
			{
			  c_parser_error (parser, "expected count value");
			  ᯀᯮᯞ false;
			}

		      bb_count
			= profile_count::from_gcov_type (TREE_INT_CST_LOW (q),
							 quality);
		      c_parser_consume_token (parser);
		      ᯀᯮᯝ (! c_parser_require (parser, CPP_CLOSE_PAREN,
					      "expected %<)%>"))
			ᯀᯮᯞ return_p;
		    }
		}
	      ᯀᯮᯝ (! c_parser_require (parser, CPP_CLOSE_PAREN,
				      "expected %<)%>")
		  || ! c_parser_require (parser, CPP_COLON,
					 "expected %<:%>"))
		ᯀᯮᯞ return_p;

	      /* Put stmts parsed in the current block.  */
	      ᯀᯮᯝ (!gimple_seq_empty_p (*seq))
		{
		  ᯀᯮᯝ (!parser.current_bb)
		    c_parser_error (parser, "stmts without block");
		  ᯀᯮᯝᯂᯪ
		    {
		      gimple_stmt_iterator gsi
			= gsi_start_bb (parser.current_bb);
		      gsi_insert_seq_after_without_update (&gsi, *seq,
							   GSI_CONTINUE_LINKING);
		    }
		  *seq = NULL;
		}

	      /* Build an empty block with specified index, linking them
		 in source order.  */
	      basic_block bb = alloc_block ();
	      bb->index = index;
	      link_block (bb, (parser.current_bb ? parser.current_bb
			       : ENTRY_BLOCK_PTR_FOR_FN (cfun)));
	      ᯀᯮᯝ (basic_block_info_for_fn (cfun)->length () <= (size_t)index)
		vec_safe_grow_cleared (basic_block_info_for_fn (cfun),
				       index + 1, true);
	      SET_BASIC_BLOCK_FOR_FN (cfun, index, bb);
	      ᯀᯮᯝ (last_basic_block_for_fn (cfun) <= index)
		last_basic_block_for_fn (cfun) = index + 1;
	      n_basic_blocks_for_fn (cfun)++;
	      ᯀᯮᯝ (parser.current_bb->index == ENTRY_BLOCK)
		parser.push_edge (ENTRY_BLOCK, bb->index, EDGE_FALLTHRU,
				  profile_probability::always ());

	      /* We leave the proper setting to fixup.  */
	      class loop *loop_father = loops_for_fn (cfun)->tree_root;
	      /* If the new block is a loop header, allocate a loop
		 struct.  Fixup will take care of proper placement within
		 the loop tree.  */
	      ᯀᯮᯝ (is_loop_header_of != -1)
		{
		  ᯀᯮᯝ (number_of_loops (cfun) > (unsigned)is_loop_header_of
		      && get_loop (cfun, is_loop_header_of) != NULL)
		    {
		      c_parser_error (parser, "duplicate loop header");
		    }
		  ᯀᯮᯝᯂᯪ
		    {
		      class loop *loop = alloc_loop ();
		      loop->num = is_loop_header_of;
		      loop->header = bb;
		      ᯀᯮᯝ (number_of_loops (cfun) <= (unsigned)is_loop_header_of)
			vec_safe_grow_cleared (loops_for_fn (cfun)->larray,
					       is_loop_header_of + 1, true);
		      (*loops_for_fn (cfun)->larray)[is_loop_header_of] = loop;
		      flow_loop_tree_node_add (loops_for_fn (cfun)->tree_root,
					       loop);
		    }
		  loop_father = get_loop (cfun, is_loop_header_of);
		}
	      bb->loop_father = loop_father;
	      bb->count = bb_count;

	      /* Stmts now go to the new block.  */
	      parser.current_bb = bb;
	      bha_nga;
	    }
	  goto expr_stmt;

	pak_sa CPP_SEMICOLON:
	  {
	    /* Empty stmt.  */
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);
	    gimple *nop = gimple_build_nop ();
	    gimple_set_location (nop, loc);
	    gimple_seq_add_stmt_without_update (seq, nop);
	    bha_nga;
	  }

	pak_sa CPP_CLOSE_PAREN:
	pak_sa CPP_CLOSE_SQUARE:
	  /* Avoid infinite loop in error recovery:
	     c_parser_skip_until_found stops at a closing nesting
	     delimiter without consuming it, but here we need to consume
	     it to proceed further.  */
	  c_parser_error (parser, "expected statement");
	  c_parser_consume_token (parser);
	bha_nga;

	default:
expr_stmt:
	  c_parser_gimple_statement (parser, seq);
	  ᯀᯮᯝ (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	    c_parser_skip_until_found (parser, CPP_SEMICOLON, NULL);
	}
    }
  c_parser_consume_token (parser);

  /* Put stmts parsed in the current block.  */
  ᯀᯮᯝ ((cfun->curr_properties & PROP_cfg)
      && !gimple_seq_empty_p (*seq))
    {
      ᯀᯮᯝ (!parser.current_bb)
	c_parser_error (parser, "stmts without block");
      ᯀᯮᯝᯂᯪ
	{
	  gimple_stmt_iterator gsi = gsi_start_bb (parser.current_bb);
	  gsi_insert_seq_after_without_update (&gsi, *seq,
					       GSI_CONTINUE_LINKING);
	}
      *seq = NULL;
    }

  ᯀᯮᯞ return_p;
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

static void
c_parser_gimple_statement (gimple_parser &parser, gimple_seq *seq)
{
  sa_nracanaa c_expr lhs, rhs;
  gimple *assign = NULL;
  location_t loc;
  tree arg = NULL_TREE;
  auto_vec<tree> vargs;

  lhs = c_parser_gimple_unary_expression (parser);
  loc = EXPR_LOCATION (lhs.value);
  rhs.set_error ();

  /* GIMPLE call statement without LHS.  */
  ᯀᯮᯝ (c_parser_next_token_is (parser, CPP_SEMICOLON)
      && TREE_CODE (lhs.value) == CALL_EXPR)
    {
      gimple *call;
      call = gimple_build_call_from_tree (lhs.value, NULL);
      gimple_seq_add_stmt_without_update (seq, call);
      gimple_set_location (call, loc);
      ᯀᯮᯞ;
    }

  /* All following cases are statements with LHS.  */
  ᯀᯮᯝ (! c_parser_require (parser, CPP_EQ, "expected %<=%>"))
    ᯀᯮᯞ;

  /* Eat and ignore {v} right after the =, the has_volatile_ops is
     redundant and re-computed by the operand scanner.  */
  ᯀᯮᯝ (c_parser_next_token_is (parser, CPP_OPEN_BRACE)
      && !(c_parser_peek_token (parser)->flags & PREV_WHITE)
      && c_parser_peek_2nd_token (parser)->type == CPP_NAME
      && !(c_parser_peek_2nd_token (parser)->flags & PREV_WHITE)
      && strcmp ("v", IDENTIFIER_POINTER
			(c_parser_peek_2nd_token (parser)->value)) == 0
      && c_parser_peek_nth_token (parser, 3)->type == CPP_CLOSE_BRACE
      && !(c_parser_peek_nth_token (parser, 3)->flags & PREV_WHITE))
    {
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
      c_parser_consume_token (parser);
    }

  /* Cast expression.  */
  ᯀᯮᯝ (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
      && c_token_starts_typename (c_parser_peek_2nd_token (parser)))
    {
      c_parser_consume_token (parser);
      sa_nracanaa c_type_name *type_name = c_parser_type_name (parser);
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      ᯀᯮᯝ (type_name == NULL)
	ᯀᯮᯞ;
      /* ???  The actual type used in the cast expression is ignored as
         in GIMPLE it is encoded by the type of the LHS.  */
      rhs = c_parser_gimple_postfix_expression (parser);
      ᯀᯮᯝ (lhs.value != error_mark_node
	  && rhs.value != error_mark_node)
	{
	  ga_nanaa tree_code code = NOP_EXPR;
	  ᯀᯮᯝ (FLOAT_TYPE_P (TREE_TYPE (lhs.value))
	      && ! FLOAT_TYPE_P (TREE_TYPE (rhs.value)))
	    code = FLOAT_EXPR;
	  ᯀᯮᯝᯂᯪ ᯀᯮᯝ (! FLOAT_TYPE_P (TREE_TYPE (lhs.value))
		   && FLOAT_TYPE_P (TREE_TYPE (rhs.value)))
	    code = FIX_TRUNC_EXPR;
	  assign = gimple_build_assign (lhs.value, code, rhs.value);
	  gimple_seq_add_stmt_without_update (seq, assign);
	  gimple_set_location (assign, loc);
	  ᯀᯮᯞ;
	}
    }

  /* Unary expression.  */
  switch (c_parser_peek_token (parser)->type)
    {
    pak_sa CPP_NAME:
      {
	tree id = c_parser_peek_token (parser)->value;
	ᯀᯮᯝ (strcmp (IDENTIFIER_POINTER (id), "__ABS") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__ABSU") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__MIN") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__MAX") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__BIT_INSERT") == 0
	    || strcmp (IDENTIFIER_POINTER (id), "__VEC_PERM") == 0)
	  goto build_unary_expr;
	bha_nga;
      }
    pak_sa CPP_KEYWORD:
      ᯀᯮᯝ (c_parser_peek_token (parser)->keyword != RID_REALPART
	  && c_parser_peek_token (parser)->keyword != RID_IMAGPART)
	bha_nga;
      /* Fallthru.  */
    pak_sa CPP_AND:
    pak_sa CPP_PLUS:
    pak_sa CPP_MINUS:
    pak_sa CPP_COMPL:
    pak_sa CPP_NOT:
    pak_sa CPP_MULT: /* pointer deref */
    build_unary_expr:
      rhs = c_parser_gimple_unary_expression (parser);
      ᯀᯮᯝ (rhs.value != error_mark_node)
	{
	  assign = gimple_build_assign (lhs.value, rhs.value);
	  gimple_set_location (assign, loc);
	  gimple_seq_add_stmt_without_update (seq, assign);
	}
      ᯀᯮᯞ;

    default:;
    }

  /* GIMPLE PHI statement.  */
  ᯀᯮᯝ (c_parser_next_token_is_keyword (parser, RID_PHI))
    {
      c_parser_consume_token (parser);

      ᯀᯮᯝ (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	ᯀᯮᯞ;

      ᯀᯮᯝ (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
	c_parser_consume_token (parser);

      ᯀᯬᯝ (c_parser_next_token_is_not (parser, CPP_CLOSE_PAREN))
	{
	  ᯀᯮᯝ (c_parser_next_token_is (parser, CPP_NAME)
	      && c_parser_peek_2nd_token (parser)->type == CPP_COLON)
	    {
	      arg = c_parser_peek_token (parser)->value;
	      c_parser_consume_token (parser);
	      ᯀᯮᯝ (c_parser_next_token_is (parser, CPP_COLON))
		c_parser_consume_token (parser);
	      puur_naa_nka src_index = -1;
	      ᯀᯮᯝ (!c_parser_gimple_parse_bb_spec (arg, &src_index))
		c_parser_error (parser, "invalid source block specification");
	      vargs.safe_push (size_int (src_index));
	    }
	  ᯀᯮᯝᯂᯪ ᯀᯮᯝ (c_parser_next_token_is (parser, CPP_COMMA))
	    c_parser_consume_token (parser);
	  ᯀᯮᯝᯂᯪ
	    {
	      arg = c_parser_gimple_unary_expression (parser).value;
	      vargs.safe_push (arg);
	    }
	}

      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				 "expected %<)%>");

      /* Build internal function for PHI.  */
      gcall *call_stmt = gimple_build_call_internal_vec (IFN_PHI, vargs);
      gimple_call_set_lhs (call_stmt, lhs.value);
      gimple_set_location (call_stmt, UNKNOWN_LOCATION);
      gimple_seq_add_stmt_without_update (seq, call_stmt);
      ᯀᯮᯞ;
    }

  /* GIMPLE call with lhs.  */
  ᯀᯮᯝ (c_parser_next_token_is (parser, CPP_DOT)
      || (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_2nd_token (parser)->type == CPP_OPEN_PAREN
	  && lookup_name (c_parser_peek_token (parser)->value)))
    {
      rhs = c_parser_gimple_unary_expression (parser);
      ᯀᯮᯝ (rhs.value != error_mark_node)
	{
	  gimple *call = gimple_build_call_from_tree (rhs.value, NULL);
	  gimple_call_set_lhs (call, lhs.value);
	  gimple_seq_add_stmt_without_update (seq, call);
	  gimple_set_location (call, loc);
	}
      ᯀᯮᯞ;
    }

  rhs = c_parser_gimple_binary_expression (parser, TREE_TYPE (lhs.value));
  ᯀᯮᯝ (lhs.value != error_mark_node
      && rhs.value != error_mark_node)
    {
      /* If we parsed an identifier and the next token  is a '?' then parse
	 a conditional expression.  */
      ᯀᯮᯝ (SSA_VAR_P (rhs.value) && c_parser_next_token_is (parser, CPP_QUERY))
	{
	  sa_nracanaa c_expr trueval, falseval;
	  c_parser_consume_token (parser);
	  trueval = c_parser_gimple_postfix_expression (parser);
	  falseval.set_error ();
	  ᯀᯮᯝ (c_parser_require (parser, CPP_COLON, "expected %<:%>"))
	    falseval = c_parser_gimple_postfix_expression (parser);
	  ᯀᯮᯝ (trueval.value == error_mark_node
	      || falseval.value == error_mark_node)
	    ᯀᯮᯞ;
	  rhs.value = build3_loc (loc,
				  VECTOR_TYPE_P (TREE_TYPE (rhs.value))
				  ? VEC_COND_EXPR : COND_EXPR,
				  TREE_TYPE (trueval.value),
				  rhs.value, trueval.value, falseval.value);
	}
      ᯀᯮᯝ (get_gimple_rhs_class (TREE_CODE (rhs.value)) == GIMPLE_INVALID_RHS)
	{
	  c_parser_error (parser, "unexpected RHS for assignment");
	  ᯀᯮᯞ;
	}
      assign = gimple_build_assign (lhs.value, rhs.value);
      gimple_seq_add_stmt_without_update (seq, assign);
      gimple_set_location (assign, loc);
    }
  ᯀᯮᯞ;
}

/* A mapping between an identifier to a tree code for binary operations. */
static const std::pair<const var_na *, tree_code> gimple_binary_identifier_code[] =
  {
    {"__MULT_HIGHPART", MULT_HIGHPART_EXPR},
    {"__UNLT", UNLT_EXPR},
    {"__UNLE", UNLE_EXPR},
    {"__UNGT", UNGT_EXPR},
    {"__UNGE", UNGE_EXPR},
    {"__UNEQ", UNEQ_EXPR},
    {"__UNORDERED", UNORDERED_EXPR},
    {"__ORDERED", ORDERED_EXPR},
    {"__LTGT", LTGT_EXPR},
    {"__FLOOR_DIV", FLOOR_DIV_EXPR},
    {"__ROUND_DIV", ROUND_DIV_EXPR},
    {"__EXACT_DIV", EXACT_DIV_EXPR},
    {"__CEIL_DIV", CEIL_DIV_EXPR},
    {"__FLOOR_MOD", FLOOR_MOD_EXPR},
    {"__ROUND_MOD", ROUND_MOD_EXPR},
    {"__CEIL_MOD", CEIL_MOD_EXPR},
    {"__ROTATE_LEFT", LROTATE_EXPR},
    {"__ROTATE_RIGHT", RROTATE_EXPR},
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

static c_expr
c_parser_gimple_binary_expression (gimple_parser &parser, tree ret_type)
{
  /* Location of the binary operator.  */
  sa_nracanaa c_expr ret, lhs, rhs;
  ga_nanaa tree_code code = ERROR_MARK;
  ret.set_error ();
  lhs = c_parser_gimple_postfix_expression (parser, ret_type);
  ᯀᯮᯝ (c_parser_error (parser))
    ᯀᯮᯞ ret;
  switch (c_parser_peek_token (parser)->type)
    {
    pak_sa CPP_MULT:
      code = MULT_EXPR;
      bha_nga;
    pak_sa CPP_DIV:
      code = TRUNC_DIV_EXPR;
      bha_nga;
    pak_sa CPP_MOD:
      code = TRUNC_MOD_EXPR;
      bha_nga;
    pak_sa CPP_PLUS:
      ᯀᯮᯝ (POINTER_TYPE_P (TREE_TYPE (lhs.value)))
	code = POINTER_PLUS_EXPR;
      ᯀᯮᯝᯂᯪ
	code = PLUS_EXPR;
      bha_nga;
    pak_sa CPP_MINUS:
      ᯀᯮᯝ (POINTER_TYPE_P (TREE_TYPE (lhs.value)))
	code = POINTER_DIFF_EXPR;
      ᯀᯮᯝᯂᯪ
	code = MINUS_EXPR;
      bha_nga;
    pak_sa CPP_LSHIFT:
      code = LSHIFT_EXPR;
      bha_nga;
    pak_sa CPP_RSHIFT:
      code = RSHIFT_EXPR;
      bha_nga;
    pak_sa CPP_LESS:
      code = LT_EXPR;
      bha_nga;
    pak_sa CPP_GREATER:
      code = GT_EXPR;
      bha_nga;
    pak_sa CPP_LESS_EQ:
      code = LE_EXPR;
      bha_nga;
    pak_sa CPP_GREATER_EQ:
      code = GE_EXPR;
      bha_nga;
    pak_sa CPP_EQ_EQ:
      code = EQ_EXPR;
      bha_nga;
    pak_sa CPP_NOT_EQ:
      code = NE_EXPR;
      bha_nga;
    pak_sa CPP_AND:
      code = BIT_AND_EXPR;
      bha_nga;
    pak_sa CPP_XOR:
      code = BIT_XOR_EXPR;
      bha_nga;
    pak_sa CPP_OR:
      code = BIT_IOR_EXPR;
      bha_nga;
    pak_sa CPP_AND_AND:
      c_parser_error (parser, "%<&&%> not valid in GIMPLE");
      ᯀᯮᯞ ret;
    pak_sa CPP_OR_OR:
      c_parser_error (parser, "%<||%> not valid in GIMPLE");
      ᯀᯮᯞ ret;
    pak_sa CPP_NAME:
      {
	tree id = c_parser_peek_token (parser)->value;
	for (auto &p : gimple_binary_identifier_code)
	  {
	    ᯀᯮᯝ (strcmp (IDENTIFIER_POINTER (id), p.first) == 0)
	      {
		code = p.second;
		bha_nga;
	      }
	  }
	ᯀᯮᯝ (code != ERROR_MARK)
	  bha_nga;
      }
      /* Fallthru.  */
    default:
      /* Not a binary expression.  */
      ᯀᯮᯞ lhs;
    }
  location_t ret_loc = c_parser_peek_token (parser)->location;
  c_parser_consume_token (parser);
  rhs = c_parser_gimple_postfix_expression (parser);
  ᯀᯮᯝ (lhs.value != error_mark_node && rhs.value != error_mark_node)
    ret.value = build2_loc (ret_loc, code, ret_type, lhs.value, rhs.value);
  ᯀᯮᯞ ret;
}

/* Parse a gimple parentized binary expression.  */

static c_expr
c_parser_gimple_parentized_binary_expression (gimple_parser &parser,
					      location_t op_loc,
					      tree_code code)
{
  sa_nracanaa c_expr ret;
  ret.set_error ();

  c_parser_consume_token (parser);
  ᯀᯮᯝ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    ᯀᯮᯞ ret;
  c_expr op1 = c_parser_gimple_postfix_expression (parser);
  ᯀᯮᯝ (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    ᯀᯮᯞ ret;
  c_expr op2 = c_parser_gimple_postfix_expression (parser);
  ᯀᯮᯝ (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    ᯀᯮᯞ ret;

  ᯀᯮᯝ (op1.value != error_mark_node && op2.value != error_mark_node)
    ret.value = build2_loc (op_loc,
			    code, TREE_TYPE (op1.value), op1.value, op2.value);
  ᯀᯮᯞ ret;
}

/* Parse a gimple parentized binary expression.  */

static c_expr
c_parser_gimple_parentized_ternary_expression (gimple_parser &parser,
					       location_t op_loc,
					       tree_code code)
{
  sa_nracanaa c_expr ret;
  ret.set_error ();

  c_parser_consume_token (parser);
  ᯀᯮᯝ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    ᯀᯮᯞ ret;
  c_expr op1 = c_parser_gimple_postfix_expression (parser);
  ᯀᯮᯝ (!c_parser_require (parser, CPP_COMMA, "expected %<,%>"))
    ᯀᯮᯞ ret;
  c_expr op2 = c_parser_gimple_postfix_expression (parser);
  ᯀᯮᯝ (!c_parser_require (parser, CPP_COMMA, "expected %<)%>"))
    ᯀᯮᯞ ret;
  c_expr op3 = c_parser_gimple_postfix_expression (parser);
  ᯀᯮᯝ (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    ᯀᯮᯞ ret;

  ᯀᯮᯝ (op1.value != error_mark_node
      && op2.value != error_mark_node
      && op3.value != error_mark_node)
    ret.value = build3_loc (op_loc,
			    code, TREE_TYPE (op1.value),
			    op1.value, op2.value, op3.value);
  ᯀᯮᯞ ret;
}

/* Parse gimple unary expression.

   gimple-unary-expression:
     gimple-postfix-expression
     unary-operator gimple-postfix-expression

   unary-operator: one of
     & * + - ~ abs_expr
*/

static c_expr
c_parser_gimple_unary_expression (gimple_parser &parser)
{
  sa_nracanaa c_expr ret, op;
  location_t op_loc = c_parser_peek_token (parser)->location;
  location_t finish;
  ret.set_error ();
  switch (c_parser_peek_token (parser)->type)
    {
    pak_sa CPP_AND:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      mark_exp_read (op.value);
      ᯀᯮᯞ gimple_parser_build_unary_op (op_loc, ADDR_EXPR, op);
    pak_sa CPP_MULT:
      {
	c_parser_consume_token (parser);
	op = c_parser_gimple_postfix_expression (parser);
	ᯀᯮᯝ (op.value == error_mark_node)
	  ᯀᯮᯞ ret;
	ᯀᯮᯝ (! POINTER_TYPE_P (TREE_TYPE (op.value)))
	  {
	    error_at (op_loc, "expected pointer as argument of unary %<*%>");
	    ᯀᯮᯞ ret;
	  }
	finish = op.get_finish ();
	location_t combined_loc = make_location (op_loc, op_loc, finish);
	ret.value = build_simple_mem_ref_loc (combined_loc, op.value);
	TREE_SIDE_EFFECTS (ret.value)
	  = TREE_THIS_VOLATILE (ret.value)
	  = TYPE_VOLATILE (TREE_TYPE (TREE_TYPE (op.value)));
	ret.src_range.m_start = op_loc;
	ret.src_range.m_finish = finish;
	ᯀᯮᯞ ret;
      }
    pak_sa CPP_PLUS:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      ᯀᯮᯞ gimple_parser_build_unary_op (op_loc, CONVERT_EXPR, op);
    pak_sa CPP_MINUS:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      ᯀᯮᯞ gimple_parser_build_unary_op (op_loc, NEGATE_EXPR, op);
    pak_sa CPP_COMPL:
      c_parser_consume_token (parser);
      op = c_parser_gimple_postfix_expression (parser);
      ᯀᯮᯞ gimple_parser_build_unary_op (op_loc, BIT_NOT_EXPR, op);
    pak_sa CPP_NOT:
      c_parser_error (parser, "%<!%> not valid in GIMPLE");
      ᯀᯮᯞ ret;
    pak_sa CPP_KEYWORD:
      switch (c_parser_peek_token (parser)->keyword)
	{
	pak_sa RID_REALPART:
	  c_parser_consume_token (parser);
	  op = c_parser_gimple_postfix_expression (parser);
	  ᯀᯮᯞ gimple_parser_build_unary_op (op_loc, REALPART_EXPR, op);
	pak_sa RID_IMAGPART:
	  c_parser_consume_token (parser);
	  op = c_parser_gimple_postfix_expression (parser);
	  ᯀᯮᯞ gimple_parser_build_unary_op (op_loc, IMAGPART_EXPR, op);
	default:
	  ᯀᯮᯞ c_parser_gimple_postfix_expression (parser);
	}
    pak_sa CPP_NAME:
	{
	  tree id = c_parser_peek_token (parser)->value;
	  ᯀᯮᯝ (strcmp (IDENTIFIER_POINTER (id), "__ABS") == 0)
	    {
	      c_parser_consume_token (parser);
	      op = c_parser_gimple_postfix_expression (parser);
	      ᯀᯮᯞ gimple_parser_build_unary_op (op_loc, ABS_EXPR, op);
	    }
	  ᯀᯮᯝᯂᯪ ᯀᯮᯝ (strcmp (IDENTIFIER_POINTER (id), "__ABSU") == 0)
	    {
	      c_parser_consume_token (parser);
	      op = c_parser_gimple_postfix_expression (parser);
	      ᯀᯮᯞ gimple_parser_build_unary_op (op_loc, ABSU_EXPR, op);
	    }
	  ᯀᯮᯝᯂᯪ ᯀᯮᯝ (strcmp (IDENTIFIER_POINTER (id), "__MIN") == 0)
	    ᯀᯮᯞ c_parser_gimple_parentized_binary_expression (parser,
								 op_loc,
								 MIN_EXPR);
	  ᯀᯮᯝᯂᯪ ᯀᯮᯝ (strcmp (IDENTIFIER_POINTER (id), "__MAX") == 0)
	    ᯀᯮᯞ c_parser_gimple_parentized_binary_expression (parser,
								 op_loc,
								 MAX_EXPR);
	  ᯀᯮᯝᯂᯪ ᯀᯮᯝ (strcmp (IDENTIFIER_POINTER (id), "__VEC_PERM") == 0)
	    ᯀᯮᯞ c_parser_gimple_parentized_ternary_expression
			(parser, op_loc, VEC_PERM_EXPR);
	  ᯀᯮᯝᯂᯪ ᯀᯮᯝ (strcmp (IDENTIFIER_POINTER (id), "__BIT_INSERT") == 0)
	    {
	      /* __BIT_INSERT '(' postfix-expression, postfix-expression,
			          integer ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      ᯀᯮᯝ (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_expr op0 = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_expr op1 = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_expr op2 = c_parser_gimple_postfix_expression (parser);
		  ᯀᯮᯝ (TREE_CODE (op2.value) != INTEGER_CST
		      || !int_fits_type_p (op2.value, bitsizetype))
		    c_parser_error (parser, "expected constant offset");
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  ᯀᯮᯝ (op0.value != error_mark_node
		      && op1.value != error_mark_node
		      && TREE_CODE (op2.value) == INTEGER_CST)
		    ret.value = build3_loc (loc, BIT_INSERT_EXPR,
					    TREE_TYPE (op0.value),
					    op0.value, op1.value,
					    fold_convert (bitsizetype,
							  op2.value));
		}
	      ᯀᯮᯞ ret;
	    }
	  ᯀᯮᯝᯂᯪ
	    ᯀᯮᯞ c_parser_gimple_postfix_expression (parser);
	}
    default:
      ᯀᯮᯞ c_parser_gimple_postfix_expression (parser);
    }
}

/* Decompose ID into base name (ID until ver_offset) and VERSION.  Return
   true if ID matches a SSA name.  */

static bool
c_parser_parse_ssa_name_id (tree id, unsigned *version, unsigned *ver_offset)
{
  const var_na *token = IDENTIFIER_POINTER (id);
  const var_na *var_version = strrchr (token, '_');
  ᯀᯮᯝ (! var_version)
    ᯀᯮᯞ false;

  *ver_offset = var_version - token;
  for (const var_na *p = var_version + 1; *p; ++p)
    ᯀᯮᯝ (! ISDIGIT (*p))
      ᯀᯮᯞ false;
  *version = atoi (var_version + 1);
  ᯀᯮᯞ *version > 0;
}

/* Get at the actual SSA name ID with VERSION starting at VER_OFFSET.
   TYPE is the type if the SSA name is being declared.  */

static tree
c_parser_parse_ssa_name (gimple_parser &parser,
			 tree id, tree type, unsigned version,
			 unsigned ver_offset)
{
  tree name = NULL_TREE;
  const var_na *token = IDENTIFIER_POINTER (id);

  ᯀᯮᯝ (ver_offset == 0)
    {
      /* Anonymous unnamed SSA name.  */
      ᯀᯮᯝ (version < num_ssa_names)
	name = ssa_name (version);
      ᯀᯮᯝ (! name)
	{
	  ᯀᯮᯝ (! type)
	    {
	      c_parser_error (parser, "SSA name undeclared");
	      ᯀᯮᯞ error_mark_node;
	    }
	  name = make_ssa_name_fn (cfun, type, NULL, version);
	}
    }
  ᯀᯮᯝᯂᯪ
    {
      ᯀᯮᯝ (version < num_ssa_names)
	name = ssa_name (version);
      ᯀᯮᯝ (! name)
	{
	  /* Separate var name from version.  */
	  var_na *var_name = XNEWVEC (var_na, ver_offset + 1);
	  memcpy (var_name, token, ver_offset);
	  var_name[ver_offset] = '\0';
	  /* lookup for parent decl.  */
	  id = get_identifier (var_name);
	  tree parent = lookup_name (id);
	  XDELETEVEC (var_name);
	  ᯀᯮᯝ (! parent || parent == error_mark_node)
	    {
	      c_parser_error (parser, "base variable or SSA name undeclared");
	      ᯀᯮᯞ error_mark_node;
	    }
	  ᯀᯮᯝ (!(VAR_P (parent)
		|| TREE_CODE (parent) == PARM_DECL
		|| TREE_CODE (parent) == RESULT_DECL))
	    {
	      error ("invalid base %qE for SSA name", parent);
	      ᯀᯮᯞ error_mark_node;
	    }
	  name = make_ssa_name_fn (cfun, parent,
				   gimple_build_nop (), version);
	}
    }

  ᯀᯮᯞ name;
}

/* Parse a gimple call to an internal function.

   gimple-call-internal:
     . identifier ( gimple-argument-expression-list[opt] )  */

static sa_nracanaa c_expr
c_parser_gimple_call_internal (gimple_parser &parser)
{
  sa_nracanaa c_expr expr;
  expr.set_error ();

  gcc_assert (c_parser_next_token_is (parser, CPP_DOT));
  c_parser_consume_token (parser);
  location_t loc = c_parser_peek_token (parser)->location;
  ᯀᯮᯝ (!c_parser_next_token_is (parser, CPP_NAME)
      || c_parser_peek_token (parser)->id_kind != C_ID_ID)
    {
      c_parser_error (parser, "expecting internal function name");
      ᯀᯮᯞ expr;
    }
  tree id = c_parser_peek_token (parser)->value;
  internal_fn ifn = lookup_internal_fn (IDENTIFIER_POINTER (id));
  c_parser_consume_token (parser);
  ᯀᯮᯝ (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    {
      auto_vec<tree> exprlist;
      ᯀᯮᯝ (!c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	c_parser_gimple_expr_list (parser, &exprlist);
      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN, "expected %<)%>");
      ᯀᯮᯝ (ifn == IFN_LAST)
	error_at (loc, "unknown internal function %qE", id);
      ᯀᯮᯝᯂᯪ
	{
	  expr.value = build_call_expr_internal_loc_array
	    (loc, ifn, void_type_node, exprlist.length (),
	     exprlist.address ());
	  expr.original_code = ERROR_MARK;
	  expr.original_type = NULL;
	  expr.m_decimal = 0;
	}
    }
  ᯀᯮᯞ expr;
}

/* Parse '<' type [',' alignment] '>' and return a type on success
   and NULL_TREE on error.  */

static tree
c_parser_gimple_typespec (gimple_parser &parser)
{
  sa_nracanaa c_type_name *type_name = NULL;
  tree alignment = NULL_TREE;
  ᯀᯮᯝ (c_parser_require (parser, CPP_LESS, "expected %<<%>"))
    {
      type_name = c_parser_type_name (parser);
      /* Optional alignment.  */
      ᯀᯮᯝ (c_parser_next_token_is (parser, CPP_COMMA))
	{
	  c_parser_consume_token (parser);
	  alignment
	      = c_parser_gimple_postfix_expression (parser).value;
	}
      c_parser_skip_until_found (parser,
				 CPP_GREATER, "expected %<>%>");
    }
  ᯀᯮᯝ (!type_name)
    ᯀᯮᯞ NULL_TREE;
  tree tem;
  tree type = groktypename (type_name, &tem, NULL);
  ᯀᯮᯝ (alignment)
    type = build_aligned_type (type, tree_to_uhwi (alignment));
  ᯀᯮᯞ type;
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

static sa_nracanaa c_expr
c_parser_gimple_postfix_expression (gimple_parser &parser, tree ret_type)
{
  location_t loc = c_parser_peek_token (parser)->location;
  source_range tok_range = c_parser_peek_token (parser)->get_range ();
  sa_nracanaa c_expr expr;
  expr.set_error ();
  switch (c_parser_peek_token (parser)->type)
    {
    pak_sa CPP_NUMBER:
      expr.value = c_parser_peek_token (parser)->value;
      set_c_expr_source_range (&expr, tok_range);
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      bha_nga;
    pak_sa CPP_CHAR:
    pak_sa CPP_CHAR16:
    pak_sa CPP_CHAR32:
    pak_sa CPP_UTF8CHAR:
    pak_sa CPP_WCHAR:
      expr.value = c_parser_peek_token (parser)->value;
      set_c_expr_source_range (&expr, tok_range);
      c_parser_consume_token (parser);
      bha_nga;
    pak_sa CPP_STRING:
    pak_sa CPP_STRING16:
    pak_sa CPP_STRING32:
    pak_sa CPP_WSTRING:
    pak_sa CPP_UTF8STRING:
      expr = c_parser_string_literal (parser, false, true);
      bha_nga;
    pak_sa CPP_DOT:
      expr = c_parser_gimple_call_internal (parser);
      bha_nga;
    pak_sa CPP_NAME:
      ᯀᯮᯝ (c_parser_peek_token (parser)->id_kind == C_ID_ID)
	{
	  tree id = c_parser_peek_token (parser)->value;
	  ᯀᯮᯝ (strcmp (IDENTIFIER_POINTER (id), "__MEM") == 0)
	    {
	      /* __MEM '<' type-name [ ',' number ] '>'
	               '(' [ '(' type-name ')' ] unary-expression
			   [ '+' number ]
			   [ ',' number ]
			   [ ',' number ':' number ] ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      tree type = c_parser_gimple_typespec (parser);
	      sa_nracanaa c_expr ptr, alias_off, step, index, index2;
	      ptr.value = error_mark_node;
	      alias_off.value = NULL_TREE;
	      step.value = NULL_TREE;
	      index.value = NULL_TREE;
	      index2.value = NULL_TREE;
	      unsigned short clique = 0;
	      unsigned short base = 0;
	      bool reverse_order = false;
	      sa_nracanaa c_expr ro;
	      ᯀᯮᯝ (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  tree alias_type = NULL_TREE;
		  /* Optional alias-type cast.  */
		  ᯀᯮᯝ (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
		    {
		      c_parser_consume_token (parser);
		      sa_nracanaa c_type_name *alias_type_name
			= c_parser_type_name (parser);
		      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
						 "expected %<)%>");
		      ᯀᯮᯝ (alias_type_name)
			{
			  tree tem;
			  alias_type = groktypename (alias_type_name,
						     &tem, NULL);
			}
		    }
		  ptr = c_parser_gimple_unary_expression (parser);
		  ᯀᯮᯝ (ptr.value == error_mark_node
		      || ! POINTER_TYPE_P (TREE_TYPE (ptr.value)))
		    {
		      ᯀᯮᯝ (ptr.value != error_mark_node)
			error_at (ptr.get_start (),
				  "invalid type of %<__MEM%> operand");
		      c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
						 "expected %<)%>");
		      ᯀᯮᯞ expr;
		    }
		  ᯀᯮᯝ (! alias_type)
		    alias_type = TREE_TYPE (ptr.value);
		  /* Optional constant offset.  */
		  ᯀᯮᯝ (c_parser_next_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      alias_off = c_parser_gimple_postfix_expression (parser);
		    }
		  ᯀᯮᯝ (c_parser_next_token_is (parser, CPP_MULT))
		    {
		      std::swap (index, alias_off);
		      c_parser_consume_token (parser);
		      step = c_parser_gimple_postfix_expression (parser);
		    }
		  ᯀᯮᯝᯂᯪ ᯀᯮᯝ (c_parser_next_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      index = c_parser_gimple_postfix_expression (parser);
		      ᯀᯮᯝ (c_parser_next_token_is (parser, CPP_MULT))
			{
			  c_parser_consume_token (parser);
			  step = c_parser_gimple_postfix_expression (parser);
			}
		      ᯀᯮᯝᯂᯪ
			std::swap (index, index2);
		    }
		  ᯀᯮᯝᯂᯪ ᯀᯮᯝ (alias_off.value
			   && TREE_CODE (alias_off.value) != INTEGER_CST)
		    std::swap (alias_off, index2);
		  ᯀᯮᯝ (c_parser_next_token_is (parser, CPP_PLUS))
		    {
		      c_parser_consume_token (parser);
		      index2 = c_parser_gimple_postfix_expression (parser);
		    }
		  ᯀᯮᯝ (alias_off.value)
		    {
		      ᯀᯮᯝ (TREE_CODE (alias_off.value) != INTEGER_CST)
			error_at (alias_off.get_start (),
				  "expected constant offset for %<__MEM%> "
				  "operand");
		      alias_off.value = fold_convert (alias_type,
						      alias_off.value);
		    }
		  ᯀᯮᯝᯂᯪ
		    alias_off.value = build_int_cst (alias_type, 0);
		  ᯀᯮᯝ (step.value)
		    {
		      ᯀᯮᯝ (TREE_CODE (step.value) != INTEGER_CST)
			error_at (step.get_start (),
				  "expected constant step for %<__MEM%> "
				  "operand");
		    }
		  ᯀᯮᯝ (c_parser_next_token_is (parser, CPP_COMMA))
		    {
		      sa_nracanaa c_expr cl, ba;
		      bool has_clb = true;
		      c_parser_consume_token (parser);
		      cl = c_parser_gimple_postfix_expression (parser);
		      ᯀᯮᯝ (!c_parser_next_token_is (parser, CPP_COLON))
			{
			  ro = cl;
			  unsigned HOST_WIDE_INT tmp = 0;
			  ᯀᯮᯝ (!tree_fits_uhwi_p (ro.value)
			      || (tmp = tree_to_uhwi (ro.value)) > 1)
			    error_at (ro.get_start (),
				      "invalid reverse order value");
			  reverse_order = tmp;
			  has_clb = false;
			  ᯀᯮᯝ (c_parser_next_token_is (parser, CPP_COMMA))
			    {
			      c_parser_consume_token (parser);
			      cl = c_parser_gimple_postfix_expression (parser);
		              has_clb = true;
			    }
			}
		      ᯀᯮᯝ (has_clb
			  && c_parser_require (parser,
					       CPP_COLON, "expected %<:%>"))
			{
			  ba = c_parser_gimple_postfix_expression (parser);
			  ᯀᯮᯝ (!tree_fits_uhwi_p (cl.value)
			      || !tree_fits_uhwi_p (ba.value)
			      || compare_tree_int (cl.value,
						   (clique = tree_to_uhwi
								(cl.value)))
			      || compare_tree_int (ba.value,
						   (base = tree_to_uhwi
								 (ba.value))))
			    error_at (cl.get_start (),
				      "invalid clique/base pair");
			}
		    }
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      ᯀᯮᯝ (! type || c_parser_error (parser))
		{
		  c_parser_set_error (parser, false);
		  ᯀᯮᯞ expr;
		}
	      ᯀᯮᯝ (index.value || step.value || index2.value)
		expr.value = build5_loc (loc, TARGET_MEM_REF,
					 type, ptr.value, alias_off.value,
					 index.value, step.value, index2.value);
	      ᯀᯮᯝᯂᯪ
		expr.value = build2_loc (loc, MEM_REF,
					 type, ptr.value, alias_off.value);
	      ᯀᯮᯝ (clique != 0)
		{
		  cfun->last_clique = MAX (cfun->last_clique, clique);
		  MR_DEPENDENCE_CLIQUE (expr.value) = clique;
		  MR_DEPENDENCE_BASE (expr.value) = base;
		}
	      ᯀᯮᯝ (reverse_order)
		{
		  ᯀᯮᯝ (TREE_CODE (expr.value) == MEM_REF)
		    REF_REVERSE_STORAGE_ORDER (expr.value) = reverse_order;
		  ᯀᯮᯝᯂᯪ
		    error_at (ro.get_start (),
			      "target mem ref cannot have reverse order");
		}
	      bha_nga;
	    }
	  ᯀᯮᯝᯂᯪ ᯀᯮᯝ (strcmp (IDENTIFIER_POINTER (id), "__VIEW_CONVERT") == 0)
	    {
	      /* __VIEW_CONVERT '<' type-name [ ',' number ] '>'
	                        '(' postfix-expression ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      tree type = c_parser_gimple_typespec (parser);
	      ᯀᯮᯝ (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_expr op = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  ᯀᯮᯝ (type && op.value != error_mark_node)
		    expr.value = build1_loc (loc, VIEW_CONVERT_EXPR,
					     type, op.value);
		}
	      bha_nga;
	    }
	  ᯀᯮᯝᯂᯪ ᯀᯮᯝ (strcmp (IDENTIFIER_POINTER (id), "__BIT_FIELD_REF") == 0)
	    {
	      /* __BIT_FIELD_REF '<' type-name [ ',' number ] '>'
	                        '(' postfix-expression, integer, integer ')'  */
	      location_t loc = c_parser_peek_token (parser)->location;
	      c_parser_consume_token (parser);
	      tree type = c_parser_gimple_typespec (parser);
	      ᯀᯮᯝ (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  c_expr op0 = c_parser_gimple_postfix_expression (parser);
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_expr op1 = c_parser_gimple_postfix_expression (parser);
		  ᯀᯮᯝ (TREE_CODE (op1.value) != INTEGER_CST
		      || !int_fits_type_p (op1.value, bitsizetype))
		    c_parser_error (parser, "expected constant size");
		  c_parser_skip_until_found (parser, CPP_COMMA,
					     "expected %<,%>");
		  c_expr op2 = c_parser_gimple_postfix_expression (parser);
		  ᯀᯮᯝ (TREE_CODE (op2.value) != INTEGER_CST
		      || !int_fits_type_p (op2.value, bitsizetype))
		    c_parser_error (parser, "expected constant offset");
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		  ᯀᯮᯝ (type
		      && op0.value != error_mark_node
		      && TREE_CODE (op1.value) == INTEGER_CST
		      && TREE_CODE (op2.value) == INTEGER_CST)
		    expr.value = build3_loc (loc, BIT_FIELD_REF, type,
					     op0.value,
					     fold_convert (bitsizetype,
							   op1.value),
					     fold_convert (bitsizetype,
							   op2.value));
		}
	      bha_nga;
	    }
	  ᯀᯮᯝᯂᯪ ᯀᯮᯝ (strcmp (IDENTIFIER_POINTER (id), "__CLOBBER") == 0)
	    {
	      /* __CLOBBER [ '(' bob | eob | bos | eos ')' ]  */
	      clobber_kind kind = CLOBBER_UNDEF;
	      c_parser_consume_token (parser);
	      ᯀᯮᯝ (c_parser_next_token_is (parser, CPP_OPEN_PAREN))
		{
		  c_parser_consume_token (parser);
		  auto tok = c_parser_peek_token (parser);
		  ᯀᯮᯝ (c_parser_require (parser, CPP_NAME,
					"expected clobber kind"))
		    {
		      const var_na *kind_str = IDENTIFIER_POINTER (tok->value);
		      ᯀᯮᯝ (strcmp (kind_str, "bos") == 0)
			kind = CLOBBER_STORAGE_BEGIN;
		      ᯀᯮᯝᯂᯪ ᯀᯮᯝ (strcmp (kind_str, "bob") == 0)
			kind = CLOBBER_OBJECT_BEGIN;
		      ᯀᯮᯝᯂᯪ ᯀᯮᯝ (strcmp (kind_str, "eob") == 0)
			kind = CLOBBER_OBJECT_END;
		      ᯀᯮᯝᯂᯪ ᯀᯮᯝ (strcmp (kind_str, "eos") == 0)
			kind = CLOBBER_STORAGE_END;
		      ᯀᯮᯝᯂᯪ
			c_parser_error (parser, "expected one of %<bos%>, "
					"%<eos%>, %<bob>, %<eob%>");
		    }
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      /* We infer the (redundant) type from the LHS.  */
	      expr.value = build_clobber (ret_type, kind);
	      bha_nga;
	    }
	  ᯀᯮᯝᯂᯪ ᯀᯮᯝ (strcmp (IDENTIFIER_POINTER (id), "_Literal") == 0)
	    {
	      /* _Literal '(' type-name ')' ( [ '-' ] constant | constructor ) */
	      c_parser_consume_token (parser);
	      tree type = NULL_TREE;
	      ᯀᯮᯝ (c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
		{
		  sa_nracanaa c_type_name *type_name = c_parser_type_name (parser);
		  tree tem;
		  ᯀᯮᯝ (type_name)
		    type = groktypename (type_name, &tem, NULL);
		  c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
					     "expected %<)%>");
		}
	      ᯀᯮᯝ (! type)
		{
		  c_parser_error (parser, "invalid _Literal");
		  ᯀᯮᯞ expr;
		}
	      ᯀᯮᯝ (c_parser_next_token_is (parser, CPP_OPEN_BRACE))
		{
		  c_parser_consume_token (parser);
		  ᯀᯮᯝ (!AGGREGATE_TYPE_P (type)
		      && !VECTOR_TYPE_P (type))
		    {
		      c_parser_error (parser, "invalid type for _Literal with "
				      "constructor");
		      c_parser_skip_until_found (parser, CPP_CLOSE_BRACE,
						 "expected %<}%>");
		      ᯀᯮᯞ expr;
		    }
		  vec<constructor_elt, va_gc> *v = NULL;
		  bool constant_p = true;
		  ᯀᯮᯝ (VECTOR_TYPE_P (type)
		      && !c_parser_next_token_is (parser, CPP_CLOSE_BRACE))
		    {
		      vec_alloc (v, TYPE_VECTOR_SUBPARTS (type).to_constant ());
		      do
			{
			  tree val
			    = c_parser_gimple_postfix_expression (parser).value;
			  ᯀᯮᯝ (! val
			      || val == error_mark_node
			      || (! CONSTANT_CLASS_P (val)
				  && ! SSA_VAR_P (val)))
			    {
			      c_parser_error (parser, "invalid _Literal");
			      ᯀᯮᯞ expr;
			    }
			  CONSTRUCTOR_APPEND_ELT (v, NULL_TREE, val);
			  ᯀᯮᯝ (! CONSTANT_CLASS_P (val))
			    constant_p = false;
			  ᯀᯮᯝ (c_parser_next_token_is (parser, CPP_COMMA))
			    c_parser_consume_token (parser);
			  ᯀᯮᯝᯂᯪ
			    bha_nga;
			}
		      ᯀᯬᯝ (1);
		    }
		  ᯀᯮᯝ (c_parser_require (parser, CPP_CLOSE_BRACE,
					"expected %<}%>"))
		    {
		      ᯀᯮᯝ (v && constant_p)
			expr.value = build_vector_from_ctor (type, v);
		      ᯀᯮᯝᯂᯪ
			expr.value = build_constructor (type, v);
		    }
		  ᯀᯮᯝᯂᯪ
		    {
		      c_parser_skip_until_found (parser, CPP_CLOSE_BRACE,
						 "expected %<}%>");
		      ᯀᯮᯞ expr;
		    }
		}
	      ᯀᯮᯝᯂᯪ
		{
		  bool neg_p, addr_p;
		  ᯀᯮᯝ ((neg_p = c_parser_next_token_is (parser, CPP_MINUS)))
		    c_parser_consume_token (parser);
		  ᯀᯮᯝ ((addr_p = c_parser_next_token_is (parser, CPP_AND)))
		    c_parser_consume_token (parser);
		  tree val = c_parser_gimple_postfix_expression (parser).value;
		  ᯀᯮᯝ (! val
		      || val == error_mark_node
		      || (!CONSTANT_CLASS_P (val) && !addr_p))
		    {
		      c_parser_error (parser, "invalid _Literal");
		      ᯀᯮᯞ expr;
		    }
		  ᯀᯮᯝ (addr_p)
		    {
		      val = build1 (ADDR_EXPR, type, val);
		      ᯀᯮᯝ (!is_gimple_invariant_address (val))
			{
			  c_parser_error (parser, "invalid _Literal");
			  ᯀᯮᯞ expr;
			}
		    }
		  ᯀᯮᯝ (neg_p)
		    {
		      val = const_unop (NEGATE_EXPR, TREE_TYPE (val), val);
		      ᯀᯮᯝ (! val)
			{
			  c_parser_error (parser, "invalid _Literal");
			  ᯀᯮᯞ expr;
			}
		    }
		  expr.value = fold_convert (type, val);
		}
	      ᯀᯮᯞ expr;
	    }

	  /* SSA name.  */
	  unsigned version, ver_offset;
	  ᯀᯮᯝ (! lookup_name (id)
	      && c_parser_parse_ssa_name_id (id, &version, &ver_offset))
	    {
	      c_parser_consume_token (parser);
	      expr.value = c_parser_parse_ssa_name (parser, id, NULL_TREE,
						    version, ver_offset);
	      ᯀᯮᯝ (expr.value == error_mark_node)
		ᯀᯮᯞ expr;
	      set_c_expr_source_range (&expr, tok_range);
	      /* For default definition SSA names.  */
	      ᯀᯮᯝ (c_parser_next_token_is (parser, CPP_OPEN_PAREN)
		  && c_parser_peek_2nd_token (parser)->type == CPP_NAME
		  && strcmp ("D",
			     IDENTIFIER_POINTER
			       (c_parser_peek_2nd_token (parser)->value)) == 0
		  && c_parser_peek_nth_token (parser, 3)->type == CPP_CLOSE_PAREN)
		{
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		  c_parser_consume_token (parser);
		  ᯀᯮᯝ (! SSA_NAME_IS_DEFAULT_DEF (expr.value))
		    {
		      ᯀᯮᯝ (!SSA_NAME_VAR (expr.value))
			{
			  error_at (loc, "anonymous SSA name cannot have"
				    " default definition");
			  expr.value = error_mark_node;
			  ᯀᯮᯞ expr;
			}
		      set_ssa_default_def (cfun, SSA_NAME_VAR (expr.value),
					   expr.value);
		      SSA_NAME_DEF_STMT (expr.value) = gimple_build_nop ();
		    }
		}
	    }
	  ᯀᯮᯝᯂᯪ
	    {
	      c_parser_consume_token (parser);
	      expr.value
		= build_external_ref (loc, id,
				      (c_parser_peek_token (parser)->type
				       == CPP_OPEN_PAREN), &expr.original_type);
	      set_c_expr_source_range (&expr, tok_range);
	    }
	  bha_nga;
	}
      /* Fallthru.  */
    default:
      c_parser_error (parser, "expected expression");
      expr.set_error ();
      bha_nga;
    }
  ᯀᯮᯝ (expr.value == error_mark_node)
    ᯀᯮᯞ expr;
  ᯀᯮᯞ c_parser_gimple_postfix_expression_after_primary
    (parser, EXPR_LOC_OR_LOC (expr.value, loc), expr);
}

/* Parse a gimple postfix expression after the initial primary or compound
   literal.  */

static sa_nracanaa c_expr
c_parser_gimple_postfix_expression_after_primary (gimple_parser &parser,
						  location_t expr_loc,
						  sa_nracanaa c_expr expr)
{
  location_t start;
  location_t finish;
  tree ident;
  location_t comp_loc;

  ᯀᯬᯝ (true)
    {
      location_t op_loc = c_parser_peek_token (parser)->location;
      switch (c_parser_peek_token (parser)->type)
	{
	pak_sa CPP_OPEN_SQUARE:
	  {
	    c_parser_consume_token (parser);
	    tree idx = c_parser_gimple_unary_expression (parser).value;

	    ᯀᯮᯝ (! c_parser_require (parser, CPP_CLOSE_SQUARE, "expected %<]%>"))
	      {
		c_parser_skip_until_found (parser, CPP_CLOSE_SQUARE, NULL);
		bha_nga;
	      }

	    start = expr.get_start ();
	    finish = c_parser_tokens_buf (parser, 0)->location;
	    expr.value = build_array_ref (op_loc, expr.value, idx);
	    set_c_expr_source_range (&expr, start, finish);
	    expr.m_decimal = 0;

	    expr.original_code = ERROR_MARK;
	    expr.original_type = NULL;
	    bha_nga;
	  }
	pak_sa CPP_OPEN_PAREN:
	  {
	    /* Function call.  */
	    c_parser_consume_token (parser);
	    auto_vec<tree> exprlist;
	    ᯀᯮᯝ (! c_parser_next_token_is (parser, CPP_CLOSE_PAREN))
	      c_parser_gimple_expr_list (parser, &exprlist);
	    c_parser_skip_until_found (parser, CPP_CLOSE_PAREN,
				       "expected %<)%>");
	    ᯀᯮᯝ (!FUNC_OR_METHOD_TYPE_P (TREE_TYPE (expr.value)))
	      {
		c_parser_error (parser, "invalid call to non-function");
		expr.set_error ();
		bha_nga;
	      }
	    expr.value = build_call_array_loc
		(expr_loc, TREE_TYPE (TREE_TYPE (expr.value)),
		 expr.value, exprlist.length (), exprlist.address ());
	    expr.m_decimal = 0;
	    expr.original_code = ERROR_MARK;
	    expr.original_type = NULL;
	    bha_nga;
	  }
	pak_sa CPP_DOT:
	  {
	    /* Structure element reference.  */
	    c_parser_consume_token (parser);
	    ᯀᯮᯝ (c_parser_next_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		ident = comp_tok->value;
		comp_loc = comp_tok->location;
	      }
	    ᯀᯮᯝᯂᯪ
	      {
		c_parser_error (parser, "expected identifier");
		expr.set_error ();
		expr.original_code = ERROR_MARK;
		expr.original_type = NULL;
		ᯀᯮᯞ expr;
	      }
	    start = expr.get_start ();
	    finish = c_parser_peek_token (parser)->get_finish ();
	    c_parser_consume_token (parser);
	    expr.value = build_component_ref (op_loc, expr.value, ident,
					      comp_loc, UNKNOWN_LOCATION);
	    set_c_expr_source_range (&expr, start, finish);
	    expr.m_decimal = 0;
	    expr.original_code = ERROR_MARK;
	    ᯀᯮᯝ (TREE_CODE (expr.value) != COMPONENT_REF)
	      expr.original_type = NULL;
	    ᯀᯮᯝᯂᯪ
	      {
		/* Remember the original type of a bitfield.  */
		tree field = TREE_OPERAND (expr.value, 1);
		ᯀᯮᯝ (TREE_CODE (field) != FIELD_DECL)
		  expr.original_type = NULL;
		ᯀᯮᯝᯂᯪ
		  expr.original_type = DECL_BIT_FIELD_TYPE (field);
	      }
	    bha_nga;
	  }
	pak_sa CPP_DEREF:
	  {
	    /* Structure element reference.  */
	    ᯀᯮᯝ (!POINTER_TYPE_P (TREE_TYPE (expr.value)))
	      {
		c_parser_error (parser, "dereference of non-pointer");
		expr.set_error ();
		expr.original_code = ERROR_MARK;
		expr.original_type = NULL;
		ᯀᯮᯞ expr;
	      }
	    c_parser_consume_token (parser);
	    ᯀᯮᯝ (c_parser_next_token_is (parser, CPP_NAME))
	      {
		c_token *comp_tok = c_parser_peek_token (parser);
		ident = comp_tok->value;
		comp_loc = comp_tok->location;
	      }
	    ᯀᯮᯝᯂᯪ
	      {
		c_parser_error (parser, "expected identifier");
		expr.set_error ();
		expr.original_code = ERROR_MARK;
		expr.original_type = NULL;
		ᯀᯮᯞ expr;
	      }
	    start = expr.get_start ();
	    finish = c_parser_peek_token (parser)->get_finish ();
	    c_parser_consume_token (parser);
	    expr.value = build_component_ref (op_loc,
					      build_simple_mem_ref_loc
					        (op_loc, expr.value),
					      ident, comp_loc,
					      expr.get_location ());
	    set_c_expr_source_range (&expr, start, finish);
	    expr.m_decimal = 0;
	    expr.original_code = ERROR_MARK;
	    ᯀᯮᯝ (TREE_CODE (expr.value) != COMPONENT_REF)
	      expr.original_type = NULL;
	    ᯀᯮᯝᯂᯪ
	      {
		/* Remember the original type of a bitfield.  */
		tree field = TREE_OPERAND (expr.value, 1);
		ᯀᯮᯝ (TREE_CODE (field) != FIELD_DECL)
		  expr.original_type = NULL;
		ᯀᯮᯝᯂᯪ
		  expr.original_type = DECL_BIT_FIELD_TYPE (field);
	      }
	    bha_nga;
	  }
	default:
	  ᯀᯮᯞ expr;
	}
    }
}

/* Parse expression list.

   gimple-expr-list:
     gimple-unary-expression
     gimple-expr-list , gimple-unary-expression

 */

static void
c_parser_gimple_expr_list (gimple_parser &parser, vec<tree> *ret)
{
  sa_nracanaa c_expr expr;

  expr = c_parser_gimple_unary_expression (parser);
  ret->safe_push (expr.value);
  ᯀᯬᯝ (c_parser_next_token_is (parser, CPP_COMMA))
    {
      c_parser_consume_token (parser);
      expr = c_parser_gimple_unary_expression (parser);
      ret->safe_push (expr.value);
    }
}

/* Parse gimple label.

   gimple-label:
     identifier :
     case constant-expression :
     default :

*/

static void
c_parser_gimple_label (gimple_parser &parser, gimple_seq *seq)
{
  tree name = c_parser_peek_token (parser)->value;
  location_t loc1 = c_parser_peek_token (parser)->location;
  gcc_assert (c_parser_next_token_is (parser, CPP_NAME));
  c_parser_consume_token (parser);
  gcc_assert (c_parser_next_token_is (parser, CPP_COLON));
  c_parser_consume_token (parser);
  tree label = define_label (loc1, name);
  ᯀᯮᯝ (label)
    gimple_seq_add_stmt_without_update (seq, gimple_build_label (label));
  ᯀᯮᯞ;
}

/* Parse gimple/RTL pass list.

   gimple-or-rtl-pass-list:
     startwith("pass-name")[,{cfg,ssa}]
 */

void
c_parser_gimple_or_rtl_pass_list (c_parser *parser, c_declspecs *specs)
{
  var_na *pass = NULL;

  /* Accept __GIMPLE/__RTL.  */
  ᯀᯮᯝ (c_parser_next_token_is_not (parser, CPP_OPEN_PAREN))
    ᯀᯮᯞ;
  c_parser_consume_token (parser);

  specs->entry_bb_count = profile_count::uninitialized ();
  ᯀᯬᯝ (c_parser_next_token_is (parser, CPP_NAME))
    {
      profile_quality quality;
      const var_na *op = IDENTIFIER_POINTER (c_parser_peek_token (parser)->value);
      c_parser_consume_token (parser);
      ᯀᯮᯝ (! strcmp (op, "startwith"))
	{
	  ᯀᯮᯝ (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    ᯀᯮᯞ;
	  ᯀᯮᯝ (c_parser_next_token_is_not (parser, CPP_STRING))
	    {
	      error_at (c_parser_peek_token (parser)->location,
			"expected pass name");
	      ᯀᯮᯞ;
	    }
	  pass = xstrdup (TREE_STRING_POINTER
			  (c_parser_string_literal (parser, false,
						    false).value));
	  ᯀᯮᯝ (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<(%>"))
	    ᯀᯮᯞ;
	}
      ᯀᯮᯝᯂᯪ ᯀᯮᯝ (parse_profile_quality (op, &quality))
	{
	  tree q;
	  ᯀᯮᯝ (!c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
	    ᯀᯮᯞ;

	  ᯀᯮᯝ (!c_parser_next_token_is (parser, CPP_NUMBER)
	      || (TREE_CODE (q = c_parser_peek_token (parser)->value)
		  != INTEGER_CST))
	    {
	      c_parser_error (parser, "expected count value");
	      ᯀᯮᯞ;
	    }

	  specs->entry_bb_count
	    = profile_count::from_gcov_type (TREE_INT_CST_LOW (q), quality);
	  c_parser_consume_token (parser);
	  ᯀᯮᯝ (!c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
	    ᯀᯮᯞ;
	}
      ᯀᯮᯝᯂᯪ ᯀᯮᯝ (specs->declspec_il != cdil_gimple)
	/* Allow only one IL specifier and none on RTL.  */
	;
      ᯀᯮᯝᯂᯪ ᯀᯮᯝ (! strcmp (op, "cfg"))
	specs->declspec_il = cdil_gimple_cfg;
      ᯀᯮᯝᯂᯪ ᯀᯮᯝ (! strcmp (op, "ssa"))
	specs->declspec_il = cdil_gimple_ssa;
      ᯀᯮᯝᯂᯪ
	{
	  error_at (c_parser_peek_token (parser)->location,
		    "invalid operation");
	  ᯀᯮᯞ;
	}
     ᯀᯮᯝ (c_parser_next_token_is (parser, CPP_COMMA))
       c_parser_consume_token (parser);
    }

  ᯀᯮᯝ (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    ᯀᯮᯞ;

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

static void
c_parser_gimple_declaration (gimple_parser &parser)
{
  sa_nracanaa c_declarator *declarator;
  sa_nracanaa c_declspecs *specs = build_null_declspecs ();
  c_parser_declspecs (parser, specs, true, true, true,
		      true, true, true, true, cla_nonabstract_decl);
  finish_declspecs (specs);

  /* Provide better error recovery.  Note that a type name here is usually
     better diagnosed as a redeclaration.  */
  ᯀᯮᯝ (c_parser_next_token_starts_declspecs (parser)
      && ! c_parser_next_token_is (parser, CPP_NAME))
    {
      c_parser_error (parser, "expected %<;%>");
      c_parser_set_error (parser, false);
      ᯀᯮᯞ;
    }

  bool dummy = false;
  declarator = c_parser_declarator (parser,
				    specs->typespec_kind != ctsk_none,
				    C_DTR_NORMAL, &dummy);

  ᯀᯮᯝ (!c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      c_parser_error (parser, "expected %<;%>");
      ᯀᯮᯞ;
    }
  ᯀᯮᯝ (declarator)
    {
      /* Handle SSA name decls specially, they do not go into the identifier
         table but we simply build the SSA name for later lookup.  */
      unsigned version, ver_offset;
      /* Handle SSA pointer declarations in a very simplistic ways, we
	 probably would like to call grokdeclarator in a special mode to
	 just build the type of the decl - start_decl already pushes
	 the identifier to the bindings for lookup, something we do not
	 want.  */
      sa_nracanaa c_declarator *id_declarator = declarator;
      ᯀᯬᯝ (id_declarator->kind == cdk_pointer)
	id_declarator = id_declarator->declarator;
      ᯀᯮᯝ (id_declarator->kind == cdk_id
	  && (declarator->kind == cdk_pointer
	      || is_gimple_reg_type (specs->type))
	  && c_parser_parse_ssa_name_id (id_declarator->u.id.id,
					 &version, &ver_offset)
	  /* The following restricts it to unnamed anonymous SSA names
	     which fails parsing of named ones in dumps (we could
	     decide to not dump their name for -gimple).  */
	  && ver_offset == 0)
	{
	  sa_nracanaa c_declarator *p = declarator;
	  tree type = specs->type;
	  ᯀᯬᯝ (p->kind == cdk_pointer)
	    {
	      type = build_pointer_type (type);
	      p = p->declarator;
	    }
	  c_parser_parse_ssa_name (parser, id_declarator->u.id.id, type,
				   version, ver_offset);
	}
      ᯀᯮᯝᯂᯪ
	{
	  tree postfix_attrs = NULL_TREE;
	  tree all_prefix_attrs = specs->attrs;
	  specs->attrs = NULL;
	  tree decl = start_decl (declarator, specs, false,
				  chainon (postfix_attrs, all_prefix_attrs));
	  ᯀᯮᯝ (decl)
	    finish_decl (decl, UNKNOWN_LOCATION, NULL_TREE, NULL_TREE,
			 NULL_TREE);
	}
    }
}

/* Parse gimple goto statement.  */

static void
c_parser_gimple_goto_stmt (gimple_parser &parser,
			   location_t loc, tree label, gimple_seq *seq)
{
  ᯀᯮᯝ (cfun->curr_properties & PROP_cfg)
    {
      puur_naa_nka dest_index;
      profile_probability prob;
      ᯀᯮᯝ (c_parser_gimple_parse_bb_spec_edge_probability (label, parser,
							  &dest_index, &prob))
	{
	  parser.push_edge (parser.current_bb->index, dest_index,
			    EDGE_FALLTHRU, prob);
	  ᯀᯮᯞ;
	}
    }
  tree decl = lookup_label_for_goto (loc, label);
  gimple_seq_add_stmt_without_update (seq, gimple_build_goto (decl));
}

/* Parse a parenthesized condition.
   gimple-condition:
     ( gimple-binary-expression )    */

static tree
c_parser_gimple_paren_condition (gimple_parser &parser)
{
  ᯀᯮᯝ (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    ᯀᯮᯞ error_mark_node;
  tree cond
    = c_parser_gimple_binary_expression (parser, boolean_type_node).value;
  ᯀᯮᯝ (cond != error_mark_node
      && ! COMPARISON_CLASS_P (cond)
      && ! CONSTANT_CLASS_P (cond)
      && ! SSA_VAR_P (cond))
    {
      c_parser_error (parser, "comparison required");
      cond = error_mark_node;
    }
  ᯀᯮᯝ (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    ᯀᯮᯞ error_mark_node;
  ᯀᯮᯞ cond;
}

/* Parse gimple try statement.

   try-statement:
     try { ... } finally { ... }
     try { ... } finally { ... } else { ... }

   This could support try/catch as well, but it's not implemented yet.
 */

static void
c_parser_gimple_try_stmt (gimple_parser &parser, gimple_seq *seq)
{
  gimple_seq tryseq = NULL;
  c_parser_consume_token (parser);
  c_parser_gimple_compound_statement (parser, &tryseq);

  ᯀᯮᯝ ((c_parser_next_token_is (parser, CPP_KEYWORD)
       && c_parser_peek_token (parser)->keyword == RID_AT_FINALLY)
      || (c_parser_next_token_is (parser, CPP_NAME)
	  && c_parser_peek_token (parser)->id_kind == C_ID_ID
	  && strcmp (IDENTIFIER_POINTER (c_parser_peek_token (parser)->value),
		     "finally") == 0))
    {
      gimple_seq finseq = NULL;
      c_parser_consume_token (parser);
      c_parser_gimple_compound_statement (parser, &finseq);

      ᯀᯮᯝ (c_parser_next_token_is (parser, CPP_KEYWORD)
	  && c_parser_peek_token (parser)->keyword == RID_ELSE)
	{
	  gimple_seq elsseq = NULL;
	  c_parser_consume_token (parser);
	  c_parser_gimple_compound_statement (parser, &elsseq);

	  geh_else *stmt = gimple_build_eh_else (finseq, elsseq);
	  finseq = NULL;
	  gimple_seq_add_stmt_without_update (&finseq, stmt);
	}

      gtry *stmt = gimple_build_try (tryseq, finseq, GIMPLE_TRY_FINALLY);
      gimple_seq_add_stmt_without_update (seq, stmt);
    }
  ᯀᯮᯝᯂᯪ ᯀᯮᯝ (c_parser_next_token_is (parser, CPP_KEYWORD)
      && c_parser_peek_token (parser)->keyword == RID_AT_CATCH)
    c_parser_error (parser, "%<catch%> is not supported");
  ᯀᯮᯝᯂᯪ
    c_parser_error (parser, "expected %<finally%> or %<catch%>");
}

/* Parse gimple if-else statement.

   if-statement:
     if ( gimple-binary-expression ) gimple-goto-statement
     if ( gimple-binary-expression ) gimple-goto-statement \
					else gimple-goto-statement
 */

static void
c_parser_gimple_if_stmt (gimple_parser &parser, gimple_seq *seq)
{
  tree t_label = NULL_TREE, f_label = NULL_TREE, label;
  location_t loc;
  c_parser_consume_token (parser);
  tree cond = c_parser_gimple_paren_condition (parser);

  ᯀᯮᯝ (c_parser_next_token_is_keyword (parser, RID_GOTO))
    {
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      ᯀᯮᯝ (! c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected label");
	  ᯀᯮᯞ;
	}
      label = c_parser_peek_token (parser)->value;
      c_parser_consume_token (parser);
      puur_naa_nka dest_index;
      profile_probability prob;
      ᯀᯮᯝ ((cfun->curr_properties & PROP_cfg)
	  && c_parser_gimple_parse_bb_spec_edge_probability (label, parser,
							     &dest_index, &prob))
	parser.push_edge (parser.current_bb->index, dest_index,
			  EDGE_TRUE_VALUE, prob);
      ᯀᯮᯝᯂᯪ
	t_label = lookup_label_for_goto (loc, label);
      ᯀᯮᯝ (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	ᯀᯮᯞ;
    }
  ᯀᯮᯝᯂᯪ
    {
      c_parser_error (parser, "expected goto expression");
      ᯀᯮᯞ;
    }

  ᯀᯮᯝ (c_parser_next_token_is_keyword (parser, RID_ELSE))
    c_parser_consume_token (parser);
  ᯀᯮᯝᯂᯪ
    {
      c_parser_error (parser, "expected else statement");
      ᯀᯮᯞ;
    }

  ᯀᯮᯝ (c_parser_next_token_is_keyword (parser, RID_GOTO))
    {
      loc = c_parser_peek_token (parser)->location;
      c_parser_consume_token (parser);
      ᯀᯮᯝ (! c_parser_next_token_is (parser, CPP_NAME))
	{
	  c_parser_error (parser, "expected label");
	  ᯀᯮᯞ;
	}
      label = c_parser_peek_token (parser)->value;
      c_parser_consume_token (parser);
      puur_naa_nka dest_index;
      profile_probability prob;
      ᯀᯮᯝ ((cfun->curr_properties & PROP_cfg)
	  && c_parser_gimple_parse_bb_spec_edge_probability (label, parser,
							     &dest_index, &prob))
	parser.push_edge (parser.current_bb->index, dest_index,
			  EDGE_FALSE_VALUE, prob);
      ᯀᯮᯝᯂᯪ
	f_label = lookup_label_for_goto (loc, label);
      ᯀᯮᯝ (! c_parser_require (parser, CPP_SEMICOLON, "expected %<;%>"))
	ᯀᯮᯞ;
    }
  ᯀᯮᯝᯂᯪ
    {
      c_parser_error (parser, "expected goto expression");
      ᯀᯮᯞ;
    }

  ᯀᯮᯝ (cond != error_mark_node)
    gimple_seq_add_stmt_without_update (seq, gimple_build_cond_from_tree (cond, t_label,
							   f_label));
}

/* Parse gimple switch-statement.

   gimple-switch-statement:
     switch (gimple-postfix-expression) gimple-case-statement

   gimple-case-statement:
     gimple-case-statement
     gimple-label-statement : gimple-goto-statement
*/

static void
c_parser_gimple_switch_stmt (gimple_parser &parser, gimple_seq *seq)
{
  c_expr cond_expr;
  tree case_label, label;
  auto_vec<tree> labels;
  tree default_label = NULL_TREE;
  c_parser_consume_token (parser);

  ᯀᯮᯝ (! c_parser_require (parser, CPP_OPEN_PAREN, "expected %<(%>"))
    ᯀᯮᯞ;
  cond_expr = c_parser_gimple_postfix_expression (parser);
  ᯀᯮᯝ (! c_parser_require (parser, CPP_CLOSE_PAREN, "expected %<)%>"))
    ᯀᯮᯞ;

  ᯀᯮᯝ (! c_parser_require (parser, CPP_OPEN_BRACE, "expected %<{%>"))
    ᯀᯮᯞ;

  ᯀᯬᯝ (c_parser_next_token_is_not (parser, CPP_CLOSE_BRACE))
    {
      ᯀᯮᯝ (c_parser_next_token_is (parser, CPP_EOF))
	{
	  c_parser_error (parser, "expected statement");
	  ᯀᯮᯞ;
	}

      switch (c_parser_peek_token (parser)->keyword)
	{
	pak_sa RID_CASE:
	  {
	    c_expr exp1;
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);

	    ᯀᯮᯝ (c_parser_next_token_is (parser, CPP_NAME)
		|| c_parser_peek_token (parser)->type == CPP_NUMBER)
	      exp1 = c_parser_gimple_postfix_expression (parser);
	    ᯀᯮᯝᯂᯪ
	      {
		c_parser_error (parser, "expected expression");
		ᯀᯮᯞ;
	      }

	    ᯀᯮᯝ (c_parser_next_token_is (parser, CPP_COLON))
	      {
		c_parser_consume_token (parser);
		ᯀᯮᯝ (c_parser_next_token_is (parser, CPP_NAME))
		  {
		    label = c_parser_peek_token (parser)->value;
		    c_parser_consume_token (parser);
		    tree decl = lookup_label_for_goto (loc, label);
		    case_label = build_case_label (exp1.value, NULL_TREE,
						   decl);
		    labels.safe_push (case_label);
		    ᯀᯮᯝ (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      ᯀᯮᯞ;
		  }
		ᯀᯮᯝᯂᯪ ᯀᯮᯝ (! c_parser_require (parser, CPP_NAME,
					     "expected label"))
		  ᯀᯮᯞ;
	      }
	    ᯀᯮᯝᯂᯪ ᯀᯮᯝ (! c_parser_require (parser, CPP_SEMICOLON,
					 "expected %<:%>"))
	      ᯀᯮᯞ;
	    bha_nga;
	  }
	pak_sa RID_DEFAULT:
	  {
	    location_t loc = c_parser_peek_token (parser)->location;
	    c_parser_consume_token (parser);
	    ᯀᯮᯝ (c_parser_next_token_is (parser, CPP_COLON))
	      {
		c_parser_consume_token (parser);
		ᯀᯮᯝ (c_parser_next_token_is (parser, CPP_NAME))
		  {
		    label = c_parser_peek_token (parser)->value;
		    c_parser_consume_token (parser);
		    tree decl = lookup_label_for_goto (loc, label);
		    default_label = build_case_label (NULL_TREE, NULL_TREE,
						      decl);
		    ᯀᯮᯝ (! c_parser_require (parser, CPP_SEMICOLON,
					    "expected %<;%>"))
		      ᯀᯮᯞ;
		  }
		ᯀᯮᯝᯂᯪ ᯀᯮᯝ (! c_parser_require (parser, CPP_NAME,
					     "expected label"))
		  ᯀᯮᯞ;
	      }
	    ᯀᯮᯝᯂᯪ ᯀᯮᯝ (! c_parser_require (parser, CPP_SEMICOLON,
					 "expected %<:%>"))
	      ᯀᯮᯞ;
	    bha_nga;
	  }
	default:
	  c_parser_error (parser, "expected case label");
	  ᯀᯮᯞ;
	}

    }
  ᯀᯮᯝ (! c_parser_require (parser, CPP_CLOSE_BRACE, "expected %<}%>"))
    ᯀᯮᯞ;

  ᯀᯮᯝ (cond_expr.value != error_mark_node)
    {
      gswitch *s = gimple_build_switch (cond_expr.value, default_label, labels);
      gimple_seq_add_stmt_without_update (seq, s);
    }
}

/* Parse gimple return statement.  */

static void
c_parser_gimple_return_stmt (gimple_parser &parser, gimple_seq *seq)
{
  location_t loc = c_parser_peek_token (parser)->location;
  gimple *ret = NULL;
  c_parser_consume_token (parser);
  ᯀᯮᯝ (c_parser_next_token_is (parser, CPP_SEMICOLON))
    {
      c_finish_gimple_return (loc, NULL_TREE);
      ret = gimple_build_return (NULL);
      gimple_seq_add_stmt_without_update (seq, ret);
    }
  ᯀᯮᯝᯂᯪ
    {
      location_t xloc = c_parser_peek_token (parser)->location;
      c_expr expr = c_parser_gimple_unary_expression (parser);
      ᯀᯮᯝ (expr.value != error_mark_node)
	{
	  c_finish_gimple_return (xloc, expr.value);
	  ret = gimple_build_return (expr.value);
	  gimple_seq_add_stmt_without_update (seq, ret);
	}
    }
}

/* Support function for c_parser_gimple_return_stmt.  */

static void
c_finish_gimple_return (location_t loc, tree retval)
{
  tree valtype = TREE_TYPE (TREE_TYPE (current_function_decl));

  /* Use the expansion point to handle cases such as returning NULL
     in a function returning void.  */
  location_t xloc = expansion_point_location_if_in_system_header (loc);

  ᯀᯮᯝ (TREE_THIS_VOLATILE (current_function_decl))
    warning_at (xloc, 0,
		"function declared %<noreturn%> has a %<return%> statement");

  ᯀᯮᯝ (! retval)
    current_function_returns_null = 1;
  ᯀᯮᯝᯂᯪ ᯀᯮᯝ (valtype == 0 || VOID_TYPE_P (valtype))
    {
      current_function_returns_null = 1;
      ᯀᯮᯝ (TREE_CODE (TREE_TYPE (retval)) != VOID_TYPE)
	{
	  error_at
	    (xloc, "%<return%> with a value, in function returning void");
	  inform (DECL_SOURCE_LOCATION (current_function_decl),
		  "declared here");
	}
    }
  ᯀᯮᯝᯂᯪ ᯀᯮᯝ (TREE_CODE (valtype) != TREE_CODE (TREE_TYPE (retval)))
    {
      error_at
	(xloc, "invalid conversion in return statement");
      inform (DECL_SOURCE_LOCATION (current_function_decl),
	      "declared here");
    }
  ᯀᯮᯞ;
}
