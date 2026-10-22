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

#অন্তর্ভাৱ "config.h"
#অন্তর্ভাৱ "system.h"
#অন্তর্ভাৱ "coretypes.h"
#অন্তর্ভাৱ "target.h"
#অন্তর্ভাৱ "c-tree.h"
#অন্তর্ভাৱ "convert.h"
#অন্তর্ভাৱ "langhooks.h"
#অন্তর্ভাৱ "ubsan.h"
#অন্তর্ভাৱ "stringpool.h"
#অন্তর্ভাৱ "attribs.h"
#অন্তর্ভাৱ "asan.h"

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

স্থির বৃক্ষ
c_convert (বৃক্ষ type, বৃক্ষ ৰাশিমালা, তার্কিক init_const)
{
  বৃক্ষ e = ৰাশিমালা;
  গণনা বৃক্ষ_code code = বৃক্ষ_CODE (type);
  ধ্রুৱ ৱর্ণ *invalid_conv_diag;
  বৃক্ষ ret;
  location_t loc = ৰাশিমালা_LOCATION (ৰাশিমালা);

  যদি (type == error_mark_গ্ৰন্থি
      || error_operand_p (ৰাশিমালা))
    ঘূৰাই error_mark_গ্ৰন্থি;

  যদি ((invalid_conv_diag
       = targetm.invalid_conversion (বৃক্ষ_TYPE (ৰাশিমালা), type)))
    {
      error (invalid_conv_diag);
      ঘূৰাই error_mark_গ্ৰন্থি;
    }

  যদি (type == বৃক্ষ_TYPE (ৰাশিমালা))
    ঘূৰাই ৰাশিমালা;
  ret = targetm.convert_to_type (type, ৰাশিমালা);
  যদি (ret)
      ঘূৰাই ret;

  STRIP_TYPE_NOPS (e);

  যদি (TYPE_MAIN_VARIANT (type) == TYPE_MAIN_VARIANT (বৃক্ষ_TYPE (ৰাশিমালা))
      && (বৃক্ষ_CODE (বৃক্ষ_TYPE (ৰাশিমালা)) != COMPLEX_TYPE
	  || বৃক্ষ_CODE (e) == COMPLEX_ৰাশিমালা))
    ঘূৰাই fold_convert_loc (loc, type, ৰাশিমালা);
  যদি (বৃক্ষ_CODE (বৃক্ষ_TYPE (ৰাশিমালা)) == ERROR_MARK)
    ঘূৰাই error_mark_গ্ৰন্থি;
  যদি (VOID_TYPE_P (বৃক্ষ_TYPE (ৰাশিমালা)))
    {
      error ("void value not ignored as it ought to be");
      ঘূৰাই error_mark_গ্ৰন্থি;
    }

  {
    বৃক্ষ false_মান, true_মান;
    যদি (c_hardbool_type_attr (type, &false_মান, &true_মান))
      {
	তার্কিক save = in_late_দ্বিমিক_op;
	in_late_দ্বিমিক_op = সঁচা;
	ৰাশিমালা = c_objc_common_truthvalue_conversion (প্ৰবেশ_location, ৰাশিমালা);
	in_late_দ্বিমিক_op = save;

	ঘূৰাই fold_build3_loc (loc, COND_ৰাশিমালা, type,
				ৰাশিমালা, true_মান, false_মান);
      }
  }

  ৱিকল্প (code)
    {
    পক্ষ VOID_TYPE:
      ঘূৰাই fold_convert_loc (loc, type, e);

    পক্ষ ENUMERAL_TYPE:
      যদি (ENUM_UNDERLYING_TYPE (type) != NULL_বৃক্ষ
	  && বৃক্ষ_CODE (ENUM_UNDERLYING_TYPE (type)) == BOOLEAN_TYPE)
	গচ্ছ convert_to_boolean;
      gcc_fallthrough ();

    পক্ষ INTEGER_TYPE:
    পক্ষ BITINT_TYPE:
      যদি (sanitize_flags_p (SANITIZE_FLOAT_CAST)
	  && current_function_decl != NULL_বৃক্ষ
	  && SCALAR_FLOAT_TYPE_P (বৃক্ষ_TYPE (ৰাশিমালা))
	  && COMPLETE_TYPE_P (type))
	{
	  ৰাশিমালা = save_ৰাশিমালা (ৰাশিমালা);
	  ৰাশিমালা = c_fully_fold (ৰাশিমালা, init_const, রিক্ত);
	  বৃক্ষ check = ubsan_instrument_float_cast (loc, type, ৰাশিমালা);
	  ৰাশিমালা = fold_build1 (FIX_TRUNC_ৰাশিমালা, type, ৰাশিমালা);
	  যদি (check == NULL_বৃক্ষ)
	    ঘূৰাই ৰাশিমালা;
	  ঘূৰাই fold_build2 (COMPOUND_ৰাশিমালা, বৃক্ষ_TYPE (ৰাশিমালা), check, ৰাশিমালা);
	}
      ret = convert_to_integer (type, e);
      গচ্ছ maybe_fold;

    পক্ষ BOOLEAN_TYPE:
    convert_to_boolean:
      ঘূৰাই c_objc_common_truthvalue_conversion (প্ৰবেশ_location, ৰাশিমালা, type);

    পক্ষ POINTER_TYPE:
      /* The type nullptr_t may be converted to a pointer type.  The result is
	 a null pointer value.  */
      যদি (NULLPTR_TYPE_P (বৃক্ষ_TYPE (e)))
	{
	  /* To make sure that (void *)nullptr is not a null pointer constant,
	     build_c_cast will create an additional NOP_EXPR around the result
	     of this conversion.  */
	  যদি (বৃক্ষ_SIDE_EFFECTS (e))
	    ret = build2 (COMPOUND_ৰাশিমালা, type, e, build_int_cst (type, 0));
	  অন্যথা
	    ret = build_int_cst (type, 0);
	  গচ্ছ maybe_fold;
	}
      gcc_fallthrough ();
    পক্ষ REFERENCE_TYPE:
      ret = convert_to_pointer (type, e);
      গচ্ছ maybe_fold;

    পক্ষ NULLPTR_TYPE:
      /* A null pointer constant or value of type nullptr_t may be
	 converted to nullptr_t.  The latter case has already been
	 handled.  build_c_cast will create an additional NOP_EXPR to
	 ensure the result of the conversion is not itself a null
	 pointer constant.  */
      যদি (null_pointer_constant_p (ৰাশিমালা))
	{
	  ret = build_int_cst (type, 0);
	  গচ্ছ maybe_fold;
	}
      ভঙ্গ;

    পক্ষ REAL_TYPE:
      ret = convert_to_real (type, e);
      গচ্ছ maybe_fold;

    পক্ষ FIXED_POINT_TYPE:
      ret = convert_to_fixed (type, e);
      গচ্ছ maybe_fold;

    পক্ষ COMPLEX_TYPE:
      ret = convert_to_complex (type, e);
      গচ্ছ maybe_fold;

    পক্ষ VECTOR_TYPE:
      যদি (gnu_vector_type_p (type)
	  || gnu_vector_type_p (বৃক্ষ_TYPE (e))
	  /* Allow conversions between compatible non-GNU vector types
	     when -flax-vector-conversions is passed.  The whole purpose
	     of the option is to bend the normal type rules and accept
	     nonconforming code.  */
	  || (flag_lax_vector_conversions
	      && VECTOR_TYPE_P (বৃক্ষ_TYPE (e))
	      && vector_types_convertible_p (type, বৃক্ষ_TYPE (e), মিছা)))
	{
	  ret = convert_to_vector (type, e);
	  গচ্ছ maybe_fold;
	}
      ভঙ্গ;

    পক্ষ RECORD_TYPE:
    পক্ষ UNION_TYPE:
      যদি (lang_hooks.types_compatible_p (type, বৃক্ষ_TYPE (ৰাশিমালা)))
	ঘূৰাই e;
      ভঙ্গ;

    স্ৱভাৱ:
      ভঙ্গ;

    maybe_fold:
      যদি (বৃক্ষ_CODE (ret) != C_MAYBE_CONST_ৰাশিমালা)
	ret = init_const ? fold_init (ret) : fold (ret);
      ঘূৰাই ret;
    }

  /* If we are converting to nullptr_t, don't say "non-scalar type" because
     the nullptr_t type is a scalar type.  Only nullptr_t or a null pointer
     constant shall be converted to nullptr_t.  */
  যদি (code == NULLPTR_TYPE)
    {
      error ("conversion from %qT to %qT", বৃক্ষ_TYPE (e), type);
      inform (প্ৰবেশ_location,
	      "only %qT or a null pointer constant can be converted to %qT",
	      type, type);
    }
  অন্যথা
    error ("conversion to non-scalar type requested");
  ঘূৰাই error_mark_গ্ৰন্থি;
}

/* Create an expression whose value is that of EXPR, converted to type TYPE.
   The TREE_TYPE of the value is always TYPE.  This function implements all
   reasonable conversions; callers should filter out those that are not
   permitted by the language being compiled.  */

বৃক্ষ
convert (বৃক্ষ type, বৃক্ষ ৰাশিমালা)
{
  ঘূৰাই c_convert (type, ৰাশিমালা, মিছা);
}

/* Create an expression whose value is that of EXPR, converted to type TYPE, in
   a static initializer.  The TREE_TYPE of the value is always TYPE.  This
   function implements all reasonable conversions; callers should filter out
   those that are not permitted by the language being compiled.  */

বৃক্ষ
convert_init (বৃক্ষ type, বৃক্ষ ৰাশিমালা)
{
  ঘূৰাই c_convert (type, ৰাশিমালা, সঁচা);
}
