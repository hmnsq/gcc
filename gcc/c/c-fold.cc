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

ساكن ڤوکوق c_fully_fold_internal (ڤوکوق اوڠکاڤن, منطقي, منطقي *, منطقي *, منطقي,
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

ساكن ڤوکوق
c_fold_array_ref (ڤوکوق type, ڤوکوق ary, ڤوکوق index)
{
  إذا (ڤوکوق_CODE (ary) != STRING_CST
      || ڤوکوق_CODE (index) != INTEGER_CST
      || ڤوکوق_OVERFLOW (index)
      || ڤوکوق_CODE (ڤوکوق_TYPE (ary)) != ARRAY_TYPE
      || !ڤوکوق_fits_uhwi_p (index))
    أرجع NULL_ڤوکوق;

  ڤوکوق elem_type = ڤوکوق_TYPE (ڤوکوق_TYPE (ary));
  unsigned elem_nchars = (TYPE_PRECISION (elem_type)
			  / TYPE_PRECISION (char_type_نود));
  unsigned len = (unsigned) ڤوکوق_STRING_LENGTH (ary) / elem_nchars;
  ڤوکوق nelts_minus_one = array_type_nelts_minus_one (ڤوکوق_TYPE (ary));
  منطقي dummy1 = true, dummy2 = true;
  nelts_minus_one = c_fully_fold_internal (nelts_minus_one, true, &dummy1,
					   &dummy2, خطأ, خطأ);
  unsigned HOST_WIDE_INT i = ڤوکوق_to_uhwi (index);
  إذا (!ڤوکوق_int_cst_le (index, nelts_minus_one)
      || i >= len
      || i + elem_nchars > len)
    أرجع NULL_ڤوکوق;

  إذا (elem_nchars == 1)
    أرجع build_int_cst (type, ڤوکوق_STRING_POINTER (ary)[i]);

  ثابت unsigned حرف *ptr
    = ((ثابت unsigned حرف *)ڤوکوق_STRING_POINTER (ary) + i * elem_nchars);
  أرجع native_interpret_اوڠکاڤن (type, ptr, elem_nchars);
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

ڤوکوق
c_fully_fold (ڤوکوق اوڠکاڤن, منطقي in_init, منطقي *maybe_const, منطقي lval)
{
  ڤوکوق ret;
  ڤوکوق eptype = NULL_ڤوکوق;
  منطقي dummy = true;
  منطقي maybe_const_itself = true;
  location_t loc = اوڠکاڤن_LOCATION (اوڠکاڤن);

  إذا (!maybe_const)
    maybe_const = &dummy;
  إذا (ڤوکوق_CODE (اوڠکاڤن) == EXCESS_PRECISION_اوڠکاڤن)
    {
      eptype = ڤوکوق_TYPE (اوڠکاڤن);
      اوڠکاڤن = ڤوکوق_OPERAND (اوڠکاڤن, 0);
    }
  ret = c_fully_fold_internal (اوڠکاڤن, in_init, maybe_const,
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

ساكن ڤوکوق
c_fully_fold_internal (ڤوکوق اوڠکاڤن, منطقي in_init, منطقي *maybe_const_operands,
		       منطقي *maybe_const_itself, منطقي for_int_const, منطقي lval)
{
  ڤوکوق ret = اوڠکاڤن;
  تعداد ڤوکوق_code code = ڤوکوق_CODE (اوڠکاڤن);
  تعداد ڤوکوق_code_class kind = ڤوکوق_CODE_CLASS (code);
  location_t loc = اوڠکاڤن_LOCATION (اوڠکاڤن);
  ڤوکوق op0, op1, op2, op3;
  ڤوکوق orig_op0, orig_op1, orig_op2;
  منطقي op0_const = true, op1_const = true, op2_const = true;
  منطقي op0_const_self = true, op1_const_self = true, op2_const_self = true;
  منطقي nowarning = warning_suppressed_p (اوڠکاڤن, OPT_Woverflow);
  منطقي unused_p;
  منطقي op0_lval = خطأ;
  source_range old_range;

  /* Constants, declarations, statements, errors, and anything else not
     counted as an expression cannot usefully be folded further at this
     point.  */
  إذا (!IS_اوڠکاڤن_CODE_CLASS (kind) || kind == tcc_statement)
    {
      /* Except for variables which we can optimize to its initializer.  */
      إذا (VAR_P (اوڠکاڤن) && !lval && (optimize || in_init))
	{
	  إذا (in_init)
	    ret = decl_constant_نيلاي_1 (اوڠکاڤن, true);
	  وإلا
	    {
	      ret = decl_constant_نيلاي (اوڠکاڤن);
	      إذا (ret != اوڠکاڤن
		  && (TYPE_MODE (ڤوکوق_TYPE (ret)) == BLKmode
		      || ڤوکوق_CODE (ڤوکوق_TYPE (ret)) == ARRAY_TYPE))
		أرجع اوڠکاڤن;
	    }
	  /* Avoid unwanted tree sharing between the initializer and current
	     function's body where the tree can be modified e.g. by the
	     gimplifier.  */
	  إذا (ret != اوڠکاڤن && ڤوکوق_STATIC (اوڠکاڤن))
	    ret = unshare_اوڠکاڤن (ret);
	  أرجع ret;
	}
      أرجع اوڠکاڤن;
    }

  إذا (IS_اوڠکاڤن_CODE_CLASS (kind))
    old_range = اوڠکاڤن_LOCATION_RANGE (اوڠکاڤن);

  /* Operands of variable-length expressions (function calls) have
     already been folded, as have __builtin_* function calls, and such
     expressions cannot occur in constant expressions.  */
  إذا (kind == tcc_vl_exp)
    {
      *maybe_const_operands = خطأ;
      ret = fold (اوڠکاڤن);
      اذهب out;
    }

  إذا (code == C_MAYBE_CONST_اوڠکاڤن)
    {
      ڤوکوق pre = C_MAYBE_CONST_اوڠکاڤن_PRE (اوڠکاڤن);
      ڤوکوق inner = C_MAYBE_CONST_اوڠکاڤن_اوڠکاڤن (اوڠکاڤن);
      إذا (C_MAYBE_CONST_اوڠکاڤن_NON_CONST (اوڠکاڤن))
	*maybe_const_operands = خطأ;
      إذا (C_MAYBE_CONST_اوڠکاڤن_INT_OPERANDS (اوڠکاڤن))
	{
	  *maybe_const_itself = خطأ;
	  inner = c_fully_fold_internal (inner, in_init, maybe_const_operands,
					 maybe_const_itself, true, lval);
	}
      إذا (pre && !in_init)
	ret = build2 (COMPOUND_اوڠکاڤن, ڤوکوق_TYPE (اوڠکاڤن), pre, inner);
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
    حالة MODIFY_اوڠکاڤن:
    حالة PREDECREMENT_اوڠکاڤن:
    حالة PREINCREMENT_اوڠکاڤن:
    حالة POSTDECREMENT_اوڠکاڤن:
    حالة POSTINCREMENT_اوڠکاڤن:
    حالة COMPOUND_اوڠکاڤن:
      *maybe_const_operands = خطأ;
      اكسر;

    حالة VA_ARG_اوڠکاڤن:
    حالة TARGET_اوڠکاڤن:
    حالة BIND_اوڠکاڤن:
    حالة OBJ_TYPE_REF:
      *maybe_const_operands = خطأ;
      ret = fold (اوڠکاڤن);
      اذهب out;

    افتراضي:
      اكسر;
    }

  /* Fold individual tree codes as appropriate.  */
  بدل (code)
    {
    حالة COMPOUND_LITERAL_اوڠکاڤن:
      /* Any non-constancy will have been marked in a containing
	 C_MAYBE_CONST_EXPR; there is no more folding to do here.  */
      اذهب out;

    حالة COMPONENT_REF:
      orig_op0 = op0 = ڤوکوق_OPERAND (اوڠکاڤن, 0);
      op1 = ڤوکوق_OPERAND (اوڠکاڤن, 1);
      op2 = ڤوکوق_OPERAND (اوڠکاڤن, 2);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, lval);
      STRIP_TYPE_NOPS (op0);
      إذا (op0 != orig_op0)
	ret = build3 (COMPONENT_REF, ڤوکوق_TYPE (اوڠکاڤن), op0, op1, op2);
      إذا (ret != اوڠکاڤن)
	{
	  ڤوکوق_READONLY (ret) = ڤوکوق_READONLY (اوڠکاڤن);
	  ڤوکوق_THIS_VOLATILE (ret) = ڤوکوق_THIS_VOLATILE (اوڠکاڤن);
	}
      إذا (!lval)
	ret = fold (ret);
      اذهب out;

    حالة ARRAY_REF:
      orig_op0 = op0 = ڤوکوق_OPERAND (اوڠکاڤن, 0);
      orig_op1 = op1 = ڤوکوق_OPERAND (اوڠکاڤن, 1);
      op2 = ڤوکوق_OPERAND (اوڠکاڤن, 2);
      op3 = ڤوکوق_OPERAND (اوڠکاڤن, 3);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, lval);
      STRIP_TYPE_NOPS (op0);
      op1 = c_fully_fold_internal (op1, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, خطأ);
      STRIP_TYPE_NOPS (op1);
      /* Fold "foo"[2] in initializers.  */
      إذا (!lval && in_init)
	{
	  ret = c_fold_array_ref (ڤوکوق_TYPE (اوڠکاڤن), op0, op1);
	  إذا (ret)
	    اذهب out;
	  ret = اوڠکاڤن;
	}
      إذا (op0 != orig_op0 || op1 != orig_op1)
	ret = build4 (ARRAY_REF, ڤوکوق_TYPE (اوڠکاڤن), op0, op1, op2, op3);
      إذا (ret != اوڠکاڤن)
	{
	  ڤوکوق_READONLY (ret) = ڤوکوق_READONLY (اوڠکاڤن);
	  ڤوکوق_SIDE_EFFECTS (ret) = ڤوکوق_SIDE_EFFECTS (اوڠکاڤن);
	  ڤوکوق_THIS_VOLATILE (ret) = ڤوکوق_THIS_VOLATILE (اوڠکاڤن);
	}
      إذا (!lval)
	ret = fold (ret);
      اذهب out;

    حالة MODIFY_اوڠکاڤن:
    حالة PREDECREMENT_اوڠکاڤن:
    حالة PREINCREMENT_اوڠکاڤن:
    حالة POSTDECREMENT_اوڠکاڤن:
    حالة POSTINCREMENT_اوڠکاڤن:
      op0_lval = true;
      /* FALLTHRU */
    حالة COMPOUND_اوڠکاڤن:
    حالة PLUS_اوڠکاڤن:
    حالة MINUS_اوڠکاڤن:
    حالة MULT_اوڠکاڤن:
    حالة POINTER_PLUS_اوڠکاڤن:
    حالة POINTER_DIFF_اوڠکاڤن:
    حالة TRUNC_DIV_اوڠکاڤن:
    حالة CEIL_DIV_اوڠکاڤن:
    حالة FLOOR_DIV_اوڠکاڤن:
    حالة TRUNC_MOD_اوڠکاڤن:
    حالة RDIV_اوڠکاڤن:
    حالة EXACT_DIV_اوڠکاڤن:
    حالة LSHIFT_اوڠکاڤن:
    حالة RSHIFT_اوڠکاڤن:
    حالة LROTATE_اوڠکاڤن:
    حالة RROTATE_اوڠکاڤن:
    حالة BIT_IOR_اوڠکاڤن:
    حالة BIT_XOR_اوڠکاڤن:
    حالة BIT_AND_اوڠکاڤن:
    حالة LT_اوڠکاڤن:
    حالة LE_اوڠکاڤن:
    حالة GT_اوڠکاڤن:
    حالة GE_اوڠکاڤن:
    حالة EQ_اوڠکاڤن:
    حالة NE_اوڠکاڤن:
    حالة COMPLEX_اوڠکاڤن:
    حالة TRUTH_AND_اوڠکاڤن:
    حالة TRUTH_OR_اوڠکاڤن:
    حالة TRUTH_XOR_اوڠکاڤن:
    حالة UNORDERED_اوڠکاڤن:
    حالة ORDERED_اوڠکاڤن:
    حالة UNLT_اوڠکاڤن:
    حالة UNLE_اوڠکاڤن:
    حالة UNGT_اوڠکاڤن:
    حالة UNGE_اوڠکاڤن:
    حالة UNEQ_اوڠکاڤن:
    حالة MEM_REF:
      /* Binary operations evaluating both arguments (increment and
	 decrement are binary internally in GCC).  */
      orig_op0 = op0 = ڤوکوق_OPERAND (اوڠکاڤن, 0);
      orig_op1 = op1 = ڤوکوق_OPERAND (اوڠکاڤن, 1);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const,
				   op0_lval);
      STRIP_TYPE_NOPS (op0);
      /* The RHS of a MODIFY_EXPR was fully folded when building that
	 expression for the sake of conversion warnings.  */
      إذا (code != MODIFY_اوڠکاڤن)
	op1 = c_fully_fold_internal (op1, in_init, maybe_const_operands,
				     maybe_const_itself, for_int_const, خطأ);
      STRIP_TYPE_NOPS (op1);

      إذا (for_int_const && (ڤوکوق_CODE (op0) != INTEGER_CST
			    || ڤوکوق_CODE (op1) != INTEGER_CST))
	اذهب out;

      إذا (ڤوکوق_CODE_CLASS (code) == tcc_comparison
	  && ڤوکوق_CODE (ڤوکوق_TYPE (op0)) == NULLPTR_TYPE
	  && ڤوکوق_CODE (ڤوکوق_TYPE (op1)) == NULLPTR_TYPE)
	{
	  بدل (code)
	    {
	    حالة EQ_اوڠکاڤن:
	      ret = constant_boolean_نود (true, ڤوکوق_TYPE (اوڠکاڤن));
	      اكسر;
	    حالة NE_اوڠکاڤن:
	      ret = constant_boolean_نود (خطأ, ڤوکوق_TYPE (اوڠکاڤن));
	      اكسر;
	    افتراضي:
	      gcc_unreachable ();
	    }
	  ret = omit_two_operands_loc (loc, ڤوکوق_TYPE (اوڠکاڤن), ret,
				       op0, op1);
	}
      وإلا إذا (op0 != orig_op0 || op1 != orig_op1 || in_init)
	ret = in_init
	  ? fold_build2_initializer_loc (loc, code, ڤوکوق_TYPE (اوڠکاڤن), op0, op1)
	  : fold_build2_loc (loc, code, ڤوکوق_TYPE (اوڠکاڤن), op0, op1);
      وإلا
	ret = fold (اوڠکاڤن);
      إذا (ڤوکوق_OVERFLOW_P (ret)
	  && !ڤوکوق_OVERFLOW_P (op0)
	  && !(بيناري_CLASS_P (op0) && ڤوکوق_OVERFLOW_P (ڤوکوق_OPERAND (op0, 1)))
	  && !ڤوکوق_OVERFLOW_P (op1))
	overflow_warning (اوڠکاڤن_LOC_OR_LOC (اوڠکاڤن, ماسوقن_location), ret, اوڠکاڤن);
      إذا (code == LSHIFT_اوڠکاڤن
	  && ڤوکوق_CODE (orig_op0) != INTEGER_CST
	  && (ڤوکوق_CODE (ڤوکوق_TYPE (orig_op0)) == INTEGER_TYPE
	      || ڤوکوق_CODE (ڤوکوق_TYPE (orig_op0)) == BITINT_TYPE)
	  && ڤوکوق_CODE (op0) == INTEGER_CST
	  && c_inhibit_evaluation_warnings == 0
	  && !TYPE_OVERFLOW_WRAPS (ڤوکوق_TYPE (orig_op0))
	  && ڤوکوق_int_cst_sgn (op0) < 0)
	warning_at (loc, OPT_Wshift_negative_نيلاي,
		    "left shift of negative value");
      إذا ((code == LSHIFT_اوڠکاڤن
	   || code == RSHIFT_اوڠکاڤن
	   || code == LROTATE_اوڠکاڤن
	   || code == RROTATE_اوڠکاڤن)
	  && ڤوکوق_CODE (orig_op1) != INTEGER_CST
	  && ڤوکوق_CODE (op1) == INTEGER_CST
	  && ڤوکوق_CODE (ڤوکوق_TYPE (orig_op1)) == INTEGER_TYPE
	  && c_inhibit_evaluation_warnings == 0)
	{
	  إذا (ڤوکوق_int_cst_sgn (op1) < 0)
	    warning_at (loc, OPT_Wshift_کيراءن_negative,
			(code == LSHIFT_اوڠکاڤن
			 ? G_("left shift count is negative")
			 : G_("right shift count is negative")));
	  وإلا إذا ((ڤوکوق_CODE (ڤوکوق_TYPE (orig_op0)) == INTEGER_TYPE
		    || ڤوکوق_CODE (ڤوکوق_TYPE (orig_op0)) == BITINT_TYPE
		    || ڤوکوق_CODE (ڤوکوق_TYPE (orig_op0)) == FIXED_POINT_TYPE)
		   && compare_ڤوکوق_int (op1,
					TYPE_PRECISION (ڤوکوق_TYPE (orig_op0)))
		      >= 0
		   && !warning_suppressed_p (اوڠکاڤن, OPT_Wshift_کيراءن_overflow))
	    warning_at (loc, OPT_Wshift_کيراءن_overflow,
			(code == LSHIFT_اوڠکاڤن
			 ? G_("left shift count >= width of type")
			 : G_("right shift count >= width of type")));
	  وإلا إذا (ڤوکوق_CODE (ڤوکوق_TYPE (orig_op0)) == VECTOR_TYPE
		   && compare_ڤوکوق_int (op1,
					TYPE_PRECISION (ڤوکوق_TYPE (ڤوکوق_TYPE (orig_op0))))
		      >= 0)
	    warning_at (loc, OPT_Wshift_کيراءن_overflow,
			code == LSHIFT_اوڠکاڤن
			? G_("left shift count >= width of vector element")
			: G_("right shift count >= width of vector element"));
	}
      إذا (code == LSHIFT_اوڠکاڤن
	  /* If either OP0 has been folded to INTEGER_CST...  */
	  && ((ڤوکوق_CODE (orig_op0) != INTEGER_CST
	       && (ڤوکوق_CODE (ڤوکوق_TYPE (orig_op0)) == INTEGER_TYPE
		   || ڤوکوق_CODE (ڤوکوق_TYPE (orig_op0)) == BITINT_TYPE)
	       && ڤوکوق_CODE (op0) == INTEGER_CST)
	      /* ...or if OP1 has been folded to INTEGER_CST...  */
	      || (ڤوکوق_CODE (orig_op1) != INTEGER_CST
		  && (ڤوکوق_CODE (ڤوکوق_TYPE (orig_op1)) == INTEGER_TYPE
		      || ڤوکوق_CODE (ڤوکوق_TYPE (orig_op1)) == BITINT_TYPE)
		  && ڤوکوق_CODE (op1) == INTEGER_CST))
	  && c_inhibit_evaluation_warnings == 0)
	/* ...then maybe we can detect an overflow.  */
	maybe_warn_shift_overflow (loc, op0, op1);
      إذا ((code == TRUNC_DIV_اوڠکاڤن
	   || code == CEIL_DIV_اوڠکاڤن
	   || code == FLOOR_DIV_اوڠکاڤن
	   || code == EXACT_DIV_اوڠکاڤن
	   || code == TRUNC_MOD_اوڠکاڤن)
	  && ڤوکوق_CODE (orig_op1) != INTEGER_CST
	  && ڤوکوق_CODE (op1) == INTEGER_CST
	  && (ڤوکوق_CODE (ڤوکوق_TYPE (orig_op0)) == INTEGER_TYPE
	      || ڤوکوق_CODE (ڤوکوق_TYPE (orig_op0)) == BITINT_TYPE
	      || ڤوکوق_CODE (ڤوکوق_TYPE (orig_op0)) == FIXED_POINT_TYPE)
	  && (ڤوکوق_CODE (ڤوکوق_TYPE (orig_op1)) == INTEGER_TYPE
	      || ڤوکوق_CODE (ڤوکوق_TYPE (orig_op1)) == BITINT_TYPE))
	warn_for_div_by_zero (loc, op1);
      إذا (code == MEM_REF
	  && ret != اوڠکاڤن
	  && ڤوکوق_CODE (ret) == MEM_REF)
	{
	  ڤوکوق_READONLY (ret) = ڤوکوق_READONLY (اوڠکاڤن);
	  ڤوکوق_SIDE_EFFECTS (ret) = ڤوکوق_SIDE_EFFECTS (اوڠکاڤن);
	  ڤوکوق_THIS_VOLATILE (ret) = ڤوکوق_THIS_VOLATILE (اوڠکاڤن);
	}
      اذهب out;

    حالة ADDR_اوڠکاڤن:
      op0_lval = true;
      اذهب unary;
    حالة REALPART_اوڠکاڤن:
    حالة IMAGPART_اوڠکاڤن:
    حالة VIEW_CONVERT_اوڠکاڤن:
      op0_lval = lval;
      /* FALLTHRU */
    حالة INDIRECT_REF:
    حالة FIX_TRUNC_اوڠکاڤن:
    حالة FLOAT_اوڠکاڤن:
    CASE_CONVERT:
    حالة ADDR_SPACE_CONVERT_اوڠکاڤن:
    حالة NON_LVALUE_اوڠکاڤن:
    حالة NEGATE_اوڠکاڤن:
    حالة BIT_NOT_اوڠکاڤن:
    حالة TRUTH_NOT_اوڠکاڤن:
    حالة CONJ_اوڠکاڤن:
    حالة PAREN_اوڠکاڤن:
    unary:
      /* Unary operations.  */
      orig_op0 = op0 = ڤوکوق_OPERAND (اوڠکاڤن, 0);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const,
				   op0_lval);
      STRIP_TYPE_NOPS (op0);

      إذا (for_int_const && ڤوکوق_CODE (op0) != INTEGER_CST)
	اذهب out;

      /* ??? Cope with user tricks that amount to offsetof.  The middle-end is
	 not prepared to deal with them if they occur in initializers.  */
      إذا (op0 != orig_op0
	  && code == ADDR_اوڠکاڤن
	  && (op1 = get_base_address (op0)) != NULL_ڤوکوق
	  && INDIRECT_REF_P (op1)
	  && ڤوکوق_CONSTANT (ڤوکوق_OPERAND (op1, 0)))
	ret = fold_offsetof (op0, ڤوکوق_TYPE (اوڠکاڤن));
      وإلا إذا (op0 != orig_op0 || in_init)
	ret = in_init
	  ? fold_build1_initializer_loc (loc, code, ڤوکوق_TYPE (اوڠکاڤن), op0)
	  : fold_build1_loc (loc, code, ڤوکوق_TYPE (اوڠکاڤن), op0);
      وإلا
	ret = fold (اوڠکاڤن);
      إذا (code == INDIRECT_REF
	  && ret != اوڠکاڤن
	  && INDIRECT_REF_P (ret))
	{
	  ڤوکوق_READONLY (ret) = ڤوکوق_READONLY (اوڠکاڤن);
	  ڤوکوق_SIDE_EFFECTS (ret) = ڤوکوق_SIDE_EFFECTS (اوڠکاڤن);
	  ڤوکوق_THIS_VOLATILE (ret) = ڤوکوق_THIS_VOLATILE (اوڠکاڤن);
	}
      بدل (code)
	{
	حالة FIX_TRUNC_اوڠکاڤن:
	حالة FLOAT_اوڠکاڤن:
	CASE_CONVERT:
	  /* Don't warn about explicit conversions.  We will already
	     have warned about suspect implicit conversions.  */
	  اكسر;

	افتراضي:
	  إذا (ڤوکوق_OVERFLOW_P (ret) && !ڤوکوق_OVERFLOW_P (op0))
	    overflow_warning (اوڠکاڤن_LOCATION (اوڠکاڤن), ret, op0);
	  اكسر;
	}
      اذهب out;

    حالة TRUTH_ANDIF_اوڠکاڤن:
    حالة TRUTH_ORIF_اوڠکاڤن:
      /* Binary operations not necessarily evaluating both
	 arguments.  */
      orig_op0 = op0 = ڤوکوق_OPERAND (اوڠکاڤن, 0);
      orig_op1 = op1 = ڤوکوق_OPERAND (اوڠکاڤن, 1);
      op0 = c_fully_fold_internal (op0, in_init, &op0_const, &op0_const_self,
				   for_int_const, خطأ);
      STRIP_TYPE_NOPS (op0);

      unused_p = (op0 == (code == TRUTH_ANDIF_اوڠکاڤن
			  ? truthvalue_false_نود
			  : truthvalue_true_نود));
      c_disable_warnings (unused_p);
      op1 = c_fully_fold_internal (op1, in_init, &op1_const, &op1_const_self,
				   for_int_const, خطأ);
      STRIP_TYPE_NOPS (op1);
      c_enable_warnings (unused_p);

      إذا (for_int_const
	  && (ڤوکوق_CODE (op0) != INTEGER_CST
	      /* Require OP1 be an INTEGER_CST only if it's evaluated.  */
	      || (!unused_p && ڤوکوق_CODE (op1) != INTEGER_CST)))
	اذهب out;

      إذا (op0 != orig_op0 || op1 != orig_op1 || in_init)
	ret = in_init
	  ? fold_build2_initializer_loc (loc, code, ڤوکوق_TYPE (اوڠکاڤن), op0, op1)
	  : fold_build2_loc (loc, code, ڤوکوق_TYPE (اوڠکاڤن), op0, op1);
      وإلا
	ret = fold (اوڠکاڤن);
      *maybe_const_operands &= op0_const;
      *maybe_const_itself &= op0_const_self;
      إذا (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && (code == TRUTH_ANDIF_اوڠکاڤن
		? op0 == truthvalue_false_نود
		: op0 == truthvalue_true_نود)))
	*maybe_const_operands &= op1_const;
      إذا (!(op0_const
	    && op0_const_self
	    && (code == TRUTH_ANDIF_اوڠکاڤن
		? op0 == truthvalue_false_نود
		: op0 == truthvalue_true_نود)))
	*maybe_const_itself &= op1_const_self;
      اذهب out;

    حالة COND_اوڠکاڤن:
      orig_op0 = op0 = ڤوکوق_OPERAND (اوڠکاڤن, 0);
      orig_op1 = op1 = ڤوکوق_OPERAND (اوڠکاڤن, 1);
      orig_op2 = op2 = ڤوکوق_OPERAND (اوڠکاڤن, 2);
      op0 = c_fully_fold_internal (op0, in_init, &op0_const, &op0_const_self,
				   for_int_const, خطأ);

      STRIP_TYPE_NOPS (op0);
      c_disable_warnings (op0 == truthvalue_false_نود);
      op1 = c_fully_fold_internal (op1, in_init, &op1_const, &op1_const_self,
				   for_int_const, خطأ);
      STRIP_TYPE_NOPS (op1);
      c_enable_warnings (op0 == truthvalue_false_نود);

      c_disable_warnings (op0 == truthvalue_true_نود);
      op2 = c_fully_fold_internal (op2, in_init, &op2_const, &op2_const_self,
				   for_int_const, خطأ);
      STRIP_TYPE_NOPS (op2);
      c_enable_warnings (op0 == truthvalue_true_نود);

      إذا (for_int_const
	  && (ڤوکوق_CODE (op0) != INTEGER_CST
	      /* Only the evaluated operand must be an INTEGER_CST.  */
	      || (op0 == truthvalue_true_نود
		  ? ڤوکوق_CODE (op1) != INTEGER_CST
		  : ڤوکوق_CODE (op2) != INTEGER_CST)))
	اذهب out;

      إذا (op0 != orig_op0 || op1 != orig_op1 || op2 != orig_op2)
	ret = fold_build3_loc (loc, code, ڤوکوق_TYPE (اوڠکاڤن), op0, op1, op2);
      وإلا
	ret = fold (اوڠکاڤن);
      *maybe_const_operands &= op0_const;
      *maybe_const_itself &= op0_const_self;
      إذا (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && op0 == truthvalue_false_نود))
	*maybe_const_operands &= op1_const;
      إذا (!(op0_const
	    && op0_const_self
	    && op0 == truthvalue_false_نود))
	*maybe_const_itself &= op1_const_self;
      إذا (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && op0 == truthvalue_true_نود))
	*maybe_const_operands &= op2_const;
      إذا (!(op0_const
	    && op0_const_self
	    && op0 == truthvalue_true_نود))
	*maybe_const_itself &= op2_const_self;
      اذهب out;

    حالة VEC_COND_اوڠکاڤن:
      orig_op0 = op0 = ڤوکوق_OPERAND (اوڠکاڤن, 0);
      orig_op1 = op1 = ڤوکوق_OPERAND (اوڠکاڤن, 1);
      orig_op2 = op2 = ڤوکوق_OPERAND (اوڠکاڤن, 2);
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
	ret = fold_build3_loc (loc, code, ڤوکوق_TYPE (اوڠکاڤن), op0, op1, op2);
      وإلا
	ret = fold (اوڠکاڤن);
      اذهب out;

    حالة EXCESS_PRECISION_اوڠکاڤن:
      /* Each case where an operand with excess precision may be
	 encountered must remove the EXCESS_PRECISION_EXPR around
	 inner operands and possibly put one around the whole
	 expression or possibly convert to the semantic type (which
	 c_fully_fold does); we cannot tell at this stage which is
	 appropriate in any particular case.  */
      gcc_unreachable ();

    حالة SAVE_اوڠکاڤن:
      /* Make sure to fold the contents of a SAVE_EXPR exactly once.  */
      op0 = ڤوکوق_OPERAND (اوڠکاڤن, 0);
      إذا (!SAVE_اوڠکاڤن_FOLDED_P (اوڠکاڤن))
	{
	  op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				       maybe_const_itself, for_int_const,
				       خطأ);
	  ڤوکوق_OPERAND (اوڠکاڤن, 0) = op0;
	  SAVE_اوڠکاڤن_FOLDED_P (اوڠکاڤن) = true;
	}
      /* Return the SAVE_EXPR operand if it is invariant.  */
      إذا (ڤوکوق_invariant_p (op0))
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
	ret = build1 (NOP_اوڠکاڤن, ڤوکوق_TYPE (ret), ret);
      suppress_warning (ret, OPT_Woverflow);
    }
  إذا (ret != اوڠکاڤن)
    {
      protected_set_اوڠکاڤن_location (ret, loc);
      إذا (IS_اوڠکاڤن_CODE_CLASS (kind))
	set_source_range (ret, old_range.m_start, old_range.m_finish);
    }
  أرجع ret;
}

/* Fold X for consideration by one of the warning functions when checking
   whether an expression has a constant value.  */

ڤوکوق
fold_for_warn (ڤوکوق x)
{
  /* The C front-end has already folded X appropriately.  */
  أرجع x;
}
