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

#شامل "config.h"
#شامل "system.h"
#شامل "coretypes.h"
#شامل "target.h"
#شامل "function.h"
#شامل "bitmap.h"
#شامل "c-tree.h"
#شامل "intl.h"
#شامل "gimplify.h"

ساکن درخت c_fully_fold_اندرونی (درخت اظہاریہ, منطقی, منطقی *, منطقی *, منطقی,
				   منطقی);

/* If DISABLE is true, stop issuing warnings.  This is used when
   parsing code that we know will not be executed.  This function may
   be called multiple times, and works as a stack.  */

ساکن خالی
c_disable_warnings (منطقی disable)
{
  اگر (disable)
    {
      ++c_inhibit_evaluation_warnings;
    }
}

/* If ENABLE is true, re-enable issuing warnings.  */

ساکن خالی
c_enable_warnings (منطقی enable)
{
  اگر (enable)
    {
      --c_inhibit_evaluation_warnings;
    }
}

/* Try to fold ARRAY_REF ary[index] if possible and not handled by
   normal fold, return NULL_TREE otherwise.  */

ساکن درخت
c_fold_array_ref (درخت type, درخت ary, درخت اشاریہ)
{
  اگر (درخت_رمز (ary) != STRING_CST
      || درخت_رمز (اشاریہ) != INTEGER_CST
      || درخت_حد_سے_تجاوز (اشاریہ)
      || درخت_رمز (درخت_TYPE (ary)) != ARRAY_TYPE
      || !درخت_سماتا_uhwi_p (اشاریہ))
    واپس NULL_درخت;

  درخت elem_type = درخت_TYPE (درخت_TYPE (ary));
  غیرعلامتی elem_nchars = (TYPE_PRECISION (elem_type)
			  / TYPE_PRECISION (char_type_گرہ));
  غیرعلامتی len = (غیرعلامتی) درخت_STRING_لمبائی (ary) / elem_nchars;
  درخت nelts_minus_one = array_type_nelts_minus_one (درخت_TYPE (ary));
  منطقی dummy1 = سچ, dummy2 = سچ;
  nelts_minus_one = c_fully_fold_اندرونی (nelts_minus_one, سچ, &dummy1,
					   &dummy2, جھوٹ, جھوٹ);
  غیرعلامتی HOST_WIDE_INT i = درخت_مقصد_uhwi (اشاریہ);
  اگر (!درخت_int_cst_le (اشاریہ, nelts_minus_one)
      || i >= len
      || i + elem_nchars > len)
    واپس NULL_درخت;

  اگر (elem_nchars == 1)
    واپس build_int_cst (type, درخت_STRING_اشارہ_گر (ary)[i]);

  ثابت غیرعلامتی حرف *ptr
    = ((ثابت غیرعلامتی حرف *)درخت_STRING_اشارہ_گر (ary) + i * elem_nchars);
  واپس native_interpret_اظہاریہ (type, ptr, elem_nchars);
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

درخت
c_fully_fold (درخت اظہاریہ, منطقی اندر_init, منطقی *maybe_const, منطقی lval)
{
  درخت ret;
  درخت eptype = NULL_درخت;
  منطقی dummy = سچ;
  منطقی maybe_const_itself = سچ;
  location_t loc = اظہاریہ_LOCATION (اظہاریہ);

  اگر (!maybe_const)
    maybe_const = &dummy;
  اگر (درخت_رمز (اظہاریہ) == EXCESS_PRECISION_اظہاریہ)
    {
      eptype = درخت_TYPE (اظہاریہ);
      اظہاریہ = درخت_عملیہ (اظہاریہ, 0);
    }
  ret = c_fully_fold_اندرونی (اظہاریہ, اندر_init, maybe_const,
			       &maybe_const_itself, جھوٹ, lval);
  اگر (eptype)
    ret = fold_convert_loc (loc, eptype, ret);
  *maybe_const &= maybe_const_itself;
  واپس ret;
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

ساکن درخت
c_fully_fold_اندرونی (درخت اظہاریہ, منطقی اندر_init, منطقی *maybe_const_operands,
		       منطقی *maybe_const_itself, منطقی for_int_const, منطقی lval)
{
  درخت ret = اظہاریہ;
  شمار درخت_رمز_2 رمز = درخت_رمز (اظہاریہ);
  شمار درخت_رمز_class قسم = درخت_رمز_CLASS (رمز);
  location_t loc = اظہاریہ_LOCATION (اظہاریہ);
  درخت op0, op1, op2, op3;
  درخت orig_op0, orig_op1, orig_op2;
  منطقی op0_const = سچ, op1_const = سچ, op2_const = سچ;
  منطقی op0_const_self = سچ, op1_const_self = سچ, op2_const_self = سچ;
  منطقی nowarning = warning_suppressed_p (اظہاریہ, OPT_Woverflow);
  منطقی غیر_مستعمل_p;
  منطقی op0_lval = جھوٹ;
  ماخذ_range old_range;

  /* Constants, declarations, statements, errors, and anything else not
     counted as an expression cannot usefully be folded further at this
     point.  */
  اگر (!IS_اظہاریہ_رمز_CLASS (قسم) || قسم == tcc_statement)
    {
      /* Except for variables which we can optimize to its initializer.  */
      اگر (VAR_P (اظہاریہ) && !lval && (optimize || اندر_init))
	{
	  اگر (اندر_init)
	    ret = decl_constant_قدر_1 (اظہاریہ, سچ);
	  ورنہ
	    {
	      ret = decl_constant_قدر (اظہاریہ);
	      اگر (ret != اظہاریہ
		  && (TYPE_منوال (درخت_TYPE (ret)) == BLKmode
		      || درخت_رمز (درخت_TYPE (ret)) == ARRAY_TYPE))
		واپس اظہاریہ;
	    }
	  /* Avoid unwanted tree sharing between the initializer and current
	     function's body where the tree can be modified e.g. by the
	     gimplifier.  */
	  اگر (ret != اظہاریہ && درخت_STATIC (اظہاریہ))
	    ret = unshare_اظہاریہ (ret);
	  واپس ret;
	}
      واپس اظہاریہ;
    }

  اگر (IS_اظہاریہ_رمز_CLASS (قسم))
    old_range = اظہاریہ_LOCATION_RANGE (اظہاریہ);

  /* Operands of variable-length expressions (function calls) have
     already been folded, as have __builtin_* function calls, and such
     expressions cannot occur in constant expressions.  */
  اگر (قسم == tcc_vl_exp)
    {
      *maybe_const_operands = جھوٹ;
      ret = fold (اظہاریہ);
      جاؤ برآمد;
    }

  اگر (رمز == C_MAYBE_CONST_اظہاریہ)
    {
      درخت pre = C_MAYBE_CONST_اظہاریہ_PRE (اظہاریہ);
      درخت inner = C_MAYBE_CONST_اظہاریہ_اظہاریہ (اظہاریہ);
      اگر (C_MAYBE_CONST_اظہاریہ_NON_CONST (اظہاریہ))
	*maybe_const_operands = جھوٹ;
      اگر (C_MAYBE_CONST_اظہاریہ_INT_OPERANDS (اظہاریہ))
	{
	  *maybe_const_itself = جھوٹ;
	  inner = c_fully_fold_اندرونی (inner, اندر_init, maybe_const_operands,
					 maybe_const_itself, سچ, lval);
	}
      اگر (pre && !اندر_init)
	ret = build2 (COMPOUND_اظہاریہ, درخت_TYPE (اظہاریہ), pre, inner);
      ورنہ
	ret = inner;
      جاؤ برآمد;
    }

  /* Assignment, increment, decrement, function call and comma
     operators, and statement expressions, cannot occur in constant
     expressions if evaluated / outside of sizeof.  (Function calls
     were handled above, though VA_ARG_EXPR is treated like a function
     call here, and statement expressions are handled through
     C_MAYBE_CONST_EXPR to avoid folding inside them.)  */
  انتخاب (رمز)
    {
    حالت MODIFY_اظہاریہ:
    حالت PREDECREMENT_اظہاریہ:
    حالت PREINCREMENT_اظہاریہ:
    حالت POSTDECREMENT_اظہاریہ:
    حالت POSTINCREMENT_اظہاریہ:
    حالت COMPOUND_اظہاریہ:
      *maybe_const_operands = جھوٹ;
      توڑو;

    حالت VA_ARG_اظہاریہ:
    حالت ہدف_اظہاریہ:
    حالت BIND_اظہاریہ:
    حالت OBJ_TYPE_REF:
      *maybe_const_operands = جھوٹ;
      ret = fold (اظہاریہ);
      جاؤ برآمد;

    طےشدہ:
      توڑو;
    }

  /* Fold individual tree codes as appropriate.  */
  انتخاب (رمز)
    {
    حالت COMPOUND_LITERAL_اظہاریہ:
      /* Any non-constancy will have been marked in a containing
	 C_MAYBE_CONST_EXPR; there is no more folding to do here.  */
      جاؤ برآمد;

    حالت COMPONENT_REF:
      orig_op0 = op0 = درخت_عملیہ (اظہاریہ, 0);
      op1 = درخت_عملیہ (اظہاریہ, 1);
      op2 = درخت_عملیہ (اظہاریہ, 2);
      op0 = c_fully_fold_اندرونی (op0, اندر_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, lval);
      STRIP_TYPE_NOPS (op0);
      اگر (op0 != orig_op0)
	ret = build3 (COMPONENT_REF, درخت_TYPE (اظہاریہ), op0, op1, op2);
      اگر (ret != اظہاریہ)
	{
	  درخت_READONLY (ret) = درخت_READONLY (اظہاریہ);
	  درخت_THIS_VOLATILE (ret) = درخت_THIS_VOLATILE (اظہاریہ);
	}
      اگر (!lval)
	ret = fold (ret);
      جاؤ برآمد;

    حالت ARRAY_REF:
      orig_op0 = op0 = درخت_عملیہ (اظہاریہ, 0);
      orig_op1 = op1 = درخت_عملیہ (اظہاریہ, 1);
      op2 = درخت_عملیہ (اظہاریہ, 2);
      op3 = درخت_عملیہ (اظہاریہ, 3);
      op0 = c_fully_fold_اندرونی (op0, اندر_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, lval);
      STRIP_TYPE_NOPS (op0);
      op1 = c_fully_fold_اندرونی (op1, اندر_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, جھوٹ);
      STRIP_TYPE_NOPS (op1);
      /* Fold "foo"[2] in initializers.  */
      اگر (!lval && اندر_init)
	{
	  ret = c_fold_array_ref (درخت_TYPE (اظہاریہ), op0, op1);
	  اگر (ret)
	    جاؤ برآمد;
	  ret = اظہاریہ;
	}
      اگر (op0 != orig_op0 || op1 != orig_op1)
	ret = build4 (ARRAY_REF, درخت_TYPE (اظہاریہ), op0, op1, op2, op3);
      اگر (ret != اظہاریہ)
	{
	  درخت_READONLY (ret) = درخت_READONLY (اظہاریہ);
	  درخت_SIDE_EFFECTS (ret) = درخت_SIDE_EFFECTS (اظہاریہ);
	  درخت_THIS_VOLATILE (ret) = درخت_THIS_VOLATILE (اظہاریہ);
	}
      اگر (!lval)
	ret = fold (ret);
      جاؤ برآمد;

    حالت MODIFY_اظہاریہ:
    حالت PREDECREMENT_اظہاریہ:
    حالت PREINCREMENT_اظہاریہ:
    حالت POSTDECREMENT_اظہاریہ:
    حالت POSTINCREMENT_اظہاریہ:
      op0_lval = سچ;
      /* FALLTHRU */
    حالت COMPOUND_اظہاریہ:
    حالت PLUS_اظہاریہ:
    حالت MINUS_اظہاریہ:
    حالت MULT_اظہاریہ:
    حالت اشارہ_گر_PLUS_اظہاریہ:
    حالت اشارہ_گر_DIFF_اظہاریہ:
    حالت TRUNC_DIV_اظہاریہ:
    حالت CEIL_DIV_اظہاریہ:
    حالت FLOOR_DIV_اظہاریہ:
    حالت TRUNC_MOD_اظہاریہ:
    حالت RDIV_اظہاریہ:
    حالت EXACT_DIV_اظہاریہ:
    حالت LSHIFT_اظہاریہ:
    حالت RSHIFT_اظہاریہ:
    حالت LROTATE_اظہاریہ:
    حالت RROTATE_اظہاریہ:
    حالت ثنائی_ہندسہ_IOR_اظہاریہ:
    حالت ثنائی_ہندسہ_XOR_اظہاریہ:
    حالت ثنائی_ہندسہ_AND_اظہاریہ:
    حالت LT_اظہاریہ:
    حالت LE_اظہاریہ:
    حالت GT_اظہاریہ:
    حالت GE_اظہاریہ:
    حالت EQ_اظہاریہ:
    حالت NE_اظہاریہ:
    حالت COMPLEX_اظہاریہ:
    حالت TRUTH_AND_اظہاریہ:
    حالت TRUTH_OR_اظہاریہ:
    حالت TRUTH_XOR_اظہاریہ:
    حالت UNORDERED_اظہاریہ:
    حالت ORDERED_اظہاریہ:
    حالت UNLT_اظہاریہ:
    حالت UNLE_اظہاریہ:
    حالت UNGT_اظہاریہ:
    حالت UNGE_اظہاریہ:
    حالت UNEQ_اظہاریہ:
    حالت MEM_REF:
      /* Binary operations evaluating both arguments (increment and
	 decrement are binary internally in GCC).  */
      orig_op0 = op0 = درخت_عملیہ (اظہاریہ, 0);
      orig_op1 = op1 = درخت_عملیہ (اظہاریہ, 1);
      op0 = c_fully_fold_اندرونی (op0, اندر_init, maybe_const_operands,
				   maybe_const_itself, for_int_const,
				   op0_lval);
      STRIP_TYPE_NOPS (op0);
      /* The RHS of a MODIFY_EXPR was fully folded when building that
	 expression for the sake of conversion warnings.  */
      اگر (رمز != MODIFY_اظہاریہ)
	op1 = c_fully_fold_اندرونی (op1, اندر_init, maybe_const_operands,
				     maybe_const_itself, for_int_const, جھوٹ);
      STRIP_TYPE_NOPS (op1);

      اگر (for_int_const && (درخت_رمز (op0) != INTEGER_CST
			    || درخت_رمز (op1) != INTEGER_CST))
	جاؤ برآمد;

      اگر (درخت_رمز_CLASS (رمز) == tcc_comparison
	  && درخت_رمز (درخت_TYPE (op0)) == NULLPTR_TYPE
	  && درخت_رمز (درخت_TYPE (op1)) == NULLPTR_TYPE)
	{
	  انتخاب (رمز)
	    {
	    حالت EQ_اظہاریہ:
	      ret = constant_boolean_گرہ (سچ, درخت_TYPE (اظہاریہ));
	      توڑو;
	    حالت NE_اظہاریہ:
	      ret = constant_boolean_گرہ (جھوٹ, درخت_TYPE (اظہاریہ));
	      توڑو;
	    طےشدہ:
	      gcc_unreachable ();
	    }
	  ret = omit_two_operands_loc (loc, درخت_TYPE (اظہاریہ), ret,
				       op0, op1);
	}
      ورنہ اگر (op0 != orig_op0 || op1 != orig_op1 || اندر_init)
	ret = اندر_init
	  ? fold_build2_initializer_loc (loc, رمز, درخت_TYPE (اظہاریہ), op0, op1)
	  : fold_build2_loc (loc, رمز, درخت_TYPE (اظہاریہ), op0, op1);
      ورنہ
	ret = fold (اظہاریہ);
      اگر (درخت_حد_سے_تجاوز_P (ret)
	  && !درخت_حد_سے_تجاوز_P (op0)
	  && !(ثنائی_CLASS_P (op0) && درخت_حد_سے_تجاوز_P (درخت_عملیہ (op0, 1)))
	  && !درخت_حد_سے_تجاوز_P (op1))
	حد_سے_تجاوز_warning (اظہاریہ_LOC_OR_LOC (اظہاریہ, داخلہ_location), ret, اظہاریہ);
      اگر (رمز == LSHIFT_اظہاریہ
	  && درخت_رمز (orig_op0) != INTEGER_CST
	  && (درخت_رمز (درخت_TYPE (orig_op0)) == INTEGER_TYPE
	      || درخت_رمز (درخت_TYPE (orig_op0)) == BITINT_TYPE)
	  && درخت_رمز (op0) == INTEGER_CST
	  && c_inhibit_evaluation_warnings == 0
	  && !TYPE_حد_سے_تجاوز_WRAPS (درخت_TYPE (orig_op0))
	  && درخت_int_cst_sgn (op0) < 0)
	warning_at (loc, OPT_Wshift_negative_قدر,
		    "left shift of negative value");
      اگر ((رمز == LSHIFT_اظہاریہ
	   || رمز == RSHIFT_اظہاریہ
	   || رمز == LROTATE_اظہاریہ
	   || رمز == RROTATE_اظہاریہ)
	  && درخت_رمز (orig_op1) != INTEGER_CST
	  && درخت_رمز (op1) == INTEGER_CST
	  && درخت_رمز (درخت_TYPE (orig_op1)) == INTEGER_TYPE
	  && c_inhibit_evaluation_warnings == 0)
	{
	  اگر (درخت_int_cst_sgn (op1) < 0)
	    warning_at (loc, OPT_Wshift_گنتی_negative,
			(رمز == LSHIFT_اظہاریہ
			 ? G_("left shift count is negative")
			 : G_("right shift count is negative")));
	  ورنہ اگر ((درخت_رمز (درخت_TYPE (orig_op0)) == INTEGER_TYPE
		    || درخت_رمز (درخت_TYPE (orig_op0)) == BITINT_TYPE
		    || درخت_رمز (درخت_TYPE (orig_op0)) == FIXED_نقطہ_TYPE)
		   && compare_درخت_int (op1,
					TYPE_PRECISION (درخت_TYPE (orig_op0)))
		      >= 0
		   && !warning_suppressed_p (اظہاریہ, OPT_Wshift_گنتی_حد_سے_تجاوز))
	    warning_at (loc, OPT_Wshift_گنتی_حد_سے_تجاوز,
			(رمز == LSHIFT_اظہاریہ
			 ? G_("left shift count >= width of type")
			 : G_("right shift count >= width of type")));
	  ورنہ اگر (درخت_رمز (درخت_TYPE (orig_op0)) == سمتیہ_TYPE
		   && compare_درخت_int (op1,
					TYPE_PRECISION (درخت_TYPE (درخت_TYPE (orig_op0))))
		      >= 0)
	    warning_at (loc, OPT_Wshift_گنتی_حد_سے_تجاوز,
			رمز == LSHIFT_اظہاریہ
			? G_("left shift count >= width of vector element")
			: G_("right shift count >= width of vector element"));
	}
      اگر (رمز == LSHIFT_اظہاریہ
	  /* If either OP0 has been folded to INTEGER_CST...  */
	  && ((درخت_رمز (orig_op0) != INTEGER_CST
	       && (درخت_رمز (درخت_TYPE (orig_op0)) == INTEGER_TYPE
		   || درخت_رمز (درخت_TYPE (orig_op0)) == BITINT_TYPE)
	       && درخت_رمز (op0) == INTEGER_CST)
	      /* ...or if OP1 has been folded to INTEGER_CST...  */
	      || (درخت_رمز (orig_op1) != INTEGER_CST
		  && (درخت_رمز (درخت_TYPE (orig_op1)) == INTEGER_TYPE
		      || درخت_رمز (درخت_TYPE (orig_op1)) == BITINT_TYPE)
		  && درخت_رمز (op1) == INTEGER_CST))
	  && c_inhibit_evaluation_warnings == 0)
	/* ...then maybe we can detect an overflow.  */
	maybe_warn_سرکاؤ_حد_سے_تجاوز (loc, op0, op1);
      اگر ((رمز == TRUNC_DIV_اظہاریہ
	   || رمز == CEIL_DIV_اظہاریہ
	   || رمز == FLOOR_DIV_اظہاریہ
	   || رمز == EXACT_DIV_اظہاریہ
	   || رمز == TRUNC_MOD_اظہاریہ)
	  && درخت_رمز (orig_op1) != INTEGER_CST
	  && درخت_رمز (op1) == INTEGER_CST
	  && (درخت_رمز (درخت_TYPE (orig_op0)) == INTEGER_TYPE
	      || درخت_رمز (درخت_TYPE (orig_op0)) == BITINT_TYPE
	      || درخت_رمز (درخت_TYPE (orig_op0)) == FIXED_نقطہ_TYPE)
	  && (درخت_رمز (درخت_TYPE (orig_op1)) == INTEGER_TYPE
	      || درخت_رمز (درخت_TYPE (orig_op1)) == BITINT_TYPE))
	warn_for_div_by_zero (loc, op1);
      اگر (رمز == MEM_REF
	  && ret != اظہاریہ
	  && درخت_رمز (ret) == MEM_REF)
	{
	  درخت_READONLY (ret) = درخت_READONLY (اظہاریہ);
	  درخت_SIDE_EFFECTS (ret) = درخت_SIDE_EFFECTS (اظہاریہ);
	  درخت_THIS_VOLATILE (ret) = درخت_THIS_VOLATILE (اظہاریہ);
	}
      جاؤ برآمد;

    حالت ADDR_اظہاریہ:
      op0_lval = سچ;
      جاؤ unary;
    حالت REALPART_اظہاریہ:
    حالت IMAGPART_اظہاریہ:
    حالت VIEW_CONVERT_اظہاریہ:
      op0_lval = lval;
      /* FALLTHRU */
    حالت بالواسطہ_REF:
    حالت FIX_TRUNC_اظہاریہ:
    حالت FLOAT_اظہاریہ:
    CASE_CONVERT:
    حالت ADDR_SPACE_CONVERT_اظہاریہ:
    حالت NON_LVALUE_اظہاریہ:
    حالت NEGATE_اظہاریہ:
    حالت ثنائی_ہندسہ_NOT_اظہاریہ:
    حالت TRUTH_NOT_اظہاریہ:
    حالت CONJ_اظہاریہ:
    حالت PAREN_اظہاریہ:
    unary:
      /* Unary operations.  */
      orig_op0 = op0 = درخت_عملیہ (اظہاریہ, 0);
      op0 = c_fully_fold_اندرونی (op0, اندر_init, maybe_const_operands,
				   maybe_const_itself, for_int_const,
				   op0_lval);
      STRIP_TYPE_NOPS (op0);

      اگر (for_int_const && درخت_رمز (op0) != INTEGER_CST)
	جاؤ برآمد;

      /* ??? Cope with user tricks that amount to offsetof.  The middle-end is
	 not prepared to deal with them if they occur in initializers.  */
      اگر (op0 != orig_op0
	  && رمز == ADDR_اظہاریہ
	  && (op1 = get_بنیاد_پتہ (op0)) != NULL_درخت
	  && بالواسطہ_REF_P (op1)
	  && درخت_CONSTANT (درخت_عملیہ (op1, 0)))
	ret = fold_offsetof (op0, درخت_TYPE (اظہاریہ));
      ورنہ اگر (op0 != orig_op0 || اندر_init)
	ret = اندر_init
	  ? fold_build1_initializer_loc (loc, رمز, درخت_TYPE (اظہاریہ), op0)
	  : fold_build1_loc (loc, رمز, درخت_TYPE (اظہاریہ), op0);
      ورنہ
	ret = fold (اظہاریہ);
      اگر (رمز == بالواسطہ_REF
	  && ret != اظہاریہ
	  && بالواسطہ_REF_P (ret))
	{
	  درخت_READONLY (ret) = درخت_READONLY (اظہاریہ);
	  درخت_SIDE_EFFECTS (ret) = درخت_SIDE_EFFECTS (اظہاریہ);
	  درخت_THIS_VOLATILE (ret) = درخت_THIS_VOLATILE (اظہاریہ);
	}
      انتخاب (رمز)
	{
	حالت FIX_TRUNC_اظہاریہ:
	حالت FLOAT_اظہاریہ:
	CASE_CONVERT:
	  /* Don't warn about explicit conversions.  We will already
	     have warned about suspect implicit conversions.  */
	  توڑو;

	طےشدہ:
	  اگر (درخت_حد_سے_تجاوز_P (ret) && !درخت_حد_سے_تجاوز_P (op0))
	    حد_سے_تجاوز_warning (اظہاریہ_LOCATION (اظہاریہ), ret, op0);
	  توڑو;
	}
      جاؤ برآمد;

    حالت TRUTH_ANDIF_اظہاریہ:
    حالت TRUTH_ORIF_اظہاریہ:
      /* Binary operations not necessarily evaluating both
	 arguments.  */
      orig_op0 = op0 = درخت_عملیہ (اظہاریہ, 0);
      orig_op1 = op1 = درخت_عملیہ (اظہاریہ, 1);
      op0 = c_fully_fold_اندرونی (op0, اندر_init, &op0_const, &op0_const_self,
				   for_int_const, جھوٹ);
      STRIP_TYPE_NOPS (op0);

      غیر_مستعمل_p = (op0 == (رمز == TRUTH_ANDIF_اظہاریہ
			  ? truthvalue_false_گرہ
			  : truthvalue_true_گرہ));
      c_disable_warnings (غیر_مستعمل_p);
      op1 = c_fully_fold_اندرونی (op1, اندر_init, &op1_const, &op1_const_self,
				   for_int_const, جھوٹ);
      STRIP_TYPE_NOPS (op1);
      c_enable_warnings (غیر_مستعمل_p);

      اگر (for_int_const
	  && (درخت_رمز (op0) != INTEGER_CST
	      /* Require OP1 be an INTEGER_CST only if it's evaluated.  */
	      || (!غیر_مستعمل_p && درخت_رمز (op1) != INTEGER_CST)))
	جاؤ برآمد;

      اگر (op0 != orig_op0 || op1 != orig_op1 || اندر_init)
	ret = اندر_init
	  ? fold_build2_initializer_loc (loc, رمز, درخت_TYPE (اظہاریہ), op0, op1)
	  : fold_build2_loc (loc, رمز, درخت_TYPE (اظہاریہ), op0, op1);
      ورنہ
	ret = fold (اظہاریہ);
      *maybe_const_operands &= op0_const;
      *maybe_const_itself &= op0_const_self;
      اگر (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && (رمز == TRUTH_ANDIF_اظہاریہ
		? op0 == truthvalue_false_گرہ
		: op0 == truthvalue_true_گرہ)))
	*maybe_const_operands &= op1_const;
      اگر (!(op0_const
	    && op0_const_self
	    && (رمز == TRUTH_ANDIF_اظہاریہ
		? op0 == truthvalue_false_گرہ
		: op0 == truthvalue_true_گرہ)))
	*maybe_const_itself &= op1_const_self;
      جاؤ برآمد;

    حالت COND_اظہاریہ:
      orig_op0 = op0 = درخت_عملیہ (اظہاریہ, 0);
      orig_op1 = op1 = درخت_عملیہ (اظہاریہ, 1);
      orig_op2 = op2 = درخت_عملیہ (اظہاریہ, 2);
      op0 = c_fully_fold_اندرونی (op0, اندر_init, &op0_const, &op0_const_self,
				   for_int_const, جھوٹ);

      STRIP_TYPE_NOPS (op0);
      c_disable_warnings (op0 == truthvalue_false_گرہ);
      op1 = c_fully_fold_اندرونی (op1, اندر_init, &op1_const, &op1_const_self,
				   for_int_const, جھوٹ);
      STRIP_TYPE_NOPS (op1);
      c_enable_warnings (op0 == truthvalue_false_گرہ);

      c_disable_warnings (op0 == truthvalue_true_گرہ);
      op2 = c_fully_fold_اندرونی (op2, اندر_init, &op2_const, &op2_const_self,
				   for_int_const, جھوٹ);
      STRIP_TYPE_NOPS (op2);
      c_enable_warnings (op0 == truthvalue_true_گرہ);

      اگر (for_int_const
	  && (درخت_رمز (op0) != INTEGER_CST
	      /* Only the evaluated operand must be an INTEGER_CST.  */
	      || (op0 == truthvalue_true_گرہ
		  ? درخت_رمز (op1) != INTEGER_CST
		  : درخت_رمز (op2) != INTEGER_CST)))
	جاؤ برآمد;

      اگر (op0 != orig_op0 || op1 != orig_op1 || op2 != orig_op2)
	ret = fold_build3_loc (loc, رمز, درخت_TYPE (اظہاریہ), op0, op1, op2);
      ورنہ
	ret = fold (اظہاریہ);
      *maybe_const_operands &= op0_const;
      *maybe_const_itself &= op0_const_self;
      اگر (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && op0 == truthvalue_false_گرہ))
	*maybe_const_operands &= op1_const;
      اگر (!(op0_const
	    && op0_const_self
	    && op0 == truthvalue_false_گرہ))
	*maybe_const_itself &= op1_const_self;
      اگر (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && op0 == truthvalue_true_گرہ))
	*maybe_const_operands &= op2_const;
      اگر (!(op0_const
	    && op0_const_self
	    && op0 == truthvalue_true_گرہ))
	*maybe_const_itself &= op2_const_self;
      جاؤ برآمد;

    حالت VEC_COND_اظہاریہ:
      orig_op0 = op0 = درخت_عملیہ (اظہاریہ, 0);
      orig_op1 = op1 = درخت_عملیہ (اظہاریہ, 1);
      orig_op2 = op2 = درخت_عملیہ (اظہاریہ, 2);
      op0 = c_fully_fold_اندرونی (op0, اندر_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, جھوٹ);
      STRIP_TYPE_NOPS (op0);
      op1 = c_fully_fold_اندرونی (op1, اندر_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, جھوٹ);
      STRIP_TYPE_NOPS (op1);
      op2 = c_fully_fold_اندرونی (op2, اندر_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, جھوٹ);
      STRIP_TYPE_NOPS (op2);

      اگر (op0 != orig_op0 || op1 != orig_op1 || op2 != orig_op2)
	ret = fold_build3_loc (loc, رمز, درخت_TYPE (اظہاریہ), op0, op1, op2);
      ورنہ
	ret = fold (اظہاریہ);
      جاؤ برآمد;

    حالت EXCESS_PRECISION_اظہاریہ:
      /* Each case where an operand with excess precision may be
	 encountered must remove the EXCESS_PRECISION_EXPR around
	 inner operands and possibly put one around the whole
	 expression or possibly convert to the semantic type (which
	 c_fully_fold does); we cannot tell at this stage which is
	 appropriate in any particular case.  */
      gcc_unreachable ();

    حالت SAVE_اظہاریہ:
      /* Make sure to fold the contents of a SAVE_EXPR exactly once.  */
      op0 = درخت_عملیہ (اظہاریہ, 0);
      اگر (!SAVE_اظہاریہ_FOLDED_P (اظہاریہ))
	{
	  op0 = c_fully_fold_اندرونی (op0, اندر_init, maybe_const_operands,
				       maybe_const_itself, for_int_const,
				       جھوٹ);
	  درخت_عملیہ (اظہاریہ, 0) = op0;
	  SAVE_اظہاریہ_FOLDED_P (اظہاریہ) = سچ;
	}
      /* Return the SAVE_EXPR operand if it is invariant.  */
      اگر (درخت_invariant_p (op0))
	ret = op0;
      جاؤ برآمد;

    طےشدہ:
      /* Various codes may appear through folding built-in functions
	 and their arguments.  */
      جاؤ برآمد;
    }

 برآمد:
  /* Some folding may introduce NON_LVALUE_EXPRs; all lvalue checks
     have been done by this point, so remove them again.  */
  nowarning |= warning_suppressed_p (ret, OPT_Woverflow);
  STRIP_TYPE_NOPS (ret);
  اگر (nowarning && !warning_suppressed_p (ret, OPT_Woverflow))
    {
      اگر (!CAN_HAVE_LOCATION_P (ret))
	ret = build1 (NOP_اظہاریہ, درخت_TYPE (ret), ret);
      suppress_warning (ret, OPT_Woverflow);
    }
  اگر (ret != اظہاریہ)
    {
      protected_سیٹ_اظہاریہ_location (ret, loc);
      اگر (IS_اظہاریہ_رمز_CLASS (قسم))
	سیٹ_ماخذ_range (ret, old_range.m_آغاز, old_range.m_اختتام);
    }
  واپس ret;
}

/* Fold X for consideration by one of the warning functions when checking
   whether an expression has a constant value.  */

درخت
fold_for_warn (درخت x)
{
  /* The C front-end has already folded X appropriately.  */
  واپس x;
}
