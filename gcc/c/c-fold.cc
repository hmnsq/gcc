/* Support for fully folding sub-trees of an expression for C compiler.
   Copyright (C) 1992-2026 Free Software Foundation, Inc.

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
#అన్తర్భావ "bitmap.h"
#అన్తర్భావ "c-tree.h"
#అన్తర్భావ "intl.h"
#అన్తర్భావ "gimplify.h"

స్థిర వృక్షం c_fully_fold_అంతర్గత (వృక్షం సమాసం, తార్కిక, తార్కిక *, తార్కిక *, తార్కిక,
				   తార్కిక);

/* If DISABLE is true, stop issuing warnings.  This is used when
   parsing code that we know will not be executed.  This function may
   be called multiple times, and works as a stack.  */

స్థిర శూన్య
c_disable_warnings (తార్కిక disable)
{
  ఒకవేళ (disable)
    {
      ++c_inhibit_evaluation_warnings;
    }
}

/* If ENABLE is true, re-enable issuing warnings.  */

స్థిర శూన్య
c_enable_warnings (తార్కిక enable)
{
  ఒకవేళ (enable)
    {
      --c_inhibit_evaluation_warnings;
    }
}

/* Try to fold ARRAY_REF ary[index] if possible and not handled by
   normal fold, return NULL_TREE otherwise.  */

స్థిర వృక్షం
c_fold_array_ref (వృక్షం type, వృక్షం ary, వృక్షం సూచీ)
{
  ఒకవేళ (వృక్షం_సంకేతం (ary) != STRING_CST
      || వృక్షం_సంకేతం (సూచీ) != INTEGER_CST
      || వృక్షం_అధికప్రవాహం (సూచీ)
      || వృక్షం_సంకేతం (వృక్షం_TYPE (ary)) != ARRAY_TYPE
      || !వృక్షం_సరిపోతుంది_uhwi_p (సూచీ))
    తిరిగి NULL_వృక్షం;

  వృక్షం elem_type = వృక్షం_TYPE (వృక్షం_TYPE (ary));
  గుర్తులేని elem_nchars = (TYPE_PRECISION (elem_type)
			  / TYPE_PRECISION (char_type_కణుపు));
  గుర్తులేని len = (గుర్తులేని) వృక్షం_STRING_నిడివి (ary) / elem_nchars;
  వృక్షం nelts_minus_one = array_type_nelts_minus_one (వృక్షం_TYPE (ary));
  తార్కిక dummy1 = నిజం, dummy2 = నిజం;
  nelts_minus_one = c_fully_fold_అంతర్గత (nelts_minus_one, నిజం, &dummy1,
					   &dummy2, అబద్ధం, అబద్ధం);
  గుర్తులేని HOST_WIDE_INT i = వృక్షం_గమ్యం_uhwi (సూచీ);
  ఒకవేళ (!వృక్షం_int_cst_le (సూచీ, nelts_minus_one)
      || i >= len
      || i + elem_nchars > len)
    తిరిగి NULL_వృక్షం;

  ఒకవేళ (elem_nchars == 1)
    తిరిగి build_int_cst (type, వృక్షం_STRING_సూచిక (ary)[i]);

  స్థిరరాశి గుర్తులేని అక్షరం *ptr
    = ((స్థిరరాశి గుర్తులేని అక్షరం *)వృక్షం_STRING_సూచిక (ary) + i * elem_nchars);
  తిరిగి native_interpret_సమాసం (type, ptr, elem_nchars);
}

/* Fully fold EXPR, an expression that was not folded (beyond integer
   constant expressions and null pointer constants) when being built
   up.  If IN_INIT, this is in a static initializer and certain
   changes are made to the folding done.  Clear *MAYBE_CONST if
   MAYBE_CONST is not NULL and EXPR is definitely not a constant
   expression because it contains an evaluated operator (in C99) or an
   operator outside of sizeof returning an integer constant (in C90)
   not permitted in constant expressions, or because it contains an
   evaluated arithmetic overflow.  (*MAYBE_CONST should typically be
   set to true by callers before calling this function.)  Return the
   folded expression.  Function arguments have already been folded
   before calling this function, as have the contents of SAVE_EXPR,
   TARGET_EXPR, BIND_EXPR, VA_ARG_EXPR, OBJ_TYPE_REF and
   C_MAYBE_CONST_EXPR.  LVAL is true if it should be treated as an
   lvalue.  */

