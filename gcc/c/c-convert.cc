/* Language-level data type conversion for GNU C.
   Copyright (C) 1987-2026 Free Software Foundation, Inc.

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


/* This file contains the functions for converting C expressions
   to different data types.  The only entry point is `convert'.
   Every language front end must have a `convert' function
   but what kind of conversions it does will depend on the language.  */

#ضمن "config.h"
#ضمن "system.h"
#ضمن "coretypes.h"
#ضمن "target.h"
#ضمن "c-tree.h"
#ضمن "convert.h"
#ضمن "langhooks.h"
#ضمن "ubsan.h"
#ضمن "stringpool.h"
#ضمن "attribs.h"
#ضمن "asan.h"

/* Change of width--truncation and extension of integers or reals--
   is represented with NOP_EXPR.  Proper functioning of many things
   assumes that no other conversions can be NOP_EXPRs.

   Conversion between integer and pointer is represented with CONVERT_EXPR.
   Converting integer to real uses FLOAT_EXPR
   and real to integer uses FIX_TRUNC_EXPR.

   Here is a list of all the functions that assume that widening and
   narrowing is always done with a NOP_EXPR:
     In convert.cc, convert_to_integer.
     In c-typeck.cc, build_binary_op (boolean ops), and
	c_common_truthvalue_conversion.
     In expr.cc: expand_expr, for operands of a MULT_EXPR.
     In fold-const.cc: fold.
     In tree.cc: get_narrower and get_unwidened.  */

/* Subroutines of `convert'.  */



/* Create an expression whose value is that of EXPR,
   converted to type TYPE.  The TREE_TYPE of the value
   is always TYPE.  This function implements all reasonable
   conversions; callers should filter out those that are
   not permitted by the language being compiled.
   INIT_CONST is true if the conversion is for arithmetic types for a static
   initializer and folding must apply accordingly (discarding floating-point
   exceptions and assuming the default rounding mode is in effect).  */

