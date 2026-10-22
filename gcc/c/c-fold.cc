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

#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "system.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "coretypes.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "target.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "function.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "bitmap.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "c-tree.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "intl.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "gimplify.h"

ਸਥਿਰ ਰੁੱਖ c_fully_fold_ਅੰਦਰੂਨੀ (ਰੁੱਖ ਵਿਅੰਜਕ, ਤਾਰਕਿਕ, ਤਾਰਕਿਕ *, ਤਾਰਕਿਕ *, ਤਾਰਕਿਕ,
				   ਤਾਰਕਿਕ);

/* If DISABLE is true, stop issuing warnings.  This is used when
   parsing code that we know will not be executed.  This function may
   be called multiple times, and works as a stack.  */

ਸਥਿਰ ਖਾਲੀ
c_disable_warnings (ਤਾਰਕਿਕ disable)
{
  ਜੇ (disable)
    {
      ++c_inhibit_evaluation_warnings;
    }
}

/* If ENABLE is true, re-enable issuing warnings.  */

ਸਥਿਰ ਖਾਲੀ
c_enable_warnings (ਤਾਰਕਿਕ enable)
{
  ਜੇ (enable)
    {
      --c_inhibit_evaluation_warnings;
    }
}

/* Try to fold ARRAY_REF ary[index] if possible and not handled by
   normal fold, return NULL_TREE otherwise.  */

ਸਥਿਰ ਰੁੱਖ
c_fold_array_ref (ਰੁੱਖ type, ਰੁੱਖ ary, ਰੁੱਖ ਸੂਚਕਾਂਕ)
{
  ਜੇ (ਰੁੱਖ_ਕੋਡ (ary) != STRING_CST
      || ਰੁੱਖ_ਕੋਡ (ਸੂਚਕਾਂਕ) != INTEGER_CST
      || ਰੁੱਖ_ਉਛਾਲ (ਸੂਚਕਾਂਕ)
      || ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (ary)) != ARRAY_TYPE
      || !ਰੁੱਖ_ਸਮਾਉਂਦਾ_uhwi_p (ਸੂਚਕਾਂਕ))
    ਵਾਪਸ NULL_ਰੁੱਖ;

  ਰੁੱਖ elem_type = ਰੁੱਖ_TYPE (ਰੁੱਖ_TYPE (ary));
  ਬਿਨਾਨਿਸ਼ਾਨੀ elem_nchars = (TYPE_PRECISION (elem_type)
			  / TYPE_PRECISION (char_type_ਗੰਢ));
  ਬਿਨਾਨਿਸ਼ਾਨੀ len = (ਬਿਨਾਨਿਸ਼ਾਨੀ) ਰੁੱਖ_STRING_ਲੰਮਾਈ (ary) / elem_nchars;
  ਰੁੱਖ nelts_minus_one = array_type_nelts_minus_one (ਰੁੱਖ_TYPE (ary));
  ਤਾਰਕਿਕ dummy1 = ਸੱਚ, dummy2 = ਸੱਚ;
  nelts_minus_one = c_fully_fold_ਅੰਦਰੂਨੀ (nelts_minus_one, ਸੱਚ, &dummy1,
					   &dummy2, ਝੂਠ, ਝੂਠ);
  ਬਿਨਾਨਿਸ਼ਾਨੀ HOST_WIDE_INT i = ਰੁੱਖ_ਮੰਜ਼ਿਲ_uhwi (ਸੂਚਕਾਂਕ);
  ਜੇ (!ਰੁੱਖ_int_cst_le (ਸੂਚਕਾਂਕ, nelts_minus_one)
      || i >= len
      || i + elem_nchars > len)
    ਵਾਪਸ NULL_ਰੁੱਖ;

  ਜੇ (elem_nchars == 1)
    ਵਾਪਸ build_int_cst (type, ਰੁੱਖ_STRING_ਸੂਚਕ (ary)[i]);

  ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *ptr
    = ((ਅਚਲ ਬਿਨਾਨਿਸ਼ਾਨੀ ਅੱਖਰ *)ਰੁੱਖ_STRING_ਸੂਚਕ (ary) + i * elem_nchars);
  ਵਾਪਸ native_interpret_ਵਿਅੰਜਕ (type, ptr, elem_nchars);
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

ਰੁੱਖ
c_fully_fold (ਰੁੱਖ ਵਿਅੰਜਕ, ਤਾਰਕਿਕ ਵਿੱਚ_init, ਤਾਰਕਿਕ *maybe_const, ਤਾਰਕਿਕ lval)
{
  ਰੁੱਖ ret;
  ਰੁੱਖ eptype = NULL_ਰੁੱਖ;
  ਤਾਰਕਿਕ dummy = ਸੱਚ;
  ਤਾਰਕਿਕ maybe_const_itself = ਸੱਚ;
  location_t loc = ਵਿਅੰਜਕ_LOCATION (ਵਿਅੰਜਕ);

  ਜੇ (!maybe_const)
    maybe_const = &dummy;
  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਵਿਅੰਜਕ) == EXCESS_PRECISION_ਵਿਅੰਜਕ)
    {
      eptype = ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ);
      ਵਿਅੰਜਕ = ਰੁੱਖ_ਸੰਕਾਰਜ (ਵਿਅੰਜਕ, 0);
    }
  ret = c_fully_fold_ਅੰਦਰੂਨੀ (ਵਿਅੰਜਕ, ਵਿੱਚ_init, maybe_const,
			       &maybe_const_itself, ਝੂਠ, lval);
  ਜੇ (eptype)
    ret = fold_convert_loc (loc, eptype, ret);
  *maybe_const &= maybe_const_itself;
  ਵਾਪਸ ret;
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

