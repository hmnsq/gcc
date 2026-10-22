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

#ಅನ್ತರ್ಭಾವ "config.h"
#ಅನ್ತರ್ಭಾವ "system.h"
#ಅನ್ತರ್ಭಾವ "coretypes.h"
#ಅನ್ತರ್ಭಾವ "target.h"
#ಅನ್ತರ್ಭಾವ "c-tree.h"
#ಅನ್ತರ್ಭಾವ "convert.h"
#ಅನ್ತರ್ಭಾವ "langhooks.h"
#ಅನ್ತರ್ಭಾವ "ubsan.h"
#ಅನ್ತರ್ಭಾವ "stringpool.h"
#ಅನ್ತರ್ಭಾವ "attribs.h"
#ಅನ್ತರ್ಭಾವ "asan.h"

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

ಸ್ಥಿರ ವೃಕ್ಷ
c_convert (ವೃಕ್ಷ type, ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ, ತಾರ್ಕಿಕ init_const)
{
  ವೃಕ್ಷ e = ಅಭಿವ್ಯಕ್ತಿ;
  ಗಣನಾ ವೃಕ್ಷ_code code = ವೃಕ್ಷ_CODE (type);
  ಧ್ರುವ ವರ್ಣ *invalid_conv_diag;
  ವೃಕ್ಷ ret;
  location_t loc = ಅಭಿವ್ಯಕ್ತಿ_LOCATION (ಅಭಿವ್ಯಕ್ತಿ);

  ಯದಿ (type == error_mark_ಗಂಟು
      || error_operand_p (ಅಭಿವ್ಯಕ್ತಿ))
    ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;

  ಯದಿ ((invalid_conv_diag
       = targetm.invalid_conversion (ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ), type)))
    {
      error (invalid_conv_diag);
      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
    }

  ಯದಿ (type == ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ))
    ಪ್ರತ್ಯಾಗಮ ಅಭಿವ್ಯಕ್ತಿ;
  ret = targetm.convert_to_type (type, ಅಭಿವ್ಯಕ್ತಿ);
  ಯದಿ (ret)
      ಪ್ರತ್ಯಾಗಮ ret;

  STRIP_TYPE_NOPS (e);

  ಯದಿ (TYPE_MAIN_VARIANT (type) == TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ))
      && (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ)) != COMPLEX_TYPE
	  || ವೃಕ್ಷ_CODE (e) == COMPLEX_ಅಭಿವ್ಯಕ್ತಿ))
    ಪ್ರತ್ಯಾಗಮ fold_convert_loc (loc, type, ಅಭಿವ್ಯಕ್ತಿ);
  ಯದಿ (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ)) == ERROR_MARK)
    ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
  ಯದಿ (VOID_TYPE_P (ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ)))
    {
      error ("void value not ignored as it ought to be");
      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
    }

  {
    ವೃಕ್ಷ false_ಮೌಲ್ಯ, true_ಮೌಲ್ಯ;
    ಯದಿ (c_hardbool_type_attr (type, &false_ಮೌಲ್ಯ, &true_ಮೌಲ್ಯ))
      {
	ತಾರ್ಕಿಕ save = in_late_ದ್ವಿಮಾನ_op;
	in_late_ದ್ವಿಮಾನ_op = ಸತ್ಯ;
	ಅಭಿವ್ಯಕ್ತಿ = c_objc_common_truthvalue_conversion (ಒಳಹರಿವು_location, ಅಭಿವ್ಯಕ್ತಿ);
	in_late_ದ್ವಿಮಾನ_op = save;

	ಪ್ರತ್ಯಾಗಮ fold_build3_loc (loc, COND_ಅಭಿವ್ಯಕ್ತಿ, type,
				ಅಭಿವ್ಯಕ್ತಿ, true_ಮೌಲ್ಯ, false_ಮೌಲ್ಯ);
      }
  }

  ವಿಕಲ್ಪ (code)
    {
    ಪಕ್ಷ VOID_TYPE:
      ಪ್ರತ್ಯಾಗಮ fold_convert_loc (loc, type, e);

    ಪಕ್ಷ ENUMERAL_TYPE:
      ಯದಿ (ENUM_UNDERLYING_TYPE (type) != NULL_ವೃಕ್ಷ
	  && ವೃಕ್ಷ_CODE (ENUM_UNDERLYING_TYPE (type)) == BOOLEAN_TYPE)
	ಗಚ್ಛ convert_to_boolean;
      gcc_fallthrough ();

    ಪಕ್ಷ INTEGER_TYPE:
    ಪಕ್ಷ BITINT_TYPE:
      ಯದಿ (sanitize_flags_p (SANITIZE_FLOAT_CAST)
	  && current_function_decl != NULL_ವೃಕ್ಷ
	  && SCALAR_FLOAT_TYPE_P (ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ))
	  && COMPLETE_TYPE_P (type))
	{
	  ಅಭಿವ್ಯಕ್ತಿ = save_ಅಭಿವ್ಯಕ್ತಿ (ಅಭಿವ್ಯಕ್ತಿ);
	  ಅಭಿವ್ಯಕ್ತಿ = c_fully_fold (ಅಭಿವ್ಯಕ್ತಿ, init_const, ರಿಕ್ತ);
	  ವೃಕ್ಷ check = ubsan_instrument_float_cast (loc, type, ಅಭಿವ್ಯಕ್ತಿ);
	  ಅಭಿವ್ಯಕ್ತಿ = fold_build1 (FIX_TRUNC_ಅಭಿವ್ಯಕ್ತಿ, type, ಅಭಿವ್ಯಕ್ತಿ);
	  ಯದಿ (check == NULL_ವೃಕ್ಷ)
	    ಪ್ರತ್ಯಾಗಮ ಅಭಿವ್ಯಕ್ತಿ;
	  ಪ್ರತ್ಯಾಗಮ fold_build2 (COMPOUND_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ), check, ಅಭಿವ್ಯಕ್ತಿ);
	}
      ret = convert_to_integer (type, e);
      ಗಚ್ಛ maybe_fold;

    ಪಕ್ಷ BOOLEAN_TYPE:
    convert_to_boolean:
      ಪ್ರತ್ಯಾಗಮ c_objc_common_truthvalue_conversion (ಒಳಹರಿವು_location, ಅಭಿವ್ಯಕ್ತಿ, type);

    ಪಕ್ಷ POINTER_TYPE:
      /* The type nullptr_t may be converted to a pointer type.  The result is
	 a null pointer value.  */
      ಯದಿ (NULLPTR_TYPE_P (ವೃಕ್ಷ_TYPE (e)))
	{
	  /* To make sure that (void *)nullptr is not a null pointer constant,
	     build_c_cast will create an additional NOP_EXPR around the result
	     of this conversion.  */
	  ಯದಿ (ವೃಕ್ಷ_SIDE_EFFECTS (e))
	    ret = build2 (COMPOUND_ಅಭಿವ್ಯಕ್ತಿ, type, e, build_int_cst (type, 0));
	  ಅನ್ಯಥಾ
	    ret = build_int_cst (type, 0);
	  ಗಚ್ಛ maybe_fold;
	}
      gcc_fallthrough ();
    ಪಕ್ಷ REFERENCE_TYPE:
      ret = convert_to_pointer (type, e);
      ಗಚ್ಛ maybe_fold;

    ಪಕ್ಷ NULLPTR_TYPE:
      /* A null pointer constant or value of type nullptr_t may be
	 converted to nullptr_t.  The latter case has already been
	 handled.  build_c_cast will create an additional NOP_EXPR to
	 ensure the result of the conversion is not itself a null
	 pointer constant.  */
      ಯದಿ (null_pointer_constant_p (ಅಭಿವ್ಯಕ್ತಿ))
	{
	  ret = build_int_cst (type, 0);
	  ಗಚ್ಛ maybe_fold;
	}
      ಭಙ್ಗ;

    ಪಕ್ಷ REAL_TYPE:
      ret = convert_to_real (type, e);
      ಗಚ್ಛ maybe_fold;

    ಪಕ್ಷ FIXED_POINT_TYPE:
      ret = convert_to_fixed (type, e);
      ಗಚ್ಛ maybe_fold;

    ಪಕ್ಷ COMPLEX_TYPE:
      ret = convert_to_complex (type, e);
      ಗಚ್ಛ maybe_fold;

    ಪಕ್ಷ VECTOR_TYPE:
      ಯದಿ (gnu_vector_type_p (type)
	  || gnu_vector_type_p (ವೃಕ್ಷ_TYPE (e))
	  /* Allow conversions between compatible non-GNU vector types
	     when -flax-vector-conversions is passed.  The whole purpose
	     of the option is to bend the normal type rules and accept
	     nonconforming code.  */
	  || (flag_lax_vector_conversions
	      && VECTOR_TYPE_P (ವೃಕ್ಷ_TYPE (e))
	      && vector_types_convertible_p (type, ವೃಕ್ಷ_TYPE (e), ಅಸತ್ಯ)))
	{
	  ret = convert_to_vector (type, e);
	  ಗಚ್ಛ maybe_fold;
	}
      ಭಙ್ಗ;

    ಪಕ್ಷ RECORD_TYPE:
    ಪಕ್ಷ UNION_TYPE:
      ಯದಿ (lang_hooks.types_compatible_p (type, ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ)))
	ಪ್ರತ್ಯಾಗಮ e;
      ಭಙ್ಗ;

    ಸ್ವಭಾವ:
      ಭಙ್ಗ;

    maybe_fold:
      ಯದಿ (ವೃಕ್ಷ_CODE (ret) != C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ)
	ret = init_const ? fold_init (ret) : fold (ret);
      ಪ್ರತ್ಯಾಗಮ ret;
    }

  /* If we are converting to nullptr_t, don't say "non-scalar type" because
     the nullptr_t type is a scalar type.  Only nullptr_t or a null pointer
     constant shall be converted to nullptr_t.  */
  ಯದಿ (code == NULLPTR_TYPE)
    {
      error ("conversion from %qT to %qT", ವೃಕ್ಷ_TYPE (e), type);
      inform (ಒಳಹರಿವು_location,
	      "only %qT or a null pointer constant can be converted to %qT",
	      type, type);
    }
  ಅನ್ಯಥಾ
    error ("conversion to non-scalar type requested");
  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
}

/* Create an expression whose value is that of EXPR, converted to type TYPE.
   The TREE_TYPE of the value is always TYPE.  This function implements all
   reasonable conversions; callers should filter out those that are not
   permitted by the language being compiled.  */

ವೃಕ್ಷ
convert (ವೃಕ್ಷ type, ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ)
{
  ಪ್ರತ್ಯಾಗಮ c_convert (type, ಅಭಿವ್ಯಕ್ತಿ, ಅಸತ್ಯ);
}

/* Create an expression whose value is that of EXPR, converted to type TYPE, in
   a static initializer.  The TREE_TYPE of the value is always TYPE.  This
   function implements all reasonable conversions; callers should filter out
   those that are not permitted by the language being compiled.  */

ವೃಕ್ಷ
convert_init (ವೃಕ್ಷ type, ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ)
{
  ಪ್ರತ್ಯಾಗಮ c_convert (type, ಅಭಿವ್ಯಕ್ತಿ, ಸತ್ಯ);
}
