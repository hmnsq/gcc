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

#ضمن "config.h"
#ضمن "system.h"
#ضمن "coretypes.h"
#ضمن "target.h"
#ضمن "function.h"
#ضمن "bitmap.h"
#ضمن "c-tree.h"
#ضمن "intl.h"
#ضمن "gimplify.h"

ساكن وڻ c_fully_fold_اندروني (وڻ اظهار, منطقي, منطقي *, منطقي *, منطقي,
				   منطقي);

/* If DISABLE is true, stop issuing warnings.  This is used when
   parsing code that we know will not be executed.  This function may
   be called multiple times, and works as a stack.  */

ساكن فراغ
c_disable_warnings (منطقي disable)
{
  إذا (disable)
    {
      ++c_inhibit_evaluation_warnings;
    }
}

/* If ENABLE is true, re-enable issuing warnings.  */

ساكن فراغ
c_enable_warnings (منطقي enable)
{
  إذا (enable)
    {
      --c_inhibit_evaluation_warnings;
    }
}

/* Try to fold ARRAY_REF ary[index] if possible and not handled by
   normal fold, return NULL_TREE otherwise.  */

ساكن وڻ
c_fold_array_ref (وڻ type, وڻ ary, وڻ اشاريو)
{
  إذا (وڻ_ڪوڊ (ary) != STRING_CST
      || وڻ_ڪوڊ (اشاريو) != INTEGER_CST
      || وڻ_حد_کان_مٿي (اشاريو)
      || وڻ_ڪوڊ (وڻ_TYPE (ary)) != ARRAY_TYPE
      || !وڻ_سمائي_uhwi_p (اشاريو))
    أرجع NULL_وڻ;

  وڻ elem_type = وڻ_TYPE (وڻ_TYPE (ary));
  بنانشان elem_nchars = (TYPE_PRECISION (elem_type)
			  / TYPE_PRECISION (char_type_ڳنڍ));
  بنانشان len = (بنانشان) وڻ_STRING_ڊيگهائي (ary) / elem_nchars;
  وڻ nelts_minus_one = array_type_nelts_minus_one (وڻ_TYPE (ary));
  منطقي dummy1 = سچ, dummy2 = سچ;
  nelts_minus_one = c_fully_fold_اندروني (nelts_minus_one, سچ, &dummy1,
					   &dummy2, خطأ, خطأ);
  بنانشان HOST_WIDE_INT i = وڻ_منزل_uhwi (اشاريو);
  إذا (!وڻ_int_cst_le (اشاريو, nelts_minus_one)
      || i >= len
      || i + elem_nchars > len)
    أرجع NULL_وڻ;

  إذا (elem_nchars == 1)
    أرجع build_int_cst (type, وڻ_STRING_اشارو (ary)[i]);

  ثابت بنانشان حرف *ptr
    = ((ثابت بنانشان حرف *)وڻ_STRING_اشارو (ary) + i * elem_nchars);
  أرجع native_interpret_اظهار (type, ptr, elem_nchars);
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

وڻ
c_fully_fold (وڻ اظهار, منطقي اندريون_init, منطقي *maybe_const, منطقي lval)
{
  وڻ ret;
  وڻ eptype = NULL_وڻ;
  منطقي dummy = سچ;
  منطقي maybe_const_itself = سچ;
  location_t loc = اظهار_LOCATION (اظهار);

  إذا (!maybe_const)
    maybe_const = &dummy;
  إذا (وڻ_ڪوڊ (اظهار) == EXCESS_PRECISION_اظهار)
    {
      eptype = وڻ_TYPE (اظهار);
      اظهار = وڻ_عمليو (اظهار, 0);
    }
  ret = c_fully_fold_اندروني (اظهار, اندريون_init, maybe_const,
			       &maybe_const_itself, خطأ, lval);
  إذا (eptype)
    ret = fold_convert_loc (loc, eptype, ret);
  *maybe_const &= maybe_const_itself;
  أرجع ret;
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

ساكن وڻ
c_fully_fold_اندروني (وڻ اظهار, منطقي اندريون_init, منطقي *maybe_const_operands,
		       منطقي *maybe_const_itself, منطقي for_int_const, منطقي lval)
{
  وڻ ret = اظهار;
  تعداد وڻ_ڪوڊ_2 ڪوڊ = وڻ_ڪوڊ (اظهار);
  تعداد وڻ_ڪوڊ_class قسم = وڻ_ڪوڊ_CLASS (ڪوڊ);
  location_t loc = اظهار_LOCATION (اظهار);
  وڻ op0, op1, op2, op3;
  وڻ orig_op0, orig_op1, orig_op2;
  منطقي op0_const = سچ, op1_const = سچ, op2_const = سچ;
  منطقي op0_const_self = سچ, op1_const_self = سچ, op2_const_self = سچ;
  منطقي nowarning = warning_suppressed_p (اظهار, OPT_Woverflow);
  منطقي اڻ_استعمال_ٿيل_p;
  منطقي op0_lval = خطأ;
  ذريعو_range old_range;

  /* Constants, declarations, statements, errors, and anything else not
     counted as an expression cannot usefully be folded further at this
     point.  */
  إذا (!IS_اظهار_ڪوڊ_CLASS (قسم) || قسم == tcc_statement)
    {
      /* Except for variables which we can optimize to its initializer.  */
      إذا (VAR_P (اظهار) && !lval && (optimize || اندريون_init))
	{
	  إذا (اندريون_init)
	    ret = decl_constant_قدر_1 (اظهار, سچ);
	  وإلا
	    {
	      ret = decl_constant_قدر (اظهار);
	      إذا (ret != اظهار
		  && (TYPE_گهڻائي (وڻ_TYPE (ret)) == BLKmode
		      || وڻ_ڪوڊ (وڻ_TYPE (ret)) == ARRAY_TYPE))
		أرجع اظهار;
	    }
	  /* Avoid unwanted tree sharing between the initializer and current
	     function's body where the tree can be modified e.g. by the
	     gimplifier.  */
	  إذا (ret != اظهار && وڻ_STATIC (اظهار))
	    ret = unshare_اظهار (ret);
	  أرجع ret;
	}
      أرجع اظهار;
    }

  إذا (IS_اظهار_ڪوڊ_CLASS (قسم))
    old_range = اظهار_LOCATION_RANGE (اظهار);

  /* Operands of variable-length expressions (function calls) have
     already been folded, as have __builtin_* function calls, and such
     expressions cannot occur in constant expressions.  */
  إذا (قسم == tcc_vl_exp)
    {
      *maybe_const_operands = خطأ;
      ret = fold (اظهار);
      اذهب ٻاهريون;
    }

  إذا (ڪوڊ == C_MAYBE_CONST_اظهار)
    {
      وڻ pre = C_MAYBE_CONST_اظهار_PRE (اظهار);
      وڻ inner = C_MAYBE_CONST_اظهار_اظهار (اظهار);
      إذا (C_MAYBE_CONST_اظهار_NON_CONST (اظهار))
	*maybe_const_operands = خطأ;
      إذا (C_MAYBE_CONST_اظهار_INT_OPERANDS (اظهار))
	{
	  *maybe_const_itself = خطأ;
	  inner = c_fully_fold_اندروني (inner, اندريون_init, maybe_const_operands,
					 maybe_const_itself, سچ, lval);
	}
      إذا (pre && !اندريون_init)
	ret = build2 (COMPOUND_اظهار, وڻ_TYPE (اظهار), pre, inner);
      وإلا
	ret = inner;
      اذهب ٻاهريون;
    }

  /* Assignment, increment, decrement, function call and comma
     operators, and statement expressions, cannot occur in constant
     expressions if evaluated / outside of sizeof.  (Function calls
     were handled above, though VA_ARG_EXPR is treated like a function
     call here, and statement expressions are handled through
     C_MAYBE_CONST_EXPR to avoid folding inside them.)  */
  بدل (ڪوڊ)
    {
    حالة MODIFY_اظهار:
    حالة PREDECREMENT_اظهار:
    حالة PREINCREMENT_اظهار:
    حالة POSTDECREMENT_اظهار:
    حالة POSTINCREMENT_اظهار:
    حالة COMPOUND_اظهار:
      *maybe_const_operands = خطأ;
      اكسر;

    حالة VA_ARG_اظهار:
    حالة هدف_اظهار:
    حالة BIND_اظهار:
    حالة OBJ_TYPE_REF:
      *maybe_const_operands = خطأ;
      ret = fold (اظهار);
      اذهب ٻاهريون;

    افتراضي:
      اكسر;
    }

  /* Fold individual tree codes as appropriate.  */
  بدل (ڪوڊ)
    {
    حالة COMPOUND_LITERAL_اظهار:
      /* Any non-constancy will have been marked in a containing
	 C_MAYBE_CONST_EXPR; there is no more folding to do here.  */
      اذهب ٻاهريون;

    حالة COMPONENT_REF:
      orig_op0 = op0 = وڻ_عمليو (اظهار, 0);
      op1 = وڻ_عمليو (اظهار, 1);
      op2 = وڻ_عمليو (اظهار, 2);
      op0 = c_fully_fold_اندروني (op0, اندريون_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, lval);
      STRIP_TYPE_NOPS (op0);
      إذا (op0 != orig_op0)
	ret = build3 (COMPONENT_REF, وڻ_TYPE (اظهار), op0, op1, op2);
      إذا (ret != اظهار)
	{
	  وڻ_READONLY (ret) = وڻ_READONLY (اظهار);
	  وڻ_THIS_VOLATILE (ret) = وڻ_THIS_VOLATILE (اظهار);
	}
      إذا (!lval)
	ret = fold (ret);
      اذهب ٻاهريون;

    حالة ARRAY_REF:
      orig_op0 = op0 = وڻ_عمليو (اظهار, 0);
      orig_op1 = op1 = وڻ_عمليو (اظهار, 1);
      op2 = وڻ_عمليو (اظهار, 2);
      op3 = وڻ_عمليو (اظهار, 3);
      op0 = c_fully_fold_اندروني (op0, اندريون_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, lval);
      STRIP_TYPE_NOPS (op0);
      op1 = c_fully_fold_اندروني (op1, اندريون_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, خطأ);
      STRIP_TYPE_NOPS (op1);
      /* Fold "foo"[2] in initializers.  */
      إذا (!lval && اندريون_init)
	{
	  ret = c_fold_array_ref (وڻ_TYPE (اظهار), op0, op1);
	  إذا (ret)
	    اذهب ٻاهريون;
	  ret = اظهار;
	}
      إذا (op0 != orig_op0 || op1 != orig_op1)
	ret = build4 (ARRAY_REF, وڻ_TYPE (اظهار), op0, op1, op2, op3);
      إذا (ret != اظهار)
	{
	  وڻ_READONLY (ret) = وڻ_READONLY (اظهار);
	  وڻ_SIDE_EFFECTS (ret) = وڻ_SIDE_EFFECTS (اظهار);
	  وڻ_THIS_VOLATILE (ret) = وڻ_THIS_VOLATILE (اظهار);
	}
      إذا (!lval)
	ret = fold (ret);
      اذهب ٻاهريون;

    حالة MODIFY_اظهار:
    حالة PREDECREMENT_اظهار:
    حالة PREINCREMENT_اظهار:
    حالة POSTDECREMENT_اظهار:
    حالة POSTINCREMENT_اظهار:
      op0_lval = سچ;
      /* FALLTHRU */
    حالة COMPOUND_اظهار:
    حالة PLUS_اظهار:
    حالة MINUS_اظهار:
    حالة MULT_اظهار:
    حالة اشارو_PLUS_اظهار:
    حالة اشارو_DIFF_اظهار:
    حالة TRUNC_DIV_اظهار:
    حالة CEIL_DIV_اظهار:
    حالة FLOOR_DIV_اظهار:
    حالة TRUNC_MOD_اظهار:
    حالة RDIV_اظهار:
    حالة EXACT_DIV_اظهار:
    حالة LSHIFT_اظهار:
    حالة RSHIFT_اظهار:
    حالة LROTATE_اظهار:
    حالة RROTATE_اظهار:
    حالة ٻٽو_انگ_IOR_اظهار:
    حالة ٻٽو_انگ_XOR_اظهار:
    حالة ٻٽو_انگ_AND_اظهار:
    حالة LT_اظهار:
    حالة LE_اظهار:
    حالة GT_اظهار:
    حالة GE_اظهار:
    حالة EQ_اظهار:
    حالة NE_اظهار:
    حالة COMPLEX_اظهار:
    حالة TRUTH_AND_اظهار:
    حالة TRUTH_OR_اظهار:
    حالة TRUTH_XOR_اظهار:
    حالة UNORDERED_اظهار:
    حالة ORDERED_اظهار:
    حالة UNLT_اظهار:
    حالة UNLE_اظهار:
    حالة UNGT_اظهار:
    حالة UNGE_اظهار:
    حالة UNEQ_اظهار:
    حالة MEM_REF:
      /* Binary operations evaluating both arguments (increment and
	 decrement are binary internally in GCC).  */
      orig_op0 = op0 = وڻ_عمليو (اظهار, 0);
      orig_op1 = op1 = وڻ_عمليو (اظهار, 1);
      op0 = c_fully_fold_اندروني (op0, اندريون_init, maybe_const_operands,
				   maybe_const_itself, for_int_const,
				   op0_lval);
      STRIP_TYPE_NOPS (op0);
      /* The RHS of a MODIFY_EXPR was fully folded when building that
	 expression for the sake of conversion warnings.  */
      إذا (ڪوڊ != MODIFY_اظهار)
	op1 = c_fully_fold_اندروني (op1, اندريون_init, maybe_const_operands,
				     maybe_const_itself, for_int_const, خطأ);
      STRIP_TYPE_NOPS (op1);

      إذا (for_int_const && (وڻ_ڪوڊ (op0) != INTEGER_CST
			    || وڻ_ڪوڊ (op1) != INTEGER_CST))
	اذهب ٻاهريون;

      إذا (وڻ_ڪوڊ_CLASS (ڪوڊ) == tcc_comparison
	  && وڻ_ڪوڊ (وڻ_TYPE (op0)) == NULLPTR_TYPE
	  && وڻ_ڪوڊ (وڻ_TYPE (op1)) == NULLPTR_TYPE)
	{
	  بدل (ڪوڊ)
	    {
	    حالة EQ_اظهار:
	      ret = constant_boolean_ڳنڍ (سچ, وڻ_TYPE (اظهار));
	      اكسر;
	    حالة NE_اظهار:
	      ret = constant_boolean_ڳنڍ (خطأ, وڻ_TYPE (اظهار));
	      اكسر;
	    افتراضي:
	      gcc_unreachable ();
	    }
	  ret = omit_two_operands_loc (loc, وڻ_TYPE (اظهار), ret,
				       op0, op1);
	}
      وإلا إذا (op0 != orig_op0 || op1 != orig_op1 || اندريون_init)
	ret = اندريون_init
	  ? fold_build2_initializer_loc (loc, ڪوڊ, وڻ_TYPE (اظهار), op0, op1)
	  : fold_build2_loc (loc, ڪوڊ, وڻ_TYPE (اظهار), op0, op1);
      وإلا
	ret = fold (اظهار);
      إذا (وڻ_حد_کان_مٿي_P (ret)
	  && !وڻ_حد_کان_مٿي_P (op0)
	  && !(ٻٽو_CLASS_P (op0) && وڻ_حد_کان_مٿي_P (وڻ_عمليو (op0, 1)))
	  && !وڻ_حد_کان_مٿي_P (op1))
	حد_کان_مٿي_warning (اظهار_LOC_OR_LOC (اظهار, داخلا_location), ret, اظهار);
      إذا (ڪوڊ == LSHIFT_اظهار
	  && وڻ_ڪوڊ (orig_op0) != INTEGER_CST
	  && (وڻ_ڪوڊ (وڻ_TYPE (orig_op0)) == INTEGER_TYPE
	      || وڻ_ڪوڊ (وڻ_TYPE (orig_op0)) == BITINT_TYPE)
	  && وڻ_ڪوڊ (op0) == INTEGER_CST
	  && c_inhibit_evaluation_warnings == 0
	  && !TYPE_حد_کان_مٿي_WRAPS (وڻ_TYPE (orig_op0))
	  && وڻ_int_cst_sgn (op0) < 0)
	warning_at (loc, OPT_Wshift_negative_قدر,
		    "left shift of negative value");
      إذا ((ڪوڊ == LSHIFT_اظهار
	   || ڪوڊ == RSHIFT_اظهار
	   || ڪوڊ == LROTATE_اظهار
	   || ڪوڊ == RROTATE_اظهار)
	  && وڻ_ڪوڊ (orig_op1) != INTEGER_CST
	  && وڻ_ڪوڊ (op1) == INTEGER_CST
	  && وڻ_ڪوڊ (وڻ_TYPE (orig_op1)) == INTEGER_TYPE
	  && c_inhibit_evaluation_warnings == 0)
	{
	  إذا (وڻ_int_cst_sgn (op1) < 0)
	    warning_at (loc, OPT_Wshift_ڳڻپ_negative,
			(ڪوڊ == LSHIFT_اظهار
			 ? G_("left shift count is negative")
			 : G_("right shift count is negative")));
	  وإلا إذا ((وڻ_ڪوڊ (وڻ_TYPE (orig_op0)) == INTEGER_TYPE
		    || وڻ_ڪوڊ (وڻ_TYPE (orig_op0)) == BITINT_TYPE
		    || وڻ_ڪوڊ (وڻ_TYPE (orig_op0)) == FIXED_نقطو_TYPE)
		   && compare_وڻ_int (op1,
					TYPE_PRECISION (وڻ_TYPE (orig_op0)))
		      >= 0
		   && !warning_suppressed_p (اظهار, OPT_Wshift_ڳڻپ_حد_کان_مٿي))
	    warning_at (loc, OPT_Wshift_ڳڻپ_حد_کان_مٿي,
			(ڪوڊ == LSHIFT_اظهار
			 ? G_("left shift count >= width of type")
			 : G_("right shift count >= width of type")));
	  وإلا إذا (وڻ_ڪوڊ (وڻ_TYPE (orig_op0)) == ويڪٽر_TYPE
		   && compare_وڻ_int (op1,
					TYPE_PRECISION (وڻ_TYPE (وڻ_TYPE (orig_op0))))
		      >= 0)
	    warning_at (loc, OPT_Wshift_ڳڻپ_حد_کان_مٿي,
			ڪوڊ == LSHIFT_اظهار
			? G_("left shift count >= width of vector element")
			: G_("right shift count >= width of vector element"));
	}
      إذا (ڪوڊ == LSHIFT_اظهار
	  /* If either OP0 has been folded to INTEGER_CST...  */
	  && ((وڻ_ڪوڊ (orig_op0) != INTEGER_CST
	       && (وڻ_ڪوڊ (وڻ_TYPE (orig_op0)) == INTEGER_TYPE
		   || وڻ_ڪوڊ (وڻ_TYPE (orig_op0)) == BITINT_TYPE)
	       && وڻ_ڪوڊ (op0) == INTEGER_CST)
	      /* ...or if OP1 has been folded to INTEGER_CST...  */
	      || (وڻ_ڪوڊ (orig_op1) != INTEGER_CST
		  && (وڻ_ڪوڊ (وڻ_TYPE (orig_op1)) == INTEGER_TYPE
		      || وڻ_ڪوڊ (وڻ_TYPE (orig_op1)) == BITINT_TYPE)
		  && وڻ_ڪوڊ (op1) == INTEGER_CST))
	  && c_inhibit_evaluation_warnings == 0)
	/* ...then maybe we can detect an overflow.  */
	maybe_warn_سرڪايو_حد_کان_مٿي (loc, op0, op1);
      إذا ((ڪوڊ == TRUNC_DIV_اظهار
	   || ڪوڊ == CEIL_DIV_اظهار
	   || ڪوڊ == FLOOR_DIV_اظهار
	   || ڪوڊ == EXACT_DIV_اظهار
	   || ڪوڊ == TRUNC_MOD_اظهار)
	  && وڻ_ڪوڊ (orig_op1) != INTEGER_CST
	  && وڻ_ڪوڊ (op1) == INTEGER_CST
	  && (وڻ_ڪوڊ (وڻ_TYPE (orig_op0)) == INTEGER_TYPE
	      || وڻ_ڪوڊ (وڻ_TYPE (orig_op0)) == BITINT_TYPE
	      || وڻ_ڪوڊ (وڻ_TYPE (orig_op0)) == FIXED_نقطو_TYPE)
	  && (وڻ_ڪوڊ (وڻ_TYPE (orig_op1)) == INTEGER_TYPE
	      || وڻ_ڪوڊ (وڻ_TYPE (orig_op1)) == BITINT_TYPE))
	warn_for_div_by_zero (loc, op1);
      إذا (ڪوڊ == MEM_REF
	  && ret != اظهار
	  && وڻ_ڪوڊ (ret) == MEM_REF)
	{
	  وڻ_READONLY (ret) = وڻ_READONLY (اظهار);
	  وڻ_SIDE_EFFECTS (ret) = وڻ_SIDE_EFFECTS (اظهار);
	  وڻ_THIS_VOLATILE (ret) = وڻ_THIS_VOLATILE (اظهار);
	}
      اذهب ٻاهريون;

    حالة ADDR_اظهار:
      op0_lval = سچ;
      اذهب unary;
    حالة REALPART_اظهار:
    حالة IMAGPART_اظهار:
    حالة VIEW_CONVERT_اظهار:
      op0_lval = lval;
      /* FALLTHRU */
    حالة اڻسڌو_REF:
    حالة FIX_TRUNC_اظهار:
    حالة FLOAT_اظهار:
    CASE_CONVERT:
    حالة ADDR_SPACE_CONVERT_اظهار:
    حالة NON_LVALUE_اظهار:
    حالة NEGATE_اظهار:
    حالة ٻٽو_انگ_NOT_اظهار:
    حالة TRUTH_NOT_اظهار:
    حالة CONJ_اظهار:
    حالة PAREN_اظهار:
    unary:
      /* Unary operations.  */
      orig_op0 = op0 = وڻ_عمليو (اظهار, 0);
      op0 = c_fully_fold_اندروني (op0, اندريون_init, maybe_const_operands,
				   maybe_const_itself, for_int_const,
				   op0_lval);
      STRIP_TYPE_NOPS (op0);

      إذا (for_int_const && وڻ_ڪوڊ (op0) != INTEGER_CST)
	اذهب ٻاهريون;

      /* ??? Cope with user tricks that amount to offsetof.  The middle-end is
	 not prepared to deal with them if they occur in initializers.  */
      إذا (op0 != orig_op0
	  && ڪوڊ == ADDR_اظهار
	  && (op1 = get_بنياد_پتو (op0)) != NULL_وڻ
	  && اڻسڌو_REF_P (op1)
	  && وڻ_CONSTANT (وڻ_عمليو (op1, 0)))
	ret = fold_offsetof (op0, وڻ_TYPE (اظهار));
      وإلا إذا (op0 != orig_op0 || اندريون_init)
	ret = اندريون_init
	  ? fold_build1_initializer_loc (loc, ڪوڊ, وڻ_TYPE (اظهار), op0)
	  : fold_build1_loc (loc, ڪوڊ, وڻ_TYPE (اظهار), op0);
      وإلا
	ret = fold (اظهار);
      إذا (ڪوڊ == اڻسڌو_REF
	  && ret != اظهار
	  && اڻسڌو_REF_P (ret))
	{
	  وڻ_READONLY (ret) = وڻ_READONLY (اظهار);
	  وڻ_SIDE_EFFECTS (ret) = وڻ_SIDE_EFFECTS (اظهار);
	  وڻ_THIS_VOLATILE (ret) = وڻ_THIS_VOLATILE (اظهار);
	}
      بدل (ڪوڊ)
	{
	حالة FIX_TRUNC_اظهار:
	حالة FLOAT_اظهار:
	CASE_CONVERT:
	  /* Don't warn about explicit conversions.  We will already
	     have warned about suspect implicit conversions.  */
	  اكسر;

	افتراضي:
	  إذا (وڻ_حد_کان_مٿي_P (ret) && !وڻ_حد_کان_مٿي_P (op0))
	    حد_کان_مٿي_warning (اظهار_LOCATION (اظهار), ret, op0);
	  اكسر;
	}
      اذهب ٻاهريون;

    حالة TRUTH_ANDIF_اظهار:
    حالة TRUTH_ORIF_اظهار:
      /* Binary operations not necessarily evaluating both
	 arguments.  */
      orig_op0 = op0 = وڻ_عمليو (اظهار, 0);
      orig_op1 = op1 = وڻ_عمليو (اظهار, 1);
      op0 = c_fully_fold_اندروني (op0, اندريون_init, &op0_const, &op0_const_self,
				   for_int_const, خطأ);
      STRIP_TYPE_NOPS (op0);

      اڻ_استعمال_ٿيل_p = (op0 == (ڪوڊ == TRUTH_ANDIF_اظهار
			  ? truthvalue_false_ڳنڍ
			  : truthvalue_true_ڳنڍ));
      c_disable_warnings (اڻ_استعمال_ٿيل_p);
      op1 = c_fully_fold_اندروني (op1, اندريون_init, &op1_const, &op1_const_self,
				   for_int_const, خطأ);
      STRIP_TYPE_NOPS (op1);
      c_enable_warnings (اڻ_استعمال_ٿيل_p);

      إذا (for_int_const
	  && (وڻ_ڪوڊ (op0) != INTEGER_CST
	      /* Require OP1 be an INTEGER_CST only if it's evaluated.  */
	      || (!اڻ_استعمال_ٿيل_p && وڻ_ڪوڊ (op1) != INTEGER_CST)))
	اذهب ٻاهريون;

      إذا (op0 != orig_op0 || op1 != orig_op1 || اندريون_init)
	ret = اندريون_init
	  ? fold_build2_initializer_loc (loc, ڪوڊ, وڻ_TYPE (اظهار), op0, op1)
	  : fold_build2_loc (loc, ڪوڊ, وڻ_TYPE (اظهار), op0, op1);
      وإلا
	ret = fold (اظهار);
      *maybe_const_operands &= op0_const;
      *maybe_const_itself &= op0_const_self;
      إذا (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && (ڪوڊ == TRUTH_ANDIF_اظهار
		? op0 == truthvalue_false_ڳنڍ
		: op0 == truthvalue_true_ڳنڍ)))
	*maybe_const_operands &= op1_const;
      إذا (!(op0_const
	    && op0_const_self
	    && (ڪوڊ == TRUTH_ANDIF_اظهار
		? op0 == truthvalue_false_ڳنڍ
		: op0 == truthvalue_true_ڳنڍ)))
	*maybe_const_itself &= op1_const_self;
      اذهب ٻاهريون;

    حالة COND_اظهار:
      orig_op0 = op0 = وڻ_عمليو (اظهار, 0);
      orig_op1 = op1 = وڻ_عمليو (اظهار, 1);
      orig_op2 = op2 = وڻ_عمليو (اظهار, 2);
      op0 = c_fully_fold_اندروني (op0, اندريون_init, &op0_const, &op0_const_self,
				   for_int_const, خطأ);

      STRIP_TYPE_NOPS (op0);
      c_disable_warnings (op0 == truthvalue_false_ڳنڍ);
      op1 = c_fully_fold_اندروني (op1, اندريون_init, &op1_const, &op1_const_self,
				   for_int_const, خطأ);
      STRIP_TYPE_NOPS (op1);
      c_enable_warnings (op0 == truthvalue_false_ڳنڍ);

      c_disable_warnings (op0 == truthvalue_true_ڳنڍ);
      op2 = c_fully_fold_اندروني (op2, اندريون_init, &op2_const, &op2_const_self,
				   for_int_const, خطأ);
      STRIP_TYPE_NOPS (op2);
      c_enable_warnings (op0 == truthvalue_true_ڳنڍ);

      إذا (for_int_const
	  && (وڻ_ڪوڊ (op0) != INTEGER_CST
	      /* Only the evaluated operand must be an INTEGER_CST.  */
	      || (op0 == truthvalue_true_ڳنڍ
		  ? وڻ_ڪوڊ (op1) != INTEGER_CST
		  : وڻ_ڪوڊ (op2) != INTEGER_CST)))
	اذهب ٻاهريون;

      إذا (op0 != orig_op0 || op1 != orig_op1 || op2 != orig_op2)
	ret = fold_build3_loc (loc, ڪوڊ, وڻ_TYPE (اظهار), op0, op1, op2);
      وإلا
	ret = fold (اظهار);
      *maybe_const_operands &= op0_const;
      *maybe_const_itself &= op0_const_self;
      إذا (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && op0 == truthvalue_false_ڳنڍ))
	*maybe_const_operands &= op1_const;
      إذا (!(op0_const
	    && op0_const_self
	    && op0 == truthvalue_false_ڳنڍ))
	*maybe_const_itself &= op1_const_self;
      إذا (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && op0 == truthvalue_true_ڳنڍ))
	*maybe_const_operands &= op2_const;
      إذا (!(op0_const
	    && op0_const_self
	    && op0 == truthvalue_true_ڳنڍ))
	*maybe_const_itself &= op2_const_self;
      اذهب ٻاهريون;

    حالة VEC_COND_اظهار:
      orig_op0 = op0 = وڻ_عمليو (اظهار, 0);
      orig_op1 = op1 = وڻ_عمليو (اظهار, 1);
      orig_op2 = op2 = وڻ_عمليو (اظهار, 2);
      op0 = c_fully_fold_اندروني (op0, اندريون_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, خطأ);
      STRIP_TYPE_NOPS (op0);
      op1 = c_fully_fold_اندروني (op1, اندريون_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, خطأ);
      STRIP_TYPE_NOPS (op1);
      op2 = c_fully_fold_اندروني (op2, اندريون_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, خطأ);
      STRIP_TYPE_NOPS (op2);

      إذا (op0 != orig_op0 || op1 != orig_op1 || op2 != orig_op2)
	ret = fold_build3_loc (loc, ڪوڊ, وڻ_TYPE (اظهار), op0, op1, op2);
      وإلا
	ret = fold (اظهار);
      اذهب ٻاهريون;

    حالة EXCESS_PRECISION_اظهار:
      /* Each case where an operand with excess precision may be
	 encountered must remove the EXCESS_PRECISION_EXPR around
	 inner operands and possibly put one around the whole
	 expression or possibly convert to the semantic type (which
	 c_fully_fold does); we cannot tell at this stage which is
	 appropriate in any particular case.  */
      gcc_unreachable ();

    حالة SAVE_اظهار:
      /* Make sure to fold the contents of a SAVE_EXPR exactly once.  */
      op0 = وڻ_عمليو (اظهار, 0);
      إذا (!SAVE_اظهار_FOLDED_P (اظهار))
	{
	  op0 = c_fully_fold_اندروني (op0, اندريون_init, maybe_const_operands,
				       maybe_const_itself, for_int_const,
				       خطأ);
	  وڻ_عمليو (اظهار, 0) = op0;
	  SAVE_اظهار_FOLDED_P (اظهار) = سچ;
	}
      /* Return the SAVE_EXPR operand if it is invariant.  */
      إذا (وڻ_invariant_p (op0))
	ret = op0;
      اذهب ٻاهريون;

    افتراضي:
      /* Various codes may appear through folding built-in functions
	 and their arguments.  */
      اذهب ٻاهريون;
    }

 ٻاهريون:
  /* Some folding may introduce NON_LVALUE_EXPRs; all lvalue checks
     have been done by this point, so remove them again.  */
  nowarning |= warning_suppressed_p (ret, OPT_Woverflow);
  STRIP_TYPE_NOPS (ret);
  إذا (nowarning && !warning_suppressed_p (ret, OPT_Woverflow))
    {
      إذا (!CAN_HAVE_LOCATION_P (ret))
	ret = build1 (NOP_اظهار, وڻ_TYPE (ret), ret);
      suppress_warning (ret, OPT_Woverflow);
    }
  إذا (ret != اظهار)
    {
      protected_سيٽ_اظهار_location (ret, loc);
      إذا (IS_اظهار_ڪوڊ_CLASS (قسم))
	سيٽ_ذريعو_range (ret, old_range.m_شروعات, old_range.m_پڄاڻي);
    }
  أرجع ret;
}

/* Fold X for consideration by one of the warning functions when checking
   whether an expression has a constant value.  */

وڻ
fold_for_warn (وڻ x)
{
  /* The C front-end has already folded X appropriately.  */
  أرجع x;
}
