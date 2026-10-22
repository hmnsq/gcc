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

ساكن درخت c_fully_fold_internal (درخت اظہاریہ, منطقي, منطقي *, منطقي *, منطقي,
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
c_fold_array_ref (درخت type, درخت ary, درخت index)
{
  إذا (درخت_CODE (ary) != STRING_CST
      || درخت_CODE (index) != INTEGER_CST
      || درخت_OVERFLOW (index)
      || درخت_CODE (درخت_TYPE (ary)) != ARRAY_TYPE
      || !درخت_fits_uhwi_p (index))
    أرجع NULL_درخت;

  درخت elem_type = درخت_TYPE (درخت_TYPE (ary));
  unsigned elem_nchars = (TYPE_PRECISION (elem_type)
			  / TYPE_PRECISION (char_type_گرہ));
  unsigned len = (unsigned) درخت_STRING_LENGTH (ary) / elem_nchars;
  درخت nelts_minus_one = array_type_nelts_minus_one (درخت_TYPE (ary));
  منطقي dummy1 = true, dummy2 = true;
  nelts_minus_one = c_fully_fold_internal (nelts_minus_one, true, &dummy1,
					   &dummy2, خطأ, خطأ);
  unsigned HOST_WIDE_INT i = درخت_to_uhwi (index);
  إذا (!درخت_int_cst_le (index, nelts_minus_one)
      || i >= len
      || i + elem_nchars > len)
    أرجع NULL_درخت;

  إذا (elem_nchars == 1)
    أرجع build_int_cst (type, درخت_STRING_POINTER (ary)[i]);

  ثابت unsigned حرف *ptr
    = ((ثابت unsigned حرف *)درخت_STRING_POINTER (ary) + i * elem_nchars);
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
c_fully_fold (درخت اظہاریہ, منطقي in_init, منطقي *maybe_const, منطقي lval)
{
  درخت ret;
  درخت eptype = NULL_درخت;
  منطقي dummy = true;
  منطقي maybe_const_itself = true;
  location_t loc = اظہاریہ_LOCATION (اظہاریہ);

  إذا (!maybe_const)
    maybe_const = &dummy;
  إذا (درخت_CODE (اظہاریہ) == EXCESS_PRECISION_اظہاریہ)
    {
      eptype = درخت_TYPE (اظہاریہ);
      اظہاریہ = درخت_OPERAND (اظہاریہ, 0);
    }
  ret = c_fully_fold_internal (اظہاریہ, in_init, maybe_const,
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
c_fully_fold_internal (درخت اظہاریہ, منطقي in_init, منطقي *maybe_const_operands,
		       منطقي *maybe_const_itself, منطقي for_int_const, منطقي lval)
{
  درخت ret = اظہاریہ;
  تعداد درخت_code code = درخت_CODE (اظہاریہ);
  تعداد درخت_code_class kind = درخت_CODE_CLASS (code);
  location_t loc = اظہاریہ_LOCATION (اظہاریہ);
  درخت op0, op1, op2, op3;
  درخت orig_op0, orig_op1, orig_op2;
  منطقي op0_const = true, op1_const = true, op2_const = true;
  منطقي op0_const_self = true, op1_const_self = true, op2_const_self = true;
  منطقي nowarning = warning_suppressed_p (اظہاریہ, OPT_Woverflow);
  منطقي unused_p;
  منطقي op0_lval = خطأ;
  source_range old_range;

  /* Constants, declarations, statements, errors, and anything else not
     counted as an expression cannot usefully be folded further at this
     point.  */
  إذا (!IS_اظہاریہ_CODE_CLASS (kind) || kind == tcc_statement)
    {
      /* Except for variables which we can optimize to its initializer.  */
      إذا (VAR_P (اظہاریہ) && !lval && (optimize || in_init))
	{
	  إذا (in_init)
	    ret = decl_constant_قدر_1 (اظہاریہ, true);
	  وإلا
	    {
	      ret = decl_constant_قدر (اظہاریہ);
	      إذا (ret != اظہاریہ
		  && (TYPE_MODE (درخت_TYPE (ret)) == BLKmode
		      || درخت_CODE (درخت_TYPE (ret)) == ARRAY_TYPE))
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

  إذا (IS_اظہاریہ_CODE_CLASS (kind))
    old_range = اظہاریہ_LOCATION_RANGE (اظہاریہ);

  /* Operands of variable-length expressions (function calls) have
     already been folded, as have __builtin_* function calls, and such
     expressions cannot occur in constant expressions.  */
  إذا (kind == tcc_vl_exp)
    {
      *maybe_const_operands = خطأ;
      ret = fold (اظہاریہ);
      اذهب out;
    }

  إذا (code == C_MAYBE_CONST_اظہاریہ)
    {
      درخت pre = C_MAYBE_CONST_اظہاریہ_PRE (اظہاریہ);
      درخت inner = C_MAYBE_CONST_اظہاریہ_اظہاریہ (اظہاریہ);
      إذا (C_MAYBE_CONST_اظہاریہ_NON_CONST (اظہاریہ))
	*maybe_const_operands = خطأ;
      إذا (C_MAYBE_CONST_اظہاریہ_INT_OPERANDS (اظہاریہ))
	{
	  *maybe_const_itself = خطأ;
	  inner = c_fully_fold_internal (inner, in_init, maybe_const_operands,
					 maybe_const_itself, true, lval);
	}
      إذا (pre && !in_init)
	ret = build2 (COMPOUND_اظہاریہ, درخت_TYPE (اظہاریہ), pre, inner);
      وإلا
	ret = inner;
      اذهب out;
    }

  /* Assignment, increment, decrement, function call and comma
     operators, and statement expressions, cannot occur in constant
     expressions if evaluated / outside of sizeof.  (Function calls
     were handled above, though VA_ARG_EXPR is treated like a function
     call here, and statement expressions are handled through
     C_MAYBE_CONST_EXPR to avoid folding inside them.)  */
  بدل (code)
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
    حالة TARGET_اظہاریہ:
    حالة BIND_اظہاریہ:
    حالة OBJ_TYPE_REF:
      *maybe_const_operands = خطأ;
      ret = fold (اظہاریہ);
      اذهب out;

    افتراضي:
      اكسر;
    }

  /* Fold individual tree codes as appropriate.  */
  بدل (code)
    {
    حالة COMPOUND_LITERAL_اظہاریہ:
      /* Any non-constancy will have been marked in a containing
	 C_MAYBE_CONST_EXPR; there is no more folding to do here.  */
      اذهب out;

    حالة COMPONENT_REF:
      orig_op0 = op0 = درخت_OPERAND (اظہاریہ, 0);
      op1 = درخت_OPERAND (اظہاریہ, 1);
      op2 = درخت_OPERAND (اظہاریہ, 2);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
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
      اذهب out;

    حالة ARRAY_REF:
      orig_op0 = op0 = درخت_OPERAND (اظہاریہ, 0);
      orig_op1 = op1 = درخت_OPERAND (اظہاریہ, 1);
      op2 = درخت_OPERAND (اظہاریہ, 2);
      op3 = درخت_OPERAND (اظہاریہ, 3);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, lval);
      STRIP_TYPE_NOPS (op0);
      op1 = c_fully_fold_internal (op1, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, خطأ);
      STRIP_TYPE_NOPS (op1);
      /* Fold "foo"[2] in initializers.  */
      إذا (!lval && in_init)
	{
	  ret = c_fold_array_ref (درخت_TYPE (اظہاریہ), op0, op1);
	  إذا (ret)
	    اذهب out;
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
      اذهب out;

    حالة MODIFY_اظہاریہ:
    حالة PREDECREMENT_اظہاریہ:
    حالة PREINCREMENT_اظہاریہ:
    حالة POSTDECREMENT_اظہاریہ:
    حالة POSTINCREMENT_اظہاریہ:
      op0_lval = true;
      /* FALLTHRU */
    حالة COMPOUND_اظہاریہ:
    حالة PLUS_اظہاریہ:
    حالة MINUS_اظہاریہ:
    حالة MULT_اظہاریہ:
    حالة POINTER_PLUS_اظہاریہ:
    حالة POINTER_DIFF_اظہاریہ:
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
    حالة BIT_IOR_اظہاریہ:
    حالة BIT_XOR_اظہاریہ:
    حالة BIT_AND_اظہاریہ:
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
      orig_op0 = op0 = درخت_OPERAND (اظہاریہ, 0);
      orig_op1 = op1 = درخت_OPERAND (اظہاریہ, 1);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const,
				   op0_lval);
      STRIP_TYPE_NOPS (op0);
      /* The RHS of a MODIFY_EXPR was fully folded when building that
	 expression for the sake of conversion warnings.  */
      إذا (code != MODIFY_اظہاریہ)
	op1 = c_fully_fold_internal (op1, in_init, maybe_const_operands,
				     maybe_const_itself, for_int_const, خطأ);
      STRIP_TYPE_NOPS (op1);

      إذا (for_int_const && (درخت_CODE (op0) != INTEGER_CST
			    || درخت_CODE (op1) != INTEGER_CST))
	اذهب out;

      إذا (درخت_CODE_CLASS (code) == tcc_comparison
	  && درخت_CODE (درخت_TYPE (op0)) == NULLPTR_TYPE
	  && درخت_CODE (درخت_TYPE (op1)) == NULLPTR_TYPE)
	{
	  بدل (code)
	    {
	    حالة EQ_اظہاریہ:
	      ret = constant_boolean_گرہ (true, درخت_TYPE (اظہاریہ));
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
      وإلا إذا (op0 != orig_op0 || op1 != orig_op1 || in_init)
	ret = in_init
	  ? fold_build2_initializer_loc (loc, code, درخت_TYPE (اظہاریہ), op0, op1)
	  : fold_build2_loc (loc, code, درخت_TYPE (اظہاریہ), op0, op1);
      وإلا
	ret = fold (اظہاریہ);
      إذا (درخت_OVERFLOW_P (ret)
	  && !درخت_OVERFLOW_P (op0)
	  && !(ثنائی_CLASS_P (op0) && درخت_OVERFLOW_P (درخت_OPERAND (op0, 1)))
	  && !درخت_OVERFLOW_P (op1))
	overflow_warning (اظہاریہ_LOC_OR_LOC (اظہاریہ, داخلہ_location), ret, اظہاریہ);
      إذا (code == LSHIFT_اظہاریہ
	  && درخت_CODE (orig_op0) != INTEGER_CST
	  && (درخت_CODE (درخت_TYPE (orig_op0)) == INTEGER_TYPE
	      || درخت_CODE (درخت_TYPE (orig_op0)) == BITINT_TYPE)
	  && درخت_CODE (op0) == INTEGER_CST
	  && c_inhibit_evaluation_warnings == 0
	  && !TYPE_OVERFLOW_WRAPS (درخت_TYPE (orig_op0))
	  && درخت_int_cst_sgn (op0) < 0)
	warning_at (loc, OPT_Wshift_negative_قدر,
		    "left shift of negative value");
      إذا ((code == LSHIFT_اظہاریہ
	   || code == RSHIFT_اظہاریہ
	   || code == LROTATE_اظہاریہ
	   || code == RROTATE_اظہاریہ)
	  && درخت_CODE (orig_op1) != INTEGER_CST
	  && درخت_CODE (op1) == INTEGER_CST
	  && درخت_CODE (درخت_TYPE (orig_op1)) == INTEGER_TYPE
	  && c_inhibit_evaluation_warnings == 0)
	{
	  إذا (درخت_int_cst_sgn (op1) < 0)
	    warning_at (loc, OPT_Wshift_گنتی_negative,
			(code == LSHIFT_اظہاریہ
			 ? G_("left shift count is negative")
			 : G_("right shift count is negative")));
	  وإلا إذا ((درخت_CODE (درخت_TYPE (orig_op0)) == INTEGER_TYPE
		    || درخت_CODE (درخت_TYPE (orig_op0)) == BITINT_TYPE
		    || درخت_CODE (درخت_TYPE (orig_op0)) == FIXED_POINT_TYPE)
		   && compare_درخت_int (op1,
					TYPE_PRECISION (درخت_TYPE (orig_op0)))
		      >= 0
		   && !warning_suppressed_p (اظہاریہ, OPT_Wshift_گنتی_overflow))
	    warning_at (loc, OPT_Wshift_گنتی_overflow,
			(code == LSHIFT_اظہاریہ
			 ? G_("left shift count >= width of type")
			 : G_("right shift count >= width of type")));
	  وإلا إذا (درخت_CODE (درخت_TYPE (orig_op0)) == VECTOR_TYPE
		   && compare_درخت_int (op1,
					TYPE_PRECISION (درخت_TYPE (درخت_TYPE (orig_op0))))
		      >= 0)
	    warning_at (loc, OPT_Wshift_گنتی_overflow,
			code == LSHIFT_اظہاریہ
			? G_("left shift count >= width of vector element")
			: G_("right shift count >= width of vector element"));
	}
      إذا (code == LSHIFT_اظہاریہ
	  /* If either OP0 has been folded to INTEGER_CST...  */
	  && ((درخت_CODE (orig_op0) != INTEGER_CST
	       && (درخت_CODE (درخت_TYPE (orig_op0)) == INTEGER_TYPE
		   || درخت_CODE (درخت_TYPE (orig_op0)) == BITINT_TYPE)
	       && درخت_CODE (op0) == INTEGER_CST)
	      /* ...or if OP1 has been folded to INTEGER_CST...  */
	      || (درخت_CODE (orig_op1) != INTEGER_CST
		  && (درخت_CODE (درخت_TYPE (orig_op1)) == INTEGER_TYPE
		      || درخت_CODE (درخت_TYPE (orig_op1)) == BITINT_TYPE)
		  && درخت_CODE (op1) == INTEGER_CST))
	  && c_inhibit_evaluation_warnings == 0)
	/* ...then maybe we can detect an overflow.  */
	maybe_warn_shift_overflow (loc, op0, op1);
      إذا ((code == TRUNC_DIV_اظہاریہ
	   || code == CEIL_DIV_اظہاریہ
	   || code == FLOOR_DIV_اظہاریہ
	   || code == EXACT_DIV_اظہاریہ
	   || code == TRUNC_MOD_اظہاریہ)
	  && درخت_CODE (orig_op1) != INTEGER_CST
	  && درخت_CODE (op1) == INTEGER_CST
	  && (درخت_CODE (درخت_TYPE (orig_op0)) == INTEGER_TYPE
	      || درخت_CODE (درخت_TYPE (orig_op0)) == BITINT_TYPE
	      || درخت_CODE (درخت_TYPE (orig_op0)) == FIXED_POINT_TYPE)
	  && (درخت_CODE (درخت_TYPE (orig_op1)) == INTEGER_TYPE
	      || درخت_CODE (درخت_TYPE (orig_op1)) == BITINT_TYPE))
	warn_for_div_by_zero (loc, op1);
      إذا (code == MEM_REF
	  && ret != اظہاریہ
	  && درخت_CODE (ret) == MEM_REF)
	{
	  درخت_READONLY (ret) = درخت_READONLY (اظہاریہ);
	  درخت_SIDE_EFFECTS (ret) = درخت_SIDE_EFFECTS (اظہاریہ);
	  درخت_THIS_VOLATILE (ret) = درخت_THIS_VOLATILE (اظہاریہ);
	}
      اذهب out;

    حالة ADDR_اظہاریہ:
      op0_lval = true;
      اذهب unary;
    حالة REALPART_اظہاریہ:
    حالة IMAGPART_اظہاریہ:
    حالة VIEW_CONVERT_اظہاریہ:
      op0_lval = lval;
      /* FALLTHRU */
    حالة INDIRECT_REF:
    حالة FIX_TRUNC_اظہاریہ:
    حالة FLOAT_اظہاریہ:
    CASE_CONVERT:
    حالة ADDR_SPACE_CONVERT_اظہاریہ:
    حالة NON_LVALUE_اظہاریہ:
    حالة NEGATE_اظہاریہ:
    حالة BIT_NOT_اظہاریہ:
    حالة TRUTH_NOT_اظہاریہ:
    حالة CONJ_اظہاریہ:
    حالة PAREN_اظہاریہ:
    unary:
      /* Unary operations.  */
      orig_op0 = op0 = درخت_OPERAND (اظہاریہ, 0);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const,
				   op0_lval);
      STRIP_TYPE_NOPS (op0);

      إذا (for_int_const && درخت_CODE (op0) != INTEGER_CST)
	اذهب out;

      /* ??? Cope with user tricks that amount to offsetof.  The middle-end is
	 not prepared to deal with them if they occur in initializers.  */
      إذا (op0 != orig_op0
	  && code == ADDR_اظہاریہ
	  && (op1 = get_base_address (op0)) != NULL_درخت
	  && INDIRECT_REF_P (op1)
	  && درخت_CONSTANT (درخت_OPERAND (op1, 0)))
	ret = fold_offsetof (op0, درخت_TYPE (اظہاریہ));
      وإلا إذا (op0 != orig_op0 || in_init)
	ret = in_init
	  ? fold_build1_initializer_loc (loc, code, درخت_TYPE (اظہاریہ), op0)
	  : fold_build1_loc (loc, code, درخت_TYPE (اظہاریہ), op0);
      وإلا
	ret = fold (اظہاریہ);
      إذا (code == INDIRECT_REF
	  && ret != اظہاریہ
	  && INDIRECT_REF_P (ret))
	{
	  درخت_READONLY (ret) = درخت_READONLY (اظہاریہ);
	  درخت_SIDE_EFFECTS (ret) = درخت_SIDE_EFFECTS (اظہاریہ);
	  درخت_THIS_VOLATILE (ret) = درخت_THIS_VOLATILE (اظہاریہ);
	}
      بدل (code)
	{
	حالة FIX_TRUNC_اظہاریہ:
	حالة FLOAT_اظہاریہ:
	CASE_CONVERT:
	  /* Don't warn about explicit conversions.  We will already
	     have warned about suspect implicit conversions.  */
	  اكسر;

	افتراضي:
	  إذا (درخت_OVERFLOW_P (ret) && !درخت_OVERFLOW_P (op0))
	    overflow_warning (اظہاریہ_LOCATION (اظہاریہ), ret, op0);
	  اكسر;
	}
      اذهب out;

    حالة TRUTH_ANDIF_اظہاریہ:
    حالة TRUTH_ORIF_اظہاریہ:
      /* Binary operations not necessarily evaluating both
	 arguments.  */
      orig_op0 = op0 = درخت_OPERAND (اظہاریہ, 0);
      orig_op1 = op1 = درخت_OPERAND (اظہاریہ, 1);
      op0 = c_fully_fold_internal (op0, in_init, &op0_const, &op0_const_self,
				   for_int_const, خطأ);
      STRIP_TYPE_NOPS (op0);

      unused_p = (op0 == (code == TRUTH_ANDIF_اظہاریہ
			  ? truthvalue_false_گرہ
			  : truthvalue_true_گرہ));
      c_disable_warnings (unused_p);
      op1 = c_fully_fold_internal (op1, in_init, &op1_const, &op1_const_self,
				   for_int_const, خطأ);
      STRIP_TYPE_NOPS (op1);
      c_enable_warnings (unused_p);

      إذا (for_int_const
	  && (درخت_CODE (op0) != INTEGER_CST
	      /* Require OP1 be an INTEGER_CST only if it's evaluated.  */
	      || (!unused_p && درخت_CODE (op1) != INTEGER_CST)))
	اذهب out;

      إذا (op0 != orig_op0 || op1 != orig_op1 || in_init)
	ret = in_init
	  ? fold_build2_initializer_loc (loc, code, درخت_TYPE (اظہاریہ), op0, op1)
	  : fold_build2_loc (loc, code, درخت_TYPE (اظہاریہ), op0, op1);
      وإلا
	ret = fold (اظہاریہ);
      *maybe_const_operands &= op0_const;
      *maybe_const_itself &= op0_const_self;
      إذا (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && (code == TRUTH_ANDIF_اظہاریہ
		? op0 == truthvalue_false_گرہ
		: op0 == truthvalue_true_گرہ)))
	*maybe_const_operands &= op1_const;
      إذا (!(op0_const
	    && op0_const_self
	    && (code == TRUTH_ANDIF_اظہاریہ
		? op0 == truthvalue_false_گرہ
		: op0 == truthvalue_true_گرہ)))
	*maybe_const_itself &= op1_const_self;
      اذهب out;

    حالة COND_اظہاریہ:
      orig_op0 = op0 = درخت_OPERAND (اظہاریہ, 0);
      orig_op1 = op1 = درخت_OPERAND (اظہاریہ, 1);
      orig_op2 = op2 = درخت_OPERAND (اظہاریہ, 2);
      op0 = c_fully_fold_internal (op0, in_init, &op0_const, &op0_const_self,
				   for_int_const, خطأ);

      STRIP_TYPE_NOPS (op0);
      c_disable_warnings (op0 == truthvalue_false_گرہ);
      op1 = c_fully_fold_internal (op1, in_init, &op1_const, &op1_const_self,
				   for_int_const, خطأ);
      STRIP_TYPE_NOPS (op1);
      c_enable_warnings (op0 == truthvalue_false_گرہ);

      c_disable_warnings (op0 == truthvalue_true_گرہ);
      op2 = c_fully_fold_internal (op2, in_init, &op2_const, &op2_const_self,
				   for_int_const, خطأ);
      STRIP_TYPE_NOPS (op2);
      c_enable_warnings (op0 == truthvalue_true_گرہ);

      إذا (for_int_const
	  && (درخت_CODE (op0) != INTEGER_CST
	      /* Only the evaluated operand must be an INTEGER_CST.  */
	      || (op0 == truthvalue_true_گرہ
		  ? درخت_CODE (op1) != INTEGER_CST
		  : درخت_CODE (op2) != INTEGER_CST)))
	اذهب out;

      إذا (op0 != orig_op0 || op1 != orig_op1 || op2 != orig_op2)
	ret = fold_build3_loc (loc, code, درخت_TYPE (اظہاریہ), op0, op1, op2);
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
      اذهب out;

    حالة VEC_COND_اظہاریہ:
      orig_op0 = op0 = درخت_OPERAND (اظہاریہ, 0);
      orig_op1 = op1 = درخت_OPERAND (اظہاریہ, 1);
      orig_op2 = op2 = درخت_OPERAND (اظہاریہ, 2);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, خطأ);
      STRIP_TYPE_NOPS (op0);
      op1 = c_fully_fold_internal (op1, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, خطأ);
      STRIP_TYPE_NOPS (op1);
      op2 = c_fully_fold_internal (op2, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, خطأ);
      STRIP_TYPE_NOPS (op2);

      إذا (op0 != orig_op0 || op1 != orig_op1 || op2 != orig_op2)
	ret = fold_build3_loc (loc, code, درخت_TYPE (اظہاریہ), op0, op1, op2);
      وإلا
	ret = fold (اظہاریہ);
      اذهب out;

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
      op0 = درخت_OPERAND (اظہاریہ, 0);
      إذا (!SAVE_اظہاریہ_FOLDED_P (اظہاریہ))
	{
	  op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				       maybe_const_itself, for_int_const,
				       خطأ);
	  درخت_OPERAND (اظہاریہ, 0) = op0;
	  SAVE_اظہاریہ_FOLDED_P (اظہاریہ) = true;
	}
      /* Return the SAVE_EXPR operand if it is invariant.  */
      إذا (درخت_invariant_p (op0))
	ret = op0;
      اذهب out;

    افتراضي:
      /* Various codes may appear through folding built-in functions
	 and their arguments.  */
      اذهب out;
    }

 out:
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
      protected_set_اظہاریہ_location (ret, loc);
      إذا (IS_اظہاریہ_CODE_CLASS (kind))
	set_source_range (ret, old_range.m_start, old_range.m_finish);
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
