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

#समावेश "config.h"
#समावेश "system.h"
#समावेश "coretypes.h"
#समावेश "target.h"
#समावेश "function.h"
#समावेश "bitmap.h"
#समावेश "c-tree.h"
#समावेश "intl.h"
#समावेश "gimplify.h"

अटल वृक्ष c_fully_fold_internal (वृक्ष व्यंजक, bool, bool *, bool *, bool,
				   bool);

/* If DISABLE is true, stop issuing warnings.  This is used when
   parsing code that we know will not be executed.  This function may
   be called multiple times, and works as a stack.  */

अटल व्योम
c_disable_warnings (bool disable)
{
  अगर (disable)
    {
      ++c_inhibit_evaluation_warnings;
    }
}

/* If ENABLE is true, re-enable issuing warnings.  */

अटल व्योम
c_enable_warnings (bool enable)
{
  अगर (enable)
    {
      --c_inhibit_evaluation_warnings;
    }
}

/* Try to fold ARRAY_REF ary[index] if possible and not handled by
   normal fold, return NULL_TREE otherwise.  */

अटल वृक्ष
c_fold_array_ref (वृक्ष type, वृक्ष ary, वृक्ष सूचकांक)
{
  अगर (वृक्ष_CODE (ary) != STRING_CST
      || वृक्ष_CODE (सूचकांक) != INTEGER_CST
      || वृक्ष_OVERFLOW (सूचकांक)
      || वृक्ष_CODE (वृक्ष_TYPE (ary)) != ARRAY_TYPE
      || !वृक्ष_fits_uhwi_p (सूचकांक))
    वापस NULL_वृक्ष;

  वृक्ष elem_type = वृक्ष_TYPE (वृक्ष_TYPE (ary));
  अचिन्हित elem_nchars = (TYPE_PRECISION (elem_type)
			  / TYPE_PRECISION (char_type_गाँठ));
  अचिन्हित len = (अचिन्हित) वृक्ष_STRING_लंबाई (ary) / elem_nchars;
  वृक्ष nelts_minus_one = array_type_nelts_minus_one (वृक्ष_TYPE (ary));
  bool dummy1 = true, dummy2 = true;
  nelts_minus_one = c_fully_fold_internal (nelts_minus_one, true, &dummy1,
					   &dummy2, false, false);
  अचिन्हित HOST_WIDE_INT i = वृक्ष_to_uhwi (सूचकांक);
  अगर (!वृक्ष_int_cst_le (सूचकांक, nelts_minus_one)
      || i >= len
      || i + elem_nchars > len)
    वापस NULL_वृक्ष;

  अगर (elem_nchars == 1)
    वापस build_int_cst (type, वृक्ष_STRING_POINTER (ary)[i]);

  स्थिर अचिन्हित अक्षर *ptr
    = ((स्थिर अचिन्हित अक्षर *)वृक्ष_STRING_POINTER (ary) + i * elem_nchars);
  वापस native_interpret_व्यंजक (type, ptr, elem_nchars);
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
c_fully_fold (वृक्ष व्यंजक, bool in_init, bool *maybe_const, bool lval)
{
  वृक्ष ret;
  वृक्ष eptype = NULL_वृक्ष;
  bool dummy = true;
  bool maybe_const_itself = true;
  location_t loc = व्यंजक_LOCATION (व्यंजक);

  अगर (!maybe_const)
    maybe_const = &dummy;
  अगर (वृक्ष_CODE (व्यंजक) == EXCESS_PRECISION_व्यंजक)
    {
      eptype = वृक्ष_TYPE (व्यंजक);
      व्यंजक = वृक्ष_OPERAND (व्यंजक, 0);
    }
  ret = c_fully_fold_internal (व्यंजक, in_init, maybe_const,
			       &maybe_const_itself, false, lval);
  अगर (eptype)
    ret = fold_convert_loc (loc, eptype, ret);
  *maybe_const &= maybe_const_itself;
  वापस ret;
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

अटल वृक्ष
c_fully_fold_internal (वृक्ष व्यंजक, bool in_init, bool *maybe_const_operands,
		       bool *maybe_const_itself, bool for_int_const, bool lval)
{
  वृक्ष ret = व्यंजक;
  क्रमागत वृक्ष_code code = वृक्ष_CODE (व्यंजक);
  क्रमागत वृक्ष_code_class kind = वृक्ष_CODE_CLASS (code);
  location_t loc = व्यंजक_LOCATION (व्यंजक);
  वृक्ष op0, op1, op2, op3;
  वृक्ष orig_op0, orig_op1, orig_op2;
  bool op0_const = true, op1_const = true, op2_const = true;
  bool op0_const_self = true, op1_const_self = true, op2_const_self = true;
  bool nowarning = warning_suppressed_p (व्यंजक, OPT_Woverflow);
  bool unused_p;
  bool op0_lval = false;
  source_range old_range;

  /* Constants, declarations, statements, errors, and anything else not
     counted as an expression cannot usefully be folded further at this
     point.  */
  अगर (!IS_व्यंजक_CODE_CLASS (kind) || kind == tcc_statement)
    {
      /* Except for variables which we can optimize to its initializer.  */
      अगर (VAR_P (व्यंजक) && !lval && (optimize || in_init))
	{
	  अगर (in_init)
	    ret = decl_constant_मूल्य_1 (व्यंजक, true);
	  अन्यथा
	    {
	      ret = decl_constant_मूल्य (व्यंजक);
	      अगर (ret != व्यंजक
		  && (TYPE_MODE (वृक्ष_TYPE (ret)) == BLKmode
		      || वृक्ष_CODE (वृक्ष_TYPE (ret)) == ARRAY_TYPE))
		वापस व्यंजक;
	    }
	  /* Avoid unwanted tree sharing between the initializer and current
	     function's body where the tree can be modified e.g. by the
	     gimplifier.  */
	  अगर (ret != व्यंजक && वृक्ष_STATIC (व्यंजक))
	    ret = unshare_व्यंजक (ret);
	  वापस ret;
	}
      वापस व्यंजक;
    }

  अगर (IS_व्यंजक_CODE_CLASS (kind))
    old_range = व्यंजक_LOCATION_RANGE (व्यंजक);

  /* Operands of variable-length expressions (function calls) have
     already been folded, as have __builtin_* function calls, and such
     expressions cannot occur in constant expressions.  */
  अगर (kind == tcc_vl_exp)
    {
      *maybe_const_operands = false;
      ret = fold (व्यंजक);
      जाओ out;
    }

  अगर (code == C_MAYBE_CONST_व्यंजक)
    {
      वृक्ष pre = C_MAYBE_CONST_व्यंजक_PRE (व्यंजक);
      वृक्ष inner = C_MAYBE_CONST_व्यंजक_व्यंजक (व्यंजक);
      अगर (C_MAYBE_CONST_व्यंजक_NON_CONST (व्यंजक))
	*maybe_const_operands = false;
      अगर (C_MAYBE_CONST_व्यंजक_INT_OPERANDS (व्यंजक))
	{
	  *maybe_const_itself = false;
	  inner = c_fully_fold_internal (inner, in_init, maybe_const_operands,
					 maybe_const_itself, true, lval);
	}
      अगर (pre && !in_init)
	ret = build2 (COMPOUND_व्यंजक, वृक्ष_TYPE (व्यंजक), pre, inner);
      अन्यथा
	ret = inner;
      जाओ out;
    }

  /* Assignment, increment, decrement, function call and comma
     operators, and statement expressions, cannot occur in constant
     expressions if evaluated / outside of sizeof.  (Function calls
     were handled above, though VA_ARG_EXPR is treated like a function
     call here, and statement expressions are handled through
     C_MAYBE_CONST_EXPR to avoid folding inside them.)  */
  चयन (code)
    {
    हाल MODIFY_व्यंजक:
    हाल PREDECREMENT_व्यंजक:
    हाल PREINCREMENT_व्यंजक:
    हाल POSTDECREMENT_व्यंजक:
    हाल POSTINCREMENT_व्यंजक:
    हाल COMPOUND_व्यंजक:
      *maybe_const_operands = false;
      अवरोध;

    हाल VA_ARG_व्यंजक:
    हाल TARGET_व्यंजक:
    हाल BIND_व्यंजक:
    हाल OBJ_TYPE_REF:
      *maybe_const_operands = false;
      ret = fold (व्यंजक);
      जाओ out;

    शेष:
      अवरोध;
    }

  /* Fold individual tree codes as appropriate.  */
  चयन (code)
    {
    हाल COMPOUND_LITERAL_व्यंजक:
      /* Any non-constancy will have been marked in a containing
	 C_MAYBE_CONST_EXPR; there is no more folding to do here.  */
      जाओ out;

    हाल COMPONENT_REF:
      orig_op0 = op0 = वृक्ष_OPERAND (व्यंजक, 0);
      op1 = वृक्ष_OPERAND (व्यंजक, 1);
      op2 = वृक्ष_OPERAND (व्यंजक, 2);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, lval);
      STRIP_TYPE_NOPS (op0);
      अगर (op0 != orig_op0)
	ret = build3 (COMPONENT_REF, वृक्ष_TYPE (व्यंजक), op0, op1, op2);
      अगर (ret != व्यंजक)
	{
	  वृक्ष_READONLY (ret) = वृक्ष_READONLY (व्यंजक);
	  वृक्ष_THIS_VOLATILE (ret) = वृक्ष_THIS_VOLATILE (व्यंजक);
	}
      अगर (!lval)
	ret = fold (ret);
      जाओ out;

    हाल ARRAY_REF:
      orig_op0 = op0 = वृक्ष_OPERAND (व्यंजक, 0);
      orig_op1 = op1 = वृक्ष_OPERAND (व्यंजक, 1);
      op2 = वृक्ष_OPERAND (व्यंजक, 2);
      op3 = वृक्ष_OPERAND (व्यंजक, 3);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, lval);
      STRIP_TYPE_NOPS (op0);
      op1 = c_fully_fold_internal (op1, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, false);
      STRIP_TYPE_NOPS (op1);
      /* Fold "foo"[2] in initializers.  */
      अगर (!lval && in_init)
	{
	  ret = c_fold_array_ref (वृक्ष_TYPE (व्यंजक), op0, op1);
	  अगर (ret)
	    जाओ out;
	  ret = व्यंजक;
	}
      अगर (op0 != orig_op0 || op1 != orig_op1)
	ret = build4 (ARRAY_REF, वृक्ष_TYPE (व्यंजक), op0, op1, op2, op3);
      अगर (ret != व्यंजक)
	{
	  वृक्ष_READONLY (ret) = वृक्ष_READONLY (व्यंजक);
	  वृक्ष_SIDE_EFFECTS (ret) = वृक्ष_SIDE_EFFECTS (व्यंजक);
	  वृक्ष_THIS_VOLATILE (ret) = वृक्ष_THIS_VOLATILE (व्यंजक);
	}
      अगर (!lval)
	ret = fold (ret);
      जाओ out;

    हाल MODIFY_व्यंजक:
    हाल PREDECREMENT_व्यंजक:
    हाल PREINCREMENT_व्यंजक:
    हाल POSTDECREMENT_व्यंजक:
    हाल POSTINCREMENT_व्यंजक:
      op0_lval = true;
      /* FALLTHRU */
    हाल COMPOUND_व्यंजक:
    हाल PLUS_व्यंजक:
    हाल MINUS_व्यंजक:
    हाल MULT_व्यंजक:
    हाल POINTER_PLUS_व्यंजक:
    हाल POINTER_DIFF_व्यंजक:
    हाल TRUNC_DIV_व्यंजक:
    हाल CEIL_DIV_व्यंजक:
    हाल FLOOR_DIV_व्यंजक:
    हाल TRUNC_MOD_व्यंजक:
    हाल RDIV_व्यंजक:
    हाल EXACT_DIV_व्यंजक:
    हाल LSHIFT_व्यंजक:
    हाल RSHIFT_व्यंजक:
    हाल LROTATE_व्यंजक:
    हाल RROTATE_व्यंजक:
    हाल BIT_IOR_व्यंजक:
    हाल BIT_XOR_व्यंजक:
    हाल BIT_AND_व्यंजक:
    हाल LT_व्यंजक:
    हाल LE_व्यंजक:
    हाल GT_व्यंजक:
    हाल GE_व्यंजक:
    हाल EQ_व्यंजक:
    हाल NE_व्यंजक:
    हाल COMPLEX_व्यंजक:
    हाल TRUTH_AND_व्यंजक:
    हाल TRUTH_OR_व्यंजक:
    हाल TRUTH_XOR_व्यंजक:
    हाल UNORDERED_व्यंजक:
    हाल ORDERED_व्यंजक:
    हाल UNLT_व्यंजक:
    हाल UNLE_व्यंजक:
    हाल UNGT_व्यंजक:
    हाल UNGE_व्यंजक:
    हाल UNEQ_व्यंजक:
    हाल MEM_REF:
      /* Binary operations evaluating both arguments (increment and
	 decrement are binary internally in GCC).  */
      orig_op0 = op0 = वृक्ष_OPERAND (व्यंजक, 0);
      orig_op1 = op1 = वृक्ष_OPERAND (व्यंजक, 1);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const,
				   op0_lval);
      STRIP_TYPE_NOPS (op0);
      /* The RHS of a MODIFY_EXPR was fully folded when building that
	 expression for the sake of conversion warnings.  */
      अगर (code != MODIFY_व्यंजक)
	op1 = c_fully_fold_internal (op1, in_init, maybe_const_operands,
				     maybe_const_itself, for_int_const, false);
      STRIP_TYPE_NOPS (op1);

      अगर (for_int_const && (वृक्ष_CODE (op0) != INTEGER_CST
			    || वृक्ष_CODE (op1) != INTEGER_CST))
	जाओ out;

      अगर (वृक्ष_CODE_CLASS (code) == tcc_comparison
	  && वृक्ष_CODE (वृक्ष_TYPE (op0)) == NULLPTR_TYPE
	  && वृक्ष_CODE (वृक्ष_TYPE (op1)) == NULLPTR_TYPE)
	{
	  चयन (code)
	    {
	    हाल EQ_व्यंजक:
	      ret = constant_boolean_गाँठ (true, वृक्ष_TYPE (व्यंजक));
	      अवरोध;
	    हाल NE_व्यंजक:
	      ret = constant_boolean_गाँठ (false, वृक्ष_TYPE (व्यंजक));
	      अवरोध;
	    शेष:
	      gcc_unreachable ();
	    }
	  ret = omit_two_operands_loc (loc, वृक्ष_TYPE (व्यंजक), ret,
				       op0, op1);
	}
      अन्यथा अगर (op0 != orig_op0 || op1 != orig_op1 || in_init)
	ret = in_init
	  ? fold_build2_initializer_loc (loc, code, वृक्ष_TYPE (व्यंजक), op0, op1)
	  : fold_build2_loc (loc, code, वृक्ष_TYPE (व्यंजक), op0, op1);
      अन्यथा
	ret = fold (व्यंजक);
      अगर (वृक्ष_OVERFLOW_P (ret)
	  && !वृक्ष_OVERFLOW_P (op0)
	  && !(द्विआधारी_CLASS_P (op0) && वृक्ष_OVERFLOW_P (वृक्ष_OPERAND (op0, 1)))
	  && !वृक्ष_OVERFLOW_P (op1))
	overflow_warning (व्यंजक_LOC_OR_LOC (व्यंजक, निवेश_location), ret, व्यंजक);
      अगर (code == LSHIFT_व्यंजक
	  && वृक्ष_CODE (orig_op0) != INTEGER_CST
	  && (वृक्ष_CODE (वृक्ष_TYPE (orig_op0)) == INTEGER_TYPE
	      || वृक्ष_CODE (वृक्ष_TYPE (orig_op0)) == BITINT_TYPE)
	  && वृक्ष_CODE (op0) == INTEGER_CST
	  && c_inhibit_evaluation_warnings == 0
	  && !TYPE_OVERFLOW_WRAPS (वृक्ष_TYPE (orig_op0))
	  && वृक्ष_int_cst_sgn (op0) < 0)
	warning_at (loc, OPT_Wshift_negative_मूल्य,
		    "left shift of negative value");
      अगर ((code == LSHIFT_व्यंजक
	   || code == RSHIFT_व्यंजक
	   || code == LROTATE_व्यंजक
	   || code == RROTATE_व्यंजक)
	  && वृक्ष_CODE (orig_op1) != INTEGER_CST
	  && वृक्ष_CODE (op1) == INTEGER_CST
	  && वृक्ष_CODE (वृक्ष_TYPE (orig_op1)) == INTEGER_TYPE
	  && c_inhibit_evaluation_warnings == 0)
	{
	  अगर (वृक्ष_int_cst_sgn (op1) < 0)
	    warning_at (loc, OPT_Wshift_गिनती_negative,
			(code == LSHIFT_व्यंजक
			 ? G_("left shift count is negative")
			 : G_("right shift count is negative")));
	  अन्यथा अगर ((वृक्ष_CODE (वृक्ष_TYPE (orig_op0)) == INTEGER_TYPE
		    || वृक्ष_CODE (वृक्ष_TYPE (orig_op0)) == BITINT_TYPE
		    || वृक्ष_CODE (वृक्ष_TYPE (orig_op0)) == FIXED_POINT_TYPE)
		   && compare_वृक्ष_int (op1,
					TYPE_PRECISION (वृक्ष_TYPE (orig_op0)))
		      >= 0
		   && !warning_suppressed_p (व्यंजक, OPT_Wshift_गिनती_overflow))
	    warning_at (loc, OPT_Wshift_गिनती_overflow,
			(code == LSHIFT_व्यंजक
			 ? G_("left shift count >= width of type")
			 : G_("right shift count >= width of type")));
	  अन्यथा अगर (वृक्ष_CODE (वृक्ष_TYPE (orig_op0)) == VECTOR_TYPE
		   && compare_वृक्ष_int (op1,
					TYPE_PRECISION (वृक्ष_TYPE (वृक्ष_TYPE (orig_op0))))
		      >= 0)
	    warning_at (loc, OPT_Wshift_गिनती_overflow,
			code == LSHIFT_व्यंजक
			? G_("left shift count >= width of vector element")
			: G_("right shift count >= width of vector element"));
	}
      अगर (code == LSHIFT_व्यंजक
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
      अगर ((code == TRUNC_DIV_व्यंजक
	   || code == CEIL_DIV_व्यंजक
	   || code == FLOOR_DIV_व्यंजक
	   || code == EXACT_DIV_व्यंजक
	   || code == TRUNC_MOD_व्यंजक)
	  && वृक्ष_CODE (orig_op1) != INTEGER_CST
	  && वृक्ष_CODE (op1) == INTEGER_CST
	  && (वृक्ष_CODE (वृक्ष_TYPE (orig_op0)) == INTEGER_TYPE
	      || वृक्ष_CODE (वृक्ष_TYPE (orig_op0)) == BITINT_TYPE
	      || वृक्ष_CODE (वृक्ष_TYPE (orig_op0)) == FIXED_POINT_TYPE)
	  && (वृक्ष_CODE (वृक्ष_TYPE (orig_op1)) == INTEGER_TYPE
	      || वृक्ष_CODE (वृक्ष_TYPE (orig_op1)) == BITINT_TYPE))
	warn_for_div_by_zero (loc, op1);
      अगर (code == MEM_REF
	  && ret != व्यंजक
	  && वृक्ष_CODE (ret) == MEM_REF)
	{
	  वृक्ष_READONLY (ret) = वृक्ष_READONLY (व्यंजक);
	  वृक्ष_SIDE_EFFECTS (ret) = वृक्ष_SIDE_EFFECTS (व्यंजक);
	  वृक्ष_THIS_VOLATILE (ret) = वृक्ष_THIS_VOLATILE (व्यंजक);
	}
      जाओ out;

    हाल ADDR_व्यंजक:
      op0_lval = true;
      जाओ unary;
    हाल REALPART_व्यंजक:
    हाल IMAGPART_व्यंजक:
    हाल VIEW_CONVERT_व्यंजक:
      op0_lval = lval;
      /* FALLTHRU */
    हाल INDIRECT_REF:
    हाल FIX_TRUNC_व्यंजक:
    हाल FLOAT_व्यंजक:
    CASE_CONVERT:
    हाल ADDR_SPACE_CONVERT_व्यंजक:
    हाल NON_LVALUE_व्यंजक:
    हाल NEGATE_व्यंजक:
    हाल BIT_NOT_व्यंजक:
    हाल TRUTH_NOT_व्यंजक:
    हाल CONJ_व्यंजक:
    हाल PAREN_व्यंजक:
    unary:
      /* Unary operations.  */
      orig_op0 = op0 = वृक्ष_OPERAND (व्यंजक, 0);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const,
				   op0_lval);
      STRIP_TYPE_NOPS (op0);

      अगर (for_int_const && वृक्ष_CODE (op0) != INTEGER_CST)
	जाओ out;

      /* ??? Cope with user tricks that amount to offsetof.  The middle-end is
	 not prepared to deal with them if they occur in initializers.  */
      अगर (op0 != orig_op0
	  && code == ADDR_व्यंजक
	  && (op1 = get_base_address (op0)) != NULL_वृक्ष
	  && INDIRECT_REF_P (op1)
	  && वृक्ष_CONSTANT (वृक्ष_OPERAND (op1, 0)))
	ret = fold_offsetof (op0, वृक्ष_TYPE (व्यंजक));
      अन्यथा अगर (op0 != orig_op0 || in_init)
	ret = in_init
	  ? fold_build1_initializer_loc (loc, code, वृक्ष_TYPE (व्यंजक), op0)
	  : fold_build1_loc (loc, code, वृक्ष_TYPE (व्यंजक), op0);
      अन्यथा
	ret = fold (व्यंजक);
      अगर (code == INDIRECT_REF
	  && ret != व्यंजक
	  && INDIRECT_REF_P (ret))
	{
	  वृक्ष_READONLY (ret) = वृक्ष_READONLY (व्यंजक);
	  वृक्ष_SIDE_EFFECTS (ret) = वृक्ष_SIDE_EFFECTS (व्यंजक);
	  वृक्ष_THIS_VOLATILE (ret) = वृक्ष_THIS_VOLATILE (व्यंजक);
	}
      चयन (code)
	{
	हाल FIX_TRUNC_व्यंजक:
	हाल FLOAT_व्यंजक:
	CASE_CONVERT:
	  /* Don't warn about explicit conversions.  We will already
	     have warned about suspect implicit conversions.  */
	  अवरोध;

	शेष:
	  अगर (वृक्ष_OVERFLOW_P (ret) && !वृक्ष_OVERFLOW_P (op0))
	    overflow_warning (व्यंजक_LOCATION (व्यंजक), ret, op0);
	  अवरोध;
	}
      जाओ out;

    हाल TRUTH_ANDIF_व्यंजक:
    हाल TRUTH_ORIF_व्यंजक:
      /* Binary operations not necessarily evaluating both
	 arguments.  */
      orig_op0 = op0 = वृक्ष_OPERAND (व्यंजक, 0);
      orig_op1 = op1 = वृक्ष_OPERAND (व्यंजक, 1);
      op0 = c_fully_fold_internal (op0, in_init, &op0_const, &op0_const_self,
				   for_int_const, false);
      STRIP_TYPE_NOPS (op0);

      unused_p = (op0 == (code == TRUTH_ANDIF_व्यंजक
			  ? truthvalue_false_गाँठ
			  : truthvalue_true_गाँठ));
      c_disable_warnings (unused_p);
      op1 = c_fully_fold_internal (op1, in_init, &op1_const, &op1_const_self,
				   for_int_const, false);
      STRIP_TYPE_NOPS (op1);
      c_enable_warnings (unused_p);

      अगर (for_int_const
	  && (वृक्ष_CODE (op0) != INTEGER_CST
	      /* Require OP1 be an INTEGER_CST only if it's evaluated.  */
	      || (!unused_p && वृक्ष_CODE (op1) != INTEGER_CST)))
	जाओ out;

      अगर (op0 != orig_op0 || op1 != orig_op1 || in_init)
	ret = in_init
	  ? fold_build2_initializer_loc (loc, code, वृक्ष_TYPE (व्यंजक), op0, op1)
	  : fold_build2_loc (loc, code, वृक्ष_TYPE (व्यंजक), op0, op1);
      अन्यथा
	ret = fold (व्यंजक);
      *maybe_const_operands &= op0_const;
      *maybe_const_itself &= op0_const_self;
      अगर (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && (code == TRUTH_ANDIF_व्यंजक
		? op0 == truthvalue_false_गाँठ
		: op0 == truthvalue_true_गाँठ)))
	*maybe_const_operands &= op1_const;
      अगर (!(op0_const
	    && op0_const_self
	    && (code == TRUTH_ANDIF_व्यंजक
		? op0 == truthvalue_false_गाँठ
		: op0 == truthvalue_true_गाँठ)))
	*maybe_const_itself &= op1_const_self;
      जाओ out;

    हाल COND_व्यंजक:
      orig_op0 = op0 = वृक्ष_OPERAND (व्यंजक, 0);
      orig_op1 = op1 = वृक्ष_OPERAND (व्यंजक, 1);
      orig_op2 = op2 = वृक्ष_OPERAND (व्यंजक, 2);
      op0 = c_fully_fold_internal (op0, in_init, &op0_const, &op0_const_self,
				   for_int_const, false);

      STRIP_TYPE_NOPS (op0);
      c_disable_warnings (op0 == truthvalue_false_गाँठ);
      op1 = c_fully_fold_internal (op1, in_init, &op1_const, &op1_const_self,
				   for_int_const, false);
      STRIP_TYPE_NOPS (op1);
      c_enable_warnings (op0 == truthvalue_false_गाँठ);

      c_disable_warnings (op0 == truthvalue_true_गाँठ);
      op2 = c_fully_fold_internal (op2, in_init, &op2_const, &op2_const_self,
				   for_int_const, false);
      STRIP_TYPE_NOPS (op2);
      c_enable_warnings (op0 == truthvalue_true_गाँठ);

      अगर (for_int_const
	  && (वृक्ष_CODE (op0) != INTEGER_CST
	      /* Only the evaluated operand must be an INTEGER_CST.  */
	      || (op0 == truthvalue_true_गाँठ
		  ? वृक्ष_CODE (op1) != INTEGER_CST
		  : वृक्ष_CODE (op2) != INTEGER_CST)))
	जाओ out;

      अगर (op0 != orig_op0 || op1 != orig_op1 || op2 != orig_op2)
	ret = fold_build3_loc (loc, code, वृक्ष_TYPE (व्यंजक), op0, op1, op2);
      अन्यथा
	ret = fold (व्यंजक);
      *maybe_const_operands &= op0_const;
      *maybe_const_itself &= op0_const_self;
      अगर (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && op0 == truthvalue_false_गाँठ))
	*maybe_const_operands &= op1_const;
      अगर (!(op0_const
	    && op0_const_self
	    && op0 == truthvalue_false_गाँठ))
	*maybe_const_itself &= op1_const_self;
      अगर (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && op0 == truthvalue_true_गाँठ))
	*maybe_const_operands &= op2_const;
      अगर (!(op0_const
	    && op0_const_self
	    && op0 == truthvalue_true_गाँठ))
	*maybe_const_itself &= op2_const_self;
      जाओ out;

    हाल VEC_COND_व्यंजक:
      orig_op0 = op0 = वृक्ष_OPERAND (व्यंजक, 0);
      orig_op1 = op1 = वृक्ष_OPERAND (व्यंजक, 1);
      orig_op2 = op2 = वृक्ष_OPERAND (व्यंजक, 2);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, false);
      STRIP_TYPE_NOPS (op0);
      op1 = c_fully_fold_internal (op1, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, false);
      STRIP_TYPE_NOPS (op1);
      op2 = c_fully_fold_internal (op2, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, false);
      STRIP_TYPE_NOPS (op2);

      अगर (op0 != orig_op0 || op1 != orig_op1 || op2 != orig_op2)
	ret = fold_build3_loc (loc, code, वृक्ष_TYPE (व्यंजक), op0, op1, op2);
      अन्यथा
	ret = fold (व्यंजक);
      जाओ out;

    हाल EXCESS_PRECISION_व्यंजक:
      /* Each case where an operand with excess precision may be
	 encountered must remove the EXCESS_PRECISION_EXPR around
	 inner operands and possibly put one around the whole
	 expression or possibly convert to the semantic type (which
	 c_fully_fold does); we cannot tell at this stage which is
	 appropriate in any particular case.  */
      gcc_unreachable ();

    हाल SAVE_व्यंजक:
      /* Make sure to fold the contents of a SAVE_EXPR exactly once.  */
      op0 = वृक्ष_OPERAND (व्यंजक, 0);
      अगर (!SAVE_व्यंजक_FOLDED_P (व्यंजक))
	{
	  op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				       maybe_const_itself, for_int_const,
				       false);
	  वृक्ष_OPERAND (व्यंजक, 0) = op0;
	  SAVE_व्यंजक_FOLDED_P (व्यंजक) = true;
	}
      /* Return the SAVE_EXPR operand if it is invariant.  */
      अगर (वृक्ष_invariant_p (op0))
	ret = op0;
      जाओ out;

    शेष:
      /* Various codes may appear through folding built-in functions
	 and their arguments.  */
      जाओ out;
    }

 out:
  /* Some folding may introduce NON_LVALUE_EXPRs; all lvalue checks
     have been done by this point, so remove them again.  */
  nowarning |= warning_suppressed_p (ret, OPT_Woverflow);
  STRIP_TYPE_NOPS (ret);
  अगर (nowarning && !warning_suppressed_p (ret, OPT_Woverflow))
    {
      अगर (!CAN_HAVE_LOCATION_P (ret))
	ret = build1 (NOP_व्यंजक, वृक्ष_TYPE (ret), ret);
      suppress_warning (ret, OPT_Woverflow);
    }
  अगर (ret != व्यंजक)
    {
      protected_set_व्यंजक_location (ret, loc);
      अगर (IS_व्यंजक_CODE_CLASS (kind))
	set_source_range (ret, old_range.m_start, old_range.m_finish);
    }
  वापस ret;
}

/* Fold X for consideration by one of the warning functions when checking
   whether an expression has a constant value.  */

वृक्ष
fold_for_warn (वृक्ष x)
{
  /* The C front-end has already folded X appropriately.  */
  वापस x;
}
