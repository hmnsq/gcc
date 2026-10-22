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

#شامل "config.h"
#شامل "system.h"
#شامل "coretypes.h"
#شامل "target.h"
#شامل "c-tree.h"
#شامل "convert.h"
#شامل "langhooks.h"
#شامل "ubsan.h"
#شامل "stringpool.h"
#شامل "attribs.h"
#شامل "asan.h"

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

ایستا درخت
c_convert (درخت type, درخت عبارت, منطقی init_const)
{
  درخت e = عبارت;
  شمارش درخت_code code = درخت_CODE (type);
  ثابت نویسه *invalid_conv_diag;
  درخت ret;
  location_t loc = عبارت_LOCATION (عبارت);

  اگر (type == error_mark_گره
      || error_operand_p (عبارت))
    بازگشت error_mark_گره;

  اگر ((invalid_conv_diag
       = targetm.invalid_conversion (درخت_TYPE (عبارت), type)))
    {
      error (invalid_conv_diag);
      بازگشت error_mark_گره;
    }

  اگر (type == درخت_TYPE (عبارت))
    بازگشت عبارت;
  ret = targetm.convert_to_type (type, عبارت);
  اگر (ret)
      بازگشت ret;

  STRIP_TYPE_NOPS (e);

  اگر (TYPE_MAIN_VARIANT (type) == TYPE_MAIN_VARIANT (درخت_TYPE (عبارت))
      && (درخت_CODE (درخت_TYPE (عبارت)) != COMPLEX_TYPE
	  || درخت_CODE (e) == COMPLEX_عبارت))
    بازگشت fold_convert_loc (loc, type, عبارت);
  اگر (درخت_CODE (درخت_TYPE (عبارت)) == ERROR_MARK)
    بازگشت error_mark_گره;
  اگر (VOID_TYPE_P (درخت_TYPE (عبارت)))
    {
      error ("void value not ignored as it ought to be");
      بازگشت error_mark_گره;
    }

  {
    درخت false_مقدار, true_مقدار;
    اگر (c_hardbool_type_attr (type, &false_مقدار, &true_مقدار))
      {
	منطقی save = in_late_دودویی_op;
	in_late_دودویی_op = درست;
	عبارت = c_objc_common_truthvalue_conversion (درون_داد_location, عبارت);
	in_late_دودویی_op = save;

	بازگشت fold_build3_loc (loc, COND_عبارت, type,
				عبارت, true_مقدار, false_مقدار);
      }
  }

  انتخاب (code)
    {
    حالت VOID_TYPE:
      بازگشت fold_convert_loc (loc, type, e);

    حالت ENUMERAL_TYPE:
      اگر (ENUM_UNDERLYING_TYPE (type) != NULL_درخت
	  && درخت_CODE (ENUM_UNDERLYING_TYPE (type)) == BOOLEAN_TYPE)
	برو convert_to_boolean;
      gcc_fallthrough ();

    حالت INTEGER_TYPE:
    حالت BITINT_TYPE:
      اگر (sanitize_flags_p (SANITIZE_FLOAT_CAST)
	  && current_function_decl != NULL_درخت
	  && SCALAR_FLOAT_TYPE_P (درخت_TYPE (عبارت))
	  && COMPLETE_TYPE_P (type))
	{
	  عبارت = save_عبارت (عبارت);
	  عبارت = c_fully_fold (عبارت, init_const, پوچ);
	  درخت check = ubsan_instrument_float_cast (loc, type, عبارت);
	  عبارت = fold_build1 (FIX_TRUNC_عبارت, type, عبارت);
	  اگر (check == NULL_درخت)
	    بازگشت عبارت;
	  بازگشت fold_build2 (COMPOUND_عبارت, درخت_TYPE (عبارت), check, عبارت);
	}
      ret = convert_to_integer (type, e);
      برو maybe_fold;

    حالت BOOLEAN_TYPE:
    convert_to_boolean:
      بازگشت c_objc_common_truthvalue_conversion (درون_داد_location, عبارت, type);

    حالت POINTER_TYPE:
      /* The type nullptr_t may be converted to a pointer type.  The result is
	 a null pointer value.  */
      اگر (NULLPTR_TYPE_P (درخت_TYPE (e)))
	{
	  /* To make sure that (void *)nullptr is not a null pointer constant,
	     build_c_cast will create an additional NOP_EXPR around the result
	     of this conversion.  */
	  اگر (درخت_SIDE_EFFECTS (e))
	    ret = build2 (COMPOUND_عبارت, type, e, build_int_cst (type, 0));
	  وگرنه
	    ret = build_int_cst (type, 0);
	  برو maybe_fold;
	}
      gcc_fallthrough ();
    حالت REFERENCE_TYPE:
      ret = convert_to_pointer (type, e);
      برو maybe_fold;

    حالت NULLPTR_TYPE:
      /* A null pointer constant or value of type nullptr_t may be
	 converted to nullptr_t.  The latter case has already been
	 handled.  build_c_cast will create an additional NOP_EXPR to
	 ensure the result of the conversion is not itself a null
	 pointer constant.  */
      اگر (null_pointer_constant_p (عبارت))
	{
	  ret = build_int_cst (type, 0);
	  برو maybe_fold;
	}
      بشکن;

    حالت REAL_TYPE:
      ret = convert_to_real (type, e);
      برو maybe_fold;

    حالت FIXED_POINT_TYPE:
      ret = convert_to_fixed (type, e);
      برو maybe_fold;

    حالت COMPLEX_TYPE:
      ret = convert_to_complex (type, e);
      برو maybe_fold;

    حالت VECTOR_TYPE:
      اگر (gnu_vector_type_p (type)
	  || gnu_vector_type_p (درخت_TYPE (e))
	  /* Allow conversions between compatible non-GNU vector types
	     when -flax-vector-conversions is passed.  The whole purpose
	     of the option is to bend the normal type rules and accept
	     nonconforming code.  */
	  || (flag_lax_vector_conversions
	      && VECTOR_TYPE_P (درخت_TYPE (e))
	      && vector_types_convertible_p (type, درخت_TYPE (e), نادرست)))
	{
	  ret = convert_to_vector (type, e);
	  برو maybe_fold;
	}
      بشکن;

    حالت RECORD_TYPE:
    حالت UNION_TYPE:
      اگر (lang_hooks.types_compatible_p (type, درخت_TYPE (عبارت)))
	بازگشت e;
      بشکن;

    پیشفرض:
      بشکن;

    maybe_fold:
      اگر (درخت_CODE (ret) != C_MAYBE_CONST_عبارت)
	ret = init_const ? fold_init (ret) : fold (ret);
      بازگشت ret;
    }

  /* If we are converting to nullptr_t, don't say "non-scalar type" because
     the nullptr_t type is a scalar type.  Only nullptr_t or a null pointer
     constant shall be converted to nullptr_t.  */
  اگر (code == NULLPTR_TYPE)
    {
      error ("conversion from %qT to %qT", درخت_TYPE (e), type);
      inform (درون_داد_location,
	      "only %qT or a null pointer constant can be converted to %qT",
	      type, type);
    }
  وگرنه
    error ("conversion to non-scalar type requested");
  بازگشت error_mark_گره;
}

/* Create an expression whose value is that of EXPR, converted to type TYPE.
   The TREE_TYPE of the value is always TYPE.  This function implements all
   reasonable conversions; callers should filter out those that are not
   permitted by the language being compiled.  */

درخت
convert (درخت type, درخت عبارت)
{
  بازگشت c_convert (type, عبارت, نادرست);
}

/* Create an expression whose value is that of EXPR, converted to type TYPE, in
   a static initializer.  The TREE_TYPE of the value is always TYPE.  This
   function implements all reasonable conversions; callers should filter out
   those that are not permitted by the language being compiled.  */

درخت
convert_init (درخت type, درخت عبارت)
{
  بازگشت c_convert (type, عبارت, درست);
}
