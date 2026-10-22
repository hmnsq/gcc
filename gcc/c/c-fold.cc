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

#ଅନ୍ତର୍ଭାଵ "config.h"
#ଅନ୍ତର୍ଭାଵ "system.h"
#ଅନ୍ତର୍ଭାଵ "coretypes.h"
#ଅନ୍ତର୍ଭାଵ "target.h"
#ଅନ୍ତର୍ଭାଵ "function.h"
#ଅନ୍ତର୍ଭାଵ "bitmap.h"
#ଅନ୍ତର୍ଭାଵ "c-tree.h"
#ଅନ୍ତର୍ଭାଵ "intl.h"
#ଅନ୍ତର୍ଭାଵ "gimplify.h"

ସ୍ଥିର ବୃକ୍ଷ c_fully_fold_internal (ବୃକ୍ଷ ପଦସମଷ୍ଟି, ତାର୍କିକ, ତାର୍କିକ *, ତାର୍କିକ *, ତାର୍କିକ,
				   ତାର୍କିକ);

/* If DISABLE is true, stop issuing warnings.  This is used when
   parsing code that we know will not be executed.  This function may
   be called multiple times, and works as a stack.  */

ସ୍ଥିର ଶୂନ୍ୟ
c_disable_warnings (ତାର୍କିକ disable)
{
  ଯଦି (disable)
    {
      ++c_inhibit_evaluation_warnings;
    }
}

/* If ENABLE is true, re-enable issuing warnings.  */

ସ୍ଥିର ଶୂନ୍ୟ
c_enable_warnings (ତାର୍କିକ enable)
{
  ଯଦି (enable)
    {
      --c_inhibit_evaluation_warnings;
    }
}

/* Try to fold ARRAY_REF ary[index] if possible and not handled by
   normal fold, return NULL_TREE otherwise.  */

ସ୍ଥିର ବୃକ୍ଷ
c_fold_array_ref (ବୃକ୍ଷ type, ବୃକ୍ଷ ary, ବୃକ୍ଷ index)
{
  ଯଦି (ବୃକ୍ଷ_CODE (ary) != STRING_CST
      || ବୃକ୍ଷ_CODE (index) != INTEGER_CST
      || ବୃକ୍ଷ_OVERFLOW (index)
      || ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (ary)) != ARRAY_TYPE
      || !ବୃକ୍ଷ_fits_uhwi_p (index))
    ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;

  ବୃକ୍ଷ elem_type = ବୃକ୍ଷ_TYPE (ବୃକ୍ଷ_TYPE (ary));
  unsigned elem_nchars = (TYPE_PRECISION (elem_type)
			  / TYPE_PRECISION (char_type_ଗଣ୍ଠି));
  unsigned len = (unsigned) ବୃକ୍ଷ_STRING_LENGTH (ary) / elem_nchars;
  ବୃକ୍ଷ nelts_minus_one = array_type_nelts_minus_one (ବୃକ୍ଷ_TYPE (ary));
  ତାର୍କିକ dummy1 = ସତ୍ୟ, dummy2 = ସତ୍ୟ;
  nelts_minus_one = c_fully_fold_internal (nelts_minus_one, ସତ୍ୟ, &dummy1,
					   &dummy2, ମିଥ୍ୟା, ମିଥ୍ୟା);
  unsigned HOST_WIDE_INT i = ବୃକ୍ଷ_to_uhwi (index);
  ଯଦି (!ବୃକ୍ଷ_int_cst_le (index, nelts_minus_one)
      || i >= len
      || i + elem_nchars > len)
    ଫେରନ୍ତୁ NULL_ବୃକ୍ଷ;

  ଯଦି (elem_nchars == 1)
    ଫେରନ୍ତୁ build_int_cst (type, ବୃକ୍ଷ_STRING_POINTER (ary)[i]);

  ଅଚଳ unsigned ଅକ୍ଷର *ptr
    = ((ଅଚଳ unsigned ଅକ୍ଷର *)ବୃକ୍ଷ_STRING_POINTER (ary) + i * elem_nchars);
  ଫେରନ୍ତୁ native_interpret_ପଦସମଷ୍ଟି (type, ptr, elem_nchars);
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

