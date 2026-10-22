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

ساكن درخت c_fully_fold_اندرونی (درخت اظہاریہ, منطقي, منطقي *, منطقي *, منطقي,
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
c_fold_array_ref (درخت type, درخت ary, درخت اشاریہ)
{
  إذا (درخت_کوڈ (ary) != STRING_CST
      || درخت_کوڈ (اشاریہ) != INTEGER_CST
      || درخت_حد_توں_ودھ (اشاریہ)
      || درخت_کوڈ (درخت_TYPE (ary)) != ARRAY_TYPE
      || !درخت_سماندا_uhwi_p (اشاریہ))
    أرجع NULL_درخت;

  درخت elem_type = درخت_TYPE (درخت_TYPE (ary));
  بنانشانی elem_nchars = (TYPE_PRECISION (elem_type)
			  / TYPE_PRECISION (char_type_گرہ));
  بنانشانی len = (بنانشانی) درخت_STRING_لمائی (ary) / elem_nchars;
  درخت nelts_minus_one = array_type_nelts_minus_one (درخت_TYPE (ary));
  منطقي dummy1 = سچ, dummy2 = سچ;
  nelts_minus_one = c_fully_fold_اندرونی (nelts_minus_one, سچ, &dummy1,
					   &dummy2, خطأ, خطأ);
  بنانشانی HOST_WIDE_INT i = درخت_منزل_uhwi (اشاریہ);
  إذا (!درخت_int_cst_le (اشاریہ, nelts_minus_one)
      || i >= len
      || i + elem_nchars > len)
    أرجع NULL_درخت;

  إذا (elem_nchars == 1)
    أرجع build_int_cst (type, درخت_STRING_اشارہ_گر (ary)[i]);

  ثابت بنانشانی حرف *ptr
    = ((ثابت بنانشانی حرف *)درخت_STRING_اشارہ_گر (ary) + i * elem_nchars);
  أرجع native_interpret_اظہاریہ (type, ptr, elem_nchars);
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
c_fully_fold (درخت اظہاریہ, منطقي وچ_init, منطقي *maybe_const, منطقي lval)
{
  درخت ret;
  درخت eptype = NULL_درخت;
  منطقي dummy = سچ;
  منطقي maybe_const_itself = سچ;
  location_t loc = اظہاریہ_LOCATION (اظہاریہ);

  إذا (!maybe_const)
    maybe_const = &dummy;
  إذا (درخت_کوڈ (اظہاریہ) == EXCESS_PRECISION_اظہاریہ)
    {
      eptype = درخت_TYPE (اظہاریہ);
      اظہاریہ = درخت_عملیہ (اظہاریہ, 0);
    }
  ret = c_fully_fold_اندرونی (اظہاریہ, وچ_init, maybe_const,
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
c_fully_fold_اندرونی (درخت اظہاریہ, منطقي وچ_init, منطقي *maybe_const_operands,
		       منطقي *maybe_const_itself, منطقي for_int_const, منطقي lval)
{
  درخت ret = اظہاریہ;
  تعداد درخت_کوڈ_2 کوڈ = درخت_کوڈ (اظہاریہ);
  تعداد درخت_کوڈ_class قسم = درخت_کوڈ_CLASS (کوڈ);
  location_t loc = اظہاریہ_LOCATION (اظہاریہ);
  درخت op0, op1, op2, op3;
  درخت orig_op0, orig_op1, orig_op2;
  منطقي op0_const = سچ, op1_const = سچ, op2_const = سچ;
  منطقي op0_const_self = سچ, op1_const_self = سچ, op2_const_self = سچ;
  منطقي nowarning = warning_suppressed_p (اظہاریہ, OPT_Woverflow);
  منطقي بن_ورتیا_p;
  منطقي op0_lval = خطأ;
  سروت_range old_range;

  /* Constants, declarations, statements, errors, and anything else not
     counted as an expression cannot usefully be folded further at this
     point.  */
  إذا (!IS_اظہاریہ_کوڈ_CLASS (قسم) || قسم == tcc_statement)
    {
      /* Except for variables which we can optimize to its initializer.  */
      إذا (VAR_P (اظہاریہ) && !lval && (optimize || وچ_init))
	{
	  إذا (وچ_init)
	    ret = decl_constant_قدر_1 (اظہاریہ, سچ);
	  وإلا
	    {
	      ret = decl_constant_قدر (اظہاریہ);
	      إذا (ret != اظہاریہ
		  && (TYPE_منوال (درخت_TYPE (ret)) == BLKmode
		      || درخت_کوڈ (درخت_TYPE (ret)) == ARRAY_TYPE))
		أرجع اظہاریہ;
	    }
	  /* Avoid unwanted tree sharing between the initializer and current
	     function's body where the tree can be modified e.g. by the
	     gimplifier.  */
	  إذا (ret != اظہاریہ && درخت_STATIC (اظہاریہ))
	    ret = unshare_اظہاریہ (ret);
	  أرجع ret;
	}
      أرجع اظہاریہ;
    }

  إذا (IS_اظہاریہ_کوڈ_CLASS (قسم))
    old_range = اظہاریہ_LOCATION_RANGE (اظہاریہ);

  /* Operands of variable-length expressions (function calls) have
     already been folded, as have __builtin_* function calls, and such
     expressions cannot occur in constant expressions.  */
  إذا (قسم == tcc_vl_exp)
    {
      *maybe_const_operands = خطأ;
      ret = fold (اظہاریہ);
      اذهب باہرلا;
    }

  إذا (کوڈ == C_MAYBE_CONST_اظہاریہ)
    {
      درخت pre = C_MAYBE_CONST_اظہاریہ_PRE (اظہاریہ);
      درخت inner = C_MAYBE_CONST_اظہاریہ_اظہاریہ (اظہاریہ);
      إذا (C_MAYBE_CONST_اظہاریہ_NON_CONST (اظہاریہ))
	*maybe_const_operands = خطأ;
      إذا (C_MAYBE_CONST_اظہاریہ_INT_OPERANDS (اظہاریہ))
	{
	  *maybe_const_itself = خطأ;
	  inner = c_fully_fold_اندرونی (inner, وچ_init, maybe_const_operands,
					 maybe_const_itself, سچ, lval);
	}
      إذا (pre && !وچ_init)
	ret = build2 (COMPOUND_اظہاریہ, درخت_TYPE (اظہاریہ), pre, inner);
      وإلا
	ret = inner;
      اذهب باہرلا;
    }

  /* Assignment, increment, decrement, function call and comma
     operators, and statement expressions, cannot occur in constant
     expressions if evaluated / outside of sizeof.  (Function calls
     were handled above, though VA_ARG_EXPR is treated like a function
     call here, and statement expressions are handled through
     C_MAYBE_CONST_EXPR to avoid folding inside them.)  */
  بدل (کوڈ)
    {
    حالة MODIFY_اظہاریہ:
    حالة PREDECREMENT_اظہاریہ:
    حالة PREINCREMENT_اظہاریہ:
    حالة POSTDECREMENT_اظہاریہ:
    حالة POSTINCREMENT_اظہاریہ:
    حالة COMPOUND_اظہاریہ:
      *maybe_const_operands = خطأ;
      اكسر;

    حالة VA_ARG_اظہاریہ:
    حالة نشانہ_اظہاریہ:
    حالة BIND_اظہاریہ:
    حالة OBJ_TYPE_REF:
      *maybe_const_operands = خطأ;
      ret = fold (اظہاریہ);
      اذهب باہرلا;

    افتراضي:
      اكسر;
    }

  /* Fold individual tree codes as appropriate.  */
  بدل (کوڈ)
    {
    حالة COMPOUND_LITERAL_اظہاریہ:
      /* Any non-constancy will have been marked in a containing
	 C_MAYBE_CONST_EXPR; there is no more folding to do here.  */
      اذهب باہرلا;

    حالة COMPONENT_REF:
      orig_op0 = op0 = درخت_عملیہ (اظہاریہ, 0);
      op1 = درخت_عملیہ (اظہاریہ, 1);
      op2 = درخت_عملیہ (اظہاریہ, 2);
      op0 = c_fully_fold_اندرونی (op0, وچ_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, lval);
      STRIP_TYPE_NOPS (op0);
      إذا (op0 != orig_op0)
	ret = build3 (COMPONENT_REF, درخت_TYPE (اظہاریہ), op0, op1, op2);
      إذا (ret != اظہاریہ)
	{
	  درخت_READONLY (ret) = درخت_READONLY (اظہاریہ);
	  درخت_THIS_VOLATILE (ret) = درخت_THIS_VOLATILE (اظہاریہ);
	}
      إذا (!lval)
	ret = fold (ret);
      اذهب باہرلا;

    حالة ARRAY_REF:
      orig_op0 = op0 = درخت_عملیہ (اظہاریہ, 0);
      orig_op1 = op1 = درخت_عملیہ (اظہاریہ, 1);
      op2 = درخت_عملیہ (اظہاریہ, 2);
      op3 = درخت_عملیہ (اظہاریہ, 3);
      op0 = c_fully_fold_اندرونی (op0, وچ_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, lval);
      STRIP_TYPE_NOPS (op0);
      op1 = c_fully_fold_اندرونی (op1, وچ_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, خطأ);
      STRIP_TYPE_NOPS (op1);
      /* Fold "foo"[2] in initializers.  */
      إذا (!lval && وچ_init)
	{
	  ret = c_fold_array_ref (درخت_TYPE (اظہاریہ), op0, op1);
	  إذا (ret)
	    اذهب باہرلا;
	  ret = اظہاریہ;
	}
      إذا (op0 != orig_op0 || op1 != orig_op1)
	ret = build4 (ARRAY_REF, درخت_TYPE (اظہاریہ), op0, op1, op2, op3);
      إذا (ret != اظہاریہ)
	{
	  درخت_READONLY (ret) = درخت_READONLY (اظہاریہ);
	  درخت_SIDE_EFFECTS (ret) = درخت_SIDE_EFFECTS (اظہاریہ);
	  درخت_THIS_VOLATILE (ret) = درخت_THIS_VOLATILE (اظہاریہ);
	}
      إذا (!lval)
	ret = fold (ret);
      اذهب باہرلا;

    حالة MODIFY_اظہاریہ:
    حالة PREDECREMENT_اظہاریہ:
    حالة PREINCREMENT_اظہاریہ:
    حالة POSTDECREMENT_اظہاریہ:
    حالة POSTINCREMENT_اظہاریہ:
      op0_lval = سچ;
      /* FALLTHRU */
    حالة COMPOUND_اظہاریہ:
    حالة PLUS_اظہاریہ:
    حالة MINUS_اظہاریہ:
    حالة MULT_اظہاریہ:
    حالة اشارہ_گر_PLUS_اظہاریہ:
    حالة اشارہ_گر_DIFF_اظہاریہ:
    حالة TRUNC_DIV_اظہاریہ:
    حالة CEIL_DIV_اظہاریہ:
    حالة FLOOR_DIV_اظہاریہ:
    حالة TRUNC_MOD_اظہاریہ:
    حالة RDIV_اظہاریہ:
    حالة EXACT_DIV_اظہاریہ:
    حالة LSHIFT_اظہاریہ:
    حالة RSHIFT_اظہاریہ:
    حالة LROTATE_اظہاریہ:
    حالة RROTATE_اظہاریہ:
    حالة ثنائی_ہندسہ_IOR_اظہاریہ:
    حالة ثنائی_ہندسہ_XOR_اظہاریہ:
    حالة ثنائی_ہندسہ_AND_اظہاریہ:
    حالة LT_اظہاریہ:
    حالة LE_اظہاریہ:
    حالة GT_اظہاریہ:
    حالة GE_اظہاریہ:
    حالة EQ_اظہاریہ:
    حالة NE_اظہاریہ:
    حالة COMPLEX_اظہاریہ:
    حالة TRUTH_AND_اظہاریہ:
    حالة TRUTH_OR_اظہاریہ:
    حالة TRUTH_XOR_اظہاریہ:
    حالة UNORDERED_اظہاریہ:
    حالة ORDERED_اظہاریہ:
    حالة UNLT_اظہاریہ:
    حالة UNLE_اظہاریہ:
    حالة UNGT_اظہاریہ:
    حالة UNGE_اظہاریہ:
    حالة UNEQ_اظہاریہ:
    حالة MEM_REF:
      /* Binary operations evaluating both arguments (increment and
	 decrement are binary internally in GCC).  */
      orig_op0 = op0 = درخت_عملیہ (اظہاریہ, 0);
      orig_op1 = op1 = درخت_عملیہ (اظہاریہ, 1);
      op0 = c_fully_fold_اندرونی (op0, وچ_init, maybe_const_operands,
				   maybe_const_itself, for_int_const,
				   op0_lval);
      STRIP_TYPE_NOPS (op0);
      /* The RHS of a MODIFY_EXPR was fully folded when building that
	 expression for the sake of conversion warnings.  */
      إذا (کوڈ != MODIFY_اظہاریہ)
	op1 = c_fully_fold_اندرونی (op1, وچ_init, maybe_const_operands,
				     maybe_const_itself, for_int_const, خطأ);
      STRIP_TYPE_NOPS (op1);

      إذا (for_int_const && (درخت_کوڈ (op0) != INTEGER_CST
			    || درخت_کوڈ (op1) != INTEGER_CST))
	اذهب باہرلا;

      إذا (درخت_کوڈ_CLASS (کوڈ) == tcc_comparison
	  && درخت_کوڈ (درخت_TYPE (op0)) == NULLPTR_TYPE
	  && درخت_کوڈ (درخت_TYPE (op1)) == NULLPTR_TYPE)
	{
	  بدل (کوڈ)
	    {
	    حالة EQ_اظہاریہ:
	      ret = constant_boolean_گرہ (سچ, درخت_TYPE (اظہاریہ));
	      اكسر;
	    حالة NE_اظہاریہ:
	      ret = constant_boolean_گرہ (خطأ, درخت_TYPE (اظہاریہ));
	      اكسر;
	    افتراضي:
	      gcc_unreachable ();
	    }
	  ret = omit_two_operands_loc (loc, درخت_TYPE (اظہاریہ), ret,
				       op0, op1);
	}
      وإلا إذا (op0 != orig_op0 || op1 != orig_op1 || وچ_init)
	ret = وچ_init
	  ? fold_build2_initializer_loc (loc, کوڈ, درخت_TYPE (اظہاریہ), op0, op1)
	  : fold_build2_loc (loc, کوڈ, درخت_TYPE (اظہاریہ), op0, op1);
      وإلا
	ret = fold (اظہاریہ);
      إذا (درخت_حد_توں_ودھ_P (ret)
	  && !درخت_حد_توں_ودھ_P (op0)
	  && !(ثنائی_CLASS_P (op0) && درخت_حد_توں_ودھ_P (درخت_عملیہ (op0, 1)))
	  && !درخت_حد_توں_ودھ_P (op1))
	حد_توں_ودھ_warning (اظہاریہ_LOC_OR_LOC (اظہاریہ, داخلہ_location), ret, اظہاریہ);
      إذا (کوڈ == LSHIFT_اظہاریہ
	  && درخت_کوڈ (orig_op0) != INTEGER_CST
	  && (درخت_کوڈ (درخت_TYPE (orig_op0)) == INTEGER_TYPE
	      || درخت_کوڈ (درخت_TYPE (orig_op0)) == BITINT_TYPE)
	  && درخت_کوڈ (op0) == INTEGER_CST
	  && c_inhibit_evaluation_warnings == 0
	  && !TYPE_حد_توں_ودھ_WRAPS (درخت_TYPE (orig_op0))
	  && درخت_int_cst_sgn (op0) < 0)
	warning_at (loc, OPT_Wshift_negative_قدر,
		    "left shift of negative value");
      إذا ((کوڈ == LSHIFT_اظہاریہ
	   || کوڈ == RSHIFT_اظہاریہ
	   || کوڈ == LROTATE_اظہاریہ
	   || کوڈ == RROTATE_اظہاریہ)
	  && درخت_کوڈ (orig_op1) != INTEGER_CST
	  && درخت_کوڈ (op1) == INTEGER_CST
	  && درخت_کوڈ (درخت_TYPE (orig_op1)) == INTEGER_TYPE
	  && c_inhibit_evaluation_warnings == 0)
	{
	  إذا (درخت_int_cst_sgn (op1) < 0)
	    warning_at (loc, OPT_Wshift_گنتی_negative,
			(کوڈ == LSHIFT_اظہاریہ
			 ? G_("left shift count is negative")
			 : G_("right shift count is negative")));
	  وإلا إذا ((درخت_کوڈ (درخت_TYPE (orig_op0)) == INTEGER_TYPE
		    || درخت_کوڈ (درخت_TYPE (orig_op0)) == BITINT_TYPE
		    || درخت_کوڈ (درخت_TYPE (orig_op0)) == FIXED_نقطہ_TYPE)
		   && compare_درخت_int (op1,
					TYPE_PRECISION (درخت_TYPE (orig_op0)))
		      >= 0
		   && !warning_suppressed_p (اظہاریہ, OPT_Wshift_گنتی_حد_توں_ودھ))
	    warning_at (loc, OPT_Wshift_گنتی_حد_توں_ودھ,
			(کوڈ == LSHIFT_اظہاریہ
			 ? G_("left shift count >= width of type")
			 : G_("right shift count >= width of type")));
	  وإلا إذا (درخت_کوڈ (درخت_TYPE (orig_op0)) == سمتیہ_TYPE
		   && compare_درخت_int (op1,
					TYPE_PRECISION (درخت_TYPE (درخت_TYPE (orig_op0))))
		      >= 0)
	    warning_at (loc, OPT_Wshift_گنتی_حد_توں_ودھ,
			کوڈ == LSHIFT_اظہاریہ
			? G_("left shift count >= width of vector element")
			: G_("right shift count >= width of vector element"));
	}
      إذا (کوڈ == LSHIFT_اظہاریہ
	  /* If either OP0 has been folded to INTEGER_CST...  */
	  && ((درخت_کوڈ (orig_op0) != INTEGER_CST
	       && (درخت_کوڈ (درخت_TYPE (orig_op0)) == INTEGER_TYPE
		   || درخت_کوڈ (درخت_TYPE (orig_op0)) == BITINT_TYPE)
	       && درخت_کوڈ (op0) == INTEGER_CST)
	      /* ...or if OP1 has been folded to INTEGER_CST...  */
	      || (درخت_کوڈ (orig_op1) != INTEGER_CST
		  && (درخت_کوڈ (درخت_TYPE (orig_op1)) == INTEGER_TYPE
		      || درخت_کوڈ (درخت_TYPE (orig_op1)) == BITINT_TYPE)
		  && درخت_کوڈ (op1) == INTEGER_CST))
	  && c_inhibit_evaluation_warnings == 0)
	/* ...then maybe we can detect an overflow.  */
	maybe_warn_کھسکاؤ_حد_توں_ودھ (loc, op0, op1);
      إذا ((کوڈ == TRUNC_DIV_اظہاریہ
	   || کوڈ == CEIL_DIV_اظہاریہ
	   || کوڈ == FLOOR_DIV_اظہاریہ
	   || کوڈ == EXACT_DIV_اظہاریہ
	   || کوڈ == TRUNC_MOD_اظہاریہ)
	  && درخت_کوڈ (orig_op1) != INTEGER_CST
	  && درخت_کوڈ (op1) == INTEGER_CST
	  && (درخت_کوڈ (درخت_TYPE (orig_op0)) == INTEGER_TYPE
	      || درخت_کوڈ (درخت_TYPE (orig_op0)) == BITINT_TYPE
	      || درخت_کوڈ (درخت_TYPE (orig_op0)) == FIXED_نقطہ_TYPE)
	  && (درخت_کوڈ (درخت_TYPE (orig_op1)) == INTEGER_TYPE
	      || درخت_کوڈ (درخت_TYPE (orig_op1)) == BITINT_TYPE))
	warn_for_div_by_zero (loc, op1);
      إذا (کوڈ == MEM_REF
	  && ret != اظہاریہ
	  && درخت_کوڈ (ret) == MEM_REF)
	{
	  درخت_READONLY (ret) = درخت_READONLY (اظہاریہ);
	  درخت_SIDE_EFFECTS (ret) = درخت_SIDE_EFFECTS (اظہاریہ);
	  درخت_THIS_VOLATILE (ret) = درخت_THIS_VOLATILE (اظہاریہ);
	}
      اذهب باہرلا;

    حالة ADDR_اظہاریہ:
      op0_lval = سچ;
      اذهب unary;
    حالة REALPART_اظہاریہ:
    حالة IMAGPART_اظہاریہ:
    حالة VIEW_CONVERT_اظہاریہ:
      op0_lval = lval;
      /* FALLTHRU */
    حالة اسدھا_REF:
    حالة FIX_TRUNC_اظہاریہ:
    حالة FLOAT_اظہاریہ:
    CASE_CONVERT:
    حالة ADDR_SPACE_CONVERT_اظہاریہ:
    حالة NON_LVALUE_اظہاریہ:
    حالة NEGATE_اظہاریہ:
    حالة ثنائی_ہندسہ_NOT_اظہاریہ:
    حالة TRUTH_NOT_اظہاریہ:
    حالة CONJ_اظہاریہ:
    حالة PAREN_اظہاریہ:
    unary:
      /* Unary operations.  */
      orig_op0 = op0 = درخت_عملیہ (اظہاریہ, 0);
      op0 = c_fully_fold_اندرونی (op0, وچ_init, maybe_const_operands,
				   maybe_const_itself, for_int_const,
				   op0_lval);
      STRIP_TYPE_NOPS (op0);

      إذا (for_int_const && درخت_کوڈ (op0) != INTEGER_CST)
	اذهب باہرلا;

      /* ??? Cope with user tricks that amount to offsetof.  The middle-end is
	 not prepared to deal with them if they occur in initializers.  */
      إذا (op0 != orig_op0
	  && کوڈ == ADDR_اظہاریہ
	  && (op1 = get_ادھار_پتہ (op0)) != NULL_درخت
	  && اسدھا_REF_P (op1)
	  && درخت_CONSTANT (درخت_عملیہ (op1, 0)))
	ret = fold_offsetof (op0, درخت_TYPE (اظہاریہ));
      وإلا إذا (op0 != orig_op0 || وچ_init)
	ret = وچ_init
	  ? fold_build1_initializer_loc (loc, کوڈ, درخت_TYPE (اظہاریہ), op0)
	  : fold_build1_loc (loc, کوڈ, درخت_TYPE (اظہاریہ), op0);
      وإلا
	ret = fold (اظہاریہ);
      إذا (کوڈ == اسدھا_REF
	  && ret != اظہاریہ
	  && اسدھا_REF_P (ret))
	{
	  درخت_READONLY (ret) = درخت_READONLY (اظہاریہ);
	  درخت_SIDE_EFFECTS (ret) = درخت_SIDE_EFFECTS (اظہاریہ);
	  درخت_THIS_VOLATILE (ret) = درخت_THIS_VOLATILE (اظہاریہ);
	}
      بدل (کوڈ)
	{
	حالة FIX_TRUNC_اظہاریہ:
	حالة FLOAT_اظہاریہ:
	CASE_CONVERT:
	  /* Don't warn about explicit conversions.  We will already
	     have warned about suspect implicit conversions.  */
	  اكسر;

	افتراضي:
	  إذا (درخت_حد_توں_ودھ_P (ret) && !درخت_حد_توں_ودھ_P (op0))
	    حد_توں_ودھ_warning (اظہاریہ_LOCATION (اظہاریہ), ret, op0);
	  اكسر;
	}
      اذهب باہرلا;

    حالة TRUTH_ANDIF_اظہاریہ:
    حالة TRUTH_ORIF_اظہاریہ:
      /* Binary operations not necessarily evaluating both
	 arguments.  */
      orig_op0 = op0 = درخت_عملیہ (اظہاریہ, 0);
      orig_op1 = op1 = درخت_عملیہ (اظہاریہ, 1);
      op0 = c_fully_fold_اندرونی (op0, وچ_init, &op0_const, &op0_const_self,
				   for_int_const, خطأ);
      STRIP_TYPE_NOPS (op0);

      بن_ورتیا_p = (op0 == (کوڈ == TRUTH_ANDIF_اظہاریہ
			  ? truthvalue_false_گرہ
			  : truthvalue_true_گرہ));
      c_disable_warnings (بن_ورتیا_p);
      op1 = c_fully_fold_اندرونی (op1, وچ_init, &op1_const, &op1_const_self,
				   for_int_const, خطأ);
      STRIP_TYPE_NOPS (op1);
      c_enable_warnings (بن_ورتیا_p);

      إذا (for_int_const
	  && (درخت_کوڈ (op0) != INTEGER_CST
	      /* Require OP1 be an INTEGER_CST only if it's evaluated.  */
	      || (!بن_ورتیا_p && درخت_کوڈ (op1) != INTEGER_CST)))
	اذهب باہرلا;

      إذا (op0 != orig_op0 || op1 != orig_op1 || وچ_init)
	ret = وچ_init
	  ? fold_build2_initializer_loc (loc, کوڈ, درخت_TYPE (اظہاریہ), op0, op1)
	  : fold_build2_loc (loc, کوڈ, درخت_TYPE (اظہاریہ), op0, op1);
      وإلا
	ret = fold (اظہاریہ);
      *maybe_const_operands &= op0_const;
      *maybe_const_itself &= op0_const_self;
      إذا (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && (کوڈ == TRUTH_ANDIF_اظہاریہ
		? op0 == truthvalue_false_گرہ
		: op0 == truthvalue_true_گرہ)))
	*maybe_const_operands &= op1_const;
      إذا (!(op0_const
	    && op0_const_self
	    && (کوڈ == TRUTH_ANDIF_اظہاریہ
		? op0 == truthvalue_false_گرہ
		: op0 == truthvalue_true_گرہ)))
	*maybe_const_itself &= op1_const_self;
      اذهب باہرلا;

    حالة COND_اظہاریہ:
      orig_op0 = op0 = درخت_عملیہ (اظہاریہ, 0);
      orig_op1 = op1 = درخت_عملیہ (اظہاریہ, 1);
      orig_op2 = op2 = درخت_عملیہ (اظہاریہ, 2);
      op0 = c_fully_fold_اندرونی (op0, وچ_init, &op0_const, &op0_const_self,
				   for_int_const, خطأ);

      STRIP_TYPE_NOPS (op0);
      c_disable_warnings (op0 == truthvalue_false_گرہ);
      op1 = c_fully_fold_اندرونی (op1, وچ_init, &op1_const, &op1_const_self,
				   for_int_const, خطأ);
      STRIP_TYPE_NOPS (op1);
      c_enable_warnings (op0 == truthvalue_false_گرہ);

      c_disable_warnings (op0 == truthvalue_true_گرہ);
      op2 = c_fully_fold_اندرونی (op2, وچ_init, &op2_const, &op2_const_self,
				   for_int_const, خطأ);
      STRIP_TYPE_NOPS (op2);
      c_enable_warnings (op0 == truthvalue_true_گرہ);

      إذا (for_int_const
	  && (درخت_کوڈ (op0) != INTEGER_CST
	      /* Only the evaluated operand must be an INTEGER_CST.  */
	      || (op0 == truthvalue_true_گرہ
		  ? درخت_کوڈ (op1) != INTEGER_CST
		  : درخت_کوڈ (op2) != INTEGER_CST)))
	اذهب باہرلا;

      إذا (op0 != orig_op0 || op1 != orig_op1 || op2 != orig_op2)
	ret = fold_build3_loc (loc, کوڈ, درخت_TYPE (اظہاریہ), op0, op1, op2);
      وإلا
	ret = fold (اظہاریہ);
      *maybe_const_operands &= op0_const;
      *maybe_const_itself &= op0_const_self;
      إذا (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && op0 == truthvalue_false_گرہ))
	*maybe_const_operands &= op1_const;
      إذا (!(op0_const
	    && op0_const_self
	    && op0 == truthvalue_false_گرہ))
	*maybe_const_itself &= op1_const_self;
      إذا (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && op0 == truthvalue_true_گرہ))
	*maybe_const_operands &= op2_const;
      إذا (!(op0_const
	    && op0_const_self
	    && op0 == truthvalue_true_گرہ))
	*maybe_const_itself &= op2_const_self;
      اذهب باہرلا;

    حالة VEC_COND_اظہاریہ:
      orig_op0 = op0 = درخت_عملیہ (اظہاریہ, 0);
      orig_op1 = op1 = درخت_عملیہ (اظہاریہ, 1);
      orig_op2 = op2 = درخت_عملیہ (اظہاریہ, 2);
      op0 = c_fully_fold_اندرونی (op0, وچ_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, خطأ);
      STRIP_TYPE_NOPS (op0);
      op1 = c_fully_fold_اندرونی (op1, وچ_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, خطأ);
      STRIP_TYPE_NOPS (op1);
      op2 = c_fully_fold_اندرونی (op2, وچ_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, خطأ);
      STRIP_TYPE_NOPS (op2);

      إذا (op0 != orig_op0 || op1 != orig_op1 || op2 != orig_op2)
	ret = fold_build3_loc (loc, کوڈ, درخت_TYPE (اظہاریہ), op0, op1, op2);
      وإلا
	ret = fold (اظہاریہ);
      اذهب باہرلا;

    حالة EXCESS_PRECISION_اظہاریہ:
      /* Each case where an operand with excess precision may be
	 encountered must remove the EXCESS_PRECISION_EXPR around
	 inner operands and possibly put one around the whole
	 expression or possibly convert to the semantic type (which
	 c_fully_fold does); we cannot tell at this stage which is
	 appropriate in any particular case.  */
      gcc_unreachable ();

    حالة SAVE_اظہاریہ:
      /* Make sure to fold the contents of a SAVE_EXPR exactly once.  */
      op0 = درخت_عملیہ (اظہاریہ, 0);
      إذا (!SAVE_اظہاریہ_FOLDED_P (اظہاریہ))
	{
	  op0 = c_fully_fold_اندرونی (op0, وچ_init, maybe_const_operands,
				       maybe_const_itself, for_int_const,
				       خطأ);
	  درخت_عملیہ (اظہاریہ, 0) = op0;
	  SAVE_اظہاریہ_FOLDED_P (اظہاریہ) = سچ;
	}
      /* Return the SAVE_EXPR operand if it is invariant.  */
      إذا (درخت_invariant_p (op0))
	ret = op0;
      اذهب باہرلا;

    افتراضي:
      /* Various codes may appear through folding built-in functions
	 and their arguments.  */
      اذهب باہرلا;
    }

 باہرلا:
  /* Some folding may introduce NON_LVALUE_EXPRs; all lvalue checks
     have been done by this point, so remove them again.  */
  nowarning |= warning_suppressed_p (ret, OPT_Woverflow);
  STRIP_TYPE_NOPS (ret);
  إذا (nowarning && !warning_suppressed_p (ret, OPT_Woverflow))
    {
      إذا (!CAN_HAVE_LOCATION_P (ret))
	ret = build1 (NOP_اظہاریہ, درخت_TYPE (ret), ret);
      suppress_warning (ret, OPT_Woverflow);
    }
  إذا (ret != اظہاریہ)
    {
      protected_سیٹ_اظہاریہ_location (ret, loc);
      إذا (IS_اظہاریہ_کوڈ_CLASS (قسم))
	سیٹ_سروت_range (ret, old_range.m_شروع, old_range.m_انت);
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
