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

#ਅਨ੍ਤਰ੍ਭਾਵ "config.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "system.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "coretypes.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "target.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "c-tree.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "convert.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "langhooks.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "ubsan.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "stringpool.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "attribs.h"
#ਅਨ੍ਤਰ੍ਭਾਵ "asan.h"

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

ਸਥਿਰ ਰੁੱਖ
c_convert (ਰੁੱਖ type, ਰੁੱਖ ਵਿਅੰਜਕ, ਤਾਰਕਿਕ init_const)
{
  ਰੁੱਖ e = ਵਿਅੰਜਕ;
  ਗਿਣਤੀ ਰੁੱਖ_ਕੋਡ_2 ਕੋਡ = ਰੁੱਖ_ਕੋਡ (type);
  ਅਚਲ ਅੱਖਰ *invalid_conv_diag;
  ਰੁੱਖ ret;
  location_t loc = ਵਿਅੰਜਕ_LOCATION (ਵਿਅੰਜਕ);

  ਜੇ (type == error_mark_ਗੰਢ
      || error_ਸੰਕਾਰਜ_p (ਵਿਅੰਜਕ))
    ਵਾਪਸ error_mark_ਗੰਢ;

  ਜੇ ((invalid_conv_diag
       = targetm.invalid_conversion (ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ), type)))
    {
      error (invalid_conv_diag);
      ਵਾਪਸ error_mark_ਗੰਢ;
    }

  ਜੇ (type == ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ))
    ਵਾਪਸ ਵਿਅੰਜਕ;
  ret = targetm.convert_ਮੰਜ਼ਿਲ_type (type, ਵਿਅੰਜਕ);
  ਜੇ (ret)
      ਵਾਪਸ ret;

  STRIP_TYPE_NOPS (e);

  ਜੇ (TYPE_MAIN_VARIANT (type) == TYPE_MAIN_VARIANT (ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ))
      && (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ)) != COMPLEX_TYPE
	  || ਰੁੱਖ_ਕੋਡ (e) == COMPLEX_ਵਿਅੰਜਕ))
    ਵਾਪਸ fold_convert_loc (loc, type, ਵਿਅੰਜਕ);
  ਜੇ (ਰੁੱਖ_ਕੋਡ (ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ)) == ERROR_MARK)
    ਵਾਪਸ error_mark_ਗੰਢ;
  ਜੇ (VOID_TYPE_P (ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ)))
    {
      error ("void value not ignored as it ought to be");
      ਵਾਪਸ error_mark_ਗੰਢ;
    }

  {
    ਰੁੱਖ false_ਮੁੱਲ, true_ਮੁੱਲ;
    ਜੇ (c_hardbool_type_attr (type, &false_ਮੁੱਲ, &true_ਮੁੱਲ))
      {
	ਤਾਰਕਿਕ save = ਵਿੱਚ_late_ਦੁਆਧਾਰੀ_op;
	ਵਿੱਚ_late_ਦੁਆਧਾਰੀ_op = ਸੱਚ;
	ਵਿਅੰਜਕ = c_objc_common_truthvalue_conversion (ਨਿਵੇਸ਼_location, ਵਿਅੰਜਕ);
	ਵਿੱਚ_late_ਦੁਆਧਾਰੀ_op = save;

	ਵਾਪਸ fold_build3_loc (loc, COND_ਵਿਅੰਜਕ, type,
				ਵਿਅੰਜਕ, true_ਮੁੱਲ, false_ਮੁੱਲ);
      }
  }

  ਚੋਣ (ਕੋਡ)
    {
    ਹਾਲਤ VOID_TYPE:
      ਵਾਪਸ fold_convert_loc (loc, type, e);

    ਹਾਲਤ ENUMERAL_TYPE:
      ਜੇ (ENUM_UNDERLYING_TYPE (type) != NULL_ਰੁੱਖ
	  && ਰੁੱਖ_ਕੋਡ (ENUM_UNDERLYING_TYPE (type)) == BOOLEAN_TYPE)
	ਜਾਓ convert_ਮੰਜ਼ਿਲ_boolean;
      gcc_fallthrough ();

    ਹਾਲਤ INTEGER_TYPE:
    ਹਾਲਤ BITINT_TYPE:
      ਜੇ (sanitize_flags_p (SANITIZE_FLOAT_CAST)
	  && current_function_decl != NULL_ਰੁੱਖ
	  && SCALAR_FLOAT_TYPE_P (ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ))
	  && COMPLETE_TYPE_P (type))
	{
	  ਵਿਅੰਜਕ = save_ਵਿਅੰਜਕ (ਵਿਅੰਜਕ);
	  ਵਿਅੰਜਕ = c_fully_fold (ਵਿਅੰਜਕ, init_const, ਨਿਰਾ);
	  ਰੁੱਖ check = ubsan_instrument_float_cast (loc, type, ਵਿਅੰਜਕ);
	  ਵਿਅੰਜਕ = fold_build1 (FIX_TRUNC_ਵਿਅੰਜਕ, type, ਵਿਅੰਜਕ);
	  ਜੇ (check == NULL_ਰੁੱਖ)
	    ਵਾਪਸ ਵਿਅੰਜਕ;
	  ਵਾਪਸ fold_build2 (COMPOUND_ਵਿਅੰਜਕ, ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ), check, ਵਿਅੰਜਕ);
	}
      ret = convert_ਮੰਜ਼ਿਲ_integer (type, e);
      ਜਾਓ maybe_fold;

    ਹਾਲਤ BOOLEAN_TYPE:
    convert_ਮੰਜ਼ਿਲ_boolean:
      ਵਾਪਸ c_objc_common_truthvalue_conversion (ਨਿਵੇਸ਼_location, ਵਿਅੰਜਕ, type);

    ਹਾਲਤ ਸੂਚਕ_TYPE:
      /* The type nullptr_t may be converted to a pointer type.  The result is
	 a null pointer value.  */
      ਜੇ (NULLPTR_TYPE_P (ਰੁੱਖ_TYPE (e)))
	{
	  /* To make sure that (void *)nullptr is not a null pointer constant,
	     build_c_cast will create an additional NOP_EXPR around the result
	     of this conversion.  */
	  ਜੇ (ਰੁੱਖ_SIDE_EFFECTS (e))
	    ret = build2 (COMPOUND_ਵਿਅੰਜਕ, type, e, build_int_cst (type, 0));
	  ਨਹੀਂਤਾਂ
	    ret = build_int_cst (type, 0);
	  ਜਾਓ maybe_fold;
	}
      gcc_fallthrough ();
    ਹਾਲਤ REFERENCE_TYPE:
      ret = convert_ਮੰਜ਼ਿਲ_ਸੂਚਕ (type, e);
      ਜਾਓ maybe_fold;

    ਹਾਲਤ NULLPTR_TYPE:
      /* A null pointer constant or value of type nullptr_t may be
	 converted to nullptr_t.  The latter case has already been
	 handled.  build_c_cast will create an additional NOP_EXPR to
	 ensure the result of the conversion is not itself a null
	 pointer constant.  */
      ਜੇ (null_ਸੂਚਕ_constant_p (ਵਿਅੰਜਕ))
	{
	  ret = build_int_cst (type, 0);
	  ਜਾਓ maybe_fold;
	}
      ਰੋਕੋ;

    ਹਾਲਤ REAL_TYPE:
      ret = convert_ਮੰਜ਼ਿਲ_real (type, e);
      ਜਾਓ maybe_fold;

    ਹਾਲਤ FIXED_ਬਿੰਦੂ_TYPE:
      ret = convert_ਮੰਜ਼ਿਲ_fixed (type, e);
      ਜਾਓ maybe_fold;

    ਹਾਲਤ COMPLEX_TYPE:
      ret = convert_ਮੰਜ਼ਿਲ_complex (type, e);
      ਜਾਓ maybe_fold;

    ਹਾਲਤ ਸਦਿਸ਼_TYPE:
      ਜੇ (gnu_ਸਦਿਸ਼_type_p (type)
	  || gnu_ਸਦਿਸ਼_type_p (ਰੁੱਖ_TYPE (e))
	  /* Allow conversions between compatible non-GNU vector types
	     when -flax-vector-conversions is passed.  The whole purpose
	     of the option is to bend the normal type rules and accept
	     nonconforming code.  */
	  || (flag_lax_ਸਦਿਸ਼_conversions
	      && ਸਦਿਸ਼_TYPE_P (ਰੁੱਖ_TYPE (e))
	      && ਸਦਿਸ਼_types_convertible_p (type, ਰੁੱਖ_TYPE (e), ਝੂਠ)))
	{
	  ret = convert_ਮੰਜ਼ਿਲ_ਸਦਿਸ਼ (type, e);
	  ਜਾਓ maybe_fold;
	}
      ਰੋਕੋ;

    ਹਾਲਤ ਰਿਕਾਰਡ_TYPE:
    ਹਾਲਤ UNION_TYPE:
      ਜੇ (lang_hooks.types_compatible_p (type, ਰੁੱਖ_TYPE (ਵਿਅੰਜਕ)))
	ਵਾਪਸ e;
      ਰੋਕੋ;

    ਮੂਲ:
      ਰੋਕੋ;

    maybe_fold:
      ਜੇ (ਰੁੱਖ_ਕੋਡ (ret) != C_MAYBE_CONST_ਵਿਅੰਜਕ)
	ret = init_const ? fold_init (ret) : fold (ret);
      ਵਾਪਸ ret;
    }

  /* If we are converting to nullptr_t, don't say "non-scalar type" because
     the nullptr_t type is a scalar type.  Only nullptr_t or a null pointer
     constant shall be converted to nullptr_t.  */
  ਜੇ (ਕੋਡ == NULLPTR_TYPE)
    {
      error ("conversion from %qT to %qT", ਰੁੱਖ_TYPE (e), type);
      inform (ਨਿਵੇਸ਼_location,
	      "only %qT or a null pointer constant can be converted to %qT",
	      type, type);
    }
  ਨਹੀਂਤਾਂ
    error ("conversion to non-scalar type requested");
  ਵਾਪਸ error_mark_ਗੰਢ;
}

/* Create an expression whose value is that of EXPR, converted to type TYPE.
   The TREE_TYPE of the value is always TYPE.  This function implements all
   reasonable conversions; callers should filter out those that are not
   permitted by the language being compiled.  */

ਰੁੱਖ
convert (ਰੁੱਖ type, ਰੁੱਖ ਵਿਅੰਜਕ)
{
  ਵਾਪਸ c_convert (type, ਵਿਅੰਜਕ, ਝੂਠ);
}

/* Create an expression whose value is that of EXPR, converted to type TYPE, in
   a static initializer.  The TREE_TYPE of the value is always TYPE.  This
   function implements all reasonable conversions; callers should filter out
   those that are not permitted by the language being compiled.  */

ਰੁੱਖ
convert_init (ਰੁੱਖ type, ਰੁੱਖ ਵਿਅੰਜਕ)
{
  ਵਾਪਸ c_convert (type, ਵਿਅੰਜਕ, ਸੱਚ);
}
