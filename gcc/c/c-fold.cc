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

#अन्तर्भाव "config.h"
#अन्तर्भाव "system.h"
#अन्तर्भाव "coretypes.h"
#अन्तर्भाव "target.h"
#अन्तर्भाव "function.h"
#अन्तर्भाव "bitmap.h"
#अन्तर्भाव "c-tree.h"
#अन्तर्भाव "intl.h"
#अन्तर्भाव "gimplify.h"

स्थिर वृक्षः c_fully_fold_internal (वृक्षः व्यञ्जकम्, तार्किक, तार्किक *, तार्किक *, तार्किक,
				   तार्किक);

/* If DISABLE is true, stop issuing warnings.  This is used when
   parsing code that we know will not be executed.  This function may
   be called multiple times, and works as a stack.  */

स्थिर शून्य
c_disable_warnings (तार्किक disable)
{
  सचे (disable)
    {
      ++c_inhibit_evaluation_warnings;
    }
}

/* If ENABLE is true, re-enable issuing warnings.  */

स्थिर शून्य
c_enable_warnings (तार्किक enable)
{
  सचे (enable)
    {
      --c_inhibit_evaluation_warnings;
    }
}

/* Try to fold ARRAY_REF ary[index] if possible and not handled by
   normal fold, return NULL_TREE otherwise.  */

