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

#অন্তর্ভাব "config.h"
#অন্তর্ভাব "system.h"
#অন্তর্ভাব "coretypes.h"
#অন্তর্ভাব "target.h"
#অন্তর্ভাব "function.h"
#অন্তর্ভাব "bitmap.h"
#অন্তর্ভাব "c-tree.h"
#অন্তর্ভাব "intl.h"
#অন্তর্ভাব "gimplify.h"

স্থির বৃক্ষ c_fully_fold_internal (বৃক্ষ রাশিমালা, যৌক্তিক, যৌক্তিক *, যৌক্তিক *, যৌক্তিক,
				   যৌক্তিক);

/* If DISABLE is true, stop issuing warnings.  This is used when
   parsing code that we know will not be executed.  This function may
   be called multiple times, and works as a stack.  */

স্থির শূন্য
c_disable_warnings (যৌক্তিক disable)
{
  যদি (disable)
    {
      ++c_inhibit_evaluation_warnings;
    }
}

/* If ENABLE is true, re-enable issuing warnings.  */

স্থির শূন্য
c_enable_warnings (যৌক্তিক enable)
{
  যদি (enable)
    {
      --c_inhibit_evaluation_warnings;
    }
}

/* Try to fold ARRAY_REF ary[index] if possible and not handled by
   normal fold, return NULL_TREE otherwise.  */

