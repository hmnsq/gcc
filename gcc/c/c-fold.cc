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

#അന്തര്ഭാവ "config.h"
#അന്തര്ഭാവ "system.h"
#അന്തര്ഭാവ "coretypes.h"
#അന്തര്ഭാവ "target.h"
#അന്തര്ഭാവ "function.h"
#അന്തര്ഭാവ "bitmap.h"
#അന്തര്ഭാവ "c-tree.h"
#അന്തര്ഭാവ "intl.h"
#അന്തര്ഭാവ "gimplify.h"

സ്ഥിതം വൃക്ഷം c_fully_fold_internal (വൃക്ഷം വ്യഞ്ജകം, തർക്കം, തർക്കം *, തർക്കം *, തർക്കം,
				   തർക്കം);

/* If DISABLE is true, stop issuing warnings.  This is used when
   parsing code that we know will not be executed.  This function may
   be called multiple times, and works as a stack.  */

സ്ഥിതം ശൂന്യം
c_disable_warnings (തർക്കം disable)
{
  എങ്കിൽ (disable)
    {
      ++c_inhibit_evaluation_warnings;
    }
}

/* If ENABLE is true, re-enable issuing warnings.  */

സ്ഥിതം ശൂന്യം
c_enable_warnings (തർക്കം enable)
{
  എങ്കിൽ (enable)
    {
      --c_inhibit_evaluation_warnings;
    }
}

/* Try to fold ARRAY_REF ary[index] if possible and not handled by
   normal fold, return NULL_TREE otherwise.  */