स्थिर वृक्षः
c_fold_array_ref (वृक्षः type, वृक्षः ary, वृक्षः index)
{
  सचे (वृक्षः_CODE (ary) != STRING_CST
      || वृक्षः_CODE (index) != INTEGER_CST
      || वृक्षः_OVERFLOW (index)
      || वृक्षः_CODE (वृक्षः_TYPE (ary)) != ARRAY_TYPE
      || !वृक्षः_fits_uhwi_p (index))
    पटिनिवत्त NULL_वृक्षः;

  वृक्षः elem_type = वृक्षः_TYPE (वृक्षः_TYPE (ary));
  unsigned elem_nchars = (TYPE_PRECISION (elem_type)
			  / TYPE_PRECISION (char_type_ग्रन्थिः));
  unsigned len = (unsigned) वृक्षः_STRING_LENGTH (ary) / elem_nchars;
  वृक्षः nelts_minus_one = array_type_nelts_minus_one (वृक्षः_TYPE (ary));
  तार्किक dummy1 = सच्च, dummy2 = सच्च;
  nelts_minus_one = c_fully_fold_internal (nelts_minus_one, सच्च, &dummy1,
					   &dummy2, मिच्छा, मिच्छा);
  unsigned HOST_WIDE_INT i = वृक्षः_to_uhwi (index);
  सचे (!वृक्षः_int_cst_le (index, nelts_minus_one)
      || i >= len
      || i + elem_nchars > len)
    पटिनिवत्त NULL_वृक्षः;

  सचे (elem_nchars == 1)
    पटिनिवत्त build_int_cst (type, वृक्षः_STRING_POINTER (ary)[i]);

  ध्रुव unsigned वर्ण *ptr
    = ((ध्रुव unsigned वर्ण *)वृक्षः_STRING_POINTER (ary) + i * elem_nchars);
  पटिनिवत्त native_interpret_व्यञ्जकम् (type, ptr, elem_nchars);
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

वृक्षः
c_fully_fold (वृक्षः व्यञ्जकम्, तार्किक in_init, तार्किक *maybe_const, तार्किक lval)
{
  वृक्षः ret;
  वृक्षः eptype = NULL_वृक्षः;
  तार्किक dummy = सच्च;
  तार्किक maybe_const_itself = सच्च;
  location_t loc = व्यञ्जकम्_LOCATION (व्यञ्जकम्);

  सचे (!maybe_const)
    maybe_const = &dummy;
  सचे (वृक्षः_CODE (व्यञ्जकम्) == EXCESS_PRECISION_व्यञ्जकम्)
    {
      eptype = वृक्षः_TYPE (व्यञ्जकम्);
      व्यञ्जकम् = वृक्षः_OPERAND (व्यञ्जकम्, 0);
    }
  ret = c_fully_fold_internal (व्यञ्जकम्, in_init, maybe_const,
			       &maybe_const_itself, मिच्छा, lval);
  सचे (eptype)
    ret = fold_convert_loc (loc, eptype, ret);
  *maybe_const &= maybe_const_itself;
  पटिनिवत्त ret;
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

स्थिर वृक्षः
c_fully_fold_internal (वृक्षः व्यञ्जकम्, तार्किक in_init, तार्किक *maybe_const_operands,
		       तार्किक *maybe_const_itself, तार्किक for_int_const, तार्किक lval)
{
  वृक्षः ret = व्यञ्जकम्;
  गणना वृक्षः_code code = वृक्षः_CODE (व्यञ्जकम्);
  गणना वृक्षः_code_class kind = वृक्षः_CODE_CLASS (code);
  location_t loc = व्यञ्जकम्_LOCATION (व्यञ्जकम्);
  वृक्षः op0, op1, op2, op3;
  वृक्षः orig_op0, orig_op1, orig_op2;
  तार्किक op0_const = सच्च, op1_const = सच्च, op2_const = सच्च;
  तार्किक op0_const_self = सच्च, op1_const_self = सच्च, op2_const_self = सच्च;
  तार्किक nowarning = warning_suppressed_p (व्यञ्जकम्, OPT_Woverflow);
  तार्किक unused_p;
  तार्किक op0_lval = मिच्छा;
  source_range old_range;

  /* Constants, declarations, statements, errors, and anything else not
     counted as an expression cannot usefully be folded further at this
     point.  */
  सचे (!IS_व्यञ्जकम्_CODE_CLASS (kind) || kind == tcc_statement)
    {
      /* Except for variables which we can optimize to its initializer.  */
      सचे (VAR_P (व्यञ्जकम्) && !lval && (optimize || in_init))
	{
	  सचे (in_init)
	    ret = decl_constant_मानम्_1 (व्यञ्जकम्, सच्च);
	  अञ्ञथा
	    {
	      ret = decl_constant_मानम् (व्यञ्जकम्);
	      सचे (ret != व्यञ्जकम्
		  && (TYPE_MODE (वृक्षः_TYPE (ret)) == BLKmode
		      || वृक्षः_CODE (वृक्षः_TYPE (ret)) == ARRAY_TYPE))
		पटिनिवत्त व्यञ्जकम्;
	    }
	  /* Avoid unwanted tree sharing between the initializer and current
	     function's body where the tree can be modified e.g. by the
	     gimplifier.  */
	  सचे (ret != व्यञ्जकम् && वृक्षः_STATIC (व्यञ्जकम्))
	    ret = unshare_व्यञ्जकम् (ret);
	  पटिनिवत्त ret;
	}
      पटिनिवत्त व्यञ्जकम्;
    }

  सचे (IS_व्यञ्जकम्_CODE_CLASS (kind))
    old_range = व्यञ्जकम्_LOCATION_RANGE (व्यञ्जकम्);

  /* Operands of variable-length expressions (function calls) have
     already been folded, as have __builtin_* function calls, and such
     expressions cannot occur in constant expressions.  */
  सचे (kind == tcc_vl_exp)
    {
      *maybe_const_operands = मिच्छा;
      ret = fold (व्यञ्जकम्);
      गच्छ out;
    }

  सचे (code == C_MAYBE_CONST_व्यञ्जकम्)
    {
      वृक्षः pre = C_MAYBE_CONST_व्यञ्जकम्_PRE (व्यञ्जकम्);
      वृक्षः inner = C_MAYBE_CONST_व्यञ्जकम्_व्यञ्जकम् (व्यञ्जकम्);
      सचे (C_MAYBE_CONST_व्यञ्जकम्_NON_CONST (व्यञ्जकम्))
	*maybe_const_operands = मिच्छा;
      सचे (C_MAYBE_CONST_व्यञ्जकम्_INT_OPERANDS (व्यञ्जकम्))
	{
	  *maybe_const_itself = मिच्छा;
	  inner = c_fully_fold_internal (inner, in_init, maybe_const_operands,
					 maybe_const_itself, सच्च, lval);
	}
      सचे (pre && !in_init)
	ret = build2 (COMPOUND_व्यञ्जकम्, वृक्षः_TYPE (व्यञ्जकम्), pre, inner);
      अञ्ञथा
	ret = inner;
      गच्छ out;
    }

  /* Assignment, increment, decrement, function call and comma
     operators, and statement expressions, cannot occur in constant
     expressions if evaluated / outside of sizeof.  (Function calls
     were handled above, though VA_ARG_EXPR is treated like a function
     call here, and statement expressions are handled through
     C_MAYBE_CONST_EXPR to avoid folding inside them.)  */
  विकल्प (code)
    {
    पक्ष MODIFY_व्यञ्जकम्:
    पक्ष PREDECREMENT_व्यञ्जकम्:
    पक्ष PREINCREMENT_व्यञ्जकम्:
    पक्ष POSTDECREMENT_व्यञ्जकम्:
    पक्ष POSTINCREMENT_व्यञ्जकम्:
    पक्ष COMPOUND_व्यञ्जकम्:
      *maybe_const_operands = मिच्छा;
      भङ्ग;

    पक्ष VA_ARG_व्यञ्जकम्:
    पक्ष TARGET_व्यञ्जकम्:
    पक्ष BIND_व्यञ्जकम्:
    पक्ष OBJ_TYPE_REF:
      *maybe_const_operands = मिच्छा;
      ret = fold (व्यञ्जकम्);
      गच्छ out;

    स्वभाव:
      भङ्ग;
    }

  /* Fold individual tree codes as appropriate.  */
  विकल्प (code)
    {
    पक्ष COMPOUND_LITERAL_व्यञ्जकम्:
      /* Any non-constancy will have been marked in a containing
	 C_MAYBE_CONST_EXPR; there is no more folding to do here.  */
      गच्छ out;

    पक्ष COMPONENT_REF:
      orig_op0 = op0 = वृक्षः_OPERAND (व्यञ्जकम्, 0);
      op1 = वृक्षः_OPERAND (व्यञ्जकम्, 1);
      op2 = वृक्षः_OPERAND (व्यञ्जकम्, 2);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, lval);
      STRIP_TYPE_NOPS (op0);
      सचे (op0 != orig_op0)
	ret = build3 (COMPONENT_REF, वृक्षः_TYPE (व्यञ्जकम्), op0, op1, op2);
      सचे (ret != व्यञ्जकम्)
	{
	  वृक्षः_READONLY (ret) = वृक्षः_READONLY (व्यञ्जकम्);
	  वृक्षः_THIS_VOLATILE (ret) = वृक्षः_THIS_VOLATILE (व्यञ्जकम्);
	}
      सचे (!lval)
	ret = fold (ret);
      गच्छ out;

    पक्ष ARRAY_REF:
      orig_op0 = op0 = वृक्षः_OPERAND (व्यञ्जकम्, 0);
      orig_op1 = op1 = वृक्षः_OPERAND (व्यञ्जकम्, 1);
      op2 = वृक्षः_OPERAND (व्यञ्जकम्, 2);
      op3 = वृक्षः_OPERAND (व्यञ्जकम्, 3);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, lval);
      STRIP_TYPE_NOPS (op0);
      op1 = c_fully_fold_internal (op1, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, मिच्छा);
      STRIP_TYPE_NOPS (op1);
      /* Fold "foo"[2] in initializers.  */
      सचे (!lval && in_init)
	{
	  ret = c_fold_array_ref (वृक्षः_TYPE (व्यञ्जकम्), op0, op1);
	  सचे (ret)
	    गच्छ out;
	  ret = व्यञ्जकम्;
	}
      सचे (op0 != orig_op0 || op1 != orig_op1)
	ret = build4 (ARRAY_REF, वृक्षः_TYPE (व्यञ्जकम्), op0, op1, op2, op3);
      सचे (ret != व्यञ्जकम्)
	{
	  वृक्षः_READONLY (ret) = वृक्षः_READONLY (व्यञ्जकम्);
	  वृक्षः_SIDE_EFFECTS (ret) = वृक्षः_SIDE_EFFECTS (व्यञ्जकम्);
	  वृक्षः_THIS_VOLATILE (ret) = वृक्षः_THIS_VOLATILE (व्यञ्जकम्);
	}
      सचे (!lval)
	ret = fold (ret);
      गच्छ out;

    पक्ष MODIFY_व्यञ्जकम्:
    पक्ष PREDECREMENT_व्यञ्जकम्:
    पक्ष PREINCREMENT_व्यञ्जकम्:
    पक्ष POSTDECREMENT_व्यञ्जकम्:
    पक्ष POSTINCREMENT_व्यञ्जकम्:
      op0_lval = सच्च;
      /* FALLTHRU */
    पक्ष COMPOUND_व्यञ्जकम्:
    पक्ष PLUS_व्यञ्जकम्:
    पक्ष MINUS_व्यञ्जकम्:
    पक्ष MULT_व्यञ्जकम्:
    पक्ष POINTER_PLUS_व्यञ्जकम्:
    पक्ष POINTER_DIFF_व्यञ्जकम्:
    पक्ष TRUNC_DIV_व्यञ्जकम्:
    पक्ष CEIL_DIV_व्यञ्जकम्:
    पक्ष FLOOR_DIV_व्यञ्जकम्:
    पक्ष TRUNC_MOD_व्यञ्जकम्:
    पक्ष RDIV_व्यञ्जकम्:
    पक्ष EXACT_DIV_व्यञ्जकम्:
    पक्ष LSHIFT_व्यञ्जकम्:
    पक्ष RSHIFT_व्यञ्जकम्:
    पक्ष LROTATE_व्यञ्जकम्:
    पक्ष RROTATE_व्यञ्जकम्:
    पक्ष BIT_IOR_व्यञ्जकम्:
    पक्ष BIT_XOR_व्यञ्जकम्:
    पक्ष BIT_AND_व्यञ्जकम्:
    पक्ष LT_व्यञ्जकम्:
    पक्ष LE_व्यञ्जकम्:
    पक्ष GT_व्यञ्जकम्:
    पक्ष GE_व्यञ्जकम्:
    पक्ष EQ_व्यञ्जकम्:
    पक्ष NE_व्यञ्जकम्:
    पक्ष COMPLEX_व्यञ्जकम्:
    पक्ष TRUTH_AND_व्यञ्जकम्:
    पक्ष TRUTH_OR_व्यञ्जकम्:
    पक्ष TRUTH_XOR_व्यञ्जकम्:
    पक्ष UNORDERED_व्यञ्जकम्:
    पक्ष ORDERED_व्यञ्जकम्:
    पक्ष UNLT_व्यञ्जकम्:
    पक्ष UNLE_व्यञ्जकम्:
    पक्ष UNGT_व्यञ्जकम्:
    पक्ष UNGE_व्यञ्जकम्:
    पक्ष UNEQ_व्यञ्जकम्:
    पक्ष MEM_REF:
      /* Binary operations evaluating both arguments (increment and
	 decrement are binary internally in GCC).  */
      orig_op0 = op0 = वृक्षः_OPERAND (व्यञ्जकम्, 0);
      orig_op1 = op1 = वृक्षः_OPERAND (व्यञ्जकम्, 1);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const,
				   op0_lval);
      STRIP_TYPE_NOPS (op0);
      /* The RHS of a MODIFY_EXPR was fully folded when building that
	 expression for the sake of conversion warnings.  */
      सचे (code != MODIFY_व्यञ्जकम्)
	op1 = c_fully_fold_internal (op1, in_init, maybe_const_operands,
				     maybe_const_itself, for_int_const, मिच्छा);
      STRIP_TYPE_NOPS (op1);

      सचे (for_int_const && (वृक्षः_CODE (op0) != INTEGER_CST
			    || वृक्षः_CODE (op1) != INTEGER_CST))
	गच्छ out;

      सचे (वृक्षः_CODE_CLASS (code) == tcc_comparison
	  && वृक्षः_CODE (वृक्षः_TYPE (op0)) == NULLPTR_TYPE
	  && वृक्षः_CODE (वृक्षः_TYPE (op1)) == NULLPTR_TYPE)
	{
	  विकल्प (code)
	    {
	    पक्ष EQ_व्यञ्जकम्:
	      ret = constant_boolean_ग्रन्थिः (सच्च, वृक्षः_TYPE (व्यञ्जकम्));
	      भङ्ग;
	    पक्ष NE_व्यञ्जकम्:
	      ret = constant_boolean_ग्रन्थिः (मिच्छा, वृक्षः_TYPE (व्यञ्जकम्));
	      भङ्ग;
	    स्वभाव:
	      gcc_unreachable ();
	    }
	  ret = omit_two_operands_loc (loc, वृक्षः_TYPE (व्यञ्जकम्), ret,
				       op0, op1);
	}
      अञ्ञथा सचे (op0 != orig_op0 || op1 != orig_op1 || in_init)
	ret = in_init
	  ? fold_build2_initializer_loc (loc, code, वृक्षः_TYPE (व्यञ्जकम्), op0, op1)
	  : fold_build2_loc (loc, code, वृक्षः_TYPE (व्यञ्जकम्), op0, op1);
      अञ्ञथा
	ret = fold (व्यञ्जकम्);
      सचे (वृक्षः_OVERFLOW_P (ret)
	  && !वृक्षः_OVERFLOW_P (op0)
	  && !(द्विमान_CLASS_P (op0) && वृक्षः_OVERFLOW_P (वृक्षः_OPERAND (op0, 1)))
	  && !वृक्षः_OVERFLOW_P (op1))
	overflow_warning (व्यञ्जकम्_LOC_OR_LOC (व्यञ्जकम्, निवेशः_location), ret, व्यञ्जकम्);
      सचे (code == LSHIFT_व्यञ्जकम्
	  && वृक्षः_CODE (orig_op0) != INTEGER_CST
	  && (वृक्षः_CODE (वृक्षः_TYPE (orig_op0)) == INTEGER_TYPE
	      || वृक्षः_CODE (वृक्षः_TYPE (orig_op0)) == BITINT_TYPE)
	  && वृक्षः_CODE (op0) == INTEGER_CST
	  && c_inhibit_evaluation_warnings == 0
	  && !TYPE_OVERFLOW_WRAPS (वृक्षः_TYPE (orig_op0))
	  && वृक्षः_int_cst_sgn (op0) < 0)
	warning_at (loc, OPT_Wshift_negative_मानम्,
		    "left shift of negative value");
      सचे ((code == LSHIFT_व्यञ्जकम्
	   || code == RSHIFT_व्यञ्जकम्
	   || code == LROTATE_व्यञ्जकम्
	   || code == RROTATE_व्यञ्जकम्)
	  && वृक्षः_CODE (orig_op1) != INTEGER_CST
	  && वृक्षः_CODE (op1) == INTEGER_CST
	  && वृक्षः_CODE (वृक्षः_TYPE (orig_op1)) == INTEGER_TYPE
	  && c_inhibit_evaluation_warnings == 0)
	{
	  सचे (वृक्षः_int_cst_sgn (op1) < 0)
	    warning_at (loc, OPT_Wshift_गणनम्_negative,
			(code == LSHIFT_व्यञ्जकम्
			 ? G_("left shift count is negative")
			 : G_("right shift count is negative")));
	  अञ्ञथा सचे ((वृक्षः_CODE (वृक्षः_TYPE (orig_op0)) == INTEGER_TYPE
		    || वृक्षः_CODE (वृक्षः_TYPE (orig_op0)) == BITINT_TYPE
		    || वृक्षः_CODE (वृक्षः_TYPE (orig_op0)) == FIXED_POINT_TYPE)
		   && compare_वृक्षः_int (op1,
					TYPE_PRECISION (वृक्षः_TYPE (orig_op0)))
		      >= 0
		   && !warning_suppressed_p (व्यञ्जकम्, OPT_Wshift_गणनम्_overflow))
	    warning_at (loc, OPT_Wshift_गणनम्_overflow,
			(code == LSHIFT_व्यञ्जकम्
			 ? G_("left shift count >= width of type")
			 : G_("right shift count >= width of type")));
	  अञ्ञथा सचे (वृक्षः_CODE (वृक्षः_TYPE (orig_op0)) == VECTOR_TYPE
		   && compare_वृक्षः_int (op1,
					TYPE_PRECISION (वृक्षः_TYPE (वृक्षः_TYPE (orig_op0))))
		      >= 0)
	    warning_at (loc, OPT_Wshift_गणनम्_overflow,
			code == LSHIFT_व्यञ्जकम्
			? G_("left shift count >= width of vector element")
			: G_("right shift count >= width of vector element"));
	}
      सचे (code == LSHIFT_व्यञ्जकम्
	  /* If either OP0 has been folded to INTEGER_CST...  */
	  && ((वृक्षः_CODE (orig_op0) != INTEGER_CST
	       && (वृक्षः_CODE (वृक्षः_TYPE (orig_op0)) == INTEGER_TYPE
		   || वृक्षः_CODE (वृक्षः_TYPE (orig_op0)) == BITINT_TYPE)
	       && वृक्षः_CODE (op0) == INTEGER_CST)
	      /* ...or if OP1 has been folded to INTEGER_CST...  */
	      || (वृक्षः_CODE (orig_op1) != INTEGER_CST
		  && (वृक्षः_CODE (वृक्षः_TYPE (orig_op1)) == INTEGER_TYPE
		      || वृक्षः_CODE (वृक्षः_TYPE (orig_op1)) == BITINT_TYPE)
		  && वृक्षः_CODE (op1) == INTEGER_CST))
	  && c_inhibit_evaluation_warnings == 0)
	/* ...then maybe we can detect an overflow.  */
	maybe_warn_shift_overflow (loc, op0, op1);
      सचे ((code == TRUNC_DIV_व्यञ्जकम्
	   || code == CEIL_DIV_व्यञ्जकम्
	   || code == FLOOR_DIV_व्यञ्जकम्
	   || code == EXACT_DIV_व्यञ्जकम्
	   || code == TRUNC_MOD_व्यञ्जकम्)
	  && वृक्षः_CODE (orig_op1) != INTEGER_CST
	  && वृक्षः_CODE (op1) == INTEGER_CST
	  && (वृक्षः_CODE (वृक्षः_TYPE (orig_op0)) == INTEGER_TYPE
	      || वृक्षः_CODE (वृक्षः_TYPE (orig_op0)) == BITINT_TYPE
	      || वृक्षः_CODE (वृक्षः_TYPE (orig_op0)) == FIXED_POINT_TYPE)
	  && (वृक्षः_CODE (वृक्षः_TYPE (orig_op1)) == INTEGER_TYPE
	      || वृक्षः_CODE (वृक्षः_TYPE (orig_op1)) == BITINT_TYPE))
	warn_for_div_by_zero (loc, op1);
      सचे (code == MEM_REF
	  && ret != व्यञ्जकम्
	  && वृक्षः_CODE (ret) == MEM_REF)
	{
	  वृक्षः_READONLY (ret) = वृक्षः_READONLY (व्यञ्जकम्);
	  वृक्षः_SIDE_EFFECTS (ret) = वृक्षः_SIDE_EFFECTS (व्यञ्जकम्);
	  वृक्षः_THIS_VOLATILE (ret) = वृक्षः_THIS_VOLATILE (व्यञ्जकम्);
	}
      गच्छ out;

    पक्ष ADDR_व्यञ्जकम्:
      op0_lval = सच्च;
      गच्छ unary;
    पक्ष REALPART_व्यञ्जकम्:
    पक्ष IMAGPART_व्यञ्जकम्:
    पक्ष VIEW_CONVERT_व्यञ्जकम्:
      op0_lval = lval;
      /* FALLTHRU */
    पक्ष INDIRECT_REF:
    पक्ष FIX_TRUNC_व्यञ्जकम्:
    पक्ष FLOAT_व्यञ्जकम्:
    CASE_CONVERT:
    पक्ष ADDR_SPACE_CONVERT_व्यञ्जकम्:
    पक्ष NON_LVALUE_व्यञ्जकम्:
    पक्ष NEGATE_व्यञ्जकम्:
    पक्ष BIT_NOT_व्यञ्जकम्:
    पक्ष TRUTH_NOT_व्यञ्जकम्:
    पक्ष CONJ_व्यञ्जकम्:
    पक्ष PAREN_व्यञ्जकम्:
    unary:
      /* Unary operations.  */
      orig_op0 = op0 = वृक्षः_OPERAND (व्यञ्जकम्, 0);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const,
				   op0_lval);
      STRIP_TYPE_NOPS (op0);

      सचे (for_int_const && वृक्षः_CODE (op0) != INTEGER_CST)
	गच्छ out;

      /* ??? Cope with user tricks that amount to offsetof.  The middle-end is
	 not prepared to deal with them if they occur in initializers.  */
      सचे (op0 != orig_op0
	  && code == ADDR_व्यञ्जकम्
	  && (op1 = get_base_address (op0)) != NULL_वृक्षः
	  && INDIRECT_REF_P (op1)
	  && वृक्षः_CONSTANT (वृक्षः_OPERAND (op1, 0)))
	ret = fold_offsetof (op0, वृक्षः_TYPE (व्यञ्जकम्));
      अञ्ञथा सचे (op0 != orig_op0 || in_init)
	ret = in_init
	  ? fold_build1_initializer_loc (loc, code, वृक्षः_TYPE (व्यञ्जकम्), op0)
	  : fold_build1_loc (loc, code, वृक्षः_TYPE (व्यञ्जकम्), op0);
      अञ्ञथा
	ret = fold (व्यञ्जकम्);
      सचे (code == INDIRECT_REF
	  && ret != व्यञ्जकम्
	  && INDIRECT_REF_P (ret))
	{
	  वृक्षः_READONLY (ret) = वृक्षः_READONLY (व्यञ्जकम्);
	  वृक्षः_SIDE_EFFECTS (ret) = वृक्षः_SIDE_EFFECTS (व्यञ्जकम्);
	  वृक्षः_THIS_VOLATILE (ret) = वृक्षः_THIS_VOLATILE (व्यञ्जकम्);
	}
      विकल्प (code)
	{
	पक्ष FIX_TRUNC_व्यञ्जकम्:
	पक्ष FLOAT_व्यञ्जकम्:
	CASE_CONVERT:
	  /* Don't warn about explicit conversions.  We will already
	     have warned about suspect implicit conversions.  */
	  भङ्ग;

	स्वभाव:
	  सचे (वृक्षः_OVERFLOW_P (ret) && !वृक्षः_OVERFLOW_P (op0))
	    overflow_warning (व्यञ्जकम्_LOCATION (व्यञ्जकम्), ret, op0);
	  भङ्ग;
	}
      गच्छ out;

    पक्ष TRUTH_ANDIF_व्यञ्जकम्:
    पक्ष TRUTH_ORIF_व्यञ्जकम्:
      /* Binary operations not necessarily evaluating both
	 arguments.  */
      orig_op0 = op0 = वृक्षः_OPERAND (व्यञ्जकम्, 0);
      orig_op1 = op1 = वृक्षः_OPERAND (व्यञ्जकम्, 1);
      op0 = c_fully_fold_internal (op0, in_init, &op0_const, &op0_const_self,
				   for_int_const, मिच्छा);
      STRIP_TYPE_NOPS (op0);

      unused_p = (op0 == (code == TRUTH_ANDIF_व्यञ्जकम्
			  ? truthvalue_false_ग्रन्थिः
			  : truthvalue_true_ग्रन्थिः));
      c_disable_warnings (unused_p);
      op1 = c_fully_fold_internal (op1, in_init, &op1_const, &op1_const_self,
				   for_int_const, मिच्छा);
      STRIP_TYPE_NOPS (op1);
      c_enable_warnings (unused_p);

      सचे (for_int_const
	  && (वृक्षः_CODE (op0) != INTEGER_CST
	      /* Require OP1 be an INTEGER_CST only if it's evaluated.  */
	      || (!unused_p && वृक्षः_CODE (op1) != INTEGER_CST)))
	गच्छ out;

      सचे (op0 != orig_op0 || op1 != orig_op1 || in_init)
	ret = in_init
	  ? fold_build2_initializer_loc (loc, code, वृक्षः_TYPE (व्यञ्जकम्), op0, op1)
	  : fold_build2_loc (loc, code, वृक्षः_TYPE (व्यञ्जकम्), op0, op1);
      अञ्ञथा
	ret = fold (व्यञ्जकम्);
      *maybe_const_operands &= op0_const;
      *maybe_const_itself &= op0_const_self;
      सचे (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && (code == TRUTH_ANDIF_व्यञ्जकम्
		? op0 == truthvalue_false_ग्रन्थिः
		: op0 == truthvalue_true_ग्रन्थिः)))
	*maybe_const_operands &= op1_const;
      सचे (!(op0_const
	    && op0_const_self
	    && (code == TRUTH_ANDIF_व्यञ्जकम्
		? op0 == truthvalue_false_ग्रन्थिः
		: op0 == truthvalue_true_ग्रन्थिः)))
	*maybe_const_itself &= op1_const_self;
      गच्छ out;

    पक्ष COND_व्यञ्जकम्:
      orig_op0 = op0 = वृक्षः_OPERAND (व्यञ्जकम्, 0);
      orig_op1 = op1 = वृक्षः_OPERAND (व्यञ्जकम्, 1);
      orig_op2 = op2 = वृक्षः_OPERAND (व्यञ्जकम्, 2);
      op0 = c_fully_fold_internal (op0, in_init, &op0_const, &op0_const_self,
				   for_int_const, मिच्छा);

      STRIP_TYPE_NOPS (op0);
      c_disable_warnings (op0 == truthvalue_false_ग्रन्थिः);
      op1 = c_fully_fold_internal (op1, in_init, &op1_const, &op1_const_self,
				   for_int_const, मिच्छा);
      STRIP_TYPE_NOPS (op1);
      c_enable_warnings (op0 == truthvalue_false_ग्रन्थिः);

      c_disable_warnings (op0 == truthvalue_true_ग्रन्थिः);
      op2 = c_fully_fold_internal (op2, in_init, &op2_const, &op2_const_self,
				   for_int_const, मिच्छा);
      STRIP_TYPE_NOPS (op2);
      c_enable_warnings (op0 == truthvalue_true_ग्रन्थिः);

      सचे (for_int_const
	  && (वृक्षः_CODE (op0) != INTEGER_CST
	      /* Only the evaluated operand must be an INTEGER_CST.  */
	      || (op0 == truthvalue_true_ग्रन्थिः
		  ? वृक्षः_CODE (op1) != INTEGER_CST
		  : वृक्षः_CODE (op2) != INTEGER_CST)))
	गच्छ out;

      सचे (op0 != orig_op0 || op1 != orig_op1 || op2 != orig_op2)
	ret = fold_build3_loc (loc, code, वृक्षः_TYPE (व्यञ्जकम्), op0, op1, op2);
      अञ्ञथा
	ret = fold (व्यञ्जकम्);
      *maybe_const_operands &= op0_const;
      *maybe_const_itself &= op0_const_self;
      सचे (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && op0 == truthvalue_false_ग्रन्थिः))
	*maybe_const_operands &= op1_const;
      सचे (!(op0_const
	    && op0_const_self
	    && op0 == truthvalue_false_ग्रन्थिः))
	*maybe_const_itself &= op1_const_self;
      सचे (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && op0 == truthvalue_true_ग्रन्थिः))
	*maybe_const_operands &= op2_const;
      सचे (!(op0_const
	    && op0_const_self
	    && op0 == truthvalue_true_ग्रन्थिः))
	*maybe_const_itself &= op2_const_self;
      गच्छ out;

    पक्ष VEC_COND_व्यञ्जकम्:
      orig_op0 = op0 = वृक्षः_OPERAND (व्यञ्जकम्, 0);
      orig_op1 = op1 = वृक्षः_OPERAND (व्यञ्जकम्, 1);
      orig_op2 = op2 = वृक्षः_OPERAND (व्यञ्जकम्, 2);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, मिच्छा);
      STRIP_TYPE_NOPS (op0);
      op1 = c_fully_fold_internal (op1, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, मिच्छा);
      STRIP_TYPE_NOPS (op1);
      op2 = c_fully_fold_internal (op2, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, मिच्छा);
      STRIP_TYPE_NOPS (op2);

      सचे (op0 != orig_op0 || op1 != orig_op1 || op2 != orig_op2)
	ret = fold_build3_loc (loc, code, वृक्षः_TYPE (व्यञ्जकम्), op0, op1, op2);
      अञ्ञथा
	ret = fold (व्यञ्जकम्);
      गच्छ out;

    पक्ष EXCESS_PRECISION_व्यञ्जकम्:
      /* Each case where an operand with excess precision may be
	 encountered must remove the EXCESS_PRECISION_EXPR around
	 inner operands and possibly put one around the whole
	 expression or possibly convert to the semantic type (which
	 c_fully_fold does); we cannot tell at this stage which is
	 appropriate in any particular case.  */
      gcc_unreachable ();

    पक्ष SAVE_व्यञ्जकम्:
      /* Make sure to fold the contents of a SAVE_EXPR exactly once.  */
      op0 = वृक्षः_OPERAND (व्यञ्जकम्, 0);
      सचे (!SAVE_व्यञ्जकम्_FOLDED_P (व्यञ्जकम्))
	{
	  op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				       maybe_const_itself, for_int_const,
				       मिच्छा);
	  वृक्षः_OPERAND (व्यञ्जकम्, 0) = op0;
	  SAVE_व्यञ्जकम्_FOLDED_P (व्यञ्जकम्) = सच्च;
	}
      /* Return the SAVE_EXPR operand if it is invariant.  */
      सचे (वृक्षः_invariant_p (op0))
	ret = op0;
      गच्छ out;

    स्वभाव:
      /* Various codes may appear through folding built-in functions
	 and their arguments.  */
      गच्छ out;
    }

 out:
  /* Some folding may introduce NON_LVALUE_EXPRs; all lvalue checks
     have been done by this point, so remove them again.  */
  nowarning |= warning_suppressed_p (ret, OPT_Woverflow);
  STRIP_TYPE_NOPS (ret);
  सचे (nowarning && !warning_suppressed_p (ret, OPT_Woverflow))
    {
      सचे (!CAN_HAVE_LOCATION_P (ret))
	ret = build1 (NOP_व्यञ्जकम्, वृक्षः_TYPE (ret), ret);
      suppress_warning (ret, OPT_Woverflow);
    }
  सचे (ret != व्यञ्जकम्)
    {
      protected_set_व्यञ्जकम्_location (ret, loc);
      सचे (IS_व्यञ्जकम्_CODE_CLASS (kind))
	set_source_range (ret, old_range.m_start, old_range.m_finish);
    }
  पटिनिवत्त ret;
}

/* Fold X for consideration by one of the warning functions when checking
   whether an expression has a constant value.  */

वृक्षः
fold_for_warn (वृक्षः x)
{
  /* The C front-end has already folded X appropriately.  */
  पटिनिवत्त x;
}
