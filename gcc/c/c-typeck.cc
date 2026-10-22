/* Build expressions with type checking for C compiler.
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


/* This file is part of the C front end.
   It contains routines to build C expressions given their operands,
   including computing the types of the result, C-specific error checks,
   and some optimization.  */

#شامل "config.h"
#شامل "system.h"
#شامل "coretypes.h"
#شامل "memmodel.h"
#شامل "target.h"
#شامل "function.h"
#شامل "bitmap.h"
#شامل "c-tree.h"
#شامل "gimple-expr.h"
#شامل "predict.h"
#شامل "stor-layout.h"
#شامل "trans-mem.h"
#شامل "varasm.h"
#شامل "stmt.h"
#شامل "langhooks.h"
#شامل "c-lang.h"
#شامل "intl.h"
#شامل "tree-iterator.h"
#شامل "gimplify.h"
#شامل "tree-inline.h"
#شامل "omp-general.h"
#شامل "c-family/c-objc.h"
#شامل "c-family/c-ubsan.h"
#شامل "gomp-constants.h"
#شامل "spellcheck-tree.h"
#شامل "c-family/c-type-mismatch.h"
#شامل "stringpool.h"
#شامل "attribs.h"
#شامل "asan.h"
#شامل "realmpfr.h"
#شامل "tree-pretty-print-markup.h"
#شامل "gcc-urlifier.h"

/* Possible cases of implicit conversions.  Used to select diagnostic messages
   and control folding initializers in convert_for_assignment.  */
شمار impl_conv {
  ic_argpass,
  ic_تفویض,
  ic_init,
  ic_init_const,
  ic_return
};

/* The level of nesting inside "__alignof__".  */
صحیح اندر_alignof;

/* The level of nesting inside "sizeof".  */
صحیح اندر_sizeof;

/* The level of nesting inside "countof".  */
صحیح اندر_countof;

/* The level of nesting inside "typeof".  */
صحیح اندر_typeof;

/* The level of nesting inside "_Generic".  */
صحیح اندر_generic;

/* True when parsing OpenMP loop expressions.  */
منطقی c_اندر_omp_for;

/* True when parsing OpenMP map clause.  */
منطقی c_omp_array_section_p;

/* The argument of last parsed sizeof expression, only to be tested
   if expr.original_code == SIZEOF_EXPR.  */
درخت c_آخری_sizeof_arg;
location_t c_آخری_sizeof_loc;

/* Nonzero if we might need to print a "missing braces around
   initializer" message within this initializer.  */
ساکن صحیح ملا_missing_braces;

ساکن منطقی require_constant_قدر;
ساکن منطقی require_constant_elements;
ساکن منطقی require_constexpr_قدر;

ساکن درخت qualify_type (درخت, درخت);
ساخت comptypes_ڈیٹا;
ساکن منطقی tagged_types_tu_compatible_p (const_درخت, const_درخت,
					  ساخت comptypes_ڈیٹا *);
ساکن منطقی comp_ہدف_types (location_t, درخت, درخت);
ساکن منطقی function_types_compatible_p (const_درخت, const_درخت,
					 ساخت comptypes_ڈیٹا *);
ساکن منطقی type_lists_compatible_p (const_درخت, const_درخت,
				     ساخت comptypes_ڈیٹا *);
ساکن صحیح convert_arguments (location_t, vec<location_t>, درخت,
			      vec<درخت, va_gc> *, vec<درخت, va_gc> *, درخت,
			      درخت);
ساکن درخت اشارہ_گر_diff (location_t, درخت, درخت, درخت *);
ساکن درخت convert_for_assignment (location_t, location_t, درخت, درخت, درخت,
				    شمار impl_conv, منطقی, درخت, درخت, صحیح,
				    صحیح = 0);
ساکن درخت valid_compound_اظہاریہ_initializer (درخت, درخت);
ساکن خالی ڈالو_string (ثابت حرف *);
ساکن خالی ڈالو_member_name (درخت);
ساکن صحیح spelling_لمبائی (خالی);
ساکن حرف *print_spelling (حرف *);
ساکن خالی warning_init (location_t, صحیح, ثابت حرف *);
ساکن درخت digest_init (location_t, درخت, درخت, درخت, درخت, منطقی, منطقی, منطقی,
			 منطقی, منطقی, منطقی);
ساکن خالی output_init_element (location_t, درخت, درخت, منطقی, درخت, درخت, منطقی,
				 منطقی, ساخت obstack *);
ساکن خالی output_pending_init_elements (صحیح, ساخت obstack *);
ساکن منطقی سیٹ_designator (location_t, منطقی, ساخت obstack *);
ساکن خالی ڈالو_range_ڈھیر (درخت, ساخت obstack *);
ساکن خالی جوڑو_pending_init (location_t, درخت, درخت, درخت, منطقی,
			      ساخت obstack *);
ساکن خالی سیٹ_nonincremental_init (ساخت obstack *);
ساکن خالی سیٹ_nonincremental_init_from_string (درخت, ساخت obstack *);
ساکن درخت ڈھونڈو_init_member (درخت, ساخت obstack *);
ساکن خالی readonly_warning (درخت, شمار lvalue_use);
ساکن صحیح lvalue_or_else (location_t, const_درخت, شمار lvalue_use);
ساکن خالی ریکارڈ_maybe_مستعمل_decl (درخت, منطقی پتہ);
ساکن منطقی comptypes_اندرونی (const_درخت, const_درخت,
				ساخت comptypes_ڈیٹا *ڈیٹا);
ساکن منطقی comptypes_check_for_مرکب (درخت t1, درخت t2);
ساکن منطقی handle_counted_by_p (درخت);
ساکن منطقی چوٹی_array_vla_p (const_درخت type);


/* Return true if EXP is a null pointer constant, false otherwise.  */

منطقی
null_اشارہ_گر_constant_p (const_درخت اظہاریہ)
{
  /* This should really operate on c_expr structures, but they aren't
     yet available everywhere required.  */
  درخت type = درخت_TYPE (اظہاریہ);

  /* An integer constant expression with the value 0, such an expression
     cast to type void*, or the predefined constant nullptr, are a null
     pointer constant.  */
  اگر (اظہاریہ == nullptr_گرہ)
    واپس سچ;

  واپس (درخت_رمز (اظہاریہ) == INTEGER_CST
	  && !درخت_حد_سے_تجاوز (اظہاریہ)
	  && integer_zerop (اظہاریہ)
	  && (INTEGRAL_TYPE_P (type)
	      || (درخت_رمز (type) == اشارہ_گر_TYPE
		  && VOID_TYPE_P (درخت_TYPE (type))
		  && TYPE_QUALS (درخت_TYPE (type)) == TYPE_UNQUALIFIED)));
}

/* EXPR may appear in an unevaluated part of an integer constant
   expression, but not in an evaluated part.  Wrap it in a
   C_MAYBE_CONST_EXPR, or mark it with TREE_OVERFLOW if it is just an
   INTEGER_CST and we cannot create a C_MAYBE_CONST_EXPR.  */

ساکن درخت
note_integer_operands (درخت اظہاریہ)
{
  درخت ret;
  اگر (درخت_رمز (اظہاریہ) == INTEGER_CST && اندر_late_ثنائی_op)
    {
      ret = copy_گرہ (اظہاریہ);
      درخت_حد_سے_تجاوز (ret) = 1;
    }
  ورنہ
    {
      ret = build2 (C_MAYBE_CONST_اظہاریہ, درخت_TYPE (اظہاریہ), NULL_درخت, اظہاریہ);
      C_MAYBE_CONST_اظہاریہ_INT_OPERANDS (ret) = 1;
    }
  واپس ret;
}

/* Having checked whether EXPR may appear in an unevaluated part of an
   integer constant expression and found that it may, remove any
   C_MAYBE_CONST_EXPR noting this fact and return the resulting
   expression.  */

ساکن اندرونی درخت
remove_c_maybe_const_اظہاریہ (درخت اظہاریہ)
{
  اگر (درخت_رمز (اظہاریہ) == C_MAYBE_CONST_اظہاریہ)
    واپس C_MAYBE_CONST_اظہاریہ_اظہاریہ (اظہاریہ);
  ورنہ
    واپس اظہاریہ;
}

/* This is a cache to hold if two types are seen.  */

ساخت tagged_tu_نظر_آیا_cache {
  ثابت ساخت tagged_tu_نظر_آیا_cache * اگلا;
  const_درخت t1;
  const_درخت t2;
};

/* Do `exp = require_complete_type (loc, exp);' to make sure exp
   does not have an incomplete type.  (That includes void types.)
   LOC is the location of the use.  */

درخت
require_complete_type (location_t loc, درخت قدر)
{
  درخت type = درخت_TYPE (قدر);

  اگر (error_عملیہ_p (قدر))
    واپس error_mark_گرہ;

  /* First, detect a valid value with a complete type.  */
  اگر (COMPLETE_TYPE_P (type))
    واپس قدر;

  c_incomplete_type_error (loc, قدر, type);
  واپس error_mark_گرہ;
}

/* Print an error message for invalid use of an incomplete type.
   VALUE is the expression that was used (or 0 if that isn't known)
   and TYPE is the type that was invalid.  LOC is the location for
   the error.  */

خالی
c_incomplete_type_error (location_t loc, const_درخت قدر, const_درخت type)
{
  /* Avoid duplicate error message.  */
  اگر (درخت_رمز (type) == ERROR_MARK)
    واپس;

  اگر (قدر != NULL_درخت && (VAR_P (قدر) || درخت_رمز (قدر) == PARM_DECL))
    error_at (loc, "%qD has an incomplete type %qT", قدر, type);
  ورنہ
    {
    retry:
      /* We must print an error message.  Be clever about what it says.  */

      انتخاب (درخت_رمز (type))
	{
	حالت ریکارڈ_TYPE:
	حالت UNION_TYPE:
	حالت ENUMERAL_TYPE:
	  توڑو;

	حالت VOID_TYPE:
	  error_at (loc, "invalid use of void expression");
	  واپس;

	حالت ARRAY_TYPE:
	  اگر (TYPE_DOMAIN (type))
	    {
	      اگر (flexible_array_member_type_p (type))
		{
		  error_at (loc, "invalid use of flexible array member");
		  واپس;
		}
	      type = درخت_TYPE (type);
	      جاؤ retry;
	    }
	  error_at (loc, "invalid use of array with unspecified bounds");
	  واپس;

	طےشدہ:
	  gcc_unreachable ();
	}

      اگر (درخت_رمز (TYPE_NAME (type)) == IDENTIFIER_گرہ)
	error_at (loc, "invalid use of undefined type %qT", type);
      ورنہ
	/* If this type has a typedef-name, the TYPE_NAME is a TYPE_DECL.  */
	error_at (loc, "invalid use of incomplete typedef %qT", type);
    }
}

/* Given a type, apply default promotions wrt unnamed function
   arguments and return the new type.  */

درخت
c_type_promotes_مقصد (درخت type)
{
  درخت ret = NULL_درخت;

  اگر (TYPE_MAIN_VARIANT (type) == float_type_گرہ)
    ret = double_type_گرہ;
  ورنہ اگر (c_promoting_integer_type_p (type))
    {
      /* Preserve unsignedness if not really getting any wider.  */
      اگر (TYPE_UNSIGNED (type)
	  && (TYPE_PRECISION (type) == TYPE_PRECISION (integer_type_گرہ)))
	ret = unsigned_type_گرہ;
      ورنہ
	ret = integer_type_گرہ;
    }

  اگر (ret != NULL_درخت)
    واپس (TYPE_ATOMIC (type)
	    ? c_build_qualified_type (ret, TYPE_QUAL_ATOMIC)
	    : ret);

  واپس type;
}

/* Return true if between two named address spaces, whether there is a superset
   named address space that encompasses both address spaces.  If there is a
   superset, return which address space is the superset.  */

ساکن منطقی
addr_space_superset (addr_space_t as1, addr_space_t as2, addr_space_t *common)
{
  اگر (as1 == as2)
    {
      *common = as1;
      واپس سچ;
    }
  ورنہ اگر (targetm.addr_space.subset_p (as1, as2))
    {
      *common = as2;
      واپس سچ;
    }
  ورنہ اگر (targetm.addr_space.subset_p (as2, as1))
    {
      *common = as1;
      واپس سچ;
    }
  ورنہ
    واپس جھوٹ;
}

/* Return a variant of TYPE which has all the type qualifiers of LIKE
   as well as those of TYPE.  */

ساکن درخت
qualify_type (درخت type, درخت like)
{
  addr_space_t as_type = TYPE_ADDR_SPACE (type);
  addr_space_t as_like = TYPE_ADDR_SPACE (like);
  addr_space_t as_common;

  /* If the two named address spaces are different, determine the common
     superset address space.  If there isn't one, raise an error.  */
  اگر (!addr_space_superset (as_type, as_like, &as_common))
    {
      as_common = as_type;
      error ("%qT and %qT are in disjoint named address spaces",
	     type, like);
    }

  واپس c_build_qualified_type (type,
				 TYPE_QUALS_NO_ADDR_SPACE (type)
				 | TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (like)
				 | ENCODE_QUAL_ADDR_SPACE (as_common));
}


/* Check consistency of type TYPE.  For derived types, we test that
   C_TYPE_VARIABLE_SIZE and C_TYPE_VARIABLY_MODIFIED are consistent with
   the requirements of the base type.  We also check that arrays with a
   non-constant length are marked with C_TYPE_VARIABLE_SIZE. If any
   inconsistency is detected false is returned and true otherwise.  */

ساکن منطقی
c_verify_type (درخت type)
{
  انتخاب (درخت_رمز (type))
    {
    حالت اشارہ_گر_TYPE:
    حالت FUNCTION_TYPE:
    حالت ARRAY_TYPE:
      /* Pointer, array, functions are variably modified if and only if the
	 target, element, return type is variably modified.  */
      اگر (!TYPE_STRUCTURAL_EQUALITY_P (type)
	  && (C_TYPE_VARIABLY_MODIFIED (type)
	      != C_TYPE_VARIABLY_MODIFIED (درخت_TYPE (type))))
	واپس جھوٹ;
      /* If the target type is structural equality, the type should also. */
      اگر (!TYPE_STRUCTURAL_EQUALITY_P (type)
	  && TYPE_STRUCTURAL_EQUALITY_P (درخت_TYPE (type)))
	واپس جھوٹ;
    طےشدہ:
       توڑو;
    }

  انتخاب (درخت_رمز (type))
    {
    حالت اشارہ_گر_TYPE:
    حالت FUNCTION_TYPE:
      /* Pointer and functions can not have variable size.  */
      اگر (C_TYPE_VARIABLE_سائز (type))
	واپس جھوٹ;
      توڑو;
    حالت ARRAY_TYPE:
      /* An array has variable size if and only if it has a non-constant
	 dimensions or its element type has variable size.  */
      اگر ((C_TYPE_VARIABLE_سائز (درخت_TYPE (type))
	   || چوٹی_array_vla_p (type))
	  != C_TYPE_VARIABLE_سائز (type))
	واپس جھوٹ;
      /* If the element type or the array has variable size, then the
	 array has variable size and is variably modified.  */
      اگر (C_TYPE_VARIABLE_سائز (درخت_TYPE (type))
	  || C_TYPE_VARIABLE_سائز (type))
	{
	  اگر (!C_TYPE_VARIABLE_سائز (type))
	    واپس جھوٹ;
	  اگر (!C_TYPE_VARIABLY_MODIFIED (type))
	    واپس جھوٹ;
	}

      /* va_list violates this, accept such types here.  */
      اگر (!COMPLETE_TYPE_P (درخت_TYPE (type)))
	واپس سچ;

      اگر (COMPLETE_TYPE_P (type))
	{
	  /* If the size is unknown, it can not be complete.  */
	  اگر (NULL_درخت == TYPE_DOMAIN (type))
	    واپس جھوٹ;

	  /* Zero-length arrays must have size zero.  */
	  اگر (zero_لمبائی_array_type_p (type)
	      && !integer_zerop (TYPE_سائز (type)))
	    واپس جھوٹ;
	}
      ورنہ
	{
	  /* If not complete but has a domain, it must be a FAM.  */
	  اگر (NULL_درخت != TYPE_DOMAIN (type)
	      && !flexible_array_member_type_p (type))
	    واپس جھوٹ;
	}
    طےشدہ:
      توڑو;
    }
  واپس سچ;
}

/* Propagate C_TYPE_VARIABLY_MODIFIED and C_TYPE_VARIABLE_SIZE
   from a base type to a newly built derived or qualified type.  */

ساکن درخت
c_سیٹ_type_بٹ (درخت new_type, درخت old_type)
{
  gcc_checking_assert (c_verify_type (old_type));

  اگر (c_type_variably_modified_p (old_type))
    C_TYPE_VARIABLY_MODIFIED (new_type) = سچ;

  اگر (درخت_رمز (new_type) == ARRAY_TYPE && C_TYPE_VARIABLE_سائز (old_type))
    {
      C_TYPE_VARIABLY_MODIFIED (new_type) = سچ;
      C_TYPE_VARIABLE_سائز (new_type) = سچ;
    }
  واپس new_type;
}

/* Build a pointer type using the default pointer mode.  */

درخت
c_build_اشارہ_گر_type (درخت مقصد_type)
{
  addr_space_t as = مقصد_type == error_mark_گرہ ? ADDR_SPACE_GENERIC
					       : TYPE_ADDR_SPACE (مقصد_type);
  machine_منوال اشارہ_گر_منوال;

  اگر (as != ADDR_SPACE_GENERIC || c_default_اشارہ_گر_منوال == VOIDmode)
    اشارہ_گر_منوال = targetm.addr_space.اشارہ_گر_منوال (as);
  ورنہ
    اشارہ_گر_منوال = c_default_اشارہ_گر_منوال;

  واپس c_build_اشارہ_گر_type_for_منوال (مقصد_type, اشارہ_گر_منوال, جھوٹ);
}

/* Build a pointer type using the given mode.  */

درخت
c_build_اشارہ_گر_type_for_منوال (درخت type, machine_منوال منوال, منطقی m)
{
  درخت ret = build_اشارہ_گر_type_for_منوال (type, منوال, m);
  واپس c_سیٹ_type_بٹ (ret, type);
}

/* Build a function type.  */

درخت
c_build_function_type (درخت type, درخت دلائل, منطقی no)
{
  درخت ret = build_function_type (type, دلائل, no);
  واپس c_سیٹ_type_بٹ (ret, type);
}

/* Build an array type.  This sets typeless storage as required
   by C2Y and C_TYPE_VARIABLY_MODIFIED and C_TYPE_VARIABLE_SIZE
   based on the element type and domain.  */

درخت
c_build_array_type (درخت type, درخت domain)
{
  صحیح type_quals = TYPE_QUALS (type);

  /* Identify typeless storage as introduced in C2Y
     and supported also in earlier language modes.  */
  منطقی typeless = (char_type_p (type) && !(type_quals & TYPE_QUAL_ATOMIC))
		  || (AGGREGATE_TYPE_P (type) && TYPE_TYPELESS_STORAGE (type));

  درخت ret = build_array_type (type, domain, typeless);

  اگر (چوٹی_array_vla_p (ret))
    {
      C_TYPE_VARIABLE_سائز (ret) = 1;
      C_TYPE_VARIABLY_MODIFIED (ret) = 1;
    }

  واپس c_سیٹ_type_بٹ (ret, type);
}

/* Build an array type of unspecified size.  */
درخت
c_build_array_type_unspecified (درخت type)
{
  درخت بالائی = build2 (COMPOUND_اظہاریہ, درخت_TYPE (سائز_zero_گرہ),
		       integer_zero_گرہ, سائز_zero_گرہ);
  واپس c_build_array_type (type, build_اشاریہ_type (بالائی));
}

/* Build an array type of zero size.  */
درخت
c_build_array_type_zero_سائز (درخت type)
{
  /* The GCC extension for zero-length arrays differs from
     ISO flexible array members in that sizeof yields
     zero.  */
  type = c_build_array_type (type, build_اشاریہ_type (NULL_درخت));
  type = build_distinct_type_copy (TYPE_MAIN_VARIANT (type));
  TYPE_سائز (type) = bitsize_zero_گرہ;
  TYPE_سائز_UNIT (type) = سائز_zero_گرہ;
  سیٹ_TYPE_STRUCTURAL_EQUALITY (type);
  واپس type;
}

درخت
c_build_type_attribute_qual_variant (درخت type, درخت attrs, صحیح quals)
{
  درخت ret = build_type_attribute_qual_variant (type, attrs, quals);
  واپس c_سیٹ_type_بٹ (ret, type);
}

درخت
c_build_type_attribute_variant (درخت type, درخت attrs)
{
  واپس c_build_type_attribute_qual_variant (type, attrs, TYPE_QUALS (type));
}

/* Reconstruct a complex derived type.  This is used to re-construct types
   with the vector attribute.  It is called via a langhook.  */

درخت
c_reconstruct_complex_type (درخت type, درخت bottom)
{
  درخت inner, outer;

  اگر (درخت_رمز (type) == اشارہ_گر_TYPE)
    {
      inner = c_reconstruct_complex_type (درخت_TYPE (type), bottom);
      outer = c_build_اشارہ_گر_type_for_منوال (inner, TYPE_منوال (type),
					     TYPE_REF_CAN_ALIAS_ALL (type));
    }
  ورنہ اگر (درخت_رمز (type) == ARRAY_TYPE)
    {
      منطقی rso = TYPE_الٹ_STORAGE_ترتیب (type);
      inner = c_reconstruct_complex_type (درخت_TYPE (type), bottom);
      outer = c_build_array_type (inner, TYPE_DOMAIN (type));
      اگر (rso)
	{
	  outer = build_distinct_type_copy (outer);
	  TYPE_الٹ_STORAGE_ترتیب (outer) = 1;
	}

      gcc_checking_assert (C_TYPE_VARIABLE_سائز (type)
			   == C_TYPE_VARIABLE_سائز (outer));
    }
  ورنہ اگر (درخت_رمز (type) == FUNCTION_TYPE)
    {
      inner = c_reconstruct_complex_type (درخت_TYPE (type), bottom);
      outer = c_build_function_type (inner, TYPE_ARG_TYPES (type),
				     TYPE_NO_NAMED_دلائل_STDARG_P (type));
    }
  ورنہ اگر (درخت_رمز (type) == REFERENCE_TYPE
	   || درخت_رمز (type) == انحراف_TYPE)
    gcc_unreachable ();
  ورنہ
    واپس bottom;

  واپس c_build_type_attribute_qual_variant (outer, TYPE_اوصاف (type),
					      TYPE_QUALS (type));
}


/* Helper function for c_canonical_type.  Check whether FIELD
   contains a pointer to a structure or union with tag,
   possibly nested in other type derivations, and return the
   type of this nested structure or union.  */
ساکن درخت
ptr_مقصد_tagged_member (درخت میدان_2)
{
  gcc_assert (میدان_DECL == درخت_رمز (میدان_2));
  درخت type = درخت_TYPE (میدان_2);
  منطقی ptr_نظر_آیا = جھوٹ;
  جب (درخت_رمز (type) == ARRAY_TYPE
	 || درخت_رمز (type) == FUNCTION_TYPE
	 || درخت_رمز (type) == اشارہ_گر_TYPE)
    {
      اگر (درخت_رمز (type) == اشارہ_گر_TYPE)
	ptr_نظر_آیا = سچ;
      type = درخت_TYPE (type);
    }

  اگر (ptr_نظر_آیا
      && ریکارڈ_OR_UNION_TYPE_P (type)
      && NULL_درخت != c_type_لیبل (type))
    واپس type;

  واپس NULL_درخت;
}

/* For a record or union type, make necessary adaptations so that the
   type can be used as TYPE_CANONICAL.

   If the TYPE contains a pointer (possibly nested in other type
   derivations) to a structure or union as a member, create a copy and
   change the nested type to an incomplete type.  Otherwise, the middle-end
   gets confused when recording component aliases in the case where we
   have formed equivalency classes that include types for which these
   member pointers end up pointing to other structure or unions types
   which have the same tag but are not compatible.  */
درخت
c_type_canonical (درخت type)
{
  gcc_assert (ریکارڈ_OR_UNION_TYPE_P (type));

  منطقی needs_mod = جھوٹ;
  برائے (درخت x = TYPE_FIELDS (type); x; x = DECL_CHAIN (x))
    {
      اگر (!ptr_مقصد_tagged_member (x))
	جاری;
      needs_mod = سچ;
      توڑو;
    }
  اگر (!needs_mod)
    واپس type;

  /* Construct new version with such members replaced.  */
  درخت n = build_distinct_type_copy (type);
  درخت *fields = &TYPE_FIELDS (n);
  برائے (درخت x = TYPE_FIELDS (type); x; x = DECL_CHAIN (x))
    {
      درخت f = copy_گرہ (x);
      اگر (درخت m = ptr_مقصد_tagged_member (x))
	{
	  درخت new_گرہ = make_گرہ (درخت_رمز (m));
	  TYPE_NAME (new_گرہ) = TYPE_NAME (m);
	  سیٹ_TYPE_STRUCTURAL_EQUALITY (new_گرہ);
	  new_گرہ = qualify_type (new_گرہ, m);
	  درخت_TYPE (f) = c_reconstruct_complex_type (درخت_TYPE (x),
						      new_گرہ);
	}
      *fields = f;
      fields = &DECL_CHAIN (f);
    }
  TYPE_CANONICAL (n) = n;
  واپس n;
}


/* If NTYPE is a type of a non-variadic function with a prototype
   and OTYPE is a type of a function without a prototype and ATTRS
   contains attribute format, diagnosess and removes it from ATTRS.
   Returns the result of build_type_attribute_variant of NTYPE and
   the (possibly) modified ATTRS.  */

ساکن درخت
c_build_functype_attribute_variant (درخت ntype, درخت otype, درخت attrs)
{
  اگر (!prototype_p (otype)
      && prototype_p (ntype)
      && lookup_attribute ("format", attrs))
    {
      warning_at (داخلہ_location, OPT_Wattributes,
		  "%qs attribute can only be applied to variadic functions",
		  "format");
      attrs = remove_attribute ("format", attrs);
    }
  واپس c_build_type_attribute_variant (ntype, attrs);

}

/* Given a type which could be a typedef name, make sure to return the
   original type.  See set_underlying_type. */
ساکن const_درخت
c_type_original (const_درخت t)
{
  /* It may even be a typedef of a typedef...
     In the case of compiler-created builtin structs the TYPE_DECL
     may be a dummy, with no DECL_ORIGINAL_TYPE.  Don't fault.  */
  جب (TYPE_NAME (t)
	 && درخت_رمز (TYPE_NAME (t)) == TYPE_DECL
	 && DECL_ORIGINAL_TYPE (TYPE_NAME (t)))
    t = DECL_ORIGINAL_TYPE (TYPE_NAME (t));
  واپس t;
}

/* Return the tag for a tagged type.  */
درخت
c_type_لیبل (const_درخت t)
{
  gcc_assert (ریکارڈ_OR_UNION_TYPE_P (t) || درخت_رمز (t) == ENUMERAL_TYPE);
  const_درخت orig = c_type_original (t);
  درخت name = TYPE_NAME (orig);
  اگر (!name)
    واپس NULL_درخت;
  اگر (درخت_رمز (name) == TYPE_DECL)
    {
      اگر (!DECL_NAME (name))
	واپس NULL_درخت;
      name = DECL_NAME (name);
    }
  gcc_checking_assert (درخت_رمز (name) == IDENTIFIER_گرہ);
  واپس name;
}

/* Remove qualifiers but not atomic.  For arrays remove qualifiers
   on the element type but also do not remove atomic.  */
ساکن درخت
remove_qualifiers (درخت t)
{
  اگر (!t || t == error_mark_گرہ)
    واپس t;
  واپس TYPE_ATOMIC (strip_array_types (t))
	 ? c_build_qualified_type (TYPE_MAIN_VARIANT (t), TYPE_QUAL_ATOMIC)
	 : TYPE_MAIN_VARIANT (t);
}


/* Helper function for composite_type_internal.  Find a compatible type
   in a (transparent) union U compatible to T.  If found, return the
   type of the corresponding member.  Otherwise, return the union type U.  */
ساکن درخت
transparent_union_replacement (درخت u, درخت t)
{
  اگر (u == error_mark_گرہ || t == error_mark_گرہ
      || درخت_رمز (u) != UNION_TYPE
      || !(TYPE_TRANSPARENT_AGGR (u) || TYPE_NAME (u) == NULL_درخت)
      || comptypes (u, t))
    واپس u;

  برائے (درخت memb = TYPE_FIELDS (u); memb; memb = DECL_CHAIN (memb))
    {
      درخت m = remove_qualifiers (درخت_TYPE (memb));
      اگر (comptypes (m, t))
	{
	  pedwarn (داخلہ_location, OPT_Wpedantic,
		    "function types not truly compatible in ISO C");
	  واپس m;
	}
    }

  واپس u;
}



/* Return the composite type of two compatible types.

   We assume that comptypes has already been done and returned
   nonzero; if that isn't so, this may crash.  In particular, we
   assume that qualifiers match.  */

ساخت مرکب_cache {
  درخت t1;
  درخت t2;
  درخت مرکب;
  ساخت مرکب_cache* اگلا;
};

درخت
مرکب_type_اندرونی (درخت t1, درخت t2, درخت cond,
			 ساخت مرکب_cache* cache)
{
  شمار درخت_رمز_2 code1;
  شمار درخت_رمز_2 code2;
  درخت اوصاف;

  /* Save time if the two types are the same.  */

  اگر (t1 == t2) واپس t1;

  /* If one type is nonsense, use the other.  */
  اگر (t1 == error_mark_گرہ)
    واپس t2;
  اگر (t2 == error_mark_گرہ)
    واپس t1;

  code1 = درخت_رمز (t1);
  code2 = درخت_رمز (t2);

  /* Merge the attributes.  */
  اوصاف = targetm.ملاؤ_type_اوصاف (t1, t2);

  /* If one is an enumerated type and the other is the compatible
     integer type, the composite type might be either of the two
     (DR#013 question 3).  For consistency, use the enumerated type as
     the composite type.  */

  اگر (code1 == ENUMERAL_TYPE
      && (code2 == INTEGER_TYPE
	  || code2 == BOOLEAN_TYPE))
    واپس t1;
  اگر (code2 == ENUMERAL_TYPE
      && (code1 == INTEGER_TYPE
	  || code1 == BOOLEAN_TYPE))
    واپس t2;

  gcc_assert (code1 == code2);

  انتخاب (code1)
    {
    حالت اشارہ_گر_TYPE:
      /* For two pointers, do this recursively on the target type.  */
      {
	gcc_checking_assert (TYPE_QUALS (t1) == TYPE_QUALS (t2));
	درخت ہدف = مرکب_type_اندرونی (درخت_TYPE (t1), درخت_TYPE (t2),
					       cond, cache);
	درخت n = c_build_اشارہ_گر_type_for_منوال (ہدف, TYPE_منوال (t1), جھوٹ);
	واپس c_build_type_attribute_qual_variant (n, اوصاف,
						    TYPE_QUALS (t2));
      }

    حالت ARRAY_TYPE:
      {
	درخت d1 = TYPE_DOMAIN (t1);
	درخت d2 = TYPE_DOMAIN (t2);

	/* We should not have any type quals on arrays at all.  */
	gcc_assert (!TYPE_QUALS_NO_ADDR_SPACE (t1)
		    && !TYPE_QUALS_NO_ADDR_SPACE (t2));

	منطقی d1_zero = zero_لمبائی_array_type_p (t1)
		       || flexible_array_member_type_p (t1);
	منطقی d2_zero = zero_لمبائی_array_type_p (t2)
		       || flexible_array_member_type_p (t2);

	منطقی d1_variable = چوٹی_array_vla_p (t1);
	منطقی d2_variable = چوٹی_array_vla_p (t2);

	منطقی use1 = d1 && (d2_variable || !d2 || d2_zero || !d1_variable);
	منطقی use2 = d2 && (d1_variable || !d1 || d1_zero || !d2_variable);

	/* If the first is an unspecified size pick the other one.  */
	اگر (d2_variable && c_type_unspecified_p (t1))
	  {
	    gcc_assert (use1 && use2);
	    use1 = جھوٹ;
	  }

	/* If both are VLAs but not unspecified and we are in the
	   conditional operator, we create a conditional to select
	   the size of the active branch.  */
	منطقی use0 = cond && d1_variable && !c_type_unspecified_p (t1)
			 && d2_variable && !c_type_unspecified_p (t2);

	درخت td;
	درخت elt = مرکب_type_اندرونی (درخت_TYPE (t1), درخت_TYPE (t2),
					    cond, cache);

	اگر (!use0)
	  {
	    /* Save space: see if the result is identical to one of the args.  */
	    اگر (elt == درخت_TYPE (t1) && use1)
	      واپس c_build_type_attribute_variant (t1, اوصاف);
	    اگر (elt == درخت_TYPE (t2) && use2)
	      واپس c_build_type_attribute_variant (t2, اوصاف);

	    اگر (elt == درخت_TYPE (t1) && !TYPE_DOMAIN (t2) && !TYPE_DOMAIN (t1))
	      واپس c_build_type_attribute_variant (t1, اوصاف);
	    اگر (elt == درخت_TYPE (t2) && !TYPE_DOMAIN (t2) && !TYPE_DOMAIN (t1))
	      واپس c_build_type_attribute_variant (t2, اوصاف);

	    td = TYPE_DOMAIN (use1 ? t1 : t2);
	  }
	ورنہ
	  {
	    /* Not used in C.  */
	    gcc_assert (سائز_zero_گرہ == TYPE_MIN_قدر (d1));
	    gcc_assert (سائز_zero_گرہ == TYPE_MIN_قدر (d2));

	    درخت d = fold_build3_loc (UNKNOWN_LOCATION, COND_اظہاریہ, sizetype,
				      cond, TYPE_MAX_قدر (d1),
				      TYPE_MAX_قدر (d2));

	    td = build_اشاریہ_type (d);
	  }

	/* Merge the element types, and have a size if either arg has
	   one.  We may have qualifiers on the element types.  To set
	   up TYPE_MAIN_VARIANT correctly, we need to form the
	   composite of the unqualified types and add the qualifiers
	   back at the end.  */
	صحیح quals = TYPE_QUALS (strip_array_types (elt));
	درخت unqual_elt = c_build_qualified_type (elt, TYPE_UNQUALIFIED);

	اگر ((!d1 || d1_zero) && (!d2 || d2_zero) && (d1 || d2))
	  t1 = c_build_array_type_zero_سائز (unqual_elt);
	ورنہ
	  t1 = c_build_array_type (unqual_elt, td);

	/* Check that a type which has a varying outermost dimension
	   got marked as having a variable size.  */
	منطقی varsize = (d1_variable && d2_variable)
		       || (d1_variable && !d2)
		       || (d2_variable && !d1);
	gcc_checking_assert (!varsize || C_TYPE_VARIABLE_سائز (t1));

	t1 = c_build_qualified_type (t1, quals);
	واپس c_build_type_attribute_variant (t1, اوصاف);
      }

    حالت ریکارڈ_TYPE:
    حالت UNION_TYPE:
      اگر (flag_isoc23 && !comptypes_same_p (t1, t2))
	{
	  /* Go to the original type to get the right tag.  */
	  درخت لیبل = c_type_لیبل (t1);

	  gcc_checking_assert (COMPLETE_TYPE_P (t1) && COMPLETE_TYPE_P (t2));
	  gcc_checking_assert (!لیبل || comptypes (t1, t2));

	  /* If a composite type for these two types is already under
	     construction, return it.  */

	  برائے (ساخت مرکب_cache *c = cache; c != تہی; c = c->اگلا)
	    اگر ((c->t1 == t1 && c->t2 == t2) || (c->t1 == t2 && c->t2 == t1))
	       واپس c->مرکب;

	  /* Otherwise, create a new type node and link it into the cache.  */

	  درخت n = make_گرہ (code1);
	  سیٹ_TYPE_STRUCTURAL_EQUALITY (n);
	  TYPE_NAME (n) = لیبل;

	  ساخت مرکب_cache cache2 = { t1, t2, n, cache };
	  cache = &cache2;

	  درخت f1 = TYPE_FIELDS (t1);
	  درخت f2 = TYPE_FIELDS (t2);
	  درخت fields = NULL_درخت;

	  برائے (درخت a = f1, b = f2; a && b;
	       a = DECL_CHAIN (a), b = DECL_CHAIN (b))
	    {
	      درخت ta = درخت_TYPE (a);
	      درخت tb = درخت_TYPE (b);

	      اگر (DECL_C_ثنائی_ہندسہ_میدان (a))
		{
		  ta = DECL_ثنائی_ہندسہ_میدان_TYPE (a);
		  tb = DECL_ثنائی_ہندسہ_میدان_TYPE (b);
		}

	      gcc_assert (DECL_NAME (a) == DECL_NAME (b));
	      gcc_checking_assert (!DECL_NAME (a) || comptypes (ta, tb));

	      درخت t = مرکب_type_اندرونی (ta, tb, cond, cache);
	      درخت f = build_decl (داخلہ_location, میدان_DECL, DECL_NAME (a), t);

	      DECL_PACKED (f) = DECL_PACKED (a);
	      سیٹ_DECL_ALIGN (f, DECL_ALIGN (a));
	      DECL_اوصاف (f) = DECL_اوصاف (a);
	      C_DECL_VARIABLE_سائز (f) = C_TYPE_VARIABLE_سائز (t);

	      decl_اوصاف (&f, DECL_اوصاف (f), 0);

	      اختتام_decl (f, داخلہ_location, تہی, تہی, تہی);

	      اگر (DECL_C_ثنائی_ہندسہ_میدان (a))
		{
		  /* This will be processed by finish_struct.  */
		  سیٹ_DECL_C_ثنائی_ہندسہ_میدان (f);
		  DECL_INITIAL (f) = build_int_cst (integer_type_گرہ,
						    درخت_مقصد_uhwi (DECL_سائز (a)));
		  DECL_NONADDRESSABLE_P (f) = سچ;
		  DECL_PADDING_P (f) = !DECL_NAME (a);
		}

	      DECL_CHAIN (f) = fields;
	      fields = f;
	    }

	  fields = nreverse (fields);

	  /* Setup the struct/union type.  Because we inherit all variably
	     modified components, we can ignore the size expression.  */
	  درخت اظہاریہ = NULL_درخت;

	  /* Set TYPE_STUB_DECL for debugging symbols.  */
	  TYPE_STUB_DECL (n) = pushdecl (build_decl (داخلہ_location, TYPE_DECL,
						     NULL_درخت, n));

	  n = اختتام_struct (داخلہ_location, n, fields, اوصاف, تہی,
			     &اظہاریہ);

	  واپس qualify_type (n, t1);
	}
      /* FALLTHRU */
    حالت ENUMERAL_TYPE:
      اگر (اوصاف != تہی)
	{
	  /* Try harder not to create a new aggregate type.  */
	  اگر (attribute_list_equal (TYPE_اوصاف (t1), اوصاف))
	    واپس t1;
	  اگر (attribute_list_equal (TYPE_اوصاف (t2), اوصاف))
	    واپس t2;
	}
      واپس c_build_type_attribute_variant (t1, اوصاف);

    حالت FUNCTION_TYPE:
      /* Function types: prefer the one that specified arg types.
	 If both do, merge the arg types.  Also merge the return types.  */
      {
	درخت valtype = مرکب_type_اندرونی (درخت_TYPE (t1), درخت_TYPE (t2),
						cond, cache);
	درخت p1 = TYPE_ARG_TYPES (t1);
	درخت p2 = TYPE_ARG_TYPES (t2);

	/* Save space: see if the result is identical to one of the args.  */
	اگر (valtype == درخت_TYPE (t1) && !TYPE_ARG_TYPES (t2))
	  واپس c_build_functype_attribute_variant (t1, t2, اوصاف);
	اگر (valtype == درخت_TYPE (t2) && !TYPE_ARG_TYPES (t1))
	  واپس c_build_functype_attribute_variant (t2, t1, اوصاف);

	/* Simple way if one arg fails to specify argument types.  */
	اگر (TYPE_ARG_TYPES (t1) == NULL_درخت)
	  {
	    t1 = c_build_function_type (valtype, TYPE_ARG_TYPES (t2),
					TYPE_NO_NAMED_دلائل_STDARG_P (t2));
	    t1 = c_build_type_attribute_variant (t1, اوصاف);
	    واپس qualify_type (t1, t2);
	 }
	اگر (TYPE_ARG_TYPES (t2) == NULL_درخت)
	  {
	    t1 = c_build_function_type (valtype, TYPE_ARG_TYPES (t1),
					TYPE_NO_NAMED_دلائل_STDARG_P (t1));
	    t1 = c_build_type_attribute_variant (t1, اوصاف);
	    واپس qualify_type (t1, t2);
	  }

	/* If both args specify argument types, we must merge the two
	   lists, argument by argument.  */
	درخت newargs = NULL_درخت;
	درخت *endp = &newargs;

	برائے (; p1; p1 = درخت_CHAIN (p1), p2 = درخت_CHAIN (p2))
	  {
	    اگر (p1 == void_list_گرہ)
	      {
		*endp = void_list_گرہ;
		توڑو;
	      }
	    درخت mv1 = remove_qualifiers (درخت_قدر (p1));
	    درخت mv2 = remove_qualifiers (درخت_قدر (p2));

	    gcc_assert (mv1);
	    gcc_assert (mv2);

	    mv1 = transparent_union_replacement (mv1, mv2);
	    mv2 = transparent_union_replacement (mv2, mv1);

	    *endp = درخت_cons (NULL_درخت,
			       مرکب_type_اندرونی (mv1, mv2, cond, cache),
			       NULL_درخت);

	    endp = &درخت_CHAIN (*endp);
	  }

	t1 = c_build_function_type (valtype, newargs);
	t1 = qualify_type (t1, t2);
      }
      /* FALLTHRU */

    طےشدہ:
      واپس c_build_type_attribute_variant (t1, اوصاف);
    }
}

درخت
مرکب_type_cond (درخت t1, درخت t2, درخت cond)
{
  gcc_checking_assert (comptypes_check_for_مرکب (t1, t2));

  ساخت مرکب_cache cache = { };
  درخت n = مرکب_type_اندرونی (t1, t2, cond, &cache);

  gcc_checking_assert (comptypes_check_for_مرکب (n, t1));
  gcc_checking_assert (comptypes_check_for_مرکب (n, t2));
  واپس n;
}


درخت
مرکب_type (درخت t1, درخت t2)
{
  واپس مرکب_type_cond (t1, t2, NULL_درخت);
}

/* Return the type of a conditional expression between pointers to
   possibly differently qualified versions of compatible types.

   We assume that comp_target_types has already been done and returned
   true; if that isn't so, this may crash.  */

ساکن درخت
common_اشارہ_گر_type (درخت t1, درخت t2, درخت cond)
{
  درخت اوصاف;
  غیرعلامتی ہدف_quals;
  addr_space_t as1, as2, as_common;
  صحیح quals1, quals2;

  /* Save time if the two types are the same.  */

  اگر (t1 == t2) واپس t1;

  /* If one type is nonsense, use the other.  */
  اگر (t1 == error_mark_گرہ)
    واپس t2;
  اگر (t2 == error_mark_گرہ)
    واپس t1;

  gcc_assert (درخت_رمز (t1) == اشارہ_گر_TYPE
	      && درخت_رمز (t2) == اشارہ_گر_TYPE);

  /* Merge the attributes.  */
  اوصاف = targetm.ملاؤ_type_اوصاف (t1, t2);

  /* Find the composite type of the target types, and combine the
     qualifiers of the two types' targets.  */
  درخت pointed_مقصد_1 = درخت_TYPE (t1);
  درخت pointed_مقصد_2 = درخت_TYPE (t2);
  درخت ہدف = مرکب_type_cond (TYPE_MAIN_VARIANT (pointed_مقصد_1),
				     TYPE_MAIN_VARIANT (pointed_مقصد_2), cond);

  /* Strip array types to get correct qualifier for pointers to arrays */
  quals1 = TYPE_QUALS_NO_ADDR_SPACE (strip_array_types (pointed_مقصد_1));
  quals2 = TYPE_QUALS_NO_ADDR_SPACE (strip_array_types (pointed_مقصد_2));

  /* For function types do not merge const qualifiers, but drop them
     if used inconsistently.  The middle-end uses these to mark const
     and noreturn functions.  */
  اگر (درخت_رمز (pointed_مقصد_1) == FUNCTION_TYPE)
    ہدف_quals = (quals1 & quals2);
  ورنہ
    ہدف_quals = (quals1 | quals2);

  /* If the two named address spaces are different, determine the common
     superset address space.  This is guaranteed to exist due to the
     assumption that comp_target_type returned true.  */
  as1 = TYPE_ADDR_SPACE (pointed_مقصد_1);
  as2 = TYPE_ADDR_SPACE (pointed_مقصد_2);
  اگر (!addr_space_superset (as1, as2, &as_common))
    gcc_unreachable ();

  ہدف_quals |= ENCODE_QUAL_ADDR_SPACE (as_common);

  t1 = c_build_اشارہ_گر_type (c_build_qualified_type (ہدف, ہدف_quals));
  واپس c_build_type_attribute_variant (t1, اوصاف);
}

/* Return the common type for two arithmetic types under the usual
   arithmetic conversions.  The default conversions have already been
   applied, and enumerated types converted to their compatible integer
   types.  The resulting type is unqualified and has no attributes.

   This is the type for the result of most arithmetic operations
   if the operands have the given two types.  */

ساکن درخت
c_common_type (درخت t1, درخت t2)
{
  شمار درخت_رمز_2 code1;
  شمار درخت_رمز_2 code2;

  /* If one type is nonsense, use the other.  */
  اگر (t1 == error_mark_گرہ)
    واپس t2;
  اگر (t2 == error_mark_گرہ)
    واپس t1;

  اگر (TYPE_QUALS (t1) != TYPE_UNQUALIFIED)
    t1 = TYPE_MAIN_VARIANT (t1);

  اگر (TYPE_QUALS (t2) != TYPE_UNQUALIFIED)
    t2 = TYPE_MAIN_VARIANT (t2);

  اگر (TYPE_اوصاف (t1) != NULL_درخت)
    {
      درخت attrs = affects_type_شناختی_عنصر_اوصاف (TYPE_اوصاف (t1));
      t1 = c_build_type_attribute_variant (t1, attrs);
    }

  اگر (TYPE_اوصاف (t2) != NULL_درخت)
    {
      درخت attrs = affects_type_شناختی_عنصر_اوصاف (TYPE_اوصاف (t2));
      t2 = c_build_type_attribute_variant (t2, attrs);
    }

  /* Save time if the two types are the same.  */

  اگر (t1 == t2) واپس t1;

  code1 = درخت_رمز (t1);
  code2 = درخت_رمز (t2);

  gcc_assert (code1 == سمتیہ_TYPE || code1 == COMPLEX_TYPE
	      || code1 == FIXED_نقطہ_TYPE || code1 == REAL_TYPE
	      || code1 == INTEGER_TYPE || code1 == BITINT_TYPE);
  gcc_assert (code2 == سمتیہ_TYPE || code2 == COMPLEX_TYPE
	      || code2 == FIXED_نقطہ_TYPE || code2 == REAL_TYPE
	      || code2 == INTEGER_TYPE || code2 == BITINT_TYPE);

  /* When one operand is a decimal float type, the other operand cannot be
     a generic float type or a complex type.  We also disallow vector types
     here.  */
  اگر ((DECIMAL_FLOAT_TYPE_P (t1) || DECIMAL_FLOAT_TYPE_P (t2))
      && !(DECIMAL_FLOAT_TYPE_P (t1) && DECIMAL_FLOAT_TYPE_P (t2)))
    {
      اگر (code1 == سمتیہ_TYPE || code2 == سمتیہ_TYPE)
	{
	  error ("cannot mix operands of decimal floating and vector types");
	  واپس error_mark_گرہ;
	}
      اگر (code1 == COMPLEX_TYPE || code2 == COMPLEX_TYPE)
	{
	  error ("cannot mix operands of decimal floating and complex types");
	  واپس error_mark_گرہ;
	}
      اگر (code1 == REAL_TYPE && code2 == REAL_TYPE)
	{
	  error ("cannot mix operands of decimal floating "
		 "and other floating types");
	  واپس error_mark_گرہ;
	}
    }

  /* If one type is a vector type, return that type.  (How the usual
     arithmetic conversions apply to the vector types extension is not
     precisely specified.)  */
  اگر (code1 == سمتیہ_TYPE)
    واپس t1;

  اگر (code2 == سمتیہ_TYPE)
    واپس t2;

  /* If one type is complex, form the common type of the non-complex
     components, then make that complex.  Use T1 or T2 if it is the
     required type.  */
  اگر (code1 == COMPLEX_TYPE || code2 == COMPLEX_TYPE)
    {
      درخت subtype1 = code1 == COMPLEX_TYPE ? درخت_TYPE (t1) : t1;
      درخت subtype2 = code2 == COMPLEX_TYPE ? درخت_TYPE (t2) : t2;
      درخت subtype = c_common_type (subtype1, subtype2);

      اگر (code1 == COMPLEX_TYPE && درخت_TYPE (t1) == subtype)
	واپس t1;
      ورنہ اگر (code2 == COMPLEX_TYPE && درخت_TYPE (t2) == subtype)
	واپس t2;
      ورنہ اگر (درخت_رمز (subtype) == BITINT_TYPE)
	{
	  sorry ("%<_Complex _BitInt(%d)%> unsupported",
		 TYPE_PRECISION (subtype));
	  واپس code1 == COMPLEX_TYPE ? t1 : t2;
	}
      ورنہ
	واپس build_complex_type (subtype);
    }

  /* If only one is real, use it as the result.  */

  اگر (code1 == REAL_TYPE && code2 != REAL_TYPE)
    واپس t1;

  اگر (code2 == REAL_TYPE && code1 != REAL_TYPE)
    واپس t2;

  /* If both are real and either are decimal floating point types, use
     the decimal floating point type with the greater precision. */

  اگر (code1 == REAL_TYPE && code2 == REAL_TYPE)
    {
      اگر (TYPE_MAIN_VARIANT (t1) == dfloat128_type_گرہ
	  || TYPE_MAIN_VARIANT (t2) == dfloat128_type_گرہ)
	واپس dfloat128_type_گرہ;
      /* And prefer _Decimal128 over _Decimal64x which has in GCC's
	 implementation the same mode.  */
      ورنہ اگر (TYPE_MAIN_VARIANT (t1) == dfloat64x_type_گرہ
	       || TYPE_MAIN_VARIANT (t2) == dfloat64x_type_گرہ)
	واپس dfloat64x_type_گرہ;
      ورنہ اگر (TYPE_MAIN_VARIANT (t1) == dfloat64_type_گرہ
	       || TYPE_MAIN_VARIANT (t2) == dfloat64_type_گرہ)
	واپس dfloat64_type_گرہ;
      ورنہ اگر (TYPE_MAIN_VARIANT (t1) == dfloat32_type_گرہ
	       || TYPE_MAIN_VARIANT (t2) == dfloat32_type_گرہ)
	واپس dfloat32_type_گرہ;
    }

  /* Deal with fixed-point types.  */
  اگر (code1 == FIXED_نقطہ_TYPE || code2 == FIXED_نقطہ_TYPE)
    {
      غیرعلامتی صحیح unsignedp = 0, satp = 0;
      scalar_منوال m1, m2;
      غیرعلامتی صحیح fbit1, ibit1, fbit2, ibit2, max_fbit, max_ibit;

      m1 = SCALAR_TYPE_منوال (t1);
      m2 = SCALAR_TYPE_منوال (t2);

      /* If one input type is saturating, the result type is saturating.  */
      اگر (TYPE_SATURATING (t1) || TYPE_SATURATING (t2))
	satp = 1;

      /* If both fixed-point types are unsigned, the result type is unsigned.
	 When mixing fixed-point and integer types, follow the sign of the
	 fixed-point type.
	 Otherwise, the result type is signed.  */
      اگر ((TYPE_UNSIGNED (t1) && TYPE_UNSIGNED (t2)
	   && code1 == FIXED_نقطہ_TYPE && code2 == FIXED_نقطہ_TYPE)
	  || (code1 == FIXED_نقطہ_TYPE && code2 != FIXED_نقطہ_TYPE
	      && TYPE_UNSIGNED (t1))
	  || (code1 != FIXED_نقطہ_TYPE && code2 == FIXED_نقطہ_TYPE
	      && TYPE_UNSIGNED (t2)))
	unsignedp = 1;

      /* The result type is signed.  */
      اگر (unsignedp == 0)
	{
	  /* If the input type is unsigned, we need to convert to the
	     signed type.  */
	  اگر (code1 == FIXED_نقطہ_TYPE && TYPE_UNSIGNED (t1))
	    {
	      شمار منوال_class mclass = (شمار منوال_class) 0;
	      اگر (GET_منوال_CLASS (m1) == منوال_UFRACT)
		mclass = منوال_FRACT;
	      ورنہ اگر (GET_منوال_CLASS (m1) == منوال_UACCUM)
		mclass = منوال_ACCUM;
	      ورنہ
		gcc_unreachable ();
	      m1 = as_a <scalar_منوال>
		(منوال_for_سائز (GET_منوال_PRECISION (m1), mclass, 0));
	    }
	  اگر (code2 == FIXED_نقطہ_TYPE && TYPE_UNSIGNED (t2))
	    {
	      شمار منوال_class mclass = (شمار منوال_class) 0;
	      اگر (GET_منوال_CLASS (m2) == منوال_UFRACT)
		mclass = منوال_FRACT;
	      ورنہ اگر (GET_منوال_CLASS (m2) == منوال_UACCUM)
		mclass = منوال_ACCUM;
	      ورنہ
		gcc_unreachable ();
	      m2 = as_a <scalar_منوال>
		(منوال_for_سائز (GET_منوال_PRECISION (m2), mclass, 0));
	    }
	}

      اگر (code1 == FIXED_نقطہ_TYPE)
	{
	  fbit1 = GET_منوال_FBIT (m1);
	  ibit1 = GET_منوال_IBIT (m1);
	}
      ورنہ
	{
	  fbit1 = 0;
	  /* Signed integers need to subtract one sign bit.  */
	  ibit1 = TYPE_PRECISION (t1) - (!TYPE_UNSIGNED (t1));
	}

      اگر (code2 == FIXED_نقطہ_TYPE)
	{
	  fbit2 = GET_منوال_FBIT (m2);
	  ibit2 = GET_منوال_IBIT (m2);
	}
      ورنہ
	{
	  fbit2 = 0;
	  /* Signed integers need to subtract one sign bit.  */
	  ibit2 = TYPE_PRECISION (t2) - (!TYPE_UNSIGNED (t2));
	}

      max_ibit = ibit1 >= ibit2 ?  ibit1 : ibit2;
      max_fbit = fbit1 >= fbit2 ?  fbit1 : fbit2;
      واپس c_common_fixed_نقطہ_type_for_سائز (max_ibit, max_fbit, unsignedp,
						 satp);
    }

  /* Both real or both integers; use the one with greater precision.  */

  اگر (TYPE_PRECISION (t1) > TYPE_PRECISION (t2))
    واپس t1;
  ورنہ اگر (TYPE_PRECISION (t2) > TYPE_PRECISION (t1))
    واپس t2;

  /* Same precision.  Prefer long longs to longs to ints when the
     same precision, following the C99 rules on integer type rank
     (which are equivalent to the C90 rules for C90 types).  */

  اگر (TYPE_MAIN_VARIANT (t1) == long_long_unsigned_type_گرہ
      || TYPE_MAIN_VARIANT (t2) == long_long_unsigned_type_گرہ)
    واپس long_long_unsigned_type_گرہ;

  اگر (TYPE_MAIN_VARIANT (t1) == long_long_integer_type_گرہ
      || TYPE_MAIN_VARIANT (t2) == long_long_integer_type_گرہ)
    {
      اگر (TYPE_UNSIGNED (t1) || TYPE_UNSIGNED (t2))
	واپس long_long_unsigned_type_گرہ;
      ورنہ
	واپس long_long_integer_type_گرہ;
    }

  اگر (TYPE_MAIN_VARIANT (t1) == long_unsigned_type_گرہ
      || TYPE_MAIN_VARIANT (t2) == long_unsigned_type_گرہ)
    واپس long_unsigned_type_گرہ;

  اگر (TYPE_MAIN_VARIANT (t1) == long_integer_type_گرہ
      || TYPE_MAIN_VARIANT (t2) == long_integer_type_گرہ)
    {
      /* But preserve unsignedness from the other type,
	 since long cannot hold all the values of an unsigned int.  */
      اگر (TYPE_UNSIGNED (t1) || TYPE_UNSIGNED (t2))
	واپس long_unsigned_type_گرہ;
      ورنہ
	واپس long_integer_type_گرہ;
    }

  /* For floating types of the same TYPE_PRECISION (which we here
     assume means either the same set of values, or sets of values
     neither a subset of the other, with behavior being undefined in
     the latter case), follow the rules from TS 18661-3: prefer
     interchange types _FloatN, then standard types long double,
     double, float, then extended types _FloatNx.  For extended types,
     check them starting with _Float128x as that seems most consistent
     in spirit with preferring long double to double; for interchange
     types, also check in that order for consistency although it's not
     possible for more than one of them to have the same
     precision.  */
  درخت mv1 = TYPE_MAIN_VARIANT (t1);
  درخت mv2 = TYPE_MAIN_VARIANT (t2);

  برائے (صحیح i = عدد_FLOATN_TYPES - 1; i >= 0; i--)
    اگر (mv1 == FLOATN_TYPE_گرہ (i) || mv2 == FLOATN_TYPE_گرہ (i))
      واپس FLOATN_TYPE_گرہ (i);

  /* Likewise, prefer long double to double even if same size.  */
  اگر (mv1 == long_double_type_گرہ || mv2 == long_double_type_گرہ)
    واپس long_double_type_گرہ;

  /* Likewise, prefer double to float even if same size.
     We got a couple of embedded targets with 32 bit doubles, and the
     pdp11 might have 64 bit floats.  */
  اگر (mv1 == double_type_گرہ || mv2 == double_type_گرہ)
    واپس double_type_گرہ;

  اگر (mv1 == float_type_گرہ || mv2 == float_type_گرہ)
    واپس float_type_گرہ;

  برائے (صحیح i = عدد_FLOATNX_TYPES - 1; i >= 0; i--)
    اگر (mv1 == FLOATNX_TYPE_گرہ (i) || mv2 == FLOATNX_TYPE_گرہ (i))
      واپس FLOATNX_TYPE_گرہ (i);

  اگر ((code1 == BITINT_TYPE || code2 == BITINT_TYPE) && code1 != code2)
    {
      /* Prefer any other integral types over bit-precise integer types.  */
      اگر (TYPE_UNSIGNED (t1) == TYPE_UNSIGNED (t2))
	واپس code1 == BITINT_TYPE ? t2 : t1;
      /* If BITINT_TYPE is unsigned and the other type is signed
	 non-BITINT_TYPE with the same precision, the latter has higher rank.
	 In that case:
	 Otherwise, both operands are converted to the unsigned integer type
	 corresponding to the type of the operand with signed integer type.  */
      اگر (TYPE_UNSIGNED (code1 == BITINT_TYPE ? t1 : t2))
	واپس c_common_unsigned_type (code1 == BITINT_TYPE ? t2 : t1);
    }

  /* Otherwise prefer the unsigned one.  */

  اگر (TYPE_UNSIGNED (t1))
    واپس t1;
  ورنہ
    واپس t2;
}

/* Wrapper around c_common_type that is used by c-common.cc and other
   front end optimizations that remove promotions.  ENUMERAL_TYPEs
   are allowed here and are converted to their compatible integer types.
   BOOLEAN_TYPEs are allowed here and return either boolean_type_node or
   preferably a non-Boolean type as the common type.  */
درخت
common_type (درخت t1, درخت t2)
{
  اگر (درخت_رمز (t1) == ENUMERAL_TYPE)
    t1 = ENUM_UNDERLYING_TYPE (t1);
  اگر (درخت_رمز (t2) == ENUMERAL_TYPE)
    t2 = ENUM_UNDERLYING_TYPE (t2);

  /* If both types are BOOLEAN_TYPE, then return boolean_type_node.  */
  اگر (درخت_رمز (t1) == BOOLEAN_TYPE
      && درخت_رمز (t2) == BOOLEAN_TYPE)
    واپس boolean_type_گرہ;

  /* If either type is BOOLEAN_TYPE, then return the other.  */
  اگر (درخت_رمز (t1) == BOOLEAN_TYPE)
    واپس t2;
  اگر (درخت_رمز (t2) == BOOLEAN_TYPE)
    واپس t1;

  واپس c_common_type (t1, t2);
}



/* Helper function for comptypes.  For two compatible types, return 1
   if they pass consistency checks.  In particular we test that
   TYPE_CANONICAL is set correctly, i.e. the two types can alias.  */

ساکن منطقی
comptypes_verify (درخت type1, درخت type2)
{
  اگر (type1 == type2 || !type1 || !type2
      || درخت_رمز (type1) == ERROR_MARK || درخت_رمز (type2) == ERROR_MARK)
    واپس سچ;

  gcc_checking_assert (c_verify_type (type1));
  gcc_checking_assert (c_verify_type (type2));

  اگر (TYPE_CANONICAL (type1) != TYPE_CANONICAL (type2)
      && !TYPE_STRUCTURAL_EQUALITY_P (type1)
      && !TYPE_STRUCTURAL_EQUALITY_P (type2))
    {
      /* FIXME: check other types. */
      اگر (ریکارڈ_OR_UNION_TYPE_P (type1)
	  || درخت_رمز (type1) == ENUMERAL_TYPE
	  || درخت_رمز (type2) == ENUMERAL_TYPE)
	واپس جھوٹ;
    }
  واپس سچ;
}

ساخت comptypes_ڈیٹا {

  /* output */
  منطقی enum_and_int_p;
  منطقی different_types_p;
  منطقی warning_needed;

  /* context */
  منطقی anon_میدان;
  منطقی pointedto;

  /* configuration */
  منطقی equiv;
  منطقی ignore_promoting_دلائل;

  ثابت ساخت tagged_tu_نظر_آیا_cache* cache;
};


/* Helper function for composite_type.  This function ignores when the
   function type of an old-style declaration is incompatible with a type
   of a declaration with prototype because some are arguments are not
   self-promoting.  This is ignored only for function types but not
   ignored in a nested context.  */

ساکن منطقی
comptypes_check_for_مرکب (درخت t1, درخت t2)
{
  ساخت comptypes_ڈیٹا ڈیٹا = { };
  ڈیٹا.ignore_promoting_دلائل = FUNCTION_TYPE == درخت_رمز (t1);
  واپس comptypes_اندرونی (t1, t2, &ڈیٹا);
}


/* C implementation of compatible_types_for_indirection_note_p.  */

منطقی
compatible_types_for_indirection_note_p (درخت type1, درخت type2)
{
  واپس comptypes (type1, type2);
}

/* Return true if TYPE1 and TYPE2 are compatible types for assignment
   or various other operations.  */

منطقی
comptypes (درخت type1, درخت type2)
{
  ساخت comptypes_ڈیٹا ڈیٹا = { };
  منطقی ret = comptypes_اندرونی (type1, type2, &ڈیٹا);

  gcc_checking_assert (!ret || comptypes_verify (type1, type2));

  واپس ret;
}


/* Like comptypes, but it returns non-zero only for identical
   types.  */

منطقی
comptypes_same_p (درخت type1, درخت type2)
{
  ساخت comptypes_ڈیٹا ڈیٹا = { };
  منطقی ret = comptypes_اندرونی (type1, type2, &ڈیٹا);

  gcc_checking_assert (!ret || comptypes_verify (type1, type2));

  اگر (ڈیٹا.different_types_p)
    واپس جھوٹ;

  واپس ret;
}


/* Like comptypes, but if it returns true because enum and int are
   compatible, it sets *ENUM_AND_INT_P to true.  */

منطقی
comptypes_check_enum_int (درخت type1, درخت type2, منطقی *enum_and_int_p)
{
  ساخت comptypes_ڈیٹا ڈیٹا = { };
  منطقی ret = comptypes_اندرونی (type1, type2, &ڈیٹا);
  *enum_and_int_p = ڈیٹا.enum_and_int_p;

  gcc_checking_assert (!ret || comptypes_verify (type1, type2));

  واپس ret;
}



/* Like comptypes, but if it returns true for struct and union types
   considered equivalent for aliasing purposes, i.e. for setting
   TYPE_CANONICAL after completing a struct or union.

   This function must return false only for types which are not
   compatible according to C language semantics (cf. comptypes),
   otherwise the middle-end would make incorrect aliasing decisions.
   It may return true for some similar types that are not compatible
   according to those stricter rules.

   In particular, we ignore size expression in arrays so that the
   following structs are in the same equivalence class:

   struct foo { char (*buf)[]; };
   struct foo { char (*buf)[3]; };
   struct foo { char (*buf)[4]; };

   We also treat unions / structs with members which are pointers to
   structures or unions with the same tag as equivalent (if they are not
   incompatible for other reasons).  Although incomplete structure
   or union types are not compatible to any other type, they may become
   compatible to different types when completed.  To avoid having to update
   TYPE_CANONICAL at this point, we only consider the tag when forming
   the equivalence classes.  For example, the following types with tag
   'foo' are all considered equivalent:

   struct bar;
   struct foo { struct bar *x };
   struct foo { struct bar { int a; } *x };
   struct foo { struct bar { char b; } *x };  */

منطقی
comptypes_equiv_p (درخت type1, درخت type2)
{
  ساخت comptypes_ڈیٹا ڈیٹا = { };
  ڈیٹا.equiv = سچ;
  منطقی ret = comptypes_اندرونی (type1, type2, &ڈیٹا);

  /* check that different equivance classes are assigned only
     to types that are not compatible.  */
  gcc_checking_assert (ret || !comptypes (type1, type2));

  واپس ret;
}


/* Return true if TYPE1 and TYPE2 are compatible types for assignment
   or various other operations.  If they are compatible but a warning may
   be needed if you use them together, 'warning_needed' in DATA is set.
   If one type is an enum and the other a compatible integer type, then
   this sets 'enum_and_int_p' in DATA to true (it is never set to
   false).  If the types are compatible but different enough not to be
   permitted in C11 typedef redeclarations, then this sets
   'different_types_p' in DATA to true; it is never set to
   false, but may or may not be set if the types are incompatible.
   If two functions types are not compatible only because one is
   an old-style definition that does not have self-promoting arguments,
   then this can be ignored by setting 'ignore_promoting_args_p'.
   For 'equiv' we can compute equivalency classes (see above).  */

ساکن منطقی
comptypes_اندرونی (const_درخت type1, const_درخت type2,
		    ساخت comptypes_ڈیٹا *ڈیٹا)
{
  const_درخت t1 = type1;
  const_درخت t2 = type2;

  /* Suppress errors caused by previously reported errors.  */

  اگر (t1 == t2 || !t1 || !t2
      || درخت_رمز (t1) == ERROR_MARK || درخت_رمز (t2) == ERROR_MARK)
    واپس سچ;

  /* Qualifiers must match. C99 6.7.3p9 */

  اگر (TYPE_QUALS (t1) != TYPE_QUALS (t2))
    واپس جھوٹ;

  /* Enumerated types are compatible with integer types, but this is
     not transitive: two enumerated types in the same translation unit
     are compatible with each other only if they are the same type.  */

  اگر (درخت_رمز (t1) == ENUMERAL_TYPE
      && COMPLETE_TYPE_P (t1)
      && درخت_رمز (t2) != ENUMERAL_TYPE)
    {
      t1 = ENUM_UNDERLYING_TYPE (t1);
      اگر (درخت_رمز (t2) != VOID_TYPE)
	{
	  ڈیٹا->enum_and_int_p = سچ;
	  ڈیٹا->different_types_p = سچ;
	}
    }
  ورنہ اگر (درخت_رمز (t2) == ENUMERAL_TYPE
	   && COMPLETE_TYPE_P (t2)
	   && درخت_رمز (t1) != ENUMERAL_TYPE)
    {
      t2 = ENUM_UNDERLYING_TYPE (t2);
      اگر (درخت_رمز (t1) != VOID_TYPE)
	{
	  ڈیٹا->enum_and_int_p = سچ;
	  ڈیٹا->different_types_p = سچ;
	}
    }

  اگر (t1 == t2)
    واپس سچ;

  /* Different classes of types can't be compatible.  */

  اگر (درخت_رمز (t1) != درخت_رمز (t2))
    واپس جھوٹ;

  /* Allow for two different type nodes which have essentially the same
     definition.  Note that we already checked for equality of the type
     qualifiers (just above).  */

  اگر (درخت_رمز (t1) != ARRAY_TYPE
      && TYPE_MAIN_VARIANT (t1) == TYPE_MAIN_VARIANT (t2))
    واپس سچ;

  صحیح attrval;

  /* 1 if no need for warning yet, 2 if warning cause has been seen.  */
  اگر (!(attrval = comp_type_اوصاف (t1, t2)))
    واپس جھوٹ;

  اگر (2 == attrval)
    ڈیٹا->warning_needed = سچ;

  انتخاب (درخت_رمز (t1))
    {
    حالت INTEGER_TYPE:
    حالت FIXED_نقطہ_TYPE:
    حالت REAL_TYPE:
    حالت BITINT_TYPE:
      /* With these nodes, we can't determine type equivalence by
	 looking at what is stored in the nodes themselves, because
	 two nodes might have different TYPE_MAIN_VARIANTs but still
	 represent the same type.  For example, wchar_t and int could
	 have the same properties (TYPE_PRECISION, TYPE_MIN_VALUE,
	 TYPE_MAX_VALUE, etc.), but have different TYPE_MAIN_VARIANTs
	 and are distinct types.  On the other hand, int and the
	 following typedef

	   typedef int INT __attribute((may_alias));

	 have identical properties, different TYPE_MAIN_VARIANTs, but
	 represent the same type.  The canonical type system keeps
	 track of equivalence in this case, so we fall back on it.  */
      واپس TYPE_CANONICAL (t1) == TYPE_CANONICAL (t2);

    حالت اشارہ_گر_TYPE:
      /* Do not remove mode information.  */
      اگر (TYPE_منوال (t1) != TYPE_منوال (t2))
	واپس جھوٹ;
      ڈیٹا->pointedto = سچ;
      واپس comptypes_اندرونی (درخت_TYPE (t1), درخت_TYPE (t2), ڈیٹا);

    حالت FUNCTION_TYPE:
      واپس function_types_compatible_p (t1, t2, ڈیٹا);

    حالت ARRAY_TYPE:
      {
	درخت d1 = TYPE_DOMAIN (t1);
	درخت d2 = TYPE_DOMAIN (t2);

	/* Target types must match incl. qualifiers.  */
	اگر (!comptypes_اندرونی (درخت_TYPE (t1), درخت_TYPE (t2), ڈیٹا))
	  واپس جھوٹ;

	اگر ((d1 == NULL_درخت) != (d2 == NULL_درخت))
	  ڈیٹا->different_types_p = سچ;
	/* Ignore size mismatches when forming equivalence classes.  */
	اگر (ڈیٹا->equiv)
	  واپس سچ;
	/* Sizes must match unless one is missing or variable.  */
	اگر (d1 == NULL_درخت || d2 == NULL_درخت || d1 == d2)
	  واپس سچ;

	منطقی d1_variable = چوٹی_array_vla_p (t1);
	منطقی d2_variable = چوٹی_array_vla_p (t2);

	اگر (d1_variable != d2_variable)
	  ڈیٹا->different_types_p = سچ;
	اگر (d1_variable || d2_variable)
	  واپس سچ;

	منطقی d1_zero = zero_لمبائی_array_type_p (t1)
		       || flexible_array_member_type_p (t1);

	منطقی d2_zero = zero_لمبائی_array_type_p (t2)
		       || flexible_array_member_type_p (t2);

	اگر (d1_zero && d2_zero)
	  واپس سچ;
	اگر (d1_zero || d2_zero)
	  واپس جھوٹ;

	اگر (!درخت_int_cst_equal (TYPE_MIN_قدر (d1), TYPE_MIN_قدر (d2))
	    || !درخت_int_cst_equal (TYPE_MAX_قدر (d1), TYPE_MAX_قدر (d2)))
	  واپس جھوٹ;

	واپس سچ;
      }

    حالت ENUMERAL_TYPE:
    حالت ریکارڈ_TYPE:
    حالت UNION_TYPE:

      اگر (!flag_isoc23)
	واپس جھوٹ;

      واپس tagged_types_tu_compatible_p (t1, t2, ڈیٹا);

    حالت سمتیہ_TYPE:
      واپس معلوم_eq (TYPE_سمتیہ_SUBPARTS (t1), TYPE_سمتیہ_SUBPARTS (t2))
	     && comptypes_اندرونی (درخت_TYPE (t1), درخت_TYPE (t2), ڈیٹا);

    طےشدہ:
      واپس جھوٹ;
    }
  gcc_unreachable ();
}

/* Return true if TTL and TTR are pointers to types that are equivalent, ignoring
   their qualifiers, except for named address spaces.  If the pointers point to
   different named addresses, then we must determine if one address space is a
   subset of the other.  */

ساکن منطقی
comp_ہدف_types (location_t location, درخت ttl, درخت ttr)
{
  درخت mvl = درخت_TYPE (ttl);
  درخت mvr = درخت_TYPE (ttr);
  addr_space_t asl = TYPE_ADDR_SPACE (mvl);
  addr_space_t asr = TYPE_ADDR_SPACE (mvr);
  addr_space_t as_common;

  /* Fail if pointers point to incompatible address spaces.  */
  اگر (!addr_space_superset (asl, asr, &as_common))
    واپس 0;

  /* Qualifiers on element types of array types that are
     pointer targets are also removed.  */
  ساخت comptypes_ڈیٹا ڈیٹا = { };
  اگر (!comptypes_اندرونی (remove_qualifiers (mvl),
			   remove_qualifiers (mvr), &ڈیٹا))
    واپس جھوٹ;

  /* For pedantic use comptypes on arrays before removing
     qualifiers on the element type. */
  اگر (درخت_رمز (mvl) == ARRAY_TYPE
      && درخت_رمز (mvr) == ARRAY_TYPE
      && !comptypes (mvl, mvr))
    pedwarn_c11 (location, OPT_Wpedantic, "invalid use of pointers to arrays "
					  "with different qualifiers in ISO C "
					  "before C23");

  اگر (ڈیٹا.warning_needed)
    pedwarn (location, OPT_Wpedantic, "types are not quite compatible");

  اگر (ڈیٹا.enum_and_int_p && warn_cxx_compat)
    warning_at (location, OPT_Wc___compat,
		"pointer target types incompatible in C++");

  واپس سچ;
}

/* Subroutines of `comptypes'.  */

/* Return true if two 'struct', 'union', or 'enum' types T1 and T2 are
   compatible.  The two types are not the same (which has been
   checked earlier in comptypes_internal).  */

ساکن منطقی
tagged_types_tu_compatible_p (const_درخت t1, const_درخت t2,
			      ساخت comptypes_ڈیٹا *ڈیٹا)
{
  درخت s1, s2;

  اگر (c_type_لیبل (t1) != c_type_لیبل (t2))
    واپس جھوٹ;

  /* When forming equivalence classes for TYPE_CANONICAL in C23, we treat
     structs with the same tag as equivalent, but only when they are targets
     of pointers inside other structs.  */
  اگر (ڈیٹا->equiv && ڈیٹا->pointedto && NULL_درخت != c_type_لیبل (t1))
    واپس سچ;

  /* Different types without tag are incompatible except as an anonymous
     field or when forming equivalence classes for TYPE_CANONICAL.  */
  اگر (!ڈیٹا->anon_میدان && !ڈیٹا->equiv && NULL_درخت == c_type_لیبل (t1))
    واپس جھوٹ;

  اگر (!ڈیٹا->anon_میدان && TYPE_STUB_DECL (t1) != TYPE_STUB_DECL (t2))
    ڈیٹا->different_types_p = سچ;

  /* Incomplete types are incompatible inside a TU.  */
  اگر (TYPE_سائز (t1) == تہی || TYPE_سائز (t2) == تہی)
    واپس جھوٹ;

  اگر (ENUMERAL_TYPE != درخت_رمز (t1)
      && (TYPE_الٹ_STORAGE_ترتیب (t1)
	  != TYPE_الٹ_STORAGE_ترتیب (t2)))
    واپس جھوٹ;

  اگر (TYPE_USER_ALIGN (t1) != TYPE_USER_ALIGN (t2))
    ڈیٹا->different_types_p = سچ;

  /* For types already being looked at in some active
     invocation of this function, assume compatibility.
     The cache is built as a linked list on the stack
     with the head of the list passed downwards.  */
  برائے (ثابت ساخت tagged_tu_نظر_آیا_cache *t = ڈیٹا->cache;
       t != تہی; t = t->اگلا)
    اگر (t->t1 == t1 && t->t2 == t2)
      واپس سچ;

  ثابت ساخت tagged_tu_نظر_آیا_cache اندراج_2 = { ڈیٹا->cache, t1, t2 };

  انتخاب (درخت_رمز (t1))
    {
    حالت ENUMERAL_TYPE:
      {
	اگر (!comptypes (ENUM_UNDERLYING_TYPE (t1), ENUM_UNDERLYING_TYPE (t2)))
	  واپس جھوٹ;

	/* Speed up the case where the type values are in the same order.  */
	درخت tv1 = TYPE_اقدار (t1);
	درخت tv2 = TYPE_اقدار (t2);

	اگر (tv1 == tv2)
	  واپس سچ;

	برائے (;tv1 && tv2; tv1 = درخت_CHAIN (tv1), tv2 = درخت_CHAIN (tv2))
	  {
	    اگر (درخت_PURPOSE (tv1) != درخت_PURPOSE (tv2))
	      توڑو;

	    اگر (simple_cst_equal (DECL_INITIAL (درخت_قدر (tv1)),
				  DECL_INITIAL (درخت_قدر (tv2))) != 1)
	      توڑو;
	  }

	اگر (tv1 == NULL_درخت && tv2 == NULL_درخت)
	  واپس سچ;

	اگر (tv1 == NULL_درخت || tv2 == NULL_درخت)
	  واپس جھوٹ;

	اگر (list_لمبائی (TYPE_اقدار (t1)) != list_لمبائی (TYPE_اقدار (t2)))
	  واپس جھوٹ;

	برائے (s1 = TYPE_اقدار (t1); s1; s1 = درخت_CHAIN (s1))
	  {
	    s2 = purpose_member (درخت_PURPOSE (s1), TYPE_اقدار (t2));

	    اگر (s2 == تہی
		|| simple_cst_equal (DECL_INITIAL (درخت_قدر (s1)),
				     DECL_INITIAL (درخت_قدر (s2))) != 1)
	      واپس جھوٹ;
	  }

	واپس سچ;
      }

    حالت UNION_TYPE:
    حالت ریکارڈ_TYPE:

	اگر (list_لمبائی (TYPE_FIELDS (t1)) != list_لمبائی (TYPE_FIELDS (t2)))
	  واپس جھوٹ;

	برائے (s1 = TYPE_FIELDS (t1), s2 = TYPE_FIELDS (t2);
	     s1 && s2;
	     s1 = DECL_CHAIN (s1), s2 = DECL_CHAIN (s2))
	  {
	    gcc_assert (درخت_رمز (s1) == میدان_DECL);
	    gcc_assert (درخت_رمز (s2) == میدان_DECL);

	    درخت ft1 = درخت_TYPE (s1);
	    درخت ft2 = درخت_TYPE (s2);

	    اگر (DECL_NAME (s1) != DECL_NAME (s2))
	      واپس جھوٹ;

	    اگر (DECL_ALIGN (s1) != DECL_ALIGN (s2))
	      واپس جھوٹ;

	    اگر (DECL_C_ثنائی_ہندسہ_میدان (s1) != DECL_C_ثنائی_ہندسہ_میدان (s2))
	       واپس جھوٹ;

	    اگر (DECL_C_ثنائی_ہندسہ_میدان (s1))
	      {
		اگر (!درخت_int_cst_equal (DECL_سائز (s1), DECL_سائز (s2)))
		  واپس جھوٹ;

		ft1 = DECL_ثنائی_ہندسہ_میدان_TYPE (s1);
		ft2 = DECL_ثنائی_ہندسہ_میدان_TYPE (s2);
	      }

	    اگر (!ft1 || !ft2)
	      واپس جھوٹ;

	    اگر (درخت_رمز (ft1) == ERROR_MARK || درخت_رمز (ft2) == ERROR_MARK)
	      واپس جھوٹ;

	    ڈیٹا->anon_میدان = !DECL_NAME (s1);
	    ڈیٹا->pointedto = جھوٹ;

	    ثابت ساخت tagged_tu_نظر_آیا_cache *cache = ڈیٹا->cache;
	    ڈیٹا->cache = &اندراج_2;
	    منطقی ret = comptypes_اندرونی (ft1, ft2, ڈیٹا);
	    ڈیٹا->cache = cache;
	    اگر (!ret)
	      واپس جھوٹ;

	    درخت st1 = TYPE_سائز (درخت_TYPE (s1));
	    درخت st2 = TYPE_سائز (درخت_TYPE (s2));

	    اگر (ڈیٹا->equiv
		&& st1 && درخت_رمز (st1) == INTEGER_CST
		&& st2 && درخت_رمز (st2) == INTEGER_CST
		&& !درخت_int_cst_equal (st1, st2))
	     واپس جھوٹ;

	    درخت counted_by1 = lookup_attribute ("counted_by",
						 DECL_اوصاف (s1));
	    درخت counted_by2 = lookup_attribute ("counted_by",
						 DECL_اوصاف (s2));
	    /* If there is no counted_by attribute for both fields.  */
	    اگر (!counted_by1 && !counted_by2)
	      جاری;

	    /* If only one field has counted_by attribute.  */
	    اگر ((counted_by1 && !counted_by2)
		|| (!counted_by1 && counted_by2))
	      واپس جھوٹ;

	    /* Now both s1 and s2 have counted_by attributes, check
	       whether they are the same.  */

	    درخت counted_by_field1
	      = lookup_میدان (t1, درخت_قدر (درخت_قدر (counted_by1)));
	    درخت counted_by_field2
	      = lookup_میدان (t2, درخت_قدر (درخت_قدر (counted_by2)));

	    gcc_assert (counted_by_field1 && counted_by_field2);

	    جب (درخت_CHAIN (counted_by_field1))
	      counted_by_field1 = درخت_CHAIN (counted_by_field1);
	    جب (درخت_CHAIN (counted_by_field2))
	      counted_by_field2 = درخت_CHAIN (counted_by_field2);

	    اگر (DECL_NAME (درخت_قدر (counted_by_field1))
		!= DECL_NAME (درخت_قدر (counted_by_field2)))
	      واپس جھوٹ;
	  }
	واپس سچ;

    طےشدہ:
      gcc_unreachable ();
    }
}

/* Return true if two function types F1 and F2 are compatible.
   If either type specifies no argument types,
   the other must specify a fixed number of self-promoting arg types.
   Otherwise, if one type specifies only the number of arguments,
   the other must specify that number of self-promoting arg types.
   Otherwise, the argument types must match.  */

ساکن منطقی
function_types_compatible_p (const_درخت f1, const_درخت f2,
			     ساخت comptypes_ڈیٹا *ڈیٹا)
{
  درخت ret1 = درخت_TYPE (f1);
  درخت ret2 = درخت_TYPE (f2);

  /* 'volatile' qualifiers on a function's return type used to mean
     the function is noreturn.  */
  اگر (TYPE_VOLATILE (ret1) != TYPE_VOLATILE (ret2))
    pedwarn (داخلہ_location, 0, "function return types not compatible due to %<volatile%>");
  اگر (TYPE_VOLATILE (ret1))
    ret1 = build_qualified_type (TYPE_MAIN_VARIANT (ret1),
				 TYPE_QUALS (ret1) & ~TYPE_QUAL_VOLATILE);
  اگر (TYPE_VOLATILE (ret2))
    ret2 = build_qualified_type (TYPE_MAIN_VARIANT (ret2),
				 TYPE_QUALS (ret2) & ~TYPE_QUAL_VOLATILE);

  منطقی ignore_pargs = ڈیٹا->ignore_promoting_دلائل;
  ڈیٹا->ignore_promoting_دلائل = جھوٹ;

  اگر (!comptypes_اندرونی (ret1, ret2, ڈیٹا))
    واپس جھوٹ;

  ڈیٹا->ignore_promoting_دلائل = ignore_pargs;

  درخت args1 = TYPE_ARG_TYPES (f1);
  درخت args2 = TYPE_ARG_TYPES (f2);

  اگر ((args1 == NULL_درخت) != (args2 == NULL_درخت))
    ڈیٹا->different_types_p = سچ;

  /* An unspecified parmlist matches any specified parmlist
     whose argument types don't need default promotions.  */

  اگر (args1 == NULL_درخت)
    {
      اگر (TYPE_NO_NAMED_دلائل_STDARG_P (f1) != TYPE_NO_NAMED_دلائل_STDARG_P (f2))
	واپس جھوٹ;
      اگر (!(ڈیٹا->ignore_promoting_دلائل || self_promoting_دلائل_p (args2)))
	واپس جھوٹ;
      ڈیٹا->ignore_promoting_دلائل = جھوٹ;
      /* If one of these types comes from a non-prototype fn definition,
	 compare that with the other type's arglist.
	 If they don't match, ask for a warning (but no error).  */
      اگر (TYPE_ACTUAL_ARG_TYPES (f1)
	  && !type_lists_compatible_p (args2, TYPE_ACTUAL_ARG_TYPES (f1), ڈیٹا))
	 ڈیٹا->warning_needed = سچ;
      واپس سچ;
    }
  اگر (args2 == NULL_درخت)
    {
      اگر (TYPE_NO_NAMED_دلائل_STDARG_P (f1) != TYPE_NO_NAMED_دلائل_STDARG_P (f2))
	واپس جھوٹ;
      اگر (!(ڈیٹا->ignore_promoting_دلائل || self_promoting_دلائل_p (args1)))
	واپس جھوٹ;
      ڈیٹا->ignore_promoting_دلائل = جھوٹ;
      اگر (TYPE_ACTUAL_ARG_TYPES (f2)
	  && !type_lists_compatible_p (args1, TYPE_ACTUAL_ARG_TYPES (f2), ڈیٹا))
	ڈیٹا->warning_needed = سچ;
      واپس سچ;
    }

  /* Both types have argument lists: compare them and propagate results.  */
  واپس type_lists_compatible_p (args1, args2, ڈیٹا);
}

/* Check two lists of types for compatibility, returning false for
   incompatible, true for compatible.  */

ساکن منطقی
type_lists_compatible_p (const_درخت args1, const_درخت args2,
			 ساخت comptypes_ڈیٹا *ڈیٹا)
{
  جب (1)
    {
      اگر (args1 == NULL_درخت && args2 == NULL_درخت)
	واپس سچ;
      /* If one list is shorter than the other,
	 they fail to match.  */
      اگر (args1 == NULL_درخت || args2 == NULL_درخت)
	واپس جھوٹ;
      درخت a1 = درخت_قدر (args1);
      درخت a2 = درخت_قدر (args2);
      درخت mv1 = remove_qualifiers (a1);
      درخت mv2 = remove_qualifiers (a2);

      gcc_assert (mv2);
      gcc_assert (mv2);

      /* If one of the lists has an error marker, ignore this arg.  */
      اگر (درخت_رمز (a1) == ERROR_MARK
	       || درخت_رمز (a2) == ERROR_MARK)
	;
      ورنہ اگر (!comptypes_اندرونی (mv1, mv2, ڈیٹا))
	{
	  ڈیٹا->different_types_p = سچ;
	  /* Allow  wait (union {union wait *u; int *i} *)
	     and  wait (union wait *)  to be compatible.  */
	  اگر (درخت_رمز (a1) == UNION_TYPE
	      && (TYPE_NAME (a1) == NULL_درخت
		  || TYPE_TRANSPARENT_AGGR (a1))
	      && درخت_رمز (TYPE_سائز (a1)) == INTEGER_CST
	      && درخت_int_cst_equal (TYPE_سائز (a1),
				     TYPE_سائز (a2)))
	    {
	      درخت memb;
	      برائے (memb = TYPE_FIELDS (a1);
		   memb; memb = DECL_CHAIN (memb))
		{
		  درخت mv3 = remove_qualifiers (درخت_TYPE (memb));
		  اگر (comptypes_اندرونی (mv3, mv2, ڈیٹا))
		    توڑو;
		}
	      اگر (memb == NULL_درخت)
		واپس جھوٹ;
	    }
	  ورنہ اگر (درخت_رمز (a2) == UNION_TYPE
		   && (TYPE_NAME (a2) == NULL_درخت
		       || TYPE_TRANSPARENT_AGGR (a2))
		   && درخت_رمز (TYPE_سائز (a2)) == INTEGER_CST
		   && درخت_int_cst_equal (TYPE_سائز (a2),
					  TYPE_سائز (a1)))
	    {
	      درخت memb;
	      برائے (memb = TYPE_FIELDS (a2);
		   memb; memb = DECL_CHAIN (memb))
		{
		  درخت mv3 = remove_qualifiers (درخت_TYPE (memb));
		  اگر (comptypes_اندرونی (mv3, mv1, ڈیٹا))
		    توڑو;
		}
	      اگر (memb == NULL_درخت)
		واپس جھوٹ;
	    }
	  ورنہ
	    واپس جھوٹ;
	}

      args1 = درخت_CHAIN (args1);
      args2 = درخت_CHAIN (args2);
    }
}

/* Compute the size to increment a pointer by.  When a function type or void
   type or incomplete type is passed, size_one_node is returned.
   This function does not emit any diagnostics; the caller is responsible
   for that.  */

ساکن درخت
c_سائز_اندر_بائٹیں (const_درخت type)
{
  شمار درخت_رمز_2 رمز = درخت_رمز (type);

  اگر (رمز == FUNCTION_TYPE || رمز == VOID_TYPE || رمز == ERROR_MARK
      || !COMPLETE_TYPE_P (type))
    واپس سائز_one_گرہ;

  /* Convert in case a char is more than one unit.  */
  واپس سائز_binop_loc (داخلہ_location, CEIL_DIV_اظہاریہ, TYPE_سائز_UNIT (type),
			 سائز_int (TYPE_PRECISION (char_type_گرہ)
				   / بٹ_فی_UNIT));
}

/* Return either DECL or its known constant value (if it has one).  */

درخت
decl_constant_قدر_1 (درخت decl, منطقی اندر_init)
{
  اگر (/* Note that DECL_INITIAL isn't valid for a PARM_DECL.  */
      درخت_رمز (decl) != PARM_DECL
      && !درخت_THIS_VOLATILE (decl)
      && درخت_READONLY (decl)
      && DECL_INITIAL (decl) != NULL_درخت
      && !error_عملیہ_p (DECL_INITIAL (decl))
      /* This is invalid if initial value is not constant.
	 If it has either a function call, a memory reference,
	 or a variable, then re-evaluating it could give different results.  */
      && درخت_CONSTANT (DECL_INITIAL (decl))
      /* Check for cases where this is sub-optimal, even though valid.  */
      && (اندر_init || درخت_رمز (DECL_INITIAL (decl)) != CONSTRUCTOR))
    واپس DECL_INITIAL (decl);
  واپس decl;
}

/* Return either DECL or its known constant value (if it has one).
   Like the above, but always return decl outside of functions.  */

درخت
decl_constant_قدر (درخت decl)
{
  /* Don't change a variable array bound or initial value to a constant
     in a place where a variable is invalid.  */
  واپس current_function_decl ? decl_constant_قدر_1 (decl, جھوٹ) : decl;
}

/* Convert the array expression EXP to a pointer.  */
ساکن درخت
array_مقصد_اشارہ_گر_conversion (location_t loc, درخت قوت_نما)
{
  درخت orig_exp = قوت_نما;
  درخت type = درخت_TYPE (قوت_نما);
  درخت adr;
  درخت restype = درخت_TYPE (type);
  درخت ptrtype;

  gcc_assert (درخت_رمز (type) == ARRAY_TYPE);

  STRIP_TYPE_NOPS (قوت_نما);

  copy_warning (قوت_نما, orig_exp);

  ptrtype = c_build_اشارہ_گر_type (restype);

  اگر (بالواسطہ_REF_P (قوت_نما))
    واپس convert (ptrtype, درخت_عملیہ (قوت_نما, 0));

  /* In C++ array compound literals are temporary objects unless they are
     const or appear in namespace scope, so they are destroyed too soon
     to use them for much of anything  (c++/53220).  */
  اگر (warn_cxx_compat && درخت_رمز (قوت_نما) == COMPOUND_LITERAL_اظہاریہ)
    {
      درخت decl = درخت_عملیہ (درخت_عملیہ (قوت_نما, 0), 0);
      اگر (!درخت_READONLY (decl) && !درخت_STATIC (decl))
	warning_at (DECL_ماخذ_LOCATION (decl), OPT_Wc___compat,
		    "converting an array compound literal to a pointer "
		    "leads to a dangling pointer in C++");
    }

  adr = build_unary_op (loc, ADDR_اظہاریہ, قوت_نما, سچ);
  واپس convert (ptrtype, adr);
}

/* Convert the function expression EXP to a pointer.  */
ساکن درخت
function_مقصد_اشارہ_گر_conversion (location_t loc, درخت قوت_نما)
{
  درخت orig_exp = قوت_نما;

  gcc_assert (درخت_رمز (درخت_TYPE (قوت_نما)) == FUNCTION_TYPE);

  STRIP_TYPE_NOPS (قوت_نما);

  copy_warning (قوت_نما, orig_exp);

  درخت exp2 = build_unary_op (loc, ADDR_اظہاریہ, قوت_نما, جھوٹ);

  /* If the function is defined and known to not require a non-local
     context, make sure no trampoline is generated.  */
  اگر (درخت_رمز (قوت_نما) == FUNCTION_DECL
      && DECL_INITIAL (قوت_نما) && !C_FUNC_NONLOCAL_CONTEXT (قوت_نما))
   درخت_NO_TRAMPOLINE (exp2) = 1;

  واپس exp2;
}

/* Mark EXP as read, not just set, for set but not used -Wunused
   warning purposes.  */

خالی
mark_exp_read (درخت قوت_نما)
{
  انتخاب (درخت_رمز (قوت_نما))
    {
    حالت VAR_DECL:
    حالت PARM_DECL:
      DECL_READ_P (قوت_نما) = 1;
      توڑو;
    CASE_CONVERT:
      اگر (VOID_TYPE_P (درخت_TYPE (قوت_نما)))
	انتخاب (درخت_رمز (درخت_عملیہ (قوت_نما, 0)))
	  {
	  حالت PREINCREMENT_اظہاریہ:
	  حالت PREDECREMENT_اظہاریہ:
	  حالت POSTINCREMENT_اظہاریہ:
	  حالت POSTDECREMENT_اظہاریہ:
	    واپس;
	  طےشدہ:
	    توڑو;
	  }
      /* FALLTHRU */
    حالت ARRAY_REF:
    حالت COMPONENT_REF:
    حالت MODIFY_اظہاریہ:
    حالت REALPART_اظہاریہ:
    حالت IMAGPART_اظہاریہ:
    حالت ADDR_اظہاریہ:
    حالت VIEW_CONVERT_اظہاریہ:
    حالت PREINCREMENT_اظہاریہ:
    حالت PREDECREMENT_اظہاریہ:
    حالت POSTINCREMENT_اظہاریہ:
    حالت POSTDECREMENT_اظہاریہ:
      mark_exp_read (درخت_عملیہ (قوت_نما, 0));
      توڑو;
    حالت COMPOUND_اظہاریہ:
      /* Pattern match what build_atomic_assign produces with modifycode
	 NOP_EXPR.  */
      اگر (VAR_P (درخت_عملیہ (قوت_نما, 1))
	  && DECL_ARTIFICIAL (درخت_عملیہ (قوت_نما, 1))
	  && درخت_رمز (درخت_عملیہ (قوت_نما, 0)) == COMPOUND_اظہاریہ)
	{
	  درخت t1 = درخت_عملیہ (درخت_عملیہ (قوت_نما, 0), 0);
	  درخت t2 = درخت_عملیہ (درخت_عملیہ (قوت_نما, 0), 1);
	  اگر (درخت_رمز (t1) == ہدف_اظہاریہ
	      && ہدف_اظہاریہ_خانہ (t1) == درخت_عملیہ (قوت_نما, 1)
	      && درخت_رمز (t2) == CALL_اظہاریہ)
	    {
	      درخت fndecl = get_callee_fndecl (t2);
	      درخت arg = NULL_درخت;
	      اگر (fndecl
		  && درخت_رمز (fndecl) == FUNCTION_DECL
		  && fndecl_built_اندر_p (fndecl, BUILT_اندر_معمول)
		  && call_اظہاریہ_nargs (t2) >= 2)
		انتخاب (DECL_FUNCTION_رمز (fndecl))
		  {
		  حالت BUILT_اندر_ATOMIC_STORE:
		    arg = CALL_اظہاریہ_ARG (t2, 1);
		    توڑو;
		  حالت BUILT_اندر_ATOMIC_STORE_1:
		  حالت BUILT_اندر_ATOMIC_STORE_2:
		  حالت BUILT_اندر_ATOMIC_STORE_4:
		  حالت BUILT_اندر_ATOMIC_STORE_8:
		  حالت BUILT_اندر_ATOMIC_STORE_16:
		    arg = CALL_اظہاریہ_ARG (t2, 0);
		    توڑو;
		  طےشدہ:
		    توڑو;
		  }
	      اگر (arg)
		{
		  STRIP_NOPS (arg);
		  اگر (درخت_رمز (arg) == ADDR_اظہاریہ
		      && DECL_P (درخت_عملیہ (arg, 0))
		      && TYPE_ATOMIC (درخت_TYPE (درخت_عملیہ (arg, 0))))
		    mark_exp_read (درخت_عملیہ (arg, 0));
		}
	    }
	}
      /* FALLTHRU */
    حالت C_MAYBE_CONST_اظہاریہ:
      mark_exp_read (درخت_عملیہ (قوت_نما, 1));
      توڑو;
    حالت OMP_ARRAY_SECTION:
      mark_exp_read (درخت_عملیہ (قوت_نما, 0));
      اگر (درخت_عملیہ (قوت_نما, 1))
	mark_exp_read (درخت_عملیہ (قوت_نما, 1));
      اگر (درخت_عملیہ (قوت_نما, 2))
	mark_exp_read (درخت_عملیہ (قوت_نما, 2));
      توڑو;
    طےشدہ:
      توڑو;
    }
}

/* Perform the default conversion of arrays and functions to pointers.
   Return the result of converting EXP.  For any other expression, just
   return EXP.

   LOC is the location of the expression.  */

ساخت c_اظہاریہ
default_function_array_conversion (location_t loc, ساخت c_اظہاریہ قوت_نما)
{
  درخت orig_exp = قوت_نما.قدر;
  درخت type = درخت_TYPE (قوت_نما.قدر);
  شمار درخت_رمز_2 رمز = درخت_رمز (type);

  انتخاب (رمز)
    {
    حالت ARRAY_TYPE:
      {
	منطقی not_lvalue = جھوٹ;
	منطقی lvalue_array_p;

	جب ((درخت_رمز (قوت_نما.قدر) == NON_LVALUE_اظہاریہ
		|| CONVERT_اظہاریہ_P (قوت_نما.قدر))
	       && درخت_TYPE (درخت_عملیہ (قوت_نما.قدر, 0)) == type)
	  {
	    اگر (درخت_رمز (قوت_نما.قدر) == NON_LVALUE_اظہاریہ)
	      not_lvalue = سچ;
	    قوت_نما.قدر = درخت_عملیہ (قوت_نما.قدر, 0);
	  }

	copy_warning (قوت_نما.قدر, orig_exp);

	lvalue_array_p = !not_lvalue && lvalue_p (قوت_نما.قدر);
	اگر (!flag_isoc99 && !lvalue_array_p)
	  {
	    /* Before C99, non-lvalue arrays do not decay to pointers.
	       Normally, using such an array would be invalid; but it can
	       be used correctly inside sizeof or as a statement expression.
	       Thus, do not give an error here; an error will result later.  */
	    واپس قوت_نما;
	  }

	قوت_نما.قدر = array_مقصد_اشارہ_گر_conversion (loc, قوت_نما.قدر);
      }
      توڑو;
    حالت FUNCTION_TYPE:
      قوت_نما.قدر = function_مقصد_اشارہ_گر_conversion (loc, قوت_نما.قدر);
      توڑو;
    طےشدہ:
      توڑو;
    }

  واپس قوت_نما;
}

ساخت c_اظہاریہ
default_function_array_read_conversion (location_t loc, ساخت c_اظہاریہ قوت_نما)
{
  mark_exp_read (قوت_نما.قدر);
  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  اگر (درخت_رمز (قوت_نما.قدر) == COMPONENT_REF
      && handle_counted_by_p (قوت_نما.قدر))
    قوت_نما.قدر = handle_counted_by_for_component_ref (loc, قوت_نما.قدر);
  واپس default_function_array_conversion (loc, قوت_نما);
}

/* Return whether EXPR should be treated as an atomic lvalue for the
   purposes of load and store handling.  */

ساکن منطقی
really_atomic_lvalue (درخت اظہاریہ)
{
  اگر (error_عملیہ_p (اظہاریہ))
    واپس جھوٹ;
  اگر (!TYPE_ATOMIC (درخت_TYPE (اظہاریہ)))
    واپس جھوٹ;
  اگر (!COMPLETE_TYPE_P (درخت_TYPE (اظہاریہ)))
    واپس جھوٹ;
  اگر (!lvalue_p (اظہاریہ))
    واپس جھوٹ;

  /* Ignore _Atomic on register variables, since their addresses can't
     be taken so (a) atomicity is irrelevant and (b) the normal atomic
     sequences wouldn't work.  Ignore _Atomic on structures containing
     bit-fields, since accessing elements of atomic structures or
     unions is undefined behavior (C11 6.5.2.3#5), but it's unclear if
     it's undefined at translation time or execution time, and the
     normal atomic sequences again wouldn't work.  */
  جب (handled_component_p (اظہاریہ))
    {
      اگر (درخت_رمز (اظہاریہ) == COMPONENT_REF
	  && DECL_C_ثنائی_ہندسہ_میدان (درخت_عملیہ (اظہاریہ, 1)))
	واپس جھوٹ;
      اظہاریہ = درخت_عملیہ (اظہاریہ, 0);
    }
  اگر (درخت_رمز (اظہاریہ) == COMPOUND_LITERAL_اظہاریہ)
    اظہاریہ = COMPOUND_LITERAL_اظہاریہ_DECL (اظہاریہ);
  اگر (DECL_P (اظہاریہ) && C_DECL_رجسٹر (اظہاریہ))
    واپس جھوٹ;
  واپس سچ;
}

/* If EXPR is a named constant (C23) derived from a constexpr variable
   - that is, a reference to such a variable, or a member extracted by
   a sequence of structure and union (but not array) member accesses
   (where union member accesses must access the same member as
   initialized) - then return the corresponding initializer;
   otherwise, return NULL_TREE.  */

ساکن درخت
maybe_get_constexpr_init (درخت اظہاریہ)
{
  درخت decl = NULL_درخت;
  اگر (درخت_رمز (اظہاریہ) == VAR_DECL)
    decl = اظہاریہ;
  ورنہ اگر (درخت_رمز (اظہاریہ) == COMPOUND_LITERAL_اظہاریہ)
    decl = COMPOUND_LITERAL_اظہاریہ_DECL (اظہاریہ);
  اگر (decl
      && C_DECL_DECLARED_CONSTEXPR (decl)
      && DECL_INITIAL (decl) != NULL_درخت
      && !error_عملیہ_p (DECL_INITIAL (decl)))
    واپس DECL_INITIAL (decl);
  اگر (درخت_رمز (اظہاریہ) != COMPONENT_REF)
    واپس NULL_درخت;
  درخت inner = maybe_get_constexpr_init (درخت_عملیہ (اظہاریہ, 0));
  اگر (inner == NULL_درخت)
    واپس NULL_درخت;
  جب ((CONVERT_اظہاریہ_P (inner) || درخت_رمز (inner) == NON_LVALUE_اظہاریہ)
	 && !error_عملیہ_p (inner)
	 && (TYPE_MAIN_VARIANT (درخت_TYPE (inner))
	     == TYPE_MAIN_VARIANT (درخت_TYPE (درخت_عملیہ (inner, 0)))))
    inner = درخت_عملیہ (inner, 0);
  اگر (درخت_رمز (inner) != CONSTRUCTOR)
    واپس NULL_درخت;
  درخت میدان_2 = درخت_عملیہ (اظہاریہ, 1);
  غیرعلامتی HOST_WIDE_INT cidx;
  درخت cfield, cvalue;
  منطقی have_other_init = جھوٹ;
  FOR_EACH_CONSTRUCTOR_ELT (CONSTRUCTOR_ELTS (inner), cidx, cfield, cvalue)
    {
      اگر (cfield == میدان_2)
	واپس cvalue;
      have_other_init = سچ;
    }
  اگر (درخت_رمز (درخت_TYPE (inner)) == UNION_TYPE
      && (have_other_init || میدان_2 != TYPE_FIELDS (درخت_TYPE (inner))))
    واپس NULL_درخت;
  /* Return a default initializer.  */
  اگر (ریکارڈ_OR_UNION_TYPE_P (درخت_TYPE (اظہاریہ)))
    واپس build_constructor (درخت_TYPE (اظہاریہ), تہی);
  واپس build_zero_cst (درخت_TYPE (اظہاریہ));
}

/* Helper function for convert_lvalue_to_rvalue called via
   walk_tree_without_duplicates.  Find DATA inside of the expression.  */

ساکن درخت
c_ڈھونڈو_var_r (درخت *tp, صحیح *walk_subtrees, خالی *ڈیٹا)
{
  اگر (TYPE_P (*tp))
    *walk_subtrees = 0;
  ورنہ اگر (*tp == (درخت) ڈیٹا)
    واپس *tp;
  واپس NULL_درخت;
}

/* Convert expression EXP (location LOC) from lvalue to rvalue,
   including converting functions and arrays to pointers if CONVERT_P.
   If READ_P, also mark the expression as having been read.  If
   FOR_INIT, constexpr expressions of structure and union type should
   be replaced by the corresponding CONSTRUCTOR; otherwise, only
   constexpr scalars (including elements of structures and unions) are
   replaced by their initializers.  */

ساخت c_اظہاریہ
convert_lvalue_مقصد_rvalue (location_t loc, ساخت c_اظہاریہ قوت_نما,
			  منطقی convert_p, منطقی read_p, منطقی for_init)
{
  منطقی force_non_npc = جھوٹ;
  اگر (read_p)
    mark_exp_read (قوت_نما.قدر);
  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  اگر (read_p && درخت_رمز (قوت_نما.قدر) == COMPONENT_REF
      && handle_counted_by_p (قوت_نما.قدر))
    قوت_نما.قدر = handle_counted_by_for_component_ref (loc, قوت_نما.قدر);

  اگر (convert_p)
    قوت_نما = default_function_array_conversion (loc, قوت_نما);
  اگر (!VOID_TYPE_P (درخت_TYPE (قوت_نما.قدر))
      || (flag_isoc2y
	  && TYPE_QUALS (درخت_TYPE (قوت_نما.قدر)) != TYPE_UNQUALIFIED))
    قوت_نما.قدر = require_complete_type (loc, قوت_نما.قدر);
  اگر (for_init || !ریکارڈ_OR_UNION_TYPE_P (درخت_TYPE (قوت_نما.قدر)))
    {
      درخت init = maybe_get_constexpr_init (قوت_نما.قدر);
      اگر (init != NULL_درخت)
	{
	  /* A named constant of pointer type or type nullptr_t is not
	     a null pointer constant even if the initializer is
	     one.  */
	  اگر (درخت_رمز (init) == INTEGER_CST
	      && !INTEGRAL_TYPE_P (درخت_TYPE (init))
	      && integer_zerop (init))
	    force_non_npc = سچ;
	  قوت_نما.قدر = init;
	}
    }
  اگر (really_atomic_lvalue (قوت_نما.قدر))
    {
      vec<درخت, va_gc> *params;
      درخت nonatomic_type, tmp, tmp_addr, fndecl, func_call;
      درخت اظہاریہ_type = درخت_TYPE (قوت_نما.قدر);
      درخت اظہاریہ_addr = build_unary_op (loc, ADDR_اظہاریہ, قوت_نما.قدر, جھوٹ);
      درخت seq_cst = build_int_cst (integer_type_گرہ, MEMMODEL_SEQ_CST);

      gcc_assert (TYPE_ATOMIC (اظہاریہ_type));

      /* Expansion of a generic atomic load may require an addition
	 element, so allocate enough to prevent a resize.  */
      vec_alloc (params, 4);

      /* Remove the qualifiers for the rest of the expressions and
	 create the VAL temp variable to hold the RHS.  */
      nonatomic_type = build_qualified_type (اظہاریہ_type, TYPE_UNQUALIFIED);
      tmp = create_tmp_var_raw (nonatomic_type);
      tmp_addr = build_unary_op (loc, ADDR_اظہاریہ, tmp, جھوٹ);
      درخت_ADDRESSABLE (tmp) = 1;
      /* Do not disable warnings for TMP even though it's artificial.
	 -Winvalid-memory-model depends on it.  */

      /* Issue __atomic_load (&expr, &tmp, SEQ_CST);  */
      fndecl = builtin_decl_explicit (BUILT_اندر_ATOMIC_بھرو);
      params->تیز_ڈالو (اظہاریہ_addr);
      params->تیز_ڈالو (tmp_addr);
      params->تیز_ڈالو (seq_cst);
      func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, تہی);

      /* EXPR is always read.  */
      mark_exp_read (قوت_نما.قدر);

      /* Optimize the common case where c_build_function_call_vec
	 immediately folds __atomic_load (&expr, &tmp, SEQ_CST); into
	 tmp = __atomic_load_<N> (&expr, SEQ_CST);
	 In that case tmp is not addressable and can be initialized
	 fully by the rhs of the MODIFY_EXPR.  */
      درخت tem = func_call;
      اگر (CONVERT_اظہاریہ_P (tem) && VOID_TYPE_P (درخت_TYPE (tem)))
	{
	  tem = درخت_عملیہ (tem, 0);
	  اگر (درخت_رمز (tem) == MODIFY_اظہاریہ
	      && درخت_عملیہ (tem, 0) == tmp
	      && !walk_درخت_without_duplicates (&درخت_عملیہ (tem, 1),
						c_ڈھونڈو_var_r, tmp))
	    {
	      درخت_ADDRESSABLE (tmp) = 0;
	      func_call = درخت_عملیہ (tem, 1);
	    }
	}

      /* Return tmp which contains the value loaded.  */
      قوت_نما.قدر = build4 (ہدف_اظہاریہ, nonatomic_type, tmp, func_call,
			  NULL_درخت, NULL_درخت);
    }
  اگر (convert_p && !error_عملیہ_p (قوت_نما.قدر)
      && (درخت_رمز (درخت_TYPE (قوت_نما.قدر)) != ARRAY_TYPE))
    قوت_نما.قدر = convert (build_qualified_type (درخت_TYPE (قوت_نما.قدر), TYPE_UNQUALIFIED), قوت_نما.قدر);
  اگر (force_non_npc)
    قوت_نما.قدر = build1 (NOP_اظہاریہ, درخت_TYPE (قوت_نما.قدر), قوت_نما.قدر);

  {
    درخت false_قدر, true_قدر;
    اگر (convert_p && !error_عملیہ_p (قوت_نما.قدر)
	&& c_hardbool_type_attr (درخت_TYPE (قوت_نما.قدر),
				 &false_قدر, &true_قدر))
      {
	درخت t = save_اظہاریہ (قوت_نما.قدر);

	mark_exp_read (قوت_نما.قدر);

	درخت trapfn = builtin_decl_explicit (BUILT_اندر_TRAP);
	درخت اظہاریہ = build_call_اظہاریہ_loc (loc, trapfn, 0);
	اظہاریہ = build_compound_اظہاریہ (loc, اظہاریہ, boolean_true_گرہ);
	اظہاریہ = fold_build3_loc (loc, COND_اظہاریہ, boolean_type_گرہ,
				fold_build2_loc (loc, NE_اظہاریہ,
						 boolean_type_گرہ,
						 t, true_قدر),
				اظہاریہ, boolean_true_گرہ);
	اظہاریہ = fold_build3_loc (loc, COND_اظہاریہ, boolean_type_گرہ,
				fold_build2_loc (loc, NE_اظہاریہ,
						 boolean_type_گرہ,
						 t, false_قدر),
				اظہاریہ, boolean_false_گرہ);

	قوت_نما.قدر = اظہاریہ;
      }
  }

  واپس قوت_نما;
}

/* Wrapper for the overload above, same arguments but for tree rather than
   c_expr.  This is important for hardbools to decay to bools.  */

ساکن اندرونی درخت
convert_lvalue_مقصد_rvalue (location_t loc, درخت val,
			  منطقی convert_p, منطقی read_p, منطقی for_init = جھوٹ)
{
  ساخت c_اظہاریہ اظہاریہ;
  memset (&اظہاریہ, 0, حجم (اظہاریہ));
  اظہاریہ.قدر = val;
  اظہاریہ = convert_lvalue_مقصد_rvalue (loc, اظہاریہ, convert_p, read_p, for_init);
  واپس اظہاریہ.قدر;
}

/* EXP is an expression of integer type.  Apply the integer promotions
   to it and return the promoted value.  */

درخت
perform_integral_promotions (درخت قوت_نما)
{
  درخت type = درخت_TYPE (قوت_نما);
  شمار درخت_رمز_2 رمز = درخت_رمز (type);

  gcc_assert (INTEGRAL_TYPE_P (type));

  /* Convert enums to the result of applying the integer promotions to
     their underlying type.  */
  اگر (رمز == ENUMERAL_TYPE)
    {
      type = ENUM_UNDERLYING_TYPE (type);
      اگر (c_promoting_integer_type_p (type))
	{
	  اگر (TYPE_UNSIGNED (type)
	      && TYPE_PRECISION (type) == TYPE_PRECISION (integer_type_گرہ))
	    type = unsigned_type_گرہ;
	  ورنہ
	    type = integer_type_گرہ;
	}

      واپس convert (type, قوت_نما);
    }

  /* ??? This should no longer be needed now bit-fields have their
     proper types.  */
  اگر (درخت_رمز (قوت_نما) == COMPONENT_REF
      && DECL_C_ثنائی_ہندسہ_میدان (درخت_عملیہ (قوت_نما, 1)))
    {
      اگر (BITINT_TYPE_P (DECL_ثنائی_ہندسہ_میدان_TYPE (درخت_عملیہ (قوت_نما, 1))))
	{
	  درخت btype = DECL_ثنائی_ہندسہ_میدان_TYPE (درخت_عملیہ (قوت_نما, 1));
	  اگر (درخت_رمز (btype) == BITINT_TYPE)
	    واپس convert (btype, قوت_نما);
	  ورنہ
	    واپس convert (ENUM_UNDERLYING_TYPE (btype), قوت_نما);
	}
      /* If it's thinner than an int, promote it like a
	 c_promoting_integer_type_p, otherwise leave it alone.  */
      اگر (compare_درخت_int (DECL_سائز (درخت_عملیہ (قوت_نما, 1)),
			    TYPE_PRECISION (integer_type_گرہ)) < 0)
	واپس convert (integer_type_گرہ, قوت_نما);
    }

  اگر (c_promoting_integer_type_p (type))
    {
      /* Preserve unsignedness if not really getting any wider.  */
      اگر (TYPE_UNSIGNED (type)
	  && TYPE_PRECISION (type) == TYPE_PRECISION (integer_type_گرہ))
	واپس convert (unsigned_type_گرہ, قوت_نما);

      واپس convert (integer_type_گرہ, قوت_نما);
    }

  واپس قوت_نما;
}


/* Perform default promotions for C data used in expressions.
   Enumeral types or short or char are converted to int.
   In addition, manifest constants symbols are replaced by their values.  */

درخت
default_conversion (درخت قوت_نما)
{
  درخت orig_exp;
  درخت type = درخت_TYPE (قوت_نما);
  شمار درخت_رمز_2 رمز = درخت_رمز (type);
  درخت promoted_type;

  mark_exp_read (قوت_نما);
  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  اگر (درخت_رمز (قوت_نما) == COMPONENT_REF
      && handle_counted_by_p (قوت_نما))
    قوت_نما = handle_counted_by_for_component_ref (اظہاریہ_LOCATION (قوت_نما), قوت_نما);

  /* Functions and arrays have been converted during parsing.  */
  gcc_assert (رمز != FUNCTION_TYPE);
  اگر (رمز == ARRAY_TYPE)
    واپس قوت_نما;

  /* Constants can be used directly unless they're not loadable.  */
  اگر (درخت_رمز (قوت_نما) == CONST_DECL)
    قوت_نما = DECL_INITIAL (قوت_نما);

  /* Strip no-op conversions.  */
  orig_exp = قوت_نما;
  STRIP_TYPE_NOPS (قوت_نما);

  copy_warning (قوت_نما, orig_exp);

  اگر (رمز == VOID_TYPE)
    {
      error_at (اظہاریہ_LOC_OR_LOC (قوت_نما, داخلہ_location),
		"void value not ignored as it ought to be");
      واپس error_mark_گرہ;
    }

  قوت_نما = require_complete_type (اظہاریہ_LOC_OR_LOC (قوت_نما, داخلہ_location), قوت_نما);
  اگر (قوت_نما == error_mark_گرہ)
    واپس error_mark_گرہ;

  promoted_type = targetm.promoted_type (type);
  اگر (promoted_type)
    واپس convert (promoted_type, قوت_نما);

  اگر (INTEGRAL_TYPE_P (type))
    {
      /* Avoid performing integral promotion of bit-precise integer
	 type bit-field to its corresponding bit-precise integer if
	 orig_exp is a cast to it to its underlying type.  */
      اگر (orig_exp != قوت_نما
	  && درخت_رمز (قوت_نما) == COMPONENT_REF
	  && DECL_C_ثنائی_ہندسہ_میدان (درخت_عملیہ (قوت_نما, 1))
	  && BITINT_TYPE_P (DECL_ثنائی_ہندسہ_میدان_TYPE (درخت_عملیہ (قوت_نما, 1))))
	واپس perform_integral_promotions (orig_exp);
      واپس perform_integral_promotions (قوت_نما);
    }

  واپس قوت_نما;
}

/* Look up COMPONENT in a structure or union TYPE.

   If the component name is not found, returns NULL_TREE.  Otherwise,
   the return value is a TREE_LIST, with each TREE_VALUE a FIELD_DECL
   stepping down the chain to the component, which is in the last
   TREE_VALUE of the list.  Normally the list is of length one, but if
   the component is embedded within (nested) anonymous structures or
   unions, the list steps down the chain to the component.  */

درخت
lookup_میدان (const_درخت type, درخت component)
{
  درخت میدان_2;

  /* If TYPE_LANG_SPECIFIC is set, then it is a sorted array of pointers
     to the field elements.  Use a binary search on this array to quickly
     find the element.  Otherwise, do a linear search.  TYPE_LANG_SPECIFIC
     will always be set for structures which have many elements.

     Duplicate field checking replaces duplicates with NULL_TREE so
     TYPE_LANG_SPECIFIC arrays are potentially no longer sorted.  In that
     case just iterate using DECL_CHAIN.  */

  اگر (TYPE_LANG_SPECIFIC (type) && TYPE_LANG_SPECIFIC (type)->s
      && !نظر_آیا_error ())
    {
      صحیح bot, چوٹی, half;
      درخت *میدان_array = &TYPE_LANG_SPECIFIC (type)->s->elts[0];

      میدان_2 = TYPE_FIELDS (type);
      bot = 0;
      چوٹی = TYPE_LANG_SPECIFIC (type)->s->len;
      جب (چوٹی - bot > 1)
	{
	  half = (چوٹی - bot + 1) >> 1;
	  میدان_2 = میدان_array[bot+half];

	  اگر (DECL_NAME (میدان_2) == NULL_درخت)
	    {
	      /* Step through all anon unions in linear fashion.  */
	      جب (DECL_NAME (میدان_array[bot]) == NULL_درخت)
		{
		  میدان_2 = میدان_array[bot++];
		  اگر (ریکارڈ_OR_UNION_TYPE_P (درخت_TYPE (میدان_2)))
		    {
		      درخت anon = lookup_میدان (درخت_TYPE (میدان_2), component);

		      اگر (anon)
			واپس درخت_cons (NULL_درخت, میدان_2, anon);

		      /* The Plan 9 compiler permits referring
			 directly to an anonymous struct/union field
			 using a typedef name.  */
		      اگر (flag_plan9_extensions
			  && TYPE_NAME (درخت_TYPE (میدان_2)) != NULL_درخت
			  && (درخت_رمز (TYPE_NAME (درخت_TYPE (میدان_2)))
			      == TYPE_DECL)
			  && (DECL_NAME (TYPE_NAME (درخت_TYPE (میدان_2)))
			      == component))
			توڑو;
		    }
		}

	      /* Entire record is only anon unions.  */
	      اگر (bot > چوٹی)
		واپس NULL_درخت;

	      /* Restart the binary search, with new lower bound.  */
	      جاری;
	    }

	  اگر (DECL_NAME (میدان_2) == component)
	    توڑو;
	  اگر (DECL_NAME (میدان_2) < component)
	    bot += half;
	  ورنہ
	    چوٹی = bot + half;
	}

      اگر (DECL_NAME (میدان_array[bot]) == component)
	میدان_2 = میدان_array[bot];
      ورنہ اگر (DECL_NAME (میدان_2) != component)
	واپس NULL_درخت;
    }
  ورنہ
    {
      برائے (میدان_2 = TYPE_FIELDS (type); میدان_2; میدان_2 = DECL_CHAIN (میدان_2))
	{
	  اگر (DECL_NAME (میدان_2) == NULL_درخت
	      && ریکارڈ_OR_UNION_TYPE_P (درخت_TYPE (میدان_2)))
	    {
	      درخت anon = lookup_میدان (درخت_TYPE (میدان_2), component);

	      اگر (anon)
		واپس درخت_cons (NULL_درخت, میدان_2, anon);

	      /* The Plan 9 compiler permits referring directly to an
		 anonymous struct/union field using a typedef
		 name.  */
	      اگر (flag_plan9_extensions
		  && TYPE_NAME (درخت_TYPE (میدان_2)) != NULL_درخت
		  && درخت_رمز (TYPE_NAME (درخت_TYPE (میدان_2))) == TYPE_DECL
		  && (DECL_NAME (TYPE_NAME (درخت_TYPE (میدان_2)))
		      == component))
		توڑو;
	    }

	  اگر (DECL_NAME (میدان_2) == component)
	    توڑو;
	}

      اگر (میدان_2 == NULL_درخت)
	واپس NULL_درخت;
    }

  واپس درخت_cons (NULL_درخت, میدان_2, NULL_درخت);
}

/* Recursively append candidate IDENTIFIER_NODEs to CANDIDATES.  */

ساکن خالی
lookup_میدان_fuzzy_ڈھونڈو_candidates (درخت type, درخت component,
				    vec<درخت> *candidates)
{
  درخت میدان_2;
  برائے (میدان_2 = TYPE_FIELDS (type); میدان_2; میدان_2 = DECL_CHAIN (میدان_2))
    {
      اگر (DECL_NAME (میدان_2) == NULL_درخت
	  && ریکارڈ_OR_UNION_TYPE_P (درخت_TYPE (میدان_2)))
	lookup_میدان_fuzzy_ڈھونڈو_candidates (درخت_TYPE (میدان_2), component,
					    candidates);

      اگر (DECL_NAME (میدان_2))
	candidates->محفوظ_ڈالو (DECL_NAME (میدان_2));
    }
}

/* Like "lookup_field", but find the closest matching IDENTIFIER_NODE,
   rather than returning a TREE_LIST for an exact match.  */

ساکن درخت
lookup_میدان_fuzzy (درخت type, درخت component)
{
  gcc_assert (درخت_رمز (component) == IDENTIFIER_گرہ);

  /* First, gather a list of candidates.  */
  auto_vec <درخت> candidates;

  lookup_میدان_fuzzy_ڈھونڈو_candidates (type, component,
				      &candidates);

  واپس ڈھونڈو_closest_identifier (component, &candidates);
}

/* Support function for build_component_ref's error-handling.

   Given DATUM_TYPE, and "DATUM.COMPONENT", where DATUM is *not* a
   struct or union, should we suggest "DATUM->COMPONENT" as a hint?  */

ساکن منطقی
should_suggest_deref_p (درخت datum_type)
{
  /* We don't do it for Objective-C, since Objective-C 2.0 dot-syntax
     allows "." for ptrs; we could be handling a failed attempt
     to access a property.  */
  اگر (c_dialect_objc ())
    واپس جھوٹ;

  /* Only suggest it for pointers...  */
  اگر (درخت_رمز (datum_type) != اشارہ_گر_TYPE)
    واپس جھوٹ;

  /* ...to structs/unions.  */
  درخت underlying_type = درخت_TYPE (datum_type);
  شمار درخت_رمز_2 رمز = درخت_رمز (underlying_type);
  اگر (رمز == ریکارڈ_TYPE || رمز == UNION_TYPE)
    واپس سچ;
  ورنہ
    واپس جھوٹ;
}

/* Give a component ref REF, decide whether we should handle its counted_by
   attribute based on its context:
   Do not handle counted_by when in offsetof, typeof and alignof operator.  */

ساکن منطقی
handle_counted_by_p (درخت ref)
{
  gcc_assert (درخت_رمز (ref) == COMPONENT_REF);
  درخت datum = درخت_عملیہ (ref, 0);
  /* If the component_ref is build for a offsetof, i.e., the datum
     of the component_ref is a indirect_ref of null_pointer_node,
     we should not generate call to .ACCESS_WITH_SIZE.  */
  اگر (درخت_رمز (datum) == بالواسطہ_REF
      && درخت_عملیہ (datum, 0) == null_اشارہ_گر_گرہ)
    واپس جھوٹ;
  اگر (اندر_typeof || اندر_alignof)
    واپس جھوٹ;
  واپس سچ;
}

/* Given a component ref REF, if there is a counted_by attribute attached,
   issue error when the element_type is a structure or union including a
   flexible array member.  */

ساکن خالی
check_counted_by_attribute (location_t loc, درخت ref)
{
  درخت subdatum = درخت_عملیہ (ref, 1);
  درخت sub_type = درخت_TYPE (subdatum);

  اگر (!flexible_array_member_type_p (sub_type)
      && درخت_رمز (sub_type) != اشارہ_گر_TYPE)
    واپس;

  درخت element_type = درخت_TYPE (sub_type);

  درخت attr_counted_by = lookup_attribute ("counted_by",
					   DECL_اوصاف (subdatum));
  اگر (attr_counted_by)
    {
      /* Issue error when the element_type is a structure or
	union including a flexible array member.  */
      اگر (ریکارڈ_OR_UNION_TYPE_P (element_type)
	  && TYPE_INCLUDES_FLEXARRAY (element_type))
	{
	  error_at (loc,
		    "%<counted_by%> attribute is not allowed for a pointer to"
		    " structure or union with flexible array member");
	  واپس;
	}
    }
}

/* For a SUBDATUM field of a structure or union DATUM, generate a REF
   to the object that represents its counted_by per the attribute
   counted_by attached to this field if it's a flexible array member
   or a pointer field, otherwise return NULL_TREE.
   Set COUNTED_BY_TYPE to the TYPE of the counted_by field.
   For example, if:

    struct P {
      int k;
      int x[] __attribute__ ((counted_by (k)));
    } *p;

    for:
    p->x

    the ref to the object that represents its element count will be:

    &(p->k)
*/

ساکن درخت
build_counted_by_ref (درخت datum, درخت subdatum,
		      درخت *counted_by_type)
{
  درخت sub_type = درخت_TYPE (subdatum);
  اگر (!flexible_array_member_type_p (sub_type)
      && درخت_رمز (sub_type) != اشارہ_گر_TYPE)
    واپس NULL_درخت;

  درخت attr_counted_by = lookup_attribute ("counted_by",
					   DECL_اوصاف (subdatum));
  اگر (!attr_counted_by)
    واپس NULL_درخت;

  درخت counted_by_ref = NULL_درخت;
  *counted_by_type = NULL_درخت;

  درخت type = درخت_TYPE (datum);

  /* If the type of the containing structure is an anonymous struct/union,
     and this anonymous struct/union is not a root type, get the first
     outer named structure/union type.  */
  جب (درخت_رمز (datum) == COMPONENT_REF
	 && c_type_لیبل (type) == NULL_درخت
	 && DECL_NAME (درخت_عملیہ (datum, 1)) == NULL_درخت)
    {
      datum = درخت_عملیہ (datum, 0);
      type = درخت_TYPE (datum);
    }

  درخت میدان_id = درخت_قدر (درخت_قدر (attr_counted_by));
  درخت counted_by_میدان = lookup_میدان (type, میدان_id);
  gcc_assert (counted_by_میدان);

  درخت counted_by_subdatum;
  کرو
    {
      counted_by_subdatum = درخت_قدر (counted_by_میدان);
      /* Get the TYPE of the counted_by field.  */
      *counted_by_type = درخت_TYPE (counted_by_subdatum);

      counted_by_ref
	= build3 (COMPONENT_REF, درخت_TYPE (counted_by_subdatum),
		  datum, counted_by_subdatum, NULL_درخت);

      datum = counted_by_ref;
      counted_by_میدان = درخت_CHAIN (counted_by_میدان);
    }
  جب (counted_by_میدان);

  counted_by_ref = build_fold_addr_اظہاریہ (counted_by_ref);
  واپس counted_by_ref;
}

/* Given a COMPONENT_REF REF with the location LOC, the corresponding
   COUNTED_BY_REF, and the COUNTED_BY_TYPE, generate the corresponding
   call to the internal function .ACCESS_WITH_SIZE.

   A: For the Flexible Array Member, Generate an INDIRECT_REF to a call to
   the internal function .ACCESS_WITH_SIZE.

   REF

   to:

   (*.ACCESS_WITH_SIZE (REF, COUNTED_BY_REF, (* TYPE_OF_SIZE)0,
			TYPE_SIZE_UNIT for element)

   NOTE: The return type of this function is the POINTER type pointing
   to the original flexible array type.  Then the type of the INDIRECT_REF
   is the original flexible array type.
   The type of the first argument of this function is a POINTER type
   to the original flexible array type.

   B: For pointers with counted_by, generate a call to the internal function
   .ACCESS_WITH_SIZE.

    REF

    to:

    .ACCESS_WITH_SIZE (REF, COUNTED_BY_REF, (* TYPE_OF_SIZE)0,
		       TYPE_SIZE_UNIT for element)

   NOTE: The return type of this function is the original pointer type.
   The type of the first argument of this function is the original
   pointer type.

   The 3rd argument of the call is a constant 0 with the pointer TYPE whose
   pointee type is the TYPE of the object pointed by COUNTED_BY_REF.

   The 4th argument of the call is the TYPE_SIZE_UNIT of the element TYPE
   of the array.

  */
ساکن درخت
build_access_with_سائز_for_counted_by (location_t loc, درخت ref,
				       درخت counted_by_ref,
				       درخت counted_by_type)
{
  gcc_assert (flexible_array_member_type_p (درخت_TYPE (ref))
	      || درخت_رمز (درخت_TYPE (ref)) == اشارہ_گر_TYPE);

  منطقی is_fam = flexible_array_member_type_p (درخت_TYPE (ref));

  /* The result type of the call is a pointer to the flexible array type;
     or is the original pointer type to the pointer field with counted_by.  */
  درخت نتیجہ_type = is_fam ? c_build_اشارہ_گر_type (درخت_TYPE (ref))
		     : درخت_TYPE (ref);

  درخت element_type = درخت_TYPE (درخت_TYPE (ref));
  درخت element_سائز = VOID_TYPE_P (element_type)
		      ? سائز_one_گرہ
		      : TYPE_سائز_UNIT (element_type);
  اگر (element_سائز == NULL_درخت)
    واپس ref;

  درخت پہلا_param = is_fam
		     ? c_fully_fold (array_مقصد_اشارہ_گر_conversion (loc, ref),
				     جھوٹ, تہی)
		     : c_fully_fold (ref, جھوٹ, تہی);
  درخت دوسرا_param
    = c_fully_fold (counted_by_ref, جھوٹ, تہی);
  درخت تیسرا_param = build_int_cst (c_build_اشارہ_گر_type (counted_by_type), 0);

  درخت call
    = build_call_اظہاریہ_اندرونی_loc (loc, IFN_ACCESS_WITH_سائز,
				    نتیجہ_type, 4,
				    پہلا_param,
				    دوسرا_param,
				    تیسرا_param,
				    element_سائز);

  /* Wrap the call with an INDIRECT_REF with the flexible array type.  */
  اگر (is_fam)
    call = build1 (بالواسطہ_REF, درخت_TYPE (ref), call);
  سیٹ_اظہاریہ_LOCATION (call, loc);
  واپس call;
}

/* For the COMPONENT_REF ref, check whether it has a counted_by attribute,
   if so, wrap this COMPONENT_REF with the corresponding CALL to the
   function .ACCESS_WITH_SIZE.
   Otherwise, return the ref itself.  */

درخت
handle_counted_by_for_component_ref (location_t loc, درخت ref)
{
  gcc_assert (درخت_رمز (ref) == COMPONENT_REF);
  درخت datum = درخت_عملیہ (ref, 0);
  درخت subdatum = درخت_عملیہ (ref, 1);
  درخت counted_by_type = NULL_درخت;

  اگر (!(flexible_array_member_type_p (درخت_TYPE (ref))
	|| درخت_رمز (درخت_TYPE (ref)) == اشارہ_گر_TYPE))
    واپس ref;

  درخت counted_by_ref = build_counted_by_ref (datum, subdatum,
					      &counted_by_type);
  اگر (counted_by_ref)
    ref = build_access_with_سائز_for_counted_by (loc, ref,
						 counted_by_ref,
						 counted_by_type);
  واپس ref;
}

/* Make an expression to refer to the COMPONENT field of structure or
   union value DATUM.  COMPONENT is an IDENTIFIER_NODE.  LOC is the
   location of the COMPONENT_REF.  COMPONENT_LOC is the location
   of COMPONENT.  ARROW_LOC is the location of the first -> operand if
   it is from -> operator.
   If HANDLE_COUNTED_BY is true, check the counted_by attribute and generate
   a call to .ACCESS_WITH_SIZE.  Otherwise, ignore the attribute.  */

درخت
build_component_ref (location_t loc, درخت datum, درخت component,
		     location_t component_loc, location_t arrow_loc)
{
  درخت type = درخت_TYPE (datum);
  شمار درخت_رمز_2 رمز = درخت_رمز (type);
  درخت میدان_2 = تہی;
  درخت ref;
  منطقی datum_lvalue = lvalue_p (datum);

  اگر (!objc_is_عوامی (datum, component))
    واپس error_mark_گرہ;

  /* Detect Objective-C property syntax object.property.  */
  اگر (c_dialect_objc ()
      && (ref = objc_maybe_build_component_ref (datum, component)))
    واپس ref;

  /* See if there is a field or component with name COMPONENT.  */

  اگر (رمز == ریکارڈ_TYPE || رمز == UNION_TYPE)
    {
      اگر (!COMPLETE_TYPE_P (type))
	{
	  c_incomplete_type_error (loc, NULL_درخت, type);
	  واپس error_mark_گرہ;
	}

      میدان_2 = lookup_میدان (type, component);

      اگر (!میدان_2)
	{
	  درخت guessed_id = lookup_میدان_fuzzy (type, component);
	  اگر (guessed_id)
	    {
	      /* Attempt to provide a fixit replacement hint, if
		 we have a valid range for the component.  */
	      location_t reported_loc
		= (component_loc != UNKNOWN_LOCATION) ? component_loc : loc;
	      gcc_rich_location rich_loc (reported_loc);
	      اگر (component_loc != UNKNOWN_LOCATION)
		rich_loc.جوڑو_fixit_misspelled_id (component_loc, guessed_id);
	      error_at (&rich_loc,
			"%qT has no member named %qE; did you mean %qE?",
			type, component, guessed_id);
	    }
	  ورنہ
	    error_at (loc, "%qT has no member named %qE", type, component);
	  واپس error_mark_گرہ;
	}

      /* Accessing elements of atomic structures or unions is undefined
	 behavior (C11 6.5.2.3#5).  */
      اگر (TYPE_ATOMIC (type) && c_inhibit_evaluation_warnings == 0)
	{
	  اگر (رمز == ریکارڈ_TYPE)
	    warning_at (loc, 0, "accessing a member %qE of an atomic "
			"structure %qE", component, datum);
	  ورنہ
	    warning_at (loc, 0, "accessing a member %qE of an atomic "
			"union %qE", component, datum);
	}

      /* Chain the COMPONENT_REFs if necessary down to the FIELD.
	 This might be better solved in future the way the C++ front
	 end does it - by giving the anonymous entities each a
	 separate name and type, and then have build_component_ref
	 recursively call itself.  We can't do that here.  */
      کرو
	{
	  درخت subdatum = درخت_قدر (میدان_2);
	  صحیح quals;
	  درخت subtype;
	  منطقی use_datum_quals;

	  اگر (درخت_TYPE (subdatum) == error_mark_گرہ)
	    واپس error_mark_گرہ;

	  /* If this is an rvalue, it does not have qualifiers in C
	     standard terms and we must avoid propagating such
	     qualifiers down to a non-lvalue array that is then
	     converted to a pointer.  */
	  use_datum_quals = (datum_lvalue
			     || درخت_رمز (درخت_TYPE (subdatum)) != ARRAY_TYPE);

	  quals = TYPE_QUALS (strip_array_types (درخت_TYPE (subdatum)));
	  اگر (use_datum_quals)
	    quals |= TYPE_QUALS (درخت_TYPE (datum));
	  subtype = c_build_qualified_type (درخت_TYPE (subdatum), quals);

	  ref = build3 (COMPONENT_REF, subtype, datum, subdatum,
			NULL_درخت);
	  سیٹ_اظہاریہ_LOCATION (ref, loc);

	  check_counted_by_attribute (loc, ref);

	  اگر (درخت_READONLY (subdatum)
	      || (use_datum_quals && درخت_READONLY (datum)))
	    درخت_READONLY (ref) = 1;
	  اگر (درخت_THIS_VOLATILE (subdatum)
	      || (use_datum_quals && درخت_THIS_VOLATILE (datum)))
	    درخت_THIS_VOLATILE (ref) = 1;

	  اگر (درخت_UNAVAILABLE (subdatum))
	    error_unavailable_use (subdatum, NULL_درخت);
	  ورنہ اگر (درخت_DEPRECATED (subdatum))
	    warn_deprecated_use (subdatum, NULL_درخت);

	  datum = ref;

	  میدان_2 = درخت_CHAIN (میدان_2);
	}
      جب (میدان_2);

      واپس ref;
    }
  ورنہ اگر (should_suggest_deref_p (type))
    {
      /* Special-case the error message for "ptr.field" for the case
	 where the user has confused "." vs "->".  */
      rich_location richloc (سطر_جدول, loc);
      اگر (بالواسطہ_REF_P (datum) && arrow_loc != UNKNOWN_LOCATION)
	{
	  richloc.جوڑو_fixit_داخل_کرو_before (arrow_loc, "(*");
	  richloc.جوڑو_fixit_داخل_کرو_after (arrow_loc, ")");
	  error_at (&richloc,
		    "%qE is a pointer to pointer; did you mean to dereference "
		    "it before applying %<->%> to it?",
		    درخت_عملیہ (datum, 0));
	}
      ورنہ
	{
	  /* "loc" should be the "." token.  */
	  richloc.جوڑو_fixit_replace ("->");
	  error_at (&richloc,
		    "%qE is a pointer; did you mean to use %<->%>?",
		    datum);
	}
      واپس error_mark_گرہ;
    }
  ورنہ اگر (رمز != ERROR_MARK)
    error_at (loc,
	      "request for member %qE in something not a structure or union",
	      component);

  واپس error_mark_گرہ;
}

/* Given an expression PTR for a pointer, return an expression
   for the value pointed to.
   ERRORSTRING is the name of the operator to appear in error messages.

   LOC is the location to use for the generated tree.  */

درخت
build_بالواسطہ_ref (location_t loc, درخت ptr, ref_operator errstring)
{
  درخت اشارہ_گر = default_conversion (ptr);
  درخت type = درخت_TYPE (اشارہ_گر);
  درخت ref;

  اگر (درخت_رمز (type) == اشارہ_گر_TYPE)
    {
      اگر (CONVERT_اظہاریہ_P (اشارہ_گر)
          || درخت_رمز (اشارہ_گر) == VIEW_CONVERT_اظہاریہ)
	{
	  /* If a warning is issued, mark it to avoid duplicates from
	     the backend.  This only needs to be done at
	     warn_strict_aliasing > 2.  */
	  اگر (warn_strict_aliasing > 2)
	    اگر (strict_aliasing_warning (اظہاریہ_LOCATION (اشارہ_گر),
					 type, درخت_عملیہ (اشارہ_گر, 0)))
	      suppress_warning (اشارہ_گر, OPT_Wstrict_aliasing_);
	}

      اگر (درخت_رمز (اشارہ_گر) == ADDR_اظہاریہ
	  && (درخت_TYPE (درخت_عملیہ (اشارہ_گر, 0))
	      == درخت_TYPE (type)))
	{
	  ref = درخت_عملیہ (اشارہ_گر, 0);
	  protected_سیٹ_اظہاریہ_location (ref, loc);
	  واپس ref;
	}
      ورنہ
	{
	  درخت t = درخت_TYPE (type);

	  ref = build1 (بالواسطہ_REF, t, اشارہ_گر);

	  اگر (VOID_TYPE_P (t) && c_inhibit_evaluation_warnings == 0)
	    warning_at (loc, 0, "dereferencing %<void *%> pointer");

	  /* We *must* set TREE_READONLY when dereferencing a pointer to const,
	     so that we get the proper error message if the result is used
	     to assign to.  Also, &* is supposed to be a no-op.
	     And ANSI C seems to specify that the type of the result
	     should be the const type.  */
	  /* A de-reference of a pointer to const is not a const.  It is valid
	     to change it via some other pointer.  */
	  درخت_READONLY (ref) = TYPE_READONLY (t);
	  درخت_SIDE_EFFECTS (ref)
	    = TYPE_VOLATILE (t) || درخت_SIDE_EFFECTS (اشارہ_گر);
	  درخت_THIS_VOLATILE (ref) = TYPE_VOLATILE (t);
	  protected_سیٹ_اظہاریہ_location (ref, loc);
	  واپس ref;
	}
    }
  ورنہ اگر (درخت_رمز (اشارہ_گر) != ERROR_MARK)
    invalid_indirection_error (loc, type, errstring);

  واپس error_mark_گرہ;
}

/* This handles expressions of the form "a[i]", which denotes
   an array reference.

   This is logically equivalent in C to *(a+i), but we may do it differently.
   If A is a variable or a member, we generate a primitive ARRAY_REF.
   This avoids forcing the array out of registers, and can work on
   arrays that are not lvalues (for example, members of structures returned
   by functions).

   For vector types, allow vector[i] but not i[vector], and create
   *(((type*)&vectortype) + i) for the expression.

   LOC is the location to use for the returned expression.  */

درخت
build_array_ref (location_t loc, درخت array, درخت اشاریہ)
{
  درخت ret;
  منطقی swapped = جھوٹ;
  اگر (درخت_TYPE (array) == error_mark_گرہ
      || درخت_TYPE (اشاریہ) == error_mark_گرہ)
    واپس error_mark_گرہ;

  اگر (درخت_رمز (درخت_TYPE (array)) != ARRAY_TYPE
      && درخت_رمز (درخت_TYPE (array)) != اشارہ_گر_TYPE
      /* Allow vector[index] but not index[vector].  */
      && !gnu_سمتیہ_type_p (درخت_TYPE (array)))
    {
      اگر (درخت_رمز (درخت_TYPE (اشاریہ)) != ARRAY_TYPE
	  && درخت_رمز (درخت_TYPE (اشاریہ)) != اشارہ_گر_TYPE)
	{
          error_at (loc,
            "subscripted value is neither array nor pointer nor vector");

	  واپس error_mark_گرہ;
	}
      std::تبادلہ (array, اشاریہ);
      swapped = سچ;
    }

  اگر (!INTEGRAL_TYPE_P (درخت_TYPE (اشاریہ)))
    {
      error_at (loc, "array subscript is not an integer");
      واپس error_mark_گرہ;
    }

  اگر (درخت_رمز (درخت_TYPE (درخت_TYPE (array))) == FUNCTION_TYPE)
    {
      error_at (loc, "subscripted value is pointer to function");
      واپس error_mark_گرہ;
    }

  /* ??? Existing practice has been to warn only when the char
     index is syntactically the index, not for char[array].  */
  اگر (!swapped)
     warn_array_subscript_with_type_char (loc, اشاریہ);

  /* Apply default promotions *after* noticing character types.  */
  اشاریہ = default_conversion (اشاریہ);
  اگر (اشاریہ == error_mark_گرہ)
    واپس error_mark_گرہ;

  gcc_assert (درخت_رمز (درخت_TYPE (اشاریہ)) == INTEGER_TYPE
	      || درخت_رمز (درخت_TYPE (اشاریہ)) == BITINT_TYPE);

  منطقی was_سمتیہ = سمتیہ_TYPE_P (درخت_TYPE (array));
  منطقی non_lvalue = convert_سمتیہ_مقصد_array_for_subscript (loc, &array, اشاریہ);

  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  اگر (درخت_رمز (array) == COMPONENT_REF
      && handle_counted_by_p (array))
    array = handle_counted_by_for_component_ref (loc, array);

  اگر (درخت_رمز (درخت_TYPE (array)) == ARRAY_TYPE)
    {
      درخت rval, type;

      /* An array that is indexed by a non-constant
	 cannot be stored in a register; we must be able to do
	 address arithmetic on its address.
	 Likewise an array of elements of variable size.  */
      اگر (درخت_رمز (اشاریہ) != INTEGER_CST
	  || (COMPLETE_TYPE_P (درخت_TYPE (درخت_TYPE (array)))
	      && درخت_رمز (TYPE_سائز (درخت_TYPE (درخت_TYPE (array)))) != INTEGER_CST))
	{
	  اگر (!c_mark_addressable (array, سچ, سچ))
	    واپس error_mark_گرہ;
	}
      /* An array that is indexed by a constant value which is not within
	 the array bounds cannot be stored in a register either; because we
	 would get a crash in store_bit_field/extract_bit_field when trying
	 to access a non-existent part of the register.  */
      اگر (درخت_رمز (اشاریہ) == INTEGER_CST
	  && TYPE_DOMAIN (درخت_TYPE (array))
	  && !int_سماتا_type_p (اشاریہ, TYPE_DOMAIN (درخت_TYPE (array))))
	{
	  اگر (!c_mark_addressable (array, جھوٹ, سچ))
	    واپس error_mark_گرہ;
	  /* ISO C2Y disallows a negative integer constant expression index
	     when array subscripting has an operand of array type.  */
	  اگر (flag_isoc2y
	      && !درخت_حد_سے_تجاوز (اشاریہ)
	      && درخت_int_cst_sgn (اشاریہ) < 0)
	    error_at (loc, "array subscript is negative");
	}

      اگر ((pedantic || warn_c90_c99_compat || warn_c23_c2y_compat)
	  && ! was_سمتیہ)
	{
	  درخت foo = array;
	  جب (درخت_رمز (foo) == COMPONENT_REF)
	    foo = درخت_عملیہ (foo, 0);
	  اگر ((VAR_P (foo) && C_DECL_رجسٹر (foo))
	      || (درخت_رمز (foo) == COMPOUND_LITERAL_اظہاریہ
		  && C_DECL_رجسٹر (COMPOUND_LITERAL_اظہاریہ_DECL (foo))))
	    pedwarn_c23 (loc, OPT_Wpedantic,
			 "ISO C forbids subscripting %<register%> array "
			 "before C2Y");
	  ورنہ اگر (!lvalue_p (foo))
	    pedwarn_c90 (loc, OPT_Wpedantic,
			 "ISO C90 forbids subscripting non-lvalue "
			 "array");
	}

      اگر (درخت_رمز (درخت_TYPE (اشاریہ)) == BITINT_TYPE
	  && TYPE_PRECISION (درخت_TYPE (اشاریہ)) > TYPE_PRECISION (sizetype))
	اشاریہ = fold_convert (sizetype, اشاریہ);

      type = درخت_TYPE (درخت_TYPE (array));
      rval = build4 (ARRAY_REF, type, array, اشاریہ, NULL_درخت, NULL_درخت);
      /* Array ref is const/volatile if the array elements are
	 or if the array is.  */
      درخت_READONLY (rval)
	|= (TYPE_READONLY (درخت_TYPE (درخت_TYPE (array)))
	    | درخت_READONLY (array));
      درخت_SIDE_EFFECTS (rval)
	|= (TYPE_VOLATILE (درخت_TYPE (درخت_TYPE (array)))
	    | درخت_SIDE_EFFECTS (array));
      درخت_THIS_VOLATILE (rval)
	|= (TYPE_VOLATILE (درخت_TYPE (درخت_TYPE (array)))
	    /* This was added by rms on 16 Nov 91.
	       It fixes  vol struct foo *a;  a->elts[1]
	       in an inline function.
	       Hope it doesn't break something else.  */
	    | درخت_THIS_VOLATILE (array));
      ret = require_complete_type (loc, rval);
      protected_سیٹ_اظہاریہ_location (ret, loc);
      اگر (non_lvalue)
	ret = non_lvalue_loc (loc, ret);
      واپس ret;
    }
  ورنہ
    {
      درخت ar = default_conversion (array);

      اگر (ar == error_mark_گرہ)
	واپس ar;

      gcc_assert (درخت_رمز (درخت_TYPE (ar)) == اشارہ_گر_TYPE);
      gcc_assert (درخت_رمز (درخت_TYPE (درخت_TYPE (ar))) != FUNCTION_TYPE);

      ret = build_بالواسطہ_ref (loc, build_ثنائی_op (loc, PLUS_اظہاریہ, ar,
						      اشاریہ, جھوٹ),
				RO_ARRAY_INDEXING);
      اگر (non_lvalue)
	ret = non_lvalue_loc (loc, ret);
      واپس ret;
    }
}

/* Build an OpenMP array section reference, creating an exact type for the
   resulting expression based on the element type and bounds if possible.  If
   we have variable bounds, create an incomplete array type for the result
   instead.  */

درخت
build_omp_array_section (location_t loc, درخت array, درخت اشاریہ, درخت لمبائی)
{
  درخت type = درخت_TYPE (array);
  gcc_assert (type);

  درخت sectype, eltype = درخت_TYPE (type);

  /* It's not an array or pointer type.  Just reuse the type of the original
     expression as the type of the array section (an error will be raised
     anyway, later).  */
  اگر (eltype == NULL_درخت || error_عملیہ_p (eltype))
    sectype = درخت_TYPE (array);
  ورنہ
    {
      درخت idxtype = NULL_درخت;

      اگر (اشاریہ != NULL_درخت
	  && لمبائی != NULL_درخت
	  && INTEGRAL_TYPE_P (درخت_TYPE (اشاریہ))
	  && INTEGRAL_TYPE_P (درخت_TYPE (لمبائی)))
	{
	  درخت کم = fold_convert (sizetype, اشاریہ);
	  درخت بلند = fold_convert (sizetype, لمبائی);
	  بلند = سائز_binop (PLUS_اظہاریہ, کم, بلند);
	  بلند = سائز_binop (MINUS_اظہاریہ, بلند, سائز_one_گرہ);
	  idxtype = build_range_type (sizetype, کم, بلند);
	}
      ورنہ اگر ((اشاریہ == NULL_درخت || integer_zerop (اشاریہ))
	       && لمبائی != NULL_درخت
	       && INTEGRAL_TYPE_P (درخت_TYPE (لمبائی)))
	idxtype = build_اشاریہ_type (لمبائی);

      gcc_assert (!error_عملیہ_p (idxtype));

      sectype = c_build_array_type (eltype, idxtype);
    }

  واپس build3_loc (loc, OMP_ARRAY_SECTION, sectype, array, اشاریہ, لمبائی);
}


/* Record that REF is used.  This is relevant for undeclared static
   function and declarations referenced from a non-local context.
   ADDRESS indicates whether the address is taken.  */

خالی
mark_decl_مستعمل (درخت ref, منطقی پتہ)
{
  اگر (!ref || !DECL_P (ref) || اندر_alignof)
    واپس;

  /* Non-file-scope and non-local reference in nested function.  */
  منطقی nonloc_p = current_function_decl && DECL_CONTEXT (ref)
		  && DECL_CONTEXT (current_function_decl)
		  && DECL_CONTEXT (ref) != current_function_decl;

  /* An undeclared static function.  */
  منطقی static_p = درخت_رمز (ref) == FUNCTION_DECL
		  && DECL_INITIAL (ref) == NULL_درخت
		  && DECL_EXTERNAL (ref)
		  && !درخت_عوامی (ref);

  اگر (!static_p && !nonloc_p)
    واپس;

  /* If we may be in an unevaluated context, delay the decision.  */
  اگر (اندر_sizeof || اندر_typeof || اندر_countof || اندر_generic)
    واپس ریکارڈ_maybe_مستعمل_decl (ref, پتہ);

  اگر (static_p)
    C_DECL_مستعمل (ref) = 1;

  اگر (nonloc_p && (VAR_OR_FUNCTION_DECL_P (ref)
		   || درخت_رمز (ref) == PARM_DECL))
    DECL_NONLOCAL (ref) = 1;

  /* Nothing to do anymore.  */
  اگر (!nonloc_p || C_FUNC_NONLOCAL_CONTEXT (current_function_decl))
    واپس;

  /* Filter out the cases where referencing a non-local variable does not
     require a non-local context passed via the static chain.  */
  اگر (!c_type_variably_modified_p (درخت_TYPE (ref)))
    انتخاب (درخت_رمز (ref))
      {
      حالت FUNCTION_DECL:
	/* Use of another local function that requires no context is ok.  */
	اگر (!C_FUNC_NONLOCAL_CONTEXT (ref) && DECL_INITIAL (ref))
	  واپس;
	توڑو;
      حالت VAR_DECL:
	/* Static variables and constexpr are ok, but for the later only
	   when the address is not taken.  */
	اگر (درخت_STATIC (ref) || (C_DECL_DECLARED_CONSTEXPR (ref) && !پتہ))
	  واپس;
	توڑو;
      حالت TYPE_DECL:
	/* A typedef is ok when not for a variably-modified type. */
	واپس;
      حالت CONST_DECL:
	/* An enumeration constant is ok. */
	واپس;
      حالت PARM_DECL:
	توڑو;
      حالت LABEL_DECL:
	توڑو;
      طےشدہ:
	gcc_unreachable ();
    }

  /* Mark all parent functions up to the nesting level of the variable as
     as needing the non-local context.  */
  برائے (درخت cont = current_function_decl; cont; cont = DECL_CONTEXT (cont))
    {
      اگر (cont == DECL_CONTEXT (ref))
	توڑو;

      /* There should not be any other type of context used for function
	 except TRANSLATION_UNIT_DECL which we should be able to reach.  */
      gcc_checking_assert (درخت_رمز (cont) == FUNCTION_DECL);

      اگر (درخت_رمز (cont) == FUNCTION_DECL)
	C_FUNC_NONLOCAL_CONTEXT (cont) = 1;
    }
}


/* Build an external reference to identifier ID.  FUN indicates
   whether this will be used for a function call.  LOC is the source
   location of the identifier.  This sets *TYPE to the type of the
   identifier, which is not the same as the type of the returned value
   for CONST_DECLs defined as enum constants.  If the type of the
   identifier is not available, *TYPE is set to NULL.  */
درخت
build_external_ref (location_t loc, درخت id, منطقی fun, درخت *type)
{
  درخت ref;
  درخت decl = lookup_name (id);

  /* In Objective-C, an instance variable (ivar) may be preferred to
     whatever lookup_name() found.  */
  decl = objc_lookup_ivar (decl, id);

  *type = تہی;
  اگر (decl && decl != error_mark_گرہ)
    {
      ref = decl;
      *type = درخت_TYPE (ref);
      اگر (DECL_P (decl) && C_DECL_UNDERSPECIFIED (decl))
	error_at (loc, "underspecified %qD referenced in its initializer",
		  decl);
    }
  ورنہ اگر (fun)
    /* Implicit function declaration.  */
    ref = implicitly_declare (loc, id);
  ورنہ اگر (decl == error_mark_گرہ)
    /* Don't complain about something that's already been
       complained about.  */
    واپس error_mark_گرہ;
  ورنہ
    {
      undeclared_variable (loc, id);
      واپس error_mark_گرہ;
    }

  /* For an OpenMP map clause, we can get better diagnostics for decls with
     unmappable types if we return the decl with an error_mark_node type,
     rather than returning error_mark_node for the decl itself.  */
  اگر (درخت_TYPE (ref) == error_mark_گرہ
      && !c_omp_array_section_p)
    واپس error_mark_گرہ;

  اگر (درخت_UNAVAILABLE (ref))
    error_unavailable_use (ref, NULL_درخت);
  ورنہ اگر (درخت_DEPRECATED (ref))
    warn_deprecated_use (ref, NULL_درخت);

  /* Recursive call does not count as usage.  */
  اگر (ref != current_function_decl)
    {
      درخت_مستعمل (ref) = 1;
    }

  mark_decl_مستعمل (ref, جھوٹ);

  اگر (درخت_رمز (ref) == CONST_DECL)
    {
      مستعمل_types_داخل_کرو (درخت_TYPE (ref));

      اگر (warn_cxx_compat
	  && درخت_رمز (درخت_TYPE (ref)) == ENUMERAL_TYPE
	  && C_TYPE_DEFINED_اندر_STRUCT (درخت_TYPE (ref)))
	{
	  warning_at (loc, OPT_Wc___compat,
		      "enum constant defined in struct or union "
		      "is not visible in C++");
	  inform (DECL_ماخذ_LOCATION (ref), "enum constant defined here");
	}

      ref = DECL_INITIAL (ref);
      درخت_CONSTANT (ref) = 1;
    }
  /* C99 6.7.4p3: An inline definition of a function with external
     linkage ... shall not contain a reference to an identifier with
     internal linkage.  */
  ورنہ اگر (current_function_decl != NULL_درخت
	   && DECL_DECLARED_INLINE_P (current_function_decl)
	   && DECL_EXTERNAL (current_function_decl)
	   && VAR_OR_FUNCTION_DECL_P (ref)
	   && (!VAR_P (ref) || درخت_STATIC (ref))
	   && ! درخت_عوامی (ref)
	   && DECL_CONTEXT (ref) != current_function_decl)
    ریکارڈ_inline_static (loc, current_function_decl, ref,
			  csi_اندرونی);

  واپس ref;
}

ساکن ساخت maybe_مستعمل_decl *maybe_مستعمل_decls;

/* Record that DECL, a reference seen inside sizeof or typeof or _Countof or
   _Generic, might be used if the operand of sizeof is a VLA type or the
   operand of typeof is a variably modified type or the operand of _Countof has
   a variable number of elements or the operand of _Generic is the one selected
   as the result.  */

ساکن خالی
ریکارڈ_maybe_مستعمل_decl (درخت decl, منطقی پتہ)
{
  ساخت maybe_مستعمل_decl *t = XOBNEW (&parser_obstack, ساخت maybe_مستعمل_decl);
  t->decl = decl;
  t->level = اندر_sizeof + اندر_typeof + اندر_countof + اندر_generic;
  t->پتہ = پتہ;
  t->اگلا = maybe_مستعمل_decls;
  maybe_مستعمل_decls = t;
}

/* Pop the stack of decls possibly used inside sizeof or typeof or _Countof or
   _Generic.  If USED is false, just discard them.  If it is true, mark them
   used (if no longer inside sizeof or typeof or _Countof or _Generic) or move
   them to the next level up (if still inside sizeof or typeof or _Countof or
   _Generic).  */

خالی
نکالو_maybe_مستعمل (منطقی مستعمل)
{
  ساخت maybe_مستعمل_decl *p = maybe_مستعمل_decls;
  صحیح cur_level = اندر_sizeof + اندر_typeof + اندر_countof + اندر_generic;
  جب (p && p->level > cur_level)
    {
      اگر (مستعمل)
	{
	  اگر (cur_level == 0)
	    mark_decl_مستعمل (p->decl, p->پتہ);
	  ورنہ
	    p->level = cur_level;
	}
      p = p->اگلا;
    }
  اگر (!مستعمل || cur_level == 0)
    maybe_مستعمل_decls = p;
}

/* Pop the stack of decls possibly used inside sizeof or typeof or _Countof or
   _Generic, without acting on them, and return the pointer to the previous top
   of the stack.  This for use at the end of a default generic association when
   it is not yet known whether the expression is used.  If it later turns out
   the expression is used (or treated as used before C23), restore_maybe_used
   should be called on the return value followed by pop_maybe_used (true);
   otherwise, the return value can be discarded.  */

ساخت maybe_مستعمل_decl *
save_maybe_مستعمل ()
{
  ساخت maybe_مستعمل_decl *p = maybe_مستعمل_decls, *orig = p;
  صحیح cur_level = اندر_sizeof + اندر_typeof + اندر_countof + اندر_generic;
  جب (p && p->level > cur_level)
    p = p->اگلا;
  maybe_مستعمل_decls = p;
  واپس orig;
}

/* Restore the stack of decls possibly used inside sizeof or typeof or _Countof
   or _Generic returned by save_maybe_used.  It is required that the stack is
   at exactly the point where it was left by save_maybe_used.  */

خالی
restore_maybe_مستعمل (ساخت maybe_مستعمل_decl *ڈھیر)
{
  maybe_مستعمل_decls = ڈھیر;
}

/* Return the result of sizeof applied to EXPR.  */

ساخت c_اظہاریہ
c_اظہاریہ_sizeof_اظہاریہ (location_t loc, ساخت c_اظہاریہ اظہاریہ)
{
  ساخت c_اظہاریہ ret;
  اگر (اظہاریہ.قدر == error_mark_گرہ)
    {
      ret.قدر = error_mark_گرہ;
      ret.original_رمز = ERROR_MARK;
      ret.original_type = تہی;
      ret.m_decimal = 0;
      نکالو_maybe_مستعمل (جھوٹ);
    }
  ورنہ
    {
      منطقی اظہاریہ_const_operands = سچ;

      اگر (درخت_رمز (اظہاریہ.قدر) == PARM_DECL
	  && C_ARRAY_PARAMETER (اظہاریہ.قدر))
	{
	  auto_diagnostic_گروہ d;
	  اگر (warning_at (loc, OPT_Wsizeof_array_دلیل,
			  "%<sizeof%> on array function parameter %qE will "
			  "return size of %qT", اظہاریہ.قدر,
			  درخت_TYPE (اظہاریہ.قدر)))
	    inform (DECL_ماخذ_LOCATION (اظہاریہ.قدر), "declared here");
	}
      درخت folded_اظہاریہ = c_fully_fold (اظہاریہ.قدر, require_constant_قدر,
				       &اظہاریہ_const_operands);
      ret.قدر = c_sizeof (loc, درخت_TYPE (folded_اظہاریہ));
      c_آخری_sizeof_arg = اظہاریہ.قدر;
      c_آخری_sizeof_loc = loc;
      ret.original_رمز = SIZEOF_اظہاریہ;
      ret.original_type = تہی;
      ret.m_decimal = 0;
      اگر (C_TYPE_VARIABLE_سائز (درخت_TYPE (folded_اظہاریہ)))
	{
	  /* sizeof is evaluated when given a vla (C99 6.5.3.4p2).  */
	  ret.قدر = build2 (C_MAYBE_CONST_اظہاریہ, درخت_TYPE (ret.قدر),
			      folded_اظہاریہ, ret.قدر);
	  C_MAYBE_CONST_اظہاریہ_NON_CONST (ret.قدر) = !اظہاریہ_const_operands;
	  سیٹ_اظہاریہ_LOCATION (ret.قدر, loc);
	}
      نکالو_maybe_مستعمل (C_TYPE_VARIABLE_سائز (درخت_TYPE (folded_اظہاریہ)));
    }
  واپس ret;
}

/* Return the result of sizeof applied to T, a structure for the type
   name passed to sizeof (rather than the type itself).  LOC is the
   location of the original expression.  */

ساخت c_اظہاریہ
c_اظہاریہ_sizeof_type (location_t loc, ساخت c_type_name *t)
{
  درخت type;
  ساخت c_اظہاریہ ret;
  درخت type_اظہاریہ = NULL_درخت;
  منطقی type_اظہاریہ_const = سچ;
  type = groktypename (t, &type_اظہاریہ, &type_اظہاریہ_const);
  ret.قدر = c_sizeof (loc, type);
  c_آخری_sizeof_arg = type;
  c_آخری_sizeof_loc = loc;
  ret.original_رمز = SIZEOF_اظہاریہ;
  ret.original_type = تہی;
  ret.m_decimal = 0;
  اگر (type == error_mark_گرہ)
    {
      ret.قدر = error_mark_گرہ;
      ret.original_رمز = ERROR_MARK;
    }
  ورنہ
  اگر ((type_اظہاریہ || درخت_رمز (ret.قدر) == INTEGER_CST)
      && C_TYPE_VARIABLE_سائز (type))
    {
      /* If the type is a [*] array, it is a VLA but is represented as
	 having a size of zero.  In such a case we must ensure that
	 the result of sizeof does not get folded to a constant by
	 c_fully_fold, because if the size is evaluated the result is
	 not constant and so constraints on zero or negative size
	 arrays must not be applied when this sizeof call is inside
	 another array declarator.  */
      اگر (!type_اظہاریہ)
	type_اظہاریہ = integer_zero_گرہ;
      ret.قدر = build2 (C_MAYBE_CONST_اظہاریہ, درخت_TYPE (ret.قدر),
			  type_اظہاریہ, ret.قدر);
      C_MAYBE_CONST_اظہاریہ_NON_CONST (ret.قدر) = !type_اظہاریہ_const;
    }
  نکالو_maybe_مستعمل (type != error_mark_گرہ
		  ? C_TYPE_VARIABLE_سائز (type) : جھوٹ);
  واپس ret;
}

ساکن منطقی
چوٹی_array_vla_p (const_درخت type)
{
  اگر (درخت_رمز (type) != ARRAY_TYPE)
    واپس جھوٹ;

  درخت d = TYPE_DOMAIN (type);

  اگر (!d)
    واپس جھوٹ;
  اگر (!TYPE_MAX_قدر (d))
    واپس جھوٹ;

  واپس درخت_رمز (TYPE_MAX_قدر (d)) != INTEGER_CST
	 || درخت_رمز (TYPE_MIN_قدر (d)) != INTEGER_CST;
}

/* Return the result of countof applied to EXPR.  */

ساخت c_اظہاریہ
c_اظہاریہ_countof_اظہاریہ (location_t loc, ساخت c_اظہاریہ اظہاریہ)
{
  ساخت c_اظہاریہ ret;
  اگر (اظہاریہ.قدر == error_mark_گرہ)
    {
      ret.قدر = error_mark_گرہ;
      ret.original_رمز = ERROR_MARK;
      ret.original_type = تہی;
      ret.m_decimal = 0;
      نکالو_maybe_مستعمل (جھوٹ);
    }
  ورنہ
    {
      منطقی اظہاریہ_const_operands = سچ;

      درخت folded_اظہاریہ = c_fully_fold (اظہاریہ.قدر, require_constant_قدر,
				       &اظہاریہ_const_operands);
      ret.قدر = c_countof_type (loc, درخت_TYPE (folded_اظہاریہ));
      c_آخری_sizeof_arg = اظہاریہ.قدر;
      c_آخری_sizeof_loc = loc;
      ret.original_رمز = COUNTOF_اظہاریہ;
      ret.original_type = تہی;
      ret.m_decimal = 0;
      اگر (چوٹی_array_vla_p (درخت_TYPE (folded_اظہاریہ)))
	{
	  /* countof is evaluated when given a vla.  */
	  ret.قدر = build2 (C_MAYBE_CONST_اظہاریہ, درخت_TYPE (ret.قدر),
			      folded_اظہاریہ, ret.قدر);
	  C_MAYBE_CONST_اظہاریہ_NON_CONST (ret.قدر) = !اظہاریہ_const_operands;
	  سیٹ_اظہاریہ_LOCATION (ret.قدر, loc);
	}
      نکالو_maybe_مستعمل (چوٹی_array_vla_p (درخت_TYPE (folded_اظہاریہ)));
    }
  واپس ret;
}

/* Return the result of countof applied to T, a structure for the type
   name passed to countof (rather than the type itself).  LOC is the
   location of the original expression.  */

ساخت c_اظہاریہ
c_اظہاریہ_countof_type (location_t loc, ساخت c_type_name *t)
{
  درخت type;
  ساخت c_اظہاریہ ret;
  درخت type_اظہاریہ = NULL_درخت;
  منطقی type_اظہاریہ_const = سچ;
  type = groktypename (t, &type_اظہاریہ, &type_اظہاریہ_const);
  ret.قدر = c_countof_type (loc, type);
  c_آخری_sizeof_arg = type;
  c_آخری_sizeof_loc = loc;
  ret.original_رمز = COUNTOF_اظہاریہ;
  ret.original_type = تہی;
  ret.m_decimal = 0;
  اگر (type == error_mark_گرہ)
    {
      ret.قدر = error_mark_گرہ;
      ret.original_رمز = ERROR_MARK;
    }
  ورنہ
  اگر ((type_اظہاریہ || درخت_رمز (ret.قدر) == INTEGER_CST)
      && چوٹی_array_vla_p (type))
    {
      /* If the type is a [*] array, it is a VLA but is represented as
	 having a size of zero.  In such a case we must ensure that
	 the result of countof does not get folded to a constant by
	 c_fully_fold, because if the number of elements is evaluated
	 the result is not constant and so
	 constraints on zero or negative size arrays must not be applied
	 when this countof call is inside another array declarator.  */
      اگر (!type_اظہاریہ)
	type_اظہاریہ = integer_zero_گرہ;
      ret.قدر = build2 (C_MAYBE_CONST_اظہاریہ, درخت_TYPE (ret.قدر),
			  type_اظہاریہ, ret.قدر);
      C_MAYBE_CONST_اظہاریہ_NON_CONST (ret.قدر) = !type_اظہاریہ_const;
    }
  نکالو_maybe_مستعمل (type != error_mark_گرہ ? چوٹی_array_vla_p (type) : جھوٹ);
  واپس ret;
}

/* Return the result of maxof applied to T, a structure for the type
   name passed to maxof (rather than the type itself).  LOC is the
   location of the original expression.  */

ساخت c_اظہاریہ
c_اظہاریہ_maxof_type (location_t loc, ساخت c_type_name *t)
{
  درخت type;
  ساخت c_اظہاریہ ret;
  درخت type_اظہاریہ = NULL_درخت;
  منطقی type_اظہاریہ_const = سچ;
  type = groktypename (t, &type_اظہاریہ, &type_اظہاریہ_const);
  ret.قدر = c_maxof_type (loc, type);
  c_آخری_sizeof_arg = type;
  c_آخری_sizeof_loc = loc;
  ret.original_رمز = MAXOF_اظہاریہ;
  ret.original_type = تہی;
  ret.m_decimal = 0;
  اگر (type == error_mark_گرہ)
    {
      ret.قدر = error_mark_گرہ;
      ret.original_رمز = ERROR_MARK;
    }
  نکالو_maybe_مستعمل (type != error_mark_گرہ);
  واپس ret;
}

/* Return the result of minof applied to T, a structure for the type
   name passed to minof (rather than the type itself).  LOC is the
   location of the original expression.  */

ساخت c_اظہاریہ
c_اظہاریہ_minof_type (location_t loc, ساخت c_type_name *t)
{
  درخت type;
  ساخت c_اظہاریہ ret;
  درخت type_اظہاریہ = NULL_درخت;
  منطقی type_اظہاریہ_const = سچ;
  type = groktypename (t, &type_اظہاریہ, &type_اظہاریہ_const);
  ret.قدر = c_minof_type (loc, type);
  c_آخری_sizeof_arg = type;
  c_آخری_sizeof_loc = loc;
  ret.original_رمز = MINOF_اظہاریہ;
  ret.original_type = تہی;
  ret.m_decimal = 0;
  اگر (type == error_mark_گرہ)
    {
      ret.قدر = error_mark_گرہ;
      ret.original_رمز = ERROR_MARK;
    }
  نکالو_maybe_مستعمل (type != error_mark_گرہ);
  واپس ret;
}

/* Build a function call to function FUNCTION with parameters PARAMS.
   The function call is at LOC.
   PARAMS is a list--a chain of TREE_LIST nodes--in which the
   TREE_VALUE of each node is a parameter-expression.
   FUNCTION's data type may be a function type or a pointer-to-function.  */

درخت
build_function_call (location_t loc, درخت function, درخت params)
{
  vec<درخت, va_gc> *v;
  درخت ret;

  vec_alloc (v, list_لمبائی (params));
  برائے (; params; params = درخت_CHAIN (params))
    v->تیز_ڈالو (درخت_قدر (params));
  ret = c_build_function_call_vec (loc, vNULL, function, v, تہی);
  vec_free (v);
  واپس ret;
}

/* Give a note about the location of the declaration of DECL,
   or, failing that, a pertinent declaration for FUNCTION_EXPR.  */

ساکن خالی
inform_declaration (درخت decl, درخت function_اظہاریہ)
{
  اگر (decl && (درخت_رمز (decl) != FUNCTION_DECL
	       || !DECL_IS_UNDECLARED_BUILTIN (decl)))
    inform (DECL_ماخذ_LOCATION (decl), "declared here");
  ورنہ اگر (function_اظہاریہ)
    انتخاب (درخت_رمز (function_اظہاریہ))
      {
      طےشدہ:
	توڑو;
      حالت COMPONENT_REF:
	/* Show the decl of the pertinent field (e.g. for callback
	   fields in a struct.  */
	{
	  درخت میدان_decl = درخت_عملیہ (function_اظہاریہ, 1);
	  اگر (location_t loc = DECL_ماخذ_LOCATION (میدان_decl))
	    inform (loc, "declared here");
	}
	توڑو;
      }
}


/* Build a function call to function FUNCTION with parameters PARAMS.
   If FUNCTION is the result of resolving an overloaded target built-in,
   ORIG_FUNDECL is the original function decl, otherwise it is null.
   ORIGTYPES, if not NULL, is a vector of types; each element is
   either NULL or the original type of the corresponding element in
   PARAMS.  The original type may differ from TREE_TYPE of the
   parameter for enums.  FUNCTION's data type may be a function type
   or pointer-to-function.  This function changes the elements of
   PARAMS.  */

درخت
build_function_call_vec (location_t loc, vec<location_t> arg_loc,
			 درخت function, vec<درخت, va_gc> *params,
			 vec<درخت, va_gc> *origtypes, درخت orig_fundecl)
{
  درخت fntype, fundecl = NULL_درخت;
  درخت name = NULL_درخت, نتیجہ;
  درخت tem;
  صحیح nargs;
  درخت *argarray;


  /* Strip NON_LVALUE_EXPRs, etc., since we aren't using as an lvalue.  */
  STRIP_TYPE_NOPS (function);

  /* Convert anything with function type to a pointer-to-function.  */
  اگر (درخت_رمز (function) == FUNCTION_DECL)
    {
      name = DECL_NAME (function);

      اگر (flag_tm)
	tm_malloc_replacement (function);
      fundecl = function;
      اگر (!orig_fundecl)
	orig_fundecl = fundecl;
      /* Atomic functions have type checking/casting already done.  They are
	 often rewritten and don't match the original parameter list.  */
      اگر (name && startswith (IDENTIFIER_اشارہ_گر (name), "__atomic_"))
        origtypes = تہی;
    }
  اگر (درخت_رمز (درخت_TYPE (function)) == FUNCTION_TYPE)
    function = function_مقصد_اشارہ_گر_conversion (loc, function);

  /* For Objective-C, convert any calls via a cast to OBJC_TYPE_REF
     expressions, like those used for ObjC messenger dispatches.  */
  اگر (params && !params->is_خالی_خانے ())
    function = objc_rewrite_function_call (function, (*params)[0]);

  function = c_fully_fold (function, جھوٹ, تہی);

  fntype = درخت_TYPE (function);

  اگر (درخت_رمز (fntype) == ERROR_MARK)
    واپس error_mark_گرہ;

  اگر (!(درخت_رمز (fntype) == اشارہ_گر_TYPE
	&& درخت_رمز (درخت_TYPE (fntype)) == FUNCTION_TYPE))
    {
      اگر (!flag_diagnostics_show_caret && !STATEMENT_CLASS_P (function))
	error_at (loc,
		  "called object %qE is not a function or function pointer",
		  function);
      ورنہ اگر (DECL_P (function))
	{
	  auto_diagnostic_گروہ d;
	  error_at (loc,
		    "called object %qD is not a function or function pointer",
		    function);
	  inform_declaration (function, NULL_درخت);
	}
      ورنہ
	error_at (loc,
		  "called object is not a function or function pointer");
      واپس error_mark_گرہ;
    }

  اگر (fundecl && درخت_THIS_VOLATILE (fundecl))
    current_function_returns_abnormally = 1;

  /* fntype now gets the type of function pointed to.  */
  fntype = درخت_TYPE (fntype);
  درخت return_type = درخت_TYPE (fntype);

  /* Convert the parameters to the types declared in the
     function prototype, or apply default promotions.  */

  nargs = convert_arguments (loc, arg_loc, fntype, params,
			     origtypes, function, fundecl);
  اگر (nargs < 0)
    واپس error_mark_گرہ;

  /* Check that the function is called through a compatible prototype.
     If it is not, warn.  */
  اگر (CONVERT_اظہاریہ_P (function)
      && درخت_رمز (tem = درخت_عملیہ (function, 0)) == ADDR_اظہاریہ
      && درخت_رمز (tem = درخت_عملیہ (tem, 0)) == FUNCTION_DECL
      && !comptypes (fntype, درخت_TYPE (tem)))
    {
      /* This situation leads to run-time undefined behavior.  We can't,
	 therefore, simply error unless we can prove that all possible
	 executions of the program must execute the code.  */
      warning_at (loc, 0, "function called through a non-compatible type");

      اگر (VOID_TYPE_P (return_type)
	  && TYPE_QUALS (return_type) != TYPE_UNQUALIFIED)
	pedwarn (loc, 0,
		 "function with qualified void return type called");
     }

  argarray = vec_محفوظ_پتہ (params);

  /* Check that arguments to builtin functions match the expectations.  */
  اگر (fundecl
      && fndecl_built_اندر_p (fundecl)
      && !check_builtin_function_arguments (loc, arg_loc, fundecl,
					    orig_fundecl, nargs, argarray))
    واپس error_mark_گرہ;

  /* Check that the arguments to the function are valid.  */
  منطقی warned_p = check_function_arguments (loc, fundecl, fntype,
					    nargs, argarray, &arg_loc,
					    comptypes);

  اگر (TYPE_QUALS (return_type) != TYPE_UNQUALIFIED
      && !VOID_TYPE_P (return_type))
    return_type = c_build_qualified_type (return_type, TYPE_UNQUALIFIED);
  اگر (name != NULL_درخت
      && startswith (IDENTIFIER_اشارہ_گر (name), "__builtin_"))
    {
      اگر (require_constant_قدر)
	نتیجہ
	  = fold_build_call_array_initializer_loc (loc, return_type,
						   function, nargs, argarray);
      ورنہ
	نتیجہ = fold_build_call_array_loc (loc, return_type,
					    function, nargs, argarray);
      اگر (درخت_رمز (نتیجہ) == NOP_اظہاریہ
	  && درخت_رمز (درخت_عملیہ (نتیجہ, 0)) == INTEGER_CST)
	STRIP_TYPE_NOPS (نتیجہ);
    }
  ورنہ
    نتیجہ = build_call_array_loc (loc, return_type,
				   function, nargs, argarray);
  /* If -Wnonnull warning has been diagnosed, avoid diagnosing it again
     later.  */
  اگر (warned_p && درخت_رمز (نتیجہ) == CALL_اظہاریہ)
    suppress_warning (نتیجہ, OPT_Wnonnull);

  /* In this improbable scenario, a nested function returns a VM type.
     Create a TARGET_EXPR so that the call always has a LHS, much as
     what the C++ FE does for functions returning non-PODs.  */
  اگر (c_type_variably_modified_p (درخت_TYPE (fntype)))
    {
      درخت tmp = create_tmp_var_raw (درخت_TYPE (fntype));
      نتیجہ = build4 (ہدف_اظہاریہ, درخت_TYPE (fntype), tmp, نتیجہ,
		       NULL_درخت, NULL_درخت);
    }

  اگر (VOID_TYPE_P (درخت_TYPE (نتیجہ)))
    {
      اگر (TYPE_QUALS (درخت_TYPE (نتیجہ)) != TYPE_UNQUALIFIED)
	pedwarn (loc, 0,
		 "function with qualified void return type called");
      واپس نتیجہ;
    }
  واپس require_complete_type (loc, نتیجہ);
}

/* Like build_function_call_vec, but call also resolve_overloaded_builtin.  */

درخت
c_build_function_call_vec (location_t loc, ثابت vec<location_t> &arg_loc,
			   درخت function, vec<درخت, va_gc> *params,
			   vec<درخت, va_gc> *origtypes)
{
  /* Strip NON_LVALUE_EXPRs, etc., since we aren't using as an lvalue.  */
  STRIP_TYPE_NOPS (function);

  /* Convert anything with function type to a pointer-to-function.  */
  اگر (درخت_رمز (function) == FUNCTION_DECL)
    {
      /* Implement type-directed function overloading for builtins.
	 resolve_overloaded_builtin and targetm.resolve_overloaded_builtin
	 handle all the type checking.  The result is a complete expression
	 that implements this function call.  */
      درخت tem = resolve_overloaded_builtin (loc, function, params);
      اگر (tem)
	واپس tem;
    }
  واپس build_function_call_vec (loc, arg_loc, function, params, origtypes);
}

/* Helper for convert_arguments called to convert the VALue of argument
   number ARGNUM from ORIGTYPE to the corresponding parameter number
   PARMNUM and TYPE.
   PLOC is the location where the conversion is being performed.
   FUNCTION and FUNDECL are the same as in convert_arguments.
   VALTYPE is the original type of VAL before the conversion and,
   for EXCESS_PRECISION_EXPR, the operand of the expression.
   NPC is true if VAL represents the null pointer constant (VAL itself
   will have been folded to an integer constant).
   RNAME is the same as FUNCTION except in Objective C when it's
   the function selector.
   EXCESS_PRECISION is true when VAL was originally represented
   as EXCESS_PRECISION_EXPR.
   WARNOPT is the same as in convert_for_assignment.  */

ساکن درخت
convert_دلیل (location_t ploc, درخت function, درخت fundecl,
		  درخت type, درخت origtype, درخت val, درخت valtype,
		  منطقی npc, درخت rname, صحیح parmnum, صحیح argnum,
		  منطقی excess_precision, صحیح warnopt)
{
  /* Formal parm type is specified by a function prototype.  */

  اگر (type == error_mark_گرہ || !COMPLETE_TYPE_P (type))
    {
      error_at (ploc, "type of formal parameter %d is incomplete",
		parmnum + 1);
      واپس error_mark_گرہ;
    }

  /* Optionally warn about conversions that differ from the default
     conversions.  */
  اگر (warn_traditional_conversion || warn_traditional)
    {
      اگر (INTEGRAL_TYPE_P (type)
	  && SCALAR_FLOAT_TYPE_P (valtype))
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as integer rather "
		    "than floating due to prototype",
		    argnum, rname);
      اگر (INTEGRAL_TYPE_P (type)
	  && درخت_رمز (valtype) == COMPLEX_TYPE)
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as integer rather "
		    "than complex due to prototype",
		    argnum, rname);
      ورنہ اگر (درخت_رمز (type) == COMPLEX_TYPE
	       && SCALAR_FLOAT_TYPE_P (valtype))
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as complex rather "
		    "than floating due to prototype",
		    argnum, rname);
      ورنہ اگر (SCALAR_FLOAT_TYPE_P (type)
	       && INTEGRAL_TYPE_P (valtype))
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as floating rather "
		    "than integer due to prototype",
		    argnum, rname);
      ورنہ اگر (درخت_رمز (type) == COMPLEX_TYPE
	       && INTEGRAL_TYPE_P (valtype))
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as complex rather "
		    "than integer due to prototype",
		    argnum, rname);
      ورنہ اگر (SCALAR_FLOAT_TYPE_P (type)
	       && درخت_رمز (valtype) == COMPLEX_TYPE)
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as floating rather "
		    "than complex due to prototype",
		    argnum, rname);
      /* ??? At some point, messages should be written about
	 conversions between complex types, but that's too messy
	 to do now.  */
      ورنہ اگر (SCALAR_FLOAT_TYPE_P (type)
	       && SCALAR_FLOAT_TYPE_P (valtype))
	{
	  غیرعلامتی صحیح formal_prec = TYPE_PRECISION (type);

	  /* Warn if any argument is passed as `float',
	     since without a prototype it would be `double'.  */
	  اگر (formal_prec == TYPE_PRECISION (float_type_گرہ)
	      && type != dfloat32_type_گرہ)
	    warning_at (ploc, 0,
			"passing argument %d of %qE as %<float%> "
			"rather than %<double%> due to prototype",
			argnum, rname);

	  /* Warn if mismatch between argument and prototype
	     for decimal float types.  Warn of conversions with
	     binary float types and of precision narrowing due to
	     prototype.  */
	  ورنہ اگر (type != valtype
		   && (type == dfloat32_type_گرہ
		       || type == dfloat64_type_گرہ
		       || type == dfloat128_type_گرہ
		       || valtype == dfloat32_type_گرہ
		       || valtype == dfloat64_type_گرہ
		       || valtype == dfloat128_type_گرہ)
		   && (formal_prec
		       <= TYPE_PRECISION (valtype)
		       || (type == dfloat128_type_گرہ
			   && (valtype
			       != dfloat64_type_گرہ
			       && (valtype
				   != dfloat32_type_گرہ)))
		       || (type == dfloat64_type_گرہ
			   && (valtype
			       != dfloat32_type_گرہ))))
	    warning_at (ploc, 0,
			"passing argument %d of %qE as %qT "
			"rather than %qT due to prototype",
			argnum, rname, type, valtype);

	}
      /* Detect integer changing in width or signedness.
	 These warnings are only activated with
	 -Wtraditional-conversion, not with -Wtraditional.  */
      ورنہ اگر (warn_traditional_conversion
	       && INTEGRAL_TYPE_P (type)
	       && INTEGRAL_TYPE_P (valtype))
	{
	  غیرعلامتی صحیح formal_prec = TYPE_PRECISION (type);
	  درخت would_have_been = default_conversion (val);
	  درخت type1 = درخت_TYPE (would_have_been);

	  اگر (val == error_mark_گرہ)
	    /* VAL could have been of incomplete type.  */;
	  ورنہ اگر (درخت_رمز (type) == ENUMERAL_TYPE
		   && (TYPE_MAIN_VARIANT (type)
		       == TYPE_MAIN_VARIANT (valtype)))
	    /* No warning if function asks for enum
	       and the actual arg is that enum type.  */
	    ;
	  ورنہ اگر (formal_prec != TYPE_PRECISION (type1))
	    warning_at (ploc, OPT_Wtraditional_conversion,
			"passing argument %d of %qE "
			"with different width due to prototype",
			argnum, rname);
	  ورنہ اگر (TYPE_UNSIGNED (type) == TYPE_UNSIGNED (type1))
	    ;
	  /* Don't complain if the formal parameter type
	     is an enum, because we can't tell now whether
	     the value was an enum--even the same enum.  */
	  ورنہ اگر (درخت_رمز (type) == ENUMERAL_TYPE)
	    ;
	  ورنہ اگر (درخت_رمز (val) == INTEGER_CST
		   && int_سماتا_type_p (val, type))
	    /* Change in signedness doesn't matter
	       if a constant value is unaffected.  */
	    ;
	  /* If the value is extended from a narrower
	     unsigned type, it doesn't matter whether we
	     pass it as signed or unsigned; the value
	     certainly is the same either way.  */
	  ورنہ اگر (TYPE_PRECISION (valtype) < TYPE_PRECISION (type)
		   && TYPE_UNSIGNED (valtype))
	    ;
	  ورنہ اگر (TYPE_UNSIGNED (type))
	    warning_at (ploc, OPT_Wtraditional_conversion,
			"passing argument %d of %qE "
			"as unsigned due to prototype",
			argnum, rname);
	  ورنہ
	    warning_at (ploc, OPT_Wtraditional_conversion,
			"passing argument %d of %qE "
			"as signed due to prototype",
			argnum, rname);
	}
    }

  /* Possibly restore an EXCESS_PRECISION_EXPR for the
     sake of better warnings from convert_and_check.  */
  اگر (excess_precision)
    val = build1 (EXCESS_PRECISION_اظہاریہ, valtype, val);

  درخت parmval = convert_for_assignment (ploc, ploc, type,
					 val, origtype, ic_argpass,
					 npc, fundecl, function,
					 parmnum + 1, warnopt);
  واپس parmval;
}

/* Convert the argument expressions in the vector VALUES
   to the types in the list TYPE_ARG_TYPES (FNTYPE).

   If the list is exhausted, or when an element has NULL as its type,
   perform the default conversions.

   ORIGTYPES is the original types of the expressions in VALUES.  This
   holds the type of enum values which have been converted to integral
   types.  It may be NULL.

   FUNCTION is a tree for the called function.  It is used only for
   error messages, where it is formatted with %qE.

   This is also where warnings about wrong number of args are generated.

   ARG_LOC are locations of function arguments (if any).

   Returns the actual number of arguments processed (which may be less
   than the length of VALUES in some error situations), or -1 on
   failure.  */

ساکن صحیح
convert_arguments (location_t loc, vec<location_t> arg_loc, درخت fntype,
		   vec<درخت, va_gc> *اقدار, vec<درخت, va_gc> *origtypes,
		   درخت function, درخت fundecl)
{
  درخت typelist = TYPE_ARG_TYPES (fntype);
  غیرعلامتی صحیح parmnum;
  منطقی error_دلائل = جھوٹ;
  ثابت منطقی type_generic = fundecl
    && lookup_attribute ("type generic", TYPE_اوصاف (درخت_TYPE (fundecl)));
  منطقی type_generic_remove_excess_precision = جھوٹ;
  منطقی type_generic_حد_سے_تجاوز_p = جھوٹ;
  منطقی type_generic_ثنائی_ہندسہ_query = جھوٹ;
  درخت selector;

  /* Change pointer to function to the function itself for
     diagnostics.  */
  اگر (درخت_رمز (function) == ADDR_اظہاریہ
      && درخت_رمز (درخت_عملیہ (function, 0)) == FUNCTION_DECL)
    function = درخت_عملیہ (function, 0);

  /* Handle an ObjC selector specially for diagnostics.  */
  selector = objc_پیغام_selector ();

  /* For a call to a built-in function declared without a prototype,
     set to the built-in function's argument list.  */
  درخت builtin_typelist = NULL_درخت;

  /* For type-generic built-in functions, determine whether excess
     precision should be removed (classification) or not
     (comparison).  */
  اگر (fundecl
      && fndecl_built_اندر_p (fundecl, BUILT_اندر_معمول))
    {
      built_اندر_function رمز = DECL_FUNCTION_رمز (fundecl);
      اگر (C_DECL_BUILTIN_PROTOTYPE (fundecl))
	{
	  /* For a call to a built-in function declared without a prototype
	     use the types of the parameters of the internal built-in to
	     match those of the arguments to.  */
	  اگر (درخت bdecl = builtin_decl_explicit (رمز))
	    builtin_typelist = TYPE_ARG_TYPES (درخت_TYPE (bdecl));
	}

      /* For type-generic built-in functions, determine whether excess
	 precision should be removed (classification) or not
	 (comparison).  */
      اگر (type_generic)
	انتخاب (رمز)
	  {
	  حالت BUILT_اندر_ISFINITE:
	  حالت BUILT_اندر_ISINF:
	  حالت BUILT_اندر_ISINF_SIGN:
	  حالت BUILT_اندر_ISNAN:
	  حالت BUILT_اندر_ISNORMAL:
	  حالت BUILT_اندر_ISSIGNALING:
	  حالت BUILT_اندر_FPCLASSIFY:
	    type_generic_remove_excess_precision = سچ;
	    توڑو;

	  حالت BUILT_اندر_جوڑو_حد_سے_تجاوز_P:
	  حالت BUILT_اندر_SUB_حد_سے_تجاوز_P:
	  حالت BUILT_اندر_MUL_حد_سے_تجاوز_P:
	    /* The last argument of these type-generic builtins
	       should not be promoted.  */
	    type_generic_حد_سے_تجاوز_p = سچ;
	    توڑو;

	  حالت BUILT_اندر_CLZG:
	  حالت BUILT_اندر_CTZG:
	  حالت BUILT_اندر_CLRSBG:
	  حالت BUILT_اندر_FFSG:
	  حالت BUILT_اندر_PARITYG:
	  حالت BUILT_اندر_POPCOUNTG:
	    /* The first argument of these type-generic builtins
	       should not be promoted.  */
	    type_generic_ثنائی_ہندسہ_query = سچ;
	    توڑو;

	  طےشدہ:
	    توڑو;
	  }
    }

  /* Scan the given expressions (VALUES) and types (TYPELIST), producing
     individual converted arguments.  */

  درخت typetail, builtin_typetail, val;
  برائے (typetail = typelist,
	 builtin_typetail = builtin_typelist,
	 parmnum = 0;
       اقدار && اقدار->iterate (parmnum, &val);
       ++parmnum)
    {
      /* The type of the function parameter (if it was declared with one).  */
      درخت type = typetail ? درخت_قدر (typetail) : NULL_درخت;
      /* The type of the built-in function parameter (if the function
	 is a built-in).  Used to detect type incompatibilities in
	 calls to built-ins declared without a prototype.  */
      درخت builtin_type = (builtin_typetail
			   ? درخت_قدر (builtin_typetail) : NULL_درخت);
      /* The original type of the argument being passed to the function.  */
      درخت valtype = درخت_TYPE (val);
      /* The called function (or function selector in Objective C).  */
      درخت rname = function;
      صحیح argnum = parmnum + 1;
      ثابت حرف *invalid_func_diag;
      /* Set for EXCESS_PRECISION_EXPR arguments.  */
      منطقی excess_precision = جھوٹ;
      /* The value of the argument after conversion to the type
	 of the function parameter it is passed to.  */
      درخت parmval;
      /* Some __atomic_* builtins have additional hidden argument at
	 position 0.  */
      location_t ploc
	= !arg_loc.is_خالی_خانے () && اقدار->لمبائی () == arg_loc.لمبائی ()
	  ? expansion_نقطہ_location_if_اندر_system_سرخی (arg_loc[parmnum])
	  : داخلہ_location;

      اگر (type == void_type_گرہ)
	{
	  auto_diagnostic_گروہ d;
	  صحیح عدد_expected = parmnum;
	  صحیح عدد_actual = اقدار->لمبائی ();
	  gcc_rich_location rich_loc (loc);
	  اگر (ploc != داخلہ_location)
	    rich_loc.جوڑو_range (ploc);
	  اگر (selector)
	    error_at (&rich_loc,
		      "too many arguments to method %qE; expected %i, have %i",
		      selector, عدد_expected, عدد_actual);
	  ورنہ
	    error_at (&rich_loc,
		      "too many arguments to function %qE; expected %i, have %i",
		      function, عدد_expected, عدد_actual);
	  inform_declaration (fundecl, function);
	  واپس error_دلائل ? -1 : (صحیح) parmnum;
	}

      اگر (builtin_type == void_type_گرہ)
	{
	  auto_diagnostic_گروہ d;
	  اگر (warning_at (loc, OPT_Wbuiltin_declaration_mismatch,
			  "too many arguments to built-in function %qE "
			  "expecting %d", function, parmnum))
	    inform_declaration (fundecl, function);
	  builtin_typetail = NULL_درخت;
	}

      اگر (!typetail && parmnum == 0 && !TYPE_NO_NAMED_دلائل_STDARG_P (fntype)
	  && !(fundecl && fndecl_built_اندر_p (fundecl)))
	{
	  auto_diagnostic_گروہ d;
	  منطقی warned;
	  اگر (selector)
	    warned = warning_at (loc, OPT_Wdeprecated_non_prototype,
				 "ISO C23 does not allow arguments"
				 " for method %qE declared without parameters",
				 function);
	  ورنہ
	    warned = warning_at (loc, OPT_Wdeprecated_non_prototype,
				 "ISO C23 does not allow arguments"
				 " for function %qE declared without parameters",
				 function);
	  اگر (warned)
	    inform_declaration (fundecl, function);
	}

      اگر (selector && argnum > 2)
	{
	  rname = selector;
	  argnum -= 2;
	}

      /* Determine if VAL is a null pointer constant before folding it.  */
      منطقی npc = null_اشارہ_گر_constant_p (val);

      /* If there is excess precision and a prototype, convert once to
	 the required type rather than converting via the semantic
	 type.  Likewise without a prototype a float value represented
	 as long double should be converted once to double.  But for
	 type-generic classification functions excess precision must
	 be removed here.  */
      اگر (درخت_رمز (val) == EXCESS_PRECISION_اظہاریہ
	  && (type || !type_generic || !type_generic_remove_excess_precision))
	{
	  val = درخت_عملیہ (val, 0);
	  excess_precision = سچ;
	}
      val = c_fully_fold (val, جھوٹ, تہی);
      STRIP_TYPE_NOPS (val);

      val = require_complete_type (ploc, val);

      /* Some floating-point arguments must be promoted to double when
	 no type is specified by a prototype.  This applies to
	 arguments of type float, and to architecture-specific types
	 (ARM __fp16), but not to _FloatN or _FloatNx types.  */
      منطقی promote_float_arg = جھوٹ;
      اگر (type == NULL_درخت
	  && درخت_رمز (valtype) == REAL_TYPE
	  && (TYPE_PRECISION (valtype)
	      <= TYPE_PRECISION (double_type_گرہ))
	  && TYPE_MAIN_VARIANT (valtype) != double_type_گرہ
	  && TYPE_MAIN_VARIANT (valtype) != long_double_type_گرہ
	  && !DECIMAL_FLOAT_منوال_P (TYPE_منوال (valtype)))
	{
	  /* Promote this argument, unless it has a _FloatN or
	     _FloatNx type.  */
	  promote_float_arg = سچ;
	  برائے (صحیح i = 0; i < عدد_FLOATN_NX_TYPES; i++)
	    اگر (TYPE_MAIN_VARIANT (valtype) == FLOATN_NX_TYPE_گرہ (i))
	      {
		promote_float_arg = جھوٹ;
		توڑو;
	      }
	  /* Don't promote __bf16 either.  */
	  اگر (TYPE_MAIN_VARIANT (valtype) == bfloat16_type_گرہ)
	    promote_float_arg = جھوٹ;
	}

      اگر (type != NULL_درخت)
	{
	  درخت origtype = (!origtypes) ? NULL_درخت : (*origtypes)[parmnum];
	  parmval = convert_دلیل (ploc, function, fundecl, type, origtype,
				      val, valtype, npc, rname, parmnum, argnum,
				      excess_precision, 0);
	}
      /* A NULLPTR type is just a nullptr always.  */
      ورنہ اگر (درخت_رمز (درخت_TYPE (val)) == NULLPTR_TYPE)
	parmval = omit_one_عملیہ_loc (ploc, درخت_TYPE (val), nullptr_گرہ, val);
      ورنہ اگر (promote_float_arg)
        {
	  اگر (type_generic)
	    parmval = val;
	  ورنہ
	    {
	      /* Convert `float' to `double'.  */
	      اگر (warn_double_promotion && !c_inhibit_evaluation_warnings)
		warning_at (ploc, OPT_Wdouble_promotion,
			    "implicit conversion from %qT to %qT when passing "
			    "argument to function",
			    valtype, double_type_گرہ);
	      parmval = convert (double_type_گرہ, val);
	    }
	}
      ورنہ اگر ((excess_precision && !type_generic)
	       || (type_generic_حد_سے_تجاوز_p && parmnum == 2)
	       || (type_generic_ثنائی_ہندسہ_query && parmnum == 0))
	/* A "double" argument with excess precision being passed
	   without a prototype or in variable arguments.
	   The last argument of __builtin_*_overflow_p should not be
	   promoted, similarly the first argument of
	   __builtin_{clz,ctz,clrsb,ffs,parity,popcount}g.  */
	parmval = convert (valtype, val);
      ورنہ اگر ((invalid_func_diag =
		targetm.calls.invalid_arg_for_unprototyped_fn (typelist, fundecl, val)))
	{
	  error (invalid_func_diag);
	  واپس -1;
	}
      ورنہ اگر (درخت_رمز (val) == ADDR_اظہاریہ && reject_gcc_builtin (val))
	{
	  واپس -1;
	}
      ورنہ
	/* Convert `short' and `char' to full-size `int'.  */
	parmval = default_conversion (val);

      (*اقدار)[parmnum] = parmval;
      اگر (parmval == error_mark_گرہ)
	error_دلائل = سچ;

      اگر (!type && builtin_type && درخت_رمز (builtin_type) != VOID_TYPE)
	{
	  /* For a call to a built-in function declared without a prototype,
	     perform the conversions from the argument to the expected type
	     but issue warnings rather than errors for any mismatches.
	     Ignore the converted argument and use the PARMVAL obtained
	     above by applying default conversions instead.  */
	  درخت origtype = (!origtypes) ? NULL_درخت : (*origtypes)[parmnum];
	  convert_دلیل (ploc, function, fundecl, builtin_type, origtype,
			    val, valtype, npc, rname, parmnum, argnum,
			    excess_precision,
			    OPT_Wbuiltin_declaration_mismatch);
	}

      اگر (typetail)
	typetail = درخت_CHAIN (typetail);

      اگر (builtin_typetail)
	builtin_typetail = درخت_CHAIN (builtin_typetail);
    }

  gcc_assert (parmnum == vec_محفوظ_لمبائی (اقدار));

  اگر (typetail != NULL_درخت && درخت_قدر (typetail) != void_type_گرہ)
    {
      /* Not enough args.
	 Determine minimum number of arguments required.  */
      صحیح min_expected_عدد = 0;
      منطقی at_کم_سے_کم_p = جھوٹ;
      درخت iter = typelist;
      جب (سچ)
	{
	  اگر (!iter)
	    {
	      /* Variadic arguments; stop iterating.  */
	      at_کم_سے_کم_p = سچ;
	      توڑو;
	    }
	  اگر (iter == void_list_گرہ)
	    /* End of arguments; stop iterating.  */
	    توڑو;
	  ++min_expected_عدد;
	  iter = درخت_CHAIN (iter);
	}
      auto_diagnostic_گروہ d;
      صحیح actual_عدد = vec_محفوظ_لمبائی (اقدار);
      error_at (loc,
		at_کم_سے_کم_p
		? G_("too few arguments to function %qE; expected at least %i, have %i")
		: G_("too few arguments to function %qE; expected %i, have %i"),
		function, min_expected_عدد, actual_عدد);
      inform_declaration (fundecl, function);
      واپس -1;
    }

  اگر (builtin_typetail && درخت_قدر (builtin_typetail) != void_type_گرہ)
    {
      غیرعلامتی nargs = parmnum;
      برائے (درخت t = builtin_typetail; t; t = درخت_CHAIN (t))
	++nargs;

      auto_diagnostic_گروہ d;
      اگر (warning_at (loc, OPT_Wbuiltin_declaration_mismatch,
		      "too few arguments to built-in function %qE "
		      "expecting %u", function, nargs - 1))
	inform_declaration (fundecl, function);
    }

  واپس error_دلائل ? -1 : (صحیح) parmnum;
}

/* This is the entry point used by the parser to build unary operators
   in the input.  CODE, a tree_code, specifies the unary operator, and
   ARG is the operand.  For unary plus, the C parser currently uses
   CONVERT_EXPR for code.

   LOC is the location to use for the tree generated.
*/

ساخت c_اظہاریہ
parser_build_unary_op (location_t loc, شمار درخت_رمز_2 رمز, ساخت c_اظہاریہ arg)
{
  ساخت c_اظہاریہ نتیجہ;

  نتیجہ.original_رمز = رمز;
  نتیجہ.original_type = تہی;
  نتیجہ.m_decimal = 0;

  اگر (reject_gcc_builtin (arg.قدر))
    {
      نتیجہ.قدر = error_mark_گرہ;
    }
  ورنہ
    {
      نتیجہ.قدر = build_unary_op (loc, رمز, arg.قدر, جھوٹ);

      اگر (درخت_حد_سے_تجاوز_P (نتیجہ.قدر) && !درخت_حد_سے_تجاوز_P (arg.قدر))
	حد_سے_تجاوز_warning (loc, نتیجہ.قدر, arg.قدر);
    }

  /* We are typically called when parsing a prefix token at LOC acting on
     ARG.  Reflect this by updating the source range of the result to
     start at LOC and end at the end of ARG.  */
  سیٹ_c_اظہاریہ_ماخذ_range (&نتیجہ,
			   loc, arg.get_اختتام ());

  واپس نتیجہ;
}

/* Returns true if TYPE is a character type, *not* including wchar_t.  */

منطقی
char_type_p (درخت type)
{
  واپس (type == char_type_گرہ
	  || type == unsigned_char_type_گرہ
	  || type == signed_char_type_گرہ
	  || type == char16_type_گرہ
	  || type == char32_type_گرہ);
}

/* This is the entry point used by the parser to build binary operators
   in the input.  CODE, a tree_code, specifies the binary operator, and
   ARG1 and ARG2 are the operands.  In addition to constructing the
   expression, we check for operands that were written with other binary
   operators in a way that is likely to confuse the user.  ORIG_ARG1 is
   the original first operand for TRUTH_{AND,OR}IF_EXPR before it is
   converted to truth value, otherwise NULL_TREE.

   LOCATION is the location of the binary operator.  */

ساخت c_اظہاریہ
parser_build_ثنائی_op (location_t location, شمار درخت_رمز_2 رمز,
			ساخت c_اظہاریہ arg1, ساخت c_اظہاریہ arg2, درخت orig_arg1)
{
  ساخت c_اظہاریہ نتیجہ;
  نتیجہ.m_decimal = 0;

  شمار درخت_رمز_2 code1 = arg1.original_رمز;
  شمار درخت_رمز_2 code2 = arg2.original_رمز;
  درخت type1 = (arg1.original_type
                ? arg1.original_type
                : درخت_TYPE (arg1.قدر));
  درخت type2 = (arg2.original_type
                ? arg2.original_type
                : درخت_TYPE (arg2.قدر));

  نتیجہ.قدر = build_ثنائی_op (location, رمز,
				  arg1.قدر, arg2.قدر, سچ);
  نتیجہ.original_رمز = رمز;
  نتیجہ.original_type = تہی;
  نتیجہ.m_decimal = 0;

  اگر (درخت_رمز (نتیجہ.قدر) == ERROR_MARK)
    {
      سیٹ_c_اظہاریہ_ماخذ_range (&نتیجہ,
			       arg1.get_آغاز (),
			       arg2.get_اختتام ());
      واپس نتیجہ;
    }

  اگر (location != UNKNOWN_LOCATION)
    protected_سیٹ_اظہاریہ_location (نتیجہ.قدر, location);

  سیٹ_c_اظہاریہ_ماخذ_range (&نتیجہ,
			   arg1.get_آغاز (),
			   arg2.get_اختتام ());

  /* Check for cases such as x+y<<z which users are likely
     to misinterpret.  */
  اگر (warn_parentheses)
    warn_about_parentheses (location, رمز, code1, arg1.قدر, code2,
			    arg2.قدر);

  اگر (warn_logical_op)
    warn_logical_operator (location, رمز, درخت_TYPE (نتیجہ.قدر),
			   code1, arg1.قدر, code2, arg2.قدر);

  اگر (warn_constant_logical_عملیہ
      && (رمز == TRUTH_ANDIF_اظہاریہ || رمز == TRUTH_ORIF_اظہاریہ)
      && INTEGRAL_NB_TYPE_P (type1)
      && INTEGRAL_NB_TYPE_P (type2))
    {
      ثابت حرف *name = رمز == TRUTH_ANDIF_اظہاریہ ? "&&" : "||";
      اگر (orig_arg1 == NULL_درخت)
	orig_arg1 = arg1.قدر;
      خودکار enum_other_than_0_1 = [] (درخت type) {
	اگر (درخت_رمز (type) != ENUMERAL_TYPE)
	  واپس جھوٹ;
	برائے (درخت l = TYPE_اقدار (type); l; l = درخت_CHAIN (l))
	  {
	    درخت v = DECL_INITIAL (درخت_قدر (l));
	    اگر (!integer_zerop (v) && !integer_onep (v))
	      واپس سچ;
	  }
	واپس جھوٹ;
      };
      خودکار diagnose_constant_logical_عملیہ = [=] (درخت val, درخت type) {
	اگر (درخت_رمز (val) != INTEGER_CST || integer_zerop (val))
	  واپس جھوٹ;
	اگر (integer_onep (val) && !enum_other_than_0_1 (type))
	  واپس جھوٹ;
	gcc_rich_location richloc (location);
	richloc.جوڑو_fixit_replace (name + 1);
	auto_diagnostic_گروہ d;
	اگر (warning_at (location, OPT_Wconstant_logical_عملیہ,
			"use of logical %qs with constant operand %qE",
			name, val))
	  inform (&richloc, "use %qs for bitwise operation", name + 1);
	واپس سچ;
      };
      اگر (!diagnose_constant_logical_عملیہ (arg2.قدر, type2))
	diagnose_constant_logical_عملیہ (orig_arg1, type1);
    }

  اگر (warn_tautological_compare)
    {
      درخت lhs = arg1.قدر;
      درخت rhs = arg2.قدر;
      اگر (درخت_رمز (lhs) == C_MAYBE_CONST_اظہاریہ)
	{
	  اگر (C_MAYBE_CONST_اظہاریہ_PRE (lhs) != NULL_درخت
	      && درخت_SIDE_EFFECTS (C_MAYBE_CONST_اظہاریہ_PRE (lhs)))
	    lhs = NULL_درخت;
	  ورنہ
	    lhs = C_MAYBE_CONST_اظہاریہ_اظہاریہ (lhs);
	}
      اگر (درخت_رمز (rhs) == C_MAYBE_CONST_اظہاریہ)
	{
	  اگر (C_MAYBE_CONST_اظہاریہ_PRE (rhs) != NULL_درخت
	      && درخت_SIDE_EFFECTS (C_MAYBE_CONST_اظہاریہ_PRE (rhs)))
	    rhs = NULL_درخت;
	  ورنہ
	    rhs = C_MAYBE_CONST_اظہاریہ_اظہاریہ (rhs);
	}
      اگر (lhs != NULL_درخت && rhs != NULL_درخت)
	warn_tautological_cmp (location, رمز, lhs, rhs);
    }

  اگر (warn_logical_not_paren
      && درخت_رمز_CLASS (رمز) == tcc_comparison
      && code1 == TRUTH_NOT_اظہاریہ
      && code2 != TRUTH_NOT_اظہاریہ
      /* Avoid warning for !!x == y.  */
      && (درخت_رمز (arg1.قدر) != NE_اظہاریہ
	  || !integer_zerop (درخت_عملیہ (arg1.قدر, 1))))
    {
      /* Avoid warning for !b == y where b has _Bool type.  */
      درخت t = integer_zero_گرہ;
      اگر (درخت_رمز (arg1.قدر) == EQ_اظہاریہ
	  && integer_zerop (درخت_عملیہ (arg1.قدر, 1))
	  && درخت_TYPE (درخت_عملیہ (arg1.قدر, 0)) == integer_type_گرہ)
	{
	  t = درخت_عملیہ (arg1.قدر, 0);
	  کرو
	    {
	      اگر (درخت_TYPE (t) != integer_type_گرہ)
		توڑو;
	      اگر (درخت_رمز (t) == C_MAYBE_CONST_اظہاریہ)
		t = C_MAYBE_CONST_اظہاریہ_اظہاریہ (t);
	      ورنہ اگر (CONVERT_اظہاریہ_P (t))
		t = درخت_عملیہ (t, 0);
	      ورنہ
		توڑو;
	    }
	  جب (1);
	}
      اگر (!C_BOOLEAN_TYPE_P (درخت_TYPE (t)))
	warn_logical_not_parentheses (location, رمز, arg1.قدر, arg2.قدر);
    }

  /* Warn about comparisons against string literals, with the exception
     of testing for equality or inequality of a string literal with NULL.  */
  اگر (رمز == EQ_اظہاریہ || رمز == NE_اظہاریہ)
    {
      اگر ((code1 == STRING_CST
	   && !integer_zerop (درخت_strip_nop_conversions (arg2.قدر)))
	  || (code2 == STRING_CST
	      && !integer_zerop (درخت_strip_nop_conversions (arg1.قدر))))
	warning_at (location, OPT_Waddress,
		    "comparison with string literal results in unspecified behavior");
      /* Warn for ptr == '\0', it's likely that it should've been ptr[0].  */
      اگر (اشارہ_گر_TYPE_P (type1)
	  && null_اشارہ_گر_constant_p (arg2.قدر)
	  && char_type_p (type2))
	{
	  auto_diagnostic_گروہ d;
	  اگر (warning_at (location, OPT_Wpointer_compare,
			    "comparison between pointer and zero character "
			    "constant"))
	    inform (arg1.get_آغاز (),
		      "did you mean to dereference the pointer?");
	}
      ورنہ اگر (اشارہ_گر_TYPE_P (type2)
	       && null_اشارہ_گر_constant_p (arg1.قدر)
	       && char_type_p (type1))
	{
	  auto_diagnostic_گروہ d;
	  اگر (warning_at (location, OPT_Wpointer_compare,
			    "comparison between pointer and zero character "
			    "constant"))
	    inform (arg2.get_آغاز (),
		      "did you mean to dereference the pointer?");
	}
    }
  ورنہ اگر (درخت_رمز_CLASS (رمز) == tcc_comparison
	   && (code1 == STRING_CST || code2 == STRING_CST))
    warning_at (location, OPT_Waddress,
		"comparison with string literal results in unspecified "
		"behavior");

  اگر (warn_zero_as_null_اشارہ_گر_constant
      && c_inhibit_evaluation_warnings == 0
      && درخت_رمز_CLASS (رمز) == tcc_comparison)
    {
      اگر ((درخت_رمز (type1) == اشارہ_گر_TYPE
	   || درخت_رمز (type1) == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type2)
	  && null_اشارہ_گر_constant_p (arg2.قدر))
	warning_at (arg2.get_location(), OPT_Wzero_as_null_اشارہ_گر_constant,
		    "zero as null pointer constant");

      اگر ((درخت_رمز (type2) == اشارہ_گر_TYPE
	   || درخت_رمز (type2) == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type1)
	  && null_اشارہ_گر_constant_p (arg1.قدر))
	warning_at (arg1.get_location(), OPT_Wzero_as_null_اشارہ_گر_constant,
		    "zero as null pointer constant");
    }

  اگر (warn_array_compare
      && درخت_رمز_CLASS (رمز) == tcc_comparison
      && درخت_رمز (type1) == ARRAY_TYPE
      && درخت_رمز (type2) == ARRAY_TYPE)
    do_warn_array_compare (location, رمز, arg1.قدر, arg2.قدر);

  اگر (درخت_حد_سے_تجاوز_P (نتیجہ.قدر)
      && !درخت_حد_سے_تجاوز_P (arg1.قدر)
      && !درخت_حد_سے_تجاوز_P (arg2.قدر))
    حد_سے_تجاوز_warning (location, نتیجہ.قدر);

  /* Warn about comparisons of different enum types.  */
  اگر (warn_enum_compare
      && درخت_رمز_CLASS (رمز) == tcc_comparison
      && درخت_رمز (type1) == ENUMERAL_TYPE
      && درخت_رمز (type2) == ENUMERAL_TYPE
      && TYPE_MAIN_VARIANT (type1) != TYPE_MAIN_VARIANT (type2))
    warning_at (location, OPT_Wenum_compare,
		"comparison between %qT and %qT",
		type1, type2);

  اگر (warn_xor_مستعمل_as_pow
      && رمز == ثنائی_ہندسہ_XOR_اظہاریہ
      && arg1.m_decimal
      && arg2.m_decimal)
    check_for_xor_مستعمل_as_pow (arg1.get_location (), arg1.قدر,
			       location,
			       arg2.get_location (), arg2.قدر);

  واپس نتیجہ;
}

/* Return a tree for the difference of pointers OP0 and OP1.
   The resulting tree has type ptrdiff_t.  If POINTER_SUBTRACT sanitization is
   enabled, assign to INSTRUMENT_EXPR call to libsanitizer.  */

ساکن درخت
اشارہ_گر_diff (location_t loc, درخت op0, درخت op1, درخت *instrument_اظہاریہ)
{
  درخت restype = ptrdiff_type_گرہ;
  درخت نتیجہ, inttype;

  addr_space_t as0 = TYPE_ADDR_SPACE (درخت_TYPE (درخت_TYPE (op0)));
  addr_space_t as1 = TYPE_ADDR_SPACE (درخت_TYPE (درخت_TYPE (op1)));
  درخت ہدف_type = درخت_TYPE (درخت_TYPE (op0));
  درخت orig_op0 = op0;
  درخت orig_op1 = op1;

  /* If the operands point into different address spaces, we need to
     explicitly convert them to pointers into the common address space
     before we can subtract the numerical address values.  */
  اگر (as0 != as1)
    {
      addr_space_t as_common;
      درخت common_type;

      /* Determine the common superset address space.  This is guaranteed
	 to exist because the caller verified that comp_target_types
	 returned non-zero.  */
      اگر (!addr_space_superset (as0, as1, &as_common))
	gcc_unreachable ();

      common_type = common_اشارہ_گر_type (درخت_TYPE (op0), درخت_TYPE (op1), NULL_درخت);
      op0 = convert (common_type, op0);
      op1 = convert (common_type, op1);
    }

  /* Determine integer type result of the subtraction.  This will usually
     be the same as the result type (ptrdiff_t), but may need to be a wider
     type if pointers for the address space are wider than ptrdiff_t.  */
  اگر (TYPE_PRECISION (restype) < TYPE_PRECISION (درخت_TYPE (op0)))
    inttype = c_common_type_for_سائز (TYPE_PRECISION (درخت_TYPE (op0)), 0);
  ورنہ
    inttype = restype;

  اگر (VOID_TYPE_P (ہدف_type))
    pedwarn (loc, OPT_Wpointer_arith,
	     "pointer of type %<void *%> used in subtraction");
  اگر (درخت_رمز (ہدف_type) == FUNCTION_TYPE)
    pedwarn (loc, OPT_Wpointer_arith,
	     "pointer to a function used in subtraction");

  اگر (current_function_decl != NULL_درخت
      && sanitize_flags_p (SANITIZE_اشارہ_گر_تفریق))
    {
      op0 = save_اظہاریہ (c_fully_fold (op0, جھوٹ, تہی));
      op1 = save_اظہاریہ (c_fully_fold (op1, جھوٹ, تہی));

      درخت tt = builtin_decl_explicit (BUILT_اندر_ASAN_اشارہ_گر_تفریق);
      *instrument_اظہاریہ = build_call_اظہاریہ_loc (loc, tt, 2, op0, op1);
    }

  /* First do the subtraction, then build the divide operator
     and only convert at the very end.
     Do not do default conversions in case restype is a short type.  */

  /* POINTER_DIFF_EXPR requires a signed integer type of the same size as
     pointers.  If some platform cannot provide that, or has a larger
     ptrdiff_type to support differences larger than half the address
     space, cast the pointers to some larger integer type and do the
     computations in that type.  */
  اگر (TYPE_PRECISION (inttype) > TYPE_PRECISION (درخت_TYPE (op0)))
    op0 = build_ثنائی_op (loc, MINUS_اظہاریہ, convert (inttype, op0),
			   convert (inttype, op1), جھوٹ);
  ورنہ
    {
      /* Cast away qualifiers.  */
      op0 = convert (c_common_type (درخت_TYPE (op0), درخت_TYPE (op0)), op0);
      op1 = convert (c_common_type (درخت_TYPE (op1), درخت_TYPE (op1)), op1);
      op0 = build2_loc (loc, اشارہ_گر_DIFF_اظہاریہ, inttype, op0, op1);
    }

  /* This generates an error if op1 is pointer to incomplete type.  */
  اگر (!COMPLETE_OR_VOID_TYPE_P (درخت_TYPE (درخت_TYPE (orig_op1))))
    error_at (loc, "arithmetic on pointer to an incomplete type");
  ورنہ اگر (verify_type_context (loc, TCTX_اشارہ_گر_ARITH,
				درخت_TYPE (درخت_TYPE (orig_op0))))
    verify_type_context (loc, TCTX_اشارہ_گر_ARITH,
			 درخت_TYPE (درخت_TYPE (orig_op1)));

  op1 = c_سائز_اندر_بائٹیں (ہدف_type);

  اگر (اشارہ_گر_مقصد_zero_sized_aggr_p (درخت_TYPE (orig_op1)))
    error_at (loc, "arithmetic on pointer to an empty aggregate");

  /* Divide by the size, in easiest possible way.  */
  نتیجہ = fold_build2_loc (loc, EXACT_DIV_اظہاریہ, inttype,
			    op0, convert (inttype, op1));

  /* Convert to final result type if necessary.  */
  واپس convert (restype, نتیجہ);
}

/* Expand atomic compound assignments into an appropriate sequence as
   specified by the C11 standard section 6.5.16.2.

       _Atomic T1 E1
       T2 E2
       E1 op= E2

  This sequence is used for all types for which these operations are
  supported.

  In addition, built-in versions of the 'fe' prefixed routines may
  need to be invoked for floating point (real, complex or vector) when
  floating-point exceptions are supported.  See 6.5.16.2 footnote 113.

  T1 newval;
  T1 old;
  T1 *addr
  T2 val
  fenv_t fenv

  addr = &E1;
  val = (E2);
  __atomic_load (addr, &old, SEQ_CST);
  feholdexcept (&fenv);
loop:
    newval = old op val;
    if (__atomic_compare_exchange_strong (addr, &old, &newval, SEQ_CST,
					  SEQ_CST))
      goto done;
    feclearexcept (FE_ALL_EXCEPT);
    goto loop:
done:
  feupdateenv (&fenv);

  The compiler will issue the __atomic_fetch_* built-in when possible,
  otherwise it will generate the generic form of the atomic operations.
  This requires temp(s) and has their address taken.  The atomic processing
  is smart enough to figure out when the size of an object can utilize
  a lock-free version, and convert the built-in call to the appropriate
  lock-free routine.  The optimizers will then dispose of any temps that
  are no longer required, and lock-free implementations are utilized as
  long as there is target support for the required size.

  If the operator is NOP_EXPR, then this is a simple assignment, and
  an __atomic_store is issued to perform the assignment rather than
  the above loop.  */

/* Build an atomic assignment at LOC, expanding into the proper
   sequence to store LHS MODIFYCODE= RHS.  Return a value representing
   the result of the operation, unless RETURN_OLD_P, in which case
   return the old value of LHS (this is only for postincrement and
   postdecrement).  */

ساکن درخت
build_atomic_تفویض (location_t loc, درخت lhs, شمار درخت_رمز_2 modifycode,
		     درخت rhs, منطقی return_old_p)
{
  درخت fndecl, func_call;
  vec<درخت, va_gc> *params;
  درخت val, nonatomic_lhs_type, nonatomic_rhs_type, newval, newval_addr;
  درخت old, old_addr;
  درخت compound_stmt = NULL_درخت;
  درخت stmt, goto_stmt;
  درخت loop_label, loop_decl, مکمل_label, مکمل_decl;

  درخت lhs_type = درخت_TYPE (lhs);
  درخت lhs_addr = build_unary_op (loc, ADDR_اظہاریہ, lhs, جھوٹ);
  درخت seq_cst = build_int_cst (integer_type_گرہ, MEMMODEL_SEQ_CST);
  درخت rhs_semantic_type = درخت_TYPE (rhs);
  درخت nonatomic_rhs_semantic_type;
  درخت rhs_type;

  gcc_assert (TYPE_ATOMIC (lhs_type));

  اگر (return_old_p)
    gcc_assert (modifycode == PLUS_اظہاریہ || modifycode == MINUS_اظہاریہ);

  /* Allocate enough vector items for a compare_exchange.  */
  vec_alloc (params, 6);

  /* Create a compound statement to hold the sequence of statements
     with a loop.  */
  اگر (modifycode != NOP_اظہاریہ)
    {
      compound_stmt = c_begin_compound_stmt (جھوٹ);

      /* For consistency with build_modify_expr on non-_Atomic,
	 mark the lhs as read.  Also, it would be very hard to match
	 such expressions in mark_exp_read.  */
      mark_exp_read (lhs);
    }

  /* Remove any excess precision (which is only present here in the
     case of compound assignments).  */
  اگر (درخت_رمز (rhs) == EXCESS_PRECISION_اظہاریہ)
    {
      gcc_assert (modifycode != NOP_اظہاریہ);
      rhs = درخت_عملیہ (rhs, 0);
    }
  rhs_type = درخت_TYPE (rhs);

  /* Fold the RHS if it hasn't already been folded.  */
  اگر (modifycode != NOP_اظہاریہ)
    rhs = c_fully_fold (rhs, جھوٹ, تہی);

  /* Remove the qualifiers for the rest of the expressions and create
     the VAL temp variable to hold the RHS.  */
  nonatomic_lhs_type = build_qualified_type (lhs_type, TYPE_UNQUALIFIED);
  nonatomic_rhs_type = build_qualified_type (rhs_type, TYPE_UNQUALIFIED);
  nonatomic_rhs_semantic_type = build_qualified_type (rhs_semantic_type,
						      TYPE_UNQUALIFIED);
  val = create_tmp_var_raw (nonatomic_rhs_type);
  درخت_ADDRESSABLE (val) = 1;
  suppress_warning (val);
  rhs = build4 (ہدف_اظہاریہ, nonatomic_rhs_type, val, rhs, NULL_درخت,
		NULL_درخت);
  درخت_SIDE_EFFECTS (rhs) = 1;
  سیٹ_اظہاریہ_LOCATION (rhs, loc);
  اگر (modifycode != NOP_اظہاریہ)
    جوڑو_stmt (rhs);

  /* NOP_EXPR indicates it's a straight store of the RHS. Simply issue
     an atomic_store.  */
  اگر (modifycode == NOP_اظہاریہ)
    {
      compound_stmt = rhs;
      /* Build __atomic_store (&lhs, &val, SEQ_CST)  */
      rhs = build_unary_op (loc, ADDR_اظہاریہ, val, جھوٹ);
      fndecl = builtin_decl_explicit (BUILT_اندر_ATOMIC_STORE);
      params->تیز_ڈالو (lhs_addr);
      params->تیز_ڈالو (rhs);
      params->تیز_ڈالو (seq_cst);
      func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, تہی);

      compound_stmt = build2 (COMPOUND_اظہاریہ, void_type_گرہ,
			      compound_stmt, func_call);

      /* VAL is the value which was stored, return a COMPOUND_STMT of
	 the statement and that value.  */
      واپس build2 (COMPOUND_اظہاریہ, nonatomic_lhs_type, compound_stmt, val);
    }

  /* Attempt to implement the atomic operation as an __atomic_fetch_* or
     __atomic_*_fetch built-in rather than a CAS loop.  atomic_bool type
     isn't applicable for such builtins.  ??? Do we want to handle enums?  */
  اگر ((درخت_رمز (lhs_type) == INTEGER_TYPE || اشارہ_گر_TYPE_P (lhs_type))
      && درخت_رمز (rhs_type) == INTEGER_TYPE)
    {
      built_اندر_function fncode;
      انتخاب (modifycode)
	{
	حالت PLUS_اظہاریہ:
	حالت اشارہ_گر_PLUS_اظہاریہ:
	  fncode = (return_old_p
		    ? BUILT_اندر_ATOMIC_FETCH_جوڑو_N
		    : BUILT_اندر_ATOMIC_جوڑو_FETCH_N);
	  توڑو;
	حالت MINUS_اظہاریہ:
	  fncode = (return_old_p
		    ? BUILT_اندر_ATOMIC_FETCH_SUB_N
		    : BUILT_اندر_ATOMIC_SUB_FETCH_N);
	  توڑو;
	حالت ثنائی_ہندسہ_AND_اظہاریہ:
	  fncode = (return_old_p
		    ? BUILT_اندر_ATOMIC_FETCH_AND_N
		    : BUILT_اندر_ATOMIC_AND_FETCH_N);
	  توڑو;
	حالت ثنائی_ہندسہ_IOR_اظہاریہ:
	  fncode = (return_old_p
		    ? BUILT_اندر_ATOMIC_FETCH_OR_N
		    : BUILT_اندر_ATOMIC_OR_FETCH_N);
	  توڑو;
	حالت ثنائی_ہندسہ_XOR_اظہاریہ:
	  fncode = (return_old_p
		    ? BUILT_اندر_ATOMIC_FETCH_XOR_N
		    : BUILT_اندر_ATOMIC_XOR_FETCH_N);
	  توڑو;
	طےشدہ:
	  جاؤ cas_loop;
	}

      /* We can only use "_1" through "_16" variants of the atomic fetch
	 built-ins.  */
      غیرعلامتی HOST_WIDE_INT سائز = درخت_مقصد_uhwi (TYPE_سائز_UNIT (lhs_type));
      اگر (سائز != 1 && سائز != 2 && سائز != 4 && سائز != 8 && سائز != 16)
	جاؤ cas_loop;

      /* If this is a pointer type, we need to multiply by the size of
	 the pointer target type.  */
      اگر (اشارہ_گر_TYPE_P (lhs_type))
	{
	  اگر (!COMPLETE_TYPE_P (درخت_TYPE (lhs_type))
	      /* ??? This would introduce -Wdiscarded-qualifiers
		 warning: __atomic_fetch_* expect volatile void *
		 type as the first argument.  (Assignments between
		 atomic and non-atomic objects are OK.) */
	      || TYPE_RESTRICT (lhs_type))
	    جاؤ cas_loop;
	  درخت sz = TYPE_سائز_UNIT (درخت_TYPE (lhs_type));
	  rhs = fold_build2_loc (loc, MULT_اظہاریہ, ptrdiff_type_گرہ,
				 convert (ptrdiff_type_گرہ, rhs),
				 convert (ptrdiff_type_گرہ, sz));
	}

      /* Build __atomic_fetch_* (&lhs, &val, SEQ_CST), or
	 __atomic_*_fetch (&lhs, &val, SEQ_CST).  */
      fndecl = builtin_decl_explicit (fncode);
      params->تیز_ڈالو (lhs_addr);
      params->تیز_ڈالو (rhs);
      params->تیز_ڈالو (seq_cst);
      func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, تہی);

      newval = create_tmp_var_raw (nonatomic_lhs_type);
      درخت_ADDRESSABLE (newval) = 1;
      suppress_warning (newval);
      rhs = build4 (ہدف_اظہاریہ, nonatomic_lhs_type, newval, func_call,
		    NULL_درخت, NULL_درخت);
      سیٹ_اظہاریہ_LOCATION (rhs, loc);
      جوڑو_stmt (rhs);

      /* Finish the compound statement.  */
      compound_stmt = c_انتہا_compound_stmt (loc, compound_stmt, جھوٹ);

      /* NEWVAL is the value which was stored, return a COMPOUND_STMT of
	 the statement and that value.  */
      واپس build2 (COMPOUND_اظہاریہ, nonatomic_lhs_type, compound_stmt, newval);
    }

cas_loop:
  /* Create the variables and labels required for the op= form.  */
  old = create_tmp_var_raw (nonatomic_lhs_type);
  old_addr = build_unary_op (loc, ADDR_اظہاریہ, old, جھوٹ);
  درخت_ADDRESSABLE (old) = 1;
  suppress_warning (old);

  newval = create_tmp_var_raw (nonatomic_lhs_type);
  newval_addr = build_unary_op (loc, ADDR_اظہاریہ, newval, جھوٹ);
  درخت_ADDRESSABLE (newval) = 1;
  suppress_warning (newval);

  loop_decl = create_artificial_label (loc);
  loop_label = build1 (LABEL_اظہاریہ, void_type_گرہ, loop_decl);

  مکمل_decl = create_artificial_label (loc);
  مکمل_label = build1 (LABEL_اظہاریہ, void_type_گرہ, مکمل_decl);

  /* __atomic_load (addr, &old, SEQ_CST).  */
  fndecl = builtin_decl_explicit (BUILT_اندر_ATOMIC_بھرو);
  params->تیز_ڈالو (lhs_addr);
  params->تیز_ڈالو (old_addr);
  params->تیز_ڈالو (seq_cst);
  func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, تہی);
  old = build4 (ہدف_اظہاریہ, nonatomic_lhs_type, old, func_call, NULL_درخت,
		NULL_درخت);
  جوڑو_stmt (old);
  params->truncate (0);

  /* Create the expressions for floating-point environment
     manipulation, if required.  */
  منطقی need_fenv = (flag_trapping_math
		    && (FLOAT_TYPE_P (lhs_type) || FLOAT_TYPE_P (rhs_type)));
  درخت hold_call = NULL_درخت, clear_call = NULL_درخت, update_call = NULL_درخت;
  اگر (need_fenv)
    targetm.atomic_تفویض_expand_fenv (&hold_call, &clear_call, &update_call);

  اگر (hold_call)
    جوڑو_stmt (hold_call);

  /* loop:  */
  جوڑو_stmt (loop_label);

  /* newval = old + val;  */
  اگر (rhs_type != rhs_semantic_type)
    val = build1 (EXCESS_PRECISION_اظہاریہ, nonatomic_rhs_semantic_type, val);
  rhs = build_ثنائی_op (loc, modifycode,
			 convert_lvalue_مقصد_rvalue (loc, old, سچ, سچ),
			 val, سچ);
  اگر (درخت_رمز (rhs) == EXCESS_PRECISION_اظہاریہ)
    {
      درخت eptype = درخت_TYPE (rhs);
      rhs = c_fully_fold (درخت_عملیہ (rhs, 0), جھوٹ, تہی);
      rhs = build1 (EXCESS_PRECISION_اظہاریہ, eptype, rhs);
    }
  ورنہ
    rhs = c_fully_fold (rhs, جھوٹ, تہی);
  rhs = convert_for_assignment (loc, UNKNOWN_LOCATION, nonatomic_lhs_type,
				rhs, NULL_درخت, ic_تفویض, جھوٹ, NULL_درخت,
				NULL_درخت, 0);
  /* The temporary variable for NEWVAL is only gimplified correctly (in
     particular, given a DECL_CONTEXT) if used in a TARGET_EXPR.  To avoid
     subsequent ICEs in nested function processing after an error, ensure such
     a TARGET_EXPR is built even after an error.  */
  اگر (rhs == error_mark_گرہ)
    rhs = old;
  rhs = build4 (ہدف_اظہاریہ, nonatomic_lhs_type, newval, rhs, NULL_درخت,
		NULL_درخت);
  سیٹ_اظہاریہ_LOCATION (rhs, loc);
  جوڑو_stmt (rhs);

  /* if (__atomic_compare_exchange (addr, &old, &new, false, SEQ_CST, SEQ_CST))
       goto done;  */
  fndecl = builtin_decl_explicit (BUILT_اندر_ATOMIC_COMPARE_EXCHANGE);
  params->تیز_ڈالو (lhs_addr);
  params->تیز_ڈالو (old_addr);
  params->تیز_ڈالو (newval_addr);
  params->تیز_ڈالو (integer_zero_گرہ);
  params->تیز_ڈالو (seq_cst);
  params->تیز_ڈالو (seq_cst);
  func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, تہی);

  goto_stmt = build1 (GOTO_اظہاریہ, void_type_گرہ, مکمل_decl);
  سیٹ_اظہاریہ_LOCATION (goto_stmt, loc);

  stmt = build3 (COND_اظہاریہ, void_type_گرہ, func_call, goto_stmt, NULL_درخت);
  سیٹ_اظہاریہ_LOCATION (stmt, loc);
  جوڑو_stmt (stmt);

  اگر (clear_call)
    جوڑو_stmt (clear_call);

  /* goto loop;  */
  goto_stmt  = build1 (GOTO_اظہاریہ, void_type_گرہ, loop_decl);
  سیٹ_اظہاریہ_LOCATION (goto_stmt, loc);
  جوڑو_stmt (goto_stmt);

  /* done:  */
  جوڑو_stmt (مکمل_label);

  اگر (update_call)
    جوڑو_stmt (update_call);

  /* Finish the compound statement.  */
  compound_stmt = c_انتہا_compound_stmt (loc, compound_stmt, جھوٹ);

  /* NEWVAL is the value that was successfully stored, return a
     COMPOUND_EXPR of the statement and the appropriate value.  */
  واپس build2 (COMPOUND_اظہاریہ, nonatomic_lhs_type, compound_stmt,
		 return_old_p ? old : newval);
}

/* Construct and perhaps optimize a tree representation
   for a unary operation.  CODE, a tree_code, specifies the operation
   and XARG is the operand.
   For any CODE other than ADDR_EXPR, NOCONVERT suppresses the default
   promotions (such as from short to int).
   For ADDR_EXPR, the default promotions are not applied; NOCONVERT allows
   non-lvalues; this is only used to handle conversion of non-lvalue arrays
   to pointers in C99.

   LOCATION is the location of the operator.  */

درخت
build_unary_op (location_t location, شمار درخت_رمز_2 رمز, درخت xarg,
		منطقی noconvert)
{
  /* No default_conversion here.  It causes trouble for ADDR_EXPR.  */
  درخت arg = xarg;
  درخت argtype = NULL_درخت;
  شمار درخت_رمز_2 typecode;
  درخت val;
  درخت ret = error_mark_گرہ;
  درخت eptype = NULL_درخت;
  ثابت حرف *invalid_op_diag;

  /* If ARG is wrapped in a call to .ACCESS_WITH_SIZE — created when the
     C parser rvalue-converts a counted_by-annotated member access (see
     PR123569) — unwrap it here.  Unary operators that consume an rvalue
     (!, -, +) read the value itself rather than dereferencing into the
     pointed-to data, so the bounds-checking wrapper is unnecessary and
     would otherwise reach build_unary_op while it is not equipped to
     handle the wrapped form.  PR123569 fixed the ++/-- side of this by
     suppressing wrapper creation in the parser; the rvalue-consuming
     ops still receive the wrapper and need to strip it here.  */
  اگر (is_access_with_سائز_p (arg))
    xarg = arg = get_ref_from_access_with_سائز (arg);

  gcc_checking_assert (!is_access_with_سائز_p (arg));

  منطقی int_operands = اظہاریہ_INT_CONST_OPERANDS (xarg);
  اگر (int_operands)
    arg = remove_c_maybe_const_اظہاریہ (arg);

  اگر (رمز != ADDR_اظہاریہ)
    arg = require_complete_type (location, arg);

  typecode = درخت_رمز (درخت_TYPE (arg));
  اگر (typecode == ERROR_MARK)
    واپس error_mark_گرہ;
  اگر (typecode == ENUMERAL_TYPE || typecode == BOOLEAN_TYPE)
    typecode = INTEGER_TYPE;

  اگر ((invalid_op_diag
       = targetm.invalid_unary_op (رمز, درخت_TYPE (xarg))))
    {
      error_at (location, invalid_op_diag);
      واپس error_mark_گرہ;
    }

  اگر (درخت_رمز (arg) == EXCESS_PRECISION_اظہاریہ)
    {
      eptype = درخت_TYPE (arg);
      arg = درخت_عملیہ (arg, 0);
    }

  انتخاب (رمز)
    {
    حالت CONVERT_اظہاریہ:
      /* This is used for unary plus, because a CONVERT_EXPR
	 is enough to prevent anybody from looking inside for
	 associativity, but won't generate any code.  */
      اگر (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE
	    || typecode == FIXED_نقطہ_TYPE || typecode == COMPLEX_TYPE
	    || typecode == BITINT_TYPE
	    || gnu_سمتیہ_type_p (درخت_TYPE (arg))))
	{
	  error_at (location, "wrong type argument to unary plus");
	  واپس error_mark_گرہ;
	}
      ورنہ اگر (!noconvert)
	arg = default_conversion (arg);
      arg = non_lvalue_loc (location, arg);
      توڑو;

    حالت NEGATE_اظہاریہ:
      اگر (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE
	    || typecode == FIXED_نقطہ_TYPE || typecode == COMPLEX_TYPE
	    || typecode == BITINT_TYPE
	    || gnu_سمتیہ_type_p (درخت_TYPE (arg))))
	{
	  error_at (location, "wrong type argument to unary minus");
	  واپس error_mark_گرہ;
	}
      ورنہ اگر (!noconvert)
	arg = default_conversion (arg);
      توڑو;

    حالت ثنائی_ہندسہ_NOT_اظہاریہ:
      /* ~ works on integer types and non float vectors. */
      اگر (typecode == INTEGER_TYPE
	  || typecode == BITINT_TYPE
	  || (gnu_سمتیہ_type_p (درخت_TYPE (arg))
	      && !سمتیہ_FLOAT_TYPE_P (درخت_TYPE (arg))))
	{
	  درخت e = arg;

	  /* Warn if the expression has boolean value.  */
	  جب (درخت_رمز (e) == COMPOUND_اظہاریہ)
	    e = درخت_عملیہ (e, 1);

	  اگر ((C_BOOLEAN_TYPE_P (درخت_TYPE (arg))
	       || truth_قدر_p (درخت_رمز (e))))
	    {
	      auto_diagnostic_گروہ d;
	      اگر (warning_at (location, OPT_Wbool_operation,
				"%<~%> on a boolean expression"))
		{
		  gcc_rich_location richloc (location);
		  richloc.جوڑو_fixit_داخل_کرو_before (location, "!");
		  inform (&richloc, "did you mean to use logical not?");
		}
	    }
	  اگر (!noconvert)
	    arg = default_conversion (arg);
	}
      ورنہ اگر (typecode == COMPLEX_TYPE)
	{
	  رمز = CONJ_اظہاریہ;
	  pedwarn (location, OPT_Wpedantic,
		   "ISO C does not support %<~%> for complex conjugation");
	  اگر (!noconvert)
	    arg = default_conversion (arg);
	}
      ورنہ
	{
	  error_at (location, "wrong type argument to bit-complement");
	  واپس error_mark_گرہ;
	}
      توڑو;

    حالت ABS_اظہاریہ:
      اگر (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE))
	{
	  error_at (location, "wrong type argument to abs");
	  واپس error_mark_گرہ;
	}
      ورنہ اگر (!noconvert)
	arg = default_conversion (arg);
      توڑو;

    حالت ABSU_اظہاریہ:
      اگر (!(typecode == INTEGER_TYPE))
	{
	  error_at (location, "wrong type argument to absu");
	  واپس error_mark_گرہ;
	}
      ورنہ اگر (!noconvert)
	arg = default_conversion (arg);
      توڑو;

    حالت CONJ_اظہاریہ:
      /* Conjugating a real value is a no-op, but allow it anyway.  */
      اگر (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE
	    || typecode == COMPLEX_TYPE))
	{
	  error_at (location, "wrong type argument to conjugation");
	  واپس error_mark_گرہ;
	}
      ورنہ اگر (!noconvert)
	arg = default_conversion (arg);
      توڑو;

    حالت TRUTH_NOT_اظہاریہ:
      اگر (typecode != INTEGER_TYPE && typecode != FIXED_نقطہ_TYPE
	  && typecode != REAL_TYPE && typecode != اشارہ_گر_TYPE
	  && typecode != COMPLEX_TYPE && typecode != NULLPTR_TYPE
	  && typecode != BITINT_TYPE)
	{
	  error_at (location,
		    "wrong type argument to unary exclamation mark");
	  واپس error_mark_گرہ;
	}
      اگر (int_operands)
	{
	  arg = c_objc_common_truthvalue_conversion (location, xarg);
	  arg = remove_c_maybe_const_اظہاریہ (arg);
	}
      ورنہ
	arg = c_objc_common_truthvalue_conversion (location, arg);
      ret = invert_truthvalue_loc (location, arg);
      eptype = NULL_درخت;
      /* If the TRUTH_NOT_EXPR has been folded, reset the location.  */
      اگر (اظہاریہ_P (ret) && اظہاریہ_HAS_LOCATION (ret))
	location = اظہاریہ_LOCATION (ret);
      جاؤ return_build_unary_op;

    حالت REALPART_اظہاریہ:
    حالت IMAGPART_اظہاریہ:
      ret = build_real_imag_اظہاریہ (location, رمز, arg);
      اگر (ret == error_mark_گرہ)
	واپس error_mark_گرہ;
      اگر (eptype && درخت_رمز (eptype) == COMPLEX_TYPE)
	eptype = درخت_TYPE (eptype);
      جاؤ return_build_unary_op;

    حالت PREINCREMENT_اظہاریہ:
    حالت POSTINCREMENT_اظہاریہ:
    حالت PREDECREMENT_اظہاریہ:
    حالت POSTDECREMENT_اظہاریہ:

      اگر (درخت_رمز (arg) == C_MAYBE_CONST_اظہاریہ)
	{
	  درخت inner = build_unary_op (location, رمز,
				       C_MAYBE_CONST_اظہاریہ_اظہاریہ (arg),
				       noconvert);
	  اگر (inner == error_mark_گرہ)
	    واپس error_mark_گرہ;
	  ret = build2 (C_MAYBE_CONST_اظہاریہ, درخت_TYPE (inner),
			C_MAYBE_CONST_اظہاریہ_PRE (arg), inner);
	  gcc_assert (!C_MAYBE_CONST_اظہاریہ_INT_OPERANDS (arg));
	  C_MAYBE_CONST_اظہاریہ_NON_CONST (ret) = 1;
	  جاؤ return_build_unary_op;
	}

      /* Complain about anything that is not a true lvalue.  In
	 Objective-C, skip this check for property_refs.  */
      اگر (!objc_is_property_ref (arg)
	  && !lvalue_or_else (location,
			      arg, ((رمز == PREINCREMENT_اظہاریہ
				     || رمز == POSTINCREMENT_اظہاریہ)
				    ? lv_increment
				    : lv_decrement)))
	واپس error_mark_گرہ;

      اگر (warn_cxx_compat && درخت_رمز (درخت_TYPE (arg)) == ENUMERAL_TYPE)
	{
	  اگر (رمز == PREINCREMENT_اظہاریہ || رمز == POSTINCREMENT_اظہاریہ)
	    warning_at (location, OPT_Wc___compat,
			"increment of enumeration value is invalid in C++");
	  ورنہ
	    warning_at (location, OPT_Wc___compat,
			"decrement of enumeration value is invalid in C++");
	}

      اگر (C_BOOLEAN_TYPE_P (درخت_TYPE (arg)))
	{
	  اگر (رمز == PREINCREMENT_اظہاریہ || رمز == POSTINCREMENT_اظہاریہ)
	    warning_at (location, OPT_Wbool_operation,
			"increment of a boolean expression");
	  ورنہ
	    warning_at (location, OPT_Wbool_operation,
			"decrement of a boolean expression");
	}

      /* Ensure the argument is fully folded inside any SAVE_EXPR.  */
      arg = c_fully_fold (arg, جھوٹ, تہی, سچ);

      منطقی atomic_op;
      atomic_op = really_atomic_lvalue (arg);

      /* Increment or decrement the real part of the value,
	 and don't change the imaginary part.  */
      اگر (typecode == COMPLEX_TYPE)
	{
	  درخت real, imag;

	  pedwarn_c23 (location, OPT_Wpedantic,
		       "ISO C does not support %<++%> and %<--%> on complex "
		       "types before C2Y");

	  اگر (!atomic_op)
	    {
	      arg = stabilize_reference (arg);
	      real = build_unary_op (اظہاریہ_LOCATION (arg), REALPART_اظہاریہ, arg,
				     سچ);
	      imag = build_unary_op (اظہاریہ_LOCATION (arg), IMAGPART_اظہاریہ, arg,
				     سچ);
	      real = build_unary_op (اظہاریہ_LOCATION (arg), رمز, real, سچ);
	      اگر (real == error_mark_گرہ || imag == error_mark_گرہ)
		واپس error_mark_گرہ;
	      ret = build2 (COMPLEX_اظہاریہ, درخت_TYPE (arg),
			    real, imag);
	      جاؤ return_build_unary_op;
	    }
	}

      /* Report invalid types.  */

      اگر (typecode != اشارہ_گر_TYPE && typecode != FIXED_نقطہ_TYPE
	  && typecode != INTEGER_TYPE && typecode != REAL_TYPE
	  && typecode != COMPLEX_TYPE && typecode != BITINT_TYPE
	  && !gnu_سمتیہ_type_p (درخت_TYPE (arg)))
	{
	  اگر (رمز == PREINCREMENT_اظہاریہ || رمز == POSTINCREMENT_اظہاریہ)
	    error_at (location, "wrong type argument to increment");
	  ورنہ
	    error_at (location, "wrong type argument to decrement");

	  واپس error_mark_گرہ;
	}

      {
	درخت inc;

	argtype = درخت_TYPE (arg);

	/* Compute the increment.  */

	اگر (typecode == اشارہ_گر_TYPE)
	  {
	    /* If pointer target is an incomplete type,
	       we just cannot know how to do the arithmetic.  */
	    اگر (!COMPLETE_OR_VOID_TYPE_P (درخت_TYPE (argtype)))
	      {
		اگر (رمز == PREINCREMENT_اظہاریہ || رمز == POSTINCREMENT_اظہاریہ)
		  error_at (location,
			    "increment of pointer to an incomplete type %qT",
			    درخت_TYPE (argtype));
		ورنہ
		  error_at (location,
			    "decrement of pointer to an incomplete type %qT",
			    درخت_TYPE (argtype));
	      }
	    ورنہ اگر (درخت_رمز (درخت_TYPE (argtype)) == FUNCTION_TYPE
		     || VOID_TYPE_P (درخت_TYPE (argtype)))
	      {
		اگر (رمز == PREINCREMENT_اظہاریہ || رمز == POSTINCREMENT_اظہاریہ)
		  pedwarn (location, OPT_Wpointer_arith,
			   "wrong type argument to increment");
		ورنہ
		  pedwarn (location, OPT_Wpointer_arith,
			   "wrong type argument to decrement");
	      }
	    ورنہ
	      verify_type_context (location, TCTX_اشارہ_گر_ARITH,
				   درخت_TYPE (argtype));

	    inc = c_سائز_اندر_بائٹیں (درخت_TYPE (argtype));
	    inc = convert_مقصد_ptrofftype_loc (location, inc);
	  }
	ورنہ اگر (FRACT_منوال_P (TYPE_منوال (argtype)))
	  {
	    /* For signed fract types, we invert ++ to -- or
	       -- to ++, and change inc from 1 to -1, because
	       it is not possible to represent 1 in signed fract constants.
	       For unsigned fract types, the result always overflows and
	       we get an undefined (original) or the maximum value.  */
	    اگر (رمز == PREINCREMENT_اظہاریہ)
	      رمز = PREDECREMENT_اظہاریہ;
	    ورنہ اگر (رمز == PREDECREMENT_اظہاریہ)
	      رمز = PREINCREMENT_اظہاریہ;
	    ورنہ اگر (رمز == POSTINCREMENT_اظہاریہ)
	      رمز = POSTDECREMENT_اظہاریہ;
	    ورنہ /* code == POSTDECREMENT_EXPR  */
	      رمز = POSTINCREMENT_اظہاریہ;

	    inc = integer_minus_one_گرہ;
	    inc = convert (argtype, inc);
	  }
	ورنہ
	  {
	    inc = سمتیہ_TYPE_P (argtype)
	      ? build_one_cst (argtype)
	      : integer_one_گرہ;
	    inc = convert (argtype, inc);
	  }

	/* If 'arg' is an Objective-C PROPERTY_REF expression, then we
	   need to ask Objective-C to build the increment or decrement
	   expression for it.  */
	اگر (objc_is_property_ref (arg))
	  واپس objc_build_incr_اظہاریہ_for_property_ref (location, رمز,
							arg, inc);

	/* Report a read-only lvalue.  */
	اگر (TYPE_READONLY (argtype))
	  {
	    readonly_error (location, arg,
			    ((رمز == PREINCREMENT_اظہاریہ
			      || رمز == POSTINCREMENT_اظہاریہ)
			     ? lv_increment : lv_decrement));
	    واپس error_mark_گرہ;
	  }
	ورنہ اگر (درخت_READONLY (arg))
	  readonly_warning (arg,
			    ((رمز == PREINCREMENT_اظہاریہ
			      || رمز == POSTINCREMENT_اظہاریہ)
			     ? lv_increment : lv_decrement));

	/* If the argument is atomic, use the special code sequences for
	   atomic compound assignment.  */
	اگر (atomic_op)
	  {
	    arg = stabilize_reference (arg);
	    ret = build_atomic_تفویض (location, arg,
				       ((رمز == PREINCREMENT_اظہاریہ
					 || رمز == POSTINCREMENT_اظہاریہ)
					? PLUS_اظہاریہ
					: MINUS_اظہاریہ),
				       (FRACT_منوال_P (TYPE_منوال (argtype))
					? inc
					: integer_one_گرہ),
				       (رمز == POSTINCREMENT_اظہاریہ
					|| رمز == POSTDECREMENT_اظہاریہ));
	    جاؤ return_build_unary_op;
	  }

	درخت true_res;
	اگر (c_hardbool_type_attr (درخت_TYPE (arg), تہی, &true_res))
	  {
	    درخت larg = stabilize_reference (arg);
	    درخت sarg = save_اظہاریہ (larg);
	    انتخاب (رمز)
	      {
	      حالت PREINCREMENT_اظہاریہ:
		val = build2 (MODIFY_اظہاریہ, درخت_TYPE (larg), larg, true_res);
		val = build2 (COMPOUND_اظہاریہ, درخت_TYPE (larg), sarg, val);
		توڑو;
	      حالت POSTINCREMENT_اظہاریہ:
		val = build2 (MODIFY_اظہاریہ, درخت_TYPE (larg), larg, true_res);
		val = build2 (COMPOUND_اظہاریہ, درخت_TYPE (larg), val, sarg);
		val = build2 (COMPOUND_اظہاریہ, درخت_TYPE (larg), sarg, val);
		توڑو;
	      حالت PREDECREMENT_اظہاریہ:
		{
		  درخت rarg = convert_lvalue_مقصد_rvalue (location, sarg,
							سچ, سچ);
		  rarg = invert_truthvalue_loc (location, rarg);
		  rarg = convert (درخت_TYPE (sarg), rarg);
		  val = build2 (MODIFY_اظہاریہ, درخت_TYPE (larg), larg, rarg);
		}
		توڑو;
	      حالت POSTDECREMENT_اظہاریہ:
		{
		  درخت rarg = convert_lvalue_مقصد_rvalue (location, sarg,
							سچ, سچ);
		  rarg = invert_truthvalue_loc (location, rarg);
		  درخت iarg = convert (درخت_TYPE (larg), rarg);
		  val = build2 (MODIFY_اظہاریہ, درخت_TYPE (larg), larg, iarg);
		  val = build2 (COMPOUND_اظہاریہ, درخت_TYPE (larg), val, sarg);
		  val = build2 (COMPOUND_اظہاریہ, درخت_TYPE (larg), sarg, val);
		}
		توڑو;
	      طےشدہ:
		gcc_unreachable ();
	      }
	    درخت_SIDE_EFFECTS (val) = 1;
	  }
	ورنہ اگر (C_BOOLEAN_TYPE_P (درخت_TYPE (arg)))
	  val = boolean_increment (رمز, arg);
	ورنہ
	  val = build2 (رمز, درخت_TYPE (arg), arg, inc);
	درخت_SIDE_EFFECTS (val) = 1;
	اگر (TYPE_QUALS (درخت_TYPE (val)) != TYPE_UNQUALIFIED)
	  درخت_TYPE (val) = c_build_qualified_type (درخت_TYPE (val),
						    TYPE_UNQUALIFIED);
	ret = val;
	جاؤ return_build_unary_op;
      }

    حالت ADDR_اظہاریہ:
      /* Note that this operation never does default_conversion.  */

      /* The operand of unary '&' must be an lvalue (which excludes
	 expressions of type void), or, in C99, the result of a [] or
	 unary '*' operator.  */
      اگر (VOID_TYPE_P (درخت_TYPE (arg))
	  && TYPE_QUALS (درخت_TYPE (arg)) == TYPE_UNQUALIFIED
	  && (!بالواسطہ_REF_P (arg) || !flag_isoc99))
	pedwarn (location, 0, "taking address of expression of type %<void%>");

      /* Let &* cancel out to simplify resulting code.  */
      اگر (بالواسطہ_REF_P (arg))
	{
	  /* Don't let this be an lvalue.  */
	  اگر (lvalue_p (درخت_عملیہ (arg, 0)))
	    واپس non_lvalue_loc (location, درخت_عملیہ (arg, 0));
	  ret = درخت_عملیہ (arg, 0);
	  جاؤ return_build_unary_op;
	}

      /* Anything not already handled and not a true memory reference
	 or a non-lvalue array is an error.  */
      اگر (typecode != FUNCTION_TYPE && !noconvert
	  && !lvalue_or_else (location, arg, lv_addressof))
	واپس error_mark_گرہ;

      /* Move address operations inside C_MAYBE_CONST_EXPR to simplify
	 folding later.  */
      اگر (درخت_رمز (arg) == C_MAYBE_CONST_اظہاریہ)
	{
	  درخت inner = build_unary_op (location, رمز,
				       C_MAYBE_CONST_اظہاریہ_اظہاریہ (arg),
				       noconvert);
	  ret = build2 (C_MAYBE_CONST_اظہاریہ, درخت_TYPE (inner),
			C_MAYBE_CONST_اظہاریہ_PRE (arg), inner);
	  gcc_assert (!C_MAYBE_CONST_اظہاریہ_INT_OPERANDS (arg));
	  C_MAYBE_CONST_اظہاریہ_NON_CONST (ret)
	    = C_MAYBE_CONST_اظہاریہ_NON_CONST (arg);
	  جاؤ return_build_unary_op;
	}

      /* Ordinary case; arg is a COMPONENT_REF or a decl.  */

      argtype = درخت_TYPE (arg);

      /* If the lvalue is const or volatile, merge that into the type
	 to which the address will point.  This is only needed
	 for function types.  */
      اگر ((DECL_P (arg) || REFERENCE_CLASS_P (arg))
	  && (درخت_READONLY (arg) || درخت_THIS_VOLATILE (arg))
	  && درخت_رمز (argtype) == FUNCTION_TYPE)
	{
	  صحیح orig_quals = TYPE_QUALS (strip_array_types (argtype));
	  صحیح quals = orig_quals;

	  اگر (درخت_READONLY (arg))
	    quals |= TYPE_QUAL_CONST;
	  اگر (درخت_THIS_VOLATILE (arg))
	    quals |= TYPE_QUAL_VOLATILE;

	  argtype = c_build_qualified_type (argtype, quals);
	}

      انتخاب (درخت_رمز (arg))
	{
	حالت COMPONENT_REF:
	  اگر (DECL_C_ثنائی_ہندسہ_میدان (درخت_عملیہ (arg, 1)))
	    {
	      error_at (location, "cannot take address of bit-field %qD",
			درخت_عملیہ (arg, 1));
	      واپس error_mark_گرہ;
	    }

	  /* fall through */

	حالت ARRAY_REF:
	  اگر (TYPE_الٹ_STORAGE_ترتیب (درخت_TYPE (درخت_عملیہ (arg, 0))))
	    {
	      اگر (!AGGREGATE_TYPE_P (درخت_TYPE (arg))
		  && !اشارہ_گر_TYPE_P (درخت_TYPE (arg))
		  && !سمتیہ_TYPE_P (درخت_TYPE (arg)))
		{
		  error_at (location, "cannot take address of scalar with "
			    "reverse storage order");
		  واپس error_mark_گرہ;
		}

	      اگر (درخت_رمز (درخت_TYPE (arg)) == ARRAY_TYPE
		  && TYPE_الٹ_STORAGE_ترتیب (درخت_TYPE (arg)))
		warning_at (location, OPT_Wscalar_storage_ترتیب,
			    "address of array with reverse scalar storage "
			    "order requested");
	    }

	طےشدہ:
	  توڑو;
	}

      اگر (!c_mark_addressable (arg))
	واپس error_mark_گرہ;

      gcc_assert (درخت_رمز (arg) != COMPONENT_REF
		  || !DECL_C_ثنائی_ہندسہ_میدان (درخت_عملیہ (arg, 1)));

      argtype = c_build_اشارہ_گر_type (argtype);

      /* ??? Cope with user tricks that amount to offsetof.  Delete this
	 when we have proper support for integer constant expressions.  */
      val = get_بنیاد_پتہ (arg);
      اگر (val && بالواسطہ_REF_P (val)
          && درخت_CONSTANT (درخت_عملیہ (val, 0)))
	{
	  ret = fold_offsetof (arg, argtype);
	  جاؤ return_build_unary_op;
	}

      val = build1 (ADDR_اظہاریہ, argtype, arg);

      ret = val;
      جاؤ return_build_unary_op;

    حالت PAREN_اظہاریہ:
      ret = build1 (رمز, درخت_TYPE (arg), arg);
      جاؤ return_build_unary_op;

    طےشدہ:
      gcc_unreachable ();
    }

  اگر (argtype == NULL_درخت)
    argtype = درخت_TYPE (arg);
  اگر (درخت_رمز (arg) == INTEGER_CST)
    ret = (require_constant_قدر
	   ? fold_build1_initializer_loc (location, رمز, argtype, arg)
	   : fold_build1_loc (location, رمز, argtype, arg));
  ورنہ
    ret = build1 (رمز, argtype, arg);
 return_build_unary_op:
  gcc_assert (ret != error_mark_گرہ);
  اگر (درخت_رمز (ret) == INTEGER_CST && !درخت_حد_سے_تجاوز (ret)
      && !(درخت_رمز (xarg) == INTEGER_CST && !درخت_حد_سے_تجاوز (xarg)))
    ret = build1 (NOP_اظہاریہ, درخت_TYPE (ret), ret);
  ورنہ اگر (درخت_رمز (ret) != INTEGER_CST && int_operands)
    ret = note_integer_operands (ret);
  اگر (eptype)
    ret = build1 (EXCESS_PRECISION_اظہاریہ, eptype, ret);
  protected_سیٹ_اظہاریہ_location (ret, location);
  واپس ret;
}

/* Return nonzero if REF is an lvalue valid for this language.
   Lvalues can be assigned, unless their type has TYPE_READONLY.
   Lvalues can have their address taken, unless they have C_DECL_REGISTER.  */

منطقی
lvalue_p (const_درخت ref)
{
  ثابت شمار درخت_رمز_2 رمز = درخت_رمز (ref);

  انتخاب (رمز)
    {
    حالت REALPART_اظہاریہ:
    حالت IMAGPART_اظہاریہ:
    حالت COMPONENT_REF:
      واپس lvalue_p (درخت_عملیہ (ref, 0));

    حالت C_MAYBE_CONST_اظہاریہ:
      واپس lvalue_p (درخت_عملیہ (ref, 1));

    حالت COMPOUND_LITERAL_اظہاریہ:
    حالت STRING_CST:
      واپس سچ;

    حالت MEM_REF:
    حالت ہدف_MEM_REF:
      /* MEM_REFs can appear from -fgimple parsing or folding, so allow them
	 here as well.  */
    حالت بالواسطہ_REF:
    حالت ARRAY_REF:
    حالت VAR_DECL:
    حالت PARM_DECL:
    حالت نتیجہ_DECL:
    حالت ERROR_MARK:
      واپس (درخت_رمز (درخت_TYPE (ref)) != FUNCTION_TYPE
	      && درخت_رمز (درخت_TYPE (ref)) != طریقہ_TYPE);

    حالت BIND_اظہاریہ:
      واپس درخت_رمز (درخت_TYPE (ref)) == ARRAY_TYPE;

    حالت CALL_اظہاریہ:
      واپس is_access_with_سائز_p (ref);

    طےشدہ:
      واپس جھوٹ;
    }
}

/* Give a warning for storing in something that is read-only in GCC
   terms but not const in ISO C terms.  */

ساکن خالی
readonly_warning (درخت arg, شمار lvalue_use use)
{
  انتخاب (use)
    {
    حالت lv_تفویض:
      warning (0, "assignment of read-only location %qE", arg);
      توڑو;
    حالت lv_increment:
      warning (0, "increment of read-only location %qE", arg);
      توڑو;
    حالت lv_decrement:
      warning (0, "decrement of read-only location %qE", arg);
      توڑو;
    طےشدہ:
      gcc_unreachable ();
    }
  واپس;
}


/* Return nonzero if REF is an lvalue valid for this language;
   otherwise, print an error message and return zero.  USE says
   how the lvalue is being used and so selects the error message.
   LOCATION is the location at which any error should be reported.  */

ساکن صحیح
lvalue_or_else (location_t loc, const_درخت ref, شمار lvalue_use use)
{
  صحیح win = lvalue_p (ref);

  اگر (!win)
    lvalue_error (loc, use);

  واپس win;
}

/* Mark EXP saying that we need to be able to take the
   address of it; it should not be allocated in a register.
   Returns true if successful.  ARRAY_REF_P is true if this
   is for ARRAY_REF construction - in that case we don't want
   to look through VIEW_CONVERT_EXPR from VECTOR_TYPE to ARRAY_TYPE,
   it is fine to use ARRAY_REFs for vector subscripts on vector
   register variables.  If OVERRIDE_REGISTER, clear DECL_REGISTER rather
   than producing an error for taking the address of a register.  */

منطقی
c_mark_addressable (درخت قوت_نما, منطقی array_ref_p, منطقی override_رجسٹر)
{
  درخت x = قوت_نما;

  جب (1)
    انتخاب (درخت_رمز (x))
      {
      حالت VIEW_CONVERT_اظہاریہ:
	اگر (array_ref_p
	    && درخت_رمز (درخت_TYPE (x)) == ARRAY_TYPE
	    && سمتیہ_TYPE_P (درخت_TYPE (درخت_عملیہ (x, 0))))
	  واپس سچ;
	x = درخت_عملیہ (x, 0);
	توڑو;

      حالت COMPONENT_REF:
	اگر (DECL_C_ثنائی_ہندسہ_میدان (درخت_عملیہ (x, 1)))
	  {
	    error ("cannot take address of bit-field %qD",
		   درخت_عملیہ (x, 1));
	    واپس جھوٹ;
	  }
	/* FALLTHRU */
      حالت ADDR_اظہاریہ:
      حالت ARRAY_REF:
      حالت REALPART_اظہاریہ:
      حالت IMAGPART_اظہاریہ:
	x = درخت_عملیہ (x, 0);
	توڑو;

      حالت COMPOUND_LITERAL_اظہاریہ:
	اگر (C_DECL_رجسٹر (COMPOUND_LITERAL_اظہاریہ_DECL (x)))
	  {
	    اگر (override_رجسٹر)
	      DECL_رجسٹر (COMPOUND_LITERAL_اظہاریہ_DECL (x)) = 0;
	    ورنہ
	      {
		error ("address of register compound literal requested");
		واپس جھوٹ;
	      }
	  }
	درخت_ADDRESSABLE (x) = 1;
	درخت_ADDRESSABLE (COMPOUND_LITERAL_اظہاریہ_DECL (x)) = 1;
	واپس سچ;

      حالت CONSTRUCTOR:
	درخت_ADDRESSABLE (x) = 1;
	واپس سچ;

      حالت VAR_DECL:
      حالت CONST_DECL:
      حالت PARM_DECL:
      حالت نتیجہ_DECL:
	اگر (C_DECL_رجسٹر (x)
	    && DECL_NONLOCAL (x))
	  {
	    اگر (درخت_عوامی (x) || is_global_var (x))
	      {
		error
		  ("global register variable %qD used in nested function", x);
		واپس جھوٹ;
	      }
	    pedwarn (داخلہ_location, 0, "register variable %qD used in nested function", x);
	  }
	ورنہ اگر (C_DECL_رجسٹر (x))
	  {
	    اگر (درخت_عوامی (x) || is_global_var (x))
	      error ("address of global register variable %qD requested", x);
	    ورنہ اگر (override_رجسٹر && !DECL_HARD_رجسٹر (x))
	      {
		DECL_رجسٹر (x) = 0;
		درخت_ADDRESSABLE (x) = 1;
		mark_decl_مستعمل (x, سچ);
		واپس سچ;
	      }
	    ورنہ
	      error ("address of register variable %qD requested", x);
	    واپس جھوٹ;
	  }

	/* FALLTHRU */
      حالت FUNCTION_DECL:
	درخت_ADDRESSABLE (x) = 1;
	mark_decl_مستعمل (x, سچ);
	/* FALLTHRU */
      طےشدہ:
	واپس سچ;
    }
}

/* Convert EXPR to TYPE, warning about conversion problems with
   constants.  SEMANTIC_TYPE is the type this conversion would use
   without excess precision. If SEMANTIC_TYPE is NULL, this function
   is equivalent to convert_and_check. This function is a wrapper that
   handles conversions that may be different than
   the usual ones because of excess precision.  */

ساکن درخت
ep_convert_and_check (location_t loc, درخت type, درخت اظہاریہ,
		      درخت semantic_type)
{
  اگر (درخت_TYPE (اظہاریہ) == type)
    واپس اظہاریہ;

  /* For C11, integer conversions may have results with excess
     precision.  */
  اگر (flag_isoc11 || !semantic_type)
    واپس convert_and_check (loc, type, اظہاریہ);

  اگر (درخت_رمز (درخت_TYPE (اظہاریہ)) == INTEGER_TYPE
      && درخت_TYPE (اظہاریہ) != semantic_type)
    {
      /* For integers, we need to check the real conversion, not
	 the conversion to the excess precision type.  */
      اظہاریہ = convert_and_check (loc, semantic_type, اظہاریہ);
    }
  /* Result type is the excess precision type, which should be
     large enough, so do not check.  */
  واپس convert (type, اظہاریہ);
}

/* If EXPR refers to a built-in declared without a prototype returns
   the actual type of the built-in and, if non-null, set *BLTIN to
   a pointer to the built-in.  Otherwise return the type of EXPR
   and clear *BLTIN if non-null.  */

ساکن درخت
type_or_builtin_type (درخت اظہاریہ, درخت *bltin = تہی)
{
  درخت dummy;
  اگر (!bltin)
    bltin = &dummy;

  *bltin = NULL_درخت;

  درخت type = درخت_TYPE (اظہاریہ);
  اگر (درخت_رمز (اظہاریہ) != ADDR_اظہاریہ)
    واپس type;

  درخت oper = درخت_عملیہ (اظہاریہ, 0);
  اگر (!DECL_P (oper)
      || درخت_رمز (oper) != FUNCTION_DECL
      || !fndecl_built_اندر_p (oper, BUILT_اندر_معمول))
    واپس type;

  built_اندر_function رمز = DECL_FUNCTION_رمز (oper);
  اگر (!C_DECL_BUILTIN_PROTOTYPE (oper))
    واپس type;

  اگر ((*bltin = builtin_decl_implicit (رمز)))
    type = c_build_اشارہ_گر_type (درخت_TYPE (*bltin));

  واپس type;
}

/* Build and return a conditional expression IFEXP ? OP1 : OP2.  If
   IFEXP_BCP then the condition is a call to __builtin_constant_p, and
   if folded to an integer constant then the unselected half may
   contain arbitrary operations not normally permitted in constant
   expressions.  Set the location of the expression to LOC.  */

درخت
build_conditional_اظہاریہ (location_t colon_loc, درخت ifexp, منطقی ifexp_bcp,
			درخت op1, درخت op1_original_type, location_t op1_loc,
			درخت op2, درخت op2_original_type, location_t op2_loc)
{
  درخت type1;
  درخت type2;
  درخت نتیجہ_type = تہی;
  درخت semantic_نتیجہ_type = تہی;
  درخت orig_op1 = op1, orig_op2 = op2;
  منطقی int_const, op1_int_operands, op2_int_operands, int_operands;
  منطقی ifexp_int_operands;
  درخت ret;

  op1_int_operands = اظہاریہ_INT_CONST_OPERANDS (orig_op1);
  اگر (op1_int_operands)
    op1 = remove_c_maybe_const_اظہاریہ (op1);
  op2_int_operands = اظہاریہ_INT_CONST_OPERANDS (orig_op2);
  اگر (op2_int_operands)
    op2 = remove_c_maybe_const_اظہاریہ (op2);
  ifexp_int_operands = اظہاریہ_INT_CONST_OPERANDS (ifexp);
  اگر (ifexp_int_operands)
    ifexp = remove_c_maybe_const_اظہاریہ (ifexp);

  /* Promote both alternatives.  */

  اگر (درخت_رمز (درخت_TYPE (op1)) != VOID_TYPE)
    op1 = default_conversion (op1);
  اگر (درخت_رمز (درخت_TYPE (op2)) != VOID_TYPE)
    op2 = default_conversion (op2);

  اگر (درخت_رمز (ifexp) == ERROR_MARK
      || درخت_رمز (درخت_TYPE (op1)) == ERROR_MARK
      || درخت_رمز (درخت_TYPE (op2)) == ERROR_MARK)
    واپس error_mark_گرہ;

  درخت bltin1 = NULL_درخت;
  درخت bltin2 = NULL_درخت;
  type1 = type_or_builtin_type (op1, &bltin1);
  ثابت شمار درخت_رمز_2 code1 = درخت_رمز (type1);
  type2 = type_or_builtin_type (op2, &bltin2);
  ثابت شمار درخت_رمز_2 code2 = درخت_رمز (type2);

  اگر (code1 == اشارہ_گر_TYPE && reject_gcc_builtin (op1))
    واپس error_mark_گرہ;

  اگر (code2 == اشارہ_گر_TYPE && reject_gcc_builtin (op2))
    واپس error_mark_گرہ;

  /* C90 does not permit non-lvalue arrays in conditional expressions.
     In C99 they will be pointers by now.  */
  اگر (code1 == ARRAY_TYPE || code2 == ARRAY_TYPE)
    {
      error_at (colon_loc, "non-lvalue array in conditional expression");
      واپس error_mark_گرہ;
    }

  اگر ((درخت_رمز (op1) == EXCESS_PRECISION_اظہاریہ
       || درخت_رمز (op2) == EXCESS_PRECISION_اظہاریہ)
      && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	  || code1 == COMPLEX_TYPE || code1 == BITINT_TYPE)
      && (code2 == INTEGER_TYPE || code2 == REAL_TYPE
	  || code2 == COMPLEX_TYPE || code2 == BITINT_TYPE))
    {
      semantic_نتیجہ_type = c_common_type (type1, type2);
      اگر (درخت_رمز (op1) == EXCESS_PRECISION_اظہاریہ)
	{
	  op1 = درخت_عملیہ (op1, 0);
	  type1 = درخت_TYPE (op1);
	  gcc_assert (درخت_رمز (type1) == code1);
	}
      اگر (درخت_رمز (op2) == EXCESS_PRECISION_اظہاریہ)
	{
	  op2 = درخت_عملیہ (op2, 0);
	  type2 = درخت_TYPE (op2);
	  gcc_assert (درخت_رمز (type2) == code2);
	}
    }

  اگر (warn_cxx_compat)
    {
      درخت t1 = op1_original_type ? op1_original_type : درخت_TYPE (orig_op1);
      درخت t2 = op2_original_type ? op2_original_type : درخت_TYPE (orig_op2);

      اگر (درخت_رمز (t1) == ENUMERAL_TYPE
	  && درخت_رمز (t2) == ENUMERAL_TYPE
	  && TYPE_MAIN_VARIANT (t1) != TYPE_MAIN_VARIANT (t2))
	warning_at (colon_loc, OPT_Wc___compat,
		    "different enum types in conditional is "
		    "invalid in C++: %qT vs %qT", t1, t2);
    }

  اگر (warn_zero_as_null_اشارہ_گر_constant
      && c_inhibit_evaluation_warnings == 0)
    {
      اگر ((code1 == اشارہ_گر_TYPE || code1 == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type2) && null_اشارہ_گر_constant_p (orig_op2))
	warning_at (op2_loc, OPT_Wzero_as_null_اشارہ_گر_constant,
		    "zero as null pointer constant");

      اگر ((code2 == اشارہ_گر_TYPE || code2 == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type1) && null_اشارہ_گر_constant_p (orig_op1))
	warning_at (op1_loc, OPT_Wzero_as_null_اشارہ_گر_constant,
		    "zero as null pointer constant");
    }

  /* Quickly detect the usual case where op1 and op2 have the same type
     after promotion.  */
  اگر (TYPE_MAIN_VARIANT (type1) == TYPE_MAIN_VARIANT (type2))
    {
      اگر (type1 == type2)
	نتیجہ_type = type1;
      ورنہ
	نتیجہ_type = TYPE_MAIN_VARIANT (type1);
    }
  ورنہ اگر ((code1 == INTEGER_TYPE || code1 == REAL_TYPE
	    || code1 == COMPLEX_TYPE || code1 == BITINT_TYPE)
	   && (code2 == INTEGER_TYPE || code2 == REAL_TYPE
	       || code2 == COMPLEX_TYPE || code2 == BITINT_TYPE))
    {
      /* In C11, a conditional expression between a floating-point
	 type and an integer type should convert the integer type to
	 the evaluation format of the floating-point type, with
	 possible excess precision.  */
      درخت eptype1 = type1;
      درخت eptype2 = type2;
      اگر (flag_isoc11)
	{
	  درخت eptype;
	  اگر (ANY_INTEGRAL_TYPE_P (type1)
	      && (eptype = excess_precision_type (type2)) != NULL_درخت)
	    {
	      eptype2 = eptype;
	      اگر (!semantic_نتیجہ_type)
		semantic_نتیجہ_type = c_common_type (type1, type2);
	    }
	  ورنہ اگر (ANY_INTEGRAL_TYPE_P (type2)
		   && (eptype = excess_precision_type (type1)) != NULL_درخت)
	    {
	      eptype1 = eptype;
	      اگر (!semantic_نتیجہ_type)
		semantic_نتیجہ_type = c_common_type (type1, type2);
	    }
	}
      نتیجہ_type = c_common_type (eptype1, eptype2);
      اگر (نتیجہ_type == error_mark_گرہ)
	واپس error_mark_گرہ;
      do_warn_double_promotion (نتیجہ_type, type1, type2,
				"implicit conversion from %qT to %qT to "
				"match other result of conditional",
				colon_loc);

      /* If -Wsign-compare, warn here if type1 and type2 have
	 different signedness.  We'll promote the signed to unsigned
	 and later code won't know it used to be different.
	 Do this check on the original types, so that explicit casts
	 will be considered, but default promotions won't.  */
      اگر (c_inhibit_evaluation_warnings == 0)
	{
	  صحیح unsigned_op1 = TYPE_UNSIGNED (درخت_TYPE (orig_op1));
	  صحیح unsigned_op2 = TYPE_UNSIGNED (درخت_TYPE (orig_op2));

	  اگر (unsigned_op1 ^ unsigned_op2)
	    {
	      /* Do not warn if the result type is signed, since the
		 signed type will only be chosen if it can represent
		 all the values of the unsigned type.  */
	      اگر (!TYPE_UNSIGNED (نتیجہ_type))
		/* OK */;
	      ورنہ
		{
		  منطقی op1_maybe_const = سچ;
		  منطقی op2_maybe_const = سچ;

		  /* Do not warn if the signed quantity is an
		     unsuffixed integer literal (or some static
		     constant expression involving such literals) and
		     it is non-negative.  This warning requires the
		     operands to be folded for best results, so do
		     that folding in this case even without
		     warn_sign_compare to avoid warning options
		     possibly affecting code generation.  */
		  c_inhibit_evaluation_warnings
		    += (ifexp == truthvalue_false_گرہ);
		  op1 = c_fully_fold (op1, require_constant_قدر,
				      &op1_maybe_const);
		  c_inhibit_evaluation_warnings
		    -= (ifexp == truthvalue_false_گرہ);

		  c_inhibit_evaluation_warnings
		    += (ifexp == truthvalue_true_گرہ);
		  op2 = c_fully_fold (op2, require_constant_قدر,
				      &op2_maybe_const);
		  c_inhibit_evaluation_warnings
		    -= (ifexp == truthvalue_true_گرہ);

		  اگر (warn_sign_compare)
		    {
		      اگر ((unsigned_op2
			   && درخت_اظہاریہ_nonnegative_p (op1))
			  || (unsigned_op1
			      && درخت_اظہاریہ_nonnegative_p (op2)))
			/* OK */;
		      ورنہ اگر (unsigned_op2)
			warning_at (op1_loc, OPT_Wsign_compare,
				    "operand of %<?:%> changes signedness from "
				    "%qT to %qT due to unsignedness of other "
				    "operand", درخت_TYPE (orig_op1),
				    درخت_TYPE (orig_op2));
		      ورنہ
			warning_at (op2_loc, OPT_Wsign_compare,
				    "operand of %<?:%> changes signedness from "
				    "%qT to %qT due to unsignedness of other "
				    "operand", درخت_TYPE (orig_op2),
				    درخت_TYPE (orig_op1));
		    }
		  اگر (!op1_maybe_const || درخت_رمز (op1) != INTEGER_CST)
		    op1 = c_wrap_maybe_const (op1, !op1_maybe_const);
		  اگر (!op2_maybe_const || درخت_رمز (op2) != INTEGER_CST)
		    op2 = c_wrap_maybe_const (op2, !op2_maybe_const);
		}
	    }
	}
    }
  ورنہ اگر (code1 == VOID_TYPE || code2 == VOID_TYPE)
    {
      اگر (code1 != VOID_TYPE || code2 != VOID_TYPE)
	pedwarn (colon_loc, OPT_Wpedantic,
		 "ISO C forbids conditional expr with only one void side");
      نتیجہ_type = void_type_گرہ;
    }
  ورنہ اگر (code1 == اشارہ_گر_TYPE && code2 == اشارہ_گر_TYPE)
    {
      addr_space_t as1 = TYPE_ADDR_SPACE (درخت_TYPE (type1));
      addr_space_t as2 = TYPE_ADDR_SPACE (درخت_TYPE (type2));
      addr_space_t as_common;

      اگر (comp_ہدف_types (colon_loc, type1, type2))
	{
	  ifexp = save_اظہاریہ (ifexp);
	  نتیجہ_type = common_اشارہ_گر_type (type1, type2, ifexp);
	}
      ورنہ اگر (null_اشارہ_گر_constant_p (orig_op1))
	نتیجہ_type = type2;
      ورنہ اگر (null_اشارہ_گر_constant_p (orig_op2))
	نتیجہ_type = type1;
      ورنہ اگر (!addr_space_superset (as1, as2, &as_common))
	{
	  error_at (colon_loc, "pointers to disjoint address spaces "
		    "used in conditional expression");
	  واپس error_mark_گرہ;
	}
      ورنہ اگر ((VOID_TYPE_P (درخت_TYPE (type1))
		&& !TYPE_ATOMIC (درخت_TYPE (type1)))
	       || (VOID_TYPE_P (درخت_TYPE (type2))
		   && !TYPE_ATOMIC (درخت_TYPE (type2))))
	{
	  درخت t1 = درخت_TYPE (type1);
	  درخت t2 = درخت_TYPE (type2);
	  اگر (!(VOID_TYPE_P (t1)
		&& !TYPE_ATOMIC (t1)))
	   {
	     /* roles are swapped */
	     t1 = t2;
	     t2 = درخت_TYPE (type1);
	   }
	  درخت t2_stripped = strip_array_types (t2);
	  اگر ((درخت_رمز (t2) == ARRAY_TYPE)
	      && (TYPE_QUALS (t2_stripped) & ~TYPE_QUALS (t1)))
	    {
	      اگر (!flag_isoc23)
		warning_at (colon_loc, OPT_Wdiscarded_array_qualifiers,
			    "pointer to array loses qualifier "
			    "in conditional expression");
	      ورنہ اگر (warn_c11_c23_compat > 0)
		warning_at (colon_loc, OPT_Wc11_c23_compat,
			    "pointer to array loses qualifier "
			    "in conditional expression in ISO C before C23");
	    }
	  اگر (درخت_رمز (t2) == FUNCTION_TYPE)
	    pedwarn (colon_loc, OPT_Wpedantic,
		     "ISO C forbids conditional expr between "
		     "%<void *%> and function pointer");
	  /* for array, use qualifiers of element type */
	  اگر (flag_isoc23)
	    t2 = t2_stripped;
	  نتیجہ_type = c_build_اشارہ_گر_type (qualify_type (t1, t2));
	}
      /* Objective-C pointer comparisons are a bit more lenient.  */
      ورنہ اگر (objc_have_common_type (type1, type2, -3, NULL_درخت))
	نتیجہ_type = objc_common_type (type1, type2);
      ورنہ
	{
	  صحیح qual = ENCODE_QUAL_ADDR_SPACE (as_common);
	  شمار diagnostics::قسم قسم = diagnostics::قسم::permerror;
	  اگر (!flag_isoc99)
	    /* This downgrade to a warning ensures that -std=gnu89
	       -pedantic-errors does not flag these mismatches between
	       builtins as errors (as diagnostics::kind::permerror would)
	       ISO C99 and later do not have implicit function declarations,
	       so the mismatch cannot occur naturally there.  */
	    قسم = (bltin1 && bltin2
		    ? diagnostics::قسم::warning
		    : diagnostics::قسم::pedwarn);
	  اگر (emit_diagnostic (قسم, colon_loc, OPT_Wincompatible_اشارہ_گر_types,
			       "pointer type mismatch "
			       "in conditional expression"))
	    {
	      inform (op1_loc, "first expression has type %qT", type1);
	      inform (op2_loc, "second expression has type %qT", type2);
	    }
	  نتیجہ_type = c_build_اشارہ_گر_type
			  (c_build_qualified_type (void_type_گرہ, qual));
	}
    }
  ورنہ اگر (code1 == اشارہ_گر_TYPE
	   && (code2 == INTEGER_TYPE || code2 == BITINT_TYPE))
    {
      اگر (!null_اشارہ_گر_constant_p (orig_op2))
	permerror_opt (colon_loc, OPT_Wint_conversion,
		       "pointer/integer type mismatch "
		       "in conditional expression");
      ورنہ
	{
	  op2 = null_اشارہ_گر_گرہ;
	}
      نتیجہ_type = type1;
    }
  ورنہ اگر (code2 == اشارہ_گر_TYPE
	   && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
    {
      اگر (!null_اشارہ_گر_constant_p (orig_op1))
	permerror_opt (colon_loc, OPT_Wint_conversion,
		       "pointer/integer type mismatch "
		       "in conditional expression");
      ورنہ
	{
	  op1 = null_اشارہ_گر_گرہ;
	}
      نتیجہ_type = type2;
    }
  /* 6.5.15: "if one is a null pointer constant (other than a pointer) or has
     type nullptr_t and the other is a pointer, the result type is the pointer
     type."  */
  ورنہ اگر (code1 == NULLPTR_TYPE && code2 == اشارہ_گر_TYPE)
    نتیجہ_type = type2;
  ورنہ اگر (code1 == اشارہ_گر_TYPE && code2 == NULLPTR_TYPE)
    نتیجہ_type = type1;
  ورنہ اگر (ریکارڈ_OR_UNION_TYPE_P (type1) && ریکارڈ_OR_UNION_TYPE_P (type2)
	   && comptypes (TYPE_MAIN_VARIANT (type1),
			 TYPE_MAIN_VARIANT (type2)))
    نتیجہ_type = مرکب_type (TYPE_MAIN_VARIANT (type1),
				  TYPE_MAIN_VARIANT (type2));

  اگر (!نتیجہ_type)
    {
      اگر (flag_cond_mismatch)
	نتیجہ_type = void_type_گرہ;
      ورنہ
	{
	  error_at (colon_loc, "type mismatch in conditional expression");
	  واپس error_mark_گرہ;
	}
    }

  /* Merge const and volatile flags of the incoming types.  */
  نتیجہ_type
    = build_type_variant (نتیجہ_type,
			  TYPE_READONLY (type1) || TYPE_READONLY (type2),
			  TYPE_VOLATILE (type1) || TYPE_VOLATILE (type2));

  op1 = ep_convert_and_check (colon_loc, نتیجہ_type, op1,
			      semantic_نتیجہ_type);
  op2 = ep_convert_and_check (colon_loc, نتیجہ_type, op2,
			      semantic_نتیجہ_type);

  اگر (ifexp_bcp && ifexp == truthvalue_true_گرہ)
    {
      op2_int_operands = سچ;
      op1 = c_fully_fold (op1, require_constant_قدر, تہی);
    }
  اگر (ifexp_bcp && ifexp == truthvalue_false_گرہ)
    {
      op1_int_operands = سچ;
      op2 = c_fully_fold (op2, require_constant_قدر, تہی);
    }
  int_const = int_operands = (ifexp_int_operands
			      && op1_int_operands
			      && op2_int_operands);
  اگر (int_operands)
    {
      int_const = ((ifexp == truthvalue_true_گرہ
		    && درخت_رمز (orig_op1) == INTEGER_CST
		    && !درخت_حد_سے_تجاوز (orig_op1))
		   || (ifexp == truthvalue_false_گرہ
		       && درخت_رمز (orig_op2) == INTEGER_CST
		       && !درخت_حد_سے_تجاوز (orig_op2)));
    }

  /* Need to convert condition operand into a vector mask.  */
  اگر (سمتیہ_TYPE_P (درخت_TYPE (ifexp)))
    {
      درخت vectype = درخت_TYPE (ifexp);
      درخت elem_type = درخت_TYPE (vectype);
      درخت zero = build_int_cst (elem_type, 0);
      درخت zero_vec = build_سمتیہ_from_val (vectype, zero);
      درخت cmp_type = truth_type_for (vectype);
      ifexp = build2 (NE_اظہاریہ, cmp_type, ifexp, zero_vec);
    }

  اگر (int_const || (ifexp_bcp && درخت_رمز (ifexp) == INTEGER_CST))
    ret = fold_build3_loc (colon_loc, COND_اظہاریہ, نتیجہ_type, ifexp, op1, op2);
  ورنہ
    {
      اگر (int_operands)
	{
	  /* Use c_fully_fold here, since C_MAYBE_CONST_EXPR might be
	     nested inside of the expression.  */
	  op1 = c_fully_fold (op1, جھوٹ, تہی);
	  op2 = c_fully_fold (op2, جھوٹ, تہی);
	}
      ret = build3 (COND_اظہاریہ, نتیجہ_type, ifexp, op1, op2);
      اگر (int_operands)
	ret = note_integer_operands (ret);
    }
  اگر (semantic_نتیجہ_type)
    ret = build1 (EXCESS_PRECISION_اظہاریہ, semantic_نتیجہ_type, ret);

  protected_سیٹ_اظہاریہ_location (ret, colon_loc);

  /* If the OP1 and OP2 are the same and don't have side-effects,
     warn here, because the COND_EXPR will be turned into OP1.  */
  اگر (warn_duplicated_branches
      && درخت_رمز (ret) == COND_اظہاریہ
      && (op1 == op2 || عملیہ_equal_p (op1, op2, OEP_پتہ_کا_SAME_میدان)))
    warning_at (اظہاریہ_LOCATION (ret), OPT_Wduplicated_branches,
		"this condition has identical branches");

  واپس ret;
}

/* EXPR is an expression, location LOC, whose result is discarded.
   Warn if it is a call to a nodiscard function (or a COMPOUND_EXPR
   whose right-hand operand is such a call, possibly recursively).  */

ساکن خالی
maybe_warn_nodiscard (location_t loc, درخت اظہاریہ)
{
  اگر (VOID_TYPE_P (درخت_TYPE (اظہاریہ)))
    واپس;
  جب (درخت_رمز (اظہاریہ) == COMPOUND_اظہاریہ)
    {
      اظہاریہ = درخت_عملیہ (اظہاریہ, 1);
      اگر (اظہاریہ_HAS_LOCATION (اظہاریہ))
	loc = اظہاریہ_LOCATION (اظہاریہ);
    }
  اگر (درخت_رمز (اظہاریہ) != CALL_اظہاریہ)
    واپس;
  درخت fn = CALL_اظہاریہ_FN (اظہاریہ);
  اگر (!fn)
    واپس;
  درخت attr;
  اگر (درخت_رمز (fn) == ADDR_اظہاریہ
      && درخت_رمز (درخت_عملیہ (fn, 0)) == FUNCTION_DECL
      && (attr = lookup_attribute ("nodiscard",
				   DECL_اوصاف (درخت_عملیہ (fn, 0)))))
    {
      fn = درخت_عملیہ (fn, 0);
      درخت دلائل = درخت_قدر (attr);
      اگر (دلائل)
	دلائل = درخت_قدر (دلائل);
      auto_diagnostic_گروہ d;
      auto_urlify_اوصاف sentinel;
      صحیح warned;
      اگر (دلائل)
	warned = warning_at (loc, OPT_Wunused_نتیجہ,
			     "ignoring return value of %qD, declared with "
			     "attribute %<nodiscard%>: %E", fn, دلائل);
      ورنہ
	warned = warning_at (loc, OPT_Wunused_نتیجہ,
			     "ignoring return value of %qD, declared with "
			     "attribute %<nodiscard%>", fn);
      اگر (warned)
	inform (DECL_ماخذ_LOCATION (fn), "declared here");
    }
  ورنہ
    {
      درخت rettype = درخت_TYPE (درخت_TYPE (درخت_TYPE (fn)));
      attr = lookup_attribute ("nodiscard", TYPE_اوصاف (rettype));
      اگر (!attr)
	واپس;
      درخت دلائل = درخت_قدر (attr);
      اگر (دلائل)
	دلائل = درخت_قدر (دلائل);
      auto_diagnostic_گروہ d;
      auto_urlify_اوصاف sentinel;
      صحیح warned;
      اگر (دلائل)
	warned = warning_at (loc, OPT_Wunused_نتیجہ,
			     "ignoring return value of type %qT, declared "
			     "with attribute %<nodiscard%>: %E",
			     rettype, دلائل);
      ورنہ
	warned = warning_at (loc, OPT_Wunused_نتیجہ,
			     "ignoring return value of type %qT, declared "
			     "with attribute %<nodiscard%>", rettype);
      اگر (warned)
	{
	  اگر (درخت_رمز (fn) == ADDR_اظہاریہ)
	    {
	      fn = درخت_عملیہ (fn, 0);
	      اگر (درخت_رمز (fn) == FUNCTION_DECL)
		inform (DECL_ماخذ_LOCATION (fn),
			"in call to %qD, declared here", fn);
	    }
	}
    }
}

/* Return a compound expression that performs two expressions and
   returns the value of the second of them.

   LOC is the location of the COMPOUND_EXPR.  */

درخت
build_compound_اظہاریہ (location_t loc, درخت expr1, درخت expr2)
{
  منطقی expr1_int_operands, expr2_int_operands;
  درخت eptype = NULL_درخت;
  درخت ret;

  expr1_int_operands = اظہاریہ_INT_CONST_OPERANDS (expr1);
  اگر (expr1_int_operands)
    expr1 = remove_c_maybe_const_اظہاریہ (expr1);
  expr2_int_operands = اظہاریہ_INT_CONST_OPERANDS (expr2);
  اگر (expr2_int_operands)
    expr2 = remove_c_maybe_const_اظہاریہ (expr2);

  اگر (درخت_رمز (expr1) == EXCESS_PRECISION_اظہاریہ)
    expr1 = درخت_عملیہ (expr1, 0);
  اگر (درخت_رمز (expr2) == EXCESS_PRECISION_اظہاریہ)
    {
      eptype = درخت_TYPE (expr2);
      expr2 = درخت_عملیہ (expr2, 0);
    }

  اگر (!درخت_SIDE_EFFECTS (expr1))
    {
      /* The left-hand operand of a comma expression is like an expression
	 statement: with -Wunused, we should warn if it doesn't have
	 any side-effects, unless it was explicitly cast to (void).  */
      اگر (warn_غیر_مستعمل_قدر)
	{
	  اگر (VOID_TYPE_P (درخت_TYPE (expr1))
	      && CONVERT_اظہاریہ_P (expr1))
	    ; /* (void) a, b */
	  ورنہ اگر (VOID_TYPE_P (درخت_TYPE (expr1))
		   && درخت_رمز (expr1) == COMPOUND_اظہاریہ
		   && CONVERT_اظہاریہ_P (درخت_عملیہ (expr1, 1)))
	    ; /* (void) a, (void) b, c */
	  ورنہ
	    warning_at (loc, OPT_Wunused_قدر,
			"left-hand operand of comma expression has no effect");
	}
    }
  ورنہ اگر (درخت_رمز (expr1) == COMPOUND_اظہاریہ
	   && warn_غیر_مستعمل_قدر)
    {
      درخت r = expr1;
      location_t cloc = loc;
      جب (درخت_رمز (r) == COMPOUND_اظہاریہ)
        {
	  اگر (اظہاریہ_HAS_LOCATION (r))
	    cloc = اظہاریہ_LOCATION (r);
	  r = درخت_عملیہ (r, 1);
	}
      اگر (!درخت_SIDE_EFFECTS (r)
	  && !VOID_TYPE_P (درخت_TYPE (r))
	  && !CONVERT_اظہاریہ_P (r))
	warning_at (cloc, OPT_Wunused_قدر,
	            "right-hand operand of comma expression has no effect");
    }

  /* With -Wunused, we should also warn if the left-hand operand does have
     side-effects, but computes a value which is not used.  For example, in
     `foo() + bar(), baz()' the result of the `+' operator is not used,
     so we should issue a warning.  */
  ورنہ اگر (warn_غیر_مستعمل_قدر)
    warn_if_غیر_مستعمل_قدر (expr1, loc);

  maybe_warn_nodiscard (loc, expr1);

  اگر (expr2 == error_mark_گرہ)
    واپس error_mark_گرہ;

  ret = build2 (COMPOUND_اظہاریہ, درخت_TYPE (expr2), expr1, expr2);

  اگر (flag_isoc99
      && expr1_int_operands
      && expr2_int_operands)
    ret = note_integer_operands (ret);

  اگر (eptype)
    ret = build1 (EXCESS_PRECISION_اظہاریہ, eptype, ret);

  protected_سیٹ_اظہاریہ_location (ret, loc);
  واپس ret;
}

/* Issue -Wcast-qual warnings when appropriate.  TYPE is the type to
   which we are casting.  OTYPE is the type of the expression being
   cast.  Both TYPE and OTYPE are pointer types.  LOC is the location
   of the cast.  -Wcast-qual appeared on the command line.  Named
   address space qualifiers are not handled here, because they result
   in different warnings.  */

ساکن خالی
handle_warn_cast_qual (location_t loc, درخت type, درخت otype)
{
  درخت اندر_type = type;
  درخت اندر_otype = otype;
  صحیح added = 0;
  صحیح discarded = 0;
  منطقی is_const;

  /* Check that the qualifiers on IN_TYPE are a superset of the
     qualifiers of IN_OTYPE.  The outermost level of POINTER_TYPE
     nodes is uninteresting and we stop as soon as we hit a
     non-POINTER_TYPE node on either type.  */
  کرو
    {
      اندر_otype = درخت_TYPE (اندر_otype);
      اندر_type = درخت_TYPE (اندر_type);

      /* GNU C allows cv-qualified function types.  'const' means the
	 function is very pure, 'volatile' means it can't return.  We
	 need to warn when such qualifiers are added, not when they're
	 taken away.  */
      اگر (درخت_رمز (اندر_otype) == FUNCTION_TYPE
	  && درخت_رمز (اندر_type) == FUNCTION_TYPE)
	added |= (TYPE_QUALS_NO_ADDR_SPACE (اندر_type)
		  & ~TYPE_QUALS_NO_ADDR_SPACE (اندر_otype));
      ورنہ
	discarded |= (TYPE_QUALS_NO_ADDR_SPACE (اندر_otype)
		      & ~TYPE_QUALS_NO_ADDR_SPACE (اندر_type));
    }
  جب (درخت_رمز (اندر_type) == اشارہ_گر_TYPE
	 && درخت_رمز (اندر_otype) == اشارہ_گر_TYPE);

  اگر (added)
    warning_at (loc, OPT_Wcast_qual,
		"cast adds %q#v qualifier to function type", added);

  اگر (discarded)
    /* There are qualifiers present in IN_OTYPE that are not present
       in IN_TYPE.  */
    warning_at (loc, OPT_Wcast_qual,
		"cast discards %qv qualifier from pointer target type",
		discarded);

  اگر (added || discarded)
    واپس;

  /* A cast from **T to const **T is unsafe, because it can cause a
     const value to be changed with no additional warning.  We only
     issue this warning if T is the same on both sides, and we only
     issue the warning if there are the same number of pointers on
     both sides, as otherwise the cast is clearly unsafe anyhow.  A
     cast is unsafe when a qualifier is added at one level and const
     is not present at all outer levels.

     To issue this warning, we check at each level whether the cast
     adds new qualifiers not already seen.  We don't need to special
     case function types, as they won't have the same
     TYPE_MAIN_VARIANT.  */

  اگر (TYPE_MAIN_VARIANT (اندر_type) != TYPE_MAIN_VARIANT (اندر_otype))
    واپس;
  اگر (درخت_رمز (درخت_TYPE (type)) != اشارہ_گر_TYPE)
    واپس;

  اندر_type = type;
  اندر_otype = otype;
  is_const = TYPE_READONLY (درخت_TYPE (اندر_type));
  کرو
    {
      اندر_type = درخت_TYPE (اندر_type);
      اندر_otype = درخت_TYPE (اندر_otype);
      اگر ((TYPE_QUALS (اندر_type) &~ TYPE_QUALS (اندر_otype)) != 0
	  && !is_const)
	{
	  warning_at (loc, OPT_Wcast_qual,
		      "to be safe all intermediate pointers in cast from "
                      "%qT to %qT must be %<const%> qualified",
		      otype, type);
	  توڑو;
	}
      اگر (is_const)
	is_const = TYPE_READONLY (اندر_type);
    }
  جب (درخت_رمز (اندر_type) == اشارہ_گر_TYPE);
}

/* Heuristic check if two parameter types can be considered ABI-equivalent.  */

ساکن منطقی
c_محفوظ_arg_type_equiv_p (درخت t1, درخت t2)
{
  اگر (error_عملیہ_p (t1) || error_عملیہ_p (t2))
    واپس سچ;

  t1 = TYPE_MAIN_VARIANT (t1);
  t2 = TYPE_MAIN_VARIANT (t2);

  اگر (درخت_رمز (t1) == اشارہ_گر_TYPE
      && درخت_رمز (t2) == اشارہ_گر_TYPE)
    واپس سچ;

  /* Only the precision of the parameter matters.  This check should
     make sure that the callee does not see undefined values in argument
     registers.  */
  اگر (INTEGRAL_TYPE_P (t1)
      && INTEGRAL_TYPE_P (t2)
      && TYPE_PRECISION (t1) == TYPE_PRECISION (t2))
    واپس سچ;

  واپس comptypes (t1, t2);
}

/* Check if a type cast between two function types can be considered safe.  */

ساکن منطقی
c_محفوظ_function_type_cast_p (درخت t1, درخت t2)
{
  اگر (درخت_TYPE (t1) == void_type_گرہ &&
      TYPE_ARG_TYPES (t1) == void_list_گرہ)
    واپس سچ;

  اگر (درخت_TYPE (t2) == void_type_گرہ &&
      TYPE_ARG_TYPES (t2) == void_list_گرہ)
    واپس سچ;

  اگر (!c_محفوظ_arg_type_equiv_p (درخت_TYPE (t1), درخت_TYPE (t2)))
    واپس جھوٹ;

  برائے (t1 = TYPE_ARG_TYPES (t1), t2 = TYPE_ARG_TYPES (t2);
       t1 && t2;
       t1 = درخت_CHAIN (t1), t2 = درخت_CHAIN (t2))
    اگر (!c_محفوظ_arg_type_equiv_p (درخت_قدر (t1), درخت_قدر (t2)))
      واپس جھوٹ;

  واپس سچ;
}

/* Build an expression representing a cast to type TYPE of expression EXPR.
   LOC is the location of the cast-- typically the open paren of the cast.  */

درخت
build_c_cast (location_t loc, درخت type, درخت اظہاریہ)
{
  درخت قدر;

  منطقی int_operands = اظہاریہ_INT_CONST_OPERANDS (اظہاریہ);

  اگر (درخت_رمز (اظہاریہ) == EXCESS_PRECISION_اظہاریہ)
    اظہاریہ = درخت_عملیہ (اظہاریہ, 0);

  قدر = اظہاریہ;
  اگر (int_operands)
    قدر = remove_c_maybe_const_اظہاریہ (قدر);

  اگر (type == error_mark_گرہ || اظہاریہ == error_mark_گرہ)
    واپس error_mark_گرہ;

  /* The ObjC front-end uses TYPE_MAIN_VARIANT to tie together types differing
     only in <protocol> qualifications.  But when constructing cast expressions,
     the protocols do matter and must be kept around.  */
  اگر (objc_is_object_ptr (type) && objc_is_object_ptr (درخت_TYPE (اظہاریہ)))
    واپس build1 (NOP_اظہاریہ, type, اظہاریہ);

  type = TYPE_MAIN_VARIANT (type);

  اگر (درخت_رمز (type) == ARRAY_TYPE)
    {
      error_at (loc, "cast specifies array type");
      واپس error_mark_گرہ;
    }

  اگر (درخت_رمز (type) == FUNCTION_TYPE)
    {
      error_at (loc, "cast specifies function type");
      واپس error_mark_گرہ;
    }

  اگر (!VOID_TYPE_P (type))
    {
      قدر = require_complete_type (loc, قدر);
      اگر (قدر == error_mark_گرہ)
	واپس error_mark_گرہ;
    }

  اگر (type == TYPE_MAIN_VARIANT (درخت_TYPE (قدر)))
    {
      اگر (ریکارڈ_OR_UNION_TYPE_P (type)
	  && pedwarn (loc, OPT_Wpedantic,
		      "ISO C forbids casting nonscalar to the same type"))
	      ;
      ورنہ اگر (warn_useless_cast && c_inhibit_evaluation_warnings == 0)
	warning_at (loc, OPT_Wuseless_cast,
		    "useless cast to type %qT", type);

      /* Convert to remove any qualifiers from VALUE's type.  */
      قدر = convert (type, قدر);
    }
  ورنہ اگر (درخت_رمز (type) == UNION_TYPE)
    {
      درخت میدان_2;

      برائے (میدان_2 = TYPE_FIELDS (type); میدان_2; میدان_2 = DECL_CHAIN (میدان_2))
	اگر (درخت_TYPE (میدان_2) != error_mark_گرہ
	    && comptypes (TYPE_MAIN_VARIANT (درخت_TYPE (میدان_2)),
			  TYPE_MAIN_VARIANT (درخت_TYPE (قدر))))
	  توڑو;

      اگر (میدان_2)
	{
	  درخت t;
	  منطقی maybe_const = سچ;

	  pedwarn (loc, OPT_Wpedantic, "ISO C forbids casts to union type");
	  t = c_fully_fold (قدر, جھوٹ, &maybe_const);
	  t = build_constructor_single (type, میدان_2, t);
	  اگر (!maybe_const)
	    t = c_wrap_maybe_const (t, سچ);
	  t = digest_init (loc, میدان_2, type, t,
			   NULL_درخت, جھوٹ, جھوٹ, جھوٹ, سچ, جھوٹ, جھوٹ);
	  درخت_CONSTANT (t) = درخت_CONSTANT (قدر);
	  واپس t;
	}
      error_at (loc, "cast to union type from type not present in union");
      واپس error_mark_گرہ;
    }
  ورنہ
    {
      درخت otype, ovalue;

      اگر (type == void_type_گرہ)
	{
	  درخت t = build1 (CONVERT_اظہاریہ, type, قدر);
	  سیٹ_اظہاریہ_LOCATION (t, loc);
	  واپس t;
	}

      otype = درخت_TYPE (قدر);

      /* Optionally warn about potentially worrisome casts.  */
      اگر (warn_cast_qual
	  && درخت_رمز (type) == اشارہ_گر_TYPE
	  && درخت_رمز (otype) == اشارہ_گر_TYPE)
	handle_warn_cast_qual (loc, type, otype);

      /* Warn about conversions between pointers to disjoint
	 address spaces.  */
      اگر (درخت_رمز (type) == اشارہ_گر_TYPE
	  && درخت_رمز (otype) == اشارہ_گر_TYPE
	  && !null_اشارہ_گر_constant_p (قدر))
	{
	  addr_space_t as_مقصد = TYPE_ADDR_SPACE (درخت_TYPE (type));
	  addr_space_t as_from = TYPE_ADDR_SPACE (درخت_TYPE (otype));
	  addr_space_t as_common;

	  اگر (!addr_space_superset (as_مقصد, as_from, &as_common))
	    {
	      اگر (ADDR_SPACE_GENERIC_P (as_from))
		warning_at (loc, 0, "cast to %qs address space pointer "
			    "from disjoint generic address space pointer",
			    c_addr_space_name (as_مقصد));

	      ورنہ اگر (ADDR_SPACE_GENERIC_P (as_مقصد))
		warning_at (loc, 0, "cast to generic address space pointer "
			    "from disjoint %qs address space pointer",
			    c_addr_space_name (as_from));

	      ورنہ
		warning_at (loc, 0, "cast to %qs address space pointer "
			    "from disjoint %qs address space pointer",
			    c_addr_space_name (as_مقصد),
			    c_addr_space_name (as_from));
	    }

	  /* Warn of new allocations that are not big enough for the target
	     type.  */
	  اگر (warn_alloc_سائز && درخت_رمز (قدر) == CALL_اظہاریہ)
	    اگر (درخت fndecl = get_callee_fndecl (قدر))
	      اگر (DECL_IS_MALLOC (fndecl))
		{
		  درخت attrs = TYPE_اوصاف (درخت_TYPE (fndecl));
		  درخت alloc_سائز = lookup_attribute ("alloc_size", attrs);
		  اگر (alloc_سائز)
		    warn_for_alloc_سائز (loc, درخت_TYPE (type), قدر,
					 alloc_سائز);
		}
	}

      /* Warn about possible alignment problems.  */
      اگر ((STRICT_ALIGNMENT || warn_cast_align == 2)
	  && درخت_رمز (type) == اشارہ_گر_TYPE
	  && درخت_رمز (otype) == اشارہ_گر_TYPE
	  && درخت_رمز (درخت_TYPE (otype)) != VOID_TYPE
	  && درخت_رمز (درخت_TYPE (otype)) != FUNCTION_TYPE
	  /* Don't warn about opaque types, where the actual alignment
	     restriction is unknown.  */
	  && !(ریکارڈ_OR_UNION_TYPE_P (درخت_TYPE (otype))
	       && TYPE_منوال (درخت_TYPE (otype)) == VOIDmode)
	  && min_align_کا_type (درخت_TYPE (type))
	     > min_align_کا_type (درخت_TYPE (otype)))
	warning_at (loc, OPT_Wcast_align,
		    "cast increases required alignment of target type");

      اگر ((درخت_رمز (type) == INTEGER_TYPE
	   || درخت_رمز (type) == BITINT_TYPE)
	  && درخت_رمز (otype) == اشارہ_گر_TYPE
	  && TYPE_PRECISION (type) != TYPE_PRECISION (otype))
      /* Unlike conversion of integers to pointers, where the
         warning is disabled for converting constants because
         of cases such as SIG_*, warn about converting constant
         pointers to integers. In some cases it may cause unwanted
         sign extension, and a warning is appropriate.  */
	warning_at (loc, OPT_Wpointer_مقصد_int_cast,
		    "cast from pointer to integer of different size");

      اگر ((درخت_رمز (قدر) == CALL_اظہاریہ
	   && !is_access_with_سائز_p (قدر))
	  && درخت_رمز (type) != درخت_رمز (otype))
	warning_at (loc, OPT_Wbad_function_cast,
		    "cast from function call of type %qT "
		    "to non-matching type %qT", otype, type);

      اگر (درخت_رمز (type) == اشارہ_گر_TYPE
	  && (درخت_رمز (otype) == INTEGER_TYPE
	      || درخت_رمز (otype) == BITINT_TYPE)
	  && TYPE_PRECISION (type) != TYPE_PRECISION (otype)
	  /* Don't warn about converting any constant.  */
	  && !درخت_CONSTANT (قدر))
	warning_at (loc,
		    OPT_Wint_مقصد_اشارہ_گر_cast, "cast to pointer from integer "
		    "of different size");

      اگر (warn_strict_aliasing <= 2)
        strict_aliasing_warning (اظہاریہ_LOCATION (قدر), type, اظہاریہ);

      /* If pedantic, warn for conversions between function and object
	 pointer types, except for converting a null pointer constant
	 to function pointer type.  */
      اگر (pedantic
	  && درخت_رمز (type) == اشارہ_گر_TYPE
	  && درخت_رمز (otype) == اشارہ_گر_TYPE
	  && درخت_رمز (درخت_TYPE (otype)) == FUNCTION_TYPE
	  && درخت_رمز (درخت_TYPE (type)) != FUNCTION_TYPE)
	pedwarn (loc, OPT_Wpedantic, "ISO C forbids "
		 "conversion of function pointer to object pointer type");

      اگر (pedantic
	  && درخت_رمز (type) == اشارہ_گر_TYPE
	  && درخت_رمز (otype) == اشارہ_گر_TYPE
	  && درخت_رمز (درخت_TYPE (type)) == FUNCTION_TYPE
	  && درخت_رمز (درخت_TYPE (otype)) != FUNCTION_TYPE
	  && !null_اشارہ_گر_constant_p (قدر))
	pedwarn (loc, OPT_Wpedantic, "ISO C forbids "
		 "conversion of object pointer to function pointer type");

      اگر (درخت_رمز (type) == اشارہ_گر_TYPE
	  && درخت_رمز (otype) == اشارہ_گر_TYPE
	  && درخت_رمز (درخت_TYPE (type)) == FUNCTION_TYPE
	  && درخت_رمز (درخت_TYPE (otype)) == FUNCTION_TYPE
	  && !c_محفوظ_function_type_cast_p (درخت_TYPE (type),
					   درخت_TYPE (otype)))
	warning_at (loc, OPT_Wcast_function_type,
		    "cast between incompatible function types"
		    " from %qT to %qT", otype, type);

      ovalue = قدر;
      /* If converting to boolean a value with integer operands that
	 is not itself represented as an INTEGER_CST, the call below
	 to note_integer_operands may insert a C_MAYBE_CONST_EXPR, but
	 build_binary_op as called by c_common_truthvalue_conversion
	 may also insert a C_MAYBE_CONST_EXPR to indicate that a
	 subexpression has been fully folded.  To avoid nested
	 C_MAYBE_CONST_EXPR, ensure that
	 c_objc_common_truthvalue_conversion receives an argument
	 properly marked as having integer operands in that case.  */
      اگر (int_operands
	  && درخت_رمز (قدر) != INTEGER_CST
	  && (درخت_رمز (type) == BOOLEAN_TYPE
	      || (درخت_رمز (type) == ENUMERAL_TYPE
		  && ENUM_UNDERLYING_TYPE (type) != NULL_درخت
		  && درخت_رمز (ENUM_UNDERLYING_TYPE (type)) == BOOLEAN_TYPE)))
	قدر = note_integer_operands (قدر);
      قدر = convert (type, قدر);

      /* Ignore any integer overflow caused by the cast.  */
      اگر (درخت_رمز (قدر) == INTEGER_CST && !FLOAT_TYPE_P (otype))
	{
	  اگر (درخت_حد_سے_تجاوز_P (ovalue))
	    {
	      اگر (!درخت_حد_سے_تجاوز (قدر))
		{
		  /* Avoid clobbering a shared constant.  */
		  قدر = copy_گرہ (قدر);
		  درخت_حد_سے_تجاوز (قدر) = درخت_حد_سے_تجاوز (ovalue);
		}
	    }
	  ورنہ اگر (درخت_حد_سے_تجاوز (قدر))
	    /* Reset VALUE's overflow flags, ensuring constant sharing.  */
	    قدر = wide_int_مقصد_درخت (درخت_TYPE (قدر), wi::مقصد_wide (قدر));
	}
    }

  /* Don't let a cast be an lvalue.  */
  اگر (lvalue_p (قدر)
      /* Also, don't let a cast be a bit-field of a bit-precise integer type,
	 otherwise it could be incorrectly subject of integer promotions.  */
      || (درخت_رمز (قدر) == COMPONENT_REF
	  && DECL_C_ثنائی_ہندسہ_میدان (درخت_عملیہ (قدر, 1))
	  && BITINT_TYPE_P (DECL_ثنائی_ہندسہ_میدان_TYPE (درخت_عملیہ (قدر, 1)))))
    قدر = non_lvalue_loc (loc, قدر);

  /* Don't allow the results of casting to floating-point or complex
     types be confused with actual constants, or casts involving
     integer and pointer types other than direct integer-to-integer
     and integer-to-pointer be confused with integer constant
     expressions and null pointer constants.  */
  اگر (درخت_رمز (قدر) == REAL_CST
      || درخت_رمز (قدر) == COMPLEX_CST
      || (درخت_رمز (قدر) == INTEGER_CST
	  && !((درخت_رمز (اظہاریہ) == INTEGER_CST
		&& INTEGRAL_TYPE_P (درخت_TYPE (اظہاریہ)))
	       || درخت_رمز (اظہاریہ) == REAL_CST
	       || درخت_رمز (اظہاریہ) == COMPLEX_CST)))
      قدر = build1 (NOP_اظہاریہ, type, قدر);

  /* If the expression has integer operands and so can occur in an
     unevaluated part of an integer constant expression, ensure the
     return value reflects this.  */
  اگر (int_operands
      && INTEGRAL_TYPE_P (type)
      && قدر != error_mark_گرہ
      && !اظہاریہ_INT_CONST_OPERANDS (قدر))
    قدر = note_integer_operands (قدر);

  protected_سیٹ_اظہاریہ_location (قدر, loc);
  واپس قدر;
}

/* Interpret a cast of expression EXPR to type TYPE.  LOC is the
   location of the open paren of the cast, or the position of the cast
   expr.  */
درخت
c_cast_اظہاریہ (location_t loc, ساخت c_type_name *type_name, درخت اظہاریہ)
{
  درخت type;
  درخت type_اظہاریہ = NULL_درخت;
  منطقی type_اظہاریہ_const = سچ;
  درخت ret;
  صحیح saved_wsp = warn_strict_prototypes;

  /* This avoids warnings about unprototyped casts on
     integers.  E.g. "#define SIG_DFL (void(*)())0".  */
  اگر (درخت_رمز (اظہاریہ) == INTEGER_CST)
    warn_strict_prototypes = 0;
  type = groktypename (type_name, &type_اظہاریہ, &type_اظہاریہ_const);
  warn_strict_prototypes = saved_wsp;

  اگر (درخت_رمز (اظہاریہ) == ADDR_اظہاریہ && !VOID_TYPE_P (type)
      && reject_gcc_builtin (اظہاریہ))
    واپس error_mark_گرہ;

  ret = build_c_cast (loc, type, اظہاریہ);
  اگر (ret == error_mark_گرہ)
    واپس error_mark_گرہ;

  اگر (type_اظہاریہ)
    {
      منطقی inner_اظہاریہ_const = سچ;
      ret = c_fully_fold (ret, require_constant_قدر, &inner_اظہاریہ_const);
      ret = build2 (C_MAYBE_CONST_اظہاریہ, درخت_TYPE (ret), type_اظہاریہ, ret);
      C_MAYBE_CONST_اظہاریہ_NON_CONST (ret) = !(type_اظہاریہ_const
					     && inner_اظہاریہ_const);
      سیٹ_اظہاریہ_LOCATION (ret, loc);
    }

  اگر (!اظہاریہ_HAS_LOCATION (ret))
    protected_سیٹ_اظہاریہ_location (ret, loc);

  /* C++ does not permits types to be defined in a cast, but it
     allows references to incomplete types.  */
  اگر (warn_cxx_compat && type_name->specs->typespec_قسم == ctsk_tagdef)
    warning_at (loc, OPT_Wc___compat,
		"defining a type in a cast is invalid in C++");

  واپس ret;
}

/* Build an assignment expression of lvalue LHS from value RHS.
   If LHS_ORIGTYPE is not NULL, it is the original type of LHS, which
   may differ from TREE_TYPE (LHS) for an enum bitfield.
   MODIFYCODE is the code for a binary operator that we use
   to combine the old value of LHS with RHS to get the new value.
   Or else MODIFYCODE is NOP_EXPR meaning do a simple assignment.
   If RHS_ORIGTYPE is not NULL_TREE, it is the original type of RHS,
   which may differ from TREE_TYPE (RHS) for an enum value.

   LOCATION is the location of the MODIFYCODE operator.
   RHS_LOC is the location of the RHS.  */

درخت
build_modify_اظہاریہ (location_t location, درخت lhs, درخت lhs_origtype,
		   شمار درخت_رمز_2 modifycode,
		   location_t rhs_loc, درخت rhs, درخت rhs_origtype)
{
  درخت نتیجہ;
  درخت newrhs;
  درخت rhseval = NULL_درخت;
  درخت lhstype = درخت_TYPE (lhs);
  درخت olhstype = lhstype;
  منطقی npc;
  منطقی is_atomic_op;

  /* Types that aren't fully specified cannot be used in assignments.  */
  lhs = require_complete_type (location, lhs);
  rhs = require_complete_type (location, rhs);

  /* Avoid duplicate error messages from operands that had errors.  */
  اگر (درخت_رمز (lhs) == ERROR_MARK || درخت_رمز (rhs) == ERROR_MARK)
    واپس error_mark_گرہ;

  /* Ensure an error for assigning a non-lvalue array to an array in
     C90.  */
  اگر (درخت_رمز (lhstype) == ARRAY_TYPE)
    {
      error_at (location, "assignment to expression with array type");
      واپس error_mark_گرہ;
    }

  /* For ObjC properties, defer this check.  */
  اگر (!objc_is_property_ref (lhs) && !lvalue_or_else (location, lhs, lv_تفویض))
    واپس error_mark_گرہ;

  is_atomic_op = really_atomic_lvalue (lhs);

  newrhs = rhs;

  اگر (درخت_رمز (lhs) == C_MAYBE_CONST_اظہاریہ)
    {
      درخت inner = build_modify_اظہاریہ (location, C_MAYBE_CONST_اظہاریہ_اظہاریہ (lhs),
				      lhs_origtype, modifycode, rhs_loc, rhs,
				      rhs_origtype);
      اگر (inner == error_mark_گرہ)
	واپس error_mark_گرہ;
      نتیجہ = build2 (C_MAYBE_CONST_اظہاریہ, درخت_TYPE (inner),
		       C_MAYBE_CONST_اظہاریہ_PRE (lhs), inner);
      gcc_assert (!C_MAYBE_CONST_اظہاریہ_INT_OPERANDS (lhs));
      C_MAYBE_CONST_اظہاریہ_NON_CONST (نتیجہ) = 1;
      protected_سیٹ_اظہاریہ_location (نتیجہ, location);
      واپس نتیجہ;
    }

  /* If a binary op has been requested, combine the old LHS value with the RHS
     producing the value we should actually store into the LHS.  */

  اگر (modifycode != NOP_اظہاریہ)
    {
      lhs = c_fully_fold (lhs, جھوٹ, تہی, سچ);
      lhs = stabilize_reference (lhs);

      /* Construct the RHS for any non-atomic compound assignment. */
      اگر (!is_atomic_op)
        {
	  /* If in LHS op= RHS the RHS has side-effects, ensure they
	     are preevaluated before the rest of the assignment expression's
	     side-effects, because RHS could contain e.g. function calls
	     that modify LHS.  */
	  اگر (درخت_SIDE_EFFECTS (rhs))
	    {
	      اگر (درخت_رمز (rhs) == EXCESS_PRECISION_اظہاریہ)
		newrhs = save_اظہاریہ (درخت_عملیہ (rhs, 0));
	      ورنہ
		newrhs = save_اظہاریہ (rhs);
	      rhseval = newrhs;
	      اگر (درخت_رمز (rhs) == EXCESS_PRECISION_اظہاریہ)
		newrhs = build1 (EXCESS_PRECISION_اظہاریہ, درخت_TYPE (rhs),
				 newrhs);
	    }
	  منطقی clear_decl_read = جھوٹ;
	  اگر ((VAR_P (lhs) || درخت_رمز (lhs) == PARM_DECL)
	      && !DECL_READ_P (lhs)
	      && (VAR_P (lhs) ? warn_غیر_مستعمل_but_سیٹ_variable
			      : warn_غیر_مستعمل_but_سیٹ_parameter) > 2)
	    {
	      mark_exp_read (newrhs);
	      اگر (!DECL_READ_P (lhs))
		clear_decl_read = سچ;
	    }

	  newrhs = build_ثنائی_op (location, modifycode,
				    convert_lvalue_مقصد_rvalue (location, lhs,
							      سچ, سچ),
				    newrhs, سچ);
	  اگر (clear_decl_read)
	    DECL_READ_P (lhs) = 0;

	  /* The original type of the right hand side is no longer
	     meaningful.  */
	  rhs_origtype = NULL_درخت;
	}
    }

  اگر (c_dialect_objc ())
    {
      /* Check if we are modifying an Objective-C property reference;
	 if so, we need to generate setter calls.  */
      اگر (درخت_رمز (newrhs) == EXCESS_PRECISION_اظہاریہ)
	نتیجہ = objc_maybe_build_modify_اظہاریہ (lhs, درخت_عملیہ (newrhs, 0));
      ورنہ
	نتیجہ = objc_maybe_build_modify_اظہاریہ (lhs, newrhs);
      اگر (نتیجہ)
	جاؤ return_نتیجہ;

      /* Else, do the check that we postponed for Objective-C.  */
      اگر (!lvalue_or_else (location, lhs, lv_تفویض))
	واپس error_mark_گرہ;
    }

  /* Give an error for storing in something that is 'const'.  */

  اگر (TYPE_READONLY (lhstype)
      || (ریکارڈ_OR_UNION_TYPE_P (lhstype)
	  && C_TYPE_FIELDS_READONLY (lhstype)))
    {
      readonly_error (location, lhs, lv_تفویض);
      واپس error_mark_گرہ;
    }
  ورنہ اگر (درخت_READONLY (lhs))
    readonly_warning (lhs, lv_تفویض);

  /* If storing into a structure or union member,
     it has probably been given type `int'.
     Compute the type that would go with
     the actual amount of storage the member occupies.  */

  اگر (درخت_رمز (lhs) == COMPONENT_REF
      && (درخت_رمز (lhstype) == INTEGER_TYPE
	  || درخت_رمز (lhstype) == BOOLEAN_TYPE
	  || SCALAR_FLOAT_TYPE_P (lhstype)
	  || درخت_رمز (lhstype) == ENUMERAL_TYPE))
    lhstype = درخت_TYPE (get_unwidened (lhs, 0));

  /* If storing in a field that is in actuality a short or narrower than one,
     we must store in the field in its actual type.  */

  اگر (lhstype != درخت_TYPE (lhs))
    {
      lhs = copy_گرہ (lhs);
      درخت_TYPE (lhs) = lhstype;
    }

  /* Issue -Wc++-compat warnings about an assignment to an enum type
     when LHS does not have its original type.  This happens for,
     e.g., an enum bitfield in a struct.  */
  اگر (warn_cxx_compat
      && lhs_origtype != NULL_درخت
      && lhs_origtype != lhstype
      && درخت_رمز (lhs_origtype) == ENUMERAL_TYPE)
    {
      درخت checktype = (rhs_origtype != NULL_درخت
			? rhs_origtype
			: درخت_TYPE (rhs));
      اگر (checktype != error_mark_گرہ
	  && (TYPE_MAIN_VARIANT (checktype) != TYPE_MAIN_VARIANT (lhs_origtype)
	      || (is_atomic_op && modifycode != NOP_اظہاریہ)))
	warning_at (location, OPT_Wc___compat,
		    "enum conversion in assignment is invalid in C++");
    }

  /* Remove qualifiers.  */
  lhstype = c_build_qualified_type (lhstype, TYPE_UNQUALIFIED);
  olhstype = c_build_qualified_type (olhstype, TYPE_UNQUALIFIED);

  /* Convert new value to destination type.  Fold it first, then
     restore any excess precision information, for the sake of
     conversion warnings.  */

  اگر (!(is_atomic_op && modifycode != NOP_اظہاریہ))
    {
      درخت rhs_semantic_type = NULL_درخت;
      اگر (!c_اندر_omp_for)
	{
	  اگر (درخت_رمز (newrhs) == EXCESS_PRECISION_اظہاریہ)
	    {
	      rhs_semantic_type = درخت_TYPE (newrhs);
	      newrhs = درخت_عملیہ (newrhs, 0);
	    }
	  npc = null_اشارہ_گر_constant_p (newrhs);
	  newrhs = c_fully_fold (newrhs, جھوٹ, تہی);
	  اگر (rhs_semantic_type)
	    newrhs = build1 (EXCESS_PRECISION_اظہاریہ, rhs_semantic_type, newrhs);
	}
      ورنہ
	npc = null_اشارہ_گر_constant_p (newrhs);
      newrhs = convert_for_assignment (location, rhs_loc, lhstype, newrhs,
				       rhs_origtype, ic_تفویض, npc,
				       NULL_درخت, NULL_درخت, 0);
      اگر (درخت_رمز (newrhs) == ERROR_MARK)
	واپس error_mark_گرہ;
    }

  /* Emit ObjC write barrier, if necessary.  */
  اگر (c_dialect_objc () && flag_objc_gc)
    {
      نتیجہ = objc_generate_write_barrier (lhs, modifycode, newrhs);
      اگر (نتیجہ)
	{
	  protected_سیٹ_اظہاریہ_location (نتیجہ, location);
	  جاؤ return_نتیجہ;
	}
    }

  /* Scan operands.  */

  اگر (is_atomic_op)
    نتیجہ = build_atomic_تفویض (location, lhs, modifycode, newrhs, جھوٹ);
  ورنہ
    {
      نتیجہ = build2 (MODIFY_اظہاریہ, lhstype, lhs, newrhs);
      درخت_SIDE_EFFECTS (نتیجہ) = 1;
      protected_سیٹ_اظہاریہ_location (نتیجہ, location);
    }

  /* If we got the LHS in a different type for storing in,
     convert the result back to the nominal type of LHS
     so that the value we return always has the same type
     as the LHS argument.  */

  اگر (olhstype == درخت_TYPE (نتیجہ))
    جاؤ return_نتیجہ;

  نتیجہ = convert_for_assignment (location, rhs_loc, olhstype, نتیجہ,
				   rhs_origtype, ic_تفویض, جھوٹ, NULL_درخت,
				   NULL_درخت, 0);
  protected_سیٹ_اظہاریہ_location (نتیجہ, location);

return_نتیجہ:
  اگر (rhseval)
    نتیجہ = build2 (COMPOUND_اظہاریہ, درخت_TYPE (نتیجہ), rhseval, نتیجہ);
  واپس نتیجہ;
}

/* Return whether STRUCT_TYPE has an anonymous field with type TYPE.
   This is used to implement -fplan9-extensions.  */

ساکن منطقی
ڈھونڈو_anonymous_میدان_with_type (درخت struct_type, درخت type)
{
  درخت میدان_2;
  منطقی ملا;

  gcc_assert (ریکارڈ_OR_UNION_TYPE_P (struct_type));
  ملا = جھوٹ;
  برائے (میدان_2 = TYPE_FIELDS (struct_type);
       میدان_2 != NULL_درخت;
       میدان_2 = درخت_CHAIN (میدان_2))
    {
      درخت fieldtype = remove_qualifiers (درخت_TYPE (میدان_2));
      اگر (DECL_NAME (میدان_2) == تہی
	  && comptypes (type, fieldtype))
	{
	  اگر (ملا)
	    واپس جھوٹ;
	  ملا = سچ;
	}
      ورنہ اگر (DECL_NAME (میدان_2) == تہی
	       && ریکارڈ_OR_UNION_TYPE_P (درخت_TYPE (میدان_2))
	       && ڈھونڈو_anonymous_میدان_with_type (درخت_TYPE (میدان_2), type))
	{
	  اگر (ملا)
	    واپس جھوٹ;
	  ملا = سچ;
	}
    }
  واپس ملا;
}

/* RHS is an expression whose type is pointer to struct.  If there is
   an anonymous field in RHS with type TYPE, then return a pointer to
   that field in RHS.  This is used with -fplan9-extensions.  This
   returns NULL if no conversion could be found.  */

ساکن درخت
convert_مقصد_anonymous_میدان (location_t location, درخت type, درخت rhs)
{
  درخت rhs_struct_type, lhs_main_type;
  درخت میدان_2, ملا_میدان;
  منطقی ملا_sub_میدان;
  درخت ret;

  gcc_assert (اشارہ_گر_TYPE_P (درخت_TYPE (rhs)));
  rhs_struct_type = درخت_TYPE (درخت_TYPE (rhs));
  gcc_assert (ریکارڈ_OR_UNION_TYPE_P (rhs_struct_type));

  gcc_assert (اشارہ_گر_TYPE_P (type));
  lhs_main_type = remove_qualifiers (درخت_TYPE (type));

  ملا_میدان = NULL_درخت;
  ملا_sub_میدان = جھوٹ;
  برائے (میدان_2 = TYPE_FIELDS (rhs_struct_type);
       میدان_2 != NULL_درخت;
       میدان_2 = درخت_CHAIN (میدان_2))
    {
      اگر (DECL_NAME (میدان_2) != NULL_درخت
	  || !ریکارڈ_OR_UNION_TYPE_P (درخت_TYPE (میدان_2)))
	جاری;
      درخت fieldtype = remove_qualifiers (درخت_TYPE (میدان_2));
      اگر (comptypes (lhs_main_type, fieldtype))
	{
	  اگر (ملا_میدان != NULL_درخت)
	    واپس NULL_درخت;
	  ملا_میدان = میدان_2;
	}
      ورنہ اگر (ڈھونڈو_anonymous_میدان_with_type (درخت_TYPE (میدان_2),
					       lhs_main_type))
	{
	  اگر (ملا_میدان != NULL_درخت)
	    واپس NULL_درخت;
	  ملا_میدان = میدان_2;
	  ملا_sub_میدان = سچ;
	}
    }

  اگر (ملا_میدان == NULL_درخت)
    واپس NULL_درخت;

  ret = fold_build3_loc (location, COMPONENT_REF, درخت_TYPE (ملا_میدان),
			 build_fold_بالواسطہ_ref (rhs), ملا_میدان,
			 NULL_درخت);
  ret = build_fold_addr_اظہاریہ_loc (location, ret);

  اگر (ملا_sub_میدان)
    {
      ret = convert_مقصد_anonymous_میدان (location, type, ret);
      gcc_assert (ret != NULL_درخت);
    }

  واپس ret;
}

/* Issue an error message for a bad initializer component.
   GMSGID identifies the message.
   The component name is taken from the spelling stack.  */

ساکن خالی ATTRIBUTE_GCC_DIAG (2,0)
error_init (location_t loc, ثابت حرف *gmsgid, ...)
{
  حرف *ofwhat;

  auto_diagnostic_گروہ d;

  /* The gmsgid may be a format string with %< and %>. */
  va_list ap;
  va_آغاز (ap, gmsgid);
  منطقی warned = emit_diagnostic_valist (diagnostics::قسم::error,
					loc, -1, gmsgid, &ap);
  va_انتہا (ap);

  ofwhat = print_spelling ((حرف *) alloca (spelling_لمبائی () + 1));
  اگر (*ofwhat && warned)
    inform (loc, "(near initialization for %qs)", ofwhat);
}

/* Used to implement pedwarn_init and permerror_init.  */

ساکن منطقی ATTRIBUTE_GCC_DIAG (3,0)
pedwarn_permerror_init (location_t loc, صحیح opt, ثابت حرف *gmsgid,
			va_list *ap, شمار diagnostics::قسم قسم)
{
  /* Use the location where a macro was expanded rather than where
     it was defined to make sure macros defined in system headers
     but used incorrectly elsewhere are diagnosed.  */
  location_t exploc = expansion_نقطہ_location_if_اندر_system_سرخی (loc);
  auto_diagnostic_گروہ d;
  منطقی warned = emit_diagnostic_valist (قسم, exploc, opt, gmsgid, ap);
  اگر (warned)
    {
      حرف *ofwhat = print_spelling ((حرف *) alloca (spelling_لمبائی () + 1));
      اگر (*ofwhat)
	inform (exploc, "(near initialization for %qs)", ofwhat);
    }
  واپس warned;
}

/* Issue a pedantic warning for a bad initializer component.  OPT is
   the option OPT_* (from options.h) controlling this warning or 0 if
   it is unconditionally given.  GMSGID identifies the message.  The
   component name is taken from the spelling stack.  */

ساکن منطقی ATTRIBUTE_GCC_DIAG (3,0)
pedwarn_init (location_t loc, صحیح opt, ثابت حرف *gmsgid, ...)
{
  va_list ap;
  va_آغاز (ap, gmsgid);
  منطقی warned = pedwarn_permerror_init (loc, opt, gmsgid, &ap,
					diagnostics::قسم::pedwarn);
  va_انتہا (ap);
  واپس warned;
}

/* Like pedwarn_init, but issue a permerror.  */

ساکن منطقی ATTRIBUTE_GCC_DIAG (3,0)
permerror_init (location_t loc, صحیح opt, ثابت حرف *gmsgid, ...)
{
  va_list ap;
  va_آغاز (ap, gmsgid);
  منطقی warned = pedwarn_permerror_init (loc, opt, gmsgid, &ap,
					diagnostics::قسم::permerror);
  va_انتہا (ap);
  واپس warned;
}

/* Issue a warning for a bad initializer component.

   OPT is the OPT_W* value corresponding to the warning option that
   controls this warning.  GMSGID identifies the message.  The
   component name is taken from the spelling stack.  */

ساکن خالی
warning_init (location_t loc, صحیح opt, ثابت حرف *gmsgid)
{
  حرف *ofwhat;
  منطقی warned;

  auto_diagnostic_گروہ d;

  /* Use the location where a macro was expanded rather than where
     it was defined to make sure macros defined in system headers
     but used incorrectly elsewhere are diagnosed.  */
  location_t exploc = expansion_نقطہ_location_if_اندر_system_سرخی (loc);

  /* The gmsgid may be a format string with %< and %>. */
  warned = warning_at (exploc, opt, gmsgid);
  اگر (warned)
    {
      ofwhat = print_spelling ((حرف *) alloca (spelling_لمبائی () + 1));
      اگر (*ofwhat)
	inform (exploc, "(near initialization for %qs)", ofwhat);
    }
}

/* If TYPE is an array type and EXPR is a parenthesized string
   constant, warn if pedantic that EXPR is being used to initialize an
   object of type TYPE.  */

خالی
maybe_warn_string_init (location_t loc, درخت type, ساخت c_اظہاریہ اظہاریہ)
{
  اگر (pedantic
      && درخت_رمز (type) == ARRAY_TYPE
      && درخت_رمز (اظہاریہ.قدر) == STRING_CST
      && اظہاریہ.original_رمز != STRING_CST)
    pedwarn_init (loc, OPT_Wpedantic,
		  "array initialized from parenthesized string constant");
}

/* Attempt to locate the parameter with the given index within FNDECL,
   returning DECL_SOURCE_LOCATION (FNDECL) if it can't be found.  */

ساکن location_t
get_fndecl_دلیل_location (درخت fndecl, صحیح argnum)
{
  صحیح i;
  درخت param;

  /* Locate param by index within DECL_ARGUMENTS (fndecl).  */
  برائے (i = 0, param = DECL_ARGUMENTS (fndecl);
       i < argnum && param;
       i++, param = درخت_CHAIN (param))
    ;

  /* If something went wrong (e.g. if we have a builtin and thus no arguments),
     return DECL_SOURCE_LOCATION (FNDECL).  */
  اگر (param == تہی)
    واپس DECL_ماخذ_LOCATION (fndecl);

  واپس DECL_ماخذ_LOCATION (param);
}

/* Issue a note about a mismatching argument for parameter PARMNUM
   to FUNDECL, for types EXPECTED_TYPE and ACTUAL_TYPE.
   Attempt to issue the note at the pertinent parameter of the decl;
   failing that issue it at the location of FUNDECL; failing that
   issue it at PLOC.
   Use highlight_colors::actual for the ACTUAL_TYPE
   and highlight_colors::expected for EXPECTED_TYPE and the
   parameter of FUNDECL*/

ساکن خالی
inform_for_arg (درخت fundecl, location_t ploc, صحیح parmnum,
		درخت expected_type, درخت actual_type)
{
  location_t loc;
  اگر (fundecl && !DECL_IS_UNDECLARED_BUILTIN (fundecl))
    loc = get_fndecl_دلیل_location (fundecl, parmnum - 1);
  ورنہ
    loc = ploc;

  gcc_rich_location richloc (loc, خالی_اشاریہ, highlight_colors::expected);

  pp_markup::element_expected_type elem_expected_type (expected_type);
  pp_markup::element_actual_type elem_actual_type (actual_type);
  inform (&richloc,
	  "expected %e but argument is of type %e",
	  &elem_expected_type, &elem_actual_type);
}

/* Issue a warning when an argument of ARGTYPE is passed to a built-in
   function FUNDECL declared without prototype to parameter PARMNUM of
   PARMTYPE when ARGTYPE does not promote to PARMTYPE.  */

ساکن خالی
maybe_warn_builtin_no_proto_arg (location_t loc, درخت fundecl, صحیح parmnum,
				 درخت parmtype, درخت argtype)
{
  درخت_رمز_2 parmcode = درخت_رمز (parmtype);
  درخت_رمز_2 argcode = درخت_رمز (argtype);
  درخت promoted = c_type_promotes_مقصد (argtype);

  /* Avoid warning for enum arguments that promote to an integer type
     of the same size/mode.  */
  اگر (parmcode == INTEGER_TYPE
      && argcode == ENUMERAL_TYPE
      && TYPE_منوال (parmtype) == TYPE_منوال (argtype))
    واپس;

  اگر ((parmcode == argcode
       || (parmcode == INTEGER_TYPE
	   && argcode == ENUMERAL_TYPE))
      && TYPE_MAIN_VARIANT (parmtype) == TYPE_MAIN_VARIANT (promoted))
    واپس;

  /* This diagnoses even signed/unsigned mismatches.  Those might be
     safe in many cases but GCC may emit suboptimal code for them so
     warning on those cases drives efficiency improvements.  */
  اگر (warning_at (loc, OPT_Wbuiltin_declaration_mismatch,
		  TYPE_MAIN_VARIANT (promoted) == argtype
		  ? G_("%qD argument %d type is %qT where %qT is expected "
		       "in a call to built-in function declared without "
		       "prototype")
		  : G_("%qD argument %d promotes to %qT where %qT is expected "
		       "in a call to built-in function declared without "
		       "prototype"),
		  fundecl, parmnum, promoted, parmtype))
    inform (DECL_ماخذ_LOCATION (fundecl),
	    "built-in %qD declared here",
	    fundecl);
}

/* Print a declaration in quotes, with the given highlight_color.
   Analogous to handler for %qD, but with a specific highlight color.  */

جماعت pp_element_quoted_decl : عوامی pp_element
{
عوامی:
  pp_element_quoted_decl (درخت decl, ثابت حرف *highlight_color)
  : m_decl (decl),
    m_highlight_color (highlight_color)
  {
  }

  خالی جوڑو_مقصد_phase_2 (pp_markup::context &ctxt) override
  {
    ctxt.begin_quote ();
    ctxt.begin_highlight_color (m_highlight_color);

    print_decl (ctxt);

    ctxt.انتہا_highlight_color ();
    ctxt.انتہا_quote ();
  }

  خالی print_decl (pp_markup::context &ctxt)
  {
    pretty_printer *ثابت pp = &ctxt.m_pp;
    pp->سیٹ_padding (pp_none);
    اگر (DECL_NAME (m_decl))
      pp_identifier (pp, lang_hooks.decl_printable_name (m_decl, 2));
    ورنہ
      pp_string (pp, _("({anonymous})"));
  }

نجی:
  درخت m_decl;
  ثابت حرف *m_highlight_color;
};

/* If TYPE is from a typedef, issue a note showing the location
   to the user.
   Use HIGHLIGHT_COLOR as the highlight color.  */

ساکن خالی
maybe_inform_typedef_location (درخت type, ثابت حرف *highlight_color)
{
  اگر (!typedef_variant_p (type))
    واپس;

  درخت typedef_decl = TYPE_NAME (type);
  gcc_assert (درخت_رمز (typedef_decl) == TYPE_DECL);
  gcc_rich_location richloc (DECL_ماخذ_LOCATION (typedef_decl),
			     خالی_اشاریہ, highlight_color);
  pp_element_quoted_decl e_typedef_decl (typedef_decl, highlight_color);
  inform (&richloc, "%e declared here", &e_typedef_decl);
}

/* Convert value RHS to type TYPE as preparation for an assignment to
   an lvalue of type TYPE.  If ORIGTYPE is not NULL_TREE, it is the
   original type of RHS; this differs from TREE_TYPE (RHS) for enum
   types.  NULL_POINTER_CONSTANT says whether RHS was a null pointer
   constant before any folding.
   The real work of conversion is done by `convert'.
   The purpose of this function is to generate error messages
   for assignments that are not allowed in C.
   ERRTYPE says whether it is argument passing, assignment,
   initialization or return.

   In the following example, '~' denotes where EXPR_LOC and '^' where
   LOCATION point to:

     f (var);      [ic_argpass]
     ^  ~~~
     x = var;      [ic_assign]
       ^ ~~~;
     int x = var;  [ic_init]
	     ^^^
     return x;     [ic_return]
	    ^

   FUNCTION is a tree for the function being called.
   PARMNUM is the number of the argument, for printing in error messages.
   WARNOPT may be set to a warning option to issue the corresponding warning
   rather than an error for invalid conversions.  Used for calls to built-in
   functions declared without a prototype.  */

ساکن درخت
convert_for_assignment (location_t location, location_t اظہاریہ_loc, درخت type,
			درخت rhs, درخت origtype, شمار impl_conv errtype,
			منطقی null_اشارہ_گر_constant, درخت fundecl,
			درخت function, صحیح parmnum, صحیح warnopt /* = 0 */)
{
  شمار درخت_رمز_2 codel = درخت_رمز (type);
  درخت orig_rhs = rhs;
  درخت rhstype;
  شمار درخت_رمز_2 coder;
  درخت rname = NULL_درخت;
  منطقی objc_ok = جھوٹ;

  /* Use the expansion point location to handle cases such as user's
     function returning a wrong-type macro defined in a system header.  */
  location = expansion_نقطہ_location_if_اندر_system_سرخی (location);

  اگر (errtype == ic_argpass)
    {
      درخت selector;
      /* Change pointer to function to the function itself for
	 diagnostics.  */
      اگر (درخت_رمز (function) == ADDR_اظہاریہ
	  && درخت_رمز (درخت_عملیہ (function, 0)) == FUNCTION_DECL)
	function = درخت_عملیہ (function, 0);

      /* Handle an ObjC selector specially for diagnostics.  */
      selector = objc_پیغام_selector ();
      rname = function;
      اگر (selector && parmnum > 2)
	{
	  rname = selector;
	  parmnum -= 2;
	}
    }

  /* This macro is used to emit diagnostics to ensure that all format
     strings are complete sentences, visible to gettext and checked at
     compile time.  */
#تعریف_کرو PEDWARN_FOR_ASSIGNMENT(LOCATION, PLOC, OPT, AR, AS, اندر, RE)	 \
  کرو {                                                                   \
    انتخاب (errtype)                                                     \
      {                                                                  \
      حالت ic_argpass:                                                   \
	{								\
	  auto_diagnostic_گروہ d;						\
	  اگر (pedwarn (PLOC, OPT, AR, parmnum, rname))		\
	    inform_for_arg (fundecl, (PLOC), parmnum, type, rhstype); \
	}								\
        توڑو;                                                           \
      حالت ic_تفویض:                                                    \
        pedwarn (LOCATION, OPT, AS);                                     \
        توڑو;                                                           \
      حالت ic_init:                                                      \
      حالت ic_init_const:                                                \
        pedwarn_init (LOCATION, OPT, اندر);                                \
        توڑو;                                                           \
      حالت ic_return:                                                    \
        pedwarn (LOCATION, OPT, RE);					 \
        توڑو;                                                           \
      طےشدہ:                                                           \
        gcc_unreachable ();                                              \
      }                                                                  \
  } جب (0)

  /* This macro is used to emit diagnostics to ensure that all format
     strings are complete sentences, visible to gettext and checked at
     compile time.  It can be called with 'pedwarn' or 'warning_at'.  */
#تعریف_کرو WARNING_FOR_QUALIFIERS(PEDWARN, LOCATION, PLOC, OPT, AR, AS, اندر, RE, QUALS) \
  کرو {                                                                   \
    انتخاب (errtype)                                                     \
      {                                                                  \
      حالت ic_argpass:                                                   \
	{								 \
	  auto_diagnostic_گروہ d;					 \
	  اگر (PEDWARN) {						 \
	    اگر (pedwarn (PLOC, OPT, AR, parmnum, rname, QUALS))          \
	      inform_for_arg (fundecl, (PLOC), parmnum, type, rhstype);  \
	  } ورنہ {							 \
	    اگر (warning_at (PLOC, OPT, AR, parmnum, rname, QUALS))	 \
	      inform_for_arg (fundecl, (PLOC), parmnum, type, rhstype);  \
	  }								 \
	}								 \
        توڑو;                                                           \
      حالت ic_تفویض:                                                    \
	اگر (PEDWARN)							 \
	  pedwarn (LOCATION, OPT, AS, QUALS);                            \
	ورنہ								 \
	  warning_at (LOCATION, OPT, AS, QUALS);                         \
        توڑو;                                                           \
      حالت ic_init:                                                      \
      حالت ic_init_const:                                                \
	اگر (PEDWARN)							 \
	  pedwarn (LOCATION, OPT, اندر, QUALS);                            \
	ورنہ								 \
	  warning_at (LOCATION, OPT, اندر, QUALS);                         \
        توڑو;                                                           \
      حالت ic_return:                                                    \
	اگر (PEDWARN)							 \
	  pedwarn (LOCATION, OPT, RE, QUALS);                            \
	ورنہ								 \
	  warning_at (LOCATION, OPT, RE, QUALS);                         \
        توڑو;                                                           \
      طےشدہ:                                                           \
        gcc_unreachable ();                                              \
      }                                                                  \
  } جب (0)

  /* This macro is used to emit diagnostics to ensure that all format
     strings are complete sentences, visible to gettext and checked at
     compile time.  It is the same as PEDWARN_FOR_ASSIGNMENT but with an
     extra parameter to enumerate qualifiers.  */
#تعریف_کرو PEDWARN_FOR_QUALIFIERS(LOCATION, PLOC, OPT, AR, AS, اندر, RE, QUALS) \
   WARNING_FOR_QUALIFIERS (سچ, LOCATION, PLOC, OPT, AR, AS, اندر, RE, QUALS)


  اگر (درخت_رمز (rhs) == EXCESS_PRECISION_اظہاریہ)
    rhs = درخت_عملیہ (rhs, 0);

  rhstype = درخت_TYPE (rhs);
  coder = درخت_رمز (rhstype);

  اگر (coder == ERROR_MARK)
    واپس error_mark_گرہ;

  اگر (c_dialect_objc ())
    {
      صحیح parmno;

      انتخاب (errtype)
	{
	حالت ic_return:
	  parmno = 0;
	  توڑو;

	حالت ic_تفویض:
	  parmno = -1;
	  توڑو;

	حالت ic_init:
	حالت ic_init_const:
	  parmno = -2;
	  توڑو;

	طےشدہ:
	  parmno = parmnum;
	  توڑو;
	}

      objc_ok = objc_compare_types (type, rhstype, parmno, rname);
    }

  اگر (warn_cxx_compat)
    {
      درخت checktype = origtype != NULL_درخت ? origtype : rhstype;
      اگر (checktype != error_mark_گرہ
	  && درخت_رمز (type) == ENUMERAL_TYPE
	  && TYPE_MAIN_VARIANT (checktype) != TYPE_MAIN_VARIANT (type))
	انتخاب (errtype)
	  {
	  حالت ic_argpass:
	    اگر (pedwarn (اظہاریہ_loc, OPT_Wc___compat, "enum conversion when "
			 "passing argument %d of %qE is invalid in C++",
			 parmnum, rname))
	      inform ((fundecl && !DECL_IS_UNDECLARED_BUILTIN (fundecl))
		      ? DECL_ماخذ_LOCATION (fundecl) : اظہاریہ_loc,
		      "expected %qT but argument is of type %qT",
		      type, rhstype);
	    توڑو;
	  حالت ic_تفویض:
	    pedwarn (location, OPT_Wc___compat, "enum conversion from %qT to "
		     "%qT in assignment is invalid in C++", rhstype, type);
	    توڑو;
	  حالت ic_init:
	  حالت ic_init_const:
	    pedwarn_init (location, OPT_Wc___compat, "enum conversion from "
			  "%qT to %qT in initialization is invalid in C++",
			  rhstype, type);
	    توڑو;
	  حالت ic_return:
	    pedwarn (location, OPT_Wc___compat, "enum conversion from %qT to "
		     "%qT in return is invalid in C++", rhstype, type);
	    توڑو;
	  طےشدہ:
	    gcc_unreachable ();
	  }
    }

  اگر (warn_enum_conversion)
    {
      درخت checktype = origtype != NULL_درخت ? origtype : rhstype;
      اگر (checktype != error_mark_گرہ
	  && درخت_رمز (checktype) == ENUMERAL_TYPE
	  && درخت_رمز (type) == ENUMERAL_TYPE
	  && !comptypes (TYPE_MAIN_VARIANT (checktype), TYPE_MAIN_VARIANT (type)))
       {
	  gcc_rich_location loc (location);
	  warning_at (&loc, OPT_Wenum_conversion,
		      "implicit conversion from %qT to %qT",
		      checktype, type);
       }
    }

  اگر (TYPE_MAIN_VARIANT (type) == TYPE_MAIN_VARIANT (rhstype))
    {
      warn_for_پتہ_کا_packed_member (type, orig_rhs);
      اگر (type != rhstype)
	/* Convert RHS to TYPE in order to not lose TYPE in diagnostics.  */
	rhs = convert (type, rhs);
      واپس rhs;
    }

  اگر (coder == VOID_TYPE)
    {
      /* Except for passing an argument to an unprototyped function,
	 this is a constraint violation.  When passing an argument to
	 an unprototyped function, it is compile-time undefined;
	 making it a constraint in that case was rejected in
	 DR#252.  */
      ثابت حرف پیغام_2[] = "void value not ignored as it ought to be";
      اگر (warnopt)
	warning_at (location, warnopt, پیغام_2);
      ورنہ
	error_at (location, پیغام_2);
      واپس error_mark_گرہ;
    }
  rhs = require_complete_type (location, rhs);
  اگر (rhs == error_mark_گرہ)
    واپس error_mark_گرہ;

  اگر (coder == اشارہ_گر_TYPE && reject_gcc_builtin (rhs))
    واپس error_mark_گرہ;

  /* A non-reference type can convert to a reference.  This handles
     va_start, va_copy and possibly port built-ins.  */
  اگر (codel == REFERENCE_TYPE && coder != REFERENCE_TYPE)
    {
      اگر (!lvalue_p (rhs))
	{
	  ثابت حرف پیغام_2[] = "cannot pass rvalue to reference parameter";
	  اگر (warnopt)
	    warning_at (location, warnopt, پیغام_2);
	  ورنہ
	    error_at (location, پیغام_2);
	  واپس error_mark_گرہ;
	}
      اگر (!c_mark_addressable (rhs))
	واپس error_mark_گرہ;
      rhs = build1 (ADDR_اظہاریہ, c_build_اشارہ_گر_type (درخت_TYPE (rhs)), rhs);
      سیٹ_اظہاریہ_LOCATION (rhs, location);

      rhs = convert_for_assignment (location, اظہاریہ_loc,
				    c_build_اشارہ_گر_type (درخت_TYPE (type)),
				    rhs, origtype, errtype,
				    null_اشارہ_گر_constant, fundecl, function,
				    parmnum, warnopt);
      اگر (rhs == error_mark_گرہ)
	واپس error_mark_گرہ;

      rhs = build1 (NOP_اظہاریہ, type, rhs);
      سیٹ_اظہاریہ_LOCATION (rhs, location);
      واپس rhs;
    }
  /* Some types can interconvert without explicit casts.  */
  ورنہ اگر (codel == سمتیہ_TYPE && coder == سمتیہ_TYPE
	   && سمتیہ_types_convertible_p (type, درخت_TYPE (rhs), سچ))
    واپس convert (type, rhs);
  /* Arithmetic types all interconvert, and enum is treated like int.  */
  ورنہ اگر ((codel == INTEGER_TYPE || codel == REAL_TYPE
	    || codel == FIXED_نقطہ_TYPE
	    || codel == ENUMERAL_TYPE || codel == COMPLEX_TYPE
	    || codel == BOOLEAN_TYPE || codel == BITINT_TYPE)
	   && (coder == INTEGER_TYPE || coder == REAL_TYPE
	       || coder == FIXED_نقطہ_TYPE
	       || coder == ENUMERAL_TYPE || coder == COMPLEX_TYPE
	       || coder == BOOLEAN_TYPE || coder == BITINT_TYPE))
    {
      اگر (warnopt && errtype == ic_argpass)
	maybe_warn_builtin_no_proto_arg (اظہاریہ_loc, fundecl, parmnum, type,
					 rhstype);

      منطقی save = اندر_late_ثنائی_op;
      اگر (C_BOOLEAN_TYPE_P (type) || codel == COMPLEX_TYPE
	  || (coder == REAL_TYPE
	      && (codel == INTEGER_TYPE || codel == ENUMERAL_TYPE)
	      && sanitize_flags_p (SANITIZE_FLOAT_CAST)))
	اندر_late_ثنائی_op = سچ;
      درخت ret = convert_and_check (اظہاریہ_loc != UNKNOWN_LOCATION
				    ? اظہاریہ_loc : location, type, orig_rhs,
				    errtype == ic_init_const);
      اندر_late_ثنائی_op = save;
      واپس ret;
    }

  /* Aggregates in different TUs might need conversion.  */
  اگر ((codel == ریکارڈ_TYPE || codel == UNION_TYPE)
      && codel == coder
      && comptypes (TYPE_MAIN_VARIANT (type), TYPE_MAIN_VARIANT (rhstype)))
    واپس convert_and_check (اظہاریہ_loc != UNKNOWN_LOCATION
			      ? اظہاریہ_loc : location, type, rhs);

  /* Conversion to a transparent union or record from its member types.
     This applies only to function arguments.  */
  اگر (((codel == UNION_TYPE || codel == ریکارڈ_TYPE)
      && TYPE_TRANSPARENT_AGGR (type))
      && errtype == ic_argpass)
    {
      درخت memb, marginal_memb = NULL_درخت;

      برائے (memb = TYPE_FIELDS (type); memb ; memb = DECL_CHAIN (memb))
	{
	  درخت memb_type = درخت_TYPE (memb);

	  اگر (comptypes (TYPE_MAIN_VARIANT (memb_type),
			 TYPE_MAIN_VARIANT (rhstype)))
	    توڑو;

	  اگر (درخت_رمز (memb_type) != اشارہ_گر_TYPE)
	    جاری;

	  اگر (coder == اشارہ_گر_TYPE)
	    {
	      درخت ttl = درخت_TYPE (memb_type);
	      درخت ttr = درخت_TYPE (rhstype);

	      /* Any non-function converts to a [const][volatile] void *
		 and vice versa; otherwise, targets must be the same.
		 Meanwhile, the lhs target must have all the qualifiers of
		 the rhs.  */
	      اگر ((VOID_TYPE_P (ttl) && !TYPE_ATOMIC (ttl))
		  || (VOID_TYPE_P (ttr) && !TYPE_ATOMIC (ttr))
		  || comp_ہدف_types (location, memb_type, rhstype))
		{
		  صحیح lquals = TYPE_QUALS (ttl) & ~TYPE_QUAL_ATOMIC;
		  صحیح rquals = TYPE_QUALS (ttr) & ~TYPE_QUAL_ATOMIC;
		  /* If this type won't generate any warnings, use it.  */
		  اگر (lquals == rquals
		      || ((درخت_رمز (ttr) == FUNCTION_TYPE
			   && درخت_رمز (ttl) == FUNCTION_TYPE)
			  ? ((lquals | rquals) == rquals)
			  : ((lquals | rquals) == lquals)))
		    توڑو;

		  /* Keep looking for a better type, but remember this one.  */
		  اگر (!marginal_memb)
		    marginal_memb = memb;
		}
	    }

	  /* Can convert integer zero to any pointer type.  */
	  اگر (null_اشارہ_گر_constant)
	    {
	      rhs = null_اشارہ_گر_گرہ;
	      توڑو;
	    }
	}

      اگر (memb || marginal_memb)
	{
	  اگر (!memb)
	    {
	      /* We have only a marginally acceptable member type;
		 it needs a warning.  */
	      درخت ttl = درخت_TYPE (درخت_TYPE (marginal_memb));
	      درخت ttr = درخت_TYPE (rhstype);

	      /* Const and volatile mean something different for function
		 types, so the usual warnings are not appropriate.  */
	      اگر (درخت_رمز (ttr) == FUNCTION_TYPE
		  && درخت_رمز (ttl) == FUNCTION_TYPE)
		{
		  /* Because const and volatile on functions are
		     restrictions that say the function will not do
		     certain things, it is okay to use a const or volatile
		     function where an ordinary one is wanted, but not
		     vice-versa.  */
		  اگر (TYPE_QUALS_NO_ADDR_SPACE (ttl)
		      & ~TYPE_QUALS_NO_ADDR_SPACE (ttr))
		    PEDWARN_FOR_QUALIFIERS (location, اظہاریہ_loc,
					    OPT_Wdiscarded_qualifiers,
					    G_("passing argument %d of %qE "
					       "makes %q#v qualified function "
					       "pointer from unqualified"),
					    G_("assignment makes %q#v qualified "
					       "function pointer from "
					       "unqualified"),
					    G_("initialization makes %q#v qualified "
					       "function pointer from "
					       "unqualified"),
					    G_("return makes %q#v qualified function "
					       "pointer from unqualified"),
					    TYPE_QUALS (ttl) & ~TYPE_QUALS (ttr));
		}
	      ورنہ اگر (TYPE_QUALS_NO_ADDR_SPACE (ttr)
		       & ~TYPE_QUALS_NO_ADDR_SPACE (ttl))
		PEDWARN_FOR_QUALIFIERS (location, اظہاریہ_loc,
				        OPT_Wdiscarded_qualifiers,
				        G_("passing argument %d of %qE discards "
					   "%qv qualifier from pointer target type"),
				        G_("assignment discards %qv qualifier "
					   "from pointer target type"),
				        G_("initialization discards %qv qualifier "
					   "from pointer target type"),
				        G_("return discards %qv qualifier from "
					   "pointer target type"),
				        TYPE_QUALS (ttr) & ~TYPE_QUALS (ttl));

	      memb = marginal_memb;
	    }

	  اگر (!fundecl || !DECL_اندر_SYSTEM_سرخی (fundecl))
	    pedwarn (location, OPT_Wpedantic,
		     "ISO C prohibits argument conversion to union type");

	  rhs = fold_convert_loc (location, درخت_TYPE (memb), rhs);
	  واپس build_constructor_single (type, memb, rhs);
	}
    }

  /* Conversions among pointers */
  ورنہ اگر ((codel == اشارہ_گر_TYPE || codel == REFERENCE_TYPE)
	   && (coder == codel))
    {
      /* If RHS refers to a built-in declared without a prototype
	 BLTIN is the declaration of the built-in with a prototype
	 and RHSTYPE is set to the actual type of the built-in.  */
      درخت bltin;
      rhstype = type_or_builtin_type (rhs, &bltin);

      درخت ttl = درخت_TYPE (type);
      درخت ttr = درخت_TYPE (rhstype);
      منطقی is_opaque_اشارہ_گر;
      منطقی ہدف_cmp = جھوٹ;   /* Cache comp_target_types () result.  */
      addr_space_t asl;
      addr_space_t asr;

      درخت mvl = remove_qualifiers (ttl);
      درخت mvr = remove_qualifiers (ttr);

      /* Opaque pointers are treated like void pointers.  */
      is_opaque_اشارہ_گر = سمتیہ_targets_convertible_p (ttl, ttr);

      /* The Plan 9 compiler permits a pointer to a struct to be
	 automatically converted into a pointer to an anonymous field
	 within the struct.  */
      اگر (flag_plan9_extensions
	  && ریکارڈ_OR_UNION_TYPE_P (mvl)
	  && ریکارڈ_OR_UNION_TYPE_P (mvr)
	  && mvl != mvr)
	{
	  درخت new_rhs = convert_مقصد_anonymous_میدان (location, type, rhs);
	  اگر (new_rhs != NULL_درخت)
	    {
	      rhs = new_rhs;
	      rhstype = درخت_TYPE (rhs);
	      coder = درخت_رمز (rhstype);
	      ttr = درخت_TYPE (rhstype);
	      mvr = TYPE_MAIN_VARIANT (ttr);
	    }
	}

      /* C++ does not allow the implicit conversion void* -> T*.  However,
	 for the purpose of reducing the number of false positives, we
	 tolerate the special case of

		int *p = NULL;

	 where NULL is typically defined in C to be '(void *) 0'.  */
      اگر (VOID_TYPE_P (ttr) && rhs != null_اشارہ_گر_گرہ && !VOID_TYPE_P (ttl))
	warning_at (errtype == ic_argpass ? اظہاریہ_loc : location,
		    OPT_Wc___compat,
		    "request for implicit conversion "
		    "from %qT to %qT not permitted in C++", rhstype, type);

      /* Warn of new allocations that are not big enough for the target
	 type.  */
      اگر (warn_alloc_سائز && درخت_رمز (rhs) == CALL_اظہاریہ)
	اگر (درخت fndecl = get_callee_fndecl (rhs))
	  اگر (DECL_IS_MALLOC (fndecl))
	    {
	      درخت attrs = TYPE_اوصاف (درخت_TYPE (fndecl));
	      درخت alloc_سائز = lookup_attribute ("alloc_size", attrs);
	      اگر (alloc_سائز)
		warn_for_alloc_سائز (location, ttl, rhs, alloc_سائز);
	    }

      /* See if the pointers point to incompatible address spaces.  */
      asl = TYPE_ADDR_SPACE (ttl);
      asr = TYPE_ADDR_SPACE (ttr);
      اگر (!null_اشارہ_گر_constant_p (rhs)
	  && asr != asl && !targetm.addr_space.subset_p (asr, asl))
	{
	  auto_diagnostic_گروہ d;
	  منطقی diagnosed = سچ;
	  انتخاب (errtype)
	    {
	    حالت ic_argpass:
	      {
		ثابت حرف پیغام_2[] = G_("passing argument %d of %qE from "
				      "pointer to non-enclosed address space");
		اگر (warnopt)
		  diagnosed
		    = warning_at (اظہاریہ_loc, warnopt, پیغام_2, parmnum, rname);
		ورنہ
		  error_at (اظہاریہ_loc, پیغام_2, parmnum, rname);
	      توڑو;
	      }
	    حالت ic_تفویض:
	      {
		ثابت حرف پیغام_2[] = G_("assignment from pointer to "
				      "non-enclosed address space");
		اگر (warnopt)
		  diagnosed = warning_at (location, warnopt, پیغام_2);
		ورنہ
		  error_at (location, پیغام_2);
		توڑو;
	      }
	    حالت ic_init:
	    حالت ic_init_const:
	      {
		ثابت حرف پیغام_2[] = G_("initialization from pointer to "
				      "non-enclosed address space");
		اگر (warnopt)
		  diagnosed = warning_at (location, warnopt, پیغام_2);
		ورنہ
		  error_at (location, پیغام_2);
		توڑو;
	      }
	    حالت ic_return:
	      {
		ثابت حرف پیغام_2[] = G_("return from pointer to "
				      "non-enclosed address space");
		اگر (warnopt)
		  diagnosed = warning_at (location, warnopt, پیغام_2);
		ورنہ
		  error_at (location, پیغام_2);
		توڑو;
	      }
	    طےشدہ:
	      gcc_unreachable ();
	    }
	  اگر (diagnosed)
	    {
	      اگر (errtype == ic_argpass)
		inform_for_arg (fundecl, اظہاریہ_loc, parmnum, type, rhstype);
	      ورنہ
		inform (location, "expected %qT but pointer is of type %qT",
			type, rhstype);
	    }
	  واپس error_mark_گرہ;
	}

      /* Check if the right-hand side has a format attribute but the
	 left-hand side doesn't.  */
      اگر (warn_suggest_attribute_format
	  && check_missing_format_attribute (type, rhstype))
	{
	  انتخاب (errtype)
	  {
	  حالت ic_argpass:
	    warning_at (اظہاریہ_loc, OPT_Wsuggest_attribute_format,
			"argument %d of %qE might be "
			"a candidate for a format attribute",
			parmnum, rname);
	    توڑو;
	  حالت ic_تفویض:
	    warning_at (location, OPT_Wsuggest_attribute_format,
			"assignment left-hand side might be "
			"a candidate for a format attribute");
	    توڑو;
	  حالت ic_init:
	  حالت ic_init_const:
	    warning_at (location, OPT_Wsuggest_attribute_format,
			"initialization left-hand side might be "
			"a candidate for a format attribute");
	    توڑو;
	  حالت ic_return:
	    warning_at (location, OPT_Wsuggest_attribute_format,
			"return type might be "
			"a candidate for a format attribute");
	    توڑو;
	  طےشدہ:
	    gcc_unreachable ();
	  }
	}

      /* See if the pointers point to incompatible scalar storage orders.  */
      اگر (warn_scalar_storage_ترتیب
	  && !null_اشارہ_گر_constant_p (rhs)
	  && (AGGREGATE_TYPE_P (ttl) && TYPE_الٹ_STORAGE_ترتیب (ttl))
	     != (AGGREGATE_TYPE_P (ttr) && TYPE_الٹ_STORAGE_ترتیب (ttr)))
	{
	  درخت t;

	  انتخاب (errtype)
	  {
	  حالت ic_argpass:
	    /* Do not warn for built-in functions, for example memcpy, since we
	       control how they behave and they can be useful in this area.  */
	    اگر (درخت_رمز (rname) != FUNCTION_DECL
		|| !fndecl_built_اندر_p (rname))
	      warning_at (location, OPT_Wscalar_storage_ترتیب,
			  "passing argument %d of %qE from incompatible "
			  "scalar storage order", parmnum, rname);
	    توڑو;
	  حالت ic_تفویض:
	    /* Do not warn if the RHS is a call to a function that returns a
	       pointer that is not an alias.  */
	    اگر (درخت_رمز (rhs) != CALL_اظہاریہ
		|| (t = get_callee_fndecl (rhs)) == NULL_درخت
		|| !DECL_IS_MALLOC (t))
	      warning_at (location, OPT_Wscalar_storage_ترتیب,
			  "assignment to %qT from pointer type %qT with "
			  "incompatible scalar storage order", type, rhstype);
	    توڑو;
	  حالت ic_init:
	  حالت ic_init_const:
	    /* Likewise.  */
	    اگر (درخت_رمز (rhs) != CALL_اظہاریہ
		|| (t = get_callee_fndecl (rhs)) == NULL_درخت
		|| !DECL_IS_MALLOC (t))
	      warning_at (location, OPT_Wscalar_storage_ترتیب,
			  "initialization of %qT from pointer type %qT with "
			  "incompatible scalar storage order", type, rhstype);
	    توڑو;
	  حالت ic_return:
	    warning_at (location, OPT_Wscalar_storage_ترتیب,
			"returning %qT from pointer type with incompatible "
			"scalar storage order %qT", rhstype, type);
	    توڑو;
	  طےشدہ:
	    gcc_unreachable ();
	  }
	}

      /* Any non-function converts to a [const][volatile] void *
	 and vice versa; otherwise, targets must be the same.
	 Meanwhile, the lhs target must have all the qualifiers of the rhs.  */
      اگر ((VOID_TYPE_P (ttl) && !TYPE_ATOMIC (ttl))
	  || (VOID_TYPE_P (ttr) && !TYPE_ATOMIC (ttr))
	  || (ہدف_cmp = comp_ہدف_types (location, type, rhstype))
	  || is_opaque_اشارہ_گر
	  || ((c_common_unsigned_type (mvl)
	       == c_common_unsigned_type (mvr))
	      && (c_common_signed_type (mvl)
		  == c_common_signed_type (mvr))
	      && TYPE_ATOMIC (mvl) == TYPE_ATOMIC (mvr)))
	{
	  /* Warn about loss of qualifers from pointers to arrays with
	     qualifiers on the element type. */
	  اگر (درخت_رمز (ttr) == ARRAY_TYPE)
	    {
	      ttr = strip_array_types (ttr);
	      ttl = strip_array_types (ttl);

	      اگر (TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttr)
		  & ~TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttl))
		WARNING_FOR_QUALIFIERS (flag_isoc23,
					location, اظہاریہ_loc,
					OPT_Wdiscarded_array_qualifiers,
					G_("passing argument %d of %qE discards "
					   "%qv qualifier from pointer target type"),
					G_("assignment discards %qv qualifier "
					   "from pointer target type"),
					G_("initialization discards %qv qualifier "
					   "from pointer target type"),
					G_("return discards %qv qualifier from "
					   "pointer target type"),
					TYPE_QUALS (ttr) & ~TYPE_QUALS (ttl));
            }
          ورنہ اگر (pedantic
	      && ((VOID_TYPE_P (ttl) && درخت_رمز (ttr) == FUNCTION_TYPE)
		  ||
		  (VOID_TYPE_P (ttr)
		   && !null_اشارہ_گر_constant
		   && درخت_رمز (ttl) == FUNCTION_TYPE)))
	    PEDWARN_FOR_ASSIGNMENT (location, اظہاریہ_loc, OPT_Wpedantic,
				    G_("ISO C forbids passing argument %d of "
				       "%qE between function pointer "
				       "and %<void *%>"),
				    G_("ISO C forbids assignment between "
				       "function pointer and %<void *%>"),
				    G_("ISO C forbids initialization between "
				       "function pointer and %<void *%>"),
				    G_("ISO C forbids return between function "
				       "pointer and %<void *%>"));
	  /* Const and volatile mean something different for function types,
	     so the usual warnings are not appropriate.  */
	  ورنہ اگر (درخت_رمز (ttr) != FUNCTION_TYPE
		   && درخت_رمز (ttl) != FUNCTION_TYPE)
	    {
	       /* Assignments between atomic and non-atomic objects are OK.  */
	       منطقی warn_quals_ped = TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttr)
				     & ~TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttl);
	       منطقی warn_quals = TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttr)
				 & ~TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (strip_array_types (ttl));

	      /* Don't warn about loss of qualifier for conversions from
		 qualified void* to pointers to arrays with corresponding
		 qualifier on the element type (except for pedantic before C23). */
	      اگر (warn_quals || (warn_quals_ped && pedantic && !flag_isoc23))
		PEDWARN_FOR_QUALIFIERS (location, اظہاریہ_loc,
					OPT_Wdiscarded_qualifiers,
					G_("passing argument %d of %qE discards "
					   "%qv qualifier from pointer target type"),
					G_("assignment discards %qv qualifier "
					   "from pointer target type"),
					G_("initialization discards %qv qualifier "
					   "from pointer target type"),
					G_("return discards %qv qualifier from "
					   "pointer target type"),
					TYPE_QUALS (ttr) & ~TYPE_QUALS (ttl));
	      ورنہ اگر (warn_quals_ped)
		pedwarn_c11 (location, OPT_Wc11_c23_compat,
			     "array with qualifier on the element is not qualified before C23");

	      /* If this is not a case of ignoring a mismatch in signedness,
		 no warning.  */
	      ورنہ اگر (VOID_TYPE_P (ttl) || VOID_TYPE_P (ttr)
		       || ہدف_cmp)
		;
	      /* If there is a mismatch, do warn.  */
	      ورنہ اگر (warn_اشارہ_گر_sign)
		انتخاب (errtype)
		  {
		  حالت ic_argpass:
		    {
		      auto_diagnostic_گروہ d;
		      range_label_for_type_mismatch rhs_label (rhstype, type);
		      gcc_rich_location richloc (اظہاریہ_loc, &rhs_label,
						 highlight_colors::actual);
		      اگر (pedwarn (&richloc, OPT_Wpointer_sign,
				   "pointer targets in passing argument %d of "
				   "%qE differ in signedness", parmnum, rname))
			inform_for_arg (fundecl, اظہاریہ_loc, parmnum, type,
					rhstype);
		    }
		    توڑو;
		  حالت ic_تفویض:
		    pedwarn (location, OPT_Wpointer_sign,
			     "pointer targets in assignment from %qT to %qT "
			     "differ in signedness", rhstype, type);
		    توڑو;
		  حالت ic_init:
		  حالت ic_init_const:
		    pedwarn_init (location, OPT_Wpointer_sign,
				  "pointer targets in initialization of %qT "
				  "from %qT differ in signedness", type,
				  rhstype);
		    توڑو;
		  حالت ic_return:
		    pedwarn (location, OPT_Wpointer_sign, "pointer targets in "
			     "returning %qT from a function with return type "
			     "%qT differ in signedness", rhstype, type);
		    توڑو;
		  طےشدہ:
		    gcc_unreachable ();
		  }
	    }
	  ورنہ اگر (درخت_رمز (ttl) == FUNCTION_TYPE
		   && درخت_رمز (ttr) == FUNCTION_TYPE)
	    {
	      /* Because const and volatile on functions are restrictions
		 that say the function will not do certain things,
		 it is okay to use a const or volatile function
		 where an ordinary one is wanted, but not vice-versa.  */
	      اگر (TYPE_QUALS_NO_ADDR_SPACE (ttl)
		  & ~TYPE_QUALS_NO_ADDR_SPACE (ttr))
		PEDWARN_FOR_QUALIFIERS (location, اظہاریہ_loc,
				        OPT_Wdiscarded_qualifiers,
				        G_("passing argument %d of %qE makes "
					   "%q#v qualified function pointer "
					   "from unqualified"),
				        G_("assignment makes %q#v qualified function "
					   "pointer from unqualified"),
				        G_("initialization makes %q#v qualified "
					   "function pointer from unqualified"),
				        G_("return makes %q#v qualified function "
					   "pointer from unqualified"),
				        TYPE_QUALS (ttl) & ~TYPE_QUALS (ttr));
	    }
	}
      /* Avoid warning about the volatile ObjC EH puts on decls.  */
      ورنہ اگر (!objc_ok)
	{
	  auto_diagnostic_گروہ d;
	  منطقی warned = جھوٹ;
	  pp_markup::element_expected_type e_type (type);
	  pp_markup::element_actual_type e_rhstype (rhstype);
	  انتخاب (errtype)
	    {
	    حالت ic_argpass:
	      {
		range_label_for_type_mismatch rhs_label (rhstype, type);
		gcc_rich_location richloc (اظہاریہ_loc, &rhs_label,
					   highlight_colors::actual);
		warned
		  = permerror_opt (&richloc, OPT_Wincompatible_اشارہ_گر_types,
				   "passing argument %d of %qE from "
				   "incompatible pointer type",
				   parmnum, rname);
		اگر (warned)
		  inform_for_arg (fundecl, اظہاریہ_loc, parmnum, type, rhstype);
	      }
	      توڑو;
	    حالت ic_تفویض:
	      اگر (bltin)
		warned
		  = permerror_opt (location, OPT_Wincompatible_اشارہ_گر_types,
				   "assignment to %e from pointer to "
				   "%qD with incompatible type %e",
				   &e_type, bltin, &e_rhstype);
	      ورنہ
		warned
		  = permerror_opt (location, OPT_Wincompatible_اشارہ_گر_types,
				   "assignment to %e from incompatible "
				   "pointer type %e",
				   &e_type, &e_rhstype);
	      توڑو;
	    حالت ic_init:
	    حالت ic_init_const:
	      اگر (bltin)
		warned
		  = permerror_init (location, OPT_Wincompatible_اشارہ_گر_types,
				    "initialization of %e from pointer to "
				    "%qD with incompatible type %e",
				    &e_type, bltin, &e_rhstype);
	      ورنہ
		warned
		  = permerror_init (location, OPT_Wincompatible_اشارہ_گر_types,
				    "initialization of %e from incompatible "
				    "pointer type %e",
				    &e_type, &e_rhstype);
	      توڑو;
	    حالت ic_return:
	      اگر (bltin)
		warned
		  = permerror_opt (location, OPT_Wincompatible_اشارہ_گر_types,
				   "returning pointer to %qD of type %e from "
				   "a function with incompatible type %e",
				   bltin, &e_rhstype, &e_type);
	      ورنہ
		warned
		  = permerror_opt (location, OPT_Wincompatible_اشارہ_گر_types,
				   "returning %e from a function with "
				   "incompatible return type %e",
				   &e_rhstype, &e_type);
	      توڑو;
	    طےشدہ:
	      gcc_unreachable ();
	    }
	  اگر (warned)
	    {
	      /* If the mismatching function type is a pointer to a function,
		 try to show the decl of the function.  */
	      اگر (درخت_رمز (rhs) == ADDR_اظہاریہ
		  && درخت_رمز (درخت_عملیہ (rhs, 0)) == FUNCTION_DECL)
		{
		  درخت rhs_fndecl = درخت_عملیہ (rhs, 0);
		  اگر (!DECL_IS_UNDECLARED_BUILTIN (rhs_fndecl))
		    {
		      gcc_rich_location richloc
			(DECL_ماخذ_LOCATION (rhs_fndecl), خالی_اشاریہ,
			 highlight_colors::actual);
		      pp_element_quoted_decl e_rhs_fndecl
			(rhs_fndecl, highlight_colors::actual);
		      inform (&richloc,
			      "%e declared here", &e_rhs_fndecl);
		    }
		}
	      /* If either/both of the types are typedefs, show the decl.  */
	      maybe_inform_typedef_location (type,
					     highlight_colors::expected);
	      maybe_inform_typedef_location (rhstype,
					     highlight_colors::actual);
	    }
	}

      /* If RHS isn't an address, check pointer or array of packed
	 struct or union.  */
      warn_for_پتہ_کا_packed_member (type, orig_rhs);

      واپس convert (type, rhs);
    }
  ورنہ اگر (codel == اشارہ_گر_TYPE && coder == ARRAY_TYPE)
    {
      /* ??? This should not be an error when inlining calls to
	 unprototyped functions.  */
      ثابت حرف پیغام_2[] = "invalid use of non-lvalue array";
      اگر (warnopt)
	warning_at (location, warnopt, پیغام_2);
      ورنہ
	error_at (location, پیغام_2);
      واپس error_mark_گرہ;
    }
  ورنہ اگر (codel == اشارہ_گر_TYPE
	   && (coder == INTEGER_TYPE
	       || coder == ENUMERAL_TYPE
	       || coder == BOOLEAN_TYPE
	       || coder == NULLPTR_TYPE
	       || coder == BITINT_TYPE))
    {
      اگر (null_اشارہ_گر_constant && c_inhibit_evaluation_warnings == 0
	  && coder != NULLPTR_TYPE)
	warning_at (location, OPT_Wzero_as_null_اشارہ_گر_constant,
		    "zero as null pointer constant");
      /* A NULLPTR type is just a nullptr always.  */
      اگر (coder == NULLPTR_TYPE)
	واپس omit_one_عملیہ_loc (اظہاریہ_loc, type, nullptr_گرہ, rhs);
      /* An explicit constant 0 or type nullptr_t can convert to a pointer,
	 or one that results from arithmetic, even including a cast to
	 integer type.  */
      ورنہ اگر (!null_اشارہ_گر_constant)
	انتخاب (errtype)
	  {
	  حالت ic_argpass:
	    {
	      auto_diagnostic_گروہ d;
	      range_label_for_type_mismatch rhs_label (rhstype, type);
	      gcc_rich_location richloc (اظہاریہ_loc, &rhs_label,
					 highlight_colors::actual);
	      اگر (permerror_opt (&richloc, OPT_Wint_conversion,
				 "passing argument %d of %qE makes pointer "
				 "from integer without a cast", parmnum, rname))
		{
		  maybe_emit_indirection_note (اظہاریہ_loc, rhs, type);
		  inform_for_arg (fundecl, اظہاریہ_loc, parmnum, type, rhstype);
		}
	    }
	    توڑو;
	  حالت ic_تفویض:
	    permerror_opt (location, OPT_Wint_conversion,
			   "assignment to %qT from %qT makes pointer from "
			   "integer without a cast", type, rhstype);
	    توڑو;
	  حالت ic_init:
	  حالت ic_init_const:
	    permerror_init (location, OPT_Wint_conversion,
			    "initialization of %qT from %qT makes pointer "
			    "from integer without a cast", type, rhstype);
	    توڑو;
	  حالت ic_return:
	    permerror_init (location, OPT_Wint_conversion,
			    "returning %qT from a function with return type "
			    "%qT makes pointer from integer without a cast",
			    rhstype, type);
	    توڑو;
	  طےشدہ:
	    gcc_unreachable ();
	  }

      واپس convert (type, rhs);
    }
  ورنہ اگر ((codel == INTEGER_TYPE || codel == BITINT_TYPE)
	   && coder == اشارہ_گر_TYPE)
    {
      انتخاب (errtype)
	{
	حالت ic_argpass:
	  {
	    auto_diagnostic_گروہ d;
	    range_label_for_type_mismatch rhs_label (rhstype, type);
	    gcc_rich_location richloc (اظہاریہ_loc, &rhs_label,
				       highlight_colors::actual);
	    اگر (permerror_opt (&richloc, OPT_Wint_conversion,
			       "passing argument %d of %qE makes integer from "
			       "pointer without a cast", parmnum, rname))
	      {
		maybe_emit_indirection_note (اظہاریہ_loc, rhs, type);
		inform_for_arg (fundecl, اظہاریہ_loc, parmnum, type, rhstype);
	      }
	  }
	  توڑو;
	حالت ic_تفویض:
	  permerror_opt (location, OPT_Wint_conversion,
			 "assignment to %qT from %qT makes integer from "
			 "pointer without a cast", type, rhstype);
	  توڑو;
	حالت ic_init:
	حالت ic_init_const:
	  permerror_init (location, OPT_Wint_conversion,
			  "initialization of %qT from %qT makes integer "
			  "from pointer without a cast", type, rhstype);
	  توڑو;
	حالت ic_return:
	  permerror_opt (location, OPT_Wint_conversion, "returning %qT from a "
			 "function with return type %qT makes integer from "
			 "pointer without a cast", rhstype, type);
	  توڑو;
	طےشدہ:
	  gcc_unreachable ();
	}

      واپس convert (type, rhs);
    }
  ورنہ اگر (C_BOOLEAN_TYPE_P (type)
	   /* The type nullptr_t may be converted to bool.  The
	      result is false.  */
	   && (coder == اشارہ_گر_TYPE || coder == NULLPTR_TYPE))
    {
      درخت ret;
      منطقی save = اندر_late_ثنائی_op;
      اندر_late_ثنائی_op = سچ;
      ret = convert (type, rhs);
      اندر_late_ثنائی_op = save;
      واپس ret;
    }
  ورنہ اگر (codel == NULLPTR_TYPE && null_اشارہ_گر_constant)
    واپس convert (type, rhs);

  انتخاب (errtype)
    {
    حالت ic_argpass:
      {
	auto_diagnostic_گروہ d;
	range_label_for_type_mismatch rhs_label (rhstype, type);
	gcc_rich_location richloc (اظہاریہ_loc, &rhs_label,
				   highlight_colors::actual);
	ثابت حرف پیغام_2[] = G_("incompatible type for argument %d of %qE");
	اگر (warnopt)
	  warning_at (اظہاریہ_loc, warnopt, پیغام_2, parmnum, rname);
	ورنہ
	  error_at (&richloc, پیغام_2, parmnum, rname);
	inform_for_arg (fundecl, اظہاریہ_loc, parmnum, type, rhstype);
      }
      توڑو;
    حالت ic_تفویض:
      {
	ثابت حرف پیغام_2[]
	  = G_("incompatible types when assigning to type %qT from type %qT");
	اگر (warnopt)
	  warning_at (اظہاریہ_loc, 0, پیغام_2, type, rhstype);
	ورنہ
	  error_at (اظہاریہ_loc, پیغام_2, type, rhstype);
	توڑو;
      }
    حالت ic_init:
    حالت ic_init_const:
      {
	ثابت حرف پیغام_2[]
	  = G_("incompatible types when initializing type %qT using type %qT");
	اگر (warnopt)
	  warning_at (location, 0, پیغام_2, type, rhstype);
	ورنہ
	  error_at (location, پیغام_2, type, rhstype);
	توڑو;
      }
    حالت ic_return:
      {
	ثابت حرف پیغام_2[]
	  = G_("incompatible types when returning type %qT but %qT was expected");
	اگر (warnopt)
	  warning_at (location, 0, پیغام_2, rhstype, type);
	ورنہ
	  error_at (location, پیغام_2, rhstype, type);
	توڑو;
      }
    طےشدہ:
      gcc_unreachable ();
    }

  واپس error_mark_گرہ;
}

/* If VALUE is a compound expr all of whose expressions are constant, then
   return its value.  Otherwise, return error_mark_node.

   This is for handling COMPOUND_EXPRs as initializer elements
   which is allowed with a warning when -pedantic is specified.  */

ساکن درخت
valid_compound_اظہاریہ_initializer (درخت قدر, درخت endtype)
{
  اگر (درخت_رمز (قدر) == COMPOUND_اظہاریہ)
    {
      اگر (valid_compound_اظہاریہ_initializer (درخت_عملیہ (قدر, 0), endtype)
	  == error_mark_گرہ)
	واپس error_mark_گرہ;
      واپس valid_compound_اظہاریہ_initializer (درخت_عملیہ (قدر, 1),
					      endtype);
    }
  ورنہ اگر (!initializer_constant_valid_p (قدر, endtype))
    واپس error_mark_گرہ;
  ورنہ
    واپس قدر;
}

/* Perform appropriate conversions on the initial value of a variable,
   store it in the declaration DECL,
   and print any error messages that are appropriate.
   If ORIGTYPE is not NULL_TREE, it is the original type of INIT.
   If the init is invalid, store an ERROR_MARK.

   INIT_LOC is the location of the initial value.  */

خالی
store_init_قدر (location_t init_loc, درخت decl, درخت init, درخت origtype)
{
  درخت قدر, type;
  منطقی npc = جھوٹ;
  منطقی int_const_اظہاریہ = جھوٹ;
  منطقی arith_const_اظہاریہ = جھوٹ;

  /* If variable's type was invalidly declared, just ignore it.  */

  type = درخت_TYPE (decl);
  اگر (درخت_رمز (type) == ERROR_MARK)
    واپس;

  /* Digest the specified initializer into an expression.  */

  اگر (init)
    {
      npc = null_اشارہ_گر_constant_p (init);
      int_const_اظہاریہ = (درخت_رمز (init) == INTEGER_CST
			&& !درخت_حد_سے_تجاوز (init)
			&& INTEGRAL_TYPE_P (درخت_TYPE (init)));
      /* Not fully determined before folding.  */
      arith_const_اظہاریہ = سچ;
    }
  منطقی constexpr_p = (VAR_P (decl)
		      && C_DECL_DECLARED_CONSTEXPR (decl));
  قدر = digest_init (init_loc, decl, type, init, origtype, npc,
		       int_const_اظہاریہ, arith_const_اظہاریہ, سچ,
		       درخت_STATIC (decl) || constexpr_p, constexpr_p);

  /* Store the expression if valid; else report error.  */

  اگر (!اندر_system_سرخی_at (داخلہ_location)
      && AGGREGATE_TYPE_P (درخت_TYPE (decl)) && !درخت_STATIC (decl))
    warning (OPT_Wtraditional, "traditional C rejects automatic "
	     "aggregate initialization");

  اگر (قدر != error_mark_گرہ || درخت_رمز (decl) != FUNCTION_DECL)
    DECL_INITIAL (decl) = قدر;

  /* ANSI wants warnings about out-of-range constant initializers.  */
  STRIP_TYPE_NOPS (قدر);
  اگر (درخت_STATIC (decl))
    constant_عبارت_warning (قدر);

  /* Check if we need to set array size from compound literal size.  */
  اگر (درخت_رمز (type) == ARRAY_TYPE
      && TYPE_DOMAIN (type) == NULL_درخت
      && قدر != error_mark_گرہ)
    {
      درخت inside_init = init;

      STRIP_TYPE_NOPS (inside_init);
      inside_init = fold (inside_init);

      اگر (درخت_رمز (inside_init) == COMPOUND_LITERAL_اظہاریہ)
	{
	  درخت cldecl = COMPOUND_LITERAL_اظہاریہ_DECL (inside_init);

	  اگر (TYPE_DOMAIN (درخت_TYPE (cldecl)))
	    {
	      /* For int foo[] = (int [3]){1}; we need to set array size
		 now since later on array initializer will be just the
		 brace enclosed list of the compound literal.  */
	      درخت etype = strip_array_types (درخت_TYPE (decl));
	      type = build_distinct_type_copy (TYPE_MAIN_VARIANT (type));
	      TYPE_DOMAIN (type) = TYPE_DOMAIN (درخت_TYPE (cldecl));
	      layout_type (type);
	      layout_decl (cldecl, 0);
	      درخت_TYPE (decl)
		= c_build_qualified_type (type, TYPE_QUALS (etype));
	    }
	}
    }
}

/* Methods for storing and printing names for error messages.  */

/* Implement a spelling stack that allows components of a name to be pushed
   and popped.  Each element on the stack is this structure.  */

ساخت spelling
{
  صحیح قسم;
  اتحاد
    {
      غیرعلامتی HOST_WIDE_INT i;
      ثابت حرف *s;
    } u;
};

#تعریف_کرو SPELLING_STRING 1
#تعریف_کرو SPELLING_MEMBER 2
#تعریف_کرو SPELLING_BOUNDS 3

ساکن ساخت spelling *spelling;	/* Next stack element (unused).  */
ساکن ساخت spelling *spelling_بنیاد;	/* Spelling stack base.  */
ساکن صحیح spelling_سائز;		/* Size of the spelling stack.  */

/* Macros to save and restore the spelling stack around push_... functions.
   Alternative to SAVE_SPELLING_STACK.  */

#تعریف_کرو SPELLING_گہرائی() (spelling - spelling_بنیاد)
#تعریف_کرو RESTORE_SPELLING_گہرائی(گہرائی_2) (spelling = spelling_بنیاد + (گہرائی_2))

/* Push an element on the spelling stack with type KIND and assign VALUE
   to MEMBER.  */

#تعریف_کرو ڈالو_SPELLING(قسم_2, قدر_2, MEMBER)				\
{									\
  صحیح گہرائی = SPELLING_گہرائی ();					\
									\
  اگر (گہرائی >= spelling_سائز)						\
    {									\
      spelling_سائز += 10;						\
      spelling_بنیاد = XRESIZEVEC (ساخت spelling, spelling_بنیاد,	\
				  spelling_سائز);			\
      RESTORE_SPELLING_گہرائی (گہرائی);					\
    }									\
									\
  spelling->قسم = (قسم_2);						\
  spelling->MEMBER = (قدر_2);						\
  spelling++;								\
}

/* Push STRING on the stack.  Printed literally.  */

ساکن خالی
ڈالو_string (ثابت حرف *string)
{
  ڈالو_SPELLING (SPELLING_STRING, string, u.s);
}

/* Push a member name on the stack.  Printed as '.' STRING.  */

ساکن خالی
ڈالو_member_name (درخت decl)
{
  ثابت حرف *ثابت string
    = (DECL_NAME (decl)
       ? identifier_مقصد_locale (IDENTIFIER_اشارہ_گر (DECL_NAME (decl)))
       : _("<anonymous>"));
  ڈالو_SPELLING (SPELLING_MEMBER, string, u.s);
}

/* Push an array bounds on the stack.  Printed as [BOUNDS].  */

ساکن خالی
ڈالو_array_bounds (غیرعلامتی HOST_WIDE_INT bounds)
{
  ڈالو_SPELLING (SPELLING_BOUNDS, bounds, u.i);
}

/* Compute the maximum size in bytes of the printed spelling.  */

ساکن صحیح
spelling_لمبائی (خالی)
{
  صحیح سائز = 0;
  ساخت spelling *p;

  برائے (p = spelling_بنیاد; p < spelling; p++)
    {
      اگر (p->قسم == SPELLING_BOUNDS)
	سائز += 25;
      ورنہ
	سائز += لڑی_لمبائی (p->u.s) + 1;
    }

  واپس سائز;
}

/* Print the spelling to BUFFER and return it.  */

ساکن حرف *
print_spelling (حرف *بفر)
{
  حرف *d = بفر;
  ساخت spelling *p;

  برائے (p = spelling_بنیاد; p < spelling; p++)
    اگر (p->قسم == SPELLING_BOUNDS)
      {
	sprintf (d, "[" HOST_WIDE_INT_PRINT_UNSIGNED "]", p->u.i);
	d += لڑی_لمبائی (d);
      }
    ورنہ
      {
	ثابت حرف *s;
	اگر (p->قسم == SPELLING_MEMBER)
	  *d++ = '.';
	برائے (s = p->u.s; (*d = *s++); d++)
	  ;
      }
  *d++ = '\0';
  واپس بفر;
}

/* Check whether INIT, a floating or integer constant, is
   representable in TYPE, a real floating type with the same radix or
   a decimal floating type initialized with a binary floating
   constant.  Return true if OK, false if not.  */
ساکن منطقی
constexpr_init_سماتا_real_type (درخت type, درخت init)
{
  gcc_assert (SCALAR_FLOAT_TYPE_P (type));
  gcc_assert (درخت_رمز (init) == INTEGER_CST || درخت_رمز (init) == REAL_CST);
  اگر (درخت_رمز (init) == REAL_CST
      && TYPE_منوال (درخت_TYPE (init)) == TYPE_منوال (type))
    {
      /* Same mode, no conversion required except for the case of
	 signaling NaNs if the types are incompatible (e.g. double and
	 long double with the same mode).  */
      اگر (REAL_قدر_ISSIGNALING_NAN (درخت_REAL_CST (init))
	  && !comptypes (TYPE_MAIN_VARIANT (type),
			 TYPE_MAIN_VARIANT (درخت_TYPE (init))))
	واپس جھوٹ;
      واپس سچ;
    }
  اگر (درخت_رمز (init) == INTEGER_CST)
    {
      درخت converted = build_real_from_int_cst (type, init);
      منطقی fail = جھوٹ;
      wide_int w = real_مقصد_integer (&درخت_REAL_CST (converted), &fail,
				    TYPE_PRECISION (درخت_TYPE (init)));
      واپس !fail && wi::eq_p (w, wi::مقصد_wide (init));
    }
  اگر (REAL_قدر_ISSIGNALING_NAN (درخت_REAL_CST (init)))
    واپس جھوٹ;
  اگر ((REAL_قدر_ISINF (درخت_REAL_CST (init))
       && منوال_HAS_INFINITIES (TYPE_منوال (type)))
      || (REAL_قدر_ISNAN (درخت_REAL_CST (init))
	  && منوال_HAS_NANS (TYPE_منوال (type))))
    واپس سچ;
  اگر (DECIMAL_FLOAT_TYPE_P (type)
      && !DECIMAL_FLOAT_TYPE_P (درخت_TYPE (init)))
    {
      /* This is valid if the real number represented by the
	 initializer can be exactly represented in the decimal
	 type.  Compare the values using MPFR.  */
      REAL_قدر_TYPE t;
      real_convert (&t, TYPE_منوال (type), &درخت_REAL_CST (init));
      mpfr_t bin_val, dec_val;
      mpfr_init2 (bin_val, REAL_منوال_FORMAT (TYPE_منوال (درخت_TYPE (init)))->p);
      mpfr_init2 (dec_val, REAL_منوال_FORMAT (TYPE_منوال (درخت_TYPE (init)))->p);
      mpfr_from_real (bin_val, &درخت_REAL_CST (init), MPFR_RNDN);
      حرف string[256];
      real_مقصد_decimal (string, &t, حجم string, 0, 1);
      منطقی res = (mpfr_strtofr (dec_val, string, تہی, 10, MPFR_RNDN) == 0
		  && mpfr_equal_p (bin_val, dec_val));
      mpfr_clear (bin_val);
      mpfr_clear (dec_val);
      واپس res;
    }
  /* exact_real_truncate is not quite right here, since it doesn't
     allow even an exact conversion to subnormal values.  */
  REAL_قدر_TYPE t;
  real_convert (&t, TYPE_منوال (type), &درخت_REAL_CST (init));
  واپس real_identical (&t, &درخت_REAL_CST (init));
}

/* Check whether INIT (location LOC) is valid as a 'constexpr'
   initializer for type TYPE, and give an error if not.  INIT has
   already been folded and verified to be constant.  INT_CONST_EXPR
   and ARITH_CONST_EXPR say whether it is an integer constant
   expression or arithmetic constant expression, respectively.  If
   TYPE is not a scalar type, this function does nothing.  */

ساکن خالی
check_constexpr_init (location_t loc, درخت type, درخت init,
		      منطقی int_const_اظہاریہ, منطقی arith_const_اظہاریہ)
{
  اگر (اشارہ_گر_TYPE_P (type))
    {
      /* The initializer must be null.  */
      اگر (درخت_رمز (init) != INTEGER_CST || !integer_zerop (init))
	error_at (loc, "%<constexpr%> pointer initializer is not null");
      واپس;
    }
  اگر (INTEGRAL_TYPE_P (type))
    {
      /* The initializer must be an integer constant expression,
	 representable in the target type.  */
      اگر (!int_const_اظہاریہ)
	{
	  اگر (درخت_رمز (init) == RAW_ڈیٹا_CST
	      && TYPE_PRECISION (type) == CHAR_ثنائی_ہندسہ)
	    {
	      اگر (!TYPE_UNSIGNED (type))
		برائے (غیرعلامتی صحیح i = 0;
		     i < (غیرعلامتی) RAW_ڈیٹا_لمبائی (init); ++i)
		  اگر (RAW_ڈیٹا_SCHAR_ELT (init, i) < 0)
		    {
		      error_at (loc, "%<constexpr%> initializer not "
				"representable in type of object");
		      توڑو;
		    }
	    }
	  ورنہ
	    error_at (loc, "%<constexpr%> integer initializer is not an "
		      "integer constant expression");
	}
      ورنہ اگر (!int_سماتا_type_p (init, type))
	error_at (loc, "%<constexpr%> initializer not representable in "
		  "type of object");
      واپس;
    }
  /* We don't apply any extra checks to extension types such as vector
     or fixed-point types.  */
  اگر (درخت_رمز (type) != REAL_TYPE && درخت_رمز (type) != COMPLEX_TYPE)
    واپس;
  اگر (!arith_const_اظہاریہ)
    {
      error_at (loc, "%<constexpr%> initializer is not an arithmetic "
		"constant expression");
      واپس;
    }
  /* We don't apply any extra checks to complex integers.  */
  اگر (درخت_رمز (type) == COMPLEX_TYPE
      && درخت_رمز (درخت_TYPE (type)) != REAL_TYPE)
    واپس;
  /* Following N3082, a real type cannot be initialized from a complex
     type and a binary type cannot be initialized from a decimal type
     (but initializing a decimal type from a binary type is OK).
     Signaling NaN initializers are OK only if the types are
     compatible (not just the same mode); all quiet NaN and infinity
     initializations are considered to preserve the value.  */
  اگر (درخت_رمز (درخت_TYPE (init)) == COMPLEX_TYPE
      && SCALAR_FLOAT_TYPE_P (type))
    {
      error_at (loc, "%<constexpr%> initializer for a real type is of "
		"complex type");
      واپس;
    }
  اگر (SCALAR_FLOAT_TYPE_P (type)
      && SCALAR_FLOAT_TYPE_P (درخت_TYPE (init))
      && DECIMAL_FLOAT_TYPE_P (درخت_TYPE (init))
      && !DECIMAL_FLOAT_TYPE_P (type))
    {
      error_at (loc, "%<constexpr%> initializer for a binary "
		"floating-point type is of decimal type");
      واپس;
    }
  منطقی سماتا;
  اگر (درخت_رمز (type) == COMPLEX_TYPE)
    {
      انتخاب (درخت_رمز (init))
	{
	حالت INTEGER_CST:
	حالت REAL_CST:
	  سماتا = constexpr_init_سماتا_real_type (درخت_TYPE (type), init);
	  توڑو;
	حالت COMPLEX_CST:
	  سماتا = (constexpr_init_سماتا_real_type (درخت_TYPE (type),
						 درخت_REALPART (init))
		  && constexpr_init_سماتا_real_type (درخت_TYPE (type),
						    درخت_IMAGPART (init)));
	  توڑو;
	طےشدہ:
	  gcc_unreachable ();
	}
    }
  ورنہ
    سماتا = constexpr_init_سماتا_real_type (type, init);
  اگر (!سماتا)
    error_at (loc, "%<constexpr%> initializer not representable in "
	      "type of object");
}

/* Digest the parser output INIT as an initializer for type TYPE
   initializing DECL.
   Return a C expression of type TYPE to represent the initial value.

   If ORIGTYPE is not NULL_TREE, it is the original type of INIT.

   NULL_POINTER_CONSTANT is true if INIT is a null pointer constant,
   INT_CONST_EXPR is true if INIT is an integer constant expression,
   and ARITH_CONST_EXPR is true if INIT is, or might be, an arithmetic
   constant expression, false if it has already been determined in the
   caller that it is not (but folding may have made the value passed here
   indistinguishable from an arithmetic constant expression).

   If INIT is a string constant, STRICT_STRING is true if it is
   unparenthesized or we should not warn here for it being parenthesized.
   For other types of INIT, STRICT_STRING is not used.

   INIT_LOC is the location of the INIT.

   REQUIRE_CONSTANT requests an error if non-constant initializers or
   elements are seen.  REQUIRE_CONSTEXPR means the stricter requirements
   on initializers for 'constexpr' objects apply.  */

ساکن درخت
digest_init (location_t init_loc, درخت decl, درخت type, درخت init,
	     درخت origtype, منطقی null_اشارہ_گر_constant, منطقی int_const_اظہاریہ,
	     منطقی arith_const_اظہاریہ, منطقی strict_string,
	     منطقی require_constant, منطقی require_constexpr)
{
  شمار درخت_رمز_2 رمز = درخت_رمز (type);
  درخت inside_init = init;
  درخت semantic_type = NULL_درخت;
  منطقی maybe_const = سچ;

  اگر (type == error_mark_گرہ
      || !init
      || error_عملیہ_p (init))
    واپس error_mark_گرہ;

  STRIP_TYPE_NOPS (inside_init);

  /* If require_constant is TRUE,  when the initializer is a call to
     .ACCESS_WITH_SIZE, use the first argument as the initializer.
     For example:
     y = (char *) .ACCESS_WITH_SIZE ((char *) &static_annotated.c,...)
     will be converted to
     y = &static_annotated.c.  */

  اگر (require_constant
      && درخت_رمز (inside_init) == NOP_اظہاریہ
      && درخت_رمز (درخت_عملیہ (inside_init, 0)) == CALL_اظہاریہ
      && is_access_with_سائز_p (درخت_عملیہ (inside_init, 0)))
    inside_init
      = get_ref_from_access_with_سائز (درخت_عملیہ (inside_init, 0));

  اگر (!c_اندر_omp_for)
    {
      اگر (درخت_رمز (inside_init) == EXCESS_PRECISION_اظہاریہ)
	{
	  semantic_type = درخت_TYPE (inside_init);
	  inside_init = درخت_عملیہ (inside_init, 0);
	}
      inside_init = c_fully_fold (inside_init, require_constant, &maybe_const);
    }
  /* TODO: this may not detect all cases of expressions folding to
     constants that are not arithmetic constant expressions.  */
  اگر (!maybe_const)
    arith_const_اظہاریہ = جھوٹ;
  ورنہ اگر (!INTEGRAL_TYPE_P (درخت_TYPE (inside_init))
	   && درخت_رمز (درخت_TYPE (inside_init)) != REAL_TYPE
	   && درخت_رمز (درخت_TYPE (inside_init)) != COMPLEX_TYPE)
    arith_const_اظہاریہ = جھوٹ;
  ورنہ اگر (درخت_رمز (inside_init) != INTEGER_CST
	   && درخت_رمز (inside_init) != REAL_CST
	   && درخت_رمز (inside_init) != COMPLEX_CST
	   && درخت_رمز (inside_init) != RAW_ڈیٹا_CST)
    arith_const_اظہاریہ = جھوٹ;
  ورنہ اگر (درخت_حد_سے_تجاوز (inside_init))
    arith_const_اظہاریہ = جھوٹ;

  /* Initialization of an array of chars from a string constant
     optionally enclosed in braces.  */

  اگر (رمز == ARRAY_TYPE && inside_init
      && درخت_رمز (inside_init) == STRING_CST)
    {
      درخت typ1
	= (TYPE_ATOMIC (درخت_TYPE (type))
	   ? c_build_qualified_type (TYPE_MAIN_VARIANT (درخت_TYPE (type)),
				     TYPE_QUAL_ATOMIC)
	   : TYPE_MAIN_VARIANT (درخت_TYPE (type)));
      /* Note that an array could be both an array of character type
	 and an array of wchar_t if wchar_t is signed char or unsigned
	 char.  */
      منطقی char_array = (typ1 == char_type_گرہ
			 || typ1 == signed_char_type_گرہ
			 || typ1 == unsigned_char_type_گرہ);
      منطقی wchar_array = comptypes (typ1, wchar_type_گرہ);
      منطقی char16_array = comptypes (typ1, char16_type_گرہ);
      منطقی char32_array = comptypes (typ1, char32_type_گرہ);

      اگر (char_array || wchar_array || char16_array || char32_array)
	{
	  ساخت c_اظہاریہ اظہاریہ;
	  درخت typ2 = TYPE_MAIN_VARIANT (درخت_TYPE (درخت_TYPE (inside_init)));
	  منطقی incompat_string_cst = جھوٹ;
	  اظہاریہ.قدر = inside_init;
	  اظہاریہ.original_رمز = (strict_string ? STRING_CST : ERROR_MARK);
	  اظہاریہ.original_type = تہی;
	  اظہاریہ.m_decimal = 0;
	  maybe_warn_string_init (init_loc, type, اظہاریہ);

	  اگر (flexible_array_member_type_p (type))
	    pedwarn_init (init_loc, OPT_Wpedantic,
			  "initialization of a flexible array member");

	  اگر (comptypes (TYPE_MAIN_VARIANT (درخت_TYPE (inside_init)),
			 TYPE_MAIN_VARIANT (type)))
	    واپس inside_init;

	  اگر (char_array)
	    {
	      اگر (typ2 != char_type_گرہ && typ2 != char8_type_گرہ)
		incompat_string_cst = سچ;
	    }
	  ورنہ اگر (!comptypes (typ1, typ2))
	    incompat_string_cst = سچ;

          اگر (incompat_string_cst)
            {
	      error_init (init_loc, "cannot initialize array of %qT from "
			  "a string literal with type array of %qT",
			  typ1, typ2);
	      واپس error_mark_گرہ;
            }

	  اگر (require_constexpr
	      && TYPE_UNSIGNED (typ1) != TYPE_UNSIGNED (typ2))
	    {
	      /* Check if all characters of the string can be
		 represented in the type of the constexpr object being
		 initialized.  */
	      غیرعلامتی HOST_WIDE_INT len = درخت_STRING_لمبائی (inside_init);
	      ثابت غیرعلامتی حرف *p =
		(ثابت غیرعلامتی حرف *) درخت_STRING_اشارہ_گر (inside_init);
	      gcc_assert (CHAR_TYPE_سائز == 8 && CHAR_ثنائی_ہندسہ == 8);
	      برائے (غیرعلامتی i = 0; i < len; i++)
		اگر (p[i] > 127)
		  {
		    error_init (init_loc, "%<constexpr%> initializer not "
				"representable in type of object");
		    توڑو;
		  }
	    }

	  اگر (TYPE_DOMAIN (type) != NULL_درخت
	      && TYPE_سائز (type) != NULL_درخت
	      && درخت_رمز (TYPE_سائز (type)) == INTEGER_CST)
	    {
	      غیرعلامتی HOST_WIDE_INT len = درخت_STRING_لمبائی (inside_init);

	      اگر (compare_درخت_int (TYPE_سائز_UNIT (type), len) < 0)
		{
		  غیرعلامتی HOST_WIDE_INT avail
		    = درخت_مقصد_uhwi (TYPE_سائز_UNIT (type));
		  غیرعلامتی unit = TYPE_PRECISION (typ1) / بٹ_فی_UNIT;
		  ثابت حرف *p = درخت_STRING_اشارہ_گر (inside_init);

		  /* Construct truncated string.  */
		  inside_init = build_string (avail, p);

		  /* Subtract the size of a single (possibly wide) character
		     because it may be ok to ignore the terminating NUL char
		     that is counted in the length of the constant.  */
		  اگر (len - unit > avail)
		    pedwarn_init (init_loc, 0,
				  "initializer-string for array of %qT "
				  "is too long (%wu chars into %wu "
				  "available)", typ1, len, avail);
		  ورنہ اگر (warn_cxx_compat)
		    warning_at (init_loc, OPT_Wc___compat,
				"initializer-string for array of %qT "
				"is too long for C++ (%wu chars into %wu "
				"available)", typ1, len, avail);
		  ورنہ اگر (warn_unterminated_string_initialization
			   && get_attr_nonstring_decl (decl) == NULL_درخت)
		    warning_at (init_loc,
				OPT_Wunterminated_string_initialization,
				"initializer-string for array of %qT "
				"truncates NUL terminator but destination "
				"lacks %qs attribute (%wu chars into %wu "
				"available)", typ1, "nonstring", len, avail);
		}
	    }

	  درخت_TYPE (inside_init) = type;
	  واپس inside_init;
	}
      ورنہ اگر (INTEGRAL_TYPE_P (typ1))
	{
	  error_init (init_loc, "array of inappropriate type initialized "
		      "from string constant");
	  واپس error_mark_گرہ;
	}
    }

  /* Build a VECTOR_CST from a *constant* vector constructor.  If the
     vector constructor is not constant (e.g. {1,2,3,foo()}) then punt
     below and handle as a constructor.  */
  اگر (رمز == سمتیہ_TYPE
      && سمتیہ_TYPE_P (درخت_TYPE (inside_init))
      && سمتیہ_types_convertible_p (درخت_TYPE (inside_init), type, سچ)
      && درخت_CONSTANT (inside_init))
    {
      اگر (درخت_رمز (inside_init) == سمتیہ_CST
	  && comptypes (TYPE_MAIN_VARIANT (درخت_TYPE (inside_init)),
			TYPE_MAIN_VARIANT (type)))
	واپس inside_init;

      اگر (درخت_رمز (inside_init) == CONSTRUCTOR)
	{
	  غیرعلامتی HOST_WIDE_INT ix;
	  درخت قدر;
	  منطقی constant_p = سچ;

	  /* Iterate through elements and check if all constructor
	     elements are *_CSTs.  */
	  FOR_EACH_CONSTRUCTOR_قدر (CONSTRUCTOR_ELTS (inside_init), ix, قدر)
	    اگر (!CONSTANT_CLASS_P (قدر))
	      {
		constant_p = جھوٹ;
		توڑو;
	      }

	  اگر (constant_p)
	    واپس build_سمتیہ_from_ctor (type,
					   CONSTRUCTOR_ELTS (inside_init));
	}
    }

  اگر (warn_sequence_نقطہ)
    verify_sequence_points (inside_init);

  /* Any type can be initialized
     from an expression of the same type, optionally with braces.  */

  اگر (inside_init && درخت_TYPE (inside_init) != NULL_درخت
      && (comptypes (TYPE_MAIN_VARIANT (درخت_TYPE (inside_init)),
		     TYPE_MAIN_VARIANT (type))
	  || (رمز == ARRAY_TYPE
	      && comptypes (درخت_TYPE (inside_init), type))
	  || (gnu_سمتیہ_type_p (type)
	      && comptypes (درخت_TYPE (inside_init), type))
	  || (رمز == اشارہ_گر_TYPE
	      && درخت_رمز (درخت_TYPE (inside_init)) == ARRAY_TYPE
	      && comptypes (درخت_TYPE (درخت_TYPE (inside_init)),
			    درخت_TYPE (type)))))
    {
      اگر (رمز == اشارہ_گر_TYPE)
	{
	  اگر (درخت_رمز (درخت_TYPE (inside_init)) == ARRAY_TYPE)
	    {
	      اگر (درخت_رمز (inside_init) == STRING_CST
		  || درخت_رمز (inside_init) == COMPOUND_LITERAL_اظہاریہ)
		inside_init = array_مقصد_اشارہ_گر_conversion
		  (init_loc, inside_init);
	      ورنہ
		{
		  error_init (init_loc, "invalid use of non-lvalue array");
		  واپس error_mark_گرہ;
		}
	    }
	}

      اگر (رمز == سمتیہ_TYPE || c_hardbool_type_attr (type))
	/* Although the types are compatible, we may require a
	   conversion.  */
	inside_init = convert (type, inside_init);

      اگر ((رمز == ریکارڈ_TYPE || رمز == UNION_TYPE)
	  && !comptypes (TYPE_MAIN_VARIANT (type), TYPE_MAIN_VARIANT (درخت_TYPE (inside_init))))
	{
	  error_init (init_loc, "invalid initializer");
	  واپس error_mark_گرہ;
	}

      اگر (require_constant
	  && درخت_رمز (inside_init) == COMPOUND_LITERAL_اظہاریہ)
	{
	  /* As an extension, allow initializing objects with static storage
	     duration with compound literals (which are then treated just as
	     the brace enclosed list they contain).  Also allow this for
	     vectors, as we can only assign them with compound literals.  */
	  اگر (flag_isoc99 && رمز != سمتیہ_TYPE)
	    pedwarn_init (init_loc, OPT_Wpedantic, "initializer element "
			  "is not constant");
	  درخت decl = COMPOUND_LITERAL_اظہاریہ_DECL (inside_init);
	  inside_init = DECL_INITIAL (decl);
	}

      اگر (رمز == ARRAY_TYPE && درخت_رمز (inside_init) != STRING_CST
	  && درخت_رمز (inside_init) != CONSTRUCTOR)
	{
	  error_init (init_loc, "array initialized from non-constant array "
		      "expression");
	  واپس error_mark_گرہ;
	}

      /* Compound expressions can only occur here if -Wpedantic or
	 -pedantic-errors is specified.  In the later case, we always want
	 an error.  In the former case, we simply want a warning.  */
      اگر (require_constant && pedantic
	  && درخت_رمز (inside_init) == COMPOUND_اظہاریہ)
	{
	  inside_init
	    = valid_compound_اظہاریہ_initializer (inside_init,
					       درخت_TYPE (inside_init));
	  اگر (inside_init == error_mark_گرہ)
	    error_init (init_loc, "initializer element is not constant");
	  ورنہ
	    pedwarn_init (init_loc, OPT_Wpedantic,
			  "initializer element is not constant");
	  اگر (flag_pedantic_errors)
	    inside_init = error_mark_گرہ;
	}
      ورنہ اگر (require_constant
	       && !initializer_constant_valid_p (inside_init,
						 درخت_TYPE (inside_init)))
	{
	  error_init (init_loc, "initializer element is not constant");
	  inside_init = error_mark_گرہ;
	}
      ورنہ اگر (require_constant && !maybe_const)
	pedwarn_init (init_loc, OPT_Wpedantic,
		      "initializer element is not a constant expression");
      ورنہ اگر (require_constexpr)
	check_constexpr_init (init_loc, type, inside_init,
			      int_const_اظہاریہ, arith_const_اظہاریہ);

      /* Added to enable additional -Wsuggest-attribute=format warnings.  */
      اگر (درخت_رمز (درخت_TYPE (inside_init)) == اشارہ_گر_TYPE)
	inside_init = convert_for_assignment (init_loc, UNKNOWN_LOCATION,
					      type, inside_init, origtype,
					      (require_constant
					       ? ic_init_const
					       : ic_init), null_اشارہ_گر_constant,
					      NULL_درخت, NULL_درخت, 0);
      اگر (درخت_رمز (inside_init) == RAW_ڈیٹا_CST
	  && c_inhibit_evaluation_warnings == 0
	  && warn_conversion
	  && !TYPE_UNSIGNED (type)
	  && TYPE_PRECISION (type) == CHAR_ثنائی_ہندسہ)
	برائے (غیرعلامتی صحیح i = 0;
	     i < (غیرعلامتی) RAW_ڈیٹا_لمبائی (inside_init); ++i)
	  اگر (RAW_ڈیٹا_SCHAR_ELT (inside_init, i) < 0)
	    warning_at (init_loc, OPT_Wconversion,
			"conversion from %qT to %qT changes value from "
			"%qd to %qd",
			integer_type_گرہ, type,
			RAW_ڈیٹا_UCHAR_ELT (inside_init, i),
			RAW_ڈیٹا_SCHAR_ELT (inside_init, i));
      واپس inside_init;
    }

  /* Handle scalar types, including conversions.  */

  اگر (رمز == INTEGER_TYPE || رمز == REAL_TYPE || رمز == FIXED_نقطہ_TYPE
      || رمز == اشارہ_گر_TYPE || رمز == ENUMERAL_TYPE || رمز == BOOLEAN_TYPE
      || رمز == COMPLEX_TYPE || رمز == سمتیہ_TYPE || رمز == NULLPTR_TYPE
      || رمز == BITINT_TYPE)
    {
      درخت unconverted_init = inside_init;
      اگر (درخت_رمز (درخت_TYPE (init)) == ARRAY_TYPE
	  && (درخت_رمز (init) == STRING_CST
	      || درخت_رمز (init) == COMPOUND_LITERAL_اظہاریہ))
	inside_init = init = array_مقصد_اشارہ_گر_conversion (init_loc, init);
      اگر (semantic_type)
	inside_init = build1 (EXCESS_PRECISION_اظہاریہ, semantic_type,
			      inside_init);
      inside_init
	= convert_for_assignment (init_loc, UNKNOWN_LOCATION, type,
				  inside_init, origtype,
				  require_constant ? ic_init_const : ic_init,
				  null_اشارہ_گر_constant, NULL_درخت, NULL_درخت,
				  0);

      /* Check to see if we have already given an error message.  */
      اگر (inside_init == error_mark_گرہ)
	;
      ورنہ اگر (require_constant && !درخت_CONSTANT (inside_init))
	{
	  error_init (init_loc, "initializer element is not constant");
	  inside_init = error_mark_گرہ;
	}
      ورنہ اگر (require_constant
	       && !initializer_constant_valid_p (inside_init,
						 درخت_TYPE (inside_init)))
	{
	  error_init (init_loc, "initializer element is not computable at "
		      "load time");
	  inside_init = error_mark_گرہ;
	}
      ورنہ اگر (require_constant && !maybe_const)
	pedwarn_init (init_loc, OPT_Wpedantic,
		      "initializer element is not a constant expression");
      ورنہ اگر (require_constexpr)
	check_constexpr_init (init_loc, type, unconverted_init,
			      int_const_اظہاریہ, arith_const_اظہاریہ);

      واپس inside_init;
    }

  /* Come here only for records and arrays.  */

  اگر (COMPLETE_TYPE_P (type) && درخت_رمز (TYPE_سائز (type)) != INTEGER_CST)
    {
      error_init (init_loc,
		  "variable-sized object may not be initialized except "
		  "with an empty initializer");
      واپس error_mark_گرہ;
    }

  error_init (init_loc, "invalid initializer");
  واپس error_mark_گرہ;
}

/* Handle initializers that use braces.  */

/* Type of object we are accumulating a constructor for.
   This type is always a RECORD_TYPE, UNION_TYPE or ARRAY_TYPE.  */
ساکن درخت constructor_type;

/* For a RECORD_TYPE or UNION_TYPE, this is the chain of fields
   left to fill.  */
ساکن درخت constructor_fields;

/* For an ARRAY_TYPE, this is the specified index
   at which to store the next element we get.  */
ساکن درخت constructor_اشاریہ;

/* For an ARRAY_TYPE, this is the maximum index.  */
ساکن درخت constructor_max_اشاریہ;

/* For a RECORD_TYPE, this is the first field not yet written out.  */
ساکن درخت constructor_unfilled_fields;

/* For an ARRAY_TYPE, this is the index of the first element
   not yet written out.  */
ساکن درخت constructor_unfilled_اشاریہ;

/* In a RECORD_TYPE, the byte index of the next consecutive field.
   This is so we can generate gaps between fields, when appropriate.  */
ساکن درخت constructor_ثنائی_ہندسہ_اشاریہ;

/* If we are saving up the elements rather than allocating them,
   this is the list of elements so far (in reverse order,
   most recent first).  */
ساکن vec<constructor_elt, va_gc> *constructor_elements;

/* 1 if constructor should be incrementally stored into a constructor chain,
   0 if all the elements should be kept in AVL tree.  */
ساکن صحیح constructor_incremental;

/* 1 if so far this constructor's elements are all compile-time constants.  */
ساکن صحیح constructor_constant;

/* 1 if so far this constructor's elements are all valid address constants.  */
ساکن صحیح constructor_simple;

/* 1 if this constructor has an element that cannot be part of a
   constant expression.  */
ساکن صحیح constructor_nonconst;

/* 1 if this constructor is erroneous so far.  */
ساکن صحیح constructor_erroneous;

/* 1 if this constructor is the universal zero initializer { 0 }.  */
ساکن صحیح constructor_zeroinit;

/* 1 if this constructor should have padding bits zeroed (C23 {}.  */
ساکن منطقی constructor_zero_padding_بٹ;

/* 1 if this constructor is a braced scalar initializer (further nested levels
   of braces are an error).  */
ساکن منطقی constructor_braced_scalar;

/* Structure for managing pending initializer elements, organized as an
   AVL tree.  */

ساخت init_گرہ
{
  ساخت init_گرہ *بائیں, *دائیں;
  ساخت init_گرہ *والد;
  صحیح balance;
  درخت purpose;
  درخت قدر;
  درخت origtype;
};

/* Tree of pending elements at this constructor level.
   These are elements encountered out of order
   which belong at places we haven't reached yet in actually
   writing the output.
   Will never hold tree nodes across GC runs.  */
ساکن ساخت init_گرہ *constructor_pending_elts;

/* The SPELLING_DEPTH of this constructor.  */
ساکن صحیح constructor_گہرائی;

/* DECL node for which an initializer is being read.
   0 means we are reading a constructor expression
   such as (struct foo) {...}.  */
ساکن درخت constructor_decl;

/* Nonzero if there were any member designators in this initializer.  */
ساکن صحیح constructor_designated;

/* Nesting depth of designator list.  */
ساکن صحیح designator_گہرائی;

/* Nonzero if there were diagnosed errors in this designator list.  */
ساکن صحیح designator_erroneous;


/* This stack has a level for each implicit or explicit level of
   structuring in the initializer, including the outermost one.  It
   saves the values of most of the variables above.  */

ساخت constructor_range_ڈھیر;

ساخت constructor_ڈھیر
{
  ساخت constructor_ڈھیر *اگلا;
  درخت type;
  درخت fields;
  درخت اشاریہ;
  درخت max_اشاریہ;
  درخت unfilled_اشاریہ;
  درخت unfilled_fields;
  درخت ثنائی_ہندسہ_اشاریہ;
  vec<constructor_elt, va_gc> *elements;
  ساخت init_گرہ *pending_elts;
  صحیح انحراف;
  صحیح گہرائی;
  /* If value nonzero, this value should replace the entire
     constructor at this level.  */
  ساخت c_اظہاریہ replacement_قدر;
  ساخت constructor_range_ڈھیر *range_ڈھیر;
  حرف constant;
  حرف simple;
  حرف nonconst;
  حرف implicit;
  حرف erroneous;
  حرف outer;
  حرف incremental;
  حرف designated;
  منطقی zero_padding_بٹ;
  منطقی braced_scalar;
  صحیح designator_گہرائی;
};

ساکن ساخت constructor_ڈھیر *constructor_ڈھیر;

/* This stack represents designators from some range designator up to
   the last designator in the list.  */

ساخت constructor_range_ڈھیر
{
  ساخت constructor_range_ڈھیر *اگلا, *پچھلا;
  ساخت constructor_ڈھیر *ڈھیر;
  درخت range_آغاز;
  درخت اشاریہ;
  درخت range_انتہا;
  درخت fields;
};

ساکن ساخت constructor_range_ڈھیر *constructor_range_ڈھیر;

/* This stack records separate initializers that are nested.
   Nested initializers can't happen in ANSI C, but GNU C allows them
   in cases like { ... (struct foo) { ... } ... }.  */

ساخت initializer_ڈھیر
{
  ساخت initializer_ڈھیر *اگلا;
  درخت decl;
  ساخت constructor_ڈھیر *constructor_ڈھیر;
  ساخت constructor_range_ڈھیر *constructor_range_ڈھیر;
  vec<constructor_elt, va_gc> *elements;
  ساخت spelling *spelling;
  ساخت spelling *spelling_بنیاد;
  صحیح spelling_سائز;
  حرف require_constant_قدر;
  حرف require_constant_elements;
  حرف require_constexpr_قدر;
  حرف designated;
  rich_location *missing_brace_richloc;
};

ساکن ساخت initializer_ڈھیر *initializer_ڈھیر;

/* Prepare to parse and output the initializer for variable DECL.  */

خالی
آغاز_init (درخت decl, درخت asmspec_درخت ATTRIBUTE_غیر_مستعمل,
	    منطقی init_require_constant, منطقی init_require_constexpr,
	    rich_location *richloc)
{
  ثابت حرف *locus;
  ساخت initializer_ڈھیر *p = XNEW (ساخت initializer_ڈھیر);

  p->decl = constructor_decl;
  p->require_constant_قدر = require_constant_قدر;
  p->require_constant_elements = require_constant_elements;
  p->require_constexpr_قدر = require_constexpr_قدر;
  p->constructor_ڈھیر = constructor_ڈھیر;
  p->constructor_range_ڈھیر = constructor_range_ڈھیر;
  p->elements = constructor_elements;
  p->spelling = spelling;
  p->spelling_بنیاد = spelling_بنیاد;
  p->spelling_سائز = spelling_سائز;
  p->اگلا = initializer_ڈھیر;
  p->missing_brace_richloc = richloc;
  p->designated = constructor_designated;
  initializer_ڈھیر = p;

  constructor_decl = decl;
  constructor_designated = 0;

  require_constant_قدر = init_require_constant;
  require_constexpr_قدر = init_require_constexpr;
  اگر (decl != NULL_درخت && decl != error_mark_گرہ)
    {
      require_constant_elements
	= ((init_require_constant || (pedantic && !flag_isoc99))
	   /* For a scalar, you can always use any value to initialize,
	      even within braces.  */
	   && AGGREGATE_TYPE_P (درخت_TYPE (decl)));
      locus = identifier_مقصد_locale (IDENTIFIER_اشارہ_گر (DECL_NAME (decl)));
    }
  ورنہ
    {
      require_constant_elements = جھوٹ;
      locus = _("(anonymous)");
    }

  constructor_ڈھیر = 0;
  constructor_range_ڈھیر = 0;

  ملا_missing_braces = 0;

  spelling_بنیاد = 0;
  spelling_سائز = 0;
  RESTORE_SPELLING_گہرائی (0);

  اگر (locus)
    ڈالو_string (locus);
}

خالی
اختتام_init (خالی)
{
  ساخت initializer_ڈھیر *p = initializer_ڈھیر;

  /* Free the whole constructor stack of this initializer.  */
  جب (constructor_ڈھیر)
    {
      ساخت constructor_ڈھیر *q = constructor_ڈھیر;
      constructor_ڈھیر = q->اگلا;
      XDELETE (q);
    }

  gcc_assert (!constructor_range_ڈھیر);

  /* Pop back to the data of the outer initializer (if any).  */
  XDELETE (spelling_بنیاد);

  constructor_decl = p->decl;
  require_constant_قدر = p->require_constant_قدر;
  require_constant_elements = p->require_constant_elements;
  require_constexpr_قدر = p->require_constexpr_قدر;
  constructor_ڈھیر = p->constructor_ڈھیر;
  constructor_designated = p->designated;
  constructor_range_ڈھیر = p->constructor_range_ڈھیر;
  constructor_elements = p->elements;
  spelling = p->spelling;
  spelling_بنیاد = p->spelling_بنیاد;
  spelling_سائز = p->spelling_سائز;
  initializer_ڈھیر = p->اگلا;
  XDELETE (p);
}

/* Call here when we see the initializer is surrounded by braces.
   This is instead of a call to push_init_level;
   it is matched by a call to pop_init_level.

   TYPE is the type to initialize, for a constructor expression.
   For an initializer for a decl, TYPE is zero.  */

خالی
really_آغاز_incremental_init (درخت type)
{
  ساخت constructor_ڈھیر *p = XNEW (ساخت constructor_ڈھیر);

  اگر (type == NULL_درخت)
    type = درخت_TYPE (constructor_decl);

  اگر (سمتیہ_TYPE_P (type)
      && TYPE_سمتیہ_OPAQUE (type))
    error ("opaque vector types cannot be initialized");

  p->type = constructor_type;
  p->fields = constructor_fields;
  p->اشاریہ = constructor_اشاریہ;
  p->max_اشاریہ = constructor_max_اشاریہ;
  p->unfilled_اشاریہ = constructor_unfilled_اشاریہ;
  p->unfilled_fields = constructor_unfilled_fields;
  p->ثنائی_ہندسہ_اشاریہ = constructor_ثنائی_ہندسہ_اشاریہ;
  p->elements = constructor_elements;
  p->constant = constructor_constant;
  p->simple = constructor_simple;
  p->nonconst = constructor_nonconst;
  p->erroneous = constructor_erroneous;
  p->pending_elts = constructor_pending_elts;
  p->گہرائی = constructor_گہرائی;
  p->replacement_قدر.قدر = 0;
  p->replacement_قدر.original_رمز = ERROR_MARK;
  p->replacement_قدر.original_type = تہی;
  p->implicit = 0;
  p->range_ڈھیر = 0;
  p->outer = 0;
  p->incremental = constructor_incremental;
  p->designated = constructor_designated;
  p->zero_padding_بٹ = constructor_zero_padding_بٹ;
  p->braced_scalar = constructor_braced_scalar;
  p->designator_گہرائی = designator_گہرائی;
  p->اگلا = 0;
  constructor_ڈھیر = p;

  constructor_constant = 1;
  constructor_simple = 1;
  constructor_nonconst = 0;
  constructor_گہرائی = SPELLING_گہرائی ();
  constructor_elements = تہی;
  constructor_pending_elts = 0;
  constructor_type = type;
  constructor_incremental = 1;
  constructor_designated = 0;
  constructor_zero_padding_بٹ = جھوٹ;
  constructor_zeroinit = 1;
  constructor_braced_scalar = جھوٹ;
  designator_گہرائی = 0;
  designator_erroneous = 0;

  اگر (ریکارڈ_OR_UNION_TYPE_P (constructor_type))
    {
      constructor_fields = TYPE_FIELDS (constructor_type);
      /* Skip any nameless bit fields at the beginning.  */
      جب (constructor_fields != NULL_درخت
	     && DECL_UNNAMED_ثنائی_ہندسہ_میدان (constructor_fields))
	constructor_fields = DECL_CHAIN (constructor_fields);

      constructor_unfilled_fields = constructor_fields;
      constructor_ثنائی_ہندسہ_اشاریہ = bitsize_zero_گرہ;
    }
  ورنہ اگر (درخت_رمز (constructor_type) == ARRAY_TYPE)
    {
      اگر (TYPE_DOMAIN (constructor_type))
	{
	  constructor_max_اشاریہ
	    = TYPE_MAX_قدر (TYPE_DOMAIN (constructor_type));

	  /* Detect non-empty initializations of zero-length arrays.  */
	  اگر (constructor_max_اشاریہ == NULL_درخت
	      && TYPE_سائز (constructor_type))
	    constructor_max_اشاریہ = integer_minus_one_گرہ;

	  /* constructor_max_index needs to be an INTEGER_CST.  Attempts
	     to initialize VLAs with a nonempty initializer will cause a
	     proper error; avoid tree checking errors as well by setting a
	     safe value.  */
	  اگر (constructor_max_اشاریہ
	      && درخت_رمز (constructor_max_اشاریہ) != INTEGER_CST)
	    constructor_max_اشاریہ = integer_minus_one_گرہ;

	  constructor_اشاریہ
	    = convert (bitsizetype,
		       TYPE_MIN_قدر (TYPE_DOMAIN (constructor_type)));
	}
      ورنہ
	{
	  constructor_اشاریہ = bitsize_zero_گرہ;
	  constructor_max_اشاریہ = NULL_درخت;
	}

      constructor_unfilled_اشاریہ = constructor_اشاریہ;
    }
  ورنہ اگر (gnu_سمتیہ_type_p (constructor_type))
    {
      /* Vectors are like simple fixed-size arrays.  */
      constructor_max_اشاریہ =
	bitsize_int (TYPE_سمتیہ_SUBPARTS (constructor_type) - 1);
      constructor_اشاریہ = bitsize_zero_گرہ;
      constructor_unfilled_اشاریہ = constructor_اشاریہ;
    }
  ورنہ
    {
      /* Handle the case of int x = {5}; */
      constructor_fields = constructor_type;
      constructor_unfilled_fields = constructor_type;
      constructor_braced_scalar = سچ;
    }
}

خارجی location_t آخری_init_list_comma;

/* Called when we see an open brace for a nested initializer.  Finish
   off any pending levels with implicit braces.  */
خالی
اختتام_implicit_inits (location_t loc, ساخت obstack *braced_init_obstack)
{
  جب (constructor_ڈھیر->implicit)
    {
      اگر (ریکارڈ_OR_UNION_TYPE_P (constructor_type)
	  && constructor_fields == NULL_درخت)
	process_init_element (داخلہ_location,
			      نکالو_init_level (loc, 1, braced_init_obstack,
					      آخری_init_list_comma),
			      سچ, braced_init_obstack);
      ورنہ اگر (درخت_رمز (constructor_type) == ARRAY_TYPE
	       && constructor_max_اشاریہ
	       && درخت_int_cst_lt (constructor_max_اشاریہ,
				   constructor_اشاریہ))
	process_init_element (داخلہ_location,
			      نکالو_init_level (loc, 1, braced_init_obstack,
					      آخری_init_list_comma),
			      سچ, braced_init_obstack);
      ورنہ
	توڑو;
    }
}

/* Push down into a subobject, for initialization.
   If this is for an explicit set of braces, IMPLICIT is 0.
   If it is because the next element belongs at a lower level,
   IMPLICIT is 1 (or 2 if the push is because of designator list).  */

خالی
ڈالو_init_level (location_t loc, صحیح implicit,
		 ساخت obstack *braced_init_obstack)
{
  ساخت constructor_ڈھیر *p;
  درخت قدر = NULL_درخت;

  /* Unless this is an explicit brace, we need to preserve previous
     content if any.  */
  اگر (implicit)
    {
      اگر (ریکارڈ_OR_UNION_TYPE_P (constructor_type) && constructor_fields)
	قدر = ڈھونڈو_init_member (constructor_fields, braced_init_obstack);
      ورنہ اگر (درخت_رمز (constructor_type) == ARRAY_TYPE)
	قدر = ڈھونڈو_init_member (constructor_اشاریہ, braced_init_obstack);
    }

  p = XNEW (ساخت constructor_ڈھیر);
  p->type = constructor_type;
  p->fields = constructor_fields;
  p->اشاریہ = constructor_اشاریہ;
  p->max_اشاریہ = constructor_max_اشاریہ;
  p->unfilled_اشاریہ = constructor_unfilled_اشاریہ;
  p->unfilled_fields = constructor_unfilled_fields;
  p->ثنائی_ہندسہ_اشاریہ = constructor_ثنائی_ہندسہ_اشاریہ;
  p->elements = constructor_elements;
  p->constant = constructor_constant;
  p->simple = constructor_simple;
  p->nonconst = constructor_nonconst;
  p->erroneous = constructor_erroneous;
  p->pending_elts = constructor_pending_elts;
  p->گہرائی = constructor_گہرائی;
  p->replacement_قدر.قدر = NULL_درخت;
  p->replacement_قدر.original_رمز = ERROR_MARK;
  p->replacement_قدر.original_type = تہی;
  p->implicit = implicit;
  p->outer = 0;
  p->incremental = constructor_incremental;
  p->designated = constructor_designated;
  p->zero_padding_بٹ = constructor_zero_padding_بٹ;
  p->braced_scalar = constructor_braced_scalar;
  p->designator_گہرائی = designator_گہرائی;
  p->اگلا = constructor_ڈھیر;
  p->range_ڈھیر = 0;
  constructor_ڈھیر = p;

  constructor_constant = 1;
  constructor_simple = 1;
  constructor_nonconst = 0;
  constructor_گہرائی = SPELLING_گہرائی ();
  constructor_elements = تہی;
  constructor_incremental = 1;
  /* If the upper initializer is designated, then mark this as
     designated too to prevent bogus warnings.  */
  constructor_designated = p->designated;
  /* If the upper initializer has padding bits zeroed, that includes
     all nested initializers as well.  */
  constructor_zero_padding_بٹ = p->zero_padding_بٹ;
  constructor_braced_scalar = جھوٹ;
  constructor_pending_elts = 0;
  اگر (!implicit)
    {
      p->range_ڈھیر = constructor_range_ڈھیر;
      constructor_range_ڈھیر = 0;
      designator_گہرائی = 0;
      designator_erroneous = 0;
    }

  /* Don't die if an entire brace-pair level is superfluous
     in the containing level.  */
  اگر (constructor_type == NULL_درخت)
    ;
  ورنہ اگر (ریکارڈ_OR_UNION_TYPE_P (constructor_type))
    {
      /* Don't die if there are extra init elts at the end.  */
      اگر (constructor_fields == NULL_درخت)
	constructor_type = NULL_درخت;
      ورنہ
	{
	  constructor_type = درخت_TYPE (constructor_fields);
	  ڈالو_member_name (constructor_fields);
	  constructor_گہرائی++;
	}
    }
  ورنہ اگر (درخت_رمز (constructor_type) == ARRAY_TYPE)
    {
      constructor_type = درخت_TYPE (constructor_type);
      ڈالو_array_bounds (درخت_مقصد_uhwi (constructor_اشاریہ));
      constructor_گہرائی++;
    }

  اگر (constructor_type == NULL_درخت)
    {
      error_init (loc, "extra brace group at end of initializer");
      constructor_fields = NULL_درخت;
      constructor_unfilled_fields = NULL_درخت;
      واپس;
    }

  اگر (قدر && درخت_رمز (قدر) == CONSTRUCTOR)
    {
      constructor_constant = درخت_CONSTANT (قدر);
      constructor_simple = درخت_STATIC (قدر);
      constructor_nonconst = CONSTRUCTOR_NON_CONST (قدر);
      constructor_elements = CONSTRUCTOR_ELTS (قدر);
      constructor_zero_padding_بٹ |= CONSTRUCTOR_ZERO_PADDING_بٹ (قدر);
      اگر (!vec_محفوظ_is_خالی_خانے (constructor_elements)
	  && (درخت_رمز (constructor_type) == ریکارڈ_TYPE
	      || درخت_رمز (constructor_type) == ARRAY_TYPE))
	سیٹ_nonincremental_init (braced_init_obstack);
    }

  اگر (implicit == 1)
    {
      ملا_missing_braces = 1;
      اگر (initializer_ڈھیر->missing_brace_richloc)
	initializer_ڈھیر->missing_brace_richloc->جوڑو_fixit_داخل_کرو_before
	  (loc, "{");
    }

  اگر (ریکارڈ_OR_UNION_TYPE_P (constructor_type))
    {
      constructor_fields = TYPE_FIELDS (constructor_type);
      /* Skip any nameless bit fields at the beginning.  */
      جب (constructor_fields != NULL_درخت
	     && DECL_UNNAMED_ثنائی_ہندسہ_میدان (constructor_fields))
	constructor_fields = DECL_CHAIN (constructor_fields);

      constructor_unfilled_fields = constructor_fields;
      constructor_ثنائی_ہندسہ_اشاریہ = bitsize_zero_گرہ;
    }
  ورنہ اگر (gnu_سمتیہ_type_p (constructor_type))
    {
      /* Vectors are like simple fixed-size arrays.  */
      constructor_max_اشاریہ =
	bitsize_int (TYPE_سمتیہ_SUBPARTS (constructor_type) - 1);
      constructor_اشاریہ = bitsize_int (0);
      constructor_unfilled_اشاریہ = constructor_اشاریہ;
    }
  ورنہ اگر (درخت_رمز (constructor_type) == ARRAY_TYPE)
    {
      اگر (TYPE_DOMAIN (constructor_type))
	{
	  constructor_max_اشاریہ
	    = TYPE_MAX_قدر (TYPE_DOMAIN (constructor_type));

	  /* Detect non-empty initializations of zero-length arrays.  */
	  اگر (constructor_max_اشاریہ == NULL_درخت
	      && TYPE_سائز (constructor_type))
	    constructor_max_اشاریہ = integer_minus_one_گرہ;

	  /* constructor_max_index needs to be an INTEGER_CST.  Attempts
	     to initialize VLAs will cause a proper error; avoid tree
	     checking errors as well by setting a safe value.  */
	  اگر (constructor_max_اشاریہ
	      && درخت_رمز (constructor_max_اشاریہ) != INTEGER_CST)
	    constructor_max_اشاریہ = integer_minus_one_گرہ;

	  constructor_اشاریہ
	    = convert (bitsizetype,
		       TYPE_MIN_قدر (TYPE_DOMAIN (constructor_type)));
	}
      ورنہ
	constructor_اشاریہ = bitsize_zero_گرہ;

      constructor_unfilled_اشاریہ = constructor_اشاریہ;
      اگر (قدر && درخت_رمز (قدر) == STRING_CST)
	{
	  /* We need to split the char/wchar array into individual
	     characters, so that we don't have to special case it
	     everywhere.  */
	  سیٹ_nonincremental_init_from_string (قدر, braced_init_obstack);
	}
    }
  ورنہ
    {
      اگر (constructor_type != error_mark_گرہ)
	{
	  اگر (p->braced_scalar)
	    permerror_init (داخلہ_location, 0,
			    "braces around scalar initializer");
	  ورنہ
	    warning_init (داخلہ_location, 0,
			  "braces around scalar initializer");
	  constructor_braced_scalar = سچ;
	}
      constructor_fields = constructor_type;
      constructor_unfilled_fields = constructor_type;
    }
}

/* At the end of an implicit or explicit brace level,
   finish up that level of constructor.  If a single expression
   with redundant braces initialized that level, return the
   c_expr structure for that expression.  Otherwise, the original_code
   element is set to ERROR_MARK.
   If we were outputting the elements as they are read, return 0 as the value
   from inner levels (process_init_element ignores that),
   but return error_mark_node as the value from the outermost level
   (that's what we want to put in DECL_INITIAL).
   Otherwise, return a CONSTRUCTOR expression as the value.  */

ساخت c_اظہاریہ
نکالو_init_level (location_t loc, صحیح implicit,
		ساخت obstack *braced_init_obstack,
		location_t داخل_کرو_before)
{
  ساخت constructor_ڈھیر *p;
  ساخت c_اظہاریہ ret;
  ret.قدر = NULL_درخت;
  ret.original_رمز = ERROR_MARK;
  ret.original_type = تہی;
  ret.m_decimal = 0;

  اگر (implicit == 0)
    {
      /* When we come to an explicit close brace,
	 pop any inner levels that didn't have explicit braces.  */
      جب (constructor_ڈھیر->implicit)
	process_init_element (داخلہ_location,
			      نکالو_init_level (loc, 1, braced_init_obstack,
					      داخل_کرو_before),
			      سچ, braced_init_obstack);
      gcc_assert (!constructor_range_ڈھیر);
    }
  ورنہ
    اگر (initializer_ڈھیر->missing_brace_richloc)
      initializer_ڈھیر->missing_brace_richloc->جوڑو_fixit_داخل_کرو_before
	(داخل_کرو_before, "}");

  /* Now output all pending elements.  */
  constructor_incremental = 1;
  output_pending_init_elements (1, braced_init_obstack);

  p = constructor_ڈھیر;

  /* Error for initializing a flexible array member.  */
  اگر (constructor_type && constructor_fields
      && flexible_array_member_type_p (constructor_type))
    {
      /* Silently discard empty initializations.  The parser will
	 already have pedwarned for empty brackets for C17 and earlier.  */
      اگر (integer_zerop (constructor_unfilled_اشاریہ))
	constructor_type = NULL_درخت;
      اگر (constructor_type || flag_isoc23)
	{
	  gcc_assert (!constructor_type || !TYPE_سائز (constructor_type));

	  اگر (constructor_گہرائی <= 2)
	    pedwarn_init (loc, OPT_Wpedantic,
			  "initialization of a flexible array member");
	  ورنہ اگر (constructor_type)
	    error_init (loc, "initialization of flexible array member "
			     "in a nested context");
	  ورنہ
	    pedwarn_init (loc, OPT_Wpedantic,
			  "initialization of flexible array member "
			  "in a nested context");

	  /* We have already issued an error message for the existence
	     of a flexible array member not at the end of the structure.
	     Discard the initializer so that we do not die later.  */
	  اگر (constructor_type
	      && DECL_CHAIN (constructor_fields) != NULL_درخت
	      && (!p->type || درخت_رمز (p->type) != UNION_TYPE))
	    constructor_type = NULL_درخت;
	}
    }

  انتخاب (vec_محفوظ_لمبائی (constructor_elements))
    {
    حالت 0:
      /* Initialization with { } counts as zeroinit.  */
      constructor_zeroinit = 1;
      توڑو;
    حالت 1:
      /* This might be zeroinit as well.  */
      اگر (integer_zerop ((*constructor_elements)[0].قدر))
	constructor_zeroinit = 1;
      توڑو;
    طےشدہ:
      /* If the constructor has more than one element, it can't be { 0 }.  */
      constructor_zeroinit = 0;
      توڑو;
    }

  /* Warn when some structs are initialized with direct aggregation.  */
  اگر (!implicit && ملا_missing_braces && warn_missing_braces
      && !constructor_zeroinit)
    {
      gcc_assert (initializer_ڈھیر->missing_brace_richloc);
      warning_at (initializer_ڈھیر->missing_brace_richloc,
		  OPT_Wmissing_braces,
		  "missing braces around initializer");
    }

  /* Warn when some struct elements are implicitly initialized to zero.  */
  اگر (warn_missing_میدان_initializers
      && constructor_type
      && درخت_رمز (constructor_type) == ریکارڈ_TYPE
      && constructor_unfilled_fields)
    {
	/* Do not warn for flexible array members or zero-length arrays.  */
	جب (constructor_unfilled_fields
	       && (!DECL_سائز (constructor_unfilled_fields)
		   || integer_zerop (DECL_سائز (constructor_unfilled_fields))))
	  constructor_unfilled_fields = DECL_CHAIN (constructor_unfilled_fields);

	اگر (constructor_unfilled_fields
	    /* Do not warn if this level of the initializer uses member
	       designators; it is likely to be deliberate.  */
	    && !constructor_designated
	    /* Do not warn about initializing with { 0 } or with { }.  */
	    && !constructor_zeroinit)
	  {
	    اگر (warning_at (داخلہ_location, OPT_Wmissing_میدان_initializers,
			    "missing initializer for field %qD of %qT",
			    constructor_unfilled_fields,
			    constructor_type))
	      inform (DECL_ماخذ_LOCATION (constructor_unfilled_fields),
		      "%qD declared here", constructor_unfilled_fields);
	  }
    }

  /* Pad out the end of the structure.  */
  اگر (p->replacement_قدر.قدر)
    /* If this closes a superfluous brace pair,
       just pass out the element between them.  */
    ret = p->replacement_قدر;
  ورنہ اگر (constructor_type == NULL_درخت)
    ;
  ورنہ اگر (!ریکارڈ_OR_UNION_TYPE_P (constructor_type)
	   && درخت_رمز (constructor_type) != ARRAY_TYPE
	   && !gnu_سمتیہ_type_p (constructor_type))
    {
      /* A nonincremental scalar initializer--just return
	 the element, after verifying there is just one.
         Empty scalar initializers are supported in C23.  */
      اگر (vec_محفوظ_is_خالی_خانے (constructor_elements))
	{
	  اگر (constructor_erroneous || constructor_type == error_mark_گرہ)
	    ret.قدر = error_mark_گرہ;
	  ورنہ اگر (درخت_رمز (constructor_type) == FUNCTION_TYPE)
	    {
	      error_init (loc, "invalid initializer");
	      ret.قدر = error_mark_گرہ;
	    }
	  ورنہ اگر (درخت_رمز (constructor_type) == اشارہ_گر_TYPE)
	    /* Ensure this is a null pointer constant in the case of a
	       'constexpr' object initialized with {}.  */
	    ret.قدر = build_zero_cst (ptr_type_گرہ);
	  ورنہ
	    ret.قدر = build_zero_cst (constructor_type);
	}
      ورنہ اگر (vec_محفوظ_لمبائی (constructor_elements) != 1)
	{
	  error_init (loc, "extra elements in scalar initializer");
	  ret.قدر = (*constructor_elements)[0].قدر;
	}
      ورنہ
	ret.قدر = (*constructor_elements)[0].قدر;
    }
  ورنہ
    {
      اگر (constructor_erroneous)
	ret.قدر = error_mark_گرہ;
      ورنہ
	{
	  ret.قدر = build_constructor (constructor_type,
					 constructor_elements);
	  اگر (constructor_constant)
	    درخت_CONSTANT (ret.قدر) = 1;
	  اگر (constructor_constant && constructor_simple)
	    درخت_STATIC (ret.قدر) = 1;
	  اگر (constructor_nonconst)
	    CONSTRUCTOR_NON_CONST (ret.قدر) = 1;
	  اگر (constructor_zero_padding_بٹ)
	    CONSTRUCTOR_ZERO_PADDING_بٹ (ret.قدر) = 1;
	}
    }

  اگر (ret.قدر && درخت_رمز (ret.قدر) != CONSTRUCTOR)
    {
      اگر (constructor_nonconst)
	ret.original_رمز = C_MAYBE_CONST_اظہاریہ;
      ورنہ اگر (ret.original_رمز == C_MAYBE_CONST_اظہاریہ)
	ret.original_رمز = ERROR_MARK;
    }

  constructor_type = p->type;
  constructor_fields = p->fields;
  constructor_اشاریہ = p->اشاریہ;
  constructor_max_اشاریہ = p->max_اشاریہ;
  constructor_unfilled_اشاریہ = p->unfilled_اشاریہ;
  constructor_unfilled_fields = p->unfilled_fields;
  constructor_ثنائی_ہندسہ_اشاریہ = p->ثنائی_ہندسہ_اشاریہ;
  constructor_elements = p->elements;
  constructor_constant = p->constant;
  constructor_simple = p->simple;
  constructor_nonconst = p->nonconst;
  constructor_erroneous = p->erroneous;
  constructor_incremental = p->incremental;
  constructor_designated = p->designated;
  constructor_zero_padding_بٹ = p->zero_padding_بٹ;
  constructor_braced_scalar = p->braced_scalar;
  designator_گہرائی = p->designator_گہرائی;
  constructor_pending_elts = p->pending_elts;
  constructor_گہرائی = p->گہرائی;
  اگر (!p->implicit)
    constructor_range_ڈھیر = p->range_ڈھیر;
  RESTORE_SPELLING_گہرائی (constructor_گہرائی);

  constructor_ڈھیر = p->اگلا;
  XDELETE (p);

  اگر (ret.قدر == NULL_درخت && constructor_ڈھیر == 0)
    ret.قدر = error_mark_گرہ;
  واپس ret;
}

/* Common handling for both array range and field name designators.
   ARRAY argument is nonzero for array ranges.  Returns false for success.  */

ساکن منطقی
سیٹ_designator (location_t loc, منطقی array,
		ساخت obstack *braced_init_obstack)
{
  درخت subtype;
  شمار درخت_رمز_2 subcode;

  /* Don't die if an entire brace-pair level is superfluous
     in the containing level, or for an erroneous type.  */
  اگر (constructor_type == NULL_درخت || constructor_type == error_mark_گرہ)
    واپس سچ;

  /* If there were errors in this designator list already, bail out
     silently.  */
  اگر (designator_erroneous)
    واپس سچ;

  /* Likewise for an initializer for a variable-size type.  Those are
     diagnosed in the parser, except for empty initializer braces.  */
  اگر (COMPLETE_TYPE_P (constructor_type)
      && درخت_رمز (TYPE_سائز (constructor_type)) != INTEGER_CST)
    واپس سچ;

  اگر (!designator_گہرائی)
    {
      gcc_assert (!constructor_range_ڈھیر);

      /* Designator list starts at the level of closest explicit
	 braces.  */
      جب (constructor_ڈھیر->implicit)
	process_init_element (داخلہ_location,
			      نکالو_init_level (loc, 1, braced_init_obstack,
					      آخری_init_list_comma),
			      سچ, braced_init_obstack);
      constructor_designated = 1;
      واپس جھوٹ;
    }

  انتخاب (درخت_رمز (constructor_type))
    {
    حالت  ریکارڈ_TYPE:
    حالت  UNION_TYPE:
      subtype = درخت_TYPE (constructor_fields);
      اگر (subtype != error_mark_گرہ)
	subtype = TYPE_MAIN_VARIANT (subtype);
      توڑو;
    حالت ARRAY_TYPE:
      subtype = TYPE_MAIN_VARIANT (درخت_TYPE (constructor_type));
      توڑو;
    طےشدہ:
      gcc_unreachable ();
    }

  subcode = درخت_رمز (subtype);
  اگر (array && subcode != ARRAY_TYPE)
    {
      error_init (loc, "array index in non-array initializer");
      واپس سچ;
    }
  ورنہ اگر (!array && subcode != ریکارڈ_TYPE && subcode != UNION_TYPE)
    {
      error_init (loc, "field name not in record or union initializer");
      واپس سچ;
    }

  constructor_designated = 1;
  اختتام_implicit_inits (loc, braced_init_obstack);
  ڈالو_init_level (loc, 2, braced_init_obstack);
  واپس جھوٹ;
}

/* If there are range designators in designator list, push a new designator
   to constructor_range_stack.  RANGE_END is end of such stack range or
   NULL_TREE if there is no range designator at this level.  */

ساکن خالی
ڈالو_range_ڈھیر (درخت range_انتہا, ساخت obstack * braced_init_obstack)
{
  ساخت constructor_range_ڈھیر *p;

  p = (ساخت constructor_range_ڈھیر *)
    obstack_alloc (braced_init_obstack,
		   حجم (ساخت constructor_range_ڈھیر));
  p->پچھلا = constructor_range_ڈھیر;
  p->اگلا = 0;
  p->fields = constructor_fields;
  p->range_آغاز = constructor_اشاریہ;
  p->اشاریہ = constructor_اشاریہ;
  p->ڈھیر = constructor_ڈھیر;
  p->range_انتہا = range_انتہا;
  اگر (constructor_range_ڈھیر)
    constructor_range_ڈھیر->اگلا = p;
  constructor_range_ڈھیر = p;
}

/* Within an array initializer, specify the next index to be initialized.
   FIRST is that index.  If LAST is nonzero, then initialize a range
   of indices, running from FIRST through LAST.  */

خالی
سیٹ_init_اشاریہ (location_t loc, درخت پہلا, درخت آخری,
		ساخت obstack *braced_init_obstack)
{
  اگر (سیٹ_designator (loc, سچ, braced_init_obstack))
    واپس;

  designator_erroneous = 1;

  اگر (!INTEGRAL_TYPE_P (درخت_TYPE (پہلا))
      || (آخری && !INTEGRAL_TYPE_P (درخت_TYPE (آخری))))
    {
      error_init (loc, "array index in initializer not of integer type");
      واپس;
    }

  اگر (درخت_رمز (پہلا) != INTEGER_CST)
    {
      پہلا = c_fully_fold (پہلا, جھوٹ, تہی);
      اگر (درخت_رمز (پہلا) == INTEGER_CST)
	pedwarn_init (loc, OPT_Wpedantic,
		      "array index in initializer is not "
		      "an integer constant expression");
    }

  اگر (آخری && درخت_رمز (آخری) != INTEGER_CST)
    {
      آخری = c_fully_fold (آخری, جھوٹ, تہی);
      اگر (درخت_رمز (آخری) == INTEGER_CST)
	pedwarn_init (loc, OPT_Wpedantic,
		      "array index in initializer is not "
		      "an integer constant expression");
    }

  اگر (درخت_رمز (پہلا) != INTEGER_CST)
    error_init (loc, "nonconstant array index in initializer");
  ورنہ اگر (آخری != NULL_درخت && درخت_رمز (آخری) != INTEGER_CST)
    error_init (loc, "nonconstant array index in initializer");
  ورنہ اگر (درخت_رمز (constructor_type) != ARRAY_TYPE)
    error_init (loc, "array index in non-array initializer");
  ورنہ اگر (درخت_int_cst_sgn (پہلا) == -1)
    error_init (loc, "array index in initializer exceeds array bounds");
  ورنہ اگر (constructor_max_اشاریہ
	   && درخت_int_cst_lt (constructor_max_اشاریہ, پہلا))
    error_init (loc, "array index in initializer exceeds array bounds");
  ورنہ
    {
      constant_عبارت_warning (پہلا);
      اگر (آخری)
	constant_عبارت_warning (آخری);
      constructor_اشاریہ = convert (bitsizetype, پہلا);
      اگر (درخت_int_cst_lt (constructor_اشاریہ, پہلا))
	{
	  constructor_اشاریہ = copy_گرہ (constructor_اشاریہ);
	  درخت_حد_سے_تجاوز (constructor_اشاریہ) = 1;
	}

      اگر (آخری)
	{
	  اگر (درخت_int_cst_equal (پہلا, آخری))
	    آخری = NULL_درخت;
	  ورنہ اگر (درخت_int_cst_lt (آخری, پہلا))
	    {
	      error_init (loc, "empty index range in initializer");
	      آخری = NULL_درخت;
	    }
	  ورنہ
	    {
	      آخری = convert (bitsizetype, آخری);
	      اگر (constructor_max_اشاریہ != NULL_درخت
		  && درخت_int_cst_lt (constructor_max_اشاریہ, آخری))
		{
		  error_init (loc, "array index range in initializer exceeds "
			      "array bounds");
		  آخری = NULL_درخت;
		}
	    }
	}

      designator_گہرائی++;
      designator_erroneous = 0;
      اگر (constructor_range_ڈھیر || آخری)
	ڈالو_range_ڈھیر (آخری, braced_init_obstack);
    }
}

/* Within a struct initializer, specify the next field to be initialized.  */

خالی
سیٹ_init_label (location_t loc, درخت fieldname, location_t fieldname_loc,
		ساخت obstack *braced_init_obstack)
{
  درخت میدان_2;

  اگر (سیٹ_designator (loc, جھوٹ, braced_init_obstack))
    واپس;

  designator_erroneous = 1;

  اگر (!ریکارڈ_OR_UNION_TYPE_P (constructor_type))
    {
      error_init (loc, "field name not in record or union initializer");
      واپس;
    }

  میدان_2 = lookup_میدان (constructor_type, fieldname);

  اگر (میدان_2 == NULL_درخت)
    {
      درخت guessed_id = lookup_میدان_fuzzy (constructor_type, fieldname);
      اگر (guessed_id)
	{
	  gcc_rich_location rich_loc (fieldname_loc);
	  rich_loc.جوڑو_fixit_misspelled_id (fieldname_loc, guessed_id);
	  error_at (&rich_loc,
		    "%qT has no member named %qE; did you mean %qE?",
		    constructor_type, fieldname, guessed_id);
	}
      ورنہ
	error_at (fieldname_loc, "%qT has no member named %qE",
		  constructor_type, fieldname);
    }
  ورنہ
    کرو
      {
	constructor_fields = درخت_قدر (میدان_2);
	designator_گہرائی++;
	designator_erroneous = 0;
	اگر (constructor_range_ڈھیر)
	  ڈالو_range_ڈھیر (NULL_درخت, braced_init_obstack);
	میدان_2 = درخت_CHAIN (میدان_2);
	اگر (میدان_2)
	  {
	    اگر (سیٹ_designator (loc, جھوٹ, braced_init_obstack))
	      واپس;
	  }
      }
    جب (میدان_2 != NULL_درخت);
}

/* Helper function for add_pending_init.  Find inorder successor of P
   in AVL tree.  */
ساکن ساخت init_گرہ *
init_گرہ_successor (ساخت init_گرہ *p)
{
  ساخت init_گرہ *r;
  اگر (p->دائیں)
    {
      r = p->دائیں;
      جب (r->بائیں)
	r = r->بائیں;
      واپس r;
    }
  r = p->والد;
  جب (r && p == r->دائیں)
    {
      p = r;
      r = r->والد;
    }
  واپس r;
}

/* Add a new initializer to the tree of pending initializers.  PURPOSE
   identifies the initializer, either array index or field in a structure.
   VALUE is the value of that index or field.  If ORIGTYPE is not
   NULL_TREE, it is the original type of VALUE.

   IMPLICIT is true if value comes from pop_init_level (1),
   the new initializer has been merged with the existing one
   and thus no warnings should be emitted about overriding an
   existing initializer.  */

ساکن خالی
جوڑو_pending_init (location_t loc, درخت purpose, درخت قدر, درخت origtype,
		  منطقی implicit, ساخت obstack *braced_init_obstack)
{
  ساخت init_گرہ *p, **q, *r;

  q = &constructor_pending_elts;
  p = 0;

  اگر (درخت_رمز (constructor_type) == ARRAY_TYPE)
    {
      جب (*q != 0)
	{
	  p = *q;
	  اگر (درخت_int_cst_lt (purpose, p->purpose))
	    q = &p->بائیں;
	  ورنہ اگر (درخت_int_cst_lt (p->purpose, purpose))
	    {
	      اگر (درخت_رمز (p->قدر) != RAW_ڈیٹا_CST
		  || (p->دائیں
		      && درخت_int_cst_le (p->دائیں->purpose, purpose)))
		q = &p->دائیں;
	      ورنہ
		{
		  widest_int pp = wi::مقصد_widest (p->purpose);
		  widest_int pw = wi::مقصد_widest (purpose);
		  اگر (pp + RAW_ڈیٹا_لمبائی (p->قدر) <= pw)
		    q = &p->دائیں;
		  ورنہ
		    {
		      /* Override which should split the old RAW_DATA_CST
			 into 2 or 3 pieces.  */
		      اگر (!implicit && warn_override_init)
			warning_init (loc, OPT_Woverride_init,
				      "initialized field overwritten");
		      غیرعلامتی HOST_WIDE_INT آغاز = (pw - pp).مقصد_uhwi ();
		      غیرعلامتی HOST_WIDE_INT len = 1;
		      اگر (درخت_رمز (قدر) == RAW_ڈیٹا_CST)
			len = RAW_ڈیٹا_لمبائی (قدر);
		      غیرعلامتی HOST_WIDE_INT انتہا = 0;
		      غیرعلامتی plen = RAW_ڈیٹا_لمبائی (p->قدر);
		      gcc_checking_assert (آغاز < plen && آغاز);
		      اگر (plen - آغاز > len)
			انتہا = plen - آغاز - len;
		      درخت v = p->قدر;
		      درخت origtype = p->origtype;
		      اگر (آغاز == 1)
			p->قدر = build_int_cst (درخت_TYPE (v),
						  RAW_ڈیٹا_UCHAR_ELT (v, 0));
		      ورنہ
			{
			  p->قدر = v;
			  اگر (انتہا > 1)
			    v = copy_گرہ (v);
			  RAW_ڈیٹا_لمبائی (p->قدر) = آغاز;
			}
		      اگر (انتہا)
			{
			  درخت epurpose
			    = سائز_binop (PLUS_اظہاریہ, purpose,
					  bitsize_int (len));
			  اگر (انتہا > 1)
			    {
			      RAW_ڈیٹا_لمبائی (v) -= plen - انتہا;
			      RAW_ڈیٹا_اشارہ_گر (v) += plen - انتہا;
			    }
			  ورنہ
			    v = build_int_cst (درخت_TYPE (v),
					       RAW_ڈیٹا_UCHAR_ELT (v, plen
								      - انتہا));
			  جوڑو_pending_init (loc, epurpose, v, origtype,
					    implicit, braced_init_obstack);
			}
		      q = &constructor_pending_elts;
		      جاری;
		    }
		}
	    }
	  ورنہ
	    {
	      اگر (درخت_رمز (p->قدر) == RAW_ڈیٹا_CST
		  && (RAW_ڈیٹا_لمبائی (p->قدر)
		      > (درخت_رمز (قدر) == RAW_ڈیٹا_CST
			 ? RAW_ڈیٹا_لمبائی (قدر) : 1)))
		{
		  /* Override which should split the old RAW_DATA_CST
		     into 2 pieces.  */
		  اگر (!implicit && warn_override_init)
		    warning_init (loc, OPT_Woverride_init,
				  "initialized field overwritten");
		  غیرعلامتی HOST_WIDE_INT len = 1;
		  اگر (درخت_رمز (قدر) == RAW_ڈیٹا_CST)
		    len = RAW_ڈیٹا_لمبائی (قدر);
		  اگر ((غیرعلامتی) RAW_ڈیٹا_لمبائی (p->قدر) > len + 1)
		    {
		      RAW_ڈیٹا_لمبائی (p->قدر) -= len;
		      RAW_ڈیٹا_اشارہ_گر (p->قدر) += len;
		    }
		  ورنہ
		    {
		      غیرعلامتی صحیح l = RAW_ڈیٹا_لمبائی (p->قدر) - 1;
		      p->قدر
			= build_int_cst (درخت_TYPE (p->قدر),
					 RAW_ڈیٹا_UCHAR_ELT (p->قدر, l));
		    }
		  p->purpose = سائز_binop (PLUS_اظہاریہ, p->purpose,
					   bitsize_int (len));
		  جاری;
		}
	      اگر (درخت_رمز (قدر) == RAW_ڈیٹا_CST)
		{
		handle_raw_ڈیٹا:
		  /* RAW_DATA_CST value might overlap various further
		     prior initval entries.  Find out how many.  */
		  غیرعلامتی cnt = 0;
		  widest_int w
		    = wi::مقصد_widest (purpose) + RAW_ڈیٹا_لمبائی (قدر);
		  ساخت init_گرہ *r = p, *آخری = تہی;
		  منطقی override_init = warn_override_init;
		  جب ((r = init_گرہ_successor (r))
			 && wi::مقصد_widest (r->purpose) < w)
		    {
		      ++cnt;
		      اگر (درخت_SIDE_EFFECTS (r->قدر))
			warning_init (loc, OPT_Woverride_init_side_effects,
				      "initialized field with side-effects "
				      "overwritten");
		      ورنہ اگر (override_init)
			{
			  warning_init (loc, OPT_Woverride_init,
					"initialized field overwritten");
			  override_init = جھوٹ;
			}
		      آخری = r;
		    }
		  اگر (cnt)
		    {
		      اگر (درخت_رمز (آخری->قدر) == RAW_ڈیٹا_CST
			  && (wi::مقصد_widest (آخری->purpose)
			      + RAW_ڈیٹا_لمبائی (آخری->قدر) > w))
			{
			  /* The last overlapping prior initval overlaps
			     only partially.  Shrink it and decrease cnt.  */
			  غیرعلامتی صحیح l = (wi::مقصد_widest (آخری->purpose)
					    + RAW_ڈیٹا_لمبائی (آخری->قدر)
					    - w).مقصد_uhwi ();
			  --cnt;
			  RAW_ڈیٹا_لمبائی (آخری->قدر) -= l;
			  RAW_ڈیٹا_اشارہ_گر (آخری->قدر) += l;
			  اگر (RAW_ڈیٹا_لمبائی (آخری->قدر) == 1)
			    آخری->قدر
			      = build_int_cst (درخت_TYPE (آخری->قدر),
					       RAW_ڈیٹا_UCHAR_ELT (آخری->قدر,
								   0));
			  آخری->purpose
			    = سائز_binop (PLUS_اظہاریہ, آخری->purpose,
					  bitsize_int (l));
			}
		      /* Instead of deleting cnt nodes from the AVL tree
			 and rebalancing, peel of last cnt bytes from the
			 RAW_DATA_CST.  Overriding thousands of previously
			 initialized array elements with #embed needs to work,
			 but doesn't need to be super efficient.  */
		      gcc_checking_assert ((غیرعلامتی) RAW_ڈیٹا_لمبائی (قدر)
					   > cnt);
		      RAW_ڈیٹا_لمبائی (قدر) -= cnt;
		      ثابت غیرعلامتی حرف *s
			= &RAW_ڈیٹا_UCHAR_ELT (قدر, RAW_ڈیٹا_لمبائی (قدر));
		      غیرعلامتی صحیح o = RAW_ڈیٹا_لمبائی (قدر);
		      برائے (r = p; cnt--; ++o, ++s)
			{
			  r = init_گرہ_successor (r);
			  r->purpose = سائز_binop (PLUS_اظہاریہ, purpose,
						   bitsize_int (o));
			  r->قدر = build_int_cst (درخت_TYPE (قدر), *s);
			  r->origtype = origtype;
			}
		      اگر (RAW_ڈیٹا_لمبائی (قدر) == 1)
			قدر = build_int_cst (درخت_TYPE (قدر),
					       RAW_ڈیٹا_UCHAR_ELT (قدر, 0));
		    }
		}
	      اگر (!implicit)
		{
		  اگر (درخت_SIDE_EFFECTS (p->قدر))
		    warning_init (loc, OPT_Woverride_init_side_effects,
				  "initialized field with side-effects "
				  "overwritten");
		  ورنہ اگر (warn_override_init)
		    warning_init (loc, OPT_Woverride_init,
				  "initialized field overwritten");
		}
	      p->قدر = قدر;
	      p->origtype = origtype;
	      واپس;
	    }
	}
      اگر (درخت_رمز (قدر) == RAW_ڈیٹا_CST && p)
	{
	  ساخت init_گرہ *r;
	  اگر (q == &p->بائیں)
	    r = p;
	  ورنہ
	    r = init_گرہ_successor (p);
	  اگر (r && wi::مقصد_widest (r->purpose) < (wi::مقصد_widest (purpose)
						 + RAW_ڈیٹا_لمبائی (قدر)))
	    {
	      /* Overlap with at least one prior initval in the range but
		 not at the start.  */
	      p = r;
	      p->purpose = purpose;
	      جاؤ handle_raw_ڈیٹا;
	    }
	}
    }
  ورنہ
    {
      درخت bitpos;

      bitpos = ثنائی_ہندسہ_position (purpose);
      جب (*q != تہی)
	{
	  p = *q;
	  اگر (درخت_int_cst_lt (bitpos, ثنائی_ہندسہ_position (p->purpose)))
	    q = &p->بائیں;
	  ورنہ اگر (p->purpose != purpose)
	    q = &p->دائیں;
	  ورنہ
	    {
	      اگر (!implicit)
		{
		  اگر (درخت_SIDE_EFFECTS (p->قدر))
		    warning_init (loc, OPT_Woverride_init_side_effects,
				  "initialized field with side-effects "
				  "overwritten");
		  ورنہ اگر (warn_override_init)
		    warning_init (loc, OPT_Woverride_init,
				  "initialized field overwritten");
		}
	      p->قدر = قدر;
	      p->origtype = origtype;
	      واپس;
	    }
	}
    }

  r = (ساخت init_گرہ *) obstack_alloc (braced_init_obstack,
					  حجم (ساخت init_گرہ));
  r->purpose = purpose;
  r->قدر = قدر;
  r->origtype = origtype;

  *q = r;
  r->والد = p;
  r->بائیں = 0;
  r->دائیں = 0;
  r->balance = 0;

  جب (p)
    {
      ساخت init_گرہ *s;

      اگر (r == p->بائیں)
	{
	  اگر (p->balance == 0)
	    p->balance = -1;
	  ورنہ اگر (p->balance < 0)
	    {
	      اگر (r->balance < 0)
		{
		  /* L rotation.  */
		  p->بائیں = r->دائیں;
		  اگر (p->بائیں)
		    p->بائیں->والد = p;
		  r->دائیں = p;

		  p->balance = 0;
		  r->balance = 0;

		  s = p->والد;
		  p->والد = r;
		  r->والد = s;
		  اگر (s)
		    {
		      اگر (s->بائیں == p)
			s->بائیں = r;
		      ورنہ
			s->دائیں = r;
		    }
		  ورنہ
		    constructor_pending_elts = r;
		}
	      ورنہ
		{
		  /* LR rotation.  */
		  ساخت init_گرہ *t = r->دائیں;

		  r->دائیں = t->بائیں;
		  اگر (r->دائیں)
		    r->دائیں->والد = r;
		  t->بائیں = r;

		  p->بائیں = t->دائیں;
		  اگر (p->بائیں)
		    p->بائیں->والد = p;
		  t->دائیں = p;

		  p->balance = t->balance < 0;
		  r->balance = -(t->balance > 0);
		  t->balance = 0;

		  s = p->والد;
		  p->والد = t;
		  r->والد = t;
		  t->والد = s;
		  اگر (s)
		    {
		      اگر (s->بائیں == p)
			s->بائیں = t;
		      ورنہ
			s->دائیں = t;
		    }
		  ورنہ
		    constructor_pending_elts = t;
		}
	      توڑو;
	    }
	  ورنہ
	    {
	      /* p->balance == +1; growth of left side balances the node.  */
	      p->balance = 0;
	      توڑو;
	    }
	}
      ورنہ /* r == p->right */
	{
	  اگر (p->balance == 0)
	    /* Growth propagation from right side.  */
	    p->balance++;
	  ورنہ اگر (p->balance > 0)
	    {
	      اگر (r->balance > 0)
		{
		  /* R rotation.  */
		  p->دائیں = r->بائیں;
		  اگر (p->دائیں)
		    p->دائیں->والد = p;
		  r->بائیں = p;

		  p->balance = 0;
		  r->balance = 0;

		  s = p->والد;
		  p->والد = r;
		  r->والد = s;
		  اگر (s)
		    {
		      اگر (s->بائیں == p)
			s->بائیں = r;
		      ورنہ
			s->دائیں = r;
		    }
		  ورنہ
		    constructor_pending_elts = r;
		}
	      ورنہ /* r->balance == -1 */
		{
		  /* RL rotation */
		  ساخت init_گرہ *t = r->بائیں;

		  r->بائیں = t->دائیں;
		  اگر (r->بائیں)
		    r->بائیں->والد = r;
		  t->دائیں = r;

		  p->دائیں = t->بائیں;
		  اگر (p->دائیں)
		    p->دائیں->والد = p;
		  t->بائیں = p;

		  r->balance = (t->balance < 0);
		  p->balance = -(t->balance > 0);
		  t->balance = 0;

		  s = p->والد;
		  p->والد = t;
		  r->والد = t;
		  t->والد = s;
		  اگر (s)
		    {
		      اگر (s->بائیں == p)
			s->بائیں = t;
		      ورنہ
			s->دائیں = t;
		    }
		  ورنہ
		    constructor_pending_elts = t;
		}
	      توڑو;
	    }
	  ورنہ
	    {
	      /* p->balance == -1; growth of right side balances the node.  */
	      p->balance = 0;
	      توڑو;
	    }
	}

      r = p;
      p = p->والد;
    }
}

/* Build AVL tree from a sorted chain.  */

ساکن خالی
سیٹ_nonincremental_init (ساخت obstack * braced_init_obstack)
{
  غیرعلامتی HOST_WIDE_INT ix;
  درخت اشاریہ, قدر;

  اگر (درخت_رمز (constructor_type) != ریکارڈ_TYPE
      && درخت_رمز (constructor_type) != ARRAY_TYPE)
    واپس;

  FOR_EACH_CONSTRUCTOR_ELT (constructor_elements, ix, اشاریہ, قدر)
    جوڑو_pending_init (داخلہ_location, اشاریہ, قدر, NULL_درخت, سچ,
		      braced_init_obstack);
  constructor_elements = تہی;
  اگر (درخت_رمز (constructor_type) == ریکارڈ_TYPE)
    {
      constructor_unfilled_fields = TYPE_FIELDS (constructor_type);
      /* Skip any nameless bit fields at the beginning.  */
      جب (constructor_unfilled_fields != NULL_درخت
	     && DECL_UNNAMED_ثنائی_ہندسہ_میدان (constructor_unfilled_fields))
	constructor_unfilled_fields = درخت_CHAIN (constructor_unfilled_fields);

    }
  ورنہ اگر (درخت_رمز (constructor_type) == ARRAY_TYPE)
    {
      اگر (TYPE_DOMAIN (constructor_type))
	constructor_unfilled_اشاریہ
	  = convert (bitsizetype,
		     TYPE_MIN_قدر (TYPE_DOMAIN (constructor_type)));
      ورنہ
	constructor_unfilled_اشاریہ = bitsize_zero_گرہ;
    }
  constructor_incremental = 0;
}

/* Build AVL tree from a string constant.  */

ساکن خالی
سیٹ_nonincremental_init_from_string (درخت str,
				     ساخت obstack * braced_init_obstack)
{
  درخت قدر, purpose, type;
  HOST_WIDE_INT val[2];
  ثابت حرف *p, *انتہا;
  صحیح byte, wchar_بائٹیں, charwidth, bitpos;

  gcc_assert (درخت_رمز (constructor_type) == ARRAY_TYPE);

  wchar_بائٹیں = TYPE_PRECISION (درخت_TYPE (درخت_TYPE (str))) / بٹ_فی_UNIT;
  charwidth = TYPE_PRECISION (char_type_گرہ);
  gcc_assert ((سائز_t) wchar_بائٹیں * charwidth
	      <= ARRAY_سائز (val) * HOST_بٹ_فی_WIDE_INT);
  type = درخت_TYPE (constructor_type);
  p = درخت_STRING_اشارہ_گر (str);
  انتہا = p + درخت_STRING_لمبائی (str);

  برائے (purpose = bitsize_zero_گرہ;
       p < انتہا
       && !(constructor_max_اشاریہ
	    && درخت_int_cst_lt (constructor_max_اشاریہ, purpose));
       purpose = سائز_binop (PLUS_اظہاریہ, purpose, bitsize_one_گرہ))
    {
      اگر (wchar_بائٹیں == 1)
	{
	  val[0] = (غیرعلامتی حرف) *p++;
	  val[1] = 0;
	}
      ورنہ
	{
	  val[1] = 0;
	  val[0] = 0;
	  برائے (byte = 0; byte < wchar_بائٹیں; byte++)
	    {
	      اگر (بائٹیں_BIG_ENDIAN)
		bitpos = (wchar_بائٹیں - byte - 1) * charwidth;
	      ورنہ
		bitpos = byte * charwidth;
	      val[bitpos / HOST_بٹ_فی_WIDE_INT]
		|= ((غیرعلامتی HOST_WIDE_INT) ((غیرعلامتی حرف) *p++))
		   << (bitpos % HOST_بٹ_فی_WIDE_INT);
	    }
	}

      اگر (!TYPE_UNSIGNED (type))
	{
	  bitpos = ((wchar_بائٹیں - 1) * charwidth) + HOST_بٹ_فی_CHAR;
	  اگر (bitpos < HOST_بٹ_فی_WIDE_INT)
	    {
	      اگر (val[0] & (HOST_WIDE_INT_1 << (bitpos - 1)))
		{
		  val[0] |= HOST_WIDE_INT_M1U << bitpos;
		  val[1] = -1;
		}
	    }
	  ورنہ اگر (bitpos == HOST_بٹ_فی_WIDE_INT)
	    {
	      اگر (val[0] < 0)
		val[1] = -1;
	    }
	  ورنہ اگر (val[1] & (HOST_WIDE_INT_1
			     << (bitpos - 1 - HOST_بٹ_فی_WIDE_INT)))
	    val[1] |= HOST_WIDE_INT_M1U << (bitpos - HOST_بٹ_فی_WIDE_INT);
	}

      قدر = wide_int_مقصد_درخت (type,
				wide_int::from_array (val, 2,
						      HOST_بٹ_فی_WIDE_INT * 2));
      جوڑو_pending_init (داخلہ_location, purpose, قدر, NULL_درخت, سچ,
                        braced_init_obstack);
    }

  constructor_incremental = 0;
}

/* Return value of FIELD in pending initializer or NULL_TREE if the field was
   not initialized yet.  */

ساکن درخت
ڈھونڈو_init_member (درخت میدان_2, ساخت obstack * braced_init_obstack)
{
  ساخت init_گرہ *p;

  اگر (درخت_رمز (constructor_type) == ARRAY_TYPE)
    {
      اگر (constructor_incremental
	  && درخت_int_cst_lt (میدان_2, constructor_unfilled_اشاریہ))
	سیٹ_nonincremental_init (braced_init_obstack);

      p = constructor_pending_elts;
      جب (p)
	{
	  اگر (درخت_int_cst_lt (میدان_2, p->purpose))
	    p = p->بائیں;
	  ورنہ اگر (درخت_int_cst_lt (p->purpose, میدان_2))
	    p = p->دائیں;
	  ورنہ
	    واپس p->قدر;
	}
    }
  ورنہ اگر (درخت_رمز (constructor_type) == ریکارڈ_TYPE)
    {
      درخت bitpos = ثنائی_ہندسہ_position (میدان_2);

      اگر (constructor_incremental
	  && (!constructor_unfilled_fields
	      || درخت_int_cst_lt (bitpos,
				  ثنائی_ہندسہ_position (constructor_unfilled_fields))))
	سیٹ_nonincremental_init (braced_init_obstack);

      p = constructor_pending_elts;
      جب (p)
	{
	  اگر (میدان_2 == p->purpose)
	    واپس p->قدر;
	  ورنہ اگر (درخت_int_cst_lt (bitpos, ثنائی_ہندسہ_position (p->purpose)))
	    p = p->بائیں;
	  ورنہ
	    p = p->دائیں;
	}
    }
  ورنہ اگر (درخت_رمز (constructor_type) == UNION_TYPE)
    {
      اگر (!vec_محفوظ_is_خالی_خانے (constructor_elements)
	  && (constructor_elements->آخری ().اشاریہ == میدان_2))
	واپس constructor_elements->آخری ().قدر;
    }
  واپس NULL_درخت;
}

/* "Output" the next constructor element.
   At top level, really output it to assembler code now.
   Otherwise, collect it in a list from which we will make a CONSTRUCTOR.
   If ORIGTYPE is not NULL_TREE, it is the original type of VALUE.
   TYPE is the data type that the containing data type wants here.
   FIELD is the field (a FIELD_DECL) or the index that this element fills.
   If VALUE is a string constant, STRICT_STRING is true if it is
   unparenthesized or we should not warn here for it being parenthesized.
   For other types of VALUE, STRICT_STRING is not used.

   PENDING if true means output pending elements that belong
   right after this element.  (PENDING is normally true;
   it is false while outputting pending elements, to avoid recursion.)

   IMPLICIT is true if value comes from pop_init_level (1),
   the new initializer has been merged with the existing one
   and thus no warnings should be emitted about overriding an
   existing initializer.  */

ساکن خالی
output_init_element (location_t loc, درخت قدر, درخت origtype,
		     منطقی strict_string, درخت type, درخت میدان_2, منطقی pending,
		     منطقی implicit, ساخت obstack * braced_init_obstack)
{
  درخت semantic_type = NULL_درخت;
  منطقی maybe_const = سچ;
  منطقی npc, int_const_اظہاریہ, arith_const_اظہاریہ;

  اگر (type == error_mark_گرہ || قدر == error_mark_گرہ)
    {
      constructor_erroneous = 1;
      واپس;
    }
  اگر (درخت_رمز (درخت_TYPE (قدر)) == ARRAY_TYPE
      && (درخت_رمز (قدر) == STRING_CST
	  || درخت_رمز (قدر) == COMPOUND_LITERAL_اظہاریہ)
      && !(درخت_رمز (قدر) == STRING_CST
	   && درخت_رمز (type) == ARRAY_TYPE
	   && INTEGRAL_TYPE_P (درخت_TYPE (type)))
      && !comptypes (TYPE_MAIN_VARIANT (درخت_TYPE (قدر)),
		     TYPE_MAIN_VARIANT (type)))
    قدر = array_مقصد_اشارہ_گر_conversion (داخلہ_location, قدر);

  اگر (درخت_رمز (قدر) == COMPOUND_LITERAL_اظہاریہ
      && require_constant_قدر && pending)
    {
      /* As an extension, allow initializing objects with static storage
	 duration with compound literals (which are then treated just as
	 the brace enclosed list they contain).  */
      اگر (flag_isoc99)
	pedwarn_init (loc, OPT_Wpedantic, "initializer element is not "
		      "constant");
      درخت decl = COMPOUND_LITERAL_اظہاریہ_DECL (قدر);
      قدر = DECL_INITIAL (decl);
    }

  npc = null_اشارہ_گر_constant_p (قدر);
  int_const_اظہاریہ = (درخت_رمز (قدر) == INTEGER_CST
		    && !درخت_حد_سے_تجاوز (قدر)
		    && INTEGRAL_TYPE_P (درخت_TYPE (قدر)));
  /* Not fully determined before folding.  */
  arith_const_اظہاریہ = سچ;
  اگر (درخت_رمز (قدر) == EXCESS_PRECISION_اظہاریہ)
    {
      semantic_type = درخت_TYPE (قدر);
      قدر = درخت_عملیہ (قدر, 0);
    }
  قدر = c_fully_fold (قدر, require_constant_قدر, &maybe_const);
  /* TODO: this may not detect all cases of expressions folding to
     constants that are not arithmetic constant expressions.  */
  اگر (!maybe_const)
    arith_const_اظہاریہ = جھوٹ;
  ورنہ اگر (!INTEGRAL_TYPE_P (درخت_TYPE (قدر))
	   && درخت_رمز (درخت_TYPE (قدر)) != REAL_TYPE
	   && درخت_رمز (درخت_TYPE (قدر)) != COMPLEX_TYPE)
    arith_const_اظہاریہ = جھوٹ;
  ورنہ اگر (درخت_رمز (قدر) != INTEGER_CST
	   && درخت_رمز (قدر) != REAL_CST
	   && درخت_رمز (قدر) != COMPLEX_CST
	   && درخت_رمز (قدر) != RAW_ڈیٹا_CST)
    arith_const_اظہاریہ = جھوٹ;
  ورنہ اگر (درخت_حد_سے_تجاوز (قدر))
    arith_const_اظہاریہ = جھوٹ;

  اگر (قدر == error_mark_گرہ)
    constructor_erroneous = 1;
  ورنہ اگر (!درخت_CONSTANT (قدر))
    constructor_constant = 0;
  ورنہ اگر (!initializer_constant_valid_p (قدر,
					  درخت_TYPE (قدر),
					  AGGREGATE_TYPE_P (constructor_type)
					  && TYPE_الٹ_STORAGE_ترتیب
					     (constructor_type))
	   || (ریکارڈ_OR_UNION_TYPE_P (constructor_type)
	       && DECL_C_ثنائی_ہندسہ_میدان (میدان_2)
	       && درخت_رمز (قدر) != INTEGER_CST))
    constructor_simple = 0;
  اگر (!maybe_const)
    constructor_nonconst = 1;

  /* Digest the initializer and issue any errors about incompatible
     types before issuing errors about non-constant initializers.  */
  درخت new_قدر = قدر;
  اگر (semantic_type)
    new_قدر = build1 (EXCESS_PRECISION_اظہاریہ, semantic_type, قدر);
  /* In the case of braces around a scalar initializer, the result of
     this initializer processing goes through digest_init again at the
     outer level.  In the case of a constexpr initializer for a
     pointer, avoid converting a null pointer constant to something
     that is not a null pointer constant to avoid a spurious error
     from that second processing.  */
  اگر (!require_constexpr_قدر
      || !npc
      || درخت_رمز (constructor_type) != اشارہ_گر_TYPE)
    new_قدر = digest_init (loc,
			     ریکارڈ_OR_UNION_TYPE_P (constructor_type)
			     ? میدان_2 : constructor_fields
			     ? constructor_fields : constructor_decl,
			     type, new_قدر, origtype, npc,
			     int_const_اظہاریہ, arith_const_اظہاریہ, strict_string,
			     require_constant_قدر, require_constexpr_قدر);
  اگر (new_قدر == error_mark_گرہ)
    {
      constructor_erroneous = 1;
      واپس;
    }
  اگر (require_constant_قدر || require_constant_elements)
    constant_عبارت_warning (new_قدر);

  /* Proceed to check the constness of the original initializer.  */
  اگر (!initializer_constant_valid_p (قدر, درخت_TYPE (قدر)))
    {
      اگر (require_constant_قدر)
	{
	  error_init (loc, "initializer element is not constant");
	  قدر = error_mark_گرہ;
	}
      ورنہ اگر (require_constant_elements)
	pedwarn (loc, OPT_Wpedantic,
		 "initializer element is not computable at load time");
    }
  ورنہ اگر (!maybe_const
	   && (require_constant_قدر || require_constant_elements))
    pedwarn_init (loc, OPT_Wpedantic,
		  "initializer element is not a constant expression");
  /* digest_init has already carried out the additional checks
     required for 'constexpr' initializers (using the information
     passed to it about whether the original initializer was certain
     kinds of constant expression), so that check does not need to be
     repeated here.  */

  /* Issue -Wc++-compat warnings about initializing a bitfield with
     enum type.  */
  اگر (warn_cxx_compat
      && میدان_2 != NULL_درخت
      && درخت_رمز (میدان_2) == میدان_DECL
      && DECL_ثنائی_ہندسہ_میدان_TYPE (میدان_2) != NULL_درخت
      && (TYPE_MAIN_VARIANT (DECL_ثنائی_ہندسہ_میدان_TYPE (میدان_2))
	  != TYPE_MAIN_VARIANT (type))
      && درخت_رمز (DECL_ثنائی_ہندسہ_میدان_TYPE (میدان_2)) == ENUMERAL_TYPE)
    {
      درخت checktype = origtype != NULL_درخت ? origtype : درخت_TYPE (قدر);
      اگر (checktype != error_mark_گرہ
	  && (TYPE_MAIN_VARIANT (checktype)
	      != TYPE_MAIN_VARIANT (DECL_ثنائی_ہندسہ_میدان_TYPE (میدان_2))))
	warning_init (loc, OPT_Wc___compat,
		      "enum conversion in initialization is invalid in C++");
    }

  /* If this field is empty and does not have side effects (and is not at
     the end of structure), don't do anything other than checking the
     initializer.  */
  اگر (میدان_2
      && (درخت_TYPE (میدان_2) == error_mark_گرہ
	  || (COMPLETE_TYPE_P (درخت_TYPE (میدان_2))
	      && integer_zerop (TYPE_سائز (درخت_TYPE (میدان_2)))
	      && !درخت_SIDE_EFFECTS (new_قدر)
	      && (درخت_رمز (constructor_type) == ARRAY_TYPE
		  || DECL_CHAIN (میدان_2)))))
    واپس;

  /* Finally, set VALUE to the initializer value digested above.  */
  قدر = new_قدر;

  /* If this element doesn't come next in sequence,
     put it on constructor_pending_elts.  */
  اگر (درخت_رمز (constructor_type) == ARRAY_TYPE
      && (!constructor_incremental
	  || !درخت_int_cst_equal (میدان_2, constructor_unfilled_اشاریہ)
	  || (درخت_رمز (قدر) == RAW_ڈیٹا_CST
	      && constructor_pending_elts
	      && pending)))
    {
      اگر (constructor_incremental
	  && (درخت_int_cst_lt (میدان_2, constructor_unfilled_اشاریہ)
	      || (درخت_رمز (قدر) == RAW_ڈیٹا_CST
		  && constructor_pending_elts
		  && pending)))
	سیٹ_nonincremental_init (braced_init_obstack);

      جوڑو_pending_init (loc, میدان_2, قدر, origtype, implicit,
			braced_init_obstack);
      واپس;
    }
  ورنہ اگر (درخت_رمز (constructor_type) == ریکارڈ_TYPE
	   && (!constructor_incremental
	       || میدان_2 != constructor_unfilled_fields))
    {
      /* We do this for records but not for unions.  In a union,
	 no matter which field is specified, it can be initialized
	 right away since it starts at the beginning of the union.  */
      اگر (constructor_incremental)
	{
	  اگر (!constructor_unfilled_fields)
	    سیٹ_nonincremental_init (braced_init_obstack);
	  ورنہ
	    {
	      درخت bitpos, unfillpos;

	      bitpos = ثنائی_ہندسہ_position (میدان_2);
	      unfillpos = ثنائی_ہندسہ_position (constructor_unfilled_fields);

	      اگر (درخت_int_cst_lt (bitpos, unfillpos))
		سیٹ_nonincremental_init (braced_init_obstack);
	    }
	}

      جوڑو_pending_init (loc, میدان_2, قدر, origtype, implicit,
			braced_init_obstack);
      واپس;
    }
  ورنہ اگر (درخت_رمز (constructor_type) == UNION_TYPE
	   && !vec_محفوظ_is_خالی_خانے (constructor_elements))
    {
      اگر (!implicit)
	{
	  اگر (درخت_SIDE_EFFECTS (constructor_elements->آخری ().قدر))
	    warning_init (loc, OPT_Woverride_init_side_effects,
			  "initialized field with side-effects overwritten");
	  ورنہ اگر (warn_override_init)
	    warning_init (loc, OPT_Woverride_init,
			  "initialized field overwritten");
	}

      /* We can have just one union field set.  */
      constructor_elements = تہی;
    }

  /* Otherwise, output this element either to
     constructor_elements or to the assembler file.  */

  constructor_elt celt = {میدان_2, قدر};
  vec_محفوظ_ڈالو (constructor_elements, celt);

  /* Advance the variable that indicates sequential elements output.  */
  اگر (درخت_رمز (constructor_type) == ARRAY_TYPE)
    {
      درخت inc = bitsize_one_گرہ;
      اگر (قدر && درخت_رمز (قدر) == RAW_ڈیٹا_CST)
	inc = bitsize_int (RAW_ڈیٹا_لمبائی (قدر));
      constructor_unfilled_اشاریہ
	= سائز_binop_loc (داخلہ_location, PLUS_اظہاریہ,
			  constructor_unfilled_اشاریہ, inc);
    }
  ورنہ اگر (درخت_رمز (constructor_type) == ریکارڈ_TYPE)
    {
      constructor_unfilled_fields
	= DECL_CHAIN (constructor_unfilled_fields);

      /* Skip any nameless bit fields.  */
      جب (constructor_unfilled_fields != NULL_درخت
	     && DECL_UNNAMED_ثنائی_ہندسہ_میدان (constructor_unfilled_fields))
	constructor_unfilled_fields
	  = DECL_CHAIN (constructor_unfilled_fields);
    }
  ورنہ اگر (درخت_رمز (constructor_type) == UNION_TYPE)
    constructor_unfilled_fields = NULL_درخت;

  /* Now output any pending elements which have become next.  */
  اگر (pending)
    output_pending_init_elements (0, braced_init_obstack);
}

/* For two FIELD_DECLs in the same chain, return -1 if field1
   comes before field2, 1 if field1 comes after field2 and
   0 if field1 == field2.  */

ساکن صحیح
init_میدان_decl_cmp (درخت field1, درخت field2)
{
  اگر (field1 == field2)
    واپس 0;

  درخت bitpos1 = ثنائی_ہندسہ_position (field1);
  درخت bitpos2 = ثنائی_ہندسہ_position (field2);
  اگر (درخت_int_cst_equal (bitpos1, bitpos2))
    {
      /* If one of the fields has non-zero bitsize, then that
	 field must be the last one in a sequence of zero
	 sized fields, fields after it will have bigger
	 bit_position.  */
      اگر (درخت_TYPE (field1) != error_mark_گرہ
	  && COMPLETE_TYPE_P (درخت_TYPE (field1))
	  && integer_nonzerop (درخت_TYPE (field1)))
	واپس 1;
      اگر (درخت_TYPE (field2) != error_mark_گرہ
	  && COMPLETE_TYPE_P (درخت_TYPE (field2))
	  && integer_nonzerop (درخت_TYPE (field2)))
	واپس -1;
      /* Otherwise, fallback to DECL_CHAIN walk to find out
	 which field comes earlier.  Walk chains of both
	 fields, so that if field1 and field2 are close to each
	 other in either order, it is found soon even for large
	 sequences of zero sized fields.  */
      درخت f1 = field1, f2 = field2;
      جب (1)
	{
	  f1 = DECL_CHAIN (f1);
	  f2 = DECL_CHAIN (f2);
	  اگر (f1 == NULL_درخت)
	    {
	      gcc_assert (f2);
	      واپس 1;
	    }
	  اگر (f2 == NULL_درخت)
	    واپس -1;
	  اگر (f1 == field2)
	    واپس -1;
	  اگر (f2 == field1)
	    واپس 1;
	  اگر (!درخت_int_cst_equal (ثنائی_ہندسہ_position (f1), bitpos1))
	    واپس 1;
	  اگر (!درخت_int_cst_equal (ثنائی_ہندسہ_position (f2), bitpos1))
	    واپس -1;
	}
    }
  ورنہ اگر (درخت_int_cst_lt (bitpos1, bitpos2))
    واپس -1;
  ورنہ
    واپس 1;
}

/* Output any pending elements which have become next.
   As we output elements, constructor_unfilled_{fields,index}
   advances, which may cause other elements to become next;
   if so, they too are output.

   If ALL is 0, we return when there are
   no more pending elements to output now.

   If ALL is 1, we output space as necessary so that
   we can output all the pending elements.  */
ساکن خالی
output_pending_init_elements (صحیح all, ساخت obstack * braced_init_obstack)
{
  ساخت init_گرہ *elt = constructor_pending_elts;
  درخت اگلا;

 retry:

  /* Look through the whole pending tree.
     If we find an element that should be output now,
     output it.  Otherwise, set NEXT to the element
     that comes first among those still pending.  */

  اگلا = NULL_درخت;
  جب (elt)
    {
      اگر (درخت_رمز (constructor_type) == ARRAY_TYPE)
	{
	  اگر (درخت_int_cst_equal (elt->purpose,
				  constructor_unfilled_اشاریہ))
	    output_init_element (داخلہ_location, elt->قدر, elt->origtype,
				 سچ, درخت_TYPE (constructor_type),
				 constructor_unfilled_اشاریہ, جھوٹ, جھوٹ,
				 braced_init_obstack);
	  ورنہ اگر (درخت_int_cst_lt (constructor_unfilled_اشاریہ,
				    elt->purpose))
	    {
	      /* Advance to the next smaller node.  */
	      اگر (elt->بائیں)
		elt = elt->بائیں;
	      ورنہ
		{
		  /* We have reached the smallest node bigger than the
		     current unfilled index.  Fill the space first.  */
		  اگلا = elt->purpose;
		  توڑو;
		}
	    }
	  ورنہ
	    {
	      /* Advance to the next bigger node.  */
	      اگر (elt->دائیں)
		elt = elt->دائیں;
	      ورنہ
		{
		  /* We have reached the biggest node in a subtree.  Find
		     the parent of it, which is the next bigger node.  */
		  جب (elt->والد && elt->والد->دائیں == elt)
		    elt = elt->والد;
		  elt = elt->والد;
		  اگر (elt && درخت_int_cst_lt (constructor_unfilled_اشاریہ,
					      elt->purpose))
		    {
		      اگلا = elt->purpose;
		      توڑو;
		    }
		}
	    }
	}
      ورنہ اگر (ریکارڈ_OR_UNION_TYPE_P (constructor_type))
	{
	  /* If the current record is complete we are done.  */
	  اگر (constructor_unfilled_fields == NULL_درخت)
	    توڑو;

	  صحیح cmp = init_میدان_decl_cmp (constructor_unfilled_fields,
					 elt->purpose);
	  اگر (cmp == 0)
	    output_init_element (داخلہ_location, elt->قدر, elt->origtype,
				 سچ, درخت_TYPE (elt->purpose),
				 elt->purpose, جھوٹ, جھوٹ,
				 braced_init_obstack);
	  ورنہ اگر (cmp < 0)
	    {
	      /* Advance to the next smaller node.  */
	      اگر (elt->بائیں)
		elt = elt->بائیں;
	      ورنہ
		{
		  /* We have reached the smallest node bigger than the
		     current unfilled field.  Fill the space first.  */
		  اگلا = elt->purpose;
		  توڑو;
		}
	    }
	  ورنہ
	    {
	      /* Advance to the next bigger node.  */
	      اگر (elt->دائیں)
		elt = elt->دائیں;
	      ورنہ
		{
		  /* We have reached the biggest node in a subtree.  Find
		     the parent of it, which is the next bigger node.  */
		  جب (elt->والد && elt->والد->دائیں == elt)
		    elt = elt->والد;
		  elt = elt->والد;
		  اگر (elt
		      && init_میدان_decl_cmp (constructor_unfilled_fields,
					      elt->purpose) < 0)
		    {
		      اگلا = elt->purpose;
		      توڑو;
		    }
		}
	    }
	}
    }

  /* Ordinarily return, but not if we want to output all
     and there are elements left.  */
  اگر (!(all && اگلا != NULL_درخت))
    واپس;

  /* If it's not incremental, just skip over the gap, so that after
     jumping to retry we will output the next successive element.  */
  اگر (ریکارڈ_OR_UNION_TYPE_P (constructor_type))
    constructor_unfilled_fields = اگلا;
  ورنہ اگر (درخت_رمز (constructor_type) == ARRAY_TYPE)
    constructor_unfilled_اشاریہ = اگلا;

  /* ELT now points to the node in the pending tree with the next
     initializer to output.  */
  جاؤ retry;
}

/* Expression VALUE coincides with the start of type TYPE in a braced
   initializer.  Return true if we should treat VALUE as initializing
   the first element of TYPE, false if we should treat it as initializing
   TYPE as a whole.

   If the initializer is clearly invalid, the question becomes:
   which choice gives the best error message?  */

ساکن منطقی
initialize_elementwise_p (درخت type, درخت قدر)
{
  اگر (type == error_mark_گرہ || قدر == error_mark_گرہ)
    واپس جھوٹ;

  gcc_checking_assert (TYPE_MAIN_VARIANT (type) == type);

  درخت قدر_type = درخت_TYPE (قدر);
  اگر (قدر_type == error_mark_گرہ)
    واپس جھوٹ;

  /* GNU vectors can be initialized elementwise.  However, treat any
     kind of vector value as initializing the vector type as a whole,
     regardless of whether the value is a GNU vector.  Such initializers
     are valid if and only if they would have been valid in a non-braced
     initializer like:

	TYPE foo = VALUE;

     so recursing into the vector type would be at best confusing or at
     worst wrong.  For example, when -flax-vector-conversions is in effect,
     it's possible to initialize a V8HI from a V4SI, even though the vectors
     have different element types and different numbers of elements.  */
  اگر (gnu_سمتیہ_type_p (type))
    واپس !سمتیہ_TYPE_P (قدر_type);

  اگر (AGGREGATE_TYPE_P (type))
    واپس !comptypes (type, TYPE_MAIN_VARIANT (قدر_type));

  واپس جھوٹ;
}

/* Helper function for process_init_element.  Split first element of
   RAW_DATA_CST and save the rest to *RAW_DATA.  */

ساکن اندرونی درخت
maybe_بانٹو_raw_ڈیٹا (درخت قدر, درخت *raw_ڈیٹا)
{
  اگر (قدر == NULL_درخت || درخت_رمز (قدر) != RAW_ڈیٹا_CST)
    واپس قدر;
  *raw_ڈیٹا = قدر;
  قدر = build_int_cst (integer_type_گرہ,
			 RAW_ڈیٹا_UCHAR_ELT (*raw_ڈیٹا, 0));
  ++RAW_ڈیٹا_اشارہ_گر (*raw_ڈیٹا);
  --RAW_ڈیٹا_لمبائی (*raw_ڈیٹا);
  واپس قدر;
}

/* Return non-zero if c_parser_initval should attempt to optimize
   large initializers into RAW_DATA_CST.  In that case return how
   many elements to optimize at most.  */

غیرعلامتی
c_maybe_optimize_large_byte_initializer (خالی)
{
  اگر (!constructor_type
      || درخت_رمز (constructor_type) != ARRAY_TYPE
      || constructor_ڈھیر->implicit)
    واپس 0;
  درخت elttype = TYPE_MAIN_VARIANT (درخت_TYPE (constructor_type));
  اگر (درخت_رمز (elttype) != INTEGER_TYPE
      && درخت_رمز (elttype) != BITINT_TYPE)
    واپس 0;
  اگر (TYPE_PRECISION (elttype) != CHAR_ثنائی_ہندسہ
      || constructor_ڈھیر->replacement_قدر.قدر
      || (COMPLETE_TYPE_P (constructor_type)
	  && !poly_int_درخت_p (TYPE_سائز (constructor_type)))
      || constructor_range_ڈھیر)
    واپس 0;
  اگر (constructor_max_اشاریہ == NULL_درخت)
    واپس زیادہ_سے_زیادہ_عدد;
  اگر (درخت_int_cst_le (constructor_max_اشاریہ, constructor_اشاریہ)
      || integer_all_onesp (constructor_max_اشاریہ))
    واپس 0;
  widest_int w = wi::مقصد_widest (constructor_max_اشاریہ);
  w -= wi::مقصد_widest (constructor_اشاریہ);
  w += 1;
  اگر (w < 64)
    واپس 0;
  اگر (w > زیادہ_سے_زیادہ_عدد)
    واپس زیادہ_سے_زیادہ_عدد;
  واپس w.مقصد_uhwi ();
}

/* Add one non-braced element to the current constructor level.
   This adjusts the current position within the constructor's type.
   This may also start or terminate implicit levels
   to handle a partly-braced initializer.

   Once this has found the correct level for the new element,
   it calls output_init_element.

   IMPLICIT is true if value comes from pop_init_level (1),
   the new initializer has been merged with the existing one
   and thus no warnings should be emitted about overriding an
   existing initializer.  */

خالی
process_init_element (location_t loc, ساخت c_اظہاریہ قدر, منطقی implicit,
		      ساخت obstack * braced_init_obstack)
{
  درخت orig_قدر = قدر.قدر;
  صحیح string_flag
    = (orig_قدر != NULL_درخت && درخت_رمز (orig_قدر) == STRING_CST);
  منطقی strict_string = قدر.original_رمز == STRING_CST;
  منطقی was_designated = designator_گہرائی != 0;
  درخت raw_ڈیٹا = NULL_درخت;

retry:
  designator_گہرائی = 0;
  designator_erroneous = 0;

  اگر (!implicit && قدر.قدر && !integer_zerop (قدر.قدر))
    constructor_zeroinit = 0;

  /* Handle superfluous braces around string cst as in
     char x[] = {"foo"}; */
  اگر (constructor_type
      && !was_designated
      && درخت_رمز (constructor_type) == ARRAY_TYPE
      && INTEGRAL_TYPE_P (درخت_TYPE (constructor_type))
      && integer_zerop (constructor_unfilled_اشاریہ))
    {
      اگر (constructor_ڈھیر->replacement_قدر.قدر)
	{
	  error_init (loc, "excess elements in %qT initializer", constructor_type);
	  واپس;
	}
      ورنہ اگر (string_flag)
	{
	  constructor_ڈھیر->replacement_قدر = قدر;
	  واپس;
	}
    }

  اگر (constructor_ڈھیر->replacement_قدر.قدر != NULL_درخت)
    {
      error_init (loc, "excess elements in struct initializer");
      واپس;
    }

  /* Ignore elements of a brace group if it is entirely superfluous
     and has already been diagnosed, or if the type is erroneous.  */
  اگر (constructor_type == NULL_درخت || constructor_type == error_mark_گرہ)
    واپس;

  /* Ignore elements of an initializer for a variable-size type.
     Those are diagnosed in the parser (empty initializer braces are OK).  */
  اگر (COMPLETE_TYPE_P (constructor_type)
      && !poly_int_درخت_p (TYPE_سائز (constructor_type)))
    واپس;

  اگر (!implicit && warn_designated_init && !was_designated
      && درخت_رمز (constructor_type) == ریکارڈ_TYPE
      && lookup_attribute ("designated_init",
			   TYPE_اوصاف (constructor_type)))
    warning_init (loc,
		  OPT_Wdesignated_init,
		  "positional initialization of field "
		  "in %<struct%> declared with %<designated_init%> attribute");

  /* If we've exhausted any levels that didn't have braces,
     pop them now.  */
  جب (constructor_ڈھیر->implicit)
    {
      اگر (ریکارڈ_OR_UNION_TYPE_P (constructor_type)
	  && constructor_fields == NULL_درخت)
	process_init_element (loc,
			      نکالو_init_level (loc, 1, braced_init_obstack,
					      آخری_init_list_comma),
			      سچ, braced_init_obstack);
      ورنہ اگر ((درخت_رمز (constructor_type) == ARRAY_TYPE
		|| gnu_سمتیہ_type_p (constructor_type))
	       && constructor_max_اشاریہ
	       && درخت_int_cst_lt (constructor_max_اشاریہ,
				   constructor_اشاریہ))
	process_init_element (loc,
			      نکالو_init_level (loc, 1, braced_init_obstack,
					      آخری_init_list_comma),
			      سچ, braced_init_obstack);
      ورنہ
	توڑو;
    }

  /* In the case of [LO ... HI] = VALUE, only evaluate VALUE once.  */
  اگر (constructor_range_ڈھیر)
    {
      /* If value is a compound literal and we'll be just using its
	 content, don't put it into a SAVE_EXPR.  */
      اگر (درخت_رمز (قدر.قدر) != COMPOUND_LITERAL_اظہاریہ
	  || !require_constant_قدر)
	{
	  درخت semantic_type = NULL_درخت;
	  اگر (درخت_رمز (قدر.قدر) == EXCESS_PRECISION_اظہاریہ)
	    {
	      semantic_type = درخت_TYPE (قدر.قدر);
	      قدر.قدر = درخت_عملیہ (قدر.قدر, 0);
	    }
	  قدر.قدر = save_اظہاریہ (قدر.قدر);
	  اگر (semantic_type)
	    قدر.قدر = build1 (EXCESS_PRECISION_اظہاریہ, semantic_type,
				  قدر.قدر);
	}
    }

  جب (1)
    {
      اگر (درخت_رمز (constructor_type) == ریکارڈ_TYPE)
	{
	  درخت fieldtype;
	  شمار درخت_رمز_2 fieldcode;

	  اگر (constructor_fields == NULL_درخت)
	    {
	      pedwarn_init (loc, 0, "excess elements in struct initializer");
	      توڑو;
	    }

	  fieldtype = درخت_TYPE (constructor_fields);
	  اگر (fieldtype != error_mark_گرہ)
	    fieldtype = TYPE_MAIN_VARIANT (fieldtype);
	  fieldcode = درخت_رمز (fieldtype);

	  /* Error for non-static initialization of a flexible array member.  */
	  اگر (fieldcode == ARRAY_TYPE
	      && !require_constant_قدر
	      && TYPE_سائز (fieldtype) == NULL_درخت
	      && DECL_CHAIN (constructor_fields) == NULL_درخت)
	    {
	      error_init (loc, "non-static initialization of a flexible "
			  "array member");
	      توڑو;
	    }

	  /* Error for initialization of a flexible array member with
	     a string constant if the structure is in an array.  E.g.:
	     struct S { int x; char y[]; };
	     struct S s[] = { { 1, "foo" } };
	     is invalid.  */
	  اگر (string_flag
	      && fieldcode == ARRAY_TYPE
	      && constructor_گہرائی > 1
	      && TYPE_سائز (fieldtype) == NULL_درخت
	      && DECL_CHAIN (constructor_fields) == NULL_درخت)
	    {
	      منطقی اندر_array_p = جھوٹ;
	      برائے (ساخت constructor_ڈھیر *p = constructor_ڈھیر;
		   p && p->type; p = p->اگلا)
		اگر (درخت_رمز (p->type) == ARRAY_TYPE)
		  {
		    اندر_array_p = سچ;
		    توڑو;
		  }
	      اگر (اندر_array_p)
		{
		  error_init (loc, "initialization of flexible array "
			      "member in a nested context");
		  توڑو;
		}
	    }

	  /* Accept a string constant to initialize a subarray.  */
	  اگر (قدر.قدر != NULL_درخت
	      && fieldcode == ARRAY_TYPE
	      && INTEGRAL_TYPE_P (درخت_TYPE (fieldtype))
	      && string_flag)
	    قدر.قدر = orig_قدر;
	  /* Otherwise, if we have come to a subaggregate,
	     and we don't have an element of its type, push into it.  */
	  ورنہ اگر (قدر.قدر != NULL_درخت
		   && initialize_elementwise_p (fieldtype, قدر.قدر))
	    {
	      ڈالو_init_level (loc, 1, braced_init_obstack);
	      جاری;
	    }

	  قدر.قدر = maybe_بانٹو_raw_ڈیٹا (قدر.قدر, &raw_ڈیٹا);
	  اگر (قدر.قدر)
	    {
	      ڈالو_member_name (constructor_fields);
	      output_init_element (loc, قدر.قدر, قدر.original_type,
				   strict_string, fieldtype,
				   constructor_fields, سچ, implicit,
				   braced_init_obstack);
	      RESTORE_SPELLING_گہرائی (constructor_گہرائی);
	    }
	  ورنہ
	    /* Do the bookkeeping for an element that was
	       directly output as a constructor.  */
	    {
	      /* For a record, keep track of end position of last field.  */
	      اگر (DECL_سائز (constructor_fields))
		constructor_ثنائی_ہندسہ_اشاریہ
		  = سائز_binop_loc (داخلہ_location, PLUS_اظہاریہ,
				    ثنائی_ہندسہ_position (constructor_fields),
				    DECL_سائز (constructor_fields));

	      /* If the current field was the first one not yet written out,
		 it isn't now, so update.  */
	      اگر (constructor_unfilled_fields == constructor_fields)
		{
		  constructor_unfilled_fields = DECL_CHAIN (constructor_fields);
		  /* Skip any nameless bit fields.  */
		  جب (constructor_unfilled_fields != 0
			 && (DECL_UNNAMED_ثنائی_ہندسہ_میدان
			     (constructor_unfilled_fields)))
		    constructor_unfilled_fields =
		      DECL_CHAIN (constructor_unfilled_fields);
		}
	    }

	  constructor_fields = DECL_CHAIN (constructor_fields);
	  /* Skip any nameless bit fields at the beginning.  */
	  جب (constructor_fields != NULL_درخت
		 && DECL_UNNAMED_ثنائی_ہندسہ_میدان (constructor_fields))
	    constructor_fields = DECL_CHAIN (constructor_fields);
	}
      ورنہ اگر (درخت_رمز (constructor_type) == UNION_TYPE)
	{
	  درخت fieldtype;
	  شمار درخت_رمز_2 fieldcode;

	  اگر (constructor_fields == NULL_درخت)
	    {
	      pedwarn_init (loc, 0,
			    "excess elements in union initializer");
	      توڑو;
	    }

	  fieldtype = درخت_TYPE (constructor_fields);
	  اگر (fieldtype != error_mark_گرہ)
	    fieldtype = TYPE_MAIN_VARIANT (fieldtype);
	  fieldcode = درخت_رمز (fieldtype);

	  /* Warn that traditional C rejects initialization of unions.
	     We skip the warning if the value is zero.  This is done
	     under the assumption that the zero initializer in user
	     code appears conditioned on e.g. __STDC__ to avoid
	     "missing initializer" warnings and relies on default
	     initialization to zero in the traditional C case.
	     We also skip the warning if the initializer is designated,
	     again on the assumption that this must be conditional on
	     __STDC__ anyway (and we've already complained about the
	     member-designator already).  */
	  اگر (!اندر_system_سرخی_at (داخلہ_location) && !constructor_designated
	      && !(قدر.قدر && (integer_zerop (قدر.قدر)
				   || real_zerop (قدر.قدر))))
	    warning (OPT_Wtraditional, "traditional C rejects initialization "
		     "of unions");

	  /* Error for non-static initialization of a flexible array member.  */
	  اگر (fieldcode == ARRAY_TYPE
	      && !require_constant_قدر
	      && TYPE_سائز (fieldtype) == NULL_درخت)
	    {
	      error_init (loc, "non-static initialization of a flexible "
			  "array member");
	      توڑو;
	    }

	  /* Error for initialization of a flexible array member with
	     a string constant if the structure is in an array.  E.g.:
	     union U { int x; char y[]; };
	     union U s[] = { { 1, "foo" } };
	     is invalid.  */
	  اگر (string_flag
	      && fieldcode == ARRAY_TYPE
	      && constructor_گہرائی > 1
	      && TYPE_سائز (fieldtype) == NULL_درخت)
	    {
	      منطقی اندر_array_p = جھوٹ;
	      برائے (ساخت constructor_ڈھیر *p = constructor_ڈھیر;
		   p && p->type; p = p->اگلا)
		اگر (درخت_رمز (p->type) == ARRAY_TYPE)
		  {
		    اندر_array_p = سچ;
		    توڑو;
		  }
	      اگر (اندر_array_p)
		{
		  error_init (loc, "initialization of flexible array "
			      "member in a nested context");
		  توڑو;
		}
	    }

	  /* Accept a string constant to initialize a subarray.  */
	  اگر (قدر.قدر != NULL_درخت
	      && fieldcode == ARRAY_TYPE
	      && INTEGRAL_TYPE_P (درخت_TYPE (fieldtype))
	      && string_flag)
	    قدر.قدر = orig_قدر;
	  /* Otherwise, if we have come to a subaggregate,
	     and we don't have an element of its type, push into it.  */
	  ورنہ اگر (قدر.قدر != NULL_درخت
		   && initialize_elementwise_p (fieldtype, قدر.قدر))
	    {
	      ڈالو_init_level (loc, 1, braced_init_obstack);
	      جاری;
	    }

	  قدر.قدر = maybe_بانٹو_raw_ڈیٹا (قدر.قدر, &raw_ڈیٹا);
	  اگر (قدر.قدر)
	    {
	      ڈالو_member_name (constructor_fields);
	      output_init_element (loc, قدر.قدر, قدر.original_type,
				   strict_string, fieldtype,
				   constructor_fields, سچ, implicit,
				   braced_init_obstack);
	      RESTORE_SPELLING_گہرائی (constructor_گہرائی);
	    }
	  ورنہ
	    /* Do the bookkeeping for an element that was
	       directly output as a constructor.  */
	    {
	      constructor_ثنائی_ہندسہ_اشاریہ = DECL_سائز (constructor_fields);
	      constructor_unfilled_fields = DECL_CHAIN (constructor_fields);
	    }

	  constructor_fields = NULL_درخت;
	}
      ورنہ اگر (درخت_رمز (constructor_type) == ARRAY_TYPE)
	{
	  درخت elttype = TYPE_MAIN_VARIANT (درخت_TYPE (constructor_type));
	  شمار درخت_رمز_2 eltcode = درخت_رمز (elttype);

	  /* Accept a string constant to initialize a subarray.  */
	  اگر (قدر.قدر != NULL_درخت
	      && eltcode == ARRAY_TYPE
	      && INTEGRAL_TYPE_P (درخت_TYPE (elttype))
	      && string_flag)
	    قدر.قدر = orig_قدر;
	  /* Otherwise, if we have come to a subaggregate,
	     and we don't have an element of its type, push into it.  */
	  ورنہ اگر (قدر.قدر != NULL_درخت
		   && initialize_elementwise_p (elttype, قدر.قدر))
	    {
	      ڈالو_init_level (loc, 1, braced_init_obstack);
	      جاری;
	    }

	  اگر (constructor_max_اشاریہ != NULL_درخت
	      && (درخت_int_cst_lt (constructor_max_اشاریہ, constructor_اشاریہ)
		  || integer_all_onesp (constructor_max_اشاریہ))
	      /* For VLA we got an error already.  */
	      && !C_TYPE_VARIABLE_سائز (constructor_type))
	    {
	      pedwarn_init (loc, 0,
			    "excess elements in array initializer");
	      توڑو;
	    }

	  اگر (قدر.قدر
	      && درخت_رمز (قدر.قدر) == RAW_ڈیٹا_CST
	      && RAW_ڈیٹا_لمبائی (قدر.قدر) > 1
	      && (درخت_رمز (elttype) == INTEGER_TYPE
		  || درخت_رمز (elttype) == BITINT_TYPE)
	      && TYPE_PRECISION (elttype) == CHAR_ثنائی_ہندسہ
	      && (constructor_max_اشاریہ == NULL_درخت
		  || درخت_int_cst_lt (constructor_اشاریہ,
				      constructor_max_اشاریہ)))
	    {
	      غیرعلامتی صحیح len = RAW_ڈیٹا_لمبائی (قدر.قدر);
	      اگر (constructor_max_اشاریہ)
		{
		  widest_int w = wi::مقصد_widest (constructor_max_اشاریہ);
		  w -= wi::مقصد_widest (constructor_اشاریہ);
		  w += 1;
		  اگر (w < len)
		    len = w.مقصد_uhwi ();
		}
	      اگر (len < (غیرعلامتی) RAW_ڈیٹا_لمبائی (قدر.قدر))
		{
		  raw_ڈیٹا = copy_گرہ (قدر.قدر);
		  RAW_ڈیٹا_لمبائی (raw_ڈیٹا) -= len;
		  RAW_ڈیٹا_اشارہ_گر (raw_ڈیٹا) += len;
		  RAW_ڈیٹا_لمبائی (قدر.قدر) = len;
		}
	      درخت_TYPE (قدر.قدر) = elttype;
	      ڈالو_array_bounds (درخت_مقصد_uhwi (constructor_اشاریہ));
	      output_init_element (loc, قدر.قدر, قدر.original_type,
				   جھوٹ, elttype, constructor_اشاریہ, سچ,
				   implicit, braced_init_obstack);
	      RESTORE_SPELLING_گہرائی (constructor_گہرائی);
	      constructor_اشاریہ
		= سائز_binop_loc (داخلہ_location, PLUS_اظہاریہ,
				  constructor_اشاریہ, bitsize_int (len));
	    }
	  ورنہ
	    {
	      قدر.قدر = maybe_بانٹو_raw_ڈیٹا (قدر.قدر, &raw_ڈیٹا);
	      /* Now output the actual element.  */
	      اگر (قدر.قدر)
		{
		  ڈالو_array_bounds (درخت_مقصد_uhwi (constructor_اشاریہ));
		  output_init_element (loc, قدر.قدر, قدر.original_type,
				       strict_string, elttype,
				       constructor_اشاریہ, سچ, implicit,
				       braced_init_obstack);
		  RESTORE_SPELLING_گہرائی (constructor_گہرائی);
		}

	      constructor_اشاریہ
		= سائز_binop_loc (داخلہ_location, PLUS_اظہاریہ,
				  constructor_اشاریہ, bitsize_one_گرہ);

	      اگر (!قدر.قدر)
		/* If we are doing the bookkeeping for an element that was
		   directly output as a constructor, we must update
		   constructor_unfilled_index.  */
		constructor_unfilled_اشاریہ = constructor_اشاریہ;
	    }
	}
      ورنہ اگر (gnu_سمتیہ_type_p (constructor_type))
	{
	  درخت elttype = TYPE_MAIN_VARIANT (درخت_TYPE (constructor_type));

	  /* Do a basic check of initializer size.  Note that vectors
	     may not always have a fixed size derived from their type.  */
	  اگر (maybe_lt (درخت_مقصد_poly_uint64 (constructor_max_اشاریہ),
			درخت_مقصد_poly_uint64 (constructor_اشاریہ)))
	    {
	      /* Diagose VLA out-of-bounds as errors.  */
	      اگر (درخت_مقصد_poly_uint64 (constructor_max_اشاریہ).is_constant())
		pedwarn_init (loc, 0,
			      "excess elements in vector initializer");
	      ورنہ
		error_init (loc, "excess elements in vector initializer");

	      توڑو;
	    }

	  قدر.قدر = maybe_بانٹو_raw_ڈیٹا (قدر.قدر, &raw_ڈیٹا);
	  /* Now output the actual element.  */
	  اگر (قدر.قدر)
	    {
	      اگر (درخت_رمز (قدر.قدر) == سمتیہ_CST)
		elttype = TYPE_MAIN_VARIANT (constructor_type);
	      output_init_element (loc, قدر.قدر, قدر.original_type,
				   strict_string, elttype,
				   constructor_اشاریہ, سچ, implicit,
				   braced_init_obstack);
	    }

	  constructor_اشاریہ
	    = سائز_binop_loc (داخلہ_location,
			      PLUS_اظہاریہ, constructor_اشاریہ, bitsize_one_گرہ);

	  اگر (!قدر.قدر)
	    /* If we are doing the bookkeeping for an element that was
	       directly output as a constructor, we must update
	       constructor_unfilled_index.  */
	    constructor_unfilled_اشاریہ = constructor_اشاریہ;
	}

      /* Handle the sole element allowed in a braced initializer
	 for a scalar variable.  */
      ورنہ اگر (constructor_type != error_mark_گرہ
	       && constructor_fields == NULL_درخت)
	{
	  pedwarn_init (loc, 0,
			"excess elements in scalar initializer");
	  توڑو;
	}
      ورنہ
	{
	  قدر.قدر = maybe_بانٹو_raw_ڈیٹا (قدر.قدر, &raw_ڈیٹا);
	  اگر (قدر.قدر)
	    output_init_element (loc, قدر.قدر, قدر.original_type,
				 strict_string, constructor_type,
				 NULL_درخت, سچ, implicit,
				 braced_init_obstack);
	  constructor_fields = NULL_درخت;
	}

      /* Handle range initializers either at this level or anywhere higher
	 in the designator stack.  */
      اگر (constructor_range_ڈھیر)
	{
	  ساخت constructor_range_ڈھیر *p, *range_ڈھیر;
	  صحیح اختتام = 0;

	  range_ڈھیر = constructor_range_ڈھیر;
	  constructor_range_ڈھیر = 0;
	  جب (constructor_ڈھیر != range_ڈھیر->ڈھیر)
	    {
	      gcc_assert (constructor_ڈھیر->implicit);
	      process_init_element (loc,
				    نکالو_init_level (loc, 1,
						    braced_init_obstack,
						    آخری_init_list_comma),
				    سچ, braced_init_obstack);
	    }
	  برائے (p = range_ڈھیر;
	       !p->range_انتہا || درخت_int_cst_equal (p->اشاریہ, p->range_انتہا);
	       p = p->پچھلا)
	    {
	      gcc_assert (constructor_ڈھیر->implicit);
	      process_init_element (loc,
				    نکالو_init_level (loc, 1,
						    braced_init_obstack,
						    آخری_init_list_comma),
				    سچ, braced_init_obstack);
	    }

	  p->اشاریہ = سائز_binop_loc (داخلہ_location,
				     PLUS_اظہاریہ, p->اشاریہ, bitsize_one_گرہ);
	  اگر (درخت_int_cst_equal (p->اشاریہ, p->range_انتہا) && !p->پچھلا)
	    اختتام = 1;

	  جب (1)
	    {
	      constructor_اشاریہ = p->اشاریہ;
	      constructor_fields = p->fields;
	      اگر (اختتام && p->range_انتہا && p->اشاریہ == p->range_آغاز)
		{
		  اختتام = 0;
		  p->پچھلا = 0;
		}
	      p = p->اگلا;
	      اگر (!p)
		توڑو;
	      اختتام_implicit_inits (loc, braced_init_obstack);
	      ڈالو_init_level (loc, 2, braced_init_obstack);
	      p->ڈھیر = constructor_ڈھیر;
	      اگر (p->range_انتہا && درخت_int_cst_equal (p->اشاریہ, p->range_انتہا))
		p->اشاریہ = p->range_آغاز;
	    }

	  اگر (!اختتام)
	    constructor_range_ڈھیر = range_ڈھیر;
	  جاری;
	}

      توڑو;
    }

  constructor_range_ڈھیر = 0;

  اگر (raw_ڈیٹا && RAW_ڈیٹا_لمبائی (raw_ڈیٹا))
    {
      gcc_assert (!string_flag && !was_designated);
      قدر.قدر = raw_ڈیٹا;
      raw_ڈیٹا = NULL_درخت;
      جاؤ retry;
    }
}

/* Build a complete asm-statement, whose components are a CV_QUALIFIER
   (guaranteed to be 'volatile' or null) and ARGS (represented using
   an ASM_EXPR node).  */
درخت
build_asm_stmt (منطقی is_volatile, درخت دلائل)
{
  اگر (is_volatile)
    ASM_VOLATILE_P (دلائل) = 1;
  واپس جوڑو_stmt (دلائل);
}

/* Build an asm-expr, whose components are a STRING, some OUTPUTS,
   some INPUTS, and some CLOBBERS.  The latter three may be NULL.
   SIMPLE indicates whether there was anything at all after the
   string in the asm expression -- asm("blah") and asm("blah" : )
   are subtly different.  We use a ASM_EXPR node to represent this.
   LOC is the location of the asm, and IS_INLINE says whether this
   is asm inline.  */
درخت
build_asm_اظہاریہ (location_t loc, درخت string, درخت outputs, درخت inputs,
		درخت clobbers, درخت labels, منطقی simple, منطقی is_inline)
{
  درخت دم;
  درخت دلائل;
  صحیح i;
  ثابت حرف *constraint;
  ثابت حرف **oconstraints;
  منطقی allows_mem, allows_reg, is_inout;
  صحیح ninputs, noutputs;

  ninputs = list_لمبائی (inputs);
  noutputs = list_لمبائی (outputs);
  oconstraints = (ثابت حرف **) alloca (noutputs * حجم (ثابت حرف *));

  string = resolve_asm_عملیہ_نام (string, outputs, inputs, labels);

  /* Remove output conversions that change the type but not the mode.  */
  برائے (i = 0, دم = outputs; دم; ++i, دم = درخت_CHAIN (دم))
    {
      درخت output = درخت_قدر (دم);

      output = c_fully_fold (output, جھوٹ, تہی, سچ);

      /* ??? Really, this should not be here.  Users should be using a
	 proper lvalue, dammit.  But there's a long history of using casts
	 in the output operands.  In cases like longlong.h, this becomes a
	 primitive form of typechecking -- if the cast can be removed, then
	 the output operand had a type of the proper width; otherwise we'll
	 get an error.  Gross, but ...  */
      STRIP_NOPS (output);

      اگر (!lvalue_or_else (loc, output, lv_asm))
	output = error_mark_گرہ;

      اگر (output != error_mark_گرہ
	  && (درخت_READONLY (output)
	      || TYPE_READONLY (درخت_TYPE (output))
	      || (ریکارڈ_OR_UNION_TYPE_P (درخت_TYPE (output))
		  && C_TYPE_FIELDS_READONLY (درخت_TYPE (output)))))
	readonly_error (loc, output, lv_asm);

      constraint = درخت_STRING_اشارہ_گر (درخت_قدر (درخت_PURPOSE (دم)));
      oconstraints[i] = constraint;

      اگر (parse_output_constraint (&constraint, i, ninputs, noutputs,
				   &allows_mem, &allows_reg, &is_inout,
				   خالی_اشاریہ))
	{
	  /* If the operand is going to end up in memory,
	     mark it addressable.  */
	  اگر (!allows_reg && !c_mark_addressable (output))
	    output = error_mark_گرہ;
	  اگر (!(!allows_reg && allows_mem)
	      && output != error_mark_گرہ
	      && VOID_TYPE_P (درخت_TYPE (output)))
	    {
	      error_at (loc, "invalid use of void expression");
	      output = error_mark_گرہ;
	    }
	  اگر (allows_reg && current_function_decl == NULL_درخت)
	    {
	      error_at (loc, "constraint allows registers outside of "
			     "a function");
	      output = error_mark_گرہ;
	    }
	}
      ورنہ
	output = error_mark_گرہ;

      اگر (current_function_decl == NULL_درخت && output != error_mark_گرہ)
	{
	  اگر (درخت_SIDE_EFFECTS (output))
	    {
	      error_at (loc, "side-effects in output operand outside "
			     "of a function");
	      output = error_mark_گرہ;
	    }
	  ورنہ
	    {
	      درخت addr = build_unary_op (loc, ADDR_اظہاریہ, output, جھوٹ);
	      اگر (addr == error_mark_گرہ)
		output = error_mark_گرہ;
	      ورنہ اگر (!initializer_constant_valid_p (addr, درخت_TYPE (addr)))
		{
		  error_at (loc, "output operand outside of a function is not "
				 "constant");
		  output = error_mark_گرہ;
		}
	    }
	}
      ورنہ اگر (output != error_mark_گرہ && لڑی_تلاش (constraint, "-"))
	{
	  error_at (loc, "%<-%> modifier used inside of a function");
	  output = error_mark_گرہ;
	}

      درخت_قدر (دم) = output;
    }

  برائے (i = 0, دم = inputs; دم; ++i, دم = درخت_CHAIN (دم))
    {
      درخت داخلہ;

      constraint = درخت_STRING_اشارہ_گر (درخت_قدر (درخت_PURPOSE (دم)));
      داخلہ = درخت_قدر (دم);

      اگر (parse_داخلہ_constraint (&constraint, i, ninputs, noutputs, 0,
				  oconstraints, &allows_mem, &allows_reg,
				  خالی_اشاریہ))
	{
	  /* If the operand is going to end up in memory,
	     mark it addressable.  */
	  اگر (!allows_reg && allows_mem)
	    {
	      داخلہ = c_fully_fold (داخلہ, جھوٹ, تہی, سچ);

	      /* Strip the nops as we allow this case.  FIXME, this really
		 should be rejected or made deprecated.  */
	      STRIP_NOPS (داخلہ);
	      اگر (!c_mark_addressable (داخلہ))
		داخلہ = error_mark_گرہ;
	    }
	  ورنہ
	    {
	      داخلہ = c_fully_fold (convert_lvalue_مقصد_rvalue (loc, داخلہ,
							      سچ, جھوٹ),
				    جھوٹ, تہی);

	      اگر (داخلہ != error_mark_گرہ && VOID_TYPE_P (درخت_TYPE (داخلہ)))
		{
		  error_at (loc, "invalid use of void expression");
		  داخلہ = error_mark_گرہ;
		}
	    }
	  اگر (allows_reg && current_function_decl == NULL_درخت)
	    {
	      error_at (loc, "constraint allows registers outside of "
			     "a function");
	      داخلہ = error_mark_گرہ;
	    }
	  اگر (constraint[0] == ':' && داخلہ != error_mark_گرہ)
	    {
	      درخت t = داخلہ;
	      STRIP_NOPS (t);
	      اگر (درخت_رمز (t) != ADDR_اظہاریہ
		  || !(درخت_رمز (درخت_عملیہ (t, 0)) == FUNCTION_DECL
		       || (VAR_P (درخت_عملیہ (t, 0))
			   && is_global_var (درخت_عملیہ (t, 0)))))
		{
		  error_at (loc, "%<:%> constraint operand is not address "
				 "of a function or non-automatic variable");
		  داخلہ = error_mark_گرہ;
		}
	      ورنہ اگر (درخت_رمز (درخت_عملیہ (t, 0)) == FUNCTION_DECL)
		suppress_warning (درخت_عملیہ (t, 0), OPT_Wunused);
	    }
	}
      ورنہ
	داخلہ = error_mark_گرہ;

      اگر (current_function_decl == NULL_درخت && داخلہ != error_mark_گرہ)
	{
	  اگر (درخت_SIDE_EFFECTS (داخلہ))
	    {
	      error_at (loc, "side-effects in input operand outside "
			     "of a function");
	      داخلہ = error_mark_گرہ;
	    }
	  ورنہ
	    {
	      درخت tem = داخلہ;
	      اگر (allows_mem && lvalue_p (داخلہ))
		tem = build_unary_op (loc, ADDR_اظہاریہ, داخلہ, جھوٹ);
	      اگر (!initializer_constant_valid_p (tem, درخت_TYPE (tem)))
		{
		  error_at (loc, "input operand outside of a function is not "
				 "constant");
		  داخلہ = error_mark_گرہ;
		}
	    }
	}
      ورنہ اگر (داخلہ != error_mark_گرہ && لڑی_تلاش (constraint, "-"))
	{
	  error_at (loc, "%<-%> modifier used inside of a function");
	  داخلہ = error_mark_گرہ;
	}

      درخت_قدر (دم) = داخلہ;
    }

  دلائل = build_stmt (loc, ASM_اظہاریہ, string, outputs, inputs, clobbers, labels);

  /* asm statements without outputs, including simple ones, are treated
     as volatile.  */
  ASM_BASIC_P (دلائل) = simple;
  ASM_VOLATILE_P (دلائل) = (noutputs == 0);
  ASM_INLINE_P (دلائل) = is_inline;

  واپس دلائل;
}

/* Generate a goto statement to LABEL.  LOC is the location of the
   GOTO.  */

درخت
c_اختتام_goto_label (location_t loc, درخت label)
{
  درخت decl = lookup_label_for_goto (loc, label);
  اگر (!decl)
    واپس NULL_درخت;
  درخت_مستعمل (decl) = 1;
  mark_decl_مستعمل (decl, جھوٹ);
  {
    جوڑو_stmt (build_predict_اظہاریہ (PRED_GOTO, NOT_لیا_گیا));
    درخت t = build1 (GOTO_اظہاریہ, void_type_گرہ, decl);
    سیٹ_اظہاریہ_LOCATION (t, loc);
    واپس جوڑو_stmt (t);
  }
}

/* Generate a computed goto statement to EXPR.  LOC is the location of
   the GOTO.  */

درخت
c_اختتام_goto_ptr (location_t loc, c_اظہاریہ val)
{
  درخت اظہاریہ = val.قدر;
  درخت t;
  pedwarn (loc, OPT_Wpedantic, "ISO C forbids %<goto *expr;%>");
  اگر (اظہاریہ != error_mark_گرہ
      && !اشارہ_گر_TYPE_P (درخت_TYPE (اظہاریہ))
      && !null_اشارہ_گر_constant_p (اظہاریہ))
    {
      error_at (val.get_location (),
		"computed goto must be pointer type");
      اظہاریہ = build_zero_cst (ptr_type_گرہ);
    }
  اظہاریہ = c_fully_fold (اظہاریہ, جھوٹ, تہی);
  اظہاریہ = convert (ptr_type_گرہ, اظہاریہ);
  t = build1 (GOTO_اظہاریہ, void_type_گرہ, اظہاریہ);
  سیٹ_اظہاریہ_LOCATION (t, loc);
  واپس جوڑو_stmt (t);
}

/* Generate a C `return' statement.  RETVAL is the expression for what
   to return, or a null pointer for `return;' with no value.  LOC is
   the location of the return statement, or the location of the expression,
   if the statement has any.  If ORIGTYPE is not NULL_TREE, it
   is the original type of RETVAL.  MUSTTAIL_P indicates a musttail
   attribute.  */

درخت
c_اختتام_return (location_t loc, درخت retval, درخت origtype, منطقی musttail_p)
{
  درخت valtype = درخت_TYPE (درخت_TYPE (current_function_decl)), ret_stmt;
  منطقی no_warning = جھوٹ;
  منطقی npc = جھوٹ;

  /* Use the expansion point to handle cases such as returning NULL
     in a function returning void.  */
  location_t xloc = expansion_نقطہ_location_if_اندر_system_سرخی (loc);

  اگر (درخت_THIS_VOLATILE (current_function_decl))
    warning_at (xloc, 0,
		"function declared %<noreturn%> has a %<return%> statement");

  سیٹ_musttail_on_return (retval, xloc, musttail_p);

  اگر (retval)
    {
      درخت semantic_type = NULL_درخت;
      npc = null_اشارہ_گر_constant_p (retval);
      اگر (درخت_رمز (retval) == EXCESS_PRECISION_اظہاریہ)
	{
	  semantic_type = درخت_TYPE (retval);
	  retval = درخت_عملیہ (retval, 0);
	}
      retval = c_fully_fold (retval, جھوٹ, تہی);
      اگر (semantic_type
	  && valtype != NULL_درخت
	  && درخت_رمز (valtype) != VOID_TYPE)
	retval = build1 (EXCESS_PRECISION_اظہاریہ, semantic_type, retval);
    }

  اگر (!retval)
    {
      current_function_returns_null = 1;
      اگر ((warn_return_type >= 0 || flag_isoc99)
	  && valtype != NULL_درخت && درخت_رمز (valtype) != VOID_TYPE)
	{
	  no_warning = سچ;
	  اگر (emit_diagnostic (flag_isoc99
			       ? diagnostics::قسم::permerror
			       : diagnostics::قسم::warning,
			       loc, OPT_Wreturn_mismatch,
			       "%<return%> with no value,"
			       " in function returning non-void"))
	    inform (DECL_ماخذ_LOCATION (current_function_decl),
		    "declared here");
	}
    }
  ورنہ اگر (valtype == NULL_درخت || VOID_TYPE_P (valtype))
    {
      current_function_returns_null = 1;
      منطقی warned_یہاں;
      اگر (درخت_رمز (درخت_TYPE (retval)) != VOID_TYPE)
	warned_یہاں = permerror_opt
	  (xloc, OPT_Wreturn_mismatch,
	   "%<return%> with a value, in function returning void");
      ورنہ
	warned_یہاں = pedwarn
	  (xloc, OPT_Wpedantic, "ISO C forbids "
	   "%<return%> with expression, in function returning void");
      اگر (warned_یہاں)
	inform (DECL_ماخذ_LOCATION (current_function_decl),
		"declared here");
    }
  ورنہ
    {
      درخت t = convert_for_assignment (loc, UNKNOWN_LOCATION, valtype,
				       retval, origtype, ic_return,
				       npc, NULL_درخت, NULL_درخت, 0);
      درخت res = DECL_نتیجہ (current_function_decl);
      درخت inner;
      منطقی save;

      current_function_returns_قدر = 1;
      اگر (t == error_mark_گرہ)
	{
	  /* Suppress -Wreturn-type for this function.  */
	  اگر (warn_return_type)
	    suppress_warning (current_function_decl, OPT_Wreturn_type);
	  واپس NULL_درخت;
	}

      save = اندر_late_ثنائی_op;
      اگر (C_BOOLEAN_TYPE_P (درخت_TYPE (res))
	  || درخت_رمز (درخت_TYPE (res)) == COMPLEX_TYPE
	  || (SCALAR_FLOAT_TYPE_P (درخت_TYPE (t))
	      && (درخت_رمز (درخت_TYPE (res)) == INTEGER_TYPE
		  || درخت_رمز (درخت_TYPE (res)) == ENUMERAL_TYPE)
	      && sanitize_flags_p (SANITIZE_FLOAT_CAST)))
        اندر_late_ثنائی_op = سچ;
      inner = t = convert (درخت_TYPE (res), t);
      اندر_late_ثنائی_op = save;

      /* Strip any conversions, additions, and subtractions, and see if
	 we are returning the address of a local variable.  Warn if so.  */
      جب (1)
	{
	  انتخاب (درخت_رمز (inner))
	    {
	    CASE_CONVERT:
	    حالت NON_LVALUE_اظہاریہ:
	    حالت PLUS_اظہاریہ:
	    حالت اشارہ_گر_PLUS_اظہاریہ:
	      inner = درخت_عملیہ (inner, 0);
	      جاری;

	    حالت MINUS_اظہاریہ:
	      /* If the second operand of the MINUS_EXPR has a pointer
		 type (or is converted from it), this may be valid, so
		 don't give a warning.  */
	      {
		درخت op1 = درخت_عملیہ (inner, 1);

		جب (!اشارہ_گر_TYPE_P (درخت_TYPE (op1))
		       && (CONVERT_اظہاریہ_P (op1)
			   || درخت_رمز (op1) == NON_LVALUE_اظہاریہ))
		  op1 = درخت_عملیہ (op1, 0);

		اگر (اشارہ_گر_TYPE_P (درخت_TYPE (op1)))
		  توڑو;

		inner = درخت_عملیہ (inner, 0);
		جاری;
	      }

	    حالت ADDR_اظہاریہ:
	      inner = درخت_عملیہ (inner, 0);

	      جب (REFERENCE_CLASS_P (inner)
		     && !بالواسطہ_REF_P (inner))
		inner = درخت_عملیہ (inner, 0);

	      اگر (DECL_P (inner)
		  && !DECL_EXTERNAL (inner)
		  && DECL_CONTEXT (inner) == current_function_decl
		  && اشارہ_گر_TYPE_P (درخت_TYPE (درخت_TYPE (current_function_decl))))
		{
		  اگر (درخت_رمز (inner) == LABEL_DECL)
		    warning_at (loc, OPT_Wreturn_local_addr,
				"function returns address of label");
		  ورنہ اگر (درخت_رمز (inner) == FUNCTION_DECL
			   && (C_FUNC_NONLOCAL_CONTEXT (inner)
			       || !DECL_INITIAL (inner)))
		    warning_at (loc, OPT_Wreturn_local_addr,
				"function returns address of nested function "
				"referencing local context");
		  ورنہ اگر (درخت_رمز (inner) != FUNCTION_DECL
			   && !درخت_STATIC (inner))
		    {
		      warning_at (loc, OPT_Wreturn_local_addr,
				  "function returns address of local variable");
		      درخت zero = build_zero_cst (درخت_TYPE (res));
		      t = build2 (COMPOUND_اظہاریہ, درخت_TYPE (res), t, zero);
		    }
		}
	      توڑو;

	    طےشدہ:
	      توڑو;
	    }

	  توڑو;
	}

      retval = build2 (MODIFY_اظہاریہ, درخت_TYPE (res), res, t);
      سیٹ_اظہاریہ_LOCATION (retval, loc);

      اگر (warn_sequence_نقطہ)
	verify_sequence_points (retval);
    }

  ret_stmt = build_stmt (loc, RETURN_اظہاریہ, retval);
  اگر (no_warning)
    suppress_warning (ret_stmt, OPT_Wreturn_type);
  واپس جوڑو_stmt (ret_stmt);
}

ساخت c_switch {
  /* The SWITCH_STMT being built.  */
  درخت switch_stmt;

  /* The original type of the testing expression, i.e. before the
     default conversion is applied.  */
  درخت orig_type;

  /* A splay-tree mapping the low element of a case range to the high
     element, or NULL_TREE if there is no high element.  Used to
     determine whether or not a new case label duplicates an old case
     label.  We need a tree, rather than simply a hash table, because
     of the GNU case range extension.  */
  splay_درخت cases;

  /* The bindings at the point of the switch.  This is used for
     warnings crossing decls when branching to a case label.  */
  ساخت c_spot_bindings *bindings;

  /* Whether the switch includes any break statements.  */
  منطقی break_stmt_نظر_آیا_p;

  /* The next node on the stack.  */
  ساخت c_switch *اگلا;

  /* Remember whether the controlling expression had boolean type
     before integer promotions for the sake of -Wswitch-bool.  */
  منطقی bool_cond_p;
};

/* A stack of the currently active switch statements.  The innermost
   switch statement is on the top of the stack.  There is no need to
   mark the stack for garbage collection because it is only active
   during the processing of the body of a function, and we never
   collect at that point.  */

ساخت c_switch *c_switch_ڈھیر;

/* Start a C switch statement, testing expression EXP.  Return the new
   SWITCH_STMT.  SWITCH_LOC is the location of the `switch'.
   SWITCH_COND_LOC is the location of the switch's condition.
   EXPLICIT_CAST_P is true if the expression EXP has an explicit cast.  */

درخت
c_آغاز_switch (location_t switch_loc,
		location_t switch_cond_loc,
		درخت قوت_نما, منطقی explicit_cast_p, درخت switch_name)
{
  درخت orig_type = error_mark_گرہ;
  منطقی bool_cond_p = جھوٹ;
  ساخت c_switch *cs;

  اگر (قوت_نما != error_mark_گرہ)
    {
      orig_type = درخت_TYPE (قوت_نما);

      اگر (!INTEGRAL_TYPE_P (orig_type))
	{
	  اگر (orig_type != error_mark_گرہ)
	    {
	      error_at (switch_cond_loc, "switch quantity not an integer");
	      orig_type = error_mark_گرہ;
	    }
	  قوت_نما = integer_zero_گرہ;
	}
      ورنہ
	{
	  درخت type = TYPE_MAIN_VARIANT (orig_type);
	  درخت e = قوت_نما;

	  /* Warn if the condition has boolean value.  */
	  جب (درخت_رمز (e) == COMPOUND_اظہاریہ)
	    e = درخت_عملیہ (e, 1);

	  اگر ((C_BOOLEAN_TYPE_P (type)
	       || truth_قدر_p (درخت_رمز (e)))
	      /* Explicit cast to int suppresses this warning.  */
	      && !(درخت_رمز (type) == INTEGER_TYPE
		   && explicit_cast_p))
	    bool_cond_p = سچ;

	  اگر (!اندر_system_سرخی_at (داخلہ_location)
	      && (type == long_integer_type_گرہ
		  || type == long_unsigned_type_گرہ))
	    warning_at (switch_cond_loc,
			OPT_Wtraditional, "%<long%> switch expression not "
			"converted to %<int%> in ISO C");

	  قوت_نما = c_fully_fold (قوت_نما, جھوٹ, تہی);
	  قوت_نما = default_conversion (قوت_نما);

	  اگر (warn_sequence_نقطہ)
	    verify_sequence_points (قوت_نما);
	}
    }

  /* Add this new SWITCH_STMT to the stack.  */
  cs = XNEW (ساخت c_switch);
  cs->switch_stmt = build_stmt (switch_loc, SWITCH_STMT, قوت_نما,
				NULL_درخت, orig_type, NULL_درخت, switch_name);
  cs->orig_type = orig_type;
  cs->cases = splay_درخت_new (case_compare, تہی, تہی);
  cs->bindings = c_get_switch_bindings ();
  cs->break_stmt_نظر_آیا_p = جھوٹ;
  cs->bool_cond_p = bool_cond_p;
  cs->اگلا = c_switch_ڈھیر;
  c_switch_ڈھیر = cs;

  واپس جوڑو_stmt (cs->switch_stmt);
}

/* Process a case label at location LOC, with attributes ATTRS.  */

درخت
do_case (location_t loc, درخت کم_قدر, درخت بلند_قدر, درخت attrs)
{
  درخت label = NULL_درخت;

  اگر (کم_قدر && درخت_رمز (کم_قدر) != INTEGER_CST)
    {
      کم_قدر = c_fully_fold (کم_قدر, جھوٹ, تہی);
      اگر (درخت_رمز (کم_قدر) == INTEGER_CST)
	pedwarn (loc, OPT_Wpedantic,
		 "case label is not an integer constant expression");
    }

  اگر (بلند_قدر && درخت_رمز (بلند_قدر) != INTEGER_CST)
    {
      بلند_قدر = c_fully_fold (بلند_قدر, جھوٹ, تہی);
      اگر (درخت_رمز (بلند_قدر) == INTEGER_CST)
	pedwarn (داخلہ_location, OPT_Wpedantic,
		 "case label is not an integer constant expression");
    }

  اگر (c_switch_ڈھیر == تہی)
    {
      اگر (کم_قدر)
	error_at (loc, "case label not within a switch statement");
      ورنہ
	error_at (loc, "%<default%> label not within a switch statement");
      واپس NULL_درخت;
    }

  اگر (c_check_switch_jump_warnings (c_switch_ڈھیر->bindings,
				    اظہاریہ_LOCATION (c_switch_ڈھیر->switch_stmt),
				    loc))
    واپس NULL_درخت;

  label = c_جوڑو_case_label (loc, c_switch_ڈھیر->cases,
			    SWITCH_STMT_COND (c_switch_ڈھیر->switch_stmt),
			    کم_قدر, بلند_قدر, attrs);
  اگر (label == error_mark_گرہ)
    label = NULL_درخت;
  واپس label;
}

/* Finish the switch statement.  TYPE is the original type of the
   controlling expression of the switch, or NULL_TREE.  */

خالی
c_اختتام_switch (درخت body, درخت type)
{
  ساخت c_switch *cs = c_switch_ڈھیر;
  location_t switch_location;

  SWITCH_STMT_BODY (cs->switch_stmt) = body;

  /* Emit warnings as needed.  */
  switch_location = اظہاریہ_LOCATION (cs->switch_stmt);
  c_do_switch_warnings (cs->cases, switch_location,
			type ? type : SWITCH_STMT_TYPE (cs->switch_stmt),
			SWITCH_STMT_COND (cs->switch_stmt), cs->bool_cond_p);
  اگر (c_switch_covers_all_cases_p (cs->cases,
				   SWITCH_STMT_TYPE (cs->switch_stmt)))
    SWITCH_STMT_ALL_CASES_P (cs->switch_stmt) = 1;
  SWITCH_STMT_NO_BREAK_P (cs->switch_stmt) = !cs->break_stmt_نظر_آیا_p;

  /* Pop the stack.  */
  c_switch_ڈھیر = cs->اگلا;
  splay_درخت_delete (cs->cases);
  c_release_switch_bindings (cs->bindings);
  XDELETE (cs);
}

/* Emit an if statement.  IF_LOCUS is the location of the 'if'.  COND,
   THEN_BLOCK and ELSE_BLOCK are expressions to be used; ELSE_BLOCK
   may be null.  */

خالی
c_اختتام_if_stmt (location_t if_locus, درخت cond, درخت then_بلاک,
		  درخت else_بلاک)
{
  درخت stmt;

  stmt = build3 (COND_اظہاریہ, void_type_گرہ, cond, then_بلاک, else_بلاک);
  سیٹ_اظہاریہ_LOCATION (stmt, if_locus);
  جوڑو_stmt (stmt);
}

درخت
c_اختتام_bc_stmt (location_t loc, درخت label, منطقی is_break, درخت name)
{
  /* In switch statements break is sometimes stylistically used after
     a return statement.  This can lead to spurious warnings about
     control reaching the end of a non-void function when it is
     inlined.  Note that we are calling block_may_fallthru with
     language specific tree nodes; this works because
     block_may_fallthru returns true when given something it does not
     understand.  */
  منطقی skip = !بلاک_may_fallthru (cur_stmt_list);

  اگر (is_break)
    انتخاب (اندر_statement & ~اندر_NAMED_STMT)
      {
      حالت 0:
	error_at (loc, "break statement not within loop or switch");
	واپس NULL_درخت;
      حالت اندر_OMP_بلاک:
	error_at (loc, "invalid exit from OpenMP structured block");
	واپس NULL_درخت;
      حالت اندر_OMP_FOR:
	error_at (loc, "break statement used with OpenMP for loop");
	واپس NULL_درخت;
      حالت اندر_ITERATION_STMT:
      حالت اندر_OBJC_FOREACH:
	توڑو;
      طےشدہ:
	gcc_assert (اندر_statement & اندر_SWITCH_STMT);
	c_switch_ڈھیر->break_stmt_نظر_آیا_p = سچ;
	توڑو;
      }
  ورنہ
    انتخاب (اندر_statement & ~(اندر_SWITCH_STMT | اندر_NAMED_STMT))
      {
      حالت 0:
	error_at (loc, "continue statement not within a loop");
	واپس NULL_درخت;
      حالت اندر_OMP_بلاک:
	error_at (loc, "invalid exit from OpenMP structured block");
	واپس NULL_درخت;
      حالت اندر_ITERATION_STMT:
      حالت اندر_OMP_FOR:
      حالت اندر_OBJC_FOREACH:
	توڑو;
      طےشدہ:
	gcc_unreachable ();
      }

  اگر (skip)
    واپس NULL_درخت;
  ورنہ اگر ((اندر_statement & اندر_OBJC_FOREACH)
	   && !(is_break && (اندر_statement & اندر_SWITCH_STMT))
	   && name == NULL_درخت)
    {
      /* The foreach expander produces low-level code using gotos instead
	 of a structured loop construct.  */
      gcc_assert (label);
      واپس جوڑو_stmt (build_stmt (loc, GOTO_اظہاریہ, label));
    }
  ورنہ اگر (name && C_DECL_LOOP_NAME (name) && C_DECL_SWITCH_NAME (name))
    {
      label = DECL_CHAIN (name);
      اگر (!is_break)
	label = DECL_CHAIN (label);
      /* Foreach expander from some outer level.  */
      واپس جوڑو_stmt (build_stmt (loc, GOTO_اظہاریہ, label));
    }
  واپس جوڑو_stmt (build_stmt (loc, is_break ? BREAK_STMT : CONTINUE_STMT,
			       name));
}

/* A helper routine for c_process_expr_stmt and c_finish_stmt_expr.  */

ساکن خالی
emit_side_effect_warnings (location_t loc, درخت اظہاریہ)
{
  maybe_warn_nodiscard (loc, اظہاریہ);
  اگر (!warn_غیر_مستعمل_قدر)
    واپس;
  اگر (اظہاریہ == error_mark_گرہ)
    ;
  ورنہ اگر (!درخت_SIDE_EFFECTS (اظہاریہ))
    {
      اگر (!VOID_TYPE_P (درخت_TYPE (اظہاریہ))
	  && !warning_suppressed_p (اظہاریہ, OPT_Wunused_قدر))
	warning_at (loc, OPT_Wunused_قدر, "statement with no effect");
    }
  ورنہ اگر (درخت_رمز (اظہاریہ) == COMPOUND_اظہاریہ)
    {
      درخت r = اظہاریہ;
      location_t cloc = loc;
      جب (درخت_رمز (r) == COMPOUND_اظہاریہ)
	{
	  اگر (اظہاریہ_HAS_LOCATION (r))
	    cloc = اظہاریہ_LOCATION (r);
	  r = درخت_عملیہ (r, 1);
	}
      اگر (!درخت_SIDE_EFFECTS (r)
	  && !VOID_TYPE_P (درخت_TYPE (r))
	  && !CONVERT_اظہاریہ_P (r)
	  && !warning_suppressed_p (r, OPT_Wunused_قدر)
	  && !warning_suppressed_p (اظہاریہ, OPT_Wunused_قدر))
	warning_at (cloc, OPT_Wunused_قدر,
		    "right-hand operand of comma expression has no effect");
    }
  ورنہ
    warn_if_غیر_مستعمل_قدر (اظہاریہ, loc);
}

/* Process an expression as if it were a complete statement.  Emit
   diagnostics, but do not call ADD_STMT.  LOC is the location of the
   statement.  */

درخت
c_process_اظہاریہ_stmt (location_t loc, درخت اظہاریہ)
{
  درخت exprv;

  اگر (!اظہاریہ)
    واپس NULL_درخت;

  اظہاریہ = c_fully_fold (اظہاریہ, جھوٹ, تہی);

  اگر (warn_sequence_نقطہ)
    verify_sequence_points (اظہاریہ);

  اگر (درخت_TYPE (اظہاریہ) != error_mark_گرہ
      && !COMPLETE_OR_VOID_TYPE_P (درخت_TYPE (اظہاریہ))
      && درخت_رمز (درخت_TYPE (اظہاریہ)) != ARRAY_TYPE)
    error_at (loc, "expression statement has incomplete type");

  /* If we're not processing a statement expression, warn about unused values.
     Warnings for statement expressions will be emitted later, once we figure
     out which is the result.  */
  اگر (!STATEMENT_LIST_STMT_اظہاریہ (cur_stmt_list)
      && (warn_غیر_مستعمل_قدر || warn_غیر_مستعمل_نتیجہ))
    emit_side_effect_warnings (اظہاریہ_LOC_OR_LOC (اظہاریہ, loc), اظہاریہ);

  exprv = اظہاریہ;
  جب (درخت_رمز (exprv) == COMPOUND_اظہاریہ)
    exprv = درخت_عملیہ (exprv, 1);
  جب (CONVERT_اظہاریہ_P (exprv))
    exprv = درخت_عملیہ (exprv, 0);
  اگر (DECL_P (exprv)
      || handled_component_p (exprv)
      || درخت_رمز (exprv) == ADDR_اظہاریہ)
    mark_exp_read (exprv);

  /* If the expression is not of a type to which we cannot assign a line
     number, wrap the thing in a no-op NOP_EXPR.  */
  اگر (DECL_P (اظہاریہ) || CONSTANT_CLASS_P (اظہاریہ))
    {
      اظہاریہ = build1 (NOP_اظہاریہ, درخت_TYPE (اظہاریہ), اظہاریہ);
      سیٹ_اظہاریہ_LOCATION (اظہاریہ, loc);
    }

  واپس اظہاریہ;
}

/* Emit an expression as a statement.  LOC is the location of the
   expression.  */

درخت
c_اختتام_اظہاریہ_stmt (location_t loc, درخت اظہاریہ)
{
  اگر (اظہاریہ)
    واپس جوڑو_stmt (c_process_اظہاریہ_stmt (loc, اظہاریہ));
  ورنہ
    واپس تہی;
}

/* Do the opposite and emit a statement as an expression.  To begin,
   create a new binding level and return it.  */

درخت
c_begin_stmt_اظہاریہ (خالی)
{
  درخت ret;

  /* We must force a BLOCK for this level so that, if it is not expanded
     later, there is a way to turn off the entire subtree of blocks that
     are contained in it.  */
  keep_اگلا_level ();
  ret = c_begin_compound_stmt (سچ);

  c_bindings_آغاز_stmt_اظہاریہ (c_switch_ڈھیر == تہی
			      ? تہی
			      : c_switch_ڈھیر->bindings);

  /* Mark the current statement list as belonging to a statement list.  */
  STATEMENT_LIST_STMT_اظہاریہ (ret) = 1;

  واپس ret;
}

/* LOC is the location of the compound statement to which this body
   belongs.  */

درخت
c_اختتام_stmt_اظہاریہ (location_t loc, درخت body)
{
  درخت آخری, type, tmp, val;
  درخت *آخری_p;

  body = c_انتہا_compound_stmt (loc, body, سچ);

  c_bindings_انتہا_stmt_اظہاریہ (c_switch_ڈھیر == تہی
			    ? تہی
			    : c_switch_ڈھیر->bindings);

  /* Locate the last statement in BODY.  See c_end_compound_stmt
     about always returning a BIND_EXPR.  */
  آخری_p = &BIND_اظہاریہ_BODY (body);
  آخری = BIND_اظہاریہ_BODY (body);

 continue_searching:
  اگر (درخت_رمز (آخری) == STATEMENT_LIST)
    {
      درخت_stmt_iterator l = tsi_آخری (آخری);

      جب (!tsi_انتہا_p (l) && درخت_رمز (tsi_stmt (l)) == DEBUG_BEGIN_STMT)
	tsi_پچھلا (&l);

      /* This can happen with degenerate cases like ({ }).  No value.  */
      اگر (tsi_انتہا_p (l))
	واپس body;

      /* If we're supposed to generate side effects warnings, process
	 all of the statements except the last.  */
      اگر (warn_غیر_مستعمل_قدر || warn_غیر_مستعمل_نتیجہ)
	{
	  برائے (درخت_stmt_iterator i = tsi_آغاز (آخری);
	       tsi_stmt (i) != tsi_stmt (l); tsi_اگلا (&i))
	    {
	      location_t tloc;
	      درخت t = tsi_stmt (i);

	      tloc = اظہاریہ_HAS_LOCATION (t) ? اظہاریہ_LOCATION (t) : loc;
	      emit_side_effect_warnings (tloc, t);
	    }
	}
      آخری_p = tsi_stmt_ptr (l);
      آخری = *آخری_p;
    }

  /* If the end of the list is exception related, then the list was split
     by a call to push_cleanup.  Continue searching.  */
  اگر (درخت_رمز (آخری) == TRY_FINALLY_اظہاریہ
      || درخت_رمز (آخری) == TRY_CATCH_اظہاریہ)
    {
      آخری_p = &درخت_عملیہ (آخری, 0);
      آخری = *آخری_p;
      جاؤ continue_searching;
    }

  اگر (آخری == error_mark_گرہ)
    واپس آخری;

  /* In the case that the BIND_EXPR is not necessary, return the
     expression out from inside it.  */
  اگر ((آخری == BIND_اظہاریہ_BODY (body)
       /* Skip nested debug stmts.  */
       || آخری == اظہاریہ_پہلا (BIND_اظہاریہ_BODY (body)))
      && BIND_اظہاریہ_VARS (body) == تہی)
    {
      /* Even if this looks constant, do not allow it in a constant
	 expression.  */
      آخری = c_wrap_maybe_const (آخری, سچ);
      /* Do not warn if the return value of a statement expression is
	 unused.  */
      suppress_warning (آخری, OPT_Wunused);
      واپس آخری;
    }

  /* Extract the type of said expression.  */
  type = درخت_TYPE (آخری);

  /* If we're not returning a value at all, then the BIND_EXPR that
     we already have is a fine expression to return.  */
  اگر (!type || VOID_TYPE_P (type))
    واپس body;

  /* Now that we've located the expression containing the value, it seems
     silly to make voidify_wrapper_expr repeat the process.  Create a
     temporary of the appropriate type and stick it in a TARGET_EXPR.  */
  tmp = create_tmp_var_raw (type);

  /* Unwrap a no-op NOP_EXPR as added by c_finish_expr_stmt.  This avoids
     tree_expr_nonnegative_p giving up immediately.  */
  val = آخری;
  اگر (درخت_رمز (val) == NOP_اظہاریہ
      && درخت_TYPE (val) == درخت_TYPE (درخت_عملیہ (val, 0)))
    val = درخت_عملیہ (val, 0);

  *آخری_p = build2 (MODIFY_اظہاریہ, void_type_گرہ, tmp, val);
  سیٹ_اظہاریہ_LOCATION (*آخری_p, اظہاریہ_LOCATION (آخری));

  {
    درخت t = build4 (ہدف_اظہاریہ, type, tmp, body, NULL_درخت, NULL_درخت);
    سیٹ_اظہاریہ_LOCATION (t, loc);
    واپس t;
  }
}

/* Begin and end compound statements.  This is as simple as pushing
   and popping new statement lists from the tree.  */

درخت
c_begin_compound_stmt (منطقی do_scope)
{
  درخت stmt = ڈالو_stmt_list ();
  اگر (do_scope)
    ڈالو_scope ();
  واپس stmt;
}

/* End a compound statement.  STMT is the statement.  LOC is the
   location of the compound statement-- this is usually the location
   of the opening brace.  */

درخت
c_انتہا_compound_stmt (location_t loc, درخت stmt, منطقی do_scope)
{
  درخت بلاک = تہی;

  اگر (do_scope)
    {
      اگر (c_dialect_objc ())
	objc_clear_super_receiver ();
      بلاک = نکالو_scope ();
    }

  stmt = نکالو_stmt_list (stmt);
  stmt = c_build_bind_اظہاریہ (loc, بلاک, stmt);

  /* If this compound statement is nested immediately inside a statement
     expression, then force a BIND_EXPR to be created.  Otherwise we'll
     do the wrong thing for ({ { 1; } }) or ({ 1; { } }).  In particular,
     STATEMENT_LISTs merge, and thus we can lose track of what statement
     was really last.  */
  اگر (building_stmt_list_p ()
      && STATEMENT_LIST_STMT_اظہاریہ (cur_stmt_list)
      && درخت_رمز (stmt) != BIND_اظہاریہ)
    {
      stmt = build3 (BIND_اظہاریہ, void_type_گرہ, تہی, stmt, تہی);
      درخت_SIDE_EFFECTS (stmt) = 1;
      سیٹ_اظہاریہ_LOCATION (stmt, loc);
    }

  واپس stmt;
}

/* Queue a cleanup.  CLEANUP is an expression/statement to be executed
   when the current scope is exited.  EH_ONLY is true when this is not
   meant to apply to normal control flow transfer.  */

خالی
ڈالو_cleanup (درخت decl, درخت cleanup, منطقی eh_only)
{
  شمار درخت_رمز_2 رمز;
  درخت stmt, list;
  منطقی stmt_اظہاریہ;

  رمز = eh_only ? TRY_CATCH_اظہاریہ : TRY_FINALLY_اظہاریہ;
  stmt = build_stmt (DECL_ماخذ_LOCATION (decl), رمز, تہی, cleanup);
  جوڑو_stmt (stmt);
  stmt_اظہاریہ = STATEMENT_LIST_STMT_اظہاریہ (cur_stmt_list);
  list = ڈالو_stmt_list ();
  درخت_عملیہ (stmt, 0) = list;
  STATEMENT_LIST_STMT_اظہاریہ (list) = stmt_اظہاریہ;
}

/* Build a vector comparison of ARG0 and ARG1 using CODE opcode
   into a value of TYPE type.  Comparison is done via VEC_COND_EXPR.  */

ساکن درخت
build_vec_cmp (درخت_رمز_2 رمز, درخت type,
	       درخت arg0, درخت arg1)
{
  درخت zero_vec = build_zero_cst (type);
  درخت minus_one_vec = build_minus_one_cst (type);
  درخت cmp_type = truth_type_for (درخت_TYPE (arg0));
  درخت cmp = build2 (رمز, cmp_type, arg0, arg1);
  واپس build3 (VEC_COND_اظہاریہ, type, cmp, minus_one_vec, zero_vec);
}

/* Possibly warn about an address of OP never being NULL in a comparison
   operation CODE involving null.  */

ساکن خالی
maybe_warn_for_null_پتہ (location_t loc, درخت op, درخت_رمز_2 رمز)
{
  /* Prevent warnings issued for macro expansion.  */
  اگر (!warn_پتہ
      || warning_suppressed_p (op, OPT_Waddress)
      || from_macro_expansion_at (loc))
    واپس;

  اگر (درخت_رمز (op) == NOP_اظہاریہ)
    {
      /* Allow casts to intptr_t to suppress the warning.  */
      درخت type = درخت_TYPE (op);
      اگر (درخت_رمز (type) == INTEGER_TYPE)
	واپس;
      op = درخت_عملیہ (op, 0);
    }

  اگر (درخت_رمز (op) == اشارہ_گر_PLUS_اظہاریہ)
    {
      /* Allow a cast to void* to suppress the warning.  */
      درخت type = درخت_TYPE (درخت_TYPE (op));
      اگر (VOID_TYPE_P (type))
	واپس;

      /* Adding any value to a null pointer, including zero, is undefined
	 in C.  This includes the expression &p[0] where p is the null
	 pointer, although &p[0] will have been folded to p by this point
	 and so not diagnosed.  */
      اگر (رمز == EQ_اظہاریہ)
	warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<false%> "
		    "for the pointer operand in %qE must not be NULL",
		    op);
      ورنہ
	warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<true%> "
		    "for the pointer operand in %qE must not be NULL",
		    op);

      واپس;
    }

  اگر (درخت_رمز (op) != ADDR_اظہاریہ)
    واپس;

  op = درخت_عملیہ (op, 0);

  اگر (درخت_رمز (op) == IMAGPART_اظہاریہ
      || درخت_رمز (op) == REALPART_اظہاریہ)
    {
      /* The address of either complex part may not be null.  */
      اگر (رمز == EQ_اظہاریہ)
	warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<false%> "
		    "for the address of %qE will never be NULL",
		    op);
      ورنہ
	warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<true%> "
		    "for the address of %qE will never be NULL",
		    op);
      واپس;
    }

  /* Set to true in the loop below if OP dereferences is operand.
     In such a case the ultimate target need not be a decl for
     the null [in]equality test to be constant.  */
  منطقی deref = جھوٹ;

  /* Get the outermost array or object, or member.  */
  جب (handled_component_p (op))
    {
      اگر (درخت_رمز (op) == COMPONENT_REF)
	{
	  /* Get the member (its address is never null).  */
	  op = درخت_عملیہ (op, 1);
	  توڑو;
	}

      /* Get the outer array/object to refer to in the warning.  */
      op = درخت_عملیہ (op, 0);
      deref = سچ;
    }

  اگر ((!deref && !decl_with_nonnull_addr_p (op))
      || from_macro_expansion_at (loc))
    واپس;

  منطقی w;
  اگر (رمز == EQ_اظہاریہ)
    w = warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<false%> "
		    "for the address of %qE will never be NULL",
		    op);
  ورنہ
    w = warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<true%> "
		    "for the address of %qE will never be NULL",
		    op);

  اگر (w && DECL_P (op))
    inform (DECL_ماخذ_LOCATION (op), "%qD declared here", op);
}

/* Build a binary-operation expression without default conversions.
   CODE is the kind of expression to build.
   LOCATION is the operator's location.
   This function differs from `build' in several ways:
   the data type of the result is computed and recorded in it,
   warnings are generated if arg data types are invalid,
   special handling for addition and subtraction of pointers is known,
   and some optimization is done (operations on narrow ints
   are done in the narrower type when that gives the same result).
   Constant folding is also done before the result is returned.

   Note that the operands will never have enumeral types, or function
   or array types, because either they will have the default conversions
   performed or they have both just been converted to some other type in which
   the arithmetic is to be done.  */

درخت
build_ثنائی_op (location_t location, شمار درخت_رمز_2 رمز,
		 درخت orig_op0, درخت orig_op1, منطقی convert_p)
{
  درخت type0, type1, orig_type0, orig_type1;
  درخت eptype;
  شمار درخت_رمز_2 code0, code1;
  درخت op0, op1;
  درخت ret = error_mark_گرہ;
  ثابت حرف *invalid_op_diag;
  منطقی op0_int_operands, op1_int_operands;
  منطقی int_const, int_const_or_حد_سے_تجاوز, int_operands;

  /* Expression code to give to the expression when it is built.
     Normally this is CODE, which is what the caller asked for,
     but in some special cases we change it.  */
  شمار درخت_رمز_2 resultcode = رمز;

  /* Data type in which the computation is to be performed.
     In the simplest cases this is the common type of the arguments.  */
  درخت نتیجہ_type = تہی;

  /* When the computation is in excess precision, the type of the
     final EXCESS_PRECISION_EXPR.  */
  درخت semantic_نتیجہ_type = تہی;

  /* Nonzero means operands have already been type-converted
     in whatever way is necessary.
     Zero means they need to be converted to RESULT_TYPE.  */
  صحیح converted = 0;

  /* Nonzero means create the expression with this type, rather than
     RESULT_TYPE.  */
  درخت build_type = NULL_درخت;

  /* Nonzero means after finally constructing the expression
     convert it to this type.  */
  درخت final_type = NULL_درخت;

  /* Nonzero if this is an operation like MIN or MAX which can
     safely be computed in short if both args are promoted shorts.
     Also implies COMMON.
     -1 indicates a bitwise operation; this makes a difference
     in the exact conditions for when it is safe to do the operation
     in a narrower mode.  */
  صحیح shorten = 0;

  /* Nonzero if this is a comparison operation;
     if both args are promoted shorts, compare the original shorts.
     Also implies COMMON.  */
  صحیح short_compare = 0;

  /* Nonzero if this is a right-shift operation, which can be computed on the
     original short and then promoted if the operand is a promoted short.  */
  صحیح short_سرکاؤ = 0;

  /* Nonzero means set RESULT_TYPE to the common type of the args.  */
  صحیح common = 0;

  /* True means types are compatible as far as ObjC is concerned.  */
  منطقی objc_ok;

  /* True means this is an arithmetic operation that may need excess
     precision.  */
  منطقی may_need_excess_precision;

  /* True means this is a boolean operation that converts both its
     operands to truth-values.  */
  منطقی boolean_op = جھوٹ;

  /* Remember whether we're doing / or %.  */
  منطقی doing_div_or_mod = جھوٹ;

  /* Remember whether we're doing << or >>.  */
  منطقی doing_سرکاؤ = جھوٹ;

  /* Tree holding instrumentation expression.  */
  درخت instrument_اظہاریہ = تہی;

  اگر (location == UNKNOWN_LOCATION)
    location = داخلہ_location;

  op0 = orig_op0;
  op1 = orig_op1;

  op0_int_operands = اظہاریہ_INT_CONST_OPERANDS (orig_op0);
  اگر (op0_int_operands)
    op0 = remove_c_maybe_const_اظہاریہ (op0);
  op1_int_operands = اظہاریہ_INT_CONST_OPERANDS (orig_op1);
  اگر (op1_int_operands)
    op1 = remove_c_maybe_const_اظہاریہ (op1);
  int_operands = (op0_int_operands && op1_int_operands);
  اگر (int_operands)
    {
      int_const_or_حد_سے_تجاوز = (درخت_رمز (orig_op0) == INTEGER_CST
			       && درخت_رمز (orig_op1) == INTEGER_CST);
      int_const = (int_const_or_حد_سے_تجاوز
		   && !درخت_حد_سے_تجاوز (orig_op0)
		   && !درخت_حد_سے_تجاوز (orig_op1));
    }
  ورنہ
    int_const = int_const_or_حد_سے_تجاوز = جھوٹ;

  /* Do not apply default conversion in mixed vector/scalar expression.  */
  اگر (convert_p
      && سمتیہ_TYPE_P (درخت_TYPE (op0)) == سمتیہ_TYPE_P (درخت_TYPE (op1)))
    {
      op0 = default_conversion (op0);
      op1 = default_conversion (op1);
    }

  orig_type0 = type0 = درخت_TYPE (op0);

  orig_type1 = type1 = درخت_TYPE (op1);

  /* The expression codes of the data types of the arguments tell us
     whether the arguments are integers, floating, pointers, etc.  */
  code0 = درخت_رمز (type0);
  code1 = درخت_رمز (type1);

  /* Strip NON_LVALUE_EXPRs, etc., since we aren't using as an lvalue.  */
  STRIP_TYPE_NOPS (op0);
  STRIP_TYPE_NOPS (op1);

  /* If an error was already reported for one of the arguments,
     avoid reporting another error.  */

  اگر (code0 == ERROR_MARK || code1 == ERROR_MARK)
    واپس error_mark_گرہ;

  اگر (code0 == اشارہ_گر_TYPE
      && reject_gcc_builtin (op0, اظہاریہ_LOCATION (orig_op0)))
    واپس error_mark_گرہ;

  اگر (code1 == اشارہ_گر_TYPE
      && reject_gcc_builtin (op1, اظہاریہ_LOCATION (orig_op1)))
    واپس error_mark_گرہ;

  اگر ((invalid_op_diag
       = targetm.invalid_ثنائی_op (رمز, type0, type1)))
    {
      error_at (location, invalid_op_diag);
      واپس error_mark_گرہ;
    }

  انتخاب (رمز)
    {
    حالت PLUS_اظہاریہ:
    حالت MINUS_اظہاریہ:
    حالت MULT_اظہاریہ:
    حالت TRUNC_DIV_اظہاریہ:
    حالت CEIL_DIV_اظہاریہ:
    حالت FLOOR_DIV_اظہاریہ:
    حالت باری_DIV_اظہاریہ:
    حالت EXACT_DIV_اظہاریہ:
      may_need_excess_precision = سچ;
      توڑو;

    حالت EQ_اظہاریہ:
    حالت NE_اظہاریہ:
    حالت LE_اظہاریہ:
    حالت GE_اظہاریہ:
    حالت LT_اظہاریہ:
    حالت GT_اظہاریہ:
      /* Excess precision for implicit conversions of integers to
	 floating point in C11 and later.  */
      may_need_excess_precision = (flag_isoc11
				   && (ANY_INTEGRAL_TYPE_P (type0)
				       || ANY_INTEGRAL_TYPE_P (type1)));
      توڑو;

    طےشدہ:
      may_need_excess_precision = جھوٹ;
      توڑو;
    }
  اگر (درخت_رمز (op0) == EXCESS_PRECISION_اظہاریہ)
    {
      op0 = درخت_عملیہ (op0, 0);
      type0 = درخت_TYPE (op0);
    }
  ورنہ اگر (may_need_excess_precision
	   && (eptype = excess_precision_type (type0)) != NULL_درخت)
    {
      type0 = eptype;
      op0 = convert (eptype, op0);
    }
  اگر (درخت_رمز (op1) == EXCESS_PRECISION_اظہاریہ)
    {
      op1 = درخت_عملیہ (op1, 0);
      type1 = درخت_TYPE (op1);
    }
  ورنہ اگر (may_need_excess_precision
	   && (eptype = excess_precision_type (type1)) != NULL_درخت)
    {
      type1 = eptype;
      op1 = convert (eptype, op1);
    }

  objc_ok = objc_compare_types (type0, type1, -3, NULL_درخت);

  /* In case when one of the operands of the binary operation is
     a vector and another is a scalar -- convert scalar to vector.  */
  اگر ((gnu_سمتیہ_type_p (type0) && code1 != سمتیہ_TYPE)
      || (gnu_سمتیہ_type_p (type1) && code0 != سمتیہ_TYPE))
    {
      شمار stv_conv convert_flag = scalar_مقصد_سمتیہ (location, رمز, orig_op0,
						     orig_op1, سچ);

      انتخاب (convert_flag)
	{
	  حالت stv_error:
	    واپس error_mark_گرہ;
	  حالت stv_firstarg:
	    {
              منطقی maybe_const = سچ;
              درخت sc;
              sc = c_fully_fold (op0, جھوٹ, &maybe_const);
              sc = save_اظہاریہ (sc);
              sc = convert (درخت_TYPE (type1), sc);
              op0 = build_سمتیہ_from_val (type1, sc);
              اگر (!maybe_const)
                op0 = c_wrap_maybe_const (op0, سچ);
              orig_type0 = type0 = درخت_TYPE (op0);
              code0 = درخت_رمز (type0);
              converted = 1;
              توڑو;
	    }
	  حالت stv_secondarg:
	    {
	      منطقی maybe_const = سچ;
	      درخت sc;
	      sc = c_fully_fold (op1, جھوٹ, &maybe_const);
	      sc = save_اظہاریہ (sc);
	      sc = convert (درخت_TYPE (type0), sc);
	      op1 = build_سمتیہ_from_val (type0, sc);
	      اگر (!maybe_const)
		op1 = c_wrap_maybe_const (op1, سچ);
	      orig_type1 = type1 = درخت_TYPE (op1);
	      code1 = درخت_رمز (type1);
	      converted = 1;
	      توڑو;
	    }
	  طےشدہ:
	    توڑو;
	}
    }

  انتخاب (رمز)
    {
    حالت PLUS_اظہاریہ:
      /* Handle the pointer + int case.  */
      اگر (code0 == اشارہ_گر_TYPE
	  && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  ret = اشارہ_گر_int_مجموع (location, PLUS_اظہاریہ, op0, op1);
	  جاؤ return_build_ثنائی_op;
	}
      ورنہ اگر (code1 == اشارہ_گر_TYPE
	       && (code0 == INTEGER_TYPE || code0 == BITINT_TYPE))
	{
	  ret = اشارہ_گر_int_مجموع (location, PLUS_اظہاریہ, op1, op0);
	  جاؤ return_build_ثنائی_op;
	}
      ورنہ
	common = 1;
      توڑو;

    حالت MINUS_اظہاریہ:
      /* Subtraction of two similar pointers.
	 We must subtract them as integers, then divide by object size.  */
      اگر (code0 == اشارہ_گر_TYPE && code1 == اشارہ_گر_TYPE
	  && comp_ہدف_types (location, type0, type1))
	{
	  ret = اشارہ_گر_diff (location, op0, op1, &instrument_اظہاریہ);
	  جاؤ return_build_ثنائی_op;
	}
      /* Handle pointer minus int.  Just like pointer plus int.  */
      ورنہ اگر (code0 == اشارہ_گر_TYPE
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  ret = اشارہ_گر_int_مجموع (location, MINUS_اظہاریہ, op0, op1);
	  جاؤ return_build_ثنائی_op;
	}
      ورنہ
	common = 1;
      توڑو;

    حالت MULT_اظہاریہ:
      common = 1;
      توڑو;

    حالت TRUNC_DIV_اظہاریہ:
    حالت CEIL_DIV_اظہاریہ:
    حالت FLOOR_DIV_اظہاریہ:
    حالت باری_DIV_اظہاریہ:
    حالت EXACT_DIV_اظہاریہ:
      doing_div_or_mod = سچ;
      warn_for_div_by_zero (location, op1);

      اگر ((code0 == INTEGER_TYPE || code0 == REAL_TYPE
	   || code0 == FIXED_نقطہ_TYPE || code0 == BITINT_TYPE
	   || code0 == COMPLEX_TYPE
	   || gnu_سمتیہ_type_p (type0))
	  && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	      || code1 == FIXED_نقطہ_TYPE || code1 == BITINT_TYPE
	      || code1 == COMPLEX_TYPE
	      || gnu_سمتیہ_type_p (type1)))
	{
	  شمار درخت_رمز_2 tcode0 = code0, tcode1 = code1;

	  اگر (code0 == COMPLEX_TYPE || code0 == سمتیہ_TYPE)
	    tcode0 = درخت_رمز (درخت_TYPE (درخت_TYPE (op0)));
	  اگر (code1 == COMPLEX_TYPE || code1 == سمتیہ_TYPE)
	    tcode1 = درخت_رمز (درخت_TYPE (درخت_TYPE (op1)));

	  اگر (!(((tcode0 == INTEGER_TYPE || tcode0 == BITINT_TYPE
		  || (tcode0 == ENUMERAL_TYPE && code0 == سمتیہ_TYPE))
		 && (tcode1 == INTEGER_TYPE || tcode1 == BITINT_TYPE
		     || (tcode1 == ENUMERAL_TYPE && code1 == سمتیہ_TYPE)))
		|| (tcode0 == FIXED_نقطہ_TYPE && tcode1 == FIXED_نقطہ_TYPE)))
	    resultcode = RDIV_اظہاریہ;
	  ورنہ
	    /* Although it would be tempting to shorten always here, that
	       loses on some targets, since the modulo instruction is
	       undefined if the quotient can't be represented in the
	       computation mode.  We shorten only if unsigned or if
	       dividing by something we know != -1.  */
	    shorten = may_shorten_divmod (op0, op1);
	  common = 1;
	}
      توڑو;

    حالت ثنائی_ہندسہ_AND_اظہاریہ:
    حالت ثنائی_ہندسہ_IOR_اظہاریہ:
    حالت ثنائی_ہندسہ_XOR_اظہاریہ:
      اگر ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	shorten = -1;
      /* Allow vector types which are not floating point types.   */
      ورنہ اگر (gnu_سمتیہ_type_p (type0)
	       && gnu_سمتیہ_type_p (type1)
	       && !سمتیہ_FLOAT_TYPE_P (type0)
	       && !سمتیہ_FLOAT_TYPE_P (type1))
	common = 1;
      توڑو;

    حالت TRUNC_MOD_اظہاریہ:
    حالت FLOOR_MOD_اظہاریہ:
      doing_div_or_mod = سچ;
      warn_for_div_by_zero (location, op1);

      اگر (gnu_سمتیہ_type_p (type0)
	  && gnu_سمتیہ_type_p (type1)
	  && درخت_رمز (درخت_TYPE (type0)) == INTEGER_TYPE
	  && درخت_رمز (درخت_TYPE (type1)) == INTEGER_TYPE)
	common = 1;
      ورنہ اگر ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  /* Although it would be tempting to shorten always here, that loses
	     on some targets, since the modulo instruction is undefined if the
	     quotient can't be represented in the computation mode.  We shorten
	     only if unsigned or if dividing by something we know != -1.  */
	  shorten = may_shorten_divmod (op0, op1);
	  common = 1;
	}
      توڑو;

    حالت TRUTH_ANDIF_اظہاریہ:
    حالت TRUTH_ORIF_اظہاریہ:
    حالت TRUTH_AND_اظہاریہ:
    حالت TRUTH_OR_اظہاریہ:
    حالت TRUTH_XOR_اظہاریہ:
      اگر ((code0 == INTEGER_TYPE || code0 == اشارہ_گر_TYPE
	   || code0 == REAL_TYPE || code0 == COMPLEX_TYPE
	   || code0 == FIXED_نقطہ_TYPE || code0 == NULLPTR_TYPE
	   || code0 == BITINT_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == اشارہ_گر_TYPE
	      || code1 == REAL_TYPE || code1 == COMPLEX_TYPE
	      || code1 == FIXED_نقطہ_TYPE || code1 == NULLPTR_TYPE
	      || code1 == BITINT_TYPE))
	{
	  /* Result of these operations is always an int,
	     but that does not mean the operands should be
	     converted to ints!  */
	  نتیجہ_type = integer_type_گرہ;
	  اگر (op0_int_operands)
	    {
	      op0 = c_objc_common_truthvalue_conversion (location, orig_op0);
	      op0 = remove_c_maybe_const_اظہاریہ (op0);
	    }
	  ورنہ
	    op0 = c_objc_common_truthvalue_conversion (location, op0);
	  اگر (op1_int_operands)
	    {
	      op1 = c_objc_common_truthvalue_conversion (location, orig_op1);
	      op1 = remove_c_maybe_const_اظہاریہ (op1);
	    }
	  ورنہ
	    op1 = c_objc_common_truthvalue_conversion (location, op1);
	  converted = 1;
	  boolean_op = سچ;
	}
      اگر (رمز == TRUTH_ANDIF_اظہاریہ)
	{
	  int_const_or_حد_سے_تجاوز = (int_operands
				   && درخت_رمز (orig_op0) == INTEGER_CST
				   && (op0 == truthvalue_false_گرہ
				       || درخت_رمز (orig_op1) == INTEGER_CST));
	  int_const = (int_const_or_حد_سے_تجاوز
		       && !درخت_حد_سے_تجاوز (orig_op0)
		       && (op0 == truthvalue_false_گرہ
			   || !درخت_حد_سے_تجاوز (orig_op1)));
	}
      ورنہ اگر (رمز == TRUTH_ORIF_اظہاریہ)
	{
	  int_const_or_حد_سے_تجاوز = (int_operands
				   && درخت_رمز (orig_op0) == INTEGER_CST
				   && (op0 == truthvalue_true_گرہ
				       || درخت_رمز (orig_op1) == INTEGER_CST));
	  int_const = (int_const_or_حد_سے_تجاوز
		       && !درخت_حد_سے_تجاوز (orig_op0)
		       && (op0 == truthvalue_true_گرہ
			   || !درخت_حد_سے_تجاوز (orig_op1)));
	}
      توڑو;

      /* Shift operations: result has same type as first operand;
	 always convert second operand to int.
	 Also set SHORT_SHIFT if shifting rightward.  */

    حالت RSHIFT_اظہاریہ:
      اگر (gnu_سمتیہ_type_p (type0)
	  && gnu_سمتیہ_type_p (type1)
	  && درخت_رمز (درخت_TYPE (type0)) == INTEGER_TYPE
	  && درخت_رمز (درخت_TYPE (type1)) == INTEGER_TYPE
	  && معلوم_eq (TYPE_سمتیہ_SUBPARTS (type0),
		       TYPE_سمتیہ_SUBPARTS (type1)))
	{
	  نتیجہ_type = type0;
	  converted = 1;
	}
      ورنہ اگر ((code0 == INTEGER_TYPE || code0 == FIXED_نقطہ_TYPE
		|| code0 == BITINT_TYPE
		|| (gnu_سمتیہ_type_p (type0)
		    && درخت_رمز (درخت_TYPE (type0)) == INTEGER_TYPE))
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  doing_سرکاؤ = سچ;
	  اگر (درخت_رمز (op1) == INTEGER_CST)
	    {
	      اگر (درخت_int_cst_sgn (op1) < 0)
		{
		  int_const = جھوٹ;
		  اگر (c_inhibit_evaluation_warnings == 0)
		    warning_at (location, OPT_Wshift_گنتی_negative,
				"right shift count is negative");
		}
	      ورنہ اگر (code0 == سمتیہ_TYPE)
		{
		  اگر (compare_درخت_int (op1,
					TYPE_PRECISION (درخت_TYPE (type0)))
		      >= 0)
		    {
		      int_const = جھوٹ;
		      اگر (c_inhibit_evaluation_warnings == 0)
			warning_at (location, OPT_Wshift_گنتی_حد_سے_تجاوز,
				    "right shift count >= width of vector element");
		    }
		}
	      ورنہ
		{
		  اگر (!integer_zerop (op1))
		    short_سرکاؤ = 1;

		  اگر (compare_درخت_int (op1, TYPE_PRECISION (type0)) >= 0)
		    {
		      int_const = جھوٹ;
		      اگر (c_inhibit_evaluation_warnings == 0)
			warning_at (location, OPT_Wshift_گنتی_حد_سے_تجاوز,
				    "right shift count >= width of type");
		    }
		}
	    }

	  /* Use the type of the value to be shifted.  */
	  نتیجہ_type = type0;
	  /* Avoid converting op1 to result_type later.  */
	  converted = 1;
	}
      توڑو;

    حالت LSHIFT_اظہاریہ:
      اگر (gnu_سمتیہ_type_p (type0)
	  && gnu_سمتیہ_type_p (type1)
	  && درخت_رمز (درخت_TYPE (type0)) == INTEGER_TYPE
	  && درخت_رمز (درخت_TYPE (type1)) == INTEGER_TYPE
	  && معلوم_eq (TYPE_سمتیہ_SUBPARTS (type0),
		       TYPE_سمتیہ_SUBPARTS (type1)))
	{
	  نتیجہ_type = type0;
	  converted = 1;
	}
      ورنہ اگر ((code0 == INTEGER_TYPE || code0 == FIXED_نقطہ_TYPE
		|| code0 == BITINT_TYPE
		|| (gnu_سمتیہ_type_p (type0)
		    && درخت_رمز (درخت_TYPE (type0)) == INTEGER_TYPE))
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  doing_سرکاؤ = سچ;
	  اگر (درخت_رمز (op0) == INTEGER_CST
	      && درخت_int_cst_sgn (op0) < 0
	      && !TYPE_حد_سے_تجاوز_WRAPS (type0))
	    {
	      /* Don't reject a left shift of a negative value in a context
		 where a constant expression is needed in C90.  */
	      اگر (flag_isoc99)
		int_const = جھوٹ;
	      اگر (c_inhibit_evaluation_warnings == 0)
		warning_at (location, OPT_Wshift_negative_قدر,
			    "left shift of negative value");
	    }
	  اگر (درخت_رمز (op1) == INTEGER_CST)
	    {
	      اگر (درخت_int_cst_sgn (op1) < 0)
		{
		  int_const = جھوٹ;
		  اگر (c_inhibit_evaluation_warnings == 0)
		    warning_at (location, OPT_Wshift_گنتی_negative,
				"left shift count is negative");
		}
	      ورنہ اگر (code0 == سمتیہ_TYPE)
		{
		  اگر (compare_درخت_int (op1,
					TYPE_PRECISION (درخت_TYPE (type0)))
		      >= 0)
		    {
		      int_const = جھوٹ;
		      اگر (c_inhibit_evaluation_warnings == 0)
			warning_at (location, OPT_Wshift_گنتی_حد_سے_تجاوز,
				    "left shift count >= width of vector element");
		    }
		}
	      ورنہ اگر (compare_درخت_int (op1, TYPE_PRECISION (type0)) >= 0)
		{
		  int_const = جھوٹ;
		  اگر (c_inhibit_evaluation_warnings == 0)
		    warning_at (location, OPT_Wshift_گنتی_حد_سے_تجاوز,
				"left shift count >= width of type");
		}
	      ورنہ اگر (درخت_رمز (op0) == INTEGER_CST
		       && maybe_warn_سرکاؤ_حد_سے_تجاوز (location, op0, op1)
		       && flag_isoc99)
		int_const = جھوٹ;
	    }

	  /* Use the type of the value to be shifted.  */
	  نتیجہ_type = type0;
	  /* Avoid converting op1 to result_type later.  */
	  converted = 1;
	}
      توڑو;

    حالت EQ_اظہاریہ:
    حالت NE_اظہاریہ:
      اگر (gnu_سمتیہ_type_p (type0) && gnu_سمتیہ_type_p (type1))
        {
          درخت intt;
	  اگر (!سمتیہ_types_compatible_elements_p (type0, type1))
            {
              error_at (location, "comparing vectors with different "
                                  "element types");
              واپس error_mark_گرہ;
            }

	  اگر (maybe_ne (TYPE_سمتیہ_SUBPARTS (type0),
			TYPE_سمتیہ_SUBPARTS (type1)))
            {
              error_at (location, "comparing vectors with different "
                                  "number of elements");
              واپس error_mark_گرہ;
            }

	  /* It's not precisely specified how the usual arithmetic
	     conversions apply to the vector types.  Here, we use
	     the unsigned type if one of the operands is signed and
	     the other one is unsigned.  */
	  اگر (TYPE_UNSIGNED (type0) != TYPE_UNSIGNED (type1))
	    {
	      اگر (!TYPE_UNSIGNED (type0))
		op0 = build1 (VIEW_CONVERT_اظہاریہ, type1, op0);
	      ورنہ
		op1 = build1 (VIEW_CONVERT_اظہاریہ, type0, op1);
	      warning_at (location, OPT_Wsign_compare, "comparison between "
			  "types %qT and %qT", type0, type1);
	    }

          /* Always construct signed integer vector type.  */
	  اگر (سمتیہ_BOOLEAN_TYPE_P (type0) && سمتیہ_BOOLEAN_TYPE_P (type1))
	    نتیجہ_type = type0;
	  ورنہ
	    {
	      خودکار nelts = TYPE_سمتیہ_SUBPARTS (type0);

	      intt = c_common_type_for_سائز (GET_منوال_BITSIZE
					     (SCALAR_TYPE_منوال
						(درخت_TYPE (type0))), 0);
	      اگر (!intt)
		{
		  error_at (location, "could not find an integer type "
				      "of the same size as %qT",
			    درخت_TYPE (type0));
		  واپس error_mark_گرہ;
		}
	      نتیجہ_type = build_opaque_سمتیہ_type (intt, nelts);
	    }
          converted = 1;
	  ret = build_vec_cmp (resultcode, نتیجہ_type, op0, op1);
	  جاؤ return_build_ثنائی_op;
        }
      اگر (FLOAT_TYPE_P (type0) || FLOAT_TYPE_P (type1))
	warning_at (location,
		    OPT_Wfloat_equal,
		    "comparing floating-point with %<==%> or %<!=%> is unsafe");
      /* Result of comparison is always int,
	 but don't convert the args to int!  */
      build_type = integer_type_گرہ;
      اگر ((code0 == INTEGER_TYPE || code0 == REAL_TYPE || code0 == BITINT_TYPE
	   || code0 == FIXED_نقطہ_TYPE || code0 == COMPLEX_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	      || code1 == BITINT_TYPE
	      || code1 == FIXED_نقطہ_TYPE || code1 == COMPLEX_TYPE))
	short_compare = 1;
      ورنہ اگر (code0 == اشارہ_گر_TYPE
	       && (code1 == NULLPTR_TYPE
		   || null_اشارہ_گر_constant_p (orig_op1)))
	{
	  maybe_warn_for_null_پتہ (location, op0, رمز);
	  نتیجہ_type = type0;
	}
      ورنہ اگر (code1 == اشارہ_گر_TYPE
	       && (code0 == NULLPTR_TYPE
		   || null_اشارہ_گر_constant_p (orig_op0)))
	{
	  maybe_warn_for_null_پتہ (location, op1, رمز);
	  نتیجہ_type = type1;
	}
      ورنہ اگر (code0 == اشارہ_گر_TYPE && code1 == اشارہ_گر_TYPE)
	{
	  درخت tt0 = درخت_TYPE (type0);
	  درخت tt1 = درخت_TYPE (type1);
	  addr_space_t as0 = TYPE_ADDR_SPACE (tt0);
	  addr_space_t as1 = TYPE_ADDR_SPACE (tt1);
	  addr_space_t as_common = ADDR_SPACE_GENERIC;

	  /* Anything compares with void *.  void * compares with anything.
	     Otherwise, the targets must be compatible
	     and both must be object or both incomplete.  */
	  اگر (comp_ہدف_types (location, type0, type1))
	    نتیجہ_type = common_اشارہ_گر_type (type0, type1, NULL_درخت);
	  ورنہ اگر (!addr_space_superset (as0, as1, &as_common))
	    {
	      error_at (location, "comparison of pointers to "
			"disjoint address spaces");
	      واپس error_mark_گرہ;
	    }
	  ورنہ اگر (VOID_TYPE_P (tt0) && !TYPE_ATOMIC (tt0))
	    {
	      اگر (pedantic && درخت_رمز (tt1) == FUNCTION_TYPE)
		pedwarn (location, OPT_Wpedantic, "ISO C forbids "
			 "comparison of %<void *%> with function pointer");
	    }
	  ورنہ اگر (VOID_TYPE_P (tt1) && !TYPE_ATOMIC (tt1))
	    {
	      اگر (pedantic && درخت_رمز (tt0) == FUNCTION_TYPE)
		pedwarn (location, OPT_Wpedantic, "ISO C forbids "
			 "comparison of %<void *%> with function pointer");
	    }
	  ورنہ
	    /* Avoid warning about the volatile ObjC EH puts on decls.  */
	    اگر (!objc_ok)
	      pedwarn (location, OPT_Wcompare_distinct_اشارہ_گر_types,
		       "comparison of distinct pointer types lacks a cast");

	  اگر (نتیجہ_type == NULL_درخت)
	    {
	      صحیح qual = ENCODE_QUAL_ADDR_SPACE (as_common);
	      نتیجہ_type = c_build_اشارہ_گر_type
			      (c_build_qualified_type (void_type_گرہ, qual));
	    }
	}
      ورنہ اگر (code0 == اشارہ_گر_TYPE
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  نتیجہ_type = type0;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}
      ورنہ اگر ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	       && code1 == اشارہ_گر_TYPE)
	{
	  نتیجہ_type = type1;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}
      /* 6.5.9: One of the following shall hold:
	 -- both operands have type nullptr_t;  */
      ورنہ اگر (code0 == NULLPTR_TYPE && code1 == NULLPTR_TYPE)
	{
	  نتیجہ_type = nullptr_type_گرہ;
	  /* No need to convert the operands to result_type later.  */
	  converted = 1;
	}
    /* -- one operand has type nullptr_t and the other is a null pointer
       constant.  We will have to convert the former to the type of the
       latter, because during gimplification we can't have mismatching
       comparison operand type.  We convert from nullptr_t to the other
       type, since only nullptr_t can be converted to nullptr_t.  Also,
       even a constant 0 is a null pointer constant, so we may have to
       create a pointer type from its type.  */
      ورنہ اگر (code0 == NULLPTR_TYPE && null_اشارہ_گر_constant_p (orig_op1))
	نتیجہ_type = (INTEGRAL_TYPE_P (type1)
		       ? c_build_اشارہ_گر_type (type1) : type1);
      ورنہ اگر (code1 == NULLPTR_TYPE && null_اشارہ_گر_constant_p (orig_op0))
	نتیجہ_type = (INTEGRAL_TYPE_P (type0)
		       ? c_build_اشارہ_گر_type (type0) : type0);
      اگر ((C_BOOLEAN_TYPE_P (درخت_TYPE (orig_op0))
	   || truth_قدر_p (درخت_رمز (orig_op0)))
	  ^ (C_BOOLEAN_TYPE_P (درخت_TYPE (orig_op1))
	     || truth_قدر_p (درخت_رمز (orig_op1))))
	maybe_warn_bool_compare (location, رمز, orig_op0, orig_op1);
      توڑو;

    حالت LE_اظہاریہ:
    حالت GE_اظہاریہ:
    حالت LT_اظہاریہ:
    حالت GT_اظہاریہ:
      اگر (gnu_سمتیہ_type_p (type0) && gnu_سمتیہ_type_p (type1))
        {
          درخت intt;
	  اگر (!سمتیہ_types_compatible_elements_p (type0, type1))
            {
              error_at (location, "comparing vectors with different "
                                  "element types");
              واپس error_mark_گرہ;
            }

	  اگر (maybe_ne (TYPE_سمتیہ_SUBPARTS (type0),
			TYPE_سمتیہ_SUBPARTS (type1)))
            {
              error_at (location, "comparing vectors with different "
                                  "number of elements");
              واپس error_mark_گرہ;
            }

	  /* It's not precisely specified how the usual arithmetic
	     conversions apply to the vector types.  Here, we use
	     the unsigned type if one of the operands is signed and
	     the other one is unsigned.  */
	  اگر (TYPE_UNSIGNED (type0) != TYPE_UNSIGNED (type1))
	    {
	      اگر (!TYPE_UNSIGNED (type0))
		op0 = build1 (VIEW_CONVERT_اظہاریہ, type1, op0);
	      ورنہ
		op1 = build1 (VIEW_CONVERT_اظہاریہ, type0, op1);
	      warning_at (location, OPT_Wsign_compare, "comparison between "
			  "types %qT and %qT", type0, type1);
	    }

          /* Always construct signed integer vector type.  */
          intt = c_common_type_for_سائز (GET_منوال_BITSIZE
					 (SCALAR_TYPE_منوال
					  (درخت_TYPE (type0))), 0);
	  اگر (!intt)
	    {
	      error_at (location, "could not find an integer type "
				  "of the same size as %qT",
			درخت_TYPE (type0));
	      واپس error_mark_گرہ;
	    }
          نتیجہ_type = build_opaque_سمتیہ_type (intt,
						  TYPE_سمتیہ_SUBPARTS (type0));
          converted = 1;
	  ret = build_vec_cmp (resultcode, نتیجہ_type, op0, op1);
	  جاؤ return_build_ثنائی_op;
        }
      build_type = integer_type_گرہ;
      اگر ((code0 == INTEGER_TYPE || code0 == REAL_TYPE
	   || code0 == BITINT_TYPE || code0 == FIXED_نقطہ_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	      || code1 == BITINT_TYPE || code1 == FIXED_نقطہ_TYPE))
	short_compare = 1;
      ورنہ اگر (code0 == اشارہ_گر_TYPE && code1 == اشارہ_گر_TYPE)
	{
	  addr_space_t as0 = TYPE_ADDR_SPACE (درخت_TYPE (type0));
	  addr_space_t as1 = TYPE_ADDR_SPACE (درخت_TYPE (type1));
	  addr_space_t as_common;

	  اگر (comp_ہدف_types (location, type0, type1))
	    {
	      نتیجہ_type = common_اشارہ_گر_type (type0, type1, NULL_درخت);
	      اگر (!COMPLETE_TYPE_P (درخت_TYPE (type0))
		  != !COMPLETE_TYPE_P (درخت_TYPE (type1)))
		pedwarn_c99 (location, OPT_Wpedantic,
			     "comparison of complete and incomplete pointers");
	      ورنہ اگر (درخت_رمز (درخت_TYPE (type0)) == FUNCTION_TYPE)
		pedwarn (location, OPT_Wpedantic, "ISO C forbids "
			 "ordered comparisons of pointers to functions");
	      ورنہ اگر (null_اشارہ_گر_constant_p (orig_op0)
		       || null_اشارہ_گر_constant_p (orig_op1))
		warning_at (location, OPT_Wextra,
			    "ordered comparison of pointer with null pointer");

	    }
	  ورنہ اگر (!addr_space_superset (as0, as1, &as_common))
	    {
	      error_at (location, "comparison of pointers to "
			"disjoint address spaces");
	      واپس error_mark_گرہ;
	    }
	  ورنہ
	    {
	      صحیح qual = ENCODE_QUAL_ADDR_SPACE (as_common);
	      نتیجہ_type = c_build_اشارہ_گر_type
			      (c_build_qualified_type (void_type_گرہ, qual));
              pedwarn (location, OPT_Wcompare_distinct_اشارہ_گر_types,
                       "comparison of distinct pointer types lacks a cast");
	    }
	}
      ورنہ اگر (code0 == اشارہ_گر_TYPE && null_اشارہ_گر_constant_p (orig_op1))
	{
	  نتیجہ_type = type0;
	  اگر (pedantic)
	    pedwarn (location, OPT_Wpedantic,
		     "ordered comparison of pointer with integer zero");
	  ورنہ اگر (extra_warnings)
	    warning_at (location, OPT_Wextra,
			"ordered comparison of pointer with integer zero");
	}
      ورنہ اگر (code1 == اشارہ_گر_TYPE && null_اشارہ_گر_constant_p (orig_op0))
	{
	  نتیجہ_type = type1;
	  اگر (pedantic)
	    pedwarn (location, OPT_Wpedantic,
		     "ordered comparison of pointer with integer zero");
	  ورنہ اگر (extra_warnings)
	    warning_at (location, OPT_Wextra,
			"ordered comparison of pointer with integer zero");
	}
      ورنہ اگر (code0 == اشارہ_گر_TYPE
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  نتیجہ_type = type0;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}
      ورنہ اگر ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	       && code1 == اشارہ_گر_TYPE)
	{
	  نتیجہ_type = type1;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}

      اگر ((code0 == اشارہ_گر_TYPE || code1 == اشارہ_گر_TYPE)
	  && current_function_decl != NULL_درخت
	  && sanitize_flags_p (SANITIZE_اشارہ_گر_COMPARE))
	{
	  op0 = save_اظہاریہ (c_fully_fold (op0, جھوٹ, تہی));
	  op1 = save_اظہاریہ (c_fully_fold (op1, جھوٹ, تہی));

	  درخت tt = builtin_decl_explicit (BUILT_اندر_ASAN_اشارہ_گر_COMPARE);
	  instrument_اظہاریہ = build_call_اظہاریہ_loc (location, tt, 2, op0, op1);
	}

      اگر ((C_BOOLEAN_TYPE_P (درخت_TYPE (orig_op0))
	   || truth_قدر_p (درخت_رمز (orig_op0)))
	  ^ (C_BOOLEAN_TYPE_P (درخت_TYPE (orig_op1))
	     || truth_قدر_p (درخت_رمز (orig_op1))))
	maybe_warn_bool_compare (location, رمز, orig_op0, orig_op1);
      توڑو;

    حالت MIN_اظہاریہ:
    حالت MAX_اظہاریہ:
      /* Used for OpenMP atomics.  */
      gcc_assert (flag_openmp);
      common = 1;
      توڑو;

    طےشدہ:
      gcc_unreachable ();
    }

  اگر (code0 == ERROR_MARK || code1 == ERROR_MARK)
    واپس error_mark_گرہ;

  اگر (gnu_سمتیہ_type_p (type0)
      && gnu_سمتیہ_type_p (type1)
      && (!درخت_int_cst_equal (TYPE_سائز (type0), TYPE_سائز (type1))
	  || !سمتیہ_types_compatible_elements_p (type0, type1)))
    {
      gcc_rich_location richloc (location);
      maybe_range_label_for_درخت_type_mismatch
	label_for_op0 (orig_op0, orig_op1),
	label_for_op1 (orig_op1, orig_op0);
      richloc.maybe_جوڑو_اظہاریہ (orig_op0, &label_for_op0, highlight_colors::lhs);
      richloc.maybe_جوڑو_اظہاریہ (orig_op1, &label_for_op1, highlight_colors::rhs);
      ثنائی_op_error (&richloc, رمز, type0, type1);
      واپس error_mark_گرہ;
    }

  اگر ((code0 == INTEGER_TYPE || code0 == REAL_TYPE || code0 == COMPLEX_TYPE
       || code0 == FIXED_نقطہ_TYPE || code0 == BITINT_TYPE
       || gnu_سمتیہ_type_p (type0))
      && (code1 == INTEGER_TYPE || code1 == REAL_TYPE || code1 == COMPLEX_TYPE
	  || code1 == FIXED_نقطہ_TYPE || code1 == BITINT_TYPE
	  || gnu_سمتیہ_type_p (type1)))
    {
      منطقی پہلا_complex = (code0 == COMPLEX_TYPE);
      منطقی دوسرا_complex = (code1 == COMPLEX_TYPE);
      صحیح none_complex = (!پہلا_complex && !دوسرا_complex);

      اگر (shorten || common || short_compare)
	{
	  نتیجہ_type = c_common_type (type0, type1);
	  do_warn_double_promotion (نتیجہ_type, type0, type1,
				    "implicit conversion from %qT to %qT "
				    "to match other operand of binary "
				    "expression",
				    location);
	  اگر (نتیجہ_type == error_mark_گرہ)
	    واپس error_mark_گرہ;
	}

      اگر (پہلا_complex != دوسرا_complex
	  && (رمز == PLUS_اظہاریہ
	      || رمز == MINUS_اظہاریہ
	      || رمز == MULT_اظہاریہ
	      || (رمز == TRUNC_DIV_اظہاریہ && پہلا_complex))
	  && درخت_رمز (درخت_TYPE (نتیجہ_type)) == REAL_TYPE
	  && flag_signed_zeros)
	{
	  /* An operation on mixed real/complex operands must be
	     handled specially, but the language-independent code can
	     more easily optimize the plain complex arithmetic if
	     -fno-signed-zeros.  */
	  درخت real_type = درخت_TYPE (نتیجہ_type);
	  درخت real, imag;
	  اگر (type0 != orig_type0 || type1 != orig_type1)
	    {
	      gcc_assert (may_need_excess_precision && common);
	      semantic_نتیجہ_type = c_common_type (orig_type0, orig_type1);
	    }
	  اگر (پہلا_complex)
	    {
	      اگر (درخت_TYPE (op0) != نتیجہ_type)
		op0 = convert_and_check (location, نتیجہ_type, op0);
	      اگر (درخت_TYPE (op1) != real_type)
		op1 = convert_and_check (location, real_type, op1);
	    }
	  ورنہ
	    {
	      اگر (درخت_TYPE (op0) != real_type)
		op0 = convert_and_check (location, real_type, op0);
	      اگر (درخت_TYPE (op1) != نتیجہ_type)
		op1 = convert_and_check (location, نتیجہ_type, op1);
	    }
	  اگر (درخت_رمز (op0) == ERROR_MARK || درخت_رمز (op1) == ERROR_MARK)
	    واپس error_mark_گرہ;
	  اگر (پہلا_complex)
	    {
	      op0 = save_اظہاریہ (op0);
	      real = build_unary_op (اظہاریہ_LOCATION (orig_op0), REALPART_اظہاریہ,
				     op0, سچ);
	      imag = build_unary_op (اظہاریہ_LOCATION (orig_op0), IMAGPART_اظہاریہ,
				     op0, سچ);
	      انتخاب (رمز)
		{
		حالت MULT_اظہاریہ:
		حالت TRUNC_DIV_اظہاریہ:
		  op1 = save_اظہاریہ (op1);
		  imag = build2 (resultcode, real_type, imag, op1);
		  /* Fall through.  */
		حالت PLUS_اظہاریہ:
		حالت MINUS_اظہاریہ:
		  real = build2 (resultcode, real_type, real, op1);
		  توڑو;
		طےشدہ:
		  gcc_unreachable();
		}
	    }
	  ورنہ
	    {
	      op1 = save_اظہاریہ (op1);
	      real = build_unary_op (اظہاریہ_LOCATION (orig_op1), REALPART_اظہاریہ,
				     op1, سچ);
	      imag = build_unary_op (اظہاریہ_LOCATION (orig_op1), IMAGPART_اظہاریہ,
				     op1, سچ);
	      انتخاب (رمز)
		{
		حالت MULT_اظہاریہ:
		  op0 = save_اظہاریہ (op0);
		  imag = build2 (resultcode, real_type, op0, imag);
		  /* Fall through.  */
		حالت PLUS_اظہاریہ:
		  real = build2 (resultcode, real_type, op0, real);
		  توڑو;
		حالت MINUS_اظہاریہ:
		  real = build2 (resultcode, real_type, op0, real);
		  imag = build1 (NEGATE_اظہاریہ, real_type, imag);
		  توڑو;
		طےشدہ:
		  gcc_unreachable();
		}
	    }
	  ret = build2 (COMPLEX_اظہاریہ, نتیجہ_type, real, imag);
	  جاؤ return_build_ثنائی_op;
	}

      /* For certain operations (which identify themselves by shorten != 0)
	 if both args were extended from the same smaller type,
	 do the arithmetic in that type and then extend.

	 shorten !=0 and !=1 indicates a bitwise operation.
	 For them, this optimization is safe only if
	 both args are zero-extended or both are sign-extended.
	 Otherwise, we might change the result.
	 Eg, (short)-1 | (unsigned short)-1 is (int)-1
	 but calculated in (unsigned short) it would be (unsigned short)-1.  */

      اگر (shorten && none_complex)
	{
	  final_type = نتیجہ_type;
	  نتیجہ_type = shorten_ثنائی_op (نتیجہ_type, op0, op1,
					   shorten == -1);
	}

      /* Shifts can be shortened if shifting right.  */

      اگر (short_سرکاؤ)
	{
	  صحیح unsigned_arg;
	  درخت arg0 = get_narrower (op0, &unsigned_arg);

	  final_type = نتیجہ_type;

	  اگر (arg0 == op0 && final_type == درخت_TYPE (op0))
	    unsigned_arg = TYPE_UNSIGNED (درخت_TYPE (op0));

	  اگر (TYPE_PRECISION (درخت_TYPE (arg0)) < TYPE_PRECISION (نتیجہ_type)
	      && درخت_int_cst_sgn (op1) > 0
	      /* We can shorten only if the shift count is less than the
		 number of bits in the smaller type size.  */
	      && compare_درخت_int (op1, TYPE_PRECISION (درخت_TYPE (arg0))) < 0
	      /* We cannot drop an unsigned shift after sign-extension.  */
	      && (!TYPE_UNSIGNED (final_type) || unsigned_arg))
	    {
	      /* Do an unsigned shift if the operand was zero-extended.  */
	      نتیجہ_type
		= c_common_signed_or_unsigned_type (unsigned_arg,
						    درخت_TYPE (arg0));
	      /* Convert value-to-be-shifted to that type.  */
	      اگر (درخت_TYPE (op0) != نتیجہ_type)
		op0 = convert (نتیجہ_type, op0);
	      converted = 1;
	    }
	}

      /* Comparison operations are shortened too but differently.
	 They identify themselves by setting short_compare = 1.  */

      اگر (short_compare)
	{
	  /* Don't write &op0, etc., because that would prevent op0
	     from being kept in a register.
	     Instead, make copies of the our local variables and
	     pass the copies by reference, then copy them back afterward.  */
	  درخت xop0 = op0, xop1 = op1, xresult_type = نتیجہ_type;
	  شمار درخت_رمز_2 xresultcode = resultcode;
	  درخت val
	    = shorten_compare (location, &xop0, &xop1, &xresult_type,
			       &xresultcode);

	  اگر (val != NULL_درخت)
	    {
	      ret = val;
	      جاؤ return_build_ثنائی_op;
	    }

	  op0 = xop0, op1 = xop1;
	  converted = 1;
	  resultcode = xresultcode;

	  اگر (c_inhibit_evaluation_warnings == 0 && !c_اندر_omp_for)
	    {
	      منطقی op0_maybe_const = سچ;
	      منطقی op1_maybe_const = سچ;
	      درخت orig_op0_folded, orig_op1_folded;

	      اگر (اندر_late_ثنائی_op)
		{
		  orig_op0_folded = orig_op0;
		  orig_op1_folded = orig_op1;
		}
	      ورنہ
		{
		  /* Fold for the sake of possible warnings, as in
		     build_conditional_expr.  This requires the
		     "original" values to be folded, not just op0 and
		     op1.  */
		  c_inhibit_evaluation_warnings++;
		  op0 = c_fully_fold (op0, require_constant_قدر,
				      &op0_maybe_const);
		  op1 = c_fully_fold (op1, require_constant_قدر,
				      &op1_maybe_const);
		  c_inhibit_evaluation_warnings--;
		  orig_op0_folded = c_fully_fold (orig_op0,
						  require_constant_قدر,
						  تہی);
		  orig_op1_folded = c_fully_fold (orig_op1,
						  require_constant_قدر,
						  تہی);
		}

	      اگر (warn_sign_compare)
		warn_for_sign_compare (location, orig_op0_folded,
				       orig_op1_folded, op0, op1,
				       نتیجہ_type, resultcode);
	      اگر (!اندر_late_ثنائی_op && !int_operands)
		{
		  اگر (!op0_maybe_const || درخت_رمز (op0) != INTEGER_CST)
		    op0 = c_wrap_maybe_const (op0, !op0_maybe_const);
		  اگر (!op1_maybe_const || درخت_رمز (op1) != INTEGER_CST)
		    op1 = c_wrap_maybe_const (op1, !op1_maybe_const);
		}
	    }
	}
    }

  /* At this point, RESULT_TYPE must be nonzero to avoid an error message.
     If CONVERTED is zero, both args will be converted to type RESULT_TYPE.
     Then the expression will be built.
     It will be given type FINAL_TYPE if that is nonzero;
     otherwise, it will be given type RESULT_TYPE.  */

  اگر (!نتیجہ_type)
    {
      /* Favor showing any expression locations that are available. */
      op_location_t oploc (location, UNKNOWN_LOCATION);
      ثنائی_op_rich_location richloc (oploc, orig_op0, orig_op1, سچ);
      ثنائی_op_error (&richloc, رمز, درخت_TYPE (op0), درخت_TYPE (op1));
      واپس error_mark_گرہ;
    }

  اگر (build_type == NULL_درخت)
    {
      build_type = نتیجہ_type;
      اگر ((type0 != orig_type0 || type1 != orig_type1)
	  && !boolean_op)
	{
	  gcc_assert (may_need_excess_precision && common);
	  semantic_نتیجہ_type = c_common_type (orig_type0, orig_type1);
	}
    }

  اگر (!converted)
    {
      op0 = ep_convert_and_check (location, نتیجہ_type, op0,
				  semantic_نتیجہ_type);
      op1 = ep_convert_and_check (location, نتیجہ_type, op1,
				  semantic_نتیجہ_type);

      /* This can happen if one operand has a vector type, and the other
	 has a different type.  */
      اگر (درخت_رمز (op0) == ERROR_MARK || درخت_رمز (op1) == ERROR_MARK)
	واپس error_mark_گرہ;
    }

  اگر (sanitize_flags_p ((SANITIZE_سرکاؤ
			 | SANITIZE_DIVIDE
			 | SANITIZE_FLOAT_DIVIDE
			 | SANITIZE_SI_حد_سے_تجاوز))
      && current_function_decl != NULL_درخت
      && (doing_div_or_mod || doing_سرکاؤ)
      && !require_constant_قدر)
    {
      /* OP0 and/or OP1 might have side-effects.  */
      op0 = save_اظہاریہ (op0);
      op1 = save_اظہاریہ (op1);
      op0 = c_fully_fold (op0, جھوٹ, تہی);
      op1 = c_fully_fold (op1, جھوٹ, تہی);
      اگر (doing_div_or_mod && (sanitize_flags_p ((SANITIZE_DIVIDE
						  | SANITIZE_FLOAT_DIVIDE
						  | SANITIZE_SI_حد_سے_تجاوز))))
	instrument_اظہاریہ = ubsan_instrument_division (location, op0, op1);
      ورنہ اگر (doing_سرکاؤ && sanitize_flags_p (SANITIZE_سرکاؤ))
	instrument_اظہاریہ = ubsan_instrument_سرکاؤ (location, رمز, op0, op1);
    }

  /* Treat expressions in initializers specially as they can't trap.  */
  اگر (int_const_or_حد_سے_تجاوز)
    ret = (require_constant_قدر
	   ? fold_build2_initializer_loc (location, resultcode, build_type,
					  op0, op1)
	   : fold_build2_loc (location, resultcode, build_type, op0, op1));
  ورنہ
    ret = build2 (resultcode, build_type, op0, op1);
  اگر (final_type != NULL_درخت)
    ret = convert (final_type, ret);

 return_build_ثنائی_op:
  gcc_assert (ret != error_mark_گرہ);
  اگر (درخت_رمز (ret) == INTEGER_CST && !درخت_حد_سے_تجاوز (ret) && !int_const)
    ret = (int_operands
	   ? note_integer_operands (ret)
	   : build1 (NOP_اظہاریہ, درخت_TYPE (ret), ret));
  ورنہ اگر (درخت_رمز (ret) != INTEGER_CST && int_operands
	   && !اندر_late_ثنائی_op)
    ret = note_integer_operands (ret);
  protected_سیٹ_اظہاریہ_location (ret, location);

  اگر (instrument_اظہاریہ != تہی)
    ret = fold_build2 (COMPOUND_اظہاریہ, درخت_TYPE (ret),
		       instrument_اظہاریہ, ret);

  اگر (semantic_نتیجہ_type)
    ret = build1_loc (location, EXCESS_PRECISION_اظہاریہ,
		      semantic_نتیجہ_type, ret);

  واپس ret;
}


/* Convert EXPR to be a truth-value (type TYPE), validating its type for this
   purpose.  LOCATION is the source location for the expression.  */

درخت
c_objc_common_truthvalue_conversion (location_t location, درخت اظہاریہ, درخت type)
{
  منطقی int_const, int_operands;

  انتخاب (درخت_رمز (درخت_TYPE (اظہاریہ)))
    {
    حالت ARRAY_TYPE:
      error_at (location, "used array that cannot be converted to pointer where scalar is required");
      واپس error_mark_گرہ;

    حالت ریکارڈ_TYPE:
      error_at (location, "used struct type value where scalar is required");
      واپس error_mark_گرہ;

    حالت UNION_TYPE:
      error_at (location, "used union type value where scalar is required");
      واپس error_mark_گرہ;

    حالت VOID_TYPE:
      error_at (location, "void value not ignored as it ought to be");
      واپس error_mark_گرہ;

    حالت اشارہ_گر_TYPE:
      اگر (reject_gcc_builtin (اظہاریہ))
	واپس error_mark_گرہ;
      توڑو;

    حالت FUNCTION_TYPE:
      gcc_unreachable ();

    حالت سمتیہ_TYPE:
      error_at (location, "used vector type where scalar is required");
      واپس error_mark_گرہ;

    طےشدہ:
      توڑو;
    }

  /* Conversion of a floating constant to boolean goes through here
     and yields an integer constant expression.  Otherwise, the result
     is only an integer constant expression if the argument is.  */
  int_const = ((درخت_رمز (اظہاریہ) == INTEGER_CST && !درخت_حد_سے_تجاوز (اظہاریہ))
	       || ((درخت_رمز (اظہاریہ) == REAL_CST
		    || درخت_رمز (اظہاریہ) == COMPLEX_CST)
		   && (درخت_رمز (type) == BOOLEAN_TYPE
		       || (درخت_رمز (type) == ENUMERAL_TYPE
			   && ENUM_UNDERLYING_TYPE (type) != NULL_درخت
			   && (درخت_رمز (ENUM_UNDERLYING_TYPE (type))
			       == BOOLEAN_TYPE)))));
  int_operands = اظہاریہ_INT_CONST_OPERANDS (اظہاریہ);
  اگر (int_operands && درخت_رمز (اظہاریہ) != INTEGER_CST)
    {
      اظہاریہ = remove_c_maybe_const_اظہاریہ (اظہاریہ);
      اظہاریہ = build2 (NE_اظہاریہ, type, اظہاریہ,
		     convert (درخت_TYPE (اظہاریہ), integer_zero_گرہ));
      اظہاریہ = note_integer_operands (اظہاریہ);
    }
  ورنہ
    {
      /* ??? Should we also give an error for vectors rather than leaving
	 those to give errors later?  */
      اظہاریہ = c_common_truthvalue_conversion (location, اظہاریہ);
      اظہاریہ = fold_convert_loc (location, type, اظہاریہ);
    }

  اگر (درخت_رمز (اظہاریہ) == INTEGER_CST && int_operands && !int_const)
    {
      اگر (درخت_حد_سے_تجاوز (اظہاریہ))
	واپس اظہاریہ;
      ورنہ
	واپس note_integer_operands (اظہاریہ);
    }
  اگر (درخت_رمز (اظہاریہ) == INTEGER_CST && !int_const)
    واپس build1 (NOP_اظہاریہ, درخت_TYPE (اظہاریہ), اظہاریہ);
  واپس اظہاریہ;
}


/* Convert EXPR to a contained DECL, updating *TC, *TI and *SE as
   required.  */

درخت
c_اظہاریہ_مقصد_decl (درخت اظہاریہ, منطقی *tc ATTRIBUTE_غیر_مستعمل, منطقی *se)
{
  اگر (درخت_رمز (اظہاریہ) == COMPOUND_LITERAL_اظہاریہ)
    {
      درخت decl = COMPOUND_LITERAL_اظہاریہ_DECL (اظہاریہ);
      /* Executing a compound literal inside a function reinitializes
	 it.  */
      اگر (!درخت_STATIC (decl))
	*se = سچ;
      واپس decl;
    }
  ورنہ
    واپس اظہاریہ;
}

/* Generate OMP construct CODE, with BODY and CLAUSES as its compound
   statement.  LOC is the location of the construct.  */

درخت
c_اختتام_omp_construct (location_t loc, شمار درخت_رمز_2 رمز, درخت body,
			درخت clauses)
{
  body = c_انتہا_compound_stmt (loc, body, سچ);

  درخت stmt = make_گرہ (رمز);
  درخت_TYPE (stmt) = void_type_گرہ;
  OMP_BODY (stmt) = body;
  OMP_CLAUSES (stmt) = clauses;
  سیٹ_اظہاریہ_LOCATION (stmt, loc);

  واپس جوڑو_stmt (stmt);
}

/* Generate OACC_DATA, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the OACC_DATA.  */

درخت
c_اختتام_oacc_ڈیٹا (location_t loc, درخت clauses, درخت بلاک)
{
  درخت stmt;

  بلاک = c_انتہا_compound_stmt (loc, بلاک, سچ);

  stmt = make_گرہ (OACC_ڈیٹا);
  درخت_TYPE (stmt) = void_type_گرہ;
  OACC_ڈیٹا_CLAUSES (stmt) = clauses;
  OACC_ڈیٹا_BODY (stmt) = بلاک;
  سیٹ_اظہاریہ_LOCATION (stmt, loc);

  واپس جوڑو_stmt (stmt);
}

/* Generate OACC_HOST_DATA, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the OACC_HOST_DATA.  */

درخت
c_اختتام_oacc_host_ڈیٹا (location_t loc, درخت clauses, درخت بلاک)
{
  درخت stmt;

  بلاک = c_انتہا_compound_stmt (loc, بلاک, سچ);

  stmt = make_گرہ (OACC_HOST_ڈیٹا);
  درخت_TYPE (stmt) = void_type_گرہ;
  OACC_HOST_ڈیٹا_CLAUSES (stmt) = clauses;
  OACC_HOST_ڈیٹا_BODY (stmt) = بلاک;
  سیٹ_اظہاریہ_LOCATION (stmt, loc);

  واپس جوڑو_stmt (stmt);
}

/* Like c_begin_compound_stmt, except force the retention of the BLOCK.  */

درخت
c_begin_omp_parallel (خالی)
{
  درخت بلاک;

  keep_اگلا_level ();
  بلاک = c_begin_compound_stmt (سچ);

  واپس بلاک;
}

/* Generate OMP_PARALLEL, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the OMP_PARALLEL.  */

درخت
c_اختتام_omp_parallel (location_t loc, درخت clauses, درخت بلاک)
{
  درخت stmt;

  بلاک = c_انتہا_compound_stmt (loc, بلاک, سچ);

  stmt = make_گرہ (OMP_PARALLEL);
  درخت_TYPE (stmt) = void_type_گرہ;
  OMP_PARALLEL_CLAUSES (stmt) = clauses;
  OMP_PARALLEL_BODY (stmt) = بلاک;
  سیٹ_اظہاریہ_LOCATION (stmt, loc);

  واپس جوڑو_stmt (stmt);
}

/* Like c_begin_compound_stmt, except force the retention of the BLOCK.  */

درخت
c_begin_omp_task (خالی)
{
  درخت بلاک;

  keep_اگلا_level ();
  بلاک = c_begin_compound_stmt (سچ);

  واپس بلاک;
}

/* Generate OMP_TASK, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the #pragma.  */

درخت
c_اختتام_omp_task (location_t loc, درخت clauses, درخت بلاک)
{
  درخت stmt;

  بلاک = c_انتہا_compound_stmt (loc, بلاک, سچ);

  stmt = make_گرہ (OMP_TASK);
  درخت_TYPE (stmt) = void_type_گرہ;
  OMP_TASK_CLAUSES (stmt) = clauses;
  OMP_TASK_BODY (stmt) = بلاک;
  سیٹ_اظہاریہ_LOCATION (stmt, loc);

  واپس جوڑو_stmt (stmt);
}

/* Generate GOMP_cancel call for #pragma omp cancel.  */

خالی
c_اختتام_omp_cancel (location_t loc, درخت clauses)
{
  درخت fn = builtin_decl_explicit (BUILT_اندر_GOMP_CANCEL);
  صحیح نقاب = 0;
  اگر (omp_ڈھونڈو_clause (clauses, OMP_CLAUSE_PARALLEL))
    نقاب = 1;
  ورنہ اگر (omp_ڈھونڈو_clause (clauses, OMP_CLAUSE_FOR))
    نقاب = 2;
  ورنہ اگر (omp_ڈھونڈو_clause (clauses, OMP_CLAUSE_SECTIONS))
    نقاب = 4;
  ورنہ اگر (omp_ڈھونڈو_clause (clauses, OMP_CLAUSE_TASKGROUP))
    نقاب = 8;
  ورنہ
    {
      error_at (loc, "%<#pragma omp cancel%> must specify one of "
		     "%<parallel%>, %<for%>, %<sections%> or %<taskgroup%> "
		     "clauses");
      واپس;
    }
  درخت ifc = omp_ڈھونڈو_clause (clauses, OMP_CLAUSE_IF);
  اگر (ifc != NULL_درخت)
    {
      اگر (OMP_CLAUSE_IF_MODIFIER (ifc) != ERROR_MARK
	  && OMP_CLAUSE_IF_MODIFIER (ifc) != VOID_CST)
	error_at (OMP_CLAUSE_LOCATION (ifc),
		  "expected %<cancel%> %<if%> clause modifier");
      ورنہ
	{
	  درخت ifc2 = omp_ڈھونڈو_clause (OMP_CLAUSE_CHAIN (ifc), OMP_CLAUSE_IF);
	  اگر (ifc2 != NULL_درخت)
	    {
	      gcc_assert (OMP_CLAUSE_IF_MODIFIER (ifc) == VOID_CST
			  && OMP_CLAUSE_IF_MODIFIER (ifc2) != ERROR_MARK
			  && OMP_CLAUSE_IF_MODIFIER (ifc2) != VOID_CST);
	      error_at (OMP_CLAUSE_LOCATION (ifc2),
			"expected %<cancel%> %<if%> clause modifier");
	    }
	}

      درخت type = درخت_TYPE (OMP_CLAUSE_IF_اظہاریہ (ifc));
      ifc = fold_build2_loc (OMP_CLAUSE_LOCATION (ifc), NE_اظہاریہ,
			     boolean_type_گرہ, OMP_CLAUSE_IF_اظہاریہ (ifc),
			     build_zero_cst (type));
    }
  ورنہ
    ifc = boolean_true_گرہ;
  درخت stmt = build_call_اظہاریہ_loc (loc, fn, 2,
				   build_int_cst (integer_type_گرہ, نقاب),
				   ifc);
  جوڑو_stmt (stmt);
}

/* Generate GOMP_cancellation_point call for
   #pragma omp cancellation point.  */

خالی
c_اختتام_omp_cancellation_نقطہ (location_t loc, درخت clauses)
{
  درخت fn = builtin_decl_explicit (BUILT_اندر_GOMP_CANCELLATION_نقطہ);
  صحیح نقاب = 0;
  اگر (omp_ڈھونڈو_clause (clauses, OMP_CLAUSE_PARALLEL))
    نقاب = 1;
  ورنہ اگر (omp_ڈھونڈو_clause (clauses, OMP_CLAUSE_FOR))
    نقاب = 2;
  ورنہ اگر (omp_ڈھونڈو_clause (clauses, OMP_CLAUSE_SECTIONS))
    نقاب = 4;
  ورنہ اگر (omp_ڈھونڈو_clause (clauses, OMP_CLAUSE_TASKGROUP))
    نقاب = 8;
  ورنہ
    {
      error_at (loc, "%<#pragma omp cancellation point%> must specify one of "
		     "%<parallel%>, %<for%>, %<sections%> or %<taskgroup%> "
		     "clauses");
      واپس;
    }
  درخت stmt = build_call_اظہاریہ_loc (loc, fn, 1,
				   build_int_cst (integer_type_گرہ, نقاب));
  جوڑو_stmt (stmt);
}

/* Helper function for handle_omp_array_sections.  Called recursively
   to handle multiple array-section-subscripts.  C is the clause,
   T current expression (initially OMP_CLAUSE_DECL), which is either
   a TREE_LIST for array-section-subscript (TREE_PURPOSE is low-bound
   expression if specified, TREE_VALUE length expression if specified,
   TREE_CHAIN is what it has been specified after, or some decl.
   TYPES vector is populated with array section types, MAYBE_ZERO_LEN
   set to true if any of the array-section-subscript could have length
   of zero (explicit or implicit), FIRST_NON_ONE is the index of the
   first array-section-subscript which is known not to have length
   of one.  Given say:
   map(a[:b][2:1][:c][:2][:d][e:f][2:5])
   FIRST_NON_ONE will be 3, array-section-subscript [:b], [2:1] and [:c]
   all are or may have length of 1, array-section-subscript [:2] is the
   first one known not to have length 1.  For array-section-subscript
   <= FIRST_NON_ONE we diagnose non-contiguous arrays if low bound isn't
   0 or length isn't the array domain max + 1, for > FIRST_NON_ONE we
   can if MAYBE_ZERO_LEN is false.  MAYBE_ZERO_LEN will be true in the above
   case though, as some lengths could be zero.  */

ساکن درخت
handle_omp_array_sections_1 (درخت c, درخت t, vec<درخت> &types,
			     منطقی &maybe_zero_len, غیرعلامتی صحیح &پہلا_non_one,
			     شمار c_omp_region_type ort)
{
  درخت ret, کم_bound, لمبائی, type;
  منطقی openacc = (ort & C_ORT_ACC) != 0;
  اگر (درخت_رمز (t) != OMP_ARRAY_SECTION)
    {
      اگر (error_عملیہ_p (t))
	واپس error_mark_گرہ;
      c_omp_پتہ_inspector ai (OMP_CLAUSE_LOCATION (c), t);
      ret = t;
      اگر (OMP_CLAUSE_رمز (c) != OMP_CLAUSE_AFFINITY
	  && OMP_CLAUSE_رمز (c) != OMP_CLAUSE_DEPEND
	  && TYPE_ATOMIC (strip_array_types (درخت_TYPE (t))))
	{
	  error_at (OMP_CLAUSE_LOCATION (c), "%<_Atomic%> %qE in %qs clause",
		    t, omp_clause_رمز_name[OMP_CLAUSE_رمز (c)]);
	  واپس error_mark_گرہ;
	}
      اگر (!ai.check_clause (c))
	واپس error_mark_گرہ;
      ورنہ اگر (ai.component_access_p ()
	       && (OMP_CLAUSE_رمز (c) == OMP_CLAUSE_MAP
		   || OMP_CLAUSE_رمز (c) == OMP_CLAUSE_مقصد
		   || OMP_CLAUSE_رمز (c) == OMP_CLAUSE_FROM))
	t = ai.get_جڑ_رکن (سچ);
      ورنہ
	t = ai.unconverted_ref_origin ();
      اگر (t == error_mark_گرہ)
	واپس error_mark_گرہ;
      اگر (!VAR_P (t)
	  && (ort == C_ORT_ACC || !اظہاریہ_P (t))
	  && درخت_رمز (t) != PARM_DECL)
	{
	  اگر (DECL_P (t))
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD is not a variable in %qs clause", t,
		      omp_clause_رمز_name[OMP_CLAUSE_رمز (c)]);
	  ورنہ
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qE is not a variable in %qs clause", t,
		      omp_clause_رمز_name[OMP_CLAUSE_رمز (c)]);
	  واپس error_mark_گرہ;
	}
      ورنہ اگر (OMP_CLAUSE_رمز (c) != OMP_CLAUSE_AFFINITY
	       && OMP_CLAUSE_رمز (c) != OMP_CLAUSE_DEPEND
	       && TYPE_ATOMIC (درخت_TYPE (t)))
	{
	  error_at (OMP_CLAUSE_LOCATION (c), "%<_Atomic%> %qD in %qs clause",
		    t, omp_clause_رمز_name[OMP_CLAUSE_رمز (c)]);
	  واپس error_mark_گرہ;
	}
      ورنہ اگر (OMP_CLAUSE_رمز (c) != OMP_CLAUSE_AFFINITY
	       && OMP_CLAUSE_رمز (c) != OMP_CLAUSE_DEPEND
	       && VAR_P (t)
	       && DECL_THREAD_LOCAL_P (t))
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "%qD is threadprivate variable in %qs clause", t,
		    omp_clause_رمز_name[OMP_CLAUSE_رمز (c)]);
	  واپس error_mark_گرہ;
	}
      اگر ((OMP_CLAUSE_رمز (c) == OMP_CLAUSE_AFFINITY
	   || OMP_CLAUSE_رمز (c) == OMP_CLAUSE_DEPEND)
	  && TYPE_ATOMIC (درخت_TYPE (t))
	  && اشارہ_گر_TYPE_P (درخت_TYPE (t)))
	{
	  /* If the array section is pointer based and the pointer
	     itself is _Atomic qualified, we need to atomically load
	     the pointer.  */
	  ret = convert_lvalue_مقصد_rvalue (OMP_CLAUSE_LOCATION (c),
					  ret, جھوٹ, جھوٹ);
	}
      واپس ret;
    }

  ret = handle_omp_array_sections_1 (c, درخت_عملیہ (t, 0), types,
				     maybe_zero_len, پہلا_non_one, ort);
  اگر (ret == error_mark_گرہ || ret == NULL_درخت)
    واپس ret;

  type = درخت_TYPE (ret);
  کم_bound = درخت_عملیہ (t, 1);
  لمبائی = درخت_عملیہ (t, 2);

  اگر (کم_bound == error_mark_گرہ || لمبائی == error_mark_گرہ)
    واپس error_mark_گرہ;

  اگر (کم_bound && !INTEGRAL_TYPE_P (درخت_TYPE (کم_bound)))
    {
      error_at (OMP_CLAUSE_LOCATION (c),
		"low bound %qE of array section does not have integral type",
		کم_bound);
      واپس error_mark_گرہ;
    }
  اگر (لمبائی && !INTEGRAL_TYPE_P (درخت_TYPE (لمبائی)))
    {
      error_at (OMP_CLAUSE_LOCATION (c),
		"length %qE of array section does not have integral type",
		لمبائی);
      واپس error_mark_گرہ;
    }
  اگر (کم_bound
      && درخت_رمز (کم_bound) == INTEGER_CST
      && TYPE_PRECISION (درخت_TYPE (کم_bound))
	 > TYPE_PRECISION (sizetype))
    کم_bound = fold_convert (sizetype, کم_bound);
  اگر (لمبائی
      && درخت_رمز (لمبائی) == INTEGER_CST
      && TYPE_PRECISION (درخت_TYPE (لمبائی))
	 > TYPE_PRECISION (sizetype))
    لمبائی = fold_convert (sizetype, لمبائی);
  اگر (کم_bound == NULL_درخت)
    کم_bound = integer_zero_گرہ;
  اگر (OMP_CLAUSE_رمز (c) == OMP_CLAUSE_MAP
      && (OMP_CLAUSE_MAP_قسم (c) == GOMP_MAP_ATTACH
	  || OMP_CLAUSE_MAP_قسم (c) == GOMP_MAP_DETACH))
    {
      اگر (لمبائی != integer_one_گرہ)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "expected single pointer in %qs clause",
		    user_omp_clause_رمز_name (c, openacc));
	  واپس error_mark_گرہ;
	}
    }
  اگر (لمبائی != NULL_درخت)
    {
      اگر (!integer_nonzerop (لمبائی))
	{
	  اگر (OMP_CLAUSE_رمز (c) == OMP_CLAUSE_AFFINITY
	      || OMP_CLAUSE_رمز (c) == OMP_CLAUSE_DEPEND
	      || OMP_CLAUSE_رمز (c) == OMP_CLAUSE_REDUCTION
	      || OMP_CLAUSE_رمز (c) == OMP_CLAUSE_اندر_REDUCTION
	      || OMP_CLAUSE_رمز (c) == OMP_CLAUSE_TASK_REDUCTION)
	    {
	      اگر (integer_zerop (لمبائی))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "zero length array section in %qs clause",
			    omp_clause_رمز_name[OMP_CLAUSE_رمز (c)]);
		  واپس error_mark_گرہ;
		}
	    }
	  ورنہ
	    maybe_zero_len = سچ;
	}
      اگر (پہلا_non_one == types.لمبائی ()
	  && (درخت_رمز (لمبائی) != INTEGER_CST || integer_onep (لمبائی)))
	پہلا_non_one++;
    }
  اگر (درخت_رمز (type) == ARRAY_TYPE)
    {
      اگر (لمبائی == NULL_درخت
	  && (TYPE_DOMAIN (type) == NULL_درخت
	      || TYPE_MAX_قدر (TYPE_DOMAIN (type)) == NULL_درخت))
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "for unknown bound array type length expression must "
		    "be specified");
	  واپس error_mark_گرہ;
	}
      اگر (درخت_رمز (کم_bound) == INTEGER_CST
	  && درخت_int_cst_sgn (کم_bound) == -1)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "negative low bound in array section in %qs clause",
		    omp_clause_رمز_name[OMP_CLAUSE_رمز (c)]);
	  واپس error_mark_گرہ;
	}
      اگر (لمبائی != NULL_درخت
	  && درخت_رمز (لمبائی) == INTEGER_CST
	  && درخت_int_cst_sgn (لمبائی) == -1)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "negative length in array section in %qs clause",
		    omp_clause_رمز_name[OMP_CLAUSE_رمز (c)]);
	  واپس error_mark_گرہ;
	}
      اگر (TYPE_DOMAIN (type)
	  && TYPE_MAX_قدر (TYPE_DOMAIN (type))
	  && درخت_رمز (TYPE_MAX_قدر (TYPE_DOMAIN (type)))
			== INTEGER_CST)
	{
	  درخت سائز
	    = fold_convert (sizetype, TYPE_MAX_قدر (TYPE_DOMAIN (type)));
	  سائز = سائز_binop (PLUS_اظہاریہ, سائز, سائز_one_گرہ);
	  اگر (درخت_رمز (کم_bound) == INTEGER_CST)
	    {
	      اگر (درخت_int_cst_lt (سائز, کم_bound))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "low bound %qE above array section size "
			    "in %qs clause", کم_bound,
			    omp_clause_رمز_name[OMP_CLAUSE_رمز (c)]);
		  واپس error_mark_گرہ;
		}
	      اگر (درخت_int_cst_equal (سائز, کم_bound))
		{
		  اگر (OMP_CLAUSE_رمز (c) == OMP_CLAUSE_AFFINITY
		      || OMP_CLAUSE_رمز (c) == OMP_CLAUSE_DEPEND
		      || OMP_CLAUSE_رمز (c) == OMP_CLAUSE_REDUCTION
		      || OMP_CLAUSE_رمز (c) == OMP_CLAUSE_اندر_REDUCTION
		      || OMP_CLAUSE_رمز (c) == OMP_CLAUSE_TASK_REDUCTION)
		    {
		      error_at (OMP_CLAUSE_LOCATION (c),
				"zero length array section in %qs clause",
				omp_clause_رمز_name[OMP_CLAUSE_رمز (c)]);
		      واپس error_mark_گرہ;
		    }
		  maybe_zero_len = سچ;
		}
	      ورنہ اگر (لمبائی == NULL_درخت
		       && پہلا_non_one == types.لمبائی ()
		       && درخت_int_cst_equal
			    (TYPE_MAX_قدر (TYPE_DOMAIN (type)),
			     کم_bound))
		پہلا_non_one++;
	    }
	  ورنہ اگر (لمبائی == NULL_درخت)
	    {
	      اگر (OMP_CLAUSE_رمز (c) != OMP_CLAUSE_AFFINITY
		  && OMP_CLAUSE_رمز (c) != OMP_CLAUSE_DEPEND
		  && OMP_CLAUSE_رمز (c) != OMP_CLAUSE_REDUCTION
		  && OMP_CLAUSE_رمز (c) != OMP_CLAUSE_اندر_REDUCTION
		  && OMP_CLAUSE_رمز (c) != OMP_CLAUSE_TASK_REDUCTION)
		maybe_zero_len = سچ;
	      اگر (پہلا_non_one == types.لمبائی ())
		پہلا_non_one++;
	    }
	  اگر (لمبائی && درخت_رمز (لمبائی) == INTEGER_CST)
	    {
	      اگر (درخت_int_cst_lt (سائز, لمبائی))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "length %qE above array section size "
			    "in %qs clause", لمبائی,
			    omp_clause_رمز_name[OMP_CLAUSE_رمز (c)]);
		  واپس error_mark_گرہ;
		}
	      اگر (درخت_رمز (کم_bound) == INTEGER_CST)
		{
		  درخت lbpluslen
		    = سائز_binop (PLUS_اظہاریہ,
				  fold_convert (sizetype, کم_bound),
				  fold_convert (sizetype, لمبائی));
		  اگر (درخت_رمز (lbpluslen) == INTEGER_CST
		      && درخت_int_cst_lt (سائز, lbpluslen))
		    {
		      error_at (OMP_CLAUSE_LOCATION (c),
				"high bound %qE above array section size "
				"in %qs clause", lbpluslen,
				omp_clause_رمز_name[OMP_CLAUSE_رمز (c)]);
		      واپس error_mark_گرہ;
		    }
		}
	    }
	}
      ورنہ اگر (لمبائی == NULL_درخت)
	{
	  اگر (OMP_CLAUSE_رمز (c) != OMP_CLAUSE_AFFINITY
	      && OMP_CLAUSE_رمز (c) != OMP_CLAUSE_DEPEND
	      && OMP_CLAUSE_رمز (c) != OMP_CLAUSE_REDUCTION
	      && OMP_CLAUSE_رمز (c) != OMP_CLAUSE_اندر_REDUCTION
	      && OMP_CLAUSE_رمز (c) != OMP_CLAUSE_TASK_REDUCTION)
	    maybe_zero_len = سچ;
	  اگر (پہلا_non_one == types.لمبائی ())
	    پہلا_non_one++;
	}

      /* For [lb:] we will need to evaluate lb more than once.  */
      اگر (لمبائی == NULL_درخت && OMP_CLAUSE_رمز (c) != OMP_CLAUSE_DEPEND)
	{
	  درخت lb = save_اظہاریہ (کم_bound);
	  اگر (lb != کم_bound)
	    {
	      درخت_عملیہ (t, 1) = lb;
	      کم_bound = lb;
	    }
	}
    }
  ورنہ اگر (درخت_رمز (type) == اشارہ_گر_TYPE)
    {
      اگر (لمبائی == NULL_درخت)
	{
	  اگر (درخت_رمز (ret) == PARM_DECL && C_ARRAY_PARAMETER (ret))
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "for array function parameter length expression "
		      "must be specified");
	  ورنہ
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "for pointer type length expression must be specified");
	  واپس error_mark_گرہ;
	}
      اگر (لمبائی != NULL_درخت
	  && درخت_رمز (لمبائی) == INTEGER_CST
	  && درخت_int_cst_sgn (لمبائی) == -1)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "negative length in array section in %qs clause",
		    omp_clause_رمز_name[OMP_CLAUSE_رمز (c)]);
	  واپس error_mark_گرہ;
	}
      /* If there is a pointer type anywhere but in the very first
	 array-section-subscript, the array section could be non-contiguous.  */
      اگر (OMP_CLAUSE_رمز (c) != OMP_CLAUSE_DEPEND
	  && OMP_CLAUSE_رمز (c) != OMP_CLAUSE_AFFINITY
	  && درخت_رمز (درخت_عملیہ (t, 0)) == OMP_ARRAY_SECTION)
	{
	  /* If any prior dimension has a non-one length, then deem this
	     array section as non-contiguous.  */
	  برائے (درخت d = درخت_عملیہ (t, 0);
	       درخت_رمز (d) == OMP_ARRAY_SECTION;
	       d = درخت_عملیہ (d, 0))
	    {
	      درخت d_لمبائی = درخت_عملیہ (d, 2);
	      اگر (d_لمبائی == NULL_درخت || !integer_onep (d_لمبائی))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "array section is not contiguous in %qs clause",
			    omp_clause_رمز_name[OMP_CLAUSE_رمز (c)]);
		  واپس error_mark_گرہ;
		}
	    }
	}
    }
  ورنہ
    {
      error_at (OMP_CLAUSE_LOCATION (c),
		"%qE does not have pointer or array type", ret);
      واپس error_mark_گرہ;
    }
  اگر (OMP_CLAUSE_رمز (c) != OMP_CLAUSE_DEPEND)
    types.محفوظ_ڈالو (درخت_TYPE (ret));
  /* We will need to evaluate lb more than once.  */
  درخت lb = save_اظہاریہ (کم_bound);
  اگر (lb != کم_bound)
    {
      درخت_عملیہ (t, 1) = lb;
      کم_bound = lb;
    }
  ret = build_array_ref (OMP_CLAUSE_LOCATION (c), ret, کم_bound);
  واپس ret;
}

/* Handle array sections for clause C.  */

ساکن منطقی
handle_omp_array_sections (درخت &c, شمار c_omp_region_type ort)
{
  منطقی maybe_zero_len = جھوٹ;
  غیرعلامتی صحیح پہلا_non_one = 0;
  auto_vec<درخت, 10> types;
  درخت *tp = &OMP_CLAUSE_DECL (c);
  اگر ((OMP_CLAUSE_رمز (c) == OMP_CLAUSE_DEPEND
       || OMP_CLAUSE_رمز (c) == OMP_CLAUSE_AFFINITY)
      && OMP_ITERATOR_DECL_P (*tp))
    tp = &درخت_قدر (*tp);
  درخت پہلا = handle_omp_array_sections_1 (c, *tp, types,
					    maybe_zero_len, پہلا_non_one,
					    ort);
  اگر (پہلا == error_mark_گرہ)
    واپس سچ;
  اگر (پہلا == NULL_درخت)
    واپس جھوٹ;
  اگر (OMP_CLAUSE_رمز (c) == OMP_CLAUSE_DEPEND
      || OMP_CLAUSE_رمز (c) == OMP_CLAUSE_AFFINITY)
    {
      درخت t = *tp;
      درخت tem = NULL_درخت;
      /* Need to evaluate side effects in the length expressions
	 if any.  */
      جب (درخت_رمز (t) == درخت_LIST)
	{
	  اگر (درخت_قدر (t) && درخت_SIDE_EFFECTS (درخت_قدر (t)))
	    {
	      اگر (tem == NULL_درخت)
		tem = درخت_قدر (t);
	      ورنہ
		tem = build2 (COMPOUND_اظہاریہ, درخت_TYPE (tem),
			      درخت_قدر (t), tem);
	    }
	  t = درخت_CHAIN (t);
	}
      اگر (tem)
	پہلا = build2 (COMPOUND_اظہاریہ, درخت_TYPE (پہلا), tem, پہلا);
      پہلا = c_fully_fold (پہلا, جھوٹ, تہی, سچ);
      *tp = پہلا;
    }
  ورنہ
    {
      غیرعلامتی صحیح عدد = types.لمبائی (), i;
      درخت t, side_effects = NULL_درخت, سائز = NULL_درخت;
      درخت condition = NULL_درخت;

      اگر (int_سائز_اندر_بائٹیں (درخت_TYPE (پہلا)) <= 0)
	maybe_zero_len = سچ;

      برائے (i = عدد, t = OMP_CLAUSE_DECL (c); i > 0;
	   t = درخت_عملیہ (t, 0))
	{
	  درخت کم_bound = درخت_عملیہ (t, 1);
	  درخت لمبائی = درخت_عملیہ (t, 2);

	  i--;
	  اگر (کم_bound
	      && درخت_رمز (کم_bound) == INTEGER_CST
	      && TYPE_PRECISION (درخت_TYPE (کم_bound))
		 > TYPE_PRECISION (sizetype))
	    کم_bound = fold_convert (sizetype, کم_bound);
	  اگر (لمبائی
	      && درخت_رمز (لمبائی) == INTEGER_CST
	      && TYPE_PRECISION (درخت_TYPE (لمبائی))
		 > TYPE_PRECISION (sizetype))
	    لمبائی = fold_convert (sizetype, لمبائی);
	  اگر (کم_bound == NULL_درخت)
	    کم_bound = integer_zero_گرہ;
	  اگر (!maybe_zero_len && i > پہلا_non_one)
	    {
	      اگر (integer_nonzerop (کم_bound))
		جاؤ do_warn_noncontiguous;
	      اگر (لمبائی != NULL_درخت
		  && درخت_رمز (لمبائی) == INTEGER_CST
		  && TYPE_DOMAIN (types[i])
		  && TYPE_MAX_قدر (TYPE_DOMAIN (types[i]))
		  && درخت_رمز (TYPE_MAX_قدر (TYPE_DOMAIN (types[i])))
		     == INTEGER_CST)
		{
		  درخت سائز;
		  سائز = سائز_binop (PLUS_اظہاریہ,
				     TYPE_MAX_قدر (TYPE_DOMAIN (types[i])),
				     سائز_one_گرہ);
		  اگر (!درخت_int_cst_equal (لمبائی, سائز))
		    {
		     do_warn_noncontiguous:
		      error_at (OMP_CLAUSE_LOCATION (c),
				"array section is not contiguous in %qs "
				"clause",
				omp_clause_رمز_name[OMP_CLAUSE_رمز (c)]);
		      واپس سچ;
		    }
		}
	      اگر (لمبائی != NULL_درخت
		  && درخت_SIDE_EFFECTS (لمبائی))
		{
		  اگر (side_effects == NULL_درخت)
		    side_effects = لمبائی;
		  ورنہ
		    side_effects = build2 (COMPOUND_اظہاریہ,
					   درخت_TYPE (side_effects),
					   لمبائی, side_effects);
		}
	    }
	  ورنہ
	    {
	      درخت l;

	      اگر (i > پہلا_non_one
		  && ((لمبائی && integer_nonzerop (لمبائی))
		      || OMP_CLAUSE_رمز (c) == OMP_CLAUSE_REDUCTION
		      || OMP_CLAUSE_رمز (c) == OMP_CLAUSE_اندر_REDUCTION
		      || OMP_CLAUSE_رمز (c) == OMP_CLAUSE_TASK_REDUCTION))
		جاری;
	      اگر (لمبائی)
		l = fold_convert (sizetype, لمبائی);
	      ورنہ
		{
		  l = سائز_binop (PLUS_اظہاریہ,
				  TYPE_MAX_قدر (TYPE_DOMAIN (types[i])),
				  سائز_one_گرہ);
		  l = سائز_binop (MINUS_اظہاریہ, l,
				  fold_convert (sizetype, کم_bound));
		}
	      اگر (i > پہلا_non_one)
		{
		  l = fold_build2 (NE_اظہاریہ, boolean_type_گرہ, l,
				   سائز_zero_گرہ);
		  اگر (condition == NULL_درخت)
		    condition = l;
		  ورنہ
		    condition = fold_build2 (ثنائی_ہندسہ_AND_اظہاریہ, boolean_type_گرہ,
					     l, condition);
		}
	      ورنہ اگر (سائز == NULL_درخت)
		{
		  سائز = سائز_اندر_بائٹیں (درخت_TYPE (types[i]));
		  درخت eltype = درخت_TYPE (types[عدد - 1]);
		  جب (درخت_رمز (eltype) == ARRAY_TYPE)
		    eltype = درخت_TYPE (eltype);
		  اگر (OMP_CLAUSE_رمز (c) == OMP_CLAUSE_REDUCTION
		      || OMP_CLAUSE_رمز (c) == OMP_CLAUSE_اندر_REDUCTION
		      || OMP_CLAUSE_رمز (c) == OMP_CLAUSE_TASK_REDUCTION)
		    {
		      اگر (integer_zerop (سائز)
			  || integer_zerop (سائز_اندر_بائٹیں (eltype)))
			{
			  error_at (OMP_CLAUSE_LOCATION (c),
				    "zero length array section in %qs clause",
				    omp_clause_رمز_name[OMP_CLAUSE_رمز (c)]);
			  واپس error_mark_گرہ;
			}
		      سائز = سائز_binop (EXACT_DIV_اظہاریہ, سائز,
					 سائز_اندر_بائٹیں (eltype));
		    }
		  سائز = سائز_binop (MULT_اظہاریہ, سائز, l);
		  اگر (condition)
		    سائز = fold_build3 (COND_اظہاریہ, sizetype, condition,
					سائز, سائز_zero_گرہ);
		}
	      ورنہ
		سائز = سائز_binop (MULT_اظہاریہ, سائز, l);
	    }
	}
      اگر (side_effects)
	سائز = build2 (COMPOUND_اظہاریہ, sizetype, side_effects, سائز);
      اگر (OMP_CLAUSE_رمز (c) == OMP_CLAUSE_REDUCTION
	  || OMP_CLAUSE_رمز (c) == OMP_CLAUSE_اندر_REDUCTION
	  || OMP_CLAUSE_رمز (c) == OMP_CLAUSE_TASK_REDUCTION)
	{
	  سائز = سائز_binop (MINUS_اظہاریہ, سائز, سائز_one_گرہ);
	  سائز = c_fully_fold (سائز, جھوٹ, تہی);
	  سائز = save_اظہاریہ (سائز);
	  درخت اشاریہ_type = build_اشاریہ_type (سائز);
	  درخت eltype = درخت_TYPE (پہلا);
	  جب (درخت_رمز (eltype) == ARRAY_TYPE)
	    eltype = درخت_TYPE (eltype);
	  درخت type = c_build_array_type (eltype, اشاریہ_type);
	  درخت ptype = c_build_اشارہ_گر_type (eltype);
	  اگر (درخت_رمز (درخت_TYPE (t)) == ARRAY_TYPE)
	    t = build_fold_addr_اظہاریہ (t);
	  درخت t2 = build_fold_addr_اظہاریہ (پہلا);
	  t2 = fold_convert_loc (OMP_CLAUSE_LOCATION (c),
				 ptrdiff_type_گرہ, t2);
	  t2 = fold_build2_loc (OMP_CLAUSE_LOCATION (c), MINUS_اظہاریہ,
				ptrdiff_type_گرہ, t2,
				fold_convert_loc (OMP_CLAUSE_LOCATION (c),
						  ptrdiff_type_گرہ, t));
	  t2 = c_fully_fold (t2, جھوٹ, تہی);
	  اگر (درخت_سماتا_shwi_p (t2))
	    t = build2 (MEM_REF, type, t,
			build_int_cst (ptype, درخت_مقصد_shwi (t2)));
	  ورنہ
	    {
	      t2 = fold_convert_loc (OMP_CLAUSE_LOCATION (c), sizetype, t2);
	      t = build2_loc (OMP_CLAUSE_LOCATION (c), اشارہ_گر_PLUS_اظہاریہ,
			      درخت_TYPE (t), t, t2);
	      t = build2 (MEM_REF, type, t, build_int_cst (ptype, 0));
	    }
	  OMP_CLAUSE_DECL (c) = t;
	  واپس جھوٹ;
	}
      پہلا = c_fully_fold (پہلا, جھوٹ, تہی);
      OMP_CLAUSE_DECL (c) = پہلا;
      اگر (OMP_CLAUSE_رمز (c) == OMP_CLAUSE_HAS_DEVICE_ADDR)
	واپس جھوٹ;
      /* Don't set OMP_CLAUSE_SIZE for bare attach/detach clauses.  */
      اگر (OMP_CLAUSE_رمز (c) != OMP_CLAUSE_MAP
	  || (OMP_CLAUSE_MAP_قسم (c) != GOMP_MAP_ATTACH
	      && OMP_CLAUSE_MAP_قسم (c) != GOMP_MAP_DETACH
	      && OMP_CLAUSE_MAP_قسم (c) != GOMP_MAP_FORCE_DETACH))
	{
	  اگر (سائز)
	    سائز = c_fully_fold (سائز, جھوٹ, تہی);
	  OMP_CLAUSE_سائز (c) = سائز;
	}

      اگر (OMP_CLAUSE_رمز (c) != OMP_CLAUSE_MAP)
	واپس جھوٹ;

      auto_vec<omp_addr_token *, 10> addr_علامات;

      اگر (!omp_parse_اظہاریہ (addr_علامات, پہلا))
	واپس سچ;

      c_omp_پتہ_inspector ai (OMP_CLAUSE_LOCATION (c), t);

      درخت nc = ai.expand_map_clause (c, پہلا, addr_علامات, ort);
      اگر (nc != error_mark_گرہ)
	{
	  استعمال نامخلا omp_addr_tokenizer;

	  اگر (ai.maybe_zero_لمبائی_array_section (c))
	    OMP_CLAUSE_MAP_MAYBE_ZERO_لمبائی_ARRAY_SECTION (c) = 1;

	  /* !!! If we're accessing a base decl via chained access
	     methods (e.g. multiple indirections), duplicate clause
	     detection won't work properly.  Skip it in that case.  */
	  اگر ((addr_علامات[0]->type == STRUCTURE_بنیاد
	       || addr_علامات[0]->type == ARRAY_بنیاد)
	      && addr_علامات[0]->u.structure_بنیاد_قسم == بنیاد_DECL
	      && addr_علامات[1]->type == ACCESS_طریقہ
	      && omp_access_chain_p (addr_علامات, 1))
	    c = nc;

	  واپس جھوٹ;
	}
    }
  واپس جھوٹ;
}

/* Helper function of finish_omp_clauses.  Clone STMT as if we were making
   an inline call.  But, remap
   the OMP_DECL1 VAR_DECL (omp_out resp. omp_orig) to PLACEHOLDER
   and OMP_DECL2 VAR_DECL (omp_in resp. omp_priv) to DECL.  */

ساکن درخت
c_clone_omp_udr (درخت stmt, درخت omp_decl1, درخت omp_decl2,
		 درخت decl, درخت placeholder)
{
  copy_body_ڈیٹا id;
  hash_map<درخت, درخت> decl_map;

  decl_map.put (omp_decl1, placeholder);
  decl_map.put (omp_decl2, decl);
  memset (&id, 0, حجم (id));
  id.src_fn = DECL_CONTEXT (omp_decl1);
  id.dst_fn = current_function_decl;
  id.src_cfun = DECL_STRUCT_FUNCTION (id.src_fn);
  id.decl_map = &decl_map;

  id.copy_decl = copy_decl_no_change;
  id.transform_call_گراف_کنارے = CB_CGE_DUPLICATE;
  id.transform_new_cfg = سچ;
  id.transform_return_مقصد_modify = جھوٹ;
  id.eh_lp_nr = 0;
  walk_درخت (&stmt, copy_درخت_body_r, &id, تہی);
  واپس stmt;
}

/* Helper function of c_finish_omp_clauses, called via walk_tree.
   Find OMP_CLAUSE_PLACEHOLDER (passed in DATA) in *TP.  */

ساکن درخت
c_ڈھونڈو_omp_placeholder_r (درخت *tp, صحیح *, خالی *ڈیٹا)
{
  اگر (*tp == (درخت) ڈیٹا)
    واپس *tp;
  واپس NULL_درخت;
}

/* Similarly, but also walk aggregate fields.  */

ساخت c_ڈھونڈو_omp_var_s { درخت var; hash_سیٹ<درخت> *pset; };

ساکن درخت
c_ڈھونڈو_omp_var_r (درخت *tp, صحیح *, خالی *ڈیٹا)
{
  اگر (*tp == ((ساخت c_ڈھونڈو_omp_var_s *) ڈیٹا)->var)
    واپس *tp;
  اگر (ریکارڈ_OR_UNION_TYPE_P (*tp))
    {
      درخت میدان_2;
      hash_سیٹ<درخت> *pset = ((ساخت c_ڈھونڈو_omp_var_s *) ڈیٹا)->pset;

      برائے (میدان_2 = TYPE_FIELDS (*tp); میدان_2;
	   میدان_2 = DECL_CHAIN (میدان_2))
	اگر (درخت_رمز (میدان_2) == میدان_DECL)
	  {
	    درخت ret = walk_درخت (&DECL_میدان_انحراف (میدان_2),
				  c_ڈھونڈو_omp_var_r, ڈیٹا, pset);
	    اگر (ret)
	      واپس ret;
	    ret = walk_درخت (&DECL_سائز (میدان_2), c_ڈھونڈو_omp_var_r, ڈیٹا, pset);
	    اگر (ret)
	      واپس ret;
	    ret = walk_درخت (&DECL_سائز_UNIT (میدان_2), c_ڈھونڈو_omp_var_r, ڈیٹا,
			     pset);
	    اگر (ret)
	      واپس ret;
	    ret = walk_درخت (&درخت_TYPE (میدان_2), c_ڈھونڈو_omp_var_r, ڈیٹا, pset);
	    اگر (ret)
	      واپس ret;
	  }
    }
  ورنہ اگر (INTEGRAL_TYPE_P (*tp))
    واپس walk_درخت (&TYPE_MAX_قدر (*tp), c_ڈھونڈو_omp_var_r, ڈیٹا,
		      ((ساخت c_ڈھونڈو_omp_var_s *) ڈیٹا)->pset);
  واپس NULL_درخت;
}

/* Finish OpenMP iterators ITER.  Return true if they are erroneous
   and clauses containing them should be removed.  */

ساکن منطقی
c_omp_اختتام_iterators (درخت iter)
{
  منطقی ret = جھوٹ;
  برائے (درخت it = iter; it; it = درخت_CHAIN (it))
    {
      درخت var = OMP_ITERATOR_VAR (it);
      درخت begin = OMP_ITERATOR_BEGIN (it);
      درخت انتہا = OMP_ITERATOR_انتہا (it);
      درخت قدم = OMP_ITERATOR_قدم (it);
      درخت orig_قدم;
      درخت type = درخت_TYPE (var);
      location_t loc = DECL_ماخذ_LOCATION (var);
      اگر (type == error_mark_گرہ)
	{
	  ret = سچ;
	  جاری;
	}
      اگر (!INTEGRAL_TYPE_P (type) && !اشارہ_گر_TYPE_P (type))
	{
	  error_at (loc, "iterator %qD has neither integral nor pointer type",
		    var);
	  ret = سچ;
	  جاری;
	}
      ورنہ اگر (TYPE_ATOMIC (type))
	{
	  error_at (loc, "iterator %qD has %<_Atomic%> qualified type", var);
	  ret = سچ;
	  جاری;
	}
      ورنہ اگر (TYPE_READONLY (type))
	{
	  error_at (loc, "iterator %qD has const qualified type", var);
	  ret = سچ;
	  جاری;
	}
      ورنہ اگر (قدم == error_mark_گرہ
	       || درخت_TYPE (قدم) == error_mark_گرہ)
	{
	  ret = سچ;
	  جاری;
	}
      ورنہ اگر (!INTEGRAL_TYPE_P (درخت_TYPE (قدم)))
	{
	  error_at (اظہاریہ_LOC_OR_LOC (قدم, loc),
		    "iterator step with non-integral type");
	  ret = سچ;
	  جاری;
	}
      begin = c_fully_fold (build_c_cast (loc, type, begin), جھوٹ, تہی);
      انتہا = c_fully_fold (build_c_cast (loc, type, انتہا), جھوٹ, تہی);
      orig_قدم = save_اظہاریہ (c_fully_fold (قدم, جھوٹ, تہی));
      درخت stype = اشارہ_گر_TYPE_P (type) ? sizetype : type;
      قدم = c_fully_fold (build_c_cast (loc, stype, orig_قدم), جھوٹ, تہی);
      اگر (اشارہ_گر_TYPE_P (type))
	{
	  begin = save_اظہاریہ (begin);
	  قدم = اشارہ_گر_int_مجموع (loc, PLUS_اظہاریہ, begin, قدم);
	  قدم = fold_build2_loc (loc, MINUS_اظہاریہ, sizetype,
				  fold_convert (sizetype, قدم),
				  fold_convert (sizetype, begin));
	  قدم = fold_convert (ssizetype, قدم);
	}
      اگر (integer_zerop (قدم))
	{
	  error_at (loc, "iterator %qD has zero step", var);
	  ret = سچ;
	  جاری;
	}

      اگر (begin == error_mark_گرہ
	  || انتہا == error_mark_گرہ
	  || قدم == error_mark_گرہ
	  || orig_قدم == error_mark_گرہ)
	{
	  ret = سچ;
	  جاری;
	}
      hash_سیٹ<درخت> pset;
      درخت it2;
      برائے (it2 = درخت_CHAIN (it); it2; it2 = درخت_CHAIN (it2))
	{
	  درخت var2 = OMP_ITERATOR_VAR (it2);
	  درخت begin2 = OMP_ITERATOR_BEGIN (it2);
	  درخت end2 = OMP_ITERATOR_انتہا (it2);
	  درخت step2 = OMP_ITERATOR_قدم (it2);
	  درخت type2 = درخت_TYPE (var2);
	  location_t loc2 = DECL_ماخذ_LOCATION (var2);
	  ساخت c_ڈھونڈو_omp_var_s ڈیٹا = { var, &pset };
	  اگر (walk_درخت (&type2, c_ڈھونڈو_omp_var_r, &ڈیٹا, &pset))
	    {
	      error_at (loc2,
			"type of iterator %qD refers to outer iterator %qD",
			var2, var);
	      توڑو;
	    }
	  ورنہ اگر (walk_درخت (&begin2, c_ڈھونڈو_omp_var_r, &ڈیٹا, &pset))
	    {
	      error_at (اظہاریہ_LOC_OR_LOC (begin2, loc2),
			"begin expression refers to outer iterator %qD", var);
	      توڑو;
	    }
	  ورنہ اگر (walk_درخت (&end2, c_ڈھونڈو_omp_var_r, &ڈیٹا, &pset))
	    {
	      error_at (اظہاریہ_LOC_OR_LOC (end2, loc2),
			"end expression refers to outer iterator %qD", var);
	      توڑو;
	    }
	  ورنہ اگر (walk_درخت (&step2, c_ڈھونڈو_omp_var_r, &ڈیٹا, &pset))
	    {
	      error_at (اظہاریہ_LOC_OR_LOC (step2, loc2),
			"step expression refers to outer iterator %qD", var);
	      توڑو;
	    }
	}
      اگر (it2)
	{
	  ret = سچ;
	  جاری;
	}
      OMP_ITERATOR_BEGIN (it) = begin;
      OMP_ITERATOR_انتہا (it) = انتہا;
      OMP_ITERATOR_قدم (it) = قدم;
      OMP_ITERATOR_ORIG_قدم (it) = orig_قدم;
    }
  واپس ret;
}

/* Ensure that pointers are used in OpenACC attach and detach clauses.
   Return true if an error has been detected.  */

ساکن منطقی
c_oacc_check_attachments (درخت c)
{
  اگر (OMP_CLAUSE_رمز (c) != OMP_CLAUSE_MAP)
    واپس جھوٹ;

  /* OpenACC attach / detach clauses must be pointers.  */
  اگر (OMP_CLAUSE_MAP_قسم (c) == GOMP_MAP_ATTACH
      || OMP_CLAUSE_MAP_قسم (c) == GOMP_MAP_DETACH)
    {
      درخت t = OMP_CLAUSE_DECL (c);

      جب (درخت_رمز (t) == OMP_ARRAY_SECTION)
	t = درخت_عملیہ (t, 0);

      اگر (درخت_رمز (درخت_TYPE (t)) != اشارہ_گر_TYPE)
	{
	  error_at (OMP_CLAUSE_LOCATION (c), "expected pointer in %qs clause",
		    user_omp_clause_رمز_name (c, سچ));
	  واپس سچ;
	}
    }

  واپس جھوٹ;
}

/* For all elements of CLAUSES, validate them against their constraints.
   Remove any elements from the list that are invalid.  */

درخت
c_اختتام_omp_clauses (درخت clauses, شمار c_omp_region_type ort)
{
  bitmap_سر generic_سر, firstprivate_سر, lastprivate_سر;
  bitmap_سر aligned_سر, map_سر, map_میدان_سر, map_firstprivate_سر;
  bitmap_سر oacc_reduction_سر, is_on_device_سر;
  درخت c, t, type, *pc;
  درخت simdlen = NULL_درخت, safelen = NULL_درخت;
  منطقی branch_نظر_آیا = جھوٹ;
  منطقی copyprivate_نظر_آیا = جھوٹ;
  منطقی mergeable_نظر_آیا = جھوٹ;
  درخت *detach_نظر_آیا = تہی;
  منطقی خطی_variable_قدم_check = جھوٹ;
  درخت *nowait_clause = تہی;
  درخت *grainsize_نظر_آیا = تہی;
  منطقی عدد_tasks_نظر_آیا = جھوٹ;
  درخت ordered_clause = NULL_درخت;
  درخت جدول_وقت_clause = NULL_درخت;
  منطقی oacc_async = جھوٹ;
  درخت آخری_iterators = NULL_درخت;
  منطقی آخری_iterators_remove = جھوٹ;
  درخت *nogroup_نظر_آیا = تہی;
  درخت *ترتیب_clause = تہی;
  /* 1 if normal/task reduction has been seen, -1 if inscan reduction
     has been seen, -2 if mixed inscan/normal reduction diagnosed.  */
  صحیح reduction_نظر_آیا = 0;
  منطقی allocate_نظر_آیا = جھوٹ;
  منطقی implicit_moved = جھوٹ;
  منطقی ہدف_اندر_reduction_نظر_آیا = جھوٹ;
  درخت *بھرا_نظر_آیا = تہی;
  منطقی partial_نظر_آیا = جھوٹ;
  منطقی openacc = (ort & C_ORT_ACC) != 0;
  منطقی init_نظر_آیا = جھوٹ;
  منطقی init_use_destroy_نظر_آیا = جھوٹ;
  درخت init_no_targetsync_clause = NULL_درخت;
  درخت depend_clause = NULL_درخت;

  اگر (!openacc)
    clauses = omp_remove_duplicate_maps (clauses, سچ);

  bitmap_obstack_initialize (تہی);
  bitmap_initialize (&generic_سر, &bitmap_default_obstack);
  bitmap_initialize (&firstprivate_سر, &bitmap_default_obstack);
  bitmap_initialize (&lastprivate_سر, &bitmap_default_obstack);
  bitmap_initialize (&aligned_سر, &bitmap_default_obstack);
  /* If ort == C_ORT_OMP_DECLARE_SIMD used as uniform_head instead.  */
  bitmap_initialize (&map_سر, &bitmap_default_obstack);
  bitmap_initialize (&map_میدان_سر, &bitmap_default_obstack);
  bitmap_initialize (&map_firstprivate_سر, &bitmap_default_obstack);
  /* If ort == C_ORT_OMP used as nontemporal_head or use_device_xxx_head
     instead and for ort == C_ORT_OMP_TARGET used as in_reduction_head.  */
  bitmap_initialize (&oacc_reduction_سر, &bitmap_default_obstack);
  bitmap_initialize (&is_on_device_سر, &bitmap_default_obstack);

  اگر (openacc)
    برائے (c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
      اگر (OMP_CLAUSE_رمز (c) == OMP_CLAUSE_ASYNC)
	{
	  oacc_async = سچ;
	  توڑو;
	}

  درخت *grp_آغاز_p = تہی, grp_sentinel = NULL_درخت;

  برائے (pc = &clauses, c = clauses; c ; c = *pc)
    {
      منطقی remove = جھوٹ;
      منطقی need_complete = جھوٹ;
      منطقی need_implicitly_determined = جھوٹ;

      /* We've reached the end of a list of expanded nodes.  Reset the group
	 start pointer.  */
      اگر (c == grp_sentinel)
	{
	  اگر (grp_آغاز_p
	      && OMP_CLAUSE_HAS_ITERATORS (*grp_آغاز_p))
	    برائے (درخت gc = *grp_آغاز_p; gc != grp_sentinel;
		 gc = OMP_CLAUSE_CHAIN (gc))
	      OMP_CLAUSE_ITERATORS (gc) = OMP_CLAUSE_ITERATORS (*grp_آغاز_p);
	  grp_آغاز_p = تہی;
	}

      انتخاب (OMP_CLAUSE_رمز (c))
	{
	حالت OMP_CLAUSE_SHARED:
	  need_implicitly_determined = سچ;
	  جاؤ check_dup_generic;

	حالت OMP_CLAUSE_نجی:
	  need_complete = سچ;
	  need_implicitly_determined = سچ;
	  جاؤ check_dup_generic;

	حالت OMP_CLAUSE_REDUCTION:
	  اگر (reduction_نظر_آیا == 0)
	    reduction_نظر_آیا = OMP_CLAUSE_REDUCTION_INSCAN (c) ? -1 : 1;
	  ورنہ اگر (reduction_نظر_آیا != -2
		   && reduction_نظر_آیا != (OMP_CLAUSE_REDUCTION_INSCAN (c)
					 ? -1 : 1))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<inscan%> and non-%<inscan%> %<reduction%> clauses "
			"on the same construct");
	      reduction_نظر_آیا = -2;
	    }
	  /* FALLTHRU */
	حالت OMP_CLAUSE_اندر_REDUCTION:
	حالت OMP_CLAUSE_TASK_REDUCTION:
	  need_implicitly_determined = سچ;
	  t = OMP_CLAUSE_DECL (c);
	  اگر (درخت_رمز (t) == OMP_ARRAY_SECTION)
	    {
	      اگر (handle_omp_array_sections (c, ort))
		{
		  remove = سچ;
		  توڑو;
		}

	      t = OMP_CLAUSE_DECL (c);
	      اگر (OMP_CLAUSE_رمز (c) == OMP_CLAUSE_REDUCTION
		  && OMP_CLAUSE_REDUCTION_INSCAN (c))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<inscan%> %<reduction%> clause with array "
			    "section");
		  remove = سچ;
		  توڑو;
		}
	    }
	  t = require_complete_type (OMP_CLAUSE_LOCATION (c), t);
	  اگر (t == error_mark_گرہ)
	    {
	      remove = سچ;
	      توڑو;
	    }
	  اگر (oacc_async)
	    c_mark_addressable (t);
	  type = درخت_TYPE (t);
	  اگر (درخت_رمز (t) == MEM_REF)
	    type = درخت_TYPE (type);
	  اگر (درخت_رمز (type) == ARRAY_TYPE)
	    {
	      درخت oatype = type;
	      gcc_assert (درخت_رمز (t) != MEM_REF);
	      جب (درخت_رمز (type) == ARRAY_TYPE)
		type = درخت_TYPE (type);
	      اگر (integer_zerop (TYPE_سائز_UNIT (type)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD in %<reduction%> clause is a zero size array",
			    t);
		  remove = سچ;
		  توڑو;
		}
	      درخت سائز = سائز_binop (EXACT_DIV_اظہاریہ, TYPE_سائز_UNIT (oatype),
				      TYPE_سائز_UNIT (type));
	      اگر (integer_zerop (سائز))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD in %<reduction%> clause is a zero size array",
			    t);
		  remove = سچ;
		  توڑو;
		}
	      سائز = سائز_binop (MINUS_اظہاریہ, سائز, سائز_one_گرہ);
	      سائز = save_اظہاریہ (سائز);
	      درخت اشاریہ_type = build_اشاریہ_type (سائز);
	      درخت atype = c_build_array_type (TYPE_MAIN_VARIANT (type),
					       اشاریہ_type);
	      atype = c_build_qualified_type (atype, TYPE_QUALS (type));
	      درخت ptype = c_build_اشارہ_گر_type (type);
	      اگر (درخت_رمز (درخت_TYPE (t)) == ARRAY_TYPE)
		t = build_fold_addr_اظہاریہ (t);
	      t = build2 (MEM_REF, atype, t, build_int_cst (ptype, 0));
	      OMP_CLAUSE_DECL (c) = t;
	    }
	  اگر (TYPE_ATOMIC (type))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<_Atomic%> %qE in %<reduction%> clause", t);
	      remove = سچ;
	      توڑو;
	    }
	  اگر (OMP_CLAUSE_رمز (c) != OMP_CLAUSE_REDUCTION
	      || OMP_CLAUSE_REDUCTION_TASK (c))
	    {
	      /* Disallow zero sized or potentially zero sized task
		 reductions.  */
	      اگر (integer_zerop (TYPE_سائز_UNIT (type)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "zero sized type %qT in %qs clause", type,
			    omp_clause_رمز_name[OMP_CLAUSE_رمز (c)]);
		  remove = سچ;
		  توڑو;
		}
	      ورنہ اگر (درخت_رمز (TYPE_سائز_UNIT (type)) != INTEGER_CST)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "variable sized type %qT in %qs clause", type,
			    omp_clause_رمز_name[OMP_CLAUSE_رمز (c)]);
		  remove = سچ;
		  توڑو;
		}
	    }
	  اگر (OMP_CLAUSE_REDUCTION_PLACEHOLDER (c) == NULL_درخت
	      && (FLOAT_TYPE_P (type)
		  || درخت_رمز (type) == COMPLEX_TYPE))
	    {
	      شمار درخت_رمز_2 r_رمز = OMP_CLAUSE_REDUCTION_رمز (c);
	      ثابت حرف *r_name = تہی;

	      انتخاب (r_رمز)
		{
		حالت PLUS_اظہاریہ:
		حالت MULT_اظہاریہ:
		حالت MINUS_اظہاریہ:
		حالت TRUTH_ANDIF_اظہاریہ:
		حالت TRUTH_ORIF_اظہاریہ:
		  توڑو;
		حالت MIN_اظہاریہ:
		  اگر (درخت_رمز (type) == COMPLEX_TYPE)
		    r_name = "min";
		  توڑو;
		حالت MAX_اظہاریہ:
		  اگر (درخت_رمز (type) == COMPLEX_TYPE)
		    r_name = "max";
		  توڑو;
		حالت ثنائی_ہندسہ_AND_اظہاریہ:
		  r_name = "&";
		  توڑو;
		حالت ثنائی_ہندسہ_XOR_اظہاریہ:
		  r_name = "^";
		  توڑو;
		حالت ثنائی_ہندسہ_IOR_اظہاریہ:
		  r_name = "|";
		  توڑو;
		طےشدہ:
		  gcc_unreachable ();
		}
	      اگر (r_name)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qE has invalid type for %<reduction(%s)%>",
			    t, r_name);
		  remove = سچ;
		  توڑو;
		}
	    }
	  ورنہ اگر (OMP_CLAUSE_REDUCTION_PLACEHOLDER (c) == error_mark_گرہ)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"user defined reduction not found for %qE", t);
	      remove = سچ;
	      توڑو;
	    }
	  ورنہ اگر (OMP_CLAUSE_REDUCTION_PLACEHOLDER (c))
	    {
	      درخت list = OMP_CLAUSE_REDUCTION_PLACEHOLDER (c);
	      type = TYPE_MAIN_VARIANT (type);
	      درخت placeholder = build_decl (OMP_CLAUSE_LOCATION (c),
					     VAR_DECL, NULL_درخت, type);
	      درخت decl_placeholder = NULL_درخت;
	      OMP_CLAUSE_REDUCTION_PLACEHOLDER (c) = placeholder;
	      DECL_ARTIFICIAL (placeholder) = 1;
	      DECL_IGNORED_P (placeholder) = 1;
	      اگر (درخت_رمز (t) == MEM_REF)
		{
		  decl_placeholder = build_decl (OMP_CLAUSE_LOCATION (c),
						 VAR_DECL, NULL_درخت, type);
		  OMP_CLAUSE_REDUCTION_DECL_PLACEHOLDER (c) = decl_placeholder;
		  DECL_ARTIFICIAL (decl_placeholder) = 1;
		  DECL_IGNORED_P (decl_placeholder) = 1;
		}
	      اگر (درخت_ADDRESSABLE (درخت_VEC_ELT (list, 0)))
		c_mark_addressable (placeholder);
	      اگر (درخت_ADDRESSABLE (درخت_VEC_ELT (list, 1)))
		c_mark_addressable (decl_placeholder ? decl_placeholder
				    : OMP_CLAUSE_DECL (c));
	      OMP_CLAUSE_REDUCTION_ملاؤ (c)
		= c_clone_omp_udr (درخت_VEC_ELT (list, 2),
				   درخت_VEC_ELT (list, 0),
				   درخت_VEC_ELT (list, 1),
				   decl_placeholder ? decl_placeholder
				   : OMP_CLAUSE_DECL (c), placeholder);
	      OMP_CLAUSE_REDUCTION_ملاؤ (c)
		= build3_loc (OMP_CLAUSE_LOCATION (c), BIND_اظہاریہ,
			      void_type_گرہ, NULL_درخت,
			      OMP_CLAUSE_REDUCTION_ملاؤ (c), NULL_درخت);
	      درخت_SIDE_EFFECTS (OMP_CLAUSE_REDUCTION_ملاؤ (c)) = 1;
	      اگر (درخت_VEC_لمبائی (list) == 6)
		{
		  اگر (درخت_ADDRESSABLE (درخت_VEC_ELT (list, 3)))
		    c_mark_addressable (decl_placeholder ? decl_placeholder
					: OMP_CLAUSE_DECL (c));
		  اگر (درخت_ADDRESSABLE (درخت_VEC_ELT (list, 4)))
		    c_mark_addressable (placeholder);
		  درخت init = درخت_VEC_ELT (list, 5);
		  اگر (init == error_mark_گرہ)
		    init = DECL_INITIAL (درخت_VEC_ELT (list, 3));
		  OMP_CLAUSE_REDUCTION_INIT (c)
		    = c_clone_omp_udr (init, درخت_VEC_ELT (list, 4),
				       درخت_VEC_ELT (list, 3),
				       decl_placeholder ? decl_placeholder
				       : OMP_CLAUSE_DECL (c), placeholder);
		  اگر (درخت_VEC_ELT (list, 5) == error_mark_گرہ)
		    {
		      درخت v = decl_placeholder ? decl_placeholder : t;
		      OMP_CLAUSE_REDUCTION_INIT (c)
			= build2 (INIT_اظہاریہ, درخت_TYPE (v), v,
				  OMP_CLAUSE_REDUCTION_INIT (c));
		    }
		  اگر (walk_درخت (&OMP_CLAUSE_REDUCTION_INIT (c),
				 c_ڈھونڈو_omp_placeholder_r,
				 placeholder, تہی))
		    OMP_CLAUSE_REDUCTION_OMP_ORIG_REF (c) = 1;
		}
	      ورنہ
		{
		  درخت init;
		  درخت v = decl_placeholder ? decl_placeholder : t;
		  اگر (AGGREGATE_TYPE_P (درخت_TYPE (v)))
		    init = build_constructor (درخت_TYPE (v), تہی);
		  ورنہ
		    init = fold_convert (درخت_TYPE (v), integer_zero_گرہ);
		  OMP_CLAUSE_REDUCTION_INIT (c)
		    = build2 (INIT_اظہاریہ, درخت_TYPE (v), v, init);
		}
	      OMP_CLAUSE_REDUCTION_INIT (c)
		= build3_loc (OMP_CLAUSE_LOCATION (c), BIND_اظہاریہ,
			      void_type_گرہ, NULL_درخت,
			       OMP_CLAUSE_REDUCTION_INIT (c), NULL_درخت);
	      درخت_SIDE_EFFECTS (OMP_CLAUSE_REDUCTION_INIT (c)) = 1;
	    }
	  اگر (درخت_رمز (t) == MEM_REF)
	    {
	      اگر (TYPE_سائز_UNIT (درخت_TYPE (درخت_TYPE (t))) == NULL_درخت
		  || درخت_رمز (TYPE_سائز_UNIT (درخت_TYPE (درخت_TYPE (t))))
		     != INTEGER_CST)
		{
		  sorry ("variable length element type in array "
			 "%<reduction%> clause");
		  remove = سچ;
		  توڑو;
		}
	      t = درخت_عملیہ (t, 0);
	      اگر (درخت_رمز (t) == اشارہ_گر_PLUS_اظہاریہ)
		t = درخت_عملیہ (t, 0);
	      اگر (درخت_رمز (t) == ADDR_اظہاریہ)
		t = درخت_عملیہ (t, 0);
	    }
	  جاؤ check_dup_generic_t;

	حالت OMP_CLAUSE_COPYPRIVATE:
	  copyprivate_نظر_آیا = سچ;
	  اگر (nowait_clause)
	    {
	      error_at (OMP_CLAUSE_LOCATION (*nowait_clause),
			"%<nowait%> clause must not be used together "
			"with %<copyprivate%> clause");
	      *nowait_clause = OMP_CLAUSE_CHAIN (*nowait_clause);
	      nowait_clause = تہی;
	    }
	  جاؤ check_dup_generic;

	حالت OMP_CLAUSE_COPYIN:
	  t = OMP_CLAUSE_DECL (c);
	  اگر (!VAR_P (t) || !DECL_THREAD_LOCAL_P (t))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE must be %<threadprivate%> for %<copyin%>", t);
	      remove = سچ;
	      توڑو;
	    }
	  جاؤ check_dup_generic;

	حالت OMP_CLAUSE_خطی:
	  اگر (ort != C_ORT_OMP_DECLARE_SIMD)
	    need_implicitly_determined = سچ;
	  t = OMP_CLAUSE_DECL (c);
	  اگر (ort != C_ORT_OMP_DECLARE_SIMD
	      && OMP_CLAUSE_خطی_قسم (c) != OMP_CLAUSE_خطی_DEFAULT
	      && OMP_CLAUSE_خطی_OLD_خطی_MODIFIER (c))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"modifier should not be specified in %<linear%> "
			"clause on %<simd%> or %<for%> constructs when not "
			"using OpenMP 5.2 modifiers");
	      OMP_CLAUSE_خطی_قسم (c) = OMP_CLAUSE_خطی_DEFAULT;
	    }
	  اگر (!INTEGRAL_TYPE_P (درخت_TYPE (t))
	      && درخت_رمز (درخت_TYPE (t)) != اشارہ_گر_TYPE)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"linear clause applied to non-integral non-pointer "
			"variable with type %qT", درخت_TYPE (t));
	      remove = سچ;
	      توڑو;
	    }
	  اگر (TYPE_ATOMIC (درخت_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<_Atomic%> %qD in %<linear%> clause", t);
	      remove = سچ;
	      توڑو;
	    }
	  اگر (ort == C_ORT_OMP_DECLARE_SIMD)
	    {
	      درخت s = OMP_CLAUSE_خطی_قدم (c);
	      اگر (درخت_رمز (s) == PARM_DECL)
		{
		  OMP_CLAUSE_خطی_VARIABLE_STRIDE (c) = 1;
		  /* map_head bitmap is used as uniform_head if
		     declare_simd.  */
		  اگر (!bitmap_ثنائی_ہندسہ_p (&map_سر, DECL_UID (s)))
		    خطی_variable_قدم_check = سچ;
		  جاؤ check_dup_generic;
		}
	      اگر (درخت_رمز (s) != INTEGER_CST)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<linear%> clause step %qE is neither constant "
			    "nor a parameter", s);
		  remove = سچ;
		  توڑو;
		}
	    }
	  اگر (درخت_رمز (درخت_TYPE (OMP_CLAUSE_DECL (c))) == اشارہ_گر_TYPE)
	    {
	      درخت s = OMP_CLAUSE_خطی_قدم (c);
	      s = اشارہ_گر_int_مجموع (OMP_CLAUSE_LOCATION (c), PLUS_اظہاریہ,
				   OMP_CLAUSE_DECL (c), s);
	      s = fold_build2_loc (OMP_CLAUSE_LOCATION (c), MINUS_اظہاریہ,
				   sizetype, fold_convert (sizetype, s),
				   fold_convert
				     (sizetype, OMP_CLAUSE_DECL (c)));
	      اگر (s == error_mark_گرہ)
		s = سائز_one_گرہ;
	      OMP_CLAUSE_خطی_قدم (c) = s;
	    }
	  ورنہ
	    OMP_CLAUSE_خطی_قدم (c)
	      = fold_convert (درخت_TYPE (t), OMP_CLAUSE_خطی_قدم (c));
	  جاؤ check_dup_generic;

	check_dup_generic:
	  t = OMP_CLAUSE_DECL (c);
	check_dup_generic_t:
	  اگر (!VAR_P (t) && درخت_رمز (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %qs", t,
			omp_clause_رمز_name[OMP_CLAUSE_رمز (c)]);
	      remove = سچ;
	    }
	  ورنہ اگر ((openacc && OMP_CLAUSE_رمز (c) == OMP_CLAUSE_REDUCTION)
		   || (ort == C_ORT_OMP
		       && (OMP_CLAUSE_رمز (c) == OMP_CLAUSE_USE_DEVICE_PTR
			   || (OMP_CLAUSE_رمز (c)
			       == OMP_CLAUSE_USE_DEVICE_ADDR)))
		   || (ort == C_ORT_OMP_ہدف
		       && OMP_CLAUSE_رمز (c) == OMP_CLAUSE_اندر_REDUCTION))
	    {
	      اگر (OMP_CLAUSE_رمز (c) == OMP_CLAUSE_اندر_REDUCTION
		  && (bitmap_ثنائی_ہندسہ_p (&generic_سر, DECL_UID (t))
		      || bitmap_ثنائی_ہندسہ_p (&firstprivate_سر, DECL_UID (t))))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in data-sharing "
			    "clauses", t);
		  remove = سچ;
		  توڑو;
		}
	      اگر (OMP_CLAUSE_رمز (c) == OMP_CLAUSE_اندر_REDUCTION)
		ہدف_اندر_reduction_نظر_آیا = سچ;
	      اگر (bitmap_ثنائی_ہندسہ_p (&oacc_reduction_سر, DECL_UID (t)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    openacc
			    ? "%qD appears more than once in reduction clauses"
			    : "%qD appears more than once in data clauses",
			    t);
		  remove = سچ;
		}
	      ورنہ
		bitmap_سیٹ_ثنائی_ہندسہ (&oacc_reduction_سر, DECL_UID (t));
	    }
	  ورنہ اگر (bitmap_ثنائی_ہندسہ_p (&generic_سر, DECL_UID (t))
		   || bitmap_ثنائی_ہندسہ_p (&firstprivate_سر, DECL_UID (t))
		   || bitmap_ثنائی_ہندسہ_p (&lastprivate_سر, DECL_UID (t))
		   || bitmap_ثنائی_ہندسہ_p (&map_firstprivate_سر, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in data clauses", t);
	      remove = سچ;
	    }
	  ورنہ اگر ((OMP_CLAUSE_رمز (c) == OMP_CLAUSE_نجی
		    || OMP_CLAUSE_رمز (c) == OMP_CLAUSE_HAS_DEVICE_ADDR
		    || OMP_CLAUSE_رمز (c) == OMP_CLAUSE_IS_DEVICE_PTR)
		   && bitmap_ثنائی_ہندسہ_p (&map_سر, DECL_UID (t)))
	    {
	      اگر (openacc)
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears more than once in data clauses", t);
	      ورنہ
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears both in data and map clauses", t);
	      remove = سچ;
	    }
	  ورنہ
	    bitmap_سیٹ_ثنائی_ہندسہ (&generic_سر, DECL_UID (t));
	  توڑو;

	حالت OMP_CLAUSE_FIRSTPRIVATE:
	  اگر (OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (c) && !implicit_moved)
	    {
	    move_implicit:
	      implicit_moved = سچ;
	      /* Move firstprivate and map clauses with
		 OMP_CLAUSE_{FIRSTPRIVATE,MAP}_IMPLICIT set to the end of
		 clauses chain.  */
	      درخت cl1 = NULL_درخت, cl2 = NULL_درخت;
	      درخت *pc1 = pc, *pc2 = &cl1, *pc3 = &cl2;
	      جب (*pc1)
		اگر (OMP_CLAUSE_رمز (*pc1) == OMP_CLAUSE_FIRSTPRIVATE
		    && OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (*pc1))
		  {
		    *pc3 = *pc1;
		    pc3 = &OMP_CLAUSE_CHAIN (*pc3);
		    *pc1 = OMP_CLAUSE_CHAIN (*pc1);
		  }
		ورنہ اگر (OMP_CLAUSE_رمز (*pc1) == OMP_CLAUSE_MAP
			 && OMP_CLAUSE_MAP_IMPLICIT (*pc1))
		  {
		    *pc2 = *pc1;
		    pc2 = &OMP_CLAUSE_CHAIN (*pc2);
		    *pc1 = OMP_CLAUSE_CHAIN (*pc1);
		  }
		ورنہ
		  pc1 = &OMP_CLAUSE_CHAIN (*pc1);
	      *pc3 = تہی;
	      *pc2 = cl2;
	      *pc1 = cl1;
	      جاری;
	    }
	  t = OMP_CLAUSE_DECL (c);
	  need_complete = سچ;
	  need_implicitly_determined = سچ;
	  اگر (!VAR_P (t) && درخت_رمز (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %<firstprivate%>", t);
	      remove = سچ;
	    }
	  ورنہ اگر (OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (c)
		   && !OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT_ہدف (c)
		   && bitmap_ثنائی_ہندسہ_p (&map_firstprivate_سر, DECL_UID (t)))
	    remove = سچ;
	  ورنہ اگر (bitmap_ثنائی_ہندسہ_p (&generic_سر, DECL_UID (t))
		   || bitmap_ثنائی_ہندسہ_p (&firstprivate_سر, DECL_UID (t))
		   || bitmap_ثنائی_ہندسہ_p (&map_firstprivate_سر, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in data clauses", t);
	      remove = سچ;
	    }
	  ورنہ اگر (bitmap_ثنائی_ہندسہ_p (&map_سر, DECL_UID (t))
		   || bitmap_ثنائی_ہندسہ_p (&map_میدان_سر, DECL_UID (t)))
	    {
	      اگر (openacc)
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears more than once in data clauses", t);
	      ورنہ اگر (OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (c)
		       && !OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT_ہدف (c))
		/* Silently drop the clause.  */;
	      ورنہ
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears both in data and map clauses", t);
	      remove = سچ;
	    }
	  ورنہ
	    bitmap_سیٹ_ثنائی_ہندسہ (&firstprivate_سر, DECL_UID (t));
	  توڑو;

	حالت OMP_CLAUSE_LASTPRIVATE:
	  t = OMP_CLAUSE_DECL (c);
	  need_complete = سچ;
	  need_implicitly_determined = سچ;
	  اگر (!VAR_P (t) && درخت_رمز (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %<lastprivate%>", t);
	      remove = سچ;
	    }
	  ورنہ اگر (bitmap_ثنائی_ہندسہ_p (&generic_سر, DECL_UID (t))
		   || bitmap_ثنائی_ہندسہ_p (&lastprivate_سر, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
		     "%qE appears more than once in data clauses", t);
	      remove = سچ;
	    }
	  ورنہ
	    bitmap_سیٹ_ثنائی_ہندسہ (&lastprivate_سر, DECL_UID (t));
	  توڑو;

	حالت OMP_CLAUSE_ALIGNED:
	  t = OMP_CLAUSE_DECL (c);
	  اگر (!VAR_P (t) && درخت_رمز (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in %<aligned%> clause", t);
	      remove = سچ;
	    }
	  ورنہ اگر (!اشارہ_گر_TYPE_P (درخت_TYPE (t))
		   && درخت_رمز (درخت_TYPE (t)) != ARRAY_TYPE)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE in %<aligned%> clause is neither a pointer nor "
			"an array", t);
	      remove = سچ;
	    }
	  ورنہ اگر (TYPE_ATOMIC (درخت_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<_Atomic%> %qD in %<aligned%> clause", t);
	      remove = سچ;
	      توڑو;
	    }
	  ورنہ اگر (bitmap_ثنائی_ہندسہ_p (&aligned_سر, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in %<aligned%> clauses",
			t);
	      remove = سچ;
	    }
	  ورنہ
	    bitmap_سیٹ_ثنائی_ہندسہ (&aligned_سر, DECL_UID (t));
	  توڑو;

	حالت OMP_CLAUSE_NONTEMPORAL:
	  t = OMP_CLAUSE_DECL (c);
	  اگر (!VAR_P (t) && درخت_رمز (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in %<nontemporal%> clause", t);
	      remove = سچ;
	    }
	  ورنہ اگر (bitmap_ثنائی_ہندسہ_p (&oacc_reduction_سر, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in %<nontemporal%> "
			"clauses", t);
	      remove = سچ;
	    }
	  ورنہ
	    bitmap_سیٹ_ثنائی_ہندسہ (&oacc_reduction_سر, DECL_UID (t));
	  توڑو;

	حالت OMP_CLAUSE_ALLOCATE:
	  t = OMP_CLAUSE_DECL (c);
	  اگر (!VAR_P (t) && درخت_رمز (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in %<allocate%> clause", t);
	      remove = سچ;
	    }
	  ورنہ اگر (bitmap_ثنائی_ہندسہ_p (&aligned_سر, DECL_UID (t)))
	    {
	      warning_at (OMP_CLAUSE_LOCATION (c), OPT_Wopenmp,
			  "%qE appears more than once in %<allocate%> clauses",
			  t);
	      remove = سچ;
	    }
	  ورنہ
	    {
	      bitmap_سیٹ_ثنائی_ہندسہ (&aligned_سر, DECL_UID (t));
	      اگر (!OMP_CLAUSE_ALLOCATE_COMBINED (c))
		allocate_نظر_آیا = سچ;
	    }
	  توڑو;

	حالت OMP_CLAUSE_DOACROSS:
	  t = OMP_CLAUSE_DECL (c);
	  اگر (t == NULL_درخت)
	    توڑو;
	  اگر (OMP_CLAUSE_DOACROSS_قسم (c) == OMP_CLAUSE_DOACROSS_SINK)
	    {
	      gcc_assert (درخت_رمز (t) == درخت_LIST);
	      برائے (; t; t = درخت_CHAIN (t))
		{
		  درخت decl = درخت_قدر (t);
		  اگر (درخت_رمز (درخت_TYPE (decl)) == اشارہ_گر_TYPE)
		    {
		      درخت انحراف = درخت_PURPOSE (t);
		      منطقی neg = wi::neg_p (wi::مقصد_wide (انحراف));
		      انحراف = fold_unary (ABS_اظہاریہ, درخت_TYPE (انحراف), انحراف);
		      درخت t2 = اشارہ_گر_int_مجموع (OMP_CLAUSE_LOCATION (c),
						 neg ? MINUS_اظہاریہ : PLUS_اظہاریہ,
						 decl, انحراف);
		      t2 = fold_build2_loc (OMP_CLAUSE_LOCATION (c), MINUS_اظہاریہ,
					    sizetype,
					    fold_convert (sizetype, t2),
					    fold_convert (sizetype, decl));
		      اگر (t2 == error_mark_گرہ)
			{
			  remove = سچ;
			  توڑو;
			}
		      درخت_PURPOSE (t) = t2;
		    }
		}
	      توڑو;
	    }
	  gcc_unreachable ();

	حالت OMP_CLAUSE_استعمال_کرتا_ALLOCATORS:
	  t = OMP_CLAUSE_استعمال_کرتا_ALLOCATORS_ALLOCATOR (c);
	  اگر (t == error_mark_گرہ)
	    {
	      remove = سچ;
	      توڑو;
	    }
	  اگر ((VAR_P (t) || درخت_رمز (t) == PARM_DECL)
	      && (bitmap_ثنائی_ہندسہ_p (&generic_سر, DECL_UID (t))
		  || bitmap_ثنائی_ہندسہ_p (&map_سر, DECL_UID (t))
		  || bitmap_ثنائی_ہندسہ_p (&firstprivate_سر, DECL_UID (t))
		  || bitmap_ثنائی_ہندسہ_p (&lastprivate_سر, DECL_UID (t))))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in data clauses", t);
	      remove = سچ;
	      توڑو;
	    }
	  ورنہ
	    bitmap_سیٹ_ثنائی_ہندسہ (&generic_سر, DECL_UID (t));
	  اگر (درخت_رمز (درخت_TYPE (t)) != ENUMERAL_TYPE
	      || strcmp (IDENTIFIER_اشارہ_گر (TYPE_IDENTIFIER (درخت_TYPE (t))),
			 "omp_allocator_handle_t") != 0)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"allocator %qE must be of %<omp_allocator_handle_t%> "
			"type", t);
	      remove = سچ;
	      توڑو;
	    }
	  درخت init;
	  اگر (!DECL_P (t)
	      || (درخت_رمز (t) == CONST_DECL
		  && ((init = DECL_INITIAL(t)) == خالی_اشاریہ
		      || درخت_رمز (init) != INTEGER_CST
		      || ((wi::مقصد_widest (init) < 0
			   || wi::مقصد_widest (init) > GOMP_OMP_PREDEF_ALLOC_MAX)
			  && (wi::مقصد_widest (init) < GOMP_OMPX_PREDEF_ALLOC_MIN
			      || (wi::مقصد_widest (init)
				  > GOMP_OMPX_PREDEF_ALLOC_MAX))))))
	    {
	      remove = سچ;
	      error_at (OMP_CLAUSE_LOCATION (c),
			"allocator %qE must be either a variable or a "
			"predefined allocator", t);
	      توڑو;
	    }
	  ورنہ اگر (درخت_رمز (t) == CONST_DECL)
	    {
	      /* omp_null_allocator is ignored and for predefined allocators,
		 no special handling is required; thus, mark them removed. */
	      remove = سچ;

	      اگر (OMP_CLAUSE_استعمال_کرتا_ALLOCATORS_MEMSPACE (c)
		  || OMP_CLAUSE_استعمال_کرتا_ALLOCATORS_TRAITS (c))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "modifiers cannot be used with predefined "
			    "allocator %qE", t);
		  توڑو;
		}
	    }
	  t = OMP_CLAUSE_استعمال_کرتا_ALLOCATORS_MEMSPACE (c);
	  اگر (t == error_mark_گرہ)
	    {
	      remove = سچ;
	      توڑو;
	    }
	  اگر (t != NULL_درخت
	      && ((درخت_رمز (t) != CONST_DECL && درخت_رمز (t) != INTEGER_CST)
		  || درخت_رمز (درخت_TYPE (t)) != ENUMERAL_TYPE
		  || strcmp (IDENTIFIER_اشارہ_گر (TYPE_IDENTIFIER (درخت_TYPE (t))),
			     "omp_memspace_handle_t") != 0))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c), "memspace modifier %qE must be"
			" constant enum of %<omp_memspace_handle_t%> type", t);
	      remove = سچ;
	      توڑو;
	    }
	  t = OMP_CLAUSE_استعمال_کرتا_ALLOCATORS_TRAITS (c);
	  اگر (t == error_mark_گرہ)
	    {
	      remove = سچ;
	      توڑو;
	    }
	  اگر (t != NULL_درخت
	      && t != error_mark_گرہ
	      && (DECL_EXTERNAL (t)
		  || درخت_رمز (t) == PARM_DECL))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c), "traits array %qE must be "
			"defined in same scope as the construct on which the "
			"clause appears", t);
	      remove = سچ;
	    }
	  اگر (t != NULL_درخت)
	    {
	      منطقی type_err = جھوٹ;

	      اگر (درخت_رمز (درخت_TYPE (t)) != ARRAY_TYPE
		  || DECL_سائز (t) == NULL_درخت
		  || !COMPLETE_TYPE_P (درخت_TYPE (t)))
		type_err = سچ;
	      ورنہ
		{
		  درخت elem_t = درخت_TYPE (درخت_TYPE (t));
		  اگر (درخت_رمز (elem_t) != ریکارڈ_TYPE
		      || strcmp (IDENTIFIER_اشارہ_گر (TYPE_IDENTIFIER (elem_t)),
				 "omp_alloctrait_t") != 0
		      || !TYPE_READONLY (elem_t))
		    type_err = سچ;
		}
	      اگر (type_err)
		{
		  اگر (t != error_mark_گرہ)
		    error_at (OMP_CLAUSE_LOCATION (c), "traits array %qE must "
			      "be of %<const omp_alloctrait_t []%> type", t);
		  ورنہ
		    error_at (OMP_CLAUSE_LOCATION (c), "traits array must "
			      "be of %<const omp_alloctrait_t []%> type");
		  remove = سچ;
		}
	      ورنہ
		{
		  درخت cst_val = decl_constant_قدر_1 (t, سچ);
		  اگر (cst_val == t)
		    {
		      error_at (OMP_CLAUSE_LOCATION (c), "traits array must be "
				"initialized with constants");

		      remove = سچ;
		    }
		}
	    }
	  اگر (remove)
	    توڑو;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  جاری;
	حالت OMP_CLAUSE_DEPEND:
	  depend_clause = c;
	  /* FALLTHRU */
	حالت OMP_CLAUSE_AFFINITY:
	  t = OMP_CLAUSE_DECL (c);
	  اگر (OMP_ITERATOR_DECL_P (t))
	    {
	      اگر (درخت_PURPOSE (t) != آخری_iterators)
		آخری_iterators_remove
		  = c_omp_اختتام_iterators (درخت_PURPOSE (t));
	      آخری_iterators = درخت_PURPOSE (t);
	      t = درخت_قدر (t);
	      اگر (آخری_iterators_remove)
		t = error_mark_گرہ;
	    }
	  ورنہ
	    آخری_iterators = NULL_درخت;
	  اگر (درخت_رمز (t) == OMP_ARRAY_SECTION)
	    {
	      اگر (handle_omp_array_sections (c, ort))
		remove = سچ;
	      ورنہ اگر (OMP_CLAUSE_رمز (c) == OMP_CLAUSE_DEPEND
		       && OMP_CLAUSE_DEPEND_قسم (c) == OMP_CLAUSE_DEPEND_DEPOBJ)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<depend%> clause with %<depobj%> dependence "
			    "type on array section");
		  remove = سچ;
		}
	      توڑو;
	    }
	  اگر (t == error_mark_گرہ)
	    remove = سچ;
	  ورنہ اگر (OMP_CLAUSE_رمز (c) == OMP_CLAUSE_DEPEND
		   && t == ridpointers[RID_OMP_ALL_حافظہ])
	    {
	      اگر (OMP_CLAUSE_DEPEND_قسم (c) != OMP_CLAUSE_DEPEND_برآمد
		  && OMP_CLAUSE_DEPEND_قسم (c) != OMP_CLAUSE_DEPEND_INOUT)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<omp_all_memory%> used with %<depend%> kind "
			    "other than %<out%> or %<inout%>");
		  remove = سچ;
		}
	    }
	  ورنہ اگر (!lvalue_p (t))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not lvalue expression nor array section in "
			"%qs clause", t,
			omp_clause_رمز_name[OMP_CLAUSE_رمز (c)]);
	      remove = سچ;
	    }
	  ورنہ اگر (درخت_رمز (t) == COMPONENT_REF
		   && DECL_C_ثنائی_ہندسہ_میدان (درخت_عملیہ (t, 1)))
	    {
	      gcc_assert (OMP_CLAUSE_رمز (c) == OMP_CLAUSE_DEPEND
			  || OMP_CLAUSE_رمز (c) == OMP_CLAUSE_AFFINITY);
	      error_at (OMP_CLAUSE_LOCATION (c),
			"bit-field %qE in %qs clause", t,
			omp_clause_رمز_name[OMP_CLAUSE_رمز (c)]);
	      remove = سچ;
	    }
	  ورنہ اگر (OMP_CLAUSE_رمز (c) == OMP_CLAUSE_DEPEND
		   && OMP_CLAUSE_DEPEND_قسم (c) == OMP_CLAUSE_DEPEND_DEPOBJ)
	    {
	      اگر (!c_omp_depend_t_p (درخت_TYPE (t)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qE does not have %<omp_depend_t%> type in "
			    "%<depend%> clause with %<depobj%> dependence "
			    "type", t);
		  remove = سچ;
		}
	    }
	  ورنہ اگر (OMP_CLAUSE_رمز (c) == OMP_CLAUSE_DEPEND
		   && c_omp_depend_t_p (درخت_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE should not have %<omp_depend_t%> type in "
			"%<depend%> clause with dependence type other than "
			"%<depobj%>", t);
	      remove = سچ;
	    }
	  اگر (!remove)
	    {
	      اگر (t == ridpointers[RID_OMP_ALL_حافظہ])
		t = null_اشارہ_گر_گرہ;
	      ورنہ
		{
		  درخت addr = build_unary_op (OMP_CLAUSE_LOCATION (c),
					      ADDR_اظہاریہ, t, جھوٹ);
		  اگر (addr == error_mark_گرہ)
		    {
		      remove = سچ;
		      توڑو;
		    }
		  t = build_بالواسطہ_ref (OMP_CLAUSE_LOCATION (c), addr,
					  RO_UNARY_ستارہ);
		  اگر (t == error_mark_گرہ)
		    {
		      remove = سچ;
		      توڑو;
		    }
		}
	      اگر (OMP_ITERATOR_DECL_P (OMP_CLAUSE_DECL (c)))
		درخت_قدر (OMP_CLAUSE_DECL (c)) = t;
	      ورنہ
		OMP_CLAUSE_DECL (c) = t;
	    }
	  توڑو;

	حالت OMP_CLAUSE_MAP:
	  اگر (OMP_CLAUSE_MAP_IMPLICIT (c) && !implicit_moved)
	    جاؤ move_implicit;
	  اگر (OMP_CLAUSE_MAP_قسم (c) == GOMP_MAP_ڈالو_MAPPER_NAME
	      || OMP_CLAUSE_MAP_قسم (c) == GOMP_MAP_نکالو_MAPPER_NAME)
	    {
	      remove = سچ;
	      توڑو;
	    }
	  /* FALLTHRU */
	حالت OMP_CLAUSE_مقصد:
	حالت OMP_CLAUSE_FROM:
	  اگر (OMP_CLAUSE_ITERATORS (c)
	      && c_omp_اختتام_iterators (OMP_CLAUSE_ITERATORS (c)))
	    {
	      t = error_mark_گرہ;
	      توڑو;
	    }
	  /* FALLTHRU */
	حالت OMP_CLAUSE__CACHE_:
	  {
	    استعمال نامخلا omp_addr_tokenizer;
	    auto_vec<omp_addr_token *, 10> addr_علامات;

	    t = OMP_CLAUSE_DECL (c);
	    اگر (درخت_رمز (t) == OMP_ARRAY_SECTION)
	      {
		grp_آغاز_p = pc;
		grp_sentinel = OMP_CLAUSE_CHAIN (c);

		اگر (handle_omp_array_sections (c, ort))
		  remove = سچ;
		ورنہ
		  {
		    t = OMP_CLAUSE_DECL (c);
		    اگر (!omp_mappable_type (درخت_TYPE (t)))
		      {
			error_at (OMP_CLAUSE_LOCATION (c),
				  "array section does not have mappable type "
				  "in %qs clause",
				  omp_clause_رمز_name[OMP_CLAUSE_رمز (c)]);
			remove = سچ;
		      }
		    ورنہ اگر (TYPE_ATOMIC (درخت_TYPE (t)))
		      {
			error_at (OMP_CLAUSE_LOCATION (c),
				  "%<_Atomic%> %qE in %qs clause", t,
				  omp_clause_رمز_name[OMP_CLAUSE_رمز (c)]);
			remove = سچ;
		      }
		    جب (درخت_رمز (t) == ARRAY_REF)
		      t = درخت_عملیہ (t, 0);

		    c_omp_پتہ_inspector ai (OMP_CLAUSE_LOCATION (c), t);

		    اگر (!omp_parse_اظہاریہ (addr_علامات, t))
		      {
			sorry_at (OMP_CLAUSE_LOCATION (c),
				  "unsupported map expression %qE",
				  OMP_CLAUSE_DECL (c));
			remove = سچ;
			توڑو;
		      }

		    /* This check is to determine if this will be the only map
		       node created for this clause.  Otherwise, we'll check
		       the following FIRSTPRIVATE_POINTER or ATTACH_DETACH
		       node on the next iteration(s) of the loop.   */
		    اگر (addr_علامات.لمبائی () >= 4
			&& addr_علامات[0]->type == STRUCTURE_بنیاد
			&& addr_علامات[0]->u.structure_بنیاد_قسم == بنیاد_DECL
			&& addr_علامات[1]->type == ACCESS_طریقہ
			&& addr_علامات[2]->type == COMPONENT_SELECTOR
			&& addr_علامات[3]->type == ACCESS_طریقہ
			&& (addr_علامات[3]->u.access_قسم == ACCESS_براہ_راست
			    || (addr_علامات[3]->u.access_قسم
				== ACCESS_اشاریہ_دار_ARRAY)))
		      {
			درخت rt = addr_علامات[1]->اظہاریہ;

			gcc_assert (DECL_P (rt));

			اگر (OMP_CLAUSE_رمز (c) == OMP_CLAUSE_MAP
			    && OMP_CLAUSE_MAP_IMPLICIT (c)
			    && (bitmap_ثنائی_ہندسہ_p (&map_سر, DECL_UID (rt))
				|| bitmap_ثنائی_ہندسہ_p (&map_میدان_سر, DECL_UID (rt))
				|| bitmap_ثنائی_ہندسہ_p (&map_firstprivate_سر,
						 DECL_UID (rt))))
			  {
			    remove = سچ;
			    توڑو;
			  }
			اگر (bitmap_ثنائی_ہندسہ_p (&map_میدان_سر, DECL_UID (rt)))
			  توڑو;
			اگر (bitmap_ثنائی_ہندسہ_p (&map_سر, DECL_UID (rt)))
			  {
			    اگر (OMP_CLAUSE_رمز (c) != OMP_CLAUSE_MAP)
			      error_at (OMP_CLAUSE_LOCATION (c),
					"%qD appears more than once in motion "
					"clauses", rt);
			    ورنہ اگر (openacc)
			      error_at (OMP_CLAUSE_LOCATION (c),
					"%qD appears more than once in data "
					"clauses", rt);
			    ورنہ
			      error_at (OMP_CLAUSE_LOCATION (c),
					"%qD appears more than once in map "
					"clauses", rt);
			    remove = سچ;
			  }
			ورنہ
			  {
			    bitmap_سیٹ_ثنائی_ہندسہ (&map_سر, DECL_UID (rt));
			    bitmap_سیٹ_ثنائی_ہندسہ (&map_میدان_سر, DECL_UID (rt));
			  }
		      }
		  }
		اگر (c_oacc_check_attachments (c))
		  remove = سچ;
		اگر (OMP_CLAUSE_رمز (c) == OMP_CLAUSE_MAP
		    && (OMP_CLAUSE_MAP_قسم (c) == GOMP_MAP_ATTACH
			|| OMP_CLAUSE_MAP_قسم (c) == GOMP_MAP_DETACH)
		    && !OMP_CLAUSE_سائز (c))
		  /* In this case, we have a single array element which is a
		     pointer, and we already set OMP_CLAUSE_SIZE in
		     handle_omp_array_sections above.  For attach/detach
		     clauses, reset the OMP_CLAUSE_SIZE (representing a bias)
		     to zero here.  */
		  OMP_CLAUSE_سائز (c) = سائز_zero_گرہ;
		توڑو;
	      }
	    ورنہ اگر (!omp_parse_اظہاریہ (addr_علامات, t))
	      {
		sorry_at (OMP_CLAUSE_LOCATION (c),
			  "unsupported map expression %qE",
			  OMP_CLAUSE_DECL (c));
		remove = سچ;
		توڑو;
	      }
	    اگر (t == error_mark_گرہ)
	      {
		remove = سچ;
		توڑو;
	      }

	    درخت attr;
	    اگر (DECL_P (t)
		&& OMP_CLAUSE_رمز (c) == OMP_CLAUSE_MAP
		&& (attr = lookup_attribute ("omp declare target",
					     DECL_اوصاف (t)))
		&& قدر_member (get_identifier ("local"),
				 درخت_قدر (attr)))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "device-local variable %qD cannot appear "
			  "in map clause", t);
		remove = سچ;
		توڑو;
	      }

	    /* OpenACC attach / detach clauses must be pointers.  */
	    اگر (c_oacc_check_attachments (c))
	      {
		remove = سچ;
		توڑو;
	      }
	    اگر (OMP_CLAUSE_رمز (c) == OMP_CLAUSE_MAP
		&& (OMP_CLAUSE_MAP_قسم (c) == GOMP_MAP_ATTACH
		    || OMP_CLAUSE_MAP_قسم (c) == GOMP_MAP_DETACH)
		&& !OMP_CLAUSE_سائز (c))
	      /* For attach/detach clauses, set OMP_CLAUSE_SIZE (representing a
		 bias) to zero here, so it is not set erroneously to the pointer
		 size later on in gimplify.cc.  */
	      OMP_CLAUSE_سائز (c) = سائز_zero_گرہ;

	    c_omp_پتہ_inspector ai (OMP_CLAUSE_LOCATION (c), t);

	    اگر (!ai.check_clause (c))
	      {
		remove = سچ;
		توڑو;
	      }

	    اگر (!ai.map_supported_p ())
	      {
		sorry_at (OMP_CLAUSE_LOCATION (c),
			  "unsupported map expression %qE",
			  OMP_CLAUSE_DECL (c));
		remove = سچ;
		توڑو;
	      }

	    gcc_assert ((addr_علامات[0]->type == ARRAY_بنیاد
			 || addr_علامات[0]->type == STRUCTURE_بنیاد)
			&& addr_علامات[1]->type == ACCESS_طریقہ);

	    t = addr_علامات[1]->اظہاریہ;

	    اگر (addr_علامات[0]->u.structure_بنیاد_قسم != بنیاد_DECL)
	      جاؤ skip_decl_checks;

	    /* For OpenMP, we can access a struct "t" and "t.d" on the same
	       mapping.  OpenACC allows multiple fields of the same structure
	       to be written.  */
	    اگر (addr_علامات[0]->type == STRUCTURE_بنیاد
		&& (bitmap_ثنائی_ہندسہ_p (&map_میدان_سر, DECL_UID (t))
		    || (!openacc && bitmap_ثنائی_ہندسہ_p (&map_سر, DECL_UID (t)))))
	      جاؤ skip_decl_checks;

	    اگر (!VAR_P (t) && درخت_رمز (t) != PARM_DECL)
	      {
		اگر (ort != C_ORT_ACC && اظہاریہ_P (t))
		  توڑو;

		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is not a variable in %qs clause", t,
			  omp_clause_رمز_name[OMP_CLAUSE_رمز (c)]);
		remove = سچ;
	      }
	    ورنہ اگر (VAR_P (t) && DECL_THREAD_LOCAL_P (t))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD is threadprivate variable in %qs clause", t,
			  omp_clause_رمز_name[OMP_CLAUSE_رمز (c)]);
		remove = سچ;
	      }
	    ورنہ اگر ((OMP_CLAUSE_رمز (c) != OMP_CLAUSE_MAP
		      || (OMP_CLAUSE_MAP_قسم (c)
			  != GOMP_MAP_FIRSTPRIVATE_اشارہ_گر))
		     && !c_mark_addressable (t))
	      remove = سچ;
	    ورنہ اگر (!(OMP_CLAUSE_رمز (c) == OMP_CLAUSE_MAP
		       && (OMP_CLAUSE_MAP_قسم (c) == GOMP_MAP_اشارہ_گر
			   || (OMP_CLAUSE_MAP_قسم (c)
			       == GOMP_MAP_FIRSTPRIVATE_اشارہ_گر)
			   || (OMP_CLAUSE_MAP_قسم (c)
			       == GOMP_MAP_FORCE_DEVICEPTR)))
		     && t == OMP_CLAUSE_DECL (c)
		     && !omp_mappable_type (درخت_TYPE (t)))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD does not have a mappable type in %qs clause", t,
			  omp_clause_رمز_name[OMP_CLAUSE_رمز (c)]);
		remove = سچ;
	      }
	    ورنہ اگر (درخت_TYPE (t) == error_mark_گرہ)
	      remove = سچ;
	    ورنہ اگر (TYPE_ATOMIC (strip_array_types (درخت_TYPE (t))))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%<_Atomic%> %qE in %qs clause", t,
			  omp_clause_رمز_name[OMP_CLAUSE_رمز (c)]);
		remove = سچ;
	      }
	    ورنہ اگر (OMP_CLAUSE_رمز (c) == OMP_CLAUSE_MAP
		     && OMP_CLAUSE_MAP_IMPLICIT (c)
		     && (bitmap_ثنائی_ہندسہ_p (&map_سر, DECL_UID (t))
			 || bitmap_ثنائی_ہندسہ_p (&map_میدان_سر, DECL_UID (t))
			 || bitmap_ثنائی_ہندسہ_p (&map_firstprivate_سر,
					  DECL_UID (t))))
	      remove = سچ;
	    ورنہ اگر (OMP_CLAUSE_رمز (c) == OMP_CLAUSE_MAP
		     && (OMP_CLAUSE_MAP_قسم (c)
			 == GOMP_MAP_FIRSTPRIVATE_اشارہ_گر))
	      {
		اگر (bitmap_ثنائی_ہندسہ_p (&generic_سر, DECL_UID (t))
		    || bitmap_ثنائی_ہندسہ_p (&firstprivate_سر, DECL_UID (t))
		    || bitmap_ثنائی_ہندسہ_p (&map_firstprivate_سر, DECL_UID (t)))
		  {
		    error_at (OMP_CLAUSE_LOCATION (c),
			      "%qD appears more than once in data clauses", t);
		    remove = سچ;
		  }
		ورنہ اگر (bitmap_ثنائی_ہندسہ_p (&map_سر, DECL_UID (t))
			 && !bitmap_ثنائی_ہندسہ_p (&map_میدان_سر, DECL_UID (t))
			 && openacc)
		  {
		    error_at (OMP_CLAUSE_LOCATION (c),
			      "%qD appears more than once in data clauses", t);
		    remove = سچ;
		  }
		ورنہ
		  bitmap_سیٹ_ثنائی_ہندسہ (&map_firstprivate_سر, DECL_UID (t));
	      }
	    ورنہ اگر (bitmap_ثنائی_ہندسہ_p (&map_سر, DECL_UID (t))
		     && !bitmap_ثنائی_ہندسہ_p (&map_میدان_سر, DECL_UID (t))
		     && ort != C_ORT_OMP
		     && ort != C_ORT_OMP_ہدف
		     && ort != C_ORT_OMP_EXIT_ڈیٹا)
	      {
		اگر (OMP_CLAUSE_رمز (c) != OMP_CLAUSE_MAP)
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in motion clauses", t);
		ورنہ اگر (openacc)
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in data clauses", t);
		ورنہ
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in map clauses", t);
		remove = سچ;
	      }
	    ورنہ اگر (openacc && bitmap_ثنائی_ہندسہ_p (&generic_سر, DECL_UID (t)))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears more than once in data clauses", t);
		remove = سچ;
	      }
	    ورنہ اگر (bitmap_ثنائی_ہندسہ_p (&firstprivate_سر, DECL_UID (t))
		     || bitmap_ثنائی_ہندسہ_p (&is_on_device_سر, DECL_UID (t)))
	      {
		اگر (openacc)
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in data clauses", t);
		ورنہ
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears both in data and map clauses", t);
		remove = سچ;
	      }
	    ورنہ اگر (!omp_access_chain_p (addr_علامات, 1))
	      {
		bitmap_سیٹ_ثنائی_ہندسہ (&map_سر, DECL_UID (t));
		اگر (t != OMP_CLAUSE_DECL (c)
		    && درخت_رمز (OMP_CLAUSE_DECL (c)) == COMPONENT_REF)
		  bitmap_سیٹ_ثنائی_ہندسہ (&map_میدان_سر, DECL_UID (t));
	      }

	  skip_decl_checks:
	    /* If we call omp_expand_map_clause in handle_omp_array_sections,
	       the containing loop (here) iterates through the new nodes
	       created by that expansion.  Avoid expanding those again (just
	       by checking the node type).  */
	    اگر (!remove
		&& ort != C_ORT_DECLARE_SIMD
		&& (OMP_CLAUSE_رمز (c) != OMP_CLAUSE_MAP
		    || (OMP_CLAUSE_MAP_قسم (c) != GOMP_MAP_FIRSTPRIVATE_اشارہ_گر
			&& (OMP_CLAUSE_MAP_قسم (c)
			    != GOMP_MAP_FIRSTPRIVATE_REFERENCE)
			&& OMP_CLAUSE_MAP_قسم (c) != GOMP_MAP_ALWAYS_اشارہ_گر
			&& OMP_CLAUSE_MAP_قسم (c) != GOMP_MAP_ATTACH_DETACH
			&& OMP_CLAUSE_MAP_قسم (c) != GOMP_MAP_ATTACH
			&& OMP_CLAUSE_MAP_قسم (c) != GOMP_MAP_DETACH)))
	      {
		grp_آغاز_p = pc;
		grp_sentinel = OMP_CLAUSE_CHAIN (c);
		درخت nc = ai.expand_map_clause (c, OMP_CLAUSE_DECL (c),
						addr_علامات, ort);
		اگر (nc != error_mark_گرہ)
		  c = nc;
	      }
	  }
	  توڑو;

	حالت OMP_CLAUSE_ENTER:
	حالت OMP_CLAUSE_LINK:
	حالت OMP_CLAUSE_LOCAL:
	  t = OMP_CLAUSE_DECL (c);
	  ثابت حرف *cname;
	  cname = omp_clause_رمز_name[OMP_CLAUSE_رمز (c)];
	  اگر (OMP_CLAUSE_رمز (c) == OMP_CLAUSE_ENTER
	      && OMP_CLAUSE_ENTER_مقصد (c))
	    cname = "to";
	  اگر (درخت_رمز (t) == FUNCTION_DECL
	      && OMP_CLAUSE_رمز (c) == OMP_CLAUSE_ENTER)
	    ;
	  ورنہ اگر (!VAR_P (t))
	    {
	      اگر (OMP_CLAUSE_رمز (c) == OMP_CLAUSE_ENTER)
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is neither a variable nor a function name in "
			  "clause %qs", t, cname);
	      ورنہ
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is not a variable in clause %qs", t, cname);
	      remove = سچ;
	    }
	  ورنہ اگر (DECL_THREAD_LOCAL_P (t))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD is threadprivate variable in %qs clause", t,
			cname);
	      remove = سچ;
	    }
	  ورنہ اگر (!omp_mappable_type (درخت_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD does not have a mappable type in %qs clause", t,
			cname);
	      remove = سچ;
	    }
	  اگر (remove)
	    توڑو;
	  اگر (bitmap_ثنائی_ہندسہ_p (&generic_سر, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once on the same "
			"%<declare target%> directive", t);
	      remove = سچ;
	    }
	  ورنہ
	    bitmap_سیٹ_ثنائی_ہندسہ (&generic_سر, DECL_UID (t));
	  توڑو;

	حالت OMP_CLAUSE_یکساں:
	  t = OMP_CLAUSE_DECL (c);
	  اگر (درخت_رمز (t) != PARM_DECL)
	    {
	      اگر (DECL_P (t))
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD is not an argument in %<uniform%> clause", t);
	      ورنہ
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is not an argument in %<uniform%> clause", t);
	      remove = سچ;
	      توڑو;
	    }
	  /* map_head bitmap is used as uniform_head if declare_simd.  */
	  bitmap_سیٹ_ثنائی_ہندسہ (&map_سر, DECL_UID (t));
	  جاؤ check_dup_generic;

	حالت OMP_CLAUSE_IS_DEVICE_PTR:
	حالت OMP_CLAUSE_USE_DEVICE_PTR:
	  t = OMP_CLAUSE_DECL (c);
	  اگر (OMP_CLAUSE_رمز (c) == OMP_CLAUSE_IS_DEVICE_PTR)
	    bitmap_سیٹ_ثنائی_ہندسہ (&is_on_device_سر, DECL_UID (t));
	  اگر (درخت_رمز (درخت_TYPE (t)) != اشارہ_گر_TYPE)
	    {
	      اگر (OMP_CLAUSE_رمز (c) == OMP_CLAUSE_USE_DEVICE_PTR
		  && !openacc)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qs variable is not a pointer",
			    omp_clause_رمز_name[OMP_CLAUSE_رمز (c)]);
		  remove = سچ;
		}
	      ورنہ اگر (درخت_رمز (درخت_TYPE (t)) != ARRAY_TYPE)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qs variable is neither a pointer nor an array",
			    omp_clause_رمز_name[OMP_CLAUSE_رمز (c)]);
		  remove = سچ;
		}
	    }
	  جاؤ check_dup_generic;

	حالت OMP_CLAUSE_HAS_DEVICE_ADDR:
	  t = OMP_CLAUSE_DECL (c);
	  اگر (درخت_رمز (t) == OMP_ARRAY_SECTION)
	    {
	      اگر (handle_omp_array_sections (c, ort))
		remove = سچ;
	      ورنہ
		{
		  t = OMP_CLAUSE_DECL (c);
		  جب (درخت_رمز (t) == ARRAY_REF)
		    t = درخت_عملیہ (t, 0);
		}
	    }
	  bitmap_سیٹ_ثنائی_ہندسہ (&is_on_device_سر, DECL_UID (t));
	  اگر (VAR_P (t) || درخت_رمز (t) == PARM_DECL)
	    c_mark_addressable (t);
	  جاؤ check_dup_generic_t;

	حالت OMP_CLAUSE_USE_DEVICE_ADDR:
	  t = OMP_CLAUSE_DECL (c);
	  اگر (VAR_P (t) || درخت_رمز (t) == PARM_DECL)
	    c_mark_addressable (t);
	  جاؤ check_dup_generic;

	حالت OMP_CLAUSE_NOWAIT:
	  اگر (copyprivate_نظر_آیا)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<nowait%> clause must not be used together "
			"with %<copyprivate%> clause");
	      remove = سچ;
	      توڑو;
	    }
	  nowait_clause = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  جاری;

	حالت OMP_CLAUSE_ترتیب:
	  اگر (ordered_clause)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<order%> clause must not be used together "
			"with %<ordered%> clause");
	      remove = سچ;
	      توڑو;
	    }
	  ورنہ اگر (ترتیب_clause)
	    {
	      /* Silently remove duplicates.  */
	      remove = سچ;
	      توڑو;
	    }
	  ترتیب_clause = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  جاری;

	حالت OMP_CLAUSE_DETACH:
	  t = OMP_CLAUSE_DECL (c);
	  اگر (detach_نظر_آیا)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"too many %qs clauses on a task construct",
			"detach");
	      remove = سچ;
	      توڑو;
	    }
	  detach_نظر_آیا = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  c_mark_addressable (t);
	  جاری;

	حالت OMP_CLAUSE_IF:
	حالت OMP_CLAUSE_SELF:
	حالت OMP_CLAUSE_عدد_دھاگے:
	حالت OMP_CLAUSE_عدد_TEAMS:
	حالت OMP_CLAUSE_THREAD_حد_بندی:
	حالت OMP_CLAUSE_DEFAULT:
	حالت OMP_CLAUSE_UNTIED:
	حالت OMP_CLAUSE_COLLAPSE:
	حالت OMP_CLAUSE_FINAL:
	حالت OMP_CLAUSE_DEVICE:
	حالت OMP_CLAUSE_DIST_جدول_وقت:
	حالت OMP_CLAUSE_DYN_GROUPPRIVATE:
	حالت OMP_CLAUSE_PARALLEL:
	حالت OMP_CLAUSE_FOR:
	حالت OMP_CLAUSE_SECTIONS:
	حالت OMP_CLAUSE_TASKGROUP:
	حالت OMP_CLAUSE_PROC_BIND:
	حالت OMP_CLAUSE_DEVICE_TYPE:
	حالت OMP_CLAUSE_ترجیح:
	حالت OMP_CLAUSE_دھاگے:
	حالت OMP_CLAUSE_SIMD:
	حالت OMP_CLAUSE_HINT:
	حالت OMP_CLAUSE_FILTER:
	حالت OMP_CLAUSE_DEFAULTMAP:
	حالت OMP_CLAUSE_BIND:
	حالت OMP_CLAUSE_عدد_GANGS:
	حالت OMP_CLAUSE_عدد_WORKERS:
	حالت OMP_CLAUSE_سمتیہ_لمبائی:
	حالت OMP_CLAUSE_ASYNC:
	حالت OMP_CLAUSE_WAIT:
	حالت OMP_CLAUSE_AUTO:
	حالت OMP_CLAUSE_INDEPENDENT:
	حالت OMP_CLAUSE_SEQ:
	حالت OMP_CLAUSE_GANG:
	حالت OMP_CLAUSE_کارکن:
	حالت OMP_CLAUSE_سمتیہ:
	حالت OMP_CLAUSE_TILE:
	حالت OMP_CLAUSE_IF_PRESENT:
	حالت OMP_CLAUSE_FINALIZE:
	حالت OMP_CLAUSE_NOHOST:
	حالت OMP_CLAUSE_بالواسطہ:
	حالت OMP_CLAUSE_NOVARIANTS:
	حالت OMP_CLAUSE_NOCONTEXT:
	  pc = &OMP_CLAUSE_CHAIN (c);
	  جاری;

	حالت OMP_CLAUSE_GRAINSIZE:
	  grainsize_نظر_آیا = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  جاری;

	حالت OMP_CLAUSE_عدد_TASKS:
	  عدد_tasks_نظر_آیا = سچ;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  جاری;

	حالت OMP_CLAUSE_MERGEABLE:
	  mergeable_نظر_آیا = سچ;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  جاری;

	حالت OMP_CLAUSE_NOGROUP:
	  nogroup_نظر_آیا = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  جاری;

	حالت OMP_CLAUSE_جدول_وقت:
	  جدول_وقت_clause = c;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  جاری;

	حالت OMP_CLAUSE_ORDERED:
	  ordered_clause = c;
	  اگر (ترتیب_clause)
	    {
	      error_at (OMP_CLAUSE_LOCATION (*ترتیب_clause),
			"%<order%> clause must not be used together "
			"with %<ordered%> clause");
	      *ترتیب_clause = OMP_CLAUSE_CHAIN (*ترتیب_clause);
	      ترتیب_clause = تہی;
	    }
	  pc = &OMP_CLAUSE_CHAIN (c);
	  جاری;

	حالت OMP_CLAUSE_SAFELEN:
	  safelen = c;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  جاری;
	حالت OMP_CLAUSE_SIMDLEN:
	  simdlen = c;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  جاری;

	حالت OMP_CLAUSE_بھرا:
	  بھرا_نظر_آیا = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  جاری;

	حالت OMP_CLAUSE_PARTIAL:
	  partial_نظر_آیا = سچ;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  جاری;

	حالت OMP_CLAUSE_SIZES:
	  pc = &OMP_CLAUSE_CHAIN (c);
	  جاری;

	حالت OMP_CLAUSE_INBRANCH:
	حالت OMP_CLAUSE_NOTINBRANCH:
	  اگر (branch_نظر_آیا)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<inbranch%> clause is incompatible with "
			"%<notinbranch%>");
	      remove = سچ;
	      توڑو;
	    }
	  branch_نظر_آیا = سچ;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  جاری;

	حالت OMP_CLAUSE_INCLUSIVE:
	حالت OMP_CLAUSE_EXCLUSIVE:
	  need_complete = سچ;
	  need_implicitly_determined = سچ;
	  t = OMP_CLAUSE_DECL (c);
	  اگر (!VAR_P (t) && درخت_رمز (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %qs", t,
			omp_clause_رمز_name[OMP_CLAUSE_رمز (c)]);
	      remove = سچ;
	    }
	  توڑو;

	حالت OMP_CLAUSE_INIT:
	  init_نظر_آیا = سچ;
	  اگر (!OMP_CLAUSE_INIT_TARGETSYNC (c))
	    init_no_targetsync_clause = c;
	  /* FALLTHRU */
	حالت OMP_CLAUSE_DESTROY:
	حالت OMP_CLAUSE_USE:
	  init_use_destroy_نظر_آیا = سچ;
	  t = OMP_CLAUSE_DECL (c);
	  اگر (bitmap_ثنائی_ہندسہ_p (&generic_سر, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD appears more than once in action clauses", t);
	      remove = سچ;
	      توڑو;
	    }
	  bitmap_سیٹ_ثنائی_ہندسہ (&generic_سر, DECL_UID (t));
	  /* FALLTHRU */
	حالت OMP_CLAUSE_INTEROP:
	  اگر (/* ort == C_ORT_OMP_INTEROP [uncomment for depobj init]  */
		   !c_omp_interop_t_p (درخت_TYPE (OMP_CLAUSE_DECL (c))))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD must be of %<omp_interop_t%>",
			OMP_CLAUSE_DECL (c));
	      remove = سچ;
	    }
	  ورنہ اگر ((OMP_CLAUSE_رمز (c) == OMP_CLAUSE_INIT
		    || OMP_CLAUSE_رمز (c) == OMP_CLAUSE_DESTROY)
		   && درخت_READONLY (OMP_CLAUSE_DECL (c)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD shall not be const", OMP_CLAUSE_DECL (c));
	      remove = سچ;
	    }
	  pc = &OMP_CLAUSE_CHAIN (c);
	  توڑو;
	طےشدہ:
	  gcc_unreachable ();
	}

      اگر (!remove)
	{
	  t = OMP_CLAUSE_DECL (c);

	  اگر (need_complete)
	    {
	      t = require_complete_type (OMP_CLAUSE_LOCATION (c), t);
	      اگر (t == error_mark_گرہ)
		remove = سچ;
	    }

	  اگر (need_implicitly_determined)
	    {
	      ثابت حرف *share_name = تہی;

	      اگر (VAR_P (t) && DECL_THREAD_LOCAL_P (t))
		share_name = "threadprivate";
	      ورنہ انتخاب (c_omp_predetermined_sharing (t))
		{
		حالت OMP_CLAUSE_DEFAULT_UNSPECIFIED:
		  توڑو;
		حالت OMP_CLAUSE_DEFAULT_SHARED:
		  اگر ((OMP_CLAUSE_رمز (c) == OMP_CLAUSE_SHARED
		       || OMP_CLAUSE_رمز (c) == OMP_CLAUSE_FIRSTPRIVATE)
		      && c_omp_predefined_variable (t))
		    /* The __func__ variable and similar function-local
		       predefined variables may be listed in a shared or
		       firstprivate clause.  */
		    توڑو;
		  share_name = "shared";
		  توڑو;
		حالت OMP_CLAUSE_DEFAULT_نجی:
		  share_name = "private";
		  توڑو;
		طےشدہ:
		  gcc_unreachable ();
		}
	      اگر (share_name)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qE is predetermined %qs for %qs",
			    t, share_name,
			    omp_clause_رمز_name[OMP_CLAUSE_رمز (c)]);
		  remove = سچ;
		}
	      ورنہ اگر (درخت_READONLY (t)
		       && OMP_CLAUSE_رمز (c) != OMP_CLAUSE_SHARED
		       && OMP_CLAUSE_رمز (c) != OMP_CLAUSE_FIRSTPRIVATE)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<const%> qualified %qE may appear only in "
			    "%<shared%> or %<firstprivate%> clauses", t);
		  remove = سچ;
		}
	    }
	}

      اگر (remove)
	{
	  اگر (grp_آغاز_p)
	    {
	      /* If we found a clause to remove, we want to remove the whole
		 expanded group, otherwise gimplify
		 (omp_resolve_clause_dependencies) can get confused.  */
	      *grp_آغاز_p = grp_sentinel;
	      pc = grp_آغاز_p;
	      grp_آغاز_p = تہی;
	    }
	  ورنہ
	    *pc = OMP_CLAUSE_CHAIN (c);
	}
      ورنہ
	pc = &OMP_CLAUSE_CHAIN (c);
    }

  اگر (grp_آغاز_p
      && OMP_CLAUSE_HAS_ITERATORS (*grp_آغاز_p))
    برائے (درخت gc = *grp_آغاز_p; gc; gc = OMP_CLAUSE_CHAIN (gc))
      OMP_CLAUSE_ITERATORS (gc) = OMP_CLAUSE_ITERATORS (*grp_آغاز_p);

  اگر (simdlen
      && safelen
      && درخت_int_cst_lt (OMP_CLAUSE_SAFELEN_اظہاریہ (safelen),
			  OMP_CLAUSE_SIMDLEN_اظہاریہ (simdlen)))
    {
      /* Note: How a scaling factor affects this, is underspecified in OpenMP;
	 cf. OpenMP spec issue #5160.  Presumably, it means:
	   savelen >= simdlen * scale_factor
	 with
	   scale_factor = MAX (1, FLOOR_DIV_EXPR (VL(type), divisor))
	 and OpenMP states that VL(type) might be only known at runtime.
	 Hence scale_factor >= 1 and, conservatively, assume == 1 for this
	 error check.  */
      error_at (OMP_CLAUSE_LOCATION (simdlen),
		"%<simdlen%> clause value is bigger than "
		"%<safelen%> clause value");
      OMP_CLAUSE_SIMDLEN_اظہاریہ (simdlen)
	= OMP_CLAUSE_SAFELEN_اظہاریہ (safelen);
    }

  اگر (ordered_clause
      && جدول_وقت_clause
      && (OMP_CLAUSE_جدول_وقت_قسم (جدول_وقت_clause)
	  & OMP_CLAUSE_جدول_وقت_NONMONOTONIC))
    {
      error_at (OMP_CLAUSE_LOCATION (جدول_وقت_clause),
		"%<nonmonotonic%> schedule modifier specified together "
		"with %<ordered%> clause");
      OMP_CLAUSE_جدول_وقت_قسم (جدول_وقت_clause)
	= (شمار omp_clause_جدول_وقت_قسم)
	  (OMP_CLAUSE_جدول_وقت_قسم (جدول_وقت_clause)
	   & ~OMP_CLAUSE_جدول_وقت_NONMONOTONIC);
    }

  اگر (reduction_نظر_آیا < 0 && ordered_clause)
    {
      error_at (OMP_CLAUSE_LOCATION (ordered_clause),
		"%qs clause specified together with %<inscan%> "
		"%<reduction%> clause", "ordered");
      reduction_نظر_آیا = -2;
    }

  اگر (reduction_نظر_آیا < 0 && جدول_وقت_clause)
    {
      error_at (OMP_CLAUSE_LOCATION (جدول_وقت_clause),
		"%qs clause specified together with %<inscan%> "
		"%<reduction%> clause", "schedule");
      reduction_نظر_آیا = -2;
    }

  اگر (خطی_variable_قدم_check
      || reduction_نظر_آیا == -2
      || allocate_نظر_آیا
      || ہدف_اندر_reduction_نظر_آیا)
    برائے (pc = &clauses, c = clauses; c ; c = *pc)
      {
	منطقی remove = جھوٹ;
	اگر (allocate_نظر_آیا)
	  انتخاب (OMP_CLAUSE_رمز (c))
	    {
	    حالت OMP_CLAUSE_REDUCTION:
	    حالت OMP_CLAUSE_اندر_REDUCTION:
	    حالت OMP_CLAUSE_TASK_REDUCTION:
	      اگر (درخت_رمز (OMP_CLAUSE_DECL (c)) == MEM_REF)
		{
		  t = درخت_عملیہ (OMP_CLAUSE_DECL (c), 0);
		  اگر (درخت_رمز (t) == اشارہ_گر_PLUS_اظہاریہ)
		    t = درخت_عملیہ (t, 0);
		  اگر (درخت_رمز (t) == ADDR_اظہاریہ
		      || بالواسطہ_REF_P (t))
		    t = درخت_عملیہ (t, 0);
		  اگر (DECL_P (t))
		    bitmap_clear_ثنائی_ہندسہ (&aligned_سر, DECL_UID (t));
		  توڑو;
		}
	      /* FALLTHRU */
	    حالت OMP_CLAUSE_نجی:
	    حالت OMP_CLAUSE_FIRSTPRIVATE:
	    حالت OMP_CLAUSE_LASTPRIVATE:
	    حالت OMP_CLAUSE_خطی:
	      اگر (DECL_P (OMP_CLAUSE_DECL (c)))
		bitmap_clear_ثنائی_ہندسہ (&aligned_سر,
				  DECL_UID (OMP_CLAUSE_DECL (c)));
	      توڑو;
	    طےشدہ:
	      توڑو;
	    }
	اگر (OMP_CLAUSE_رمز (c) == OMP_CLAUSE_خطی
	    && OMP_CLAUSE_خطی_VARIABLE_STRIDE (c)
	    && !bitmap_ثنائی_ہندسہ_p (&map_سر,
			      DECL_UID (OMP_CLAUSE_خطی_قدم (c))))
	  {
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%<linear%> clause step is a parameter %qD not "
		      "specified in %<uniform%> clause",
		      OMP_CLAUSE_خطی_قدم (c));
	    remove = سچ;
	  }
	ورنہ اگر (OMP_CLAUSE_رمز (c) == OMP_CLAUSE_REDUCTION
		 && reduction_نظر_آیا == -2)
	  OMP_CLAUSE_REDUCTION_INSCAN (c) = 0;
	اگر (ہدف_اندر_reduction_نظر_آیا
	    && OMP_CLAUSE_رمز (c) == OMP_CLAUSE_MAP)
	  {
	    درخت t = OMP_CLAUSE_DECL (c);
	    جب (handled_component_p (t)
		   || بالواسطہ_REF_P (t)
		   || درخت_رمز (t) == ADDR_اظہاریہ
		   || درخت_رمز (t) == MEM_REF
		   || درخت_رمز (t) == NON_LVALUE_اظہاریہ)
	      t = درخت_عملیہ (t, 0);
	    اگر (DECL_P (t)
		&& bitmap_ثنائی_ہندسہ_p (&oacc_reduction_سر, DECL_UID (t)))
	      OMP_CLAUSE_MAP_اندر_REDUCTION (c) = 1;
	  }

	اگر (remove)
	  *pc = OMP_CLAUSE_CHAIN (c);
	ورنہ
	  pc = &OMP_CLAUSE_CHAIN (c);
      }

  اگر (allocate_نظر_آیا)
    برائے (pc = &clauses, c = clauses; c ; c = *pc)
      {
	منطقی remove = جھوٹ;
	اگر (OMP_CLAUSE_رمز (c) == OMP_CLAUSE_ALLOCATE
	    && !OMP_CLAUSE_ALLOCATE_COMBINED (c)
	    && bitmap_ثنائی_ہندسہ_p (&aligned_سر, DECL_UID (OMP_CLAUSE_DECL (c))))
	  {
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD specified in %<allocate%> clause but not in "
		      "an explicit privatization clause", OMP_CLAUSE_DECL (c));
	    remove = سچ;
	  }
	اگر (remove)
	  *pc = OMP_CLAUSE_CHAIN (c);
	ورنہ
	  pc = &OMP_CLAUSE_CHAIN (c);
      }

  اگر (nogroup_نظر_آیا && reduction_نظر_آیا)
    {
      error_at (OMP_CLAUSE_LOCATION (*nogroup_نظر_آیا),
		"%<nogroup%> clause must not be used together with "
		"%<reduction%> clause");
      *nogroup_نظر_آیا = OMP_CLAUSE_CHAIN (*nogroup_نظر_آیا);
    }

  اگر (grainsize_نظر_آیا && عدد_tasks_نظر_آیا)
    {
      error_at (OMP_CLAUSE_LOCATION (*grainsize_نظر_آیا),
		"%<grainsize%> clause must not be used together with "
		"%<num_tasks%> clause");
      *grainsize_نظر_آیا = OMP_CLAUSE_CHAIN (*grainsize_نظر_آیا);
    }

  اگر (بھرا_نظر_آیا && partial_نظر_آیا)
    {
      error_at (OMP_CLAUSE_LOCATION (*بھرا_نظر_آیا),
		"%<full%> clause must not be used together with "
		"%<partial%> clause");
      *بھرا_نظر_آیا = OMP_CLAUSE_CHAIN (*بھرا_نظر_آیا);
    }

  اگر (detach_نظر_آیا)
    {
      اگر (mergeable_نظر_آیا)
	{
	  error_at (OMP_CLAUSE_LOCATION (*detach_نظر_آیا),
		    "%<detach%> clause must not be used together with "
		    "%<mergeable%> clause");
	  *detach_نظر_آیا = OMP_CLAUSE_CHAIN (*detach_نظر_آیا);
	}
      ورنہ
	{
	  درخت detach_decl = OMP_CLAUSE_DECL (*detach_نظر_آیا);

	  برائے (pc = &clauses, c = clauses; c ; c = *pc)
	    {
	      منطقی remove = جھوٹ;
	      اگر ((OMP_CLAUSE_رمز (c) == OMP_CLAUSE_SHARED
		   || OMP_CLAUSE_رمز (c) == OMP_CLAUSE_نجی
		   || OMP_CLAUSE_رمز (c) == OMP_CLAUSE_FIRSTPRIVATE
		   || OMP_CLAUSE_رمز (c) == OMP_CLAUSE_LASTPRIVATE)
		  && OMP_CLAUSE_DECL (c) == detach_decl)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "the event handle of a %<detach%> clause "
			    "should not be in a data-sharing clause");
		  remove = سچ;
		}
	      اگر (remove)
		*pc = OMP_CLAUSE_CHAIN (c);
	      ورنہ
		pc = &OMP_CLAUSE_CHAIN (c);
	    }
	}
    }

  اگر (ort == C_ORT_OMP_INTEROP
      && depend_clause
      && (!init_use_destroy_نظر_آیا
	  || (init_نظر_آیا && init_no_targetsync_clause)))
    {
      error_at (OMP_CLAUSE_LOCATION (depend_clause),
		"%<depend%> clause requires action clauses with "
		"%<targetsync%> interop-type");
      اگر (init_no_targetsync_clause)
	inform (OMP_CLAUSE_LOCATION (init_no_targetsync_clause),
		"%<init%> clause lacks the %<targetsync%> modifier");
    }

  bitmap_obstack_release (تہی);
  واپس clauses;
}

/* Do processing necessary to make CLAUSES well-formed, where CLAUSES result
   from implicit instantiation of user-defined mappers (in gimplify.cc).  */

درخت
c_omp_اختتام_mapper_clauses (درخت clauses)
{
  واپس c_اختتام_omp_clauses (clauses, C_ORT_OMP);
}

/* Return code to initialize DST with a copy constructor from SRC.
   C doesn't have copy constructors nor assignment operators, only for
   _Atomic vars we need to perform __atomic_load from src into a temporary
   followed by __atomic_store of the temporary to dst.  */

درخت
c_omp_clause_copy_ctor (درخت clause, درخت dst, درخت src)
{
  اگر (!really_atomic_lvalue (dst) && !really_atomic_lvalue (src))
    واپس build2 (MODIFY_اظہاریہ, درخت_TYPE (dst), dst, src);

  location_t loc = OMP_CLAUSE_LOCATION (clause);
  درخت type = درخت_TYPE (dst);
  درخت nonatomic_type = build_qualified_type (type, TYPE_UNQUALIFIED);
  درخت tmp = create_tmp_var (nonatomic_type);
  درخت tmp_addr = build_fold_addr_اظہاریہ (tmp);
  درخت_ADDRESSABLE (tmp) = 1;
  suppress_warning (tmp);
  درخت src_addr = build_fold_addr_اظہاریہ (src);
  درخت dst_addr = build_fold_addr_اظہاریہ (dst);
  درخت seq_cst = build_int_cst (integer_type_گرہ, MEMMODEL_SEQ_CST);
  vec<درخت, va_gc> *params;
  /* Expansion of a generic atomic load may require an addition
     element, so allocate enough to prevent a resize.  */
  vec_alloc (params, 4);

  /* Build __atomic_load (&src, &tmp, SEQ_CST);  */
  درخت fndecl = builtin_decl_explicit (BUILT_اندر_ATOMIC_بھرو);
  params->تیز_ڈالو (src_addr);
  params->تیز_ڈالو (tmp_addr);
  params->تیز_ڈالو (seq_cst);
  درخت بھرو = c_build_function_call_vec (loc, vNULL, fndecl, params, تہی);

  vec_alloc (params, 4);

  /* Build __atomic_store (&dst, &tmp, SEQ_CST);  */
  fndecl = builtin_decl_explicit (BUILT_اندر_ATOMIC_STORE);
  params->تیز_ڈالو (dst_addr);
  params->تیز_ڈالو (tmp_addr);
  params->تیز_ڈالو (seq_cst);
  درخت store = c_build_function_call_vec (loc, vNULL, fndecl, params, تہی);
  واپس build2 (COMPOUND_اظہاریہ, void_type_گرہ, بھرو, store);
}

/* Create a transaction node.  */

درخت
c_اختتام_transaction (location_t loc, درخت بلاک, صحیح flags)
{
  درخت stmt = build_stmt (loc, TRANSACTION_اظہاریہ, بلاک);
  اگر (flags & TM_STMT_ATTR_OUTER)
    TRANSACTION_اظہاریہ_OUTER (stmt) = 1;
  اگر (flags & TM_STMT_ATTR_RELAXED)
    TRANSACTION_اظہاریہ_RELAXED (stmt) = 1;
  واپس جوڑو_stmt (stmt);
}

/* Make a variant type in the proper way for C/C++, propagating qualifiers
   down to the element type of an array.  If ORIG_QUAL_TYPE is not
   NULL, then it should be used as the qualified type
   ORIG_QUAL_INDIRECT levels down in array type derivation (to
   preserve information about the typedef name from which an array
   type was derived).  */

درخت
c_build_qualified_type (درخت type, صحیح type_quals, درخت orig_qual_type,
			سائز_t orig_qual_بالواسطہ)
{
  اگر (type == error_mark_گرہ)
    واپس type;

  اگر (درخت_رمز (type) == ARRAY_TYPE)
    {
      درخت t;
      درخت element_type = c_build_qualified_type (درخت_TYPE (type),
						  type_quals, orig_qual_type,
						  orig_qual_بالواسطہ - 1);

      /* See if we already have an identically qualified type.  */
      اگر (orig_qual_type && orig_qual_بالواسطہ == 0)
	t = orig_qual_type;
      ورنہ
	برائے (t = TYPE_MAIN_VARIANT (type); t; t = TYPE_اگلا_VARIANT (t))
	  {
	    اگر (TYPE_QUALS (strip_array_types (t)) == type_quals
		&& TYPE_NAME (t) == TYPE_NAME (type)
		&& TYPE_CONTEXT (t) == TYPE_CONTEXT (type)
		&& attribute_list_equal (TYPE_اوصاف (t),
					 TYPE_اوصاف (type)))
	      توڑو;
	  }
      اگر (!t)
	{
          درخت domain = TYPE_DOMAIN (type);

	  t = build_variant_type_copy (type);
	  درخت_TYPE (t) = element_type;
	  TYPE_ADDR_SPACE (t) = TYPE_ADDR_SPACE (element_type);

          اگر (TYPE_STRUCTURAL_EQUALITY_P (element_type)
              || (domain && TYPE_STRUCTURAL_EQUALITY_P (domain)))
            سیٹ_TYPE_STRUCTURAL_EQUALITY (t);
          ورنہ اگر (TYPE_CANONICAL (element_type) != element_type
                   || (domain && TYPE_CANONICAL (domain) != domain))
            {
              درخت unqualified_canon
		= c_build_array_type (TYPE_CANONICAL (element_type),
				      domain ? TYPE_CANONICAL (domain)
					     : NULL_درخت);
              اگر (TYPE_الٹ_STORAGE_ترتیب (type))
                {
                  unqualified_canon
		    = build_distinct_type_copy (unqualified_canon);
                  TYPE_الٹ_STORAGE_ترتیب (unqualified_canon) = 1;
                }
              TYPE_CANONICAL (t)
		= c_build_qualified_type (unqualified_canon, type_quals);
            }
          ورنہ
            TYPE_CANONICAL (t) = t;
	}
      واپس t;
    }

  /* A restrict-qualified pointer type must be a pointer to object or
     incomplete type.  Note that the use of POINTER_TYPE_P also allows
     REFERENCE_TYPEs, which is appropriate for C++.  */
  اگر ((type_quals & TYPE_QUAL_RESTRICT)
      && (!اشارہ_گر_TYPE_P (type)
	  || !C_TYPE_OBJECT_OR_INCOMPLETE_P (درخت_TYPE (type))))
    {
      error ("invalid use of %<restrict%>");
      type_quals &= ~TYPE_QUAL_RESTRICT;
    }

  درخت var_type = (orig_qual_type && orig_qual_بالواسطہ == 0
		   ? orig_qual_type
		   : build_qualified_type (type, type_quals));

  gcc_checking_assert (C_TYPE_VARIABLE_سائز (var_type)
		       == C_TYPE_VARIABLE_سائز (type));
  gcc_checking_assert (c_type_variably_modified_p (var_type)
		       == c_type_variably_modified_p (type));

  /* A variant type does not inherit the list of incomplete vars from the
     type main variant.  */
  اگر ((ریکارڈ_OR_UNION_TYPE_P (var_type)
       || درخت_رمز (var_type) == ENUMERAL_TYPE)
      && TYPE_MAIN_VARIANT (var_type) != var_type)
    C_TYPE_INCOMPLETE_VARS (var_type) = 0;
  واپس var_type;
}

/* Build a VA_ARG_EXPR for the C parser.  */

درخت
c_build_va_arg (location_t loc1, درخت اظہاریہ, location_t loc2, درخت type,
		درخت type_اظہاریہ)
{
  اگر (error_عملیہ_p (type))
    واپس error_mark_گرہ;
  /* VA_ARG_EXPR cannot be used for a scalar va_list with reverse storage
     order because it takes the address of the expression.  */
  ورنہ اگر (handled_component_p (اظہاریہ)
	   && الٹ_storage_ترتیب_for_component_p (اظہاریہ))
    {
      error_at (loc1, "cannot use %<va_arg%> with reverse storage order");
      واپس error_mark_گرہ;
    }
  ورنہ اگر (!COMPLETE_TYPE_P (type))
    {
      error_at (loc2, "second argument to %<va_arg%> is of incomplete "
		"type %qT", type);
      واپس error_mark_گرہ;
    }
  ورنہ اگر (درخت_رمز (type) == FUNCTION_TYPE)
    {
      error_at (loc2, "second argument to %<va_arg%> is a function type %qT",
		type);
      واپس error_mark_گرہ;
    }
  ورنہ اگر (درخت_رمز (type) == ARRAY_TYPE && C_TYPE_VARIABLE_سائز (type)
	   && !flag_isoc99)
    {
      error_at (loc2, "second argument to %<va_arg%> is an array type %qT",
		type);
      واپس error_mark_گرہ;
    }
  ورنہ اگر (warn_cxx_compat && درخت_رمز (type) == ENUMERAL_TYPE)
    warning_at (loc2, OPT_Wc___compat,
		"C++ requires promoted type, not enum type, in %<va_arg%>");

  اگر (flag_isoc99 && درخت_رمز (type) == ARRAY_TYPE)
    {
      warning_at (loc2, 0, "second argument to %<va_arg%> is an array type %qT",
		  type);
      /* We create a trap but evaluate side effects first.  */
      درخت trapfn = builtin_decl_explicit (BUILT_اندر_TRAP);
      trapfn = build_call_اظہاریہ_loc (loc2, trapfn, 0);
      درخت e2 = build2 (COMPOUND_اظہاریہ, void_type_گرہ, اظہاریہ, trapfn);
      /* Return a compound literal of the right type.  */
      درخت e1 = build_compound_literal (loc2, type, تہی, سچ, 0, تہی);
      اظہاریہ = build2 (COMPOUND_اظہاریہ, type, e2, e1);
    }
  ورنہ
    اظہاریہ = build_va_arg (loc2, اظہاریہ, type);

  اگر (type_اظہاریہ)
    اظہاریہ = build2 (COMPOUND_اظہاریہ, درخت_TYPE (اظہاریہ), type_اظہاریہ, اظہاریہ);

  واپس اظہاریہ;
}

/* Return truthvalue of whether T1 is the same tree structure as T2.
   Return 1 if they are the same. Return false if they are different.  */

منطقی
c_درخت_equal (درخت t1, درخت t2)
{
  شمار درخت_رمز_2 code1, code2;

  اگر (t1 == t2)
    واپس سچ;
  اگر (!t1 || !t2)
    واپس جھوٹ;

  برائے (code1 = درخت_رمز (t1); code1 == NON_LVALUE_اظہاریہ;
       code1 = درخت_رمز (t1))
    t1 = درخت_عملیہ (t1, 0);
  برائے (code2 = درخت_رمز (t2); code2 == NON_LVALUE_اظہاریہ;
       code2 = درخت_رمز (t2))
    t2 = درخت_عملیہ (t2, 0);

  /* They might have become equal now.  */
  اگر (t1 == t2)
    واپس سچ;

  اگر (code1 != code2)
    واپس جھوٹ;

  اگر (CONSTANT_CLASS_P (t1) && !comptypes (درخت_TYPE (t1), درخت_TYPE (t2)))
    واپس جھوٹ;

  انتخاب (code1)
    {
    حالت INTEGER_CST:
      واپس wi::مقصد_wide (t1) == wi::مقصد_wide (t2);

    حالت REAL_CST:
      واپس real_equal (&درخت_REAL_CST (t1), &درخت_REAL_CST (t2));

    حالت STRING_CST:
      واپس درخت_STRING_لمبائی (t1) == درخت_STRING_لمبائی (t2)
	&& !memcmp (درخت_STRING_اشارہ_گر (t1), درخت_STRING_اشارہ_گر (t2),
		    درخت_STRING_لمبائی (t1));

    حالت FIXED_CST:
      واپس FIXED_اقدار_IDENTICAL (درخت_FIXED_CST (t1),
				     درخت_FIXED_CST (t2));

    حالت COMPLEX_CST:
      واپس c_درخت_equal (درخت_REALPART (t1), درخت_REALPART (t2))
	     && c_درخت_equal (درخت_IMAGPART (t1), درخت_IMAGPART (t2));

    حالت سمتیہ_CST:
      واپس عملیہ_equal_p (t1, t2, OEP_ONLY_CONST);

    حالت CONSTRUCTOR:
      /* We need to do this when determining whether or not two
	 non-type pointer to member function template arguments
	 are the same.  */
      اگر (!comptypes (درخت_TYPE (t1), درخت_TYPE (t2))
	  || CONSTRUCTOR_NELTS (t1) != CONSTRUCTOR_NELTS (t2))
	واپس جھوٹ;
      {
	درخت میدان_2, قدر;
	غیرعلامتی صحیح i;
	FOR_EACH_CONSTRUCTOR_ELT (CONSTRUCTOR_ELTS (t1), i, میدان_2, قدر)
	  {
	    constructor_elt *elt2 = CONSTRUCTOR_ELT (t2, i);
	    اگر (!c_درخت_equal (میدان_2, elt2->اشاریہ)
		|| !c_درخت_equal (قدر, elt2->قدر))
	      واپس جھوٹ;
	  }
      }
      واپس سچ;

    حالت درخت_LIST:
      اگر (!c_درخت_equal (درخت_PURPOSE (t1), درخت_PURPOSE (t2)))
	واپس جھوٹ;
      اگر (!c_درخت_equal (درخت_قدر (t1), درخت_قدر (t2)))
	واپس جھوٹ;
      واپس c_درخت_equal (درخت_CHAIN (t1), درخت_CHAIN (t2));

    حالت SAVE_اظہاریہ:
      واپس c_درخت_equal (درخت_عملیہ (t1, 0), درخت_عملیہ (t2, 0));

    حالت CALL_اظہاریہ:
      {
	درخت arg1, arg2;
	call_اظہاریہ_arg_iterator iter1, iter2;
	اگر (!c_درخت_equal (CALL_اظہاریہ_FN (t1), CALL_اظہاریہ_FN (t2)))
	  واپس جھوٹ;
	برائے (arg1 = پہلا_call_اظہاریہ_arg (t1, &iter1),
	       arg2 = پہلا_call_اظہاریہ_arg (t2, &iter2);
	     arg1 && arg2;
	     arg1 = اگلا_call_اظہاریہ_arg (&iter1),
	       arg2 = اگلا_call_اظہاریہ_arg (&iter2))
	  اگر (!c_درخت_equal (arg1, arg2))
	    واپس جھوٹ;
	اگر (arg1 || arg2)
	  واپس جھوٹ;
	واپس سچ;
      }

    حالت ہدف_اظہاریہ:
      {
	درخت o1 = درخت_عملیہ (t1, 0);
	درخت o2 = درخت_عملیہ (t2, 0);

	/* Special case: if either target is an unallocated VAR_DECL,
	   it means that it's going to be unified with whatever the
	   TARGET_EXPR is really supposed to initialize, so treat it
	   as being equivalent to anything.  */
	اگر (VAR_P (o1) && DECL_NAME (o1) == NULL_درخت
	    && !DECL_RTL_سیٹ_P (o1))
	  /*Nop*/;
	ورنہ اگر (VAR_P (o2) && DECL_NAME (o2) == NULL_درخت
		 && !DECL_RTL_سیٹ_P (o2))
	  /*Nop*/;
	ورنہ اگر (!c_درخت_equal (o1, o2))
	  واپس جھوٹ;

	واپس c_درخت_equal (درخت_عملیہ (t1, 1), درخت_عملیہ (t2, 1));
      }

    حالت COMPONENT_REF:
      اگر (درخت_عملیہ (t1, 1) != درخت_عملیہ (t2, 1))
	واپس جھوٹ;
      واپس c_درخت_equal (درخت_عملیہ (t1, 0), درخت_عملیہ (t2, 0));

    حالت PARM_DECL:
    حالت VAR_DECL:
    حالت CONST_DECL:
    حالت میدان_DECL:
    حالت FUNCTION_DECL:
    حالت IDENTIFIER_گرہ:
    حالت SSA_NAME:
      واپس جھوٹ;

    حالت درخت_VEC:
      {
	غیرعلامتی ix;
	اگر (درخت_VEC_لمبائی (t1) != درخت_VEC_لمبائی (t2))
	  واپس جھوٹ;
	برائے (ix = درخت_VEC_لمبائی (t1); ix--;)
	  اگر (!c_درخت_equal (درخت_VEC_ELT (t1, ix),
			     درخت_VEC_ELT (t2, ix)))
	    واپس جھوٹ;
	واپس سچ;
      }

    CASE_CONVERT:
      اگر (!comptypes (درخت_TYPE (t1), درخت_TYPE (t2)))
	واپس جھوٹ;
      توڑو;

    طےشدہ:
      توڑو;
    }

  انتخاب (درخت_رمز_CLASS (code1))
    {
    حالت tcc_unary:
    حالت tcc_ثنائی:
    حالت tcc_comparison:
    حالت tcc_عبارت:
    حالت tcc_vl_exp:
    حالت tcc_reference:
    حالت tcc_statement:
      {
	صحیح i, n = درخت_عملیہ_لمبائی (t1);

	انتخاب (code1)
	  {
	  حالت PREINCREMENT_اظہاریہ:
	  حالت PREDECREMENT_اظہاریہ:
	  حالت POSTINCREMENT_اظہاریہ:
	  حالت POSTDECREMENT_اظہاریہ:
	    n = 1;
	    توڑو;
	  حالت ARRAY_REF:
	    n = 2;
	    توڑو;
	  طےشدہ:
	    توڑو;
	  }

	اگر (درخت_رمز_CLASS (code1) == tcc_vl_exp
	    && n != درخت_عملیہ_لمبائی (t2))
	  واپس جھوٹ;

	برائے (i = 0; i < n; ++i)
	  اگر (!c_درخت_equal (درخت_عملیہ (t1, i), درخت_عملیہ (t2, i)))
	    واپس جھوٹ;

	واپس سچ;
      }

    حالت tcc_type:
      واپس comptypes (t1, t2);
    طےشدہ:
      gcc_unreachable ();
    }
}

/* Returns true when the function declaration FNDECL is implicit,
   introduced as a result of a call to an otherwise undeclared
   function, and false otherwise.  */

منطقی
c_decl_implicit (const_درخت fndecl)
{
  واپس C_DECL_IMPLICIT (fndecl);
}