ਸਥਿਰ ਰੁੱਖ
c_fully_fold_ਅੰਦਰੂਨੀ (ਰੁੱਖ ਵਿਅੰਜਕ, ਤਾਰਕਿਕ ਵਿੱਚ_init, ਤਾਰਕਿਕ *maybe_const_operands,
		       ਤਾਰਕਿਕ *maybe_const_itself, ਤਾਰਕਿਕ for_int_const, ਤਾਰਕਿਕ lval)
{
  ਰੁੱਖ ret = ਵਿਅੰਜਕ;
  ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 ਕੋਡ = ਰੁੱਖ_ਕੋਡ (ਵਿਅੰਜਕ);
  ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_class ਕਿਸਮ = ਰੁੱਖ_ਕੋਡ_CLASS (ਕੋਡ);
  location_t loc = ਵਿਅੰਜਕ_LOCATION (ਵਿਅੰਜਕ);
  ਰੁੱਖ op0, op1, op2, op3;
  ਰੁੱਖ orig_op0, orig_op1, orig_op2;
  ਤਾਰਕਿਕ op0_const = ਸੱਚ, op1_const = ਸੱਚ, op2_const = ਸੱਚ;
  ਤਾਰਕਿਕ op0_const_self = ਸੱਚ, op1_const_self = ਸੱਚ, op2_const_self = ਸੱਚ;
  ਤਾਰਕਿਕ nowarning = warning_suppressed_p (ਵਿਅੰਜਕ, OPT_Woverflow);
  ਤਾਰਕਿਕ ਅਣਵਰਤਿਆ_p;
  ਤਾਰਕਿਕ op0_lval = ਝੂਠ;
  ਸਰੋਤ_range old_range;

  /* Constants, declarations, statements, errors, and anything else not
     counted as an expression cannot usefully be folded further at this
     point.  */
  ਜੇ (!IS_ਵਿਅੰਜਕ_ਕੋਡ_CLASS (ਕਿਸਮ) || ਕਿਸਮ == tcc_statement)
    {
      /* Except for variables which we can optimize to its initializer.  */
      ਜੇ (VAR_P (ਵਿਅੰਜਕ) && !lval && (optimize || ਵਿੱਚ_init))
	{
	  ਜੇ (ਵਿੱਚ_init)
	    ret = decl_constant_ਮੁੱਲ_1 (ਵਿਅੰਜਕ, ਸੱਚ);
	  ਨਹੀਂਤਾਂ
	    {
	      ret = decl_constant_ਮੁੱਲ (ਵਿਅੰਜਕ);
	      ਜੇ (ret != ਵਿਅੰਜਕ
		  && (TYPE_ਬਹੁਲਕ (ਰੁੱਖ_TYPE (ret)) == BLKmode
		      || ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (ret)) == ARRAY_TYPE))
		ਵਾਪਸ ਵਿਅੰਜਕ;
	    }
	  /* Avoid unwanted tree sharing between the initializer and current
	     function's body where the tree can be modified e.g. by the
	     gimplifier.  */
	  ਜੇ (ret != ਵਿਅੰਜਕ && ਰੁੱਖ_STATIC (ਵਿਅੰਜਕ))
	    ret = unshare_ਵਿਅੰਜਕ (ret);
	  ਵਾਪਸ ret;
	}
      ਵਾਪਸ ਵਿਅੰਜਕ;
    }

  ਜੇ (IS_ਵਿਅੰਜਕ_ਕੋਡ_CLASS (ਕਿਸਮ))
    old_range = ਵਿਅੰਜਕ_LOCATION_RANGE (ਵਿਅੰਜਕ);

  /* Operands of variable-length expressions (function calls) have
     already been folded, as have __builtin_* function calls, and such
     expressions cannot occur in constant expressions.  */
  ਜੇ (ਕਿਸਮ == tcc_vl_exp)
    {
      *maybe_const_operands = ਝੂਠ;
      ret = fold (ਵਿਅੰਜਕ);
      ਜਾਓ ਬਾਹਰਲਾ;
    }

  ਜੇ (ਕੋਡ == C_MAYBE_CONST_ਵਿਅੰਜਕ)
    {
      ਰੁੱਖ pre = C_MAYBE_CONST_ਵਿਅੰਜਕ_PRE (ਵਿਅੰਜਕ);
      ਰੁੱਖ inner = C_MAYBE_CONST_ਵਿਅੰਜਕ_ਵਿਅੰਜਕ (ਵਿਅੰਜਕ);
      ਜੇ (C_MAYBE_CONST_ਵਿਅੰਜਕ_NON_CONST (ਵਿਅੰਜਕ))
	*maybe_const_operands = ਝੂਠ;
      ਜੇ (C_MAYBE_CONST_ਵਿਅੰਜਕ_INT_OPERANDS (ਵਿਅੰਜਕ))
	{
	  *maybe_const_itself = ਝੂਠ;
	  inner = c_fully_fold_ਅੰਦਰੂਨੀ (inner, ਵਿੱਚ_init, maybe_const_operands,
					 maybe_const_itself, ਸੱਚ, lval);
	}
      ਜੇ (pre && !ਵਿੱਚ_init)
	ret = build2 (COMPOUND_ਵਿਅੰਜਕ, ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ), pre, inner);
      ਨਹੀਂਤਾਂ
	ret = inner;
      ਜਾਓ ਬਾਹਰਲਾ;
    }

  /* Assignment, increment, decrement, function call and comma
     operators, and statement expressions, cannot occur in constant
     expressions if evaluated / outside of sizeof.  (Function calls
     were handled above, though VA_ARG_EXPR is treated like a function
     call here, and statement expressions are handled through
     C_MAYBE_CONST_EXPR to avoid folding inside them.)  */
  ਚੋਣ (ਕੋਡ)
    {
    ਹਾਲਤ MODIFY_ਵਿਅੰਜਕ:
    ਹਾਲਤ PREDECREMENT_ਵਿਅੰਜਕ:
    ਹਾਲਤ PREINCREMENT_ਵਿਅੰਜਕ:
    ਹਾਲਤ POSTDECREMENT_ਵਿਅੰਜਕ:
    ਹਾਲਤ POSTINCREMENT_ਵਿਅੰਜਕ:
    ਹਾਲਤ COMPOUND_ਵਿਅੰਜਕ:
      *maybe_const_operands = ਝੂਠ;
      ਰੋਕੋ;

    ਹਾਲਤ VA_ARG_ਵਿਅੰਜਕ:
    ਹਾਲਤ ਨਿਸ਼ਾਨਾ_ਵਿਅੰਜਕ:
    ਹਾਲਤ BIND_ਵਿਅੰਜਕ:
    ਹਾਲਤ OBJ_TYPE_REF:
      *maybe_const_operands = ਝੂਠ;
      ret = fold (ਵਿਅੰਜਕ);
      ਜਾਓ ਬਾਹਰਲਾ;

    ਮੂਲ:
      ਰੋਕੋ;
    }

  /* Fold individual tree codes as appropriate.  */
  ਚੋਣ (ਕੋਡ)
    {
    ਹਾਲਤ COMPOUND_LITERAL_ਵਿਅੰਜਕ:
      /* Any non-constancy will have been marked in a containing
	 C_MAYBE_CONST_EXPR; there is no more folding to do here.  */
      ਜਾਓ ਬਾਹਰਲਾ;

    ਹਾਲਤ COMPONENT_REF:
      orig_op0 = op0 = ਰੁੱਖ_ਸੰਕਾਰਜ (ਵਿਅੰਜਕ, 0);
      op1 = ਰੁੱਖ_ਸੰਕਾਰਜ (ਵਿਅੰਜਕ, 1);
      op2 = ਰੁੱਖ_ਸੰਕਾਰਜ (ਵਿਅੰਜਕ, 2);
      op0 = c_fully_fold_ਅੰਦਰੂਨੀ (op0, ਵਿੱਚ_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, lval);
      STRIP_TYPE_NOPS (op0);
      ਜੇ (op0 != orig_op0)
	ret = build3 (COMPONENT_REF, ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ), op0, op1, op2);
      ਜੇ (ret != ਵਿਅੰਜਕ)
	{
	  ਰੁੱਖ_READONLY (ret) = ਰੁੱਖ_READONLY (ਵਿਅੰਜਕ);
	  ਰੁੱਖ_THIS_VOLATILE (ret) = ਰੁੱਖ_THIS_VOLATILE (ਵਿਅੰਜਕ);
	}
      ਜੇ (!lval)
	ret = fold (ret);
      ਜਾਓ ਬਾਹਰਲਾ;

    ਹਾਲਤ ARRAY_REF:
      orig_op0 = op0 = ਰੁੱਖ_ਸੰਕਾਰਜ (ਵਿਅੰਜਕ, 0);
      orig_op1 = op1 = ਰੁੱਖ_ਸੰਕਾਰਜ (ਵਿਅੰਜਕ, 1);
      op2 = ਰੁੱਖ_ਸੰਕਾਰਜ (ਵਿਅੰਜਕ, 2);
      op3 = ਰੁੱਖ_ਸੰਕਾਰਜ (ਵਿਅੰਜਕ, 3);
      op0 = c_fully_fold_ਅੰਦਰੂਨੀ (op0, ਵਿੱਚ_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, lval);
      STRIP_TYPE_NOPS (op0);
      op1 = c_fully_fold_ਅੰਦਰੂਨੀ (op1, ਵਿੱਚ_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, ਝੂਠ);
      STRIP_TYPE_NOPS (op1);
      /* Fold "foo"[2] in initializers.  */
      ਜੇ (!lval && ਵਿੱਚ_init)
	{
	  ret = c_fold_array_ref (ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ), op0, op1);
	  ਜੇ (ret)
	    ਜਾਓ ਬਾਹਰਲਾ;
	  ret = ਵਿਅੰਜਕ;
	}
      ਜੇ (op0 != orig_op0 || op1 != orig_op1)
	ret = build4 (ARRAY_REF, ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ), op0, op1, op2, op3);
      ਜੇ (ret != ਵਿਅੰਜਕ)
	{
	  ਰੁੱਖ_READONLY (ret) = ਰੁੱਖ_READONLY (ਵਿਅੰਜਕ);
	  ਰੁੱਖ_SIDE_EFFECTS (ret) = ਰੁੱਖ_SIDE_EFFECTS (ਵਿਅੰਜਕ);
	  ਰੁੱਖ_THIS_VOLATILE (ret) = ਰੁੱਖ_THIS_VOLATILE (ਵਿਅੰਜਕ);
	}
      ਜੇ (!lval)
	ret = fold (ret);
      ਜਾਓ ਬਾਹਰਲਾ;

    ਹਾਲਤ MODIFY_ਵਿਅੰਜਕ:
    ਹਾਲਤ PREDECREMENT_ਵਿਅੰਜਕ:
    ਹਾਲਤ PREINCREMENT_ਵਿਅੰਜਕ:
    ਹਾਲਤ POSTDECREMENT_ਵਿਅੰਜਕ:
    ਹਾਲਤ POSTINCREMENT_ਵਿਅੰਜਕ:
      op0_lval = ਸੱਚ;
      /* FALLTHRU */
    ਹਾਲਤ COMPOUND_ਵਿਅੰਜਕ:
    ਹਾਲਤ PLUS_ਵਿਅੰਜਕ:
    ਹਾਲਤ MINUS_ਵਿਅੰਜਕ:
    ਹਾਲਤ MULT_ਵਿਅੰਜਕ:
    ਹਾਲਤ ਸੂਚਕ_PLUS_ਵਿਅੰਜਕ:
    ਹਾਲਤ ਸੂਚਕ_DIFF_ਵਿਅੰਜਕ:
    ਹਾਲਤ TRUNC_DIV_ਵਿਅੰਜਕ:
    ਹਾਲਤ CEIL_DIV_ਵਿਅੰਜਕ:
    ਹਾਲਤ FLOOR_DIV_ਵਿਅੰਜਕ:
    ਹਾਲਤ TRUNC_MOD_ਵਿਅੰਜਕ:
    ਹਾਲਤ RDIV_ਵਿਅੰਜਕ:
    ਹਾਲਤ EXACT_DIV_ਵਿਅੰਜਕ:
    ਹਾਲਤ LSHIFT_ਵਿਅੰਜਕ:
    ਹਾਲਤ RSHIFT_ਵਿਅੰਜਕ:
    ਹਾਲਤ LROTATE_ਵਿਅੰਜਕ:
    ਹਾਲਤ RROTATE_ਵਿਅੰਜਕ:
    ਹਾਲਤ ਦੋਆਧਾਰੀ_ਅੰਕ_IOR_ਵਿਅੰਜਕ:
    ਹਾਲਤ ਦੋਆਧਾਰੀ_ਅੰਕ_XOR_ਵਿਅੰਜਕ:
    ਹਾਲਤ ਦੋਆਧਾਰੀ_ਅੰਕ_AND_ਵਿਅੰਜਕ:
    ਹਾਲਤ LT_ਵਿਅੰਜਕ:
    ਹਾਲਤ LE_ਵਿਅੰਜਕ:
    ਹਾਲਤ GT_ਵਿਅੰਜਕ:
    ਹਾਲਤ GE_ਵਿਅੰਜਕ:
    ਹਾਲਤ EQ_ਵਿਅੰਜਕ:
    ਹਾਲਤ NE_ਵਿਅੰਜਕ:
    ਹਾਲਤ COMPLEX_ਵਿਅੰਜਕ:
    ਹਾਲਤ TRUTH_AND_ਵਿਅੰਜਕ:
    ਹਾਲਤ TRUTH_OR_ਵਿਅੰਜਕ:
    ਹਾਲਤ TRUTH_XOR_ਵਿਅੰਜਕ:
    ਹਾਲਤ UNORDERED_ਵਿਅੰਜਕ:
    ਹਾਲਤ ORDERED_ਵਿਅੰਜਕ:
    ਹਾਲਤ UNLT_ਵਿਅੰਜਕ:
    ਹਾਲਤ UNLE_ਵਿਅੰਜਕ:
    ਹਾਲਤ UNGT_ਵਿਅੰਜਕ:
    ਹਾਲਤ UNGE_ਵਿਅੰਜਕ:
    ਹਾਲਤ UNEQ_ਵਿਅੰਜਕ:
    ਹਾਲਤ MEM_REF:
      /* Binary operations evaluating both arguments (increment and
	 decrement are binary internally in GCC).  */
      orig_op0 = op0 = ਰੁੱਖ_ਸੰਕਾਰਜ (ਵਿਅੰਜਕ, 0);
      orig_op1 = op1 = ਰੁੱਖ_ਸੰਕਾਰਜ (ਵਿਅੰਜਕ, 1);
      op0 = c_fully_fold_ਅੰਦਰੂਨੀ (op0, ਵਿੱਚ_init, maybe_const_operands,
				   maybe_const_itself, for_int_const,
				   op0_lval);
      STRIP_TYPE_NOPS (op0);
      /* The RHS of a MODIFY_EXPR was fully folded when building that
	 expression for the sake of conversion warnings.  */
      ਜੇ (ਕੋਡ != MODIFY_ਵਿਅੰਜਕ)
	op1 = c_fully_fold_ਅੰਦਰੂਨੀ (op1, ਵਿੱਚ_init, maybe_const_operands,
				     maybe_const_itself, for_int_const, ਝੂਠ);
      STRIP_TYPE_NOPS (op1);

      ਜੇ (for_int_const && (ਰੁੱਖ_ਕੋਡ (op0) != INTEGER_CST
			    || ਰੁੱਖ_ਕੋਡ (op1) != INTEGER_CST))
	ਜਾਓ ਬਾਹਰਲਾ;

      ਜੇ (ਰੁੱਖ_ਕੋਡ_CLASS (ਕੋਡ) == tcc_comparison
	  && ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (op0)) == NULLPTR_TYPE
	  && ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (op1)) == NULLPTR_TYPE)
	{
	  ਚੋਣ (ਕੋਡ)
	    {
	    ਹਾਲਤ EQ_ਵਿਅੰਜਕ:
	      ret = constant_boolean_ਗੰਢ (ਸੱਚ, ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ));
	      ਰੋਕੋ;
	    ਹਾਲਤ NE_ਵਿਅੰਜਕ:
	      ret = constant_boolean_ਗੰਢ (ਝੂਠ, ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ));
	      ਰੋਕੋ;
	    ਮੂਲ:
	      gcc_unreachable ();
	    }
	  ret = omit_two_operands_loc (loc, ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ), ret,
				       op0, op1);
	}
      ਨਹੀਂਤਾਂ ਜੇ (op0 != orig_op0 || op1 != orig_op1 || ਵਿੱਚ_init)
	ret = ਵਿੱਚ_init
	  ? fold_build2_initializer_loc (loc, ਕੋਡ, ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ), op0, op1)
	  : fold_build2_loc (loc, ਕੋਡ, ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ), op0, op1);
      ਨਹੀਂਤਾਂ
	ret = fold (ਵਿਅੰਜਕ);
      ਜੇ (ਰੁੱਖ_ਉਛਾਲ_P (ret)
	  && !ਰੁੱਖ_ਉਛਾਲ_P (op0)
	  && !(ਦੁਆਧਾਰੀ_CLASS_P (op0) && ਰੁੱਖ_ਉਛਾਲ_P (ਰੁੱਖ_ਸੰਕਾਰਜ (op0, 1)))
	  && !ਰੁੱਖ_ਉਛਾਲ_P (op1))
	ਉਛਾਲ_warning (ਵਿਅੰਜਕ_LOC_OR_LOC (ਵਿਅੰਜਕ, ਨਿਵੇਸ਼_location), ret, ਵਿਅੰਜਕ);
      ਜੇ (ਕੋਡ == LSHIFT_ਵਿਅੰਜਕ
	  && ਰੁੱਖ_ਕੋਡ (orig_op0) != INTEGER_CST
	  && (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (orig_op0)) == INTEGER_TYPE
	      || ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (orig_op0)) == BITINT_TYPE)
	  && ਰੁੱਖ_ਕੋਡ (op0) == INTEGER_CST
	  && c_inhibit_evaluation_warnings == 0
	  && !TYPE_ਉਛਾਲ_WRAPS (ਰੁੱਖ_TYPE (orig_op0))
	  && ਰੁੱਖ_int_cst_sgn (op0) < 0)
	warning_at (loc, OPT_Wshift_negative_ਮੁੱਲ,
		    "left shift of negative value");
      ਜੇ ((ਕੋਡ == LSHIFT_ਵਿਅੰਜਕ
	   || ਕੋਡ == RSHIFT_ਵਿਅੰਜਕ
	   || ਕੋਡ == LROTATE_ਵਿਅੰਜਕ
	   || ਕੋਡ == RROTATE_ਵਿਅੰਜਕ)
	  && ਰੁੱਖ_ਕੋਡ (orig_op1) != INTEGER_CST
	  && ਰੁੱਖ_ਕੋਡ (op1) == INTEGER_CST
	  && ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (orig_op1)) == INTEGER_TYPE
	  && c_inhibit_evaluation_warnings == 0)
	{
	  ਜੇ (ਰੁੱਖ_int_cst_sgn (op1) < 0)
	    warning_at (loc, OPT_Wshift_ਗਿਣਤੀ_negative,
			(ਕੋਡ == LSHIFT_ਵਿਅੰਜਕ
			 ? G_("left shift count is negative")
			 : G_("right shift count is negative")));
	  ਨਹੀਂਤਾਂ ਜੇ ((ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (orig_op0)) == INTEGER_TYPE
		    || ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (orig_op0)) == BITINT_TYPE
		    || ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (orig_op0)) == FIXED_ਬਿੰਦੂ_TYPE)
		   && compare_ਰੁੱਖ_int (op1,
					TYPE_PRECISION (ਰੁੱਖ_TYPE (orig_op0)))
		      >= 0
		   && !warning_suppressed_p (ਵਿਅੰਜਕ, OPT_Wshift_ਗਿਣਤੀ_ਉਛਾਲ))
	    warning_at (loc, OPT_Wshift_ਗਿਣਤੀ_ਉਛਾਲ,
			(ਕੋਡ == LSHIFT_ਵਿਅੰਜਕ
			 ? G_("left shift count >= width of type")
			 : G_("right shift count >= width of type")));
	  ਨਹੀਂਤਾਂ ਜੇ (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (orig_op0)) == ਸਦਿਸ਼_TYPE
		   && compare_ਰੁੱਖ_int (op1,
					TYPE_PRECISION (ਰੁੱਖ_TYPE (ਰੁੱਖ_TYPE (orig_op0))))
		      >= 0)
	    warning_at (loc, OPT_Wshift_ਗਿਣਤੀ_ਉਛਾਲ,
			ਕੋਡ == LSHIFT_ਵਿਅੰਜਕ
			? G_("left shift count >= width of vector element")
			: G_("right shift count >= width of vector element"));
	}
      ਜੇ (ਕੋਡ == LSHIFT_ਵਿਅੰਜਕ
	  /* If either OP0 has been folded to INTEGER_CST...  */
	  && ((ਰੁੱਖ_ਕੋਡ (orig_op0) != INTEGER_CST
	       && (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (orig_op0)) == INTEGER_TYPE
		   || ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (orig_op0)) == BITINT_TYPE)
	       && ਰੁੱਖ_ਕੋਡ (op0) == INTEGER_CST)
	      /* ...or if OP1 has been folded to INTEGER_CST...  */
	      || (ਰੁੱਖ_ਕੋਡ (orig_op1) != INTEGER_CST
		  && (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (orig_op1)) == INTEGER_TYPE
		      || ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (orig_op1)) == BITINT_TYPE)
		  && ਰੁੱਖ_ਕੋਡ (op1) == INTEGER_CST))
	  && c_inhibit_evaluation_warnings == 0)
	/* ...then maybe we can detect an overflow.  */
	maybe_warn_ਖਿਸਕਾਓ_ਉਛਾਲ (loc, op0, op1);
      ਜੇ ((ਕੋਡ == TRUNC_DIV_ਵਿਅੰਜਕ
	   || ਕੋਡ == CEIL_DIV_ਵਿਅੰਜਕ
	   || ਕੋਡ == FLOOR_DIV_ਵਿਅੰਜਕ
	   || ਕੋਡ == EXACT_DIV_ਵਿਅੰਜਕ
	   || ਕੋਡ == TRUNC_MOD_ਵਿਅੰਜਕ)
	  && ਰੁੱਖ_ਕੋਡ (orig_op1) != INTEGER_CST
	  && ਰੁੱਖ_ਕੋਡ (op1) == INTEGER_CST
	  && (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (orig_op0)) == INTEGER_TYPE
	      || ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (orig_op0)) == BITINT_TYPE
	      || ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (orig_op0)) == FIXED_ਬਿੰਦੂ_TYPE)
	  && (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (orig_op1)) == INTEGER_TYPE
	      || ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (orig_op1)) == BITINT_TYPE))
	warn_for_div_by_zero (loc, op1);
      ਜੇ (ਕੋਡ == MEM_REF
	  && ret != ਵਿਅੰਜਕ
	  && ਰੁੱਖ_ਕੋਡ (ret) == MEM_REF)
	{
	  ਰੁੱਖ_READONLY (ret) = ਰੁੱਖ_READONLY (ਵਿਅੰਜਕ);
	  ਰੁੱਖ_SIDE_EFFECTS (ret) = ਰੁੱਖ_SIDE_EFFECTS (ਵਿਅੰਜਕ);
	  ਰੁੱਖ_THIS_VOLATILE (ret) = ਰੁੱਖ_THIS_VOLATILE (ਵਿਅੰਜਕ);
	}
      ਜਾਓ ਬਾਹਰਲਾ;

    ਹਾਲਤ ADDR_ਵਿਅੰਜਕ:
      op0_lval = ਸੱਚ;
      ਜਾਓ unary;
    ਹਾਲਤ REALPART_ਵਿਅੰਜਕ:
    ਹਾਲਤ IMAGPART_ਵਿਅੰਜਕ:
    ਹਾਲਤ VIEW_CONVERT_ਵਿਅੰਜਕ:
      op0_lval = lval;
      /* FALLTHRU */
    ਹਾਲਤ ਅਸਿੱਧਾ_REF:
    ਹਾਲਤ FIX_TRUNC_ਵਿਅੰਜਕ:
    ਹਾਲਤ FLOAT_ਵਿਅੰਜਕ:
    CASE_CONVERT:
    ਹਾਲਤ ADDR_SPACE_CONVERT_ਵਿਅੰਜਕ:
    ਹਾਲਤ NON_LVALUE_ਵਿਅੰਜਕ:
    ਹਾਲਤ NEGATE_ਵਿਅੰਜਕ:
    ਹਾਲਤ ਦੋਆਧਾਰੀ_ਅੰਕ_NOT_ਵਿਅੰਜਕ:
    ਹਾਲਤ TRUTH_NOT_ਵਿਅੰਜਕ:
    ਹਾਲਤ CONJ_ਵਿਅੰਜਕ:
    ਹਾਲਤ PAREN_ਵਿਅੰਜਕ:
    unary:
      /* Unary operations.  */
      orig_op0 = op0 = ਰੁੱਖ_ਸੰਕਾਰਜ (ਵਿਅੰਜਕ, 0);
      op0 = c_fully_fold_ਅੰਦਰੂਨੀ (op0, ਵਿੱਚ_init, maybe_const_operands,
				   maybe_const_itself, for_int_const,
				   op0_lval);
      STRIP_TYPE_NOPS (op0);

      ਜੇ (for_int_const && ਰੁੱਖ_ਕੋਡ (op0) != INTEGER_CST)
	ਜਾਓ ਬਾਹਰਲਾ;

      /* ??? Cope with user tricks that amount to offsetof.  The middle-end is
	 not prepared to deal with them if they occur in initializers.  */
      ਜੇ (op0 != orig_op0
	  && ਕੋਡ == ADDR_ਵਿਅੰਜਕ
	  && (op1 = get_ਅਧਾਰ_ਪਤਾ (op0)) != NULL_ਰੁੱਖ
	  && ਅਸਿੱਧਾ_REF_P (op1)
	  && ਰੁੱਖ_CONSTANT (ਰੁੱਖ_ਸੰਕਾਰਜ (op1, 0)))
	ret = fold_offsetof (op0, ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ));
      ਨਹੀਂਤਾਂ ਜੇ (op0 != orig_op0 || ਵਿੱਚ_init)
	ret = ਵਿੱਚ_init
	  ? fold_build1_initializer_loc (loc, ਕੋਡ, ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ), op0)
	  : fold_build1_loc (loc, ਕੋਡ, ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ), op0);
      ਨਹੀਂਤਾਂ
	ret = fold (ਵਿਅੰਜਕ);
      ਜੇ (ਕੋਡ == ਅਸਿੱਧਾ_REF
	  && ret != ਵਿਅੰਜਕ
	  && ਅਸਿੱਧਾ_REF_P (ret))
	{
	  ਰੁੱਖ_READONLY (ret) = ਰੁੱਖ_READONLY (ਵਿਅੰਜਕ);
	  ਰੁੱਖ_SIDE_EFFECTS (ret) = ਰੁੱਖ_SIDE_EFFECTS (ਵਿਅੰਜਕ);
	  ਰੁੱਖ_THIS_VOLATILE (ret) = ਰੁੱਖ_THIS_VOLATILE (ਵਿਅੰਜਕ);
	}
      ਚੋਣ (ਕੋਡ)
	{
	ਹਾਲਤ FIX_TRUNC_ਵਿਅੰਜਕ:
	ਹਾਲਤ FLOAT_ਵਿਅੰਜਕ:
	CASE_CONVERT:
	  /* Don't warn about explicit conversions.  We will already
	     have warned about suspect implicit conversions.  */
	  ਰੋਕੋ;

	ਮੂਲ:
	  ਜੇ (ਰੁੱਖ_ਉਛਾਲ_P (ret) && !ਰੁੱਖ_ਉਛਾਲ_P (op0))
	    ਉਛਾਲ_warning (ਵਿਅੰਜਕ_LOCATION (ਵਿਅੰਜਕ), ret, op0);
	  ਰੋਕੋ;
	}
      ਜਾਓ ਬਾਹਰਲਾ;

    ਹਾਲਤ TRUTH_ANDIF_ਵਿਅੰਜਕ:
    ਹਾਲਤ TRUTH_ORIF_ਵਿਅੰਜਕ:
      /* Binary operations not necessarily evaluating both
	 arguments.  */
      orig_op0 = op0 = ਰੁੱਖ_ਸੰਕਾਰਜ (ਵਿਅੰਜਕ, 0);
      orig_op1 = op1 = ਰੁੱਖ_ਸੰਕਾਰਜ (ਵਿਅੰਜਕ, 1);
      op0 = c_fully_fold_ਅੰਦਰੂਨੀ (op0, ਵਿੱਚ_init, &op0_const, &op0_const_self,
				   for_int_const, ਝੂਠ);
      STRIP_TYPE_NOPS (op0);

      ਅਣਵਰਤਿਆ_p = (op0 == (ਕੋਡ == TRUTH_ANDIF_ਵਿਅੰਜਕ
			  ? truthvalue_false_ਗੰਢ
			  : truthvalue_true_ਗੰਢ));
      c_disable_warnings (ਅਣਵਰਤਿਆ_p);
      op1 = c_fully_fold_ਅੰਦਰੂਨੀ (op1, ਵਿੱਚ_init, &op1_const, &op1_const_self,
				   for_int_const, ਝੂਠ);
      STRIP_TYPE_NOPS (op1);
      c_enable_warnings (ਅਣਵਰਤਿਆ_p);

      ਜੇ (for_int_const
	  && (ਰੁੱਖ_ਕੋਡ (op0) != INTEGER_CST
	      /* Require OP1 be an INTEGER_CST only if it's evaluated.  */
	      || (!ਅਣਵਰਤਿਆ_p && ਰੁੱਖ_ਕੋਡ (op1) != INTEGER_CST)))
	ਜਾਓ ਬਾਹਰਲਾ;

      ਜੇ (op0 != orig_op0 || op1 != orig_op1 || ਵਿੱਚ_init)
	ret = ਵਿੱਚ_init
	  ? fold_build2_initializer_loc (loc, ਕੋਡ, ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ), op0, op1)
	  : fold_build2_loc (loc, ਕੋਡ, ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ), op0, op1);
      ਨਹੀਂਤਾਂ
	ret = fold (ਵਿਅੰਜਕ);
      *maybe_const_operands &= op0_const;
      *maybe_const_itself &= op0_const_self;
      ਜੇ (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && (ਕੋਡ == TRUTH_ANDIF_ਵਿਅੰਜਕ
		? op0 == truthvalue_false_ਗੰਢ
		: op0 == truthvalue_true_ਗੰਢ)))
	*maybe_const_operands &= op1_const;
      ਜੇ (!(op0_const
	    && op0_const_self
	    && (ਕੋਡ == TRUTH_ANDIF_ਵਿਅੰਜਕ
		? op0 == truthvalue_false_ਗੰਢ
		: op0 == truthvalue_true_ਗੰਢ)))
	*maybe_const_itself &= op1_const_self;
      ਜਾਓ ਬਾਹਰਲਾ;

    ਹਾਲਤ COND_ਵਿਅੰਜਕ:
      orig_op0 = op0 = ਰੁੱਖ_ਸੰਕਾਰਜ (ਵਿਅੰਜਕ, 0);
      orig_op1 = op1 = ਰੁੱਖ_ਸੰਕਾਰਜ (ਵਿਅੰਜਕ, 1);
      orig_op2 = op2 = ਰੁੱਖ_ਸੰਕਾਰਜ (ਵਿਅੰਜਕ, 2);
      op0 = c_fully_fold_ਅੰਦਰੂਨੀ (op0, ਵਿੱਚ_init, &op0_const, &op0_const_self,
				   for_int_const, ਝੂਠ);

      STRIP_TYPE_NOPS (op0);
      c_disable_warnings (op0 == truthvalue_false_ਗੰਢ);
      op1 = c_fully_fold_ਅੰਦਰੂਨੀ (op1, ਵਿੱਚ_init, &op1_const, &op1_const_self,
				   for_int_const, ਝੂਠ);
      STRIP_TYPE_NOPS (op1);
      c_enable_warnings (op0 == truthvalue_false_ਗੰਢ);

      c_disable_warnings (op0 == truthvalue_true_ਗੰਢ);
      op2 = c_fully_fold_ਅੰਦਰੂਨੀ (op2, ਵਿੱਚ_init, &op2_const, &op2_const_self,
				   for_int_const, ਝੂਠ);
      STRIP_TYPE_NOPS (op2);
      c_enable_warnings (op0 == truthvalue_true_ਗੰਢ);

      ਜੇ (for_int_const
	  && (ਰੁੱਖ_ਕੋਡ (op0) != INTEGER_CST
	      /* Only the evaluated operand must be an INTEGER_CST.  */
	      || (op0 == truthvalue_true_ਗੰਢ
		  ? ਰੁੱਖ_ਕੋਡ (op1) != INTEGER_CST
		  : ਰੁੱਖ_ਕੋਡ (op2) != INTEGER_CST)))
	ਜਾਓ ਬਾਹਰਲਾ;

      ਜੇ (op0 != orig_op0 || op1 != orig_op1 || op2 != orig_op2)
	ret = fold_build3_loc (loc, ਕੋਡ, ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ), op0, op1, op2);
      ਨਹੀਂਤਾਂ
	ret = fold (ਵਿਅੰਜਕ);
      *maybe_const_operands &= op0_const;
      *maybe_const_itself &= op0_const_self;
      ਜੇ (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && op0 == truthvalue_false_ਗੰਢ))
	*maybe_const_operands &= op1_const;
      ਜੇ (!(op0_const
	    && op0_const_self
	    && op0 == truthvalue_false_ਗੰਢ))
	*maybe_const_itself &= op1_const_self;
      ਜੇ (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && op0 == truthvalue_true_ਗੰਢ))
	*maybe_const_operands &= op2_const;
      ਜੇ (!(op0_const
	    && op0_const_self
	    && op0 == truthvalue_true_ਗੰਢ))
	*maybe_const_itself &= op2_const_self;
      ਜਾਓ ਬਾਹਰਲਾ;

    ਹਾਲਤ VEC_COND_ਵਿਅੰਜਕ:
      orig_op0 = op0 = ਰੁੱਖ_ਸੰਕਾਰਜ (ਵਿਅੰਜਕ, 0);
      orig_op1 = op1 = ਰੁੱਖ_ਸੰਕਾਰਜ (ਵਿਅੰਜਕ, 1);
      orig_op2 = op2 = ਰੁੱਖ_ਸੰਕਾਰਜ (ਵਿਅੰਜਕ, 2);
      op0 = c_fully_fold_ਅੰਦਰੂਨੀ (op0, ਵਿੱਚ_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, ਝੂਠ);
      STRIP_TYPE_NOPS (op0);
      op1 = c_fully_fold_ਅੰਦਰੂਨੀ (op1, ਵਿੱਚ_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, ਝੂਠ);
      STRIP_TYPE_NOPS (op1);
      op2 = c_fully_fold_ਅੰਦਰੂਨੀ (op2, ਵਿੱਚ_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, ਝੂਠ);
      STRIP_TYPE_NOPS (op2);

      ਜੇ (op0 != orig_op0 || op1 != orig_op1 || op2 != orig_op2)
	ret = fold_build3_loc (loc, ਕੋਡ, ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ), op0, op1, op2);
      ਨਹੀਂਤਾਂ
	ret = fold (ਵਿਅੰਜਕ);
      ਜਾਓ ਬਾਹਰਲਾ;

    ਹਾਲਤ EXCESS_PRECISION_ਵਿਅੰਜਕ:
      /* Each case where an operand with excess precision may be
	 encountered must remove the EXCESS_PRECISION_EXPR around
	 inner operands and possibly put one around the whole
	 expression or possibly convert to the semantic type (which
	 c_fully_fold does); we cannot tell at this stage which is
	 appropriate in any particular case.  */
      gcc_unreachable ();

    ਹਾਲਤ SAVE_ਵਿਅੰਜਕ:
      /* Make sure to fold the contents of a SAVE_EXPR exactly once.  */
      op0 = ਰੁੱਖ_ਸੰਕਾਰਜ (ਵਿਅੰਜਕ, 0);
      ਜੇ (!SAVE_ਵਿਅੰਜਕ_FOLDED_P (ਵਿਅੰਜਕ))
	{
	  op0 = c_fully_fold_ਅੰਦਰੂਨੀ (op0, ਵਿੱਚ_init, maybe_const_operands,
				       maybe_const_itself, for_int_const,
				       ਝੂਠ);
	  ਰੁੱਖ_ਸੰਕਾਰਜ (ਵਿਅੰਜਕ, 0) = op0;
	  SAVE_ਵਿਅੰਜਕ_FOLDED_P (ਵਿਅੰਜਕ) = ਸੱਚ;
	}
      /* Return the SAVE_EXPR operand if it is invariant.  */
      ਜੇ (ਰੁੱਖ_invariant_p (op0))
	ret = op0;
      ਜਾਓ ਬਾਹਰਲਾ;

    ਮੂਲ:
      /* Various codes may appear through folding built-in functions
	 and their arguments.  */
      ਜਾਓ ਬਾਹਰਲਾ;
    }

 ਬਾਹਰਲਾ:
  /* Some folding may introduce NON_LVALUE_EXPRs; all lvalue checks
     have been done by this point, so remove them again.  */
  nowarning |= warning_suppressed_p (ret, OPT_Woverflow);
  STRIP_TYPE_NOPS (ret);
  ਜੇ (nowarning && !warning_suppressed_p (ret, OPT_Woverflow))
    {
      ਜੇ (!CAN_HAVE_LOCATION_P (ret))
	ret = build1 (NOP_ਵਿਅੰਜਕ, ਰੁੱਖ_TYPE (ret), ret);
      suppress_warning (ret, OPT_Woverflow);
    }
  ਜੇ (ret != ਵਿਅੰਜਕ)
    {
      protected_ਸੈੱਟ_ਵਿਅੰਜਕ_location (ret, loc);
      ਜੇ (IS_ਵਿਅੰਜਕ_ਕੋਡ_CLASS (ਕਿਸਮ))
	ਸੈੱਟ_ਸਰੋਤ_range (ret, old_range.m_ਸ਼ੁਰੂ, old_range.m_ਅੰਤ);
    }
  ਵਾਪਸ ret;
}

/* Fold X for consideration by one of the warning functions when checking
   whether an expression has a constant value.  */

ਰੁੱਖ
fold_for_warn (ਰੁੱਖ x)
{
  /* The C front-end has already folded X appropriately.  */
  ਵਾਪਸ x;
}
