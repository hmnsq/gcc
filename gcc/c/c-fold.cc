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

ساكن درەخت c_fully_fold_internal (درەخت دەربڕین, منطقي, منطقي *, منطقي *, منطقي,
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

ساكن درەخت
c_fold_array_ref (درەخت type, درەخت ary, درەخت index)
{
  إذا (درەخت_CODE (ary) != STRING_CST
      || درەخت_CODE (index) != INTEGER_CST
      || درەخت_OVERFLOW (index)
      || درەخت_CODE (درەخت_TYPE (ary)) != ARRAY_TYPE
      || !درەخت_fits_uhwi_p (index))
    أرجع NULL_درەخت;

  درەخت elem_type = درەخت_TYPE (درەخت_TYPE (ary));
  unsigned elem_nchars = (TYPE_PRECISION (elem_type)
			  / TYPE_PRECISION (char_type_گرێ));
  unsigned len = (unsigned) درەخت_STRING_LENGTH (ary) / elem_nchars;
  درەخت nelts_minus_one = array_type_nelts_minus_one (درەخت_TYPE (ary));
  منطقي dummy1 = true, dummy2 = true;
  nelts_minus_one = c_fully_fold_internal (nelts_minus_one, true, &dummy1,
					   &dummy2, خطأ, خطأ);
  unsigned HOST_WIDE_INT i = درەخت_to_uhwi (index);
  إذا (!درەخت_int_cst_le (index, nelts_minus_one)
      || i >= len
      || i + elem_nchars > len)
    أرجع NULL_درەخت;

  إذا (elem_nchars == 1)
    أرجع build_int_cst (type, درەخت_STRING_POINTER (ary)[i]);

  ثابت unsigned حرف *ptr
    = ((ثابت unsigned حرف *)درەخت_STRING_POINTER (ary) + i * elem_nchars);
  أرجع native_interpret_دەربڕین (type, ptr, elem_nchars);
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

درەخت
c_fully_fold (درەخت دەربڕین, منطقي in_init, منطقي *maybe_const, منطقي lval)
{
  درەخت ret;
  درەخت eptype = NULL_درەخت;
  منطقي dummy = true;
  منطقي maybe_const_itself = true;
  location_t loc = دەربڕین_LOCATION (دەربڕین);

  إذا (!maybe_const)
    maybe_const = &dummy;
  إذا (درەخت_CODE (دەربڕین) == EXCESS_PRECISION_دەربڕین)
    {
      eptype = درەخت_TYPE (دەربڕین);
      دەربڕین = درەخت_OPERAND (دەربڕین, 0);
    }
  ret = c_fully_fold_internal (دەربڕین, in_init, maybe_const,
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

ساكن درەخت
c_fully_fold_internal (درەخت دەربڕین, منطقي in_init, منطقي *maybe_const_operands,
		       منطقي *maybe_const_itself, منطقي for_int_const, منطقي lval)
{
  درەخت ret = دەربڕین;
  تعداد درەخت_code code = درەخت_CODE (دەربڕین);
  تعداد درەخت_code_class kind = درەخت_CODE_CLASS (code);
  location_t loc = دەربڕین_LOCATION (دەربڕین);
  درەخت op0, op1, op2, op3;
  درەخت orig_op0, orig_op1, orig_op2;
  منطقي op0_const = true, op1_const = true, op2_const = true;
  منطقي op0_const_self = true, op1_const_self = true, op2_const_self = true;
  منطقي nowarning = warning_suppressed_p (دەربڕین, OPT_Woverflow);
  منطقي unused_p;
  منطقي op0_lval = خطأ;
  source_range old_range;

  /* Constants, declarations, statements, errors, and anything else not
     counted as an expression cannot usefully be folded further at this
     point.  */
  إذا (!IS_دەربڕین_CODE_CLASS (kind) || kind == tcc_statement)
    {
      /* Except for variables which we can optimize to its initializer.  */
      إذا (VAR_P (دەربڕین) && !lval && (optimize || in_init))
	{
	  إذا (in_init)
	    ret = decl_constant_بەها_1 (دەربڕین, true);
	  وإلا
	    {
	      ret = decl_constant_بەها (دەربڕین);
	      إذا (ret != دەربڕین
		  && (TYPE_MODE (درەخت_TYPE (ret)) == BLKmode
		      || درەخت_CODE (درەخت_TYPE (ret)) == ARRAY_TYPE))
		أرجع دەربڕین;
	    }
	  /* Avoid unwanted tree sharing between the initializer and current
	     function's body where the tree can be modified e.g. by the
	     gimplifier.  */
	  إذا (ret != دەربڕین && درەخت_STATIC (دەربڕین))
	    ret = unshare_دەربڕین (ret);
	  أرجع ret;
	}
      أرجع دەربڕین;
    }

  إذا (IS_دەربڕین_CODE_CLASS (kind))
    old_range = دەربڕین_LOCATION_RANGE (دەربڕین);

  /* Operands of variable-length expressions (function calls) have
     already been folded, as have __builtin_* function calls, and such
     expressions cannot occur in constant expressions.  */
  إذا (kind == tcc_vl_exp)
    {
      *maybe_const_operands = خطأ;
      ret = fold (دەربڕین);
      اذهب out;
    }

  إذا (code == C_MAYBE_CONST_دەربڕین)
    {
      درەخت pre = C_MAYBE_CONST_دەربڕین_PRE (دەربڕین);
      درەخت inner = C_MAYBE_CONST_دەربڕین_دەربڕین (دەربڕین);
      إذا (C_MAYBE_CONST_دەربڕین_NON_CONST (دەربڕین))
	*maybe_const_operands = خطأ;
      إذا (C_MAYBE_CONST_دەربڕین_INT_OPERANDS (دەربڕین))
	{
	  *maybe_const_itself = خطأ;
	  inner = c_fully_fold_internal (inner, in_init, maybe_const_operands,
					 maybe_const_itself, true, lval);
	}
      إذا (pre && !in_init)
	ret = build2 (COMPOUND_دەربڕین, درەخت_TYPE (دەربڕین), pre, inner);
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
    حالة MODIFY_دەربڕین:
    حالة PREDECREMENT_دەربڕین:
    حالة PREINCREMENT_دەربڕین:
    حالة POSTDECREMENT_دەربڕین:
    حالة POSTINCREMENT_دەربڕین:
    حالة COMPOUND_دەربڕین:
      *maybe_const_operands = خطأ;
      اكسر;

    حالة VA_ARG_دەربڕین:
    حالة TARGET_دەربڕین:
    حالة BIND_دەربڕین:
    حالة OBJ_TYPE_REF:
      *maybe_const_operands = خطأ;
      ret = fold (دەربڕین);
      اذهب out;

    افتراضي:
      اكسر;
    }

  /* Fold individual tree codes as appropriate.  */
  بدل (code)
    {
    حالة COMPOUND_LITERAL_دەربڕین:
      /* Any non-constancy will have been marked in a containing
	 C_MAYBE_CONST_EXPR; there is no more folding to do here.  */
      اذهب out;

    حالة COMPONENT_REF:
      orig_op0 = op0 = درەخت_OPERAND (دەربڕین, 0);
      op1 = درەخت_OPERAND (دەربڕین, 1);
      op2 = درەخت_OPERAND (دەربڕین, 2);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, lval);
      STRIP_TYPE_NOPS (op0);
      إذا (op0 != orig_op0)
	ret = build3 (COMPONENT_REF, درەخت_TYPE (دەربڕین), op0, op1, op2);
      إذا (ret != دەربڕین)
	{
	  درەخت_READONLY (ret) = درەخت_READONLY (دەربڕین);
	  درەخت_THIS_VOLATILE (ret) = درەخت_THIS_VOLATILE (دەربڕین);
	}
      إذا (!lval)
	ret = fold (ret);
      اذهب out;

    حالة ARRAY_REF:
      orig_op0 = op0 = درەخت_OPERAND (دەربڕین, 0);
      orig_op1 = op1 = درەخت_OPERAND (دەربڕین, 1);
      op2 = درەخت_OPERAND (دەربڕین, 2);
      op3 = درەخت_OPERAND (دەربڕین, 3);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, lval);
      STRIP_TYPE_NOPS (op0);
      op1 = c_fully_fold_internal (op1, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, خطأ);
      STRIP_TYPE_NOPS (op1);
      /* Fold "foo"[2] in initializers.  */
      إذا (!lval && in_init)
	{
	  ret = c_fold_array_ref (درەخت_TYPE (دەربڕین), op0, op1);
	  إذا (ret)
	    اذهب out;
	  ret = دەربڕین;
	}
      إذا (op0 != orig_op0 || op1 != orig_op1)
	ret = build4 (ARRAY_REF, درەخت_TYPE (دەربڕین), op0, op1, op2, op3);
      إذا (ret != دەربڕین)
	{
	  درەخت_READONLY (ret) = درەخت_READONLY (دەربڕین);
	  درەخت_SIDE_EFFECTS (ret) = درەخت_SIDE_EFFECTS (دەربڕین);
	  درەخت_THIS_VOLATILE (ret) = درەخت_THIS_VOLATILE (دەربڕین);
	}
      إذا (!lval)
	ret = fold (ret);
      اذهب out;

    حالة MODIFY_دەربڕین:
    حالة PREDECREMENT_دەربڕین:
    حالة PREINCREMENT_دەربڕین:
    حالة POSTDECREMENT_دەربڕین:
    حالة POSTINCREMENT_دەربڕین:
      op0_lval = true;
      /* FALLTHRU */
    حالة COMPOUND_دەربڕین:
    حالة PLUS_دەربڕین:
    حالة MINUS_دەربڕین:
    حالة MULT_دەربڕین:
    حالة POINTER_PLUS_دەربڕین:
    حالة POINTER_DIFF_دەربڕین:
    حالة TRUNC_DIV_دەربڕین:
    حالة CEIL_DIV_دەربڕین:
    حالة FLOOR_DIV_دەربڕین:
    حالة TRUNC_MOD_دەربڕین:
    حالة RDIV_دەربڕین:
    حالة EXACT_DIV_دەربڕین:
    حالة LSHIFT_دەربڕین:
    حالة RSHIFT_دەربڕین:
    حالة LROTATE_دەربڕین:
    حالة RROTATE_دەربڕین:
    حالة BIT_IOR_دەربڕین:
    حالة BIT_XOR_دەربڕین:
    حالة BIT_AND_دەربڕین:
    حالة LT_دەربڕین:
    حالة LE_دەربڕین:
    حالة GT_دەربڕین:
    حالة GE_دەربڕین:
    حالة EQ_دەربڕین:
    حالة NE_دەربڕین:
    حالة COMPLEX_دەربڕین:
    حالة TRUTH_AND_دەربڕین:
    حالة TRUTH_OR_دەربڕین:
    حالة TRUTH_XOR_دەربڕین:
    حالة UNORDERED_دەربڕین:
    حالة ORDERED_دەربڕین:
    حالة UNLT_دەربڕین:
    حالة UNLE_دەربڕین:
    حالة UNGT_دەربڕین:
    حالة UNGE_دەربڕین:
    حالة UNEQ_دەربڕین:
    حالة MEM_REF:
      /* Binary operations evaluating both arguments (increment and
	 decrement are binary internally in GCC).  */
      orig_op0 = op0 = درەخت_OPERAND (دەربڕین, 0);
      orig_op1 = op1 = درەخت_OPERAND (دەربڕین, 1);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const,
				   op0_lval);
      STRIP_TYPE_NOPS (op0);
      /* The RHS of a MODIFY_EXPR was fully folded when building that
	 expression for the sake of conversion warnings.  */
      إذا (code != MODIFY_دەربڕین)
	op1 = c_fully_fold_internal (op1, in_init, maybe_const_operands,
				     maybe_const_itself, for_int_const, خطأ);
      STRIP_TYPE_NOPS (op1);

      إذا (for_int_const && (درەخت_CODE (op0) != INTEGER_CST
			    || درەخت_CODE (op1) != INTEGER_CST))
	اذهب out;

      إذا (درەخت_CODE_CLASS (code) == tcc_comparison
	  && درەخت_CODE (درەخت_TYPE (op0)) == NULLPTR_TYPE
	  && درەخت_CODE (درەخت_TYPE (op1)) == NULLPTR_TYPE)
	{
	  بدل (code)
	    {
	    حالة EQ_دەربڕین:
	      ret = constant_boolean_گرێ (true, درەخت_TYPE (دەربڕین));
	      اكسر;
	    حالة NE_دەربڕین:
	      ret = constant_boolean_گرێ (خطأ, درەخت_TYPE (دەربڕین));
	      اكسر;
	    افتراضي:
	      gcc_unreachable ();
	    }
	  ret = omit_two_operands_loc (loc, درەخت_TYPE (دەربڕین), ret,
				       op0, op1);
	}
      وإلا إذا (op0 != orig_op0 || op1 != orig_op1 || in_init)
	ret = in_init
	  ? fold_build2_initializer_loc (loc, code, درەخت_TYPE (دەربڕین), op0, op1)
	  : fold_build2_loc (loc, code, درەخت_TYPE (دەربڕین), op0, op1);
      وإلا
	ret = fold (دەربڕین);
      إذا (درەخت_OVERFLOW_P (ret)
	  && !درەخت_OVERFLOW_P (op0)
	  && !(دووانەیی_CLASS_P (op0) && درەخت_OVERFLOW_P (درەخت_OPERAND (op0, 1)))
	  && !درەخت_OVERFLOW_P (op1))
	overflow_warning (دەربڕین_LOC_OR_LOC (دەربڕین, تێخستن_location), ret, دەربڕین);
      إذا (code == LSHIFT_دەربڕین
	  && درەخت_CODE (orig_op0) != INTEGER_CST
	  && (درەخت_CODE (درەخت_TYPE (orig_op0)) == INTEGER_TYPE
	      || درەخت_CODE (درەخت_TYPE (orig_op0)) == BITINT_TYPE)
	  && درەخت_CODE (op0) == INTEGER_CST
	  && c_inhibit_evaluation_warnings == 0
	  && !TYPE_OVERFLOW_WRAPS (درەخت_TYPE (orig_op0))
	  && درەخت_int_cst_sgn (op0) < 0)
	warning_at (loc, OPT_Wshift_negative_بەها,
		    "left shift of negative value");
      إذا ((code == LSHIFT_دەربڕین
	   || code == RSHIFT_دەربڕین
	   || code == LROTATE_دەربڕین
	   || code == RROTATE_دەربڕین)
	  && درەخت_CODE (orig_op1) != INTEGER_CST
	  && درەخت_CODE (op1) == INTEGER_CST
	  && درەخت_CODE (درەخت_TYPE (orig_op1)) == INTEGER_TYPE
	  && c_inhibit_evaluation_warnings == 0)
	{
	  إذا (درەخت_int_cst_sgn (op1) < 0)
	    warning_at (loc, OPT_Wshift_ژماردن_negative,
			(code == LSHIFT_دەربڕین
			 ? G_("left shift count is negative")
			 : G_("right shift count is negative")));
	  وإلا إذا ((درەخت_CODE (درەخت_TYPE (orig_op0)) == INTEGER_TYPE
		    || درەخت_CODE (درەخت_TYPE (orig_op0)) == BITINT_TYPE
		    || درەخت_CODE (درەخت_TYPE (orig_op0)) == FIXED_POINT_TYPE)
		   && compare_درەخت_int (op1,
					TYPE_PRECISION (درەخت_TYPE (orig_op0)))
		      >= 0
		   && !warning_suppressed_p (دەربڕین, OPT_Wshift_ژماردن_overflow))
	    warning_at (loc, OPT_Wshift_ژماردن_overflow,
			(code == LSHIFT_دەربڕین
			 ? G_("left shift count >= width of type")
			 : G_("right shift count >= width of type")));
	  وإلا إذا (درەخت_CODE (درەخت_TYPE (orig_op0)) == VECTOR_TYPE
		   && compare_درەخت_int (op1,
					TYPE_PRECISION (درەخت_TYPE (درەخت_TYPE (orig_op0))))
		      >= 0)
	    warning_at (loc, OPT_Wshift_ژماردن_overflow,
			code == LSHIFT_دەربڕین
			? G_("left shift count >= width of vector element")
			: G_("right shift count >= width of vector element"));
	}
      إذا (code == LSHIFT_دەربڕین
	  /* If either OP0 has been folded to INTEGER_CST...  */
	  && ((درەخت_CODE (orig_op0) != INTEGER_CST
	       && (درەخت_CODE (درەخت_TYPE (orig_op0)) == INTEGER_TYPE
		   || درەخت_CODE (درەخت_TYPE (orig_op0)) == BITINT_TYPE)
	       && درەخت_CODE (op0) == INTEGER_CST)
	      /* ...or if OP1 has been folded to INTEGER_CST...  */
	      || (درەخت_CODE (orig_op1) != INTEGER_CST
		  && (درەخت_CODE (درەخت_TYPE (orig_op1)) == INTEGER_TYPE
		      || درەخت_CODE (درەخت_TYPE (orig_op1)) == BITINT_TYPE)
		  && درەخت_CODE (op1) == INTEGER_CST))
	  && c_inhibit_evaluation_warnings == 0)
	/* ...then maybe we can detect an overflow.  */
	maybe_warn_shift_overflow (loc, op0, op1);
      إذا ((code == TRUNC_DIV_دەربڕین
	   || code == CEIL_DIV_دەربڕین
	   || code == FLOOR_DIV_دەربڕین
	   || code == EXACT_DIV_دەربڕین
	   || code == TRUNC_MOD_دەربڕین)
	  && درەخت_CODE (orig_op1) != INTEGER_CST
	  && درەخت_CODE (op1) == INTEGER_CST
	  && (درەخت_CODE (درەخت_TYPE (orig_op0)) == INTEGER_TYPE
	      || درەخت_CODE (درەخت_TYPE (orig_op0)) == BITINT_TYPE
	      || درەخت_CODE (درەخت_TYPE (orig_op0)) == FIXED_POINT_TYPE)
	  && (درەخت_CODE (درەخت_TYPE (orig_op1)) == INTEGER_TYPE
	      || درەخت_CODE (درەخت_TYPE (orig_op1)) == BITINT_TYPE))
	warn_for_div_by_zero (loc, op1);
      إذا (code == MEM_REF
	  && ret != دەربڕین
	  && درەخت_CODE (ret) == MEM_REF)
	{
	  درەخت_READONLY (ret) = درەخت_READONLY (دەربڕین);
	  درەخت_SIDE_EFFECTS (ret) = درەخت_SIDE_EFFECTS (دەربڕین);
	  درەخت_THIS_VOLATILE (ret) = درەخت_THIS_VOLATILE (دەربڕین);
	}
      اذهب out;

    حالة ADDR_دەربڕین:
      op0_lval = true;
      اذهب unary;
    حالة REALPART_دەربڕین:
    حالة IMAGPART_دەربڕین:
    حالة VIEW_CONVERT_دەربڕین:
      op0_lval = lval;
      /* FALLTHRU */
    حالة INDIRECT_REF:
    حالة FIX_TRUNC_دەربڕین:
    حالة FLOAT_دەربڕین:
    CASE_CONVERT:
    حالة ADDR_SPACE_CONVERT_دەربڕین:
    حالة NON_LVALUE_دەربڕین:
    حالة NEGATE_دەربڕین:
    حالة BIT_NOT_دەربڕین:
    حالة TRUTH_NOT_دەربڕین:
    حالة CONJ_دەربڕین:
    حالة PAREN_دەربڕین:
    unary:
      /* Unary operations.  */
      orig_op0 = op0 = درەخت_OPERAND (دەربڕین, 0);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const,
				   op0_lval);
      STRIP_TYPE_NOPS (op0);

      إذا (for_int_const && درەخت_CODE (op0) != INTEGER_CST)
	اذهب out;

      /* ??? Cope with user tricks that amount to offsetof.  The middle-end is
	 not prepared to deal with them if they occur in initializers.  */
      إذا (op0 != orig_op0
	  && code == ADDR_دەربڕین
	  && (op1 = get_base_address (op0)) != NULL_درەخت
	  && INDIRECT_REF_P (op1)
	  && درەخت_CONSTANT (درەخت_OPERAND (op1, 0)))
	ret = fold_offsetof (op0, درەخت_TYPE (دەربڕین));
      وإلا إذا (op0 != orig_op0 || in_init)
	ret = in_init
	  ? fold_build1_initializer_loc (loc, code, درەخت_TYPE (دەربڕین), op0)
	  : fold_build1_loc (loc, code, درەخت_TYPE (دەربڕین), op0);
      وإلا
	ret = fold (دەربڕین);
      إذا (code == INDIRECT_REF
	  && ret != دەربڕین
	  && INDIRECT_REF_P (ret))
	{
	  درەخت_READONLY (ret) = درەخت_READONLY (دەربڕین);
	  درەخت_SIDE_EFFECTS (ret) = درەخت_SIDE_EFFECTS (دەربڕین);
	  درەخت_THIS_VOLATILE (ret) = درەخت_THIS_VOLATILE (دەربڕین);
	}
      بدل (code)
	{
	حالة FIX_TRUNC_دەربڕین:
	حالة FLOAT_دەربڕین:
	CASE_CONVERT:
	  /* Don't warn about explicit conversions.  We will already
	     have warned about suspect implicit conversions.  */
	  اكسر;

	افتراضي:
	  إذا (درەخت_OVERFLOW_P (ret) && !درەخت_OVERFLOW_P (op0))
	    overflow_warning (دەربڕین_LOCATION (دەربڕین), ret, op0);
	  اكسر;
	}
      اذهب out;

    حالة TRUTH_ANDIF_دەربڕین:
    حالة TRUTH_ORIF_دەربڕین:
      /* Binary operations not necessarily evaluating both
	 arguments.  */
      orig_op0 = op0 = درەخت_OPERAND (دەربڕین, 0);
      orig_op1 = op1 = درەخت_OPERAND (دەربڕین, 1);
      op0 = c_fully_fold_internal (op0, in_init, &op0_const, &op0_const_self,
				   for_int_const, خطأ);
      STRIP_TYPE_NOPS (op0);

      unused_p = (op0 == (code == TRUTH_ANDIF_دەربڕین
			  ? truthvalue_false_گرێ
			  : truthvalue_true_گرێ));
      c_disable_warnings (unused_p);
      op1 = c_fully_fold_internal (op1, in_init, &op1_const, &op1_const_self,
				   for_int_const, خطأ);
      STRIP_TYPE_NOPS (op1);
      c_enable_warnings (unused_p);

      إذا (for_int_const
	  && (درەخت_CODE (op0) != INTEGER_CST
	      /* Require OP1 be an INTEGER_CST only if it's evaluated.  */
	      || (!unused_p && درەخت_CODE (op1) != INTEGER_CST)))
	اذهب out;

      إذا (op0 != orig_op0 || op1 != orig_op1 || in_init)
	ret = in_init
	  ? fold_build2_initializer_loc (loc, code, درەخت_TYPE (دەربڕین), op0, op1)
	  : fold_build2_loc (loc, code, درەخت_TYPE (دەربڕین), op0, op1);
      وإلا
	ret = fold (دەربڕین);
      *maybe_const_operands &= op0_const;
      *maybe_const_itself &= op0_const_self;
      إذا (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && (code == TRUTH_ANDIF_دەربڕین
		? op0 == truthvalue_false_گرێ
		: op0 == truthvalue_true_گرێ)))
	*maybe_const_operands &= op1_const;
      إذا (!(op0_const
	    && op0_const_self
	    && (code == TRUTH_ANDIF_دەربڕین
		? op0 == truthvalue_false_گرێ
		: op0 == truthvalue_true_گرێ)))
	*maybe_const_itself &= op1_const_self;
      اذهب out;

    حالة COND_دەربڕین:
      orig_op0 = op0 = درەخت_OPERAND (دەربڕین, 0);
      orig_op1 = op1 = درەخت_OPERAND (دەربڕین, 1);
      orig_op2 = op2 = درەخت_OPERAND (دەربڕین, 2);
      op0 = c_fully_fold_internal (op0, in_init, &op0_const, &op0_const_self,
				   for_int_const, خطأ);

      STRIP_TYPE_NOPS (op0);
      c_disable_warnings (op0 == truthvalue_false_گرێ);
      op1 = c_fully_fold_internal (op1, in_init, &op1_const, &op1_const_self,
				   for_int_const, خطأ);
      STRIP_TYPE_NOPS (op1);
      c_enable_warnings (op0 == truthvalue_false_گرێ);

      c_disable_warnings (op0 == truthvalue_true_گرێ);
      op2 = c_fully_fold_internal (op2, in_init, &op2_const, &op2_const_self,
				   for_int_const, خطأ);
      STRIP_TYPE_NOPS (op2);
      c_enable_warnings (op0 == truthvalue_true_گرێ);

      إذا (for_int_const
	  && (درەخت_CODE (op0) != INTEGER_CST
	      /* Only the evaluated operand must be an INTEGER_CST.  */
	      || (op0 == truthvalue_true_گرێ
		  ? درەخت_CODE (op1) != INTEGER_CST
		  : درەخت_CODE (op2) != INTEGER_CST)))
	اذهب out;

      إذا (op0 != orig_op0 || op1 != orig_op1 || op2 != orig_op2)
	ret = fold_build3_loc (loc, code, درەخت_TYPE (دەربڕین), op0, op1, op2);
      وإلا
	ret = fold (دەربڕین);
      *maybe_const_operands &= op0_const;
      *maybe_const_itself &= op0_const_self;
      إذا (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && op0 == truthvalue_false_گرێ))
	*maybe_const_operands &= op1_const;
      إذا (!(op0_const
	    && op0_const_self
	    && op0 == truthvalue_false_گرێ))
	*maybe_const_itself &= op1_const_self;
      إذا (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && op0 == truthvalue_true_گرێ))
	*maybe_const_operands &= op2_const;
      إذا (!(op0_const
	    && op0_const_self
	    && op0 == truthvalue_true_گرێ))
	*maybe_const_itself &= op2_const_self;
      اذهب out;

    حالة VEC_COND_دەربڕین:
      orig_op0 = op0 = درەخت_OPERAND (دەربڕین, 0);
      orig_op1 = op1 = درەخت_OPERAND (دەربڕین, 1);
      orig_op2 = op2 = درەخت_OPERAND (دەربڕین, 2);
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
	ret = fold_build3_loc (loc, code, درەخت_TYPE (دەربڕین), op0, op1, op2);
      وإلا
	ret = fold (دەربڕین);
      اذهب out;

    حالة EXCESS_PRECISION_دەربڕین:
      /* Each case where an operand with excess precision may be
	 encountered must remove the EXCESS_PRECISION_EXPR around
	 inner operands and possibly put one around the whole
	 expression or possibly convert to the semantic type (which
	 c_fully_fold does); we cannot tell at this stage which is
	 appropriate in any particular case.  */
      gcc_unreachable ();

    حالة SAVE_دەربڕین:
      /* Make sure to fold the contents of a SAVE_EXPR exactly once.  */
      op0 = درەخت_OPERAND (دەربڕین, 0);
      إذا (!SAVE_دەربڕین_FOLDED_P (دەربڕین))
	{
	  op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				       maybe_const_itself, for_int_const,
				       خطأ);
	  درەخت_OPERAND (دەربڕین, 0) = op0;
	  SAVE_دەربڕین_FOLDED_P (دەربڕین) = true;
	}
      /* Return the SAVE_EXPR operand if it is invariant.  */
      إذا (درەخت_invariant_p (op0))
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
	ret = build1 (NOP_دەربڕین, درەخت_TYPE (ret), ret);
      suppress_warning (ret, OPT_Woverflow);
    }
  إذا (ret != دەربڕین)
    {
      protected_set_دەربڕین_location (ret, loc);
      إذا (IS_دەربڕین_CODE_CLASS (kind))
	set_source_range (ret, old_range.m_start, old_range.m_finish);
    }
  أرجع ret;
}

/* Fold X for consideration by one of the warning functions when checking
   whether an expression has a constant value.  */

درەخت
fold_for_warn (درەخت x)
{
  /* The C front-end has already folded X appropriately.  */
  أرجع x;
}
