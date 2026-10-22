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

ایستا درخت c_fully_fold_internal (درخت عبارت, منطقی, منطقی *, منطقی *, منطقی,
				   منطقی);

/* If DISABLE is true, stop issuing warnings.  This is used when
   parsing code that we know will not be executed.  This function may
   be called multiple times, and works as a stack.  */

ایستا تهی
c_disable_warnings (منطقی disable)
{
  اگر (disable)
    {
      ++c_inhibit_evaluation_warnings;
    }
}

/* If ENABLE is true, re-enable issuing warnings.  */

ایستا تهی
c_enable_warnings (منطقی enable)
{
  اگر (enable)
    {
      --c_inhibit_evaluation_warnings;
    }
}

/* Try to fold ARRAY_REF ary[index] if possible and not handled by
   normal fold, return NULL_TREE otherwise.  */

ایستا درخت
c_fold_array_ref (درخت type, درخت ary, درخت index)
{
  اگر (درخت_CODE (ary) != STRING_CST
      || درخت_CODE (index) != INTEGER_CST
      || درخت_OVERFLOW (index)
      || درخت_CODE (درخت_TYPE (ary)) != ARRAY_TYPE
      || !درخت_fits_uhwi_p (index))
    بازگشت NULL_درخت;

  درخت elem_type = درخت_TYPE (درخت_TYPE (ary));
  unsigned elem_nchars = (TYPE_PRECISION (elem_type)
			  / TYPE_PRECISION (char_type_گره));
  unsigned len = (unsigned) درخت_STRING_LENGTH (ary) / elem_nchars;
  درخت nelts_minus_one = array_type_nelts_minus_one (درخت_TYPE (ary));
  منطقی dummy1 = درست, dummy2 = درست;
  nelts_minus_one = c_fully_fold_internal (nelts_minus_one, درست, &dummy1,
					   &dummy2, نادرست, نادرست);
  unsigned HOST_WIDE_INT i = درخت_to_uhwi (index);
  اگر (!درخت_int_cst_le (index, nelts_minus_one)
      || i >= len
      || i + elem_nchars > len)
    بازگشت NULL_درخت;

  اگر (elem_nchars == 1)
    بازگشت build_int_cst (type, درخت_STRING_POINTER (ary)[i]);

  ثابت unsigned نویسه *ptr
    = ((ثابت unsigned نویسه *)درخت_STRING_POINTER (ary) + i * elem_nchars);
  بازگشت native_interpret_عبارت (type, ptr, elem_nchars);
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
c_fully_fold (درخت عبارت, منطقی in_init, منطقی *maybe_const, منطقی lval)
{
  درخت ret;
  درخت eptype = NULL_درخت;
  منطقی dummy = درست;
  منطقی maybe_const_itself = درست;
  location_t loc = عبارت_LOCATION (عبارت);

  اگر (!maybe_const)
    maybe_const = &dummy;
  اگر (درخت_CODE (عبارت) == EXCESS_PRECISION_عبارت)
    {
      eptype = درخت_TYPE (عبارت);
      عبارت = درخت_OPERAND (عبارت, 0);
    }
  ret = c_fully_fold_internal (عبارت, in_init, maybe_const,
			       &maybe_const_itself, نادرست, lval);
  اگر (eptype)
    ret = fold_convert_loc (loc, eptype, ret);
  *maybe_const &= maybe_const_itself;
  بازگشت ret;
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

ایستا درخت
c_fully_fold_internal (درخت عبارت, منطقی in_init, منطقی *maybe_const_operands,
		       منطقی *maybe_const_itself, منطقی for_int_const, منطقی lval)
{
  درخت ret = عبارت;
  شمارش درخت_code code = درخت_CODE (عبارت);
  شمارش درخت_code_class kind = درخت_CODE_CLASS (code);
  location_t loc = عبارت_LOCATION (عبارت);
  درخت op0, op1, op2, op3;
  درخت orig_op0, orig_op1, orig_op2;
  منطقی op0_const = درست, op1_const = درست, op2_const = درست;
  منطقی op0_const_self = درست, op1_const_self = درست, op2_const_self = درست;
  منطقی nowarning = warning_suppressed_p (عبارت, OPT_Woverflow);
  منطقی unused_p;
  منطقی op0_lval = نادرست;
  source_range old_range;

  /* Constants, declarations, statements, errors, and anything else not
     counted as an expression cannot usefully be folded further at this
     point.  */
  اگر (!IS_عبارت_CODE_CLASS (kind) || kind == tcc_statement)
    {
      /* Except for variables which we can optimize to its initializer.  */
      اگر (VAR_P (عبارت) && !lval && (optimize || in_init))
	{
	  اگر (in_init)
	    ret = decl_constant_مقدار_1 (عبارت, درست);
	  وگرنه
	    {
	      ret = decl_constant_مقدار (عبارت);
	      اگر (ret != عبارت
		  && (TYPE_MODE (درخت_TYPE (ret)) == BLKmode
		      || درخت_CODE (درخت_TYPE (ret)) == ARRAY_TYPE))
		بازگشت عبارت;
	    }
	  /* Avoid unwanted tree sharing between the initializer and current
	     function's body where the tree can be modified e.g. by the
	     gimplifier.  */
	  اگر (ret != عبارت && درخت_STATIC (عبارت))
	    ret = unshare_عبارت (ret);
	  بازگشت ret;
	}
      بازگشت عبارت;
    }

  اگر (IS_عبارت_CODE_CLASS (kind))
    old_range = عبارت_LOCATION_RANGE (عبارت);

  /* Operands of variable-length expressions (function calls) have
     already been folded, as have __builtin_* function calls, and such
     expressions cannot occur in constant expressions.  */
  اگر (kind == tcc_vl_exp)
    {
      *maybe_const_operands = نادرست;
      ret = fold (عبارت);
      برو out;
    }

  اگر (code == C_MAYBE_CONST_عبارت)
    {
      درخت pre = C_MAYBE_CONST_عبارت_PRE (عبارت);
      درخت inner = C_MAYBE_CONST_عبارت_عبارت (عبارت);
      اگر (C_MAYBE_CONST_عبارت_NON_CONST (عبارت))
	*maybe_const_operands = نادرست;
      اگر (C_MAYBE_CONST_عبارت_INT_OPERANDS (عبارت))
	{
	  *maybe_const_itself = نادرست;
	  inner = c_fully_fold_internal (inner, in_init, maybe_const_operands,
					 maybe_const_itself, درست, lval);
	}
      اگر (pre && !in_init)
	ret = build2 (COMPOUND_عبارت, درخت_TYPE (عبارت), pre, inner);
      وگرنه
	ret = inner;
      برو out;
    }

  /* Assignment, increment, decrement, function call and comma
     operators, and statement expressions, cannot occur in constant
     expressions if evaluated / outside of sizeof.  (Function calls
     were handled above, though VA_ARG_EXPR is treated like a function
     call here, and statement expressions are handled through
     C_MAYBE_CONST_EXPR to avoid folding inside them.)  */
  انتخاب (code)
    {
    حالت MODIFY_عبارت:
    حالت PREDECREMENT_عبارت:
    حالت PREINCREMENT_عبارت:
    حالت POSTDECREMENT_عبارت:
    حالت POSTINCREMENT_عبارت:
    حالت COMPOUND_عبارت:
      *maybe_const_operands = نادرست;
      بشکن;

    حالت VA_ARG_عبارت:
    حالت TARGET_عبارت:
    حالت BIND_عبارت:
    حالت OBJ_TYPE_REF:
      *maybe_const_operands = نادرست;
      ret = fold (عبارت);
      برو out;

    پیشفرض:
      بشکن;
    }

  /* Fold individual tree codes as appropriate.  */
  انتخاب (code)
    {
    حالت COMPOUND_LITERAL_عبارت:
      /* Any non-constancy will have been marked in a containing
	 C_MAYBE_CONST_EXPR; there is no more folding to do here.  */
      برو out;

    حالت COMPONENT_REF:
      orig_op0 = op0 = درخت_OPERAND (عبارت, 0);
      op1 = درخت_OPERAND (عبارت, 1);
      op2 = درخت_OPERAND (عبارت, 2);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, lval);
      STRIP_TYPE_NOPS (op0);
      اگر (op0 != orig_op0)
	ret = build3 (COMPONENT_REF, درخت_TYPE (عبارت), op0, op1, op2);
      اگر (ret != عبارت)
	{
	  درخت_READONLY (ret) = درخت_READONLY (عبارت);
	  درخت_THIS_VOLATILE (ret) = درخت_THIS_VOLATILE (عبارت);
	}
      اگر (!lval)
	ret = fold (ret);
      برو out;

    حالت ARRAY_REF:
      orig_op0 = op0 = درخت_OPERAND (عبارت, 0);
      orig_op1 = op1 = درخت_OPERAND (عبارت, 1);
      op2 = درخت_OPERAND (عبارت, 2);
      op3 = درخت_OPERAND (عبارت, 3);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, lval);
      STRIP_TYPE_NOPS (op0);
      op1 = c_fully_fold_internal (op1, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, نادرست);
      STRIP_TYPE_NOPS (op1);
      /* Fold "foo"[2] in initializers.  */
      اگر (!lval && in_init)
	{
	  ret = c_fold_array_ref (درخت_TYPE (عبارت), op0, op1);
	  اگر (ret)
	    برو out;
	  ret = عبارت;
	}
      اگر (op0 != orig_op0 || op1 != orig_op1)
	ret = build4 (ARRAY_REF, درخت_TYPE (عبارت), op0, op1, op2, op3);
      اگر (ret != عبارت)
	{
	  درخت_READONLY (ret) = درخت_READONLY (عبارت);
	  درخت_SIDE_EFFECTS (ret) = درخت_SIDE_EFFECTS (عبارت);
	  درخت_THIS_VOLATILE (ret) = درخت_THIS_VOLATILE (عبارت);
	}
      اگر (!lval)
	ret = fold (ret);
      برو out;

    حالت MODIFY_عبارت:
    حالت PREDECREMENT_عبارت:
    حالت PREINCREMENT_عبارت:
    حالت POSTDECREMENT_عبارت:
    حالت POSTINCREMENT_عبارت:
      op0_lval = درست;
      /* FALLTHRU */
    حالت COMPOUND_عبارت:
    حالت PLUS_عبارت:
    حالت MINUS_عبارت:
    حالت MULT_عبارت:
    حالت POINTER_PLUS_عبارت:
    حالت POINTER_DIFF_عبارت:
    حالت TRUNC_DIV_عبارت:
    حالت CEIL_DIV_عبارت:
    حالت FLOOR_DIV_عبارت:
    حالت TRUNC_MOD_عبارت:
    حالت RDIV_عبارت:
    حالت EXACT_DIV_عبارت:
    حالت LSHIFT_عبارت:
    حالت RSHIFT_عبارت:
    حالت LROTATE_عبارت:
    حالت RROTATE_عبارت:
    حالت BIT_IOR_عبارت:
    حالت BIT_XOR_عبارت:
    حالت BIT_AND_عبارت:
    حالت LT_عبارت:
    حالت LE_عبارت:
    حالت GT_عبارت:
    حالت GE_عبارت:
    حالت EQ_عبارت:
    حالت NE_عبارت:
    حالت COMPLEX_عبارت:
    حالت TRUTH_AND_عبارت:
    حالت TRUTH_OR_عبارت:
    حالت TRUTH_XOR_عبارت:
    حالت UNORDERED_عبارت:
    حالت ORDERED_عبارت:
    حالت UNLT_عبارت:
    حالت UNLE_عبارت:
    حالت UNGT_عبارت:
    حالت UNGE_عبارت:
    حالت UNEQ_عبارت:
    حالت MEM_REF:
      /* Binary operations evaluating both arguments (increment and
	 decrement are binary internally in GCC).  */
      orig_op0 = op0 = درخت_OPERAND (عبارت, 0);
      orig_op1 = op1 = درخت_OPERAND (عبارت, 1);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const,
				   op0_lval);
      STRIP_TYPE_NOPS (op0);
      /* The RHS of a MODIFY_EXPR was fully folded when building that
	 expression for the sake of conversion warnings.  */
      اگر (code != MODIFY_عبارت)
	op1 = c_fully_fold_internal (op1, in_init, maybe_const_operands,
				     maybe_const_itself, for_int_const, نادرست);
      STRIP_TYPE_NOPS (op1);

      اگر (for_int_const && (درخت_CODE (op0) != INTEGER_CST
			    || درخت_CODE (op1) != INTEGER_CST))
	برو out;

      اگر (درخت_CODE_CLASS (code) == tcc_comparison
	  && درخت_CODE (درخت_TYPE (op0)) == NULLPTR_TYPE
	  && درخت_CODE (درخت_TYPE (op1)) == NULLPTR_TYPE)
	{
	  انتخاب (code)
	    {
	    حالت EQ_عبارت:
	      ret = constant_boolean_گره (درست, درخت_TYPE (عبارت));
	      بشکن;
	    حالت NE_عبارت:
	      ret = constant_boolean_گره (نادرست, درخت_TYPE (عبارت));
	      بشکن;
	    پیشفرض:
	      gcc_unreachable ();
	    }
	  ret = omit_two_operands_loc (loc, درخت_TYPE (عبارت), ret,
				       op0, op1);
	}
      وگرنه اگر (op0 != orig_op0 || op1 != orig_op1 || in_init)
	ret = in_init
	  ? fold_build2_initializer_loc (loc, code, درخت_TYPE (عبارت), op0, op1)
	  : fold_build2_loc (loc, code, درخت_TYPE (عبارت), op0, op1);
      وگرنه
	ret = fold (عبارت);
      اگر (درخت_OVERFLOW_P (ret)
	  && !درخت_OVERFLOW_P (op0)
	  && !(دودویی_CLASS_P (op0) && درخت_OVERFLOW_P (درخت_OPERAND (op0, 1)))
	  && !درخت_OVERFLOW_P (op1))
	overflow_warning (عبارت_LOC_OR_LOC (عبارت, درون_داد_location), ret, عبارت);
      اگر (code == LSHIFT_عبارت
	  && درخت_CODE (orig_op0) != INTEGER_CST
	  && (درخت_CODE (درخت_TYPE (orig_op0)) == INTEGER_TYPE
	      || درخت_CODE (درخت_TYPE (orig_op0)) == BITINT_TYPE)
	  && درخت_CODE (op0) == INTEGER_CST
	  && c_inhibit_evaluation_warnings == 0
	  && !TYPE_OVERFLOW_WRAPS (درخت_TYPE (orig_op0))
	  && درخت_int_cst_sgn (op0) < 0)
	warning_at (loc, OPT_Wshift_negative_مقدار,
		    "left shift of negative value");
      اگر ((code == LSHIFT_عبارت
	   || code == RSHIFT_عبارت
	   || code == LROTATE_عبارت
	   || code == RROTATE_عبارت)
	  && درخت_CODE (orig_op1) != INTEGER_CST
	  && درخت_CODE (op1) == INTEGER_CST
	  && درخت_CODE (درخت_TYPE (orig_op1)) == INTEGER_TYPE
	  && c_inhibit_evaluation_warnings == 0)
	{
	  اگر (درخت_int_cst_sgn (op1) < 0)
	    warning_at (loc, OPT_Wshift_شمار_negative,
			(code == LSHIFT_عبارت
			 ? G_("left shift count is negative")
			 : G_("right shift count is negative")));
	  وگرنه اگر ((درخت_CODE (درخت_TYPE (orig_op0)) == INTEGER_TYPE
		    || درخت_CODE (درخت_TYPE (orig_op0)) == BITINT_TYPE
		    || درخت_CODE (درخت_TYPE (orig_op0)) == FIXED_POINT_TYPE)
		   && compare_درخت_int (op1,
					TYPE_PRECISION (درخت_TYPE (orig_op0)))
		      >= 0
		   && !warning_suppressed_p (عبارت, OPT_Wshift_شمار_overflow))
	    warning_at (loc, OPT_Wshift_شمار_overflow,
			(code == LSHIFT_عبارت
			 ? G_("left shift count >= width of type")
			 : G_("right shift count >= width of type")));
	  وگرنه اگر (درخت_CODE (درخت_TYPE (orig_op0)) == VECTOR_TYPE
		   && compare_درخت_int (op1,
					TYPE_PRECISION (درخت_TYPE (درخت_TYPE (orig_op0))))
		      >= 0)
	    warning_at (loc, OPT_Wshift_شمار_overflow,
			code == LSHIFT_عبارت
			? G_("left shift count >= width of vector element")
			: G_("right shift count >= width of vector element"));
	}
      اگر (code == LSHIFT_عبارت
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
      اگر ((code == TRUNC_DIV_عبارت
	   || code == CEIL_DIV_عبارت
	   || code == FLOOR_DIV_عبارت
	   || code == EXACT_DIV_عبارت
	   || code == TRUNC_MOD_عبارت)
	  && درخت_CODE (orig_op1) != INTEGER_CST
	  && درخت_CODE (op1) == INTEGER_CST
	  && (درخت_CODE (درخت_TYPE (orig_op0)) == INTEGER_TYPE
	      || درخت_CODE (درخت_TYPE (orig_op0)) == BITINT_TYPE
	      || درخت_CODE (درخت_TYPE (orig_op0)) == FIXED_POINT_TYPE)
	  && (درخت_CODE (درخت_TYPE (orig_op1)) == INTEGER_TYPE
	      || درخت_CODE (درخت_TYPE (orig_op1)) == BITINT_TYPE))
	warn_for_div_by_zero (loc, op1);
      اگر (code == MEM_REF
	  && ret != عبارت
	  && درخت_CODE (ret) == MEM_REF)
	{
	  درخت_READONLY (ret) = درخت_READONLY (عبارت);
	  درخت_SIDE_EFFECTS (ret) = درخت_SIDE_EFFECTS (عبارت);
	  درخت_THIS_VOLATILE (ret) = درخت_THIS_VOLATILE (عبارت);
	}
      برو out;

    حالت ADDR_عبارت:
      op0_lval = درست;
      برو unary;
    حالت REALPART_عبارت:
    حالت IMAGPART_عبارت:
    حالت VIEW_CONVERT_عبارت:
      op0_lval = lval;
      /* FALLTHRU */
    حالت INDIRECT_REF:
    حالت FIX_TRUNC_عبارت:
    حالت FLOAT_عبارت:
    CASE_CONVERT:
    حالت ADDR_SPACE_CONVERT_عبارت:
    حالت NON_LVALUE_عبارت:
    حالت NEGATE_عبارت:
    حالت BIT_NOT_عبارت:
    حالت TRUTH_NOT_عبارت:
    حالت CONJ_عبارت:
    حالت PAREN_عبارت:
    unary:
      /* Unary operations.  */
      orig_op0 = op0 = درخت_OPERAND (عبارت, 0);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const,
				   op0_lval);
      STRIP_TYPE_NOPS (op0);

      اگر (for_int_const && درخت_CODE (op0) != INTEGER_CST)
	برو out;

      /* ??? Cope with user tricks that amount to offsetof.  The middle-end is
	 not prepared to deal with them if they occur in initializers.  */
      اگر (op0 != orig_op0
	  && code == ADDR_عبارت
	  && (op1 = get_base_address (op0)) != NULL_درخت
	  && INDIRECT_REF_P (op1)
	  && درخت_CONSTANT (درخت_OPERAND (op1, 0)))
	ret = fold_offsetof (op0, درخت_TYPE (عبارت));
      وگرنه اگر (op0 != orig_op0 || in_init)
	ret = in_init
	  ? fold_build1_initializer_loc (loc, code, درخت_TYPE (عبارت), op0)
	  : fold_build1_loc (loc, code, درخت_TYPE (عبارت), op0);
      وگرنه
	ret = fold (عبارت);
      اگر (code == INDIRECT_REF
	  && ret != عبارت
	  && INDIRECT_REF_P (ret))
	{
	  درخت_READONLY (ret) = درخت_READONLY (عبارت);
	  درخت_SIDE_EFFECTS (ret) = درخت_SIDE_EFFECTS (عبارت);
	  درخت_THIS_VOLATILE (ret) = درخت_THIS_VOLATILE (عبارت);
	}
      انتخاب (code)
	{
	حالت FIX_TRUNC_عبارت:
	حالت FLOAT_عبارت:
	CASE_CONVERT:
	  /* Don't warn about explicit conversions.  We will already
	     have warned about suspect implicit conversions.  */
	  بشکن;

	پیشفرض:
	  اگر (درخت_OVERFLOW_P (ret) && !درخت_OVERFLOW_P (op0))
	    overflow_warning (عبارت_LOCATION (عبارت), ret, op0);
	  بشکن;
	}
      برو out;

    حالت TRUTH_ANDIF_عبارت:
    حالت TRUTH_ORIF_عبارت:
      /* Binary operations not necessarily evaluating both
	 arguments.  */
      orig_op0 = op0 = درخت_OPERAND (عبارت, 0);
      orig_op1 = op1 = درخت_OPERAND (عبارت, 1);
      op0 = c_fully_fold_internal (op0, in_init, &op0_const, &op0_const_self,
				   for_int_const, نادرست);
      STRIP_TYPE_NOPS (op0);

      unused_p = (op0 == (code == TRUTH_ANDIF_عبارت
			  ? truthvalue_false_گره
			  : truthvalue_true_گره));
      c_disable_warnings (unused_p);
      op1 = c_fully_fold_internal (op1, in_init, &op1_const, &op1_const_self,
				   for_int_const, نادرست);
      STRIP_TYPE_NOPS (op1);
      c_enable_warnings (unused_p);

      اگر (for_int_const
	  && (درخت_CODE (op0) != INTEGER_CST
	      /* Require OP1 be an INTEGER_CST only if it's evaluated.  */
	      || (!unused_p && درخت_CODE (op1) != INTEGER_CST)))
	برو out;

      اگر (op0 != orig_op0 || op1 != orig_op1 || in_init)
	ret = in_init
	  ? fold_build2_initializer_loc (loc, code, درخت_TYPE (عبارت), op0, op1)
	  : fold_build2_loc (loc, code, درخت_TYPE (عبارت), op0, op1);
      وگرنه
	ret = fold (عبارت);
      *maybe_const_operands &= op0_const;
      *maybe_const_itself &= op0_const_self;
      اگر (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && (code == TRUTH_ANDIF_عبارت
		? op0 == truthvalue_false_گره
		: op0 == truthvalue_true_گره)))
	*maybe_const_operands &= op1_const;
      اگر (!(op0_const
	    && op0_const_self
	    && (code == TRUTH_ANDIF_عبارت
		? op0 == truthvalue_false_گره
		: op0 == truthvalue_true_گره)))
	*maybe_const_itself &= op1_const_self;
      برو out;

    حالت COND_عبارت:
      orig_op0 = op0 = درخت_OPERAND (عبارت, 0);
      orig_op1 = op1 = درخت_OPERAND (عبارت, 1);
      orig_op2 = op2 = درخت_OPERAND (عبارت, 2);
      op0 = c_fully_fold_internal (op0, in_init, &op0_const, &op0_const_self,
				   for_int_const, نادرست);

      STRIP_TYPE_NOPS (op0);
      c_disable_warnings (op0 == truthvalue_false_گره);
      op1 = c_fully_fold_internal (op1, in_init, &op1_const, &op1_const_self,
				   for_int_const, نادرست);
      STRIP_TYPE_NOPS (op1);
      c_enable_warnings (op0 == truthvalue_false_گره);

      c_disable_warnings (op0 == truthvalue_true_گره);
      op2 = c_fully_fold_internal (op2, in_init, &op2_const, &op2_const_self,
				   for_int_const, نادرست);
      STRIP_TYPE_NOPS (op2);
      c_enable_warnings (op0 == truthvalue_true_گره);

      اگر (for_int_const
	  && (درخت_CODE (op0) != INTEGER_CST
	      /* Only the evaluated operand must be an INTEGER_CST.  */
	      || (op0 == truthvalue_true_گره
		  ? درخت_CODE (op1) != INTEGER_CST
		  : درخت_CODE (op2) != INTEGER_CST)))
	برو out;

      اگر (op0 != orig_op0 || op1 != orig_op1 || op2 != orig_op2)
	ret = fold_build3_loc (loc, code, درخت_TYPE (عبارت), op0, op1, op2);
      وگرنه
	ret = fold (عبارت);
      *maybe_const_operands &= op0_const;
      *maybe_const_itself &= op0_const_self;
      اگر (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && op0 == truthvalue_false_گره))
	*maybe_const_operands &= op1_const;
      اگر (!(op0_const
	    && op0_const_self
	    && op0 == truthvalue_false_گره))
	*maybe_const_itself &= op1_const_self;
      اگر (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && op0 == truthvalue_true_گره))
	*maybe_const_operands &= op2_const;
      اگر (!(op0_const
	    && op0_const_self
	    && op0 == truthvalue_true_گره))
	*maybe_const_itself &= op2_const_self;
      برو out;

    حالت VEC_COND_عبارت:
      orig_op0 = op0 = درخت_OPERAND (عبارت, 0);
      orig_op1 = op1 = درخت_OPERAND (عبارت, 1);
      orig_op2 = op2 = درخت_OPERAND (عبارت, 2);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, نادرست);
      STRIP_TYPE_NOPS (op0);
      op1 = c_fully_fold_internal (op1, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, نادرست);
      STRIP_TYPE_NOPS (op1);
      op2 = c_fully_fold_internal (op2, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, نادرست);
      STRIP_TYPE_NOPS (op2);

      اگر (op0 != orig_op0 || op1 != orig_op1 || op2 != orig_op2)
	ret = fold_build3_loc (loc, code, درخت_TYPE (عبارت), op0, op1, op2);
      وگرنه
	ret = fold (عبارت);
      برو out;

    حالت EXCESS_PRECISION_عبارت:
      /* Each case where an operand with excess precision may be
	 encountered must remove the EXCESS_PRECISION_EXPR around
	 inner operands and possibly put one around the whole
	 expression or possibly convert to the semantic type (which
	 c_fully_fold does); we cannot tell at this stage which is
	 appropriate in any particular case.  */
      gcc_unreachable ();

    حالت SAVE_عبارت:
      /* Make sure to fold the contents of a SAVE_EXPR exactly once.  */
      op0 = درخت_OPERAND (عبارت, 0);
      اگر (!SAVE_عبارت_FOLDED_P (عبارت))
	{
	  op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				       maybe_const_itself, for_int_const,
				       نادرست);
	  درخت_OPERAND (عبارت, 0) = op0;
	  SAVE_عبارت_FOLDED_P (عبارت) = درست;
	}
      /* Return the SAVE_EXPR operand if it is invariant.  */
      اگر (درخت_invariant_p (op0))
	ret = op0;
      برو out;

    پیشفرض:
      /* Various codes may appear through folding built-in functions
	 and their arguments.  */
      برو out;
    }

 out:
  /* Some folding may introduce NON_LVALUE_EXPRs; all lvalue checks
     have been done by this point, so remove them again.  */
  nowarning |= warning_suppressed_p (ret, OPT_Woverflow);
  STRIP_TYPE_NOPS (ret);
  اگر (nowarning && !warning_suppressed_p (ret, OPT_Woverflow))
    {
      اگر (!CAN_HAVE_LOCATION_P (ret))
	ret = build1 (NOP_عبارت, درخت_TYPE (ret), ret);
      suppress_warning (ret, OPT_Woverflow);
    }
  اگر (ret != عبارت)
    {
      protected_set_عبارت_location (ret, loc);
      اگر (IS_عبارت_CODE_CLASS (kind))
	set_source_range (ret, old_range.m_start, old_range.m_finish);
    }
  بازگشت ret;
}

/* Fold X for consideration by one of the warning functions when checking
   whether an expression has a constant value.  */

درخت
fold_for_warn (درخت x)
{
  /* The C front-end has already folded X appropriately.  */
  بازگشت x;
}