ବୃକ୍ଷ
c_fully_fold (ବୃକ୍ଷ ପଦସମଷ୍ଟି, ତାର୍କିକ in_init, ତାର୍କିକ *maybe_const, ତାର୍କିକ lval)
{
  ବୃକ୍ଷ ret;
  ବୃକ୍ଷ eptype = NULL_ବୃକ୍ଷ;
  ତାର୍କିକ dummy = ସତ୍ୟ;
  ତାର୍କିକ maybe_const_itself = ସତ୍ୟ;
  location_t loc = ପଦସମଷ୍ଟି_LOCATION (ପଦସମଷ୍ଟି);

  ଯଦି (!maybe_const)
    maybe_const = &dummy;
  ଯଦି (ବୃକ୍ଷ_CODE (ପଦସମଷ୍ଟି) == EXCESS_PRECISION_ପଦସମଷ୍ଟି)
    {
      eptype = ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି);
      ପଦସମଷ୍ଟି = ବୃକ୍ଷ_OPERAND (ପଦସମଷ୍ଟି, 0);
    }
  ret = c_fully_fold_internal (ପଦସମଷ୍ଟି, in_init, maybe_const,
			       &maybe_const_itself, ମିଥ୍ୟା, lval);
  ଯଦି (eptype)
    ret = fold_convert_loc (loc, eptype, ret);
  *maybe_const &= maybe_const_itself;
  ଫେରନ୍ତୁ ret;
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

