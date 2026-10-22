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

#অন্তর্ভাৱ "config.h"
#অন্তর্ভাৱ "system.h"
#অন্তর্ভাৱ "coretypes.h"
#অন্তর্ভাৱ "target.h"
#অন্তর্ভাৱ "function.h"
#অন্তর্ভাৱ "bitmap.h"
#অন্তর্ভাৱ "c-tree.h"
#অন্তর্ভাৱ "intl.h"
#অন্তর্ভাৱ "gimplify.h"

স্থির বৃক্ষ c_fully_fold_internal (বৃক্ষ ৰাশিমালা, তার্কিক, তার্কিক *, তার্কিক *, তার্কিক,
				   তার্কিক);

/* If DISABLE is true, stop issuing warnings.  This is used when
   parsing code that we know will not be executed.  This function may
   be called multiple times, and works as a stack.  */

স্থির শূন্য
c_disable_warnings (তার্কিক disable)
{
  যদি (disable)
    {
      ++c_inhibit_evaluation_warnings;
    }
}

/* If ENABLE is true, re-enable issuing warnings.  */

স্থির শূন্য
c_enable_warnings (তার্কিক enable)
{
  যদি (enable)
    {
      --c_inhibit_evaluation_warnings;
    }
}

/* Try to fold ARRAY_REF ary[index] if possible and not handled by
   normal fold, return NULL_TREE otherwise.  */