వృక్షం
c_fully_fold (వృక్షం సమాసం, తార్కిక లోపల_init, తార్కిక *maybe_const, తార్కిక lval)
{
  వృక్షం ret;
  వృక్షం eptype = NULL_వృక్షం;
  తార్కిక dummy = నిజం;
  తార్కిక maybe_const_itself = నిజం;
  location_t loc = సమాసం_LOCATION (సమాసం);

  ఒకవేళ (!maybe_const)
    maybe_const = &dummy;
  ఒకవేళ (వృక్షం_సంకేతం (సమాసం) == EXCESS_PRECISION_సమాసం)
    {
      eptype = వృక్షం_TYPE (సమాసం);
      సమాసం = వృక్షం_నిర్వాహ్యం (సమాసం, 0);
    }
  ret = c_fully_fold_అంతర్గత (సమాసం, లోపల_init, maybe_const,
			       &maybe_const_itself, అబద్ధం, lval);
  ఒకవేళ (eptype)
    ret = fold_convert_loc (loc, eptype, ret);
  *maybe_const &= maybe_const_itself;
  తిరిగి ret;
}

/* Internal helper for c_fully_fold.  EXPR and IN_INIT are as for
   c_fully_fold.  *MAYBE_CONST_OPERANDS is cleared because of operands
   not permitted, while *MAYBE_CONST_ITSELF is cleared because of
   arithmetic overflow (for C90, *MAYBE_CONST_OPERANDS is carried from
   both evaluated and unevaluated subexpressions while
   *MAYBE_CONST_ITSELF is carried from only evaluated
   subexpressions).  FOR_INT_CONST indicates if EXPR is an expression
   with integer constant operands, and if any of the operands doesn't
   get folded to an integer constant, don't fold the expression itself.
   LVAL indicates folding of lvalue, where we can't replace it with
   an rvalue.  */

