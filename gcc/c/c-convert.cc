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

ساكن وڻ
c_convert (وڻ type, وڻ اظهار, منطقي init_const)
{
  وڻ e = اظهار;
  تعداد وڻ_ڪوڊ_2 ڪوڊ = وڻ_ڪوڊ (type);
  ثابت حرف *invalid_conv_diag;
  وڻ ret;
  location_t loc = اظهار_LOCATION (اظهار);

  إذا (type == error_mark_ڳنڍ
      || error_عمليو_p (اظهار))
    أرجع error_mark_ڳنڍ;

  إذا ((invalid_conv_diag
       = targetm.invalid_conversion (وڻ_TYPE (اظهار), type)))
    {
      error (invalid_conv_diag);
      أرجع error_mark_ڳنڍ;
    }

  إذا (type == وڻ_TYPE (اظهار))
    أرجع اظهار;
  ret = targetm.convert_منزل_type (type, اظهار);
  إذا (ret)
      أرجع ret;

  STRIP_TYPE_NOPS (e);

  إذا (TYPE_MAIN_VARIANT (type) == TYPE_MAIN_VARIANT (وڻ_TYPE (اظهار))
      && (وڻ_ڪوڊ (وڻ_TYPE (اظهار)) != COMPLEX_TYPE
	  || وڻ_ڪوڊ (e) == COMPLEX_اظهار))
    أرجع fold_convert_loc (loc, type, اظهار);
  إذا (وڻ_ڪوڊ (وڻ_TYPE (اظهار)) == ERROR_MARK)
    أرجع error_mark_ڳنڍ;
  إذا (VOID_TYPE_P (وڻ_TYPE (اظهار)))
    {
      error ("void value not ignored as it ought to be");
      أرجع error_mark_ڳنڍ;
    }

  {
    وڻ false_قدر, true_قدر;
    إذا (c_hardbool_type_attr (type, &false_قدر, &true_قدر))
      {
	منطقي save = اندريون_late_ٻٽو_op;
	اندريون_late_ٻٽو_op = سچ;
	اظهار = c_objc_common_truthvalue_conversion (داخلا_location, اظهار);
	اندريون_late_ٻٽو_op = save;

	أرجع fold_build3_loc (loc, COND_اظهار, type,
				اظهار, true_قدر, false_قدر);
      }
  }

  بدل (ڪوڊ)
    {
    حالة VOID_TYPE:
      أرجع fold_convert_loc (loc, type, e);

    حالة ENUMERAL_TYPE:
      إذا (ENUM_UNDERLYING_TYPE (type) != NULL_وڻ
	  && وڻ_ڪوڊ (ENUM_UNDERLYING_TYPE (type)) == BOOLEAN_TYPE)
	اذهب convert_منزل_boolean;
      gcc_fallthrough ();

    حالة INTEGER_TYPE:
    حالة BITINT_TYPE:
      إذا (sanitize_flags_p (SANITIZE_FLOAT_CAST)
	  && current_function_decl != NULL_وڻ
	  && SCALAR_FLOAT_TYPE_P (وڻ_TYPE (اظهار))
	  && COMPLETE_TYPE_P (type))
	{
	  اظهار = save_اظهار (اظهار);
	  اظهار = c_fully_fold (اظهار, init_const, عدم);
	  وڻ check = ubsan_instrument_float_cast (loc, type, اظهار);
	  اظهار = fold_build1 (FIX_TRUNC_اظهار, type, اظهار);
	  إذا (check == NULL_وڻ)
	    أرجع اظهار;
	  أرجع fold_build2 (COMPOUND_اظهار, وڻ_TYPE (اظهار), check, اظهار);
	}
      ret = convert_منزل_integer (type, e);
      اذهب maybe_fold;

    حالة BOOLEAN_TYPE:
    convert_منزل_boolean:
      أرجع c_objc_common_truthvalue_conversion (داخلا_location, اظهار, type);

    حالة اشارو_TYPE:
      /* The type nullptr_t may be converted to a pointer type.  The result is
	 a null pointer value.  */
      إذا (NULLPTR_TYPE_P (وڻ_TYPE (e)))
	{
	  /* To make sure that (void *)nullptr is not a null pointer constant,
	     build_c_cast will create an additional NOP_EXPR around the result
	     of this conversion.  */
	  إذا (وڻ_SIDE_EFFECTS (e))
	    ret = build2 (COMPOUND_اظهار, type, e, build_int_cst (type, 0));
	  وإلا
	    ret = build_int_cst (type, 0);
	  اذهب maybe_fold;
	}
      gcc_fallthrough ();
    حالة REFERENCE_TYPE:
      ret = convert_منزل_اشارو (type, e);
      اذهب maybe_fold;

    حالة NULLPTR_TYPE:
      /* A null pointer constant or value of type nullptr_t may be
	 converted to nullptr_t.  The latter case has already been
	 handled.  build_c_cast will create an additional NOP_EXPR to
	 ensure the result of the conversion is not itself a null
	 pointer constant.  */
      إذا (null_اشارو_constant_p (اظهار))
	{
	  ret = build_int_cst (type, 0);
	  اذهب maybe_fold;
	}
      اكسر;

    حالة REAL_TYPE:
      ret = convert_منزل_real (type, e);
      اذهب maybe_fold;

    حالة FIXED_نقطو_TYPE:
      ret = convert_منزل_fixed (type, e);
      اذهب maybe_fold;

    حالة COMPLEX_TYPE:
      ret = convert_منزل_complex (type, e);
      اذهب maybe_fold;

    حالة ويڪٽر_TYPE:
      إذا (gnu_ويڪٽر_type_p (type)
	  || gnu_ويڪٽر_type_p (وڻ_TYPE (e))
	  /* Allow conversions between compatible non-GNU vector types
	     when -flax-vector-conversions is passed.  The whole purpose
	     of the option is to bend the normal type rules and accept
	     nonconforming code.  */
	  || (flag_lax_ويڪٽر_conversions
	      && ويڪٽر_TYPE_P (وڻ_TYPE (e))
	      && ويڪٽر_types_convertible_p (type, وڻ_TYPE (e), خطأ)))
	{
	  ret = convert_منزل_ويڪٽر (type, e);
	  اذهب maybe_fold;
	}
      اكسر;

    حالة رڪارڊ_TYPE:
    حالة UNION_TYPE:
      إذا (lang_hooks.types_compatible_p (type, وڻ_TYPE (اظهار)))
	أرجع e;
      اكسر;

    افتراضي:
      اكسر;

    maybe_fold:
      إذا (وڻ_ڪوڊ (ret) != C_MAYBE_CONST_اظهار)
	ret = init_const ? fold_init (ret) : fold (ret);
      أرجع ret;
    }

  /* If we are converting to nullptr_t, don't say "non-scalar type" because
     the nullptr_t type is a scalar type.  Only nullptr_t or a null pointer
     constant shall be converted to nullptr_t.  */
  إذا (ڪوڊ == NULLPTR_TYPE)
    {
      error ("conversion from %qT to %qT", وڻ_TYPE (e), type);
      inform (داخلا_location,
	      "only %qT or a null pointer constant can be converted to %qT",
	      type, type);
    }
  وإلا
    error ("conversion to non-scalar type requested");
  أرجع error_mark_ڳنڍ;
}

/* Create an expression whose value is that of EXPR, converted to type TYPE.
   The TREE_TYPE of the value is always TYPE.  This function implements all
   reasonable conversions; callers should filter out those that are not
   permitted by the language being compiled.  */

وڻ
convert (وڻ type, وڻ اظهار)
{
  أرجع c_convert (type, اظهار, خطأ);
}

/* Create an expression whose value is that of EXPR, converted to type TYPE, in
   a static initializer.  The TREE_TYPE of the value is always TYPE.  This
   function implements all reasonable conversions; callers should filter out
   those that are not permitted by the language being compiled.  */

وڻ
convert_init (وڻ type, وڻ اظهار)
{
  أرجع c_convert (type, اظهار, سچ);
}
