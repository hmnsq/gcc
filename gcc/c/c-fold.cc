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

ساكن دەرەخ c_fully_fold_internal (دەرەخ ئىپادە, منطقي, منطقي *, منطقي *, منطقي,
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

ساكن دەرەخ
c_fold_array_ref (دەرەخ type, دەرەخ ary, دەرەخ index)
{
  إذا (دەرەخ_CODE (ary) != STRING_CST
      || دەرەخ_CODE (index) != INTEGER_CST
      || دەرەخ_OVERFLOW (index)
      || دەرەخ_CODE (دەرەخ_TYPE (ary)) != ARRAY_TYPE
      || !دەرەخ_fits_uhwi_p (index))
    أرجع NULL_دەرەخ;

  دەرەخ elem_type = دەرەخ_TYPE (دەرەخ_TYPE (ary));
  unsigned elem_nchars = (TYPE_PRECISION (elem_type)
			  / TYPE_PRECISION (char_type_تۈگۈن));
  unsigned len = (unsigned) دەرەخ_STRING_LENGTH (ary) / elem_nchars;
  دەرەخ nelts_minus_one = array_type_nelts_minus_one (دەرەخ_TYPE (ary));
  منطقي dummy1 = true, dummy2 = true;
  nelts_minus_one = c_fully_fold_internal (nelts_minus_one, true, &dummy1,
					   &dummy2, خطأ, خطأ);
  unsigned HOST_WIDE_INT i = دەرەخ_to_uhwi (index);
  إذا (!دەرەخ_int_cst_le (index, nelts_minus_one)
      || i >= len
      || i + elem_nchars > len)
    أرجع NULL_دەرەخ;

  إذا (elem_nchars == 1)
    أرجع build_int_cst (type, دەرەخ_STRING_POINTER (ary)[i]);

  ثابت unsigned حرف *ptr
    = ((ثابت unsigned حرف *)دەرەخ_STRING_POINTER (ary) + i * elem_nchars);
  أرجع native_interpret_ئىپادە (type, ptr, elem_nchars);
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

دەرەخ
c_fully_fold (دەرەخ ئىپادە, منطقي in_init, منطقي *maybe_const, منطقي lval)
{
  دەرەخ ret;
  دەرەخ eptype = NULL_دەرەخ;
  منطقي dummy = true;
  منطقي maybe_const_itself = true;
  location_t loc = ئىپادە_LOCATION (ئىپادە);

  إذا (!maybe_const)
    maybe_const = &dummy;
  إذا (دەرەخ_CODE (ئىپادە) == EXCESS_PRECISION_ئىپادە)
    {
      eptype = دەرەخ_TYPE (ئىپادە);
      ئىپادە = دەرەخ_OPERAND (ئىپادە, 0);
    }
  ret = c_fully_fold_internal (ئىپادە, in_init, maybe_const,
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

ساكن دەرەخ
c_fully_fold_internal (دەرەخ ئىپادە, منطقي in_init, منطقي *maybe_const_operands,
		       منطقي *maybe_const_itself, منطقي for_int_const, منطقي lval)
{
  دەرەخ ret = ئىپادە;
  تعداد دەرەخ_code code = دەرەخ_CODE (ئىپادە);
  تعداد دەرەخ_code_class kind = دەرەخ_CODE_CLASS (code);
  location_t loc = ئىپادە_LOCATION (ئىپادە);
  دەرەخ op0, op1, op2, op3;
  دەرەخ orig_op0, orig_op1, orig_op2;
  منطقي op0_const = true, op1_const = true, op2_const = true;
  منطقي op0_const_self = true, op1_const_self = true, op2_const_self = true;
  منطقي nowarning = warning_suppressed_p (ئىپادە, OPT_Woverflow);
  منطقي unused_p;
  منطقي op0_lval = خطأ;
  source_range old_range;

  /* Constants, declarations, statements, errors, and anything else not
     counted as an expression cannot usefully be folded further at this
     point.  */
  إذا (!IS_ئىپادە_CODE_CLASS (kind) || kind == tcc_statement)
    {
      /* Except for variables which we can optimize to its initializer.  */
      إذا (VAR_P (ئىپادە) && !lval && (optimize || in_init))
	{
	  إذا (in_init)
	    ret = decl_constant_قىممەت_1 (ئىپادە, true);
	  وإلا
	    {
	      ret = decl_constant_قىممەت (ئىپادە);
	      إذا (ret != ئىپادە
		  && (TYPE_MODE (دەرەخ_TYPE (ret)) == BLKmode
		      || دەرەخ_CODE (دەرەخ_TYPE (ret)) == ARRAY_TYPE))
		أرجع ئىپادە;
	    }
	  /* Avoid unwanted tree sharing between the initializer and current
	     function's body where the tree can be modified e.g. by the
	     gimplifier.  */
	  إذا (ret != ئىپادە && دەرەخ_STATIC (ئىپادە))
	    ret = unshare_ئىپادە (ret);
	  أرجع ret;
	}
      أرجع ئىپادە;
    }

  إذا (IS_ئىپادە_CODE_CLASS (kind))
    old_range = ئىپادە_LOCATION_RANGE (ئىپادە);

  /* Operands of variable-length expressions (function calls) have
     already been folded, as have __builtin_* function calls, and such
     expressions cannot occur in constant expressions.  */
  إذا (kind == tcc_vl_exp)
    {
      *maybe_const_operands = خطأ;
      ret = fold (ئىپادە);
      اذهب out;
    }

  إذا (code == C_MAYBE_CONST_ئىپادە)
    {
      دەرەخ pre = C_MAYBE_CONST_ئىپادە_PRE (ئىپادە);
      دەرەخ inner = C_MAYBE_CONST_ئىپادە_ئىپادە (ئىپادە);
      إذا (C_MAYBE_CONST_ئىپادە_NON_CONST (ئىپادە))
	*maybe_const_operands = خطأ;
      إذا (C_MAYBE_CONST_ئىپادە_INT_OPERANDS (ئىپادە))
	{
	  *maybe_const_itself = خطأ;
	  inner = c_fully_fold_internal (inner, in_init, maybe_const_operands,
					 maybe_const_itself, true, lval);
	}
      إذا (pre && !in_init)
	ret = build2 (COMPOUND_ئىپادە, دەرەخ_TYPE (ئىپادە), pre, inner);
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
    حالة MODIFY_ئىپادە:
    حالة PREDECREMENT_ئىپادە:
    حالة PREINCREMENT_ئىپادە:
    حالة POSTDECREMENT_ئىپادە:
    حالة POSTINCREMENT_ئىپادە:
    حالة COMPOUND_ئىپادە:
      *maybe_const_operands = خطأ;
      اكسر;

    حالة VA_ARG_ئىپادە:
    حالة TARGET_ئىپادە:
    حالة BIND_ئىپادە:
    حالة OBJ_TYPE_REF:
      *maybe_const_operands = خطأ;
      ret = fold (ئىپادە);
      اذهب out;

    افتراضي:
      اكسر;
    }

  /* Fold individual tree codes as appropriate.  */
  بدل (code)
    {
    حالة COMPOUND_LITERAL_ئىپادە:
      /* Any non-constancy will have been marked in a containing
	 C_MAYBE_CONST_EXPR; there is no more folding to do here.  */
      اذهب out;

    حالة COMPONENT_REF:
      orig_op0 = op0 = دەرەخ_OPERAND (ئىپادە, 0);
      op1 = دەرەخ_OPERAND (ئىپادە, 1);
      op2 = دەرەخ_OPERAND (ئىپادە, 2);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, lval);
      STRIP_TYPE_NOPS (op0);
      إذا (op0 != orig_op0)
	ret = build3 (COMPONENT_REF, دەرەخ_TYPE (ئىپادە), op0, op1, op2);
      إذا (ret != ئىپادە)
	{
	  دەرەخ_READONLY (ret) = دەرەخ_READONLY (ئىپادە);
	  دەرەخ_THIS_VOLATILE (ret) = دەرەخ_THIS_VOLATILE (ئىپادە);
	}
      إذا (!lval)
	ret = fold (ret);
      اذهب out;

    حالة ARRAY_REF:
      orig_op0 = op0 = دەرەخ_OPERAND (ئىپادە, 0);
      orig_op1 = op1 = دەرەخ_OPERAND (ئىپادە, 1);
      op2 = دەرەخ_OPERAND (ئىپادە, 2);
      op3 = دەرەخ_OPERAND (ئىپادە, 3);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, lval);
      STRIP_TYPE_NOPS (op0);
      op1 = c_fully_fold_internal (op1, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, خطأ);
      STRIP_TYPE_NOPS (op1);
      /* Fold "foo"[2] in initializers.  */
      إذا (!lval && in_init)
	{
	  ret = c_fold_array_ref (دەرەخ_TYPE (ئىپادە), op0, op1);
	  إذا (ret)
	    اذهب out;
	  ret = ئىپادە;
	}
      إذا (op0 != orig_op0 || op1 != orig_op1)
	ret = build4 (ARRAY_REF, دەرەخ_TYPE (ئىپادە), op0, op1, op2, op3);
      إذا (ret != ئىپادە)
	{
	  دەرەخ_READONLY (ret) = دەرەخ_READONLY (ئىپادە);
	  دەرەخ_SIDE_EFFECTS (ret) = دەرەخ_SIDE_EFFECTS (ئىپادە);
	  دەرەخ_THIS_VOLATILE (ret) = دەرەخ_THIS_VOLATILE (ئىپادە);
	}
      إذا (!lval)
	ret = fold (ret);
      اذهب out;

    حالة MODIFY_ئىپادە:
    حالة PREDECREMENT_ئىپادە:
    حالة PREINCREMENT_ئىپادە:
    حالة POSTDECREMENT_ئىپادە:
    حالة POSTINCREMENT_ئىپادە:
      op0_lval = true;
      /* FALLTHRU */
    حالة COMPOUND_ئىپادە:
    حالة PLUS_ئىپادە:
    حالة MINUS_ئىپادە:
    حالة MULT_ئىپادە:
    حالة POINTER_PLUS_ئىپادە:
    حالة POINTER_DIFF_ئىپادە:
    حالة TRUNC_DIV_ئىپادە:
    حالة CEIL_DIV_ئىپادە:
    حالة FLOOR_DIV_ئىپادە:
    حالة TRUNC_MOD_ئىپادە:
    حالة RDIV_ئىپادە:
    حالة EXACT_DIV_ئىپادە:
    حالة LSHIFT_ئىپادە:
    حالة RSHIFT_ئىپادە:
    حالة LROTATE_ئىپادە:
    حالة RROTATE_ئىپادە:
    حالة BIT_IOR_ئىپادە:
    حالة BIT_XOR_ئىپادە:
    حالة BIT_AND_ئىپادە:
    حالة LT_ئىپادە:
    حالة LE_ئىپادە:
    حالة GT_ئىپادە:
    حالة GE_ئىپادە:
    حالة EQ_ئىپادە:
    حالة NE_ئىپادە:
    حالة COMPLEX_ئىپادە:
    حالة TRUTH_AND_ئىپادە:
    حالة TRUTH_OR_ئىپادە:
    حالة TRUTH_XOR_ئىپادە:
    حالة UNORDERED_ئىپادە:
    حالة ORDERED_ئىپادە:
    حالة UNLT_ئىپادە:
    حالة UNLE_ئىپادە:
    حالة UNGT_ئىپادە:
    حالة UNGE_ئىپادە:
    حالة UNEQ_ئىپادە:
    حالة MEM_REF:
      /* Binary operations evaluating both arguments (increment and
	 decrement are binary internally in GCC).  */
      orig_op0 = op0 = دەرەخ_OPERAND (ئىپادە, 0);
      orig_op1 = op1 = دەرەخ_OPERAND (ئىپادە, 1);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const,
				   op0_lval);
      STRIP_TYPE_NOPS (op0);
      /* The RHS of a MODIFY_EXPR was fully folded when building that
	 expression for the sake of conversion warnings.  */
      إذا (code != MODIFY_ئىپادە)
	op1 = c_fully_fold_internal (op1, in_init, maybe_const_operands,
				     maybe_const_itself, for_int_const, خطأ);
      STRIP_TYPE_NOPS (op1);

      إذا (for_int_const && (دەرەخ_CODE (op0) != INTEGER_CST
			    || دەرەخ_CODE (op1) != INTEGER_CST))
	اذهب out;

      إذا (دەرەخ_CODE_CLASS (code) == tcc_comparison
	  && دەرەخ_CODE (دەرەخ_TYPE (op0)) == NULLPTR_TYPE
	  && دەرەخ_CODE (دەرەخ_TYPE (op1)) == NULLPTR_TYPE)
	{
	  بدل (code)
	    {
	    حالة EQ_ئىپادە:
	      ret = constant_boolean_تۈگۈن (true, دەرەخ_TYPE (ئىپادە));
	      اكسر;
	    حالة NE_ئىپادە:
	      ret = constant_boolean_تۈگۈن (خطأ, دەرەخ_TYPE (ئىپادە));
	      اكسر;
	    افتراضي:
	      gcc_unreachable ();
	    }
	  ret = omit_two_operands_loc (loc, دەرەخ_TYPE (ئىپادە), ret,
				       op0, op1);
	}
      وإلا إذا (op0 != orig_op0 || op1 != orig_op1 || in_init)
	ret = in_init
	  ? fold_build2_initializer_loc (loc, code, دەرەخ_TYPE (ئىپادە), op0, op1)
	  : fold_build2_loc (loc, code, دەرەخ_TYPE (ئىپادە), op0, op1);
      وإلا
	ret = fold (ئىپادە);
      إذا (دەرەخ_OVERFLOW_P (ret)
	  && !دەرەخ_OVERFLOW_P (op0)
	  && !(ئىككىلىك_CLASS_P (op0) && دەرەخ_OVERFLOW_P (دەرەخ_OPERAND (op0, 1)))
	  && !دەرەخ_OVERFLOW_P (op1))
	overflow_warning (ئىپادە_LOC_OR_LOC (ئىپادە, كىرگۈزۈش_location), ret, ئىپادە);
      إذا (code == LSHIFT_ئىپادە
	  && دەرەخ_CODE (orig_op0) != INTEGER_CST
	  && (دەرەخ_CODE (دەرەخ_TYPE (orig_op0)) == INTEGER_TYPE
	      || دەرەخ_CODE (دەرەخ_TYPE (orig_op0)) == BITINT_TYPE)
	  && دەرەخ_CODE (op0) == INTEGER_CST
	  && c_inhibit_evaluation_warnings == 0
	  && !TYPE_OVERFLOW_WRAPS (دەرەخ_TYPE (orig_op0))
	  && دەرەخ_int_cst_sgn (op0) < 0)
	warning_at (loc, OPT_Wshift_negative_قىممەت,
		    "left shift of negative value");
      إذا ((code == LSHIFT_ئىپادە
	   || code == RSHIFT_ئىپادە
	   || code == LROTATE_ئىپادە
	   || code == RROTATE_ئىپادە)
	  && دەرەخ_CODE (orig_op1) != INTEGER_CST
	  && دەرەخ_CODE (op1) == INTEGER_CST
	  && دەرەخ_CODE (دەرەخ_TYPE (orig_op1)) == INTEGER_TYPE
	  && c_inhibit_evaluation_warnings == 0)
	{
	  إذا (دەرەخ_int_cst_sgn (op1) < 0)
	    warning_at (loc, OPT_Wshift_سانى_negative,
			(code == LSHIFT_ئىپادە
			 ? G_("left shift count is negative")
			 : G_("right shift count is negative")));
	  وإلا إذا ((دەرەخ_CODE (دەرەخ_TYPE (orig_op0)) == INTEGER_TYPE
		    || دەرەخ_CODE (دەرەخ_TYPE (orig_op0)) == BITINT_TYPE
		    || دەرەخ_CODE (دەرەخ_TYPE (orig_op0)) == FIXED_POINT_TYPE)
		   && compare_دەرەخ_int (op1,
					TYPE_PRECISION (دەرەخ_TYPE (orig_op0)))
		      >= 0
		   && !warning_suppressed_p (ئىپادە, OPT_Wshift_سانى_overflow))
	    warning_at (loc, OPT_Wshift_سانى_overflow,
			(code == LSHIFT_ئىپادە
			 ? G_("left shift count >= width of type")
			 : G_("right shift count >= width of type")));
	  وإلا إذا (دەرەخ_CODE (دەرەخ_TYPE (orig_op0)) == VECTOR_TYPE
		   && compare_دەرەخ_int (op1,
					TYPE_PRECISION (دەرەخ_TYPE (دەرەخ_TYPE (orig_op0))))
		      >= 0)
	    warning_at (loc, OPT_Wshift_سانى_overflow,
			code == LSHIFT_ئىپادە
			? G_("left shift count >= width of vector element")
			: G_("right shift count >= width of vector element"));
	}
      إذا (code == LSHIFT_ئىپادە
	  /* If either OP0 has been folded to INTEGER_CST...  */
	  && ((دەرەخ_CODE (orig_op0) != INTEGER_CST
	       && (دەرەخ_CODE (دەرەخ_TYPE (orig_op0)) == INTEGER_TYPE
		   || دەرەخ_CODE (دەرەخ_TYPE (orig_op0)) == BITINT_TYPE)
	       && دەرەخ_CODE (op0) == INTEGER_CST)
	      /* ...or if OP1 has been folded to INTEGER_CST...  */
	      || (دەرەخ_CODE (orig_op1) != INTEGER_CST
		  && (دەرەخ_CODE (دەرەخ_TYPE (orig_op1)) == INTEGER_TYPE
		      || دەرەخ_CODE (دەرەخ_TYPE (orig_op1)) == BITINT_TYPE)
		  && دەرەخ_CODE (op1) == INTEGER_CST))
	  && c_inhibit_evaluation_warnings == 0)
	/* ...then maybe we can detect an overflow.  */
	maybe_warn_shift_overflow (loc, op0, op1);
      إذا ((code == TRUNC_DIV_ئىپادە
	   || code == CEIL_DIV_ئىپادە
	   || code == FLOOR_DIV_ئىپادە
	   || code == EXACT_DIV_ئىپادە
	   || code == TRUNC_MOD_ئىپادە)
	  && دەرەخ_CODE (orig_op1) != INTEGER_CST
	  && دەرەخ_CODE (op1) == INTEGER_CST
	  && (دەرەخ_CODE (دەرەخ_TYPE (orig_op0)) == INTEGER_TYPE
	      || دەرەخ_CODE (دەرەخ_TYPE (orig_op0)) == BITINT_TYPE
	      || دەرەخ_CODE (دەرەخ_TYPE (orig_op0)) == FIXED_POINT_TYPE)
	  && (دەرەخ_CODE (دەرەخ_TYPE (orig_op1)) == INTEGER_TYPE
	      || دەرەخ_CODE (دەرەخ_TYPE (orig_op1)) == BITINT_TYPE))
	warn_for_div_by_zero (loc, op1);
      إذا (code == MEM_REF
	  && ret != ئىپادە
	  && دەرەخ_CODE (ret) == MEM_REF)
	{
	  دەرەخ_READONLY (ret) = دەرەخ_READONLY (ئىپادە);
	  دەرەخ_SIDE_EFFECTS (ret) = دەرەخ_SIDE_EFFECTS (ئىپادە);
	  دەرەخ_THIS_VOLATILE (ret) = دەرەخ_THIS_VOLATILE (ئىپادە);
	}
      اذهب out;

    حالة ADDR_ئىپادە:
      op0_lval = true;
      اذهب unary;
    حالة REALPART_ئىپادە:
    حالة IMAGPART_ئىپادە:
    حالة VIEW_CONVERT_ئىپادە:
      op0_lval = lval;
      /* FALLTHRU */
    حالة INDIRECT_REF:
    حالة FIX_TRUNC_ئىپادە:
    حالة FLOAT_ئىپادە:
    CASE_CONVERT:
    حالة ADDR_SPACE_CONVERT_ئىپادە:
    حالة NON_LVALUE_ئىپادە:
    حالة NEGATE_ئىپادە:
    حالة BIT_NOT_ئىپادە:
    حالة TRUTH_NOT_ئىپادە:
    حالة CONJ_ئىپادە:
    حالة PAREN_ئىپادە:
    unary:
      /* Unary operations.  */
      orig_op0 = op0 = دەرەخ_OPERAND (ئىپادە, 0);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const,
				   op0_lval);
      STRIP_TYPE_NOPS (op0);

      إذا (for_int_const && دەرەخ_CODE (op0) != INTEGER_CST)
	اذهب out;

      /* ??? Cope with user tricks that amount to offsetof.  The middle-end is
	 not prepared to deal with them if they occur in initializers.  */
      إذا (op0 != orig_op0
	  && code == ADDR_ئىپادە
	  && (op1 = get_base_address (op0)) != NULL_دەرەخ
	  && INDIRECT_REF_P (op1)
	  && دەرەخ_CONSTANT (دەرەخ_OPERAND (op1, 0)))
	ret = fold_offsetof (op0, دەرەخ_TYPE (ئىپادە));
      وإلا إذا (op0 != orig_op0 || in_init)
	ret = in_init
	  ? fold_build1_initializer_loc (loc, code, دەرەخ_TYPE (ئىپادە), op0)
	  : fold_build1_loc (loc, code, دەرەخ_TYPE (ئىپادە), op0);
      وإلا
	ret = fold (ئىپادە);
      إذا (code == INDIRECT_REF
	  && ret != ئىپادە
	  && INDIRECT_REF_P (ret))
	{
	  دەرەخ_READONLY (ret) = دەرەخ_READONLY (ئىپادە);
	  دەرەخ_SIDE_EFFECTS (ret) = دەرەخ_SIDE_EFFECTS (ئىپادە);
	  دەرەخ_THIS_VOLATILE (ret) = دەرەخ_THIS_VOLATILE (ئىپادە);
	}
      بدل (code)
	{
	حالة FIX_TRUNC_ئىپادە:
	حالة FLOAT_ئىپادە:
	CASE_CONVERT:
	  /* Don't warn about explicit conversions.  We will already
	     have warned about suspect implicit conversions.  */
	  اكسر;

	افتراضي:
	  إذا (دەرەخ_OVERFLOW_P (ret) && !دەرەخ_OVERFLOW_P (op0))
	    overflow_warning (ئىپادە_LOCATION (ئىپادە), ret, op0);
	  اكسر;
	}
      اذهب out;

    حالة TRUTH_ANDIF_ئىپادە:
    حالة TRUTH_ORIF_ئىپادە:
      /* Binary operations not necessarily evaluating both
	 arguments.  */
      orig_op0 = op0 = دەرەخ_OPERAND (ئىپادە, 0);
      orig_op1 = op1 = دەرەخ_OPERAND (ئىپادە, 1);
      op0 = c_fully_fold_internal (op0, in_init, &op0_const, &op0_const_self,
				   for_int_const, خطأ);
      STRIP_TYPE_NOPS (op0);

      unused_p = (op0 == (code == TRUTH_ANDIF_ئىپادە
			  ? truthvalue_false_تۈگۈن
			  : truthvalue_true_تۈگۈن));
      c_disable_warnings (unused_p);
      op1 = c_fully_fold_internal (op1, in_init, &op1_const, &op1_const_self,
				   for_int_const, خطأ);
      STRIP_TYPE_NOPS (op1);
      c_enable_warnings (unused_p);

      إذا (for_int_const
	  && (دەرەخ_CODE (op0) != INTEGER_CST
	      /* Require OP1 be an INTEGER_CST only if it's evaluated.  */
	      || (!unused_p && دەرەخ_CODE (op1) != INTEGER_CST)))
	اذهب out;

      إذا (op0 != orig_op0 || op1 != orig_op1 || in_init)
	ret = in_init
	  ? fold_build2_initializer_loc (loc, code, دەرەخ_TYPE (ئىپادە), op0, op1)
	  : fold_build2_loc (loc, code, دەرەخ_TYPE (ئىپادە), op0, op1);
      وإلا
	ret = fold (ئىپادە);
      *maybe_const_operands &= op0_const;
      *maybe_const_itself &= op0_const_self;
      إذا (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && (code == TRUTH_ANDIF_ئىپادە
		? op0 == truthvalue_false_تۈگۈن
		: op0 == truthvalue_true_تۈگۈن)))
	*maybe_const_operands &= op1_const;
      إذا (!(op0_const
	    && op0_const_self
	    && (code == TRUTH_ANDIF_ئىپادە
		? op0 == truthvalue_false_تۈگۈن
		: op0 == truthvalue_true_تۈگۈن)))
	*maybe_const_itself &= op1_const_self;
      اذهب out;

    حالة COND_ئىپادە:
      orig_op0 = op0 = دەرەخ_OPERAND (ئىپادە, 0);
      orig_op1 = op1 = دەرەخ_OPERAND (ئىپادە, 1);
      orig_op2 = op2 = دەرەخ_OPERAND (ئىپادە, 2);
      op0 = c_fully_fold_internal (op0, in_init, &op0_const, &op0_const_self,
				   for_int_const, خطأ);

      STRIP_TYPE_NOPS (op0);
      c_disable_warnings (op0 == truthvalue_false_تۈگۈن);
      op1 = c_fully_fold_internal (op1, in_init, &op1_const, &op1_const_self,
				   for_int_const, خطأ);
      STRIP_TYPE_NOPS (op1);
      c_enable_warnings (op0 == truthvalue_false_تۈگۈن);

      c_disable_warnings (op0 == truthvalue_true_تۈگۈن);
      op2 = c_fully_fold_internal (op2, in_init, &op2_const, &op2_const_self,
				   for_int_const, خطأ);
      STRIP_TYPE_NOPS (op2);
      c_enable_warnings (op0 == truthvalue_true_تۈگۈن);

      إذا (for_int_const
	  && (دەرەخ_CODE (op0) != INTEGER_CST
	      /* Only the evaluated operand must be an INTEGER_CST.  */
	      || (op0 == truthvalue_true_تۈگۈن
		  ? دەرەخ_CODE (op1) != INTEGER_CST
		  : دەرەخ_CODE (op2) != INTEGER_CST)))
	اذهب out;

      إذا (op0 != orig_op0 || op1 != orig_op1 || op2 != orig_op2)
	ret = fold_build3_loc (loc, code, دەرەخ_TYPE (ئىپادە), op0, op1, op2);
      وإلا
	ret = fold (ئىپادە);
      *maybe_const_operands &= op0_const;
      *maybe_const_itself &= op0_const_self;
      إذا (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && op0 == truthvalue_false_تۈگۈن))
	*maybe_const_operands &= op1_const;
      إذا (!(op0_const
	    && op0_const_self
	    && op0 == truthvalue_false_تۈگۈن))
	*maybe_const_itself &= op1_const_self;
      إذا (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && op0 == truthvalue_true_تۈگۈن))
	*maybe_const_operands &= op2_const;
      إذا (!(op0_const
	    && op0_const_self
	    && op0 == truthvalue_true_تۈگۈن))
	*maybe_const_itself &= op2_const_self;
      اذهب out;

    حالة VEC_COND_ئىپادە:
      orig_op0 = op0 = دەرەخ_OPERAND (ئىپادە, 0);
      orig_op1 = op1 = دەرەخ_OPERAND (ئىپادە, 1);
      orig_op2 = op2 = دەرەخ_OPERAND (ئىپادە, 2);
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
	ret = fold_build3_loc (loc, code, دەرەخ_TYPE (ئىپادە), op0, op1, op2);
      وإلا
	ret = fold (ئىپادە);
      اذهب out;

    حالة EXCESS_PRECISION_ئىپادە:
      /* Each case where an operand with excess precision may be
	 encountered must remove the EXCESS_PRECISION_EXPR around
	 inner operands and possibly put one around the whole
	 expression or possibly convert to the semantic type (which
	 c_fully_fold does); we cannot tell at this stage which is
	 appropriate in any particular case.  */
      gcc_unreachable ();

    حالة SAVE_ئىپادە:
      /* Make sure to fold the contents of a SAVE_EXPR exactly once.  */
      op0 = دەرەخ_OPERAND (ئىپادە, 0);
      إذا (!SAVE_ئىپادە_FOLDED_P (ئىپادە))
	{
	  op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				       maybe_const_itself, for_int_const,
				       خطأ);
	  دەرەخ_OPERAND (ئىپادە, 0) = op0;
	  SAVE_ئىپادە_FOLDED_P (ئىپادە) = true;
	}
      /* Return the SAVE_EXPR operand if it is invariant.  */
      إذا (دەرەخ_invariant_p (op0))
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
	ret = build1 (NOP_ئىپادە, دەرەخ_TYPE (ret), ret);
      suppress_warning (ret, OPT_Woverflow);
    }
  إذا (ret != ئىپادە)
    {
      protected_set_ئىپادە_location (ret, loc);
      إذا (IS_ئىپادە_CODE_CLASS (kind))
	set_source_range (ret, old_range.m_start, old_range.m_finish);
    }
  أرجع ret;
}

/* Fold X for consideration by one of the warning functions when checking
   whether an expression has a constant value.  */

دەرەخ
fold_for_warn (دەرەخ x)
{
  /* The C front-end has already folded X appropriately.  */
  أرجع x;
}