স্থির বৃক্ষ
c_fold_array_ref (বৃক্ষ type, বৃক্ষ ary, বৃক্ষ index)
{
  যদি (বৃক্ষ_CODE (ary) != STRING_CST
      || বৃক্ষ_CODE (index) != INTEGER_CST
      || বৃক্ষ_OVERFLOW (index)
      || বৃক্ষ_CODE (বৃক্ষ_TYPE (ary)) != ARRAY_TYPE
      || !বৃক্ষ_fits_uhwi_p (index))
    ঘূৰাই NULL_বৃক্ষ;

  বৃক্ষ elem_type = বৃক্ষ_TYPE (বৃক্ষ_TYPE (ary));
  unsigned elem_nchars = (TYPE_PRECISION (elem_type)
			  / TYPE_PRECISION (char_type_গ্ৰন্থি));
  unsigned len = (unsigned) বৃক্ষ_STRING_LENGTH (ary) / elem_nchars;
  বৃক্ষ nelts_minus_one = array_type_nelts_minus_one (বৃক্ষ_TYPE (ary));
  তার্কিক dummy1 = সঁচা, dummy2 = সঁচা;
  nelts_minus_one = c_fully_fold_internal (nelts_minus_one, সঁচা, &dummy1,
					   &dummy2, মিছা, মিছা);
  unsigned HOST_WIDE_INT i = বৃক্ষ_to_uhwi (index);
  যদি (!বৃক্ষ_int_cst_le (index, nelts_minus_one)
      || i >= len
      || i + elem_nchars > len)
    ঘূৰাই NULL_বৃক্ষ;

  যদি (elem_nchars == 1)
    ঘূৰাই build_int_cst (type, বৃক্ষ_STRING_POINTER (ary)[i]);

  ধ্রুৱ unsigned ৱর্ণ *ptr
    = ((ধ্রুৱ unsigned ৱর্ণ *)বৃক্ষ_STRING_POINTER (ary) + i * elem_nchars);
  ঘূৰাই native_interpret_ৰাশিমালা (type, ptr, elem_nchars);
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

বৃক্ষ
c_fully_fold (বৃক্ষ ৰাশিমালা, তার্কিক in_init, তার্কিক *maybe_const, তার্কিক lval)
{
  বৃক্ষ ret;
  বৃক্ষ eptype = NULL_বৃক্ষ;
  তার্কিক dummy = সঁচা;
  তার্কিক maybe_const_itself = সঁচা;
  location_t loc = ৰাশিমালা_LOCATION (ৰাশিমালা);

  যদি (!maybe_const)
    maybe_const = &dummy;
  যদি (বৃক্ষ_CODE (ৰাশিমালা) == EXCESS_PRECISION_ৰাশিমালা)
    {
      eptype = বৃক্ষ_TYPE (ৰাশিমালা);
      ৰাশিমালা = বৃক্ষ_OPERAND (ৰাশিমালা, 0);
    }
  ret = c_fully_fold_internal (ৰাশিমালা, in_init, maybe_const,
			       &maybe_const_itself, মিছা, lval);
  যদি (eptype)
    ret = fold_convert_loc (loc, eptype, ret);
  *maybe_const &= maybe_const_itself;
  ঘূৰাই ret;
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

স্থির বৃক্ষ
c_fully_fold_internal (বৃক্ষ ৰাশিমালা, তার্কিক in_init, তার্কিক *maybe_const_operands,
		       তার্কিক *maybe_const_itself, তার্কিক for_int_const, তার্কিক lval)
{
  বৃক্ষ ret = ৰাশিমালা;
  গণনা বৃক্ষ_code code = বৃক্ষ_CODE (ৰাশিমালা);
  গণনা বৃক্ষ_code_class kind = বৃক্ষ_CODE_CLASS (code);
  location_t loc = ৰাশিমালা_LOCATION (ৰাশিমালা);
  বৃক্ষ op0, op1, op2, op3;
  বৃক্ষ orig_op0, orig_op1, orig_op2;
  তার্কিক op0_const = সঁচা, op1_const = সঁচা, op2_const = সঁচা;
  তার্কিক op0_const_self = সঁচা, op1_const_self = সঁচা, op2_const_self = সঁচা;
  তার্কিক nowarning = warning_suppressed_p (ৰাশিমালা, OPT_Woverflow);
  তার্কিক unused_p;
  তার্কিক op0_lval = মিছা;
  source_range old_range;

  /* Constants, declarations, statements, errors, and anything else not
     counted as an expression cannot usefully be folded further at this
     point.  */
  যদি (!IS_ৰাশিমালা_CODE_CLASS (kind) || kind == tcc_statement)
    {
      /* Except for variables which we can optimize to its initializer.  */
      যদি (VAR_P (ৰাশিমালা) && !lval && (optimize || in_init))
	{
	  যদি (in_init)
	    ret = decl_constant_মান_1 (ৰাশিমালা, সঁচা);
	  অন্যথা
	    {
	      ret = decl_constant_মান (ৰাশিমালা);
	      যদি (ret != ৰাশিমালা
		  && (TYPE_MODE (বৃক্ষ_TYPE (ret)) == BLKmode
		      || বৃক্ষ_CODE (বৃক্ষ_TYPE (ret)) == ARRAY_TYPE))
		ঘূৰাই ৰাশিমালা;
	    }
	  /* Avoid unwanted tree sharing between the initializer and current
	     function's body where the tree can be modified e.g. by the
	     gimplifier.  */
	  যদি (ret != ৰাশিমালা && বৃক্ষ_STATIC (ৰাশিমালা))
	    ret = unshare_ৰাশিমালা (ret);
	  ঘূৰাই ret;
	}
      ঘূৰাই ৰাশিমালা;
    }

  যদি (IS_ৰাশিমালা_CODE_CLASS (kind))
    old_range = ৰাশিমালা_LOCATION_RANGE (ৰাশিমালা);

  /* Operands of variable-length expressions (function calls) have
     already been folded, as have __builtin_* function calls, and such
     expressions cannot occur in constant expressions.  */
  যদি (kind == tcc_vl_exp)
    {
      *maybe_const_operands = মিছা;
      ret = fold (ৰাশিমালা);
      গচ্ছ out;
    }

  যদি (code == C_MAYBE_CONST_ৰাশিমালা)
    {
      বৃক্ষ pre = C_MAYBE_CONST_ৰাশিমালা_PRE (ৰাশিমালা);
      বৃক্ষ inner = C_MAYBE_CONST_ৰাশিমালা_ৰাশিমালা (ৰাশিমালা);
      যদি (C_MAYBE_CONST_ৰাশিমালা_NON_CONST (ৰাশিমালা))
	*maybe_const_operands = মিছা;
      যদি (C_MAYBE_CONST_ৰাশিমালা_INT_OPERANDS (ৰাশিমালা))
	{
	  *maybe_const_itself = মিছা;
	  inner = c_fully_fold_internal (inner, in_init, maybe_const_operands,
					 maybe_const_itself, সঁচা, lval);
	}
      যদি (pre && !in_init)
	ret = build2 (COMPOUND_ৰাশিমালা, বৃক্ষ_TYPE (ৰাশিমালা), pre, inner);
      অন্যথা
	ret = inner;
      গচ্ছ out;
    }

  /* Assignment, increment, decrement, function call and comma
     operators, and statement expressions, cannot occur in constant
     expressions if evaluated / outside of sizeof.  (Function calls
     were handled above, though VA_ARG_EXPR is treated like a function
     call here, and statement expressions are handled through
     C_MAYBE_CONST_EXPR to avoid folding inside them.)  */
  ৱিকল্প (code)
    {
    পক্ষ MODIFY_ৰাশিমালা:
    পক্ষ PREDECREMENT_ৰাশিমালা:
    পক্ষ PREINCREMENT_ৰাশিমালা:
    পক্ষ POSTDECREMENT_ৰাশিমালা:
    পক্ষ POSTINCREMENT_ৰাশিমালা:
    পক্ষ COMPOUND_ৰাশিমালা:
      *maybe_const_operands = মিছা;
      ভঙ্গ;

    পক্ষ VA_ARG_ৰাশিমালা:
    পক্ষ TARGET_ৰাশিমালা:
    পক্ষ BIND_ৰাশিমালা:
    পক্ষ OBJ_TYPE_REF:
      *maybe_const_operands = মিছা;
      ret = fold (ৰাশিমালা);
      গচ্ছ out;

    স্ৱভাৱ:
      ভঙ্গ;
    }

  /* Fold individual tree codes as appropriate.  */
  ৱিকল্প (code)
    {
    পক্ষ COMPOUND_LITERAL_ৰাশিমালা:
      /* Any non-constancy will have been marked in a containing
	 C_MAYBE_CONST_EXPR; there is no more folding to do here.  */
      গচ্ছ out;

    পক্ষ COMPONENT_REF:
      orig_op0 = op0 = বৃক্ষ_OPERAND (ৰাশিমালা, 0);
      op1 = বৃক্ষ_OPERAND (ৰাশিমালা, 1);
      op2 = বৃক্ষ_OPERAND (ৰাশিমালা, 2);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, lval);
      STRIP_TYPE_NOPS (op0);
      যদি (op0 != orig_op0)
	ret = build3 (COMPONENT_REF, বৃক্ষ_TYPE (ৰাশিমালা), op0, op1, op2);
      যদি (ret != ৰাশিমালা)
	{
	  বৃক্ষ_READONLY (ret) = বৃক্ষ_READONLY (ৰাশিমালা);
	  বৃক্ষ_THIS_VOLATILE (ret) = বৃক্ষ_THIS_VOLATILE (ৰাশিমালা);
	}
      যদি (!lval)
	ret = fold (ret);
      গচ্ছ out;

    পক্ষ ARRAY_REF:
      orig_op0 = op0 = বৃক্ষ_OPERAND (ৰাশিমালা, 0);
      orig_op1 = op1 = বৃক্ষ_OPERAND (ৰাশিমালা, 1);
      op2 = বৃক্ষ_OPERAND (ৰাশিমালা, 2);
      op3 = বৃক্ষ_OPERAND (ৰাশিমালা, 3);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, lval);
      STRIP_TYPE_NOPS (op0);
      op1 = c_fully_fold_internal (op1, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, মিছা);
      STRIP_TYPE_NOPS (op1);
      /* Fold "foo"[2] in initializers.  */
      যদি (!lval && in_init)
	{
	  ret = c_fold_array_ref (বৃক্ষ_TYPE (ৰাশিমালা), op0, op1);
	  যদি (ret)
	    গচ্ছ out;
	  ret = ৰাশিমালা;
	}
      যদি (op0 != orig_op0 || op1 != orig_op1)
	ret = build4 (ARRAY_REF, বৃক্ষ_TYPE (ৰাশিমালা), op0, op1, op2, op3);
      যদি (ret != ৰাশিমালা)
	{
	  বৃক্ষ_READONLY (ret) = বৃক্ষ_READONLY (ৰাশিমালা);
	  বৃক্ষ_SIDE_EFFECTS (ret) = বৃক্ষ_SIDE_EFFECTS (ৰাশিমালা);
	  বৃক্ষ_THIS_VOLATILE (ret) = বৃক্ষ_THIS_VOLATILE (ৰাশিমালা);
	}
      যদি (!lval)
	ret = fold (ret);
      গচ্ছ out;

    পক্ষ MODIFY_ৰাশিমালা:
    পক্ষ PREDECREMENT_ৰাশিমালা:
    পক্ষ PREINCREMENT_ৰাশিমালা:
    পক্ষ POSTDECREMENT_ৰাশিমালা:
    পক্ষ POSTINCREMENT_ৰাশিমালা:
      op0_lval = সঁচা;
      /* FALLTHRU */
    পক্ষ COMPOUND_ৰাশিমালা:
    পক্ষ PLUS_ৰাশিমালা:
    পক্ষ MINUS_ৰাশিমালা:
    পক্ষ MULT_ৰাশিমালা:
    পক্ষ POINTER_PLUS_ৰাশিমালা:
    পক্ষ POINTER_DIFF_ৰাশিমালা:
    পক্ষ TRUNC_DIV_ৰাশিমালা:
    পক্ষ CEIL_DIV_ৰাশিমালা:
    পক্ষ FLOOR_DIV_ৰাশিমালা:
    পক্ষ TRUNC_MOD_ৰাশিমালা:
    পক্ষ RDIV_ৰাশিমালা:
    পক্ষ EXACT_DIV_ৰাশিমালা:
    পক্ষ LSHIFT_ৰাশিমালা:
    পক্ষ RSHIFT_ৰাশিমালা:
    পক্ষ LROTATE_ৰাশিমালা:
    পক্ষ RROTATE_ৰাশিমালা:
    পক্ষ BIT_IOR_ৰাশিমালা:
    পক্ষ BIT_XOR_ৰাশিমালা:
    পক্ষ BIT_AND_ৰাশিমালা:
    পক্ষ LT_ৰাশিমালা:
    পক্ষ LE_ৰাশিমালা:
    পক্ষ GT_ৰাশিমালা:
    পক্ষ GE_ৰাশিমালা:
    পক্ষ EQ_ৰাশিমালা:
    পক্ষ NE_ৰাশিমালা:
    পক্ষ COMPLEX_ৰাশিমালা:
    পক্ষ TRUTH_AND_ৰাশিমালা:
    পক্ষ TRUTH_OR_ৰাশিমালা:
    পক্ষ TRUTH_XOR_ৰাশিমালা:
    পক্ষ UNORDERED_ৰাশিমালা:
    পক্ষ ORDERED_ৰাশিমালা:
    পক্ষ UNLT_ৰাশিমালা:
    পক্ষ UNLE_ৰাশিমালা:
    পক্ষ UNGT_ৰাশিমালা:
    পক্ষ UNGE_ৰাশিমালা:
    পক্ষ UNEQ_ৰাশিমালা:
    পক্ষ MEM_REF:
      /* Binary operations evaluating both arguments (increment and
	 decrement are binary internally in GCC).  */
      orig_op0 = op0 = বৃক্ষ_OPERAND (ৰাশিমালা, 0);
      orig_op1 = op1 = বৃক্ষ_OPERAND (ৰাশিমালা, 1);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const,
				   op0_lval);
      STRIP_TYPE_NOPS (op0);
      /* The RHS of a MODIFY_EXPR was fully folded when building that
	 expression for the sake of conversion warnings.  */
      যদি (code != MODIFY_ৰাশিমালা)
	op1 = c_fully_fold_internal (op1, in_init, maybe_const_operands,
				     maybe_const_itself, for_int_const, মিছা);
      STRIP_TYPE_NOPS (op1);

      যদি (for_int_const && (বৃক্ষ_CODE (op0) != INTEGER_CST
			    || বৃক্ষ_CODE (op1) != INTEGER_CST))
	গচ্ছ out;

      যদি (বৃক্ষ_CODE_CLASS (code) == tcc_comparison
	  && বৃক্ষ_CODE (বৃক্ষ_TYPE (op0)) == NULLPTR_TYPE
	  && বৃক্ষ_CODE (বৃক্ষ_TYPE (op1)) == NULLPTR_TYPE)
	{
	  ৱিকল্প (code)
	    {
	    পক্ষ EQ_ৰাশিমালা:
	      ret = constant_boolean_গ্ৰন্থি (সঁচা, বৃক্ষ_TYPE (ৰাশিমালা));
	      ভঙ্গ;
	    পক্ষ NE_ৰাশিমালা:
	      ret = constant_boolean_গ্ৰন্থি (মিছা, বৃক্ষ_TYPE (ৰাশিমালা));
	      ভঙ্গ;
	    স্ৱভাৱ:
	      gcc_unreachable ();
	    }
	  ret = omit_two_operands_loc (loc, বৃক্ষ_TYPE (ৰাশিমালা), ret,
				       op0, op1);
	}
      অন্যথা যদি (op0 != orig_op0 || op1 != orig_op1 || in_init)
	ret = in_init
	  ? fold_build2_initializer_loc (loc, code, বৃক্ষ_TYPE (ৰাশিমালা), op0, op1)
	  : fold_build2_loc (loc, code, বৃক্ষ_TYPE (ৰাশিমালা), op0, op1);
      অন্যথা
	ret = fold (ৰাশিমালা);
      যদি (বৃক্ষ_OVERFLOW_P (ret)
	  && !বৃক্ষ_OVERFLOW_P (op0)
	  && !(দ্বিমিক_CLASS_P (op0) && বৃক্ষ_OVERFLOW_P (বৃক্ষ_OPERAND (op0, 1)))
	  && !বৃক্ষ_OVERFLOW_P (op1))
	overflow_warning (ৰাশিমালা_LOC_OR_LOC (ৰাশিমালা, প্ৰবেশ_location), ret, ৰাশিমালা);
      যদি (code == LSHIFT_ৰাশিমালা
	  && বৃক্ষ_CODE (orig_op0) != INTEGER_CST
	  && (বৃক্ষ_CODE (বৃক্ষ_TYPE (orig_op0)) == INTEGER_TYPE
	      || বৃক্ষ_CODE (বৃক্ষ_TYPE (orig_op0)) == BITINT_TYPE)
	  && বৃক্ষ_CODE (op0) == INTEGER_CST
	  && c_inhibit_evaluation_warnings == 0
	  && !TYPE_OVERFLOW_WRAPS (বৃক্ষ_TYPE (orig_op0))
	  && বৃক্ষ_int_cst_sgn (op0) < 0)
	warning_at (loc, OPT_Wshift_negative_মান,
		    "left shift of negative value");
      যদি ((code == LSHIFT_ৰাশিমালা
	   || code == RSHIFT_ৰাশিমালা
	   || code == LROTATE_ৰাশিমালা
	   || code == RROTATE_ৰাশিমালা)
	  && বৃক্ষ_CODE (orig_op1) != INTEGER_CST
	  && বৃক্ষ_CODE (op1) == INTEGER_CST
	  && বৃক্ষ_CODE (বৃক্ষ_TYPE (orig_op1)) == INTEGER_TYPE
	  && c_inhibit_evaluation_warnings == 0)
	{
	  যদি (বৃক্ষ_int_cst_sgn (op1) < 0)
	    warning_at (loc, OPT_Wshift_গুনতি_negative,
			(code == LSHIFT_ৰাশিমালা
			 ? G_("left shift count is negative")
			 : G_("right shift count is negative")));
	  অন্যথা যদি ((বৃক্ষ_CODE (বৃক্ষ_TYPE (orig_op0)) == INTEGER_TYPE
		    || বৃক্ষ_CODE (বৃক্ষ_TYPE (orig_op0)) == BITINT_TYPE
		    || বৃক্ষ_CODE (বৃক্ষ_TYPE (orig_op0)) == FIXED_POINT_TYPE)
		   && compare_বৃক্ষ_int (op1,
					TYPE_PRECISION (বৃক্ষ_TYPE (orig_op0)))
		      >= 0
		   && !warning_suppressed_p (ৰাশিমালা, OPT_Wshift_গুনতি_overflow))
	    warning_at (loc, OPT_Wshift_গুনতি_overflow,
			(code == LSHIFT_ৰাশিমালা
			 ? G_("left shift count >= width of type")
			 : G_("right shift count >= width of type")));
	  অন্যথা যদি (বৃক্ষ_CODE (বৃক্ষ_TYPE (orig_op0)) == VECTOR_TYPE
		   && compare_বৃক্ষ_int (op1,
					TYPE_PRECISION (বৃক্ষ_TYPE (বৃক্ষ_TYPE (orig_op0))))
		      >= 0)
	    warning_at (loc, OPT_Wshift_গুনতি_overflow,
			code == LSHIFT_ৰাশিমালা
			? G_("left shift count >= width of vector element")
			: G_("right shift count >= width of vector element"));
	}
      যদি (code == LSHIFT_ৰাশিমালা
	  /* If either OP0 has been folded to INTEGER_CST...  */
	  && ((বৃক্ষ_CODE (orig_op0) != INTEGER_CST
	       && (বৃক্ষ_CODE (বৃক্ষ_TYPE (orig_op0)) == INTEGER_TYPE
		   || বৃক্ষ_CODE (বৃক্ষ_TYPE (orig_op0)) == BITINT_TYPE)
	       && বৃক্ষ_CODE (op0) == INTEGER_CST)
	      /* ...or if OP1 has been folded to INTEGER_CST...  */
	      || (বৃক্ষ_CODE (orig_op1) != INTEGER_CST
		  && (বৃক্ষ_CODE (বৃক্ষ_TYPE (orig_op1)) == INTEGER_TYPE
		      || বৃক্ষ_CODE (বৃক্ষ_TYPE (orig_op1)) == BITINT_TYPE)
		  && বৃক্ষ_CODE (op1) == INTEGER_CST))
	  && c_inhibit_evaluation_warnings == 0)
	/* ...then maybe we can detect an overflow.  */
	maybe_warn_shift_overflow (loc, op0, op1);
      যদি ((code == TRUNC_DIV_ৰাশিমালা
	   || code == CEIL_DIV_ৰাশিমালা
	   || code == FLOOR_DIV_ৰাশিমালা
	   || code == EXACT_DIV_ৰাশিমালা
	   || code == TRUNC_MOD_ৰাশিমালা)
	  && বৃক্ষ_CODE (orig_op1) != INTEGER_CST
	  && বৃক্ষ_CODE (op1) == INTEGER_CST
	  && (বৃক্ষ_CODE (বৃক্ষ_TYPE (orig_op0)) == INTEGER_TYPE
	      || বৃক্ষ_CODE (বৃক্ষ_TYPE (orig_op0)) == BITINT_TYPE
	      || বৃক্ষ_CODE (বৃক্ষ_TYPE (orig_op0)) == FIXED_POINT_TYPE)
	  && (বৃক্ষ_CODE (বৃক্ষ_TYPE (orig_op1)) == INTEGER_TYPE
	      || বৃক্ষ_CODE (বৃক্ষ_TYPE (orig_op1)) == BITINT_TYPE))
	warn_for_div_by_zero (loc, op1);
      যদি (code == MEM_REF
	  && ret != ৰাশিমালা
	  && বৃক্ষ_CODE (ret) == MEM_REF)
	{
	  বৃক্ষ_READONLY (ret) = বৃক্ষ_READONLY (ৰাশিমালা);
	  বৃক্ষ_SIDE_EFFECTS (ret) = বৃক্ষ_SIDE_EFFECTS (ৰাশিমালা);
	  বৃক্ষ_THIS_VOLATILE (ret) = বৃক্ষ_THIS_VOLATILE (ৰাশিমালা);
	}
      গচ্ছ out;

    পক্ষ ADDR_ৰাশিমালা:
      op0_lval = সঁচা;
      গচ্ছ unary;
    পক্ষ REALPART_ৰাশিমালা:
    পক্ষ IMAGPART_ৰাশিমালা:
    পক্ষ VIEW_CONVERT_ৰাশিমালা:
      op0_lval = lval;
      /* FALLTHRU */
    পক্ষ INDIRECT_REF:
    পক্ষ FIX_TRUNC_ৰাশিমালা:
    পক্ষ FLOAT_ৰাশিমালা:
    CASE_CONVERT:
    পক্ষ ADDR_SPACE_CONVERT_ৰাশিমালা:
    পক্ষ NON_LVALUE_ৰাশিমালা:
    পক্ষ NEGATE_ৰাশিমালা:
    পক্ষ BIT_NOT_ৰাশিমালা:
    পক্ষ TRUTH_NOT_ৰাশিমালা:
    পক্ষ CONJ_ৰাশিমালা:
    পক্ষ PAREN_ৰাশিমালা:
    unary:
      /* Unary operations.  */
      orig_op0 = op0 = বৃক্ষ_OPERAND (ৰাশিমালা, 0);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const,
				   op0_lval);
      STRIP_TYPE_NOPS (op0);

      যদি (for_int_const && বৃক্ষ_CODE (op0) != INTEGER_CST)
	গচ্ছ out;

      /* ??? Cope with user tricks that amount to offsetof.  The middle-end is
	 not prepared to deal with them if they occur in initializers.  */
      যদি (op0 != orig_op0
	  && code == ADDR_ৰাশিমালা
	  && (op1 = get_base_address (op0)) != NULL_বৃক্ষ
	  && INDIRECT_REF_P (op1)
	  && বৃক্ষ_CONSTANT (বৃক্ষ_OPERAND (op1, 0)))
	ret = fold_offsetof (op0, বৃক্ষ_TYPE (ৰাশিমালা));
      অন্যথা যদি (op0 != orig_op0 || in_init)
	ret = in_init
	  ? fold_build1_initializer_loc (loc, code, বৃক্ষ_TYPE (ৰাশিমালা), op0)
	  : fold_build1_loc (loc, code, বৃক্ষ_TYPE (ৰাশিমালা), op0);
      অন্যথা
	ret = fold (ৰাশিমালা);
      যদি (code == INDIRECT_REF
	  && ret != ৰাশিমালা
	  && INDIRECT_REF_P (ret))
	{
	  বৃক্ষ_READONLY (ret) = বৃক্ষ_READONLY (ৰাশিমালা);
	  বৃক্ষ_SIDE_EFFECTS (ret) = বৃক্ষ_SIDE_EFFECTS (ৰাশিমালা);
	  বৃক্ষ_THIS_VOLATILE (ret) = বৃক্ষ_THIS_VOLATILE (ৰাশিমালা);
	}
      ৱিকল্প (code)
	{
	পক্ষ FIX_TRUNC_ৰাশিমালা:
	পক্ষ FLOAT_ৰাশিমালা:
	CASE_CONVERT:
	  /* Don't warn about explicit conversions.  We will already
	     have warned about suspect implicit conversions.  */
	  ভঙ্গ;

	স্ৱভাৱ:
	  যদি (বৃক্ষ_OVERFLOW_P (ret) && !বৃক্ষ_OVERFLOW_P (op0))
	    overflow_warning (ৰাশিমালা_LOCATION (ৰাশিমালা), ret, op0);
	  ভঙ্গ;
	}
      গচ্ছ out;

    পক্ষ TRUTH_ANDIF_ৰাশিমালা:
    পক্ষ TRUTH_ORIF_ৰাশিমালা:
      /* Binary operations not necessarily evaluating both
	 arguments.  */
      orig_op0 = op0 = বৃক্ষ_OPERAND (ৰাশিমালা, 0);
      orig_op1 = op1 = বৃক্ষ_OPERAND (ৰাশিমালা, 1);
      op0 = c_fully_fold_internal (op0, in_init, &op0_const, &op0_const_self,
				   for_int_const, মিছা);
      STRIP_TYPE_NOPS (op0);

      unused_p = (op0 == (code == TRUTH_ANDIF_ৰাশিমালা
			  ? truthvalue_false_গ্ৰন্থি
			  : truthvalue_true_গ্ৰন্থি));
      c_disable_warnings (unused_p);
      op1 = c_fully_fold_internal (op1, in_init, &op1_const, &op1_const_self,
				   for_int_const, মিছা);
      STRIP_TYPE_NOPS (op1);
      c_enable_warnings (unused_p);

      যদি (for_int_const
	  && (বৃক্ষ_CODE (op0) != INTEGER_CST
	      /* Require OP1 be an INTEGER_CST only if it's evaluated.  */
	      || (!unused_p && বৃক্ষ_CODE (op1) != INTEGER_CST)))
	গচ্ছ out;

      যদি (op0 != orig_op0 || op1 != orig_op1 || in_init)
	ret = in_init
	  ? fold_build2_initializer_loc (loc, code, বৃক্ষ_TYPE (ৰাশিমালা), op0, op1)
	  : fold_build2_loc (loc, code, বৃক্ষ_TYPE (ৰাশিমালা), op0, op1);
      অন্যথা
	ret = fold (ৰাশিমালা);
      *maybe_const_operands &= op0_const;
      *maybe_const_itself &= op0_const_self;
      যদি (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && (code == TRUTH_ANDIF_ৰাশিমালা
		? op0 == truthvalue_false_গ্ৰন্থি
		: op0 == truthvalue_true_গ্ৰন্থি)))
	*maybe_const_operands &= op1_const;
      যদি (!(op0_const
	    && op0_const_self
	    && (code == TRUTH_ANDIF_ৰাশিমালা
		? op0 == truthvalue_false_গ্ৰন্থি
		: op0 == truthvalue_true_গ্ৰন্থি)))
	*maybe_const_itself &= op1_const_self;
      গচ্ছ out;

    পক্ষ COND_ৰাশিমালা:
      orig_op0 = op0 = বৃক্ষ_OPERAND (ৰাশিমালা, 0);
      orig_op1 = op1 = বৃক্ষ_OPERAND (ৰাশিমালা, 1);
      orig_op2 = op2 = বৃক্ষ_OPERAND (ৰাশিমালা, 2);
      op0 = c_fully_fold_internal (op0, in_init, &op0_const, &op0_const_self,
				   for_int_const, মিছা);

      STRIP_TYPE_NOPS (op0);
      c_disable_warnings (op0 == truthvalue_false_গ্ৰন্থি);
      op1 = c_fully_fold_internal (op1, in_init, &op1_const, &op1_const_self,
				   for_int_const, মিছা);
      STRIP_TYPE_NOPS (op1);
      c_enable_warnings (op0 == truthvalue_false_গ্ৰন্থি);

      c_disable_warnings (op0 == truthvalue_true_গ্ৰন্থি);
      op2 = c_fully_fold_internal (op2, in_init, &op2_const, &op2_const_self,
				   for_int_const, মিছা);
      STRIP_TYPE_NOPS (op2);
      c_enable_warnings (op0 == truthvalue_true_গ্ৰন্থি);

      যদি (for_int_const
	  && (বৃক্ষ_CODE (op0) != INTEGER_CST
	      /* Only the evaluated operand must be an INTEGER_CST.  */
	      || (op0 == truthvalue_true_গ্ৰন্থি
		  ? বৃক্ষ_CODE (op1) != INTEGER_CST
		  : বৃক্ষ_CODE (op2) != INTEGER_CST)))
	গচ্ছ out;

      যদি (op0 != orig_op0 || op1 != orig_op1 || op2 != orig_op2)
	ret = fold_build3_loc (loc, code, বৃক্ষ_TYPE (ৰাশিমালা), op0, op1, op2);
      অন্যথা
	ret = fold (ৰাশিমালা);
      *maybe_const_operands &= op0_const;
      *maybe_const_itself &= op0_const_self;
      যদি (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && op0 == truthvalue_false_গ্ৰন্থি))
	*maybe_const_operands &= op1_const;
      যদি (!(op0_const
	    && op0_const_self
	    && op0 == truthvalue_false_গ্ৰন্থি))
	*maybe_const_itself &= op1_const_self;
      যদি (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && op0 == truthvalue_true_গ্ৰন্থি))
	*maybe_const_operands &= op2_const;
      যদি (!(op0_const
	    && op0_const_self
	    && op0 == truthvalue_true_গ্ৰন্থি))
	*maybe_const_itself &= op2_const_self;
      গচ্ছ out;

    পক্ষ VEC_COND_ৰাশিমালা:
      orig_op0 = op0 = বৃক্ষ_OPERAND (ৰাশিমালা, 0);
      orig_op1 = op1 = বৃক্ষ_OPERAND (ৰাশিমালা, 1);
      orig_op2 = op2 = বৃক্ষ_OPERAND (ৰাশিমালা, 2);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, মিছা);
      STRIP_TYPE_NOPS (op0);
      op1 = c_fully_fold_internal (op1, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, মিছা);
      STRIP_TYPE_NOPS (op1);
      op2 = c_fully_fold_internal (op2, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, মিছা);
      STRIP_TYPE_NOPS (op2);

      যদি (op0 != orig_op0 || op1 != orig_op1 || op2 != orig_op2)
	ret = fold_build3_loc (loc, code, বৃক্ষ_TYPE (ৰাশিমালা), op0, op1, op2);
      অন্যথা
	ret = fold (ৰাশিমালা);
      গচ্ছ out;

    পক্ষ EXCESS_PRECISION_ৰাশিমালা:
      /* Each case where an operand with excess precision may be
	 encountered must remove the EXCESS_PRECISION_EXPR around
	 inner operands and possibly put one around the whole
	 expression or possibly convert to the semantic type (which
	 c_fully_fold does); we cannot tell at this stage which is
	 appropriate in any particular case.  */
      gcc_unreachable ();

    পক্ষ SAVE_ৰাশিমালা:
      /* Make sure to fold the contents of a SAVE_EXPR exactly once.  */
      op0 = বৃক্ষ_OPERAND (ৰাশিমালা, 0);
      যদি (!SAVE_ৰাশিমালা_FOLDED_P (ৰাশিমালা))
	{
	  op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				       maybe_const_itself, for_int_const,
				       মিছা);
	  বৃক্ষ_OPERAND (ৰাশিমালা, 0) = op0;
	  SAVE_ৰাশিমালা_FOLDED_P (ৰাশিমালা) = সঁচা;
	}
      /* Return the SAVE_EXPR operand if it is invariant.  */
      যদি (বৃক্ষ_invariant_p (op0))
	ret = op0;
      গচ্ছ out;

    স্ৱভাৱ:
      /* Various codes may appear through folding built-in functions
	 and their arguments.  */
      গচ্ছ out;
    }

 out:
  /* Some folding may introduce NON_LVALUE_EXPRs; all lvalue checks
     have been done by this point, so remove them again.  */
  nowarning |= warning_suppressed_p (ret, OPT_Woverflow);
  STRIP_TYPE_NOPS (ret);
  যদি (nowarning && !warning_suppressed_p (ret, OPT_Woverflow))
    {
      যদি (!CAN_HAVE_LOCATION_P (ret))
	ret = build1 (NOP_ৰাশিমালা, বৃক্ষ_TYPE (ret), ret);
      suppress_warning (ret, OPT_Woverflow);
    }
  যদি (ret != ৰাশিমালা)
    {
      protected_set_ৰাশিমালা_location (ret, loc);
      যদি (IS_ৰাশিমালা_CODE_CLASS (kind))
	set_source_range (ret, old_range.m_start, old_range.m_finish);
    }
  ঘূৰাই ret;
}

/* Fold X for consideration by one of the warning functions when checking
   whether an expression has a constant value.  */

বৃক্ষ
fold_for_warn (বৃক্ষ x)
{
  /* The C front-end has already folded X appropriately.  */
  ঘূৰাই x;
}
