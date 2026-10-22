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

#ضمن "config.h"
#ضمن "system.h"
#ضمن "coretypes.h"
#ضمن "target.h"
#ضمن "function.h"
#ضمن "bitmap.h"
#ضمن "c-tree.h"
#ضمن "intl.h"
#ضمن "gimplify.h"

ساكن ونه c_fully_fold_دننی (ونه بیان, منطقي, منطقي *, منطقي *, منطقي,
				   منطقي);

/* If DISABLE is true, stop issuing warnings.  This is used when
   parsing code that we know will not be executed.  This function may
   be called multiple times, and works as a stack.  */

ساكن فراغ
c_disable_warnings (منطقي disable)
{
  إذا (disable)
    {
      ++c_inhibit_evaluation_warnings;
    }
}

/* If ENABLE is true, re-enable issuing warnings.  */

ساكن فراغ
c_enable_warnings (منطقي enable)
{
  إذا (enable)
    {
      --c_inhibit_evaluation_warnings;
    }
}

/* Try to fold ARRAY_REF ary[index] if possible and not handled by
   normal fold, return NULL_TREE otherwise.  */

ساكن ونه
c_fold_array_ref (ونه type, ونه ary, ونه شاخص)
{
  إذا (ونه_کوډ (ary) != STRING_CST
      || ونه_کوډ (شاخص) != INTEGER_CST
      || ونه_ډکېدنه (شاخص)
      || ونه_کوډ (ونه_TYPE (ary)) != ARRAY_TYPE
      || !ونه_ځاییږي_uhwi_p (شاخص))
    أرجع NULL_ونه;

  ونه elem_type = ونه_TYPE (ونه_TYPE (ary));
  بینښه elem_nchars = (TYPE_PRECISION (elem_type)
			  / TYPE_PRECISION (char_type_غوټه));
  بینښه len = (بینښه) ونه_STRING_اوږدتیا (ary) / elem_nchars;
  ونه nelts_minus_one = array_type_nelts_minus_one (ونه_TYPE (ary));
  منطقي dummy1 = ریښتیا, dummy2 = ریښتیا;
  nelts_minus_one = c_fully_fold_دننی (nelts_minus_one, ریښتیا, &dummy1,
					   &dummy2, خطأ, خطأ);
  بینښه HOST_WIDE_INT i = ونه_منزل_uhwi (شاخص);
  إذا (!ونه_int_cst_le (شاخص, nelts_minus_one)
      || i >= len
      || i + elem_nchars > len)
    أرجع NULL_ونه;

  إذا (elem_nchars == 1)
    أرجع build_int_cst (type, ونه_STRING_اشاره_ګر (ary)[i]);

  ثابت بینښه حرف *ptr
    = ((ثابت بینښه حرف *)ونه_STRING_اشاره_ګر (ary) + i * elem_nchars);
  أرجع native_interpret_بیان (type, ptr, elem_nchars);
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

ونه
c_fully_fold (ونه بیان, منطقي دننه_init, منطقي *maybe_const, منطقي lval)
{
  ونه ret;
  ونه eptype = NULL_ونه;
  منطقي dummy = ریښتیا;
  منطقي maybe_const_itself = ریښتیا;
  location_t loc = بیان_LOCATION (بیان);

  إذا (!maybe_const)
    maybe_const = &dummy;
  إذا (ونه_کوډ (بیان) == EXCESS_PRECISION_بیان)
    {
      eptype = ونه_TYPE (بیان);
      بیان = ونه_عملوند (بیان, 0);
    }
  ret = c_fully_fold_دننی (بیان, دننه_init, maybe_const,
			       &maybe_const_itself, خطأ, lval);
  إذا (eptype)
    ret = fold_convert_loc (loc, eptype, ret);
  *maybe_const &= maybe_const_itself;
  أرجع ret;
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

ساكن ونه
c_fully_fold_دننی (ونه بیان, منطقي دننه_init, منطقي *maybe_const_operands,
		       منطقي *maybe_const_itself, منطقي for_int_const, منطقي lval)
{
  ونه ret = بیان;
  تعداد ونه_کوډ_2 کوډ = ونه_کوډ (بیان);
  تعداد ونه_کوډ_class ډول = ونه_کوډ_CLASS (کوډ);
  location_t loc = بیان_LOCATION (بیان);
  ونه op0, op1, op2, op3;
  ونه orig_op0, orig_op1, orig_op2;
  منطقي op0_const = ریښتیا, op1_const = ریښتیا, op2_const = ریښتیا;
  منطقي op0_const_self = ریښتیا, op1_const_self = ریښتیا, op2_const_self = ریښتیا;
  منطقي nowarning = warning_suppressed_p (بیان, OPT_Woverflow);
  منطقي ناکارول_شوی_p;
  منطقي op0_lval = خطأ;
  سرچینه_range old_range;

  /* Constants, declarations, statements, errors, and anything else not
     counted as an expression cannot usefully be folded further at this
     point.  */
  إذا (!IS_بیان_کوډ_CLASS (ډول) || ډول == tcc_statement)
    {
      /* Except for variables which we can optimize to its initializer.  */
      إذا (VAR_P (بیان) && !lval && (optimize || دننه_init))
	{
	  إذا (دننه_init)
	    ret = decl_constant_ارزښت_1 (بیان, ریښتیا);
	  وإلا
	    {
	      ret = decl_constant_ارزښت (بیان);
	      إذا (ret != بیان
		  && (TYPE_ډېرپېښ (ونه_TYPE (ret)) == BLKmode
		      || ونه_کوډ (ونه_TYPE (ret)) == ARRAY_TYPE))
		أرجع بیان;
	    }
	  /* Avoid unwanted tree sharing between the initializer and current
	     function's body where the tree can be modified e.g. by the
	     gimplifier.  */
	  إذا (ret != بیان && ونه_STATIC (بیان))
	    ret = unshare_بیان (ret);
	  أرجع ret;
	}
      أرجع بیان;
    }

  إذا (IS_بیان_کوډ_CLASS (ډول))
    old_range = بیان_LOCATION_RANGE (بیان);

  /* Operands of variable-length expressions (function calls) have
     already been folded, as have __builtin_* function calls, and such
     expressions cannot occur in constant expressions.  */
  إذا (ډول == tcc_vl_exp)
    {
      *maybe_const_operands = خطأ;
      ret = fold (بیان);
      اذهب بهر;
    }

  إذا (کوډ == C_MAYBE_CONST_بیان)
    {
      ونه pre = C_MAYBE_CONST_بیان_PRE (بیان);
      ونه inner = C_MAYBE_CONST_بیان_بیان (بیان);
      إذا (C_MAYBE_CONST_بیان_NON_CONST (بیان))
	*maybe_const_operands = خطأ;
      إذا (C_MAYBE_CONST_بیان_INT_OPERANDS (بیان))
	{
	  *maybe_const_itself = خطأ;
	  inner = c_fully_fold_دننی (inner, دننه_init, maybe_const_operands,
					 maybe_const_itself, ریښتیا, lval);
	}
      إذا (pre && !دننه_init)
	ret = build2 (COMPOUND_بیان, ونه_TYPE (بیان), pre, inner);
      وإلا
	ret = inner;
      اذهب بهر;
    }

  /* Assignment, increment, decrement, function call and comma
     operators, and statement expressions, cannot occur in constant
     expressions if evaluated / outside of sizeof.  (Function calls
     were handled above, though VA_ARG_EXPR is treated like a function
     call here, and statement expressions are handled through
     C_MAYBE_CONST_EXPR to avoid folding inside them.)  */
  بدل (کوډ)
    {
    حالة MODIFY_بیان:
    حالة PREDECREMENT_بیان:
    حالة PREINCREMENT_بیان:
    حالة POSTDECREMENT_بیان:
    حالة POSTINCREMENT_بیان:
    حالة COMPOUND_بیان:
      *maybe_const_operands = خطأ;
      اكسر;

    حالة VA_ARG_بیان:
    حالة موخه_بیان:
    حالة BIND_بیان:
    حالة OBJ_TYPE_REF:
      *maybe_const_operands = خطأ;
      ret = fold (بیان);
      اذهب بهر;

    افتراضي:
      اكسر;
    }

  /* Fold individual tree codes as appropriate.  */
  بدل (کوډ)
    {
    حالة COMPOUND_LITERAL_بیان:
      /* Any non-constancy will have been marked in a containing
	 C_MAYBE_CONST_EXPR; there is no more folding to do here.  */
      اذهب بهر;

    حالة COMPONENT_REF:
      orig_op0 = op0 = ونه_عملوند (بیان, 0);
      op1 = ونه_عملوند (بیان, 1);
      op2 = ونه_عملوند (بیان, 2);
      op0 = c_fully_fold_دننی (op0, دننه_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, lval);
      STRIP_TYPE_NOPS (op0);
      إذا (op0 != orig_op0)
	ret = build3 (COMPONENT_REF, ونه_TYPE (بیان), op0, op1, op2);
      إذا (ret != بیان)
	{
	  ونه_READONLY (ret) = ونه_READONLY (بیان);
	  ونه_THIS_VOLATILE (ret) = ونه_THIS_VOLATILE (بیان);
	}
      إذا (!lval)
	ret = fold (ret);
      اذهب بهر;

    حالة ARRAY_REF:
      orig_op0 = op0 = ونه_عملوند (بیان, 0);
      orig_op1 = op1 = ونه_عملوند (بیان, 1);
      op2 = ونه_عملوند (بیان, 2);
      op3 = ونه_عملوند (بیان, 3);
      op0 = c_fully_fold_دننی (op0, دننه_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, lval);
      STRIP_TYPE_NOPS (op0);
      op1 = c_fully_fold_دننی (op1, دننه_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, خطأ);
      STRIP_TYPE_NOPS (op1);
      /* Fold "foo"[2] in initializers.  */
      إذا (!lval && دننه_init)
	{
	  ret = c_fold_array_ref (ونه_TYPE (بیان), op0, op1);
	  إذا (ret)
	    اذهب بهر;
	  ret = بیان;
	}
      إذا (op0 != orig_op0 || op1 != orig_op1)
	ret = build4 (ARRAY_REF, ونه_TYPE (بیان), op0, op1, op2, op3);
      إذا (ret != بیان)
	{
	  ونه_READONLY (ret) = ونه_READONLY (بیان);
	  ونه_SIDE_EFFECTS (ret) = ونه_SIDE_EFFECTS (بیان);
	  ونه_THIS_VOLATILE (ret) = ونه_THIS_VOLATILE (بیان);
	}
      إذا (!lval)
	ret = fold (ret);
      اذهب بهر;

    حالة MODIFY_بیان:
    حالة PREDECREMENT_بیان:
    حالة PREINCREMENT_بیان:
    حالة POSTDECREMENT_بیان:
    حالة POSTINCREMENT_بیان:
      op0_lval = ریښتیا;
      /* FALLTHRU */
    حالة COMPOUND_بیان:
    حالة PLUS_بیان:
    حالة MINUS_بیان:
    حالة MULT_بیان:
    حالة اشاره_ګر_PLUS_بیان:
    حالة اشاره_ګر_DIFF_بیان:
    حالة TRUNC_DIV_بیان:
    حالة CEIL_DIV_بیان:
    حالة FLOOR_DIV_بیان:
    حالة TRUNC_MOD_بیان:
    حالة RDIV_بیان:
    حالة EXACT_DIV_بیان:
    حالة LSHIFT_بیان:
    حالة RSHIFT_بیان:
    حالة LROTATE_بیان:
    حالة RROTATE_بیان:
    حالة بټ_IOR_بیان:
    حالة بټ_XOR_بیان:
    حالة بټ_AND_بیان:
    حالة LT_بیان:
    حالة LE_بیان:
    حالة GT_بیان:
    حالة GE_بیان:
    حالة EQ_بیان:
    حالة NE_بیان:
    حالة COMPLEX_بیان:
    حالة TRUTH_AND_بیان:
    حالة TRUTH_OR_بیان:
    حالة TRUTH_XOR_بیان:
    حالة UNORDERED_بیان:
    حالة ORDERED_بیان:
    حالة UNLT_بیان:
    حالة UNLE_بیان:
    حالة UNGT_بیان:
    حالة UNGE_بیان:
    حالة UNEQ_بیان:
    حالة MEM_REF:
      /* Binary operations evaluating both arguments (increment and
	 decrement are binary internally in GCC).  */
      orig_op0 = op0 = ونه_عملوند (بیان, 0);
      orig_op1 = op1 = ونه_عملوند (بیان, 1);
      op0 = c_fully_fold_دننی (op0, دننه_init, maybe_const_operands,
				   maybe_const_itself, for_int_const,
				   op0_lval);
      STRIP_TYPE_NOPS (op0);
      /* The RHS of a MODIFY_EXPR was fully folded when building that
	 expression for the sake of conversion warnings.  */
      إذا (کوډ != MODIFY_بیان)
	op1 = c_fully_fold_دننی (op1, دننه_init, maybe_const_operands,
				     maybe_const_itself, for_int_const, خطأ);
      STRIP_TYPE_NOPS (op1);

      إذا (for_int_const && (ونه_کوډ (op0) != INTEGER_CST
			    || ونه_کوډ (op1) != INTEGER_CST))
	اذهب بهر;

      إذا (ونه_کوډ_CLASS (کوډ) == tcc_comparison
	  && ونه_کوډ (ونه_TYPE (op0)) == NULLPTR_TYPE
	  && ونه_کوډ (ونه_TYPE (op1)) == NULLPTR_TYPE)
	{
	  بدل (کوډ)
	    {
	    حالة EQ_بیان:
	      ret = constant_boolean_غوټه (ریښتیا, ونه_TYPE (بیان));
	      اكسر;
	    حالة NE_بیان:
	      ret = constant_boolean_غوټه (خطأ, ونه_TYPE (بیان));
	      اكسر;
	    افتراضي:
	      gcc_unreachable ();
	    }
	  ret = omit_two_operands_loc (loc, ونه_TYPE (بیان), ret,
				       op0, op1);
	}
      وإلا إذا (op0 != orig_op0 || op1 != orig_op1 || دننه_init)
	ret = دننه_init
	  ? fold_build2_initializer_loc (loc, کوډ, ونه_TYPE (بیان), op0, op1)
	  : fold_build2_loc (loc, کوډ, ونه_TYPE (بیان), op0, op1);
      وإلا
	ret = fold (بیان);
      إذا (ونه_ډکېدنه_P (ret)
	  && !ونه_ډکېدنه_P (op0)
	  && !(دوګونی_CLASS_P (op0) && ونه_ډکېدنه_P (ونه_عملوند (op0, 1)))
	  && !ونه_ډکېدنه_P (op1))
	ډکېدنه_warning (بیان_LOC_OR_LOC (بیان, ننوت_location), ret, بیان);
      إذا (کوډ == LSHIFT_بیان
	  && ونه_کوډ (orig_op0) != INTEGER_CST
	  && (ونه_کوډ (ونه_TYPE (orig_op0)) == INTEGER_TYPE
	      || ونه_کوډ (ونه_TYPE (orig_op0)) == BITINT_TYPE)
	  && ونه_کوډ (op0) == INTEGER_CST
	  && c_inhibit_evaluation_warnings == 0
	  && !TYPE_ډکېدنه_WRAPS (ونه_TYPE (orig_op0))
	  && ونه_int_cst_sgn (op0) < 0)
	warning_at (loc, OPT_Wshift_negative_ارزښت,
		    "left shift of negative value");
      إذا ((کوډ == LSHIFT_بیان
	   || کوډ == RSHIFT_بیان
	   || کوډ == LROTATE_بیان
	   || کوډ == RROTATE_بیان)
	  && ونه_کوډ (orig_op1) != INTEGER_CST
	  && ونه_کوډ (op1) == INTEGER_CST
	  && ونه_کوډ (ونه_TYPE (orig_op1)) == INTEGER_TYPE
	  && c_inhibit_evaluation_warnings == 0)
	{
	  إذا (ونه_int_cst_sgn (op1) < 0)
	    warning_at (loc, OPT_Wshift_شمېر_negative,
			(کوډ == LSHIFT_بیان
			 ? G_("left shift count is negative")
			 : G_("right shift count is negative")));
	  وإلا إذا ((ونه_کوډ (ونه_TYPE (orig_op0)) == INTEGER_TYPE
		    || ونه_کوډ (ونه_TYPE (orig_op0)) == BITINT_TYPE
		    || ونه_کوډ (ونه_TYPE (orig_op0)) == FIXED_ټکی_TYPE)
		   && compare_ونه_int (op1,
					TYPE_PRECISION (ونه_TYPE (orig_op0)))
		      >= 0
		   && !warning_suppressed_p (بیان, OPT_Wshift_شمېر_ډکېدنه))
	    warning_at (loc, OPT_Wshift_شمېر_ډکېدنه,
			(کوډ == LSHIFT_بیان
			 ? G_("left shift count >= width of type")
			 : G_("right shift count >= width of type")));
	  وإلا إذا (ونه_کوډ (ونه_TYPE (orig_op0)) == ویکټور_TYPE
		   && compare_ونه_int (op1,
					TYPE_PRECISION (ونه_TYPE (ونه_TYPE (orig_op0))))
		      >= 0)
	    warning_at (loc, OPT_Wshift_شمېر_ډکېدنه,
			کوډ == LSHIFT_بیان
			? G_("left shift count >= width of vector element")
			: G_("right shift count >= width of vector element"));
	}
      إذا (کوډ == LSHIFT_بیان
	  /* If either OP0 has been folded to INTEGER_CST...  */
	  && ((ونه_کوډ (orig_op0) != INTEGER_CST
	       && (ونه_کوډ (ونه_TYPE (orig_op0)) == INTEGER_TYPE
		   || ونه_کوډ (ونه_TYPE (orig_op0)) == BITINT_TYPE)
	       && ونه_کوډ (op0) == INTEGER_CST)
	      /* ...or if OP1 has been folded to INTEGER_CST...  */
	      || (ونه_کوډ (orig_op1) != INTEGER_CST
		  && (ونه_کوډ (ونه_TYPE (orig_op1)) == INTEGER_TYPE
		      || ونه_کوډ (ونه_TYPE (orig_op1)) == BITINT_TYPE)
		  && ونه_کوډ (op1) == INTEGER_CST))
	  && c_inhibit_evaluation_warnings == 0)
	/* ...then maybe we can detect an overflow.  */
	maybe_warn_ښويدنه_ډکېدنه (loc, op0, op1);
      إذا ((کوډ == TRUNC_DIV_بیان
	   || کوډ == CEIL_DIV_بیان
	   || کوډ == FLOOR_DIV_بیان
	   || کوډ == EXACT_DIV_بیان
	   || کوډ == TRUNC_MOD_بیان)
	  && ونه_کوډ (orig_op1) != INTEGER_CST
	  && ونه_کوډ (op1) == INTEGER_CST
	  && (ونه_کوډ (ونه_TYPE (orig_op0)) == INTEGER_TYPE
	      || ونه_کوډ (ونه_TYPE (orig_op0)) == BITINT_TYPE
	      || ونه_کوډ (ونه_TYPE (orig_op0)) == FIXED_ټکی_TYPE)
	  && (ونه_کوډ (ونه_TYPE (orig_op1)) == INTEGER_TYPE
	      || ونه_کوډ (ونه_TYPE (orig_op1)) == BITINT_TYPE))
	warn_for_div_by_zero (loc, op1);
      إذا (کوډ == MEM_REF
	  && ret != بیان
	  && ونه_کوډ (ret) == MEM_REF)
	{
	  ونه_READONLY (ret) = ونه_READONLY (بیان);
	  ونه_SIDE_EFFECTS (ret) = ونه_SIDE_EFFECTS (بیان);
	  ونه_THIS_VOLATILE (ret) = ونه_THIS_VOLATILE (بیان);
	}
      اذهب بهر;

    حالة ADDR_بیان:
      op0_lval = ریښتیا;
      اذهب unary;
    حالة REALPART_بیان:
    حالة IMAGPART_بیان:
    حالة VIEW_CONVERT_بیان:
      op0_lval = lval;
      /* FALLTHRU */
    حالة غیرمستقیم_REF:
    حالة FIX_TRUNC_بیان:
    حالة FLOAT_بیان:
    CASE_CONVERT:
    حالة ADDR_SPACE_CONVERT_بیان:
    حالة NON_LVALUE_بیان:
    حالة NEGATE_بیان:
    حالة بټ_NOT_بیان:
    حالة TRUTH_NOT_بیان:
    حالة CONJ_بیان:
    حالة PAREN_بیان:
    unary:
      /* Unary operations.  */
      orig_op0 = op0 = ونه_عملوند (بیان, 0);
      op0 = c_fully_fold_دننی (op0, دننه_init, maybe_const_operands,
				   maybe_const_itself, for_int_const,
				   op0_lval);
      STRIP_TYPE_NOPS (op0);

      إذا (for_int_const && ونه_کوډ (op0) != INTEGER_CST)
	اذهب بهر;

      /* ??? Cope with user tricks that amount to offsetof.  The middle-end is
	 not prepared to deal with them if they occur in initializers.  */
      إذا (op0 != orig_op0
	  && کوډ == ADDR_بیان
	  && (op1 = get_بنسټ_پته (op0)) != NULL_ونه
	  && غیرمستقیم_REF_P (op1)
	  && ونه_CONSTANT (ونه_عملوند (op1, 0)))
	ret = fold_offsetof (op0, ونه_TYPE (بیان));
      وإلا إذا (op0 != orig_op0 || دننه_init)
	ret = دننه_init
	  ? fold_build1_initializer_loc (loc, کوډ, ونه_TYPE (بیان), op0)
	  : fold_build1_loc (loc, کوډ, ونه_TYPE (بیان), op0);
      وإلا
	ret = fold (بیان);
      إذا (کوډ == غیرمستقیم_REF
	  && ret != بیان
	  && غیرمستقیم_REF_P (ret))
	{
	  ونه_READONLY (ret) = ونه_READONLY (بیان);
	  ونه_SIDE_EFFECTS (ret) = ونه_SIDE_EFFECTS (بیان);
	  ونه_THIS_VOLATILE (ret) = ونه_THIS_VOLATILE (بیان);
	}
      بدل (کوډ)
	{
	حالة FIX_TRUNC_بیان:
	حالة FLOAT_بیان:
	CASE_CONVERT:
	  /* Don't warn about explicit conversions.  We will already
	     have warned about suspect implicit conversions.  */
	  اكسر;

	افتراضي:
	  إذا (ونه_ډکېدنه_P (ret) && !ونه_ډکېدنه_P (op0))
	    ډکېدنه_warning (بیان_LOCATION (بیان), ret, op0);
	  اكسر;
	}
      اذهب بهر;

    حالة TRUTH_ANDIF_بیان:
    حالة TRUTH_ORIF_بیان:
      /* Binary operations not necessarily evaluating both
	 arguments.  */
      orig_op0 = op0 = ونه_عملوند (بیان, 0);
      orig_op1 = op1 = ونه_عملوند (بیان, 1);
      op0 = c_fully_fold_دننی (op0, دننه_init, &op0_const, &op0_const_self,
				   for_int_const, خطأ);
      STRIP_TYPE_NOPS (op0);

      ناکارول_شوی_p = (op0 == (کوډ == TRUTH_ANDIF_بیان
			  ? truthvalue_false_غوټه
			  : truthvalue_true_غوټه));
      c_disable_warnings (ناکارول_شوی_p);
      op1 = c_fully_fold_دننی (op1, دننه_init, &op1_const, &op1_const_self,
				   for_int_const, خطأ);
      STRIP_TYPE_NOPS (op1);
      c_enable_warnings (ناکارول_شوی_p);

      إذا (for_int_const
	  && (ونه_کوډ (op0) != INTEGER_CST
	      /* Require OP1 be an INTEGER_CST only if it's evaluated.  */
	      || (!ناکارول_شوی_p && ونه_کوډ (op1) != INTEGER_CST)))
	اذهب بهر;

      إذا (op0 != orig_op0 || op1 != orig_op1 || دننه_init)
	ret = دننه_init
	  ? fold_build2_initializer_loc (loc, کوډ, ونه_TYPE (بیان), op0, op1)
	  : fold_build2_loc (loc, کوډ, ونه_TYPE (بیان), op0, op1);
      وإلا
	ret = fold (بیان);
      *maybe_const_operands &= op0_const;
      *maybe_const_itself &= op0_const_self;
      إذا (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && (کوډ == TRUTH_ANDIF_بیان
		? op0 == truthvalue_false_غوټه
		: op0 == truthvalue_true_غوټه)))
	*maybe_const_operands &= op1_const;
      إذا (!(op0_const
	    && op0_const_self
	    && (کوډ == TRUTH_ANDIF_بیان
		? op0 == truthvalue_false_غوټه
		: op0 == truthvalue_true_غوټه)))
	*maybe_const_itself &= op1_const_self;
      اذهب بهر;

    حالة COND_بیان:
      orig_op0 = op0 = ونه_عملوند (بیان, 0);
      orig_op1 = op1 = ونه_عملوند (بیان, 1);
      orig_op2 = op2 = ونه_عملوند (بیان, 2);
      op0 = c_fully_fold_دننی (op0, دننه_init, &op0_const, &op0_const_self,
				   for_int_const, خطأ);

      STRIP_TYPE_NOPS (op0);
      c_disable_warnings (op0 == truthvalue_false_غوټه);
      op1 = c_fully_fold_دننی (op1, دننه_init, &op1_const, &op1_const_self,
				   for_int_const, خطأ);
      STRIP_TYPE_NOPS (op1);
      c_enable_warnings (op0 == truthvalue_false_غوټه);

      c_disable_warnings (op0 == truthvalue_true_غوټه);
      op2 = c_fully_fold_دننی (op2, دننه_init, &op2_const, &op2_const_self,
				   for_int_const, خطأ);
      STRIP_TYPE_NOPS (op2);
      c_enable_warnings (op0 == truthvalue_true_غوټه);

      إذا (for_int_const
	  && (ونه_کوډ (op0) != INTEGER_CST
	      /* Only the evaluated operand must be an INTEGER_CST.  */
	      || (op0 == truthvalue_true_غوټه
		  ? ونه_کوډ (op1) != INTEGER_CST
		  : ونه_کوډ (op2) != INTEGER_CST)))
	اذهب بهر;

      إذا (op0 != orig_op0 || op1 != orig_op1 || op2 != orig_op2)
	ret = fold_build3_loc (loc, کوډ, ونه_TYPE (بیان), op0, op1, op2);
      وإلا
	ret = fold (بیان);
      *maybe_const_operands &= op0_const;
      *maybe_const_itself &= op0_const_self;
      إذا (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && op0 == truthvalue_false_غوټه))
	*maybe_const_operands &= op1_const;
      إذا (!(op0_const
	    && op0_const_self
	    && op0 == truthvalue_false_غوټه))
	*maybe_const_itself &= op1_const_self;
      إذا (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && op0 == truthvalue_true_غوټه))
	*maybe_const_operands &= op2_const;
      إذا (!(op0_const
	    && op0_const_self
	    && op0 == truthvalue_true_غوټه))
	*maybe_const_itself &= op2_const_self;
      اذهب بهر;

    حالة VEC_COND_بیان:
      orig_op0 = op0 = ونه_عملوند (بیان, 0);
      orig_op1 = op1 = ونه_عملوند (بیان, 1);
      orig_op2 = op2 = ونه_عملوند (بیان, 2);
      op0 = c_fully_fold_دننی (op0, دننه_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, خطأ);
      STRIP_TYPE_NOPS (op0);
      op1 = c_fully_fold_دننی (op1, دننه_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, خطأ);
      STRIP_TYPE_NOPS (op1);
      op2 = c_fully_fold_دننی (op2, دننه_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, خطأ);
      STRIP_TYPE_NOPS (op2);

      إذا (op0 != orig_op0 || op1 != orig_op1 || op2 != orig_op2)
	ret = fold_build3_loc (loc, کوډ, ونه_TYPE (بیان), op0, op1, op2);
      وإلا
	ret = fold (بیان);
      اذهب بهر;

    حالة EXCESS_PRECISION_بیان:
      /* Each case where an operand with excess precision may be
	 encountered must remove the EXCESS_PRECISION_EXPR around
	 inner operands and possibly put one around the whole
	 expression or possibly convert to the semantic type (which
	 c_fully_fold does); we cannot tell at this stage which is
	 appropriate in any particular case.  */
      gcc_unreachable ();

    حالة SAVE_بیان:
      /* Make sure to fold the contents of a SAVE_EXPR exactly once.  */
      op0 = ونه_عملوند (بیان, 0);
      إذا (!SAVE_بیان_FOLDED_P (بیان))
	{
	  op0 = c_fully_fold_دننی (op0, دننه_init, maybe_const_operands,
				       maybe_const_itself, for_int_const,
				       خطأ);
	  ونه_عملوند (بیان, 0) = op0;
	  SAVE_بیان_FOLDED_P (بیان) = ریښتیا;
	}
      /* Return the SAVE_EXPR operand if it is invariant.  */
      إذا (ونه_invariant_p (op0))
	ret = op0;
      اذهب بهر;

    افتراضي:
      /* Various codes may appear through folding built-in functions
	 and their arguments.  */
      اذهب بهر;
    }

 بهر:
  /* Some folding may introduce NON_LVALUE_EXPRs; all lvalue checks
     have been done by this point, so remove them again.  */
  nowarning |= warning_suppressed_p (ret, OPT_Woverflow);
  STRIP_TYPE_NOPS (ret);
  إذا (nowarning && !warning_suppressed_p (ret, OPT_Woverflow))
    {
      إذا (!CAN_HAVE_LOCATION_P (ret))
	ret = build1 (NOP_بیان, ونه_TYPE (ret), ret);
      suppress_warning (ret, OPT_Woverflow);
    }
  إذا (ret != بیان)
    {
      protected_سېټ_بیان_location (ret, loc);
      إذا (IS_بیان_کوډ_CLASS (ډول))
	سېټ_سرچینه_range (ret, old_range.m_پیل, old_range.m_پای);
    }
  أرجع ret;
}

/* Fold X for consideration by one of the warning functions when checking
   whether an expression has a constant value.  */

ونه
fold_for_warn (ونه x)
{
  /* The C front-end has already folded X appropriately.  */
  أرجع x;
}
