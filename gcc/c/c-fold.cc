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

#અન્તર્ભાવ "config.h"
#અન્તર્ભાવ "system.h"
#અન્તર્ભાવ "coretypes.h"
#અન્તર્ભાવ "target.h"
#અન્તર્ભાવ "function.h"
#અન્તર્ભાવ "bitmap.h"
#અન્તર્ભાવ "c-tree.h"
#અન્તર્ભાવ "intl.h"
#અન્તર્ભાવ "gimplify.h"

સ્થિર વૃક્ષ c_fully_fold_internal (વૃક્ષ પદાવલિ, તાર્કિક, તાર્કિક *, તાર્કિક *, તાર્કિક,
				   તાર્કિક);

/* If DISABLE is true, stop issuing warnings.  This is used when
   parsing code that we know will not be executed.  This function may
   be called multiple times, and works as a stack.  */

સ્થિર શૂન્ય
c_disable_warnings (તાર્કિક disable)
{
  જો (disable)
    {
      ++c_inhibit_evaluation_warnings;
    }
}

/* If ENABLE is true, re-enable issuing warnings.  */

સ્થિર શૂન્ય
c_enable_warnings (તાર્કિક enable)
{
  જો (enable)
    {
      --c_inhibit_evaluation_warnings;
    }
}

/* Try to fold ARRAY_REF ary[index] if possible and not handled by
   normal fold, return NULL_TREE otherwise.  */

