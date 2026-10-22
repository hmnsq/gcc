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

#समावेश "config.h"
#समावेश "system.h"
#समावेश "coretypes.h"
#समावेश "target.h"
#समावेश "c-tree.h"
#समावेश "convert.h"
#समावेश "langhooks.h"
#समावेश "ubsan.h"
#समावेश "stringpool.h"
#समावेश "attribs.h"
#समावेश "asan.h"

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

अटल वृक्ष
c_convert (वृक्ष type, वृक्ष व्यंजक, bool init_const)
{
  वृक्ष e = व्यंजक;
  क्रमागत वृक्ष_code code = वृक्ष_CODE (type);
  स्थिर अक्षर *invalid_conv_diag;
  वृक्ष ret;
  location_t loc = व्यंजक_LOCATION (व्यंजक);

  अगर (type == error_mark_गाँठ
      || error_operand_p (व्यंजक))
    वापस error_mark_गाँठ;

  अगर ((invalid_conv_diag
       = targetm.invalid_conversion (वृक्ष_TYPE (व्यंजक), type)))
    {
      error (invalid_conv_diag);
      वापस error_mark_गाँठ;
    }

  अगर (type == वृक्ष_TYPE (व्यंजक))
    वापस व्यंजक;
  ret = targetm.convert_to_type (type, व्यंजक);
  अगर (ret)
      वापस ret;

  STRIP_TYPE_NOPS (e);

  अगर (TYPE_MAIN_VARIANT (type) == TYPE_MAIN_VARIANT (वृक्ष_TYPE (व्यंजक))
      && (वृक्ष_CODE (वृक्ष_TYPE (व्यंजक)) != COMPLEX_TYPE
	  || वृक्ष_CODE (e) == COMPLEX_व्यंजक))
    वापस fold_convert_loc (loc, type, व्यंजक);
  अगर (वृक्ष_CODE (वृक्ष_TYPE (व्यंजक)) == ERROR_MARK)
    वापस error_mark_गाँठ;
  अगर (VOID_TYPE_P (वृक्ष_TYPE (व्यंजक)))
    {
      error ("void value not ignored as it ought to be");
      वापस error_mark_गाँठ;
    }

  {
    वृक्ष false_मूल्य, true_मूल्य;
    अगर (c_hardbool_type_attr (type, &false_मूल्य, &true_मूल्य))
      {
	bool save = in_late_द्विआधारी_op;
	in_late_द्विआधारी_op = true;
	व्यंजक = c_objc_common_truthvalue_conversion (निवेश_location, व्यंजक);
	in_late_द्विआधारी_op = save;

	वापस fold_build3_loc (loc, COND_व्यंजक, type,
				व्यंजक, true_मूल्य, false_मूल्य);
      }
  }

  चयन (code)
    {
    हाल VOID_TYPE:
      वापस fold_convert_loc (loc, type, e);

    हाल ENUMERAL_TYPE:
      अगर (ENUM_UNDERLYING_TYPE (type) != NULL_वृक्ष
	  && वृक्ष_CODE (ENUM_UNDERLYING_TYPE (type)) == BOOLEAN_TYPE)
	जाओ convert_to_boolean;
      gcc_fallthrough ();

    हाल INTEGER_TYPE:
    हाल BITINT_TYPE:
      अगर (sanitize_flags_p (SANITIZE_FLOAT_CAST)
	  && current_function_decl != NULL_वृक्ष
	  && SCALAR_FLOAT_TYPE_P (वृक्ष_TYPE (व्यंजक))
	  && COMPLETE_TYPE_P (type))
	{
	  व्यंजक = save_व्यंजक (व्यंजक);
	  व्यंजक = c_fully_fold (व्यंजक, init_const, शून्य);
	  वृक्ष check = ubsan_instrument_float_cast (loc, type, व्यंजक);
	  व्यंजक = fold_build1 (FIX_TRUNC_व्यंजक, type, व्यंजक);
	  अगर (check == NULL_वृक्ष)
	    वापस व्यंजक;
	  वापस fold_build2 (COMPOUND_व्यंजक, वृक्ष_TYPE (व्यंजक), check, व्यंजक);
	}
      ret = convert_to_integer (type, e);
      जाओ maybe_fold;

    हाल BOOLEAN_TYPE:
    convert_to_boolean:
      वापस c_objc_common_truthvalue_conversion (निवेश_location, व्यंजक, type);

    हाल POINTER_TYPE:
      /* The type nullptr_t may be converted to a pointer type.  The result is
	 a null pointer value.  */
      अगर (NULLPTR_TYPE_P (वृक्ष_TYPE (e)))
	{
	  /* To make sure that (void *)nullptr is not a null pointer constant,
	     build_c_cast will create an additional NOP_EXPR around the result
	     of this conversion.  */
	  अगर (वृक्ष_SIDE_EFFECTS (e))
	    ret = build2 (COMPOUND_व्यंजक, type, e, build_int_cst (type, 0));
	  अन्यथा
	    ret = build_int_cst (type, 0);
	  जाओ maybe_fold;
	}
      gcc_fallthrough ();
    हाल REFERENCE_TYPE:
      ret = convert_to_pointer (type, e);
      जाओ maybe_fold;

    हाल NULLPTR_TYPE:
      /* A null pointer constant or value of type nullptr_t may be
	 converted to nullptr_t.  The latter case has already been
	 handled.  build_c_cast will create an additional NOP_EXPR to
	 ensure the result of the conversion is not itself a null
	 pointer constant.  */
      अगर (null_pointer_constant_p (व्यंजक))
	{
	  ret = build_int_cst (type, 0);
	  जाओ maybe_fold;
	}
      अवरोध;

    हाल REAL_TYPE:
      ret = convert_to_real (type, e);
      जाओ maybe_fold;

    हाल FIXED_POINT_TYPE:
      ret = convert_to_fixed (type, e);
      जाओ maybe_fold;

    हाल COMPLEX_TYPE:
      ret = convert_to_complex (type, e);
      जाओ maybe_fold;

    हाल VECTOR_TYPE:
      अगर (gnu_vector_type_p (type)
	  || gnu_vector_type_p (वृक्ष_TYPE (e))
	  /* Allow conversions between compatible non-GNU vector types
	     when -flax-vector-conversions is passed.  The whole purpose
	     of the option is to bend the normal type rules and accept
	     nonconforming code.  */
	  || (flag_lax_vector_conversions
	      && VECTOR_TYPE_P (वृक्ष_TYPE (e))
	      && vector_types_convertible_p (type, वृक्ष_TYPE (e), false)))
	{
	  ret = convert_to_vector (type, e);
	  जाओ maybe_fold;
	}
      अवरोध;

    हाल RECORD_TYPE:
    हाल UNION_TYPE:
      अगर (lang_hooks.types_compatible_p (type, वृक्ष_TYPE (व्यंजक)))
	वापस e;
      अवरोध;

    शेष:
      अवरोध;

    maybe_fold:
      अगर (वृक्ष_CODE (ret) != C_MAYBE_CONST_व्यंजक)
	ret = init_const ? fold_init (ret) : fold (ret);
      वापस ret;
    }

  /* If we are converting to nullptr_t, don't say "non-scalar type" because
     the nullptr_t type is a scalar type.  Only nullptr_t or a null pointer
     constant shall be converted to nullptr_t.  */
  अगर (code == NULLPTR_TYPE)
    {
      error ("conversion from %qT to %qT", वृक्ष_TYPE (e), type);
      inform (निवेश_location,
	      "only %qT or a null pointer constant can be converted to %qT",
	      type, type);
    }
  अन्यथा
    error ("conversion to non-scalar type requested");
  वापस error_mark_गाँठ;
}

/* Create an expression whose value is that of EXPR, converted to type TYPE.
   The TREE_TYPE of the value is always TYPE.  This function implements all
   reasonable conversions; callers should filter out those that are not
   permitted by the language being compiled.  */

वृक्ष
convert (वृक्ष type, वृक्ष व्यंजक)
{
  वापस c_convert (type, व्यंजक, false);
}

/* Create an expression whose value is that of EXPR, converted to type TYPE, in
   a static initializer.  The TREE_TYPE of the value is always TYPE.  This
   function implements all reasonable conversions; callers should filter out
   those that are not permitted by the language being compiled.  */

वृक्ष
convert_init (वृक्ष type, वृक्ष व्यंजक)
{
  वापस c_convert (type, व्यंजक, true);
}
