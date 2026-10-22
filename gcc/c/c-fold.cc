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

ಸ್ಥಿರ ವೃಕ್ಷ c_fully_fold_ಆಂತರಿಕ (ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ, ತಾರ್ಕಿಕ, ತಾರ್ಕಿಕ *, ತಾರ್ಕಿಕ *, ತಾರ್ಕಿಕ,
				   ತಾರ್ಕಿಕ);

/* If DISABLE is true, stop issuing warnings.  This is used when
   parsing code that we know will not be executed.  This function may
   be called multiple times, and works as a stack.  */

ಸ್ಥಿರ ಶೂನ್ಯ
c_disable_warnings (ತಾರ್ಕಿಕ disable)
{
  ಆದರೆ (disable)
    {
      ++c_inhibit_evaluation_warnings;
    }
}

/* If ENABLE is true, re-enable issuing warnings.  */

ಸ್ಥಿರ ಶೂನ್ಯ
c_enable_warnings (ತಾರ್ಕಿಕ enable)
{
  ಆದರೆ (enable)
    {
      --c_inhibit_evaluation_warnings;
    }
}

/* Try to fold ARRAY_REF ary[index] if possible and not handled by
   normal fold, return NULL_TREE otherwise.  */

ಸ್ಥಿರ ವೃಕ್ಷ
c_fold_array_ref (ವೃಕ್ಷ type, ವೃಕ್ಷ ary, ವೃಕ್ಷ ಸೂಚ್ಯಂಕ)
{
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ary) != STRING_CST
      || ವೃಕ್ಷ_ಸಂಕೇತ (ಸೂಚ್ಯಂಕ) != INTEGER_CST
      || ವೃಕ್ಷ_ಅತಿಪ್ರವಾಹ (ಸೂಚ್ಯಂಕ)
      || ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (ary)) != ARRAY_TYPE
      || !ವೃಕ್ಷ_ಹೊಂದುತ್ತದೆ_uhwi_p (ಸೂಚ್ಯಂಕ))
    ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;

  ವೃಕ್ಷ elem_type = ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (ary));
  ಚಿಹ್ನೆರಹಿತ elem_nchars = (TYPE_PRECISION (elem_type)
			  / TYPE_PRECISION (char_type_ಗಂಟು));
  ಚಿಹ್ನೆರಹಿತ len = (ಚಿಹ್ನೆರಹಿತ) ವೃಕ್ಷ_STRING_ಉದ್ದಳತೆ (ary) / elem_nchars;
  ವೃಕ್ಷ nelts_minus_one = array_type_nelts_minus_one (ವೃಕ್ಷ_TYPE (ary));
  ತಾರ್ಕಿಕ dummy1 = ನಿಜ, dummy2 = ನಿಜ;
  nelts_minus_one = c_fully_fold_ಆಂತರಿಕ (nelts_minus_one, ನಿಜ, &dummy1,
					   &dummy2, ಸುಳ್ಳು, ಸುಳ್ಳು);
  ಚಿಹ್ನೆರಹಿತ HOST_WIDE_INT i = ವೃಕ್ಷ_ಗಮ್ಯ_uhwi (ಸೂಚ್ಯಂಕ);
  ಆದರೆ (!ವೃಕ್ಷ_int_cst_le (ಸೂಚ್ಯಂಕ, nelts_minus_one)
      || i >= len
      || i + elem_nchars > len)
    ಹಿಂತಿರುಗಿ NULL_ವೃಕ್ಷ;

  ಆದರೆ (elem_nchars == 1)
    ಹಿಂತಿರುಗಿ build_int_cst (type, ವೃಕ್ಷ_STRING_ಸೂಚಕ (ary)[i]);

  ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *ptr
    = ((ಸ್ಥಿರಾಂಕ ಚಿಹ್ನೆರಹಿತ ಅಕ್ಷರ *)ವೃಕ್ಷ_STRING_ಸೂಚಕ (ary) + i * elem_nchars);
  ಹಿಂತಿರುಗಿ native_interpret_ಅಭಿವ್ಯಕ್ತಿ (type, ptr, elem_nchars);
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
c_fully_fold (ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ, ತಾರ್ಕಿಕ ಒಳ_init, ತಾರ್ಕಿಕ *maybe_const, ತಾರ್ಕಿಕ lval)
{
  ವೃಕ್ಷ ret;
  ವೃಕ್ಷ eptype = NULL_ವೃಕ್ಷ;
  ತಾರ್ಕಿಕ dummy = ನಿಜ;
  ತಾರ್ಕಿಕ maybe_const_itself = ನಿಜ;
  location_t loc = ಅಭಿವ್ಯಕ್ತಿ_LOCATION (ಅಭಿವ್ಯಕ್ತಿ);

  ಆದರೆ (!maybe_const)
    maybe_const = &dummy;
  ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ಅಭಿವ್ಯಕ್ತಿ) == EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ)
    {
      eptype = ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ);
      ಅಭಿವ್ಯಕ್ತಿ = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಅಭಿವ್ಯಕ್ತಿ, 0);
    }
  ret = c_fully_fold_ಆಂತರಿಕ (ಅಭಿವ್ಯಕ್ತಿ, ಒಳ_init, maybe_const,
			       &maybe_const_itself, ಸುಳ್ಳು, lval);
  ಆದರೆ (eptype)
    ret = fold_convert_loc (loc, eptype, ret);
  *maybe_const &= maybe_const_itself;
  ಹಿಂತಿರುಗಿ ret;
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
c_fully_fold_ಆಂತರಿಕ (ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ, ತಾರ್ಕಿಕ ಒಳ_init, ತಾರ್ಕಿಕ *maybe_const_operands,
		       ತಾರ್ಕಿಕ *maybe_const_itself, ತಾರ್ಕಿಕ for_int_const, ತಾರ್ಕಿಕ lval)
{
  ವೃಕ್ಷ ret = ಅಭಿವ್ಯಕ್ತಿ;
  ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_2 ಸಂಕೇತ_2 = ವೃಕ್ಷ_ಸಂಕೇತ (ಅಭಿವ್ಯಕ್ತಿ);
  ಎಣಿಕೆ ವೃಕ್ಷ_ಸಂಕೇತ_class ಬಗೆ = ವೃಕ್ಷ_ಸಂಕೇತ_CLASS (ಸಂಕೇತ_2);
  location_t loc = ಅಭಿವ್ಯಕ್ತಿ_LOCATION (ಅಭಿವ್ಯಕ್ತಿ);
  ವೃಕ್ಷ op0, op1, op2, op3;
  ವೃಕ್ಷ orig_op0, orig_op1, orig_op2;
  ತಾರ್ಕಿಕ op0_const = ನಿಜ, op1_const = ನಿಜ, op2_const = ನಿಜ;
  ತಾರ್ಕಿಕ op0_const_self = ನಿಜ, op1_const_self = ನಿಜ, op2_const_self = ನಿಜ;
  ತಾರ್ಕಿಕ nowarning = warning_suppressed_p (ಅಭಿವ್ಯಕ್ತಿ, OPT_Woverflow);
  ತಾರ್ಕಿಕ ಬಳಸದ_p;
  ತಾರ್ಕಿಕ op0_lval = ಸುಳ್ಳು;
  ಮೂಲ_range old_range;

  /* Constants, declarations, statements, errors, and anything else not
     counted as an expression cannot usefully be folded further at this
     point.  */
  ಆದರೆ (!IS_ಅಭಿವ್ಯಕ್ತಿ_ಸಂಕೇತ_CLASS (ಬಗೆ) || ಬಗೆ == tcc_statement)
    {
      /* Except for variables which we can optimize to its initializer.  */
      ಆದರೆ (VAR_P (ಅಭಿವ್ಯಕ್ತಿ) && !lval && (optimize || ಒಳ_init))
	{
	  ಆದರೆ (ಒಳ_init)
	    ret = decl_constant_ಮೌಲ್ಯ_1 (ಅಭಿವ್ಯಕ್ತಿ, ನಿಜ);
	  ಇಲ್ಲದಿದ್ದರೆ
	    {
	      ret = decl_constant_ಮೌಲ್ಯ (ಅಭಿವ್ಯಕ್ತಿ);
	      ಆದರೆ (ret != ಅಭಿವ್ಯಕ್ತಿ
		  && (TYPE_ಬಹುಲಕ (ವೃಕ್ಷ_TYPE (ret)) == BLKmode
		      || ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (ret)) == ARRAY_TYPE))
		ಹಿಂತಿರುಗಿ ಅಭಿವ್ಯಕ್ತಿ;
	    }
	  /* Avoid unwanted tree sharing between the initializer and current
	     function's body where the tree can be modified e.g. by the
	     gimplifier.  */
	  ಆದರೆ (ret != ಅಭಿವ್ಯಕ್ತಿ && ವೃಕ್ಷ_STATIC (ಅಭಿವ್ಯಕ್ತಿ))
	    ret = unshare_ಅಭಿವ್ಯಕ್ತಿ (ret);
	  ಹಿಂತಿರುಗಿ ret;
	}
      ಹಿಂತಿರುಗಿ ಅಭಿವ್ಯಕ್ತಿ;
    }

  ಆದರೆ (IS_ಅಭಿವ್ಯಕ್ತಿ_ಸಂಕೇತ_CLASS (ಬಗೆ))
    old_range = ಅಭಿವ್ಯಕ್ತಿ_LOCATION_RANGE (ಅಭಿವ್ಯಕ್ತಿ);

  /* Operands of variable-length expressions (function calls) have
     already been folded, as have __builtin_* function calls, and such
     expressions cannot occur in constant expressions.  */
  ಆದರೆ (ಬಗೆ == tcc_vl_exp)
    {
      *maybe_const_operands = ಸುಳ್ಳು;
      ret = fold (ಅಭಿವ್ಯಕ್ತಿ);
      ಹೋಗು ಹೊರಹೋಗು;
    }

  ಆದರೆ (ಸಂಕೇತ_2 == C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ)
    {
      ವೃಕ್ಷ pre = C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_PRE (ಅಭಿವ್ಯಕ್ತಿ);
      ವೃಕ್ಷ inner = C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_ಅಭಿವ್ಯಕ್ತಿ (ಅಭಿವ್ಯಕ್ತಿ);
      ಆದರೆ (C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_NON_CONST (ಅಭಿವ್ಯಕ್ತಿ))
	*maybe_const_operands = ಸುಳ್ಳು;
      ಆದರೆ (C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_INT_OPERANDS (ಅಭಿವ್ಯಕ್ತಿ))
	{
	  *maybe_const_itself = ಸುಳ್ಳು;
	  inner = c_fully_fold_ಆಂತರಿಕ (inner, ಒಳ_init, maybe_const_operands,
					 maybe_const_itself, ನಿಜ, lval);
	}
      ಆದರೆ (pre && !ಒಳ_init)
	ret = build2 (COMPOUND_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ), pre, inner);
      ಇಲ್ಲದಿದ್ದರೆ
	ret = inner;
      ಹೋಗು ಹೊರಹೋಗು;
    }

  /* Assignment, increment, decrement, function call and comma
     operators, and statement expressions, cannot occur in constant
     expressions if evaluated / outside of sizeof.  (Function calls
     were handled above, though VA_ARG_EXPR is treated like a function
     call here, and statement expressions are handled through
     C_MAYBE_CONST_EXPR to avoid folding inside them.)  */
  ಆಯ್ಕೆ (ಸಂಕೇತ_2)
    {
    ಸ್ಥಿತಿ MODIFY_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ PREDECREMENT_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ PREINCREMENT_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ POSTDECREMENT_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ POSTINCREMENT_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ COMPOUND_ಅಭಿವ್ಯಕ್ತಿ:
      *maybe_const_operands = ಸುಳ್ಳು;
      ನಿಲ್ಲಿಸು;

    ಸ್ಥಿತಿ VA_ARG_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ ಗುರಿ_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ BIND_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ OBJ_TYPE_REF:
      *maybe_const_operands = ಸುಳ್ಳು;
      ret = fold (ಅಭಿವ್ಯಕ್ತಿ);
      ಹೋಗು ಹೊರಹೋಗು;

    ಪೂರ್ವನಿಯೋಜಿತ:
      ನಿಲ್ಲಿಸು;
    }

  /* Fold individual tree codes as appropriate.  */
  ಆಯ್ಕೆ (ಸಂಕೇತ_2)
    {
    ಸ್ಥಿತಿ COMPOUND_LITERAL_ಅಭಿವ್ಯಕ್ತಿ:
      /* Any non-constancy will have been marked in a containing
	 C_MAYBE_CONST_EXPR; there is no more folding to do here.  */
      ಹೋಗು ಹೊರಹೋಗು;

    ಸ್ಥಿತಿ COMPONENT_REF:
      orig_op0 = op0 = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಅಭಿವ್ಯಕ್ತಿ, 0);
      op1 = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಅಭಿವ್ಯಕ್ತಿ, 1);
      op2 = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಅಭಿವ್ಯಕ್ತಿ, 2);
      op0 = c_fully_fold_ಆಂತರಿಕ (op0, ಒಳ_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, lval);
      STRIP_TYPE_NOPS (op0);
      ಆದರೆ (op0 != orig_op0)
	ret = build3 (COMPONENT_REF, ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ), op0, op1, op2);
      ಆದರೆ (ret != ಅಭಿವ್ಯಕ್ತಿ)
	{
	  ವೃಕ್ಷ_READONLY (ret) = ವೃಕ್ಷ_READONLY (ಅಭಿವ್ಯಕ್ತಿ);
	  ವೃಕ್ಷ_THIS_VOLATILE (ret) = ವೃಕ್ಷ_THIS_VOLATILE (ಅಭಿವ್ಯಕ್ತಿ);
	}
      ಆದರೆ (!lval)
	ret = fold (ret);
      ಹೋಗು ಹೊರಹೋಗು;

    ಸ್ಥಿತಿ ARRAY_REF:
      orig_op0 = op0 = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಅಭಿವ್ಯಕ್ತಿ, 0);
      orig_op1 = op1 = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಅಭಿವ್ಯಕ್ತಿ, 1);
      op2 = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಅಭಿವ್ಯಕ್ತಿ, 2);
      op3 = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಅಭಿವ್ಯಕ್ತಿ, 3);
      op0 = c_fully_fold_ಆಂತರಿಕ (op0, ಒಳ_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, lval);
      STRIP_TYPE_NOPS (op0);
      op1 = c_fully_fold_ಆಂತರಿಕ (op1, ಒಳ_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, ಸುಳ್ಳು);
      STRIP_TYPE_NOPS (op1);
      /* Fold "foo"[2] in initializers.  */
      ಆದರೆ (!lval && ಒಳ_init)
	{
	  ret = c_fold_array_ref (ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ), op0, op1);
	  ಆದರೆ (ret)
	    ಹೋಗು ಹೊರಹೋಗು;
	  ret = ಅಭಿವ್ಯಕ್ತಿ;
	}
      ಆದರೆ (op0 != orig_op0 || op1 != orig_op1)
	ret = build4 (ARRAY_REF, ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ), op0, op1, op2, op3);
      ಆದರೆ (ret != ಅಭಿವ್ಯಕ್ತಿ)
	{
	  ವೃಕ್ಷ_READONLY (ret) = ವೃಕ್ಷ_READONLY (ಅಭಿವ್ಯಕ್ತಿ);
	  ವೃಕ್ಷ_SIDE_EFFECTS (ret) = ವೃಕ್ಷ_SIDE_EFFECTS (ಅಭಿವ್ಯಕ್ತಿ);
	  ವೃಕ್ಷ_THIS_VOLATILE (ret) = ವೃಕ್ಷ_THIS_VOLATILE (ಅಭಿವ್ಯಕ್ತಿ);
	}
      ಆದರೆ (!lval)
	ret = fold (ret);
      ಹೋಗು ಹೊರಹೋಗು;

    ಸ್ಥಿತಿ MODIFY_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ PREDECREMENT_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ PREINCREMENT_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ POSTDECREMENT_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ POSTINCREMENT_ಅಭಿವ್ಯಕ್ತಿ:
      op0_lval = ನಿಜ;
      /* FALLTHRU */
    ಸ್ಥಿತಿ COMPOUND_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ PLUS_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ MINUS_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ MULT_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ ಸೂಚಕ_PLUS_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ ಸೂಚಕ_DIFF_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ TRUNC_DIV_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ CEIL_DIV_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ FLOOR_DIV_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ TRUNC_MOD_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ RDIV_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ EXACT_DIV_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ LSHIFT_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ RSHIFT_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ LROTATE_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ RROTATE_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ ಬಿಟ್_IOR_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ ಬಿಟ್_XOR_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ ಬಿಟ್_AND_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ LT_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ LE_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ GT_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ GE_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ EQ_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ NE_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ COMPLEX_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ TRUTH_AND_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ TRUTH_OR_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ TRUTH_XOR_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ UNORDERED_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ ORDERED_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ UNLT_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ UNLE_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ UNGT_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ UNGE_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ UNEQ_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ MEM_REF:
      /* Binary operations evaluating both arguments (increment and
	 decrement are binary internally in GCC).  */
      orig_op0 = op0 = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಅಭಿವ್ಯಕ್ತಿ, 0);
      orig_op1 = op1 = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಅಭಿವ್ಯಕ್ತಿ, 1);
      op0 = c_fully_fold_ಆಂತರಿಕ (op0, ಒಳ_init, maybe_const_operands,
				   maybe_const_itself, for_int_const,
				   op0_lval);
      STRIP_TYPE_NOPS (op0);
      /* The RHS of a MODIFY_EXPR was fully folded when building that
	 expression for the sake of conversion warnings.  */
      ಆದರೆ (ಸಂಕೇತ_2 != MODIFY_ಅಭಿವ್ಯಕ್ತಿ)
	op1 = c_fully_fold_ಆಂತರಿಕ (op1, ಒಳ_init, maybe_const_operands,
				     maybe_const_itself, for_int_const, ಸುಳ್ಳು);
      STRIP_TYPE_NOPS (op1);

      ಆದರೆ (for_int_const && (ವೃಕ್ಷ_ಸಂಕೇತ (op0) != INTEGER_CST
			    || ವೃಕ್ಷ_ಸಂಕೇತ (op1) != INTEGER_CST))
	ಹೋಗು ಹೊರಹೋಗು;

      ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ_CLASS (ಸಂಕೇತ_2) == tcc_comparison
	  && ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (op0)) == NULLPTR_TYPE
	  && ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (op1)) == NULLPTR_TYPE)
	{
	  ಆಯ್ಕೆ (ಸಂಕೇತ_2)
	    {
	    ಸ್ಥಿತಿ EQ_ಅಭಿವ್ಯಕ್ತಿ:
	      ret = constant_boolean_ಗಂಟು (ನಿಜ, ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ));
	      ನಿಲ್ಲಿಸು;
	    ಸ್ಥಿತಿ NE_ಅಭಿವ್ಯಕ್ತಿ:
	      ret = constant_boolean_ಗಂಟು (ಸುಳ್ಳು, ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ));
	      ನಿಲ್ಲಿಸು;
	    ಪೂರ್ವನಿಯೋಜಿತ:
	      gcc_unreachable ();
	    }
	  ret = omit_two_operands_loc (loc, ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ), ret,
				       op0, op1);
	}
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (op0 != orig_op0 || op1 != orig_op1 || ಒಳ_init)
	ret = ಒಳ_init
	  ? fold_build2_initializer_loc (loc, ಸಂಕೇತ_2, ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ), op0, op1)
	  : fold_build2_loc (loc, ಸಂಕೇತ_2, ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ), op0, op1);
      ಇಲ್ಲದಿದ್ದರೆ
	ret = fold (ಅಭಿವ್ಯಕ್ತಿ);
      ಆದರೆ (ವೃಕ್ಷ_ಅತಿಪ್ರವಾಹ_P (ret)
	  && !ವೃಕ್ಷ_ಅತಿಪ್ರವಾಹ_P (op0)
	  && !(ದ್ವಿಮಾನ_CLASS_P (op0) && ವೃಕ್ಷ_ಅತಿಪ್ರವಾಹ_P (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (op0, 1)))
	  && !ವೃಕ್ಷ_ಅತಿಪ್ರವಾಹ_P (op1))
	ಅತಿಪ್ರವಾಹ_warning (ಅಭಿವ್ಯಕ್ತಿ_LOC_OR_LOC (ಅಭಿವ್ಯಕ್ತಿ, ಒಳಹರಿವು_location), ret, ಅಭಿವ್ಯಕ್ತಿ);
      ಆದರೆ (ಸಂಕೇತ_2 == LSHIFT_ಅಭಿವ್ಯಕ್ತಿ
	  && ವೃಕ್ಷ_ಸಂಕೇತ (orig_op0) != INTEGER_CST
	  && (ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (orig_op0)) == INTEGER_TYPE
	      || ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (orig_op0)) == BITINT_TYPE)
	  && ವೃಕ್ಷ_ಸಂಕೇತ (op0) == INTEGER_CST
	  && c_inhibit_evaluation_warnings == 0
	  && !TYPE_ಅತಿಪ್ರವಾಹ_WRAPS (ವೃಕ್ಷ_TYPE (orig_op0))
	  && ವೃಕ್ಷ_int_cst_sgn (op0) < 0)
	warning_at (loc, OPT_Wshift_negative_ಮೌಲ್ಯ,
		    "left shift of negative value");
      ಆದರೆ ((ಸಂಕೇತ_2 == LSHIFT_ಅಭಿವ್ಯಕ್ತಿ
	   || ಸಂಕೇತ_2 == RSHIFT_ಅಭಿವ್ಯಕ್ತಿ
	   || ಸಂಕೇತ_2 == LROTATE_ಅಭಿವ್ಯಕ್ತಿ
	   || ಸಂಕೇತ_2 == RROTATE_ಅಭಿವ್ಯಕ್ತಿ)
	  && ವೃಕ್ಷ_ಸಂಕೇತ (orig_op1) != INTEGER_CST
	  && ವೃಕ್ಷ_ಸಂಕೇತ (op1) == INTEGER_CST
	  && ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (orig_op1)) == INTEGER_TYPE
	  && c_inhibit_evaluation_warnings == 0)
	{
	  ಆದರೆ (ವೃಕ್ಷ_int_cst_sgn (op1) < 0)
	    warning_at (loc, OPT_Wshift_ಎಣಿಕೆ_negative,
			(ಸಂಕೇತ_2 == LSHIFT_ಅಭಿವ್ಯಕ್ತಿ
			 ? G_("left shift count is negative")
			 : G_("right shift count is negative")));
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ ((ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (orig_op0)) == INTEGER_TYPE
		    || ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (orig_op0)) == BITINT_TYPE
		    || ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (orig_op0)) == FIXED_ಬಿಂದು_TYPE)
		   && compare_ವೃಕ್ಷ_int (op1,
					TYPE_PRECISION (ವೃಕ್ಷ_TYPE (orig_op0)))
		      >= 0
		   && !warning_suppressed_p (ಅಭಿವ್ಯಕ್ತಿ, OPT_Wshift_ಎಣಿಕೆ_ಅತಿಪ್ರವಾಹ))
	    warning_at (loc, OPT_Wshift_ಎಣಿಕೆ_ಅತಿಪ್ರವಾಹ,
			(ಸಂಕೇತ_2 == LSHIFT_ಅಭಿವ್ಯಕ್ತಿ
			 ? G_("left shift count >= width of type")
			 : G_("right shift count >= width of type")));
	  ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (orig_op0)) == ಸದಿಶ_TYPE
		   && compare_ವೃಕ್ಷ_int (op1,
					TYPE_PRECISION (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (orig_op0))))
		      >= 0)
	    warning_at (loc, OPT_Wshift_ಎಣಿಕೆ_ಅತಿಪ್ರವಾಹ,
			ಸಂಕೇತ_2 == LSHIFT_ಅಭಿವ್ಯಕ್ತಿ
			? G_("left shift count >= width of vector element")
			: G_("right shift count >= width of vector element"));
	}
      ಆದರೆ (ಸಂಕೇತ_2 == LSHIFT_ಅಭಿವ್ಯಕ್ತಿ
	  /* If either OP0 has been folded to INTEGER_CST...  */
	  && ((ವೃಕ್ಷ_ಸಂಕೇತ (orig_op0) != INTEGER_CST
	       && (ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (orig_op0)) == INTEGER_TYPE
		   || ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (orig_op0)) == BITINT_TYPE)
	       && ವೃಕ್ಷ_ಸಂಕೇತ (op0) == INTEGER_CST)
	      /* ...or if OP1 has been folded to INTEGER_CST...  */
	      || (ವೃಕ್ಷ_ಸಂಕೇತ (orig_op1) != INTEGER_CST
		  && (ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (orig_op1)) == INTEGER_TYPE
		      || ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (orig_op1)) == BITINT_TYPE)
		  && ವೃಕ್ಷ_ಸಂಕೇತ (op1) == INTEGER_CST))
	  && c_inhibit_evaluation_warnings == 0)
	/* ...then maybe we can detect an overflow.  */
	maybe_warn_ಸರಿಸು_ಅತಿಪ್ರವಾಹ (loc, op0, op1);
      ಆದರೆ ((ಸಂಕೇತ_2 == TRUNC_DIV_ಅಭಿವ್ಯಕ್ತಿ
	   || ಸಂಕೇತ_2 == CEIL_DIV_ಅಭಿವ್ಯಕ್ತಿ
	   || ಸಂಕೇತ_2 == FLOOR_DIV_ಅಭಿವ್ಯಕ್ತಿ
	   || ಸಂಕೇತ_2 == EXACT_DIV_ಅಭಿವ್ಯಕ್ತಿ
	   || ಸಂಕೇತ_2 == TRUNC_MOD_ಅಭಿವ್ಯಕ್ತಿ)
	  && ವೃಕ್ಷ_ಸಂಕೇತ (orig_op1) != INTEGER_CST
	  && ವೃಕ್ಷ_ಸಂಕೇತ (op1) == INTEGER_CST
	  && (ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (orig_op0)) == INTEGER_TYPE
	      || ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (orig_op0)) == BITINT_TYPE
	      || ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (orig_op0)) == FIXED_ಬಿಂದು_TYPE)
	  && (ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (orig_op1)) == INTEGER_TYPE
	      || ವೃಕ್ಷ_ಸಂಕೇತ (ವೃಕ್ಷ_TYPE (orig_op1)) == BITINT_TYPE))
	warn_for_div_by_zero (loc, op1);
      ಆದರೆ (ಸಂಕೇತ_2 == MEM_REF
	  && ret != ಅಭಿವ್ಯಕ್ತಿ
	  && ವೃಕ್ಷ_ಸಂಕೇತ (ret) == MEM_REF)
	{
	  ವೃಕ್ಷ_READONLY (ret) = ವೃಕ್ಷ_READONLY (ಅಭಿವ್ಯಕ್ತಿ);
	  ವೃಕ್ಷ_SIDE_EFFECTS (ret) = ವೃಕ್ಷ_SIDE_EFFECTS (ಅಭಿವ್ಯಕ್ತಿ);
	  ವೃಕ್ಷ_THIS_VOLATILE (ret) = ವೃಕ್ಷ_THIS_VOLATILE (ಅಭಿವ್ಯಕ್ತಿ);
	}
      ಹೋಗು ಹೊರಹೋಗು;

    ಸ್ಥಿತಿ ADDR_ಅಭಿವ್ಯಕ್ತಿ:
      op0_lval = ನಿಜ;
      ಹೋಗು unary;
    ಸ್ಥಿತಿ REALPART_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ IMAGPART_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ VIEW_CONVERT_ಅಭಿವ್ಯಕ್ತಿ:
      op0_lval = lval;
      /* FALLTHRU */
    ಸ್ಥಿತಿ ಪರೋಕ್ಷ_REF:
    ಸ್ಥಿತಿ FIX_TRUNC_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ FLOAT_ಅಭಿವ್ಯಕ್ತಿ:
    CASE_CONVERT:
    ಸ್ಥಿತಿ ADDR_SPACE_CONVERT_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ NON_LVALUE_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ NEGATE_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ ಬಿಟ್_NOT_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ TRUTH_NOT_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ CONJ_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ PAREN_ಅಭಿವ್ಯಕ್ತಿ:
    unary:
      /* Unary operations.  */
      orig_op0 = op0 = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಅಭಿವ್ಯಕ್ತಿ, 0);
      op0 = c_fully_fold_ಆಂತರಿಕ (op0, ಒಳ_init, maybe_const_operands,
				   maybe_const_itself, for_int_const,
				   op0_lval);
      STRIP_TYPE_NOPS (op0);

      ಆದರೆ (for_int_const && ವೃಕ್ಷ_ಸಂಕೇತ (op0) != INTEGER_CST)
	ಹೋಗು ಹೊರಹೋಗು;

      /* ??? Cope with user tricks that amount to offsetof.  The middle-end is
	 not prepared to deal with them if they occur in initializers.  */
      ಆದರೆ (op0 != orig_op0
	  && ಸಂಕೇತ_2 == ADDR_ಅಭಿವ್ಯಕ್ತಿ
	  && (op1 = get_ತಳ_ವಿಳಾಸ (op0)) != NULL_ವೃಕ್ಷ
	  && ಪರೋಕ್ಷ_REF_P (op1)
	  && ವೃಕ್ಷ_CONSTANT (ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (op1, 0)))
	ret = fold_offsetof (op0, ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ));
      ಇಲ್ಲದಿದ್ದರೆ ಆದರೆ (op0 != orig_op0 || ಒಳ_init)
	ret = ಒಳ_init
	  ? fold_build1_initializer_loc (loc, ಸಂಕೇತ_2, ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ), op0)
	  : fold_build1_loc (loc, ಸಂಕೇತ_2, ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ), op0);
      ಇಲ್ಲದಿದ್ದರೆ
	ret = fold (ಅಭಿವ್ಯಕ್ತಿ);
      ಆದರೆ (ಸಂಕೇತ_2 == ಪರೋಕ್ಷ_REF
	  && ret != ಅಭಿವ್ಯಕ್ತಿ
	  && ಪರೋಕ್ಷ_REF_P (ret))
	{
	  ವೃಕ್ಷ_READONLY (ret) = ವೃಕ್ಷ_READONLY (ಅಭಿವ್ಯಕ್ತಿ);
	  ವೃಕ್ಷ_SIDE_EFFECTS (ret) = ವೃಕ್ಷ_SIDE_EFFECTS (ಅಭಿವ್ಯಕ್ತಿ);
	  ವೃಕ್ಷ_THIS_VOLATILE (ret) = ವೃಕ್ಷ_THIS_VOLATILE (ಅಭಿವ್ಯಕ್ತಿ);
	}
      ಆಯ್ಕೆ (ಸಂಕೇತ_2)
	{
	ಸ್ಥಿತಿ FIX_TRUNC_ಅಭಿವ್ಯಕ್ತಿ:
	ಸ್ಥಿತಿ FLOAT_ಅಭಿವ್ಯಕ್ತಿ:
	CASE_CONVERT:
	  /* Don't warn about explicit conversions.  We will already
	     have warned about suspect implicit conversions.  */
	  ನಿಲ್ಲಿಸು;

	ಪೂರ್ವನಿಯೋಜಿತ:
	  ಆದರೆ (ವೃಕ್ಷ_ಅತಿಪ್ರವಾಹ_P (ret) && !ವೃಕ್ಷ_ಅತಿಪ್ರವಾಹ_P (op0))
	    ಅತಿಪ್ರವಾಹ_warning (ಅಭಿವ್ಯಕ್ತಿ_LOCATION (ಅಭಿವ್ಯಕ್ತಿ), ret, op0);
	  ನಿಲ್ಲಿಸು;
	}
      ಹೋಗು ಹೊರಹೋಗು;

    ಸ್ಥಿತಿ TRUTH_ANDIF_ಅಭಿವ್ಯಕ್ತಿ:
    ಸ್ಥಿತಿ TRUTH_ORIF_ಅಭಿವ್ಯಕ್ತಿ:
      /* Binary operations not necessarily evaluating both
	 arguments.  */
      orig_op0 = op0 = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಅಭಿವ್ಯಕ್ತಿ, 0);
      orig_op1 = op1 = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಅಭಿವ್ಯಕ್ತಿ, 1);
      op0 = c_fully_fold_ಆಂತರಿಕ (op0, ಒಳ_init, &op0_const, &op0_const_self,
				   for_int_const, ಸುಳ್ಳು);
      STRIP_TYPE_NOPS (op0);

      ಬಳಸದ_p = (op0 == (ಸಂಕೇತ_2 == TRUTH_ANDIF_ಅಭಿವ್ಯಕ್ತಿ
			  ? truthvalue_false_ಗಂಟು
			  : truthvalue_true_ಗಂಟು));
      c_disable_warnings (ಬಳಸದ_p);
      op1 = c_fully_fold_ಆಂತರಿಕ (op1, ಒಳ_init, &op1_const, &op1_const_self,
				   for_int_const, ಸುಳ್ಳು);
      STRIP_TYPE_NOPS (op1);
      c_enable_warnings (ಬಳಸದ_p);

      ಆದರೆ (for_int_const
	  && (ವೃಕ್ಷ_ಸಂಕೇತ (op0) != INTEGER_CST
	      /* Require OP1 be an INTEGER_CST only if it's evaluated.  */
	      || (!ಬಳಸದ_p && ವೃಕ್ಷ_ಸಂಕೇತ (op1) != INTEGER_CST)))
	ಹೋಗು ಹೊರಹೋಗು;

      ಆದರೆ (op0 != orig_op0 || op1 != orig_op1 || ಒಳ_init)
	ret = ಒಳ_init
	  ? fold_build2_initializer_loc (loc, ಸಂಕೇತ_2, ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ), op0, op1)
	  : fold_build2_loc (loc, ಸಂಕೇತ_2, ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ), op0, op1);
      ಇಲ್ಲದಿದ್ದರೆ
	ret = fold (ಅಭಿವ್ಯಕ್ತಿ);
      *maybe_const_operands &= op0_const;
      *maybe_const_itself &= op0_const_self;
      ಆದರೆ (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && (ಸಂಕೇತ_2 == TRUTH_ANDIF_ಅಭಿವ್ಯಕ್ತಿ
		? op0 == truthvalue_false_ಗಂಟು
		: op0 == truthvalue_true_ಗಂಟು)))
	*maybe_const_operands &= op1_const;
      ಆದರೆ (!(op0_const
	    && op0_const_self
	    && (ಸಂಕೇತ_2 == TRUTH_ANDIF_ಅಭಿವ್ಯಕ್ತಿ
		? op0 == truthvalue_false_ಗಂಟು
		: op0 == truthvalue_true_ಗಂಟು)))
	*maybe_const_itself &= op1_const_self;
      ಹೋಗು ಹೊರಹೋಗು;

    ಸ್ಥಿತಿ COND_ಅಭಿವ್ಯಕ್ತಿ:
      orig_op0 = op0 = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಅಭಿವ್ಯಕ್ತಿ, 0);
      orig_op1 = op1 = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಅಭಿವ್ಯಕ್ತಿ, 1);
      orig_op2 = op2 = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಅಭಿವ್ಯಕ್ತಿ, 2);
      op0 = c_fully_fold_ಆಂತರಿಕ (op0, ಒಳ_init, &op0_const, &op0_const_self,
				   for_int_const, ಸುಳ್ಳು);

      STRIP_TYPE_NOPS (op0);
      c_disable_warnings (op0 == truthvalue_false_ಗಂಟು);
      op1 = c_fully_fold_ಆಂತರಿಕ (op1, ಒಳ_init, &op1_const, &op1_const_self,
				   for_int_const, ಸುಳ್ಳು);
      STRIP_TYPE_NOPS (op1);
      c_enable_warnings (op0 == truthvalue_false_ಗಂಟು);

      c_disable_warnings (op0 == truthvalue_true_ಗಂಟು);
      op2 = c_fully_fold_ಆಂತರಿಕ (op2, ಒಳ_init, &op2_const, &op2_const_self,
				   for_int_const, ಸುಳ್ಳು);
      STRIP_TYPE_NOPS (op2);
      c_enable_warnings (op0 == truthvalue_true_ಗಂಟು);

      ಆದರೆ (for_int_const
	  && (ವೃಕ್ಷ_ಸಂಕೇತ (op0) != INTEGER_CST
	      /* Only the evaluated operand must be an INTEGER_CST.  */
	      || (op0 == truthvalue_true_ಗಂಟು
		  ? ವೃಕ್ಷ_ಸಂಕೇತ (op1) != INTEGER_CST
		  : ವೃಕ್ಷ_ಸಂಕೇತ (op2) != INTEGER_CST)))
	ಹೋಗು ಹೊರಹೋಗು;

      ಆದರೆ (op0 != orig_op0 || op1 != orig_op1 || op2 != orig_op2)
	ret = fold_build3_loc (loc, ಸಂಕೇತ_2, ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ), op0, op1, op2);
      ಇಲ್ಲದಿದ್ದರೆ
	ret = fold (ಅಭಿವ್ಯಕ್ತಿ);
      *maybe_const_operands &= op0_const;
      *maybe_const_itself &= op0_const_self;
      ಆದರೆ (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && op0 == truthvalue_false_ಗಂಟು))
	*maybe_const_operands &= op1_const;
      ಆದರೆ (!(op0_const
	    && op0_const_self
	    && op0 == truthvalue_false_ಗಂಟು))
	*maybe_const_itself &= op1_const_self;
      ಆದರೆ (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && op0 == truthvalue_true_ಗಂಟು))
	*maybe_const_operands &= op2_const;
      ಆದರೆ (!(op0_const
	    && op0_const_self
	    && op0 == truthvalue_true_ಗಂಟು))
	*maybe_const_itself &= op2_const_self;
      ಹೋಗು ಹೊರಹೋಗು;

    ಸ್ಥಿತಿ VEC_COND_ಅಭಿವ್ಯಕ್ತಿ:
      orig_op0 = op0 = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಅಭಿವ್ಯಕ್ತಿ, 0);
      orig_op1 = op1 = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಅಭಿವ್ಯಕ್ತಿ, 1);
      orig_op2 = op2 = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಅಭಿವ್ಯಕ್ತಿ, 2);
      op0 = c_fully_fold_ಆಂತರಿಕ (op0, ಒಳ_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, ಸುಳ್ಳು);
      STRIP_TYPE_NOPS (op0);
      op1 = c_fully_fold_ಆಂತರಿಕ (op1, ಒಳ_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, ಸುಳ್ಳು);
      STRIP_TYPE_NOPS (op1);
      op2 = c_fully_fold_ಆಂತರಿಕ (op2, ಒಳ_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, ಸುಳ್ಳು);
      STRIP_TYPE_NOPS (op2);

      ಆದರೆ (op0 != orig_op0 || op1 != orig_op1 || op2 != orig_op2)
	ret = fold_build3_loc (loc, ಸಂಕೇತ_2, ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ), op0, op1, op2);
      ಇಲ್ಲದಿದ್ದರೆ
	ret = fold (ಅಭಿವ್ಯಕ್ತಿ);
      ಹೋಗು ಹೊರಹೋಗು;

    ಸ್ಥಿತಿ EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ:
      /* Each case where an operand with excess precision may be
	 encountered must remove the EXCESS_PRECISION_EXPR around
	 inner operands and possibly put one around the whole
	 expression or possibly convert to the semantic type (which
	 c_fully_fold does); we cannot tell at this stage which is
	 appropriate in any particular case.  */
      gcc_unreachable ();

    ಸ್ಥಿತಿ SAVE_ಅಭಿವ್ಯಕ್ತಿ:
      /* Make sure to fold the contents of a SAVE_EXPR exactly once.  */
      op0 = ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಅಭಿವ್ಯಕ್ತಿ, 0);
      ಆದರೆ (!SAVE_ಅಭಿವ್ಯಕ್ತಿ_FOLDED_P (ಅಭಿವ್ಯಕ್ತಿ))
	{
	  op0 = c_fully_fold_ಆಂತರಿಕ (op0, ಒಳ_init, maybe_const_operands,
				       maybe_const_itself, for_int_const,
				       ಸುಳ್ಳು);
	  ವೃಕ್ಷ_ಕಾರ್ಯಾಂಶ (ಅಭಿವ್ಯಕ್ತಿ, 0) = op0;
	  SAVE_ಅಭಿವ್ಯಕ್ತಿ_FOLDED_P (ಅಭಿವ್ಯಕ್ತಿ) = ನಿಜ;
	}
      /* Return the SAVE_EXPR operand if it is invariant.  */
      ಆದರೆ (ವೃಕ್ಷ_invariant_p (op0))
	ret = op0;
      ಹೋಗು ಹೊರಹೋಗು;

    ಪೂರ್ವನಿಯೋಜಿತ:
      /* Various codes may appear through folding built-in functions
	 and their arguments.  */
      ಹೋಗು ಹೊರಹೋಗು;
    }

 ಹೊರಹೋಗು:
  /* Some folding may introduce NON_LVALUE_EXPRs; all lvalue checks
     have been done by this point, so remove them again.  */
  nowarning |= warning_suppressed_p (ret, OPT_Woverflow);
  STRIP_TYPE_NOPS (ret);
  ಆದರೆ (nowarning && !warning_suppressed_p (ret, OPT_Woverflow))
    {
      ಆದರೆ (!CAN_HAVE_LOCATION_P (ret))
	ret = build1 (NOP_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (ret), ret);
      suppress_warning (ret, OPT_Woverflow);
    }
  ಆದರೆ (ret != ಅಭಿವ್ಯಕ್ತಿ)
    {
      protected_ಗಣ_ಅಭಿವ್ಯಕ್ತಿ_location (ret, loc);
      ಆದರೆ (IS_ಅಭಿವ್ಯಕ್ತಿ_ಸಂಕೇತ_CLASS (ಬಗೆ))
	ಗಣ_ಮೂಲ_range (ret, old_range.m_ಆರಂಭ, old_range.m_ಮುಕ್ತಾಯ);
    }
  ಹಿಂತಿರುಗಿ ret;
}

/* Fold X for consideration by one of the warning functions when checking
   whether an expression has a constant value.  */

ವೃಕ್ಷ
fold_for_warn (ವೃಕ್ಷ x)
{
  /* The C front-end has already folded X appropriately.  */
  ಹಿಂತಿರುಗಿ x;
}
