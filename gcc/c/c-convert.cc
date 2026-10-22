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

ساکن درخت
c_convert (درخت type, درخت اظہاریہ, منطقی init_const)
{
  درخت e = اظہاریہ;
  شمار درخت_رمز_2 رمز = درخت_رمز (type);
  ثابت حرف *invalid_conv_diag;
  درخت ret;
  location_t loc = اظہاریہ_LOCATION (اظہاریہ);

  اگر (type == error_mark_گرہ
      || error_عملیہ_p (اظہاریہ))
    واپس error_mark_گرہ;

  اگر ((invalid_conv_diag
       = targetm.invalid_conversion (درخت_TYPE (اظہاریہ), type)))
    {
      error (invalid_conv_diag);
      واپس error_mark_گرہ;
    }

  اگر (type == درخت_TYPE (اظہاریہ))
    واپس اظہاریہ;
  ret = targetm.convert_مقصد_type (type, اظہاریہ);
  اگر (ret)
      واپس ret;

  STRIP_TYPE_NOPS (e);

  اگر (TYPE_MAIN_VARIANT (type) == TYPE_MAIN_VARIANT (درخت_TYPE (اظہاریہ))
      && (درخت_رمز (درخت_TYPE (اظہاریہ)) != COMPLEX_TYPE
	  || درخت_رمز (e) == COMPLEX_اظہاریہ))
    واپس fold_convert_loc (loc, type, اظہاریہ);
  اگر (درخت_رمز (درخت_TYPE (اظہاریہ)) == ERROR_MARK)
    واپس error_mark_گرہ;
  اگر (VOID_TYPE_P (درخت_TYPE (اظہاریہ)))
    {
      error ("void value not ignored as it ought to be");
      واپس error_mark_گرہ;
    }

  {
    درخت false_قدر, true_قدر;
    اگر (c_hardbool_type_attr (type, &false_قدر, &true_قدر))
      {
	منطقی save = اندر_late_ثنائی_op;
	اندر_late_ثنائی_op = سچ;
	اظہاریہ = c_objc_common_truthvalue_conversion (داخلہ_location, اظہاریہ);
	اندر_late_ثنائی_op = save;

	واپس fold_build3_loc (loc, COND_اظہاریہ, type,
				اظہاریہ, true_قدر, false_قدر);
      }
  }

  انتخاب (رمز)
    {
    حالت VOID_TYPE:
      واپس fold_convert_loc (loc, type, e);

    حالت ENUMERAL_TYPE:
      اگر (ENUM_UNDERLYING_TYPE (type) != NULL_درخت
	  && درخت_رمز (ENUM_UNDERLYING_TYPE (type)) == BOOLEAN_TYPE)
	جاؤ convert_مقصد_boolean;
      gcc_fallthrough ();

    حالت INTEGER_TYPE:
    حالت BITINT_TYPE:
      اگر (sanitize_flags_p (SANITIZE_FLOAT_CAST)
	  && current_function_decl != NULL_درخت
	  && SCALAR_FLOAT_TYPE_P (درخت_TYPE (اظہاریہ))
	  && COMPLETE_TYPE_P (type))
	{
	  اظہاریہ = save_اظہاریہ (اظہاریہ);
	  اظہاریہ = c_fully_fold (اظہاریہ, init_const, تہی);
	  درخت check = ubsan_instrument_float_cast (loc, type, اظہاریہ);
	  اظہاریہ = fold_build1 (FIX_TRUNC_اظہاریہ, type, اظہاریہ);
	  اگر (check == NULL_درخت)
	    واپس اظہاریہ;
	  واپس fold_build2 (COMPOUND_اظہاریہ, درخت_TYPE (اظہاریہ), check, اظہاریہ);
	}
      ret = convert_مقصد_integer (type, e);
      جاؤ maybe_fold;

    حالت BOOLEAN_TYPE:
    convert_مقصد_boolean:
      واپس c_objc_common_truthvalue_conversion (داخلہ_location, اظہاریہ, type);

    حالت اشارہ_گر_TYPE:
      /* The type nullptr_t may be converted to a pointer type.  The result is
	 a null pointer value.  */
      اگر (NULLPTR_TYPE_P (درخت_TYPE (e)))
	{
	  /* To make sure that (void *)nullptr is not a null pointer constant,
	     build_c_cast will create an additional NOP_EXPR around the result
	     of this conversion.  */
	  اگر (درخت_SIDE_EFFECTS (e))
	    ret = build2 (COMPOUND_اظہاریہ, type, e, build_int_cst (type, 0));
	  ورنہ
	    ret = build_int_cst (type, 0);
	  جاؤ maybe_fold;
	}
      gcc_fallthrough ();
    حالت REFERENCE_TYPE:
      ret = convert_مقصد_اشارہ_گر (type, e);
      جاؤ maybe_fold;

    حالت NULLPTR_TYPE:
      /* A null pointer constant or value of type nullptr_t may be
	 converted to nullptr_t.  The latter case has already been
	 handled.  build_c_cast will create an additional NOP_EXPR to
	 ensure the result of the conversion is not itself a null
	 pointer constant.  */
      اگر (null_اشارہ_گر_constant_p (اظہاریہ))
	{
	  ret = build_int_cst (type, 0);
	  جاؤ maybe_fold;
	}
      توڑو;

    حالت REAL_TYPE:
      ret = convert_مقصد_real (type, e);
      جاؤ maybe_fold;

    حالت FIXED_نقطہ_TYPE:
      ret = convert_مقصد_fixed (type, e);
      جاؤ maybe_fold;

    حالت COMPLEX_TYPE:
      ret = convert_مقصد_complex (type, e);
      جاؤ maybe_fold;

    حالت سمتیہ_TYPE:
      اگر (gnu_سمتیہ_type_p (type)
	  || gnu_سمتیہ_type_p (درخت_TYPE (e))
	  /* Allow conversions between compatible non-GNU vector types
	     when -flax-vector-conversions is passed.  The whole purpose
	     of the option is to bend the normal type rules and accept
	     nonconforming code.  */
	  || (flag_lax_سمتیہ_conversions
	      && سمتیہ_TYPE_P (درخت_TYPE (e))
	      && سمتیہ_types_convertible_p (type, درخت_TYPE (e), جھوٹ)))
	{
	  ret = convert_مقصد_سمتیہ (type, e);
	  جاؤ maybe_fold;
	}
      توڑو;

    حالت ریکارڈ_TYPE:
    حالت UNION_TYPE:
      اگر (lang_hooks.types_compatible_p (type, درخت_TYPE (اظہاریہ)))
	واپس e;
      توڑو;

    طےشدہ:
      توڑو;

    maybe_fold:
      اگر (درخت_رمز (ret) != C_MAYBE_CONST_اظہاریہ)
	ret = init_const ? fold_init (ret) : fold (ret);
      واپس ret;
    }

  /* If we are converting to nullptr_t, don't say "non-scalar type" because
     the nullptr_t type is a scalar type.  Only nullptr_t or a null pointer
     constant shall be converted to nullptr_t.  */
  اگر (رمز == NULLPTR_TYPE)
    {
      error ("conversion from %qT to %qT", درخت_TYPE (e), type);
      inform (داخلہ_location,
	      "only %qT or a null pointer constant can be converted to %qT",
	      type, type);
    }
  ورنہ
    error ("conversion to non-scalar type requested");
  واپس error_mark_گرہ;
}

/* Create an expression whose value is that of EXPR, converted to type TYPE.
   The TREE_TYPE of the value is always TYPE.  This function implements all
   reasonable conversions; callers should filter out those that are not
   permitted by the language being compiled.  */

درخت
convert (درخت type, درخت اظہاریہ)
{
  واپس c_convert (type, اظہاریہ, جھوٹ);
}

/* Create an expression whose value is that of EXPR, converted to type TYPE, in
   a static initializer.  The TREE_TYPE of the value is always TYPE.  This
   function implements all reasonable conversions; callers should filter out
   those that are not permitted by the language being compiled.  */

درخت
convert_init (درخت type, درخت اظہاریہ)
{
  واپس c_convert (type, اظہاریہ, سچ);
}
