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

#அந்தர்பாவ "config.h"
#அந்தர்பாவ "system.h"
#அந்தர்பாவ "coretypes.h"
#அந்தர்பாவ "target.h"
#அந்தர்பாவ "function.h"
#அந்தர்பாவ "bitmap.h"
#அந்தர்பாவ "c-tree.h"
#அந்தர்பாவ "intl.h"
#அந்தர்பாவ "gimplify.h"

நிலையான மரம் c_fully_fold_internal (மரம் கோவை, தருக்க, தருக்க *, தருக்க *, தருக்க,
				   தருக்க);

/* If DISABLE is true, stop issuing warnings.  This is used when
   parsing code that we know will not be executed.  This function may
   be called multiple times, and works as a stack.  */

நிலையான வெறுமை
c_disable_warnings (தருக்க disable)
{
  எனில் (disable)
    {
      ++c_inhibit_evaluation_warnings;
    }
}

/* If ENABLE is true, re-enable issuing warnings.  */

நிலையான வெறுமை
c_enable_warnings (தருக்க enable)
{
  எனில் (enable)
    {
      --c_inhibit_evaluation_warnings;
    }
}

/* Try to fold ARRAY_REF ary[index] if possible and not handled by
   normal fold, return NULL_TREE otherwise.  */

நிலையான மரம்
c_fold_array_ref (மரம் type, மரம் ary, மரம் index)
{
  எனில் (மரம்_CODE (ary) != STRING_CST
      || மரம்_CODE (index) != INTEGER_CST
      || மரம்_OVERFLOW (index)
      || மரம்_CODE (மரம்_TYPE (ary)) != ARRAY_TYPE
      || !மரம்_fits_uhwi_p (index))
    திரும்பு NULL_மரம்;

  மரம் elem_type = மரம்_TYPE (மரம்_TYPE (ary));
  unsigned elem_nchars = (TYPE_PRECISION (elem_type)
			  / TYPE_PRECISION (char_type_முனை));
  unsigned len = (unsigned) மரம்_STRING_LENGTH (ary) / elem_nchars;
  மரம் nelts_minus_one = array_type_nelts_minus_one (மரம்_TYPE (ary));
  தருக்க dummy1 = உண்மை, dummy2 = உண்மை;
  nelts_minus_one = c_fully_fold_internal (nelts_minus_one, உண்மை, &dummy1,
					   &dummy2, பொய், பொய்);
  unsigned HOST_WIDE_INT i = மரம்_to_uhwi (index);
  எனில் (!மரம்_int_cst_le (index, nelts_minus_one)
      || i >= len
      || i + elem_nchars > len)
    திரும்பு NULL_மரம்;

  எனில் (elem_nchars == 1)
    திரும்பு build_int_cst (type, மரம்_STRING_POINTER (ary)[i]);

  மாறிலி unsigned எழுத்து *ptr
    = ((மாறிலி unsigned எழுத்து *)மரம்_STRING_POINTER (ary) + i * elem_nchars);
  திரும்பு native_interpret_கோவை (type, ptr, elem_nchars);
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

மரம்
c_fully_fold (மரம் கோவை, தருக்க in_init, தருக்க *maybe_const, தருக்க lval)
{
  மரம் ret;
  மரம் eptype = NULL_மரம்;
  தருக்க dummy = உண்மை;
  தருக்க maybe_const_itself = உண்மை;
  location_t loc = கோவை_LOCATION (கோவை);

  எனில் (!maybe_const)
    maybe_const = &dummy;
  எனில் (மரம்_CODE (கோவை) == EXCESS_PRECISION_கோவை)
    {
      eptype = மரம்_TYPE (கோவை);
      கோவை = மரம்_OPERAND (கோவை, 0);
    }
  ret = c_fully_fold_internal (கோவை, in_init, maybe_const,
			       &maybe_const_itself, பொய், lval);
  எனில் (eptype)
    ret = fold_convert_loc (loc, eptype, ret);
  *maybe_const &= maybe_const_itself;
  திரும்பு ret;
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

நிலையான மரம்
c_fully_fold_internal (மரம் கோவை, தருக்க in_init, தருக்க *maybe_const_operands,
		       தருக்க *maybe_const_itself, தருக்க for_int_const, தருக்க lval)
{
  மரம் ret = கோவை;
  எண்ணிக்கை மரம்_code code = மரம்_CODE (கோவை);
  எண்ணிக்கை மரம்_code_class kind = மரம்_CODE_CLASS (code);
  location_t loc = கோவை_LOCATION (கோவை);
  மரம் op0, op1, op2, op3;
  மரம் orig_op0, orig_op1, orig_op2;
  தருக்க op0_const = உண்மை, op1_const = உண்மை, op2_const = உண்மை;
  தருக்க op0_const_self = உண்மை, op1_const_self = உண்மை, op2_const_self = உண்மை;
  தருக்க nowarning = warning_suppressed_p (கோவை, OPT_Woverflow);
  தருக்க unused_p;
  தருக்க op0_lval = பொய்;
  source_range old_range;

  /* Constants, declarations, statements, errors, and anything else not
     counted as an expression cannot usefully be folded further at this
     point.  */
  எனில் (!IS_கோவை_CODE_CLASS (kind) || kind == tcc_statement)
    {
      /* Except for variables which we can optimize to its initializer.  */
      எனில் (VAR_P (கோவை) && !lval && (optimize || in_init))
	{
	  எனில் (in_init)
	    ret = decl_constant_மதிப்பு_1 (கோவை, உண்மை);
	  இல்லையெனில்
	    {
	      ret = decl_constant_மதிப்பு (கோவை);
	      எனில் (ret != கோவை
		  && (TYPE_MODE (மரம்_TYPE (ret)) == BLKmode
		      || மரம்_CODE (மரம்_TYPE (ret)) == ARRAY_TYPE))
		திரும்பு கோவை;
	    }
	  /* Avoid unwanted tree sharing between the initializer and current
	     function's body where the tree can be modified e.g. by the
	     gimplifier.  */
	  எனில் (ret != கோவை && மரம்_STATIC (கோவை))
	    ret = unshare_கோவை (ret);
	  திரும்பு ret;
	}
      திரும்பு கோவை;
    }

  எனில் (IS_கோவை_CODE_CLASS (kind))
    old_range = கோவை_LOCATION_RANGE (கோவை);

  /* Operands of variable-length expressions (function calls) have
     already been folded, as have __builtin_* function calls, and such
     expressions cannot occur in constant expressions.  */
  எனில் (kind == tcc_vl_exp)
    {
      *maybe_const_operands = பொய்;
      ret = fold (கோவை);
      செல் out;
    }

  எனில் (code == C_MAYBE_CONST_கோவை)
    {
      மரம் pre = C_MAYBE_CONST_கோவை_PRE (கோவை);
      மரம் inner = C_MAYBE_CONST_கோவை_கோவை (கோவை);
      எனில் (C_MAYBE_CONST_கோவை_NON_CONST (கோவை))
	*maybe_const_operands = பொய்;
      எனில் (C_MAYBE_CONST_கோவை_INT_OPERANDS (கோவை))
	{
	  *maybe_const_itself = பொய்;
	  inner = c_fully_fold_internal (inner, in_init, maybe_const_operands,
					 maybe_const_itself, உண்மை, lval);
	}
      எனில் (pre && !in_init)
	ret = build2 (COMPOUND_கோவை, மரம்_TYPE (கோவை), pre, inner);
      இல்லையெனில்
	ret = inner;
      செல் out;
    }

  /* Assignment, increment, decrement, function call and comma
     operators, and statement expressions, cannot occur in constant
     expressions if evaluated / outside of sizeof.  (Function calls
     were handled above, though VA_ARG_EXPR is treated like a function
     call here, and statement expressions are handled through
     C_MAYBE_CONST_EXPR to avoid folding inside them.)  */
  தேர்வு (code)
    {
    நிலை MODIFY_கோவை:
    நிலை PREDECREMENT_கோவை:
    நிலை PREINCREMENT_கோவை:
    நிலை POSTDECREMENT_கோவை:
    நிலை POSTINCREMENT_கோவை:
    நிலை COMPOUND_கோவை:
      *maybe_const_operands = பொய்;
      நிறுத்து;

    நிலை VA_ARG_கோவை:
    நிலை TARGET_கோவை:
    நிலை BIND_கோவை:
    நிலை OBJ_TYPE_REF:
      *maybe_const_operands = பொய்;
      ret = fold (கோவை);
      செல் out;

    இயல்பு:
      நிறுத்து;
    }

  /* Fold individual tree codes as appropriate.  */
  தேர்வு (code)
    {
    நிலை COMPOUND_LITERAL_கோவை:
      /* Any non-constancy will have been marked in a containing
	 C_MAYBE_CONST_EXPR; there is no more folding to do here.  */
      செல் out;

    நிலை COMPONENT_REF:
      orig_op0 = op0 = மரம்_OPERAND (கோவை, 0);
      op1 = மரம்_OPERAND (கோவை, 1);
      op2 = மரம்_OPERAND (கோவை, 2);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, lval);
      STRIP_TYPE_NOPS (op0);
      எனில் (op0 != orig_op0)
	ret = build3 (COMPONENT_REF, மரம்_TYPE (கோவை), op0, op1, op2);
      எனில் (ret != கோவை)
	{
	  மரம்_READONLY (ret) = மரம்_READONLY (கோவை);
	  மரம்_THIS_VOLATILE (ret) = மரம்_THIS_VOLATILE (கோவை);
	}
      எனில் (!lval)
	ret = fold (ret);
      செல் out;

    நிலை ARRAY_REF:
      orig_op0 = op0 = மரம்_OPERAND (கோவை, 0);
      orig_op1 = op1 = மரம்_OPERAND (கோவை, 1);
      op2 = மரம்_OPERAND (கோவை, 2);
      op3 = மரம்_OPERAND (கோவை, 3);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, lval);
      STRIP_TYPE_NOPS (op0);
      op1 = c_fully_fold_internal (op1, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, பொய்);
      STRIP_TYPE_NOPS (op1);
      /* Fold "foo"[2] in initializers.  */
      எனில் (!lval && in_init)
	{
	  ret = c_fold_array_ref (மரம்_TYPE (கோவை), op0, op1);
	  எனில் (ret)
	    செல் out;
	  ret = கோவை;
	}
      எனில் (op0 != orig_op0 || op1 != orig_op1)
	ret = build4 (ARRAY_REF, மரம்_TYPE (கோவை), op0, op1, op2, op3);
      எனில் (ret != கோவை)
	{
	  மரம்_READONLY (ret) = மரம்_READONLY (கோவை);
	  மரம்_SIDE_EFFECTS (ret) = மரம்_SIDE_EFFECTS (கோவை);
	  மரம்_THIS_VOLATILE (ret) = மரம்_THIS_VOLATILE (கோவை);
	}
      எனில் (!lval)
	ret = fold (ret);
      செல் out;

    நிலை MODIFY_கோவை:
    நிலை PREDECREMENT_கோவை:
    நிலை PREINCREMENT_கோவை:
    நிலை POSTDECREMENT_கோவை:
    நிலை POSTINCREMENT_கோவை:
      op0_lval = உண்மை;
      /* FALLTHRU */
    நிலை COMPOUND_கோவை:
    நிலை PLUS_கோவை:
    நிலை MINUS_கோவை:
    நிலை MULT_கோவை:
    நிலை POINTER_PLUS_கோவை:
    நிலை POINTER_DIFF_கோவை:
    நிலை TRUNC_DIV_கோவை:
    நிலை CEIL_DIV_கோவை:
    நிலை FLOOR_DIV_கோவை:
    நிலை TRUNC_MOD_கோவை:
    நிலை RDIV_கோவை:
    நிலை EXACT_DIV_கோவை:
    நிலை LSHIFT_கோவை:
    நிலை RSHIFT_கோவை:
    நிலை LROTATE_கோவை:
    நிலை RROTATE_கோவை:
    நிலை BIT_IOR_கோவை:
    நிலை BIT_XOR_கோவை:
    நிலை BIT_AND_கோவை:
    நிலை LT_கோவை:
    நிலை LE_கோவை:
    நிலை GT_கோவை:
    நிலை GE_கோவை:
    நிலை EQ_கோவை:
    நிலை NE_கோவை:
    நிலை COMPLEX_கோவை:
    நிலை TRUTH_AND_கோவை:
    நிலை TRUTH_OR_கோவை:
    நிலை TRUTH_XOR_கோவை:
    நிலை UNORDERED_கோவை:
    நிலை ORDERED_கோவை:
    நிலை UNLT_கோவை:
    நிலை UNLE_கோவை:
    நிலை UNGT_கோவை:
    நிலை UNGE_கோவை:
    நிலை UNEQ_கோவை:
    நிலை MEM_REF:
      /* Binary operations evaluating both arguments (increment and
	 decrement are binary internally in GCC).  */
      orig_op0 = op0 = மரம்_OPERAND (கோவை, 0);
      orig_op1 = op1 = மரம்_OPERAND (கோவை, 1);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const,
				   op0_lval);
      STRIP_TYPE_NOPS (op0);
      /* The RHS of a MODIFY_EXPR was fully folded when building that
	 expression for the sake of conversion warnings.  */
      எனில் (code != MODIFY_கோவை)
	op1 = c_fully_fold_internal (op1, in_init, maybe_const_operands,
				     maybe_const_itself, for_int_const, பொய்);
      STRIP_TYPE_NOPS (op1);

      எனில் (for_int_const && (மரம்_CODE (op0) != INTEGER_CST
			    || மரம்_CODE (op1) != INTEGER_CST))
	செல் out;

      எனில் (மரம்_CODE_CLASS (code) == tcc_comparison
	  && மரம்_CODE (மரம்_TYPE (op0)) == NULLPTR_TYPE
	  && மரம்_CODE (மரம்_TYPE (op1)) == NULLPTR_TYPE)
	{
	  தேர்வு (code)
	    {
	    நிலை EQ_கோவை:
	      ret = constant_boolean_முனை (உண்மை, மரம்_TYPE (கோவை));
	      நிறுத்து;
	    நிலை NE_கோவை:
	      ret = constant_boolean_முனை (பொய், மரம்_TYPE (கோவை));
	      நிறுத்து;
	    இயல்பு:
	      gcc_unreachable ();
	    }
	  ret = omit_two_operands_loc (loc, மரம்_TYPE (கோவை), ret,
				       op0, op1);
	}
      இல்லையெனில் எனில் (op0 != orig_op0 || op1 != orig_op1 || in_init)
	ret = in_init
	  ? fold_build2_initializer_loc (loc, code, மரம்_TYPE (கோவை), op0, op1)
	  : fold_build2_loc (loc, code, மரம்_TYPE (கோவை), op0, op1);
      இல்லையெனில்
	ret = fold (கோவை);
      எனில் (மரம்_OVERFLOW_P (ret)
	  && !மரம்_OVERFLOW_P (op0)
	  && !(இருமம்_CLASS_P (op0) && மரம்_OVERFLOW_P (மரம்_OPERAND (op0, 1)))
	  && !மரம்_OVERFLOW_P (op1))
	overflow_warning (கோவை_LOC_OR_LOC (கோவை, உள்ளீடு_location), ret, கோவை);
      எனில் (code == LSHIFT_கோவை
	  && மரம்_CODE (orig_op0) != INTEGER_CST
	  && (மரம்_CODE (மரம்_TYPE (orig_op0)) == INTEGER_TYPE
	      || மரம்_CODE (மரம்_TYPE (orig_op0)) == BITINT_TYPE)
	  && மரம்_CODE (op0) == INTEGER_CST
	  && c_inhibit_evaluation_warnings == 0
	  && !TYPE_OVERFLOW_WRAPS (மரம்_TYPE (orig_op0))
	  && மரம்_int_cst_sgn (op0) < 0)
	warning_at (loc, OPT_Wshift_negative_மதிப்பு,
		    "left shift of negative value");
      எனில் ((code == LSHIFT_கோவை
	   || code == RSHIFT_கோவை
	   || code == LROTATE_கோவை
	   || code == RROTATE_கோவை)
	  && மரம்_CODE (orig_op1) != INTEGER_CST
	  && மரம்_CODE (op1) == INTEGER_CST
	  && மரம்_CODE (மரம்_TYPE (orig_op1)) == INTEGER_TYPE
	  && c_inhibit_evaluation_warnings == 0)
	{
	  எனில் (மரம்_int_cst_sgn (op1) < 0)
	    warning_at (loc, OPT_Wshift_மொத்தம்_negative,
			(code == LSHIFT_கோவை
			 ? G_("left shift count is negative")
			 : G_("right shift count is negative")));
	  இல்லையெனில் எனில் ((மரம்_CODE (மரம்_TYPE (orig_op0)) == INTEGER_TYPE
		    || மரம்_CODE (மரம்_TYPE (orig_op0)) == BITINT_TYPE
		    || மரம்_CODE (மரம்_TYPE (orig_op0)) == FIXED_POINT_TYPE)
		   && compare_மரம்_int (op1,
					TYPE_PRECISION (மரம்_TYPE (orig_op0)))
		      >= 0
		   && !warning_suppressed_p (கோவை, OPT_Wshift_மொத்தம்_overflow))
	    warning_at (loc, OPT_Wshift_மொத்தம்_overflow,
			(code == LSHIFT_கோவை
			 ? G_("left shift count >= width of type")
			 : G_("right shift count >= width of type")));
	  இல்லையெனில் எனில் (மரம்_CODE (மரம்_TYPE (orig_op0)) == VECTOR_TYPE
		   && compare_மரம்_int (op1,
					TYPE_PRECISION (மரம்_TYPE (மரம்_TYPE (orig_op0))))
		      >= 0)
	    warning_at (loc, OPT_Wshift_மொத்தம்_overflow,
			code == LSHIFT_கோவை
			? G_("left shift count >= width of vector element")
			: G_("right shift count >= width of vector element"));
	}
      எனில் (code == LSHIFT_கோவை
	  /* If either OP0 has been folded to INTEGER_CST...  */
	  && ((மரம்_CODE (orig_op0) != INTEGER_CST
	       && (மரம்_CODE (மரம்_TYPE (orig_op0)) == INTEGER_TYPE
		   || மரம்_CODE (மரம்_TYPE (orig_op0)) == BITINT_TYPE)
	       && மரம்_CODE (op0) == INTEGER_CST)
	      /* ...or if OP1 has been folded to INTEGER_CST...  */
	      || (மரம்_CODE (orig_op1) != INTEGER_CST
		  && (மரம்_CODE (மரம்_TYPE (orig_op1)) == INTEGER_TYPE
		      || மரம்_CODE (மரம்_TYPE (orig_op1)) == BITINT_TYPE)
		  && மரம்_CODE (op1) == INTEGER_CST))
	  && c_inhibit_evaluation_warnings == 0)
	/* ...then maybe we can detect an overflow.  */
	maybe_warn_shift_overflow (loc, op0, op1);
      எனில் ((code == TRUNC_DIV_கோவை
	   || code == CEIL_DIV_கோவை
	   || code == FLOOR_DIV_கோவை
	   || code == EXACT_DIV_கோவை
	   || code == TRUNC_MOD_கோவை)
	  && மரம்_CODE (orig_op1) != INTEGER_CST
	  && மரம்_CODE (op1) == INTEGER_CST
	  && (மரம்_CODE (மரம்_TYPE (orig_op0)) == INTEGER_TYPE
	      || மரம்_CODE (மரம்_TYPE (orig_op0)) == BITINT_TYPE
	      || மரம்_CODE (மரம்_TYPE (orig_op0)) == FIXED_POINT_TYPE)
	  && (மரம்_CODE (மரம்_TYPE (orig_op1)) == INTEGER_TYPE
	      || மரம்_CODE (மரம்_TYPE (orig_op1)) == BITINT_TYPE))
	warn_for_div_by_zero (loc, op1);
      எனில் (code == MEM_REF
	  && ret != கோவை
	  && மரம்_CODE (ret) == MEM_REF)
	{
	  மரம்_READONLY (ret) = மரம்_READONLY (கோவை);
	  மரம்_SIDE_EFFECTS (ret) = மரம்_SIDE_EFFECTS (கோவை);
	  மரம்_THIS_VOLATILE (ret) = மரம்_THIS_VOLATILE (கோவை);
	}
      செல் out;

    நிலை ADDR_கோவை:
      op0_lval = உண்மை;
      செல் unary;
    நிலை REALPART_கோவை:
    நிலை IMAGPART_கோவை:
    நிலை VIEW_CONVERT_கோவை:
      op0_lval = lval;
      /* FALLTHRU */
    நிலை INDIRECT_REF:
    நிலை FIX_TRUNC_கோவை:
    நிலை FLOAT_கோவை:
    CASE_CONVERT:
    நிலை ADDR_SPACE_CONVERT_கோவை:
    நிலை NON_LVALUE_கோவை:
    நிலை NEGATE_கோவை:
    நிலை BIT_NOT_கோவை:
    நிலை TRUTH_NOT_கோவை:
    நிலை CONJ_கோவை:
    நிலை PAREN_கோவை:
    unary:
      /* Unary operations.  */
      orig_op0 = op0 = மரம்_OPERAND (கோவை, 0);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const,
				   op0_lval);
      STRIP_TYPE_NOPS (op0);

      எனில் (for_int_const && மரம்_CODE (op0) != INTEGER_CST)
	செல் out;

      /* ??? Cope with user tricks that amount to offsetof.  The middle-end is
	 not prepared to deal with them if they occur in initializers.  */
      எனில் (op0 != orig_op0
	  && code == ADDR_கோவை
	  && (op1 = get_base_address (op0)) != NULL_மரம்
	  && INDIRECT_REF_P (op1)
	  && மரம்_CONSTANT (மரம்_OPERAND (op1, 0)))
	ret = fold_offsetof (op0, மரம்_TYPE (கோவை));
      இல்லையெனில் எனில் (op0 != orig_op0 || in_init)
	ret = in_init
	  ? fold_build1_initializer_loc (loc, code, மரம்_TYPE (கோவை), op0)
	  : fold_build1_loc (loc, code, மரம்_TYPE (கோவை), op0);
      இல்லையெனில்
	ret = fold (கோவை);
      எனில் (code == INDIRECT_REF
	  && ret != கோவை
	  && INDIRECT_REF_P (ret))
	{
	  மரம்_READONLY (ret) = மரம்_READONLY (கோவை);
	  மரம்_SIDE_EFFECTS (ret) = மரம்_SIDE_EFFECTS (கோவை);
	  மரம்_THIS_VOLATILE (ret) = மரம்_THIS_VOLATILE (கோவை);
	}
      தேர்வு (code)
	{
	நிலை FIX_TRUNC_கோவை:
	நிலை FLOAT_கோவை:
	CASE_CONVERT:
	  /* Don't warn about explicit conversions.  We will already
	     have warned about suspect implicit conversions.  */
	  நிறுத்து;

	இயல்பு:
	  எனில் (மரம்_OVERFLOW_P (ret) && !மரம்_OVERFLOW_P (op0))
	    overflow_warning (கோவை_LOCATION (கோவை), ret, op0);
	  நிறுத்து;
	}
      செல் out;

    நிலை TRUTH_ANDIF_கோவை:
    நிலை TRUTH_ORIF_கோவை:
      /* Binary operations not necessarily evaluating both
	 arguments.  */
      orig_op0 = op0 = மரம்_OPERAND (கோவை, 0);
      orig_op1 = op1 = மரம்_OPERAND (கோவை, 1);
      op0 = c_fully_fold_internal (op0, in_init, &op0_const, &op0_const_self,
				   for_int_const, பொய்);
      STRIP_TYPE_NOPS (op0);

      unused_p = (op0 == (code == TRUTH_ANDIF_கோவை
			  ? truthvalue_false_முனை
			  : truthvalue_true_முனை));
      c_disable_warnings (unused_p);
      op1 = c_fully_fold_internal (op1, in_init, &op1_const, &op1_const_self,
				   for_int_const, பொய்);
      STRIP_TYPE_NOPS (op1);
      c_enable_warnings (unused_p);

      எனில் (for_int_const
	  && (மரம்_CODE (op0) != INTEGER_CST
	      /* Require OP1 be an INTEGER_CST only if it's evaluated.  */
	      || (!unused_p && மரம்_CODE (op1) != INTEGER_CST)))
	செல் out;

      எனில் (op0 != orig_op0 || op1 != orig_op1 || in_init)
	ret = in_init
	  ? fold_build2_initializer_loc (loc, code, மரம்_TYPE (கோவை), op0, op1)
	  : fold_build2_loc (loc, code, மரம்_TYPE (கோவை), op0, op1);
      இல்லையெனில்
	ret = fold (கோவை);
      *maybe_const_operands &= op0_const;
      *maybe_const_itself &= op0_const_self;
      எனில் (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && (code == TRUTH_ANDIF_கோவை
		? op0 == truthvalue_false_முனை
		: op0 == truthvalue_true_முனை)))
	*maybe_const_operands &= op1_const;
      எனில் (!(op0_const
	    && op0_const_self
	    && (code == TRUTH_ANDIF_கோவை
		? op0 == truthvalue_false_முனை
		: op0 == truthvalue_true_முனை)))
	*maybe_const_itself &= op1_const_self;
      செல் out;

    நிலை COND_கோவை:
      orig_op0 = op0 = மரம்_OPERAND (கோவை, 0);
      orig_op1 = op1 = மரம்_OPERAND (கோவை, 1);
      orig_op2 = op2 = மரம்_OPERAND (கோவை, 2);
      op0 = c_fully_fold_internal (op0, in_init, &op0_const, &op0_const_self,
				   for_int_const, பொய்);

      STRIP_TYPE_NOPS (op0);
      c_disable_warnings (op0 == truthvalue_false_முனை);
      op1 = c_fully_fold_internal (op1, in_init, &op1_const, &op1_const_self,
				   for_int_const, பொய்);
      STRIP_TYPE_NOPS (op1);
      c_enable_warnings (op0 == truthvalue_false_முனை);

      c_disable_warnings (op0 == truthvalue_true_முனை);
      op2 = c_fully_fold_internal (op2, in_init, &op2_const, &op2_const_self,
				   for_int_const, பொய்);
      STRIP_TYPE_NOPS (op2);
      c_enable_warnings (op0 == truthvalue_true_முனை);

      எனில் (for_int_const
	  && (மரம்_CODE (op0) != INTEGER_CST
	      /* Only the evaluated operand must be an INTEGER_CST.  */
	      || (op0 == truthvalue_true_முனை
		  ? மரம்_CODE (op1) != INTEGER_CST
		  : மரம்_CODE (op2) != INTEGER_CST)))
	செல் out;

      எனில் (op0 != orig_op0 || op1 != orig_op1 || op2 != orig_op2)
	ret = fold_build3_loc (loc, code, மரம்_TYPE (கோவை), op0, op1, op2);
      இல்லையெனில்
	ret = fold (கோவை);
      *maybe_const_operands &= op0_const;
      *maybe_const_itself &= op0_const_self;
      எனில் (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && op0 == truthvalue_false_முனை))
	*maybe_const_operands &= op1_const;
      எனில் (!(op0_const
	    && op0_const_self
	    && op0 == truthvalue_false_முனை))
	*maybe_const_itself &= op1_const_self;
      எனில் (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && op0 == truthvalue_true_முனை))
	*maybe_const_operands &= op2_const;
      எனில் (!(op0_const
	    && op0_const_self
	    && op0 == truthvalue_true_முனை))
	*maybe_const_itself &= op2_const_self;
      செல் out;

    நிலை VEC_COND_கோவை:
      orig_op0 = op0 = மரம்_OPERAND (கோவை, 0);
      orig_op1 = op1 = மரம்_OPERAND (கோவை, 1);
      orig_op2 = op2 = மரம்_OPERAND (கோவை, 2);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, பொய்);
      STRIP_TYPE_NOPS (op0);
      op1 = c_fully_fold_internal (op1, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, பொய்);
      STRIP_TYPE_NOPS (op1);
      op2 = c_fully_fold_internal (op2, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, பொய்);
      STRIP_TYPE_NOPS (op2);

      எனில் (op0 != orig_op0 || op1 != orig_op1 || op2 != orig_op2)
	ret = fold_build3_loc (loc, code, மரம்_TYPE (கோவை), op0, op1, op2);
      இல்லையெனில்
	ret = fold (கோவை);
      செல் out;

    நிலை EXCESS_PRECISION_கோவை:
      /* Each case where an operand with excess precision may be
	 encountered must remove the EXCESS_PRECISION_EXPR around
	 inner operands and possibly put one around the whole
	 expression or possibly convert to the semantic type (which
	 c_fully_fold does); we cannot tell at this stage which is
	 appropriate in any particular case.  */
      gcc_unreachable ();

    நிலை SAVE_கோவை:
      /* Make sure to fold the contents of a SAVE_EXPR exactly once.  */
      op0 = மரம்_OPERAND (கோவை, 0);
      எனில் (!SAVE_கோவை_FOLDED_P (கோவை))
	{
	  op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				       maybe_const_itself, for_int_const,
				       பொய்);
	  மரம்_OPERAND (கோவை, 0) = op0;
	  SAVE_கோவை_FOLDED_P (கோவை) = உண்மை;
	}
      /* Return the SAVE_EXPR operand if it is invariant.  */
      எனில் (மரம்_invariant_p (op0))
	ret = op0;
      செல் out;

    இயல்பு:
      /* Various codes may appear through folding built-in functions
	 and their arguments.  */
      செல் out;
    }

 out:
  /* Some folding may introduce NON_LVALUE_EXPRs; all lvalue checks
     have been done by this point, so remove them again.  */
  nowarning |= warning_suppressed_p (ret, OPT_Woverflow);
  STRIP_TYPE_NOPS (ret);
  எனில் (nowarning && !warning_suppressed_p (ret, OPT_Woverflow))
    {
      எனில் (!CAN_HAVE_LOCATION_P (ret))
	ret = build1 (NOP_கோவை, மரம்_TYPE (ret), ret);
      suppress_warning (ret, OPT_Woverflow);
    }
  எனில் (ret != கோவை)
    {
      protected_set_கோவை_location (ret, loc);
      எனில் (IS_கோவை_CODE_CLASS (kind))
	set_source_range (ret, old_range.m_start, old_range.m_finish);
    }
  திரும்பு ret;
}

/* Fold X for consideration by one of the warning functions when checking
   whether an expression has a constant value.  */

மரம்
fold_for_warn (மரம் x)
{
  /* The C front-end has already folded X appropriately.  */
  திரும்பு x;
}