ସ୍ଥିର ବୃକ୍ଷ
c_fully_fold_internal (ବୃକ୍ଷ ପଦସମଷ୍ଟି, ତାର୍କିକ in_init, ତାର୍କିକ *maybe_const_operands,
		       ତାର୍କିକ *maybe_const_itself, ତାର୍କିକ for_int_const, ତାର୍କିକ lval)
{
  ବୃକ୍ଷ ret = ପଦସମଷ୍ଟି;
  ଗଣନା ବୃକ୍ଷ_code code = ବୃକ୍ଷ_CODE (ପଦସମଷ୍ଟି);
  ଗଣନା ବୃକ୍ଷ_code_class kind = ବୃକ୍ଷ_CODE_CLASS (code);
  location_t loc = ପଦସମଷ୍ଟି_LOCATION (ପଦସମଷ୍ଟି);
  ବୃକ୍ଷ op0, op1, op2, op3;
  ବୃକ୍ଷ orig_op0, orig_op1, orig_op2;
  ତାର୍କିକ op0_const = ସତ୍ୟ, op1_const = ସତ୍ୟ, op2_const = ସତ୍ୟ;
  ତାର୍କିକ op0_const_self = ସତ୍ୟ, op1_const_self = ସତ୍ୟ, op2_const_self = ସତ୍ୟ;
  ତାର୍କିକ nowarning = warning_suppressed_p (ପଦସମଷ୍ଟି, OPT_Woverflow);
  ତାର୍କିକ unused_p;
  ତାର୍କିକ op0_lval = ମିଥ୍ୟା;
  source_range old_range;

  /* Constants, declarations, statements, errors, and anything else not
     counted as an expression cannot usefully be folded further at this
     point.  */
  ଯଦି (!IS_ପଦସମଷ୍ଟି_CODE_CLASS (kind) || kind == tcc_statement)
    {
      /* Except for variables which we can optimize to its initializer.  */
      ଯଦି (VAR_P (ପଦସମଷ୍ଟି) && !lval && (optimize || in_init))
	{
	  ଯଦି (in_init)
	    ret = decl_constant_ମୂଲ୍ୟ_1 (ପଦସମଷ୍ଟି, ସତ୍ୟ);
	  ଅନ୍ୟଥା
	    {
	      ret = decl_constant_ମୂଲ୍ୟ (ପଦସମଷ୍ଟି);
	      ଯଦି (ret != ପଦସମଷ୍ଟି
		  && (TYPE_MODE (ବୃକ୍ଷ_TYPE (ret)) == BLKmode
		      || ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (ret)) == ARRAY_TYPE))
		ଫେରନ୍ତୁ ପଦସମଷ୍ଟି;
	    }
	  /* Avoid unwanted tree sharing between the initializer and current
	     function's body where the tree can be modified e.g. by the
	     gimplifier.  */
	  ଯଦି (ret != ପଦସମଷ୍ଟି && ବୃକ୍ଷ_STATIC (ପଦସମଷ୍ଟି))
	    ret = unshare_ପଦସମଷ୍ଟି (ret);
	  ଫେରନ୍ତୁ ret;
	}
      ଫେରନ୍ତୁ ପଦସମଷ୍ଟି;
    }

  ଯଦି (IS_ପଦସମଷ୍ଟି_CODE_CLASS (kind))
    old_range = ପଦସମଷ୍ଟି_LOCATION_RANGE (ପଦସମଷ୍ଟି);

  /* Operands of variable-length expressions (function calls) have
     already been folded, as have __builtin_* function calls, and such
     expressions cannot occur in constant expressions.  */
  ଯଦି (kind == tcc_vl_exp)
    {
      *maybe_const_operands = ମିଥ୍ୟା;
      ret = fold (ପଦସମଷ୍ଟି);
      ଯାଅ out;
    }

  ଯଦି (code == C_MAYBE_CONST_ପଦସମଷ୍ଟି)
    {
      ବୃକ୍ଷ pre = C_MAYBE_CONST_ପଦସମଷ୍ଟି_PRE (ପଦସମଷ୍ଟି);
      ବୃକ୍ଷ inner = C_MAYBE_CONST_ପଦସମଷ୍ଟି_ପଦସମଷ୍ଟି (ପଦସମଷ୍ଟି);
      ଯଦି (C_MAYBE_CONST_ପଦସମଷ୍ଟି_NON_CONST (ପଦସମଷ୍ଟି))
	*maybe_const_operands = ମିଥ୍ୟା;
      ଯଦି (C_MAYBE_CONST_ପଦସମଷ୍ଟି_INT_OPERANDS (ପଦସମଷ୍ଟି))
	{
	  *maybe_const_itself = ମିଥ୍ୟା;
	  inner = c_fully_fold_internal (inner, in_init, maybe_const_operands,
					 maybe_const_itself, ସତ୍ୟ, lval);
	}
      ଯଦି (pre && !in_init)
	ret = build2 (COMPOUND_ପଦସମଷ୍ଟି, ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି), pre, inner);
      ଅନ୍ୟଥା
	ret = inner;
      ଯାଅ out;
    }

  /* Assignment, increment, decrement, function call and comma
     operators, and statement expressions, cannot occur in constant
     expressions if evaluated / outside of sizeof.  (Function calls
     were handled above, though VA_ARG_EXPR is treated like a function
     call here, and statement expressions are handled through
     C_MAYBE_CONST_EXPR to avoid folding inside them.)  */
  ବାଛ (code)
    {
    ସ୍ଥିତି MODIFY_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି PREDECREMENT_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି PREINCREMENT_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି POSTDECREMENT_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି POSTINCREMENT_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି COMPOUND_ପଦସମଷ୍ଟି:
      *maybe_const_operands = ମିଥ୍ୟା;
      ଭାଙ୍ଗ;

    ସ୍ଥିତି VA_ARG_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି TARGET_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି BIND_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି OBJ_TYPE_REF:
      *maybe_const_operands = ମିଥ୍ୟା;
      ret = fold (ପଦସମଷ୍ଟି);
      ଯାଅ out;

    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
      ଭାଙ୍ଗ;
    }

  /* Fold individual tree codes as appropriate.  */
  ବାଛ (code)
    {
    ସ୍ଥିତି COMPOUND_LITERAL_ପଦସମଷ୍ଟି:
      /* Any non-constancy will have been marked in a containing
	 C_MAYBE_CONST_EXPR; there is no more folding to do here.  */
      ଯାଅ out;

    ସ୍ଥିତି COMPONENT_REF:
      orig_op0 = op0 = ବୃକ୍ଷ_OPERAND (ପଦସମଷ୍ଟି, 0);
      op1 = ବୃକ୍ଷ_OPERAND (ପଦସମଷ୍ଟି, 1);
      op2 = ବୃକ୍ଷ_OPERAND (ପଦସମଷ୍ଟି, 2);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, lval);
      STRIP_TYPE_NOPS (op0);
      ଯଦି (op0 != orig_op0)
	ret = build3 (COMPONENT_REF, ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି), op0, op1, op2);
      ଯଦି (ret != ପଦସମଷ୍ଟି)
	{
	  ବୃକ୍ଷ_READONLY (ret) = ବୃକ୍ଷ_READONLY (ପଦସମଷ୍ଟି);
	  ବୃକ୍ଷ_THIS_VOLATILE (ret) = ବୃକ୍ଷ_THIS_VOLATILE (ପଦସମଷ୍ଟି);
	}
      ଯଦି (!lval)
	ret = fold (ret);
      ଯାଅ out;

    ସ୍ଥିତି ARRAY_REF:
      orig_op0 = op0 = ବୃକ୍ଷ_OPERAND (ପଦସମଷ୍ଟି, 0);
      orig_op1 = op1 = ବୃକ୍ଷ_OPERAND (ପଦସମଷ୍ଟି, 1);
      op2 = ବୃକ୍ଷ_OPERAND (ପଦସମଷ୍ଟି, 2);
      op3 = ବୃକ୍ଷ_OPERAND (ପଦସମଷ୍ଟି, 3);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, lval);
      STRIP_TYPE_NOPS (op0);
      op1 = c_fully_fold_internal (op1, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, ମିଥ୍ୟା);
      STRIP_TYPE_NOPS (op1);
      /* Fold "foo"[2] in initializers.  */
      ଯଦି (!lval && in_init)
	{
	  ret = c_fold_array_ref (ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି), op0, op1);
	  ଯଦି (ret)
	    ଯାଅ out;
	  ret = ପଦସମଷ୍ଟି;
	}
      ଯଦି (op0 != orig_op0 || op1 != orig_op1)
	ret = build4 (ARRAY_REF, ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି), op0, op1, op2, op3);
      ଯଦି (ret != ପଦସମଷ୍ଟି)
	{
	  ବୃକ୍ଷ_READONLY (ret) = ବୃକ୍ଷ_READONLY (ପଦସମଷ୍ଟି);
	  ବୃକ୍ଷ_SIDE_EFFECTS (ret) = ବୃକ୍ଷ_SIDE_EFFECTS (ପଦସମଷ୍ଟି);
	  ବୃକ୍ଷ_THIS_VOLATILE (ret) = ବୃକ୍ଷ_THIS_VOLATILE (ପଦସମଷ୍ଟି);
	}
      ଯଦି (!lval)
	ret = fold (ret);
      ଯାଅ out;

    ସ୍ଥିତି MODIFY_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି PREDECREMENT_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି PREINCREMENT_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି POSTDECREMENT_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି POSTINCREMENT_ପଦସମଷ୍ଟି:
      op0_lval = ସତ୍ୟ;
      /* FALLTHRU */
    ସ୍ଥିତି COMPOUND_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି PLUS_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି MINUS_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି MULT_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି POINTER_PLUS_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି POINTER_DIFF_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି TRUNC_DIV_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି CEIL_DIV_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି FLOOR_DIV_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି TRUNC_MOD_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି RDIV_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି EXACT_DIV_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି LSHIFT_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି RSHIFT_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି LROTATE_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି RROTATE_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି BIT_IOR_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି BIT_XOR_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି BIT_AND_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି LT_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି LE_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି GT_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି GE_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି EQ_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି NE_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି COMPLEX_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି TRUTH_AND_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି TRUTH_OR_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି TRUTH_XOR_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି UNORDERED_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି ORDERED_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି UNLT_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି UNLE_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି UNGT_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି UNGE_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି UNEQ_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି MEM_REF:
      /* Binary operations evaluating both arguments (increment and
	 decrement are binary internally in GCC).  */
      orig_op0 = op0 = ବୃକ୍ଷ_OPERAND (ପଦସମଷ୍ଟି, 0);
      orig_op1 = op1 = ବୃକ୍ଷ_OPERAND (ପଦସମଷ୍ଟି, 1);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const,
				   op0_lval);
      STRIP_TYPE_NOPS (op0);
      /* The RHS of a MODIFY_EXPR was fully folded when building that
	 expression for the sake of conversion warnings.  */
      ଯଦି (code != MODIFY_ପଦସମଷ୍ଟି)
	op1 = c_fully_fold_internal (op1, in_init, maybe_const_operands,
				     maybe_const_itself, for_int_const, ମିଥ୍ୟା);
      STRIP_TYPE_NOPS (op1);

      ଯଦି (for_int_const && (ବୃକ୍ଷ_CODE (op0) != INTEGER_CST
			    || ବୃକ୍ଷ_CODE (op1) != INTEGER_CST))
	ଯାଅ out;

      ଯଦି (ବୃକ୍ଷ_CODE_CLASS (code) == tcc_comparison
	  && ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (op0)) == NULLPTR_TYPE
	  && ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (op1)) == NULLPTR_TYPE)
	{
	  ବାଛ (code)
	    {
	    ସ୍ଥିତି EQ_ପଦସମଷ୍ଟି:
	      ret = constant_boolean_ଗଣ୍ଠି (ସତ୍ୟ, ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି));
	      ଭାଙ୍ଗ;
	    ସ୍ଥିତି NE_ପଦସମଷ୍ଟି:
	      ret = constant_boolean_ଗଣ୍ଠି (ମିଥ୍ୟା, ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି));
	      ଭାଙ୍ଗ;
	    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	      gcc_unreachable ();
	    }
	  ret = omit_two_operands_loc (loc, ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି), ret,
				       op0, op1);
	}
      ଅନ୍ୟଥା ଯଦି (op0 != orig_op0 || op1 != orig_op1 || in_init)
	ret = in_init
	  ? fold_build2_initializer_loc (loc, code, ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି), op0, op1)
	  : fold_build2_loc (loc, code, ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି), op0, op1);
      ଅନ୍ୟଥା
	ret = fold (ପଦସମଷ୍ଟି);
      ଯଦି (ବୃକ୍ଷ_OVERFLOW_P (ret)
	  && !ବୃକ୍ଷ_OVERFLOW_P (op0)
	  && !(ଦ୍ୱିମିକ_CLASS_P (op0) && ବୃକ୍ଷ_OVERFLOW_P (ବୃକ୍ଷ_OPERAND (op0, 1)))
	  && !ବୃକ୍ଷ_OVERFLOW_P (op1))
	overflow_warning (ପଦସମଷ୍ଟି_LOC_OR_LOC (ପଦସମଷ୍ଟି, ନିବେଶ_location), ret, ପଦସମଷ୍ଟି);
      ଯଦି (code == LSHIFT_ପଦସମଷ୍ଟି
	  && ବୃକ୍ଷ_CODE (orig_op0) != INTEGER_CST
	  && (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (orig_op0)) == INTEGER_TYPE
	      || ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (orig_op0)) == BITINT_TYPE)
	  && ବୃକ୍ଷ_CODE (op0) == INTEGER_CST
	  && c_inhibit_evaluation_warnings == 0
	  && !TYPE_OVERFLOW_WRAPS (ବୃକ୍ଷ_TYPE (orig_op0))
	  && ବୃକ୍ଷ_int_cst_sgn (op0) < 0)
	warning_at (loc, OPT_Wshift_negative_ମୂଲ୍ୟ,
		    "left shift of negative value");
      ଯଦି ((code == LSHIFT_ପଦସମଷ୍ଟି
	   || code == RSHIFT_ପଦସମଷ୍ଟି
	   || code == LROTATE_ପଦସମଷ୍ଟି
	   || code == RROTATE_ପଦସମଷ୍ଟି)
	  && ବୃକ୍ଷ_CODE (orig_op1) != INTEGER_CST
	  && ବୃକ୍ଷ_CODE (op1) == INTEGER_CST
	  && ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (orig_op1)) == INTEGER_TYPE
	  && c_inhibit_evaluation_warnings == 0)
	{
	  ଯଦି (ବୃକ୍ଷ_int_cst_sgn (op1) < 0)
	    warning_at (loc, OPT_Wshift_ଗଣନା_negative,
			(code == LSHIFT_ପଦସମଷ୍ଟି
			 ? G_("left shift count is negative")
			 : G_("right shift count is negative")));
	  ଅନ୍ୟଥା ଯଦି ((ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (orig_op0)) == INTEGER_TYPE
		    || ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (orig_op0)) == BITINT_TYPE
		    || ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (orig_op0)) == FIXED_POINT_TYPE)
		   && compare_ବୃକ୍ଷ_int (op1,
					TYPE_PRECISION (ବୃକ୍ଷ_TYPE (orig_op0)))
		      >= 0
		   && !warning_suppressed_p (ପଦସମଷ୍ଟି, OPT_Wshift_ଗଣନା_overflow))
	    warning_at (loc, OPT_Wshift_ଗଣନା_overflow,
			(code == LSHIFT_ପଦସମଷ୍ଟି
			 ? G_("left shift count >= width of type")
			 : G_("right shift count >= width of type")));
	  ଅନ୍ୟଥା ଯଦି (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (orig_op0)) == VECTOR_TYPE
		   && compare_ବୃକ୍ଷ_int (op1,
					TYPE_PRECISION (ବୃକ୍ଷ_TYPE (ବୃକ୍ଷ_TYPE (orig_op0))))
		      >= 0)
	    warning_at (loc, OPT_Wshift_ଗଣନା_overflow,
			code == LSHIFT_ପଦସମଷ୍ଟି
			? G_("left shift count >= width of vector element")
			: G_("right shift count >= width of vector element"));
	}
      ଯଦି (code == LSHIFT_ପଦସମଷ୍ଟି
	  /* If either OP0 has been folded to INTEGER_CST...  */
	  && ((ବୃକ୍ଷ_CODE (orig_op0) != INTEGER_CST
	       && (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (orig_op0)) == INTEGER_TYPE
		   || ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (orig_op0)) == BITINT_TYPE)
	       && ବୃକ୍ଷ_CODE (op0) == INTEGER_CST)
	      /* ...or if OP1 has been folded to INTEGER_CST...  */
	      || (ବୃକ୍ଷ_CODE (orig_op1) != INTEGER_CST
		  && (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (orig_op1)) == INTEGER_TYPE
		      || ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (orig_op1)) == BITINT_TYPE)
		  && ବୃକ୍ଷ_CODE (op1) == INTEGER_CST))
	  && c_inhibit_evaluation_warnings == 0)
	/* ...then maybe we can detect an overflow.  */
	maybe_warn_shift_overflow (loc, op0, op1);
      ଯଦି ((code == TRUNC_DIV_ପଦସମଷ୍ଟି
	   || code == CEIL_DIV_ପଦସମଷ୍ଟି
	   || code == FLOOR_DIV_ପଦସମଷ୍ଟି
	   || code == EXACT_DIV_ପଦସମଷ୍ଟି
	   || code == TRUNC_MOD_ପଦସମଷ୍ଟି)
	  && ବୃକ୍ଷ_CODE (orig_op1) != INTEGER_CST
	  && ବୃକ୍ଷ_CODE (op1) == INTEGER_CST
	  && (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (orig_op0)) == INTEGER_TYPE
	      || ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (orig_op0)) == BITINT_TYPE
	      || ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (orig_op0)) == FIXED_POINT_TYPE)
	  && (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (orig_op1)) == INTEGER_TYPE
	      || ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (orig_op1)) == BITINT_TYPE))
	warn_for_div_by_zero (loc, op1);
      ଯଦି (code == MEM_REF
	  && ret != ପଦସମଷ୍ଟି
	  && ବୃକ୍ଷ_CODE (ret) == MEM_REF)
	{
	  ବୃକ୍ଷ_READONLY (ret) = ବୃକ୍ଷ_READONLY (ପଦସମଷ୍ଟି);
	  ବୃକ୍ଷ_SIDE_EFFECTS (ret) = ବୃକ୍ଷ_SIDE_EFFECTS (ପଦସମଷ୍ଟି);
	  ବୃକ୍ଷ_THIS_VOLATILE (ret) = ବୃକ୍ଷ_THIS_VOLATILE (ପଦସମଷ୍ଟି);
	}
      ଯାଅ out;

    ସ୍ଥିତି ADDR_ପଦସମଷ୍ଟି:
      op0_lval = ସତ୍ୟ;
      ଯାଅ unary;
    ସ୍ଥିତି REALPART_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି IMAGPART_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି VIEW_CONVERT_ପଦସମଷ୍ଟି:
      op0_lval = lval;
      /* FALLTHRU */
    ସ୍ଥିତି INDIRECT_REF:
    ସ୍ଥିତି FIX_TRUNC_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି FLOAT_ପଦସମଷ୍ଟି:
    CASE_CONVERT:
    ସ୍ଥିତି ADDR_SPACE_CONVERT_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି NON_LVALUE_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି NEGATE_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି BIT_NOT_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି TRUTH_NOT_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି CONJ_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି PAREN_ପଦସମଷ୍ଟି:
    unary:
      /* Unary operations.  */
      orig_op0 = op0 = ବୃକ୍ଷ_OPERAND (ପଦସମଷ୍ଟି, 0);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const,
				   op0_lval);
      STRIP_TYPE_NOPS (op0);

      ଯଦି (for_int_const && ବୃକ୍ଷ_CODE (op0) != INTEGER_CST)
	ଯାଅ out;

      /* ??? Cope with user tricks that amount to offsetof.  The middle-end is
	 not prepared to deal with them if they occur in initializers.  */
      ଯଦି (op0 != orig_op0
	  && code == ADDR_ପଦସମଷ୍ଟି
	  && (op1 = get_base_address (op0)) != NULL_ବୃକ୍ଷ
	  && INDIRECT_REF_P (op1)
	  && ବୃକ୍ଷ_CONSTANT (ବୃକ୍ଷ_OPERAND (op1, 0)))
	ret = fold_offsetof (op0, ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି));
      ଅନ୍ୟଥା ଯଦି (op0 != orig_op0 || in_init)
	ret = in_init
	  ? fold_build1_initializer_loc (loc, code, ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି), op0)
	  : fold_build1_loc (loc, code, ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି), op0);
      ଅନ୍ୟଥା
	ret = fold (ପଦସମଷ୍ଟି);
      ଯଦି (code == INDIRECT_REF
	  && ret != ପଦସମଷ୍ଟି
	  && INDIRECT_REF_P (ret))
	{
	  ବୃକ୍ଷ_READONLY (ret) = ବୃକ୍ଷ_READONLY (ପଦସମଷ୍ଟି);
	  ବୃକ୍ଷ_SIDE_EFFECTS (ret) = ବୃକ୍ଷ_SIDE_EFFECTS (ପଦସମଷ୍ଟି);
	  ବୃକ୍ଷ_THIS_VOLATILE (ret) = ବୃକ୍ଷ_THIS_VOLATILE (ପଦସମଷ୍ଟି);
	}
      ବାଛ (code)
	{
	ସ୍ଥିତି FIX_TRUNC_ପଦସମଷ୍ଟି:
	ସ୍ଥିତି FLOAT_ପଦସମଷ୍ଟି:
	CASE_CONVERT:
	  /* Don't warn about explicit conversions.  We will already
	     have warned about suspect implicit conversions.  */
	  ଭାଙ୍ଗ;

	ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
	  ଯଦି (ବୃକ୍ଷ_OVERFLOW_P (ret) && !ବୃକ୍ଷ_OVERFLOW_P (op0))
	    overflow_warning (ପଦସମଷ୍ଟି_LOCATION (ପଦସମଷ୍ଟି), ret, op0);
	  ଭାଙ୍ଗ;
	}
      ଯାଅ out;

    ସ୍ଥିତି TRUTH_ANDIF_ପଦସମଷ୍ଟି:
    ସ୍ଥିତି TRUTH_ORIF_ପଦସମଷ୍ଟି:
      /* Binary operations not necessarily evaluating both
	 arguments.  */
      orig_op0 = op0 = ବୃକ୍ଷ_OPERAND (ପଦସମଷ୍ଟି, 0);
      orig_op1 = op1 = ବୃକ୍ଷ_OPERAND (ପଦସମଷ୍ଟି, 1);
      op0 = c_fully_fold_internal (op0, in_init, &op0_const, &op0_const_self,
				   for_int_const, ମିଥ୍ୟା);
      STRIP_TYPE_NOPS (op0);

      unused_p = (op0 == (code == TRUTH_ANDIF_ପଦସମଷ୍ଟି
			  ? truthvalue_false_ଗଣ୍ଠି
			  : truthvalue_true_ଗଣ୍ଠି));
      c_disable_warnings (unused_p);
      op1 = c_fully_fold_internal (op1, in_init, &op1_const, &op1_const_self,
				   for_int_const, ମିଥ୍ୟା);
      STRIP_TYPE_NOPS (op1);
      c_enable_warnings (unused_p);

      ଯଦି (for_int_const
	  && (ବୃକ୍ଷ_CODE (op0) != INTEGER_CST
	      /* Require OP1 be an INTEGER_CST only if it's evaluated.  */
	      || (!unused_p && ବୃକ୍ଷ_CODE (op1) != INTEGER_CST)))
	ଯାଅ out;

      ଯଦି (op0 != orig_op0 || op1 != orig_op1 || in_init)
	ret = in_init
	  ? fold_build2_initializer_loc (loc, code, ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି), op0, op1)
	  : fold_build2_loc (loc, code, ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି), op0, op1);
      ଅନ୍ୟଥା
	ret = fold (ପଦସମଷ୍ଟି);
      *maybe_const_operands &= op0_const;
      *maybe_const_itself &= op0_const_self;
      ଯଦି (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && (code == TRUTH_ANDIF_ପଦସମଷ୍ଟି
		? op0 == truthvalue_false_ଗଣ୍ଠି
		: op0 == truthvalue_true_ଗଣ୍ଠି)))
	*maybe_const_operands &= op1_const;
      ଯଦି (!(op0_const
	    && op0_const_self
	    && (code == TRUTH_ANDIF_ପଦସମଷ୍ଟି
		? op0 == truthvalue_false_ଗଣ୍ଠି
		: op0 == truthvalue_true_ଗଣ୍ଠି)))
	*maybe_const_itself &= op1_const_self;
      ଯାଅ out;

    ସ୍ଥିତି COND_ପଦସମଷ୍ଟି:
      orig_op0 = op0 = ବୃକ୍ଷ_OPERAND (ପଦସମଷ୍ଟି, 0);
      orig_op1 = op1 = ବୃକ୍ଷ_OPERAND (ପଦସମଷ୍ଟି, 1);
      orig_op2 = op2 = ବୃକ୍ଷ_OPERAND (ପଦସମଷ୍ଟି, 2);
      op0 = c_fully_fold_internal (op0, in_init, &op0_const, &op0_const_self,
				   for_int_const, ମିଥ୍ୟା);

      STRIP_TYPE_NOPS (op0);
      c_disable_warnings (op0 == truthvalue_false_ଗଣ୍ଠି);
      op1 = c_fully_fold_internal (op1, in_init, &op1_const, &op1_const_self,
				   for_int_const, ମିଥ୍ୟା);
      STRIP_TYPE_NOPS (op1);
      c_enable_warnings (op0 == truthvalue_false_ଗଣ୍ଠି);

      c_disable_warnings (op0 == truthvalue_true_ଗଣ୍ଠି);
      op2 = c_fully_fold_internal (op2, in_init, &op2_const, &op2_const_self,
				   for_int_const, ମିଥ୍ୟା);
      STRIP_TYPE_NOPS (op2);
      c_enable_warnings (op0 == truthvalue_true_ଗଣ୍ଠି);

      ଯଦି (for_int_const
	  && (ବୃକ୍ଷ_CODE (op0) != INTEGER_CST
	      /* Only the evaluated operand must be an INTEGER_CST.  */
	      || (op0 == truthvalue_true_ଗଣ୍ଠି
		  ? ବୃକ୍ଷ_CODE (op1) != INTEGER_CST
		  : ବୃକ୍ଷ_CODE (op2) != INTEGER_CST)))
	ଯାଅ out;

      ଯଦି (op0 != orig_op0 || op1 != orig_op1 || op2 != orig_op2)
	ret = fold_build3_loc (loc, code, ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି), op0, op1, op2);
      ଅନ୍ୟଥା
	ret = fold (ପଦସମଷ୍ଟି);
      *maybe_const_operands &= op0_const;
      *maybe_const_itself &= op0_const_self;
      ଯଦି (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && op0 == truthvalue_false_ଗଣ୍ଠି))
	*maybe_const_operands &= op1_const;
      ଯଦି (!(op0_const
	    && op0_const_self
	    && op0 == truthvalue_false_ଗଣ୍ଠି))
	*maybe_const_itself &= op1_const_self;
      ଯଦି (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && op0 == truthvalue_true_ଗଣ୍ଠି))
	*maybe_const_operands &= op2_const;
      ଯଦି (!(op0_const
	    && op0_const_self
	    && op0 == truthvalue_true_ଗଣ୍ଠି))
	*maybe_const_itself &= op2_const_self;
      ଯାଅ out;

    ସ୍ଥିତି VEC_COND_ପଦସମଷ୍ଟି:
      orig_op0 = op0 = ବୃକ୍ଷ_OPERAND (ପଦସମଷ୍ଟି, 0);
      orig_op1 = op1 = ବୃକ୍ଷ_OPERAND (ପଦସମଷ୍ଟି, 1);
      orig_op2 = op2 = ବୃକ୍ଷ_OPERAND (ପଦସମଷ୍ଟି, 2);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, ମିଥ୍ୟା);
      STRIP_TYPE_NOPS (op0);
      op1 = c_fully_fold_internal (op1, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, ମିଥ୍ୟା);
      STRIP_TYPE_NOPS (op1);
      op2 = c_fully_fold_internal (op2, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, ମିଥ୍ୟା);
      STRIP_TYPE_NOPS (op2);

      ଯଦି (op0 != orig_op0 || op1 != orig_op1 || op2 != orig_op2)
	ret = fold_build3_loc (loc, code, ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି), op0, op1, op2);
      ଅନ୍ୟଥା
	ret = fold (ପଦସମଷ୍ଟି);
      ଯାଅ out;

    ସ୍ଥିତି EXCESS_PRECISION_ପଦସମଷ୍ଟି:
      /* Each case where an operand with excess precision may be
	 encountered must remove the EXCESS_PRECISION_EXPR around
	 inner operands and possibly put one around the whole
	 expression or possibly convert to the semantic type (which
	 c_fully_fold does); we cannot tell at this stage which is
	 appropriate in any particular case.  */
      gcc_unreachable ();

    ସ୍ଥିତି SAVE_ପଦସମଷ୍ଟି:
      /* Make sure to fold the contents of a SAVE_EXPR exactly once.  */
      op0 = ବୃକ୍ଷ_OPERAND (ପଦସମଷ୍ଟି, 0);
      ଯଦି (!SAVE_ପଦସମଷ୍ଟି_FOLDED_P (ପଦସମଷ୍ଟି))
	{
	  op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				       maybe_const_itself, for_int_const,
				       ମିଥ୍ୟା);
	  ବୃକ୍ଷ_OPERAND (ପଦସମଷ୍ଟି, 0) = op0;
	  SAVE_ପଦସମଷ୍ଟି_FOLDED_P (ପଦସମଷ୍ଟି) = ସତ୍ୟ;
	}
      /* Return the SAVE_EXPR operand if it is invariant.  */
      ଯଦି (ବୃକ୍ଷ_invariant_p (op0))
	ret = op0;
      ଯାଅ out;

    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
      /* Various codes may appear through folding built-in functions
	 and their arguments.  */
      ଯାଅ out;
    }

 out:
  /* Some folding may introduce NON_LVALUE_EXPRs; all lvalue checks
     have been done by this point, so remove them again.  */
  nowarning |= warning_suppressed_p (ret, OPT_Woverflow);
  STRIP_TYPE_NOPS (ret);
  ଯଦି (nowarning && !warning_suppressed_p (ret, OPT_Woverflow))
    {
      ଯଦି (!CAN_HAVE_LOCATION_P (ret))
	ret = build1 (NOP_ପଦସମଷ୍ଟି, ବୃକ୍ଷ_TYPE (ret), ret);
      suppress_warning (ret, OPT_Woverflow);
    }
  ଯଦି (ret != ପଦସମଷ୍ଟି)
    {
      protected_set_ପଦସମଷ୍ଟି_location (ret, loc);
      ଯଦି (IS_ପଦସମଷ୍ଟି_CODE_CLASS (kind))
	set_source_range (ret, old_range.m_start, old_range.m_finish);
    }
  ଫେରନ୍ତୁ ret;
}

/* Fold X for consideration by one of the warning functions when checking
   whether an expression has a constant value.  */

ବୃକ୍ଷ
fold_for_warn (ବୃକ୍ଷ x)
{
  /* The C front-end has already folded X appropriately.  */
  ଫେରନ୍ତୁ x;
}
