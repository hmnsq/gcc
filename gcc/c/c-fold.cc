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

#include "config.h"
#include "system.h"
#include "coretypes.h"
#include "target.h"
#include "function.h"
#include "bitmap.h"
#include "c-tree.h"
#include "intl.h"
#include "gimplify.h"

static tree c_fully_fold_internal (tree expr, bool, bool *, bool *, bool,
				   bool);

/* If DISABLE is true, stop issuing warnings.  This is used when
   parsing code that we know will not be executed.  This function may
   be called multiple times, and works as a stack.  */

static void
c_disable_warnings (bool disable)
{
  အကယ်၍ (disable)
    {
      ++c_inhibit_evaluation_warnings;
    }
}

/* If ENABLE is true, re-enable issuing warnings.  */

static void
c_enable_warnings (bool enable)
{
  အကယ်၍ (enable)
    {
      --c_inhibit_evaluation_warnings;
    }
}

/* Try to fold ARRAY_REF ary[index] if possible and not handled by
   normal fold, return NULL_TREE otherwise.  */

static tree
c_fold_array_ref (tree type, tree ary, tree index)
{
  အကယ်၍ (TREE_CODE (ary) != STRING_CST
      || TREE_CODE (index) != INTEGER_CST
      || TREE_OVERFLOW (index)
      || TREE_CODE (TREE_TYPE (ary)) != ARRAY_TYPE
      || !tree_fits_uhwi_p (index))
    ပြန်ပေး NULL_TREE;

  tree elem_type = TREE_TYPE (TREE_TYPE (ary));
  unsigned elem_nchars = (TYPE_PRECISION (elem_type)
			  / TYPE_PRECISION (char_type_node));
  unsigned len = (unsigned) TREE_STRING_LENGTH (ary) / elem_nchars;
  tree nelts_minus_one = array_type_nelts_minus_one (TREE_TYPE (ary));
  bool dummy1 = true, dummy2 = true;
  nelts_minus_one = c_fully_fold_internal (nelts_minus_one, true, &dummy1,
					   &dummy2, false, false);
  unsigned HOST_WIDE_INT i = tree_to_uhwi (index);
  အကယ်၍ (!tree_int_cst_le (index, nelts_minus_one)
      || i >= len
      || i + elem_nchars > len)
    ပြန်ပေး NULL_TREE;

  အကယ်၍ (elem_nchars == 1)
    ပြန်ပေး build_int_cst (type, TREE_STRING_POINTER (ary)[i]);

  const unsigned var_na *ptr
    = ((const unsigned var_na *)TREE_STRING_POINTER (ary) + i * elem_nchars);
  ပြန်ပေး native_interpret_expr (type, ptr, elem_nchars);
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

tree
c_fully_fold (tree expr, bool in_init, bool *maybe_const, bool lval)
{
  tree ret;
  tree eptype = NULL_TREE;
  bool dummy = true;
  bool maybe_const_itself = true;
  location_t loc = EXPR_LOCATION (expr);

  အကယ်၍ (!maybe_const)
    maybe_const = &dummy;
  အကယ်၍ (TREE_CODE (expr) == EXCESS_PRECISION_EXPR)
    {
      eptype = TREE_TYPE (expr);
      expr = TREE_OPERAND (expr, 0);
    }
  ret = c_fully_fold_internal (expr, in_init, maybe_const,
			       &maybe_const_itself, false, lval);
  အကယ်၍ (eptype)
    ret = fold_convert_loc (loc, eptype, ret);
  *maybe_const &= maybe_const_itself;
  ပြန်ပေး ret;
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

static tree
c_fully_fold_internal (tree expr, bool in_init, bool *maybe_const_operands,
		       bool *maybe_const_itself, bool for_int_const, bool lval)
{
  tree ret = expr;
  ga_nanaa tree_code code = TREE_CODE (expr);
  ga_nanaa tree_code_class kind = TREE_CODE_CLASS (code);
  location_t loc = EXPR_LOCATION (expr);
  tree op0, op1, op2, op3;
  tree orig_op0, orig_op1, orig_op2;
  bool op0_const = true, op1_const = true, op2_const = true;
  bool op0_const_self = true, op1_const_self = true, op2_const_self = true;
  bool nowarning = warning_suppressed_p (expr, OPT_Woverflow);
  bool unused_p;
  bool op0_lval = false;
  source_range old_range;

  /* Constants, declarations, statements, errors, and anything else not
     counted as an expression cannot usefully be folded further at this
     point.  */
  အကယ်၍ (!IS_EXPR_CODE_CLASS (kind) || kind == tcc_statement)
    {
      /* Except for variables which we can optimize to its initializer.  */
      အကယ်၍ (VAR_P (expr) && !lval && (optimize || in_init))
	{
	  အကယ်၍ (in_init)
	    ret = decl_constant_value_1 (expr, true);
	  မဟုတ်ပါက
	    {
	      ret = decl_constant_value (expr);
	      အကယ်၍ (ret != expr
		  && (TYPE_MODE (TREE_TYPE (ret)) == BLKmode
		      || TREE_CODE (TREE_TYPE (ret)) == ARRAY_TYPE))
		ပြန်ပေး expr;
	    }
	  /* Avoid unwanted tree sharing between the initializer and current
	     function's body where the tree can be modified e.g. by the
	     gimplifier.  */
	  အကယ်၍ (ret != expr && TREE_STATIC (expr))
	    ret = unshare_expr (ret);
	  ပြန်ပေး ret;
	}
      ပြန်ပေး expr;
    }

  အကယ်၍ (IS_EXPR_CODE_CLASS (kind))
    old_range = EXPR_LOCATION_RANGE (expr);

  /* Operands of variable-length expressions (function calls) have
     already been folded, as have __builtin_* function calls, and such
     expressions cannot occur in constant expressions.  */
  အကယ်၍ (kind == tcc_vl_exp)
    {
      *maybe_const_operands = false;
      ret = fold (expr);
      goto out;
    }

  အကယ်၍ (code == C_MAYBE_CONST_EXPR)
    {
      tree pre = C_MAYBE_CONST_EXPR_PRE (expr);
      tree inner = C_MAYBE_CONST_EXPR_EXPR (expr);
      အကယ်၍ (C_MAYBE_CONST_EXPR_NON_CONST (expr))
	*maybe_const_operands = false;
      အကယ်၍ (C_MAYBE_CONST_EXPR_INT_OPERANDS (expr))
	{
	  *maybe_const_itself = false;
	  inner = c_fully_fold_internal (inner, in_init, maybe_const_operands,
					 maybe_const_itself, true, lval);
	}
      အကယ်၍ (pre && !in_init)
	ret = build2 (COMPOUND_EXPR, TREE_TYPE (expr), pre, inner);
      မဟုတ်ပါက
	ret = inner;
      goto out;
    }

  /* Assignment, increment, decrement, function call and comma
     operators, and statement expressions, cannot occur in constant
     expressions if evaluated / outside of sizeof.  (Function calls
     were handled above, though VA_ARG_EXPR is treated like a function
     call here, and statement expressions are handled through
     C_MAYBE_CONST_EXPR to avoid folding inside them.)  */
  switch (code)
    {
    pak_sa MODIFY_EXPR:
    pak_sa PREDECREMENT_EXPR:
    pak_sa PREINCREMENT_EXPR:
    pak_sa POSTDECREMENT_EXPR:
    pak_sa POSTINCREMENT_EXPR:
    pak_sa COMPOUND_EXPR:
      *maybe_const_operands = false;
      bha_nga;

    pak_sa VA_ARG_EXPR:
    pak_sa TARGET_EXPR:
    pak_sa BIND_EXPR:
    pak_sa OBJ_TYPE_REF:
      *maybe_const_operands = false;
      ret = fold (expr);
      goto out;

    default:
      bha_nga;
    }

  /* Fold individual tree codes as appropriate.  */
  switch (code)
    {
    pak_sa COMPOUND_LITERAL_EXPR:
      /* Any non-constancy will have been marked in a containing
	 C_MAYBE_CONST_EXPR; there is no more folding to do here.  */
      goto out;

    pak_sa COMPONENT_REF:
      orig_op0 = op0 = TREE_OPERAND (expr, 0);
      op1 = TREE_OPERAND (expr, 1);
      op2 = TREE_OPERAND (expr, 2);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, lval);
      STRIP_TYPE_NOPS (op0);
      အကယ်၍ (op0 != orig_op0)
	ret = build3 (COMPONENT_REF, TREE_TYPE (expr), op0, op1, op2);
      အကယ်၍ (ret != expr)
	{
	  TREE_READONLY (ret) = TREE_READONLY (expr);
	  TREE_THIS_VOLATILE (ret) = TREE_THIS_VOLATILE (expr);
	}
      အကယ်၍ (!lval)
	ret = fold (ret);
      goto out;

    pak_sa ARRAY_REF:
      orig_op0 = op0 = TREE_OPERAND (expr, 0);
      orig_op1 = op1 = TREE_OPERAND (expr, 1);
      op2 = TREE_OPERAND (expr, 2);
      op3 = TREE_OPERAND (expr, 3);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, lval);
      STRIP_TYPE_NOPS (op0);
      op1 = c_fully_fold_internal (op1, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, false);
      STRIP_TYPE_NOPS (op1);
      /* Fold "foo"[2] in initializers.  */
      အကယ်၍ (!lval && in_init)
	{
	  ret = c_fold_array_ref (TREE_TYPE (expr), op0, op1);
	  အကယ်၍ (ret)
	    goto out;
	  ret = expr;
	}
      အကယ်၍ (op0 != orig_op0 || op1 != orig_op1)
	ret = build4 (ARRAY_REF, TREE_TYPE (expr), op0, op1, op2, op3);
      အကယ်၍ (ret != expr)
	{
	  TREE_READONLY (ret) = TREE_READONLY (expr);
	  TREE_SIDE_EFFECTS (ret) = TREE_SIDE_EFFECTS (expr);
	  TREE_THIS_VOLATILE (ret) = TREE_THIS_VOLATILE (expr);
	}
      အကယ်၍ (!lval)
	ret = fold (ret);
      goto out;

    pak_sa MODIFY_EXPR:
    pak_sa PREDECREMENT_EXPR:
    pak_sa PREINCREMENT_EXPR:
    pak_sa POSTDECREMENT_EXPR:
    pak_sa POSTINCREMENT_EXPR:
      op0_lval = true;
      /* FALLTHRU */
    pak_sa COMPOUND_EXPR:
    pak_sa PLUS_EXPR:
    pak_sa MINUS_EXPR:
    pak_sa MULT_EXPR:
    pak_sa POINTER_PLUS_EXPR:
    pak_sa POINTER_DIFF_EXPR:
    pak_sa TRUNC_DIV_EXPR:
    pak_sa CEIL_DIV_EXPR:
    pak_sa FLOOR_DIV_EXPR:
    pak_sa TRUNC_MOD_EXPR:
    pak_sa RDIV_EXPR:
    pak_sa EXACT_DIV_EXPR:
    pak_sa LSHIFT_EXPR:
    pak_sa RSHIFT_EXPR:
    pak_sa LROTATE_EXPR:
    pak_sa RROTATE_EXPR:
    pak_sa BIT_IOR_EXPR:
    pak_sa BIT_XOR_EXPR:
    pak_sa BIT_AND_EXPR:
    pak_sa LT_EXPR:
    pak_sa LE_EXPR:
    pak_sa GT_EXPR:
    pak_sa GE_EXPR:
    pak_sa EQ_EXPR:
    pak_sa NE_EXPR:
    pak_sa COMPLEX_EXPR:
    pak_sa TRUTH_AND_EXPR:
    pak_sa TRUTH_OR_EXPR:
    pak_sa TRUTH_XOR_EXPR:
    pak_sa UNORDERED_EXPR:
    pak_sa ORDERED_EXPR:
    pak_sa UNLT_EXPR:
    pak_sa UNLE_EXPR:
    pak_sa UNGT_EXPR:
    pak_sa UNGE_EXPR:
    pak_sa UNEQ_EXPR:
    pak_sa MEM_REF:
      /* Binary operations evaluating both arguments (increment and
	 decrement are binary internally in GCC).  */
      orig_op0 = op0 = TREE_OPERAND (expr, 0);
      orig_op1 = op1 = TREE_OPERAND (expr, 1);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const,
				   op0_lval);
      STRIP_TYPE_NOPS (op0);
      /* The RHS of a MODIFY_EXPR was fully folded when building that
	 expression for the sake of conversion warnings.  */
      အကယ်၍ (code != MODIFY_EXPR)
	op1 = c_fully_fold_internal (op1, in_init, maybe_const_operands,
				     maybe_const_itself, for_int_const, false);
      STRIP_TYPE_NOPS (op1);

      အကယ်၍ (for_int_const && (TREE_CODE (op0) != INTEGER_CST
			    || TREE_CODE (op1) != INTEGER_CST))
	goto out;

      အကယ်၍ (TREE_CODE_CLASS (code) == tcc_comparison
	  && TREE_CODE (TREE_TYPE (op0)) == NULLPTR_TYPE
	  && TREE_CODE (TREE_TYPE (op1)) == NULLPTR_TYPE)
	{
	  switch (code)
	    {
	    pak_sa EQ_EXPR:
	      ret = constant_boolean_node (true, TREE_TYPE (expr));
	      bha_nga;
	    pak_sa NE_EXPR:
	      ret = constant_boolean_node (false, TREE_TYPE (expr));
	      bha_nga;
	    default:
	      gcc_unreachable ();
	    }
	  ret = omit_two_operands_loc (loc, TREE_TYPE (expr), ret,
				       op0, op1);
	}
      မဟုတ်ပါက အကယ်၍ (op0 != orig_op0 || op1 != orig_op1 || in_init)
	ret = in_init
	  ? fold_build2_initializer_loc (loc, code, TREE_TYPE (expr), op0, op1)
	  : fold_build2_loc (loc, code, TREE_TYPE (expr), op0, op1);
      မဟုတ်ပါက
	ret = fold (expr);
      အကယ်၍ (TREE_OVERFLOW_P (ret)
	  && !TREE_OVERFLOW_P (op0)
	  && !(BINARY_CLASS_P (op0) && TREE_OVERFLOW_P (TREE_OPERAND (op0, 1)))
	  && !TREE_OVERFLOW_P (op1))
	overflow_warning (EXPR_LOC_OR_LOC (expr, input_location), ret, expr);
      အကယ်၍ (code == LSHIFT_EXPR
	  && TREE_CODE (orig_op0) != INTEGER_CST
	  && (TREE_CODE (TREE_TYPE (orig_op0)) == INTEGER_TYPE
	      || TREE_CODE (TREE_TYPE (orig_op0)) == BITINT_TYPE)
	  && TREE_CODE (op0) == INTEGER_CST
	  && c_inhibit_evaluation_warnings == 0
	  && !TYPE_OVERFLOW_WRAPS (TREE_TYPE (orig_op0))
	  && tree_int_cst_sgn (op0) < 0)
	warning_at (loc, OPT_Wshift_negative_value,
		    "left shift of negative value");
      အကယ်၍ ((code == LSHIFT_EXPR
	   || code == RSHIFT_EXPR
	   || code == LROTATE_EXPR
	   || code == RROTATE_EXPR)
	  && TREE_CODE (orig_op1) != INTEGER_CST
	  && TREE_CODE (op1) == INTEGER_CST
	  && TREE_CODE (TREE_TYPE (orig_op1)) == INTEGER_TYPE
	  && c_inhibit_evaluation_warnings == 0)
	{
	  အကယ်၍ (tree_int_cst_sgn (op1) < 0)
	    warning_at (loc, OPT_Wshift_count_negative,
			(code == LSHIFT_EXPR
			 ? G_("left shift count is negative")
			 : G_("right shift count is negative")));
	  မဟုတ်ပါက အကယ်၍ ((TREE_CODE (TREE_TYPE (orig_op0)) == INTEGER_TYPE
		    || TREE_CODE (TREE_TYPE (orig_op0)) == BITINT_TYPE
		    || TREE_CODE (TREE_TYPE (orig_op0)) == FIXED_POINT_TYPE)
		   && compare_tree_int (op1,
					TYPE_PRECISION (TREE_TYPE (orig_op0)))
		      >= 0
		   && !warning_suppressed_p (expr, OPT_Wshift_count_overflow))
	    warning_at (loc, OPT_Wshift_count_overflow,
			(code == LSHIFT_EXPR
			 ? G_("left shift count >= width of type")
			 : G_("right shift count >= width of type")));
	  မဟုတ်ပါက အကယ်၍ (TREE_CODE (TREE_TYPE (orig_op0)) == VECTOR_TYPE
		   && compare_tree_int (op1,
					TYPE_PRECISION (TREE_TYPE (TREE_TYPE (orig_op0))))
		      >= 0)
	    warning_at (loc, OPT_Wshift_count_overflow,
			code == LSHIFT_EXPR
			? G_("left shift count >= width of vector element")
			: G_("right shift count >= width of vector element"));
	}
      အကယ်၍ (code == LSHIFT_EXPR
	  /* If either OP0 has been folded to INTEGER_CST...  */
	  && ((TREE_CODE (orig_op0) != INTEGER_CST
	       && (TREE_CODE (TREE_TYPE (orig_op0)) == INTEGER_TYPE
		   || TREE_CODE (TREE_TYPE (orig_op0)) == BITINT_TYPE)
	       && TREE_CODE (op0) == INTEGER_CST)
	      /* ...or if OP1 has been folded to INTEGER_CST...  */
	      || (TREE_CODE (orig_op1) != INTEGER_CST
		  && (TREE_CODE (TREE_TYPE (orig_op1)) == INTEGER_TYPE
		      || TREE_CODE (TREE_TYPE (orig_op1)) == BITINT_TYPE)
		  && TREE_CODE (op1) == INTEGER_CST))
	  && c_inhibit_evaluation_warnings == 0)
	/* ...then maybe we can detect an overflow.  */
	maybe_warn_shift_overflow (loc, op0, op1);
      အကယ်၍ ((code == TRUNC_DIV_EXPR
	   || code == CEIL_DIV_EXPR
	   || code == FLOOR_DIV_EXPR
	   || code == EXACT_DIV_EXPR
	   || code == TRUNC_MOD_EXPR)
	  && TREE_CODE (orig_op1) != INTEGER_CST
	  && TREE_CODE (op1) == INTEGER_CST
	  && (TREE_CODE (TREE_TYPE (orig_op0)) == INTEGER_TYPE
	      || TREE_CODE (TREE_TYPE (orig_op0)) == BITINT_TYPE
	      || TREE_CODE (TREE_TYPE (orig_op0)) == FIXED_POINT_TYPE)
	  && (TREE_CODE (TREE_TYPE (orig_op1)) == INTEGER_TYPE
	      || TREE_CODE (TREE_TYPE (orig_op1)) == BITINT_TYPE))
	warn_for_div_by_zero (loc, op1);
      အကယ်၍ (code == MEM_REF
	  && ret != expr
	  && TREE_CODE (ret) == MEM_REF)
	{
	  TREE_READONLY (ret) = TREE_READONLY (expr);
	  TREE_SIDE_EFFECTS (ret) = TREE_SIDE_EFFECTS (expr);
	  TREE_THIS_VOLATILE (ret) = TREE_THIS_VOLATILE (expr);
	}
      goto out;

    pak_sa ADDR_EXPR:
      op0_lval = true;
      goto unary;
    pak_sa REALPART_EXPR:
    pak_sa IMAGPART_EXPR:
    pak_sa VIEW_CONVERT_EXPR:
      op0_lval = lval;
      /* FALLTHRU */
    pak_sa INDIRECT_REF:
    pak_sa FIX_TRUNC_EXPR:
    pak_sa FLOAT_EXPR:
    CASE_CONVERT:
    pak_sa ADDR_SPACE_CONVERT_EXPR:
    pak_sa NON_LVALUE_EXPR:
    pak_sa NEGATE_EXPR:
    pak_sa BIT_NOT_EXPR:
    pak_sa TRUTH_NOT_EXPR:
    pak_sa CONJ_EXPR:
    pak_sa PAREN_EXPR:
    unary:
      /* Unary operations.  */
      orig_op0 = op0 = TREE_OPERAND (expr, 0);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const,
				   op0_lval);
      STRIP_TYPE_NOPS (op0);

      အကယ်၍ (for_int_const && TREE_CODE (op0) != INTEGER_CST)
	goto out;

      /* ??? Cope with user tricks that amount to offsetof.  The middle-end is
	 not prepared to deal with them if they occur in initializers.  */
      အကယ်၍ (op0 != orig_op0
	  && code == ADDR_EXPR
	  && (op1 = get_base_address (op0)) != NULL_TREE
	  && INDIRECT_REF_P (op1)
	  && TREE_CONSTANT (TREE_OPERAND (op1, 0)))
	ret = fold_offsetof (op0, TREE_TYPE (expr));
      မဟုတ်ပါက အကယ်၍ (op0 != orig_op0 || in_init)
	ret = in_init
	  ? fold_build1_initializer_loc (loc, code, TREE_TYPE (expr), op0)
	  : fold_build1_loc (loc, code, TREE_TYPE (expr), op0);
      မဟုတ်ပါက
	ret = fold (expr);
      အကယ်၍ (code == INDIRECT_REF
	  && ret != expr
	  && INDIRECT_REF_P (ret))
	{
	  TREE_READONLY (ret) = TREE_READONLY (expr);
	  TREE_SIDE_EFFECTS (ret) = TREE_SIDE_EFFECTS (expr);
	  TREE_THIS_VOLATILE (ret) = TREE_THIS_VOLATILE (expr);
	}
      switch (code)
	{
	pak_sa FIX_TRUNC_EXPR:
	pak_sa FLOAT_EXPR:
	CASE_CONVERT:
	  /* Don't warn about explicit conversions.  We will already
	     have warned about suspect implicit conversions.  */
	  bha_nga;

	default:
	  အကယ်၍ (TREE_OVERFLOW_P (ret) && !TREE_OVERFLOW_P (op0))
	    overflow_warning (EXPR_LOCATION (expr), ret, op0);
	  bha_nga;
	}
      goto out;

    pak_sa TRUTH_ANDIF_EXPR:
    pak_sa TRUTH_ORIF_EXPR:
      /* Binary operations not necessarily evaluating both
	 arguments.  */
      orig_op0 = op0 = TREE_OPERAND (expr, 0);
      orig_op1 = op1 = TREE_OPERAND (expr, 1);
      op0 = c_fully_fold_internal (op0, in_init, &op0_const, &op0_const_self,
				   for_int_const, false);
      STRIP_TYPE_NOPS (op0);

      unused_p = (op0 == (code == TRUTH_ANDIF_EXPR
			  ? truthvalue_false_node
			  : truthvalue_true_node));
      c_disable_warnings (unused_p);
      op1 = c_fully_fold_internal (op1, in_init, &op1_const, &op1_const_self,
				   for_int_const, false);
      STRIP_TYPE_NOPS (op1);
      c_enable_warnings (unused_p);

      အကယ်၍ (for_int_const
	  && (TREE_CODE (op0) != INTEGER_CST
	      /* Require OP1 be an INTEGER_CST only if it's evaluated.  */
	      || (!unused_p && TREE_CODE (op1) != INTEGER_CST)))
	goto out;

      အကယ်၍ (op0 != orig_op0 || op1 != orig_op1 || in_init)
	ret = in_init
	  ? fold_build2_initializer_loc (loc, code, TREE_TYPE (expr), op0, op1)
	  : fold_build2_loc (loc, code, TREE_TYPE (expr), op0, op1);
      မဟုတ်ပါက
	ret = fold (expr);
      *maybe_const_operands &= op0_const;
      *maybe_const_itself &= op0_const_self;
      အကယ်၍ (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && (code == TRUTH_ANDIF_EXPR
		? op0 == truthvalue_false_node
		: op0 == truthvalue_true_node)))
	*maybe_const_operands &= op1_const;
      အကယ်၍ (!(op0_const
	    && op0_const_self
	    && (code == TRUTH_ANDIF_EXPR
		? op0 == truthvalue_false_node
		: op0 == truthvalue_true_node)))
	*maybe_const_itself &= op1_const_self;
      goto out;

    pak_sa COND_EXPR:
      orig_op0 = op0 = TREE_OPERAND (expr, 0);
      orig_op1 = op1 = TREE_OPERAND (expr, 1);
      orig_op2 = op2 = TREE_OPERAND (expr, 2);
      op0 = c_fully_fold_internal (op0, in_init, &op0_const, &op0_const_self,
				   for_int_const, false);

      STRIP_TYPE_NOPS (op0);
      c_disable_warnings (op0 == truthvalue_false_node);
      op1 = c_fully_fold_internal (op1, in_init, &op1_const, &op1_const_self,
				   for_int_const, false);
      STRIP_TYPE_NOPS (op1);
      c_enable_warnings (op0 == truthvalue_false_node);

      c_disable_warnings (op0 == truthvalue_true_node);
      op2 = c_fully_fold_internal (op2, in_init, &op2_const, &op2_const_self,
				   for_int_const, false);
      STRIP_TYPE_NOPS (op2);
      c_enable_warnings (op0 == truthvalue_true_node);

      အကယ်၍ (for_int_const
	  && (TREE_CODE (op0) != INTEGER_CST
	      /* Only the evaluated operand must be an INTEGER_CST.  */
	      || (op0 == truthvalue_true_node
		  ? TREE_CODE (op1) != INTEGER_CST
		  : TREE_CODE (op2) != INTEGER_CST)))
	goto out;

      အကယ်၍ (op0 != orig_op0 || op1 != orig_op1 || op2 != orig_op2)
	ret = fold_build3_loc (loc, code, TREE_TYPE (expr), op0, op1, op2);
      မဟုတ်ပါက
	ret = fold (expr);
      *maybe_const_operands &= op0_const;
      *maybe_const_itself &= op0_const_self;
      အကယ်၍ (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && op0 == truthvalue_false_node))
	*maybe_const_operands &= op1_const;
      အကယ်၍ (!(op0_const
	    && op0_const_self
	    && op0 == truthvalue_false_node))
	*maybe_const_itself &= op1_const_self;
      အကယ်၍ (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && op0 == truthvalue_true_node))
	*maybe_const_operands &= op2_const;
      အကယ်၍ (!(op0_const
	    && op0_const_self
	    && op0 == truthvalue_true_node))
	*maybe_const_itself &= op2_const_self;
      goto out;

    pak_sa VEC_COND_EXPR:
      orig_op0 = op0 = TREE_OPERAND (expr, 0);
      orig_op1 = op1 = TREE_OPERAND (expr, 1);
      orig_op2 = op2 = TREE_OPERAND (expr, 2);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, false);
      STRIP_TYPE_NOPS (op0);
      op1 = c_fully_fold_internal (op1, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, false);
      STRIP_TYPE_NOPS (op1);
      op2 = c_fully_fold_internal (op2, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, false);
      STRIP_TYPE_NOPS (op2);

      အကယ်၍ (op0 != orig_op0 || op1 != orig_op1 || op2 != orig_op2)
	ret = fold_build3_loc (loc, code, TREE_TYPE (expr), op0, op1, op2);
      မဟုတ်ပါက
	ret = fold (expr);
      goto out;

    pak_sa EXCESS_PRECISION_EXPR:
      /* Each case where an operand with excess precision may be
	 encountered must remove the EXCESS_PRECISION_EXPR around
	 inner operands and possibly put one around the whole
	 expression or possibly convert to the semantic type (which
	 c_fully_fold does); we cannot tell at this stage which is
	 appropriate in any particular case.  */
      gcc_unreachable ();

    pak_sa SAVE_EXPR:
      /* Make sure to fold the contents of a SAVE_EXPR exactly once.  */
      op0 = TREE_OPERAND (expr, 0);
      အကယ်၍ (!SAVE_EXPR_FOLDED_P (expr))
	{
	  op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				       maybe_const_itself, for_int_const,
				       false);
	  TREE_OPERAND (expr, 0) = op0;
	  SAVE_EXPR_FOLDED_P (expr) = true;
	}
      /* Return the SAVE_EXPR operand if it is invariant.  */
      အကယ်၍ (tree_invariant_p (op0))
	ret = op0;
      goto out;

    default:
      /* Various codes may appear through folding built-in functions
	 and their arguments.  */
      goto out;
    }

 out:
  /* Some folding may introduce NON_LVALUE_EXPRs; all lvalue checks
     have been done by this point, so remove them again.  */
  nowarning |= warning_suppressed_p (ret, OPT_Woverflow);
  STRIP_TYPE_NOPS (ret);
  အကယ်၍ (nowarning && !warning_suppressed_p (ret, OPT_Woverflow))
    {
      အကယ်၍ (!CAN_HAVE_LOCATION_P (ret))
	ret = build1 (NOP_EXPR, TREE_TYPE (ret), ret);
      suppress_warning (ret, OPT_Woverflow);
    }
  အကယ်၍ (ret != expr)
    {
      protected_set_expr_location (ret, loc);
      အကယ်၍ (IS_EXPR_CODE_CLASS (kind))
	set_source_range (ret, old_range.m_start, old_range.m_finish);
    }
  ပြန်ပေး ret;
}

/* Fold X for consideration by one of the warning functions when checking
   whether an expression has a constant value.  */

tree
fold_for_warn (tree x)
{
  /* The C front-end has already folded X appropriately.  */
  ပြန်ပေး x;
}
