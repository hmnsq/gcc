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

#অন্তর্ভাব "config.h"
#অন্তর্ভাব "system.h"
#অন্তর্ভাব "coretypes.h"
#অন্তর্ভাব "target.h"
#অন্তর্ভাব "c-tree.h"
#অন্তর্ভাব "convert.h"
#অন্তর্ভাব "langhooks.h"
#অন্তর্ভাব "ubsan.h"
#অন্তর্ভাব "stringpool.h"
#অন্তর্ভাব "attribs.h"
#অন্তর্ভাব "asan.h"

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
c_convert (বৃক্ষ type, বৃক্ষ রাশিমালা, যৌক্তিক init_const)
{
  বৃক্ষ e = রাশিমালা;
  গণনা বৃক্ষ_code code = বৃক্ষ_CODE (type);
  ধ্রুবক অক্ষর *invalid_conv_diag;
  বৃক্ষ ret;
  location_t loc = রাশিমালা_LOCATION (রাশিমালা);

  যদি (type == error_mark_গ্রন্থি
      || error_operand_p (রাশিমালা))
    ফেরত error_mark_গ্রন্থি;

  যদি ((invalid_conv_diag
       = targetm.invalid_conversion (বৃক্ষ_TYPE (রাশিমালা), type)))
    {
      error (invalid_conv_diag);
      ফেরত error_mark_গ্রন্থি;
    }

  যদি (type == বৃক্ষ_TYPE (রাশিমালা))
    ফেরত রাশিমালা;
  ret = targetm.convert_to_type (type, রাশিমালা);
  যদি (ret)
      ফেরত ret;

  STRIP_TYPE_NOPS (e);

  যদি (TYPE_MAIN_VARIANT (type) == TYPE_MAIN_VARIANT (বৃক্ষ_TYPE (রাশিমালা))
      && (বৃক্ষ_CODE (বৃক্ষ_TYPE (রাশিমালা)) != COMPLEX_TYPE
	  || বৃক্ষ_CODE (e) == COMPLEX_রাশিমালা))
    ফেরত fold_convert_loc (loc, type, রাশিমালা);
  যদি (বৃক্ষ_CODE (বৃক্ষ_TYPE (রাশিমালা)) == ERROR_MARK)
    ফেরত error_mark_গ্রন্থি;
  যদি (VOID_TYPE_P (বৃক্ষ_TYPE (রাশিমালা)))
    {
      error ("void value not ignored as it ought to be");
      ফেরত error_mark_গ্রন্থি;
    }

  {
    বৃক্ষ false_মান, true_মান;
    যদি (c_hardbool_type_attr (type, &false_মান, &true_মান))
      {
	যৌক্তিক save = in_late_দ্বিমিক_op;
	in_late_দ্বিমিক_op = সত্য;
	রাশিমালা = c_objc_common_truthvalue_conversion (প্রবেশ_location, রাশিমালা);
	in_late_দ্বিমিক_op = save;

	ফেরত fold_build3_loc (loc, COND_রাশিমালা, type,
				রাশিমালা, true_মান, false_মান);
      }
  }

  নির্বাচন (code)
    {
    ক্ষেত্র VOID_TYPE:
      ফেরত fold_convert_loc (loc, type, e);

    ক্ষেত্র ENUMERAL_TYPE:
      যদি (ENUM_UNDERLYING_TYPE (type) != NULL_বৃক্ষ
	  && বৃক্ষ_CODE (ENUM_UNDERLYING_TYPE (type)) == BOOLEAN_TYPE)
	যাও convert_to_boolean;
      gcc_fallthrough ();

    ক্ষেত্র INTEGER_TYPE:
    ক্ষেত্র BITINT_TYPE:
      যদি (sanitize_flags_p (SANITIZE_FLOAT_CAST)
	  && current_function_decl != NULL_বৃক্ষ
	  && SCALAR_FLOAT_TYPE_P (বৃক্ষ_TYPE (রাশিমালা))
	  && COMPLETE_TYPE_P (type))
	{
	  রাশিমালা = save_রাশিমালা (রাশিমালা);
	  রাশিমালা = c_fully_fold (রাশিমালা, init_const, ফাঁকা);
	  বৃক্ষ check = ubsan_instrument_float_cast (loc, type, রাশিমালা);
	  রাশিমালা = fold_build1 (FIX_TRUNC_রাশিমালা, type, রাশিমালা);
	  যদি (check == NULL_বৃক্ষ)
	    ফেরত রাশিমালা;
	  ফেরত fold_build2 (COMPOUND_রাশিমালা, বৃক্ষ_TYPE (রাশিমালা), check, রাশিমালা);
	}
      ret = convert_to_integer (type, e);
      যাও maybe_fold;

    ক্ষেত্র BOOLEAN_TYPE:
    convert_to_boolean:
      ফেরত c_objc_common_truthvalue_conversion (প্রবেশ_location, রাশিমালা, type);

    ক্ষেত্র POINTER_TYPE:
      /* The type nullptr_t may be converted to a pointer type.  The result is
	 a null pointer value.  */
      যদি (NULLPTR_TYPE_P (বৃক্ষ_TYPE (e)))
	{
	  /* To make sure that (void *)nullptr is not a null pointer constant,
	     build_c_cast will create an additional NOP_EXPR around the result
	     of this conversion.  */
	  যদি (বৃক্ষ_SIDE_EFFECTS (e))
	    ret = build2 (COMPOUND_রাশিমালা, type, e, build_int_cst (type, 0));
	  অন্যথা
	    ret = build_int_cst (type, 0);
	  যাও maybe_fold;
	}
      gcc_fallthrough ();
    ক্ষেত্র REFERENCE_TYPE:
      ret = convert_to_pointer (type, e);
      যাও maybe_fold;

    ক্ষেত্র NULLPTR_TYPE:
      /* A null pointer constant or value of type nullptr_t may be
	 converted to nullptr_t.  The latter case has already been
	 handled.  build_c_cast will create an additional NOP_EXPR to
	 ensure the result of the conversion is not itself a null
	 pointer constant.  */
      যদি (null_pointer_constant_p (রাশিমালা))
	{
	  ret = build_int_cst (type, 0);
	  যাও maybe_fold;
	}
      বিরতি;

    ক্ষেত্র REAL_TYPE:
      ret = convert_to_real (type, e);
      যাও maybe_fold;

    ক্ষেত্র FIXED_POINT_TYPE:
      ret = convert_to_fixed (type, e);
      যাও maybe_fold;

    ক্ষেত্র COMPLEX_TYPE:
      ret = convert_to_complex (type, e);
      যাও maybe_fold;

    ক্ষেত্র VECTOR_TYPE:
      যদি (gnu_vector_type_p (type)
	  || gnu_vector_type_p (বৃক্ষ_TYPE (e))
	  /* Allow conversions between compatible non-GNU vector types
	     when -flax-vector-conversions is passed.  The whole purpose
	     of the option is to bend the normal type rules and accept
	     nonconforming code.  */
	  || (flag_lax_vector_conversions
	      && VECTOR_TYPE_P (বৃক্ষ_TYPE (e))
	      && vector_types_convertible_p (type, বৃক্ষ_TYPE (e), মিথ্যা)))
	{
	  ret = convert_to_vector (type, e);
	  যাও maybe_fold;
	}
      বিরতি;

    ক্ষেত্র RECORD_TYPE:
    ক্ষেত্র UNION_TYPE:
      যদি (lang_hooks.types_compatible_p (type, বৃক্ষ_TYPE (রাশিমালা)))
	ফেরত e;
      বিরতি;

    পূর্বনির্ধারিত:
      বিরতি;

    maybe_fold:
      যদি (বৃক্ষ_CODE (ret) != C_MAYBE_CONST_রাশিমালা)
	ret = init_const ? fold_init (ret) : fold (ret);
      ফেরত ret;
    }

  /* If we are converting to nullptr_t, don't say "non-scalar type" because
     the nullptr_t type is a scalar type.  Only nullptr_t or a null pointer
     constant shall be converted to nullptr_t.  */
  যদি (code == NULLPTR_TYPE)
    {
      error ("conversion from %qT to %qT", বৃক্ষ_TYPE (e), type);
      inform (প্রবেশ_location,
	      "only %qT or a null pointer constant can be converted to %qT",
	      type, type);
    }
  অন্যথা
    error ("conversion to non-scalar type requested");
  ফেরত error_mark_গ্রন্থি;
}

/* Create an expression whose value is that of EXPR, converted to type TYPE.
   The TREE_TYPE of the value is always TYPE.  This function implements all
   reasonable conversions; callers should filter out those that are not
   permitted by the language being compiled.  */

বৃক্ষ
convert (বৃক্ষ type, বৃক্ষ রাশিমালা)
{
  ফেরত c_convert (type, রাশিমালা, মিথ্যা);
}

/* Create an expression whose value is that of EXPR, converted to type TYPE, in
   a static initializer.  The TREE_TYPE of the value is always TYPE.  This
   function implements all reasonable conversions; callers should filter out
   those that are not permitted by the language being compiled.  */

বৃক্ষ
convert_init (বৃক্ষ type, বৃক্ষ রাশিমালা)
{
  ফেরত c_convert (type, রাশিমালা, সত্য);
}