స్థిర వృక్షం
c_fully_fold_అంతర్గత (వృక్షం సమాసం, తార్కిక లోపల_init, తార్కిక *maybe_const_operands,
		       తార్కిక *maybe_const_itself, తార్కిక for_int_const, తార్కిక lval)
{
  వృక్షం ret = సమాసం;
  గణన వృక్షం_సంకేతం_2 సంకేతం_2 = వృక్షం_సంకేతం (సమాసం);
  గణన వృక్షం_సంకేతం_class రకం = వృక్షం_సంకేతం_CLASS (సంకేతం_2);
  location_t loc = సమాసం_LOCATION (సమాసం);
  వృక్షం op0, op1, op2, op3;
  వృక్షం orig_op0, orig_op1, orig_op2;
  తార్కిక op0_const = నిజం, op1_const = నిజం, op2_const = నిజం;
  తార్కిక op0_const_self = నిజం, op1_const_self = నిజం, op2_const_self = నిజం;
  తార్కిక nowarning = warning_suppressed_p (సమాసం, OPT_Woverflow);
  తార్కిక వాడని_p;
  తార్కిక op0_lval = అబద్ధం;
  ఆధారం_range old_range;

  /* Constants, declarations, statements, errors, and anything else not
     counted as an expression cannot usefully be folded further at this
     point.  */
  ఒకవేళ (!IS_సమాసం_సంకేతం_CLASS (రకం) || రకం == tcc_statement)
    {
      /* Except for variables which we can optimize to its initializer.  */
      ఒకవేళ (VAR_P (సమాసం) && !lval && (optimize || లోపల_init))
	{
	  ఒకవేళ (లోపల_init)
	    ret = decl_constant_విలువ_1 (సమాసం, నిజం);
	  లేకపోతే
	    {
	      ret = decl_constant_విలువ (సమాసం);
	      ఒకవేళ (ret != సమాసం
		  && (TYPE_బహుళకం (వృక్షం_TYPE (ret)) == BLKmode
		      || వృక్షం_సంకేతం (వృక్షం_TYPE (ret)) == ARRAY_TYPE))
		తిరిగి సమాసం;
	    }
	  /* Avoid unwanted tree sharing between the initializer and current
	     function's body where the tree can be modified e.g. by the
	     gimplifier.  */
	  ఒకవేళ (ret != సమాసం && వృక్షం_STATIC (సమాసం))
	    ret = unshare_సమాసం (ret);
	  తిరిగి ret;
	}
      తిరిగి సమాసం;
    }

  ఒకవేళ (IS_సమాసం_సంకేతం_CLASS (రకం))
    old_range = సమాసం_LOCATION_RANGE (సమాసం);

  /* Operands of variable-length expressions (function calls) have
     already been folded, as have __builtin_* function calls, and such
     expressions cannot occur in constant expressions.  */
  ఒకవేళ (రకం == tcc_vl_exp)
    {
      *maybe_const_operands = అబద్ధం;
      ret = fold (సమాసం);
      వెళ్ళు బహిర్గతం;
    }

  ఒకవేళ (సంకేతం_2 == C_MAYBE_CONST_సమాసం)
    {
      వృక్షం pre = C_MAYBE_CONST_సమాసం_PRE (సమాసం);
      వృక్షం inner = C_MAYBE_CONST_సమాసం_సమాసం (సమాసం);
      ఒకవేళ (C_MAYBE_CONST_సమాసం_NON_CONST (సమాసం))
	*maybe_const_operands = అబద్ధం;
      ఒకవేళ (C_MAYBE_CONST_సమాసం_INT_OPERANDS (సమాసం))
	{
	  *maybe_const_itself = అబద్ధం;
	  inner = c_fully_fold_అంతర్గత (inner, లోపల_init, maybe_const_operands,
					 maybe_const_itself, నిజం, lval);
	}
      ఒకవేళ (pre && !లోపల_init)
	ret = build2 (COMPOUND_సమాసం, వృక్షం_TYPE (సమాసం), pre, inner);
      లేకపోతే
	ret = inner;
      వెళ్ళు బహిర్గతం;
    }

  /* Assignment, increment, decrement, function call and comma
     operators, and statement expressions, cannot occur in constant
     expressions if evaluated / outside of sizeof.  (Function calls
     were handled above, though VA_ARG_EXPR is treated like a function
     call here, and statement expressions are handled through
     C_MAYBE_CONST_EXPR to avoid folding inside them.)  */
  ఎంపిక (సంకేతం_2)
    {
    స్థితి MODIFY_సమాసం:
    స్థితి PREDECREMENT_సమాసం:
    స్థితి PREINCREMENT_సమాసం:
    స్థితి POSTDECREMENT_సమాసం:
    స్థితి POSTINCREMENT_సమాసం:
    స్థితి COMPOUND_సమాసం:
      *maybe_const_operands = అబద్ధం;
      ఆపు;

    స్థితి VA_ARG_సమాసం:
    స్థితి లక్ష్యం_సమాసం:
    స్థితి BIND_సమాసం:
    స్థితి OBJ_TYPE_REF:
      *maybe_const_operands = అబద్ధం;
      ret = fold (సమాసం);
      వెళ్ళు బహిర్గతం;

    అప్రమేయ:
      ఆపు;
    }

  /* Fold individual tree codes as appropriate.  */
  ఎంపిక (సంకేతం_2)
    {
    స్థితి COMPOUND_LITERAL_సమాసం:
      /* Any non-constancy will have been marked in a containing
	 C_MAYBE_CONST_EXPR; there is no more folding to do here.  */
      వెళ్ళు బహిర్గతం;

    స్థితి COMPONENT_REF:
      orig_op0 = op0 = వృక్షం_నిర్వాహ్యం (సమాసం, 0);
      op1 = వృక్షం_నిర్వాహ్యం (సమాసం, 1);
      op2 = వృక్షం_నిర్వాహ్యం (సమాసం, 2);
      op0 = c_fully_fold_అంతర్గత (op0, లోపల_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, lval);
      STRIP_TYPE_NOPS (op0);
      ఒకవేళ (op0 != orig_op0)
	ret = build3 (COMPONENT_REF, వృక్షం_TYPE (సమాసం), op0, op1, op2);
      ఒకవేళ (ret != సమాసం)
	{
	  వృక్షం_READONLY (ret) = వృక్షం_READONLY (సమాసం);
	  వృక్షం_THIS_VOLATILE (ret) = వృక్షం_THIS_VOLATILE (సమాసం);
	}
      ఒకవేళ (!lval)
	ret = fold (ret);
      వెళ్ళు బహిర్గతం;

    స్థితి ARRAY_REF:
      orig_op0 = op0 = వృక్షం_నిర్వాహ్యం (సమాసం, 0);
      orig_op1 = op1 = వృక్షం_నిర్వాహ్యం (సమాసం, 1);
      op2 = వృక్షం_నిర్వాహ్యం (సమాసం, 2);
      op3 = వృక్షం_నిర్వాహ్యం (సమాసం, 3);
      op0 = c_fully_fold_అంతర్గత (op0, లోపల_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, lval);
      STRIP_TYPE_NOPS (op0);
      op1 = c_fully_fold_అంతర్గత (op1, లోపల_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, అబద్ధం);
      STRIP_TYPE_NOPS (op1);
      /* Fold "foo"[2] in initializers.  */
      ఒకవేళ (!lval && లోపల_init)
	{
	  ret = c_fold_array_ref (వృక్షం_TYPE (సమాసం), op0, op1);
	  ఒకవేళ (ret)
	    వెళ్ళు బహిర్గతం;
	  ret = సమాసం;
	}
      ఒకవేళ (op0 != orig_op0 || op1 != orig_op1)
	ret = build4 (ARRAY_REF, వృక్షం_TYPE (సమాసం), op0, op1, op2, op3);
      ఒకవేళ (ret != సమాసం)
	{
	  వృక్షం_READONLY (ret) = వృక్షం_READONLY (సమాసం);
	  వృక్షం_SIDE_EFFECTS (ret) = వృక్షం_SIDE_EFFECTS (సమాసం);
	  వృక్షం_THIS_VOLATILE (ret) = వృక్షం_THIS_VOLATILE (సమాసం);
	}
      ఒకవేళ (!lval)
	ret = fold (ret);
      వెళ్ళు బహిర్గతం;

    స్థితి MODIFY_సమాసం:
    స్థితి PREDECREMENT_సమాసం:
    స్థితి PREINCREMENT_సమాసం:
    స్థితి POSTDECREMENT_సమాసం:
    స్థితి POSTINCREMENT_సమాసం:
      op0_lval = నిజం;
      /* FALLTHRU */
    స్థితి COMPOUND_సమాసం:
    స్థితి PLUS_సమాసం:
    స్థితి MINUS_సమాసం:
    స్థితి MULT_సమాసం:
    స్థితి సూచిక_PLUS_సమాసం:
    స్థితి సూచిక_DIFF_సమాసం:
    స్థితి TRUNC_DIV_సమాసం:
    స్థితి CEIL_DIV_సమాసం:
    స్థితి FLOOR_DIV_సమాసం:
    స్థితి TRUNC_MOD_సమాసం:
    స్థితి RDIV_సమాసం:
    స్థితి EXACT_DIV_సమాసం:
    స్థితి LSHIFT_సమాసం:
    స్థితి RSHIFT_సమాసం:
    స్థితి LROTATE_సమాసం:
    స్థితి RROTATE_సమాసం:
    స్థితి బిట్టు_IOR_సమాసం:
    స్థితి బిట్టు_XOR_సమాసం:
    స్థితి బిట్టు_AND_సమాసం:
    స్థితి LT_సమాసం:
    స్థితి LE_సమాసం:
    స్థితి GT_సమాసం:
    స్థితి GE_సమాసం:
    స్థితి EQ_సమాసం:
    స్థితి NE_సమాసం:
    స్థితి COMPLEX_సమాసం:
    స్థితి TRUTH_AND_సమాసం:
    స్థితి TRUTH_OR_సమాసం:
    స్థితి TRUTH_XOR_సమాసం:
    స్థితి UNORDERED_సమాసం:
    స్థితి ORDERED_సమాసం:
    స్థితి UNLT_సమాసం:
    స్థితి UNLE_సమాసం:
    స్థితి UNGT_సమాసం:
    స్థితి UNGE_సమాసం:
    స్థితి UNEQ_సమాసం:
    స్థితి MEM_REF:
      /* Binary operations evaluating both arguments (increment and
	 decrement are binary internally in GCC).  */
      orig_op0 = op0 = వృక్షం_నిర్వాహ్యం (సమాసం, 0);
      orig_op1 = op1 = వృక్షం_నిర్వాహ్యం (సమాసం, 1);
      op0 = c_fully_fold_అంతర్గత (op0, లోపల_init, maybe_const_operands,
				   maybe_const_itself, for_int_const,
				   op0_lval);
      STRIP_TYPE_NOPS (op0);
      /* The RHS of a MODIFY_EXPR was fully folded when building that
	 expression for the sake of conversion warnings.  */
      ఒకవేళ (సంకేతం_2 != MODIFY_సమాసం)
	op1 = c_fully_fold_అంతర్గత (op1, లోపల_init, maybe_const_operands,
				     maybe_const_itself, for_int_const, అబద్ధం);
      STRIP_TYPE_NOPS (op1);

      ఒకవేళ (for_int_const && (వృక్షం_సంకేతం (op0) != INTEGER_CST
			    || వృక్షం_సంకేతం (op1) != INTEGER_CST))
	వెళ్ళు బహిర్గతం;

      ఒకవేళ (వృక్షం_సంకేతం_CLASS (సంకేతం_2) == tcc_comparison
	  && వృక్షం_సంకేతం (వృక్షం_TYPE (op0)) == NULLPTR_TYPE
	  && వృక్షం_సంకేతం (వృక్షం_TYPE (op1)) == NULLPTR_TYPE)
	{
	  ఎంపిక (సంకేతం_2)
	    {
	    స్థితి EQ_సమాసం:
	      ret = constant_boolean_కణుపు (నిజం, వృక్షం_TYPE (సమాసం));
	      ఆపు;
	    స్థితి NE_సమాసం:
	      ret = constant_boolean_కణుపు (అబద్ధం, వృక్షం_TYPE (సమాసం));
	      ఆపు;
	    అప్రమేయ:
	      gcc_unreachable ();
	    }
	  ret = omit_two_operands_loc (loc, వృక్షం_TYPE (సమాసం), ret,
				       op0, op1);
	}
      లేకపోతే ఒకవేళ (op0 != orig_op0 || op1 != orig_op1 || లోపల_init)
	ret = లోపల_init
	  ? fold_build2_initializer_loc (loc, సంకేతం_2, వృక్షం_TYPE (సమాసం), op0, op1)
	  : fold_build2_loc (loc, సంకేతం_2, వృక్షం_TYPE (సమాసం), op0, op1);
      లేకపోతే
	ret = fold (సమాసం);
      ఒకవేళ (వృక్షం_అధికప్రవాహం_P (ret)
	  && !వృక్షం_అధికప్రవాహం_P (op0)
	  && !(ద్విమాన_CLASS_P (op0) && వృక్షం_అధికప్రవాహం_P (వృక్షం_నిర్వాహ్యం (op0, 1)))
	  && !వృక్షం_అధికప్రవాహం_P (op1))
	అధికప్రవాహం_warning (సమాసం_LOC_OR_LOC (సమాసం, ఆదానం_location), ret, సమాసం);
      ఒకవేళ (సంకేతం_2 == LSHIFT_సమాసం
	  && వృక్షం_సంకేతం (orig_op0) != INTEGER_CST
	  && (వృక్షం_సంకేతం (వృక్షం_TYPE (orig_op0)) == INTEGER_TYPE
	      || వృక్షం_సంకేతం (వృక్షం_TYPE (orig_op0)) == BITINT_TYPE)
	  && వృక్షం_సంకేతం (op0) == INTEGER_CST
	  && c_inhibit_evaluation_warnings == 0
	  && !TYPE_అధికప్రవాహం_WRAPS (వృక్షం_TYPE (orig_op0))
	  && వృక్షం_int_cst_sgn (op0) < 0)
	warning_at (loc, OPT_Wshift_negative_విలువ,
		    "left shift of negative value");
      ఒకవేళ ((సంకేతం_2 == LSHIFT_సమాసం
	   || సంకేతం_2 == RSHIFT_సమాసం
	   || సంకేతం_2 == LROTATE_సమాసం
	   || సంకేతం_2 == RROTATE_సమాసం)
	  && వృక్షం_సంకేతం (orig_op1) != INTEGER_CST
	  && వృక్షం_సంకేతం (op1) == INTEGER_CST
	  && వృక్షం_సంకేతం (వృక్షం_TYPE (orig_op1)) == INTEGER_TYPE
	  && c_inhibit_evaluation_warnings == 0)
	{
	  ఒకవేళ (వృక్షం_int_cst_sgn (op1) < 0)
	    warning_at (loc, OPT_Wshift_లెక్క_negative,
			(సంకేతం_2 == LSHIFT_సమాసం
			 ? G_("left shift count is negative")
			 : G_("right shift count is negative")));
	  లేకపోతే ఒకవేళ ((వృక్షం_సంకేతం (వృక్షం_TYPE (orig_op0)) == INTEGER_TYPE
		    || వృక్షం_సంకేతం (వృక్షం_TYPE (orig_op0)) == BITINT_TYPE
		    || వృక్షం_సంకేతం (వృక్షం_TYPE (orig_op0)) == FIXED_బిందువు_TYPE)
		   && compare_వృక్షం_int (op1,
					TYPE_PRECISION (వృక్షం_TYPE (orig_op0)))
		      >= 0
		   && !warning_suppressed_p (సమాసం, OPT_Wshift_లెక్క_అధికప్రవాహం))
	    warning_at (loc, OPT_Wshift_లెక్క_అధికప్రవాహం,
			(సంకేతం_2 == LSHIFT_సమాసం
			 ? G_("left shift count >= width of type")
			 : G_("right shift count >= width of type")));
	  లేకపోతే ఒకవేళ (వృక్షం_సంకేతం (వృక్షం_TYPE (orig_op0)) == సదిశ_TYPE
		   && compare_వృక్షం_int (op1,
					TYPE_PRECISION (వృక్షం_TYPE (వృక్షం_TYPE (orig_op0))))
		      >= 0)
	    warning_at (loc, OPT_Wshift_లెక్క_అధికప్రవాహం,
			సంకేతం_2 == LSHIFT_సమాసం
			? G_("left shift count >= width of vector element")
			: G_("right shift count >= width of vector element"));
	}
      ఒకవేళ (సంకేతం_2 == LSHIFT_సమాసం
	  /* If either OP0 has been folded to INTEGER_CST...  */
	  && ((వృక్షం_సంకేతం (orig_op0) != INTEGER_CST
	       && (వృక్షం_సంకేతం (వృక్షం_TYPE (orig_op0)) == INTEGER_TYPE
		   || వృక్షం_సంకేతం (వృక్షం_TYPE (orig_op0)) == BITINT_TYPE)
	       && వృక్షం_సంకేతం (op0) == INTEGER_CST)
	      /* ...or if OP1 has been folded to INTEGER_CST...  */
	      || (వృక్షం_సంకేతం (orig_op1) != INTEGER_CST
		  && (వృక్షం_సంకేతం (వృక్షం_TYPE (orig_op1)) == INTEGER_TYPE
		      || వృక్షం_సంకేతం (వృక్షం_TYPE (orig_op1)) == BITINT_TYPE)
		  && వృక్షం_సంకేతం (op1) == INTEGER_CST))
	  && c_inhibit_evaluation_warnings == 0)
	/* ...then maybe we can detect an overflow.  */
	maybe_warn_జరుపు_అధికప్రవాహం (loc, op0, op1);
      ఒకవేళ ((సంకేతం_2 == TRUNC_DIV_సమాసం
	   || సంకేతం_2 == CEIL_DIV_సమాసం
	   || సంకేతం_2 == FLOOR_DIV_సమాసం
	   || సంకేతం_2 == EXACT_DIV_సమాసం
	   || సంకేతం_2 == TRUNC_MOD_సమాసం)
	  && వృక్షం_సంకేతం (orig_op1) != INTEGER_CST
	  && వృక్షం_సంకేతం (op1) == INTEGER_CST
	  && (వృక్షం_సంకేతం (వృక్షం_TYPE (orig_op0)) == INTEGER_TYPE
	      || వృక్షం_సంకేతం (వృక్షం_TYPE (orig_op0)) == BITINT_TYPE
	      || వృక్షం_సంకేతం (వృక్షం_TYPE (orig_op0)) == FIXED_బిందువు_TYPE)
	  && (వృక్షం_సంకేతం (వృక్షం_TYPE (orig_op1)) == INTEGER_TYPE
	      || వృక్షం_సంకేతం (వృక్షం_TYPE (orig_op1)) == BITINT_TYPE))
	warn_for_div_by_zero (loc, op1);
      ఒకవేళ (సంకేతం_2 == MEM_REF
	  && ret != సమాసం
	  && వృక్షం_సంకేతం (ret) == MEM_REF)
	{
	  వృక్షం_READONLY (ret) = వృక్షం_READONLY (సమాసం);
	  వృక్షం_SIDE_EFFECTS (ret) = వృక్షం_SIDE_EFFECTS (సమాసం);
	  వృక్షం_THIS_VOLATILE (ret) = వృక్షం_THIS_VOLATILE (సమాసం);
	}
      వెళ్ళు బహిర్గతం;

    స్థితి ADDR_సమాసం:
      op0_lval = నిజం;
      వెళ్ళు unary;
    స్థితి REALPART_సమాసం:
    స్థితి IMAGPART_సమాసం:
    స్థితి VIEW_CONVERT_సమాసం:
      op0_lval = lval;
      /* FALLTHRU */
    స్థితి పరోక్ష_REF:
    స్థితి FIX_TRUNC_సమాసం:
    స్థితి FLOAT_సమాసం:
    CASE_CONVERT:
    స్థితి ADDR_SPACE_CONVERT_సమాసం:
    స్థితి NON_LVALUE_సమాసం:
    స్థితి NEGATE_సమాసం:
    స్థితి బిట్టు_NOT_సమాసం:
    స్థితి TRUTH_NOT_సమాసం:
    స్థితి CONJ_సమాసం:
    స్థితి PAREN_సమాసం:
    unary:
      /* Unary operations.  */
      orig_op0 = op0 = వృక్షం_నిర్వాహ్యం (సమాసం, 0);
      op0 = c_fully_fold_అంతర్గత (op0, లోపల_init, maybe_const_operands,
				   maybe_const_itself, for_int_const,
				   op0_lval);
      STRIP_TYPE_NOPS (op0);

      ఒకవేళ (for_int_const && వృక్షం_సంకేతం (op0) != INTEGER_CST)
	వెళ్ళు బహిర్గతం;

      /* ??? Cope with user tricks that amount to offsetof.  The middle-end is
	 not prepared to deal with them if they occur in initializers.  */
      ఒకవేళ (op0 != orig_op0
	  && సంకేతం_2 == ADDR_సమాసం
	  && (op1 = get_పునాది_చిరునామా (op0)) != NULL_వృక్షం
	  && పరోక్ష_REF_P (op1)
	  && వృక్షం_CONSTANT (వృక్షం_నిర్వాహ్యం (op1, 0)))
	ret = fold_offsetof (op0, వృక్షం_TYPE (సమాసం));
      లేకపోతే ఒకవేళ (op0 != orig_op0 || లోపల_init)
	ret = లోపల_init
	  ? fold_build1_initializer_loc (loc, సంకేతం_2, వృక్షం_TYPE (సమాసం), op0)
	  : fold_build1_loc (loc, సంకేతం_2, వృక్షం_TYPE (సమాసం), op0);
      లేకపోతే
	ret = fold (సమాసం);
      ఒకవేళ (సంకేతం_2 == పరోక్ష_REF
	  && ret != సమాసం
	  && పరోక్ష_REF_P (ret))
	{
	  వృక్షం_READONLY (ret) = వృక్షం_READONLY (సమాసం);
	  వృక్షం_SIDE_EFFECTS (ret) = వృక్షం_SIDE_EFFECTS (సమాసం);
	  వృక్షం_THIS_VOLATILE (ret) = వృక్షం_THIS_VOLATILE (సమాసం);
	}
      ఎంపిక (సంకేతం_2)
	{
	స్థితి FIX_TRUNC_సమాసం:
	స్థితి FLOAT_సమాసం:
	CASE_CONVERT:
	  /* Don't warn about explicit conversions.  We will already
	     have warned about suspect implicit conversions.  */
	  ఆపు;

	అప్రమేయ:
	  ఒకవేళ (వృక్షం_అధికప్రవాహం_P (ret) && !వృక్షం_అధికప్రవాహం_P (op0))
	    అధికప్రవాహం_warning (సమాసం_LOCATION (సమాసం), ret, op0);
	  ఆపు;
	}
      వెళ్ళు బహిర్గతం;

    స్థితి TRUTH_ANDIF_సమాసం:
    స్థితి TRUTH_ORIF_సమాసం:
      /* Binary operations not necessarily evaluating both
	 arguments.  */
      orig_op0 = op0 = వృక్షం_నిర్వాహ్యం (సమాసం, 0);
      orig_op1 = op1 = వృక్షం_నిర్వాహ్యం (సమాసం, 1);
      op0 = c_fully_fold_అంతర్గత (op0, లోపల_init, &op0_const, &op0_const_self,
				   for_int_const, అబద్ధం);
      STRIP_TYPE_NOPS (op0);

      వాడని_p = (op0 == (సంకేతం_2 == TRUTH_ANDIF_సమాసం
			  ? truthvalue_false_కణుపు
			  : truthvalue_true_కణుపు));
      c_disable_warnings (వాడని_p);
      op1 = c_fully_fold_అంతర్గత (op1, లోపల_init, &op1_const, &op1_const_self,
				   for_int_const, అబద్ధం);
      STRIP_TYPE_NOPS (op1);
      c_enable_warnings (వాడని_p);

      ఒకవేళ (for_int_const
	  && (వృక్షం_సంకేతం (op0) != INTEGER_CST
	      /* Require OP1 be an INTEGER_CST only if it's evaluated.  */
	      || (!వాడని_p && వృక్షం_సంకేతం (op1) != INTEGER_CST)))
	వెళ్ళు బహిర్గతం;

      ఒకవేళ (op0 != orig_op0 || op1 != orig_op1 || లోపల_init)
	ret = లోపల_init
	  ? fold_build2_initializer_loc (loc, సంకేతం_2, వృక్షం_TYPE (సమాసం), op0, op1)
	  : fold_build2_loc (loc, సంకేతం_2, వృక్షం_TYPE (సమాసం), op0, op1);
      లేకపోతే
	ret = fold (సమాసం);
      *maybe_const_operands &= op0_const;
      *maybe_const_itself &= op0_const_self;
      ఒకవేళ (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && (సంకేతం_2 == TRUTH_ANDIF_సమాసం
		? op0 == truthvalue_false_కణుపు
		: op0 == truthvalue_true_కణుపు)))
	*maybe_const_operands &= op1_const;
      ఒకవేళ (!(op0_const
	    && op0_const_self
	    && (సంకేతం_2 == TRUTH_ANDIF_సమాసం
		? op0 == truthvalue_false_కణుపు
		: op0 == truthvalue_true_కణుపు)))
	*maybe_const_itself &= op1_const_self;
      వెళ్ళు బహిర్గతం;

    స్థితి COND_సమాసం:
      orig_op0 = op0 = వృక్షం_నిర్వాహ్యం (సమాసం, 0);
      orig_op1 = op1 = వృక్షం_నిర్వాహ్యం (సమాసం, 1);
      orig_op2 = op2 = వృక్షం_నిర్వాహ్యం (సమాసం, 2);
      op0 = c_fully_fold_అంతర్గత (op0, లోపల_init, &op0_const, &op0_const_self,
				   for_int_const, అబద్ధం);

      STRIP_TYPE_NOPS (op0);
      c_disable_warnings (op0 == truthvalue_false_కణుపు);
      op1 = c_fully_fold_అంతర్గత (op1, లోపల_init, &op1_const, &op1_const_self,
				   for_int_const, అబద్ధం);
      STRIP_TYPE_NOPS (op1);
      c_enable_warnings (op0 == truthvalue_false_కణుపు);

      c_disable_warnings (op0 == truthvalue_true_కణుపు);
      op2 = c_fully_fold_అంతర్గత (op2, లోపల_init, &op2_const, &op2_const_self,
				   for_int_const, అబద్ధం);
      STRIP_TYPE_NOPS (op2);
      c_enable_warnings (op0 == truthvalue_true_కణుపు);

      ఒకవేళ (for_int_const
	  && (వృక్షం_సంకేతం (op0) != INTEGER_CST
	      /* Only the evaluated operand must be an INTEGER_CST.  */
	      || (op0 == truthvalue_true_కణుపు
		  ? వృక్షం_సంకేతం (op1) != INTEGER_CST
		  : వృక్షం_సంకేతం (op2) != INTEGER_CST)))
	వెళ్ళు బహిర్గతం;

      ఒకవేళ (op0 != orig_op0 || op1 != orig_op1 || op2 != orig_op2)
	ret = fold_build3_loc (loc, సంకేతం_2, వృక్షం_TYPE (సమాసం), op0, op1, op2);
      లేకపోతే
	ret = fold (సమాసం);
      *maybe_const_operands &= op0_const;
      *maybe_const_itself &= op0_const_self;
      ఒకవేళ (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && op0 == truthvalue_false_కణుపు))
	*maybe_const_operands &= op1_const;
      ఒకవేళ (!(op0_const
	    && op0_const_self
	    && op0 == truthvalue_false_కణుపు))
	*maybe_const_itself &= op1_const_self;
      ఒకవేళ (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && op0 == truthvalue_true_కణుపు))
	*maybe_const_operands &= op2_const;
      ఒకవేళ (!(op0_const
	    && op0_const_self
	    && op0 == truthvalue_true_కణుపు))
	*maybe_const_itself &= op2_const_self;
      వెళ్ళు బహిర్గతం;

    స్థితి VEC_COND_సమాసం:
      orig_op0 = op0 = వృక్షం_నిర్వాహ్యం (సమాసం, 0);
      orig_op1 = op1 = వృక్షం_నిర్వాహ్యం (సమాసం, 1);
      orig_op2 = op2 = వృక్షం_నిర్వాహ్యం (సమాసం, 2);
      op0 = c_fully_fold_అంతర్గత (op0, లోపల_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, అబద్ధం);
      STRIP_TYPE_NOPS (op0);
      op1 = c_fully_fold_అంతర్గత (op1, లోపల_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, అబద్ధం);
      STRIP_TYPE_NOPS (op1);
      op2 = c_fully_fold_అంతర్గత (op2, లోపల_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, అబద్ధం);
      STRIP_TYPE_NOPS (op2);

      ఒకవేళ (op0 != orig_op0 || op1 != orig_op1 || op2 != orig_op2)
	ret = fold_build3_loc (loc, సంకేతం_2, వృక్షం_TYPE (సమాసం), op0, op1, op2);
      లేకపోతే
	ret = fold (సమాసం);
      వెళ్ళు బహిర్గతం;

    స్థితి EXCESS_PRECISION_సమాసం:
      /* Each case where an operand with excess precision may be
	 encountered must remove the EXCESS_PRECISION_EXPR around
	 inner operands and possibly put one around the whole
	 expression or possibly convert to the semantic type (which
	 c_fully_fold does); we cannot tell at this stage which is
	 appropriate in any particular case.  */
      gcc_unreachable ();

    స్థితి SAVE_సమాసం:
      /* Make sure to fold the contents of a SAVE_EXPR exactly once.  */
      op0 = వృక్షం_నిర్వాహ్యం (సమాసం, 0);
      ఒకవేళ (!SAVE_సమాసం_FOLDED_P (సమాసం))
	{
	  op0 = c_fully_fold_అంతర్గత (op0, లోపల_init, maybe_const_operands,
				       maybe_const_itself, for_int_const,
				       అబద్ధం);
	  వృక్షం_నిర్వాహ్యం (సమాసం, 0) = op0;
	  SAVE_సమాసం_FOLDED_P (సమాసం) = నిజం;
	}
      /* Return the SAVE_EXPR operand if it is invariant.  */
      ఒకవేళ (వృక్షం_invariant_p (op0))
	ret = op0;
      వెళ్ళు బహిర్గతం;

    అప్రమేయ:
      /* Various codes may appear through folding built-in functions
	 and their arguments.  */
      వెళ్ళు బహిర్గతం;
    }

 బహిర్గతం:
  /* Some folding may introduce NON_LVALUE_EXPRs; all lvalue checks
     have been done by this point, so remove them again.  */
  nowarning |= warning_suppressed_p (ret, OPT_Woverflow);
  STRIP_TYPE_NOPS (ret);
  ఒకవేళ (nowarning && !warning_suppressed_p (ret, OPT_Woverflow))
    {
      ఒకవేళ (!CAN_HAVE_LOCATION_P (ret))
	ret = build1 (NOP_సమాసం, వృక్షం_TYPE (ret), ret);
      suppress_warning (ret, OPT_Woverflow);
    }
  ఒకవేళ (ret != సమాసం)
    {
      protected_సమితి_సమాసం_location (ret, loc);
      ఒకవేళ (IS_సమాసం_సంకేతం_CLASS (రకం))
	సమితి_ఆధారం_range (ret, old_range.m_ప్రారంభం, old_range.m_ముగింపు);
    }
  తిరిగి ret;
}

/* Fold X for consideration by one of the warning functions when checking
   whether an expression has a constant value.  */

వృక్షం
fold_for_warn (వృక్షం x)
{
  /* The C front-end has already folded X appropriately.  */
  తిరిగి x;
}
