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

#ಅನ್ತರ್ಭಾವ "config.h"
#ಅನ್ತರ್ಭಾವ "system.h"
#ಅನ್ತರ್ಭಾವ "coretypes.h"
#ಅನ್ತರ್ಭಾವ "target.h"
#ಅನ್ತರ್ಭಾವ "function.h"
#ಅನ್ತರ್ಭಾವ "bitmap.h"
#ಅನ್ತರ್ಭಾವ "c-tree.h"
#ಅನ್ತರ್ಭಾವ "intl.h"
#ಅನ್ತರ್ಭಾವ "gimplify.h"

ಸ್ಥಿರ ವೃಕ್ಷ c_fully_fold_internal (ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ, ತಾರ್ಕಿಕ, ತಾರ್ಕಿಕ *, ತಾರ್ಕಿಕ *, ತಾರ್ಕಿಕ,
				   ತಾರ್ಕಿಕ);

/* If DISABLE is true, stop issuing warnings.  This is used when
   parsing code that we know will not be executed.  This function may
   be called multiple times, and works as a stack.  */

ಸ್ಥಿರ ಶೂನ್ಯ
c_disable_warnings (ತಾರ್ಕಿಕ disable)
{
  ಯದಿ (disable)
    {
      ++c_inhibit_evaluation_warnings;
    }
}

/* If ENABLE is true, re-enable issuing warnings.  */

ಸ್ಥಿರ ಶೂನ್ಯ
c_enable_warnings (ತಾರ್ಕಿಕ enable)
{
  ಯದಿ (enable)
    {
      --c_inhibit_evaluation_warnings;
    }
}

/* Try to fold ARRAY_REF ary[index] if possible and not handled by
   normal fold, return NULL_TREE otherwise.  */

ಸ್ಥಿರ ವೃಕ್ಷ
c_fold_array_ref (ವೃಕ್ಷ type, ವೃಕ್ಷ ary, ವೃಕ್ಷ index)
{
  ಯದಿ (ವೃಕ್ಷ_CODE (ary) != STRING_CST
      || ವೃಕ್ಷ_CODE (index) != INTEGER_CST
      || ವೃಕ್ಷ_OVERFLOW (index)
      || ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (ary)) != ARRAY_TYPE
      || !ವೃಕ್ಷ_fits_uhwi_p (index))
    ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;

  ವೃಕ್ಷ elem_type = ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (ary));
  unsigned elem_nchars = (TYPE_PRECISION (elem_type)
			  / TYPE_PRECISION (char_type_ಗಂಟು));
  unsigned len = (unsigned) ವೃಕ್ಷ_STRING_LENGTH (ary) / elem_nchars;
  ವೃಕ್ಷ nelts_minus_one = array_type_nelts_minus_one (ವೃಕ್ಷ_TYPE (ary));
  ತಾರ್ಕಿಕ dummy1 = ಸತ್ಯ, dummy2 = ಸತ್ಯ;
  nelts_minus_one = c_fully_fold_internal (nelts_minus_one, ಸತ್ಯ, &dummy1,
					   &dummy2, ಅಸತ್ಯ, ಅಸತ್ಯ);
  unsigned HOST_WIDE_INT i = ವೃಕ್ಷ_to_uhwi (index);
  ಯದಿ (!ವೃಕ್ಷ_int_cst_le (index, nelts_minus_one)
      || i >= len
      || i + elem_nchars > len)
    ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;

  ಯದಿ (elem_nchars == 1)
    ಪ್ರತ್ಯಾಗಮ build_int_cst (type, ವೃಕ್ಷ_STRING_POINTER (ary)[i]);

  ಧ್ರುವ unsigned ವರ್ಣ *ptr
    = ((ಧ್ರುವ unsigned ವರ್ಣ *)ವೃಕ್ಷ_STRING_POINTER (ary) + i * elem_nchars);
  ಪ್ರತ್ಯಾಗಮ native_interpret_ಅಭಿವ್ಯಕ್ತಿ (type, ptr, elem_nchars);
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

ವೃಕ್ಷ
c_fully_fold (ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ, ತಾರ್ಕಿಕ in_init, ತಾರ್ಕಿಕ *maybe_const, ತಾರ್ಕಿಕ lval)
{
  ವೃಕ್ಷ ret;
  ವೃಕ್ಷ eptype = NULL_ವೃಕ್ಷ;
  ತಾರ್ಕಿಕ dummy = ಸತ್ಯ;
  ತಾರ್ಕಿಕ maybe_const_itself = ಸತ್ಯ;
  location_t loc = ಅಭಿವ್ಯಕ್ತಿ_LOCATION (ಅಭಿವ್ಯಕ್ತಿ);

  ಯದಿ (!maybe_const)
    maybe_const = &dummy;
  ಯದಿ (ವೃಕ್ಷ_CODE (ಅಭಿವ್ಯಕ್ತಿ) == EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ)
    {
      eptype = ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ);
      ಅಭಿವ್ಯಕ್ತಿ = ವೃಕ್ಷ_OPERAND (ಅಭಿವ್ಯಕ್ತಿ, 0);
    }
  ret = c_fully_fold_internal (ಅಭಿವ್ಯಕ್ತಿ, in_init, maybe_const,
			       &maybe_const_itself, ಅಸತ್ಯ, lval);
  ಯದಿ (eptype)
    ret = fold_convert_loc (loc, eptype, ret);
  *maybe_const &= maybe_const_itself;
  ಪ್ರತ್ಯಾಗಮ ret;
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

