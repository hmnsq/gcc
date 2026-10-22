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

#అన్తర్భావ "config.h"
#అన్తర్భావ "system.h"
#అన్తర్భావ "coretypes.h"
#అన్తర్భావ "target.h"
#అన్తర్భావ "c-tree.h"
#అన్తర్భావ "convert.h"
#అన్తర్భావ "langhooks.h"
#అన్తర్భావ "ubsan.h"
#అన్తర్భావ "stringpool.h"
#అన్తర్భావ "attribs.h"
#అన్తర్భావ "asan.h"

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

స్థిర వృక్షం
c_convert (వృక్షం type, వృక్షం సమాసం, తార్కిక init_const)
{
  వృక్షం e = సమాసం;
  గణన వృక్షం_సంకేతం_2 సంకేతం_2 = వృక్షం_సంకేతం (type);
  స్థిరరాశి అక్షరం *invalid_conv_diag;
  వృక్షం ret;
  location_t loc = సమాసం_LOCATION (సమాసం);

  ఒకవేళ (type == error_mark_కణుపు
      || error_నిర్వాహ్యం_p (సమాసం))
    తిరిగి error_mark_కణుపు;

  ఒకవేళ ((invalid_conv_diag
       = targetm.invalid_conversion (వృక్షం_TYPE (సమాసం), type)))
    {
      error (invalid_conv_diag);
      తిరిగి error_mark_కణుపు;
    }

  ఒకవేళ (type == వృక్షం_TYPE (సమాసం))
    తిరిగి సమాసం;
  ret = targetm.convert_గమ్యం_type (type, సమాసం);
  ఒకవేళ (ret)
      తిరిగి ret;

  STRIP_TYPE_NOPS (e);

  ఒకవేళ (TYPE_MAIN_VARIANT (type) == TYPE_MAIN_VARIANT (వృక్షం_TYPE (సమాసం))
      && (వృక్షం_సంకేతం (వృక్షం_TYPE (సమాసం)) != COMPLEX_TYPE
	  || వృక్షం_సంకేతం (e) == COMPLEX_సమాసం))
    తిరిగి fold_convert_loc (loc, type, సమాసం);
  ఒకవేళ (వృక్షం_సంకేతం (వృక్షం_TYPE (సమాసం)) == ERROR_MARK)
    తిరిగి error_mark_కణుపు;
  ఒకవేళ (VOID_TYPE_P (వృక్షం_TYPE (సమాసం)))
    {
      error ("void value not ignored as it ought to be");
      తిరిగి error_mark_కణుపు;
    }

  {
    వృక్షం false_విలువ, true_విలువ;
    ఒకవేళ (c_hardbool_type_attr (type, &false_విలువ, &true_విలువ))
      {
	తార్కిక save = లోపల_late_ద్విమాన_op;
	లోపల_late_ద్విమాన_op = నిజం;
	సమాసం = c_objc_common_truthvalue_conversion (ఆదానం_location, సమాసం);
	లోపల_late_ద్విమాన_op = save;

	తిరిగి fold_build3_loc (loc, COND_సమాసం, type,
				సమాసం, true_విలువ, false_విలువ);
      }
  }

  ఎంపిక (సంకేతం_2)
    {
    స్థితి VOID_TYPE:
      తిరిగి fold_convert_loc (loc, type, e);

    స్థితి ENUMERAL_TYPE:
      ఒకవేళ (ENUM_UNDERLYING_TYPE (type) != NULL_వృక్షం
	  && వృక్షం_సంకేతం (ENUM_UNDERLYING_TYPE (type)) == BOOLEAN_TYPE)
	వెళ్ళు convert_గమ్యం_boolean;
      gcc_fallthrough ();

    స్థితి INTEGER_TYPE:
    స్థితి BITINT_TYPE:
      ఒకవేళ (sanitize_flags_p (SANITIZE_FLOAT_CAST)
	  && current_function_decl != NULL_వృక్షం
	  && SCALAR_FLOAT_TYPE_P (వృక్షం_TYPE (సమాసం))
	  && COMPLETE_TYPE_P (type))
	{
	  సమాసం = save_సమాసం (సమాసం);
	  సమాసం = c_fully_fold (సమాసం, init_const, ఖాళీ);
	  వృక్షం check = ubsan_instrument_float_cast (loc, type, సమాసం);
	  సమాసం = fold_build1 (FIX_TRUNC_సమాసం, type, సమాసం);
	  ఒకవేళ (check == NULL_వృక్షం)
	    తిరిగి సమాసం;
	  తిరిగి fold_build2 (COMPOUND_సమాసం, వృక్షం_TYPE (సమాసం), check, సమాసం);
	}
      ret = convert_గమ్యం_integer (type, e);
      వెళ్ళు maybe_fold;

    స్థితి BOOLEAN_TYPE:
    convert_గమ్యం_boolean:
      తిరిగి c_objc_common_truthvalue_conversion (ఆదానం_location, సమాసం, type);

    స్థితి సూచిక_TYPE:
      /* The type nullptr_t may be converted to a pointer type.  The result is
	 a null pointer value.  */
      ఒకవేళ (NULLPTR_TYPE_P (వృక్షం_TYPE (e)))
	{
	  /* To make sure that (void *)nullptr is not a null pointer constant,
	     build_c_cast will create an additional NOP_EXPR around the result
	     of this conversion.  */
	  ఒకవేళ (వృక్షం_SIDE_EFFECTS (e))
	    ret = build2 (COMPOUND_సమాసం, type, e, build_int_cst (type, 0));
	  లేకపోతే
	    ret = build_int_cst (type, 0);
	  వెళ్ళు maybe_fold;
	}
      gcc_fallthrough ();
    స్థితి REFERENCE_TYPE:
      ret = convert_గమ్యం_సూచిక (type, e);
      వెళ్ళు maybe_fold;

    స్థితి NULLPTR_TYPE:
      /* A null pointer constant or value of type nullptr_t may be
	 converted to nullptr_t.  The latter case has already been
	 handled.  build_c_cast will create an additional NOP_EXPR to
	 ensure the result of the conversion is not itself a null
	 pointer constant.  */
      ఒకవేళ (null_సూచిక_constant_p (సమాసం))
	{
	  ret = build_int_cst (type, 0);
	  వెళ్ళు maybe_fold;
	}
      ఆపు;

    స్థితి REAL_TYPE:
      ret = convert_గమ్యం_real (type, e);
      వెళ్ళు maybe_fold;

    స్థితి FIXED_బిందువు_TYPE:
      ret = convert_గమ్యం_fixed (type, e);
      వెళ్ళు maybe_fold;

    స్థితి COMPLEX_TYPE:
      ret = convert_గమ్యం_complex (type, e);
      వెళ్ళు maybe_fold;

    స్థితి సదిశ_TYPE:
      ఒకవేళ (gnu_సదిశ_type_p (type)
	  || gnu_సదిశ_type_p (వృక్షం_TYPE (e))
	  /* Allow conversions between compatible non-GNU vector types
	     when -flax-vector-conversions is passed.  The whole purpose
	     of the option is to bend the normal type rules and accept
	     nonconforming code.  */
	  || (flag_lax_సదిశ_conversions
	      && సదిశ_TYPE_P (వృక్షం_TYPE (e))
	      && సదిశ_types_convertible_p (type, వృక్షం_TYPE (e), అబద్ధం)))
	{
	  ret = convert_గమ్యం_సదిశ (type, e);
	  వెళ్ళు maybe_fold;
	}
      ఆపు;

    స్థితి రికార్డు_TYPE:
    స్థితి UNION_TYPE:
      ఒకవేళ (lang_hooks.types_compatible_p (type, వృక్షం_TYPE (సమాసం)))
	తిరిగి e;
      ఆపు;

    అప్రమేయ:
      ఆపు;

    maybe_fold:
      ఒకవేళ (వృక్షం_సంకేతం (ret) != C_MAYBE_CONST_సమాసం)
	ret = init_const ? fold_init (ret) : fold (ret);
      తిరిగి ret;
    }

  /* If we are converting to nullptr_t, don't say "non-scalar type" because
     the nullptr_t type is a scalar type.  Only nullptr_t or a null pointer
     constant shall be converted to nullptr_t.  */
  ఒకవేళ (సంకేతం_2 == NULLPTR_TYPE)
    {
      error ("conversion from %qT to %qT", వృక్షం_TYPE (e), type);
      inform (ఆదానం_location,
	      "only %qT or a null pointer constant can be converted to %qT",
	      type, type);
    }
  లేకపోతే
    error ("conversion to non-scalar type requested");
  తిరిగి error_mark_కణుపు;
}

/* Create an expression whose value is that of EXPR, converted to type TYPE.
   The TREE_TYPE of the value is always TYPE.  This function implements all
   reasonable conversions; callers should filter out those that are not
   permitted by the language being compiled.  */

వృక్షం
convert (వృక్షం type, వృక్షం సమాసం)
{
  తిరిగి c_convert (type, సమాసం, అబద్ధం);
}

/* Create an expression whose value is that of EXPR, converted to type TYPE, in
   a static initializer.  The TREE_TYPE of the value is always TYPE.  This
   function implements all reasonable conversions; callers should filter out
   those that are not permitted by the language being compiled.  */

వృక్షం
convert_init (వృక్షం type, వృక్షం సమాసం)
{
  తిరిగి c_convert (type, సమాసం, నిజం);
}
