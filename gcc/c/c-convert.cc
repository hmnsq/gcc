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

स्थिर वृक्ष
c_convert (वृक्ष type, वृक्ष अभिव्यक्ती, तार्किक init_const)
{
  वृक्ष e = अभिव्यक्ती;
  गणना वृक्ष_code code = वृक्ष_CODE (type);
  ध्रुव वर्ण *invalid_conv_diag;
  वृक्ष ret;
  location_t loc = अभिव्यक्ती_LOCATION (अभिव्यक्ती);

  यदि (type == error_mark_गाठ
      || error_operand_p (अभिव्यक्ती))
    प्रत्यागम error_mark_गाठ;

  यदि ((invalid_conv_diag
       = targetm.invalid_conversion (वृक्ष_TYPE (अभिव्यक्ती), type)))
    {
      error (invalid_conv_diag);
      प्रत्यागम error_mark_गाठ;
    }

  यदि (type == वृक्ष_TYPE (अभिव्यक्ती))
    प्रत्यागम अभिव्यक्ती;
  ret = targetm.convert_to_type (type, अभिव्यक्ती);
  यदि (ret)
      प्रत्यागम ret;

  STRIP_TYPE_NOPS (e);

  यदि (TYPE_MAIN_VARIANT (type) == TYPE_MAIN_VARIANT (वृक्ष_TYPE (अभिव्यक्ती))
      && (वृक्ष_CODE (वृक्ष_TYPE (अभिव्यक्ती)) != COMPLEX_TYPE
	  || वृक्ष_CODE (e) == COMPLEX_अभिव्यक्ती))
    प्रत्यागम fold_convert_loc (loc, type, अभिव्यक्ती);
  यदि (वृक्ष_CODE (वृक्ष_TYPE (अभिव्यक्ती)) == ERROR_MARK)
    प्रत्यागम error_mark_गाठ;
  यदि (VOID_TYPE_P (वृक्ष_TYPE (अभिव्यक्ती)))
    {
      error ("void value not ignored as it ought to be");
      प्रत्यागम error_mark_गाठ;
    }

  {
    वृक्ष false_मूल्य, true_मूल्य;
    यदि (c_hardbool_type_attr (type, &false_मूल्य, &true_मूल्य))
      {
	तार्किक save = in_late_द्विमान_op;
	in_late_द्विमान_op = सत्य;
	अभिव्यक्ती = c_objc_common_truthvalue_conversion (आदान_location, अभिव्यक्ती);
	in_late_द्विमान_op = save;

	प्रत्यागम fold_build3_loc (loc, COND_अभिव्यक्ती, type,
				अभिव्यक्ती, true_मूल्य, false_मूल्य);
      }
  }

  विकल्प (code)
    {
    पक्ष VOID_TYPE:
      प्रत्यागम fold_convert_loc (loc, type, e);

    पक्ष ENUMERAL_TYPE:
      यदि (ENUM_UNDERLYING_TYPE (type) != NULL_वृक्ष
	  && वृक्ष_CODE (ENUM_UNDERLYING_TYPE (type)) == BOOLEAN_TYPE)
	गच्छ convert_to_boolean;
      gcc_fallthrough ();

    पक्ष INTEGER_TYPE:
    पक्ष BITINT_TYPE:
      यदि (sanitize_flags_p (SANITIZE_FLOAT_CAST)
	  && current_function_decl != NULL_वृक्ष
	  && SCALAR_FLOAT_TYPE_P (वृक्ष_TYPE (अभिव्यक्ती))
	  && COMPLETE_TYPE_P (type))
	{
	  अभिव्यक्ती = save_अभिव्यक्ती (अभिव्यक्ती);
	  अभिव्यक्ती = c_fully_fold (अभिव्यक्ती, init_const, रिक्त);
	  वृक्ष check = ubsan_instrument_float_cast (loc, type, अभिव्यक्ती);
	  अभिव्यक्ती = fold_build1 (FIX_TRUNC_अभिव्यक्ती, type, अभिव्यक्ती);
	  यदि (check == NULL_वृक्ष)
	    प्रत्यागम अभिव्यक्ती;
	  प्रत्यागम fold_build2 (COMPOUND_अभिव्यक्ती, वृक्ष_TYPE (अभिव्यक्ती), check, अभिव्यक्ती);
	}
      ret = convert_to_integer (type, e);
      गच्छ maybe_fold;

    पक्ष BOOLEAN_TYPE:
    convert_to_boolean:
      प्रत्यागम c_objc_common_truthvalue_conversion (आदान_location, अभिव्यक्ती, type);

    पक्ष POINTER_TYPE:
      /* The type nullptr_t may be converted to a pointer type.  The result is
	 a null pointer value.  */
      यदि (NULLPTR_TYPE_P (वृक्ष_TYPE (e)))
	{
	  /* To make sure that (void *)nullptr is not a null pointer constant,
	     build_c_cast will create an additional NOP_EXPR around the result
	     of this conversion.  */
	  यदि (वृक्ष_SIDE_EFFECTS (e))
	    ret = build2 (COMPOUND_अभिव्यक्ती, type, e, build_int_cst (type, 0));
	  अन्यथा
	    ret = build_int_cst (type, 0);
	  गच्छ maybe_fold;
	}
      gcc_fallthrough ();
    पक्ष REFERENCE_TYPE:
      ret = convert_to_pointer (type, e);
      गच्छ maybe_fold;

    पक्ष NULLPTR_TYPE:
      /* A null pointer constant or value of type nullptr_t may be
	 converted to nullptr_t.  The latter case has already been
	 handled.  build_c_cast will create an additional NOP_EXPR to
	 ensure the result of the conversion is not itself a null
	 pointer constant.  */
      यदि (null_pointer_constant_p (अभिव्यक्ती))
	{
	  ret = build_int_cst (type, 0);
	  गच्छ maybe_fold;
	}
      भङ्ग;

    पक्ष REAL_TYPE:
      ret = convert_to_real (type, e);
      गच्छ maybe_fold;

    पक्ष FIXED_POINT_TYPE:
      ret = convert_to_fixed (type, e);
      गच्छ maybe_fold;

    पक्ष COMPLEX_TYPE:
      ret = convert_to_complex (type, e);
      गच्छ maybe_fold;

    पक्ष VECTOR_TYPE:
      यदि (gnu_vector_type_p (type)
	  || gnu_vector_type_p (वृक्ष_TYPE (e))
	  /* Allow conversions between compatible non-GNU vector types
	     when -flax-vector-conversions is passed.  The whole purpose
	     of the option is to bend the normal type rules and accept
	     nonconforming code.  */
	  || (flag_lax_vector_conversions
	      && VECTOR_TYPE_P (वृक्ष_TYPE (e))
	      && vector_types_convertible_p (type, वृक्ष_TYPE (e), असत्य)))
	{
	  ret = convert_to_vector (type, e);
	  गच्छ maybe_fold;
	}
      भङ्ग;

    पक्ष RECORD_TYPE:
    पक्ष UNION_TYPE:
      यदि (lang_hooks.types_compatible_p (type, वृक्ष_TYPE (अभिव्यक्ती)))
	प्रत्यागम e;
      भङ्ग;

    स्वभाव:
      भङ्ग;

    maybe_fold:
      यदि (वृक्ष_CODE (ret) != C_MAYBE_CONST_अभिव्यक्ती)
	ret = init_const ? fold_init (ret) : fold (ret);
      प्रत्यागम ret;
    }

  /* If we are converting to nullptr_t, don't say "non-scalar type" because
     the nullptr_t type is a scalar type.  Only nullptr_t or a null pointer
     constant shall be converted to nullptr_t.  */
  यदि (code == NULLPTR_TYPE)
    {
      error ("conversion from %qT to %qT", वृक्ष_TYPE (e), type);
      inform (आदान_location,
	      "only %qT or a null pointer constant can be converted to %qT",
	      type, type);
    }
  अन्यथा
    error ("conversion to non-scalar type requested");
  प्रत्यागम error_mark_गाठ;
}

/* Create an expression whose value is that of EXPR, converted to type TYPE.
   The TREE_TYPE of the value is always TYPE.  This function implements all
   reasonable conversions; callers should filter out those that are not
   permitted by the language being compiled.  */

वृक्ष
convert (वृक्ष type, वृक्ष अभिव्यक्ती)
{
  प्रत्यागम c_convert (type, अभिव्यक्ती, असत्य);
}

/* Create an expression whose value is that of EXPR, converted to type TYPE, in
   a static initializer.  The TREE_TYPE of the value is always TYPE.  This
   function implements all reasonable conversions; callers should filter out
   those that are not permitted by the language being compiled.  */

वृक्ष
convert_init (वृक्ष type, वृक्ष अभिव्यक्ती)
{
  प्रत्यागम c_convert (type, अभिव्यक्ती, सत्य);
}
