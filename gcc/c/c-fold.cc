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

स्थिर वृक्षः c_fully_fold_आन्तरिकम् (वृक्षः व्यञ्जकम्, तार्किक, तार्किक *, तार्किक *, तार्किक,
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

स्थिर वृक्षः
c_fold_array_ref (वृक्षः type, वृक्षः ary, वृक्षः सूचकांक)
{
  यदि (वृक्षः_संहिता (ary) != STRING_CST
      || वृक्षः_संहिता (सूचकांक) != INTEGER_CST
      || वृक्षः_अतिप्रवाहः (सूचकांक)
      || वृक्षः_संहिता (वृक्षः_TYPE (ary)) != ARRAY_TYPE
      || !वृक्षः_माति_uhwi_p (सूचकांक))
    प्रत्यागम NULL_वृक्षः;

  वृक्षः elem_type = वृक्षः_TYPE (वृक्षः_TYPE (ary));
  अचिह्नित elem_nchars = (TYPE_PRECISION (elem_type)
			  / TYPE_PRECISION (char_type_ग्रन्थिः));
  अचिह्नित len = (अचिह्नित) वृक्षः_STRING_दीर्घता (ary) / elem_nchars;
  वृक्षः nelts_minus_one = array_type_nelts_minus_one (वृक्षः_TYPE (ary));
  तार्किक dummy1 = सत्य, dummy2 = सत्य;
  nelts_minus_one = c_fully_fold_आन्तरिकम् (nelts_minus_one, सत्य, &dummy1,
					   &dummy2, असत्य, असत्य);
  अचिह्नित HOST_WIDE_INT i = वृक्षः_गन्तव्यम्_uhwi (सूचकांक);
  यदि (!वृक्षः_int_cst_le (सूचकांक, nelts_minus_one)
      || i >= len
      || i + elem_nchars > len)
    प्रत्यागम NULL_वृक्षः;

  यदि (elem_nchars == 1)
    प्रत्यागम build_int_cst (type, वृक्षः_STRING_POINTER (ary)[i]);

  ध्रुव अचिह्नित वर्ण *ptr
    = ((ध्रुव अचिह्नित वर्ण *)वृक्षः_STRING_POINTER (ary) + i * elem_nchars);
  प्रत्यागम native_interpret_व्यञ्जकम् (type, ptr, elem_nchars);
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
c_fully_fold (वृक्षः व्यञ्जकम्, तार्किक अन्तर्_init, तार्किक *maybe_const, तार्किक lval)
{
  वृक्षः ret;
  वृक्षः eptype = NULL_वृक्षः;
  तार्किक dummy = सत्य;
  तार्किक maybe_const_itself = सत्य;
  location_t loc = व्यञ्जकम्_LOCATION (व्यञ्जकम्);

  यदि (!maybe_const)
    maybe_const = &dummy;
  यदि (वृक्षः_संहिता (व्यञ्जकम्) == EXCESS_PRECISION_व्यञ्जकम्)
    {
      eptype = वृक्षः_TYPE (व्यञ्जकम्);
      व्यञ्जकम् = वृक्षः_सङ्कार्यम् (व्यञ्जकम्, 0);
    }
  ret = c_fully_fold_आन्तरिकम् (व्यञ्जकम्, अन्तर्_init, maybe_const,
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

स्थिर वृक्षः
c_fully_fold_आन्तरिकम् (वृक्षः व्यञ्जकम्, तार्किक अन्तर्_init, तार्किक *maybe_const_operands,
		       तार्किक *maybe_const_itself, तार्किक for_int_const, तार्किक lval)
{
  वृक्षः ret = व्यञ्जकम्;
  गणना वृक्षः_संहिता_2 संहिता = वृक्षः_संहिता (व्यञ्जकम्);
  गणना वृक्षः_संहिता_class विधा = वृक्षः_संहिता_CLASS (संहिता);
  location_t loc = व्यञ्जकम्_LOCATION (व्यञ्जकम्);
  वृक्षः op0, op1, op2, op3;
  वृक्षः orig_op0, orig_op1, orig_op2;
  तार्किक op0_const = सत्य, op1_const = सत्य, op2_const = सत्य;
  तार्किक op0_const_self = सत्य, op1_const_self = सत्य, op2_const_self = सत्य;
  तार्किक nowarning = warning_suppressed_p (व्यञ्जकम्, OPT_Woverflow);
  तार्किक अप्रयुक्तम्_p;
  तार्किक op0_lval = असत्य;
  source_range old_range;

  /* Constants, declarations, statements, errors, and anything else not
     counted as an expression cannot usefully be folded further at this
     point.  */
  यदि (!IS_व्यञ्जकम्_संहिता_CLASS (विधा) || विधा == tcc_statement)
    {
      /* Except for variables which we can optimize to its initializer.  */
      यदि (VAR_P (व्यञ्जकम्) && !lval && (optimize || अन्तर्_init))
	{
	  यदि (अन्तर्_init)
	    ret = decl_constant_मानम्_1 (व्यञ्जकम्, सत्य);
	  अन्यथा
	    {
	      ret = decl_constant_मानम् (व्यञ्जकम्);
	      यदि (ret != व्यञ्जकम्
		  && (TYPE_बहुलकम् (वृक्षः_TYPE (ret)) == BLKmode
		      || वृक्षः_संहिता (वृक्षः_TYPE (ret)) == ARRAY_TYPE))
		प्रत्यागम व्यञ्जकम्;
	    }
	  /* Avoid unwanted tree sharing between the initializer and current
	     function's body where the tree can be modified e.g. by the
	     gimplifier.  */
	  यदि (ret != व्यञ्जकम् && वृक्षः_STATIC (व्यञ्जकम्))
	    ret = unshare_व्यञ्जकम् (ret);
	  प्रत्यागम ret;
	}
      प्रत्यागम व्यञ्जकम्;
    }

  यदि (IS_व्यञ्जकम्_संहिता_CLASS (विधा))
    old_range = व्यञ्जकम्_LOCATION_RANGE (व्यञ्जकम्);

  /* Operands of variable-length expressions (function calls) have
     already been folded, as have __builtin_* function calls, and such
     expressions cannot occur in constant expressions.  */
  यदि (विधा == tcc_vl_exp)
    {
      *maybe_const_operands = असत्य;
      ret = fold (व्यञ्जकम्);
      गच्छ बहिर्गमनम्;
    }

  यदि (संहिता == C_MAYBE_CONST_व्यञ्जकम्)
    {
      वृक्षः pre = C_MAYBE_CONST_व्यञ्जकम्_PRE (व्यञ्जकम्);
      वृक्षः inner = C_MAYBE_CONST_व्यञ्जकम्_व्यञ्जकम् (व्यञ्जकम्);
      यदि (C_MAYBE_CONST_व्यञ्जकम्_NON_CONST (व्यञ्जकम्))
	*maybe_const_operands = असत्य;
      यदि (C_MAYBE_CONST_व्यञ्जकम्_INT_OPERANDS (व्यञ्जकम्))
	{
	  *maybe_const_itself = असत्य;
	  inner = c_fully_fold_आन्तरिकम् (inner, अन्तर्_init, maybe_const_operands,
					 maybe_const_itself, सत्य, lval);
	}
      यदि (pre && !अन्तर्_init)
	ret = build2 (COMPOUND_व्यञ्जकम्, वृक्षः_TYPE (व्यञ्जकम्), pre, inner);
      अन्यथा
	ret = inner;
      गच्छ बहिर्गमनम्;
    }

  /* Assignment, increment, decrement, function call and comma
     operators, and statement expressions, cannot occur in constant
     expressions if evaluated / outside of sizeof.  (Function calls
     were handled above, though VA_ARG_EXPR is treated like a function
     call here, and statement expressions are handled through
     C_MAYBE_CONST_EXPR to avoid folding inside them.)  */
  विकल्प (संहिता)
    {
    पक्ष MODIFY_व्यञ्जकम्:
    पक्ष PREDECREMENT_व्यञ्जकम्:
    पक्ष PREINCREMENT_व्यञ्जकम्:
    पक्ष POSTDECREMENT_व्यञ्जकम्:
    पक्ष POSTINCREMENT_व्यञ्जकम्:
    पक्ष COMPOUND_व्यञ्जकम्:
      *maybe_const_operands = असत्य;
      भङ्ग;

    पक्ष VA_ARG_व्यञ्जकम्:
    पक्ष TARGET_व्यञ्जकम्:
    पक्ष BIND_व्यञ्जकम्:
    पक्ष OBJ_TYPE_REF:
      *maybe_const_operands = असत्य;
      ret = fold (व्यञ्जकम्);
      गच्छ बहिर्गमनम्;

    स्वभाव:
      भङ्ग;
    }

  /* Fold individual tree codes as appropriate.  */
  विकल्प (संहिता)
    {
    पक्ष COMPOUND_LITERAL_व्यञ्जकम्:
      /* Any non-constancy will have been marked in a containing
	 C_MAYBE_CONST_EXPR; there is no more folding to do here.  */
      गच्छ बहिर्गमनम्;

    पक्ष COMPONENT_REF:
      orig_op0 = op0 = वृक्षः_सङ्कार्यम् (व्यञ्जकम्, 0);
      op1 = वृक्षः_सङ्कार्यम् (व्यञ्जकम्, 1);
      op2 = वृक्षः_सङ्कार्यम् (व्यञ्जकम्, 2);
      op0 = c_fully_fold_आन्तरिकम् (op0, अन्तर्_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, lval);
      STRIP_TYPE_NOPS (op0);
      यदि (op0 != orig_op0)
	ret = build3 (COMPONENT_REF, वृक्षः_TYPE (व्यञ्जकम्), op0, op1, op2);
      यदि (ret != व्यञ्जकम्)
	{
	  वृक्षः_READONLY (ret) = वृक्षः_READONLY (व्यञ्जकम्);
	  वृक्षः_THIS_VOLATILE (ret) = वृक्षः_THIS_VOLATILE (व्यञ्जकम्);
	}
      यदि (!lval)
	ret = fold (ret);
      गच्छ बहिर्गमनम्;

    पक्ष ARRAY_REF:
      orig_op0 = op0 = वृक्षः_सङ्कार्यम् (व्यञ्जकम्, 0);
      orig_op1 = op1 = वृक्षः_सङ्कार्यम् (व्यञ्जकम्, 1);
      op2 = वृक्षः_सङ्कार्यम् (व्यञ्जकम्, 2);
      op3 = वृक्षः_सङ्कार्यम् (व्यञ्जकम्, 3);
      op0 = c_fully_fold_आन्तरिकम् (op0, अन्तर्_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, lval);
      STRIP_TYPE_NOPS (op0);
      op1 = c_fully_fold_आन्तरिकम् (op1, अन्तर्_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, असत्य);
      STRIP_TYPE_NOPS (op1);
      /* Fold "foo"[2] in initializers.  */
      यदि (!lval && अन्तर्_init)
	{
	  ret = c_fold_array_ref (वृक्षः_TYPE (व्यञ्जकम्), op0, op1);
	  यदि (ret)
	    गच्छ बहिर्गमनम्;
	  ret = व्यञ्जकम्;
	}
      यदि (op0 != orig_op0 || op1 != orig_op1)
	ret = build4 (ARRAY_REF, वृक्षः_TYPE (व्यञ्जकम्), op0, op1, op2, op3);
      यदि (ret != व्यञ्जकम्)
	{
	  वृक्षः_READONLY (ret) = वृक्षः_READONLY (व्यञ्जकम्);
	  वृक्षः_SIDE_EFFECTS (ret) = वृक्षः_SIDE_EFFECTS (व्यञ्जकम्);
	  वृक्षः_THIS_VOLATILE (ret) = वृक्षः_THIS_VOLATILE (व्यञ्जकम्);
	}
      यदि (!lval)
	ret = fold (ret);
      गच्छ बहिर्गमनम्;

    पक्ष MODIFY_व्यञ्जकम्:
    पक्ष PREDECREMENT_व्यञ्जकम्:
    पक्ष PREINCREMENT_व्यञ्जकम्:
    पक्ष POSTDECREMENT_व्यञ्जकम्:
    पक्ष POSTINCREMENT_व्यञ्जकम्:
      op0_lval = सत्य;
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
      orig_op0 = op0 = वृक्षः_सङ्कार्यम् (व्यञ्जकम्, 0);
      orig_op1 = op1 = वृक्षः_सङ्कार्यम् (व्यञ्जकम्, 1);
      op0 = c_fully_fold_आन्तरिकम् (op0, अन्तर्_init, maybe_const_operands,
				   maybe_const_itself, for_int_const,
				   op0_lval);
      STRIP_TYPE_NOPS (op0);
      /* The RHS of a MODIFY_EXPR was fully folded when building that
	 expression for the sake of conversion warnings.  */
      यदि (संहिता != MODIFY_व्यञ्जकम्)
	op1 = c_fully_fold_आन्तरिकम् (op1, अन्तर्_init, maybe_const_operands,
				     maybe_const_itself, for_int_const, असत्य);
      STRIP_TYPE_NOPS (op1);

      यदि (for_int_const && (वृक्षः_संहिता (op0) != INTEGER_CST
			    || वृक्षः_संहिता (op1) != INTEGER_CST))
	गच्छ बहिर्गमनम्;

      यदि (वृक्षः_संहिता_CLASS (संहिता) == tcc_comparison
	  && वृक्षः_संहिता (वृक्षः_TYPE (op0)) == NULLPTR_TYPE
	  && वृक्षः_संहिता (वृक्षः_TYPE (op1)) == NULLPTR_TYPE)
	{
	  विकल्प (संहिता)
	    {
	    पक्ष EQ_व्यञ्जकम्:
	      ret = constant_boolean_ग्रन्थिः (सत्य, वृक्षः_TYPE (व्यञ्जकम्));
	      भङ्ग;
	    पक्ष NE_व्यञ्जकम्:
	      ret = constant_boolean_ग्रन्थिः (असत्य, वृक्षः_TYPE (व्यञ्जकम्));
	      भङ्ग;
	    स्वभाव:
	      gcc_unreachable ();
	    }
	  ret = omit_two_operands_loc (loc, वृक्षः_TYPE (व्यञ्जकम्), ret,
				       op0, op1);
	}
      अन्यथा यदि (op0 != orig_op0 || op1 != orig_op1 || अन्तर्_init)
	ret = अन्तर्_init
	  ? fold_build2_initializer_loc (loc, संहिता, वृक्षः_TYPE (व्यञ्जकम्), op0, op1)
	  : fold_build2_loc (loc, संहिता, वृक्षः_TYPE (व्यञ्जकम्), op0, op1);
      अन्यथा
	ret = fold (व्यञ्जकम्);
      यदि (वृक्षः_अतिप्रवाहः_P (ret)
	  && !वृक्षः_अतिप्रवाहः_P (op0)
	  && !(द्विमान_CLASS_P (op0) && वृक्षः_अतिप्रवाहः_P (वृक्षः_सङ्कार्यम् (op0, 1)))
	  && !वृक्षः_अतिप्रवाहः_P (op1))
	अतिप्रवाहः_warning (व्यञ्जकम्_LOC_OR_LOC (व्यञ्जकम्, निवेशः_location), ret, व्यञ्जकम्);
      यदि (संहिता == LSHIFT_व्यञ्जकम्
	  && वृक्षः_संहिता (orig_op0) != INTEGER_CST
	  && (वृक्षः_संहिता (वृक्षः_TYPE (orig_op0)) == INTEGER_TYPE
	      || वृक्षः_संहिता (वृक्षः_TYPE (orig_op0)) == BITINT_TYPE)
	  && वृक्षः_संहिता (op0) == INTEGER_CST
	  && c_inhibit_evaluation_warnings == 0
	  && !TYPE_अतिप्रवाहः_WRAPS (वृक्षः_TYPE (orig_op0))
	  && वृक्षः_int_cst_sgn (op0) < 0)
	warning_at (loc, OPT_Wshift_negative_मानम्,
		    "left shift of negative value");
      यदि ((संहिता == LSHIFT_व्यञ्जकम्
	   || संहिता == RSHIFT_व्यञ्जकम्
	   || संहिता == LROTATE_व्यञ्जकम्
	   || संहिता == RROTATE_व्यञ्जकम्)
	  && वृक्षः_संहिता (orig_op1) != INTEGER_CST
	  && वृक्षः_संहिता (op1) == INTEGER_CST
	  && वृक्षः_संहिता (वृक्षः_TYPE (orig_op1)) == INTEGER_TYPE
	  && c_inhibit_evaluation_warnings == 0)
	{
	  यदि (वृक्षः_int_cst_sgn (op1) < 0)
	    warning_at (loc, OPT_Wshift_गणनम्_negative,
			(संहिता == LSHIFT_व्यञ्जकम्
			 ? G_("left shift count is negative")
			 : G_("right shift count is negative")));
	  अन्यथा यदि ((वृक्षः_संहिता (वृक्षः_TYPE (orig_op0)) == INTEGER_TYPE
		    || वृक्षः_संहिता (वृक्षः_TYPE (orig_op0)) == BITINT_TYPE
		    || वृक्षः_संहिता (वृक्षः_TYPE (orig_op0)) == FIXED_POINT_TYPE)
		   && compare_वृक्षः_int (op1,
					TYPE_PRECISION (वृक्षः_TYPE (orig_op0)))
		      >= 0
		   && !warning_suppressed_p (व्यञ्जकम्, OPT_Wshift_गणनम्_अतिप्रवाहः))
	    warning_at (loc, OPT_Wshift_गणनम्_अतिप्रवाहः,
			(संहिता == LSHIFT_व्यञ्जकम्
			 ? G_("left shift count >= width of type")
			 : G_("right shift count >= width of type")));
	  अन्यथा यदि (वृक्षः_संहिता (वृक्षः_TYPE (orig_op0)) == सदिशम्_TYPE
		   && compare_वृक्षः_int (op1,
					TYPE_PRECISION (वृक्षः_TYPE (वृक्षः_TYPE (orig_op0))))
		      >= 0)
	    warning_at (loc, OPT_Wshift_गणनम्_अतिप्रवाहः,
			संहिता == LSHIFT_व्यञ्जकम्
			? G_("left shift count >= width of vector element")
			: G_("right shift count >= width of vector element"));
	}
      यदि (संहिता == LSHIFT_व्यञ्जकम्
	  /* If either OP0 has been folded to INTEGER_CST...  */
	  && ((वृक्षः_संहिता (orig_op0) != INTEGER_CST
	       && (वृक्षः_संहिता (वृक्षः_TYPE (orig_op0)) == INTEGER_TYPE
		   || वृक्षः_संहिता (वृक्षः_TYPE (orig_op0)) == BITINT_TYPE)
	       && वृक्षः_संहिता (op0) == INTEGER_CST)
	      /* ...or if OP1 has been folded to INTEGER_CST...  */
	      || (वृक्षः_संहिता (orig_op1) != INTEGER_CST
		  && (वृक्षः_संहिता (वृक्षः_TYPE (orig_op1)) == INTEGER_TYPE
		      || वृक्षः_संहिता (वृक्षः_TYPE (orig_op1)) == BITINT_TYPE)
		  && वृक्षः_संहिता (op1) == INTEGER_CST))
	  && c_inhibit_evaluation_warnings == 0)
	/* ...then maybe we can detect an overflow.  */
	maybe_warn_सरणम्_अतिप्रवाहः (loc, op0, op1);
      यदि ((संहिता == TRUNC_DIV_व्यञ्जकम्
	   || संहिता == CEIL_DIV_व्यञ्जकम्
	   || संहिता == FLOOR_DIV_व्यञ्जकम्
	   || संहिता == EXACT_DIV_व्यञ्जकम्
	   || संहिता == TRUNC_MOD_व्यञ्जकम्)
	  && वृक्षः_संहिता (orig_op1) != INTEGER_CST
	  && वृक्षः_संहिता (op1) == INTEGER_CST
	  && (वृक्षः_संहिता (वृक्षः_TYPE (orig_op0)) == INTEGER_TYPE
	      || वृक्षः_संहिता (वृक्षः_TYPE (orig_op0)) == BITINT_TYPE
	      || वृक्षः_संहिता (वृक्षः_TYPE (orig_op0)) == FIXED_POINT_TYPE)
	  && (वृक्षः_संहिता (वृक्षः_TYPE (orig_op1)) == INTEGER_TYPE
	      || वृक्षः_संहिता (वृक्षः_TYPE (orig_op1)) == BITINT_TYPE))
	warn_for_div_by_zero (loc, op1);
      यदि (संहिता == MEM_REF
	  && ret != व्यञ्जकम्
	  && वृक्षः_संहिता (ret) == MEM_REF)
	{
	  वृक्षः_READONLY (ret) = वृक्षः_READONLY (व्यञ्जकम्);
	  वृक्षः_SIDE_EFFECTS (ret) = वृक्षः_SIDE_EFFECTS (व्यञ्जकम्);
	  वृक्षः_THIS_VOLATILE (ret) = वृक्षः_THIS_VOLATILE (व्यञ्जकम्);
	}
      गच्छ बहिर्गमनम्;

    पक्ष ADDR_व्यञ्जकम्:
      op0_lval = सत्य;
      गच्छ unary;
    पक्ष REALPART_व्यञ्जकम्:
    पक्ष IMAGPART_व्यञ्जकम्:
    पक्ष VIEW_CONVERT_व्यञ्जकम्:
      op0_lval = lval;
      /* FALLTHRU */
    पक्ष परोक्षम्_REF:
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
      orig_op0 = op0 = वृक्षः_सङ्कार्यम् (व्यञ्जकम्, 0);
      op0 = c_fully_fold_आन्तरिकम् (op0, अन्तर्_init, maybe_const_operands,
				   maybe_const_itself, for_int_const,
				   op0_lval);
      STRIP_TYPE_NOPS (op0);

      यदि (for_int_const && वृक्षः_संहिता (op0) != INTEGER_CST)
	गच्छ बहिर्गमनम्;

      /* ??? Cope with user tricks that amount to offsetof.  The middle-end is
	 not prepared to deal with them if they occur in initializers.  */
      यदि (op0 != orig_op0
	  && संहिता == ADDR_व्यञ्जकम्
	  && (op1 = get_आधारः_स्थानाङ्कः (op0)) != NULL_वृक्षः
	  && परोक्षम्_REF_P (op1)
	  && वृक्षः_CONSTANT (वृक्षः_सङ्कार्यम् (op1, 0)))
	ret = fold_offsetof (op0, वृक्षः_TYPE (व्यञ्जकम्));
      अन्यथा यदि (op0 != orig_op0 || अन्तर्_init)
	ret = अन्तर्_init
	  ? fold_build1_initializer_loc (loc, संहिता, वृक्षः_TYPE (व्यञ्जकम्), op0)
	  : fold_build1_loc (loc, संहिता, वृक्षः_TYPE (व्यञ्जकम्), op0);
      अन्यथा
	ret = fold (व्यञ्जकम्);
      यदि (संहिता == परोक्षम्_REF
	  && ret != व्यञ्जकम्
	  && परोक्षम्_REF_P (ret))
	{
	  वृक्षः_READONLY (ret) = वृक्षः_READONLY (व्यञ्जकम्);
	  वृक्षः_SIDE_EFFECTS (ret) = वृक्षः_SIDE_EFFECTS (व्यञ्जकम्);
	  वृक्षः_THIS_VOLATILE (ret) = वृक्षः_THIS_VOLATILE (व्यञ्जकम्);
	}
      विकल्प (संहिता)
	{
	पक्ष FIX_TRUNC_व्यञ्जकम्:
	पक्ष FLOAT_व्यञ्जकम्:
	CASE_CONVERT:
	  /* Don't warn about explicit conversions.  We will already
	     have warned about suspect implicit conversions.  */
	  भङ्ग;

	स्वभाव:
	  यदि (वृक्षः_अतिप्रवाहः_P (ret) && !वृक्षः_अतिप्रवाहः_P (op0))
	    अतिप्रवाहः_warning (व्यञ्जकम्_LOCATION (व्यञ्जकम्), ret, op0);
	  भङ्ग;
	}
      गच्छ बहिर्गमनम्;

    पक्ष TRUTH_ANDIF_व्यञ्जकम्:
    पक्ष TRUTH_ORIF_व्यञ्जकम्:
      /* Binary operations not necessarily evaluating both
	 arguments.  */
      orig_op0 = op0 = वृक्षः_सङ्कार्यम् (व्यञ्जकम्, 0);
      orig_op1 = op1 = वृक्षः_सङ्कार्यम् (व्यञ्जकम्, 1);
      op0 = c_fully_fold_आन्तरिकम् (op0, अन्तर्_init, &op0_const, &op0_const_self,
				   for_int_const, असत्य);
      STRIP_TYPE_NOPS (op0);

      अप्रयुक्तम्_p = (op0 == (संहिता == TRUTH_ANDIF_व्यञ्जकम्
			  ? truthvalue_false_ग्रन्थिः
			  : truthvalue_true_ग्रन्थिः));
      c_disable_warnings (अप्रयुक्तम्_p);
      op1 = c_fully_fold_आन्तरिकम् (op1, अन्तर्_init, &op1_const, &op1_const_self,
				   for_int_const, असत्य);
      STRIP_TYPE_NOPS (op1);
      c_enable_warnings (अप्रयुक्तम्_p);

      यदि (for_int_const
	  && (वृक्षः_संहिता (op0) != INTEGER_CST
	      /* Require OP1 be an INTEGER_CST only if it's evaluated.  */
	      || (!अप्रयुक्तम्_p && वृक्षः_संहिता (op1) != INTEGER_CST)))
	गच्छ बहिर्गमनम्;

      यदि (op0 != orig_op0 || op1 != orig_op1 || अन्तर्_init)
	ret = अन्तर्_init
	  ? fold_build2_initializer_loc (loc, संहिता, वृक्षः_TYPE (व्यञ्जकम्), op0, op1)
	  : fold_build2_loc (loc, संहिता, वृक्षः_TYPE (व्यञ्जकम्), op0, op1);
      अन्यथा
	ret = fold (व्यञ्जकम्);
      *maybe_const_operands &= op0_const;
      *maybe_const_itself &= op0_const_self;
      यदि (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && (संहिता == TRUTH_ANDIF_व्यञ्जकम्
		? op0 == truthvalue_false_ग्रन्थिः
		: op0 == truthvalue_true_ग्रन्थिः)))
	*maybe_const_operands &= op1_const;
      यदि (!(op0_const
	    && op0_const_self
	    && (संहिता == TRUTH_ANDIF_व्यञ्जकम्
		? op0 == truthvalue_false_ग्रन्थिः
		: op0 == truthvalue_true_ग्रन्थिः)))
	*maybe_const_itself &= op1_const_self;
      गच्छ बहिर्गमनम्;

    पक्ष COND_व्यञ्जकम्:
      orig_op0 = op0 = वृक्षः_सङ्कार्यम् (व्यञ्जकम्, 0);
      orig_op1 = op1 = वृक्षः_सङ्कार्यम् (व्यञ्जकम्, 1);
      orig_op2 = op2 = वृक्षः_सङ्कार्यम् (व्यञ्जकम्, 2);
      op0 = c_fully_fold_आन्तरिकम् (op0, अन्तर्_init, &op0_const, &op0_const_self,
				   for_int_const, असत्य);

      STRIP_TYPE_NOPS (op0);
      c_disable_warnings (op0 == truthvalue_false_ग्रन्थिः);
      op1 = c_fully_fold_आन्तरिकम् (op1, अन्तर्_init, &op1_const, &op1_const_self,
				   for_int_const, असत्य);
      STRIP_TYPE_NOPS (op1);
      c_enable_warnings (op0 == truthvalue_false_ग्रन्थिः);

      c_disable_warnings (op0 == truthvalue_true_ग्रन्थिः);
      op2 = c_fully_fold_आन्तरिकम् (op2, अन्तर्_init, &op2_const, &op2_const_self,
				   for_int_const, असत्य);
      STRIP_TYPE_NOPS (op2);
      c_enable_warnings (op0 == truthvalue_true_ग्रन्थिः);

      यदि (for_int_const
	  && (वृक्षः_संहिता (op0) != INTEGER_CST
	      /* Only the evaluated operand must be an INTEGER_CST.  */
	      || (op0 == truthvalue_true_ग्रन्थिः
		  ? वृक्षः_संहिता (op1) != INTEGER_CST
		  : वृक्षः_संहिता (op2) != INTEGER_CST)))
	गच्छ बहिर्गमनम्;

      यदि (op0 != orig_op0 || op1 != orig_op1 || op2 != orig_op2)
	ret = fold_build3_loc (loc, संहिता, वृक्षः_TYPE (व्यञ्जकम्), op0, op1, op2);
      अन्यथा
	ret = fold (व्यञ्जकम्);
      *maybe_const_operands &= op0_const;
      *maybe_const_itself &= op0_const_self;
      यदि (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && op0 == truthvalue_false_ग्रन्थिः))
	*maybe_const_operands &= op1_const;
      यदि (!(op0_const
	    && op0_const_self
	    && op0 == truthvalue_false_ग्रन्थिः))
	*maybe_const_itself &= op1_const_self;
      यदि (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && op0 == truthvalue_true_ग्रन्थिः))
	*maybe_const_operands &= op2_const;
      यदि (!(op0_const
	    && op0_const_self
	    && op0 == truthvalue_true_ग्रन्थिः))
	*maybe_const_itself &= op2_const_self;
      गच्छ बहिर्गमनम्;

    पक्ष VEC_COND_व्यञ्जकम्:
      orig_op0 = op0 = वृक्षः_सङ्कार्यम् (व्यञ्जकम्, 0);
      orig_op1 = op1 = वृक्षः_सङ्कार्यम् (व्यञ्जकम्, 1);
      orig_op2 = op2 = वृक्षः_सङ्कार्यम् (व्यञ्जकम्, 2);
      op0 = c_fully_fold_आन्तरिकम् (op0, अन्तर्_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, असत्य);
      STRIP_TYPE_NOPS (op0);
      op1 = c_fully_fold_आन्तरिकम् (op1, अन्तर्_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, असत्य);
      STRIP_TYPE_NOPS (op1);
      op2 = c_fully_fold_आन्तरिकम् (op2, अन्तर्_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, असत्य);
      STRIP_TYPE_NOPS (op2);

      यदि (op0 != orig_op0 || op1 != orig_op1 || op2 != orig_op2)
	ret = fold_build3_loc (loc, संहिता, वृक्षः_TYPE (व्यञ्जकम्), op0, op1, op2);
      अन्यथा
	ret = fold (व्यञ्जकम्);
      गच्छ बहिर्गमनम्;

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
      op0 = वृक्षः_सङ्कार्यम् (व्यञ्जकम्, 0);
      यदि (!SAVE_व्यञ्जकम्_FOLDED_P (व्यञ्जकम्))
	{
	  op0 = c_fully_fold_आन्तरिकम् (op0, अन्तर्_init, maybe_const_operands,
				       maybe_const_itself, for_int_const,
				       असत्य);
	  वृक्षः_सङ्कार्यम् (व्यञ्जकम्, 0) = op0;
	  SAVE_व्यञ्जकम्_FOLDED_P (व्यञ्जकम्) = सत्य;
	}
      /* Return the SAVE_EXPR operand if it is invariant.  */
      यदि (वृक्षः_invariant_p (op0))
	ret = op0;
      गच्छ बहिर्गमनम्;

    स्वभाव:
      /* Various codes may appear through folding built-in functions
	 and their arguments.  */
      गच्छ बहिर्गमनम्;
    }

 बहिर्गमनम्:
  /* Some folding may introduce NON_LVALUE_EXPRs; all lvalue checks
     have been done by this point, so remove them again.  */
  nowarning |= warning_suppressed_p (ret, OPT_Woverflow);
  STRIP_TYPE_NOPS (ret);
  यदि (nowarning && !warning_suppressed_p (ret, OPT_Woverflow))
    {
      यदि (!CAN_HAVE_LOCATION_P (ret))
	ret = build1 (NOP_व्यञ्जकम्, वृक्षः_TYPE (ret), ret);
      suppress_warning (ret, OPT_Woverflow);
    }
  यदि (ret != व्यञ्जकम्)
    {
      protected_समुच्चयः_व्यञ्जकम्_location (ret, loc);
      यदि (IS_व्यञ्जकम्_संहिता_CLASS (विधा))
	समुच्चयः_source_range (ret, old_range.m_start, old_range.m_finish);
    }
  प्रत्यागम ret;
}

/* Fold X for consideration by one of the warning functions when checking
   whether an expression has a constant value.  */

वृक्षः
fold_for_warn (वृक्षः x)
{
  /* The C front-end has already folded X appropriately.  */
  प्रत्यागम x;
}
