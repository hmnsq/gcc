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

ساكن شجرة c_fully_fold_internal (شجرة تعبير, منطقي, منطقي *, منطقي *, منطقي,
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

ساكن شجرة
c_fold_array_ref (شجرة type, شجرة ary, شجرة index)
{
  إذا (شجرة_CODE (ary) != STRING_CST
      || شجرة_CODE (index) != INTEGER_CST
      || شجرة_OVERFLOW (index)
      || شجرة_CODE (شجرة_TYPE (ary)) != ARRAY_TYPE
      || !شجرة_fits_uhwi_p (index))
    أرجع NULL_شجرة;

  شجرة elem_type = شجرة_TYPE (شجرة_TYPE (ary));
  unsigned elem_nchars = (TYPE_PRECISION (elem_type)
			  / TYPE_PRECISION (char_type_عقدة));
  unsigned len = (unsigned) شجرة_STRING_LENGTH (ary) / elem_nchars;
  شجرة nelts_minus_one = array_type_nelts_minus_one (شجرة_TYPE (ary));
  منطقي dummy1 = true, dummy2 = true;
  nelts_minus_one = c_fully_fold_internal (nelts_minus_one, true, &dummy1,
					   &dummy2, خطأ, خطأ);
  unsigned HOST_WIDE_INT i = شجرة_to_uhwi (index);
  إذا (!شجرة_int_cst_le (index, nelts_minus_one)
      || i >= len
      || i + elem_nchars > len)
    أرجع NULL_شجرة;

  إذا (elem_nchars == 1)
    أرجع build_int_cst (type, شجرة_STRING_POINTER (ary)[i]);

  ثابت unsigned حرف *ptr
    = ((ثابت unsigned حرف *)شجرة_STRING_POINTER (ary) + i * elem_nchars);
  أرجع native_interpret_تعبير (type, ptr, elem_nchars);
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

شجرة
c_fully_fold (شجرة تعبير, منطقي in_init, منطقي *maybe_const, منطقي lval)
{
  شجرة ret;
  شجرة eptype = NULL_شجرة;
  منطقي dummy = true;
  منطقي maybe_const_itself = true;
  location_t loc = تعبير_LOCATION (تعبير);

  إذا (!maybe_const)
    maybe_const = &dummy;
  إذا (شجرة_CODE (تعبير) == EXCESS_PRECISION_تعبير)
    {
      eptype = شجرة_TYPE (تعبير);
      تعبير = شجرة_OPERAND (تعبير, 0);
    }
  ret = c_fully_fold_internal (تعبير, in_init, maybe_const,
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

ساكن شجرة
c_fully_fold_internal (شجرة تعبير, منطقي in_init, منطقي *maybe_const_operands,
		       منطقي *maybe_const_itself, منطقي for_int_const, منطقي lval)
{
  شجرة ret = تعبير;
  تعداد شجرة_code code = شجرة_CODE (تعبير);
  تعداد شجرة_code_class kind = شجرة_CODE_CLASS (code);
  location_t loc = تعبير_LOCATION (تعبير);
  شجرة op0, op1, op2, op3;
  شجرة orig_op0, orig_op1, orig_op2;
  منطقي op0_const = true, op1_const = true, op2_const = true;
  منطقي op0_const_self = true, op1_const_self = true, op2_const_self = true;
  منطقي nowarning = warning_suppressed_p (تعبير, OPT_Woverflow);
  منطقي unused_p;
  منطقي op0_lval = خطأ;
  source_range old_range;

  /* Constants, declarations, statements, errors, and anything else not
     counted as an expression cannot usefully be folded further at this
     point.  */
  إذا (!IS_تعبير_CODE_CLASS (kind) || kind == tcc_statement)
    {
      /* Except for variables which we can optimize to its initializer.  */
      إذا (VAR_P (تعبير) && !lval && (optimize || in_init))
	{
	  إذا (in_init)
	    ret = decl_constant_قيمة_1 (تعبير, true);
	  وإلا
	    {
	      ret = decl_constant_قيمة (تعبير);
	      إذا (ret != تعبير
		  && (TYPE_MODE (شجرة_TYPE (ret)) == BLKmode
		      || شجرة_CODE (شجرة_TYPE (ret)) == ARRAY_TYPE))
		أرجع تعبير;
	    }
	  /* Avoid unwanted tree sharing between the initializer and current
	     function's body where the tree can be modified e.g. by the
	     gimplifier.  */
	  إذا (ret != تعبير && شجرة_STATIC (تعبير))
	    ret = unshare_تعبير (ret);
	  أرجع ret;
	}
      أرجع تعبير;
    }

  إذا (IS_تعبير_CODE_CLASS (kind))
    old_range = تعبير_LOCATION_RANGE (تعبير);

  /* Operands of variable-length expressions (function calls) have
     already been folded, as have __builtin_* function calls, and such
     expressions cannot occur in constant expressions.  */
  إذا (kind == tcc_vl_exp)
    {
      *maybe_const_operands = خطأ;
      ret = fold (تعبير);
      اذهب out;
    }

  إذا (code == C_MAYBE_CONST_تعبير)
    {
      شجرة pre = C_MAYBE_CONST_تعبير_PRE (تعبير);
      شجرة inner = C_MAYBE_CONST_تعبير_تعبير (تعبير);
      إذا (C_MAYBE_CONST_تعبير_NON_CONST (تعبير))
	*maybe_const_operands = خطأ;
      إذا (C_MAYBE_CONST_تعبير_INT_OPERANDS (تعبير))
	{
	  *maybe_const_itself = خطأ;
	  inner = c_fully_fold_internal (inner, in_init, maybe_const_operands,
					 maybe_const_itself, true, lval);
	}
      إذا (pre && !in_init)
	ret = build2 (COMPOUND_تعبير, شجرة_TYPE (تعبير), pre, inner);
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
    حالة MODIFY_تعبير:
    حالة PREDECREMENT_تعبير:
    حالة PREINCREMENT_تعبير:
    حالة POSTDECREMENT_تعبير:
    حالة POSTINCREMENT_تعبير:
    حالة COMPOUND_تعبير:
      *maybe_const_operands = خطأ;
      اكسر;

    حالة VA_ARG_تعبير:
    حالة TARGET_تعبير:
    حالة BIND_تعبير:
    حالة OBJ_TYPE_REF:
      *maybe_const_operands = خطأ;
      ret = fold (تعبير);
      اذهب out;

    افتراضي:
      اكسر;
    }

  /* Fold individual tree codes as appropriate.  */
  بدل (code)
    {
    حالة COMPOUND_LITERAL_تعبير:
      /* Any non-constancy will have been marked in a containing
	 C_MAYBE_CONST_EXPR; there is no more folding to do here.  */
      اذهب out;

    حالة COMPONENT_REF:
      orig_op0 = op0 = شجرة_OPERAND (تعبير, 0);
      op1 = شجرة_OPERAND (تعبير, 1);
      op2 = شجرة_OPERAND (تعبير, 2);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, lval);
      STRIP_TYPE_NOPS (op0);
      إذا (op0 != orig_op0)
	ret = build3 (COMPONENT_REF, شجرة_TYPE (تعبير), op0, op1, op2);
      إذا (ret != تعبير)
	{
	  شجرة_READONLY (ret) = شجرة_READONLY (تعبير);
	  شجرة_THIS_VOLATILE (ret) = شجرة_THIS_VOLATILE (تعبير);
	}
      إذا (!lval)
	ret = fold (ret);
      اذهب out;

    حالة ARRAY_REF:
      orig_op0 = op0 = شجرة_OPERAND (تعبير, 0);
      orig_op1 = op1 = شجرة_OPERAND (تعبير, 1);
      op2 = شجرة_OPERAND (تعبير, 2);
      op3 = شجرة_OPERAND (تعبير, 3);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, lval);
      STRIP_TYPE_NOPS (op0);
      op1 = c_fully_fold_internal (op1, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, خطأ);
      STRIP_TYPE_NOPS (op1);
      /* Fold "foo"[2] in initializers.  */
      إذا (!lval && in_init)
	{
	  ret = c_fold_array_ref (شجرة_TYPE (تعبير), op0, op1);
	  إذا (ret)
	    اذهب out;
	  ret = تعبير;
	}
      إذا (op0 != orig_op0 || op1 != orig_op1)
	ret = build4 (ARRAY_REF, شجرة_TYPE (تعبير), op0, op1, op2, op3);
      إذا (ret != تعبير)
	{
	  شجرة_READONLY (ret) = شجرة_READONLY (تعبير);
	  شجرة_SIDE_EFFECTS (ret) = شجرة_SIDE_EFFECTS (تعبير);
	  شجرة_THIS_VOLATILE (ret) = شجرة_THIS_VOLATILE (تعبير);
	}
      إذا (!lval)
	ret = fold (ret);
      اذهب out;

    حالة MODIFY_تعبير:
    حالة PREDECREMENT_تعبير:
    حالة PREINCREMENT_تعبير:
    حالة POSTDECREMENT_تعبير:
    حالة POSTINCREMENT_تعبير:
      op0_lval = true;
      /* FALLTHRU */
    حالة COMPOUND_تعبير:
    حالة PLUS_تعبير:
    حالة MINUS_تعبير:
    حالة MULT_تعبير:
    حالة POINTER_PLUS_تعبير:
    حالة POINTER_DIFF_تعبير:
    حالة TRUNC_DIV_تعبير:
    حالة CEIL_DIV_تعبير:
    حالة FLOOR_DIV_تعبير:
    حالة TRUNC_MOD_تعبير:
    حالة RDIV_تعبير:
    حالة EXACT_DIV_تعبير:
    حالة LSHIFT_تعبير:
    حالة RSHIFT_تعبير:
    حالة LROTATE_تعبير:
    حالة RROTATE_تعبير:
    حالة BIT_IOR_تعبير:
    حالة BIT_XOR_تعبير:
    حالة BIT_AND_تعبير:
    حالة LT_تعبير:
    حالة LE_تعبير:
    حالة GT_تعبير:
    حالة GE_تعبير:
    حالة EQ_تعبير:
    حالة NE_تعبير:
    حالة COMPLEX_تعبير:
    حالة TRUTH_AND_تعبير:
    حالة TRUTH_OR_تعبير:
    حالة TRUTH_XOR_تعبير:
    حالة UNORDERED_تعبير:
    حالة ORDERED_تعبير:
    حالة UNLT_تعبير:
    حالة UNLE_تعبير:
    حالة UNGT_تعبير:
    حالة UNGE_تعبير:
    حالة UNEQ_تعبير:
    حالة MEM_REF:
      /* Binary operations evaluating both arguments (increment and
	 decrement are binary internally in GCC).  */
      orig_op0 = op0 = شجرة_OPERAND (تعبير, 0);
      orig_op1 = op1 = شجرة_OPERAND (تعبير, 1);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const,
				   op0_lval);
      STRIP_TYPE_NOPS (op0);
      /* The RHS of a MODIFY_EXPR was fully folded when building that
	 expression for the sake of conversion warnings.  */
      إذا (code != MODIFY_تعبير)
	op1 = c_fully_fold_internal (op1, in_init, maybe_const_operands,
				     maybe_const_itself, for_int_const, خطأ);
      STRIP_TYPE_NOPS (op1);

      إذا (for_int_const && (شجرة_CODE (op0) != INTEGER_CST
			    || شجرة_CODE (op1) != INTEGER_CST))
	اذهب out;

      إذا (شجرة_CODE_CLASS (code) == tcc_comparison
	  && شجرة_CODE (شجرة_TYPE (op0)) == NULLPTR_TYPE
	  && شجرة_CODE (شجرة_TYPE (op1)) == NULLPTR_TYPE)
	{
	  بدل (code)
	    {
	    حالة EQ_تعبير:
	      ret = constant_boolean_عقدة (true, شجرة_TYPE (تعبير));
	      اكسر;
	    حالة NE_تعبير:
	      ret = constant_boolean_عقدة (خطأ, شجرة_TYPE (تعبير));
	      اكسر;
	    افتراضي:
	      gcc_unreachable ();
	    }
	  ret = omit_two_operands_loc (loc, شجرة_TYPE (تعبير), ret,
				       op0, op1);
	}
      وإلا إذا (op0 != orig_op0 || op1 != orig_op1 || in_init)
	ret = in_init
	  ? fold_build2_initializer_loc (loc, code, شجرة_TYPE (تعبير), op0, op1)
	  : fold_build2_loc (loc, code, شجرة_TYPE (تعبير), op0, op1);
      وإلا
	ret = fold (تعبير);
      إذا (شجرة_OVERFLOW_P (ret)
	  && !شجرة_OVERFLOW_P (op0)
	  && !(ثنائي_CLASS_P (op0) && شجرة_OVERFLOW_P (شجرة_OPERAND (op0, 1)))
	  && !شجرة_OVERFLOW_P (op1))
	overflow_warning (تعبير_LOC_OR_LOC (تعبير, مدخل_location), ret, تعبير);
      إذا (code == LSHIFT_تعبير
	  && شجرة_CODE (orig_op0) != INTEGER_CST
	  && (شجرة_CODE (شجرة_TYPE (orig_op0)) == INTEGER_TYPE
	      || شجرة_CODE (شجرة_TYPE (orig_op0)) == BITINT_TYPE)
	  && شجرة_CODE (op0) == INTEGER_CST
	  && c_inhibit_evaluation_warnings == 0
	  && !TYPE_OVERFLOW_WRAPS (شجرة_TYPE (orig_op0))
	  && شجرة_int_cst_sgn (op0) < 0)
	warning_at (loc, OPT_Wshift_negative_قيمة,
		    "left shift of negative value");
      إذا ((code == LSHIFT_تعبير
	   || code == RSHIFT_تعبير
	   || code == LROTATE_تعبير
	   || code == RROTATE_تعبير)
	  && شجرة_CODE (orig_op1) != INTEGER_CST
	  && شجرة_CODE (op1) == INTEGER_CST
	  && شجرة_CODE (شجرة_TYPE (orig_op1)) == INTEGER_TYPE
	  && c_inhibit_evaluation_warnings == 0)
	{
	  إذا (شجرة_int_cst_sgn (op1) < 0)
	    warning_at (loc, OPT_Wshift_عدد_negative,
			(code == LSHIFT_تعبير
			 ? G_("left shift count is negative")
			 : G_("right shift count is negative")));
	  وإلا إذا ((شجرة_CODE (شجرة_TYPE (orig_op0)) == INTEGER_TYPE
		    || شجرة_CODE (شجرة_TYPE (orig_op0)) == BITINT_TYPE
		    || شجرة_CODE (شجرة_TYPE (orig_op0)) == FIXED_POINT_TYPE)
		   && compare_شجرة_int (op1,
					TYPE_PRECISION (شجرة_TYPE (orig_op0)))
		      >= 0
		   && !warning_suppressed_p (تعبير, OPT_Wshift_عدد_overflow))
	    warning_at (loc, OPT_Wshift_عدد_overflow,
			(code == LSHIFT_تعبير
			 ? G_("left shift count >= width of type")
			 : G_("right shift count >= width of type")));
	  وإلا إذا (شجرة_CODE (شجرة_TYPE (orig_op0)) == VECTOR_TYPE
		   && compare_شجرة_int (op1,
					TYPE_PRECISION (شجرة_TYPE (شجرة_TYPE (orig_op0))))
		      >= 0)
	    warning_at (loc, OPT_Wshift_عدد_overflow,
			code == LSHIFT_تعبير
			? G_("left shift count >= width of vector element")
			: G_("right shift count >= width of vector element"));
	}
      إذا (code == LSHIFT_تعبير
	  /* If either OP0 has been folded to INTEGER_CST...  */
	  && ((شجرة_CODE (orig_op0) != INTEGER_CST
	       && (شجرة_CODE (شجرة_TYPE (orig_op0)) == INTEGER_TYPE
		   || شجرة_CODE (شجرة_TYPE (orig_op0)) == BITINT_TYPE)
	       && شجرة_CODE (op0) == INTEGER_CST)
	      /* ...or if OP1 has been folded to INTEGER_CST...  */
	      || (شجرة_CODE (orig_op1) != INTEGER_CST
		  && (شجرة_CODE (شجرة_TYPE (orig_op1)) == INTEGER_TYPE
		      || شجرة_CODE (شجرة_TYPE (orig_op1)) == BITINT_TYPE)
		  && شجرة_CODE (op1) == INTEGER_CST))
	  && c_inhibit_evaluation_warnings == 0)
	/* ...then maybe we can detect an overflow.  */
	maybe_warn_shift_overflow (loc, op0, op1);
      إذا ((code == TRUNC_DIV_تعبير
	   || code == CEIL_DIV_تعبير
	   || code == FLOOR_DIV_تعبير
	   || code == EXACT_DIV_تعبير
	   || code == TRUNC_MOD_تعبير)
	  && شجرة_CODE (orig_op1) != INTEGER_CST
	  && شجرة_CODE (op1) == INTEGER_CST
	  && (شجرة_CODE (شجرة_TYPE (orig_op0)) == INTEGER_TYPE
	      || شجرة_CODE (شجرة_TYPE (orig_op0)) == BITINT_TYPE
	      || شجرة_CODE (شجرة_TYPE (orig_op0)) == FIXED_POINT_TYPE)
	  && (شجرة_CODE (شجرة_TYPE (orig_op1)) == INTEGER_TYPE
	      || شجرة_CODE (شجرة_TYPE (orig_op1)) == BITINT_TYPE))
	warn_for_div_by_zero (loc, op1);
      إذا (code == MEM_REF
	  && ret != تعبير
	  && شجرة_CODE (ret) == MEM_REF)
	{
	  شجرة_READONLY (ret) = شجرة_READONLY (تعبير);
	  شجرة_SIDE_EFFECTS (ret) = شجرة_SIDE_EFFECTS (تعبير);
	  شجرة_THIS_VOLATILE (ret) = شجرة_THIS_VOLATILE (تعبير);
	}
      اذهب out;

    حالة ADDR_تعبير:
      op0_lval = true;
      اذهب unary;
    حالة REALPART_تعبير:
    حالة IMAGPART_تعبير:
    حالة VIEW_CONVERT_تعبير:
      op0_lval = lval;
      /* FALLTHRU */
    حالة INDIRECT_REF:
    حالة FIX_TRUNC_تعبير:
    حالة FLOAT_تعبير:
    CASE_CONVERT:
    حالة ADDR_SPACE_CONVERT_تعبير:
    حالة NON_LVALUE_تعبير:
    حالة NEGATE_تعبير:
    حالة BIT_NOT_تعبير:
    حالة TRUTH_NOT_تعبير:
    حالة CONJ_تعبير:
    حالة PAREN_تعبير:
    unary:
      /* Unary operations.  */
      orig_op0 = op0 = شجرة_OPERAND (تعبير, 0);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const,
				   op0_lval);
      STRIP_TYPE_NOPS (op0);

      إذا (for_int_const && شجرة_CODE (op0) != INTEGER_CST)
	اذهب out;

      /* ??? Cope with user tricks that amount to offsetof.  The middle-end is
	 not prepared to deal with them if they occur in initializers.  */
      إذا (op0 != orig_op0
	  && code == ADDR_تعبير
	  && (op1 = get_base_address (op0)) != NULL_شجرة
	  && INDIRECT_REF_P (op1)
	  && شجرة_CONSTANT (شجرة_OPERAND (op1, 0)))
	ret = fold_offsetof (op0, شجرة_TYPE (تعبير));
      وإلا إذا (op0 != orig_op0 || in_init)
	ret = in_init
	  ? fold_build1_initializer_loc (loc, code, شجرة_TYPE (تعبير), op0)
	  : fold_build1_loc (loc, code, شجرة_TYPE (تعبير), op0);
      وإلا
	ret = fold (تعبير);
      إذا (code == INDIRECT_REF
	  && ret != تعبير
	  && INDIRECT_REF_P (ret))
	{
	  شجرة_READONLY (ret) = شجرة_READONLY (تعبير);
	  شجرة_SIDE_EFFECTS (ret) = شجرة_SIDE_EFFECTS (تعبير);
	  شجرة_THIS_VOLATILE (ret) = شجرة_THIS_VOLATILE (تعبير);
	}
      بدل (code)
	{
	حالة FIX_TRUNC_تعبير:
	حالة FLOAT_تعبير:
	CASE_CONVERT:
	  /* Don't warn about explicit conversions.  We will already
	     have warned about suspect implicit conversions.  */
	  اكسر;

	افتراضي:
	  إذا (شجرة_OVERFLOW_P (ret) && !شجرة_OVERFLOW_P (op0))
	    overflow_warning (تعبير_LOCATION (تعبير), ret, op0);
	  اكسر;
	}
      اذهب out;

    حالة TRUTH_ANDIF_تعبير:
    حالة TRUTH_ORIF_تعبير:
      /* Binary operations not necessarily evaluating both
	 arguments.  */
      orig_op0 = op0 = شجرة_OPERAND (تعبير, 0);
      orig_op1 = op1 = شجرة_OPERAND (تعبير, 1);
      op0 = c_fully_fold_internal (op0, in_init, &op0_const, &op0_const_self,
				   for_int_const, خطأ);
      STRIP_TYPE_NOPS (op0);

      unused_p = (op0 == (code == TRUTH_ANDIF_تعبير
			  ? truthvalue_false_عقدة
			  : truthvalue_true_عقدة));
      c_disable_warnings (unused_p);
      op1 = c_fully_fold_internal (op1, in_init, &op1_const, &op1_const_self,
				   for_int_const, خطأ);
      STRIP_TYPE_NOPS (op1);
      c_enable_warnings (unused_p);

      إذا (for_int_const
	  && (شجرة_CODE (op0) != INTEGER_CST
	      /* Require OP1 be an INTEGER_CST only if it's evaluated.  */
	      || (!unused_p && شجرة_CODE (op1) != INTEGER_CST)))
	اذهب out;

      إذا (op0 != orig_op0 || op1 != orig_op1 || in_init)
	ret = in_init
	  ? fold_build2_initializer_loc (loc, code, شجرة_TYPE (تعبير), op0, op1)
	  : fold_build2_loc (loc, code, شجرة_TYPE (تعبير), op0, op1);
      وإلا
	ret = fold (تعبير);
      *maybe_const_operands &= op0_const;
      *maybe_const_itself &= op0_const_self;
      إذا (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && (code == TRUTH_ANDIF_تعبير
		? op0 == truthvalue_false_عقدة
		: op0 == truthvalue_true_عقدة)))
	*maybe_const_operands &= op1_const;
      إذا (!(op0_const
	    && op0_const_self
	    && (code == TRUTH_ANDIF_تعبير
		? op0 == truthvalue_false_عقدة
		: op0 == truthvalue_true_عقدة)))
	*maybe_const_itself &= op1_const_self;
      اذهب out;

    حالة COND_تعبير:
      orig_op0 = op0 = شجرة_OPERAND (تعبير, 0);
      orig_op1 = op1 = شجرة_OPERAND (تعبير, 1);
      orig_op2 = op2 = شجرة_OPERAND (تعبير, 2);
      op0 = c_fully_fold_internal (op0, in_init, &op0_const, &op0_const_self,
				   for_int_const, خطأ);

      STRIP_TYPE_NOPS (op0);
      c_disable_warnings (op0 == truthvalue_false_عقدة);
      op1 = c_fully_fold_internal (op1, in_init, &op1_const, &op1_const_self,
				   for_int_const, خطأ);
      STRIP_TYPE_NOPS (op1);
      c_enable_warnings (op0 == truthvalue_false_عقدة);

      c_disable_warnings (op0 == truthvalue_true_عقدة);
      op2 = c_fully_fold_internal (op2, in_init, &op2_const, &op2_const_self,
				   for_int_const, خطأ);
      STRIP_TYPE_NOPS (op2);
      c_enable_warnings (op0 == truthvalue_true_عقدة);

      إذا (for_int_const
	  && (شجرة_CODE (op0) != INTEGER_CST
	      /* Only the evaluated operand must be an INTEGER_CST.  */
	      || (op0 == truthvalue_true_عقدة
		  ? شجرة_CODE (op1) != INTEGER_CST
		  : شجرة_CODE (op2) != INTEGER_CST)))
	اذهب out;

      إذا (op0 != orig_op0 || op1 != orig_op1 || op2 != orig_op2)
	ret = fold_build3_loc (loc, code, شجرة_TYPE (تعبير), op0, op1, op2);
      وإلا
	ret = fold (تعبير);
      *maybe_const_operands &= op0_const;
      *maybe_const_itself &= op0_const_self;
      إذا (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && op0 == truthvalue_false_عقدة))
	*maybe_const_operands &= op1_const;
      إذا (!(op0_const
	    && op0_const_self
	    && op0 == truthvalue_false_عقدة))
	*maybe_const_itself &= op1_const_self;
      إذا (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && op0 == truthvalue_true_عقدة))
	*maybe_const_operands &= op2_const;
      إذا (!(op0_const
	    && op0_const_self
	    && op0 == truthvalue_true_عقدة))
	*maybe_const_itself &= op2_const_self;
      اذهب out;

    حالة VEC_COND_تعبير:
      orig_op0 = op0 = شجرة_OPERAND (تعبير, 0);
      orig_op1 = op1 = شجرة_OPERAND (تعبير, 1);
      orig_op2 = op2 = شجرة_OPERAND (تعبير, 2);
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
	ret = fold_build3_loc (loc, code, شجرة_TYPE (تعبير), op0, op1, op2);
      وإلا
	ret = fold (تعبير);
      اذهب out;

    حالة EXCESS_PRECISION_تعبير:
      /* Each case where an operand with excess precision may be
	 encountered must remove the EXCESS_PRECISION_EXPR around
	 inner operands and possibly put one around the whole
	 expression or possibly convert to the semantic type (which
	 c_fully_fold does); we cannot tell at this stage which is
	 appropriate in any particular case.  */
      gcc_unreachable ();

    حالة SAVE_تعبير:
      /* Make sure to fold the contents of a SAVE_EXPR exactly once.  */
      op0 = شجرة_OPERAND (تعبير, 0);
      إذا (!SAVE_تعبير_FOLDED_P (تعبير))
	{
	  op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				       maybe_const_itself, for_int_const,
				       خطأ);
	  شجرة_OPERAND (تعبير, 0) = op0;
	  SAVE_تعبير_FOLDED_P (تعبير) = true;
	}
      /* Return the SAVE_EXPR operand if it is invariant.  */
      إذا (شجرة_invariant_p (op0))
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
	ret = build1 (NOP_تعبير, شجرة_TYPE (ret), ret);
      suppress_warning (ret, OPT_Woverflow);
    }
  إذا (ret != تعبير)
    {
      protected_set_تعبير_location (ret, loc);
      إذا (IS_تعبير_CODE_CLASS (kind))
	set_source_range (ret, old_range.m_start, old_range.m_finish);
    }
  أرجع ret;
}

/* Fold X for consideration by one of the warning functions when checking
   whether an expression has a constant value.  */

شجرة
fold_for_warn (شجرة x)
{
  /* The C front-end has already folded X appropriately.  */
  أرجع x;
}
