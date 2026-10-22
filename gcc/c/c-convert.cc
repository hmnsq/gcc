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

#અન્તર્ભાવ "config.h"
#અન્તર્ભાવ "system.h"
#અન્તર્ભાવ "coretypes.h"
#અન્તર્ભાવ "target.h"
#અન્તર્ભાવ "c-tree.h"
#અન્તર્ભાવ "convert.h"
#અન્તર્ભાવ "langhooks.h"
#અન્તર્ભાવ "ubsan.h"
#અન્તર્ભાવ "stringpool.h"
#અન્તર્ભાવ "attribs.h"
#અન્તર્ભાવ "asan.h"

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

સ્થિર વૃક્ષ
c_convert (વૃક્ષ type, વૃક્ષ પદાવલિ, તાર્કિક init_const)
{
  વૃક્ષ e = પદાવલિ;
  ગણના વૃક્ષ_code code = વૃક્ષ_CODE (type);
  અચલ અક્ષર *invalid_conv_diag;
  વૃક્ષ ret;
  location_t loc = પદાવલિ_LOCATION (પદાવલિ);

  જો (type == error_mark_ગાંઠ
      || error_operand_p (પદાવલિ))
    પાછા error_mark_ગાંઠ;

  જો ((invalid_conv_diag
       = targetm.invalid_conversion (વૃક્ષ_TYPE (પદાવલિ), type)))
    {
      error (invalid_conv_diag);
      પાછા error_mark_ગાંઠ;
    }

  જો (type == વૃક્ષ_TYPE (પદાવલિ))
    પાછા પદાવલિ;
  ret = targetm.convert_to_type (type, પદાવલિ);
  જો (ret)
      પાછા ret;

  STRIP_TYPE_NOPS (e);

  જો (TYPE_MAIN_VARIANT (type) == TYPE_MAIN_VARIANT (વૃક્ષ_TYPE (પદાવલિ))
      && (વૃક્ષ_CODE (વૃક્ષ_TYPE (પદાવલિ)) != COMPLEX_TYPE
	  || વૃક્ષ_CODE (e) == COMPLEX_પદાવલિ))
    પાછા fold_convert_loc (loc, type, પદાવલિ);
  જો (વૃક્ષ_CODE (વૃક્ષ_TYPE (પદાવલિ)) == ERROR_MARK)
    પાછા error_mark_ગાંઠ;
  જો (VOID_TYPE_P (વૃક્ષ_TYPE (પદાવલિ)))
    {
      error ("void value not ignored as it ought to be");
      પાછા error_mark_ગાંઠ;
    }

  {
    વૃક્ષ false_કિંમત, true_કિંમત;
    જો (c_hardbool_type_attr (type, &false_કિંમત, &true_કિંમત))
      {
	તાર્કિક save = in_late_દ્વિઅંકી_op;
	in_late_દ્વિઅંકી_op = સાચું;
	પદાવલિ = c_objc_common_truthvalue_conversion (આગત_location, પદાવલિ);
	in_late_દ્વિઅંકી_op = save;

	પાછા fold_build3_loc (loc, COND_પદાવલિ, type,
				પદાવલિ, true_કિંમત, false_કિંમત);
      }
  }

  પસંદગી (code)
    {
    સ્થિતિ VOID_TYPE:
      પાછા fold_convert_loc (loc, type, e);

    સ્થિતિ ENUMERAL_TYPE:
      જો (ENUM_UNDERLYING_TYPE (type) != NULL_વૃક્ષ
	  && વૃક્ષ_CODE (ENUM_UNDERLYING_TYPE (type)) == BOOLEAN_TYPE)
	જાઓ convert_to_boolean;
      gcc_fallthrough ();

    સ્થિતિ INTEGER_TYPE:
    સ્થિતિ BITINT_TYPE:
      જો (sanitize_flags_p (SANITIZE_FLOAT_CAST)
	  && current_function_decl != NULL_વૃક્ષ
	  && SCALAR_FLOAT_TYPE_P (વૃક્ષ_TYPE (પદાવલિ))
	  && COMPLETE_TYPE_P (type))
	{
	  પદાવલિ = save_પદાવલિ (પદાવલિ);
	  પદાવલિ = c_fully_fold (પદાવલિ, init_const, ખાલી);
	  વૃક્ષ check = ubsan_instrument_float_cast (loc, type, પદાવલિ);
	  પદાવલિ = fold_build1 (FIX_TRUNC_પદાવલિ, type, પદાવલિ);
	  જો (check == NULL_વૃક્ષ)
	    પાછા પદાવલિ;
	  પાછા fold_build2 (COMPOUND_પદાવલિ, વૃક્ષ_TYPE (પદાવલિ), check, પદાવલિ);
	}
      ret = convert_to_integer (type, e);
      જાઓ maybe_fold;

    સ્થિતિ BOOLEAN_TYPE:
    convert_to_boolean:
      પાછા c_objc_common_truthvalue_conversion (આગત_location, પદાવલિ, type);

    સ્થિતિ POINTER_TYPE:
      /* The type nullptr_t may be converted to a pointer type.  The result is
	 a null pointer value.  */
      જો (NULLPTR_TYPE_P (વૃક્ષ_TYPE (e)))
	{
	  /* To make sure that (void *)nullptr is not a null pointer constant,
	     build_c_cast will create an additional NOP_EXPR around the result
	     of this conversion.  */
	  જો (વૃક્ષ_SIDE_EFFECTS (e))
	    ret = build2 (COMPOUND_પદાવલિ, type, e, build_int_cst (type, 0));
	  નહીંતર
	    ret = build_int_cst (type, 0);
	  જાઓ maybe_fold;
	}
      gcc_fallthrough ();
    સ્થિતિ REFERENCE_TYPE:
      ret = convert_to_pointer (type, e);
      જાઓ maybe_fold;

    સ્થિતિ NULLPTR_TYPE:
      /* A null pointer constant or value of type nullptr_t may be
	 converted to nullptr_t.  The latter case has already been
	 handled.  build_c_cast will create an additional NOP_EXPR to
	 ensure the result of the conversion is not itself a null
	 pointer constant.  */
      જો (null_pointer_constant_p (પદાવલિ))
	{
	  ret = build_int_cst (type, 0);
	  જાઓ maybe_fold;
	}
      તોડો;

    સ્થિતિ REAL_TYPE:
      ret = convert_to_real (type, e);
      જાઓ maybe_fold;

    સ્થિતિ FIXED_POINT_TYPE:
      ret = convert_to_fixed (type, e);
      જાઓ maybe_fold;

    સ્થિતિ COMPLEX_TYPE:
      ret = convert_to_complex (type, e);
      જાઓ maybe_fold;

    સ્થિતિ VECTOR_TYPE:
      જો (gnu_vector_type_p (type)
	  || gnu_vector_type_p (વૃક્ષ_TYPE (e))
	  /* Allow conversions between compatible non-GNU vector types
	     when -flax-vector-conversions is passed.  The whole purpose
	     of the option is to bend the normal type rules and accept
	     nonconforming code.  */
	  || (flag_lax_vector_conversions
	      && VECTOR_TYPE_P (વૃક્ષ_TYPE (e))
	      && vector_types_convertible_p (type, વૃક્ષ_TYPE (e), ખોટું)))
	{
	  ret = convert_to_vector (type, e);
	  જાઓ maybe_fold;
	}
      તોડો;

    સ્થિતિ RECORD_TYPE:
    સ્થિતિ UNION_TYPE:
      જો (lang_hooks.types_compatible_p (type, વૃક્ષ_TYPE (પદાવલિ)))
	પાછા e;
      તોડો;

    મૂળભૂત:
      તોડો;

    maybe_fold:
      જો (વૃક્ષ_CODE (ret) != C_MAYBE_CONST_પદાવલિ)
	ret = init_const ? fold_init (ret) : fold (ret);
      પાછા ret;
    }

  /* If we are converting to nullptr_t, don't say "non-scalar type" because
     the nullptr_t type is a scalar type.  Only nullptr_t or a null pointer
     constant shall be converted to nullptr_t.  */
  જો (code == NULLPTR_TYPE)
    {
      error ("conversion from %qT to %qT", વૃક્ષ_TYPE (e), type);
      inform (આગત_location,
	      "only %qT or a null pointer constant can be converted to %qT",
	      type, type);
    }
  નહીંતર
    error ("conversion to non-scalar type requested");
  પાછા error_mark_ગાંઠ;
}

/* Create an expression whose value is that of EXPR, converted to type TYPE.
   The TREE_TYPE of the value is always TYPE.  This function implements all
   reasonable conversions; callers should filter out those that are not
   permitted by the language being compiled.  */

વૃક્ષ
convert (વૃક્ષ type, વૃક્ષ પદાવલિ)
{
  પાછા c_convert (type, પદાવલિ, ખોટું);
}

/* Create an expression whose value is that of EXPR, converted to type TYPE, in
   a static initializer.  The TREE_TYPE of the value is always TYPE.  This
   function implements all reasonable conversions; callers should filter out
   those that are not permitted by the language being compiled.  */

વૃક્ષ
convert_init (વૃક્ષ type, વૃક્ષ પદાવલિ)
{
  પાછા c_convert (type, પદાવલિ, સાચું);
}
