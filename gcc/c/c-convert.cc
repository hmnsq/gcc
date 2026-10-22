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

#ଅନ୍ତର୍ଭାଵ "config.h"
#ଅନ୍ତର୍ଭାଵ "system.h"
#ଅନ୍ତର୍ଭାଵ "coretypes.h"
#ଅନ୍ତର୍ଭାଵ "target.h"
#ଅନ୍ତର୍ଭାଵ "c-tree.h"
#ଅନ୍ତର୍ଭାଵ "convert.h"
#ଅନ୍ତର୍ଭାଵ "langhooks.h"
#ଅନ୍ତର୍ଭାଵ "ubsan.h"
#ଅନ୍ତର୍ଭାଵ "stringpool.h"
#ଅନ୍ତର୍ଭାଵ "attribs.h"
#ଅନ୍ତର୍ଭାଵ "asan.h"

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

ସ୍ଥିର ବୃକ୍ଷ
c_convert (ବୃକ୍ଷ type, ବୃକ୍ଷ ପଦସମଷ୍ଟି, ତାର୍କିକ init_const)
{
  ବୃକ୍ଷ e = ପଦସମଷ୍ଟି;
  ଗଣନା ବୃକ୍ଷ_code code = ବୃକ୍ଷ_CODE (type);
  ଅଚଳ ଅକ୍ଷର *invalid_conv_diag;
  ବୃକ୍ଷ ret;
  location_t loc = ପଦସମଷ୍ଟି_LOCATION (ପଦସମଷ୍ଟି);

  ଯଦି (type == error_mark_ଗଣ୍ଠି
      || error_operand_p (ପଦସମଷ୍ଟି))
    ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;

  ଯଦି ((invalid_conv_diag
       = targetm.invalid_conversion (ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି), type)))
    {
      error (invalid_conv_diag);
      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
    }

  ଯଦି (type == ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି))
    ଫେରନ୍ତୁ ପଦସମଷ୍ଟି;
  ret = targetm.convert_to_type (type, ପଦସମଷ୍ଟି);
  ଯଦି (ret)
      ଫେରନ୍ତୁ ret;

  STRIP_TYPE_NOPS (e);

  ଯଦି (TYPE_MAIN_VARIANT (type) == TYPE_MAIN_VARIANT (ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି))
      && (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି)) != COMPLEX_TYPE
	  || ବୃକ୍ଷ_CODE (e) == COMPLEX_ପଦସମଷ୍ଟି))
    ଫେରନ୍ତୁ fold_convert_loc (loc, type, ପଦସମଷ୍ଟି);
  ଯଦି (ବୃକ୍ଷ_CODE (ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି)) == ERROR_MARK)
    ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
  ଯଦି (VOID_TYPE_P (ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି)))
    {
      error ("void value not ignored as it ought to be");
      ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
    }

  {
    ବୃକ୍ଷ false_ମୂଲ୍ୟ, true_ମୂଲ୍ୟ;
    ଯଦି (c_hardbool_type_attr (type, &false_ମୂଲ୍ୟ, &true_ମୂଲ୍ୟ))
      {
	ତାର୍କିକ save = in_late_ଦ୍ୱିମିକ_op;
	in_late_ଦ୍ୱିମିକ_op = ସତ୍ୟ;
	ପଦସମଷ୍ଟି = c_objc_common_truthvalue_conversion (ନିବେଶ_location, ପଦସମଷ୍ଟି);
	in_late_ଦ୍ୱିମିକ_op = save;

	ଫେରନ୍ତୁ fold_build3_loc (loc, COND_ପଦସମଷ୍ଟି, type,
				ପଦସମଷ୍ଟି, true_ମୂଲ୍ୟ, false_ମୂଲ୍ୟ);
      }
  }

  ବାଛ (code)
    {
    ସ୍ଥିତି VOID_TYPE:
      ଫେରନ୍ତୁ fold_convert_loc (loc, type, e);

    ସ୍ଥିତି ENUMERAL_TYPE:
      ଯଦି (ENUM_UNDERLYING_TYPE (type) != NULL_ବୃକ୍ଷ
	  && ବୃକ୍ଷ_CODE (ENUM_UNDERLYING_TYPE (type)) == BOOLEAN_TYPE)
	ଯାଅ convert_to_boolean;
      gcc_fallthrough ();

    ସ୍ଥିତି INTEGER_TYPE:
    ସ୍ଥିତି BITINT_TYPE:
      ଯଦି (sanitize_flags_p (SANITIZE_FLOAT_CAST)
	  && current_function_decl != NULL_ବୃକ୍ଷ
	  && SCALAR_FLOAT_TYPE_P (ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି))
	  && COMPLETE_TYPE_P (type))
	{
	  ପଦସମଷ୍ଟି = save_ପଦସମଷ୍ଟି (ପଦସମଷ୍ଟି);
	  ପଦସମଷ୍ଟି = c_fully_fold (ପଦସମଷ୍ଟି, init_const, ଖାଲି);
	  ବୃକ୍ଷ check = ubsan_instrument_float_cast (loc, type, ପଦସମଷ୍ଟି);
	  ପଦସମଷ୍ଟି = fold_build1 (FIX_TRUNC_ପଦସମଷ୍ଟି, type, ପଦସମଷ୍ଟି);
	  ଯଦି (check == NULL_ବୃକ୍ଷ)
	    ଫେରନ୍ତୁ ପଦସମଷ୍ଟି;
	  ଫେରନ୍ତୁ fold_build2 (COMPOUND_ପଦସମଷ୍ଟି, ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି), check, ପଦସମଷ୍ଟି);
	}
      ret = convert_to_integer (type, e);
      ଯାଅ maybe_fold;

    ସ୍ଥିତି BOOLEAN_TYPE:
    convert_to_boolean:
      ଫେରନ୍ତୁ c_objc_common_truthvalue_conversion (ନିବେଶ_location, ପଦସମଷ୍ଟି, type);

    ସ୍ଥିତି POINTER_TYPE:
      /* The type nullptr_t may be converted to a pointer type.  The result is
	 a null pointer value.  */
      ଯଦି (NULLPTR_TYPE_P (ବୃକ୍ଷ_TYPE (e)))
	{
	  /* To make sure that (void *)nullptr is not a null pointer constant,
	     build_c_cast will create an additional NOP_EXPR around the result
	     of this conversion.  */
	  ଯଦି (ବୃକ୍ଷ_SIDE_EFFECTS (e))
	    ret = build2 (COMPOUND_ପଦସମଷ୍ଟି, type, e, build_int_cst (type, 0));
	  ଅନ୍ୟଥା
	    ret = build_int_cst (type, 0);
	  ଯାଅ maybe_fold;
	}
      gcc_fallthrough ();
    ସ୍ଥିତି REFERENCE_TYPE:
      ret = convert_to_pointer (type, e);
      ଯାଅ maybe_fold;

    ସ୍ଥିତି NULLPTR_TYPE:
      /* A null pointer constant or value of type nullptr_t may be
	 converted to nullptr_t.  The latter case has already been
	 handled.  build_c_cast will create an additional NOP_EXPR to
	 ensure the result of the conversion is not itself a null
	 pointer constant.  */
      ଯଦି (null_pointer_constant_p (ପଦସମଷ୍ଟି))
	{
	  ret = build_int_cst (type, 0);
	  ଯାଅ maybe_fold;
	}
      ଭାଙ୍ଗ;

    ସ୍ଥିତି REAL_TYPE:
      ret = convert_to_real (type, e);
      ଯାଅ maybe_fold;

    ସ୍ଥିତି FIXED_POINT_TYPE:
      ret = convert_to_fixed (type, e);
      ଯାଅ maybe_fold;

    ସ୍ଥିତି COMPLEX_TYPE:
      ret = convert_to_complex (type, e);
      ଯାଅ maybe_fold;

    ସ୍ଥିତି VECTOR_TYPE:
      ଯଦି (gnu_vector_type_p (type)
	  || gnu_vector_type_p (ବୃକ୍ଷ_TYPE (e))
	  /* Allow conversions between compatible non-GNU vector types
	     when -flax-vector-conversions is passed.  The whole purpose
	     of the option is to bend the normal type rules and accept
	     nonconforming code.  */
	  || (flag_lax_vector_conversions
	      && VECTOR_TYPE_P (ବୃକ୍ଷ_TYPE (e))
	      && vector_types_convertible_p (type, ବୃକ୍ଷ_TYPE (e), ମିଥ୍ୟା)))
	{
	  ret = convert_to_vector (type, e);
	  ଯାଅ maybe_fold;
	}
      ଭାଙ୍ଗ;

    ସ୍ଥିତି RECORD_TYPE:
    ସ୍ଥିତି UNION_TYPE:
      ଯଦି (lang_hooks.types_compatible_p (type, ବୃକ୍ଷ_TYPE (ପଦସମଷ୍ଟି)))
	ଫେରନ୍ତୁ e;
      ଭାଙ୍ଗ;

    ପୂର୍ବନିର୍ଦ୍ଧାରିତ:
      ଭାଙ୍ଗ;

    maybe_fold:
      ଯଦି (ବୃକ୍ଷ_CODE (ret) != C_MAYBE_CONST_ପଦସମଷ୍ଟି)
	ret = init_const ? fold_init (ret) : fold (ret);
      ଫେରନ୍ତୁ ret;
    }

  /* If we are converting to nullptr_t, don't say "non-scalar type" because
     the nullptr_t type is a scalar type.  Only nullptr_t or a null pointer
     constant shall be converted to nullptr_t.  */
  ଯଦି (code == NULLPTR_TYPE)
    {
      error ("conversion from %qT to %qT", ବୃକ୍ଷ_TYPE (e), type);
      inform (ନିବେଶ_location,
	      "only %qT or a null pointer constant can be converted to %qT",
	      type, type);
    }
  ଅନ୍ୟଥା
    error ("conversion to non-scalar type requested");
  ଫେରନ୍ତୁ error_mark_ଗଣ୍ଠି;
}

/* Create an expression whose value is that of EXPR, converted to type TYPE.
   The TREE_TYPE of the value is always TYPE.  This function implements all
   reasonable conversions; callers should filter out those that are not
   permitted by the language being compiled.  */

ବୃକ୍ଷ
convert (ବୃକ୍ଷ type, ବୃକ୍ଷ ପଦସମଷ୍ଟି)
{
  ଫେରନ୍ତୁ c_convert (type, ପଦସମଷ୍ଟି, ମିଥ୍ୟା);
}

/* Create an expression whose value is that of EXPR, converted to type TYPE, in
   a static initializer.  The TREE_TYPE of the value is always TYPE.  This
   function implements all reasonable conversions; callers should filter out
   those that are not permitted by the language being compiled.  */

ବୃକ୍ଷ
convert_init (ବୃକ୍ଷ type, ବୃକ୍ଷ ପଦସମଷ୍ଟି)
{
  ଫେରନ୍ତୁ c_convert (type, ପଦସମଷ୍ଟି, ସତ୍ୟ);
}