ساكن tree
c_convert (tree type, tree expr, منطقي init_const)
{
  tree e = expr;
  تعداد tree_code code = TREE_CODE (type);
  ثابت حرف *invalid_conv_diag;
  tree ret;
  location_t loc = EXPR_LOCATION (expr);

  ܐܢ (type == error_mark_node
      || error_operand_p (expr))
    ܦܢܐ error_mark_node;

  ܐܢ ((invalid_conv_diag
       = targetm.invalid_conversion (TREE_TYPE (expr), type)))
    {
      error (invalid_conv_diag);
      ܦܢܐ error_mark_node;
    }

  ܐܢ (type == TREE_TYPE (expr))
    ܦܢܐ expr;
  ret = targetm.convert_to_type (type, expr);
  ܐܢ (ret)
      ܦܢܐ ret;

  STRIP_TYPE_NOPS (e);

  ܐܢ (TYPE_MAIN_VARIANT (type) == TYPE_MAIN_VARIANT (TREE_TYPE (expr))
      && (TREE_CODE (TREE_TYPE (expr)) != COMPLEX_TYPE
	  || TREE_CODE (e) == COMPLEX_EXPR))
    ܦܢܐ fold_convert_loc (loc, type, expr);
  ܐܢ (TREE_CODE (TREE_TYPE (expr)) == ERROR_MARK)
    ܦܢܐ error_mark_node;
  ܐܢ (VOID_TYPE_P (TREE_TYPE (expr)))
    {
      error ("void value not ignored as it ought to be");
      ܦܢܐ error_mark_node;
    }

  {
    tree false_value, true_value;
    ܐܢ (c_hardbool_type_attr (type, &false_value, &true_value))
      {
	منطقي save = in_late_binary_op;
	in_late_binary_op = ܫܪܪܐ;
	expr = c_objc_common_truthvalue_conversion (input_location, expr);
	in_late_binary_op = save;

	ܦܢܐ fold_build3_loc (loc, COND_EXPR, type,
				expr, true_value, false_value);
      }
  }

  بدل (code)
    {
    حالة VOID_TYPE:
      ܦܢܐ fold_convert_loc (loc, type, e);

    حالة ENUMERAL_TYPE:
      ܐܢ (ENUM_UNDERLYING_TYPE (type) != NULL_TREE
	  && TREE_CODE (ENUM_UNDERLYING_TYPE (type)) == BOOLEAN_TYPE)
	اذهب convert_to_boolean;
      gcc_fallthrough ();

    حالة INTEGER_TYPE:
    حالة BITINT_TYPE:
      ܐܢ (sanitize_flags_p (SANITIZE_FLOAT_CAST)
	  && current_function_decl != NULL_TREE
	  && SCALAR_FLOAT_TYPE_P (TREE_TYPE (expr))
	  && COMPLETE_TYPE_P (type))
	{
	  expr = save_expr (expr);
	  expr = c_fully_fold (expr, init_const, عدم);
	  tree check = ubsan_instrument_float_cast (loc, type, expr);
	  expr = fold_build1 (FIX_TRUNC_EXPR, type, expr);
	  ܐܢ (check == NULL_TREE)
	    ܦܢܐ expr;
	  ܦܢܐ fold_build2 (COMPOUND_EXPR, TREE_TYPE (expr), check, expr);
	}
      ret = convert_to_integer (type, e);
      اذهب maybe_fold;

    حالة BOOLEAN_TYPE:
    convert_to_boolean:
      ܦܢܐ c_objc_common_truthvalue_conversion (input_location, expr, type);

    حالة POINTER_TYPE:
      /* The type nullptr_t may be converted to a pointer type.  The result is
	 a null pointer value.  */
      ܐܢ (NULLPTR_TYPE_P (TREE_TYPE (e)))
	{
	  /* To make sure that (void *)nullptr is not a null pointer constant,
	     build_c_cast will create an additional NOP_EXPR around the result
	     of this conversion.  */
	  ܐܢ (TREE_SIDE_EFFECTS (e))
	    ret = build2 (COMPOUND_EXPR, type, e, build_int_cst (type, 0));
	  ܐܚܪܢܐ
	    ret = build_int_cst (type, 0);
	  اذهب maybe_fold;
	}
      gcc_fallthrough ();
    حالة REFERENCE_TYPE:
      ret = convert_to_pointer (type, e);
      اذهب maybe_fold;

    حالة NULLPTR_TYPE:
      /* A null pointer constant or value of type nullptr_t may be
	 converted to nullptr_t.  The latter case has already been
	 handled.  build_c_cast will create an additional NOP_EXPR to
	 ensure the result of the conversion is not itself a null
	 pointer constant.  */
      ܐܢ (null_pointer_constant_p (expr))
	{
	  ret = build_int_cst (type, 0);
	  اذهب maybe_fold;
	}
      اكسر;

    حالة REAL_TYPE:
      ret = convert_to_real (type, e);
      اذهب maybe_fold;

    حالة FIXED_POINT_TYPE:
      ret = convert_to_fixed (type, e);
      اذهب maybe_fold;

    حالة COMPLEX_TYPE:
      ret = convert_to_complex (type, e);
      اذهب maybe_fold;

    حالة VECTOR_TYPE:
      ܐܢ (gnu_vector_type_p (type)
	  || gnu_vector_type_p (TREE_TYPE (e))
	  /* Allow conversions between compatible non-GNU vector types
	     when -flax-vector-conversions is passed.  The whole purpose
	     of the option is to bend the normal type rules and accept
	     nonconforming code.  */
	  || (flag_lax_vector_conversions
	      && VECTOR_TYPE_P (TREE_TYPE (e))
	      && vector_types_convertible_p (type, TREE_TYPE (e), ܕܓܠܐ)))
	{
	  ret = convert_to_vector (type, e);
	  اذهب maybe_fold;
	}
      اكسر;

    حالة RECORD_TYPE:
    حالة UNION_TYPE:
      ܐܢ (lang_hooks.types_compatible_p (type, TREE_TYPE (expr)))
	ܦܢܐ e;
      اكسر;

    افتراضي:
      اكسر;

    maybe_fold:
      ܐܢ (TREE_CODE (ret) != C_MAYBE_CONST_EXPR)
	ret = init_const ? fold_init (ret) : fold (ret);
      ܦܢܐ ret;
    }

  /* If we are converting to nullptr_t, don't say "non-scalar type" because
     the nullptr_t type is a scalar type.  Only nullptr_t or a null pointer
     constant shall be converted to nullptr_t.  */
  ܐܢ (code == NULLPTR_TYPE)
    {
      error ("conversion from %qT to %qT", TREE_TYPE (e), type);
      inform (input_location,
	      "only %qT or a null pointer constant can be converted to %qT",
	      type, type);
    }
  ܐܚܪܢܐ
    error ("conversion to non-scalar type requested");
  ܦܢܐ error_mark_node;
}

/* Create an expression whose value is that of EXPR, converted to type TYPE.
   The TREE_TYPE of the value is always TYPE.  This function implements all
   reasonable conversions; callers should filter out those that are not
   permitted by the language being compiled.  */

tree
convert (tree type, tree expr)
{
  ܦܢܐ c_convert (type, expr, ܕܓܠܐ);
}

/* Create an expression whose value is that of EXPR, converted to type TYPE, in
   a static initializer.  The TREE_TYPE of the value is always TYPE.  This
   function implements all reasonable conversions; callers should filter out
   those that are not permitted by the language being compiled.  */

tree
convert_init (tree type, tree expr)
{
  ܦܢܐ c_convert (type, expr, ܫܪܪܐ);
}
