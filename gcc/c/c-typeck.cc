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

#ضمن "config.h"
#ضمن "system.h"
#ضمن "coretypes.h"
#ضمن "memmodel.h"
#ضمن "target.h"
#ضمن "function.h"
#ضمن "bitmap.h"
#ضمن "c-tree.h"
#ضمن "gimple-expr.h"
#ضمن "predict.h"
#ضمن "stor-layout.h"
#ضمن "trans-mem.h"
#ضمن "varasm.h"
#ضمن "stmt.h"
#ضمن "langhooks.h"
#ضمن "c-lang.h"
#ضمن "intl.h"
#ضمن "tree-iterator.h"
#ضمن "gimplify.h"
#ضمن "tree-inline.h"
#ضمن "omp-general.h"
#ضمن "c-family/c-objc.h"
#ضمن "c-family/c-ubsan.h"
#ضمن "gomp-constants.h"
#ضمن "spellcheck-tree.h"
#ضمن "c-family/c-type-mismatch.h"
#ضمن "stringpool.h"
#ضمن "attribs.h"
#ضمن "asan.h"
#ضمن "realmpfr.h"
#ضمن "tree-pretty-print-markup.h"
#ضمن "gcc-urlifier.h"

/* Possible cases of implicit conversions.  Used to select diagnostic messages
   and control folding initializers in convert_for_assignment.  */
تعداد impl_conv {
  ic_argpass,
  ic_تخصیص_بده,
  ic_init,
  ic_init_const,
  ic_return
};

/* The level of nesting inside "__alignof__".  */
صحيح درون_alignof;

/* The level of nesting inside "sizeof".  */
صحيح درون_sizeof;

/* The level of nesting inside "countof".  */
صحيح درون_countof;

/* The level of nesting inside "typeof".  */
صحيح درون_typeof;

/* The level of nesting inside "_Generic".  */
صحيح درون_generic;

/* True when parsing OpenMP loop expressions.  */
منطقي c_درون_omp_for;

/* True when parsing OpenMP map clause.  */
منطقي c_omp_array_section_p;

/* The argument of last parsed sizeof expression, only to be tested
   if expr.original_code == SIZEOF_EXPR.  */
درخت c_آخرین_sizeof_arg;
location_t c_آخرین_sizeof_loc;

/* Nonzero if we might need to print a "missing braces around
   initializer" message within this initializer.  */
ساكن صحيح یافت_missing_braces;

ساكن منطقي require_constant_مقدار;
ساكن منطقي require_constant_elements;
ساكن منطقي require_constexpr_مقدار;

ساكن درخت qualify_type (درخت, درخت);
بنية comptypes_داده;
ساكن منطقي tagged_types_tu_compatible_p (const_درخت, const_درخت,
					  بنية comptypes_داده *);
ساكن منطقي comp_هدف_types (location_t, درخت, درخت);
ساكن منطقي function_types_compatible_p (const_درخت, const_درخت,
					 بنية comptypes_داده *);
ساكن منطقي type_lists_compatible_p (const_درخت, const_درخت,
				     بنية comptypes_داده *);
ساكن صحيح convert_arguments (location_t, vec<location_t>, درخت,
			      vec<درخت, va_gc> *, vec<درخت, va_gc> *, درخت,
			      درخت);
ساكن درخت اشاره_گر_diff (location_t, درخت, درخت, درخت *);
ساكن درخت convert_for_assignment (location_t, location_t, درخت, درخت, درخت,
				    تعداد impl_conv, منطقي, درخت, درخت, صحيح,
				    صحيح = 0);
ساكن درخت valid_compound_عبارت_initializer (درخت, درخت);
ساكن فراغ افزودن_string (ثابت حرف *);
ساكن فراغ افزودن_member_name (درخت);
ساكن صحيح spelling_درازی (فراغ);
ساكن حرف *print_spelling (حرف *);
ساكن فراغ warning_init (location_t, صحيح, ثابت حرف *);
ساكن درخت digest_init (location_t, درخت, درخت, درخت, درخت, منطقي, منطقي, منطقي,
			 منطقي, منطقي, منطقي);
ساكن فراغ output_init_element (location_t, درخت, درخت, منطقي, درخت, درخت, منطقي,
				 منطقي, بنية obstack *);
ساكن فراغ output_pending_init_elements (صحيح, بنية obstack *);
ساكن منطقي مجموعه_designator (location_t, منطقي, بنية obstack *);
ساكن فراغ افزودن_range_پشته (درخت, بنية obstack *);
ساكن فراغ جمع_کن_pending_init (location_t, درخت, درخت, درخت, منطقي,
			      بنية obstack *);
ساكن فراغ مجموعه_nonincremental_init (بنية obstack *);
ساكن فراغ مجموعه_nonincremental_init_from_string (درخت, بنية obstack *);
ساكن درخت پیدا_کن_init_member (درخت, بنية obstack *);
ساكن فراغ readonly_warning (درخت, تعداد lvalue_use);
ساكن صحيح lvalue_or_else (location_t, const_درخت, تعداد lvalue_use);
ساكن فراغ رکورد_maybe_استفاده_شده_decl (درخت, منطقي آدرس);
ساكن منطقي comptypes_داخلی (const_درخت, const_درخت,
				بنية comptypes_داده *داده);
ساكن منطقي comptypes_check_for_مرکب (درخت t1, درخت t2);
ساكن منطقي handle_counted_by_p (درخت);
ساكن منطقي بالاترین_array_vla_p (const_درخت type);


/* Return true if EXP is a null pointer constant, false otherwise.  */

منطقي
null_اشاره_گر_constant_p (const_درخت عبارت)
{
  /* This should really operate on c_expr structures, but they aren't
     yet available everywhere required.  */
  درخت type = درخت_TYPE (عبارت);

  /* An integer constant expression with the value 0, such an expression
     cast to type void*, or the predefined constant nullptr, are a null
     pointer constant.  */
  إذا (عبارت == nullptr_گره)
    أرجع درست;

  أرجع (درخت_کد (عبارت) == INTEGER_CST
	  && !درخت_سرریز (عبارت)
	  && integer_zerop (عبارت)
	  && (INTEGRAL_TYPE_P (type)
	      || (درخت_کد (type) == اشاره_گر_TYPE
		  && VOID_TYPE_P (درخت_TYPE (type))
		  && TYPE_QUALS (درخت_TYPE (type)) == TYPE_UNQUALIFIED)));
}

/* EXPR may appear in an unevaluated part of an integer constant
   expression, but not in an evaluated part.  Wrap it in a
   C_MAYBE_CONST_EXPR, or mark it with TREE_OVERFLOW if it is just an
   INTEGER_CST and we cannot create a C_MAYBE_CONST_EXPR.  */

ساكن درخت
note_integer_operands (درخت عبارت)
{
  درخت ret;
  إذا (درخت_کد (عبارت) == INTEGER_CST && درون_late_دودویی_op)
    {
      ret = copy_گره (عبارت);
      درخت_سرریز (ret) = 1;
    }
  وإلا
    {
      ret = build2 (C_MAYBE_CONST_عبارت, درخت_TYPE (عبارت), NULL_درخت, عبارت);
      C_MAYBE_CONST_عبارت_INT_OPERANDS (ret) = 1;
    }
  أرجع ret;
}

/* Having checked whether EXPR may appear in an unevaluated part of an
   integer constant expression and found that it may, remove any
   C_MAYBE_CONST_EXPR noting this fact and return the resulting
   expression.  */

ساكن مضمن درخت
remove_c_maybe_const_عبارت (درخت عبارت)
{
  إذا (درخت_کد (عبارت) == C_MAYBE_CONST_عبارت)
    أرجع C_MAYBE_CONST_عبارت_عبارت (عبارت);
  وإلا
    أرجع عبارت;
}

/* This is a cache to hold if two types are seen.  */

بنية tagged_tu_دیده_cache {
  ثابت بنية tagged_tu_دیده_cache * بعدی;
  const_درخت t1;
  const_درخت t2;
};

/* Do `exp = require_complete_type (loc, exp);' to make sure exp
   does not have an incomplete type.  (That includes void types.)
   LOC is the location of the use.  */

درخت
require_complete_type (location_t loc, درخت مقدار)
{
  درخت type = درخت_TYPE (مقدار);

  إذا (error_عملوند_p (مقدار))
    أرجع error_mark_گره;

  /* First, detect a valid value with a complete type.  */
  إذا (COMPLETE_TYPE_P (type))
    أرجع مقدار;

  c_incomplete_type_error (loc, مقدار, type);
  أرجع error_mark_گره;
}

/* Print an error message for invalid use of an incomplete type.
   VALUE is the expression that was used (or 0 if that isn't known)
   and TYPE is the type that was invalid.  LOC is the location for
   the error.  */

فراغ
c_incomplete_type_error (location_t loc, const_درخت مقدار, const_درخت type)
{
  /* Avoid duplicate error message.  */
  إذا (درخت_کد (type) == ERROR_MARK)
    أرجع;

  إذا (مقدار != NULL_درخت && (VAR_P (مقدار) || درخت_کد (مقدار) == PARM_DECL))
    error_at (loc, "%qD has an incomplete type %qT", مقدار, type);
  وإلا
    {
    retry:
      /* We must print an error message.  Be clever about what it says.  */

      بدل (درخت_کد (type))
	{
	حالة رکورد_TYPE:
	حالة UNION_TYPE:
	حالة ENUMERAL_TYPE:
	  اكسر;

	حالة VOID_TYPE:
	  error_at (loc, "invalid use of void expression");
	  أرجع;

	حالة ARRAY_TYPE:
	  إذا (TYPE_DOMAIN (type))
	    {
	      إذا (flexible_array_member_type_p (type))
		{
		  error_at (loc, "invalid use of flexible array member");
		  أرجع;
		}
	      type = درخت_TYPE (type);
	      اذهب retry;
	    }
	  error_at (loc, "invalid use of array with unspecified bounds");
	  أرجع;

	افتراضي:
	  gcc_unreachable ();
	}

      إذا (درخت_کد (TYPE_NAME (type)) == IDENTIFIER_گره)
	error_at (loc, "invalid use of undefined type %qT", type);
      وإلا
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

  إذا (TYPE_MAIN_VARIANT (type) == float_type_گره)
    ret = double_type_گره;
  وإلا إذا (c_promoting_integer_type_p (type))
    {
      /* Preserve unsignedness if not really getting any wider.  */
      إذا (TYPE_UNSIGNED (type)
	  && (TYPE_PRECISION (type) == TYPE_PRECISION (integer_type_گره)))
	ret = unsigned_type_گره;
      وإلا
	ret = integer_type_گره;
    }

  إذا (ret != NULL_درخت)
    أرجع (TYPE_ATOMIC (type)
	    ? c_build_qualified_type (ret, TYPE_QUAL_ATOMIC)
	    : ret);

  أرجع type;
}

/* Return true if between two named address spaces, whether there is a superset
   named address space that encompasses both address spaces.  If there is a
   superset, return which address space is the superset.  */

ساكن منطقي
addr_space_superset (addr_space_t as1, addr_space_t as2, addr_space_t *common)
{
  إذا (as1 == as2)
    {
      *common = as1;
      أرجع درست;
    }
  وإلا إذا (targetm.addr_space.subset_p (as1, as2))
    {
      *common = as2;
      أرجع درست;
    }
  وإلا إذا (targetm.addr_space.subset_p (as2, as1))
    {
      *common = as1;
      أرجع درست;
    }
  وإلا
    أرجع خطأ;
}

/* Return a variant of TYPE which has all the type qualifiers of LIKE
   as well as those of TYPE.  */

ساكن درخت
qualify_type (درخت type, درخت like)
{
  addr_space_t as_type = TYPE_ADDR_SPACE (type);
  addr_space_t as_like = TYPE_ADDR_SPACE (like);
  addr_space_t as_common;

  /* If the two named address spaces are different, determine the common
     superset address space.  If there isn't one, raise an error.  */
  إذا (!addr_space_superset (as_type, as_like, &as_common))
    {
      as_common = as_type;
      error ("%qT and %qT are in disjoint named address spaces",
	     type, like);
    }

  أرجع c_build_qualified_type (type,
				 TYPE_QUALS_NO_ADDR_SPACE (type)
				 | TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (like)
				 | ENCODE_QUAL_ADDR_SPACE (as_common));
}


/* Check consistency of type TYPE.  For derived types, we test that
   C_TYPE_VARIABLE_SIZE and C_TYPE_VARIABLY_MODIFIED are consistent with
   the requirements of the base type.  We also check that arrays with a
   non-constant length are marked with C_TYPE_VARIABLE_SIZE. If any
   inconsistency is detected false is returned and true otherwise.  */

ساكن منطقي
c_verify_type (درخت type)
{
  بدل (درخت_کد (type))
    {
    حالة اشاره_گر_TYPE:
    حالة FUNCTION_TYPE:
    حالة ARRAY_TYPE:
      /* Pointer, array, functions are variably modified if and only if the
	 target, element, return type is variably modified.  */
      إذا (!TYPE_STRUCTURAL_EQUALITY_P (type)
	  && (C_TYPE_VARIABLY_MODIFIED (type)
	      != C_TYPE_VARIABLY_MODIFIED (درخت_TYPE (type))))
	أرجع خطأ;
      /* If the target type is structural equality, the type should also. */
      إذا (!TYPE_STRUCTURAL_EQUALITY_P (type)
	  && TYPE_STRUCTURAL_EQUALITY_P (درخت_TYPE (type)))
	أرجع خطأ;
    افتراضي:
       اكسر;
    }

  بدل (درخت_کد (type))
    {
    حالة اشاره_گر_TYPE:
    حالة FUNCTION_TYPE:
      /* Pointer and functions can not have variable size.  */
      إذا (C_TYPE_VARIABLE_اندازه (type))
	أرجع خطأ;
      اكسر;
    حالة ARRAY_TYPE:
      /* An array has variable size if and only if it has a non-constant
	 dimensions or its element type has variable size.  */
      إذا ((C_TYPE_VARIABLE_اندازه (درخت_TYPE (type))
	   || بالاترین_array_vla_p (type))
	  != C_TYPE_VARIABLE_اندازه (type))
	أرجع خطأ;
      /* If the element type or the array has variable size, then the
	 array has variable size and is variably modified.  */
      إذا (C_TYPE_VARIABLE_اندازه (درخت_TYPE (type))
	  || C_TYPE_VARIABLE_اندازه (type))
	{
	  إذا (!C_TYPE_VARIABLE_اندازه (type))
	    أرجع خطأ;
	  إذا (!C_TYPE_VARIABLY_MODIFIED (type))
	    أرجع خطأ;
	}

      /* va_list violates this, accept such types here.  */
      إذا (!COMPLETE_TYPE_P (درخت_TYPE (type)))
	أرجع درست;

      إذا (COMPLETE_TYPE_P (type))
	{
	  /* If the size is unknown, it can not be complete.  */
	  إذا (NULL_درخت == TYPE_DOMAIN (type))
	    أرجع خطأ;

	  /* Zero-length arrays must have size zero.  */
	  إذا (zero_درازی_array_type_p (type)
	      && !integer_zerop (TYPE_اندازه (type)))
	    أرجع خطأ;
	}
      وإلا
	{
	  /* If not complete but has a domain, it must be a FAM.  */
	  إذا (NULL_درخت != TYPE_DOMAIN (type)
	      && !flexible_array_member_type_p (type))
	    أرجع خطأ;
	}
    افتراضي:
      اكسر;
    }
  أرجع درست;
}

/* Propagate C_TYPE_VARIABLY_MODIFIED and C_TYPE_VARIABLE_SIZE
   from a base type to a newly built derived or qualified type.  */

ساكن درخت
c_مجموعه_type_بیتها (درخت new_type, درخت old_type)
{
  gcc_checking_assert (c_verify_type (old_type));

  إذا (c_type_variably_modified_p (old_type))
    C_TYPE_VARIABLY_MODIFIED (new_type) = درست;

  إذا (درخت_کد (new_type) == ARRAY_TYPE && C_TYPE_VARIABLE_اندازه (old_type))
    {
      C_TYPE_VARIABLY_MODIFIED (new_type) = درست;
      C_TYPE_VARIABLE_اندازه (new_type) = درست;
    }
  أرجع new_type;
}

/* Build a pointer type using the default pointer mode.  */

درخت
c_build_اشاره_گر_type (درخت مقصد_type)
{
  addr_space_t as = مقصد_type == error_mark_گره ? ADDR_SPACE_GENERIC
					       : TYPE_ADDR_SPACE (مقصد_type);
  machine_نما اشاره_گر_نما;

  إذا (as != ADDR_SPACE_GENERIC || c_default_اشاره_گر_نما == VOIDmode)
    اشاره_گر_نما = targetm.addr_space.اشاره_گر_نما (as);
  وإلا
    اشاره_گر_نما = c_default_اشاره_گر_نما;

  أرجع c_build_اشاره_گر_type_for_نما (مقصد_type, اشاره_گر_نما, خطأ);
}

/* Build a pointer type using the given mode.  */

درخت
c_build_اشاره_گر_type_for_نما (درخت type, machine_نما نما, منطقي m)
{
  درخت ret = build_اشاره_گر_type_for_نما (type, نما, m);
  أرجع c_مجموعه_type_بیتها (ret, type);
}

/* Build a function type.  */

درخت
c_build_function_type (درخت type, درخت آرگومانها, منطقي no)
{
  درخت ret = build_function_type (type, آرگومانها, no);
  أرجع c_مجموعه_type_بیتها (ret, type);
}

/* Build an array type.  This sets typeless storage as required
   by C2Y and C_TYPE_VARIABLY_MODIFIED and C_TYPE_VARIABLE_SIZE
   based on the element type and domain.  */

درخت
c_build_array_type (درخت type, درخت domain)
{
  صحيح type_quals = TYPE_QUALS (type);

  /* Identify typeless storage as introduced in C2Y
     and supported also in earlier language modes.  */
  منطقي typeless = (char_type_p (type) && !(type_quals & TYPE_QUAL_ATOMIC))
		  || (AGGREGATE_TYPE_P (type) && TYPE_TYPELESS_STORAGE (type));

  درخت ret = build_array_type (type, domain, typeless);

  إذا (بالاترین_array_vla_p (ret))
    {
      C_TYPE_VARIABLE_اندازه (ret) = 1;
      C_TYPE_VARIABLY_MODIFIED (ret) = 1;
    }

  أرجع c_مجموعه_type_بیتها (ret, type);
}

/* Build an array type of unspecified size.  */
درخت
c_build_array_type_unspecified (درخت type)
{
  درخت فوقانی = build2 (COMPOUND_عبارت, درخت_TYPE (اندازه_zero_گره),
		       integer_zero_گره, اندازه_zero_گره);
  أرجع c_build_array_type (type, build_شاخص_type (فوقانی));
}

/* Build an array type of zero size.  */
درخت
c_build_array_type_zero_اندازه (درخت type)
{
  /* The GCC extension for zero-length arrays differs from
     ISO flexible array members in that sizeof yields
     zero.  */
  type = c_build_array_type (type, build_شاخص_type (NULL_درخت));
  type = build_distinct_type_copy (TYPE_MAIN_VARIANT (type));
  TYPE_اندازه (type) = bitsize_zero_گره;
  TYPE_اندازه_UNIT (type) = اندازه_zero_گره;
  مجموعه_TYPE_STRUCTURAL_EQUALITY (type);
  أرجع type;
}

درخت
c_build_type_attribute_qual_variant (درخت type, درخت attrs, صحيح quals)
{
  درخت ret = build_type_attribute_qual_variant (type, attrs, quals);
  أرجع c_مجموعه_type_بیتها (ret, type);
}

درخت
c_build_type_attribute_variant (درخت type, درخت attrs)
{
  أرجع c_build_type_attribute_qual_variant (type, attrs, TYPE_QUALS (type));
}

/* Reconstruct a complex derived type.  This is used to re-construct types
   with the vector attribute.  It is called via a langhook.  */

درخت
c_reconstruct_complex_type (درخت type, درخت bottom)
{
  درخت inner, outer;

  إذا (درخت_کد (type) == اشاره_گر_TYPE)
    {
      inner = c_reconstruct_complex_type (درخت_TYPE (type), bottom);
      outer = c_build_اشاره_گر_type_for_نما (inner, TYPE_نما (type),
					     TYPE_REF_CAN_ALIAS_ALL (type));
    }
  وإلا إذا (درخت_کد (type) == ARRAY_TYPE)
    {
      منطقي rso = TYPE_معکوس_STORAGE_ترتیب (type);
      inner = c_reconstruct_complex_type (درخت_TYPE (type), bottom);
      outer = c_build_array_type (inner, TYPE_DOMAIN (type));
      إذا (rso)
	{
	  outer = build_distinct_type_copy (outer);
	  TYPE_معکوس_STORAGE_ترتیب (outer) = 1;
	}

      gcc_checking_assert (C_TYPE_VARIABLE_اندازه (type)
			   == C_TYPE_VARIABLE_اندازه (outer));
    }
  وإلا إذا (درخت_کد (type) == FUNCTION_TYPE)
    {
      inner = c_reconstruct_complex_type (درخت_TYPE (type), bottom);
      outer = c_build_function_type (inner, TYPE_ARG_TYPES (type),
				     TYPE_NO_NAMED_آرگومانها_STDARG_P (type));
    }
  وإلا إذا (درخت_کد (type) == REFERENCE_TYPE
	   || درخت_کد (type) == جابه_جایی_TYPE)
    gcc_unreachable ();
  وإلا
    أرجع bottom;

  أرجع c_build_type_attribute_qual_variant (outer, TYPE_صفات (type),
					      TYPE_QUALS (type));
}


/* Helper function for c_canonical_type.  Check whether FIELD
   contains a pointer to a structure or union with tag,
   possibly nested in other type derivations, and return the
   type of this nested structure or union.  */
ساكن درخت
ptr_مقصد_tagged_member (درخت فیلد_2)
{
  gcc_assert (فیلد_DECL == درخت_کد (فیلد_2));
  درخت type = درخت_TYPE (فیلد_2);
  منطقي ptr_دیده = خطأ;
  طالما (درخت_کد (type) == ARRAY_TYPE
	 || درخت_کد (type) == FUNCTION_TYPE
	 || درخت_کد (type) == اشاره_گر_TYPE)
    {
      إذا (درخت_کد (type) == اشاره_گر_TYPE)
	ptr_دیده = درست;
      type = درخت_TYPE (type);
    }

  إذا (ptr_دیده
      && رکورد_OR_UNION_TYPE_P (type)
      && NULL_درخت != c_type_برچسب (type))
    أرجع type;

  أرجع NULL_درخت;
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
  gcc_assert (رکورد_OR_UNION_TYPE_P (type));

  منطقي needs_mod = خطأ;
  لكل (درخت x = TYPE_FIELDS (type); x; x = DECL_CHAIN (x))
    {
      إذا (!ptr_مقصد_tagged_member (x))
	استمر;
      needs_mod = درست;
      اكسر;
    }
  إذا (!needs_mod)
    أرجع type;

  /* Construct new version with such members replaced.  */
  درخت n = build_distinct_type_copy (type);
  درخت *fields = &TYPE_FIELDS (n);
  لكل (درخت x = TYPE_FIELDS (type); x; x = DECL_CHAIN (x))
    {
      درخت f = copy_گره (x);
      إذا (درخت m = ptr_مقصد_tagged_member (x))
	{
	  درخت new_گره = make_گره (درخت_کد (m));
	  TYPE_NAME (new_گره) = TYPE_NAME (m);
	  مجموعه_TYPE_STRUCTURAL_EQUALITY (new_گره);
	  new_گره = qualify_type (new_گره, m);
	  درخت_TYPE (f) = c_reconstruct_complex_type (درخت_TYPE (x),
						      new_گره);
	}
      *fields = f;
      fields = &DECL_CHAIN (f);
    }
  TYPE_CANONICAL (n) = n;
  أرجع n;
}


/* If NTYPE is a type of a non-variadic function with a prototype
   and OTYPE is a type of a function without a prototype and ATTRS
   contains attribute format, diagnosess and removes it from ATTRS.
   Returns the result of build_type_attribute_variant of NTYPE and
   the (possibly) modified ATTRS.  */

ساكن درخت
c_build_functype_attribute_variant (درخت ntype, درخت otype, درخت attrs)
{
  إذا (!prototype_p (otype)
      && prototype_p (ntype)
      && lookup_attribute ("format", attrs))
    {
      warning_at (درون_داد_location, OPT_Wattributes,
		  "%qs attribute can only be applied to variadic functions",
		  "format");
      attrs = remove_attribute ("format", attrs);
    }
  أرجع c_build_type_attribute_variant (ntype, attrs);

}

/* Given a type which could be a typedef name, make sure to return the
   original type.  See set_underlying_type. */
ساكن const_درخت
c_type_original (const_درخت t)
{
  /* It may even be a typedef of a typedef...
     In the case of compiler-created builtin structs the TYPE_DECL
     may be a dummy, with no DECL_ORIGINAL_TYPE.  Don't fault.  */
  طالما (TYPE_NAME (t)
	 && درخت_کد (TYPE_NAME (t)) == TYPE_DECL
	 && DECL_ORIGINAL_TYPE (TYPE_NAME (t)))
    t = DECL_ORIGINAL_TYPE (TYPE_NAME (t));
  أرجع t;
}

/* Return the tag for a tagged type.  */
درخت
c_type_برچسب (const_درخت t)
{
  gcc_assert (رکورد_OR_UNION_TYPE_P (t) || درخت_کد (t) == ENUMERAL_TYPE);
  const_درخت orig = c_type_original (t);
  درخت name = TYPE_NAME (orig);
  إذا (!name)
    أرجع NULL_درخت;
  إذا (درخت_کد (name) == TYPE_DECL)
    {
      إذا (!DECL_NAME (name))
	أرجع NULL_درخت;
      name = DECL_NAME (name);
    }
  gcc_checking_assert (درخت_کد (name) == IDENTIFIER_گره);
  أرجع name;
}

/* Remove qualifiers but not atomic.  For arrays remove qualifiers
   on the element type but also do not remove atomic.  */
ساكن درخت
remove_qualifiers (درخت t)
{
  إذا (!t || t == error_mark_گره)
    أرجع t;
  أرجع TYPE_ATOMIC (strip_array_types (t))
	 ? c_build_qualified_type (TYPE_MAIN_VARIANT (t), TYPE_QUAL_ATOMIC)
	 : TYPE_MAIN_VARIANT (t);
}


/* Helper function for composite_type_internal.  Find a compatible type
   in a (transparent) union U compatible to T.  If found, return the
   type of the corresponding member.  Otherwise, return the union type U.  */
ساكن درخت
transparent_union_replacement (درخت u, درخت t)
{
  إذا (u == error_mark_گره || t == error_mark_گره
      || درخت_کد (u) != UNION_TYPE
      || !(TYPE_TRANSPARENT_AGGR (u) || TYPE_NAME (u) == NULL_درخت)
      || comptypes (u, t))
    أرجع u;

  لكل (درخت memb = TYPE_FIELDS (u); memb; memb = DECL_CHAIN (memb))
    {
      درخت m = remove_qualifiers (درخت_TYPE (memb));
      إذا (comptypes (m, t))
	{
	  pedwarn (درون_داد_location, OPT_Wpedantic,
		    "function types not truly compatible in ISO C");
	  أرجع m;
	}
    }

  أرجع u;
}



/* Return the composite type of two compatible types.

   We assume that comptypes has already been done and returned
   nonzero; if that isn't so, this may crash.  In particular, we
   assume that qualifiers match.  */

بنية مرکب_cache {
  درخت t1;
  درخت t2;
  درخت مرکب;
  بنية مرکب_cache* بعدی;
};

درخت
مرکب_type_داخلی (درخت t1, درخت t2, درخت cond,
			 بنية مرکب_cache* cache)
{
  تعداد درخت_کد_2 code1;
  تعداد درخت_کد_2 code2;
  درخت صفات;

  /* Save time if the two types are the same.  */

  إذا (t1 == t2) أرجع t1;

  /* If one type is nonsense, use the other.  */
  إذا (t1 == error_mark_گره)
    أرجع t2;
  إذا (t2 == error_mark_گره)
    أرجع t1;

  code1 = درخت_کد (t1);
  code2 = درخت_کد (t2);

  /* Merge the attributes.  */
  صفات = targetm.ادغام_type_صفات (t1, t2);

  /* If one is an enumerated type and the other is the compatible
     integer type, the composite type might be either of the two
     (DR#013 question 3).  For consistency, use the enumerated type as
     the composite type.  */

  إذا (code1 == ENUMERAL_TYPE
      && (code2 == INTEGER_TYPE
	  || code2 == BOOLEAN_TYPE))
    أرجع t1;
  إذا (code2 == ENUMERAL_TYPE
      && (code1 == INTEGER_TYPE
	  || code1 == BOOLEAN_TYPE))
    أرجع t2;

  gcc_assert (code1 == code2);

  بدل (code1)
    {
    حالة اشاره_گر_TYPE:
      /* For two pointers, do this recursively on the target type.  */
      {
	gcc_checking_assert (TYPE_QUALS (t1) == TYPE_QUALS (t2));
	درخت هدف = مرکب_type_داخلی (درخت_TYPE (t1), درخت_TYPE (t2),
					       cond, cache);
	درخت n = c_build_اشاره_گر_type_for_نما (هدف, TYPE_نما (t1), خطأ);
	أرجع c_build_type_attribute_qual_variant (n, صفات,
						    TYPE_QUALS (t2));
      }

    حالة ARRAY_TYPE:
      {
	درخت d1 = TYPE_DOMAIN (t1);
	درخت d2 = TYPE_DOMAIN (t2);

	/* We should not have any type quals on arrays at all.  */
	gcc_assert (!TYPE_QUALS_NO_ADDR_SPACE (t1)
		    && !TYPE_QUALS_NO_ADDR_SPACE (t2));

	منطقي d1_zero = zero_درازی_array_type_p (t1)
		       || flexible_array_member_type_p (t1);
	منطقي d2_zero = zero_درازی_array_type_p (t2)
		       || flexible_array_member_type_p (t2);

	منطقي d1_variable = بالاترین_array_vla_p (t1);
	منطقي d2_variable = بالاترین_array_vla_p (t2);

	منطقي use1 = d1 && (d2_variable || !d2 || d2_zero || !d1_variable);
	منطقي use2 = d2 && (d1_variable || !d1 || d1_zero || !d2_variable);

	/* If the first is an unspecified size pick the other one.  */
	إذا (d2_variable && c_type_unspecified_p (t1))
	  {
	    gcc_assert (use1 && use2);
	    use1 = خطأ;
	  }

	/* If both are VLAs but not unspecified and we are in the
	   conditional operator, we create a conditional to select
	   the size of the active branch.  */
	منطقي use0 = cond && d1_variable && !c_type_unspecified_p (t1)
			 && d2_variable && !c_type_unspecified_p (t2);

	درخت td;
	درخت elt = مرکب_type_داخلی (درخت_TYPE (t1), درخت_TYPE (t2),
					    cond, cache);

	إذا (!use0)
	  {
	    /* Save space: see if the result is identical to one of the args.  */
	    إذا (elt == درخت_TYPE (t1) && use1)
	      أرجع c_build_type_attribute_variant (t1, صفات);
	    إذا (elt == درخت_TYPE (t2) && use2)
	      أرجع c_build_type_attribute_variant (t2, صفات);

	    إذا (elt == درخت_TYPE (t1) && !TYPE_DOMAIN (t2) && !TYPE_DOMAIN (t1))
	      أرجع c_build_type_attribute_variant (t1, صفات);
	    إذا (elt == درخت_TYPE (t2) && !TYPE_DOMAIN (t2) && !TYPE_DOMAIN (t1))
	      أرجع c_build_type_attribute_variant (t2, صفات);

	    td = TYPE_DOMAIN (use1 ? t1 : t2);
	  }
	وإلا
	  {
	    /* Not used in C.  */
	    gcc_assert (اندازه_zero_گره == TYPE_MIN_مقدار (d1));
	    gcc_assert (اندازه_zero_گره == TYPE_MIN_مقدار (d2));

	    درخت d = fold_build3_loc (UNKNOWN_LOCATION, COND_عبارت, sizetype,
				      cond, TYPE_MAX_مقدار (d1),
				      TYPE_MAX_مقدار (d2));

	    td = build_شاخص_type (d);
	  }

	/* Merge the element types, and have a size if either arg has
	   one.  We may have qualifiers on the element types.  To set
	   up TYPE_MAIN_VARIANT correctly, we need to form the
	   composite of the unqualified types and add the qualifiers
	   back at the end.  */
	صحيح quals = TYPE_QUALS (strip_array_types (elt));
	درخت unqual_elt = c_build_qualified_type (elt, TYPE_UNQUALIFIED);

	إذا ((!d1 || d1_zero) && (!d2 || d2_zero) && (d1 || d2))
	  t1 = c_build_array_type_zero_اندازه (unqual_elt);
	وإلا
	  t1 = c_build_array_type (unqual_elt, td);

	/* Check that a type which has a varying outermost dimension
	   got marked as having a variable size.  */
	منطقي varsize = (d1_variable && d2_variable)
		       || (d1_variable && !d2)
		       || (d2_variable && !d1);
	gcc_checking_assert (!varsize || C_TYPE_VARIABLE_اندازه (t1));

	t1 = c_build_qualified_type (t1, quals);
	أرجع c_build_type_attribute_variant (t1, صفات);
      }

    حالة رکورد_TYPE:
    حالة UNION_TYPE:
      إذا (flag_isoc23 && !comptypes_same_p (t1, t2))
	{
	  /* Go to the original type to get the right tag.  */
	  درخت برچسب = c_type_برچسب (t1);

	  gcc_checking_assert (COMPLETE_TYPE_P (t1) && COMPLETE_TYPE_P (t2));
	  gcc_checking_assert (!برچسب || comptypes (t1, t2));

	  /* If a composite type for these two types is already under
	     construction, return it.  */

	  لكل (بنية مرکب_cache *c = cache; c != عدم; c = c->بعدی)
	    إذا ((c->t1 == t1 && c->t2 == t2) || (c->t1 == t2 && c->t2 == t1))
	       أرجع c->مرکب;

	  /* Otherwise, create a new type node and link it into the cache.  */

	  درخت n = make_گره (code1);
	  مجموعه_TYPE_STRUCTURAL_EQUALITY (n);
	  TYPE_NAME (n) = برچسب;

	  بنية مرکب_cache cache2 = { t1, t2, n, cache };
	  cache = &cache2;

	  درخت f1 = TYPE_FIELDS (t1);
	  درخت f2 = TYPE_FIELDS (t2);
	  درخت fields = NULL_درخت;

	  لكل (درخت a = f1, b = f2; a && b;
	       a = DECL_CHAIN (a), b = DECL_CHAIN (b))
	    {
	      درخت ta = درخت_TYPE (a);
	      درخت tb = درخت_TYPE (b);

	      إذا (DECL_C_بیت_فیلد (a))
		{
		  ta = DECL_بیت_فیلد_TYPE (a);
		  tb = DECL_بیت_فیلد_TYPE (b);
		}

	      gcc_assert (DECL_NAME (a) == DECL_NAME (b));
	      gcc_checking_assert (!DECL_NAME (a) || comptypes (ta, tb));

	      درخت t = مرکب_type_داخلی (ta, tb, cond, cache);
	      درخت f = build_decl (درون_داد_location, فیلد_DECL, DECL_NAME (a), t);

	      DECL_PACKED (f) = DECL_PACKED (a);
	      مجموعه_DECL_ALIGN (f, DECL_ALIGN (a));
	      DECL_صفات (f) = DECL_صفات (a);
	      C_DECL_VARIABLE_اندازه (f) = C_TYPE_VARIABLE_اندازه (t);

	      decl_صفات (&f, DECL_صفات (f), 0);

	      پایان_decl (f, درون_داد_location, عدم, عدم, عدم);

	      إذا (DECL_C_بیت_فیلد (a))
		{
		  /* This will be processed by finish_struct.  */
		  مجموعه_DECL_C_بیت_فیلد (f);
		  DECL_INITIAL (f) = build_int_cst (integer_type_گره,
						    درخت_مقصد_uhwi (DECL_اندازه (a)));
		  DECL_NONADDRESSABLE_P (f) = درست;
		  DECL_PADDING_P (f) = !DECL_NAME (a);
		}

	      DECL_CHAIN (f) = fields;
	      fields = f;
	    }

	  fields = nreverse (fields);

	  /* Setup the struct/union type.  Because we inherit all variably
	     modified components, we can ignore the size expression.  */
	  درخت عبارت = NULL_درخت;

	  /* Set TYPE_STUB_DECL for debugging symbols.  */
	  TYPE_STUB_DECL (n) = pushdecl (build_decl (درون_داد_location, TYPE_DECL,
						     NULL_درخت, n));

	  n = پایان_struct (درون_داد_location, n, fields, صفات, عدم,
			     &عبارت);

	  أرجع qualify_type (n, t1);
	}
      /* FALLTHRU */
    حالة ENUMERAL_TYPE:
      إذا (صفات != عدم)
	{
	  /* Try harder not to create a new aggregate type.  */
	  إذا (attribute_list_equal (TYPE_صفات (t1), صفات))
	    أرجع t1;
	  إذا (attribute_list_equal (TYPE_صفات (t2), صفات))
	    أرجع t2;
	}
      أرجع c_build_type_attribute_variant (t1, صفات);

    حالة FUNCTION_TYPE:
      /* Function types: prefer the one that specified arg types.
	 If both do, merge the arg types.  Also merge the return types.  */
      {
	درخت valtype = مرکب_type_داخلی (درخت_TYPE (t1), درخت_TYPE (t2),
						cond, cache);
	درخت p1 = TYPE_ARG_TYPES (t1);
	درخت p2 = TYPE_ARG_TYPES (t2);

	/* Save space: see if the result is identical to one of the args.  */
	إذا (valtype == درخت_TYPE (t1) && !TYPE_ARG_TYPES (t2))
	  أرجع c_build_functype_attribute_variant (t1, t2, صفات);
	إذا (valtype == درخت_TYPE (t2) && !TYPE_ARG_TYPES (t1))
	  أرجع c_build_functype_attribute_variant (t2, t1, صفات);

	/* Simple way if one arg fails to specify argument types.  */
	إذا (TYPE_ARG_TYPES (t1) == NULL_درخت)
	  {
	    t1 = c_build_function_type (valtype, TYPE_ARG_TYPES (t2),
					TYPE_NO_NAMED_آرگومانها_STDARG_P (t2));
	    t1 = c_build_type_attribute_variant (t1, صفات);
	    أرجع qualify_type (t1, t2);
	 }
	إذا (TYPE_ARG_TYPES (t2) == NULL_درخت)
	  {
	    t1 = c_build_function_type (valtype, TYPE_ARG_TYPES (t1),
					TYPE_NO_NAMED_آرگومانها_STDARG_P (t1));
	    t1 = c_build_type_attribute_variant (t1, صفات);
	    أرجع qualify_type (t1, t2);
	  }

	/* If both args specify argument types, we must merge the two
	   lists, argument by argument.  */
	درخت newargs = NULL_درخت;
	درخت *endp = &newargs;

	لكل (; p1; p1 = درخت_CHAIN (p1), p2 = درخت_CHAIN (p2))
	  {
	    إذا (p1 == void_list_گره)
	      {
		*endp = void_list_گره;
		اكسر;
	      }
	    درخت mv1 = remove_qualifiers (درخت_مقدار (p1));
	    درخت mv2 = remove_qualifiers (درخت_مقدار (p2));

	    gcc_assert (mv1);
	    gcc_assert (mv2);

	    mv1 = transparent_union_replacement (mv1, mv2);
	    mv2 = transparent_union_replacement (mv2, mv1);

	    *endp = درخت_cons (NULL_درخت,
			       مرکب_type_داخلی (mv1, mv2, cond, cache),
			       NULL_درخت);

	    endp = &درخت_CHAIN (*endp);
	  }

	t1 = c_build_function_type (valtype, newargs);
	t1 = qualify_type (t1, t2);
      }
      /* FALLTHRU */

    افتراضي:
      أرجع c_build_type_attribute_variant (t1, صفات);
    }
}

درخت
مرکب_type_cond (درخت t1, درخت t2, درخت cond)
{
  gcc_checking_assert (comptypes_check_for_مرکب (t1, t2));

  بنية مرکب_cache cache = { };
  درخت n = مرکب_type_داخلی (t1, t2, cond, &cache);

  gcc_checking_assert (comptypes_check_for_مرکب (n, t1));
  gcc_checking_assert (comptypes_check_for_مرکب (n, t2));
  أرجع n;
}


درخت
مرکب_type (درخت t1, درخت t2)
{
  أرجع مرکب_type_cond (t1, t2, NULL_درخت);
}

/* Return the type of a conditional expression between pointers to
   possibly differently qualified versions of compatible types.

   We assume that comp_target_types has already been done and returned
   true; if that isn't so, this may crash.  */

ساكن درخت
common_اشاره_گر_type (درخت t1, درخت t2, درخت cond)
{
  درخت صفات;
  بیعلامت هدف_quals;
  addr_space_t as1, as2, as_common;
  صحيح quals1, quals2;

  /* Save time if the two types are the same.  */

  إذا (t1 == t2) أرجع t1;

  /* If one type is nonsense, use the other.  */
  إذا (t1 == error_mark_گره)
    أرجع t2;
  إذا (t2 == error_mark_گره)
    أرجع t1;

  gcc_assert (درخت_کد (t1) == اشاره_گر_TYPE
	      && درخت_کد (t2) == اشاره_گر_TYPE);

  /* Merge the attributes.  */
  صفات = targetm.ادغام_type_صفات (t1, t2);

  /* Find the composite type of the target types, and combine the
     qualifiers of the two types' targets.  */
  درخت pointed_مقصد_1 = درخت_TYPE (t1);
  درخت pointed_مقصد_2 = درخت_TYPE (t2);
  درخت هدف = مرکب_type_cond (TYPE_MAIN_VARIANT (pointed_مقصد_1),
				     TYPE_MAIN_VARIANT (pointed_مقصد_2), cond);

  /* Strip array types to get correct qualifier for pointers to arrays */
  quals1 = TYPE_QUALS_NO_ADDR_SPACE (strip_array_types (pointed_مقصد_1));
  quals2 = TYPE_QUALS_NO_ADDR_SPACE (strip_array_types (pointed_مقصد_2));

  /* For function types do not merge const qualifiers, but drop them
     if used inconsistently.  The middle-end uses these to mark const
     and noreturn functions.  */
  إذا (درخت_کد (pointed_مقصد_1) == FUNCTION_TYPE)
    هدف_quals = (quals1 & quals2);
  وإلا
    هدف_quals = (quals1 | quals2);

  /* If the two named address spaces are different, determine the common
     superset address space.  This is guaranteed to exist due to the
     assumption that comp_target_type returned true.  */
  as1 = TYPE_ADDR_SPACE (pointed_مقصد_1);
  as2 = TYPE_ADDR_SPACE (pointed_مقصد_2);
  إذا (!addr_space_superset (as1, as2, &as_common))
    gcc_unreachable ();

  هدف_quals |= ENCODE_QUAL_ADDR_SPACE (as_common);

  t1 = c_build_اشاره_گر_type (c_build_qualified_type (هدف, هدف_quals));
  أرجع c_build_type_attribute_variant (t1, صفات);
}

/* Return the common type for two arithmetic types under the usual
   arithmetic conversions.  The default conversions have already been
   applied, and enumerated types converted to their compatible integer
   types.  The resulting type is unqualified and has no attributes.

   This is the type for the result of most arithmetic operations
   if the operands have the given two types.  */

ساكن درخت
c_common_type (درخت t1, درخت t2)
{
  تعداد درخت_کد_2 code1;
  تعداد درخت_کد_2 code2;

  /* If one type is nonsense, use the other.  */
  إذا (t1 == error_mark_گره)
    أرجع t2;
  إذا (t2 == error_mark_گره)
    أرجع t1;

  إذا (TYPE_QUALS (t1) != TYPE_UNQUALIFIED)
    t1 = TYPE_MAIN_VARIANT (t1);

  إذا (TYPE_QUALS (t2) != TYPE_UNQUALIFIED)
    t2 = TYPE_MAIN_VARIANT (t2);

  إذا (TYPE_صفات (t1) != NULL_درخت)
    {
      درخت attrs = affects_type_عنصر_خنثی_صفات (TYPE_صفات (t1));
      t1 = c_build_type_attribute_variant (t1, attrs);
    }

  إذا (TYPE_صفات (t2) != NULL_درخت)
    {
      درخت attrs = affects_type_عنصر_خنثی_صفات (TYPE_صفات (t2));
      t2 = c_build_type_attribute_variant (t2, attrs);
    }

  /* Save time if the two types are the same.  */

  إذا (t1 == t2) أرجع t1;

  code1 = درخت_کد (t1);
  code2 = درخت_کد (t2);

  gcc_assert (code1 == وکتور_TYPE || code1 == COMPLEX_TYPE
	      || code1 == FIXED_نقطه_TYPE || code1 == REAL_TYPE
	      || code1 == INTEGER_TYPE || code1 == BITINT_TYPE);
  gcc_assert (code2 == وکتور_TYPE || code2 == COMPLEX_TYPE
	      || code2 == FIXED_نقطه_TYPE || code2 == REAL_TYPE
	      || code2 == INTEGER_TYPE || code2 == BITINT_TYPE);

  /* When one operand is a decimal float type, the other operand cannot be
     a generic float type or a complex type.  We also disallow vector types
     here.  */
  إذا ((DECIMAL_FLOAT_TYPE_P (t1) || DECIMAL_FLOAT_TYPE_P (t2))
      && !(DECIMAL_FLOAT_TYPE_P (t1) && DECIMAL_FLOAT_TYPE_P (t2)))
    {
      إذا (code1 == وکتور_TYPE || code2 == وکتور_TYPE)
	{
	  error ("cannot mix operands of decimal floating and vector types");
	  أرجع error_mark_گره;
	}
      إذا (code1 == COMPLEX_TYPE || code2 == COMPLEX_TYPE)
	{
	  error ("cannot mix operands of decimal floating and complex types");
	  أرجع error_mark_گره;
	}
      إذا (code1 == REAL_TYPE && code2 == REAL_TYPE)
	{
	  error ("cannot mix operands of decimal floating "
		 "and other floating types");
	  أرجع error_mark_گره;
	}
    }

  /* If one type is a vector type, return that type.  (How the usual
     arithmetic conversions apply to the vector types extension is not
     precisely specified.)  */
  إذا (code1 == وکتور_TYPE)
    أرجع t1;

  إذا (code2 == وکتور_TYPE)
    أرجع t2;

  /* If one type is complex, form the common type of the non-complex
     components, then make that complex.  Use T1 or T2 if it is the
     required type.  */
  إذا (code1 == COMPLEX_TYPE || code2 == COMPLEX_TYPE)
    {
      درخت subtype1 = code1 == COMPLEX_TYPE ? درخت_TYPE (t1) : t1;
      درخت subtype2 = code2 == COMPLEX_TYPE ? درخت_TYPE (t2) : t2;
      درخت subtype = c_common_type (subtype1, subtype2);

      إذا (code1 == COMPLEX_TYPE && درخت_TYPE (t1) == subtype)
	أرجع t1;
      وإلا إذا (code2 == COMPLEX_TYPE && درخت_TYPE (t2) == subtype)
	أرجع t2;
      وإلا إذا (درخت_کد (subtype) == BITINT_TYPE)
	{
	  sorry ("%<_Complex _BitInt(%d)%> unsupported",
		 TYPE_PRECISION (subtype));
	  أرجع code1 == COMPLEX_TYPE ? t1 : t2;
	}
      وإلا
	أرجع build_complex_type (subtype);
    }

  /* If only one is real, use it as the result.  */

  إذا (code1 == REAL_TYPE && code2 != REAL_TYPE)
    أرجع t1;

  إذا (code2 == REAL_TYPE && code1 != REAL_TYPE)
    أرجع t2;

  /* If both are real and either are decimal floating point types, use
     the decimal floating point type with the greater precision. */

  إذا (code1 == REAL_TYPE && code2 == REAL_TYPE)
    {
      إذا (TYPE_MAIN_VARIANT (t1) == dfloat128_type_گره
	  || TYPE_MAIN_VARIANT (t2) == dfloat128_type_گره)
	أرجع dfloat128_type_گره;
      /* And prefer _Decimal128 over _Decimal64x which has in GCC's
	 implementation the same mode.  */
      وإلا إذا (TYPE_MAIN_VARIANT (t1) == dfloat64x_type_گره
	       || TYPE_MAIN_VARIANT (t2) == dfloat64x_type_گره)
	أرجع dfloat64x_type_گره;
      وإلا إذا (TYPE_MAIN_VARIANT (t1) == dfloat64_type_گره
	       || TYPE_MAIN_VARIANT (t2) == dfloat64_type_گره)
	أرجع dfloat64_type_گره;
      وإلا إذا (TYPE_MAIN_VARIANT (t1) == dfloat32_type_گره
	       || TYPE_MAIN_VARIANT (t2) == dfloat32_type_گره)
	أرجع dfloat32_type_گره;
    }

  /* Deal with fixed-point types.  */
  إذا (code1 == FIXED_نقطه_TYPE || code2 == FIXED_نقطه_TYPE)
    {
      بیعلامت صحيح unsignedp = 0, satp = 0;
      scalar_نما m1, m2;
      بیعلامت صحيح fbit1, ibit1, fbit2, ibit2, max_fbit, max_ibit;

      m1 = SCALAR_TYPE_نما (t1);
      m2 = SCALAR_TYPE_نما (t2);

      /* If one input type is saturating, the result type is saturating.  */
      إذا (TYPE_SATURATING (t1) || TYPE_SATURATING (t2))
	satp = 1;

      /* If both fixed-point types are unsigned, the result type is unsigned.
	 When mixing fixed-point and integer types, follow the sign of the
	 fixed-point type.
	 Otherwise, the result type is signed.  */
      إذا ((TYPE_UNSIGNED (t1) && TYPE_UNSIGNED (t2)
	   && code1 == FIXED_نقطه_TYPE && code2 == FIXED_نقطه_TYPE)
	  || (code1 == FIXED_نقطه_TYPE && code2 != FIXED_نقطه_TYPE
	      && TYPE_UNSIGNED (t1))
	  || (code1 != FIXED_نقطه_TYPE && code2 == FIXED_نقطه_TYPE
	      && TYPE_UNSIGNED (t2)))
	unsignedp = 1;

      /* The result type is signed.  */
      إذا (unsignedp == 0)
	{
	  /* If the input type is unsigned, we need to convert to the
	     signed type.  */
	  إذا (code1 == FIXED_نقطه_TYPE && TYPE_UNSIGNED (t1))
	    {
	      تعداد نما_class mclass = (تعداد نما_class) 0;
	      إذا (GET_نما_CLASS (m1) == نما_UFRACT)
		mclass = نما_FRACT;
	      وإلا إذا (GET_نما_CLASS (m1) == نما_UACCUM)
		mclass = نما_ACCUM;
	      وإلا
		gcc_unreachable ();
	      m1 = as_a <scalar_نما>
		(نما_for_اندازه (GET_نما_PRECISION (m1), mclass, 0));
	    }
	  إذا (code2 == FIXED_نقطه_TYPE && TYPE_UNSIGNED (t2))
	    {
	      تعداد نما_class mclass = (تعداد نما_class) 0;
	      إذا (GET_نما_CLASS (m2) == نما_UFRACT)
		mclass = نما_FRACT;
	      وإلا إذا (GET_نما_CLASS (m2) == نما_UACCUM)
		mclass = نما_ACCUM;
	      وإلا
		gcc_unreachable ();
	      m2 = as_a <scalar_نما>
		(نما_for_اندازه (GET_نما_PRECISION (m2), mclass, 0));
	    }
	}

      إذا (code1 == FIXED_نقطه_TYPE)
	{
	  fbit1 = GET_نما_FBIT (m1);
	  ibit1 = GET_نما_IBIT (m1);
	}
      وإلا
	{
	  fbit1 = 0;
	  /* Signed integers need to subtract one sign bit.  */
	  ibit1 = TYPE_PRECISION (t1) - (!TYPE_UNSIGNED (t1));
	}

      إذا (code2 == FIXED_نقطه_TYPE)
	{
	  fbit2 = GET_نما_FBIT (m2);
	  ibit2 = GET_نما_IBIT (m2);
	}
      وإلا
	{
	  fbit2 = 0;
	  /* Signed integers need to subtract one sign bit.  */
	  ibit2 = TYPE_PRECISION (t2) - (!TYPE_UNSIGNED (t2));
	}

      max_ibit = ibit1 >= ibit2 ?  ibit1 : ibit2;
      max_fbit = fbit1 >= fbit2 ?  fbit1 : fbit2;
      أرجع c_common_fixed_نقطه_type_for_اندازه (max_ibit, max_fbit, unsignedp,
						 satp);
    }

  /* Both real or both integers; use the one with greater precision.  */

  إذا (TYPE_PRECISION (t1) > TYPE_PRECISION (t2))
    أرجع t1;
  وإلا إذا (TYPE_PRECISION (t2) > TYPE_PRECISION (t1))
    أرجع t2;

  /* Same precision.  Prefer long longs to longs to ints when the
     same precision, following the C99 rules on integer type rank
     (which are equivalent to the C90 rules for C90 types).  */

  إذا (TYPE_MAIN_VARIANT (t1) == long_long_unsigned_type_گره
      || TYPE_MAIN_VARIANT (t2) == long_long_unsigned_type_گره)
    أرجع long_long_unsigned_type_گره;

  إذا (TYPE_MAIN_VARIANT (t1) == long_long_integer_type_گره
      || TYPE_MAIN_VARIANT (t2) == long_long_integer_type_گره)
    {
      إذا (TYPE_UNSIGNED (t1) || TYPE_UNSIGNED (t2))
	أرجع long_long_unsigned_type_گره;
      وإلا
	أرجع long_long_integer_type_گره;
    }

  إذا (TYPE_MAIN_VARIANT (t1) == long_unsigned_type_گره
      || TYPE_MAIN_VARIANT (t2) == long_unsigned_type_گره)
    أرجع long_unsigned_type_گره;

  إذا (TYPE_MAIN_VARIANT (t1) == long_integer_type_گره
      || TYPE_MAIN_VARIANT (t2) == long_integer_type_گره)
    {
      /* But preserve unsignedness from the other type,
	 since long cannot hold all the values of an unsigned int.  */
      إذا (TYPE_UNSIGNED (t1) || TYPE_UNSIGNED (t2))
	أرجع long_unsigned_type_گره;
      وإلا
	أرجع long_integer_type_گره;
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

  لكل (صحيح i = رقم_FLOATN_TYPES - 1; i >= 0; i--)
    إذا (mv1 == FLOATN_TYPE_گره (i) || mv2 == FLOATN_TYPE_گره (i))
      أرجع FLOATN_TYPE_گره (i);

  /* Likewise, prefer long double to double even if same size.  */
  إذا (mv1 == long_double_type_گره || mv2 == long_double_type_گره)
    أرجع long_double_type_گره;

  /* Likewise, prefer double to float even if same size.
     We got a couple of embedded targets with 32 bit doubles, and the
     pdp11 might have 64 bit floats.  */
  إذا (mv1 == double_type_گره || mv2 == double_type_گره)
    أرجع double_type_گره;

  إذا (mv1 == float_type_گره || mv2 == float_type_گره)
    أرجع float_type_گره;

  لكل (صحيح i = رقم_FLOATNX_TYPES - 1; i >= 0; i--)
    إذا (mv1 == FLOATNX_TYPE_گره (i) || mv2 == FLOATNX_TYPE_گره (i))
      أرجع FLOATNX_TYPE_گره (i);

  إذا ((code1 == BITINT_TYPE || code2 == BITINT_TYPE) && code1 != code2)
    {
      /* Prefer any other integral types over bit-precise integer types.  */
      إذا (TYPE_UNSIGNED (t1) == TYPE_UNSIGNED (t2))
	أرجع code1 == BITINT_TYPE ? t2 : t1;
      /* If BITINT_TYPE is unsigned and the other type is signed
	 non-BITINT_TYPE with the same precision, the latter has higher rank.
	 In that case:
	 Otherwise, both operands are converted to the unsigned integer type
	 corresponding to the type of the operand with signed integer type.  */
      إذا (TYPE_UNSIGNED (code1 == BITINT_TYPE ? t1 : t2))
	أرجع c_common_unsigned_type (code1 == BITINT_TYPE ? t2 : t1);
    }

  /* Otherwise prefer the unsigned one.  */

  إذا (TYPE_UNSIGNED (t1))
    أرجع t1;
  وإلا
    أرجع t2;
}

/* Wrapper around c_common_type that is used by c-common.cc and other
   front end optimizations that remove promotions.  ENUMERAL_TYPEs
   are allowed here and are converted to their compatible integer types.
   BOOLEAN_TYPEs are allowed here and return either boolean_type_node or
   preferably a non-Boolean type as the common type.  */
درخت
common_type (درخت t1, درخت t2)
{
  إذا (درخت_کد (t1) == ENUMERAL_TYPE)
    t1 = ENUM_UNDERLYING_TYPE (t1);
  إذا (درخت_کد (t2) == ENUMERAL_TYPE)
    t2 = ENUM_UNDERLYING_TYPE (t2);

  /* If both types are BOOLEAN_TYPE, then return boolean_type_node.  */
  إذا (درخت_کد (t1) == BOOLEAN_TYPE
      && درخت_کد (t2) == BOOLEAN_TYPE)
    أرجع boolean_type_گره;

  /* If either type is BOOLEAN_TYPE, then return the other.  */
  إذا (درخت_کد (t1) == BOOLEAN_TYPE)
    أرجع t2;
  إذا (درخت_کد (t2) == BOOLEAN_TYPE)
    أرجع t1;

  أرجع c_common_type (t1, t2);
}



/* Helper function for comptypes.  For two compatible types, return 1
   if they pass consistency checks.  In particular we test that
   TYPE_CANONICAL is set correctly, i.e. the two types can alias.  */

ساكن منطقي
comptypes_verify (درخت type1, درخت type2)
{
  إذا (type1 == type2 || !type1 || !type2
      || درخت_کد (type1) == ERROR_MARK || درخت_کد (type2) == ERROR_MARK)
    أرجع درست;

  gcc_checking_assert (c_verify_type (type1));
  gcc_checking_assert (c_verify_type (type2));

  إذا (TYPE_CANONICAL (type1) != TYPE_CANONICAL (type2)
      && !TYPE_STRUCTURAL_EQUALITY_P (type1)
      && !TYPE_STRUCTURAL_EQUALITY_P (type2))
    {
      /* FIXME: check other types. */
      إذا (رکورد_OR_UNION_TYPE_P (type1)
	  || درخت_کد (type1) == ENUMERAL_TYPE
	  || درخت_کد (type2) == ENUMERAL_TYPE)
	أرجع خطأ;
    }
  أرجع درست;
}

بنية comptypes_داده {

  /* output */
  منطقي enum_and_int_p;
  منطقي different_types_p;
  منطقي warning_needed;

  /* context */
  منطقي anon_فیلد;
  منطقي pointedto;

  /* configuration */
  منطقي equiv;
  منطقي ignore_promoting_آرگومانها;

  ثابت بنية tagged_tu_دیده_cache* cache;
};


/* Helper function for composite_type.  This function ignores when the
   function type of an old-style declaration is incompatible with a type
   of a declaration with prototype because some are arguments are not
   self-promoting.  This is ignored only for function types but not
   ignored in a nested context.  */

ساكن منطقي
comptypes_check_for_مرکب (درخت t1, درخت t2)
{
  بنية comptypes_داده داده = { };
  داده.ignore_promoting_آرگومانها = FUNCTION_TYPE == درخت_کد (t1);
  أرجع comptypes_داخلی (t1, t2, &داده);
}


/* C implementation of compatible_types_for_indirection_note_p.  */

منطقي
compatible_types_for_indirection_note_p (درخت type1, درخت type2)
{
  أرجع comptypes (type1, type2);
}

/* Return true if TYPE1 and TYPE2 are compatible types for assignment
   or various other operations.  */

منطقي
comptypes (درخت type1, درخت type2)
{
  بنية comptypes_داده داده = { };
  منطقي ret = comptypes_داخلی (type1, type2, &داده);

  gcc_checking_assert (!ret || comptypes_verify (type1, type2));

  أرجع ret;
}


/* Like comptypes, but it returns non-zero only for identical
   types.  */

منطقي
comptypes_same_p (درخت type1, درخت type2)
{
  بنية comptypes_داده داده = { };
  منطقي ret = comptypes_داخلی (type1, type2, &داده);

  gcc_checking_assert (!ret || comptypes_verify (type1, type2));

  إذا (داده.different_types_p)
    أرجع خطأ;

  أرجع ret;
}


/* Like comptypes, but if it returns true because enum and int are
   compatible, it sets *ENUM_AND_INT_P to true.  */

منطقي
comptypes_check_enum_int (درخت type1, درخت type2, منطقي *enum_and_int_p)
{
  بنية comptypes_داده داده = { };
  منطقي ret = comptypes_داخلی (type1, type2, &داده);
  *enum_and_int_p = داده.enum_and_int_p;

  gcc_checking_assert (!ret || comptypes_verify (type1, type2));

  أرجع ret;
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

منطقي
comptypes_equiv_p (درخت type1, درخت type2)
{
  بنية comptypes_داده داده = { };
  داده.equiv = درست;
  منطقي ret = comptypes_داخلی (type1, type2, &داده);

  /* check that different equivance classes are assigned only
     to types that are not compatible.  */
  gcc_checking_assert (ret || !comptypes (type1, type2));

  أرجع ret;
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

ساكن منطقي
comptypes_داخلی (const_درخت type1, const_درخت type2,
		    بنية comptypes_داده *داده)
{
  const_درخت t1 = type1;
  const_درخت t2 = type2;

  /* Suppress errors caused by previously reported errors.  */

  إذا (t1 == t2 || !t1 || !t2
      || درخت_کد (t1) == ERROR_MARK || درخت_کد (t2) == ERROR_MARK)
    أرجع درست;

  /* Qualifiers must match. C99 6.7.3p9 */

  إذا (TYPE_QUALS (t1) != TYPE_QUALS (t2))
    أرجع خطأ;

  /* Enumerated types are compatible with integer types, but this is
     not transitive: two enumerated types in the same translation unit
     are compatible with each other only if they are the same type.  */

  إذا (درخت_کد (t1) == ENUMERAL_TYPE
      && COMPLETE_TYPE_P (t1)
      && درخت_کد (t2) != ENUMERAL_TYPE)
    {
      t1 = ENUM_UNDERLYING_TYPE (t1);
      إذا (درخت_کد (t2) != VOID_TYPE)
	{
	  داده->enum_and_int_p = درست;
	  داده->different_types_p = درست;
	}
    }
  وإلا إذا (درخت_کد (t2) == ENUMERAL_TYPE
	   && COMPLETE_TYPE_P (t2)
	   && درخت_کد (t1) != ENUMERAL_TYPE)
    {
      t2 = ENUM_UNDERLYING_TYPE (t2);
      إذا (درخت_کد (t1) != VOID_TYPE)
	{
	  داده->enum_and_int_p = درست;
	  داده->different_types_p = درست;
	}
    }

  إذا (t1 == t2)
    أرجع درست;

  /* Different classes of types can't be compatible.  */

  إذا (درخت_کد (t1) != درخت_کد (t2))
    أرجع خطأ;

  /* Allow for two different type nodes which have essentially the same
     definition.  Note that we already checked for equality of the type
     qualifiers (just above).  */

  إذا (درخت_کد (t1) != ARRAY_TYPE
      && TYPE_MAIN_VARIANT (t1) == TYPE_MAIN_VARIANT (t2))
    أرجع درست;

  صحيح attrval;

  /* 1 if no need for warning yet, 2 if warning cause has been seen.  */
  إذا (!(attrval = comp_type_صفات (t1, t2)))
    أرجع خطأ;

  إذا (2 == attrval)
    داده->warning_needed = درست;

  بدل (درخت_کد (t1))
    {
    حالة INTEGER_TYPE:
    حالة FIXED_نقطه_TYPE:
    حالة REAL_TYPE:
    حالة BITINT_TYPE:
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
      أرجع TYPE_CANONICAL (t1) == TYPE_CANONICAL (t2);

    حالة اشاره_گر_TYPE:
      /* Do not remove mode information.  */
      إذا (TYPE_نما (t1) != TYPE_نما (t2))
	أرجع خطأ;
      داده->pointedto = درست;
      أرجع comptypes_داخلی (درخت_TYPE (t1), درخت_TYPE (t2), داده);

    حالة FUNCTION_TYPE:
      أرجع function_types_compatible_p (t1, t2, داده);

    حالة ARRAY_TYPE:
      {
	درخت d1 = TYPE_DOMAIN (t1);
	درخت d2 = TYPE_DOMAIN (t2);

	/* Target types must match incl. qualifiers.  */
	إذا (!comptypes_داخلی (درخت_TYPE (t1), درخت_TYPE (t2), داده))
	  أرجع خطأ;

	إذا ((d1 == NULL_درخت) != (d2 == NULL_درخت))
	  داده->different_types_p = درست;
	/* Ignore size mismatches when forming equivalence classes.  */
	إذا (داده->equiv)
	  أرجع درست;
	/* Sizes must match unless one is missing or variable.  */
	إذا (d1 == NULL_درخت || d2 == NULL_درخت || d1 == d2)
	  أرجع درست;

	منطقي d1_variable = بالاترین_array_vla_p (t1);
	منطقي d2_variable = بالاترین_array_vla_p (t2);

	إذا (d1_variable != d2_variable)
	  داده->different_types_p = درست;
	إذا (d1_variable || d2_variable)
	  أرجع درست;

	منطقي d1_zero = zero_درازی_array_type_p (t1)
		       || flexible_array_member_type_p (t1);

	منطقي d2_zero = zero_درازی_array_type_p (t2)
		       || flexible_array_member_type_p (t2);

	إذا (d1_zero && d2_zero)
	  أرجع درست;
	إذا (d1_zero || d2_zero)
	  أرجع خطأ;

	إذا (!درخت_int_cst_equal (TYPE_MIN_مقدار (d1), TYPE_MIN_مقدار (d2))
	    || !درخت_int_cst_equal (TYPE_MAX_مقدار (d1), TYPE_MAX_مقدار (d2)))
	  أرجع خطأ;

	أرجع درست;
      }

    حالة ENUMERAL_TYPE:
    حالة رکورد_TYPE:
    حالة UNION_TYPE:

      إذا (!flag_isoc23)
	أرجع خطأ;

      أرجع tagged_types_tu_compatible_p (t1, t2, داده);

    حالة وکتور_TYPE:
      أرجع معلوم_eq (TYPE_وکتور_SUBPARTS (t1), TYPE_وکتور_SUBPARTS (t2))
	     && comptypes_داخلی (درخت_TYPE (t1), درخت_TYPE (t2), داده);

    افتراضي:
      أرجع خطأ;
    }
  gcc_unreachable ();
}

/* Return true if TTL and TTR are pointers to types that are equivalent, ignoring
   their qualifiers, except for named address spaces.  If the pointers point to
   different named addresses, then we must determine if one address space is a
   subset of the other.  */

ساكن منطقي
comp_هدف_types (location_t location, درخت ttl, درخت ttr)
{
  درخت mvl = درخت_TYPE (ttl);
  درخت mvr = درخت_TYPE (ttr);
  addr_space_t asl = TYPE_ADDR_SPACE (mvl);
  addr_space_t asr = TYPE_ADDR_SPACE (mvr);
  addr_space_t as_common;

  /* Fail if pointers point to incompatible address spaces.  */
  إذا (!addr_space_superset (asl, asr, &as_common))
    أرجع 0;

  /* Qualifiers on element types of array types that are
     pointer targets are also removed.  */
  بنية comptypes_داده داده = { };
  إذا (!comptypes_داخلی (remove_qualifiers (mvl),
			   remove_qualifiers (mvr), &داده))
    أرجع خطأ;

  /* For pedantic use comptypes on arrays before removing
     qualifiers on the element type. */
  إذا (درخت_کد (mvl) == ARRAY_TYPE
      && درخت_کد (mvr) == ARRAY_TYPE
      && !comptypes (mvl, mvr))
    pedwarn_c11 (location, OPT_Wpedantic, "invalid use of pointers to arrays "
					  "with different qualifiers in ISO C "
					  "before C23");

  إذا (داده.warning_needed)
    pedwarn (location, OPT_Wpedantic, "types are not quite compatible");

  إذا (داده.enum_and_int_p && warn_cxx_compat)
    warning_at (location, OPT_Wc___compat,
		"pointer target types incompatible in C++");

  أرجع درست;
}

/* Subroutines of `comptypes'.  */

/* Return true if two 'struct', 'union', or 'enum' types T1 and T2 are
   compatible.  The two types are not the same (which has been
   checked earlier in comptypes_internal).  */

ساكن منطقي
tagged_types_tu_compatible_p (const_درخت t1, const_درخت t2,
			      بنية comptypes_داده *داده)
{
  درخت s1, s2;

  إذا (c_type_برچسب (t1) != c_type_برچسب (t2))
    أرجع خطأ;

  /* When forming equivalence classes for TYPE_CANONICAL in C23, we treat
     structs with the same tag as equivalent, but only when they are targets
     of pointers inside other structs.  */
  إذا (داده->equiv && داده->pointedto && NULL_درخت != c_type_برچسب (t1))
    أرجع درست;

  /* Different types without tag are incompatible except as an anonymous
     field or when forming equivalence classes for TYPE_CANONICAL.  */
  إذا (!داده->anon_فیلد && !داده->equiv && NULL_درخت == c_type_برچسب (t1))
    أرجع خطأ;

  إذا (!داده->anon_فیلد && TYPE_STUB_DECL (t1) != TYPE_STUB_DECL (t2))
    داده->different_types_p = درست;

  /* Incomplete types are incompatible inside a TU.  */
  إذا (TYPE_اندازه (t1) == عدم || TYPE_اندازه (t2) == عدم)
    أرجع خطأ;

  إذا (ENUMERAL_TYPE != درخت_کد (t1)
      && (TYPE_معکوس_STORAGE_ترتیب (t1)
	  != TYPE_معکوس_STORAGE_ترتیب (t2)))
    أرجع خطأ;

  إذا (TYPE_USER_ALIGN (t1) != TYPE_USER_ALIGN (t2))
    داده->different_types_p = درست;

  /* For types already being looked at in some active
     invocation of this function, assume compatibility.
     The cache is built as a linked list on the stack
     with the head of the list passed downwards.  */
  لكل (ثابت بنية tagged_tu_دیده_cache *t = داده->cache;
       t != عدم; t = t->بعدی)
    إذا (t->t1 == t1 && t->t2 == t2)
      أرجع درست;

  ثابت بنية tagged_tu_دیده_cache مدخل = { داده->cache, t1, t2 };

  بدل (درخت_کد (t1))
    {
    حالة ENUMERAL_TYPE:
      {
	إذا (!comptypes (ENUM_UNDERLYING_TYPE (t1), ENUM_UNDERLYING_TYPE (t2)))
	  أرجع خطأ;

	/* Speed up the case where the type values are in the same order.  */
	درخت tv1 = TYPE_مقادیر (t1);
	درخت tv2 = TYPE_مقادیر (t2);

	إذا (tv1 == tv2)
	  أرجع درست;

	لكل (;tv1 && tv2; tv1 = درخت_CHAIN (tv1), tv2 = درخت_CHAIN (tv2))
	  {
	    إذا (درخت_PURPOSE (tv1) != درخت_PURPOSE (tv2))
	      اكسر;

	    إذا (simple_cst_equal (DECL_INITIAL (درخت_مقدار (tv1)),
				  DECL_INITIAL (درخت_مقدار (tv2))) != 1)
	      اكسر;
	  }

	إذا (tv1 == NULL_درخت && tv2 == NULL_درخت)
	  أرجع درست;

	إذا (tv1 == NULL_درخت || tv2 == NULL_درخت)
	  أرجع خطأ;

	إذا (list_درازی (TYPE_مقادیر (t1)) != list_درازی (TYPE_مقادیر (t2)))
	  أرجع خطأ;

	لكل (s1 = TYPE_مقادیر (t1); s1; s1 = درخت_CHAIN (s1))
	  {
	    s2 = purpose_member (درخت_PURPOSE (s1), TYPE_مقادیر (t2));

	    إذا (s2 == عدم
		|| simple_cst_equal (DECL_INITIAL (درخت_مقدار (s1)),
				     DECL_INITIAL (درخت_مقدار (s2))) != 1)
	      أرجع خطأ;
	  }

	أرجع درست;
      }

    حالة UNION_TYPE:
    حالة رکورد_TYPE:

	إذا (list_درازی (TYPE_FIELDS (t1)) != list_درازی (TYPE_FIELDS (t2)))
	  أرجع خطأ;

	لكل (s1 = TYPE_FIELDS (t1), s2 = TYPE_FIELDS (t2);
	     s1 && s2;
	     s1 = DECL_CHAIN (s1), s2 = DECL_CHAIN (s2))
	  {
	    gcc_assert (درخت_کد (s1) == فیلد_DECL);
	    gcc_assert (درخت_کد (s2) == فیلد_DECL);

	    درخت ft1 = درخت_TYPE (s1);
	    درخت ft2 = درخت_TYPE (s2);

	    إذا (DECL_NAME (s1) != DECL_NAME (s2))
	      أرجع خطأ;

	    إذا (DECL_ALIGN (s1) != DECL_ALIGN (s2))
	      أرجع خطأ;

	    إذا (DECL_C_بیت_فیلد (s1) != DECL_C_بیت_فیلد (s2))
	       أرجع خطأ;

	    إذا (DECL_C_بیت_فیلد (s1))
	      {
		إذا (!درخت_int_cst_equal (DECL_اندازه (s1), DECL_اندازه (s2)))
		  أرجع خطأ;

		ft1 = DECL_بیت_فیلد_TYPE (s1);
		ft2 = DECL_بیت_فیلد_TYPE (s2);
	      }

	    إذا (!ft1 || !ft2)
	      أرجع خطأ;

	    إذا (درخت_کد (ft1) == ERROR_MARK || درخت_کد (ft2) == ERROR_MARK)
	      أرجع خطأ;

	    داده->anon_فیلد = !DECL_NAME (s1);
	    داده->pointedto = خطأ;

	    ثابت بنية tagged_tu_دیده_cache *cache = داده->cache;
	    داده->cache = &مدخل;
	    منطقي ret = comptypes_داخلی (ft1, ft2, داده);
	    داده->cache = cache;
	    إذا (!ret)
	      أرجع خطأ;

	    درخت st1 = TYPE_اندازه (درخت_TYPE (s1));
	    درخت st2 = TYPE_اندازه (درخت_TYPE (s2));

	    إذا (داده->equiv
		&& st1 && درخت_کد (st1) == INTEGER_CST
		&& st2 && درخت_کد (st2) == INTEGER_CST
		&& !درخت_int_cst_equal (st1, st2))
	     أرجع خطأ;

	    درخت counted_by1 = lookup_attribute ("counted_by",
						 DECL_صفات (s1));
	    درخت counted_by2 = lookup_attribute ("counted_by",
						 DECL_صفات (s2));
	    /* If there is no counted_by attribute for both fields.  */
	    إذا (!counted_by1 && !counted_by2)
	      استمر;

	    /* If only one field has counted_by attribute.  */
	    إذا ((counted_by1 && !counted_by2)
		|| (!counted_by1 && counted_by2))
	      أرجع خطأ;

	    /* Now both s1 and s2 have counted_by attributes, check
	       whether they are the same.  */

	    درخت counted_by_field1
	      = lookup_فیلد (t1, درخت_مقدار (درخت_مقدار (counted_by1)));
	    درخت counted_by_field2
	      = lookup_فیلد (t2, درخت_مقدار (درخت_مقدار (counted_by2)));

	    gcc_assert (counted_by_field1 && counted_by_field2);

	    طالما (درخت_CHAIN (counted_by_field1))
	      counted_by_field1 = درخت_CHAIN (counted_by_field1);
	    طالما (درخت_CHAIN (counted_by_field2))
	      counted_by_field2 = درخت_CHAIN (counted_by_field2);

	    إذا (DECL_NAME (درخت_مقدار (counted_by_field1))
		!= DECL_NAME (درخت_مقدار (counted_by_field2)))
	      أرجع خطأ;
	  }
	أرجع درست;

    افتراضي:
      gcc_unreachable ();
    }
}

/* Return true if two function types F1 and F2 are compatible.
   If either type specifies no argument types,
   the other must specify a fixed number of self-promoting arg types.
   Otherwise, if one type specifies only the number of arguments,
   the other must specify that number of self-promoting arg types.
   Otherwise, the argument types must match.  */

ساكن منطقي
function_types_compatible_p (const_درخت f1, const_درخت f2,
			     بنية comptypes_داده *داده)
{
  درخت ret1 = درخت_TYPE (f1);
  درخت ret2 = درخت_TYPE (f2);

  /* 'volatile' qualifiers on a function's return type used to mean
     the function is noreturn.  */
  إذا (TYPE_VOLATILE (ret1) != TYPE_VOLATILE (ret2))
    pedwarn (درون_داد_location, 0, "function return types not compatible due to %<volatile%>");
  إذا (TYPE_VOLATILE (ret1))
    ret1 = build_qualified_type (TYPE_MAIN_VARIANT (ret1),
				 TYPE_QUALS (ret1) & ~TYPE_QUAL_VOLATILE);
  إذا (TYPE_VOLATILE (ret2))
    ret2 = build_qualified_type (TYPE_MAIN_VARIANT (ret2),
				 TYPE_QUALS (ret2) & ~TYPE_QUAL_VOLATILE);

  منطقي ignore_pargs = داده->ignore_promoting_آرگومانها;
  داده->ignore_promoting_آرگومانها = خطأ;

  إذا (!comptypes_داخلی (ret1, ret2, داده))
    أرجع خطأ;

  داده->ignore_promoting_آرگومانها = ignore_pargs;

  درخت args1 = TYPE_ARG_TYPES (f1);
  درخت args2 = TYPE_ARG_TYPES (f2);

  إذا ((args1 == NULL_درخت) != (args2 == NULL_درخت))
    داده->different_types_p = درست;

  /* An unspecified parmlist matches any specified parmlist
     whose argument types don't need default promotions.  */

  إذا (args1 == NULL_درخت)
    {
      إذا (TYPE_NO_NAMED_آرگومانها_STDARG_P (f1) != TYPE_NO_NAMED_آرگومانها_STDARG_P (f2))
	أرجع خطأ;
      إذا (!(داده->ignore_promoting_آرگومانها || self_promoting_آرگومانها_p (args2)))
	أرجع خطأ;
      داده->ignore_promoting_آرگومانها = خطأ;
      /* If one of these types comes from a non-prototype fn definition,
	 compare that with the other type's arglist.
	 If they don't match, ask for a warning (but no error).  */
      إذا (TYPE_ACTUAL_ARG_TYPES (f1)
	  && !type_lists_compatible_p (args2, TYPE_ACTUAL_ARG_TYPES (f1), داده))
	 داده->warning_needed = درست;
      أرجع درست;
    }
  إذا (args2 == NULL_درخت)
    {
      إذا (TYPE_NO_NAMED_آرگومانها_STDARG_P (f1) != TYPE_NO_NAMED_آرگومانها_STDARG_P (f2))
	أرجع خطأ;
      إذا (!(داده->ignore_promoting_آرگومانها || self_promoting_آرگومانها_p (args1)))
	أرجع خطأ;
      داده->ignore_promoting_آرگومانها = خطأ;
      إذا (TYPE_ACTUAL_ARG_TYPES (f2)
	  && !type_lists_compatible_p (args1, TYPE_ACTUAL_ARG_TYPES (f2), داده))
	داده->warning_needed = درست;
      أرجع درست;
    }

  /* Both types have argument lists: compare them and propagate results.  */
  أرجع type_lists_compatible_p (args1, args2, داده);
}

/* Check two lists of types for compatibility, returning false for
   incompatible, true for compatible.  */

ساكن منطقي
type_lists_compatible_p (const_درخت args1, const_درخت args2,
			 بنية comptypes_داده *داده)
{
  طالما (1)
    {
      إذا (args1 == NULL_درخت && args2 == NULL_درخت)
	أرجع درست;
      /* If one list is shorter than the other,
	 they fail to match.  */
      إذا (args1 == NULL_درخت || args2 == NULL_درخت)
	أرجع خطأ;
      درخت a1 = درخت_مقدار (args1);
      درخت a2 = درخت_مقدار (args2);
      درخت mv1 = remove_qualifiers (a1);
      درخت mv2 = remove_qualifiers (a2);

      gcc_assert (mv2);
      gcc_assert (mv2);

      /* If one of the lists has an error marker, ignore this arg.  */
      إذا (درخت_کد (a1) == ERROR_MARK
	       || درخت_کد (a2) == ERROR_MARK)
	;
      وإلا إذا (!comptypes_داخلی (mv1, mv2, داده))
	{
	  داده->different_types_p = درست;
	  /* Allow  wait (union {union wait *u; int *i} *)
	     and  wait (union wait *)  to be compatible.  */
	  إذا (درخت_کد (a1) == UNION_TYPE
	      && (TYPE_NAME (a1) == NULL_درخت
		  || TYPE_TRANSPARENT_AGGR (a1))
	      && درخت_کد (TYPE_اندازه (a1)) == INTEGER_CST
	      && درخت_int_cst_equal (TYPE_اندازه (a1),
				     TYPE_اندازه (a2)))
	    {
	      درخت memb;
	      لكل (memb = TYPE_FIELDS (a1);
		   memb; memb = DECL_CHAIN (memb))
		{
		  درخت mv3 = remove_qualifiers (درخت_TYPE (memb));
		  إذا (comptypes_داخلی (mv3, mv2, داده))
		    اكسر;
		}
	      إذا (memb == NULL_درخت)
		أرجع خطأ;
	    }
	  وإلا إذا (درخت_کد (a2) == UNION_TYPE
		   && (TYPE_NAME (a2) == NULL_درخت
		       || TYPE_TRANSPARENT_AGGR (a2))
		   && درخت_کد (TYPE_اندازه (a2)) == INTEGER_CST
		   && درخت_int_cst_equal (TYPE_اندازه (a2),
					  TYPE_اندازه (a1)))
	    {
	      درخت memb;
	      لكل (memb = TYPE_FIELDS (a2);
		   memb; memb = DECL_CHAIN (memb))
		{
		  درخت mv3 = remove_qualifiers (درخت_TYPE (memb));
		  إذا (comptypes_داخلی (mv3, mv1, داده))
		    اكسر;
		}
	      إذا (memb == NULL_درخت)
		أرجع خطأ;
	    }
	  وإلا
	    أرجع خطأ;
	}

      args1 = درخت_CHAIN (args1);
      args2 = درخت_CHAIN (args2);
    }
}

/* Compute the size to increment a pointer by.  When a function type or void
   type or incomplete type is passed, size_one_node is returned.
   This function does not emit any diagnostics; the caller is responsible
   for that.  */

ساكن درخت
c_اندازه_درون_بایتها (const_درخت type)
{
  تعداد درخت_کد_2 کد = درخت_کد (type);

  إذا (کد == FUNCTION_TYPE || کد == VOID_TYPE || کد == ERROR_MARK
      || !COMPLETE_TYPE_P (type))
    أرجع اندازه_one_گره;

  /* Convert in case a char is more than one unit.  */
  أرجع اندازه_binop_loc (درون_داد_location, CEIL_DIV_عبارت, TYPE_اندازه_UNIT (type),
			 اندازه_int (TYPE_PRECISION (char_type_گره)
				   / بیتها_در_هر_UNIT));
}

/* Return either DECL or its known constant value (if it has one).  */

درخت
decl_constant_مقدار_1 (درخت decl, منطقي درون_init)
{
  إذا (/* Note that DECL_INITIAL isn't valid for a PARM_DECL.  */
      درخت_کد (decl) != PARM_DECL
      && !درخت_THIS_VOLATILE (decl)
      && درخت_READONLY (decl)
      && DECL_INITIAL (decl) != NULL_درخت
      && !error_عملوند_p (DECL_INITIAL (decl))
      /* This is invalid if initial value is not constant.
	 If it has either a function call, a memory reference,
	 or a variable, then re-evaluating it could give different results.  */
      && درخت_CONSTANT (DECL_INITIAL (decl))
      /* Check for cases where this is sub-optimal, even though valid.  */
      && (درون_init || درخت_کد (DECL_INITIAL (decl)) != CONSTRUCTOR))
    أرجع DECL_INITIAL (decl);
  أرجع decl;
}

/* Return either DECL or its known constant value (if it has one).
   Like the above, but always return decl outside of functions.  */

درخت
decl_constant_مقدار (درخت decl)
{
  /* Don't change a variable array bound or initial value to a constant
     in a place where a variable is invalid.  */
  أرجع current_function_decl ? decl_constant_مقدار_1 (decl, خطأ) : decl;
}

/* Convert the array expression EXP to a pointer.  */
ساكن درخت
array_مقصد_اشاره_گر_conversion (location_t loc, درخت نمایی_تابع)
{
  درخت orig_exp = نمایی_تابع;
  درخت type = درخت_TYPE (نمایی_تابع);
  درخت adr;
  درخت restype = درخت_TYPE (type);
  درخت ptrtype;

  gcc_assert (درخت_کد (type) == ARRAY_TYPE);

  STRIP_TYPE_NOPS (نمایی_تابع);

  copy_warning (نمایی_تابع, orig_exp);

  ptrtype = c_build_اشاره_گر_type (restype);

  إذا (غیرمستقیم_REF_P (نمایی_تابع))
    أرجع convert (ptrtype, درخت_عملوند (نمایی_تابع, 0));

  /* In C++ array compound literals are temporary objects unless they are
     const or appear in namespace scope, so they are destroyed too soon
     to use them for much of anything  (c++/53220).  */
  إذا (warn_cxx_compat && درخت_کد (نمایی_تابع) == COMPOUND_LITERAL_عبارت)
    {
      درخت decl = درخت_عملوند (درخت_عملوند (نمایی_تابع, 0), 0);
      إذا (!درخت_READONLY (decl) && !درخت_STATIC (decl))
	warning_at (DECL_منبع_LOCATION (decl), OPT_Wc___compat,
		    "converting an array compound literal to a pointer "
		    "leads to a dangling pointer in C++");
    }

  adr = build_unary_op (loc, ADDR_عبارت, نمایی_تابع, درست);
  أرجع convert (ptrtype, adr);
}

/* Convert the function expression EXP to a pointer.  */
ساكن درخت
function_مقصد_اشاره_گر_conversion (location_t loc, درخت نمایی_تابع)
{
  درخت orig_exp = نمایی_تابع;

  gcc_assert (درخت_کد (درخت_TYPE (نمایی_تابع)) == FUNCTION_TYPE);

  STRIP_TYPE_NOPS (نمایی_تابع);

  copy_warning (نمایی_تابع, orig_exp);

  درخت exp2 = build_unary_op (loc, ADDR_عبارت, نمایی_تابع, خطأ);

  /* If the function is defined and known to not require a non-local
     context, make sure no trampoline is generated.  */
  إذا (درخت_کد (نمایی_تابع) == FUNCTION_DECL
      && DECL_INITIAL (نمایی_تابع) && !C_FUNC_NONLOCAL_CONTEXT (نمایی_تابع))
   درخت_NO_TRAMPOLINE (exp2) = 1;

  أرجع exp2;
}

/* Mark EXP as read, not just set, for set but not used -Wunused
   warning purposes.  */

فراغ
mark_exp_read (درخت نمایی_تابع)
{
  بدل (درخت_کد (نمایی_تابع))
    {
    حالة VAR_DECL:
    حالة PARM_DECL:
      DECL_READ_P (نمایی_تابع) = 1;
      اكسر;
    CASE_CONVERT:
      إذا (VOID_TYPE_P (درخت_TYPE (نمایی_تابع)))
	بدل (درخت_کد (درخت_عملوند (نمایی_تابع, 0)))
	  {
	  حالة PREINCREMENT_عبارت:
	  حالة PREDECREMENT_عبارت:
	  حالة POSTINCREMENT_عبارت:
	  حالة POSTDECREMENT_عبارت:
	    أرجع;
	  افتراضي:
	    اكسر;
	  }
      /* FALLTHRU */
    حالة ARRAY_REF:
    حالة COMPONENT_REF:
    حالة MODIFY_عبارت:
    حالة REALPART_عبارت:
    حالة IMAGPART_عبارت:
    حالة ADDR_عبارت:
    حالة VIEW_CONVERT_عبارت:
    حالة PREINCREMENT_عبارت:
    حالة PREDECREMENT_عبارت:
    حالة POSTINCREMENT_عبارت:
    حالة POSTDECREMENT_عبارت:
      mark_exp_read (درخت_عملوند (نمایی_تابع, 0));
      اكسر;
    حالة COMPOUND_عبارت:
      /* Pattern match what build_atomic_assign produces with modifycode
	 NOP_EXPR.  */
      إذا (VAR_P (درخت_عملوند (نمایی_تابع, 1))
	  && DECL_ARTIFICIAL (درخت_عملوند (نمایی_تابع, 1))
	  && درخت_کد (درخت_عملوند (نمایی_تابع, 0)) == COMPOUND_عبارت)
	{
	  درخت t1 = درخت_عملوند (درخت_عملوند (نمایی_تابع, 0), 0);
	  درخت t2 = درخت_عملوند (درخت_عملوند (نمایی_تابع, 0), 1);
	  إذا (درخت_کد (t1) == هدف_عبارت
	      && هدف_عبارت_جایگاه (t1) == درخت_عملوند (نمایی_تابع, 1)
	      && درخت_کد (t2) == CALL_عبارت)
	    {
	      درخت fndecl = get_callee_fndecl (t2);
	      درخت arg = NULL_درخت;
	      إذا (fndecl
		  && درخت_کد (fndecl) == FUNCTION_DECL
		  && fndecl_built_درون_p (fndecl, BUILT_درون_نرمال)
		  && call_عبارت_nargs (t2) >= 2)
		بدل (DECL_FUNCTION_کد (fndecl))
		  {
		  حالة BUILT_درون_ATOMIC_STORE:
		    arg = CALL_عبارت_ARG (t2, 1);
		    اكسر;
		  حالة BUILT_درون_ATOMIC_STORE_1:
		  حالة BUILT_درون_ATOMIC_STORE_2:
		  حالة BUILT_درون_ATOMIC_STORE_4:
		  حالة BUILT_درون_ATOMIC_STORE_8:
		  حالة BUILT_درون_ATOMIC_STORE_16:
		    arg = CALL_عبارت_ARG (t2, 0);
		    اكسر;
		  افتراضي:
		    اكسر;
		  }
	      إذا (arg)
		{
		  STRIP_NOPS (arg);
		  إذا (درخت_کد (arg) == ADDR_عبارت
		      && DECL_P (درخت_عملوند (arg, 0))
		      && TYPE_ATOMIC (درخت_TYPE (درخت_عملوند (arg, 0))))
		    mark_exp_read (درخت_عملوند (arg, 0));
		}
	    }
	}
      /* FALLTHRU */
    حالة C_MAYBE_CONST_عبارت:
      mark_exp_read (درخت_عملوند (نمایی_تابع, 1));
      اكسر;
    حالة OMP_ARRAY_SECTION:
      mark_exp_read (درخت_عملوند (نمایی_تابع, 0));
      إذا (درخت_عملوند (نمایی_تابع, 1))
	mark_exp_read (درخت_عملوند (نمایی_تابع, 1));
      إذا (درخت_عملوند (نمایی_تابع, 2))
	mark_exp_read (درخت_عملوند (نمایی_تابع, 2));
      اكسر;
    افتراضي:
      اكسر;
    }
}

/* Perform the default conversion of arrays and functions to pointers.
   Return the result of converting EXP.  For any other expression, just
   return EXP.

   LOC is the location of the expression.  */

بنية c_عبارت
default_function_array_conversion (location_t loc, بنية c_عبارت نمایی_تابع)
{
  درخت orig_exp = نمایی_تابع.مقدار;
  درخت type = درخت_TYPE (نمایی_تابع.مقدار);
  تعداد درخت_کد_2 کد = درخت_کد (type);

  بدل (کد)
    {
    حالة ARRAY_TYPE:
      {
	منطقي not_lvalue = خطأ;
	منطقي lvalue_array_p;

	طالما ((درخت_کد (نمایی_تابع.مقدار) == NON_LVALUE_عبارت
		|| CONVERT_عبارت_P (نمایی_تابع.مقدار))
	       && درخت_TYPE (درخت_عملوند (نمایی_تابع.مقدار, 0)) == type)
	  {
	    إذا (درخت_کد (نمایی_تابع.مقدار) == NON_LVALUE_عبارت)
	      not_lvalue = درست;
	    نمایی_تابع.مقدار = درخت_عملوند (نمایی_تابع.مقدار, 0);
	  }

	copy_warning (نمایی_تابع.مقدار, orig_exp);

	lvalue_array_p = !not_lvalue && lvalue_p (نمایی_تابع.مقدار);
	إذا (!flag_isoc99 && !lvalue_array_p)
	  {
	    /* Before C99, non-lvalue arrays do not decay to pointers.
	       Normally, using such an array would be invalid; but it can
	       be used correctly inside sizeof or as a statement expression.
	       Thus, do not give an error here; an error will result later.  */
	    أرجع نمایی_تابع;
	  }

	نمایی_تابع.مقدار = array_مقصد_اشاره_گر_conversion (loc, نمایی_تابع.مقدار);
      }
      اكسر;
    حالة FUNCTION_TYPE:
      نمایی_تابع.مقدار = function_مقصد_اشاره_گر_conversion (loc, نمایی_تابع.مقدار);
      اكسر;
    افتراضي:
      اكسر;
    }

  أرجع نمایی_تابع;
}

بنية c_عبارت
default_function_array_read_conversion (location_t loc, بنية c_عبارت نمایی_تابع)
{
  mark_exp_read (نمایی_تابع.مقدار);
  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  إذا (درخت_کد (نمایی_تابع.مقدار) == COMPONENT_REF
      && handle_counted_by_p (نمایی_تابع.مقدار))
    نمایی_تابع.مقدار = handle_counted_by_for_component_ref (loc, نمایی_تابع.مقدار);
  أرجع default_function_array_conversion (loc, نمایی_تابع);
}

/* Return whether EXPR should be treated as an atomic lvalue for the
   purposes of load and store handling.  */

ساكن منطقي
really_atomic_lvalue (درخت عبارت)
{
  إذا (error_عملوند_p (عبارت))
    أرجع خطأ;
  إذا (!TYPE_ATOMIC (درخت_TYPE (عبارت)))
    أرجع خطأ;
  إذا (!COMPLETE_TYPE_P (درخت_TYPE (عبارت)))
    أرجع خطأ;
  إذا (!lvalue_p (عبارت))
    أرجع خطأ;

  /* Ignore _Atomic on register variables, since their addresses can't
     be taken so (a) atomicity is irrelevant and (b) the normal atomic
     sequences wouldn't work.  Ignore _Atomic on structures containing
     bit-fields, since accessing elements of atomic structures or
     unions is undefined behavior (C11 6.5.2.3#5), but it's unclear if
     it's undefined at translation time or execution time, and the
     normal atomic sequences again wouldn't work.  */
  طالما (handled_component_p (عبارت))
    {
      إذا (درخت_کد (عبارت) == COMPONENT_REF
	  && DECL_C_بیت_فیلد (درخت_عملوند (عبارت, 1)))
	أرجع خطأ;
      عبارت = درخت_عملوند (عبارت, 0);
    }
  إذا (درخت_کد (عبارت) == COMPOUND_LITERAL_عبارت)
    عبارت = COMPOUND_LITERAL_عبارت_DECL (عبارت);
  إذا (DECL_P (عبارت) && C_DECL_ثبات (عبارت))
    أرجع خطأ;
  أرجع درست;
}

/* If EXPR is a named constant (C23) derived from a constexpr variable
   - that is, a reference to such a variable, or a member extracted by
   a sequence of structure and union (but not array) member accesses
   (where union member accesses must access the same member as
   initialized) - then return the corresponding initializer;
   otherwise, return NULL_TREE.  */

ساكن درخت
maybe_get_constexpr_init (درخت عبارت)
{
  درخت decl = NULL_درخت;
  إذا (درخت_کد (عبارت) == VAR_DECL)
    decl = عبارت;
  وإلا إذا (درخت_کد (عبارت) == COMPOUND_LITERAL_عبارت)
    decl = COMPOUND_LITERAL_عبارت_DECL (عبارت);
  إذا (decl
      && C_DECL_DECLARED_CONSTEXPR (decl)
      && DECL_INITIAL (decl) != NULL_درخت
      && !error_عملوند_p (DECL_INITIAL (decl)))
    أرجع DECL_INITIAL (decl);
  إذا (درخت_کد (عبارت) != COMPONENT_REF)
    أرجع NULL_درخت;
  درخت inner = maybe_get_constexpr_init (درخت_عملوند (عبارت, 0));
  إذا (inner == NULL_درخت)
    أرجع NULL_درخت;
  طالما ((CONVERT_عبارت_P (inner) || درخت_کد (inner) == NON_LVALUE_عبارت)
	 && !error_عملوند_p (inner)
	 && (TYPE_MAIN_VARIANT (درخت_TYPE (inner))
	     == TYPE_MAIN_VARIANT (درخت_TYPE (درخت_عملوند (inner, 0)))))
    inner = درخت_عملوند (inner, 0);
  إذا (درخت_کد (inner) != CONSTRUCTOR)
    أرجع NULL_درخت;
  درخت فیلد_2 = درخت_عملوند (عبارت, 1);
  بیعلامت HOST_WIDE_INT cidx;
  درخت cfield, cvalue;
  منطقي have_other_init = خطأ;
  FOR_EACH_CONSTRUCTOR_ELT (CONSTRUCTOR_ELTS (inner), cidx, cfield, cvalue)
    {
      إذا (cfield == فیلد_2)
	أرجع cvalue;
      have_other_init = درست;
    }
  إذا (درخت_کد (درخت_TYPE (inner)) == UNION_TYPE
      && (have_other_init || فیلد_2 != TYPE_FIELDS (درخت_TYPE (inner))))
    أرجع NULL_درخت;
  /* Return a default initializer.  */
  إذا (رکورد_OR_UNION_TYPE_P (درخت_TYPE (عبارت)))
    أرجع build_constructor (درخت_TYPE (عبارت), عدم);
  أرجع build_zero_cst (درخت_TYPE (عبارت));
}

/* Helper function for convert_lvalue_to_rvalue called via
   walk_tree_without_duplicates.  Find DATA inside of the expression.  */

ساكن درخت
c_پیدا_کن_var_r (درخت *tp, صحيح *walk_subtrees, فراغ *داده)
{
  إذا (TYPE_P (*tp))
    *walk_subtrees = 0;
  وإلا إذا (*tp == (درخت) داده)
    أرجع *tp;
  أرجع NULL_درخت;
}

/* Convert expression EXP (location LOC) from lvalue to rvalue,
   including converting functions and arrays to pointers if CONVERT_P.
   If READ_P, also mark the expression as having been read.  If
   FOR_INIT, constexpr expressions of structure and union type should
   be replaced by the corresponding CONSTRUCTOR; otherwise, only
   constexpr scalars (including elements of structures and unions) are
   replaced by their initializers.  */

بنية c_عبارت
convert_lvalue_مقصد_rvalue (location_t loc, بنية c_عبارت نمایی_تابع,
			  منطقي convert_p, منطقي read_p, منطقي for_init)
{
  منطقي force_non_npc = خطأ;
  إذا (read_p)
    mark_exp_read (نمایی_تابع.مقدار);
  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  إذا (read_p && درخت_کد (نمایی_تابع.مقدار) == COMPONENT_REF
      && handle_counted_by_p (نمایی_تابع.مقدار))
    نمایی_تابع.مقدار = handle_counted_by_for_component_ref (loc, نمایی_تابع.مقدار);

  إذا (convert_p)
    نمایی_تابع = default_function_array_conversion (loc, نمایی_تابع);
  إذا (!VOID_TYPE_P (درخت_TYPE (نمایی_تابع.مقدار))
      || (flag_isoc2y
	  && TYPE_QUALS (درخت_TYPE (نمایی_تابع.مقدار)) != TYPE_UNQUALIFIED))
    نمایی_تابع.مقدار = require_complete_type (loc, نمایی_تابع.مقدار);
  إذا (for_init || !رکورد_OR_UNION_TYPE_P (درخت_TYPE (نمایی_تابع.مقدار)))
    {
      درخت init = maybe_get_constexpr_init (نمایی_تابع.مقدار);
      إذا (init != NULL_درخت)
	{
	  /* A named constant of pointer type or type nullptr_t is not
	     a null pointer constant even if the initializer is
	     one.  */
	  إذا (درخت_کد (init) == INTEGER_CST
	      && !INTEGRAL_TYPE_P (درخت_TYPE (init))
	      && integer_zerop (init))
	    force_non_npc = درست;
	  نمایی_تابع.مقدار = init;
	}
    }
  إذا (really_atomic_lvalue (نمایی_تابع.مقدار))
    {
      vec<درخت, va_gc> *params;
      درخت nonatomic_type, tmp, tmp_addr, fndecl, func_call;
      درخت عبارت_type = درخت_TYPE (نمایی_تابع.مقدار);
      درخت عبارت_addr = build_unary_op (loc, ADDR_عبارت, نمایی_تابع.مقدار, خطأ);
      درخت seq_cst = build_int_cst (integer_type_گره, MEMMODEL_SEQ_CST);

      gcc_assert (TYPE_ATOMIC (عبارت_type));

      /* Expansion of a generic atomic load may require an addition
	 element, so allocate enough to prevent a resize.  */
      vec_alloc (params, 4);

      /* Remove the qualifiers for the rest of the expressions and
	 create the VAL temp variable to hold the RHS.  */
      nonatomic_type = build_qualified_type (عبارت_type, TYPE_UNQUALIFIED);
      tmp = create_tmp_var_raw (nonatomic_type);
      tmp_addr = build_unary_op (loc, ADDR_عبارت, tmp, خطأ);
      درخت_ADDRESSABLE (tmp) = 1;
      /* Do not disable warnings for TMP even though it's artificial.
	 -Winvalid-memory-model depends on it.  */

      /* Issue __atomic_load (&expr, &tmp, SEQ_CST);  */
      fndecl = builtin_decl_explicit (BUILT_درون_ATOMIC_بارگیری);
      params->سریع_افزودن (عبارت_addr);
      params->سریع_افزودن (tmp_addr);
      params->سریع_افزودن (seq_cst);
      func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, عدم);

      /* EXPR is always read.  */
      mark_exp_read (نمایی_تابع.مقدار);

      /* Optimize the common case where c_build_function_call_vec
	 immediately folds __atomic_load (&expr, &tmp, SEQ_CST); into
	 tmp = __atomic_load_<N> (&expr, SEQ_CST);
	 In that case tmp is not addressable and can be initialized
	 fully by the rhs of the MODIFY_EXPR.  */
      درخت tem = func_call;
      إذا (CONVERT_عبارت_P (tem) && VOID_TYPE_P (درخت_TYPE (tem)))
	{
	  tem = درخت_عملوند (tem, 0);
	  إذا (درخت_کد (tem) == MODIFY_عبارت
	      && درخت_عملوند (tem, 0) == tmp
	      && !walk_درخت_without_duplicates (&درخت_عملوند (tem, 1),
						c_پیدا_کن_var_r, tmp))
	    {
	      درخت_ADDRESSABLE (tmp) = 0;
	      func_call = درخت_عملوند (tem, 1);
	    }
	}

      /* Return tmp which contains the value loaded.  */
      نمایی_تابع.مقدار = build4 (هدف_عبارت, nonatomic_type, tmp, func_call,
			  NULL_درخت, NULL_درخت);
    }
  إذا (convert_p && !error_عملوند_p (نمایی_تابع.مقدار)
      && (درخت_کد (درخت_TYPE (نمایی_تابع.مقدار)) != ARRAY_TYPE))
    نمایی_تابع.مقدار = convert (build_qualified_type (درخت_TYPE (نمایی_تابع.مقدار), TYPE_UNQUALIFIED), نمایی_تابع.مقدار);
  إذا (force_non_npc)
    نمایی_تابع.مقدار = build1 (NOP_عبارت, درخت_TYPE (نمایی_تابع.مقدار), نمایی_تابع.مقدار);

  {
    درخت false_مقدار, true_مقدار;
    إذا (convert_p && !error_عملوند_p (نمایی_تابع.مقدار)
	&& c_hardbool_type_attr (درخت_TYPE (نمایی_تابع.مقدار),
				 &false_مقدار, &true_مقدار))
      {
	درخت t = save_عبارت (نمایی_تابع.مقدار);

	mark_exp_read (نمایی_تابع.مقدار);

	درخت trapfn = builtin_decl_explicit (BUILT_درون_TRAP);
	درخت عبارت = build_call_عبارت_loc (loc, trapfn, 0);
	عبارت = build_compound_عبارت (loc, عبارت, boolean_true_گره);
	عبارت = fold_build3_loc (loc, COND_عبارت, boolean_type_گره,
				fold_build2_loc (loc, NE_عبارت,
						 boolean_type_گره,
						 t, true_مقدار),
				عبارت, boolean_true_گره);
	عبارت = fold_build3_loc (loc, COND_عبارت, boolean_type_گره,
				fold_build2_loc (loc, NE_عبارت,
						 boolean_type_گره,
						 t, false_مقدار),
				عبارت, boolean_false_گره);

	نمایی_تابع.مقدار = عبارت;
      }
  }

  أرجع نمایی_تابع;
}

/* Wrapper for the overload above, same arguments but for tree rather than
   c_expr.  This is important for hardbools to decay to bools.  */

ساكن مضمن درخت
convert_lvalue_مقصد_rvalue (location_t loc, درخت val,
			  منطقي convert_p, منطقي read_p, منطقي for_init = خطأ)
{
  بنية c_عبارت عبارت;
  memset (&عبارت, 0, حجم (عبارت));
  عبارت.مقدار = val;
  عبارت = convert_lvalue_مقصد_rvalue (loc, عبارت, convert_p, read_p, for_init);
  أرجع عبارت.مقدار;
}

/* EXP is an expression of integer type.  Apply the integer promotions
   to it and return the promoted value.  */

درخت
perform_integral_promotions (درخت نمایی_تابع)
{
  درخت type = درخت_TYPE (نمایی_تابع);
  تعداد درخت_کد_2 کد = درخت_کد (type);

  gcc_assert (INTEGRAL_TYPE_P (type));

  /* Convert enums to the result of applying the integer promotions to
     their underlying type.  */
  إذا (کد == ENUMERAL_TYPE)
    {
      type = ENUM_UNDERLYING_TYPE (type);
      إذا (c_promoting_integer_type_p (type))
	{
	  إذا (TYPE_UNSIGNED (type)
	      && TYPE_PRECISION (type) == TYPE_PRECISION (integer_type_گره))
	    type = unsigned_type_گره;
	  وإلا
	    type = integer_type_گره;
	}

      أرجع convert (type, نمایی_تابع);
    }

  /* ??? This should no longer be needed now bit-fields have their
     proper types.  */
  إذا (درخت_کد (نمایی_تابع) == COMPONENT_REF
      && DECL_C_بیت_فیلد (درخت_عملوند (نمایی_تابع, 1)))
    {
      إذا (BITINT_TYPE_P (DECL_بیت_فیلد_TYPE (درخت_عملوند (نمایی_تابع, 1))))
	{
	  درخت btype = DECL_بیت_فیلد_TYPE (درخت_عملوند (نمایی_تابع, 1));
	  إذا (درخت_کد (btype) == BITINT_TYPE)
	    أرجع convert (btype, نمایی_تابع);
	  وإلا
	    أرجع convert (ENUM_UNDERLYING_TYPE (btype), نمایی_تابع);
	}
      /* If it's thinner than an int, promote it like a
	 c_promoting_integer_type_p, otherwise leave it alone.  */
      إذا (compare_درخت_int (DECL_اندازه (درخت_عملوند (نمایی_تابع, 1)),
			    TYPE_PRECISION (integer_type_گره)) < 0)
	أرجع convert (integer_type_گره, نمایی_تابع);
    }

  إذا (c_promoting_integer_type_p (type))
    {
      /* Preserve unsignedness if not really getting any wider.  */
      إذا (TYPE_UNSIGNED (type)
	  && TYPE_PRECISION (type) == TYPE_PRECISION (integer_type_گره))
	أرجع convert (unsigned_type_گره, نمایی_تابع);

      أرجع convert (integer_type_گره, نمایی_تابع);
    }

  أرجع نمایی_تابع;
}


/* Perform default promotions for C data used in expressions.
   Enumeral types or short or char are converted to int.
   In addition, manifest constants symbols are replaced by their values.  */

درخت
default_conversion (درخت نمایی_تابع)
{
  درخت orig_exp;
  درخت type = درخت_TYPE (نمایی_تابع);
  تعداد درخت_کد_2 کد = درخت_کد (type);
  درخت promoted_type;

  mark_exp_read (نمایی_تابع);
  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  إذا (درخت_کد (نمایی_تابع) == COMPONENT_REF
      && handle_counted_by_p (نمایی_تابع))
    نمایی_تابع = handle_counted_by_for_component_ref (عبارت_LOCATION (نمایی_تابع), نمایی_تابع);

  /* Functions and arrays have been converted during parsing.  */
  gcc_assert (کد != FUNCTION_TYPE);
  إذا (کد == ARRAY_TYPE)
    أرجع نمایی_تابع;

  /* Constants can be used directly unless they're not loadable.  */
  إذا (درخت_کد (نمایی_تابع) == CONST_DECL)
    نمایی_تابع = DECL_INITIAL (نمایی_تابع);

  /* Strip no-op conversions.  */
  orig_exp = نمایی_تابع;
  STRIP_TYPE_NOPS (نمایی_تابع);

  copy_warning (نمایی_تابع, orig_exp);

  إذا (کد == VOID_TYPE)
    {
      error_at (عبارت_LOC_OR_LOC (نمایی_تابع, درون_داد_location),
		"void value not ignored as it ought to be");
      أرجع error_mark_گره;
    }

  نمایی_تابع = require_complete_type (عبارت_LOC_OR_LOC (نمایی_تابع, درون_داد_location), نمایی_تابع);
  إذا (نمایی_تابع == error_mark_گره)
    أرجع error_mark_گره;

  promoted_type = targetm.promoted_type (type);
  إذا (promoted_type)
    أرجع convert (promoted_type, نمایی_تابع);

  إذا (INTEGRAL_TYPE_P (type))
    {
      /* Avoid performing integral promotion of bit-precise integer
	 type bit-field to its corresponding bit-precise integer if
	 orig_exp is a cast to it to its underlying type.  */
      إذا (orig_exp != نمایی_تابع
	  && درخت_کد (نمایی_تابع) == COMPONENT_REF
	  && DECL_C_بیت_فیلد (درخت_عملوند (نمایی_تابع, 1))
	  && BITINT_TYPE_P (DECL_بیت_فیلد_TYPE (درخت_عملوند (نمایی_تابع, 1))))
	أرجع perform_integral_promotions (orig_exp);
      أرجع perform_integral_promotions (نمایی_تابع);
    }

  أرجع نمایی_تابع;
}

/* Look up COMPONENT in a structure or union TYPE.

   If the component name is not found, returns NULL_TREE.  Otherwise,
   the return value is a TREE_LIST, with each TREE_VALUE a FIELD_DECL
   stepping down the chain to the component, which is in the last
   TREE_VALUE of the list.  Normally the list is of length one, but if
   the component is embedded within (nested) anonymous structures or
   unions, the list steps down the chain to the component.  */

درخت
lookup_فیلد (const_درخت type, درخت component)
{
  درخت فیلد_2;

  /* If TYPE_LANG_SPECIFIC is set, then it is a sorted array of pointers
     to the field elements.  Use a binary search on this array to quickly
     find the element.  Otherwise, do a linear search.  TYPE_LANG_SPECIFIC
     will always be set for structures which have many elements.

     Duplicate field checking replaces duplicates with NULL_TREE so
     TYPE_LANG_SPECIFIC arrays are potentially no longer sorted.  In that
     case just iterate using DECL_CHAIN.  */

  إذا (TYPE_LANG_SPECIFIC (type) && TYPE_LANG_SPECIFIC (type)->s
      && !دیده_error ())
    {
      صحيح bot, بالاترین, half;
      درخت *فیلد_array = &TYPE_LANG_SPECIFIC (type)->s->elts[0];

      فیلد_2 = TYPE_FIELDS (type);
      bot = 0;
      بالاترین = TYPE_LANG_SPECIFIC (type)->s->len;
      طالما (بالاترین - bot > 1)
	{
	  half = (بالاترین - bot + 1) >> 1;
	  فیلد_2 = فیلد_array[bot+half];

	  إذا (DECL_NAME (فیلد_2) == NULL_درخت)
	    {
	      /* Step through all anon unions in linear fashion.  */
	      طالما (DECL_NAME (فیلد_array[bot]) == NULL_درخت)
		{
		  فیلد_2 = فیلد_array[bot++];
		  إذا (رکورد_OR_UNION_TYPE_P (درخت_TYPE (فیلد_2)))
		    {
		      درخت anon = lookup_فیلد (درخت_TYPE (فیلد_2), component);

		      إذا (anon)
			أرجع درخت_cons (NULL_درخت, فیلد_2, anon);

		      /* The Plan 9 compiler permits referring
			 directly to an anonymous struct/union field
			 using a typedef name.  */
		      إذا (flag_plan9_extensions
			  && TYPE_NAME (درخت_TYPE (فیلد_2)) != NULL_درخت
			  && (درخت_کد (TYPE_NAME (درخت_TYPE (فیلد_2)))
			      == TYPE_DECL)
			  && (DECL_NAME (TYPE_NAME (درخت_TYPE (فیلد_2)))
			      == component))
			اكسر;
		    }
		}

	      /* Entire record is only anon unions.  */
	      إذا (bot > بالاترین)
		أرجع NULL_درخت;

	      /* Restart the binary search, with new lower bound.  */
	      استمر;
	    }

	  إذا (DECL_NAME (فیلد_2) == component)
	    اكسر;
	  إذا (DECL_NAME (فیلد_2) < component)
	    bot += half;
	  وإلا
	    بالاترین = bot + half;
	}

      إذا (DECL_NAME (فیلد_array[bot]) == component)
	فیلد_2 = فیلد_array[bot];
      وإلا إذا (DECL_NAME (فیلد_2) != component)
	أرجع NULL_درخت;
    }
  وإلا
    {
      لكل (فیلد_2 = TYPE_FIELDS (type); فیلد_2; فیلد_2 = DECL_CHAIN (فیلد_2))
	{
	  إذا (DECL_NAME (فیلد_2) == NULL_درخت
	      && رکورد_OR_UNION_TYPE_P (درخت_TYPE (فیلد_2)))
	    {
	      درخت anon = lookup_فیلد (درخت_TYPE (فیلد_2), component);

	      إذا (anon)
		أرجع درخت_cons (NULL_درخت, فیلد_2, anon);

	      /* The Plan 9 compiler permits referring directly to an
		 anonymous struct/union field using a typedef
		 name.  */
	      إذا (flag_plan9_extensions
		  && TYPE_NAME (درخت_TYPE (فیلد_2)) != NULL_درخت
		  && درخت_کد (TYPE_NAME (درخت_TYPE (فیلد_2))) == TYPE_DECL
		  && (DECL_NAME (TYPE_NAME (درخت_TYPE (فیلد_2)))
		      == component))
		اكسر;
	    }

	  إذا (DECL_NAME (فیلد_2) == component)
	    اكسر;
	}

      إذا (فیلد_2 == NULL_درخت)
	أرجع NULL_درخت;
    }

  أرجع درخت_cons (NULL_درخت, فیلد_2, NULL_درخت);
}

/* Recursively append candidate IDENTIFIER_NODEs to CANDIDATES.  */

ساكن فراغ
lookup_فیلد_fuzzy_پیدا_کن_candidates (درخت type, درخت component,
				    vec<درخت> *candidates)
{
  درخت فیلد_2;
  لكل (فیلد_2 = TYPE_FIELDS (type); فیلد_2; فیلد_2 = DECL_CHAIN (فیلد_2))
    {
      إذا (DECL_NAME (فیلد_2) == NULL_درخت
	  && رکورد_OR_UNION_TYPE_P (درخت_TYPE (فیلد_2)))
	lookup_فیلد_fuzzy_پیدا_کن_candidates (درخت_TYPE (فیلد_2), component,
					    candidates);

      إذا (DECL_NAME (فیلد_2))
	candidates->امن_افزودن (DECL_NAME (فیلد_2));
    }
}

/* Like "lookup_field", but find the closest matching IDENTIFIER_NODE,
   rather than returning a TREE_LIST for an exact match.  */

ساكن درخت
lookup_فیلد_fuzzy (درخت type, درخت component)
{
  gcc_assert (درخت_کد (component) == IDENTIFIER_گره);

  /* First, gather a list of candidates.  */
  auto_vec <درخت> candidates;

  lookup_فیلد_fuzzy_پیدا_کن_candidates (type, component,
				      &candidates);

  أرجع پیدا_کن_closest_identifier (component, &candidates);
}

/* Support function for build_component_ref's error-handling.

   Given DATUM_TYPE, and "DATUM.COMPONENT", where DATUM is *not* a
   struct or union, should we suggest "DATUM->COMPONENT" as a hint?  */

ساكن منطقي
should_suggest_deref_p (درخت datum_type)
{
  /* We don't do it for Objective-C, since Objective-C 2.0 dot-syntax
     allows "." for ptrs; we could be handling a failed attempt
     to access a property.  */
  إذا (c_dialect_objc ())
    أرجع خطأ;

  /* Only suggest it for pointers...  */
  إذا (درخت_کد (datum_type) != اشاره_گر_TYPE)
    أرجع خطأ;

  /* ...to structs/unions.  */
  درخت underlying_type = درخت_TYPE (datum_type);
  تعداد درخت_کد_2 کد = درخت_کد (underlying_type);
  إذا (کد == رکورد_TYPE || کد == UNION_TYPE)
    أرجع درست;
  وإلا
    أرجع خطأ;
}

/* Give a component ref REF, decide whether we should handle its counted_by
   attribute based on its context:
   Do not handle counted_by when in offsetof, typeof and alignof operator.  */

ساكن منطقي
handle_counted_by_p (درخت ref)
{
  gcc_assert (درخت_کد (ref) == COMPONENT_REF);
  درخت datum = درخت_عملوند (ref, 0);
  /* If the component_ref is build for a offsetof, i.e., the datum
     of the component_ref is a indirect_ref of null_pointer_node,
     we should not generate call to .ACCESS_WITH_SIZE.  */
  إذا (درخت_کد (datum) == غیرمستقیم_REF
      && درخت_عملوند (datum, 0) == null_اشاره_گر_گره)
    أرجع خطأ;
  إذا (درون_typeof || درون_alignof)
    أرجع خطأ;
  أرجع درست;
}

/* Given a component ref REF, if there is a counted_by attribute attached,
   issue error when the element_type is a structure or union including a
   flexible array member.  */

ساكن فراغ
check_counted_by_attribute (location_t loc, درخت ref)
{
  درخت subdatum = درخت_عملوند (ref, 1);
  درخت sub_type = درخت_TYPE (subdatum);

  إذا (!flexible_array_member_type_p (sub_type)
      && درخت_کد (sub_type) != اشاره_گر_TYPE)
    أرجع;

  درخت element_type = درخت_TYPE (sub_type);

  درخت attr_counted_by = lookup_attribute ("counted_by",
					   DECL_صفات (subdatum));
  إذا (attr_counted_by)
    {
      /* Issue error when the element_type is a structure or
	union including a flexible array member.  */
      إذا (رکورد_OR_UNION_TYPE_P (element_type)
	  && TYPE_INCLUDES_FLEXARRAY (element_type))
	{
	  error_at (loc,
		    "%<counted_by%> attribute is not allowed for a pointer to"
		    " structure or union with flexible array member");
	  أرجع;
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

ساكن درخت
build_counted_by_ref (درخت datum, درخت subdatum,
		      درخت *counted_by_type)
{
  درخت sub_type = درخت_TYPE (subdatum);
  إذا (!flexible_array_member_type_p (sub_type)
      && درخت_کد (sub_type) != اشاره_گر_TYPE)
    أرجع NULL_درخت;

  درخت attr_counted_by = lookup_attribute ("counted_by",
					   DECL_صفات (subdatum));
  إذا (!attr_counted_by)
    أرجع NULL_درخت;

  درخت counted_by_ref = NULL_درخت;
  *counted_by_type = NULL_درخت;

  درخت type = درخت_TYPE (datum);

  /* If the type of the containing structure is an anonymous struct/union,
     and this anonymous struct/union is not a root type, get the first
     outer named structure/union type.  */
  طالما (درخت_کد (datum) == COMPONENT_REF
	 && c_type_برچسب (type) == NULL_درخت
	 && DECL_NAME (درخت_عملوند (datum, 1)) == NULL_درخت)
    {
      datum = درخت_عملوند (datum, 0);
      type = درخت_TYPE (datum);
    }

  درخت فیلد_id = درخت_مقدار (درخت_مقدار (attr_counted_by));
  درخت counted_by_فیلد = lookup_فیلد (type, فیلد_id);
  gcc_assert (counted_by_فیلد);

  درخت counted_by_subdatum;
  افعل
    {
      counted_by_subdatum = درخت_مقدار (counted_by_فیلد);
      /* Get the TYPE of the counted_by field.  */
      *counted_by_type = درخت_TYPE (counted_by_subdatum);

      counted_by_ref
	= build3 (COMPONENT_REF, درخت_TYPE (counted_by_subdatum),
		  datum, counted_by_subdatum, NULL_درخت);

      datum = counted_by_ref;
      counted_by_فیلد = درخت_CHAIN (counted_by_فیلد);
    }
  طالما (counted_by_فیلد);

  counted_by_ref = build_fold_addr_عبارت (counted_by_ref);
  أرجع counted_by_ref;
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
ساكن درخت
build_access_with_اندازه_for_counted_by (location_t loc, درخت ref,
				       درخت counted_by_ref,
				       درخت counted_by_type)
{
  gcc_assert (flexible_array_member_type_p (درخت_TYPE (ref))
	      || درخت_کد (درخت_TYPE (ref)) == اشاره_گر_TYPE);

  منطقي is_fam = flexible_array_member_type_p (درخت_TYPE (ref));

  /* The result type of the call is a pointer to the flexible array type;
     or is the original pointer type to the pointer field with counted_by.  */
  درخت نتیجه_type = is_fam ? c_build_اشاره_گر_type (درخت_TYPE (ref))
		     : درخت_TYPE (ref);

  درخت element_type = درخت_TYPE (درخت_TYPE (ref));
  درخت element_اندازه = VOID_TYPE_P (element_type)
		      ? اندازه_one_گره
		      : TYPE_اندازه_UNIT (element_type);
  إذا (element_اندازه == NULL_درخت)
    أرجع ref;

  درخت اولی_param = is_fam
		     ? c_fully_fold (array_مقصد_اشاره_گر_conversion (loc, ref),
				     خطأ, عدم)
		     : c_fully_fold (ref, خطأ, عدم);
  درخت دومی_param
    = c_fully_fold (counted_by_ref, خطأ, عدم);
  درخت سوم_param = build_int_cst (c_build_اشاره_گر_type (counted_by_type), 0);

  درخت call
    = build_call_عبارت_داخلی_loc (loc, IFN_ACCESS_WITH_اندازه,
				    نتیجه_type, 4,
				    اولی_param,
				    دومی_param,
				    سوم_param,
				    element_اندازه);

  /* Wrap the call with an INDIRECT_REF with the flexible array type.  */
  إذا (is_fam)
    call = build1 (غیرمستقیم_REF, درخت_TYPE (ref), call);
  مجموعه_عبارت_LOCATION (call, loc);
  أرجع call;
}

/* For the COMPONENT_REF ref, check whether it has a counted_by attribute,
   if so, wrap this COMPONENT_REF with the corresponding CALL to the
   function .ACCESS_WITH_SIZE.
   Otherwise, return the ref itself.  */

درخت
handle_counted_by_for_component_ref (location_t loc, درخت ref)
{
  gcc_assert (درخت_کد (ref) == COMPONENT_REF);
  درخت datum = درخت_عملوند (ref, 0);
  درخت subdatum = درخت_عملوند (ref, 1);
  درخت counted_by_type = NULL_درخت;

  إذا (!(flexible_array_member_type_p (درخت_TYPE (ref))
	|| درخت_کد (درخت_TYPE (ref)) == اشاره_گر_TYPE))
    أرجع ref;

  درخت counted_by_ref = build_counted_by_ref (datum, subdatum,
					      &counted_by_type);
  إذا (counted_by_ref)
    ref = build_access_with_اندازه_for_counted_by (loc, ref,
						 counted_by_ref,
						 counted_by_type);
  أرجع ref;
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
  تعداد درخت_کد_2 کد = درخت_کد (type);
  درخت فیلد_2 = عدم;
  درخت ref;
  منطقي datum_lvalue = lvalue_p (datum);

  إذا (!objc_is_عمومی (datum, component))
    أرجع error_mark_گره;

  /* Detect Objective-C property syntax object.property.  */
  إذا (c_dialect_objc ()
      && (ref = objc_maybe_build_component_ref (datum, component)))
    أرجع ref;

  /* See if there is a field or component with name COMPONENT.  */

  إذا (کد == رکورد_TYPE || کد == UNION_TYPE)
    {
      إذا (!COMPLETE_TYPE_P (type))
	{
	  c_incomplete_type_error (loc, NULL_درخت, type);
	  أرجع error_mark_گره;
	}

      فیلد_2 = lookup_فیلد (type, component);

      إذا (!فیلد_2)
	{
	  درخت guessed_id = lookup_فیلد_fuzzy (type, component);
	  إذا (guessed_id)
	    {
	      /* Attempt to provide a fixit replacement hint, if
		 we have a valid range for the component.  */
	      location_t reported_loc
		= (component_loc != UNKNOWN_LOCATION) ? component_loc : loc;
	      gcc_rich_location rich_loc (reported_loc);
	      إذا (component_loc != UNKNOWN_LOCATION)
		rich_loc.جمع_کن_fixit_misspelled_id (component_loc, guessed_id);
	      error_at (&rich_loc,
			"%qT has no member named %qE; did you mean %qE?",
			type, component, guessed_id);
	    }
	  وإلا
	    error_at (loc, "%qT has no member named %qE", type, component);
	  أرجع error_mark_گره;
	}

      /* Accessing elements of atomic structures or unions is undefined
	 behavior (C11 6.5.2.3#5).  */
      إذا (TYPE_ATOMIC (type) && c_inhibit_evaluation_warnings == 0)
	{
	  إذا (کد == رکورد_TYPE)
	    warning_at (loc, 0, "accessing a member %qE of an atomic "
			"structure %qE", component, datum);
	  وإلا
	    warning_at (loc, 0, "accessing a member %qE of an atomic "
			"union %qE", component, datum);
	}

      /* Chain the COMPONENT_REFs if necessary down to the FIELD.
	 This might be better solved in future the way the C++ front
	 end does it - by giving the anonymous entities each a
	 separate name and type, and then have build_component_ref
	 recursively call itself.  We can't do that here.  */
      افعل
	{
	  درخت subdatum = درخت_مقدار (فیلد_2);
	  صحيح quals;
	  درخت subtype;
	  منطقي use_datum_quals;

	  إذا (درخت_TYPE (subdatum) == error_mark_گره)
	    أرجع error_mark_گره;

	  /* If this is an rvalue, it does not have qualifiers in C
	     standard terms and we must avoid propagating such
	     qualifiers down to a non-lvalue array that is then
	     converted to a pointer.  */
	  use_datum_quals = (datum_lvalue
			     || درخت_کد (درخت_TYPE (subdatum)) != ARRAY_TYPE);

	  quals = TYPE_QUALS (strip_array_types (درخت_TYPE (subdatum)));
	  إذا (use_datum_quals)
	    quals |= TYPE_QUALS (درخت_TYPE (datum));
	  subtype = c_build_qualified_type (درخت_TYPE (subdatum), quals);

	  ref = build3 (COMPONENT_REF, subtype, datum, subdatum,
			NULL_درخت);
	  مجموعه_عبارت_LOCATION (ref, loc);

	  check_counted_by_attribute (loc, ref);

	  إذا (درخت_READONLY (subdatum)
	      || (use_datum_quals && درخت_READONLY (datum)))
	    درخت_READONLY (ref) = 1;
	  إذا (درخت_THIS_VOLATILE (subdatum)
	      || (use_datum_quals && درخت_THIS_VOLATILE (datum)))
	    درخت_THIS_VOLATILE (ref) = 1;

	  إذا (درخت_UNAVAILABLE (subdatum))
	    error_unavailable_use (subdatum, NULL_درخت);
	  وإلا إذا (درخت_DEPRECATED (subdatum))
	    warn_deprecated_use (subdatum, NULL_درخت);

	  datum = ref;

	  فیلد_2 = درخت_CHAIN (فیلد_2);
	}
      طالما (فیلد_2);

      أرجع ref;
    }
  وإلا إذا (should_suggest_deref_p (type))
    {
      /* Special-case the error message for "ptr.field" for the case
	 where the user has confused "." vs "->".  */
      rich_location richloc (سطر_جدول, loc);
      إذا (غیرمستقیم_REF_P (datum) && arrow_loc != UNKNOWN_LOCATION)
	{
	  richloc.جمع_کن_fixit_درج_before (arrow_loc, "(*");
	  richloc.جمع_کن_fixit_درج_after (arrow_loc, ")");
	  error_at (&richloc,
		    "%qE is a pointer to pointer; did you mean to dereference "
		    "it before applying %<->%> to it?",
		    درخت_عملوند (datum, 0));
	}
      وإلا
	{
	  /* "loc" should be the "." token.  */
	  richloc.جمع_کن_fixit_replace ("->");
	  error_at (&richloc,
		    "%qE is a pointer; did you mean to use %<->%>?",
		    datum);
	}
      أرجع error_mark_گره;
    }
  وإلا إذا (کد != ERROR_MARK)
    error_at (loc,
	      "request for member %qE in something not a structure or union",
	      component);

  أرجع error_mark_گره;
}

/* Given an expression PTR for a pointer, return an expression
   for the value pointed to.
   ERRORSTRING is the name of the operator to appear in error messages.

   LOC is the location to use for the generated tree.  */

درخت
build_غیرمستقیم_ref (location_t loc, درخت ptr, ref_operator errstring)
{
  درخت اشاره_گر = default_conversion (ptr);
  درخت type = درخت_TYPE (اشاره_گر);
  درخت ref;

  إذا (درخت_کد (type) == اشاره_گر_TYPE)
    {
      إذا (CONVERT_عبارت_P (اشاره_گر)
          || درخت_کد (اشاره_گر) == VIEW_CONVERT_عبارت)
	{
	  /* If a warning is issued, mark it to avoid duplicates from
	     the backend.  This only needs to be done at
	     warn_strict_aliasing > 2.  */
	  إذا (warn_strict_aliasing > 2)
	    إذا (strict_aliasing_warning (عبارت_LOCATION (اشاره_گر),
					 type, درخت_عملوند (اشاره_گر, 0)))
	      suppress_warning (اشاره_گر, OPT_Wstrict_aliasing_);
	}

      إذا (درخت_کد (اشاره_گر) == ADDR_عبارت
	  && (درخت_TYPE (درخت_عملوند (اشاره_گر, 0))
	      == درخت_TYPE (type)))
	{
	  ref = درخت_عملوند (اشاره_گر, 0);
	  protected_مجموعه_عبارت_location (ref, loc);
	  أرجع ref;
	}
      وإلا
	{
	  درخت t = درخت_TYPE (type);

	  ref = build1 (غیرمستقیم_REF, t, اشاره_گر);

	  إذا (VOID_TYPE_P (t) && c_inhibit_evaluation_warnings == 0)
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
	    = TYPE_VOLATILE (t) || درخت_SIDE_EFFECTS (اشاره_گر);
	  درخت_THIS_VOLATILE (ref) = TYPE_VOLATILE (t);
	  protected_مجموعه_عبارت_location (ref, loc);
	  أرجع ref;
	}
    }
  وإلا إذا (درخت_کد (اشاره_گر) != ERROR_MARK)
    invalid_indirection_error (loc, type, errstring);

  أرجع error_mark_گره;
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
build_array_ref (location_t loc, درخت array, درخت شاخص)
{
  درخت ret;
  منطقي swapped = خطأ;
  إذا (درخت_TYPE (array) == error_mark_گره
      || درخت_TYPE (شاخص) == error_mark_گره)
    أرجع error_mark_گره;

  إذا (درخت_کد (درخت_TYPE (array)) != ARRAY_TYPE
      && درخت_کد (درخت_TYPE (array)) != اشاره_گر_TYPE
      /* Allow vector[index] but not index[vector].  */
      && !gnu_وکتور_type_p (درخت_TYPE (array)))
    {
      إذا (درخت_کد (درخت_TYPE (شاخص)) != ARRAY_TYPE
	  && درخت_کد (درخت_TYPE (شاخص)) != اشاره_گر_TYPE)
	{
          error_at (loc,
            "subscripted value is neither array nor pointer nor vector");

	  أرجع error_mark_گره;
	}
      std::جابجا (array, شاخص);
      swapped = درست;
    }

  إذا (!INTEGRAL_TYPE_P (درخت_TYPE (شاخص)))
    {
      error_at (loc, "array subscript is not an integer");
      أرجع error_mark_گره;
    }

  إذا (درخت_کد (درخت_TYPE (درخت_TYPE (array))) == FUNCTION_TYPE)
    {
      error_at (loc, "subscripted value is pointer to function");
      أرجع error_mark_گره;
    }

  /* ??? Existing practice has been to warn only when the char
     index is syntactically the index, not for char[array].  */
  إذا (!swapped)
     warn_array_subscript_with_type_char (loc, شاخص);

  /* Apply default promotions *after* noticing character types.  */
  شاخص = default_conversion (شاخص);
  إذا (شاخص == error_mark_گره)
    أرجع error_mark_گره;

  gcc_assert (درخت_کد (درخت_TYPE (شاخص)) == INTEGER_TYPE
	      || درخت_کد (درخت_TYPE (شاخص)) == BITINT_TYPE);

  منطقي was_وکتور = وکتور_TYPE_P (درخت_TYPE (array));
  منطقي non_lvalue = convert_وکتور_مقصد_array_for_subscript (loc, &array, شاخص);

  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  إذا (درخت_کد (array) == COMPONENT_REF
      && handle_counted_by_p (array))
    array = handle_counted_by_for_component_ref (loc, array);

  إذا (درخت_کد (درخت_TYPE (array)) == ARRAY_TYPE)
    {
      درخت rval, type;

      /* An array that is indexed by a non-constant
	 cannot be stored in a register; we must be able to do
	 address arithmetic on its address.
	 Likewise an array of elements of variable size.  */
      إذا (درخت_کد (شاخص) != INTEGER_CST
	  || (COMPLETE_TYPE_P (درخت_TYPE (درخت_TYPE (array)))
	      && درخت_کد (TYPE_اندازه (درخت_TYPE (درخت_TYPE (array)))) != INTEGER_CST))
	{
	  إذا (!c_mark_addressable (array, درست, درست))
	    أرجع error_mark_گره;
	}
      /* An array that is indexed by a constant value which is not within
	 the array bounds cannot be stored in a register either; because we
	 would get a crash in store_bit_field/extract_bit_field when trying
	 to access a non-existent part of the register.  */
      إذا (درخت_کد (شاخص) == INTEGER_CST
	  && TYPE_DOMAIN (درخت_TYPE (array))
	  && !int_میگنجد_type_p (شاخص, TYPE_DOMAIN (درخت_TYPE (array))))
	{
	  إذا (!c_mark_addressable (array, خطأ, درست))
	    أرجع error_mark_گره;
	  /* ISO C2Y disallows a negative integer constant expression index
	     when array subscripting has an operand of array type.  */
	  إذا (flag_isoc2y
	      && !درخت_سرریز (شاخص)
	      && درخت_int_cst_sgn (شاخص) < 0)
	    error_at (loc, "array subscript is negative");
	}

      إذا ((pedantic || warn_c90_c99_compat || warn_c23_c2y_compat)
	  && ! was_وکتور)
	{
	  درخت foo = array;
	  طالما (درخت_کد (foo) == COMPONENT_REF)
	    foo = درخت_عملوند (foo, 0);
	  إذا ((VAR_P (foo) && C_DECL_ثبات (foo))
	      || (درخت_کد (foo) == COMPOUND_LITERAL_عبارت
		  && C_DECL_ثبات (COMPOUND_LITERAL_عبارت_DECL (foo))))
	    pedwarn_c23 (loc, OPT_Wpedantic,
			 "ISO C forbids subscripting %<register%> array "
			 "before C2Y");
	  وإلا إذا (!lvalue_p (foo))
	    pedwarn_c90 (loc, OPT_Wpedantic,
			 "ISO C90 forbids subscripting non-lvalue "
			 "array");
	}

      إذا (درخت_کد (درخت_TYPE (شاخص)) == BITINT_TYPE
	  && TYPE_PRECISION (درخت_TYPE (شاخص)) > TYPE_PRECISION (sizetype))
	شاخص = fold_convert (sizetype, شاخص);

      type = درخت_TYPE (درخت_TYPE (array));
      rval = build4 (ARRAY_REF, type, array, شاخص, NULL_درخت, NULL_درخت);
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
      protected_مجموعه_عبارت_location (ret, loc);
      إذا (non_lvalue)
	ret = non_lvalue_loc (loc, ret);
      أرجع ret;
    }
  وإلا
    {
      درخت ar = default_conversion (array);

      إذا (ar == error_mark_گره)
	أرجع ar;

      gcc_assert (درخت_کد (درخت_TYPE (ar)) == اشاره_گر_TYPE);
      gcc_assert (درخت_کد (درخت_TYPE (درخت_TYPE (ar))) != FUNCTION_TYPE);

      ret = build_غیرمستقیم_ref (loc, build_دودویی_op (loc, PLUS_عبارت, ar,
						      شاخص, خطأ),
				RO_ARRAY_INDEXING);
      إذا (non_lvalue)
	ret = non_lvalue_loc (loc, ret);
      أرجع ret;
    }
}

/* Build an OpenMP array section reference, creating an exact type for the
   resulting expression based on the element type and bounds if possible.  If
   we have variable bounds, create an incomplete array type for the result
   instead.  */

درخت
build_omp_array_section (location_t loc, درخت array, درخت شاخص, درخت درازی)
{
  درخت type = درخت_TYPE (array);
  gcc_assert (type);

  درخت sectype, eltype = درخت_TYPE (type);

  /* It's not an array or pointer type.  Just reuse the type of the original
     expression as the type of the array section (an error will be raised
     anyway, later).  */
  إذا (eltype == NULL_درخت || error_عملوند_p (eltype))
    sectype = درخت_TYPE (array);
  وإلا
    {
      درخت idxtype = NULL_درخت;

      إذا (شاخص != NULL_درخت
	  && درازی != NULL_درخت
	  && INTEGRAL_TYPE_P (درخت_TYPE (شاخص))
	  && INTEGRAL_TYPE_P (درخت_TYPE (درازی)))
	{
	  درخت کم = fold_convert (sizetype, شاخص);
	  درخت بالا = fold_convert (sizetype, درازی);
	  بالا = اندازه_binop (PLUS_عبارت, کم, بالا);
	  بالا = اندازه_binop (MINUS_عبارت, بالا, اندازه_one_گره);
	  idxtype = build_range_type (sizetype, کم, بالا);
	}
      وإلا إذا ((شاخص == NULL_درخت || integer_zerop (شاخص))
	       && درازی != NULL_درخت
	       && INTEGRAL_TYPE_P (درخت_TYPE (درازی)))
	idxtype = build_شاخص_type (درازی);

      gcc_assert (!error_عملوند_p (idxtype));

      sectype = c_build_array_type (eltype, idxtype);
    }

  أرجع build3_loc (loc, OMP_ARRAY_SECTION, sectype, array, شاخص, درازی);
}


/* Record that REF is used.  This is relevant for undeclared static
   function and declarations referenced from a non-local context.
   ADDRESS indicates whether the address is taken.  */

فراغ
mark_decl_استفاده_شده (درخت ref, منطقي آدرس)
{
  إذا (!ref || !DECL_P (ref) || درون_alignof)
    أرجع;

  /* Non-file-scope and non-local reference in nested function.  */
  منطقي nonloc_p = current_function_decl && DECL_CONTEXT (ref)
		  && DECL_CONTEXT (current_function_decl)
		  && DECL_CONTEXT (ref) != current_function_decl;

  /* An undeclared static function.  */
  منطقي static_p = درخت_کد (ref) == FUNCTION_DECL
		  && DECL_INITIAL (ref) == NULL_درخت
		  && DECL_EXTERNAL (ref)
		  && !درخت_عمومی (ref);

  إذا (!static_p && !nonloc_p)
    أرجع;

  /* If we may be in an unevaluated context, delay the decision.  */
  إذا (درون_sizeof || درون_typeof || درون_countof || درون_generic)
    أرجع رکورد_maybe_استفاده_شده_decl (ref, آدرس);

  إذا (static_p)
    C_DECL_استفاده_شده (ref) = 1;

  إذا (nonloc_p && (VAR_OR_FUNCTION_DECL_P (ref)
		   || درخت_کد (ref) == PARM_DECL))
    DECL_NONLOCAL (ref) = 1;

  /* Nothing to do anymore.  */
  إذا (!nonloc_p || C_FUNC_NONLOCAL_CONTEXT (current_function_decl))
    أرجع;

  /* Filter out the cases where referencing a non-local variable does not
     require a non-local context passed via the static chain.  */
  إذا (!c_type_variably_modified_p (درخت_TYPE (ref)))
    بدل (درخت_کد (ref))
      {
      حالة FUNCTION_DECL:
	/* Use of another local function that requires no context is ok.  */
	إذا (!C_FUNC_NONLOCAL_CONTEXT (ref) && DECL_INITIAL (ref))
	  أرجع;
	اكسر;
      حالة VAR_DECL:
	/* Static variables and constexpr are ok, but for the later only
	   when the address is not taken.  */
	إذا (درخت_STATIC (ref) || (C_DECL_DECLARED_CONSTEXPR (ref) && !آدرس))
	  أرجع;
	اكسر;
      حالة TYPE_DECL:
	/* A typedef is ok when not for a variably-modified type. */
	أرجع;
      حالة CONST_DECL:
	/* An enumeration constant is ok. */
	أرجع;
      حالة PARM_DECL:
	اكسر;
      حالة LABEL_DECL:
	اكسر;
      افتراضي:
	gcc_unreachable ();
    }

  /* Mark all parent functions up to the nesting level of the variable as
     as needing the non-local context.  */
  لكل (درخت cont = current_function_decl; cont; cont = DECL_CONTEXT (cont))
    {
      إذا (cont == DECL_CONTEXT (ref))
	اكسر;

      /* There should not be any other type of context used for function
	 except TRANSLATION_UNIT_DECL which we should be able to reach.  */
      gcc_checking_assert (درخت_کد (cont) == FUNCTION_DECL);

      إذا (درخت_کد (cont) == FUNCTION_DECL)
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
build_external_ref (location_t loc, درخت id, منطقي fun, درخت *type)
{
  درخت ref;
  درخت decl = lookup_name (id);

  /* In Objective-C, an instance variable (ivar) may be preferred to
     whatever lookup_name() found.  */
  decl = objc_lookup_ivar (decl, id);

  *type = عدم;
  إذا (decl && decl != error_mark_گره)
    {
      ref = decl;
      *type = درخت_TYPE (ref);
      إذا (DECL_P (decl) && C_DECL_UNDERSPECIFIED (decl))
	error_at (loc, "underspecified %qD referenced in its initializer",
		  decl);
    }
  وإلا إذا (fun)
    /* Implicit function declaration.  */
    ref = implicitly_declare (loc, id);
  وإلا إذا (decl == error_mark_گره)
    /* Don't complain about something that's already been
       complained about.  */
    أرجع error_mark_گره;
  وإلا
    {
      undeclared_variable (loc, id);
      أرجع error_mark_گره;
    }

  /* For an OpenMP map clause, we can get better diagnostics for decls with
     unmappable types if we return the decl with an error_mark_node type,
     rather than returning error_mark_node for the decl itself.  */
  إذا (درخت_TYPE (ref) == error_mark_گره
      && !c_omp_array_section_p)
    أرجع error_mark_گره;

  إذا (درخت_UNAVAILABLE (ref))
    error_unavailable_use (ref, NULL_درخت);
  وإلا إذا (درخت_DEPRECATED (ref))
    warn_deprecated_use (ref, NULL_درخت);

  /* Recursive call does not count as usage.  */
  إذا (ref != current_function_decl)
    {
      درخت_استفاده_شده (ref) = 1;
    }

  mark_decl_استفاده_شده (ref, خطأ);

  إذا (درخت_کد (ref) == CONST_DECL)
    {
      استفاده_شده_types_درج (درخت_TYPE (ref));

      إذا (warn_cxx_compat
	  && درخت_کد (درخت_TYPE (ref)) == ENUMERAL_TYPE
	  && C_TYPE_DEFINED_درون_STRUCT (درخت_TYPE (ref)))
	{
	  warning_at (loc, OPT_Wc___compat,
		      "enum constant defined in struct or union "
		      "is not visible in C++");
	  inform (DECL_منبع_LOCATION (ref), "enum constant defined here");
	}

      ref = DECL_INITIAL (ref);
      درخت_CONSTANT (ref) = 1;
    }
  /* C99 6.7.4p3: An inline definition of a function with external
     linkage ... shall not contain a reference to an identifier with
     internal linkage.  */
  وإلا إذا (current_function_decl != NULL_درخت
	   && DECL_DECLARED_INLINE_P (current_function_decl)
	   && DECL_EXTERNAL (current_function_decl)
	   && VAR_OR_FUNCTION_DECL_P (ref)
	   && (!VAR_P (ref) || درخت_STATIC (ref))
	   && ! درخت_عمومی (ref)
	   && DECL_CONTEXT (ref) != current_function_decl)
    رکورد_inline_static (loc, current_function_decl, ref,
			  csi_داخلی);

  أرجع ref;
}

ساكن بنية maybe_استفاده_شده_decl *maybe_استفاده_شده_decls;

/* Record that DECL, a reference seen inside sizeof or typeof or _Countof or
   _Generic, might be used if the operand of sizeof is a VLA type or the
   operand of typeof is a variably modified type or the operand of _Countof has
   a variable number of elements or the operand of _Generic is the one selected
   as the result.  */

ساكن فراغ
رکورد_maybe_استفاده_شده_decl (درخت decl, منطقي آدرس)
{
  بنية maybe_استفاده_شده_decl *t = XOBNEW (&parser_obstack, بنية maybe_استفاده_شده_decl);
  t->decl = decl;
  t->level = درون_sizeof + درون_typeof + درون_countof + درون_generic;
  t->آدرس = آدرس;
  t->بعدی = maybe_استفاده_شده_decls;
  maybe_استفاده_شده_decls = t;
}

/* Pop the stack of decls possibly used inside sizeof or typeof or _Countof or
   _Generic.  If USED is false, just discard them.  If it is true, mark them
   used (if no longer inside sizeof or typeof or _Countof or _Generic) or move
   them to the next level up (if still inside sizeof or typeof or _Countof or
   _Generic).  */

فراغ
برداشت_maybe_استفاده_شده (منطقي استفاده_شده)
{
  بنية maybe_استفاده_شده_decl *p = maybe_استفاده_شده_decls;
  صحيح cur_level = درون_sizeof + درون_typeof + درون_countof + درون_generic;
  طالما (p && p->level > cur_level)
    {
      إذا (استفاده_شده)
	{
	  إذا (cur_level == 0)
	    mark_decl_استفاده_شده (p->decl, p->آدرس);
	  وإلا
	    p->level = cur_level;
	}
      p = p->بعدی;
    }
  إذا (!استفاده_شده || cur_level == 0)
    maybe_استفاده_شده_decls = p;
}

/* Pop the stack of decls possibly used inside sizeof or typeof or _Countof or
   _Generic, without acting on them, and return the pointer to the previous top
   of the stack.  This for use at the end of a default generic association when
   it is not yet known whether the expression is used.  If it later turns out
   the expression is used (or treated as used before C23), restore_maybe_used
   should be called on the return value followed by pop_maybe_used (true);
   otherwise, the return value can be discarded.  */

بنية maybe_استفاده_شده_decl *
save_maybe_استفاده_شده ()
{
  بنية maybe_استفاده_شده_decl *p = maybe_استفاده_شده_decls, *orig = p;
  صحيح cur_level = درون_sizeof + درون_typeof + درون_countof + درون_generic;
  طالما (p && p->level > cur_level)
    p = p->بعدی;
  maybe_استفاده_شده_decls = p;
  أرجع orig;
}

/* Restore the stack of decls possibly used inside sizeof or typeof or _Countof
   or _Generic returned by save_maybe_used.  It is required that the stack is
   at exactly the point where it was left by save_maybe_used.  */

فراغ
restore_maybe_استفاده_شده (بنية maybe_استفاده_شده_decl *پشته)
{
  maybe_استفاده_شده_decls = پشته;
}

/* Return the result of sizeof applied to EXPR.  */

بنية c_عبارت
c_عبارت_sizeof_عبارت (location_t loc, بنية c_عبارت عبارت)
{
  بنية c_عبارت ret;
  إذا (عبارت.مقدار == error_mark_گره)
    {
      ret.مقدار = error_mark_گره;
      ret.original_کد = ERROR_MARK;
      ret.original_type = عدم;
      ret.m_decimal = 0;
      برداشت_maybe_استفاده_شده (خطأ);
    }
  وإلا
    {
      منطقي عبارت_const_operands = درست;

      إذا (درخت_کد (عبارت.مقدار) == PARM_DECL
	  && C_ARRAY_PARAMETER (عبارت.مقدار))
	{
	  auto_diagnostic_گروه d;
	  إذا (warning_at (loc, OPT_Wsizeof_array_آرگومان,
			  "%<sizeof%> on array function parameter %qE will "
			  "return size of %qT", عبارت.مقدار,
			  درخت_TYPE (عبارت.مقدار)))
	    inform (DECL_منبع_LOCATION (عبارت.مقدار), "declared here");
	}
      درخت folded_عبارت = c_fully_fold (عبارت.مقدار, require_constant_مقدار,
				       &عبارت_const_operands);
      ret.مقدار = c_sizeof (loc, درخت_TYPE (folded_عبارت));
      c_آخرین_sizeof_arg = عبارت.مقدار;
      c_آخرین_sizeof_loc = loc;
      ret.original_کد = SIZEOF_عبارت;
      ret.original_type = عدم;
      ret.m_decimal = 0;
      إذا (C_TYPE_VARIABLE_اندازه (درخت_TYPE (folded_عبارت)))
	{
	  /* sizeof is evaluated when given a vla (C99 6.5.3.4p2).  */
	  ret.مقدار = build2 (C_MAYBE_CONST_عبارت, درخت_TYPE (ret.مقدار),
			      folded_عبارت, ret.مقدار);
	  C_MAYBE_CONST_عبارت_NON_CONST (ret.مقدار) = !عبارت_const_operands;
	  مجموعه_عبارت_LOCATION (ret.مقدار, loc);
	}
      برداشت_maybe_استفاده_شده (C_TYPE_VARIABLE_اندازه (درخت_TYPE (folded_عبارت)));
    }
  أرجع ret;
}

/* Return the result of sizeof applied to T, a structure for the type
   name passed to sizeof (rather than the type itself).  LOC is the
   location of the original expression.  */

بنية c_عبارت
c_عبارت_sizeof_type (location_t loc, بنية c_type_name *t)
{
  درخت type;
  بنية c_عبارت ret;
  درخت type_عبارت = NULL_درخت;
  منطقي type_عبارت_const = درست;
  type = groktypename (t, &type_عبارت, &type_عبارت_const);
  ret.مقدار = c_sizeof (loc, type);
  c_آخرین_sizeof_arg = type;
  c_آخرین_sizeof_loc = loc;
  ret.original_کد = SIZEOF_عبارت;
  ret.original_type = عدم;
  ret.m_decimal = 0;
  إذا (type == error_mark_گره)
    {
      ret.مقدار = error_mark_گره;
      ret.original_کد = ERROR_MARK;
    }
  وإلا
  إذا ((type_عبارت || درخت_کد (ret.مقدار) == INTEGER_CST)
      && C_TYPE_VARIABLE_اندازه (type))
    {
      /* If the type is a [*] array, it is a VLA but is represented as
	 having a size of zero.  In such a case we must ensure that
	 the result of sizeof does not get folded to a constant by
	 c_fully_fold, because if the size is evaluated the result is
	 not constant and so constraints on zero or negative size
	 arrays must not be applied when this sizeof call is inside
	 another array declarator.  */
      إذا (!type_عبارت)
	type_عبارت = integer_zero_گره;
      ret.مقدار = build2 (C_MAYBE_CONST_عبارت, درخت_TYPE (ret.مقدار),
			  type_عبارت, ret.مقدار);
      C_MAYBE_CONST_عبارت_NON_CONST (ret.مقدار) = !type_عبارت_const;
    }
  برداشت_maybe_استفاده_شده (type != error_mark_گره
		  ? C_TYPE_VARIABLE_اندازه (type) : خطأ);
  أرجع ret;
}

ساكن منطقي
بالاترین_array_vla_p (const_درخت type)
{
  إذا (درخت_کد (type) != ARRAY_TYPE)
    أرجع خطأ;

  درخت d = TYPE_DOMAIN (type);

  إذا (!d)
    أرجع خطأ;
  إذا (!TYPE_MAX_مقدار (d))
    أرجع خطأ;

  أرجع درخت_کد (TYPE_MAX_مقدار (d)) != INTEGER_CST
	 || درخت_کد (TYPE_MIN_مقدار (d)) != INTEGER_CST;
}

/* Return the result of countof applied to EXPR.  */

بنية c_عبارت
c_عبارت_countof_عبارت (location_t loc, بنية c_عبارت عبارت)
{
  بنية c_عبارت ret;
  إذا (عبارت.مقدار == error_mark_گره)
    {
      ret.مقدار = error_mark_گره;
      ret.original_کد = ERROR_MARK;
      ret.original_type = عدم;
      ret.m_decimal = 0;
      برداشت_maybe_استفاده_شده (خطأ);
    }
  وإلا
    {
      منطقي عبارت_const_operands = درست;

      درخت folded_عبارت = c_fully_fold (عبارت.مقدار, require_constant_مقدار,
				       &عبارت_const_operands);
      ret.مقدار = c_countof_type (loc, درخت_TYPE (folded_عبارت));
      c_آخرین_sizeof_arg = عبارت.مقدار;
      c_آخرین_sizeof_loc = loc;
      ret.original_کد = COUNTOF_عبارت;
      ret.original_type = عدم;
      ret.m_decimal = 0;
      إذا (بالاترین_array_vla_p (درخت_TYPE (folded_عبارت)))
	{
	  /* countof is evaluated when given a vla.  */
	  ret.مقدار = build2 (C_MAYBE_CONST_عبارت, درخت_TYPE (ret.مقدار),
			      folded_عبارت, ret.مقدار);
	  C_MAYBE_CONST_عبارت_NON_CONST (ret.مقدار) = !عبارت_const_operands;
	  مجموعه_عبارت_LOCATION (ret.مقدار, loc);
	}
      برداشت_maybe_استفاده_شده (بالاترین_array_vla_p (درخت_TYPE (folded_عبارت)));
    }
  أرجع ret;
}

/* Return the result of countof applied to T, a structure for the type
   name passed to countof (rather than the type itself).  LOC is the
   location of the original expression.  */

بنية c_عبارت
c_عبارت_countof_type (location_t loc, بنية c_type_name *t)
{
  درخت type;
  بنية c_عبارت ret;
  درخت type_عبارت = NULL_درخت;
  منطقي type_عبارت_const = درست;
  type = groktypename (t, &type_عبارت, &type_عبارت_const);
  ret.مقدار = c_countof_type (loc, type);
  c_آخرین_sizeof_arg = type;
  c_آخرین_sizeof_loc = loc;
  ret.original_کد = COUNTOF_عبارت;
  ret.original_type = عدم;
  ret.m_decimal = 0;
  إذا (type == error_mark_گره)
    {
      ret.مقدار = error_mark_گره;
      ret.original_کد = ERROR_MARK;
    }
  وإلا
  إذا ((type_عبارت || درخت_کد (ret.مقدار) == INTEGER_CST)
      && بالاترین_array_vla_p (type))
    {
      /* If the type is a [*] array, it is a VLA but is represented as
	 having a size of zero.  In such a case we must ensure that
	 the result of countof does not get folded to a constant by
	 c_fully_fold, because if the number of elements is evaluated
	 the result is not constant and so
	 constraints on zero or negative size arrays must not be applied
	 when this countof call is inside another array declarator.  */
      إذا (!type_عبارت)
	type_عبارت = integer_zero_گره;
      ret.مقدار = build2 (C_MAYBE_CONST_عبارت, درخت_TYPE (ret.مقدار),
			  type_عبارت, ret.مقدار);
      C_MAYBE_CONST_عبارت_NON_CONST (ret.مقدار) = !type_عبارت_const;
    }
  برداشت_maybe_استفاده_شده (type != error_mark_گره ? بالاترین_array_vla_p (type) : خطأ);
  أرجع ret;
}

/* Return the result of maxof applied to T, a structure for the type
   name passed to maxof (rather than the type itself).  LOC is the
   location of the original expression.  */

بنية c_عبارت
c_عبارت_maxof_type (location_t loc, بنية c_type_name *t)
{
  درخت type;
  بنية c_عبارت ret;
  درخت type_عبارت = NULL_درخت;
  منطقي type_عبارت_const = درست;
  type = groktypename (t, &type_عبارت, &type_عبارت_const);
  ret.مقدار = c_maxof_type (loc, type);
  c_آخرین_sizeof_arg = type;
  c_آخرین_sizeof_loc = loc;
  ret.original_کد = MAXOF_عبارت;
  ret.original_type = عدم;
  ret.m_decimal = 0;
  إذا (type == error_mark_گره)
    {
      ret.مقدار = error_mark_گره;
      ret.original_کد = ERROR_MARK;
    }
  برداشت_maybe_استفاده_شده (type != error_mark_گره);
  أرجع ret;
}

/* Return the result of minof applied to T, a structure for the type
   name passed to minof (rather than the type itself).  LOC is the
   location of the original expression.  */

بنية c_عبارت
c_عبارت_minof_type (location_t loc, بنية c_type_name *t)
{
  درخت type;
  بنية c_عبارت ret;
  درخت type_عبارت = NULL_درخت;
  منطقي type_عبارت_const = درست;
  type = groktypename (t, &type_عبارت, &type_عبارت_const);
  ret.مقدار = c_minof_type (loc, type);
  c_آخرین_sizeof_arg = type;
  c_آخرین_sizeof_loc = loc;
  ret.original_کد = MINOF_عبارت;
  ret.original_type = عدم;
  ret.m_decimal = 0;
  إذا (type == error_mark_گره)
    {
      ret.مقدار = error_mark_گره;
      ret.original_کد = ERROR_MARK;
    }
  برداشت_maybe_استفاده_شده (type != error_mark_گره);
  أرجع ret;
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

  vec_alloc (v, list_درازی (params));
  لكل (; params; params = درخت_CHAIN (params))
    v->سریع_افزودن (درخت_مقدار (params));
  ret = c_build_function_call_vec (loc, vNULL, function, v, عدم);
  vec_free (v);
  أرجع ret;
}

/* Give a note about the location of the declaration of DECL,
   or, failing that, a pertinent declaration for FUNCTION_EXPR.  */

ساكن فراغ
inform_declaration (درخت decl, درخت function_عبارت)
{
  إذا (decl && (درخت_کد (decl) != FUNCTION_DECL
	       || !DECL_IS_UNDECLARED_BUILTIN (decl)))
    inform (DECL_منبع_LOCATION (decl), "declared here");
  وإلا إذا (function_عبارت)
    بدل (درخت_کد (function_عبارت))
      {
      افتراضي:
	اكسر;
      حالة COMPONENT_REF:
	/* Show the decl of the pertinent field (e.g. for callback
	   fields in a struct.  */
	{
	  درخت فیلد_decl = درخت_عملوند (function_عبارت, 1);
	  إذا (location_t loc = DECL_منبع_LOCATION (فیلد_decl))
	    inform (loc, "declared here");
	}
	اكسر;
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
  درخت name = NULL_درخت, نتیجه;
  درخت tem;
  صحيح nargs;
  درخت *argarray;


  /* Strip NON_LVALUE_EXPRs, etc., since we aren't using as an lvalue.  */
  STRIP_TYPE_NOPS (function);

  /* Convert anything with function type to a pointer-to-function.  */
  إذا (درخت_کد (function) == FUNCTION_DECL)
    {
      name = DECL_NAME (function);

      إذا (flag_tm)
	tm_malloc_replacement (function);
      fundecl = function;
      إذا (!orig_fundecl)
	orig_fundecl = fundecl;
      /* Atomic functions have type checking/casting already done.  They are
	 often rewritten and don't match the original parameter list.  */
      إذا (name && startswith (IDENTIFIER_اشاره_گر (name), "__atomic_"))
        origtypes = عدم;
    }
  إذا (درخت_کد (درخت_TYPE (function)) == FUNCTION_TYPE)
    function = function_مقصد_اشاره_گر_conversion (loc, function);

  /* For Objective-C, convert any calls via a cast to OBJC_TYPE_REF
     expressions, like those used for ObjC messenger dispatches.  */
  إذا (params && !params->is_خالی ())
    function = objc_rewrite_function_call (function, (*params)[0]);

  function = c_fully_fold (function, خطأ, عدم);

  fntype = درخت_TYPE (function);

  إذا (درخت_کد (fntype) == ERROR_MARK)
    أرجع error_mark_گره;

  إذا (!(درخت_کد (fntype) == اشاره_گر_TYPE
	&& درخت_کد (درخت_TYPE (fntype)) == FUNCTION_TYPE))
    {
      إذا (!flag_diagnostics_show_caret && !STATEMENT_CLASS_P (function))
	error_at (loc,
		  "called object %qE is not a function or function pointer",
		  function);
      وإلا إذا (DECL_P (function))
	{
	  auto_diagnostic_گروه d;
	  error_at (loc,
		    "called object %qD is not a function or function pointer",
		    function);
	  inform_declaration (function, NULL_درخت);
	}
      وإلا
	error_at (loc,
		  "called object is not a function or function pointer");
      أرجع error_mark_گره;
    }

  إذا (fundecl && درخت_THIS_VOLATILE (fundecl))
    current_function_returns_abnormally = 1;

  /* fntype now gets the type of function pointed to.  */
  fntype = درخت_TYPE (fntype);
  درخت return_type = درخت_TYPE (fntype);

  /* Convert the parameters to the types declared in the
     function prototype, or apply default promotions.  */

  nargs = convert_arguments (loc, arg_loc, fntype, params,
			     origtypes, function, fundecl);
  إذا (nargs < 0)
    أرجع error_mark_گره;

  /* Check that the function is called through a compatible prototype.
     If it is not, warn.  */
  إذا (CONVERT_عبارت_P (function)
      && درخت_کد (tem = درخت_عملوند (function, 0)) == ADDR_عبارت
      && درخت_کد (tem = درخت_عملوند (tem, 0)) == FUNCTION_DECL
      && !comptypes (fntype, درخت_TYPE (tem)))
    {
      /* This situation leads to run-time undefined behavior.  We can't,
	 therefore, simply error unless we can prove that all possible
	 executions of the program must execute the code.  */
      warning_at (loc, 0, "function called through a non-compatible type");

      إذا (VOID_TYPE_P (return_type)
	  && TYPE_QUALS (return_type) != TYPE_UNQUALIFIED)
	pedwarn (loc, 0,
		 "function with qualified void return type called");
     }

  argarray = vec_امن_آدرس (params);

  /* Check that arguments to builtin functions match the expectations.  */
  إذا (fundecl
      && fndecl_built_درون_p (fundecl)
      && !check_builtin_function_arguments (loc, arg_loc, fundecl,
					    orig_fundecl, nargs, argarray))
    أرجع error_mark_گره;

  /* Check that the arguments to the function are valid.  */
  منطقي warned_p = check_function_arguments (loc, fundecl, fntype,
					    nargs, argarray, &arg_loc,
					    comptypes);

  إذا (TYPE_QUALS (return_type) != TYPE_UNQUALIFIED
      && !VOID_TYPE_P (return_type))
    return_type = c_build_qualified_type (return_type, TYPE_UNQUALIFIED);
  إذا (name != NULL_درخت
      && startswith (IDENTIFIER_اشاره_گر (name), "__builtin_"))
    {
      إذا (require_constant_مقدار)
	نتیجه
	  = fold_build_call_array_initializer_loc (loc, return_type,
						   function, nargs, argarray);
      وإلا
	نتیجه = fold_build_call_array_loc (loc, return_type,
					    function, nargs, argarray);
      إذا (درخت_کد (نتیجه) == NOP_عبارت
	  && درخت_کد (درخت_عملوند (نتیجه, 0)) == INTEGER_CST)
	STRIP_TYPE_NOPS (نتیجه);
    }
  وإلا
    نتیجه = build_call_array_loc (loc, return_type,
				   function, nargs, argarray);
  /* If -Wnonnull warning has been diagnosed, avoid diagnosing it again
     later.  */
  إذا (warned_p && درخت_کد (نتیجه) == CALL_عبارت)
    suppress_warning (نتیجه, OPT_Wnonnull);

  /* In this improbable scenario, a nested function returns a VM type.
     Create a TARGET_EXPR so that the call always has a LHS, much as
     what the C++ FE does for functions returning non-PODs.  */
  إذا (c_type_variably_modified_p (درخت_TYPE (fntype)))
    {
      درخت tmp = create_tmp_var_raw (درخت_TYPE (fntype));
      نتیجه = build4 (هدف_عبارت, درخت_TYPE (fntype), tmp, نتیجه,
		       NULL_درخت, NULL_درخت);
    }

  إذا (VOID_TYPE_P (درخت_TYPE (نتیجه)))
    {
      إذا (TYPE_QUALS (درخت_TYPE (نتیجه)) != TYPE_UNQUALIFIED)
	pedwarn (loc, 0,
		 "function with qualified void return type called");
      أرجع نتیجه;
    }
  أرجع require_complete_type (loc, نتیجه);
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
  إذا (درخت_کد (function) == FUNCTION_DECL)
    {
      /* Implement type-directed function overloading for builtins.
	 resolve_overloaded_builtin and targetm.resolve_overloaded_builtin
	 handle all the type checking.  The result is a complete expression
	 that implements this function call.  */
      درخت tem = resolve_overloaded_builtin (loc, function, params);
      إذا (tem)
	أرجع tem;
    }
  أرجع build_function_call_vec (loc, arg_loc, function, params, origtypes);
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

ساكن درخت
convert_آرگومان (location_t ploc, درخت function, درخت fundecl,
		  درخت type, درخت origtype, درخت val, درخت valtype,
		  منطقي npc, درخت rname, صحيح parmnum, صحيح argnum,
		  منطقي excess_precision, صحيح warnopt)
{
  /* Formal parm type is specified by a function prototype.  */

  إذا (type == error_mark_گره || !COMPLETE_TYPE_P (type))
    {
      error_at (ploc, "type of formal parameter %d is incomplete",
		parmnum + 1);
      أرجع error_mark_گره;
    }

  /* Optionally warn about conversions that differ from the default
     conversions.  */
  إذا (warn_traditional_conversion || warn_traditional)
    {
      إذا (INTEGRAL_TYPE_P (type)
	  && SCALAR_FLOAT_TYPE_P (valtype))
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as integer rather "
		    "than floating due to prototype",
		    argnum, rname);
      إذا (INTEGRAL_TYPE_P (type)
	  && درخت_کد (valtype) == COMPLEX_TYPE)
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as integer rather "
		    "than complex due to prototype",
		    argnum, rname);
      وإلا إذا (درخت_کد (type) == COMPLEX_TYPE
	       && SCALAR_FLOAT_TYPE_P (valtype))
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as complex rather "
		    "than floating due to prototype",
		    argnum, rname);
      وإلا إذا (SCALAR_FLOAT_TYPE_P (type)
	       && INTEGRAL_TYPE_P (valtype))
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as floating rather "
		    "than integer due to prototype",
		    argnum, rname);
      وإلا إذا (درخت_کد (type) == COMPLEX_TYPE
	       && INTEGRAL_TYPE_P (valtype))
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as complex rather "
		    "than integer due to prototype",
		    argnum, rname);
      وإلا إذا (SCALAR_FLOAT_TYPE_P (type)
	       && درخت_کد (valtype) == COMPLEX_TYPE)
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as floating rather "
		    "than complex due to prototype",
		    argnum, rname);
      /* ??? At some point, messages should be written about
	 conversions between complex types, but that's too messy
	 to do now.  */
      وإلا إذا (SCALAR_FLOAT_TYPE_P (type)
	       && SCALAR_FLOAT_TYPE_P (valtype))
	{
	  بیعلامت صحيح formal_prec = TYPE_PRECISION (type);

	  /* Warn if any argument is passed as `float',
	     since without a prototype it would be `double'.  */
	  إذا (formal_prec == TYPE_PRECISION (float_type_گره)
	      && type != dfloat32_type_گره)
	    warning_at (ploc, 0,
			"passing argument %d of %qE as %<float%> "
			"rather than %<double%> due to prototype",
			argnum, rname);

	  /* Warn if mismatch between argument and prototype
	     for decimal float types.  Warn of conversions with
	     binary float types and of precision narrowing due to
	     prototype.  */
	  وإلا إذا (type != valtype
		   && (type == dfloat32_type_گره
		       || type == dfloat64_type_گره
		       || type == dfloat128_type_گره
		       || valtype == dfloat32_type_گره
		       || valtype == dfloat64_type_گره
		       || valtype == dfloat128_type_گره)
		   && (formal_prec
		       <= TYPE_PRECISION (valtype)
		       || (type == dfloat128_type_گره
			   && (valtype
			       != dfloat64_type_گره
			       && (valtype
				   != dfloat32_type_گره)))
		       || (type == dfloat64_type_گره
			   && (valtype
			       != dfloat32_type_گره))))
	    warning_at (ploc, 0,
			"passing argument %d of %qE as %qT "
			"rather than %qT due to prototype",
			argnum, rname, type, valtype);

	}
      /* Detect integer changing in width or signedness.
	 These warnings are only activated with
	 -Wtraditional-conversion, not with -Wtraditional.  */
      وإلا إذا (warn_traditional_conversion
	       && INTEGRAL_TYPE_P (type)
	       && INTEGRAL_TYPE_P (valtype))
	{
	  بیعلامت صحيح formal_prec = TYPE_PRECISION (type);
	  درخت would_have_been = default_conversion (val);
	  درخت type1 = درخت_TYPE (would_have_been);

	  إذا (val == error_mark_گره)
	    /* VAL could have been of incomplete type.  */;
	  وإلا إذا (درخت_کد (type) == ENUMERAL_TYPE
		   && (TYPE_MAIN_VARIANT (type)
		       == TYPE_MAIN_VARIANT (valtype)))
	    /* No warning if function asks for enum
	       and the actual arg is that enum type.  */
	    ;
	  وإلا إذا (formal_prec != TYPE_PRECISION (type1))
	    warning_at (ploc, OPT_Wtraditional_conversion,
			"passing argument %d of %qE "
			"with different width due to prototype",
			argnum, rname);
	  وإلا إذا (TYPE_UNSIGNED (type) == TYPE_UNSIGNED (type1))
	    ;
	  /* Don't complain if the formal parameter type
	     is an enum, because we can't tell now whether
	     the value was an enum--even the same enum.  */
	  وإلا إذا (درخت_کد (type) == ENUMERAL_TYPE)
	    ;
	  وإلا إذا (درخت_کد (val) == INTEGER_CST
		   && int_میگنجد_type_p (val, type))
	    /* Change in signedness doesn't matter
	       if a constant value is unaffected.  */
	    ;
	  /* If the value is extended from a narrower
	     unsigned type, it doesn't matter whether we
	     pass it as signed or unsigned; the value
	     certainly is the same either way.  */
	  وإلا إذا (TYPE_PRECISION (valtype) < TYPE_PRECISION (type)
		   && TYPE_UNSIGNED (valtype))
	    ;
	  وإلا إذا (TYPE_UNSIGNED (type))
	    warning_at (ploc, OPT_Wtraditional_conversion,
			"passing argument %d of %qE "
			"as unsigned due to prototype",
			argnum, rname);
	  وإلا
	    warning_at (ploc, OPT_Wtraditional_conversion,
			"passing argument %d of %qE "
			"as signed due to prototype",
			argnum, rname);
	}
    }

  /* Possibly restore an EXCESS_PRECISION_EXPR for the
     sake of better warnings from convert_and_check.  */
  إذا (excess_precision)
    val = build1 (EXCESS_PRECISION_عبارت, valtype, val);

  درخت parmval = convert_for_assignment (ploc, ploc, type,
					 val, origtype, ic_argpass,
					 npc, fundecl, function,
					 parmnum + 1, warnopt);
  أرجع parmval;
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

ساكن صحيح
convert_arguments (location_t loc, vec<location_t> arg_loc, درخت fntype,
		   vec<درخت, va_gc> *مقادیر, vec<درخت, va_gc> *origtypes,
		   درخت function, درخت fundecl)
{
  درخت typelist = TYPE_ARG_TYPES (fntype);
  بیعلامت صحيح parmnum;
  منطقي error_آرگومانها = خطأ;
  ثابت منطقي type_generic = fundecl
    && lookup_attribute ("type generic", TYPE_صفات (درخت_TYPE (fundecl)));
  منطقي type_generic_remove_excess_precision = خطأ;
  منطقي type_generic_سرریز_p = خطأ;
  منطقي type_generic_بیت_query = خطأ;
  درخت selector;

  /* Change pointer to function to the function itself for
     diagnostics.  */
  إذا (درخت_کد (function) == ADDR_عبارت
      && درخت_کد (درخت_عملوند (function, 0)) == FUNCTION_DECL)
    function = درخت_عملوند (function, 0);

  /* Handle an ObjC selector specially for diagnostics.  */
  selector = objc_پیام_selector ();

  /* For a call to a built-in function declared without a prototype,
     set to the built-in function's argument list.  */
  درخت builtin_typelist = NULL_درخت;

  /* For type-generic built-in functions, determine whether excess
     precision should be removed (classification) or not
     (comparison).  */
  إذا (fundecl
      && fndecl_built_درون_p (fundecl, BUILT_درون_نرمال))
    {
      built_درون_function کد = DECL_FUNCTION_کد (fundecl);
      إذا (C_DECL_BUILTIN_PROTOTYPE (fundecl))
	{
	  /* For a call to a built-in function declared without a prototype
	     use the types of the parameters of the internal built-in to
	     match those of the arguments to.  */
	  إذا (درخت bdecl = builtin_decl_explicit (کد))
	    builtin_typelist = TYPE_ARG_TYPES (درخت_TYPE (bdecl));
	}

      /* For type-generic built-in functions, determine whether excess
	 precision should be removed (classification) or not
	 (comparison).  */
      إذا (type_generic)
	بدل (کد)
	  {
	  حالة BUILT_درون_ISFINITE:
	  حالة BUILT_درون_ISINF:
	  حالة BUILT_درون_ISINF_SIGN:
	  حالة BUILT_درون_ISNAN:
	  حالة BUILT_درون_ISNORMAL:
	  حالة BUILT_درون_ISSIGNALING:
	  حالة BUILT_درون_FPCLASSIFY:
	    type_generic_remove_excess_precision = درست;
	    اكسر;

	  حالة BUILT_درون_جمع_کن_سرریز_P:
	  حالة BUILT_درون_SUB_سرریز_P:
	  حالة BUILT_درون_MUL_سرریز_P:
	    /* The last argument of these type-generic builtins
	       should not be promoted.  */
	    type_generic_سرریز_p = درست;
	    اكسر;

	  حالة BUILT_درون_CLZG:
	  حالة BUILT_درون_CTZG:
	  حالة BUILT_درون_CLRSBG:
	  حالة BUILT_درون_FFSG:
	  حالة BUILT_درون_PARITYG:
	  حالة BUILT_درون_POPCOUNTG:
	    /* The first argument of these type-generic builtins
	       should not be promoted.  */
	    type_generic_بیت_query = درست;
	    اكسر;

	  افتراضي:
	    اكسر;
	  }
    }

  /* Scan the given expressions (VALUES) and types (TYPELIST), producing
     individual converted arguments.  */

  درخت typetail, builtin_typetail, val;
  لكل (typetail = typelist,
	 builtin_typetail = builtin_typelist,
	 parmnum = 0;
       مقادیر && مقادیر->iterate (parmnum, &val);
       ++parmnum)
    {
      /* The type of the function parameter (if it was declared with one).  */
      درخت type = typetail ? درخت_مقدار (typetail) : NULL_درخت;
      /* The type of the built-in function parameter (if the function
	 is a built-in).  Used to detect type incompatibilities in
	 calls to built-ins declared without a prototype.  */
      درخت builtin_type = (builtin_typetail
			   ? درخت_مقدار (builtin_typetail) : NULL_درخت);
      /* The original type of the argument being passed to the function.  */
      درخت valtype = درخت_TYPE (val);
      /* The called function (or function selector in Objective C).  */
      درخت rname = function;
      صحيح argnum = parmnum + 1;
      ثابت حرف *invalid_func_diag;
      /* Set for EXCESS_PRECISION_EXPR arguments.  */
      منطقي excess_precision = خطأ;
      /* The value of the argument after conversion to the type
	 of the function parameter it is passed to.  */
      درخت parmval;
      /* Some __atomic_* builtins have additional hidden argument at
	 position 0.  */
      location_t ploc
	= !arg_loc.is_خالی () && مقادیر->درازی () == arg_loc.درازی ()
	  ? expansion_نقطه_location_if_درون_system_سرآیند (arg_loc[parmnum])
	  : درون_داد_location;

      إذا (type == void_type_گره)
	{
	  auto_diagnostic_گروه d;
	  صحيح رقم_expected = parmnum;
	  صحيح رقم_actual = مقادیر->درازی ();
	  gcc_rich_location rich_loc (loc);
	  إذا (ploc != درون_داد_location)
	    rich_loc.جمع_کن_range (ploc);
	  إذا (selector)
	    error_at (&rich_loc,
		      "too many arguments to method %qE; expected %i, have %i",
		      selector, رقم_expected, رقم_actual);
	  وإلا
	    error_at (&rich_loc,
		      "too many arguments to function %qE; expected %i, have %i",
		      function, رقم_expected, رقم_actual);
	  inform_declaration (fundecl, function);
	  أرجع error_آرگومانها ? -1 : (صحيح) parmnum;
	}

      إذا (builtin_type == void_type_گره)
	{
	  auto_diagnostic_گروه d;
	  إذا (warning_at (loc, OPT_Wbuiltin_declaration_mismatch,
			  "too many arguments to built-in function %qE "
			  "expecting %d", function, parmnum))
	    inform_declaration (fundecl, function);
	  builtin_typetail = NULL_درخت;
	}

      إذا (!typetail && parmnum == 0 && !TYPE_NO_NAMED_آرگومانها_STDARG_P (fntype)
	  && !(fundecl && fndecl_built_درون_p (fundecl)))
	{
	  auto_diagnostic_گروه d;
	  منطقي warned;
	  إذا (selector)
	    warned = warning_at (loc, OPT_Wdeprecated_non_prototype,
				 "ISO C23 does not allow arguments"
				 " for method %qE declared without parameters",
				 function);
	  وإلا
	    warned = warning_at (loc, OPT_Wdeprecated_non_prototype,
				 "ISO C23 does not allow arguments"
				 " for function %qE declared without parameters",
				 function);
	  إذا (warned)
	    inform_declaration (fundecl, function);
	}

      إذا (selector && argnum > 2)
	{
	  rname = selector;
	  argnum -= 2;
	}

      /* Determine if VAL is a null pointer constant before folding it.  */
      منطقي npc = null_اشاره_گر_constant_p (val);

      /* If there is excess precision and a prototype, convert once to
	 the required type rather than converting via the semantic
	 type.  Likewise without a prototype a float value represented
	 as long double should be converted once to double.  But for
	 type-generic classification functions excess precision must
	 be removed here.  */
      إذا (درخت_کد (val) == EXCESS_PRECISION_عبارت
	  && (type || !type_generic || !type_generic_remove_excess_precision))
	{
	  val = درخت_عملوند (val, 0);
	  excess_precision = درست;
	}
      val = c_fully_fold (val, خطأ, عدم);
      STRIP_TYPE_NOPS (val);

      val = require_complete_type (ploc, val);

      /* Some floating-point arguments must be promoted to double when
	 no type is specified by a prototype.  This applies to
	 arguments of type float, and to architecture-specific types
	 (ARM __fp16), but not to _FloatN or _FloatNx types.  */
      منطقي promote_float_arg = خطأ;
      إذا (type == NULL_درخت
	  && درخت_کد (valtype) == REAL_TYPE
	  && (TYPE_PRECISION (valtype)
	      <= TYPE_PRECISION (double_type_گره))
	  && TYPE_MAIN_VARIANT (valtype) != double_type_گره
	  && TYPE_MAIN_VARIANT (valtype) != long_double_type_گره
	  && !DECIMAL_FLOAT_نما_P (TYPE_نما (valtype)))
	{
	  /* Promote this argument, unless it has a _FloatN or
	     _FloatNx type.  */
	  promote_float_arg = درست;
	  لكل (صحيح i = 0; i < رقم_FLOATN_NX_TYPES; i++)
	    إذا (TYPE_MAIN_VARIANT (valtype) == FLOATN_NX_TYPE_گره (i))
	      {
		promote_float_arg = خطأ;
		اكسر;
	      }
	  /* Don't promote __bf16 either.  */
	  إذا (TYPE_MAIN_VARIANT (valtype) == bfloat16_type_گره)
	    promote_float_arg = خطأ;
	}

      إذا (type != NULL_درخت)
	{
	  درخت origtype = (!origtypes) ? NULL_درخت : (*origtypes)[parmnum];
	  parmval = convert_آرگومان (ploc, function, fundecl, type, origtype,
				      val, valtype, npc, rname, parmnum, argnum,
				      excess_precision, 0);
	}
      /* A NULLPTR type is just a nullptr always.  */
      وإلا إذا (درخت_کد (درخت_TYPE (val)) == NULLPTR_TYPE)
	parmval = omit_one_عملوند_loc (ploc, درخت_TYPE (val), nullptr_گره, val);
      وإلا إذا (promote_float_arg)
        {
	  إذا (type_generic)
	    parmval = val;
	  وإلا
	    {
	      /* Convert `float' to `double'.  */
	      إذا (warn_double_promotion && !c_inhibit_evaluation_warnings)
		warning_at (ploc, OPT_Wdouble_promotion,
			    "implicit conversion from %qT to %qT when passing "
			    "argument to function",
			    valtype, double_type_گره);
	      parmval = convert (double_type_گره, val);
	    }
	}
      وإلا إذا ((excess_precision && !type_generic)
	       || (type_generic_سرریز_p && parmnum == 2)
	       || (type_generic_بیت_query && parmnum == 0))
	/* A "double" argument with excess precision being passed
	   without a prototype or in variable arguments.
	   The last argument of __builtin_*_overflow_p should not be
	   promoted, similarly the first argument of
	   __builtin_{clz,ctz,clrsb,ffs,parity,popcount}g.  */
	parmval = convert (valtype, val);
      وإلا إذا ((invalid_func_diag =
		targetm.calls.invalid_arg_for_unprototyped_fn (typelist, fundecl, val)))
	{
	  error (invalid_func_diag);
	  أرجع -1;
	}
      وإلا إذا (درخت_کد (val) == ADDR_عبارت && reject_gcc_builtin (val))
	{
	  أرجع -1;
	}
      وإلا
	/* Convert `short' and `char' to full-size `int'.  */
	parmval = default_conversion (val);

      (*مقادیر)[parmnum] = parmval;
      إذا (parmval == error_mark_گره)
	error_آرگومانها = درست;

      إذا (!type && builtin_type && درخت_کد (builtin_type) != VOID_TYPE)
	{
	  /* For a call to a built-in function declared without a prototype,
	     perform the conversions from the argument to the expected type
	     but issue warnings rather than errors for any mismatches.
	     Ignore the converted argument and use the PARMVAL obtained
	     above by applying default conversions instead.  */
	  درخت origtype = (!origtypes) ? NULL_درخت : (*origtypes)[parmnum];
	  convert_آرگومان (ploc, function, fundecl, builtin_type, origtype,
			    val, valtype, npc, rname, parmnum, argnum,
			    excess_precision,
			    OPT_Wbuiltin_declaration_mismatch);
	}

      إذا (typetail)
	typetail = درخت_CHAIN (typetail);

      إذا (builtin_typetail)
	builtin_typetail = درخت_CHAIN (builtin_typetail);
    }

  gcc_assert (parmnum == vec_امن_درازی (مقادیر));

  إذا (typetail != NULL_درخت && درخت_مقدار (typetail) != void_type_گره)
    {
      /* Not enough args.
	 Determine minimum number of arguments required.  */
      صحيح min_expected_رقم = 0;
      منطقي at_کمترین_p = خطأ;
      درخت iter = typelist;
      طالما (درست)
	{
	  إذا (!iter)
	    {
	      /* Variadic arguments; stop iterating.  */
	      at_کمترین_p = درست;
	      اكسر;
	    }
	  إذا (iter == void_list_گره)
	    /* End of arguments; stop iterating.  */
	    اكسر;
	  ++min_expected_رقم;
	  iter = درخت_CHAIN (iter);
	}
      auto_diagnostic_گروه d;
      صحيح actual_رقم = vec_امن_درازی (مقادیر);
      error_at (loc,
		at_کمترین_p
		? G_("too few arguments to function %qE; expected at least %i, have %i")
		: G_("too few arguments to function %qE; expected %i, have %i"),
		function, min_expected_رقم, actual_رقم);
      inform_declaration (fundecl, function);
      أرجع -1;
    }

  إذا (builtin_typetail && درخت_مقدار (builtin_typetail) != void_type_گره)
    {
      بیعلامت nargs = parmnum;
      لكل (درخت t = builtin_typetail; t; t = درخت_CHAIN (t))
	++nargs;

      auto_diagnostic_گروه d;
      إذا (warning_at (loc, OPT_Wbuiltin_declaration_mismatch,
		      "too few arguments to built-in function %qE "
		      "expecting %u", function, nargs - 1))
	inform_declaration (fundecl, function);
    }

  أرجع error_آرگومانها ? -1 : (صحيح) parmnum;
}

/* This is the entry point used by the parser to build unary operators
   in the input.  CODE, a tree_code, specifies the unary operator, and
   ARG is the operand.  For unary plus, the C parser currently uses
   CONVERT_EXPR for code.

   LOC is the location to use for the tree generated.
*/

بنية c_عبارت
parser_build_unary_op (location_t loc, تعداد درخت_کد_2 کد, بنية c_عبارت arg)
{
  بنية c_عبارت نتیجه;

  نتیجه.original_کد = کد;
  نتیجه.original_type = عدم;
  نتیجه.m_decimal = 0;

  إذا (reject_gcc_builtin (arg.مقدار))
    {
      نتیجه.مقدار = error_mark_گره;
    }
  وإلا
    {
      نتیجه.مقدار = build_unary_op (loc, کد, arg.مقدار, خطأ);

      إذا (درخت_سرریز_P (نتیجه.مقدار) && !درخت_سرریز_P (arg.مقدار))
	سرریز_warning (loc, نتیجه.مقدار, arg.مقدار);
    }

  /* We are typically called when parsing a prefix token at LOC acting on
     ARG.  Reflect this by updating the source range of the result to
     start at LOC and end at the end of ARG.  */
  مجموعه_c_عبارت_منبع_range (&نتیجه,
			   loc, arg.get_پایان ());

  أرجع نتیجه;
}

/* Returns true if TYPE is a character type, *not* including wchar_t.  */

منطقي
char_type_p (درخت type)
{
  أرجع (type == char_type_گره
	  || type == unsigned_char_type_گره
	  || type == signed_char_type_گره
	  || type == char16_type_گره
	  || type == char32_type_گره);
}

/* This is the entry point used by the parser to build binary operators
   in the input.  CODE, a tree_code, specifies the binary operator, and
   ARG1 and ARG2 are the operands.  In addition to constructing the
   expression, we check for operands that were written with other binary
   operators in a way that is likely to confuse the user.  ORIG_ARG1 is
   the original first operand for TRUTH_{AND,OR}IF_EXPR before it is
   converted to truth value, otherwise NULL_TREE.

   LOCATION is the location of the binary operator.  */

بنية c_عبارت
parser_build_دودویی_op (location_t location, تعداد درخت_کد_2 کد,
			بنية c_عبارت arg1, بنية c_عبارت arg2, درخت orig_arg1)
{
  بنية c_عبارت نتیجه;
  نتیجه.m_decimal = 0;

  تعداد درخت_کد_2 code1 = arg1.original_کد;
  تعداد درخت_کد_2 code2 = arg2.original_کد;
  درخت type1 = (arg1.original_type
                ? arg1.original_type
                : درخت_TYPE (arg1.مقدار));
  درخت type2 = (arg2.original_type
                ? arg2.original_type
                : درخت_TYPE (arg2.مقدار));

  نتیجه.مقدار = build_دودویی_op (location, کد,
				  arg1.مقدار, arg2.مقدار, درست);
  نتیجه.original_کد = کد;
  نتیجه.original_type = عدم;
  نتیجه.m_decimal = 0;

  إذا (درخت_کد (نتیجه.مقدار) == ERROR_MARK)
    {
      مجموعه_c_عبارت_منبع_range (&نتیجه,
			       arg1.get_شروع (),
			       arg2.get_پایان ());
      أرجع نتیجه;
    }

  إذا (location != UNKNOWN_LOCATION)
    protected_مجموعه_عبارت_location (نتیجه.مقدار, location);

  مجموعه_c_عبارت_منبع_range (&نتیجه,
			   arg1.get_شروع (),
			   arg2.get_پایان ());

  /* Check for cases such as x+y<<z which users are likely
     to misinterpret.  */
  إذا (warn_parentheses)
    warn_about_parentheses (location, کد, code1, arg1.مقدار, code2,
			    arg2.مقدار);

  إذا (warn_logical_op)
    warn_logical_operator (location, کد, درخت_TYPE (نتیجه.مقدار),
			   code1, arg1.مقدار, code2, arg2.مقدار);

  إذا (warn_constant_logical_عملوند
      && (کد == TRUTH_ANDIF_عبارت || کد == TRUTH_ORIF_عبارت)
      && INTEGRAL_NB_TYPE_P (type1)
      && INTEGRAL_NB_TYPE_P (type2))
    {
      ثابت حرف *name = کد == TRUTH_ANDIF_عبارت ? "&&" : "||";
      إذا (orig_arg1 == NULL_درخت)
	orig_arg1 = arg1.مقدار;
      خودکار enum_other_than_0_1 = [] (درخت type) {
	إذا (درخت_کد (type) != ENUMERAL_TYPE)
	  أرجع خطأ;
	لكل (درخت l = TYPE_مقادیر (type); l; l = درخت_CHAIN (l))
	  {
	    درخت v = DECL_INITIAL (درخت_مقدار (l));
	    إذا (!integer_zerop (v) && !integer_onep (v))
	      أرجع درست;
	  }
	أرجع خطأ;
      };
      خودکار diagnose_constant_logical_عملوند = [=] (درخت val, درخت type) {
	إذا (درخت_کد (val) != INTEGER_CST || integer_zerop (val))
	  أرجع خطأ;
	إذا (integer_onep (val) && !enum_other_than_0_1 (type))
	  أرجع خطأ;
	gcc_rich_location richloc (location);
	richloc.جمع_کن_fixit_replace (name + 1);
	auto_diagnostic_گروه d;
	إذا (warning_at (location, OPT_Wconstant_logical_عملوند,
			"use of logical %qs with constant operand %qE",
			name, val))
	  inform (&richloc, "use %qs for bitwise operation", name + 1);
	أرجع درست;
      };
      إذا (!diagnose_constant_logical_عملوند (arg2.مقدار, type2))
	diagnose_constant_logical_عملوند (orig_arg1, type1);
    }

  إذا (warn_tautological_compare)
    {
      درخت lhs = arg1.مقدار;
      درخت rhs = arg2.مقدار;
      إذا (درخت_کد (lhs) == C_MAYBE_CONST_عبارت)
	{
	  إذا (C_MAYBE_CONST_عبارت_PRE (lhs) != NULL_درخت
	      && درخت_SIDE_EFFECTS (C_MAYBE_CONST_عبارت_PRE (lhs)))
	    lhs = NULL_درخت;
	  وإلا
	    lhs = C_MAYBE_CONST_عبارت_عبارت (lhs);
	}
      إذا (درخت_کد (rhs) == C_MAYBE_CONST_عبارت)
	{
	  إذا (C_MAYBE_CONST_عبارت_PRE (rhs) != NULL_درخت
	      && درخت_SIDE_EFFECTS (C_MAYBE_CONST_عبارت_PRE (rhs)))
	    rhs = NULL_درخت;
	  وإلا
	    rhs = C_MAYBE_CONST_عبارت_عبارت (rhs);
	}
      إذا (lhs != NULL_درخت && rhs != NULL_درخت)
	warn_tautological_cmp (location, کد, lhs, rhs);
    }

  إذا (warn_logical_not_paren
      && درخت_کد_CLASS (کد) == tcc_comparison
      && code1 == TRUTH_NOT_عبارت
      && code2 != TRUTH_NOT_عبارت
      /* Avoid warning for !!x == y.  */
      && (درخت_کد (arg1.مقدار) != NE_عبارت
	  || !integer_zerop (درخت_عملوند (arg1.مقدار, 1))))
    {
      /* Avoid warning for !b == y where b has _Bool type.  */
      درخت t = integer_zero_گره;
      إذا (درخت_کد (arg1.مقدار) == EQ_عبارت
	  && integer_zerop (درخت_عملوند (arg1.مقدار, 1))
	  && درخت_TYPE (درخت_عملوند (arg1.مقدار, 0)) == integer_type_گره)
	{
	  t = درخت_عملوند (arg1.مقدار, 0);
	  افعل
	    {
	      إذا (درخت_TYPE (t) != integer_type_گره)
		اكسر;
	      إذا (درخت_کد (t) == C_MAYBE_CONST_عبارت)
		t = C_MAYBE_CONST_عبارت_عبارت (t);
	      وإلا إذا (CONVERT_عبارت_P (t))
		t = درخت_عملوند (t, 0);
	      وإلا
		اكسر;
	    }
	  طالما (1);
	}
      إذا (!C_BOOLEAN_TYPE_P (درخت_TYPE (t)))
	warn_logical_not_parentheses (location, کد, arg1.مقدار, arg2.مقدار);
    }

  /* Warn about comparisons against string literals, with the exception
     of testing for equality or inequality of a string literal with NULL.  */
  إذا (کد == EQ_عبارت || کد == NE_عبارت)
    {
      إذا ((code1 == STRING_CST
	   && !integer_zerop (درخت_strip_nop_conversions (arg2.مقدار)))
	  || (code2 == STRING_CST
	      && !integer_zerop (درخت_strip_nop_conversions (arg1.مقدار))))
	warning_at (location, OPT_Waddress,
		    "comparison with string literal results in unspecified behavior");
      /* Warn for ptr == '\0', it's likely that it should've been ptr[0].  */
      إذا (اشاره_گر_TYPE_P (type1)
	  && null_اشاره_گر_constant_p (arg2.مقدار)
	  && char_type_p (type2))
	{
	  auto_diagnostic_گروه d;
	  إذا (warning_at (location, OPT_Wpointer_compare,
			    "comparison between pointer and zero character "
			    "constant"))
	    inform (arg1.get_شروع (),
		      "did you mean to dereference the pointer?");
	}
      وإلا إذا (اشاره_گر_TYPE_P (type2)
	       && null_اشاره_گر_constant_p (arg1.مقدار)
	       && char_type_p (type1))
	{
	  auto_diagnostic_گروه d;
	  إذا (warning_at (location, OPT_Wpointer_compare,
			    "comparison between pointer and zero character "
			    "constant"))
	    inform (arg2.get_شروع (),
		      "did you mean to dereference the pointer?");
	}
    }
  وإلا إذا (درخت_کد_CLASS (کد) == tcc_comparison
	   && (code1 == STRING_CST || code2 == STRING_CST))
    warning_at (location, OPT_Waddress,
		"comparison with string literal results in unspecified "
		"behavior");

  إذا (warn_zero_as_null_اشاره_گر_constant
      && c_inhibit_evaluation_warnings == 0
      && درخت_کد_CLASS (کد) == tcc_comparison)
    {
      إذا ((درخت_کد (type1) == اشاره_گر_TYPE
	   || درخت_کد (type1) == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type2)
	  && null_اشاره_گر_constant_p (arg2.مقدار))
	warning_at (arg2.get_location(), OPT_Wzero_as_null_اشاره_گر_constant,
		    "zero as null pointer constant");

      إذا ((درخت_کد (type2) == اشاره_گر_TYPE
	   || درخت_کد (type2) == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type1)
	  && null_اشاره_گر_constant_p (arg1.مقدار))
	warning_at (arg1.get_location(), OPT_Wzero_as_null_اشاره_گر_constant,
		    "zero as null pointer constant");
    }

  إذا (warn_array_compare
      && درخت_کد_CLASS (کد) == tcc_comparison
      && درخت_کد (type1) == ARRAY_TYPE
      && درخت_کد (type2) == ARRAY_TYPE)
    do_warn_array_compare (location, کد, arg1.مقدار, arg2.مقدار);

  إذا (درخت_سرریز_P (نتیجه.مقدار)
      && !درخت_سرریز_P (arg1.مقدار)
      && !درخت_سرریز_P (arg2.مقدار))
    سرریز_warning (location, نتیجه.مقدار);

  /* Warn about comparisons of different enum types.  */
  إذا (warn_enum_compare
      && درخت_کد_CLASS (کد) == tcc_comparison
      && درخت_کد (type1) == ENUMERAL_TYPE
      && درخت_کد (type2) == ENUMERAL_TYPE
      && TYPE_MAIN_VARIANT (type1) != TYPE_MAIN_VARIANT (type2))
    warning_at (location, OPT_Wenum_compare,
		"comparison between %qT and %qT",
		type1, type2);

  إذا (warn_xor_استفاده_شده_as_pow
      && کد == بیت_XOR_عبارت
      && arg1.m_decimal
      && arg2.m_decimal)
    check_for_xor_استفاده_شده_as_pow (arg1.get_location (), arg1.مقدار,
			       location,
			       arg2.get_location (), arg2.مقدار);

  أرجع نتیجه;
}

/* Return a tree for the difference of pointers OP0 and OP1.
   The resulting tree has type ptrdiff_t.  If POINTER_SUBTRACT sanitization is
   enabled, assign to INSTRUMENT_EXPR call to libsanitizer.  */

ساكن درخت
اشاره_گر_diff (location_t loc, درخت op0, درخت op1, درخت *instrument_عبارت)
{
  درخت restype = ptrdiff_type_گره;
  درخت نتیجه, inttype;

  addr_space_t as0 = TYPE_ADDR_SPACE (درخت_TYPE (درخت_TYPE (op0)));
  addr_space_t as1 = TYPE_ADDR_SPACE (درخت_TYPE (درخت_TYPE (op1)));
  درخت هدف_type = درخت_TYPE (درخت_TYPE (op0));
  درخت orig_op0 = op0;
  درخت orig_op1 = op1;

  /* If the operands point into different address spaces, we need to
     explicitly convert them to pointers into the common address space
     before we can subtract the numerical address values.  */
  إذا (as0 != as1)
    {
      addr_space_t as_common;
      درخت common_type;

      /* Determine the common superset address space.  This is guaranteed
	 to exist because the caller verified that comp_target_types
	 returned non-zero.  */
      إذا (!addr_space_superset (as0, as1, &as_common))
	gcc_unreachable ();

      common_type = common_اشاره_گر_type (درخت_TYPE (op0), درخت_TYPE (op1), NULL_درخت);
      op0 = convert (common_type, op0);
      op1 = convert (common_type, op1);
    }

  /* Determine integer type result of the subtraction.  This will usually
     be the same as the result type (ptrdiff_t), but may need to be a wider
     type if pointers for the address space are wider than ptrdiff_t.  */
  إذا (TYPE_PRECISION (restype) < TYPE_PRECISION (درخت_TYPE (op0)))
    inttype = c_common_type_for_اندازه (TYPE_PRECISION (درخت_TYPE (op0)), 0);
  وإلا
    inttype = restype;

  إذا (VOID_TYPE_P (هدف_type))
    pedwarn (loc, OPT_Wpointer_arith,
	     "pointer of type %<void *%> used in subtraction");
  إذا (درخت_کد (هدف_type) == FUNCTION_TYPE)
    pedwarn (loc, OPT_Wpointer_arith,
	     "pointer to a function used in subtraction");

  إذا (current_function_decl != NULL_درخت
      && sanitize_flags_p (SANITIZE_اشاره_گر_تفریق))
    {
      op0 = save_عبارت (c_fully_fold (op0, خطأ, عدم));
      op1 = save_عبارت (c_fully_fold (op1, خطأ, عدم));

      درخت tt = builtin_decl_explicit (BUILT_درون_ASAN_اشاره_گر_تفریق);
      *instrument_عبارت = build_call_عبارت_loc (loc, tt, 2, op0, op1);
    }

  /* First do the subtraction, then build the divide operator
     and only convert at the very end.
     Do not do default conversions in case restype is a short type.  */

  /* POINTER_DIFF_EXPR requires a signed integer type of the same size as
     pointers.  If some platform cannot provide that, or has a larger
     ptrdiff_type to support differences larger than half the address
     space, cast the pointers to some larger integer type and do the
     computations in that type.  */
  إذا (TYPE_PRECISION (inttype) > TYPE_PRECISION (درخت_TYPE (op0)))
    op0 = build_دودویی_op (loc, MINUS_عبارت, convert (inttype, op0),
			   convert (inttype, op1), خطأ);
  وإلا
    {
      /* Cast away qualifiers.  */
      op0 = convert (c_common_type (درخت_TYPE (op0), درخت_TYPE (op0)), op0);
      op1 = convert (c_common_type (درخت_TYPE (op1), درخت_TYPE (op1)), op1);
      op0 = build2_loc (loc, اشاره_گر_DIFF_عبارت, inttype, op0, op1);
    }

  /* This generates an error if op1 is pointer to incomplete type.  */
  إذا (!COMPLETE_OR_VOID_TYPE_P (درخت_TYPE (درخت_TYPE (orig_op1))))
    error_at (loc, "arithmetic on pointer to an incomplete type");
  وإلا إذا (verify_type_context (loc, TCTX_اشاره_گر_ARITH,
				درخت_TYPE (درخت_TYPE (orig_op0))))
    verify_type_context (loc, TCTX_اشاره_گر_ARITH,
			 درخت_TYPE (درخت_TYPE (orig_op1)));

  op1 = c_اندازه_درون_بایتها (هدف_type);

  إذا (اشاره_گر_مقصد_zero_sized_aggr_p (درخت_TYPE (orig_op1)))
    error_at (loc, "arithmetic on pointer to an empty aggregate");

  /* Divide by the size, in easiest possible way.  */
  نتیجه = fold_build2_loc (loc, EXACT_DIV_عبارت, inttype,
			    op0, convert (inttype, op1));

  /* Convert to final result type if necessary.  */
  أرجع convert (restype, نتیجه);
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

ساكن درخت
build_atomic_تخصیص_بده (location_t loc, درخت lhs, تعداد درخت_کد_2 modifycode,
		     درخت rhs, منطقي return_old_p)
{
  درخت fndecl, func_call;
  vec<درخت, va_gc> *params;
  درخت val, nonatomic_lhs_type, nonatomic_rhs_type, newval, newval_addr;
  درخت old, old_addr;
  درخت compound_stmt = NULL_درخت;
  درخت stmt, goto_stmt;
  درخت loop_label, loop_decl, انجامشده_label, انجامشده_decl;

  درخت lhs_type = درخت_TYPE (lhs);
  درخت lhs_addr = build_unary_op (loc, ADDR_عبارت, lhs, خطأ);
  درخت seq_cst = build_int_cst (integer_type_گره, MEMMODEL_SEQ_CST);
  درخت rhs_semantic_type = درخت_TYPE (rhs);
  درخت nonatomic_rhs_semantic_type;
  درخت rhs_type;

  gcc_assert (TYPE_ATOMIC (lhs_type));

  إذا (return_old_p)
    gcc_assert (modifycode == PLUS_عبارت || modifycode == MINUS_عبارت);

  /* Allocate enough vector items for a compare_exchange.  */
  vec_alloc (params, 6);

  /* Create a compound statement to hold the sequence of statements
     with a loop.  */
  إذا (modifycode != NOP_عبارت)
    {
      compound_stmt = c_begin_compound_stmt (خطأ);

      /* For consistency with build_modify_expr on non-_Atomic,
	 mark the lhs as read.  Also, it would be very hard to match
	 such expressions in mark_exp_read.  */
      mark_exp_read (lhs);
    }

  /* Remove any excess precision (which is only present here in the
     case of compound assignments).  */
  إذا (درخت_کد (rhs) == EXCESS_PRECISION_عبارت)
    {
      gcc_assert (modifycode != NOP_عبارت);
      rhs = درخت_عملوند (rhs, 0);
    }
  rhs_type = درخت_TYPE (rhs);

  /* Fold the RHS if it hasn't already been folded.  */
  إذا (modifycode != NOP_عبارت)
    rhs = c_fully_fold (rhs, خطأ, عدم);

  /* Remove the qualifiers for the rest of the expressions and create
     the VAL temp variable to hold the RHS.  */
  nonatomic_lhs_type = build_qualified_type (lhs_type, TYPE_UNQUALIFIED);
  nonatomic_rhs_type = build_qualified_type (rhs_type, TYPE_UNQUALIFIED);
  nonatomic_rhs_semantic_type = build_qualified_type (rhs_semantic_type,
						      TYPE_UNQUALIFIED);
  val = create_tmp_var_raw (nonatomic_rhs_type);
  درخت_ADDRESSABLE (val) = 1;
  suppress_warning (val);
  rhs = build4 (هدف_عبارت, nonatomic_rhs_type, val, rhs, NULL_درخت,
		NULL_درخت);
  درخت_SIDE_EFFECTS (rhs) = 1;
  مجموعه_عبارت_LOCATION (rhs, loc);
  إذا (modifycode != NOP_عبارت)
    جمع_کن_stmt (rhs);

  /* NOP_EXPR indicates it's a straight store of the RHS. Simply issue
     an atomic_store.  */
  إذا (modifycode == NOP_عبارت)
    {
      compound_stmt = rhs;
      /* Build __atomic_store (&lhs, &val, SEQ_CST)  */
      rhs = build_unary_op (loc, ADDR_عبارت, val, خطأ);
      fndecl = builtin_decl_explicit (BUILT_درون_ATOMIC_STORE);
      params->سریع_افزودن (lhs_addr);
      params->سریع_افزودن (rhs);
      params->سریع_افزودن (seq_cst);
      func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, عدم);

      compound_stmt = build2 (COMPOUND_عبارت, void_type_گره,
			      compound_stmt, func_call);

      /* VAL is the value which was stored, return a COMPOUND_STMT of
	 the statement and that value.  */
      أرجع build2 (COMPOUND_عبارت, nonatomic_lhs_type, compound_stmt, val);
    }

  /* Attempt to implement the atomic operation as an __atomic_fetch_* or
     __atomic_*_fetch built-in rather than a CAS loop.  atomic_bool type
     isn't applicable for such builtins.  ??? Do we want to handle enums?  */
  إذا ((درخت_کد (lhs_type) == INTEGER_TYPE || اشاره_گر_TYPE_P (lhs_type))
      && درخت_کد (rhs_type) == INTEGER_TYPE)
    {
      built_درون_function fncode;
      بدل (modifycode)
	{
	حالة PLUS_عبارت:
	حالة اشاره_گر_PLUS_عبارت:
	  fncode = (return_old_p
		    ? BUILT_درون_ATOMIC_FETCH_جمع_کن_N
		    : BUILT_درون_ATOMIC_جمع_کن_FETCH_N);
	  اكسر;
	حالة MINUS_عبارت:
	  fncode = (return_old_p
		    ? BUILT_درون_ATOMIC_FETCH_SUB_N
		    : BUILT_درون_ATOMIC_SUB_FETCH_N);
	  اكسر;
	حالة بیت_AND_عبارت:
	  fncode = (return_old_p
		    ? BUILT_درون_ATOMIC_FETCH_AND_N
		    : BUILT_درون_ATOMIC_AND_FETCH_N);
	  اكسر;
	حالة بیت_IOR_عبارت:
	  fncode = (return_old_p
		    ? BUILT_درون_ATOMIC_FETCH_OR_N
		    : BUILT_درون_ATOMIC_OR_FETCH_N);
	  اكسر;
	حالة بیت_XOR_عبارت:
	  fncode = (return_old_p
		    ? BUILT_درون_ATOMIC_FETCH_XOR_N
		    : BUILT_درون_ATOMIC_XOR_FETCH_N);
	  اكسر;
	افتراضي:
	  اذهب cas_loop;
	}

      /* We can only use "_1" through "_16" variants of the atomic fetch
	 built-ins.  */
      بیعلامت HOST_WIDE_INT اندازه = درخت_مقصد_uhwi (TYPE_اندازه_UNIT (lhs_type));
      إذا (اندازه != 1 && اندازه != 2 && اندازه != 4 && اندازه != 8 && اندازه != 16)
	اذهب cas_loop;

      /* If this is a pointer type, we need to multiply by the size of
	 the pointer target type.  */
      إذا (اشاره_گر_TYPE_P (lhs_type))
	{
	  إذا (!COMPLETE_TYPE_P (درخت_TYPE (lhs_type))
	      /* ??? This would introduce -Wdiscarded-qualifiers
		 warning: __atomic_fetch_* expect volatile void *
		 type as the first argument.  (Assignments between
		 atomic and non-atomic objects are OK.) */
	      || TYPE_RESTRICT (lhs_type))
	    اذهب cas_loop;
	  درخت sz = TYPE_اندازه_UNIT (درخت_TYPE (lhs_type));
	  rhs = fold_build2_loc (loc, MULT_عبارت, ptrdiff_type_گره,
				 convert (ptrdiff_type_گره, rhs),
				 convert (ptrdiff_type_گره, sz));
	}

      /* Build __atomic_fetch_* (&lhs, &val, SEQ_CST), or
	 __atomic_*_fetch (&lhs, &val, SEQ_CST).  */
      fndecl = builtin_decl_explicit (fncode);
      params->سریع_افزودن (lhs_addr);
      params->سریع_افزودن (rhs);
      params->سریع_افزودن (seq_cst);
      func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, عدم);

      newval = create_tmp_var_raw (nonatomic_lhs_type);
      درخت_ADDRESSABLE (newval) = 1;
      suppress_warning (newval);
      rhs = build4 (هدف_عبارت, nonatomic_lhs_type, newval, func_call,
		    NULL_درخت, NULL_درخت);
      مجموعه_عبارت_LOCATION (rhs, loc);
      جمع_کن_stmt (rhs);

      /* Finish the compound statement.  */
      compound_stmt = c_انتها_compound_stmt (loc, compound_stmt, خطأ);

      /* NEWVAL is the value which was stored, return a COMPOUND_STMT of
	 the statement and that value.  */
      أرجع build2 (COMPOUND_عبارت, nonatomic_lhs_type, compound_stmt, newval);
    }

cas_loop:
  /* Create the variables and labels required for the op= form.  */
  old = create_tmp_var_raw (nonatomic_lhs_type);
  old_addr = build_unary_op (loc, ADDR_عبارت, old, خطأ);
  درخت_ADDRESSABLE (old) = 1;
  suppress_warning (old);

  newval = create_tmp_var_raw (nonatomic_lhs_type);
  newval_addr = build_unary_op (loc, ADDR_عبارت, newval, خطأ);
  درخت_ADDRESSABLE (newval) = 1;
  suppress_warning (newval);

  loop_decl = create_artificial_label (loc);
  loop_label = build1 (LABEL_عبارت, void_type_گره, loop_decl);

  انجامشده_decl = create_artificial_label (loc);
  انجامشده_label = build1 (LABEL_عبارت, void_type_گره, انجامشده_decl);

  /* __atomic_load (addr, &old, SEQ_CST).  */
  fndecl = builtin_decl_explicit (BUILT_درون_ATOMIC_بارگیری);
  params->سریع_افزودن (lhs_addr);
  params->سریع_افزودن (old_addr);
  params->سریع_افزودن (seq_cst);
  func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, عدم);
  old = build4 (هدف_عبارت, nonatomic_lhs_type, old, func_call, NULL_درخت,
		NULL_درخت);
  جمع_کن_stmt (old);
  params->truncate (0);

  /* Create the expressions for floating-point environment
     manipulation, if required.  */
  منطقي need_fenv = (flag_trapping_math
		    && (FLOAT_TYPE_P (lhs_type) || FLOAT_TYPE_P (rhs_type)));
  درخت hold_call = NULL_درخت, clear_call = NULL_درخت, update_call = NULL_درخت;
  إذا (need_fenv)
    targetm.atomic_تخصیص_بده_expand_fenv (&hold_call, &clear_call, &update_call);

  إذا (hold_call)
    جمع_کن_stmt (hold_call);

  /* loop:  */
  جمع_کن_stmt (loop_label);

  /* newval = old + val;  */
  إذا (rhs_type != rhs_semantic_type)
    val = build1 (EXCESS_PRECISION_عبارت, nonatomic_rhs_semantic_type, val);
  rhs = build_دودویی_op (loc, modifycode,
			 convert_lvalue_مقصد_rvalue (loc, old, درست, درست),
			 val, درست);
  إذا (درخت_کد (rhs) == EXCESS_PRECISION_عبارت)
    {
      درخت eptype = درخت_TYPE (rhs);
      rhs = c_fully_fold (درخت_عملوند (rhs, 0), خطأ, عدم);
      rhs = build1 (EXCESS_PRECISION_عبارت, eptype, rhs);
    }
  وإلا
    rhs = c_fully_fold (rhs, خطأ, عدم);
  rhs = convert_for_assignment (loc, UNKNOWN_LOCATION, nonatomic_lhs_type,
				rhs, NULL_درخت, ic_تخصیص_بده, خطأ, NULL_درخت,
				NULL_درخت, 0);
  /* The temporary variable for NEWVAL is only gimplified correctly (in
     particular, given a DECL_CONTEXT) if used in a TARGET_EXPR.  To avoid
     subsequent ICEs in nested function processing after an error, ensure such
     a TARGET_EXPR is built even after an error.  */
  إذا (rhs == error_mark_گره)
    rhs = old;
  rhs = build4 (هدف_عبارت, nonatomic_lhs_type, newval, rhs, NULL_درخت,
		NULL_درخت);
  مجموعه_عبارت_LOCATION (rhs, loc);
  جمع_کن_stmt (rhs);

  /* if (__atomic_compare_exchange (addr, &old, &new, false, SEQ_CST, SEQ_CST))
       goto done;  */
  fndecl = builtin_decl_explicit (BUILT_درون_ATOMIC_COMPARE_EXCHANGE);
  params->سریع_افزودن (lhs_addr);
  params->سریع_افزودن (old_addr);
  params->سریع_افزودن (newval_addr);
  params->سریع_افزودن (integer_zero_گره);
  params->سریع_افزودن (seq_cst);
  params->سریع_افزودن (seq_cst);
  func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, عدم);

  goto_stmt = build1 (GOTO_عبارت, void_type_گره, انجامشده_decl);
  مجموعه_عبارت_LOCATION (goto_stmt, loc);

  stmt = build3 (COND_عبارت, void_type_گره, func_call, goto_stmt, NULL_درخت);
  مجموعه_عبارت_LOCATION (stmt, loc);
  جمع_کن_stmt (stmt);

  إذا (clear_call)
    جمع_کن_stmt (clear_call);

  /* goto loop;  */
  goto_stmt  = build1 (GOTO_عبارت, void_type_گره, loop_decl);
  مجموعه_عبارت_LOCATION (goto_stmt, loc);
  جمع_کن_stmt (goto_stmt);

  /* done:  */
  جمع_کن_stmt (انجامشده_label);

  إذا (update_call)
    جمع_کن_stmt (update_call);

  /* Finish the compound statement.  */
  compound_stmt = c_انتها_compound_stmt (loc, compound_stmt, خطأ);

  /* NEWVAL is the value that was successfully stored, return a
     COMPOUND_EXPR of the statement and the appropriate value.  */
  أرجع build2 (COMPOUND_عبارت, nonatomic_lhs_type, compound_stmt,
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
build_unary_op (location_t location, تعداد درخت_کد_2 کد, درخت xarg,
		منطقي noconvert)
{
  /* No default_conversion here.  It causes trouble for ADDR_EXPR.  */
  درخت arg = xarg;
  درخت argtype = NULL_درخت;
  تعداد درخت_کد_2 typecode;
  درخت val;
  درخت ret = error_mark_گره;
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
  إذا (is_access_with_اندازه_p (arg))
    xarg = arg = get_ref_from_access_with_اندازه (arg);

  gcc_checking_assert (!is_access_with_اندازه_p (arg));

  منطقي int_operands = عبارت_INT_CONST_OPERANDS (xarg);
  إذا (int_operands)
    arg = remove_c_maybe_const_عبارت (arg);

  إذا (کد != ADDR_عبارت)
    arg = require_complete_type (location, arg);

  typecode = درخت_کد (درخت_TYPE (arg));
  إذا (typecode == ERROR_MARK)
    أرجع error_mark_گره;
  إذا (typecode == ENUMERAL_TYPE || typecode == BOOLEAN_TYPE)
    typecode = INTEGER_TYPE;

  إذا ((invalid_op_diag
       = targetm.invalid_unary_op (کد, درخت_TYPE (xarg))))
    {
      error_at (location, invalid_op_diag);
      أرجع error_mark_گره;
    }

  إذا (درخت_کد (arg) == EXCESS_PRECISION_عبارت)
    {
      eptype = درخت_TYPE (arg);
      arg = درخت_عملوند (arg, 0);
    }

  بدل (کد)
    {
    حالة CONVERT_عبارت:
      /* This is used for unary plus, because a CONVERT_EXPR
	 is enough to prevent anybody from looking inside for
	 associativity, but won't generate any code.  */
      إذا (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE
	    || typecode == FIXED_نقطه_TYPE || typecode == COMPLEX_TYPE
	    || typecode == BITINT_TYPE
	    || gnu_وکتور_type_p (درخت_TYPE (arg))))
	{
	  error_at (location, "wrong type argument to unary plus");
	  أرجع error_mark_گره;
	}
      وإلا إذا (!noconvert)
	arg = default_conversion (arg);
      arg = non_lvalue_loc (location, arg);
      اكسر;

    حالة NEGATE_عبارت:
      إذا (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE
	    || typecode == FIXED_نقطه_TYPE || typecode == COMPLEX_TYPE
	    || typecode == BITINT_TYPE
	    || gnu_وکتور_type_p (درخت_TYPE (arg))))
	{
	  error_at (location, "wrong type argument to unary minus");
	  أرجع error_mark_گره;
	}
      وإلا إذا (!noconvert)
	arg = default_conversion (arg);
      اكسر;

    حالة بیت_NOT_عبارت:
      /* ~ works on integer types and non float vectors. */
      إذا (typecode == INTEGER_TYPE
	  || typecode == BITINT_TYPE
	  || (gnu_وکتور_type_p (درخت_TYPE (arg))
	      && !وکتور_FLOAT_TYPE_P (درخت_TYPE (arg))))
	{
	  درخت e = arg;

	  /* Warn if the expression has boolean value.  */
	  طالما (درخت_کد (e) == COMPOUND_عبارت)
	    e = درخت_عملوند (e, 1);

	  إذا ((C_BOOLEAN_TYPE_P (درخت_TYPE (arg))
	       || truth_مقدار_p (درخت_کد (e))))
	    {
	      auto_diagnostic_گروه d;
	      إذا (warning_at (location, OPT_Wbool_operation,
				"%<~%> on a boolean expression"))
		{
		  gcc_rich_location richloc (location);
		  richloc.جمع_کن_fixit_درج_before (location, "!");
		  inform (&richloc, "did you mean to use logical not?");
		}
	    }
	  إذا (!noconvert)
	    arg = default_conversion (arg);
	}
      وإلا إذا (typecode == COMPLEX_TYPE)
	{
	  کد = CONJ_عبارت;
	  pedwarn (location, OPT_Wpedantic,
		   "ISO C does not support %<~%> for complex conjugation");
	  إذا (!noconvert)
	    arg = default_conversion (arg);
	}
      وإلا
	{
	  error_at (location, "wrong type argument to bit-complement");
	  أرجع error_mark_گره;
	}
      اكسر;

    حالة ABS_عبارت:
      إذا (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE))
	{
	  error_at (location, "wrong type argument to abs");
	  أرجع error_mark_گره;
	}
      وإلا إذا (!noconvert)
	arg = default_conversion (arg);
      اكسر;

    حالة ABSU_عبارت:
      إذا (!(typecode == INTEGER_TYPE))
	{
	  error_at (location, "wrong type argument to absu");
	  أرجع error_mark_گره;
	}
      وإلا إذا (!noconvert)
	arg = default_conversion (arg);
      اكسر;

    حالة CONJ_عبارت:
      /* Conjugating a real value is a no-op, but allow it anyway.  */
      إذا (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE
	    || typecode == COMPLEX_TYPE))
	{
	  error_at (location, "wrong type argument to conjugation");
	  أرجع error_mark_گره;
	}
      وإلا إذا (!noconvert)
	arg = default_conversion (arg);
      اكسر;

    حالة TRUTH_NOT_عبارت:
      إذا (typecode != INTEGER_TYPE && typecode != FIXED_نقطه_TYPE
	  && typecode != REAL_TYPE && typecode != اشاره_گر_TYPE
	  && typecode != COMPLEX_TYPE && typecode != NULLPTR_TYPE
	  && typecode != BITINT_TYPE)
	{
	  error_at (location,
		    "wrong type argument to unary exclamation mark");
	  أرجع error_mark_گره;
	}
      إذا (int_operands)
	{
	  arg = c_objc_common_truthvalue_conversion (location, xarg);
	  arg = remove_c_maybe_const_عبارت (arg);
	}
      وإلا
	arg = c_objc_common_truthvalue_conversion (location, arg);
      ret = invert_truthvalue_loc (location, arg);
      eptype = NULL_درخت;
      /* If the TRUTH_NOT_EXPR has been folded, reset the location.  */
      إذا (عبارت_P (ret) && عبارت_HAS_LOCATION (ret))
	location = عبارت_LOCATION (ret);
      اذهب return_build_unary_op;

    حالة REALPART_عبارت:
    حالة IMAGPART_عبارت:
      ret = build_real_imag_عبارت (location, کد, arg);
      إذا (ret == error_mark_گره)
	أرجع error_mark_گره;
      إذا (eptype && درخت_کد (eptype) == COMPLEX_TYPE)
	eptype = درخت_TYPE (eptype);
      اذهب return_build_unary_op;

    حالة PREINCREMENT_عبارت:
    حالة POSTINCREMENT_عبارت:
    حالة PREDECREMENT_عبارت:
    حالة POSTDECREMENT_عبارت:

      إذا (درخت_کد (arg) == C_MAYBE_CONST_عبارت)
	{
	  درخت inner = build_unary_op (location, کد,
				       C_MAYBE_CONST_عبارت_عبارت (arg),
				       noconvert);
	  إذا (inner == error_mark_گره)
	    أرجع error_mark_گره;
	  ret = build2 (C_MAYBE_CONST_عبارت, درخت_TYPE (inner),
			C_MAYBE_CONST_عبارت_PRE (arg), inner);
	  gcc_assert (!C_MAYBE_CONST_عبارت_INT_OPERANDS (arg));
	  C_MAYBE_CONST_عبارت_NON_CONST (ret) = 1;
	  اذهب return_build_unary_op;
	}

      /* Complain about anything that is not a true lvalue.  In
	 Objective-C, skip this check for property_refs.  */
      إذا (!objc_is_property_ref (arg)
	  && !lvalue_or_else (location,
			      arg, ((کد == PREINCREMENT_عبارت
				     || کد == POSTINCREMENT_عبارت)
				    ? lv_increment
				    : lv_decrement)))
	أرجع error_mark_گره;

      إذا (warn_cxx_compat && درخت_کد (درخت_TYPE (arg)) == ENUMERAL_TYPE)
	{
	  إذا (کد == PREINCREMENT_عبارت || کد == POSTINCREMENT_عبارت)
	    warning_at (location, OPT_Wc___compat,
			"increment of enumeration value is invalid in C++");
	  وإلا
	    warning_at (location, OPT_Wc___compat,
			"decrement of enumeration value is invalid in C++");
	}

      إذا (C_BOOLEAN_TYPE_P (درخت_TYPE (arg)))
	{
	  إذا (کد == PREINCREMENT_عبارت || کد == POSTINCREMENT_عبارت)
	    warning_at (location, OPT_Wbool_operation,
			"increment of a boolean expression");
	  وإلا
	    warning_at (location, OPT_Wbool_operation,
			"decrement of a boolean expression");
	}

      /* Ensure the argument is fully folded inside any SAVE_EXPR.  */
      arg = c_fully_fold (arg, خطأ, عدم, درست);

      منطقي atomic_op;
      atomic_op = really_atomic_lvalue (arg);

      /* Increment or decrement the real part of the value,
	 and don't change the imaginary part.  */
      إذا (typecode == COMPLEX_TYPE)
	{
	  درخت real, imag;

	  pedwarn_c23 (location, OPT_Wpedantic,
		       "ISO C does not support %<++%> and %<--%> on complex "
		       "types before C2Y");

	  إذا (!atomic_op)
	    {
	      arg = stabilize_reference (arg);
	      real = build_unary_op (عبارت_LOCATION (arg), REALPART_عبارت, arg,
				     درست);
	      imag = build_unary_op (عبارت_LOCATION (arg), IMAGPART_عبارت, arg,
				     درست);
	      real = build_unary_op (عبارت_LOCATION (arg), کد, real, درست);
	      إذا (real == error_mark_گره || imag == error_mark_گره)
		أرجع error_mark_گره;
	      ret = build2 (COMPLEX_عبارت, درخت_TYPE (arg),
			    real, imag);
	      اذهب return_build_unary_op;
	    }
	}

      /* Report invalid types.  */

      إذا (typecode != اشاره_گر_TYPE && typecode != FIXED_نقطه_TYPE
	  && typecode != INTEGER_TYPE && typecode != REAL_TYPE
	  && typecode != COMPLEX_TYPE && typecode != BITINT_TYPE
	  && !gnu_وکتور_type_p (درخت_TYPE (arg)))
	{
	  إذا (کد == PREINCREMENT_عبارت || کد == POSTINCREMENT_عبارت)
	    error_at (location, "wrong type argument to increment");
	  وإلا
	    error_at (location, "wrong type argument to decrement");

	  أرجع error_mark_گره;
	}

      {
	درخت inc;

	argtype = درخت_TYPE (arg);

	/* Compute the increment.  */

	إذا (typecode == اشاره_گر_TYPE)
	  {
	    /* If pointer target is an incomplete type,
	       we just cannot know how to do the arithmetic.  */
	    إذا (!COMPLETE_OR_VOID_TYPE_P (درخت_TYPE (argtype)))
	      {
		إذا (کد == PREINCREMENT_عبارت || کد == POSTINCREMENT_عبارت)
		  error_at (location,
			    "increment of pointer to an incomplete type %qT",
			    درخت_TYPE (argtype));
		وإلا
		  error_at (location,
			    "decrement of pointer to an incomplete type %qT",
			    درخت_TYPE (argtype));
	      }
	    وإلا إذا (درخت_کد (درخت_TYPE (argtype)) == FUNCTION_TYPE
		     || VOID_TYPE_P (درخت_TYPE (argtype)))
	      {
		إذا (کد == PREINCREMENT_عبارت || کد == POSTINCREMENT_عبارت)
		  pedwarn (location, OPT_Wpointer_arith,
			   "wrong type argument to increment");
		وإلا
		  pedwarn (location, OPT_Wpointer_arith,
			   "wrong type argument to decrement");
	      }
	    وإلا
	      verify_type_context (location, TCTX_اشاره_گر_ARITH,
				   درخت_TYPE (argtype));

	    inc = c_اندازه_درون_بایتها (درخت_TYPE (argtype));
	    inc = convert_مقصد_ptrofftype_loc (location, inc);
	  }
	وإلا إذا (FRACT_نما_P (TYPE_نما (argtype)))
	  {
	    /* For signed fract types, we invert ++ to -- or
	       -- to ++, and change inc from 1 to -1, because
	       it is not possible to represent 1 in signed fract constants.
	       For unsigned fract types, the result always overflows and
	       we get an undefined (original) or the maximum value.  */
	    إذا (کد == PREINCREMENT_عبارت)
	      کد = PREDECREMENT_عبارت;
	    وإلا إذا (کد == PREDECREMENT_عبارت)
	      کد = PREINCREMENT_عبارت;
	    وإلا إذا (کد == POSTINCREMENT_عبارت)
	      کد = POSTDECREMENT_عبارت;
	    وإلا /* code == POSTDECREMENT_EXPR  */
	      کد = POSTINCREMENT_عبارت;

	    inc = integer_minus_one_گره;
	    inc = convert (argtype, inc);
	  }
	وإلا
	  {
	    inc = وکتور_TYPE_P (argtype)
	      ? build_one_cst (argtype)
	      : integer_one_گره;
	    inc = convert (argtype, inc);
	  }

	/* If 'arg' is an Objective-C PROPERTY_REF expression, then we
	   need to ask Objective-C to build the increment or decrement
	   expression for it.  */
	إذا (objc_is_property_ref (arg))
	  أرجع objc_build_incr_عبارت_for_property_ref (location, کد,
							arg, inc);

	/* Report a read-only lvalue.  */
	إذا (TYPE_READONLY (argtype))
	  {
	    readonly_error (location, arg,
			    ((کد == PREINCREMENT_عبارت
			      || کد == POSTINCREMENT_عبارت)
			     ? lv_increment : lv_decrement));
	    أرجع error_mark_گره;
	  }
	وإلا إذا (درخت_READONLY (arg))
	  readonly_warning (arg,
			    ((کد == PREINCREMENT_عبارت
			      || کد == POSTINCREMENT_عبارت)
			     ? lv_increment : lv_decrement));

	/* If the argument is atomic, use the special code sequences for
	   atomic compound assignment.  */
	إذا (atomic_op)
	  {
	    arg = stabilize_reference (arg);
	    ret = build_atomic_تخصیص_بده (location, arg,
				       ((کد == PREINCREMENT_عبارت
					 || کد == POSTINCREMENT_عبارت)
					? PLUS_عبارت
					: MINUS_عبارت),
				       (FRACT_نما_P (TYPE_نما (argtype))
					? inc
					: integer_one_گره),
				       (کد == POSTINCREMENT_عبارت
					|| کد == POSTDECREMENT_عبارت));
	    اذهب return_build_unary_op;
	  }

	درخت true_res;
	إذا (c_hardbool_type_attr (درخت_TYPE (arg), عدم, &true_res))
	  {
	    درخت larg = stabilize_reference (arg);
	    درخت sarg = save_عبارت (larg);
	    بدل (کد)
	      {
	      حالة PREINCREMENT_عبارت:
		val = build2 (MODIFY_عبارت, درخت_TYPE (larg), larg, true_res);
		val = build2 (COMPOUND_عبارت, درخت_TYPE (larg), sarg, val);
		اكسر;
	      حالة POSTINCREMENT_عبارت:
		val = build2 (MODIFY_عبارت, درخت_TYPE (larg), larg, true_res);
		val = build2 (COMPOUND_عبارت, درخت_TYPE (larg), val, sarg);
		val = build2 (COMPOUND_عبارت, درخت_TYPE (larg), sarg, val);
		اكسر;
	      حالة PREDECREMENT_عبارت:
		{
		  درخت rarg = convert_lvalue_مقصد_rvalue (location, sarg,
							درست, درست);
		  rarg = invert_truthvalue_loc (location, rarg);
		  rarg = convert (درخت_TYPE (sarg), rarg);
		  val = build2 (MODIFY_عبارت, درخت_TYPE (larg), larg, rarg);
		}
		اكسر;
	      حالة POSTDECREMENT_عبارت:
		{
		  درخت rarg = convert_lvalue_مقصد_rvalue (location, sarg,
							درست, درست);
		  rarg = invert_truthvalue_loc (location, rarg);
		  درخت iarg = convert (درخت_TYPE (larg), rarg);
		  val = build2 (MODIFY_عبارت, درخت_TYPE (larg), larg, iarg);
		  val = build2 (COMPOUND_عبارت, درخت_TYPE (larg), val, sarg);
		  val = build2 (COMPOUND_عبارت, درخت_TYPE (larg), sarg, val);
		}
		اكسر;
	      افتراضي:
		gcc_unreachable ();
	      }
	    درخت_SIDE_EFFECTS (val) = 1;
	  }
	وإلا إذا (C_BOOLEAN_TYPE_P (درخت_TYPE (arg)))
	  val = boolean_increment (کد, arg);
	وإلا
	  val = build2 (کد, درخت_TYPE (arg), arg, inc);
	درخت_SIDE_EFFECTS (val) = 1;
	إذا (TYPE_QUALS (درخت_TYPE (val)) != TYPE_UNQUALIFIED)
	  درخت_TYPE (val) = c_build_qualified_type (درخت_TYPE (val),
						    TYPE_UNQUALIFIED);
	ret = val;
	اذهب return_build_unary_op;
      }

    حالة ADDR_عبارت:
      /* Note that this operation never does default_conversion.  */

      /* The operand of unary '&' must be an lvalue (which excludes
	 expressions of type void), or, in C99, the result of a [] or
	 unary '*' operator.  */
      إذا (VOID_TYPE_P (درخت_TYPE (arg))
	  && TYPE_QUALS (درخت_TYPE (arg)) == TYPE_UNQUALIFIED
	  && (!غیرمستقیم_REF_P (arg) || !flag_isoc99))
	pedwarn (location, 0, "taking address of expression of type %<void%>");

      /* Let &* cancel out to simplify resulting code.  */
      إذا (غیرمستقیم_REF_P (arg))
	{
	  /* Don't let this be an lvalue.  */
	  إذا (lvalue_p (درخت_عملوند (arg, 0)))
	    أرجع non_lvalue_loc (location, درخت_عملوند (arg, 0));
	  ret = درخت_عملوند (arg, 0);
	  اذهب return_build_unary_op;
	}

      /* Anything not already handled and not a true memory reference
	 or a non-lvalue array is an error.  */
      إذا (typecode != FUNCTION_TYPE && !noconvert
	  && !lvalue_or_else (location, arg, lv_addressof))
	أرجع error_mark_گره;

      /* Move address operations inside C_MAYBE_CONST_EXPR to simplify
	 folding later.  */
      إذا (درخت_کد (arg) == C_MAYBE_CONST_عبارت)
	{
	  درخت inner = build_unary_op (location, کد,
				       C_MAYBE_CONST_عبارت_عبارت (arg),
				       noconvert);
	  ret = build2 (C_MAYBE_CONST_عبارت, درخت_TYPE (inner),
			C_MAYBE_CONST_عبارت_PRE (arg), inner);
	  gcc_assert (!C_MAYBE_CONST_عبارت_INT_OPERANDS (arg));
	  C_MAYBE_CONST_عبارت_NON_CONST (ret)
	    = C_MAYBE_CONST_عبارت_NON_CONST (arg);
	  اذهب return_build_unary_op;
	}

      /* Ordinary case; arg is a COMPONENT_REF or a decl.  */

      argtype = درخت_TYPE (arg);

      /* If the lvalue is const or volatile, merge that into the type
	 to which the address will point.  This is only needed
	 for function types.  */
      إذا ((DECL_P (arg) || REFERENCE_CLASS_P (arg))
	  && (درخت_READONLY (arg) || درخت_THIS_VOLATILE (arg))
	  && درخت_کد (argtype) == FUNCTION_TYPE)
	{
	  صحيح orig_quals = TYPE_QUALS (strip_array_types (argtype));
	  صحيح quals = orig_quals;

	  إذا (درخت_READONLY (arg))
	    quals |= TYPE_QUAL_CONST;
	  إذا (درخت_THIS_VOLATILE (arg))
	    quals |= TYPE_QUAL_VOLATILE;

	  argtype = c_build_qualified_type (argtype, quals);
	}

      بدل (درخت_کد (arg))
	{
	حالة COMPONENT_REF:
	  إذا (DECL_C_بیت_فیلد (درخت_عملوند (arg, 1)))
	    {
	      error_at (location, "cannot take address of bit-field %qD",
			درخت_عملوند (arg, 1));
	      أرجع error_mark_گره;
	    }

	  /* fall through */

	حالة ARRAY_REF:
	  إذا (TYPE_معکوس_STORAGE_ترتیب (درخت_TYPE (درخت_عملوند (arg, 0))))
	    {
	      إذا (!AGGREGATE_TYPE_P (درخت_TYPE (arg))
		  && !اشاره_گر_TYPE_P (درخت_TYPE (arg))
		  && !وکتور_TYPE_P (درخت_TYPE (arg)))
		{
		  error_at (location, "cannot take address of scalar with "
			    "reverse storage order");
		  أرجع error_mark_گره;
		}

	      إذا (درخت_کد (درخت_TYPE (arg)) == ARRAY_TYPE
		  && TYPE_معکوس_STORAGE_ترتیب (درخت_TYPE (arg)))
		warning_at (location, OPT_Wscalar_storage_ترتیب,
			    "address of array with reverse scalar storage "
			    "order requested");
	    }

	افتراضي:
	  اكسر;
	}

      إذا (!c_mark_addressable (arg))
	أرجع error_mark_گره;

      gcc_assert (درخت_کد (arg) != COMPONENT_REF
		  || !DECL_C_بیت_فیلد (درخت_عملوند (arg, 1)));

      argtype = c_build_اشاره_گر_type (argtype);

      /* ??? Cope with user tricks that amount to offsetof.  Delete this
	 when we have proper support for integer constant expressions.  */
      val = get_پایه_آدرس (arg);
      إذا (val && غیرمستقیم_REF_P (val)
          && درخت_CONSTANT (درخت_عملوند (val, 0)))
	{
	  ret = fold_offsetof (arg, argtype);
	  اذهب return_build_unary_op;
	}

      val = build1 (ADDR_عبارت, argtype, arg);

      ret = val;
      اذهب return_build_unary_op;

    حالة PAREN_عبارت:
      ret = build1 (کد, درخت_TYPE (arg), arg);
      اذهب return_build_unary_op;

    افتراضي:
      gcc_unreachable ();
    }

  إذا (argtype == NULL_درخت)
    argtype = درخت_TYPE (arg);
  إذا (درخت_کد (arg) == INTEGER_CST)
    ret = (require_constant_مقدار
	   ? fold_build1_initializer_loc (location, کد, argtype, arg)
	   : fold_build1_loc (location, کد, argtype, arg));
  وإلا
    ret = build1 (کد, argtype, arg);
 return_build_unary_op:
  gcc_assert (ret != error_mark_گره);
  إذا (درخت_کد (ret) == INTEGER_CST && !درخت_سرریز (ret)
      && !(درخت_کد (xarg) == INTEGER_CST && !درخت_سرریز (xarg)))
    ret = build1 (NOP_عبارت, درخت_TYPE (ret), ret);
  وإلا إذا (درخت_کد (ret) != INTEGER_CST && int_operands)
    ret = note_integer_operands (ret);
  إذا (eptype)
    ret = build1 (EXCESS_PRECISION_عبارت, eptype, ret);
  protected_مجموعه_عبارت_location (ret, location);
  أرجع ret;
}

/* Return nonzero if REF is an lvalue valid for this language.
   Lvalues can be assigned, unless their type has TYPE_READONLY.
   Lvalues can have their address taken, unless they have C_DECL_REGISTER.  */

منطقي
lvalue_p (const_درخت ref)
{
  ثابت تعداد درخت_کد_2 کد = درخت_کد (ref);

  بدل (کد)
    {
    حالة REALPART_عبارت:
    حالة IMAGPART_عبارت:
    حالة COMPONENT_REF:
      أرجع lvalue_p (درخت_عملوند (ref, 0));

    حالة C_MAYBE_CONST_عبارت:
      أرجع lvalue_p (درخت_عملوند (ref, 1));

    حالة COMPOUND_LITERAL_عبارت:
    حالة STRING_CST:
      أرجع درست;

    حالة MEM_REF:
    حالة هدف_MEM_REF:
      /* MEM_REFs can appear from -fgimple parsing or folding, so allow them
	 here as well.  */
    حالة غیرمستقیم_REF:
    حالة ARRAY_REF:
    حالة VAR_DECL:
    حالة PARM_DECL:
    حالة نتیجه_DECL:
    حالة ERROR_MARK:
      أرجع (درخت_کد (درخت_TYPE (ref)) != FUNCTION_TYPE
	      && درخت_کد (درخت_TYPE (ref)) != روش_TYPE);

    حالة BIND_عبارت:
      أرجع درخت_کد (درخت_TYPE (ref)) == ARRAY_TYPE;

    حالة CALL_عبارت:
      أرجع is_access_with_اندازه_p (ref);

    افتراضي:
      أرجع خطأ;
    }
}

/* Give a warning for storing in something that is read-only in GCC
   terms but not const in ISO C terms.  */

ساكن فراغ
readonly_warning (درخت arg, تعداد lvalue_use use)
{
  بدل (use)
    {
    حالة lv_تخصیص_بده:
      warning (0, "assignment of read-only location %qE", arg);
      اكسر;
    حالة lv_increment:
      warning (0, "increment of read-only location %qE", arg);
      اكسر;
    حالة lv_decrement:
      warning (0, "decrement of read-only location %qE", arg);
      اكسر;
    افتراضي:
      gcc_unreachable ();
    }
  أرجع;
}


/* Return nonzero if REF is an lvalue valid for this language;
   otherwise, print an error message and return zero.  USE says
   how the lvalue is being used and so selects the error message.
   LOCATION is the location at which any error should be reported.  */

ساكن صحيح
lvalue_or_else (location_t loc, const_درخت ref, تعداد lvalue_use use)
{
  صحيح win = lvalue_p (ref);

  إذا (!win)
    lvalue_error (loc, use);

  أرجع win;
}

/* Mark EXP saying that we need to be able to take the
   address of it; it should not be allocated in a register.
   Returns true if successful.  ARRAY_REF_P is true if this
   is for ARRAY_REF construction - in that case we don't want
   to look through VIEW_CONVERT_EXPR from VECTOR_TYPE to ARRAY_TYPE,
   it is fine to use ARRAY_REFs for vector subscripts on vector
   register variables.  If OVERRIDE_REGISTER, clear DECL_REGISTER rather
   than producing an error for taking the address of a register.  */

منطقي
c_mark_addressable (درخت نمایی_تابع, منطقي array_ref_p, منطقي override_ثبات)
{
  درخت x = نمایی_تابع;

  طالما (1)
    بدل (درخت_کد (x))
      {
      حالة VIEW_CONVERT_عبارت:
	إذا (array_ref_p
	    && درخت_کد (درخت_TYPE (x)) == ARRAY_TYPE
	    && وکتور_TYPE_P (درخت_TYPE (درخت_عملوند (x, 0))))
	  أرجع درست;
	x = درخت_عملوند (x, 0);
	اكسر;

      حالة COMPONENT_REF:
	إذا (DECL_C_بیت_فیلد (درخت_عملوند (x, 1)))
	  {
	    error ("cannot take address of bit-field %qD",
		   درخت_عملوند (x, 1));
	    أرجع خطأ;
	  }
	/* FALLTHRU */
      حالة ADDR_عبارت:
      حالة ARRAY_REF:
      حالة REALPART_عبارت:
      حالة IMAGPART_عبارت:
	x = درخت_عملوند (x, 0);
	اكسر;

      حالة COMPOUND_LITERAL_عبارت:
	إذا (C_DECL_ثبات (COMPOUND_LITERAL_عبارت_DECL (x)))
	  {
	    إذا (override_ثبات)
	      DECL_ثبات (COMPOUND_LITERAL_عبارت_DECL (x)) = 0;
	    وإلا
	      {
		error ("address of register compound literal requested");
		أرجع خطأ;
	      }
	  }
	درخت_ADDRESSABLE (x) = 1;
	درخت_ADDRESSABLE (COMPOUND_LITERAL_عبارت_DECL (x)) = 1;
	أرجع درست;

      حالة CONSTRUCTOR:
	درخت_ADDRESSABLE (x) = 1;
	أرجع درست;

      حالة VAR_DECL:
      حالة CONST_DECL:
      حالة PARM_DECL:
      حالة نتیجه_DECL:
	إذا (C_DECL_ثبات (x)
	    && DECL_NONLOCAL (x))
	  {
	    إذا (درخت_عمومی (x) || is_global_var (x))
	      {
		error
		  ("global register variable %qD used in nested function", x);
		أرجع خطأ;
	      }
	    pedwarn (درون_داد_location, 0, "register variable %qD used in nested function", x);
	  }
	وإلا إذا (C_DECL_ثبات (x))
	  {
	    إذا (درخت_عمومی (x) || is_global_var (x))
	      error ("address of global register variable %qD requested", x);
	    وإلا إذا (override_ثبات && !DECL_HARD_ثبات (x))
	      {
		DECL_ثبات (x) = 0;
		درخت_ADDRESSABLE (x) = 1;
		mark_decl_استفاده_شده (x, درست);
		أرجع درست;
	      }
	    وإلا
	      error ("address of register variable %qD requested", x);
	    أرجع خطأ;
	  }

	/* FALLTHRU */
      حالة FUNCTION_DECL:
	درخت_ADDRESSABLE (x) = 1;
	mark_decl_استفاده_شده (x, درست);
	/* FALLTHRU */
      افتراضي:
	أرجع درست;
    }
}

/* Convert EXPR to TYPE, warning about conversion problems with
   constants.  SEMANTIC_TYPE is the type this conversion would use
   without excess precision. If SEMANTIC_TYPE is NULL, this function
   is equivalent to convert_and_check. This function is a wrapper that
   handles conversions that may be different than
   the usual ones because of excess precision.  */

ساكن درخت
ep_convert_and_check (location_t loc, درخت type, درخت عبارت,
		      درخت semantic_type)
{
  إذا (درخت_TYPE (عبارت) == type)
    أرجع عبارت;

  /* For C11, integer conversions may have results with excess
     precision.  */
  إذا (flag_isoc11 || !semantic_type)
    أرجع convert_and_check (loc, type, عبارت);

  إذا (درخت_کد (درخت_TYPE (عبارت)) == INTEGER_TYPE
      && درخت_TYPE (عبارت) != semantic_type)
    {
      /* For integers, we need to check the real conversion, not
	 the conversion to the excess precision type.  */
      عبارت = convert_and_check (loc, semantic_type, عبارت);
    }
  /* Result type is the excess precision type, which should be
     large enough, so do not check.  */
  أرجع convert (type, عبارت);
}

/* If EXPR refers to a built-in declared without a prototype returns
   the actual type of the built-in and, if non-null, set *BLTIN to
   a pointer to the built-in.  Otherwise return the type of EXPR
   and clear *BLTIN if non-null.  */

ساكن درخت
type_or_builtin_type (درخت عبارت, درخت *bltin = عدم)
{
  درخت dummy;
  إذا (!bltin)
    bltin = &dummy;

  *bltin = NULL_درخت;

  درخت type = درخت_TYPE (عبارت);
  إذا (درخت_کد (عبارت) != ADDR_عبارت)
    أرجع type;

  درخت oper = درخت_عملوند (عبارت, 0);
  إذا (!DECL_P (oper)
      || درخت_کد (oper) != FUNCTION_DECL
      || !fndecl_built_درون_p (oper, BUILT_درون_نرمال))
    أرجع type;

  built_درون_function کد = DECL_FUNCTION_کد (oper);
  إذا (!C_DECL_BUILTIN_PROTOTYPE (oper))
    أرجع type;

  إذا ((*bltin = builtin_decl_implicit (کد)))
    type = c_build_اشاره_گر_type (درخت_TYPE (*bltin));

  أرجع type;
}

/* Build and return a conditional expression IFEXP ? OP1 : OP2.  If
   IFEXP_BCP then the condition is a call to __builtin_constant_p, and
   if folded to an integer constant then the unselected half may
   contain arbitrary operations not normally permitted in constant
   expressions.  Set the location of the expression to LOC.  */

درخت
build_conditional_عبارت (location_t colon_loc, درخت ifexp, منطقي ifexp_bcp,
			درخت op1, درخت op1_original_type, location_t op1_loc,
			درخت op2, درخت op2_original_type, location_t op2_loc)
{
  درخت type1;
  درخت type2;
  درخت نتیجه_type = عدم;
  درخت semantic_نتیجه_type = عدم;
  درخت orig_op1 = op1, orig_op2 = op2;
  منطقي int_const, op1_int_operands, op2_int_operands, int_operands;
  منطقي ifexp_int_operands;
  درخت ret;

  op1_int_operands = عبارت_INT_CONST_OPERANDS (orig_op1);
  إذا (op1_int_operands)
    op1 = remove_c_maybe_const_عبارت (op1);
  op2_int_operands = عبارت_INT_CONST_OPERANDS (orig_op2);
  إذا (op2_int_operands)
    op2 = remove_c_maybe_const_عبارت (op2);
  ifexp_int_operands = عبارت_INT_CONST_OPERANDS (ifexp);
  إذا (ifexp_int_operands)
    ifexp = remove_c_maybe_const_عبارت (ifexp);

  /* Promote both alternatives.  */

  إذا (درخت_کد (درخت_TYPE (op1)) != VOID_TYPE)
    op1 = default_conversion (op1);
  إذا (درخت_کد (درخت_TYPE (op2)) != VOID_TYPE)
    op2 = default_conversion (op2);

  إذا (درخت_کد (ifexp) == ERROR_MARK
      || درخت_کد (درخت_TYPE (op1)) == ERROR_MARK
      || درخت_کد (درخت_TYPE (op2)) == ERROR_MARK)
    أرجع error_mark_گره;

  درخت bltin1 = NULL_درخت;
  درخت bltin2 = NULL_درخت;
  type1 = type_or_builtin_type (op1, &bltin1);
  ثابت تعداد درخت_کد_2 code1 = درخت_کد (type1);
  type2 = type_or_builtin_type (op2, &bltin2);
  ثابت تعداد درخت_کد_2 code2 = درخت_کد (type2);

  إذا (code1 == اشاره_گر_TYPE && reject_gcc_builtin (op1))
    أرجع error_mark_گره;

  إذا (code2 == اشاره_گر_TYPE && reject_gcc_builtin (op2))
    أرجع error_mark_گره;

  /* C90 does not permit non-lvalue arrays in conditional expressions.
     In C99 they will be pointers by now.  */
  إذا (code1 == ARRAY_TYPE || code2 == ARRAY_TYPE)
    {
      error_at (colon_loc, "non-lvalue array in conditional expression");
      أرجع error_mark_گره;
    }

  إذا ((درخت_کد (op1) == EXCESS_PRECISION_عبارت
       || درخت_کد (op2) == EXCESS_PRECISION_عبارت)
      && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	  || code1 == COMPLEX_TYPE || code1 == BITINT_TYPE)
      && (code2 == INTEGER_TYPE || code2 == REAL_TYPE
	  || code2 == COMPLEX_TYPE || code2 == BITINT_TYPE))
    {
      semantic_نتیجه_type = c_common_type (type1, type2);
      إذا (درخت_کد (op1) == EXCESS_PRECISION_عبارت)
	{
	  op1 = درخت_عملوند (op1, 0);
	  type1 = درخت_TYPE (op1);
	  gcc_assert (درخت_کد (type1) == code1);
	}
      إذا (درخت_کد (op2) == EXCESS_PRECISION_عبارت)
	{
	  op2 = درخت_عملوند (op2, 0);
	  type2 = درخت_TYPE (op2);
	  gcc_assert (درخت_کد (type2) == code2);
	}
    }

  إذا (warn_cxx_compat)
    {
      درخت t1 = op1_original_type ? op1_original_type : درخت_TYPE (orig_op1);
      درخت t2 = op2_original_type ? op2_original_type : درخت_TYPE (orig_op2);

      إذا (درخت_کد (t1) == ENUMERAL_TYPE
	  && درخت_کد (t2) == ENUMERAL_TYPE
	  && TYPE_MAIN_VARIANT (t1) != TYPE_MAIN_VARIANT (t2))
	warning_at (colon_loc, OPT_Wc___compat,
		    "different enum types in conditional is "
		    "invalid in C++: %qT vs %qT", t1, t2);
    }

  إذا (warn_zero_as_null_اشاره_گر_constant
      && c_inhibit_evaluation_warnings == 0)
    {
      إذا ((code1 == اشاره_گر_TYPE || code1 == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type2) && null_اشاره_گر_constant_p (orig_op2))
	warning_at (op2_loc, OPT_Wzero_as_null_اشاره_گر_constant,
		    "zero as null pointer constant");

      إذا ((code2 == اشاره_گر_TYPE || code2 == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type1) && null_اشاره_گر_constant_p (orig_op1))
	warning_at (op1_loc, OPT_Wzero_as_null_اشاره_گر_constant,
		    "zero as null pointer constant");
    }

  /* Quickly detect the usual case where op1 and op2 have the same type
     after promotion.  */
  إذا (TYPE_MAIN_VARIANT (type1) == TYPE_MAIN_VARIANT (type2))
    {
      إذا (type1 == type2)
	نتیجه_type = type1;
      وإلا
	نتیجه_type = TYPE_MAIN_VARIANT (type1);
    }
  وإلا إذا ((code1 == INTEGER_TYPE || code1 == REAL_TYPE
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
      إذا (flag_isoc11)
	{
	  درخت eptype;
	  إذا (ANY_INTEGRAL_TYPE_P (type1)
	      && (eptype = excess_precision_type (type2)) != NULL_درخت)
	    {
	      eptype2 = eptype;
	      إذا (!semantic_نتیجه_type)
		semantic_نتیجه_type = c_common_type (type1, type2);
	    }
	  وإلا إذا (ANY_INTEGRAL_TYPE_P (type2)
		   && (eptype = excess_precision_type (type1)) != NULL_درخت)
	    {
	      eptype1 = eptype;
	      إذا (!semantic_نتیجه_type)
		semantic_نتیجه_type = c_common_type (type1, type2);
	    }
	}
      نتیجه_type = c_common_type (eptype1, eptype2);
      إذا (نتیجه_type == error_mark_گره)
	أرجع error_mark_گره;
      do_warn_double_promotion (نتیجه_type, type1, type2,
				"implicit conversion from %qT to %qT to "
				"match other result of conditional",
				colon_loc);

      /* If -Wsign-compare, warn here if type1 and type2 have
	 different signedness.  We'll promote the signed to unsigned
	 and later code won't know it used to be different.
	 Do this check on the original types, so that explicit casts
	 will be considered, but default promotions won't.  */
      إذا (c_inhibit_evaluation_warnings == 0)
	{
	  صحيح unsigned_op1 = TYPE_UNSIGNED (درخت_TYPE (orig_op1));
	  صحيح unsigned_op2 = TYPE_UNSIGNED (درخت_TYPE (orig_op2));

	  إذا (unsigned_op1 ^ unsigned_op2)
	    {
	      /* Do not warn if the result type is signed, since the
		 signed type will only be chosen if it can represent
		 all the values of the unsigned type.  */
	      إذا (!TYPE_UNSIGNED (نتیجه_type))
		/* OK */;
	      وإلا
		{
		  منطقي op1_maybe_const = درست;
		  منطقي op2_maybe_const = درست;

		  /* Do not warn if the signed quantity is an
		     unsuffixed integer literal (or some static
		     constant expression involving such literals) and
		     it is non-negative.  This warning requires the
		     operands to be folded for best results, so do
		     that folding in this case even without
		     warn_sign_compare to avoid warning options
		     possibly affecting code generation.  */
		  c_inhibit_evaluation_warnings
		    += (ifexp == truthvalue_false_گره);
		  op1 = c_fully_fold (op1, require_constant_مقدار,
				      &op1_maybe_const);
		  c_inhibit_evaluation_warnings
		    -= (ifexp == truthvalue_false_گره);

		  c_inhibit_evaluation_warnings
		    += (ifexp == truthvalue_true_گره);
		  op2 = c_fully_fold (op2, require_constant_مقدار,
				      &op2_maybe_const);
		  c_inhibit_evaluation_warnings
		    -= (ifexp == truthvalue_true_گره);

		  إذا (warn_sign_compare)
		    {
		      إذا ((unsigned_op2
			   && درخت_عبارت_nonnegative_p (op1))
			  || (unsigned_op1
			      && درخت_عبارت_nonnegative_p (op2)))
			/* OK */;
		      وإلا إذا (unsigned_op2)
			warning_at (op1_loc, OPT_Wsign_compare,
				    "operand of %<?:%> changes signedness from "
				    "%qT to %qT due to unsignedness of other "
				    "operand", درخت_TYPE (orig_op1),
				    درخت_TYPE (orig_op2));
		      وإلا
			warning_at (op2_loc, OPT_Wsign_compare,
				    "operand of %<?:%> changes signedness from "
				    "%qT to %qT due to unsignedness of other "
				    "operand", درخت_TYPE (orig_op2),
				    درخت_TYPE (orig_op1));
		    }
		  إذا (!op1_maybe_const || درخت_کد (op1) != INTEGER_CST)
		    op1 = c_wrap_maybe_const (op1, !op1_maybe_const);
		  إذا (!op2_maybe_const || درخت_کد (op2) != INTEGER_CST)
		    op2 = c_wrap_maybe_const (op2, !op2_maybe_const);
		}
	    }
	}
    }
  وإلا إذا (code1 == VOID_TYPE || code2 == VOID_TYPE)
    {
      إذا (code1 != VOID_TYPE || code2 != VOID_TYPE)
	pedwarn (colon_loc, OPT_Wpedantic,
		 "ISO C forbids conditional expr with only one void side");
      نتیجه_type = void_type_گره;
    }
  وإلا إذا (code1 == اشاره_گر_TYPE && code2 == اشاره_گر_TYPE)
    {
      addr_space_t as1 = TYPE_ADDR_SPACE (درخت_TYPE (type1));
      addr_space_t as2 = TYPE_ADDR_SPACE (درخت_TYPE (type2));
      addr_space_t as_common;

      إذا (comp_هدف_types (colon_loc, type1, type2))
	{
	  ifexp = save_عبارت (ifexp);
	  نتیجه_type = common_اشاره_گر_type (type1, type2, ifexp);
	}
      وإلا إذا (null_اشاره_گر_constant_p (orig_op1))
	نتیجه_type = type2;
      وإلا إذا (null_اشاره_گر_constant_p (orig_op2))
	نتیجه_type = type1;
      وإلا إذا (!addr_space_superset (as1, as2, &as_common))
	{
	  error_at (colon_loc, "pointers to disjoint address spaces "
		    "used in conditional expression");
	  أرجع error_mark_گره;
	}
      وإلا إذا ((VOID_TYPE_P (درخت_TYPE (type1))
		&& !TYPE_ATOMIC (درخت_TYPE (type1)))
	       || (VOID_TYPE_P (درخت_TYPE (type2))
		   && !TYPE_ATOMIC (درخت_TYPE (type2))))
	{
	  درخت t1 = درخت_TYPE (type1);
	  درخت t2 = درخت_TYPE (type2);
	  إذا (!(VOID_TYPE_P (t1)
		&& !TYPE_ATOMIC (t1)))
	   {
	     /* roles are swapped */
	     t1 = t2;
	     t2 = درخت_TYPE (type1);
	   }
	  درخت t2_stripped = strip_array_types (t2);
	  إذا ((درخت_کد (t2) == ARRAY_TYPE)
	      && (TYPE_QUALS (t2_stripped) & ~TYPE_QUALS (t1)))
	    {
	      إذا (!flag_isoc23)
		warning_at (colon_loc, OPT_Wdiscarded_array_qualifiers,
			    "pointer to array loses qualifier "
			    "in conditional expression");
	      وإلا إذا (warn_c11_c23_compat > 0)
		warning_at (colon_loc, OPT_Wc11_c23_compat,
			    "pointer to array loses qualifier "
			    "in conditional expression in ISO C before C23");
	    }
	  إذا (درخت_کد (t2) == FUNCTION_TYPE)
	    pedwarn (colon_loc, OPT_Wpedantic,
		     "ISO C forbids conditional expr between "
		     "%<void *%> and function pointer");
	  /* for array, use qualifiers of element type */
	  إذا (flag_isoc23)
	    t2 = t2_stripped;
	  نتیجه_type = c_build_اشاره_گر_type (qualify_type (t1, t2));
	}
      /* Objective-C pointer comparisons are a bit more lenient.  */
      وإلا إذا (objc_have_common_type (type1, type2, -3, NULL_درخت))
	نتیجه_type = objc_common_type (type1, type2);
      وإلا
	{
	  صحيح qual = ENCODE_QUAL_ADDR_SPACE (as_common);
	  تعداد diagnostics::نوع نوع = diagnostics::نوع::permerror;
	  إذا (!flag_isoc99)
	    /* This downgrade to a warning ensures that -std=gnu89
	       -pedantic-errors does not flag these mismatches between
	       builtins as errors (as diagnostics::kind::permerror would)
	       ISO C99 and later do not have implicit function declarations,
	       so the mismatch cannot occur naturally there.  */
	    نوع = (bltin1 && bltin2
		    ? diagnostics::نوع::warning
		    : diagnostics::نوع::pedwarn);
	  إذا (emit_diagnostic (نوع, colon_loc, OPT_Wincompatible_اشاره_گر_types,
			       "pointer type mismatch "
			       "in conditional expression"))
	    {
	      inform (op1_loc, "first expression has type %qT", type1);
	      inform (op2_loc, "second expression has type %qT", type2);
	    }
	  نتیجه_type = c_build_اشاره_گر_type
			  (c_build_qualified_type (void_type_گره, qual));
	}
    }
  وإلا إذا (code1 == اشاره_گر_TYPE
	   && (code2 == INTEGER_TYPE || code2 == BITINT_TYPE))
    {
      إذا (!null_اشاره_گر_constant_p (orig_op2))
	permerror_opt (colon_loc, OPT_Wint_conversion,
		       "pointer/integer type mismatch "
		       "in conditional expression");
      وإلا
	{
	  op2 = null_اشاره_گر_گره;
	}
      نتیجه_type = type1;
    }
  وإلا إذا (code2 == اشاره_گر_TYPE
	   && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
    {
      إذا (!null_اشاره_گر_constant_p (orig_op1))
	permerror_opt (colon_loc, OPT_Wint_conversion,
		       "pointer/integer type mismatch "
		       "in conditional expression");
      وإلا
	{
	  op1 = null_اشاره_گر_گره;
	}
      نتیجه_type = type2;
    }
  /* 6.5.15: "if one is a null pointer constant (other than a pointer) or has
     type nullptr_t and the other is a pointer, the result type is the pointer
     type."  */
  وإلا إذا (code1 == NULLPTR_TYPE && code2 == اشاره_گر_TYPE)
    نتیجه_type = type2;
  وإلا إذا (code1 == اشاره_گر_TYPE && code2 == NULLPTR_TYPE)
    نتیجه_type = type1;
  وإلا إذا (رکورد_OR_UNION_TYPE_P (type1) && رکورد_OR_UNION_TYPE_P (type2)
	   && comptypes (TYPE_MAIN_VARIANT (type1),
			 TYPE_MAIN_VARIANT (type2)))
    نتیجه_type = مرکب_type (TYPE_MAIN_VARIANT (type1),
				  TYPE_MAIN_VARIANT (type2));

  إذا (!نتیجه_type)
    {
      إذا (flag_cond_mismatch)
	نتیجه_type = void_type_گره;
      وإلا
	{
	  error_at (colon_loc, "type mismatch in conditional expression");
	  أرجع error_mark_گره;
	}
    }

  /* Merge const and volatile flags of the incoming types.  */
  نتیجه_type
    = build_type_variant (نتیجه_type,
			  TYPE_READONLY (type1) || TYPE_READONLY (type2),
			  TYPE_VOLATILE (type1) || TYPE_VOLATILE (type2));

  op1 = ep_convert_and_check (colon_loc, نتیجه_type, op1,
			      semantic_نتیجه_type);
  op2 = ep_convert_and_check (colon_loc, نتیجه_type, op2,
			      semantic_نتیجه_type);

  إذا (ifexp_bcp && ifexp == truthvalue_true_گره)
    {
      op2_int_operands = درست;
      op1 = c_fully_fold (op1, require_constant_مقدار, عدم);
    }
  إذا (ifexp_bcp && ifexp == truthvalue_false_گره)
    {
      op1_int_operands = درست;
      op2 = c_fully_fold (op2, require_constant_مقدار, عدم);
    }
  int_const = int_operands = (ifexp_int_operands
			      && op1_int_operands
			      && op2_int_operands);
  إذا (int_operands)
    {
      int_const = ((ifexp == truthvalue_true_گره
		    && درخت_کد (orig_op1) == INTEGER_CST
		    && !درخت_سرریز (orig_op1))
		   || (ifexp == truthvalue_false_گره
		       && درخت_کد (orig_op2) == INTEGER_CST
		       && !درخت_سرریز (orig_op2)));
    }

  /* Need to convert condition operand into a vector mask.  */
  إذا (وکتور_TYPE_P (درخت_TYPE (ifexp)))
    {
      درخت vectype = درخت_TYPE (ifexp);
      درخت elem_type = درخت_TYPE (vectype);
      درخت zero = build_int_cst (elem_type, 0);
      درخت zero_vec = build_وکتور_from_val (vectype, zero);
      درخت cmp_type = truth_type_for (vectype);
      ifexp = build2 (NE_عبارت, cmp_type, ifexp, zero_vec);
    }

  إذا (int_const || (ifexp_bcp && درخت_کد (ifexp) == INTEGER_CST))
    ret = fold_build3_loc (colon_loc, COND_عبارت, نتیجه_type, ifexp, op1, op2);
  وإلا
    {
      إذا (int_operands)
	{
	  /* Use c_fully_fold here, since C_MAYBE_CONST_EXPR might be
	     nested inside of the expression.  */
	  op1 = c_fully_fold (op1, خطأ, عدم);
	  op2 = c_fully_fold (op2, خطأ, عدم);
	}
      ret = build3 (COND_عبارت, نتیجه_type, ifexp, op1, op2);
      إذا (int_operands)
	ret = note_integer_operands (ret);
    }
  إذا (semantic_نتیجه_type)
    ret = build1 (EXCESS_PRECISION_عبارت, semantic_نتیجه_type, ret);

  protected_مجموعه_عبارت_location (ret, colon_loc);

  /* If the OP1 and OP2 are the same and don't have side-effects,
     warn here, because the COND_EXPR will be turned into OP1.  */
  إذا (warn_duplicated_branches
      && درخت_کد (ret) == COND_عبارت
      && (op1 == op2 || عملوند_equal_p (op1, op2, OEP_آدرس_از_SAME_فیلد)))
    warning_at (عبارت_LOCATION (ret), OPT_Wduplicated_branches,
		"this condition has identical branches");

  أرجع ret;
}

/* EXPR is an expression, location LOC, whose result is discarded.
   Warn if it is a call to a nodiscard function (or a COMPOUND_EXPR
   whose right-hand operand is such a call, possibly recursively).  */

ساكن فراغ
maybe_warn_nodiscard (location_t loc, درخت عبارت)
{
  إذا (VOID_TYPE_P (درخت_TYPE (عبارت)))
    أرجع;
  طالما (درخت_کد (عبارت) == COMPOUND_عبارت)
    {
      عبارت = درخت_عملوند (عبارت, 1);
      إذا (عبارت_HAS_LOCATION (عبارت))
	loc = عبارت_LOCATION (عبارت);
    }
  إذا (درخت_کد (عبارت) != CALL_عبارت)
    أرجع;
  درخت fn = CALL_عبارت_FN (عبارت);
  إذا (!fn)
    أرجع;
  درخت attr;
  إذا (درخت_کد (fn) == ADDR_عبارت
      && درخت_کد (درخت_عملوند (fn, 0)) == FUNCTION_DECL
      && (attr = lookup_attribute ("nodiscard",
				   DECL_صفات (درخت_عملوند (fn, 0)))))
    {
      fn = درخت_عملوند (fn, 0);
      درخت آرگومانها = درخت_مقدار (attr);
      إذا (آرگومانها)
	آرگومانها = درخت_مقدار (آرگومانها);
      auto_diagnostic_گروه d;
      auto_urlify_صفات sentinel;
      صحيح warned;
      إذا (آرگومانها)
	warned = warning_at (loc, OPT_Wunused_نتیجه,
			     "ignoring return value of %qD, declared with "
			     "attribute %<nodiscard%>: %E", fn, آرگومانها);
      وإلا
	warned = warning_at (loc, OPT_Wunused_نتیجه,
			     "ignoring return value of %qD, declared with "
			     "attribute %<nodiscard%>", fn);
      إذا (warned)
	inform (DECL_منبع_LOCATION (fn), "declared here");
    }
  وإلا
    {
      درخت rettype = درخت_TYPE (درخت_TYPE (درخت_TYPE (fn)));
      attr = lookup_attribute ("nodiscard", TYPE_صفات (rettype));
      إذا (!attr)
	أرجع;
      درخت آرگومانها = درخت_مقدار (attr);
      إذا (آرگومانها)
	آرگومانها = درخت_مقدار (آرگومانها);
      auto_diagnostic_گروه d;
      auto_urlify_صفات sentinel;
      صحيح warned;
      إذا (آرگومانها)
	warned = warning_at (loc, OPT_Wunused_نتیجه,
			     "ignoring return value of type %qT, declared "
			     "with attribute %<nodiscard%>: %E",
			     rettype, آرگومانها);
      وإلا
	warned = warning_at (loc, OPT_Wunused_نتیجه,
			     "ignoring return value of type %qT, declared "
			     "with attribute %<nodiscard%>", rettype);
      إذا (warned)
	{
	  إذا (درخت_کد (fn) == ADDR_عبارت)
	    {
	      fn = درخت_عملوند (fn, 0);
	      إذا (درخت_کد (fn) == FUNCTION_DECL)
		inform (DECL_منبع_LOCATION (fn),
			"in call to %qD, declared here", fn);
	    }
	}
    }
}

/* Return a compound expression that performs two expressions and
   returns the value of the second of them.

   LOC is the location of the COMPOUND_EXPR.  */

درخت
build_compound_عبارت (location_t loc, درخت expr1, درخت expr2)
{
  منطقي expr1_int_operands, expr2_int_operands;
  درخت eptype = NULL_درخت;
  درخت ret;

  expr1_int_operands = عبارت_INT_CONST_OPERANDS (expr1);
  إذا (expr1_int_operands)
    expr1 = remove_c_maybe_const_عبارت (expr1);
  expr2_int_operands = عبارت_INT_CONST_OPERANDS (expr2);
  إذا (expr2_int_operands)
    expr2 = remove_c_maybe_const_عبارت (expr2);

  إذا (درخت_کد (expr1) == EXCESS_PRECISION_عبارت)
    expr1 = درخت_عملوند (expr1, 0);
  إذا (درخت_کد (expr2) == EXCESS_PRECISION_عبارت)
    {
      eptype = درخت_TYPE (expr2);
      expr2 = درخت_عملوند (expr2, 0);
    }

  إذا (!درخت_SIDE_EFFECTS (expr1))
    {
      /* The left-hand operand of a comma expression is like an expression
	 statement: with -Wunused, we should warn if it doesn't have
	 any side-effects, unless it was explicitly cast to (void).  */
      إذا (warn_استفادهنشده_مقدار)
	{
	  إذا (VOID_TYPE_P (درخت_TYPE (expr1))
	      && CONVERT_عبارت_P (expr1))
	    ; /* (void) a, b */
	  وإلا إذا (VOID_TYPE_P (درخت_TYPE (expr1))
		   && درخت_کد (expr1) == COMPOUND_عبارت
		   && CONVERT_عبارت_P (درخت_عملوند (expr1, 1)))
	    ; /* (void) a, (void) b, c */
	  وإلا
	    warning_at (loc, OPT_Wunused_مقدار,
			"left-hand operand of comma expression has no effect");
	}
    }
  وإلا إذا (درخت_کد (expr1) == COMPOUND_عبارت
	   && warn_استفادهنشده_مقدار)
    {
      درخت r = expr1;
      location_t cloc = loc;
      طالما (درخت_کد (r) == COMPOUND_عبارت)
        {
	  إذا (عبارت_HAS_LOCATION (r))
	    cloc = عبارت_LOCATION (r);
	  r = درخت_عملوند (r, 1);
	}
      إذا (!درخت_SIDE_EFFECTS (r)
	  && !VOID_TYPE_P (درخت_TYPE (r))
	  && !CONVERT_عبارت_P (r))
	warning_at (cloc, OPT_Wunused_مقدار,
	            "right-hand operand of comma expression has no effect");
    }

  /* With -Wunused, we should also warn if the left-hand operand does have
     side-effects, but computes a value which is not used.  For example, in
     `foo() + bar(), baz()' the result of the `+' operator is not used,
     so we should issue a warning.  */
  وإلا إذا (warn_استفادهنشده_مقدار)
    warn_if_استفادهنشده_مقدار (expr1, loc);

  maybe_warn_nodiscard (loc, expr1);

  إذا (expr2 == error_mark_گره)
    أرجع error_mark_گره;

  ret = build2 (COMPOUND_عبارت, درخت_TYPE (expr2), expr1, expr2);

  إذا (flag_isoc99
      && expr1_int_operands
      && expr2_int_operands)
    ret = note_integer_operands (ret);

  إذا (eptype)
    ret = build1 (EXCESS_PRECISION_عبارت, eptype, ret);

  protected_مجموعه_عبارت_location (ret, loc);
  أرجع ret;
}

/* Issue -Wcast-qual warnings when appropriate.  TYPE is the type to
   which we are casting.  OTYPE is the type of the expression being
   cast.  Both TYPE and OTYPE are pointer types.  LOC is the location
   of the cast.  -Wcast-qual appeared on the command line.  Named
   address space qualifiers are not handled here, because they result
   in different warnings.  */

ساكن فراغ
handle_warn_cast_qual (location_t loc, درخت type, درخت otype)
{
  درخت درون_type = type;
  درخت درون_otype = otype;
  صحيح added = 0;
  صحيح discarded = 0;
  منطقي is_const;

  /* Check that the qualifiers on IN_TYPE are a superset of the
     qualifiers of IN_OTYPE.  The outermost level of POINTER_TYPE
     nodes is uninteresting and we stop as soon as we hit a
     non-POINTER_TYPE node on either type.  */
  افعل
    {
      درون_otype = درخت_TYPE (درون_otype);
      درون_type = درخت_TYPE (درون_type);

      /* GNU C allows cv-qualified function types.  'const' means the
	 function is very pure, 'volatile' means it can't return.  We
	 need to warn when such qualifiers are added, not when they're
	 taken away.  */
      إذا (درخت_کد (درون_otype) == FUNCTION_TYPE
	  && درخت_کد (درون_type) == FUNCTION_TYPE)
	added |= (TYPE_QUALS_NO_ADDR_SPACE (درون_type)
		  & ~TYPE_QUALS_NO_ADDR_SPACE (درون_otype));
      وإلا
	discarded |= (TYPE_QUALS_NO_ADDR_SPACE (درون_otype)
		      & ~TYPE_QUALS_NO_ADDR_SPACE (درون_type));
    }
  طالما (درخت_کد (درون_type) == اشاره_گر_TYPE
	 && درخت_کد (درون_otype) == اشاره_گر_TYPE);

  إذا (added)
    warning_at (loc, OPT_Wcast_qual,
		"cast adds %q#v qualifier to function type", added);

  إذا (discarded)
    /* There are qualifiers present in IN_OTYPE that are not present
       in IN_TYPE.  */
    warning_at (loc, OPT_Wcast_qual,
		"cast discards %qv qualifier from pointer target type",
		discarded);

  إذا (added || discarded)
    أرجع;

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

  إذا (TYPE_MAIN_VARIANT (درون_type) != TYPE_MAIN_VARIANT (درون_otype))
    أرجع;
  إذا (درخت_کد (درخت_TYPE (type)) != اشاره_گر_TYPE)
    أرجع;

  درون_type = type;
  درون_otype = otype;
  is_const = TYPE_READONLY (درخت_TYPE (درون_type));
  افعل
    {
      درون_type = درخت_TYPE (درون_type);
      درون_otype = درخت_TYPE (درون_otype);
      إذا ((TYPE_QUALS (درون_type) &~ TYPE_QUALS (درون_otype)) != 0
	  && !is_const)
	{
	  warning_at (loc, OPT_Wcast_qual,
		      "to be safe all intermediate pointers in cast from "
                      "%qT to %qT must be %<const%> qualified",
		      otype, type);
	  اكسر;
	}
      إذا (is_const)
	is_const = TYPE_READONLY (درون_type);
    }
  طالما (درخت_کد (درون_type) == اشاره_گر_TYPE);
}

/* Heuristic check if two parameter types can be considered ABI-equivalent.  */

ساكن منطقي
c_امن_arg_type_equiv_p (درخت t1, درخت t2)
{
  إذا (error_عملوند_p (t1) || error_عملوند_p (t2))
    أرجع درست;

  t1 = TYPE_MAIN_VARIANT (t1);
  t2 = TYPE_MAIN_VARIANT (t2);

  إذا (درخت_کد (t1) == اشاره_گر_TYPE
      && درخت_کد (t2) == اشاره_گر_TYPE)
    أرجع درست;

  /* Only the precision of the parameter matters.  This check should
     make sure that the callee does not see undefined values in argument
     registers.  */
  إذا (INTEGRAL_TYPE_P (t1)
      && INTEGRAL_TYPE_P (t2)
      && TYPE_PRECISION (t1) == TYPE_PRECISION (t2))
    أرجع درست;

  أرجع comptypes (t1, t2);
}

/* Check if a type cast between two function types can be considered safe.  */

ساكن منطقي
c_امن_function_type_cast_p (درخت t1, درخت t2)
{
  إذا (درخت_TYPE (t1) == void_type_گره &&
      TYPE_ARG_TYPES (t1) == void_list_گره)
    أرجع درست;

  إذا (درخت_TYPE (t2) == void_type_گره &&
      TYPE_ARG_TYPES (t2) == void_list_گره)
    أرجع درست;

  إذا (!c_امن_arg_type_equiv_p (درخت_TYPE (t1), درخت_TYPE (t2)))
    أرجع خطأ;

  لكل (t1 = TYPE_ARG_TYPES (t1), t2 = TYPE_ARG_TYPES (t2);
       t1 && t2;
       t1 = درخت_CHAIN (t1), t2 = درخت_CHAIN (t2))
    إذا (!c_امن_arg_type_equiv_p (درخت_مقدار (t1), درخت_مقدار (t2)))
      أرجع خطأ;

  أرجع درست;
}

/* Build an expression representing a cast to type TYPE of expression EXPR.
   LOC is the location of the cast-- typically the open paren of the cast.  */

درخت
build_c_cast (location_t loc, درخت type, درخت عبارت)
{
  درخت مقدار;

  منطقي int_operands = عبارت_INT_CONST_OPERANDS (عبارت);

  إذا (درخت_کد (عبارت) == EXCESS_PRECISION_عبارت)
    عبارت = درخت_عملوند (عبارت, 0);

  مقدار = عبارت;
  إذا (int_operands)
    مقدار = remove_c_maybe_const_عبارت (مقدار);

  إذا (type == error_mark_گره || عبارت == error_mark_گره)
    أرجع error_mark_گره;

  /* The ObjC front-end uses TYPE_MAIN_VARIANT to tie together types differing
     only in <protocol> qualifications.  But when constructing cast expressions,
     the protocols do matter and must be kept around.  */
  إذا (objc_is_object_ptr (type) && objc_is_object_ptr (درخت_TYPE (عبارت)))
    أرجع build1 (NOP_عبارت, type, عبارت);

  type = TYPE_MAIN_VARIANT (type);

  إذا (درخت_کد (type) == ARRAY_TYPE)
    {
      error_at (loc, "cast specifies array type");
      أرجع error_mark_گره;
    }

  إذا (درخت_کد (type) == FUNCTION_TYPE)
    {
      error_at (loc, "cast specifies function type");
      أرجع error_mark_گره;
    }

  إذا (!VOID_TYPE_P (type))
    {
      مقدار = require_complete_type (loc, مقدار);
      إذا (مقدار == error_mark_گره)
	أرجع error_mark_گره;
    }

  إذا (type == TYPE_MAIN_VARIANT (درخت_TYPE (مقدار)))
    {
      إذا (رکورد_OR_UNION_TYPE_P (type)
	  && pedwarn (loc, OPT_Wpedantic,
		      "ISO C forbids casting nonscalar to the same type"))
	      ;
      وإلا إذا (warn_useless_cast && c_inhibit_evaluation_warnings == 0)
	warning_at (loc, OPT_Wuseless_cast,
		    "useless cast to type %qT", type);

      /* Convert to remove any qualifiers from VALUE's type.  */
      مقدار = convert (type, مقدار);
    }
  وإلا إذا (درخت_کد (type) == UNION_TYPE)
    {
      درخت فیلد_2;

      لكل (فیلد_2 = TYPE_FIELDS (type); فیلد_2; فیلد_2 = DECL_CHAIN (فیلد_2))
	إذا (درخت_TYPE (فیلد_2) != error_mark_گره
	    && comptypes (TYPE_MAIN_VARIANT (درخت_TYPE (فیلد_2)),
			  TYPE_MAIN_VARIANT (درخت_TYPE (مقدار))))
	  اكسر;

      إذا (فیلد_2)
	{
	  درخت t;
	  منطقي maybe_const = درست;

	  pedwarn (loc, OPT_Wpedantic, "ISO C forbids casts to union type");
	  t = c_fully_fold (مقدار, خطأ, &maybe_const);
	  t = build_constructor_single (type, فیلد_2, t);
	  إذا (!maybe_const)
	    t = c_wrap_maybe_const (t, درست);
	  t = digest_init (loc, فیلد_2, type, t,
			   NULL_درخت, خطأ, خطأ, خطأ, درست, خطأ, خطأ);
	  درخت_CONSTANT (t) = درخت_CONSTANT (مقدار);
	  أرجع t;
	}
      error_at (loc, "cast to union type from type not present in union");
      أرجع error_mark_گره;
    }
  وإلا
    {
      درخت otype, ovalue;

      إذا (type == void_type_گره)
	{
	  درخت t = build1 (CONVERT_عبارت, type, مقدار);
	  مجموعه_عبارت_LOCATION (t, loc);
	  أرجع t;
	}

      otype = درخت_TYPE (مقدار);

      /* Optionally warn about potentially worrisome casts.  */
      إذا (warn_cast_qual
	  && درخت_کد (type) == اشاره_گر_TYPE
	  && درخت_کد (otype) == اشاره_گر_TYPE)
	handle_warn_cast_qual (loc, type, otype);

      /* Warn about conversions between pointers to disjoint
	 address spaces.  */
      إذا (درخت_کد (type) == اشاره_گر_TYPE
	  && درخت_کد (otype) == اشاره_گر_TYPE
	  && !null_اشاره_گر_constant_p (مقدار))
	{
	  addr_space_t as_مقصد = TYPE_ADDR_SPACE (درخت_TYPE (type));
	  addr_space_t as_from = TYPE_ADDR_SPACE (درخت_TYPE (otype));
	  addr_space_t as_common;

	  إذا (!addr_space_superset (as_مقصد, as_from, &as_common))
	    {
	      إذا (ADDR_SPACE_GENERIC_P (as_from))
		warning_at (loc, 0, "cast to %qs address space pointer "
			    "from disjoint generic address space pointer",
			    c_addr_space_name (as_مقصد));

	      وإلا إذا (ADDR_SPACE_GENERIC_P (as_مقصد))
		warning_at (loc, 0, "cast to generic address space pointer "
			    "from disjoint %qs address space pointer",
			    c_addr_space_name (as_from));

	      وإلا
		warning_at (loc, 0, "cast to %qs address space pointer "
			    "from disjoint %qs address space pointer",
			    c_addr_space_name (as_مقصد),
			    c_addr_space_name (as_from));
	    }

	  /* Warn of new allocations that are not big enough for the target
	     type.  */
	  إذا (warn_alloc_اندازه && درخت_کد (مقدار) == CALL_عبارت)
	    إذا (درخت fndecl = get_callee_fndecl (مقدار))
	      إذا (DECL_IS_MALLOC (fndecl))
		{
		  درخت attrs = TYPE_صفات (درخت_TYPE (fndecl));
		  درخت alloc_اندازه = lookup_attribute ("alloc_size", attrs);
		  إذا (alloc_اندازه)
		    warn_for_alloc_اندازه (loc, درخت_TYPE (type), مقدار,
					 alloc_اندازه);
		}
	}

      /* Warn about possible alignment problems.  */
      إذا ((STRICT_ALIGNMENT || warn_cast_align == 2)
	  && درخت_کد (type) == اشاره_گر_TYPE
	  && درخت_کد (otype) == اشاره_گر_TYPE
	  && درخت_کد (درخت_TYPE (otype)) != VOID_TYPE
	  && درخت_کد (درخت_TYPE (otype)) != FUNCTION_TYPE
	  /* Don't warn about opaque types, where the actual alignment
	     restriction is unknown.  */
	  && !(رکورد_OR_UNION_TYPE_P (درخت_TYPE (otype))
	       && TYPE_نما (درخت_TYPE (otype)) == VOIDmode)
	  && min_align_از_type (درخت_TYPE (type))
	     > min_align_از_type (درخت_TYPE (otype)))
	warning_at (loc, OPT_Wcast_align,
		    "cast increases required alignment of target type");

      إذا ((درخت_کد (type) == INTEGER_TYPE
	   || درخت_کد (type) == BITINT_TYPE)
	  && درخت_کد (otype) == اشاره_گر_TYPE
	  && TYPE_PRECISION (type) != TYPE_PRECISION (otype))
      /* Unlike conversion of integers to pointers, where the
         warning is disabled for converting constants because
         of cases such as SIG_*, warn about converting constant
         pointers to integers. In some cases it may cause unwanted
         sign extension, and a warning is appropriate.  */
	warning_at (loc, OPT_Wpointer_مقصد_int_cast,
		    "cast from pointer to integer of different size");

      إذا ((درخت_کد (مقدار) == CALL_عبارت
	   && !is_access_with_اندازه_p (مقدار))
	  && درخت_کد (type) != درخت_کد (otype))
	warning_at (loc, OPT_Wbad_function_cast,
		    "cast from function call of type %qT "
		    "to non-matching type %qT", otype, type);

      إذا (درخت_کد (type) == اشاره_گر_TYPE
	  && (درخت_کد (otype) == INTEGER_TYPE
	      || درخت_کد (otype) == BITINT_TYPE)
	  && TYPE_PRECISION (type) != TYPE_PRECISION (otype)
	  /* Don't warn about converting any constant.  */
	  && !درخت_CONSTANT (مقدار))
	warning_at (loc,
		    OPT_Wint_مقصد_اشاره_گر_cast, "cast to pointer from integer "
		    "of different size");

      إذا (warn_strict_aliasing <= 2)
        strict_aliasing_warning (عبارت_LOCATION (مقدار), type, عبارت);

      /* If pedantic, warn for conversions between function and object
	 pointer types, except for converting a null pointer constant
	 to function pointer type.  */
      إذا (pedantic
	  && درخت_کد (type) == اشاره_گر_TYPE
	  && درخت_کد (otype) == اشاره_گر_TYPE
	  && درخت_کد (درخت_TYPE (otype)) == FUNCTION_TYPE
	  && درخت_کد (درخت_TYPE (type)) != FUNCTION_TYPE)
	pedwarn (loc, OPT_Wpedantic, "ISO C forbids "
		 "conversion of function pointer to object pointer type");

      إذا (pedantic
	  && درخت_کد (type) == اشاره_گر_TYPE
	  && درخت_کد (otype) == اشاره_گر_TYPE
	  && درخت_کد (درخت_TYPE (type)) == FUNCTION_TYPE
	  && درخت_کد (درخت_TYPE (otype)) != FUNCTION_TYPE
	  && !null_اشاره_گر_constant_p (مقدار))
	pedwarn (loc, OPT_Wpedantic, "ISO C forbids "
		 "conversion of object pointer to function pointer type");

      إذا (درخت_کد (type) == اشاره_گر_TYPE
	  && درخت_کد (otype) == اشاره_گر_TYPE
	  && درخت_کد (درخت_TYPE (type)) == FUNCTION_TYPE
	  && درخت_کد (درخت_TYPE (otype)) == FUNCTION_TYPE
	  && !c_امن_function_type_cast_p (درخت_TYPE (type),
					   درخت_TYPE (otype)))
	warning_at (loc, OPT_Wcast_function_type,
		    "cast between incompatible function types"
		    " from %qT to %qT", otype, type);

      ovalue = مقدار;
      /* If converting to boolean a value with integer operands that
	 is not itself represented as an INTEGER_CST, the call below
	 to note_integer_operands may insert a C_MAYBE_CONST_EXPR, but
	 build_binary_op as called by c_common_truthvalue_conversion
	 may also insert a C_MAYBE_CONST_EXPR to indicate that a
	 subexpression has been fully folded.  To avoid nested
	 C_MAYBE_CONST_EXPR, ensure that
	 c_objc_common_truthvalue_conversion receives an argument
	 properly marked as having integer operands in that case.  */
      إذا (int_operands
	  && درخت_کد (مقدار) != INTEGER_CST
	  && (درخت_کد (type) == BOOLEAN_TYPE
	      || (درخت_کد (type) == ENUMERAL_TYPE
		  && ENUM_UNDERLYING_TYPE (type) != NULL_درخت
		  && درخت_کد (ENUM_UNDERLYING_TYPE (type)) == BOOLEAN_TYPE)))
	مقدار = note_integer_operands (مقدار);
      مقدار = convert (type, مقدار);

      /* Ignore any integer overflow caused by the cast.  */
      إذا (درخت_کد (مقدار) == INTEGER_CST && !FLOAT_TYPE_P (otype))
	{
	  إذا (درخت_سرریز_P (ovalue))
	    {
	      إذا (!درخت_سرریز (مقدار))
		{
		  /* Avoid clobbering a shared constant.  */
		  مقدار = copy_گره (مقدار);
		  درخت_سرریز (مقدار) = درخت_سرریز (ovalue);
		}
	    }
	  وإلا إذا (درخت_سرریز (مقدار))
	    /* Reset VALUE's overflow flags, ensuring constant sharing.  */
	    مقدار = wide_int_مقصد_درخت (درخت_TYPE (مقدار), wi::مقصد_wide (مقدار));
	}
    }

  /* Don't let a cast be an lvalue.  */
  إذا (lvalue_p (مقدار)
      /* Also, don't let a cast be a bit-field of a bit-precise integer type,
	 otherwise it could be incorrectly subject of integer promotions.  */
      || (درخت_کد (مقدار) == COMPONENT_REF
	  && DECL_C_بیت_فیلد (درخت_عملوند (مقدار, 1))
	  && BITINT_TYPE_P (DECL_بیت_فیلد_TYPE (درخت_عملوند (مقدار, 1)))))
    مقدار = non_lvalue_loc (loc, مقدار);

  /* Don't allow the results of casting to floating-point or complex
     types be confused with actual constants, or casts involving
     integer and pointer types other than direct integer-to-integer
     and integer-to-pointer be confused with integer constant
     expressions and null pointer constants.  */
  إذا (درخت_کد (مقدار) == REAL_CST
      || درخت_کد (مقدار) == COMPLEX_CST
      || (درخت_کد (مقدار) == INTEGER_CST
	  && !((درخت_کد (عبارت) == INTEGER_CST
		&& INTEGRAL_TYPE_P (درخت_TYPE (عبارت)))
	       || درخت_کد (عبارت) == REAL_CST
	       || درخت_کد (عبارت) == COMPLEX_CST)))
      مقدار = build1 (NOP_عبارت, type, مقدار);

  /* If the expression has integer operands and so can occur in an
     unevaluated part of an integer constant expression, ensure the
     return value reflects this.  */
  إذا (int_operands
      && INTEGRAL_TYPE_P (type)
      && مقدار != error_mark_گره
      && !عبارت_INT_CONST_OPERANDS (مقدار))
    مقدار = note_integer_operands (مقدار);

  protected_مجموعه_عبارت_location (مقدار, loc);
  أرجع مقدار;
}

/* Interpret a cast of expression EXPR to type TYPE.  LOC is the
   location of the open paren of the cast, or the position of the cast
   expr.  */
درخت
c_cast_عبارت (location_t loc, بنية c_type_name *type_name, درخت عبارت)
{
  درخت type;
  درخت type_عبارت = NULL_درخت;
  منطقي type_عبارت_const = درست;
  درخت ret;
  صحيح saved_wsp = warn_strict_prototypes;

  /* This avoids warnings about unprototyped casts on
     integers.  E.g. "#define SIG_DFL (void(*)())0".  */
  إذا (درخت_کد (عبارت) == INTEGER_CST)
    warn_strict_prototypes = 0;
  type = groktypename (type_name, &type_عبارت, &type_عبارت_const);
  warn_strict_prototypes = saved_wsp;

  إذا (درخت_کد (عبارت) == ADDR_عبارت && !VOID_TYPE_P (type)
      && reject_gcc_builtin (عبارت))
    أرجع error_mark_گره;

  ret = build_c_cast (loc, type, عبارت);
  إذا (ret == error_mark_گره)
    أرجع error_mark_گره;

  إذا (type_عبارت)
    {
      منطقي inner_عبارت_const = درست;
      ret = c_fully_fold (ret, require_constant_مقدار, &inner_عبارت_const);
      ret = build2 (C_MAYBE_CONST_عبارت, درخت_TYPE (ret), type_عبارت, ret);
      C_MAYBE_CONST_عبارت_NON_CONST (ret) = !(type_عبارت_const
					     && inner_عبارت_const);
      مجموعه_عبارت_LOCATION (ret, loc);
    }

  إذا (!عبارت_HAS_LOCATION (ret))
    protected_مجموعه_عبارت_location (ret, loc);

  /* C++ does not permits types to be defined in a cast, but it
     allows references to incomplete types.  */
  إذا (warn_cxx_compat && type_name->specs->typespec_نوع == ctsk_tagdef)
    warning_at (loc, OPT_Wc___compat,
		"defining a type in a cast is invalid in C++");

  أرجع ret;
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
build_modify_عبارت (location_t location, درخت lhs, درخت lhs_origtype,
		   تعداد درخت_کد_2 modifycode,
		   location_t rhs_loc, درخت rhs, درخت rhs_origtype)
{
  درخت نتیجه;
  درخت newrhs;
  درخت rhseval = NULL_درخت;
  درخت lhstype = درخت_TYPE (lhs);
  درخت olhstype = lhstype;
  منطقي npc;
  منطقي is_atomic_op;

  /* Types that aren't fully specified cannot be used in assignments.  */
  lhs = require_complete_type (location, lhs);
  rhs = require_complete_type (location, rhs);

  /* Avoid duplicate error messages from operands that had errors.  */
  إذا (درخت_کد (lhs) == ERROR_MARK || درخت_کد (rhs) == ERROR_MARK)
    أرجع error_mark_گره;

  /* Ensure an error for assigning a non-lvalue array to an array in
     C90.  */
  إذا (درخت_کد (lhstype) == ARRAY_TYPE)
    {
      error_at (location, "assignment to expression with array type");
      أرجع error_mark_گره;
    }

  /* For ObjC properties, defer this check.  */
  إذا (!objc_is_property_ref (lhs) && !lvalue_or_else (location, lhs, lv_تخصیص_بده))
    أرجع error_mark_گره;

  is_atomic_op = really_atomic_lvalue (lhs);

  newrhs = rhs;

  إذا (درخت_کد (lhs) == C_MAYBE_CONST_عبارت)
    {
      درخت inner = build_modify_عبارت (location, C_MAYBE_CONST_عبارت_عبارت (lhs),
				      lhs_origtype, modifycode, rhs_loc, rhs,
				      rhs_origtype);
      إذا (inner == error_mark_گره)
	أرجع error_mark_گره;
      نتیجه = build2 (C_MAYBE_CONST_عبارت, درخت_TYPE (inner),
		       C_MAYBE_CONST_عبارت_PRE (lhs), inner);
      gcc_assert (!C_MAYBE_CONST_عبارت_INT_OPERANDS (lhs));
      C_MAYBE_CONST_عبارت_NON_CONST (نتیجه) = 1;
      protected_مجموعه_عبارت_location (نتیجه, location);
      أرجع نتیجه;
    }

  /* If a binary op has been requested, combine the old LHS value with the RHS
     producing the value we should actually store into the LHS.  */

  إذا (modifycode != NOP_عبارت)
    {
      lhs = c_fully_fold (lhs, خطأ, عدم, درست);
      lhs = stabilize_reference (lhs);

      /* Construct the RHS for any non-atomic compound assignment. */
      إذا (!is_atomic_op)
        {
	  /* If in LHS op= RHS the RHS has side-effects, ensure they
	     are preevaluated before the rest of the assignment expression's
	     side-effects, because RHS could contain e.g. function calls
	     that modify LHS.  */
	  إذا (درخت_SIDE_EFFECTS (rhs))
	    {
	      إذا (درخت_کد (rhs) == EXCESS_PRECISION_عبارت)
		newrhs = save_عبارت (درخت_عملوند (rhs, 0));
	      وإلا
		newrhs = save_عبارت (rhs);
	      rhseval = newrhs;
	      إذا (درخت_کد (rhs) == EXCESS_PRECISION_عبارت)
		newrhs = build1 (EXCESS_PRECISION_عبارت, درخت_TYPE (rhs),
				 newrhs);
	    }
	  منطقي clear_decl_read = خطأ;
	  إذا ((VAR_P (lhs) || درخت_کد (lhs) == PARM_DECL)
	      && !DECL_READ_P (lhs)
	      && (VAR_P (lhs) ? warn_استفادهنشده_but_مجموعه_variable
			      : warn_استفادهنشده_but_مجموعه_parameter) > 2)
	    {
	      mark_exp_read (newrhs);
	      إذا (!DECL_READ_P (lhs))
		clear_decl_read = درست;
	    }

	  newrhs = build_دودویی_op (location, modifycode,
				    convert_lvalue_مقصد_rvalue (location, lhs,
							      درست, درست),
				    newrhs, درست);
	  إذا (clear_decl_read)
	    DECL_READ_P (lhs) = 0;

	  /* The original type of the right hand side is no longer
	     meaningful.  */
	  rhs_origtype = NULL_درخت;
	}
    }

  إذا (c_dialect_objc ())
    {
      /* Check if we are modifying an Objective-C property reference;
	 if so, we need to generate setter calls.  */
      إذا (درخت_کد (newrhs) == EXCESS_PRECISION_عبارت)
	نتیجه = objc_maybe_build_modify_عبارت (lhs, درخت_عملوند (newrhs, 0));
      وإلا
	نتیجه = objc_maybe_build_modify_عبارت (lhs, newrhs);
      إذا (نتیجه)
	اذهب return_نتیجه;

      /* Else, do the check that we postponed for Objective-C.  */
      إذا (!lvalue_or_else (location, lhs, lv_تخصیص_بده))
	أرجع error_mark_گره;
    }

  /* Give an error for storing in something that is 'const'.  */

  إذا (TYPE_READONLY (lhstype)
      || (رکورد_OR_UNION_TYPE_P (lhstype)
	  && C_TYPE_FIELDS_READONLY (lhstype)))
    {
      readonly_error (location, lhs, lv_تخصیص_بده);
      أرجع error_mark_گره;
    }
  وإلا إذا (درخت_READONLY (lhs))
    readonly_warning (lhs, lv_تخصیص_بده);

  /* If storing into a structure or union member,
     it has probably been given type `int'.
     Compute the type that would go with
     the actual amount of storage the member occupies.  */

  إذا (درخت_کد (lhs) == COMPONENT_REF
      && (درخت_کد (lhstype) == INTEGER_TYPE
	  || درخت_کد (lhstype) == BOOLEAN_TYPE
	  || SCALAR_FLOAT_TYPE_P (lhstype)
	  || درخت_کد (lhstype) == ENUMERAL_TYPE))
    lhstype = درخت_TYPE (get_unwidened (lhs, 0));

  /* If storing in a field that is in actuality a short or narrower than one,
     we must store in the field in its actual type.  */

  إذا (lhstype != درخت_TYPE (lhs))
    {
      lhs = copy_گره (lhs);
      درخت_TYPE (lhs) = lhstype;
    }

  /* Issue -Wc++-compat warnings about an assignment to an enum type
     when LHS does not have its original type.  This happens for,
     e.g., an enum bitfield in a struct.  */
  إذا (warn_cxx_compat
      && lhs_origtype != NULL_درخت
      && lhs_origtype != lhstype
      && درخت_کد (lhs_origtype) == ENUMERAL_TYPE)
    {
      درخت checktype = (rhs_origtype != NULL_درخت
			? rhs_origtype
			: درخت_TYPE (rhs));
      إذا (checktype != error_mark_گره
	  && (TYPE_MAIN_VARIANT (checktype) != TYPE_MAIN_VARIANT (lhs_origtype)
	      || (is_atomic_op && modifycode != NOP_عبارت)))
	warning_at (location, OPT_Wc___compat,
		    "enum conversion in assignment is invalid in C++");
    }

  /* Remove qualifiers.  */
  lhstype = c_build_qualified_type (lhstype, TYPE_UNQUALIFIED);
  olhstype = c_build_qualified_type (olhstype, TYPE_UNQUALIFIED);

  /* Convert new value to destination type.  Fold it first, then
     restore any excess precision information, for the sake of
     conversion warnings.  */

  إذا (!(is_atomic_op && modifycode != NOP_عبارت))
    {
      درخت rhs_semantic_type = NULL_درخت;
      إذا (!c_درون_omp_for)
	{
	  إذا (درخت_کد (newrhs) == EXCESS_PRECISION_عبارت)
	    {
	      rhs_semantic_type = درخت_TYPE (newrhs);
	      newrhs = درخت_عملوند (newrhs, 0);
	    }
	  npc = null_اشاره_گر_constant_p (newrhs);
	  newrhs = c_fully_fold (newrhs, خطأ, عدم);
	  إذا (rhs_semantic_type)
	    newrhs = build1 (EXCESS_PRECISION_عبارت, rhs_semantic_type, newrhs);
	}
      وإلا
	npc = null_اشاره_گر_constant_p (newrhs);
      newrhs = convert_for_assignment (location, rhs_loc, lhstype, newrhs,
				       rhs_origtype, ic_تخصیص_بده, npc,
				       NULL_درخت, NULL_درخت, 0);
      إذا (درخت_کد (newrhs) == ERROR_MARK)
	أرجع error_mark_گره;
    }

  /* Emit ObjC write barrier, if necessary.  */
  إذا (c_dialect_objc () && flag_objc_gc)
    {
      نتیجه = objc_generate_write_barrier (lhs, modifycode, newrhs);
      إذا (نتیجه)
	{
	  protected_مجموعه_عبارت_location (نتیجه, location);
	  اذهب return_نتیجه;
	}
    }

  /* Scan operands.  */

  إذا (is_atomic_op)
    نتیجه = build_atomic_تخصیص_بده (location, lhs, modifycode, newrhs, خطأ);
  وإلا
    {
      نتیجه = build2 (MODIFY_عبارت, lhstype, lhs, newrhs);
      درخت_SIDE_EFFECTS (نتیجه) = 1;
      protected_مجموعه_عبارت_location (نتیجه, location);
    }

  /* If we got the LHS in a different type for storing in,
     convert the result back to the nominal type of LHS
     so that the value we return always has the same type
     as the LHS argument.  */

  إذا (olhstype == درخت_TYPE (نتیجه))
    اذهب return_نتیجه;

  نتیجه = convert_for_assignment (location, rhs_loc, olhstype, نتیجه,
				   rhs_origtype, ic_تخصیص_بده, خطأ, NULL_درخت,
				   NULL_درخت, 0);
  protected_مجموعه_عبارت_location (نتیجه, location);

return_نتیجه:
  إذا (rhseval)
    نتیجه = build2 (COMPOUND_عبارت, درخت_TYPE (نتیجه), rhseval, نتیجه);
  أرجع نتیجه;
}

/* Return whether STRUCT_TYPE has an anonymous field with type TYPE.
   This is used to implement -fplan9-extensions.  */

ساكن منطقي
پیدا_کن_anonymous_فیلد_with_type (درخت struct_type, درخت type)
{
  درخت فیلد_2;
  منطقي یافت;

  gcc_assert (رکورد_OR_UNION_TYPE_P (struct_type));
  یافت = خطأ;
  لكل (فیلد_2 = TYPE_FIELDS (struct_type);
       فیلد_2 != NULL_درخت;
       فیلد_2 = درخت_CHAIN (فیلد_2))
    {
      درخت fieldtype = remove_qualifiers (درخت_TYPE (فیلد_2));
      إذا (DECL_NAME (فیلد_2) == عدم
	  && comptypes (type, fieldtype))
	{
	  إذا (یافت)
	    أرجع خطأ;
	  یافت = درست;
	}
      وإلا إذا (DECL_NAME (فیلد_2) == عدم
	       && رکورد_OR_UNION_TYPE_P (درخت_TYPE (فیلد_2))
	       && پیدا_کن_anonymous_فیلد_with_type (درخت_TYPE (فیلد_2), type))
	{
	  إذا (یافت)
	    أرجع خطأ;
	  یافت = درست;
	}
    }
  أرجع یافت;
}

/* RHS is an expression whose type is pointer to struct.  If there is
   an anonymous field in RHS with type TYPE, then return a pointer to
   that field in RHS.  This is used with -fplan9-extensions.  This
   returns NULL if no conversion could be found.  */

ساكن درخت
convert_مقصد_anonymous_فیلد (location_t location, درخت type, درخت rhs)
{
  درخت rhs_struct_type, lhs_main_type;
  درخت فیلد_2, یافت_فیلد;
  منطقي یافت_sub_فیلد;
  درخت ret;

  gcc_assert (اشاره_گر_TYPE_P (درخت_TYPE (rhs)));
  rhs_struct_type = درخت_TYPE (درخت_TYPE (rhs));
  gcc_assert (رکورد_OR_UNION_TYPE_P (rhs_struct_type));

  gcc_assert (اشاره_گر_TYPE_P (type));
  lhs_main_type = remove_qualifiers (درخت_TYPE (type));

  یافت_فیلد = NULL_درخت;
  یافت_sub_فیلد = خطأ;
  لكل (فیلد_2 = TYPE_FIELDS (rhs_struct_type);
       فیلد_2 != NULL_درخت;
       فیلد_2 = درخت_CHAIN (فیلد_2))
    {
      إذا (DECL_NAME (فیلد_2) != NULL_درخت
	  || !رکورد_OR_UNION_TYPE_P (درخت_TYPE (فیلد_2)))
	استمر;
      درخت fieldtype = remove_qualifiers (درخت_TYPE (فیلد_2));
      إذا (comptypes (lhs_main_type, fieldtype))
	{
	  إذا (یافت_فیلد != NULL_درخت)
	    أرجع NULL_درخت;
	  یافت_فیلد = فیلد_2;
	}
      وإلا إذا (پیدا_کن_anonymous_فیلد_with_type (درخت_TYPE (فیلد_2),
					       lhs_main_type))
	{
	  إذا (یافت_فیلد != NULL_درخت)
	    أرجع NULL_درخت;
	  یافت_فیلد = فیلد_2;
	  یافت_sub_فیلد = درست;
	}
    }

  إذا (یافت_فیلد == NULL_درخت)
    أرجع NULL_درخت;

  ret = fold_build3_loc (location, COMPONENT_REF, درخت_TYPE (یافت_فیلد),
			 build_fold_غیرمستقیم_ref (rhs), یافت_فیلد,
			 NULL_درخت);
  ret = build_fold_addr_عبارت_loc (location, ret);

  إذا (یافت_sub_فیلد)
    {
      ret = convert_مقصد_anonymous_فیلد (location, type, ret);
      gcc_assert (ret != NULL_درخت);
    }

  أرجع ret;
}

/* Issue an error message for a bad initializer component.
   GMSGID identifies the message.
   The component name is taken from the spelling stack.  */

ساكن فراغ ATTRIBUTE_GCC_DIAG (2,0)
error_init (location_t loc, ثابت حرف *gmsgid, ...)
{
  حرف *ofwhat;

  auto_diagnostic_گروه d;

  /* The gmsgid may be a format string with %< and %>. */
  va_list ap;
  va_شروع (ap, gmsgid);
  منطقي warned = emit_diagnostic_valist (diagnostics::نوع::error,
					loc, -1, gmsgid, &ap);
  va_انتها (ap);

  ofwhat = print_spelling ((حرف *) alloca (spelling_درازی () + 1));
  إذا (*ofwhat && warned)
    inform (loc, "(near initialization for %qs)", ofwhat);
}

/* Used to implement pedwarn_init and permerror_init.  */

ساكن منطقي ATTRIBUTE_GCC_DIAG (3,0)
pedwarn_permerror_init (location_t loc, صحيح opt, ثابت حرف *gmsgid,
			va_list *ap, تعداد diagnostics::نوع نوع)
{
  /* Use the location where a macro was expanded rather than where
     it was defined to make sure macros defined in system headers
     but used incorrectly elsewhere are diagnosed.  */
  location_t exploc = expansion_نقطه_location_if_درون_system_سرآیند (loc);
  auto_diagnostic_گروه d;
  منطقي warned = emit_diagnostic_valist (نوع, exploc, opt, gmsgid, ap);
  إذا (warned)
    {
      حرف *ofwhat = print_spelling ((حرف *) alloca (spelling_درازی () + 1));
      إذا (*ofwhat)
	inform (exploc, "(near initialization for %qs)", ofwhat);
    }
  أرجع warned;
}

/* Issue a pedantic warning for a bad initializer component.  OPT is
   the option OPT_* (from options.h) controlling this warning or 0 if
   it is unconditionally given.  GMSGID identifies the message.  The
   component name is taken from the spelling stack.  */

ساكن منطقي ATTRIBUTE_GCC_DIAG (3,0)
pedwarn_init (location_t loc, صحيح opt, ثابت حرف *gmsgid, ...)
{
  va_list ap;
  va_شروع (ap, gmsgid);
  منطقي warned = pedwarn_permerror_init (loc, opt, gmsgid, &ap,
					diagnostics::نوع::pedwarn);
  va_انتها (ap);
  أرجع warned;
}

/* Like pedwarn_init, but issue a permerror.  */

ساكن منطقي ATTRIBUTE_GCC_DIAG (3,0)
permerror_init (location_t loc, صحيح opt, ثابت حرف *gmsgid, ...)
{
  va_list ap;
  va_شروع (ap, gmsgid);
  منطقي warned = pedwarn_permerror_init (loc, opt, gmsgid, &ap,
					diagnostics::نوع::permerror);
  va_انتها (ap);
  أرجع warned;
}

/* Issue a warning for a bad initializer component.

   OPT is the OPT_W* value corresponding to the warning option that
   controls this warning.  GMSGID identifies the message.  The
   component name is taken from the spelling stack.  */

ساكن فراغ
warning_init (location_t loc, صحيح opt, ثابت حرف *gmsgid)
{
  حرف *ofwhat;
  منطقي warned;

  auto_diagnostic_گروه d;

  /* Use the location where a macro was expanded rather than where
     it was defined to make sure macros defined in system headers
     but used incorrectly elsewhere are diagnosed.  */
  location_t exploc = expansion_نقطه_location_if_درون_system_سرآیند (loc);

  /* The gmsgid may be a format string with %< and %>. */
  warned = warning_at (exploc, opt, gmsgid);
  إذا (warned)
    {
      ofwhat = print_spelling ((حرف *) alloca (spelling_درازی () + 1));
      إذا (*ofwhat)
	inform (exploc, "(near initialization for %qs)", ofwhat);
    }
}

/* If TYPE is an array type and EXPR is a parenthesized string
   constant, warn if pedantic that EXPR is being used to initialize an
   object of type TYPE.  */

فراغ
maybe_warn_string_init (location_t loc, درخت type, بنية c_عبارت عبارت)
{
  إذا (pedantic
      && درخت_کد (type) == ARRAY_TYPE
      && درخت_کد (عبارت.مقدار) == STRING_CST
      && عبارت.original_کد != STRING_CST)
    pedwarn_init (loc, OPT_Wpedantic,
		  "array initialized from parenthesized string constant");
}

/* Attempt to locate the parameter with the given index within FNDECL,
   returning DECL_SOURCE_LOCATION (FNDECL) if it can't be found.  */

ساكن location_t
get_fndecl_آرگومان_location (درخت fndecl, صحيح argnum)
{
  صحيح i;
  درخت param;

  /* Locate param by index within DECL_ARGUMENTS (fndecl).  */
  لكل (i = 0, param = DECL_ARGUMENTS (fndecl);
       i < argnum && param;
       i++, param = درخت_CHAIN (param))
    ;

  /* If something went wrong (e.g. if we have a builtin and thus no arguments),
     return DECL_SOURCE_LOCATION (FNDECL).  */
  إذا (param == عدم)
    أرجع DECL_منبع_LOCATION (fndecl);

  أرجع DECL_منبع_LOCATION (param);
}

/* Issue a note about a mismatching argument for parameter PARMNUM
   to FUNDECL, for types EXPECTED_TYPE and ACTUAL_TYPE.
   Attempt to issue the note at the pertinent parameter of the decl;
   failing that issue it at the location of FUNDECL; failing that
   issue it at PLOC.
   Use highlight_colors::actual for the ACTUAL_TYPE
   and highlight_colors::expected for EXPECTED_TYPE and the
   parameter of FUNDECL*/

ساكن فراغ
inform_for_arg (درخت fundecl, location_t ploc, صحيح parmnum,
		درخت expected_type, درخت actual_type)
{
  location_t loc;
  إذا (fundecl && !DECL_IS_UNDECLARED_BUILTIN (fundecl))
    loc = get_fndecl_آرگومان_location (fundecl, parmnum - 1);
  وإلا
    loc = ploc;

  gcc_rich_location richloc (loc, اشاره_تهی, highlight_colors::expected);

  pp_markup::element_expected_type elem_expected_type (expected_type);
  pp_markup::element_actual_type elem_actual_type (actual_type);
  inform (&richloc,
	  "expected %e but argument is of type %e",
	  &elem_expected_type, &elem_actual_type);
}

/* Issue a warning when an argument of ARGTYPE is passed to a built-in
   function FUNDECL declared without prototype to parameter PARMNUM of
   PARMTYPE when ARGTYPE does not promote to PARMTYPE.  */

ساكن فراغ
maybe_warn_builtin_no_proto_arg (location_t loc, درخت fundecl, صحيح parmnum,
				 درخت parmtype, درخت argtype)
{
  درخت_کد_2 parmcode = درخت_کد (parmtype);
  درخت_کد_2 argcode = درخت_کد (argtype);
  درخت promoted = c_type_promotes_مقصد (argtype);

  /* Avoid warning for enum arguments that promote to an integer type
     of the same size/mode.  */
  إذا (parmcode == INTEGER_TYPE
      && argcode == ENUMERAL_TYPE
      && TYPE_نما (parmtype) == TYPE_نما (argtype))
    أرجع;

  إذا ((parmcode == argcode
       || (parmcode == INTEGER_TYPE
	   && argcode == ENUMERAL_TYPE))
      && TYPE_MAIN_VARIANT (parmtype) == TYPE_MAIN_VARIANT (promoted))
    أرجع;

  /* This diagnoses even signed/unsigned mismatches.  Those might be
     safe in many cases but GCC may emit suboptimal code for them so
     warning on those cases drives efficiency improvements.  */
  إذا (warning_at (loc, OPT_Wbuiltin_declaration_mismatch,
		  TYPE_MAIN_VARIANT (promoted) == argtype
		  ? G_("%qD argument %d type is %qT where %qT is expected "
		       "in a call to built-in function declared without "
		       "prototype")
		  : G_("%qD argument %d promotes to %qT where %qT is expected "
		       "in a call to built-in function declared without "
		       "prototype"),
		  fundecl, parmnum, promoted, parmtype))
    inform (DECL_منبع_LOCATION (fundecl),
	    "built-in %qD declared here",
	    fundecl);
}

/* Print a declaration in quotes, with the given highlight_color.
   Analogous to handler for %qD, but with a specific highlight color.  */

صنف pp_element_quoted_decl : عام pp_element
{
عام:
  pp_element_quoted_decl (درخت decl, ثابت حرف *highlight_color)
  : m_decl (decl),
    m_highlight_color (highlight_color)
  {
  }

  فراغ جمع_کن_مقصد_phase_2 (pp_markup::context &ctxt) override
  {
    ctxt.begin_quote ();
    ctxt.begin_highlight_color (m_highlight_color);

    print_decl (ctxt);

    ctxt.انتها_highlight_color ();
    ctxt.انتها_quote ();
  }

  فراغ print_decl (pp_markup::context &ctxt)
  {
    pretty_printer *ثابت pp = &ctxt.m_pp;
    pp->مجموعه_padding (pp_none);
    إذا (DECL_NAME (m_decl))
      pp_identifier (pp, lang_hooks.decl_printable_name (m_decl, 2));
    وإلا
      pp_string (pp, _("({anonymous})"));
  }

خاص:
  درخت m_decl;
  ثابت حرف *m_highlight_color;
};

/* If TYPE is from a typedef, issue a note showing the location
   to the user.
   Use HIGHLIGHT_COLOR as the highlight color.  */

ساكن فراغ
maybe_inform_typedef_location (درخت type, ثابت حرف *highlight_color)
{
  إذا (!typedef_variant_p (type))
    أرجع;

  درخت typedef_decl = TYPE_NAME (type);
  gcc_assert (درخت_کد (typedef_decl) == TYPE_DECL);
  gcc_rich_location richloc (DECL_منبع_LOCATION (typedef_decl),
			     اشاره_تهی, highlight_color);
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

ساكن درخت
convert_for_assignment (location_t location, location_t عبارت_loc, درخت type,
			درخت rhs, درخت origtype, تعداد impl_conv errtype,
			منطقي null_اشاره_گر_constant, درخت fundecl,
			درخت function, صحيح parmnum, صحيح warnopt /* = 0 */)
{
  تعداد درخت_کد_2 codel = درخت_کد (type);
  درخت orig_rhs = rhs;
  درخت rhstype;
  تعداد درخت_کد_2 coder;
  درخت rname = NULL_درخت;
  منطقي objc_ok = خطأ;

  /* Use the expansion point location to handle cases such as user's
     function returning a wrong-type macro defined in a system header.  */
  location = expansion_نقطه_location_if_درون_system_سرآیند (location);

  إذا (errtype == ic_argpass)
    {
      درخت selector;
      /* Change pointer to function to the function itself for
	 diagnostics.  */
      إذا (درخت_کد (function) == ADDR_عبارت
	  && درخت_کد (درخت_عملوند (function, 0)) == FUNCTION_DECL)
	function = درخت_عملوند (function, 0);

      /* Handle an ObjC selector specially for diagnostics.  */
      selector = objc_پیام_selector ();
      rname = function;
      إذا (selector && parmnum > 2)
	{
	  rname = selector;
	  parmnum -= 2;
	}
    }

  /* This macro is used to emit diagnostics to ensure that all format
     strings are complete sentences, visible to gettext and checked at
     compile time.  */
#تعریف_کن PEDWARN_FOR_ASSIGNMENT(LOCATION, PLOC, OPT, AR, AS, درون, RE)	 \
  افعل {                                                                   \
    بدل (errtype)                                                     \
      {                                                                  \
      حالة ic_argpass:                                                   \
	{								\
	  auto_diagnostic_گروه d;						\
	  إذا (pedwarn (PLOC, OPT, AR, parmnum, rname))		\
	    inform_for_arg (fundecl, (PLOC), parmnum, type, rhstype); \
	}								\
        اكسر;                                                           \
      حالة ic_تخصیص_بده:                                                    \
        pedwarn (LOCATION, OPT, AS);                                     \
        اكسر;                                                           \
      حالة ic_init:                                                      \
      حالة ic_init_const:                                                \
        pedwarn_init (LOCATION, OPT, درون);                                \
        اكسر;                                                           \
      حالة ic_return:                                                    \
        pedwarn (LOCATION, OPT, RE);					 \
        اكسر;                                                           \
      افتراضي:                                                           \
        gcc_unreachable ();                                              \
      }                                                                  \
  } طالما (0)

  /* This macro is used to emit diagnostics to ensure that all format
     strings are complete sentences, visible to gettext and checked at
     compile time.  It can be called with 'pedwarn' or 'warning_at'.  */
#تعریف_کن WARNING_FOR_QUALIFIERS(PEDWARN, LOCATION, PLOC, OPT, AR, AS, درون, RE, QUALS) \
  افعل {                                                                   \
    بدل (errtype)                                                     \
      {                                                                  \
      حالة ic_argpass:                                                   \
	{								 \
	  auto_diagnostic_گروه d;					 \
	  إذا (PEDWARN) {						 \
	    إذا (pedwarn (PLOC, OPT, AR, parmnum, rname, QUALS))          \
	      inform_for_arg (fundecl, (PLOC), parmnum, type, rhstype);  \
	  } وإلا {							 \
	    إذا (warning_at (PLOC, OPT, AR, parmnum, rname, QUALS))	 \
	      inform_for_arg (fundecl, (PLOC), parmnum, type, rhstype);  \
	  }								 \
	}								 \
        اكسر;                                                           \
      حالة ic_تخصیص_بده:                                                    \
	إذا (PEDWARN)							 \
	  pedwarn (LOCATION, OPT, AS, QUALS);                            \
	وإلا								 \
	  warning_at (LOCATION, OPT, AS, QUALS);                         \
        اكسر;                                                           \
      حالة ic_init:                                                      \
      حالة ic_init_const:                                                \
	إذا (PEDWARN)							 \
	  pedwarn (LOCATION, OPT, درون, QUALS);                            \
	وإلا								 \
	  warning_at (LOCATION, OPT, درون, QUALS);                         \
        اكسر;                                                           \
      حالة ic_return:                                                    \
	إذا (PEDWARN)							 \
	  pedwarn (LOCATION, OPT, RE, QUALS);                            \
	وإلا								 \
	  warning_at (LOCATION, OPT, RE, QUALS);                         \
        اكسر;                                                           \
      افتراضي:                                                           \
        gcc_unreachable ();                                              \
      }                                                                  \
  } طالما (0)

  /* This macro is used to emit diagnostics to ensure that all format
     strings are complete sentences, visible to gettext and checked at
     compile time.  It is the same as PEDWARN_FOR_ASSIGNMENT but with an
     extra parameter to enumerate qualifiers.  */
#تعریف_کن PEDWARN_FOR_QUALIFIERS(LOCATION, PLOC, OPT, AR, AS, درون, RE, QUALS) \
   WARNING_FOR_QUALIFIERS (درست, LOCATION, PLOC, OPT, AR, AS, درون, RE, QUALS)


  إذا (درخت_کد (rhs) == EXCESS_PRECISION_عبارت)
    rhs = درخت_عملوند (rhs, 0);

  rhstype = درخت_TYPE (rhs);
  coder = درخت_کد (rhstype);

  إذا (coder == ERROR_MARK)
    أرجع error_mark_گره;

  إذا (c_dialect_objc ())
    {
      صحيح parmno;

      بدل (errtype)
	{
	حالة ic_return:
	  parmno = 0;
	  اكسر;

	حالة ic_تخصیص_بده:
	  parmno = -1;
	  اكسر;

	حالة ic_init:
	حالة ic_init_const:
	  parmno = -2;
	  اكسر;

	افتراضي:
	  parmno = parmnum;
	  اكسر;
	}

      objc_ok = objc_compare_types (type, rhstype, parmno, rname);
    }

  إذا (warn_cxx_compat)
    {
      درخت checktype = origtype != NULL_درخت ? origtype : rhstype;
      إذا (checktype != error_mark_گره
	  && درخت_کد (type) == ENUMERAL_TYPE
	  && TYPE_MAIN_VARIANT (checktype) != TYPE_MAIN_VARIANT (type))
	بدل (errtype)
	  {
	  حالة ic_argpass:
	    إذا (pedwarn (عبارت_loc, OPT_Wc___compat, "enum conversion when "
			 "passing argument %d of %qE is invalid in C++",
			 parmnum, rname))
	      inform ((fundecl && !DECL_IS_UNDECLARED_BUILTIN (fundecl))
		      ? DECL_منبع_LOCATION (fundecl) : عبارت_loc,
		      "expected %qT but argument is of type %qT",
		      type, rhstype);
	    اكسر;
	  حالة ic_تخصیص_بده:
	    pedwarn (location, OPT_Wc___compat, "enum conversion from %qT to "
		     "%qT in assignment is invalid in C++", rhstype, type);
	    اكسر;
	  حالة ic_init:
	  حالة ic_init_const:
	    pedwarn_init (location, OPT_Wc___compat, "enum conversion from "
			  "%qT to %qT in initialization is invalid in C++",
			  rhstype, type);
	    اكسر;
	  حالة ic_return:
	    pedwarn (location, OPT_Wc___compat, "enum conversion from %qT to "
		     "%qT in return is invalid in C++", rhstype, type);
	    اكسر;
	  افتراضي:
	    gcc_unreachable ();
	  }
    }

  إذا (warn_enum_conversion)
    {
      درخت checktype = origtype != NULL_درخت ? origtype : rhstype;
      إذا (checktype != error_mark_گره
	  && درخت_کد (checktype) == ENUMERAL_TYPE
	  && درخت_کد (type) == ENUMERAL_TYPE
	  && !comptypes (TYPE_MAIN_VARIANT (checktype), TYPE_MAIN_VARIANT (type)))
       {
	  gcc_rich_location loc (location);
	  warning_at (&loc, OPT_Wenum_conversion,
		      "implicit conversion from %qT to %qT",
		      checktype, type);
       }
    }

  إذا (TYPE_MAIN_VARIANT (type) == TYPE_MAIN_VARIANT (rhstype))
    {
      warn_for_آدرس_از_packed_member (type, orig_rhs);
      إذا (type != rhstype)
	/* Convert RHS to TYPE in order to not lose TYPE in diagnostics.  */
	rhs = convert (type, rhs);
      أرجع rhs;
    }

  إذا (coder == VOID_TYPE)
    {
      /* Except for passing an argument to an unprototyped function,
	 this is a constraint violation.  When passing an argument to
	 an unprototyped function, it is compile-time undefined;
	 making it a constraint in that case was rejected in
	 DR#252.  */
      ثابت حرف پیام_2[] = "void value not ignored as it ought to be";
      إذا (warnopt)
	warning_at (location, warnopt, پیام_2);
      وإلا
	error_at (location, پیام_2);
      أرجع error_mark_گره;
    }
  rhs = require_complete_type (location, rhs);
  إذا (rhs == error_mark_گره)
    أرجع error_mark_گره;

  إذا (coder == اشاره_گر_TYPE && reject_gcc_builtin (rhs))
    أرجع error_mark_گره;

  /* A non-reference type can convert to a reference.  This handles
     va_start, va_copy and possibly port built-ins.  */
  إذا (codel == REFERENCE_TYPE && coder != REFERENCE_TYPE)
    {
      إذا (!lvalue_p (rhs))
	{
	  ثابت حرف پیام_2[] = "cannot pass rvalue to reference parameter";
	  إذا (warnopt)
	    warning_at (location, warnopt, پیام_2);
	  وإلا
	    error_at (location, پیام_2);
	  أرجع error_mark_گره;
	}
      إذا (!c_mark_addressable (rhs))
	أرجع error_mark_گره;
      rhs = build1 (ADDR_عبارت, c_build_اشاره_گر_type (درخت_TYPE (rhs)), rhs);
      مجموعه_عبارت_LOCATION (rhs, location);

      rhs = convert_for_assignment (location, عبارت_loc,
				    c_build_اشاره_گر_type (درخت_TYPE (type)),
				    rhs, origtype, errtype,
				    null_اشاره_گر_constant, fundecl, function,
				    parmnum, warnopt);
      إذا (rhs == error_mark_گره)
	أرجع error_mark_گره;

      rhs = build1 (NOP_عبارت, type, rhs);
      مجموعه_عبارت_LOCATION (rhs, location);
      أرجع rhs;
    }
  /* Some types can interconvert without explicit casts.  */
  وإلا إذا (codel == وکتور_TYPE && coder == وکتور_TYPE
	   && وکتور_types_convertible_p (type, درخت_TYPE (rhs), درست))
    أرجع convert (type, rhs);
  /* Arithmetic types all interconvert, and enum is treated like int.  */
  وإلا إذا ((codel == INTEGER_TYPE || codel == REAL_TYPE
	    || codel == FIXED_نقطه_TYPE
	    || codel == ENUMERAL_TYPE || codel == COMPLEX_TYPE
	    || codel == BOOLEAN_TYPE || codel == BITINT_TYPE)
	   && (coder == INTEGER_TYPE || coder == REAL_TYPE
	       || coder == FIXED_نقطه_TYPE
	       || coder == ENUMERAL_TYPE || coder == COMPLEX_TYPE
	       || coder == BOOLEAN_TYPE || coder == BITINT_TYPE))
    {
      إذا (warnopt && errtype == ic_argpass)
	maybe_warn_builtin_no_proto_arg (عبارت_loc, fundecl, parmnum, type,
					 rhstype);

      منطقي save = درون_late_دودویی_op;
      إذا (C_BOOLEAN_TYPE_P (type) || codel == COMPLEX_TYPE
	  || (coder == REAL_TYPE
	      && (codel == INTEGER_TYPE || codel == ENUMERAL_TYPE)
	      && sanitize_flags_p (SANITIZE_FLOAT_CAST)))
	درون_late_دودویی_op = درست;
      درخت ret = convert_and_check (عبارت_loc != UNKNOWN_LOCATION
				    ? عبارت_loc : location, type, orig_rhs,
				    errtype == ic_init_const);
      درون_late_دودویی_op = save;
      أرجع ret;
    }

  /* Aggregates in different TUs might need conversion.  */
  إذا ((codel == رکورد_TYPE || codel == UNION_TYPE)
      && codel == coder
      && comptypes (TYPE_MAIN_VARIANT (type), TYPE_MAIN_VARIANT (rhstype)))
    أرجع convert_and_check (عبارت_loc != UNKNOWN_LOCATION
			      ? عبارت_loc : location, type, rhs);

  /* Conversion to a transparent union or record from its member types.
     This applies only to function arguments.  */
  إذا (((codel == UNION_TYPE || codel == رکورد_TYPE)
      && TYPE_TRANSPARENT_AGGR (type))
      && errtype == ic_argpass)
    {
      درخت memb, marginal_memb = NULL_درخت;

      لكل (memb = TYPE_FIELDS (type); memb ; memb = DECL_CHAIN (memb))
	{
	  درخت memb_type = درخت_TYPE (memb);

	  إذا (comptypes (TYPE_MAIN_VARIANT (memb_type),
			 TYPE_MAIN_VARIANT (rhstype)))
	    اكسر;

	  إذا (درخت_کد (memb_type) != اشاره_گر_TYPE)
	    استمر;

	  إذا (coder == اشاره_گر_TYPE)
	    {
	      درخت ttl = درخت_TYPE (memb_type);
	      درخت ttr = درخت_TYPE (rhstype);

	      /* Any non-function converts to a [const][volatile] void *
		 and vice versa; otherwise, targets must be the same.
		 Meanwhile, the lhs target must have all the qualifiers of
		 the rhs.  */
	      إذا ((VOID_TYPE_P (ttl) && !TYPE_ATOMIC (ttl))
		  || (VOID_TYPE_P (ttr) && !TYPE_ATOMIC (ttr))
		  || comp_هدف_types (location, memb_type, rhstype))
		{
		  صحيح lquals = TYPE_QUALS (ttl) & ~TYPE_QUAL_ATOMIC;
		  صحيح rquals = TYPE_QUALS (ttr) & ~TYPE_QUAL_ATOMIC;
		  /* If this type won't generate any warnings, use it.  */
		  إذا (lquals == rquals
		      || ((درخت_کد (ttr) == FUNCTION_TYPE
			   && درخت_کد (ttl) == FUNCTION_TYPE)
			  ? ((lquals | rquals) == rquals)
			  : ((lquals | rquals) == lquals)))
		    اكسر;

		  /* Keep looking for a better type, but remember this one.  */
		  إذا (!marginal_memb)
		    marginal_memb = memb;
		}
	    }

	  /* Can convert integer zero to any pointer type.  */
	  إذا (null_اشاره_گر_constant)
	    {
	      rhs = null_اشاره_گر_گره;
	      اكسر;
	    }
	}

      إذا (memb || marginal_memb)
	{
	  إذا (!memb)
	    {
	      /* We have only a marginally acceptable member type;
		 it needs a warning.  */
	      درخت ttl = درخت_TYPE (درخت_TYPE (marginal_memb));
	      درخت ttr = درخت_TYPE (rhstype);

	      /* Const and volatile mean something different for function
		 types, so the usual warnings are not appropriate.  */
	      إذا (درخت_کد (ttr) == FUNCTION_TYPE
		  && درخت_کد (ttl) == FUNCTION_TYPE)
		{
		  /* Because const and volatile on functions are
		     restrictions that say the function will not do
		     certain things, it is okay to use a const or volatile
		     function where an ordinary one is wanted, but not
		     vice-versa.  */
		  إذا (TYPE_QUALS_NO_ADDR_SPACE (ttl)
		      & ~TYPE_QUALS_NO_ADDR_SPACE (ttr))
		    PEDWARN_FOR_QUALIFIERS (location, عبارت_loc,
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
	      وإلا إذا (TYPE_QUALS_NO_ADDR_SPACE (ttr)
		       & ~TYPE_QUALS_NO_ADDR_SPACE (ttl))
		PEDWARN_FOR_QUALIFIERS (location, عبارت_loc,
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

	  إذا (!fundecl || !DECL_درون_SYSTEM_سرآیند (fundecl))
	    pedwarn (location, OPT_Wpedantic,
		     "ISO C prohibits argument conversion to union type");

	  rhs = fold_convert_loc (location, درخت_TYPE (memb), rhs);
	  أرجع build_constructor_single (type, memb, rhs);
	}
    }

  /* Conversions among pointers */
  وإلا إذا ((codel == اشاره_گر_TYPE || codel == REFERENCE_TYPE)
	   && (coder == codel))
    {
      /* If RHS refers to a built-in declared without a prototype
	 BLTIN is the declaration of the built-in with a prototype
	 and RHSTYPE is set to the actual type of the built-in.  */
      درخت bltin;
      rhstype = type_or_builtin_type (rhs, &bltin);

      درخت ttl = درخت_TYPE (type);
      درخت ttr = درخت_TYPE (rhstype);
      منطقي is_opaque_اشاره_گر;
      منطقي هدف_cmp = خطأ;   /* Cache comp_target_types () result.  */
      addr_space_t asl;
      addr_space_t asr;

      درخت mvl = remove_qualifiers (ttl);
      درخت mvr = remove_qualifiers (ttr);

      /* Opaque pointers are treated like void pointers.  */
      is_opaque_اشاره_گر = وکتور_targets_convertible_p (ttl, ttr);

      /* The Plan 9 compiler permits a pointer to a struct to be
	 automatically converted into a pointer to an anonymous field
	 within the struct.  */
      إذا (flag_plan9_extensions
	  && رکورد_OR_UNION_TYPE_P (mvl)
	  && رکورد_OR_UNION_TYPE_P (mvr)
	  && mvl != mvr)
	{
	  درخت new_rhs = convert_مقصد_anonymous_فیلد (location, type, rhs);
	  إذا (new_rhs != NULL_درخت)
	    {
	      rhs = new_rhs;
	      rhstype = درخت_TYPE (rhs);
	      coder = درخت_کد (rhstype);
	      ttr = درخت_TYPE (rhstype);
	      mvr = TYPE_MAIN_VARIANT (ttr);
	    }
	}

      /* C++ does not allow the implicit conversion void* -> T*.  However,
	 for the purpose of reducing the number of false positives, we
	 tolerate the special case of

		int *p = NULL;

	 where NULL is typically defined in C to be '(void *) 0'.  */
      إذا (VOID_TYPE_P (ttr) && rhs != null_اشاره_گر_گره && !VOID_TYPE_P (ttl))
	warning_at (errtype == ic_argpass ? عبارت_loc : location,
		    OPT_Wc___compat,
		    "request for implicit conversion "
		    "from %qT to %qT not permitted in C++", rhstype, type);

      /* Warn of new allocations that are not big enough for the target
	 type.  */
      إذا (warn_alloc_اندازه && درخت_کد (rhs) == CALL_عبارت)
	إذا (درخت fndecl = get_callee_fndecl (rhs))
	  إذا (DECL_IS_MALLOC (fndecl))
	    {
	      درخت attrs = TYPE_صفات (درخت_TYPE (fndecl));
	      درخت alloc_اندازه = lookup_attribute ("alloc_size", attrs);
	      إذا (alloc_اندازه)
		warn_for_alloc_اندازه (location, ttl, rhs, alloc_اندازه);
	    }

      /* See if the pointers point to incompatible address spaces.  */
      asl = TYPE_ADDR_SPACE (ttl);
      asr = TYPE_ADDR_SPACE (ttr);
      إذا (!null_اشاره_گر_constant_p (rhs)
	  && asr != asl && !targetm.addr_space.subset_p (asr, asl))
	{
	  auto_diagnostic_گروه d;
	  منطقي diagnosed = درست;
	  بدل (errtype)
	    {
	    حالة ic_argpass:
	      {
		ثابت حرف پیام_2[] = G_("passing argument %d of %qE from "
				      "pointer to non-enclosed address space");
		إذا (warnopt)
		  diagnosed
		    = warning_at (عبارت_loc, warnopt, پیام_2, parmnum, rname);
		وإلا
		  error_at (عبارت_loc, پیام_2, parmnum, rname);
	      اكسر;
	      }
	    حالة ic_تخصیص_بده:
	      {
		ثابت حرف پیام_2[] = G_("assignment from pointer to "
				      "non-enclosed address space");
		إذا (warnopt)
		  diagnosed = warning_at (location, warnopt, پیام_2);
		وإلا
		  error_at (location, پیام_2);
		اكسر;
	      }
	    حالة ic_init:
	    حالة ic_init_const:
	      {
		ثابت حرف پیام_2[] = G_("initialization from pointer to "
				      "non-enclosed address space");
		إذا (warnopt)
		  diagnosed = warning_at (location, warnopt, پیام_2);
		وإلا
		  error_at (location, پیام_2);
		اكسر;
	      }
	    حالة ic_return:
	      {
		ثابت حرف پیام_2[] = G_("return from pointer to "
				      "non-enclosed address space");
		إذا (warnopt)
		  diagnosed = warning_at (location, warnopt, پیام_2);
		وإلا
		  error_at (location, پیام_2);
		اكسر;
	      }
	    افتراضي:
	      gcc_unreachable ();
	    }
	  إذا (diagnosed)
	    {
	      إذا (errtype == ic_argpass)
		inform_for_arg (fundecl, عبارت_loc, parmnum, type, rhstype);
	      وإلا
		inform (location, "expected %qT but pointer is of type %qT",
			type, rhstype);
	    }
	  أرجع error_mark_گره;
	}

      /* Check if the right-hand side has a format attribute but the
	 left-hand side doesn't.  */
      إذا (warn_suggest_attribute_format
	  && check_missing_format_attribute (type, rhstype))
	{
	  بدل (errtype)
	  {
	  حالة ic_argpass:
	    warning_at (عبارت_loc, OPT_Wsuggest_attribute_format,
			"argument %d of %qE might be "
			"a candidate for a format attribute",
			parmnum, rname);
	    اكسر;
	  حالة ic_تخصیص_بده:
	    warning_at (location, OPT_Wsuggest_attribute_format,
			"assignment left-hand side might be "
			"a candidate for a format attribute");
	    اكسر;
	  حالة ic_init:
	  حالة ic_init_const:
	    warning_at (location, OPT_Wsuggest_attribute_format,
			"initialization left-hand side might be "
			"a candidate for a format attribute");
	    اكسر;
	  حالة ic_return:
	    warning_at (location, OPT_Wsuggest_attribute_format,
			"return type might be "
			"a candidate for a format attribute");
	    اكسر;
	  افتراضي:
	    gcc_unreachable ();
	  }
	}

      /* See if the pointers point to incompatible scalar storage orders.  */
      إذا (warn_scalar_storage_ترتیب
	  && !null_اشاره_گر_constant_p (rhs)
	  && (AGGREGATE_TYPE_P (ttl) && TYPE_معکوس_STORAGE_ترتیب (ttl))
	     != (AGGREGATE_TYPE_P (ttr) && TYPE_معکوس_STORAGE_ترتیب (ttr)))
	{
	  درخت t;

	  بدل (errtype)
	  {
	  حالة ic_argpass:
	    /* Do not warn for built-in functions, for example memcpy, since we
	       control how they behave and they can be useful in this area.  */
	    إذا (درخت_کد (rname) != FUNCTION_DECL
		|| !fndecl_built_درون_p (rname))
	      warning_at (location, OPT_Wscalar_storage_ترتیب,
			  "passing argument %d of %qE from incompatible "
			  "scalar storage order", parmnum, rname);
	    اكسر;
	  حالة ic_تخصیص_بده:
	    /* Do not warn if the RHS is a call to a function that returns a
	       pointer that is not an alias.  */
	    إذا (درخت_کد (rhs) != CALL_عبارت
		|| (t = get_callee_fndecl (rhs)) == NULL_درخت
		|| !DECL_IS_MALLOC (t))
	      warning_at (location, OPT_Wscalar_storage_ترتیب,
			  "assignment to %qT from pointer type %qT with "
			  "incompatible scalar storage order", type, rhstype);
	    اكسر;
	  حالة ic_init:
	  حالة ic_init_const:
	    /* Likewise.  */
	    إذا (درخت_کد (rhs) != CALL_عبارت
		|| (t = get_callee_fndecl (rhs)) == NULL_درخت
		|| !DECL_IS_MALLOC (t))
	      warning_at (location, OPT_Wscalar_storage_ترتیب,
			  "initialization of %qT from pointer type %qT with "
			  "incompatible scalar storage order", type, rhstype);
	    اكسر;
	  حالة ic_return:
	    warning_at (location, OPT_Wscalar_storage_ترتیب,
			"returning %qT from pointer type with incompatible "
			"scalar storage order %qT", rhstype, type);
	    اكسر;
	  افتراضي:
	    gcc_unreachable ();
	  }
	}

      /* Any non-function converts to a [const][volatile] void *
	 and vice versa; otherwise, targets must be the same.
	 Meanwhile, the lhs target must have all the qualifiers of the rhs.  */
      إذا ((VOID_TYPE_P (ttl) && !TYPE_ATOMIC (ttl))
	  || (VOID_TYPE_P (ttr) && !TYPE_ATOMIC (ttr))
	  || (هدف_cmp = comp_هدف_types (location, type, rhstype))
	  || is_opaque_اشاره_گر
	  || ((c_common_unsigned_type (mvl)
	       == c_common_unsigned_type (mvr))
	      && (c_common_signed_type (mvl)
		  == c_common_signed_type (mvr))
	      && TYPE_ATOMIC (mvl) == TYPE_ATOMIC (mvr)))
	{
	  /* Warn about loss of qualifers from pointers to arrays with
	     qualifiers on the element type. */
	  إذا (درخت_کد (ttr) == ARRAY_TYPE)
	    {
	      ttr = strip_array_types (ttr);
	      ttl = strip_array_types (ttl);

	      إذا (TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttr)
		  & ~TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttl))
		WARNING_FOR_QUALIFIERS (flag_isoc23,
					location, عبارت_loc,
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
          وإلا إذا (pedantic
	      && ((VOID_TYPE_P (ttl) && درخت_کد (ttr) == FUNCTION_TYPE)
		  ||
		  (VOID_TYPE_P (ttr)
		   && !null_اشاره_گر_constant
		   && درخت_کد (ttl) == FUNCTION_TYPE)))
	    PEDWARN_FOR_ASSIGNMENT (location, عبارت_loc, OPT_Wpedantic,
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
	  وإلا إذا (درخت_کد (ttr) != FUNCTION_TYPE
		   && درخت_کد (ttl) != FUNCTION_TYPE)
	    {
	       /* Assignments between atomic and non-atomic objects are OK.  */
	       منطقي warn_quals_ped = TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttr)
				     & ~TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttl);
	       منطقي warn_quals = TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttr)
				 & ~TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (strip_array_types (ttl));

	      /* Don't warn about loss of qualifier for conversions from
		 qualified void* to pointers to arrays with corresponding
		 qualifier on the element type (except for pedantic before C23). */
	      إذا (warn_quals || (warn_quals_ped && pedantic && !flag_isoc23))
		PEDWARN_FOR_QUALIFIERS (location, عبارت_loc,
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
	      وإلا إذا (warn_quals_ped)
		pedwarn_c11 (location, OPT_Wc11_c23_compat,
			     "array with qualifier on the element is not qualified before C23");

	      /* If this is not a case of ignoring a mismatch in signedness,
		 no warning.  */
	      وإلا إذا (VOID_TYPE_P (ttl) || VOID_TYPE_P (ttr)
		       || هدف_cmp)
		;
	      /* If there is a mismatch, do warn.  */
	      وإلا إذا (warn_اشاره_گر_sign)
		بدل (errtype)
		  {
		  حالة ic_argpass:
		    {
		      auto_diagnostic_گروه d;
		      range_label_for_type_mismatch rhs_label (rhstype, type);
		      gcc_rich_location richloc (عبارت_loc, &rhs_label,
						 highlight_colors::actual);
		      إذا (pedwarn (&richloc, OPT_Wpointer_sign,
				   "pointer targets in passing argument %d of "
				   "%qE differ in signedness", parmnum, rname))
			inform_for_arg (fundecl, عبارت_loc, parmnum, type,
					rhstype);
		    }
		    اكسر;
		  حالة ic_تخصیص_بده:
		    pedwarn (location, OPT_Wpointer_sign,
			     "pointer targets in assignment from %qT to %qT "
			     "differ in signedness", rhstype, type);
		    اكسر;
		  حالة ic_init:
		  حالة ic_init_const:
		    pedwarn_init (location, OPT_Wpointer_sign,
				  "pointer targets in initialization of %qT "
				  "from %qT differ in signedness", type,
				  rhstype);
		    اكسر;
		  حالة ic_return:
		    pedwarn (location, OPT_Wpointer_sign, "pointer targets in "
			     "returning %qT from a function with return type "
			     "%qT differ in signedness", rhstype, type);
		    اكسر;
		  افتراضي:
		    gcc_unreachable ();
		  }
	    }
	  وإلا إذا (درخت_کد (ttl) == FUNCTION_TYPE
		   && درخت_کد (ttr) == FUNCTION_TYPE)
	    {
	      /* Because const and volatile on functions are restrictions
		 that say the function will not do certain things,
		 it is okay to use a const or volatile function
		 where an ordinary one is wanted, but not vice-versa.  */
	      إذا (TYPE_QUALS_NO_ADDR_SPACE (ttl)
		  & ~TYPE_QUALS_NO_ADDR_SPACE (ttr))
		PEDWARN_FOR_QUALIFIERS (location, عبارت_loc,
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
      وإلا إذا (!objc_ok)
	{
	  auto_diagnostic_گروه d;
	  منطقي warned = خطأ;
	  pp_markup::element_expected_type e_type (type);
	  pp_markup::element_actual_type e_rhstype (rhstype);
	  بدل (errtype)
	    {
	    حالة ic_argpass:
	      {
		range_label_for_type_mismatch rhs_label (rhstype, type);
		gcc_rich_location richloc (عبارت_loc, &rhs_label,
					   highlight_colors::actual);
		warned
		  = permerror_opt (&richloc, OPT_Wincompatible_اشاره_گر_types,
				   "passing argument %d of %qE from "
				   "incompatible pointer type",
				   parmnum, rname);
		إذا (warned)
		  inform_for_arg (fundecl, عبارت_loc, parmnum, type, rhstype);
	      }
	      اكسر;
	    حالة ic_تخصیص_بده:
	      إذا (bltin)
		warned
		  = permerror_opt (location, OPT_Wincompatible_اشاره_گر_types,
				   "assignment to %e from pointer to "
				   "%qD with incompatible type %e",
				   &e_type, bltin, &e_rhstype);
	      وإلا
		warned
		  = permerror_opt (location, OPT_Wincompatible_اشاره_گر_types,
				   "assignment to %e from incompatible "
				   "pointer type %e",
				   &e_type, &e_rhstype);
	      اكسر;
	    حالة ic_init:
	    حالة ic_init_const:
	      إذا (bltin)
		warned
		  = permerror_init (location, OPT_Wincompatible_اشاره_گر_types,
				    "initialization of %e from pointer to "
				    "%qD with incompatible type %e",
				    &e_type, bltin, &e_rhstype);
	      وإلا
		warned
		  = permerror_init (location, OPT_Wincompatible_اشاره_گر_types,
				    "initialization of %e from incompatible "
				    "pointer type %e",
				    &e_type, &e_rhstype);
	      اكسر;
	    حالة ic_return:
	      إذا (bltin)
		warned
		  = permerror_opt (location, OPT_Wincompatible_اشاره_گر_types,
				   "returning pointer to %qD of type %e from "
				   "a function with incompatible type %e",
				   bltin, &e_rhstype, &e_type);
	      وإلا
		warned
		  = permerror_opt (location, OPT_Wincompatible_اشاره_گر_types,
				   "returning %e from a function with "
				   "incompatible return type %e",
				   &e_rhstype, &e_type);
	      اكسر;
	    افتراضي:
	      gcc_unreachable ();
	    }
	  إذا (warned)
	    {
	      /* If the mismatching function type is a pointer to a function,
		 try to show the decl of the function.  */
	      إذا (درخت_کد (rhs) == ADDR_عبارت
		  && درخت_کد (درخت_عملوند (rhs, 0)) == FUNCTION_DECL)
		{
		  درخت rhs_fndecl = درخت_عملوند (rhs, 0);
		  إذا (!DECL_IS_UNDECLARED_BUILTIN (rhs_fndecl))
		    {
		      gcc_rich_location richloc
			(DECL_منبع_LOCATION (rhs_fndecl), اشاره_تهی,
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
      warn_for_آدرس_از_packed_member (type, orig_rhs);

      أرجع convert (type, rhs);
    }
  وإلا إذا (codel == اشاره_گر_TYPE && coder == ARRAY_TYPE)
    {
      /* ??? This should not be an error when inlining calls to
	 unprototyped functions.  */
      ثابت حرف پیام_2[] = "invalid use of non-lvalue array";
      إذا (warnopt)
	warning_at (location, warnopt, پیام_2);
      وإلا
	error_at (location, پیام_2);
      أرجع error_mark_گره;
    }
  وإلا إذا (codel == اشاره_گر_TYPE
	   && (coder == INTEGER_TYPE
	       || coder == ENUMERAL_TYPE
	       || coder == BOOLEAN_TYPE
	       || coder == NULLPTR_TYPE
	       || coder == BITINT_TYPE))
    {
      إذا (null_اشاره_گر_constant && c_inhibit_evaluation_warnings == 0
	  && coder != NULLPTR_TYPE)
	warning_at (location, OPT_Wzero_as_null_اشاره_گر_constant,
		    "zero as null pointer constant");
      /* A NULLPTR type is just a nullptr always.  */
      إذا (coder == NULLPTR_TYPE)
	أرجع omit_one_عملوند_loc (عبارت_loc, type, nullptr_گره, rhs);
      /* An explicit constant 0 or type nullptr_t can convert to a pointer,
	 or one that results from arithmetic, even including a cast to
	 integer type.  */
      وإلا إذا (!null_اشاره_گر_constant)
	بدل (errtype)
	  {
	  حالة ic_argpass:
	    {
	      auto_diagnostic_گروه d;
	      range_label_for_type_mismatch rhs_label (rhstype, type);
	      gcc_rich_location richloc (عبارت_loc, &rhs_label,
					 highlight_colors::actual);
	      إذا (permerror_opt (&richloc, OPT_Wint_conversion,
				 "passing argument %d of %qE makes pointer "
				 "from integer without a cast", parmnum, rname))
		{
		  maybe_emit_indirection_note (عبارت_loc, rhs, type);
		  inform_for_arg (fundecl, عبارت_loc, parmnum, type, rhstype);
		}
	    }
	    اكسر;
	  حالة ic_تخصیص_بده:
	    permerror_opt (location, OPT_Wint_conversion,
			   "assignment to %qT from %qT makes pointer from "
			   "integer without a cast", type, rhstype);
	    اكسر;
	  حالة ic_init:
	  حالة ic_init_const:
	    permerror_init (location, OPT_Wint_conversion,
			    "initialization of %qT from %qT makes pointer "
			    "from integer without a cast", type, rhstype);
	    اكسر;
	  حالة ic_return:
	    permerror_init (location, OPT_Wint_conversion,
			    "returning %qT from a function with return type "
			    "%qT makes pointer from integer without a cast",
			    rhstype, type);
	    اكسر;
	  افتراضي:
	    gcc_unreachable ();
	  }

      أرجع convert (type, rhs);
    }
  وإلا إذا ((codel == INTEGER_TYPE || codel == BITINT_TYPE)
	   && coder == اشاره_گر_TYPE)
    {
      بدل (errtype)
	{
	حالة ic_argpass:
	  {
	    auto_diagnostic_گروه d;
	    range_label_for_type_mismatch rhs_label (rhstype, type);
	    gcc_rich_location richloc (عبارت_loc, &rhs_label,
				       highlight_colors::actual);
	    إذا (permerror_opt (&richloc, OPT_Wint_conversion,
			       "passing argument %d of %qE makes integer from "
			       "pointer without a cast", parmnum, rname))
	      {
		maybe_emit_indirection_note (عبارت_loc, rhs, type);
		inform_for_arg (fundecl, عبارت_loc, parmnum, type, rhstype);
	      }
	  }
	  اكسر;
	حالة ic_تخصیص_بده:
	  permerror_opt (location, OPT_Wint_conversion,
			 "assignment to %qT from %qT makes integer from "
			 "pointer without a cast", type, rhstype);
	  اكسر;
	حالة ic_init:
	حالة ic_init_const:
	  permerror_init (location, OPT_Wint_conversion,
			  "initialization of %qT from %qT makes integer "
			  "from pointer without a cast", type, rhstype);
	  اكسر;
	حالة ic_return:
	  permerror_opt (location, OPT_Wint_conversion, "returning %qT from a "
			 "function with return type %qT makes integer from "
			 "pointer without a cast", rhstype, type);
	  اكسر;
	افتراضي:
	  gcc_unreachable ();
	}

      أرجع convert (type, rhs);
    }
  وإلا إذا (C_BOOLEAN_TYPE_P (type)
	   /* The type nullptr_t may be converted to bool.  The
	      result is false.  */
	   && (coder == اشاره_گر_TYPE || coder == NULLPTR_TYPE))
    {
      درخت ret;
      منطقي save = درون_late_دودویی_op;
      درون_late_دودویی_op = درست;
      ret = convert (type, rhs);
      درون_late_دودویی_op = save;
      أرجع ret;
    }
  وإلا إذا (codel == NULLPTR_TYPE && null_اشاره_گر_constant)
    أرجع convert (type, rhs);

  بدل (errtype)
    {
    حالة ic_argpass:
      {
	auto_diagnostic_گروه d;
	range_label_for_type_mismatch rhs_label (rhstype, type);
	gcc_rich_location richloc (عبارت_loc, &rhs_label,
				   highlight_colors::actual);
	ثابت حرف پیام_2[] = G_("incompatible type for argument %d of %qE");
	إذا (warnopt)
	  warning_at (عبارت_loc, warnopt, پیام_2, parmnum, rname);
	وإلا
	  error_at (&richloc, پیام_2, parmnum, rname);
	inform_for_arg (fundecl, عبارت_loc, parmnum, type, rhstype);
      }
      اكسر;
    حالة ic_تخصیص_بده:
      {
	ثابت حرف پیام_2[]
	  = G_("incompatible types when assigning to type %qT from type %qT");
	إذا (warnopt)
	  warning_at (عبارت_loc, 0, پیام_2, type, rhstype);
	وإلا
	  error_at (عبارت_loc, پیام_2, type, rhstype);
	اكسر;
      }
    حالة ic_init:
    حالة ic_init_const:
      {
	ثابت حرف پیام_2[]
	  = G_("incompatible types when initializing type %qT using type %qT");
	إذا (warnopt)
	  warning_at (location, 0, پیام_2, type, rhstype);
	وإلا
	  error_at (location, پیام_2, type, rhstype);
	اكسر;
      }
    حالة ic_return:
      {
	ثابت حرف پیام_2[]
	  = G_("incompatible types when returning type %qT but %qT was expected");
	إذا (warnopt)
	  warning_at (location, 0, پیام_2, rhstype, type);
	وإلا
	  error_at (location, پیام_2, rhstype, type);
	اكسر;
      }
    افتراضي:
      gcc_unreachable ();
    }

  أرجع error_mark_گره;
}

/* If VALUE is a compound expr all of whose expressions are constant, then
   return its value.  Otherwise, return error_mark_node.

   This is for handling COMPOUND_EXPRs as initializer elements
   which is allowed with a warning when -pedantic is specified.  */

ساكن درخت
valid_compound_عبارت_initializer (درخت مقدار, درخت endtype)
{
  إذا (درخت_کد (مقدار) == COMPOUND_عبارت)
    {
      إذا (valid_compound_عبارت_initializer (درخت_عملوند (مقدار, 0), endtype)
	  == error_mark_گره)
	أرجع error_mark_گره;
      أرجع valid_compound_عبارت_initializer (درخت_عملوند (مقدار, 1),
					      endtype);
    }
  وإلا إذا (!initializer_constant_valid_p (مقدار, endtype))
    أرجع error_mark_گره;
  وإلا
    أرجع مقدار;
}

/* Perform appropriate conversions on the initial value of a variable,
   store it in the declaration DECL,
   and print any error messages that are appropriate.
   If ORIGTYPE is not NULL_TREE, it is the original type of INIT.
   If the init is invalid, store an ERROR_MARK.

   INIT_LOC is the location of the initial value.  */

فراغ
store_init_مقدار (location_t init_loc, درخت decl, درخت init, درخت origtype)
{
  درخت مقدار, type;
  منطقي npc = خطأ;
  منطقي int_const_عبارت = خطأ;
  منطقي arith_const_عبارت = خطأ;

  /* If variable's type was invalidly declared, just ignore it.  */

  type = درخت_TYPE (decl);
  إذا (درخت_کد (type) == ERROR_MARK)
    أرجع;

  /* Digest the specified initializer into an expression.  */

  إذا (init)
    {
      npc = null_اشاره_گر_constant_p (init);
      int_const_عبارت = (درخت_کد (init) == INTEGER_CST
			&& !درخت_سرریز (init)
			&& INTEGRAL_TYPE_P (درخت_TYPE (init)));
      /* Not fully determined before folding.  */
      arith_const_عبارت = درست;
    }
  منطقي constexpr_p = (VAR_P (decl)
		      && C_DECL_DECLARED_CONSTEXPR (decl));
  مقدار = digest_init (init_loc, decl, type, init, origtype, npc,
		       int_const_عبارت, arith_const_عبارت, درست,
		       درخت_STATIC (decl) || constexpr_p, constexpr_p);

  /* Store the expression if valid; else report error.  */

  إذا (!درون_system_سرآیند_at (درون_داد_location)
      && AGGREGATE_TYPE_P (درخت_TYPE (decl)) && !درخت_STATIC (decl))
    warning (OPT_Wtraditional, "traditional C rejects automatic "
	     "aggregate initialization");

  إذا (مقدار != error_mark_گره || درخت_کد (decl) != FUNCTION_DECL)
    DECL_INITIAL (decl) = مقدار;

  /* ANSI wants warnings about out-of-range constant initializers.  */
  STRIP_TYPE_NOPS (مقدار);
  إذا (درخت_STATIC (decl))
    constant_عبارت_warning (مقدار);

  /* Check if we need to set array size from compound literal size.  */
  إذا (درخت_کد (type) == ARRAY_TYPE
      && TYPE_DOMAIN (type) == NULL_درخت
      && مقدار != error_mark_گره)
    {
      درخت inside_init = init;

      STRIP_TYPE_NOPS (inside_init);
      inside_init = fold (inside_init);

      إذا (درخت_کد (inside_init) == COMPOUND_LITERAL_عبارت)
	{
	  درخت cldecl = COMPOUND_LITERAL_عبارت_DECL (inside_init);

	  إذا (TYPE_DOMAIN (درخت_TYPE (cldecl)))
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

بنية spelling
{
  صحيح نوع;
  اتحاد
    {
      بیعلامت HOST_WIDE_INT i;
      ثابت حرف *s;
    } u;
};

#تعریف_کن SPELLING_STRING 1
#تعریف_کن SPELLING_MEMBER 2
#تعریف_کن SPELLING_BOUNDS 3

ساكن بنية spelling *spelling;	/* Next stack element (unused).  */
ساكن بنية spelling *spelling_پایه;	/* Spelling stack base.  */
ساكن صحيح spelling_اندازه;		/* Size of the spelling stack.  */

/* Macros to save and restore the spelling stack around push_... functions.
   Alternative to SAVE_SPELLING_STACK.  */

#تعریف_کن SPELLING_عمق() (spelling - spelling_پایه)
#تعریف_کن RESTORE_SPELLING_عمق(عمق_2) (spelling = spelling_پایه + (عمق_2))

/* Push an element on the spelling stack with type KIND and assign VALUE
   to MEMBER.  */

#تعریف_کن افزودن_SPELLING(نوع_2, مقدار_2, MEMBER)				\
{									\
  صحيح عمق = SPELLING_عمق ();					\
									\
  إذا (عمق >= spelling_اندازه)						\
    {									\
      spelling_اندازه += 10;						\
      spelling_پایه = XRESIZEVEC (بنية spelling, spelling_پایه,	\
				  spelling_اندازه);			\
      RESTORE_SPELLING_عمق (عمق);					\
    }									\
									\
  spelling->نوع = (نوع_2);						\
  spelling->MEMBER = (مقدار_2);						\
  spelling++;								\
}

/* Push STRING on the stack.  Printed literally.  */

ساكن فراغ
افزودن_string (ثابت حرف *string)
{
  افزودن_SPELLING (SPELLING_STRING, string, u.s);
}

/* Push a member name on the stack.  Printed as '.' STRING.  */

ساكن فراغ
افزودن_member_name (درخت decl)
{
  ثابت حرف *ثابت string
    = (DECL_NAME (decl)
       ? identifier_مقصد_locale (IDENTIFIER_اشاره_گر (DECL_NAME (decl)))
       : _("<anonymous>"));
  افزودن_SPELLING (SPELLING_MEMBER, string, u.s);
}

/* Push an array bounds on the stack.  Printed as [BOUNDS].  */

ساكن فراغ
افزودن_array_bounds (بیعلامت HOST_WIDE_INT bounds)
{
  افزودن_SPELLING (SPELLING_BOUNDS, bounds, u.i);
}

/* Compute the maximum size in bytes of the printed spelling.  */

ساكن صحيح
spelling_درازی (فراغ)
{
  صحيح اندازه = 0;
  بنية spelling *p;

  لكل (p = spelling_پایه; p < spelling; p++)
    {
      إذا (p->نوع == SPELLING_BOUNDS)
	اندازه += 25;
      وإلا
	اندازه += طول_رشته (p->u.s) + 1;
    }

  أرجع اندازه;
}

/* Print the spelling to BUFFER and return it.  */

ساكن حرف *
print_spelling (حرف *میانگیر)
{
  حرف *d = میانگیر;
  بنية spelling *p;

  لكل (p = spelling_پایه; p < spelling; p++)
    إذا (p->نوع == SPELLING_BOUNDS)
      {
	sprintf (d, "[" HOST_WIDE_INT_PRINT_UNSIGNED "]", p->u.i);
	d += طول_رشته (d);
      }
    وإلا
      {
	ثابت حرف *s;
	إذا (p->نوع == SPELLING_MEMBER)
	  *d++ = '.';
	لكل (s = p->u.s; (*d = *s++); d++)
	  ;
      }
  *d++ = '\0';
  أرجع میانگیر;
}

/* Check whether INIT, a floating or integer constant, is
   representable in TYPE, a real floating type with the same radix or
   a decimal floating type initialized with a binary floating
   constant.  Return true if OK, false if not.  */
ساكن منطقي
constexpr_init_میگنجد_real_type (درخت type, درخت init)
{
  gcc_assert (SCALAR_FLOAT_TYPE_P (type));
  gcc_assert (درخت_کد (init) == INTEGER_CST || درخت_کد (init) == REAL_CST);
  إذا (درخت_کد (init) == REAL_CST
      && TYPE_نما (درخت_TYPE (init)) == TYPE_نما (type))
    {
      /* Same mode, no conversion required except for the case of
	 signaling NaNs if the types are incompatible (e.g. double and
	 long double with the same mode).  */
      إذا (REAL_مقدار_ISSIGNALING_NAN (درخت_REAL_CST (init))
	  && !comptypes (TYPE_MAIN_VARIANT (type),
			 TYPE_MAIN_VARIANT (درخت_TYPE (init))))
	أرجع خطأ;
      أرجع درست;
    }
  إذا (درخت_کد (init) == INTEGER_CST)
    {
      درخت converted = build_real_from_int_cst (type, init);
      منطقي fail = خطأ;
      wide_int w = real_مقصد_integer (&درخت_REAL_CST (converted), &fail,
				    TYPE_PRECISION (درخت_TYPE (init)));
      أرجع !fail && wi::eq_p (w, wi::مقصد_wide (init));
    }
  إذا (REAL_مقدار_ISSIGNALING_NAN (درخت_REAL_CST (init)))
    أرجع خطأ;
  إذا ((REAL_مقدار_ISINF (درخت_REAL_CST (init))
       && نما_HAS_INFINITIES (TYPE_نما (type)))
      || (REAL_مقدار_ISNAN (درخت_REAL_CST (init))
	  && نما_HAS_NANS (TYPE_نما (type))))
    أرجع درست;
  إذا (DECIMAL_FLOAT_TYPE_P (type)
      && !DECIMAL_FLOAT_TYPE_P (درخت_TYPE (init)))
    {
      /* This is valid if the real number represented by the
	 initializer can be exactly represented in the decimal
	 type.  Compare the values using MPFR.  */
      REAL_مقدار_TYPE t;
      real_convert (&t, TYPE_نما (type), &درخت_REAL_CST (init));
      mpfr_t bin_val, dec_val;
      mpfr_init2 (bin_val, REAL_نما_FORMAT (TYPE_نما (درخت_TYPE (init)))->p);
      mpfr_init2 (dec_val, REAL_نما_FORMAT (TYPE_نما (درخت_TYPE (init)))->p);
      mpfr_from_real (bin_val, &درخت_REAL_CST (init), MPFR_RNDN);
      حرف string[256];
      real_مقصد_decimal (string, &t, حجم string, 0, 1);
      منطقي res = (mpfr_strtofr (dec_val, string, عدم, 10, MPFR_RNDN) == 0
		  && mpfr_equal_p (bin_val, dec_val));
      mpfr_clear (bin_val);
      mpfr_clear (dec_val);
      أرجع res;
    }
  /* exact_real_truncate is not quite right here, since it doesn't
     allow even an exact conversion to subnormal values.  */
  REAL_مقدار_TYPE t;
  real_convert (&t, TYPE_نما (type), &درخت_REAL_CST (init));
  أرجع real_identical (&t, &درخت_REAL_CST (init));
}

/* Check whether INIT (location LOC) is valid as a 'constexpr'
   initializer for type TYPE, and give an error if not.  INIT has
   already been folded and verified to be constant.  INT_CONST_EXPR
   and ARITH_CONST_EXPR say whether it is an integer constant
   expression or arithmetic constant expression, respectively.  If
   TYPE is not a scalar type, this function does nothing.  */

ساكن فراغ
check_constexpr_init (location_t loc, درخت type, درخت init,
		      منطقي int_const_عبارت, منطقي arith_const_عبارت)
{
  إذا (اشاره_گر_TYPE_P (type))
    {
      /* The initializer must be null.  */
      إذا (درخت_کد (init) != INTEGER_CST || !integer_zerop (init))
	error_at (loc, "%<constexpr%> pointer initializer is not null");
      أرجع;
    }
  إذا (INTEGRAL_TYPE_P (type))
    {
      /* The initializer must be an integer constant expression,
	 representable in the target type.  */
      إذا (!int_const_عبارت)
	{
	  إذا (درخت_کد (init) == RAW_داده_CST
	      && TYPE_PRECISION (type) == CHAR_بیت)
	    {
	      إذا (!TYPE_UNSIGNED (type))
		لكل (بیعلامت صحيح i = 0;
		     i < (بیعلامت) RAW_داده_درازی (init); ++i)
		  إذا (RAW_داده_SCHAR_ELT (init, i) < 0)
		    {
		      error_at (loc, "%<constexpr%> initializer not "
				"representable in type of object");
		      اكسر;
		    }
	    }
	  وإلا
	    error_at (loc, "%<constexpr%> integer initializer is not an "
		      "integer constant expression");
	}
      وإلا إذا (!int_میگنجد_type_p (init, type))
	error_at (loc, "%<constexpr%> initializer not representable in "
		  "type of object");
      أرجع;
    }
  /* We don't apply any extra checks to extension types such as vector
     or fixed-point types.  */
  إذا (درخت_کد (type) != REAL_TYPE && درخت_کد (type) != COMPLEX_TYPE)
    أرجع;
  إذا (!arith_const_عبارت)
    {
      error_at (loc, "%<constexpr%> initializer is not an arithmetic "
		"constant expression");
      أرجع;
    }
  /* We don't apply any extra checks to complex integers.  */
  إذا (درخت_کد (type) == COMPLEX_TYPE
      && درخت_کد (درخت_TYPE (type)) != REAL_TYPE)
    أرجع;
  /* Following N3082, a real type cannot be initialized from a complex
     type and a binary type cannot be initialized from a decimal type
     (but initializing a decimal type from a binary type is OK).
     Signaling NaN initializers are OK only if the types are
     compatible (not just the same mode); all quiet NaN and infinity
     initializations are considered to preserve the value.  */
  إذا (درخت_کد (درخت_TYPE (init)) == COMPLEX_TYPE
      && SCALAR_FLOAT_TYPE_P (type))
    {
      error_at (loc, "%<constexpr%> initializer for a real type is of "
		"complex type");
      أرجع;
    }
  إذا (SCALAR_FLOAT_TYPE_P (type)
      && SCALAR_FLOAT_TYPE_P (درخت_TYPE (init))
      && DECIMAL_FLOAT_TYPE_P (درخت_TYPE (init))
      && !DECIMAL_FLOAT_TYPE_P (type))
    {
      error_at (loc, "%<constexpr%> initializer for a binary "
		"floating-point type is of decimal type");
      أرجع;
    }
  منطقي میگنجد;
  إذا (درخت_کد (type) == COMPLEX_TYPE)
    {
      بدل (درخت_کد (init))
	{
	حالة INTEGER_CST:
	حالة REAL_CST:
	  میگنجد = constexpr_init_میگنجد_real_type (درخت_TYPE (type), init);
	  اكسر;
	حالة COMPLEX_CST:
	  میگنجد = (constexpr_init_میگنجد_real_type (درخت_TYPE (type),
						 درخت_REALPART (init))
		  && constexpr_init_میگنجد_real_type (درخت_TYPE (type),
						    درخت_IMAGPART (init)));
	  اكسر;
	افتراضي:
	  gcc_unreachable ();
	}
    }
  وإلا
    میگنجد = constexpr_init_میگنجد_real_type (type, init);
  إذا (!میگنجد)
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

ساكن درخت
digest_init (location_t init_loc, درخت decl, درخت type, درخت init,
	     درخت origtype, منطقي null_اشاره_گر_constant, منطقي int_const_عبارت,
	     منطقي arith_const_عبارت, منطقي strict_string,
	     منطقي require_constant, منطقي require_constexpr)
{
  تعداد درخت_کد_2 کد = درخت_کد (type);
  درخت inside_init = init;
  درخت semantic_type = NULL_درخت;
  منطقي maybe_const = درست;

  إذا (type == error_mark_گره
      || !init
      || error_عملوند_p (init))
    أرجع error_mark_گره;

  STRIP_TYPE_NOPS (inside_init);

  /* If require_constant is TRUE,  when the initializer is a call to
     .ACCESS_WITH_SIZE, use the first argument as the initializer.
     For example:
     y = (char *) .ACCESS_WITH_SIZE ((char *) &static_annotated.c,...)
     will be converted to
     y = &static_annotated.c.  */

  إذا (require_constant
      && درخت_کد (inside_init) == NOP_عبارت
      && درخت_کد (درخت_عملوند (inside_init, 0)) == CALL_عبارت
      && is_access_with_اندازه_p (درخت_عملوند (inside_init, 0)))
    inside_init
      = get_ref_from_access_with_اندازه (درخت_عملوند (inside_init, 0));

  إذا (!c_درون_omp_for)
    {
      إذا (درخت_کد (inside_init) == EXCESS_PRECISION_عبارت)
	{
	  semantic_type = درخت_TYPE (inside_init);
	  inside_init = درخت_عملوند (inside_init, 0);
	}
      inside_init = c_fully_fold (inside_init, require_constant, &maybe_const);
    }
  /* TODO: this may not detect all cases of expressions folding to
     constants that are not arithmetic constant expressions.  */
  إذا (!maybe_const)
    arith_const_عبارت = خطأ;
  وإلا إذا (!INTEGRAL_TYPE_P (درخت_TYPE (inside_init))
	   && درخت_کد (درخت_TYPE (inside_init)) != REAL_TYPE
	   && درخت_کد (درخت_TYPE (inside_init)) != COMPLEX_TYPE)
    arith_const_عبارت = خطأ;
  وإلا إذا (درخت_کد (inside_init) != INTEGER_CST
	   && درخت_کد (inside_init) != REAL_CST
	   && درخت_کد (inside_init) != COMPLEX_CST
	   && درخت_کد (inside_init) != RAW_داده_CST)
    arith_const_عبارت = خطأ;
  وإلا إذا (درخت_سرریز (inside_init))
    arith_const_عبارت = خطأ;

  /* Initialization of an array of chars from a string constant
     optionally enclosed in braces.  */

  إذا (کد == ARRAY_TYPE && inside_init
      && درخت_کد (inside_init) == STRING_CST)
    {
      درخت typ1
	= (TYPE_ATOMIC (درخت_TYPE (type))
	   ? c_build_qualified_type (TYPE_MAIN_VARIANT (درخت_TYPE (type)),
				     TYPE_QUAL_ATOMIC)
	   : TYPE_MAIN_VARIANT (درخت_TYPE (type)));
      /* Note that an array could be both an array of character type
	 and an array of wchar_t if wchar_t is signed char or unsigned
	 char.  */
      منطقي char_array = (typ1 == char_type_گره
			 || typ1 == signed_char_type_گره
			 || typ1 == unsigned_char_type_گره);
      منطقي wchar_array = comptypes (typ1, wchar_type_گره);
      منطقي char16_array = comptypes (typ1, char16_type_گره);
      منطقي char32_array = comptypes (typ1, char32_type_گره);

      إذا (char_array || wchar_array || char16_array || char32_array)
	{
	  بنية c_عبارت عبارت;
	  درخت typ2 = TYPE_MAIN_VARIANT (درخت_TYPE (درخت_TYPE (inside_init)));
	  منطقي incompat_string_cst = خطأ;
	  عبارت.مقدار = inside_init;
	  عبارت.original_کد = (strict_string ? STRING_CST : ERROR_MARK);
	  عبارت.original_type = عدم;
	  عبارت.m_decimal = 0;
	  maybe_warn_string_init (init_loc, type, عبارت);

	  إذا (flexible_array_member_type_p (type))
	    pedwarn_init (init_loc, OPT_Wpedantic,
			  "initialization of a flexible array member");

	  إذا (comptypes (TYPE_MAIN_VARIANT (درخت_TYPE (inside_init)),
			 TYPE_MAIN_VARIANT (type)))
	    أرجع inside_init;

	  إذا (char_array)
	    {
	      إذا (typ2 != char_type_گره && typ2 != char8_type_گره)
		incompat_string_cst = درست;
	    }
	  وإلا إذا (!comptypes (typ1, typ2))
	    incompat_string_cst = درست;

          إذا (incompat_string_cst)
            {
	      error_init (init_loc, "cannot initialize array of %qT from "
			  "a string literal with type array of %qT",
			  typ1, typ2);
	      أرجع error_mark_گره;
            }

	  إذا (require_constexpr
	      && TYPE_UNSIGNED (typ1) != TYPE_UNSIGNED (typ2))
	    {
	      /* Check if all characters of the string can be
		 represented in the type of the constexpr object being
		 initialized.  */
	      بیعلامت HOST_WIDE_INT len = درخت_STRING_درازی (inside_init);
	      ثابت بیعلامت حرف *p =
		(ثابت بیعلامت حرف *) درخت_STRING_اشاره_گر (inside_init);
	      gcc_assert (CHAR_TYPE_اندازه == 8 && CHAR_بیت == 8);
	      لكل (بیعلامت i = 0; i < len; i++)
		إذا (p[i] > 127)
		  {
		    error_init (init_loc, "%<constexpr%> initializer not "
				"representable in type of object");
		    اكسر;
		  }
	    }

	  إذا (TYPE_DOMAIN (type) != NULL_درخت
	      && TYPE_اندازه (type) != NULL_درخت
	      && درخت_کد (TYPE_اندازه (type)) == INTEGER_CST)
	    {
	      بیعلامت HOST_WIDE_INT len = درخت_STRING_درازی (inside_init);

	      إذا (compare_درخت_int (TYPE_اندازه_UNIT (type), len) < 0)
		{
		  بیعلامت HOST_WIDE_INT avail
		    = درخت_مقصد_uhwi (TYPE_اندازه_UNIT (type));
		  بیعلامت unit = TYPE_PRECISION (typ1) / بیتها_در_هر_UNIT;
		  ثابت حرف *p = درخت_STRING_اشاره_گر (inside_init);

		  /* Construct truncated string.  */
		  inside_init = build_string (avail, p);

		  /* Subtract the size of a single (possibly wide) character
		     because it may be ok to ignore the terminating NUL char
		     that is counted in the length of the constant.  */
		  إذا (len - unit > avail)
		    pedwarn_init (init_loc, 0,
				  "initializer-string for array of %qT "
				  "is too long (%wu chars into %wu "
				  "available)", typ1, len, avail);
		  وإلا إذا (warn_cxx_compat)
		    warning_at (init_loc, OPT_Wc___compat,
				"initializer-string for array of %qT "
				"is too long for C++ (%wu chars into %wu "
				"available)", typ1, len, avail);
		  وإلا إذا (warn_unterminated_string_initialization
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
	  أرجع inside_init;
	}
      وإلا إذا (INTEGRAL_TYPE_P (typ1))
	{
	  error_init (init_loc, "array of inappropriate type initialized "
		      "from string constant");
	  أرجع error_mark_گره;
	}
    }

  /* Build a VECTOR_CST from a *constant* vector constructor.  If the
     vector constructor is not constant (e.g. {1,2,3,foo()}) then punt
     below and handle as a constructor.  */
  إذا (کد == وکتور_TYPE
      && وکتور_TYPE_P (درخت_TYPE (inside_init))
      && وکتور_types_convertible_p (درخت_TYPE (inside_init), type, درست)
      && درخت_CONSTANT (inside_init))
    {
      إذا (درخت_کد (inside_init) == وکتور_CST
	  && comptypes (TYPE_MAIN_VARIANT (درخت_TYPE (inside_init)),
			TYPE_MAIN_VARIANT (type)))
	أرجع inside_init;

      إذا (درخت_کد (inside_init) == CONSTRUCTOR)
	{
	  بیعلامت HOST_WIDE_INT ix;
	  درخت مقدار;
	  منطقي constant_p = درست;

	  /* Iterate through elements and check if all constructor
	     elements are *_CSTs.  */
	  FOR_EACH_CONSTRUCTOR_مقدار (CONSTRUCTOR_ELTS (inside_init), ix, مقدار)
	    إذا (!CONSTANT_CLASS_P (مقدار))
	      {
		constant_p = خطأ;
		اكسر;
	      }

	  إذا (constant_p)
	    أرجع build_وکتور_from_ctor (type,
					   CONSTRUCTOR_ELTS (inside_init));
	}
    }

  إذا (warn_sequence_نقطه)
    verify_sequence_points (inside_init);

  /* Any type can be initialized
     from an expression of the same type, optionally with braces.  */

  إذا (inside_init && درخت_TYPE (inside_init) != NULL_درخت
      && (comptypes (TYPE_MAIN_VARIANT (درخت_TYPE (inside_init)),
		     TYPE_MAIN_VARIANT (type))
	  || (کد == ARRAY_TYPE
	      && comptypes (درخت_TYPE (inside_init), type))
	  || (gnu_وکتور_type_p (type)
	      && comptypes (درخت_TYPE (inside_init), type))
	  || (کد == اشاره_گر_TYPE
	      && درخت_کد (درخت_TYPE (inside_init)) == ARRAY_TYPE
	      && comptypes (درخت_TYPE (درخت_TYPE (inside_init)),
			    درخت_TYPE (type)))))
    {
      إذا (کد == اشاره_گر_TYPE)
	{
	  إذا (درخت_کد (درخت_TYPE (inside_init)) == ARRAY_TYPE)
	    {
	      إذا (درخت_کد (inside_init) == STRING_CST
		  || درخت_کد (inside_init) == COMPOUND_LITERAL_عبارت)
		inside_init = array_مقصد_اشاره_گر_conversion
		  (init_loc, inside_init);
	      وإلا
		{
		  error_init (init_loc, "invalid use of non-lvalue array");
		  أرجع error_mark_گره;
		}
	    }
	}

      إذا (کد == وکتور_TYPE || c_hardbool_type_attr (type))
	/* Although the types are compatible, we may require a
	   conversion.  */
	inside_init = convert (type, inside_init);

      إذا ((کد == رکورد_TYPE || کد == UNION_TYPE)
	  && !comptypes (TYPE_MAIN_VARIANT (type), TYPE_MAIN_VARIANT (درخت_TYPE (inside_init))))
	{
	  error_init (init_loc, "invalid initializer");
	  أرجع error_mark_گره;
	}

      إذا (require_constant
	  && درخت_کد (inside_init) == COMPOUND_LITERAL_عبارت)
	{
	  /* As an extension, allow initializing objects with static storage
	     duration with compound literals (which are then treated just as
	     the brace enclosed list they contain).  Also allow this for
	     vectors, as we can only assign them with compound literals.  */
	  إذا (flag_isoc99 && کد != وکتور_TYPE)
	    pedwarn_init (init_loc, OPT_Wpedantic, "initializer element "
			  "is not constant");
	  درخت decl = COMPOUND_LITERAL_عبارت_DECL (inside_init);
	  inside_init = DECL_INITIAL (decl);
	}

      إذا (کد == ARRAY_TYPE && درخت_کد (inside_init) != STRING_CST
	  && درخت_کد (inside_init) != CONSTRUCTOR)
	{
	  error_init (init_loc, "array initialized from non-constant array "
		      "expression");
	  أرجع error_mark_گره;
	}

      /* Compound expressions can only occur here if -Wpedantic or
	 -pedantic-errors is specified.  In the later case, we always want
	 an error.  In the former case, we simply want a warning.  */
      إذا (require_constant && pedantic
	  && درخت_کد (inside_init) == COMPOUND_عبارت)
	{
	  inside_init
	    = valid_compound_عبارت_initializer (inside_init,
					       درخت_TYPE (inside_init));
	  إذا (inside_init == error_mark_گره)
	    error_init (init_loc, "initializer element is not constant");
	  وإلا
	    pedwarn_init (init_loc, OPT_Wpedantic,
			  "initializer element is not constant");
	  إذا (flag_pedantic_errors)
	    inside_init = error_mark_گره;
	}
      وإلا إذا (require_constant
	       && !initializer_constant_valid_p (inside_init,
						 درخت_TYPE (inside_init)))
	{
	  error_init (init_loc, "initializer element is not constant");
	  inside_init = error_mark_گره;
	}
      وإلا إذا (require_constant && !maybe_const)
	pedwarn_init (init_loc, OPT_Wpedantic,
		      "initializer element is not a constant expression");
      وإلا إذا (require_constexpr)
	check_constexpr_init (init_loc, type, inside_init,
			      int_const_عبارت, arith_const_عبارت);

      /* Added to enable additional -Wsuggest-attribute=format warnings.  */
      إذا (درخت_کد (درخت_TYPE (inside_init)) == اشاره_گر_TYPE)
	inside_init = convert_for_assignment (init_loc, UNKNOWN_LOCATION,
					      type, inside_init, origtype,
					      (require_constant
					       ? ic_init_const
					       : ic_init), null_اشاره_گر_constant,
					      NULL_درخت, NULL_درخت, 0);
      إذا (درخت_کد (inside_init) == RAW_داده_CST
	  && c_inhibit_evaluation_warnings == 0
	  && warn_conversion
	  && !TYPE_UNSIGNED (type)
	  && TYPE_PRECISION (type) == CHAR_بیت)
	لكل (بیعلامت صحيح i = 0;
	     i < (بیعلامت) RAW_داده_درازی (inside_init); ++i)
	  إذا (RAW_داده_SCHAR_ELT (inside_init, i) < 0)
	    warning_at (init_loc, OPT_Wconversion,
			"conversion from %qT to %qT changes value from "
			"%qd to %qd",
			integer_type_گره, type,
			RAW_داده_UCHAR_ELT (inside_init, i),
			RAW_داده_SCHAR_ELT (inside_init, i));
      أرجع inside_init;
    }

  /* Handle scalar types, including conversions.  */

  إذا (کد == INTEGER_TYPE || کد == REAL_TYPE || کد == FIXED_نقطه_TYPE
      || کد == اشاره_گر_TYPE || کد == ENUMERAL_TYPE || کد == BOOLEAN_TYPE
      || کد == COMPLEX_TYPE || کد == وکتور_TYPE || کد == NULLPTR_TYPE
      || کد == BITINT_TYPE)
    {
      درخت unconverted_init = inside_init;
      إذا (درخت_کد (درخت_TYPE (init)) == ARRAY_TYPE
	  && (درخت_کد (init) == STRING_CST
	      || درخت_کد (init) == COMPOUND_LITERAL_عبارت))
	inside_init = init = array_مقصد_اشاره_گر_conversion (init_loc, init);
      إذا (semantic_type)
	inside_init = build1 (EXCESS_PRECISION_عبارت, semantic_type,
			      inside_init);
      inside_init
	= convert_for_assignment (init_loc, UNKNOWN_LOCATION, type,
				  inside_init, origtype,
				  require_constant ? ic_init_const : ic_init,
				  null_اشاره_گر_constant, NULL_درخت, NULL_درخت,
				  0);

      /* Check to see if we have already given an error message.  */
      إذا (inside_init == error_mark_گره)
	;
      وإلا إذا (require_constant && !درخت_CONSTANT (inside_init))
	{
	  error_init (init_loc, "initializer element is not constant");
	  inside_init = error_mark_گره;
	}
      وإلا إذا (require_constant
	       && !initializer_constant_valid_p (inside_init,
						 درخت_TYPE (inside_init)))
	{
	  error_init (init_loc, "initializer element is not computable at "
		      "load time");
	  inside_init = error_mark_گره;
	}
      وإلا إذا (require_constant && !maybe_const)
	pedwarn_init (init_loc, OPT_Wpedantic,
		      "initializer element is not a constant expression");
      وإلا إذا (require_constexpr)
	check_constexpr_init (init_loc, type, unconverted_init,
			      int_const_عبارت, arith_const_عبارت);

      أرجع inside_init;
    }

  /* Come here only for records and arrays.  */

  إذا (COMPLETE_TYPE_P (type) && درخت_کد (TYPE_اندازه (type)) != INTEGER_CST)
    {
      error_init (init_loc,
		  "variable-sized object may not be initialized except "
		  "with an empty initializer");
      أرجع error_mark_گره;
    }

  error_init (init_loc, "invalid initializer");
  أرجع error_mark_گره;
}

/* Handle initializers that use braces.  */

/* Type of object we are accumulating a constructor for.
   This type is always a RECORD_TYPE, UNION_TYPE or ARRAY_TYPE.  */
ساكن درخت constructor_type;

/* For a RECORD_TYPE or UNION_TYPE, this is the chain of fields
   left to fill.  */
ساكن درخت constructor_fields;

/* For an ARRAY_TYPE, this is the specified index
   at which to store the next element we get.  */
ساكن درخت constructor_شاخص;

/* For an ARRAY_TYPE, this is the maximum index.  */
ساكن درخت constructor_max_شاخص;

/* For a RECORD_TYPE, this is the first field not yet written out.  */
ساكن درخت constructor_unfilled_fields;

/* For an ARRAY_TYPE, this is the index of the first element
   not yet written out.  */
ساكن درخت constructor_unfilled_شاخص;

/* In a RECORD_TYPE, the byte index of the next consecutive field.
   This is so we can generate gaps between fields, when appropriate.  */
ساكن درخت constructor_بیت_شاخص;

/* If we are saving up the elements rather than allocating them,
   this is the list of elements so far (in reverse order,
   most recent first).  */
ساكن vec<constructor_elt, va_gc> *constructor_elements;

/* 1 if constructor should be incrementally stored into a constructor chain,
   0 if all the elements should be kept in AVL tree.  */
ساكن صحيح constructor_incremental;

/* 1 if so far this constructor's elements are all compile-time constants.  */
ساكن صحيح constructor_constant;

/* 1 if so far this constructor's elements are all valid address constants.  */
ساكن صحيح constructor_simple;

/* 1 if this constructor has an element that cannot be part of a
   constant expression.  */
ساكن صحيح constructor_nonconst;

/* 1 if this constructor is erroneous so far.  */
ساكن صحيح constructor_erroneous;

/* 1 if this constructor is the universal zero initializer { 0 }.  */
ساكن صحيح constructor_zeroinit;

/* 1 if this constructor should have padding bits zeroed (C23 {}.  */
ساكن منطقي constructor_zero_padding_بیتها;

/* 1 if this constructor is a braced scalar initializer (further nested levels
   of braces are an error).  */
ساكن منطقي constructor_braced_scalar;

/* Structure for managing pending initializer elements, organized as an
   AVL tree.  */

بنية init_گره
{
  بنية init_گره *چپ, *راست;
  بنية init_گره *والد;
  صحيح balance;
  درخت purpose;
  درخت مقدار;
  درخت origtype;
};

/* Tree of pending elements at this constructor level.
   These are elements encountered out of order
   which belong at places we haven't reached yet in actually
   writing the output.
   Will never hold tree nodes across GC runs.  */
ساكن بنية init_گره *constructor_pending_elts;

/* The SPELLING_DEPTH of this constructor.  */
ساكن صحيح constructor_عمق;

/* DECL node for which an initializer is being read.
   0 means we are reading a constructor expression
   such as (struct foo) {...}.  */
ساكن درخت constructor_decl;

/* Nonzero if there were any member designators in this initializer.  */
ساكن صحيح constructor_designated;

/* Nesting depth of designator list.  */
ساكن صحيح designator_عمق;

/* Nonzero if there were diagnosed errors in this designator list.  */
ساكن صحيح designator_erroneous;


/* This stack has a level for each implicit or explicit level of
   structuring in the initializer, including the outermost one.  It
   saves the values of most of the variables above.  */

بنية constructor_range_پشته;

بنية constructor_پشته
{
  بنية constructor_پشته *بعدی;
  درخت type;
  درخت fields;
  درخت شاخص;
  درخت max_شاخص;
  درخت unfilled_شاخص;
  درخت unfilled_fields;
  درخت بیت_شاخص;
  vec<constructor_elt, va_gc> *elements;
  بنية init_گره *pending_elts;
  صحيح جابه_جایی;
  صحيح عمق;
  /* If value nonzero, this value should replace the entire
     constructor at this level.  */
  بنية c_عبارت replacement_مقدار;
  بنية constructor_range_پشته *range_پشته;
  حرف constant;
  حرف simple;
  حرف nonconst;
  حرف implicit;
  حرف erroneous;
  حرف outer;
  حرف incremental;
  حرف designated;
  منطقي zero_padding_بیتها;
  منطقي braced_scalar;
  صحيح designator_عمق;
};

ساكن بنية constructor_پشته *constructor_پشته;

/* This stack represents designators from some range designator up to
   the last designator in the list.  */

بنية constructor_range_پشته
{
  بنية constructor_range_پشته *بعدی, *prev;
  بنية constructor_پشته *پشته;
  درخت range_شروع;
  درخت شاخص;
  درخت range_انتها;
  درخت fields;
};

ساكن بنية constructor_range_پشته *constructor_range_پشته;

/* This stack records separate initializers that are nested.
   Nested initializers can't happen in ANSI C, but GNU C allows them
   in cases like { ... (struct foo) { ... } ... }.  */

بنية initializer_پشته
{
  بنية initializer_پشته *بعدی;
  درخت decl;
  بنية constructor_پشته *constructor_پشته;
  بنية constructor_range_پشته *constructor_range_پشته;
  vec<constructor_elt, va_gc> *elements;
  بنية spelling *spelling;
  بنية spelling *spelling_پایه;
  صحيح spelling_اندازه;
  حرف require_constant_مقدار;
  حرف require_constant_elements;
  حرف require_constexpr_مقدار;
  حرف designated;
  rich_location *missing_brace_richloc;
};

ساكن بنية initializer_پشته *initializer_پشته;

/* Prepare to parse and output the initializer for variable DECL.  */

فراغ
شروع_init (درخت decl, درخت asmspec_درخت ATTRIBUTE_استفادهنشده,
	    منطقي init_require_constant, منطقي init_require_constexpr,
	    rich_location *richloc)
{
  ثابت حرف *locus;
  بنية initializer_پشته *p = XNEW (بنية initializer_پشته);

  p->decl = constructor_decl;
  p->require_constant_مقدار = require_constant_مقدار;
  p->require_constant_elements = require_constant_elements;
  p->require_constexpr_مقدار = require_constexpr_مقدار;
  p->constructor_پشته = constructor_پشته;
  p->constructor_range_پشته = constructor_range_پشته;
  p->elements = constructor_elements;
  p->spelling = spelling;
  p->spelling_پایه = spelling_پایه;
  p->spelling_اندازه = spelling_اندازه;
  p->بعدی = initializer_پشته;
  p->missing_brace_richloc = richloc;
  p->designated = constructor_designated;
  initializer_پشته = p;

  constructor_decl = decl;
  constructor_designated = 0;

  require_constant_مقدار = init_require_constant;
  require_constexpr_مقدار = init_require_constexpr;
  إذا (decl != NULL_درخت && decl != error_mark_گره)
    {
      require_constant_elements
	= ((init_require_constant || (pedantic && !flag_isoc99))
	   /* For a scalar, you can always use any value to initialize,
	      even within braces.  */
	   && AGGREGATE_TYPE_P (درخت_TYPE (decl)));
      locus = identifier_مقصد_locale (IDENTIFIER_اشاره_گر (DECL_NAME (decl)));
    }
  وإلا
    {
      require_constant_elements = خطأ;
      locus = _("(anonymous)");
    }

  constructor_پشته = 0;
  constructor_range_پشته = 0;

  یافت_missing_braces = 0;

  spelling_پایه = 0;
  spelling_اندازه = 0;
  RESTORE_SPELLING_عمق (0);

  إذا (locus)
    افزودن_string (locus);
}

فراغ
پایان_init (فراغ)
{
  بنية initializer_پشته *p = initializer_پشته;

  /* Free the whole constructor stack of this initializer.  */
  طالما (constructor_پشته)
    {
      بنية constructor_پشته *q = constructor_پشته;
      constructor_پشته = q->بعدی;
      XDELETE (q);
    }

  gcc_assert (!constructor_range_پشته);

  /* Pop back to the data of the outer initializer (if any).  */
  XDELETE (spelling_پایه);

  constructor_decl = p->decl;
  require_constant_مقدار = p->require_constant_مقدار;
  require_constant_elements = p->require_constant_elements;
  require_constexpr_مقدار = p->require_constexpr_مقدار;
  constructor_پشته = p->constructor_پشته;
  constructor_designated = p->designated;
  constructor_range_پشته = p->constructor_range_پشته;
  constructor_elements = p->elements;
  spelling = p->spelling;
  spelling_پایه = p->spelling_پایه;
  spelling_اندازه = p->spelling_اندازه;
  initializer_پشته = p->بعدی;
  XDELETE (p);
}

/* Call here when we see the initializer is surrounded by braces.
   This is instead of a call to push_init_level;
   it is matched by a call to pop_init_level.

   TYPE is the type to initialize, for a constructor expression.
   For an initializer for a decl, TYPE is zero.  */

فراغ
really_شروع_incremental_init (درخت type)
{
  بنية constructor_پشته *p = XNEW (بنية constructor_پشته);

  إذا (type == NULL_درخت)
    type = درخت_TYPE (constructor_decl);

  إذا (وکتور_TYPE_P (type)
      && TYPE_وکتور_OPAQUE (type))
    error ("opaque vector types cannot be initialized");

  p->type = constructor_type;
  p->fields = constructor_fields;
  p->شاخص = constructor_شاخص;
  p->max_شاخص = constructor_max_شاخص;
  p->unfilled_شاخص = constructor_unfilled_شاخص;
  p->unfilled_fields = constructor_unfilled_fields;
  p->بیت_شاخص = constructor_بیت_شاخص;
  p->elements = constructor_elements;
  p->constant = constructor_constant;
  p->simple = constructor_simple;
  p->nonconst = constructor_nonconst;
  p->erroneous = constructor_erroneous;
  p->pending_elts = constructor_pending_elts;
  p->عمق = constructor_عمق;
  p->replacement_مقدار.مقدار = 0;
  p->replacement_مقدار.original_کد = ERROR_MARK;
  p->replacement_مقدار.original_type = عدم;
  p->implicit = 0;
  p->range_پشته = 0;
  p->outer = 0;
  p->incremental = constructor_incremental;
  p->designated = constructor_designated;
  p->zero_padding_بیتها = constructor_zero_padding_بیتها;
  p->braced_scalar = constructor_braced_scalar;
  p->designator_عمق = designator_عمق;
  p->بعدی = 0;
  constructor_پشته = p;

  constructor_constant = 1;
  constructor_simple = 1;
  constructor_nonconst = 0;
  constructor_عمق = SPELLING_عمق ();
  constructor_elements = عدم;
  constructor_pending_elts = 0;
  constructor_type = type;
  constructor_incremental = 1;
  constructor_designated = 0;
  constructor_zero_padding_بیتها = خطأ;
  constructor_zeroinit = 1;
  constructor_braced_scalar = خطأ;
  designator_عمق = 0;
  designator_erroneous = 0;

  إذا (رکورد_OR_UNION_TYPE_P (constructor_type))
    {
      constructor_fields = TYPE_FIELDS (constructor_type);
      /* Skip any nameless bit fields at the beginning.  */
      طالما (constructor_fields != NULL_درخت
	     && DECL_UNNAMED_بیت_فیلد (constructor_fields))
	constructor_fields = DECL_CHAIN (constructor_fields);

      constructor_unfilled_fields = constructor_fields;
      constructor_بیت_شاخص = bitsize_zero_گره;
    }
  وإلا إذا (درخت_کد (constructor_type) == ARRAY_TYPE)
    {
      إذا (TYPE_DOMAIN (constructor_type))
	{
	  constructor_max_شاخص
	    = TYPE_MAX_مقدار (TYPE_DOMAIN (constructor_type));

	  /* Detect non-empty initializations of zero-length arrays.  */
	  إذا (constructor_max_شاخص == NULL_درخت
	      && TYPE_اندازه (constructor_type))
	    constructor_max_شاخص = integer_minus_one_گره;

	  /* constructor_max_index needs to be an INTEGER_CST.  Attempts
	     to initialize VLAs with a nonempty initializer will cause a
	     proper error; avoid tree checking errors as well by setting a
	     safe value.  */
	  إذا (constructor_max_شاخص
	      && درخت_کد (constructor_max_شاخص) != INTEGER_CST)
	    constructor_max_شاخص = integer_minus_one_گره;

	  constructor_شاخص
	    = convert (bitsizetype,
		       TYPE_MIN_مقدار (TYPE_DOMAIN (constructor_type)));
	}
      وإلا
	{
	  constructor_شاخص = bitsize_zero_گره;
	  constructor_max_شاخص = NULL_درخت;
	}

      constructor_unfilled_شاخص = constructor_شاخص;
    }
  وإلا إذا (gnu_وکتور_type_p (constructor_type))
    {
      /* Vectors are like simple fixed-size arrays.  */
      constructor_max_شاخص =
	bitsize_int (TYPE_وکتور_SUBPARTS (constructor_type) - 1);
      constructor_شاخص = bitsize_zero_گره;
      constructor_unfilled_شاخص = constructor_شاخص;
    }
  وإلا
    {
      /* Handle the case of int x = {5}; */
      constructor_fields = constructor_type;
      constructor_unfilled_fields = constructor_type;
      constructor_braced_scalar = درست;
    }
}

خارجي location_t آخرین_init_list_comma;

/* Called when we see an open brace for a nested initializer.  Finish
   off any pending levels with implicit braces.  */
فراغ
پایان_implicit_inits (location_t loc, بنية obstack *braced_init_obstack)
{
  طالما (constructor_پشته->implicit)
    {
      إذا (رکورد_OR_UNION_TYPE_P (constructor_type)
	  && constructor_fields == NULL_درخت)
	process_init_element (درون_داد_location,
			      برداشت_init_level (loc, 1, braced_init_obstack,
					      آخرین_init_list_comma),
			      درست, braced_init_obstack);
      وإلا إذا (درخت_کد (constructor_type) == ARRAY_TYPE
	       && constructor_max_شاخص
	       && درخت_int_cst_lt (constructor_max_شاخص,
				   constructor_شاخص))
	process_init_element (درون_داد_location,
			      برداشت_init_level (loc, 1, braced_init_obstack,
					      آخرین_init_list_comma),
			      درست, braced_init_obstack);
      وإلا
	اكسر;
    }
}

/* Push down into a subobject, for initialization.
   If this is for an explicit set of braces, IMPLICIT is 0.
   If it is because the next element belongs at a lower level,
   IMPLICIT is 1 (or 2 if the push is because of designator list).  */

فراغ
افزودن_init_level (location_t loc, صحيح implicit,
		 بنية obstack *braced_init_obstack)
{
  بنية constructor_پشته *p;
  درخت مقدار = NULL_درخت;

  /* Unless this is an explicit brace, we need to preserve previous
     content if any.  */
  إذا (implicit)
    {
      إذا (رکورد_OR_UNION_TYPE_P (constructor_type) && constructor_fields)
	مقدار = پیدا_کن_init_member (constructor_fields, braced_init_obstack);
      وإلا إذا (درخت_کد (constructor_type) == ARRAY_TYPE)
	مقدار = پیدا_کن_init_member (constructor_شاخص, braced_init_obstack);
    }

  p = XNEW (بنية constructor_پشته);
  p->type = constructor_type;
  p->fields = constructor_fields;
  p->شاخص = constructor_شاخص;
  p->max_شاخص = constructor_max_شاخص;
  p->unfilled_شاخص = constructor_unfilled_شاخص;
  p->unfilled_fields = constructor_unfilled_fields;
  p->بیت_شاخص = constructor_بیت_شاخص;
  p->elements = constructor_elements;
  p->constant = constructor_constant;
  p->simple = constructor_simple;
  p->nonconst = constructor_nonconst;
  p->erroneous = constructor_erroneous;
  p->pending_elts = constructor_pending_elts;
  p->عمق = constructor_عمق;
  p->replacement_مقدار.مقدار = NULL_درخت;
  p->replacement_مقدار.original_کد = ERROR_MARK;
  p->replacement_مقدار.original_type = عدم;
  p->implicit = implicit;
  p->outer = 0;
  p->incremental = constructor_incremental;
  p->designated = constructor_designated;
  p->zero_padding_بیتها = constructor_zero_padding_بیتها;
  p->braced_scalar = constructor_braced_scalar;
  p->designator_عمق = designator_عمق;
  p->بعدی = constructor_پشته;
  p->range_پشته = 0;
  constructor_پشته = p;

  constructor_constant = 1;
  constructor_simple = 1;
  constructor_nonconst = 0;
  constructor_عمق = SPELLING_عمق ();
  constructor_elements = عدم;
  constructor_incremental = 1;
  /* If the upper initializer is designated, then mark this as
     designated too to prevent bogus warnings.  */
  constructor_designated = p->designated;
  /* If the upper initializer has padding bits zeroed, that includes
     all nested initializers as well.  */
  constructor_zero_padding_بیتها = p->zero_padding_بیتها;
  constructor_braced_scalar = خطأ;
  constructor_pending_elts = 0;
  إذا (!implicit)
    {
      p->range_پشته = constructor_range_پشته;
      constructor_range_پشته = 0;
      designator_عمق = 0;
      designator_erroneous = 0;
    }

  /* Don't die if an entire brace-pair level is superfluous
     in the containing level.  */
  إذا (constructor_type == NULL_درخت)
    ;
  وإلا إذا (رکورد_OR_UNION_TYPE_P (constructor_type))
    {
      /* Don't die if there are extra init elts at the end.  */
      إذا (constructor_fields == NULL_درخت)
	constructor_type = NULL_درخت;
      وإلا
	{
	  constructor_type = درخت_TYPE (constructor_fields);
	  افزودن_member_name (constructor_fields);
	  constructor_عمق++;
	}
    }
  وإلا إذا (درخت_کد (constructor_type) == ARRAY_TYPE)
    {
      constructor_type = درخت_TYPE (constructor_type);
      افزودن_array_bounds (درخت_مقصد_uhwi (constructor_شاخص));
      constructor_عمق++;
    }

  إذا (constructor_type == NULL_درخت)
    {
      error_init (loc, "extra brace group at end of initializer");
      constructor_fields = NULL_درخت;
      constructor_unfilled_fields = NULL_درخت;
      أرجع;
    }

  إذا (مقدار && درخت_کد (مقدار) == CONSTRUCTOR)
    {
      constructor_constant = درخت_CONSTANT (مقدار);
      constructor_simple = درخت_STATIC (مقدار);
      constructor_nonconst = CONSTRUCTOR_NON_CONST (مقدار);
      constructor_elements = CONSTRUCTOR_ELTS (مقدار);
      constructor_zero_padding_بیتها |= CONSTRUCTOR_ZERO_PADDING_بیتها (مقدار);
      إذا (!vec_امن_is_خالی (constructor_elements)
	  && (درخت_کد (constructor_type) == رکورد_TYPE
	      || درخت_کد (constructor_type) == ARRAY_TYPE))
	مجموعه_nonincremental_init (braced_init_obstack);
    }

  إذا (implicit == 1)
    {
      یافت_missing_braces = 1;
      إذا (initializer_پشته->missing_brace_richloc)
	initializer_پشته->missing_brace_richloc->جمع_کن_fixit_درج_before
	  (loc, "{");
    }

  إذا (رکورد_OR_UNION_TYPE_P (constructor_type))
    {
      constructor_fields = TYPE_FIELDS (constructor_type);
      /* Skip any nameless bit fields at the beginning.  */
      طالما (constructor_fields != NULL_درخت
	     && DECL_UNNAMED_بیت_فیلد (constructor_fields))
	constructor_fields = DECL_CHAIN (constructor_fields);

      constructor_unfilled_fields = constructor_fields;
      constructor_بیت_شاخص = bitsize_zero_گره;
    }
  وإلا إذا (gnu_وکتور_type_p (constructor_type))
    {
      /* Vectors are like simple fixed-size arrays.  */
      constructor_max_شاخص =
	bitsize_int (TYPE_وکتور_SUBPARTS (constructor_type) - 1);
      constructor_شاخص = bitsize_int (0);
      constructor_unfilled_شاخص = constructor_شاخص;
    }
  وإلا إذا (درخت_کد (constructor_type) == ARRAY_TYPE)
    {
      إذا (TYPE_DOMAIN (constructor_type))
	{
	  constructor_max_شاخص
	    = TYPE_MAX_مقدار (TYPE_DOMAIN (constructor_type));

	  /* Detect non-empty initializations of zero-length arrays.  */
	  إذا (constructor_max_شاخص == NULL_درخت
	      && TYPE_اندازه (constructor_type))
	    constructor_max_شاخص = integer_minus_one_گره;

	  /* constructor_max_index needs to be an INTEGER_CST.  Attempts
	     to initialize VLAs will cause a proper error; avoid tree
	     checking errors as well by setting a safe value.  */
	  إذا (constructor_max_شاخص
	      && درخت_کد (constructor_max_شاخص) != INTEGER_CST)
	    constructor_max_شاخص = integer_minus_one_گره;

	  constructor_شاخص
	    = convert (bitsizetype,
		       TYPE_MIN_مقدار (TYPE_DOMAIN (constructor_type)));
	}
      وإلا
	constructor_شاخص = bitsize_zero_گره;

      constructor_unfilled_شاخص = constructor_شاخص;
      إذا (مقدار && درخت_کد (مقدار) == STRING_CST)
	{
	  /* We need to split the char/wchar array into individual
	     characters, so that we don't have to special case it
	     everywhere.  */
	  مجموعه_nonincremental_init_from_string (مقدار, braced_init_obstack);
	}
    }
  وإلا
    {
      إذا (constructor_type != error_mark_گره)
	{
	  إذا (p->braced_scalar)
	    permerror_init (درون_داد_location, 0,
			    "braces around scalar initializer");
	  وإلا
	    warning_init (درون_داد_location, 0,
			  "braces around scalar initializer");
	  constructor_braced_scalar = درست;
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

بنية c_عبارت
برداشت_init_level (location_t loc, صحيح implicit,
		بنية obstack *braced_init_obstack,
		location_t درج_before)
{
  بنية constructor_پشته *p;
  بنية c_عبارت ret;
  ret.مقدار = NULL_درخت;
  ret.original_کد = ERROR_MARK;
  ret.original_type = عدم;
  ret.m_decimal = 0;

  إذا (implicit == 0)
    {
      /* When we come to an explicit close brace,
	 pop any inner levels that didn't have explicit braces.  */
      طالما (constructor_پشته->implicit)
	process_init_element (درون_داد_location,
			      برداشت_init_level (loc, 1, braced_init_obstack,
					      درج_before),
			      درست, braced_init_obstack);
      gcc_assert (!constructor_range_پشته);
    }
  وإلا
    إذا (initializer_پشته->missing_brace_richloc)
      initializer_پشته->missing_brace_richloc->جمع_کن_fixit_درج_before
	(درج_before, "}");

  /* Now output all pending elements.  */
  constructor_incremental = 1;
  output_pending_init_elements (1, braced_init_obstack);

  p = constructor_پشته;

  /* Error for initializing a flexible array member.  */
  إذا (constructor_type && constructor_fields
      && flexible_array_member_type_p (constructor_type))
    {
      /* Silently discard empty initializations.  The parser will
	 already have pedwarned for empty brackets for C17 and earlier.  */
      إذا (integer_zerop (constructor_unfilled_شاخص))
	constructor_type = NULL_درخت;
      إذا (constructor_type || flag_isoc23)
	{
	  gcc_assert (!constructor_type || !TYPE_اندازه (constructor_type));

	  إذا (constructor_عمق <= 2)
	    pedwarn_init (loc, OPT_Wpedantic,
			  "initialization of a flexible array member");
	  وإلا إذا (constructor_type)
	    error_init (loc, "initialization of flexible array member "
			     "in a nested context");
	  وإلا
	    pedwarn_init (loc, OPT_Wpedantic,
			  "initialization of flexible array member "
			  "in a nested context");

	  /* We have already issued an error message for the existence
	     of a flexible array member not at the end of the structure.
	     Discard the initializer so that we do not die later.  */
	  إذا (constructor_type
	      && DECL_CHAIN (constructor_fields) != NULL_درخت
	      && (!p->type || درخت_کد (p->type) != UNION_TYPE))
	    constructor_type = NULL_درخت;
	}
    }

  بدل (vec_امن_درازی (constructor_elements))
    {
    حالة 0:
      /* Initialization with { } counts as zeroinit.  */
      constructor_zeroinit = 1;
      اكسر;
    حالة 1:
      /* This might be zeroinit as well.  */
      إذا (integer_zerop ((*constructor_elements)[0].مقدار))
	constructor_zeroinit = 1;
      اكسر;
    افتراضي:
      /* If the constructor has more than one element, it can't be { 0 }.  */
      constructor_zeroinit = 0;
      اكسر;
    }

  /* Warn when some structs are initialized with direct aggregation.  */
  إذا (!implicit && یافت_missing_braces && warn_missing_braces
      && !constructor_zeroinit)
    {
      gcc_assert (initializer_پشته->missing_brace_richloc);
      warning_at (initializer_پشته->missing_brace_richloc,
		  OPT_Wmissing_braces,
		  "missing braces around initializer");
    }

  /* Warn when some struct elements are implicitly initialized to zero.  */
  إذا (warn_missing_فیلد_initializers
      && constructor_type
      && درخت_کد (constructor_type) == رکورد_TYPE
      && constructor_unfilled_fields)
    {
	/* Do not warn for flexible array members or zero-length arrays.  */
	طالما (constructor_unfilled_fields
	       && (!DECL_اندازه (constructor_unfilled_fields)
		   || integer_zerop (DECL_اندازه (constructor_unfilled_fields))))
	  constructor_unfilled_fields = DECL_CHAIN (constructor_unfilled_fields);

	إذا (constructor_unfilled_fields
	    /* Do not warn if this level of the initializer uses member
	       designators; it is likely to be deliberate.  */
	    && !constructor_designated
	    /* Do not warn about initializing with { 0 } or with { }.  */
	    && !constructor_zeroinit)
	  {
	    إذا (warning_at (درون_داد_location, OPT_Wmissing_فیلد_initializers,
			    "missing initializer for field %qD of %qT",
			    constructor_unfilled_fields,
			    constructor_type))
	      inform (DECL_منبع_LOCATION (constructor_unfilled_fields),
		      "%qD declared here", constructor_unfilled_fields);
	  }
    }

  /* Pad out the end of the structure.  */
  إذا (p->replacement_مقدار.مقدار)
    /* If this closes a superfluous brace pair,
       just pass out the element between them.  */
    ret = p->replacement_مقدار;
  وإلا إذا (constructor_type == NULL_درخت)
    ;
  وإلا إذا (!رکورد_OR_UNION_TYPE_P (constructor_type)
	   && درخت_کد (constructor_type) != ARRAY_TYPE
	   && !gnu_وکتور_type_p (constructor_type))
    {
      /* A nonincremental scalar initializer--just return
	 the element, after verifying there is just one.
         Empty scalar initializers are supported in C23.  */
      إذا (vec_امن_is_خالی (constructor_elements))
	{
	  إذا (constructor_erroneous || constructor_type == error_mark_گره)
	    ret.مقدار = error_mark_گره;
	  وإلا إذا (درخت_کد (constructor_type) == FUNCTION_TYPE)
	    {
	      error_init (loc, "invalid initializer");
	      ret.مقدار = error_mark_گره;
	    }
	  وإلا إذا (درخت_کد (constructor_type) == اشاره_گر_TYPE)
	    /* Ensure this is a null pointer constant in the case of a
	       'constexpr' object initialized with {}.  */
	    ret.مقدار = build_zero_cst (ptr_type_گره);
	  وإلا
	    ret.مقدار = build_zero_cst (constructor_type);
	}
      وإلا إذا (vec_امن_درازی (constructor_elements) != 1)
	{
	  error_init (loc, "extra elements in scalar initializer");
	  ret.مقدار = (*constructor_elements)[0].مقدار;
	}
      وإلا
	ret.مقدار = (*constructor_elements)[0].مقدار;
    }
  وإلا
    {
      إذا (constructor_erroneous)
	ret.مقدار = error_mark_گره;
      وإلا
	{
	  ret.مقدار = build_constructor (constructor_type,
					 constructor_elements);
	  إذا (constructor_constant)
	    درخت_CONSTANT (ret.مقدار) = 1;
	  إذا (constructor_constant && constructor_simple)
	    درخت_STATIC (ret.مقدار) = 1;
	  إذا (constructor_nonconst)
	    CONSTRUCTOR_NON_CONST (ret.مقدار) = 1;
	  إذا (constructor_zero_padding_بیتها)
	    CONSTRUCTOR_ZERO_PADDING_بیتها (ret.مقدار) = 1;
	}
    }

  إذا (ret.مقدار && درخت_کد (ret.مقدار) != CONSTRUCTOR)
    {
      إذا (constructor_nonconst)
	ret.original_کد = C_MAYBE_CONST_عبارت;
      وإلا إذا (ret.original_کد == C_MAYBE_CONST_عبارت)
	ret.original_کد = ERROR_MARK;
    }

  constructor_type = p->type;
  constructor_fields = p->fields;
  constructor_شاخص = p->شاخص;
  constructor_max_شاخص = p->max_شاخص;
  constructor_unfilled_شاخص = p->unfilled_شاخص;
  constructor_unfilled_fields = p->unfilled_fields;
  constructor_بیت_شاخص = p->بیت_شاخص;
  constructor_elements = p->elements;
  constructor_constant = p->constant;
  constructor_simple = p->simple;
  constructor_nonconst = p->nonconst;
  constructor_erroneous = p->erroneous;
  constructor_incremental = p->incremental;
  constructor_designated = p->designated;
  constructor_zero_padding_بیتها = p->zero_padding_بیتها;
  constructor_braced_scalar = p->braced_scalar;
  designator_عمق = p->designator_عمق;
  constructor_pending_elts = p->pending_elts;
  constructor_عمق = p->عمق;
  إذا (!p->implicit)
    constructor_range_پشته = p->range_پشته;
  RESTORE_SPELLING_عمق (constructor_عمق);

  constructor_پشته = p->بعدی;
  XDELETE (p);

  إذا (ret.مقدار == NULL_درخت && constructor_پشته == 0)
    ret.مقدار = error_mark_گره;
  أرجع ret;
}

/* Common handling for both array range and field name designators.
   ARRAY argument is nonzero for array ranges.  Returns false for success.  */

ساكن منطقي
مجموعه_designator (location_t loc, منطقي array,
		بنية obstack *braced_init_obstack)
{
  درخت subtype;
  تعداد درخت_کد_2 subcode;

  /* Don't die if an entire brace-pair level is superfluous
     in the containing level, or for an erroneous type.  */
  إذا (constructor_type == NULL_درخت || constructor_type == error_mark_گره)
    أرجع درست;

  /* If there were errors in this designator list already, bail out
     silently.  */
  إذا (designator_erroneous)
    أرجع درست;

  /* Likewise for an initializer for a variable-size type.  Those are
     diagnosed in the parser, except for empty initializer braces.  */
  إذا (COMPLETE_TYPE_P (constructor_type)
      && درخت_کد (TYPE_اندازه (constructor_type)) != INTEGER_CST)
    أرجع درست;

  إذا (!designator_عمق)
    {
      gcc_assert (!constructor_range_پشته);

      /* Designator list starts at the level of closest explicit
	 braces.  */
      طالما (constructor_پشته->implicit)
	process_init_element (درون_داد_location,
			      برداشت_init_level (loc, 1, braced_init_obstack,
					      آخرین_init_list_comma),
			      درست, braced_init_obstack);
      constructor_designated = 1;
      أرجع خطأ;
    }

  بدل (درخت_کد (constructor_type))
    {
    حالة  رکورد_TYPE:
    حالة  UNION_TYPE:
      subtype = درخت_TYPE (constructor_fields);
      إذا (subtype != error_mark_گره)
	subtype = TYPE_MAIN_VARIANT (subtype);
      اكسر;
    حالة ARRAY_TYPE:
      subtype = TYPE_MAIN_VARIANT (درخت_TYPE (constructor_type));
      اكسر;
    افتراضي:
      gcc_unreachable ();
    }

  subcode = درخت_کد (subtype);
  إذا (array && subcode != ARRAY_TYPE)
    {
      error_init (loc, "array index in non-array initializer");
      أرجع درست;
    }
  وإلا إذا (!array && subcode != رکورد_TYPE && subcode != UNION_TYPE)
    {
      error_init (loc, "field name not in record or union initializer");
      أرجع درست;
    }

  constructor_designated = 1;
  پایان_implicit_inits (loc, braced_init_obstack);
  افزودن_init_level (loc, 2, braced_init_obstack);
  أرجع خطأ;
}

/* If there are range designators in designator list, push a new designator
   to constructor_range_stack.  RANGE_END is end of such stack range or
   NULL_TREE if there is no range designator at this level.  */

ساكن فراغ
افزودن_range_پشته (درخت range_انتها, بنية obstack * braced_init_obstack)
{
  بنية constructor_range_پشته *p;

  p = (بنية constructor_range_پشته *)
    obstack_alloc (braced_init_obstack,
		   حجم (بنية constructor_range_پشته));
  p->prev = constructor_range_پشته;
  p->بعدی = 0;
  p->fields = constructor_fields;
  p->range_شروع = constructor_شاخص;
  p->شاخص = constructor_شاخص;
  p->پشته = constructor_پشته;
  p->range_انتها = range_انتها;
  إذا (constructor_range_پشته)
    constructor_range_پشته->بعدی = p;
  constructor_range_پشته = p;
}

/* Within an array initializer, specify the next index to be initialized.
   FIRST is that index.  If LAST is nonzero, then initialize a range
   of indices, running from FIRST through LAST.  */

فراغ
مجموعه_init_شاخص (location_t loc, درخت اولی, درخت آخرین,
		بنية obstack *braced_init_obstack)
{
  إذا (مجموعه_designator (loc, درست, braced_init_obstack))
    أرجع;

  designator_erroneous = 1;

  إذا (!INTEGRAL_TYPE_P (درخت_TYPE (اولی))
      || (آخرین && !INTEGRAL_TYPE_P (درخت_TYPE (آخرین))))
    {
      error_init (loc, "array index in initializer not of integer type");
      أرجع;
    }

  إذا (درخت_کد (اولی) != INTEGER_CST)
    {
      اولی = c_fully_fold (اولی, خطأ, عدم);
      إذا (درخت_کد (اولی) == INTEGER_CST)
	pedwarn_init (loc, OPT_Wpedantic,
		      "array index in initializer is not "
		      "an integer constant expression");
    }

  إذا (آخرین && درخت_کد (آخرین) != INTEGER_CST)
    {
      آخرین = c_fully_fold (آخرین, خطأ, عدم);
      إذا (درخت_کد (آخرین) == INTEGER_CST)
	pedwarn_init (loc, OPT_Wpedantic,
		      "array index in initializer is not "
		      "an integer constant expression");
    }

  إذا (درخت_کد (اولی) != INTEGER_CST)
    error_init (loc, "nonconstant array index in initializer");
  وإلا إذا (آخرین != NULL_درخت && درخت_کد (آخرین) != INTEGER_CST)
    error_init (loc, "nonconstant array index in initializer");
  وإلا إذا (درخت_کد (constructor_type) != ARRAY_TYPE)
    error_init (loc, "array index in non-array initializer");
  وإلا إذا (درخت_int_cst_sgn (اولی) == -1)
    error_init (loc, "array index in initializer exceeds array bounds");
  وإلا إذا (constructor_max_شاخص
	   && درخت_int_cst_lt (constructor_max_شاخص, اولی))
    error_init (loc, "array index in initializer exceeds array bounds");
  وإلا
    {
      constant_عبارت_warning (اولی);
      إذا (آخرین)
	constant_عبارت_warning (آخرین);
      constructor_شاخص = convert (bitsizetype, اولی);
      إذا (درخت_int_cst_lt (constructor_شاخص, اولی))
	{
	  constructor_شاخص = copy_گره (constructor_شاخص);
	  درخت_سرریز (constructor_شاخص) = 1;
	}

      إذا (آخرین)
	{
	  إذا (درخت_int_cst_equal (اولی, آخرین))
	    آخرین = NULL_درخت;
	  وإلا إذا (درخت_int_cst_lt (آخرین, اولی))
	    {
	      error_init (loc, "empty index range in initializer");
	      آخرین = NULL_درخت;
	    }
	  وإلا
	    {
	      آخرین = convert (bitsizetype, آخرین);
	      إذا (constructor_max_شاخص != NULL_درخت
		  && درخت_int_cst_lt (constructor_max_شاخص, آخرین))
		{
		  error_init (loc, "array index range in initializer exceeds "
			      "array bounds");
		  آخرین = NULL_درخت;
		}
	    }
	}

      designator_عمق++;
      designator_erroneous = 0;
      إذا (constructor_range_پشته || آخرین)
	افزودن_range_پشته (آخرین, braced_init_obstack);
    }
}

/* Within a struct initializer, specify the next field to be initialized.  */

فراغ
مجموعه_init_label (location_t loc, درخت fieldname, location_t fieldname_loc,
		بنية obstack *braced_init_obstack)
{
  درخت فیلد_2;

  إذا (مجموعه_designator (loc, خطأ, braced_init_obstack))
    أرجع;

  designator_erroneous = 1;

  إذا (!رکورد_OR_UNION_TYPE_P (constructor_type))
    {
      error_init (loc, "field name not in record or union initializer");
      أرجع;
    }

  فیلد_2 = lookup_فیلد (constructor_type, fieldname);

  إذا (فیلد_2 == NULL_درخت)
    {
      درخت guessed_id = lookup_فیلد_fuzzy (constructor_type, fieldname);
      إذا (guessed_id)
	{
	  gcc_rich_location rich_loc (fieldname_loc);
	  rich_loc.جمع_کن_fixit_misspelled_id (fieldname_loc, guessed_id);
	  error_at (&rich_loc,
		    "%qT has no member named %qE; did you mean %qE?",
		    constructor_type, fieldname, guessed_id);
	}
      وإلا
	error_at (fieldname_loc, "%qT has no member named %qE",
		  constructor_type, fieldname);
    }
  وإلا
    افعل
      {
	constructor_fields = درخت_مقدار (فیلد_2);
	designator_عمق++;
	designator_erroneous = 0;
	إذا (constructor_range_پشته)
	  افزودن_range_پشته (NULL_درخت, braced_init_obstack);
	فیلد_2 = درخت_CHAIN (فیلد_2);
	إذا (فیلد_2)
	  {
	    إذا (مجموعه_designator (loc, خطأ, braced_init_obstack))
	      أرجع;
	  }
      }
    طالما (فیلد_2 != NULL_درخت);
}

/* Helper function for add_pending_init.  Find inorder successor of P
   in AVL tree.  */
ساكن بنية init_گره *
init_گره_successor (بنية init_گره *p)
{
  بنية init_گره *r;
  إذا (p->راست)
    {
      r = p->راست;
      طالما (r->چپ)
	r = r->چپ;
      أرجع r;
    }
  r = p->والد;
  طالما (r && p == r->راست)
    {
      p = r;
      r = r->والد;
    }
  أرجع r;
}

/* Add a new initializer to the tree of pending initializers.  PURPOSE
   identifies the initializer, either array index or field in a structure.
   VALUE is the value of that index or field.  If ORIGTYPE is not
   NULL_TREE, it is the original type of VALUE.

   IMPLICIT is true if value comes from pop_init_level (1),
   the new initializer has been merged with the existing one
   and thus no warnings should be emitted about overriding an
   existing initializer.  */

ساكن فراغ
جمع_کن_pending_init (location_t loc, درخت purpose, درخت مقدار, درخت origtype,
		  منطقي implicit, بنية obstack *braced_init_obstack)
{
  بنية init_گره *p, **q, *r;

  q = &constructor_pending_elts;
  p = 0;

  إذا (درخت_کد (constructor_type) == ARRAY_TYPE)
    {
      طالما (*q != 0)
	{
	  p = *q;
	  إذا (درخت_int_cst_lt (purpose, p->purpose))
	    q = &p->چپ;
	  وإلا إذا (درخت_int_cst_lt (p->purpose, purpose))
	    {
	      إذا (درخت_کد (p->مقدار) != RAW_داده_CST
		  || (p->راست
		      && درخت_int_cst_le (p->راست->purpose, purpose)))
		q = &p->راست;
	      وإلا
		{
		  widest_int pp = wi::مقصد_widest (p->purpose);
		  widest_int pw = wi::مقصد_widest (purpose);
		  إذا (pp + RAW_داده_درازی (p->مقدار) <= pw)
		    q = &p->راست;
		  وإلا
		    {
		      /* Override which should split the old RAW_DATA_CST
			 into 2 or 3 pieces.  */
		      إذا (!implicit && warn_override_init)
			warning_init (loc, OPT_Woverride_init,
				      "initialized field overwritten");
		      بیعلامت HOST_WIDE_INT شروع = (pw - pp).مقصد_uhwi ();
		      بیعلامت HOST_WIDE_INT len = 1;
		      إذا (درخت_کد (مقدار) == RAW_داده_CST)
			len = RAW_داده_درازی (مقدار);
		      بیعلامت HOST_WIDE_INT انتها = 0;
		      بیعلامت plen = RAW_داده_درازی (p->مقدار);
		      gcc_checking_assert (شروع < plen && شروع);
		      إذا (plen - شروع > len)
			انتها = plen - شروع - len;
		      درخت v = p->مقدار;
		      درخت origtype = p->origtype;
		      إذا (شروع == 1)
			p->مقدار = build_int_cst (درخت_TYPE (v),
						  RAW_داده_UCHAR_ELT (v, 0));
		      وإلا
			{
			  p->مقدار = v;
			  إذا (انتها > 1)
			    v = copy_گره (v);
			  RAW_داده_درازی (p->مقدار) = شروع;
			}
		      إذا (انتها)
			{
			  درخت epurpose
			    = اندازه_binop (PLUS_عبارت, purpose,
					  bitsize_int (len));
			  إذا (انتها > 1)
			    {
			      RAW_داده_درازی (v) -= plen - انتها;
			      RAW_داده_اشاره_گر (v) += plen - انتها;
			    }
			  وإلا
			    v = build_int_cst (درخت_TYPE (v),
					       RAW_داده_UCHAR_ELT (v, plen
								      - انتها));
			  جمع_کن_pending_init (loc, epurpose, v, origtype,
					    implicit, braced_init_obstack);
			}
		      q = &constructor_pending_elts;
		      استمر;
		    }
		}
	    }
	  وإلا
	    {
	      إذا (درخت_کد (p->مقدار) == RAW_داده_CST
		  && (RAW_داده_درازی (p->مقدار)
		      > (درخت_کد (مقدار) == RAW_داده_CST
			 ? RAW_داده_درازی (مقدار) : 1)))
		{
		  /* Override which should split the old RAW_DATA_CST
		     into 2 pieces.  */
		  إذا (!implicit && warn_override_init)
		    warning_init (loc, OPT_Woverride_init,
				  "initialized field overwritten");
		  بیعلامت HOST_WIDE_INT len = 1;
		  إذا (درخت_کد (مقدار) == RAW_داده_CST)
		    len = RAW_داده_درازی (مقدار);
		  إذا ((بیعلامت) RAW_داده_درازی (p->مقدار) > len + 1)
		    {
		      RAW_داده_درازی (p->مقدار) -= len;
		      RAW_داده_اشاره_گر (p->مقدار) += len;
		    }
		  وإلا
		    {
		      بیعلامت صحيح l = RAW_داده_درازی (p->مقدار) - 1;
		      p->مقدار
			= build_int_cst (درخت_TYPE (p->مقدار),
					 RAW_داده_UCHAR_ELT (p->مقدار, l));
		    }
		  p->purpose = اندازه_binop (PLUS_عبارت, p->purpose,
					   bitsize_int (len));
		  استمر;
		}
	      إذا (درخت_کد (مقدار) == RAW_داده_CST)
		{
		handle_raw_داده:
		  /* RAW_DATA_CST value might overlap various further
		     prior initval entries.  Find out how many.  */
		  بیعلامت cnt = 0;
		  widest_int w
		    = wi::مقصد_widest (purpose) + RAW_داده_درازی (مقدار);
		  بنية init_گره *r = p, *آخرین = عدم;
		  منطقي override_init = warn_override_init;
		  طالما ((r = init_گره_successor (r))
			 && wi::مقصد_widest (r->purpose) < w)
		    {
		      ++cnt;
		      إذا (درخت_SIDE_EFFECTS (r->مقدار))
			warning_init (loc, OPT_Woverride_init_side_effects,
				      "initialized field with side-effects "
				      "overwritten");
		      وإلا إذا (override_init)
			{
			  warning_init (loc, OPT_Woverride_init,
					"initialized field overwritten");
			  override_init = خطأ;
			}
		      آخرین = r;
		    }
		  إذا (cnt)
		    {
		      إذا (درخت_کد (آخرین->مقدار) == RAW_داده_CST
			  && (wi::مقصد_widest (آخرین->purpose)
			      + RAW_داده_درازی (آخرین->مقدار) > w))
			{
			  /* The last overlapping prior initval overlaps
			     only partially.  Shrink it and decrease cnt.  */
			  بیعلامت صحيح l = (wi::مقصد_widest (آخرین->purpose)
					    + RAW_داده_درازی (آخرین->مقدار)
					    - w).مقصد_uhwi ();
			  --cnt;
			  RAW_داده_درازی (آخرین->مقدار) -= l;
			  RAW_داده_اشاره_گر (آخرین->مقدار) += l;
			  إذا (RAW_داده_درازی (آخرین->مقدار) == 1)
			    آخرین->مقدار
			      = build_int_cst (درخت_TYPE (آخرین->مقدار),
					       RAW_داده_UCHAR_ELT (آخرین->مقدار,
								   0));
			  آخرین->purpose
			    = اندازه_binop (PLUS_عبارت, آخرین->purpose,
					  bitsize_int (l));
			}
		      /* Instead of deleting cnt nodes from the AVL tree
			 and rebalancing, peel of last cnt bytes from the
			 RAW_DATA_CST.  Overriding thousands of previously
			 initialized array elements with #embed needs to work,
			 but doesn't need to be super efficient.  */
		      gcc_checking_assert ((بیعلامت) RAW_داده_درازی (مقدار)
					   > cnt);
		      RAW_داده_درازی (مقدار) -= cnt;
		      ثابت بیعلامت حرف *s
			= &RAW_داده_UCHAR_ELT (مقدار, RAW_داده_درازی (مقدار));
		      بیعلامت صحيح o = RAW_داده_درازی (مقدار);
		      لكل (r = p; cnt--; ++o, ++s)
			{
			  r = init_گره_successor (r);
			  r->purpose = اندازه_binop (PLUS_عبارت, purpose,
						   bitsize_int (o));
			  r->مقدار = build_int_cst (درخت_TYPE (مقدار), *s);
			  r->origtype = origtype;
			}
		      إذا (RAW_داده_درازی (مقدار) == 1)
			مقدار = build_int_cst (درخت_TYPE (مقدار),
					       RAW_داده_UCHAR_ELT (مقدار, 0));
		    }
		}
	      إذا (!implicit)
		{
		  إذا (درخت_SIDE_EFFECTS (p->مقدار))
		    warning_init (loc, OPT_Woverride_init_side_effects,
				  "initialized field with side-effects "
				  "overwritten");
		  وإلا إذا (warn_override_init)
		    warning_init (loc, OPT_Woverride_init,
				  "initialized field overwritten");
		}
	      p->مقدار = مقدار;
	      p->origtype = origtype;
	      أرجع;
	    }
	}
      إذا (درخت_کد (مقدار) == RAW_داده_CST && p)
	{
	  بنية init_گره *r;
	  إذا (q == &p->چپ)
	    r = p;
	  وإلا
	    r = init_گره_successor (p);
	  إذا (r && wi::مقصد_widest (r->purpose) < (wi::مقصد_widest (purpose)
						 + RAW_داده_درازی (مقدار)))
	    {
	      /* Overlap with at least one prior initval in the range but
		 not at the start.  */
	      p = r;
	      p->purpose = purpose;
	      اذهب handle_raw_داده;
	    }
	}
    }
  وإلا
    {
      درخت bitpos;

      bitpos = بیت_position (purpose);
      طالما (*q != عدم)
	{
	  p = *q;
	  إذا (درخت_int_cst_lt (bitpos, بیت_position (p->purpose)))
	    q = &p->چپ;
	  وإلا إذا (p->purpose != purpose)
	    q = &p->راست;
	  وإلا
	    {
	      إذا (!implicit)
		{
		  إذا (درخت_SIDE_EFFECTS (p->مقدار))
		    warning_init (loc, OPT_Woverride_init_side_effects,
				  "initialized field with side-effects "
				  "overwritten");
		  وإلا إذا (warn_override_init)
		    warning_init (loc, OPT_Woverride_init,
				  "initialized field overwritten");
		}
	      p->مقدار = مقدار;
	      p->origtype = origtype;
	      أرجع;
	    }
	}
    }

  r = (بنية init_گره *) obstack_alloc (braced_init_obstack,
					  حجم (بنية init_گره));
  r->purpose = purpose;
  r->مقدار = مقدار;
  r->origtype = origtype;

  *q = r;
  r->والد = p;
  r->چپ = 0;
  r->راست = 0;
  r->balance = 0;

  طالما (p)
    {
      بنية init_گره *s;

      إذا (r == p->چپ)
	{
	  إذا (p->balance == 0)
	    p->balance = -1;
	  وإلا إذا (p->balance < 0)
	    {
	      إذا (r->balance < 0)
		{
		  /* L rotation.  */
		  p->چپ = r->راست;
		  إذا (p->چپ)
		    p->چپ->والد = p;
		  r->راست = p;

		  p->balance = 0;
		  r->balance = 0;

		  s = p->والد;
		  p->والد = r;
		  r->والد = s;
		  إذا (s)
		    {
		      إذا (s->چپ == p)
			s->چپ = r;
		      وإلا
			s->راست = r;
		    }
		  وإلا
		    constructor_pending_elts = r;
		}
	      وإلا
		{
		  /* LR rotation.  */
		  بنية init_گره *t = r->راست;

		  r->راست = t->چپ;
		  إذا (r->راست)
		    r->راست->والد = r;
		  t->چپ = r;

		  p->چپ = t->راست;
		  إذا (p->چپ)
		    p->چپ->والد = p;
		  t->راست = p;

		  p->balance = t->balance < 0;
		  r->balance = -(t->balance > 0);
		  t->balance = 0;

		  s = p->والد;
		  p->والد = t;
		  r->والد = t;
		  t->والد = s;
		  إذا (s)
		    {
		      إذا (s->چپ == p)
			s->چپ = t;
		      وإلا
			s->راست = t;
		    }
		  وإلا
		    constructor_pending_elts = t;
		}
	      اكسر;
	    }
	  وإلا
	    {
	      /* p->balance == +1; growth of left side balances the node.  */
	      p->balance = 0;
	      اكسر;
	    }
	}
      وإلا /* r == p->right */
	{
	  إذا (p->balance == 0)
	    /* Growth propagation from right side.  */
	    p->balance++;
	  وإلا إذا (p->balance > 0)
	    {
	      إذا (r->balance > 0)
		{
		  /* R rotation.  */
		  p->راست = r->چپ;
		  إذا (p->راست)
		    p->راست->والد = p;
		  r->چپ = p;

		  p->balance = 0;
		  r->balance = 0;

		  s = p->والد;
		  p->والد = r;
		  r->والد = s;
		  إذا (s)
		    {
		      إذا (s->چپ == p)
			s->چپ = r;
		      وإلا
			s->راست = r;
		    }
		  وإلا
		    constructor_pending_elts = r;
		}
	      وإلا /* r->balance == -1 */
		{
		  /* RL rotation */
		  بنية init_گره *t = r->چپ;

		  r->چپ = t->راست;
		  إذا (r->چپ)
		    r->چپ->والد = r;
		  t->راست = r;

		  p->راست = t->چپ;
		  إذا (p->راست)
		    p->راست->والد = p;
		  t->چپ = p;

		  r->balance = (t->balance < 0);
		  p->balance = -(t->balance > 0);
		  t->balance = 0;

		  s = p->والد;
		  p->والد = t;
		  r->والد = t;
		  t->والد = s;
		  إذا (s)
		    {
		      إذا (s->چپ == p)
			s->چپ = t;
		      وإلا
			s->راست = t;
		    }
		  وإلا
		    constructor_pending_elts = t;
		}
	      اكسر;
	    }
	  وإلا
	    {
	      /* p->balance == -1; growth of right side balances the node.  */
	      p->balance = 0;
	      اكسر;
	    }
	}

      r = p;
      p = p->والد;
    }
}

/* Build AVL tree from a sorted chain.  */

ساكن فراغ
مجموعه_nonincremental_init (بنية obstack * braced_init_obstack)
{
  بیعلامت HOST_WIDE_INT ix;
  درخت شاخص, مقدار;

  إذا (درخت_کد (constructor_type) != رکورد_TYPE
      && درخت_کد (constructor_type) != ARRAY_TYPE)
    أرجع;

  FOR_EACH_CONSTRUCTOR_ELT (constructor_elements, ix, شاخص, مقدار)
    جمع_کن_pending_init (درون_داد_location, شاخص, مقدار, NULL_درخت, درست,
		      braced_init_obstack);
  constructor_elements = عدم;
  إذا (درخت_کد (constructor_type) == رکورد_TYPE)
    {
      constructor_unfilled_fields = TYPE_FIELDS (constructor_type);
      /* Skip any nameless bit fields at the beginning.  */
      طالما (constructor_unfilled_fields != NULL_درخت
	     && DECL_UNNAMED_بیت_فیلد (constructor_unfilled_fields))
	constructor_unfilled_fields = درخت_CHAIN (constructor_unfilled_fields);

    }
  وإلا إذا (درخت_کد (constructor_type) == ARRAY_TYPE)
    {
      إذا (TYPE_DOMAIN (constructor_type))
	constructor_unfilled_شاخص
	  = convert (bitsizetype,
		     TYPE_MIN_مقدار (TYPE_DOMAIN (constructor_type)));
      وإلا
	constructor_unfilled_شاخص = bitsize_zero_گره;
    }
  constructor_incremental = 0;
}

/* Build AVL tree from a string constant.  */

ساكن فراغ
مجموعه_nonincremental_init_from_string (درخت str,
				     بنية obstack * braced_init_obstack)
{
  درخت مقدار, purpose, type;
  HOST_WIDE_INT val[2];
  ثابت حرف *p, *انتها;
  صحيح byte, wchar_بایتها, charwidth, bitpos;

  gcc_assert (درخت_کد (constructor_type) == ARRAY_TYPE);

  wchar_بایتها = TYPE_PRECISION (درخت_TYPE (درخت_TYPE (str))) / بیتها_در_هر_UNIT;
  charwidth = TYPE_PRECISION (char_type_گره);
  gcc_assert ((اندازه_t) wchar_بایتها * charwidth
	      <= ARRAY_اندازه (val) * HOST_بیتها_در_هر_WIDE_INT);
  type = درخت_TYPE (constructor_type);
  p = درخت_STRING_اشاره_گر (str);
  انتها = p + درخت_STRING_درازی (str);

  لكل (purpose = bitsize_zero_گره;
       p < انتها
       && !(constructor_max_شاخص
	    && درخت_int_cst_lt (constructor_max_شاخص, purpose));
       purpose = اندازه_binop (PLUS_عبارت, purpose, bitsize_one_گره))
    {
      إذا (wchar_بایتها == 1)
	{
	  val[0] = (بیعلامت حرف) *p++;
	  val[1] = 0;
	}
      وإلا
	{
	  val[1] = 0;
	  val[0] = 0;
	  لكل (byte = 0; byte < wchar_بایتها; byte++)
	    {
	      إذا (بایتها_BIG_ENDIAN)
		bitpos = (wchar_بایتها - byte - 1) * charwidth;
	      وإلا
		bitpos = byte * charwidth;
	      val[bitpos / HOST_بیتها_در_هر_WIDE_INT]
		|= ((بیعلامت HOST_WIDE_INT) ((بیعلامت حرف) *p++))
		   << (bitpos % HOST_بیتها_در_هر_WIDE_INT);
	    }
	}

      إذا (!TYPE_UNSIGNED (type))
	{
	  bitpos = ((wchar_بایتها - 1) * charwidth) + HOST_بیتها_در_هر_CHAR;
	  إذا (bitpos < HOST_بیتها_در_هر_WIDE_INT)
	    {
	      إذا (val[0] & (HOST_WIDE_INT_1 << (bitpos - 1)))
		{
		  val[0] |= HOST_WIDE_INT_M1U << bitpos;
		  val[1] = -1;
		}
	    }
	  وإلا إذا (bitpos == HOST_بیتها_در_هر_WIDE_INT)
	    {
	      إذا (val[0] < 0)
		val[1] = -1;
	    }
	  وإلا إذا (val[1] & (HOST_WIDE_INT_1
			     << (bitpos - 1 - HOST_بیتها_در_هر_WIDE_INT)))
	    val[1] |= HOST_WIDE_INT_M1U << (bitpos - HOST_بیتها_در_هر_WIDE_INT);
	}

      مقدار = wide_int_مقصد_درخت (type,
				wide_int::from_array (val, 2,
						      HOST_بیتها_در_هر_WIDE_INT * 2));
      جمع_کن_pending_init (درون_داد_location, purpose, مقدار, NULL_درخت, درست,
                        braced_init_obstack);
    }

  constructor_incremental = 0;
}

/* Return value of FIELD in pending initializer or NULL_TREE if the field was
   not initialized yet.  */

ساكن درخت
پیدا_کن_init_member (درخت فیلد_2, بنية obstack * braced_init_obstack)
{
  بنية init_گره *p;

  إذا (درخت_کد (constructor_type) == ARRAY_TYPE)
    {
      إذا (constructor_incremental
	  && درخت_int_cst_lt (فیلد_2, constructor_unfilled_شاخص))
	مجموعه_nonincremental_init (braced_init_obstack);

      p = constructor_pending_elts;
      طالما (p)
	{
	  إذا (درخت_int_cst_lt (فیلد_2, p->purpose))
	    p = p->چپ;
	  وإلا إذا (درخت_int_cst_lt (p->purpose, فیلد_2))
	    p = p->راست;
	  وإلا
	    أرجع p->مقدار;
	}
    }
  وإلا إذا (درخت_کد (constructor_type) == رکورد_TYPE)
    {
      درخت bitpos = بیت_position (فیلد_2);

      إذا (constructor_incremental
	  && (!constructor_unfilled_fields
	      || درخت_int_cst_lt (bitpos,
				  بیت_position (constructor_unfilled_fields))))
	مجموعه_nonincremental_init (braced_init_obstack);

      p = constructor_pending_elts;
      طالما (p)
	{
	  إذا (فیلد_2 == p->purpose)
	    أرجع p->مقدار;
	  وإلا إذا (درخت_int_cst_lt (bitpos, بیت_position (p->purpose)))
	    p = p->چپ;
	  وإلا
	    p = p->راست;
	}
    }
  وإلا إذا (درخت_کد (constructor_type) == UNION_TYPE)
    {
      إذا (!vec_امن_is_خالی (constructor_elements)
	  && (constructor_elements->آخرین ().شاخص == فیلد_2))
	أرجع constructor_elements->آخرین ().مقدار;
    }
  أرجع NULL_درخت;
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

ساكن فراغ
output_init_element (location_t loc, درخت مقدار, درخت origtype,
		     منطقي strict_string, درخت type, درخت فیلد_2, منطقي pending,
		     منطقي implicit, بنية obstack * braced_init_obstack)
{
  درخت semantic_type = NULL_درخت;
  منطقي maybe_const = درست;
  منطقي npc, int_const_عبارت, arith_const_عبارت;

  إذا (type == error_mark_گره || مقدار == error_mark_گره)
    {
      constructor_erroneous = 1;
      أرجع;
    }
  إذا (درخت_کد (درخت_TYPE (مقدار)) == ARRAY_TYPE
      && (درخت_کد (مقدار) == STRING_CST
	  || درخت_کد (مقدار) == COMPOUND_LITERAL_عبارت)
      && !(درخت_کد (مقدار) == STRING_CST
	   && درخت_کد (type) == ARRAY_TYPE
	   && INTEGRAL_TYPE_P (درخت_TYPE (type)))
      && !comptypes (TYPE_MAIN_VARIANT (درخت_TYPE (مقدار)),
		     TYPE_MAIN_VARIANT (type)))
    مقدار = array_مقصد_اشاره_گر_conversion (درون_داد_location, مقدار);

  إذا (درخت_کد (مقدار) == COMPOUND_LITERAL_عبارت
      && require_constant_مقدار && pending)
    {
      /* As an extension, allow initializing objects with static storage
	 duration with compound literals (which are then treated just as
	 the brace enclosed list they contain).  */
      إذا (flag_isoc99)
	pedwarn_init (loc, OPT_Wpedantic, "initializer element is not "
		      "constant");
      درخت decl = COMPOUND_LITERAL_عبارت_DECL (مقدار);
      مقدار = DECL_INITIAL (decl);
    }

  npc = null_اشاره_گر_constant_p (مقدار);
  int_const_عبارت = (درخت_کد (مقدار) == INTEGER_CST
		    && !درخت_سرریز (مقدار)
		    && INTEGRAL_TYPE_P (درخت_TYPE (مقدار)));
  /* Not fully determined before folding.  */
  arith_const_عبارت = درست;
  إذا (درخت_کد (مقدار) == EXCESS_PRECISION_عبارت)
    {
      semantic_type = درخت_TYPE (مقدار);
      مقدار = درخت_عملوند (مقدار, 0);
    }
  مقدار = c_fully_fold (مقدار, require_constant_مقدار, &maybe_const);
  /* TODO: this may not detect all cases of expressions folding to
     constants that are not arithmetic constant expressions.  */
  إذا (!maybe_const)
    arith_const_عبارت = خطأ;
  وإلا إذا (!INTEGRAL_TYPE_P (درخت_TYPE (مقدار))
	   && درخت_کد (درخت_TYPE (مقدار)) != REAL_TYPE
	   && درخت_کد (درخت_TYPE (مقدار)) != COMPLEX_TYPE)
    arith_const_عبارت = خطأ;
  وإلا إذا (درخت_کد (مقدار) != INTEGER_CST
	   && درخت_کد (مقدار) != REAL_CST
	   && درخت_کد (مقدار) != COMPLEX_CST
	   && درخت_کد (مقدار) != RAW_داده_CST)
    arith_const_عبارت = خطأ;
  وإلا إذا (درخت_سرریز (مقدار))
    arith_const_عبارت = خطأ;

  إذا (مقدار == error_mark_گره)
    constructor_erroneous = 1;
  وإلا إذا (!درخت_CONSTANT (مقدار))
    constructor_constant = 0;
  وإلا إذا (!initializer_constant_valid_p (مقدار,
					  درخت_TYPE (مقدار),
					  AGGREGATE_TYPE_P (constructor_type)
					  && TYPE_معکوس_STORAGE_ترتیب
					     (constructor_type))
	   || (رکورد_OR_UNION_TYPE_P (constructor_type)
	       && DECL_C_بیت_فیلد (فیلد_2)
	       && درخت_کد (مقدار) != INTEGER_CST))
    constructor_simple = 0;
  إذا (!maybe_const)
    constructor_nonconst = 1;

  /* Digest the initializer and issue any errors about incompatible
     types before issuing errors about non-constant initializers.  */
  درخت new_مقدار = مقدار;
  إذا (semantic_type)
    new_مقدار = build1 (EXCESS_PRECISION_عبارت, semantic_type, مقدار);
  /* In the case of braces around a scalar initializer, the result of
     this initializer processing goes through digest_init again at the
     outer level.  In the case of a constexpr initializer for a
     pointer, avoid converting a null pointer constant to something
     that is not a null pointer constant to avoid a spurious error
     from that second processing.  */
  إذا (!require_constexpr_مقدار
      || !npc
      || درخت_کد (constructor_type) != اشاره_گر_TYPE)
    new_مقدار = digest_init (loc,
			     رکورد_OR_UNION_TYPE_P (constructor_type)
			     ? فیلد_2 : constructor_fields
			     ? constructor_fields : constructor_decl,
			     type, new_مقدار, origtype, npc,
			     int_const_عبارت, arith_const_عبارت, strict_string,
			     require_constant_مقدار, require_constexpr_مقدار);
  إذا (new_مقدار == error_mark_گره)
    {
      constructor_erroneous = 1;
      أرجع;
    }
  إذا (require_constant_مقدار || require_constant_elements)
    constant_عبارت_warning (new_مقدار);

  /* Proceed to check the constness of the original initializer.  */
  إذا (!initializer_constant_valid_p (مقدار, درخت_TYPE (مقدار)))
    {
      إذا (require_constant_مقدار)
	{
	  error_init (loc, "initializer element is not constant");
	  مقدار = error_mark_گره;
	}
      وإلا إذا (require_constant_elements)
	pedwarn (loc, OPT_Wpedantic,
		 "initializer element is not computable at load time");
    }
  وإلا إذا (!maybe_const
	   && (require_constant_مقدار || require_constant_elements))
    pedwarn_init (loc, OPT_Wpedantic,
		  "initializer element is not a constant expression");
  /* digest_init has already carried out the additional checks
     required for 'constexpr' initializers (using the information
     passed to it about whether the original initializer was certain
     kinds of constant expression), so that check does not need to be
     repeated here.  */

  /* Issue -Wc++-compat warnings about initializing a bitfield with
     enum type.  */
  إذا (warn_cxx_compat
      && فیلد_2 != NULL_درخت
      && درخت_کد (فیلد_2) == فیلد_DECL
      && DECL_بیت_فیلد_TYPE (فیلد_2) != NULL_درخت
      && (TYPE_MAIN_VARIANT (DECL_بیت_فیلد_TYPE (فیلد_2))
	  != TYPE_MAIN_VARIANT (type))
      && درخت_کد (DECL_بیت_فیلد_TYPE (فیلد_2)) == ENUMERAL_TYPE)
    {
      درخت checktype = origtype != NULL_درخت ? origtype : درخت_TYPE (مقدار);
      إذا (checktype != error_mark_گره
	  && (TYPE_MAIN_VARIANT (checktype)
	      != TYPE_MAIN_VARIANT (DECL_بیت_فیلد_TYPE (فیلد_2))))
	warning_init (loc, OPT_Wc___compat,
		      "enum conversion in initialization is invalid in C++");
    }

  /* If this field is empty and does not have side effects (and is not at
     the end of structure), don't do anything other than checking the
     initializer.  */
  إذا (فیلد_2
      && (درخت_TYPE (فیلد_2) == error_mark_گره
	  || (COMPLETE_TYPE_P (درخت_TYPE (فیلد_2))
	      && integer_zerop (TYPE_اندازه (درخت_TYPE (فیلد_2)))
	      && !درخت_SIDE_EFFECTS (new_مقدار)
	      && (درخت_کد (constructor_type) == ARRAY_TYPE
		  || DECL_CHAIN (فیلد_2)))))
    أرجع;

  /* Finally, set VALUE to the initializer value digested above.  */
  مقدار = new_مقدار;

  /* If this element doesn't come next in sequence,
     put it on constructor_pending_elts.  */
  إذا (درخت_کد (constructor_type) == ARRAY_TYPE
      && (!constructor_incremental
	  || !درخت_int_cst_equal (فیلد_2, constructor_unfilled_شاخص)
	  || (درخت_کد (مقدار) == RAW_داده_CST
	      && constructor_pending_elts
	      && pending)))
    {
      إذا (constructor_incremental
	  && (درخت_int_cst_lt (فیلد_2, constructor_unfilled_شاخص)
	      || (درخت_کد (مقدار) == RAW_داده_CST
		  && constructor_pending_elts
		  && pending)))
	مجموعه_nonincremental_init (braced_init_obstack);

      جمع_کن_pending_init (loc, فیلد_2, مقدار, origtype, implicit,
			braced_init_obstack);
      أرجع;
    }
  وإلا إذا (درخت_کد (constructor_type) == رکورد_TYPE
	   && (!constructor_incremental
	       || فیلد_2 != constructor_unfilled_fields))
    {
      /* We do this for records but not for unions.  In a union,
	 no matter which field is specified, it can be initialized
	 right away since it starts at the beginning of the union.  */
      إذا (constructor_incremental)
	{
	  إذا (!constructor_unfilled_fields)
	    مجموعه_nonincremental_init (braced_init_obstack);
	  وإلا
	    {
	      درخت bitpos, unfillpos;

	      bitpos = بیت_position (فیلد_2);
	      unfillpos = بیت_position (constructor_unfilled_fields);

	      إذا (درخت_int_cst_lt (bitpos, unfillpos))
		مجموعه_nonincremental_init (braced_init_obstack);
	    }
	}

      جمع_کن_pending_init (loc, فیلد_2, مقدار, origtype, implicit,
			braced_init_obstack);
      أرجع;
    }
  وإلا إذا (درخت_کد (constructor_type) == UNION_TYPE
	   && !vec_امن_is_خالی (constructor_elements))
    {
      إذا (!implicit)
	{
	  إذا (درخت_SIDE_EFFECTS (constructor_elements->آخرین ().مقدار))
	    warning_init (loc, OPT_Woverride_init_side_effects,
			  "initialized field with side-effects overwritten");
	  وإلا إذا (warn_override_init)
	    warning_init (loc, OPT_Woverride_init,
			  "initialized field overwritten");
	}

      /* We can have just one union field set.  */
      constructor_elements = عدم;
    }

  /* Otherwise, output this element either to
     constructor_elements or to the assembler file.  */

  constructor_elt celt = {فیلد_2, مقدار};
  vec_امن_افزودن (constructor_elements, celt);

  /* Advance the variable that indicates sequential elements output.  */
  إذا (درخت_کد (constructor_type) == ARRAY_TYPE)
    {
      درخت inc = bitsize_one_گره;
      إذا (مقدار && درخت_کد (مقدار) == RAW_داده_CST)
	inc = bitsize_int (RAW_داده_درازی (مقدار));
      constructor_unfilled_شاخص
	= اندازه_binop_loc (درون_داد_location, PLUS_عبارت,
			  constructor_unfilled_شاخص, inc);
    }
  وإلا إذا (درخت_کد (constructor_type) == رکورد_TYPE)
    {
      constructor_unfilled_fields
	= DECL_CHAIN (constructor_unfilled_fields);

      /* Skip any nameless bit fields.  */
      طالما (constructor_unfilled_fields != NULL_درخت
	     && DECL_UNNAMED_بیت_فیلد (constructor_unfilled_fields))
	constructor_unfilled_fields
	  = DECL_CHAIN (constructor_unfilled_fields);
    }
  وإلا إذا (درخت_کد (constructor_type) == UNION_TYPE)
    constructor_unfilled_fields = NULL_درخت;

  /* Now output any pending elements which have become next.  */
  إذا (pending)
    output_pending_init_elements (0, braced_init_obstack);
}

/* For two FIELD_DECLs in the same chain, return -1 if field1
   comes before field2, 1 if field1 comes after field2 and
   0 if field1 == field2.  */

ساكن صحيح
init_فیلد_decl_cmp (درخت field1, درخت field2)
{
  إذا (field1 == field2)
    أرجع 0;

  درخت bitpos1 = بیت_position (field1);
  درخت bitpos2 = بیت_position (field2);
  إذا (درخت_int_cst_equal (bitpos1, bitpos2))
    {
      /* If one of the fields has non-zero bitsize, then that
	 field must be the last one in a sequence of zero
	 sized fields, fields after it will have bigger
	 bit_position.  */
      إذا (درخت_TYPE (field1) != error_mark_گره
	  && COMPLETE_TYPE_P (درخت_TYPE (field1))
	  && integer_nonzerop (درخت_TYPE (field1)))
	أرجع 1;
      إذا (درخت_TYPE (field2) != error_mark_گره
	  && COMPLETE_TYPE_P (درخت_TYPE (field2))
	  && integer_nonzerop (درخت_TYPE (field2)))
	أرجع -1;
      /* Otherwise, fallback to DECL_CHAIN walk to find out
	 which field comes earlier.  Walk chains of both
	 fields, so that if field1 and field2 are close to each
	 other in either order, it is found soon even for large
	 sequences of zero sized fields.  */
      درخت f1 = field1, f2 = field2;
      طالما (1)
	{
	  f1 = DECL_CHAIN (f1);
	  f2 = DECL_CHAIN (f2);
	  إذا (f1 == NULL_درخت)
	    {
	      gcc_assert (f2);
	      أرجع 1;
	    }
	  إذا (f2 == NULL_درخت)
	    أرجع -1;
	  إذا (f1 == field2)
	    أرجع -1;
	  إذا (f2 == field1)
	    أرجع 1;
	  إذا (!درخت_int_cst_equal (بیت_position (f1), bitpos1))
	    أرجع 1;
	  إذا (!درخت_int_cst_equal (بیت_position (f2), bitpos1))
	    أرجع -1;
	}
    }
  وإلا إذا (درخت_int_cst_lt (bitpos1, bitpos2))
    أرجع -1;
  وإلا
    أرجع 1;
}

/* Output any pending elements which have become next.
   As we output elements, constructor_unfilled_{fields,index}
   advances, which may cause other elements to become next;
   if so, they too are output.

   If ALL is 0, we return when there are
   no more pending elements to output now.

   If ALL is 1, we output space as necessary so that
   we can output all the pending elements.  */
ساكن فراغ
output_pending_init_elements (صحيح all, بنية obstack * braced_init_obstack)
{
  بنية init_گره *elt = constructor_pending_elts;
  درخت بعدی;

 retry:

  /* Look through the whole pending tree.
     If we find an element that should be output now,
     output it.  Otherwise, set NEXT to the element
     that comes first among those still pending.  */

  بعدی = NULL_درخت;
  طالما (elt)
    {
      إذا (درخت_کد (constructor_type) == ARRAY_TYPE)
	{
	  إذا (درخت_int_cst_equal (elt->purpose,
				  constructor_unfilled_شاخص))
	    output_init_element (درون_داد_location, elt->مقدار, elt->origtype,
				 درست, درخت_TYPE (constructor_type),
				 constructor_unfilled_شاخص, خطأ, خطأ,
				 braced_init_obstack);
	  وإلا إذا (درخت_int_cst_lt (constructor_unfilled_شاخص,
				    elt->purpose))
	    {
	      /* Advance to the next smaller node.  */
	      إذا (elt->چپ)
		elt = elt->چپ;
	      وإلا
		{
		  /* We have reached the smallest node bigger than the
		     current unfilled index.  Fill the space first.  */
		  بعدی = elt->purpose;
		  اكسر;
		}
	    }
	  وإلا
	    {
	      /* Advance to the next bigger node.  */
	      إذا (elt->راست)
		elt = elt->راست;
	      وإلا
		{
		  /* We have reached the biggest node in a subtree.  Find
		     the parent of it, which is the next bigger node.  */
		  طالما (elt->والد && elt->والد->راست == elt)
		    elt = elt->والد;
		  elt = elt->والد;
		  إذا (elt && درخت_int_cst_lt (constructor_unfilled_شاخص,
					      elt->purpose))
		    {
		      بعدی = elt->purpose;
		      اكسر;
		    }
		}
	    }
	}
      وإلا إذا (رکورد_OR_UNION_TYPE_P (constructor_type))
	{
	  /* If the current record is complete we are done.  */
	  إذا (constructor_unfilled_fields == NULL_درخت)
	    اكسر;

	  صحيح cmp = init_فیلد_decl_cmp (constructor_unfilled_fields,
					 elt->purpose);
	  إذا (cmp == 0)
	    output_init_element (درون_داد_location, elt->مقدار, elt->origtype,
				 درست, درخت_TYPE (elt->purpose),
				 elt->purpose, خطأ, خطأ,
				 braced_init_obstack);
	  وإلا إذا (cmp < 0)
	    {
	      /* Advance to the next smaller node.  */
	      إذا (elt->چپ)
		elt = elt->چپ;
	      وإلا
		{
		  /* We have reached the smallest node bigger than the
		     current unfilled field.  Fill the space first.  */
		  بعدی = elt->purpose;
		  اكسر;
		}
	    }
	  وإلا
	    {
	      /* Advance to the next bigger node.  */
	      إذا (elt->راست)
		elt = elt->راست;
	      وإلا
		{
		  /* We have reached the biggest node in a subtree.  Find
		     the parent of it, which is the next bigger node.  */
		  طالما (elt->والد && elt->والد->راست == elt)
		    elt = elt->والد;
		  elt = elt->والد;
		  إذا (elt
		      && init_فیلد_decl_cmp (constructor_unfilled_fields,
					      elt->purpose) < 0)
		    {
		      بعدی = elt->purpose;
		      اكسر;
		    }
		}
	    }
	}
    }

  /* Ordinarily return, but not if we want to output all
     and there are elements left.  */
  إذا (!(all && بعدی != NULL_درخت))
    أرجع;

  /* If it's not incremental, just skip over the gap, so that after
     jumping to retry we will output the next successive element.  */
  إذا (رکورد_OR_UNION_TYPE_P (constructor_type))
    constructor_unfilled_fields = بعدی;
  وإلا إذا (درخت_کد (constructor_type) == ARRAY_TYPE)
    constructor_unfilled_شاخص = بعدی;

  /* ELT now points to the node in the pending tree with the next
     initializer to output.  */
  اذهب retry;
}

/* Expression VALUE coincides with the start of type TYPE in a braced
   initializer.  Return true if we should treat VALUE as initializing
   the first element of TYPE, false if we should treat it as initializing
   TYPE as a whole.

   If the initializer is clearly invalid, the question becomes:
   which choice gives the best error message?  */

ساكن منطقي
initialize_elementwise_p (درخت type, درخت مقدار)
{
  إذا (type == error_mark_گره || مقدار == error_mark_گره)
    أرجع خطأ;

  gcc_checking_assert (TYPE_MAIN_VARIANT (type) == type);

  درخت مقدار_type = درخت_TYPE (مقدار);
  إذا (مقدار_type == error_mark_گره)
    أرجع خطأ;

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
  إذا (gnu_وکتور_type_p (type))
    أرجع !وکتور_TYPE_P (مقدار_type);

  إذا (AGGREGATE_TYPE_P (type))
    أرجع !comptypes (type, TYPE_MAIN_VARIANT (مقدار_type));

  أرجع خطأ;
}

/* Helper function for process_init_element.  Split first element of
   RAW_DATA_CST and save the rest to *RAW_DATA.  */

ساكن مضمن درخت
maybe_تقسیم_raw_داده (درخت مقدار, درخت *raw_داده)
{
  إذا (مقدار == NULL_درخت || درخت_کد (مقدار) != RAW_داده_CST)
    أرجع مقدار;
  *raw_داده = مقدار;
  مقدار = build_int_cst (integer_type_گره,
			 RAW_داده_UCHAR_ELT (*raw_داده, 0));
  ++RAW_داده_اشاره_گر (*raw_داده);
  --RAW_داده_درازی (*raw_داده);
  أرجع مقدار;
}

/* Return non-zero if c_parser_initval should attempt to optimize
   large initializers into RAW_DATA_CST.  In that case return how
   many elements to optimize at most.  */

بیعلامت
c_maybe_optimize_large_byte_initializer (فراغ)
{
  إذا (!constructor_type
      || درخت_کد (constructor_type) != ARRAY_TYPE
      || constructor_پشته->implicit)
    أرجع 0;
  درخت elttype = TYPE_MAIN_VARIANT (درخت_TYPE (constructor_type));
  إذا (درخت_کد (elttype) != INTEGER_TYPE
      && درخت_کد (elttype) != BITINT_TYPE)
    أرجع 0;
  إذا (TYPE_PRECISION (elttype) != CHAR_بیت
      || constructor_پشته->replacement_مقدار.مقدار
      || (COMPLETE_TYPE_P (constructor_type)
	  && !poly_int_درخت_p (TYPE_اندازه (constructor_type)))
      || constructor_range_پشته)
    أرجع 0;
  إذا (constructor_max_شاخص == NULL_درخت)
    أرجع بیشترین_صحیح;
  إذا (درخت_int_cst_le (constructor_max_شاخص, constructor_شاخص)
      || integer_all_onesp (constructor_max_شاخص))
    أرجع 0;
  widest_int w = wi::مقصد_widest (constructor_max_شاخص);
  w -= wi::مقصد_widest (constructor_شاخص);
  w += 1;
  إذا (w < 64)
    أرجع 0;
  إذا (w > بیشترین_صحیح)
    أرجع بیشترین_صحیح;
  أرجع w.مقصد_uhwi ();
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

فراغ
process_init_element (location_t loc, بنية c_عبارت مقدار, منطقي implicit,
		      بنية obstack * braced_init_obstack)
{
  درخت orig_مقدار = مقدار.مقدار;
  صحيح string_flag
    = (orig_مقدار != NULL_درخت && درخت_کد (orig_مقدار) == STRING_CST);
  منطقي strict_string = مقدار.original_کد == STRING_CST;
  منطقي was_designated = designator_عمق != 0;
  درخت raw_داده = NULL_درخت;

retry:
  designator_عمق = 0;
  designator_erroneous = 0;

  إذا (!implicit && مقدار.مقدار && !integer_zerop (مقدار.مقدار))
    constructor_zeroinit = 0;

  /* Handle superfluous braces around string cst as in
     char x[] = {"foo"}; */
  إذا (constructor_type
      && !was_designated
      && درخت_کد (constructor_type) == ARRAY_TYPE
      && INTEGRAL_TYPE_P (درخت_TYPE (constructor_type))
      && integer_zerop (constructor_unfilled_شاخص))
    {
      إذا (constructor_پشته->replacement_مقدار.مقدار)
	{
	  error_init (loc, "excess elements in %qT initializer", constructor_type);
	  أرجع;
	}
      وإلا إذا (string_flag)
	{
	  constructor_پشته->replacement_مقدار = مقدار;
	  أرجع;
	}
    }

  إذا (constructor_پشته->replacement_مقدار.مقدار != NULL_درخت)
    {
      error_init (loc, "excess elements in struct initializer");
      أرجع;
    }

  /* Ignore elements of a brace group if it is entirely superfluous
     and has already been diagnosed, or if the type is erroneous.  */
  إذا (constructor_type == NULL_درخت || constructor_type == error_mark_گره)
    أرجع;

  /* Ignore elements of an initializer for a variable-size type.
     Those are diagnosed in the parser (empty initializer braces are OK).  */
  إذا (COMPLETE_TYPE_P (constructor_type)
      && !poly_int_درخت_p (TYPE_اندازه (constructor_type)))
    أرجع;

  إذا (!implicit && warn_designated_init && !was_designated
      && درخت_کد (constructor_type) == رکورد_TYPE
      && lookup_attribute ("designated_init",
			   TYPE_صفات (constructor_type)))
    warning_init (loc,
		  OPT_Wdesignated_init,
		  "positional initialization of field "
		  "in %<struct%> declared with %<designated_init%> attribute");

  /* If we've exhausted any levels that didn't have braces,
     pop them now.  */
  طالما (constructor_پشته->implicit)
    {
      إذا (رکورد_OR_UNION_TYPE_P (constructor_type)
	  && constructor_fields == NULL_درخت)
	process_init_element (loc,
			      برداشت_init_level (loc, 1, braced_init_obstack,
					      آخرین_init_list_comma),
			      درست, braced_init_obstack);
      وإلا إذا ((درخت_کد (constructor_type) == ARRAY_TYPE
		|| gnu_وکتور_type_p (constructor_type))
	       && constructor_max_شاخص
	       && درخت_int_cst_lt (constructor_max_شاخص,
				   constructor_شاخص))
	process_init_element (loc,
			      برداشت_init_level (loc, 1, braced_init_obstack,
					      آخرین_init_list_comma),
			      درست, braced_init_obstack);
      وإلا
	اكسر;
    }

  /* In the case of [LO ... HI] = VALUE, only evaluate VALUE once.  */
  إذا (constructor_range_پشته)
    {
      /* If value is a compound literal and we'll be just using its
	 content, don't put it into a SAVE_EXPR.  */
      إذا (درخت_کد (مقدار.مقدار) != COMPOUND_LITERAL_عبارت
	  || !require_constant_مقدار)
	{
	  درخت semantic_type = NULL_درخت;
	  إذا (درخت_کد (مقدار.مقدار) == EXCESS_PRECISION_عبارت)
	    {
	      semantic_type = درخت_TYPE (مقدار.مقدار);
	      مقدار.مقدار = درخت_عملوند (مقدار.مقدار, 0);
	    }
	  مقدار.مقدار = save_عبارت (مقدار.مقدار);
	  إذا (semantic_type)
	    مقدار.مقدار = build1 (EXCESS_PRECISION_عبارت, semantic_type,
				  مقدار.مقدار);
	}
    }

  طالما (1)
    {
      إذا (درخت_کد (constructor_type) == رکورد_TYPE)
	{
	  درخت fieldtype;
	  تعداد درخت_کد_2 fieldcode;

	  إذا (constructor_fields == NULL_درخت)
	    {
	      pedwarn_init (loc, 0, "excess elements in struct initializer");
	      اكسر;
	    }

	  fieldtype = درخت_TYPE (constructor_fields);
	  إذا (fieldtype != error_mark_گره)
	    fieldtype = TYPE_MAIN_VARIANT (fieldtype);
	  fieldcode = درخت_کد (fieldtype);

	  /* Error for non-static initialization of a flexible array member.  */
	  إذا (fieldcode == ARRAY_TYPE
	      && !require_constant_مقدار
	      && TYPE_اندازه (fieldtype) == NULL_درخت
	      && DECL_CHAIN (constructor_fields) == NULL_درخت)
	    {
	      error_init (loc, "non-static initialization of a flexible "
			  "array member");
	      اكسر;
	    }

	  /* Error for initialization of a flexible array member with
	     a string constant if the structure is in an array.  E.g.:
	     struct S { int x; char y[]; };
	     struct S s[] = { { 1, "foo" } };
	     is invalid.  */
	  إذا (string_flag
	      && fieldcode == ARRAY_TYPE
	      && constructor_عمق > 1
	      && TYPE_اندازه (fieldtype) == NULL_درخت
	      && DECL_CHAIN (constructor_fields) == NULL_درخت)
	    {
	      منطقي درون_array_p = خطأ;
	      لكل (بنية constructor_پشته *p = constructor_پشته;
		   p && p->type; p = p->بعدی)
		إذا (درخت_کد (p->type) == ARRAY_TYPE)
		  {
		    درون_array_p = درست;
		    اكسر;
		  }
	      إذا (درون_array_p)
		{
		  error_init (loc, "initialization of flexible array "
			      "member in a nested context");
		  اكسر;
		}
	    }

	  /* Accept a string constant to initialize a subarray.  */
	  إذا (مقدار.مقدار != NULL_درخت
	      && fieldcode == ARRAY_TYPE
	      && INTEGRAL_TYPE_P (درخت_TYPE (fieldtype))
	      && string_flag)
	    مقدار.مقدار = orig_مقدار;
	  /* Otherwise, if we have come to a subaggregate,
	     and we don't have an element of its type, push into it.  */
	  وإلا إذا (مقدار.مقدار != NULL_درخت
		   && initialize_elementwise_p (fieldtype, مقدار.مقدار))
	    {
	      افزودن_init_level (loc, 1, braced_init_obstack);
	      استمر;
	    }

	  مقدار.مقدار = maybe_تقسیم_raw_داده (مقدار.مقدار, &raw_داده);
	  إذا (مقدار.مقدار)
	    {
	      افزودن_member_name (constructor_fields);
	      output_init_element (loc, مقدار.مقدار, مقدار.original_type,
				   strict_string, fieldtype,
				   constructor_fields, درست, implicit,
				   braced_init_obstack);
	      RESTORE_SPELLING_عمق (constructor_عمق);
	    }
	  وإلا
	    /* Do the bookkeeping for an element that was
	       directly output as a constructor.  */
	    {
	      /* For a record, keep track of end position of last field.  */
	      إذا (DECL_اندازه (constructor_fields))
		constructor_بیت_شاخص
		  = اندازه_binop_loc (درون_داد_location, PLUS_عبارت,
				    بیت_position (constructor_fields),
				    DECL_اندازه (constructor_fields));

	      /* If the current field was the first one not yet written out,
		 it isn't now, so update.  */
	      إذا (constructor_unfilled_fields == constructor_fields)
		{
		  constructor_unfilled_fields = DECL_CHAIN (constructor_fields);
		  /* Skip any nameless bit fields.  */
		  طالما (constructor_unfilled_fields != 0
			 && (DECL_UNNAMED_بیت_فیلد
			     (constructor_unfilled_fields)))
		    constructor_unfilled_fields =
		      DECL_CHAIN (constructor_unfilled_fields);
		}
	    }

	  constructor_fields = DECL_CHAIN (constructor_fields);
	  /* Skip any nameless bit fields at the beginning.  */
	  طالما (constructor_fields != NULL_درخت
		 && DECL_UNNAMED_بیت_فیلد (constructor_fields))
	    constructor_fields = DECL_CHAIN (constructor_fields);
	}
      وإلا إذا (درخت_کد (constructor_type) == UNION_TYPE)
	{
	  درخت fieldtype;
	  تعداد درخت_کد_2 fieldcode;

	  إذا (constructor_fields == NULL_درخت)
	    {
	      pedwarn_init (loc, 0,
			    "excess elements in union initializer");
	      اكسر;
	    }

	  fieldtype = درخت_TYPE (constructor_fields);
	  إذا (fieldtype != error_mark_گره)
	    fieldtype = TYPE_MAIN_VARIANT (fieldtype);
	  fieldcode = درخت_کد (fieldtype);

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
	  إذا (!درون_system_سرآیند_at (درون_داد_location) && !constructor_designated
	      && !(مقدار.مقدار && (integer_zerop (مقدار.مقدار)
				   || real_zerop (مقدار.مقدار))))
	    warning (OPT_Wtraditional, "traditional C rejects initialization "
		     "of unions");

	  /* Error for non-static initialization of a flexible array member.  */
	  إذا (fieldcode == ARRAY_TYPE
	      && !require_constant_مقدار
	      && TYPE_اندازه (fieldtype) == NULL_درخت)
	    {
	      error_init (loc, "non-static initialization of a flexible "
			  "array member");
	      اكسر;
	    }

	  /* Error for initialization of a flexible array member with
	     a string constant if the structure is in an array.  E.g.:
	     union U { int x; char y[]; };
	     union U s[] = { { 1, "foo" } };
	     is invalid.  */
	  إذا (string_flag
	      && fieldcode == ARRAY_TYPE
	      && constructor_عمق > 1
	      && TYPE_اندازه (fieldtype) == NULL_درخت)
	    {
	      منطقي درون_array_p = خطأ;
	      لكل (بنية constructor_پشته *p = constructor_پشته;
		   p && p->type; p = p->بعدی)
		إذا (درخت_کد (p->type) == ARRAY_TYPE)
		  {
		    درون_array_p = درست;
		    اكسر;
		  }
	      إذا (درون_array_p)
		{
		  error_init (loc, "initialization of flexible array "
			      "member in a nested context");
		  اكسر;
		}
	    }

	  /* Accept a string constant to initialize a subarray.  */
	  إذا (مقدار.مقدار != NULL_درخت
	      && fieldcode == ARRAY_TYPE
	      && INTEGRAL_TYPE_P (درخت_TYPE (fieldtype))
	      && string_flag)
	    مقدار.مقدار = orig_مقدار;
	  /* Otherwise, if we have come to a subaggregate,
	     and we don't have an element of its type, push into it.  */
	  وإلا إذا (مقدار.مقدار != NULL_درخت
		   && initialize_elementwise_p (fieldtype, مقدار.مقدار))
	    {
	      افزودن_init_level (loc, 1, braced_init_obstack);
	      استمر;
	    }

	  مقدار.مقدار = maybe_تقسیم_raw_داده (مقدار.مقدار, &raw_داده);
	  إذا (مقدار.مقدار)
	    {
	      افزودن_member_name (constructor_fields);
	      output_init_element (loc, مقدار.مقدار, مقدار.original_type,
				   strict_string, fieldtype,
				   constructor_fields, درست, implicit,
				   braced_init_obstack);
	      RESTORE_SPELLING_عمق (constructor_عمق);
	    }
	  وإلا
	    /* Do the bookkeeping for an element that was
	       directly output as a constructor.  */
	    {
	      constructor_بیت_شاخص = DECL_اندازه (constructor_fields);
	      constructor_unfilled_fields = DECL_CHAIN (constructor_fields);
	    }

	  constructor_fields = NULL_درخت;
	}
      وإلا إذا (درخت_کد (constructor_type) == ARRAY_TYPE)
	{
	  درخت elttype = TYPE_MAIN_VARIANT (درخت_TYPE (constructor_type));
	  تعداد درخت_کد_2 eltcode = درخت_کد (elttype);

	  /* Accept a string constant to initialize a subarray.  */
	  إذا (مقدار.مقدار != NULL_درخت
	      && eltcode == ARRAY_TYPE
	      && INTEGRAL_TYPE_P (درخت_TYPE (elttype))
	      && string_flag)
	    مقدار.مقدار = orig_مقدار;
	  /* Otherwise, if we have come to a subaggregate,
	     and we don't have an element of its type, push into it.  */
	  وإلا إذا (مقدار.مقدار != NULL_درخت
		   && initialize_elementwise_p (elttype, مقدار.مقدار))
	    {
	      افزودن_init_level (loc, 1, braced_init_obstack);
	      استمر;
	    }

	  إذا (constructor_max_شاخص != NULL_درخت
	      && (درخت_int_cst_lt (constructor_max_شاخص, constructor_شاخص)
		  || integer_all_onesp (constructor_max_شاخص))
	      /* For VLA we got an error already.  */
	      && !C_TYPE_VARIABLE_اندازه (constructor_type))
	    {
	      pedwarn_init (loc, 0,
			    "excess elements in array initializer");
	      اكسر;
	    }

	  إذا (مقدار.مقدار
	      && درخت_کد (مقدار.مقدار) == RAW_داده_CST
	      && RAW_داده_درازی (مقدار.مقدار) > 1
	      && (درخت_کد (elttype) == INTEGER_TYPE
		  || درخت_کد (elttype) == BITINT_TYPE)
	      && TYPE_PRECISION (elttype) == CHAR_بیت
	      && (constructor_max_شاخص == NULL_درخت
		  || درخت_int_cst_lt (constructor_شاخص,
				      constructor_max_شاخص)))
	    {
	      بیعلامت صحيح len = RAW_داده_درازی (مقدار.مقدار);
	      إذا (constructor_max_شاخص)
		{
		  widest_int w = wi::مقصد_widest (constructor_max_شاخص);
		  w -= wi::مقصد_widest (constructor_شاخص);
		  w += 1;
		  إذا (w < len)
		    len = w.مقصد_uhwi ();
		}
	      إذا (len < (بیعلامت) RAW_داده_درازی (مقدار.مقدار))
		{
		  raw_داده = copy_گره (مقدار.مقدار);
		  RAW_داده_درازی (raw_داده) -= len;
		  RAW_داده_اشاره_گر (raw_داده) += len;
		  RAW_داده_درازی (مقدار.مقدار) = len;
		}
	      درخت_TYPE (مقدار.مقدار) = elttype;
	      افزودن_array_bounds (درخت_مقصد_uhwi (constructor_شاخص));
	      output_init_element (loc, مقدار.مقدار, مقدار.original_type,
				   خطأ, elttype, constructor_شاخص, درست,
				   implicit, braced_init_obstack);
	      RESTORE_SPELLING_عمق (constructor_عمق);
	      constructor_شاخص
		= اندازه_binop_loc (درون_داد_location, PLUS_عبارت,
				  constructor_شاخص, bitsize_int (len));
	    }
	  وإلا
	    {
	      مقدار.مقدار = maybe_تقسیم_raw_داده (مقدار.مقدار, &raw_داده);
	      /* Now output the actual element.  */
	      إذا (مقدار.مقدار)
		{
		  افزودن_array_bounds (درخت_مقصد_uhwi (constructor_شاخص));
		  output_init_element (loc, مقدار.مقدار, مقدار.original_type,
				       strict_string, elttype,
				       constructor_شاخص, درست, implicit,
				       braced_init_obstack);
		  RESTORE_SPELLING_عمق (constructor_عمق);
		}

	      constructor_شاخص
		= اندازه_binop_loc (درون_داد_location, PLUS_عبارت,
				  constructor_شاخص, bitsize_one_گره);

	      إذا (!مقدار.مقدار)
		/* If we are doing the bookkeeping for an element that was
		   directly output as a constructor, we must update
		   constructor_unfilled_index.  */
		constructor_unfilled_شاخص = constructor_شاخص;
	    }
	}
      وإلا إذا (gnu_وکتور_type_p (constructor_type))
	{
	  درخت elttype = TYPE_MAIN_VARIANT (درخت_TYPE (constructor_type));

	  /* Do a basic check of initializer size.  Note that vectors
	     may not always have a fixed size derived from their type.  */
	  إذا (maybe_lt (درخت_مقصد_poly_uint64 (constructor_max_شاخص),
			درخت_مقصد_poly_uint64 (constructor_شاخص)))
	    {
	      /* Diagose VLA out-of-bounds as errors.  */
	      إذا (درخت_مقصد_poly_uint64 (constructor_max_شاخص).is_constant())
		pedwarn_init (loc, 0,
			      "excess elements in vector initializer");
	      وإلا
		error_init (loc, "excess elements in vector initializer");

	      اكسر;
	    }

	  مقدار.مقدار = maybe_تقسیم_raw_داده (مقدار.مقدار, &raw_داده);
	  /* Now output the actual element.  */
	  إذا (مقدار.مقدار)
	    {
	      إذا (درخت_کد (مقدار.مقدار) == وکتور_CST)
		elttype = TYPE_MAIN_VARIANT (constructor_type);
	      output_init_element (loc, مقدار.مقدار, مقدار.original_type,
				   strict_string, elttype,
				   constructor_شاخص, درست, implicit,
				   braced_init_obstack);
	    }

	  constructor_شاخص
	    = اندازه_binop_loc (درون_داد_location,
			      PLUS_عبارت, constructor_شاخص, bitsize_one_گره);

	  إذا (!مقدار.مقدار)
	    /* If we are doing the bookkeeping for an element that was
	       directly output as a constructor, we must update
	       constructor_unfilled_index.  */
	    constructor_unfilled_شاخص = constructor_شاخص;
	}

      /* Handle the sole element allowed in a braced initializer
	 for a scalar variable.  */
      وإلا إذا (constructor_type != error_mark_گره
	       && constructor_fields == NULL_درخت)
	{
	  pedwarn_init (loc, 0,
			"excess elements in scalar initializer");
	  اكسر;
	}
      وإلا
	{
	  مقدار.مقدار = maybe_تقسیم_raw_داده (مقدار.مقدار, &raw_داده);
	  إذا (مقدار.مقدار)
	    output_init_element (loc, مقدار.مقدار, مقدار.original_type,
				 strict_string, constructor_type,
				 NULL_درخت, درست, implicit,
				 braced_init_obstack);
	  constructor_fields = NULL_درخت;
	}

      /* Handle range initializers either at this level or anywhere higher
	 in the designator stack.  */
      إذا (constructor_range_پشته)
	{
	  بنية constructor_range_پشته *p, *range_پشته;
	  صحيح پایان = 0;

	  range_پشته = constructor_range_پشته;
	  constructor_range_پشته = 0;
	  طالما (constructor_پشته != range_پشته->پشته)
	    {
	      gcc_assert (constructor_پشته->implicit);
	      process_init_element (loc,
				    برداشت_init_level (loc, 1,
						    braced_init_obstack,
						    آخرین_init_list_comma),
				    درست, braced_init_obstack);
	    }
	  لكل (p = range_پشته;
	       !p->range_انتها || درخت_int_cst_equal (p->شاخص, p->range_انتها);
	       p = p->prev)
	    {
	      gcc_assert (constructor_پشته->implicit);
	      process_init_element (loc,
				    برداشت_init_level (loc, 1,
						    braced_init_obstack,
						    آخرین_init_list_comma),
				    درست, braced_init_obstack);
	    }

	  p->شاخص = اندازه_binop_loc (درون_داد_location,
				     PLUS_عبارت, p->شاخص, bitsize_one_گره);
	  إذا (درخت_int_cst_equal (p->شاخص, p->range_انتها) && !p->prev)
	    پایان = 1;

	  طالما (1)
	    {
	      constructor_شاخص = p->شاخص;
	      constructor_fields = p->fields;
	      إذا (پایان && p->range_انتها && p->شاخص == p->range_شروع)
		{
		  پایان = 0;
		  p->prev = 0;
		}
	      p = p->بعدی;
	      إذا (!p)
		اكسر;
	      پایان_implicit_inits (loc, braced_init_obstack);
	      افزودن_init_level (loc, 2, braced_init_obstack);
	      p->پشته = constructor_پشته;
	      إذا (p->range_انتها && درخت_int_cst_equal (p->شاخص, p->range_انتها))
		p->شاخص = p->range_شروع;
	    }

	  إذا (!پایان)
	    constructor_range_پشته = range_پشته;
	  استمر;
	}

      اكسر;
    }

  constructor_range_پشته = 0;

  إذا (raw_داده && RAW_داده_درازی (raw_داده))
    {
      gcc_assert (!string_flag && !was_designated);
      مقدار.مقدار = raw_داده;
      raw_داده = NULL_درخت;
      اذهب retry;
    }
}

/* Build a complete asm-statement, whose components are a CV_QUALIFIER
   (guaranteed to be 'volatile' or null) and ARGS (represented using
   an ASM_EXPR node).  */
درخت
build_asm_stmt (منطقي is_volatile, درخت آرگومانها)
{
  إذا (is_volatile)
    ASM_VOLATILE_P (آرگومانها) = 1;
  أرجع جمع_کن_stmt (آرگومانها);
}

/* Build an asm-expr, whose components are a STRING, some OUTPUTS,
   some INPUTS, and some CLOBBERS.  The latter three may be NULL.
   SIMPLE indicates whether there was anything at all after the
   string in the asm expression -- asm("blah") and asm("blah" : )
   are subtly different.  We use a ASM_EXPR node to represent this.
   LOC is the location of the asm, and IS_INLINE says whether this
   is asm inline.  */
درخت
build_asm_عبارت (location_t loc, درخت string, درخت outputs, درخت inputs,
		درخت clobbers, درخت labels, منطقي simple, منطقي is_inline)
{
  درخت دم;
  درخت آرگومانها;
  صحيح i;
  ثابت حرف *constraint;
  ثابت حرف **oconstraints;
  منطقي allows_mem, allows_reg, is_inout;
  صحيح ninputs, noutputs;

  ninputs = list_درازی (inputs);
  noutputs = list_درازی (outputs);
  oconstraints = (ثابت حرف **) alloca (noutputs * حجم (ثابت حرف *));

  string = resolve_asm_عملوند_نامها (string, outputs, inputs, labels);

  /* Remove output conversions that change the type but not the mode.  */
  لكل (i = 0, دم = outputs; دم; ++i, دم = درخت_CHAIN (دم))
    {
      درخت output = درخت_مقدار (دم);

      output = c_fully_fold (output, خطأ, عدم, درست);

      /* ??? Really, this should not be here.  Users should be using a
	 proper lvalue, dammit.  But there's a long history of using casts
	 in the output operands.  In cases like longlong.h, this becomes a
	 primitive form of typechecking -- if the cast can be removed, then
	 the output operand had a type of the proper width; otherwise we'll
	 get an error.  Gross, but ...  */
      STRIP_NOPS (output);

      إذا (!lvalue_or_else (loc, output, lv_asm))
	output = error_mark_گره;

      إذا (output != error_mark_گره
	  && (درخت_READONLY (output)
	      || TYPE_READONLY (درخت_TYPE (output))
	      || (رکورد_OR_UNION_TYPE_P (درخت_TYPE (output))
		  && C_TYPE_FIELDS_READONLY (درخت_TYPE (output)))))
	readonly_error (loc, output, lv_asm);

      constraint = درخت_STRING_اشاره_گر (درخت_مقدار (درخت_PURPOSE (دم)));
      oconstraints[i] = constraint;

      إذا (parse_output_constraint (&constraint, i, ninputs, noutputs,
				   &allows_mem, &allows_reg, &is_inout,
				   اشاره_تهی))
	{
	  /* If the operand is going to end up in memory,
	     mark it addressable.  */
	  إذا (!allows_reg && !c_mark_addressable (output))
	    output = error_mark_گره;
	  إذا (!(!allows_reg && allows_mem)
	      && output != error_mark_گره
	      && VOID_TYPE_P (درخت_TYPE (output)))
	    {
	      error_at (loc, "invalid use of void expression");
	      output = error_mark_گره;
	    }
	  إذا (allows_reg && current_function_decl == NULL_درخت)
	    {
	      error_at (loc, "constraint allows registers outside of "
			     "a function");
	      output = error_mark_گره;
	    }
	}
      وإلا
	output = error_mark_گره;

      إذا (current_function_decl == NULL_درخت && output != error_mark_گره)
	{
	  إذا (درخت_SIDE_EFFECTS (output))
	    {
	      error_at (loc, "side-effects in output operand outside "
			     "of a function");
	      output = error_mark_گره;
	    }
	  وإلا
	    {
	      درخت addr = build_unary_op (loc, ADDR_عبارت, output, خطأ);
	      إذا (addr == error_mark_گره)
		output = error_mark_گره;
	      وإلا إذا (!initializer_constant_valid_p (addr, درخت_TYPE (addr)))
		{
		  error_at (loc, "output operand outside of a function is not "
				 "constant");
		  output = error_mark_گره;
		}
	    }
	}
      وإلا إذا (output != error_mark_گره && جستجوی_رشته (constraint, "-"))
	{
	  error_at (loc, "%<-%> modifier used inside of a function");
	  output = error_mark_گره;
	}

      درخت_مقدار (دم) = output;
    }

  لكل (i = 0, دم = inputs; دم; ++i, دم = درخت_CHAIN (دم))
    {
      درخت درون_داد;

      constraint = درخت_STRING_اشاره_گر (درخت_مقدار (درخت_PURPOSE (دم)));
      درون_داد = درخت_مقدار (دم);

      إذا (parse_درون_داد_constraint (&constraint, i, ninputs, noutputs, 0,
				  oconstraints, &allows_mem, &allows_reg,
				  اشاره_تهی))
	{
	  /* If the operand is going to end up in memory,
	     mark it addressable.  */
	  إذا (!allows_reg && allows_mem)
	    {
	      درون_داد = c_fully_fold (درون_داد, خطأ, عدم, درست);

	      /* Strip the nops as we allow this case.  FIXME, this really
		 should be rejected or made deprecated.  */
	      STRIP_NOPS (درون_داد);
	      إذا (!c_mark_addressable (درون_داد))
		درون_داد = error_mark_گره;
	    }
	  وإلا
	    {
	      درون_داد = c_fully_fold (convert_lvalue_مقصد_rvalue (loc, درون_داد,
							      درست, خطأ),
				    خطأ, عدم);

	      إذا (درون_داد != error_mark_گره && VOID_TYPE_P (درخت_TYPE (درون_داد)))
		{
		  error_at (loc, "invalid use of void expression");
		  درون_داد = error_mark_گره;
		}
	    }
	  إذا (allows_reg && current_function_decl == NULL_درخت)
	    {
	      error_at (loc, "constraint allows registers outside of "
			     "a function");
	      درون_داد = error_mark_گره;
	    }
	  إذا (constraint[0] == ':' && درون_داد != error_mark_گره)
	    {
	      درخت t = درون_داد;
	      STRIP_NOPS (t);
	      إذا (درخت_کد (t) != ADDR_عبارت
		  || !(درخت_کد (درخت_عملوند (t, 0)) == FUNCTION_DECL
		       || (VAR_P (درخت_عملوند (t, 0))
			   && is_global_var (درخت_عملوند (t, 0)))))
		{
		  error_at (loc, "%<:%> constraint operand is not address "
				 "of a function or non-automatic variable");
		  درون_داد = error_mark_گره;
		}
	      وإلا إذا (درخت_کد (درخت_عملوند (t, 0)) == FUNCTION_DECL)
		suppress_warning (درخت_عملوند (t, 0), OPT_Wunused);
	    }
	}
      وإلا
	درون_داد = error_mark_گره;

      إذا (current_function_decl == NULL_درخت && درون_داد != error_mark_گره)
	{
	  إذا (درخت_SIDE_EFFECTS (درون_داد))
	    {
	      error_at (loc, "side-effects in input operand outside "
			     "of a function");
	      درون_داد = error_mark_گره;
	    }
	  وإلا
	    {
	      درخت tem = درون_داد;
	      إذا (allows_mem && lvalue_p (درون_داد))
		tem = build_unary_op (loc, ADDR_عبارت, درون_داد, خطأ);
	      إذا (!initializer_constant_valid_p (tem, درخت_TYPE (tem)))
		{
		  error_at (loc, "input operand outside of a function is not "
				 "constant");
		  درون_داد = error_mark_گره;
		}
	    }
	}
      وإلا إذا (درون_داد != error_mark_گره && جستجوی_رشته (constraint, "-"))
	{
	  error_at (loc, "%<-%> modifier used inside of a function");
	  درون_داد = error_mark_گره;
	}

      درخت_مقدار (دم) = درون_داد;
    }

  آرگومانها = build_stmt (loc, ASM_عبارت, string, outputs, inputs, clobbers, labels);

  /* asm statements without outputs, including simple ones, are treated
     as volatile.  */
  ASM_BASIC_P (آرگومانها) = simple;
  ASM_VOLATILE_P (آرگومانها) = (noutputs == 0);
  ASM_INLINE_P (آرگومانها) = is_inline;

  أرجع آرگومانها;
}

/* Generate a goto statement to LABEL.  LOC is the location of the
   GOTO.  */

درخت
c_پایان_goto_label (location_t loc, درخت label)
{
  درخت decl = lookup_label_for_goto (loc, label);
  إذا (!decl)
    أرجع NULL_درخت;
  درخت_استفاده_شده (decl) = 1;
  mark_decl_استفاده_شده (decl, خطأ);
  {
    جمع_کن_stmt (build_predict_عبارت (PRED_GOTO, NOT_گرفته));
    درخت t = build1 (GOTO_عبارت, void_type_گره, decl);
    مجموعه_عبارت_LOCATION (t, loc);
    أرجع جمع_کن_stmt (t);
  }
}

/* Generate a computed goto statement to EXPR.  LOC is the location of
   the GOTO.  */

درخت
c_پایان_goto_ptr (location_t loc, c_عبارت val)
{
  درخت عبارت = val.مقدار;
  درخت t;
  pedwarn (loc, OPT_Wpedantic, "ISO C forbids %<goto *expr;%>");
  إذا (عبارت != error_mark_گره
      && !اشاره_گر_TYPE_P (درخت_TYPE (عبارت))
      && !null_اشاره_گر_constant_p (عبارت))
    {
      error_at (val.get_location (),
		"computed goto must be pointer type");
      عبارت = build_zero_cst (ptr_type_گره);
    }
  عبارت = c_fully_fold (عبارت, خطأ, عدم);
  عبارت = convert (ptr_type_گره, عبارت);
  t = build1 (GOTO_عبارت, void_type_گره, عبارت);
  مجموعه_عبارت_LOCATION (t, loc);
  أرجع جمع_کن_stmt (t);
}

/* Generate a C `return' statement.  RETVAL is the expression for what
   to return, or a null pointer for `return;' with no value.  LOC is
   the location of the return statement, or the location of the expression,
   if the statement has any.  If ORIGTYPE is not NULL_TREE, it
   is the original type of RETVAL.  MUSTTAIL_P indicates a musttail
   attribute.  */

درخت
c_پایان_return (location_t loc, درخت retval, درخت origtype, منطقي musttail_p)
{
  درخت valtype = درخت_TYPE (درخت_TYPE (current_function_decl)), ret_stmt;
  منطقي no_warning = خطأ;
  منطقي npc = خطأ;

  /* Use the expansion point to handle cases such as returning NULL
     in a function returning void.  */
  location_t xloc = expansion_نقطه_location_if_درون_system_سرآیند (loc);

  إذا (درخت_THIS_VOLATILE (current_function_decl))
    warning_at (xloc, 0,
		"function declared %<noreturn%> has a %<return%> statement");

  مجموعه_musttail_on_return (retval, xloc, musttail_p);

  إذا (retval)
    {
      درخت semantic_type = NULL_درخت;
      npc = null_اشاره_گر_constant_p (retval);
      إذا (درخت_کد (retval) == EXCESS_PRECISION_عبارت)
	{
	  semantic_type = درخت_TYPE (retval);
	  retval = درخت_عملوند (retval, 0);
	}
      retval = c_fully_fold (retval, خطأ, عدم);
      إذا (semantic_type
	  && valtype != NULL_درخت
	  && درخت_کد (valtype) != VOID_TYPE)
	retval = build1 (EXCESS_PRECISION_عبارت, semantic_type, retval);
    }

  إذا (!retval)
    {
      current_function_returns_null = 1;
      إذا ((warn_return_type >= 0 || flag_isoc99)
	  && valtype != NULL_درخت && درخت_کد (valtype) != VOID_TYPE)
	{
	  no_warning = درست;
	  إذا (emit_diagnostic (flag_isoc99
			       ? diagnostics::نوع::permerror
			       : diagnostics::نوع::warning,
			       loc, OPT_Wreturn_mismatch,
			       "%<return%> with no value,"
			       " in function returning non-void"))
	    inform (DECL_منبع_LOCATION (current_function_decl),
		    "declared here");
	}
    }
  وإلا إذا (valtype == NULL_درخت || VOID_TYPE_P (valtype))
    {
      current_function_returns_null = 1;
      منطقي warned_اینجا;
      إذا (درخت_کد (درخت_TYPE (retval)) != VOID_TYPE)
	warned_اینجا = permerror_opt
	  (xloc, OPT_Wreturn_mismatch,
	   "%<return%> with a value, in function returning void");
      وإلا
	warned_اینجا = pedwarn
	  (xloc, OPT_Wpedantic, "ISO C forbids "
	   "%<return%> with expression, in function returning void");
      إذا (warned_اینجا)
	inform (DECL_منبع_LOCATION (current_function_decl),
		"declared here");
    }
  وإلا
    {
      درخت t = convert_for_assignment (loc, UNKNOWN_LOCATION, valtype,
				       retval, origtype, ic_return,
				       npc, NULL_درخت, NULL_درخت, 0);
      درخت res = DECL_نتیجه (current_function_decl);
      درخت inner;
      منطقي save;

      current_function_returns_مقدار = 1;
      إذا (t == error_mark_گره)
	{
	  /* Suppress -Wreturn-type for this function.  */
	  إذا (warn_return_type)
	    suppress_warning (current_function_decl, OPT_Wreturn_type);
	  أرجع NULL_درخت;
	}

      save = درون_late_دودویی_op;
      إذا (C_BOOLEAN_TYPE_P (درخت_TYPE (res))
	  || درخت_کد (درخت_TYPE (res)) == COMPLEX_TYPE
	  || (SCALAR_FLOAT_TYPE_P (درخت_TYPE (t))
	      && (درخت_کد (درخت_TYPE (res)) == INTEGER_TYPE
		  || درخت_کد (درخت_TYPE (res)) == ENUMERAL_TYPE)
	      && sanitize_flags_p (SANITIZE_FLOAT_CAST)))
        درون_late_دودویی_op = درست;
      inner = t = convert (درخت_TYPE (res), t);
      درون_late_دودویی_op = save;

      /* Strip any conversions, additions, and subtractions, and see if
	 we are returning the address of a local variable.  Warn if so.  */
      طالما (1)
	{
	  بدل (درخت_کد (inner))
	    {
	    CASE_CONVERT:
	    حالة NON_LVALUE_عبارت:
	    حالة PLUS_عبارت:
	    حالة اشاره_گر_PLUS_عبارت:
	      inner = درخت_عملوند (inner, 0);
	      استمر;

	    حالة MINUS_عبارت:
	      /* If the second operand of the MINUS_EXPR has a pointer
		 type (or is converted from it), this may be valid, so
		 don't give a warning.  */
	      {
		درخت op1 = درخت_عملوند (inner, 1);

		طالما (!اشاره_گر_TYPE_P (درخت_TYPE (op1))
		       && (CONVERT_عبارت_P (op1)
			   || درخت_کد (op1) == NON_LVALUE_عبارت))
		  op1 = درخت_عملوند (op1, 0);

		إذا (اشاره_گر_TYPE_P (درخت_TYPE (op1)))
		  اكسر;

		inner = درخت_عملوند (inner, 0);
		استمر;
	      }

	    حالة ADDR_عبارت:
	      inner = درخت_عملوند (inner, 0);

	      طالما (REFERENCE_CLASS_P (inner)
		     && !غیرمستقیم_REF_P (inner))
		inner = درخت_عملوند (inner, 0);

	      إذا (DECL_P (inner)
		  && !DECL_EXTERNAL (inner)
		  && DECL_CONTEXT (inner) == current_function_decl
		  && اشاره_گر_TYPE_P (درخت_TYPE (درخت_TYPE (current_function_decl))))
		{
		  إذا (درخت_کد (inner) == LABEL_DECL)
		    warning_at (loc, OPT_Wreturn_local_addr,
				"function returns address of label");
		  وإلا إذا (درخت_کد (inner) == FUNCTION_DECL
			   && (C_FUNC_NONLOCAL_CONTEXT (inner)
			       || !DECL_INITIAL (inner)))
		    warning_at (loc, OPT_Wreturn_local_addr,
				"function returns address of nested function "
				"referencing local context");
		  وإلا إذا (درخت_کد (inner) != FUNCTION_DECL
			   && !درخت_STATIC (inner))
		    {
		      warning_at (loc, OPT_Wreturn_local_addr,
				  "function returns address of local variable");
		      درخت zero = build_zero_cst (درخت_TYPE (res));
		      t = build2 (COMPOUND_عبارت, درخت_TYPE (res), t, zero);
		    }
		}
	      اكسر;

	    افتراضي:
	      اكسر;
	    }

	  اكسر;
	}

      retval = build2 (MODIFY_عبارت, درخت_TYPE (res), res, t);
      مجموعه_عبارت_LOCATION (retval, loc);

      إذا (warn_sequence_نقطه)
	verify_sequence_points (retval);
    }

  ret_stmt = build_stmt (loc, RETURN_عبارت, retval);
  إذا (no_warning)
    suppress_warning (ret_stmt, OPT_Wreturn_type);
  أرجع جمع_کن_stmt (ret_stmt);
}

بنية c_switch {
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
  بنية c_spot_bindings *bindings;

  /* Whether the switch includes any break statements.  */
  منطقي break_stmt_دیده_p;

  /* The next node on the stack.  */
  بنية c_switch *بعدی;

  /* Remember whether the controlling expression had boolean type
     before integer promotions for the sake of -Wswitch-bool.  */
  منطقي bool_cond_p;
};

/* A stack of the currently active switch statements.  The innermost
   switch statement is on the top of the stack.  There is no need to
   mark the stack for garbage collection because it is only active
   during the processing of the body of a function, and we never
   collect at that point.  */

بنية c_switch *c_switch_پشته;

/* Start a C switch statement, testing expression EXP.  Return the new
   SWITCH_STMT.  SWITCH_LOC is the location of the `switch'.
   SWITCH_COND_LOC is the location of the switch's condition.
   EXPLICIT_CAST_P is true if the expression EXP has an explicit cast.  */

درخت
c_شروع_switch (location_t switch_loc,
		location_t switch_cond_loc,
		درخت نمایی_تابع, منطقي explicit_cast_p, درخت switch_name)
{
  درخت orig_type = error_mark_گره;
  منطقي bool_cond_p = خطأ;
  بنية c_switch *cs;

  إذا (نمایی_تابع != error_mark_گره)
    {
      orig_type = درخت_TYPE (نمایی_تابع);

      إذا (!INTEGRAL_TYPE_P (orig_type))
	{
	  إذا (orig_type != error_mark_گره)
	    {
	      error_at (switch_cond_loc, "switch quantity not an integer");
	      orig_type = error_mark_گره;
	    }
	  نمایی_تابع = integer_zero_گره;
	}
      وإلا
	{
	  درخت type = TYPE_MAIN_VARIANT (orig_type);
	  درخت e = نمایی_تابع;

	  /* Warn if the condition has boolean value.  */
	  طالما (درخت_کد (e) == COMPOUND_عبارت)
	    e = درخت_عملوند (e, 1);

	  إذا ((C_BOOLEAN_TYPE_P (type)
	       || truth_مقدار_p (درخت_کد (e)))
	      /* Explicit cast to int suppresses this warning.  */
	      && !(درخت_کد (type) == INTEGER_TYPE
		   && explicit_cast_p))
	    bool_cond_p = درست;

	  إذا (!درون_system_سرآیند_at (درون_داد_location)
	      && (type == long_integer_type_گره
		  || type == long_unsigned_type_گره))
	    warning_at (switch_cond_loc,
			OPT_Wtraditional, "%<long%> switch expression not "
			"converted to %<int%> in ISO C");

	  نمایی_تابع = c_fully_fold (نمایی_تابع, خطأ, عدم);
	  نمایی_تابع = default_conversion (نمایی_تابع);

	  إذا (warn_sequence_نقطه)
	    verify_sequence_points (نمایی_تابع);
	}
    }

  /* Add this new SWITCH_STMT to the stack.  */
  cs = XNEW (بنية c_switch);
  cs->switch_stmt = build_stmt (switch_loc, SWITCH_STMT, نمایی_تابع,
				NULL_درخت, orig_type, NULL_درخت, switch_name);
  cs->orig_type = orig_type;
  cs->cases = splay_درخت_new (case_compare, عدم, عدم);
  cs->bindings = c_get_switch_bindings ();
  cs->break_stmt_دیده_p = خطأ;
  cs->bool_cond_p = bool_cond_p;
  cs->بعدی = c_switch_پشته;
  c_switch_پشته = cs;

  أرجع جمع_کن_stmt (cs->switch_stmt);
}

/* Process a case label at location LOC, with attributes ATTRS.  */

درخت
do_case (location_t loc, درخت کم_مقدار, درخت بالا_مقدار, درخت attrs)
{
  درخت label = NULL_درخت;

  إذا (کم_مقدار && درخت_کد (کم_مقدار) != INTEGER_CST)
    {
      کم_مقدار = c_fully_fold (کم_مقدار, خطأ, عدم);
      إذا (درخت_کد (کم_مقدار) == INTEGER_CST)
	pedwarn (loc, OPT_Wpedantic,
		 "case label is not an integer constant expression");
    }

  إذا (بالا_مقدار && درخت_کد (بالا_مقدار) != INTEGER_CST)
    {
      بالا_مقدار = c_fully_fold (بالا_مقدار, خطأ, عدم);
      إذا (درخت_کد (بالا_مقدار) == INTEGER_CST)
	pedwarn (درون_داد_location, OPT_Wpedantic,
		 "case label is not an integer constant expression");
    }

  إذا (c_switch_پشته == عدم)
    {
      إذا (کم_مقدار)
	error_at (loc, "case label not within a switch statement");
      وإلا
	error_at (loc, "%<default%> label not within a switch statement");
      أرجع NULL_درخت;
    }

  إذا (c_check_switch_jump_warnings (c_switch_پشته->bindings,
				    عبارت_LOCATION (c_switch_پشته->switch_stmt),
				    loc))
    أرجع NULL_درخت;

  label = c_جمع_کن_case_label (loc, c_switch_پشته->cases,
			    SWITCH_STMT_COND (c_switch_پشته->switch_stmt),
			    کم_مقدار, بالا_مقدار, attrs);
  إذا (label == error_mark_گره)
    label = NULL_درخت;
  أرجع label;
}

/* Finish the switch statement.  TYPE is the original type of the
   controlling expression of the switch, or NULL_TREE.  */

فراغ
c_پایان_switch (درخت body, درخت type)
{
  بنية c_switch *cs = c_switch_پشته;
  location_t switch_location;

  SWITCH_STMT_BODY (cs->switch_stmt) = body;

  /* Emit warnings as needed.  */
  switch_location = عبارت_LOCATION (cs->switch_stmt);
  c_do_switch_warnings (cs->cases, switch_location,
			type ? type : SWITCH_STMT_TYPE (cs->switch_stmt),
			SWITCH_STMT_COND (cs->switch_stmt), cs->bool_cond_p);
  إذا (c_switch_covers_all_cases_p (cs->cases,
				   SWITCH_STMT_TYPE (cs->switch_stmt)))
    SWITCH_STMT_ALL_CASES_P (cs->switch_stmt) = 1;
  SWITCH_STMT_NO_BREAK_P (cs->switch_stmt) = !cs->break_stmt_دیده_p;

  /* Pop the stack.  */
  c_switch_پشته = cs->بعدی;
  splay_درخت_delete (cs->cases);
  c_release_switch_bindings (cs->bindings);
  XDELETE (cs);
}

/* Emit an if statement.  IF_LOCUS is the location of the 'if'.  COND,
   THEN_BLOCK and ELSE_BLOCK are expressions to be used; ELSE_BLOCK
   may be null.  */

فراغ
c_پایان_if_stmt (location_t if_locus, درخت cond, درخت then_بلوک,
		  درخت else_بلوک)
{
  درخت stmt;

  stmt = build3 (COND_عبارت, void_type_گره, cond, then_بلوک, else_بلوک);
  مجموعه_عبارت_LOCATION (stmt, if_locus);
  جمع_کن_stmt (stmt);
}

درخت
c_پایان_bc_stmt (location_t loc, درخت label, منطقي is_break, درخت name)
{
  /* In switch statements break is sometimes stylistically used after
     a return statement.  This can lead to spurious warnings about
     control reaching the end of a non-void function when it is
     inlined.  Note that we are calling block_may_fallthru with
     language specific tree nodes; this works because
     block_may_fallthru returns true when given something it does not
     understand.  */
  منطقي skip = !بلوک_may_fallthru (cur_stmt_list);

  إذا (is_break)
    بدل (درون_statement & ~درون_NAMED_STMT)
      {
      حالة 0:
	error_at (loc, "break statement not within loop or switch");
	أرجع NULL_درخت;
      حالة درون_OMP_بلوک:
	error_at (loc, "invalid exit from OpenMP structured block");
	أرجع NULL_درخت;
      حالة درون_OMP_FOR:
	error_at (loc, "break statement used with OpenMP for loop");
	أرجع NULL_درخت;
      حالة درون_ITERATION_STMT:
      حالة درون_OBJC_FOREACH:
	اكسر;
      افتراضي:
	gcc_assert (درون_statement & درون_SWITCH_STMT);
	c_switch_پشته->break_stmt_دیده_p = درست;
	اكسر;
      }
  وإلا
    بدل (درون_statement & ~(درون_SWITCH_STMT | درون_NAMED_STMT))
      {
      حالة 0:
	error_at (loc, "continue statement not within a loop");
	أرجع NULL_درخت;
      حالة درون_OMP_بلوک:
	error_at (loc, "invalid exit from OpenMP structured block");
	أرجع NULL_درخت;
      حالة درون_ITERATION_STMT:
      حالة درون_OMP_FOR:
      حالة درون_OBJC_FOREACH:
	اكسر;
      افتراضي:
	gcc_unreachable ();
      }

  إذا (skip)
    أرجع NULL_درخت;
  وإلا إذا ((درون_statement & درون_OBJC_FOREACH)
	   && !(is_break && (درون_statement & درون_SWITCH_STMT))
	   && name == NULL_درخت)
    {
      /* The foreach expander produces low-level code using gotos instead
	 of a structured loop construct.  */
      gcc_assert (label);
      أرجع جمع_کن_stmt (build_stmt (loc, GOTO_عبارت, label));
    }
  وإلا إذا (name && C_DECL_LOOP_NAME (name) && C_DECL_SWITCH_NAME (name))
    {
      label = DECL_CHAIN (name);
      إذا (!is_break)
	label = DECL_CHAIN (label);
      /* Foreach expander from some outer level.  */
      أرجع جمع_کن_stmt (build_stmt (loc, GOTO_عبارت, label));
    }
  أرجع جمع_کن_stmt (build_stmt (loc, is_break ? BREAK_STMT : CONTINUE_STMT,
			       name));
}

/* A helper routine for c_process_expr_stmt and c_finish_stmt_expr.  */

ساكن فراغ
emit_side_effect_warnings (location_t loc, درخت عبارت)
{
  maybe_warn_nodiscard (loc, عبارت);
  إذا (!warn_استفادهنشده_مقدار)
    أرجع;
  إذا (عبارت == error_mark_گره)
    ;
  وإلا إذا (!درخت_SIDE_EFFECTS (عبارت))
    {
      إذا (!VOID_TYPE_P (درخت_TYPE (عبارت))
	  && !warning_suppressed_p (عبارت, OPT_Wunused_مقدار))
	warning_at (loc, OPT_Wunused_مقدار, "statement with no effect");
    }
  وإلا إذا (درخت_کد (عبارت) == COMPOUND_عبارت)
    {
      درخت r = عبارت;
      location_t cloc = loc;
      طالما (درخت_کد (r) == COMPOUND_عبارت)
	{
	  إذا (عبارت_HAS_LOCATION (r))
	    cloc = عبارت_LOCATION (r);
	  r = درخت_عملوند (r, 1);
	}
      إذا (!درخت_SIDE_EFFECTS (r)
	  && !VOID_TYPE_P (درخت_TYPE (r))
	  && !CONVERT_عبارت_P (r)
	  && !warning_suppressed_p (r, OPT_Wunused_مقدار)
	  && !warning_suppressed_p (عبارت, OPT_Wunused_مقدار))
	warning_at (cloc, OPT_Wunused_مقدار,
		    "right-hand operand of comma expression has no effect");
    }
  وإلا
    warn_if_استفادهنشده_مقدار (عبارت, loc);
}

/* Process an expression as if it were a complete statement.  Emit
   diagnostics, but do not call ADD_STMT.  LOC is the location of the
   statement.  */

درخت
c_process_عبارت_stmt (location_t loc, درخت عبارت)
{
  درخت exprv;

  إذا (!عبارت)
    أرجع NULL_درخت;

  عبارت = c_fully_fold (عبارت, خطأ, عدم);

  إذا (warn_sequence_نقطه)
    verify_sequence_points (عبارت);

  إذا (درخت_TYPE (عبارت) != error_mark_گره
      && !COMPLETE_OR_VOID_TYPE_P (درخت_TYPE (عبارت))
      && درخت_کد (درخت_TYPE (عبارت)) != ARRAY_TYPE)
    error_at (loc, "expression statement has incomplete type");

  /* If we're not processing a statement expression, warn about unused values.
     Warnings for statement expressions will be emitted later, once we figure
     out which is the result.  */
  إذا (!STATEMENT_LIST_STMT_عبارت (cur_stmt_list)
      && (warn_استفادهنشده_مقدار || warn_استفادهنشده_نتیجه))
    emit_side_effect_warnings (عبارت_LOC_OR_LOC (عبارت, loc), عبارت);

  exprv = عبارت;
  طالما (درخت_کد (exprv) == COMPOUND_عبارت)
    exprv = درخت_عملوند (exprv, 1);
  طالما (CONVERT_عبارت_P (exprv))
    exprv = درخت_عملوند (exprv, 0);
  إذا (DECL_P (exprv)
      || handled_component_p (exprv)
      || درخت_کد (exprv) == ADDR_عبارت)
    mark_exp_read (exprv);

  /* If the expression is not of a type to which we cannot assign a line
     number, wrap the thing in a no-op NOP_EXPR.  */
  إذا (DECL_P (عبارت) || CONSTANT_CLASS_P (عبارت))
    {
      عبارت = build1 (NOP_عبارت, درخت_TYPE (عبارت), عبارت);
      مجموعه_عبارت_LOCATION (عبارت, loc);
    }

  أرجع عبارت;
}

/* Emit an expression as a statement.  LOC is the location of the
   expression.  */

درخت
c_پایان_عبارت_stmt (location_t loc, درخت عبارت)
{
  إذا (عبارت)
    أرجع جمع_کن_stmt (c_process_عبارت_stmt (loc, عبارت));
  وإلا
    أرجع عدم;
}

/* Do the opposite and emit a statement as an expression.  To begin,
   create a new binding level and return it.  */

درخت
c_begin_stmt_عبارت (فراغ)
{
  درخت ret;

  /* We must force a BLOCK for this level so that, if it is not expanded
     later, there is a way to turn off the entire subtree of blocks that
     are contained in it.  */
  keep_بعدی_level ();
  ret = c_begin_compound_stmt (درست);

  c_bindings_شروع_stmt_عبارت (c_switch_پشته == عدم
			      ? عدم
			      : c_switch_پشته->bindings);

  /* Mark the current statement list as belonging to a statement list.  */
  STATEMENT_LIST_STMT_عبارت (ret) = 1;

  أرجع ret;
}

/* LOC is the location of the compound statement to which this body
   belongs.  */

درخت
c_پایان_stmt_عبارت (location_t loc, درخت body)
{
  درخت آخرین, type, tmp, val;
  درخت *آخرین_p;

  body = c_انتها_compound_stmt (loc, body, درست);

  c_bindings_انتها_stmt_عبارت (c_switch_پشته == عدم
			    ? عدم
			    : c_switch_پشته->bindings);

  /* Locate the last statement in BODY.  See c_end_compound_stmt
     about always returning a BIND_EXPR.  */
  آخرین_p = &BIND_عبارت_BODY (body);
  آخرین = BIND_عبارت_BODY (body);

 continue_searching:
  إذا (درخت_کد (آخرین) == STATEMENT_LIST)
    {
      درخت_stmt_iterator l = tsi_آخرین (آخرین);

      طالما (!tsi_انتها_p (l) && درخت_کد (tsi_stmt (l)) == DEBUG_BEGIN_STMT)
	tsi_prev (&l);

      /* This can happen with degenerate cases like ({ }).  No value.  */
      إذا (tsi_انتها_p (l))
	أرجع body;

      /* If we're supposed to generate side effects warnings, process
	 all of the statements except the last.  */
      إذا (warn_استفادهنشده_مقدار || warn_استفادهنشده_نتیجه)
	{
	  لكل (درخت_stmt_iterator i = tsi_شروع (آخرین);
	       tsi_stmt (i) != tsi_stmt (l); tsi_بعدی (&i))
	    {
	      location_t tloc;
	      درخت t = tsi_stmt (i);

	      tloc = عبارت_HAS_LOCATION (t) ? عبارت_LOCATION (t) : loc;
	      emit_side_effect_warnings (tloc, t);
	    }
	}
      آخرین_p = tsi_stmt_ptr (l);
      آخرین = *آخرین_p;
    }

  /* If the end of the list is exception related, then the list was split
     by a call to push_cleanup.  Continue searching.  */
  إذا (درخت_کد (آخرین) == TRY_FINALLY_عبارت
      || درخت_کد (آخرین) == TRY_CATCH_عبارت)
    {
      آخرین_p = &درخت_عملوند (آخرین, 0);
      آخرین = *آخرین_p;
      اذهب continue_searching;
    }

  إذا (آخرین == error_mark_گره)
    أرجع آخرین;

  /* In the case that the BIND_EXPR is not necessary, return the
     expression out from inside it.  */
  إذا ((آخرین == BIND_عبارت_BODY (body)
       /* Skip nested debug stmts.  */
       || آخرین == عبارت_اولی (BIND_عبارت_BODY (body)))
      && BIND_عبارت_VARS (body) == عدم)
    {
      /* Even if this looks constant, do not allow it in a constant
	 expression.  */
      آخرین = c_wrap_maybe_const (آخرین, درست);
      /* Do not warn if the return value of a statement expression is
	 unused.  */
      suppress_warning (آخرین, OPT_Wunused);
      أرجع آخرین;
    }

  /* Extract the type of said expression.  */
  type = درخت_TYPE (آخرین);

  /* If we're not returning a value at all, then the BIND_EXPR that
     we already have is a fine expression to return.  */
  إذا (!type || VOID_TYPE_P (type))
    أرجع body;

  /* Now that we've located the expression containing the value, it seems
     silly to make voidify_wrapper_expr repeat the process.  Create a
     temporary of the appropriate type and stick it in a TARGET_EXPR.  */
  tmp = create_tmp_var_raw (type);

  /* Unwrap a no-op NOP_EXPR as added by c_finish_expr_stmt.  This avoids
     tree_expr_nonnegative_p giving up immediately.  */
  val = آخرین;
  إذا (درخت_کد (val) == NOP_عبارت
      && درخت_TYPE (val) == درخت_TYPE (درخت_عملوند (val, 0)))
    val = درخت_عملوند (val, 0);

  *آخرین_p = build2 (MODIFY_عبارت, void_type_گره, tmp, val);
  مجموعه_عبارت_LOCATION (*آخرین_p, عبارت_LOCATION (آخرین));

  {
    درخت t = build4 (هدف_عبارت, type, tmp, body, NULL_درخت, NULL_درخت);
    مجموعه_عبارت_LOCATION (t, loc);
    أرجع t;
  }
}

/* Begin and end compound statements.  This is as simple as pushing
   and popping new statement lists from the tree.  */

درخت
c_begin_compound_stmt (منطقي do_scope)
{
  درخت stmt = افزودن_stmt_list ();
  إذا (do_scope)
    افزودن_scope ();
  أرجع stmt;
}

/* End a compound statement.  STMT is the statement.  LOC is the
   location of the compound statement-- this is usually the location
   of the opening brace.  */

درخت
c_انتها_compound_stmt (location_t loc, درخت stmt, منطقي do_scope)
{
  درخت بلوک = عدم;

  إذا (do_scope)
    {
      إذا (c_dialect_objc ())
	objc_clear_super_receiver ();
      بلوک = برداشت_scope ();
    }

  stmt = برداشت_stmt_list (stmt);
  stmt = c_build_bind_عبارت (loc, بلوک, stmt);

  /* If this compound statement is nested immediately inside a statement
     expression, then force a BIND_EXPR to be created.  Otherwise we'll
     do the wrong thing for ({ { 1; } }) or ({ 1; { } }).  In particular,
     STATEMENT_LISTs merge, and thus we can lose track of what statement
     was really last.  */
  إذا (building_stmt_list_p ()
      && STATEMENT_LIST_STMT_عبارت (cur_stmt_list)
      && درخت_کد (stmt) != BIND_عبارت)
    {
      stmt = build3 (BIND_عبارت, void_type_گره, عدم, stmt, عدم);
      درخت_SIDE_EFFECTS (stmt) = 1;
      مجموعه_عبارت_LOCATION (stmt, loc);
    }

  أرجع stmt;
}

/* Queue a cleanup.  CLEANUP is an expression/statement to be executed
   when the current scope is exited.  EH_ONLY is true when this is not
   meant to apply to normal control flow transfer.  */

فراغ
افزودن_cleanup (درخت decl, درخت cleanup, منطقي eh_only)
{
  تعداد درخت_کد_2 کد;
  درخت stmt, list;
  منطقي stmt_عبارت;

  کد = eh_only ? TRY_CATCH_عبارت : TRY_FINALLY_عبارت;
  stmt = build_stmt (DECL_منبع_LOCATION (decl), کد, عدم, cleanup);
  جمع_کن_stmt (stmt);
  stmt_عبارت = STATEMENT_LIST_STMT_عبارت (cur_stmt_list);
  list = افزودن_stmt_list ();
  درخت_عملوند (stmt, 0) = list;
  STATEMENT_LIST_STMT_عبارت (list) = stmt_عبارت;
}

/* Build a vector comparison of ARG0 and ARG1 using CODE opcode
   into a value of TYPE type.  Comparison is done via VEC_COND_EXPR.  */

ساكن درخت
build_vec_cmp (درخت_کد_2 کد, درخت type,
	       درخت arg0, درخت arg1)
{
  درخت zero_vec = build_zero_cst (type);
  درخت minus_one_vec = build_minus_one_cst (type);
  درخت cmp_type = truth_type_for (درخت_TYPE (arg0));
  درخت cmp = build2 (کد, cmp_type, arg0, arg1);
  أرجع build3 (VEC_COND_عبارت, type, cmp, minus_one_vec, zero_vec);
}

/* Possibly warn about an address of OP never being NULL in a comparison
   operation CODE involving null.  */

ساكن فراغ
maybe_warn_for_null_آدرس (location_t loc, درخت op, درخت_کد_2 کد)
{
  /* Prevent warnings issued for macro expansion.  */
  إذا (!warn_آدرس
      || warning_suppressed_p (op, OPT_Waddress)
      || from_macro_expansion_at (loc))
    أرجع;

  إذا (درخت_کد (op) == NOP_عبارت)
    {
      /* Allow casts to intptr_t to suppress the warning.  */
      درخت type = درخت_TYPE (op);
      إذا (درخت_کد (type) == INTEGER_TYPE)
	أرجع;
      op = درخت_عملوند (op, 0);
    }

  إذا (درخت_کد (op) == اشاره_گر_PLUS_عبارت)
    {
      /* Allow a cast to void* to suppress the warning.  */
      درخت type = درخت_TYPE (درخت_TYPE (op));
      إذا (VOID_TYPE_P (type))
	أرجع;

      /* Adding any value to a null pointer, including zero, is undefined
	 in C.  This includes the expression &p[0] where p is the null
	 pointer, although &p[0] will have been folded to p by this point
	 and so not diagnosed.  */
      إذا (کد == EQ_عبارت)
	warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<false%> "
		    "for the pointer operand in %qE must not be NULL",
		    op);
      وإلا
	warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<true%> "
		    "for the pointer operand in %qE must not be NULL",
		    op);

      أرجع;
    }

  إذا (درخت_کد (op) != ADDR_عبارت)
    أرجع;

  op = درخت_عملوند (op, 0);

  إذا (درخت_کد (op) == IMAGPART_عبارت
      || درخت_کد (op) == REALPART_عبارت)
    {
      /* The address of either complex part may not be null.  */
      إذا (کد == EQ_عبارت)
	warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<false%> "
		    "for the address of %qE will never be NULL",
		    op);
      وإلا
	warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<true%> "
		    "for the address of %qE will never be NULL",
		    op);
      أرجع;
    }

  /* Set to true in the loop below if OP dereferences is operand.
     In such a case the ultimate target need not be a decl for
     the null [in]equality test to be constant.  */
  منطقي deref = خطأ;

  /* Get the outermost array or object, or member.  */
  طالما (handled_component_p (op))
    {
      إذا (درخت_کد (op) == COMPONENT_REF)
	{
	  /* Get the member (its address is never null).  */
	  op = درخت_عملوند (op, 1);
	  اكسر;
	}

      /* Get the outer array/object to refer to in the warning.  */
      op = درخت_عملوند (op, 0);
      deref = درست;
    }

  إذا ((!deref && !decl_with_nonnull_addr_p (op))
      || from_macro_expansion_at (loc))
    أرجع;

  منطقي w;
  إذا (کد == EQ_عبارت)
    w = warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<false%> "
		    "for the address of %qE will never be NULL",
		    op);
  وإلا
    w = warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<true%> "
		    "for the address of %qE will never be NULL",
		    op);

  إذا (w && DECL_P (op))
    inform (DECL_منبع_LOCATION (op), "%qD declared here", op);
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
build_دودویی_op (location_t location, تعداد درخت_کد_2 کد,
		 درخت orig_op0, درخت orig_op1, منطقي convert_p)
{
  درخت type0, type1, orig_type0, orig_type1;
  درخت eptype;
  تعداد درخت_کد_2 code0, code1;
  درخت op0, op1;
  درخت ret = error_mark_گره;
  ثابت حرف *invalid_op_diag;
  منطقي op0_int_operands, op1_int_operands;
  منطقي int_const, int_const_or_سرریز, int_operands;

  /* Expression code to give to the expression when it is built.
     Normally this is CODE, which is what the caller asked for,
     but in some special cases we change it.  */
  تعداد درخت_کد_2 resultcode = کد;

  /* Data type in which the computation is to be performed.
     In the simplest cases this is the common type of the arguments.  */
  درخت نتیجه_type = عدم;

  /* When the computation is in excess precision, the type of the
     final EXCESS_PRECISION_EXPR.  */
  درخت semantic_نتیجه_type = عدم;

  /* Nonzero means operands have already been type-converted
     in whatever way is necessary.
     Zero means they need to be converted to RESULT_TYPE.  */
  صحيح converted = 0;

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
  صحيح shorten = 0;

  /* Nonzero if this is a comparison operation;
     if both args are promoted shorts, compare the original shorts.
     Also implies COMMON.  */
  صحيح short_compare = 0;

  /* Nonzero if this is a right-shift operation, which can be computed on the
     original short and then promoted if the operand is a promoted short.  */
  صحيح short_لغزش = 0;

  /* Nonzero means set RESULT_TYPE to the common type of the args.  */
  صحيح common = 0;

  /* True means types are compatible as far as ObjC is concerned.  */
  منطقي objc_ok;

  /* True means this is an arithmetic operation that may need excess
     precision.  */
  منطقي may_need_excess_precision;

  /* True means this is a boolean operation that converts both its
     operands to truth-values.  */
  منطقي boolean_op = خطأ;

  /* Remember whether we're doing / or %.  */
  منطقي doing_div_or_mod = خطأ;

  /* Remember whether we're doing << or >>.  */
  منطقي doing_لغزش = خطأ;

  /* Tree holding instrumentation expression.  */
  درخت instrument_عبارت = عدم;

  إذا (location == UNKNOWN_LOCATION)
    location = درون_داد_location;

  op0 = orig_op0;
  op1 = orig_op1;

  op0_int_operands = عبارت_INT_CONST_OPERANDS (orig_op0);
  إذا (op0_int_operands)
    op0 = remove_c_maybe_const_عبارت (op0);
  op1_int_operands = عبارت_INT_CONST_OPERANDS (orig_op1);
  إذا (op1_int_operands)
    op1 = remove_c_maybe_const_عبارت (op1);
  int_operands = (op0_int_operands && op1_int_operands);
  إذا (int_operands)
    {
      int_const_or_سرریز = (درخت_کد (orig_op0) == INTEGER_CST
			       && درخت_کد (orig_op1) == INTEGER_CST);
      int_const = (int_const_or_سرریز
		   && !درخت_سرریز (orig_op0)
		   && !درخت_سرریز (orig_op1));
    }
  وإلا
    int_const = int_const_or_سرریز = خطأ;

  /* Do not apply default conversion in mixed vector/scalar expression.  */
  إذا (convert_p
      && وکتور_TYPE_P (درخت_TYPE (op0)) == وکتور_TYPE_P (درخت_TYPE (op1)))
    {
      op0 = default_conversion (op0);
      op1 = default_conversion (op1);
    }

  orig_type0 = type0 = درخت_TYPE (op0);

  orig_type1 = type1 = درخت_TYPE (op1);

  /* The expression codes of the data types of the arguments tell us
     whether the arguments are integers, floating, pointers, etc.  */
  code0 = درخت_کد (type0);
  code1 = درخت_کد (type1);

  /* Strip NON_LVALUE_EXPRs, etc., since we aren't using as an lvalue.  */
  STRIP_TYPE_NOPS (op0);
  STRIP_TYPE_NOPS (op1);

  /* If an error was already reported for one of the arguments,
     avoid reporting another error.  */

  إذا (code0 == ERROR_MARK || code1 == ERROR_MARK)
    أرجع error_mark_گره;

  إذا (code0 == اشاره_گر_TYPE
      && reject_gcc_builtin (op0, عبارت_LOCATION (orig_op0)))
    أرجع error_mark_گره;

  إذا (code1 == اشاره_گر_TYPE
      && reject_gcc_builtin (op1, عبارت_LOCATION (orig_op1)))
    أرجع error_mark_گره;

  إذا ((invalid_op_diag
       = targetm.invalid_دودویی_op (کد, type0, type1)))
    {
      error_at (location, invalid_op_diag);
      أرجع error_mark_گره;
    }

  بدل (کد)
    {
    حالة PLUS_عبارت:
    حالة MINUS_عبارت:
    حالة MULT_عبارت:
    حالة TRUNC_DIV_عبارت:
    حالة CEIL_DIV_عبارت:
    حالة FLOOR_DIV_عبارت:
    حالة دور_DIV_عبارت:
    حالة EXACT_DIV_عبارت:
      may_need_excess_precision = درست;
      اكسر;

    حالة EQ_عبارت:
    حالة NE_عبارت:
    حالة LE_عبارت:
    حالة GE_عبارت:
    حالة LT_عبارت:
    حالة GT_عبارت:
      /* Excess precision for implicit conversions of integers to
	 floating point in C11 and later.  */
      may_need_excess_precision = (flag_isoc11
				   && (ANY_INTEGRAL_TYPE_P (type0)
				       || ANY_INTEGRAL_TYPE_P (type1)));
      اكسر;

    افتراضي:
      may_need_excess_precision = خطأ;
      اكسر;
    }
  إذا (درخت_کد (op0) == EXCESS_PRECISION_عبارت)
    {
      op0 = درخت_عملوند (op0, 0);
      type0 = درخت_TYPE (op0);
    }
  وإلا إذا (may_need_excess_precision
	   && (eptype = excess_precision_type (type0)) != NULL_درخت)
    {
      type0 = eptype;
      op0 = convert (eptype, op0);
    }
  إذا (درخت_کد (op1) == EXCESS_PRECISION_عبارت)
    {
      op1 = درخت_عملوند (op1, 0);
      type1 = درخت_TYPE (op1);
    }
  وإلا إذا (may_need_excess_precision
	   && (eptype = excess_precision_type (type1)) != NULL_درخت)
    {
      type1 = eptype;
      op1 = convert (eptype, op1);
    }

  objc_ok = objc_compare_types (type0, type1, -3, NULL_درخت);

  /* In case when one of the operands of the binary operation is
     a vector and another is a scalar -- convert scalar to vector.  */
  إذا ((gnu_وکتور_type_p (type0) && code1 != وکتور_TYPE)
      || (gnu_وکتور_type_p (type1) && code0 != وکتور_TYPE))
    {
      تعداد stv_conv convert_flag = scalar_مقصد_وکتور (location, کد, orig_op0,
						     orig_op1, درست);

      بدل (convert_flag)
	{
	  حالة stv_error:
	    أرجع error_mark_گره;
	  حالة stv_firstarg:
	    {
              منطقي maybe_const = درست;
              درخت sc;
              sc = c_fully_fold (op0, خطأ, &maybe_const);
              sc = save_عبارت (sc);
              sc = convert (درخت_TYPE (type1), sc);
              op0 = build_وکتور_from_val (type1, sc);
              إذا (!maybe_const)
                op0 = c_wrap_maybe_const (op0, درست);
              orig_type0 = type0 = درخت_TYPE (op0);
              code0 = درخت_کد (type0);
              converted = 1;
              اكسر;
	    }
	  حالة stv_secondarg:
	    {
	      منطقي maybe_const = درست;
	      درخت sc;
	      sc = c_fully_fold (op1, خطأ, &maybe_const);
	      sc = save_عبارت (sc);
	      sc = convert (درخت_TYPE (type0), sc);
	      op1 = build_وکتور_from_val (type0, sc);
	      إذا (!maybe_const)
		op1 = c_wrap_maybe_const (op1, درست);
	      orig_type1 = type1 = درخت_TYPE (op1);
	      code1 = درخت_کد (type1);
	      converted = 1;
	      اكسر;
	    }
	  افتراضي:
	    اكسر;
	}
    }

  بدل (کد)
    {
    حالة PLUS_عبارت:
      /* Handle the pointer + int case.  */
      إذا (code0 == اشاره_گر_TYPE
	  && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  ret = اشاره_گر_int_جمع (location, PLUS_عبارت, op0, op1);
	  اذهب return_build_دودویی_op;
	}
      وإلا إذا (code1 == اشاره_گر_TYPE
	       && (code0 == INTEGER_TYPE || code0 == BITINT_TYPE))
	{
	  ret = اشاره_گر_int_جمع (location, PLUS_عبارت, op1, op0);
	  اذهب return_build_دودویی_op;
	}
      وإلا
	common = 1;
      اكسر;

    حالة MINUS_عبارت:
      /* Subtraction of two similar pointers.
	 We must subtract them as integers, then divide by object size.  */
      إذا (code0 == اشاره_گر_TYPE && code1 == اشاره_گر_TYPE
	  && comp_هدف_types (location, type0, type1))
	{
	  ret = اشاره_گر_diff (location, op0, op1, &instrument_عبارت);
	  اذهب return_build_دودویی_op;
	}
      /* Handle pointer minus int.  Just like pointer plus int.  */
      وإلا إذا (code0 == اشاره_گر_TYPE
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  ret = اشاره_گر_int_جمع (location, MINUS_عبارت, op0, op1);
	  اذهب return_build_دودویی_op;
	}
      وإلا
	common = 1;
      اكسر;

    حالة MULT_عبارت:
      common = 1;
      اكسر;

    حالة TRUNC_DIV_عبارت:
    حالة CEIL_DIV_عبارت:
    حالة FLOOR_DIV_عبارت:
    حالة دور_DIV_عبارت:
    حالة EXACT_DIV_عبارت:
      doing_div_or_mod = درست;
      warn_for_div_by_zero (location, op1);

      إذا ((code0 == INTEGER_TYPE || code0 == REAL_TYPE
	   || code0 == FIXED_نقطه_TYPE || code0 == BITINT_TYPE
	   || code0 == COMPLEX_TYPE
	   || gnu_وکتور_type_p (type0))
	  && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	      || code1 == FIXED_نقطه_TYPE || code1 == BITINT_TYPE
	      || code1 == COMPLEX_TYPE
	      || gnu_وکتور_type_p (type1)))
	{
	  تعداد درخت_کد_2 tcode0 = code0, tcode1 = code1;

	  إذا (code0 == COMPLEX_TYPE || code0 == وکتور_TYPE)
	    tcode0 = درخت_کد (درخت_TYPE (درخت_TYPE (op0)));
	  إذا (code1 == COMPLEX_TYPE || code1 == وکتور_TYPE)
	    tcode1 = درخت_کد (درخت_TYPE (درخت_TYPE (op1)));

	  إذا (!(((tcode0 == INTEGER_TYPE || tcode0 == BITINT_TYPE
		  || (tcode0 == ENUMERAL_TYPE && code0 == وکتور_TYPE))
		 && (tcode1 == INTEGER_TYPE || tcode1 == BITINT_TYPE
		     || (tcode1 == ENUMERAL_TYPE && code1 == وکتور_TYPE)))
		|| (tcode0 == FIXED_نقطه_TYPE && tcode1 == FIXED_نقطه_TYPE)))
	    resultcode = RDIV_عبارت;
	  وإلا
	    /* Although it would be tempting to shorten always here, that
	       loses on some targets, since the modulo instruction is
	       undefined if the quotient can't be represented in the
	       computation mode.  We shorten only if unsigned or if
	       dividing by something we know != -1.  */
	    shorten = may_shorten_divmod (op0, op1);
	  common = 1;
	}
      اكسر;

    حالة بیت_AND_عبارت:
    حالة بیت_IOR_عبارت:
    حالة بیت_XOR_عبارت:
      إذا ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	shorten = -1;
      /* Allow vector types which are not floating point types.   */
      وإلا إذا (gnu_وکتور_type_p (type0)
	       && gnu_وکتور_type_p (type1)
	       && !وکتور_FLOAT_TYPE_P (type0)
	       && !وکتور_FLOAT_TYPE_P (type1))
	common = 1;
      اكسر;

    حالة TRUNC_MOD_عبارت:
    حالة FLOOR_MOD_عبارت:
      doing_div_or_mod = درست;
      warn_for_div_by_zero (location, op1);

      إذا (gnu_وکتور_type_p (type0)
	  && gnu_وکتور_type_p (type1)
	  && درخت_کد (درخت_TYPE (type0)) == INTEGER_TYPE
	  && درخت_کد (درخت_TYPE (type1)) == INTEGER_TYPE)
	common = 1;
      وإلا إذا ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  /* Although it would be tempting to shorten always here, that loses
	     on some targets, since the modulo instruction is undefined if the
	     quotient can't be represented in the computation mode.  We shorten
	     only if unsigned or if dividing by something we know != -1.  */
	  shorten = may_shorten_divmod (op0, op1);
	  common = 1;
	}
      اكسر;

    حالة TRUTH_ANDIF_عبارت:
    حالة TRUTH_ORIF_عبارت:
    حالة TRUTH_AND_عبارت:
    حالة TRUTH_OR_عبارت:
    حالة TRUTH_XOR_عبارت:
      إذا ((code0 == INTEGER_TYPE || code0 == اشاره_گر_TYPE
	   || code0 == REAL_TYPE || code0 == COMPLEX_TYPE
	   || code0 == FIXED_نقطه_TYPE || code0 == NULLPTR_TYPE
	   || code0 == BITINT_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == اشاره_گر_TYPE
	      || code1 == REAL_TYPE || code1 == COMPLEX_TYPE
	      || code1 == FIXED_نقطه_TYPE || code1 == NULLPTR_TYPE
	      || code1 == BITINT_TYPE))
	{
	  /* Result of these operations is always an int,
	     but that does not mean the operands should be
	     converted to ints!  */
	  نتیجه_type = integer_type_گره;
	  إذا (op0_int_operands)
	    {
	      op0 = c_objc_common_truthvalue_conversion (location, orig_op0);
	      op0 = remove_c_maybe_const_عبارت (op0);
	    }
	  وإلا
	    op0 = c_objc_common_truthvalue_conversion (location, op0);
	  إذا (op1_int_operands)
	    {
	      op1 = c_objc_common_truthvalue_conversion (location, orig_op1);
	      op1 = remove_c_maybe_const_عبارت (op1);
	    }
	  وإلا
	    op1 = c_objc_common_truthvalue_conversion (location, op1);
	  converted = 1;
	  boolean_op = درست;
	}
      إذا (کد == TRUTH_ANDIF_عبارت)
	{
	  int_const_or_سرریز = (int_operands
				   && درخت_کد (orig_op0) == INTEGER_CST
				   && (op0 == truthvalue_false_گره
				       || درخت_کد (orig_op1) == INTEGER_CST));
	  int_const = (int_const_or_سرریز
		       && !درخت_سرریز (orig_op0)
		       && (op0 == truthvalue_false_گره
			   || !درخت_سرریز (orig_op1)));
	}
      وإلا إذا (کد == TRUTH_ORIF_عبارت)
	{
	  int_const_or_سرریز = (int_operands
				   && درخت_کد (orig_op0) == INTEGER_CST
				   && (op0 == truthvalue_true_گره
				       || درخت_کد (orig_op1) == INTEGER_CST));
	  int_const = (int_const_or_سرریز
		       && !درخت_سرریز (orig_op0)
		       && (op0 == truthvalue_true_گره
			   || !درخت_سرریز (orig_op1)));
	}
      اكسر;

      /* Shift operations: result has same type as first operand;
	 always convert second operand to int.
	 Also set SHORT_SHIFT if shifting rightward.  */

    حالة RSHIFT_عبارت:
      إذا (gnu_وکتور_type_p (type0)
	  && gnu_وکتور_type_p (type1)
	  && درخت_کد (درخت_TYPE (type0)) == INTEGER_TYPE
	  && درخت_کد (درخت_TYPE (type1)) == INTEGER_TYPE
	  && معلوم_eq (TYPE_وکتور_SUBPARTS (type0),
		       TYPE_وکتور_SUBPARTS (type1)))
	{
	  نتیجه_type = type0;
	  converted = 1;
	}
      وإلا إذا ((code0 == INTEGER_TYPE || code0 == FIXED_نقطه_TYPE
		|| code0 == BITINT_TYPE
		|| (gnu_وکتور_type_p (type0)
		    && درخت_کد (درخت_TYPE (type0)) == INTEGER_TYPE))
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  doing_لغزش = درست;
	  إذا (درخت_کد (op1) == INTEGER_CST)
	    {
	      إذا (درخت_int_cst_sgn (op1) < 0)
		{
		  int_const = خطأ;
		  إذا (c_inhibit_evaluation_warnings == 0)
		    warning_at (location, OPT_Wshift_شمار_negative,
				"right shift count is negative");
		}
	      وإلا إذا (code0 == وکتور_TYPE)
		{
		  إذا (compare_درخت_int (op1,
					TYPE_PRECISION (درخت_TYPE (type0)))
		      >= 0)
		    {
		      int_const = خطأ;
		      إذا (c_inhibit_evaluation_warnings == 0)
			warning_at (location, OPT_Wshift_شمار_سرریز,
				    "right shift count >= width of vector element");
		    }
		}
	      وإلا
		{
		  إذا (!integer_zerop (op1))
		    short_لغزش = 1;

		  إذا (compare_درخت_int (op1, TYPE_PRECISION (type0)) >= 0)
		    {
		      int_const = خطأ;
		      إذا (c_inhibit_evaluation_warnings == 0)
			warning_at (location, OPT_Wshift_شمار_سرریز,
				    "right shift count >= width of type");
		    }
		}
	    }

	  /* Use the type of the value to be shifted.  */
	  نتیجه_type = type0;
	  /* Avoid converting op1 to result_type later.  */
	  converted = 1;
	}
      اكسر;

    حالة LSHIFT_عبارت:
      إذا (gnu_وکتور_type_p (type0)
	  && gnu_وکتور_type_p (type1)
	  && درخت_کد (درخت_TYPE (type0)) == INTEGER_TYPE
	  && درخت_کد (درخت_TYPE (type1)) == INTEGER_TYPE
	  && معلوم_eq (TYPE_وکتور_SUBPARTS (type0),
		       TYPE_وکتور_SUBPARTS (type1)))
	{
	  نتیجه_type = type0;
	  converted = 1;
	}
      وإلا إذا ((code0 == INTEGER_TYPE || code0 == FIXED_نقطه_TYPE
		|| code0 == BITINT_TYPE
		|| (gnu_وکتور_type_p (type0)
		    && درخت_کد (درخت_TYPE (type0)) == INTEGER_TYPE))
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  doing_لغزش = درست;
	  إذا (درخت_کد (op0) == INTEGER_CST
	      && درخت_int_cst_sgn (op0) < 0
	      && !TYPE_سرریز_WRAPS (type0))
	    {
	      /* Don't reject a left shift of a negative value in a context
		 where a constant expression is needed in C90.  */
	      إذا (flag_isoc99)
		int_const = خطأ;
	      إذا (c_inhibit_evaluation_warnings == 0)
		warning_at (location, OPT_Wshift_negative_مقدار,
			    "left shift of negative value");
	    }
	  إذا (درخت_کد (op1) == INTEGER_CST)
	    {
	      إذا (درخت_int_cst_sgn (op1) < 0)
		{
		  int_const = خطأ;
		  إذا (c_inhibit_evaluation_warnings == 0)
		    warning_at (location, OPT_Wshift_شمار_negative,
				"left shift count is negative");
		}
	      وإلا إذا (code0 == وکتور_TYPE)
		{
		  إذا (compare_درخت_int (op1,
					TYPE_PRECISION (درخت_TYPE (type0)))
		      >= 0)
		    {
		      int_const = خطأ;
		      إذا (c_inhibit_evaluation_warnings == 0)
			warning_at (location, OPT_Wshift_شمار_سرریز,
				    "left shift count >= width of vector element");
		    }
		}
	      وإلا إذا (compare_درخت_int (op1, TYPE_PRECISION (type0)) >= 0)
		{
		  int_const = خطأ;
		  إذا (c_inhibit_evaluation_warnings == 0)
		    warning_at (location, OPT_Wshift_شمار_سرریز,
				"left shift count >= width of type");
		}
	      وإلا إذا (درخت_کد (op0) == INTEGER_CST
		       && maybe_warn_لغزش_سرریز (location, op0, op1)
		       && flag_isoc99)
		int_const = خطأ;
	    }

	  /* Use the type of the value to be shifted.  */
	  نتیجه_type = type0;
	  /* Avoid converting op1 to result_type later.  */
	  converted = 1;
	}
      اكسر;

    حالة EQ_عبارت:
    حالة NE_عبارت:
      إذا (gnu_وکتور_type_p (type0) && gnu_وکتور_type_p (type1))
        {
          درخت intt;
	  إذا (!وکتور_types_compatible_elements_p (type0, type1))
            {
              error_at (location, "comparing vectors with different "
                                  "element types");
              أرجع error_mark_گره;
            }

	  إذا (maybe_ne (TYPE_وکتور_SUBPARTS (type0),
			TYPE_وکتور_SUBPARTS (type1)))
            {
              error_at (location, "comparing vectors with different "
                                  "number of elements");
              أرجع error_mark_گره;
            }

	  /* It's not precisely specified how the usual arithmetic
	     conversions apply to the vector types.  Here, we use
	     the unsigned type if one of the operands is signed and
	     the other one is unsigned.  */
	  إذا (TYPE_UNSIGNED (type0) != TYPE_UNSIGNED (type1))
	    {
	      إذا (!TYPE_UNSIGNED (type0))
		op0 = build1 (VIEW_CONVERT_عبارت, type1, op0);
	      وإلا
		op1 = build1 (VIEW_CONVERT_عبارت, type0, op1);
	      warning_at (location, OPT_Wsign_compare, "comparison between "
			  "types %qT and %qT", type0, type1);
	    }

          /* Always construct signed integer vector type.  */
	  إذا (وکتور_BOOLEAN_TYPE_P (type0) && وکتور_BOOLEAN_TYPE_P (type1))
	    نتیجه_type = type0;
	  وإلا
	    {
	      خودکار nelts = TYPE_وکتور_SUBPARTS (type0);

	      intt = c_common_type_for_اندازه (GET_نما_BITSIZE
					     (SCALAR_TYPE_نما
						(درخت_TYPE (type0))), 0);
	      إذا (!intt)
		{
		  error_at (location, "could not find an integer type "
				      "of the same size as %qT",
			    درخت_TYPE (type0));
		  أرجع error_mark_گره;
		}
	      نتیجه_type = build_opaque_وکتور_type (intt, nelts);
	    }
          converted = 1;
	  ret = build_vec_cmp (resultcode, نتیجه_type, op0, op1);
	  اذهب return_build_دودویی_op;
        }
      إذا (FLOAT_TYPE_P (type0) || FLOAT_TYPE_P (type1))
	warning_at (location,
		    OPT_Wfloat_equal,
		    "comparing floating-point with %<==%> or %<!=%> is unsafe");
      /* Result of comparison is always int,
	 but don't convert the args to int!  */
      build_type = integer_type_گره;
      إذا ((code0 == INTEGER_TYPE || code0 == REAL_TYPE || code0 == BITINT_TYPE
	   || code0 == FIXED_نقطه_TYPE || code0 == COMPLEX_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	      || code1 == BITINT_TYPE
	      || code1 == FIXED_نقطه_TYPE || code1 == COMPLEX_TYPE))
	short_compare = 1;
      وإلا إذا (code0 == اشاره_گر_TYPE
	       && (code1 == NULLPTR_TYPE
		   || null_اشاره_گر_constant_p (orig_op1)))
	{
	  maybe_warn_for_null_آدرس (location, op0, کد);
	  نتیجه_type = type0;
	}
      وإلا إذا (code1 == اشاره_گر_TYPE
	       && (code0 == NULLPTR_TYPE
		   || null_اشاره_گر_constant_p (orig_op0)))
	{
	  maybe_warn_for_null_آدرس (location, op1, کد);
	  نتیجه_type = type1;
	}
      وإلا إذا (code0 == اشاره_گر_TYPE && code1 == اشاره_گر_TYPE)
	{
	  درخت tt0 = درخت_TYPE (type0);
	  درخت tt1 = درخت_TYPE (type1);
	  addr_space_t as0 = TYPE_ADDR_SPACE (tt0);
	  addr_space_t as1 = TYPE_ADDR_SPACE (tt1);
	  addr_space_t as_common = ADDR_SPACE_GENERIC;

	  /* Anything compares with void *.  void * compares with anything.
	     Otherwise, the targets must be compatible
	     and both must be object or both incomplete.  */
	  إذا (comp_هدف_types (location, type0, type1))
	    نتیجه_type = common_اشاره_گر_type (type0, type1, NULL_درخت);
	  وإلا إذا (!addr_space_superset (as0, as1, &as_common))
	    {
	      error_at (location, "comparison of pointers to "
			"disjoint address spaces");
	      أرجع error_mark_گره;
	    }
	  وإلا إذا (VOID_TYPE_P (tt0) && !TYPE_ATOMIC (tt0))
	    {
	      إذا (pedantic && درخت_کد (tt1) == FUNCTION_TYPE)
		pedwarn (location, OPT_Wpedantic, "ISO C forbids "
			 "comparison of %<void *%> with function pointer");
	    }
	  وإلا إذا (VOID_TYPE_P (tt1) && !TYPE_ATOMIC (tt1))
	    {
	      إذا (pedantic && درخت_کد (tt0) == FUNCTION_TYPE)
		pedwarn (location, OPT_Wpedantic, "ISO C forbids "
			 "comparison of %<void *%> with function pointer");
	    }
	  وإلا
	    /* Avoid warning about the volatile ObjC EH puts on decls.  */
	    إذا (!objc_ok)
	      pedwarn (location, OPT_Wcompare_distinct_اشاره_گر_types,
		       "comparison of distinct pointer types lacks a cast");

	  إذا (نتیجه_type == NULL_درخت)
	    {
	      صحيح qual = ENCODE_QUAL_ADDR_SPACE (as_common);
	      نتیجه_type = c_build_اشاره_گر_type
			      (c_build_qualified_type (void_type_گره, qual));
	    }
	}
      وإلا إذا (code0 == اشاره_گر_TYPE
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  نتیجه_type = type0;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}
      وإلا إذا ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	       && code1 == اشاره_گر_TYPE)
	{
	  نتیجه_type = type1;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}
      /* 6.5.9: One of the following shall hold:
	 -- both operands have type nullptr_t;  */
      وإلا إذا (code0 == NULLPTR_TYPE && code1 == NULLPTR_TYPE)
	{
	  نتیجه_type = nullptr_type_گره;
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
      وإلا إذا (code0 == NULLPTR_TYPE && null_اشاره_گر_constant_p (orig_op1))
	نتیجه_type = (INTEGRAL_TYPE_P (type1)
		       ? c_build_اشاره_گر_type (type1) : type1);
      وإلا إذا (code1 == NULLPTR_TYPE && null_اشاره_گر_constant_p (orig_op0))
	نتیجه_type = (INTEGRAL_TYPE_P (type0)
		       ? c_build_اشاره_گر_type (type0) : type0);
      إذا ((C_BOOLEAN_TYPE_P (درخت_TYPE (orig_op0))
	   || truth_مقدار_p (درخت_کد (orig_op0)))
	  ^ (C_BOOLEAN_TYPE_P (درخت_TYPE (orig_op1))
	     || truth_مقدار_p (درخت_کد (orig_op1))))
	maybe_warn_bool_compare (location, کد, orig_op0, orig_op1);
      اكسر;

    حالة LE_عبارت:
    حالة GE_عبارت:
    حالة LT_عبارت:
    حالة GT_عبارت:
      إذا (gnu_وکتور_type_p (type0) && gnu_وکتور_type_p (type1))
        {
          درخت intt;
	  إذا (!وکتور_types_compatible_elements_p (type0, type1))
            {
              error_at (location, "comparing vectors with different "
                                  "element types");
              أرجع error_mark_گره;
            }

	  إذا (maybe_ne (TYPE_وکتور_SUBPARTS (type0),
			TYPE_وکتور_SUBPARTS (type1)))
            {
              error_at (location, "comparing vectors with different "
                                  "number of elements");
              أرجع error_mark_گره;
            }

	  /* It's not precisely specified how the usual arithmetic
	     conversions apply to the vector types.  Here, we use
	     the unsigned type if one of the operands is signed and
	     the other one is unsigned.  */
	  إذا (TYPE_UNSIGNED (type0) != TYPE_UNSIGNED (type1))
	    {
	      إذا (!TYPE_UNSIGNED (type0))
		op0 = build1 (VIEW_CONVERT_عبارت, type1, op0);
	      وإلا
		op1 = build1 (VIEW_CONVERT_عبارت, type0, op1);
	      warning_at (location, OPT_Wsign_compare, "comparison between "
			  "types %qT and %qT", type0, type1);
	    }

          /* Always construct signed integer vector type.  */
          intt = c_common_type_for_اندازه (GET_نما_BITSIZE
					 (SCALAR_TYPE_نما
					  (درخت_TYPE (type0))), 0);
	  إذا (!intt)
	    {
	      error_at (location, "could not find an integer type "
				  "of the same size as %qT",
			درخت_TYPE (type0));
	      أرجع error_mark_گره;
	    }
          نتیجه_type = build_opaque_وکتور_type (intt,
						  TYPE_وکتور_SUBPARTS (type0));
          converted = 1;
	  ret = build_vec_cmp (resultcode, نتیجه_type, op0, op1);
	  اذهب return_build_دودویی_op;
        }
      build_type = integer_type_گره;
      إذا ((code0 == INTEGER_TYPE || code0 == REAL_TYPE
	   || code0 == BITINT_TYPE || code0 == FIXED_نقطه_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	      || code1 == BITINT_TYPE || code1 == FIXED_نقطه_TYPE))
	short_compare = 1;
      وإلا إذا (code0 == اشاره_گر_TYPE && code1 == اشاره_گر_TYPE)
	{
	  addr_space_t as0 = TYPE_ADDR_SPACE (درخت_TYPE (type0));
	  addr_space_t as1 = TYPE_ADDR_SPACE (درخت_TYPE (type1));
	  addr_space_t as_common;

	  إذا (comp_هدف_types (location, type0, type1))
	    {
	      نتیجه_type = common_اشاره_گر_type (type0, type1, NULL_درخت);
	      إذا (!COMPLETE_TYPE_P (درخت_TYPE (type0))
		  != !COMPLETE_TYPE_P (درخت_TYPE (type1)))
		pedwarn_c99 (location, OPT_Wpedantic,
			     "comparison of complete and incomplete pointers");
	      وإلا إذا (درخت_کد (درخت_TYPE (type0)) == FUNCTION_TYPE)
		pedwarn (location, OPT_Wpedantic, "ISO C forbids "
			 "ordered comparisons of pointers to functions");
	      وإلا إذا (null_اشاره_گر_constant_p (orig_op0)
		       || null_اشاره_گر_constant_p (orig_op1))
		warning_at (location, OPT_Wextra,
			    "ordered comparison of pointer with null pointer");

	    }
	  وإلا إذا (!addr_space_superset (as0, as1, &as_common))
	    {
	      error_at (location, "comparison of pointers to "
			"disjoint address spaces");
	      أرجع error_mark_گره;
	    }
	  وإلا
	    {
	      صحيح qual = ENCODE_QUAL_ADDR_SPACE (as_common);
	      نتیجه_type = c_build_اشاره_گر_type
			      (c_build_qualified_type (void_type_گره, qual));
              pedwarn (location, OPT_Wcompare_distinct_اشاره_گر_types,
                       "comparison of distinct pointer types lacks a cast");
	    }
	}
      وإلا إذا (code0 == اشاره_گر_TYPE && null_اشاره_گر_constant_p (orig_op1))
	{
	  نتیجه_type = type0;
	  إذا (pedantic)
	    pedwarn (location, OPT_Wpedantic,
		     "ordered comparison of pointer with integer zero");
	  وإلا إذا (extra_warnings)
	    warning_at (location, OPT_Wextra,
			"ordered comparison of pointer with integer zero");
	}
      وإلا إذا (code1 == اشاره_گر_TYPE && null_اشاره_گر_constant_p (orig_op0))
	{
	  نتیجه_type = type1;
	  إذا (pedantic)
	    pedwarn (location, OPT_Wpedantic,
		     "ordered comparison of pointer with integer zero");
	  وإلا إذا (extra_warnings)
	    warning_at (location, OPT_Wextra,
			"ordered comparison of pointer with integer zero");
	}
      وإلا إذا (code0 == اشاره_گر_TYPE
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  نتیجه_type = type0;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}
      وإلا إذا ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	       && code1 == اشاره_گر_TYPE)
	{
	  نتیجه_type = type1;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}

      إذا ((code0 == اشاره_گر_TYPE || code1 == اشاره_گر_TYPE)
	  && current_function_decl != NULL_درخت
	  && sanitize_flags_p (SANITIZE_اشاره_گر_COMPARE))
	{
	  op0 = save_عبارت (c_fully_fold (op0, خطأ, عدم));
	  op1 = save_عبارت (c_fully_fold (op1, خطأ, عدم));

	  درخت tt = builtin_decl_explicit (BUILT_درون_ASAN_اشاره_گر_COMPARE);
	  instrument_عبارت = build_call_عبارت_loc (location, tt, 2, op0, op1);
	}

      إذا ((C_BOOLEAN_TYPE_P (درخت_TYPE (orig_op0))
	   || truth_مقدار_p (درخت_کد (orig_op0)))
	  ^ (C_BOOLEAN_TYPE_P (درخت_TYPE (orig_op1))
	     || truth_مقدار_p (درخت_کد (orig_op1))))
	maybe_warn_bool_compare (location, کد, orig_op0, orig_op1);
      اكسر;

    حالة MIN_عبارت:
    حالة MAX_عبارت:
      /* Used for OpenMP atomics.  */
      gcc_assert (flag_openmp);
      common = 1;
      اكسر;

    افتراضي:
      gcc_unreachable ();
    }

  إذا (code0 == ERROR_MARK || code1 == ERROR_MARK)
    أرجع error_mark_گره;

  إذا (gnu_وکتور_type_p (type0)
      && gnu_وکتور_type_p (type1)
      && (!درخت_int_cst_equal (TYPE_اندازه (type0), TYPE_اندازه (type1))
	  || !وکتور_types_compatible_elements_p (type0, type1)))
    {
      gcc_rich_location richloc (location);
      maybe_range_label_for_درخت_type_mismatch
	label_for_op0 (orig_op0, orig_op1),
	label_for_op1 (orig_op1, orig_op0);
      richloc.maybe_جمع_کن_عبارت (orig_op0, &label_for_op0, highlight_colors::lhs);
      richloc.maybe_جمع_کن_عبارت (orig_op1, &label_for_op1, highlight_colors::rhs);
      دودویی_op_error (&richloc, کد, type0, type1);
      أرجع error_mark_گره;
    }

  إذا ((code0 == INTEGER_TYPE || code0 == REAL_TYPE || code0 == COMPLEX_TYPE
       || code0 == FIXED_نقطه_TYPE || code0 == BITINT_TYPE
       || gnu_وکتور_type_p (type0))
      && (code1 == INTEGER_TYPE || code1 == REAL_TYPE || code1 == COMPLEX_TYPE
	  || code1 == FIXED_نقطه_TYPE || code1 == BITINT_TYPE
	  || gnu_وکتور_type_p (type1)))
    {
      منطقي اولی_complex = (code0 == COMPLEX_TYPE);
      منطقي دومی_complex = (code1 == COMPLEX_TYPE);
      صحيح none_complex = (!اولی_complex && !دومی_complex);

      إذا (shorten || common || short_compare)
	{
	  نتیجه_type = c_common_type (type0, type1);
	  do_warn_double_promotion (نتیجه_type, type0, type1,
				    "implicit conversion from %qT to %qT "
				    "to match other operand of binary "
				    "expression",
				    location);
	  إذا (نتیجه_type == error_mark_گره)
	    أرجع error_mark_گره;
	}

      إذا (اولی_complex != دومی_complex
	  && (کد == PLUS_عبارت
	      || کد == MINUS_عبارت
	      || کد == MULT_عبارت
	      || (کد == TRUNC_DIV_عبارت && اولی_complex))
	  && درخت_کد (درخت_TYPE (نتیجه_type)) == REAL_TYPE
	  && flag_signed_zeros)
	{
	  /* An operation on mixed real/complex operands must be
	     handled specially, but the language-independent code can
	     more easily optimize the plain complex arithmetic if
	     -fno-signed-zeros.  */
	  درخت real_type = درخت_TYPE (نتیجه_type);
	  درخت real, imag;
	  إذا (type0 != orig_type0 || type1 != orig_type1)
	    {
	      gcc_assert (may_need_excess_precision && common);
	      semantic_نتیجه_type = c_common_type (orig_type0, orig_type1);
	    }
	  إذا (اولی_complex)
	    {
	      إذا (درخت_TYPE (op0) != نتیجه_type)
		op0 = convert_and_check (location, نتیجه_type, op0);
	      إذا (درخت_TYPE (op1) != real_type)
		op1 = convert_and_check (location, real_type, op1);
	    }
	  وإلا
	    {
	      إذا (درخت_TYPE (op0) != real_type)
		op0 = convert_and_check (location, real_type, op0);
	      إذا (درخت_TYPE (op1) != نتیجه_type)
		op1 = convert_and_check (location, نتیجه_type, op1);
	    }
	  إذا (درخت_کد (op0) == ERROR_MARK || درخت_کد (op1) == ERROR_MARK)
	    أرجع error_mark_گره;
	  إذا (اولی_complex)
	    {
	      op0 = save_عبارت (op0);
	      real = build_unary_op (عبارت_LOCATION (orig_op0), REALPART_عبارت,
				     op0, درست);
	      imag = build_unary_op (عبارت_LOCATION (orig_op0), IMAGPART_عبارت,
				     op0, درست);
	      بدل (کد)
		{
		حالة MULT_عبارت:
		حالة TRUNC_DIV_عبارت:
		  op1 = save_عبارت (op1);
		  imag = build2 (resultcode, real_type, imag, op1);
		  /* Fall through.  */
		حالة PLUS_عبارت:
		حالة MINUS_عبارت:
		  real = build2 (resultcode, real_type, real, op1);
		  اكسر;
		افتراضي:
		  gcc_unreachable();
		}
	    }
	  وإلا
	    {
	      op1 = save_عبارت (op1);
	      real = build_unary_op (عبارت_LOCATION (orig_op1), REALPART_عبارت,
				     op1, درست);
	      imag = build_unary_op (عبارت_LOCATION (orig_op1), IMAGPART_عبارت,
				     op1, درست);
	      بدل (کد)
		{
		حالة MULT_عبارت:
		  op0 = save_عبارت (op0);
		  imag = build2 (resultcode, real_type, op0, imag);
		  /* Fall through.  */
		حالة PLUS_عبارت:
		  real = build2 (resultcode, real_type, op0, real);
		  اكسر;
		حالة MINUS_عبارت:
		  real = build2 (resultcode, real_type, op0, real);
		  imag = build1 (NEGATE_عبارت, real_type, imag);
		  اكسر;
		افتراضي:
		  gcc_unreachable();
		}
	    }
	  ret = build2 (COMPLEX_عبارت, نتیجه_type, real, imag);
	  اذهب return_build_دودویی_op;
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

      إذا (shorten && none_complex)
	{
	  final_type = نتیجه_type;
	  نتیجه_type = shorten_دودویی_op (نتیجه_type, op0, op1,
					   shorten == -1);
	}

      /* Shifts can be shortened if shifting right.  */

      إذا (short_لغزش)
	{
	  صحيح unsigned_arg;
	  درخت arg0 = get_narrower (op0, &unsigned_arg);

	  final_type = نتیجه_type;

	  إذا (arg0 == op0 && final_type == درخت_TYPE (op0))
	    unsigned_arg = TYPE_UNSIGNED (درخت_TYPE (op0));

	  إذا (TYPE_PRECISION (درخت_TYPE (arg0)) < TYPE_PRECISION (نتیجه_type)
	      && درخت_int_cst_sgn (op1) > 0
	      /* We can shorten only if the shift count is less than the
		 number of bits in the smaller type size.  */
	      && compare_درخت_int (op1, TYPE_PRECISION (درخت_TYPE (arg0))) < 0
	      /* We cannot drop an unsigned shift after sign-extension.  */
	      && (!TYPE_UNSIGNED (final_type) || unsigned_arg))
	    {
	      /* Do an unsigned shift if the operand was zero-extended.  */
	      نتیجه_type
		= c_common_signed_or_unsigned_type (unsigned_arg,
						    درخت_TYPE (arg0));
	      /* Convert value-to-be-shifted to that type.  */
	      إذا (درخت_TYPE (op0) != نتیجه_type)
		op0 = convert (نتیجه_type, op0);
	      converted = 1;
	    }
	}

      /* Comparison operations are shortened too but differently.
	 They identify themselves by setting short_compare = 1.  */

      إذا (short_compare)
	{
	  /* Don't write &op0, etc., because that would prevent op0
	     from being kept in a register.
	     Instead, make copies of the our local variables and
	     pass the copies by reference, then copy them back afterward.  */
	  درخت xop0 = op0, xop1 = op1, xresult_type = نتیجه_type;
	  تعداد درخت_کد_2 xresultcode = resultcode;
	  درخت val
	    = shorten_compare (location, &xop0, &xop1, &xresult_type,
			       &xresultcode);

	  إذا (val != NULL_درخت)
	    {
	      ret = val;
	      اذهب return_build_دودویی_op;
	    }

	  op0 = xop0, op1 = xop1;
	  converted = 1;
	  resultcode = xresultcode;

	  إذا (c_inhibit_evaluation_warnings == 0 && !c_درون_omp_for)
	    {
	      منطقي op0_maybe_const = درست;
	      منطقي op1_maybe_const = درست;
	      درخت orig_op0_folded, orig_op1_folded;

	      إذا (درون_late_دودویی_op)
		{
		  orig_op0_folded = orig_op0;
		  orig_op1_folded = orig_op1;
		}
	      وإلا
		{
		  /* Fold for the sake of possible warnings, as in
		     build_conditional_expr.  This requires the
		     "original" values to be folded, not just op0 and
		     op1.  */
		  c_inhibit_evaluation_warnings++;
		  op0 = c_fully_fold (op0, require_constant_مقدار,
				      &op0_maybe_const);
		  op1 = c_fully_fold (op1, require_constant_مقدار,
				      &op1_maybe_const);
		  c_inhibit_evaluation_warnings--;
		  orig_op0_folded = c_fully_fold (orig_op0,
						  require_constant_مقدار,
						  عدم);
		  orig_op1_folded = c_fully_fold (orig_op1,
						  require_constant_مقدار,
						  عدم);
		}

	      إذا (warn_sign_compare)
		warn_for_sign_compare (location, orig_op0_folded,
				       orig_op1_folded, op0, op1,
				       نتیجه_type, resultcode);
	      إذا (!درون_late_دودویی_op && !int_operands)
		{
		  إذا (!op0_maybe_const || درخت_کد (op0) != INTEGER_CST)
		    op0 = c_wrap_maybe_const (op0, !op0_maybe_const);
		  إذا (!op1_maybe_const || درخت_کد (op1) != INTEGER_CST)
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

  إذا (!نتیجه_type)
    {
      /* Favor showing any expression locations that are available. */
      op_location_t oploc (location, UNKNOWN_LOCATION);
      دودویی_op_rich_location richloc (oploc, orig_op0, orig_op1, درست);
      دودویی_op_error (&richloc, کد, درخت_TYPE (op0), درخت_TYPE (op1));
      أرجع error_mark_گره;
    }

  إذا (build_type == NULL_درخت)
    {
      build_type = نتیجه_type;
      إذا ((type0 != orig_type0 || type1 != orig_type1)
	  && !boolean_op)
	{
	  gcc_assert (may_need_excess_precision && common);
	  semantic_نتیجه_type = c_common_type (orig_type0, orig_type1);
	}
    }

  إذا (!converted)
    {
      op0 = ep_convert_and_check (location, نتیجه_type, op0,
				  semantic_نتیجه_type);
      op1 = ep_convert_and_check (location, نتیجه_type, op1,
				  semantic_نتیجه_type);

      /* This can happen if one operand has a vector type, and the other
	 has a different type.  */
      إذا (درخت_کد (op0) == ERROR_MARK || درخت_کد (op1) == ERROR_MARK)
	أرجع error_mark_گره;
    }

  إذا (sanitize_flags_p ((SANITIZE_لغزش
			 | SANITIZE_DIVIDE
			 | SANITIZE_FLOAT_DIVIDE
			 | SANITIZE_SI_سرریز))
      && current_function_decl != NULL_درخت
      && (doing_div_or_mod || doing_لغزش)
      && !require_constant_مقدار)
    {
      /* OP0 and/or OP1 might have side-effects.  */
      op0 = save_عبارت (op0);
      op1 = save_عبارت (op1);
      op0 = c_fully_fold (op0, خطأ, عدم);
      op1 = c_fully_fold (op1, خطأ, عدم);
      إذا (doing_div_or_mod && (sanitize_flags_p ((SANITIZE_DIVIDE
						  | SANITIZE_FLOAT_DIVIDE
						  | SANITIZE_SI_سرریز))))
	instrument_عبارت = ubsan_instrument_division (location, op0, op1);
      وإلا إذا (doing_لغزش && sanitize_flags_p (SANITIZE_لغزش))
	instrument_عبارت = ubsan_instrument_لغزش (location, کد, op0, op1);
    }

  /* Treat expressions in initializers specially as they can't trap.  */
  إذا (int_const_or_سرریز)
    ret = (require_constant_مقدار
	   ? fold_build2_initializer_loc (location, resultcode, build_type,
					  op0, op1)
	   : fold_build2_loc (location, resultcode, build_type, op0, op1));
  وإلا
    ret = build2 (resultcode, build_type, op0, op1);
  إذا (final_type != NULL_درخت)
    ret = convert (final_type, ret);

 return_build_دودویی_op:
  gcc_assert (ret != error_mark_گره);
  إذا (درخت_کد (ret) == INTEGER_CST && !درخت_سرریز (ret) && !int_const)
    ret = (int_operands
	   ? note_integer_operands (ret)
	   : build1 (NOP_عبارت, درخت_TYPE (ret), ret));
  وإلا إذا (درخت_کد (ret) != INTEGER_CST && int_operands
	   && !درون_late_دودویی_op)
    ret = note_integer_operands (ret);
  protected_مجموعه_عبارت_location (ret, location);

  إذا (instrument_عبارت != عدم)
    ret = fold_build2 (COMPOUND_عبارت, درخت_TYPE (ret),
		       instrument_عبارت, ret);

  إذا (semantic_نتیجه_type)
    ret = build1_loc (location, EXCESS_PRECISION_عبارت,
		      semantic_نتیجه_type, ret);

  أرجع ret;
}


/* Convert EXPR to be a truth-value (type TYPE), validating its type for this
   purpose.  LOCATION is the source location for the expression.  */

درخت
c_objc_common_truthvalue_conversion (location_t location, درخت عبارت, درخت type)
{
  منطقي int_const, int_operands;

  بدل (درخت_کد (درخت_TYPE (عبارت)))
    {
    حالة ARRAY_TYPE:
      error_at (location, "used array that cannot be converted to pointer where scalar is required");
      أرجع error_mark_گره;

    حالة رکورد_TYPE:
      error_at (location, "used struct type value where scalar is required");
      أرجع error_mark_گره;

    حالة UNION_TYPE:
      error_at (location, "used union type value where scalar is required");
      أرجع error_mark_گره;

    حالة VOID_TYPE:
      error_at (location, "void value not ignored as it ought to be");
      أرجع error_mark_گره;

    حالة اشاره_گر_TYPE:
      إذا (reject_gcc_builtin (عبارت))
	أرجع error_mark_گره;
      اكسر;

    حالة FUNCTION_TYPE:
      gcc_unreachable ();

    حالة وکتور_TYPE:
      error_at (location, "used vector type where scalar is required");
      أرجع error_mark_گره;

    افتراضي:
      اكسر;
    }

  /* Conversion of a floating constant to boolean goes through here
     and yields an integer constant expression.  Otherwise, the result
     is only an integer constant expression if the argument is.  */
  int_const = ((درخت_کد (عبارت) == INTEGER_CST && !درخت_سرریز (عبارت))
	       || ((درخت_کد (عبارت) == REAL_CST
		    || درخت_کد (عبارت) == COMPLEX_CST)
		   && (درخت_کد (type) == BOOLEAN_TYPE
		       || (درخت_کد (type) == ENUMERAL_TYPE
			   && ENUM_UNDERLYING_TYPE (type) != NULL_درخت
			   && (درخت_کد (ENUM_UNDERLYING_TYPE (type))
			       == BOOLEAN_TYPE)))));
  int_operands = عبارت_INT_CONST_OPERANDS (عبارت);
  إذا (int_operands && درخت_کد (عبارت) != INTEGER_CST)
    {
      عبارت = remove_c_maybe_const_عبارت (عبارت);
      عبارت = build2 (NE_عبارت, type, عبارت,
		     convert (درخت_TYPE (عبارت), integer_zero_گره));
      عبارت = note_integer_operands (عبارت);
    }
  وإلا
    {
      /* ??? Should we also give an error for vectors rather than leaving
	 those to give errors later?  */
      عبارت = c_common_truthvalue_conversion (location, عبارت);
      عبارت = fold_convert_loc (location, type, عبارت);
    }

  إذا (درخت_کد (عبارت) == INTEGER_CST && int_operands && !int_const)
    {
      إذا (درخت_سرریز (عبارت))
	أرجع عبارت;
      وإلا
	أرجع note_integer_operands (عبارت);
    }
  إذا (درخت_کد (عبارت) == INTEGER_CST && !int_const)
    أرجع build1 (NOP_عبارت, درخت_TYPE (عبارت), عبارت);
  أرجع عبارت;
}


/* Convert EXPR to a contained DECL, updating *TC, *TI and *SE as
   required.  */

درخت
c_عبارت_مقصد_decl (درخت عبارت, منطقي *tc ATTRIBUTE_استفادهنشده, منطقي *se)
{
  إذا (درخت_کد (عبارت) == COMPOUND_LITERAL_عبارت)
    {
      درخت decl = COMPOUND_LITERAL_عبارت_DECL (عبارت);
      /* Executing a compound literal inside a function reinitializes
	 it.  */
      إذا (!درخت_STATIC (decl))
	*se = درست;
      أرجع decl;
    }
  وإلا
    أرجع عبارت;
}

/* Generate OMP construct CODE, with BODY and CLAUSES as its compound
   statement.  LOC is the location of the construct.  */

درخت
c_پایان_omp_construct (location_t loc, تعداد درخت_کد_2 کد, درخت body,
			درخت clauses)
{
  body = c_انتها_compound_stmt (loc, body, درست);

  درخت stmt = make_گره (کد);
  درخت_TYPE (stmt) = void_type_گره;
  OMP_BODY (stmt) = body;
  OMP_CLAUSES (stmt) = clauses;
  مجموعه_عبارت_LOCATION (stmt, loc);

  أرجع جمع_کن_stmt (stmt);
}

/* Generate OACC_DATA, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the OACC_DATA.  */

درخت
c_پایان_oacc_داده (location_t loc, درخت clauses, درخت بلوک)
{
  درخت stmt;

  بلوک = c_انتها_compound_stmt (loc, بلوک, درست);

  stmt = make_گره (OACC_داده);
  درخت_TYPE (stmt) = void_type_گره;
  OACC_داده_CLAUSES (stmt) = clauses;
  OACC_داده_BODY (stmt) = بلوک;
  مجموعه_عبارت_LOCATION (stmt, loc);

  أرجع جمع_کن_stmt (stmt);
}

/* Generate OACC_HOST_DATA, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the OACC_HOST_DATA.  */

درخت
c_پایان_oacc_host_داده (location_t loc, درخت clauses, درخت بلوک)
{
  درخت stmt;

  بلوک = c_انتها_compound_stmt (loc, بلوک, درست);

  stmt = make_گره (OACC_HOST_داده);
  درخت_TYPE (stmt) = void_type_گره;
  OACC_HOST_داده_CLAUSES (stmt) = clauses;
  OACC_HOST_داده_BODY (stmt) = بلوک;
  مجموعه_عبارت_LOCATION (stmt, loc);

  أرجع جمع_کن_stmt (stmt);
}

/* Like c_begin_compound_stmt, except force the retention of the BLOCK.  */

درخت
c_begin_omp_parallel (فراغ)
{
  درخت بلوک;

  keep_بعدی_level ();
  بلوک = c_begin_compound_stmt (درست);

  أرجع بلوک;
}

/* Generate OMP_PARALLEL, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the OMP_PARALLEL.  */

درخت
c_پایان_omp_parallel (location_t loc, درخت clauses, درخت بلوک)
{
  درخت stmt;

  بلوک = c_انتها_compound_stmt (loc, بلوک, درست);

  stmt = make_گره (OMP_PARALLEL);
  درخت_TYPE (stmt) = void_type_گره;
  OMP_PARALLEL_CLAUSES (stmt) = clauses;
  OMP_PARALLEL_BODY (stmt) = بلوک;
  مجموعه_عبارت_LOCATION (stmt, loc);

  أرجع جمع_کن_stmt (stmt);
}

/* Like c_begin_compound_stmt, except force the retention of the BLOCK.  */

درخت
c_begin_omp_task (فراغ)
{
  درخت بلوک;

  keep_بعدی_level ();
  بلوک = c_begin_compound_stmt (درست);

  أرجع بلوک;
}

/* Generate OMP_TASK, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the #pragma.  */

درخت
c_پایان_omp_task (location_t loc, درخت clauses, درخت بلوک)
{
  درخت stmt;

  بلوک = c_انتها_compound_stmt (loc, بلوک, درست);

  stmt = make_گره (OMP_TASK);
  درخت_TYPE (stmt) = void_type_گره;
  OMP_TASK_CLAUSES (stmt) = clauses;
  OMP_TASK_BODY (stmt) = بلوک;
  مجموعه_عبارت_LOCATION (stmt, loc);

  أرجع جمع_کن_stmt (stmt);
}

/* Generate GOMP_cancel call for #pragma omp cancel.  */

فراغ
c_پایان_omp_cancel (location_t loc, درخت clauses)
{
  درخت fn = builtin_decl_explicit (BUILT_درون_GOMP_CANCEL);
  صحيح ماسک = 0;
  إذا (omp_پیدا_کن_clause (clauses, OMP_CLAUSE_PARALLEL))
    ماسک = 1;
  وإلا إذا (omp_پیدا_کن_clause (clauses, OMP_CLAUSE_FOR))
    ماسک = 2;
  وإلا إذا (omp_پیدا_کن_clause (clauses, OMP_CLAUSE_SECTIONS))
    ماسک = 4;
  وإلا إذا (omp_پیدا_کن_clause (clauses, OMP_CLAUSE_TASKGROUP))
    ماسک = 8;
  وإلا
    {
      error_at (loc, "%<#pragma omp cancel%> must specify one of "
		     "%<parallel%>, %<for%>, %<sections%> or %<taskgroup%> "
		     "clauses");
      أرجع;
    }
  درخت ifc = omp_پیدا_کن_clause (clauses, OMP_CLAUSE_IF);
  إذا (ifc != NULL_درخت)
    {
      إذا (OMP_CLAUSE_IF_MODIFIER (ifc) != ERROR_MARK
	  && OMP_CLAUSE_IF_MODIFIER (ifc) != VOID_CST)
	error_at (OMP_CLAUSE_LOCATION (ifc),
		  "expected %<cancel%> %<if%> clause modifier");
      وإلا
	{
	  درخت ifc2 = omp_پیدا_کن_clause (OMP_CLAUSE_CHAIN (ifc), OMP_CLAUSE_IF);
	  إذا (ifc2 != NULL_درخت)
	    {
	      gcc_assert (OMP_CLAUSE_IF_MODIFIER (ifc) == VOID_CST
			  && OMP_CLAUSE_IF_MODIFIER (ifc2) != ERROR_MARK
			  && OMP_CLAUSE_IF_MODIFIER (ifc2) != VOID_CST);
	      error_at (OMP_CLAUSE_LOCATION (ifc2),
			"expected %<cancel%> %<if%> clause modifier");
	    }
	}

      درخت type = درخت_TYPE (OMP_CLAUSE_IF_عبارت (ifc));
      ifc = fold_build2_loc (OMP_CLAUSE_LOCATION (ifc), NE_عبارت,
			     boolean_type_گره, OMP_CLAUSE_IF_عبارت (ifc),
			     build_zero_cst (type));
    }
  وإلا
    ifc = boolean_true_گره;
  درخت stmt = build_call_عبارت_loc (loc, fn, 2,
				   build_int_cst (integer_type_گره, ماسک),
				   ifc);
  جمع_کن_stmt (stmt);
}

/* Generate GOMP_cancellation_point call for
   #pragma omp cancellation point.  */

فراغ
c_پایان_omp_cancellation_نقطه (location_t loc, درخت clauses)
{
  درخت fn = builtin_decl_explicit (BUILT_درون_GOMP_CANCELLATION_نقطه);
  صحيح ماسک = 0;
  إذا (omp_پیدا_کن_clause (clauses, OMP_CLAUSE_PARALLEL))
    ماسک = 1;
  وإلا إذا (omp_پیدا_کن_clause (clauses, OMP_CLAUSE_FOR))
    ماسک = 2;
  وإلا إذا (omp_پیدا_کن_clause (clauses, OMP_CLAUSE_SECTIONS))
    ماسک = 4;
  وإلا إذا (omp_پیدا_کن_clause (clauses, OMP_CLAUSE_TASKGROUP))
    ماسک = 8;
  وإلا
    {
      error_at (loc, "%<#pragma omp cancellation point%> must specify one of "
		     "%<parallel%>, %<for%>, %<sections%> or %<taskgroup%> "
		     "clauses");
      أرجع;
    }
  درخت stmt = build_call_عبارت_loc (loc, fn, 1,
				   build_int_cst (integer_type_گره, ماسک));
  جمع_کن_stmt (stmt);
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

ساكن درخت
handle_omp_array_sections_1 (درخت c, درخت t, vec<درخت> &types,
			     منطقي &maybe_zero_len, بیعلامت صحيح &اولی_non_one,
			     تعداد c_omp_region_type ort)
{
  درخت ret, کم_bound, درازی, type;
  منطقي openacc = (ort & C_ORT_ACC) != 0;
  إذا (درخت_کد (t) != OMP_ARRAY_SECTION)
    {
      إذا (error_عملوند_p (t))
	أرجع error_mark_گره;
      c_omp_آدرس_inspector ai (OMP_CLAUSE_LOCATION (c), t);
      ret = t;
      إذا (OMP_CLAUSE_کد (c) != OMP_CLAUSE_AFFINITY
	  && OMP_CLAUSE_کد (c) != OMP_CLAUSE_DEPEND
	  && TYPE_ATOMIC (strip_array_types (درخت_TYPE (t))))
	{
	  error_at (OMP_CLAUSE_LOCATION (c), "%<_Atomic%> %qE in %qs clause",
		    t, omp_clause_کد_name[OMP_CLAUSE_کد (c)]);
	  أرجع error_mark_گره;
	}
      إذا (!ai.check_clause (c))
	أرجع error_mark_گره;
      وإلا إذا (ai.component_access_p ()
	       && (OMP_CLAUSE_کد (c) == OMP_CLAUSE_MAP
		   || OMP_CLAUSE_کد (c) == OMP_CLAUSE_مقصد
		   || OMP_CLAUSE_کد (c) == OMP_CLAUSE_FROM))
	t = ai.get_ریشه_جمله (درست);
      وإلا
	t = ai.unconverted_ref_origin ();
      إذا (t == error_mark_گره)
	أرجع error_mark_گره;
      إذا (!VAR_P (t)
	  && (ort == C_ORT_ACC || !عبارت_P (t))
	  && درخت_کد (t) != PARM_DECL)
	{
	  إذا (DECL_P (t))
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD is not a variable in %qs clause", t,
		      omp_clause_کد_name[OMP_CLAUSE_کد (c)]);
	  وإلا
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qE is not a variable in %qs clause", t,
		      omp_clause_کد_name[OMP_CLAUSE_کد (c)]);
	  أرجع error_mark_گره;
	}
      وإلا إذا (OMP_CLAUSE_کد (c) != OMP_CLAUSE_AFFINITY
	       && OMP_CLAUSE_کد (c) != OMP_CLAUSE_DEPEND
	       && TYPE_ATOMIC (درخت_TYPE (t)))
	{
	  error_at (OMP_CLAUSE_LOCATION (c), "%<_Atomic%> %qD in %qs clause",
		    t, omp_clause_کد_name[OMP_CLAUSE_کد (c)]);
	  أرجع error_mark_گره;
	}
      وإلا إذا (OMP_CLAUSE_کد (c) != OMP_CLAUSE_AFFINITY
	       && OMP_CLAUSE_کد (c) != OMP_CLAUSE_DEPEND
	       && VAR_P (t)
	       && DECL_THREAD_LOCAL_P (t))
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "%qD is threadprivate variable in %qs clause", t,
		    omp_clause_کد_name[OMP_CLAUSE_کد (c)]);
	  أرجع error_mark_گره;
	}
      إذا ((OMP_CLAUSE_کد (c) == OMP_CLAUSE_AFFINITY
	   || OMP_CLAUSE_کد (c) == OMP_CLAUSE_DEPEND)
	  && TYPE_ATOMIC (درخت_TYPE (t))
	  && اشاره_گر_TYPE_P (درخت_TYPE (t)))
	{
	  /* If the array section is pointer based and the pointer
	     itself is _Atomic qualified, we need to atomically load
	     the pointer.  */
	  ret = convert_lvalue_مقصد_rvalue (OMP_CLAUSE_LOCATION (c),
					  ret, خطأ, خطأ);
	}
      أرجع ret;
    }

  ret = handle_omp_array_sections_1 (c, درخت_عملوند (t, 0), types,
				     maybe_zero_len, اولی_non_one, ort);
  إذا (ret == error_mark_گره || ret == NULL_درخت)
    أرجع ret;

  type = درخت_TYPE (ret);
  کم_bound = درخت_عملوند (t, 1);
  درازی = درخت_عملوند (t, 2);

  إذا (کم_bound == error_mark_گره || درازی == error_mark_گره)
    أرجع error_mark_گره;

  إذا (کم_bound && !INTEGRAL_TYPE_P (درخت_TYPE (کم_bound)))
    {
      error_at (OMP_CLAUSE_LOCATION (c),
		"low bound %qE of array section does not have integral type",
		کم_bound);
      أرجع error_mark_گره;
    }
  إذا (درازی && !INTEGRAL_TYPE_P (درخت_TYPE (درازی)))
    {
      error_at (OMP_CLAUSE_LOCATION (c),
		"length %qE of array section does not have integral type",
		درازی);
      أرجع error_mark_گره;
    }
  إذا (کم_bound
      && درخت_کد (کم_bound) == INTEGER_CST
      && TYPE_PRECISION (درخت_TYPE (کم_bound))
	 > TYPE_PRECISION (sizetype))
    کم_bound = fold_convert (sizetype, کم_bound);
  إذا (درازی
      && درخت_کد (درازی) == INTEGER_CST
      && TYPE_PRECISION (درخت_TYPE (درازی))
	 > TYPE_PRECISION (sizetype))
    درازی = fold_convert (sizetype, درازی);
  إذا (کم_bound == NULL_درخت)
    کم_bound = integer_zero_گره;
  إذا (OMP_CLAUSE_کد (c) == OMP_CLAUSE_MAP
      && (OMP_CLAUSE_MAP_نوع (c) == GOMP_MAP_ATTACH
	  || OMP_CLAUSE_MAP_نوع (c) == GOMP_MAP_DETACH))
    {
      إذا (درازی != integer_one_گره)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "expected single pointer in %qs clause",
		    user_omp_clause_کد_name (c, openacc));
	  أرجع error_mark_گره;
	}
    }
  إذا (درازی != NULL_درخت)
    {
      إذا (!integer_nonzerop (درازی))
	{
	  إذا (OMP_CLAUSE_کد (c) == OMP_CLAUSE_AFFINITY
	      || OMP_CLAUSE_کد (c) == OMP_CLAUSE_DEPEND
	      || OMP_CLAUSE_کد (c) == OMP_CLAUSE_REDUCTION
	      || OMP_CLAUSE_کد (c) == OMP_CLAUSE_درون_REDUCTION
	      || OMP_CLAUSE_کد (c) == OMP_CLAUSE_TASK_REDUCTION)
	    {
	      إذا (integer_zerop (درازی))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "zero length array section in %qs clause",
			    omp_clause_کد_name[OMP_CLAUSE_کد (c)]);
		  أرجع error_mark_گره;
		}
	    }
	  وإلا
	    maybe_zero_len = درست;
	}
      إذا (اولی_non_one == types.درازی ()
	  && (درخت_کد (درازی) != INTEGER_CST || integer_onep (درازی)))
	اولی_non_one++;
    }
  إذا (درخت_کد (type) == ARRAY_TYPE)
    {
      إذا (درازی == NULL_درخت
	  && (TYPE_DOMAIN (type) == NULL_درخت
	      || TYPE_MAX_مقدار (TYPE_DOMAIN (type)) == NULL_درخت))
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "for unknown bound array type length expression must "
		    "be specified");
	  أرجع error_mark_گره;
	}
      إذا (درخت_کد (کم_bound) == INTEGER_CST
	  && درخت_int_cst_sgn (کم_bound) == -1)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "negative low bound in array section in %qs clause",
		    omp_clause_کد_name[OMP_CLAUSE_کد (c)]);
	  أرجع error_mark_گره;
	}
      إذا (درازی != NULL_درخت
	  && درخت_کد (درازی) == INTEGER_CST
	  && درخت_int_cst_sgn (درازی) == -1)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "negative length in array section in %qs clause",
		    omp_clause_کد_name[OMP_CLAUSE_کد (c)]);
	  أرجع error_mark_گره;
	}
      إذا (TYPE_DOMAIN (type)
	  && TYPE_MAX_مقدار (TYPE_DOMAIN (type))
	  && درخت_کد (TYPE_MAX_مقدار (TYPE_DOMAIN (type)))
			== INTEGER_CST)
	{
	  درخت اندازه
	    = fold_convert (sizetype, TYPE_MAX_مقدار (TYPE_DOMAIN (type)));
	  اندازه = اندازه_binop (PLUS_عبارت, اندازه, اندازه_one_گره);
	  إذا (درخت_کد (کم_bound) == INTEGER_CST)
	    {
	      إذا (درخت_int_cst_lt (اندازه, کم_bound))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "low bound %qE above array section size "
			    "in %qs clause", کم_bound,
			    omp_clause_کد_name[OMP_CLAUSE_کد (c)]);
		  أرجع error_mark_گره;
		}
	      إذا (درخت_int_cst_equal (اندازه, کم_bound))
		{
		  إذا (OMP_CLAUSE_کد (c) == OMP_CLAUSE_AFFINITY
		      || OMP_CLAUSE_کد (c) == OMP_CLAUSE_DEPEND
		      || OMP_CLAUSE_کد (c) == OMP_CLAUSE_REDUCTION
		      || OMP_CLAUSE_کد (c) == OMP_CLAUSE_درون_REDUCTION
		      || OMP_CLAUSE_کد (c) == OMP_CLAUSE_TASK_REDUCTION)
		    {
		      error_at (OMP_CLAUSE_LOCATION (c),
				"zero length array section in %qs clause",
				omp_clause_کد_name[OMP_CLAUSE_کد (c)]);
		      أرجع error_mark_گره;
		    }
		  maybe_zero_len = درست;
		}
	      وإلا إذا (درازی == NULL_درخت
		       && اولی_non_one == types.درازی ()
		       && درخت_int_cst_equal
			    (TYPE_MAX_مقدار (TYPE_DOMAIN (type)),
			     کم_bound))
		اولی_non_one++;
	    }
	  وإلا إذا (درازی == NULL_درخت)
	    {
	      إذا (OMP_CLAUSE_کد (c) != OMP_CLAUSE_AFFINITY
		  && OMP_CLAUSE_کد (c) != OMP_CLAUSE_DEPEND
		  && OMP_CLAUSE_کد (c) != OMP_CLAUSE_REDUCTION
		  && OMP_CLAUSE_کد (c) != OMP_CLAUSE_درون_REDUCTION
		  && OMP_CLAUSE_کد (c) != OMP_CLAUSE_TASK_REDUCTION)
		maybe_zero_len = درست;
	      إذا (اولی_non_one == types.درازی ())
		اولی_non_one++;
	    }
	  إذا (درازی && درخت_کد (درازی) == INTEGER_CST)
	    {
	      إذا (درخت_int_cst_lt (اندازه, درازی))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "length %qE above array section size "
			    "in %qs clause", درازی,
			    omp_clause_کد_name[OMP_CLAUSE_کد (c)]);
		  أرجع error_mark_گره;
		}
	      إذا (درخت_کد (کم_bound) == INTEGER_CST)
		{
		  درخت lbpluslen
		    = اندازه_binop (PLUS_عبارت,
				  fold_convert (sizetype, کم_bound),
				  fold_convert (sizetype, درازی));
		  إذا (درخت_کد (lbpluslen) == INTEGER_CST
		      && درخت_int_cst_lt (اندازه, lbpluslen))
		    {
		      error_at (OMP_CLAUSE_LOCATION (c),
				"high bound %qE above array section size "
				"in %qs clause", lbpluslen,
				omp_clause_کد_name[OMP_CLAUSE_کد (c)]);
		      أرجع error_mark_گره;
		    }
		}
	    }
	}
      وإلا إذا (درازی == NULL_درخت)
	{
	  إذا (OMP_CLAUSE_کد (c) != OMP_CLAUSE_AFFINITY
	      && OMP_CLAUSE_کد (c) != OMP_CLAUSE_DEPEND
	      && OMP_CLAUSE_کد (c) != OMP_CLAUSE_REDUCTION
	      && OMP_CLAUSE_کد (c) != OMP_CLAUSE_درون_REDUCTION
	      && OMP_CLAUSE_کد (c) != OMP_CLAUSE_TASK_REDUCTION)
	    maybe_zero_len = درست;
	  إذا (اولی_non_one == types.درازی ())
	    اولی_non_one++;
	}

      /* For [lb:] we will need to evaluate lb more than once.  */
      إذا (درازی == NULL_درخت && OMP_CLAUSE_کد (c) != OMP_CLAUSE_DEPEND)
	{
	  درخت lb = save_عبارت (کم_bound);
	  إذا (lb != کم_bound)
	    {
	      درخت_عملوند (t, 1) = lb;
	      کم_bound = lb;
	    }
	}
    }
  وإلا إذا (درخت_کد (type) == اشاره_گر_TYPE)
    {
      إذا (درازی == NULL_درخت)
	{
	  إذا (درخت_کد (ret) == PARM_DECL && C_ARRAY_PARAMETER (ret))
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "for array function parameter length expression "
		      "must be specified");
	  وإلا
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "for pointer type length expression must be specified");
	  أرجع error_mark_گره;
	}
      إذا (درازی != NULL_درخت
	  && درخت_کد (درازی) == INTEGER_CST
	  && درخت_int_cst_sgn (درازی) == -1)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "negative length in array section in %qs clause",
		    omp_clause_کد_name[OMP_CLAUSE_کد (c)]);
	  أرجع error_mark_گره;
	}
      /* If there is a pointer type anywhere but in the very first
	 array-section-subscript, the array section could be non-contiguous.  */
      إذا (OMP_CLAUSE_کد (c) != OMP_CLAUSE_DEPEND
	  && OMP_CLAUSE_کد (c) != OMP_CLAUSE_AFFINITY
	  && درخت_کد (درخت_عملوند (t, 0)) == OMP_ARRAY_SECTION)
	{
	  /* If any prior dimension has a non-one length, then deem this
	     array section as non-contiguous.  */
	  لكل (درخت d = درخت_عملوند (t, 0);
	       درخت_کد (d) == OMP_ARRAY_SECTION;
	       d = درخت_عملوند (d, 0))
	    {
	      درخت d_درازی = درخت_عملوند (d, 2);
	      إذا (d_درازی == NULL_درخت || !integer_onep (d_درازی))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "array section is not contiguous in %qs clause",
			    omp_clause_کد_name[OMP_CLAUSE_کد (c)]);
		  أرجع error_mark_گره;
		}
	    }
	}
    }
  وإلا
    {
      error_at (OMP_CLAUSE_LOCATION (c),
		"%qE does not have pointer or array type", ret);
      أرجع error_mark_گره;
    }
  إذا (OMP_CLAUSE_کد (c) != OMP_CLAUSE_DEPEND)
    types.امن_افزودن (درخت_TYPE (ret));
  /* We will need to evaluate lb more than once.  */
  درخت lb = save_عبارت (کم_bound);
  إذا (lb != کم_bound)
    {
      درخت_عملوند (t, 1) = lb;
      کم_bound = lb;
    }
  ret = build_array_ref (OMP_CLAUSE_LOCATION (c), ret, کم_bound);
  أرجع ret;
}

/* Handle array sections for clause C.  */

ساكن منطقي
handle_omp_array_sections (درخت &c, تعداد c_omp_region_type ort)
{
  منطقي maybe_zero_len = خطأ;
  بیعلامت صحيح اولی_non_one = 0;
  auto_vec<درخت, 10> types;
  درخت *tp = &OMP_CLAUSE_DECL (c);
  إذا ((OMP_CLAUSE_کد (c) == OMP_CLAUSE_DEPEND
       || OMP_CLAUSE_کد (c) == OMP_CLAUSE_AFFINITY)
      && OMP_ITERATOR_DECL_P (*tp))
    tp = &درخت_مقدار (*tp);
  درخت اولی = handle_omp_array_sections_1 (c, *tp, types,
					    maybe_zero_len, اولی_non_one,
					    ort);
  إذا (اولی == error_mark_گره)
    أرجع درست;
  إذا (اولی == NULL_درخت)
    أرجع خطأ;
  إذا (OMP_CLAUSE_کد (c) == OMP_CLAUSE_DEPEND
      || OMP_CLAUSE_کد (c) == OMP_CLAUSE_AFFINITY)
    {
      درخت t = *tp;
      درخت tem = NULL_درخت;
      /* Need to evaluate side effects in the length expressions
	 if any.  */
      طالما (درخت_کد (t) == درخت_LIST)
	{
	  إذا (درخت_مقدار (t) && درخت_SIDE_EFFECTS (درخت_مقدار (t)))
	    {
	      إذا (tem == NULL_درخت)
		tem = درخت_مقدار (t);
	      وإلا
		tem = build2 (COMPOUND_عبارت, درخت_TYPE (tem),
			      درخت_مقدار (t), tem);
	    }
	  t = درخت_CHAIN (t);
	}
      إذا (tem)
	اولی = build2 (COMPOUND_عبارت, درخت_TYPE (اولی), tem, اولی);
      اولی = c_fully_fold (اولی, خطأ, عدم, درست);
      *tp = اولی;
    }
  وإلا
    {
      بیعلامت صحيح رقم = types.درازی (), i;
      درخت t, side_effects = NULL_درخت, اندازه = NULL_درخت;
      درخت condition = NULL_درخت;

      إذا (int_اندازه_درون_بایتها (درخت_TYPE (اولی)) <= 0)
	maybe_zero_len = درست;

      لكل (i = رقم, t = OMP_CLAUSE_DECL (c); i > 0;
	   t = درخت_عملوند (t, 0))
	{
	  درخت کم_bound = درخت_عملوند (t, 1);
	  درخت درازی = درخت_عملوند (t, 2);

	  i--;
	  إذا (کم_bound
	      && درخت_کد (کم_bound) == INTEGER_CST
	      && TYPE_PRECISION (درخت_TYPE (کم_bound))
		 > TYPE_PRECISION (sizetype))
	    کم_bound = fold_convert (sizetype, کم_bound);
	  إذا (درازی
	      && درخت_کد (درازی) == INTEGER_CST
	      && TYPE_PRECISION (درخت_TYPE (درازی))
		 > TYPE_PRECISION (sizetype))
	    درازی = fold_convert (sizetype, درازی);
	  إذا (کم_bound == NULL_درخت)
	    کم_bound = integer_zero_گره;
	  إذا (!maybe_zero_len && i > اولی_non_one)
	    {
	      إذا (integer_nonzerop (کم_bound))
		اذهب do_warn_noncontiguous;
	      إذا (درازی != NULL_درخت
		  && درخت_کد (درازی) == INTEGER_CST
		  && TYPE_DOMAIN (types[i])
		  && TYPE_MAX_مقدار (TYPE_DOMAIN (types[i]))
		  && درخت_کد (TYPE_MAX_مقدار (TYPE_DOMAIN (types[i])))
		     == INTEGER_CST)
		{
		  درخت اندازه;
		  اندازه = اندازه_binop (PLUS_عبارت,
				     TYPE_MAX_مقدار (TYPE_DOMAIN (types[i])),
				     اندازه_one_گره);
		  إذا (!درخت_int_cst_equal (درازی, اندازه))
		    {
		     do_warn_noncontiguous:
		      error_at (OMP_CLAUSE_LOCATION (c),
				"array section is not contiguous in %qs "
				"clause",
				omp_clause_کد_name[OMP_CLAUSE_کد (c)]);
		      أرجع درست;
		    }
		}
	      إذا (درازی != NULL_درخت
		  && درخت_SIDE_EFFECTS (درازی))
		{
		  إذا (side_effects == NULL_درخت)
		    side_effects = درازی;
		  وإلا
		    side_effects = build2 (COMPOUND_عبارت,
					   درخت_TYPE (side_effects),
					   درازی, side_effects);
		}
	    }
	  وإلا
	    {
	      درخت l;

	      إذا (i > اولی_non_one
		  && ((درازی && integer_nonzerop (درازی))
		      || OMP_CLAUSE_کد (c) == OMP_CLAUSE_REDUCTION
		      || OMP_CLAUSE_کد (c) == OMP_CLAUSE_درون_REDUCTION
		      || OMP_CLAUSE_کد (c) == OMP_CLAUSE_TASK_REDUCTION))
		استمر;
	      إذا (درازی)
		l = fold_convert (sizetype, درازی);
	      وإلا
		{
		  l = اندازه_binop (PLUS_عبارت,
				  TYPE_MAX_مقدار (TYPE_DOMAIN (types[i])),
				  اندازه_one_گره);
		  l = اندازه_binop (MINUS_عبارت, l,
				  fold_convert (sizetype, کم_bound));
		}
	      إذا (i > اولی_non_one)
		{
		  l = fold_build2 (NE_عبارت, boolean_type_گره, l,
				   اندازه_zero_گره);
		  إذا (condition == NULL_درخت)
		    condition = l;
		  وإلا
		    condition = fold_build2 (بیت_AND_عبارت, boolean_type_گره,
					     l, condition);
		}
	      وإلا إذا (اندازه == NULL_درخت)
		{
		  اندازه = اندازه_درون_بایتها (درخت_TYPE (types[i]));
		  درخت eltype = درخت_TYPE (types[رقم - 1]);
		  طالما (درخت_کد (eltype) == ARRAY_TYPE)
		    eltype = درخت_TYPE (eltype);
		  إذا (OMP_CLAUSE_کد (c) == OMP_CLAUSE_REDUCTION
		      || OMP_CLAUSE_کد (c) == OMP_CLAUSE_درون_REDUCTION
		      || OMP_CLAUSE_کد (c) == OMP_CLAUSE_TASK_REDUCTION)
		    {
		      إذا (integer_zerop (اندازه)
			  || integer_zerop (اندازه_درون_بایتها (eltype)))
			{
			  error_at (OMP_CLAUSE_LOCATION (c),
				    "zero length array section in %qs clause",
				    omp_clause_کد_name[OMP_CLAUSE_کد (c)]);
			  أرجع error_mark_گره;
			}
		      اندازه = اندازه_binop (EXACT_DIV_عبارت, اندازه,
					 اندازه_درون_بایتها (eltype));
		    }
		  اندازه = اندازه_binop (MULT_عبارت, اندازه, l);
		  إذا (condition)
		    اندازه = fold_build3 (COND_عبارت, sizetype, condition,
					اندازه, اندازه_zero_گره);
		}
	      وإلا
		اندازه = اندازه_binop (MULT_عبارت, اندازه, l);
	    }
	}
      إذا (side_effects)
	اندازه = build2 (COMPOUND_عبارت, sizetype, side_effects, اندازه);
      إذا (OMP_CLAUSE_کد (c) == OMP_CLAUSE_REDUCTION
	  || OMP_CLAUSE_کد (c) == OMP_CLAUSE_درون_REDUCTION
	  || OMP_CLAUSE_کد (c) == OMP_CLAUSE_TASK_REDUCTION)
	{
	  اندازه = اندازه_binop (MINUS_عبارت, اندازه, اندازه_one_گره);
	  اندازه = c_fully_fold (اندازه, خطأ, عدم);
	  اندازه = save_عبارت (اندازه);
	  درخت شاخص_type = build_شاخص_type (اندازه);
	  درخت eltype = درخت_TYPE (اولی);
	  طالما (درخت_کد (eltype) == ARRAY_TYPE)
	    eltype = درخت_TYPE (eltype);
	  درخت type = c_build_array_type (eltype, شاخص_type);
	  درخت ptype = c_build_اشاره_گر_type (eltype);
	  إذا (درخت_کد (درخت_TYPE (t)) == ARRAY_TYPE)
	    t = build_fold_addr_عبارت (t);
	  درخت t2 = build_fold_addr_عبارت (اولی);
	  t2 = fold_convert_loc (OMP_CLAUSE_LOCATION (c),
				 ptrdiff_type_گره, t2);
	  t2 = fold_build2_loc (OMP_CLAUSE_LOCATION (c), MINUS_عبارت,
				ptrdiff_type_گره, t2,
				fold_convert_loc (OMP_CLAUSE_LOCATION (c),
						  ptrdiff_type_گره, t));
	  t2 = c_fully_fold (t2, خطأ, عدم);
	  إذا (درخت_میگنجد_shwi_p (t2))
	    t = build2 (MEM_REF, type, t,
			build_int_cst (ptype, درخت_مقصد_shwi (t2)));
	  وإلا
	    {
	      t2 = fold_convert_loc (OMP_CLAUSE_LOCATION (c), sizetype, t2);
	      t = build2_loc (OMP_CLAUSE_LOCATION (c), اشاره_گر_PLUS_عبارت,
			      درخت_TYPE (t), t, t2);
	      t = build2 (MEM_REF, type, t, build_int_cst (ptype, 0));
	    }
	  OMP_CLAUSE_DECL (c) = t;
	  أرجع خطأ;
	}
      اولی = c_fully_fold (اولی, خطأ, عدم);
      OMP_CLAUSE_DECL (c) = اولی;
      إذا (OMP_CLAUSE_کد (c) == OMP_CLAUSE_HAS_DEVICE_ADDR)
	أرجع خطأ;
      /* Don't set OMP_CLAUSE_SIZE for bare attach/detach clauses.  */
      إذا (OMP_CLAUSE_کد (c) != OMP_CLAUSE_MAP
	  || (OMP_CLAUSE_MAP_نوع (c) != GOMP_MAP_ATTACH
	      && OMP_CLAUSE_MAP_نوع (c) != GOMP_MAP_DETACH
	      && OMP_CLAUSE_MAP_نوع (c) != GOMP_MAP_FORCE_DETACH))
	{
	  إذا (اندازه)
	    اندازه = c_fully_fold (اندازه, خطأ, عدم);
	  OMP_CLAUSE_اندازه (c) = اندازه;
	}

      إذا (OMP_CLAUSE_کد (c) != OMP_CLAUSE_MAP)
	أرجع خطأ;

      auto_vec<omp_addr_token *, 10> addr_نشانهها;

      إذا (!omp_parse_عبارت (addr_نشانهها, اولی))
	أرجع درست;

      c_omp_آدرس_inspector ai (OMP_CLAUSE_LOCATION (c), t);

      درخت nc = ai.expand_map_clause (c, اولی, addr_نشانهها, ort);
      إذا (nc != error_mark_گره)
	{
	  استفاده نطاق omp_addr_tokenizer;

	  إذا (ai.maybe_zero_درازی_array_section (c))
	    OMP_CLAUSE_MAP_MAYBE_ZERO_درازی_ARRAY_SECTION (c) = 1;

	  /* !!! If we're accessing a base decl via chained access
	     methods (e.g. multiple indirections), duplicate clause
	     detection won't work properly.  Skip it in that case.  */
	  إذا ((addr_نشانهها[0]->type == STRUCTURE_پایه
	       || addr_نشانهها[0]->type == ARRAY_پایه)
	      && addr_نشانهها[0]->u.structure_پایه_نوع == پایه_DECL
	      && addr_نشانهها[1]->type == ACCESS_روش
	      && omp_access_chain_p (addr_نشانهها, 1))
	    c = nc;

	  أرجع خطأ;
	}
    }
  أرجع خطأ;
}

/* Helper function of finish_omp_clauses.  Clone STMT as if we were making
   an inline call.  But, remap
   the OMP_DECL1 VAR_DECL (omp_out resp. omp_orig) to PLACEHOLDER
   and OMP_DECL2 VAR_DECL (omp_in resp. omp_priv) to DECL.  */

ساكن درخت
c_clone_omp_udr (درخت stmt, درخت omp_decl1, درخت omp_decl2,
		 درخت decl, درخت placeholder)
{
  copy_body_داده id;
  hash_map<درخت, درخت> decl_map;

  decl_map.put (omp_decl1, placeholder);
  decl_map.put (omp_decl2, decl);
  memset (&id, 0, حجم (id));
  id.src_fn = DECL_CONTEXT (omp_decl1);
  id.dst_fn = current_function_decl;
  id.src_cfun = DECL_STRUCT_FUNCTION (id.src_fn);
  id.decl_map = &decl_map;

  id.copy_decl = copy_decl_no_change;
  id.transform_call_گراف_یالها = CB_CGE_DUPLICATE;
  id.transform_new_cfg = درست;
  id.transform_return_مقصد_modify = خطأ;
  id.eh_lp_nr = 0;
  walk_درخت (&stmt, copy_درخت_body_r, &id, عدم);
  أرجع stmt;
}

/* Helper function of c_finish_omp_clauses, called via walk_tree.
   Find OMP_CLAUSE_PLACEHOLDER (passed in DATA) in *TP.  */

ساكن درخت
c_پیدا_کن_omp_placeholder_r (درخت *tp, صحيح *, فراغ *داده)
{
  إذا (*tp == (درخت) داده)
    أرجع *tp;
  أرجع NULL_درخت;
}

/* Similarly, but also walk aggregate fields.  */

بنية c_پیدا_کن_omp_var_s { درخت var; hash_مجموعه<درخت> *pset; };

ساكن درخت
c_پیدا_کن_omp_var_r (درخت *tp, صحيح *, فراغ *داده)
{
  إذا (*tp == ((بنية c_پیدا_کن_omp_var_s *) داده)->var)
    أرجع *tp;
  إذا (رکورد_OR_UNION_TYPE_P (*tp))
    {
      درخت فیلد_2;
      hash_مجموعه<درخت> *pset = ((بنية c_پیدا_کن_omp_var_s *) داده)->pset;

      لكل (فیلد_2 = TYPE_FIELDS (*tp); فیلد_2;
	   فیلد_2 = DECL_CHAIN (فیلد_2))
	إذا (درخت_کد (فیلد_2) == فیلد_DECL)
	  {
	    درخت ret = walk_درخت (&DECL_فیلد_جابه_جایی (فیلد_2),
				  c_پیدا_کن_omp_var_r, داده, pset);
	    إذا (ret)
	      أرجع ret;
	    ret = walk_درخت (&DECL_اندازه (فیلد_2), c_پیدا_کن_omp_var_r, داده, pset);
	    إذا (ret)
	      أرجع ret;
	    ret = walk_درخت (&DECL_اندازه_UNIT (فیلد_2), c_پیدا_کن_omp_var_r, داده,
			     pset);
	    إذا (ret)
	      أرجع ret;
	    ret = walk_درخت (&درخت_TYPE (فیلد_2), c_پیدا_کن_omp_var_r, داده, pset);
	    إذا (ret)
	      أرجع ret;
	  }
    }
  وإلا إذا (INTEGRAL_TYPE_P (*tp))
    أرجع walk_درخت (&TYPE_MAX_مقدار (*tp), c_پیدا_کن_omp_var_r, داده,
		      ((بنية c_پیدا_کن_omp_var_s *) داده)->pset);
  أرجع NULL_درخت;
}

/* Finish OpenMP iterators ITER.  Return true if they are erroneous
   and clauses containing them should be removed.  */

ساكن منطقي
c_omp_پایان_iterators (درخت iter)
{
  منطقي ret = خطأ;
  لكل (درخت it = iter; it; it = درخت_CHAIN (it))
    {
      درخت var = OMP_ITERATOR_VAR (it);
      درخت begin = OMP_ITERATOR_BEGIN (it);
      درخت انتها = OMP_ITERATOR_انتها (it);
      درخت گام = OMP_ITERATOR_گام (it);
      درخت orig_گام;
      درخت type = درخت_TYPE (var);
      location_t loc = DECL_منبع_LOCATION (var);
      إذا (type == error_mark_گره)
	{
	  ret = درست;
	  استمر;
	}
      إذا (!INTEGRAL_TYPE_P (type) && !اشاره_گر_TYPE_P (type))
	{
	  error_at (loc, "iterator %qD has neither integral nor pointer type",
		    var);
	  ret = درست;
	  استمر;
	}
      وإلا إذا (TYPE_ATOMIC (type))
	{
	  error_at (loc, "iterator %qD has %<_Atomic%> qualified type", var);
	  ret = درست;
	  استمر;
	}
      وإلا إذا (TYPE_READONLY (type))
	{
	  error_at (loc, "iterator %qD has const qualified type", var);
	  ret = درست;
	  استمر;
	}
      وإلا إذا (گام == error_mark_گره
	       || درخت_TYPE (گام) == error_mark_گره)
	{
	  ret = درست;
	  استمر;
	}
      وإلا إذا (!INTEGRAL_TYPE_P (درخت_TYPE (گام)))
	{
	  error_at (عبارت_LOC_OR_LOC (گام, loc),
		    "iterator step with non-integral type");
	  ret = درست;
	  استمر;
	}
      begin = c_fully_fold (build_c_cast (loc, type, begin), خطأ, عدم);
      انتها = c_fully_fold (build_c_cast (loc, type, انتها), خطأ, عدم);
      orig_گام = save_عبارت (c_fully_fold (گام, خطأ, عدم));
      درخت stype = اشاره_گر_TYPE_P (type) ? sizetype : type;
      گام = c_fully_fold (build_c_cast (loc, stype, orig_گام), خطأ, عدم);
      إذا (اشاره_گر_TYPE_P (type))
	{
	  begin = save_عبارت (begin);
	  گام = اشاره_گر_int_جمع (loc, PLUS_عبارت, begin, گام);
	  گام = fold_build2_loc (loc, MINUS_عبارت, sizetype,
				  fold_convert (sizetype, گام),
				  fold_convert (sizetype, begin));
	  گام = fold_convert (ssizetype, گام);
	}
      إذا (integer_zerop (گام))
	{
	  error_at (loc, "iterator %qD has zero step", var);
	  ret = درست;
	  استمر;
	}

      إذا (begin == error_mark_گره
	  || انتها == error_mark_گره
	  || گام == error_mark_گره
	  || orig_گام == error_mark_گره)
	{
	  ret = درست;
	  استمر;
	}
      hash_مجموعه<درخت> pset;
      درخت it2;
      لكل (it2 = درخت_CHAIN (it); it2; it2 = درخت_CHAIN (it2))
	{
	  درخت var2 = OMP_ITERATOR_VAR (it2);
	  درخت begin2 = OMP_ITERATOR_BEGIN (it2);
	  درخت end2 = OMP_ITERATOR_انتها (it2);
	  درخت step2 = OMP_ITERATOR_گام (it2);
	  درخت type2 = درخت_TYPE (var2);
	  location_t loc2 = DECL_منبع_LOCATION (var2);
	  بنية c_پیدا_کن_omp_var_s داده = { var, &pset };
	  إذا (walk_درخت (&type2, c_پیدا_کن_omp_var_r, &داده, &pset))
	    {
	      error_at (loc2,
			"type of iterator %qD refers to outer iterator %qD",
			var2, var);
	      اكسر;
	    }
	  وإلا إذا (walk_درخت (&begin2, c_پیدا_کن_omp_var_r, &داده, &pset))
	    {
	      error_at (عبارت_LOC_OR_LOC (begin2, loc2),
			"begin expression refers to outer iterator %qD", var);
	      اكسر;
	    }
	  وإلا إذا (walk_درخت (&end2, c_پیدا_کن_omp_var_r, &داده, &pset))
	    {
	      error_at (عبارت_LOC_OR_LOC (end2, loc2),
			"end expression refers to outer iterator %qD", var);
	      اكسر;
	    }
	  وإلا إذا (walk_درخت (&step2, c_پیدا_کن_omp_var_r, &داده, &pset))
	    {
	      error_at (عبارت_LOC_OR_LOC (step2, loc2),
			"step expression refers to outer iterator %qD", var);
	      اكسر;
	    }
	}
      إذا (it2)
	{
	  ret = درست;
	  استمر;
	}
      OMP_ITERATOR_BEGIN (it) = begin;
      OMP_ITERATOR_انتها (it) = انتها;
      OMP_ITERATOR_گام (it) = گام;
      OMP_ITERATOR_ORIG_گام (it) = orig_گام;
    }
  أرجع ret;
}

/* Ensure that pointers are used in OpenACC attach and detach clauses.
   Return true if an error has been detected.  */

ساكن منطقي
c_oacc_check_attachments (درخت c)
{
  إذا (OMP_CLAUSE_کد (c) != OMP_CLAUSE_MAP)
    أرجع خطأ;

  /* OpenACC attach / detach clauses must be pointers.  */
  إذا (OMP_CLAUSE_MAP_نوع (c) == GOMP_MAP_ATTACH
      || OMP_CLAUSE_MAP_نوع (c) == GOMP_MAP_DETACH)
    {
      درخت t = OMP_CLAUSE_DECL (c);

      طالما (درخت_کد (t) == OMP_ARRAY_SECTION)
	t = درخت_عملوند (t, 0);

      إذا (درخت_کد (درخت_TYPE (t)) != اشاره_گر_TYPE)
	{
	  error_at (OMP_CLAUSE_LOCATION (c), "expected pointer in %qs clause",
		    user_omp_clause_کد_name (c, درست));
	  أرجع درست;
	}
    }

  أرجع خطأ;
}

/* For all elements of CLAUSES, validate them against their constraints.
   Remove any elements from the list that are invalid.  */

درخت
c_پایان_omp_clauses (درخت clauses, تعداد c_omp_region_type ort)
{
  bitmap_سر generic_سر, firstprivate_سر, lastprivate_سر;
  bitmap_سر aligned_سر, map_سر, map_فیلد_سر, map_firstprivate_سر;
  bitmap_سر oacc_reduction_سر, is_on_device_سر;
  درخت c, t, type, *pc;
  درخت simdlen = NULL_درخت, safelen = NULL_درخت;
  منطقي branch_دیده = خطأ;
  منطقي copyprivate_دیده = خطأ;
  منطقي mergeable_دیده = خطأ;
  درخت *detach_دیده = عدم;
  منطقي خطی_variable_گام_check = خطأ;
  درخت *nowait_clause = عدم;
  درخت *grainsize_دیده = عدم;
  منطقي رقم_tasks_دیده = خطأ;
  درخت ordered_clause = NULL_درخت;
  درخت زمانبندی_clause = NULL_درخت;
  منطقي oacc_async = خطأ;
  درخت آخرین_iterators = NULL_درخت;
  منطقي آخرین_iterators_remove = خطأ;
  درخت *nogroup_دیده = عدم;
  درخت *ترتیب_clause = عدم;
  /* 1 if normal/task reduction has been seen, -1 if inscan reduction
     has been seen, -2 if mixed inscan/normal reduction diagnosed.  */
  صحيح reduction_دیده = 0;
  منطقي allocate_دیده = خطأ;
  منطقي implicit_moved = خطأ;
  منطقي هدف_درون_reduction_دیده = خطأ;
  درخت *پر_دیده = عدم;
  منطقي partial_دیده = خطأ;
  منطقي openacc = (ort & C_ORT_ACC) != 0;
  منطقي init_دیده = خطأ;
  منطقي init_use_destroy_دیده = خطأ;
  درخت init_no_targetsync_clause = NULL_درخت;
  درخت depend_clause = NULL_درخت;

  إذا (!openacc)
    clauses = omp_remove_duplicate_maps (clauses, درست);

  bitmap_obstack_initialize (عدم);
  bitmap_initialize (&generic_سر, &bitmap_default_obstack);
  bitmap_initialize (&firstprivate_سر, &bitmap_default_obstack);
  bitmap_initialize (&lastprivate_سر, &bitmap_default_obstack);
  bitmap_initialize (&aligned_سر, &bitmap_default_obstack);
  /* If ort == C_ORT_OMP_DECLARE_SIMD used as uniform_head instead.  */
  bitmap_initialize (&map_سر, &bitmap_default_obstack);
  bitmap_initialize (&map_فیلد_سر, &bitmap_default_obstack);
  bitmap_initialize (&map_firstprivate_سر, &bitmap_default_obstack);
  /* If ort == C_ORT_OMP used as nontemporal_head or use_device_xxx_head
     instead and for ort == C_ORT_OMP_TARGET used as in_reduction_head.  */
  bitmap_initialize (&oacc_reduction_سر, &bitmap_default_obstack);
  bitmap_initialize (&is_on_device_سر, &bitmap_default_obstack);

  إذا (openacc)
    لكل (c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
      إذا (OMP_CLAUSE_کد (c) == OMP_CLAUSE_ASYNC)
	{
	  oacc_async = درست;
	  اكسر;
	}

  درخت *grp_شروع_p = عدم, grp_sentinel = NULL_درخت;

  لكل (pc = &clauses, c = clauses; c ; c = *pc)
    {
      منطقي remove = خطأ;
      منطقي need_complete = خطأ;
      منطقي need_implicitly_determined = خطأ;

      /* We've reached the end of a list of expanded nodes.  Reset the group
	 start pointer.  */
      إذا (c == grp_sentinel)
	{
	  إذا (grp_شروع_p
	      && OMP_CLAUSE_HAS_ITERATORS (*grp_شروع_p))
	    لكل (درخت gc = *grp_شروع_p; gc != grp_sentinel;
		 gc = OMP_CLAUSE_CHAIN (gc))
	      OMP_CLAUSE_ITERATORS (gc) = OMP_CLAUSE_ITERATORS (*grp_شروع_p);
	  grp_شروع_p = عدم;
	}

      بدل (OMP_CLAUSE_کد (c))
	{
	حالة OMP_CLAUSE_SHARED:
	  need_implicitly_determined = درست;
	  اذهب check_dup_generic;

	حالة OMP_CLAUSE_خصوصی:
	  need_complete = درست;
	  need_implicitly_determined = درست;
	  اذهب check_dup_generic;

	حالة OMP_CLAUSE_REDUCTION:
	  إذا (reduction_دیده == 0)
	    reduction_دیده = OMP_CLAUSE_REDUCTION_INSCAN (c) ? -1 : 1;
	  وإلا إذا (reduction_دیده != -2
		   && reduction_دیده != (OMP_CLAUSE_REDUCTION_INSCAN (c)
					 ? -1 : 1))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<inscan%> and non-%<inscan%> %<reduction%> clauses "
			"on the same construct");
	      reduction_دیده = -2;
	    }
	  /* FALLTHRU */
	حالة OMP_CLAUSE_درون_REDUCTION:
	حالة OMP_CLAUSE_TASK_REDUCTION:
	  need_implicitly_determined = درست;
	  t = OMP_CLAUSE_DECL (c);
	  إذا (درخت_کد (t) == OMP_ARRAY_SECTION)
	    {
	      إذا (handle_omp_array_sections (c, ort))
		{
		  remove = درست;
		  اكسر;
		}

	      t = OMP_CLAUSE_DECL (c);
	      إذا (OMP_CLAUSE_کد (c) == OMP_CLAUSE_REDUCTION
		  && OMP_CLAUSE_REDUCTION_INSCAN (c))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<inscan%> %<reduction%> clause with array "
			    "section");
		  remove = درست;
		  اكسر;
		}
	    }
	  t = require_complete_type (OMP_CLAUSE_LOCATION (c), t);
	  إذا (t == error_mark_گره)
	    {
	      remove = درست;
	      اكسر;
	    }
	  إذا (oacc_async)
	    c_mark_addressable (t);
	  type = درخت_TYPE (t);
	  إذا (درخت_کد (t) == MEM_REF)
	    type = درخت_TYPE (type);
	  إذا (درخت_کد (type) == ARRAY_TYPE)
	    {
	      درخت oatype = type;
	      gcc_assert (درخت_کد (t) != MEM_REF);
	      طالما (درخت_کد (type) == ARRAY_TYPE)
		type = درخت_TYPE (type);
	      إذا (integer_zerop (TYPE_اندازه_UNIT (type)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD in %<reduction%> clause is a zero size array",
			    t);
		  remove = درست;
		  اكسر;
		}
	      درخت اندازه = اندازه_binop (EXACT_DIV_عبارت, TYPE_اندازه_UNIT (oatype),
				      TYPE_اندازه_UNIT (type));
	      إذا (integer_zerop (اندازه))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD in %<reduction%> clause is a zero size array",
			    t);
		  remove = درست;
		  اكسر;
		}
	      اندازه = اندازه_binop (MINUS_عبارت, اندازه, اندازه_one_گره);
	      اندازه = save_عبارت (اندازه);
	      درخت شاخص_type = build_شاخص_type (اندازه);
	      درخت atype = c_build_array_type (TYPE_MAIN_VARIANT (type),
					       شاخص_type);
	      atype = c_build_qualified_type (atype, TYPE_QUALS (type));
	      درخت ptype = c_build_اشاره_گر_type (type);
	      إذا (درخت_کد (درخت_TYPE (t)) == ARRAY_TYPE)
		t = build_fold_addr_عبارت (t);
	      t = build2 (MEM_REF, atype, t, build_int_cst (ptype, 0));
	      OMP_CLAUSE_DECL (c) = t;
	    }
	  إذا (TYPE_ATOMIC (type))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<_Atomic%> %qE in %<reduction%> clause", t);
	      remove = درست;
	      اكسر;
	    }
	  إذا (OMP_CLAUSE_کد (c) != OMP_CLAUSE_REDUCTION
	      || OMP_CLAUSE_REDUCTION_TASK (c))
	    {
	      /* Disallow zero sized or potentially zero sized task
		 reductions.  */
	      إذا (integer_zerop (TYPE_اندازه_UNIT (type)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "zero sized type %qT in %qs clause", type,
			    omp_clause_کد_name[OMP_CLAUSE_کد (c)]);
		  remove = درست;
		  اكسر;
		}
	      وإلا إذا (درخت_کد (TYPE_اندازه_UNIT (type)) != INTEGER_CST)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "variable sized type %qT in %qs clause", type,
			    omp_clause_کد_name[OMP_CLAUSE_کد (c)]);
		  remove = درست;
		  اكسر;
		}
	    }
	  إذا (OMP_CLAUSE_REDUCTION_PLACEHOLDER (c) == NULL_درخت
	      && (FLOAT_TYPE_P (type)
		  || درخت_کد (type) == COMPLEX_TYPE))
	    {
	      تعداد درخت_کد_2 r_کد = OMP_CLAUSE_REDUCTION_کد (c);
	      ثابت حرف *r_name = عدم;

	      بدل (r_کد)
		{
		حالة PLUS_عبارت:
		حالة MULT_عبارت:
		حالة MINUS_عبارت:
		حالة TRUTH_ANDIF_عبارت:
		حالة TRUTH_ORIF_عبارت:
		  اكسر;
		حالة MIN_عبارت:
		  إذا (درخت_کد (type) == COMPLEX_TYPE)
		    r_name = "min";
		  اكسر;
		حالة MAX_عبارت:
		  إذا (درخت_کد (type) == COMPLEX_TYPE)
		    r_name = "max";
		  اكسر;
		حالة بیت_AND_عبارت:
		  r_name = "&";
		  اكسر;
		حالة بیت_XOR_عبارت:
		  r_name = "^";
		  اكسر;
		حالة بیت_IOR_عبارت:
		  r_name = "|";
		  اكسر;
		افتراضي:
		  gcc_unreachable ();
		}
	      إذا (r_name)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qE has invalid type for %<reduction(%s)%>",
			    t, r_name);
		  remove = درست;
		  اكسر;
		}
	    }
	  وإلا إذا (OMP_CLAUSE_REDUCTION_PLACEHOLDER (c) == error_mark_گره)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"user defined reduction not found for %qE", t);
	      remove = درست;
	      اكسر;
	    }
	  وإلا إذا (OMP_CLAUSE_REDUCTION_PLACEHOLDER (c))
	    {
	      درخت list = OMP_CLAUSE_REDUCTION_PLACEHOLDER (c);
	      type = TYPE_MAIN_VARIANT (type);
	      درخت placeholder = build_decl (OMP_CLAUSE_LOCATION (c),
					     VAR_DECL, NULL_درخت, type);
	      درخت decl_placeholder = NULL_درخت;
	      OMP_CLAUSE_REDUCTION_PLACEHOLDER (c) = placeholder;
	      DECL_ARTIFICIAL (placeholder) = 1;
	      DECL_IGNORED_P (placeholder) = 1;
	      إذا (درخت_کد (t) == MEM_REF)
		{
		  decl_placeholder = build_decl (OMP_CLAUSE_LOCATION (c),
						 VAR_DECL, NULL_درخت, type);
		  OMP_CLAUSE_REDUCTION_DECL_PLACEHOLDER (c) = decl_placeholder;
		  DECL_ARTIFICIAL (decl_placeholder) = 1;
		  DECL_IGNORED_P (decl_placeholder) = 1;
		}
	      إذا (درخت_ADDRESSABLE (درخت_VEC_ELT (list, 0)))
		c_mark_addressable (placeholder);
	      إذا (درخت_ADDRESSABLE (درخت_VEC_ELT (list, 1)))
		c_mark_addressable (decl_placeholder ? decl_placeholder
				    : OMP_CLAUSE_DECL (c));
	      OMP_CLAUSE_REDUCTION_ادغام (c)
		= c_clone_omp_udr (درخت_VEC_ELT (list, 2),
				   درخت_VEC_ELT (list, 0),
				   درخت_VEC_ELT (list, 1),
				   decl_placeholder ? decl_placeholder
				   : OMP_CLAUSE_DECL (c), placeholder);
	      OMP_CLAUSE_REDUCTION_ادغام (c)
		= build3_loc (OMP_CLAUSE_LOCATION (c), BIND_عبارت,
			      void_type_گره, NULL_درخت,
			      OMP_CLAUSE_REDUCTION_ادغام (c), NULL_درخت);
	      درخت_SIDE_EFFECTS (OMP_CLAUSE_REDUCTION_ادغام (c)) = 1;
	      إذا (درخت_VEC_درازی (list) == 6)
		{
		  إذا (درخت_ADDRESSABLE (درخت_VEC_ELT (list, 3)))
		    c_mark_addressable (decl_placeholder ? decl_placeholder
					: OMP_CLAUSE_DECL (c));
		  إذا (درخت_ADDRESSABLE (درخت_VEC_ELT (list, 4)))
		    c_mark_addressable (placeholder);
		  درخت init = درخت_VEC_ELT (list, 5);
		  إذا (init == error_mark_گره)
		    init = DECL_INITIAL (درخت_VEC_ELT (list, 3));
		  OMP_CLAUSE_REDUCTION_INIT (c)
		    = c_clone_omp_udr (init, درخت_VEC_ELT (list, 4),
				       درخت_VEC_ELT (list, 3),
				       decl_placeholder ? decl_placeholder
				       : OMP_CLAUSE_DECL (c), placeholder);
		  إذا (درخت_VEC_ELT (list, 5) == error_mark_گره)
		    {
		      درخت v = decl_placeholder ? decl_placeholder : t;
		      OMP_CLAUSE_REDUCTION_INIT (c)
			= build2 (INIT_عبارت, درخت_TYPE (v), v,
				  OMP_CLAUSE_REDUCTION_INIT (c));
		    }
		  إذا (walk_درخت (&OMP_CLAUSE_REDUCTION_INIT (c),
				 c_پیدا_کن_omp_placeholder_r,
				 placeholder, عدم))
		    OMP_CLAUSE_REDUCTION_OMP_ORIG_REF (c) = 1;
		}
	      وإلا
		{
		  درخت init;
		  درخت v = decl_placeholder ? decl_placeholder : t;
		  إذا (AGGREGATE_TYPE_P (درخت_TYPE (v)))
		    init = build_constructor (درخت_TYPE (v), عدم);
		  وإلا
		    init = fold_convert (درخت_TYPE (v), integer_zero_گره);
		  OMP_CLAUSE_REDUCTION_INIT (c)
		    = build2 (INIT_عبارت, درخت_TYPE (v), v, init);
		}
	      OMP_CLAUSE_REDUCTION_INIT (c)
		= build3_loc (OMP_CLAUSE_LOCATION (c), BIND_عبارت,
			      void_type_گره, NULL_درخت,
			       OMP_CLAUSE_REDUCTION_INIT (c), NULL_درخت);
	      درخت_SIDE_EFFECTS (OMP_CLAUSE_REDUCTION_INIT (c)) = 1;
	    }
	  إذا (درخت_کد (t) == MEM_REF)
	    {
	      إذا (TYPE_اندازه_UNIT (درخت_TYPE (درخت_TYPE (t))) == NULL_درخت
		  || درخت_کد (TYPE_اندازه_UNIT (درخت_TYPE (درخت_TYPE (t))))
		     != INTEGER_CST)
		{
		  sorry ("variable length element type in array "
			 "%<reduction%> clause");
		  remove = درست;
		  اكسر;
		}
	      t = درخت_عملوند (t, 0);
	      إذا (درخت_کد (t) == اشاره_گر_PLUS_عبارت)
		t = درخت_عملوند (t, 0);
	      إذا (درخت_کد (t) == ADDR_عبارت)
		t = درخت_عملوند (t, 0);
	    }
	  اذهب check_dup_generic_t;

	حالة OMP_CLAUSE_COPYPRIVATE:
	  copyprivate_دیده = درست;
	  إذا (nowait_clause)
	    {
	      error_at (OMP_CLAUSE_LOCATION (*nowait_clause),
			"%<nowait%> clause must not be used together "
			"with %<copyprivate%> clause");
	      *nowait_clause = OMP_CLAUSE_CHAIN (*nowait_clause);
	      nowait_clause = عدم;
	    }
	  اذهب check_dup_generic;

	حالة OMP_CLAUSE_COPYIN:
	  t = OMP_CLAUSE_DECL (c);
	  إذا (!VAR_P (t) || !DECL_THREAD_LOCAL_P (t))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE must be %<threadprivate%> for %<copyin%>", t);
	      remove = درست;
	      اكسر;
	    }
	  اذهب check_dup_generic;

	حالة OMP_CLAUSE_خطی:
	  إذا (ort != C_ORT_OMP_DECLARE_SIMD)
	    need_implicitly_determined = درست;
	  t = OMP_CLAUSE_DECL (c);
	  إذا (ort != C_ORT_OMP_DECLARE_SIMD
	      && OMP_CLAUSE_خطی_نوع (c) != OMP_CLAUSE_خطی_DEFAULT
	      && OMP_CLAUSE_خطی_OLD_خطی_MODIFIER (c))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"modifier should not be specified in %<linear%> "
			"clause on %<simd%> or %<for%> constructs when not "
			"using OpenMP 5.2 modifiers");
	      OMP_CLAUSE_خطی_نوع (c) = OMP_CLAUSE_خطی_DEFAULT;
	    }
	  إذا (!INTEGRAL_TYPE_P (درخت_TYPE (t))
	      && درخت_کد (درخت_TYPE (t)) != اشاره_گر_TYPE)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"linear clause applied to non-integral non-pointer "
			"variable with type %qT", درخت_TYPE (t));
	      remove = درست;
	      اكسر;
	    }
	  إذا (TYPE_ATOMIC (درخت_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<_Atomic%> %qD in %<linear%> clause", t);
	      remove = درست;
	      اكسر;
	    }
	  إذا (ort == C_ORT_OMP_DECLARE_SIMD)
	    {
	      درخت s = OMP_CLAUSE_خطی_گام (c);
	      إذا (درخت_کد (s) == PARM_DECL)
		{
		  OMP_CLAUSE_خطی_VARIABLE_STRIDE (c) = 1;
		  /* map_head bitmap is used as uniform_head if
		     declare_simd.  */
		  إذا (!bitmap_بیت_p (&map_سر, DECL_UID (s)))
		    خطی_variable_گام_check = درست;
		  اذهب check_dup_generic;
		}
	      إذا (درخت_کد (s) != INTEGER_CST)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<linear%> clause step %qE is neither constant "
			    "nor a parameter", s);
		  remove = درست;
		  اكسر;
		}
	    }
	  إذا (درخت_کد (درخت_TYPE (OMP_CLAUSE_DECL (c))) == اشاره_گر_TYPE)
	    {
	      درخت s = OMP_CLAUSE_خطی_گام (c);
	      s = اشاره_گر_int_جمع (OMP_CLAUSE_LOCATION (c), PLUS_عبارت,
				   OMP_CLAUSE_DECL (c), s);
	      s = fold_build2_loc (OMP_CLAUSE_LOCATION (c), MINUS_عبارت,
				   sizetype, fold_convert (sizetype, s),
				   fold_convert
				     (sizetype, OMP_CLAUSE_DECL (c)));
	      إذا (s == error_mark_گره)
		s = اندازه_one_گره;
	      OMP_CLAUSE_خطی_گام (c) = s;
	    }
	  وإلا
	    OMP_CLAUSE_خطی_گام (c)
	      = fold_convert (درخت_TYPE (t), OMP_CLAUSE_خطی_گام (c));
	  اذهب check_dup_generic;

	check_dup_generic:
	  t = OMP_CLAUSE_DECL (c);
	check_dup_generic_t:
	  إذا (!VAR_P (t) && درخت_کد (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %qs", t,
			omp_clause_کد_name[OMP_CLAUSE_کد (c)]);
	      remove = درست;
	    }
	  وإلا إذا ((openacc && OMP_CLAUSE_کد (c) == OMP_CLAUSE_REDUCTION)
		   || (ort == C_ORT_OMP
		       && (OMP_CLAUSE_کد (c) == OMP_CLAUSE_USE_DEVICE_PTR
			   || (OMP_CLAUSE_کد (c)
			       == OMP_CLAUSE_USE_DEVICE_ADDR)))
		   || (ort == C_ORT_OMP_هدف
		       && OMP_CLAUSE_کد (c) == OMP_CLAUSE_درون_REDUCTION))
	    {
	      إذا (OMP_CLAUSE_کد (c) == OMP_CLAUSE_درون_REDUCTION
		  && (bitmap_بیت_p (&generic_سر, DECL_UID (t))
		      || bitmap_بیت_p (&firstprivate_سر, DECL_UID (t))))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in data-sharing "
			    "clauses", t);
		  remove = درست;
		  اكسر;
		}
	      إذا (OMP_CLAUSE_کد (c) == OMP_CLAUSE_درون_REDUCTION)
		هدف_درون_reduction_دیده = درست;
	      إذا (bitmap_بیت_p (&oacc_reduction_سر, DECL_UID (t)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    openacc
			    ? "%qD appears more than once in reduction clauses"
			    : "%qD appears more than once in data clauses",
			    t);
		  remove = درست;
		}
	      وإلا
		bitmap_مجموعه_بیت (&oacc_reduction_سر, DECL_UID (t));
	    }
	  وإلا إذا (bitmap_بیت_p (&generic_سر, DECL_UID (t))
		   || bitmap_بیت_p (&firstprivate_سر, DECL_UID (t))
		   || bitmap_بیت_p (&lastprivate_سر, DECL_UID (t))
		   || bitmap_بیت_p (&map_firstprivate_سر, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in data clauses", t);
	      remove = درست;
	    }
	  وإلا إذا ((OMP_CLAUSE_کد (c) == OMP_CLAUSE_خصوصی
		    || OMP_CLAUSE_کد (c) == OMP_CLAUSE_HAS_DEVICE_ADDR
		    || OMP_CLAUSE_کد (c) == OMP_CLAUSE_IS_DEVICE_PTR)
		   && bitmap_بیت_p (&map_سر, DECL_UID (t)))
	    {
	      إذا (openacc)
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears more than once in data clauses", t);
	      وإلا
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears both in data and map clauses", t);
	      remove = درست;
	    }
	  وإلا
	    bitmap_مجموعه_بیت (&generic_سر, DECL_UID (t));
	  اكسر;

	حالة OMP_CLAUSE_FIRSTPRIVATE:
	  إذا (OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (c) && !implicit_moved)
	    {
	    move_implicit:
	      implicit_moved = درست;
	      /* Move firstprivate and map clauses with
		 OMP_CLAUSE_{FIRSTPRIVATE,MAP}_IMPLICIT set to the end of
		 clauses chain.  */
	      درخت cl1 = NULL_درخت, cl2 = NULL_درخت;
	      درخت *pc1 = pc, *pc2 = &cl1, *pc3 = &cl2;
	      طالما (*pc1)
		إذا (OMP_CLAUSE_کد (*pc1) == OMP_CLAUSE_FIRSTPRIVATE
		    && OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (*pc1))
		  {
		    *pc3 = *pc1;
		    pc3 = &OMP_CLAUSE_CHAIN (*pc3);
		    *pc1 = OMP_CLAUSE_CHAIN (*pc1);
		  }
		وإلا إذا (OMP_CLAUSE_کد (*pc1) == OMP_CLAUSE_MAP
			 && OMP_CLAUSE_MAP_IMPLICIT (*pc1))
		  {
		    *pc2 = *pc1;
		    pc2 = &OMP_CLAUSE_CHAIN (*pc2);
		    *pc1 = OMP_CLAUSE_CHAIN (*pc1);
		  }
		وإلا
		  pc1 = &OMP_CLAUSE_CHAIN (*pc1);
	      *pc3 = عدم;
	      *pc2 = cl2;
	      *pc1 = cl1;
	      استمر;
	    }
	  t = OMP_CLAUSE_DECL (c);
	  need_complete = درست;
	  need_implicitly_determined = درست;
	  إذا (!VAR_P (t) && درخت_کد (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %<firstprivate%>", t);
	      remove = درست;
	    }
	  وإلا إذا (OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (c)
		   && !OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT_هدف (c)
		   && bitmap_بیت_p (&map_firstprivate_سر, DECL_UID (t)))
	    remove = درست;
	  وإلا إذا (bitmap_بیت_p (&generic_سر, DECL_UID (t))
		   || bitmap_بیت_p (&firstprivate_سر, DECL_UID (t))
		   || bitmap_بیت_p (&map_firstprivate_سر, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in data clauses", t);
	      remove = درست;
	    }
	  وإلا إذا (bitmap_بیت_p (&map_سر, DECL_UID (t))
		   || bitmap_بیت_p (&map_فیلد_سر, DECL_UID (t)))
	    {
	      إذا (openacc)
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears more than once in data clauses", t);
	      وإلا إذا (OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (c)
		       && !OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT_هدف (c))
		/* Silently drop the clause.  */;
	      وإلا
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears both in data and map clauses", t);
	      remove = درست;
	    }
	  وإلا
	    bitmap_مجموعه_بیت (&firstprivate_سر, DECL_UID (t));
	  اكسر;

	حالة OMP_CLAUSE_LASTPRIVATE:
	  t = OMP_CLAUSE_DECL (c);
	  need_complete = درست;
	  need_implicitly_determined = درست;
	  إذا (!VAR_P (t) && درخت_کد (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %<lastprivate%>", t);
	      remove = درست;
	    }
	  وإلا إذا (bitmap_بیت_p (&generic_سر, DECL_UID (t))
		   || bitmap_بیت_p (&lastprivate_سر, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
		     "%qE appears more than once in data clauses", t);
	      remove = درست;
	    }
	  وإلا
	    bitmap_مجموعه_بیت (&lastprivate_سر, DECL_UID (t));
	  اكسر;

	حالة OMP_CLAUSE_ALIGNED:
	  t = OMP_CLAUSE_DECL (c);
	  إذا (!VAR_P (t) && درخت_کد (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in %<aligned%> clause", t);
	      remove = درست;
	    }
	  وإلا إذا (!اشاره_گر_TYPE_P (درخت_TYPE (t))
		   && درخت_کد (درخت_TYPE (t)) != ARRAY_TYPE)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE in %<aligned%> clause is neither a pointer nor "
			"an array", t);
	      remove = درست;
	    }
	  وإلا إذا (TYPE_ATOMIC (درخت_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<_Atomic%> %qD in %<aligned%> clause", t);
	      remove = درست;
	      اكسر;
	    }
	  وإلا إذا (bitmap_بیت_p (&aligned_سر, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in %<aligned%> clauses",
			t);
	      remove = درست;
	    }
	  وإلا
	    bitmap_مجموعه_بیت (&aligned_سر, DECL_UID (t));
	  اكسر;

	حالة OMP_CLAUSE_NONTEMPORAL:
	  t = OMP_CLAUSE_DECL (c);
	  إذا (!VAR_P (t) && درخت_کد (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in %<nontemporal%> clause", t);
	      remove = درست;
	    }
	  وإلا إذا (bitmap_بیت_p (&oacc_reduction_سر, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in %<nontemporal%> "
			"clauses", t);
	      remove = درست;
	    }
	  وإلا
	    bitmap_مجموعه_بیت (&oacc_reduction_سر, DECL_UID (t));
	  اكسر;

	حالة OMP_CLAUSE_ALLOCATE:
	  t = OMP_CLAUSE_DECL (c);
	  إذا (!VAR_P (t) && درخت_کد (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in %<allocate%> clause", t);
	      remove = درست;
	    }
	  وإلا إذا (bitmap_بیت_p (&aligned_سر, DECL_UID (t)))
	    {
	      warning_at (OMP_CLAUSE_LOCATION (c), OPT_Wopenmp,
			  "%qE appears more than once in %<allocate%> clauses",
			  t);
	      remove = درست;
	    }
	  وإلا
	    {
	      bitmap_مجموعه_بیت (&aligned_سر, DECL_UID (t));
	      إذا (!OMP_CLAUSE_ALLOCATE_COMBINED (c))
		allocate_دیده = درست;
	    }
	  اكسر;

	حالة OMP_CLAUSE_DOACROSS:
	  t = OMP_CLAUSE_DECL (c);
	  إذا (t == NULL_درخت)
	    اكسر;
	  إذا (OMP_CLAUSE_DOACROSS_نوع (c) == OMP_CLAUSE_DOACROSS_SINK)
	    {
	      gcc_assert (درخت_کد (t) == درخت_LIST);
	      لكل (; t; t = درخت_CHAIN (t))
		{
		  درخت decl = درخت_مقدار (t);
		  إذا (درخت_کد (درخت_TYPE (decl)) == اشاره_گر_TYPE)
		    {
		      درخت جابه_جایی = درخت_PURPOSE (t);
		      منطقي neg = wi::neg_p (wi::مقصد_wide (جابه_جایی));
		      جابه_جایی = fold_unary (ABS_عبارت, درخت_TYPE (جابه_جایی), جابه_جایی);
		      درخت t2 = اشاره_گر_int_جمع (OMP_CLAUSE_LOCATION (c),
						 neg ? MINUS_عبارت : PLUS_عبارت,
						 decl, جابه_جایی);
		      t2 = fold_build2_loc (OMP_CLAUSE_LOCATION (c), MINUS_عبارت,
					    sizetype,
					    fold_convert (sizetype, t2),
					    fold_convert (sizetype, decl));
		      إذا (t2 == error_mark_گره)
			{
			  remove = درست;
			  اكسر;
			}
		      درخت_PURPOSE (t) = t2;
		    }
		}
	      اكسر;
	    }
	  gcc_unreachable ();

	حالة OMP_CLAUSE_استفاده_میکند_ALLOCATORS:
	  t = OMP_CLAUSE_استفاده_میکند_ALLOCATORS_ALLOCATOR (c);
	  إذا (t == error_mark_گره)
	    {
	      remove = درست;
	      اكسر;
	    }
	  إذا ((VAR_P (t) || درخت_کد (t) == PARM_DECL)
	      && (bitmap_بیت_p (&generic_سر, DECL_UID (t))
		  || bitmap_بیت_p (&map_سر, DECL_UID (t))
		  || bitmap_بیت_p (&firstprivate_سر, DECL_UID (t))
		  || bitmap_بیت_p (&lastprivate_سر, DECL_UID (t))))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in data clauses", t);
	      remove = درست;
	      اكسر;
	    }
	  وإلا
	    bitmap_مجموعه_بیت (&generic_سر, DECL_UID (t));
	  إذا (درخت_کد (درخت_TYPE (t)) != ENUMERAL_TYPE
	      || strcmp (IDENTIFIER_اشاره_گر (TYPE_IDENTIFIER (درخت_TYPE (t))),
			 "omp_allocator_handle_t") != 0)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"allocator %qE must be of %<omp_allocator_handle_t%> "
			"type", t);
	      remove = درست;
	      اكسر;
	    }
	  درخت init;
	  إذا (!DECL_P (t)
	      || (درخت_کد (t) == CONST_DECL
		  && ((init = DECL_INITIAL(t)) == اشاره_تهی
		      || درخت_کد (init) != INTEGER_CST
		      || ((wi::مقصد_widest (init) < 0
			   || wi::مقصد_widest (init) > GOMP_OMP_PREDEF_ALLOC_MAX)
			  && (wi::مقصد_widest (init) < GOMP_OMPX_PREDEF_ALLOC_MIN
			      || (wi::مقصد_widest (init)
				  > GOMP_OMPX_PREDEF_ALLOC_MAX))))))
	    {
	      remove = درست;
	      error_at (OMP_CLAUSE_LOCATION (c),
			"allocator %qE must be either a variable or a "
			"predefined allocator", t);
	      اكسر;
	    }
	  وإلا إذا (درخت_کد (t) == CONST_DECL)
	    {
	      /* omp_null_allocator is ignored and for predefined allocators,
		 no special handling is required; thus, mark them removed. */
	      remove = درست;

	      إذا (OMP_CLAUSE_استفاده_میکند_ALLOCATORS_MEMSPACE (c)
		  || OMP_CLAUSE_استفاده_میکند_ALLOCATORS_TRAITS (c))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "modifiers cannot be used with predefined "
			    "allocator %qE", t);
		  اكسر;
		}
	    }
	  t = OMP_CLAUSE_استفاده_میکند_ALLOCATORS_MEMSPACE (c);
	  إذا (t == error_mark_گره)
	    {
	      remove = درست;
	      اكسر;
	    }
	  إذا (t != NULL_درخت
	      && ((درخت_کد (t) != CONST_DECL && درخت_کد (t) != INTEGER_CST)
		  || درخت_کد (درخت_TYPE (t)) != ENUMERAL_TYPE
		  || strcmp (IDENTIFIER_اشاره_گر (TYPE_IDENTIFIER (درخت_TYPE (t))),
			     "omp_memspace_handle_t") != 0))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c), "memspace modifier %qE must be"
			" constant enum of %<omp_memspace_handle_t%> type", t);
	      remove = درست;
	      اكسر;
	    }
	  t = OMP_CLAUSE_استفاده_میکند_ALLOCATORS_TRAITS (c);
	  إذا (t == error_mark_گره)
	    {
	      remove = درست;
	      اكسر;
	    }
	  إذا (t != NULL_درخت
	      && t != error_mark_گره
	      && (DECL_EXTERNAL (t)
		  || درخت_کد (t) == PARM_DECL))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c), "traits array %qE must be "
			"defined in same scope as the construct on which the "
			"clause appears", t);
	      remove = درست;
	    }
	  إذا (t != NULL_درخت)
	    {
	      منطقي type_err = خطأ;

	      إذا (درخت_کد (درخت_TYPE (t)) != ARRAY_TYPE
		  || DECL_اندازه (t) == NULL_درخت
		  || !COMPLETE_TYPE_P (درخت_TYPE (t)))
		type_err = درست;
	      وإلا
		{
		  درخت elem_t = درخت_TYPE (درخت_TYPE (t));
		  إذا (درخت_کد (elem_t) != رکورد_TYPE
		      || strcmp (IDENTIFIER_اشاره_گر (TYPE_IDENTIFIER (elem_t)),
				 "omp_alloctrait_t") != 0
		      || !TYPE_READONLY (elem_t))
		    type_err = درست;
		}
	      إذا (type_err)
		{
		  إذا (t != error_mark_گره)
		    error_at (OMP_CLAUSE_LOCATION (c), "traits array %qE must "
			      "be of %<const omp_alloctrait_t []%> type", t);
		  وإلا
		    error_at (OMP_CLAUSE_LOCATION (c), "traits array must "
			      "be of %<const omp_alloctrait_t []%> type");
		  remove = درست;
		}
	      وإلا
		{
		  درخت cst_val = decl_constant_مقدار_1 (t, درست);
		  إذا (cst_val == t)
		    {
		      error_at (OMP_CLAUSE_LOCATION (c), "traits array must be "
				"initialized with constants");

		      remove = درست;
		    }
		}
	    }
	  إذا (remove)
	    اكسر;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  استمر;
	حالة OMP_CLAUSE_DEPEND:
	  depend_clause = c;
	  /* FALLTHRU */
	حالة OMP_CLAUSE_AFFINITY:
	  t = OMP_CLAUSE_DECL (c);
	  إذا (OMP_ITERATOR_DECL_P (t))
	    {
	      إذا (درخت_PURPOSE (t) != آخرین_iterators)
		آخرین_iterators_remove
		  = c_omp_پایان_iterators (درخت_PURPOSE (t));
	      آخرین_iterators = درخت_PURPOSE (t);
	      t = درخت_مقدار (t);
	      إذا (آخرین_iterators_remove)
		t = error_mark_گره;
	    }
	  وإلا
	    آخرین_iterators = NULL_درخت;
	  إذا (درخت_کد (t) == OMP_ARRAY_SECTION)
	    {
	      إذا (handle_omp_array_sections (c, ort))
		remove = درست;
	      وإلا إذا (OMP_CLAUSE_کد (c) == OMP_CLAUSE_DEPEND
		       && OMP_CLAUSE_DEPEND_نوع (c) == OMP_CLAUSE_DEPEND_DEPOBJ)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<depend%> clause with %<depobj%> dependence "
			    "type on array section");
		  remove = درست;
		}
	      اكسر;
	    }
	  إذا (t == error_mark_گره)
	    remove = درست;
	  وإلا إذا (OMP_CLAUSE_کد (c) == OMP_CLAUSE_DEPEND
		   && t == ridpointers[RID_OMP_ALL_حافظه])
	    {
	      إذا (OMP_CLAUSE_DEPEND_نوع (c) != OMP_CLAUSE_DEPEND_بیرون
		  && OMP_CLAUSE_DEPEND_نوع (c) != OMP_CLAUSE_DEPEND_INOUT)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<omp_all_memory%> used with %<depend%> kind "
			    "other than %<out%> or %<inout%>");
		  remove = درست;
		}
	    }
	  وإلا إذا (!lvalue_p (t))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not lvalue expression nor array section in "
			"%qs clause", t,
			omp_clause_کد_name[OMP_CLAUSE_کد (c)]);
	      remove = درست;
	    }
	  وإلا إذا (درخت_کد (t) == COMPONENT_REF
		   && DECL_C_بیت_فیلد (درخت_عملوند (t, 1)))
	    {
	      gcc_assert (OMP_CLAUSE_کد (c) == OMP_CLAUSE_DEPEND
			  || OMP_CLAUSE_کد (c) == OMP_CLAUSE_AFFINITY);
	      error_at (OMP_CLAUSE_LOCATION (c),
			"bit-field %qE in %qs clause", t,
			omp_clause_کد_name[OMP_CLAUSE_کد (c)]);
	      remove = درست;
	    }
	  وإلا إذا (OMP_CLAUSE_کد (c) == OMP_CLAUSE_DEPEND
		   && OMP_CLAUSE_DEPEND_نوع (c) == OMP_CLAUSE_DEPEND_DEPOBJ)
	    {
	      إذا (!c_omp_depend_t_p (درخت_TYPE (t)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qE does not have %<omp_depend_t%> type in "
			    "%<depend%> clause with %<depobj%> dependence "
			    "type", t);
		  remove = درست;
		}
	    }
	  وإلا إذا (OMP_CLAUSE_کد (c) == OMP_CLAUSE_DEPEND
		   && c_omp_depend_t_p (درخت_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE should not have %<omp_depend_t%> type in "
			"%<depend%> clause with dependence type other than "
			"%<depobj%>", t);
	      remove = درست;
	    }
	  إذا (!remove)
	    {
	      إذا (t == ridpointers[RID_OMP_ALL_حافظه])
		t = null_اشاره_گر_گره;
	      وإلا
		{
		  درخت addr = build_unary_op (OMP_CLAUSE_LOCATION (c),
					      ADDR_عبارت, t, خطأ);
		  إذا (addr == error_mark_گره)
		    {
		      remove = درست;
		      اكسر;
		    }
		  t = build_غیرمستقیم_ref (OMP_CLAUSE_LOCATION (c), addr,
					  RO_UNARY_ستاره);
		  إذا (t == error_mark_گره)
		    {
		      remove = درست;
		      اكسر;
		    }
		}
	      إذا (OMP_ITERATOR_DECL_P (OMP_CLAUSE_DECL (c)))
		درخت_مقدار (OMP_CLAUSE_DECL (c)) = t;
	      وإلا
		OMP_CLAUSE_DECL (c) = t;
	    }
	  اكسر;

	حالة OMP_CLAUSE_MAP:
	  إذا (OMP_CLAUSE_MAP_IMPLICIT (c) && !implicit_moved)
	    اذهب move_implicit;
	  إذا (OMP_CLAUSE_MAP_نوع (c) == GOMP_MAP_افزودن_MAPPER_NAME
	      || OMP_CLAUSE_MAP_نوع (c) == GOMP_MAP_برداشت_MAPPER_NAME)
	    {
	      remove = درست;
	      اكسر;
	    }
	  /* FALLTHRU */
	حالة OMP_CLAUSE_مقصد:
	حالة OMP_CLAUSE_FROM:
	  إذا (OMP_CLAUSE_ITERATORS (c)
	      && c_omp_پایان_iterators (OMP_CLAUSE_ITERATORS (c)))
	    {
	      t = error_mark_گره;
	      اكسر;
	    }
	  /* FALLTHRU */
	حالة OMP_CLAUSE__CACHE_:
	  {
	    استفاده نطاق omp_addr_tokenizer;
	    auto_vec<omp_addr_token *, 10> addr_نشانهها;

	    t = OMP_CLAUSE_DECL (c);
	    إذا (درخت_کد (t) == OMP_ARRAY_SECTION)
	      {
		grp_شروع_p = pc;
		grp_sentinel = OMP_CLAUSE_CHAIN (c);

		إذا (handle_omp_array_sections (c, ort))
		  remove = درست;
		وإلا
		  {
		    t = OMP_CLAUSE_DECL (c);
		    إذا (!omp_mappable_type (درخت_TYPE (t)))
		      {
			error_at (OMP_CLAUSE_LOCATION (c),
				  "array section does not have mappable type "
				  "in %qs clause",
				  omp_clause_کد_name[OMP_CLAUSE_کد (c)]);
			remove = درست;
		      }
		    وإلا إذا (TYPE_ATOMIC (درخت_TYPE (t)))
		      {
			error_at (OMP_CLAUSE_LOCATION (c),
				  "%<_Atomic%> %qE in %qs clause", t,
				  omp_clause_کد_name[OMP_CLAUSE_کد (c)]);
			remove = درست;
		      }
		    طالما (درخت_کد (t) == ARRAY_REF)
		      t = درخت_عملوند (t, 0);

		    c_omp_آدرس_inspector ai (OMP_CLAUSE_LOCATION (c), t);

		    إذا (!omp_parse_عبارت (addr_نشانهها, t))
		      {
			sorry_at (OMP_CLAUSE_LOCATION (c),
				  "unsupported map expression %qE",
				  OMP_CLAUSE_DECL (c));
			remove = درست;
			اكسر;
		      }

		    /* This check is to determine if this will be the only map
		       node created for this clause.  Otherwise, we'll check
		       the following FIRSTPRIVATE_POINTER or ATTACH_DETACH
		       node on the next iteration(s) of the loop.   */
		    إذا (addr_نشانهها.درازی () >= 4
			&& addr_نشانهها[0]->type == STRUCTURE_پایه
			&& addr_نشانهها[0]->u.structure_پایه_نوع == پایه_DECL
			&& addr_نشانهها[1]->type == ACCESS_روش
			&& addr_نشانهها[2]->type == COMPONENT_SELECTOR
			&& addr_نشانهها[3]->type == ACCESS_روش
			&& (addr_نشانهها[3]->u.access_نوع == ACCESS_مستقیم
			    || (addr_نشانهها[3]->u.access_نوع
				== ACCESS_نمایهای_ARRAY)))
		      {
			درخت rt = addr_نشانهها[1]->عبارت;

			gcc_assert (DECL_P (rt));

			إذا (OMP_CLAUSE_کد (c) == OMP_CLAUSE_MAP
			    && OMP_CLAUSE_MAP_IMPLICIT (c)
			    && (bitmap_بیت_p (&map_سر, DECL_UID (rt))
				|| bitmap_بیت_p (&map_فیلد_سر, DECL_UID (rt))
				|| bitmap_بیت_p (&map_firstprivate_سر,
						 DECL_UID (rt))))
			  {
			    remove = درست;
			    اكسر;
			  }
			إذا (bitmap_بیت_p (&map_فیلد_سر, DECL_UID (rt)))
			  اكسر;
			إذا (bitmap_بیت_p (&map_سر, DECL_UID (rt)))
			  {
			    إذا (OMP_CLAUSE_کد (c) != OMP_CLAUSE_MAP)
			      error_at (OMP_CLAUSE_LOCATION (c),
					"%qD appears more than once in motion "
					"clauses", rt);
			    وإلا إذا (openacc)
			      error_at (OMP_CLAUSE_LOCATION (c),
					"%qD appears more than once in data "
					"clauses", rt);
			    وإلا
			      error_at (OMP_CLAUSE_LOCATION (c),
					"%qD appears more than once in map "
					"clauses", rt);
			    remove = درست;
			  }
			وإلا
			  {
			    bitmap_مجموعه_بیت (&map_سر, DECL_UID (rt));
			    bitmap_مجموعه_بیت (&map_فیلد_سر, DECL_UID (rt));
			  }
		      }
		  }
		إذا (c_oacc_check_attachments (c))
		  remove = درست;
		إذا (OMP_CLAUSE_کد (c) == OMP_CLAUSE_MAP
		    && (OMP_CLAUSE_MAP_نوع (c) == GOMP_MAP_ATTACH
			|| OMP_CLAUSE_MAP_نوع (c) == GOMP_MAP_DETACH)
		    && !OMP_CLAUSE_اندازه (c))
		  /* In this case, we have a single array element which is a
		     pointer, and we already set OMP_CLAUSE_SIZE in
		     handle_omp_array_sections above.  For attach/detach
		     clauses, reset the OMP_CLAUSE_SIZE (representing a bias)
		     to zero here.  */
		  OMP_CLAUSE_اندازه (c) = اندازه_zero_گره;
		اكسر;
	      }
	    وإلا إذا (!omp_parse_عبارت (addr_نشانهها, t))
	      {
		sorry_at (OMP_CLAUSE_LOCATION (c),
			  "unsupported map expression %qE",
			  OMP_CLAUSE_DECL (c));
		remove = درست;
		اكسر;
	      }
	    إذا (t == error_mark_گره)
	      {
		remove = درست;
		اكسر;
	      }

	    درخت attr;
	    إذا (DECL_P (t)
		&& OMP_CLAUSE_کد (c) == OMP_CLAUSE_MAP
		&& (attr = lookup_attribute ("omp declare target",
					     DECL_صفات (t)))
		&& مقدار_member (get_identifier ("local"),
				 درخت_مقدار (attr)))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "device-local variable %qD cannot appear "
			  "in map clause", t);
		remove = درست;
		اكسر;
	      }

	    /* OpenACC attach / detach clauses must be pointers.  */
	    إذا (c_oacc_check_attachments (c))
	      {
		remove = درست;
		اكسر;
	      }
	    إذا (OMP_CLAUSE_کد (c) == OMP_CLAUSE_MAP
		&& (OMP_CLAUSE_MAP_نوع (c) == GOMP_MAP_ATTACH
		    || OMP_CLAUSE_MAP_نوع (c) == GOMP_MAP_DETACH)
		&& !OMP_CLAUSE_اندازه (c))
	      /* For attach/detach clauses, set OMP_CLAUSE_SIZE (representing a
		 bias) to zero here, so it is not set erroneously to the pointer
		 size later on in gimplify.cc.  */
	      OMP_CLAUSE_اندازه (c) = اندازه_zero_گره;

	    c_omp_آدرس_inspector ai (OMP_CLAUSE_LOCATION (c), t);

	    إذا (!ai.check_clause (c))
	      {
		remove = درست;
		اكسر;
	      }

	    إذا (!ai.map_supported_p ())
	      {
		sorry_at (OMP_CLAUSE_LOCATION (c),
			  "unsupported map expression %qE",
			  OMP_CLAUSE_DECL (c));
		remove = درست;
		اكسر;
	      }

	    gcc_assert ((addr_نشانهها[0]->type == ARRAY_پایه
			 || addr_نشانهها[0]->type == STRUCTURE_پایه)
			&& addr_نشانهها[1]->type == ACCESS_روش);

	    t = addr_نشانهها[1]->عبارت;

	    إذا (addr_نشانهها[0]->u.structure_پایه_نوع != پایه_DECL)
	      اذهب skip_decl_checks;

	    /* For OpenMP, we can access a struct "t" and "t.d" on the same
	       mapping.  OpenACC allows multiple fields of the same structure
	       to be written.  */
	    إذا (addr_نشانهها[0]->type == STRUCTURE_پایه
		&& (bitmap_بیت_p (&map_فیلد_سر, DECL_UID (t))
		    || (!openacc && bitmap_بیت_p (&map_سر, DECL_UID (t)))))
	      اذهب skip_decl_checks;

	    إذا (!VAR_P (t) && درخت_کد (t) != PARM_DECL)
	      {
		إذا (ort != C_ORT_ACC && عبارت_P (t))
		  اكسر;

		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is not a variable in %qs clause", t,
			  omp_clause_کد_name[OMP_CLAUSE_کد (c)]);
		remove = درست;
	      }
	    وإلا إذا (VAR_P (t) && DECL_THREAD_LOCAL_P (t))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD is threadprivate variable in %qs clause", t,
			  omp_clause_کد_name[OMP_CLAUSE_کد (c)]);
		remove = درست;
	      }
	    وإلا إذا ((OMP_CLAUSE_کد (c) != OMP_CLAUSE_MAP
		      || (OMP_CLAUSE_MAP_نوع (c)
			  != GOMP_MAP_FIRSTPRIVATE_اشاره_گر))
		     && !c_mark_addressable (t))
	      remove = درست;
	    وإلا إذا (!(OMP_CLAUSE_کد (c) == OMP_CLAUSE_MAP
		       && (OMP_CLAUSE_MAP_نوع (c) == GOMP_MAP_اشاره_گر
			   || (OMP_CLAUSE_MAP_نوع (c)
			       == GOMP_MAP_FIRSTPRIVATE_اشاره_گر)
			   || (OMP_CLAUSE_MAP_نوع (c)
			       == GOMP_MAP_FORCE_DEVICEPTR)))
		     && t == OMP_CLAUSE_DECL (c)
		     && !omp_mappable_type (درخت_TYPE (t)))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD does not have a mappable type in %qs clause", t,
			  omp_clause_کد_name[OMP_CLAUSE_کد (c)]);
		remove = درست;
	      }
	    وإلا إذا (درخت_TYPE (t) == error_mark_گره)
	      remove = درست;
	    وإلا إذا (TYPE_ATOMIC (strip_array_types (درخت_TYPE (t))))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%<_Atomic%> %qE in %qs clause", t,
			  omp_clause_کد_name[OMP_CLAUSE_کد (c)]);
		remove = درست;
	      }
	    وإلا إذا (OMP_CLAUSE_کد (c) == OMP_CLAUSE_MAP
		     && OMP_CLAUSE_MAP_IMPLICIT (c)
		     && (bitmap_بیت_p (&map_سر, DECL_UID (t))
			 || bitmap_بیت_p (&map_فیلد_سر, DECL_UID (t))
			 || bitmap_بیت_p (&map_firstprivate_سر,
					  DECL_UID (t))))
	      remove = درست;
	    وإلا إذا (OMP_CLAUSE_کد (c) == OMP_CLAUSE_MAP
		     && (OMP_CLAUSE_MAP_نوع (c)
			 == GOMP_MAP_FIRSTPRIVATE_اشاره_گر))
	      {
		إذا (bitmap_بیت_p (&generic_سر, DECL_UID (t))
		    || bitmap_بیت_p (&firstprivate_سر, DECL_UID (t))
		    || bitmap_بیت_p (&map_firstprivate_سر, DECL_UID (t)))
		  {
		    error_at (OMP_CLAUSE_LOCATION (c),
			      "%qD appears more than once in data clauses", t);
		    remove = درست;
		  }
		وإلا إذا (bitmap_بیت_p (&map_سر, DECL_UID (t))
			 && !bitmap_بیت_p (&map_فیلد_سر, DECL_UID (t))
			 && openacc)
		  {
		    error_at (OMP_CLAUSE_LOCATION (c),
			      "%qD appears more than once in data clauses", t);
		    remove = درست;
		  }
		وإلا
		  bitmap_مجموعه_بیت (&map_firstprivate_سر, DECL_UID (t));
	      }
	    وإلا إذا (bitmap_بیت_p (&map_سر, DECL_UID (t))
		     && !bitmap_بیت_p (&map_فیلد_سر, DECL_UID (t))
		     && ort != C_ORT_OMP
		     && ort != C_ORT_OMP_هدف
		     && ort != C_ORT_OMP_EXIT_داده)
	      {
		إذا (OMP_CLAUSE_کد (c) != OMP_CLAUSE_MAP)
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in motion clauses", t);
		وإلا إذا (openacc)
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in data clauses", t);
		وإلا
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in map clauses", t);
		remove = درست;
	      }
	    وإلا إذا (openacc && bitmap_بیت_p (&generic_سر, DECL_UID (t)))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears more than once in data clauses", t);
		remove = درست;
	      }
	    وإلا إذا (bitmap_بیت_p (&firstprivate_سر, DECL_UID (t))
		     || bitmap_بیت_p (&is_on_device_سر, DECL_UID (t)))
	      {
		إذا (openacc)
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in data clauses", t);
		وإلا
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears both in data and map clauses", t);
		remove = درست;
	      }
	    وإلا إذا (!omp_access_chain_p (addr_نشانهها, 1))
	      {
		bitmap_مجموعه_بیت (&map_سر, DECL_UID (t));
		إذا (t != OMP_CLAUSE_DECL (c)
		    && درخت_کد (OMP_CLAUSE_DECL (c)) == COMPONENT_REF)
		  bitmap_مجموعه_بیت (&map_فیلد_سر, DECL_UID (t));
	      }

	  skip_decl_checks:
	    /* If we call omp_expand_map_clause in handle_omp_array_sections,
	       the containing loop (here) iterates through the new nodes
	       created by that expansion.  Avoid expanding those again (just
	       by checking the node type).  */
	    إذا (!remove
		&& ort != C_ORT_DECLARE_SIMD
		&& (OMP_CLAUSE_کد (c) != OMP_CLAUSE_MAP
		    || (OMP_CLAUSE_MAP_نوع (c) != GOMP_MAP_FIRSTPRIVATE_اشاره_گر
			&& (OMP_CLAUSE_MAP_نوع (c)
			    != GOMP_MAP_FIRSTPRIVATE_REFERENCE)
			&& OMP_CLAUSE_MAP_نوع (c) != GOMP_MAP_ALWAYS_اشاره_گر
			&& OMP_CLAUSE_MAP_نوع (c) != GOMP_MAP_ATTACH_DETACH
			&& OMP_CLAUSE_MAP_نوع (c) != GOMP_MAP_ATTACH
			&& OMP_CLAUSE_MAP_نوع (c) != GOMP_MAP_DETACH)))
	      {
		grp_شروع_p = pc;
		grp_sentinel = OMP_CLAUSE_CHAIN (c);
		درخت nc = ai.expand_map_clause (c, OMP_CLAUSE_DECL (c),
						addr_نشانهها, ort);
		إذا (nc != error_mark_گره)
		  c = nc;
	      }
	  }
	  اكسر;

	حالة OMP_CLAUSE_ENTER:
	حالة OMP_CLAUSE_LINK:
	حالة OMP_CLAUSE_LOCAL:
	  t = OMP_CLAUSE_DECL (c);
	  ثابت حرف *cname;
	  cname = omp_clause_کد_name[OMP_CLAUSE_کد (c)];
	  إذا (OMP_CLAUSE_کد (c) == OMP_CLAUSE_ENTER
	      && OMP_CLAUSE_ENTER_مقصد (c))
	    cname = "to";
	  إذا (درخت_کد (t) == FUNCTION_DECL
	      && OMP_CLAUSE_کد (c) == OMP_CLAUSE_ENTER)
	    ;
	  وإلا إذا (!VAR_P (t))
	    {
	      إذا (OMP_CLAUSE_کد (c) == OMP_CLAUSE_ENTER)
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is neither a variable nor a function name in "
			  "clause %qs", t, cname);
	      وإلا
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is not a variable in clause %qs", t, cname);
	      remove = درست;
	    }
	  وإلا إذا (DECL_THREAD_LOCAL_P (t))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD is threadprivate variable in %qs clause", t,
			cname);
	      remove = درست;
	    }
	  وإلا إذا (!omp_mappable_type (درخت_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD does not have a mappable type in %qs clause", t,
			cname);
	      remove = درست;
	    }
	  إذا (remove)
	    اكسر;
	  إذا (bitmap_بیت_p (&generic_سر, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once on the same "
			"%<declare target%> directive", t);
	      remove = درست;
	    }
	  وإلا
	    bitmap_مجموعه_بیت (&generic_سر, DECL_UID (t));
	  اكسر;

	حالة OMP_CLAUSE_یکنواخت:
	  t = OMP_CLAUSE_DECL (c);
	  إذا (درخت_کد (t) != PARM_DECL)
	    {
	      إذا (DECL_P (t))
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD is not an argument in %<uniform%> clause", t);
	      وإلا
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is not an argument in %<uniform%> clause", t);
	      remove = درست;
	      اكسر;
	    }
	  /* map_head bitmap is used as uniform_head if declare_simd.  */
	  bitmap_مجموعه_بیت (&map_سر, DECL_UID (t));
	  اذهب check_dup_generic;

	حالة OMP_CLAUSE_IS_DEVICE_PTR:
	حالة OMP_CLAUSE_USE_DEVICE_PTR:
	  t = OMP_CLAUSE_DECL (c);
	  إذا (OMP_CLAUSE_کد (c) == OMP_CLAUSE_IS_DEVICE_PTR)
	    bitmap_مجموعه_بیت (&is_on_device_سر, DECL_UID (t));
	  إذا (درخت_کد (درخت_TYPE (t)) != اشاره_گر_TYPE)
	    {
	      إذا (OMP_CLAUSE_کد (c) == OMP_CLAUSE_USE_DEVICE_PTR
		  && !openacc)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qs variable is not a pointer",
			    omp_clause_کد_name[OMP_CLAUSE_کد (c)]);
		  remove = درست;
		}
	      وإلا إذا (درخت_کد (درخت_TYPE (t)) != ARRAY_TYPE)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qs variable is neither a pointer nor an array",
			    omp_clause_کد_name[OMP_CLAUSE_کد (c)]);
		  remove = درست;
		}
	    }
	  اذهب check_dup_generic;

	حالة OMP_CLAUSE_HAS_DEVICE_ADDR:
	  t = OMP_CLAUSE_DECL (c);
	  إذا (درخت_کد (t) == OMP_ARRAY_SECTION)
	    {
	      إذا (handle_omp_array_sections (c, ort))
		remove = درست;
	      وإلا
		{
		  t = OMP_CLAUSE_DECL (c);
		  طالما (درخت_کد (t) == ARRAY_REF)
		    t = درخت_عملوند (t, 0);
		}
	    }
	  bitmap_مجموعه_بیت (&is_on_device_سر, DECL_UID (t));
	  إذا (VAR_P (t) || درخت_کد (t) == PARM_DECL)
	    c_mark_addressable (t);
	  اذهب check_dup_generic_t;

	حالة OMP_CLAUSE_USE_DEVICE_ADDR:
	  t = OMP_CLAUSE_DECL (c);
	  إذا (VAR_P (t) || درخت_کد (t) == PARM_DECL)
	    c_mark_addressable (t);
	  اذهب check_dup_generic;

	حالة OMP_CLAUSE_NOWAIT:
	  إذا (copyprivate_دیده)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<nowait%> clause must not be used together "
			"with %<copyprivate%> clause");
	      remove = درست;
	      اكسر;
	    }
	  nowait_clause = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  استمر;

	حالة OMP_CLAUSE_ترتیب:
	  إذا (ordered_clause)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<order%> clause must not be used together "
			"with %<ordered%> clause");
	      remove = درست;
	      اكسر;
	    }
	  وإلا إذا (ترتیب_clause)
	    {
	      /* Silently remove duplicates.  */
	      remove = درست;
	      اكسر;
	    }
	  ترتیب_clause = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  استمر;

	حالة OMP_CLAUSE_DETACH:
	  t = OMP_CLAUSE_DECL (c);
	  إذا (detach_دیده)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"too many %qs clauses on a task construct",
			"detach");
	      remove = درست;
	      اكسر;
	    }
	  detach_دیده = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  c_mark_addressable (t);
	  استمر;

	حالة OMP_CLAUSE_IF:
	حالة OMP_CLAUSE_SELF:
	حالة OMP_CLAUSE_رقم_نخها:
	حالة OMP_CLAUSE_رقم_TEAMS:
	حالة OMP_CLAUSE_THREAD_حد:
	حالة OMP_CLAUSE_DEFAULT:
	حالة OMP_CLAUSE_UNTIED:
	حالة OMP_CLAUSE_COLLAPSE:
	حالة OMP_CLAUSE_FINAL:
	حالة OMP_CLAUSE_DEVICE:
	حالة OMP_CLAUSE_DIST_زمانبندی:
	حالة OMP_CLAUSE_DYN_GROUPPRIVATE:
	حالة OMP_CLAUSE_PARALLEL:
	حالة OMP_CLAUSE_FOR:
	حالة OMP_CLAUSE_SECTIONS:
	حالة OMP_CLAUSE_TASKGROUP:
	حالة OMP_CLAUSE_PROC_BIND:
	حالة OMP_CLAUSE_DEVICE_TYPE:
	حالة OMP_CLAUSE_اولویت:
	حالة OMP_CLAUSE_نخها:
	حالة OMP_CLAUSE_SIMD:
	حالة OMP_CLAUSE_HINT:
	حالة OMP_CLAUSE_FILTER:
	حالة OMP_CLAUSE_DEFAULTMAP:
	حالة OMP_CLAUSE_BIND:
	حالة OMP_CLAUSE_رقم_GANGS:
	حالة OMP_CLAUSE_رقم_WORKERS:
	حالة OMP_CLAUSE_وکتور_درازی:
	حالة OMP_CLAUSE_ASYNC:
	حالة OMP_CLAUSE_WAIT:
	حالة OMP_CLAUSE_AUTO:
	حالة OMP_CLAUSE_INDEPENDENT:
	حالة OMP_CLAUSE_SEQ:
	حالة OMP_CLAUSE_GANG:
	حالة OMP_CLAUSE_کارگر:
	حالة OMP_CLAUSE_وکتور:
	حالة OMP_CLAUSE_TILE:
	حالة OMP_CLAUSE_IF_PRESENT:
	حالة OMP_CLAUSE_FINALIZE:
	حالة OMP_CLAUSE_NOHOST:
	حالة OMP_CLAUSE_غیرمستقیم:
	حالة OMP_CLAUSE_NOVARIANTS:
	حالة OMP_CLAUSE_NOCONTEXT:
	  pc = &OMP_CLAUSE_CHAIN (c);
	  استمر;

	حالة OMP_CLAUSE_GRAINSIZE:
	  grainsize_دیده = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  استمر;

	حالة OMP_CLAUSE_رقم_TASKS:
	  رقم_tasks_دیده = درست;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  استمر;

	حالة OMP_CLAUSE_MERGEABLE:
	  mergeable_دیده = درست;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  استمر;

	حالة OMP_CLAUSE_NOGROUP:
	  nogroup_دیده = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  استمر;

	حالة OMP_CLAUSE_زمانبندی:
	  زمانبندی_clause = c;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  استمر;

	حالة OMP_CLAUSE_ORDERED:
	  ordered_clause = c;
	  إذا (ترتیب_clause)
	    {
	      error_at (OMP_CLAUSE_LOCATION (*ترتیب_clause),
			"%<order%> clause must not be used together "
			"with %<ordered%> clause");
	      *ترتیب_clause = OMP_CLAUSE_CHAIN (*ترتیب_clause);
	      ترتیب_clause = عدم;
	    }
	  pc = &OMP_CLAUSE_CHAIN (c);
	  استمر;

	حالة OMP_CLAUSE_SAFELEN:
	  safelen = c;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  استمر;
	حالة OMP_CLAUSE_SIMDLEN:
	  simdlen = c;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  استمر;

	حالة OMP_CLAUSE_پر:
	  پر_دیده = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  استمر;

	حالة OMP_CLAUSE_PARTIAL:
	  partial_دیده = درست;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  استمر;

	حالة OMP_CLAUSE_SIZES:
	  pc = &OMP_CLAUSE_CHAIN (c);
	  استمر;

	حالة OMP_CLAUSE_INBRANCH:
	حالة OMP_CLAUSE_NOTINBRANCH:
	  إذا (branch_دیده)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<inbranch%> clause is incompatible with "
			"%<notinbranch%>");
	      remove = درست;
	      اكسر;
	    }
	  branch_دیده = درست;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  استمر;

	حالة OMP_CLAUSE_INCLUSIVE:
	حالة OMP_CLAUSE_EXCLUSIVE:
	  need_complete = درست;
	  need_implicitly_determined = درست;
	  t = OMP_CLAUSE_DECL (c);
	  إذا (!VAR_P (t) && درخت_کد (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %qs", t,
			omp_clause_کد_name[OMP_CLAUSE_کد (c)]);
	      remove = درست;
	    }
	  اكسر;

	حالة OMP_CLAUSE_INIT:
	  init_دیده = درست;
	  إذا (!OMP_CLAUSE_INIT_TARGETSYNC (c))
	    init_no_targetsync_clause = c;
	  /* FALLTHRU */
	حالة OMP_CLAUSE_DESTROY:
	حالة OMP_CLAUSE_USE:
	  init_use_destroy_دیده = درست;
	  t = OMP_CLAUSE_DECL (c);
	  إذا (bitmap_بیت_p (&generic_سر, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD appears more than once in action clauses", t);
	      remove = درست;
	      اكسر;
	    }
	  bitmap_مجموعه_بیت (&generic_سر, DECL_UID (t));
	  /* FALLTHRU */
	حالة OMP_CLAUSE_INTEROP:
	  إذا (/* ort == C_ORT_OMP_INTEROP [uncomment for depobj init]  */
		   !c_omp_interop_t_p (درخت_TYPE (OMP_CLAUSE_DECL (c))))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD must be of %<omp_interop_t%>",
			OMP_CLAUSE_DECL (c));
	      remove = درست;
	    }
	  وإلا إذا ((OMP_CLAUSE_کد (c) == OMP_CLAUSE_INIT
		    || OMP_CLAUSE_کد (c) == OMP_CLAUSE_DESTROY)
		   && درخت_READONLY (OMP_CLAUSE_DECL (c)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD shall not be const", OMP_CLAUSE_DECL (c));
	      remove = درست;
	    }
	  pc = &OMP_CLAUSE_CHAIN (c);
	  اكسر;
	افتراضي:
	  gcc_unreachable ();
	}

      إذا (!remove)
	{
	  t = OMP_CLAUSE_DECL (c);

	  إذا (need_complete)
	    {
	      t = require_complete_type (OMP_CLAUSE_LOCATION (c), t);
	      إذا (t == error_mark_گره)
		remove = درست;
	    }

	  إذا (need_implicitly_determined)
	    {
	      ثابت حرف *share_name = عدم;

	      إذا (VAR_P (t) && DECL_THREAD_LOCAL_P (t))
		share_name = "threadprivate";
	      وإلا بدل (c_omp_predetermined_sharing (t))
		{
		حالة OMP_CLAUSE_DEFAULT_UNSPECIFIED:
		  اكسر;
		حالة OMP_CLAUSE_DEFAULT_SHARED:
		  إذا ((OMP_CLAUSE_کد (c) == OMP_CLAUSE_SHARED
		       || OMP_CLAUSE_کد (c) == OMP_CLAUSE_FIRSTPRIVATE)
		      && c_omp_predefined_variable (t))
		    /* The __func__ variable and similar function-local
		       predefined variables may be listed in a shared or
		       firstprivate clause.  */
		    اكسر;
		  share_name = "shared";
		  اكسر;
		حالة OMP_CLAUSE_DEFAULT_خصوصی:
		  share_name = "private";
		  اكسر;
		افتراضي:
		  gcc_unreachable ();
		}
	      إذا (share_name)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qE is predetermined %qs for %qs",
			    t, share_name,
			    omp_clause_کد_name[OMP_CLAUSE_کد (c)]);
		  remove = درست;
		}
	      وإلا إذا (درخت_READONLY (t)
		       && OMP_CLAUSE_کد (c) != OMP_CLAUSE_SHARED
		       && OMP_CLAUSE_کد (c) != OMP_CLAUSE_FIRSTPRIVATE)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<const%> qualified %qE may appear only in "
			    "%<shared%> or %<firstprivate%> clauses", t);
		  remove = درست;
		}
	    }
	}

      إذا (remove)
	{
	  إذا (grp_شروع_p)
	    {
	      /* If we found a clause to remove, we want to remove the whole
		 expanded group, otherwise gimplify
		 (omp_resolve_clause_dependencies) can get confused.  */
	      *grp_شروع_p = grp_sentinel;
	      pc = grp_شروع_p;
	      grp_شروع_p = عدم;
	    }
	  وإلا
	    *pc = OMP_CLAUSE_CHAIN (c);
	}
      وإلا
	pc = &OMP_CLAUSE_CHAIN (c);
    }

  إذا (grp_شروع_p
      && OMP_CLAUSE_HAS_ITERATORS (*grp_شروع_p))
    لكل (درخت gc = *grp_شروع_p; gc; gc = OMP_CLAUSE_CHAIN (gc))
      OMP_CLAUSE_ITERATORS (gc) = OMP_CLAUSE_ITERATORS (*grp_شروع_p);

  إذا (simdlen
      && safelen
      && درخت_int_cst_lt (OMP_CLAUSE_SAFELEN_عبارت (safelen),
			  OMP_CLAUSE_SIMDLEN_عبارت (simdlen)))
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
      OMP_CLAUSE_SIMDLEN_عبارت (simdlen)
	= OMP_CLAUSE_SAFELEN_عبارت (safelen);
    }

  إذا (ordered_clause
      && زمانبندی_clause
      && (OMP_CLAUSE_زمانبندی_نوع (زمانبندی_clause)
	  & OMP_CLAUSE_زمانبندی_NONMONOTONIC))
    {
      error_at (OMP_CLAUSE_LOCATION (زمانبندی_clause),
		"%<nonmonotonic%> schedule modifier specified together "
		"with %<ordered%> clause");
      OMP_CLAUSE_زمانبندی_نوع (زمانبندی_clause)
	= (تعداد omp_clause_زمانبندی_نوع)
	  (OMP_CLAUSE_زمانبندی_نوع (زمانبندی_clause)
	   & ~OMP_CLAUSE_زمانبندی_NONMONOTONIC);
    }

  إذا (reduction_دیده < 0 && ordered_clause)
    {
      error_at (OMP_CLAUSE_LOCATION (ordered_clause),
		"%qs clause specified together with %<inscan%> "
		"%<reduction%> clause", "ordered");
      reduction_دیده = -2;
    }

  إذا (reduction_دیده < 0 && زمانبندی_clause)
    {
      error_at (OMP_CLAUSE_LOCATION (زمانبندی_clause),
		"%qs clause specified together with %<inscan%> "
		"%<reduction%> clause", "schedule");
      reduction_دیده = -2;
    }

  إذا (خطی_variable_گام_check
      || reduction_دیده == -2
      || allocate_دیده
      || هدف_درون_reduction_دیده)
    لكل (pc = &clauses, c = clauses; c ; c = *pc)
      {
	منطقي remove = خطأ;
	إذا (allocate_دیده)
	  بدل (OMP_CLAUSE_کد (c))
	    {
	    حالة OMP_CLAUSE_REDUCTION:
	    حالة OMP_CLAUSE_درون_REDUCTION:
	    حالة OMP_CLAUSE_TASK_REDUCTION:
	      إذا (درخت_کد (OMP_CLAUSE_DECL (c)) == MEM_REF)
		{
		  t = درخت_عملوند (OMP_CLAUSE_DECL (c), 0);
		  إذا (درخت_کد (t) == اشاره_گر_PLUS_عبارت)
		    t = درخت_عملوند (t, 0);
		  إذا (درخت_کد (t) == ADDR_عبارت
		      || غیرمستقیم_REF_P (t))
		    t = درخت_عملوند (t, 0);
		  إذا (DECL_P (t))
		    bitmap_clear_بیت (&aligned_سر, DECL_UID (t));
		  اكسر;
		}
	      /* FALLTHRU */
	    حالة OMP_CLAUSE_خصوصی:
	    حالة OMP_CLAUSE_FIRSTPRIVATE:
	    حالة OMP_CLAUSE_LASTPRIVATE:
	    حالة OMP_CLAUSE_خطی:
	      إذا (DECL_P (OMP_CLAUSE_DECL (c)))
		bitmap_clear_بیت (&aligned_سر,
				  DECL_UID (OMP_CLAUSE_DECL (c)));
	      اكسر;
	    افتراضي:
	      اكسر;
	    }
	إذا (OMP_CLAUSE_کد (c) == OMP_CLAUSE_خطی
	    && OMP_CLAUSE_خطی_VARIABLE_STRIDE (c)
	    && !bitmap_بیت_p (&map_سر,
			      DECL_UID (OMP_CLAUSE_خطی_گام (c))))
	  {
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%<linear%> clause step is a parameter %qD not "
		      "specified in %<uniform%> clause",
		      OMP_CLAUSE_خطی_گام (c));
	    remove = درست;
	  }
	وإلا إذا (OMP_CLAUSE_کد (c) == OMP_CLAUSE_REDUCTION
		 && reduction_دیده == -2)
	  OMP_CLAUSE_REDUCTION_INSCAN (c) = 0;
	إذا (هدف_درون_reduction_دیده
	    && OMP_CLAUSE_کد (c) == OMP_CLAUSE_MAP)
	  {
	    درخت t = OMP_CLAUSE_DECL (c);
	    طالما (handled_component_p (t)
		   || غیرمستقیم_REF_P (t)
		   || درخت_کد (t) == ADDR_عبارت
		   || درخت_کد (t) == MEM_REF
		   || درخت_کد (t) == NON_LVALUE_عبارت)
	      t = درخت_عملوند (t, 0);
	    إذا (DECL_P (t)
		&& bitmap_بیت_p (&oacc_reduction_سر, DECL_UID (t)))
	      OMP_CLAUSE_MAP_درون_REDUCTION (c) = 1;
	  }

	إذا (remove)
	  *pc = OMP_CLAUSE_CHAIN (c);
	وإلا
	  pc = &OMP_CLAUSE_CHAIN (c);
      }

  إذا (allocate_دیده)
    لكل (pc = &clauses, c = clauses; c ; c = *pc)
      {
	منطقي remove = خطأ;
	إذا (OMP_CLAUSE_کد (c) == OMP_CLAUSE_ALLOCATE
	    && !OMP_CLAUSE_ALLOCATE_COMBINED (c)
	    && bitmap_بیت_p (&aligned_سر, DECL_UID (OMP_CLAUSE_DECL (c))))
	  {
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD specified in %<allocate%> clause but not in "
		      "an explicit privatization clause", OMP_CLAUSE_DECL (c));
	    remove = درست;
	  }
	إذا (remove)
	  *pc = OMP_CLAUSE_CHAIN (c);
	وإلا
	  pc = &OMP_CLAUSE_CHAIN (c);
      }

  إذا (nogroup_دیده && reduction_دیده)
    {
      error_at (OMP_CLAUSE_LOCATION (*nogroup_دیده),
		"%<nogroup%> clause must not be used together with "
		"%<reduction%> clause");
      *nogroup_دیده = OMP_CLAUSE_CHAIN (*nogroup_دیده);
    }

  إذا (grainsize_دیده && رقم_tasks_دیده)
    {
      error_at (OMP_CLAUSE_LOCATION (*grainsize_دیده),
		"%<grainsize%> clause must not be used together with "
		"%<num_tasks%> clause");
      *grainsize_دیده = OMP_CLAUSE_CHAIN (*grainsize_دیده);
    }

  إذا (پر_دیده && partial_دیده)
    {
      error_at (OMP_CLAUSE_LOCATION (*پر_دیده),
		"%<full%> clause must not be used together with "
		"%<partial%> clause");
      *پر_دیده = OMP_CLAUSE_CHAIN (*پر_دیده);
    }

  إذا (detach_دیده)
    {
      إذا (mergeable_دیده)
	{
	  error_at (OMP_CLAUSE_LOCATION (*detach_دیده),
		    "%<detach%> clause must not be used together with "
		    "%<mergeable%> clause");
	  *detach_دیده = OMP_CLAUSE_CHAIN (*detach_دیده);
	}
      وإلا
	{
	  درخت detach_decl = OMP_CLAUSE_DECL (*detach_دیده);

	  لكل (pc = &clauses, c = clauses; c ; c = *pc)
	    {
	      منطقي remove = خطأ;
	      إذا ((OMP_CLAUSE_کد (c) == OMP_CLAUSE_SHARED
		   || OMP_CLAUSE_کد (c) == OMP_CLAUSE_خصوصی
		   || OMP_CLAUSE_کد (c) == OMP_CLAUSE_FIRSTPRIVATE
		   || OMP_CLAUSE_کد (c) == OMP_CLAUSE_LASTPRIVATE)
		  && OMP_CLAUSE_DECL (c) == detach_decl)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "the event handle of a %<detach%> clause "
			    "should not be in a data-sharing clause");
		  remove = درست;
		}
	      إذا (remove)
		*pc = OMP_CLAUSE_CHAIN (c);
	      وإلا
		pc = &OMP_CLAUSE_CHAIN (c);
	    }
	}
    }

  إذا (ort == C_ORT_OMP_INTEROP
      && depend_clause
      && (!init_use_destroy_دیده
	  || (init_دیده && init_no_targetsync_clause)))
    {
      error_at (OMP_CLAUSE_LOCATION (depend_clause),
		"%<depend%> clause requires action clauses with "
		"%<targetsync%> interop-type");
      إذا (init_no_targetsync_clause)
	inform (OMP_CLAUSE_LOCATION (init_no_targetsync_clause),
		"%<init%> clause lacks the %<targetsync%> modifier");
    }

  bitmap_obstack_release (عدم);
  أرجع clauses;
}

/* Do processing necessary to make CLAUSES well-formed, where CLAUSES result
   from implicit instantiation of user-defined mappers (in gimplify.cc).  */

درخت
c_omp_پایان_mapper_clauses (درخت clauses)
{
  أرجع c_پایان_omp_clauses (clauses, C_ORT_OMP);
}

/* Return code to initialize DST with a copy constructor from SRC.
   C doesn't have copy constructors nor assignment operators, only for
   _Atomic vars we need to perform __atomic_load from src into a temporary
   followed by __atomic_store of the temporary to dst.  */

درخت
c_omp_clause_copy_ctor (درخت clause, درخت dst, درخت src)
{
  إذا (!really_atomic_lvalue (dst) && !really_atomic_lvalue (src))
    أرجع build2 (MODIFY_عبارت, درخت_TYPE (dst), dst, src);

  location_t loc = OMP_CLAUSE_LOCATION (clause);
  درخت type = درخت_TYPE (dst);
  درخت nonatomic_type = build_qualified_type (type, TYPE_UNQUALIFIED);
  درخت tmp = create_tmp_var (nonatomic_type);
  درخت tmp_addr = build_fold_addr_عبارت (tmp);
  درخت_ADDRESSABLE (tmp) = 1;
  suppress_warning (tmp);
  درخت src_addr = build_fold_addr_عبارت (src);
  درخت dst_addr = build_fold_addr_عبارت (dst);
  درخت seq_cst = build_int_cst (integer_type_گره, MEMMODEL_SEQ_CST);
  vec<درخت, va_gc> *params;
  /* Expansion of a generic atomic load may require an addition
     element, so allocate enough to prevent a resize.  */
  vec_alloc (params, 4);

  /* Build __atomic_load (&src, &tmp, SEQ_CST);  */
  درخت fndecl = builtin_decl_explicit (BUILT_درون_ATOMIC_بارگیری);
  params->سریع_افزودن (src_addr);
  params->سریع_افزودن (tmp_addr);
  params->سریع_افزودن (seq_cst);
  درخت بارگیری = c_build_function_call_vec (loc, vNULL, fndecl, params, عدم);

  vec_alloc (params, 4);

  /* Build __atomic_store (&dst, &tmp, SEQ_CST);  */
  fndecl = builtin_decl_explicit (BUILT_درون_ATOMIC_STORE);
  params->سریع_افزودن (dst_addr);
  params->سریع_افزودن (tmp_addr);
  params->سریع_افزودن (seq_cst);
  درخت store = c_build_function_call_vec (loc, vNULL, fndecl, params, عدم);
  أرجع build2 (COMPOUND_عبارت, void_type_گره, بارگیری, store);
}

/* Create a transaction node.  */

درخت
c_پایان_transaction (location_t loc, درخت بلوک, صحيح flags)
{
  درخت stmt = build_stmt (loc, TRANSACTION_عبارت, بلوک);
  إذا (flags & TM_STMT_ATTR_OUTER)
    TRANSACTION_عبارت_OUTER (stmt) = 1;
  إذا (flags & TM_STMT_ATTR_RELAXED)
    TRANSACTION_عبارت_RELAXED (stmt) = 1;
  أرجع جمع_کن_stmt (stmt);
}

/* Make a variant type in the proper way for C/C++, propagating qualifiers
   down to the element type of an array.  If ORIG_QUAL_TYPE is not
   NULL, then it should be used as the qualified type
   ORIG_QUAL_INDIRECT levels down in array type derivation (to
   preserve information about the typedef name from which an array
   type was derived).  */

درخت
c_build_qualified_type (درخت type, صحيح type_quals, درخت orig_qual_type,
			اندازه_t orig_qual_غیرمستقیم)
{
  إذا (type == error_mark_گره)
    أرجع type;

  إذا (درخت_کد (type) == ARRAY_TYPE)
    {
      درخت t;
      درخت element_type = c_build_qualified_type (درخت_TYPE (type),
						  type_quals, orig_qual_type,
						  orig_qual_غیرمستقیم - 1);

      /* See if we already have an identically qualified type.  */
      إذا (orig_qual_type && orig_qual_غیرمستقیم == 0)
	t = orig_qual_type;
      وإلا
	لكل (t = TYPE_MAIN_VARIANT (type); t; t = TYPE_بعدی_VARIANT (t))
	  {
	    إذا (TYPE_QUALS (strip_array_types (t)) == type_quals
		&& TYPE_NAME (t) == TYPE_NAME (type)
		&& TYPE_CONTEXT (t) == TYPE_CONTEXT (type)
		&& attribute_list_equal (TYPE_صفات (t),
					 TYPE_صفات (type)))
	      اكسر;
	  }
      إذا (!t)
	{
          درخت domain = TYPE_DOMAIN (type);

	  t = build_variant_type_copy (type);
	  درخت_TYPE (t) = element_type;
	  TYPE_ADDR_SPACE (t) = TYPE_ADDR_SPACE (element_type);

          إذا (TYPE_STRUCTURAL_EQUALITY_P (element_type)
              || (domain && TYPE_STRUCTURAL_EQUALITY_P (domain)))
            مجموعه_TYPE_STRUCTURAL_EQUALITY (t);
          وإلا إذا (TYPE_CANONICAL (element_type) != element_type
                   || (domain && TYPE_CANONICAL (domain) != domain))
            {
              درخت unqualified_canon
		= c_build_array_type (TYPE_CANONICAL (element_type),
				      domain ? TYPE_CANONICAL (domain)
					     : NULL_درخت);
              إذا (TYPE_معکوس_STORAGE_ترتیب (type))
                {
                  unqualified_canon
		    = build_distinct_type_copy (unqualified_canon);
                  TYPE_معکوس_STORAGE_ترتیب (unqualified_canon) = 1;
                }
              TYPE_CANONICAL (t)
		= c_build_qualified_type (unqualified_canon, type_quals);
            }
          وإلا
            TYPE_CANONICAL (t) = t;
	}
      أرجع t;
    }

  /* A restrict-qualified pointer type must be a pointer to object or
     incomplete type.  Note that the use of POINTER_TYPE_P also allows
     REFERENCE_TYPEs, which is appropriate for C++.  */
  إذا ((type_quals & TYPE_QUAL_RESTRICT)
      && (!اشاره_گر_TYPE_P (type)
	  || !C_TYPE_OBJECT_OR_INCOMPLETE_P (درخت_TYPE (type))))
    {
      error ("invalid use of %<restrict%>");
      type_quals &= ~TYPE_QUAL_RESTRICT;
    }

  درخت var_type = (orig_qual_type && orig_qual_غیرمستقیم == 0
		   ? orig_qual_type
		   : build_qualified_type (type, type_quals));

  gcc_checking_assert (C_TYPE_VARIABLE_اندازه (var_type)
		       == C_TYPE_VARIABLE_اندازه (type));
  gcc_checking_assert (c_type_variably_modified_p (var_type)
		       == c_type_variably_modified_p (type));

  /* A variant type does not inherit the list of incomplete vars from the
     type main variant.  */
  إذا ((رکورد_OR_UNION_TYPE_P (var_type)
       || درخت_کد (var_type) == ENUMERAL_TYPE)
      && TYPE_MAIN_VARIANT (var_type) != var_type)
    C_TYPE_INCOMPLETE_VARS (var_type) = 0;
  أرجع var_type;
}

/* Build a VA_ARG_EXPR for the C parser.  */

درخت
c_build_va_arg (location_t loc1, درخت عبارت, location_t loc2, درخت type,
		درخت type_عبارت)
{
  إذا (error_عملوند_p (type))
    أرجع error_mark_گره;
  /* VA_ARG_EXPR cannot be used for a scalar va_list with reverse storage
     order because it takes the address of the expression.  */
  وإلا إذا (handled_component_p (عبارت)
	   && معکوس_storage_ترتیب_for_component_p (عبارت))
    {
      error_at (loc1, "cannot use %<va_arg%> with reverse storage order");
      أرجع error_mark_گره;
    }
  وإلا إذا (!COMPLETE_TYPE_P (type))
    {
      error_at (loc2, "second argument to %<va_arg%> is of incomplete "
		"type %qT", type);
      أرجع error_mark_گره;
    }
  وإلا إذا (درخت_کد (type) == FUNCTION_TYPE)
    {
      error_at (loc2, "second argument to %<va_arg%> is a function type %qT",
		type);
      أرجع error_mark_گره;
    }
  وإلا إذا (درخت_کد (type) == ARRAY_TYPE && C_TYPE_VARIABLE_اندازه (type)
	   && !flag_isoc99)
    {
      error_at (loc2, "second argument to %<va_arg%> is an array type %qT",
		type);
      أرجع error_mark_گره;
    }
  وإلا إذا (warn_cxx_compat && درخت_کد (type) == ENUMERAL_TYPE)
    warning_at (loc2, OPT_Wc___compat,
		"C++ requires promoted type, not enum type, in %<va_arg%>");

  إذا (flag_isoc99 && درخت_کد (type) == ARRAY_TYPE)
    {
      warning_at (loc2, 0, "second argument to %<va_arg%> is an array type %qT",
		  type);
      /* We create a trap but evaluate side effects first.  */
      درخت trapfn = builtin_decl_explicit (BUILT_درون_TRAP);
      trapfn = build_call_عبارت_loc (loc2, trapfn, 0);
      درخت e2 = build2 (COMPOUND_عبارت, void_type_گره, عبارت, trapfn);
      /* Return a compound literal of the right type.  */
      درخت e1 = build_compound_literal (loc2, type, عدم, درست, 0, عدم);
      عبارت = build2 (COMPOUND_عبارت, type, e2, e1);
    }
  وإلا
    عبارت = build_va_arg (loc2, عبارت, type);

  إذا (type_عبارت)
    عبارت = build2 (COMPOUND_عبارت, درخت_TYPE (عبارت), type_عبارت, عبارت);

  أرجع عبارت;
}

/* Return truthvalue of whether T1 is the same tree structure as T2.
   Return 1 if they are the same. Return false if they are different.  */

منطقي
c_درخت_equal (درخت t1, درخت t2)
{
  تعداد درخت_کد_2 code1, code2;

  إذا (t1 == t2)
    أرجع درست;
  إذا (!t1 || !t2)
    أرجع خطأ;

  لكل (code1 = درخت_کد (t1); code1 == NON_LVALUE_عبارت;
       code1 = درخت_کد (t1))
    t1 = درخت_عملوند (t1, 0);
  لكل (code2 = درخت_کد (t2); code2 == NON_LVALUE_عبارت;
       code2 = درخت_کد (t2))
    t2 = درخت_عملوند (t2, 0);

  /* They might have become equal now.  */
  إذا (t1 == t2)
    أرجع درست;

  إذا (code1 != code2)
    أرجع خطأ;

  إذا (CONSTANT_CLASS_P (t1) && !comptypes (درخت_TYPE (t1), درخت_TYPE (t2)))
    أرجع خطأ;

  بدل (code1)
    {
    حالة INTEGER_CST:
      أرجع wi::مقصد_wide (t1) == wi::مقصد_wide (t2);

    حالة REAL_CST:
      أرجع real_equal (&درخت_REAL_CST (t1), &درخت_REAL_CST (t2));

    حالة STRING_CST:
      أرجع درخت_STRING_درازی (t1) == درخت_STRING_درازی (t2)
	&& !memcmp (درخت_STRING_اشاره_گر (t1), درخت_STRING_اشاره_گر (t2),
		    درخت_STRING_درازی (t1));

    حالة FIXED_CST:
      أرجع FIXED_مقادیر_IDENTICAL (درخت_FIXED_CST (t1),
				     درخت_FIXED_CST (t2));

    حالة COMPLEX_CST:
      أرجع c_درخت_equal (درخت_REALPART (t1), درخت_REALPART (t2))
	     && c_درخت_equal (درخت_IMAGPART (t1), درخت_IMAGPART (t2));

    حالة وکتور_CST:
      أرجع عملوند_equal_p (t1, t2, OEP_ONLY_CONST);

    حالة CONSTRUCTOR:
      /* We need to do this when determining whether or not two
	 non-type pointer to member function template arguments
	 are the same.  */
      إذا (!comptypes (درخت_TYPE (t1), درخت_TYPE (t2))
	  || CONSTRUCTOR_NELTS (t1) != CONSTRUCTOR_NELTS (t2))
	أرجع خطأ;
      {
	درخت فیلد_2, مقدار;
	بیعلامت صحيح i;
	FOR_EACH_CONSTRUCTOR_ELT (CONSTRUCTOR_ELTS (t1), i, فیلد_2, مقدار)
	  {
	    constructor_elt *elt2 = CONSTRUCTOR_ELT (t2, i);
	    إذا (!c_درخت_equal (فیلد_2, elt2->شاخص)
		|| !c_درخت_equal (مقدار, elt2->مقدار))
	      أرجع خطأ;
	  }
      }
      أرجع درست;

    حالة درخت_LIST:
      إذا (!c_درخت_equal (درخت_PURPOSE (t1), درخت_PURPOSE (t2)))
	أرجع خطأ;
      إذا (!c_درخت_equal (درخت_مقدار (t1), درخت_مقدار (t2)))
	أرجع خطأ;
      أرجع c_درخت_equal (درخت_CHAIN (t1), درخت_CHAIN (t2));

    حالة SAVE_عبارت:
      أرجع c_درخت_equal (درخت_عملوند (t1, 0), درخت_عملوند (t2, 0));

    حالة CALL_عبارت:
      {
	درخت arg1, arg2;
	call_عبارت_arg_iterator iter1, iter2;
	إذا (!c_درخت_equal (CALL_عبارت_FN (t1), CALL_عبارت_FN (t2)))
	  أرجع خطأ;
	لكل (arg1 = اولی_call_عبارت_arg (t1, &iter1),
	       arg2 = اولی_call_عبارت_arg (t2, &iter2);
	     arg1 && arg2;
	     arg1 = بعدی_call_عبارت_arg (&iter1),
	       arg2 = بعدی_call_عبارت_arg (&iter2))
	  إذا (!c_درخت_equal (arg1, arg2))
	    أرجع خطأ;
	إذا (arg1 || arg2)
	  أرجع خطأ;
	أرجع درست;
      }

    حالة هدف_عبارت:
      {
	درخت o1 = درخت_عملوند (t1, 0);
	درخت o2 = درخت_عملوند (t2, 0);

	/* Special case: if either target is an unallocated VAR_DECL,
	   it means that it's going to be unified with whatever the
	   TARGET_EXPR is really supposed to initialize, so treat it
	   as being equivalent to anything.  */
	إذا (VAR_P (o1) && DECL_NAME (o1) == NULL_درخت
	    && !DECL_RTL_مجموعه_P (o1))
	  /*Nop*/;
	وإلا إذا (VAR_P (o2) && DECL_NAME (o2) == NULL_درخت
		 && !DECL_RTL_مجموعه_P (o2))
	  /*Nop*/;
	وإلا إذا (!c_درخت_equal (o1, o2))
	  أرجع خطأ;

	أرجع c_درخت_equal (درخت_عملوند (t1, 1), درخت_عملوند (t2, 1));
      }

    حالة COMPONENT_REF:
      إذا (درخت_عملوند (t1, 1) != درخت_عملوند (t2, 1))
	أرجع خطأ;
      أرجع c_درخت_equal (درخت_عملوند (t1, 0), درخت_عملوند (t2, 0));

    حالة PARM_DECL:
    حالة VAR_DECL:
    حالة CONST_DECL:
    حالة فیلد_DECL:
    حالة FUNCTION_DECL:
    حالة IDENTIFIER_گره:
    حالة SSA_NAME:
      أرجع خطأ;

    حالة درخت_VEC:
      {
	بیعلامت ix;
	إذا (درخت_VEC_درازی (t1) != درخت_VEC_درازی (t2))
	  أرجع خطأ;
	لكل (ix = درخت_VEC_درازی (t1); ix--;)
	  إذا (!c_درخت_equal (درخت_VEC_ELT (t1, ix),
			     درخت_VEC_ELT (t2, ix)))
	    أرجع خطأ;
	أرجع درست;
      }

    CASE_CONVERT:
      إذا (!comptypes (درخت_TYPE (t1), درخت_TYPE (t2)))
	أرجع خطأ;
      اكسر;

    افتراضي:
      اكسر;
    }

  بدل (درخت_کد_CLASS (code1))
    {
    حالة tcc_unary:
    حالة tcc_دودویی:
    حالة tcc_comparison:
    حالة tcc_عبارت:
    حالة tcc_vl_exp:
    حالة tcc_reference:
    حالة tcc_statement:
      {
	صحيح i, n = درخت_عملوند_درازی (t1);

	بدل (code1)
	  {
	  حالة PREINCREMENT_عبارت:
	  حالة PREDECREMENT_عبارت:
	  حالة POSTINCREMENT_عبارت:
	  حالة POSTDECREMENT_عبارت:
	    n = 1;
	    اكسر;
	  حالة ARRAY_REF:
	    n = 2;
	    اكسر;
	  افتراضي:
	    اكسر;
	  }

	إذا (درخت_کد_CLASS (code1) == tcc_vl_exp
	    && n != درخت_عملوند_درازی (t2))
	  أرجع خطأ;

	لكل (i = 0; i < n; ++i)
	  إذا (!c_درخت_equal (درخت_عملوند (t1, i), درخت_عملوند (t2, i)))
	    أرجع خطأ;

	أرجع درست;
      }

    حالة tcc_type:
      أرجع comptypes (t1, t2);
    افتراضي:
      gcc_unreachable ();
    }
}

/* Returns true when the function declaration FNDECL is implicit,
   introduced as a result of a call to an otherwise undeclared
   function, and false otherwise.  */

منطقي
c_decl_implicit (const_درخت fndecl)
{
  أرجع C_DECL_IMPLICIT (fndecl);
}