સ્થિર વૃક્ષ
c_fold_array_ref (વૃક્ષ type, વૃક્ષ ary, વૃક્ષ index)
{
  જો (વૃક્ષ_CODE (ary) != STRING_CST
      || વૃક્ષ_CODE (index) != INTEGER_CST
      || વૃક્ષ_OVERFLOW (index)
      || વૃક્ષ_CODE (વૃક્ષ_TYPE (ary)) != ARRAY_TYPE
      || !વૃક્ષ_fits_uhwi_p (index))
    પાછા NULL_વૃક્ષ;

  વૃક્ષ elem_type = વૃક્ષ_TYPE (વૃક્ષ_TYPE (ary));
  unsigned elem_nchars = (TYPE_PRECISION (elem_type)
			  / TYPE_PRECISION (char_type_ગાંઠ));
  unsigned len = (unsigned) વૃક્ષ_STRING_LENGTH (ary) / elem_nchars;
  વૃક્ષ nelts_minus_one = array_type_nelts_minus_one (વૃક્ષ_TYPE (ary));
  તાર્કિક dummy1 = સાચું, dummy2 = સાચું;
  nelts_minus_one = c_fully_fold_internal (nelts_minus_one, સાચું, &dummy1,
					   &dummy2, ખોટું, ખોટું);
  unsigned HOST_WIDE_INT i = વૃક્ષ_to_uhwi (index);
  જો (!વૃક્ષ_int_cst_le (index, nelts_minus_one)
      || i >= len
      || i + elem_nchars > len)
    પાછા NULL_વૃક્ષ;

  જો (elem_nchars == 1)
    પાછા build_int_cst (type, વૃક્ષ_STRING_POINTER (ary)[i]);

  અચલ unsigned અક્ષર *ptr
    = ((અચલ unsigned અક્ષર *)વૃક્ષ_STRING_POINTER (ary) + i * elem_nchars);
  પાછા native_interpret_પદાવલિ (type, ptr, elem_nchars);
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

વૃક્ષ
c_fully_fold (વૃક્ષ પદાવલિ, તાર્કિક in_init, તાર્કિક *maybe_const, તાર્કિક lval)
{
  વૃક્ષ ret;
  વૃક્ષ eptype = NULL_વૃક્ષ;
  તાર્કિક dummy = સાચું;
  તાર્કિક maybe_const_itself = સાચું;
  location_t loc = પદાવલિ_LOCATION (પદાવલિ);

  જો (!maybe_const)
    maybe_const = &dummy;
  જો (વૃક્ષ_CODE (પદાવલિ) == EXCESS_PRECISION_પદાવલિ)
    {
      eptype = વૃક્ષ_TYPE (પદાવલિ);
      પદાવલિ = વૃક્ષ_OPERAND (પદાવલિ, 0);
    }
  ret = c_fully_fold_internal (પદાવલિ, in_init, maybe_const,
			       &maybe_const_itself, ખોટું, lval);
  જો (eptype)
    ret = fold_convert_loc (loc, eptype, ret);
  *maybe_const &= maybe_const_itself;
  પાછા ret;
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

સ્થિર વૃક્ષ
c_fully_fold_internal (વૃક્ષ પદાવલિ, તાર્કિક in_init, તાર્કિક *maybe_const_operands,
		       તાર્કિક *maybe_const_itself, તાર્કિક for_int_const, તાર્કિક lval)
{
  વૃક્ષ ret = પદાવલિ;
  ગણના વૃક્ષ_code code = વૃક્ષ_CODE (પદાવલિ);
  ગણના વૃક્ષ_code_class kind = વૃક્ષ_CODE_CLASS (code);
  location_t loc = પદાવલિ_LOCATION (પદાવલિ);
  વૃક્ષ op0, op1, op2, op3;
  વૃક્ષ orig_op0, orig_op1, orig_op2;
  તાર્કિક op0_const = સાચું, op1_const = સાચું, op2_const = સાચું;
  તાર્કિક op0_const_self = સાચું, op1_const_self = સાચું, op2_const_self = સાચું;
  તાર્કિક nowarning = warning_suppressed_p (પદાવલિ, OPT_Woverflow);
  તાર્કિક unused_p;
  તાર્કિક op0_lval = ખોટું;
  source_range old_range;

  /* Constants, declarations, statements, errors, and anything else not
     counted as an expression cannot usefully be folded further at this
     point.  */
  જો (!IS_પદાવલિ_CODE_CLASS (kind) || kind == tcc_statement)
    {
      /* Except for variables which we can optimize to its initializer.  */
      જો (VAR_P (પદાવલિ) && !lval && (optimize || in_init))
	{
	  જો (in_init)
	    ret = decl_constant_કિંમત_1 (પદાવલિ, સાચું);
	  નહીંતર
	    {
	      ret = decl_constant_કિંમત (પદાવલિ);
	      જો (ret != પદાવલિ
		  && (TYPE_MODE (વૃક્ષ_TYPE (ret)) == BLKmode
		      || વૃક્ષ_CODE (વૃક્ષ_TYPE (ret)) == ARRAY_TYPE))
		પાછા પદાવલિ;
	    }
	  /* Avoid unwanted tree sharing between the initializer and current
	     function's body where the tree can be modified e.g. by the
	     gimplifier.  */
	  જો (ret != પદાવલિ && વૃક્ષ_STATIC (પદાવલિ))
	    ret = unshare_પદાવલિ (ret);
	  પાછા ret;
	}
      પાછા પદાવલિ;
    }

  જો (IS_પદાવલિ_CODE_CLASS (kind))
    old_range = પદાવલિ_LOCATION_RANGE (પદાવલિ);

  /* Operands of variable-length expressions (function calls) have
     already been folded, as have __builtin_* function calls, and such
     expressions cannot occur in constant expressions.  */
  જો (kind == tcc_vl_exp)
    {
      *maybe_const_operands = ખોટું;
      ret = fold (પદાવલિ);
      જાઓ out;
    }

  જો (code == C_MAYBE_CONST_પદાવલિ)
    {
      વૃક્ષ pre = C_MAYBE_CONST_પદાવલિ_PRE (પદાવલિ);
      વૃક્ષ inner = C_MAYBE_CONST_પદાવલિ_પદાવલિ (પદાવલિ);
      જો (C_MAYBE_CONST_પદાવલિ_NON_CONST (પદાવલિ))
	*maybe_const_operands = ખોટું;
      જો (C_MAYBE_CONST_પદાવલિ_INT_OPERANDS (પદાવલિ))
	{
	  *maybe_const_itself = ખોટું;
	  inner = c_fully_fold_internal (inner, in_init, maybe_const_operands,
					 maybe_const_itself, સાચું, lval);
	}
      જો (pre && !in_init)
	ret = build2 (COMPOUND_પદાવલિ, વૃક્ષ_TYPE (પદાવલિ), pre, inner);
      નહીંતર
	ret = inner;
      જાઓ out;
    }

  /* Assignment, increment, decrement, function call and comma
     operators, and statement expressions, cannot occur in constant
     expressions if evaluated / outside of sizeof.  (Function calls
     were handled above, though VA_ARG_EXPR is treated like a function
     call here, and statement expressions are handled through
     C_MAYBE_CONST_EXPR to avoid folding inside them.)  */
  પસંદગી (code)
    {
    સ્થિતિ MODIFY_પદાવલિ:
    સ્થિતિ PREDECREMENT_પદાવલિ:
    સ્થિતિ PREINCREMENT_પદાવલિ:
    સ્થિતિ POSTDECREMENT_પદાવલિ:
    સ્થિતિ POSTINCREMENT_પદાવલિ:
    સ્થિતિ COMPOUND_પદાવલિ:
      *maybe_const_operands = ખોટું;
      તોડો;

    સ્થિતિ VA_ARG_પદાવલિ:
    સ્થિતિ TARGET_પદાવલિ:
    સ્થિતિ BIND_પદાવલિ:
    સ્થિતિ OBJ_TYPE_REF:
      *maybe_const_operands = ખોટું;
      ret = fold (પદાવલિ);
      જાઓ out;

    મૂળભૂત:
      તોડો;
    }

  /* Fold individual tree codes as appropriate.  */
  પસંદગી (code)
    {
    સ્થિતિ COMPOUND_LITERAL_પદાવલિ:
      /* Any non-constancy will have been marked in a containing
	 C_MAYBE_CONST_EXPR; there is no more folding to do here.  */
      જાઓ out;

    સ્થિતિ COMPONENT_REF:
      orig_op0 = op0 = વૃક્ષ_OPERAND (પદાવલિ, 0);
      op1 = વૃક્ષ_OPERAND (પદાવલિ, 1);
      op2 = વૃક્ષ_OPERAND (પદાવલિ, 2);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, lval);
      STRIP_TYPE_NOPS (op0);
      જો (op0 != orig_op0)
	ret = build3 (COMPONENT_REF, વૃક્ષ_TYPE (પદાવલિ), op0, op1, op2);
      જો (ret != પદાવલિ)
	{
	  વૃક્ષ_READONLY (ret) = વૃક્ષ_READONLY (પદાવલિ);
	  વૃક્ષ_THIS_VOLATILE (ret) = વૃક્ષ_THIS_VOLATILE (પદાવલિ);
	}
      જો (!lval)
	ret = fold (ret);
      જાઓ out;

    સ્થિતિ ARRAY_REF:
      orig_op0 = op0 = વૃક્ષ_OPERAND (પદાવલિ, 0);
      orig_op1 = op1 = વૃક્ષ_OPERAND (પદાવલિ, 1);
      op2 = વૃક્ષ_OPERAND (પદાવલિ, 2);
      op3 = વૃક્ષ_OPERAND (પદાવલિ, 3);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, lval);
      STRIP_TYPE_NOPS (op0);
      op1 = c_fully_fold_internal (op1, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, ખોટું);
      STRIP_TYPE_NOPS (op1);
      /* Fold "foo"[2] in initializers.  */
      જો (!lval && in_init)
	{
	  ret = c_fold_array_ref (વૃક્ષ_TYPE (પદાવલિ), op0, op1);
	  જો (ret)
	    જાઓ out;
	  ret = પદાવલિ;
	}
      જો (op0 != orig_op0 || op1 != orig_op1)
	ret = build4 (ARRAY_REF, વૃક્ષ_TYPE (પદાવલિ), op0, op1, op2, op3);
      જો (ret != પદાવલિ)
	{
	  વૃક્ષ_READONLY (ret) = વૃક્ષ_READONLY (પદાવલિ);
	  વૃક્ષ_SIDE_EFFECTS (ret) = વૃક્ષ_SIDE_EFFECTS (પદાવલિ);
	  વૃક્ષ_THIS_VOLATILE (ret) = વૃક્ષ_THIS_VOLATILE (પદાવલિ);
	}
      જો (!lval)
	ret = fold (ret);
      જાઓ out;

    સ્થિતિ MODIFY_પદાવલિ:
    સ્થિતિ PREDECREMENT_પદાવલિ:
    સ્થિતિ PREINCREMENT_પદાવલિ:
    સ્થિતિ POSTDECREMENT_પદાવલિ:
    સ્થિતિ POSTINCREMENT_પદાવલિ:
      op0_lval = સાચું;
      /* FALLTHRU */
    સ્થિતિ COMPOUND_પદાવલિ:
    સ્થિતિ PLUS_પદાવલિ:
    સ્થિતિ MINUS_પદાવલિ:
    સ્થિતિ MULT_પદાવલિ:
    સ્થિતિ POINTER_PLUS_પદાવલિ:
    સ્થિતિ POINTER_DIFF_પદાવલિ:
    સ્થિતિ TRUNC_DIV_પદાવલિ:
    સ્થિતિ CEIL_DIV_પદાવલિ:
    સ્થિતિ FLOOR_DIV_પદાવલિ:
    સ્થિતિ TRUNC_MOD_પદાવલિ:
    સ્થિતિ RDIV_પદાવલિ:
    સ્થિતિ EXACT_DIV_પદાવલિ:
    સ્થિતિ LSHIFT_પદાવલિ:
    સ્થિતિ RSHIFT_પદાવલિ:
    સ્થિતિ LROTATE_પદાવલિ:
    સ્થિતિ RROTATE_પદાવલિ:
    સ્થિતિ BIT_IOR_પદાવલિ:
    સ્થિતિ BIT_XOR_પદાવલિ:
    સ્થિતિ BIT_AND_પદાવલિ:
    સ્થિતિ LT_પદાવલિ:
    સ્થિતિ LE_પદાવલિ:
    સ્થિતિ GT_પદાવલિ:
    સ્થિતિ GE_પદાવલિ:
    સ્થિતિ EQ_પદાવલિ:
    સ્થિતિ NE_પદાવલિ:
    સ્થિતિ COMPLEX_પદાવલિ:
    સ્થિતિ TRUTH_AND_પદાવલિ:
    સ્થિતિ TRUTH_OR_પદાવલિ:
    સ્થિતિ TRUTH_XOR_પદાવલિ:
    સ્થિતિ UNORDERED_પદાવલિ:
    સ્થિતિ ORDERED_પદાવલિ:
    સ્થિતિ UNLT_પદાવલિ:
    સ્થિતિ UNLE_પદાવલિ:
    સ્થિતિ UNGT_પદાવલિ:
    સ્થિતિ UNGE_પદાવલિ:
    સ્થિતિ UNEQ_પદાવલિ:
    સ્થિતિ MEM_REF:
      /* Binary operations evaluating both arguments (increment and
	 decrement are binary internally in GCC).  */
      orig_op0 = op0 = વૃક્ષ_OPERAND (પદાવલિ, 0);
      orig_op1 = op1 = વૃક્ષ_OPERAND (પદાવલિ, 1);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const,
				   op0_lval);
      STRIP_TYPE_NOPS (op0);
      /* The RHS of a MODIFY_EXPR was fully folded when building that
	 expression for the sake of conversion warnings.  */
      જો (code != MODIFY_પદાવલિ)
	op1 = c_fully_fold_internal (op1, in_init, maybe_const_operands,
				     maybe_const_itself, for_int_const, ખોટું);
      STRIP_TYPE_NOPS (op1);

      જો (for_int_const && (વૃક્ષ_CODE (op0) != INTEGER_CST
			    || વૃક્ષ_CODE (op1) != INTEGER_CST))
	જાઓ out;

      જો (વૃક્ષ_CODE_CLASS (code) == tcc_comparison
	  && વૃક્ષ_CODE (વૃક્ષ_TYPE (op0)) == NULLPTR_TYPE
	  && વૃક્ષ_CODE (વૃક્ષ_TYPE (op1)) == NULLPTR_TYPE)
	{
	  પસંદગી (code)
	    {
	    સ્થિતિ EQ_પદાવલિ:
	      ret = constant_boolean_ગાંઠ (સાચું, વૃક્ષ_TYPE (પદાવલિ));
	      તોડો;
	    સ્થિતિ NE_પદાવલિ:
	      ret = constant_boolean_ગાંઠ (ખોટું, વૃક્ષ_TYPE (પદાવલિ));
	      તોડો;
	    મૂળભૂત:
	      gcc_unreachable ();
	    }
	  ret = omit_two_operands_loc (loc, વૃક્ષ_TYPE (પદાવલિ), ret,
				       op0, op1);
	}
      નહીંતર જો (op0 != orig_op0 || op1 != orig_op1 || in_init)
	ret = in_init
	  ? fold_build2_initializer_loc (loc, code, વૃક્ષ_TYPE (પદાવલિ), op0, op1)
	  : fold_build2_loc (loc, code, વૃક્ષ_TYPE (પદાવલિ), op0, op1);
      નહીંતર
	ret = fold (પદાવલિ);
      જો (વૃક્ષ_OVERFLOW_P (ret)
	  && !વૃક્ષ_OVERFLOW_P (op0)
	  && !(દ્વિઅંકી_CLASS_P (op0) && વૃક્ષ_OVERFLOW_P (વૃક્ષ_OPERAND (op0, 1)))
	  && !વૃક્ષ_OVERFLOW_P (op1))
	overflow_warning (પદાવલિ_LOC_OR_LOC (પદાવલિ, આગત_location), ret, પદાવલિ);
      જો (code == LSHIFT_પદાવલિ
	  && વૃક્ષ_CODE (orig_op0) != INTEGER_CST
	  && (વૃક્ષ_CODE (વૃક્ષ_TYPE (orig_op0)) == INTEGER_TYPE
	      || વૃક્ષ_CODE (વૃક્ષ_TYPE (orig_op0)) == BITINT_TYPE)
	  && વૃક્ષ_CODE (op0) == INTEGER_CST
	  && c_inhibit_evaluation_warnings == 0
	  && !TYPE_OVERFLOW_WRAPS (વૃક્ષ_TYPE (orig_op0))
	  && વૃક્ષ_int_cst_sgn (op0) < 0)
	warning_at (loc, OPT_Wshift_negative_કિંમત,
		    "left shift of negative value");
      જો ((code == LSHIFT_પદાવલિ
	   || code == RSHIFT_પદાવલિ
	   || code == LROTATE_પદાવલિ
	   || code == RROTATE_પદાવલિ)
	  && વૃક્ષ_CODE (orig_op1) != INTEGER_CST
	  && વૃક્ષ_CODE (op1) == INTEGER_CST
	  && વૃક્ષ_CODE (વૃક્ષ_TYPE (orig_op1)) == INTEGER_TYPE
	  && c_inhibit_evaluation_warnings == 0)
	{
	  જો (વૃક્ષ_int_cst_sgn (op1) < 0)
	    warning_at (loc, OPT_Wshift_ગણતરી_negative,
			(code == LSHIFT_પદાવલિ
			 ? G_("left shift count is negative")
			 : G_("right shift count is negative")));
	  નહીંતર જો ((વૃક્ષ_CODE (વૃક્ષ_TYPE (orig_op0)) == INTEGER_TYPE
		    || વૃક્ષ_CODE (વૃક્ષ_TYPE (orig_op0)) == BITINT_TYPE
		    || વૃક્ષ_CODE (વૃક્ષ_TYPE (orig_op0)) == FIXED_POINT_TYPE)
		   && compare_વૃક્ષ_int (op1,
					TYPE_PRECISION (વૃક્ષ_TYPE (orig_op0)))
		      >= 0
		   && !warning_suppressed_p (પદાવલિ, OPT_Wshift_ગણતરી_overflow))
	    warning_at (loc, OPT_Wshift_ગણતરી_overflow,
			(code == LSHIFT_પદાવલિ
			 ? G_("left shift count >= width of type")
			 : G_("right shift count >= width of type")));
	  નહીંતર જો (વૃક્ષ_CODE (વૃક્ષ_TYPE (orig_op0)) == VECTOR_TYPE
		   && compare_વૃક્ષ_int (op1,
					TYPE_PRECISION (વૃક્ષ_TYPE (વૃક્ષ_TYPE (orig_op0))))
		      >= 0)
	    warning_at (loc, OPT_Wshift_ગણતરી_overflow,
			code == LSHIFT_પદાવલિ
			? G_("left shift count >= width of vector element")
			: G_("right shift count >= width of vector element"));
	}
      જો (code == LSHIFT_પદાવલિ
	  /* If either OP0 has been folded to INTEGER_CST...  */
	  && ((વૃક્ષ_CODE (orig_op0) != INTEGER_CST
	       && (વૃક્ષ_CODE (વૃક્ષ_TYPE (orig_op0)) == INTEGER_TYPE
		   || વૃક્ષ_CODE (વૃક્ષ_TYPE (orig_op0)) == BITINT_TYPE)
	       && વૃક્ષ_CODE (op0) == INTEGER_CST)
	      /* ...or if OP1 has been folded to INTEGER_CST...  */
	      || (વૃક્ષ_CODE (orig_op1) != INTEGER_CST
		  && (વૃક્ષ_CODE (વૃક્ષ_TYPE (orig_op1)) == INTEGER_TYPE
		      || વૃક્ષ_CODE (વૃક્ષ_TYPE (orig_op1)) == BITINT_TYPE)
		  && વૃક્ષ_CODE (op1) == INTEGER_CST))
	  && c_inhibit_evaluation_warnings == 0)
	/* ...then maybe we can detect an overflow.  */
	maybe_warn_shift_overflow (loc, op0, op1);
      જો ((code == TRUNC_DIV_પદાવલિ
	   || code == CEIL_DIV_પદાવલિ
	   || code == FLOOR_DIV_પદાવલિ
	   || code == EXACT_DIV_પદાવલિ
	   || code == TRUNC_MOD_પદાવલિ)
	  && વૃક્ષ_CODE (orig_op1) != INTEGER_CST
	  && વૃક્ષ_CODE (op1) == INTEGER_CST
	  && (વૃક્ષ_CODE (વૃક્ષ_TYPE (orig_op0)) == INTEGER_TYPE
	      || વૃક્ષ_CODE (વૃક્ષ_TYPE (orig_op0)) == BITINT_TYPE
	      || વૃક્ષ_CODE (વૃક્ષ_TYPE (orig_op0)) == FIXED_POINT_TYPE)
	  && (વૃક્ષ_CODE (વૃક્ષ_TYPE (orig_op1)) == INTEGER_TYPE
	      || વૃક્ષ_CODE (વૃક્ષ_TYPE (orig_op1)) == BITINT_TYPE))
	warn_for_div_by_zero (loc, op1);
      જો (code == MEM_REF
	  && ret != પદાવલિ
	  && વૃક્ષ_CODE (ret) == MEM_REF)
	{
	  વૃક્ષ_READONLY (ret) = વૃક્ષ_READONLY (પદાવલિ);
	  વૃક્ષ_SIDE_EFFECTS (ret) = વૃક્ષ_SIDE_EFFECTS (પદાવલિ);
	  વૃક્ષ_THIS_VOLATILE (ret) = વૃક્ષ_THIS_VOLATILE (પદાવલિ);
	}
      જાઓ out;

    સ્થિતિ ADDR_પદાવલિ:
      op0_lval = સાચું;
      જાઓ unary;
    સ્થિતિ REALPART_પદાવલિ:
    સ્થિતિ IMAGPART_પદાવલિ:
    સ્થિતિ VIEW_CONVERT_પદાવલિ:
      op0_lval = lval;
      /* FALLTHRU */
    સ્થિતિ INDIRECT_REF:
    સ્થિતિ FIX_TRUNC_પદાવલિ:
    સ્થિતિ FLOAT_પદાવલિ:
    CASE_CONVERT:
    સ્થિતિ ADDR_SPACE_CONVERT_પદાવલિ:
    સ્થિતિ NON_LVALUE_પદાવલિ:
    સ્થિતિ NEGATE_પદાવલિ:
    સ્થિતિ BIT_NOT_પદાવલિ:
    સ્થિતિ TRUTH_NOT_પદાવલિ:
    સ્થિતિ CONJ_પદાવલિ:
    સ્થિતિ PAREN_પદાવલિ:
    unary:
      /* Unary operations.  */
      orig_op0 = op0 = વૃક્ષ_OPERAND (પદાવલિ, 0);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const,
				   op0_lval);
      STRIP_TYPE_NOPS (op0);

      જો (for_int_const && વૃક્ષ_CODE (op0) != INTEGER_CST)
	જાઓ out;

      /* ??? Cope with user tricks that amount to offsetof.  The middle-end is
	 not prepared to deal with them if they occur in initializers.  */
      જો (op0 != orig_op0
	  && code == ADDR_પદાવલિ
	  && (op1 = get_base_address (op0)) != NULL_વૃક્ષ
	  && INDIRECT_REF_P (op1)
	  && વૃક્ષ_CONSTANT (વૃક્ષ_OPERAND (op1, 0)))
	ret = fold_offsetof (op0, વૃક્ષ_TYPE (પદાવલિ));
      નહીંતર જો (op0 != orig_op0 || in_init)
	ret = in_init
	  ? fold_build1_initializer_loc (loc, code, વૃક્ષ_TYPE (પદાવલિ), op0)
	  : fold_build1_loc (loc, code, વૃક્ષ_TYPE (પદાવલિ), op0);
      નહીંતર
	ret = fold (પદાવલિ);
      જો (code == INDIRECT_REF
	  && ret != પદાવલિ
	  && INDIRECT_REF_P (ret))
	{
	  વૃક્ષ_READONLY (ret) = વૃક્ષ_READONLY (પદાવલિ);
	  વૃક્ષ_SIDE_EFFECTS (ret) = વૃક્ષ_SIDE_EFFECTS (પદાવલિ);
	  વૃક્ષ_THIS_VOLATILE (ret) = વૃક્ષ_THIS_VOLATILE (પદાવલિ);
	}
      પસંદગી (code)
	{
	સ્થિતિ FIX_TRUNC_પદાવલિ:
	સ્થિતિ FLOAT_પદાવલિ:
	CASE_CONVERT:
	  /* Don't warn about explicit conversions.  We will already
	     have warned about suspect implicit conversions.  */
	  તોડો;

	મૂળભૂત:
	  જો (વૃક્ષ_OVERFLOW_P (ret) && !વૃક્ષ_OVERFLOW_P (op0))
	    overflow_warning (પદાવલિ_LOCATION (પદાવલિ), ret, op0);
	  તોડો;
	}
      જાઓ out;

    સ્થિતિ TRUTH_ANDIF_પદાવલિ:
    સ્થિતિ TRUTH_ORIF_પદાવલિ:
      /* Binary operations not necessarily evaluating both
	 arguments.  */
      orig_op0 = op0 = વૃક્ષ_OPERAND (પદાવલિ, 0);
      orig_op1 = op1 = વૃક્ષ_OPERAND (પદાવલિ, 1);
      op0 = c_fully_fold_internal (op0, in_init, &op0_const, &op0_const_self,
				   for_int_const, ખોટું);
      STRIP_TYPE_NOPS (op0);

      unused_p = (op0 == (code == TRUTH_ANDIF_પદાવલિ
			  ? truthvalue_false_ગાંઠ
			  : truthvalue_true_ગાંઠ));
      c_disable_warnings (unused_p);
      op1 = c_fully_fold_internal (op1, in_init, &op1_const, &op1_const_self,
				   for_int_const, ખોટું);
      STRIP_TYPE_NOPS (op1);
      c_enable_warnings (unused_p);

      જો (for_int_const
	  && (વૃક્ષ_CODE (op0) != INTEGER_CST
	      /* Require OP1 be an INTEGER_CST only if it's evaluated.  */
	      || (!unused_p && વૃક્ષ_CODE (op1) != INTEGER_CST)))
	જાઓ out;

      જો (op0 != orig_op0 || op1 != orig_op1 || in_init)
	ret = in_init
	  ? fold_build2_initializer_loc (loc, code, વૃક્ષ_TYPE (પદાવલિ), op0, op1)
	  : fold_build2_loc (loc, code, વૃક્ષ_TYPE (પદાવલિ), op0, op1);
      નહીંતર
	ret = fold (પદાવલિ);
      *maybe_const_operands &= op0_const;
      *maybe_const_itself &= op0_const_self;
      જો (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && (code == TRUTH_ANDIF_પદાવલિ
		? op0 == truthvalue_false_ગાંઠ
		: op0 == truthvalue_true_ગાંઠ)))
	*maybe_const_operands &= op1_const;
      જો (!(op0_const
	    && op0_const_self
	    && (code == TRUTH_ANDIF_પદાવલિ
		? op0 == truthvalue_false_ગાંઠ
		: op0 == truthvalue_true_ગાંઠ)))
	*maybe_const_itself &= op1_const_self;
      જાઓ out;

    સ્થિતિ COND_પદાવલિ:
      orig_op0 = op0 = વૃક્ષ_OPERAND (પદાવલિ, 0);
      orig_op1 = op1 = વૃક્ષ_OPERAND (પદાવલિ, 1);
      orig_op2 = op2 = વૃક્ષ_OPERAND (પદાવલિ, 2);
      op0 = c_fully_fold_internal (op0, in_init, &op0_const, &op0_const_self,
				   for_int_const, ખોટું);

      STRIP_TYPE_NOPS (op0);
      c_disable_warnings (op0 == truthvalue_false_ગાંઠ);
      op1 = c_fully_fold_internal (op1, in_init, &op1_const, &op1_const_self,
				   for_int_const, ખોટું);
      STRIP_TYPE_NOPS (op1);
      c_enable_warnings (op0 == truthvalue_false_ગાંઠ);

      c_disable_warnings (op0 == truthvalue_true_ગાંઠ);
      op2 = c_fully_fold_internal (op2, in_init, &op2_const, &op2_const_self,
				   for_int_const, ખોટું);
      STRIP_TYPE_NOPS (op2);
      c_enable_warnings (op0 == truthvalue_true_ગાંઠ);

      જો (for_int_const
	  && (વૃક્ષ_CODE (op0) != INTEGER_CST
	      /* Only the evaluated operand must be an INTEGER_CST.  */
	      || (op0 == truthvalue_true_ગાંઠ
		  ? વૃક્ષ_CODE (op1) != INTEGER_CST
		  : વૃક્ષ_CODE (op2) != INTEGER_CST)))
	જાઓ out;

      જો (op0 != orig_op0 || op1 != orig_op1 || op2 != orig_op2)
	ret = fold_build3_loc (loc, code, વૃક્ષ_TYPE (પદાવલિ), op0, op1, op2);
      નહીંતર
	ret = fold (પદાવલિ);
      *maybe_const_operands &= op0_const;
      *maybe_const_itself &= op0_const_self;
      જો (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && op0 == truthvalue_false_ગાંઠ))
	*maybe_const_operands &= op1_const;
      જો (!(op0_const
	    && op0_const_self
	    && op0 == truthvalue_false_ગાંઠ))
	*maybe_const_itself &= op1_const_self;
      જો (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && op0 == truthvalue_true_ગાંઠ))
	*maybe_const_operands &= op2_const;
      જો (!(op0_const
	    && op0_const_self
	    && op0 == truthvalue_true_ગાંઠ))
	*maybe_const_itself &= op2_const_self;
      જાઓ out;

    સ્થિતિ VEC_COND_પદાવલિ:
      orig_op0 = op0 = વૃક્ષ_OPERAND (પદાવલિ, 0);
      orig_op1 = op1 = વૃક્ષ_OPERAND (પદાવલિ, 1);
      orig_op2 = op2 = વૃક્ષ_OPERAND (પદાવલિ, 2);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, ખોટું);
      STRIP_TYPE_NOPS (op0);
      op1 = c_fully_fold_internal (op1, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, ખોટું);
      STRIP_TYPE_NOPS (op1);
      op2 = c_fully_fold_internal (op2, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, ખોટું);
      STRIP_TYPE_NOPS (op2);

      જો (op0 != orig_op0 || op1 != orig_op1 || op2 != orig_op2)
	ret = fold_build3_loc (loc, code, વૃક્ષ_TYPE (પદાવલિ), op0, op1, op2);
      નહીંતર
	ret = fold (પદાવલિ);
      જાઓ out;

    સ્થિતિ EXCESS_PRECISION_પદાવલિ:
      /* Each case where an operand with excess precision may be
	 encountered must remove the EXCESS_PRECISION_EXPR around
	 inner operands and possibly put one around the whole
	 expression or possibly convert to the semantic type (which
	 c_fully_fold does); we cannot tell at this stage which is
	 appropriate in any particular case.  */
      gcc_unreachable ();

    સ્થિતિ SAVE_પદાવલિ:
      /* Make sure to fold the contents of a SAVE_EXPR exactly once.  */
      op0 = વૃક્ષ_OPERAND (પદાવલિ, 0);
      જો (!SAVE_પદાવલિ_FOLDED_P (પદાવલિ))
	{
	  op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				       maybe_const_itself, for_int_const,
				       ખોટું);
	  વૃક્ષ_OPERAND (પદાવલિ, 0) = op0;
	  SAVE_પદાવલિ_FOLDED_P (પદાવલિ) = સાચું;
	}
      /* Return the SAVE_EXPR operand if it is invariant.  */
      જો (વૃક્ષ_invariant_p (op0))
	ret = op0;
      જાઓ out;

    મૂળભૂત:
      /* Various codes may appear through folding built-in functions
	 and their arguments.  */
      જાઓ out;
    }

 out:
  /* Some folding may introduce NON_LVALUE_EXPRs; all lvalue checks
     have been done by this point, so remove them again.  */
  nowarning |= warning_suppressed_p (ret, OPT_Woverflow);
  STRIP_TYPE_NOPS (ret);
  જો (nowarning && !warning_suppressed_p (ret, OPT_Woverflow))
    {
      જો (!CAN_HAVE_LOCATION_P (ret))
	ret = build1 (NOP_પદાવલિ, વૃક્ષ_TYPE (ret), ret);
      suppress_warning (ret, OPT_Woverflow);
    }
  જો (ret != પદાવલિ)
    {
      protected_set_પદાવલિ_location (ret, loc);
      જો (IS_પદાવલિ_CODE_CLASS (kind))
	set_source_range (ret, old_range.m_start, old_range.m_finish);
    }
  પાછા ret;
}

/* Fold X for consideration by one of the warning functions when checking
   whether an expression has a constant value.  */

વૃક્ષ
fold_for_warn (વૃક્ષ x)
{
  /* The C front-end has already folded X appropriately.  */
  પાછા x;
}