স্থির বৃক্ষ
c_fold_array_ref (বৃক্ষ type, বৃক্ষ ary, বৃক্ষ সূচক)
{
  যদি (বৃক্ষ_CODE (ary) != STRING_CST
      || বৃক্ষ_CODE (সূচক) != INTEGER_CST
      || বৃক্ষ_OVERFLOW (সূচক)
      || বৃক্ষ_CODE (বৃক্ষ_TYPE (ary)) != ARRAY_TYPE
      || !বৃক্ষ_fits_uhwi_p (সূচক))
    ফেরত NULL_বৃক্ষ;

  বৃক্ষ elem_type = বৃক্ষ_TYPE (বৃক্ষ_TYPE (ary));
  unsigned elem_nchars = (TYPE_PRECISION (elem_type)
			  / TYPE_PRECISION (char_type_গ্রন্থি));
  unsigned len = (unsigned) বৃক্ষ_STRING_দৈর্ঘ্য (ary) / elem_nchars;
  বৃক্ষ nelts_minus_one = array_type_nelts_minus_one (বৃক্ষ_TYPE (ary));
  যৌক্তিক dummy1 = সত্য, dummy2 = সত্য;
  nelts_minus_one = c_fully_fold_internal (nelts_minus_one, সত্য, &dummy1,
					   &dummy2, মিথ্যা, মিথ্যা);
  unsigned HOST_WIDE_INT i = বৃক্ষ_to_uhwi (সূচক);
  যদি (!বৃক্ষ_int_cst_le (সূচক, nelts_minus_one)
      || i >= len
      || i + elem_nchars > len)
    ফেরত NULL_বৃক্ষ;

  যদি (elem_nchars == 1)
    ফেরত build_int_cst (type, বৃক্ষ_STRING_POINTER (ary)[i]);

  ধ্রুবক unsigned অক্ষর *ptr
    = ((ধ্রুবক unsigned অক্ষর *)বৃক্ষ_STRING_POINTER (ary) + i * elem_nchars);
  ফেরত native_interpret_রাশিমালা (type, ptr, elem_nchars);
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
c_fully_fold (বৃক্ষ রাশিমালা, যৌক্তিক in_init, যৌক্তিক *maybe_const, যৌক্তিক lval)
{
  বৃক্ষ ret;
  বৃক্ষ eptype = NULL_বৃক্ষ;
  যৌক্তিক dummy = সত্য;
  যৌক্তিক maybe_const_itself = সত্য;
  location_t loc = রাশিমালা_LOCATION (রাশিমালা);

  যদি (!maybe_const)
    maybe_const = &dummy;
  যদি (বৃক্ষ_CODE (রাশিমালা) == EXCESS_PRECISION_রাশিমালা)
    {
      eptype = বৃক্ষ_TYPE (রাশিমালা);
      রাশিমালা = বৃক্ষ_OPERAND (রাশিমালা, 0);
    }
  ret = c_fully_fold_internal (রাশিমালা, in_init, maybe_const,
			       &maybe_const_itself, মিথ্যা, lval);
  যদি (eptype)
    ret = fold_convert_loc (loc, eptype, ret);
  *maybe_const &= maybe_const_itself;
  ফেরত ret;
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
c_fully_fold_internal (বৃক্ষ রাশিমালা, যৌক্তিক in_init, যৌক্তিক *maybe_const_operands,
		       যৌক্তিক *maybe_const_itself, যৌক্তিক for_int_const, যৌক্তিক lval)
{
  বৃক্ষ ret = রাশিমালা;
  গণনা বৃক্ষ_code code = বৃক্ষ_CODE (রাশিমালা);
  গণনা বৃক্ষ_code_class kind = বৃক্ষ_CODE_CLASS (code);
  location_t loc = রাশিমালা_LOCATION (রাশিমালা);
  বৃক্ষ op0, op1, op2, op3;
  বৃক্ষ orig_op0, orig_op1, orig_op2;
  যৌক্তিক op0_const = সত্য, op1_const = সত্য, op2_const = সত্য;
  যৌক্তিক op0_const_self = সত্য, op1_const_self = সত্য, op2_const_self = সত্য;
  যৌক্তিক nowarning = warning_suppressed_p (রাশিমালা, OPT_Woverflow);
  যৌক্তিক unused_p;
  যৌক্তিক op0_lval = মিথ্যা;
  source_range old_range;

  /* Constants, declarations, statements, errors, and anything else not
     counted as an expression cannot usefully be folded further at this
     point.  */
  যদি (!IS_রাশিমালা_CODE_CLASS (kind) || kind == tcc_statement)
    {
      /* Except for variables which we can optimize to its initializer.  */
      যদি (VAR_P (রাশিমালা) && !lval && (optimize || in_init))
	{
	  যদি (in_init)
	    ret = decl_constant_মান_1 (রাশিমালা, সত্য);
	  অন্যথা
	    {
	      ret = decl_constant_মান (রাশিমালা);
	      যদি (ret != রাশিমালা
		  && (TYPE_MODE (বৃক্ষ_TYPE (ret)) == BLKmode
		      || বৃক্ষ_CODE (বৃক্ষ_TYPE (ret)) == ARRAY_TYPE))
		ফেরত রাশিমালা;
	    }
	  /* Avoid unwanted tree sharing between the initializer and current
	     function's body where the tree can be modified e.g. by the
	     gimplifier.  */
	  যদি (ret != রাশিমালা && বৃক্ষ_STATIC (রাশিমালা))
	    ret = unshare_রাশিমালা (ret);
	  ফেরত ret;
	}
      ফেরত রাশিমালা;
    }

  যদি (IS_রাশিমালা_CODE_CLASS (kind))
    old_range = রাশিমালা_LOCATION_RANGE (রাশিমালা);

  /* Operands of variable-length expressions (function calls) have
     already been folded, as have __builtin_* function calls, and such
     expressions cannot occur in constant expressions.  */
  যদি (kind == tcc_vl_exp)
    {
      *maybe_const_operands = মিথ্যা;
      ret = fold (রাশিমালা);
      যাও out;
    }

  যদি (code == C_MAYBE_CONST_রাশিমালা)
    {
      বৃক্ষ pre = C_MAYBE_CONST_রাশিমালা_PRE (রাশিমালা);
      বৃক্ষ inner = C_MAYBE_CONST_রাশিমালা_রাশিমালা (রাশিমালা);
      যদি (C_MAYBE_CONST_রাশিমালা_NON_CONST (রাশিমালা))
	*maybe_const_operands = মিথ্যা;
      যদি (C_MAYBE_CONST_রাশিমালা_INT_OPERANDS (রাশিমালা))
	{
	  *maybe_const_itself = মিথ্যা;
	  inner = c_fully_fold_internal (inner, in_init, maybe_const_operands,
					 maybe_const_itself, সত্য, lval);
	}
      যদি (pre && !in_init)
	ret = build2 (COMPOUND_রাশিমালা, বৃক্ষ_TYPE (রাশিমালা), pre, inner);
      অন্যথা
	ret = inner;
      যাও out;
    }

  /* Assignment, increment, decrement, function call and comma
     operators, and statement expressions, cannot occur in constant
     expressions if evaluated / outside of sizeof.  (Function calls
     were handled above, though VA_ARG_EXPR is treated like a function
     call here, and statement expressions are handled through
     C_MAYBE_CONST_EXPR to avoid folding inside them.)  */
  নির্বাচন (code)
    {
    ক্ষেত্র MODIFY_রাশিমালা:
    ক্ষেত্র PREDECREMENT_রাশিমালা:
    ক্ষেত্র PREINCREMENT_রাশিমালা:
    ক্ষেত্র POSTDECREMENT_রাশিমালা:
    ক্ষেত্র POSTINCREMENT_রাশিমালা:
    ক্ষেত্র COMPOUND_রাশিমালা:
      *maybe_const_operands = মিথ্যা;
      বিরতি;

    ক্ষেত্র VA_ARG_রাশিমালা:
    ক্ষেত্র TARGET_রাশিমালা:
    ক্ষেত্র BIND_রাশিমালা:
    ক্ষেত্র OBJ_TYPE_REF:
      *maybe_const_operands = মিথ্যা;
      ret = fold (রাশিমালা);
      যাও out;

    পূর্বনির্ধারিত:
      বিরতি;
    }

  /* Fold individual tree codes as appropriate.  */
  নির্বাচন (code)
    {
    ক্ষেত্র COMPOUND_LITERAL_রাশিমালা:
      /* Any non-constancy will have been marked in a containing
	 C_MAYBE_CONST_EXPR; there is no more folding to do here.  */
      যাও out;

    ক্ষেত্র COMPONENT_REF:
      orig_op0 = op0 = বৃক্ষ_OPERAND (রাশিমালা, 0);
      op1 = বৃক্ষ_OPERAND (রাশিমালা, 1);
      op2 = বৃক্ষ_OPERAND (রাশিমালা, 2);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, lval);
      STRIP_TYPE_NOPS (op0);
      যদি (op0 != orig_op0)
	ret = build3 (COMPONENT_REF, বৃক্ষ_TYPE (রাশিমালা), op0, op1, op2);
      যদি (ret != রাশিমালা)
	{
	  বৃক্ষ_READONLY (ret) = বৃক্ষ_READONLY (রাশিমালা);
	  বৃক্ষ_THIS_VOLATILE (ret) = বৃক্ষ_THIS_VOLATILE (রাশিমালা);
	}
      যদি (!lval)
	ret = fold (ret);
      যাও out;

    ক্ষেত্র ARRAY_REF:
      orig_op0 = op0 = বৃক্ষ_OPERAND (রাশিমালা, 0);
      orig_op1 = op1 = বৃক্ষ_OPERAND (রাশিমালা, 1);
      op2 = বৃক্ষ_OPERAND (রাশিমালা, 2);
      op3 = বৃক্ষ_OPERAND (রাশিমালা, 3);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, lval);
      STRIP_TYPE_NOPS (op0);
      op1 = c_fully_fold_internal (op1, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, মিথ্যা);
      STRIP_TYPE_NOPS (op1);
      /* Fold "foo"[2] in initializers.  */
      যদি (!lval && in_init)
	{
	  ret = c_fold_array_ref (বৃক্ষ_TYPE (রাশিমালা), op0, op1);
	  যদি (ret)
	    যাও out;
	  ret = রাশিমালা;
	}
      যদি (op0 != orig_op0 || op1 != orig_op1)
	ret = build4 (ARRAY_REF, বৃক্ষ_TYPE (রাশিমালা), op0, op1, op2, op3);
      যদি (ret != রাশিমালা)
	{
	  বৃক্ষ_READONLY (ret) = বৃক্ষ_READONLY (রাশিমালা);
	  বৃক্ষ_SIDE_EFFECTS (ret) = বৃক্ষ_SIDE_EFFECTS (রাশিমালা);
	  বৃক্ষ_THIS_VOLATILE (ret) = বৃক্ষ_THIS_VOLATILE (রাশিমালা);
	}
      যদি (!lval)
	ret = fold (ret);
      যাও out;

    ক্ষেত্র MODIFY_রাশিমালা:
    ক্ষেত্র PREDECREMENT_রাশিমালা:
    ক্ষেত্র PREINCREMENT_রাশিমালা:
    ক্ষেত্র POSTDECREMENT_রাশিমালা:
    ক্ষেত্র POSTINCREMENT_রাশিমালা:
      op0_lval = সত্য;
      /* FALLTHRU */
    ক্ষেত্র COMPOUND_রাশিমালা:
    ক্ষেত্র PLUS_রাশিমালা:
    ক্ষেত্র MINUS_রাশিমালা:
    ক্ষেত্র MULT_রাশিমালা:
    ক্ষেত্র POINTER_PLUS_রাশিমালা:
    ক্ষেত্র POINTER_DIFF_রাশিমালা:
    ক্ষেত্র TRUNC_DIV_রাশিমালা:
    ক্ষেত্র CEIL_DIV_রাশিমালা:
    ক্ষেত্র FLOOR_DIV_রাশিমালা:
    ক্ষেত্র TRUNC_MOD_রাশিমালা:
    ক্ষেত্র RDIV_রাশিমালা:
    ক্ষেত্র EXACT_DIV_রাশিমালা:
    ক্ষেত্র LSHIFT_রাশিমালা:
    ক্ষেত্র RSHIFT_রাশিমালা:
    ক্ষেত্র LROTATE_রাশিমালা:
    ক্ষেত্র RROTATE_রাশিমালা:
    ক্ষেত্র BIT_IOR_রাশিমালা:
    ক্ষেত্র BIT_XOR_রাশিমালা:
    ক্ষেত্র BIT_AND_রাশিমালা:
    ক্ষেত্র LT_রাশিমালা:
    ক্ষেত্র LE_রাশিমালা:
    ক্ষেত্র GT_রাশিমালা:
    ক্ষেত্র GE_রাশিমালা:
    ক্ষেত্র EQ_রাশিমালা:
    ক্ষেত্র NE_রাশিমালা:
    ক্ষেত্র COMPLEX_রাশিমালা:
    ক্ষেত্র TRUTH_AND_রাশিমালা:
    ক্ষেত্র TRUTH_OR_রাশিমালা:
    ক্ষেত্র TRUTH_XOR_রাশিমালা:
    ক্ষেত্র UNORDERED_রাশিমালা:
    ক্ষেত্র ORDERED_রাশিমালা:
    ক্ষেত্র UNLT_রাশিমালা:
    ক্ষেত্র UNLE_রাশিমালা:
    ক্ষেত্র UNGT_রাশিমালা:
    ক্ষেত্র UNGE_রাশিমালা:
    ক্ষেত্র UNEQ_রাশিমালা:
    ক্ষেত্র MEM_REF:
      /* Binary operations evaluating both arguments (increment and
	 decrement are binary internally in GCC).  */
      orig_op0 = op0 = বৃক্ষ_OPERAND (রাশিমালা, 0);
      orig_op1 = op1 = বৃক্ষ_OPERAND (রাশিমালা, 1);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const,
				   op0_lval);
      STRIP_TYPE_NOPS (op0);
      /* The RHS of a MODIFY_EXPR was fully folded when building that
	 expression for the sake of conversion warnings.  */
      যদি (code != MODIFY_রাশিমালা)
	op1 = c_fully_fold_internal (op1, in_init, maybe_const_operands,
				     maybe_const_itself, for_int_const, মিথ্যা);
      STRIP_TYPE_NOPS (op1);

      যদি (for_int_const && (বৃক্ষ_CODE (op0) != INTEGER_CST
			    || বৃক্ষ_CODE (op1) != INTEGER_CST))
	যাও out;

      যদি (বৃক্ষ_CODE_CLASS (code) == tcc_comparison
	  && বৃক্ষ_CODE (বৃক্ষ_TYPE (op0)) == NULLPTR_TYPE
	  && বৃক্ষ_CODE (বৃক্ষ_TYPE (op1)) == NULLPTR_TYPE)
	{
	  নির্বাচন (code)
	    {
	    ক্ষেত্র EQ_রাশিমালা:
	      ret = constant_boolean_গ্রন্থি (সত্য, বৃক্ষ_TYPE (রাশিমালা));
	      বিরতি;
	    ক্ষেত্র NE_রাশিমালা:
	      ret = constant_boolean_গ্রন্থি (মিথ্যা, বৃক্ষ_TYPE (রাশিমালা));
	      বিরতি;
	    পূর্বনির্ধারিত:
	      gcc_unreachable ();
	    }
	  ret = omit_two_operands_loc (loc, বৃক্ষ_TYPE (রাশিমালা), ret,
				       op0, op1);
	}
      অন্যথা যদি (op0 != orig_op0 || op1 != orig_op1 || in_init)
	ret = in_init
	  ? fold_build2_initializer_loc (loc, code, বৃক্ষ_TYPE (রাশিমালা), op0, op1)
	  : fold_build2_loc (loc, code, বৃক্ষ_TYPE (রাশিমালা), op0, op1);
      অন্যথা
	ret = fold (রাশিমালা);
      যদি (বৃক্ষ_OVERFLOW_P (ret)
	  && !বৃক্ষ_OVERFLOW_P (op0)
	  && !(দ্বিমিক_CLASS_P (op0) && বৃক্ষ_OVERFLOW_P (বৃক্ষ_OPERAND (op0, 1)))
	  && !বৃক্ষ_OVERFLOW_P (op1))
	overflow_warning (রাশিমালা_LOC_OR_LOC (রাশিমালা, প্রবেশ_location), ret, রাশিমালা);
      যদি (code == LSHIFT_রাশিমালা
	  && বৃক্ষ_CODE (orig_op0) != INTEGER_CST
	  && (বৃক্ষ_CODE (বৃক্ষ_TYPE (orig_op0)) == INTEGER_TYPE
	      || বৃক্ষ_CODE (বৃক্ষ_TYPE (orig_op0)) == BITINT_TYPE)
	  && বৃক্ষ_CODE (op0) == INTEGER_CST
	  && c_inhibit_evaluation_warnings == 0
	  && !TYPE_OVERFLOW_WRAPS (বৃক্ষ_TYPE (orig_op0))
	  && বৃক্ষ_int_cst_sgn (op0) < 0)
	warning_at (loc, OPT_Wshift_negative_মান,
		    "left shift of negative value");
      যদি ((code == LSHIFT_রাশিমালা
	   || code == RSHIFT_রাশিমালা
	   || code == LROTATE_রাশিমালা
	   || code == RROTATE_রাশিমালা)
	  && বৃক্ষ_CODE (orig_op1) != INTEGER_CST
	  && বৃক্ষ_CODE (op1) == INTEGER_CST
	  && বৃক্ষ_CODE (বৃক্ষ_TYPE (orig_op1)) == INTEGER_TYPE
	  && c_inhibit_evaluation_warnings == 0)
	{
	  যদি (বৃক্ষ_int_cst_sgn (op1) < 0)
	    warning_at (loc, OPT_Wshift_গুনতি_negative,
			(code == LSHIFT_রাশিমালা
			 ? G_("left shift count is negative")
			 : G_("right shift count is negative")));
	  অন্যথা যদি ((বৃক্ষ_CODE (বৃক্ষ_TYPE (orig_op0)) == INTEGER_TYPE
		    || বৃক্ষ_CODE (বৃক্ষ_TYPE (orig_op0)) == BITINT_TYPE
		    || বৃক্ষ_CODE (বৃক্ষ_TYPE (orig_op0)) == FIXED_POINT_TYPE)
		   && compare_বৃক্ষ_int (op1,
					TYPE_PRECISION (বৃক্ষ_TYPE (orig_op0)))
		      >= 0
		   && !warning_suppressed_p (রাশিমালা, OPT_Wshift_গুনতি_overflow))
	    warning_at (loc, OPT_Wshift_গুনতি_overflow,
			(code == LSHIFT_রাশিমালা
			 ? G_("left shift count >= width of type")
			 : G_("right shift count >= width of type")));
	  অন্যথা যদি (বৃক্ষ_CODE (বৃক্ষ_TYPE (orig_op0)) == VECTOR_TYPE
		   && compare_বৃক্ষ_int (op1,
					TYPE_PRECISION (বৃক্ষ_TYPE (বৃক্ষ_TYPE (orig_op0))))
		      >= 0)
	    warning_at (loc, OPT_Wshift_গুনতি_overflow,
			code == LSHIFT_রাশিমালা
			? G_("left shift count >= width of vector element")
			: G_("right shift count >= width of vector element"));
	}
      যদি (code == LSHIFT_রাশিমালা
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
      যদি ((code == TRUNC_DIV_রাশিমালা
	   || code == CEIL_DIV_রাশিমালা
	   || code == FLOOR_DIV_রাশিমালা
	   || code == EXACT_DIV_রাশিমালা
	   || code == TRUNC_MOD_রাশিমালা)
	  && বৃক্ষ_CODE (orig_op1) != INTEGER_CST
	  && বৃক্ষ_CODE (op1) == INTEGER_CST
	  && (বৃক্ষ_CODE (বৃক্ষ_TYPE (orig_op0)) == INTEGER_TYPE
	      || বৃক্ষ_CODE (বৃক্ষ_TYPE (orig_op0)) == BITINT_TYPE
	      || বৃক্ষ_CODE (বৃক্ষ_TYPE (orig_op0)) == FIXED_POINT_TYPE)
	  && (বৃক্ষ_CODE (বৃক্ষ_TYPE (orig_op1)) == INTEGER_TYPE
	      || বৃক্ষ_CODE (বৃক্ষ_TYPE (orig_op1)) == BITINT_TYPE))
	warn_for_div_by_zero (loc, op1);
      যদি (code == MEM_REF
	  && ret != রাশিমালা
	  && বৃক্ষ_CODE (ret) == MEM_REF)
	{
	  বৃক্ষ_READONLY (ret) = বৃক্ষ_READONLY (রাশিমালা);
	  বৃক্ষ_SIDE_EFFECTS (ret) = বৃক্ষ_SIDE_EFFECTS (রাশিমালা);
	  বৃক্ষ_THIS_VOLATILE (ret) = বৃক্ষ_THIS_VOLATILE (রাশিমালা);
	}
      যাও out;

    ক্ষেত্র ADDR_রাশিমালা:
      op0_lval = সত্য;
      যাও unary;
    ক্ষেত্র REALPART_রাশিমালা:
    ক্ষেত্র IMAGPART_রাশিমালা:
    ক্ষেত্র VIEW_CONVERT_রাশিমালা:
      op0_lval = lval;
      /* FALLTHRU */
    ক্ষেত্র INDIRECT_REF:
    ক্ষেত্র FIX_TRUNC_রাশিমালা:
    ক্ষেত্র FLOAT_রাশিমালা:
    CASE_CONVERT:
    ক্ষেত্র ADDR_SPACE_CONVERT_রাশিমালা:
    ক্ষেত্র NON_LVALUE_রাশিমালা:
    ক্ষেত্র NEGATE_রাশিমালা:
    ক্ষেত্র BIT_NOT_রাশিমালা:
    ক্ষেত্র TRUTH_NOT_রাশিমালা:
    ক্ষেত্র CONJ_রাশিমালা:
    ক্ষেত্র PAREN_রাশিমালা:
    unary:
      /* Unary operations.  */
      orig_op0 = op0 = বৃক্ষ_OPERAND (রাশিমালা, 0);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const,
				   op0_lval);
      STRIP_TYPE_NOPS (op0);

      যদি (for_int_const && বৃক্ষ_CODE (op0) != INTEGER_CST)
	যাও out;

      /* ??? Cope with user tricks that amount to offsetof.  The middle-end is
	 not prepared to deal with them if they occur in initializers.  */
      যদি (op0 != orig_op0
	  && code == ADDR_রাশিমালা
	  && (op1 = get_base_address (op0)) != NULL_বৃক্ষ
	  && INDIRECT_REF_P (op1)
	  && বৃক্ষ_CONSTANT (বৃক্ষ_OPERAND (op1, 0)))
	ret = fold_offsetof (op0, বৃক্ষ_TYPE (রাশিমালা));
      অন্যথা যদি (op0 != orig_op0 || in_init)
	ret = in_init
	  ? fold_build1_initializer_loc (loc, code, বৃক্ষ_TYPE (রাশিমালা), op0)
	  : fold_build1_loc (loc, code, বৃক্ষ_TYPE (রাশিমালা), op0);
      অন্যথা
	ret = fold (রাশিমালা);
      যদি (code == INDIRECT_REF
	  && ret != রাশিমালা
	  && INDIRECT_REF_P (ret))
	{
	  বৃক্ষ_READONLY (ret) = বৃক্ষ_READONLY (রাশিমালা);
	  বৃক্ষ_SIDE_EFFECTS (ret) = বৃক্ষ_SIDE_EFFECTS (রাশিমালা);
	  বৃক্ষ_THIS_VOLATILE (ret) = বৃক্ষ_THIS_VOLATILE (রাশিমালা);
	}
      নির্বাচন (code)
	{
	ক্ষেত্র FIX_TRUNC_রাশিমালা:
	ক্ষেত্র FLOAT_রাশিমালা:
	CASE_CONVERT:
	  /* Don't warn about explicit conversions.  We will already
	     have warned about suspect implicit conversions.  */
	  বিরতি;

	পূর্বনির্ধারিত:
	  যদি (বৃক্ষ_OVERFLOW_P (ret) && !বৃক্ষ_OVERFLOW_P (op0))
	    overflow_warning (রাশিমালা_LOCATION (রাশিমালা), ret, op0);
	  বিরতি;
	}
      যাও out;

    ক্ষেত্র TRUTH_ANDIF_রাশিমালা:
    ক্ষেত্র TRUTH_ORIF_রাশিমালা:
      /* Binary operations not necessarily evaluating both
	 arguments.  */
      orig_op0 = op0 = বৃক্ষ_OPERAND (রাশিমালা, 0);
      orig_op1 = op1 = বৃক্ষ_OPERAND (রাশিমালা, 1);
      op0 = c_fully_fold_internal (op0, in_init, &op0_const, &op0_const_self,
				   for_int_const, মিথ্যা);
      STRIP_TYPE_NOPS (op0);

      unused_p = (op0 == (code == TRUTH_ANDIF_রাশিমালা
			  ? truthvalue_false_গ্রন্থি
			  : truthvalue_true_গ্রন্থি));
      c_disable_warnings (unused_p);
      op1 = c_fully_fold_internal (op1, in_init, &op1_const, &op1_const_self,
				   for_int_const, মিথ্যা);
      STRIP_TYPE_NOPS (op1);
      c_enable_warnings (unused_p);

      যদি (for_int_const
	  && (বৃক্ষ_CODE (op0) != INTEGER_CST
	      /* Require OP1 be an INTEGER_CST only if it's evaluated.  */
	      || (!unused_p && বৃক্ষ_CODE (op1) != INTEGER_CST)))
	যাও out;

      যদি (op0 != orig_op0 || op1 != orig_op1 || in_init)
	ret = in_init
	  ? fold_build2_initializer_loc (loc, code, বৃক্ষ_TYPE (রাশিমালা), op0, op1)
	  : fold_build2_loc (loc, code, বৃক্ষ_TYPE (রাশিমালা), op0, op1);
      অন্যথা
	ret = fold (রাশিমালা);
      *maybe_const_operands &= op0_const;
      *maybe_const_itself &= op0_const_self;
      যদি (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && (code == TRUTH_ANDIF_রাশিমালা
		? op0 == truthvalue_false_গ্রন্থি
		: op0 == truthvalue_true_গ্রন্থি)))
	*maybe_const_operands &= op1_const;
      যদি (!(op0_const
	    && op0_const_self
	    && (code == TRUTH_ANDIF_রাশিমালা
		? op0 == truthvalue_false_গ্রন্থি
		: op0 == truthvalue_true_গ্রন্থি)))
	*maybe_const_itself &= op1_const_self;
      যাও out;

    ক্ষেত্র COND_রাশিমালা:
      orig_op0 = op0 = বৃক্ষ_OPERAND (রাশিমালা, 0);
      orig_op1 = op1 = বৃক্ষ_OPERAND (রাশিমালা, 1);
      orig_op2 = op2 = বৃক্ষ_OPERAND (রাশিমালা, 2);
      op0 = c_fully_fold_internal (op0, in_init, &op0_const, &op0_const_self,
				   for_int_const, মিথ্যা);

      STRIP_TYPE_NOPS (op0);
      c_disable_warnings (op0 == truthvalue_false_গ্রন্থি);
      op1 = c_fully_fold_internal (op1, in_init, &op1_const, &op1_const_self,
				   for_int_const, মিথ্যা);
      STRIP_TYPE_NOPS (op1);
      c_enable_warnings (op0 == truthvalue_false_গ্রন্থি);

      c_disable_warnings (op0 == truthvalue_true_গ্রন্থি);
      op2 = c_fully_fold_internal (op2, in_init, &op2_const, &op2_const_self,
				   for_int_const, মিথ্যা);
      STRIP_TYPE_NOPS (op2);
      c_enable_warnings (op0 == truthvalue_true_গ্রন্থি);

      যদি (for_int_const
	  && (বৃক্ষ_CODE (op0) != INTEGER_CST
	      /* Only the evaluated operand must be an INTEGER_CST.  */
	      || (op0 == truthvalue_true_গ্রন্থি
		  ? বৃক্ষ_CODE (op1) != INTEGER_CST
		  : বৃক্ষ_CODE (op2) != INTEGER_CST)))
	যাও out;

      যদি (op0 != orig_op0 || op1 != orig_op1 || op2 != orig_op2)
	ret = fold_build3_loc (loc, code, বৃক্ষ_TYPE (রাশিমালা), op0, op1, op2);
      অন্যথা
	ret = fold (রাশিমালা);
      *maybe_const_operands &= op0_const;
      *maybe_const_itself &= op0_const_self;
      যদি (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && op0 == truthvalue_false_গ্রন্থি))
	*maybe_const_operands &= op1_const;
      যদি (!(op0_const
	    && op0_const_self
	    && op0 == truthvalue_false_গ্রন্থি))
	*maybe_const_itself &= op1_const_self;
      যদি (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && op0 == truthvalue_true_গ্রন্থি))
	*maybe_const_operands &= op2_const;
      যদি (!(op0_const
	    && op0_const_self
	    && op0 == truthvalue_true_গ্রন্থি))
	*maybe_const_itself &= op2_const_self;
      যাও out;

    ক্ষেত্র VEC_COND_রাশিমালা:
      orig_op0 = op0 = বৃক্ষ_OPERAND (রাশিমালা, 0);
      orig_op1 = op1 = বৃক্ষ_OPERAND (রাশিমালা, 1);
      orig_op2 = op2 = বৃক্ষ_OPERAND (রাশিমালা, 2);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, মিথ্যা);
      STRIP_TYPE_NOPS (op0);
      op1 = c_fully_fold_internal (op1, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, মিথ্যা);
      STRIP_TYPE_NOPS (op1);
      op2 = c_fully_fold_internal (op2, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, মিথ্যা);
      STRIP_TYPE_NOPS (op2);

      যদি (op0 != orig_op0 || op1 != orig_op1 || op2 != orig_op2)
	ret = fold_build3_loc (loc, code, বৃক্ষ_TYPE (রাশিমালা), op0, op1, op2);
      অন্যথা
	ret = fold (রাশিমালা);
      যাও out;

    ক্ষেত্র EXCESS_PRECISION_রাশিমালা:
      /* Each case where an operand with excess precision may be
	 encountered must remove the EXCESS_PRECISION_EXPR around
	 inner operands and possibly put one around the whole
	 expression or possibly convert to the semantic type (which
	 c_fully_fold does); we cannot tell at this stage which is
	 appropriate in any particular case.  */
      gcc_unreachable ();

    ক্ষেত্র SAVE_রাশিমালা:
      /* Make sure to fold the contents of a SAVE_EXPR exactly once.  */
      op0 = বৃক্ষ_OPERAND (রাশিমালা, 0);
      যদি (!SAVE_রাশিমালা_FOLDED_P (রাশিমালা))
	{
	  op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				       maybe_const_itself, for_int_const,
				       মিথ্যা);
	  বৃক্ষ_OPERAND (রাশিমালা, 0) = op0;
	  SAVE_রাশিমালা_FOLDED_P (রাশিমালা) = সত্য;
	}
      /* Return the SAVE_EXPR operand if it is invariant.  */
      যদি (বৃক্ষ_invariant_p (op0))
	ret = op0;
      যাও out;

    পূর্বনির্ধারিত:
      /* Various codes may appear through folding built-in functions
	 and their arguments.  */
      যাও out;
    }

 out:
  /* Some folding may introduce NON_LVALUE_EXPRs; all lvalue checks
     have been done by this point, so remove them again.  */
  nowarning |= warning_suppressed_p (ret, OPT_Woverflow);
  STRIP_TYPE_NOPS (ret);
  যদি (nowarning && !warning_suppressed_p (ret, OPT_Woverflow))
    {
      যদি (!CAN_HAVE_LOCATION_P (ret))
	ret = build1 (NOP_রাশিমালা, বৃক্ষ_TYPE (ret), ret);
      suppress_warning (ret, OPT_Woverflow);
    }
  যদি (ret != রাশিমালা)
    {
      protected_set_রাশিমালা_location (ret, loc);
      যদি (IS_রাশিমালা_CODE_CLASS (kind))
	set_source_range (ret, old_range.m_start, old_range.m_finish);
    }
  ফেরত ret;
}

/* Fold X for consideration by one of the warning functions when checking
   whether an expression has a constant value.  */

বৃক্ষ
fold_for_warn (বৃক্ষ x)
{
  /* The C front-end has already folded X appropriately.  */
  ফেরত x;
}
