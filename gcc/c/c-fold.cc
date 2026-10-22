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

स्थिर वृक्ष c_fully_fold_internal (वृक्ष अभिव्यक्ती, तार्किक, तार्किक *, तार्किक *, तार्किक,
				   तार्किक);

/* If DISABLE is true, stop issuing warnings.  This is used when
   parsing code that we know will not be executed.  This function may
   be called multiple times, and works as a stack.  */

स्थिर शून्य
c_disable_warnings (तार्किक disable)
{
  यदि (disable)
    {
      ++c_inhibit_evaluation_warnings;
    }
}

/* If ENABLE is true, re-enable issuing warnings.  */

स्थिर शून्य
c_enable_warnings (तार्किक enable)
{
  यदि (enable)
    {
      --c_inhibit_evaluation_warnings;
    }
}

/* Try to fold ARRAY_REF ary[index] if possible and not handled by
   normal fold, return NULL_TREE otherwise.  */

स्थिर वृक्ष
c_fold_array_ref (वृक्ष type, वृक्ष ary, वृक्ष index)
{
  यदि (वृक्ष_CODE (ary) != STRING_CST
      || वृक्ष_CODE (index) != INTEGER_CST
      || वृक्ष_OVERFLOW (index)
      || वृक्ष_CODE (वृक्ष_TYPE (ary)) != ARRAY_TYPE
      || !वृक्ष_fits_uhwi_p (index))
    प्रत्यागम NULL_वृक्ष;

  वृक्ष elem_type = वृक्ष_TYPE (वृक्ष_TYPE (ary));
  unsigned elem_nchars = (TYPE_PRECISION (elem_type)
			  / TYPE_PRECISION (char_type_गाठ));
  unsigned len = (unsigned) वृक्ष_STRING_LENGTH (ary) / elem_nchars;
  वृक्ष nelts_minus_one = array_type_nelts_minus_one (वृक्ष_TYPE (ary));
  तार्किक dummy1 = सत्य, dummy2 = सत्य;
  nelts_minus_one = c_fully_fold_internal (nelts_minus_one, सत्य, &dummy1,
					   &dummy2, असत्य, असत्य);
  unsigned HOST_WIDE_INT i = वृक्ष_to_uhwi (index);
  यदि (!वृक्ष_int_cst_le (index, nelts_minus_one)
      || i >= len
      || i + elem_nchars > len)
    प्रत्यागम NULL_वृक्ष;

  यदि (elem_nchars == 1)
    प्रत्यागम build_int_cst (type, वृक्ष_STRING_POINTER (ary)[i]);

  ध्रुव unsigned वर्ण *ptr
    = ((ध्रुव unsigned वर्ण *)वृक्ष_STRING_POINTER (ary) + i * elem_nchars);
  प्रत्यागम native_interpret_अभिव्यक्ती (type, ptr, elem_nchars);
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

वृक्ष
c_fully_fold (वृक्ष अभिव्यक्ती, तार्किक in_init, तार्किक *maybe_const, तार्किक lval)
{
  वृक्ष ret;
  वृक्ष eptype = NULL_वृक्ष;
  तार्किक dummy = सत्य;
  तार्किक maybe_const_itself = सत्य;
  location_t loc = अभिव्यक्ती_LOCATION (अभिव्यक्ती);

  यदि (!maybe_const)
    maybe_const = &dummy;
  यदि (वृक्ष_CODE (अभिव्यक्ती) == EXCESS_PRECISION_अभिव्यक्ती)
    {
      eptype = वृक्ष_TYPE (अभिव्यक्ती);
      अभिव्यक्ती = वृक्ष_OPERAND (अभिव्यक्ती, 0);
    }
  ret = c_fully_fold_internal (अभिव्यक्ती, in_init, maybe_const,
			       &maybe_const_itself, असत्य, lval);
  यदि (eptype)
    ret = fold_convert_loc (loc, eptype, ret);
  *maybe_const &= maybe_const_itself;
  प्रत्यागम ret;
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

स्थिर वृक्ष
c_fully_fold_internal (वृक्ष अभिव्यक्ती, तार्किक in_init, तार्किक *maybe_const_operands,
		       तार्किक *maybe_const_itself, तार्किक for_int_const, तार्किक lval)
{
  वृक्ष ret = अभिव्यक्ती;
  गणना वृक्ष_code code = वृक्ष_CODE (अभिव्यक्ती);
  गणना वृक्ष_code_class kind = वृक्ष_CODE_CLASS (code);
  location_t loc = अभिव्यक्ती_LOCATION (अभिव्यक्ती);
  वृक्ष op0, op1, op2, op3;
  वृक्ष orig_op0, orig_op1, orig_op2;
  तार्किक op0_const = सत्य, op1_const = सत्य, op2_const = सत्य;
  तार्किक op0_const_self = सत्य, op1_const_self = सत्य, op2_const_self = सत्य;
  तार्किक nowarning = warning_suppressed_p (अभिव्यक्ती, OPT_Woverflow);
  तार्किक unused_p;
  तार्किक op0_lval = असत्य;
  source_range old_range;

  /* Constants, declarations, statements, errors, and anything else not
     counted as an expression cannot usefully be folded further at this
     point.  */
  यदि (!IS_अभिव्यक्ती_CODE_CLASS (kind) || kind == tcc_statement)
    {
      /* Except for variables which we can optimize to its initializer.  */
      यदि (VAR_P (अभिव्यक्ती) && !lval && (optimize || in_init))
	{
	  यदि (in_init)
	    ret = decl_constant_मूल्य_1 (अभिव्यक्ती, सत्य);
	  अन्यथा
	    {
	      ret = decl_constant_मूल्य (अभिव्यक्ती);
	      यदि (ret != अभिव्यक्ती
		  && (TYPE_MODE (वृक्ष_TYPE (ret)) == BLKmode
		      || वृक्ष_CODE (वृक्ष_TYPE (ret)) == ARRAY_TYPE))
		प्रत्यागम अभिव्यक्ती;
	    }
	  /* Avoid unwanted tree sharing between the initializer and current
	     function's body where the tree can be modified e.g. by the
	     gimplifier.  */
	  यदि (ret != अभिव्यक्ती && वृक्ष_STATIC (अभिव्यक्ती))
	    ret = unshare_अभिव्यक्ती (ret);
	  प्रत्यागम ret;
	}
      प्रत्यागम अभिव्यक्ती;
    }

  यदि (IS_अभिव्यक्ती_CODE_CLASS (kind))
    old_range = अभिव्यक्ती_LOCATION_RANGE (अभिव्यक्ती);

  /* Operands of variable-length expressions (function calls) have
     already been folded, as have __builtin_* function calls, and such
     expressions cannot occur in constant expressions.  */
  यदि (kind == tcc_vl_exp)
    {
      *maybe_const_operands = असत्य;
      ret = fold (अभिव्यक्ती);
      गच्छ out;
    }

  यदि (code == C_MAYBE_CONST_अभिव्यक्ती)
    {
      वृक्ष pre = C_MAYBE_CONST_अभिव्यक्ती_PRE (अभिव्यक्ती);
      वृक्ष inner = C_MAYBE_CONST_अभिव्यक्ती_अभिव्यक्ती (अभिव्यक्ती);
      यदि (C_MAYBE_CONST_अभिव्यक्ती_NON_CONST (अभिव्यक्ती))
	*maybe_const_operands = असत्य;
      यदि (C_MAYBE_CONST_अभिव्यक्ती_INT_OPERANDS (अभिव्यक्ती))
	{
	  *maybe_const_itself = असत्य;
	  inner = c_fully_fold_internal (inner, in_init, maybe_const_operands,
					 maybe_const_itself, सत्य, lval);
	}
      यदि (pre && !in_init)
	ret = build2 (COMPOUND_अभिव्यक्ती, वृक्ष_TYPE (अभिव्यक्ती), pre, inner);
      अन्यथा
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
    पक्ष MODIFY_अभिव्यक्ती:
    पक्ष PREDECREMENT_अभिव्यक्ती:
    पक्ष PREINCREMENT_अभिव्यक्ती:
    पक्ष POSTDECREMENT_अभिव्यक्ती:
    पक्ष POSTINCREMENT_अभिव्यक्ती:
    पक्ष COMPOUND_अभिव्यक्ती:
      *maybe_const_operands = असत्य;
      भङ्ग;

    पक्ष VA_ARG_अभिव्यक्ती:
    पक्ष TARGET_अभिव्यक्ती:
    पक्ष BIND_अभिव्यक्ती:
    पक्ष OBJ_TYPE_REF:
      *maybe_const_operands = असत्य;
      ret = fold (अभिव्यक्ती);
      गच्छ out;

    स्वभाव:
      भङ्ग;
    }

  /* Fold individual tree codes as appropriate.  */
  विकल्प (code)
    {
    पक्ष COMPOUND_LITERAL_अभिव्यक्ती:
      /* Any non-constancy will have been marked in a containing
	 C_MAYBE_CONST_EXPR; there is no more folding to do here.  */
      गच्छ out;

    पक्ष COMPONENT_REF:
      orig_op0 = op0 = वृक्ष_OPERAND (अभिव्यक्ती, 0);
      op1 = वृक्ष_OPERAND (अभिव्यक्ती, 1);
      op2 = वृक्ष_OPERAND (अभिव्यक्ती, 2);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, lval);
      STRIP_TYPE_NOPS (op0);
      यदि (op0 != orig_op0)
	ret = build3 (COMPONENT_REF, वृक्ष_TYPE (अभिव्यक्ती), op0, op1, op2);
      यदि (ret != अभिव्यक्ती)
	{
	  वृक्ष_READONLY (ret) = वृक्ष_READONLY (अभिव्यक्ती);
	  वृक्ष_THIS_VOLATILE (ret) = वृक्ष_THIS_VOLATILE (अभिव्यक्ती);
	}
      यदि (!lval)
	ret = fold (ret);
      गच्छ out;

    पक्ष ARRAY_REF:
      orig_op0 = op0 = वृक्ष_OPERAND (अभिव्यक्ती, 0);
      orig_op1 = op1 = वृक्ष_OPERAND (अभिव्यक्ती, 1);
      op2 = वृक्ष_OPERAND (अभिव्यक्ती, 2);
      op3 = वृक्ष_OPERAND (अभिव्यक्ती, 3);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, lval);
      STRIP_TYPE_NOPS (op0);
      op1 = c_fully_fold_internal (op1, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, असत्य);
      STRIP_TYPE_NOPS (op1);
      /* Fold "foo"[2] in initializers.  */
      यदि (!lval && in_init)
	{
	  ret = c_fold_array_ref (वृक्ष_TYPE (अभिव्यक्ती), op0, op1);
	  यदि (ret)
	    गच्छ out;
	  ret = अभिव्यक्ती;
	}
      यदि (op0 != orig_op0 || op1 != orig_op1)
	ret = build4 (ARRAY_REF, वृक्ष_TYPE (अभिव्यक्ती), op0, op1, op2, op3);
      यदि (ret != अभिव्यक्ती)
	{
	  वृक्ष_READONLY (ret) = वृक्ष_READONLY (अभिव्यक्ती);
	  वृक्ष_SIDE_EFFECTS (ret) = वृक्ष_SIDE_EFFECTS (अभिव्यक्ती);
	  वृक्ष_THIS_VOLATILE (ret) = वृक्ष_THIS_VOLATILE (अभिव्यक्ती);
	}
      यदि (!lval)
	ret = fold (ret);
      गच्छ out;

    पक्ष MODIFY_अभिव्यक्ती:
    पक्ष PREDECREMENT_अभिव्यक्ती:
    पक्ष PREINCREMENT_अभिव्यक्ती:
    पक्ष POSTDECREMENT_अभिव्यक्ती:
    पक्ष POSTINCREMENT_अभिव्यक्ती:
      op0_lval = सत्य;
      /* FALLTHRU */
    पक्ष COMPOUND_अभिव्यक्ती:
    पक्ष PLUS_अभिव्यक्ती:
    पक्ष MINUS_अभिव्यक्ती:
    पक्ष MULT_अभिव्यक्ती:
    पक्ष POINTER_PLUS_अभिव्यक्ती:
    पक्ष POINTER_DIFF_अभिव्यक्ती:
    पक्ष TRUNC_DIV_अभिव्यक्ती:
    पक्ष CEIL_DIV_अभिव्यक्ती:
    पक्ष FLOOR_DIV_अभिव्यक्ती:
    पक्ष TRUNC_MOD_अभिव्यक्ती:
    पक्ष RDIV_अभिव्यक्ती:
    पक्ष EXACT_DIV_अभिव्यक्ती:
    पक्ष LSHIFT_अभिव्यक्ती:
    पक्ष RSHIFT_अभिव्यक्ती:
    पक्ष LROTATE_अभिव्यक्ती:
    पक्ष RROTATE_अभिव्यक्ती:
    पक्ष BIT_IOR_अभिव्यक्ती:
    पक्ष BIT_XOR_अभिव्यक्ती:
    पक्ष BIT_AND_अभिव्यक्ती:
    पक्ष LT_अभिव्यक्ती:
    पक्ष LE_अभिव्यक्ती:
    पक्ष GT_अभिव्यक्ती:
    पक्ष GE_अभिव्यक्ती:
    पक्ष EQ_अभिव्यक्ती:
    पक्ष NE_अभिव्यक्ती:
    पक्ष COMPLEX_अभिव्यक्ती:
    पक्ष TRUTH_AND_अभिव्यक्ती:
    पक्ष TRUTH_OR_अभिव्यक्ती:
    पक्ष TRUTH_XOR_अभिव्यक्ती:
    पक्ष UNORDERED_अभिव्यक्ती:
    पक्ष ORDERED_अभिव्यक्ती:
    पक्ष UNLT_अभिव्यक्ती:
    पक्ष UNLE_अभिव्यक्ती:
    पक्ष UNGT_अभिव्यक्ती:
    पक्ष UNGE_अभिव्यक्ती:
    पक्ष UNEQ_अभिव्यक्ती:
    पक्ष MEM_REF:
      /* Binary operations evaluating both arguments (increment and
	 decrement are binary internally in GCC).  */
      orig_op0 = op0 = वृक्ष_OPERAND (अभिव्यक्ती, 0);
      orig_op1 = op1 = वृक्ष_OPERAND (अभिव्यक्ती, 1);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const,
				   op0_lval);
      STRIP_TYPE_NOPS (op0);
      /* The RHS of a MODIFY_EXPR was fully folded when building that
	 expression for the sake of conversion warnings.  */
      यदि (code != MODIFY_अभिव्यक्ती)
	op1 = c_fully_fold_internal (op1, in_init, maybe_const_operands,
				     maybe_const_itself, for_int_const, असत्य);
      STRIP_TYPE_NOPS (op1);

      यदि (for_int_const && (वृक्ष_CODE (op0) != INTEGER_CST
			    || वृक्ष_CODE (op1) != INTEGER_CST))
	गच्छ out;

      यदि (वृक्ष_CODE_CLASS (code) == tcc_comparison
	  && वृक्ष_CODE (वृक्ष_TYPE (op0)) == NULLPTR_TYPE
	  && वृक्ष_CODE (वृक्ष_TYPE (op1)) == NULLPTR_TYPE)
	{
	  विकल्प (code)
	    {
	    पक्ष EQ_अभिव्यक्ती:
	      ret = constant_boolean_गाठ (सत्य, वृक्ष_TYPE (अभिव्यक्ती));
	      भङ्ग;
	    पक्ष NE_अभिव्यक्ती:
	      ret = constant_boolean_गाठ (असत्य, वृक्ष_TYPE (अभिव्यक्ती));
	      भङ्ग;
	    स्वभाव:
	      gcc_unreachable ();
	    }
	  ret = omit_two_operands_loc (loc, वृक्ष_TYPE (अभिव्यक्ती), ret,
				       op0, op1);
	}
      अन्यथा यदि (op0 != orig_op0 || op1 != orig_op1 || in_init)
	ret = in_init
	  ? fold_build2_initializer_loc (loc, code, वृक्ष_TYPE (अभिव्यक्ती), op0, op1)
	  : fold_build2_loc (loc, code, वृक्ष_TYPE (अभिव्यक्ती), op0, op1);
      अन्यथा
	ret = fold (अभिव्यक्ती);
      यदि (वृक्ष_OVERFLOW_P (ret)
	  && !वृक्ष_OVERFLOW_P (op0)
	  && !(द्विमान_CLASS_P (op0) && वृक्ष_OVERFLOW_P (वृक्ष_OPERAND (op0, 1)))
	  && !वृक्ष_OVERFLOW_P (op1))
	overflow_warning (अभिव्यक्ती_LOC_OR_LOC (अभिव्यक्ती, आदान_location), ret, अभिव्यक्ती);
      यदि (code == LSHIFT_अभिव्यक्ती
	  && वृक्ष_CODE (orig_op0) != INTEGER_CST
	  && (वृक्ष_CODE (वृक्ष_TYPE (orig_op0)) == INTEGER_TYPE
	      || वृक्ष_CODE (वृक्ष_TYPE (orig_op0)) == BITINT_TYPE)
	  && वृक्ष_CODE (op0) == INTEGER_CST
	  && c_inhibit_evaluation_warnings == 0
	  && !TYPE_OVERFLOW_WRAPS (वृक्ष_TYPE (orig_op0))
	  && वृक्ष_int_cst_sgn (op0) < 0)
	warning_at (loc, OPT_Wshift_negative_मूल्य,
		    "left shift of negative value");
      यदि ((code == LSHIFT_अभिव्यक्ती
	   || code == RSHIFT_अभिव्यक्ती
	   || code == LROTATE_अभिव्यक्ती
	   || code == RROTATE_अभिव्यक्ती)
	  && वृक्ष_CODE (orig_op1) != INTEGER_CST
	  && वृक्ष_CODE (op1) == INTEGER_CST
	  && वृक्ष_CODE (वृक्ष_TYPE (orig_op1)) == INTEGER_TYPE
	  && c_inhibit_evaluation_warnings == 0)
	{
	  यदि (वृक्ष_int_cst_sgn (op1) < 0)
	    warning_at (loc, OPT_Wshift_मोजणी_negative,
			(code == LSHIFT_अभिव्यक्ती
			 ? G_("left shift count is negative")
			 : G_("right shift count is negative")));
	  अन्यथा यदि ((वृक्ष_CODE (वृक्ष_TYPE (orig_op0)) == INTEGER_TYPE
		    || वृक्ष_CODE (वृक्ष_TYPE (orig_op0)) == BITINT_TYPE
		    || वृक्ष_CODE (वृक्ष_TYPE (orig_op0)) == FIXED_POINT_TYPE)
		   && compare_वृक्ष_int (op1,
					TYPE_PRECISION (वृक्ष_TYPE (orig_op0)))
		      >= 0
		   && !warning_suppressed_p (अभिव्यक्ती, OPT_Wshift_मोजणी_overflow))
	    warning_at (loc, OPT_Wshift_मोजणी_overflow,
			(code == LSHIFT_अभिव्यक्ती
			 ? G_("left shift count >= width of type")
			 : G_("right shift count >= width of type")));
	  अन्यथा यदि (वृक्ष_CODE (वृक्ष_TYPE (orig_op0)) == VECTOR_TYPE
		   && compare_वृक्ष_int (op1,
					TYPE_PRECISION (वृक्ष_TYPE (वृक्ष_TYPE (orig_op0))))
		      >= 0)
	    warning_at (loc, OPT_Wshift_मोजणी_overflow,
			code == LSHIFT_अभिव्यक्ती
			? G_("left shift count >= width of vector element")
			: G_("right shift count >= width of vector element"));
	}
      यदि (code == LSHIFT_अभिव्यक्ती
	  /* If either OP0 has been folded to INTEGER_CST...  */
	  && ((वृक्ष_CODE (orig_op0) != INTEGER_CST
	       && (वृक्ष_CODE (वृक्ष_TYPE (orig_op0)) == INTEGER_TYPE
		   || वृक्ष_CODE (वृक्ष_TYPE (orig_op0)) == BITINT_TYPE)
	       && वृक्ष_CODE (op0) == INTEGER_CST)
	      /* ...or if OP1 has been folded to INTEGER_CST...  */
	      || (वृक्ष_CODE (orig_op1) != INTEGER_CST
		  && (वृक्ष_CODE (वृक्ष_TYPE (orig_op1)) == INTEGER_TYPE
		      || वृक्ष_CODE (वृक्ष_TYPE (orig_op1)) == BITINT_TYPE)
		  && वृक्ष_CODE (op1) == INTEGER_CST))
	  && c_inhibit_evaluation_warnings == 0)
	/* ...then maybe we can detect an overflow.  */
	maybe_warn_shift_overflow (loc, op0, op1);
      यदि ((code == TRUNC_DIV_अभिव्यक्ती
	   || code == CEIL_DIV_अभिव्यक्ती
	   || code == FLOOR_DIV_अभिव्यक्ती
	   || code == EXACT_DIV_अभिव्यक्ती
	   || code == TRUNC_MOD_अभिव्यक्ती)
	  && वृक्ष_CODE (orig_op1) != INTEGER_CST
	  && वृक्ष_CODE (op1) == INTEGER_CST
	  && (वृक्ष_CODE (वृक्ष_TYPE (orig_op0)) == INTEGER_TYPE
	      || वृक्ष_CODE (वृक्ष_TYPE (orig_op0)) == BITINT_TYPE
	      || वृक्ष_CODE (वृक्ष_TYPE (orig_op0)) == FIXED_POINT_TYPE)
	  && (वृक्ष_CODE (वृक्ष_TYPE (orig_op1)) == INTEGER_TYPE
	      || वृक्ष_CODE (वृक्ष_TYPE (orig_op1)) == BITINT_TYPE))
	warn_for_div_by_zero (loc, op1);
      यदि (code == MEM_REF
	  && ret != अभिव्यक्ती
	  && वृक्ष_CODE (ret) == MEM_REF)
	{
	  वृक्ष_READONLY (ret) = वृक्ष_READONLY (अभिव्यक्ती);
	  वृक्ष_SIDE_EFFECTS (ret) = वृक्ष_SIDE_EFFECTS (अभिव्यक्ती);
	  वृक्ष_THIS_VOLATILE (ret) = वृक्ष_THIS_VOLATILE (अभिव्यक्ती);
	}
      गच्छ out;

    पक्ष ADDR_अभिव्यक्ती:
      op0_lval = सत्य;
      गच्छ unary;
    पक्ष REALPART_अभिव्यक्ती:
    पक्ष IMAGPART_अभिव्यक्ती:
    पक्ष VIEW_CONVERT_अभिव्यक्ती:
      op0_lval = lval;
      /* FALLTHRU */
    पक्ष INDIRECT_REF:
    पक्ष FIX_TRUNC_अभिव्यक्ती:
    पक्ष FLOAT_अभिव्यक्ती:
    CASE_CONVERT:
    पक्ष ADDR_SPACE_CONVERT_अभिव्यक्ती:
    पक्ष NON_LVALUE_अभिव्यक्ती:
    पक्ष NEGATE_अभिव्यक्ती:
    पक्ष BIT_NOT_अभिव्यक्ती:
    पक्ष TRUTH_NOT_अभिव्यक्ती:
    पक्ष CONJ_अभिव्यक्ती:
    पक्ष PAREN_अभिव्यक्ती:
    unary:
      /* Unary operations.  */
      orig_op0 = op0 = वृक्ष_OPERAND (अभिव्यक्ती, 0);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const,
				   op0_lval);
      STRIP_TYPE_NOPS (op0);

      यदि (for_int_const && वृक्ष_CODE (op0) != INTEGER_CST)
	गच्छ out;

      /* ??? Cope with user tricks that amount to offsetof.  The middle-end is
	 not prepared to deal with them if they occur in initializers.  */
      यदि (op0 != orig_op0
	  && code == ADDR_अभिव्यक्ती
	  && (op1 = get_base_address (op0)) != NULL_वृक्ष
	  && INDIRECT_REF_P (op1)
	  && वृक्ष_CONSTANT (वृक्ष_OPERAND (op1, 0)))
	ret = fold_offsetof (op0, वृक्ष_TYPE (अभिव्यक्ती));
      अन्यथा यदि (op0 != orig_op0 || in_init)
	ret = in_init
	  ? fold_build1_initializer_loc (loc, code, वृक्ष_TYPE (अभिव्यक्ती), op0)
	  : fold_build1_loc (loc, code, वृक्ष_TYPE (अभिव्यक्ती), op0);
      अन्यथा
	ret = fold (अभिव्यक्ती);
      यदि (code == INDIRECT_REF
	  && ret != अभिव्यक्ती
	  && INDIRECT_REF_P (ret))
	{
	  वृक्ष_READONLY (ret) = वृक्ष_READONLY (अभिव्यक्ती);
	  वृक्ष_SIDE_EFFECTS (ret) = वृक्ष_SIDE_EFFECTS (अभिव्यक्ती);
	  वृक्ष_THIS_VOLATILE (ret) = वृक्ष_THIS_VOLATILE (अभिव्यक्ती);
	}
      विकल्प (code)
	{
	पक्ष FIX_TRUNC_अभिव्यक्ती:
	पक्ष FLOAT_अभिव्यक्ती:
	CASE_CONVERT:
	  /* Don't warn about explicit conversions.  We will already
	     have warned about suspect implicit conversions.  */
	  भङ्ग;

	स्वभाव:
	  यदि (वृक्ष_OVERFLOW_P (ret) && !वृक्ष_OVERFLOW_P (op0))
	    overflow_warning (अभिव्यक्ती_LOCATION (अभिव्यक्ती), ret, op0);
	  भङ्ग;
	}
      गच्छ out;

    पक्ष TRUTH_ANDIF_अभिव्यक्ती:
    पक्ष TRUTH_ORIF_अभिव्यक्ती:
      /* Binary operations not necessarily evaluating both
	 arguments.  */
      orig_op0 = op0 = वृक्ष_OPERAND (अभिव्यक्ती, 0);
      orig_op1 = op1 = वृक्ष_OPERAND (अभिव्यक्ती, 1);
      op0 = c_fully_fold_internal (op0, in_init, &op0_const, &op0_const_self,
				   for_int_const, असत्य);
      STRIP_TYPE_NOPS (op0);

      unused_p = (op0 == (code == TRUTH_ANDIF_अभिव्यक्ती
			  ? truthvalue_false_गाठ
			  : truthvalue_true_गाठ));
      c_disable_warnings (unused_p);
      op1 = c_fully_fold_internal (op1, in_init, &op1_const, &op1_const_self,
				   for_int_const, असत्य);
      STRIP_TYPE_NOPS (op1);
      c_enable_warnings (unused_p);

      यदि (for_int_const
	  && (वृक्ष_CODE (op0) != INTEGER_CST
	      /* Require OP1 be an INTEGER_CST only if it's evaluated.  */
	      || (!unused_p && वृक्ष_CODE (op1) != INTEGER_CST)))
	गच्छ out;

      यदि (op0 != orig_op0 || op1 != orig_op1 || in_init)
	ret = in_init
	  ? fold_build2_initializer_loc (loc, code, वृक्ष_TYPE (अभिव्यक्ती), op0, op1)
	  : fold_build2_loc (loc, code, वृक्ष_TYPE (अभिव्यक्ती), op0, op1);
      अन्यथा
	ret = fold (अभिव्यक्ती);
      *maybe_const_operands &= op0_const;
      *maybe_const_itself &= op0_const_self;
      यदि (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && (code == TRUTH_ANDIF_अभिव्यक्ती
		? op0 == truthvalue_false_गाठ
		: op0 == truthvalue_true_गाठ)))
	*maybe_const_operands &= op1_const;
      यदि (!(op0_const
	    && op0_const_self
	    && (code == TRUTH_ANDIF_अभिव्यक्ती
		? op0 == truthvalue_false_गाठ
		: op0 == truthvalue_true_गाठ)))
	*maybe_const_itself &= op1_const_self;
      गच्छ out;

    पक्ष COND_अभिव्यक्ती:
      orig_op0 = op0 = वृक्ष_OPERAND (अभिव्यक्ती, 0);
      orig_op1 = op1 = वृक्ष_OPERAND (अभिव्यक्ती, 1);
      orig_op2 = op2 = वृक्ष_OPERAND (अभिव्यक्ती, 2);
      op0 = c_fully_fold_internal (op0, in_init, &op0_const, &op0_const_self,
				   for_int_const, असत्य);

      STRIP_TYPE_NOPS (op0);
      c_disable_warnings (op0 == truthvalue_false_गाठ);
      op1 = c_fully_fold_internal (op1, in_init, &op1_const, &op1_const_self,
				   for_int_const, असत्य);
      STRIP_TYPE_NOPS (op1);
      c_enable_warnings (op0 == truthvalue_false_गाठ);

      c_disable_warnings (op0 == truthvalue_true_गाठ);
      op2 = c_fully_fold_internal (op2, in_init, &op2_const, &op2_const_self,
				   for_int_const, असत्य);
      STRIP_TYPE_NOPS (op2);
      c_enable_warnings (op0 == truthvalue_true_गाठ);

      यदि (for_int_const
	  && (वृक्ष_CODE (op0) != INTEGER_CST
	      /* Only the evaluated operand must be an INTEGER_CST.  */
	      || (op0 == truthvalue_true_गाठ
		  ? वृक्ष_CODE (op1) != INTEGER_CST
		  : वृक्ष_CODE (op2) != INTEGER_CST)))
	गच्छ out;

      यदि (op0 != orig_op0 || op1 != orig_op1 || op2 != orig_op2)
	ret = fold_build3_loc (loc, code, वृक्ष_TYPE (अभिव्यक्ती), op0, op1, op2);
      अन्यथा
	ret = fold (अभिव्यक्ती);
      *maybe_const_operands &= op0_const;
      *maybe_const_itself &= op0_const_self;
      यदि (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && op0 == truthvalue_false_गाठ))
	*maybe_const_operands &= op1_const;
      यदि (!(op0_const
	    && op0_const_self
	    && op0 == truthvalue_false_गाठ))
	*maybe_const_itself &= op1_const_self;
      यदि (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && op0 == truthvalue_true_गाठ))
	*maybe_const_operands &= op2_const;
      यदि (!(op0_const
	    && op0_const_self
	    && op0 == truthvalue_true_गाठ))
	*maybe_const_itself &= op2_const_self;
      गच्छ out;

    पक्ष VEC_COND_अभिव्यक्ती:
      orig_op0 = op0 = वृक्ष_OPERAND (अभिव्यक्ती, 0);
      orig_op1 = op1 = वृक्ष_OPERAND (अभिव्यक्ती, 1);
      orig_op2 = op2 = वृक्ष_OPERAND (अभिव्यक्ती, 2);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, असत्य);
      STRIP_TYPE_NOPS (op0);
      op1 = c_fully_fold_internal (op1, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, असत्य);
      STRIP_TYPE_NOPS (op1);
      op2 = c_fully_fold_internal (op2, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, असत्य);
      STRIP_TYPE_NOPS (op2);

      यदि (op0 != orig_op0 || op1 != orig_op1 || op2 != orig_op2)
	ret = fold_build3_loc (loc, code, वृक्ष_TYPE (अभिव्यक्ती), op0, op1, op2);
      अन्यथा
	ret = fold (अभिव्यक्ती);
      गच्छ out;

    पक्ष EXCESS_PRECISION_अभिव्यक्ती:
      /* Each case where an operand with excess precision may be
	 encountered must remove the EXCESS_PRECISION_EXPR around
	 inner operands and possibly put one around the whole
	 expression or possibly convert to the semantic type (which
	 c_fully_fold does); we cannot tell at this stage which is
	 appropriate in any particular case.  */
      gcc_unreachable ();

    पक्ष SAVE_अभिव्यक्ती:
      /* Make sure to fold the contents of a SAVE_EXPR exactly once.  */
      op0 = वृक्ष_OPERAND (अभिव्यक्ती, 0);
      यदि (!SAVE_अभिव्यक्ती_FOLDED_P (अभिव्यक्ती))
	{
	  op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				       maybe_const_itself, for_int_const,
				       असत्य);
	  वृक्ष_OPERAND (अभिव्यक्ती, 0) = op0;
	  SAVE_अभिव्यक्ती_FOLDED_P (अभिव्यक्ती) = सत्य;
	}
      /* Return the SAVE_EXPR operand if it is invariant.  */
      यदि (वृक्ष_invariant_p (op0))
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
  यदि (nowarning && !warning_suppressed_p (ret, OPT_Woverflow))
    {
      यदि (!CAN_HAVE_LOCATION_P (ret))
	ret = build1 (NOP_अभिव्यक्ती, वृक्ष_TYPE (ret), ret);
      suppress_warning (ret, OPT_Woverflow);
    }
  यदि (ret != अभिव्यक्ती)
    {
      protected_set_अभिव्यक्ती_location (ret, loc);
      यदि (IS_अभिव्यक्ती_CODE_CLASS (kind))
	set_source_range (ret, old_range.m_start, old_range.m_finish);
    }
  प्रत्यागम ret;
}

/* Fold X for consideration by one of the warning functions when checking
   whether an expression has a constant value.  */

वृक्ष
fold_for_warn (वृक्ष x)
{
  /* The C front-end has already folded X appropriately.  */
  प्रत्यागम x;
}
