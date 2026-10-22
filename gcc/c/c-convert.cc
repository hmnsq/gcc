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

#अन्तर्भाव "config.h"
#अन्तर्भाव "system.h"
#अन्तर्भाव "coretypes.h"
#अन्तर्भाव "target.h"
#अन्तर्भाव "c-tree.h"
#अन्तर्भाव "convert.h"
#अन्तर्भाव "langhooks.h"
#अन्तर्भाव "ubsan.h"
#अन्तर्भाव "stringpool.h"
#अन्तर्भाव "attribs.h"
#अन्तर्भाव "asan.h"

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

स्थिर वृक्षः
c_convert (वृक्षः type, वृक्षः व्यञ्जकम्, तार्किक init_const)
{
  वृक्षः e = व्यञ्जकम्;
  गणना वृक्षः_संहिता_2 संहिता = वृक्षः_संहिता (type);
  ध्रुव वर्ण *invalid_conv_diag;
  वृक्षः ret;
  location_t loc = व्यञ्जकम्_LOCATION (व्यञ्जकम्);

  यदि (type == error_mark_ग्रन्थिः
      || error_सङ्कार्यम्_p (व्यञ्जकम्))
    प्रत्यागम error_mark_ग्रन्थिः;

  यदि ((invalid_conv_diag
       = targetm.invalid_conversion (वृक्षः_TYPE (व्यञ्जकम्), type)))
    {
      error (invalid_conv_diag);
      प्रत्यागम error_mark_ग्रन्थिः;
    }

  यदि (type == वृक्षः_TYPE (व्यञ्जकम्))
    प्रत्यागम व्यञ्जकम्;
  ret = targetm.convert_गन्तव्यम्_type (type, व्यञ्जकम्);
  यदि (ret)
      प्रत्यागम ret;

  STRIP_TYPE_NOPS (e);

  यदि (TYPE_MAIN_VARIANT (type) == TYPE_MAIN_VARIANT (वृक्षः_TYPE (व्यञ्जकम्))
      && (वृक्षः_संहिता (वृक्षः_TYPE (व्यञ्जकम्)) != COMPLEX_TYPE
	  || वृक्षः_संहिता (e) == COMPLEX_व्यञ्जकम्))
    प्रत्यागम fold_convert_loc (loc, type, व्यञ्जकम्);
  यदि (वृक्षः_संहिता (वृक्षः_TYPE (व्यञ्जकम्)) == ERROR_MARK)
    प्रत्यागम error_mark_ग्रन्थिः;
  यदि (VOID_TYPE_P (वृक्षः_TYPE (व्यञ्जकम्)))
    {
      error ("void value not ignored as it ought to be");
      प्रत्यागम error_mark_ग्रन्थिः;
    }

  {
    वृक्षः false_मानम्, true_मानम्;
    यदि (c_hardbool_type_attr (type, &false_मानम्, &true_मानम्))
      {
	तार्किक save = अन्तर्_late_द्विमान_op;
	अन्तर्_late_द्विमान_op = सत्य;
	व्यञ्जकम् = c_objc_common_truthvalue_conversion (निवेशः_location, व्यञ्जकम्);
	अन्तर्_late_द्विमान_op = save;

	प्रत्यागम fold_build3_loc (loc, COND_व्यञ्जकम्, type,
				व्यञ्जकम्, true_मानम्, false_मानम्);
      }
  }

  विकल्प (संहिता)
    {
    पक्ष VOID_TYPE:
      प्रत्यागम fold_convert_loc (loc, type, e);

    पक्ष ENUMERAL_TYPE:
      यदि (ENUM_UNDERLYING_TYPE (type) != NULL_वृक्षः
	  && वृक्षः_संहिता (ENUM_UNDERLYING_TYPE (type)) == BOOLEAN_TYPE)
	गच्छ convert_गन्तव्यम्_boolean;
      gcc_fallthrough ();

    पक्ष INTEGER_TYPE:
    पक्ष BITINT_TYPE:
      यदि (sanitize_flags_p (SANITIZE_FLOAT_CAST)
	  && current_function_decl != NULL_वृक्षः
	  && SCALAR_FLOAT_TYPE_P (वृक्षः_TYPE (व्यञ्जकम्))
	  && COMPLETE_TYPE_P (type))
	{
	  व्यञ्जकम् = save_व्यञ्जकम् (व्यञ्जकम्);
	  व्यञ्जकम् = c_fully_fold (व्यञ्जकम्, init_const, रिक्त);
	  वृक्षः check = ubsan_instrument_float_cast (loc, type, व्यञ्जकम्);
	  व्यञ्जकम् = fold_build1 (FIX_TRUNC_व्यञ्जकम्, type, व्यञ्जकम्);
	  यदि (check == NULL_वृक्षः)
	    प्रत्यागम व्यञ्जकम्;
	  प्रत्यागम fold_build2 (COMPOUND_व्यञ्जकम्, वृक्षः_TYPE (व्यञ्जकम्), check, व्यञ्जकम्);
	}
      ret = convert_गन्तव्यम्_integer (type, e);
      गच्छ maybe_fold;

    पक्ष BOOLEAN_TYPE:
    convert_गन्तव्यम्_boolean:
      प्रत्यागम c_objc_common_truthvalue_conversion (निवेशः_location, व्यञ्जकम्, type);

    पक्ष POINTER_TYPE:
      /* The type nullptr_t may be converted to a pointer type.  The result is
	 a null pointer value.  */
      यदि (NULLPTR_TYPE_P (वृक्षः_TYPE (e)))
	{
	  /* To make sure that (void *)nullptr is not a null pointer constant,
	     build_c_cast will create an additional NOP_EXPR around the result
	     of this conversion.  */
	  यदि (वृक्षः_SIDE_EFFECTS (e))
	    ret = build2 (COMPOUND_व्यञ्जकम्, type, e, build_int_cst (type, 0));
	  अन्यथा
	    ret = build_int_cst (type, 0);
	  गच्छ maybe_fold;
	}
      gcc_fallthrough ();
    पक्ष REFERENCE_TYPE:
      ret = convert_गन्तव्यम्_pointer (type, e);
      गच्छ maybe_fold;

    पक्ष NULLPTR_TYPE:
      /* A null pointer constant or value of type nullptr_t may be
	 converted to nullptr_t.  The latter case has already been
	 handled.  build_c_cast will create an additional NOP_EXPR to
	 ensure the result of the conversion is not itself a null
	 pointer constant.  */
      यदि (null_pointer_constant_p (व्यञ्जकम्))
	{
	  ret = build_int_cst (type, 0);
	  गच्छ maybe_fold;
	}
      भङ्ग;

    पक्ष REAL_TYPE:
      ret = convert_गन्तव्यम्_real (type, e);
      गच्छ maybe_fold;

    पक्ष FIXED_POINT_TYPE:
      ret = convert_गन्तव्यम्_fixed (type, e);
      गच्छ maybe_fold;

    पक्ष COMPLEX_TYPE:
      ret = convert_गन्तव्यम्_complex (type, e);
      गच्छ maybe_fold;

    पक्ष सदिशम्_TYPE:
      यदि (gnu_सदिशम्_type_p (type)
	  || gnu_सदिशम्_type_p (वृक्षः_TYPE (e))
	  /* Allow conversions between compatible non-GNU vector types
	     when -flax-vector-conversions is passed.  The whole purpose
	     of the option is to bend the normal type rules and accept
	     nonconforming code.  */
	  || (flag_lax_सदिशम्_conversions
	      && सदिशम्_TYPE_P (वृक्षः_TYPE (e))
	      && सदिशम्_types_convertible_p (type, वृक्षः_TYPE (e), असत्य)))
	{
	  ret = convert_गन्तव्यम्_सदिशम् (type, e);
	  गच्छ maybe_fold;
	}
      भङ्ग;

    पक्ष लेखः_TYPE:
    पक्ष UNION_TYPE:
      यदि (lang_hooks.types_compatible_p (type, वृक्षः_TYPE (व्यञ्जकम्)))
	प्रत्यागम e;
      भङ्ग;

    स्वभाव:
      भङ्ग;

    maybe_fold:
      यदि (वृक्षः_संहिता (ret) != C_MAYBE_CONST_व्यञ्जकम्)
	ret = init_const ? fold_init (ret) : fold (ret);
      प्रत्यागम ret;
    }

  /* If we are converting to nullptr_t, don't say "non-scalar type" because
     the nullptr_t type is a scalar type.  Only nullptr_t or a null pointer
     constant shall be converted to nullptr_t.  */
  यदि (संहिता == NULLPTR_TYPE)
    {
      error ("conversion from %qT to %qT", वृक्षः_TYPE (e), type);
      inform (निवेशः_location,
	      "only %qT or a null pointer constant can be converted to %qT",
	      type, type);
    }
  अन्यथा
    error ("conversion to non-scalar type requested");
  प्रत्यागम error_mark_ग्रन्थिः;
}

/* Create an expression whose value is that of EXPR, converted to type TYPE.
   The TREE_TYPE of the value is always TYPE.  This function implements all
   reasonable conversions; callers should filter out those that are not
   permitted by the language being compiled.  */

वृक्षः
convert (वृक्षः type, वृक्षः व्यञ्जकम्)
{
  प्रत्यागम c_convert (type, व्यञ्जकम्, असत्य);
}

/* Create an expression whose value is that of EXPR, converted to type TYPE, in
   a static initializer.  The TREE_TYPE of the value is always TYPE.  This
   function implements all reasonable conversions; callers should filter out
   those that are not permitted by the language being compiled.  */

वृक्षः
convert_init (वृक्षः type, वृक्षः व्यञ्जकम्)
{
  प्रत्यागम c_convert (type, व्यञ्जकम्, सत्य);
}
