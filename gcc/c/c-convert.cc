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

#அந்தர்பாவ "config.h"
#அந்தர்பாவ "system.h"
#அந்தர்பாவ "coretypes.h"
#அந்தர்பாவ "target.h"
#அந்தர்பாவ "c-tree.h"
#அந்தர்பாவ "convert.h"
#அந்தர்பாவ "langhooks.h"
#அந்தர்பாவ "ubsan.h"
#அந்தர்பாவ "stringpool.h"
#அந்தர்பாவ "attribs.h"
#அந்தர்பாவ "asan.h"

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

நிலையான மரம்
c_convert (மரம் type, மரம் கோவை, தருக்க init_const)
{
  மரம் e = கோவை;
  எண்ணிக்கை மரம்_code code = மரம்_CODE (type);
  மாறிலி எழுத்து *invalid_conv_diag;
  மரம் ret;
  location_t loc = கோவை_LOCATION (கோவை);

  எனில் (type == error_mark_முனை
      || error_operand_p (கோவை))
    திரும்பு error_mark_முனை;

  எனில் ((invalid_conv_diag
       = targetm.invalid_conversion (மரம்_TYPE (கோவை), type)))
    {
      error (invalid_conv_diag);
      திரும்பு error_mark_முனை;
    }

  எனில் (type == மரம்_TYPE (கோவை))
    திரும்பு கோவை;
  ret = targetm.convert_to_type (type, கோவை);
  எனில் (ret)
      திரும்பு ret;

  STRIP_TYPE_NOPS (e);

  எனில் (TYPE_MAIN_VARIANT (type) == TYPE_MAIN_VARIANT (மரம்_TYPE (கோவை))
      && (மரம்_CODE (மரம்_TYPE (கோவை)) != COMPLEX_TYPE
	  || மரம்_CODE (e) == COMPLEX_கோவை))
    திரும்பு fold_convert_loc (loc, type, கோவை);
  எனில் (மரம்_CODE (மரம்_TYPE (கோவை)) == ERROR_MARK)
    திரும்பு error_mark_முனை;
  எனில் (VOID_TYPE_P (மரம்_TYPE (கோவை)))
    {
      error ("void value not ignored as it ought to be");
      திரும்பு error_mark_முனை;
    }

  {
    மரம் false_மதிப்பு, true_மதிப்பு;
    எனில் (c_hardbool_type_attr (type, &false_மதிப்பு, &true_மதிப்பு))
      {
	தருக்க save = in_late_இருமம்_op;
	in_late_இருமம்_op = உண்மை;
	கோவை = c_objc_common_truthvalue_conversion (உள்ளீடு_location, கோவை);
	in_late_இருமம்_op = save;

	திரும்பு fold_build3_loc (loc, COND_கோவை, type,
				கோவை, true_மதிப்பு, false_மதிப்பு);
      }
  }

  தேர்வு (code)
    {
    நிலை VOID_TYPE:
      திரும்பு fold_convert_loc (loc, type, e);

    நிலை ENUMERAL_TYPE:
      எனில் (ENUM_UNDERLYING_TYPE (type) != NULL_மரம்
	  && மரம்_CODE (ENUM_UNDERLYING_TYPE (type)) == BOOLEAN_TYPE)
	செல் convert_to_boolean;
      gcc_fallthrough ();

    நிலை INTEGER_TYPE:
    நிலை BITINT_TYPE:
      எனில் (sanitize_flags_p (SANITIZE_FLOAT_CAST)
	  && current_function_decl != NULL_மரம்
	  && SCALAR_FLOAT_TYPE_P (மரம்_TYPE (கோவை))
	  && COMPLETE_TYPE_P (type))
	{
	  கோவை = save_கோவை (கோவை);
	  கோவை = c_fully_fold (கோவை, init_const, வெற்று);
	  மரம் check = ubsan_instrument_float_cast (loc, type, கோவை);
	  கோவை = fold_build1 (FIX_TRUNC_கோவை, type, கோவை);
	  எனில் (check == NULL_மரம்)
	    திரும்பு கோவை;
	  திரும்பு fold_build2 (COMPOUND_கோவை, மரம்_TYPE (கோவை), check, கோவை);
	}
      ret = convert_to_integer (type, e);
      செல் maybe_fold;

    நிலை BOOLEAN_TYPE:
    convert_to_boolean:
      திரும்பு c_objc_common_truthvalue_conversion (உள்ளீடு_location, கோவை, type);

    நிலை POINTER_TYPE:
      /* The type nullptr_t may be converted to a pointer type.  The result is
	 a null pointer value.  */
      எனில் (NULLPTR_TYPE_P (மரம்_TYPE (e)))
	{
	  /* To make sure that (void *)nullptr is not a null pointer constant,
	     build_c_cast will create an additional NOP_EXPR around the result
	     of this conversion.  */
	  எனில் (மரம்_SIDE_EFFECTS (e))
	    ret = build2 (COMPOUND_கோவை, type, e, build_int_cst (type, 0));
	  இல்லையெனில்
	    ret = build_int_cst (type, 0);
	  செல் maybe_fold;
	}
      gcc_fallthrough ();
    நிலை REFERENCE_TYPE:
      ret = convert_to_pointer (type, e);
      செல் maybe_fold;

    நிலை NULLPTR_TYPE:
      /* A null pointer constant or value of type nullptr_t may be
	 converted to nullptr_t.  The latter case has already been
	 handled.  build_c_cast will create an additional NOP_EXPR to
	 ensure the result of the conversion is not itself a null
	 pointer constant.  */
      எனில் (null_pointer_constant_p (கோவை))
	{
	  ret = build_int_cst (type, 0);
	  செல் maybe_fold;
	}
      நிறுத்து;

    நிலை REAL_TYPE:
      ret = convert_to_real (type, e);
      செல் maybe_fold;

    நிலை FIXED_POINT_TYPE:
      ret = convert_to_fixed (type, e);
      செல் maybe_fold;

    நிலை COMPLEX_TYPE:
      ret = convert_to_complex (type, e);
      செல் maybe_fold;

    நிலை VECTOR_TYPE:
      எனில் (gnu_vector_type_p (type)
	  || gnu_vector_type_p (மரம்_TYPE (e))
	  /* Allow conversions between compatible non-GNU vector types
	     when -flax-vector-conversions is passed.  The whole purpose
	     of the option is to bend the normal type rules and accept
	     nonconforming code.  */
	  || (flag_lax_vector_conversions
	      && VECTOR_TYPE_P (மரம்_TYPE (e))
	      && vector_types_convertible_p (type, மரம்_TYPE (e), பொய்)))
	{
	  ret = convert_to_vector (type, e);
	  செல் maybe_fold;
	}
      நிறுத்து;

    நிலை RECORD_TYPE:
    நிலை UNION_TYPE:
      எனில் (lang_hooks.types_compatible_p (type, மரம்_TYPE (கோவை)))
	திரும்பு e;
      நிறுத்து;

    இயல்பு:
      நிறுத்து;

    maybe_fold:
      எனில் (மரம்_CODE (ret) != C_MAYBE_CONST_கோவை)
	ret = init_const ? fold_init (ret) : fold (ret);
      திரும்பு ret;
    }

  /* If we are converting to nullptr_t, don't say "non-scalar type" because
     the nullptr_t type is a scalar type.  Only nullptr_t or a null pointer
     constant shall be converted to nullptr_t.  */
  எனில் (code == NULLPTR_TYPE)
    {
      error ("conversion from %qT to %qT", மரம்_TYPE (e), type);
      inform (உள்ளீடு_location,
	      "only %qT or a null pointer constant can be converted to %qT",
	      type, type);
    }
  இல்லையெனில்
    error ("conversion to non-scalar type requested");
  திரும்பு error_mark_முனை;
}

/* Create an expression whose value is that of EXPR, converted to type TYPE.
   The TREE_TYPE of the value is always TYPE.  This function implements all
   reasonable conversions; callers should filter out those that are not
   permitted by the language being compiled.  */

மரம்
convert (மரம் type, மரம் கோவை)
{
  திரும்பு c_convert (type, கோவை, பொய்);
}

/* Create an expression whose value is that of EXPR, converted to type TYPE, in
   a static initializer.  The TREE_TYPE of the value is always TYPE.  This
   function implements all reasonable conversions; callers should filter out
   those that are not permitted by the language being compiled.  */

மரம்
convert_init (மரம் type, மரம் கோவை)
{
  திரும்பு c_convert (type, கோவை, உண்மை);
}