ಸ್ಥಿರ ವೃಕ್ಷ
c_fully_fold_internal (ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ, ತಾರ್ಕಿಕ in_init, ತಾರ್ಕಿಕ *maybe_const_operands,
		       ತಾರ್ಕಿಕ *maybe_const_itself, ತಾರ್ಕಿಕ for_int_const, ತಾರ್ಕಿಕ lval)
{
  ವೃಕ್ಷ ret = ಅಭಿವ್ಯಕ್ತಿ;
  ಗಣನಾ ವೃಕ್ಷ_code code = ವೃಕ್ಷ_CODE (ಅಭಿವ್ಯಕ್ತಿ);
  ಗಣನಾ ವೃಕ್ಷ_code_class kind = ವೃಕ್ಷ_CODE_CLASS (code);
  location_t loc = ಅಭಿವ್ಯಕ್ತಿ_LOCATION (ಅಭಿವ್ಯಕ್ತಿ);
  ವೃಕ್ಷ op0, op1, op2, op3;
  ವೃಕ್ಷ orig_op0, orig_op1, orig_op2;
  ತಾರ್ಕಿಕ op0_const = ಸತ್ಯ, op1_const = ಸತ್ಯ, op2_const = ಸತ್ಯ;
  ತಾರ್ಕಿಕ op0_const_self = ಸತ್ಯ, op1_const_self = ಸತ್ಯ, op2_const_self = ಸತ್ಯ;
  ತಾರ್ಕಿಕ nowarning = warning_suppressed_p (ಅಭಿವ್ಯಕ್ತಿ, OPT_Woverflow);
  ತಾರ್ಕಿಕ unused_p;
  ತಾರ್ಕಿಕ op0_lval = ಅಸತ್ಯ;
  source_range old_range;

  /* Constants, declarations, statements, errors, and anything else not
     counted as an expression cannot usefully be folded further at this
     point.  */
  ಯದಿ (!IS_ಅಭಿವ್ಯಕ್ತಿ_CODE_CLASS (kind) || kind == tcc_statement)
    {
      /* Except for variables which we can optimize to its initializer.  */
      ಯದಿ (VAR_P (ಅಭಿವ್ಯಕ್ತಿ) && !lval && (optimize || in_init))
	{
	  ಯದಿ (in_init)
	    ret = decl_constant_ಮೌಲ್ಯ_1 (ಅಭಿವ್ಯಕ್ತಿ, ಸತ್ಯ);
	  ಅನ್ಯಥಾ
	    {
	      ret = decl_constant_ಮೌಲ್ಯ (ಅಭಿವ್ಯಕ್ತಿ);
	      ಯದಿ (ret != ಅಭಿವ್ಯಕ್ತಿ
		  && (TYPE_MODE (ವೃಕ್ಷ_TYPE (ret)) == BLKmode
		      || ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (ret)) == ARRAY_TYPE))
		ಪ್ರತ್ಯಾಗಮ ಅಭಿವ್ಯಕ್ತಿ;
	    }
	  /* Avoid unwanted tree sharing between the initializer and current
	     function's body where the tree can be modified e.g. by the
	     gimplifier.  */
	  ಯದಿ (ret != ಅಭಿವ್ಯಕ್ತಿ && ವೃಕ್ಷ_STATIC (ಅಭಿವ್ಯಕ್ತಿ))
	    ret = unshare_ಅಭಿವ್ಯಕ್ತಿ (ret);
	  ಪ್ರತ್ಯಾಗಮ ret;
	}
      ಪ್ರತ್ಯಾಗಮ ಅಭಿವ್ಯಕ್ತಿ;
    }

  ಯದಿ (IS_ಅಭಿವ್ಯಕ್ತಿ_CODE_CLASS (kind))
    old_range = ಅಭಿವ್ಯಕ್ತಿ_LOCATION_RANGE (ಅಭಿವ್ಯಕ್ತಿ);

  /* Operands of variable-length expressions (function calls) have
     already been folded, as have __builtin_* function calls, and such
     expressions cannot occur in constant expressions.  */
  ಯದಿ (kind == tcc_vl_exp)
    {
      *maybe_const_operands = ಅಸತ್ಯ;
      ret = fold (ಅಭಿವ್ಯಕ್ತಿ);
      ಗಚ್ಛ out;
    }

  ಯದಿ (code == C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ)
    {
      ವೃಕ್ಷ pre = C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_PRE (ಅಭಿವ್ಯಕ್ತಿ);
      ವೃಕ್ಷ inner = C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_ಅಭಿವ್ಯಕ್ತಿ (ಅಭಿವ್ಯಕ್ತಿ);
      ಯದಿ (C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_NON_CONST (ಅಭಿವ್ಯಕ್ತಿ))
	*maybe_const_operands = ಅಸತ್ಯ;
      ಯದಿ (C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_INT_OPERANDS (ಅಭಿವ್ಯಕ್ತಿ))
	{
	  *maybe_const_itself = ಅಸತ್ಯ;
	  inner = c_fully_fold_internal (inner, in_init, maybe_const_operands,
					 maybe_const_itself, ಸತ್ಯ, lval);
	}
      ಯದಿ (pre && !in_init)
	ret = build2 (COMPOUND_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ), pre, inner);
      ಅನ್ಯಥಾ
	ret = inner;
      ಗಚ್ಛ out;
    }

  /* Assignment, increment, decrement, function call and comma
     operators, and statement expressions, cannot occur in constant
     expressions if evaluated / outside of sizeof.  (Function calls
     were handled above, though VA_ARG_EXPR is treated like a function
     call here, and statement expressions are handled through
     C_MAYBE_CONST_EXPR to avoid folding inside them.)  */
  ವಿಕಲ್ಪ (code)
    {
    ಪಕ್ಷ MODIFY_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ PREDECREMENT_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ PREINCREMENT_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ POSTDECREMENT_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ POSTINCREMENT_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ COMPOUND_ಅಭಿವ್ಯಕ್ತಿ:
      *maybe_const_operands = ಅಸತ್ಯ;
      ಭಙ್ಗ;

    ಪಕ್ಷ VA_ARG_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ TARGET_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ BIND_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ OBJ_TYPE_REF:
      *maybe_const_operands = ಅಸತ್ಯ;
      ret = fold (ಅಭಿವ್ಯಕ್ತಿ);
      ಗಚ್ಛ out;

    ಸ್ವಭಾವ:
      ಭಙ್ಗ;
    }

  /* Fold individual tree codes as appropriate.  */
  ವಿಕಲ್ಪ (code)
    {
    ಪಕ್ಷ COMPOUND_LITERAL_ಅಭಿವ್ಯಕ್ತಿ:
      /* Any non-constancy will have been marked in a containing
	 C_MAYBE_CONST_EXPR; there is no more folding to do here.  */
      ಗಚ್ಛ out;

    ಪಕ್ಷ COMPONENT_REF:
      orig_op0 = op0 = ವೃಕ್ಷ_OPERAND (ಅಭಿವ್ಯಕ್ತಿ, 0);
      op1 = ವೃಕ್ಷ_OPERAND (ಅಭಿವ್ಯಕ್ತಿ, 1);
      op2 = ವೃಕ್ಷ_OPERAND (ಅಭಿವ್ಯಕ್ತಿ, 2);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, lval);
      STRIP_TYPE_NOPS (op0);
      ಯದಿ (op0 != orig_op0)
	ret = build3 (COMPONENT_REF, ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ), op0, op1, op2);
      ಯದಿ (ret != ಅಭಿವ್ಯಕ್ತಿ)
	{
	  ವೃಕ್ಷ_READONLY (ret) = ವೃಕ್ಷ_READONLY (ಅಭಿವ್ಯಕ್ತಿ);
	  ವೃಕ್ಷ_THIS_VOLATILE (ret) = ವೃಕ್ಷ_THIS_VOLATILE (ಅಭಿವ್ಯಕ್ತಿ);
	}
      ಯದಿ (!lval)
	ret = fold (ret);
      ಗಚ್ಛ out;

    ಪಕ್ಷ ARRAY_REF:
      orig_op0 = op0 = ವೃಕ್ಷ_OPERAND (ಅಭಿವ್ಯಕ್ತಿ, 0);
      orig_op1 = op1 = ವೃಕ್ಷ_OPERAND (ಅಭಿವ್ಯಕ್ತಿ, 1);
      op2 = ವೃಕ್ಷ_OPERAND (ಅಭಿವ್ಯಕ್ತಿ, 2);
      op3 = ವೃಕ್ಷ_OPERAND (ಅಭಿವ್ಯಕ್ತಿ, 3);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, lval);
      STRIP_TYPE_NOPS (op0);
      op1 = c_fully_fold_internal (op1, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, ಅಸತ್ಯ);
      STRIP_TYPE_NOPS (op1);
      /* Fold "foo"[2] in initializers.  */
      ಯದಿ (!lval && in_init)
	{
	  ret = c_fold_array_ref (ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ), op0, op1);
	  ಯದಿ (ret)
	    ಗಚ್ಛ out;
	  ret = ಅಭಿವ್ಯಕ್ತಿ;
	}
      ಯದಿ (op0 != orig_op0 || op1 != orig_op1)
	ret = build4 (ARRAY_REF, ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ), op0, op1, op2, op3);
      ಯದಿ (ret != ಅಭಿವ್ಯಕ್ತಿ)
	{
	  ವೃಕ್ಷ_READONLY (ret) = ವೃಕ್ಷ_READONLY (ಅಭಿವ್ಯಕ್ತಿ);
	  ವೃಕ್ಷ_SIDE_EFFECTS (ret) = ವೃಕ್ಷ_SIDE_EFFECTS (ಅಭಿವ್ಯಕ್ತಿ);
	  ವೃಕ್ಷ_THIS_VOLATILE (ret) = ವೃಕ್ಷ_THIS_VOLATILE (ಅಭಿವ್ಯಕ್ತಿ);
	}
      ಯದಿ (!lval)
	ret = fold (ret);
      ಗಚ್ಛ out;

    ಪಕ್ಷ MODIFY_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ PREDECREMENT_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ PREINCREMENT_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ POSTDECREMENT_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ POSTINCREMENT_ಅಭಿವ್ಯಕ್ತಿ:
      op0_lval = ಸತ್ಯ;
      /* FALLTHRU */
    ಪಕ್ಷ COMPOUND_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ PLUS_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ MINUS_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ MULT_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ POINTER_PLUS_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ POINTER_DIFF_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ TRUNC_DIV_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ CEIL_DIV_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ FLOOR_DIV_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ TRUNC_MOD_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ RDIV_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ EXACT_DIV_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ LSHIFT_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ RSHIFT_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ LROTATE_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ RROTATE_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ BIT_IOR_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ BIT_XOR_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ BIT_AND_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ LT_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ LE_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ GT_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ GE_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ EQ_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ NE_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ COMPLEX_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ TRUTH_AND_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ TRUTH_OR_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ TRUTH_XOR_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ UNORDERED_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ ORDERED_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ UNLT_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ UNLE_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ UNGT_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ UNGE_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ UNEQ_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ MEM_REF:
      /* Binary operations evaluating both arguments (increment and
	 decrement are binary internally in GCC).  */
      orig_op0 = op0 = ವೃಕ್ಷ_OPERAND (ಅಭಿವ್ಯಕ್ತಿ, 0);
      orig_op1 = op1 = ವೃಕ್ಷ_OPERAND (ಅಭಿವ್ಯಕ್ತಿ, 1);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const,
				   op0_lval);
      STRIP_TYPE_NOPS (op0);
      /* The RHS of a MODIFY_EXPR was fully folded when building that
	 expression for the sake of conversion warnings.  */
      ಯದಿ (code != MODIFY_ಅಭಿವ್ಯಕ್ತಿ)
	op1 = c_fully_fold_internal (op1, in_init, maybe_const_operands,
				     maybe_const_itself, for_int_const, ಅಸತ್ಯ);
      STRIP_TYPE_NOPS (op1);

      ಯದಿ (for_int_const && (ವೃಕ್ಷ_CODE (op0) != INTEGER_CST
			    || ವೃಕ್ಷ_CODE (op1) != INTEGER_CST))
	ಗಚ್ಛ out;

      ಯದಿ (ವೃಕ್ಷ_CODE_CLASS (code) == tcc_comparison
	  && ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (op0)) == NULLPTR_TYPE
	  && ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (op1)) == NULLPTR_TYPE)
	{
	  ವಿಕಲ್ಪ (code)
	    {
	    ಪಕ್ಷ EQ_ಅಭಿವ್ಯಕ್ತಿ:
	      ret = constant_boolean_ಗಂಟು (ಸತ್ಯ, ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ));
	      ಭಙ್ಗ;
	    ಪಕ್ಷ NE_ಅಭಿವ್ಯಕ್ತಿ:
	      ret = constant_boolean_ಗಂಟು (ಅಸತ್ಯ, ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ));
	      ಭಙ್ಗ;
	    ಸ್ವಭಾವ:
	      gcc_unreachable ();
	    }
	  ret = omit_two_operands_loc (loc, ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ), ret,
				       op0, op1);
	}
      ಅನ್ಯಥಾ ಯದಿ (op0 != orig_op0 || op1 != orig_op1 || in_init)
	ret = in_init
	  ? fold_build2_initializer_loc (loc, code, ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ), op0, op1)
	  : fold_build2_loc (loc, code, ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ), op0, op1);
      ಅನ್ಯಥಾ
	ret = fold (ಅಭಿವ್ಯಕ್ತಿ);
      ಯದಿ (ವೃಕ್ಷ_OVERFLOW_P (ret)
	  && !ವೃಕ್ಷ_OVERFLOW_P (op0)
	  && !(ದ್ವಿಮಾನ_CLASS_P (op0) && ವೃಕ್ಷ_OVERFLOW_P (ವೃಕ್ಷ_OPERAND (op0, 1)))
	  && !ವೃಕ್ಷ_OVERFLOW_P (op1))
	overflow_warning (ಅಭಿವ್ಯಕ್ತಿ_LOC_OR_LOC (ಅಭಿವ್ಯಕ್ತಿ, ಒಳಹರಿವು_location), ret, ಅಭಿವ್ಯಕ್ತಿ);
      ಯದಿ (code == LSHIFT_ಅಭಿವ್ಯಕ್ತಿ
	  && ವೃಕ್ಷ_CODE (orig_op0) != INTEGER_CST
	  && (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (orig_op0)) == INTEGER_TYPE
	      || ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (orig_op0)) == BITINT_TYPE)
	  && ವೃಕ್ಷ_CODE (op0) == INTEGER_CST
	  && c_inhibit_evaluation_warnings == 0
	  && !TYPE_OVERFLOW_WRAPS (ವೃಕ್ಷ_TYPE (orig_op0))
	  && ವೃಕ್ಷ_int_cst_sgn (op0) < 0)
	warning_at (loc, OPT_Wshift_negative_ಮೌಲ್ಯ,
		    "left shift of negative value");
      ಯದಿ ((code == LSHIFT_ಅಭಿವ್ಯಕ್ತಿ
	   || code == RSHIFT_ಅಭಿವ್ಯಕ್ತಿ
	   || code == LROTATE_ಅಭಿವ್ಯಕ್ತಿ
	   || code == RROTATE_ಅಭಿವ್ಯಕ್ತಿ)
	  && ವೃಕ್ಷ_CODE (orig_op1) != INTEGER_CST
	  && ವೃಕ್ಷ_CODE (op1) == INTEGER_CST
	  && ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (orig_op1)) == INTEGER_TYPE
	  && c_inhibit_evaluation_warnings == 0)
	{
	  ಯದಿ (ವೃಕ್ಷ_int_cst_sgn (op1) < 0)
	    warning_at (loc, OPT_Wshift_ಎಣಿಕೆ_negative,
			(code == LSHIFT_ಅಭಿವ್ಯಕ್ತಿ
			 ? G_("left shift count is negative")
			 : G_("right shift count is negative")));
	  ಅನ್ಯಥಾ ಯದಿ ((ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (orig_op0)) == INTEGER_TYPE
		    || ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (orig_op0)) == BITINT_TYPE
		    || ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (orig_op0)) == FIXED_POINT_TYPE)
		   && compare_ವೃಕ್ಷ_int (op1,
					TYPE_PRECISION (ವೃಕ್ಷ_TYPE (orig_op0)))
		      >= 0
		   && !warning_suppressed_p (ಅಭಿವ್ಯಕ್ತಿ, OPT_Wshift_ಎಣಿಕೆ_overflow))
	    warning_at (loc, OPT_Wshift_ಎಣಿಕೆ_overflow,
			(code == LSHIFT_ಅಭಿವ್ಯಕ್ತಿ
			 ? G_("left shift count >= width of type")
			 : G_("right shift count >= width of type")));
	  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (orig_op0)) == VECTOR_TYPE
		   && compare_ವೃಕ್ಷ_int (op1,
					TYPE_PRECISION (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (orig_op0))))
		      >= 0)
	    warning_at (loc, OPT_Wshift_ಎಣಿಕೆ_overflow,
			code == LSHIFT_ಅಭಿವ್ಯಕ್ತಿ
			? G_("left shift count >= width of vector element")
			: G_("right shift count >= width of vector element"));
	}
      ಯದಿ (code == LSHIFT_ಅಭಿವ್ಯಕ್ತಿ
	  /* If either OP0 has been folded to INTEGER_CST...  */
	  && ((ವೃಕ್ಷ_CODE (orig_op0) != INTEGER_CST
	       && (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (orig_op0)) == INTEGER_TYPE
		   || ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (orig_op0)) == BITINT_TYPE)
	       && ವೃಕ್ಷ_CODE (op0) == INTEGER_CST)
	      /* ...or if OP1 has been folded to INTEGER_CST...  */
	      || (ವೃಕ್ಷ_CODE (orig_op1) != INTEGER_CST
		  && (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (orig_op1)) == INTEGER_TYPE
		      || ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (orig_op1)) == BITINT_TYPE)
		  && ವೃಕ್ಷ_CODE (op1) == INTEGER_CST))
	  && c_inhibit_evaluation_warnings == 0)
	/* ...then maybe we can detect an overflow.  */
	maybe_warn_shift_overflow (loc, op0, op1);
      ಯದಿ ((code == TRUNC_DIV_ಅಭಿವ್ಯಕ್ತಿ
	   || code == CEIL_DIV_ಅಭಿವ್ಯಕ್ತಿ
	   || code == FLOOR_DIV_ಅಭಿವ್ಯಕ್ತಿ
	   || code == EXACT_DIV_ಅಭಿವ್ಯಕ್ತಿ
	   || code == TRUNC_MOD_ಅಭಿವ್ಯಕ್ತಿ)
	  && ವೃಕ್ಷ_CODE (orig_op1) != INTEGER_CST
	  && ವೃಕ್ಷ_CODE (op1) == INTEGER_CST
	  && (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (orig_op0)) == INTEGER_TYPE
	      || ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (orig_op0)) == BITINT_TYPE
	      || ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (orig_op0)) == FIXED_POINT_TYPE)
	  && (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (orig_op1)) == INTEGER_TYPE
	      || ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (orig_op1)) == BITINT_TYPE))
	warn_for_div_by_zero (loc, op1);
      ಯದಿ (code == MEM_REF
	  && ret != ಅಭಿವ್ಯಕ್ತಿ
	  && ವೃಕ್ಷ_CODE (ret) == MEM_REF)
	{
	  ವೃಕ್ಷ_READONLY (ret) = ವೃಕ್ಷ_READONLY (ಅಭಿವ್ಯಕ್ತಿ);
	  ವೃಕ್ಷ_SIDE_EFFECTS (ret) = ವೃಕ್ಷ_SIDE_EFFECTS (ಅಭಿವ್ಯಕ್ತಿ);
	  ವೃಕ್ಷ_THIS_VOLATILE (ret) = ವೃಕ್ಷ_THIS_VOLATILE (ಅಭಿವ್ಯಕ್ತಿ);
	}
      ಗಚ್ಛ out;

    ಪಕ್ಷ ADDR_ಅಭಿವ್ಯಕ್ತಿ:
      op0_lval = ಸತ್ಯ;
      ಗಚ್ಛ unary;
    ಪಕ್ಷ REALPART_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ IMAGPART_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ VIEW_CONVERT_ಅಭಿವ್ಯಕ್ತಿ:
      op0_lval = lval;
      /* FALLTHRU */
    ಪಕ್ಷ INDIRECT_REF:
    ಪಕ್ಷ FIX_TRUNC_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ FLOAT_ಅಭಿವ್ಯಕ್ತಿ:
    CASE_CONVERT:
    ಪಕ್ಷ ADDR_SPACE_CONVERT_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ NON_LVALUE_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ NEGATE_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ BIT_NOT_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ TRUTH_NOT_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ CONJ_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ PAREN_ಅಭಿವ್ಯಕ್ತಿ:
    unary:
      /* Unary operations.  */
      orig_op0 = op0 = ವೃಕ್ಷ_OPERAND (ಅಭಿವ್ಯಕ್ತಿ, 0);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const,
				   op0_lval);
      STRIP_TYPE_NOPS (op0);

      ಯದಿ (for_int_const && ವೃಕ್ಷ_CODE (op0) != INTEGER_CST)
	ಗಚ್ಛ out;

      /* ??? Cope with user tricks that amount to offsetof.  The middle-end is
	 not prepared to deal with them if they occur in initializers.  */
      ಯದಿ (op0 != orig_op0
	  && code == ADDR_ಅಭಿವ್ಯಕ್ತಿ
	  && (op1 = get_base_address (op0)) != NULL_ವೃಕ್ಷ
	  && INDIRECT_REF_P (op1)
	  && ವೃಕ್ಷ_CONSTANT (ವೃಕ್ಷ_OPERAND (op1, 0)))
	ret = fold_offsetof (op0, ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ));
      ಅನ್ಯಥಾ ಯದಿ (op0 != orig_op0 || in_init)
	ret = in_init
	  ? fold_build1_initializer_loc (loc, code, ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ), op0)
	  : fold_build1_loc (loc, code, ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ), op0);
      ಅನ್ಯಥಾ
	ret = fold (ಅಭಿವ್ಯಕ್ತಿ);
      ಯದಿ (code == INDIRECT_REF
	  && ret != ಅಭಿವ್ಯಕ್ತಿ
	  && INDIRECT_REF_P (ret))
	{
	  ವೃಕ್ಷ_READONLY (ret) = ವೃಕ್ಷ_READONLY (ಅಭಿವ್ಯಕ್ತಿ);
	  ವೃಕ್ಷ_SIDE_EFFECTS (ret) = ವೃಕ್ಷ_SIDE_EFFECTS (ಅಭಿವ್ಯಕ್ತಿ);
	  ವೃಕ್ಷ_THIS_VOLATILE (ret) = ವೃಕ್ಷ_THIS_VOLATILE (ಅಭಿವ್ಯಕ್ತಿ);
	}
      ವಿಕಲ್ಪ (code)
	{
	ಪಕ್ಷ FIX_TRUNC_ಅಭಿವ್ಯಕ್ತಿ:
	ಪಕ್ಷ FLOAT_ಅಭಿವ್ಯಕ್ತಿ:
	CASE_CONVERT:
	  /* Don't warn about explicit conversions.  We will already
	     have warned about suspect implicit conversions.  */
	  ಭಙ್ಗ;

	ಸ್ವಭಾವ:
	  ಯದಿ (ವೃಕ್ಷ_OVERFLOW_P (ret) && !ವೃಕ್ಷ_OVERFLOW_P (op0))
	    overflow_warning (ಅಭಿವ್ಯಕ್ತಿ_LOCATION (ಅಭಿವ್ಯಕ್ತಿ), ret, op0);
	  ಭಙ್ಗ;
	}
      ಗಚ್ಛ out;

    ಪಕ್ಷ TRUTH_ANDIF_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ TRUTH_ORIF_ಅಭಿವ್ಯಕ್ತಿ:
      /* Binary operations not necessarily evaluating both
	 arguments.  */
      orig_op0 = op0 = ವೃಕ್ಷ_OPERAND (ಅಭಿವ್ಯಕ್ತಿ, 0);
      orig_op1 = op1 = ವೃಕ್ಷ_OPERAND (ಅಭಿವ್ಯಕ್ತಿ, 1);
      op0 = c_fully_fold_internal (op0, in_init, &op0_const, &op0_const_self,
				   for_int_const, ಅಸತ್ಯ);
      STRIP_TYPE_NOPS (op0);

      unused_p = (op0 == (code == TRUTH_ANDIF_ಅಭಿವ್ಯಕ್ತಿ
			  ? truthvalue_false_ಗಂಟು
			  : truthvalue_true_ಗಂಟು));
      c_disable_warnings (unused_p);
      op1 = c_fully_fold_internal (op1, in_init, &op1_const, &op1_const_self,
				   for_int_const, ಅಸತ್ಯ);
      STRIP_TYPE_NOPS (op1);
      c_enable_warnings (unused_p);

      ಯದಿ (for_int_const
	  && (ವೃಕ್ಷ_CODE (op0) != INTEGER_CST
	      /* Require OP1 be an INTEGER_CST only if it's evaluated.  */
	      || (!unused_p && ವೃಕ್ಷ_CODE (op1) != INTEGER_CST)))
	ಗಚ್ಛ out;

      ಯದಿ (op0 != orig_op0 || op1 != orig_op1 || in_init)
	ret = in_init
	  ? fold_build2_initializer_loc (loc, code, ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ), op0, op1)
	  : fold_build2_loc (loc, code, ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ), op0, op1);
      ಅನ್ಯಥಾ
	ret = fold (ಅಭಿವ್ಯಕ್ತಿ);
      *maybe_const_operands &= op0_const;
      *maybe_const_itself &= op0_const_self;
      ಯದಿ (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && (code == TRUTH_ANDIF_ಅಭಿವ್ಯಕ್ತಿ
		? op0 == truthvalue_false_ಗಂಟು
		: op0 == truthvalue_true_ಗಂಟು)))
	*maybe_const_operands &= op1_const;
      ಯದಿ (!(op0_const
	    && op0_const_self
	    && (code == TRUTH_ANDIF_ಅಭಿವ್ಯಕ್ತಿ
		? op0 == truthvalue_false_ಗಂಟು
		: op0 == truthvalue_true_ಗಂಟು)))
	*maybe_const_itself &= op1_const_self;
      ಗಚ್ಛ out;

    ಪಕ್ಷ COND_ಅಭಿವ್ಯಕ್ತಿ:
      orig_op0 = op0 = ವೃಕ್ಷ_OPERAND (ಅಭಿವ್ಯಕ್ತಿ, 0);
      orig_op1 = op1 = ವೃಕ್ಷ_OPERAND (ಅಭಿವ್ಯಕ್ತಿ, 1);
      orig_op2 = op2 = ವೃಕ್ಷ_OPERAND (ಅಭಿವ್ಯಕ್ತಿ, 2);
      op0 = c_fully_fold_internal (op0, in_init, &op0_const, &op0_const_self,
				   for_int_const, ಅಸತ್ಯ);

      STRIP_TYPE_NOPS (op0);
      c_disable_warnings (op0 == truthvalue_false_ಗಂಟು);
      op1 = c_fully_fold_internal (op1, in_init, &op1_const, &op1_const_self,
				   for_int_const, ಅಸತ್ಯ);
      STRIP_TYPE_NOPS (op1);
      c_enable_warnings (op0 == truthvalue_false_ಗಂಟು);

      c_disable_warnings (op0 == truthvalue_true_ಗಂಟು);
      op2 = c_fully_fold_internal (op2, in_init, &op2_const, &op2_const_self,
				   for_int_const, ಅಸತ್ಯ);
      STRIP_TYPE_NOPS (op2);
      c_enable_warnings (op0 == truthvalue_true_ಗಂಟು);

      ಯದಿ (for_int_const
	  && (ವೃಕ್ಷ_CODE (op0) != INTEGER_CST
	      /* Only the evaluated operand must be an INTEGER_CST.  */
	      || (op0 == truthvalue_true_ಗಂಟು
		  ? ವೃಕ್ಷ_CODE (op1) != INTEGER_CST
		  : ವೃಕ್ಷ_CODE (op2) != INTEGER_CST)))
	ಗಚ್ಛ out;

      ಯದಿ (op0 != orig_op0 || op1 != orig_op1 || op2 != orig_op2)
	ret = fold_build3_loc (loc, code, ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ), op0, op1, op2);
      ಅನ್ಯಥಾ
	ret = fold (ಅಭಿವ್ಯಕ್ತಿ);
      *maybe_const_operands &= op0_const;
      *maybe_const_itself &= op0_const_self;
      ಯದಿ (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && op0 == truthvalue_false_ಗಂಟು))
	*maybe_const_operands &= op1_const;
      ಯದಿ (!(op0_const
	    && op0_const_self
	    && op0 == truthvalue_false_ಗಂಟು))
	*maybe_const_itself &= op1_const_self;
      ಯದಿ (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && op0 == truthvalue_true_ಗಂಟು))
	*maybe_const_operands &= op2_const;
      ಯದಿ (!(op0_const
	    && op0_const_self
	    && op0 == truthvalue_true_ಗಂಟು))
	*maybe_const_itself &= op2_const_self;
      ಗಚ್ಛ out;

    ಪಕ್ಷ VEC_COND_ಅಭಿವ್ಯಕ್ತಿ:
      orig_op0 = op0 = ವೃಕ್ಷ_OPERAND (ಅಭಿವ್ಯಕ್ತಿ, 0);
      orig_op1 = op1 = ವೃಕ್ಷ_OPERAND (ಅಭಿವ್ಯಕ್ತಿ, 1);
      orig_op2 = op2 = ವೃಕ್ಷ_OPERAND (ಅಭಿವ್ಯಕ್ತಿ, 2);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, ಅಸತ್ಯ);
      STRIP_TYPE_NOPS (op0);
      op1 = c_fully_fold_internal (op1, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, ಅಸತ್ಯ);
      STRIP_TYPE_NOPS (op1);
      op2 = c_fully_fold_internal (op2, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, ಅಸತ್ಯ);
      STRIP_TYPE_NOPS (op2);

      ಯದಿ (op0 != orig_op0 || op1 != orig_op1 || op2 != orig_op2)
	ret = fold_build3_loc (loc, code, ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ), op0, op1, op2);
      ಅನ್ಯಥಾ
	ret = fold (ಅಭಿವ್ಯಕ್ತಿ);
      ಗಚ್ಛ out;

    ಪಕ್ಷ EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ:
      /* Each case where an operand with excess precision may be
	 encountered must remove the EXCESS_PRECISION_EXPR around
	 inner operands and possibly put one around the whole
	 expression or possibly convert to the semantic type (which
	 c_fully_fold does); we cannot tell at this stage which is
	 appropriate in any particular case.  */
      gcc_unreachable ();

    ಪಕ್ಷ SAVE_ಅಭಿವ್ಯಕ್ತಿ:
      /* Make sure to fold the contents of a SAVE_EXPR exactly once.  */
      op0 = ವೃಕ್ಷ_OPERAND (ಅಭಿವ್ಯಕ್ತಿ, 0);
      ಯದಿ (!SAVE_ಅಭಿವ್ಯಕ್ತಿ_FOLDED_P (ಅಭಿವ್ಯಕ್ತಿ))
	{
	  op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				       maybe_const_itself, for_int_const,
				       ಅಸತ್ಯ);
	  ವೃಕ್ಷ_OPERAND (ಅಭಿವ್ಯಕ್ತಿ, 0) = op0;
	  SAVE_ಅಭಿವ್ಯಕ್ತಿ_FOLDED_P (ಅಭಿವ್ಯಕ್ತಿ) = ಸತ್ಯ;
	}
      /* Return the SAVE_EXPR operand if it is invariant.  */
      ಯದಿ (ವೃಕ್ಷ_invariant_p (op0))
	ret = op0;
      ಗಚ್ಛ out;

    ಸ್ವಭಾವ:
      /* Various codes may appear through folding built-in functions
	 and their arguments.  */
      ಗಚ್ಛ out;
    }

 out:
  /* Some folding may introduce NON_LVALUE_EXPRs; all lvalue checks
     have been done by this point, so remove them again.  */
  nowarning |= warning_suppressed_p (ret, OPT_Woverflow);
  STRIP_TYPE_NOPS (ret);
  ಯದಿ (nowarning && !warning_suppressed_p (ret, OPT_Woverflow))
    {
      ಯದಿ (!CAN_HAVE_LOCATION_P (ret))
	ret = build1 (NOP_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (ret), ret);
      suppress_warning (ret, OPT_Woverflow);
    }
  ಯದಿ (ret != ಅಭಿವ್ಯಕ್ತಿ)
    {
      protected_set_ಅಭಿವ್ಯಕ್ತಿ_location (ret, loc);
      ಯದಿ (IS_ಅಭಿವ್ಯಕ್ತಿ_CODE_CLASS (kind))
	set_source_range (ret, old_range.m_start, old_range.m_finish);
    }
  ಪ್ರತ್ಯಾಗಮ ret;
}

/* Fold X for consideration by one of the warning functions when checking
   whether an expression has a constant value.  */

ವೃಕ್ಷ
fold_for_warn (ವೃಕ್ಷ x)
{
  /* The C front-end has already folded X appropriately.  */
  ಪ್ರತ್ಯಾಗಮ x;
}