സ്ഥിതം വൃക്ഷം
c_fold_array_ref (വൃക്ഷം type, വൃക്ഷം ary, വൃക്ഷം index)
{
  എങ്കിൽ (വൃക്ഷം_CODE (ary) != STRING_CST
      || വൃക്ഷം_CODE (index) != INTEGER_CST
      || വൃക്ഷം_OVERFLOW (index)
      || വൃക്ഷം_CODE (വൃക്ഷം_TYPE (ary)) != ARRAY_TYPE
      || !വൃക്ഷം_fits_uhwi_p (index))
    തിരികെ NULL_വൃക്ഷം;

  വൃക്ഷം elem_type = വൃക്ഷം_TYPE (വൃക്ഷം_TYPE (ary));
  unsigned elem_nchars = (TYPE_PRECISION (elem_type)
			  / TYPE_PRECISION (char_type_കണ്ണി));
  unsigned len = (unsigned) വൃക്ഷം_STRING_LENGTH (ary) / elem_nchars;
  വൃക്ഷം nelts_minus_one = array_type_nelts_minus_one (വൃക്ഷം_TYPE (ary));
  തർക്കം dummy1 = സത്യം, dummy2 = സത്യം;
  nelts_minus_one = c_fully_fold_internal (nelts_minus_one, സത്യം, &dummy1,
					   &dummy2, അസത്യം, അസത്യം);
  unsigned HOST_WIDE_INT i = വൃക്ഷം_to_uhwi (index);
  എങ്കിൽ (!വൃക്ഷം_int_cst_le (index, nelts_minus_one)
      || i >= len
      || i + elem_nchars > len)
    തിരികെ NULL_വൃക്ഷം;

  എങ്കിൽ (elem_nchars == 1)
    തിരികെ build_int_cst (type, വൃക്ഷം_STRING_POINTER (ary)[i]);

  സ്ഥിരം unsigned അക്ഷരം *ptr
    = ((സ്ഥിരം unsigned അക്ഷരം *)വൃക്ഷം_STRING_POINTER (ary) + i * elem_nchars);
  തിരികെ native_interpret_വ്യഞ്ജകം (type, ptr, elem_nchars);
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

വൃക്ഷം
c_fully_fold (വൃക്ഷം വ്യഞ്ജകം, തർക്കം in_init, തർക്കം *maybe_const, തർക്കം lval)
{
  വൃക്ഷം ret;
  വൃക്ഷം eptype = NULL_വൃക്ഷം;
  തർക്കം dummy = സത്യം;
  തർക്കം maybe_const_itself = സത്യം;
  location_t loc = വ്യഞ്ജകം_LOCATION (വ്യഞ്ജകം);

  എങ്കിൽ (!maybe_const)
    maybe_const = &dummy;
  എങ്കിൽ (വൃക്ഷം_CODE (വ്യഞ്ജകം) == EXCESS_PRECISION_വ്യഞ്ജകം)
    {
      eptype = വൃക്ഷം_TYPE (വ്യഞ്ജകം);
      വ്യഞ്ജകം = വൃക്ഷം_OPERAND (വ്യഞ്ജകം, 0);
    }
  ret = c_fully_fold_internal (വ്യഞ്ജകം, in_init, maybe_const,
			       &maybe_const_itself, അസത്യം, lval);
  എങ്കിൽ (eptype)
    ret = fold_convert_loc (loc, eptype, ret);
  *maybe_const &= maybe_const_itself;
  തിരികെ ret;
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

സ്ഥിതം വൃക്ഷം
c_fully_fold_internal (വൃക്ഷം വ്യഞ്ജകം, തർക്കം in_init, തർക്കം *maybe_const_operands,
		       തർക്കം *maybe_const_itself, തർക്കം for_int_const, തർക്കം lval)
{
  വൃക്ഷം ret = വ്യഞ്ജകം;
  എണ്ണൽ വൃക്ഷം_code code = വൃക്ഷം_CODE (വ്യഞ്ജകം);
  എണ്ണൽ വൃക്ഷം_code_class kind = വൃക്ഷം_CODE_CLASS (code);
  location_t loc = വ്യഞ്ജകം_LOCATION (വ്യഞ്ജകം);
  വൃക്ഷം op0, op1, op2, op3;
  വൃക്ഷം orig_op0, orig_op1, orig_op2;
  തർക്കം op0_const = സത്യം, op1_const = സത്യം, op2_const = സത്യം;
  തർക്കം op0_const_self = സത്യം, op1_const_self = സത്യം, op2_const_self = സത്യം;
  തർക്കം nowarning = warning_suppressed_p (വ്യഞ്ജകം, OPT_Woverflow);
  തർക്കം unused_p;
  തർക്കം op0_lval = അസത്യം;
  source_range old_range;

  /* Constants, declarations, statements, errors, and anything else not
     counted as an expression cannot usefully be folded further at this
     point.  */
  എങ്കിൽ (!IS_വ്യഞ്ജകം_CODE_CLASS (kind) || kind == tcc_statement)
    {
      /* Except for variables which we can optimize to its initializer.  */
      എങ്കിൽ (VAR_P (വ്യഞ്ജകം) && !lval && (optimize || in_init))
	{
	  എങ്കിൽ (in_init)
	    ret = decl_constant_മൂല്യം_1 (വ്യഞ്ജകം, സത്യം);
	  അല്ലെങ്കിൽ
	    {
	      ret = decl_constant_മൂല്യം (വ്യഞ്ജകം);
	      എങ്കിൽ (ret != വ്യഞ്ജകം
		  && (TYPE_MODE (വൃക്ഷം_TYPE (ret)) == BLKmode
		      || വൃക്ഷം_CODE (വൃക്ഷം_TYPE (ret)) == ARRAY_TYPE))
		തിരികെ വ്യഞ്ജകം;
	    }
	  /* Avoid unwanted tree sharing between the initializer and current
	     function's body where the tree can be modified e.g. by the
	     gimplifier.  */
	  എങ്കിൽ (ret != വ്യഞ്ജകം && വൃക്ഷം_STATIC (വ്യഞ്ജകം))
	    ret = unshare_വ്യഞ്ജകം (ret);
	  തിരികെ ret;
	}
      തിരികെ വ്യഞ്ജകം;
    }

  എങ്കിൽ (IS_വ്യഞ്ജകം_CODE_CLASS (kind))
    old_range = വ്യഞ്ജകം_LOCATION_RANGE (വ്യഞ്ജകം);

  /* Operands of variable-length expressions (function calls) have
     already been folded, as have __builtin_* function calls, and such
     expressions cannot occur in constant expressions.  */
  എങ്കിൽ (kind == tcc_vl_exp)
    {
      *maybe_const_operands = അസത്യം;
      ret = fold (വ്യഞ്ജകം);
      പോകുക out;
    }

  എങ്കിൽ (code == C_MAYBE_CONST_വ്യഞ്ജകം)
    {
      വൃക്ഷം pre = C_MAYBE_CONST_വ്യഞ്ജകം_PRE (വ്യഞ്ജകം);
      വൃക്ഷം inner = C_MAYBE_CONST_വ്യഞ്ജകം_വ്യഞ്ജകം (വ്യഞ്ജകം);
      എങ്കിൽ (C_MAYBE_CONST_വ്യഞ്ജകം_NON_CONST (വ്യഞ്ജകം))
	*maybe_const_operands = അസത്യം;
      എങ്കിൽ (C_MAYBE_CONST_വ്യഞ്ജകം_INT_OPERANDS (വ്യഞ്ജകം))
	{
	  *maybe_const_itself = അസത്യം;
	  inner = c_fully_fold_internal (inner, in_init, maybe_const_operands,
					 maybe_const_itself, സത്യം, lval);
	}
      എങ്കിൽ (pre && !in_init)
	ret = build2 (COMPOUND_വ്യഞ്ജകം, വൃക്ഷം_TYPE (വ്യഞ്ജകം), pre, inner);
      അല്ലെങ്കിൽ
	ret = inner;
      പോകുക out;
    }

  /* Assignment, increment, decrement, function call and comma
     operators, and statement expressions, cannot occur in constant
     expressions if evaluated / outside of sizeof.  (Function calls
     were handled above, though VA_ARG_EXPR is treated like a function
     call here, and statement expressions are handled through
     C_MAYBE_CONST_EXPR to avoid folding inside them.)  */
  തിരഞ്ഞെടുപ്പ് (code)
    {
    അവസ്ഥ MODIFY_വ്യഞ്ജകം:
    അവസ്ഥ PREDECREMENT_വ്യഞ്ജകം:
    അവസ്ഥ PREINCREMENT_വ്യഞ്ജകം:
    അവസ്ഥ POSTDECREMENT_വ്യഞ്ജകം:
    അവസ്ഥ POSTINCREMENT_വ്യഞ്ജകം:
    അവസ്ഥ COMPOUND_വ്യഞ്ജകം:
      *maybe_const_operands = അസത്യം;
      നിർത്തുക;

    അവസ്ഥ VA_ARG_വ്യഞ്ജകം:
    അവസ്ഥ TARGET_വ്യഞ്ജകം:
    അവസ്ഥ BIND_വ്യഞ്ജകം:
    അവസ്ഥ OBJ_TYPE_REF:
      *maybe_const_operands = അസത്യം;
      ret = fold (വ്യഞ്ജകം);
      പോകുക out;

    സ്ഥിരസ്ഥിതി:
      നിർത്തുക;
    }

  /* Fold individual tree codes as appropriate.  */
  തിരഞ്ഞെടുപ്പ് (code)
    {
    അവസ്ഥ COMPOUND_LITERAL_വ്യഞ്ജകം:
      /* Any non-constancy will have been marked in a containing
	 C_MAYBE_CONST_EXPR; there is no more folding to do here.  */
      പോകുക out;

    അവസ്ഥ COMPONENT_REF:
      orig_op0 = op0 = വൃക്ഷം_OPERAND (വ്യഞ്ജകം, 0);
      op1 = വൃക്ഷം_OPERAND (വ്യഞ്ജകം, 1);
      op2 = വൃക്ഷം_OPERAND (വ്യഞ്ജകം, 2);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, lval);
      STRIP_TYPE_NOPS (op0);
      എങ്കിൽ (op0 != orig_op0)
	ret = build3 (COMPONENT_REF, വൃക്ഷം_TYPE (വ്യഞ്ജകം), op0, op1, op2);
      എങ്കിൽ (ret != വ്യഞ്ജകം)
	{
	  വൃക്ഷം_READONLY (ret) = വൃക്ഷം_READONLY (വ്യഞ്ജകം);
	  വൃക്ഷം_THIS_VOLATILE (ret) = വൃക്ഷം_THIS_VOLATILE (വ്യഞ്ജകം);
	}
      എങ്കിൽ (!lval)
	ret = fold (ret);
      പോകുക out;

    അവസ്ഥ ARRAY_REF:
      orig_op0 = op0 = വൃക്ഷം_OPERAND (വ്യഞ്ജകം, 0);
      orig_op1 = op1 = വൃക്ഷം_OPERAND (വ്യഞ്ജകം, 1);
      op2 = വൃക്ഷം_OPERAND (വ്യഞ്ജകം, 2);
      op3 = വൃക്ഷം_OPERAND (വ്യഞ്ജകം, 3);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, lval);
      STRIP_TYPE_NOPS (op0);
      op1 = c_fully_fold_internal (op1, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, അസത്യം);
      STRIP_TYPE_NOPS (op1);
      /* Fold "foo"[2] in initializers.  */
      എങ്കിൽ (!lval && in_init)
	{
	  ret = c_fold_array_ref (വൃക്ഷം_TYPE (വ്യഞ്ജകം), op0, op1);
	  എങ്കിൽ (ret)
	    പോകുക out;
	  ret = വ്യഞ്ജകം;
	}
      എങ്കിൽ (op0 != orig_op0 || op1 != orig_op1)
	ret = build4 (ARRAY_REF, വൃക്ഷം_TYPE (വ്യഞ്ജകം), op0, op1, op2, op3);
      എങ്കിൽ (ret != വ്യഞ്ജകം)
	{
	  വൃക്ഷം_READONLY (ret) = വൃക്ഷം_READONLY (വ്യഞ്ജകം);
	  വൃക്ഷം_SIDE_EFFECTS (ret) = വൃക്ഷം_SIDE_EFFECTS (വ്യഞ്ജകം);
	  വൃക്ഷം_THIS_VOLATILE (ret) = വൃക്ഷം_THIS_VOLATILE (വ്യഞ്ജകം);
	}
      എങ്കിൽ (!lval)
	ret = fold (ret);
      പോകുക out;

    അവസ്ഥ MODIFY_വ്യഞ്ജകം:
    അവസ്ഥ PREDECREMENT_വ്യഞ്ജകം:
    അവസ്ഥ PREINCREMENT_വ്യഞ്ജകം:
    അവസ്ഥ POSTDECREMENT_വ്യഞ്ജകം:
    അവസ്ഥ POSTINCREMENT_വ്യഞ്ജകം:
      op0_lval = സത്യം;
      /* FALLTHRU */
    അവസ്ഥ COMPOUND_വ്യഞ്ജകം:
    അവസ്ഥ PLUS_വ്യഞ്ജകം:
    അവസ്ഥ MINUS_വ്യഞ്ജകം:
    അവസ്ഥ MULT_വ്യഞ്ജകം:
    അവസ്ഥ POINTER_PLUS_വ്യഞ്ജകം:
    അവസ്ഥ POINTER_DIFF_വ്യഞ്ജകം:
    അവസ്ഥ TRUNC_DIV_വ്യഞ്ജകം:
    അവസ്ഥ CEIL_DIV_വ്യഞ്ജകം:
    അവസ്ഥ FLOOR_DIV_വ്യഞ്ജകം:
    അവസ്ഥ TRUNC_MOD_വ്യഞ്ജകം:
    അവസ്ഥ RDIV_വ്യഞ്ജകം:
    അവസ്ഥ EXACT_DIV_വ്യഞ്ജകം:
    അവസ്ഥ LSHIFT_വ്യഞ്ജകം:
    അവസ്ഥ RSHIFT_വ്യഞ്ജകം:
    അവസ്ഥ LROTATE_വ്യഞ്ജകം:
    അവസ്ഥ RROTATE_വ്യഞ്ജകം:
    അവസ്ഥ BIT_IOR_വ്യഞ്ജകം:
    അവസ്ഥ BIT_XOR_വ്യഞ്ജകം:
    അവസ്ഥ BIT_AND_വ്യഞ്ജകം:
    അവസ്ഥ LT_വ്യഞ്ജകം:
    അവസ്ഥ LE_വ്യഞ്ജകം:
    അവസ്ഥ GT_വ്യഞ്ജകം:
    അവസ്ഥ GE_വ്യഞ്ജകം:
    അവസ്ഥ EQ_വ്യഞ്ജകം:
    അവസ്ഥ NE_വ്യഞ്ജകം:
    അവസ്ഥ COMPLEX_വ്യഞ്ജകം:
    അവസ്ഥ TRUTH_AND_വ്യഞ്ജകം:
    അവസ്ഥ TRUTH_OR_വ്യഞ്ജകം:
    അവസ്ഥ TRUTH_XOR_വ്യഞ്ജകം:
    അവസ്ഥ UNORDERED_വ്യഞ്ജകം:
    അവസ്ഥ ORDERED_വ്യഞ്ജകം:
    അവസ്ഥ UNLT_വ്യഞ്ജകം:
    അവസ്ഥ UNLE_വ്യഞ്ജകം:
    അവസ്ഥ UNGT_വ്യഞ്ജകം:
    അവസ്ഥ UNGE_വ്യഞ്ജകം:
    അവസ്ഥ UNEQ_വ്യഞ്ജകം:
    അവസ്ഥ MEM_REF:
      /* Binary operations evaluating both arguments (increment and
	 decrement are binary internally in GCC).  */
      orig_op0 = op0 = വൃക്ഷം_OPERAND (വ്യഞ്ജകം, 0);
      orig_op1 = op1 = വൃക്ഷം_OPERAND (വ്യഞ്ജകം, 1);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const,
				   op0_lval);
      STRIP_TYPE_NOPS (op0);
      /* The RHS of a MODIFY_EXPR was fully folded when building that
	 expression for the sake of conversion warnings.  */
      എങ്കിൽ (code != MODIFY_വ്യഞ്ജകം)
	op1 = c_fully_fold_internal (op1, in_init, maybe_const_operands,
				     maybe_const_itself, for_int_const, അസത്യം);
      STRIP_TYPE_NOPS (op1);

      എങ്കിൽ (for_int_const && (വൃക്ഷം_CODE (op0) != INTEGER_CST
			    || വൃക്ഷം_CODE (op1) != INTEGER_CST))
	പോകുക out;

      എങ്കിൽ (വൃക്ഷം_CODE_CLASS (code) == tcc_comparison
	  && വൃക്ഷം_CODE (വൃക്ഷം_TYPE (op0)) == NULLPTR_TYPE
	  && വൃക്ഷം_CODE (വൃക്ഷം_TYPE (op1)) == NULLPTR_TYPE)
	{
	  തിരഞ്ഞെടുപ്പ് (code)
	    {
	    അവസ്ഥ EQ_വ്യഞ്ജകം:
	      ret = constant_boolean_കണ്ണി (സത്യം, വൃക്ഷം_TYPE (വ്യഞ്ജകം));
	      നിർത്തുക;
	    അവസ്ഥ NE_വ്യഞ്ജകം:
	      ret = constant_boolean_കണ്ണി (അസത്യം, വൃക്ഷം_TYPE (വ്യഞ്ജകം));
	      നിർത്തുക;
	    സ്ഥിരസ്ഥിതി:
	      gcc_unreachable ();
	    }
	  ret = omit_two_operands_loc (loc, വൃക്ഷം_TYPE (വ്യഞ്ജകം), ret,
				       op0, op1);
	}
      അല്ലെങ്കിൽ എങ്കിൽ (op0 != orig_op0 || op1 != orig_op1 || in_init)
	ret = in_init
	  ? fold_build2_initializer_loc (loc, code, വൃക്ഷം_TYPE (വ്യഞ്ജകം), op0, op1)
	  : fold_build2_loc (loc, code, വൃക്ഷം_TYPE (വ്യഞ്ജകം), op0, op1);
      അല്ലെങ്കിൽ
	ret = fold (വ്യഞ്ജകം);
      എങ്കിൽ (വൃക്ഷം_OVERFLOW_P (ret)
	  && !വൃക്ഷം_OVERFLOW_P (op0)
	  && !(ദ്വിമാന_CLASS_P (op0) && വൃക്ഷം_OVERFLOW_P (വൃക്ഷം_OPERAND (op0, 1)))
	  && !വൃക്ഷം_OVERFLOW_P (op1))
	overflow_warning (വ്യഞ്ജകം_LOC_OR_LOC (വ്യഞ്ജകം, നിവേശം_location), ret, വ്യഞ്ജകം);
      എങ്കിൽ (code == LSHIFT_വ്യഞ്ജകം
	  && വൃക്ഷം_CODE (orig_op0) != INTEGER_CST
	  && (വൃക്ഷം_CODE (വൃക്ഷം_TYPE (orig_op0)) == INTEGER_TYPE
	      || വൃക്ഷം_CODE (വൃക്ഷം_TYPE (orig_op0)) == BITINT_TYPE)
	  && വൃക്ഷം_CODE (op0) == INTEGER_CST
	  && c_inhibit_evaluation_warnings == 0
	  && !TYPE_OVERFLOW_WRAPS (വൃക്ഷം_TYPE (orig_op0))
	  && വൃക്ഷം_int_cst_sgn (op0) < 0)
	warning_at (loc, OPT_Wshift_negative_മൂല്യം,
		    "left shift of negative value");
      എങ്കിൽ ((code == LSHIFT_വ്യഞ്ജകം
	   || code == RSHIFT_വ്യഞ്ജകം
	   || code == LROTATE_വ്യഞ്ജകം
	   || code == RROTATE_വ്യഞ്ജകം)
	  && വൃക്ഷം_CODE (orig_op1) != INTEGER_CST
	  && വൃക്ഷം_CODE (op1) == INTEGER_CST
	  && വൃക്ഷം_CODE (വൃക്ഷം_TYPE (orig_op1)) == INTEGER_TYPE
	  && c_inhibit_evaluation_warnings == 0)
	{
	  എങ്കിൽ (വൃക്ഷം_int_cst_sgn (op1) < 0)
	    warning_at (loc, OPT_Wshift_എണ്ണം_negative,
			(code == LSHIFT_വ്യഞ്ജകം
			 ? G_("left shift count is negative")
			 : G_("right shift count is negative")));
	  അല്ലെങ്കിൽ എങ്കിൽ ((വൃക്ഷം_CODE (വൃക്ഷം_TYPE (orig_op0)) == INTEGER_TYPE
		    || വൃക്ഷം_CODE (വൃക്ഷം_TYPE (orig_op0)) == BITINT_TYPE
		    || വൃക്ഷം_CODE (വൃക്ഷം_TYPE (orig_op0)) == FIXED_POINT_TYPE)
		   && compare_വൃക്ഷം_int (op1,
					TYPE_PRECISION (വൃക്ഷം_TYPE (orig_op0)))
		      >= 0
		   && !warning_suppressed_p (വ്യഞ്ജകം, OPT_Wshift_എണ്ണം_overflow))
	    warning_at (loc, OPT_Wshift_എണ്ണം_overflow,
			(code == LSHIFT_വ്യഞ്ജകം
			 ? G_("left shift count >= width of type")
			 : G_("right shift count >= width of type")));
	  അല്ലെങ്കിൽ എങ്കിൽ (വൃക്ഷം_CODE (വൃക്ഷം_TYPE (orig_op0)) == VECTOR_TYPE
		   && compare_വൃക്ഷം_int (op1,
					TYPE_PRECISION (വൃക്ഷം_TYPE (വൃക്ഷം_TYPE (orig_op0))))
		      >= 0)
	    warning_at (loc, OPT_Wshift_എണ്ണം_overflow,
			code == LSHIFT_വ്യഞ്ജകം
			? G_("left shift count >= width of vector element")
			: G_("right shift count >= width of vector element"));
	}
      എങ്കിൽ (code == LSHIFT_വ്യഞ്ജകം
	  /* If either OP0 has been folded to INTEGER_CST...  */
	  && ((വൃക്ഷം_CODE (orig_op0) != INTEGER_CST
	       && (വൃക്ഷം_CODE (വൃക്ഷം_TYPE (orig_op0)) == INTEGER_TYPE
		   || വൃക്ഷം_CODE (വൃക്ഷം_TYPE (orig_op0)) == BITINT_TYPE)
	       && വൃക്ഷം_CODE (op0) == INTEGER_CST)
	      /* ...or if OP1 has been folded to INTEGER_CST...  */
	      || (വൃക്ഷം_CODE (orig_op1) != INTEGER_CST
		  && (വൃക്ഷം_CODE (വൃക്ഷം_TYPE (orig_op1)) == INTEGER_TYPE
		      || വൃക്ഷം_CODE (വൃക്ഷം_TYPE (orig_op1)) == BITINT_TYPE)
		  && വൃക്ഷം_CODE (op1) == INTEGER_CST))
	  && c_inhibit_evaluation_warnings == 0)
	/* ...then maybe we can detect an overflow.  */
	maybe_warn_shift_overflow (loc, op0, op1);
      എങ്കിൽ ((code == TRUNC_DIV_വ്യഞ്ജകം
	   || code == CEIL_DIV_വ്യഞ്ജകം
	   || code == FLOOR_DIV_വ്യഞ്ജകം
	   || code == EXACT_DIV_വ്യഞ്ജകം
	   || code == TRUNC_MOD_വ്യഞ്ജകം)
	  && വൃക്ഷം_CODE (orig_op1) != INTEGER_CST
	  && വൃക്ഷം_CODE (op1) == INTEGER_CST
	  && (വൃക്ഷം_CODE (വൃക്ഷം_TYPE (orig_op0)) == INTEGER_TYPE
	      || വൃക്ഷം_CODE (വൃക്ഷം_TYPE (orig_op0)) == BITINT_TYPE
	      || വൃക്ഷം_CODE (വൃക്ഷം_TYPE (orig_op0)) == FIXED_POINT_TYPE)
	  && (വൃക്ഷം_CODE (വൃക്ഷം_TYPE (orig_op1)) == INTEGER_TYPE
	      || വൃക്ഷം_CODE (വൃക്ഷം_TYPE (orig_op1)) == BITINT_TYPE))
	warn_for_div_by_zero (loc, op1);
      എങ്കിൽ (code == MEM_REF
	  && ret != വ്യഞ്ജകം
	  && വൃക്ഷം_CODE (ret) == MEM_REF)
	{
	  വൃക്ഷം_READONLY (ret) = വൃക്ഷം_READONLY (വ്യഞ്ജകം);
	  വൃക്ഷം_SIDE_EFFECTS (ret) = വൃക്ഷം_SIDE_EFFECTS (വ്യഞ്ജകം);
	  വൃക്ഷം_THIS_VOLATILE (ret) = വൃക്ഷം_THIS_VOLATILE (വ്യഞ്ജകം);
	}
      പോകുക out;

    അവസ്ഥ ADDR_വ്യഞ്ജകം:
      op0_lval = സത്യം;
      പോകുക unary;
    അവസ്ഥ REALPART_വ്യഞ്ജകം:
    അവസ്ഥ IMAGPART_വ്യഞ്ജകം:
    അവസ്ഥ VIEW_CONVERT_വ്യഞ്ജകം:
      op0_lval = lval;
      /* FALLTHRU */
    അവസ്ഥ INDIRECT_REF:
    അവസ്ഥ FIX_TRUNC_വ്യഞ്ജകം:
    അവസ്ഥ FLOAT_വ്യഞ്ജകം:
    CASE_CONVERT:
    അവസ്ഥ ADDR_SPACE_CONVERT_വ്യഞ്ജകം:
    അവസ്ഥ NON_LVALUE_വ്യഞ്ജകം:
    അവസ്ഥ NEGATE_വ്യഞ്ജകം:
    അവസ്ഥ BIT_NOT_വ്യഞ്ജകം:
    അവസ്ഥ TRUTH_NOT_വ്യഞ്ജകം:
    അവസ്ഥ CONJ_വ്യഞ്ജകം:
    അവസ്ഥ PAREN_വ്യഞ്ജകം:
    unary:
      /* Unary operations.  */
      orig_op0 = op0 = വൃക്ഷം_OPERAND (വ്യഞ്ജകം, 0);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const,
				   op0_lval);
      STRIP_TYPE_NOPS (op0);

      എങ്കിൽ (for_int_const && വൃക്ഷം_CODE (op0) != INTEGER_CST)
	പോകുക out;

      /* ??? Cope with user tricks that amount to offsetof.  The middle-end is
	 not prepared to deal with them if they occur in initializers.  */
      എങ്കിൽ (op0 != orig_op0
	  && code == ADDR_വ്യഞ്ജകം
	  && (op1 = get_base_address (op0)) != NULL_വൃക്ഷം
	  && INDIRECT_REF_P (op1)
	  && വൃക്ഷം_CONSTANT (വൃക്ഷം_OPERAND (op1, 0)))
	ret = fold_offsetof (op0, വൃക്ഷം_TYPE (വ്യഞ്ജകം));
      അല്ലെങ്കിൽ എങ്കിൽ (op0 != orig_op0 || in_init)
	ret = in_init
	  ? fold_build1_initializer_loc (loc, code, വൃക്ഷം_TYPE (വ്യഞ്ജകം), op0)
	  : fold_build1_loc (loc, code, വൃക്ഷം_TYPE (വ്യഞ്ജകം), op0);
      അല്ലെങ്കിൽ
	ret = fold (വ്യഞ്ജകം);
      എങ്കിൽ (code == INDIRECT_REF
	  && ret != വ്യഞ്ജകം
	  && INDIRECT_REF_P (ret))
	{
	  വൃക്ഷം_READONLY (ret) = വൃക്ഷം_READONLY (വ്യഞ്ജകം);
	  വൃക്ഷം_SIDE_EFFECTS (ret) = വൃക്ഷം_SIDE_EFFECTS (വ്യഞ്ജകം);
	  വൃക്ഷം_THIS_VOLATILE (ret) = വൃക്ഷം_THIS_VOLATILE (വ്യഞ്ജകം);
	}
      തിരഞ്ഞെടുപ്പ് (code)
	{
	അവസ്ഥ FIX_TRUNC_വ്യഞ്ജകം:
	അവസ്ഥ FLOAT_വ്യഞ്ജകം:
	CASE_CONVERT:
	  /* Don't warn about explicit conversions.  We will already
	     have warned about suspect implicit conversions.  */
	  നിർത്തുക;

	സ്ഥിരസ്ഥിതി:
	  എങ്കിൽ (വൃക്ഷം_OVERFLOW_P (ret) && !വൃക്ഷം_OVERFLOW_P (op0))
	    overflow_warning (വ്യഞ്ജകം_LOCATION (വ്യഞ്ജകം), ret, op0);
	  നിർത്തുക;
	}
      പോകുക out;

    അവസ്ഥ TRUTH_ANDIF_വ്യഞ്ജകം:
    അവസ്ഥ TRUTH_ORIF_വ്യഞ്ജകം:
      /* Binary operations not necessarily evaluating both
	 arguments.  */
      orig_op0 = op0 = വൃക്ഷം_OPERAND (വ്യഞ്ജകം, 0);
      orig_op1 = op1 = വൃക്ഷം_OPERAND (വ്യഞ്ജകം, 1);
      op0 = c_fully_fold_internal (op0, in_init, &op0_const, &op0_const_self,
				   for_int_const, അസത്യം);
      STRIP_TYPE_NOPS (op0);

      unused_p = (op0 == (code == TRUTH_ANDIF_വ്യഞ്ജകം
			  ? truthvalue_false_കണ്ണി
			  : truthvalue_true_കണ്ണി));
      c_disable_warnings (unused_p);
      op1 = c_fully_fold_internal (op1, in_init, &op1_const, &op1_const_self,
				   for_int_const, അസത്യം);
      STRIP_TYPE_NOPS (op1);
      c_enable_warnings (unused_p);

      എങ്കിൽ (for_int_const
	  && (വൃക്ഷം_CODE (op0) != INTEGER_CST
	      /* Require OP1 be an INTEGER_CST only if it's evaluated.  */
	      || (!unused_p && വൃക്ഷം_CODE (op1) != INTEGER_CST)))
	പോകുക out;

      എങ്കിൽ (op0 != orig_op0 || op1 != orig_op1 || in_init)
	ret = in_init
	  ? fold_build2_initializer_loc (loc, code, വൃക്ഷം_TYPE (വ്യഞ്ജകം), op0, op1)
	  : fold_build2_loc (loc, code, വൃക്ഷം_TYPE (വ്യഞ്ജകം), op0, op1);
      അല്ലെങ്കിൽ
	ret = fold (വ്യഞ്ജകം);
      *maybe_const_operands &= op0_const;
      *maybe_const_itself &= op0_const_self;
      എങ്കിൽ (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && (code == TRUTH_ANDIF_വ്യഞ്ജകം
		? op0 == truthvalue_false_കണ്ണി
		: op0 == truthvalue_true_കണ്ണി)))
	*maybe_const_operands &= op1_const;
      എങ്കിൽ (!(op0_const
	    && op0_const_self
	    && (code == TRUTH_ANDIF_വ്യഞ്ജകം
		? op0 == truthvalue_false_കണ്ണി
		: op0 == truthvalue_true_കണ്ണി)))
	*maybe_const_itself &= op1_const_self;
      പോകുക out;

    അവസ്ഥ COND_വ്യഞ്ജകം:
      orig_op0 = op0 = വൃക്ഷം_OPERAND (വ്യഞ്ജകം, 0);
      orig_op1 = op1 = വൃക്ഷം_OPERAND (വ്യഞ്ജകം, 1);
      orig_op2 = op2 = വൃക്ഷം_OPERAND (വ്യഞ്ജകം, 2);
      op0 = c_fully_fold_internal (op0, in_init, &op0_const, &op0_const_self,
				   for_int_const, അസത്യം);

      STRIP_TYPE_NOPS (op0);
      c_disable_warnings (op0 == truthvalue_false_കണ്ണി);
      op1 = c_fully_fold_internal (op1, in_init, &op1_const, &op1_const_self,
				   for_int_const, അസത്യം);
      STRIP_TYPE_NOPS (op1);
      c_enable_warnings (op0 == truthvalue_false_കണ്ണി);

      c_disable_warnings (op0 == truthvalue_true_കണ്ണി);
      op2 = c_fully_fold_internal (op2, in_init, &op2_const, &op2_const_self,
				   for_int_const, അസത്യം);
      STRIP_TYPE_NOPS (op2);
      c_enable_warnings (op0 == truthvalue_true_കണ്ണി);

      എങ്കിൽ (for_int_const
	  && (വൃക്ഷം_CODE (op0) != INTEGER_CST
	      /* Only the evaluated operand must be an INTEGER_CST.  */
	      || (op0 == truthvalue_true_കണ്ണി
		  ? വൃക്ഷം_CODE (op1) != INTEGER_CST
		  : വൃക്ഷം_CODE (op2) != INTEGER_CST)))
	പോകുക out;

      എങ്കിൽ (op0 != orig_op0 || op1 != orig_op1 || op2 != orig_op2)
	ret = fold_build3_loc (loc, code, വൃക്ഷം_TYPE (വ്യഞ്ജകം), op0, op1, op2);
      അല്ലെങ്കിൽ
	ret = fold (വ്യഞ്ജകം);
      *maybe_const_operands &= op0_const;
      *maybe_const_itself &= op0_const_self;
      എങ്കിൽ (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && op0 == truthvalue_false_കണ്ണി))
	*maybe_const_operands &= op1_const;
      എങ്കിൽ (!(op0_const
	    && op0_const_self
	    && op0 == truthvalue_false_കണ്ണി))
	*maybe_const_itself &= op1_const_self;
      എങ്കിൽ (!(flag_isoc99
	    && op0_const
	    && op0_const_self
	    && op0 == truthvalue_true_കണ്ണി))
	*maybe_const_operands &= op2_const;
      എങ്കിൽ (!(op0_const
	    && op0_const_self
	    && op0 == truthvalue_true_കണ്ണി))
	*maybe_const_itself &= op2_const_self;
      പോകുക out;

    അവസ്ഥ VEC_COND_വ്യഞ്ജകം:
      orig_op0 = op0 = വൃക്ഷം_OPERAND (വ്യഞ്ജകം, 0);
      orig_op1 = op1 = വൃക്ഷം_OPERAND (വ്യഞ്ജകം, 1);
      orig_op2 = op2 = വൃക്ഷം_OPERAND (വ്യഞ്ജകം, 2);
      op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, അസത്യം);
      STRIP_TYPE_NOPS (op0);
      op1 = c_fully_fold_internal (op1, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, അസത്യം);
      STRIP_TYPE_NOPS (op1);
      op2 = c_fully_fold_internal (op2, in_init, maybe_const_operands,
				   maybe_const_itself, for_int_const, അസത്യം);
      STRIP_TYPE_NOPS (op2);

      എങ്കിൽ (op0 != orig_op0 || op1 != orig_op1 || op2 != orig_op2)
	ret = fold_build3_loc (loc, code, വൃക്ഷം_TYPE (വ്യഞ്ജകം), op0, op1, op2);
      അല്ലെങ്കിൽ
	ret = fold (വ്യഞ്ജകം);
      പോകുക out;

    അവസ്ഥ EXCESS_PRECISION_വ്യഞ്ജകം:
      /* Each case where an operand with excess precision may be
	 encountered must remove the EXCESS_PRECISION_EXPR around
	 inner operands and possibly put one around the whole
	 expression or possibly convert to the semantic type (which
	 c_fully_fold does); we cannot tell at this stage which is
	 appropriate in any particular case.  */
      gcc_unreachable ();

    അവസ്ഥ SAVE_വ്യഞ്ജകം:
      /* Make sure to fold the contents of a SAVE_EXPR exactly once.  */
      op0 = വൃക്ഷം_OPERAND (വ്യഞ്ജകം, 0);
      എങ്കിൽ (!SAVE_വ്യഞ്ജകം_FOLDED_P (വ്യഞ്ജകം))
	{
	  op0 = c_fully_fold_internal (op0, in_init, maybe_const_operands,
				       maybe_const_itself, for_int_const,
				       അസത്യം);
	  വൃക്ഷം_OPERAND (വ്യഞ്ജകം, 0) = op0;
	  SAVE_വ്യഞ്ജകം_FOLDED_P (വ്യഞ്ജകം) = സത്യം;
	}
      /* Return the SAVE_EXPR operand if it is invariant.  */
      എങ്കിൽ (വൃക്ഷം_invariant_p (op0))
	ret = op0;
      പോകുക out;

    സ്ഥിരസ്ഥിതി:
      /* Various codes may appear through folding built-in functions
	 and their arguments.  */
      പോകുക out;
    }

 out:
  /* Some folding may introduce NON_LVALUE_EXPRs; all lvalue checks
     have been done by this point, so remove them again.  */
  nowarning |= warning_suppressed_p (ret, OPT_Woverflow);
  STRIP_TYPE_NOPS (ret);
  എങ്കിൽ (nowarning && !warning_suppressed_p (ret, OPT_Woverflow))
    {
      എങ്കിൽ (!CAN_HAVE_LOCATION_P (ret))
	ret = build1 (NOP_വ്യഞ്ജകം, വൃക്ഷം_TYPE (ret), ret);
      suppress_warning (ret, OPT_Woverflow);
    }
  എങ്കിൽ (ret != വ്യഞ്ജകം)
    {
      protected_set_വ്യഞ്ജകം_location (ret, loc);
      എങ്കിൽ (IS_വ്യഞ്ജകം_CODE_CLASS (kind))
	set_source_range (ret, old_range.m_start, old_range.m_finish);
    }
  തിരികെ ret;
}

/* Fold X for consideration by one of the warning functions when checking
   whether an expression has a constant value.  */

വൃക്ഷം
fold_for_warn (വൃക്ഷം x)
{
  /* The C front-end has already folded X appropriately.  */
  തിരികെ x;
}
