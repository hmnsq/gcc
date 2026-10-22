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

#ضمن "config.h"
#ضمن "system.h"
#ضمن "coretypes.h"
#ضمن "target.h"
#ضمن "c-tree.h"
#ضمن "convert.h"
#ضمن "langhooks.h"
#ضمن "ubsan.h"
#ضمن "stringpool.h"
#ضمن "attribs.h"
#ضمن "asan.h"

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

ساكن درخت
c_convert (درخت type, درخت عبارت, منطقي init_const)
{
  درخت e = عبارت;
  تعداد درخت_کد_2 کد = درخت_کد (type);
  ثابت حرف *invalid_conv_diag;
  درخت ret;
  location_t loc = عبارت_LOCATION (عبارت);

  إذا (type == error_mark_گره
      || error_عملوند_p (عبارت))
    أرجع error_mark_گره;

  إذا ((invalid_conv_diag
       = targetm.invalid_conversion (درخت_TYPE (عبارت), type)))
    {
      error (invalid_conv_diag);
      أرجع error_mark_گره;
    }

  إذا (type == درخت_TYPE (عبارت))
    أرجع عبارت;
  ret = targetm.convert_مقصد_type (type, عبارت);
  إذا (ret)
      أرجع ret;

  STRIP_TYPE_NOPS (e);

  إذا (TYPE_MAIN_VARIANT (type) == TYPE_MAIN_VARIANT (درخت_TYPE (عبارت))
      && (درخت_کد (درخت_TYPE (عبارت)) != COMPLEX_TYPE
	  || درخت_کد (e) == COMPLEX_عبارت))
    أرجع fold_convert_loc (loc, type, عبارت);
  إذا (درخت_کد (درخت_TYPE (عبارت)) == ERROR_MARK)
    أرجع error_mark_گره;
  إذا (VOID_TYPE_P (درخت_TYPE (عبارت)))
    {
      error ("void value not ignored as it ought to be");
      أرجع error_mark_گره;
    }

  {
    درخت false_مقدار, true_مقدار;
    إذا (c_hardbool_type_attr (type, &false_مقدار, &true_مقدار))
      {
	منطقي save = درون_late_دودویی_op;
	درون_late_دودویی_op = درست;
	عبارت = c_objc_common_truthvalue_conversion (درون_داد_location, عبارت);
	درون_late_دودویی_op = save;

	أرجع fold_build3_loc (loc, COND_عبارت, type,
				عبارت, true_مقدار, false_مقدار);
      }
  }

  بدل (کد)
    {
    حالة VOID_TYPE:
      أرجع fold_convert_loc (loc, type, e);

    حالة ENUMERAL_TYPE:
      إذا (ENUM_UNDERLYING_TYPE (type) != NULL_درخت
	  && درخت_کد (ENUM_UNDERLYING_TYPE (type)) == BOOLEAN_TYPE)
	اذهب convert_مقصد_boolean;
      gcc_fallthrough ();

    حالة INTEGER_TYPE:
    حالة BITINT_TYPE:
      إذا (sanitize_flags_p (SANITIZE_FLOAT_CAST)
	  && current_function_decl != NULL_درخت
	  && SCALAR_FLOAT_TYPE_P (درخت_TYPE (عبارت))
	  && COMPLETE_TYPE_P (type))
	{
	  عبارت = save_عبارت (عبارت);
	  عبارت = c_fully_fold (عبارت, init_const, عدم);
	  درخت check = ubsan_instrument_float_cast (loc, type, عبارت);
	  عبارت = fold_build1 (FIX_TRUNC_عبارت, type, عبارت);
	  إذا (check == NULL_درخت)
	    أرجع عبارت;
	  أرجع fold_build2 (COMPOUND_عبارت, درخت_TYPE (عبارت), check, عبارت);
	}
      ret = convert_مقصد_integer (type, e);
      اذهب maybe_fold;

    حالة BOOLEAN_TYPE:
    convert_مقصد_boolean:
      أرجع c_objc_common_truthvalue_conversion (درون_داد_location, عبارت, type);

    حالة اشاره_گر_TYPE:
      /* The type nullptr_t may be converted to a pointer type.  The result is
	 a null pointer value.  */
      إذا (NULLPTR_TYPE_P (درخت_TYPE (e)))
	{
	  /* To make sure that (void *)nullptr is not a null pointer constant,
	     build_c_cast will create an additional NOP_EXPR around the result
	     of this conversion.  */
	  إذا (درخت_SIDE_EFFECTS (e))
	    ret = build2 (COMPOUND_عبارت, type, e, build_int_cst (type, 0));
	  وإلا
	    ret = build_int_cst (type, 0);
	  اذهب maybe_fold;
	}
      gcc_fallthrough ();
    حالة REFERENCE_TYPE:
      ret = convert_مقصد_اشاره_گر (type, e);
      اذهب maybe_fold;

    حالة NULLPTR_TYPE:
      /* A null pointer constant or value of type nullptr_t may be
	 converted to nullptr_t.  The latter case has already been
	 handled.  build_c_cast will create an additional NOP_EXPR to
	 ensure the result of the conversion is not itself a null
	 pointer constant.  */
      إذا (null_اشاره_گر_constant_p (عبارت))
	{
	  ret = build_int_cst (type, 0);
	  اذهب maybe_fold;
	}
      اكسر;

    حالة REAL_TYPE:
      ret = convert_مقصد_real (type, e);
      اذهب maybe_fold;

    حالة FIXED_نقطه_TYPE:
      ret = convert_مقصد_fixed (type, e);
      اذهب maybe_fold;

    حالة COMPLEX_TYPE:
      ret = convert_مقصد_complex (type, e);
      اذهب maybe_fold;

    حالة وکتور_TYPE:
      إذا (gnu_وکتور_type_p (type)
	  || gnu_وکتور_type_p (درخت_TYPE (e))
	  /* Allow conversions between compatible non-GNU vector types
	     when -flax-vector-conversions is passed.  The whole purpose
	     of the option is to bend the normal type rules and accept
	     nonconforming code.  */
	  || (flag_lax_وکتور_conversions
	      && وکتور_TYPE_P (درخت_TYPE (e))
	      && وکتور_types_convertible_p (type, درخت_TYPE (e), خطأ)))
	{
	  ret = convert_مقصد_وکتور (type, e);
	  اذهب maybe_fold;
	}
      اكسر;

    حالة رکورد_TYPE:
    حالة UNION_TYPE:
      إذا (lang_hooks.types_compatible_p (type, درخت_TYPE (عبارت)))
	أرجع e;
      اكسر;

    افتراضي:
      اكسر;

    maybe_fold:
      إذا (درخت_کد (ret) != C_MAYBE_CONST_عبارت)
	ret = init_const ? fold_init (ret) : fold (ret);
      أرجع ret;
    }

  /* If we are converting to nullptr_t, don't say "non-scalar type" because
     the nullptr_t type is a scalar type.  Only nullptr_t or a null pointer
     constant shall be converted to nullptr_t.  */
  إذا (کد == NULLPTR_TYPE)
    {
      error ("conversion from %qT to %qT", درخت_TYPE (e), type);
      inform (درون_داد_location,
	      "only %qT or a null pointer constant can be converted to %qT",
	      type, type);
    }
  وإلا
    error ("conversion to non-scalar type requested");
  أرجع error_mark_گره;
}

/* Create an expression whose value is that of EXPR, converted to type TYPE.
   The TREE_TYPE of the value is always TYPE.  This function implements all
   reasonable conversions; callers should filter out those that are not
   permitted by the language being compiled.  */

درخت
convert (درخت type, درخت عبارت)
{
  أرجع c_convert (type, عبارت, خطأ);
}

/* Create an expression whose value is that of EXPR, converted to type TYPE, in
   a static initializer.  The TREE_TYPE of the value is always TYPE.  This
   function implements all reasonable conversions; callers should filter out
   those that are not permitted by the language being compiled.  */

درخت
convert_init (درخت type, درخت عبارت)
{
  أرجع c_convert (type, عبارت, درست);
}
