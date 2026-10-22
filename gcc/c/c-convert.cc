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

#അന്തര്ഭാവ "config.h"
#അന്തര്ഭാവ "system.h"
#അന്തര്ഭാവ "coretypes.h"
#അന്തര്ഭാവ "target.h"
#അന്തര്ഭാവ "c-tree.h"
#അന്തര്ഭാവ "convert.h"
#അന്തര്ഭാവ "langhooks.h"
#അന്തര്ഭാവ "ubsan.h"
#അന്തര്ഭാവ "stringpool.h"
#അന്തര്ഭാവ "attribs.h"
#അന്തര്ഭാവ "asan.h"

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

സ്ഥിതം വൃക്ഷം
c_convert (വൃക്ഷം type, വൃക്ഷം വ്യഞ്ജകം, തർക്കം init_const)
{
  വൃക്ഷം e = വ്യഞ്ജകം;
  എണ്ണൽ വൃക്ഷം_code code = വൃക്ഷം_CODE (type);
  സ്ഥിരം അക്ഷരം *invalid_conv_diag;
  വൃക്ഷം ret;
  location_t loc = വ്യഞ്ജകം_LOCATION (വ്യഞ്ജകം);

  എങ്കിൽ (type == error_mark_കണ്ണി
      || error_operand_p (വ്യഞ്ജകം))
    തിരികെ error_mark_കണ്ണി;

  എങ്കിൽ ((invalid_conv_diag
       = targetm.invalid_conversion (വൃക്ഷം_TYPE (വ്യഞ്ജകം), type)))
    {
      error (invalid_conv_diag);
      തിരികെ error_mark_കണ്ണി;
    }

  എങ്കിൽ (type == വൃക്ഷം_TYPE (വ്യഞ്ജകം))
    തിരികെ വ്യഞ്ജകം;
  ret = targetm.convert_to_type (type, വ്യഞ്ജകം);
  എങ്കിൽ (ret)
      തിരികെ ret;

  STRIP_TYPE_NOPS (e);

  എങ്കിൽ (TYPE_MAIN_VARIANT (type) == TYPE_MAIN_VARIANT (വൃക്ഷം_TYPE (വ്യഞ്ജകം))
      && (വൃക്ഷം_CODE (വൃക്ഷം_TYPE (വ്യഞ്ജകം)) != COMPLEX_TYPE
	  || വൃക്ഷം_CODE (e) == COMPLEX_വ്യഞ്ജകം))
    തിരികെ fold_convert_loc (loc, type, വ്യഞ്ജകം);
  എങ്കിൽ (വൃക്ഷം_CODE (വൃക്ഷം_TYPE (വ്യഞ്ജകം)) == ERROR_MARK)
    തിരികെ error_mark_കണ്ണി;
  എങ്കിൽ (VOID_TYPE_P (വൃക്ഷം_TYPE (വ്യഞ്ജകം)))
    {
      error ("void value not ignored as it ought to be");
      തിരികെ error_mark_കണ്ണി;
    }

  {
    വൃക്ഷം false_മൂല്യം, true_മൂല്യം;
    എങ്കിൽ (c_hardbool_type_attr (type, &false_മൂല്യം, &true_മൂല്യം))
      {
	തർക്കം save = in_late_ദ്വിമാന_op;
	in_late_ദ്വിമാന_op = സത്യം;
	വ്യഞ്ജകം = c_objc_common_truthvalue_conversion (നിവേശം_location, വ്യഞ്ജകം);
	in_late_ദ്വിമാന_op = save;

	തിരികെ fold_build3_loc (loc, COND_വ്യഞ്ജകം, type,
				വ്യഞ്ജകം, true_മൂല്യം, false_മൂല്യം);
      }
  }

  തിരഞ്ഞെടുപ്പ് (code)
    {
    അവസ്ഥ VOID_TYPE:
      തിരികെ fold_convert_loc (loc, type, e);

    അവസ്ഥ ENUMERAL_TYPE:
      എങ്കിൽ (ENUM_UNDERLYING_TYPE (type) != NULL_വൃക്ഷം
	  && വൃക്ഷം_CODE (ENUM_UNDERLYING_TYPE (type)) == BOOLEAN_TYPE)
	പോകുക convert_to_boolean;
      gcc_fallthrough ();

    അവസ്ഥ INTEGER_TYPE:
    അവസ്ഥ BITINT_TYPE:
      എങ്കിൽ (sanitize_flags_p (SANITIZE_FLOAT_CAST)
	  && current_function_decl != NULL_വൃക്ഷം
	  && SCALAR_FLOAT_TYPE_P (വൃക്ഷം_TYPE (വ്യഞ്ജകം))
	  && COMPLETE_TYPE_P (type))
	{
	  വ്യഞ്ജകം = save_വ്യഞ്ജകം (വ്യഞ്ജകം);
	  വ്യഞ്ജകം = c_fully_fold (വ്യഞ്ജകം, init_const, ശൂന്യ);
	  വൃക്ഷം check = ubsan_instrument_float_cast (loc, type, വ്യഞ്ജകം);
	  വ്യഞ്ജകം = fold_build1 (FIX_TRUNC_വ്യഞ്ജകം, type, വ്യഞ്ജകം);
	  എങ്കിൽ (check == NULL_വൃക്ഷം)
	    തിരികെ വ്യഞ്ജകം;
	  തിരികെ fold_build2 (COMPOUND_വ്യഞ്ജകം, വൃക്ഷം_TYPE (വ്യഞ്ജകം), check, വ്യഞ്ജകം);
	}
      ret = convert_to_integer (type, e);
      പോകുക maybe_fold;

    അവസ്ഥ BOOLEAN_TYPE:
    convert_to_boolean:
      തിരികെ c_objc_common_truthvalue_conversion (നിവേശം_location, വ്യഞ്ജകം, type);

    അവസ്ഥ POINTER_TYPE:
      /* The type nullptr_t may be converted to a pointer type.  The result is
	 a null pointer value.  */
      എങ്കിൽ (NULLPTR_TYPE_P (വൃക്ഷം_TYPE (e)))
	{
	  /* To make sure that (void *)nullptr is not a null pointer constant,
	     build_c_cast will create an additional NOP_EXPR around the result
	     of this conversion.  */
	  എങ്കിൽ (വൃക്ഷം_SIDE_EFFECTS (e))
	    ret = build2 (COMPOUND_വ്യഞ്ജകം, type, e, build_int_cst (type, 0));
	  അല്ലെങ്കിൽ
	    ret = build_int_cst (type, 0);
	  പോകുക maybe_fold;
	}
      gcc_fallthrough ();
    അവസ്ഥ REFERENCE_TYPE:
      ret = convert_to_pointer (type, e);
      പോകുക maybe_fold;

    അവസ്ഥ NULLPTR_TYPE:
      /* A null pointer constant or value of type nullptr_t may be
	 converted to nullptr_t.  The latter case has already been
	 handled.  build_c_cast will create an additional NOP_EXPR to
	 ensure the result of the conversion is not itself a null
	 pointer constant.  */
      എങ്കിൽ (null_pointer_constant_p (വ്യഞ്ജകം))
	{
	  ret = build_int_cst (type, 0);
	  പോകുക maybe_fold;
	}
      നിർത്തുക;

    അവസ്ഥ REAL_TYPE:
      ret = convert_to_real (type, e);
      പോകുക maybe_fold;

    അവസ്ഥ FIXED_POINT_TYPE:
      ret = convert_to_fixed (type, e);
      പോകുക maybe_fold;

    അവസ്ഥ COMPLEX_TYPE:
      ret = convert_to_complex (type, e);
      പോകുക maybe_fold;

    അവസ്ഥ VECTOR_TYPE:
      എങ്കിൽ (gnu_vector_type_p (type)
	  || gnu_vector_type_p (വൃക്ഷം_TYPE (e))
	  /* Allow conversions between compatible non-GNU vector types
	     when -flax-vector-conversions is passed.  The whole purpose
	     of the option is to bend the normal type rules and accept
	     nonconforming code.  */
	  || (flag_lax_vector_conversions
	      && VECTOR_TYPE_P (വൃക്ഷം_TYPE (e))
	      && vector_types_convertible_p (type, വൃക്ഷം_TYPE (e), അസത്യം)))
	{
	  ret = convert_to_vector (type, e);
	  പോകുക maybe_fold;
	}
      നിർത്തുക;

    അവസ്ഥ RECORD_TYPE:
    അവസ്ഥ UNION_TYPE:
      എങ്കിൽ (lang_hooks.types_compatible_p (type, വൃക്ഷം_TYPE (വ്യഞ്ജകം)))
	തിരികെ e;
      നിർത്തുക;

    സ്ഥിരസ്ഥിതി:
      നിർത്തുക;

    maybe_fold:
      എങ്കിൽ (വൃക്ഷം_CODE (ret) != C_MAYBE_CONST_വ്യഞ്ജകം)
	ret = init_const ? fold_init (ret) : fold (ret);
      തിരികെ ret;
    }

  /* If we are converting to nullptr_t, don't say "non-scalar type" because
     the nullptr_t type is a scalar type.  Only nullptr_t or a null pointer
     constant shall be converted to nullptr_t.  */
  എങ്കിൽ (code == NULLPTR_TYPE)
    {
      error ("conversion from %qT to %qT", വൃക്ഷം_TYPE (e), type);
      inform (നിവേശം_location,
	      "only %qT or a null pointer constant can be converted to %qT",
	      type, type);
    }
  അല്ലെങ്കിൽ
    error ("conversion to non-scalar type requested");
  തിരികെ error_mark_കണ്ണി;
}

/* Create an expression whose value is that of EXPR, converted to type TYPE.
   The TREE_TYPE of the value is always TYPE.  This function implements all
   reasonable conversions; callers should filter out those that are not
   permitted by the language being compiled.  */

വൃക്ഷം
convert (വൃക്ഷം type, വൃക്ഷം വ്യഞ്ജകം)
{
  തിരികെ c_convert (type, വ്യഞ്ജകം, അസത്യം);
}

/* Create an expression whose value is that of EXPR, converted to type TYPE, in
   a static initializer.  The TREE_TYPE of the value is always TYPE.  This
   function implements all reasonable conversions; callers should filter out
   those that are not permitted by the language being compiled.  */

വൃക്ഷം
convert_init (വൃക്ഷം type, വൃക്ഷം വ്യഞ്ജകം)
{
  തിരികെ c_convert (type, വ്യഞ്ജകം, സത്യം);
}
