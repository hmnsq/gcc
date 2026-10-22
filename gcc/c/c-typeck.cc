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
  ic_ټاکل,
  ic_init,
  ic_init_const,
  ic_return
};

/* The level of nesting inside "__alignof__".  */
صحيح دننه_alignof;

/* The level of nesting inside "sizeof".  */
صحيح دننه_sizeof;

/* The level of nesting inside "countof".  */
صحيح دننه_countof;

/* The level of nesting inside "typeof".  */
صحيح دننه_typeof;

/* The level of nesting inside "_Generic".  */
صحيح دننه_generic;

/* True when parsing OpenMP loop expressions.  */
منطقي c_دننه_omp_for;

/* True when parsing OpenMP map clause.  */
منطقي c_omp_array_section_p;

/* The argument of last parsed sizeof expression, only to be tested
   if expr.original_code == SIZEOF_EXPR.  */
ونه c_وروستی_sizeof_arg;
location_t c_وروستی_sizeof_loc;

/* Nonzero if we might need to print a "missing braces around
   initializer" message within this initializer.  */
ساكن صحيح وموندل_missing_braces;

ساكن منطقي require_constant_ارزښت;
ساكن منطقي require_constant_elements;
ساكن منطقي require_constexpr_ارزښت;

ساكن ونه qualify_type (ونه, ونه);
بنية comptypes_معلومات;
ساكن منطقي tagged_types_tu_compatible_p (const_ونه, const_ونه,
					  بنية comptypes_معلومات *);
ساكن منطقي comp_موخه_types (location_t, ونه, ونه);
ساكن منطقي function_types_compatible_p (const_ونه, const_ونه,
					 بنية comptypes_معلومات *);
ساكن منطقي type_lists_compatible_p (const_ونه, const_ونه,
				     بنية comptypes_معلومات *);
ساكن صحيح convert_arguments (location_t, vec<location_t>, ونه,
			      vec<ونه, va_gc> *, vec<ونه, va_gc> *, ونه,
			      ونه);
ساكن ونه اشاره_ګر_diff (location_t, ونه, ونه, ونه *);
ساكن ونه convert_for_assignment (location_t, location_t, ونه, ونه, ونه,
				    تعداد impl_conv, منطقي, ونه, ونه, صحيح,
				    صحيح = 0);
ساكن ونه valid_compound_بیان_initializer (ونه, ونه);
ساكن فراغ ټېل_string (ثابت حرف *);
ساكن فراغ ټېل_member_name (ونه);
ساكن صحيح spelling_اوږدتیا (فراغ);
ساكن حرف *print_spelling (حرف *);
ساكن فراغ warning_init (location_t, صحيح, ثابت حرف *);
ساكن ونه digest_init (location_t, ونه, ونه, ونه, ونه, منطقي, منطقي, منطقي,
			 منطقي, منطقي, منطقي);
ساكن فراغ output_init_element (location_t, ونه, ونه, منطقي, ونه, ونه, منطقي,
				 منطقي, بنية obstack *);
ساكن فراغ output_pending_init_elements (صحيح, بنية obstack *);
ساكن منطقي سېټ_designator (location_t, منطقي, بنية obstack *);
ساكن فراغ ټېل_range_ډېری (ونه, بنية obstack *);
ساكن فراغ جمع_کړه_pending_init (location_t, ونه, ونه, ونه, منطقي,
			      بنية obstack *);
ساكن فراغ سېټ_nonincremental_init (بنية obstack *);
ساكن فراغ سېټ_nonincremental_init_from_string (ونه, بنية obstack *);
ساكن ونه پیدا_کړه_init_member (ونه, بنية obstack *);
ساكن فراغ readonly_warning (ونه, تعداد lvalue_use);
ساكن صحيح lvalue_or_else (location_t, const_ونه, تعداد lvalue_use);
ساكن فراغ ریکارډ_maybe_کارول_شوی_decl (ونه, منطقي پته);
ساكن منطقي comptypes_دننی (const_ونه, const_ونه,
				بنية comptypes_معلومات *معلومات);
ساكن منطقي comptypes_check_for_مرکب (ونه t1, ونه t2);
ساكن منطقي handle_counted_by_p (ونه);
ساكن منطقي سر_array_vla_p (const_ونه type);


/* Return true if EXP is a null pointer constant, false otherwise.  */

منطقي
null_اشاره_ګر_constant_p (const_ونه بیان)
{
  /* This should really operate on c_expr structures, but they aren't
     yet available everywhere required.  */
  ونه type = ونه_TYPE (بیان);

  /* An integer constant expression with the value 0, such an expression
     cast to type void*, or the predefined constant nullptr, are a null
     pointer constant.  */
  إذا (بیان == nullptr_غوټه)
    أرجع ریښتیا;

  أرجع (ونه_کوډ (بیان) == INTEGER_CST
	  && !ونه_ډکېدنه (بیان)
	  && integer_zerop (بیان)
	  && (INTEGRAL_TYPE_P (type)
	      || (ونه_کوډ (type) == اشاره_ګر_TYPE
		  && VOID_TYPE_P (ونه_TYPE (type))
		  && TYPE_QUALS (ونه_TYPE (type)) == TYPE_UNQUALIFIED)));
}

/* EXPR may appear in an unevaluated part of an integer constant
   expression, but not in an evaluated part.  Wrap it in a
   C_MAYBE_CONST_EXPR, or mark it with TREE_OVERFLOW if it is just an
   INTEGER_CST and we cannot create a C_MAYBE_CONST_EXPR.  */

ساكن ونه
note_integer_operands (ونه بیان)
{
  ونه ret;
  إذا (ونه_کوډ (بیان) == INTEGER_CST && دننه_late_دوګونی_op)
    {
      ret = copy_غوټه (بیان);
      ونه_ډکېدنه (ret) = 1;
    }
  وإلا
    {
      ret = build2 (C_MAYBE_CONST_بیان, ونه_TYPE (بیان), NULL_ونه, بیان);
      C_MAYBE_CONST_بیان_INT_OPERANDS (ret) = 1;
    }
  أرجع ret;
}

/* Having checked whether EXPR may appear in an unevaluated part of an
   integer constant expression and found that it may, remove any
   C_MAYBE_CONST_EXPR noting this fact and return the resulting
   expression.  */

ساكن مضمن ونه
remove_c_maybe_const_بیان (ونه بیان)
{
  إذا (ونه_کوډ (بیان) == C_MAYBE_CONST_بیان)
    أرجع C_MAYBE_CONST_بیان_بیان (بیان);
  وإلا
    أرجع بیان;
}

/* This is a cache to hold if two types are seen.  */

بنية tagged_tu_کتل_شوی_cache {
  ثابت بنية tagged_tu_کتل_شوی_cache * بل;
  const_ونه t1;
  const_ونه t2;
};

/* Do `exp = require_complete_type (loc, exp);' to make sure exp
   does not have an incomplete type.  (That includes void types.)
   LOC is the location of the use.  */

ونه
require_complete_type (location_t loc, ونه ارزښت)
{
  ونه type = ونه_TYPE (ارزښت);

  إذا (error_عملوند_p (ارزښت))
    أرجع error_mark_غوټه;

  /* First, detect a valid value with a complete type.  */
  إذا (COMPLETE_TYPE_P (type))
    أرجع ارزښت;

  c_incomplete_type_error (loc, ارزښت, type);
  أرجع error_mark_غوټه;
}

/* Print an error message for invalid use of an incomplete type.
   VALUE is the expression that was used (or 0 if that isn't known)
   and TYPE is the type that was invalid.  LOC is the location for
   the error.  */

فراغ
c_incomplete_type_error (location_t loc, const_ونه ارزښت, const_ونه type)
{
  /* Avoid duplicate error message.  */
  إذا (ونه_کوډ (type) == ERROR_MARK)
    أرجع;

  إذا (ارزښت != NULL_ونه && (VAR_P (ارزښت) || ونه_کوډ (ارزښت) == PARM_DECL))
    error_at (loc, "%qD has an incomplete type %qT", ارزښت, type);
  وإلا
    {
    retry:
      /* We must print an error message.  Be clever about what it says.  */

      بدل (ونه_کوډ (type))
	{
	حالة ریکارډ_TYPE:
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
	      type = ونه_TYPE (type);
	      اذهب retry;
	    }
	  error_at (loc, "invalid use of array with unspecified bounds");
	  أرجع;

	افتراضي:
	  gcc_unreachable ();
	}

      إذا (ونه_کوډ (TYPE_NAME (type)) == IDENTIFIER_غوټه)
	error_at (loc, "invalid use of undefined type %qT", type);
      وإلا
	/* If this type has a typedef-name, the TYPE_NAME is a TYPE_DECL.  */
	error_at (loc, "invalid use of incomplete typedef %qT", type);
    }
}

/* Given a type, apply default promotions wrt unnamed function
   arguments and return the new type.  */

ونه
c_type_promotes_منزل (ونه type)
{
  ونه ret = NULL_ونه;

  إذا (TYPE_MAIN_VARIANT (type) == float_type_غوټه)
    ret = double_type_غوټه;
  وإلا إذا (c_promoting_integer_type_p (type))
    {
      /* Preserve unsignedness if not really getting any wider.  */
      إذا (TYPE_UNSIGNED (type)
	  && (TYPE_PRECISION (type) == TYPE_PRECISION (integer_type_غوټه)))
	ret = unsigned_type_غوټه;
      وإلا
	ret = integer_type_غوټه;
    }

  إذا (ret != NULL_ونه)
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
      أرجع ریښتیا;
    }
  وإلا إذا (targetm.addr_space.subset_p (as1, as2))
    {
      *common = as2;
      أرجع ریښتیا;
    }
  وإلا إذا (targetm.addr_space.subset_p (as2, as1))
    {
      *common = as1;
      أرجع ریښتیا;
    }
  وإلا
    أرجع خطأ;
}

/* Return a variant of TYPE which has all the type qualifiers of LIKE
   as well as those of TYPE.  */

ساكن ونه
qualify_type (ونه type, ونه like)
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
c_verify_type (ونه type)
{
  بدل (ونه_کوډ (type))
    {
    حالة اشاره_ګر_TYPE:
    حالة FUNCTION_TYPE:
    حالة ARRAY_TYPE:
      /* Pointer, array, functions are variably modified if and only if the
	 target, element, return type is variably modified.  */
      إذا (!TYPE_STRUCTURAL_EQUALITY_P (type)
	  && (C_TYPE_VARIABLY_MODIFIED (type)
	      != C_TYPE_VARIABLY_MODIFIED (ونه_TYPE (type))))
	أرجع خطأ;
      /* If the target type is structural equality, the type should also. */
      إذا (!TYPE_STRUCTURAL_EQUALITY_P (type)
	  && TYPE_STRUCTURAL_EQUALITY_P (ونه_TYPE (type)))
	أرجع خطأ;
    افتراضي:
       اكسر;
    }

  بدل (ونه_کوډ (type))
    {
    حالة اشاره_ګر_TYPE:
    حالة FUNCTION_TYPE:
      /* Pointer and functions can not have variable size.  */
      إذا (C_TYPE_VARIABLE_اندازه (type))
	أرجع خطأ;
      اكسر;
    حالة ARRAY_TYPE:
      /* An array has variable size if and only if it has a non-constant
	 dimensions or its element type has variable size.  */
      إذا ((C_TYPE_VARIABLE_اندازه (ونه_TYPE (type))
	   || سر_array_vla_p (type))
	  != C_TYPE_VARIABLE_اندازه (type))
	أرجع خطأ;
      /* If the element type or the array has variable size, then the
	 array has variable size and is variably modified.  */
      إذا (C_TYPE_VARIABLE_اندازه (ونه_TYPE (type))
	  || C_TYPE_VARIABLE_اندازه (type))
	{
	  إذا (!C_TYPE_VARIABLE_اندازه (type))
	    أرجع خطأ;
	  إذا (!C_TYPE_VARIABLY_MODIFIED (type))
	    أرجع خطأ;
	}

      /* va_list violates this, accept such types here.  */
      إذا (!COMPLETE_TYPE_P (ونه_TYPE (type)))
	أرجع ریښتیا;

      إذا (COMPLETE_TYPE_P (type))
	{
	  /* If the size is unknown, it can not be complete.  */
	  إذا (NULL_ونه == TYPE_DOMAIN (type))
	    أرجع خطأ;

	  /* Zero-length arrays must have size zero.  */
	  إذا (zero_اوږدتیا_array_type_p (type)
	      && !integer_zerop (TYPE_اندازه (type)))
	    أرجع خطأ;
	}
      وإلا
	{
	  /* If not complete but has a domain, it must be a FAM.  */
	  إذا (NULL_ونه != TYPE_DOMAIN (type)
	      && !flexible_array_member_type_p (type))
	    أرجع خطأ;
	}
    افتراضي:
      اكسر;
    }
  أرجع ریښتیا;
}

/* Propagate C_TYPE_VARIABLY_MODIFIED and C_TYPE_VARIABLE_SIZE
   from a base type to a newly built derived or qualified type.  */

ساكن ونه
c_سېټ_type_بټونه (ونه new_type, ونه old_type)
{
  gcc_checking_assert (c_verify_type (old_type));

  إذا (c_type_variably_modified_p (old_type))
    C_TYPE_VARIABLY_MODIFIED (new_type) = ریښتیا;

  إذا (ونه_کوډ (new_type) == ARRAY_TYPE && C_TYPE_VARIABLE_اندازه (old_type))
    {
      C_TYPE_VARIABLY_MODIFIED (new_type) = ریښتیا;
      C_TYPE_VARIABLE_اندازه (new_type) = ریښتیا;
    }
  أرجع new_type;
}

/* Build a pointer type using the default pointer mode.  */

ونه
c_build_اشاره_ګر_type (ونه منزل_type)
{
  addr_space_t as = منزل_type == error_mark_غوټه ? ADDR_SPACE_GENERIC
					       : TYPE_ADDR_SPACE (منزل_type);
  machine_ډېرپېښ اشاره_ګر_ډېرپېښ;

  إذا (as != ADDR_SPACE_GENERIC || c_default_اشاره_ګر_ډېرپېښ == VOIDmode)
    اشاره_ګر_ډېرپېښ = targetm.addr_space.اشاره_ګر_ډېرپېښ (as);
  وإلا
    اشاره_ګر_ډېرپېښ = c_default_اشاره_ګر_ډېرپېښ;

  أرجع c_build_اشاره_ګر_type_for_ډېرپېښ (منزل_type, اشاره_ګر_ډېرپېښ, خطأ);
}

/* Build a pointer type using the given mode.  */

ونه
c_build_اشاره_ګر_type_for_ډېرپېښ (ونه type, machine_ډېرپېښ ډېرپېښ, منطقي m)
{
  ونه ret = build_اشاره_ګر_type_for_ډېرپېښ (type, ډېرپېښ, m);
  أرجع c_سېټ_type_بټونه (ret, type);
}

/* Build a function type.  */

ونه
c_build_function_type (ونه type, ونه دلیلونه, منطقي no)
{
  ونه ret = build_function_type (type, دلیلونه, no);
  أرجع c_سېټ_type_بټونه (ret, type);
}

/* Build an array type.  This sets typeless storage as required
   by C2Y and C_TYPE_VARIABLY_MODIFIED and C_TYPE_VARIABLE_SIZE
   based on the element type and domain.  */

ونه
c_build_array_type (ونه type, ونه domain)
{
  صحيح type_quals = TYPE_QUALS (type);

  /* Identify typeless storage as introduced in C2Y
     and supported also in earlier language modes.  */
  منطقي typeless = (char_type_p (type) && !(type_quals & TYPE_QUAL_ATOMIC))
		  || (AGGREGATE_TYPE_P (type) && TYPE_TYPELESS_STORAGE (type));

  ونه ret = build_array_type (type, domain, typeless);

  إذا (سر_array_vla_p (ret))
    {
      C_TYPE_VARIABLE_اندازه (ret) = 1;
      C_TYPE_VARIABLY_MODIFIED (ret) = 1;
    }

  أرجع c_سېټ_type_بټونه (ret, type);
}

/* Build an array type of unspecified size.  */
ونه
c_build_array_type_unspecified (ونه type)
{
  ونه پاسنی = build2 (COMPOUND_بیان, ونه_TYPE (اندازه_zero_غوټه),
		       integer_zero_غوټه, اندازه_zero_غوټه);
  أرجع c_build_array_type (type, build_شاخص_type (پاسنی));
}

/* Build an array type of zero size.  */
ونه
c_build_array_type_zero_اندازه (ونه type)
{
  /* The GCC extension for zero-length arrays differs from
     ISO flexible array members in that sizeof yields
     zero.  */
  type = c_build_array_type (type, build_شاخص_type (NULL_ونه));
  type = build_distinct_type_copy (TYPE_MAIN_VARIANT (type));
  TYPE_اندازه (type) = bitsize_zero_غوټه;
  TYPE_اندازه_UNIT (type) = اندازه_zero_غوټه;
  سېټ_TYPE_STRUCTURAL_EQUALITY (type);
  أرجع type;
}

ونه
c_build_type_attribute_qual_variant (ونه type, ونه attrs, صحيح quals)
{
  ونه ret = build_type_attribute_qual_variant (type, attrs, quals);
  أرجع c_سېټ_type_بټونه (ret, type);
}

ونه
c_build_type_attribute_variant (ونه type, ونه attrs)
{
  أرجع c_build_type_attribute_qual_variant (type, attrs, TYPE_QUALS (type));
}

/* Reconstruct a complex derived type.  This is used to re-construct types
   with the vector attribute.  It is called via a langhook.  */

ونه
c_reconstruct_complex_type (ونه type, ونه bottom)
{
  ونه inner, outer;

  إذا (ونه_کوډ (type) == اشاره_ګر_TYPE)
    {
      inner = c_reconstruct_complex_type (ونه_TYPE (type), bottom);
      outer = c_build_اشاره_ګر_type_for_ډېرپېښ (inner, TYPE_ډېرپېښ (type),
					     TYPE_REF_CAN_ALIAS_ALL (type));
    }
  وإلا إذا (ونه_کوډ (type) == ARRAY_TYPE)
    {
      منطقي rso = TYPE_سرچپه_STORAGE_ترتیب (type);
      inner = c_reconstruct_complex_type (ونه_TYPE (type), bottom);
      outer = c_build_array_type (inner, TYPE_DOMAIN (type));
      إذا (rso)
	{
	  outer = build_distinct_type_copy (outer);
	  TYPE_سرچپه_STORAGE_ترتیب (outer) = 1;
	}

      gcc_checking_assert (C_TYPE_VARIABLE_اندازه (type)
			   == C_TYPE_VARIABLE_اندازه (outer));
    }
  وإلا إذا (ونه_کوډ (type) == FUNCTION_TYPE)
    {
      inner = c_reconstruct_complex_type (ونه_TYPE (type), bottom);
      outer = c_build_function_type (inner, TYPE_ARG_TYPES (type),
				     TYPE_NO_NAMED_دلیلونه_STDARG_P (type));
    }
  وإلا إذا (ونه_کوډ (type) == REFERENCE_TYPE
	   || ونه_کوډ (type) == دننه_واټن_TYPE)
    gcc_unreachable ();
  وإلا
    أرجع bottom;

  أرجع c_build_type_attribute_qual_variant (outer, TYPE_ځانګړتیاوې (type),
					      TYPE_QUALS (type));
}


/* Helper function for c_canonical_type.  Check whether FIELD
   contains a pointer to a structure or union with tag,
   possibly nested in other type derivations, and return the
   type of this nested structure or union.  */
ساكن ونه
ptr_منزل_tagged_member (ونه ډګر_2)
{
  gcc_assert (ډګر_DECL == ونه_کوډ (ډګر_2));
  ونه type = ونه_TYPE (ډګر_2);
  منطقي ptr_کتل_شوی = خطأ;
  طالما (ونه_کوډ (type) == ARRAY_TYPE
	 || ونه_کوډ (type) == FUNCTION_TYPE
	 || ونه_کوډ (type) == اشاره_ګر_TYPE)
    {
      إذا (ونه_کوډ (type) == اشاره_ګر_TYPE)
	ptr_کتل_شوی = ریښتیا;
      type = ونه_TYPE (type);
    }

  إذا (ptr_کتل_شوی
      && ریکارډ_OR_UNION_TYPE_P (type)
      && NULL_ونه != c_type_نښان (type))
    أرجع type;

  أرجع NULL_ونه;
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
ونه
c_type_canonical (ونه type)
{
  gcc_assert (ریکارډ_OR_UNION_TYPE_P (type));

  منطقي needs_mod = خطأ;
  لكل (ونه x = TYPE_FIELDS (type); x; x = DECL_CHAIN (x))
    {
      إذا (!ptr_منزل_tagged_member (x))
	استمر;
      needs_mod = ریښتیا;
      اكسر;
    }
  إذا (!needs_mod)
    أرجع type;

  /* Construct new version with such members replaced.  */
  ونه n = build_distinct_type_copy (type);
  ونه *fields = &TYPE_FIELDS (n);
  لكل (ونه x = TYPE_FIELDS (type); x; x = DECL_CHAIN (x))
    {
      ونه f = copy_غوټه (x);
      إذا (ونه m = ptr_منزل_tagged_member (x))
	{
	  ونه new_غوټه = make_غوټه (ونه_کوډ (m));
	  TYPE_NAME (new_غوټه) = TYPE_NAME (m);
	  سېټ_TYPE_STRUCTURAL_EQUALITY (new_غوټه);
	  new_غوټه = qualify_type (new_غوټه, m);
	  ونه_TYPE (f) = c_reconstruct_complex_type (ونه_TYPE (x),
						      new_غوټه);
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

ساكن ونه
c_build_functype_attribute_variant (ونه ntype, ونه otype, ونه attrs)
{
  إذا (!prototype_p (otype)
      && prototype_p (ntype)
      && lookup_attribute ("format", attrs))
    {
      warning_at (ننوت_location, OPT_Wattributes,
		  "%qs attribute can only be applied to variadic functions",
		  "format");
      attrs = remove_attribute ("format", attrs);
    }
  أرجع c_build_type_attribute_variant (ntype, attrs);

}

/* Given a type which could be a typedef name, make sure to return the
   original type.  See set_underlying_type. */
ساكن const_ونه
c_type_original (const_ونه t)
{
  /* It may even be a typedef of a typedef...
     In the case of compiler-created builtin structs the TYPE_DECL
     may be a dummy, with no DECL_ORIGINAL_TYPE.  Don't fault.  */
  طالما (TYPE_NAME (t)
	 && ونه_کوډ (TYPE_NAME (t)) == TYPE_DECL
	 && DECL_ORIGINAL_TYPE (TYPE_NAME (t)))
    t = DECL_ORIGINAL_TYPE (TYPE_NAME (t));
  أرجع t;
}

/* Return the tag for a tagged type.  */
ونه
c_type_نښان (const_ونه t)
{
  gcc_assert (ریکارډ_OR_UNION_TYPE_P (t) || ونه_کوډ (t) == ENUMERAL_TYPE);
  const_ونه orig = c_type_original (t);
  ونه name = TYPE_NAME (orig);
  إذا (!name)
    أرجع NULL_ونه;
  إذا (ونه_کوډ (name) == TYPE_DECL)
    {
      إذا (!DECL_NAME (name))
	أرجع NULL_ونه;
      name = DECL_NAME (name);
    }
  gcc_checking_assert (ونه_کوډ (name) == IDENTIFIER_غوټه);
  أرجع name;
}

/* Remove qualifiers but not atomic.  For arrays remove qualifiers
   on the element type but also do not remove atomic.  */
ساكن ونه
remove_qualifiers (ونه t)
{
  إذا (!t || t == error_mark_غوټه)
    أرجع t;
  أرجع TYPE_ATOMIC (strip_array_types (t))
	 ? c_build_qualified_type (TYPE_MAIN_VARIANT (t), TYPE_QUAL_ATOMIC)
	 : TYPE_MAIN_VARIANT (t);
}


/* Helper function for composite_type_internal.  Find a compatible type
   in a (transparent) union U compatible to T.  If found, return the
   type of the corresponding member.  Otherwise, return the union type U.  */
ساكن ونه
transparent_union_replacement (ونه u, ونه t)
{
  إذا (u == error_mark_غوټه || t == error_mark_غوټه
      || ونه_کوډ (u) != UNION_TYPE
      || !(TYPE_TRANSPARENT_AGGR (u) || TYPE_NAME (u) == NULL_ونه)
      || comptypes (u, t))
    أرجع u;

  لكل (ونه memb = TYPE_FIELDS (u); memb; memb = DECL_CHAIN (memb))
    {
      ونه m = remove_qualifiers (ونه_TYPE (memb));
      إذا (comptypes (m, t))
	{
	  pedwarn (ننوت_location, OPT_Wpedantic,
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
  ونه t1;
  ونه t2;
  ونه مرکب;
  بنية مرکب_cache* بل;
};

ونه
مرکب_type_دننی (ونه t1, ونه t2, ونه cond,
			 بنية مرکب_cache* cache)
{
  تعداد ونه_کوډ_2 code1;
  تعداد ونه_کوډ_2 code2;
  ونه ځانګړتیاوې;

  /* Save time if the two types are the same.  */

  إذا (t1 == t2) أرجع t1;

  /* If one type is nonsense, use the other.  */
  إذا (t1 == error_mark_غوټه)
    أرجع t2;
  إذا (t2 == error_mark_غوټه)
    أرجع t1;

  code1 = ونه_کوډ (t1);
  code2 = ونه_کوډ (t2);

  /* Merge the attributes.  */
  ځانګړتیاوې = targetm.یوځای_type_ځانګړتیاوې (t1, t2);

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
    حالة اشاره_ګر_TYPE:
      /* For two pointers, do this recursively on the target type.  */
      {
	gcc_checking_assert (TYPE_QUALS (t1) == TYPE_QUALS (t2));
	ونه موخه = مرکب_type_دننی (ونه_TYPE (t1), ونه_TYPE (t2),
					       cond, cache);
	ونه n = c_build_اشاره_ګر_type_for_ډېرپېښ (موخه, TYPE_ډېرپېښ (t1), خطأ);
	أرجع c_build_type_attribute_qual_variant (n, ځانګړتیاوې,
						    TYPE_QUALS (t2));
      }

    حالة ARRAY_TYPE:
      {
	ونه d1 = TYPE_DOMAIN (t1);
	ونه d2 = TYPE_DOMAIN (t2);

	/* We should not have any type quals on arrays at all.  */
	gcc_assert (!TYPE_QUALS_NO_ADDR_SPACE (t1)
		    && !TYPE_QUALS_NO_ADDR_SPACE (t2));

	منطقي d1_zero = zero_اوږدتیا_array_type_p (t1)
		       || flexible_array_member_type_p (t1);
	منطقي d2_zero = zero_اوږدتیا_array_type_p (t2)
		       || flexible_array_member_type_p (t2);

	منطقي d1_variable = سر_array_vla_p (t1);
	منطقي d2_variable = سر_array_vla_p (t2);

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

	ونه td;
	ونه elt = مرکب_type_دننی (ونه_TYPE (t1), ونه_TYPE (t2),
					    cond, cache);

	إذا (!use0)
	  {
	    /* Save space: see if the result is identical to one of the args.  */
	    إذا (elt == ونه_TYPE (t1) && use1)
	      أرجع c_build_type_attribute_variant (t1, ځانګړتیاوې);
	    إذا (elt == ونه_TYPE (t2) && use2)
	      أرجع c_build_type_attribute_variant (t2, ځانګړتیاوې);

	    إذا (elt == ونه_TYPE (t1) && !TYPE_DOMAIN (t2) && !TYPE_DOMAIN (t1))
	      أرجع c_build_type_attribute_variant (t1, ځانګړتیاوې);
	    إذا (elt == ونه_TYPE (t2) && !TYPE_DOMAIN (t2) && !TYPE_DOMAIN (t1))
	      أرجع c_build_type_attribute_variant (t2, ځانګړتیاوې);

	    td = TYPE_DOMAIN (use1 ? t1 : t2);
	  }
	وإلا
	  {
	    /* Not used in C.  */
	    gcc_assert (اندازه_zero_غوټه == TYPE_MIN_ارزښت (d1));
	    gcc_assert (اندازه_zero_غوټه == TYPE_MIN_ارزښت (d2));

	    ونه d = fold_build3_loc (UNKNOWN_LOCATION, COND_بیان, sizetype,
				      cond, TYPE_MAX_ارزښت (d1),
				      TYPE_MAX_ارزښت (d2));

	    td = build_شاخص_type (d);
	  }

	/* Merge the element types, and have a size if either arg has
	   one.  We may have qualifiers on the element types.  To set
	   up TYPE_MAIN_VARIANT correctly, we need to form the
	   composite of the unqualified types and add the qualifiers
	   back at the end.  */
	صحيح quals = TYPE_QUALS (strip_array_types (elt));
	ونه unqual_elt = c_build_qualified_type (elt, TYPE_UNQUALIFIED);

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
	أرجع c_build_type_attribute_variant (t1, ځانګړتیاوې);
      }

    حالة ریکارډ_TYPE:
    حالة UNION_TYPE:
      إذا (flag_isoc23 && !comptypes_same_p (t1, t2))
	{
	  /* Go to the original type to get the right tag.  */
	  ونه نښان = c_type_نښان (t1);

	  gcc_checking_assert (COMPLETE_TYPE_P (t1) && COMPLETE_TYPE_P (t2));
	  gcc_checking_assert (!نښان || comptypes (t1, t2));

	  /* If a composite type for these two types is already under
	     construction, return it.  */

	  لكل (بنية مرکب_cache *c = cache; c != عدم; c = c->بل)
	    إذا ((c->t1 == t1 && c->t2 == t2) || (c->t1 == t2 && c->t2 == t1))
	       أرجع c->مرکب;

	  /* Otherwise, create a new type node and link it into the cache.  */

	  ونه n = make_غوټه (code1);
	  سېټ_TYPE_STRUCTURAL_EQUALITY (n);
	  TYPE_NAME (n) = نښان;

	  بنية مرکب_cache cache2 = { t1, t2, n, cache };
	  cache = &cache2;

	  ونه f1 = TYPE_FIELDS (t1);
	  ونه f2 = TYPE_FIELDS (t2);
	  ونه fields = NULL_ونه;

	  لكل (ونه a = f1, b = f2; a && b;
	       a = DECL_CHAIN (a), b = DECL_CHAIN (b))
	    {
	      ونه ta = ونه_TYPE (a);
	      ونه tb = ونه_TYPE (b);

	      إذا (DECL_C_بټ_ډګر (a))
		{
		  ta = DECL_بټ_ډګر_TYPE (a);
		  tb = DECL_بټ_ډګر_TYPE (b);
		}

	      gcc_assert (DECL_NAME (a) == DECL_NAME (b));
	      gcc_checking_assert (!DECL_NAME (a) || comptypes (ta, tb));

	      ونه t = مرکب_type_دننی (ta, tb, cond, cache);
	      ونه f = build_decl (ننوت_location, ډګر_DECL, DECL_NAME (a), t);

	      DECL_PACKED (f) = DECL_PACKED (a);
	      سېټ_DECL_ALIGN (f, DECL_ALIGN (a));
	      DECL_ځانګړتیاوې (f) = DECL_ځانګړتیاوې (a);
	      C_DECL_VARIABLE_اندازه (f) = C_TYPE_VARIABLE_اندازه (t);

	      decl_ځانګړتیاوې (&f, DECL_ځانګړتیاوې (f), 0);

	      پای_decl (f, ننوت_location, عدم, عدم, عدم);

	      إذا (DECL_C_بټ_ډګر (a))
		{
		  /* This will be processed by finish_struct.  */
		  سېټ_DECL_C_بټ_ډګر (f);
		  DECL_INITIAL (f) = build_int_cst (integer_type_غوټه,
						    ونه_منزل_uhwi (DECL_اندازه (a)));
		  DECL_NONADDRESSABLE_P (f) = ریښتیا;
		  DECL_PADDING_P (f) = !DECL_NAME (a);
		}

	      DECL_CHAIN (f) = fields;
	      fields = f;
	    }

	  fields = nreverse (fields);

	  /* Setup the struct/union type.  Because we inherit all variably
	     modified components, we can ignore the size expression.  */
	  ونه بیان = NULL_ونه;

	  /* Set TYPE_STUB_DECL for debugging symbols.  */
	  TYPE_STUB_DECL (n) = pushdecl (build_decl (ننوت_location, TYPE_DECL,
						     NULL_ونه, n));

	  n = پای_struct (ننوت_location, n, fields, ځانګړتیاوې, عدم,
			     &بیان);

	  أرجع qualify_type (n, t1);
	}
      /* FALLTHRU */
    حالة ENUMERAL_TYPE:
      إذا (ځانګړتیاوې != عدم)
	{
	  /* Try harder not to create a new aggregate type.  */
	  إذا (attribute_list_equal (TYPE_ځانګړتیاوې (t1), ځانګړتیاوې))
	    أرجع t1;
	  إذا (attribute_list_equal (TYPE_ځانګړتیاوې (t2), ځانګړتیاوې))
	    أرجع t2;
	}
      أرجع c_build_type_attribute_variant (t1, ځانګړتیاوې);

    حالة FUNCTION_TYPE:
      /* Function types: prefer the one that specified arg types.
	 If both do, merge the arg types.  Also merge the return types.  */
      {
	ونه valtype = مرکب_type_دننی (ونه_TYPE (t1), ونه_TYPE (t2),
						cond, cache);
	ونه p1 = TYPE_ARG_TYPES (t1);
	ونه p2 = TYPE_ARG_TYPES (t2);

	/* Save space: see if the result is identical to one of the args.  */
	إذا (valtype == ونه_TYPE (t1) && !TYPE_ARG_TYPES (t2))
	  أرجع c_build_functype_attribute_variant (t1, t2, ځانګړتیاوې);
	إذا (valtype == ونه_TYPE (t2) && !TYPE_ARG_TYPES (t1))
	  أرجع c_build_functype_attribute_variant (t2, t1, ځانګړتیاوې);

	/* Simple way if one arg fails to specify argument types.  */
	إذا (TYPE_ARG_TYPES (t1) == NULL_ونه)
	  {
	    t1 = c_build_function_type (valtype, TYPE_ARG_TYPES (t2),
					TYPE_NO_NAMED_دلیلونه_STDARG_P (t2));
	    t1 = c_build_type_attribute_variant (t1, ځانګړتیاوې);
	    أرجع qualify_type (t1, t2);
	 }
	إذا (TYPE_ARG_TYPES (t2) == NULL_ونه)
	  {
	    t1 = c_build_function_type (valtype, TYPE_ARG_TYPES (t1),
					TYPE_NO_NAMED_دلیلونه_STDARG_P (t1));
	    t1 = c_build_type_attribute_variant (t1, ځانګړتیاوې);
	    أرجع qualify_type (t1, t2);
	  }

	/* If both args specify argument types, we must merge the two
	   lists, argument by argument.  */
	ونه newargs = NULL_ونه;
	ونه *endp = &newargs;

	لكل (; p1; p1 = ونه_CHAIN (p1), p2 = ونه_CHAIN (p2))
	  {
	    إذا (p1 == void_list_غوټه)
	      {
		*endp = void_list_غوټه;
		اكسر;
	      }
	    ونه mv1 = remove_qualifiers (ونه_ارزښت (p1));
	    ونه mv2 = remove_qualifiers (ونه_ارزښت (p2));

	    gcc_assert (mv1);
	    gcc_assert (mv2);

	    mv1 = transparent_union_replacement (mv1, mv2);
	    mv2 = transparent_union_replacement (mv2, mv1);

	    *endp = ونه_cons (NULL_ونه,
			       مرکب_type_دننی (mv1, mv2, cond, cache),
			       NULL_ونه);

	    endp = &ونه_CHAIN (*endp);
	  }

	t1 = c_build_function_type (valtype, newargs);
	t1 = qualify_type (t1, t2);
      }
      /* FALLTHRU */

    افتراضي:
      أرجع c_build_type_attribute_variant (t1, ځانګړتیاوې);
    }
}

ونه
مرکب_type_cond (ونه t1, ونه t2, ونه cond)
{
  gcc_checking_assert (comptypes_check_for_مرکب (t1, t2));

  بنية مرکب_cache cache = { };
  ونه n = مرکب_type_دننی (t1, t2, cond, &cache);

  gcc_checking_assert (comptypes_check_for_مرکب (n, t1));
  gcc_checking_assert (comptypes_check_for_مرکب (n, t2));
  أرجع n;
}


ونه
مرکب_type (ونه t1, ونه t2)
{
  أرجع مرکب_type_cond (t1, t2, NULL_ونه);
}

/* Return the type of a conditional expression between pointers to
   possibly differently qualified versions of compatible types.

   We assume that comp_target_types has already been done and returned
   true; if that isn't so, this may crash.  */

ساكن ونه
common_اشاره_ګر_type (ونه t1, ونه t2, ونه cond)
{
  ونه ځانګړتیاوې;
  بینښه موخه_quals;
  addr_space_t as1, as2, as_common;
  صحيح quals1, quals2;

  /* Save time if the two types are the same.  */

  إذا (t1 == t2) أرجع t1;

  /* If one type is nonsense, use the other.  */
  إذا (t1 == error_mark_غوټه)
    أرجع t2;
  إذا (t2 == error_mark_غوټه)
    أرجع t1;

  gcc_assert (ونه_کوډ (t1) == اشاره_ګر_TYPE
	      && ونه_کوډ (t2) == اشاره_ګر_TYPE);

  /* Merge the attributes.  */
  ځانګړتیاوې = targetm.یوځای_type_ځانګړتیاوې (t1, t2);

  /* Find the composite type of the target types, and combine the
     qualifiers of the two types' targets.  */
  ونه pointed_منزل_1 = ونه_TYPE (t1);
  ونه pointed_منزل_2 = ونه_TYPE (t2);
  ونه موخه = مرکب_type_cond (TYPE_MAIN_VARIANT (pointed_منزل_1),
				     TYPE_MAIN_VARIANT (pointed_منزل_2), cond);

  /* Strip array types to get correct qualifier for pointers to arrays */
  quals1 = TYPE_QUALS_NO_ADDR_SPACE (strip_array_types (pointed_منزل_1));
  quals2 = TYPE_QUALS_NO_ADDR_SPACE (strip_array_types (pointed_منزل_2));

  /* For function types do not merge const qualifiers, but drop them
     if used inconsistently.  The middle-end uses these to mark const
     and noreturn functions.  */
  إذا (ونه_کوډ (pointed_منزل_1) == FUNCTION_TYPE)
    موخه_quals = (quals1 & quals2);
  وإلا
    موخه_quals = (quals1 | quals2);

  /* If the two named address spaces are different, determine the common
     superset address space.  This is guaranteed to exist due to the
     assumption that comp_target_type returned true.  */
  as1 = TYPE_ADDR_SPACE (pointed_منزل_1);
  as2 = TYPE_ADDR_SPACE (pointed_منزل_2);
  إذا (!addr_space_superset (as1, as2, &as_common))
    gcc_unreachable ();

  موخه_quals |= ENCODE_QUAL_ADDR_SPACE (as_common);

  t1 = c_build_اشاره_ګر_type (c_build_qualified_type (موخه, موخه_quals));
  أرجع c_build_type_attribute_variant (t1, ځانګړتیاوې);
}

/* Return the common type for two arithmetic types under the usual
   arithmetic conversions.  The default conversions have already been
   applied, and enumerated types converted to their compatible integer
   types.  The resulting type is unqualified and has no attributes.

   This is the type for the result of most arithmetic operations
   if the operands have the given two types.  */

ساكن ونه
c_common_type (ونه t1, ونه t2)
{
  تعداد ونه_کوډ_2 code1;
  تعداد ونه_کوډ_2 code2;

  /* If one type is nonsense, use the other.  */
  إذا (t1 == error_mark_غوټه)
    أرجع t2;
  إذا (t2 == error_mark_غوټه)
    أرجع t1;

  إذا (TYPE_QUALS (t1) != TYPE_UNQUALIFIED)
    t1 = TYPE_MAIN_VARIANT (t1);

  إذا (TYPE_QUALS (t2) != TYPE_UNQUALIFIED)
    t2 = TYPE_MAIN_VARIANT (t2);

  إذا (TYPE_ځانګړتیاوې (t1) != NULL_ونه)
    {
      ونه attrs = affects_type_بې_اغېزه_عنصر_ځانګړتیاوې (TYPE_ځانګړتیاوې (t1));
      t1 = c_build_type_attribute_variant (t1, attrs);
    }

  إذا (TYPE_ځانګړتیاوې (t2) != NULL_ونه)
    {
      ونه attrs = affects_type_بې_اغېزه_عنصر_ځانګړتیاوې (TYPE_ځانګړتیاوې (t2));
      t2 = c_build_type_attribute_variant (t2, attrs);
    }

  /* Save time if the two types are the same.  */

  إذا (t1 == t2) أرجع t1;

  code1 = ونه_کوډ (t1);
  code2 = ونه_کوډ (t2);

  gcc_assert (code1 == ویکټور_TYPE || code1 == COMPLEX_TYPE
	      || code1 == FIXED_ټکی_TYPE || code1 == REAL_TYPE
	      || code1 == INTEGER_TYPE || code1 == BITINT_TYPE);
  gcc_assert (code2 == ویکټور_TYPE || code2 == COMPLEX_TYPE
	      || code2 == FIXED_ټکی_TYPE || code2 == REAL_TYPE
	      || code2 == INTEGER_TYPE || code2 == BITINT_TYPE);

  /* When one operand is a decimal float type, the other operand cannot be
     a generic float type or a complex type.  We also disallow vector types
     here.  */
  إذا ((DECIMAL_FLOAT_TYPE_P (t1) || DECIMAL_FLOAT_TYPE_P (t2))
      && !(DECIMAL_FLOAT_TYPE_P (t1) && DECIMAL_FLOAT_TYPE_P (t2)))
    {
      إذا (code1 == ویکټور_TYPE || code2 == ویکټور_TYPE)
	{
	  error ("cannot mix operands of decimal floating and vector types");
	  أرجع error_mark_غوټه;
	}
      إذا (code1 == COMPLEX_TYPE || code2 == COMPLEX_TYPE)
	{
	  error ("cannot mix operands of decimal floating and complex types");
	  أرجع error_mark_غوټه;
	}
      إذا (code1 == REAL_TYPE && code2 == REAL_TYPE)
	{
	  error ("cannot mix operands of decimal floating "
		 "and other floating types");
	  أرجع error_mark_غوټه;
	}
    }

  /* If one type is a vector type, return that type.  (How the usual
     arithmetic conversions apply to the vector types extension is not
     precisely specified.)  */
  إذا (code1 == ویکټور_TYPE)
    أرجع t1;

  إذا (code2 == ویکټور_TYPE)
    أرجع t2;

  /* If one type is complex, form the common type of the non-complex
     components, then make that complex.  Use T1 or T2 if it is the
     required type.  */
  إذا (code1 == COMPLEX_TYPE || code2 == COMPLEX_TYPE)
    {
      ونه subtype1 = code1 == COMPLEX_TYPE ? ونه_TYPE (t1) : t1;
      ونه subtype2 = code2 == COMPLEX_TYPE ? ونه_TYPE (t2) : t2;
      ونه subtype = c_common_type (subtype1, subtype2);

      إذا (code1 == COMPLEX_TYPE && ونه_TYPE (t1) == subtype)
	أرجع t1;
      وإلا إذا (code2 == COMPLEX_TYPE && ونه_TYPE (t2) == subtype)
	أرجع t2;
      وإلا إذا (ونه_کوډ (subtype) == BITINT_TYPE)
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
      إذا (TYPE_MAIN_VARIANT (t1) == dfloat128_type_غوټه
	  || TYPE_MAIN_VARIANT (t2) == dfloat128_type_غوټه)
	أرجع dfloat128_type_غوټه;
      /* And prefer _Decimal128 over _Decimal64x which has in GCC's
	 implementation the same mode.  */
      وإلا إذا (TYPE_MAIN_VARIANT (t1) == dfloat64x_type_غوټه
	       || TYPE_MAIN_VARIANT (t2) == dfloat64x_type_غوټه)
	أرجع dfloat64x_type_غوټه;
      وإلا إذا (TYPE_MAIN_VARIANT (t1) == dfloat64_type_غوټه
	       || TYPE_MAIN_VARIANT (t2) == dfloat64_type_غوټه)
	أرجع dfloat64_type_غوټه;
      وإلا إذا (TYPE_MAIN_VARIANT (t1) == dfloat32_type_غوټه
	       || TYPE_MAIN_VARIANT (t2) == dfloat32_type_غوټه)
	أرجع dfloat32_type_غوټه;
    }

  /* Deal with fixed-point types.  */
  إذا (code1 == FIXED_ټکی_TYPE || code2 == FIXED_ټکی_TYPE)
    {
      بینښه صحيح unsignedp = 0, satp = 0;
      scalar_ډېرپېښ m1, m2;
      بینښه صحيح fbit1, ibit1, fbit2, ibit2, max_fbit, max_ibit;

      m1 = SCALAR_TYPE_ډېرپېښ (t1);
      m2 = SCALAR_TYPE_ډېرپېښ (t2);

      /* If one input type is saturating, the result type is saturating.  */
      إذا (TYPE_SATURATING (t1) || TYPE_SATURATING (t2))
	satp = 1;

      /* If both fixed-point types are unsigned, the result type is unsigned.
	 When mixing fixed-point and integer types, follow the sign of the
	 fixed-point type.
	 Otherwise, the result type is signed.  */
      إذا ((TYPE_UNSIGNED (t1) && TYPE_UNSIGNED (t2)
	   && code1 == FIXED_ټکی_TYPE && code2 == FIXED_ټکی_TYPE)
	  || (code1 == FIXED_ټکی_TYPE && code2 != FIXED_ټکی_TYPE
	      && TYPE_UNSIGNED (t1))
	  || (code1 != FIXED_ټکی_TYPE && code2 == FIXED_ټکی_TYPE
	      && TYPE_UNSIGNED (t2)))
	unsignedp = 1;

      /* The result type is signed.  */
      إذا (unsignedp == 0)
	{
	  /* If the input type is unsigned, we need to convert to the
	     signed type.  */
	  إذا (code1 == FIXED_ټکی_TYPE && TYPE_UNSIGNED (t1))
	    {
	      تعداد ډېرپېښ_class mclass = (تعداد ډېرپېښ_class) 0;
	      إذا (GET_ډېرپېښ_CLASS (m1) == ډېرپېښ_UFRACT)
		mclass = ډېرپېښ_FRACT;
	      وإلا إذا (GET_ډېرپېښ_CLASS (m1) == ډېرپېښ_UACCUM)
		mclass = ډېرپېښ_ACCUM;
	      وإلا
		gcc_unreachable ();
	      m1 = as_a <scalar_ډېرپېښ>
		(ډېرپېښ_for_اندازه (GET_ډېرپېښ_PRECISION (m1), mclass, 0));
	    }
	  إذا (code2 == FIXED_ټکی_TYPE && TYPE_UNSIGNED (t2))
	    {
	      تعداد ډېرپېښ_class mclass = (تعداد ډېرپېښ_class) 0;
	      إذا (GET_ډېرپېښ_CLASS (m2) == ډېرپېښ_UFRACT)
		mclass = ډېرپېښ_FRACT;
	      وإلا إذا (GET_ډېرپېښ_CLASS (m2) == ډېرپېښ_UACCUM)
		mclass = ډېرپېښ_ACCUM;
	      وإلا
		gcc_unreachable ();
	      m2 = as_a <scalar_ډېرپېښ>
		(ډېرپېښ_for_اندازه (GET_ډېرپېښ_PRECISION (m2), mclass, 0));
	    }
	}

      إذا (code1 == FIXED_ټکی_TYPE)
	{
	  fbit1 = GET_ډېرپېښ_FBIT (m1);
	  ibit1 = GET_ډېرپېښ_IBIT (m1);
	}
      وإلا
	{
	  fbit1 = 0;
	  /* Signed integers need to subtract one sign bit.  */
	  ibit1 = TYPE_PRECISION (t1) - (!TYPE_UNSIGNED (t1));
	}

      إذا (code2 == FIXED_ټکی_TYPE)
	{
	  fbit2 = GET_ډېرپېښ_FBIT (m2);
	  ibit2 = GET_ډېرپېښ_IBIT (m2);
	}
      وإلا
	{
	  fbit2 = 0;
	  /* Signed integers need to subtract one sign bit.  */
	  ibit2 = TYPE_PRECISION (t2) - (!TYPE_UNSIGNED (t2));
	}

      max_ibit = ibit1 >= ibit2 ?  ibit1 : ibit2;
      max_fbit = fbit1 >= fbit2 ?  fbit1 : fbit2;
      أرجع c_common_fixed_ټکی_type_for_اندازه (max_ibit, max_fbit, unsignedp,
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

  إذا (TYPE_MAIN_VARIANT (t1) == long_long_unsigned_type_غوټه
      || TYPE_MAIN_VARIANT (t2) == long_long_unsigned_type_غوټه)
    أرجع long_long_unsigned_type_غوټه;

  إذا (TYPE_MAIN_VARIANT (t1) == long_long_integer_type_غوټه
      || TYPE_MAIN_VARIANT (t2) == long_long_integer_type_غوټه)
    {
      إذا (TYPE_UNSIGNED (t1) || TYPE_UNSIGNED (t2))
	أرجع long_long_unsigned_type_غوټه;
      وإلا
	أرجع long_long_integer_type_غوټه;
    }

  إذا (TYPE_MAIN_VARIANT (t1) == long_unsigned_type_غوټه
      || TYPE_MAIN_VARIANT (t2) == long_unsigned_type_غوټه)
    أرجع long_unsigned_type_غوټه;

  إذا (TYPE_MAIN_VARIANT (t1) == long_integer_type_غوټه
      || TYPE_MAIN_VARIANT (t2) == long_integer_type_غوټه)
    {
      /* But preserve unsignedness from the other type,
	 since long cannot hold all the values of an unsigned int.  */
      إذا (TYPE_UNSIGNED (t1) || TYPE_UNSIGNED (t2))
	أرجع long_unsigned_type_غوټه;
      وإلا
	أرجع long_integer_type_غوټه;
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
  ونه mv1 = TYPE_MAIN_VARIANT (t1);
  ونه mv2 = TYPE_MAIN_VARIANT (t2);

  لكل (صحيح i = عدد_FLOATN_TYPES - 1; i >= 0; i--)
    إذا (mv1 == FLOATN_TYPE_غوټه (i) || mv2 == FLOATN_TYPE_غوټه (i))
      أرجع FLOATN_TYPE_غوټه (i);

  /* Likewise, prefer long double to double even if same size.  */
  إذا (mv1 == long_double_type_غوټه || mv2 == long_double_type_غوټه)
    أرجع long_double_type_غوټه;

  /* Likewise, prefer double to float even if same size.
     We got a couple of embedded targets with 32 bit doubles, and the
     pdp11 might have 64 bit floats.  */
  إذا (mv1 == double_type_غوټه || mv2 == double_type_غوټه)
    أرجع double_type_غوټه;

  إذا (mv1 == float_type_غوټه || mv2 == float_type_غوټه)
    أرجع float_type_غوټه;

  لكل (صحيح i = عدد_FLOATNX_TYPES - 1; i >= 0; i--)
    إذا (mv1 == FLOATNX_TYPE_غوټه (i) || mv2 == FLOATNX_TYPE_غوټه (i))
      أرجع FLOATNX_TYPE_غوټه (i);

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
ونه
common_type (ونه t1, ونه t2)
{
  إذا (ونه_کوډ (t1) == ENUMERAL_TYPE)
    t1 = ENUM_UNDERLYING_TYPE (t1);
  إذا (ونه_کوډ (t2) == ENUMERAL_TYPE)
    t2 = ENUM_UNDERLYING_TYPE (t2);

  /* If both types are BOOLEAN_TYPE, then return boolean_type_node.  */
  إذا (ونه_کوډ (t1) == BOOLEAN_TYPE
      && ونه_کوډ (t2) == BOOLEAN_TYPE)
    أرجع boolean_type_غوټه;

  /* If either type is BOOLEAN_TYPE, then return the other.  */
  إذا (ونه_کوډ (t1) == BOOLEAN_TYPE)
    أرجع t2;
  إذا (ونه_کوډ (t2) == BOOLEAN_TYPE)
    أرجع t1;

  أرجع c_common_type (t1, t2);
}



/* Helper function for comptypes.  For two compatible types, return 1
   if they pass consistency checks.  In particular we test that
   TYPE_CANONICAL is set correctly, i.e. the two types can alias.  */

ساكن منطقي
comptypes_verify (ونه type1, ونه type2)
{
  إذا (type1 == type2 || !type1 || !type2
      || ونه_کوډ (type1) == ERROR_MARK || ونه_کوډ (type2) == ERROR_MARK)
    أرجع ریښتیا;

  gcc_checking_assert (c_verify_type (type1));
  gcc_checking_assert (c_verify_type (type2));

  إذا (TYPE_CANONICAL (type1) != TYPE_CANONICAL (type2)
      && !TYPE_STRUCTURAL_EQUALITY_P (type1)
      && !TYPE_STRUCTURAL_EQUALITY_P (type2))
    {
      /* FIXME: check other types. */
      إذا (ریکارډ_OR_UNION_TYPE_P (type1)
	  || ونه_کوډ (type1) == ENUMERAL_TYPE
	  || ونه_کوډ (type2) == ENUMERAL_TYPE)
	أرجع خطأ;
    }
  أرجع ریښتیا;
}

بنية comptypes_معلومات {

  /* output */
  منطقي enum_and_int_p;
  منطقي different_types_p;
  منطقي warning_needed;

  /* context */
  منطقي anon_ډګر;
  منطقي pointedto;

  /* configuration */
  منطقي equiv;
  منطقي ignore_promoting_دلیلونه;

  ثابت بنية tagged_tu_کتل_شوی_cache* cache;
};


/* Helper function for composite_type.  This function ignores when the
   function type of an old-style declaration is incompatible with a type
   of a declaration with prototype because some are arguments are not
   self-promoting.  This is ignored only for function types but not
   ignored in a nested context.  */

ساكن منطقي
comptypes_check_for_مرکب (ونه t1, ونه t2)
{
  بنية comptypes_معلومات معلومات = { };
  معلومات.ignore_promoting_دلیلونه = FUNCTION_TYPE == ونه_کوډ (t1);
  أرجع comptypes_دننی (t1, t2, &معلومات);
}


/* C implementation of compatible_types_for_indirection_note_p.  */

منطقي
compatible_types_for_indirection_note_p (ونه type1, ونه type2)
{
  أرجع comptypes (type1, type2);
}

/* Return true if TYPE1 and TYPE2 are compatible types for assignment
   or various other operations.  */

منطقي
comptypes (ونه type1, ونه type2)
{
  بنية comptypes_معلومات معلومات = { };
  منطقي ret = comptypes_دننی (type1, type2, &معلومات);

  gcc_checking_assert (!ret || comptypes_verify (type1, type2));

  أرجع ret;
}


/* Like comptypes, but it returns non-zero only for identical
   types.  */

منطقي
comptypes_same_p (ونه type1, ونه type2)
{
  بنية comptypes_معلومات معلومات = { };
  منطقي ret = comptypes_دننی (type1, type2, &معلومات);

  gcc_checking_assert (!ret || comptypes_verify (type1, type2));

  إذا (معلومات.different_types_p)
    أرجع خطأ;

  أرجع ret;
}


/* Like comptypes, but if it returns true because enum and int are
   compatible, it sets *ENUM_AND_INT_P to true.  */

منطقي
comptypes_check_enum_int (ونه type1, ونه type2, منطقي *enum_and_int_p)
{
  بنية comptypes_معلومات معلومات = { };
  منطقي ret = comptypes_دننی (type1, type2, &معلومات);
  *enum_and_int_p = معلومات.enum_and_int_p;

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
comptypes_equiv_p (ونه type1, ونه type2)
{
  بنية comptypes_معلومات معلومات = { };
  معلومات.equiv = ریښتیا;
  منطقي ret = comptypes_دننی (type1, type2, &معلومات);

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
comptypes_دننی (const_ونه type1, const_ونه type2,
		    بنية comptypes_معلومات *معلومات)
{
  const_ونه t1 = type1;
  const_ونه t2 = type2;

  /* Suppress errors caused by previously reported errors.  */

  إذا (t1 == t2 || !t1 || !t2
      || ونه_کوډ (t1) == ERROR_MARK || ونه_کوډ (t2) == ERROR_MARK)
    أرجع ریښتیا;

  /* Qualifiers must match. C99 6.7.3p9 */

  إذا (TYPE_QUALS (t1) != TYPE_QUALS (t2))
    أرجع خطأ;

  /* Enumerated types are compatible with integer types, but this is
     not transitive: two enumerated types in the same translation unit
     are compatible with each other only if they are the same type.  */

  إذا (ونه_کوډ (t1) == ENUMERAL_TYPE
      && COMPLETE_TYPE_P (t1)
      && ونه_کوډ (t2) != ENUMERAL_TYPE)
    {
      t1 = ENUM_UNDERLYING_TYPE (t1);
      إذا (ونه_کوډ (t2) != VOID_TYPE)
	{
	  معلومات->enum_and_int_p = ریښتیا;
	  معلومات->different_types_p = ریښتیا;
	}
    }
  وإلا إذا (ونه_کوډ (t2) == ENUMERAL_TYPE
	   && COMPLETE_TYPE_P (t2)
	   && ونه_کوډ (t1) != ENUMERAL_TYPE)
    {
      t2 = ENUM_UNDERLYING_TYPE (t2);
      إذا (ونه_کوډ (t1) != VOID_TYPE)
	{
	  معلومات->enum_and_int_p = ریښتیا;
	  معلومات->different_types_p = ریښتیا;
	}
    }

  إذا (t1 == t2)
    أرجع ریښتیا;

  /* Different classes of types can't be compatible.  */

  إذا (ونه_کوډ (t1) != ونه_کوډ (t2))
    أرجع خطأ;

  /* Allow for two different type nodes which have essentially the same
     definition.  Note that we already checked for equality of the type
     qualifiers (just above).  */

  إذا (ونه_کوډ (t1) != ARRAY_TYPE
      && TYPE_MAIN_VARIANT (t1) == TYPE_MAIN_VARIANT (t2))
    أرجع ریښتیا;

  صحيح attrval;

  /* 1 if no need for warning yet, 2 if warning cause has been seen.  */
  إذا (!(attrval = comp_type_ځانګړتیاوې (t1, t2)))
    أرجع خطأ;

  إذا (2 == attrval)
    معلومات->warning_needed = ریښتیا;

  بدل (ونه_کوډ (t1))
    {
    حالة INTEGER_TYPE:
    حالة FIXED_ټکی_TYPE:
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

    حالة اشاره_ګر_TYPE:
      /* Do not remove mode information.  */
      إذا (TYPE_ډېرپېښ (t1) != TYPE_ډېرپېښ (t2))
	أرجع خطأ;
      معلومات->pointedto = ریښتیا;
      أرجع comptypes_دننی (ونه_TYPE (t1), ونه_TYPE (t2), معلومات);

    حالة FUNCTION_TYPE:
      أرجع function_types_compatible_p (t1, t2, معلومات);

    حالة ARRAY_TYPE:
      {
	ونه d1 = TYPE_DOMAIN (t1);
	ونه d2 = TYPE_DOMAIN (t2);

	/* Target types must match incl. qualifiers.  */
	إذا (!comptypes_دننی (ونه_TYPE (t1), ونه_TYPE (t2), معلومات))
	  أرجع خطأ;

	إذا ((d1 == NULL_ونه) != (d2 == NULL_ونه))
	  معلومات->different_types_p = ریښتیا;
	/* Ignore size mismatches when forming equivalence classes.  */
	إذا (معلومات->equiv)
	  أرجع ریښتیا;
	/* Sizes must match unless one is missing or variable.  */
	إذا (d1 == NULL_ونه || d2 == NULL_ونه || d1 == d2)
	  أرجع ریښتیا;

	منطقي d1_variable = سر_array_vla_p (t1);
	منطقي d2_variable = سر_array_vla_p (t2);

	إذا (d1_variable != d2_variable)
	  معلومات->different_types_p = ریښتیا;
	إذا (d1_variable || d2_variable)
	  أرجع ریښتیا;

	منطقي d1_zero = zero_اوږدتیا_array_type_p (t1)
		       || flexible_array_member_type_p (t1);

	منطقي d2_zero = zero_اوږدتیا_array_type_p (t2)
		       || flexible_array_member_type_p (t2);

	إذا (d1_zero && d2_zero)
	  أرجع ریښتیا;
	إذا (d1_zero || d2_zero)
	  أرجع خطأ;

	إذا (!ونه_int_cst_equal (TYPE_MIN_ارزښت (d1), TYPE_MIN_ارزښت (d2))
	    || !ونه_int_cst_equal (TYPE_MAX_ارزښت (d1), TYPE_MAX_ارزښت (d2)))
	  أرجع خطأ;

	أرجع ریښتیا;
      }

    حالة ENUMERAL_TYPE:
    حالة ریکارډ_TYPE:
    حالة UNION_TYPE:

      إذا (!flag_isoc23)
	أرجع خطأ;

      أرجع tagged_types_tu_compatible_p (t1, t2, معلومات);

    حالة ویکټور_TYPE:
      أرجع معلوم_eq (TYPE_ویکټور_SUBPARTS (t1), TYPE_ویکټور_SUBPARTS (t2))
	     && comptypes_دننی (ونه_TYPE (t1), ونه_TYPE (t2), معلومات);

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
comp_موخه_types (location_t location, ونه ttl, ونه ttr)
{
  ونه mvl = ونه_TYPE (ttl);
  ونه mvr = ونه_TYPE (ttr);
  addr_space_t asl = TYPE_ADDR_SPACE (mvl);
  addr_space_t asr = TYPE_ADDR_SPACE (mvr);
  addr_space_t as_common;

  /* Fail if pointers point to incompatible address spaces.  */
  إذا (!addr_space_superset (asl, asr, &as_common))
    أرجع 0;

  /* Qualifiers on element types of array types that are
     pointer targets are also removed.  */
  بنية comptypes_معلومات معلومات = { };
  إذا (!comptypes_دننی (remove_qualifiers (mvl),
			   remove_qualifiers (mvr), &معلومات))
    أرجع خطأ;

  /* For pedantic use comptypes on arrays before removing
     qualifiers on the element type. */
  إذا (ونه_کوډ (mvl) == ARRAY_TYPE
      && ونه_کوډ (mvr) == ARRAY_TYPE
      && !comptypes (mvl, mvr))
    pedwarn_c11 (location, OPT_Wpedantic, "invalid use of pointers to arrays "
					  "with different qualifiers in ISO C "
					  "before C23");

  إذا (معلومات.warning_needed)
    pedwarn (location, OPT_Wpedantic, "types are not quite compatible");

  إذا (معلومات.enum_and_int_p && warn_cxx_compat)
    warning_at (location, OPT_Wc___compat,
		"pointer target types incompatible in C++");

  أرجع ریښتیا;
}

/* Subroutines of `comptypes'.  */

/* Return true if two 'struct', 'union', or 'enum' types T1 and T2 are
   compatible.  The two types are not the same (which has been
   checked earlier in comptypes_internal).  */

ساكن منطقي
tagged_types_tu_compatible_p (const_ونه t1, const_ونه t2,
			      بنية comptypes_معلومات *معلومات)
{
  ونه s1, s2;

  إذا (c_type_نښان (t1) != c_type_نښان (t2))
    أرجع خطأ;

  /* When forming equivalence classes for TYPE_CANONICAL in C23, we treat
     structs with the same tag as equivalent, but only when they are targets
     of pointers inside other structs.  */
  إذا (معلومات->equiv && معلومات->pointedto && NULL_ونه != c_type_نښان (t1))
    أرجع ریښتیا;

  /* Different types without tag are incompatible except as an anonymous
     field or when forming equivalence classes for TYPE_CANONICAL.  */
  إذا (!معلومات->anon_ډګر && !معلومات->equiv && NULL_ونه == c_type_نښان (t1))
    أرجع خطأ;

  إذا (!معلومات->anon_ډګر && TYPE_STUB_DECL (t1) != TYPE_STUB_DECL (t2))
    معلومات->different_types_p = ریښتیا;

  /* Incomplete types are incompatible inside a TU.  */
  إذا (TYPE_اندازه (t1) == عدم || TYPE_اندازه (t2) == عدم)
    أرجع خطأ;

  إذا (ENUMERAL_TYPE != ونه_کوډ (t1)
      && (TYPE_سرچپه_STORAGE_ترتیب (t1)
	  != TYPE_سرچپه_STORAGE_ترتیب (t2)))
    أرجع خطأ;

  إذا (TYPE_USER_ALIGN (t1) != TYPE_USER_ALIGN (t2))
    معلومات->different_types_p = ریښتیا;

  /* For types already being looked at in some active
     invocation of this function, assume compatibility.
     The cache is built as a linked list on the stack
     with the head of the list passed downwards.  */
  لكل (ثابت بنية tagged_tu_کتل_شوی_cache *t = معلومات->cache;
       t != عدم; t = t->بل)
    إذا (t->t1 == t1 && t->t2 == t2)
      أرجع ریښتیا;

  ثابت بنية tagged_tu_کتل_شوی_cache ثبت = { معلومات->cache, t1, t2 };

  بدل (ونه_کوډ (t1))
    {
    حالة ENUMERAL_TYPE:
      {
	إذا (!comptypes (ENUM_UNDERLYING_TYPE (t1), ENUM_UNDERLYING_TYPE (t2)))
	  أرجع خطأ;

	/* Speed up the case where the type values are in the same order.  */
	ونه tv1 = TYPE_ارزښتونه (t1);
	ونه tv2 = TYPE_ارزښتونه (t2);

	إذا (tv1 == tv2)
	  أرجع ریښتیا;

	لكل (;tv1 && tv2; tv1 = ونه_CHAIN (tv1), tv2 = ونه_CHAIN (tv2))
	  {
	    إذا (ونه_PURPOSE (tv1) != ونه_PURPOSE (tv2))
	      اكسر;

	    إذا (simple_cst_equal (DECL_INITIAL (ونه_ارزښت (tv1)),
				  DECL_INITIAL (ونه_ارزښت (tv2))) != 1)
	      اكسر;
	  }

	إذا (tv1 == NULL_ونه && tv2 == NULL_ونه)
	  أرجع ریښتیا;

	إذا (tv1 == NULL_ونه || tv2 == NULL_ونه)
	  أرجع خطأ;

	إذا (list_اوږدتیا (TYPE_ارزښتونه (t1)) != list_اوږدتیا (TYPE_ارزښتونه (t2)))
	  أرجع خطأ;

	لكل (s1 = TYPE_ارزښتونه (t1); s1; s1 = ونه_CHAIN (s1))
	  {
	    s2 = purpose_member (ونه_PURPOSE (s1), TYPE_ارزښتونه (t2));

	    إذا (s2 == عدم
		|| simple_cst_equal (DECL_INITIAL (ونه_ارزښت (s1)),
				     DECL_INITIAL (ونه_ارزښت (s2))) != 1)
	      أرجع خطأ;
	  }

	أرجع ریښتیا;
      }

    حالة UNION_TYPE:
    حالة ریکارډ_TYPE:

	إذا (list_اوږدتیا (TYPE_FIELDS (t1)) != list_اوږدتیا (TYPE_FIELDS (t2)))
	  أرجع خطأ;

	لكل (s1 = TYPE_FIELDS (t1), s2 = TYPE_FIELDS (t2);
	     s1 && s2;
	     s1 = DECL_CHAIN (s1), s2 = DECL_CHAIN (s2))
	  {
	    gcc_assert (ونه_کوډ (s1) == ډګر_DECL);
	    gcc_assert (ونه_کوډ (s2) == ډګر_DECL);

	    ونه ft1 = ونه_TYPE (s1);
	    ونه ft2 = ونه_TYPE (s2);

	    إذا (DECL_NAME (s1) != DECL_NAME (s2))
	      أرجع خطأ;

	    إذا (DECL_ALIGN (s1) != DECL_ALIGN (s2))
	      أرجع خطأ;

	    إذا (DECL_C_بټ_ډګر (s1) != DECL_C_بټ_ډګر (s2))
	       أرجع خطأ;

	    إذا (DECL_C_بټ_ډګر (s1))
	      {
		إذا (!ونه_int_cst_equal (DECL_اندازه (s1), DECL_اندازه (s2)))
		  أرجع خطأ;

		ft1 = DECL_بټ_ډګر_TYPE (s1);
		ft2 = DECL_بټ_ډګر_TYPE (s2);
	      }

	    إذا (!ft1 || !ft2)
	      أرجع خطأ;

	    إذا (ونه_کوډ (ft1) == ERROR_MARK || ونه_کوډ (ft2) == ERROR_MARK)
	      أرجع خطأ;

	    معلومات->anon_ډګر = !DECL_NAME (s1);
	    معلومات->pointedto = خطأ;

	    ثابت بنية tagged_tu_کتل_شوی_cache *cache = معلومات->cache;
	    معلومات->cache = &ثبت;
	    منطقي ret = comptypes_دننی (ft1, ft2, معلومات);
	    معلومات->cache = cache;
	    إذا (!ret)
	      أرجع خطأ;

	    ونه st1 = TYPE_اندازه (ونه_TYPE (s1));
	    ونه st2 = TYPE_اندازه (ونه_TYPE (s2));

	    إذا (معلومات->equiv
		&& st1 && ونه_کوډ (st1) == INTEGER_CST
		&& st2 && ونه_کوډ (st2) == INTEGER_CST
		&& !ونه_int_cst_equal (st1, st2))
	     أرجع خطأ;

	    ونه counted_by1 = lookup_attribute ("counted_by",
						 DECL_ځانګړتیاوې (s1));
	    ونه counted_by2 = lookup_attribute ("counted_by",
						 DECL_ځانګړتیاوې (s2));
	    /* If there is no counted_by attribute for both fields.  */
	    إذا (!counted_by1 && !counted_by2)
	      استمر;

	    /* If only one field has counted_by attribute.  */
	    إذا ((counted_by1 && !counted_by2)
		|| (!counted_by1 && counted_by2))
	      أرجع خطأ;

	    /* Now both s1 and s2 have counted_by attributes, check
	       whether they are the same.  */

	    ونه counted_by_field1
	      = lookup_ډګر (t1, ونه_ارزښت (ونه_ارزښت (counted_by1)));
	    ونه counted_by_field2
	      = lookup_ډګر (t2, ونه_ارزښت (ونه_ارزښت (counted_by2)));

	    gcc_assert (counted_by_field1 && counted_by_field2);

	    طالما (ونه_CHAIN (counted_by_field1))
	      counted_by_field1 = ونه_CHAIN (counted_by_field1);
	    طالما (ونه_CHAIN (counted_by_field2))
	      counted_by_field2 = ونه_CHAIN (counted_by_field2);

	    إذا (DECL_NAME (ونه_ارزښت (counted_by_field1))
		!= DECL_NAME (ونه_ارزښت (counted_by_field2)))
	      أرجع خطأ;
	  }
	أرجع ریښتیا;

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
function_types_compatible_p (const_ونه f1, const_ونه f2,
			     بنية comptypes_معلومات *معلومات)
{
  ونه ret1 = ونه_TYPE (f1);
  ونه ret2 = ونه_TYPE (f2);

  /* 'volatile' qualifiers on a function's return type used to mean
     the function is noreturn.  */
  إذا (TYPE_VOLATILE (ret1) != TYPE_VOLATILE (ret2))
    pedwarn (ننوت_location, 0, "function return types not compatible due to %<volatile%>");
  إذا (TYPE_VOLATILE (ret1))
    ret1 = build_qualified_type (TYPE_MAIN_VARIANT (ret1),
				 TYPE_QUALS (ret1) & ~TYPE_QUAL_VOLATILE);
  إذا (TYPE_VOLATILE (ret2))
    ret2 = build_qualified_type (TYPE_MAIN_VARIANT (ret2),
				 TYPE_QUALS (ret2) & ~TYPE_QUAL_VOLATILE);

  منطقي ignore_pargs = معلومات->ignore_promoting_دلیلونه;
  معلومات->ignore_promoting_دلیلونه = خطأ;

  إذا (!comptypes_دننی (ret1, ret2, معلومات))
    أرجع خطأ;

  معلومات->ignore_promoting_دلیلونه = ignore_pargs;

  ونه args1 = TYPE_ARG_TYPES (f1);
  ونه args2 = TYPE_ARG_TYPES (f2);

  إذا ((args1 == NULL_ونه) != (args2 == NULL_ونه))
    معلومات->different_types_p = ریښتیا;

  /* An unspecified parmlist matches any specified parmlist
     whose argument types don't need default promotions.  */

  إذا (args1 == NULL_ونه)
    {
      إذا (TYPE_NO_NAMED_دلیلونه_STDARG_P (f1) != TYPE_NO_NAMED_دلیلونه_STDARG_P (f2))
	أرجع خطأ;
      إذا (!(معلومات->ignore_promoting_دلیلونه || self_promoting_دلیلونه_p (args2)))
	أرجع خطأ;
      معلومات->ignore_promoting_دلیلونه = خطأ;
      /* If one of these types comes from a non-prototype fn definition,
	 compare that with the other type's arglist.
	 If they don't match, ask for a warning (but no error).  */
      إذا (TYPE_ACTUAL_ARG_TYPES (f1)
	  && !type_lists_compatible_p (args2, TYPE_ACTUAL_ARG_TYPES (f1), معلومات))
	 معلومات->warning_needed = ریښتیا;
      أرجع ریښتیا;
    }
  إذا (args2 == NULL_ونه)
    {
      إذا (TYPE_NO_NAMED_دلیلونه_STDARG_P (f1) != TYPE_NO_NAMED_دلیلونه_STDARG_P (f2))
	أرجع خطأ;
      إذا (!(معلومات->ignore_promoting_دلیلونه || self_promoting_دلیلونه_p (args1)))
	أرجع خطأ;
      معلومات->ignore_promoting_دلیلونه = خطأ;
      إذا (TYPE_ACTUAL_ARG_TYPES (f2)
	  && !type_lists_compatible_p (args1, TYPE_ACTUAL_ARG_TYPES (f2), معلومات))
	معلومات->warning_needed = ریښتیا;
      أرجع ریښتیا;
    }

  /* Both types have argument lists: compare them and propagate results.  */
  أرجع type_lists_compatible_p (args1, args2, معلومات);
}

/* Check two lists of types for compatibility, returning false for
   incompatible, true for compatible.  */

ساكن منطقي
type_lists_compatible_p (const_ونه args1, const_ونه args2,
			 بنية comptypes_معلومات *معلومات)
{
  طالما (1)
    {
      إذا (args1 == NULL_ونه && args2 == NULL_ونه)
	أرجع ریښتیا;
      /* If one list is shorter than the other,
	 they fail to match.  */
      إذا (args1 == NULL_ونه || args2 == NULL_ونه)
	أرجع خطأ;
      ونه a1 = ونه_ارزښت (args1);
      ونه a2 = ونه_ارزښت (args2);
      ونه mv1 = remove_qualifiers (a1);
      ونه mv2 = remove_qualifiers (a2);

      gcc_assert (mv2);
      gcc_assert (mv2);

      /* If one of the lists has an error marker, ignore this arg.  */
      إذا (ونه_کوډ (a1) == ERROR_MARK
	       || ونه_کوډ (a2) == ERROR_MARK)
	;
      وإلا إذا (!comptypes_دننی (mv1, mv2, معلومات))
	{
	  معلومات->different_types_p = ریښتیا;
	  /* Allow  wait (union {union wait *u; int *i} *)
	     and  wait (union wait *)  to be compatible.  */
	  إذا (ونه_کوډ (a1) == UNION_TYPE
	      && (TYPE_NAME (a1) == NULL_ونه
		  || TYPE_TRANSPARENT_AGGR (a1))
	      && ونه_کوډ (TYPE_اندازه (a1)) == INTEGER_CST
	      && ونه_int_cst_equal (TYPE_اندازه (a1),
				     TYPE_اندازه (a2)))
	    {
	      ونه memb;
	      لكل (memb = TYPE_FIELDS (a1);
		   memb; memb = DECL_CHAIN (memb))
		{
		  ونه mv3 = remove_qualifiers (ونه_TYPE (memb));
		  إذا (comptypes_دننی (mv3, mv2, معلومات))
		    اكسر;
		}
	      إذا (memb == NULL_ونه)
		أرجع خطأ;
	    }
	  وإلا إذا (ونه_کوډ (a2) == UNION_TYPE
		   && (TYPE_NAME (a2) == NULL_ونه
		       || TYPE_TRANSPARENT_AGGR (a2))
		   && ونه_کوډ (TYPE_اندازه (a2)) == INTEGER_CST
		   && ونه_int_cst_equal (TYPE_اندازه (a2),
					  TYPE_اندازه (a1)))
	    {
	      ونه memb;
	      لكل (memb = TYPE_FIELDS (a2);
		   memb; memb = DECL_CHAIN (memb))
		{
		  ونه mv3 = remove_qualifiers (ونه_TYPE (memb));
		  إذا (comptypes_دننی (mv3, mv1, معلومات))
		    اكسر;
		}
	      إذا (memb == NULL_ونه)
		أرجع خطأ;
	    }
	  وإلا
	    أرجع خطأ;
	}

      args1 = ونه_CHAIN (args1);
      args2 = ونه_CHAIN (args2);
    }
}

/* Compute the size to increment a pointer by.  When a function type or void
   type or incomplete type is passed, size_one_node is returned.
   This function does not emit any diagnostics; the caller is responsible
   for that.  */

ساكن ونه
c_اندازه_دننه_بایټونه (const_ونه type)
{
  تعداد ونه_کوډ_2 کوډ = ونه_کوډ (type);

  إذا (کوډ == FUNCTION_TYPE || کوډ == VOID_TYPE || کوډ == ERROR_MARK
      || !COMPLETE_TYPE_P (type))
    أرجع اندازه_one_غوټه;

  /* Convert in case a char is more than one unit.  */
  أرجع اندازه_binop_loc (ننوت_location, CEIL_DIV_بیان, TYPE_اندازه_UNIT (type),
			 اندازه_int (TYPE_PRECISION (char_type_غوټه)
				   / بټونه_فی_UNIT));
}

/* Return either DECL or its known constant value (if it has one).  */

ونه
decl_constant_ارزښت_1 (ونه decl, منطقي دننه_init)
{
  إذا (/* Note that DECL_INITIAL isn't valid for a PARM_DECL.  */
      ونه_کوډ (decl) != PARM_DECL
      && !ونه_THIS_VOLATILE (decl)
      && ونه_READONLY (decl)
      && DECL_INITIAL (decl) != NULL_ونه
      && !error_عملوند_p (DECL_INITIAL (decl))
      /* This is invalid if initial value is not constant.
	 If it has either a function call, a memory reference,
	 or a variable, then re-evaluating it could give different results.  */
      && ونه_CONSTANT (DECL_INITIAL (decl))
      /* Check for cases where this is sub-optimal, even though valid.  */
      && (دننه_init || ونه_کوډ (DECL_INITIAL (decl)) != CONSTRUCTOR))
    أرجع DECL_INITIAL (decl);
  أرجع decl;
}

/* Return either DECL or its known constant value (if it has one).
   Like the above, but always return decl outside of functions.  */

ونه
decl_constant_ارزښت (ونه decl)
{
  /* Don't change a variable array bound or initial value to a constant
     in a place where a variable is invalid.  */
  أرجع current_function_decl ? decl_constant_ارزښت_1 (decl, خطأ) : decl;
}

/* Convert the array expression EXP to a pointer.  */
ساكن ونه
array_منزل_اشاره_ګر_conversion (location_t loc, ونه توانیز_تابع)
{
  ونه orig_exp = توانیز_تابع;
  ونه type = ونه_TYPE (توانیز_تابع);
  ونه adr;
  ونه restype = ونه_TYPE (type);
  ونه ptrtype;

  gcc_assert (ونه_کوډ (type) == ARRAY_TYPE);

  STRIP_TYPE_NOPS (توانیز_تابع);

  copy_warning (توانیز_تابع, orig_exp);

  ptrtype = c_build_اشاره_ګر_type (restype);

  إذا (غیرمستقیم_REF_P (توانیز_تابع))
    أرجع convert (ptrtype, ونه_عملوند (توانیز_تابع, 0));

  /* In C++ array compound literals are temporary objects unless they are
     const or appear in namespace scope, so they are destroyed too soon
     to use them for much of anything  (c++/53220).  */
  إذا (warn_cxx_compat && ونه_کوډ (توانیز_تابع) == COMPOUND_LITERAL_بیان)
    {
      ونه decl = ونه_عملوند (ونه_عملوند (توانیز_تابع, 0), 0);
      إذا (!ونه_READONLY (decl) && !ونه_STATIC (decl))
	warning_at (DECL_سرچینه_LOCATION (decl), OPT_Wc___compat,
		    "converting an array compound literal to a pointer "
		    "leads to a dangling pointer in C++");
    }

  adr = build_unary_op (loc, ADDR_بیان, توانیز_تابع, ریښتیا);
  أرجع convert (ptrtype, adr);
}

/* Convert the function expression EXP to a pointer.  */
ساكن ونه
function_منزل_اشاره_ګر_conversion (location_t loc, ونه توانیز_تابع)
{
  ونه orig_exp = توانیز_تابع;

  gcc_assert (ونه_کوډ (ونه_TYPE (توانیز_تابع)) == FUNCTION_TYPE);

  STRIP_TYPE_NOPS (توانیز_تابع);

  copy_warning (توانیز_تابع, orig_exp);

  ونه exp2 = build_unary_op (loc, ADDR_بیان, توانیز_تابع, خطأ);

  /* If the function is defined and known to not require a non-local
     context, make sure no trampoline is generated.  */
  إذا (ونه_کوډ (توانیز_تابع) == FUNCTION_DECL
      && DECL_INITIAL (توانیز_تابع) && !C_FUNC_NONLOCAL_CONTEXT (توانیز_تابع))
   ونه_NO_TRAMPOLINE (exp2) = 1;

  أرجع exp2;
}

/* Mark EXP as read, not just set, for set but not used -Wunused
   warning purposes.  */

فراغ
mark_exp_read (ونه توانیز_تابع)
{
  بدل (ونه_کوډ (توانیز_تابع))
    {
    حالة VAR_DECL:
    حالة PARM_DECL:
      DECL_READ_P (توانیز_تابع) = 1;
      اكسر;
    CASE_CONVERT:
      إذا (VOID_TYPE_P (ونه_TYPE (توانیز_تابع)))
	بدل (ونه_کوډ (ونه_عملوند (توانیز_تابع, 0)))
	  {
	  حالة PREINCREMENT_بیان:
	  حالة PREDECREMENT_بیان:
	  حالة POSTINCREMENT_بیان:
	  حالة POSTDECREMENT_بیان:
	    أرجع;
	  افتراضي:
	    اكسر;
	  }
      /* FALLTHRU */
    حالة ARRAY_REF:
    حالة COMPONENT_REF:
    حالة MODIFY_بیان:
    حالة REALPART_بیان:
    حالة IMAGPART_بیان:
    حالة ADDR_بیان:
    حالة VIEW_CONVERT_بیان:
    حالة PREINCREMENT_بیان:
    حالة PREDECREMENT_بیان:
    حالة POSTINCREMENT_بیان:
    حالة POSTDECREMENT_بیان:
      mark_exp_read (ونه_عملوند (توانیز_تابع, 0));
      اكسر;
    حالة COMPOUND_بیان:
      /* Pattern match what build_atomic_assign produces with modifycode
	 NOP_EXPR.  */
      إذا (VAR_P (ونه_عملوند (توانیز_تابع, 1))
	  && DECL_ARTIFICIAL (ونه_عملوند (توانیز_تابع, 1))
	  && ونه_کوډ (ونه_عملوند (توانیز_تابع, 0)) == COMPOUND_بیان)
	{
	  ونه t1 = ونه_عملوند (ونه_عملوند (توانیز_تابع, 0), 0);
	  ونه t2 = ونه_عملوند (ونه_عملوند (توانیز_تابع, 0), 1);
	  إذا (ونه_کوډ (t1) == موخه_بیان
	      && موخه_بیان_خونه (t1) == ونه_عملوند (توانیز_تابع, 1)
	      && ونه_کوډ (t2) == CALL_بیان)
	    {
	      ونه fndecl = get_callee_fndecl (t2);
	      ونه arg = NULL_ونه;
	      إذا (fndecl
		  && ونه_کوډ (fndecl) == FUNCTION_DECL
		  && fndecl_built_دننه_p (fndecl, BUILT_دننه_نورمال)
		  && call_بیان_nargs (t2) >= 2)
		بدل (DECL_FUNCTION_کوډ (fndecl))
		  {
		  حالة BUILT_دننه_ATOMIC_STORE:
		    arg = CALL_بیان_ARG (t2, 1);
		    اكسر;
		  حالة BUILT_دننه_ATOMIC_STORE_1:
		  حالة BUILT_دننه_ATOMIC_STORE_2:
		  حالة BUILT_دننه_ATOMIC_STORE_4:
		  حالة BUILT_دننه_ATOMIC_STORE_8:
		  حالة BUILT_دننه_ATOMIC_STORE_16:
		    arg = CALL_بیان_ARG (t2, 0);
		    اكسر;
		  افتراضي:
		    اكسر;
		  }
	      إذا (arg)
		{
		  STRIP_NOPS (arg);
		  إذا (ونه_کوډ (arg) == ADDR_بیان
		      && DECL_P (ونه_عملوند (arg, 0))
		      && TYPE_ATOMIC (ونه_TYPE (ونه_عملوند (arg, 0))))
		    mark_exp_read (ونه_عملوند (arg, 0));
		}
	    }
	}
      /* FALLTHRU */
    حالة C_MAYBE_CONST_بیان:
      mark_exp_read (ونه_عملوند (توانیز_تابع, 1));
      اكسر;
    حالة OMP_ARRAY_SECTION:
      mark_exp_read (ونه_عملوند (توانیز_تابع, 0));
      إذا (ونه_عملوند (توانیز_تابع, 1))
	mark_exp_read (ونه_عملوند (توانیز_تابع, 1));
      إذا (ونه_عملوند (توانیز_تابع, 2))
	mark_exp_read (ونه_عملوند (توانیز_تابع, 2));
      اكسر;
    افتراضي:
      اكسر;
    }
}

/* Perform the default conversion of arrays and functions to pointers.
   Return the result of converting EXP.  For any other expression, just
   return EXP.

   LOC is the location of the expression.  */

بنية c_بیان
default_function_array_conversion (location_t loc, بنية c_بیان توانیز_تابع)
{
  ونه orig_exp = توانیز_تابع.ارزښت;
  ونه type = ونه_TYPE (توانیز_تابع.ارزښت);
  تعداد ونه_کوډ_2 کوډ = ونه_کوډ (type);

  بدل (کوډ)
    {
    حالة ARRAY_TYPE:
      {
	منطقي not_lvalue = خطأ;
	منطقي lvalue_array_p;

	طالما ((ونه_کوډ (توانیز_تابع.ارزښت) == NON_LVALUE_بیان
		|| CONVERT_بیان_P (توانیز_تابع.ارزښت))
	       && ونه_TYPE (ونه_عملوند (توانیز_تابع.ارزښت, 0)) == type)
	  {
	    إذا (ونه_کوډ (توانیز_تابع.ارزښت) == NON_LVALUE_بیان)
	      not_lvalue = ریښتیا;
	    توانیز_تابع.ارزښت = ونه_عملوند (توانیز_تابع.ارزښت, 0);
	  }

	copy_warning (توانیز_تابع.ارزښت, orig_exp);

	lvalue_array_p = !not_lvalue && lvalue_p (توانیز_تابع.ارزښت);
	إذا (!flag_isoc99 && !lvalue_array_p)
	  {
	    /* Before C99, non-lvalue arrays do not decay to pointers.
	       Normally, using such an array would be invalid; but it can
	       be used correctly inside sizeof or as a statement expression.
	       Thus, do not give an error here; an error will result later.  */
	    أرجع توانیز_تابع;
	  }

	توانیز_تابع.ارزښت = array_منزل_اشاره_ګر_conversion (loc, توانیز_تابع.ارزښت);
      }
      اكسر;
    حالة FUNCTION_TYPE:
      توانیز_تابع.ارزښت = function_منزل_اشاره_ګر_conversion (loc, توانیز_تابع.ارزښت);
      اكسر;
    افتراضي:
      اكسر;
    }

  أرجع توانیز_تابع;
}

بنية c_بیان
default_function_array_read_conversion (location_t loc, بنية c_بیان توانیز_تابع)
{
  mark_exp_read (توانیز_تابع.ارزښت);
  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  إذا (ونه_کوډ (توانیز_تابع.ارزښت) == COMPONENT_REF
      && handle_counted_by_p (توانیز_تابع.ارزښت))
    توانیز_تابع.ارزښت = handle_counted_by_for_component_ref (loc, توانیز_تابع.ارزښت);
  أرجع default_function_array_conversion (loc, توانیز_تابع);
}

/* Return whether EXPR should be treated as an atomic lvalue for the
   purposes of load and store handling.  */

ساكن منطقي
really_atomic_lvalue (ونه بیان)
{
  إذا (error_عملوند_p (بیان))
    أرجع خطأ;
  إذا (!TYPE_ATOMIC (ونه_TYPE (بیان)))
    أرجع خطأ;
  إذا (!COMPLETE_TYPE_P (ونه_TYPE (بیان)))
    أرجع خطأ;
  إذا (!lvalue_p (بیان))
    أرجع خطأ;

  /* Ignore _Atomic on register variables, since their addresses can't
     be taken so (a) atomicity is irrelevant and (b) the normal atomic
     sequences wouldn't work.  Ignore _Atomic on structures containing
     bit-fields, since accessing elements of atomic structures or
     unions is undefined behavior (C11 6.5.2.3#5), but it's unclear if
     it's undefined at translation time or execution time, and the
     normal atomic sequences again wouldn't work.  */
  طالما (handled_component_p (بیان))
    {
      إذا (ونه_کوډ (بیان) == COMPONENT_REF
	  && DECL_C_بټ_ډګر (ونه_عملوند (بیان, 1)))
	أرجع خطأ;
      بیان = ونه_عملوند (بیان, 0);
    }
  إذا (ونه_کوډ (بیان) == COMPOUND_LITERAL_بیان)
    بیان = COMPOUND_LITERAL_بیان_DECL (بیان);
  إذا (DECL_P (بیان) && C_DECL_ثبتوونکی (بیان))
    أرجع خطأ;
  أرجع ریښتیا;
}

/* If EXPR is a named constant (C23) derived from a constexpr variable
   - that is, a reference to such a variable, or a member extracted by
   a sequence of structure and union (but not array) member accesses
   (where union member accesses must access the same member as
   initialized) - then return the corresponding initializer;
   otherwise, return NULL_TREE.  */

ساكن ونه
maybe_get_constexpr_init (ونه بیان)
{
  ونه decl = NULL_ونه;
  إذا (ونه_کوډ (بیان) == VAR_DECL)
    decl = بیان;
  وإلا إذا (ونه_کوډ (بیان) == COMPOUND_LITERAL_بیان)
    decl = COMPOUND_LITERAL_بیان_DECL (بیان);
  إذا (decl
      && C_DECL_DECLARED_CONSTEXPR (decl)
      && DECL_INITIAL (decl) != NULL_ونه
      && !error_عملوند_p (DECL_INITIAL (decl)))
    أرجع DECL_INITIAL (decl);
  إذا (ونه_کوډ (بیان) != COMPONENT_REF)
    أرجع NULL_ونه;
  ونه inner = maybe_get_constexpr_init (ونه_عملوند (بیان, 0));
  إذا (inner == NULL_ونه)
    أرجع NULL_ونه;
  طالما ((CONVERT_بیان_P (inner) || ونه_کوډ (inner) == NON_LVALUE_بیان)
	 && !error_عملوند_p (inner)
	 && (TYPE_MAIN_VARIANT (ونه_TYPE (inner))
	     == TYPE_MAIN_VARIANT (ونه_TYPE (ونه_عملوند (inner, 0)))))
    inner = ونه_عملوند (inner, 0);
  إذا (ونه_کوډ (inner) != CONSTRUCTOR)
    أرجع NULL_ونه;
  ونه ډګر_2 = ونه_عملوند (بیان, 1);
  بینښه HOST_WIDE_INT cidx;
  ونه cfield, cvalue;
  منطقي have_other_init = خطأ;
  FOR_EACH_CONSTRUCTOR_ELT (CONSTRUCTOR_ELTS (inner), cidx, cfield, cvalue)
    {
      إذا (cfield == ډګر_2)
	أرجع cvalue;
      have_other_init = ریښتیا;
    }
  إذا (ونه_کوډ (ونه_TYPE (inner)) == UNION_TYPE
      && (have_other_init || ډګر_2 != TYPE_FIELDS (ونه_TYPE (inner))))
    أرجع NULL_ونه;
  /* Return a default initializer.  */
  إذا (ریکارډ_OR_UNION_TYPE_P (ونه_TYPE (بیان)))
    أرجع build_constructor (ونه_TYPE (بیان), عدم);
  أرجع build_zero_cst (ونه_TYPE (بیان));
}

/* Helper function for convert_lvalue_to_rvalue called via
   walk_tree_without_duplicates.  Find DATA inside of the expression.  */

ساكن ونه
c_پیدا_کړه_var_r (ونه *tp, صحيح *walk_subtrees, فراغ *معلومات)
{
  إذا (TYPE_P (*tp))
    *walk_subtrees = 0;
  وإلا إذا (*tp == (ونه) معلومات)
    أرجع *tp;
  أرجع NULL_ونه;
}

/* Convert expression EXP (location LOC) from lvalue to rvalue,
   including converting functions and arrays to pointers if CONVERT_P.
   If READ_P, also mark the expression as having been read.  If
   FOR_INIT, constexpr expressions of structure and union type should
   be replaced by the corresponding CONSTRUCTOR; otherwise, only
   constexpr scalars (including elements of structures and unions) are
   replaced by their initializers.  */

بنية c_بیان
convert_lvalue_منزل_rvalue (location_t loc, بنية c_بیان توانیز_تابع,
			  منطقي convert_p, منطقي read_p, منطقي for_init)
{
  منطقي force_non_npc = خطأ;
  إذا (read_p)
    mark_exp_read (توانیز_تابع.ارزښت);
  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  إذا (read_p && ونه_کوډ (توانیز_تابع.ارزښت) == COMPONENT_REF
      && handle_counted_by_p (توانیز_تابع.ارزښت))
    توانیز_تابع.ارزښت = handle_counted_by_for_component_ref (loc, توانیز_تابع.ارزښت);

  إذا (convert_p)
    توانیز_تابع = default_function_array_conversion (loc, توانیز_تابع);
  إذا (!VOID_TYPE_P (ونه_TYPE (توانیز_تابع.ارزښت))
      || (flag_isoc2y
	  && TYPE_QUALS (ونه_TYPE (توانیز_تابع.ارزښت)) != TYPE_UNQUALIFIED))
    توانیز_تابع.ارزښت = require_complete_type (loc, توانیز_تابع.ارزښت);
  إذا (for_init || !ریکارډ_OR_UNION_TYPE_P (ونه_TYPE (توانیز_تابع.ارزښت)))
    {
      ونه init = maybe_get_constexpr_init (توانیز_تابع.ارزښت);
      إذا (init != NULL_ونه)
	{
	  /* A named constant of pointer type or type nullptr_t is not
	     a null pointer constant even if the initializer is
	     one.  */
	  إذا (ونه_کوډ (init) == INTEGER_CST
	      && !INTEGRAL_TYPE_P (ونه_TYPE (init))
	      && integer_zerop (init))
	    force_non_npc = ریښتیا;
	  توانیز_تابع.ارزښت = init;
	}
    }
  إذا (really_atomic_lvalue (توانیز_تابع.ارزښت))
    {
      vec<ونه, va_gc> *params;
      ونه nonatomic_type, tmp, tmp_addr, fndecl, func_call;
      ونه بیان_type = ونه_TYPE (توانیز_تابع.ارزښت);
      ونه بیان_addr = build_unary_op (loc, ADDR_بیان, توانیز_تابع.ارزښت, خطأ);
      ونه seq_cst = build_int_cst (integer_type_غوټه, MEMMODEL_SEQ_CST);

      gcc_assert (TYPE_ATOMIC (بیان_type));

      /* Expansion of a generic atomic load may require an addition
	 element, so allocate enough to prevent a resize.  */
      vec_alloc (params, 4);

      /* Remove the qualifiers for the rest of the expressions and
	 create the VAL temp variable to hold the RHS.  */
      nonatomic_type = build_qualified_type (بیان_type, TYPE_UNQUALIFIED);
      tmp = create_tmp_var_raw (nonatomic_type);
      tmp_addr = build_unary_op (loc, ADDR_بیان, tmp, خطأ);
      ونه_ADDRESSABLE (tmp) = 1;
      /* Do not disable warnings for TMP even though it's artificial.
	 -Winvalid-memory-model depends on it.  */

      /* Issue __atomic_load (&expr, &tmp, SEQ_CST);  */
      fndecl = builtin_decl_explicit (BUILT_دننه_ATOMIC_بارول);
      params->چټک_ټېل (بیان_addr);
      params->چټک_ټېل (tmp_addr);
      params->چټک_ټېل (seq_cst);
      func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, عدم);

      /* EXPR is always read.  */
      mark_exp_read (توانیز_تابع.ارزښت);

      /* Optimize the common case where c_build_function_call_vec
	 immediately folds __atomic_load (&expr, &tmp, SEQ_CST); into
	 tmp = __atomic_load_<N> (&expr, SEQ_CST);
	 In that case tmp is not addressable and can be initialized
	 fully by the rhs of the MODIFY_EXPR.  */
      ونه tem = func_call;
      إذا (CONVERT_بیان_P (tem) && VOID_TYPE_P (ونه_TYPE (tem)))
	{
	  tem = ونه_عملوند (tem, 0);
	  إذا (ونه_کوډ (tem) == MODIFY_بیان
	      && ونه_عملوند (tem, 0) == tmp
	      && !walk_ونه_without_duplicates (&ونه_عملوند (tem, 1),
						c_پیدا_کړه_var_r, tmp))
	    {
	      ونه_ADDRESSABLE (tmp) = 0;
	      func_call = ونه_عملوند (tem, 1);
	    }
	}

      /* Return tmp which contains the value loaded.  */
      توانیز_تابع.ارزښت = build4 (موخه_بیان, nonatomic_type, tmp, func_call,
			  NULL_ونه, NULL_ونه);
    }
  إذا (convert_p && !error_عملوند_p (توانیز_تابع.ارزښت)
      && (ونه_کوډ (ونه_TYPE (توانیز_تابع.ارزښت)) != ARRAY_TYPE))
    توانیز_تابع.ارزښت = convert (build_qualified_type (ونه_TYPE (توانیز_تابع.ارزښت), TYPE_UNQUALIFIED), توانیز_تابع.ارزښت);
  إذا (force_non_npc)
    توانیز_تابع.ارزښت = build1 (NOP_بیان, ونه_TYPE (توانیز_تابع.ارزښت), توانیز_تابع.ارزښت);

  {
    ونه false_ارزښت, true_ارزښت;
    إذا (convert_p && !error_عملوند_p (توانیز_تابع.ارزښت)
	&& c_hardbool_type_attr (ونه_TYPE (توانیز_تابع.ارزښت),
				 &false_ارزښت, &true_ارزښت))
      {
	ونه t = save_بیان (توانیز_تابع.ارزښت);

	mark_exp_read (توانیز_تابع.ارزښت);

	ونه trapfn = builtin_decl_explicit (BUILT_دننه_TRAP);
	ونه بیان = build_call_بیان_loc (loc, trapfn, 0);
	بیان = build_compound_بیان (loc, بیان, boolean_true_غوټه);
	بیان = fold_build3_loc (loc, COND_بیان, boolean_type_غوټه,
				fold_build2_loc (loc, NE_بیان,
						 boolean_type_غوټه,
						 t, true_ارزښت),
				بیان, boolean_true_غوټه);
	بیان = fold_build3_loc (loc, COND_بیان, boolean_type_غوټه,
				fold_build2_loc (loc, NE_بیان,
						 boolean_type_غوټه,
						 t, false_ارزښت),
				بیان, boolean_false_غوټه);

	توانیز_تابع.ارزښت = بیان;
      }
  }

  أرجع توانیز_تابع;
}

/* Wrapper for the overload above, same arguments but for tree rather than
   c_expr.  This is important for hardbools to decay to bools.  */

ساكن مضمن ونه
convert_lvalue_منزل_rvalue (location_t loc, ونه val,
			  منطقي convert_p, منطقي read_p, منطقي for_init = خطأ)
{
  بنية c_بیان بیان;
  memset (&بیان, 0, حجم (بیان));
  بیان.ارزښت = val;
  بیان = convert_lvalue_منزل_rvalue (loc, بیان, convert_p, read_p, for_init);
  أرجع بیان.ارزښت;
}

/* EXP is an expression of integer type.  Apply the integer promotions
   to it and return the promoted value.  */

ونه
perform_integral_promotions (ونه توانیز_تابع)
{
  ونه type = ونه_TYPE (توانیز_تابع);
  تعداد ونه_کوډ_2 کوډ = ونه_کوډ (type);

  gcc_assert (INTEGRAL_TYPE_P (type));

  /* Convert enums to the result of applying the integer promotions to
     their underlying type.  */
  إذا (کوډ == ENUMERAL_TYPE)
    {
      type = ENUM_UNDERLYING_TYPE (type);
      إذا (c_promoting_integer_type_p (type))
	{
	  إذا (TYPE_UNSIGNED (type)
	      && TYPE_PRECISION (type) == TYPE_PRECISION (integer_type_غوټه))
	    type = unsigned_type_غوټه;
	  وإلا
	    type = integer_type_غوټه;
	}

      أرجع convert (type, توانیز_تابع);
    }

  /* ??? This should no longer be needed now bit-fields have their
     proper types.  */
  إذا (ونه_کوډ (توانیز_تابع) == COMPONENT_REF
      && DECL_C_بټ_ډګر (ونه_عملوند (توانیز_تابع, 1)))
    {
      إذا (BITINT_TYPE_P (DECL_بټ_ډګر_TYPE (ونه_عملوند (توانیز_تابع, 1))))
	{
	  ونه btype = DECL_بټ_ډګر_TYPE (ونه_عملوند (توانیز_تابع, 1));
	  إذا (ونه_کوډ (btype) == BITINT_TYPE)
	    أرجع convert (btype, توانیز_تابع);
	  وإلا
	    أرجع convert (ENUM_UNDERLYING_TYPE (btype), توانیز_تابع);
	}
      /* If it's thinner than an int, promote it like a
	 c_promoting_integer_type_p, otherwise leave it alone.  */
      إذا (compare_ونه_int (DECL_اندازه (ونه_عملوند (توانیز_تابع, 1)),
			    TYPE_PRECISION (integer_type_غوټه)) < 0)
	أرجع convert (integer_type_غوټه, توانیز_تابع);
    }

  إذا (c_promoting_integer_type_p (type))
    {
      /* Preserve unsignedness if not really getting any wider.  */
      إذا (TYPE_UNSIGNED (type)
	  && TYPE_PRECISION (type) == TYPE_PRECISION (integer_type_غوټه))
	أرجع convert (unsigned_type_غوټه, توانیز_تابع);

      أرجع convert (integer_type_غوټه, توانیز_تابع);
    }

  أرجع توانیز_تابع;
}


/* Perform default promotions for C data used in expressions.
   Enumeral types or short or char are converted to int.
   In addition, manifest constants symbols are replaced by their values.  */

ونه
default_conversion (ونه توانیز_تابع)
{
  ونه orig_exp;
  ونه type = ونه_TYPE (توانیز_تابع);
  تعداد ونه_کوډ_2 کوډ = ونه_کوډ (type);
  ونه promoted_type;

  mark_exp_read (توانیز_تابع);
  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  إذا (ونه_کوډ (توانیز_تابع) == COMPONENT_REF
      && handle_counted_by_p (توانیز_تابع))
    توانیز_تابع = handle_counted_by_for_component_ref (بیان_LOCATION (توانیز_تابع), توانیز_تابع);

  /* Functions and arrays have been converted during parsing.  */
  gcc_assert (کوډ != FUNCTION_TYPE);
  إذا (کوډ == ARRAY_TYPE)
    أرجع توانیز_تابع;

  /* Constants can be used directly unless they're not loadable.  */
  إذا (ونه_کوډ (توانیز_تابع) == CONST_DECL)
    توانیز_تابع = DECL_INITIAL (توانیز_تابع);

  /* Strip no-op conversions.  */
  orig_exp = توانیز_تابع;
  STRIP_TYPE_NOPS (توانیز_تابع);

  copy_warning (توانیز_تابع, orig_exp);

  إذا (کوډ == VOID_TYPE)
    {
      error_at (بیان_LOC_OR_LOC (توانیز_تابع, ننوت_location),
		"void value not ignored as it ought to be");
      أرجع error_mark_غوټه;
    }

  توانیز_تابع = require_complete_type (بیان_LOC_OR_LOC (توانیز_تابع, ننوت_location), توانیز_تابع);
  إذا (توانیز_تابع == error_mark_غوټه)
    أرجع error_mark_غوټه;

  promoted_type = targetm.promoted_type (type);
  إذا (promoted_type)
    أرجع convert (promoted_type, توانیز_تابع);

  إذا (INTEGRAL_TYPE_P (type))
    {
      /* Avoid performing integral promotion of bit-precise integer
	 type bit-field to its corresponding bit-precise integer if
	 orig_exp is a cast to it to its underlying type.  */
      إذا (orig_exp != توانیز_تابع
	  && ونه_کوډ (توانیز_تابع) == COMPONENT_REF
	  && DECL_C_بټ_ډګر (ونه_عملوند (توانیز_تابع, 1))
	  && BITINT_TYPE_P (DECL_بټ_ډګر_TYPE (ونه_عملوند (توانیز_تابع, 1))))
	أرجع perform_integral_promotions (orig_exp);
      أرجع perform_integral_promotions (توانیز_تابع);
    }

  أرجع توانیز_تابع;
}

/* Look up COMPONENT in a structure or union TYPE.

   If the component name is not found, returns NULL_TREE.  Otherwise,
   the return value is a TREE_LIST, with each TREE_VALUE a FIELD_DECL
   stepping down the chain to the component, which is in the last
   TREE_VALUE of the list.  Normally the list is of length one, but if
   the component is embedded within (nested) anonymous structures or
   unions, the list steps down the chain to the component.  */

ونه
lookup_ډګر (const_ونه type, ونه component)
{
  ونه ډګر_2;

  /* If TYPE_LANG_SPECIFIC is set, then it is a sorted array of pointers
     to the field elements.  Use a binary search on this array to quickly
     find the element.  Otherwise, do a linear search.  TYPE_LANG_SPECIFIC
     will always be set for structures which have many elements.

     Duplicate field checking replaces duplicates with NULL_TREE so
     TYPE_LANG_SPECIFIC arrays are potentially no longer sorted.  In that
     case just iterate using DECL_CHAIN.  */

  إذا (TYPE_LANG_SPECIFIC (type) && TYPE_LANG_SPECIFIC (type)->s
      && !کتل_شوی_error ())
    {
      صحيح bot, سر, half;
      ونه *ډګر_array = &TYPE_LANG_SPECIFIC (type)->s->elts[0];

      ډګر_2 = TYPE_FIELDS (type);
      bot = 0;
      سر = TYPE_LANG_SPECIFIC (type)->s->len;
      طالما (سر - bot > 1)
	{
	  half = (سر - bot + 1) >> 1;
	  ډګر_2 = ډګر_array[bot+half];

	  إذا (DECL_NAME (ډګر_2) == NULL_ونه)
	    {
	      /* Step through all anon unions in linear fashion.  */
	      طالما (DECL_NAME (ډګر_array[bot]) == NULL_ونه)
		{
		  ډګر_2 = ډګر_array[bot++];
		  إذا (ریکارډ_OR_UNION_TYPE_P (ونه_TYPE (ډګر_2)))
		    {
		      ونه anon = lookup_ډګر (ونه_TYPE (ډګر_2), component);

		      إذا (anon)
			أرجع ونه_cons (NULL_ونه, ډګر_2, anon);

		      /* The Plan 9 compiler permits referring
			 directly to an anonymous struct/union field
			 using a typedef name.  */
		      إذا (flag_plan9_extensions
			  && TYPE_NAME (ونه_TYPE (ډګر_2)) != NULL_ونه
			  && (ونه_کوډ (TYPE_NAME (ونه_TYPE (ډګر_2)))
			      == TYPE_DECL)
			  && (DECL_NAME (TYPE_NAME (ونه_TYPE (ډګر_2)))
			      == component))
			اكسر;
		    }
		}

	      /* Entire record is only anon unions.  */
	      إذا (bot > سر)
		أرجع NULL_ونه;

	      /* Restart the binary search, with new lower bound.  */
	      استمر;
	    }

	  إذا (DECL_NAME (ډګر_2) == component)
	    اكسر;
	  إذا (DECL_NAME (ډګر_2) < component)
	    bot += half;
	  وإلا
	    سر = bot + half;
	}

      إذا (DECL_NAME (ډګر_array[bot]) == component)
	ډګر_2 = ډګر_array[bot];
      وإلا إذا (DECL_NAME (ډګر_2) != component)
	أرجع NULL_ونه;
    }
  وإلا
    {
      لكل (ډګر_2 = TYPE_FIELDS (type); ډګر_2; ډګر_2 = DECL_CHAIN (ډګر_2))
	{
	  إذا (DECL_NAME (ډګر_2) == NULL_ونه
	      && ریکارډ_OR_UNION_TYPE_P (ونه_TYPE (ډګر_2)))
	    {
	      ونه anon = lookup_ډګر (ونه_TYPE (ډګر_2), component);

	      إذا (anon)
		أرجع ونه_cons (NULL_ونه, ډګر_2, anon);

	      /* The Plan 9 compiler permits referring directly to an
		 anonymous struct/union field using a typedef
		 name.  */
	      إذا (flag_plan9_extensions
		  && TYPE_NAME (ونه_TYPE (ډګر_2)) != NULL_ونه
		  && ونه_کوډ (TYPE_NAME (ونه_TYPE (ډګر_2))) == TYPE_DECL
		  && (DECL_NAME (TYPE_NAME (ونه_TYPE (ډګر_2)))
		      == component))
		اكسر;
	    }

	  إذا (DECL_NAME (ډګر_2) == component)
	    اكسر;
	}

      إذا (ډګر_2 == NULL_ونه)
	أرجع NULL_ونه;
    }

  أرجع ونه_cons (NULL_ونه, ډګر_2, NULL_ونه);
}

/* Recursively append candidate IDENTIFIER_NODEs to CANDIDATES.  */

ساكن فراغ
lookup_ډګر_fuzzy_پیدا_کړه_candidates (ونه type, ونه component,
				    vec<ونه> *candidates)
{
  ونه ډګر_2;
  لكل (ډګر_2 = TYPE_FIELDS (type); ډګر_2; ډګر_2 = DECL_CHAIN (ډګر_2))
    {
      إذا (DECL_NAME (ډګر_2) == NULL_ونه
	  && ریکارډ_OR_UNION_TYPE_P (ونه_TYPE (ډګر_2)))
	lookup_ډګر_fuzzy_پیدا_کړه_candidates (ونه_TYPE (ډګر_2), component,
					    candidates);

      إذا (DECL_NAME (ډګر_2))
	candidates->خوندي_ټېل (DECL_NAME (ډګر_2));
    }
}

/* Like "lookup_field", but find the closest matching IDENTIFIER_NODE,
   rather than returning a TREE_LIST for an exact match.  */

ساكن ونه
lookup_ډګر_fuzzy (ونه type, ونه component)
{
  gcc_assert (ونه_کوډ (component) == IDENTIFIER_غوټه);

  /* First, gather a list of candidates.  */
  auto_vec <ونه> candidates;

  lookup_ډګر_fuzzy_پیدا_کړه_candidates (type, component,
				      &candidates);

  أرجع پیدا_کړه_closest_identifier (component, &candidates);
}

/* Support function for build_component_ref's error-handling.

   Given DATUM_TYPE, and "DATUM.COMPONENT", where DATUM is *not* a
   struct or union, should we suggest "DATUM->COMPONENT" as a hint?  */

ساكن منطقي
should_suggest_deref_p (ونه datum_type)
{
  /* We don't do it for Objective-C, since Objective-C 2.0 dot-syntax
     allows "." for ptrs; we could be handling a failed attempt
     to access a property.  */
  إذا (c_dialect_objc ())
    أرجع خطأ;

  /* Only suggest it for pointers...  */
  إذا (ونه_کوډ (datum_type) != اشاره_ګر_TYPE)
    أرجع خطأ;

  /* ...to structs/unions.  */
  ونه underlying_type = ونه_TYPE (datum_type);
  تعداد ونه_کوډ_2 کوډ = ونه_کوډ (underlying_type);
  إذا (کوډ == ریکارډ_TYPE || کوډ == UNION_TYPE)
    أرجع ریښتیا;
  وإلا
    أرجع خطأ;
}

/* Give a component ref REF, decide whether we should handle its counted_by
   attribute based on its context:
   Do not handle counted_by when in offsetof, typeof and alignof operator.  */

ساكن منطقي
handle_counted_by_p (ونه ref)
{
  gcc_assert (ونه_کوډ (ref) == COMPONENT_REF);
  ونه datum = ونه_عملوند (ref, 0);
  /* If the component_ref is build for a offsetof, i.e., the datum
     of the component_ref is a indirect_ref of null_pointer_node,
     we should not generate call to .ACCESS_WITH_SIZE.  */
  إذا (ونه_کوډ (datum) == غیرمستقیم_REF
      && ونه_عملوند (datum, 0) == null_اشاره_ګر_غوټه)
    أرجع خطأ;
  إذا (دننه_typeof || دننه_alignof)
    أرجع خطأ;
  أرجع ریښتیا;
}

/* Given a component ref REF, if there is a counted_by attribute attached,
   issue error when the element_type is a structure or union including a
   flexible array member.  */

ساكن فراغ
check_counted_by_attribute (location_t loc, ونه ref)
{
  ونه subdatum = ونه_عملوند (ref, 1);
  ونه sub_type = ونه_TYPE (subdatum);

  إذا (!flexible_array_member_type_p (sub_type)
      && ونه_کوډ (sub_type) != اشاره_ګر_TYPE)
    أرجع;

  ونه element_type = ونه_TYPE (sub_type);

  ونه attr_counted_by = lookup_attribute ("counted_by",
					   DECL_ځانګړتیاوې (subdatum));
  إذا (attr_counted_by)
    {
      /* Issue error when the element_type is a structure or
	union including a flexible array member.  */
      إذا (ریکارډ_OR_UNION_TYPE_P (element_type)
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

ساكن ونه
build_counted_by_ref (ونه datum, ونه subdatum,
		      ونه *counted_by_type)
{
  ونه sub_type = ونه_TYPE (subdatum);
  إذا (!flexible_array_member_type_p (sub_type)
      && ونه_کوډ (sub_type) != اشاره_ګر_TYPE)
    أرجع NULL_ونه;

  ونه attr_counted_by = lookup_attribute ("counted_by",
					   DECL_ځانګړتیاوې (subdatum));
  إذا (!attr_counted_by)
    أرجع NULL_ونه;

  ونه counted_by_ref = NULL_ونه;
  *counted_by_type = NULL_ونه;

  ونه type = ونه_TYPE (datum);

  /* If the type of the containing structure is an anonymous struct/union,
     and this anonymous struct/union is not a root type, get the first
     outer named structure/union type.  */
  طالما (ونه_کوډ (datum) == COMPONENT_REF
	 && c_type_نښان (type) == NULL_ونه
	 && DECL_NAME (ونه_عملوند (datum, 1)) == NULL_ونه)
    {
      datum = ونه_عملوند (datum, 0);
      type = ونه_TYPE (datum);
    }

  ونه ډګر_id = ونه_ارزښت (ونه_ارزښت (attr_counted_by));
  ونه counted_by_ډګر = lookup_ډګر (type, ډګر_id);
  gcc_assert (counted_by_ډګر);

  ونه counted_by_subdatum;
  افعل
    {
      counted_by_subdatum = ونه_ارزښت (counted_by_ډګر);
      /* Get the TYPE of the counted_by field.  */
      *counted_by_type = ونه_TYPE (counted_by_subdatum);

      counted_by_ref
	= build3 (COMPONENT_REF, ونه_TYPE (counted_by_subdatum),
		  datum, counted_by_subdatum, NULL_ونه);

      datum = counted_by_ref;
      counted_by_ډګر = ونه_CHAIN (counted_by_ډګر);
    }
  طالما (counted_by_ډګر);

  counted_by_ref = build_fold_addr_بیان (counted_by_ref);
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
ساكن ونه
build_access_with_اندازه_for_counted_by (location_t loc, ونه ref,
				       ونه counted_by_ref,
				       ونه counted_by_type)
{
  gcc_assert (flexible_array_member_type_p (ونه_TYPE (ref))
	      || ونه_کوډ (ونه_TYPE (ref)) == اشاره_ګر_TYPE);

  منطقي is_fam = flexible_array_member_type_p (ونه_TYPE (ref));

  /* The result type of the call is a pointer to the flexible array type;
     or is the original pointer type to the pointer field with counted_by.  */
  ونه پایله_type = is_fam ? c_build_اشاره_ګر_type (ونه_TYPE (ref))
		     : ونه_TYPE (ref);

  ونه element_type = ونه_TYPE (ونه_TYPE (ref));
  ونه element_اندازه = VOID_TYPE_P (element_type)
		      ? اندازه_one_غوټه
		      : TYPE_اندازه_UNIT (element_type);
  إذا (element_اندازه == NULL_ونه)
    أرجع ref;

  ونه لومړی_param = is_fam
		     ? c_fully_fold (array_منزل_اشاره_ګر_conversion (loc, ref),
				     خطأ, عدم)
		     : c_fully_fold (ref, خطأ, عدم);
  ونه دوهم_param
    = c_fully_fold (counted_by_ref, خطأ, عدم);
  ونه دریم_param = build_int_cst (c_build_اشاره_ګر_type (counted_by_type), 0);

  ونه call
    = build_call_بیان_دننی_loc (loc, IFN_ACCESS_WITH_اندازه,
				    پایله_type, 4,
				    لومړی_param,
				    دوهم_param,
				    دریم_param,
				    element_اندازه);

  /* Wrap the call with an INDIRECT_REF with the flexible array type.  */
  إذا (is_fam)
    call = build1 (غیرمستقیم_REF, ونه_TYPE (ref), call);
  سېټ_بیان_LOCATION (call, loc);
  أرجع call;
}

/* For the COMPONENT_REF ref, check whether it has a counted_by attribute,
   if so, wrap this COMPONENT_REF with the corresponding CALL to the
   function .ACCESS_WITH_SIZE.
   Otherwise, return the ref itself.  */

ونه
handle_counted_by_for_component_ref (location_t loc, ونه ref)
{
  gcc_assert (ونه_کوډ (ref) == COMPONENT_REF);
  ونه datum = ونه_عملوند (ref, 0);
  ونه subdatum = ونه_عملوند (ref, 1);
  ونه counted_by_type = NULL_ونه;

  إذا (!(flexible_array_member_type_p (ونه_TYPE (ref))
	|| ونه_کوډ (ونه_TYPE (ref)) == اشاره_ګر_TYPE))
    أرجع ref;

  ونه counted_by_ref = build_counted_by_ref (datum, subdatum,
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

ونه
build_component_ref (location_t loc, ونه datum, ونه component,
		     location_t component_loc, location_t arrow_loc)
{
  ونه type = ونه_TYPE (datum);
  تعداد ونه_کوډ_2 کوډ = ونه_کوډ (type);
  ونه ډګر_2 = عدم;
  ونه ref;
  منطقي datum_lvalue = lvalue_p (datum);

  إذا (!objc_is_عامه (datum, component))
    أرجع error_mark_غوټه;

  /* Detect Objective-C property syntax object.property.  */
  إذا (c_dialect_objc ()
      && (ref = objc_maybe_build_component_ref (datum, component)))
    أرجع ref;

  /* See if there is a field or component with name COMPONENT.  */

  إذا (کوډ == ریکارډ_TYPE || کوډ == UNION_TYPE)
    {
      إذا (!COMPLETE_TYPE_P (type))
	{
	  c_incomplete_type_error (loc, NULL_ونه, type);
	  أرجع error_mark_غوټه;
	}

      ډګر_2 = lookup_ډګر (type, component);

      إذا (!ډګر_2)
	{
	  ونه guessed_id = lookup_ډګر_fuzzy (type, component);
	  إذا (guessed_id)
	    {
	      /* Attempt to provide a fixit replacement hint, if
		 we have a valid range for the component.  */
	      location_t reported_loc
		= (component_loc != UNKNOWN_LOCATION) ? component_loc : loc;
	      gcc_rich_location rich_loc (reported_loc);
	      إذا (component_loc != UNKNOWN_LOCATION)
		rich_loc.جمع_کړه_fixit_misspelled_id (component_loc, guessed_id);
	      error_at (&rich_loc,
			"%qT has no member named %qE; did you mean %qE?",
			type, component, guessed_id);
	    }
	  وإلا
	    error_at (loc, "%qT has no member named %qE", type, component);
	  أرجع error_mark_غوټه;
	}

      /* Accessing elements of atomic structures or unions is undefined
	 behavior (C11 6.5.2.3#5).  */
      إذا (TYPE_ATOMIC (type) && c_inhibit_evaluation_warnings == 0)
	{
	  إذا (کوډ == ریکارډ_TYPE)
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
	  ونه subdatum = ونه_ارزښت (ډګر_2);
	  صحيح quals;
	  ونه subtype;
	  منطقي use_datum_quals;

	  إذا (ونه_TYPE (subdatum) == error_mark_غوټه)
	    أرجع error_mark_غوټه;

	  /* If this is an rvalue, it does not have qualifiers in C
	     standard terms and we must avoid propagating such
	     qualifiers down to a non-lvalue array that is then
	     converted to a pointer.  */
	  use_datum_quals = (datum_lvalue
			     || ونه_کوډ (ونه_TYPE (subdatum)) != ARRAY_TYPE);

	  quals = TYPE_QUALS (strip_array_types (ونه_TYPE (subdatum)));
	  إذا (use_datum_quals)
	    quals |= TYPE_QUALS (ونه_TYPE (datum));
	  subtype = c_build_qualified_type (ونه_TYPE (subdatum), quals);

	  ref = build3 (COMPONENT_REF, subtype, datum, subdatum,
			NULL_ونه);
	  سېټ_بیان_LOCATION (ref, loc);

	  check_counted_by_attribute (loc, ref);

	  إذا (ونه_READONLY (subdatum)
	      || (use_datum_quals && ونه_READONLY (datum)))
	    ونه_READONLY (ref) = 1;
	  إذا (ونه_THIS_VOLATILE (subdatum)
	      || (use_datum_quals && ونه_THIS_VOLATILE (datum)))
	    ونه_THIS_VOLATILE (ref) = 1;

	  إذا (ونه_UNAVAILABLE (subdatum))
	    error_unavailable_use (subdatum, NULL_ونه);
	  وإلا إذا (ونه_DEPRECATED (subdatum))
	    warn_deprecated_use (subdatum, NULL_ونه);

	  datum = ref;

	  ډګر_2 = ونه_CHAIN (ډګر_2);
	}
      طالما (ډګر_2);

      أرجع ref;
    }
  وإلا إذا (should_suggest_deref_p (type))
    {
      /* Special-case the error message for "ptr.field" for the case
	 where the user has confused "." vs "->".  */
      rich_location richloc (کرښه_جدول, loc);
      إذا (غیرمستقیم_REF_P (datum) && arrow_loc != UNKNOWN_LOCATION)
	{
	  richloc.جمع_کړه_fixit_ورننباسه_before (arrow_loc, "(*");
	  richloc.جمع_کړه_fixit_ورننباسه_after (arrow_loc, ")");
	  error_at (&richloc,
		    "%qE is a pointer to pointer; did you mean to dereference "
		    "it before applying %<->%> to it?",
		    ونه_عملوند (datum, 0));
	}
      وإلا
	{
	  /* "loc" should be the "." token.  */
	  richloc.جمع_کړه_fixit_replace ("->");
	  error_at (&richloc,
		    "%qE is a pointer; did you mean to use %<->%>?",
		    datum);
	}
      أرجع error_mark_غوټه;
    }
  وإلا إذا (کوډ != ERROR_MARK)
    error_at (loc,
	      "request for member %qE in something not a structure or union",
	      component);

  أرجع error_mark_غوټه;
}

/* Given an expression PTR for a pointer, return an expression
   for the value pointed to.
   ERRORSTRING is the name of the operator to appear in error messages.

   LOC is the location to use for the generated tree.  */

ونه
build_غیرمستقیم_ref (location_t loc, ونه ptr, ref_operator errstring)
{
  ونه اشاره_ګر = default_conversion (ptr);
  ونه type = ونه_TYPE (اشاره_ګر);
  ونه ref;

  إذا (ونه_کوډ (type) == اشاره_ګر_TYPE)
    {
      إذا (CONVERT_بیان_P (اشاره_ګر)
          || ونه_کوډ (اشاره_ګر) == VIEW_CONVERT_بیان)
	{
	  /* If a warning is issued, mark it to avoid duplicates from
	     the backend.  This only needs to be done at
	     warn_strict_aliasing > 2.  */
	  إذا (warn_strict_aliasing > 2)
	    إذا (strict_aliasing_warning (بیان_LOCATION (اشاره_ګر),
					 type, ونه_عملوند (اشاره_ګر, 0)))
	      suppress_warning (اشاره_ګر, OPT_Wstrict_aliasing_);
	}

      إذا (ونه_کوډ (اشاره_ګر) == ADDR_بیان
	  && (ونه_TYPE (ونه_عملوند (اشاره_ګر, 0))
	      == ونه_TYPE (type)))
	{
	  ref = ونه_عملوند (اشاره_ګر, 0);
	  protected_سېټ_بیان_location (ref, loc);
	  أرجع ref;
	}
      وإلا
	{
	  ونه t = ونه_TYPE (type);

	  ref = build1 (غیرمستقیم_REF, t, اشاره_ګر);

	  إذا (VOID_TYPE_P (t) && c_inhibit_evaluation_warnings == 0)
	    warning_at (loc, 0, "dereferencing %<void *%> pointer");

	  /* We *must* set TREE_READONLY when dereferencing a pointer to const,
	     so that we get the proper error message if the result is used
	     to assign to.  Also, &* is supposed to be a no-op.
	     And ANSI C seems to specify that the type of the result
	     should be the const type.  */
	  /* A de-reference of a pointer to const is not a const.  It is valid
	     to change it via some other pointer.  */
	  ونه_READONLY (ref) = TYPE_READONLY (t);
	  ونه_SIDE_EFFECTS (ref)
	    = TYPE_VOLATILE (t) || ونه_SIDE_EFFECTS (اشاره_ګر);
	  ونه_THIS_VOLATILE (ref) = TYPE_VOLATILE (t);
	  protected_سېټ_بیان_location (ref, loc);
	  أرجع ref;
	}
    }
  وإلا إذا (ونه_کوډ (اشاره_ګر) != ERROR_MARK)
    invalid_indirection_error (loc, type, errstring);

  أرجع error_mark_غوټه;
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

ونه
build_array_ref (location_t loc, ونه array, ونه شاخص)
{
  ونه ret;
  منطقي swapped = خطأ;
  إذا (ونه_TYPE (array) == error_mark_غوټه
      || ونه_TYPE (شاخص) == error_mark_غوټه)
    أرجع error_mark_غوټه;

  إذا (ونه_کوډ (ونه_TYPE (array)) != ARRAY_TYPE
      && ونه_کوډ (ونه_TYPE (array)) != اشاره_ګر_TYPE
      /* Allow vector[index] but not index[vector].  */
      && !gnu_ویکټور_type_p (ونه_TYPE (array)))
    {
      إذا (ونه_کوډ (ونه_TYPE (شاخص)) != ARRAY_TYPE
	  && ونه_کوډ (ونه_TYPE (شاخص)) != اشاره_ګر_TYPE)
	{
          error_at (loc,
            "subscripted value is neither array nor pointer nor vector");

	  أرجع error_mark_غوټه;
	}
      std::بدلون (array, شاخص);
      swapped = ریښتیا;
    }

  إذا (!INTEGRAL_TYPE_P (ونه_TYPE (شاخص)))
    {
      error_at (loc, "array subscript is not an integer");
      أرجع error_mark_غوټه;
    }

  إذا (ونه_کوډ (ونه_TYPE (ونه_TYPE (array))) == FUNCTION_TYPE)
    {
      error_at (loc, "subscripted value is pointer to function");
      أرجع error_mark_غوټه;
    }

  /* ??? Existing practice has been to warn only when the char
     index is syntactically the index, not for char[array].  */
  إذا (!swapped)
     warn_array_subscript_with_type_char (loc, شاخص);

  /* Apply default promotions *after* noticing character types.  */
  شاخص = default_conversion (شاخص);
  إذا (شاخص == error_mark_غوټه)
    أرجع error_mark_غوټه;

  gcc_assert (ونه_کوډ (ونه_TYPE (شاخص)) == INTEGER_TYPE
	      || ونه_کوډ (ونه_TYPE (شاخص)) == BITINT_TYPE);

  منطقي was_ویکټور = ویکټور_TYPE_P (ونه_TYPE (array));
  منطقي non_lvalue = convert_ویکټور_منزل_array_for_subscript (loc, &array, شاخص);

  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  إذا (ونه_کوډ (array) == COMPONENT_REF
      && handle_counted_by_p (array))
    array = handle_counted_by_for_component_ref (loc, array);

  إذا (ونه_کوډ (ونه_TYPE (array)) == ARRAY_TYPE)
    {
      ونه rval, type;

      /* An array that is indexed by a non-constant
	 cannot be stored in a register; we must be able to do
	 address arithmetic on its address.
	 Likewise an array of elements of variable size.  */
      إذا (ونه_کوډ (شاخص) != INTEGER_CST
	  || (COMPLETE_TYPE_P (ونه_TYPE (ونه_TYPE (array)))
	      && ونه_کوډ (TYPE_اندازه (ونه_TYPE (ونه_TYPE (array)))) != INTEGER_CST))
	{
	  إذا (!c_mark_addressable (array, ریښتیا, ریښتیا))
	    أرجع error_mark_غوټه;
	}
      /* An array that is indexed by a constant value which is not within
	 the array bounds cannot be stored in a register either; because we
	 would get a crash in store_bit_field/extract_bit_field when trying
	 to access a non-existent part of the register.  */
      إذا (ونه_کوډ (شاخص) == INTEGER_CST
	  && TYPE_DOMAIN (ونه_TYPE (array))
	  && !int_ځاییږي_type_p (شاخص, TYPE_DOMAIN (ونه_TYPE (array))))
	{
	  إذا (!c_mark_addressable (array, خطأ, ریښتیا))
	    أرجع error_mark_غوټه;
	  /* ISO C2Y disallows a negative integer constant expression index
	     when array subscripting has an operand of array type.  */
	  إذا (flag_isoc2y
	      && !ونه_ډکېدنه (شاخص)
	      && ونه_int_cst_sgn (شاخص) < 0)
	    error_at (loc, "array subscript is negative");
	}

      إذا ((pedantic || warn_c90_c99_compat || warn_c23_c2y_compat)
	  && ! was_ویکټور)
	{
	  ونه foo = array;
	  طالما (ونه_کوډ (foo) == COMPONENT_REF)
	    foo = ونه_عملوند (foo, 0);
	  إذا ((VAR_P (foo) && C_DECL_ثبتوونکی (foo))
	      || (ونه_کوډ (foo) == COMPOUND_LITERAL_بیان
		  && C_DECL_ثبتوونکی (COMPOUND_LITERAL_بیان_DECL (foo))))
	    pedwarn_c23 (loc, OPT_Wpedantic,
			 "ISO C forbids subscripting %<register%> array "
			 "before C2Y");
	  وإلا إذا (!lvalue_p (foo))
	    pedwarn_c90 (loc, OPT_Wpedantic,
			 "ISO C90 forbids subscripting non-lvalue "
			 "array");
	}

      إذا (ونه_کوډ (ونه_TYPE (شاخص)) == BITINT_TYPE
	  && TYPE_PRECISION (ونه_TYPE (شاخص)) > TYPE_PRECISION (sizetype))
	شاخص = fold_convert (sizetype, شاخص);

      type = ونه_TYPE (ونه_TYPE (array));
      rval = build4 (ARRAY_REF, type, array, شاخص, NULL_ونه, NULL_ونه);
      /* Array ref is const/volatile if the array elements are
	 or if the array is.  */
      ونه_READONLY (rval)
	|= (TYPE_READONLY (ونه_TYPE (ونه_TYPE (array)))
	    | ونه_READONLY (array));
      ونه_SIDE_EFFECTS (rval)
	|= (TYPE_VOLATILE (ونه_TYPE (ونه_TYPE (array)))
	    | ونه_SIDE_EFFECTS (array));
      ونه_THIS_VOLATILE (rval)
	|= (TYPE_VOLATILE (ونه_TYPE (ونه_TYPE (array)))
	    /* This was added by rms on 16 Nov 91.
	       It fixes  vol struct foo *a;  a->elts[1]
	       in an inline function.
	       Hope it doesn't break something else.  */
	    | ونه_THIS_VOLATILE (array));
      ret = require_complete_type (loc, rval);
      protected_سېټ_بیان_location (ret, loc);
      إذا (non_lvalue)
	ret = non_lvalue_loc (loc, ret);
      أرجع ret;
    }
  وإلا
    {
      ونه ar = default_conversion (array);

      إذا (ar == error_mark_غوټه)
	أرجع ar;

      gcc_assert (ونه_کوډ (ونه_TYPE (ar)) == اشاره_ګر_TYPE);
      gcc_assert (ونه_کوډ (ونه_TYPE (ونه_TYPE (ar))) != FUNCTION_TYPE);

      ret = build_غیرمستقیم_ref (loc, build_دوګونی_op (loc, PLUS_بیان, ar,
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

ونه
build_omp_array_section (location_t loc, ونه array, ونه شاخص, ونه اوږدتیا)
{
  ونه type = ونه_TYPE (array);
  gcc_assert (type);

  ونه sectype, eltype = ونه_TYPE (type);

  /* It's not an array or pointer type.  Just reuse the type of the original
     expression as the type of the array section (an error will be raised
     anyway, later).  */
  إذا (eltype == NULL_ونه || error_عملوند_p (eltype))
    sectype = ونه_TYPE (array);
  وإلا
    {
      ونه idxtype = NULL_ونه;

      إذا (شاخص != NULL_ونه
	  && اوږدتیا != NULL_ونه
	  && INTEGRAL_TYPE_P (ونه_TYPE (شاخص))
	  && INTEGRAL_TYPE_P (ونه_TYPE (اوږدتیا)))
	{
	  ونه ټیټ = fold_convert (sizetype, شاخص);
	  ونه لوړ = fold_convert (sizetype, اوږدتیا);
	  لوړ = اندازه_binop (PLUS_بیان, ټیټ, لوړ);
	  لوړ = اندازه_binop (MINUS_بیان, لوړ, اندازه_one_غوټه);
	  idxtype = build_range_type (sizetype, ټیټ, لوړ);
	}
      وإلا إذا ((شاخص == NULL_ونه || integer_zerop (شاخص))
	       && اوږدتیا != NULL_ونه
	       && INTEGRAL_TYPE_P (ونه_TYPE (اوږدتیا)))
	idxtype = build_شاخص_type (اوږدتیا);

      gcc_assert (!error_عملوند_p (idxtype));

      sectype = c_build_array_type (eltype, idxtype);
    }

  أرجع build3_loc (loc, OMP_ARRAY_SECTION, sectype, array, شاخص, اوږدتیا);
}


/* Record that REF is used.  This is relevant for undeclared static
   function and declarations referenced from a non-local context.
   ADDRESS indicates whether the address is taken.  */

فراغ
mark_decl_کارول_شوی (ونه ref, منطقي پته)
{
  إذا (!ref || !DECL_P (ref) || دننه_alignof)
    أرجع;

  /* Non-file-scope and non-local reference in nested function.  */
  منطقي nonloc_p = current_function_decl && DECL_CONTEXT (ref)
		  && DECL_CONTEXT (current_function_decl)
		  && DECL_CONTEXT (ref) != current_function_decl;

  /* An undeclared static function.  */
  منطقي static_p = ونه_کوډ (ref) == FUNCTION_DECL
		  && DECL_INITIAL (ref) == NULL_ونه
		  && DECL_EXTERNAL (ref)
		  && !ونه_عامه (ref);

  إذا (!static_p && !nonloc_p)
    أرجع;

  /* If we may be in an unevaluated context, delay the decision.  */
  إذا (دننه_sizeof || دننه_typeof || دننه_countof || دننه_generic)
    أرجع ریکارډ_maybe_کارول_شوی_decl (ref, پته);

  إذا (static_p)
    C_DECL_کارول_شوی (ref) = 1;

  إذا (nonloc_p && (VAR_OR_FUNCTION_DECL_P (ref)
		   || ونه_کوډ (ref) == PARM_DECL))
    DECL_NONLOCAL (ref) = 1;

  /* Nothing to do anymore.  */
  إذا (!nonloc_p || C_FUNC_NONLOCAL_CONTEXT (current_function_decl))
    أرجع;

  /* Filter out the cases where referencing a non-local variable does not
     require a non-local context passed via the static chain.  */
  إذا (!c_type_variably_modified_p (ونه_TYPE (ref)))
    بدل (ونه_کوډ (ref))
      {
      حالة FUNCTION_DECL:
	/* Use of another local function that requires no context is ok.  */
	إذا (!C_FUNC_NONLOCAL_CONTEXT (ref) && DECL_INITIAL (ref))
	  أرجع;
	اكسر;
      حالة VAR_DECL:
	/* Static variables and constexpr are ok, but for the later only
	   when the address is not taken.  */
	إذا (ونه_STATIC (ref) || (C_DECL_DECLARED_CONSTEXPR (ref) && !پته))
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
  لكل (ونه cont = current_function_decl; cont; cont = DECL_CONTEXT (cont))
    {
      إذا (cont == DECL_CONTEXT (ref))
	اكسر;

      /* There should not be any other type of context used for function
	 except TRANSLATION_UNIT_DECL which we should be able to reach.  */
      gcc_checking_assert (ونه_کوډ (cont) == FUNCTION_DECL);

      إذا (ونه_کوډ (cont) == FUNCTION_DECL)
	C_FUNC_NONLOCAL_CONTEXT (cont) = 1;
    }
}


/* Build an external reference to identifier ID.  FUN indicates
   whether this will be used for a function call.  LOC is the source
   location of the identifier.  This sets *TYPE to the type of the
   identifier, which is not the same as the type of the returned value
   for CONST_DECLs defined as enum constants.  If the type of the
   identifier is not available, *TYPE is set to NULL.  */
ونه
build_external_ref (location_t loc, ونه id, منطقي fun, ونه *type)
{
  ونه ref;
  ونه decl = lookup_name (id);

  /* In Objective-C, an instance variable (ivar) may be preferred to
     whatever lookup_name() found.  */
  decl = objc_lookup_ivar (decl, id);

  *type = عدم;
  إذا (decl && decl != error_mark_غوټه)
    {
      ref = decl;
      *type = ونه_TYPE (ref);
      إذا (DECL_P (decl) && C_DECL_UNDERSPECIFIED (decl))
	error_at (loc, "underspecified %qD referenced in its initializer",
		  decl);
    }
  وإلا إذا (fun)
    /* Implicit function declaration.  */
    ref = implicitly_declare (loc, id);
  وإلا إذا (decl == error_mark_غوټه)
    /* Don't complain about something that's already been
       complained about.  */
    أرجع error_mark_غوټه;
  وإلا
    {
      undeclared_variable (loc, id);
      أرجع error_mark_غوټه;
    }

  /* For an OpenMP map clause, we can get better diagnostics for decls with
     unmappable types if we return the decl with an error_mark_node type,
     rather than returning error_mark_node for the decl itself.  */
  إذا (ونه_TYPE (ref) == error_mark_غوټه
      && !c_omp_array_section_p)
    أرجع error_mark_غوټه;

  إذا (ونه_UNAVAILABLE (ref))
    error_unavailable_use (ref, NULL_ونه);
  وإلا إذا (ونه_DEPRECATED (ref))
    warn_deprecated_use (ref, NULL_ونه);

  /* Recursive call does not count as usage.  */
  إذا (ref != current_function_decl)
    {
      ونه_کارول_شوی (ref) = 1;
    }

  mark_decl_کارول_شوی (ref, خطأ);

  إذا (ونه_کوډ (ref) == CONST_DECL)
    {
      کارول_شوی_types_ورننباسه (ونه_TYPE (ref));

      إذا (warn_cxx_compat
	  && ونه_کوډ (ونه_TYPE (ref)) == ENUMERAL_TYPE
	  && C_TYPE_DEFINED_دننه_STRUCT (ونه_TYPE (ref)))
	{
	  warning_at (loc, OPT_Wc___compat,
		      "enum constant defined in struct or union "
		      "is not visible in C++");
	  inform (DECL_سرچینه_LOCATION (ref), "enum constant defined here");
	}

      ref = DECL_INITIAL (ref);
      ونه_CONSTANT (ref) = 1;
    }
  /* C99 6.7.4p3: An inline definition of a function with external
     linkage ... shall not contain a reference to an identifier with
     internal linkage.  */
  وإلا إذا (current_function_decl != NULL_ونه
	   && DECL_DECLARED_INLINE_P (current_function_decl)
	   && DECL_EXTERNAL (current_function_decl)
	   && VAR_OR_FUNCTION_DECL_P (ref)
	   && (!VAR_P (ref) || ونه_STATIC (ref))
	   && ! ونه_عامه (ref)
	   && DECL_CONTEXT (ref) != current_function_decl)
    ریکارډ_inline_static (loc, current_function_decl, ref,
			  csi_دننی);

  أرجع ref;
}

ساكن بنية maybe_کارول_شوی_decl *maybe_کارول_شوی_decls;

/* Record that DECL, a reference seen inside sizeof or typeof or _Countof or
   _Generic, might be used if the operand of sizeof is a VLA type or the
   operand of typeof is a variably modified type or the operand of _Countof has
   a variable number of elements or the operand of _Generic is the one selected
   as the result.  */

ساكن فراغ
ریکارډ_maybe_کارول_شوی_decl (ونه decl, منطقي پته)
{
  بنية maybe_کارول_شوی_decl *t = XOBNEW (&parser_obstack, بنية maybe_کارول_شوی_decl);
  t->decl = decl;
  t->level = دننه_sizeof + دننه_typeof + دننه_countof + دننه_generic;
  t->پته = پته;
  t->بل = maybe_کارول_شوی_decls;
  maybe_کارول_شوی_decls = t;
}

/* Pop the stack of decls possibly used inside sizeof or typeof or _Countof or
   _Generic.  If USED is false, just discard them.  If it is true, mark them
   used (if no longer inside sizeof or typeof or _Countof or _Generic) or move
   them to the next level up (if still inside sizeof or typeof or _Countof or
   _Generic).  */

فراغ
راوباسه_maybe_کارول_شوی (منطقي کارول_شوی)
{
  بنية maybe_کارول_شوی_decl *p = maybe_کارول_شوی_decls;
  صحيح cur_level = دننه_sizeof + دننه_typeof + دننه_countof + دننه_generic;
  طالما (p && p->level > cur_level)
    {
      إذا (کارول_شوی)
	{
	  إذا (cur_level == 0)
	    mark_decl_کارول_شوی (p->decl, p->پته);
	  وإلا
	    p->level = cur_level;
	}
      p = p->بل;
    }
  إذا (!کارول_شوی || cur_level == 0)
    maybe_کارول_شوی_decls = p;
}

/* Pop the stack of decls possibly used inside sizeof or typeof or _Countof or
   _Generic, without acting on them, and return the pointer to the previous top
   of the stack.  This for use at the end of a default generic association when
   it is not yet known whether the expression is used.  If it later turns out
   the expression is used (or treated as used before C23), restore_maybe_used
   should be called on the return value followed by pop_maybe_used (true);
   otherwise, the return value can be discarded.  */

بنية maybe_کارول_شوی_decl *
save_maybe_کارول_شوی ()
{
  بنية maybe_کارول_شوی_decl *p = maybe_کارول_شوی_decls, *orig = p;
  صحيح cur_level = دننه_sizeof + دننه_typeof + دننه_countof + دننه_generic;
  طالما (p && p->level > cur_level)
    p = p->بل;
  maybe_کارول_شوی_decls = p;
  أرجع orig;
}

/* Restore the stack of decls possibly used inside sizeof or typeof or _Countof
   or _Generic returned by save_maybe_used.  It is required that the stack is
   at exactly the point where it was left by save_maybe_used.  */

فراغ
restore_maybe_کارول_شوی (بنية maybe_کارول_شوی_decl *ډېری)
{
  maybe_کارول_شوی_decls = ډېری;
}

/* Return the result of sizeof applied to EXPR.  */

بنية c_بیان
c_بیان_sizeof_بیان (location_t loc, بنية c_بیان بیان)
{
  بنية c_بیان ret;
  إذا (بیان.ارزښت == error_mark_غوټه)
    {
      ret.ارزښت = error_mark_غوټه;
      ret.original_کوډ = ERROR_MARK;
      ret.original_type = عدم;
      ret.m_decimal = 0;
      راوباسه_maybe_کارول_شوی (خطأ);
    }
  وإلا
    {
      منطقي بیان_const_operands = ریښتیا;

      إذا (ونه_کوډ (بیان.ارزښت) == PARM_DECL
	  && C_ARRAY_PARAMETER (بیان.ارزښت))
	{
	  auto_diagnostic_ډله d;
	  إذا (warning_at (loc, OPT_Wsizeof_array_دلیل,
			  "%<sizeof%> on array function parameter %qE will "
			  "return size of %qT", بیان.ارزښت,
			  ونه_TYPE (بیان.ارزښت)))
	    inform (DECL_سرچینه_LOCATION (بیان.ارزښت), "declared here");
	}
      ونه folded_بیان = c_fully_fold (بیان.ارزښت, require_constant_ارزښت,
				       &بیان_const_operands);
      ret.ارزښت = c_sizeof (loc, ونه_TYPE (folded_بیان));
      c_وروستی_sizeof_arg = بیان.ارزښت;
      c_وروستی_sizeof_loc = loc;
      ret.original_کوډ = SIZEOF_بیان;
      ret.original_type = عدم;
      ret.m_decimal = 0;
      إذا (C_TYPE_VARIABLE_اندازه (ونه_TYPE (folded_بیان)))
	{
	  /* sizeof is evaluated when given a vla (C99 6.5.3.4p2).  */
	  ret.ارزښت = build2 (C_MAYBE_CONST_بیان, ونه_TYPE (ret.ارزښت),
			      folded_بیان, ret.ارزښت);
	  C_MAYBE_CONST_بیان_NON_CONST (ret.ارزښت) = !بیان_const_operands;
	  سېټ_بیان_LOCATION (ret.ارزښت, loc);
	}
      راوباسه_maybe_کارول_شوی (C_TYPE_VARIABLE_اندازه (ونه_TYPE (folded_بیان)));
    }
  أرجع ret;
}

/* Return the result of sizeof applied to T, a structure for the type
   name passed to sizeof (rather than the type itself).  LOC is the
   location of the original expression.  */

بنية c_بیان
c_بیان_sizeof_type (location_t loc, بنية c_type_name *t)
{
  ونه type;
  بنية c_بیان ret;
  ونه type_بیان = NULL_ونه;
  منطقي type_بیان_const = ریښتیا;
  type = groktypename (t, &type_بیان, &type_بیان_const);
  ret.ارزښت = c_sizeof (loc, type);
  c_وروستی_sizeof_arg = type;
  c_وروستی_sizeof_loc = loc;
  ret.original_کوډ = SIZEOF_بیان;
  ret.original_type = عدم;
  ret.m_decimal = 0;
  إذا (type == error_mark_غوټه)
    {
      ret.ارزښت = error_mark_غوټه;
      ret.original_کوډ = ERROR_MARK;
    }
  وإلا
  إذا ((type_بیان || ونه_کوډ (ret.ارزښت) == INTEGER_CST)
      && C_TYPE_VARIABLE_اندازه (type))
    {
      /* If the type is a [*] array, it is a VLA but is represented as
	 having a size of zero.  In such a case we must ensure that
	 the result of sizeof does not get folded to a constant by
	 c_fully_fold, because if the size is evaluated the result is
	 not constant and so constraints on zero or negative size
	 arrays must not be applied when this sizeof call is inside
	 another array declarator.  */
      إذا (!type_بیان)
	type_بیان = integer_zero_غوټه;
      ret.ارزښت = build2 (C_MAYBE_CONST_بیان, ونه_TYPE (ret.ارزښت),
			  type_بیان, ret.ارزښت);
      C_MAYBE_CONST_بیان_NON_CONST (ret.ارزښت) = !type_بیان_const;
    }
  راوباسه_maybe_کارول_شوی (type != error_mark_غوټه
		  ? C_TYPE_VARIABLE_اندازه (type) : خطأ);
  أرجع ret;
}

ساكن منطقي
سر_array_vla_p (const_ونه type)
{
  إذا (ونه_کوډ (type) != ARRAY_TYPE)
    أرجع خطأ;

  ونه d = TYPE_DOMAIN (type);

  إذا (!d)
    أرجع خطأ;
  إذا (!TYPE_MAX_ارزښت (d))
    أرجع خطأ;

  أرجع ونه_کوډ (TYPE_MAX_ارزښت (d)) != INTEGER_CST
	 || ونه_کوډ (TYPE_MIN_ارزښت (d)) != INTEGER_CST;
}

/* Return the result of countof applied to EXPR.  */

بنية c_بیان
c_بیان_countof_بیان (location_t loc, بنية c_بیان بیان)
{
  بنية c_بیان ret;
  إذا (بیان.ارزښت == error_mark_غوټه)
    {
      ret.ارزښت = error_mark_غوټه;
      ret.original_کوډ = ERROR_MARK;
      ret.original_type = عدم;
      ret.m_decimal = 0;
      راوباسه_maybe_کارول_شوی (خطأ);
    }
  وإلا
    {
      منطقي بیان_const_operands = ریښتیا;

      ونه folded_بیان = c_fully_fold (بیان.ارزښت, require_constant_ارزښت,
				       &بیان_const_operands);
      ret.ارزښت = c_countof_type (loc, ونه_TYPE (folded_بیان));
      c_وروستی_sizeof_arg = بیان.ارزښت;
      c_وروستی_sizeof_loc = loc;
      ret.original_کوډ = COUNTOF_بیان;
      ret.original_type = عدم;
      ret.m_decimal = 0;
      إذا (سر_array_vla_p (ونه_TYPE (folded_بیان)))
	{
	  /* countof is evaluated when given a vla.  */
	  ret.ارزښت = build2 (C_MAYBE_CONST_بیان, ونه_TYPE (ret.ارزښت),
			      folded_بیان, ret.ارزښت);
	  C_MAYBE_CONST_بیان_NON_CONST (ret.ارزښت) = !بیان_const_operands;
	  سېټ_بیان_LOCATION (ret.ارزښت, loc);
	}
      راوباسه_maybe_کارول_شوی (سر_array_vla_p (ونه_TYPE (folded_بیان)));
    }
  أرجع ret;
}

/* Return the result of countof applied to T, a structure for the type
   name passed to countof (rather than the type itself).  LOC is the
   location of the original expression.  */

بنية c_بیان
c_بیان_countof_type (location_t loc, بنية c_type_name *t)
{
  ونه type;
  بنية c_بیان ret;
  ونه type_بیان = NULL_ونه;
  منطقي type_بیان_const = ریښتیا;
  type = groktypename (t, &type_بیان, &type_بیان_const);
  ret.ارزښت = c_countof_type (loc, type);
  c_وروستی_sizeof_arg = type;
  c_وروستی_sizeof_loc = loc;
  ret.original_کوډ = COUNTOF_بیان;
  ret.original_type = عدم;
  ret.m_decimal = 0;
  إذا (type == error_mark_غوټه)
    {
      ret.ارزښت = error_mark_غوټه;
      ret.original_کوډ = ERROR_MARK;
    }
  وإلا
  إذا ((type_بیان || ونه_کوډ (ret.ارزښت) == INTEGER_CST)
      && سر_array_vla_p (type))
    {
      /* If the type is a [*] array, it is a VLA but is represented as
	 having a size of zero.  In such a case we must ensure that
	 the result of countof does not get folded to a constant by
	 c_fully_fold, because if the number of elements is evaluated
	 the result is not constant and so
	 constraints on zero or negative size arrays must not be applied
	 when this countof call is inside another array declarator.  */
      إذا (!type_بیان)
	type_بیان = integer_zero_غوټه;
      ret.ارزښت = build2 (C_MAYBE_CONST_بیان, ونه_TYPE (ret.ارزښت),
			  type_بیان, ret.ارزښت);
      C_MAYBE_CONST_بیان_NON_CONST (ret.ارزښت) = !type_بیان_const;
    }
  راوباسه_maybe_کارول_شوی (type != error_mark_غوټه ? سر_array_vla_p (type) : خطأ);
  أرجع ret;
}

/* Return the result of maxof applied to T, a structure for the type
   name passed to maxof (rather than the type itself).  LOC is the
   location of the original expression.  */

بنية c_بیان
c_بیان_maxof_type (location_t loc, بنية c_type_name *t)
{
  ونه type;
  بنية c_بیان ret;
  ونه type_بیان = NULL_ونه;
  منطقي type_بیان_const = ریښتیا;
  type = groktypename (t, &type_بیان, &type_بیان_const);
  ret.ارزښت = c_maxof_type (loc, type);
  c_وروستی_sizeof_arg = type;
  c_وروستی_sizeof_loc = loc;
  ret.original_کوډ = MAXOF_بیان;
  ret.original_type = عدم;
  ret.m_decimal = 0;
  إذا (type == error_mark_غوټه)
    {
      ret.ارزښت = error_mark_غوټه;
      ret.original_کوډ = ERROR_MARK;
    }
  راوباسه_maybe_کارول_شوی (type != error_mark_غوټه);
  أرجع ret;
}

/* Return the result of minof applied to T, a structure for the type
   name passed to minof (rather than the type itself).  LOC is the
   location of the original expression.  */

بنية c_بیان
c_بیان_minof_type (location_t loc, بنية c_type_name *t)
{
  ونه type;
  بنية c_بیان ret;
  ونه type_بیان = NULL_ونه;
  منطقي type_بیان_const = ریښتیا;
  type = groktypename (t, &type_بیان, &type_بیان_const);
  ret.ارزښت = c_minof_type (loc, type);
  c_وروستی_sizeof_arg = type;
  c_وروستی_sizeof_loc = loc;
  ret.original_کوډ = MINOF_بیان;
  ret.original_type = عدم;
  ret.m_decimal = 0;
  إذا (type == error_mark_غوټه)
    {
      ret.ارزښت = error_mark_غوټه;
      ret.original_کوډ = ERROR_MARK;
    }
  راوباسه_maybe_کارول_شوی (type != error_mark_غوټه);
  أرجع ret;
}

/* Build a function call to function FUNCTION with parameters PARAMS.
   The function call is at LOC.
   PARAMS is a list--a chain of TREE_LIST nodes--in which the
   TREE_VALUE of each node is a parameter-expression.
   FUNCTION's data type may be a function type or a pointer-to-function.  */

ونه
build_function_call (location_t loc, ونه function, ونه params)
{
  vec<ونه, va_gc> *v;
  ونه ret;

  vec_alloc (v, list_اوږدتیا (params));
  لكل (; params; params = ونه_CHAIN (params))
    v->چټک_ټېل (ونه_ارزښت (params));
  ret = c_build_function_call_vec (loc, vNULL, function, v, عدم);
  vec_free (v);
  أرجع ret;
}

/* Give a note about the location of the declaration of DECL,
   or, failing that, a pertinent declaration for FUNCTION_EXPR.  */

ساكن فراغ
inform_declaration (ونه decl, ونه function_بیان)
{
  إذا (decl && (ونه_کوډ (decl) != FUNCTION_DECL
	       || !DECL_IS_UNDECLARED_BUILTIN (decl)))
    inform (DECL_سرچینه_LOCATION (decl), "declared here");
  وإلا إذا (function_بیان)
    بدل (ونه_کوډ (function_بیان))
      {
      افتراضي:
	اكسر;
      حالة COMPONENT_REF:
	/* Show the decl of the pertinent field (e.g. for callback
	   fields in a struct.  */
	{
	  ونه ډګر_decl = ونه_عملوند (function_بیان, 1);
	  إذا (location_t loc = DECL_سرچینه_LOCATION (ډګر_decl))
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

ونه
build_function_call_vec (location_t loc, vec<location_t> arg_loc,
			 ونه function, vec<ونه, va_gc> *params,
			 vec<ونه, va_gc> *origtypes, ونه orig_fundecl)
{
  ونه fntype, fundecl = NULL_ونه;
  ونه name = NULL_ونه, پایله;
  ونه tem;
  صحيح nargs;
  ونه *argarray;


  /* Strip NON_LVALUE_EXPRs, etc., since we aren't using as an lvalue.  */
  STRIP_TYPE_NOPS (function);

  /* Convert anything with function type to a pointer-to-function.  */
  إذا (ونه_کوډ (function) == FUNCTION_DECL)
    {
      name = DECL_NAME (function);

      إذا (flag_tm)
	tm_malloc_replacement (function);
      fundecl = function;
      إذا (!orig_fundecl)
	orig_fundecl = fundecl;
      /* Atomic functions have type checking/casting already done.  They are
	 often rewritten and don't match the original parameter list.  */
      إذا (name && startswith (IDENTIFIER_اشاره_ګر (name), "__atomic_"))
        origtypes = عدم;
    }
  إذا (ونه_کوډ (ونه_TYPE (function)) == FUNCTION_TYPE)
    function = function_منزل_اشاره_ګر_conversion (loc, function);

  /* For Objective-C, convert any calls via a cast to OBJC_TYPE_REF
     expressions, like those used for ObjC messenger dispatches.  */
  إذا (params && !params->is_تشه ())
    function = objc_rewrite_function_call (function, (*params)[0]);

  function = c_fully_fold (function, خطأ, عدم);

  fntype = ونه_TYPE (function);

  إذا (ونه_کوډ (fntype) == ERROR_MARK)
    أرجع error_mark_غوټه;

  إذا (!(ونه_کوډ (fntype) == اشاره_ګر_TYPE
	&& ونه_کوډ (ونه_TYPE (fntype)) == FUNCTION_TYPE))
    {
      إذا (!flag_diagnostics_show_caret && !STATEMENT_CLASS_P (function))
	error_at (loc,
		  "called object %qE is not a function or function pointer",
		  function);
      وإلا إذا (DECL_P (function))
	{
	  auto_diagnostic_ډله d;
	  error_at (loc,
		    "called object %qD is not a function or function pointer",
		    function);
	  inform_declaration (function, NULL_ونه);
	}
      وإلا
	error_at (loc,
		  "called object is not a function or function pointer");
      أرجع error_mark_غوټه;
    }

  إذا (fundecl && ونه_THIS_VOLATILE (fundecl))
    current_function_returns_abnormally = 1;

  /* fntype now gets the type of function pointed to.  */
  fntype = ونه_TYPE (fntype);
  ونه return_type = ونه_TYPE (fntype);

  /* Convert the parameters to the types declared in the
     function prototype, or apply default promotions.  */

  nargs = convert_arguments (loc, arg_loc, fntype, params,
			     origtypes, function, fundecl);
  إذا (nargs < 0)
    أرجع error_mark_غوټه;

  /* Check that the function is called through a compatible prototype.
     If it is not, warn.  */
  إذا (CONVERT_بیان_P (function)
      && ونه_کوډ (tem = ونه_عملوند (function, 0)) == ADDR_بیان
      && ونه_کوډ (tem = ونه_عملوند (tem, 0)) == FUNCTION_DECL
      && !comptypes (fntype, ونه_TYPE (tem)))
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

  argarray = vec_خوندي_پته (params);

  /* Check that arguments to builtin functions match the expectations.  */
  إذا (fundecl
      && fndecl_built_دننه_p (fundecl)
      && !check_builtin_function_arguments (loc, arg_loc, fundecl,
					    orig_fundecl, nargs, argarray))
    أرجع error_mark_غوټه;

  /* Check that the arguments to the function are valid.  */
  منطقي warned_p = check_function_arguments (loc, fundecl, fntype,
					    nargs, argarray, &arg_loc,
					    comptypes);

  إذا (TYPE_QUALS (return_type) != TYPE_UNQUALIFIED
      && !VOID_TYPE_P (return_type))
    return_type = c_build_qualified_type (return_type, TYPE_UNQUALIFIED);
  إذا (name != NULL_ونه
      && startswith (IDENTIFIER_اشاره_ګر (name), "__builtin_"))
    {
      إذا (require_constant_ارزښت)
	پایله
	  = fold_build_call_array_initializer_loc (loc, return_type,
						   function, nargs, argarray);
      وإلا
	پایله = fold_build_call_array_loc (loc, return_type,
					    function, nargs, argarray);
      إذا (ونه_کوډ (پایله) == NOP_بیان
	  && ونه_کوډ (ونه_عملوند (پایله, 0)) == INTEGER_CST)
	STRIP_TYPE_NOPS (پایله);
    }
  وإلا
    پایله = build_call_array_loc (loc, return_type,
				   function, nargs, argarray);
  /* If -Wnonnull warning has been diagnosed, avoid diagnosing it again
     later.  */
  إذا (warned_p && ونه_کوډ (پایله) == CALL_بیان)
    suppress_warning (پایله, OPT_Wnonnull);

  /* In this improbable scenario, a nested function returns a VM type.
     Create a TARGET_EXPR so that the call always has a LHS, much as
     what the C++ FE does for functions returning non-PODs.  */
  إذا (c_type_variably_modified_p (ونه_TYPE (fntype)))
    {
      ونه tmp = create_tmp_var_raw (ونه_TYPE (fntype));
      پایله = build4 (موخه_بیان, ونه_TYPE (fntype), tmp, پایله,
		       NULL_ونه, NULL_ونه);
    }

  إذا (VOID_TYPE_P (ونه_TYPE (پایله)))
    {
      إذا (TYPE_QUALS (ونه_TYPE (پایله)) != TYPE_UNQUALIFIED)
	pedwarn (loc, 0,
		 "function with qualified void return type called");
      أرجع پایله;
    }
  أرجع require_complete_type (loc, پایله);
}

/* Like build_function_call_vec, but call also resolve_overloaded_builtin.  */

ونه
c_build_function_call_vec (location_t loc, ثابت vec<location_t> &arg_loc,
			   ونه function, vec<ونه, va_gc> *params,
			   vec<ونه, va_gc> *origtypes)
{
  /* Strip NON_LVALUE_EXPRs, etc., since we aren't using as an lvalue.  */
  STRIP_TYPE_NOPS (function);

  /* Convert anything with function type to a pointer-to-function.  */
  إذا (ونه_کوډ (function) == FUNCTION_DECL)
    {
      /* Implement type-directed function overloading for builtins.
	 resolve_overloaded_builtin and targetm.resolve_overloaded_builtin
	 handle all the type checking.  The result is a complete expression
	 that implements this function call.  */
      ونه tem = resolve_overloaded_builtin (loc, function, params);
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

ساكن ونه
convert_دلیل (location_t ploc, ونه function, ونه fundecl,
		  ونه type, ونه origtype, ونه val, ونه valtype,
		  منطقي npc, ونه rname, صحيح parmnum, صحيح argnum,
		  منطقي excess_precision, صحيح warnopt)
{
  /* Formal parm type is specified by a function prototype.  */

  إذا (type == error_mark_غوټه || !COMPLETE_TYPE_P (type))
    {
      error_at (ploc, "type of formal parameter %d is incomplete",
		parmnum + 1);
      أرجع error_mark_غوټه;
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
	  && ونه_کوډ (valtype) == COMPLEX_TYPE)
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as integer rather "
		    "than complex due to prototype",
		    argnum, rname);
      وإلا إذا (ونه_کوډ (type) == COMPLEX_TYPE
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
      وإلا إذا (ونه_کوډ (type) == COMPLEX_TYPE
	       && INTEGRAL_TYPE_P (valtype))
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as complex rather "
		    "than integer due to prototype",
		    argnum, rname);
      وإلا إذا (SCALAR_FLOAT_TYPE_P (type)
	       && ونه_کوډ (valtype) == COMPLEX_TYPE)
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
	  بینښه صحيح formal_prec = TYPE_PRECISION (type);

	  /* Warn if any argument is passed as `float',
	     since without a prototype it would be `double'.  */
	  إذا (formal_prec == TYPE_PRECISION (float_type_غوټه)
	      && type != dfloat32_type_غوټه)
	    warning_at (ploc, 0,
			"passing argument %d of %qE as %<float%> "
			"rather than %<double%> due to prototype",
			argnum, rname);

	  /* Warn if mismatch between argument and prototype
	     for decimal float types.  Warn of conversions with
	     binary float types and of precision narrowing due to
	     prototype.  */
	  وإلا إذا (type != valtype
		   && (type == dfloat32_type_غوټه
		       || type == dfloat64_type_غوټه
		       || type == dfloat128_type_غوټه
		       || valtype == dfloat32_type_غوټه
		       || valtype == dfloat64_type_غوټه
		       || valtype == dfloat128_type_غوټه)
		   && (formal_prec
		       <= TYPE_PRECISION (valtype)
		       || (type == dfloat128_type_غوټه
			   && (valtype
			       != dfloat64_type_غوټه
			       && (valtype
				   != dfloat32_type_غوټه)))
		       || (type == dfloat64_type_غوټه
			   && (valtype
			       != dfloat32_type_غوټه))))
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
	  بینښه صحيح formal_prec = TYPE_PRECISION (type);
	  ونه would_have_been = default_conversion (val);
	  ونه type1 = ونه_TYPE (would_have_been);

	  إذا (val == error_mark_غوټه)
	    /* VAL could have been of incomplete type.  */;
	  وإلا إذا (ونه_کوډ (type) == ENUMERAL_TYPE
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
	  وإلا إذا (ونه_کوډ (type) == ENUMERAL_TYPE)
	    ;
	  وإلا إذا (ونه_کوډ (val) == INTEGER_CST
		   && int_ځاییږي_type_p (val, type))
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
    val = build1 (EXCESS_PRECISION_بیان, valtype, val);

  ونه parmval = convert_for_assignment (ploc, ploc, type,
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
convert_arguments (location_t loc, vec<location_t> arg_loc, ونه fntype,
		   vec<ونه, va_gc> *ارزښتونه, vec<ونه, va_gc> *origtypes,
		   ونه function, ونه fundecl)
{
  ونه typelist = TYPE_ARG_TYPES (fntype);
  بینښه صحيح parmnum;
  منطقي error_دلیلونه = خطأ;
  ثابت منطقي type_generic = fundecl
    && lookup_attribute ("type generic", TYPE_ځانګړتیاوې (ونه_TYPE (fundecl)));
  منطقي type_generic_remove_excess_precision = خطأ;
  منطقي type_generic_ډکېدنه_p = خطأ;
  منطقي type_generic_بټ_query = خطأ;
  ونه selector;

  /* Change pointer to function to the function itself for
     diagnostics.  */
  إذا (ونه_کوډ (function) == ADDR_بیان
      && ونه_کوډ (ونه_عملوند (function, 0)) == FUNCTION_DECL)
    function = ونه_عملوند (function, 0);

  /* Handle an ObjC selector specially for diagnostics.  */
  selector = objc_پیغام_selector ();

  /* For a call to a built-in function declared without a prototype,
     set to the built-in function's argument list.  */
  ونه builtin_typelist = NULL_ونه;

  /* For type-generic built-in functions, determine whether excess
     precision should be removed (classification) or not
     (comparison).  */
  إذا (fundecl
      && fndecl_built_دننه_p (fundecl, BUILT_دننه_نورمال))
    {
      built_دننه_function کوډ = DECL_FUNCTION_کوډ (fundecl);
      إذا (C_DECL_BUILTIN_PROTOTYPE (fundecl))
	{
	  /* For a call to a built-in function declared without a prototype
	     use the types of the parameters of the internal built-in to
	     match those of the arguments to.  */
	  إذا (ونه bdecl = builtin_decl_explicit (کوډ))
	    builtin_typelist = TYPE_ARG_TYPES (ونه_TYPE (bdecl));
	}

      /* For type-generic built-in functions, determine whether excess
	 precision should be removed (classification) or not
	 (comparison).  */
      إذا (type_generic)
	بدل (کوډ)
	  {
	  حالة BUILT_دننه_ISFINITE:
	  حالة BUILT_دننه_ISINF:
	  حالة BUILT_دننه_ISINF_SIGN:
	  حالة BUILT_دننه_ISNAN:
	  حالة BUILT_دننه_ISNORMAL:
	  حالة BUILT_دننه_ISSIGNALING:
	  حالة BUILT_دننه_FPCLASSIFY:
	    type_generic_remove_excess_precision = ریښتیا;
	    اكسر;

	  حالة BUILT_دننه_جمع_کړه_ډکېدنه_P:
	  حالة BUILT_دننه_SUB_ډکېدنه_P:
	  حالة BUILT_دننه_MUL_ډکېدنه_P:
	    /* The last argument of these type-generic builtins
	       should not be promoted.  */
	    type_generic_ډکېدنه_p = ریښتیا;
	    اكسر;

	  حالة BUILT_دننه_CLZG:
	  حالة BUILT_دننه_CTZG:
	  حالة BUILT_دننه_CLRSBG:
	  حالة BUILT_دننه_FFSG:
	  حالة BUILT_دننه_PARITYG:
	  حالة BUILT_دننه_POPCOUNTG:
	    /* The first argument of these type-generic builtins
	       should not be promoted.  */
	    type_generic_بټ_query = ریښتیا;
	    اكسر;

	  افتراضي:
	    اكسر;
	  }
    }

  /* Scan the given expressions (VALUES) and types (TYPELIST), producing
     individual converted arguments.  */

  ونه typetail, builtin_typetail, val;
  لكل (typetail = typelist,
	 builtin_typetail = builtin_typelist,
	 parmnum = 0;
       ارزښتونه && ارزښتونه->iterate (parmnum, &val);
       ++parmnum)
    {
      /* The type of the function parameter (if it was declared with one).  */
      ونه type = typetail ? ونه_ارزښت (typetail) : NULL_ونه;
      /* The type of the built-in function parameter (if the function
	 is a built-in).  Used to detect type incompatibilities in
	 calls to built-ins declared without a prototype.  */
      ونه builtin_type = (builtin_typetail
			   ? ونه_ارزښت (builtin_typetail) : NULL_ونه);
      /* The original type of the argument being passed to the function.  */
      ونه valtype = ونه_TYPE (val);
      /* The called function (or function selector in Objective C).  */
      ونه rname = function;
      صحيح argnum = parmnum + 1;
      ثابت حرف *invalid_func_diag;
      /* Set for EXCESS_PRECISION_EXPR arguments.  */
      منطقي excess_precision = خطأ;
      /* The value of the argument after conversion to the type
	 of the function parameter it is passed to.  */
      ونه parmval;
      /* Some __atomic_* builtins have additional hidden argument at
	 position 0.  */
      location_t ploc
	= !arg_loc.is_تشه () && ارزښتونه->اوږدتیا () == arg_loc.اوږدتیا ()
	  ? expansion_ټکی_location_if_دننه_system_سرلیک (arg_loc[parmnum])
	  : ننوت_location;

      إذا (type == void_type_غوټه)
	{
	  auto_diagnostic_ډله d;
	  صحيح عدد_expected = parmnum;
	  صحيح عدد_actual = ارزښتونه->اوږدتیا ();
	  gcc_rich_location rich_loc (loc);
	  إذا (ploc != ننوت_location)
	    rich_loc.جمع_کړه_range (ploc);
	  إذا (selector)
	    error_at (&rich_loc,
		      "too many arguments to method %qE; expected %i, have %i",
		      selector, عدد_expected, عدد_actual);
	  وإلا
	    error_at (&rich_loc,
		      "too many arguments to function %qE; expected %i, have %i",
		      function, عدد_expected, عدد_actual);
	  inform_declaration (fundecl, function);
	  أرجع error_دلیلونه ? -1 : (صحيح) parmnum;
	}

      إذا (builtin_type == void_type_غوټه)
	{
	  auto_diagnostic_ډله d;
	  إذا (warning_at (loc, OPT_Wbuiltin_declaration_mismatch,
			  "too many arguments to built-in function %qE "
			  "expecting %d", function, parmnum))
	    inform_declaration (fundecl, function);
	  builtin_typetail = NULL_ونه;
	}

      إذا (!typetail && parmnum == 0 && !TYPE_NO_NAMED_دلیلونه_STDARG_P (fntype)
	  && !(fundecl && fndecl_built_دننه_p (fundecl)))
	{
	  auto_diagnostic_ډله d;
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
      منطقي npc = null_اشاره_ګر_constant_p (val);

      /* If there is excess precision and a prototype, convert once to
	 the required type rather than converting via the semantic
	 type.  Likewise without a prototype a float value represented
	 as long double should be converted once to double.  But for
	 type-generic classification functions excess precision must
	 be removed here.  */
      إذا (ونه_کوډ (val) == EXCESS_PRECISION_بیان
	  && (type || !type_generic || !type_generic_remove_excess_precision))
	{
	  val = ونه_عملوند (val, 0);
	  excess_precision = ریښتیا;
	}
      val = c_fully_fold (val, خطأ, عدم);
      STRIP_TYPE_NOPS (val);

      val = require_complete_type (ploc, val);

      /* Some floating-point arguments must be promoted to double when
	 no type is specified by a prototype.  This applies to
	 arguments of type float, and to architecture-specific types
	 (ARM __fp16), but not to _FloatN or _FloatNx types.  */
      منطقي promote_float_arg = خطأ;
      إذا (type == NULL_ونه
	  && ونه_کوډ (valtype) == REAL_TYPE
	  && (TYPE_PRECISION (valtype)
	      <= TYPE_PRECISION (double_type_غوټه))
	  && TYPE_MAIN_VARIANT (valtype) != double_type_غوټه
	  && TYPE_MAIN_VARIANT (valtype) != long_double_type_غوټه
	  && !DECIMAL_FLOAT_ډېرپېښ_P (TYPE_ډېرپېښ (valtype)))
	{
	  /* Promote this argument, unless it has a _FloatN or
	     _FloatNx type.  */
	  promote_float_arg = ریښتیا;
	  لكل (صحيح i = 0; i < عدد_FLOATN_NX_TYPES; i++)
	    إذا (TYPE_MAIN_VARIANT (valtype) == FLOATN_NX_TYPE_غوټه (i))
	      {
		promote_float_arg = خطأ;
		اكسر;
	      }
	  /* Don't promote __bf16 either.  */
	  إذا (TYPE_MAIN_VARIANT (valtype) == bfloat16_type_غوټه)
	    promote_float_arg = خطأ;
	}

      إذا (type != NULL_ونه)
	{
	  ونه origtype = (!origtypes) ? NULL_ونه : (*origtypes)[parmnum];
	  parmval = convert_دلیل (ploc, function, fundecl, type, origtype,
				      val, valtype, npc, rname, parmnum, argnum,
				      excess_precision, 0);
	}
      /* A NULLPTR type is just a nullptr always.  */
      وإلا إذا (ونه_کوډ (ونه_TYPE (val)) == NULLPTR_TYPE)
	parmval = omit_one_عملوند_loc (ploc, ونه_TYPE (val), nullptr_غوټه, val);
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
			    valtype, double_type_غوټه);
	      parmval = convert (double_type_غوټه, val);
	    }
	}
      وإلا إذا ((excess_precision && !type_generic)
	       || (type_generic_ډکېدنه_p && parmnum == 2)
	       || (type_generic_بټ_query && parmnum == 0))
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
      وإلا إذا (ونه_کوډ (val) == ADDR_بیان && reject_gcc_builtin (val))
	{
	  أرجع -1;
	}
      وإلا
	/* Convert `short' and `char' to full-size `int'.  */
	parmval = default_conversion (val);

      (*ارزښتونه)[parmnum] = parmval;
      إذا (parmval == error_mark_غوټه)
	error_دلیلونه = ریښتیا;

      إذا (!type && builtin_type && ونه_کوډ (builtin_type) != VOID_TYPE)
	{
	  /* For a call to a built-in function declared without a prototype,
	     perform the conversions from the argument to the expected type
	     but issue warnings rather than errors for any mismatches.
	     Ignore the converted argument and use the PARMVAL obtained
	     above by applying default conversions instead.  */
	  ونه origtype = (!origtypes) ? NULL_ونه : (*origtypes)[parmnum];
	  convert_دلیل (ploc, function, fundecl, builtin_type, origtype,
			    val, valtype, npc, rname, parmnum, argnum,
			    excess_precision,
			    OPT_Wbuiltin_declaration_mismatch);
	}

      إذا (typetail)
	typetail = ونه_CHAIN (typetail);

      إذا (builtin_typetail)
	builtin_typetail = ونه_CHAIN (builtin_typetail);
    }

  gcc_assert (parmnum == vec_خوندي_اوږدتیا (ارزښتونه));

  إذا (typetail != NULL_ونه && ونه_ارزښت (typetail) != void_type_غوټه)
    {
      /* Not enough args.
	 Determine minimum number of arguments required.  */
      صحيح min_expected_عدد = 0;
      منطقي at_لږترلږه_p = خطأ;
      ونه iter = typelist;
      طالما (ریښتیا)
	{
	  إذا (!iter)
	    {
	      /* Variadic arguments; stop iterating.  */
	      at_لږترلږه_p = ریښتیا;
	      اكسر;
	    }
	  إذا (iter == void_list_غوټه)
	    /* End of arguments; stop iterating.  */
	    اكسر;
	  ++min_expected_عدد;
	  iter = ونه_CHAIN (iter);
	}
      auto_diagnostic_ډله d;
      صحيح actual_عدد = vec_خوندي_اوږدتیا (ارزښتونه);
      error_at (loc,
		at_لږترلږه_p
		? G_("too few arguments to function %qE; expected at least %i, have %i")
		: G_("too few arguments to function %qE; expected %i, have %i"),
		function, min_expected_عدد, actual_عدد);
      inform_declaration (fundecl, function);
      أرجع -1;
    }

  إذا (builtin_typetail && ونه_ارزښت (builtin_typetail) != void_type_غوټه)
    {
      بینښه nargs = parmnum;
      لكل (ونه t = builtin_typetail; t; t = ونه_CHAIN (t))
	++nargs;

      auto_diagnostic_ډله d;
      إذا (warning_at (loc, OPT_Wbuiltin_declaration_mismatch,
		      "too few arguments to built-in function %qE "
		      "expecting %u", function, nargs - 1))
	inform_declaration (fundecl, function);
    }

  أرجع error_دلیلونه ? -1 : (صحيح) parmnum;
}

/* This is the entry point used by the parser to build unary operators
   in the input.  CODE, a tree_code, specifies the unary operator, and
   ARG is the operand.  For unary plus, the C parser currently uses
   CONVERT_EXPR for code.

   LOC is the location to use for the tree generated.
*/

بنية c_بیان
parser_build_unary_op (location_t loc, تعداد ونه_کوډ_2 کوډ, بنية c_بیان arg)
{
  بنية c_بیان پایله;

  پایله.original_کوډ = کوډ;
  پایله.original_type = عدم;
  پایله.m_decimal = 0;

  إذا (reject_gcc_builtin (arg.ارزښت))
    {
      پایله.ارزښت = error_mark_غوټه;
    }
  وإلا
    {
      پایله.ارزښت = build_unary_op (loc, کوډ, arg.ارزښت, خطأ);

      إذا (ونه_ډکېدنه_P (پایله.ارزښت) && !ونه_ډکېدنه_P (arg.ارزښت))
	ډکېدنه_warning (loc, پایله.ارزښت, arg.ارزښت);
    }

  /* We are typically called when parsing a prefix token at LOC acting on
     ARG.  Reflect this by updating the source range of the result to
     start at LOC and end at the end of ARG.  */
  سېټ_c_بیان_سرچینه_range (&پایله,
			   loc, arg.get_پای ());

  أرجع پایله;
}

/* Returns true if TYPE is a character type, *not* including wchar_t.  */

منطقي
char_type_p (ونه type)
{
  أرجع (type == char_type_غوټه
	  || type == unsigned_char_type_غوټه
	  || type == signed_char_type_غوټه
	  || type == char16_type_غوټه
	  || type == char32_type_غوټه);
}

/* This is the entry point used by the parser to build binary operators
   in the input.  CODE, a tree_code, specifies the binary operator, and
   ARG1 and ARG2 are the operands.  In addition to constructing the
   expression, we check for operands that were written with other binary
   operators in a way that is likely to confuse the user.  ORIG_ARG1 is
   the original first operand for TRUTH_{AND,OR}IF_EXPR before it is
   converted to truth value, otherwise NULL_TREE.

   LOCATION is the location of the binary operator.  */

بنية c_بیان
parser_build_دوګونی_op (location_t location, تعداد ونه_کوډ_2 کوډ,
			بنية c_بیان arg1, بنية c_بیان arg2, ونه orig_arg1)
{
  بنية c_بیان پایله;
  پایله.m_decimal = 0;

  تعداد ونه_کوډ_2 code1 = arg1.original_کوډ;
  تعداد ونه_کوډ_2 code2 = arg2.original_کوډ;
  ونه type1 = (arg1.original_type
                ? arg1.original_type
                : ونه_TYPE (arg1.ارزښت));
  ونه type2 = (arg2.original_type
                ? arg2.original_type
                : ونه_TYPE (arg2.ارزښت));

  پایله.ارزښت = build_دوګونی_op (location, کوډ,
				  arg1.ارزښت, arg2.ارزښت, ریښتیا);
  پایله.original_کوډ = کوډ;
  پایله.original_type = عدم;
  پایله.m_decimal = 0;

  إذا (ونه_کوډ (پایله.ارزښت) == ERROR_MARK)
    {
      سېټ_c_بیان_سرچینه_range (&پایله,
			       arg1.get_پیل (),
			       arg2.get_پای ());
      أرجع پایله;
    }

  إذا (location != UNKNOWN_LOCATION)
    protected_سېټ_بیان_location (پایله.ارزښت, location);

  سېټ_c_بیان_سرچینه_range (&پایله,
			   arg1.get_پیل (),
			   arg2.get_پای ());

  /* Check for cases such as x+y<<z which users are likely
     to misinterpret.  */
  إذا (warn_parentheses)
    warn_about_parentheses (location, کوډ, code1, arg1.ارزښت, code2,
			    arg2.ارزښت);

  إذا (warn_logical_op)
    warn_logical_operator (location, کوډ, ونه_TYPE (پایله.ارزښت),
			   code1, arg1.ارزښت, code2, arg2.ارزښت);

  إذا (warn_constant_logical_عملوند
      && (کوډ == TRUTH_ANDIF_بیان || کوډ == TRUTH_ORIF_بیان)
      && INTEGRAL_NB_TYPE_P (type1)
      && INTEGRAL_NB_TYPE_P (type2))
    {
      ثابت حرف *name = کوډ == TRUTH_ANDIF_بیان ? "&&" : "||";
      إذا (orig_arg1 == NULL_ونه)
	orig_arg1 = arg1.ارزښت;
      خپلکاری enum_other_than_0_1 = [] (ونه type) {
	إذا (ونه_کوډ (type) != ENUMERAL_TYPE)
	  أرجع خطأ;
	لكل (ونه l = TYPE_ارزښتونه (type); l; l = ونه_CHAIN (l))
	  {
	    ونه v = DECL_INITIAL (ونه_ارزښت (l));
	    إذا (!integer_zerop (v) && !integer_onep (v))
	      أرجع ریښتیا;
	  }
	أرجع خطأ;
      };
      خپلکاری diagnose_constant_logical_عملوند = [=] (ونه val, ونه type) {
	إذا (ونه_کوډ (val) != INTEGER_CST || integer_zerop (val))
	  أرجع خطأ;
	إذا (integer_onep (val) && !enum_other_than_0_1 (type))
	  أرجع خطأ;
	gcc_rich_location richloc (location);
	richloc.جمع_کړه_fixit_replace (name + 1);
	auto_diagnostic_ډله d;
	إذا (warning_at (location, OPT_Wconstant_logical_عملوند,
			"use of logical %qs with constant operand %qE",
			name, val))
	  inform (&richloc, "use %qs for bitwise operation", name + 1);
	أرجع ریښتیا;
      };
      إذا (!diagnose_constant_logical_عملوند (arg2.ارزښت, type2))
	diagnose_constant_logical_عملوند (orig_arg1, type1);
    }

  إذا (warn_tautological_compare)
    {
      ونه lhs = arg1.ارزښت;
      ونه rhs = arg2.ارزښت;
      إذا (ونه_کوډ (lhs) == C_MAYBE_CONST_بیان)
	{
	  إذا (C_MAYBE_CONST_بیان_PRE (lhs) != NULL_ونه
	      && ونه_SIDE_EFFECTS (C_MAYBE_CONST_بیان_PRE (lhs)))
	    lhs = NULL_ونه;
	  وإلا
	    lhs = C_MAYBE_CONST_بیان_بیان (lhs);
	}
      إذا (ونه_کوډ (rhs) == C_MAYBE_CONST_بیان)
	{
	  إذا (C_MAYBE_CONST_بیان_PRE (rhs) != NULL_ونه
	      && ونه_SIDE_EFFECTS (C_MAYBE_CONST_بیان_PRE (rhs)))
	    rhs = NULL_ونه;
	  وإلا
	    rhs = C_MAYBE_CONST_بیان_بیان (rhs);
	}
      إذا (lhs != NULL_ونه && rhs != NULL_ونه)
	warn_tautological_cmp (location, کوډ, lhs, rhs);
    }

  إذا (warn_logical_not_paren
      && ونه_کوډ_CLASS (کوډ) == tcc_comparison
      && code1 == TRUTH_NOT_بیان
      && code2 != TRUTH_NOT_بیان
      /* Avoid warning for !!x == y.  */
      && (ونه_کوډ (arg1.ارزښت) != NE_بیان
	  || !integer_zerop (ونه_عملوند (arg1.ارزښت, 1))))
    {
      /* Avoid warning for !b == y where b has _Bool type.  */
      ونه t = integer_zero_غوټه;
      إذا (ونه_کوډ (arg1.ارزښت) == EQ_بیان
	  && integer_zerop (ونه_عملوند (arg1.ارزښت, 1))
	  && ونه_TYPE (ونه_عملوند (arg1.ارزښت, 0)) == integer_type_غوټه)
	{
	  t = ونه_عملوند (arg1.ارزښت, 0);
	  افعل
	    {
	      إذا (ونه_TYPE (t) != integer_type_غوټه)
		اكسر;
	      إذا (ونه_کوډ (t) == C_MAYBE_CONST_بیان)
		t = C_MAYBE_CONST_بیان_بیان (t);
	      وإلا إذا (CONVERT_بیان_P (t))
		t = ونه_عملوند (t, 0);
	      وإلا
		اكسر;
	    }
	  طالما (1);
	}
      إذا (!C_BOOLEAN_TYPE_P (ونه_TYPE (t)))
	warn_logical_not_parentheses (location, کوډ, arg1.ارزښت, arg2.ارزښت);
    }

  /* Warn about comparisons against string literals, with the exception
     of testing for equality or inequality of a string literal with NULL.  */
  إذا (کوډ == EQ_بیان || کوډ == NE_بیان)
    {
      إذا ((code1 == STRING_CST
	   && !integer_zerop (ونه_strip_nop_conversions (arg2.ارزښت)))
	  || (code2 == STRING_CST
	      && !integer_zerop (ونه_strip_nop_conversions (arg1.ارزښت))))
	warning_at (location, OPT_Waddress,
		    "comparison with string literal results in unspecified behavior");
      /* Warn for ptr == '\0', it's likely that it should've been ptr[0].  */
      إذا (اشاره_ګر_TYPE_P (type1)
	  && null_اشاره_ګر_constant_p (arg2.ارزښت)
	  && char_type_p (type2))
	{
	  auto_diagnostic_ډله d;
	  إذا (warning_at (location, OPT_Wpointer_compare,
			    "comparison between pointer and zero character "
			    "constant"))
	    inform (arg1.get_پیل (),
		      "did you mean to dereference the pointer?");
	}
      وإلا إذا (اشاره_ګر_TYPE_P (type2)
	       && null_اشاره_ګر_constant_p (arg1.ارزښت)
	       && char_type_p (type1))
	{
	  auto_diagnostic_ډله d;
	  إذا (warning_at (location, OPT_Wpointer_compare,
			    "comparison between pointer and zero character "
			    "constant"))
	    inform (arg2.get_پیل (),
		      "did you mean to dereference the pointer?");
	}
    }
  وإلا إذا (ونه_کوډ_CLASS (کوډ) == tcc_comparison
	   && (code1 == STRING_CST || code2 == STRING_CST))
    warning_at (location, OPT_Waddress,
		"comparison with string literal results in unspecified "
		"behavior");

  إذا (warn_zero_as_null_اشاره_ګر_constant
      && c_inhibit_evaluation_warnings == 0
      && ونه_کوډ_CLASS (کوډ) == tcc_comparison)
    {
      إذا ((ونه_کوډ (type1) == اشاره_ګر_TYPE
	   || ونه_کوډ (type1) == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type2)
	  && null_اشاره_ګر_constant_p (arg2.ارزښت))
	warning_at (arg2.get_location(), OPT_Wzero_as_null_اشاره_ګر_constant,
		    "zero as null pointer constant");

      إذا ((ونه_کوډ (type2) == اشاره_ګر_TYPE
	   || ونه_کوډ (type2) == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type1)
	  && null_اشاره_ګر_constant_p (arg1.ارزښت))
	warning_at (arg1.get_location(), OPT_Wzero_as_null_اشاره_ګر_constant,
		    "zero as null pointer constant");
    }

  إذا (warn_array_compare
      && ونه_کوډ_CLASS (کوډ) == tcc_comparison
      && ونه_کوډ (type1) == ARRAY_TYPE
      && ونه_کوډ (type2) == ARRAY_TYPE)
    do_warn_array_compare (location, کوډ, arg1.ارزښت, arg2.ارزښت);

  إذا (ونه_ډکېدنه_P (پایله.ارزښت)
      && !ونه_ډکېدنه_P (arg1.ارزښت)
      && !ونه_ډکېدنه_P (arg2.ارزښت))
    ډکېدنه_warning (location, پایله.ارزښت);

  /* Warn about comparisons of different enum types.  */
  إذا (warn_enum_compare
      && ونه_کوډ_CLASS (کوډ) == tcc_comparison
      && ونه_کوډ (type1) == ENUMERAL_TYPE
      && ونه_کوډ (type2) == ENUMERAL_TYPE
      && TYPE_MAIN_VARIANT (type1) != TYPE_MAIN_VARIANT (type2))
    warning_at (location, OPT_Wenum_compare,
		"comparison between %qT and %qT",
		type1, type2);

  إذا (warn_xor_کارول_شوی_as_pow
      && کوډ == بټ_XOR_بیان
      && arg1.m_decimal
      && arg2.m_decimal)
    check_for_xor_کارول_شوی_as_pow (arg1.get_location (), arg1.ارزښت,
			       location,
			       arg2.get_location (), arg2.ارزښت);

  أرجع پایله;
}

/* Return a tree for the difference of pointers OP0 and OP1.
   The resulting tree has type ptrdiff_t.  If POINTER_SUBTRACT sanitization is
   enabled, assign to INSTRUMENT_EXPR call to libsanitizer.  */

ساكن ونه
اشاره_ګر_diff (location_t loc, ونه op0, ونه op1, ونه *instrument_بیان)
{
  ونه restype = ptrdiff_type_غوټه;
  ونه پایله, inttype;

  addr_space_t as0 = TYPE_ADDR_SPACE (ونه_TYPE (ونه_TYPE (op0)));
  addr_space_t as1 = TYPE_ADDR_SPACE (ونه_TYPE (ونه_TYPE (op1)));
  ونه موخه_type = ونه_TYPE (ونه_TYPE (op0));
  ونه orig_op0 = op0;
  ونه orig_op1 = op1;

  /* If the operands point into different address spaces, we need to
     explicitly convert them to pointers into the common address space
     before we can subtract the numerical address values.  */
  إذا (as0 != as1)
    {
      addr_space_t as_common;
      ونه common_type;

      /* Determine the common superset address space.  This is guaranteed
	 to exist because the caller verified that comp_target_types
	 returned non-zero.  */
      إذا (!addr_space_superset (as0, as1, &as_common))
	gcc_unreachable ();

      common_type = common_اشاره_ګر_type (ونه_TYPE (op0), ونه_TYPE (op1), NULL_ونه);
      op0 = convert (common_type, op0);
      op1 = convert (common_type, op1);
    }

  /* Determine integer type result of the subtraction.  This will usually
     be the same as the result type (ptrdiff_t), but may need to be a wider
     type if pointers for the address space are wider than ptrdiff_t.  */
  إذا (TYPE_PRECISION (restype) < TYPE_PRECISION (ونه_TYPE (op0)))
    inttype = c_common_type_for_اندازه (TYPE_PRECISION (ونه_TYPE (op0)), 0);
  وإلا
    inttype = restype;

  إذا (VOID_TYPE_P (موخه_type))
    pedwarn (loc, OPT_Wpointer_arith,
	     "pointer of type %<void *%> used in subtraction");
  إذا (ونه_کوډ (موخه_type) == FUNCTION_TYPE)
    pedwarn (loc, OPT_Wpointer_arith,
	     "pointer to a function used in subtraction");

  إذا (current_function_decl != NULL_ونه
      && sanitize_flags_p (SANITIZE_اشاره_ګر_کمول))
    {
      op0 = save_بیان (c_fully_fold (op0, خطأ, عدم));
      op1 = save_بیان (c_fully_fold (op1, خطأ, عدم));

      ونه tt = builtin_decl_explicit (BUILT_دننه_ASAN_اشاره_ګر_کمول);
      *instrument_بیان = build_call_بیان_loc (loc, tt, 2, op0, op1);
    }

  /* First do the subtraction, then build the divide operator
     and only convert at the very end.
     Do not do default conversions in case restype is a short type.  */

  /* POINTER_DIFF_EXPR requires a signed integer type of the same size as
     pointers.  If some platform cannot provide that, or has a larger
     ptrdiff_type to support differences larger than half the address
     space, cast the pointers to some larger integer type and do the
     computations in that type.  */
  إذا (TYPE_PRECISION (inttype) > TYPE_PRECISION (ونه_TYPE (op0)))
    op0 = build_دوګونی_op (loc, MINUS_بیان, convert (inttype, op0),
			   convert (inttype, op1), خطأ);
  وإلا
    {
      /* Cast away qualifiers.  */
      op0 = convert (c_common_type (ونه_TYPE (op0), ونه_TYPE (op0)), op0);
      op1 = convert (c_common_type (ونه_TYPE (op1), ونه_TYPE (op1)), op1);
      op0 = build2_loc (loc, اشاره_ګر_DIFF_بیان, inttype, op0, op1);
    }

  /* This generates an error if op1 is pointer to incomplete type.  */
  إذا (!COMPLETE_OR_VOID_TYPE_P (ونه_TYPE (ونه_TYPE (orig_op1))))
    error_at (loc, "arithmetic on pointer to an incomplete type");
  وإلا إذا (verify_type_context (loc, TCTX_اشاره_ګر_ARITH,
				ونه_TYPE (ونه_TYPE (orig_op0))))
    verify_type_context (loc, TCTX_اشاره_ګر_ARITH,
			 ونه_TYPE (ونه_TYPE (orig_op1)));

  op1 = c_اندازه_دننه_بایټونه (موخه_type);

  إذا (اشاره_ګر_منزل_zero_sized_aggr_p (ونه_TYPE (orig_op1)))
    error_at (loc, "arithmetic on pointer to an empty aggregate");

  /* Divide by the size, in easiest possible way.  */
  پایله = fold_build2_loc (loc, EXACT_DIV_بیان, inttype,
			    op0, convert (inttype, op1));

  /* Convert to final result type if necessary.  */
  أرجع convert (restype, پایله);
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

ساكن ونه
build_atomic_ټاکل (location_t loc, ونه lhs, تعداد ونه_کوډ_2 modifycode,
		     ونه rhs, منطقي return_old_p)
{
  ونه fndecl, func_call;
  vec<ونه, va_gc> *params;
  ونه val, nonatomic_lhs_type, nonatomic_rhs_type, newval, newval_addr;
  ونه old, old_addr;
  ونه compound_stmt = NULL_ونه;
  ونه stmt, goto_stmt;
  ونه loop_label, loop_decl, بشپړ_label, بشپړ_decl;

  ونه lhs_type = ونه_TYPE (lhs);
  ونه lhs_addr = build_unary_op (loc, ADDR_بیان, lhs, خطأ);
  ونه seq_cst = build_int_cst (integer_type_غوټه, MEMMODEL_SEQ_CST);
  ونه rhs_semantic_type = ونه_TYPE (rhs);
  ونه nonatomic_rhs_semantic_type;
  ونه rhs_type;

  gcc_assert (TYPE_ATOMIC (lhs_type));

  إذا (return_old_p)
    gcc_assert (modifycode == PLUS_بیان || modifycode == MINUS_بیان);

  /* Allocate enough vector items for a compare_exchange.  */
  vec_alloc (params, 6);

  /* Create a compound statement to hold the sequence of statements
     with a loop.  */
  إذا (modifycode != NOP_بیان)
    {
      compound_stmt = c_begin_compound_stmt (خطأ);

      /* For consistency with build_modify_expr on non-_Atomic,
	 mark the lhs as read.  Also, it would be very hard to match
	 such expressions in mark_exp_read.  */
      mark_exp_read (lhs);
    }

  /* Remove any excess precision (which is only present here in the
     case of compound assignments).  */
  إذا (ونه_کوډ (rhs) == EXCESS_PRECISION_بیان)
    {
      gcc_assert (modifycode != NOP_بیان);
      rhs = ونه_عملوند (rhs, 0);
    }
  rhs_type = ونه_TYPE (rhs);

  /* Fold the RHS if it hasn't already been folded.  */
  إذا (modifycode != NOP_بیان)
    rhs = c_fully_fold (rhs, خطأ, عدم);

  /* Remove the qualifiers for the rest of the expressions and create
     the VAL temp variable to hold the RHS.  */
  nonatomic_lhs_type = build_qualified_type (lhs_type, TYPE_UNQUALIFIED);
  nonatomic_rhs_type = build_qualified_type (rhs_type, TYPE_UNQUALIFIED);
  nonatomic_rhs_semantic_type = build_qualified_type (rhs_semantic_type,
						      TYPE_UNQUALIFIED);
  val = create_tmp_var_raw (nonatomic_rhs_type);
  ونه_ADDRESSABLE (val) = 1;
  suppress_warning (val);
  rhs = build4 (موخه_بیان, nonatomic_rhs_type, val, rhs, NULL_ونه,
		NULL_ونه);
  ونه_SIDE_EFFECTS (rhs) = 1;
  سېټ_بیان_LOCATION (rhs, loc);
  إذا (modifycode != NOP_بیان)
    جمع_کړه_stmt (rhs);

  /* NOP_EXPR indicates it's a straight store of the RHS. Simply issue
     an atomic_store.  */
  إذا (modifycode == NOP_بیان)
    {
      compound_stmt = rhs;
      /* Build __atomic_store (&lhs, &val, SEQ_CST)  */
      rhs = build_unary_op (loc, ADDR_بیان, val, خطأ);
      fndecl = builtin_decl_explicit (BUILT_دننه_ATOMIC_STORE);
      params->چټک_ټېل (lhs_addr);
      params->چټک_ټېل (rhs);
      params->چټک_ټېل (seq_cst);
      func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, عدم);

      compound_stmt = build2 (COMPOUND_بیان, void_type_غوټه,
			      compound_stmt, func_call);

      /* VAL is the value which was stored, return a COMPOUND_STMT of
	 the statement and that value.  */
      أرجع build2 (COMPOUND_بیان, nonatomic_lhs_type, compound_stmt, val);
    }

  /* Attempt to implement the atomic operation as an __atomic_fetch_* or
     __atomic_*_fetch built-in rather than a CAS loop.  atomic_bool type
     isn't applicable for such builtins.  ??? Do we want to handle enums?  */
  إذا ((ونه_کوډ (lhs_type) == INTEGER_TYPE || اشاره_ګر_TYPE_P (lhs_type))
      && ونه_کوډ (rhs_type) == INTEGER_TYPE)
    {
      built_دننه_function fncode;
      بدل (modifycode)
	{
	حالة PLUS_بیان:
	حالة اشاره_ګر_PLUS_بیان:
	  fncode = (return_old_p
		    ? BUILT_دننه_ATOMIC_FETCH_جمع_کړه_N
		    : BUILT_دننه_ATOMIC_جمع_کړه_FETCH_N);
	  اكسر;
	حالة MINUS_بیان:
	  fncode = (return_old_p
		    ? BUILT_دننه_ATOMIC_FETCH_SUB_N
		    : BUILT_دننه_ATOMIC_SUB_FETCH_N);
	  اكسر;
	حالة بټ_AND_بیان:
	  fncode = (return_old_p
		    ? BUILT_دننه_ATOMIC_FETCH_AND_N
		    : BUILT_دننه_ATOMIC_AND_FETCH_N);
	  اكسر;
	حالة بټ_IOR_بیان:
	  fncode = (return_old_p
		    ? BUILT_دننه_ATOMIC_FETCH_OR_N
		    : BUILT_دننه_ATOMIC_OR_FETCH_N);
	  اكسر;
	حالة بټ_XOR_بیان:
	  fncode = (return_old_p
		    ? BUILT_دننه_ATOMIC_FETCH_XOR_N
		    : BUILT_دننه_ATOMIC_XOR_FETCH_N);
	  اكسر;
	افتراضي:
	  اذهب cas_loop;
	}

      /* We can only use "_1" through "_16" variants of the atomic fetch
	 built-ins.  */
      بینښه HOST_WIDE_INT اندازه = ونه_منزل_uhwi (TYPE_اندازه_UNIT (lhs_type));
      إذا (اندازه != 1 && اندازه != 2 && اندازه != 4 && اندازه != 8 && اندازه != 16)
	اذهب cas_loop;

      /* If this is a pointer type, we need to multiply by the size of
	 the pointer target type.  */
      إذا (اشاره_ګر_TYPE_P (lhs_type))
	{
	  إذا (!COMPLETE_TYPE_P (ونه_TYPE (lhs_type))
	      /* ??? This would introduce -Wdiscarded-qualifiers
		 warning: __atomic_fetch_* expect volatile void *
		 type as the first argument.  (Assignments between
		 atomic and non-atomic objects are OK.) */
	      || TYPE_RESTRICT (lhs_type))
	    اذهب cas_loop;
	  ونه sz = TYPE_اندازه_UNIT (ونه_TYPE (lhs_type));
	  rhs = fold_build2_loc (loc, MULT_بیان, ptrdiff_type_غوټه,
				 convert (ptrdiff_type_غوټه, rhs),
				 convert (ptrdiff_type_غوټه, sz));
	}

      /* Build __atomic_fetch_* (&lhs, &val, SEQ_CST), or
	 __atomic_*_fetch (&lhs, &val, SEQ_CST).  */
      fndecl = builtin_decl_explicit (fncode);
      params->چټک_ټېل (lhs_addr);
      params->چټک_ټېل (rhs);
      params->چټک_ټېل (seq_cst);
      func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, عدم);

      newval = create_tmp_var_raw (nonatomic_lhs_type);
      ونه_ADDRESSABLE (newval) = 1;
      suppress_warning (newval);
      rhs = build4 (موخه_بیان, nonatomic_lhs_type, newval, func_call,
		    NULL_ونه, NULL_ونه);
      سېټ_بیان_LOCATION (rhs, loc);
      جمع_کړه_stmt (rhs);

      /* Finish the compound statement.  */
      compound_stmt = c_پای_ټکی_compound_stmt (loc, compound_stmt, خطأ);

      /* NEWVAL is the value which was stored, return a COMPOUND_STMT of
	 the statement and that value.  */
      أرجع build2 (COMPOUND_بیان, nonatomic_lhs_type, compound_stmt, newval);
    }

cas_loop:
  /* Create the variables and labels required for the op= form.  */
  old = create_tmp_var_raw (nonatomic_lhs_type);
  old_addr = build_unary_op (loc, ADDR_بیان, old, خطأ);
  ونه_ADDRESSABLE (old) = 1;
  suppress_warning (old);

  newval = create_tmp_var_raw (nonatomic_lhs_type);
  newval_addr = build_unary_op (loc, ADDR_بیان, newval, خطأ);
  ونه_ADDRESSABLE (newval) = 1;
  suppress_warning (newval);

  loop_decl = create_artificial_label (loc);
  loop_label = build1 (LABEL_بیان, void_type_غوټه, loop_decl);

  بشپړ_decl = create_artificial_label (loc);
  بشپړ_label = build1 (LABEL_بیان, void_type_غوټه, بشپړ_decl);

  /* __atomic_load (addr, &old, SEQ_CST).  */
  fndecl = builtin_decl_explicit (BUILT_دننه_ATOMIC_بارول);
  params->چټک_ټېل (lhs_addr);
  params->چټک_ټېل (old_addr);
  params->چټک_ټېل (seq_cst);
  func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, عدم);
  old = build4 (موخه_بیان, nonatomic_lhs_type, old, func_call, NULL_ونه,
		NULL_ونه);
  جمع_کړه_stmt (old);
  params->truncate (0);

  /* Create the expressions for floating-point environment
     manipulation, if required.  */
  منطقي need_fenv = (flag_trapping_math
		    && (FLOAT_TYPE_P (lhs_type) || FLOAT_TYPE_P (rhs_type)));
  ونه hold_call = NULL_ونه, clear_call = NULL_ونه, update_call = NULL_ونه;
  إذا (need_fenv)
    targetm.atomic_ټاکل_expand_fenv (&hold_call, &clear_call, &update_call);

  إذا (hold_call)
    جمع_کړه_stmt (hold_call);

  /* loop:  */
  جمع_کړه_stmt (loop_label);

  /* newval = old + val;  */
  إذا (rhs_type != rhs_semantic_type)
    val = build1 (EXCESS_PRECISION_بیان, nonatomic_rhs_semantic_type, val);
  rhs = build_دوګونی_op (loc, modifycode,
			 convert_lvalue_منزل_rvalue (loc, old, ریښتیا, ریښتیا),
			 val, ریښتیا);
  إذا (ونه_کوډ (rhs) == EXCESS_PRECISION_بیان)
    {
      ونه eptype = ونه_TYPE (rhs);
      rhs = c_fully_fold (ونه_عملوند (rhs, 0), خطأ, عدم);
      rhs = build1 (EXCESS_PRECISION_بیان, eptype, rhs);
    }
  وإلا
    rhs = c_fully_fold (rhs, خطأ, عدم);
  rhs = convert_for_assignment (loc, UNKNOWN_LOCATION, nonatomic_lhs_type,
				rhs, NULL_ونه, ic_ټاکل, خطأ, NULL_ونه,
				NULL_ونه, 0);
  /* The temporary variable for NEWVAL is only gimplified correctly (in
     particular, given a DECL_CONTEXT) if used in a TARGET_EXPR.  To avoid
     subsequent ICEs in nested function processing after an error, ensure such
     a TARGET_EXPR is built even after an error.  */
  إذا (rhs == error_mark_غوټه)
    rhs = old;
  rhs = build4 (موخه_بیان, nonatomic_lhs_type, newval, rhs, NULL_ونه,
		NULL_ونه);
  سېټ_بیان_LOCATION (rhs, loc);
  جمع_کړه_stmt (rhs);

  /* if (__atomic_compare_exchange (addr, &old, &new, false, SEQ_CST, SEQ_CST))
       goto done;  */
  fndecl = builtin_decl_explicit (BUILT_دننه_ATOMIC_COMPARE_EXCHANGE);
  params->چټک_ټېل (lhs_addr);
  params->چټک_ټېل (old_addr);
  params->چټک_ټېل (newval_addr);
  params->چټک_ټېل (integer_zero_غوټه);
  params->چټک_ټېل (seq_cst);
  params->چټک_ټېل (seq_cst);
  func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, عدم);

  goto_stmt = build1 (GOTO_بیان, void_type_غوټه, بشپړ_decl);
  سېټ_بیان_LOCATION (goto_stmt, loc);

  stmt = build3 (COND_بیان, void_type_غوټه, func_call, goto_stmt, NULL_ونه);
  سېټ_بیان_LOCATION (stmt, loc);
  جمع_کړه_stmt (stmt);

  إذا (clear_call)
    جمع_کړه_stmt (clear_call);

  /* goto loop;  */
  goto_stmt  = build1 (GOTO_بیان, void_type_غوټه, loop_decl);
  سېټ_بیان_LOCATION (goto_stmt, loc);
  جمع_کړه_stmt (goto_stmt);

  /* done:  */
  جمع_کړه_stmt (بشپړ_label);

  إذا (update_call)
    جمع_کړه_stmt (update_call);

  /* Finish the compound statement.  */
  compound_stmt = c_پای_ټکی_compound_stmt (loc, compound_stmt, خطأ);

  /* NEWVAL is the value that was successfully stored, return a
     COMPOUND_EXPR of the statement and the appropriate value.  */
  أرجع build2 (COMPOUND_بیان, nonatomic_lhs_type, compound_stmt,
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

ونه
build_unary_op (location_t location, تعداد ونه_کوډ_2 کوډ, ونه xarg,
		منطقي noconvert)
{
  /* No default_conversion here.  It causes trouble for ADDR_EXPR.  */
  ونه arg = xarg;
  ونه argtype = NULL_ونه;
  تعداد ونه_کوډ_2 typecode;
  ونه val;
  ونه ret = error_mark_غوټه;
  ونه eptype = NULL_ونه;
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

  منطقي int_operands = بیان_INT_CONST_OPERANDS (xarg);
  إذا (int_operands)
    arg = remove_c_maybe_const_بیان (arg);

  إذا (کوډ != ADDR_بیان)
    arg = require_complete_type (location, arg);

  typecode = ونه_کوډ (ونه_TYPE (arg));
  إذا (typecode == ERROR_MARK)
    أرجع error_mark_غوټه;
  إذا (typecode == ENUMERAL_TYPE || typecode == BOOLEAN_TYPE)
    typecode = INTEGER_TYPE;

  إذا ((invalid_op_diag
       = targetm.invalid_unary_op (کوډ, ونه_TYPE (xarg))))
    {
      error_at (location, invalid_op_diag);
      أرجع error_mark_غوټه;
    }

  إذا (ونه_کوډ (arg) == EXCESS_PRECISION_بیان)
    {
      eptype = ونه_TYPE (arg);
      arg = ونه_عملوند (arg, 0);
    }

  بدل (کوډ)
    {
    حالة CONVERT_بیان:
      /* This is used for unary plus, because a CONVERT_EXPR
	 is enough to prevent anybody from looking inside for
	 associativity, but won't generate any code.  */
      إذا (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE
	    || typecode == FIXED_ټکی_TYPE || typecode == COMPLEX_TYPE
	    || typecode == BITINT_TYPE
	    || gnu_ویکټور_type_p (ونه_TYPE (arg))))
	{
	  error_at (location, "wrong type argument to unary plus");
	  أرجع error_mark_غوټه;
	}
      وإلا إذا (!noconvert)
	arg = default_conversion (arg);
      arg = non_lvalue_loc (location, arg);
      اكسر;

    حالة NEGATE_بیان:
      إذا (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE
	    || typecode == FIXED_ټکی_TYPE || typecode == COMPLEX_TYPE
	    || typecode == BITINT_TYPE
	    || gnu_ویکټور_type_p (ونه_TYPE (arg))))
	{
	  error_at (location, "wrong type argument to unary minus");
	  أرجع error_mark_غوټه;
	}
      وإلا إذا (!noconvert)
	arg = default_conversion (arg);
      اكسر;

    حالة بټ_NOT_بیان:
      /* ~ works on integer types and non float vectors. */
      إذا (typecode == INTEGER_TYPE
	  || typecode == BITINT_TYPE
	  || (gnu_ویکټور_type_p (ونه_TYPE (arg))
	      && !ویکټور_FLOAT_TYPE_P (ونه_TYPE (arg))))
	{
	  ونه e = arg;

	  /* Warn if the expression has boolean value.  */
	  طالما (ونه_کوډ (e) == COMPOUND_بیان)
	    e = ونه_عملوند (e, 1);

	  إذا ((C_BOOLEAN_TYPE_P (ونه_TYPE (arg))
	       || truth_ارزښت_p (ونه_کوډ (e))))
	    {
	      auto_diagnostic_ډله d;
	      إذا (warning_at (location, OPT_Wbool_operation,
				"%<~%> on a boolean expression"))
		{
		  gcc_rich_location richloc (location);
		  richloc.جمع_کړه_fixit_ورننباسه_before (location, "!");
		  inform (&richloc, "did you mean to use logical not?");
		}
	    }
	  إذا (!noconvert)
	    arg = default_conversion (arg);
	}
      وإلا إذا (typecode == COMPLEX_TYPE)
	{
	  کوډ = CONJ_بیان;
	  pedwarn (location, OPT_Wpedantic,
		   "ISO C does not support %<~%> for complex conjugation");
	  إذا (!noconvert)
	    arg = default_conversion (arg);
	}
      وإلا
	{
	  error_at (location, "wrong type argument to bit-complement");
	  أرجع error_mark_غوټه;
	}
      اكسر;

    حالة ABS_بیان:
      إذا (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE))
	{
	  error_at (location, "wrong type argument to abs");
	  أرجع error_mark_غوټه;
	}
      وإلا إذا (!noconvert)
	arg = default_conversion (arg);
      اكسر;

    حالة ABSU_بیان:
      إذا (!(typecode == INTEGER_TYPE))
	{
	  error_at (location, "wrong type argument to absu");
	  أرجع error_mark_غوټه;
	}
      وإلا إذا (!noconvert)
	arg = default_conversion (arg);
      اكسر;

    حالة CONJ_بیان:
      /* Conjugating a real value is a no-op, but allow it anyway.  */
      إذا (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE
	    || typecode == COMPLEX_TYPE))
	{
	  error_at (location, "wrong type argument to conjugation");
	  أرجع error_mark_غوټه;
	}
      وإلا إذا (!noconvert)
	arg = default_conversion (arg);
      اكسر;

    حالة TRUTH_NOT_بیان:
      إذا (typecode != INTEGER_TYPE && typecode != FIXED_ټکی_TYPE
	  && typecode != REAL_TYPE && typecode != اشاره_ګر_TYPE
	  && typecode != COMPLEX_TYPE && typecode != NULLPTR_TYPE
	  && typecode != BITINT_TYPE)
	{
	  error_at (location,
		    "wrong type argument to unary exclamation mark");
	  أرجع error_mark_غوټه;
	}
      إذا (int_operands)
	{
	  arg = c_objc_common_truthvalue_conversion (location, xarg);
	  arg = remove_c_maybe_const_بیان (arg);
	}
      وإلا
	arg = c_objc_common_truthvalue_conversion (location, arg);
      ret = invert_truthvalue_loc (location, arg);
      eptype = NULL_ونه;
      /* If the TRUTH_NOT_EXPR has been folded, reset the location.  */
      إذا (بیان_P (ret) && بیان_HAS_LOCATION (ret))
	location = بیان_LOCATION (ret);
      اذهب return_build_unary_op;

    حالة REALPART_بیان:
    حالة IMAGPART_بیان:
      ret = build_real_imag_بیان (location, کوډ, arg);
      إذا (ret == error_mark_غوټه)
	أرجع error_mark_غوټه;
      إذا (eptype && ونه_کوډ (eptype) == COMPLEX_TYPE)
	eptype = ونه_TYPE (eptype);
      اذهب return_build_unary_op;

    حالة PREINCREMENT_بیان:
    حالة POSTINCREMENT_بیان:
    حالة PREDECREMENT_بیان:
    حالة POSTDECREMENT_بیان:

      إذا (ونه_کوډ (arg) == C_MAYBE_CONST_بیان)
	{
	  ونه inner = build_unary_op (location, کوډ,
				       C_MAYBE_CONST_بیان_بیان (arg),
				       noconvert);
	  إذا (inner == error_mark_غوټه)
	    أرجع error_mark_غوټه;
	  ret = build2 (C_MAYBE_CONST_بیان, ونه_TYPE (inner),
			C_MAYBE_CONST_بیان_PRE (arg), inner);
	  gcc_assert (!C_MAYBE_CONST_بیان_INT_OPERANDS (arg));
	  C_MAYBE_CONST_بیان_NON_CONST (ret) = 1;
	  اذهب return_build_unary_op;
	}

      /* Complain about anything that is not a true lvalue.  In
	 Objective-C, skip this check for property_refs.  */
      إذا (!objc_is_property_ref (arg)
	  && !lvalue_or_else (location,
			      arg, ((کوډ == PREINCREMENT_بیان
				     || کوډ == POSTINCREMENT_بیان)
				    ? lv_increment
				    : lv_decrement)))
	أرجع error_mark_غوټه;

      إذا (warn_cxx_compat && ونه_کوډ (ونه_TYPE (arg)) == ENUMERAL_TYPE)
	{
	  إذا (کوډ == PREINCREMENT_بیان || کوډ == POSTINCREMENT_بیان)
	    warning_at (location, OPT_Wc___compat,
			"increment of enumeration value is invalid in C++");
	  وإلا
	    warning_at (location, OPT_Wc___compat,
			"decrement of enumeration value is invalid in C++");
	}

      إذا (C_BOOLEAN_TYPE_P (ونه_TYPE (arg)))
	{
	  إذا (کوډ == PREINCREMENT_بیان || کوډ == POSTINCREMENT_بیان)
	    warning_at (location, OPT_Wbool_operation,
			"increment of a boolean expression");
	  وإلا
	    warning_at (location, OPT_Wbool_operation,
			"decrement of a boolean expression");
	}

      /* Ensure the argument is fully folded inside any SAVE_EXPR.  */
      arg = c_fully_fold (arg, خطأ, عدم, ریښتیا);

      منطقي atomic_op;
      atomic_op = really_atomic_lvalue (arg);

      /* Increment or decrement the real part of the value,
	 and don't change the imaginary part.  */
      إذا (typecode == COMPLEX_TYPE)
	{
	  ونه real, imag;

	  pedwarn_c23 (location, OPT_Wpedantic,
		       "ISO C does not support %<++%> and %<--%> on complex "
		       "types before C2Y");

	  إذا (!atomic_op)
	    {
	      arg = stabilize_reference (arg);
	      real = build_unary_op (بیان_LOCATION (arg), REALPART_بیان, arg,
				     ریښتیا);
	      imag = build_unary_op (بیان_LOCATION (arg), IMAGPART_بیان, arg,
				     ریښتیا);
	      real = build_unary_op (بیان_LOCATION (arg), کوډ, real, ریښتیا);
	      إذا (real == error_mark_غوټه || imag == error_mark_غوټه)
		أرجع error_mark_غوټه;
	      ret = build2 (COMPLEX_بیان, ونه_TYPE (arg),
			    real, imag);
	      اذهب return_build_unary_op;
	    }
	}

      /* Report invalid types.  */

      إذا (typecode != اشاره_ګر_TYPE && typecode != FIXED_ټکی_TYPE
	  && typecode != INTEGER_TYPE && typecode != REAL_TYPE
	  && typecode != COMPLEX_TYPE && typecode != BITINT_TYPE
	  && !gnu_ویکټور_type_p (ونه_TYPE (arg)))
	{
	  إذا (کوډ == PREINCREMENT_بیان || کوډ == POSTINCREMENT_بیان)
	    error_at (location, "wrong type argument to increment");
	  وإلا
	    error_at (location, "wrong type argument to decrement");

	  أرجع error_mark_غوټه;
	}

      {
	ونه inc;

	argtype = ونه_TYPE (arg);

	/* Compute the increment.  */

	إذا (typecode == اشاره_ګر_TYPE)
	  {
	    /* If pointer target is an incomplete type,
	       we just cannot know how to do the arithmetic.  */
	    إذا (!COMPLETE_OR_VOID_TYPE_P (ونه_TYPE (argtype)))
	      {
		إذا (کوډ == PREINCREMENT_بیان || کوډ == POSTINCREMENT_بیان)
		  error_at (location,
			    "increment of pointer to an incomplete type %qT",
			    ونه_TYPE (argtype));
		وإلا
		  error_at (location,
			    "decrement of pointer to an incomplete type %qT",
			    ونه_TYPE (argtype));
	      }
	    وإلا إذا (ونه_کوډ (ونه_TYPE (argtype)) == FUNCTION_TYPE
		     || VOID_TYPE_P (ونه_TYPE (argtype)))
	      {
		إذا (کوډ == PREINCREMENT_بیان || کوډ == POSTINCREMENT_بیان)
		  pedwarn (location, OPT_Wpointer_arith,
			   "wrong type argument to increment");
		وإلا
		  pedwarn (location, OPT_Wpointer_arith,
			   "wrong type argument to decrement");
	      }
	    وإلا
	      verify_type_context (location, TCTX_اشاره_ګر_ARITH,
				   ونه_TYPE (argtype));

	    inc = c_اندازه_دننه_بایټونه (ونه_TYPE (argtype));
	    inc = convert_منزل_ptrofftype_loc (location, inc);
	  }
	وإلا إذا (FRACT_ډېرپېښ_P (TYPE_ډېرپېښ (argtype)))
	  {
	    /* For signed fract types, we invert ++ to -- or
	       -- to ++, and change inc from 1 to -1, because
	       it is not possible to represent 1 in signed fract constants.
	       For unsigned fract types, the result always overflows and
	       we get an undefined (original) or the maximum value.  */
	    إذا (کوډ == PREINCREMENT_بیان)
	      کوډ = PREDECREMENT_بیان;
	    وإلا إذا (کوډ == PREDECREMENT_بیان)
	      کوډ = PREINCREMENT_بیان;
	    وإلا إذا (کوډ == POSTINCREMENT_بیان)
	      کوډ = POSTDECREMENT_بیان;
	    وإلا /* code == POSTDECREMENT_EXPR  */
	      کوډ = POSTINCREMENT_بیان;

	    inc = integer_minus_one_غوټه;
	    inc = convert (argtype, inc);
	  }
	وإلا
	  {
	    inc = ویکټور_TYPE_P (argtype)
	      ? build_one_cst (argtype)
	      : integer_one_غوټه;
	    inc = convert (argtype, inc);
	  }

	/* If 'arg' is an Objective-C PROPERTY_REF expression, then we
	   need to ask Objective-C to build the increment or decrement
	   expression for it.  */
	إذا (objc_is_property_ref (arg))
	  أرجع objc_build_incr_بیان_for_property_ref (location, کوډ,
							arg, inc);

	/* Report a read-only lvalue.  */
	إذا (TYPE_READONLY (argtype))
	  {
	    readonly_error (location, arg,
			    ((کوډ == PREINCREMENT_بیان
			      || کوډ == POSTINCREMENT_بیان)
			     ? lv_increment : lv_decrement));
	    أرجع error_mark_غوټه;
	  }
	وإلا إذا (ونه_READONLY (arg))
	  readonly_warning (arg,
			    ((کوډ == PREINCREMENT_بیان
			      || کوډ == POSTINCREMENT_بیان)
			     ? lv_increment : lv_decrement));

	/* If the argument is atomic, use the special code sequences for
	   atomic compound assignment.  */
	إذا (atomic_op)
	  {
	    arg = stabilize_reference (arg);
	    ret = build_atomic_ټاکل (location, arg,
				       ((کوډ == PREINCREMENT_بیان
					 || کوډ == POSTINCREMENT_بیان)
					? PLUS_بیان
					: MINUS_بیان),
				       (FRACT_ډېرپېښ_P (TYPE_ډېرپېښ (argtype))
					? inc
					: integer_one_غوټه),
				       (کوډ == POSTINCREMENT_بیان
					|| کوډ == POSTDECREMENT_بیان));
	    اذهب return_build_unary_op;
	  }

	ونه true_res;
	إذا (c_hardbool_type_attr (ونه_TYPE (arg), عدم, &true_res))
	  {
	    ونه larg = stabilize_reference (arg);
	    ونه sarg = save_بیان (larg);
	    بدل (کوډ)
	      {
	      حالة PREINCREMENT_بیان:
		val = build2 (MODIFY_بیان, ونه_TYPE (larg), larg, true_res);
		val = build2 (COMPOUND_بیان, ونه_TYPE (larg), sarg, val);
		اكسر;
	      حالة POSTINCREMENT_بیان:
		val = build2 (MODIFY_بیان, ونه_TYPE (larg), larg, true_res);
		val = build2 (COMPOUND_بیان, ونه_TYPE (larg), val, sarg);
		val = build2 (COMPOUND_بیان, ونه_TYPE (larg), sarg, val);
		اكسر;
	      حالة PREDECREMENT_بیان:
		{
		  ونه rarg = convert_lvalue_منزل_rvalue (location, sarg,
							ریښتیا, ریښتیا);
		  rarg = invert_truthvalue_loc (location, rarg);
		  rarg = convert (ونه_TYPE (sarg), rarg);
		  val = build2 (MODIFY_بیان, ونه_TYPE (larg), larg, rarg);
		}
		اكسر;
	      حالة POSTDECREMENT_بیان:
		{
		  ونه rarg = convert_lvalue_منزل_rvalue (location, sarg,
							ریښتیا, ریښتیا);
		  rarg = invert_truthvalue_loc (location, rarg);
		  ونه iarg = convert (ونه_TYPE (larg), rarg);
		  val = build2 (MODIFY_بیان, ونه_TYPE (larg), larg, iarg);
		  val = build2 (COMPOUND_بیان, ونه_TYPE (larg), val, sarg);
		  val = build2 (COMPOUND_بیان, ونه_TYPE (larg), sarg, val);
		}
		اكسر;
	      افتراضي:
		gcc_unreachable ();
	      }
	    ونه_SIDE_EFFECTS (val) = 1;
	  }
	وإلا إذا (C_BOOLEAN_TYPE_P (ونه_TYPE (arg)))
	  val = boolean_increment (کوډ, arg);
	وإلا
	  val = build2 (کوډ, ونه_TYPE (arg), arg, inc);
	ونه_SIDE_EFFECTS (val) = 1;
	إذا (TYPE_QUALS (ونه_TYPE (val)) != TYPE_UNQUALIFIED)
	  ونه_TYPE (val) = c_build_qualified_type (ونه_TYPE (val),
						    TYPE_UNQUALIFIED);
	ret = val;
	اذهب return_build_unary_op;
      }

    حالة ADDR_بیان:
      /* Note that this operation never does default_conversion.  */

      /* The operand of unary '&' must be an lvalue (which excludes
	 expressions of type void), or, in C99, the result of a [] or
	 unary '*' operator.  */
      إذا (VOID_TYPE_P (ونه_TYPE (arg))
	  && TYPE_QUALS (ونه_TYPE (arg)) == TYPE_UNQUALIFIED
	  && (!غیرمستقیم_REF_P (arg) || !flag_isoc99))
	pedwarn (location, 0, "taking address of expression of type %<void%>");

      /* Let &* cancel out to simplify resulting code.  */
      إذا (غیرمستقیم_REF_P (arg))
	{
	  /* Don't let this be an lvalue.  */
	  إذا (lvalue_p (ونه_عملوند (arg, 0)))
	    أرجع non_lvalue_loc (location, ونه_عملوند (arg, 0));
	  ret = ونه_عملوند (arg, 0);
	  اذهب return_build_unary_op;
	}

      /* Anything not already handled and not a true memory reference
	 or a non-lvalue array is an error.  */
      إذا (typecode != FUNCTION_TYPE && !noconvert
	  && !lvalue_or_else (location, arg, lv_addressof))
	أرجع error_mark_غوټه;

      /* Move address operations inside C_MAYBE_CONST_EXPR to simplify
	 folding later.  */
      إذا (ونه_کوډ (arg) == C_MAYBE_CONST_بیان)
	{
	  ونه inner = build_unary_op (location, کوډ,
				       C_MAYBE_CONST_بیان_بیان (arg),
				       noconvert);
	  ret = build2 (C_MAYBE_CONST_بیان, ونه_TYPE (inner),
			C_MAYBE_CONST_بیان_PRE (arg), inner);
	  gcc_assert (!C_MAYBE_CONST_بیان_INT_OPERANDS (arg));
	  C_MAYBE_CONST_بیان_NON_CONST (ret)
	    = C_MAYBE_CONST_بیان_NON_CONST (arg);
	  اذهب return_build_unary_op;
	}

      /* Ordinary case; arg is a COMPONENT_REF or a decl.  */

      argtype = ونه_TYPE (arg);

      /* If the lvalue is const or volatile, merge that into the type
	 to which the address will point.  This is only needed
	 for function types.  */
      إذا ((DECL_P (arg) || REFERENCE_CLASS_P (arg))
	  && (ونه_READONLY (arg) || ونه_THIS_VOLATILE (arg))
	  && ونه_کوډ (argtype) == FUNCTION_TYPE)
	{
	  صحيح orig_quals = TYPE_QUALS (strip_array_types (argtype));
	  صحيح quals = orig_quals;

	  إذا (ونه_READONLY (arg))
	    quals |= TYPE_QUAL_CONST;
	  إذا (ونه_THIS_VOLATILE (arg))
	    quals |= TYPE_QUAL_VOLATILE;

	  argtype = c_build_qualified_type (argtype, quals);
	}

      بدل (ونه_کوډ (arg))
	{
	حالة COMPONENT_REF:
	  إذا (DECL_C_بټ_ډګر (ونه_عملوند (arg, 1)))
	    {
	      error_at (location, "cannot take address of bit-field %qD",
			ونه_عملوند (arg, 1));
	      أرجع error_mark_غوټه;
	    }

	  /* fall through */

	حالة ARRAY_REF:
	  إذا (TYPE_سرچپه_STORAGE_ترتیب (ونه_TYPE (ونه_عملوند (arg, 0))))
	    {
	      إذا (!AGGREGATE_TYPE_P (ونه_TYPE (arg))
		  && !اشاره_ګر_TYPE_P (ونه_TYPE (arg))
		  && !ویکټور_TYPE_P (ونه_TYPE (arg)))
		{
		  error_at (location, "cannot take address of scalar with "
			    "reverse storage order");
		  أرجع error_mark_غوټه;
		}

	      إذا (ونه_کوډ (ونه_TYPE (arg)) == ARRAY_TYPE
		  && TYPE_سرچپه_STORAGE_ترتیب (ونه_TYPE (arg)))
		warning_at (location, OPT_Wscalar_storage_ترتیب,
			    "address of array with reverse scalar storage "
			    "order requested");
	    }

	افتراضي:
	  اكسر;
	}

      إذا (!c_mark_addressable (arg))
	أرجع error_mark_غوټه;

      gcc_assert (ونه_کوډ (arg) != COMPONENT_REF
		  || !DECL_C_بټ_ډګر (ونه_عملوند (arg, 1)));

      argtype = c_build_اشاره_ګر_type (argtype);

      /* ??? Cope with user tricks that amount to offsetof.  Delete this
	 when we have proper support for integer constant expressions.  */
      val = get_بنسټ_پته (arg);
      إذا (val && غیرمستقیم_REF_P (val)
          && ونه_CONSTANT (ونه_عملوند (val, 0)))
	{
	  ret = fold_offsetof (arg, argtype);
	  اذهب return_build_unary_op;
	}

      val = build1 (ADDR_بیان, argtype, arg);

      ret = val;
      اذهب return_build_unary_op;

    حالة PAREN_بیان:
      ret = build1 (کوډ, ونه_TYPE (arg), arg);
      اذهب return_build_unary_op;

    افتراضي:
      gcc_unreachable ();
    }

  إذا (argtype == NULL_ونه)
    argtype = ونه_TYPE (arg);
  إذا (ونه_کوډ (arg) == INTEGER_CST)
    ret = (require_constant_ارزښت
	   ? fold_build1_initializer_loc (location, کوډ, argtype, arg)
	   : fold_build1_loc (location, کوډ, argtype, arg));
  وإلا
    ret = build1 (کوډ, argtype, arg);
 return_build_unary_op:
  gcc_assert (ret != error_mark_غوټه);
  إذا (ونه_کوډ (ret) == INTEGER_CST && !ونه_ډکېدنه (ret)
      && !(ونه_کوډ (xarg) == INTEGER_CST && !ونه_ډکېدنه (xarg)))
    ret = build1 (NOP_بیان, ونه_TYPE (ret), ret);
  وإلا إذا (ونه_کوډ (ret) != INTEGER_CST && int_operands)
    ret = note_integer_operands (ret);
  إذا (eptype)
    ret = build1 (EXCESS_PRECISION_بیان, eptype, ret);
  protected_سېټ_بیان_location (ret, location);
  أرجع ret;
}

/* Return nonzero if REF is an lvalue valid for this language.
   Lvalues can be assigned, unless their type has TYPE_READONLY.
   Lvalues can have their address taken, unless they have C_DECL_REGISTER.  */

منطقي
lvalue_p (const_ونه ref)
{
  ثابت تعداد ونه_کوډ_2 کوډ = ونه_کوډ (ref);

  بدل (کوډ)
    {
    حالة REALPART_بیان:
    حالة IMAGPART_بیان:
    حالة COMPONENT_REF:
      أرجع lvalue_p (ونه_عملوند (ref, 0));

    حالة C_MAYBE_CONST_بیان:
      أرجع lvalue_p (ونه_عملوند (ref, 1));

    حالة COMPOUND_LITERAL_بیان:
    حالة STRING_CST:
      أرجع ریښتیا;

    حالة MEM_REF:
    حالة موخه_MEM_REF:
      /* MEM_REFs can appear from -fgimple parsing or folding, so allow them
	 here as well.  */
    حالة غیرمستقیم_REF:
    حالة ARRAY_REF:
    حالة VAR_DECL:
    حالة PARM_DECL:
    حالة پایله_DECL:
    حالة ERROR_MARK:
      أرجع (ونه_کوډ (ونه_TYPE (ref)) != FUNCTION_TYPE
	      && ونه_کوډ (ونه_TYPE (ref)) != لاره_TYPE);

    حالة BIND_بیان:
      أرجع ونه_کوډ (ونه_TYPE (ref)) == ARRAY_TYPE;

    حالة CALL_بیان:
      أرجع is_access_with_اندازه_p (ref);

    افتراضي:
      أرجع خطأ;
    }
}

/* Give a warning for storing in something that is read-only in GCC
   terms but not const in ISO C terms.  */

ساكن فراغ
readonly_warning (ونه arg, تعداد lvalue_use use)
{
  بدل (use)
    {
    حالة lv_ټاکل:
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
lvalue_or_else (location_t loc, const_ونه ref, تعداد lvalue_use use)
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
c_mark_addressable (ونه توانیز_تابع, منطقي array_ref_p, منطقي override_ثبتوونکی)
{
  ونه x = توانیز_تابع;

  طالما (1)
    بدل (ونه_کوډ (x))
      {
      حالة VIEW_CONVERT_بیان:
	إذا (array_ref_p
	    && ونه_کوډ (ونه_TYPE (x)) == ARRAY_TYPE
	    && ویکټور_TYPE_P (ونه_TYPE (ونه_عملوند (x, 0))))
	  أرجع ریښتیا;
	x = ونه_عملوند (x, 0);
	اكسر;

      حالة COMPONENT_REF:
	إذا (DECL_C_بټ_ډګر (ونه_عملوند (x, 1)))
	  {
	    error ("cannot take address of bit-field %qD",
		   ونه_عملوند (x, 1));
	    أرجع خطأ;
	  }
	/* FALLTHRU */
      حالة ADDR_بیان:
      حالة ARRAY_REF:
      حالة REALPART_بیان:
      حالة IMAGPART_بیان:
	x = ونه_عملوند (x, 0);
	اكسر;

      حالة COMPOUND_LITERAL_بیان:
	إذا (C_DECL_ثبتوونکی (COMPOUND_LITERAL_بیان_DECL (x)))
	  {
	    إذا (override_ثبتوونکی)
	      DECL_ثبتوونکی (COMPOUND_LITERAL_بیان_DECL (x)) = 0;
	    وإلا
	      {
		error ("address of register compound literal requested");
		أرجع خطأ;
	      }
	  }
	ونه_ADDRESSABLE (x) = 1;
	ونه_ADDRESSABLE (COMPOUND_LITERAL_بیان_DECL (x)) = 1;
	أرجع ریښتیا;

      حالة CONSTRUCTOR:
	ونه_ADDRESSABLE (x) = 1;
	أرجع ریښتیا;

      حالة VAR_DECL:
      حالة CONST_DECL:
      حالة PARM_DECL:
      حالة پایله_DECL:
	إذا (C_DECL_ثبتوونکی (x)
	    && DECL_NONLOCAL (x))
	  {
	    إذا (ونه_عامه (x) || is_global_var (x))
	      {
		error
		  ("global register variable %qD used in nested function", x);
		أرجع خطأ;
	      }
	    pedwarn (ننوت_location, 0, "register variable %qD used in nested function", x);
	  }
	وإلا إذا (C_DECL_ثبتوونکی (x))
	  {
	    إذا (ونه_عامه (x) || is_global_var (x))
	      error ("address of global register variable %qD requested", x);
	    وإلا إذا (override_ثبتوونکی && !DECL_HARD_ثبتوونکی (x))
	      {
		DECL_ثبتوونکی (x) = 0;
		ونه_ADDRESSABLE (x) = 1;
		mark_decl_کارول_شوی (x, ریښتیا);
		أرجع ریښتیا;
	      }
	    وإلا
	      error ("address of register variable %qD requested", x);
	    أرجع خطأ;
	  }

	/* FALLTHRU */
      حالة FUNCTION_DECL:
	ونه_ADDRESSABLE (x) = 1;
	mark_decl_کارول_شوی (x, ریښتیا);
	/* FALLTHRU */
      افتراضي:
	أرجع ریښتیا;
    }
}

/* Convert EXPR to TYPE, warning about conversion problems with
   constants.  SEMANTIC_TYPE is the type this conversion would use
   without excess precision. If SEMANTIC_TYPE is NULL, this function
   is equivalent to convert_and_check. This function is a wrapper that
   handles conversions that may be different than
   the usual ones because of excess precision.  */

ساكن ونه
ep_convert_and_check (location_t loc, ونه type, ونه بیان,
		      ونه semantic_type)
{
  إذا (ونه_TYPE (بیان) == type)
    أرجع بیان;

  /* For C11, integer conversions may have results with excess
     precision.  */
  إذا (flag_isoc11 || !semantic_type)
    أرجع convert_and_check (loc, type, بیان);

  إذا (ونه_کوډ (ونه_TYPE (بیان)) == INTEGER_TYPE
      && ونه_TYPE (بیان) != semantic_type)
    {
      /* For integers, we need to check the real conversion, not
	 the conversion to the excess precision type.  */
      بیان = convert_and_check (loc, semantic_type, بیان);
    }
  /* Result type is the excess precision type, which should be
     large enough, so do not check.  */
  أرجع convert (type, بیان);
}

/* If EXPR refers to a built-in declared without a prototype returns
   the actual type of the built-in and, if non-null, set *BLTIN to
   a pointer to the built-in.  Otherwise return the type of EXPR
   and clear *BLTIN if non-null.  */

ساكن ونه
type_or_builtin_type (ونه بیان, ونه *bltin = عدم)
{
  ونه dummy;
  إذا (!bltin)
    bltin = &dummy;

  *bltin = NULL_ونه;

  ونه type = ونه_TYPE (بیان);
  إذا (ونه_کوډ (بیان) != ADDR_بیان)
    أرجع type;

  ونه oper = ونه_عملوند (بیان, 0);
  إذا (!DECL_P (oper)
      || ونه_کوډ (oper) != FUNCTION_DECL
      || !fndecl_built_دننه_p (oper, BUILT_دننه_نورمال))
    أرجع type;

  built_دننه_function کوډ = DECL_FUNCTION_کوډ (oper);
  إذا (!C_DECL_BUILTIN_PROTOTYPE (oper))
    أرجع type;

  إذا ((*bltin = builtin_decl_implicit (کوډ)))
    type = c_build_اشاره_ګر_type (ونه_TYPE (*bltin));

  أرجع type;
}

/* Build and return a conditional expression IFEXP ? OP1 : OP2.  If
   IFEXP_BCP then the condition is a call to __builtin_constant_p, and
   if folded to an integer constant then the unselected half may
   contain arbitrary operations not normally permitted in constant
   expressions.  Set the location of the expression to LOC.  */

ونه
build_conditional_بیان (location_t colon_loc, ونه ifexp, منطقي ifexp_bcp,
			ونه op1, ونه op1_original_type, location_t op1_loc,
			ونه op2, ونه op2_original_type, location_t op2_loc)
{
  ونه type1;
  ونه type2;
  ونه پایله_type = عدم;
  ونه semantic_پایله_type = عدم;
  ونه orig_op1 = op1, orig_op2 = op2;
  منطقي int_const, op1_int_operands, op2_int_operands, int_operands;
  منطقي ifexp_int_operands;
  ونه ret;

  op1_int_operands = بیان_INT_CONST_OPERANDS (orig_op1);
  إذا (op1_int_operands)
    op1 = remove_c_maybe_const_بیان (op1);
  op2_int_operands = بیان_INT_CONST_OPERANDS (orig_op2);
  إذا (op2_int_operands)
    op2 = remove_c_maybe_const_بیان (op2);
  ifexp_int_operands = بیان_INT_CONST_OPERANDS (ifexp);
  إذا (ifexp_int_operands)
    ifexp = remove_c_maybe_const_بیان (ifexp);

  /* Promote both alternatives.  */

  إذا (ونه_کوډ (ونه_TYPE (op1)) != VOID_TYPE)
    op1 = default_conversion (op1);
  إذا (ونه_کوډ (ونه_TYPE (op2)) != VOID_TYPE)
    op2 = default_conversion (op2);

  إذا (ونه_کوډ (ifexp) == ERROR_MARK
      || ونه_کوډ (ونه_TYPE (op1)) == ERROR_MARK
      || ونه_کوډ (ونه_TYPE (op2)) == ERROR_MARK)
    أرجع error_mark_غوټه;

  ونه bltin1 = NULL_ونه;
  ونه bltin2 = NULL_ونه;
  type1 = type_or_builtin_type (op1, &bltin1);
  ثابت تعداد ونه_کوډ_2 code1 = ونه_کوډ (type1);
  type2 = type_or_builtin_type (op2, &bltin2);
  ثابت تعداد ونه_کوډ_2 code2 = ونه_کوډ (type2);

  إذا (code1 == اشاره_ګر_TYPE && reject_gcc_builtin (op1))
    أرجع error_mark_غوټه;

  إذا (code2 == اشاره_ګر_TYPE && reject_gcc_builtin (op2))
    أرجع error_mark_غوټه;

  /* C90 does not permit non-lvalue arrays in conditional expressions.
     In C99 they will be pointers by now.  */
  إذا (code1 == ARRAY_TYPE || code2 == ARRAY_TYPE)
    {
      error_at (colon_loc, "non-lvalue array in conditional expression");
      أرجع error_mark_غوټه;
    }

  إذا ((ونه_کوډ (op1) == EXCESS_PRECISION_بیان
       || ونه_کوډ (op2) == EXCESS_PRECISION_بیان)
      && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	  || code1 == COMPLEX_TYPE || code1 == BITINT_TYPE)
      && (code2 == INTEGER_TYPE || code2 == REAL_TYPE
	  || code2 == COMPLEX_TYPE || code2 == BITINT_TYPE))
    {
      semantic_پایله_type = c_common_type (type1, type2);
      إذا (ونه_کوډ (op1) == EXCESS_PRECISION_بیان)
	{
	  op1 = ونه_عملوند (op1, 0);
	  type1 = ونه_TYPE (op1);
	  gcc_assert (ونه_کوډ (type1) == code1);
	}
      إذا (ونه_کوډ (op2) == EXCESS_PRECISION_بیان)
	{
	  op2 = ونه_عملوند (op2, 0);
	  type2 = ونه_TYPE (op2);
	  gcc_assert (ونه_کوډ (type2) == code2);
	}
    }

  إذا (warn_cxx_compat)
    {
      ونه t1 = op1_original_type ? op1_original_type : ونه_TYPE (orig_op1);
      ونه t2 = op2_original_type ? op2_original_type : ونه_TYPE (orig_op2);

      إذا (ونه_کوډ (t1) == ENUMERAL_TYPE
	  && ونه_کوډ (t2) == ENUMERAL_TYPE
	  && TYPE_MAIN_VARIANT (t1) != TYPE_MAIN_VARIANT (t2))
	warning_at (colon_loc, OPT_Wc___compat,
		    "different enum types in conditional is "
		    "invalid in C++: %qT vs %qT", t1, t2);
    }

  إذا (warn_zero_as_null_اشاره_ګر_constant
      && c_inhibit_evaluation_warnings == 0)
    {
      إذا ((code1 == اشاره_ګر_TYPE || code1 == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type2) && null_اشاره_ګر_constant_p (orig_op2))
	warning_at (op2_loc, OPT_Wzero_as_null_اشاره_ګر_constant,
		    "zero as null pointer constant");

      إذا ((code2 == اشاره_ګر_TYPE || code2 == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type1) && null_اشاره_ګر_constant_p (orig_op1))
	warning_at (op1_loc, OPT_Wzero_as_null_اشاره_ګر_constant,
		    "zero as null pointer constant");
    }

  /* Quickly detect the usual case where op1 and op2 have the same type
     after promotion.  */
  إذا (TYPE_MAIN_VARIANT (type1) == TYPE_MAIN_VARIANT (type2))
    {
      إذا (type1 == type2)
	پایله_type = type1;
      وإلا
	پایله_type = TYPE_MAIN_VARIANT (type1);
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
      ونه eptype1 = type1;
      ونه eptype2 = type2;
      إذا (flag_isoc11)
	{
	  ونه eptype;
	  إذا (ANY_INTEGRAL_TYPE_P (type1)
	      && (eptype = excess_precision_type (type2)) != NULL_ونه)
	    {
	      eptype2 = eptype;
	      إذا (!semantic_پایله_type)
		semantic_پایله_type = c_common_type (type1, type2);
	    }
	  وإلا إذا (ANY_INTEGRAL_TYPE_P (type2)
		   && (eptype = excess_precision_type (type1)) != NULL_ونه)
	    {
	      eptype1 = eptype;
	      إذا (!semantic_پایله_type)
		semantic_پایله_type = c_common_type (type1, type2);
	    }
	}
      پایله_type = c_common_type (eptype1, eptype2);
      إذا (پایله_type == error_mark_غوټه)
	أرجع error_mark_غوټه;
      do_warn_double_promotion (پایله_type, type1, type2,
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
	  صحيح unsigned_op1 = TYPE_UNSIGNED (ونه_TYPE (orig_op1));
	  صحيح unsigned_op2 = TYPE_UNSIGNED (ونه_TYPE (orig_op2));

	  إذا (unsigned_op1 ^ unsigned_op2)
	    {
	      /* Do not warn if the result type is signed, since the
		 signed type will only be chosen if it can represent
		 all the values of the unsigned type.  */
	      إذا (!TYPE_UNSIGNED (پایله_type))
		/* OK */;
	      وإلا
		{
		  منطقي op1_maybe_const = ریښتیا;
		  منطقي op2_maybe_const = ریښتیا;

		  /* Do not warn if the signed quantity is an
		     unsuffixed integer literal (or some static
		     constant expression involving such literals) and
		     it is non-negative.  This warning requires the
		     operands to be folded for best results, so do
		     that folding in this case even without
		     warn_sign_compare to avoid warning options
		     possibly affecting code generation.  */
		  c_inhibit_evaluation_warnings
		    += (ifexp == truthvalue_false_غوټه);
		  op1 = c_fully_fold (op1, require_constant_ارزښت,
				      &op1_maybe_const);
		  c_inhibit_evaluation_warnings
		    -= (ifexp == truthvalue_false_غوټه);

		  c_inhibit_evaluation_warnings
		    += (ifexp == truthvalue_true_غوټه);
		  op2 = c_fully_fold (op2, require_constant_ارزښت,
				      &op2_maybe_const);
		  c_inhibit_evaluation_warnings
		    -= (ifexp == truthvalue_true_غوټه);

		  إذا (warn_sign_compare)
		    {
		      إذا ((unsigned_op2
			   && ونه_بیان_nonnegative_p (op1))
			  || (unsigned_op1
			      && ونه_بیان_nonnegative_p (op2)))
			/* OK */;
		      وإلا إذا (unsigned_op2)
			warning_at (op1_loc, OPT_Wsign_compare,
				    "operand of %<?:%> changes signedness from "
				    "%qT to %qT due to unsignedness of other "
				    "operand", ونه_TYPE (orig_op1),
				    ونه_TYPE (orig_op2));
		      وإلا
			warning_at (op2_loc, OPT_Wsign_compare,
				    "operand of %<?:%> changes signedness from "
				    "%qT to %qT due to unsignedness of other "
				    "operand", ونه_TYPE (orig_op2),
				    ونه_TYPE (orig_op1));
		    }
		  إذا (!op1_maybe_const || ونه_کوډ (op1) != INTEGER_CST)
		    op1 = c_wrap_maybe_const (op1, !op1_maybe_const);
		  إذا (!op2_maybe_const || ونه_کوډ (op2) != INTEGER_CST)
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
      پایله_type = void_type_غوټه;
    }
  وإلا إذا (code1 == اشاره_ګر_TYPE && code2 == اشاره_ګر_TYPE)
    {
      addr_space_t as1 = TYPE_ADDR_SPACE (ونه_TYPE (type1));
      addr_space_t as2 = TYPE_ADDR_SPACE (ونه_TYPE (type2));
      addr_space_t as_common;

      إذا (comp_موخه_types (colon_loc, type1, type2))
	{
	  ifexp = save_بیان (ifexp);
	  پایله_type = common_اشاره_ګر_type (type1, type2, ifexp);
	}
      وإلا إذا (null_اشاره_ګر_constant_p (orig_op1))
	پایله_type = type2;
      وإلا إذا (null_اشاره_ګر_constant_p (orig_op2))
	پایله_type = type1;
      وإلا إذا (!addr_space_superset (as1, as2, &as_common))
	{
	  error_at (colon_loc, "pointers to disjoint address spaces "
		    "used in conditional expression");
	  أرجع error_mark_غوټه;
	}
      وإلا إذا ((VOID_TYPE_P (ونه_TYPE (type1))
		&& !TYPE_ATOMIC (ونه_TYPE (type1)))
	       || (VOID_TYPE_P (ونه_TYPE (type2))
		   && !TYPE_ATOMIC (ونه_TYPE (type2))))
	{
	  ونه t1 = ونه_TYPE (type1);
	  ونه t2 = ونه_TYPE (type2);
	  إذا (!(VOID_TYPE_P (t1)
		&& !TYPE_ATOMIC (t1)))
	   {
	     /* roles are swapped */
	     t1 = t2;
	     t2 = ونه_TYPE (type1);
	   }
	  ونه t2_stripped = strip_array_types (t2);
	  إذا ((ونه_کوډ (t2) == ARRAY_TYPE)
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
	  إذا (ونه_کوډ (t2) == FUNCTION_TYPE)
	    pedwarn (colon_loc, OPT_Wpedantic,
		     "ISO C forbids conditional expr between "
		     "%<void *%> and function pointer");
	  /* for array, use qualifiers of element type */
	  إذا (flag_isoc23)
	    t2 = t2_stripped;
	  پایله_type = c_build_اشاره_ګر_type (qualify_type (t1, t2));
	}
      /* Objective-C pointer comparisons are a bit more lenient.  */
      وإلا إذا (objc_have_common_type (type1, type2, -3, NULL_ونه))
	پایله_type = objc_common_type (type1, type2);
      وإلا
	{
	  صحيح qual = ENCODE_QUAL_ADDR_SPACE (as_common);
	  تعداد diagnostics::ډول ډول = diagnostics::ډول::permerror;
	  إذا (!flag_isoc99)
	    /* This downgrade to a warning ensures that -std=gnu89
	       -pedantic-errors does not flag these mismatches between
	       builtins as errors (as diagnostics::kind::permerror would)
	       ISO C99 and later do not have implicit function declarations,
	       so the mismatch cannot occur naturally there.  */
	    ډول = (bltin1 && bltin2
		    ? diagnostics::ډول::warning
		    : diagnostics::ډول::pedwarn);
	  إذا (emit_diagnostic (ډول, colon_loc, OPT_Wincompatible_اشاره_ګر_types,
			       "pointer type mismatch "
			       "in conditional expression"))
	    {
	      inform (op1_loc, "first expression has type %qT", type1);
	      inform (op2_loc, "second expression has type %qT", type2);
	    }
	  پایله_type = c_build_اشاره_ګر_type
			  (c_build_qualified_type (void_type_غوټه, qual));
	}
    }
  وإلا إذا (code1 == اشاره_ګر_TYPE
	   && (code2 == INTEGER_TYPE || code2 == BITINT_TYPE))
    {
      إذا (!null_اشاره_ګر_constant_p (orig_op2))
	permerror_opt (colon_loc, OPT_Wint_conversion,
		       "pointer/integer type mismatch "
		       "in conditional expression");
      وإلا
	{
	  op2 = null_اشاره_ګر_غوټه;
	}
      پایله_type = type1;
    }
  وإلا إذا (code2 == اشاره_ګر_TYPE
	   && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
    {
      إذا (!null_اشاره_ګر_constant_p (orig_op1))
	permerror_opt (colon_loc, OPT_Wint_conversion,
		       "pointer/integer type mismatch "
		       "in conditional expression");
      وإلا
	{
	  op1 = null_اشاره_ګر_غوټه;
	}
      پایله_type = type2;
    }
  /* 6.5.15: "if one is a null pointer constant (other than a pointer) or has
     type nullptr_t and the other is a pointer, the result type is the pointer
     type."  */
  وإلا إذا (code1 == NULLPTR_TYPE && code2 == اشاره_ګر_TYPE)
    پایله_type = type2;
  وإلا إذا (code1 == اشاره_ګر_TYPE && code2 == NULLPTR_TYPE)
    پایله_type = type1;
  وإلا إذا (ریکارډ_OR_UNION_TYPE_P (type1) && ریکارډ_OR_UNION_TYPE_P (type2)
	   && comptypes (TYPE_MAIN_VARIANT (type1),
			 TYPE_MAIN_VARIANT (type2)))
    پایله_type = مرکب_type (TYPE_MAIN_VARIANT (type1),
				  TYPE_MAIN_VARIANT (type2));

  إذا (!پایله_type)
    {
      إذا (flag_cond_mismatch)
	پایله_type = void_type_غوټه;
      وإلا
	{
	  error_at (colon_loc, "type mismatch in conditional expression");
	  أرجع error_mark_غوټه;
	}
    }

  /* Merge const and volatile flags of the incoming types.  */
  پایله_type
    = build_type_variant (پایله_type,
			  TYPE_READONLY (type1) || TYPE_READONLY (type2),
			  TYPE_VOLATILE (type1) || TYPE_VOLATILE (type2));

  op1 = ep_convert_and_check (colon_loc, پایله_type, op1,
			      semantic_پایله_type);
  op2 = ep_convert_and_check (colon_loc, پایله_type, op2,
			      semantic_پایله_type);

  إذا (ifexp_bcp && ifexp == truthvalue_true_غوټه)
    {
      op2_int_operands = ریښتیا;
      op1 = c_fully_fold (op1, require_constant_ارزښت, عدم);
    }
  إذا (ifexp_bcp && ifexp == truthvalue_false_غوټه)
    {
      op1_int_operands = ریښتیا;
      op2 = c_fully_fold (op2, require_constant_ارزښت, عدم);
    }
  int_const = int_operands = (ifexp_int_operands
			      && op1_int_operands
			      && op2_int_operands);
  إذا (int_operands)
    {
      int_const = ((ifexp == truthvalue_true_غوټه
		    && ونه_کوډ (orig_op1) == INTEGER_CST
		    && !ونه_ډکېدنه (orig_op1))
		   || (ifexp == truthvalue_false_غوټه
		       && ونه_کوډ (orig_op2) == INTEGER_CST
		       && !ونه_ډکېدنه (orig_op2)));
    }

  /* Need to convert condition operand into a vector mask.  */
  إذا (ویکټور_TYPE_P (ونه_TYPE (ifexp)))
    {
      ونه vectype = ونه_TYPE (ifexp);
      ونه elem_type = ونه_TYPE (vectype);
      ونه zero = build_int_cst (elem_type, 0);
      ونه zero_vec = build_ویکټور_from_val (vectype, zero);
      ونه cmp_type = truth_type_for (vectype);
      ifexp = build2 (NE_بیان, cmp_type, ifexp, zero_vec);
    }

  إذا (int_const || (ifexp_bcp && ونه_کوډ (ifexp) == INTEGER_CST))
    ret = fold_build3_loc (colon_loc, COND_بیان, پایله_type, ifexp, op1, op2);
  وإلا
    {
      إذا (int_operands)
	{
	  /* Use c_fully_fold here, since C_MAYBE_CONST_EXPR might be
	     nested inside of the expression.  */
	  op1 = c_fully_fold (op1, خطأ, عدم);
	  op2 = c_fully_fold (op2, خطأ, عدم);
	}
      ret = build3 (COND_بیان, پایله_type, ifexp, op1, op2);
      إذا (int_operands)
	ret = note_integer_operands (ret);
    }
  إذا (semantic_پایله_type)
    ret = build1 (EXCESS_PRECISION_بیان, semantic_پایله_type, ret);

  protected_سېټ_بیان_location (ret, colon_loc);

  /* If the OP1 and OP2 are the same and don't have side-effects,
     warn here, because the COND_EXPR will be turned into OP1.  */
  إذا (warn_duplicated_branches
      && ونه_کوډ (ret) == COND_بیان
      && (op1 == op2 || عملوند_equal_p (op1, op2, OEP_پته_د_SAME_ډګر)))
    warning_at (بیان_LOCATION (ret), OPT_Wduplicated_branches,
		"this condition has identical branches");

  أرجع ret;
}

/* EXPR is an expression, location LOC, whose result is discarded.
   Warn if it is a call to a nodiscard function (or a COMPOUND_EXPR
   whose right-hand operand is such a call, possibly recursively).  */

ساكن فراغ
maybe_warn_nodiscard (location_t loc, ونه بیان)
{
  إذا (VOID_TYPE_P (ونه_TYPE (بیان)))
    أرجع;
  طالما (ونه_کوډ (بیان) == COMPOUND_بیان)
    {
      بیان = ونه_عملوند (بیان, 1);
      إذا (بیان_HAS_LOCATION (بیان))
	loc = بیان_LOCATION (بیان);
    }
  إذا (ونه_کوډ (بیان) != CALL_بیان)
    أرجع;
  ونه fn = CALL_بیان_FN (بیان);
  إذا (!fn)
    أرجع;
  ونه attr;
  إذا (ونه_کوډ (fn) == ADDR_بیان
      && ونه_کوډ (ونه_عملوند (fn, 0)) == FUNCTION_DECL
      && (attr = lookup_attribute ("nodiscard",
				   DECL_ځانګړتیاوې (ونه_عملوند (fn, 0)))))
    {
      fn = ونه_عملوند (fn, 0);
      ونه دلیلونه = ونه_ارزښت (attr);
      إذا (دلیلونه)
	دلیلونه = ونه_ارزښت (دلیلونه);
      auto_diagnostic_ډله d;
      auto_urlify_ځانګړتیاوې sentinel;
      صحيح warned;
      إذا (دلیلونه)
	warned = warning_at (loc, OPT_Wunused_پایله,
			     "ignoring return value of %qD, declared with "
			     "attribute %<nodiscard%>: %E", fn, دلیلونه);
      وإلا
	warned = warning_at (loc, OPT_Wunused_پایله,
			     "ignoring return value of %qD, declared with "
			     "attribute %<nodiscard%>", fn);
      إذا (warned)
	inform (DECL_سرچینه_LOCATION (fn), "declared here");
    }
  وإلا
    {
      ونه rettype = ونه_TYPE (ونه_TYPE (ونه_TYPE (fn)));
      attr = lookup_attribute ("nodiscard", TYPE_ځانګړتیاوې (rettype));
      إذا (!attr)
	أرجع;
      ونه دلیلونه = ونه_ارزښت (attr);
      إذا (دلیلونه)
	دلیلونه = ونه_ارزښت (دلیلونه);
      auto_diagnostic_ډله d;
      auto_urlify_ځانګړتیاوې sentinel;
      صحيح warned;
      إذا (دلیلونه)
	warned = warning_at (loc, OPT_Wunused_پایله,
			     "ignoring return value of type %qT, declared "
			     "with attribute %<nodiscard%>: %E",
			     rettype, دلیلونه);
      وإلا
	warned = warning_at (loc, OPT_Wunused_پایله,
			     "ignoring return value of type %qT, declared "
			     "with attribute %<nodiscard%>", rettype);
      إذا (warned)
	{
	  إذا (ونه_کوډ (fn) == ADDR_بیان)
	    {
	      fn = ونه_عملوند (fn, 0);
	      إذا (ونه_کوډ (fn) == FUNCTION_DECL)
		inform (DECL_سرچینه_LOCATION (fn),
			"in call to %qD, declared here", fn);
	    }
	}
    }
}

/* Return a compound expression that performs two expressions and
   returns the value of the second of them.

   LOC is the location of the COMPOUND_EXPR.  */

ونه
build_compound_بیان (location_t loc, ونه expr1, ونه expr2)
{
  منطقي expr1_int_operands, expr2_int_operands;
  ونه eptype = NULL_ونه;
  ونه ret;

  expr1_int_operands = بیان_INT_CONST_OPERANDS (expr1);
  إذا (expr1_int_operands)
    expr1 = remove_c_maybe_const_بیان (expr1);
  expr2_int_operands = بیان_INT_CONST_OPERANDS (expr2);
  إذا (expr2_int_operands)
    expr2 = remove_c_maybe_const_بیان (expr2);

  إذا (ونه_کوډ (expr1) == EXCESS_PRECISION_بیان)
    expr1 = ونه_عملوند (expr1, 0);
  إذا (ونه_کوډ (expr2) == EXCESS_PRECISION_بیان)
    {
      eptype = ونه_TYPE (expr2);
      expr2 = ونه_عملوند (expr2, 0);
    }

  إذا (!ونه_SIDE_EFFECTS (expr1))
    {
      /* The left-hand operand of a comma expression is like an expression
	 statement: with -Wunused, we should warn if it doesn't have
	 any side-effects, unless it was explicitly cast to (void).  */
      إذا (warn_ناکارول_شوی_ارزښت)
	{
	  إذا (VOID_TYPE_P (ونه_TYPE (expr1))
	      && CONVERT_بیان_P (expr1))
	    ; /* (void) a, b */
	  وإلا إذا (VOID_TYPE_P (ونه_TYPE (expr1))
		   && ونه_کوډ (expr1) == COMPOUND_بیان
		   && CONVERT_بیان_P (ونه_عملوند (expr1, 1)))
	    ; /* (void) a, (void) b, c */
	  وإلا
	    warning_at (loc, OPT_Wunused_ارزښت,
			"left-hand operand of comma expression has no effect");
	}
    }
  وإلا إذا (ونه_کوډ (expr1) == COMPOUND_بیان
	   && warn_ناکارول_شوی_ارزښت)
    {
      ونه r = expr1;
      location_t cloc = loc;
      طالما (ونه_کوډ (r) == COMPOUND_بیان)
        {
	  إذا (بیان_HAS_LOCATION (r))
	    cloc = بیان_LOCATION (r);
	  r = ونه_عملوند (r, 1);
	}
      إذا (!ونه_SIDE_EFFECTS (r)
	  && !VOID_TYPE_P (ونه_TYPE (r))
	  && !CONVERT_بیان_P (r))
	warning_at (cloc, OPT_Wunused_ارزښت,
	            "right-hand operand of comma expression has no effect");
    }

  /* With -Wunused, we should also warn if the left-hand operand does have
     side-effects, but computes a value which is not used.  For example, in
     `foo() + bar(), baz()' the result of the `+' operator is not used,
     so we should issue a warning.  */
  وإلا إذا (warn_ناکارول_شوی_ارزښت)
    warn_if_ناکارول_شوی_ارزښت (expr1, loc);

  maybe_warn_nodiscard (loc, expr1);

  إذا (expr2 == error_mark_غوټه)
    أرجع error_mark_غوټه;

  ret = build2 (COMPOUND_بیان, ونه_TYPE (expr2), expr1, expr2);

  إذا (flag_isoc99
      && expr1_int_operands
      && expr2_int_operands)
    ret = note_integer_operands (ret);

  إذا (eptype)
    ret = build1 (EXCESS_PRECISION_بیان, eptype, ret);

  protected_سېټ_بیان_location (ret, loc);
  أرجع ret;
}

/* Issue -Wcast-qual warnings when appropriate.  TYPE is the type to
   which we are casting.  OTYPE is the type of the expression being
   cast.  Both TYPE and OTYPE are pointer types.  LOC is the location
   of the cast.  -Wcast-qual appeared on the command line.  Named
   address space qualifiers are not handled here, because they result
   in different warnings.  */

ساكن فراغ
handle_warn_cast_qual (location_t loc, ونه type, ونه otype)
{
  ونه دننه_type = type;
  ونه دننه_otype = otype;
  صحيح added = 0;
  صحيح discarded = 0;
  منطقي is_const;

  /* Check that the qualifiers on IN_TYPE are a superset of the
     qualifiers of IN_OTYPE.  The outermost level of POINTER_TYPE
     nodes is uninteresting and we stop as soon as we hit a
     non-POINTER_TYPE node on either type.  */
  افعل
    {
      دننه_otype = ونه_TYPE (دننه_otype);
      دننه_type = ونه_TYPE (دننه_type);

      /* GNU C allows cv-qualified function types.  'const' means the
	 function is very pure, 'volatile' means it can't return.  We
	 need to warn when such qualifiers are added, not when they're
	 taken away.  */
      إذا (ونه_کوډ (دننه_otype) == FUNCTION_TYPE
	  && ونه_کوډ (دننه_type) == FUNCTION_TYPE)
	added |= (TYPE_QUALS_NO_ADDR_SPACE (دننه_type)
		  & ~TYPE_QUALS_NO_ADDR_SPACE (دننه_otype));
      وإلا
	discarded |= (TYPE_QUALS_NO_ADDR_SPACE (دننه_otype)
		      & ~TYPE_QUALS_NO_ADDR_SPACE (دننه_type));
    }
  طالما (ونه_کوډ (دننه_type) == اشاره_ګر_TYPE
	 && ونه_کوډ (دننه_otype) == اشاره_ګر_TYPE);

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

  إذا (TYPE_MAIN_VARIANT (دننه_type) != TYPE_MAIN_VARIANT (دننه_otype))
    أرجع;
  إذا (ونه_کوډ (ونه_TYPE (type)) != اشاره_ګر_TYPE)
    أرجع;

  دننه_type = type;
  دننه_otype = otype;
  is_const = TYPE_READONLY (ونه_TYPE (دننه_type));
  افعل
    {
      دننه_type = ونه_TYPE (دننه_type);
      دننه_otype = ونه_TYPE (دننه_otype);
      إذا ((TYPE_QUALS (دننه_type) &~ TYPE_QUALS (دننه_otype)) != 0
	  && !is_const)
	{
	  warning_at (loc, OPT_Wcast_qual,
		      "to be safe all intermediate pointers in cast from "
                      "%qT to %qT must be %<const%> qualified",
		      otype, type);
	  اكسر;
	}
      إذا (is_const)
	is_const = TYPE_READONLY (دننه_type);
    }
  طالما (ونه_کوډ (دننه_type) == اشاره_ګر_TYPE);
}

/* Heuristic check if two parameter types can be considered ABI-equivalent.  */

ساكن منطقي
c_خوندي_arg_type_equiv_p (ونه t1, ونه t2)
{
  إذا (error_عملوند_p (t1) || error_عملوند_p (t2))
    أرجع ریښتیا;

  t1 = TYPE_MAIN_VARIANT (t1);
  t2 = TYPE_MAIN_VARIANT (t2);

  إذا (ونه_کوډ (t1) == اشاره_ګر_TYPE
      && ونه_کوډ (t2) == اشاره_ګر_TYPE)
    أرجع ریښتیا;

  /* Only the precision of the parameter matters.  This check should
     make sure that the callee does not see undefined values in argument
     registers.  */
  إذا (INTEGRAL_TYPE_P (t1)
      && INTEGRAL_TYPE_P (t2)
      && TYPE_PRECISION (t1) == TYPE_PRECISION (t2))
    أرجع ریښتیا;

  أرجع comptypes (t1, t2);
}

/* Check if a type cast between two function types can be considered safe.  */

ساكن منطقي
c_خوندي_function_type_cast_p (ونه t1, ونه t2)
{
  إذا (ونه_TYPE (t1) == void_type_غوټه &&
      TYPE_ARG_TYPES (t1) == void_list_غوټه)
    أرجع ریښتیا;

  إذا (ونه_TYPE (t2) == void_type_غوټه &&
      TYPE_ARG_TYPES (t2) == void_list_غوټه)
    أرجع ریښتیا;

  إذا (!c_خوندي_arg_type_equiv_p (ونه_TYPE (t1), ونه_TYPE (t2)))
    أرجع خطأ;

  لكل (t1 = TYPE_ARG_TYPES (t1), t2 = TYPE_ARG_TYPES (t2);
       t1 && t2;
       t1 = ونه_CHAIN (t1), t2 = ونه_CHAIN (t2))
    إذا (!c_خوندي_arg_type_equiv_p (ونه_ارزښت (t1), ونه_ارزښت (t2)))
      أرجع خطأ;

  أرجع ریښتیا;
}

/* Build an expression representing a cast to type TYPE of expression EXPR.
   LOC is the location of the cast-- typically the open paren of the cast.  */

ونه
build_c_cast (location_t loc, ونه type, ونه بیان)
{
  ونه ارزښت;

  منطقي int_operands = بیان_INT_CONST_OPERANDS (بیان);

  إذا (ونه_کوډ (بیان) == EXCESS_PRECISION_بیان)
    بیان = ونه_عملوند (بیان, 0);

  ارزښت = بیان;
  إذا (int_operands)
    ارزښت = remove_c_maybe_const_بیان (ارزښت);

  إذا (type == error_mark_غوټه || بیان == error_mark_غوټه)
    أرجع error_mark_غوټه;

  /* The ObjC front-end uses TYPE_MAIN_VARIANT to tie together types differing
     only in <protocol> qualifications.  But when constructing cast expressions,
     the protocols do matter and must be kept around.  */
  إذا (objc_is_object_ptr (type) && objc_is_object_ptr (ونه_TYPE (بیان)))
    أرجع build1 (NOP_بیان, type, بیان);

  type = TYPE_MAIN_VARIANT (type);

  إذا (ونه_کوډ (type) == ARRAY_TYPE)
    {
      error_at (loc, "cast specifies array type");
      أرجع error_mark_غوټه;
    }

  إذا (ونه_کوډ (type) == FUNCTION_TYPE)
    {
      error_at (loc, "cast specifies function type");
      أرجع error_mark_غوټه;
    }

  إذا (!VOID_TYPE_P (type))
    {
      ارزښت = require_complete_type (loc, ارزښت);
      إذا (ارزښت == error_mark_غوټه)
	أرجع error_mark_غوټه;
    }

  إذا (type == TYPE_MAIN_VARIANT (ونه_TYPE (ارزښت)))
    {
      إذا (ریکارډ_OR_UNION_TYPE_P (type)
	  && pedwarn (loc, OPT_Wpedantic,
		      "ISO C forbids casting nonscalar to the same type"))
	      ;
      وإلا إذا (warn_useless_cast && c_inhibit_evaluation_warnings == 0)
	warning_at (loc, OPT_Wuseless_cast,
		    "useless cast to type %qT", type);

      /* Convert to remove any qualifiers from VALUE's type.  */
      ارزښت = convert (type, ارزښت);
    }
  وإلا إذا (ونه_کوډ (type) == UNION_TYPE)
    {
      ونه ډګر_2;

      لكل (ډګر_2 = TYPE_FIELDS (type); ډګر_2; ډګر_2 = DECL_CHAIN (ډګر_2))
	إذا (ونه_TYPE (ډګر_2) != error_mark_غوټه
	    && comptypes (TYPE_MAIN_VARIANT (ونه_TYPE (ډګر_2)),
			  TYPE_MAIN_VARIANT (ونه_TYPE (ارزښت))))
	  اكسر;

      إذا (ډګر_2)
	{
	  ونه t;
	  منطقي maybe_const = ریښتیا;

	  pedwarn (loc, OPT_Wpedantic, "ISO C forbids casts to union type");
	  t = c_fully_fold (ارزښت, خطأ, &maybe_const);
	  t = build_constructor_single (type, ډګر_2, t);
	  إذا (!maybe_const)
	    t = c_wrap_maybe_const (t, ریښتیا);
	  t = digest_init (loc, ډګر_2, type, t,
			   NULL_ونه, خطأ, خطأ, خطأ, ریښتیا, خطأ, خطأ);
	  ونه_CONSTANT (t) = ونه_CONSTANT (ارزښت);
	  أرجع t;
	}
      error_at (loc, "cast to union type from type not present in union");
      أرجع error_mark_غوټه;
    }
  وإلا
    {
      ونه otype, ovalue;

      إذا (type == void_type_غوټه)
	{
	  ونه t = build1 (CONVERT_بیان, type, ارزښت);
	  سېټ_بیان_LOCATION (t, loc);
	  أرجع t;
	}

      otype = ونه_TYPE (ارزښت);

      /* Optionally warn about potentially worrisome casts.  */
      إذا (warn_cast_qual
	  && ونه_کوډ (type) == اشاره_ګر_TYPE
	  && ونه_کوډ (otype) == اشاره_ګر_TYPE)
	handle_warn_cast_qual (loc, type, otype);

      /* Warn about conversions between pointers to disjoint
	 address spaces.  */
      إذا (ونه_کوډ (type) == اشاره_ګر_TYPE
	  && ونه_کوډ (otype) == اشاره_ګر_TYPE
	  && !null_اشاره_ګر_constant_p (ارزښت))
	{
	  addr_space_t as_منزل = TYPE_ADDR_SPACE (ونه_TYPE (type));
	  addr_space_t as_from = TYPE_ADDR_SPACE (ونه_TYPE (otype));
	  addr_space_t as_common;

	  إذا (!addr_space_superset (as_منزل, as_from, &as_common))
	    {
	      إذا (ADDR_SPACE_GENERIC_P (as_from))
		warning_at (loc, 0, "cast to %qs address space pointer "
			    "from disjoint generic address space pointer",
			    c_addr_space_name (as_منزل));

	      وإلا إذا (ADDR_SPACE_GENERIC_P (as_منزل))
		warning_at (loc, 0, "cast to generic address space pointer "
			    "from disjoint %qs address space pointer",
			    c_addr_space_name (as_from));

	      وإلا
		warning_at (loc, 0, "cast to %qs address space pointer "
			    "from disjoint %qs address space pointer",
			    c_addr_space_name (as_منزل),
			    c_addr_space_name (as_from));
	    }

	  /* Warn of new allocations that are not big enough for the target
	     type.  */
	  إذا (warn_alloc_اندازه && ونه_کوډ (ارزښت) == CALL_بیان)
	    إذا (ونه fndecl = get_callee_fndecl (ارزښت))
	      إذا (DECL_IS_MALLOC (fndecl))
		{
		  ونه attrs = TYPE_ځانګړتیاوې (ونه_TYPE (fndecl));
		  ونه alloc_اندازه = lookup_attribute ("alloc_size", attrs);
		  إذا (alloc_اندازه)
		    warn_for_alloc_اندازه (loc, ونه_TYPE (type), ارزښت,
					 alloc_اندازه);
		}
	}

      /* Warn about possible alignment problems.  */
      إذا ((STRICT_ALIGNMENT || warn_cast_align == 2)
	  && ونه_کوډ (type) == اشاره_ګر_TYPE
	  && ونه_کوډ (otype) == اشاره_ګر_TYPE
	  && ونه_کوډ (ونه_TYPE (otype)) != VOID_TYPE
	  && ونه_کوډ (ونه_TYPE (otype)) != FUNCTION_TYPE
	  /* Don't warn about opaque types, where the actual alignment
	     restriction is unknown.  */
	  && !(ریکارډ_OR_UNION_TYPE_P (ونه_TYPE (otype))
	       && TYPE_ډېرپېښ (ونه_TYPE (otype)) == VOIDmode)
	  && min_align_د_type (ونه_TYPE (type))
	     > min_align_د_type (ونه_TYPE (otype)))
	warning_at (loc, OPT_Wcast_align,
		    "cast increases required alignment of target type");

      إذا ((ونه_کوډ (type) == INTEGER_TYPE
	   || ونه_کوډ (type) == BITINT_TYPE)
	  && ونه_کوډ (otype) == اشاره_ګر_TYPE
	  && TYPE_PRECISION (type) != TYPE_PRECISION (otype))
      /* Unlike conversion of integers to pointers, where the
         warning is disabled for converting constants because
         of cases such as SIG_*, warn about converting constant
         pointers to integers. In some cases it may cause unwanted
         sign extension, and a warning is appropriate.  */
	warning_at (loc, OPT_Wpointer_منزل_int_cast,
		    "cast from pointer to integer of different size");

      إذا ((ونه_کوډ (ارزښت) == CALL_بیان
	   && !is_access_with_اندازه_p (ارزښت))
	  && ونه_کوډ (type) != ونه_کوډ (otype))
	warning_at (loc, OPT_Wbad_function_cast,
		    "cast from function call of type %qT "
		    "to non-matching type %qT", otype, type);

      إذا (ونه_کوډ (type) == اشاره_ګر_TYPE
	  && (ونه_کوډ (otype) == INTEGER_TYPE
	      || ونه_کوډ (otype) == BITINT_TYPE)
	  && TYPE_PRECISION (type) != TYPE_PRECISION (otype)
	  /* Don't warn about converting any constant.  */
	  && !ونه_CONSTANT (ارزښت))
	warning_at (loc,
		    OPT_Wint_منزل_اشاره_ګر_cast, "cast to pointer from integer "
		    "of different size");

      إذا (warn_strict_aliasing <= 2)
        strict_aliasing_warning (بیان_LOCATION (ارزښت), type, بیان);

      /* If pedantic, warn for conversions between function and object
	 pointer types, except for converting a null pointer constant
	 to function pointer type.  */
      إذا (pedantic
	  && ونه_کوډ (type) == اشاره_ګر_TYPE
	  && ونه_کوډ (otype) == اشاره_ګر_TYPE
	  && ونه_کوډ (ونه_TYPE (otype)) == FUNCTION_TYPE
	  && ونه_کوډ (ونه_TYPE (type)) != FUNCTION_TYPE)
	pedwarn (loc, OPT_Wpedantic, "ISO C forbids "
		 "conversion of function pointer to object pointer type");

      إذا (pedantic
	  && ونه_کوډ (type) == اشاره_ګر_TYPE
	  && ونه_کوډ (otype) == اشاره_ګر_TYPE
	  && ونه_کوډ (ونه_TYPE (type)) == FUNCTION_TYPE
	  && ونه_کوډ (ونه_TYPE (otype)) != FUNCTION_TYPE
	  && !null_اشاره_ګر_constant_p (ارزښت))
	pedwarn (loc, OPT_Wpedantic, "ISO C forbids "
		 "conversion of object pointer to function pointer type");

      إذا (ونه_کوډ (type) == اشاره_ګر_TYPE
	  && ونه_کوډ (otype) == اشاره_ګر_TYPE
	  && ونه_کوډ (ونه_TYPE (type)) == FUNCTION_TYPE
	  && ونه_کوډ (ونه_TYPE (otype)) == FUNCTION_TYPE
	  && !c_خوندي_function_type_cast_p (ونه_TYPE (type),
					   ونه_TYPE (otype)))
	warning_at (loc, OPT_Wcast_function_type,
		    "cast between incompatible function types"
		    " from %qT to %qT", otype, type);

      ovalue = ارزښت;
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
	  && ونه_کوډ (ارزښت) != INTEGER_CST
	  && (ونه_کوډ (type) == BOOLEAN_TYPE
	      || (ونه_کوډ (type) == ENUMERAL_TYPE
		  && ENUM_UNDERLYING_TYPE (type) != NULL_ونه
		  && ونه_کوډ (ENUM_UNDERLYING_TYPE (type)) == BOOLEAN_TYPE)))
	ارزښت = note_integer_operands (ارزښت);
      ارزښت = convert (type, ارزښت);

      /* Ignore any integer overflow caused by the cast.  */
      إذا (ونه_کوډ (ارزښت) == INTEGER_CST && !FLOAT_TYPE_P (otype))
	{
	  إذا (ونه_ډکېدنه_P (ovalue))
	    {
	      إذا (!ونه_ډکېدنه (ارزښت))
		{
		  /* Avoid clobbering a shared constant.  */
		  ارزښت = copy_غوټه (ارزښت);
		  ونه_ډکېدنه (ارزښت) = ونه_ډکېدنه (ovalue);
		}
	    }
	  وإلا إذا (ونه_ډکېدنه (ارزښت))
	    /* Reset VALUE's overflow flags, ensuring constant sharing.  */
	    ارزښت = wide_int_منزل_ونه (ونه_TYPE (ارزښت), wi::منزل_wide (ارزښت));
	}
    }

  /* Don't let a cast be an lvalue.  */
  إذا (lvalue_p (ارزښت)
      /* Also, don't let a cast be a bit-field of a bit-precise integer type,
	 otherwise it could be incorrectly subject of integer promotions.  */
      || (ونه_کوډ (ارزښت) == COMPONENT_REF
	  && DECL_C_بټ_ډګر (ونه_عملوند (ارزښت, 1))
	  && BITINT_TYPE_P (DECL_بټ_ډګر_TYPE (ونه_عملوند (ارزښت, 1)))))
    ارزښت = non_lvalue_loc (loc, ارزښت);

  /* Don't allow the results of casting to floating-point or complex
     types be confused with actual constants, or casts involving
     integer and pointer types other than direct integer-to-integer
     and integer-to-pointer be confused with integer constant
     expressions and null pointer constants.  */
  إذا (ونه_کوډ (ارزښت) == REAL_CST
      || ونه_کوډ (ارزښت) == COMPLEX_CST
      || (ونه_کوډ (ارزښت) == INTEGER_CST
	  && !((ونه_کوډ (بیان) == INTEGER_CST
		&& INTEGRAL_TYPE_P (ونه_TYPE (بیان)))
	       || ونه_کوډ (بیان) == REAL_CST
	       || ونه_کوډ (بیان) == COMPLEX_CST)))
      ارزښت = build1 (NOP_بیان, type, ارزښت);

  /* If the expression has integer operands and so can occur in an
     unevaluated part of an integer constant expression, ensure the
     return value reflects this.  */
  إذا (int_operands
      && INTEGRAL_TYPE_P (type)
      && ارزښت != error_mark_غوټه
      && !بیان_INT_CONST_OPERANDS (ارزښت))
    ارزښت = note_integer_operands (ارزښت);

  protected_سېټ_بیان_location (ارزښت, loc);
  أرجع ارزښت;
}

/* Interpret a cast of expression EXPR to type TYPE.  LOC is the
   location of the open paren of the cast, or the position of the cast
   expr.  */
ونه
c_cast_بیان (location_t loc, بنية c_type_name *type_name, ونه بیان)
{
  ونه type;
  ونه type_بیان = NULL_ونه;
  منطقي type_بیان_const = ریښتیا;
  ونه ret;
  صحيح saved_wsp = warn_strict_prototypes;

  /* This avoids warnings about unprototyped casts on
     integers.  E.g. "#define SIG_DFL (void(*)())0".  */
  إذا (ونه_کوډ (بیان) == INTEGER_CST)
    warn_strict_prototypes = 0;
  type = groktypename (type_name, &type_بیان, &type_بیان_const);
  warn_strict_prototypes = saved_wsp;

  إذا (ونه_کوډ (بیان) == ADDR_بیان && !VOID_TYPE_P (type)
      && reject_gcc_builtin (بیان))
    أرجع error_mark_غوټه;

  ret = build_c_cast (loc, type, بیان);
  إذا (ret == error_mark_غوټه)
    أرجع error_mark_غوټه;

  إذا (type_بیان)
    {
      منطقي inner_بیان_const = ریښتیا;
      ret = c_fully_fold (ret, require_constant_ارزښت, &inner_بیان_const);
      ret = build2 (C_MAYBE_CONST_بیان, ونه_TYPE (ret), type_بیان, ret);
      C_MAYBE_CONST_بیان_NON_CONST (ret) = !(type_بیان_const
					     && inner_بیان_const);
      سېټ_بیان_LOCATION (ret, loc);
    }

  إذا (!بیان_HAS_LOCATION (ret))
    protected_سېټ_بیان_location (ret, loc);

  /* C++ does not permits types to be defined in a cast, but it
     allows references to incomplete types.  */
  إذا (warn_cxx_compat && type_name->specs->typespec_ډول == ctsk_tagdef)
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

ونه
build_modify_بیان (location_t location, ونه lhs, ونه lhs_origtype,
		   تعداد ونه_کوډ_2 modifycode,
		   location_t rhs_loc, ونه rhs, ونه rhs_origtype)
{
  ونه پایله;
  ونه newrhs;
  ونه rhseval = NULL_ونه;
  ونه lhstype = ونه_TYPE (lhs);
  ونه olhstype = lhstype;
  منطقي npc;
  منطقي is_atomic_op;

  /* Types that aren't fully specified cannot be used in assignments.  */
  lhs = require_complete_type (location, lhs);
  rhs = require_complete_type (location, rhs);

  /* Avoid duplicate error messages from operands that had errors.  */
  إذا (ونه_کوډ (lhs) == ERROR_MARK || ونه_کوډ (rhs) == ERROR_MARK)
    أرجع error_mark_غوټه;

  /* Ensure an error for assigning a non-lvalue array to an array in
     C90.  */
  إذا (ونه_کوډ (lhstype) == ARRAY_TYPE)
    {
      error_at (location, "assignment to expression with array type");
      أرجع error_mark_غوټه;
    }

  /* For ObjC properties, defer this check.  */
  إذا (!objc_is_property_ref (lhs) && !lvalue_or_else (location, lhs, lv_ټاکل))
    أرجع error_mark_غوټه;

  is_atomic_op = really_atomic_lvalue (lhs);

  newrhs = rhs;

  إذا (ونه_کوډ (lhs) == C_MAYBE_CONST_بیان)
    {
      ونه inner = build_modify_بیان (location, C_MAYBE_CONST_بیان_بیان (lhs),
				      lhs_origtype, modifycode, rhs_loc, rhs,
				      rhs_origtype);
      إذا (inner == error_mark_غوټه)
	أرجع error_mark_غوټه;
      پایله = build2 (C_MAYBE_CONST_بیان, ونه_TYPE (inner),
		       C_MAYBE_CONST_بیان_PRE (lhs), inner);
      gcc_assert (!C_MAYBE_CONST_بیان_INT_OPERANDS (lhs));
      C_MAYBE_CONST_بیان_NON_CONST (پایله) = 1;
      protected_سېټ_بیان_location (پایله, location);
      أرجع پایله;
    }

  /* If a binary op has been requested, combine the old LHS value with the RHS
     producing the value we should actually store into the LHS.  */

  إذا (modifycode != NOP_بیان)
    {
      lhs = c_fully_fold (lhs, خطأ, عدم, ریښتیا);
      lhs = stabilize_reference (lhs);

      /* Construct the RHS for any non-atomic compound assignment. */
      إذا (!is_atomic_op)
        {
	  /* If in LHS op= RHS the RHS has side-effects, ensure they
	     are preevaluated before the rest of the assignment expression's
	     side-effects, because RHS could contain e.g. function calls
	     that modify LHS.  */
	  إذا (ونه_SIDE_EFFECTS (rhs))
	    {
	      إذا (ونه_کوډ (rhs) == EXCESS_PRECISION_بیان)
		newrhs = save_بیان (ونه_عملوند (rhs, 0));
	      وإلا
		newrhs = save_بیان (rhs);
	      rhseval = newrhs;
	      إذا (ونه_کوډ (rhs) == EXCESS_PRECISION_بیان)
		newrhs = build1 (EXCESS_PRECISION_بیان, ونه_TYPE (rhs),
				 newrhs);
	    }
	  منطقي clear_decl_read = خطأ;
	  إذا ((VAR_P (lhs) || ونه_کوډ (lhs) == PARM_DECL)
	      && !DECL_READ_P (lhs)
	      && (VAR_P (lhs) ? warn_ناکارول_شوی_but_سېټ_variable
			      : warn_ناکارول_شوی_but_سېټ_parameter) > 2)
	    {
	      mark_exp_read (newrhs);
	      إذا (!DECL_READ_P (lhs))
		clear_decl_read = ریښتیا;
	    }

	  newrhs = build_دوګونی_op (location, modifycode,
				    convert_lvalue_منزل_rvalue (location, lhs,
							      ریښتیا, ریښتیا),
				    newrhs, ریښتیا);
	  إذا (clear_decl_read)
	    DECL_READ_P (lhs) = 0;

	  /* The original type of the right hand side is no longer
	     meaningful.  */
	  rhs_origtype = NULL_ونه;
	}
    }

  إذا (c_dialect_objc ())
    {
      /* Check if we are modifying an Objective-C property reference;
	 if so, we need to generate setter calls.  */
      إذا (ونه_کوډ (newrhs) == EXCESS_PRECISION_بیان)
	پایله = objc_maybe_build_modify_بیان (lhs, ونه_عملوند (newrhs, 0));
      وإلا
	پایله = objc_maybe_build_modify_بیان (lhs, newrhs);
      إذا (پایله)
	اذهب return_پایله;

      /* Else, do the check that we postponed for Objective-C.  */
      إذا (!lvalue_or_else (location, lhs, lv_ټاکل))
	أرجع error_mark_غوټه;
    }

  /* Give an error for storing in something that is 'const'.  */

  إذا (TYPE_READONLY (lhstype)
      || (ریکارډ_OR_UNION_TYPE_P (lhstype)
	  && C_TYPE_FIELDS_READONLY (lhstype)))
    {
      readonly_error (location, lhs, lv_ټاکل);
      أرجع error_mark_غوټه;
    }
  وإلا إذا (ونه_READONLY (lhs))
    readonly_warning (lhs, lv_ټاکل);

  /* If storing into a structure or union member,
     it has probably been given type `int'.
     Compute the type that would go with
     the actual amount of storage the member occupies.  */

  إذا (ونه_کوډ (lhs) == COMPONENT_REF
      && (ونه_کوډ (lhstype) == INTEGER_TYPE
	  || ونه_کوډ (lhstype) == BOOLEAN_TYPE
	  || SCALAR_FLOAT_TYPE_P (lhstype)
	  || ونه_کوډ (lhstype) == ENUMERAL_TYPE))
    lhstype = ونه_TYPE (get_unwidened (lhs, 0));

  /* If storing in a field that is in actuality a short or narrower than one,
     we must store in the field in its actual type.  */

  إذا (lhstype != ونه_TYPE (lhs))
    {
      lhs = copy_غوټه (lhs);
      ونه_TYPE (lhs) = lhstype;
    }

  /* Issue -Wc++-compat warnings about an assignment to an enum type
     when LHS does not have its original type.  This happens for,
     e.g., an enum bitfield in a struct.  */
  إذا (warn_cxx_compat
      && lhs_origtype != NULL_ونه
      && lhs_origtype != lhstype
      && ونه_کوډ (lhs_origtype) == ENUMERAL_TYPE)
    {
      ونه checktype = (rhs_origtype != NULL_ونه
			? rhs_origtype
			: ونه_TYPE (rhs));
      إذا (checktype != error_mark_غوټه
	  && (TYPE_MAIN_VARIANT (checktype) != TYPE_MAIN_VARIANT (lhs_origtype)
	      || (is_atomic_op && modifycode != NOP_بیان)))
	warning_at (location, OPT_Wc___compat,
		    "enum conversion in assignment is invalid in C++");
    }

  /* Remove qualifiers.  */
  lhstype = c_build_qualified_type (lhstype, TYPE_UNQUALIFIED);
  olhstype = c_build_qualified_type (olhstype, TYPE_UNQUALIFIED);

  /* Convert new value to destination type.  Fold it first, then
     restore any excess precision information, for the sake of
     conversion warnings.  */

  إذا (!(is_atomic_op && modifycode != NOP_بیان))
    {
      ونه rhs_semantic_type = NULL_ونه;
      إذا (!c_دننه_omp_for)
	{
	  إذا (ونه_کوډ (newrhs) == EXCESS_PRECISION_بیان)
	    {
	      rhs_semantic_type = ونه_TYPE (newrhs);
	      newrhs = ونه_عملوند (newrhs, 0);
	    }
	  npc = null_اشاره_ګر_constant_p (newrhs);
	  newrhs = c_fully_fold (newrhs, خطأ, عدم);
	  إذا (rhs_semantic_type)
	    newrhs = build1 (EXCESS_PRECISION_بیان, rhs_semantic_type, newrhs);
	}
      وإلا
	npc = null_اشاره_ګر_constant_p (newrhs);
      newrhs = convert_for_assignment (location, rhs_loc, lhstype, newrhs,
				       rhs_origtype, ic_ټاکل, npc,
				       NULL_ونه, NULL_ونه, 0);
      إذا (ونه_کوډ (newrhs) == ERROR_MARK)
	أرجع error_mark_غوټه;
    }

  /* Emit ObjC write barrier, if necessary.  */
  إذا (c_dialect_objc () && flag_objc_gc)
    {
      پایله = objc_generate_write_barrier (lhs, modifycode, newrhs);
      إذا (پایله)
	{
	  protected_سېټ_بیان_location (پایله, location);
	  اذهب return_پایله;
	}
    }

  /* Scan operands.  */

  إذا (is_atomic_op)
    پایله = build_atomic_ټاکل (location, lhs, modifycode, newrhs, خطأ);
  وإلا
    {
      پایله = build2 (MODIFY_بیان, lhstype, lhs, newrhs);
      ونه_SIDE_EFFECTS (پایله) = 1;
      protected_سېټ_بیان_location (پایله, location);
    }

  /* If we got the LHS in a different type for storing in,
     convert the result back to the nominal type of LHS
     so that the value we return always has the same type
     as the LHS argument.  */

  إذا (olhstype == ونه_TYPE (پایله))
    اذهب return_پایله;

  پایله = convert_for_assignment (location, rhs_loc, olhstype, پایله,
				   rhs_origtype, ic_ټاکل, خطأ, NULL_ونه,
				   NULL_ونه, 0);
  protected_سېټ_بیان_location (پایله, location);

return_پایله:
  إذا (rhseval)
    پایله = build2 (COMPOUND_بیان, ونه_TYPE (پایله), rhseval, پایله);
  أرجع پایله;
}

/* Return whether STRUCT_TYPE has an anonymous field with type TYPE.
   This is used to implement -fplan9-extensions.  */

ساكن منطقي
پیدا_کړه_anonymous_ډګر_with_type (ونه struct_type, ونه type)
{
  ونه ډګر_2;
  منطقي وموندل;

  gcc_assert (ریکارډ_OR_UNION_TYPE_P (struct_type));
  وموندل = خطأ;
  لكل (ډګر_2 = TYPE_FIELDS (struct_type);
       ډګر_2 != NULL_ونه;
       ډګر_2 = ونه_CHAIN (ډګر_2))
    {
      ونه fieldtype = remove_qualifiers (ونه_TYPE (ډګر_2));
      إذا (DECL_NAME (ډګر_2) == عدم
	  && comptypes (type, fieldtype))
	{
	  إذا (وموندل)
	    أرجع خطأ;
	  وموندل = ریښتیا;
	}
      وإلا إذا (DECL_NAME (ډګر_2) == عدم
	       && ریکارډ_OR_UNION_TYPE_P (ونه_TYPE (ډګر_2))
	       && پیدا_کړه_anonymous_ډګر_with_type (ونه_TYPE (ډګر_2), type))
	{
	  إذا (وموندل)
	    أرجع خطأ;
	  وموندل = ریښتیا;
	}
    }
  أرجع وموندل;
}

/* RHS is an expression whose type is pointer to struct.  If there is
   an anonymous field in RHS with type TYPE, then return a pointer to
   that field in RHS.  This is used with -fplan9-extensions.  This
   returns NULL if no conversion could be found.  */

ساكن ونه
convert_منزل_anonymous_ډګر (location_t location, ونه type, ونه rhs)
{
  ونه rhs_struct_type, lhs_main_type;
  ونه ډګر_2, وموندل_ډګر;
  منطقي وموندل_sub_ډګر;
  ونه ret;

  gcc_assert (اشاره_ګر_TYPE_P (ونه_TYPE (rhs)));
  rhs_struct_type = ونه_TYPE (ونه_TYPE (rhs));
  gcc_assert (ریکارډ_OR_UNION_TYPE_P (rhs_struct_type));

  gcc_assert (اشاره_ګر_TYPE_P (type));
  lhs_main_type = remove_qualifiers (ونه_TYPE (type));

  وموندل_ډګر = NULL_ونه;
  وموندل_sub_ډګر = خطأ;
  لكل (ډګر_2 = TYPE_FIELDS (rhs_struct_type);
       ډګر_2 != NULL_ونه;
       ډګر_2 = ونه_CHAIN (ډګر_2))
    {
      إذا (DECL_NAME (ډګر_2) != NULL_ونه
	  || !ریکارډ_OR_UNION_TYPE_P (ونه_TYPE (ډګر_2)))
	استمر;
      ونه fieldtype = remove_qualifiers (ونه_TYPE (ډګر_2));
      إذا (comptypes (lhs_main_type, fieldtype))
	{
	  إذا (وموندل_ډګر != NULL_ونه)
	    أرجع NULL_ونه;
	  وموندل_ډګر = ډګر_2;
	}
      وإلا إذا (پیدا_کړه_anonymous_ډګر_with_type (ونه_TYPE (ډګر_2),
					       lhs_main_type))
	{
	  إذا (وموندل_ډګر != NULL_ونه)
	    أرجع NULL_ونه;
	  وموندل_ډګر = ډګر_2;
	  وموندل_sub_ډګر = ریښتیا;
	}
    }

  إذا (وموندل_ډګر == NULL_ونه)
    أرجع NULL_ونه;

  ret = fold_build3_loc (location, COMPONENT_REF, ونه_TYPE (وموندل_ډګر),
			 build_fold_غیرمستقیم_ref (rhs), وموندل_ډګر,
			 NULL_ونه);
  ret = build_fold_addr_بیان_loc (location, ret);

  إذا (وموندل_sub_ډګر)
    {
      ret = convert_منزل_anonymous_ډګر (location, type, ret);
      gcc_assert (ret != NULL_ونه);
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

  auto_diagnostic_ډله d;

  /* The gmsgid may be a format string with %< and %>. */
  va_list ap;
  va_پیل (ap, gmsgid);
  منطقي warned = emit_diagnostic_valist (diagnostics::ډول::error,
					loc, -1, gmsgid, &ap);
  va_پای_ټکی (ap);

  ofwhat = print_spelling ((حرف *) alloca (spelling_اوږدتیا () + 1));
  إذا (*ofwhat && warned)
    inform (loc, "(near initialization for %qs)", ofwhat);
}

/* Used to implement pedwarn_init and permerror_init.  */

ساكن منطقي ATTRIBUTE_GCC_DIAG (3,0)
pedwarn_permerror_init (location_t loc, صحيح opt, ثابت حرف *gmsgid,
			va_list *ap, تعداد diagnostics::ډول ډول)
{
  /* Use the location where a macro was expanded rather than where
     it was defined to make sure macros defined in system headers
     but used incorrectly elsewhere are diagnosed.  */
  location_t exploc = expansion_ټکی_location_if_دننه_system_سرلیک (loc);
  auto_diagnostic_ډله d;
  منطقي warned = emit_diagnostic_valist (ډول, exploc, opt, gmsgid, ap);
  إذا (warned)
    {
      حرف *ofwhat = print_spelling ((حرف *) alloca (spelling_اوږدتیا () + 1));
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
  va_پیل (ap, gmsgid);
  منطقي warned = pedwarn_permerror_init (loc, opt, gmsgid, &ap,
					diagnostics::ډول::pedwarn);
  va_پای_ټکی (ap);
  أرجع warned;
}

/* Like pedwarn_init, but issue a permerror.  */

ساكن منطقي ATTRIBUTE_GCC_DIAG (3,0)
permerror_init (location_t loc, صحيح opt, ثابت حرف *gmsgid, ...)
{
  va_list ap;
  va_پیل (ap, gmsgid);
  منطقي warned = pedwarn_permerror_init (loc, opt, gmsgid, &ap,
					diagnostics::ډول::permerror);
  va_پای_ټکی (ap);
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

  auto_diagnostic_ډله d;

  /* Use the location where a macro was expanded rather than where
     it was defined to make sure macros defined in system headers
     but used incorrectly elsewhere are diagnosed.  */
  location_t exploc = expansion_ټکی_location_if_دننه_system_سرلیک (loc);

  /* The gmsgid may be a format string with %< and %>. */
  warned = warning_at (exploc, opt, gmsgid);
  إذا (warned)
    {
      ofwhat = print_spelling ((حرف *) alloca (spelling_اوږدتیا () + 1));
      إذا (*ofwhat)
	inform (exploc, "(near initialization for %qs)", ofwhat);
    }
}

/* If TYPE is an array type and EXPR is a parenthesized string
   constant, warn if pedantic that EXPR is being used to initialize an
   object of type TYPE.  */

فراغ
maybe_warn_string_init (location_t loc, ونه type, بنية c_بیان بیان)
{
  إذا (pedantic
      && ونه_کوډ (type) == ARRAY_TYPE
      && ونه_کوډ (بیان.ارزښت) == STRING_CST
      && بیان.original_کوډ != STRING_CST)
    pedwarn_init (loc, OPT_Wpedantic,
		  "array initialized from parenthesized string constant");
}

/* Attempt to locate the parameter with the given index within FNDECL,
   returning DECL_SOURCE_LOCATION (FNDECL) if it can't be found.  */

ساكن location_t
get_fndecl_دلیل_location (ونه fndecl, صحيح argnum)
{
  صحيح i;
  ونه param;

  /* Locate param by index within DECL_ARGUMENTS (fndecl).  */
  لكل (i = 0, param = DECL_ARGUMENTS (fndecl);
       i < argnum && param;
       i++, param = ونه_CHAIN (param))
    ;

  /* If something went wrong (e.g. if we have a builtin and thus no arguments),
     return DECL_SOURCE_LOCATION (FNDECL).  */
  إذا (param == عدم)
    أرجع DECL_سرچینه_LOCATION (fndecl);

  أرجع DECL_سرچینه_LOCATION (param);
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
inform_for_arg (ونه fundecl, location_t ploc, صحيح parmnum,
		ونه expected_type, ونه actual_type)
{
  location_t loc;
  إذا (fundecl && !DECL_IS_UNDECLARED_BUILTIN (fundecl))
    loc = get_fndecl_دلیل_location (fundecl, parmnum - 1);
  وإلا
    loc = ploc;

  gcc_rich_location richloc (loc, تش_اشاره, highlight_colors::expected);

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
maybe_warn_builtin_no_proto_arg (location_t loc, ونه fundecl, صحيح parmnum,
				 ونه parmtype, ونه argtype)
{
  ونه_کوډ_2 parmcode = ونه_کوډ (parmtype);
  ونه_کوډ_2 argcode = ونه_کوډ (argtype);
  ونه promoted = c_type_promotes_منزل (argtype);

  /* Avoid warning for enum arguments that promote to an integer type
     of the same size/mode.  */
  إذا (parmcode == INTEGER_TYPE
      && argcode == ENUMERAL_TYPE
      && TYPE_ډېرپېښ (parmtype) == TYPE_ډېرپېښ (argtype))
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
    inform (DECL_سرچینه_LOCATION (fundecl),
	    "built-in %qD declared here",
	    fundecl);
}

/* Print a declaration in quotes, with the given highlight_color.
   Analogous to handler for %qD, but with a specific highlight color.  */

صنف pp_element_quoted_decl : عام pp_element
{
عام:
  pp_element_quoted_decl (ونه decl, ثابت حرف *highlight_color)
  : m_decl (decl),
    m_highlight_color (highlight_color)
  {
  }

  فراغ جمع_کړه_منزل_phase_2 (pp_markup::context &ctxt) override
  {
    ctxt.begin_quote ();
    ctxt.begin_highlight_color (m_highlight_color);

    print_decl (ctxt);

    ctxt.پای_ټکی_highlight_color ();
    ctxt.پای_ټکی_quote ();
  }

  فراغ print_decl (pp_markup::context &ctxt)
  {
    pretty_printer *ثابت pp = &ctxt.m_pp;
    pp->سېټ_padding (pp_none);
    إذا (DECL_NAME (m_decl))
      pp_identifier (pp, lang_hooks.decl_printable_name (m_decl, 2));
    وإلا
      pp_string (pp, _("({anonymous})"));
  }

خاص:
  ونه m_decl;
  ثابت حرف *m_highlight_color;
};

/* If TYPE is from a typedef, issue a note showing the location
   to the user.
   Use HIGHLIGHT_COLOR as the highlight color.  */

ساكن فراغ
maybe_inform_typedef_location (ونه type, ثابت حرف *highlight_color)
{
  إذا (!typedef_variant_p (type))
    أرجع;

  ونه typedef_decl = TYPE_NAME (type);
  gcc_assert (ونه_کوډ (typedef_decl) == TYPE_DECL);
  gcc_rich_location richloc (DECL_سرچینه_LOCATION (typedef_decl),
			     تش_اشاره, highlight_color);
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

ساكن ونه
convert_for_assignment (location_t location, location_t بیان_loc, ونه type,
			ونه rhs, ونه origtype, تعداد impl_conv errtype,
			منطقي null_اشاره_ګر_constant, ونه fundecl,
			ونه function, صحيح parmnum, صحيح warnopt /* = 0 */)
{
  تعداد ونه_کوډ_2 codel = ونه_کوډ (type);
  ونه orig_rhs = rhs;
  ونه rhstype;
  تعداد ونه_کوډ_2 coder;
  ونه rname = NULL_ونه;
  منطقي objc_ok = خطأ;

  /* Use the expansion point location to handle cases such as user's
     function returning a wrong-type macro defined in a system header.  */
  location = expansion_ټکی_location_if_دننه_system_سرلیک (location);

  إذا (errtype == ic_argpass)
    {
      ونه selector;
      /* Change pointer to function to the function itself for
	 diagnostics.  */
      إذا (ونه_کوډ (function) == ADDR_بیان
	  && ونه_کوډ (ونه_عملوند (function, 0)) == FUNCTION_DECL)
	function = ونه_عملوند (function, 0);

      /* Handle an ObjC selector specially for diagnostics.  */
      selector = objc_پیغام_selector ();
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
#تعریف_کړه PEDWARN_FOR_ASSIGNMENT(LOCATION, PLOC, OPT, AR, AS, دننه, RE)	 \
  افعل {                                                                   \
    بدل (errtype)                                                     \
      {                                                                  \
      حالة ic_argpass:                                                   \
	{								\
	  auto_diagnostic_ډله d;						\
	  إذا (pedwarn (PLOC, OPT, AR, parmnum, rname))		\
	    inform_for_arg (fundecl, (PLOC), parmnum, type, rhstype); \
	}								\
        اكسر;                                                           \
      حالة ic_ټاکل:                                                    \
        pedwarn (LOCATION, OPT, AS);                                     \
        اكسر;                                                           \
      حالة ic_init:                                                      \
      حالة ic_init_const:                                                \
        pedwarn_init (LOCATION, OPT, دننه);                                \
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
#تعریف_کړه WARNING_FOR_QUALIFIERS(PEDWARN, LOCATION, PLOC, OPT, AR, AS, دننه, RE, QUALS) \
  افعل {                                                                   \
    بدل (errtype)                                                     \
      {                                                                  \
      حالة ic_argpass:                                                   \
	{								 \
	  auto_diagnostic_ډله d;					 \
	  إذا (PEDWARN) {						 \
	    إذا (pedwarn (PLOC, OPT, AR, parmnum, rname, QUALS))          \
	      inform_for_arg (fundecl, (PLOC), parmnum, type, rhstype);  \
	  } وإلا {							 \
	    إذا (warning_at (PLOC, OPT, AR, parmnum, rname, QUALS))	 \
	      inform_for_arg (fundecl, (PLOC), parmnum, type, rhstype);  \
	  }								 \
	}								 \
        اكسر;                                                           \
      حالة ic_ټاکل:                                                    \
	إذا (PEDWARN)							 \
	  pedwarn (LOCATION, OPT, AS, QUALS);                            \
	وإلا								 \
	  warning_at (LOCATION, OPT, AS, QUALS);                         \
        اكسر;                                                           \
      حالة ic_init:                                                      \
      حالة ic_init_const:                                                \
	إذا (PEDWARN)							 \
	  pedwarn (LOCATION, OPT, دننه, QUALS);                            \
	وإلا								 \
	  warning_at (LOCATION, OPT, دننه, QUALS);                         \
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
#تعریف_کړه PEDWARN_FOR_QUALIFIERS(LOCATION, PLOC, OPT, AR, AS, دننه, RE, QUALS) \
   WARNING_FOR_QUALIFIERS (ریښتیا, LOCATION, PLOC, OPT, AR, AS, دننه, RE, QUALS)


  إذا (ونه_کوډ (rhs) == EXCESS_PRECISION_بیان)
    rhs = ونه_عملوند (rhs, 0);

  rhstype = ونه_TYPE (rhs);
  coder = ونه_کوډ (rhstype);

  إذا (coder == ERROR_MARK)
    أرجع error_mark_غوټه;

  إذا (c_dialect_objc ())
    {
      صحيح parmno;

      بدل (errtype)
	{
	حالة ic_return:
	  parmno = 0;
	  اكسر;

	حالة ic_ټاکل:
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
      ونه checktype = origtype != NULL_ونه ? origtype : rhstype;
      إذا (checktype != error_mark_غوټه
	  && ونه_کوډ (type) == ENUMERAL_TYPE
	  && TYPE_MAIN_VARIANT (checktype) != TYPE_MAIN_VARIANT (type))
	بدل (errtype)
	  {
	  حالة ic_argpass:
	    إذا (pedwarn (بیان_loc, OPT_Wc___compat, "enum conversion when "
			 "passing argument %d of %qE is invalid in C++",
			 parmnum, rname))
	      inform ((fundecl && !DECL_IS_UNDECLARED_BUILTIN (fundecl))
		      ? DECL_سرچینه_LOCATION (fundecl) : بیان_loc,
		      "expected %qT but argument is of type %qT",
		      type, rhstype);
	    اكسر;
	  حالة ic_ټاکل:
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
      ونه checktype = origtype != NULL_ونه ? origtype : rhstype;
      إذا (checktype != error_mark_غوټه
	  && ونه_کوډ (checktype) == ENUMERAL_TYPE
	  && ونه_کوډ (type) == ENUMERAL_TYPE
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
      warn_for_پته_د_packed_member (type, orig_rhs);
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
      ثابت حرف پیغام_2[] = "void value not ignored as it ought to be";
      إذا (warnopt)
	warning_at (location, warnopt, پیغام_2);
      وإلا
	error_at (location, پیغام_2);
      أرجع error_mark_غوټه;
    }
  rhs = require_complete_type (location, rhs);
  إذا (rhs == error_mark_غوټه)
    أرجع error_mark_غوټه;

  إذا (coder == اشاره_ګر_TYPE && reject_gcc_builtin (rhs))
    أرجع error_mark_غوټه;

  /* A non-reference type can convert to a reference.  This handles
     va_start, va_copy and possibly port built-ins.  */
  إذا (codel == REFERENCE_TYPE && coder != REFERENCE_TYPE)
    {
      إذا (!lvalue_p (rhs))
	{
	  ثابت حرف پیغام_2[] = "cannot pass rvalue to reference parameter";
	  إذا (warnopt)
	    warning_at (location, warnopt, پیغام_2);
	  وإلا
	    error_at (location, پیغام_2);
	  أرجع error_mark_غوټه;
	}
      إذا (!c_mark_addressable (rhs))
	أرجع error_mark_غوټه;
      rhs = build1 (ADDR_بیان, c_build_اشاره_ګر_type (ونه_TYPE (rhs)), rhs);
      سېټ_بیان_LOCATION (rhs, location);

      rhs = convert_for_assignment (location, بیان_loc,
				    c_build_اشاره_ګر_type (ونه_TYPE (type)),
				    rhs, origtype, errtype,
				    null_اشاره_ګر_constant, fundecl, function,
				    parmnum, warnopt);
      إذا (rhs == error_mark_غوټه)
	أرجع error_mark_غوټه;

      rhs = build1 (NOP_بیان, type, rhs);
      سېټ_بیان_LOCATION (rhs, location);
      أرجع rhs;
    }
  /* Some types can interconvert without explicit casts.  */
  وإلا إذا (codel == ویکټور_TYPE && coder == ویکټور_TYPE
	   && ویکټور_types_convertible_p (type, ونه_TYPE (rhs), ریښتیا))
    أرجع convert (type, rhs);
  /* Arithmetic types all interconvert, and enum is treated like int.  */
  وإلا إذا ((codel == INTEGER_TYPE || codel == REAL_TYPE
	    || codel == FIXED_ټکی_TYPE
	    || codel == ENUMERAL_TYPE || codel == COMPLEX_TYPE
	    || codel == BOOLEAN_TYPE || codel == BITINT_TYPE)
	   && (coder == INTEGER_TYPE || coder == REAL_TYPE
	       || coder == FIXED_ټکی_TYPE
	       || coder == ENUMERAL_TYPE || coder == COMPLEX_TYPE
	       || coder == BOOLEAN_TYPE || coder == BITINT_TYPE))
    {
      إذا (warnopt && errtype == ic_argpass)
	maybe_warn_builtin_no_proto_arg (بیان_loc, fundecl, parmnum, type,
					 rhstype);

      منطقي save = دننه_late_دوګونی_op;
      إذا (C_BOOLEAN_TYPE_P (type) || codel == COMPLEX_TYPE
	  || (coder == REAL_TYPE
	      && (codel == INTEGER_TYPE || codel == ENUMERAL_TYPE)
	      && sanitize_flags_p (SANITIZE_FLOAT_CAST)))
	دننه_late_دوګونی_op = ریښتیا;
      ونه ret = convert_and_check (بیان_loc != UNKNOWN_LOCATION
				    ? بیان_loc : location, type, orig_rhs,
				    errtype == ic_init_const);
      دننه_late_دوګونی_op = save;
      أرجع ret;
    }

  /* Aggregates in different TUs might need conversion.  */
  إذا ((codel == ریکارډ_TYPE || codel == UNION_TYPE)
      && codel == coder
      && comptypes (TYPE_MAIN_VARIANT (type), TYPE_MAIN_VARIANT (rhstype)))
    أرجع convert_and_check (بیان_loc != UNKNOWN_LOCATION
			      ? بیان_loc : location, type, rhs);

  /* Conversion to a transparent union or record from its member types.
     This applies only to function arguments.  */
  إذا (((codel == UNION_TYPE || codel == ریکارډ_TYPE)
      && TYPE_TRANSPARENT_AGGR (type))
      && errtype == ic_argpass)
    {
      ونه memb, marginal_memb = NULL_ونه;

      لكل (memb = TYPE_FIELDS (type); memb ; memb = DECL_CHAIN (memb))
	{
	  ونه memb_type = ونه_TYPE (memb);

	  إذا (comptypes (TYPE_MAIN_VARIANT (memb_type),
			 TYPE_MAIN_VARIANT (rhstype)))
	    اكسر;

	  إذا (ونه_کوډ (memb_type) != اشاره_ګر_TYPE)
	    استمر;

	  إذا (coder == اشاره_ګر_TYPE)
	    {
	      ونه ttl = ونه_TYPE (memb_type);
	      ونه ttr = ونه_TYPE (rhstype);

	      /* Any non-function converts to a [const][volatile] void *
		 and vice versa; otherwise, targets must be the same.
		 Meanwhile, the lhs target must have all the qualifiers of
		 the rhs.  */
	      إذا ((VOID_TYPE_P (ttl) && !TYPE_ATOMIC (ttl))
		  || (VOID_TYPE_P (ttr) && !TYPE_ATOMIC (ttr))
		  || comp_موخه_types (location, memb_type, rhstype))
		{
		  صحيح lquals = TYPE_QUALS (ttl) & ~TYPE_QUAL_ATOMIC;
		  صحيح rquals = TYPE_QUALS (ttr) & ~TYPE_QUAL_ATOMIC;
		  /* If this type won't generate any warnings, use it.  */
		  إذا (lquals == rquals
		      || ((ونه_کوډ (ttr) == FUNCTION_TYPE
			   && ونه_کوډ (ttl) == FUNCTION_TYPE)
			  ? ((lquals | rquals) == rquals)
			  : ((lquals | rquals) == lquals)))
		    اكسر;

		  /* Keep looking for a better type, but remember this one.  */
		  إذا (!marginal_memb)
		    marginal_memb = memb;
		}
	    }

	  /* Can convert integer zero to any pointer type.  */
	  إذا (null_اشاره_ګر_constant)
	    {
	      rhs = null_اشاره_ګر_غوټه;
	      اكسر;
	    }
	}

      إذا (memb || marginal_memb)
	{
	  إذا (!memb)
	    {
	      /* We have only a marginally acceptable member type;
		 it needs a warning.  */
	      ونه ttl = ونه_TYPE (ونه_TYPE (marginal_memb));
	      ونه ttr = ونه_TYPE (rhstype);

	      /* Const and volatile mean something different for function
		 types, so the usual warnings are not appropriate.  */
	      إذا (ونه_کوډ (ttr) == FUNCTION_TYPE
		  && ونه_کوډ (ttl) == FUNCTION_TYPE)
		{
		  /* Because const and volatile on functions are
		     restrictions that say the function will not do
		     certain things, it is okay to use a const or volatile
		     function where an ordinary one is wanted, but not
		     vice-versa.  */
		  إذا (TYPE_QUALS_NO_ADDR_SPACE (ttl)
		      & ~TYPE_QUALS_NO_ADDR_SPACE (ttr))
		    PEDWARN_FOR_QUALIFIERS (location, بیان_loc,
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
		PEDWARN_FOR_QUALIFIERS (location, بیان_loc,
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

	  إذا (!fundecl || !DECL_دننه_SYSTEM_سرلیک (fundecl))
	    pedwarn (location, OPT_Wpedantic,
		     "ISO C prohibits argument conversion to union type");

	  rhs = fold_convert_loc (location, ونه_TYPE (memb), rhs);
	  أرجع build_constructor_single (type, memb, rhs);
	}
    }

  /* Conversions among pointers */
  وإلا إذا ((codel == اشاره_ګر_TYPE || codel == REFERENCE_TYPE)
	   && (coder == codel))
    {
      /* If RHS refers to a built-in declared without a prototype
	 BLTIN is the declaration of the built-in with a prototype
	 and RHSTYPE is set to the actual type of the built-in.  */
      ونه bltin;
      rhstype = type_or_builtin_type (rhs, &bltin);

      ونه ttl = ونه_TYPE (type);
      ونه ttr = ونه_TYPE (rhstype);
      منطقي is_opaque_اشاره_ګر;
      منطقي موخه_cmp = خطأ;   /* Cache comp_target_types () result.  */
      addr_space_t asl;
      addr_space_t asr;

      ونه mvl = remove_qualifiers (ttl);
      ونه mvr = remove_qualifiers (ttr);

      /* Opaque pointers are treated like void pointers.  */
      is_opaque_اشاره_ګر = ویکټور_targets_convertible_p (ttl, ttr);

      /* The Plan 9 compiler permits a pointer to a struct to be
	 automatically converted into a pointer to an anonymous field
	 within the struct.  */
      إذا (flag_plan9_extensions
	  && ریکارډ_OR_UNION_TYPE_P (mvl)
	  && ریکارډ_OR_UNION_TYPE_P (mvr)
	  && mvl != mvr)
	{
	  ونه new_rhs = convert_منزل_anonymous_ډګر (location, type, rhs);
	  إذا (new_rhs != NULL_ونه)
	    {
	      rhs = new_rhs;
	      rhstype = ونه_TYPE (rhs);
	      coder = ونه_کوډ (rhstype);
	      ttr = ونه_TYPE (rhstype);
	      mvr = TYPE_MAIN_VARIANT (ttr);
	    }
	}

      /* C++ does not allow the implicit conversion void* -> T*.  However,
	 for the purpose of reducing the number of false positives, we
	 tolerate the special case of

		int *p = NULL;

	 where NULL is typically defined in C to be '(void *) 0'.  */
      إذا (VOID_TYPE_P (ttr) && rhs != null_اشاره_ګر_غوټه && !VOID_TYPE_P (ttl))
	warning_at (errtype == ic_argpass ? بیان_loc : location,
		    OPT_Wc___compat,
		    "request for implicit conversion "
		    "from %qT to %qT not permitted in C++", rhstype, type);

      /* Warn of new allocations that are not big enough for the target
	 type.  */
      إذا (warn_alloc_اندازه && ونه_کوډ (rhs) == CALL_بیان)
	إذا (ونه fndecl = get_callee_fndecl (rhs))
	  إذا (DECL_IS_MALLOC (fndecl))
	    {
	      ونه attrs = TYPE_ځانګړتیاوې (ونه_TYPE (fndecl));
	      ونه alloc_اندازه = lookup_attribute ("alloc_size", attrs);
	      إذا (alloc_اندازه)
		warn_for_alloc_اندازه (location, ttl, rhs, alloc_اندازه);
	    }

      /* See if the pointers point to incompatible address spaces.  */
      asl = TYPE_ADDR_SPACE (ttl);
      asr = TYPE_ADDR_SPACE (ttr);
      إذا (!null_اشاره_ګر_constant_p (rhs)
	  && asr != asl && !targetm.addr_space.subset_p (asr, asl))
	{
	  auto_diagnostic_ډله d;
	  منطقي diagnosed = ریښتیا;
	  بدل (errtype)
	    {
	    حالة ic_argpass:
	      {
		ثابت حرف پیغام_2[] = G_("passing argument %d of %qE from "
				      "pointer to non-enclosed address space");
		إذا (warnopt)
		  diagnosed
		    = warning_at (بیان_loc, warnopt, پیغام_2, parmnum, rname);
		وإلا
		  error_at (بیان_loc, پیغام_2, parmnum, rname);
	      اكسر;
	      }
	    حالة ic_ټاکل:
	      {
		ثابت حرف پیغام_2[] = G_("assignment from pointer to "
				      "non-enclosed address space");
		إذا (warnopt)
		  diagnosed = warning_at (location, warnopt, پیغام_2);
		وإلا
		  error_at (location, پیغام_2);
		اكسر;
	      }
	    حالة ic_init:
	    حالة ic_init_const:
	      {
		ثابت حرف پیغام_2[] = G_("initialization from pointer to "
				      "non-enclosed address space");
		إذا (warnopt)
		  diagnosed = warning_at (location, warnopt, پیغام_2);
		وإلا
		  error_at (location, پیغام_2);
		اكسر;
	      }
	    حالة ic_return:
	      {
		ثابت حرف پیغام_2[] = G_("return from pointer to "
				      "non-enclosed address space");
		إذا (warnopt)
		  diagnosed = warning_at (location, warnopt, پیغام_2);
		وإلا
		  error_at (location, پیغام_2);
		اكسر;
	      }
	    افتراضي:
	      gcc_unreachable ();
	    }
	  إذا (diagnosed)
	    {
	      إذا (errtype == ic_argpass)
		inform_for_arg (fundecl, بیان_loc, parmnum, type, rhstype);
	      وإلا
		inform (location, "expected %qT but pointer is of type %qT",
			type, rhstype);
	    }
	  أرجع error_mark_غوټه;
	}

      /* Check if the right-hand side has a format attribute but the
	 left-hand side doesn't.  */
      إذا (warn_suggest_attribute_format
	  && check_missing_format_attribute (type, rhstype))
	{
	  بدل (errtype)
	  {
	  حالة ic_argpass:
	    warning_at (بیان_loc, OPT_Wsuggest_attribute_format,
			"argument %d of %qE might be "
			"a candidate for a format attribute",
			parmnum, rname);
	    اكسر;
	  حالة ic_ټاکل:
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
	  && !null_اشاره_ګر_constant_p (rhs)
	  && (AGGREGATE_TYPE_P (ttl) && TYPE_سرچپه_STORAGE_ترتیب (ttl))
	     != (AGGREGATE_TYPE_P (ttr) && TYPE_سرچپه_STORAGE_ترتیب (ttr)))
	{
	  ونه t;

	  بدل (errtype)
	  {
	  حالة ic_argpass:
	    /* Do not warn for built-in functions, for example memcpy, since we
	       control how they behave and they can be useful in this area.  */
	    إذا (ونه_کوډ (rname) != FUNCTION_DECL
		|| !fndecl_built_دننه_p (rname))
	      warning_at (location, OPT_Wscalar_storage_ترتیب,
			  "passing argument %d of %qE from incompatible "
			  "scalar storage order", parmnum, rname);
	    اكسر;
	  حالة ic_ټاکل:
	    /* Do not warn if the RHS is a call to a function that returns a
	       pointer that is not an alias.  */
	    إذا (ونه_کوډ (rhs) != CALL_بیان
		|| (t = get_callee_fndecl (rhs)) == NULL_ونه
		|| !DECL_IS_MALLOC (t))
	      warning_at (location, OPT_Wscalar_storage_ترتیب,
			  "assignment to %qT from pointer type %qT with "
			  "incompatible scalar storage order", type, rhstype);
	    اكسر;
	  حالة ic_init:
	  حالة ic_init_const:
	    /* Likewise.  */
	    إذا (ونه_کوډ (rhs) != CALL_بیان
		|| (t = get_callee_fndecl (rhs)) == NULL_ونه
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
	  || (موخه_cmp = comp_موخه_types (location, type, rhstype))
	  || is_opaque_اشاره_ګر
	  || ((c_common_unsigned_type (mvl)
	       == c_common_unsigned_type (mvr))
	      && (c_common_signed_type (mvl)
		  == c_common_signed_type (mvr))
	      && TYPE_ATOMIC (mvl) == TYPE_ATOMIC (mvr)))
	{
	  /* Warn about loss of qualifers from pointers to arrays with
	     qualifiers on the element type. */
	  إذا (ونه_کوډ (ttr) == ARRAY_TYPE)
	    {
	      ttr = strip_array_types (ttr);
	      ttl = strip_array_types (ttl);

	      إذا (TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttr)
		  & ~TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttl))
		WARNING_FOR_QUALIFIERS (flag_isoc23,
					location, بیان_loc,
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
	      && ((VOID_TYPE_P (ttl) && ونه_کوډ (ttr) == FUNCTION_TYPE)
		  ||
		  (VOID_TYPE_P (ttr)
		   && !null_اشاره_ګر_constant
		   && ونه_کوډ (ttl) == FUNCTION_TYPE)))
	    PEDWARN_FOR_ASSIGNMENT (location, بیان_loc, OPT_Wpedantic,
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
	  وإلا إذا (ونه_کوډ (ttr) != FUNCTION_TYPE
		   && ونه_کوډ (ttl) != FUNCTION_TYPE)
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
		PEDWARN_FOR_QUALIFIERS (location, بیان_loc,
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
		       || موخه_cmp)
		;
	      /* If there is a mismatch, do warn.  */
	      وإلا إذا (warn_اشاره_ګر_sign)
		بدل (errtype)
		  {
		  حالة ic_argpass:
		    {
		      auto_diagnostic_ډله d;
		      range_label_for_type_mismatch rhs_label (rhstype, type);
		      gcc_rich_location richloc (بیان_loc, &rhs_label,
						 highlight_colors::actual);
		      إذا (pedwarn (&richloc, OPT_Wpointer_sign,
				   "pointer targets in passing argument %d of "
				   "%qE differ in signedness", parmnum, rname))
			inform_for_arg (fundecl, بیان_loc, parmnum, type,
					rhstype);
		    }
		    اكسر;
		  حالة ic_ټاکل:
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
	  وإلا إذا (ونه_کوډ (ttl) == FUNCTION_TYPE
		   && ونه_کوډ (ttr) == FUNCTION_TYPE)
	    {
	      /* Because const and volatile on functions are restrictions
		 that say the function will not do certain things,
		 it is okay to use a const or volatile function
		 where an ordinary one is wanted, but not vice-versa.  */
	      إذا (TYPE_QUALS_NO_ADDR_SPACE (ttl)
		  & ~TYPE_QUALS_NO_ADDR_SPACE (ttr))
		PEDWARN_FOR_QUALIFIERS (location, بیان_loc,
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
	  auto_diagnostic_ډله d;
	  منطقي warned = خطأ;
	  pp_markup::element_expected_type e_type (type);
	  pp_markup::element_actual_type e_rhstype (rhstype);
	  بدل (errtype)
	    {
	    حالة ic_argpass:
	      {
		range_label_for_type_mismatch rhs_label (rhstype, type);
		gcc_rich_location richloc (بیان_loc, &rhs_label,
					   highlight_colors::actual);
		warned
		  = permerror_opt (&richloc, OPT_Wincompatible_اشاره_ګر_types,
				   "passing argument %d of %qE from "
				   "incompatible pointer type",
				   parmnum, rname);
		إذا (warned)
		  inform_for_arg (fundecl, بیان_loc, parmnum, type, rhstype);
	      }
	      اكسر;
	    حالة ic_ټاکل:
	      إذا (bltin)
		warned
		  = permerror_opt (location, OPT_Wincompatible_اشاره_ګر_types,
				   "assignment to %e from pointer to "
				   "%qD with incompatible type %e",
				   &e_type, bltin, &e_rhstype);
	      وإلا
		warned
		  = permerror_opt (location, OPT_Wincompatible_اشاره_ګر_types,
				   "assignment to %e from incompatible "
				   "pointer type %e",
				   &e_type, &e_rhstype);
	      اكسر;
	    حالة ic_init:
	    حالة ic_init_const:
	      إذا (bltin)
		warned
		  = permerror_init (location, OPT_Wincompatible_اشاره_ګر_types,
				    "initialization of %e from pointer to "
				    "%qD with incompatible type %e",
				    &e_type, bltin, &e_rhstype);
	      وإلا
		warned
		  = permerror_init (location, OPT_Wincompatible_اشاره_ګر_types,
				    "initialization of %e from incompatible "
				    "pointer type %e",
				    &e_type, &e_rhstype);
	      اكسر;
	    حالة ic_return:
	      إذا (bltin)
		warned
		  = permerror_opt (location, OPT_Wincompatible_اشاره_ګر_types,
				   "returning pointer to %qD of type %e from "
				   "a function with incompatible type %e",
				   bltin, &e_rhstype, &e_type);
	      وإلا
		warned
		  = permerror_opt (location, OPT_Wincompatible_اشاره_ګر_types,
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
	      إذا (ونه_کوډ (rhs) == ADDR_بیان
		  && ونه_کوډ (ونه_عملوند (rhs, 0)) == FUNCTION_DECL)
		{
		  ونه rhs_fndecl = ونه_عملوند (rhs, 0);
		  إذا (!DECL_IS_UNDECLARED_BUILTIN (rhs_fndecl))
		    {
		      gcc_rich_location richloc
			(DECL_سرچینه_LOCATION (rhs_fndecl), تش_اشاره,
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
      warn_for_پته_د_packed_member (type, orig_rhs);

      أرجع convert (type, rhs);
    }
  وإلا إذا (codel == اشاره_ګر_TYPE && coder == ARRAY_TYPE)
    {
      /* ??? This should not be an error when inlining calls to
	 unprototyped functions.  */
      ثابت حرف پیغام_2[] = "invalid use of non-lvalue array";
      إذا (warnopt)
	warning_at (location, warnopt, پیغام_2);
      وإلا
	error_at (location, پیغام_2);
      أرجع error_mark_غوټه;
    }
  وإلا إذا (codel == اشاره_ګر_TYPE
	   && (coder == INTEGER_TYPE
	       || coder == ENUMERAL_TYPE
	       || coder == BOOLEAN_TYPE
	       || coder == NULLPTR_TYPE
	       || coder == BITINT_TYPE))
    {
      إذا (null_اشاره_ګر_constant && c_inhibit_evaluation_warnings == 0
	  && coder != NULLPTR_TYPE)
	warning_at (location, OPT_Wzero_as_null_اشاره_ګر_constant,
		    "zero as null pointer constant");
      /* A NULLPTR type is just a nullptr always.  */
      إذا (coder == NULLPTR_TYPE)
	أرجع omit_one_عملوند_loc (بیان_loc, type, nullptr_غوټه, rhs);
      /* An explicit constant 0 or type nullptr_t can convert to a pointer,
	 or one that results from arithmetic, even including a cast to
	 integer type.  */
      وإلا إذا (!null_اشاره_ګر_constant)
	بدل (errtype)
	  {
	  حالة ic_argpass:
	    {
	      auto_diagnostic_ډله d;
	      range_label_for_type_mismatch rhs_label (rhstype, type);
	      gcc_rich_location richloc (بیان_loc, &rhs_label,
					 highlight_colors::actual);
	      إذا (permerror_opt (&richloc, OPT_Wint_conversion,
				 "passing argument %d of %qE makes pointer "
				 "from integer without a cast", parmnum, rname))
		{
		  maybe_emit_indirection_note (بیان_loc, rhs, type);
		  inform_for_arg (fundecl, بیان_loc, parmnum, type, rhstype);
		}
	    }
	    اكسر;
	  حالة ic_ټاکل:
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
	   && coder == اشاره_ګر_TYPE)
    {
      بدل (errtype)
	{
	حالة ic_argpass:
	  {
	    auto_diagnostic_ډله d;
	    range_label_for_type_mismatch rhs_label (rhstype, type);
	    gcc_rich_location richloc (بیان_loc, &rhs_label,
				       highlight_colors::actual);
	    إذا (permerror_opt (&richloc, OPT_Wint_conversion,
			       "passing argument %d of %qE makes integer from "
			       "pointer without a cast", parmnum, rname))
	      {
		maybe_emit_indirection_note (بیان_loc, rhs, type);
		inform_for_arg (fundecl, بیان_loc, parmnum, type, rhstype);
	      }
	  }
	  اكسر;
	حالة ic_ټاکل:
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
	   && (coder == اشاره_ګر_TYPE || coder == NULLPTR_TYPE))
    {
      ونه ret;
      منطقي save = دننه_late_دوګونی_op;
      دننه_late_دوګونی_op = ریښتیا;
      ret = convert (type, rhs);
      دننه_late_دوګونی_op = save;
      أرجع ret;
    }
  وإلا إذا (codel == NULLPTR_TYPE && null_اشاره_ګر_constant)
    أرجع convert (type, rhs);

  بدل (errtype)
    {
    حالة ic_argpass:
      {
	auto_diagnostic_ډله d;
	range_label_for_type_mismatch rhs_label (rhstype, type);
	gcc_rich_location richloc (بیان_loc, &rhs_label,
				   highlight_colors::actual);
	ثابت حرف پیغام_2[] = G_("incompatible type for argument %d of %qE");
	إذا (warnopt)
	  warning_at (بیان_loc, warnopt, پیغام_2, parmnum, rname);
	وإلا
	  error_at (&richloc, پیغام_2, parmnum, rname);
	inform_for_arg (fundecl, بیان_loc, parmnum, type, rhstype);
      }
      اكسر;
    حالة ic_ټاکل:
      {
	ثابت حرف پیغام_2[]
	  = G_("incompatible types when assigning to type %qT from type %qT");
	إذا (warnopt)
	  warning_at (بیان_loc, 0, پیغام_2, type, rhstype);
	وإلا
	  error_at (بیان_loc, پیغام_2, type, rhstype);
	اكسر;
      }
    حالة ic_init:
    حالة ic_init_const:
      {
	ثابت حرف پیغام_2[]
	  = G_("incompatible types when initializing type %qT using type %qT");
	إذا (warnopt)
	  warning_at (location, 0, پیغام_2, type, rhstype);
	وإلا
	  error_at (location, پیغام_2, type, rhstype);
	اكسر;
      }
    حالة ic_return:
      {
	ثابت حرف پیغام_2[]
	  = G_("incompatible types when returning type %qT but %qT was expected");
	إذا (warnopt)
	  warning_at (location, 0, پیغام_2, rhstype, type);
	وإلا
	  error_at (location, پیغام_2, rhstype, type);
	اكسر;
      }
    افتراضي:
      gcc_unreachable ();
    }

  أرجع error_mark_غوټه;
}

/* If VALUE is a compound expr all of whose expressions are constant, then
   return its value.  Otherwise, return error_mark_node.

   This is for handling COMPOUND_EXPRs as initializer elements
   which is allowed with a warning when -pedantic is specified.  */

ساكن ونه
valid_compound_بیان_initializer (ونه ارزښت, ونه endtype)
{
  إذا (ونه_کوډ (ارزښت) == COMPOUND_بیان)
    {
      إذا (valid_compound_بیان_initializer (ونه_عملوند (ارزښت, 0), endtype)
	  == error_mark_غوټه)
	أرجع error_mark_غوټه;
      أرجع valid_compound_بیان_initializer (ونه_عملوند (ارزښت, 1),
					      endtype);
    }
  وإلا إذا (!initializer_constant_valid_p (ارزښت, endtype))
    أرجع error_mark_غوټه;
  وإلا
    أرجع ارزښت;
}

/* Perform appropriate conversions on the initial value of a variable,
   store it in the declaration DECL,
   and print any error messages that are appropriate.
   If ORIGTYPE is not NULL_TREE, it is the original type of INIT.
   If the init is invalid, store an ERROR_MARK.

   INIT_LOC is the location of the initial value.  */

فراغ
store_init_ارزښت (location_t init_loc, ونه decl, ونه init, ونه origtype)
{
  ونه ارزښت, type;
  منطقي npc = خطأ;
  منطقي int_const_بیان = خطأ;
  منطقي arith_const_بیان = خطأ;

  /* If variable's type was invalidly declared, just ignore it.  */

  type = ونه_TYPE (decl);
  إذا (ونه_کوډ (type) == ERROR_MARK)
    أرجع;

  /* Digest the specified initializer into an expression.  */

  إذا (init)
    {
      npc = null_اشاره_ګر_constant_p (init);
      int_const_بیان = (ونه_کوډ (init) == INTEGER_CST
			&& !ونه_ډکېدنه (init)
			&& INTEGRAL_TYPE_P (ونه_TYPE (init)));
      /* Not fully determined before folding.  */
      arith_const_بیان = ریښتیا;
    }
  منطقي constexpr_p = (VAR_P (decl)
		      && C_DECL_DECLARED_CONSTEXPR (decl));
  ارزښت = digest_init (init_loc, decl, type, init, origtype, npc,
		       int_const_بیان, arith_const_بیان, ریښتیا,
		       ونه_STATIC (decl) || constexpr_p, constexpr_p);

  /* Store the expression if valid; else report error.  */

  إذا (!دننه_system_سرلیک_at (ننوت_location)
      && AGGREGATE_TYPE_P (ونه_TYPE (decl)) && !ونه_STATIC (decl))
    warning (OPT_Wtraditional, "traditional C rejects automatic "
	     "aggregate initialization");

  إذا (ارزښت != error_mark_غوټه || ونه_کوډ (decl) != FUNCTION_DECL)
    DECL_INITIAL (decl) = ارزښت;

  /* ANSI wants warnings about out-of-range constant initializers.  */
  STRIP_TYPE_NOPS (ارزښت);
  إذا (ونه_STATIC (decl))
    constant_افاده_warning (ارزښت);

  /* Check if we need to set array size from compound literal size.  */
  إذا (ونه_کوډ (type) == ARRAY_TYPE
      && TYPE_DOMAIN (type) == NULL_ونه
      && ارزښت != error_mark_غوټه)
    {
      ونه inside_init = init;

      STRIP_TYPE_NOPS (inside_init);
      inside_init = fold (inside_init);

      إذا (ونه_کوډ (inside_init) == COMPOUND_LITERAL_بیان)
	{
	  ونه cldecl = COMPOUND_LITERAL_بیان_DECL (inside_init);

	  إذا (TYPE_DOMAIN (ونه_TYPE (cldecl)))
	    {
	      /* For int foo[] = (int [3]){1}; we need to set array size
		 now since later on array initializer will be just the
		 brace enclosed list of the compound literal.  */
	      ونه etype = strip_array_types (ونه_TYPE (decl));
	      type = build_distinct_type_copy (TYPE_MAIN_VARIANT (type));
	      TYPE_DOMAIN (type) = TYPE_DOMAIN (ونه_TYPE (cldecl));
	      layout_type (type);
	      layout_decl (cldecl, 0);
	      ونه_TYPE (decl)
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
  صحيح ډول;
  اتحاد
    {
      بینښه HOST_WIDE_INT i;
      ثابت حرف *s;
    } u;
};

#تعریف_کړه SPELLING_STRING 1
#تعریف_کړه SPELLING_MEMBER 2
#تعریف_کړه SPELLING_BOUNDS 3

ساكن بنية spelling *spelling;	/* Next stack element (unused).  */
ساكن بنية spelling *spelling_بنسټ;	/* Spelling stack base.  */
ساكن صحيح spelling_اندازه;		/* Size of the spelling stack.  */

/* Macros to save and restore the spelling stack around push_... functions.
   Alternative to SAVE_SPELLING_STACK.  */

#تعریف_کړه SPELLING_ژوروالی() (spelling - spelling_بنسټ)
#تعریف_کړه RESTORE_SPELLING_ژوروالی(ژوروالی_2) (spelling = spelling_بنسټ + (ژوروالی_2))

/* Push an element on the spelling stack with type KIND and assign VALUE
   to MEMBER.  */

#تعریف_کړه ټېل_SPELLING(ډول_2, ارزښت_2, MEMBER)				\
{									\
  صحيح ژوروالی = SPELLING_ژوروالی ();					\
									\
  إذا (ژوروالی >= spelling_اندازه)						\
    {									\
      spelling_اندازه += 10;						\
      spelling_بنسټ = XRESIZEVEC (بنية spelling, spelling_بنسټ,	\
				  spelling_اندازه);			\
      RESTORE_SPELLING_ژوروالی (ژوروالی);					\
    }									\
									\
  spelling->ډول = (ډول_2);						\
  spelling->MEMBER = (ارزښت_2);						\
  spelling++;								\
}

/* Push STRING on the stack.  Printed literally.  */

ساكن فراغ
ټېل_string (ثابت حرف *string)
{
  ټېل_SPELLING (SPELLING_STRING, string, u.s);
}

/* Push a member name on the stack.  Printed as '.' STRING.  */

ساكن فراغ
ټېل_member_name (ونه decl)
{
  ثابت حرف *ثابت string
    = (DECL_NAME (decl)
       ? identifier_منزل_locale (IDENTIFIER_اشاره_ګر (DECL_NAME (decl)))
       : _("<anonymous>"));
  ټېل_SPELLING (SPELLING_MEMBER, string, u.s);
}

/* Push an array bounds on the stack.  Printed as [BOUNDS].  */

ساكن فراغ
ټېل_array_bounds (بینښه HOST_WIDE_INT bounds)
{
  ټېل_SPELLING (SPELLING_BOUNDS, bounds, u.i);
}

/* Compute the maximum size in bytes of the printed spelling.  */

ساكن صحيح
spelling_اوږدتیا (فراغ)
{
  صحيح اندازه = 0;
  بنية spelling *p;

  لكل (p = spelling_بنسټ; p < spelling; p++)
    {
      إذا (p->ډول == SPELLING_BOUNDS)
	اندازه += 25;
      وإلا
	اندازه += مزي_اوږدوالی (p->u.s) + 1;
    }

  أرجع اندازه;
}

/* Print the spelling to BUFFER and return it.  */

ساكن حرف *
print_spelling (حرف *بفر)
{
  حرف *d = بفر;
  بنية spelling *p;

  لكل (p = spelling_بنسټ; p < spelling; p++)
    إذا (p->ډول == SPELLING_BOUNDS)
      {
	sprintf (d, "[" HOST_WIDE_INT_PRINT_UNSIGNED "]", p->u.i);
	d += مزي_اوږدوالی (d);
      }
    وإلا
      {
	ثابت حرف *s;
	إذا (p->ډول == SPELLING_MEMBER)
	  *d++ = '.';
	لكل (s = p->u.s; (*d = *s++); d++)
	  ;
      }
  *d++ = '\0';
  أرجع بفر;
}

/* Check whether INIT, a floating or integer constant, is
   representable in TYPE, a real floating type with the same radix or
   a decimal floating type initialized with a binary floating
   constant.  Return true if OK, false if not.  */
ساكن منطقي
constexpr_init_ځاییږي_real_type (ونه type, ونه init)
{
  gcc_assert (SCALAR_FLOAT_TYPE_P (type));
  gcc_assert (ونه_کوډ (init) == INTEGER_CST || ونه_کوډ (init) == REAL_CST);
  إذا (ونه_کوډ (init) == REAL_CST
      && TYPE_ډېرپېښ (ونه_TYPE (init)) == TYPE_ډېرپېښ (type))
    {
      /* Same mode, no conversion required except for the case of
	 signaling NaNs if the types are incompatible (e.g. double and
	 long double with the same mode).  */
      إذا (REAL_ارزښت_ISSIGNALING_NAN (ونه_REAL_CST (init))
	  && !comptypes (TYPE_MAIN_VARIANT (type),
			 TYPE_MAIN_VARIANT (ونه_TYPE (init))))
	أرجع خطأ;
      أرجع ریښتیا;
    }
  إذا (ونه_کوډ (init) == INTEGER_CST)
    {
      ونه converted = build_real_from_int_cst (type, init);
      منطقي fail = خطأ;
      wide_int w = real_منزل_integer (&ونه_REAL_CST (converted), &fail,
				    TYPE_PRECISION (ونه_TYPE (init)));
      أرجع !fail && wi::eq_p (w, wi::منزل_wide (init));
    }
  إذا (REAL_ارزښت_ISSIGNALING_NAN (ونه_REAL_CST (init)))
    أرجع خطأ;
  إذا ((REAL_ارزښت_ISINF (ونه_REAL_CST (init))
       && ډېرپېښ_HAS_INFINITIES (TYPE_ډېرپېښ (type)))
      || (REAL_ارزښت_ISNAN (ونه_REAL_CST (init))
	  && ډېرپېښ_HAS_NANS (TYPE_ډېرپېښ (type))))
    أرجع ریښتیا;
  إذا (DECIMAL_FLOAT_TYPE_P (type)
      && !DECIMAL_FLOAT_TYPE_P (ونه_TYPE (init)))
    {
      /* This is valid if the real number represented by the
	 initializer can be exactly represented in the decimal
	 type.  Compare the values using MPFR.  */
      REAL_ارزښت_TYPE t;
      real_convert (&t, TYPE_ډېرپېښ (type), &ونه_REAL_CST (init));
      mpfr_t bin_val, dec_val;
      mpfr_init2 (bin_val, REAL_ډېرپېښ_FORMAT (TYPE_ډېرپېښ (ونه_TYPE (init)))->p);
      mpfr_init2 (dec_val, REAL_ډېرپېښ_FORMAT (TYPE_ډېرپېښ (ونه_TYPE (init)))->p);
      mpfr_from_real (bin_val, &ونه_REAL_CST (init), MPFR_RNDN);
      حرف string[256];
      real_منزل_decimal (string, &t, حجم string, 0, 1);
      منطقي res = (mpfr_strtofr (dec_val, string, عدم, 10, MPFR_RNDN) == 0
		  && mpfr_equal_p (bin_val, dec_val));
      mpfr_clear (bin_val);
      mpfr_clear (dec_val);
      أرجع res;
    }
  /* exact_real_truncate is not quite right here, since it doesn't
     allow even an exact conversion to subnormal values.  */
  REAL_ارزښت_TYPE t;
  real_convert (&t, TYPE_ډېرپېښ (type), &ونه_REAL_CST (init));
  أرجع real_identical (&t, &ونه_REAL_CST (init));
}

/* Check whether INIT (location LOC) is valid as a 'constexpr'
   initializer for type TYPE, and give an error if not.  INIT has
   already been folded and verified to be constant.  INT_CONST_EXPR
   and ARITH_CONST_EXPR say whether it is an integer constant
   expression or arithmetic constant expression, respectively.  If
   TYPE is not a scalar type, this function does nothing.  */

ساكن فراغ
check_constexpr_init (location_t loc, ونه type, ونه init,
		      منطقي int_const_بیان, منطقي arith_const_بیان)
{
  إذا (اشاره_ګر_TYPE_P (type))
    {
      /* The initializer must be null.  */
      إذا (ونه_کوډ (init) != INTEGER_CST || !integer_zerop (init))
	error_at (loc, "%<constexpr%> pointer initializer is not null");
      أرجع;
    }
  إذا (INTEGRAL_TYPE_P (type))
    {
      /* The initializer must be an integer constant expression,
	 representable in the target type.  */
      إذا (!int_const_بیان)
	{
	  إذا (ونه_کوډ (init) == RAW_معلومات_CST
	      && TYPE_PRECISION (type) == CHAR_بټ)
	    {
	      إذا (!TYPE_UNSIGNED (type))
		لكل (بینښه صحيح i = 0;
		     i < (بینښه) RAW_معلومات_اوږدتیا (init); ++i)
		  إذا (RAW_معلومات_SCHAR_ELT (init, i) < 0)
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
      وإلا إذا (!int_ځاییږي_type_p (init, type))
	error_at (loc, "%<constexpr%> initializer not representable in "
		  "type of object");
      أرجع;
    }
  /* We don't apply any extra checks to extension types such as vector
     or fixed-point types.  */
  إذا (ونه_کوډ (type) != REAL_TYPE && ونه_کوډ (type) != COMPLEX_TYPE)
    أرجع;
  إذا (!arith_const_بیان)
    {
      error_at (loc, "%<constexpr%> initializer is not an arithmetic "
		"constant expression");
      أرجع;
    }
  /* We don't apply any extra checks to complex integers.  */
  إذا (ونه_کوډ (type) == COMPLEX_TYPE
      && ونه_کوډ (ونه_TYPE (type)) != REAL_TYPE)
    أرجع;
  /* Following N3082, a real type cannot be initialized from a complex
     type and a binary type cannot be initialized from a decimal type
     (but initializing a decimal type from a binary type is OK).
     Signaling NaN initializers are OK only if the types are
     compatible (not just the same mode); all quiet NaN and infinity
     initializations are considered to preserve the value.  */
  إذا (ونه_کوډ (ونه_TYPE (init)) == COMPLEX_TYPE
      && SCALAR_FLOAT_TYPE_P (type))
    {
      error_at (loc, "%<constexpr%> initializer for a real type is of "
		"complex type");
      أرجع;
    }
  إذا (SCALAR_FLOAT_TYPE_P (type)
      && SCALAR_FLOAT_TYPE_P (ونه_TYPE (init))
      && DECIMAL_FLOAT_TYPE_P (ونه_TYPE (init))
      && !DECIMAL_FLOAT_TYPE_P (type))
    {
      error_at (loc, "%<constexpr%> initializer for a binary "
		"floating-point type is of decimal type");
      أرجع;
    }
  منطقي ځاییږي;
  إذا (ونه_کوډ (type) == COMPLEX_TYPE)
    {
      بدل (ونه_کوډ (init))
	{
	حالة INTEGER_CST:
	حالة REAL_CST:
	  ځاییږي = constexpr_init_ځاییږي_real_type (ونه_TYPE (type), init);
	  اكسر;
	حالة COMPLEX_CST:
	  ځاییږي = (constexpr_init_ځاییږي_real_type (ونه_TYPE (type),
						 ونه_REALPART (init))
		  && constexpr_init_ځاییږي_real_type (ونه_TYPE (type),
						    ونه_IMAGPART (init)));
	  اكسر;
	افتراضي:
	  gcc_unreachable ();
	}
    }
  وإلا
    ځاییږي = constexpr_init_ځاییږي_real_type (type, init);
  إذا (!ځاییږي)
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

ساكن ونه
digest_init (location_t init_loc, ونه decl, ونه type, ونه init,
	     ونه origtype, منطقي null_اشاره_ګر_constant, منطقي int_const_بیان,
	     منطقي arith_const_بیان, منطقي strict_string,
	     منطقي require_constant, منطقي require_constexpr)
{
  تعداد ونه_کوډ_2 کوډ = ونه_کوډ (type);
  ونه inside_init = init;
  ونه semantic_type = NULL_ونه;
  منطقي maybe_const = ریښتیا;

  إذا (type == error_mark_غوټه
      || !init
      || error_عملوند_p (init))
    أرجع error_mark_غوټه;

  STRIP_TYPE_NOPS (inside_init);

  /* If require_constant is TRUE,  when the initializer is a call to
     .ACCESS_WITH_SIZE, use the first argument as the initializer.
     For example:
     y = (char *) .ACCESS_WITH_SIZE ((char *) &static_annotated.c,...)
     will be converted to
     y = &static_annotated.c.  */

  إذا (require_constant
      && ونه_کوډ (inside_init) == NOP_بیان
      && ونه_کوډ (ونه_عملوند (inside_init, 0)) == CALL_بیان
      && is_access_with_اندازه_p (ونه_عملوند (inside_init, 0)))
    inside_init
      = get_ref_from_access_with_اندازه (ونه_عملوند (inside_init, 0));

  إذا (!c_دننه_omp_for)
    {
      إذا (ونه_کوډ (inside_init) == EXCESS_PRECISION_بیان)
	{
	  semantic_type = ونه_TYPE (inside_init);
	  inside_init = ونه_عملوند (inside_init, 0);
	}
      inside_init = c_fully_fold (inside_init, require_constant, &maybe_const);
    }
  /* TODO: this may not detect all cases of expressions folding to
     constants that are not arithmetic constant expressions.  */
  إذا (!maybe_const)
    arith_const_بیان = خطأ;
  وإلا إذا (!INTEGRAL_TYPE_P (ونه_TYPE (inside_init))
	   && ونه_کوډ (ونه_TYPE (inside_init)) != REAL_TYPE
	   && ونه_کوډ (ونه_TYPE (inside_init)) != COMPLEX_TYPE)
    arith_const_بیان = خطأ;
  وإلا إذا (ونه_کوډ (inside_init) != INTEGER_CST
	   && ونه_کوډ (inside_init) != REAL_CST
	   && ونه_کوډ (inside_init) != COMPLEX_CST
	   && ونه_کوډ (inside_init) != RAW_معلومات_CST)
    arith_const_بیان = خطأ;
  وإلا إذا (ونه_ډکېدنه (inside_init))
    arith_const_بیان = خطأ;

  /* Initialization of an array of chars from a string constant
     optionally enclosed in braces.  */

  إذا (کوډ == ARRAY_TYPE && inside_init
      && ونه_کوډ (inside_init) == STRING_CST)
    {
      ونه typ1
	= (TYPE_ATOMIC (ونه_TYPE (type))
	   ? c_build_qualified_type (TYPE_MAIN_VARIANT (ونه_TYPE (type)),
				     TYPE_QUAL_ATOMIC)
	   : TYPE_MAIN_VARIANT (ونه_TYPE (type)));
      /* Note that an array could be both an array of character type
	 and an array of wchar_t if wchar_t is signed char or unsigned
	 char.  */
      منطقي char_array = (typ1 == char_type_غوټه
			 || typ1 == signed_char_type_غوټه
			 || typ1 == unsigned_char_type_غوټه);
      منطقي wchar_array = comptypes (typ1, wchar_type_غوټه);
      منطقي char16_array = comptypes (typ1, char16_type_غوټه);
      منطقي char32_array = comptypes (typ1, char32_type_غوټه);

      إذا (char_array || wchar_array || char16_array || char32_array)
	{
	  بنية c_بیان بیان;
	  ونه typ2 = TYPE_MAIN_VARIANT (ونه_TYPE (ونه_TYPE (inside_init)));
	  منطقي incompat_string_cst = خطأ;
	  بیان.ارزښت = inside_init;
	  بیان.original_کوډ = (strict_string ? STRING_CST : ERROR_MARK);
	  بیان.original_type = عدم;
	  بیان.m_decimal = 0;
	  maybe_warn_string_init (init_loc, type, بیان);

	  إذا (flexible_array_member_type_p (type))
	    pedwarn_init (init_loc, OPT_Wpedantic,
			  "initialization of a flexible array member");

	  إذا (comptypes (TYPE_MAIN_VARIANT (ونه_TYPE (inside_init)),
			 TYPE_MAIN_VARIANT (type)))
	    أرجع inside_init;

	  إذا (char_array)
	    {
	      إذا (typ2 != char_type_غوټه && typ2 != char8_type_غوټه)
		incompat_string_cst = ریښتیا;
	    }
	  وإلا إذا (!comptypes (typ1, typ2))
	    incompat_string_cst = ریښتیا;

          إذا (incompat_string_cst)
            {
	      error_init (init_loc, "cannot initialize array of %qT from "
			  "a string literal with type array of %qT",
			  typ1, typ2);
	      أرجع error_mark_غوټه;
            }

	  إذا (require_constexpr
	      && TYPE_UNSIGNED (typ1) != TYPE_UNSIGNED (typ2))
	    {
	      /* Check if all characters of the string can be
		 represented in the type of the constexpr object being
		 initialized.  */
	      بینښه HOST_WIDE_INT len = ونه_STRING_اوږدتیا (inside_init);
	      ثابت بینښه حرف *p =
		(ثابت بینښه حرف *) ونه_STRING_اشاره_ګر (inside_init);
	      gcc_assert (CHAR_TYPE_اندازه == 8 && CHAR_بټ == 8);
	      لكل (بینښه i = 0; i < len; i++)
		إذا (p[i] > 127)
		  {
		    error_init (init_loc, "%<constexpr%> initializer not "
				"representable in type of object");
		    اكسر;
		  }
	    }

	  إذا (TYPE_DOMAIN (type) != NULL_ونه
	      && TYPE_اندازه (type) != NULL_ونه
	      && ونه_کوډ (TYPE_اندازه (type)) == INTEGER_CST)
	    {
	      بینښه HOST_WIDE_INT len = ونه_STRING_اوږدتیا (inside_init);

	      إذا (compare_ونه_int (TYPE_اندازه_UNIT (type), len) < 0)
		{
		  بینښه HOST_WIDE_INT avail
		    = ونه_منزل_uhwi (TYPE_اندازه_UNIT (type));
		  بینښه unit = TYPE_PRECISION (typ1) / بټونه_فی_UNIT;
		  ثابت حرف *p = ونه_STRING_اشاره_ګر (inside_init);

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
			   && get_attr_nonstring_decl (decl) == NULL_ونه)
		    warning_at (init_loc,
				OPT_Wunterminated_string_initialization,
				"initializer-string for array of %qT "
				"truncates NUL terminator but destination "
				"lacks %qs attribute (%wu chars into %wu "
				"available)", typ1, "nonstring", len, avail);
		}
	    }

	  ونه_TYPE (inside_init) = type;
	  أرجع inside_init;
	}
      وإلا إذا (INTEGRAL_TYPE_P (typ1))
	{
	  error_init (init_loc, "array of inappropriate type initialized "
		      "from string constant");
	  أرجع error_mark_غوټه;
	}
    }

  /* Build a VECTOR_CST from a *constant* vector constructor.  If the
     vector constructor is not constant (e.g. {1,2,3,foo()}) then punt
     below and handle as a constructor.  */
  إذا (کوډ == ویکټور_TYPE
      && ویکټور_TYPE_P (ونه_TYPE (inside_init))
      && ویکټور_types_convertible_p (ونه_TYPE (inside_init), type, ریښتیا)
      && ونه_CONSTANT (inside_init))
    {
      إذا (ونه_کوډ (inside_init) == ویکټور_CST
	  && comptypes (TYPE_MAIN_VARIANT (ونه_TYPE (inside_init)),
			TYPE_MAIN_VARIANT (type)))
	أرجع inside_init;

      إذا (ونه_کوډ (inside_init) == CONSTRUCTOR)
	{
	  بینښه HOST_WIDE_INT ix;
	  ونه ارزښت;
	  منطقي constant_p = ریښتیا;

	  /* Iterate through elements and check if all constructor
	     elements are *_CSTs.  */
	  FOR_EACH_CONSTRUCTOR_ارزښت (CONSTRUCTOR_ELTS (inside_init), ix, ارزښت)
	    إذا (!CONSTANT_CLASS_P (ارزښت))
	      {
		constant_p = خطأ;
		اكسر;
	      }

	  إذا (constant_p)
	    أرجع build_ویکټور_from_ctor (type,
					   CONSTRUCTOR_ELTS (inside_init));
	}
    }

  إذا (warn_sequence_ټکی)
    verify_sequence_points (inside_init);

  /* Any type can be initialized
     from an expression of the same type, optionally with braces.  */

  إذا (inside_init && ونه_TYPE (inside_init) != NULL_ونه
      && (comptypes (TYPE_MAIN_VARIANT (ونه_TYPE (inside_init)),
		     TYPE_MAIN_VARIANT (type))
	  || (کوډ == ARRAY_TYPE
	      && comptypes (ونه_TYPE (inside_init), type))
	  || (gnu_ویکټور_type_p (type)
	      && comptypes (ونه_TYPE (inside_init), type))
	  || (کوډ == اشاره_ګر_TYPE
	      && ونه_کوډ (ونه_TYPE (inside_init)) == ARRAY_TYPE
	      && comptypes (ونه_TYPE (ونه_TYPE (inside_init)),
			    ونه_TYPE (type)))))
    {
      إذا (کوډ == اشاره_ګر_TYPE)
	{
	  إذا (ونه_کوډ (ونه_TYPE (inside_init)) == ARRAY_TYPE)
	    {
	      إذا (ونه_کوډ (inside_init) == STRING_CST
		  || ونه_کوډ (inside_init) == COMPOUND_LITERAL_بیان)
		inside_init = array_منزل_اشاره_ګر_conversion
		  (init_loc, inside_init);
	      وإلا
		{
		  error_init (init_loc, "invalid use of non-lvalue array");
		  أرجع error_mark_غوټه;
		}
	    }
	}

      إذا (کوډ == ویکټور_TYPE || c_hardbool_type_attr (type))
	/* Although the types are compatible, we may require a
	   conversion.  */
	inside_init = convert (type, inside_init);

      إذا ((کوډ == ریکارډ_TYPE || کوډ == UNION_TYPE)
	  && !comptypes (TYPE_MAIN_VARIANT (type), TYPE_MAIN_VARIANT (ونه_TYPE (inside_init))))
	{
	  error_init (init_loc, "invalid initializer");
	  أرجع error_mark_غوټه;
	}

      إذا (require_constant
	  && ونه_کوډ (inside_init) == COMPOUND_LITERAL_بیان)
	{
	  /* As an extension, allow initializing objects with static storage
	     duration with compound literals (which are then treated just as
	     the brace enclosed list they contain).  Also allow this for
	     vectors, as we can only assign them with compound literals.  */
	  إذا (flag_isoc99 && کوډ != ویکټور_TYPE)
	    pedwarn_init (init_loc, OPT_Wpedantic, "initializer element "
			  "is not constant");
	  ونه decl = COMPOUND_LITERAL_بیان_DECL (inside_init);
	  inside_init = DECL_INITIAL (decl);
	}

      إذا (کوډ == ARRAY_TYPE && ونه_کوډ (inside_init) != STRING_CST
	  && ونه_کوډ (inside_init) != CONSTRUCTOR)
	{
	  error_init (init_loc, "array initialized from non-constant array "
		      "expression");
	  أرجع error_mark_غوټه;
	}

      /* Compound expressions can only occur here if -Wpedantic or
	 -pedantic-errors is specified.  In the later case, we always want
	 an error.  In the former case, we simply want a warning.  */
      إذا (require_constant && pedantic
	  && ونه_کوډ (inside_init) == COMPOUND_بیان)
	{
	  inside_init
	    = valid_compound_بیان_initializer (inside_init,
					       ونه_TYPE (inside_init));
	  إذا (inside_init == error_mark_غوټه)
	    error_init (init_loc, "initializer element is not constant");
	  وإلا
	    pedwarn_init (init_loc, OPT_Wpedantic,
			  "initializer element is not constant");
	  إذا (flag_pedantic_errors)
	    inside_init = error_mark_غوټه;
	}
      وإلا إذا (require_constant
	       && !initializer_constant_valid_p (inside_init,
						 ونه_TYPE (inside_init)))
	{
	  error_init (init_loc, "initializer element is not constant");
	  inside_init = error_mark_غوټه;
	}
      وإلا إذا (require_constant && !maybe_const)
	pedwarn_init (init_loc, OPT_Wpedantic,
		      "initializer element is not a constant expression");
      وإلا إذا (require_constexpr)
	check_constexpr_init (init_loc, type, inside_init,
			      int_const_بیان, arith_const_بیان);

      /* Added to enable additional -Wsuggest-attribute=format warnings.  */
      إذا (ونه_کوډ (ونه_TYPE (inside_init)) == اشاره_ګر_TYPE)
	inside_init = convert_for_assignment (init_loc, UNKNOWN_LOCATION,
					      type, inside_init, origtype,
					      (require_constant
					       ? ic_init_const
					       : ic_init), null_اشاره_ګر_constant,
					      NULL_ونه, NULL_ونه, 0);
      إذا (ونه_کوډ (inside_init) == RAW_معلومات_CST
	  && c_inhibit_evaluation_warnings == 0
	  && warn_conversion
	  && !TYPE_UNSIGNED (type)
	  && TYPE_PRECISION (type) == CHAR_بټ)
	لكل (بینښه صحيح i = 0;
	     i < (بینښه) RAW_معلومات_اوږدتیا (inside_init); ++i)
	  إذا (RAW_معلومات_SCHAR_ELT (inside_init, i) < 0)
	    warning_at (init_loc, OPT_Wconversion,
			"conversion from %qT to %qT changes value from "
			"%qd to %qd",
			integer_type_غوټه, type,
			RAW_معلومات_UCHAR_ELT (inside_init, i),
			RAW_معلومات_SCHAR_ELT (inside_init, i));
      أرجع inside_init;
    }

  /* Handle scalar types, including conversions.  */

  إذا (کوډ == INTEGER_TYPE || کوډ == REAL_TYPE || کوډ == FIXED_ټکی_TYPE
      || کوډ == اشاره_ګر_TYPE || کوډ == ENUMERAL_TYPE || کوډ == BOOLEAN_TYPE
      || کوډ == COMPLEX_TYPE || کوډ == ویکټور_TYPE || کوډ == NULLPTR_TYPE
      || کوډ == BITINT_TYPE)
    {
      ونه unconverted_init = inside_init;
      إذا (ونه_کوډ (ونه_TYPE (init)) == ARRAY_TYPE
	  && (ونه_کوډ (init) == STRING_CST
	      || ونه_کوډ (init) == COMPOUND_LITERAL_بیان))
	inside_init = init = array_منزل_اشاره_ګر_conversion (init_loc, init);
      إذا (semantic_type)
	inside_init = build1 (EXCESS_PRECISION_بیان, semantic_type,
			      inside_init);
      inside_init
	= convert_for_assignment (init_loc, UNKNOWN_LOCATION, type,
				  inside_init, origtype,
				  require_constant ? ic_init_const : ic_init,
				  null_اشاره_ګر_constant, NULL_ونه, NULL_ونه,
				  0);

      /* Check to see if we have already given an error message.  */
      إذا (inside_init == error_mark_غوټه)
	;
      وإلا إذا (require_constant && !ونه_CONSTANT (inside_init))
	{
	  error_init (init_loc, "initializer element is not constant");
	  inside_init = error_mark_غوټه;
	}
      وإلا إذا (require_constant
	       && !initializer_constant_valid_p (inside_init,
						 ونه_TYPE (inside_init)))
	{
	  error_init (init_loc, "initializer element is not computable at "
		      "load time");
	  inside_init = error_mark_غوټه;
	}
      وإلا إذا (require_constant && !maybe_const)
	pedwarn_init (init_loc, OPT_Wpedantic,
		      "initializer element is not a constant expression");
      وإلا إذا (require_constexpr)
	check_constexpr_init (init_loc, type, unconverted_init,
			      int_const_بیان, arith_const_بیان);

      أرجع inside_init;
    }

  /* Come here only for records and arrays.  */

  إذا (COMPLETE_TYPE_P (type) && ونه_کوډ (TYPE_اندازه (type)) != INTEGER_CST)
    {
      error_init (init_loc,
		  "variable-sized object may not be initialized except "
		  "with an empty initializer");
      أرجع error_mark_غوټه;
    }

  error_init (init_loc, "invalid initializer");
  أرجع error_mark_غوټه;
}

/* Handle initializers that use braces.  */

/* Type of object we are accumulating a constructor for.
   This type is always a RECORD_TYPE, UNION_TYPE or ARRAY_TYPE.  */
ساكن ونه constructor_type;

/* For a RECORD_TYPE or UNION_TYPE, this is the chain of fields
   left to fill.  */
ساكن ونه constructor_fields;

/* For an ARRAY_TYPE, this is the specified index
   at which to store the next element we get.  */
ساكن ونه constructor_شاخص;

/* For an ARRAY_TYPE, this is the maximum index.  */
ساكن ونه constructor_max_شاخص;

/* For a RECORD_TYPE, this is the first field not yet written out.  */
ساكن ونه constructor_unfilled_fields;

/* For an ARRAY_TYPE, this is the index of the first element
   not yet written out.  */
ساكن ونه constructor_unfilled_شاخص;

/* In a RECORD_TYPE, the byte index of the next consecutive field.
   This is so we can generate gaps between fields, when appropriate.  */
ساكن ونه constructor_بټ_شاخص;

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
ساكن منطقي constructor_zero_padding_بټونه;

/* 1 if this constructor is a braced scalar initializer (further nested levels
   of braces are an error).  */
ساكن منطقي constructor_braced_scalar;

/* Structure for managing pending initializer elements, organized as an
   AVL tree.  */

بنية init_غوټه
{
  بنية init_غوټه *کیڼ, *ښی;
  بنية init_غوټه *پلار;
  صحيح balance;
  ونه purpose;
  ونه ارزښت;
  ونه origtype;
};

/* Tree of pending elements at this constructor level.
   These are elements encountered out of order
   which belong at places we haven't reached yet in actually
   writing the output.
   Will never hold tree nodes across GC runs.  */
ساكن بنية init_غوټه *constructor_pending_elts;

/* The SPELLING_DEPTH of this constructor.  */
ساكن صحيح constructor_ژوروالی;

/* DECL node for which an initializer is being read.
   0 means we are reading a constructor expression
   such as (struct foo) {...}.  */
ساكن ونه constructor_decl;

/* Nonzero if there were any member designators in this initializer.  */
ساكن صحيح constructor_designated;

/* Nesting depth of designator list.  */
ساكن صحيح designator_ژوروالی;

/* Nonzero if there were diagnosed errors in this designator list.  */
ساكن صحيح designator_erroneous;


/* This stack has a level for each implicit or explicit level of
   structuring in the initializer, including the outermost one.  It
   saves the values of most of the variables above.  */

بنية constructor_range_ډېری;

بنية constructor_ډېری
{
  بنية constructor_ډېری *بل;
  ونه type;
  ونه fields;
  ونه شاخص;
  ونه max_شاخص;
  ونه unfilled_شاخص;
  ونه unfilled_fields;
  ونه بټ_شاخص;
  vec<constructor_elt, va_gc> *elements;
  بنية init_غوټه *pending_elts;
  صحيح دننه_واټن;
  صحيح ژوروالی;
  /* If value nonzero, this value should replace the entire
     constructor at this level.  */
  بنية c_بیان replacement_ارزښت;
  بنية constructor_range_ډېری *range_ډېری;
  حرف constant;
  حرف simple;
  حرف nonconst;
  حرف implicit;
  حرف erroneous;
  حرف outer;
  حرف incremental;
  حرف designated;
  منطقي zero_padding_بټونه;
  منطقي braced_scalar;
  صحيح designator_ژوروالی;
};

ساكن بنية constructor_ډېری *constructor_ډېری;

/* This stack represents designators from some range designator up to
   the last designator in the list.  */

بنية constructor_range_ډېری
{
  بنية constructor_range_ډېری *بل, *prev;
  بنية constructor_ډېری *ډېری;
  ونه range_پیل;
  ونه شاخص;
  ونه range_پای_ټکی;
  ونه fields;
};

ساكن بنية constructor_range_ډېری *constructor_range_ډېری;

/* This stack records separate initializers that are nested.
   Nested initializers can't happen in ANSI C, but GNU C allows them
   in cases like { ... (struct foo) { ... } ... }.  */

بنية initializer_ډېری
{
  بنية initializer_ډېری *بل;
  ونه decl;
  بنية constructor_ډېری *constructor_ډېری;
  بنية constructor_range_ډېری *constructor_range_ډېری;
  vec<constructor_elt, va_gc> *elements;
  بنية spelling *spelling;
  بنية spelling *spelling_بنسټ;
  صحيح spelling_اندازه;
  حرف require_constant_ارزښت;
  حرف require_constant_elements;
  حرف require_constexpr_ارزښت;
  حرف designated;
  rich_location *missing_brace_richloc;
};

ساكن بنية initializer_ډېری *initializer_ډېری;

/* Prepare to parse and output the initializer for variable DECL.  */

فراغ
پیل_init (ونه decl, ونه asmspec_ونه ATTRIBUTE_ناکارول_شوی,
	    منطقي init_require_constant, منطقي init_require_constexpr,
	    rich_location *richloc)
{
  ثابت حرف *locus;
  بنية initializer_ډېری *p = XNEW (بنية initializer_ډېری);

  p->decl = constructor_decl;
  p->require_constant_ارزښت = require_constant_ارزښت;
  p->require_constant_elements = require_constant_elements;
  p->require_constexpr_ارزښت = require_constexpr_ارزښت;
  p->constructor_ډېری = constructor_ډېری;
  p->constructor_range_ډېری = constructor_range_ډېری;
  p->elements = constructor_elements;
  p->spelling = spelling;
  p->spelling_بنسټ = spelling_بنسټ;
  p->spelling_اندازه = spelling_اندازه;
  p->بل = initializer_ډېری;
  p->missing_brace_richloc = richloc;
  p->designated = constructor_designated;
  initializer_ډېری = p;

  constructor_decl = decl;
  constructor_designated = 0;

  require_constant_ارزښت = init_require_constant;
  require_constexpr_ارزښت = init_require_constexpr;
  إذا (decl != NULL_ونه && decl != error_mark_غوټه)
    {
      require_constant_elements
	= ((init_require_constant || (pedantic && !flag_isoc99))
	   /* For a scalar, you can always use any value to initialize,
	      even within braces.  */
	   && AGGREGATE_TYPE_P (ونه_TYPE (decl)));
      locus = identifier_منزل_locale (IDENTIFIER_اشاره_ګر (DECL_NAME (decl)));
    }
  وإلا
    {
      require_constant_elements = خطأ;
      locus = _("(anonymous)");
    }

  constructor_ډېری = 0;
  constructor_range_ډېری = 0;

  وموندل_missing_braces = 0;

  spelling_بنسټ = 0;
  spelling_اندازه = 0;
  RESTORE_SPELLING_ژوروالی (0);

  إذا (locus)
    ټېل_string (locus);
}

فراغ
پای_init (فراغ)
{
  بنية initializer_ډېری *p = initializer_ډېری;

  /* Free the whole constructor stack of this initializer.  */
  طالما (constructor_ډېری)
    {
      بنية constructor_ډېری *q = constructor_ډېری;
      constructor_ډېری = q->بل;
      XDELETE (q);
    }

  gcc_assert (!constructor_range_ډېری);

  /* Pop back to the data of the outer initializer (if any).  */
  XDELETE (spelling_بنسټ);

  constructor_decl = p->decl;
  require_constant_ارزښت = p->require_constant_ارزښت;
  require_constant_elements = p->require_constant_elements;
  require_constexpr_ارزښت = p->require_constexpr_ارزښت;
  constructor_ډېری = p->constructor_ډېری;
  constructor_designated = p->designated;
  constructor_range_ډېری = p->constructor_range_ډېری;
  constructor_elements = p->elements;
  spelling = p->spelling;
  spelling_بنسټ = p->spelling_بنسټ;
  spelling_اندازه = p->spelling_اندازه;
  initializer_ډېری = p->بل;
  XDELETE (p);
}

/* Call here when we see the initializer is surrounded by braces.
   This is instead of a call to push_init_level;
   it is matched by a call to pop_init_level.

   TYPE is the type to initialize, for a constructor expression.
   For an initializer for a decl, TYPE is zero.  */

فراغ
really_پیل_incremental_init (ونه type)
{
  بنية constructor_ډېری *p = XNEW (بنية constructor_ډېری);

  إذا (type == NULL_ونه)
    type = ونه_TYPE (constructor_decl);

  إذا (ویکټور_TYPE_P (type)
      && TYPE_ویکټور_OPAQUE (type))
    error ("opaque vector types cannot be initialized");

  p->type = constructor_type;
  p->fields = constructor_fields;
  p->شاخص = constructor_شاخص;
  p->max_شاخص = constructor_max_شاخص;
  p->unfilled_شاخص = constructor_unfilled_شاخص;
  p->unfilled_fields = constructor_unfilled_fields;
  p->بټ_شاخص = constructor_بټ_شاخص;
  p->elements = constructor_elements;
  p->constant = constructor_constant;
  p->simple = constructor_simple;
  p->nonconst = constructor_nonconst;
  p->erroneous = constructor_erroneous;
  p->pending_elts = constructor_pending_elts;
  p->ژوروالی = constructor_ژوروالی;
  p->replacement_ارزښت.ارزښت = 0;
  p->replacement_ارزښت.original_کوډ = ERROR_MARK;
  p->replacement_ارزښت.original_type = عدم;
  p->implicit = 0;
  p->range_ډېری = 0;
  p->outer = 0;
  p->incremental = constructor_incremental;
  p->designated = constructor_designated;
  p->zero_padding_بټونه = constructor_zero_padding_بټونه;
  p->braced_scalar = constructor_braced_scalar;
  p->designator_ژوروالی = designator_ژوروالی;
  p->بل = 0;
  constructor_ډېری = p;

  constructor_constant = 1;
  constructor_simple = 1;
  constructor_nonconst = 0;
  constructor_ژوروالی = SPELLING_ژوروالی ();
  constructor_elements = عدم;
  constructor_pending_elts = 0;
  constructor_type = type;
  constructor_incremental = 1;
  constructor_designated = 0;
  constructor_zero_padding_بټونه = خطأ;
  constructor_zeroinit = 1;
  constructor_braced_scalar = خطأ;
  designator_ژوروالی = 0;
  designator_erroneous = 0;

  إذا (ریکارډ_OR_UNION_TYPE_P (constructor_type))
    {
      constructor_fields = TYPE_FIELDS (constructor_type);
      /* Skip any nameless bit fields at the beginning.  */
      طالما (constructor_fields != NULL_ونه
	     && DECL_UNNAMED_بټ_ډګر (constructor_fields))
	constructor_fields = DECL_CHAIN (constructor_fields);

      constructor_unfilled_fields = constructor_fields;
      constructor_بټ_شاخص = bitsize_zero_غوټه;
    }
  وإلا إذا (ونه_کوډ (constructor_type) == ARRAY_TYPE)
    {
      إذا (TYPE_DOMAIN (constructor_type))
	{
	  constructor_max_شاخص
	    = TYPE_MAX_ارزښت (TYPE_DOMAIN (constructor_type));

	  /* Detect non-empty initializations of zero-length arrays.  */
	  إذا (constructor_max_شاخص == NULL_ونه
	      && TYPE_اندازه (constructor_type))
	    constructor_max_شاخص = integer_minus_one_غوټه;

	  /* constructor_max_index needs to be an INTEGER_CST.  Attempts
	     to initialize VLAs with a nonempty initializer will cause a
	     proper error; avoid tree checking errors as well by setting a
	     safe value.  */
	  إذا (constructor_max_شاخص
	      && ونه_کوډ (constructor_max_شاخص) != INTEGER_CST)
	    constructor_max_شاخص = integer_minus_one_غوټه;

	  constructor_شاخص
	    = convert (bitsizetype,
		       TYPE_MIN_ارزښت (TYPE_DOMAIN (constructor_type)));
	}
      وإلا
	{
	  constructor_شاخص = bitsize_zero_غوټه;
	  constructor_max_شاخص = NULL_ونه;
	}

      constructor_unfilled_شاخص = constructor_شاخص;
    }
  وإلا إذا (gnu_ویکټور_type_p (constructor_type))
    {
      /* Vectors are like simple fixed-size arrays.  */
      constructor_max_شاخص =
	bitsize_int (TYPE_ویکټور_SUBPARTS (constructor_type) - 1);
      constructor_شاخص = bitsize_zero_غوټه;
      constructor_unfilled_شاخص = constructor_شاخص;
    }
  وإلا
    {
      /* Handle the case of int x = {5}; */
      constructor_fields = constructor_type;
      constructor_unfilled_fields = constructor_type;
      constructor_braced_scalar = ریښتیا;
    }
}

خارجي location_t وروستی_init_list_comma;

/* Called when we see an open brace for a nested initializer.  Finish
   off any pending levels with implicit braces.  */
فراغ
پای_implicit_inits (location_t loc, بنية obstack *braced_init_obstack)
{
  طالما (constructor_ډېری->implicit)
    {
      إذا (ریکارډ_OR_UNION_TYPE_P (constructor_type)
	  && constructor_fields == NULL_ونه)
	process_init_element (ننوت_location,
			      راوباسه_init_level (loc, 1, braced_init_obstack,
					      وروستی_init_list_comma),
			      ریښتیا, braced_init_obstack);
      وإلا إذا (ونه_کوډ (constructor_type) == ARRAY_TYPE
	       && constructor_max_شاخص
	       && ونه_int_cst_lt (constructor_max_شاخص,
				   constructor_شاخص))
	process_init_element (ننوت_location,
			      راوباسه_init_level (loc, 1, braced_init_obstack,
					      وروستی_init_list_comma),
			      ریښتیا, braced_init_obstack);
      وإلا
	اكسر;
    }
}

/* Push down into a subobject, for initialization.
   If this is for an explicit set of braces, IMPLICIT is 0.
   If it is because the next element belongs at a lower level,
   IMPLICIT is 1 (or 2 if the push is because of designator list).  */

فراغ
ټېل_init_level (location_t loc, صحيح implicit,
		 بنية obstack *braced_init_obstack)
{
  بنية constructor_ډېری *p;
  ونه ارزښت = NULL_ونه;

  /* Unless this is an explicit brace, we need to preserve previous
     content if any.  */
  إذا (implicit)
    {
      إذا (ریکارډ_OR_UNION_TYPE_P (constructor_type) && constructor_fields)
	ارزښت = پیدا_کړه_init_member (constructor_fields, braced_init_obstack);
      وإلا إذا (ونه_کوډ (constructor_type) == ARRAY_TYPE)
	ارزښت = پیدا_کړه_init_member (constructor_شاخص, braced_init_obstack);
    }

  p = XNEW (بنية constructor_ډېری);
  p->type = constructor_type;
  p->fields = constructor_fields;
  p->شاخص = constructor_شاخص;
  p->max_شاخص = constructor_max_شاخص;
  p->unfilled_شاخص = constructor_unfilled_شاخص;
  p->unfilled_fields = constructor_unfilled_fields;
  p->بټ_شاخص = constructor_بټ_شاخص;
  p->elements = constructor_elements;
  p->constant = constructor_constant;
  p->simple = constructor_simple;
  p->nonconst = constructor_nonconst;
  p->erroneous = constructor_erroneous;
  p->pending_elts = constructor_pending_elts;
  p->ژوروالی = constructor_ژوروالی;
  p->replacement_ارزښت.ارزښت = NULL_ونه;
  p->replacement_ارزښت.original_کوډ = ERROR_MARK;
  p->replacement_ارزښت.original_type = عدم;
  p->implicit = implicit;
  p->outer = 0;
  p->incremental = constructor_incremental;
  p->designated = constructor_designated;
  p->zero_padding_بټونه = constructor_zero_padding_بټونه;
  p->braced_scalar = constructor_braced_scalar;
  p->designator_ژوروالی = designator_ژوروالی;
  p->بل = constructor_ډېری;
  p->range_ډېری = 0;
  constructor_ډېری = p;

  constructor_constant = 1;
  constructor_simple = 1;
  constructor_nonconst = 0;
  constructor_ژوروالی = SPELLING_ژوروالی ();
  constructor_elements = عدم;
  constructor_incremental = 1;
  /* If the upper initializer is designated, then mark this as
     designated too to prevent bogus warnings.  */
  constructor_designated = p->designated;
  /* If the upper initializer has padding bits zeroed, that includes
     all nested initializers as well.  */
  constructor_zero_padding_بټونه = p->zero_padding_بټونه;
  constructor_braced_scalar = خطأ;
  constructor_pending_elts = 0;
  إذا (!implicit)
    {
      p->range_ډېری = constructor_range_ډېری;
      constructor_range_ډېری = 0;
      designator_ژوروالی = 0;
      designator_erroneous = 0;
    }

  /* Don't die if an entire brace-pair level is superfluous
     in the containing level.  */
  إذا (constructor_type == NULL_ونه)
    ;
  وإلا إذا (ریکارډ_OR_UNION_TYPE_P (constructor_type))
    {
      /* Don't die if there are extra init elts at the end.  */
      إذا (constructor_fields == NULL_ونه)
	constructor_type = NULL_ونه;
      وإلا
	{
	  constructor_type = ونه_TYPE (constructor_fields);
	  ټېل_member_name (constructor_fields);
	  constructor_ژوروالی++;
	}
    }
  وإلا إذا (ونه_کوډ (constructor_type) == ARRAY_TYPE)
    {
      constructor_type = ونه_TYPE (constructor_type);
      ټېل_array_bounds (ونه_منزل_uhwi (constructor_شاخص));
      constructor_ژوروالی++;
    }

  إذا (constructor_type == NULL_ونه)
    {
      error_init (loc, "extra brace group at end of initializer");
      constructor_fields = NULL_ونه;
      constructor_unfilled_fields = NULL_ونه;
      أرجع;
    }

  إذا (ارزښت && ونه_کوډ (ارزښت) == CONSTRUCTOR)
    {
      constructor_constant = ونه_CONSTANT (ارزښت);
      constructor_simple = ونه_STATIC (ارزښت);
      constructor_nonconst = CONSTRUCTOR_NON_CONST (ارزښت);
      constructor_elements = CONSTRUCTOR_ELTS (ارزښت);
      constructor_zero_padding_بټونه |= CONSTRUCTOR_ZERO_PADDING_بټونه (ارزښت);
      إذا (!vec_خوندي_is_تشه (constructor_elements)
	  && (ونه_کوډ (constructor_type) == ریکارډ_TYPE
	      || ونه_کوډ (constructor_type) == ARRAY_TYPE))
	سېټ_nonincremental_init (braced_init_obstack);
    }

  إذا (implicit == 1)
    {
      وموندل_missing_braces = 1;
      إذا (initializer_ډېری->missing_brace_richloc)
	initializer_ډېری->missing_brace_richloc->جمع_کړه_fixit_ورننباسه_before
	  (loc, "{");
    }

  إذا (ریکارډ_OR_UNION_TYPE_P (constructor_type))
    {
      constructor_fields = TYPE_FIELDS (constructor_type);
      /* Skip any nameless bit fields at the beginning.  */
      طالما (constructor_fields != NULL_ونه
	     && DECL_UNNAMED_بټ_ډګر (constructor_fields))
	constructor_fields = DECL_CHAIN (constructor_fields);

      constructor_unfilled_fields = constructor_fields;
      constructor_بټ_شاخص = bitsize_zero_غوټه;
    }
  وإلا إذا (gnu_ویکټور_type_p (constructor_type))
    {
      /* Vectors are like simple fixed-size arrays.  */
      constructor_max_شاخص =
	bitsize_int (TYPE_ویکټور_SUBPARTS (constructor_type) - 1);
      constructor_شاخص = bitsize_int (0);
      constructor_unfilled_شاخص = constructor_شاخص;
    }
  وإلا إذا (ونه_کوډ (constructor_type) == ARRAY_TYPE)
    {
      إذا (TYPE_DOMAIN (constructor_type))
	{
	  constructor_max_شاخص
	    = TYPE_MAX_ارزښت (TYPE_DOMAIN (constructor_type));

	  /* Detect non-empty initializations of zero-length arrays.  */
	  إذا (constructor_max_شاخص == NULL_ونه
	      && TYPE_اندازه (constructor_type))
	    constructor_max_شاخص = integer_minus_one_غوټه;

	  /* constructor_max_index needs to be an INTEGER_CST.  Attempts
	     to initialize VLAs will cause a proper error; avoid tree
	     checking errors as well by setting a safe value.  */
	  إذا (constructor_max_شاخص
	      && ونه_کوډ (constructor_max_شاخص) != INTEGER_CST)
	    constructor_max_شاخص = integer_minus_one_غوټه;

	  constructor_شاخص
	    = convert (bitsizetype,
		       TYPE_MIN_ارزښت (TYPE_DOMAIN (constructor_type)));
	}
      وإلا
	constructor_شاخص = bitsize_zero_غوټه;

      constructor_unfilled_شاخص = constructor_شاخص;
      إذا (ارزښت && ونه_کوډ (ارزښت) == STRING_CST)
	{
	  /* We need to split the char/wchar array into individual
	     characters, so that we don't have to special case it
	     everywhere.  */
	  سېټ_nonincremental_init_from_string (ارزښت, braced_init_obstack);
	}
    }
  وإلا
    {
      إذا (constructor_type != error_mark_غوټه)
	{
	  إذا (p->braced_scalar)
	    permerror_init (ننوت_location, 0,
			    "braces around scalar initializer");
	  وإلا
	    warning_init (ننوت_location, 0,
			  "braces around scalar initializer");
	  constructor_braced_scalar = ریښتیا;
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

بنية c_بیان
راوباسه_init_level (location_t loc, صحيح implicit,
		بنية obstack *braced_init_obstack,
		location_t ورننباسه_before)
{
  بنية constructor_ډېری *p;
  بنية c_بیان ret;
  ret.ارزښت = NULL_ونه;
  ret.original_کوډ = ERROR_MARK;
  ret.original_type = عدم;
  ret.m_decimal = 0;

  إذا (implicit == 0)
    {
      /* When we come to an explicit close brace,
	 pop any inner levels that didn't have explicit braces.  */
      طالما (constructor_ډېری->implicit)
	process_init_element (ننوت_location,
			      راوباسه_init_level (loc, 1, braced_init_obstack,
					      ورننباسه_before),
			      ریښتیا, braced_init_obstack);
      gcc_assert (!constructor_range_ډېری);
    }
  وإلا
    إذا (initializer_ډېری->missing_brace_richloc)
      initializer_ډېری->missing_brace_richloc->جمع_کړه_fixit_ورننباسه_before
	(ورننباسه_before, "}");

  /* Now output all pending elements.  */
  constructor_incremental = 1;
  output_pending_init_elements (1, braced_init_obstack);

  p = constructor_ډېری;

  /* Error for initializing a flexible array member.  */
  إذا (constructor_type && constructor_fields
      && flexible_array_member_type_p (constructor_type))
    {
      /* Silently discard empty initializations.  The parser will
	 already have pedwarned for empty brackets for C17 and earlier.  */
      إذا (integer_zerop (constructor_unfilled_شاخص))
	constructor_type = NULL_ونه;
      إذا (constructor_type || flag_isoc23)
	{
	  gcc_assert (!constructor_type || !TYPE_اندازه (constructor_type));

	  إذا (constructor_ژوروالی <= 2)
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
	      && DECL_CHAIN (constructor_fields) != NULL_ونه
	      && (!p->type || ونه_کوډ (p->type) != UNION_TYPE))
	    constructor_type = NULL_ونه;
	}
    }

  بدل (vec_خوندي_اوږدتیا (constructor_elements))
    {
    حالة 0:
      /* Initialization with { } counts as zeroinit.  */
      constructor_zeroinit = 1;
      اكسر;
    حالة 1:
      /* This might be zeroinit as well.  */
      إذا (integer_zerop ((*constructor_elements)[0].ارزښت))
	constructor_zeroinit = 1;
      اكسر;
    افتراضي:
      /* If the constructor has more than one element, it can't be { 0 }.  */
      constructor_zeroinit = 0;
      اكسر;
    }

  /* Warn when some structs are initialized with direct aggregation.  */
  إذا (!implicit && وموندل_missing_braces && warn_missing_braces
      && !constructor_zeroinit)
    {
      gcc_assert (initializer_ډېری->missing_brace_richloc);
      warning_at (initializer_ډېری->missing_brace_richloc,
		  OPT_Wmissing_braces,
		  "missing braces around initializer");
    }

  /* Warn when some struct elements are implicitly initialized to zero.  */
  إذا (warn_missing_ډګر_initializers
      && constructor_type
      && ونه_کوډ (constructor_type) == ریکارډ_TYPE
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
	    إذا (warning_at (ننوت_location, OPT_Wmissing_ډګر_initializers,
			    "missing initializer for field %qD of %qT",
			    constructor_unfilled_fields,
			    constructor_type))
	      inform (DECL_سرچینه_LOCATION (constructor_unfilled_fields),
		      "%qD declared here", constructor_unfilled_fields);
	  }
    }

  /* Pad out the end of the structure.  */
  إذا (p->replacement_ارزښت.ارزښت)
    /* If this closes a superfluous brace pair,
       just pass out the element between them.  */
    ret = p->replacement_ارزښت;
  وإلا إذا (constructor_type == NULL_ونه)
    ;
  وإلا إذا (!ریکارډ_OR_UNION_TYPE_P (constructor_type)
	   && ونه_کوډ (constructor_type) != ARRAY_TYPE
	   && !gnu_ویکټور_type_p (constructor_type))
    {
      /* A nonincremental scalar initializer--just return
	 the element, after verifying there is just one.
         Empty scalar initializers are supported in C23.  */
      إذا (vec_خوندي_is_تشه (constructor_elements))
	{
	  إذا (constructor_erroneous || constructor_type == error_mark_غوټه)
	    ret.ارزښت = error_mark_غوټه;
	  وإلا إذا (ونه_کوډ (constructor_type) == FUNCTION_TYPE)
	    {
	      error_init (loc, "invalid initializer");
	      ret.ارزښت = error_mark_غوټه;
	    }
	  وإلا إذا (ونه_کوډ (constructor_type) == اشاره_ګر_TYPE)
	    /* Ensure this is a null pointer constant in the case of a
	       'constexpr' object initialized with {}.  */
	    ret.ارزښت = build_zero_cst (ptr_type_غوټه);
	  وإلا
	    ret.ارزښت = build_zero_cst (constructor_type);
	}
      وإلا إذا (vec_خوندي_اوږدتیا (constructor_elements) != 1)
	{
	  error_init (loc, "extra elements in scalar initializer");
	  ret.ارزښت = (*constructor_elements)[0].ارزښت;
	}
      وإلا
	ret.ارزښت = (*constructor_elements)[0].ارزښت;
    }
  وإلا
    {
      إذا (constructor_erroneous)
	ret.ارزښت = error_mark_غوټه;
      وإلا
	{
	  ret.ارزښت = build_constructor (constructor_type,
					 constructor_elements);
	  إذا (constructor_constant)
	    ونه_CONSTANT (ret.ارزښت) = 1;
	  إذا (constructor_constant && constructor_simple)
	    ونه_STATIC (ret.ارزښت) = 1;
	  إذا (constructor_nonconst)
	    CONSTRUCTOR_NON_CONST (ret.ارزښت) = 1;
	  إذا (constructor_zero_padding_بټونه)
	    CONSTRUCTOR_ZERO_PADDING_بټونه (ret.ارزښت) = 1;
	}
    }

  إذا (ret.ارزښت && ونه_کوډ (ret.ارزښت) != CONSTRUCTOR)
    {
      إذا (constructor_nonconst)
	ret.original_کوډ = C_MAYBE_CONST_بیان;
      وإلا إذا (ret.original_کوډ == C_MAYBE_CONST_بیان)
	ret.original_کوډ = ERROR_MARK;
    }

  constructor_type = p->type;
  constructor_fields = p->fields;
  constructor_شاخص = p->شاخص;
  constructor_max_شاخص = p->max_شاخص;
  constructor_unfilled_شاخص = p->unfilled_شاخص;
  constructor_unfilled_fields = p->unfilled_fields;
  constructor_بټ_شاخص = p->بټ_شاخص;
  constructor_elements = p->elements;
  constructor_constant = p->constant;
  constructor_simple = p->simple;
  constructor_nonconst = p->nonconst;
  constructor_erroneous = p->erroneous;
  constructor_incremental = p->incremental;
  constructor_designated = p->designated;
  constructor_zero_padding_بټونه = p->zero_padding_بټونه;
  constructor_braced_scalar = p->braced_scalar;
  designator_ژوروالی = p->designator_ژوروالی;
  constructor_pending_elts = p->pending_elts;
  constructor_ژوروالی = p->ژوروالی;
  إذا (!p->implicit)
    constructor_range_ډېری = p->range_ډېری;
  RESTORE_SPELLING_ژوروالی (constructor_ژوروالی);

  constructor_ډېری = p->بل;
  XDELETE (p);

  إذا (ret.ارزښت == NULL_ونه && constructor_ډېری == 0)
    ret.ارزښت = error_mark_غوټه;
  أرجع ret;
}

/* Common handling for both array range and field name designators.
   ARRAY argument is nonzero for array ranges.  Returns false for success.  */

ساكن منطقي
سېټ_designator (location_t loc, منطقي array,
		بنية obstack *braced_init_obstack)
{
  ونه subtype;
  تعداد ونه_کوډ_2 subcode;

  /* Don't die if an entire brace-pair level is superfluous
     in the containing level, or for an erroneous type.  */
  إذا (constructor_type == NULL_ونه || constructor_type == error_mark_غوټه)
    أرجع ریښتیا;

  /* If there were errors in this designator list already, bail out
     silently.  */
  إذا (designator_erroneous)
    أرجع ریښتیا;

  /* Likewise for an initializer for a variable-size type.  Those are
     diagnosed in the parser, except for empty initializer braces.  */
  إذا (COMPLETE_TYPE_P (constructor_type)
      && ونه_کوډ (TYPE_اندازه (constructor_type)) != INTEGER_CST)
    أرجع ریښتیا;

  إذا (!designator_ژوروالی)
    {
      gcc_assert (!constructor_range_ډېری);

      /* Designator list starts at the level of closest explicit
	 braces.  */
      طالما (constructor_ډېری->implicit)
	process_init_element (ننوت_location,
			      راوباسه_init_level (loc, 1, braced_init_obstack,
					      وروستی_init_list_comma),
			      ریښتیا, braced_init_obstack);
      constructor_designated = 1;
      أرجع خطأ;
    }

  بدل (ونه_کوډ (constructor_type))
    {
    حالة  ریکارډ_TYPE:
    حالة  UNION_TYPE:
      subtype = ونه_TYPE (constructor_fields);
      إذا (subtype != error_mark_غوټه)
	subtype = TYPE_MAIN_VARIANT (subtype);
      اكسر;
    حالة ARRAY_TYPE:
      subtype = TYPE_MAIN_VARIANT (ونه_TYPE (constructor_type));
      اكسر;
    افتراضي:
      gcc_unreachable ();
    }

  subcode = ونه_کوډ (subtype);
  إذا (array && subcode != ARRAY_TYPE)
    {
      error_init (loc, "array index in non-array initializer");
      أرجع ریښتیا;
    }
  وإلا إذا (!array && subcode != ریکارډ_TYPE && subcode != UNION_TYPE)
    {
      error_init (loc, "field name not in record or union initializer");
      أرجع ریښتیا;
    }

  constructor_designated = 1;
  پای_implicit_inits (loc, braced_init_obstack);
  ټېل_init_level (loc, 2, braced_init_obstack);
  أرجع خطأ;
}

/* If there are range designators in designator list, push a new designator
   to constructor_range_stack.  RANGE_END is end of such stack range or
   NULL_TREE if there is no range designator at this level.  */

ساكن فراغ
ټېل_range_ډېری (ونه range_پای_ټکی, بنية obstack * braced_init_obstack)
{
  بنية constructor_range_ډېری *p;

  p = (بنية constructor_range_ډېری *)
    obstack_alloc (braced_init_obstack,
		   حجم (بنية constructor_range_ډېری));
  p->prev = constructor_range_ډېری;
  p->بل = 0;
  p->fields = constructor_fields;
  p->range_پیل = constructor_شاخص;
  p->شاخص = constructor_شاخص;
  p->ډېری = constructor_ډېری;
  p->range_پای_ټکی = range_پای_ټکی;
  إذا (constructor_range_ډېری)
    constructor_range_ډېری->بل = p;
  constructor_range_ډېری = p;
}

/* Within an array initializer, specify the next index to be initialized.
   FIRST is that index.  If LAST is nonzero, then initialize a range
   of indices, running from FIRST through LAST.  */

فراغ
سېټ_init_شاخص (location_t loc, ونه لومړی, ونه وروستی,
		بنية obstack *braced_init_obstack)
{
  إذا (سېټ_designator (loc, ریښتیا, braced_init_obstack))
    أرجع;

  designator_erroneous = 1;

  إذا (!INTEGRAL_TYPE_P (ونه_TYPE (لومړی))
      || (وروستی && !INTEGRAL_TYPE_P (ونه_TYPE (وروستی))))
    {
      error_init (loc, "array index in initializer not of integer type");
      أرجع;
    }

  إذا (ونه_کوډ (لومړی) != INTEGER_CST)
    {
      لومړی = c_fully_fold (لومړی, خطأ, عدم);
      إذا (ونه_کوډ (لومړی) == INTEGER_CST)
	pedwarn_init (loc, OPT_Wpedantic,
		      "array index in initializer is not "
		      "an integer constant expression");
    }

  إذا (وروستی && ونه_کوډ (وروستی) != INTEGER_CST)
    {
      وروستی = c_fully_fold (وروستی, خطأ, عدم);
      إذا (ونه_کوډ (وروستی) == INTEGER_CST)
	pedwarn_init (loc, OPT_Wpedantic,
		      "array index in initializer is not "
		      "an integer constant expression");
    }

  إذا (ونه_کوډ (لومړی) != INTEGER_CST)
    error_init (loc, "nonconstant array index in initializer");
  وإلا إذا (وروستی != NULL_ونه && ونه_کوډ (وروستی) != INTEGER_CST)
    error_init (loc, "nonconstant array index in initializer");
  وإلا إذا (ونه_کوډ (constructor_type) != ARRAY_TYPE)
    error_init (loc, "array index in non-array initializer");
  وإلا إذا (ونه_int_cst_sgn (لومړی) == -1)
    error_init (loc, "array index in initializer exceeds array bounds");
  وإلا إذا (constructor_max_شاخص
	   && ونه_int_cst_lt (constructor_max_شاخص, لومړی))
    error_init (loc, "array index in initializer exceeds array bounds");
  وإلا
    {
      constant_افاده_warning (لومړی);
      إذا (وروستی)
	constant_افاده_warning (وروستی);
      constructor_شاخص = convert (bitsizetype, لومړی);
      إذا (ونه_int_cst_lt (constructor_شاخص, لومړی))
	{
	  constructor_شاخص = copy_غوټه (constructor_شاخص);
	  ونه_ډکېدنه (constructor_شاخص) = 1;
	}

      إذا (وروستی)
	{
	  إذا (ونه_int_cst_equal (لومړی, وروستی))
	    وروستی = NULL_ونه;
	  وإلا إذا (ونه_int_cst_lt (وروستی, لومړی))
	    {
	      error_init (loc, "empty index range in initializer");
	      وروستی = NULL_ونه;
	    }
	  وإلا
	    {
	      وروستی = convert (bitsizetype, وروستی);
	      إذا (constructor_max_شاخص != NULL_ونه
		  && ونه_int_cst_lt (constructor_max_شاخص, وروستی))
		{
		  error_init (loc, "array index range in initializer exceeds "
			      "array bounds");
		  وروستی = NULL_ونه;
		}
	    }
	}

      designator_ژوروالی++;
      designator_erroneous = 0;
      إذا (constructor_range_ډېری || وروستی)
	ټېل_range_ډېری (وروستی, braced_init_obstack);
    }
}

/* Within a struct initializer, specify the next field to be initialized.  */

فراغ
سېټ_init_label (location_t loc, ونه fieldname, location_t fieldname_loc,
		بنية obstack *braced_init_obstack)
{
  ونه ډګر_2;

  إذا (سېټ_designator (loc, خطأ, braced_init_obstack))
    أرجع;

  designator_erroneous = 1;

  إذا (!ریکارډ_OR_UNION_TYPE_P (constructor_type))
    {
      error_init (loc, "field name not in record or union initializer");
      أرجع;
    }

  ډګر_2 = lookup_ډګر (constructor_type, fieldname);

  إذا (ډګر_2 == NULL_ونه)
    {
      ونه guessed_id = lookup_ډګر_fuzzy (constructor_type, fieldname);
      إذا (guessed_id)
	{
	  gcc_rich_location rich_loc (fieldname_loc);
	  rich_loc.جمع_کړه_fixit_misspelled_id (fieldname_loc, guessed_id);
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
	constructor_fields = ونه_ارزښت (ډګر_2);
	designator_ژوروالی++;
	designator_erroneous = 0;
	إذا (constructor_range_ډېری)
	  ټېل_range_ډېری (NULL_ونه, braced_init_obstack);
	ډګر_2 = ونه_CHAIN (ډګر_2);
	إذا (ډګر_2)
	  {
	    إذا (سېټ_designator (loc, خطأ, braced_init_obstack))
	      أرجع;
	  }
      }
    طالما (ډګر_2 != NULL_ونه);
}

/* Helper function for add_pending_init.  Find inorder successor of P
   in AVL tree.  */
ساكن بنية init_غوټه *
init_غوټه_successor (بنية init_غوټه *p)
{
  بنية init_غوټه *r;
  إذا (p->ښی)
    {
      r = p->ښی;
      طالما (r->کیڼ)
	r = r->کیڼ;
      أرجع r;
    }
  r = p->پلار;
  طالما (r && p == r->ښی)
    {
      p = r;
      r = r->پلار;
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
جمع_کړه_pending_init (location_t loc, ونه purpose, ونه ارزښت, ونه origtype,
		  منطقي implicit, بنية obstack *braced_init_obstack)
{
  بنية init_غوټه *p, **q, *r;

  q = &constructor_pending_elts;
  p = 0;

  إذا (ونه_کوډ (constructor_type) == ARRAY_TYPE)
    {
      طالما (*q != 0)
	{
	  p = *q;
	  إذا (ونه_int_cst_lt (purpose, p->purpose))
	    q = &p->کیڼ;
	  وإلا إذا (ونه_int_cst_lt (p->purpose, purpose))
	    {
	      إذا (ونه_کوډ (p->ارزښت) != RAW_معلومات_CST
		  || (p->ښی
		      && ونه_int_cst_le (p->ښی->purpose, purpose)))
		q = &p->ښی;
	      وإلا
		{
		  widest_int pp = wi::منزل_widest (p->purpose);
		  widest_int pw = wi::منزل_widest (purpose);
		  إذا (pp + RAW_معلومات_اوږدتیا (p->ارزښت) <= pw)
		    q = &p->ښی;
		  وإلا
		    {
		      /* Override which should split the old RAW_DATA_CST
			 into 2 or 3 pieces.  */
		      إذا (!implicit && warn_override_init)
			warning_init (loc, OPT_Woverride_init,
				      "initialized field overwritten");
		      بینښه HOST_WIDE_INT پیل = (pw - pp).منزل_uhwi ();
		      بینښه HOST_WIDE_INT len = 1;
		      إذا (ونه_کوډ (ارزښت) == RAW_معلومات_CST)
			len = RAW_معلومات_اوږدتیا (ارزښت);
		      بینښه HOST_WIDE_INT پای_ټکی = 0;
		      بینښه plen = RAW_معلومات_اوږدتیا (p->ارزښت);
		      gcc_checking_assert (پیل < plen && پیل);
		      إذا (plen - پیل > len)
			پای_ټکی = plen - پیل - len;
		      ونه v = p->ارزښت;
		      ونه origtype = p->origtype;
		      إذا (پیل == 1)
			p->ارزښت = build_int_cst (ونه_TYPE (v),
						  RAW_معلومات_UCHAR_ELT (v, 0));
		      وإلا
			{
			  p->ارزښت = v;
			  إذا (پای_ټکی > 1)
			    v = copy_غوټه (v);
			  RAW_معلومات_اوږدتیا (p->ارزښت) = پیل;
			}
		      إذا (پای_ټکی)
			{
			  ونه epurpose
			    = اندازه_binop (PLUS_بیان, purpose,
					  bitsize_int (len));
			  إذا (پای_ټکی > 1)
			    {
			      RAW_معلومات_اوږدتیا (v) -= plen - پای_ټکی;
			      RAW_معلومات_اشاره_ګر (v) += plen - پای_ټکی;
			    }
			  وإلا
			    v = build_int_cst (ونه_TYPE (v),
					       RAW_معلومات_UCHAR_ELT (v, plen
								      - پای_ټکی));
			  جمع_کړه_pending_init (loc, epurpose, v, origtype,
					    implicit, braced_init_obstack);
			}
		      q = &constructor_pending_elts;
		      استمر;
		    }
		}
	    }
	  وإلا
	    {
	      إذا (ونه_کوډ (p->ارزښت) == RAW_معلومات_CST
		  && (RAW_معلومات_اوږدتیا (p->ارزښت)
		      > (ونه_کوډ (ارزښت) == RAW_معلومات_CST
			 ? RAW_معلومات_اوږدتیا (ارزښت) : 1)))
		{
		  /* Override which should split the old RAW_DATA_CST
		     into 2 pieces.  */
		  إذا (!implicit && warn_override_init)
		    warning_init (loc, OPT_Woverride_init,
				  "initialized field overwritten");
		  بینښه HOST_WIDE_INT len = 1;
		  إذا (ونه_کوډ (ارزښت) == RAW_معلومات_CST)
		    len = RAW_معلومات_اوږدتیا (ارزښت);
		  إذا ((بینښه) RAW_معلومات_اوږدتیا (p->ارزښت) > len + 1)
		    {
		      RAW_معلومات_اوږدتیا (p->ارزښت) -= len;
		      RAW_معلومات_اشاره_ګر (p->ارزښت) += len;
		    }
		  وإلا
		    {
		      بینښه صحيح l = RAW_معلومات_اوږدتیا (p->ارزښت) - 1;
		      p->ارزښت
			= build_int_cst (ونه_TYPE (p->ارزښت),
					 RAW_معلومات_UCHAR_ELT (p->ارزښت, l));
		    }
		  p->purpose = اندازه_binop (PLUS_بیان, p->purpose,
					   bitsize_int (len));
		  استمر;
		}
	      إذا (ونه_کوډ (ارزښت) == RAW_معلومات_CST)
		{
		handle_raw_معلومات:
		  /* RAW_DATA_CST value might overlap various further
		     prior initval entries.  Find out how many.  */
		  بینښه cnt = 0;
		  widest_int w
		    = wi::منزل_widest (purpose) + RAW_معلومات_اوږدتیا (ارزښت);
		  بنية init_غوټه *r = p, *وروستی = عدم;
		  منطقي override_init = warn_override_init;
		  طالما ((r = init_غوټه_successor (r))
			 && wi::منزل_widest (r->purpose) < w)
		    {
		      ++cnt;
		      إذا (ونه_SIDE_EFFECTS (r->ارزښت))
			warning_init (loc, OPT_Woverride_init_side_effects,
				      "initialized field with side-effects "
				      "overwritten");
		      وإلا إذا (override_init)
			{
			  warning_init (loc, OPT_Woverride_init,
					"initialized field overwritten");
			  override_init = خطأ;
			}
		      وروستی = r;
		    }
		  إذا (cnt)
		    {
		      إذا (ونه_کوډ (وروستی->ارزښت) == RAW_معلومات_CST
			  && (wi::منزل_widest (وروستی->purpose)
			      + RAW_معلومات_اوږدتیا (وروستی->ارزښت) > w))
			{
			  /* The last overlapping prior initval overlaps
			     only partially.  Shrink it and decrease cnt.  */
			  بینښه صحيح l = (wi::منزل_widest (وروستی->purpose)
					    + RAW_معلومات_اوږدتیا (وروستی->ارزښت)
					    - w).منزل_uhwi ();
			  --cnt;
			  RAW_معلومات_اوږدتیا (وروستی->ارزښت) -= l;
			  RAW_معلومات_اشاره_ګر (وروستی->ارزښت) += l;
			  إذا (RAW_معلومات_اوږدتیا (وروستی->ارزښت) == 1)
			    وروستی->ارزښت
			      = build_int_cst (ونه_TYPE (وروستی->ارزښت),
					       RAW_معلومات_UCHAR_ELT (وروستی->ارزښت,
								   0));
			  وروستی->purpose
			    = اندازه_binop (PLUS_بیان, وروستی->purpose,
					  bitsize_int (l));
			}
		      /* Instead of deleting cnt nodes from the AVL tree
			 and rebalancing, peel of last cnt bytes from the
			 RAW_DATA_CST.  Overriding thousands of previously
			 initialized array elements with #embed needs to work,
			 but doesn't need to be super efficient.  */
		      gcc_checking_assert ((بینښه) RAW_معلومات_اوږدتیا (ارزښت)
					   > cnt);
		      RAW_معلومات_اوږدتیا (ارزښت) -= cnt;
		      ثابت بینښه حرف *s
			= &RAW_معلومات_UCHAR_ELT (ارزښت, RAW_معلومات_اوږدتیا (ارزښت));
		      بینښه صحيح o = RAW_معلومات_اوږدتیا (ارزښت);
		      لكل (r = p; cnt--; ++o, ++s)
			{
			  r = init_غوټه_successor (r);
			  r->purpose = اندازه_binop (PLUS_بیان, purpose,
						   bitsize_int (o));
			  r->ارزښت = build_int_cst (ونه_TYPE (ارزښت), *s);
			  r->origtype = origtype;
			}
		      إذا (RAW_معلومات_اوږدتیا (ارزښت) == 1)
			ارزښت = build_int_cst (ونه_TYPE (ارزښت),
					       RAW_معلومات_UCHAR_ELT (ارزښت, 0));
		    }
		}
	      إذا (!implicit)
		{
		  إذا (ونه_SIDE_EFFECTS (p->ارزښت))
		    warning_init (loc, OPT_Woverride_init_side_effects,
				  "initialized field with side-effects "
				  "overwritten");
		  وإلا إذا (warn_override_init)
		    warning_init (loc, OPT_Woverride_init,
				  "initialized field overwritten");
		}
	      p->ارزښت = ارزښت;
	      p->origtype = origtype;
	      أرجع;
	    }
	}
      إذا (ونه_کوډ (ارزښت) == RAW_معلومات_CST && p)
	{
	  بنية init_غوټه *r;
	  إذا (q == &p->کیڼ)
	    r = p;
	  وإلا
	    r = init_غوټه_successor (p);
	  إذا (r && wi::منزل_widest (r->purpose) < (wi::منزل_widest (purpose)
						 + RAW_معلومات_اوږدتیا (ارزښت)))
	    {
	      /* Overlap with at least one prior initval in the range but
		 not at the start.  */
	      p = r;
	      p->purpose = purpose;
	      اذهب handle_raw_معلومات;
	    }
	}
    }
  وإلا
    {
      ونه bitpos;

      bitpos = بټ_position (purpose);
      طالما (*q != عدم)
	{
	  p = *q;
	  إذا (ونه_int_cst_lt (bitpos, بټ_position (p->purpose)))
	    q = &p->کیڼ;
	  وإلا إذا (p->purpose != purpose)
	    q = &p->ښی;
	  وإلا
	    {
	      إذا (!implicit)
		{
		  إذا (ونه_SIDE_EFFECTS (p->ارزښت))
		    warning_init (loc, OPT_Woverride_init_side_effects,
				  "initialized field with side-effects "
				  "overwritten");
		  وإلا إذا (warn_override_init)
		    warning_init (loc, OPT_Woverride_init,
				  "initialized field overwritten");
		}
	      p->ارزښت = ارزښت;
	      p->origtype = origtype;
	      أرجع;
	    }
	}
    }

  r = (بنية init_غوټه *) obstack_alloc (braced_init_obstack,
					  حجم (بنية init_غوټه));
  r->purpose = purpose;
  r->ارزښت = ارزښت;
  r->origtype = origtype;

  *q = r;
  r->پلار = p;
  r->کیڼ = 0;
  r->ښی = 0;
  r->balance = 0;

  طالما (p)
    {
      بنية init_غوټه *s;

      إذا (r == p->کیڼ)
	{
	  إذا (p->balance == 0)
	    p->balance = -1;
	  وإلا إذا (p->balance < 0)
	    {
	      إذا (r->balance < 0)
		{
		  /* L rotation.  */
		  p->کیڼ = r->ښی;
		  إذا (p->کیڼ)
		    p->کیڼ->پلار = p;
		  r->ښی = p;

		  p->balance = 0;
		  r->balance = 0;

		  s = p->پلار;
		  p->پلار = r;
		  r->پلار = s;
		  إذا (s)
		    {
		      إذا (s->کیڼ == p)
			s->کیڼ = r;
		      وإلا
			s->ښی = r;
		    }
		  وإلا
		    constructor_pending_elts = r;
		}
	      وإلا
		{
		  /* LR rotation.  */
		  بنية init_غوټه *t = r->ښی;

		  r->ښی = t->کیڼ;
		  إذا (r->ښی)
		    r->ښی->پلار = r;
		  t->کیڼ = r;

		  p->کیڼ = t->ښی;
		  إذا (p->کیڼ)
		    p->کیڼ->پلار = p;
		  t->ښی = p;

		  p->balance = t->balance < 0;
		  r->balance = -(t->balance > 0);
		  t->balance = 0;

		  s = p->پلار;
		  p->پلار = t;
		  r->پلار = t;
		  t->پلار = s;
		  إذا (s)
		    {
		      إذا (s->کیڼ == p)
			s->کیڼ = t;
		      وإلا
			s->ښی = t;
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
		  p->ښی = r->کیڼ;
		  إذا (p->ښی)
		    p->ښی->پلار = p;
		  r->کیڼ = p;

		  p->balance = 0;
		  r->balance = 0;

		  s = p->پلار;
		  p->پلار = r;
		  r->پلار = s;
		  إذا (s)
		    {
		      إذا (s->کیڼ == p)
			s->کیڼ = r;
		      وإلا
			s->ښی = r;
		    }
		  وإلا
		    constructor_pending_elts = r;
		}
	      وإلا /* r->balance == -1 */
		{
		  /* RL rotation */
		  بنية init_غوټه *t = r->کیڼ;

		  r->کیڼ = t->ښی;
		  إذا (r->کیڼ)
		    r->کیڼ->پلار = r;
		  t->ښی = r;

		  p->ښی = t->کیڼ;
		  إذا (p->ښی)
		    p->ښی->پلار = p;
		  t->کیڼ = p;

		  r->balance = (t->balance < 0);
		  p->balance = -(t->balance > 0);
		  t->balance = 0;

		  s = p->پلار;
		  p->پلار = t;
		  r->پلار = t;
		  t->پلار = s;
		  إذا (s)
		    {
		      إذا (s->کیڼ == p)
			s->کیڼ = t;
		      وإلا
			s->ښی = t;
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
      p = p->پلار;
    }
}

/* Build AVL tree from a sorted chain.  */

ساكن فراغ
سېټ_nonincremental_init (بنية obstack * braced_init_obstack)
{
  بینښه HOST_WIDE_INT ix;
  ونه شاخص, ارزښت;

  إذا (ونه_کوډ (constructor_type) != ریکارډ_TYPE
      && ونه_کوډ (constructor_type) != ARRAY_TYPE)
    أرجع;

  FOR_EACH_CONSTRUCTOR_ELT (constructor_elements, ix, شاخص, ارزښت)
    جمع_کړه_pending_init (ننوت_location, شاخص, ارزښت, NULL_ونه, ریښتیا,
		      braced_init_obstack);
  constructor_elements = عدم;
  إذا (ونه_کوډ (constructor_type) == ریکارډ_TYPE)
    {
      constructor_unfilled_fields = TYPE_FIELDS (constructor_type);
      /* Skip any nameless bit fields at the beginning.  */
      طالما (constructor_unfilled_fields != NULL_ونه
	     && DECL_UNNAMED_بټ_ډګر (constructor_unfilled_fields))
	constructor_unfilled_fields = ونه_CHAIN (constructor_unfilled_fields);

    }
  وإلا إذا (ونه_کوډ (constructor_type) == ARRAY_TYPE)
    {
      إذا (TYPE_DOMAIN (constructor_type))
	constructor_unfilled_شاخص
	  = convert (bitsizetype,
		     TYPE_MIN_ارزښت (TYPE_DOMAIN (constructor_type)));
      وإلا
	constructor_unfilled_شاخص = bitsize_zero_غوټه;
    }
  constructor_incremental = 0;
}

/* Build AVL tree from a string constant.  */

ساكن فراغ
سېټ_nonincremental_init_from_string (ونه str,
				     بنية obstack * braced_init_obstack)
{
  ونه ارزښت, purpose, type;
  HOST_WIDE_INT val[2];
  ثابت حرف *p, *پای_ټکی;
  صحيح byte, wchar_بایټونه, charwidth, bitpos;

  gcc_assert (ونه_کوډ (constructor_type) == ARRAY_TYPE);

  wchar_بایټونه = TYPE_PRECISION (ونه_TYPE (ونه_TYPE (str))) / بټونه_فی_UNIT;
  charwidth = TYPE_PRECISION (char_type_غوټه);
  gcc_assert ((اندازه_t) wchar_بایټونه * charwidth
	      <= ARRAY_اندازه (val) * HOST_بټونه_فی_WIDE_INT);
  type = ونه_TYPE (constructor_type);
  p = ونه_STRING_اشاره_ګر (str);
  پای_ټکی = p + ونه_STRING_اوږدتیا (str);

  لكل (purpose = bitsize_zero_غوټه;
       p < پای_ټکی
       && !(constructor_max_شاخص
	    && ونه_int_cst_lt (constructor_max_شاخص, purpose));
       purpose = اندازه_binop (PLUS_بیان, purpose, bitsize_one_غوټه))
    {
      إذا (wchar_بایټونه == 1)
	{
	  val[0] = (بینښه حرف) *p++;
	  val[1] = 0;
	}
      وإلا
	{
	  val[1] = 0;
	  val[0] = 0;
	  لكل (byte = 0; byte < wchar_بایټونه; byte++)
	    {
	      إذا (بایټونه_BIG_ENDIAN)
		bitpos = (wchar_بایټونه - byte - 1) * charwidth;
	      وإلا
		bitpos = byte * charwidth;
	      val[bitpos / HOST_بټونه_فی_WIDE_INT]
		|= ((بینښه HOST_WIDE_INT) ((بینښه حرف) *p++))
		   << (bitpos % HOST_بټونه_فی_WIDE_INT);
	    }
	}

      إذا (!TYPE_UNSIGNED (type))
	{
	  bitpos = ((wchar_بایټونه - 1) * charwidth) + HOST_بټونه_فی_CHAR;
	  إذا (bitpos < HOST_بټونه_فی_WIDE_INT)
	    {
	      إذا (val[0] & (HOST_WIDE_INT_1 << (bitpos - 1)))
		{
		  val[0] |= HOST_WIDE_INT_M1U << bitpos;
		  val[1] = -1;
		}
	    }
	  وإلا إذا (bitpos == HOST_بټونه_فی_WIDE_INT)
	    {
	      إذا (val[0] < 0)
		val[1] = -1;
	    }
	  وإلا إذا (val[1] & (HOST_WIDE_INT_1
			     << (bitpos - 1 - HOST_بټونه_فی_WIDE_INT)))
	    val[1] |= HOST_WIDE_INT_M1U << (bitpos - HOST_بټونه_فی_WIDE_INT);
	}

      ارزښت = wide_int_منزل_ونه (type,
				wide_int::from_array (val, 2,
						      HOST_بټونه_فی_WIDE_INT * 2));
      جمع_کړه_pending_init (ننوت_location, purpose, ارزښت, NULL_ونه, ریښتیا,
                        braced_init_obstack);
    }

  constructor_incremental = 0;
}

/* Return value of FIELD in pending initializer or NULL_TREE if the field was
   not initialized yet.  */

ساكن ونه
پیدا_کړه_init_member (ونه ډګر_2, بنية obstack * braced_init_obstack)
{
  بنية init_غوټه *p;

  إذا (ونه_کوډ (constructor_type) == ARRAY_TYPE)
    {
      إذا (constructor_incremental
	  && ونه_int_cst_lt (ډګر_2, constructor_unfilled_شاخص))
	سېټ_nonincremental_init (braced_init_obstack);

      p = constructor_pending_elts;
      طالما (p)
	{
	  إذا (ونه_int_cst_lt (ډګر_2, p->purpose))
	    p = p->کیڼ;
	  وإلا إذا (ونه_int_cst_lt (p->purpose, ډګر_2))
	    p = p->ښی;
	  وإلا
	    أرجع p->ارزښت;
	}
    }
  وإلا إذا (ونه_کوډ (constructor_type) == ریکارډ_TYPE)
    {
      ونه bitpos = بټ_position (ډګر_2);

      إذا (constructor_incremental
	  && (!constructor_unfilled_fields
	      || ونه_int_cst_lt (bitpos,
				  بټ_position (constructor_unfilled_fields))))
	سېټ_nonincremental_init (braced_init_obstack);

      p = constructor_pending_elts;
      طالما (p)
	{
	  إذا (ډګر_2 == p->purpose)
	    أرجع p->ارزښت;
	  وإلا إذا (ونه_int_cst_lt (bitpos, بټ_position (p->purpose)))
	    p = p->کیڼ;
	  وإلا
	    p = p->ښی;
	}
    }
  وإلا إذا (ونه_کوډ (constructor_type) == UNION_TYPE)
    {
      إذا (!vec_خوندي_is_تشه (constructor_elements)
	  && (constructor_elements->وروستی ().شاخص == ډګر_2))
	أرجع constructor_elements->وروستی ().ارزښت;
    }
  أرجع NULL_ونه;
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
output_init_element (location_t loc, ونه ارزښت, ونه origtype,
		     منطقي strict_string, ونه type, ونه ډګر_2, منطقي pending,
		     منطقي implicit, بنية obstack * braced_init_obstack)
{
  ونه semantic_type = NULL_ونه;
  منطقي maybe_const = ریښتیا;
  منطقي npc, int_const_بیان, arith_const_بیان;

  إذا (type == error_mark_غوټه || ارزښت == error_mark_غوټه)
    {
      constructor_erroneous = 1;
      أرجع;
    }
  إذا (ونه_کوډ (ونه_TYPE (ارزښت)) == ARRAY_TYPE
      && (ونه_کوډ (ارزښت) == STRING_CST
	  || ونه_کوډ (ارزښت) == COMPOUND_LITERAL_بیان)
      && !(ونه_کوډ (ارزښت) == STRING_CST
	   && ونه_کوډ (type) == ARRAY_TYPE
	   && INTEGRAL_TYPE_P (ونه_TYPE (type)))
      && !comptypes (TYPE_MAIN_VARIANT (ونه_TYPE (ارزښت)),
		     TYPE_MAIN_VARIANT (type)))
    ارزښت = array_منزل_اشاره_ګر_conversion (ننوت_location, ارزښت);

  إذا (ونه_کوډ (ارزښت) == COMPOUND_LITERAL_بیان
      && require_constant_ارزښت && pending)
    {
      /* As an extension, allow initializing objects with static storage
	 duration with compound literals (which are then treated just as
	 the brace enclosed list they contain).  */
      إذا (flag_isoc99)
	pedwarn_init (loc, OPT_Wpedantic, "initializer element is not "
		      "constant");
      ونه decl = COMPOUND_LITERAL_بیان_DECL (ارزښت);
      ارزښت = DECL_INITIAL (decl);
    }

  npc = null_اشاره_ګر_constant_p (ارزښت);
  int_const_بیان = (ونه_کوډ (ارزښت) == INTEGER_CST
		    && !ونه_ډکېدنه (ارزښت)
		    && INTEGRAL_TYPE_P (ونه_TYPE (ارزښت)));
  /* Not fully determined before folding.  */
  arith_const_بیان = ریښتیا;
  إذا (ونه_کوډ (ارزښت) == EXCESS_PRECISION_بیان)
    {
      semantic_type = ونه_TYPE (ارزښت);
      ارزښت = ونه_عملوند (ارزښت, 0);
    }
  ارزښت = c_fully_fold (ارزښت, require_constant_ارزښت, &maybe_const);
  /* TODO: this may not detect all cases of expressions folding to
     constants that are not arithmetic constant expressions.  */
  إذا (!maybe_const)
    arith_const_بیان = خطأ;
  وإلا إذا (!INTEGRAL_TYPE_P (ونه_TYPE (ارزښت))
	   && ونه_کوډ (ونه_TYPE (ارزښت)) != REAL_TYPE
	   && ونه_کوډ (ونه_TYPE (ارزښت)) != COMPLEX_TYPE)
    arith_const_بیان = خطأ;
  وإلا إذا (ونه_کوډ (ارزښت) != INTEGER_CST
	   && ونه_کوډ (ارزښت) != REAL_CST
	   && ونه_کوډ (ارزښت) != COMPLEX_CST
	   && ونه_کوډ (ارزښت) != RAW_معلومات_CST)
    arith_const_بیان = خطأ;
  وإلا إذا (ونه_ډکېدنه (ارزښت))
    arith_const_بیان = خطأ;

  إذا (ارزښت == error_mark_غوټه)
    constructor_erroneous = 1;
  وإلا إذا (!ونه_CONSTANT (ارزښت))
    constructor_constant = 0;
  وإلا إذا (!initializer_constant_valid_p (ارزښت,
					  ونه_TYPE (ارزښت),
					  AGGREGATE_TYPE_P (constructor_type)
					  && TYPE_سرچپه_STORAGE_ترتیب
					     (constructor_type))
	   || (ریکارډ_OR_UNION_TYPE_P (constructor_type)
	       && DECL_C_بټ_ډګر (ډګر_2)
	       && ونه_کوډ (ارزښت) != INTEGER_CST))
    constructor_simple = 0;
  إذا (!maybe_const)
    constructor_nonconst = 1;

  /* Digest the initializer and issue any errors about incompatible
     types before issuing errors about non-constant initializers.  */
  ونه new_ارزښت = ارزښت;
  إذا (semantic_type)
    new_ارزښت = build1 (EXCESS_PRECISION_بیان, semantic_type, ارزښت);
  /* In the case of braces around a scalar initializer, the result of
     this initializer processing goes through digest_init again at the
     outer level.  In the case of a constexpr initializer for a
     pointer, avoid converting a null pointer constant to something
     that is not a null pointer constant to avoid a spurious error
     from that second processing.  */
  إذا (!require_constexpr_ارزښت
      || !npc
      || ونه_کوډ (constructor_type) != اشاره_ګر_TYPE)
    new_ارزښت = digest_init (loc,
			     ریکارډ_OR_UNION_TYPE_P (constructor_type)
			     ? ډګر_2 : constructor_fields
			     ? constructor_fields : constructor_decl,
			     type, new_ارزښت, origtype, npc,
			     int_const_بیان, arith_const_بیان, strict_string,
			     require_constant_ارزښت, require_constexpr_ارزښت);
  إذا (new_ارزښت == error_mark_غوټه)
    {
      constructor_erroneous = 1;
      أرجع;
    }
  إذا (require_constant_ارزښت || require_constant_elements)
    constant_افاده_warning (new_ارزښت);

  /* Proceed to check the constness of the original initializer.  */
  إذا (!initializer_constant_valid_p (ارزښت, ونه_TYPE (ارزښت)))
    {
      إذا (require_constant_ارزښت)
	{
	  error_init (loc, "initializer element is not constant");
	  ارزښت = error_mark_غوټه;
	}
      وإلا إذا (require_constant_elements)
	pedwarn (loc, OPT_Wpedantic,
		 "initializer element is not computable at load time");
    }
  وإلا إذا (!maybe_const
	   && (require_constant_ارزښت || require_constant_elements))
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
      && ډګر_2 != NULL_ونه
      && ونه_کوډ (ډګر_2) == ډګر_DECL
      && DECL_بټ_ډګر_TYPE (ډګر_2) != NULL_ونه
      && (TYPE_MAIN_VARIANT (DECL_بټ_ډګر_TYPE (ډګر_2))
	  != TYPE_MAIN_VARIANT (type))
      && ونه_کوډ (DECL_بټ_ډګر_TYPE (ډګر_2)) == ENUMERAL_TYPE)
    {
      ونه checktype = origtype != NULL_ونه ? origtype : ونه_TYPE (ارزښت);
      إذا (checktype != error_mark_غوټه
	  && (TYPE_MAIN_VARIANT (checktype)
	      != TYPE_MAIN_VARIANT (DECL_بټ_ډګر_TYPE (ډګر_2))))
	warning_init (loc, OPT_Wc___compat,
		      "enum conversion in initialization is invalid in C++");
    }

  /* If this field is empty and does not have side effects (and is not at
     the end of structure), don't do anything other than checking the
     initializer.  */
  إذا (ډګر_2
      && (ونه_TYPE (ډګر_2) == error_mark_غوټه
	  || (COMPLETE_TYPE_P (ونه_TYPE (ډګر_2))
	      && integer_zerop (TYPE_اندازه (ونه_TYPE (ډګر_2)))
	      && !ونه_SIDE_EFFECTS (new_ارزښت)
	      && (ونه_کوډ (constructor_type) == ARRAY_TYPE
		  || DECL_CHAIN (ډګر_2)))))
    أرجع;

  /* Finally, set VALUE to the initializer value digested above.  */
  ارزښت = new_ارزښت;

  /* If this element doesn't come next in sequence,
     put it on constructor_pending_elts.  */
  إذا (ونه_کوډ (constructor_type) == ARRAY_TYPE
      && (!constructor_incremental
	  || !ونه_int_cst_equal (ډګر_2, constructor_unfilled_شاخص)
	  || (ونه_کوډ (ارزښت) == RAW_معلومات_CST
	      && constructor_pending_elts
	      && pending)))
    {
      إذا (constructor_incremental
	  && (ونه_int_cst_lt (ډګر_2, constructor_unfilled_شاخص)
	      || (ونه_کوډ (ارزښت) == RAW_معلومات_CST
		  && constructor_pending_elts
		  && pending)))
	سېټ_nonincremental_init (braced_init_obstack);

      جمع_کړه_pending_init (loc, ډګر_2, ارزښت, origtype, implicit,
			braced_init_obstack);
      أرجع;
    }
  وإلا إذا (ونه_کوډ (constructor_type) == ریکارډ_TYPE
	   && (!constructor_incremental
	       || ډګر_2 != constructor_unfilled_fields))
    {
      /* We do this for records but not for unions.  In a union,
	 no matter which field is specified, it can be initialized
	 right away since it starts at the beginning of the union.  */
      إذا (constructor_incremental)
	{
	  إذا (!constructor_unfilled_fields)
	    سېټ_nonincremental_init (braced_init_obstack);
	  وإلا
	    {
	      ونه bitpos, unfillpos;

	      bitpos = بټ_position (ډګر_2);
	      unfillpos = بټ_position (constructor_unfilled_fields);

	      إذا (ونه_int_cst_lt (bitpos, unfillpos))
		سېټ_nonincremental_init (braced_init_obstack);
	    }
	}

      جمع_کړه_pending_init (loc, ډګر_2, ارزښت, origtype, implicit,
			braced_init_obstack);
      أرجع;
    }
  وإلا إذا (ونه_کوډ (constructor_type) == UNION_TYPE
	   && !vec_خوندي_is_تشه (constructor_elements))
    {
      إذا (!implicit)
	{
	  إذا (ونه_SIDE_EFFECTS (constructor_elements->وروستی ().ارزښت))
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

  constructor_elt celt = {ډګر_2, ارزښت};
  vec_خوندي_ټېل (constructor_elements, celt);

  /* Advance the variable that indicates sequential elements output.  */
  إذا (ونه_کوډ (constructor_type) == ARRAY_TYPE)
    {
      ونه inc = bitsize_one_غوټه;
      إذا (ارزښت && ونه_کوډ (ارزښت) == RAW_معلومات_CST)
	inc = bitsize_int (RAW_معلومات_اوږدتیا (ارزښت));
      constructor_unfilled_شاخص
	= اندازه_binop_loc (ننوت_location, PLUS_بیان,
			  constructor_unfilled_شاخص, inc);
    }
  وإلا إذا (ونه_کوډ (constructor_type) == ریکارډ_TYPE)
    {
      constructor_unfilled_fields
	= DECL_CHAIN (constructor_unfilled_fields);

      /* Skip any nameless bit fields.  */
      طالما (constructor_unfilled_fields != NULL_ونه
	     && DECL_UNNAMED_بټ_ډګر (constructor_unfilled_fields))
	constructor_unfilled_fields
	  = DECL_CHAIN (constructor_unfilled_fields);
    }
  وإلا إذا (ونه_کوډ (constructor_type) == UNION_TYPE)
    constructor_unfilled_fields = NULL_ونه;

  /* Now output any pending elements which have become next.  */
  إذا (pending)
    output_pending_init_elements (0, braced_init_obstack);
}

/* For two FIELD_DECLs in the same chain, return -1 if field1
   comes before field2, 1 if field1 comes after field2 and
   0 if field1 == field2.  */

ساكن صحيح
init_ډګر_decl_cmp (ونه field1, ونه field2)
{
  إذا (field1 == field2)
    أرجع 0;

  ونه bitpos1 = بټ_position (field1);
  ونه bitpos2 = بټ_position (field2);
  إذا (ونه_int_cst_equal (bitpos1, bitpos2))
    {
      /* If one of the fields has non-zero bitsize, then that
	 field must be the last one in a sequence of zero
	 sized fields, fields after it will have bigger
	 bit_position.  */
      إذا (ونه_TYPE (field1) != error_mark_غوټه
	  && COMPLETE_TYPE_P (ونه_TYPE (field1))
	  && integer_nonzerop (ونه_TYPE (field1)))
	أرجع 1;
      إذا (ونه_TYPE (field2) != error_mark_غوټه
	  && COMPLETE_TYPE_P (ونه_TYPE (field2))
	  && integer_nonzerop (ونه_TYPE (field2)))
	أرجع -1;
      /* Otherwise, fallback to DECL_CHAIN walk to find out
	 which field comes earlier.  Walk chains of both
	 fields, so that if field1 and field2 are close to each
	 other in either order, it is found soon even for large
	 sequences of zero sized fields.  */
      ونه f1 = field1, f2 = field2;
      طالما (1)
	{
	  f1 = DECL_CHAIN (f1);
	  f2 = DECL_CHAIN (f2);
	  إذا (f1 == NULL_ونه)
	    {
	      gcc_assert (f2);
	      أرجع 1;
	    }
	  إذا (f2 == NULL_ونه)
	    أرجع -1;
	  إذا (f1 == field2)
	    أرجع -1;
	  إذا (f2 == field1)
	    أرجع 1;
	  إذا (!ونه_int_cst_equal (بټ_position (f1), bitpos1))
	    أرجع 1;
	  إذا (!ونه_int_cst_equal (بټ_position (f2), bitpos1))
	    أرجع -1;
	}
    }
  وإلا إذا (ونه_int_cst_lt (bitpos1, bitpos2))
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
  بنية init_غوټه *elt = constructor_pending_elts;
  ونه بل;

 retry:

  /* Look through the whole pending tree.
     If we find an element that should be output now,
     output it.  Otherwise, set NEXT to the element
     that comes first among those still pending.  */

  بل = NULL_ونه;
  طالما (elt)
    {
      إذا (ونه_کوډ (constructor_type) == ARRAY_TYPE)
	{
	  إذا (ونه_int_cst_equal (elt->purpose,
				  constructor_unfilled_شاخص))
	    output_init_element (ننوت_location, elt->ارزښت, elt->origtype,
				 ریښتیا, ونه_TYPE (constructor_type),
				 constructor_unfilled_شاخص, خطأ, خطأ,
				 braced_init_obstack);
	  وإلا إذا (ونه_int_cst_lt (constructor_unfilled_شاخص,
				    elt->purpose))
	    {
	      /* Advance to the next smaller node.  */
	      إذا (elt->کیڼ)
		elt = elt->کیڼ;
	      وإلا
		{
		  /* We have reached the smallest node bigger than the
		     current unfilled index.  Fill the space first.  */
		  بل = elt->purpose;
		  اكسر;
		}
	    }
	  وإلا
	    {
	      /* Advance to the next bigger node.  */
	      إذا (elt->ښی)
		elt = elt->ښی;
	      وإلا
		{
		  /* We have reached the biggest node in a subtree.  Find
		     the parent of it, which is the next bigger node.  */
		  طالما (elt->پلار && elt->پلار->ښی == elt)
		    elt = elt->پلار;
		  elt = elt->پلار;
		  إذا (elt && ونه_int_cst_lt (constructor_unfilled_شاخص,
					      elt->purpose))
		    {
		      بل = elt->purpose;
		      اكسر;
		    }
		}
	    }
	}
      وإلا إذا (ریکارډ_OR_UNION_TYPE_P (constructor_type))
	{
	  /* If the current record is complete we are done.  */
	  إذا (constructor_unfilled_fields == NULL_ونه)
	    اكسر;

	  صحيح cmp = init_ډګر_decl_cmp (constructor_unfilled_fields,
					 elt->purpose);
	  إذا (cmp == 0)
	    output_init_element (ننوت_location, elt->ارزښت, elt->origtype,
				 ریښتیا, ونه_TYPE (elt->purpose),
				 elt->purpose, خطأ, خطأ,
				 braced_init_obstack);
	  وإلا إذا (cmp < 0)
	    {
	      /* Advance to the next smaller node.  */
	      إذا (elt->کیڼ)
		elt = elt->کیڼ;
	      وإلا
		{
		  /* We have reached the smallest node bigger than the
		     current unfilled field.  Fill the space first.  */
		  بل = elt->purpose;
		  اكسر;
		}
	    }
	  وإلا
	    {
	      /* Advance to the next bigger node.  */
	      إذا (elt->ښی)
		elt = elt->ښی;
	      وإلا
		{
		  /* We have reached the biggest node in a subtree.  Find
		     the parent of it, which is the next bigger node.  */
		  طالما (elt->پلار && elt->پلار->ښی == elt)
		    elt = elt->پلار;
		  elt = elt->پلار;
		  إذا (elt
		      && init_ډګر_decl_cmp (constructor_unfilled_fields,
					      elt->purpose) < 0)
		    {
		      بل = elt->purpose;
		      اكسر;
		    }
		}
	    }
	}
    }

  /* Ordinarily return, but not if we want to output all
     and there are elements left.  */
  إذا (!(all && بل != NULL_ونه))
    أرجع;

  /* If it's not incremental, just skip over the gap, so that after
     jumping to retry we will output the next successive element.  */
  إذا (ریکارډ_OR_UNION_TYPE_P (constructor_type))
    constructor_unfilled_fields = بل;
  وإلا إذا (ونه_کوډ (constructor_type) == ARRAY_TYPE)
    constructor_unfilled_شاخص = بل;

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
initialize_elementwise_p (ونه type, ونه ارزښت)
{
  إذا (type == error_mark_غوټه || ارزښت == error_mark_غوټه)
    أرجع خطأ;

  gcc_checking_assert (TYPE_MAIN_VARIANT (type) == type);

  ونه ارزښت_type = ونه_TYPE (ارزښت);
  إذا (ارزښت_type == error_mark_غوټه)
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
  إذا (gnu_ویکټور_type_p (type))
    أرجع !ویکټور_TYPE_P (ارزښت_type);

  إذا (AGGREGATE_TYPE_P (type))
    أرجع !comptypes (type, TYPE_MAIN_VARIANT (ارزښت_type));

  أرجع خطأ;
}

/* Helper function for process_init_element.  Split first element of
   RAW_DATA_CST and save the rest to *RAW_DATA.  */

ساكن مضمن ونه
maybe_وېشل_raw_معلومات (ونه ارزښت, ونه *raw_معلومات)
{
  إذا (ارزښت == NULL_ونه || ونه_کوډ (ارزښت) != RAW_معلومات_CST)
    أرجع ارزښت;
  *raw_معلومات = ارزښت;
  ارزښت = build_int_cst (integer_type_غوټه,
			 RAW_معلومات_UCHAR_ELT (*raw_معلومات, 0));
  ++RAW_معلومات_اشاره_ګر (*raw_معلومات);
  --RAW_معلومات_اوږدتیا (*raw_معلومات);
  أرجع ارزښت;
}

/* Return non-zero if c_parser_initval should attempt to optimize
   large initializers into RAW_DATA_CST.  In that case return how
   many elements to optimize at most.  */

بینښه
c_maybe_optimize_large_byte_initializer (فراغ)
{
  إذا (!constructor_type
      || ونه_کوډ (constructor_type) != ARRAY_TYPE
      || constructor_ډېری->implicit)
    أرجع 0;
  ونه elttype = TYPE_MAIN_VARIANT (ونه_TYPE (constructor_type));
  إذا (ونه_کوډ (elttype) != INTEGER_TYPE
      && ونه_کوډ (elttype) != BITINT_TYPE)
    أرجع 0;
  إذا (TYPE_PRECISION (elttype) != CHAR_بټ
      || constructor_ډېری->replacement_ارزښت.ارزښت
      || (COMPLETE_TYPE_P (constructor_type)
	  && !poly_int_ونه_p (TYPE_اندازه (constructor_type)))
      || constructor_range_ډېری)
    أرجع 0;
  إذا (constructor_max_شاخص == NULL_ونه)
    أرجع لوی_عدد;
  إذا (ونه_int_cst_le (constructor_max_شاخص, constructor_شاخص)
      || integer_all_onesp (constructor_max_شاخص))
    أرجع 0;
  widest_int w = wi::منزل_widest (constructor_max_شاخص);
  w -= wi::منزل_widest (constructor_شاخص);
  w += 1;
  إذا (w < 64)
    أرجع 0;
  إذا (w > لوی_عدد)
    أرجع لوی_عدد;
  أرجع w.منزل_uhwi ();
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
process_init_element (location_t loc, بنية c_بیان ارزښت, منطقي implicit,
		      بنية obstack * braced_init_obstack)
{
  ونه orig_ارزښت = ارزښت.ارزښت;
  صحيح string_flag
    = (orig_ارزښت != NULL_ونه && ونه_کوډ (orig_ارزښت) == STRING_CST);
  منطقي strict_string = ارزښت.original_کوډ == STRING_CST;
  منطقي was_designated = designator_ژوروالی != 0;
  ونه raw_معلومات = NULL_ونه;

retry:
  designator_ژوروالی = 0;
  designator_erroneous = 0;

  إذا (!implicit && ارزښت.ارزښت && !integer_zerop (ارزښت.ارزښت))
    constructor_zeroinit = 0;

  /* Handle superfluous braces around string cst as in
     char x[] = {"foo"}; */
  إذا (constructor_type
      && !was_designated
      && ونه_کوډ (constructor_type) == ARRAY_TYPE
      && INTEGRAL_TYPE_P (ونه_TYPE (constructor_type))
      && integer_zerop (constructor_unfilled_شاخص))
    {
      إذا (constructor_ډېری->replacement_ارزښت.ارزښت)
	{
	  error_init (loc, "excess elements in %qT initializer", constructor_type);
	  أرجع;
	}
      وإلا إذا (string_flag)
	{
	  constructor_ډېری->replacement_ارزښت = ارزښت;
	  أرجع;
	}
    }

  إذا (constructor_ډېری->replacement_ارزښت.ارزښت != NULL_ونه)
    {
      error_init (loc, "excess elements in struct initializer");
      أرجع;
    }

  /* Ignore elements of a brace group if it is entirely superfluous
     and has already been diagnosed, or if the type is erroneous.  */
  إذا (constructor_type == NULL_ونه || constructor_type == error_mark_غوټه)
    أرجع;

  /* Ignore elements of an initializer for a variable-size type.
     Those are diagnosed in the parser (empty initializer braces are OK).  */
  إذا (COMPLETE_TYPE_P (constructor_type)
      && !poly_int_ونه_p (TYPE_اندازه (constructor_type)))
    أرجع;

  إذا (!implicit && warn_designated_init && !was_designated
      && ونه_کوډ (constructor_type) == ریکارډ_TYPE
      && lookup_attribute ("designated_init",
			   TYPE_ځانګړتیاوې (constructor_type)))
    warning_init (loc,
		  OPT_Wdesignated_init,
		  "positional initialization of field "
		  "in %<struct%> declared with %<designated_init%> attribute");

  /* If we've exhausted any levels that didn't have braces,
     pop them now.  */
  طالما (constructor_ډېری->implicit)
    {
      إذا (ریکارډ_OR_UNION_TYPE_P (constructor_type)
	  && constructor_fields == NULL_ونه)
	process_init_element (loc,
			      راوباسه_init_level (loc, 1, braced_init_obstack,
					      وروستی_init_list_comma),
			      ریښتیا, braced_init_obstack);
      وإلا إذا ((ونه_کوډ (constructor_type) == ARRAY_TYPE
		|| gnu_ویکټور_type_p (constructor_type))
	       && constructor_max_شاخص
	       && ونه_int_cst_lt (constructor_max_شاخص,
				   constructor_شاخص))
	process_init_element (loc,
			      راوباسه_init_level (loc, 1, braced_init_obstack,
					      وروستی_init_list_comma),
			      ریښتیا, braced_init_obstack);
      وإلا
	اكسر;
    }

  /* In the case of [LO ... HI] = VALUE, only evaluate VALUE once.  */
  إذا (constructor_range_ډېری)
    {
      /* If value is a compound literal and we'll be just using its
	 content, don't put it into a SAVE_EXPR.  */
      إذا (ونه_کوډ (ارزښت.ارزښت) != COMPOUND_LITERAL_بیان
	  || !require_constant_ارزښت)
	{
	  ونه semantic_type = NULL_ونه;
	  إذا (ونه_کوډ (ارزښت.ارزښت) == EXCESS_PRECISION_بیان)
	    {
	      semantic_type = ونه_TYPE (ارزښت.ارزښت);
	      ارزښت.ارزښت = ونه_عملوند (ارزښت.ارزښت, 0);
	    }
	  ارزښت.ارزښت = save_بیان (ارزښت.ارزښت);
	  إذا (semantic_type)
	    ارزښت.ارزښت = build1 (EXCESS_PRECISION_بیان, semantic_type,
				  ارزښت.ارزښت);
	}
    }

  طالما (1)
    {
      إذا (ونه_کوډ (constructor_type) == ریکارډ_TYPE)
	{
	  ونه fieldtype;
	  تعداد ونه_کوډ_2 fieldcode;

	  إذا (constructor_fields == NULL_ونه)
	    {
	      pedwarn_init (loc, 0, "excess elements in struct initializer");
	      اكسر;
	    }

	  fieldtype = ونه_TYPE (constructor_fields);
	  إذا (fieldtype != error_mark_غوټه)
	    fieldtype = TYPE_MAIN_VARIANT (fieldtype);
	  fieldcode = ونه_کوډ (fieldtype);

	  /* Error for non-static initialization of a flexible array member.  */
	  إذا (fieldcode == ARRAY_TYPE
	      && !require_constant_ارزښت
	      && TYPE_اندازه (fieldtype) == NULL_ونه
	      && DECL_CHAIN (constructor_fields) == NULL_ونه)
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
	      && constructor_ژوروالی > 1
	      && TYPE_اندازه (fieldtype) == NULL_ونه
	      && DECL_CHAIN (constructor_fields) == NULL_ونه)
	    {
	      منطقي دننه_array_p = خطأ;
	      لكل (بنية constructor_ډېری *p = constructor_ډېری;
		   p && p->type; p = p->بل)
		إذا (ونه_کوډ (p->type) == ARRAY_TYPE)
		  {
		    دننه_array_p = ریښتیا;
		    اكسر;
		  }
	      إذا (دننه_array_p)
		{
		  error_init (loc, "initialization of flexible array "
			      "member in a nested context");
		  اكسر;
		}
	    }

	  /* Accept a string constant to initialize a subarray.  */
	  إذا (ارزښت.ارزښت != NULL_ونه
	      && fieldcode == ARRAY_TYPE
	      && INTEGRAL_TYPE_P (ونه_TYPE (fieldtype))
	      && string_flag)
	    ارزښت.ارزښت = orig_ارزښت;
	  /* Otherwise, if we have come to a subaggregate,
	     and we don't have an element of its type, push into it.  */
	  وإلا إذا (ارزښت.ارزښت != NULL_ونه
		   && initialize_elementwise_p (fieldtype, ارزښت.ارزښت))
	    {
	      ټېل_init_level (loc, 1, braced_init_obstack);
	      استمر;
	    }

	  ارزښت.ارزښت = maybe_وېشل_raw_معلومات (ارزښت.ارزښت, &raw_معلومات);
	  إذا (ارزښت.ارزښت)
	    {
	      ټېل_member_name (constructor_fields);
	      output_init_element (loc, ارزښت.ارزښت, ارزښت.original_type,
				   strict_string, fieldtype,
				   constructor_fields, ریښتیا, implicit,
				   braced_init_obstack);
	      RESTORE_SPELLING_ژوروالی (constructor_ژوروالی);
	    }
	  وإلا
	    /* Do the bookkeeping for an element that was
	       directly output as a constructor.  */
	    {
	      /* For a record, keep track of end position of last field.  */
	      إذا (DECL_اندازه (constructor_fields))
		constructor_بټ_شاخص
		  = اندازه_binop_loc (ننوت_location, PLUS_بیان,
				    بټ_position (constructor_fields),
				    DECL_اندازه (constructor_fields));

	      /* If the current field was the first one not yet written out,
		 it isn't now, so update.  */
	      إذا (constructor_unfilled_fields == constructor_fields)
		{
		  constructor_unfilled_fields = DECL_CHAIN (constructor_fields);
		  /* Skip any nameless bit fields.  */
		  طالما (constructor_unfilled_fields != 0
			 && (DECL_UNNAMED_بټ_ډګر
			     (constructor_unfilled_fields)))
		    constructor_unfilled_fields =
		      DECL_CHAIN (constructor_unfilled_fields);
		}
	    }

	  constructor_fields = DECL_CHAIN (constructor_fields);
	  /* Skip any nameless bit fields at the beginning.  */
	  طالما (constructor_fields != NULL_ونه
		 && DECL_UNNAMED_بټ_ډګر (constructor_fields))
	    constructor_fields = DECL_CHAIN (constructor_fields);
	}
      وإلا إذا (ونه_کوډ (constructor_type) == UNION_TYPE)
	{
	  ونه fieldtype;
	  تعداد ونه_کوډ_2 fieldcode;

	  إذا (constructor_fields == NULL_ونه)
	    {
	      pedwarn_init (loc, 0,
			    "excess elements in union initializer");
	      اكسر;
	    }

	  fieldtype = ونه_TYPE (constructor_fields);
	  إذا (fieldtype != error_mark_غوټه)
	    fieldtype = TYPE_MAIN_VARIANT (fieldtype);
	  fieldcode = ونه_کوډ (fieldtype);

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
	  إذا (!دننه_system_سرلیک_at (ننوت_location) && !constructor_designated
	      && !(ارزښت.ارزښت && (integer_zerop (ارزښت.ارزښت)
				   || real_zerop (ارزښت.ارزښت))))
	    warning (OPT_Wtraditional, "traditional C rejects initialization "
		     "of unions");

	  /* Error for non-static initialization of a flexible array member.  */
	  إذا (fieldcode == ARRAY_TYPE
	      && !require_constant_ارزښت
	      && TYPE_اندازه (fieldtype) == NULL_ونه)
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
	      && constructor_ژوروالی > 1
	      && TYPE_اندازه (fieldtype) == NULL_ونه)
	    {
	      منطقي دننه_array_p = خطأ;
	      لكل (بنية constructor_ډېری *p = constructor_ډېری;
		   p && p->type; p = p->بل)
		إذا (ونه_کوډ (p->type) == ARRAY_TYPE)
		  {
		    دننه_array_p = ریښتیا;
		    اكسر;
		  }
	      إذا (دننه_array_p)
		{
		  error_init (loc, "initialization of flexible array "
			      "member in a nested context");
		  اكسر;
		}
	    }

	  /* Accept a string constant to initialize a subarray.  */
	  إذا (ارزښت.ارزښت != NULL_ونه
	      && fieldcode == ARRAY_TYPE
	      && INTEGRAL_TYPE_P (ونه_TYPE (fieldtype))
	      && string_flag)
	    ارزښت.ارزښت = orig_ارزښت;
	  /* Otherwise, if we have come to a subaggregate,
	     and we don't have an element of its type, push into it.  */
	  وإلا إذا (ارزښت.ارزښت != NULL_ونه
		   && initialize_elementwise_p (fieldtype, ارزښت.ارزښت))
	    {
	      ټېل_init_level (loc, 1, braced_init_obstack);
	      استمر;
	    }

	  ارزښت.ارزښت = maybe_وېشل_raw_معلومات (ارزښت.ارزښت, &raw_معلومات);
	  إذا (ارزښت.ارزښت)
	    {
	      ټېل_member_name (constructor_fields);
	      output_init_element (loc, ارزښت.ارزښت, ارزښت.original_type,
				   strict_string, fieldtype,
				   constructor_fields, ریښتیا, implicit,
				   braced_init_obstack);
	      RESTORE_SPELLING_ژوروالی (constructor_ژوروالی);
	    }
	  وإلا
	    /* Do the bookkeeping for an element that was
	       directly output as a constructor.  */
	    {
	      constructor_بټ_شاخص = DECL_اندازه (constructor_fields);
	      constructor_unfilled_fields = DECL_CHAIN (constructor_fields);
	    }

	  constructor_fields = NULL_ونه;
	}
      وإلا إذا (ونه_کوډ (constructor_type) == ARRAY_TYPE)
	{
	  ونه elttype = TYPE_MAIN_VARIANT (ونه_TYPE (constructor_type));
	  تعداد ونه_کوډ_2 eltcode = ونه_کوډ (elttype);

	  /* Accept a string constant to initialize a subarray.  */
	  إذا (ارزښت.ارزښت != NULL_ونه
	      && eltcode == ARRAY_TYPE
	      && INTEGRAL_TYPE_P (ونه_TYPE (elttype))
	      && string_flag)
	    ارزښت.ارزښت = orig_ارزښت;
	  /* Otherwise, if we have come to a subaggregate,
	     and we don't have an element of its type, push into it.  */
	  وإلا إذا (ارزښت.ارزښت != NULL_ونه
		   && initialize_elementwise_p (elttype, ارزښت.ارزښت))
	    {
	      ټېل_init_level (loc, 1, braced_init_obstack);
	      استمر;
	    }

	  إذا (constructor_max_شاخص != NULL_ونه
	      && (ونه_int_cst_lt (constructor_max_شاخص, constructor_شاخص)
		  || integer_all_onesp (constructor_max_شاخص))
	      /* For VLA we got an error already.  */
	      && !C_TYPE_VARIABLE_اندازه (constructor_type))
	    {
	      pedwarn_init (loc, 0,
			    "excess elements in array initializer");
	      اكسر;
	    }

	  إذا (ارزښت.ارزښت
	      && ونه_کوډ (ارزښت.ارزښت) == RAW_معلومات_CST
	      && RAW_معلومات_اوږدتیا (ارزښت.ارزښت) > 1
	      && (ونه_کوډ (elttype) == INTEGER_TYPE
		  || ونه_کوډ (elttype) == BITINT_TYPE)
	      && TYPE_PRECISION (elttype) == CHAR_بټ
	      && (constructor_max_شاخص == NULL_ونه
		  || ونه_int_cst_lt (constructor_شاخص,
				      constructor_max_شاخص)))
	    {
	      بینښه صحيح len = RAW_معلومات_اوږدتیا (ارزښت.ارزښت);
	      إذا (constructor_max_شاخص)
		{
		  widest_int w = wi::منزل_widest (constructor_max_شاخص);
		  w -= wi::منزل_widest (constructor_شاخص);
		  w += 1;
		  إذا (w < len)
		    len = w.منزل_uhwi ();
		}
	      إذا (len < (بینښه) RAW_معلومات_اوږدتیا (ارزښت.ارزښت))
		{
		  raw_معلومات = copy_غوټه (ارزښت.ارزښت);
		  RAW_معلومات_اوږدتیا (raw_معلومات) -= len;
		  RAW_معلومات_اشاره_ګر (raw_معلومات) += len;
		  RAW_معلومات_اوږدتیا (ارزښت.ارزښت) = len;
		}
	      ونه_TYPE (ارزښت.ارزښت) = elttype;
	      ټېل_array_bounds (ونه_منزل_uhwi (constructor_شاخص));
	      output_init_element (loc, ارزښت.ارزښت, ارزښت.original_type,
				   خطأ, elttype, constructor_شاخص, ریښتیا,
				   implicit, braced_init_obstack);
	      RESTORE_SPELLING_ژوروالی (constructor_ژوروالی);
	      constructor_شاخص
		= اندازه_binop_loc (ننوت_location, PLUS_بیان,
				  constructor_شاخص, bitsize_int (len));
	    }
	  وإلا
	    {
	      ارزښت.ارزښت = maybe_وېشل_raw_معلومات (ارزښت.ارزښت, &raw_معلومات);
	      /* Now output the actual element.  */
	      إذا (ارزښت.ارزښت)
		{
		  ټېل_array_bounds (ونه_منزل_uhwi (constructor_شاخص));
		  output_init_element (loc, ارزښت.ارزښت, ارزښت.original_type,
				       strict_string, elttype,
				       constructor_شاخص, ریښتیا, implicit,
				       braced_init_obstack);
		  RESTORE_SPELLING_ژوروالی (constructor_ژوروالی);
		}

	      constructor_شاخص
		= اندازه_binop_loc (ننوت_location, PLUS_بیان,
				  constructor_شاخص, bitsize_one_غوټه);

	      إذا (!ارزښت.ارزښت)
		/* If we are doing the bookkeeping for an element that was
		   directly output as a constructor, we must update
		   constructor_unfilled_index.  */
		constructor_unfilled_شاخص = constructor_شاخص;
	    }
	}
      وإلا إذا (gnu_ویکټور_type_p (constructor_type))
	{
	  ونه elttype = TYPE_MAIN_VARIANT (ونه_TYPE (constructor_type));

	  /* Do a basic check of initializer size.  Note that vectors
	     may not always have a fixed size derived from their type.  */
	  إذا (maybe_lt (ونه_منزل_poly_uint64 (constructor_max_شاخص),
			ونه_منزل_poly_uint64 (constructor_شاخص)))
	    {
	      /* Diagose VLA out-of-bounds as errors.  */
	      إذا (ونه_منزل_poly_uint64 (constructor_max_شاخص).is_constant())
		pedwarn_init (loc, 0,
			      "excess elements in vector initializer");
	      وإلا
		error_init (loc, "excess elements in vector initializer");

	      اكسر;
	    }

	  ارزښت.ارزښت = maybe_وېشل_raw_معلومات (ارزښت.ارزښت, &raw_معلومات);
	  /* Now output the actual element.  */
	  إذا (ارزښت.ارزښت)
	    {
	      إذا (ونه_کوډ (ارزښت.ارزښت) == ویکټور_CST)
		elttype = TYPE_MAIN_VARIANT (constructor_type);
	      output_init_element (loc, ارزښت.ارزښت, ارزښت.original_type,
				   strict_string, elttype,
				   constructor_شاخص, ریښتیا, implicit,
				   braced_init_obstack);
	    }

	  constructor_شاخص
	    = اندازه_binop_loc (ننوت_location,
			      PLUS_بیان, constructor_شاخص, bitsize_one_غوټه);

	  إذا (!ارزښت.ارزښت)
	    /* If we are doing the bookkeeping for an element that was
	       directly output as a constructor, we must update
	       constructor_unfilled_index.  */
	    constructor_unfilled_شاخص = constructor_شاخص;
	}

      /* Handle the sole element allowed in a braced initializer
	 for a scalar variable.  */
      وإلا إذا (constructor_type != error_mark_غوټه
	       && constructor_fields == NULL_ونه)
	{
	  pedwarn_init (loc, 0,
			"excess elements in scalar initializer");
	  اكسر;
	}
      وإلا
	{
	  ارزښت.ارزښت = maybe_وېشل_raw_معلومات (ارزښت.ارزښت, &raw_معلومات);
	  إذا (ارزښت.ارزښت)
	    output_init_element (loc, ارزښت.ارزښت, ارزښت.original_type,
				 strict_string, constructor_type,
				 NULL_ونه, ریښتیا, implicit,
				 braced_init_obstack);
	  constructor_fields = NULL_ونه;
	}

      /* Handle range initializers either at this level or anywhere higher
	 in the designator stack.  */
      إذا (constructor_range_ډېری)
	{
	  بنية constructor_range_ډېری *p, *range_ډېری;
	  صحيح پای = 0;

	  range_ډېری = constructor_range_ډېری;
	  constructor_range_ډېری = 0;
	  طالما (constructor_ډېری != range_ډېری->ډېری)
	    {
	      gcc_assert (constructor_ډېری->implicit);
	      process_init_element (loc,
				    راوباسه_init_level (loc, 1,
						    braced_init_obstack,
						    وروستی_init_list_comma),
				    ریښتیا, braced_init_obstack);
	    }
	  لكل (p = range_ډېری;
	       !p->range_پای_ټکی || ونه_int_cst_equal (p->شاخص, p->range_پای_ټکی);
	       p = p->prev)
	    {
	      gcc_assert (constructor_ډېری->implicit);
	      process_init_element (loc,
				    راوباسه_init_level (loc, 1,
						    braced_init_obstack,
						    وروستی_init_list_comma),
				    ریښتیا, braced_init_obstack);
	    }

	  p->شاخص = اندازه_binop_loc (ننوت_location,
				     PLUS_بیان, p->شاخص, bitsize_one_غوټه);
	  إذا (ونه_int_cst_equal (p->شاخص, p->range_پای_ټکی) && !p->prev)
	    پای = 1;

	  طالما (1)
	    {
	      constructor_شاخص = p->شاخص;
	      constructor_fields = p->fields;
	      إذا (پای && p->range_پای_ټکی && p->شاخص == p->range_پیل)
		{
		  پای = 0;
		  p->prev = 0;
		}
	      p = p->بل;
	      إذا (!p)
		اكسر;
	      پای_implicit_inits (loc, braced_init_obstack);
	      ټېل_init_level (loc, 2, braced_init_obstack);
	      p->ډېری = constructor_ډېری;
	      إذا (p->range_پای_ټکی && ونه_int_cst_equal (p->شاخص, p->range_پای_ټکی))
		p->شاخص = p->range_پیل;
	    }

	  إذا (!پای)
	    constructor_range_ډېری = range_ډېری;
	  استمر;
	}

      اكسر;
    }

  constructor_range_ډېری = 0;

  إذا (raw_معلومات && RAW_معلومات_اوږدتیا (raw_معلومات))
    {
      gcc_assert (!string_flag && !was_designated);
      ارزښت.ارزښت = raw_معلومات;
      raw_معلومات = NULL_ونه;
      اذهب retry;
    }
}

/* Build a complete asm-statement, whose components are a CV_QUALIFIER
   (guaranteed to be 'volatile' or null) and ARGS (represented using
   an ASM_EXPR node).  */
ونه
build_asm_stmt (منطقي is_volatile, ونه دلیلونه)
{
  إذا (is_volatile)
    ASM_VOLATILE_P (دلیلونه) = 1;
  أرجع جمع_کړه_stmt (دلیلونه);
}

/* Build an asm-expr, whose components are a STRING, some OUTPUTS,
   some INPUTS, and some CLOBBERS.  The latter three may be NULL.
   SIMPLE indicates whether there was anything at all after the
   string in the asm expression -- asm("blah") and asm("blah" : )
   are subtly different.  We use a ASM_EXPR node to represent this.
   LOC is the location of the asm, and IS_INLINE says whether this
   is asm inline.  */
ونه
build_asm_بیان (location_t loc, ونه string, ونه outputs, ونه inputs,
		ونه clobbers, ونه labels, منطقي simple, منطقي is_inline)
{
  ونه لکۍ;
  ونه دلیلونه;
  صحيح i;
  ثابت حرف *constraint;
  ثابت حرف **oconstraints;
  منطقي allows_mem, allows_reg, is_inout;
  صحيح ninputs, noutputs;

  ninputs = list_اوږدتیا (inputs);
  noutputs = list_اوږدتیا (outputs);
  oconstraints = (ثابت حرف **) alloca (noutputs * حجم (ثابت حرف *));

  string = resolve_asm_عملوند_نومونه (string, outputs, inputs, labels);

  /* Remove output conversions that change the type but not the mode.  */
  لكل (i = 0, لکۍ = outputs; لکۍ; ++i, لکۍ = ونه_CHAIN (لکۍ))
    {
      ونه output = ونه_ارزښت (لکۍ);

      output = c_fully_fold (output, خطأ, عدم, ریښتیا);

      /* ??? Really, this should not be here.  Users should be using a
	 proper lvalue, dammit.  But there's a long history of using casts
	 in the output operands.  In cases like longlong.h, this becomes a
	 primitive form of typechecking -- if the cast can be removed, then
	 the output operand had a type of the proper width; otherwise we'll
	 get an error.  Gross, but ...  */
      STRIP_NOPS (output);

      إذا (!lvalue_or_else (loc, output, lv_asm))
	output = error_mark_غوټه;

      إذا (output != error_mark_غوټه
	  && (ونه_READONLY (output)
	      || TYPE_READONLY (ونه_TYPE (output))
	      || (ریکارډ_OR_UNION_TYPE_P (ونه_TYPE (output))
		  && C_TYPE_FIELDS_READONLY (ونه_TYPE (output)))))
	readonly_error (loc, output, lv_asm);

      constraint = ونه_STRING_اشاره_ګر (ونه_ارزښت (ونه_PURPOSE (لکۍ)));
      oconstraints[i] = constraint;

      إذا (parse_output_constraint (&constraint, i, ninputs, noutputs,
				   &allows_mem, &allows_reg, &is_inout,
				   تش_اشاره))
	{
	  /* If the operand is going to end up in memory,
	     mark it addressable.  */
	  إذا (!allows_reg && !c_mark_addressable (output))
	    output = error_mark_غوټه;
	  إذا (!(!allows_reg && allows_mem)
	      && output != error_mark_غوټه
	      && VOID_TYPE_P (ونه_TYPE (output)))
	    {
	      error_at (loc, "invalid use of void expression");
	      output = error_mark_غوټه;
	    }
	  إذا (allows_reg && current_function_decl == NULL_ونه)
	    {
	      error_at (loc, "constraint allows registers outside of "
			     "a function");
	      output = error_mark_غوټه;
	    }
	}
      وإلا
	output = error_mark_غوټه;

      إذا (current_function_decl == NULL_ونه && output != error_mark_غوټه)
	{
	  إذا (ونه_SIDE_EFFECTS (output))
	    {
	      error_at (loc, "side-effects in output operand outside "
			     "of a function");
	      output = error_mark_غوټه;
	    }
	  وإلا
	    {
	      ونه addr = build_unary_op (loc, ADDR_بیان, output, خطأ);
	      إذا (addr == error_mark_غوټه)
		output = error_mark_غوټه;
	      وإلا إذا (!initializer_constant_valid_p (addr, ونه_TYPE (addr)))
		{
		  error_at (loc, "output operand outside of a function is not "
				 "constant");
		  output = error_mark_غوټه;
		}
	    }
	}
      وإلا إذا (output != error_mark_غوټه && مزي_پلټنه (constraint, "-"))
	{
	  error_at (loc, "%<-%> modifier used inside of a function");
	  output = error_mark_غوټه;
	}

      ونه_ارزښت (لکۍ) = output;
    }

  لكل (i = 0, لکۍ = inputs; لکۍ; ++i, لکۍ = ونه_CHAIN (لکۍ))
    {
      ونه ننوت;

      constraint = ونه_STRING_اشاره_ګر (ونه_ارزښت (ونه_PURPOSE (لکۍ)));
      ننوت = ونه_ارزښت (لکۍ);

      إذا (parse_ننوت_constraint (&constraint, i, ninputs, noutputs, 0,
				  oconstraints, &allows_mem, &allows_reg,
				  تش_اشاره))
	{
	  /* If the operand is going to end up in memory,
	     mark it addressable.  */
	  إذا (!allows_reg && allows_mem)
	    {
	      ننوت = c_fully_fold (ننوت, خطأ, عدم, ریښتیا);

	      /* Strip the nops as we allow this case.  FIXME, this really
		 should be rejected or made deprecated.  */
	      STRIP_NOPS (ننوت);
	      إذا (!c_mark_addressable (ننوت))
		ننوت = error_mark_غوټه;
	    }
	  وإلا
	    {
	      ننوت = c_fully_fold (convert_lvalue_منزل_rvalue (loc, ننوت,
							      ریښتیا, خطأ),
				    خطأ, عدم);

	      إذا (ننوت != error_mark_غوټه && VOID_TYPE_P (ونه_TYPE (ننوت)))
		{
		  error_at (loc, "invalid use of void expression");
		  ننوت = error_mark_غوټه;
		}
	    }
	  إذا (allows_reg && current_function_decl == NULL_ونه)
	    {
	      error_at (loc, "constraint allows registers outside of "
			     "a function");
	      ننوت = error_mark_غوټه;
	    }
	  إذا (constraint[0] == ':' && ننوت != error_mark_غوټه)
	    {
	      ونه t = ننوت;
	      STRIP_NOPS (t);
	      إذا (ونه_کوډ (t) != ADDR_بیان
		  || !(ونه_کوډ (ونه_عملوند (t, 0)) == FUNCTION_DECL
		       || (VAR_P (ونه_عملوند (t, 0))
			   && is_global_var (ونه_عملوند (t, 0)))))
		{
		  error_at (loc, "%<:%> constraint operand is not address "
				 "of a function or non-automatic variable");
		  ننوت = error_mark_غوټه;
		}
	      وإلا إذا (ونه_کوډ (ونه_عملوند (t, 0)) == FUNCTION_DECL)
		suppress_warning (ونه_عملوند (t, 0), OPT_Wunused);
	    }
	}
      وإلا
	ننوت = error_mark_غوټه;

      إذا (current_function_decl == NULL_ونه && ننوت != error_mark_غوټه)
	{
	  إذا (ونه_SIDE_EFFECTS (ننوت))
	    {
	      error_at (loc, "side-effects in input operand outside "
			     "of a function");
	      ننوت = error_mark_غوټه;
	    }
	  وإلا
	    {
	      ونه tem = ننوت;
	      إذا (allows_mem && lvalue_p (ننوت))
		tem = build_unary_op (loc, ADDR_بیان, ننوت, خطأ);
	      إذا (!initializer_constant_valid_p (tem, ونه_TYPE (tem)))
		{
		  error_at (loc, "input operand outside of a function is not "
				 "constant");
		  ننوت = error_mark_غوټه;
		}
	    }
	}
      وإلا إذا (ننوت != error_mark_غوټه && مزي_پلټنه (constraint, "-"))
	{
	  error_at (loc, "%<-%> modifier used inside of a function");
	  ننوت = error_mark_غوټه;
	}

      ونه_ارزښت (لکۍ) = ننوت;
    }

  دلیلونه = build_stmt (loc, ASM_بیان, string, outputs, inputs, clobbers, labels);

  /* asm statements without outputs, including simple ones, are treated
     as volatile.  */
  ASM_BASIC_P (دلیلونه) = simple;
  ASM_VOLATILE_P (دلیلونه) = (noutputs == 0);
  ASM_INLINE_P (دلیلونه) = is_inline;

  أرجع دلیلونه;
}

/* Generate a goto statement to LABEL.  LOC is the location of the
   GOTO.  */

ونه
c_پای_goto_label (location_t loc, ونه label)
{
  ونه decl = lookup_label_for_goto (loc, label);
  إذا (!decl)
    أرجع NULL_ونه;
  ونه_کارول_شوی (decl) = 1;
  mark_decl_کارول_شوی (decl, خطأ);
  {
    جمع_کړه_stmt (build_predict_بیان (PRED_GOTO, NOT_اخیستل_شوی));
    ونه t = build1 (GOTO_بیان, void_type_غوټه, decl);
    سېټ_بیان_LOCATION (t, loc);
    أرجع جمع_کړه_stmt (t);
  }
}

/* Generate a computed goto statement to EXPR.  LOC is the location of
   the GOTO.  */

ونه
c_پای_goto_ptr (location_t loc, c_بیان val)
{
  ونه بیان = val.ارزښت;
  ونه t;
  pedwarn (loc, OPT_Wpedantic, "ISO C forbids %<goto *expr;%>");
  إذا (بیان != error_mark_غوټه
      && !اشاره_ګر_TYPE_P (ونه_TYPE (بیان))
      && !null_اشاره_ګر_constant_p (بیان))
    {
      error_at (val.get_location (),
		"computed goto must be pointer type");
      بیان = build_zero_cst (ptr_type_غوټه);
    }
  بیان = c_fully_fold (بیان, خطأ, عدم);
  بیان = convert (ptr_type_غوټه, بیان);
  t = build1 (GOTO_بیان, void_type_غوټه, بیان);
  سېټ_بیان_LOCATION (t, loc);
  أرجع جمع_کړه_stmt (t);
}

/* Generate a C `return' statement.  RETVAL is the expression for what
   to return, or a null pointer for `return;' with no value.  LOC is
   the location of the return statement, or the location of the expression,
   if the statement has any.  If ORIGTYPE is not NULL_TREE, it
   is the original type of RETVAL.  MUSTTAIL_P indicates a musttail
   attribute.  */

ونه
c_پای_return (location_t loc, ونه retval, ونه origtype, منطقي musttail_p)
{
  ونه valtype = ونه_TYPE (ونه_TYPE (current_function_decl)), ret_stmt;
  منطقي no_warning = خطأ;
  منطقي npc = خطأ;

  /* Use the expansion point to handle cases such as returning NULL
     in a function returning void.  */
  location_t xloc = expansion_ټکی_location_if_دننه_system_سرلیک (loc);

  إذا (ونه_THIS_VOLATILE (current_function_decl))
    warning_at (xloc, 0,
		"function declared %<noreturn%> has a %<return%> statement");

  سېټ_musttail_on_return (retval, xloc, musttail_p);

  إذا (retval)
    {
      ونه semantic_type = NULL_ونه;
      npc = null_اشاره_ګر_constant_p (retval);
      إذا (ونه_کوډ (retval) == EXCESS_PRECISION_بیان)
	{
	  semantic_type = ونه_TYPE (retval);
	  retval = ونه_عملوند (retval, 0);
	}
      retval = c_fully_fold (retval, خطأ, عدم);
      إذا (semantic_type
	  && valtype != NULL_ونه
	  && ونه_کوډ (valtype) != VOID_TYPE)
	retval = build1 (EXCESS_PRECISION_بیان, semantic_type, retval);
    }

  إذا (!retval)
    {
      current_function_returns_null = 1;
      إذا ((warn_return_type >= 0 || flag_isoc99)
	  && valtype != NULL_ونه && ونه_کوډ (valtype) != VOID_TYPE)
	{
	  no_warning = ریښتیا;
	  إذا (emit_diagnostic (flag_isoc99
			       ? diagnostics::ډول::permerror
			       : diagnostics::ډول::warning,
			       loc, OPT_Wreturn_mismatch,
			       "%<return%> with no value,"
			       " in function returning non-void"))
	    inform (DECL_سرچینه_LOCATION (current_function_decl),
		    "declared here");
	}
    }
  وإلا إذا (valtype == NULL_ونه || VOID_TYPE_P (valtype))
    {
      current_function_returns_null = 1;
      منطقي warned_دلته;
      إذا (ونه_کوډ (ونه_TYPE (retval)) != VOID_TYPE)
	warned_دلته = permerror_opt
	  (xloc, OPT_Wreturn_mismatch,
	   "%<return%> with a value, in function returning void");
      وإلا
	warned_دلته = pedwarn
	  (xloc, OPT_Wpedantic, "ISO C forbids "
	   "%<return%> with expression, in function returning void");
      إذا (warned_دلته)
	inform (DECL_سرچینه_LOCATION (current_function_decl),
		"declared here");
    }
  وإلا
    {
      ونه t = convert_for_assignment (loc, UNKNOWN_LOCATION, valtype,
				       retval, origtype, ic_return,
				       npc, NULL_ونه, NULL_ونه, 0);
      ونه res = DECL_پایله (current_function_decl);
      ونه inner;
      منطقي save;

      current_function_returns_ارزښت = 1;
      إذا (t == error_mark_غوټه)
	{
	  /* Suppress -Wreturn-type for this function.  */
	  إذا (warn_return_type)
	    suppress_warning (current_function_decl, OPT_Wreturn_type);
	  أرجع NULL_ونه;
	}

      save = دننه_late_دوګونی_op;
      إذا (C_BOOLEAN_TYPE_P (ونه_TYPE (res))
	  || ونه_کوډ (ونه_TYPE (res)) == COMPLEX_TYPE
	  || (SCALAR_FLOAT_TYPE_P (ونه_TYPE (t))
	      && (ونه_کوډ (ونه_TYPE (res)) == INTEGER_TYPE
		  || ونه_کوډ (ونه_TYPE (res)) == ENUMERAL_TYPE)
	      && sanitize_flags_p (SANITIZE_FLOAT_CAST)))
        دننه_late_دوګونی_op = ریښتیا;
      inner = t = convert (ونه_TYPE (res), t);
      دننه_late_دوګونی_op = save;

      /* Strip any conversions, additions, and subtractions, and see if
	 we are returning the address of a local variable.  Warn if so.  */
      طالما (1)
	{
	  بدل (ونه_کوډ (inner))
	    {
	    CASE_CONVERT:
	    حالة NON_LVALUE_بیان:
	    حالة PLUS_بیان:
	    حالة اشاره_ګر_PLUS_بیان:
	      inner = ونه_عملوند (inner, 0);
	      استمر;

	    حالة MINUS_بیان:
	      /* If the second operand of the MINUS_EXPR has a pointer
		 type (or is converted from it), this may be valid, so
		 don't give a warning.  */
	      {
		ونه op1 = ونه_عملوند (inner, 1);

		طالما (!اشاره_ګر_TYPE_P (ونه_TYPE (op1))
		       && (CONVERT_بیان_P (op1)
			   || ونه_کوډ (op1) == NON_LVALUE_بیان))
		  op1 = ونه_عملوند (op1, 0);

		إذا (اشاره_ګر_TYPE_P (ونه_TYPE (op1)))
		  اكسر;

		inner = ونه_عملوند (inner, 0);
		استمر;
	      }

	    حالة ADDR_بیان:
	      inner = ونه_عملوند (inner, 0);

	      طالما (REFERENCE_CLASS_P (inner)
		     && !غیرمستقیم_REF_P (inner))
		inner = ونه_عملوند (inner, 0);

	      إذا (DECL_P (inner)
		  && !DECL_EXTERNAL (inner)
		  && DECL_CONTEXT (inner) == current_function_decl
		  && اشاره_ګر_TYPE_P (ونه_TYPE (ونه_TYPE (current_function_decl))))
		{
		  إذا (ونه_کوډ (inner) == LABEL_DECL)
		    warning_at (loc, OPT_Wreturn_local_addr,
				"function returns address of label");
		  وإلا إذا (ونه_کوډ (inner) == FUNCTION_DECL
			   && (C_FUNC_NONLOCAL_CONTEXT (inner)
			       || !DECL_INITIAL (inner)))
		    warning_at (loc, OPT_Wreturn_local_addr,
				"function returns address of nested function "
				"referencing local context");
		  وإلا إذا (ونه_کوډ (inner) != FUNCTION_DECL
			   && !ونه_STATIC (inner))
		    {
		      warning_at (loc, OPT_Wreturn_local_addr,
				  "function returns address of local variable");
		      ونه zero = build_zero_cst (ونه_TYPE (res));
		      t = build2 (COMPOUND_بیان, ونه_TYPE (res), t, zero);
		    }
		}
	      اكسر;

	    افتراضي:
	      اكسر;
	    }

	  اكسر;
	}

      retval = build2 (MODIFY_بیان, ونه_TYPE (res), res, t);
      سېټ_بیان_LOCATION (retval, loc);

      إذا (warn_sequence_ټکی)
	verify_sequence_points (retval);
    }

  ret_stmt = build_stmt (loc, RETURN_بیان, retval);
  إذا (no_warning)
    suppress_warning (ret_stmt, OPT_Wreturn_type);
  أرجع جمع_کړه_stmt (ret_stmt);
}

بنية c_switch {
  /* The SWITCH_STMT being built.  */
  ونه switch_stmt;

  /* The original type of the testing expression, i.e. before the
     default conversion is applied.  */
  ونه orig_type;

  /* A splay-tree mapping the low element of a case range to the high
     element, or NULL_TREE if there is no high element.  Used to
     determine whether or not a new case label duplicates an old case
     label.  We need a tree, rather than simply a hash table, because
     of the GNU case range extension.  */
  splay_ونه cases;

  /* The bindings at the point of the switch.  This is used for
     warnings crossing decls when branching to a case label.  */
  بنية c_spot_bindings *bindings;

  /* Whether the switch includes any break statements.  */
  منطقي break_stmt_کتل_شوی_p;

  /* The next node on the stack.  */
  بنية c_switch *بل;

  /* Remember whether the controlling expression had boolean type
     before integer promotions for the sake of -Wswitch-bool.  */
  منطقي bool_cond_p;
};

/* A stack of the currently active switch statements.  The innermost
   switch statement is on the top of the stack.  There is no need to
   mark the stack for garbage collection because it is only active
   during the processing of the body of a function, and we never
   collect at that point.  */

بنية c_switch *c_switch_ډېری;

/* Start a C switch statement, testing expression EXP.  Return the new
   SWITCH_STMT.  SWITCH_LOC is the location of the `switch'.
   SWITCH_COND_LOC is the location of the switch's condition.
   EXPLICIT_CAST_P is true if the expression EXP has an explicit cast.  */

ونه
c_پیل_switch (location_t switch_loc,
		location_t switch_cond_loc,
		ونه توانیز_تابع, منطقي explicit_cast_p, ونه switch_name)
{
  ونه orig_type = error_mark_غوټه;
  منطقي bool_cond_p = خطأ;
  بنية c_switch *cs;

  إذا (توانیز_تابع != error_mark_غوټه)
    {
      orig_type = ونه_TYPE (توانیز_تابع);

      إذا (!INTEGRAL_TYPE_P (orig_type))
	{
	  إذا (orig_type != error_mark_غوټه)
	    {
	      error_at (switch_cond_loc, "switch quantity not an integer");
	      orig_type = error_mark_غوټه;
	    }
	  توانیز_تابع = integer_zero_غوټه;
	}
      وإلا
	{
	  ونه type = TYPE_MAIN_VARIANT (orig_type);
	  ونه e = توانیز_تابع;

	  /* Warn if the condition has boolean value.  */
	  طالما (ونه_کوډ (e) == COMPOUND_بیان)
	    e = ونه_عملوند (e, 1);

	  إذا ((C_BOOLEAN_TYPE_P (type)
	       || truth_ارزښت_p (ونه_کوډ (e)))
	      /* Explicit cast to int suppresses this warning.  */
	      && !(ونه_کوډ (type) == INTEGER_TYPE
		   && explicit_cast_p))
	    bool_cond_p = ریښتیا;

	  إذا (!دننه_system_سرلیک_at (ننوت_location)
	      && (type == long_integer_type_غوټه
		  || type == long_unsigned_type_غوټه))
	    warning_at (switch_cond_loc,
			OPT_Wtraditional, "%<long%> switch expression not "
			"converted to %<int%> in ISO C");

	  توانیز_تابع = c_fully_fold (توانیز_تابع, خطأ, عدم);
	  توانیز_تابع = default_conversion (توانیز_تابع);

	  إذا (warn_sequence_ټکی)
	    verify_sequence_points (توانیز_تابع);
	}
    }

  /* Add this new SWITCH_STMT to the stack.  */
  cs = XNEW (بنية c_switch);
  cs->switch_stmt = build_stmt (switch_loc, SWITCH_STMT, توانیز_تابع,
				NULL_ونه, orig_type, NULL_ونه, switch_name);
  cs->orig_type = orig_type;
  cs->cases = splay_ونه_new (case_compare, عدم, عدم);
  cs->bindings = c_get_switch_bindings ();
  cs->break_stmt_کتل_شوی_p = خطأ;
  cs->bool_cond_p = bool_cond_p;
  cs->بل = c_switch_ډېری;
  c_switch_ډېری = cs;

  أرجع جمع_کړه_stmt (cs->switch_stmt);
}

/* Process a case label at location LOC, with attributes ATTRS.  */

ونه
do_case (location_t loc, ونه ټیټ_ارزښت, ونه لوړ_ارزښت, ونه attrs)
{
  ونه label = NULL_ونه;

  إذا (ټیټ_ارزښت && ونه_کوډ (ټیټ_ارزښت) != INTEGER_CST)
    {
      ټیټ_ارزښت = c_fully_fold (ټیټ_ارزښت, خطأ, عدم);
      إذا (ونه_کوډ (ټیټ_ارزښت) == INTEGER_CST)
	pedwarn (loc, OPT_Wpedantic,
		 "case label is not an integer constant expression");
    }

  إذا (لوړ_ارزښت && ونه_کوډ (لوړ_ارزښت) != INTEGER_CST)
    {
      لوړ_ارزښت = c_fully_fold (لوړ_ارزښت, خطأ, عدم);
      إذا (ونه_کوډ (لوړ_ارزښت) == INTEGER_CST)
	pedwarn (ننوت_location, OPT_Wpedantic,
		 "case label is not an integer constant expression");
    }

  إذا (c_switch_ډېری == عدم)
    {
      إذا (ټیټ_ارزښت)
	error_at (loc, "case label not within a switch statement");
      وإلا
	error_at (loc, "%<default%> label not within a switch statement");
      أرجع NULL_ونه;
    }

  إذا (c_check_switch_jump_warnings (c_switch_ډېری->bindings,
				    بیان_LOCATION (c_switch_ډېری->switch_stmt),
				    loc))
    أرجع NULL_ونه;

  label = c_جمع_کړه_case_label (loc, c_switch_ډېری->cases,
			    SWITCH_STMT_COND (c_switch_ډېری->switch_stmt),
			    ټیټ_ارزښت, لوړ_ارزښت, attrs);
  إذا (label == error_mark_غوټه)
    label = NULL_ونه;
  أرجع label;
}

/* Finish the switch statement.  TYPE is the original type of the
   controlling expression of the switch, or NULL_TREE.  */

فراغ
c_پای_switch (ونه body, ونه type)
{
  بنية c_switch *cs = c_switch_ډېری;
  location_t switch_location;

  SWITCH_STMT_BODY (cs->switch_stmt) = body;

  /* Emit warnings as needed.  */
  switch_location = بیان_LOCATION (cs->switch_stmt);
  c_do_switch_warnings (cs->cases, switch_location,
			type ? type : SWITCH_STMT_TYPE (cs->switch_stmt),
			SWITCH_STMT_COND (cs->switch_stmt), cs->bool_cond_p);
  إذا (c_switch_covers_all_cases_p (cs->cases,
				   SWITCH_STMT_TYPE (cs->switch_stmt)))
    SWITCH_STMT_ALL_CASES_P (cs->switch_stmt) = 1;
  SWITCH_STMT_NO_BREAK_P (cs->switch_stmt) = !cs->break_stmt_کتل_شوی_p;

  /* Pop the stack.  */
  c_switch_ډېری = cs->بل;
  splay_ونه_delete (cs->cases);
  c_release_switch_bindings (cs->bindings);
  XDELETE (cs);
}

/* Emit an if statement.  IF_LOCUS is the location of the 'if'.  COND,
   THEN_BLOCK and ELSE_BLOCK are expressions to be used; ELSE_BLOCK
   may be null.  */

فراغ
c_پای_if_stmt (location_t if_locus, ونه cond, ونه then_بلاک,
		  ونه else_بلاک)
{
  ونه stmt;

  stmt = build3 (COND_بیان, void_type_غوټه, cond, then_بلاک, else_بلاک);
  سېټ_بیان_LOCATION (stmt, if_locus);
  جمع_کړه_stmt (stmt);
}

ونه
c_پای_bc_stmt (location_t loc, ونه label, منطقي is_break, ونه name)
{
  /* In switch statements break is sometimes stylistically used after
     a return statement.  This can lead to spurious warnings about
     control reaching the end of a non-void function when it is
     inlined.  Note that we are calling block_may_fallthru with
     language specific tree nodes; this works because
     block_may_fallthru returns true when given something it does not
     understand.  */
  منطقي skip = !بلاک_may_fallthru (cur_stmt_list);

  إذا (is_break)
    بدل (دننه_statement & ~دننه_NAMED_STMT)
      {
      حالة 0:
	error_at (loc, "break statement not within loop or switch");
	أرجع NULL_ونه;
      حالة دننه_OMP_بلاک:
	error_at (loc, "invalid exit from OpenMP structured block");
	أرجع NULL_ونه;
      حالة دننه_OMP_FOR:
	error_at (loc, "break statement used with OpenMP for loop");
	أرجع NULL_ونه;
      حالة دننه_ITERATION_STMT:
      حالة دننه_OBJC_FOREACH:
	اكسر;
      افتراضي:
	gcc_assert (دننه_statement & دننه_SWITCH_STMT);
	c_switch_ډېری->break_stmt_کتل_شوی_p = ریښتیا;
	اكسر;
      }
  وإلا
    بدل (دننه_statement & ~(دننه_SWITCH_STMT | دننه_NAMED_STMT))
      {
      حالة 0:
	error_at (loc, "continue statement not within a loop");
	أرجع NULL_ونه;
      حالة دننه_OMP_بلاک:
	error_at (loc, "invalid exit from OpenMP structured block");
	أرجع NULL_ونه;
      حالة دننه_ITERATION_STMT:
      حالة دننه_OMP_FOR:
      حالة دننه_OBJC_FOREACH:
	اكسر;
      افتراضي:
	gcc_unreachable ();
      }

  إذا (skip)
    أرجع NULL_ونه;
  وإلا إذا ((دننه_statement & دننه_OBJC_FOREACH)
	   && !(is_break && (دننه_statement & دننه_SWITCH_STMT))
	   && name == NULL_ونه)
    {
      /* The foreach expander produces low-level code using gotos instead
	 of a structured loop construct.  */
      gcc_assert (label);
      أرجع جمع_کړه_stmt (build_stmt (loc, GOTO_بیان, label));
    }
  وإلا إذا (name && C_DECL_LOOP_NAME (name) && C_DECL_SWITCH_NAME (name))
    {
      label = DECL_CHAIN (name);
      إذا (!is_break)
	label = DECL_CHAIN (label);
      /* Foreach expander from some outer level.  */
      أرجع جمع_کړه_stmt (build_stmt (loc, GOTO_بیان, label));
    }
  أرجع جمع_کړه_stmt (build_stmt (loc, is_break ? BREAK_STMT : CONTINUE_STMT,
			       name));
}

/* A helper routine for c_process_expr_stmt and c_finish_stmt_expr.  */

ساكن فراغ
emit_side_effect_warnings (location_t loc, ونه بیان)
{
  maybe_warn_nodiscard (loc, بیان);
  إذا (!warn_ناکارول_شوی_ارزښت)
    أرجع;
  إذا (بیان == error_mark_غوټه)
    ;
  وإلا إذا (!ونه_SIDE_EFFECTS (بیان))
    {
      إذا (!VOID_TYPE_P (ونه_TYPE (بیان))
	  && !warning_suppressed_p (بیان, OPT_Wunused_ارزښت))
	warning_at (loc, OPT_Wunused_ارزښت, "statement with no effect");
    }
  وإلا إذا (ونه_کوډ (بیان) == COMPOUND_بیان)
    {
      ونه r = بیان;
      location_t cloc = loc;
      طالما (ونه_کوډ (r) == COMPOUND_بیان)
	{
	  إذا (بیان_HAS_LOCATION (r))
	    cloc = بیان_LOCATION (r);
	  r = ونه_عملوند (r, 1);
	}
      إذا (!ونه_SIDE_EFFECTS (r)
	  && !VOID_TYPE_P (ونه_TYPE (r))
	  && !CONVERT_بیان_P (r)
	  && !warning_suppressed_p (r, OPT_Wunused_ارزښت)
	  && !warning_suppressed_p (بیان, OPT_Wunused_ارزښت))
	warning_at (cloc, OPT_Wunused_ارزښت,
		    "right-hand operand of comma expression has no effect");
    }
  وإلا
    warn_if_ناکارول_شوی_ارزښت (بیان, loc);
}

/* Process an expression as if it were a complete statement.  Emit
   diagnostics, but do not call ADD_STMT.  LOC is the location of the
   statement.  */

ونه
c_process_بیان_stmt (location_t loc, ونه بیان)
{
  ونه exprv;

  إذا (!بیان)
    أرجع NULL_ونه;

  بیان = c_fully_fold (بیان, خطأ, عدم);

  إذا (warn_sequence_ټکی)
    verify_sequence_points (بیان);

  إذا (ونه_TYPE (بیان) != error_mark_غوټه
      && !COMPLETE_OR_VOID_TYPE_P (ونه_TYPE (بیان))
      && ونه_کوډ (ونه_TYPE (بیان)) != ARRAY_TYPE)
    error_at (loc, "expression statement has incomplete type");

  /* If we're not processing a statement expression, warn about unused values.
     Warnings for statement expressions will be emitted later, once we figure
     out which is the result.  */
  إذا (!STATEMENT_LIST_STMT_بیان (cur_stmt_list)
      && (warn_ناکارول_شوی_ارزښت || warn_ناکارول_شوی_پایله))
    emit_side_effect_warnings (بیان_LOC_OR_LOC (بیان, loc), بیان);

  exprv = بیان;
  طالما (ونه_کوډ (exprv) == COMPOUND_بیان)
    exprv = ونه_عملوند (exprv, 1);
  طالما (CONVERT_بیان_P (exprv))
    exprv = ونه_عملوند (exprv, 0);
  إذا (DECL_P (exprv)
      || handled_component_p (exprv)
      || ونه_کوډ (exprv) == ADDR_بیان)
    mark_exp_read (exprv);

  /* If the expression is not of a type to which we cannot assign a line
     number, wrap the thing in a no-op NOP_EXPR.  */
  إذا (DECL_P (بیان) || CONSTANT_CLASS_P (بیان))
    {
      بیان = build1 (NOP_بیان, ونه_TYPE (بیان), بیان);
      سېټ_بیان_LOCATION (بیان, loc);
    }

  أرجع بیان;
}

/* Emit an expression as a statement.  LOC is the location of the
   expression.  */

ونه
c_پای_بیان_stmt (location_t loc, ونه بیان)
{
  إذا (بیان)
    أرجع جمع_کړه_stmt (c_process_بیان_stmt (loc, بیان));
  وإلا
    أرجع عدم;
}

/* Do the opposite and emit a statement as an expression.  To begin,
   create a new binding level and return it.  */

ونه
c_begin_stmt_بیان (فراغ)
{
  ونه ret;

  /* We must force a BLOCK for this level so that, if it is not expanded
     later, there is a way to turn off the entire subtree of blocks that
     are contained in it.  */
  keep_بل_level ();
  ret = c_begin_compound_stmt (ریښتیا);

  c_bindings_پیل_stmt_بیان (c_switch_ډېری == عدم
			      ? عدم
			      : c_switch_ډېری->bindings);

  /* Mark the current statement list as belonging to a statement list.  */
  STATEMENT_LIST_STMT_بیان (ret) = 1;

  أرجع ret;
}

/* LOC is the location of the compound statement to which this body
   belongs.  */

ونه
c_پای_stmt_بیان (location_t loc, ونه body)
{
  ونه وروستی, type, tmp, val;
  ونه *وروستی_p;

  body = c_پای_ټکی_compound_stmt (loc, body, ریښتیا);

  c_bindings_پای_ټکی_stmt_بیان (c_switch_ډېری == عدم
			    ? عدم
			    : c_switch_ډېری->bindings);

  /* Locate the last statement in BODY.  See c_end_compound_stmt
     about always returning a BIND_EXPR.  */
  وروستی_p = &BIND_بیان_BODY (body);
  وروستی = BIND_بیان_BODY (body);

 continue_searching:
  إذا (ونه_کوډ (وروستی) == STATEMENT_LIST)
    {
      ونه_stmt_iterator l = tsi_وروستی (وروستی);

      طالما (!tsi_پای_ټکی_p (l) && ونه_کوډ (tsi_stmt (l)) == DEBUG_BEGIN_STMT)
	tsi_prev (&l);

      /* This can happen with degenerate cases like ({ }).  No value.  */
      إذا (tsi_پای_ټکی_p (l))
	أرجع body;

      /* If we're supposed to generate side effects warnings, process
	 all of the statements except the last.  */
      إذا (warn_ناکارول_شوی_ارزښت || warn_ناکارول_شوی_پایله)
	{
	  لكل (ونه_stmt_iterator i = tsi_پیل (وروستی);
	       tsi_stmt (i) != tsi_stmt (l); tsi_بل (&i))
	    {
	      location_t tloc;
	      ونه t = tsi_stmt (i);

	      tloc = بیان_HAS_LOCATION (t) ? بیان_LOCATION (t) : loc;
	      emit_side_effect_warnings (tloc, t);
	    }
	}
      وروستی_p = tsi_stmt_ptr (l);
      وروستی = *وروستی_p;
    }

  /* If the end of the list is exception related, then the list was split
     by a call to push_cleanup.  Continue searching.  */
  إذا (ونه_کوډ (وروستی) == TRY_FINALLY_بیان
      || ونه_کوډ (وروستی) == TRY_CATCH_بیان)
    {
      وروستی_p = &ونه_عملوند (وروستی, 0);
      وروستی = *وروستی_p;
      اذهب continue_searching;
    }

  إذا (وروستی == error_mark_غوټه)
    أرجع وروستی;

  /* In the case that the BIND_EXPR is not necessary, return the
     expression out from inside it.  */
  إذا ((وروستی == BIND_بیان_BODY (body)
       /* Skip nested debug stmts.  */
       || وروستی == بیان_لومړی (BIND_بیان_BODY (body)))
      && BIND_بیان_VARS (body) == عدم)
    {
      /* Even if this looks constant, do not allow it in a constant
	 expression.  */
      وروستی = c_wrap_maybe_const (وروستی, ریښتیا);
      /* Do not warn if the return value of a statement expression is
	 unused.  */
      suppress_warning (وروستی, OPT_Wunused);
      أرجع وروستی;
    }

  /* Extract the type of said expression.  */
  type = ونه_TYPE (وروستی);

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
  val = وروستی;
  إذا (ونه_کوډ (val) == NOP_بیان
      && ونه_TYPE (val) == ونه_TYPE (ونه_عملوند (val, 0)))
    val = ونه_عملوند (val, 0);

  *وروستی_p = build2 (MODIFY_بیان, void_type_غوټه, tmp, val);
  سېټ_بیان_LOCATION (*وروستی_p, بیان_LOCATION (وروستی));

  {
    ونه t = build4 (موخه_بیان, type, tmp, body, NULL_ونه, NULL_ونه);
    سېټ_بیان_LOCATION (t, loc);
    أرجع t;
  }
}

/* Begin and end compound statements.  This is as simple as pushing
   and popping new statement lists from the tree.  */

ونه
c_begin_compound_stmt (منطقي do_scope)
{
  ونه stmt = ټېل_stmt_list ();
  إذا (do_scope)
    ټېل_scope ();
  أرجع stmt;
}

/* End a compound statement.  STMT is the statement.  LOC is the
   location of the compound statement-- this is usually the location
   of the opening brace.  */

ونه
c_پای_ټکی_compound_stmt (location_t loc, ونه stmt, منطقي do_scope)
{
  ونه بلاک = عدم;

  إذا (do_scope)
    {
      إذا (c_dialect_objc ())
	objc_clear_super_receiver ();
      بلاک = راوباسه_scope ();
    }

  stmt = راوباسه_stmt_list (stmt);
  stmt = c_build_bind_بیان (loc, بلاک, stmt);

  /* If this compound statement is nested immediately inside a statement
     expression, then force a BIND_EXPR to be created.  Otherwise we'll
     do the wrong thing for ({ { 1; } }) or ({ 1; { } }).  In particular,
     STATEMENT_LISTs merge, and thus we can lose track of what statement
     was really last.  */
  إذا (building_stmt_list_p ()
      && STATEMENT_LIST_STMT_بیان (cur_stmt_list)
      && ونه_کوډ (stmt) != BIND_بیان)
    {
      stmt = build3 (BIND_بیان, void_type_غوټه, عدم, stmt, عدم);
      ونه_SIDE_EFFECTS (stmt) = 1;
      سېټ_بیان_LOCATION (stmt, loc);
    }

  أرجع stmt;
}

/* Queue a cleanup.  CLEANUP is an expression/statement to be executed
   when the current scope is exited.  EH_ONLY is true when this is not
   meant to apply to normal control flow transfer.  */

فراغ
ټېل_cleanup (ونه decl, ونه cleanup, منطقي eh_only)
{
  تعداد ونه_کوډ_2 کوډ;
  ونه stmt, list;
  منطقي stmt_بیان;

  کوډ = eh_only ? TRY_CATCH_بیان : TRY_FINALLY_بیان;
  stmt = build_stmt (DECL_سرچینه_LOCATION (decl), کوډ, عدم, cleanup);
  جمع_کړه_stmt (stmt);
  stmt_بیان = STATEMENT_LIST_STMT_بیان (cur_stmt_list);
  list = ټېل_stmt_list ();
  ونه_عملوند (stmt, 0) = list;
  STATEMENT_LIST_STMT_بیان (list) = stmt_بیان;
}

/* Build a vector comparison of ARG0 and ARG1 using CODE opcode
   into a value of TYPE type.  Comparison is done via VEC_COND_EXPR.  */

ساكن ونه
build_vec_cmp (ونه_کوډ_2 کوډ, ونه type,
	       ونه arg0, ونه arg1)
{
  ونه zero_vec = build_zero_cst (type);
  ونه minus_one_vec = build_minus_one_cst (type);
  ونه cmp_type = truth_type_for (ونه_TYPE (arg0));
  ونه cmp = build2 (کوډ, cmp_type, arg0, arg1);
  أرجع build3 (VEC_COND_بیان, type, cmp, minus_one_vec, zero_vec);
}

/* Possibly warn about an address of OP never being NULL in a comparison
   operation CODE involving null.  */

ساكن فراغ
maybe_warn_for_null_پته (location_t loc, ونه op, ونه_کوډ_2 کوډ)
{
  /* Prevent warnings issued for macro expansion.  */
  إذا (!warn_پته
      || warning_suppressed_p (op, OPT_Waddress)
      || from_macro_expansion_at (loc))
    أرجع;

  إذا (ونه_کوډ (op) == NOP_بیان)
    {
      /* Allow casts to intptr_t to suppress the warning.  */
      ونه type = ونه_TYPE (op);
      إذا (ونه_کوډ (type) == INTEGER_TYPE)
	أرجع;
      op = ونه_عملوند (op, 0);
    }

  إذا (ونه_کوډ (op) == اشاره_ګر_PLUS_بیان)
    {
      /* Allow a cast to void* to suppress the warning.  */
      ونه type = ونه_TYPE (ونه_TYPE (op));
      إذا (VOID_TYPE_P (type))
	أرجع;

      /* Adding any value to a null pointer, including zero, is undefined
	 in C.  This includes the expression &p[0] where p is the null
	 pointer, although &p[0] will have been folded to p by this point
	 and so not diagnosed.  */
      إذا (کوډ == EQ_بیان)
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

  إذا (ونه_کوډ (op) != ADDR_بیان)
    أرجع;

  op = ونه_عملوند (op, 0);

  إذا (ونه_کوډ (op) == IMAGPART_بیان
      || ونه_کوډ (op) == REALPART_بیان)
    {
      /* The address of either complex part may not be null.  */
      إذا (کوډ == EQ_بیان)
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
      إذا (ونه_کوډ (op) == COMPONENT_REF)
	{
	  /* Get the member (its address is never null).  */
	  op = ونه_عملوند (op, 1);
	  اكسر;
	}

      /* Get the outer array/object to refer to in the warning.  */
      op = ونه_عملوند (op, 0);
      deref = ریښتیا;
    }

  إذا ((!deref && !decl_with_nonnull_addr_p (op))
      || from_macro_expansion_at (loc))
    أرجع;

  منطقي w;
  إذا (کوډ == EQ_بیان)
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
    inform (DECL_سرچینه_LOCATION (op), "%qD declared here", op);
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

ونه
build_دوګونی_op (location_t location, تعداد ونه_کوډ_2 کوډ,
		 ونه orig_op0, ونه orig_op1, منطقي convert_p)
{
  ونه type0, type1, orig_type0, orig_type1;
  ونه eptype;
  تعداد ونه_کوډ_2 code0, code1;
  ونه op0, op1;
  ونه ret = error_mark_غوټه;
  ثابت حرف *invalid_op_diag;
  منطقي op0_int_operands, op1_int_operands;
  منطقي int_const, int_const_or_ډکېدنه, int_operands;

  /* Expression code to give to the expression when it is built.
     Normally this is CODE, which is what the caller asked for,
     but in some special cases we change it.  */
  تعداد ونه_کوډ_2 resultcode = کوډ;

  /* Data type in which the computation is to be performed.
     In the simplest cases this is the common type of the arguments.  */
  ونه پایله_type = عدم;

  /* When the computation is in excess precision, the type of the
     final EXCESS_PRECISION_EXPR.  */
  ونه semantic_پایله_type = عدم;

  /* Nonzero means operands have already been type-converted
     in whatever way is necessary.
     Zero means they need to be converted to RESULT_TYPE.  */
  صحيح converted = 0;

  /* Nonzero means create the expression with this type, rather than
     RESULT_TYPE.  */
  ونه build_type = NULL_ونه;

  /* Nonzero means after finally constructing the expression
     convert it to this type.  */
  ونه final_type = NULL_ونه;

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
  صحيح short_ښويدنه = 0;

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
  منطقي doing_ښويدنه = خطأ;

  /* Tree holding instrumentation expression.  */
  ونه instrument_بیان = عدم;

  إذا (location == UNKNOWN_LOCATION)
    location = ننوت_location;

  op0 = orig_op0;
  op1 = orig_op1;

  op0_int_operands = بیان_INT_CONST_OPERANDS (orig_op0);
  إذا (op0_int_operands)
    op0 = remove_c_maybe_const_بیان (op0);
  op1_int_operands = بیان_INT_CONST_OPERANDS (orig_op1);
  إذا (op1_int_operands)
    op1 = remove_c_maybe_const_بیان (op1);
  int_operands = (op0_int_operands && op1_int_operands);
  إذا (int_operands)
    {
      int_const_or_ډکېدنه = (ونه_کوډ (orig_op0) == INTEGER_CST
			       && ونه_کوډ (orig_op1) == INTEGER_CST);
      int_const = (int_const_or_ډکېدنه
		   && !ونه_ډکېدنه (orig_op0)
		   && !ونه_ډکېدنه (orig_op1));
    }
  وإلا
    int_const = int_const_or_ډکېدنه = خطأ;

  /* Do not apply default conversion in mixed vector/scalar expression.  */
  إذا (convert_p
      && ویکټور_TYPE_P (ونه_TYPE (op0)) == ویکټور_TYPE_P (ونه_TYPE (op1)))
    {
      op0 = default_conversion (op0);
      op1 = default_conversion (op1);
    }

  orig_type0 = type0 = ونه_TYPE (op0);

  orig_type1 = type1 = ونه_TYPE (op1);

  /* The expression codes of the data types of the arguments tell us
     whether the arguments are integers, floating, pointers, etc.  */
  code0 = ونه_کوډ (type0);
  code1 = ونه_کوډ (type1);

  /* Strip NON_LVALUE_EXPRs, etc., since we aren't using as an lvalue.  */
  STRIP_TYPE_NOPS (op0);
  STRIP_TYPE_NOPS (op1);

  /* If an error was already reported for one of the arguments,
     avoid reporting another error.  */

  إذا (code0 == ERROR_MARK || code1 == ERROR_MARK)
    أرجع error_mark_غوټه;

  إذا (code0 == اشاره_ګر_TYPE
      && reject_gcc_builtin (op0, بیان_LOCATION (orig_op0)))
    أرجع error_mark_غوټه;

  إذا (code1 == اشاره_ګر_TYPE
      && reject_gcc_builtin (op1, بیان_LOCATION (orig_op1)))
    أرجع error_mark_غوټه;

  إذا ((invalid_op_diag
       = targetm.invalid_دوګونی_op (کوډ, type0, type1)))
    {
      error_at (location, invalid_op_diag);
      أرجع error_mark_غوټه;
    }

  بدل (کوډ)
    {
    حالة PLUS_بیان:
    حالة MINUS_بیان:
    حالة MULT_بیان:
    حالة TRUNC_DIV_بیان:
    حالة CEIL_DIV_بیان:
    حالة FLOOR_DIV_بیان:
    حالة پړاو_DIV_بیان:
    حالة EXACT_DIV_بیان:
      may_need_excess_precision = ریښتیا;
      اكسر;

    حالة EQ_بیان:
    حالة NE_بیان:
    حالة LE_بیان:
    حالة GE_بیان:
    حالة LT_بیان:
    حالة GT_بیان:
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
  إذا (ونه_کوډ (op0) == EXCESS_PRECISION_بیان)
    {
      op0 = ونه_عملوند (op0, 0);
      type0 = ونه_TYPE (op0);
    }
  وإلا إذا (may_need_excess_precision
	   && (eptype = excess_precision_type (type0)) != NULL_ونه)
    {
      type0 = eptype;
      op0 = convert (eptype, op0);
    }
  إذا (ونه_کوډ (op1) == EXCESS_PRECISION_بیان)
    {
      op1 = ونه_عملوند (op1, 0);
      type1 = ونه_TYPE (op1);
    }
  وإلا إذا (may_need_excess_precision
	   && (eptype = excess_precision_type (type1)) != NULL_ونه)
    {
      type1 = eptype;
      op1 = convert (eptype, op1);
    }

  objc_ok = objc_compare_types (type0, type1, -3, NULL_ونه);

  /* In case when one of the operands of the binary operation is
     a vector and another is a scalar -- convert scalar to vector.  */
  إذا ((gnu_ویکټور_type_p (type0) && code1 != ویکټور_TYPE)
      || (gnu_ویکټور_type_p (type1) && code0 != ویکټور_TYPE))
    {
      تعداد stv_conv convert_flag = scalar_منزل_ویکټور (location, کوډ, orig_op0,
						     orig_op1, ریښتیا);

      بدل (convert_flag)
	{
	  حالة stv_error:
	    أرجع error_mark_غوټه;
	  حالة stv_firstarg:
	    {
              منطقي maybe_const = ریښتیا;
              ونه sc;
              sc = c_fully_fold (op0, خطأ, &maybe_const);
              sc = save_بیان (sc);
              sc = convert (ونه_TYPE (type1), sc);
              op0 = build_ویکټور_from_val (type1, sc);
              إذا (!maybe_const)
                op0 = c_wrap_maybe_const (op0, ریښتیا);
              orig_type0 = type0 = ونه_TYPE (op0);
              code0 = ونه_کوډ (type0);
              converted = 1;
              اكسر;
	    }
	  حالة stv_secondarg:
	    {
	      منطقي maybe_const = ریښتیا;
	      ونه sc;
	      sc = c_fully_fold (op1, خطأ, &maybe_const);
	      sc = save_بیان (sc);
	      sc = convert (ونه_TYPE (type0), sc);
	      op1 = build_ویکټور_from_val (type0, sc);
	      إذا (!maybe_const)
		op1 = c_wrap_maybe_const (op1, ریښتیا);
	      orig_type1 = type1 = ونه_TYPE (op1);
	      code1 = ونه_کوډ (type1);
	      converted = 1;
	      اكسر;
	    }
	  افتراضي:
	    اكسر;
	}
    }

  بدل (کوډ)
    {
    حالة PLUS_بیان:
      /* Handle the pointer + int case.  */
      إذا (code0 == اشاره_ګر_TYPE
	  && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  ret = اشاره_ګر_int_مجموعه (location, PLUS_بیان, op0, op1);
	  اذهب return_build_دوګونی_op;
	}
      وإلا إذا (code1 == اشاره_ګر_TYPE
	       && (code0 == INTEGER_TYPE || code0 == BITINT_TYPE))
	{
	  ret = اشاره_ګر_int_مجموعه (location, PLUS_بیان, op1, op0);
	  اذهب return_build_دوګونی_op;
	}
      وإلا
	common = 1;
      اكسر;

    حالة MINUS_بیان:
      /* Subtraction of two similar pointers.
	 We must subtract them as integers, then divide by object size.  */
      إذا (code0 == اشاره_ګر_TYPE && code1 == اشاره_ګر_TYPE
	  && comp_موخه_types (location, type0, type1))
	{
	  ret = اشاره_ګر_diff (location, op0, op1, &instrument_بیان);
	  اذهب return_build_دوګونی_op;
	}
      /* Handle pointer minus int.  Just like pointer plus int.  */
      وإلا إذا (code0 == اشاره_ګر_TYPE
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  ret = اشاره_ګر_int_مجموعه (location, MINUS_بیان, op0, op1);
	  اذهب return_build_دوګونی_op;
	}
      وإلا
	common = 1;
      اكسر;

    حالة MULT_بیان:
      common = 1;
      اكسر;

    حالة TRUNC_DIV_بیان:
    حالة CEIL_DIV_بیان:
    حالة FLOOR_DIV_بیان:
    حالة پړاو_DIV_بیان:
    حالة EXACT_DIV_بیان:
      doing_div_or_mod = ریښتیا;
      warn_for_div_by_zero (location, op1);

      إذا ((code0 == INTEGER_TYPE || code0 == REAL_TYPE
	   || code0 == FIXED_ټکی_TYPE || code0 == BITINT_TYPE
	   || code0 == COMPLEX_TYPE
	   || gnu_ویکټور_type_p (type0))
	  && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	      || code1 == FIXED_ټکی_TYPE || code1 == BITINT_TYPE
	      || code1 == COMPLEX_TYPE
	      || gnu_ویکټور_type_p (type1)))
	{
	  تعداد ونه_کوډ_2 tcode0 = code0, tcode1 = code1;

	  إذا (code0 == COMPLEX_TYPE || code0 == ویکټور_TYPE)
	    tcode0 = ونه_کوډ (ونه_TYPE (ونه_TYPE (op0)));
	  إذا (code1 == COMPLEX_TYPE || code1 == ویکټور_TYPE)
	    tcode1 = ونه_کوډ (ونه_TYPE (ونه_TYPE (op1)));

	  إذا (!(((tcode0 == INTEGER_TYPE || tcode0 == BITINT_TYPE
		  || (tcode0 == ENUMERAL_TYPE && code0 == ویکټور_TYPE))
		 && (tcode1 == INTEGER_TYPE || tcode1 == BITINT_TYPE
		     || (tcode1 == ENUMERAL_TYPE && code1 == ویکټور_TYPE)))
		|| (tcode0 == FIXED_ټکی_TYPE && tcode1 == FIXED_ټکی_TYPE)))
	    resultcode = RDIV_بیان;
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

    حالة بټ_AND_بیان:
    حالة بټ_IOR_بیان:
    حالة بټ_XOR_بیان:
      إذا ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	shorten = -1;
      /* Allow vector types which are not floating point types.   */
      وإلا إذا (gnu_ویکټور_type_p (type0)
	       && gnu_ویکټور_type_p (type1)
	       && !ویکټور_FLOAT_TYPE_P (type0)
	       && !ویکټور_FLOAT_TYPE_P (type1))
	common = 1;
      اكسر;

    حالة TRUNC_MOD_بیان:
    حالة FLOOR_MOD_بیان:
      doing_div_or_mod = ریښتیا;
      warn_for_div_by_zero (location, op1);

      إذا (gnu_ویکټور_type_p (type0)
	  && gnu_ویکټور_type_p (type1)
	  && ونه_کوډ (ونه_TYPE (type0)) == INTEGER_TYPE
	  && ونه_کوډ (ونه_TYPE (type1)) == INTEGER_TYPE)
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

    حالة TRUTH_ANDIF_بیان:
    حالة TRUTH_ORIF_بیان:
    حالة TRUTH_AND_بیان:
    حالة TRUTH_OR_بیان:
    حالة TRUTH_XOR_بیان:
      إذا ((code0 == INTEGER_TYPE || code0 == اشاره_ګر_TYPE
	   || code0 == REAL_TYPE || code0 == COMPLEX_TYPE
	   || code0 == FIXED_ټکی_TYPE || code0 == NULLPTR_TYPE
	   || code0 == BITINT_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == اشاره_ګر_TYPE
	      || code1 == REAL_TYPE || code1 == COMPLEX_TYPE
	      || code1 == FIXED_ټکی_TYPE || code1 == NULLPTR_TYPE
	      || code1 == BITINT_TYPE))
	{
	  /* Result of these operations is always an int,
	     but that does not mean the operands should be
	     converted to ints!  */
	  پایله_type = integer_type_غوټه;
	  إذا (op0_int_operands)
	    {
	      op0 = c_objc_common_truthvalue_conversion (location, orig_op0);
	      op0 = remove_c_maybe_const_بیان (op0);
	    }
	  وإلا
	    op0 = c_objc_common_truthvalue_conversion (location, op0);
	  إذا (op1_int_operands)
	    {
	      op1 = c_objc_common_truthvalue_conversion (location, orig_op1);
	      op1 = remove_c_maybe_const_بیان (op1);
	    }
	  وإلا
	    op1 = c_objc_common_truthvalue_conversion (location, op1);
	  converted = 1;
	  boolean_op = ریښتیا;
	}
      إذا (کوډ == TRUTH_ANDIF_بیان)
	{
	  int_const_or_ډکېدنه = (int_operands
				   && ونه_کوډ (orig_op0) == INTEGER_CST
				   && (op0 == truthvalue_false_غوټه
				       || ونه_کوډ (orig_op1) == INTEGER_CST));
	  int_const = (int_const_or_ډکېدنه
		       && !ونه_ډکېدنه (orig_op0)
		       && (op0 == truthvalue_false_غوټه
			   || !ونه_ډکېدنه (orig_op1)));
	}
      وإلا إذا (کوډ == TRUTH_ORIF_بیان)
	{
	  int_const_or_ډکېدنه = (int_operands
				   && ونه_کوډ (orig_op0) == INTEGER_CST
				   && (op0 == truthvalue_true_غوټه
				       || ونه_کوډ (orig_op1) == INTEGER_CST));
	  int_const = (int_const_or_ډکېدنه
		       && !ونه_ډکېدنه (orig_op0)
		       && (op0 == truthvalue_true_غوټه
			   || !ونه_ډکېدنه (orig_op1)));
	}
      اكسر;

      /* Shift operations: result has same type as first operand;
	 always convert second operand to int.
	 Also set SHORT_SHIFT if shifting rightward.  */

    حالة RSHIFT_بیان:
      إذا (gnu_ویکټور_type_p (type0)
	  && gnu_ویکټور_type_p (type1)
	  && ونه_کوډ (ونه_TYPE (type0)) == INTEGER_TYPE
	  && ونه_کوډ (ونه_TYPE (type1)) == INTEGER_TYPE
	  && معلوم_eq (TYPE_ویکټور_SUBPARTS (type0),
		       TYPE_ویکټور_SUBPARTS (type1)))
	{
	  پایله_type = type0;
	  converted = 1;
	}
      وإلا إذا ((code0 == INTEGER_TYPE || code0 == FIXED_ټکی_TYPE
		|| code0 == BITINT_TYPE
		|| (gnu_ویکټور_type_p (type0)
		    && ونه_کوډ (ونه_TYPE (type0)) == INTEGER_TYPE))
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  doing_ښويدنه = ریښتیا;
	  إذا (ونه_کوډ (op1) == INTEGER_CST)
	    {
	      إذا (ونه_int_cst_sgn (op1) < 0)
		{
		  int_const = خطأ;
		  إذا (c_inhibit_evaluation_warnings == 0)
		    warning_at (location, OPT_Wshift_شمېر_negative,
				"right shift count is negative");
		}
	      وإلا إذا (code0 == ویکټور_TYPE)
		{
		  إذا (compare_ونه_int (op1,
					TYPE_PRECISION (ونه_TYPE (type0)))
		      >= 0)
		    {
		      int_const = خطأ;
		      إذا (c_inhibit_evaluation_warnings == 0)
			warning_at (location, OPT_Wshift_شمېر_ډکېدنه,
				    "right shift count >= width of vector element");
		    }
		}
	      وإلا
		{
		  إذا (!integer_zerop (op1))
		    short_ښويدنه = 1;

		  إذا (compare_ونه_int (op1, TYPE_PRECISION (type0)) >= 0)
		    {
		      int_const = خطأ;
		      إذا (c_inhibit_evaluation_warnings == 0)
			warning_at (location, OPT_Wshift_شمېر_ډکېدنه,
				    "right shift count >= width of type");
		    }
		}
	    }

	  /* Use the type of the value to be shifted.  */
	  پایله_type = type0;
	  /* Avoid converting op1 to result_type later.  */
	  converted = 1;
	}
      اكسر;

    حالة LSHIFT_بیان:
      إذا (gnu_ویکټور_type_p (type0)
	  && gnu_ویکټور_type_p (type1)
	  && ونه_کوډ (ونه_TYPE (type0)) == INTEGER_TYPE
	  && ونه_کوډ (ونه_TYPE (type1)) == INTEGER_TYPE
	  && معلوم_eq (TYPE_ویکټور_SUBPARTS (type0),
		       TYPE_ویکټور_SUBPARTS (type1)))
	{
	  پایله_type = type0;
	  converted = 1;
	}
      وإلا إذا ((code0 == INTEGER_TYPE || code0 == FIXED_ټکی_TYPE
		|| code0 == BITINT_TYPE
		|| (gnu_ویکټور_type_p (type0)
		    && ونه_کوډ (ونه_TYPE (type0)) == INTEGER_TYPE))
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  doing_ښويدنه = ریښتیا;
	  إذا (ونه_کوډ (op0) == INTEGER_CST
	      && ونه_int_cst_sgn (op0) < 0
	      && !TYPE_ډکېدنه_WRAPS (type0))
	    {
	      /* Don't reject a left shift of a negative value in a context
		 where a constant expression is needed in C90.  */
	      إذا (flag_isoc99)
		int_const = خطأ;
	      إذا (c_inhibit_evaluation_warnings == 0)
		warning_at (location, OPT_Wshift_negative_ارزښت,
			    "left shift of negative value");
	    }
	  إذا (ونه_کوډ (op1) == INTEGER_CST)
	    {
	      إذا (ونه_int_cst_sgn (op1) < 0)
		{
		  int_const = خطأ;
		  إذا (c_inhibit_evaluation_warnings == 0)
		    warning_at (location, OPT_Wshift_شمېر_negative,
				"left shift count is negative");
		}
	      وإلا إذا (code0 == ویکټور_TYPE)
		{
		  إذا (compare_ونه_int (op1,
					TYPE_PRECISION (ونه_TYPE (type0)))
		      >= 0)
		    {
		      int_const = خطأ;
		      إذا (c_inhibit_evaluation_warnings == 0)
			warning_at (location, OPT_Wshift_شمېر_ډکېدنه,
				    "left shift count >= width of vector element");
		    }
		}
	      وإلا إذا (compare_ونه_int (op1, TYPE_PRECISION (type0)) >= 0)
		{
		  int_const = خطأ;
		  إذا (c_inhibit_evaluation_warnings == 0)
		    warning_at (location, OPT_Wshift_شمېر_ډکېدنه,
				"left shift count >= width of type");
		}
	      وإلا إذا (ونه_کوډ (op0) == INTEGER_CST
		       && maybe_warn_ښويدنه_ډکېدنه (location, op0, op1)
		       && flag_isoc99)
		int_const = خطأ;
	    }

	  /* Use the type of the value to be shifted.  */
	  پایله_type = type0;
	  /* Avoid converting op1 to result_type later.  */
	  converted = 1;
	}
      اكسر;

    حالة EQ_بیان:
    حالة NE_بیان:
      إذا (gnu_ویکټور_type_p (type0) && gnu_ویکټور_type_p (type1))
        {
          ونه intt;
	  إذا (!ویکټور_types_compatible_elements_p (type0, type1))
            {
              error_at (location, "comparing vectors with different "
                                  "element types");
              أرجع error_mark_غوټه;
            }

	  إذا (maybe_ne (TYPE_ویکټور_SUBPARTS (type0),
			TYPE_ویکټور_SUBPARTS (type1)))
            {
              error_at (location, "comparing vectors with different "
                                  "number of elements");
              أرجع error_mark_غوټه;
            }

	  /* It's not precisely specified how the usual arithmetic
	     conversions apply to the vector types.  Here, we use
	     the unsigned type if one of the operands is signed and
	     the other one is unsigned.  */
	  إذا (TYPE_UNSIGNED (type0) != TYPE_UNSIGNED (type1))
	    {
	      إذا (!TYPE_UNSIGNED (type0))
		op0 = build1 (VIEW_CONVERT_بیان, type1, op0);
	      وإلا
		op1 = build1 (VIEW_CONVERT_بیان, type0, op1);
	      warning_at (location, OPT_Wsign_compare, "comparison between "
			  "types %qT and %qT", type0, type1);
	    }

          /* Always construct signed integer vector type.  */
	  إذا (ویکټور_BOOLEAN_TYPE_P (type0) && ویکټور_BOOLEAN_TYPE_P (type1))
	    پایله_type = type0;
	  وإلا
	    {
	      خپلکاری nelts = TYPE_ویکټور_SUBPARTS (type0);

	      intt = c_common_type_for_اندازه (GET_ډېرپېښ_BITSIZE
					     (SCALAR_TYPE_ډېرپېښ
						(ونه_TYPE (type0))), 0);
	      إذا (!intt)
		{
		  error_at (location, "could not find an integer type "
				      "of the same size as %qT",
			    ونه_TYPE (type0));
		  أرجع error_mark_غوټه;
		}
	      پایله_type = build_opaque_ویکټور_type (intt, nelts);
	    }
          converted = 1;
	  ret = build_vec_cmp (resultcode, پایله_type, op0, op1);
	  اذهب return_build_دوګونی_op;
        }
      إذا (FLOAT_TYPE_P (type0) || FLOAT_TYPE_P (type1))
	warning_at (location,
		    OPT_Wfloat_equal,
		    "comparing floating-point with %<==%> or %<!=%> is unsafe");
      /* Result of comparison is always int,
	 but don't convert the args to int!  */
      build_type = integer_type_غوټه;
      إذا ((code0 == INTEGER_TYPE || code0 == REAL_TYPE || code0 == BITINT_TYPE
	   || code0 == FIXED_ټکی_TYPE || code0 == COMPLEX_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	      || code1 == BITINT_TYPE
	      || code1 == FIXED_ټکی_TYPE || code1 == COMPLEX_TYPE))
	short_compare = 1;
      وإلا إذا (code0 == اشاره_ګر_TYPE
	       && (code1 == NULLPTR_TYPE
		   || null_اشاره_ګر_constant_p (orig_op1)))
	{
	  maybe_warn_for_null_پته (location, op0, کوډ);
	  پایله_type = type0;
	}
      وإلا إذا (code1 == اشاره_ګر_TYPE
	       && (code0 == NULLPTR_TYPE
		   || null_اشاره_ګر_constant_p (orig_op0)))
	{
	  maybe_warn_for_null_پته (location, op1, کوډ);
	  پایله_type = type1;
	}
      وإلا إذا (code0 == اشاره_ګر_TYPE && code1 == اشاره_ګر_TYPE)
	{
	  ونه tt0 = ونه_TYPE (type0);
	  ونه tt1 = ونه_TYPE (type1);
	  addr_space_t as0 = TYPE_ADDR_SPACE (tt0);
	  addr_space_t as1 = TYPE_ADDR_SPACE (tt1);
	  addr_space_t as_common = ADDR_SPACE_GENERIC;

	  /* Anything compares with void *.  void * compares with anything.
	     Otherwise, the targets must be compatible
	     and both must be object or both incomplete.  */
	  إذا (comp_موخه_types (location, type0, type1))
	    پایله_type = common_اشاره_ګر_type (type0, type1, NULL_ونه);
	  وإلا إذا (!addr_space_superset (as0, as1, &as_common))
	    {
	      error_at (location, "comparison of pointers to "
			"disjoint address spaces");
	      أرجع error_mark_غوټه;
	    }
	  وإلا إذا (VOID_TYPE_P (tt0) && !TYPE_ATOMIC (tt0))
	    {
	      إذا (pedantic && ونه_کوډ (tt1) == FUNCTION_TYPE)
		pedwarn (location, OPT_Wpedantic, "ISO C forbids "
			 "comparison of %<void *%> with function pointer");
	    }
	  وإلا إذا (VOID_TYPE_P (tt1) && !TYPE_ATOMIC (tt1))
	    {
	      إذا (pedantic && ونه_کوډ (tt0) == FUNCTION_TYPE)
		pedwarn (location, OPT_Wpedantic, "ISO C forbids "
			 "comparison of %<void *%> with function pointer");
	    }
	  وإلا
	    /* Avoid warning about the volatile ObjC EH puts on decls.  */
	    إذا (!objc_ok)
	      pedwarn (location, OPT_Wcompare_distinct_اشاره_ګر_types,
		       "comparison of distinct pointer types lacks a cast");

	  إذا (پایله_type == NULL_ونه)
	    {
	      صحيح qual = ENCODE_QUAL_ADDR_SPACE (as_common);
	      پایله_type = c_build_اشاره_ګر_type
			      (c_build_qualified_type (void_type_غوټه, qual));
	    }
	}
      وإلا إذا (code0 == اشاره_ګر_TYPE
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  پایله_type = type0;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}
      وإلا إذا ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	       && code1 == اشاره_ګر_TYPE)
	{
	  پایله_type = type1;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}
      /* 6.5.9: One of the following shall hold:
	 -- both operands have type nullptr_t;  */
      وإلا إذا (code0 == NULLPTR_TYPE && code1 == NULLPTR_TYPE)
	{
	  پایله_type = nullptr_type_غوټه;
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
      وإلا إذا (code0 == NULLPTR_TYPE && null_اشاره_ګر_constant_p (orig_op1))
	پایله_type = (INTEGRAL_TYPE_P (type1)
		       ? c_build_اشاره_ګر_type (type1) : type1);
      وإلا إذا (code1 == NULLPTR_TYPE && null_اشاره_ګر_constant_p (orig_op0))
	پایله_type = (INTEGRAL_TYPE_P (type0)
		       ? c_build_اشاره_ګر_type (type0) : type0);
      إذا ((C_BOOLEAN_TYPE_P (ونه_TYPE (orig_op0))
	   || truth_ارزښت_p (ونه_کوډ (orig_op0)))
	  ^ (C_BOOLEAN_TYPE_P (ونه_TYPE (orig_op1))
	     || truth_ارزښت_p (ونه_کوډ (orig_op1))))
	maybe_warn_bool_compare (location, کوډ, orig_op0, orig_op1);
      اكسر;

    حالة LE_بیان:
    حالة GE_بیان:
    حالة LT_بیان:
    حالة GT_بیان:
      إذا (gnu_ویکټور_type_p (type0) && gnu_ویکټور_type_p (type1))
        {
          ونه intt;
	  إذا (!ویکټور_types_compatible_elements_p (type0, type1))
            {
              error_at (location, "comparing vectors with different "
                                  "element types");
              أرجع error_mark_غوټه;
            }

	  إذا (maybe_ne (TYPE_ویکټور_SUBPARTS (type0),
			TYPE_ویکټور_SUBPARTS (type1)))
            {
              error_at (location, "comparing vectors with different "
                                  "number of elements");
              أرجع error_mark_غوټه;
            }

	  /* It's not precisely specified how the usual arithmetic
	     conversions apply to the vector types.  Here, we use
	     the unsigned type if one of the operands is signed and
	     the other one is unsigned.  */
	  إذا (TYPE_UNSIGNED (type0) != TYPE_UNSIGNED (type1))
	    {
	      إذا (!TYPE_UNSIGNED (type0))
		op0 = build1 (VIEW_CONVERT_بیان, type1, op0);
	      وإلا
		op1 = build1 (VIEW_CONVERT_بیان, type0, op1);
	      warning_at (location, OPT_Wsign_compare, "comparison between "
			  "types %qT and %qT", type0, type1);
	    }

          /* Always construct signed integer vector type.  */
          intt = c_common_type_for_اندازه (GET_ډېرپېښ_BITSIZE
					 (SCALAR_TYPE_ډېرپېښ
					  (ونه_TYPE (type0))), 0);
	  إذا (!intt)
	    {
	      error_at (location, "could not find an integer type "
				  "of the same size as %qT",
			ونه_TYPE (type0));
	      أرجع error_mark_غوټه;
	    }
          پایله_type = build_opaque_ویکټور_type (intt,
						  TYPE_ویکټور_SUBPARTS (type0));
          converted = 1;
	  ret = build_vec_cmp (resultcode, پایله_type, op0, op1);
	  اذهب return_build_دوګونی_op;
        }
      build_type = integer_type_غوټه;
      إذا ((code0 == INTEGER_TYPE || code0 == REAL_TYPE
	   || code0 == BITINT_TYPE || code0 == FIXED_ټکی_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	      || code1 == BITINT_TYPE || code1 == FIXED_ټکی_TYPE))
	short_compare = 1;
      وإلا إذا (code0 == اشاره_ګر_TYPE && code1 == اشاره_ګر_TYPE)
	{
	  addr_space_t as0 = TYPE_ADDR_SPACE (ونه_TYPE (type0));
	  addr_space_t as1 = TYPE_ADDR_SPACE (ونه_TYPE (type1));
	  addr_space_t as_common;

	  إذا (comp_موخه_types (location, type0, type1))
	    {
	      پایله_type = common_اشاره_ګر_type (type0, type1, NULL_ونه);
	      إذا (!COMPLETE_TYPE_P (ونه_TYPE (type0))
		  != !COMPLETE_TYPE_P (ونه_TYPE (type1)))
		pedwarn_c99 (location, OPT_Wpedantic,
			     "comparison of complete and incomplete pointers");
	      وإلا إذا (ونه_کوډ (ونه_TYPE (type0)) == FUNCTION_TYPE)
		pedwarn (location, OPT_Wpedantic, "ISO C forbids "
			 "ordered comparisons of pointers to functions");
	      وإلا إذا (null_اشاره_ګر_constant_p (orig_op0)
		       || null_اشاره_ګر_constant_p (orig_op1))
		warning_at (location, OPT_Wextra,
			    "ordered comparison of pointer with null pointer");

	    }
	  وإلا إذا (!addr_space_superset (as0, as1, &as_common))
	    {
	      error_at (location, "comparison of pointers to "
			"disjoint address spaces");
	      أرجع error_mark_غوټه;
	    }
	  وإلا
	    {
	      صحيح qual = ENCODE_QUAL_ADDR_SPACE (as_common);
	      پایله_type = c_build_اشاره_ګر_type
			      (c_build_qualified_type (void_type_غوټه, qual));
              pedwarn (location, OPT_Wcompare_distinct_اشاره_ګر_types,
                       "comparison of distinct pointer types lacks a cast");
	    }
	}
      وإلا إذا (code0 == اشاره_ګر_TYPE && null_اشاره_ګر_constant_p (orig_op1))
	{
	  پایله_type = type0;
	  إذا (pedantic)
	    pedwarn (location, OPT_Wpedantic,
		     "ordered comparison of pointer with integer zero");
	  وإلا إذا (extra_warnings)
	    warning_at (location, OPT_Wextra,
			"ordered comparison of pointer with integer zero");
	}
      وإلا إذا (code1 == اشاره_ګر_TYPE && null_اشاره_ګر_constant_p (orig_op0))
	{
	  پایله_type = type1;
	  إذا (pedantic)
	    pedwarn (location, OPT_Wpedantic,
		     "ordered comparison of pointer with integer zero");
	  وإلا إذا (extra_warnings)
	    warning_at (location, OPT_Wextra,
			"ordered comparison of pointer with integer zero");
	}
      وإلا إذا (code0 == اشاره_ګر_TYPE
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  پایله_type = type0;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}
      وإلا إذا ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	       && code1 == اشاره_ګر_TYPE)
	{
	  پایله_type = type1;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}

      إذا ((code0 == اشاره_ګر_TYPE || code1 == اشاره_ګر_TYPE)
	  && current_function_decl != NULL_ونه
	  && sanitize_flags_p (SANITIZE_اشاره_ګر_COMPARE))
	{
	  op0 = save_بیان (c_fully_fold (op0, خطأ, عدم));
	  op1 = save_بیان (c_fully_fold (op1, خطأ, عدم));

	  ونه tt = builtin_decl_explicit (BUILT_دننه_ASAN_اشاره_ګر_COMPARE);
	  instrument_بیان = build_call_بیان_loc (location, tt, 2, op0, op1);
	}

      إذا ((C_BOOLEAN_TYPE_P (ونه_TYPE (orig_op0))
	   || truth_ارزښت_p (ونه_کوډ (orig_op0)))
	  ^ (C_BOOLEAN_TYPE_P (ونه_TYPE (orig_op1))
	     || truth_ارزښت_p (ونه_کوډ (orig_op1))))
	maybe_warn_bool_compare (location, کوډ, orig_op0, orig_op1);
      اكسر;

    حالة MIN_بیان:
    حالة MAX_بیان:
      /* Used for OpenMP atomics.  */
      gcc_assert (flag_openmp);
      common = 1;
      اكسر;

    افتراضي:
      gcc_unreachable ();
    }

  إذا (code0 == ERROR_MARK || code1 == ERROR_MARK)
    أرجع error_mark_غوټه;

  إذا (gnu_ویکټور_type_p (type0)
      && gnu_ویکټور_type_p (type1)
      && (!ونه_int_cst_equal (TYPE_اندازه (type0), TYPE_اندازه (type1))
	  || !ویکټور_types_compatible_elements_p (type0, type1)))
    {
      gcc_rich_location richloc (location);
      maybe_range_label_for_ونه_type_mismatch
	label_for_op0 (orig_op0, orig_op1),
	label_for_op1 (orig_op1, orig_op0);
      richloc.maybe_جمع_کړه_بیان (orig_op0, &label_for_op0, highlight_colors::lhs);
      richloc.maybe_جمع_کړه_بیان (orig_op1, &label_for_op1, highlight_colors::rhs);
      دوګونی_op_error (&richloc, کوډ, type0, type1);
      أرجع error_mark_غوټه;
    }

  إذا ((code0 == INTEGER_TYPE || code0 == REAL_TYPE || code0 == COMPLEX_TYPE
       || code0 == FIXED_ټکی_TYPE || code0 == BITINT_TYPE
       || gnu_ویکټور_type_p (type0))
      && (code1 == INTEGER_TYPE || code1 == REAL_TYPE || code1 == COMPLEX_TYPE
	  || code1 == FIXED_ټکی_TYPE || code1 == BITINT_TYPE
	  || gnu_ویکټور_type_p (type1)))
    {
      منطقي لومړی_complex = (code0 == COMPLEX_TYPE);
      منطقي دوهم_complex = (code1 == COMPLEX_TYPE);
      صحيح none_complex = (!لومړی_complex && !دوهم_complex);

      إذا (shorten || common || short_compare)
	{
	  پایله_type = c_common_type (type0, type1);
	  do_warn_double_promotion (پایله_type, type0, type1,
				    "implicit conversion from %qT to %qT "
				    "to match other operand of binary "
				    "expression",
				    location);
	  إذا (پایله_type == error_mark_غوټه)
	    أرجع error_mark_غوټه;
	}

      إذا (لومړی_complex != دوهم_complex
	  && (کوډ == PLUS_بیان
	      || کوډ == MINUS_بیان
	      || کوډ == MULT_بیان
	      || (کوډ == TRUNC_DIV_بیان && لومړی_complex))
	  && ونه_کوډ (ونه_TYPE (پایله_type)) == REAL_TYPE
	  && flag_signed_zeros)
	{
	  /* An operation on mixed real/complex operands must be
	     handled specially, but the language-independent code can
	     more easily optimize the plain complex arithmetic if
	     -fno-signed-zeros.  */
	  ونه real_type = ونه_TYPE (پایله_type);
	  ونه real, imag;
	  إذا (type0 != orig_type0 || type1 != orig_type1)
	    {
	      gcc_assert (may_need_excess_precision && common);
	      semantic_پایله_type = c_common_type (orig_type0, orig_type1);
	    }
	  إذا (لومړی_complex)
	    {
	      إذا (ونه_TYPE (op0) != پایله_type)
		op0 = convert_and_check (location, پایله_type, op0);
	      إذا (ونه_TYPE (op1) != real_type)
		op1 = convert_and_check (location, real_type, op1);
	    }
	  وإلا
	    {
	      إذا (ونه_TYPE (op0) != real_type)
		op0 = convert_and_check (location, real_type, op0);
	      إذا (ونه_TYPE (op1) != پایله_type)
		op1 = convert_and_check (location, پایله_type, op1);
	    }
	  إذا (ونه_کوډ (op0) == ERROR_MARK || ونه_کوډ (op1) == ERROR_MARK)
	    أرجع error_mark_غوټه;
	  إذا (لومړی_complex)
	    {
	      op0 = save_بیان (op0);
	      real = build_unary_op (بیان_LOCATION (orig_op0), REALPART_بیان,
				     op0, ریښتیا);
	      imag = build_unary_op (بیان_LOCATION (orig_op0), IMAGPART_بیان,
				     op0, ریښتیا);
	      بدل (کوډ)
		{
		حالة MULT_بیان:
		حالة TRUNC_DIV_بیان:
		  op1 = save_بیان (op1);
		  imag = build2 (resultcode, real_type, imag, op1);
		  /* Fall through.  */
		حالة PLUS_بیان:
		حالة MINUS_بیان:
		  real = build2 (resultcode, real_type, real, op1);
		  اكسر;
		افتراضي:
		  gcc_unreachable();
		}
	    }
	  وإلا
	    {
	      op1 = save_بیان (op1);
	      real = build_unary_op (بیان_LOCATION (orig_op1), REALPART_بیان,
				     op1, ریښتیا);
	      imag = build_unary_op (بیان_LOCATION (orig_op1), IMAGPART_بیان,
				     op1, ریښتیا);
	      بدل (کوډ)
		{
		حالة MULT_بیان:
		  op0 = save_بیان (op0);
		  imag = build2 (resultcode, real_type, op0, imag);
		  /* Fall through.  */
		حالة PLUS_بیان:
		  real = build2 (resultcode, real_type, op0, real);
		  اكسر;
		حالة MINUS_بیان:
		  real = build2 (resultcode, real_type, op0, real);
		  imag = build1 (NEGATE_بیان, real_type, imag);
		  اكسر;
		افتراضي:
		  gcc_unreachable();
		}
	    }
	  ret = build2 (COMPLEX_بیان, پایله_type, real, imag);
	  اذهب return_build_دوګونی_op;
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
	  final_type = پایله_type;
	  پایله_type = shorten_دوګونی_op (پایله_type, op0, op1,
					   shorten == -1);
	}

      /* Shifts can be shortened if shifting right.  */

      إذا (short_ښويدنه)
	{
	  صحيح unsigned_arg;
	  ونه arg0 = get_narrower (op0, &unsigned_arg);

	  final_type = پایله_type;

	  إذا (arg0 == op0 && final_type == ونه_TYPE (op0))
	    unsigned_arg = TYPE_UNSIGNED (ونه_TYPE (op0));

	  إذا (TYPE_PRECISION (ونه_TYPE (arg0)) < TYPE_PRECISION (پایله_type)
	      && ونه_int_cst_sgn (op1) > 0
	      /* We can shorten only if the shift count is less than the
		 number of bits in the smaller type size.  */
	      && compare_ونه_int (op1, TYPE_PRECISION (ونه_TYPE (arg0))) < 0
	      /* We cannot drop an unsigned shift after sign-extension.  */
	      && (!TYPE_UNSIGNED (final_type) || unsigned_arg))
	    {
	      /* Do an unsigned shift if the operand was zero-extended.  */
	      پایله_type
		= c_common_signed_or_unsigned_type (unsigned_arg,
						    ونه_TYPE (arg0));
	      /* Convert value-to-be-shifted to that type.  */
	      إذا (ونه_TYPE (op0) != پایله_type)
		op0 = convert (پایله_type, op0);
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
	  ونه xop0 = op0, xop1 = op1, xresult_type = پایله_type;
	  تعداد ونه_کوډ_2 xresultcode = resultcode;
	  ونه val
	    = shorten_compare (location, &xop0, &xop1, &xresult_type,
			       &xresultcode);

	  إذا (val != NULL_ونه)
	    {
	      ret = val;
	      اذهب return_build_دوګونی_op;
	    }

	  op0 = xop0, op1 = xop1;
	  converted = 1;
	  resultcode = xresultcode;

	  إذا (c_inhibit_evaluation_warnings == 0 && !c_دننه_omp_for)
	    {
	      منطقي op0_maybe_const = ریښتیا;
	      منطقي op1_maybe_const = ریښتیا;
	      ونه orig_op0_folded, orig_op1_folded;

	      إذا (دننه_late_دوګونی_op)
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
		  op0 = c_fully_fold (op0, require_constant_ارزښت,
				      &op0_maybe_const);
		  op1 = c_fully_fold (op1, require_constant_ارزښت,
				      &op1_maybe_const);
		  c_inhibit_evaluation_warnings--;
		  orig_op0_folded = c_fully_fold (orig_op0,
						  require_constant_ارزښت,
						  عدم);
		  orig_op1_folded = c_fully_fold (orig_op1,
						  require_constant_ارزښت,
						  عدم);
		}

	      إذا (warn_sign_compare)
		warn_for_sign_compare (location, orig_op0_folded,
				       orig_op1_folded, op0, op1,
				       پایله_type, resultcode);
	      إذا (!دننه_late_دوګونی_op && !int_operands)
		{
		  إذا (!op0_maybe_const || ونه_کوډ (op0) != INTEGER_CST)
		    op0 = c_wrap_maybe_const (op0, !op0_maybe_const);
		  إذا (!op1_maybe_const || ونه_کوډ (op1) != INTEGER_CST)
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

  إذا (!پایله_type)
    {
      /* Favor showing any expression locations that are available. */
      op_location_t oploc (location, UNKNOWN_LOCATION);
      دوګونی_op_rich_location richloc (oploc, orig_op0, orig_op1, ریښتیا);
      دوګونی_op_error (&richloc, کوډ, ونه_TYPE (op0), ونه_TYPE (op1));
      أرجع error_mark_غوټه;
    }

  إذا (build_type == NULL_ونه)
    {
      build_type = پایله_type;
      إذا ((type0 != orig_type0 || type1 != orig_type1)
	  && !boolean_op)
	{
	  gcc_assert (may_need_excess_precision && common);
	  semantic_پایله_type = c_common_type (orig_type0, orig_type1);
	}
    }

  إذا (!converted)
    {
      op0 = ep_convert_and_check (location, پایله_type, op0,
				  semantic_پایله_type);
      op1 = ep_convert_and_check (location, پایله_type, op1,
				  semantic_پایله_type);

      /* This can happen if one operand has a vector type, and the other
	 has a different type.  */
      إذا (ونه_کوډ (op0) == ERROR_MARK || ونه_کوډ (op1) == ERROR_MARK)
	أرجع error_mark_غوټه;
    }

  إذا (sanitize_flags_p ((SANITIZE_ښويدنه
			 | SANITIZE_DIVIDE
			 | SANITIZE_FLOAT_DIVIDE
			 | SANITIZE_SI_ډکېدنه))
      && current_function_decl != NULL_ونه
      && (doing_div_or_mod || doing_ښويدنه)
      && !require_constant_ارزښت)
    {
      /* OP0 and/or OP1 might have side-effects.  */
      op0 = save_بیان (op0);
      op1 = save_بیان (op1);
      op0 = c_fully_fold (op0, خطأ, عدم);
      op1 = c_fully_fold (op1, خطأ, عدم);
      إذا (doing_div_or_mod && (sanitize_flags_p ((SANITIZE_DIVIDE
						  | SANITIZE_FLOAT_DIVIDE
						  | SANITIZE_SI_ډکېدنه))))
	instrument_بیان = ubsan_instrument_division (location, op0, op1);
      وإلا إذا (doing_ښويدنه && sanitize_flags_p (SANITIZE_ښويدنه))
	instrument_بیان = ubsan_instrument_ښويدنه (location, کوډ, op0, op1);
    }

  /* Treat expressions in initializers specially as they can't trap.  */
  إذا (int_const_or_ډکېدنه)
    ret = (require_constant_ارزښت
	   ? fold_build2_initializer_loc (location, resultcode, build_type,
					  op0, op1)
	   : fold_build2_loc (location, resultcode, build_type, op0, op1));
  وإلا
    ret = build2 (resultcode, build_type, op0, op1);
  إذا (final_type != NULL_ونه)
    ret = convert (final_type, ret);

 return_build_دوګونی_op:
  gcc_assert (ret != error_mark_غوټه);
  إذا (ونه_کوډ (ret) == INTEGER_CST && !ونه_ډکېدنه (ret) && !int_const)
    ret = (int_operands
	   ? note_integer_operands (ret)
	   : build1 (NOP_بیان, ونه_TYPE (ret), ret));
  وإلا إذا (ونه_کوډ (ret) != INTEGER_CST && int_operands
	   && !دننه_late_دوګونی_op)
    ret = note_integer_operands (ret);
  protected_سېټ_بیان_location (ret, location);

  إذا (instrument_بیان != عدم)
    ret = fold_build2 (COMPOUND_بیان, ونه_TYPE (ret),
		       instrument_بیان, ret);

  إذا (semantic_پایله_type)
    ret = build1_loc (location, EXCESS_PRECISION_بیان,
		      semantic_پایله_type, ret);

  أرجع ret;
}


/* Convert EXPR to be a truth-value (type TYPE), validating its type for this
   purpose.  LOCATION is the source location for the expression.  */

ونه
c_objc_common_truthvalue_conversion (location_t location, ونه بیان, ونه type)
{
  منطقي int_const, int_operands;

  بدل (ونه_کوډ (ونه_TYPE (بیان)))
    {
    حالة ARRAY_TYPE:
      error_at (location, "used array that cannot be converted to pointer where scalar is required");
      أرجع error_mark_غوټه;

    حالة ریکارډ_TYPE:
      error_at (location, "used struct type value where scalar is required");
      أرجع error_mark_غوټه;

    حالة UNION_TYPE:
      error_at (location, "used union type value where scalar is required");
      أرجع error_mark_غوټه;

    حالة VOID_TYPE:
      error_at (location, "void value not ignored as it ought to be");
      أرجع error_mark_غوټه;

    حالة اشاره_ګر_TYPE:
      إذا (reject_gcc_builtin (بیان))
	أرجع error_mark_غوټه;
      اكسر;

    حالة FUNCTION_TYPE:
      gcc_unreachable ();

    حالة ویکټور_TYPE:
      error_at (location, "used vector type where scalar is required");
      أرجع error_mark_غوټه;

    افتراضي:
      اكسر;
    }

  /* Conversion of a floating constant to boolean goes through here
     and yields an integer constant expression.  Otherwise, the result
     is only an integer constant expression if the argument is.  */
  int_const = ((ونه_کوډ (بیان) == INTEGER_CST && !ونه_ډکېدنه (بیان))
	       || ((ونه_کوډ (بیان) == REAL_CST
		    || ونه_کوډ (بیان) == COMPLEX_CST)
		   && (ونه_کوډ (type) == BOOLEAN_TYPE
		       || (ونه_کوډ (type) == ENUMERAL_TYPE
			   && ENUM_UNDERLYING_TYPE (type) != NULL_ونه
			   && (ونه_کوډ (ENUM_UNDERLYING_TYPE (type))
			       == BOOLEAN_TYPE)))));
  int_operands = بیان_INT_CONST_OPERANDS (بیان);
  إذا (int_operands && ونه_کوډ (بیان) != INTEGER_CST)
    {
      بیان = remove_c_maybe_const_بیان (بیان);
      بیان = build2 (NE_بیان, type, بیان,
		     convert (ونه_TYPE (بیان), integer_zero_غوټه));
      بیان = note_integer_operands (بیان);
    }
  وإلا
    {
      /* ??? Should we also give an error for vectors rather than leaving
	 those to give errors later?  */
      بیان = c_common_truthvalue_conversion (location, بیان);
      بیان = fold_convert_loc (location, type, بیان);
    }

  إذا (ونه_کوډ (بیان) == INTEGER_CST && int_operands && !int_const)
    {
      إذا (ونه_ډکېدنه (بیان))
	أرجع بیان;
      وإلا
	أرجع note_integer_operands (بیان);
    }
  إذا (ونه_کوډ (بیان) == INTEGER_CST && !int_const)
    أرجع build1 (NOP_بیان, ونه_TYPE (بیان), بیان);
  أرجع بیان;
}


/* Convert EXPR to a contained DECL, updating *TC, *TI and *SE as
   required.  */

ونه
c_بیان_منزل_decl (ونه بیان, منطقي *tc ATTRIBUTE_ناکارول_شوی, منطقي *se)
{
  إذا (ونه_کوډ (بیان) == COMPOUND_LITERAL_بیان)
    {
      ونه decl = COMPOUND_LITERAL_بیان_DECL (بیان);
      /* Executing a compound literal inside a function reinitializes
	 it.  */
      إذا (!ونه_STATIC (decl))
	*se = ریښتیا;
      أرجع decl;
    }
  وإلا
    أرجع بیان;
}

/* Generate OMP construct CODE, with BODY and CLAUSES as its compound
   statement.  LOC is the location of the construct.  */

ونه
c_پای_omp_construct (location_t loc, تعداد ونه_کوډ_2 کوډ, ونه body,
			ونه clauses)
{
  body = c_پای_ټکی_compound_stmt (loc, body, ریښتیا);

  ونه stmt = make_غوټه (کوډ);
  ونه_TYPE (stmt) = void_type_غوټه;
  OMP_BODY (stmt) = body;
  OMP_CLAUSES (stmt) = clauses;
  سېټ_بیان_LOCATION (stmt, loc);

  أرجع جمع_کړه_stmt (stmt);
}

/* Generate OACC_DATA, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the OACC_DATA.  */

ونه
c_پای_oacc_معلومات (location_t loc, ونه clauses, ونه بلاک)
{
  ونه stmt;

  بلاک = c_پای_ټکی_compound_stmt (loc, بلاک, ریښتیا);

  stmt = make_غوټه (OACC_معلومات);
  ونه_TYPE (stmt) = void_type_غوټه;
  OACC_معلومات_CLAUSES (stmt) = clauses;
  OACC_معلومات_BODY (stmt) = بلاک;
  سېټ_بیان_LOCATION (stmt, loc);

  أرجع جمع_کړه_stmt (stmt);
}

/* Generate OACC_HOST_DATA, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the OACC_HOST_DATA.  */

ونه
c_پای_oacc_host_معلومات (location_t loc, ونه clauses, ونه بلاک)
{
  ونه stmt;

  بلاک = c_پای_ټکی_compound_stmt (loc, بلاک, ریښتیا);

  stmt = make_غوټه (OACC_HOST_معلومات);
  ونه_TYPE (stmt) = void_type_غوټه;
  OACC_HOST_معلومات_CLAUSES (stmt) = clauses;
  OACC_HOST_معلومات_BODY (stmt) = بلاک;
  سېټ_بیان_LOCATION (stmt, loc);

  أرجع جمع_کړه_stmt (stmt);
}

/* Like c_begin_compound_stmt, except force the retention of the BLOCK.  */

ونه
c_begin_omp_parallel (فراغ)
{
  ونه بلاک;

  keep_بل_level ();
  بلاک = c_begin_compound_stmt (ریښتیا);

  أرجع بلاک;
}

/* Generate OMP_PARALLEL, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the OMP_PARALLEL.  */

ونه
c_پای_omp_parallel (location_t loc, ونه clauses, ونه بلاک)
{
  ونه stmt;

  بلاک = c_پای_ټکی_compound_stmt (loc, بلاک, ریښتیا);

  stmt = make_غوټه (OMP_PARALLEL);
  ونه_TYPE (stmt) = void_type_غوټه;
  OMP_PARALLEL_CLAUSES (stmt) = clauses;
  OMP_PARALLEL_BODY (stmt) = بلاک;
  سېټ_بیان_LOCATION (stmt, loc);

  أرجع جمع_کړه_stmt (stmt);
}

/* Like c_begin_compound_stmt, except force the retention of the BLOCK.  */

ونه
c_begin_omp_task (فراغ)
{
  ونه بلاک;

  keep_بل_level ();
  بلاک = c_begin_compound_stmt (ریښتیا);

  أرجع بلاک;
}

/* Generate OMP_TASK, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the #pragma.  */

ونه
c_پای_omp_task (location_t loc, ونه clauses, ونه بلاک)
{
  ونه stmt;

  بلاک = c_پای_ټکی_compound_stmt (loc, بلاک, ریښتیا);

  stmt = make_غوټه (OMP_TASK);
  ونه_TYPE (stmt) = void_type_غوټه;
  OMP_TASK_CLAUSES (stmt) = clauses;
  OMP_TASK_BODY (stmt) = بلاک;
  سېټ_بیان_LOCATION (stmt, loc);

  أرجع جمع_کړه_stmt (stmt);
}

/* Generate GOMP_cancel call for #pragma omp cancel.  */

فراغ
c_پای_omp_cancel (location_t loc, ونه clauses)
{
  ونه fn = builtin_decl_explicit (BUILT_دننه_GOMP_CANCEL);
  صحيح ماسک = 0;
  إذا (omp_پیدا_کړه_clause (clauses, OMP_CLAUSE_PARALLEL))
    ماسک = 1;
  وإلا إذا (omp_پیدا_کړه_clause (clauses, OMP_CLAUSE_FOR))
    ماسک = 2;
  وإلا إذا (omp_پیدا_کړه_clause (clauses, OMP_CLAUSE_SECTIONS))
    ماسک = 4;
  وإلا إذا (omp_پیدا_کړه_clause (clauses, OMP_CLAUSE_TASKGROUP))
    ماسک = 8;
  وإلا
    {
      error_at (loc, "%<#pragma omp cancel%> must specify one of "
		     "%<parallel%>, %<for%>, %<sections%> or %<taskgroup%> "
		     "clauses");
      أرجع;
    }
  ونه ifc = omp_پیدا_کړه_clause (clauses, OMP_CLAUSE_IF);
  إذا (ifc != NULL_ونه)
    {
      إذا (OMP_CLAUSE_IF_MODIFIER (ifc) != ERROR_MARK
	  && OMP_CLAUSE_IF_MODIFIER (ifc) != VOID_CST)
	error_at (OMP_CLAUSE_LOCATION (ifc),
		  "expected %<cancel%> %<if%> clause modifier");
      وإلا
	{
	  ونه ifc2 = omp_پیدا_کړه_clause (OMP_CLAUSE_CHAIN (ifc), OMP_CLAUSE_IF);
	  إذا (ifc2 != NULL_ونه)
	    {
	      gcc_assert (OMP_CLAUSE_IF_MODIFIER (ifc) == VOID_CST
			  && OMP_CLAUSE_IF_MODIFIER (ifc2) != ERROR_MARK
			  && OMP_CLAUSE_IF_MODIFIER (ifc2) != VOID_CST);
	      error_at (OMP_CLAUSE_LOCATION (ifc2),
			"expected %<cancel%> %<if%> clause modifier");
	    }
	}

      ونه type = ونه_TYPE (OMP_CLAUSE_IF_بیان (ifc));
      ifc = fold_build2_loc (OMP_CLAUSE_LOCATION (ifc), NE_بیان,
			     boolean_type_غوټه, OMP_CLAUSE_IF_بیان (ifc),
			     build_zero_cst (type));
    }
  وإلا
    ifc = boolean_true_غوټه;
  ونه stmt = build_call_بیان_loc (loc, fn, 2,
				   build_int_cst (integer_type_غوټه, ماسک),
				   ifc);
  جمع_کړه_stmt (stmt);
}

/* Generate GOMP_cancellation_point call for
   #pragma omp cancellation point.  */

فراغ
c_پای_omp_cancellation_ټکی (location_t loc, ونه clauses)
{
  ونه fn = builtin_decl_explicit (BUILT_دننه_GOMP_CANCELLATION_ټکی);
  صحيح ماسک = 0;
  إذا (omp_پیدا_کړه_clause (clauses, OMP_CLAUSE_PARALLEL))
    ماسک = 1;
  وإلا إذا (omp_پیدا_کړه_clause (clauses, OMP_CLAUSE_FOR))
    ماسک = 2;
  وإلا إذا (omp_پیدا_کړه_clause (clauses, OMP_CLAUSE_SECTIONS))
    ماسک = 4;
  وإلا إذا (omp_پیدا_کړه_clause (clauses, OMP_CLAUSE_TASKGROUP))
    ماسک = 8;
  وإلا
    {
      error_at (loc, "%<#pragma omp cancellation point%> must specify one of "
		     "%<parallel%>, %<for%>, %<sections%> or %<taskgroup%> "
		     "clauses");
      أرجع;
    }
  ونه stmt = build_call_بیان_loc (loc, fn, 1,
				   build_int_cst (integer_type_غوټه, ماسک));
  جمع_کړه_stmt (stmt);
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

ساكن ونه
handle_omp_array_sections_1 (ونه c, ونه t, vec<ونه> &types,
			     منطقي &maybe_zero_len, بینښه صحيح &لومړی_non_one,
			     تعداد c_omp_region_type ort)
{
  ونه ret, ټیټ_bound, اوږدتیا, type;
  منطقي openacc = (ort & C_ORT_ACC) != 0;
  إذا (ونه_کوډ (t) != OMP_ARRAY_SECTION)
    {
      إذا (error_عملوند_p (t))
	أرجع error_mark_غوټه;
      c_omp_پته_inspector ai (OMP_CLAUSE_LOCATION (c), t);
      ret = t;
      إذا (OMP_CLAUSE_کوډ (c) != OMP_CLAUSE_AFFINITY
	  && OMP_CLAUSE_کوډ (c) != OMP_CLAUSE_DEPEND
	  && TYPE_ATOMIC (strip_array_types (ونه_TYPE (t))))
	{
	  error_at (OMP_CLAUSE_LOCATION (c), "%<_Atomic%> %qE in %qs clause",
		    t, omp_clause_کوډ_name[OMP_CLAUSE_کوډ (c)]);
	  أرجع error_mark_غوټه;
	}
      إذا (!ai.check_clause (c))
	أرجع error_mark_غوټه;
      وإلا إذا (ai.component_access_p ()
	       && (OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_MAP
		   || OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_منزل
		   || OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_FROM))
	t = ai.get_ریښه_غړی (ریښتیا);
      وإلا
	t = ai.unconverted_ref_origin ();
      إذا (t == error_mark_غوټه)
	أرجع error_mark_غوټه;
      إذا (!VAR_P (t)
	  && (ort == C_ORT_ACC || !بیان_P (t))
	  && ونه_کوډ (t) != PARM_DECL)
	{
	  إذا (DECL_P (t))
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD is not a variable in %qs clause", t,
		      omp_clause_کوډ_name[OMP_CLAUSE_کوډ (c)]);
	  وإلا
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qE is not a variable in %qs clause", t,
		      omp_clause_کوډ_name[OMP_CLAUSE_کوډ (c)]);
	  أرجع error_mark_غوټه;
	}
      وإلا إذا (OMP_CLAUSE_کوډ (c) != OMP_CLAUSE_AFFINITY
	       && OMP_CLAUSE_کوډ (c) != OMP_CLAUSE_DEPEND
	       && TYPE_ATOMIC (ونه_TYPE (t)))
	{
	  error_at (OMP_CLAUSE_LOCATION (c), "%<_Atomic%> %qD in %qs clause",
		    t, omp_clause_کوډ_name[OMP_CLAUSE_کوډ (c)]);
	  أرجع error_mark_غوټه;
	}
      وإلا إذا (OMP_CLAUSE_کوډ (c) != OMP_CLAUSE_AFFINITY
	       && OMP_CLAUSE_کوډ (c) != OMP_CLAUSE_DEPEND
	       && VAR_P (t)
	       && DECL_THREAD_LOCAL_P (t))
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "%qD is threadprivate variable in %qs clause", t,
		    omp_clause_کوډ_name[OMP_CLAUSE_کوډ (c)]);
	  أرجع error_mark_غوټه;
	}
      إذا ((OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_AFFINITY
	   || OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_DEPEND)
	  && TYPE_ATOMIC (ونه_TYPE (t))
	  && اشاره_ګر_TYPE_P (ونه_TYPE (t)))
	{
	  /* If the array section is pointer based and the pointer
	     itself is _Atomic qualified, we need to atomically load
	     the pointer.  */
	  ret = convert_lvalue_منزل_rvalue (OMP_CLAUSE_LOCATION (c),
					  ret, خطأ, خطأ);
	}
      أرجع ret;
    }

  ret = handle_omp_array_sections_1 (c, ونه_عملوند (t, 0), types,
				     maybe_zero_len, لومړی_non_one, ort);
  إذا (ret == error_mark_غوټه || ret == NULL_ونه)
    أرجع ret;

  type = ونه_TYPE (ret);
  ټیټ_bound = ونه_عملوند (t, 1);
  اوږدتیا = ونه_عملوند (t, 2);

  إذا (ټیټ_bound == error_mark_غوټه || اوږدتیا == error_mark_غوټه)
    أرجع error_mark_غوټه;

  إذا (ټیټ_bound && !INTEGRAL_TYPE_P (ونه_TYPE (ټیټ_bound)))
    {
      error_at (OMP_CLAUSE_LOCATION (c),
		"low bound %qE of array section does not have integral type",
		ټیټ_bound);
      أرجع error_mark_غوټه;
    }
  إذا (اوږدتیا && !INTEGRAL_TYPE_P (ونه_TYPE (اوږدتیا)))
    {
      error_at (OMP_CLAUSE_LOCATION (c),
		"length %qE of array section does not have integral type",
		اوږدتیا);
      أرجع error_mark_غوټه;
    }
  إذا (ټیټ_bound
      && ونه_کوډ (ټیټ_bound) == INTEGER_CST
      && TYPE_PRECISION (ونه_TYPE (ټیټ_bound))
	 > TYPE_PRECISION (sizetype))
    ټیټ_bound = fold_convert (sizetype, ټیټ_bound);
  إذا (اوږدتیا
      && ونه_کوډ (اوږدتیا) == INTEGER_CST
      && TYPE_PRECISION (ونه_TYPE (اوږدتیا))
	 > TYPE_PRECISION (sizetype))
    اوږدتیا = fold_convert (sizetype, اوږدتیا);
  إذا (ټیټ_bound == NULL_ونه)
    ټیټ_bound = integer_zero_غوټه;
  إذا (OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_MAP
      && (OMP_CLAUSE_MAP_ډول (c) == GOMP_MAP_ATTACH
	  || OMP_CLAUSE_MAP_ډول (c) == GOMP_MAP_DETACH))
    {
      إذا (اوږدتیا != integer_one_غوټه)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "expected single pointer in %qs clause",
		    user_omp_clause_کوډ_name (c, openacc));
	  أرجع error_mark_غوټه;
	}
    }
  إذا (اوږدتیا != NULL_ونه)
    {
      إذا (!integer_nonzerop (اوږدتیا))
	{
	  إذا (OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_AFFINITY
	      || OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_DEPEND
	      || OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_REDUCTION
	      || OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_دننه_REDUCTION
	      || OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_TASK_REDUCTION)
	    {
	      إذا (integer_zerop (اوږدتیا))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "zero length array section in %qs clause",
			    omp_clause_کوډ_name[OMP_CLAUSE_کوډ (c)]);
		  أرجع error_mark_غوټه;
		}
	    }
	  وإلا
	    maybe_zero_len = ریښتیا;
	}
      إذا (لومړی_non_one == types.اوږدتیا ()
	  && (ونه_کوډ (اوږدتیا) != INTEGER_CST || integer_onep (اوږدتیا)))
	لومړی_non_one++;
    }
  إذا (ونه_کوډ (type) == ARRAY_TYPE)
    {
      إذا (اوږدتیا == NULL_ونه
	  && (TYPE_DOMAIN (type) == NULL_ونه
	      || TYPE_MAX_ارزښت (TYPE_DOMAIN (type)) == NULL_ونه))
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "for unknown bound array type length expression must "
		    "be specified");
	  أرجع error_mark_غوټه;
	}
      إذا (ونه_کوډ (ټیټ_bound) == INTEGER_CST
	  && ونه_int_cst_sgn (ټیټ_bound) == -1)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "negative low bound in array section in %qs clause",
		    omp_clause_کوډ_name[OMP_CLAUSE_کوډ (c)]);
	  أرجع error_mark_غوټه;
	}
      إذا (اوږدتیا != NULL_ونه
	  && ونه_کوډ (اوږدتیا) == INTEGER_CST
	  && ونه_int_cst_sgn (اوږدتیا) == -1)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "negative length in array section in %qs clause",
		    omp_clause_کوډ_name[OMP_CLAUSE_کوډ (c)]);
	  أرجع error_mark_غوټه;
	}
      إذا (TYPE_DOMAIN (type)
	  && TYPE_MAX_ارزښت (TYPE_DOMAIN (type))
	  && ونه_کوډ (TYPE_MAX_ارزښت (TYPE_DOMAIN (type)))
			== INTEGER_CST)
	{
	  ونه اندازه
	    = fold_convert (sizetype, TYPE_MAX_ارزښت (TYPE_DOMAIN (type)));
	  اندازه = اندازه_binop (PLUS_بیان, اندازه, اندازه_one_غوټه);
	  إذا (ونه_کوډ (ټیټ_bound) == INTEGER_CST)
	    {
	      إذا (ونه_int_cst_lt (اندازه, ټیټ_bound))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "low bound %qE above array section size "
			    "in %qs clause", ټیټ_bound,
			    omp_clause_کوډ_name[OMP_CLAUSE_کوډ (c)]);
		  أرجع error_mark_غوټه;
		}
	      إذا (ونه_int_cst_equal (اندازه, ټیټ_bound))
		{
		  إذا (OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_AFFINITY
		      || OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_DEPEND
		      || OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_REDUCTION
		      || OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_دننه_REDUCTION
		      || OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_TASK_REDUCTION)
		    {
		      error_at (OMP_CLAUSE_LOCATION (c),
				"zero length array section in %qs clause",
				omp_clause_کوډ_name[OMP_CLAUSE_کوډ (c)]);
		      أرجع error_mark_غوټه;
		    }
		  maybe_zero_len = ریښتیا;
		}
	      وإلا إذا (اوږدتیا == NULL_ونه
		       && لومړی_non_one == types.اوږدتیا ()
		       && ونه_int_cst_equal
			    (TYPE_MAX_ارزښت (TYPE_DOMAIN (type)),
			     ټیټ_bound))
		لومړی_non_one++;
	    }
	  وإلا إذا (اوږدتیا == NULL_ونه)
	    {
	      إذا (OMP_CLAUSE_کوډ (c) != OMP_CLAUSE_AFFINITY
		  && OMP_CLAUSE_کوډ (c) != OMP_CLAUSE_DEPEND
		  && OMP_CLAUSE_کوډ (c) != OMP_CLAUSE_REDUCTION
		  && OMP_CLAUSE_کوډ (c) != OMP_CLAUSE_دننه_REDUCTION
		  && OMP_CLAUSE_کوډ (c) != OMP_CLAUSE_TASK_REDUCTION)
		maybe_zero_len = ریښتیا;
	      إذا (لومړی_non_one == types.اوږدتیا ())
		لومړی_non_one++;
	    }
	  إذا (اوږدتیا && ونه_کوډ (اوږدتیا) == INTEGER_CST)
	    {
	      إذا (ونه_int_cst_lt (اندازه, اوږدتیا))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "length %qE above array section size "
			    "in %qs clause", اوږدتیا,
			    omp_clause_کوډ_name[OMP_CLAUSE_کوډ (c)]);
		  أرجع error_mark_غوټه;
		}
	      إذا (ونه_کوډ (ټیټ_bound) == INTEGER_CST)
		{
		  ونه lbpluslen
		    = اندازه_binop (PLUS_بیان,
				  fold_convert (sizetype, ټیټ_bound),
				  fold_convert (sizetype, اوږدتیا));
		  إذا (ونه_کوډ (lbpluslen) == INTEGER_CST
		      && ونه_int_cst_lt (اندازه, lbpluslen))
		    {
		      error_at (OMP_CLAUSE_LOCATION (c),
				"high bound %qE above array section size "
				"in %qs clause", lbpluslen,
				omp_clause_کوډ_name[OMP_CLAUSE_کوډ (c)]);
		      أرجع error_mark_غوټه;
		    }
		}
	    }
	}
      وإلا إذا (اوږدتیا == NULL_ونه)
	{
	  إذا (OMP_CLAUSE_کوډ (c) != OMP_CLAUSE_AFFINITY
	      && OMP_CLAUSE_کوډ (c) != OMP_CLAUSE_DEPEND
	      && OMP_CLAUSE_کوډ (c) != OMP_CLAUSE_REDUCTION
	      && OMP_CLAUSE_کوډ (c) != OMP_CLAUSE_دننه_REDUCTION
	      && OMP_CLAUSE_کوډ (c) != OMP_CLAUSE_TASK_REDUCTION)
	    maybe_zero_len = ریښتیا;
	  إذا (لومړی_non_one == types.اوږدتیا ())
	    لومړی_non_one++;
	}

      /* For [lb:] we will need to evaluate lb more than once.  */
      إذا (اوږدتیا == NULL_ونه && OMP_CLAUSE_کوډ (c) != OMP_CLAUSE_DEPEND)
	{
	  ونه lb = save_بیان (ټیټ_bound);
	  إذا (lb != ټیټ_bound)
	    {
	      ونه_عملوند (t, 1) = lb;
	      ټیټ_bound = lb;
	    }
	}
    }
  وإلا إذا (ونه_کوډ (type) == اشاره_ګر_TYPE)
    {
      إذا (اوږدتیا == NULL_ونه)
	{
	  إذا (ونه_کوډ (ret) == PARM_DECL && C_ARRAY_PARAMETER (ret))
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "for array function parameter length expression "
		      "must be specified");
	  وإلا
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "for pointer type length expression must be specified");
	  أرجع error_mark_غوټه;
	}
      إذا (اوږدتیا != NULL_ونه
	  && ونه_کوډ (اوږدتیا) == INTEGER_CST
	  && ونه_int_cst_sgn (اوږدتیا) == -1)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "negative length in array section in %qs clause",
		    omp_clause_کوډ_name[OMP_CLAUSE_کوډ (c)]);
	  أرجع error_mark_غوټه;
	}
      /* If there is a pointer type anywhere but in the very first
	 array-section-subscript, the array section could be non-contiguous.  */
      إذا (OMP_CLAUSE_کوډ (c) != OMP_CLAUSE_DEPEND
	  && OMP_CLAUSE_کوډ (c) != OMP_CLAUSE_AFFINITY
	  && ونه_کوډ (ونه_عملوند (t, 0)) == OMP_ARRAY_SECTION)
	{
	  /* If any prior dimension has a non-one length, then deem this
	     array section as non-contiguous.  */
	  لكل (ونه d = ونه_عملوند (t, 0);
	       ونه_کوډ (d) == OMP_ARRAY_SECTION;
	       d = ونه_عملوند (d, 0))
	    {
	      ونه d_اوږدتیا = ونه_عملوند (d, 2);
	      إذا (d_اوږدتیا == NULL_ونه || !integer_onep (d_اوږدتیا))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "array section is not contiguous in %qs clause",
			    omp_clause_کوډ_name[OMP_CLAUSE_کوډ (c)]);
		  أرجع error_mark_غوټه;
		}
	    }
	}
    }
  وإلا
    {
      error_at (OMP_CLAUSE_LOCATION (c),
		"%qE does not have pointer or array type", ret);
      أرجع error_mark_غوټه;
    }
  إذا (OMP_CLAUSE_کوډ (c) != OMP_CLAUSE_DEPEND)
    types.خوندي_ټېل (ونه_TYPE (ret));
  /* We will need to evaluate lb more than once.  */
  ونه lb = save_بیان (ټیټ_bound);
  إذا (lb != ټیټ_bound)
    {
      ونه_عملوند (t, 1) = lb;
      ټیټ_bound = lb;
    }
  ret = build_array_ref (OMP_CLAUSE_LOCATION (c), ret, ټیټ_bound);
  أرجع ret;
}

/* Handle array sections for clause C.  */

ساكن منطقي
handle_omp_array_sections (ونه &c, تعداد c_omp_region_type ort)
{
  منطقي maybe_zero_len = خطأ;
  بینښه صحيح لومړی_non_one = 0;
  auto_vec<ونه, 10> types;
  ونه *tp = &OMP_CLAUSE_DECL (c);
  إذا ((OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_DEPEND
       || OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_AFFINITY)
      && OMP_ITERATOR_DECL_P (*tp))
    tp = &ونه_ارزښت (*tp);
  ونه لومړی = handle_omp_array_sections_1 (c, *tp, types,
					    maybe_zero_len, لومړی_non_one,
					    ort);
  إذا (لومړی == error_mark_غوټه)
    أرجع ریښتیا;
  إذا (لومړی == NULL_ونه)
    أرجع خطأ;
  إذا (OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_DEPEND
      || OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_AFFINITY)
    {
      ونه t = *tp;
      ونه tem = NULL_ونه;
      /* Need to evaluate side effects in the length expressions
	 if any.  */
      طالما (ونه_کوډ (t) == ونه_LIST)
	{
	  إذا (ونه_ارزښت (t) && ونه_SIDE_EFFECTS (ونه_ارزښت (t)))
	    {
	      إذا (tem == NULL_ونه)
		tem = ونه_ارزښت (t);
	      وإلا
		tem = build2 (COMPOUND_بیان, ونه_TYPE (tem),
			      ونه_ارزښت (t), tem);
	    }
	  t = ونه_CHAIN (t);
	}
      إذا (tem)
	لومړی = build2 (COMPOUND_بیان, ونه_TYPE (لومړی), tem, لومړی);
      لومړی = c_fully_fold (لومړی, خطأ, عدم, ریښتیا);
      *tp = لومړی;
    }
  وإلا
    {
      بینښه صحيح عدد = types.اوږدتیا (), i;
      ونه t, side_effects = NULL_ونه, اندازه = NULL_ونه;
      ونه condition = NULL_ونه;

      إذا (int_اندازه_دننه_بایټونه (ونه_TYPE (لومړی)) <= 0)
	maybe_zero_len = ریښتیا;

      لكل (i = عدد, t = OMP_CLAUSE_DECL (c); i > 0;
	   t = ونه_عملوند (t, 0))
	{
	  ونه ټیټ_bound = ونه_عملوند (t, 1);
	  ونه اوږدتیا = ونه_عملوند (t, 2);

	  i--;
	  إذا (ټیټ_bound
	      && ونه_کوډ (ټیټ_bound) == INTEGER_CST
	      && TYPE_PRECISION (ونه_TYPE (ټیټ_bound))
		 > TYPE_PRECISION (sizetype))
	    ټیټ_bound = fold_convert (sizetype, ټیټ_bound);
	  إذا (اوږدتیا
	      && ونه_کوډ (اوږدتیا) == INTEGER_CST
	      && TYPE_PRECISION (ونه_TYPE (اوږدتیا))
		 > TYPE_PRECISION (sizetype))
	    اوږدتیا = fold_convert (sizetype, اوږدتیا);
	  إذا (ټیټ_bound == NULL_ونه)
	    ټیټ_bound = integer_zero_غوټه;
	  إذا (!maybe_zero_len && i > لومړی_non_one)
	    {
	      إذا (integer_nonzerop (ټیټ_bound))
		اذهب do_warn_noncontiguous;
	      إذا (اوږدتیا != NULL_ونه
		  && ونه_کوډ (اوږدتیا) == INTEGER_CST
		  && TYPE_DOMAIN (types[i])
		  && TYPE_MAX_ارزښت (TYPE_DOMAIN (types[i]))
		  && ونه_کوډ (TYPE_MAX_ارزښت (TYPE_DOMAIN (types[i])))
		     == INTEGER_CST)
		{
		  ونه اندازه;
		  اندازه = اندازه_binop (PLUS_بیان,
				     TYPE_MAX_ارزښت (TYPE_DOMAIN (types[i])),
				     اندازه_one_غوټه);
		  إذا (!ونه_int_cst_equal (اوږدتیا, اندازه))
		    {
		     do_warn_noncontiguous:
		      error_at (OMP_CLAUSE_LOCATION (c),
				"array section is not contiguous in %qs "
				"clause",
				omp_clause_کوډ_name[OMP_CLAUSE_کوډ (c)]);
		      أرجع ریښتیا;
		    }
		}
	      إذا (اوږدتیا != NULL_ونه
		  && ونه_SIDE_EFFECTS (اوږدتیا))
		{
		  إذا (side_effects == NULL_ونه)
		    side_effects = اوږدتیا;
		  وإلا
		    side_effects = build2 (COMPOUND_بیان,
					   ونه_TYPE (side_effects),
					   اوږدتیا, side_effects);
		}
	    }
	  وإلا
	    {
	      ونه l;

	      إذا (i > لومړی_non_one
		  && ((اوږدتیا && integer_nonzerop (اوږدتیا))
		      || OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_REDUCTION
		      || OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_دننه_REDUCTION
		      || OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_TASK_REDUCTION))
		استمر;
	      إذا (اوږدتیا)
		l = fold_convert (sizetype, اوږدتیا);
	      وإلا
		{
		  l = اندازه_binop (PLUS_بیان,
				  TYPE_MAX_ارزښت (TYPE_DOMAIN (types[i])),
				  اندازه_one_غوټه);
		  l = اندازه_binop (MINUS_بیان, l,
				  fold_convert (sizetype, ټیټ_bound));
		}
	      إذا (i > لومړی_non_one)
		{
		  l = fold_build2 (NE_بیان, boolean_type_غوټه, l,
				   اندازه_zero_غوټه);
		  إذا (condition == NULL_ونه)
		    condition = l;
		  وإلا
		    condition = fold_build2 (بټ_AND_بیان, boolean_type_غوټه,
					     l, condition);
		}
	      وإلا إذا (اندازه == NULL_ونه)
		{
		  اندازه = اندازه_دننه_بایټونه (ونه_TYPE (types[i]));
		  ونه eltype = ونه_TYPE (types[عدد - 1]);
		  طالما (ونه_کوډ (eltype) == ARRAY_TYPE)
		    eltype = ونه_TYPE (eltype);
		  إذا (OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_REDUCTION
		      || OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_دننه_REDUCTION
		      || OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_TASK_REDUCTION)
		    {
		      إذا (integer_zerop (اندازه)
			  || integer_zerop (اندازه_دننه_بایټونه (eltype)))
			{
			  error_at (OMP_CLAUSE_LOCATION (c),
				    "zero length array section in %qs clause",
				    omp_clause_کوډ_name[OMP_CLAUSE_کوډ (c)]);
			  أرجع error_mark_غوټه;
			}
		      اندازه = اندازه_binop (EXACT_DIV_بیان, اندازه,
					 اندازه_دننه_بایټونه (eltype));
		    }
		  اندازه = اندازه_binop (MULT_بیان, اندازه, l);
		  إذا (condition)
		    اندازه = fold_build3 (COND_بیان, sizetype, condition,
					اندازه, اندازه_zero_غوټه);
		}
	      وإلا
		اندازه = اندازه_binop (MULT_بیان, اندازه, l);
	    }
	}
      إذا (side_effects)
	اندازه = build2 (COMPOUND_بیان, sizetype, side_effects, اندازه);
      إذا (OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_REDUCTION
	  || OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_دننه_REDUCTION
	  || OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_TASK_REDUCTION)
	{
	  اندازه = اندازه_binop (MINUS_بیان, اندازه, اندازه_one_غوټه);
	  اندازه = c_fully_fold (اندازه, خطأ, عدم);
	  اندازه = save_بیان (اندازه);
	  ونه شاخص_type = build_شاخص_type (اندازه);
	  ونه eltype = ونه_TYPE (لومړی);
	  طالما (ونه_کوډ (eltype) == ARRAY_TYPE)
	    eltype = ونه_TYPE (eltype);
	  ونه type = c_build_array_type (eltype, شاخص_type);
	  ونه ptype = c_build_اشاره_ګر_type (eltype);
	  إذا (ونه_کوډ (ونه_TYPE (t)) == ARRAY_TYPE)
	    t = build_fold_addr_بیان (t);
	  ونه t2 = build_fold_addr_بیان (لومړی);
	  t2 = fold_convert_loc (OMP_CLAUSE_LOCATION (c),
				 ptrdiff_type_غوټه, t2);
	  t2 = fold_build2_loc (OMP_CLAUSE_LOCATION (c), MINUS_بیان,
				ptrdiff_type_غوټه, t2,
				fold_convert_loc (OMP_CLAUSE_LOCATION (c),
						  ptrdiff_type_غوټه, t));
	  t2 = c_fully_fold (t2, خطأ, عدم);
	  إذا (ونه_ځاییږي_shwi_p (t2))
	    t = build2 (MEM_REF, type, t,
			build_int_cst (ptype, ونه_منزل_shwi (t2)));
	  وإلا
	    {
	      t2 = fold_convert_loc (OMP_CLAUSE_LOCATION (c), sizetype, t2);
	      t = build2_loc (OMP_CLAUSE_LOCATION (c), اشاره_ګر_PLUS_بیان,
			      ونه_TYPE (t), t, t2);
	      t = build2 (MEM_REF, type, t, build_int_cst (ptype, 0));
	    }
	  OMP_CLAUSE_DECL (c) = t;
	  أرجع خطأ;
	}
      لومړی = c_fully_fold (لومړی, خطأ, عدم);
      OMP_CLAUSE_DECL (c) = لومړی;
      إذا (OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_HAS_DEVICE_ADDR)
	أرجع خطأ;
      /* Don't set OMP_CLAUSE_SIZE for bare attach/detach clauses.  */
      إذا (OMP_CLAUSE_کوډ (c) != OMP_CLAUSE_MAP
	  || (OMP_CLAUSE_MAP_ډول (c) != GOMP_MAP_ATTACH
	      && OMP_CLAUSE_MAP_ډول (c) != GOMP_MAP_DETACH
	      && OMP_CLAUSE_MAP_ډول (c) != GOMP_MAP_FORCE_DETACH))
	{
	  إذا (اندازه)
	    اندازه = c_fully_fold (اندازه, خطأ, عدم);
	  OMP_CLAUSE_اندازه (c) = اندازه;
	}

      إذا (OMP_CLAUSE_کوډ (c) != OMP_CLAUSE_MAP)
	أرجع خطأ;

      auto_vec<omp_addr_token *, 10> addr_نښې;

      إذا (!omp_parse_بیان (addr_نښې, لومړی))
	أرجع ریښتیا;

      c_omp_پته_inspector ai (OMP_CLAUSE_LOCATION (c), t);

      ونه nc = ai.expand_map_clause (c, لومړی, addr_نښې, ort);
      إذا (nc != error_mark_غوټه)
	{
	  کارول نطاق omp_addr_tokenizer;

	  إذا (ai.maybe_zero_اوږدتیا_array_section (c))
	    OMP_CLAUSE_MAP_MAYBE_ZERO_اوږدتیا_ARRAY_SECTION (c) = 1;

	  /* !!! If we're accessing a base decl via chained access
	     methods (e.g. multiple indirections), duplicate clause
	     detection won't work properly.  Skip it in that case.  */
	  إذا ((addr_نښې[0]->type == STRUCTURE_بنسټ
	       || addr_نښې[0]->type == ARRAY_بنسټ)
	      && addr_نښې[0]->u.structure_بنسټ_ډول == بنسټ_DECL
	      && addr_نښې[1]->type == ACCESS_لاره
	      && omp_access_chain_p (addr_نښې, 1))
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

ساكن ونه
c_clone_omp_udr (ونه stmt, ونه omp_decl1, ونه omp_decl2,
		 ونه decl, ونه placeholder)
{
  copy_body_معلومات id;
  hash_map<ونه, ونه> decl_map;

  decl_map.put (omp_decl1, placeholder);
  decl_map.put (omp_decl2, decl);
  memset (&id, 0, حجم (id));
  id.src_fn = DECL_CONTEXT (omp_decl1);
  id.dst_fn = current_function_decl;
  id.src_cfun = DECL_STRUCT_FUNCTION (id.src_fn);
  id.decl_map = &decl_map;

  id.copy_decl = copy_decl_no_change;
  id.transform_call_ګراف_څنډې = CB_CGE_DUPLICATE;
  id.transform_new_cfg = ریښتیا;
  id.transform_return_منزل_modify = خطأ;
  id.eh_lp_nr = 0;
  walk_ونه (&stmt, copy_ونه_body_r, &id, عدم);
  أرجع stmt;
}

/* Helper function of c_finish_omp_clauses, called via walk_tree.
   Find OMP_CLAUSE_PLACEHOLDER (passed in DATA) in *TP.  */

ساكن ونه
c_پیدا_کړه_omp_placeholder_r (ونه *tp, صحيح *, فراغ *معلومات)
{
  إذا (*tp == (ونه) معلومات)
    أرجع *tp;
  أرجع NULL_ونه;
}

/* Similarly, but also walk aggregate fields.  */

بنية c_پیدا_کړه_omp_var_s { ونه var; hash_سېټ<ونه> *pset; };

ساكن ونه
c_پیدا_کړه_omp_var_r (ونه *tp, صحيح *, فراغ *معلومات)
{
  إذا (*tp == ((بنية c_پیدا_کړه_omp_var_s *) معلومات)->var)
    أرجع *tp;
  إذا (ریکارډ_OR_UNION_TYPE_P (*tp))
    {
      ونه ډګر_2;
      hash_سېټ<ونه> *pset = ((بنية c_پیدا_کړه_omp_var_s *) معلومات)->pset;

      لكل (ډګر_2 = TYPE_FIELDS (*tp); ډګر_2;
	   ډګر_2 = DECL_CHAIN (ډګر_2))
	إذا (ونه_کوډ (ډګر_2) == ډګر_DECL)
	  {
	    ونه ret = walk_ونه (&DECL_ډګر_دننه_واټن (ډګر_2),
				  c_پیدا_کړه_omp_var_r, معلومات, pset);
	    إذا (ret)
	      أرجع ret;
	    ret = walk_ونه (&DECL_اندازه (ډګر_2), c_پیدا_کړه_omp_var_r, معلومات, pset);
	    إذا (ret)
	      أرجع ret;
	    ret = walk_ونه (&DECL_اندازه_UNIT (ډګر_2), c_پیدا_کړه_omp_var_r, معلومات,
			     pset);
	    إذا (ret)
	      أرجع ret;
	    ret = walk_ونه (&ونه_TYPE (ډګر_2), c_پیدا_کړه_omp_var_r, معلومات, pset);
	    إذا (ret)
	      أرجع ret;
	  }
    }
  وإلا إذا (INTEGRAL_TYPE_P (*tp))
    أرجع walk_ونه (&TYPE_MAX_ارزښت (*tp), c_پیدا_کړه_omp_var_r, معلومات,
		      ((بنية c_پیدا_کړه_omp_var_s *) معلومات)->pset);
  أرجع NULL_ونه;
}

/* Finish OpenMP iterators ITER.  Return true if they are erroneous
   and clauses containing them should be removed.  */

ساكن منطقي
c_omp_پای_iterators (ونه iter)
{
  منطقي ret = خطأ;
  لكل (ونه it = iter; it; it = ونه_CHAIN (it))
    {
      ونه var = OMP_ITERATOR_VAR (it);
      ونه begin = OMP_ITERATOR_BEGIN (it);
      ونه پای_ټکی = OMP_ITERATOR_پای_ټکی (it);
      ونه ګام = OMP_ITERATOR_ګام (it);
      ونه orig_ګام;
      ونه type = ونه_TYPE (var);
      location_t loc = DECL_سرچینه_LOCATION (var);
      إذا (type == error_mark_غوټه)
	{
	  ret = ریښتیا;
	  استمر;
	}
      إذا (!INTEGRAL_TYPE_P (type) && !اشاره_ګر_TYPE_P (type))
	{
	  error_at (loc, "iterator %qD has neither integral nor pointer type",
		    var);
	  ret = ریښتیا;
	  استمر;
	}
      وإلا إذا (TYPE_ATOMIC (type))
	{
	  error_at (loc, "iterator %qD has %<_Atomic%> qualified type", var);
	  ret = ریښتیا;
	  استمر;
	}
      وإلا إذا (TYPE_READONLY (type))
	{
	  error_at (loc, "iterator %qD has const qualified type", var);
	  ret = ریښتیا;
	  استمر;
	}
      وإلا إذا (ګام == error_mark_غوټه
	       || ونه_TYPE (ګام) == error_mark_غوټه)
	{
	  ret = ریښتیا;
	  استمر;
	}
      وإلا إذا (!INTEGRAL_TYPE_P (ونه_TYPE (ګام)))
	{
	  error_at (بیان_LOC_OR_LOC (ګام, loc),
		    "iterator step with non-integral type");
	  ret = ریښتیا;
	  استمر;
	}
      begin = c_fully_fold (build_c_cast (loc, type, begin), خطأ, عدم);
      پای_ټکی = c_fully_fold (build_c_cast (loc, type, پای_ټکی), خطأ, عدم);
      orig_ګام = save_بیان (c_fully_fold (ګام, خطأ, عدم));
      ونه stype = اشاره_ګر_TYPE_P (type) ? sizetype : type;
      ګام = c_fully_fold (build_c_cast (loc, stype, orig_ګام), خطأ, عدم);
      إذا (اشاره_ګر_TYPE_P (type))
	{
	  begin = save_بیان (begin);
	  ګام = اشاره_ګر_int_مجموعه (loc, PLUS_بیان, begin, ګام);
	  ګام = fold_build2_loc (loc, MINUS_بیان, sizetype,
				  fold_convert (sizetype, ګام),
				  fold_convert (sizetype, begin));
	  ګام = fold_convert (ssizetype, ګام);
	}
      إذا (integer_zerop (ګام))
	{
	  error_at (loc, "iterator %qD has zero step", var);
	  ret = ریښتیا;
	  استمر;
	}

      إذا (begin == error_mark_غوټه
	  || پای_ټکی == error_mark_غوټه
	  || ګام == error_mark_غوټه
	  || orig_ګام == error_mark_غوټه)
	{
	  ret = ریښتیا;
	  استمر;
	}
      hash_سېټ<ونه> pset;
      ونه it2;
      لكل (it2 = ونه_CHAIN (it); it2; it2 = ونه_CHAIN (it2))
	{
	  ونه var2 = OMP_ITERATOR_VAR (it2);
	  ونه begin2 = OMP_ITERATOR_BEGIN (it2);
	  ونه end2 = OMP_ITERATOR_پای_ټکی (it2);
	  ونه step2 = OMP_ITERATOR_ګام (it2);
	  ونه type2 = ونه_TYPE (var2);
	  location_t loc2 = DECL_سرچینه_LOCATION (var2);
	  بنية c_پیدا_کړه_omp_var_s معلومات = { var, &pset };
	  إذا (walk_ونه (&type2, c_پیدا_کړه_omp_var_r, &معلومات, &pset))
	    {
	      error_at (loc2,
			"type of iterator %qD refers to outer iterator %qD",
			var2, var);
	      اكسر;
	    }
	  وإلا إذا (walk_ونه (&begin2, c_پیدا_کړه_omp_var_r, &معلومات, &pset))
	    {
	      error_at (بیان_LOC_OR_LOC (begin2, loc2),
			"begin expression refers to outer iterator %qD", var);
	      اكسر;
	    }
	  وإلا إذا (walk_ونه (&end2, c_پیدا_کړه_omp_var_r, &معلومات, &pset))
	    {
	      error_at (بیان_LOC_OR_LOC (end2, loc2),
			"end expression refers to outer iterator %qD", var);
	      اكسر;
	    }
	  وإلا إذا (walk_ونه (&step2, c_پیدا_کړه_omp_var_r, &معلومات, &pset))
	    {
	      error_at (بیان_LOC_OR_LOC (step2, loc2),
			"step expression refers to outer iterator %qD", var);
	      اكسر;
	    }
	}
      إذا (it2)
	{
	  ret = ریښتیا;
	  استمر;
	}
      OMP_ITERATOR_BEGIN (it) = begin;
      OMP_ITERATOR_پای_ټکی (it) = پای_ټکی;
      OMP_ITERATOR_ګام (it) = ګام;
      OMP_ITERATOR_ORIG_ګام (it) = orig_ګام;
    }
  أرجع ret;
}

/* Ensure that pointers are used in OpenACC attach and detach clauses.
   Return true if an error has been detected.  */

ساكن منطقي
c_oacc_check_attachments (ونه c)
{
  إذا (OMP_CLAUSE_کوډ (c) != OMP_CLAUSE_MAP)
    أرجع خطأ;

  /* OpenACC attach / detach clauses must be pointers.  */
  إذا (OMP_CLAUSE_MAP_ډول (c) == GOMP_MAP_ATTACH
      || OMP_CLAUSE_MAP_ډول (c) == GOMP_MAP_DETACH)
    {
      ونه t = OMP_CLAUSE_DECL (c);

      طالما (ونه_کوډ (t) == OMP_ARRAY_SECTION)
	t = ونه_عملوند (t, 0);

      إذا (ونه_کوډ (ونه_TYPE (t)) != اشاره_ګر_TYPE)
	{
	  error_at (OMP_CLAUSE_LOCATION (c), "expected pointer in %qs clause",
		    user_omp_clause_کوډ_name (c, ریښتیا));
	  أرجع ریښتیا;
	}
    }

  أرجع خطأ;
}

/* For all elements of CLAUSES, validate them against their constraints.
   Remove any elements from the list that are invalid.  */

ونه
c_پای_omp_clauses (ونه clauses, تعداد c_omp_region_type ort)
{
  bitmap_سر generic_سر, firstprivate_سر, lastprivate_سر;
  bitmap_سر aligned_سر, map_سر, map_ډګر_سر, map_firstprivate_سر;
  bitmap_سر oacc_reduction_سر, is_on_device_سر;
  ونه c, t, type, *pc;
  ونه simdlen = NULL_ونه, safelen = NULL_ونه;
  منطقي branch_کتل_شوی = خطأ;
  منطقي copyprivate_کتل_شوی = خطأ;
  منطقي mergeable_کتل_شوی = خطأ;
  ونه *detach_کتل_شوی = عدم;
  منطقي خطي_variable_ګام_check = خطأ;
  ونه *nowait_clause = عدم;
  ونه *grainsize_کتل_شوی = عدم;
  منطقي عدد_tasks_کتل_شوی = خطأ;
  ونه ordered_clause = NULL_ونه;
  ونه مهالوېش_clause = NULL_ونه;
  منطقي oacc_async = خطأ;
  ونه وروستی_iterators = NULL_ونه;
  منطقي وروستی_iterators_remove = خطأ;
  ونه *nogroup_کتل_شوی = عدم;
  ونه *ترتیب_clause = عدم;
  /* 1 if normal/task reduction has been seen, -1 if inscan reduction
     has been seen, -2 if mixed inscan/normal reduction diagnosed.  */
  صحيح reduction_کتل_شوی = 0;
  منطقي allocate_کتل_شوی = خطأ;
  منطقي implicit_moved = خطأ;
  منطقي موخه_دننه_reduction_کتل_شوی = خطأ;
  ونه *ډک_کتل_شوی = عدم;
  منطقي partial_کتل_شوی = خطأ;
  منطقي openacc = (ort & C_ORT_ACC) != 0;
  منطقي init_کتل_شوی = خطأ;
  منطقي init_use_destroy_کتل_شوی = خطأ;
  ونه init_no_targetsync_clause = NULL_ونه;
  ونه depend_clause = NULL_ونه;

  إذا (!openacc)
    clauses = omp_remove_duplicate_maps (clauses, ریښتیا);

  bitmap_obstack_initialize (عدم);
  bitmap_initialize (&generic_سر, &bitmap_default_obstack);
  bitmap_initialize (&firstprivate_سر, &bitmap_default_obstack);
  bitmap_initialize (&lastprivate_سر, &bitmap_default_obstack);
  bitmap_initialize (&aligned_سر, &bitmap_default_obstack);
  /* If ort == C_ORT_OMP_DECLARE_SIMD used as uniform_head instead.  */
  bitmap_initialize (&map_سر, &bitmap_default_obstack);
  bitmap_initialize (&map_ډګر_سر, &bitmap_default_obstack);
  bitmap_initialize (&map_firstprivate_سر, &bitmap_default_obstack);
  /* If ort == C_ORT_OMP used as nontemporal_head or use_device_xxx_head
     instead and for ort == C_ORT_OMP_TARGET used as in_reduction_head.  */
  bitmap_initialize (&oacc_reduction_سر, &bitmap_default_obstack);
  bitmap_initialize (&is_on_device_سر, &bitmap_default_obstack);

  إذا (openacc)
    لكل (c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
      إذا (OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_ASYNC)
	{
	  oacc_async = ریښتیا;
	  اكسر;
	}

  ونه *grp_پیل_p = عدم, grp_sentinel = NULL_ونه;

  لكل (pc = &clauses, c = clauses; c ; c = *pc)
    {
      منطقي remove = خطأ;
      منطقي need_complete = خطأ;
      منطقي need_implicitly_determined = خطأ;

      /* We've reached the end of a list of expanded nodes.  Reset the group
	 start pointer.  */
      إذا (c == grp_sentinel)
	{
	  إذا (grp_پیل_p
	      && OMP_CLAUSE_HAS_ITERATORS (*grp_پیل_p))
	    لكل (ونه gc = *grp_پیل_p; gc != grp_sentinel;
		 gc = OMP_CLAUSE_CHAIN (gc))
	      OMP_CLAUSE_ITERATORS (gc) = OMP_CLAUSE_ITERATORS (*grp_پیل_p);
	  grp_پیل_p = عدم;
	}

      بدل (OMP_CLAUSE_کوډ (c))
	{
	حالة OMP_CLAUSE_SHARED:
	  need_implicitly_determined = ریښتیا;
	  اذهب check_dup_generic;

	حالة OMP_CLAUSE_شخصي:
	  need_complete = ریښتیا;
	  need_implicitly_determined = ریښتیا;
	  اذهب check_dup_generic;

	حالة OMP_CLAUSE_REDUCTION:
	  إذا (reduction_کتل_شوی == 0)
	    reduction_کتل_شوی = OMP_CLAUSE_REDUCTION_INSCAN (c) ? -1 : 1;
	  وإلا إذا (reduction_کتل_شوی != -2
		   && reduction_کتل_شوی != (OMP_CLAUSE_REDUCTION_INSCAN (c)
					 ? -1 : 1))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<inscan%> and non-%<inscan%> %<reduction%> clauses "
			"on the same construct");
	      reduction_کتل_شوی = -2;
	    }
	  /* FALLTHRU */
	حالة OMP_CLAUSE_دننه_REDUCTION:
	حالة OMP_CLAUSE_TASK_REDUCTION:
	  need_implicitly_determined = ریښتیا;
	  t = OMP_CLAUSE_DECL (c);
	  إذا (ونه_کوډ (t) == OMP_ARRAY_SECTION)
	    {
	      إذا (handle_omp_array_sections (c, ort))
		{
		  remove = ریښتیا;
		  اكسر;
		}

	      t = OMP_CLAUSE_DECL (c);
	      إذا (OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_REDUCTION
		  && OMP_CLAUSE_REDUCTION_INSCAN (c))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<inscan%> %<reduction%> clause with array "
			    "section");
		  remove = ریښتیا;
		  اكسر;
		}
	    }
	  t = require_complete_type (OMP_CLAUSE_LOCATION (c), t);
	  إذا (t == error_mark_غوټه)
	    {
	      remove = ریښتیا;
	      اكسر;
	    }
	  إذا (oacc_async)
	    c_mark_addressable (t);
	  type = ونه_TYPE (t);
	  إذا (ونه_کوډ (t) == MEM_REF)
	    type = ونه_TYPE (type);
	  إذا (ونه_کوډ (type) == ARRAY_TYPE)
	    {
	      ونه oatype = type;
	      gcc_assert (ونه_کوډ (t) != MEM_REF);
	      طالما (ونه_کوډ (type) == ARRAY_TYPE)
		type = ونه_TYPE (type);
	      إذا (integer_zerop (TYPE_اندازه_UNIT (type)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD in %<reduction%> clause is a zero size array",
			    t);
		  remove = ریښتیا;
		  اكسر;
		}
	      ونه اندازه = اندازه_binop (EXACT_DIV_بیان, TYPE_اندازه_UNIT (oatype),
				      TYPE_اندازه_UNIT (type));
	      إذا (integer_zerop (اندازه))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD in %<reduction%> clause is a zero size array",
			    t);
		  remove = ریښتیا;
		  اكسر;
		}
	      اندازه = اندازه_binop (MINUS_بیان, اندازه, اندازه_one_غوټه);
	      اندازه = save_بیان (اندازه);
	      ونه شاخص_type = build_شاخص_type (اندازه);
	      ونه atype = c_build_array_type (TYPE_MAIN_VARIANT (type),
					       شاخص_type);
	      atype = c_build_qualified_type (atype, TYPE_QUALS (type));
	      ونه ptype = c_build_اشاره_ګر_type (type);
	      إذا (ونه_کوډ (ونه_TYPE (t)) == ARRAY_TYPE)
		t = build_fold_addr_بیان (t);
	      t = build2 (MEM_REF, atype, t, build_int_cst (ptype, 0));
	      OMP_CLAUSE_DECL (c) = t;
	    }
	  إذا (TYPE_ATOMIC (type))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<_Atomic%> %qE in %<reduction%> clause", t);
	      remove = ریښتیا;
	      اكسر;
	    }
	  إذا (OMP_CLAUSE_کوډ (c) != OMP_CLAUSE_REDUCTION
	      || OMP_CLAUSE_REDUCTION_TASK (c))
	    {
	      /* Disallow zero sized or potentially zero sized task
		 reductions.  */
	      إذا (integer_zerop (TYPE_اندازه_UNIT (type)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "zero sized type %qT in %qs clause", type,
			    omp_clause_کوډ_name[OMP_CLAUSE_کوډ (c)]);
		  remove = ریښتیا;
		  اكسر;
		}
	      وإلا إذا (ونه_کوډ (TYPE_اندازه_UNIT (type)) != INTEGER_CST)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "variable sized type %qT in %qs clause", type,
			    omp_clause_کوډ_name[OMP_CLAUSE_کوډ (c)]);
		  remove = ریښتیا;
		  اكسر;
		}
	    }
	  إذا (OMP_CLAUSE_REDUCTION_PLACEHOLDER (c) == NULL_ونه
	      && (FLOAT_TYPE_P (type)
		  || ونه_کوډ (type) == COMPLEX_TYPE))
	    {
	      تعداد ونه_کوډ_2 r_کوډ = OMP_CLAUSE_REDUCTION_کوډ (c);
	      ثابت حرف *r_name = عدم;

	      بدل (r_کوډ)
		{
		حالة PLUS_بیان:
		حالة MULT_بیان:
		حالة MINUS_بیان:
		حالة TRUTH_ANDIF_بیان:
		حالة TRUTH_ORIF_بیان:
		  اكسر;
		حالة MIN_بیان:
		  إذا (ونه_کوډ (type) == COMPLEX_TYPE)
		    r_name = "min";
		  اكسر;
		حالة MAX_بیان:
		  إذا (ونه_کوډ (type) == COMPLEX_TYPE)
		    r_name = "max";
		  اكسر;
		حالة بټ_AND_بیان:
		  r_name = "&";
		  اكسر;
		حالة بټ_XOR_بیان:
		  r_name = "^";
		  اكسر;
		حالة بټ_IOR_بیان:
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
		  remove = ریښتیا;
		  اكسر;
		}
	    }
	  وإلا إذا (OMP_CLAUSE_REDUCTION_PLACEHOLDER (c) == error_mark_غوټه)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"user defined reduction not found for %qE", t);
	      remove = ریښتیا;
	      اكسر;
	    }
	  وإلا إذا (OMP_CLAUSE_REDUCTION_PLACEHOLDER (c))
	    {
	      ونه list = OMP_CLAUSE_REDUCTION_PLACEHOLDER (c);
	      type = TYPE_MAIN_VARIANT (type);
	      ونه placeholder = build_decl (OMP_CLAUSE_LOCATION (c),
					     VAR_DECL, NULL_ونه, type);
	      ونه decl_placeholder = NULL_ونه;
	      OMP_CLAUSE_REDUCTION_PLACEHOLDER (c) = placeholder;
	      DECL_ARTIFICIAL (placeholder) = 1;
	      DECL_IGNORED_P (placeholder) = 1;
	      إذا (ونه_کوډ (t) == MEM_REF)
		{
		  decl_placeholder = build_decl (OMP_CLAUSE_LOCATION (c),
						 VAR_DECL, NULL_ونه, type);
		  OMP_CLAUSE_REDUCTION_DECL_PLACEHOLDER (c) = decl_placeholder;
		  DECL_ARTIFICIAL (decl_placeholder) = 1;
		  DECL_IGNORED_P (decl_placeholder) = 1;
		}
	      إذا (ونه_ADDRESSABLE (ونه_VEC_ELT (list, 0)))
		c_mark_addressable (placeholder);
	      إذا (ونه_ADDRESSABLE (ونه_VEC_ELT (list, 1)))
		c_mark_addressable (decl_placeholder ? decl_placeholder
				    : OMP_CLAUSE_DECL (c));
	      OMP_CLAUSE_REDUCTION_یوځای (c)
		= c_clone_omp_udr (ونه_VEC_ELT (list, 2),
				   ونه_VEC_ELT (list, 0),
				   ونه_VEC_ELT (list, 1),
				   decl_placeholder ? decl_placeholder
				   : OMP_CLAUSE_DECL (c), placeholder);
	      OMP_CLAUSE_REDUCTION_یوځای (c)
		= build3_loc (OMP_CLAUSE_LOCATION (c), BIND_بیان,
			      void_type_غوټه, NULL_ونه,
			      OMP_CLAUSE_REDUCTION_یوځای (c), NULL_ونه);
	      ونه_SIDE_EFFECTS (OMP_CLAUSE_REDUCTION_یوځای (c)) = 1;
	      إذا (ونه_VEC_اوږدتیا (list) == 6)
		{
		  إذا (ونه_ADDRESSABLE (ونه_VEC_ELT (list, 3)))
		    c_mark_addressable (decl_placeholder ? decl_placeholder
					: OMP_CLAUSE_DECL (c));
		  إذا (ونه_ADDRESSABLE (ونه_VEC_ELT (list, 4)))
		    c_mark_addressable (placeholder);
		  ونه init = ونه_VEC_ELT (list, 5);
		  إذا (init == error_mark_غوټه)
		    init = DECL_INITIAL (ونه_VEC_ELT (list, 3));
		  OMP_CLAUSE_REDUCTION_INIT (c)
		    = c_clone_omp_udr (init, ونه_VEC_ELT (list, 4),
				       ونه_VEC_ELT (list, 3),
				       decl_placeholder ? decl_placeholder
				       : OMP_CLAUSE_DECL (c), placeholder);
		  إذا (ونه_VEC_ELT (list, 5) == error_mark_غوټه)
		    {
		      ونه v = decl_placeholder ? decl_placeholder : t;
		      OMP_CLAUSE_REDUCTION_INIT (c)
			= build2 (INIT_بیان, ونه_TYPE (v), v,
				  OMP_CLAUSE_REDUCTION_INIT (c));
		    }
		  إذا (walk_ونه (&OMP_CLAUSE_REDUCTION_INIT (c),
				 c_پیدا_کړه_omp_placeholder_r,
				 placeholder, عدم))
		    OMP_CLAUSE_REDUCTION_OMP_ORIG_REF (c) = 1;
		}
	      وإلا
		{
		  ونه init;
		  ونه v = decl_placeholder ? decl_placeholder : t;
		  إذا (AGGREGATE_TYPE_P (ونه_TYPE (v)))
		    init = build_constructor (ونه_TYPE (v), عدم);
		  وإلا
		    init = fold_convert (ونه_TYPE (v), integer_zero_غوټه);
		  OMP_CLAUSE_REDUCTION_INIT (c)
		    = build2 (INIT_بیان, ونه_TYPE (v), v, init);
		}
	      OMP_CLAUSE_REDUCTION_INIT (c)
		= build3_loc (OMP_CLAUSE_LOCATION (c), BIND_بیان,
			      void_type_غوټه, NULL_ونه,
			       OMP_CLAUSE_REDUCTION_INIT (c), NULL_ونه);
	      ونه_SIDE_EFFECTS (OMP_CLAUSE_REDUCTION_INIT (c)) = 1;
	    }
	  إذا (ونه_کوډ (t) == MEM_REF)
	    {
	      إذا (TYPE_اندازه_UNIT (ونه_TYPE (ونه_TYPE (t))) == NULL_ونه
		  || ونه_کوډ (TYPE_اندازه_UNIT (ونه_TYPE (ونه_TYPE (t))))
		     != INTEGER_CST)
		{
		  sorry ("variable length element type in array "
			 "%<reduction%> clause");
		  remove = ریښتیا;
		  اكسر;
		}
	      t = ونه_عملوند (t, 0);
	      إذا (ونه_کوډ (t) == اشاره_ګر_PLUS_بیان)
		t = ونه_عملوند (t, 0);
	      إذا (ونه_کوډ (t) == ADDR_بیان)
		t = ونه_عملوند (t, 0);
	    }
	  اذهب check_dup_generic_t;

	حالة OMP_CLAUSE_COPYPRIVATE:
	  copyprivate_کتل_شوی = ریښتیا;
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
	      remove = ریښتیا;
	      اكسر;
	    }
	  اذهب check_dup_generic;

	حالة OMP_CLAUSE_خطي:
	  إذا (ort != C_ORT_OMP_DECLARE_SIMD)
	    need_implicitly_determined = ریښتیا;
	  t = OMP_CLAUSE_DECL (c);
	  إذا (ort != C_ORT_OMP_DECLARE_SIMD
	      && OMP_CLAUSE_خطي_ډول (c) != OMP_CLAUSE_خطي_DEFAULT
	      && OMP_CLAUSE_خطي_OLD_خطي_MODIFIER (c))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"modifier should not be specified in %<linear%> "
			"clause on %<simd%> or %<for%> constructs when not "
			"using OpenMP 5.2 modifiers");
	      OMP_CLAUSE_خطي_ډول (c) = OMP_CLAUSE_خطي_DEFAULT;
	    }
	  إذا (!INTEGRAL_TYPE_P (ونه_TYPE (t))
	      && ونه_کوډ (ونه_TYPE (t)) != اشاره_ګر_TYPE)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"linear clause applied to non-integral non-pointer "
			"variable with type %qT", ونه_TYPE (t));
	      remove = ریښتیا;
	      اكسر;
	    }
	  إذا (TYPE_ATOMIC (ونه_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<_Atomic%> %qD in %<linear%> clause", t);
	      remove = ریښتیا;
	      اكسر;
	    }
	  إذا (ort == C_ORT_OMP_DECLARE_SIMD)
	    {
	      ونه s = OMP_CLAUSE_خطي_ګام (c);
	      إذا (ونه_کوډ (s) == PARM_DECL)
		{
		  OMP_CLAUSE_خطي_VARIABLE_STRIDE (c) = 1;
		  /* map_head bitmap is used as uniform_head if
		     declare_simd.  */
		  إذا (!bitmap_بټ_p (&map_سر, DECL_UID (s)))
		    خطي_variable_ګام_check = ریښتیا;
		  اذهب check_dup_generic;
		}
	      إذا (ونه_کوډ (s) != INTEGER_CST)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<linear%> clause step %qE is neither constant "
			    "nor a parameter", s);
		  remove = ریښتیا;
		  اكسر;
		}
	    }
	  إذا (ونه_کوډ (ونه_TYPE (OMP_CLAUSE_DECL (c))) == اشاره_ګر_TYPE)
	    {
	      ونه s = OMP_CLAUSE_خطي_ګام (c);
	      s = اشاره_ګر_int_مجموعه (OMP_CLAUSE_LOCATION (c), PLUS_بیان,
				   OMP_CLAUSE_DECL (c), s);
	      s = fold_build2_loc (OMP_CLAUSE_LOCATION (c), MINUS_بیان,
				   sizetype, fold_convert (sizetype, s),
				   fold_convert
				     (sizetype, OMP_CLAUSE_DECL (c)));
	      إذا (s == error_mark_غوټه)
		s = اندازه_one_غوټه;
	      OMP_CLAUSE_خطي_ګام (c) = s;
	    }
	  وإلا
	    OMP_CLAUSE_خطي_ګام (c)
	      = fold_convert (ونه_TYPE (t), OMP_CLAUSE_خطي_ګام (c));
	  اذهب check_dup_generic;

	check_dup_generic:
	  t = OMP_CLAUSE_DECL (c);
	check_dup_generic_t:
	  إذا (!VAR_P (t) && ونه_کوډ (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %qs", t,
			omp_clause_کوډ_name[OMP_CLAUSE_کوډ (c)]);
	      remove = ریښتیا;
	    }
	  وإلا إذا ((openacc && OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_REDUCTION)
		   || (ort == C_ORT_OMP
		       && (OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_USE_DEVICE_PTR
			   || (OMP_CLAUSE_کوډ (c)
			       == OMP_CLAUSE_USE_DEVICE_ADDR)))
		   || (ort == C_ORT_OMP_موخه
		       && OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_دننه_REDUCTION))
	    {
	      إذا (OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_دننه_REDUCTION
		  && (bitmap_بټ_p (&generic_سر, DECL_UID (t))
		      || bitmap_بټ_p (&firstprivate_سر, DECL_UID (t))))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in data-sharing "
			    "clauses", t);
		  remove = ریښتیا;
		  اكسر;
		}
	      إذا (OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_دننه_REDUCTION)
		موخه_دننه_reduction_کتل_شوی = ریښتیا;
	      إذا (bitmap_بټ_p (&oacc_reduction_سر, DECL_UID (t)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    openacc
			    ? "%qD appears more than once in reduction clauses"
			    : "%qD appears more than once in data clauses",
			    t);
		  remove = ریښتیا;
		}
	      وإلا
		bitmap_سېټ_بټ (&oacc_reduction_سر, DECL_UID (t));
	    }
	  وإلا إذا (bitmap_بټ_p (&generic_سر, DECL_UID (t))
		   || bitmap_بټ_p (&firstprivate_سر, DECL_UID (t))
		   || bitmap_بټ_p (&lastprivate_سر, DECL_UID (t))
		   || bitmap_بټ_p (&map_firstprivate_سر, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in data clauses", t);
	      remove = ریښتیا;
	    }
	  وإلا إذا ((OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_شخصي
		    || OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_HAS_DEVICE_ADDR
		    || OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_IS_DEVICE_PTR)
		   && bitmap_بټ_p (&map_سر, DECL_UID (t)))
	    {
	      إذا (openacc)
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears more than once in data clauses", t);
	      وإلا
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears both in data and map clauses", t);
	      remove = ریښتیا;
	    }
	  وإلا
	    bitmap_سېټ_بټ (&generic_سر, DECL_UID (t));
	  اكسر;

	حالة OMP_CLAUSE_FIRSTPRIVATE:
	  إذا (OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (c) && !implicit_moved)
	    {
	    move_implicit:
	      implicit_moved = ریښتیا;
	      /* Move firstprivate and map clauses with
		 OMP_CLAUSE_{FIRSTPRIVATE,MAP}_IMPLICIT set to the end of
		 clauses chain.  */
	      ونه cl1 = NULL_ونه, cl2 = NULL_ونه;
	      ونه *pc1 = pc, *pc2 = &cl1, *pc3 = &cl2;
	      طالما (*pc1)
		إذا (OMP_CLAUSE_کوډ (*pc1) == OMP_CLAUSE_FIRSTPRIVATE
		    && OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (*pc1))
		  {
		    *pc3 = *pc1;
		    pc3 = &OMP_CLAUSE_CHAIN (*pc3);
		    *pc1 = OMP_CLAUSE_CHAIN (*pc1);
		  }
		وإلا إذا (OMP_CLAUSE_کوډ (*pc1) == OMP_CLAUSE_MAP
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
	  need_complete = ریښتیا;
	  need_implicitly_determined = ریښتیا;
	  إذا (!VAR_P (t) && ونه_کوډ (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %<firstprivate%>", t);
	      remove = ریښتیا;
	    }
	  وإلا إذا (OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (c)
		   && !OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT_موخه (c)
		   && bitmap_بټ_p (&map_firstprivate_سر, DECL_UID (t)))
	    remove = ریښتیا;
	  وإلا إذا (bitmap_بټ_p (&generic_سر, DECL_UID (t))
		   || bitmap_بټ_p (&firstprivate_سر, DECL_UID (t))
		   || bitmap_بټ_p (&map_firstprivate_سر, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in data clauses", t);
	      remove = ریښتیا;
	    }
	  وإلا إذا (bitmap_بټ_p (&map_سر, DECL_UID (t))
		   || bitmap_بټ_p (&map_ډګر_سر, DECL_UID (t)))
	    {
	      إذا (openacc)
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears more than once in data clauses", t);
	      وإلا إذا (OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (c)
		       && !OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT_موخه (c))
		/* Silently drop the clause.  */;
	      وإلا
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears both in data and map clauses", t);
	      remove = ریښتیا;
	    }
	  وإلا
	    bitmap_سېټ_بټ (&firstprivate_سر, DECL_UID (t));
	  اكسر;

	حالة OMP_CLAUSE_LASTPRIVATE:
	  t = OMP_CLAUSE_DECL (c);
	  need_complete = ریښتیا;
	  need_implicitly_determined = ریښتیا;
	  إذا (!VAR_P (t) && ونه_کوډ (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %<lastprivate%>", t);
	      remove = ریښتیا;
	    }
	  وإلا إذا (bitmap_بټ_p (&generic_سر, DECL_UID (t))
		   || bitmap_بټ_p (&lastprivate_سر, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
		     "%qE appears more than once in data clauses", t);
	      remove = ریښتیا;
	    }
	  وإلا
	    bitmap_سېټ_بټ (&lastprivate_سر, DECL_UID (t));
	  اكسر;

	حالة OMP_CLAUSE_ALIGNED:
	  t = OMP_CLAUSE_DECL (c);
	  إذا (!VAR_P (t) && ونه_کوډ (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in %<aligned%> clause", t);
	      remove = ریښتیا;
	    }
	  وإلا إذا (!اشاره_ګر_TYPE_P (ونه_TYPE (t))
		   && ونه_کوډ (ونه_TYPE (t)) != ARRAY_TYPE)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE in %<aligned%> clause is neither a pointer nor "
			"an array", t);
	      remove = ریښتیا;
	    }
	  وإلا إذا (TYPE_ATOMIC (ونه_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<_Atomic%> %qD in %<aligned%> clause", t);
	      remove = ریښتیا;
	      اكسر;
	    }
	  وإلا إذا (bitmap_بټ_p (&aligned_سر, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in %<aligned%> clauses",
			t);
	      remove = ریښتیا;
	    }
	  وإلا
	    bitmap_سېټ_بټ (&aligned_سر, DECL_UID (t));
	  اكسر;

	حالة OMP_CLAUSE_NONTEMPORAL:
	  t = OMP_CLAUSE_DECL (c);
	  إذا (!VAR_P (t) && ونه_کوډ (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in %<nontemporal%> clause", t);
	      remove = ریښتیا;
	    }
	  وإلا إذا (bitmap_بټ_p (&oacc_reduction_سر, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in %<nontemporal%> "
			"clauses", t);
	      remove = ریښتیا;
	    }
	  وإلا
	    bitmap_سېټ_بټ (&oacc_reduction_سر, DECL_UID (t));
	  اكسر;

	حالة OMP_CLAUSE_ALLOCATE:
	  t = OMP_CLAUSE_DECL (c);
	  إذا (!VAR_P (t) && ونه_کوډ (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in %<allocate%> clause", t);
	      remove = ریښتیا;
	    }
	  وإلا إذا (bitmap_بټ_p (&aligned_سر, DECL_UID (t)))
	    {
	      warning_at (OMP_CLAUSE_LOCATION (c), OPT_Wopenmp,
			  "%qE appears more than once in %<allocate%> clauses",
			  t);
	      remove = ریښتیا;
	    }
	  وإلا
	    {
	      bitmap_سېټ_بټ (&aligned_سر, DECL_UID (t));
	      إذا (!OMP_CLAUSE_ALLOCATE_COMBINED (c))
		allocate_کتل_شوی = ریښتیا;
	    }
	  اكسر;

	حالة OMP_CLAUSE_DOACROSS:
	  t = OMP_CLAUSE_DECL (c);
	  إذا (t == NULL_ونه)
	    اكسر;
	  إذا (OMP_CLAUSE_DOACROSS_ډول (c) == OMP_CLAUSE_DOACROSS_SINK)
	    {
	      gcc_assert (ونه_کوډ (t) == ونه_LIST);
	      لكل (; t; t = ونه_CHAIN (t))
		{
		  ونه decl = ونه_ارزښت (t);
		  إذا (ونه_کوډ (ونه_TYPE (decl)) == اشاره_ګر_TYPE)
		    {
		      ونه دننه_واټن = ونه_PURPOSE (t);
		      منطقي neg = wi::neg_p (wi::منزل_wide (دننه_واټن));
		      دننه_واټن = fold_unary (ABS_بیان, ونه_TYPE (دننه_واټن), دننه_واټن);
		      ونه t2 = اشاره_ګر_int_مجموعه (OMP_CLAUSE_LOCATION (c),
						 neg ? MINUS_بیان : PLUS_بیان,
						 decl, دننه_واټن);
		      t2 = fold_build2_loc (OMP_CLAUSE_LOCATION (c), MINUS_بیان,
					    sizetype,
					    fold_convert (sizetype, t2),
					    fold_convert (sizetype, decl));
		      إذا (t2 == error_mark_غوټه)
			{
			  remove = ریښتیا;
			  اكسر;
			}
		      ونه_PURPOSE (t) = t2;
		    }
		}
	      اكسر;
	    }
	  gcc_unreachable ();

	حالة OMP_CLAUSE_کاروي_ALLOCATORS:
	  t = OMP_CLAUSE_کاروي_ALLOCATORS_ALLOCATOR (c);
	  إذا (t == error_mark_غوټه)
	    {
	      remove = ریښتیا;
	      اكسر;
	    }
	  إذا ((VAR_P (t) || ونه_کوډ (t) == PARM_DECL)
	      && (bitmap_بټ_p (&generic_سر, DECL_UID (t))
		  || bitmap_بټ_p (&map_سر, DECL_UID (t))
		  || bitmap_بټ_p (&firstprivate_سر, DECL_UID (t))
		  || bitmap_بټ_p (&lastprivate_سر, DECL_UID (t))))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in data clauses", t);
	      remove = ریښتیا;
	      اكسر;
	    }
	  وإلا
	    bitmap_سېټ_بټ (&generic_سر, DECL_UID (t));
	  إذا (ونه_کوډ (ونه_TYPE (t)) != ENUMERAL_TYPE
	      || strcmp (IDENTIFIER_اشاره_ګر (TYPE_IDENTIFIER (ونه_TYPE (t))),
			 "omp_allocator_handle_t") != 0)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"allocator %qE must be of %<omp_allocator_handle_t%> "
			"type", t);
	      remove = ریښتیا;
	      اكسر;
	    }
	  ونه init;
	  إذا (!DECL_P (t)
	      || (ونه_کوډ (t) == CONST_DECL
		  && ((init = DECL_INITIAL(t)) == تش_اشاره
		      || ونه_کوډ (init) != INTEGER_CST
		      || ((wi::منزل_widest (init) < 0
			   || wi::منزل_widest (init) > GOMP_OMP_PREDEF_ALLOC_MAX)
			  && (wi::منزل_widest (init) < GOMP_OMPX_PREDEF_ALLOC_MIN
			      || (wi::منزل_widest (init)
				  > GOMP_OMPX_PREDEF_ALLOC_MAX))))))
	    {
	      remove = ریښتیا;
	      error_at (OMP_CLAUSE_LOCATION (c),
			"allocator %qE must be either a variable or a "
			"predefined allocator", t);
	      اكسر;
	    }
	  وإلا إذا (ونه_کوډ (t) == CONST_DECL)
	    {
	      /* omp_null_allocator is ignored and for predefined allocators,
		 no special handling is required; thus, mark them removed. */
	      remove = ریښتیا;

	      إذا (OMP_CLAUSE_کاروي_ALLOCATORS_MEMSPACE (c)
		  || OMP_CLAUSE_کاروي_ALLOCATORS_TRAITS (c))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "modifiers cannot be used with predefined "
			    "allocator %qE", t);
		  اكسر;
		}
	    }
	  t = OMP_CLAUSE_کاروي_ALLOCATORS_MEMSPACE (c);
	  إذا (t == error_mark_غوټه)
	    {
	      remove = ریښتیا;
	      اكسر;
	    }
	  إذا (t != NULL_ونه
	      && ((ونه_کوډ (t) != CONST_DECL && ونه_کوډ (t) != INTEGER_CST)
		  || ونه_کوډ (ونه_TYPE (t)) != ENUMERAL_TYPE
		  || strcmp (IDENTIFIER_اشاره_ګر (TYPE_IDENTIFIER (ونه_TYPE (t))),
			     "omp_memspace_handle_t") != 0))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c), "memspace modifier %qE must be"
			" constant enum of %<omp_memspace_handle_t%> type", t);
	      remove = ریښتیا;
	      اكسر;
	    }
	  t = OMP_CLAUSE_کاروي_ALLOCATORS_TRAITS (c);
	  إذا (t == error_mark_غوټه)
	    {
	      remove = ریښتیا;
	      اكسر;
	    }
	  إذا (t != NULL_ونه
	      && t != error_mark_غوټه
	      && (DECL_EXTERNAL (t)
		  || ونه_کوډ (t) == PARM_DECL))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c), "traits array %qE must be "
			"defined in same scope as the construct on which the "
			"clause appears", t);
	      remove = ریښتیا;
	    }
	  إذا (t != NULL_ونه)
	    {
	      منطقي type_err = خطأ;

	      إذا (ونه_کوډ (ونه_TYPE (t)) != ARRAY_TYPE
		  || DECL_اندازه (t) == NULL_ونه
		  || !COMPLETE_TYPE_P (ونه_TYPE (t)))
		type_err = ریښتیا;
	      وإلا
		{
		  ونه elem_t = ونه_TYPE (ونه_TYPE (t));
		  إذا (ونه_کوډ (elem_t) != ریکارډ_TYPE
		      || strcmp (IDENTIFIER_اشاره_ګر (TYPE_IDENTIFIER (elem_t)),
				 "omp_alloctrait_t") != 0
		      || !TYPE_READONLY (elem_t))
		    type_err = ریښتیا;
		}
	      إذا (type_err)
		{
		  إذا (t != error_mark_غوټه)
		    error_at (OMP_CLAUSE_LOCATION (c), "traits array %qE must "
			      "be of %<const omp_alloctrait_t []%> type", t);
		  وإلا
		    error_at (OMP_CLAUSE_LOCATION (c), "traits array must "
			      "be of %<const omp_alloctrait_t []%> type");
		  remove = ریښتیا;
		}
	      وإلا
		{
		  ونه cst_val = decl_constant_ارزښت_1 (t, ریښتیا);
		  إذا (cst_val == t)
		    {
		      error_at (OMP_CLAUSE_LOCATION (c), "traits array must be "
				"initialized with constants");

		      remove = ریښتیا;
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
	      إذا (ونه_PURPOSE (t) != وروستی_iterators)
		وروستی_iterators_remove
		  = c_omp_پای_iterators (ونه_PURPOSE (t));
	      وروستی_iterators = ونه_PURPOSE (t);
	      t = ونه_ارزښت (t);
	      إذا (وروستی_iterators_remove)
		t = error_mark_غوټه;
	    }
	  وإلا
	    وروستی_iterators = NULL_ونه;
	  إذا (ونه_کوډ (t) == OMP_ARRAY_SECTION)
	    {
	      إذا (handle_omp_array_sections (c, ort))
		remove = ریښتیا;
	      وإلا إذا (OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_DEPEND
		       && OMP_CLAUSE_DEPEND_ډول (c) == OMP_CLAUSE_DEPEND_DEPOBJ)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<depend%> clause with %<depobj%> dependence "
			    "type on array section");
		  remove = ریښتیا;
		}
	      اكسر;
	    }
	  إذا (t == error_mark_غوټه)
	    remove = ریښتیا;
	  وإلا إذا (OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_DEPEND
		   && t == ridpointers[RID_OMP_ALL_حافظه])
	    {
	      إذا (OMP_CLAUSE_DEPEND_ډول (c) != OMP_CLAUSE_DEPEND_بهر
		  && OMP_CLAUSE_DEPEND_ډول (c) != OMP_CLAUSE_DEPEND_INOUT)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<omp_all_memory%> used with %<depend%> kind "
			    "other than %<out%> or %<inout%>");
		  remove = ریښتیا;
		}
	    }
	  وإلا إذا (!lvalue_p (t))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not lvalue expression nor array section in "
			"%qs clause", t,
			omp_clause_کوډ_name[OMP_CLAUSE_کوډ (c)]);
	      remove = ریښتیا;
	    }
	  وإلا إذا (ونه_کوډ (t) == COMPONENT_REF
		   && DECL_C_بټ_ډګر (ونه_عملوند (t, 1)))
	    {
	      gcc_assert (OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_DEPEND
			  || OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_AFFINITY);
	      error_at (OMP_CLAUSE_LOCATION (c),
			"bit-field %qE in %qs clause", t,
			omp_clause_کوډ_name[OMP_CLAUSE_کوډ (c)]);
	      remove = ریښتیا;
	    }
	  وإلا إذا (OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_DEPEND
		   && OMP_CLAUSE_DEPEND_ډول (c) == OMP_CLAUSE_DEPEND_DEPOBJ)
	    {
	      إذا (!c_omp_depend_t_p (ونه_TYPE (t)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qE does not have %<omp_depend_t%> type in "
			    "%<depend%> clause with %<depobj%> dependence "
			    "type", t);
		  remove = ریښتیا;
		}
	    }
	  وإلا إذا (OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_DEPEND
		   && c_omp_depend_t_p (ونه_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE should not have %<omp_depend_t%> type in "
			"%<depend%> clause with dependence type other than "
			"%<depobj%>", t);
	      remove = ریښتیا;
	    }
	  إذا (!remove)
	    {
	      إذا (t == ridpointers[RID_OMP_ALL_حافظه])
		t = null_اشاره_ګر_غوټه;
	      وإلا
		{
		  ونه addr = build_unary_op (OMP_CLAUSE_LOCATION (c),
					      ADDR_بیان, t, خطأ);
		  إذا (addr == error_mark_غوټه)
		    {
		      remove = ریښتیا;
		      اكسر;
		    }
		  t = build_غیرمستقیم_ref (OMP_CLAUSE_LOCATION (c), addr,
					  RO_UNARY_ستوری);
		  إذا (t == error_mark_غوټه)
		    {
		      remove = ریښتیا;
		      اكسر;
		    }
		}
	      إذا (OMP_ITERATOR_DECL_P (OMP_CLAUSE_DECL (c)))
		ونه_ارزښت (OMP_CLAUSE_DECL (c)) = t;
	      وإلا
		OMP_CLAUSE_DECL (c) = t;
	    }
	  اكسر;

	حالة OMP_CLAUSE_MAP:
	  إذا (OMP_CLAUSE_MAP_IMPLICIT (c) && !implicit_moved)
	    اذهب move_implicit;
	  إذا (OMP_CLAUSE_MAP_ډول (c) == GOMP_MAP_ټېل_MAPPER_NAME
	      || OMP_CLAUSE_MAP_ډول (c) == GOMP_MAP_راوباسه_MAPPER_NAME)
	    {
	      remove = ریښتیا;
	      اكسر;
	    }
	  /* FALLTHRU */
	حالة OMP_CLAUSE_منزل:
	حالة OMP_CLAUSE_FROM:
	  إذا (OMP_CLAUSE_ITERATORS (c)
	      && c_omp_پای_iterators (OMP_CLAUSE_ITERATORS (c)))
	    {
	      t = error_mark_غوټه;
	      اكسر;
	    }
	  /* FALLTHRU */
	حالة OMP_CLAUSE__CACHE_:
	  {
	    کارول نطاق omp_addr_tokenizer;
	    auto_vec<omp_addr_token *, 10> addr_نښې;

	    t = OMP_CLAUSE_DECL (c);
	    إذا (ونه_کوډ (t) == OMP_ARRAY_SECTION)
	      {
		grp_پیل_p = pc;
		grp_sentinel = OMP_CLAUSE_CHAIN (c);

		إذا (handle_omp_array_sections (c, ort))
		  remove = ریښتیا;
		وإلا
		  {
		    t = OMP_CLAUSE_DECL (c);
		    إذا (!omp_mappable_type (ونه_TYPE (t)))
		      {
			error_at (OMP_CLAUSE_LOCATION (c),
				  "array section does not have mappable type "
				  "in %qs clause",
				  omp_clause_کوډ_name[OMP_CLAUSE_کوډ (c)]);
			remove = ریښتیا;
		      }
		    وإلا إذا (TYPE_ATOMIC (ونه_TYPE (t)))
		      {
			error_at (OMP_CLAUSE_LOCATION (c),
				  "%<_Atomic%> %qE in %qs clause", t,
				  omp_clause_کوډ_name[OMP_CLAUSE_کوډ (c)]);
			remove = ریښتیا;
		      }
		    طالما (ونه_کوډ (t) == ARRAY_REF)
		      t = ونه_عملوند (t, 0);

		    c_omp_پته_inspector ai (OMP_CLAUSE_LOCATION (c), t);

		    إذا (!omp_parse_بیان (addr_نښې, t))
		      {
			sorry_at (OMP_CLAUSE_LOCATION (c),
				  "unsupported map expression %qE",
				  OMP_CLAUSE_DECL (c));
			remove = ریښتیا;
			اكسر;
		      }

		    /* This check is to determine if this will be the only map
		       node created for this clause.  Otherwise, we'll check
		       the following FIRSTPRIVATE_POINTER or ATTACH_DETACH
		       node on the next iteration(s) of the loop.   */
		    إذا (addr_نښې.اوږدتیا () >= 4
			&& addr_نښې[0]->type == STRUCTURE_بنسټ
			&& addr_نښې[0]->u.structure_بنسټ_ډول == بنسټ_DECL
			&& addr_نښې[1]->type == ACCESS_لاره
			&& addr_نښې[2]->type == COMPONENT_SELECTOR
			&& addr_نښې[3]->type == ACCESS_لاره
			&& (addr_نښې[3]->u.access_ډول == ACCESS_مستقیم
			    || (addr_نښې[3]->u.access_ډول
				== ACCESS_شاخصي_ARRAY)))
		      {
			ونه rt = addr_نښې[1]->بیان;

			gcc_assert (DECL_P (rt));

			إذا (OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_MAP
			    && OMP_CLAUSE_MAP_IMPLICIT (c)
			    && (bitmap_بټ_p (&map_سر, DECL_UID (rt))
				|| bitmap_بټ_p (&map_ډګر_سر, DECL_UID (rt))
				|| bitmap_بټ_p (&map_firstprivate_سر,
						 DECL_UID (rt))))
			  {
			    remove = ریښتیا;
			    اكسر;
			  }
			إذا (bitmap_بټ_p (&map_ډګر_سر, DECL_UID (rt)))
			  اكسر;
			إذا (bitmap_بټ_p (&map_سر, DECL_UID (rt)))
			  {
			    إذا (OMP_CLAUSE_کوډ (c) != OMP_CLAUSE_MAP)
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
			    remove = ریښتیا;
			  }
			وإلا
			  {
			    bitmap_سېټ_بټ (&map_سر, DECL_UID (rt));
			    bitmap_سېټ_بټ (&map_ډګر_سر, DECL_UID (rt));
			  }
		      }
		  }
		إذا (c_oacc_check_attachments (c))
		  remove = ریښتیا;
		إذا (OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_MAP
		    && (OMP_CLAUSE_MAP_ډول (c) == GOMP_MAP_ATTACH
			|| OMP_CLAUSE_MAP_ډول (c) == GOMP_MAP_DETACH)
		    && !OMP_CLAUSE_اندازه (c))
		  /* In this case, we have a single array element which is a
		     pointer, and we already set OMP_CLAUSE_SIZE in
		     handle_omp_array_sections above.  For attach/detach
		     clauses, reset the OMP_CLAUSE_SIZE (representing a bias)
		     to zero here.  */
		  OMP_CLAUSE_اندازه (c) = اندازه_zero_غوټه;
		اكسر;
	      }
	    وإلا إذا (!omp_parse_بیان (addr_نښې, t))
	      {
		sorry_at (OMP_CLAUSE_LOCATION (c),
			  "unsupported map expression %qE",
			  OMP_CLAUSE_DECL (c));
		remove = ریښتیا;
		اكسر;
	      }
	    إذا (t == error_mark_غوټه)
	      {
		remove = ریښتیا;
		اكسر;
	      }

	    ونه attr;
	    إذا (DECL_P (t)
		&& OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_MAP
		&& (attr = lookup_attribute ("omp declare target",
					     DECL_ځانګړتیاوې (t)))
		&& ارزښت_member (get_identifier ("local"),
				 ونه_ارزښت (attr)))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "device-local variable %qD cannot appear "
			  "in map clause", t);
		remove = ریښتیا;
		اكسر;
	      }

	    /* OpenACC attach / detach clauses must be pointers.  */
	    إذا (c_oacc_check_attachments (c))
	      {
		remove = ریښتیا;
		اكسر;
	      }
	    إذا (OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_MAP
		&& (OMP_CLAUSE_MAP_ډول (c) == GOMP_MAP_ATTACH
		    || OMP_CLAUSE_MAP_ډول (c) == GOMP_MAP_DETACH)
		&& !OMP_CLAUSE_اندازه (c))
	      /* For attach/detach clauses, set OMP_CLAUSE_SIZE (representing a
		 bias) to zero here, so it is not set erroneously to the pointer
		 size later on in gimplify.cc.  */
	      OMP_CLAUSE_اندازه (c) = اندازه_zero_غوټه;

	    c_omp_پته_inspector ai (OMP_CLAUSE_LOCATION (c), t);

	    إذا (!ai.check_clause (c))
	      {
		remove = ریښتیا;
		اكسر;
	      }

	    إذا (!ai.map_supported_p ())
	      {
		sorry_at (OMP_CLAUSE_LOCATION (c),
			  "unsupported map expression %qE",
			  OMP_CLAUSE_DECL (c));
		remove = ریښتیا;
		اكسر;
	      }

	    gcc_assert ((addr_نښې[0]->type == ARRAY_بنسټ
			 || addr_نښې[0]->type == STRUCTURE_بنسټ)
			&& addr_نښې[1]->type == ACCESS_لاره);

	    t = addr_نښې[1]->بیان;

	    إذا (addr_نښې[0]->u.structure_بنسټ_ډول != بنسټ_DECL)
	      اذهب skip_decl_checks;

	    /* For OpenMP, we can access a struct "t" and "t.d" on the same
	       mapping.  OpenACC allows multiple fields of the same structure
	       to be written.  */
	    إذا (addr_نښې[0]->type == STRUCTURE_بنسټ
		&& (bitmap_بټ_p (&map_ډګر_سر, DECL_UID (t))
		    || (!openacc && bitmap_بټ_p (&map_سر, DECL_UID (t)))))
	      اذهب skip_decl_checks;

	    إذا (!VAR_P (t) && ونه_کوډ (t) != PARM_DECL)
	      {
		إذا (ort != C_ORT_ACC && بیان_P (t))
		  اكسر;

		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is not a variable in %qs clause", t,
			  omp_clause_کوډ_name[OMP_CLAUSE_کوډ (c)]);
		remove = ریښتیا;
	      }
	    وإلا إذا (VAR_P (t) && DECL_THREAD_LOCAL_P (t))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD is threadprivate variable in %qs clause", t,
			  omp_clause_کوډ_name[OMP_CLAUSE_کوډ (c)]);
		remove = ریښتیا;
	      }
	    وإلا إذا ((OMP_CLAUSE_کوډ (c) != OMP_CLAUSE_MAP
		      || (OMP_CLAUSE_MAP_ډول (c)
			  != GOMP_MAP_FIRSTPRIVATE_اشاره_ګر))
		     && !c_mark_addressable (t))
	      remove = ریښتیا;
	    وإلا إذا (!(OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_MAP
		       && (OMP_CLAUSE_MAP_ډول (c) == GOMP_MAP_اشاره_ګر
			   || (OMP_CLAUSE_MAP_ډول (c)
			       == GOMP_MAP_FIRSTPRIVATE_اشاره_ګر)
			   || (OMP_CLAUSE_MAP_ډول (c)
			       == GOMP_MAP_FORCE_DEVICEPTR)))
		     && t == OMP_CLAUSE_DECL (c)
		     && !omp_mappable_type (ونه_TYPE (t)))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD does not have a mappable type in %qs clause", t,
			  omp_clause_کوډ_name[OMP_CLAUSE_کوډ (c)]);
		remove = ریښتیا;
	      }
	    وإلا إذا (ونه_TYPE (t) == error_mark_غوټه)
	      remove = ریښتیا;
	    وإلا إذا (TYPE_ATOMIC (strip_array_types (ونه_TYPE (t))))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%<_Atomic%> %qE in %qs clause", t,
			  omp_clause_کوډ_name[OMP_CLAUSE_کوډ (c)]);
		remove = ریښتیا;
	      }
	    وإلا إذا (OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_MAP
		     && OMP_CLAUSE_MAP_IMPLICIT (c)
		     && (bitmap_بټ_p (&map_سر, DECL_UID (t))
			 || bitmap_بټ_p (&map_ډګر_سر, DECL_UID (t))
			 || bitmap_بټ_p (&map_firstprivate_سر,
					  DECL_UID (t))))
	      remove = ریښتیا;
	    وإلا إذا (OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_MAP
		     && (OMP_CLAUSE_MAP_ډول (c)
			 == GOMP_MAP_FIRSTPRIVATE_اشاره_ګر))
	      {
		إذا (bitmap_بټ_p (&generic_سر, DECL_UID (t))
		    || bitmap_بټ_p (&firstprivate_سر, DECL_UID (t))
		    || bitmap_بټ_p (&map_firstprivate_سر, DECL_UID (t)))
		  {
		    error_at (OMP_CLAUSE_LOCATION (c),
			      "%qD appears more than once in data clauses", t);
		    remove = ریښتیا;
		  }
		وإلا إذا (bitmap_بټ_p (&map_سر, DECL_UID (t))
			 && !bitmap_بټ_p (&map_ډګر_سر, DECL_UID (t))
			 && openacc)
		  {
		    error_at (OMP_CLAUSE_LOCATION (c),
			      "%qD appears more than once in data clauses", t);
		    remove = ریښتیا;
		  }
		وإلا
		  bitmap_سېټ_بټ (&map_firstprivate_سر, DECL_UID (t));
	      }
	    وإلا إذا (bitmap_بټ_p (&map_سر, DECL_UID (t))
		     && !bitmap_بټ_p (&map_ډګر_سر, DECL_UID (t))
		     && ort != C_ORT_OMP
		     && ort != C_ORT_OMP_موخه
		     && ort != C_ORT_OMP_EXIT_معلومات)
	      {
		إذا (OMP_CLAUSE_کوډ (c) != OMP_CLAUSE_MAP)
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in motion clauses", t);
		وإلا إذا (openacc)
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in data clauses", t);
		وإلا
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in map clauses", t);
		remove = ریښتیا;
	      }
	    وإلا إذا (openacc && bitmap_بټ_p (&generic_سر, DECL_UID (t)))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears more than once in data clauses", t);
		remove = ریښتیا;
	      }
	    وإلا إذا (bitmap_بټ_p (&firstprivate_سر, DECL_UID (t))
		     || bitmap_بټ_p (&is_on_device_سر, DECL_UID (t)))
	      {
		إذا (openacc)
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in data clauses", t);
		وإلا
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears both in data and map clauses", t);
		remove = ریښتیا;
	      }
	    وإلا إذا (!omp_access_chain_p (addr_نښې, 1))
	      {
		bitmap_سېټ_بټ (&map_سر, DECL_UID (t));
		إذا (t != OMP_CLAUSE_DECL (c)
		    && ونه_کوډ (OMP_CLAUSE_DECL (c)) == COMPONENT_REF)
		  bitmap_سېټ_بټ (&map_ډګر_سر, DECL_UID (t));
	      }

	  skip_decl_checks:
	    /* If we call omp_expand_map_clause in handle_omp_array_sections,
	       the containing loop (here) iterates through the new nodes
	       created by that expansion.  Avoid expanding those again (just
	       by checking the node type).  */
	    إذا (!remove
		&& ort != C_ORT_DECLARE_SIMD
		&& (OMP_CLAUSE_کوډ (c) != OMP_CLAUSE_MAP
		    || (OMP_CLAUSE_MAP_ډول (c) != GOMP_MAP_FIRSTPRIVATE_اشاره_ګر
			&& (OMP_CLAUSE_MAP_ډول (c)
			    != GOMP_MAP_FIRSTPRIVATE_REFERENCE)
			&& OMP_CLAUSE_MAP_ډول (c) != GOMP_MAP_ALWAYS_اشاره_ګر
			&& OMP_CLAUSE_MAP_ډول (c) != GOMP_MAP_ATTACH_DETACH
			&& OMP_CLAUSE_MAP_ډول (c) != GOMP_MAP_ATTACH
			&& OMP_CLAUSE_MAP_ډول (c) != GOMP_MAP_DETACH)))
	      {
		grp_پیل_p = pc;
		grp_sentinel = OMP_CLAUSE_CHAIN (c);
		ونه nc = ai.expand_map_clause (c, OMP_CLAUSE_DECL (c),
						addr_نښې, ort);
		إذا (nc != error_mark_غوټه)
		  c = nc;
	      }
	  }
	  اكسر;

	حالة OMP_CLAUSE_ENTER:
	حالة OMP_CLAUSE_LINK:
	حالة OMP_CLAUSE_LOCAL:
	  t = OMP_CLAUSE_DECL (c);
	  ثابت حرف *cname;
	  cname = omp_clause_کوډ_name[OMP_CLAUSE_کوډ (c)];
	  إذا (OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_ENTER
	      && OMP_CLAUSE_ENTER_منزل (c))
	    cname = "to";
	  إذا (ونه_کوډ (t) == FUNCTION_DECL
	      && OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_ENTER)
	    ;
	  وإلا إذا (!VAR_P (t))
	    {
	      إذا (OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_ENTER)
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is neither a variable nor a function name in "
			  "clause %qs", t, cname);
	      وإلا
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is not a variable in clause %qs", t, cname);
	      remove = ریښتیا;
	    }
	  وإلا إذا (DECL_THREAD_LOCAL_P (t))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD is threadprivate variable in %qs clause", t,
			cname);
	      remove = ریښتیا;
	    }
	  وإلا إذا (!omp_mappable_type (ونه_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD does not have a mappable type in %qs clause", t,
			cname);
	      remove = ریښتیا;
	    }
	  إذا (remove)
	    اكسر;
	  إذا (bitmap_بټ_p (&generic_سر, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once on the same "
			"%<declare target%> directive", t);
	      remove = ریښتیا;
	    }
	  وإلا
	    bitmap_سېټ_بټ (&generic_سر, DECL_UID (t));
	  اكسر;

	حالة OMP_CLAUSE_یوشان:
	  t = OMP_CLAUSE_DECL (c);
	  إذا (ونه_کوډ (t) != PARM_DECL)
	    {
	      إذا (DECL_P (t))
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD is not an argument in %<uniform%> clause", t);
	      وإلا
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is not an argument in %<uniform%> clause", t);
	      remove = ریښتیا;
	      اكسر;
	    }
	  /* map_head bitmap is used as uniform_head if declare_simd.  */
	  bitmap_سېټ_بټ (&map_سر, DECL_UID (t));
	  اذهب check_dup_generic;

	حالة OMP_CLAUSE_IS_DEVICE_PTR:
	حالة OMP_CLAUSE_USE_DEVICE_PTR:
	  t = OMP_CLAUSE_DECL (c);
	  إذا (OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_IS_DEVICE_PTR)
	    bitmap_سېټ_بټ (&is_on_device_سر, DECL_UID (t));
	  إذا (ونه_کوډ (ونه_TYPE (t)) != اشاره_ګر_TYPE)
	    {
	      إذا (OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_USE_DEVICE_PTR
		  && !openacc)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qs variable is not a pointer",
			    omp_clause_کوډ_name[OMP_CLAUSE_کوډ (c)]);
		  remove = ریښتیا;
		}
	      وإلا إذا (ونه_کوډ (ونه_TYPE (t)) != ARRAY_TYPE)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qs variable is neither a pointer nor an array",
			    omp_clause_کوډ_name[OMP_CLAUSE_کوډ (c)]);
		  remove = ریښتیا;
		}
	    }
	  اذهب check_dup_generic;

	حالة OMP_CLAUSE_HAS_DEVICE_ADDR:
	  t = OMP_CLAUSE_DECL (c);
	  إذا (ونه_کوډ (t) == OMP_ARRAY_SECTION)
	    {
	      إذا (handle_omp_array_sections (c, ort))
		remove = ریښتیا;
	      وإلا
		{
		  t = OMP_CLAUSE_DECL (c);
		  طالما (ونه_کوډ (t) == ARRAY_REF)
		    t = ونه_عملوند (t, 0);
		}
	    }
	  bitmap_سېټ_بټ (&is_on_device_سر, DECL_UID (t));
	  إذا (VAR_P (t) || ونه_کوډ (t) == PARM_DECL)
	    c_mark_addressable (t);
	  اذهب check_dup_generic_t;

	حالة OMP_CLAUSE_USE_DEVICE_ADDR:
	  t = OMP_CLAUSE_DECL (c);
	  إذا (VAR_P (t) || ونه_کوډ (t) == PARM_DECL)
	    c_mark_addressable (t);
	  اذهب check_dup_generic;

	حالة OMP_CLAUSE_NOWAIT:
	  إذا (copyprivate_کتل_شوی)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<nowait%> clause must not be used together "
			"with %<copyprivate%> clause");
	      remove = ریښتیا;
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
	      remove = ریښتیا;
	      اكسر;
	    }
	  وإلا إذا (ترتیب_clause)
	    {
	      /* Silently remove duplicates.  */
	      remove = ریښتیا;
	      اكسر;
	    }
	  ترتیب_clause = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  استمر;

	حالة OMP_CLAUSE_DETACH:
	  t = OMP_CLAUSE_DECL (c);
	  إذا (detach_کتل_شوی)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"too many %qs clauses on a task construct",
			"detach");
	      remove = ریښتیا;
	      اكسر;
	    }
	  detach_کتل_شوی = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  c_mark_addressable (t);
	  استمر;

	حالة OMP_CLAUSE_IF:
	حالة OMP_CLAUSE_SELF:
	حالة OMP_CLAUSE_عدد_تارونه:
	حالة OMP_CLAUSE_عدد_TEAMS:
	حالة OMP_CLAUSE_THREAD_حد:
	حالة OMP_CLAUSE_DEFAULT:
	حالة OMP_CLAUSE_UNTIED:
	حالة OMP_CLAUSE_COLLAPSE:
	حالة OMP_CLAUSE_FINAL:
	حالة OMP_CLAUSE_DEVICE:
	حالة OMP_CLAUSE_DIST_مهالوېش:
	حالة OMP_CLAUSE_DYN_GROUPPRIVATE:
	حالة OMP_CLAUSE_PARALLEL:
	حالة OMP_CLAUSE_FOR:
	حالة OMP_CLAUSE_SECTIONS:
	حالة OMP_CLAUSE_TASKGROUP:
	حالة OMP_CLAUSE_PROC_BIND:
	حالة OMP_CLAUSE_DEVICE_TYPE:
	حالة OMP_CLAUSE_لومړیتوب:
	حالة OMP_CLAUSE_تارونه:
	حالة OMP_CLAUSE_SIMD:
	حالة OMP_CLAUSE_HINT:
	حالة OMP_CLAUSE_FILTER:
	حالة OMP_CLAUSE_DEFAULTMAP:
	حالة OMP_CLAUSE_BIND:
	حالة OMP_CLAUSE_عدد_GANGS:
	حالة OMP_CLAUSE_عدد_WORKERS:
	حالة OMP_CLAUSE_ویکټور_اوږدتیا:
	حالة OMP_CLAUSE_ASYNC:
	حالة OMP_CLAUSE_WAIT:
	حالة OMP_CLAUSE_AUTO:
	حالة OMP_CLAUSE_INDEPENDENT:
	حالة OMP_CLAUSE_SEQ:
	حالة OMP_CLAUSE_GANG:
	حالة OMP_CLAUSE_کارګر:
	حالة OMP_CLAUSE_ویکټور:
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
	  grainsize_کتل_شوی = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  استمر;

	حالة OMP_CLAUSE_عدد_TASKS:
	  عدد_tasks_کتل_شوی = ریښتیا;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  استمر;

	حالة OMP_CLAUSE_MERGEABLE:
	  mergeable_کتل_شوی = ریښتیا;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  استمر;

	حالة OMP_CLAUSE_NOGROUP:
	  nogroup_کتل_شوی = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  استمر;

	حالة OMP_CLAUSE_مهالوېش:
	  مهالوېش_clause = c;
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

	حالة OMP_CLAUSE_ډک:
	  ډک_کتل_شوی = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  استمر;

	حالة OMP_CLAUSE_PARTIAL:
	  partial_کتل_شوی = ریښتیا;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  استمر;

	حالة OMP_CLAUSE_SIZES:
	  pc = &OMP_CLAUSE_CHAIN (c);
	  استمر;

	حالة OMP_CLAUSE_INBRANCH:
	حالة OMP_CLAUSE_NOTINBRANCH:
	  إذا (branch_کتل_شوی)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<inbranch%> clause is incompatible with "
			"%<notinbranch%>");
	      remove = ریښتیا;
	      اكسر;
	    }
	  branch_کتل_شوی = ریښتیا;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  استمر;

	حالة OMP_CLAUSE_INCLUSIVE:
	حالة OMP_CLAUSE_EXCLUSIVE:
	  need_complete = ریښتیا;
	  need_implicitly_determined = ریښتیا;
	  t = OMP_CLAUSE_DECL (c);
	  إذا (!VAR_P (t) && ونه_کوډ (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %qs", t,
			omp_clause_کوډ_name[OMP_CLAUSE_کوډ (c)]);
	      remove = ریښتیا;
	    }
	  اكسر;

	حالة OMP_CLAUSE_INIT:
	  init_کتل_شوی = ریښتیا;
	  إذا (!OMP_CLAUSE_INIT_TARGETSYNC (c))
	    init_no_targetsync_clause = c;
	  /* FALLTHRU */
	حالة OMP_CLAUSE_DESTROY:
	حالة OMP_CLAUSE_USE:
	  init_use_destroy_کتل_شوی = ریښتیا;
	  t = OMP_CLAUSE_DECL (c);
	  إذا (bitmap_بټ_p (&generic_سر, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD appears more than once in action clauses", t);
	      remove = ریښتیا;
	      اكسر;
	    }
	  bitmap_سېټ_بټ (&generic_سر, DECL_UID (t));
	  /* FALLTHRU */
	حالة OMP_CLAUSE_INTEROP:
	  إذا (/* ort == C_ORT_OMP_INTEROP [uncomment for depobj init]  */
		   !c_omp_interop_t_p (ونه_TYPE (OMP_CLAUSE_DECL (c))))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD must be of %<omp_interop_t%>",
			OMP_CLAUSE_DECL (c));
	      remove = ریښتیا;
	    }
	  وإلا إذا ((OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_INIT
		    || OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_DESTROY)
		   && ونه_READONLY (OMP_CLAUSE_DECL (c)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD shall not be const", OMP_CLAUSE_DECL (c));
	      remove = ریښتیا;
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
	      إذا (t == error_mark_غوټه)
		remove = ریښتیا;
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
		  إذا ((OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_SHARED
		       || OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_FIRSTPRIVATE)
		      && c_omp_predefined_variable (t))
		    /* The __func__ variable and similar function-local
		       predefined variables may be listed in a shared or
		       firstprivate clause.  */
		    اكسر;
		  share_name = "shared";
		  اكسر;
		حالة OMP_CLAUSE_DEFAULT_شخصي:
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
			    omp_clause_کوډ_name[OMP_CLAUSE_کوډ (c)]);
		  remove = ریښتیا;
		}
	      وإلا إذا (ونه_READONLY (t)
		       && OMP_CLAUSE_کوډ (c) != OMP_CLAUSE_SHARED
		       && OMP_CLAUSE_کوډ (c) != OMP_CLAUSE_FIRSTPRIVATE)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<const%> qualified %qE may appear only in "
			    "%<shared%> or %<firstprivate%> clauses", t);
		  remove = ریښتیا;
		}
	    }
	}

      إذا (remove)
	{
	  إذا (grp_پیل_p)
	    {
	      /* If we found a clause to remove, we want to remove the whole
		 expanded group, otherwise gimplify
		 (omp_resolve_clause_dependencies) can get confused.  */
	      *grp_پیل_p = grp_sentinel;
	      pc = grp_پیل_p;
	      grp_پیل_p = عدم;
	    }
	  وإلا
	    *pc = OMP_CLAUSE_CHAIN (c);
	}
      وإلا
	pc = &OMP_CLAUSE_CHAIN (c);
    }

  إذا (grp_پیل_p
      && OMP_CLAUSE_HAS_ITERATORS (*grp_پیل_p))
    لكل (ونه gc = *grp_پیل_p; gc; gc = OMP_CLAUSE_CHAIN (gc))
      OMP_CLAUSE_ITERATORS (gc) = OMP_CLAUSE_ITERATORS (*grp_پیل_p);

  إذا (simdlen
      && safelen
      && ونه_int_cst_lt (OMP_CLAUSE_SAFELEN_بیان (safelen),
			  OMP_CLAUSE_SIMDLEN_بیان (simdlen)))
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
      OMP_CLAUSE_SIMDLEN_بیان (simdlen)
	= OMP_CLAUSE_SAFELEN_بیان (safelen);
    }

  إذا (ordered_clause
      && مهالوېش_clause
      && (OMP_CLAUSE_مهالوېش_ډول (مهالوېش_clause)
	  & OMP_CLAUSE_مهالوېش_NONMONOTONIC))
    {
      error_at (OMP_CLAUSE_LOCATION (مهالوېش_clause),
		"%<nonmonotonic%> schedule modifier specified together "
		"with %<ordered%> clause");
      OMP_CLAUSE_مهالوېش_ډول (مهالوېش_clause)
	= (تعداد omp_clause_مهالوېش_ډول)
	  (OMP_CLAUSE_مهالوېش_ډول (مهالوېش_clause)
	   & ~OMP_CLAUSE_مهالوېش_NONMONOTONIC);
    }

  إذا (reduction_کتل_شوی < 0 && ordered_clause)
    {
      error_at (OMP_CLAUSE_LOCATION (ordered_clause),
		"%qs clause specified together with %<inscan%> "
		"%<reduction%> clause", "ordered");
      reduction_کتل_شوی = -2;
    }

  إذا (reduction_کتل_شوی < 0 && مهالوېش_clause)
    {
      error_at (OMP_CLAUSE_LOCATION (مهالوېش_clause),
		"%qs clause specified together with %<inscan%> "
		"%<reduction%> clause", "schedule");
      reduction_کتل_شوی = -2;
    }

  إذا (خطي_variable_ګام_check
      || reduction_کتل_شوی == -2
      || allocate_کتل_شوی
      || موخه_دننه_reduction_کتل_شوی)
    لكل (pc = &clauses, c = clauses; c ; c = *pc)
      {
	منطقي remove = خطأ;
	إذا (allocate_کتل_شوی)
	  بدل (OMP_CLAUSE_کوډ (c))
	    {
	    حالة OMP_CLAUSE_REDUCTION:
	    حالة OMP_CLAUSE_دننه_REDUCTION:
	    حالة OMP_CLAUSE_TASK_REDUCTION:
	      إذا (ونه_کوډ (OMP_CLAUSE_DECL (c)) == MEM_REF)
		{
		  t = ونه_عملوند (OMP_CLAUSE_DECL (c), 0);
		  إذا (ونه_کوډ (t) == اشاره_ګر_PLUS_بیان)
		    t = ونه_عملوند (t, 0);
		  إذا (ونه_کوډ (t) == ADDR_بیان
		      || غیرمستقیم_REF_P (t))
		    t = ونه_عملوند (t, 0);
		  إذا (DECL_P (t))
		    bitmap_clear_بټ (&aligned_سر, DECL_UID (t));
		  اكسر;
		}
	      /* FALLTHRU */
	    حالة OMP_CLAUSE_شخصي:
	    حالة OMP_CLAUSE_FIRSTPRIVATE:
	    حالة OMP_CLAUSE_LASTPRIVATE:
	    حالة OMP_CLAUSE_خطي:
	      إذا (DECL_P (OMP_CLAUSE_DECL (c)))
		bitmap_clear_بټ (&aligned_سر,
				  DECL_UID (OMP_CLAUSE_DECL (c)));
	      اكسر;
	    افتراضي:
	      اكسر;
	    }
	إذا (OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_خطي
	    && OMP_CLAUSE_خطي_VARIABLE_STRIDE (c)
	    && !bitmap_بټ_p (&map_سر,
			      DECL_UID (OMP_CLAUSE_خطي_ګام (c))))
	  {
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%<linear%> clause step is a parameter %qD not "
		      "specified in %<uniform%> clause",
		      OMP_CLAUSE_خطي_ګام (c));
	    remove = ریښتیا;
	  }
	وإلا إذا (OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_REDUCTION
		 && reduction_کتل_شوی == -2)
	  OMP_CLAUSE_REDUCTION_INSCAN (c) = 0;
	إذا (موخه_دننه_reduction_کتل_شوی
	    && OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_MAP)
	  {
	    ونه t = OMP_CLAUSE_DECL (c);
	    طالما (handled_component_p (t)
		   || غیرمستقیم_REF_P (t)
		   || ونه_کوډ (t) == ADDR_بیان
		   || ونه_کوډ (t) == MEM_REF
		   || ونه_کوډ (t) == NON_LVALUE_بیان)
	      t = ونه_عملوند (t, 0);
	    إذا (DECL_P (t)
		&& bitmap_بټ_p (&oacc_reduction_سر, DECL_UID (t)))
	      OMP_CLAUSE_MAP_دننه_REDUCTION (c) = 1;
	  }

	إذا (remove)
	  *pc = OMP_CLAUSE_CHAIN (c);
	وإلا
	  pc = &OMP_CLAUSE_CHAIN (c);
      }

  إذا (allocate_کتل_شوی)
    لكل (pc = &clauses, c = clauses; c ; c = *pc)
      {
	منطقي remove = خطأ;
	إذا (OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_ALLOCATE
	    && !OMP_CLAUSE_ALLOCATE_COMBINED (c)
	    && bitmap_بټ_p (&aligned_سر, DECL_UID (OMP_CLAUSE_DECL (c))))
	  {
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD specified in %<allocate%> clause but not in "
		      "an explicit privatization clause", OMP_CLAUSE_DECL (c));
	    remove = ریښتیا;
	  }
	إذا (remove)
	  *pc = OMP_CLAUSE_CHAIN (c);
	وإلا
	  pc = &OMP_CLAUSE_CHAIN (c);
      }

  إذا (nogroup_کتل_شوی && reduction_کتل_شوی)
    {
      error_at (OMP_CLAUSE_LOCATION (*nogroup_کتل_شوی),
		"%<nogroup%> clause must not be used together with "
		"%<reduction%> clause");
      *nogroup_کتل_شوی = OMP_CLAUSE_CHAIN (*nogroup_کتل_شوی);
    }

  إذا (grainsize_کتل_شوی && عدد_tasks_کتل_شوی)
    {
      error_at (OMP_CLAUSE_LOCATION (*grainsize_کتل_شوی),
		"%<grainsize%> clause must not be used together with "
		"%<num_tasks%> clause");
      *grainsize_کتل_شوی = OMP_CLAUSE_CHAIN (*grainsize_کتل_شوی);
    }

  إذا (ډک_کتل_شوی && partial_کتل_شوی)
    {
      error_at (OMP_CLAUSE_LOCATION (*ډک_کتل_شوی),
		"%<full%> clause must not be used together with "
		"%<partial%> clause");
      *ډک_کتل_شوی = OMP_CLAUSE_CHAIN (*ډک_کتل_شوی);
    }

  إذا (detach_کتل_شوی)
    {
      إذا (mergeable_کتل_شوی)
	{
	  error_at (OMP_CLAUSE_LOCATION (*detach_کتل_شوی),
		    "%<detach%> clause must not be used together with "
		    "%<mergeable%> clause");
	  *detach_کتل_شوی = OMP_CLAUSE_CHAIN (*detach_کتل_شوی);
	}
      وإلا
	{
	  ونه detach_decl = OMP_CLAUSE_DECL (*detach_کتل_شوی);

	  لكل (pc = &clauses, c = clauses; c ; c = *pc)
	    {
	      منطقي remove = خطأ;
	      إذا ((OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_SHARED
		   || OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_شخصي
		   || OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_FIRSTPRIVATE
		   || OMP_CLAUSE_کوډ (c) == OMP_CLAUSE_LASTPRIVATE)
		  && OMP_CLAUSE_DECL (c) == detach_decl)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "the event handle of a %<detach%> clause "
			    "should not be in a data-sharing clause");
		  remove = ریښتیا;
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
      && (!init_use_destroy_کتل_شوی
	  || (init_کتل_شوی && init_no_targetsync_clause)))
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

ونه
c_omp_پای_mapper_clauses (ونه clauses)
{
  أرجع c_پای_omp_clauses (clauses, C_ORT_OMP);
}

/* Return code to initialize DST with a copy constructor from SRC.
   C doesn't have copy constructors nor assignment operators, only for
   _Atomic vars we need to perform __atomic_load from src into a temporary
   followed by __atomic_store of the temporary to dst.  */

ونه
c_omp_clause_copy_ctor (ونه clause, ونه dst, ونه src)
{
  إذا (!really_atomic_lvalue (dst) && !really_atomic_lvalue (src))
    أرجع build2 (MODIFY_بیان, ونه_TYPE (dst), dst, src);

  location_t loc = OMP_CLAUSE_LOCATION (clause);
  ونه type = ونه_TYPE (dst);
  ونه nonatomic_type = build_qualified_type (type, TYPE_UNQUALIFIED);
  ونه tmp = create_tmp_var (nonatomic_type);
  ونه tmp_addr = build_fold_addr_بیان (tmp);
  ونه_ADDRESSABLE (tmp) = 1;
  suppress_warning (tmp);
  ونه src_addr = build_fold_addr_بیان (src);
  ونه dst_addr = build_fold_addr_بیان (dst);
  ونه seq_cst = build_int_cst (integer_type_غوټه, MEMMODEL_SEQ_CST);
  vec<ونه, va_gc> *params;
  /* Expansion of a generic atomic load may require an addition
     element, so allocate enough to prevent a resize.  */
  vec_alloc (params, 4);

  /* Build __atomic_load (&src, &tmp, SEQ_CST);  */
  ونه fndecl = builtin_decl_explicit (BUILT_دننه_ATOMIC_بارول);
  params->چټک_ټېل (src_addr);
  params->چټک_ټېل (tmp_addr);
  params->چټک_ټېل (seq_cst);
  ونه بارول = c_build_function_call_vec (loc, vNULL, fndecl, params, عدم);

  vec_alloc (params, 4);

  /* Build __atomic_store (&dst, &tmp, SEQ_CST);  */
  fndecl = builtin_decl_explicit (BUILT_دننه_ATOMIC_STORE);
  params->چټک_ټېل (dst_addr);
  params->چټک_ټېل (tmp_addr);
  params->چټک_ټېل (seq_cst);
  ونه store = c_build_function_call_vec (loc, vNULL, fndecl, params, عدم);
  أرجع build2 (COMPOUND_بیان, void_type_غوټه, بارول, store);
}

/* Create a transaction node.  */

ونه
c_پای_transaction (location_t loc, ونه بلاک, صحيح flags)
{
  ونه stmt = build_stmt (loc, TRANSACTION_بیان, بلاک);
  إذا (flags & TM_STMT_ATTR_OUTER)
    TRANSACTION_بیان_OUTER (stmt) = 1;
  إذا (flags & TM_STMT_ATTR_RELAXED)
    TRANSACTION_بیان_RELAXED (stmt) = 1;
  أرجع جمع_کړه_stmt (stmt);
}

/* Make a variant type in the proper way for C/C++, propagating qualifiers
   down to the element type of an array.  If ORIG_QUAL_TYPE is not
   NULL, then it should be used as the qualified type
   ORIG_QUAL_INDIRECT levels down in array type derivation (to
   preserve information about the typedef name from which an array
   type was derived).  */

ونه
c_build_qualified_type (ونه type, صحيح type_quals, ونه orig_qual_type,
			اندازه_t orig_qual_غیرمستقیم)
{
  إذا (type == error_mark_غوټه)
    أرجع type;

  إذا (ونه_کوډ (type) == ARRAY_TYPE)
    {
      ونه t;
      ونه element_type = c_build_qualified_type (ونه_TYPE (type),
						  type_quals, orig_qual_type,
						  orig_qual_غیرمستقیم - 1);

      /* See if we already have an identically qualified type.  */
      إذا (orig_qual_type && orig_qual_غیرمستقیم == 0)
	t = orig_qual_type;
      وإلا
	لكل (t = TYPE_MAIN_VARIANT (type); t; t = TYPE_بل_VARIANT (t))
	  {
	    إذا (TYPE_QUALS (strip_array_types (t)) == type_quals
		&& TYPE_NAME (t) == TYPE_NAME (type)
		&& TYPE_CONTEXT (t) == TYPE_CONTEXT (type)
		&& attribute_list_equal (TYPE_ځانګړتیاوې (t),
					 TYPE_ځانګړتیاوې (type)))
	      اكسر;
	  }
      إذا (!t)
	{
          ونه domain = TYPE_DOMAIN (type);

	  t = build_variant_type_copy (type);
	  ونه_TYPE (t) = element_type;
	  TYPE_ADDR_SPACE (t) = TYPE_ADDR_SPACE (element_type);

          إذا (TYPE_STRUCTURAL_EQUALITY_P (element_type)
              || (domain && TYPE_STRUCTURAL_EQUALITY_P (domain)))
            سېټ_TYPE_STRUCTURAL_EQUALITY (t);
          وإلا إذا (TYPE_CANONICAL (element_type) != element_type
                   || (domain && TYPE_CANONICAL (domain) != domain))
            {
              ونه unqualified_canon
		= c_build_array_type (TYPE_CANONICAL (element_type),
				      domain ? TYPE_CANONICAL (domain)
					     : NULL_ونه);
              إذا (TYPE_سرچپه_STORAGE_ترتیب (type))
                {
                  unqualified_canon
		    = build_distinct_type_copy (unqualified_canon);
                  TYPE_سرچپه_STORAGE_ترتیب (unqualified_canon) = 1;
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
      && (!اشاره_ګر_TYPE_P (type)
	  || !C_TYPE_OBJECT_OR_INCOMPLETE_P (ونه_TYPE (type))))
    {
      error ("invalid use of %<restrict%>");
      type_quals &= ~TYPE_QUAL_RESTRICT;
    }

  ونه var_type = (orig_qual_type && orig_qual_غیرمستقیم == 0
		   ? orig_qual_type
		   : build_qualified_type (type, type_quals));

  gcc_checking_assert (C_TYPE_VARIABLE_اندازه (var_type)
		       == C_TYPE_VARIABLE_اندازه (type));
  gcc_checking_assert (c_type_variably_modified_p (var_type)
		       == c_type_variably_modified_p (type));

  /* A variant type does not inherit the list of incomplete vars from the
     type main variant.  */
  إذا ((ریکارډ_OR_UNION_TYPE_P (var_type)
       || ونه_کوډ (var_type) == ENUMERAL_TYPE)
      && TYPE_MAIN_VARIANT (var_type) != var_type)
    C_TYPE_INCOMPLETE_VARS (var_type) = 0;
  أرجع var_type;
}

/* Build a VA_ARG_EXPR for the C parser.  */

ونه
c_build_va_arg (location_t loc1, ونه بیان, location_t loc2, ونه type,
		ونه type_بیان)
{
  إذا (error_عملوند_p (type))
    أرجع error_mark_غوټه;
  /* VA_ARG_EXPR cannot be used for a scalar va_list with reverse storage
     order because it takes the address of the expression.  */
  وإلا إذا (handled_component_p (بیان)
	   && سرچپه_storage_ترتیب_for_component_p (بیان))
    {
      error_at (loc1, "cannot use %<va_arg%> with reverse storage order");
      أرجع error_mark_غوټه;
    }
  وإلا إذا (!COMPLETE_TYPE_P (type))
    {
      error_at (loc2, "second argument to %<va_arg%> is of incomplete "
		"type %qT", type);
      أرجع error_mark_غوټه;
    }
  وإلا إذا (ونه_کوډ (type) == FUNCTION_TYPE)
    {
      error_at (loc2, "second argument to %<va_arg%> is a function type %qT",
		type);
      أرجع error_mark_غوټه;
    }
  وإلا إذا (ونه_کوډ (type) == ARRAY_TYPE && C_TYPE_VARIABLE_اندازه (type)
	   && !flag_isoc99)
    {
      error_at (loc2, "second argument to %<va_arg%> is an array type %qT",
		type);
      أرجع error_mark_غوټه;
    }
  وإلا إذا (warn_cxx_compat && ونه_کوډ (type) == ENUMERAL_TYPE)
    warning_at (loc2, OPT_Wc___compat,
		"C++ requires promoted type, not enum type, in %<va_arg%>");

  إذا (flag_isoc99 && ونه_کوډ (type) == ARRAY_TYPE)
    {
      warning_at (loc2, 0, "second argument to %<va_arg%> is an array type %qT",
		  type);
      /* We create a trap but evaluate side effects first.  */
      ونه trapfn = builtin_decl_explicit (BUILT_دننه_TRAP);
      trapfn = build_call_بیان_loc (loc2, trapfn, 0);
      ونه e2 = build2 (COMPOUND_بیان, void_type_غوټه, بیان, trapfn);
      /* Return a compound literal of the right type.  */
      ونه e1 = build_compound_literal (loc2, type, عدم, ریښتیا, 0, عدم);
      بیان = build2 (COMPOUND_بیان, type, e2, e1);
    }
  وإلا
    بیان = build_va_arg (loc2, بیان, type);

  إذا (type_بیان)
    بیان = build2 (COMPOUND_بیان, ونه_TYPE (بیان), type_بیان, بیان);

  أرجع بیان;
}

/* Return truthvalue of whether T1 is the same tree structure as T2.
   Return 1 if they are the same. Return false if they are different.  */

منطقي
c_ونه_equal (ونه t1, ونه t2)
{
  تعداد ونه_کوډ_2 code1, code2;

  إذا (t1 == t2)
    أرجع ریښتیا;
  إذا (!t1 || !t2)
    أرجع خطأ;

  لكل (code1 = ونه_کوډ (t1); code1 == NON_LVALUE_بیان;
       code1 = ونه_کوډ (t1))
    t1 = ونه_عملوند (t1, 0);
  لكل (code2 = ونه_کوډ (t2); code2 == NON_LVALUE_بیان;
       code2 = ونه_کوډ (t2))
    t2 = ونه_عملوند (t2, 0);

  /* They might have become equal now.  */
  إذا (t1 == t2)
    أرجع ریښتیا;

  إذا (code1 != code2)
    أرجع خطأ;

  إذا (CONSTANT_CLASS_P (t1) && !comptypes (ونه_TYPE (t1), ونه_TYPE (t2)))
    أرجع خطأ;

  بدل (code1)
    {
    حالة INTEGER_CST:
      أرجع wi::منزل_wide (t1) == wi::منزل_wide (t2);

    حالة REAL_CST:
      أرجع real_equal (&ونه_REAL_CST (t1), &ونه_REAL_CST (t2));

    حالة STRING_CST:
      أرجع ونه_STRING_اوږدتیا (t1) == ونه_STRING_اوږدتیا (t2)
	&& !memcmp (ونه_STRING_اشاره_ګر (t1), ونه_STRING_اشاره_ګر (t2),
		    ونه_STRING_اوږدتیا (t1));

    حالة FIXED_CST:
      أرجع FIXED_ارزښتونه_IDENTICAL (ونه_FIXED_CST (t1),
				     ونه_FIXED_CST (t2));

    حالة COMPLEX_CST:
      أرجع c_ونه_equal (ونه_REALPART (t1), ونه_REALPART (t2))
	     && c_ونه_equal (ونه_IMAGPART (t1), ونه_IMAGPART (t2));

    حالة ویکټور_CST:
      أرجع عملوند_equal_p (t1, t2, OEP_ONLY_CONST);

    حالة CONSTRUCTOR:
      /* We need to do this when determining whether or not two
	 non-type pointer to member function template arguments
	 are the same.  */
      إذا (!comptypes (ونه_TYPE (t1), ونه_TYPE (t2))
	  || CONSTRUCTOR_NELTS (t1) != CONSTRUCTOR_NELTS (t2))
	أرجع خطأ;
      {
	ونه ډګر_2, ارزښت;
	بینښه صحيح i;
	FOR_EACH_CONSTRUCTOR_ELT (CONSTRUCTOR_ELTS (t1), i, ډګر_2, ارزښت)
	  {
	    constructor_elt *elt2 = CONSTRUCTOR_ELT (t2, i);
	    إذا (!c_ونه_equal (ډګر_2, elt2->شاخص)
		|| !c_ونه_equal (ارزښت, elt2->ارزښت))
	      أرجع خطأ;
	  }
      }
      أرجع ریښتیا;

    حالة ونه_LIST:
      إذا (!c_ونه_equal (ونه_PURPOSE (t1), ونه_PURPOSE (t2)))
	أرجع خطأ;
      إذا (!c_ونه_equal (ونه_ارزښت (t1), ونه_ارزښت (t2)))
	أرجع خطأ;
      أرجع c_ونه_equal (ونه_CHAIN (t1), ونه_CHAIN (t2));

    حالة SAVE_بیان:
      أرجع c_ونه_equal (ونه_عملوند (t1, 0), ونه_عملوند (t2, 0));

    حالة CALL_بیان:
      {
	ونه arg1, arg2;
	call_بیان_arg_iterator iter1, iter2;
	إذا (!c_ونه_equal (CALL_بیان_FN (t1), CALL_بیان_FN (t2)))
	  أرجع خطأ;
	لكل (arg1 = لومړی_call_بیان_arg (t1, &iter1),
	       arg2 = لومړی_call_بیان_arg (t2, &iter2);
	     arg1 && arg2;
	     arg1 = بل_call_بیان_arg (&iter1),
	       arg2 = بل_call_بیان_arg (&iter2))
	  إذا (!c_ونه_equal (arg1, arg2))
	    أرجع خطأ;
	إذا (arg1 || arg2)
	  أرجع خطأ;
	أرجع ریښتیا;
      }

    حالة موخه_بیان:
      {
	ونه o1 = ونه_عملوند (t1, 0);
	ونه o2 = ونه_عملوند (t2, 0);

	/* Special case: if either target is an unallocated VAR_DECL,
	   it means that it's going to be unified with whatever the
	   TARGET_EXPR is really supposed to initialize, so treat it
	   as being equivalent to anything.  */
	إذا (VAR_P (o1) && DECL_NAME (o1) == NULL_ونه
	    && !DECL_RTL_سېټ_P (o1))
	  /*Nop*/;
	وإلا إذا (VAR_P (o2) && DECL_NAME (o2) == NULL_ونه
		 && !DECL_RTL_سېټ_P (o2))
	  /*Nop*/;
	وإلا إذا (!c_ونه_equal (o1, o2))
	  أرجع خطأ;

	أرجع c_ونه_equal (ونه_عملوند (t1, 1), ونه_عملوند (t2, 1));
      }

    حالة COMPONENT_REF:
      إذا (ونه_عملوند (t1, 1) != ونه_عملوند (t2, 1))
	أرجع خطأ;
      أرجع c_ونه_equal (ونه_عملوند (t1, 0), ونه_عملوند (t2, 0));

    حالة PARM_DECL:
    حالة VAR_DECL:
    حالة CONST_DECL:
    حالة ډګر_DECL:
    حالة FUNCTION_DECL:
    حالة IDENTIFIER_غوټه:
    حالة SSA_NAME:
      أرجع خطأ;

    حالة ونه_VEC:
      {
	بینښه ix;
	إذا (ونه_VEC_اوږدتیا (t1) != ونه_VEC_اوږدتیا (t2))
	  أرجع خطأ;
	لكل (ix = ونه_VEC_اوږدتیا (t1); ix--;)
	  إذا (!c_ونه_equal (ونه_VEC_ELT (t1, ix),
			     ونه_VEC_ELT (t2, ix)))
	    أرجع خطأ;
	أرجع ریښتیا;
      }

    CASE_CONVERT:
      إذا (!comptypes (ونه_TYPE (t1), ونه_TYPE (t2)))
	أرجع خطأ;
      اكسر;

    افتراضي:
      اكسر;
    }

  بدل (ونه_کوډ_CLASS (code1))
    {
    حالة tcc_unary:
    حالة tcc_دوګونی:
    حالة tcc_comparison:
    حالة tcc_افاده:
    حالة tcc_vl_exp:
    حالة tcc_reference:
    حالة tcc_statement:
      {
	صحيح i, n = ونه_عملوند_اوږدتیا (t1);

	بدل (code1)
	  {
	  حالة PREINCREMENT_بیان:
	  حالة PREDECREMENT_بیان:
	  حالة POSTINCREMENT_بیان:
	  حالة POSTDECREMENT_بیان:
	    n = 1;
	    اكسر;
	  حالة ARRAY_REF:
	    n = 2;
	    اكسر;
	  افتراضي:
	    اكسر;
	  }

	إذا (ونه_کوډ_CLASS (code1) == tcc_vl_exp
	    && n != ونه_عملوند_اوږدتیا (t2))
	  أرجع خطأ;

	لكل (i = 0; i < n; ++i)
	  إذا (!c_ونه_equal (ونه_عملوند (t1, i), ونه_عملوند (t2, i)))
	    أرجع خطأ;

	أرجع ریښتیا;
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
c_decl_implicit (const_ونه fndecl)
{
  أرجع C_DECL_IMPLICIT (fndecl);
}
