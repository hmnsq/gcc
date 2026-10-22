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

ساكن درخت c_fully_fold_داخلی (درخت عبارت, منطقي, منطقي *, منطقي *, منطقي,
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

ساكن درخت
c_fold_array_ref (درخت type, درخت ary, درخت شاخص)
{
  إذا (درخت_کد (ary) != STRING_CST
      || درخت_کد (شاخص) != INTEGER_CST
      || درخت_سرریز (شاخص)
      || درخت_کد (درخت_TYPE (ary)) != ARRAY_TYPE
      || !درخت_میگنجد_uhwi_p (شاخص))
    أرجع NULL_درخت;

  درخت elem_type = درخت_TYPE (درخت_TYPE (ary));
  بیعلامت elem_nchars = (TYPE_PRECISION (elem_type)
			  / TYPE_PRECISION (char_type_گره));
  بیعلامت len = (بیعلامت) درخت_STRING_درازی (ary) / elem_nchars;
  درخت nelts_minus_one = array_type_nelts_minus_one (درخت_TYPE (ary));
  منطقي dummy1 = درست, dummy2 = درست;
  nelts_minus_one = c_fully_fold_داخلی (nelts_minus_one, درست, &dummy1,
					   &dummy2, خطأ, خطأ);
  بیعلامت HOST_WIDE_INT i = درخت_مقصد_uhwi (شاخص);
  إذا (!درخت_int_cst_le (شاخص, nelts_minus_one)
      || i >= len
      || i + elem_nchars > len)
    أرجع NULL_درخت;

  إذا (elem_nchars == 1)
    أرجع build_int_cst (type, درخت_STRING_اشاره_گر (ary)[i]);

  ثابت بیعلامت حرف *ptr
    = ((ثابت بیعلامت حرف *)درخت_STRING_اشاره_گر (ary) + i * elem_nchars);
  أرجع native_interpret_عبارت (type, ptr, elem_nchars);
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
c_fully_fold (درخت عبارت, منطقي درون_init, منطقي *maybe_const, منطقي lval)
{
  درخت ret;
  درخت eptype = NULL_درخت;
  منطقي dummy = درست;
  منطقي maybe_const_itself = درست;
  location_t loc = عبارت_LOCATION (عبارت);

  إذا (!maybe_const)
    maybe_const = &dummy;
  إذا (درخت_کد (عبارت) == EXCESS_PRECISION_عبارت)
    {
      eptype = درخت_TYPE (عبارت);
      عبارت = درخت_عملوند (عبارت, 0);
    }
  ret = c_fully_fold_داخلی (عبارت, درون_init, maybe_const,
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

ساكن درخت
c_fully_fold_داخلی (درخت عبارت, منطقي درون_init, منطقي *maybe_const_operands,
		       منطقي *maybe_const_itself, منطقي for_int_const, منطقي lval)
{
  درخت ret = عبارت;
  تعداد درخت_کد_2 کد = درخت_کد (عبارت);
  تعداد درخت_کد_class نوع = درخت_کد_CLASS (کد);
  location_t loc = عبارت_LOCATION (عبارت);
  درخت op0, op1, op2, op3;
  درخت orig_op0, orig_op1, orig_op2;
  منطقي op0_const = درست, op1_const = درست, op2_const = درست;
  منطقي op0_const_self = درست, op1_const_self = درست, op2_const_self = درست;
  منطقي nowarning = warning_suppressed_p (عبارت, OPT_Woverflow);
  منطقي استفادهنشده_p;
  منطقي op0_lval = خطأ;
  منبع_range old_range;

  /* Constants, declarations, statements, errors, and anything else not
     counted as an expression cannot usefully be folded further at this
     point.  */
  إذا (!IS_عبارت_کد_CLASS (نوع) || نوع == tcc_statement)
    {
      /* Except for variables which we can optimize to its initializer.  */
      إذا (VAR_P (عبارت) && !lval && (optimize || درون_init))
	{
	  إذا (درون_init)
	    ret = decl_constant_مقدار_1 (عبارت, درست);
	  وإلا
	    {
	      ret = decl_constant_مقدار (عبارت);
	      إذا (ret != عبارت
		  && (TYPE_نما (درخت_TYPE (ret)) == BLKmode
		      || درخت_کد (درخت_TYPE (ret)) == ARRAY_TYPE))
		أرجع عبارت;
	    }
	  /* Avoid unwanted tree sharing between the initializer and current
	     function's body where the tree can be modified e.g. by the
	     gimplifier.  */
	  إذا (ret != عبارت && درخت_STATIC (عبارت))
	    ret = unshare_عبارت (ret);
	  أرجع ret;
	}
      أرجع عبارت;
    }

  إذا (IS_عبارت_کد_CLASS (نوع))
    old_range = عبارت_LOCATION_RANGE (عبارت);

  /* Operands of variable-length expressions (function calls) have
     already been folded, as have __builtin_* function calls, and such
     expressions cannot occur in constant expressions.  */
  إذا (نوع == tcc_vl_exp)
    {
      *maybe_const_operands = خطأ;
      ret = fold (عبارت);
      اذهب بیرون;
    }

  إذا (کد == C_MAYBE_CONST_عبارت)
    {
      درخت pre = C_MAYBE_CONST_عبارت_PRE (عبارت);
      درخت inner = C_MAYBE_CONST_عبارت_عبارت (عبارت);
      إذا (C_MAYBE_CONST_عبارت_NON_CONST (عبارت))
	*maybe_const_operands = خطأ;
      إذا (C_MAYBE_CONST_عبارت_INT_OPERANDS (عبارت))
	{
	  *maybe_const_itself = خطأ;
	  inner = c_fully_fold_داخلی (inner, درون_init, maybe_const_operands,
					 maybe_const_itself, درست, lval);
	}
      إذا (pre && !درون_init)
	ret = build2 (COMPOUND_عبارت, درخت_TYPE (عبارت), pre, inner);
      وإلا
	ret = inner;
      اذهب بیرون;
    }

  /* Assignment, increment, decrement, function call and comma
     operators, and statement expressions, cannot occur in constant
     expressions if evaluated / outside of sizeof.  (Function calls
     were handled above, though VA_ARG_EXPR is treated like a function
     call here, and statement expressions are handled through
     C_MAYBE_CONST_EXPR to avoid folding inside them.)  */
  بدل (کد)
    {
    حالة MODIFY_عبارت:
    حالة PREDECREMENT_عبارت:
    حالة PREINCREMENT_عبارت:
    حالة POSTDECREMENT_عبارت:
    حالة POSTINCREMENT_عبارت:
    حالة COMPOUND_عبارت:
      *maybe_const_operands = خطأ;
      اكسر;

    حالة VA_ARG_عبارت:
    حالة هدف_عبارت:
    حالة BIND_عبارت:
    حالة OBJ_TYPE_REF:
      *maybe_const_operands = خطأ;
      ret = fold (عبارت);
      اذهب بیرون;

    افتراضي:
      اكسر;
    }

  /* Fold individual tree codes as appropriate.  */
  بدل (کد)
    {
    حالة COMPOUND_LITERAL_عبارت:
      /* Any non-constancy will have been marked in a containing
	 C_MAYBE_CONST_EXPR; there is no more folding to do here.  */
      اذهب بیرون;

    حالة COMPONENT_REF:
      orig_op0 = op0 = درخت_عملوند (عبارت, 0);
      op1 = درخت_عملوند (عبارت, 1);
      op2 = درخت_عملوند (عبارت, 2);
      op0 = c_fully_fold_داخلی (op0, درون_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, lval);
      STRIP_TYPE_NOPS (op0);
      إذا (op0 != orig_op0)
	ret = build3 (COMPONENT_REF, درخت_TYPE (عبارت), op0, op1, op2);
      إذا (ret != عبارت)
	{
	  درخت_READONLY (ret) = درخت_READONLY (عبارت);
	  درخت_THIS_VOLATILE (ret) = درخت_THIS_VOLATILE (عبارت);
	}
      إذا (!lval)
	ret = fold (ret);
      اذهب بیرون;

    حالة ARRAY_REF:
      orig_op0 = op0 = درخت_عملوند (عبارت, 0);
      orig_op1 = op1 = درخت_عملوند (عبارت, 1);
      op2 = درخت_عملوند (عبارت, 2);
      op3 = درخت_عملوند (عبارت, 3);
      op0 = c_fully_fold_داخلی (op0, درون_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, lval);
      STRIP_TYPE_NOPS (op0);
      op1 = c_fully_fold_داخلی (op1, درون_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, خطأ);
      STRIP_TYPE_NOPS (op1);
      /* Fold "foo"[2] in initializers.  */
      إذا (!lval && درون_init)
	{
	  ret = c_fold_array_ref (درخت_TYPE (عبارت), op0, op1);
	  إذا (ret)
	    اذهب بیرون;
	  ret = عبارت;
	}
      إذا (op0 != orig_op0 || op1 != orig_op1)
	ret = build4 (ARRAY_REF, درخت_TYPE (عبارت), op0, op1, op2, op3);
      إذا (ret != عبارت)
	{
	  درخت_READONLY (ret) = درخت_READONLY (عبارت);
	  درخت_SIDE_EFFECTS (ret) = درخت_SIDE_EFFECTS (عبارت);
	  درخت_THIS_VOLATILE (ret) = درخت_THIS_VOLATILE (عبارت);
	}
      إذا (!lval)
	ret = fold (ret);
      اذهب بیرون;

    حالة MODIFY_عبارت:
    حالة PREDECREMENT_عبارت:
    حالة PREINCREMENT_عبارت:
    حالة POSTDECREMENT_عبارت:
    حالة POSTINCREMENT_عبارت:
      op0_lval = درست;
      /* FALLTHRU */
    حالة COMPOUND_عبارت:
    حالة PLUS_عبارت:
    حالة MINUS_عبارت:
    حالة MULT_عبارت:
    حالة اشاره_گر_PLUS_عبارت:
    حالة اشاره_گر_DIFF_عبارت:
    حالة TRUNC_DIV_عبارت:
    حالة CEIL_DIV_عبارت:
    حالة FLOOR_DIV_عبارت:
    حالة TRUNC_MOD_عبارت:
    حالة RDIV_عبارت:
    حالة EXACT_DIV_عبارت:
    حالة LSHIFT_عبارت:
    حالة RSHIFT_عبارت:
    حالة LROTATE_عبارت:
    حالة RROTATE_عبارت:
    حالة بیت_IOR_عبارت:
    حالة بیت_XOR_عبارت:
    حالة بیت_AND_عبارت:
    حالة LT_عبارت:
    حالة LE_عبارت:
    حالة GT_عبارت:
    حالة GE_عبارت:
    حالة EQ_عبارت:
    حالة NE_عبارت:
    حالة COMPLEX_عبارت:
    حالة TRUTH_AND_عبارت:
    حالة TRUTH_OR_عبارت:
    حالة TRUTH_XOR_عبارت:
    حالة UNORDERED_عبارت:
    حالة ORDERED_عبارت:
    حالة UNLT_عبارت:
    حالة UNLE_عبارت:
    حالة UNGT_عبارت:
    حالة UNGE_عبارت:
    حالة UNEQ_عبارت:
    حالة MEM_REF:
      /* Binary operations evaluating both arguments (increment and
	 decrement are binary internally in GCC).  */
      orig_op0 = op0 = درخت_عملوند (عبارت, 0);
      orig_op1 = op1 = درخت_عملوند (عبارت, 1);
      op0 = c_fully_fold_داخلی (op0, درون_init, maybe_const_operands,
				   maybe_const_itself, for_int_const,
				   op0_lval);
      STRIP_TYPE_NOPS (op0);
      /* The RHS of a MODIFY_EXPR was fully folded when building that
	 expression for the sake of conversion warnings.  */
      إذا (کد != MODIFY_عبارت)
	op1 = c_fully_fold_داخلی (op1, درون_init, maybe_const_operands,
				     maybe_const_itself, for_int_const, خطأ);
      STRIP_TYPE_NOPS (op1);

      إذا (for_int_const && (درخت_کد (op0) != INTEGER_CST
			    || درخت_کد (op1) != INTEGER_CST))
	اذهب بیرون;

      إذا (درخت_کد_CLASS (کد) == tcc_comparison
	  && درخت_کد (درخت_TYPE (op0)) == NULLPTR_TYPE
	  && درخت_کد (درخت_TYPE (op1)) == NULLPTR_TYPE)
	{
	  بدل (کد)
	    {
	    حالة EQ_عبارت:
	      ret = constant_boolean_گره (درست, درخت_TYPE (عبارت));
	      اكسر;
	    حالة NE_عبارت:
	      ret = constant_boolean_گره (خطأ, درخت_TYPE (عبارت));
	      اكسر;
	    افتراضي:
	      gcc_unreachable ();
	    }
	  ret = omit_two_operands_loc (loc, درخت_TYPE (عبارت), ret,
				       op0, op1);
	}
      وإلا إذا (op0 != orig_op0 || op1 != orig_op1 || درون_init)
	ret = درون_init
	  ? fold_build2_initializer_loc (loc, کد, درخت_TYPE (عبارت), op0, op1)
	  : fold_build2_loc (loc, کد, درخت_TYPE (عبارت), op0, op1);
      وإلا
	ret = fold (عبارت);
      إذا (درخت_سرریز_P (ret)
	  && !درخت_سرریز_P (op0)
	  && !(دودویی_CLASS_P (op0) && درخت_سرریز_P (درخت_عملوند (op0, 1)))
	  && !درخت_سرریز_P (op1))
	سرریز_warning (عبارت_LOC_OR_LOC (عبارت, درون_داد_location), ret, عبارت);
      إذا (کد == LSHIFT_عبارت
	  && درخت_کد (orig_op0) != INTEGER_CST
	  && (درخت_کد (درخت_TYPE (orig_op0)) == INTEGER_TYPE
	      || درخت_کد (درخت_TYPE (orig_op0)) == BITINT_TYPE)
	  && درخت_کد (op0) == INTEGER_CST
	  && c_inhibit_evaluation_warnings == 0
	  && !TYPE_سرریز_WRAPS (درخت_TYPE (orig_op0))
	  && درخت_int_cst_sgn (op0) < 0)
	warning_at (loc, OPT_Wshift_negative_مقدار,
		    "left shift of negative value");
      إذا ((کد == LSHIFT_عبارت
	   || کد == RSHIFT_عبارت
	   || کد == LROTATE_عبارت
	   || کد == RROTATE_عبارت)
	  && درخت_کد (orig_op1) != INTEGER_CST
	  && درخت_کد (op1) == INTEGER_CST
	  && درخت_کد (درخت_TYPE (orig_op1)) == INTEGER_TYPE
	  && c_inhibit_evaluation_warnings == 0)
	{
	  إذا (درخت_int_cst_sgn (op1) < 0)
	    warning_at (loc, OPT_Wshift_شمار_negative,
			(کد == LSHIFT_عبارت
			 ? G_("left shift count is negative")
			 : G_("right shift count is negative")));
	  وإلا إذا ((درخت_کد (درخت_TYPE (orig_op0)) == INTEGER_TYPE
		    || درخت_کد (درخت_TYPE (orig_op0)) == BITINT_TYPE
		    || درخت_کد (درخت_TYPE (orig_op0)) == FIXED_نقطه_TYPE)
		   && compare_درخت_int (op1,
					TYPE_PRECISION (درخت_TYPE (orig_op0)))
		      >= 0
		   && !warning_suppressed_p (عبارت, OPT_Wshift_شمار_سرریز))
	    warning_at (loc, OPT_Wshift_شمار_سرریز,
			(کد == LSHIFT_عبارت
			 ? G_("left shift count >= width of type")
			 : G_("right shift count >= width of type")));
	  وإلا إذا (درخت_کد (درخت_TYPE (orig_op0)) == وکتور_TYPE
		   && compare_درخت_int (op1,
					TYPE_PRECISION (درخت_TYPE (درخت_TYPE (orig_op0))))
		      >= 0)
	    warning_at (loc, OPT_Wshift_شمار_سرریز,
			کد == LSHIFT_عبارت
			? G_("left shift count >= width of vector element")
			: G_("right shift count >= width of vector element"));
	}
      إذا (کد == LSHIFT_عبارت
	  /* If either OP0 has been folded to INTEGER_CST...  */
	  && ((درخت_کد (orig_op0) != INTEGER_CST
	       && (درخت_کد (درخت_TYPE (orig_op0)) == INTEGER_TYPE
		   || درخت_کد (درخت_TYPE (orig_op0)) == BITINT_TYPE)
	       && درخت_کد (op0) == INTEGER_CST)
	      /* ...or if OP1 has been folded to INTEGER_CST...  */
	      || (درخت_کد (orig_op1) != INTEGER_CST
		  && (درخت_کد (درخت_TYPE (orig_op1)) == INTEGER_TYPE
		      || درخت_کد (درخت_TYPE (orig_op1)) == BITINT_TYPE)
		  && درخت_کد (op1) == INTEGER_CST))
	  && c_inhibit_evaluation_warnings == 0)
	/* ...then maybe we can detect an overflow.  */
	maybe_warn_لغزش_سرریز (loc, op0, op1);
      إذا ((کد == TRUNC_DIV_عبارت
	   || کد == CEIL_DIV_عبارت
	   || کد == FLOOR_DIV_عبارت
	   || کد == EXACT_DIV_عبارت
	   || کد == TRUNC_MOD_عبارت)
	  && درخت_کد (orig_op1) != INTEGER_CST
	  && درخت_کد (op1) == INTEGER_CST
	  && (درخت_کد (درخت_TYPE (orig_op0)) == INTEGER_TYPE
	      || درخت_کد (درخت_TYPE (orig_op0)) == BITINT_TYPE
	      || درخت_کد (درخت_TYPE (orig_op0)) == FIXED_نقطه_TYPE)
	  && (درخت_کد (درخت_TYPE (orig_op1)) == INTEGER_TYPE
	      || درخت_کد (درخت_TYPE (orig_op1)) == BITINT_TYPE))
	warn_for_div_by_zero (loc, op1);
      إذا (کد == MEM_REF
	  && ret != عبارت
	  && درخت_کد (ret) == MEM_REF)
	{
	  درخت_READONLY (ret) = درخت_READONLY (عبارت);
	  درخت_SIDE_EFFECTS (ret) = درخت_SIDE_EFFECTS (عبارت);
	  درخت_THIS_VOLATILE (ret) = درخت_THIS_VOLATILE (عبارت);
	}
      اذهب بیرون;

    حالة ADDR_عبارت:
      op0_lval = درست;
      اذهب unary;
    حالة REALPART_عبارت:
    حالة IMAGPART_عبارت:
    حالة VIEW_CONVERT_عبارت:
      op0_lval = lval;
      /* FALLTHRU */
    حالة غیرمستقیم_REF:
    حالة FIX_TRUNC_عبارت:
    حالة FLOAT_عبارت:
    CASE_CONVERT:
    حالة ADDR_SPACE_CONVERT_عبارت:
    حالة NON_LVALUE_عبارت:
    حالة NEGATE_عبارت:
    حالة بیت_NOT_عبارت:
    حالة TRUTH_NOT_عبارت:
    حالة CONJ_عبارت:
    حالة PAREN_عبارت:
    unary:
      /* Unary operations.  */
      orig_op0 = op0 = درخت_عملوند (عبارت, 0);
      op0 = c_fully_fold_داخلی (op0, درون_init, maybe_const_operands,
				   maybe_const_itself, for_int_const,
				   op0_lval);
      STRIP_TYPE_NOPS (op0);

      إذا (for_int_const && درخت_کد (op0) != INTEGER_CST)
	اذهب بیرون;

      /* ??? Cope with user tricks that amount to offsetof.  The middle-end is
	 not prepared to deal with them if they occur in initializers.  */
      إذا (op0 != orig_op0
	  && کد == ADDR_عبارت
	  && (op1 = get_پایه_آدرس (op0)) != NULL_درخت
	  && غیرمستقیم_REF_P (op1)
	  && درخت_CONSTANT (درخت_عملوند (op1, 0)))
	ret = fold_offsetof (op0, درخت_TYPE (عبارت));
      وإلا إذا (op0 != orig_op0 || درون_init)
	ret = درون_init
	  ? fold_build1_initializer_loc (loc, کد, درخت_TYPE (عبارت), op0)
	  : fold_build1_loc (loc, کد, درخت_TYPE (عبارت), op0);
      وإلا
	ret = fold (عبارت);
      إذا (کد == غیرمستقیم_REF
	  && ret != عبارت
	  && غیرمستقیم_REF_P (ret))
	{
	  درخت_READONLY (ret) = درخت_READONLY (عبارت);
	  درخت_SIDE_EFFECTS (ret) = درخت_SIDE_EFFECTS (عبارت);
	  درخت_THIS_VOLATILE (ret) = درخت_THIS_VOLATILE (عبارت);
	}
      بدل (کد)
	{
	حالة FIX_TRUNC_عبارت:
	حالة FLOAT_عبارت:
	CASE_CONVERT:
	  /* Don't warn about explicit conversions.  We will already
	     have warned about suspect implicit conversions.  */
	  اكسر;

	افتراضي:
	  إذا (درخت_سرریز_P (ret) && !درخت_سرریز_P (op0))
	    سرریز_warning (عبارت_LOCATION (عبارت), ret, op0);
	  اكسر;
	}
      اذهب بیرون;

    حالة TRUTH_ANDIF_عبارت:
    حالة TRUTH_ORIF_عبارت:
      /* Binary operations not necessarily evaluating both
	 arguments.  */
      orig_op0 = op0 = درخت_عملوند (عبارت, 0);
      orig_op1 = op1 = درخت_عملوند (عبارت, 1);
      op0 = c_fully_fold_داخلی (op0, درون_init, &op0_const, &op0_const_self,
				   for_int_const, خطأ);
      STRIP_TYPE_NOPS (op0);

      استفادهنشده_p = (op0 == (کد == TRUTH_ANDIF_عبارت
			  ? truthvalue_false_گره
			  : truthvalue_true_گره));
      c_disable_warnings (استفادهنشده_p);
      op1 = c_fully_fold_داخلی (op1, درون_init, &op1_const, &op1_const_self,
				   for_int_const, خطأ);
      STRIP_TYPE_NOPS (op1);
      c_enable_warnings (استفادهنشده_p);

      إذا (for_int_const
	  && (درخت_کد (op0) != INTEGER_CST
	      /* Require OP1 be an INTEGER_CST only if it's evaluated.  */
	      || (!استفادهنشده_p && درخت_کد (op1) != INTEGER_CST)))
	اذهب بیرون;

      إذا (op0 != orig_op0 || op1 != orig_op1 || درون_init)
	ret = درون_init
	  ? fold_build2_initializer_loc (loc, کد, درخت_TYPE (عبارت), op0, op1)
	  : fold_build2_loc (loc, کد, درخت_TYPE (عبارت), op0, op1);
      وإلا
	ret = fold (عبارت);
      *maybe_const_operands &= op0_const;
      *maybe_const_itself &= op0_const_self;
      إذا (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && (کد == TRUTH_ANDIF_عبارت
		? op0 == truthvalue_false_گره
		: op0 == truthvalue_true_گره)))
	*maybe_const_operands &= op1_const;
      إذا (!(op0_const
	    && op0_const_self
	    && (کد == TRUTH_ANDIF_عبارت
		? op0 == truthvalue_false_گره
		: op0 == truthvalue_true_گره)))
	*maybe_const_itself &= op1_const_self;
      اذهب بیرون;

    حالة COND_عبارت:
      orig_op0 = op0 = درخت_عملوند (عبارت, 0);
      orig_op1 = op1 = درخت_عملوند (عبارت, 1);
      orig_op2 = op2 = درخت_عملوند (عبارت, 2);
      op0 = c_fully_fold_داخلی (op0, درون_init, &op0_const, &op0_const_self,
				   for_int_const, خطأ);

      STRIP_TYPE_NOPS (op0);
      c_disable_warnings (op0 == truthvalue_false_گره);
      op1 = c_fully_fold_داخلی (op1, درون_init, &op1_const, &op1_const_self,
				   for_int_const, خطأ);
      STRIP_TYPE_NOPS (op1);
      c_enable_warnings (op0 == truthvalue_false_گره);

      c_disable_warnings (op0 == truthvalue_true_گره);
      op2 = c_fully_fold_داخلی (op2, درون_init, &op2_const, &op2_const_self,
				   for_int_const, خطأ);
      STRIP_TYPE_NOPS (op2);
      c_enable_warnings (op0 == truthvalue_true_گره);

      إذا (for_int_const
	  && (درخت_کد (op0) != INTEGER_CST
	      /* Only the evaluated operand must be an INTEGER_CST.  */
	      || (op0 == truthvalue_true_گره
		  ? درخت_کد (op1) != INTEGER_CST
		  : درخت_کد (op2) != INTEGER_CST)))
	اذهب بیرون;

      إذا (op0 != orig_op0 || op1 != orig_op1 || op2 != orig_op2)
	ret = fold_build3_loc (loc, کد, درخت_TYPE (عبارت), op0, op1, op2);
      وإلا
	ret = fold (عبارت);
      *maybe_const_operands &= op0_const;
      *maybe_const_itself &= op0_const_self;
      إذا (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && op0 == truthvalue_false_گره))
	*maybe_const_operands &= op1_const;
      إذا (!(op0_const
	    && op0_const_self
	    && op0 == truthvalue_false_گره))
	*maybe_const_itself &= op1_const_self;
      إذا (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && op0 == truthvalue_true_گره))
	*maybe_const_operands &= op2_const;
      إذا (!(op0_const
	    && op0_const_self
	    && op0 == truthvalue_true_گره))
	*maybe_const_itself &= op2_const_self;
      اذهب بیرون;

    حالة VEC_COND_عبارت:
      orig_op0 = op0 = درخت_عملوند (عبارت, 0);
      orig_op1 = op1 = درخت_عملوند (عبارت, 1);
      orig_op2 = op2 = درخت_عملوند (عبارت, 2);
      op0 = c_fully_fold_داخلی (op0, درون_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, خطأ);
      STRIP_TYPE_NOPS (op0);
      op1 = c_fully_fold_داخلی (op1, درون_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, خطأ);
      STRIP_TYPE_NOPS (op1);
      op2 = c_fully_fold_داخلی (op2, درون_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, خطأ);
      STRIP_TYPE_NOPS (op2);

      إذا (op0 != orig_op0 || op1 != orig_op1 || op2 != orig_op2)
	ret = fold_build3_loc (loc, کد, درخت_TYPE (عبارت), op0, op1, op2);
      وإلا
	ret = fold (عبارت);
      اذهب بیرون;

    حالة EXCESS_PRECISION_عبارت:
      /* Each case where an operand with excess precision may be
	 encountered must remove the EXCESS_PRECISION_EXPR around
	 inner operands and possibly put one around the whole
	 expression or possibly convert to the semantic type (which
	 c_fully_fold does); we cannot tell at this stage which is
	 appropriate in any particular case.  */
      gcc_unreachable ();

    حالة SAVE_عبارت:
      /* Make sure to fold the contents of a SAVE_EXPR exactly once.  */
      op0 = درخت_عملوند (عبارت, 0);
      إذا (!SAVE_عبارت_FOLDED_P (عبارت))
	{
	  op0 = c_fully_fold_داخلی (op0, درون_init, maybe_const_operands,
				       maybe_const_itself, for_int_const,
				       خطأ);
	  درخت_عملوند (عبارت, 0) = op0;
	  SAVE_عبارت_FOLDED_P (عبارت) = درست;
	}
      /* Return the SAVE_EXPR operand if it is invariant.  */
      إذا (درخت_invariant_p (op0))
	ret = op0;
      اذهب بیرون;

    افتراضي:
      /* Various codes may appear through folding built-in functions
	 and their arguments.  */
      اذهب بیرون;
    }

 بیرون:
  /* Some folding may introduce NON_LVALUE_EXPRs; all lvalue checks
     have been done by this point, so remove them again.  */
  nowarning |= warning_suppressed_p (ret, OPT_Woverflow);
  STRIP_TYPE_NOPS (ret);
  إذا (nowarning && !warning_suppressed_p (ret, OPT_Woverflow))
    {
      إذا (!CAN_HAVE_LOCATION_P (ret))
	ret = build1 (NOP_عبارت, درخت_TYPE (ret), ret);
      suppress_warning (ret, OPT_Woverflow);
    }
  إذا (ret != عبارت)
    {
      protected_مجموعه_عبارت_location (ret, loc);
      إذا (IS_عبارت_کد_CLASS (نوع))
	مجموعه_منبع_range (ret, old_range.m_شروع, old_range.m_پایان);
    }
  أرجع ret;
}

/* Fold X for consideration by one of the warning functions when checking
   whether an expression has a constant value.  */

درخت
fold_for_warn (درخت x)
{
  /* The C front-end has already folded X appropriately.  */
  أرجع x;
}
