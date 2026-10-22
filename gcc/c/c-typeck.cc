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
  ic_assign,
  ic_init,
  ic_init_const,
  ic_return
};

/* The level of nesting inside "__alignof__".  */
صحيح in_alignof;

/* The level of nesting inside "sizeof".  */
صحيح in_sizeof;

/* The level of nesting inside "countof".  */
صحيح in_countof;

/* The level of nesting inside "typeof".  */
صحيح in_typeof;

/* The level of nesting inside "_Generic".  */
صحيح in_generic;

/* True when parsing OpenMP loop expressions.  */
منطقي c_in_omp_for;

/* True when parsing OpenMP map clause.  */
منطقي c_omp_array_section_p;

/* The argument of last parsed sizeof expression, only to be tested
   if expr.original_code == SIZEOF_EXPR.  */
شجرة c_last_sizeof_arg;
location_t c_last_sizeof_loc;

/* Nonzero if we might need to print a "missing braces around
   initializer" message within this initializer.  */
ساكن صحيح found_missing_braces;

ساكن منطقي require_constant_قيمة;
ساكن منطقي require_constant_elements;
ساكن منطقي require_constexpr_قيمة;

ساكن شجرة qualify_type (شجرة, شجرة);
بنية comptypes_data;
ساكن منطقي tagged_types_tu_compatible_p (const_شجرة, const_شجرة,
					  بنية comptypes_data *);
ساكن منطقي comp_target_types (location_t, شجرة, شجرة);
ساكن منطقي function_types_compatible_p (const_شجرة, const_شجرة,
					 بنية comptypes_data *);
ساكن منطقي type_lists_compatible_p (const_شجرة, const_شجرة,
				     بنية comptypes_data *);
ساكن صحيح convert_arguments (location_t, vec<location_t>, شجرة,
			      vec<شجرة, va_gc> *, vec<شجرة, va_gc> *, شجرة,
			      شجرة);
ساكن شجرة pointer_diff (location_t, شجرة, شجرة, شجرة *);
ساكن شجرة convert_for_assignment (location_t, location_t, شجرة, شجرة, شجرة,
				    تعداد impl_conv, منطقي, شجرة, شجرة, صحيح,
				    صحيح = 0);
ساكن شجرة valid_compound_تعبير_initializer (شجرة, شجرة);
ساكن فراغ ادفع_string (ثابت حرف *);
ساكن فراغ ادفع_member_name (شجرة);
ساكن صحيح spelling_length (فراغ);
ساكن حرف *اطبع_spelling (حرف *);
ساكن فراغ warning_init (location_t, صحيح, ثابت حرف *);
ساكن شجرة digest_init (location_t, شجرة, شجرة, شجرة, شجرة, منطقي, منطقي, منطقي,
			 منطقي, منطقي, منطقي);
ساكن فراغ output_init_element (location_t, شجرة, شجرة, منطقي, شجرة, شجرة, منطقي,
				 منطقي, بنية obstack *);
ساكن فراغ output_pending_init_elements (صحيح, بنية obstack *);
ساكن منطقي set_designator (location_t, منطقي, بنية obstack *);
ساكن فراغ ادفع_range_مكدس (شجرة, بنية obstack *);
ساكن فراغ add_pending_init (location_t, شجرة, شجرة, شجرة, منطقي,
			      بنية obstack *);
ساكن فراغ set_nonincremental_init (بنية obstack *);
ساكن فراغ set_nonincremental_init_from_string (شجرة, بنية obstack *);
ساكن شجرة find_init_member (شجرة, بنية obstack *);
ساكن فراغ readonly_warning (شجرة, تعداد lvalue_use);
ساكن صحيح lvalue_or_else (location_t, const_شجرة, تعداد lvalue_use);
ساكن فراغ record_maybe_used_decl (شجرة, منطقي address);
ساكن منطقي comptypes_internal (const_شجرة, const_شجرة,
				بنية comptypes_data *data);
ساكن منطقي comptypes_check_for_composite (شجرة t1, شجرة t2);
ساكن منطقي handle_counted_by_p (شجرة);
ساكن منطقي قمة_array_vla_p (const_شجرة type);


/* Return true if EXP is a null pointer constant, false otherwise.  */

منطقي
null_pointer_constant_p (const_شجرة تعبير)
{
  /* This should really operate on c_expr structures, but they aren't
     yet available everywhere required.  */
  شجرة type = شجرة_TYPE (تعبير);

  /* An integer constant expression with the value 0, such an expression
     cast to type void*, or the predefined constant nullptr, are a null
     pointer constant.  */
  إذا (تعبير == nullptr_عقدة)
    أرجع true;

  أرجع (شجرة_CODE (تعبير) == INTEGER_CST
	  && !شجرة_OVERFLOW (تعبير)
	  && integer_zerop (تعبير)
	  && (INTEGRAL_TYPE_P (type)
	      || (شجرة_CODE (type) == POINTER_TYPE
		  && VOID_TYPE_P (شجرة_TYPE (type))
		  && TYPE_QUALS (شجرة_TYPE (type)) == TYPE_UNQUALIFIED)));
}

/* EXPR may appear in an unevaluated part of an integer constant
   expression, but not in an evaluated part.  Wrap it in a
   C_MAYBE_CONST_EXPR, or mark it with TREE_OVERFLOW if it is just an
   INTEGER_CST and we cannot create a C_MAYBE_CONST_EXPR.  */

ساكن شجرة
note_integer_operands (شجرة تعبير)
{
  شجرة ret;
  إذا (شجرة_CODE (تعبير) == INTEGER_CST && in_late_ثنائي_op)
    {
      ret = copy_عقدة (تعبير);
      شجرة_OVERFLOW (ret) = 1;
    }
  وإلا
    {
      ret = build2 (C_MAYBE_CONST_تعبير, شجرة_TYPE (تعبير), NULL_شجرة, تعبير);
      C_MAYBE_CONST_تعبير_INT_OPERANDS (ret) = 1;
    }
  أرجع ret;
}

/* Having checked whether EXPR may appear in an unevaluated part of an
   integer constant expression and found that it may, remove any
   C_MAYBE_CONST_EXPR noting this fact and return the resulting
   expression.  */

ساكن مضمن شجرة
remove_c_maybe_const_تعبير (شجرة تعبير)
{
  إذا (شجرة_CODE (تعبير) == C_MAYBE_CONST_تعبير)
    أرجع C_MAYBE_CONST_تعبير_تعبير (تعبير);
  وإلا
    أرجع تعبير;
}

/* This is a cache to hold if two types are seen.  */

بنية tagged_tu_seen_cache {
  ثابت بنية tagged_tu_seen_cache * next;
  const_شجرة t1;
  const_شجرة t2;
};

/* Do `exp = require_complete_type (loc, exp);' to make sure exp
   does not have an incomplete type.  (That includes void types.)
   LOC is the location of the use.  */

شجرة
require_complete_type (location_t loc, شجرة قيمة)
{
  شجرة type = شجرة_TYPE (قيمة);

  إذا (error_operand_p (قيمة))
    أرجع error_mark_عقدة;

  /* First, detect a valid value with a complete type.  */
  إذا (COMPLETE_TYPE_P (type))
    أرجع قيمة;

  c_incomplete_type_error (loc, قيمة, type);
  أرجع error_mark_عقدة;
}

/* Print an error message for invalid use of an incomplete type.
   VALUE is the expression that was used (or 0 if that isn't known)
   and TYPE is the type that was invalid.  LOC is the location for
   the error.  */

فراغ
c_incomplete_type_error (location_t loc, const_شجرة قيمة, const_شجرة type)
{
  /* Avoid duplicate error message.  */
  إذا (شجرة_CODE (type) == ERROR_MARK)
    أرجع;

  إذا (قيمة != NULL_شجرة && (VAR_P (قيمة) || شجرة_CODE (قيمة) == PARM_DECL))
    error_at (loc, "%qD has an incomplete type %qT", قيمة, type);
  وإلا
    {
    retry:
      /* We must print an error message.  Be clever about what it says.  */

      بدل (شجرة_CODE (type))
	{
	حالة RECORD_TYPE:
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
	      type = شجرة_TYPE (type);
	      اذهب retry;
	    }
	  error_at (loc, "invalid use of array with unspecified bounds");
	  أرجع;

	افتراضي:
	  gcc_unreachable ();
	}

      إذا (شجرة_CODE (TYPE_NAME (type)) == IDENTIFIER_عقدة)
	error_at (loc, "invalid use of undefined type %qT", type);
      وإلا
	/* If this type has a typedef-name, the TYPE_NAME is a TYPE_DECL.  */
	error_at (loc, "invalid use of incomplete typedef %qT", type);
    }
}

/* Given a type, apply default promotions wrt unnamed function
   arguments and return the new type.  */

شجرة
c_type_promotes_to (شجرة type)
{
  شجرة ret = NULL_شجرة;

  إذا (TYPE_MAIN_VARIANT (type) == float_type_عقدة)
    ret = double_type_عقدة;
  وإلا إذا (c_promoting_integer_type_p (type))
    {
      /* Preserve unsignedness if not really getting any wider.  */
      إذا (TYPE_UNSIGNED (type)
	  && (TYPE_PRECISION (type) == TYPE_PRECISION (integer_type_عقدة)))
	ret = unsigned_type_عقدة;
      وإلا
	ret = integer_type_عقدة;
    }

  إذا (ret != NULL_شجرة)
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
      أرجع true;
    }
  وإلا إذا (targetm.addr_space.subset_p (as1, as2))
    {
      *common = as2;
      أرجع true;
    }
  وإلا إذا (targetm.addr_space.subset_p (as2, as1))
    {
      *common = as1;
      أرجع true;
    }
  وإلا
    أرجع خطأ;
}

/* Return a variant of TYPE which has all the type qualifiers of LIKE
   as well as those of TYPE.  */

ساكن شجرة
qualify_type (شجرة type, شجرة like)
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
c_verify_type (شجرة type)
{
  بدل (شجرة_CODE (type))
    {
    حالة POINTER_TYPE:
    حالة FUNCTION_TYPE:
    حالة ARRAY_TYPE:
      /* Pointer, array, functions are variably modified if and only if the
	 target, element, return type is variably modified.  */
      إذا (!TYPE_STRUCTURAL_EQUALITY_P (type)
	  && (C_TYPE_VARIABLY_MODIFIED (type)
	      != C_TYPE_VARIABLY_MODIFIED (شجرة_TYPE (type))))
	أرجع خطأ;
      /* If the target type is structural equality, the type should also. */
      إذا (!TYPE_STRUCTURAL_EQUALITY_P (type)
	  && TYPE_STRUCTURAL_EQUALITY_P (شجرة_TYPE (type)))
	أرجع خطأ;
    افتراضي:
       اكسر;
    }

  بدل (شجرة_CODE (type))
    {
    حالة POINTER_TYPE:
    حالة FUNCTION_TYPE:
      /* Pointer and functions can not have variable size.  */
      إذا (C_TYPE_VARIABLE_SIZE (type))
	أرجع خطأ;
      اكسر;
    حالة ARRAY_TYPE:
      /* An array has variable size if and only if it has a non-constant
	 dimensions or its element type has variable size.  */
      إذا ((C_TYPE_VARIABLE_SIZE (شجرة_TYPE (type))
	   || قمة_array_vla_p (type))
	  != C_TYPE_VARIABLE_SIZE (type))
	أرجع خطأ;
      /* If the element type or the array has variable size, then the
	 array has variable size and is variably modified.  */
      إذا (C_TYPE_VARIABLE_SIZE (شجرة_TYPE (type))
	  || C_TYPE_VARIABLE_SIZE (type))
	{
	  إذا (!C_TYPE_VARIABLE_SIZE (type))
	    أرجع خطأ;
	  إذا (!C_TYPE_VARIABLY_MODIFIED (type))
	    أرجع خطأ;
	}

      /* va_list violates this, accept such types here.  */
      إذا (!COMPLETE_TYPE_P (شجرة_TYPE (type)))
	أرجع true;

      إذا (COMPLETE_TYPE_P (type))
	{
	  /* If the size is unknown, it can not be complete.  */
	  إذا (NULL_شجرة == TYPE_DOMAIN (type))
	    أرجع خطأ;

	  /* Zero-length arrays must have size zero.  */
	  إذا (zero_length_array_type_p (type)
	      && !integer_zerop (TYPE_SIZE (type)))
	    أرجع خطأ;
	}
      وإلا
	{
	  /* If not complete but has a domain, it must be a FAM.  */
	  إذا (NULL_شجرة != TYPE_DOMAIN (type)
	      && !flexible_array_member_type_p (type))
	    أرجع خطأ;
	}
    افتراضي:
      اكسر;
    }
  أرجع true;
}

/* Propagate C_TYPE_VARIABLY_MODIFIED and C_TYPE_VARIABLE_SIZE
   from a base type to a newly built derived or qualified type.  */

ساكن شجرة
c_set_type_bits (شجرة new_type, شجرة old_type)
{
  gcc_checking_assert (c_verify_type (old_type));

  إذا (c_type_variably_modified_p (old_type))
    C_TYPE_VARIABLY_MODIFIED (new_type) = true;

  إذا (شجرة_CODE (new_type) == ARRAY_TYPE && C_TYPE_VARIABLE_SIZE (old_type))
    {
      C_TYPE_VARIABLY_MODIFIED (new_type) = true;
      C_TYPE_VARIABLE_SIZE (new_type) = true;
    }
  أرجع new_type;
}

/* Build a pointer type using the default pointer mode.  */

شجرة
c_build_pointer_type (شجرة to_type)
{
  addr_space_t as = to_type == error_mark_عقدة ? ADDR_SPACE_GENERIC
					       : TYPE_ADDR_SPACE (to_type);
  machine_mode pointer_mode;

  إذا (as != ADDR_SPACE_GENERIC || c_default_pointer_mode == VOIDmode)
    pointer_mode = targetm.addr_space.pointer_mode (as);
  وإلا
    pointer_mode = c_default_pointer_mode;

  أرجع c_build_pointer_type_for_mode (to_type, pointer_mode, خطأ);
}

/* Build a pointer type using the given mode.  */

شجرة
c_build_pointer_type_for_mode (شجرة type, machine_mode mode, منطقي m)
{
  شجرة ret = build_pointer_type_for_mode (type, mode, m);
  أرجع c_set_type_bits (ret, type);
}

/* Build a function type.  */

شجرة
c_build_function_type (شجرة type, شجرة وسائط, منطقي no)
{
  شجرة ret = build_function_type (type, وسائط, no);
  أرجع c_set_type_bits (ret, type);
}

/* Build an array type.  This sets typeless storage as required
   by C2Y and C_TYPE_VARIABLY_MODIFIED and C_TYPE_VARIABLE_SIZE
   based on the element type and domain.  */

شجرة
c_build_array_type (شجرة type, شجرة domain)
{
  صحيح type_quals = TYPE_QUALS (type);

  /* Identify typeless storage as introduced in C2Y
     and supported also in earlier language modes.  */
  منطقي typeless = (char_type_p (type) && !(type_quals & TYPE_QUAL_ATOMIC))
		  || (AGGREGATE_TYPE_P (type) && TYPE_TYPELESS_STORAGE (type));

  شجرة ret = build_array_type (type, domain, typeless);

  إذا (قمة_array_vla_p (ret))
    {
      C_TYPE_VARIABLE_SIZE (ret) = 1;
      C_TYPE_VARIABLY_MODIFIED (ret) = 1;
    }

  أرجع c_set_type_bits (ret, type);
}

/* Build an array type of unspecified size.  */
شجرة
c_build_array_type_unspecified (شجرة type)
{
  شجرة upper = build2 (COMPOUND_تعبير, شجرة_TYPE (size_zero_عقدة),
		       integer_zero_عقدة, size_zero_عقدة);
  أرجع c_build_array_type (type, build_index_type (upper));
}

/* Build an array type of zero size.  */
شجرة
c_build_array_type_zero_size (شجرة type)
{
  /* The GCC extension for zero-length arrays differs from
     ISO flexible array members in that sizeof yields
     zero.  */
  type = c_build_array_type (type, build_index_type (NULL_شجرة));
  type = build_distinct_type_copy (TYPE_MAIN_VARIANT (type));
  TYPE_SIZE (type) = bitsize_zero_عقدة;
  TYPE_SIZE_UNIT (type) = size_zero_عقدة;
  SET_TYPE_STRUCTURAL_EQUALITY (type);
  أرجع type;
}

شجرة
c_build_type_attribute_qual_variant (شجرة type, شجرة attrs, صحيح quals)
{
  شجرة ret = build_type_attribute_qual_variant (type, attrs, quals);
  أرجع c_set_type_bits (ret, type);
}

شجرة
c_build_type_attribute_variant (شجرة type, شجرة attrs)
{
  أرجع c_build_type_attribute_qual_variant (type, attrs, TYPE_QUALS (type));
}

/* Reconstruct a complex derived type.  This is used to re-construct types
   with the vector attribute.  It is called via a langhook.  */

شجرة
c_reconstruct_complex_type (شجرة type, شجرة bottom)
{
  شجرة inner, outer;

  إذا (شجرة_CODE (type) == POINTER_TYPE)
    {
      inner = c_reconstruct_complex_type (شجرة_TYPE (type), bottom);
      outer = c_build_pointer_type_for_mode (inner, TYPE_MODE (type),
					     TYPE_REF_CAN_ALIAS_ALL (type));
    }
  وإلا إذا (شجرة_CODE (type) == ARRAY_TYPE)
    {
      منطقي rso = TYPE_REVERSE_STORAGE_ORDER (type);
      inner = c_reconstruct_complex_type (شجرة_TYPE (type), bottom);
      outer = c_build_array_type (inner, TYPE_DOMAIN (type));
      إذا (rso)
	{
	  outer = build_distinct_type_copy (outer);
	  TYPE_REVERSE_STORAGE_ORDER (outer) = 1;
	}

      gcc_checking_assert (C_TYPE_VARIABLE_SIZE (type)
			   == C_TYPE_VARIABLE_SIZE (outer));
    }
  وإلا إذا (شجرة_CODE (type) == FUNCTION_TYPE)
    {
      inner = c_reconstruct_complex_type (شجرة_TYPE (type), bottom);
      outer = c_build_function_type (inner, TYPE_ARG_TYPES (type),
				     TYPE_NO_NAMED_وسائط_STDARG_P (type));
    }
  وإلا إذا (شجرة_CODE (type) == REFERENCE_TYPE
	   || شجرة_CODE (type) == OFFSET_TYPE)
    gcc_unreachable ();
  وإلا
    أرجع bottom;

  أرجع c_build_type_attribute_qual_variant (outer, TYPE_ATTRIBUTES (type),
					      TYPE_QUALS (type));
}


/* Helper function for c_canonical_type.  Check whether FIELD
   contains a pointer to a structure or union with tag,
   possibly nested in other type derivations, and return the
   type of this nested structure or union.  */
ساكن شجرة
ptr_to_tagged_member (شجرة field)
{
  gcc_assert (FIELD_DECL == شجرة_CODE (field));
  شجرة type = شجرة_TYPE (field);
  منطقي ptr_seen = خطأ;
  طالما (شجرة_CODE (type) == ARRAY_TYPE
	 || شجرة_CODE (type) == FUNCTION_TYPE
	 || شجرة_CODE (type) == POINTER_TYPE)
    {
      إذا (شجرة_CODE (type) == POINTER_TYPE)
	ptr_seen = true;
      type = شجرة_TYPE (type);
    }

  إذا (ptr_seen
      && RECORD_OR_UNION_TYPE_P (type)
      && NULL_شجرة != c_type_tag (type))
    أرجع type;

  أرجع NULL_شجرة;
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
شجرة
c_type_canonical (شجرة type)
{
  gcc_assert (RECORD_OR_UNION_TYPE_P (type));

  منطقي needs_mod = خطأ;
  لكل (شجرة x = TYPE_FIELDS (type); x; x = DECL_CHAIN (x))
    {
      إذا (!ptr_to_tagged_member (x))
	استمر;
      needs_mod = true;
      اكسر;
    }
  إذا (!needs_mod)
    أرجع type;

  /* Construct new version with such members replaced.  */
  شجرة n = build_distinct_type_copy (type);
  شجرة *fields = &TYPE_FIELDS (n);
  لكل (شجرة x = TYPE_FIELDS (type); x; x = DECL_CHAIN (x))
    {
      شجرة f = copy_عقدة (x);
      إذا (شجرة m = ptr_to_tagged_member (x))
	{
	  شجرة new_عقدة = make_عقدة (شجرة_CODE (m));
	  TYPE_NAME (new_عقدة) = TYPE_NAME (m);
	  SET_TYPE_STRUCTURAL_EQUALITY (new_عقدة);
	  new_عقدة = qualify_type (new_عقدة, m);
	  شجرة_TYPE (f) = c_reconstruct_complex_type (شجرة_TYPE (x),
						      new_عقدة);
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

ساكن شجرة
c_build_functype_attribute_variant (شجرة ntype, شجرة otype, شجرة attrs)
{
  إذا (!prototype_p (otype)
      && prototype_p (ntype)
      && lookup_attribute ("format", attrs))
    {
      warning_at (مدخل_location, OPT_Wattributes,
		  "%qs attribute can only be applied to variadic functions",
		  "format");
      attrs = remove_attribute ("format", attrs);
    }
  أرجع c_build_type_attribute_variant (ntype, attrs);

}

/* Given a type which could be a typedef name, make sure to return the
   original type.  See set_underlying_type. */
ساكن const_شجرة
c_type_original (const_شجرة t)
{
  /* It may even be a typedef of a typedef...
     In the case of compiler-created builtin structs the TYPE_DECL
     may be a dummy, with no DECL_ORIGINAL_TYPE.  Don't fault.  */
  طالما (TYPE_NAME (t)
	 && شجرة_CODE (TYPE_NAME (t)) == TYPE_DECL
	 && DECL_ORIGINAL_TYPE (TYPE_NAME (t)))
    t = DECL_ORIGINAL_TYPE (TYPE_NAME (t));
  أرجع t;
}

/* Return the tag for a tagged type.  */
شجرة
c_type_tag (const_شجرة t)
{
  gcc_assert (RECORD_OR_UNION_TYPE_P (t) || شجرة_CODE (t) == ENUMERAL_TYPE);
  const_شجرة orig = c_type_original (t);
  شجرة name = TYPE_NAME (orig);
  إذا (!name)
    أرجع NULL_شجرة;
  إذا (شجرة_CODE (name) == TYPE_DECL)
    {
      إذا (!DECL_NAME (name))
	أرجع NULL_شجرة;
      name = DECL_NAME (name);
    }
  gcc_checking_assert (شجرة_CODE (name) == IDENTIFIER_عقدة);
  أرجع name;
}

/* Remove qualifiers but not atomic.  For arrays remove qualifiers
   on the element type but also do not remove atomic.  */
ساكن شجرة
remove_qualifiers (شجرة t)
{
  إذا (!t || t == error_mark_عقدة)
    أرجع t;
  أرجع TYPE_ATOMIC (strip_array_types (t))
	 ? c_build_qualified_type (TYPE_MAIN_VARIANT (t), TYPE_QUAL_ATOMIC)
	 : TYPE_MAIN_VARIANT (t);
}


/* Helper function for composite_type_internal.  Find a compatible type
   in a (transparent) union U compatible to T.  If found, return the
   type of the corresponding member.  Otherwise, return the union type U.  */
ساكن شجرة
transparent_union_replacement (شجرة u, شجرة t)
{
  إذا (u == error_mark_عقدة || t == error_mark_عقدة
      || شجرة_CODE (u) != UNION_TYPE
      || !(TYPE_TRANSPARENT_AGGR (u) || TYPE_NAME (u) == NULL_شجرة)
      || comptypes (u, t))
    أرجع u;

  لكل (شجرة memb = TYPE_FIELDS (u); memb; memb = DECL_CHAIN (memb))
    {
      شجرة m = remove_qualifiers (شجرة_TYPE (memb));
      إذا (comptypes (m, t))
	{
	  pedwarn (مدخل_location, OPT_Wpedantic,
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

بنية composite_cache {
  شجرة t1;
  شجرة t2;
  شجرة composite;
  بنية composite_cache* next;
};

شجرة
composite_type_internal (شجرة t1, شجرة t2, شجرة cond,
			 بنية composite_cache* cache)
{
  تعداد شجرة_code code1;
  تعداد شجرة_code code2;
  شجرة attributes;

  /* Save time if the two types are the same.  */

  إذا (t1 == t2) أرجع t1;

  /* If one type is nonsense, use the other.  */
  إذا (t1 == error_mark_عقدة)
    أرجع t2;
  إذا (t2 == error_mark_عقدة)
    أرجع t1;

  code1 = شجرة_CODE (t1);
  code2 = شجرة_CODE (t2);

  /* Merge the attributes.  */
  attributes = targetm.merge_type_attributes (t1, t2);

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
    حالة POINTER_TYPE:
      /* For two pointers, do this recursively on the target type.  */
      {
	gcc_checking_assert (TYPE_QUALS (t1) == TYPE_QUALS (t2));
	شجرة target = composite_type_internal (شجرة_TYPE (t1), شجرة_TYPE (t2),
					       cond, cache);
	شجرة n = c_build_pointer_type_for_mode (target, TYPE_MODE (t1), خطأ);
	أرجع c_build_type_attribute_qual_variant (n, attributes,
						    TYPE_QUALS (t2));
      }

    حالة ARRAY_TYPE:
      {
	شجرة d1 = TYPE_DOMAIN (t1);
	شجرة d2 = TYPE_DOMAIN (t2);

	/* We should not have any type quals on arrays at all.  */
	gcc_assert (!TYPE_QUALS_NO_ADDR_SPACE (t1)
		    && !TYPE_QUALS_NO_ADDR_SPACE (t2));

	منطقي d1_zero = zero_length_array_type_p (t1)
		       || flexible_array_member_type_p (t1);
	منطقي d2_zero = zero_length_array_type_p (t2)
		       || flexible_array_member_type_p (t2);

	منطقي d1_variable = قمة_array_vla_p (t1);
	منطقي d2_variable = قمة_array_vla_p (t2);

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

	شجرة td;
	شجرة elt = composite_type_internal (شجرة_TYPE (t1), شجرة_TYPE (t2),
					    cond, cache);

	إذا (!use0)
	  {
	    /* Save space: see if the result is identical to one of the args.  */
	    إذا (elt == شجرة_TYPE (t1) && use1)
	      أرجع c_build_type_attribute_variant (t1, attributes);
	    إذا (elt == شجرة_TYPE (t2) && use2)
	      أرجع c_build_type_attribute_variant (t2, attributes);

	    إذا (elt == شجرة_TYPE (t1) && !TYPE_DOMAIN (t2) && !TYPE_DOMAIN (t1))
	      أرجع c_build_type_attribute_variant (t1, attributes);
	    إذا (elt == شجرة_TYPE (t2) && !TYPE_DOMAIN (t2) && !TYPE_DOMAIN (t1))
	      أرجع c_build_type_attribute_variant (t2, attributes);

	    td = TYPE_DOMAIN (use1 ? t1 : t2);
	  }
	وإلا
	  {
	    /* Not used in C.  */
	    gcc_assert (size_zero_عقدة == TYPE_MIN_قيمة (d1));
	    gcc_assert (size_zero_عقدة == TYPE_MIN_قيمة (d2));

	    شجرة d = fold_build3_loc (UNKNOWN_LOCATION, COND_تعبير, sizetype,
				      cond, TYPE_MAX_قيمة (d1),
				      TYPE_MAX_قيمة (d2));

	    td = build_index_type (d);
	  }

	/* Merge the element types, and have a size if either arg has
	   one.  We may have qualifiers on the element types.  To set
	   up TYPE_MAIN_VARIANT correctly, we need to form the
	   composite of the unqualified types and add the qualifiers
	   back at the end.  */
	صحيح quals = TYPE_QUALS (strip_array_types (elt));
	شجرة unqual_elt = c_build_qualified_type (elt, TYPE_UNQUALIFIED);

	إذا ((!d1 || d1_zero) && (!d2 || d2_zero) && (d1 || d2))
	  t1 = c_build_array_type_zero_size (unqual_elt);
	وإلا
	  t1 = c_build_array_type (unqual_elt, td);

	/* Check that a type which has a varying outermost dimension
	   got marked as having a variable size.  */
	منطقي varsize = (d1_variable && d2_variable)
		       || (d1_variable && !d2)
		       || (d2_variable && !d1);
	gcc_checking_assert (!varsize || C_TYPE_VARIABLE_SIZE (t1));

	t1 = c_build_qualified_type (t1, quals);
	أرجع c_build_type_attribute_variant (t1, attributes);
      }

    حالة RECORD_TYPE:
    حالة UNION_TYPE:
      إذا (flag_isoc23 && !comptypes_same_p (t1, t2))
	{
	  /* Go to the original type to get the right tag.  */
	  شجرة tag = c_type_tag (t1);

	  gcc_checking_assert (COMPLETE_TYPE_P (t1) && COMPLETE_TYPE_P (t2));
	  gcc_checking_assert (!tag || comptypes (t1, t2));

	  /* If a composite type for these two types is already under
	     construction, return it.  */

	  لكل (بنية composite_cache *c = cache; c != عدم; c = c->next)
	    إذا ((c->t1 == t1 && c->t2 == t2) || (c->t1 == t2 && c->t2 == t1))
	       أرجع c->composite;

	  /* Otherwise, create a new type node and link it into the cache.  */

	  شجرة n = make_عقدة (code1);
	  SET_TYPE_STRUCTURAL_EQUALITY (n);
	  TYPE_NAME (n) = tag;

	  بنية composite_cache cache2 = { t1, t2, n, cache };
	  cache = &cache2;

	  شجرة f1 = TYPE_FIELDS (t1);
	  شجرة f2 = TYPE_FIELDS (t2);
	  شجرة fields = NULL_شجرة;

	  لكل (شجرة a = f1, b = f2; a && b;
	       a = DECL_CHAIN (a), b = DECL_CHAIN (b))
	    {
	      شجرة ta = شجرة_TYPE (a);
	      شجرة tb = شجرة_TYPE (b);

	      إذا (DECL_C_BIT_FIELD (a))
		{
		  ta = DECL_BIT_FIELD_TYPE (a);
		  tb = DECL_BIT_FIELD_TYPE (b);
		}

	      gcc_assert (DECL_NAME (a) == DECL_NAME (b));
	      gcc_checking_assert (!DECL_NAME (a) || comptypes (ta, tb));

	      شجرة t = composite_type_internal (ta, tb, cond, cache);
	      شجرة f = build_decl (مدخل_location, FIELD_DECL, DECL_NAME (a), t);

	      DECL_PACKED (f) = DECL_PACKED (a);
	      SET_DECL_ALIGN (f, DECL_ALIGN (a));
	      DECL_ATTRIBUTES (f) = DECL_ATTRIBUTES (a);
	      C_DECL_VARIABLE_SIZE (f) = C_TYPE_VARIABLE_SIZE (t);

	      decl_attributes (&f, DECL_ATTRIBUTES (f), 0);

	      finish_decl (f, مدخل_location, عدم, عدم, عدم);

	      إذا (DECL_C_BIT_FIELD (a))
		{
		  /* This will be processed by finish_struct.  */
		  SET_DECL_C_BIT_FIELD (f);
		  DECL_INITIAL (f) = build_int_cst (integer_type_عقدة,
						    شجرة_to_uhwi (DECL_SIZE (a)));
		  DECL_NONADDRESSABLE_P (f) = true;
		  DECL_PADDING_P (f) = !DECL_NAME (a);
		}

	      DECL_CHAIN (f) = fields;
	      fields = f;
	    }

	  fields = nreverse (fields);

	  /* Setup the struct/union type.  Because we inherit all variably
	     modified components, we can ignore the size expression.  */
	  شجرة تعبير = NULL_شجرة;

	  /* Set TYPE_STUB_DECL for debugging symbols.  */
	  TYPE_STUB_DECL (n) = pushdecl (build_decl (مدخل_location, TYPE_DECL,
						     NULL_شجرة, n));

	  n = finish_struct (مدخل_location, n, fields, attributes, عدم,
			     &تعبير);

	  أرجع qualify_type (n, t1);
	}
      /* FALLTHRU */
    حالة ENUMERAL_TYPE:
      إذا (attributes != عدم)
	{
	  /* Try harder not to create a new aggregate type.  */
	  إذا (attribute_list_equal (TYPE_ATTRIBUTES (t1), attributes))
	    أرجع t1;
	  إذا (attribute_list_equal (TYPE_ATTRIBUTES (t2), attributes))
	    أرجع t2;
	}
      أرجع c_build_type_attribute_variant (t1, attributes);

    حالة FUNCTION_TYPE:
      /* Function types: prefer the one that specified arg types.
	 If both do, merge the arg types.  Also merge the return types.  */
      {
	شجرة valtype = composite_type_internal (شجرة_TYPE (t1), شجرة_TYPE (t2),
						cond, cache);
	شجرة p1 = TYPE_ARG_TYPES (t1);
	شجرة p2 = TYPE_ARG_TYPES (t2);

	/* Save space: see if the result is identical to one of the args.  */
	إذا (valtype == شجرة_TYPE (t1) && !TYPE_ARG_TYPES (t2))
	  أرجع c_build_functype_attribute_variant (t1, t2, attributes);
	إذا (valtype == شجرة_TYPE (t2) && !TYPE_ARG_TYPES (t1))
	  أرجع c_build_functype_attribute_variant (t2, t1, attributes);

	/* Simple way if one arg fails to specify argument types.  */
	إذا (TYPE_ARG_TYPES (t1) == NULL_شجرة)
	  {
	    t1 = c_build_function_type (valtype, TYPE_ARG_TYPES (t2),
					TYPE_NO_NAMED_وسائط_STDARG_P (t2));
	    t1 = c_build_type_attribute_variant (t1, attributes);
	    أرجع qualify_type (t1, t2);
	 }
	إذا (TYPE_ARG_TYPES (t2) == NULL_شجرة)
	  {
	    t1 = c_build_function_type (valtype, TYPE_ARG_TYPES (t1),
					TYPE_NO_NAMED_وسائط_STDARG_P (t1));
	    t1 = c_build_type_attribute_variant (t1, attributes);
	    أرجع qualify_type (t1, t2);
	  }

	/* If both args specify argument types, we must merge the two
	   lists, argument by argument.  */
	شجرة newargs = NULL_شجرة;
	شجرة *endp = &newargs;

	لكل (; p1; p1 = شجرة_CHAIN (p1), p2 = شجرة_CHAIN (p2))
	  {
	    إذا (p1 == void_list_عقدة)
	      {
		*endp = void_list_عقدة;
		اكسر;
	      }
	    شجرة mv1 = remove_qualifiers (شجرة_قيمة (p1));
	    شجرة mv2 = remove_qualifiers (شجرة_قيمة (p2));

	    gcc_assert (mv1);
	    gcc_assert (mv2);

	    mv1 = transparent_union_replacement (mv1, mv2);
	    mv2 = transparent_union_replacement (mv2, mv1);

	    *endp = شجرة_cons (NULL_شجرة,
			       composite_type_internal (mv1, mv2, cond, cache),
			       NULL_شجرة);

	    endp = &شجرة_CHAIN (*endp);
	  }

	t1 = c_build_function_type (valtype, newargs);
	t1 = qualify_type (t1, t2);
      }
      /* FALLTHRU */

    افتراضي:
      أرجع c_build_type_attribute_variant (t1, attributes);
    }
}

شجرة
composite_type_cond (شجرة t1, شجرة t2, شجرة cond)
{
  gcc_checking_assert (comptypes_check_for_composite (t1, t2));

  بنية composite_cache cache = { };
  شجرة n = composite_type_internal (t1, t2, cond, &cache);

  gcc_checking_assert (comptypes_check_for_composite (n, t1));
  gcc_checking_assert (comptypes_check_for_composite (n, t2));
  أرجع n;
}


شجرة
composite_type (شجرة t1, شجرة t2)
{
  أرجع composite_type_cond (t1, t2, NULL_شجرة);
}

/* Return the type of a conditional expression between pointers to
   possibly differently qualified versions of compatible types.

   We assume that comp_target_types has already been done and returned
   true; if that isn't so, this may crash.  */

ساكن شجرة
common_pointer_type (شجرة t1, شجرة t2, شجرة cond)
{
  شجرة attributes;
  unsigned target_quals;
  addr_space_t as1, as2, as_common;
  صحيح quals1, quals2;

  /* Save time if the two types are the same.  */

  إذا (t1 == t2) أرجع t1;

  /* If one type is nonsense, use the other.  */
  إذا (t1 == error_mark_عقدة)
    أرجع t2;
  إذا (t2 == error_mark_عقدة)
    أرجع t1;

  gcc_assert (شجرة_CODE (t1) == POINTER_TYPE
	      && شجرة_CODE (t2) == POINTER_TYPE);

  /* Merge the attributes.  */
  attributes = targetm.merge_type_attributes (t1, t2);

  /* Find the composite type of the target types, and combine the
     qualifiers of the two types' targets.  */
  شجرة pointed_to_1 = شجرة_TYPE (t1);
  شجرة pointed_to_2 = شجرة_TYPE (t2);
  شجرة target = composite_type_cond (TYPE_MAIN_VARIANT (pointed_to_1),
				     TYPE_MAIN_VARIANT (pointed_to_2), cond);

  /* Strip array types to get correct qualifier for pointers to arrays */
  quals1 = TYPE_QUALS_NO_ADDR_SPACE (strip_array_types (pointed_to_1));
  quals2 = TYPE_QUALS_NO_ADDR_SPACE (strip_array_types (pointed_to_2));

  /* For function types do not merge const qualifiers, but drop them
     if used inconsistently.  The middle-end uses these to mark const
     and noreturn functions.  */
  إذا (شجرة_CODE (pointed_to_1) == FUNCTION_TYPE)
    target_quals = (quals1 & quals2);
  وإلا
    target_quals = (quals1 | quals2);

  /* If the two named address spaces are different, determine the common
     superset address space.  This is guaranteed to exist due to the
     assumption that comp_target_type returned true.  */
  as1 = TYPE_ADDR_SPACE (pointed_to_1);
  as2 = TYPE_ADDR_SPACE (pointed_to_2);
  إذا (!addr_space_superset (as1, as2, &as_common))
    gcc_unreachable ();

  target_quals |= ENCODE_QUAL_ADDR_SPACE (as_common);

  t1 = c_build_pointer_type (c_build_qualified_type (target, target_quals));
  أرجع c_build_type_attribute_variant (t1, attributes);
}

/* Return the common type for two arithmetic types under the usual
   arithmetic conversions.  The default conversions have already been
   applied, and enumerated types converted to their compatible integer
   types.  The resulting type is unqualified and has no attributes.

   This is the type for the result of most arithmetic operations
   if the operands have the given two types.  */

ساكن شجرة
c_common_type (شجرة t1, شجرة t2)
{
  تعداد شجرة_code code1;
  تعداد شجرة_code code2;

  /* If one type is nonsense, use the other.  */
  إذا (t1 == error_mark_عقدة)
    أرجع t2;
  إذا (t2 == error_mark_عقدة)
    أرجع t1;

  إذا (TYPE_QUALS (t1) != TYPE_UNQUALIFIED)
    t1 = TYPE_MAIN_VARIANT (t1);

  إذا (TYPE_QUALS (t2) != TYPE_UNQUALIFIED)
    t2 = TYPE_MAIN_VARIANT (t2);

  إذا (TYPE_ATTRIBUTES (t1) != NULL_شجرة)
    {
      شجرة attrs = affects_type_identity_attributes (TYPE_ATTRIBUTES (t1));
      t1 = c_build_type_attribute_variant (t1, attrs);
    }

  إذا (TYPE_ATTRIBUTES (t2) != NULL_شجرة)
    {
      شجرة attrs = affects_type_identity_attributes (TYPE_ATTRIBUTES (t2));
      t2 = c_build_type_attribute_variant (t2, attrs);
    }

  /* Save time if the two types are the same.  */

  إذا (t1 == t2) أرجع t1;

  code1 = شجرة_CODE (t1);
  code2 = شجرة_CODE (t2);

  gcc_assert (code1 == VECTOR_TYPE || code1 == COMPLEX_TYPE
	      || code1 == FIXED_POINT_TYPE || code1 == REAL_TYPE
	      || code1 == INTEGER_TYPE || code1 == BITINT_TYPE);
  gcc_assert (code2 == VECTOR_TYPE || code2 == COMPLEX_TYPE
	      || code2 == FIXED_POINT_TYPE || code2 == REAL_TYPE
	      || code2 == INTEGER_TYPE || code2 == BITINT_TYPE);

  /* When one operand is a decimal float type, the other operand cannot be
     a generic float type or a complex type.  We also disallow vector types
     here.  */
  إذا ((DECIMAL_FLOAT_TYPE_P (t1) || DECIMAL_FLOAT_TYPE_P (t2))
      && !(DECIMAL_FLOAT_TYPE_P (t1) && DECIMAL_FLOAT_TYPE_P (t2)))
    {
      إذا (code1 == VECTOR_TYPE || code2 == VECTOR_TYPE)
	{
	  error ("cannot mix operands of decimal floating and vector types");
	  أرجع error_mark_عقدة;
	}
      إذا (code1 == COMPLEX_TYPE || code2 == COMPLEX_TYPE)
	{
	  error ("cannot mix operands of decimal floating and complex types");
	  أرجع error_mark_عقدة;
	}
      إذا (code1 == REAL_TYPE && code2 == REAL_TYPE)
	{
	  error ("cannot mix operands of decimal floating "
		 "and other floating types");
	  أرجع error_mark_عقدة;
	}
    }

  /* If one type is a vector type, return that type.  (How the usual
     arithmetic conversions apply to the vector types extension is not
     precisely specified.)  */
  إذا (code1 == VECTOR_TYPE)
    أرجع t1;

  إذا (code2 == VECTOR_TYPE)
    أرجع t2;

  /* If one type is complex, form the common type of the non-complex
     components, then make that complex.  Use T1 or T2 if it is the
     required type.  */
  إذا (code1 == COMPLEX_TYPE || code2 == COMPLEX_TYPE)
    {
      شجرة subtype1 = code1 == COMPLEX_TYPE ? شجرة_TYPE (t1) : t1;
      شجرة subtype2 = code2 == COMPLEX_TYPE ? شجرة_TYPE (t2) : t2;
      شجرة subtype = c_common_type (subtype1, subtype2);

      إذا (code1 == COMPLEX_TYPE && شجرة_TYPE (t1) == subtype)
	أرجع t1;
      وإلا إذا (code2 == COMPLEX_TYPE && شجرة_TYPE (t2) == subtype)
	أرجع t2;
      وإلا إذا (شجرة_CODE (subtype) == BITINT_TYPE)
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
      إذا (TYPE_MAIN_VARIANT (t1) == dfloat128_type_عقدة
	  || TYPE_MAIN_VARIANT (t2) == dfloat128_type_عقدة)
	أرجع dfloat128_type_عقدة;
      /* And prefer _Decimal128 over _Decimal64x which has in GCC's
	 implementation the same mode.  */
      وإلا إذا (TYPE_MAIN_VARIANT (t1) == dfloat64x_type_عقدة
	       || TYPE_MAIN_VARIANT (t2) == dfloat64x_type_عقدة)
	أرجع dfloat64x_type_عقدة;
      وإلا إذا (TYPE_MAIN_VARIANT (t1) == dfloat64_type_عقدة
	       || TYPE_MAIN_VARIANT (t2) == dfloat64_type_عقدة)
	أرجع dfloat64_type_عقدة;
      وإلا إذا (TYPE_MAIN_VARIANT (t1) == dfloat32_type_عقدة
	       || TYPE_MAIN_VARIANT (t2) == dfloat32_type_عقدة)
	أرجع dfloat32_type_عقدة;
    }

  /* Deal with fixed-point types.  */
  إذا (code1 == FIXED_POINT_TYPE || code2 == FIXED_POINT_TYPE)
    {
      unsigned صحيح unsignedp = 0, satp = 0;
      scalar_mode m1, m2;
      unsigned صحيح fbit1, ibit1, fbit2, ibit2, max_fbit, max_ibit;

      m1 = SCALAR_TYPE_MODE (t1);
      m2 = SCALAR_TYPE_MODE (t2);

      /* If one input type is saturating, the result type is saturating.  */
      إذا (TYPE_SATURATING (t1) || TYPE_SATURATING (t2))
	satp = 1;

      /* If both fixed-point types are unsigned, the result type is unsigned.
	 When mixing fixed-point and integer types, follow the sign of the
	 fixed-point type.
	 Otherwise, the result type is signed.  */
      إذا ((TYPE_UNSIGNED (t1) && TYPE_UNSIGNED (t2)
	   && code1 == FIXED_POINT_TYPE && code2 == FIXED_POINT_TYPE)
	  || (code1 == FIXED_POINT_TYPE && code2 != FIXED_POINT_TYPE
	      && TYPE_UNSIGNED (t1))
	  || (code1 != FIXED_POINT_TYPE && code2 == FIXED_POINT_TYPE
	      && TYPE_UNSIGNED (t2)))
	unsignedp = 1;

      /* The result type is signed.  */
      إذا (unsignedp == 0)
	{
	  /* If the input type is unsigned, we need to convert to the
	     signed type.  */
	  إذا (code1 == FIXED_POINT_TYPE && TYPE_UNSIGNED (t1))
	    {
	      تعداد mode_class mclass = (تعداد mode_class) 0;
	      إذا (GET_MODE_CLASS (m1) == MODE_UFRACT)
		mclass = MODE_FRACT;
	      وإلا إذا (GET_MODE_CLASS (m1) == MODE_UACCUM)
		mclass = MODE_ACCUM;
	      وإلا
		gcc_unreachable ();
	      m1 = as_a <scalar_mode>
		(mode_for_size (GET_MODE_PRECISION (m1), mclass, 0));
	    }
	  إذا (code2 == FIXED_POINT_TYPE && TYPE_UNSIGNED (t2))
	    {
	      تعداد mode_class mclass = (تعداد mode_class) 0;
	      إذا (GET_MODE_CLASS (m2) == MODE_UFRACT)
		mclass = MODE_FRACT;
	      وإلا إذا (GET_MODE_CLASS (m2) == MODE_UACCUM)
		mclass = MODE_ACCUM;
	      وإلا
		gcc_unreachable ();
	      m2 = as_a <scalar_mode>
		(mode_for_size (GET_MODE_PRECISION (m2), mclass, 0));
	    }
	}

      إذا (code1 == FIXED_POINT_TYPE)
	{
	  fbit1 = GET_MODE_FBIT (m1);
	  ibit1 = GET_MODE_IBIT (m1);
	}
      وإلا
	{
	  fbit1 = 0;
	  /* Signed integers need to subtract one sign bit.  */
	  ibit1 = TYPE_PRECISION (t1) - (!TYPE_UNSIGNED (t1));
	}

      إذا (code2 == FIXED_POINT_TYPE)
	{
	  fbit2 = GET_MODE_FBIT (m2);
	  ibit2 = GET_MODE_IBIT (m2);
	}
      وإلا
	{
	  fbit2 = 0;
	  /* Signed integers need to subtract one sign bit.  */
	  ibit2 = TYPE_PRECISION (t2) - (!TYPE_UNSIGNED (t2));
	}

      max_ibit = ibit1 >= ibit2 ?  ibit1 : ibit2;
      max_fbit = fbit1 >= fbit2 ?  fbit1 : fbit2;
      أرجع c_common_fixed_point_type_for_size (max_ibit, max_fbit, unsignedp,
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

  إذا (TYPE_MAIN_VARIANT (t1) == long_long_unsigned_type_عقدة
      || TYPE_MAIN_VARIANT (t2) == long_long_unsigned_type_عقدة)
    أرجع long_long_unsigned_type_عقدة;

  إذا (TYPE_MAIN_VARIANT (t1) == long_long_integer_type_عقدة
      || TYPE_MAIN_VARIANT (t2) == long_long_integer_type_عقدة)
    {
      إذا (TYPE_UNSIGNED (t1) || TYPE_UNSIGNED (t2))
	أرجع long_long_unsigned_type_عقدة;
      وإلا
	أرجع long_long_integer_type_عقدة;
    }

  إذا (TYPE_MAIN_VARIANT (t1) == long_unsigned_type_عقدة
      || TYPE_MAIN_VARIANT (t2) == long_unsigned_type_عقدة)
    أرجع long_unsigned_type_عقدة;

  إذا (TYPE_MAIN_VARIANT (t1) == long_integer_type_عقدة
      || TYPE_MAIN_VARIANT (t2) == long_integer_type_عقدة)
    {
      /* But preserve unsignedness from the other type,
	 since long cannot hold all the values of an unsigned int.  */
      إذا (TYPE_UNSIGNED (t1) || TYPE_UNSIGNED (t2))
	أرجع long_unsigned_type_عقدة;
      وإلا
	أرجع long_integer_type_عقدة;
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
  شجرة mv1 = TYPE_MAIN_VARIANT (t1);
  شجرة mv2 = TYPE_MAIN_VARIANT (t2);

  لكل (صحيح i = رقم_FLOATN_TYPES - 1; i >= 0; i--)
    إذا (mv1 == FLOATN_TYPE_عقدة (i) || mv2 == FLOATN_TYPE_عقدة (i))
      أرجع FLOATN_TYPE_عقدة (i);

  /* Likewise, prefer long double to double even if same size.  */
  إذا (mv1 == long_double_type_عقدة || mv2 == long_double_type_عقدة)
    أرجع long_double_type_عقدة;

  /* Likewise, prefer double to float even if same size.
     We got a couple of embedded targets with 32 bit doubles, and the
     pdp11 might have 64 bit floats.  */
  إذا (mv1 == double_type_عقدة || mv2 == double_type_عقدة)
    أرجع double_type_عقدة;

  إذا (mv1 == float_type_عقدة || mv2 == float_type_عقدة)
    أرجع float_type_عقدة;

  لكل (صحيح i = رقم_FLOATNX_TYPES - 1; i >= 0; i--)
    إذا (mv1 == FLOATNX_TYPE_عقدة (i) || mv2 == FLOATNX_TYPE_عقدة (i))
      أرجع FLOATNX_TYPE_عقدة (i);

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
شجرة
common_type (شجرة t1, شجرة t2)
{
  إذا (شجرة_CODE (t1) == ENUMERAL_TYPE)
    t1 = ENUM_UNDERLYING_TYPE (t1);
  إذا (شجرة_CODE (t2) == ENUMERAL_TYPE)
    t2 = ENUM_UNDERLYING_TYPE (t2);

  /* If both types are BOOLEAN_TYPE, then return boolean_type_node.  */
  إذا (شجرة_CODE (t1) == BOOLEAN_TYPE
      && شجرة_CODE (t2) == BOOLEAN_TYPE)
    أرجع boolean_type_عقدة;

  /* If either type is BOOLEAN_TYPE, then return the other.  */
  إذا (شجرة_CODE (t1) == BOOLEAN_TYPE)
    أرجع t2;
  إذا (شجرة_CODE (t2) == BOOLEAN_TYPE)
    أرجع t1;

  أرجع c_common_type (t1, t2);
}



/* Helper function for comptypes.  For two compatible types, return 1
   if they pass consistency checks.  In particular we test that
   TYPE_CANONICAL is set correctly, i.e. the two types can alias.  */

ساكن منطقي
comptypes_verify (شجرة type1, شجرة type2)
{
  إذا (type1 == type2 || !type1 || !type2
      || شجرة_CODE (type1) == ERROR_MARK || شجرة_CODE (type2) == ERROR_MARK)
    أرجع true;

  gcc_checking_assert (c_verify_type (type1));
  gcc_checking_assert (c_verify_type (type2));

  إذا (TYPE_CANONICAL (type1) != TYPE_CANONICAL (type2)
      && !TYPE_STRUCTURAL_EQUALITY_P (type1)
      && !TYPE_STRUCTURAL_EQUALITY_P (type2))
    {
      /* FIXME: check other types. */
      إذا (RECORD_OR_UNION_TYPE_P (type1)
	  || شجرة_CODE (type1) == ENUMERAL_TYPE
	  || شجرة_CODE (type2) == ENUMERAL_TYPE)
	أرجع خطأ;
    }
  أرجع true;
}

بنية comptypes_data {

  /* output */
  منطقي enum_and_int_p;
  منطقي different_types_p;
  منطقي warning_needed;

  /* context */
  منطقي anon_field;
  منطقي pointedto;

  /* configuration */
  منطقي equiv;
  منطقي ignore_promoting_وسائط;

  ثابت بنية tagged_tu_seen_cache* cache;
};


/* Helper function for composite_type.  This function ignores when the
   function type of an old-style declaration is incompatible with a type
   of a declaration with prototype because some are arguments are not
   self-promoting.  This is ignored only for function types but not
   ignored in a nested context.  */

ساكن منطقي
comptypes_check_for_composite (شجرة t1, شجرة t2)
{
  بنية comptypes_data data = { };
  data.ignore_promoting_وسائط = FUNCTION_TYPE == شجرة_CODE (t1);
  أرجع comptypes_internal (t1, t2, &data);
}


/* C implementation of compatible_types_for_indirection_note_p.  */

منطقي
compatible_types_for_indirection_note_p (شجرة type1, شجرة type2)
{
  أرجع comptypes (type1, type2);
}

/* Return true if TYPE1 and TYPE2 are compatible types for assignment
   or various other operations.  */

منطقي
comptypes (شجرة type1, شجرة type2)
{
  بنية comptypes_data data = { };
  منطقي ret = comptypes_internal (type1, type2, &data);

  gcc_checking_assert (!ret || comptypes_verify (type1, type2));

  أرجع ret;
}


/* Like comptypes, but it returns non-zero only for identical
   types.  */

منطقي
comptypes_same_p (شجرة type1, شجرة type2)
{
  بنية comptypes_data data = { };
  منطقي ret = comptypes_internal (type1, type2, &data);

  gcc_checking_assert (!ret || comptypes_verify (type1, type2));

  إذا (data.different_types_p)
    أرجع خطأ;

  أرجع ret;
}


/* Like comptypes, but if it returns true because enum and int are
   compatible, it sets *ENUM_AND_INT_P to true.  */

منطقي
comptypes_check_enum_int (شجرة type1, شجرة type2, منطقي *enum_and_int_p)
{
  بنية comptypes_data data = { };
  منطقي ret = comptypes_internal (type1, type2, &data);
  *enum_and_int_p = data.enum_and_int_p;

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
comptypes_equiv_p (شجرة type1, شجرة type2)
{
  بنية comptypes_data data = { };
  data.equiv = true;
  منطقي ret = comptypes_internal (type1, type2, &data);

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
comptypes_internal (const_شجرة type1, const_شجرة type2,
		    بنية comptypes_data *data)
{
  const_شجرة t1 = type1;
  const_شجرة t2 = type2;

  /* Suppress errors caused by previously reported errors.  */

  إذا (t1 == t2 || !t1 || !t2
      || شجرة_CODE (t1) == ERROR_MARK || شجرة_CODE (t2) == ERROR_MARK)
    أرجع true;

  /* Qualifiers must match. C99 6.7.3p9 */

  إذا (TYPE_QUALS (t1) != TYPE_QUALS (t2))
    أرجع خطأ;

  /* Enumerated types are compatible with integer types, but this is
     not transitive: two enumerated types in the same translation unit
     are compatible with each other only if they are the same type.  */

  إذا (شجرة_CODE (t1) == ENUMERAL_TYPE
      && COMPLETE_TYPE_P (t1)
      && شجرة_CODE (t2) != ENUMERAL_TYPE)
    {
      t1 = ENUM_UNDERLYING_TYPE (t1);
      إذا (شجرة_CODE (t2) != VOID_TYPE)
	{
	  data->enum_and_int_p = true;
	  data->different_types_p = true;
	}
    }
  وإلا إذا (شجرة_CODE (t2) == ENUMERAL_TYPE
	   && COMPLETE_TYPE_P (t2)
	   && شجرة_CODE (t1) != ENUMERAL_TYPE)
    {
      t2 = ENUM_UNDERLYING_TYPE (t2);
      إذا (شجرة_CODE (t1) != VOID_TYPE)
	{
	  data->enum_and_int_p = true;
	  data->different_types_p = true;
	}
    }

  إذا (t1 == t2)
    أرجع true;

  /* Different classes of types can't be compatible.  */

  إذا (شجرة_CODE (t1) != شجرة_CODE (t2))
    أرجع خطأ;

  /* Allow for two different type nodes which have essentially the same
     definition.  Note that we already checked for equality of the type
     qualifiers (just above).  */

  إذا (شجرة_CODE (t1) != ARRAY_TYPE
      && TYPE_MAIN_VARIANT (t1) == TYPE_MAIN_VARIANT (t2))
    أرجع true;

  صحيح attrval;

  /* 1 if no need for warning yet, 2 if warning cause has been seen.  */
  إذا (!(attrval = comp_type_attributes (t1, t2)))
    أرجع خطأ;

  إذا (2 == attrval)
    data->warning_needed = true;

  بدل (شجرة_CODE (t1))
    {
    حالة INTEGER_TYPE:
    حالة FIXED_POINT_TYPE:
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

    حالة POINTER_TYPE:
      /* Do not remove mode information.  */
      إذا (TYPE_MODE (t1) != TYPE_MODE (t2))
	أرجع خطأ;
      data->pointedto = true;
      أرجع comptypes_internal (شجرة_TYPE (t1), شجرة_TYPE (t2), data);

    حالة FUNCTION_TYPE:
      أرجع function_types_compatible_p (t1, t2, data);

    حالة ARRAY_TYPE:
      {
	شجرة d1 = TYPE_DOMAIN (t1);
	شجرة d2 = TYPE_DOMAIN (t2);

	/* Target types must match incl. qualifiers.  */
	إذا (!comptypes_internal (شجرة_TYPE (t1), شجرة_TYPE (t2), data))
	  أرجع خطأ;

	إذا ((d1 == NULL_شجرة) != (d2 == NULL_شجرة))
	  data->different_types_p = true;
	/* Ignore size mismatches when forming equivalence classes.  */
	إذا (data->equiv)
	  أرجع true;
	/* Sizes must match unless one is missing or variable.  */
	إذا (d1 == NULL_شجرة || d2 == NULL_شجرة || d1 == d2)
	  أرجع true;

	منطقي d1_variable = قمة_array_vla_p (t1);
	منطقي d2_variable = قمة_array_vla_p (t2);

	إذا (d1_variable != d2_variable)
	  data->different_types_p = true;
	إذا (d1_variable || d2_variable)
	  أرجع true;

	منطقي d1_zero = zero_length_array_type_p (t1)
		       || flexible_array_member_type_p (t1);

	منطقي d2_zero = zero_length_array_type_p (t2)
		       || flexible_array_member_type_p (t2);

	إذا (d1_zero && d2_zero)
	  أرجع true;
	إذا (d1_zero || d2_zero)
	  أرجع خطأ;

	إذا (!شجرة_int_cst_equal (TYPE_MIN_قيمة (d1), TYPE_MIN_قيمة (d2))
	    || !شجرة_int_cst_equal (TYPE_MAX_قيمة (d1), TYPE_MAX_قيمة (d2)))
	  أرجع خطأ;

	أرجع true;
      }

    حالة ENUMERAL_TYPE:
    حالة RECORD_TYPE:
    حالة UNION_TYPE:

      إذا (!flag_isoc23)
	أرجع خطأ;

      أرجع tagged_types_tu_compatible_p (t1, t2, data);

    حالة VECTOR_TYPE:
      أرجع known_eq (TYPE_VECTOR_SUBPARTS (t1), TYPE_VECTOR_SUBPARTS (t2))
	     && comptypes_internal (شجرة_TYPE (t1), شجرة_TYPE (t2), data);

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
comp_target_types (location_t location, شجرة ttl, شجرة ttr)
{
  شجرة mvl = شجرة_TYPE (ttl);
  شجرة mvr = شجرة_TYPE (ttr);
  addr_space_t asl = TYPE_ADDR_SPACE (mvl);
  addr_space_t asr = TYPE_ADDR_SPACE (mvr);
  addr_space_t as_common;

  /* Fail if pointers point to incompatible address spaces.  */
  إذا (!addr_space_superset (asl, asr, &as_common))
    أرجع 0;

  /* Qualifiers on element types of array types that are
     pointer targets are also removed.  */
  بنية comptypes_data data = { };
  إذا (!comptypes_internal (remove_qualifiers (mvl),
			   remove_qualifiers (mvr), &data))
    أرجع خطأ;

  /* For pedantic use comptypes on arrays before removing
     qualifiers on the element type. */
  إذا (شجرة_CODE (mvl) == ARRAY_TYPE
      && شجرة_CODE (mvr) == ARRAY_TYPE
      && !comptypes (mvl, mvr))
    pedwarn_c11 (location, OPT_Wpedantic, "invalid use of pointers to arrays "
					  "with different qualifiers in ISO C "
					  "before C23");

  إذا (data.warning_needed)
    pedwarn (location, OPT_Wpedantic, "types are not quite compatible");

  إذا (data.enum_and_int_p && warn_cxx_compat)
    warning_at (location, OPT_Wc___compat,
		"pointer target types incompatible in C++");

  أرجع true;
}

/* Subroutines of `comptypes'.  */

/* Return true if two 'struct', 'union', or 'enum' types T1 and T2 are
   compatible.  The two types are not the same (which has been
   checked earlier in comptypes_internal).  */

ساكن منطقي
tagged_types_tu_compatible_p (const_شجرة t1, const_شجرة t2,
			      بنية comptypes_data *data)
{
  شجرة s1, s2;

  إذا (c_type_tag (t1) != c_type_tag (t2))
    أرجع خطأ;

  /* When forming equivalence classes for TYPE_CANONICAL in C23, we treat
     structs with the same tag as equivalent, but only when they are targets
     of pointers inside other structs.  */
  إذا (data->equiv && data->pointedto && NULL_شجرة != c_type_tag (t1))
    أرجع true;

  /* Different types without tag are incompatible except as an anonymous
     field or when forming equivalence classes for TYPE_CANONICAL.  */
  إذا (!data->anon_field && !data->equiv && NULL_شجرة == c_type_tag (t1))
    أرجع خطأ;

  إذا (!data->anon_field && TYPE_STUB_DECL (t1) != TYPE_STUB_DECL (t2))
    data->different_types_p = true;

  /* Incomplete types are incompatible inside a TU.  */
  إذا (TYPE_SIZE (t1) == عدم || TYPE_SIZE (t2) == عدم)
    أرجع خطأ;

  إذا (ENUMERAL_TYPE != شجرة_CODE (t1)
      && (TYPE_REVERSE_STORAGE_ORDER (t1)
	  != TYPE_REVERSE_STORAGE_ORDER (t2)))
    أرجع خطأ;

  إذا (TYPE_USER_ALIGN (t1) != TYPE_USER_ALIGN (t2))
    data->different_types_p = true;

  /* For types already being looked at in some active
     invocation of this function, assume compatibility.
     The cache is built as a linked list on the stack
     with the head of the list passed downwards.  */
  لكل (ثابت بنية tagged_tu_seen_cache *t = data->cache;
       t != عدم; t = t->next)
    إذا (t->t1 == t1 && t->t2 == t2)
      أرجع true;

  ثابت بنية tagged_tu_seen_cache entry = { data->cache, t1, t2 };

  بدل (شجرة_CODE (t1))
    {
    حالة ENUMERAL_TYPE:
      {
	إذا (!comptypes (ENUM_UNDERLYING_TYPE (t1), ENUM_UNDERLYING_TYPE (t2)))
	  أرجع خطأ;

	/* Speed up the case where the type values are in the same order.  */
	شجرة tv1 = TYPE_قيم (t1);
	شجرة tv2 = TYPE_قيم (t2);

	إذا (tv1 == tv2)
	  أرجع true;

	لكل (;tv1 && tv2; tv1 = شجرة_CHAIN (tv1), tv2 = شجرة_CHAIN (tv2))
	  {
	    إذا (شجرة_PURPOSE (tv1) != شجرة_PURPOSE (tv2))
	      اكسر;

	    إذا (simple_cst_equal (DECL_INITIAL (شجرة_قيمة (tv1)),
				  DECL_INITIAL (شجرة_قيمة (tv2))) != 1)
	      اكسر;
	  }

	إذا (tv1 == NULL_شجرة && tv2 == NULL_شجرة)
	  أرجع true;

	إذا (tv1 == NULL_شجرة || tv2 == NULL_شجرة)
	  أرجع خطأ;

	إذا (list_length (TYPE_قيم (t1)) != list_length (TYPE_قيم (t2)))
	  أرجع خطأ;

	لكل (s1 = TYPE_قيم (t1); s1; s1 = شجرة_CHAIN (s1))
	  {
	    s2 = purpose_member (شجرة_PURPOSE (s1), TYPE_قيم (t2));

	    إذا (s2 == عدم
		|| simple_cst_equal (DECL_INITIAL (شجرة_قيمة (s1)),
				     DECL_INITIAL (شجرة_قيمة (s2))) != 1)
	      أرجع خطأ;
	  }

	أرجع true;
      }

    حالة UNION_TYPE:
    حالة RECORD_TYPE:

	إذا (list_length (TYPE_FIELDS (t1)) != list_length (TYPE_FIELDS (t2)))
	  أرجع خطأ;

	لكل (s1 = TYPE_FIELDS (t1), s2 = TYPE_FIELDS (t2);
	     s1 && s2;
	     s1 = DECL_CHAIN (s1), s2 = DECL_CHAIN (s2))
	  {
	    gcc_assert (شجرة_CODE (s1) == FIELD_DECL);
	    gcc_assert (شجرة_CODE (s2) == FIELD_DECL);

	    شجرة ft1 = شجرة_TYPE (s1);
	    شجرة ft2 = شجرة_TYPE (s2);

	    إذا (DECL_NAME (s1) != DECL_NAME (s2))
	      أرجع خطأ;

	    إذا (DECL_ALIGN (s1) != DECL_ALIGN (s2))
	      أرجع خطأ;

	    إذا (DECL_C_BIT_FIELD (s1) != DECL_C_BIT_FIELD (s2))
	       أرجع خطأ;

	    إذا (DECL_C_BIT_FIELD (s1))
	      {
		إذا (!شجرة_int_cst_equal (DECL_SIZE (s1), DECL_SIZE (s2)))
		  أرجع خطأ;

		ft1 = DECL_BIT_FIELD_TYPE (s1);
		ft2 = DECL_BIT_FIELD_TYPE (s2);
	      }

	    إذا (!ft1 || !ft2)
	      أرجع خطأ;

	    إذا (شجرة_CODE (ft1) == ERROR_MARK || شجرة_CODE (ft2) == ERROR_MARK)
	      أرجع خطأ;

	    data->anon_field = !DECL_NAME (s1);
	    data->pointedto = خطأ;

	    ثابت بنية tagged_tu_seen_cache *cache = data->cache;
	    data->cache = &entry;
	    منطقي ret = comptypes_internal (ft1, ft2, data);
	    data->cache = cache;
	    إذا (!ret)
	      أرجع خطأ;

	    شجرة st1 = TYPE_SIZE (شجرة_TYPE (s1));
	    شجرة st2 = TYPE_SIZE (شجرة_TYPE (s2));

	    إذا (data->equiv
		&& st1 && شجرة_CODE (st1) == INTEGER_CST
		&& st2 && شجرة_CODE (st2) == INTEGER_CST
		&& !شجرة_int_cst_equal (st1, st2))
	     أرجع خطأ;

	    شجرة counted_by1 = lookup_attribute ("counted_by",
						 DECL_ATTRIBUTES (s1));
	    شجرة counted_by2 = lookup_attribute ("counted_by",
						 DECL_ATTRIBUTES (s2));
	    /* If there is no counted_by attribute for both fields.  */
	    إذا (!counted_by1 && !counted_by2)
	      استمر;

	    /* If only one field has counted_by attribute.  */
	    إذا ((counted_by1 && !counted_by2)
		|| (!counted_by1 && counted_by2))
	      أرجع خطأ;

	    /* Now both s1 and s2 have counted_by attributes, check
	       whether they are the same.  */

	    شجرة counted_by_field1
	      = lookup_field (t1, شجرة_قيمة (شجرة_قيمة (counted_by1)));
	    شجرة counted_by_field2
	      = lookup_field (t2, شجرة_قيمة (شجرة_قيمة (counted_by2)));

	    gcc_assert (counted_by_field1 && counted_by_field2);

	    طالما (شجرة_CHAIN (counted_by_field1))
	      counted_by_field1 = شجرة_CHAIN (counted_by_field1);
	    طالما (شجرة_CHAIN (counted_by_field2))
	      counted_by_field2 = شجرة_CHAIN (counted_by_field2);

	    إذا (DECL_NAME (شجرة_قيمة (counted_by_field1))
		!= DECL_NAME (شجرة_قيمة (counted_by_field2)))
	      أرجع خطأ;
	  }
	أرجع true;

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
function_types_compatible_p (const_شجرة f1, const_شجرة f2,
			     بنية comptypes_data *data)
{
  شجرة ret1 = شجرة_TYPE (f1);
  شجرة ret2 = شجرة_TYPE (f2);

  /* 'volatile' qualifiers on a function's return type used to mean
     the function is noreturn.  */
  إذا (TYPE_VOLATILE (ret1) != TYPE_VOLATILE (ret2))
    pedwarn (مدخل_location, 0, "function return types not compatible due to %<volatile%>");
  إذا (TYPE_VOLATILE (ret1))
    ret1 = build_qualified_type (TYPE_MAIN_VARIANT (ret1),
				 TYPE_QUALS (ret1) & ~TYPE_QUAL_VOLATILE);
  إذا (TYPE_VOLATILE (ret2))
    ret2 = build_qualified_type (TYPE_MAIN_VARIANT (ret2),
				 TYPE_QUALS (ret2) & ~TYPE_QUAL_VOLATILE);

  منطقي ignore_pargs = data->ignore_promoting_وسائط;
  data->ignore_promoting_وسائط = خطأ;

  إذا (!comptypes_internal (ret1, ret2, data))
    أرجع خطأ;

  data->ignore_promoting_وسائط = ignore_pargs;

  شجرة args1 = TYPE_ARG_TYPES (f1);
  شجرة args2 = TYPE_ARG_TYPES (f2);

  إذا ((args1 == NULL_شجرة) != (args2 == NULL_شجرة))
    data->different_types_p = true;

  /* An unspecified parmlist matches any specified parmlist
     whose argument types don't need default promotions.  */

  إذا (args1 == NULL_شجرة)
    {
      إذا (TYPE_NO_NAMED_وسائط_STDARG_P (f1) != TYPE_NO_NAMED_وسائط_STDARG_P (f2))
	أرجع خطأ;
      إذا (!(data->ignore_promoting_وسائط || self_promoting_وسائط_p (args2)))
	أرجع خطأ;
      data->ignore_promoting_وسائط = خطأ;
      /* If one of these types comes from a non-prototype fn definition,
	 compare that with the other type's arglist.
	 If they don't match, ask for a warning (but no error).  */
      إذا (TYPE_ACTUAL_ARG_TYPES (f1)
	  && !type_lists_compatible_p (args2, TYPE_ACTUAL_ARG_TYPES (f1), data))
	 data->warning_needed = true;
      أرجع true;
    }
  إذا (args2 == NULL_شجرة)
    {
      إذا (TYPE_NO_NAMED_وسائط_STDARG_P (f1) != TYPE_NO_NAMED_وسائط_STDARG_P (f2))
	أرجع خطأ;
      إذا (!(data->ignore_promoting_وسائط || self_promoting_وسائط_p (args1)))
	أرجع خطأ;
      data->ignore_promoting_وسائط = خطأ;
      إذا (TYPE_ACTUAL_ARG_TYPES (f2)
	  && !type_lists_compatible_p (args1, TYPE_ACTUAL_ARG_TYPES (f2), data))
	data->warning_needed = true;
      أرجع true;
    }

  /* Both types have argument lists: compare them and propagate results.  */
  أرجع type_lists_compatible_p (args1, args2, data);
}

/* Check two lists of types for compatibility, returning false for
   incompatible, true for compatible.  */

ساكن منطقي
type_lists_compatible_p (const_شجرة args1, const_شجرة args2,
			 بنية comptypes_data *data)
{
  طالما (1)
    {
      إذا (args1 == NULL_شجرة && args2 == NULL_شجرة)
	أرجع true;
      /* If one list is shorter than the other,
	 they fail to match.  */
      إذا (args1 == NULL_شجرة || args2 == NULL_شجرة)
	أرجع خطأ;
      شجرة a1 = شجرة_قيمة (args1);
      شجرة a2 = شجرة_قيمة (args2);
      شجرة mv1 = remove_qualifiers (a1);
      شجرة mv2 = remove_qualifiers (a2);

      gcc_assert (mv2);
      gcc_assert (mv2);

      /* If one of the lists has an error marker, ignore this arg.  */
      إذا (شجرة_CODE (a1) == ERROR_MARK
	       || شجرة_CODE (a2) == ERROR_MARK)
	;
      وإلا إذا (!comptypes_internal (mv1, mv2, data))
	{
	  data->different_types_p = true;
	  /* Allow  wait (union {union wait *u; int *i} *)
	     and  wait (union wait *)  to be compatible.  */
	  إذا (شجرة_CODE (a1) == UNION_TYPE
	      && (TYPE_NAME (a1) == NULL_شجرة
		  || TYPE_TRANSPARENT_AGGR (a1))
	      && شجرة_CODE (TYPE_SIZE (a1)) == INTEGER_CST
	      && شجرة_int_cst_equal (TYPE_SIZE (a1),
				     TYPE_SIZE (a2)))
	    {
	      شجرة memb;
	      لكل (memb = TYPE_FIELDS (a1);
		   memb; memb = DECL_CHAIN (memb))
		{
		  شجرة mv3 = remove_qualifiers (شجرة_TYPE (memb));
		  إذا (comptypes_internal (mv3, mv2, data))
		    اكسر;
		}
	      إذا (memb == NULL_شجرة)
		أرجع خطأ;
	    }
	  وإلا إذا (شجرة_CODE (a2) == UNION_TYPE
		   && (TYPE_NAME (a2) == NULL_شجرة
		       || TYPE_TRANSPARENT_AGGR (a2))
		   && شجرة_CODE (TYPE_SIZE (a2)) == INTEGER_CST
		   && شجرة_int_cst_equal (TYPE_SIZE (a2),
					  TYPE_SIZE (a1)))
	    {
	      شجرة memb;
	      لكل (memb = TYPE_FIELDS (a2);
		   memb; memb = DECL_CHAIN (memb))
		{
		  شجرة mv3 = remove_qualifiers (شجرة_TYPE (memb));
		  إذا (comptypes_internal (mv3, mv1, data))
		    اكسر;
		}
	      إذا (memb == NULL_شجرة)
		أرجع خطأ;
	    }
	  وإلا
	    أرجع خطأ;
	}

      args1 = شجرة_CHAIN (args1);
      args2 = شجرة_CHAIN (args2);
    }
}

/* Compute the size to increment a pointer by.  When a function type or void
   type or incomplete type is passed, size_one_node is returned.
   This function does not emit any diagnostics; the caller is responsible
   for that.  */

ساكن شجرة
c_size_in_bytes (const_شجرة type)
{
  تعداد شجرة_code code = شجرة_CODE (type);

  إذا (code == FUNCTION_TYPE || code == VOID_TYPE || code == ERROR_MARK
      || !COMPLETE_TYPE_P (type))
    أرجع size_one_عقدة;

  /* Convert in case a char is more than one unit.  */
  أرجع size_binop_loc (مدخل_location, CEIL_DIV_تعبير, TYPE_SIZE_UNIT (type),
			 size_int (TYPE_PRECISION (char_type_عقدة)
				   / BITS_PER_UNIT));
}

/* Return either DECL or its known constant value (if it has one).  */

شجرة
decl_constant_قيمة_1 (شجرة decl, منطقي in_init)
{
  إذا (/* Note that DECL_INITIAL isn't valid for a PARM_DECL.  */
      شجرة_CODE (decl) != PARM_DECL
      && !شجرة_THIS_VOLATILE (decl)
      && شجرة_READONLY (decl)
      && DECL_INITIAL (decl) != NULL_شجرة
      && !error_operand_p (DECL_INITIAL (decl))
      /* This is invalid if initial value is not constant.
	 If it has either a function call, a memory reference,
	 or a variable, then re-evaluating it could give different results.  */
      && شجرة_CONSTANT (DECL_INITIAL (decl))
      /* Check for cases where this is sub-optimal, even though valid.  */
      && (in_init || شجرة_CODE (DECL_INITIAL (decl)) != CONSTRUCTOR))
    أرجع DECL_INITIAL (decl);
  أرجع decl;
}

/* Return either DECL or its known constant value (if it has one).
   Like the above, but always return decl outside of functions.  */

شجرة
decl_constant_قيمة (شجرة decl)
{
  /* Don't change a variable array bound or initial value to a constant
     in a place where a variable is invalid.  */
  أرجع current_function_decl ? decl_constant_قيمة_1 (decl, خطأ) : decl;
}

/* Convert the array expression EXP to a pointer.  */
ساكن شجرة
array_to_pointer_conversion (location_t loc, شجرة exp)
{
  شجرة orig_exp = exp;
  شجرة type = شجرة_TYPE (exp);
  شجرة adr;
  شجرة restype = شجرة_TYPE (type);
  شجرة ptrtype;

  gcc_assert (شجرة_CODE (type) == ARRAY_TYPE);

  STRIP_TYPE_NOPS (exp);

  copy_warning (exp, orig_exp);

  ptrtype = c_build_pointer_type (restype);

  إذا (INDIRECT_REF_P (exp))
    أرجع convert (ptrtype, شجرة_OPERAND (exp, 0));

  /* In C++ array compound literals are temporary objects unless they are
     const or appear in namespace scope, so they are destroyed too soon
     to use them for much of anything  (c++/53220).  */
  إذا (warn_cxx_compat && شجرة_CODE (exp) == COMPOUND_LITERAL_تعبير)
    {
      شجرة decl = شجرة_OPERAND (شجرة_OPERAND (exp, 0), 0);
      إذا (!شجرة_READONLY (decl) && !شجرة_STATIC (decl))
	warning_at (DECL_SOURCE_LOCATION (decl), OPT_Wc___compat,
		    "converting an array compound literal to a pointer "
		    "leads to a dangling pointer in C++");
    }

  adr = build_unary_op (loc, ADDR_تعبير, exp, true);
  أرجع convert (ptrtype, adr);
}

/* Convert the function expression EXP to a pointer.  */
ساكن شجرة
function_to_pointer_conversion (location_t loc, شجرة exp)
{
  شجرة orig_exp = exp;

  gcc_assert (شجرة_CODE (شجرة_TYPE (exp)) == FUNCTION_TYPE);

  STRIP_TYPE_NOPS (exp);

  copy_warning (exp, orig_exp);

  شجرة exp2 = build_unary_op (loc, ADDR_تعبير, exp, خطأ);

  /* If the function is defined and known to not require a non-local
     context, make sure no trampoline is generated.  */
  إذا (شجرة_CODE (exp) == FUNCTION_DECL
      && DECL_INITIAL (exp) && !C_FUNC_NONLOCAL_CONTEXT (exp))
   شجرة_NO_TRAMPOLINE (exp2) = 1;

  أرجع exp2;
}

/* Mark EXP as read, not just set, for set but not used -Wunused
   warning purposes.  */

فراغ
mark_exp_read (شجرة exp)
{
  بدل (شجرة_CODE (exp))
    {
    حالة VAR_DECL:
    حالة PARM_DECL:
      DECL_READ_P (exp) = 1;
      اكسر;
    CASE_CONVERT:
      إذا (VOID_TYPE_P (شجرة_TYPE (exp)))
	بدل (شجرة_CODE (شجرة_OPERAND (exp, 0)))
	  {
	  حالة PREINCREMENT_تعبير:
	  حالة PREDECREMENT_تعبير:
	  حالة POSTINCREMENT_تعبير:
	  حالة POSTDECREMENT_تعبير:
	    أرجع;
	  افتراضي:
	    اكسر;
	  }
      /* FALLTHRU */
    حالة ARRAY_REF:
    حالة COMPONENT_REF:
    حالة MODIFY_تعبير:
    حالة REALPART_تعبير:
    حالة IMAGPART_تعبير:
    حالة ADDR_تعبير:
    حالة VIEW_CONVERT_تعبير:
    حالة PREINCREMENT_تعبير:
    حالة PREDECREMENT_تعبير:
    حالة POSTINCREMENT_تعبير:
    حالة POSTDECREMENT_تعبير:
      mark_exp_read (شجرة_OPERAND (exp, 0));
      اكسر;
    حالة COMPOUND_تعبير:
      /* Pattern match what build_atomic_assign produces with modifycode
	 NOP_EXPR.  */
      إذا (VAR_P (شجرة_OPERAND (exp, 1))
	  && DECL_ARTIFICIAL (شجرة_OPERAND (exp, 1))
	  && شجرة_CODE (شجرة_OPERAND (exp, 0)) == COMPOUND_تعبير)
	{
	  شجرة t1 = شجرة_OPERAND (شجرة_OPERAND (exp, 0), 0);
	  شجرة t2 = شجرة_OPERAND (شجرة_OPERAND (exp, 0), 1);
	  إذا (شجرة_CODE (t1) == TARGET_تعبير
	      && TARGET_تعبير_SLOT (t1) == شجرة_OPERAND (exp, 1)
	      && شجرة_CODE (t2) == CALL_تعبير)
	    {
	      شجرة fndecl = get_callee_fndecl (t2);
	      شجرة arg = NULL_شجرة;
	      إذا (fndecl
		  && شجرة_CODE (fndecl) == FUNCTION_DECL
		  && fndecl_built_in_p (fndecl, BUILT_IN_NORMAL)
		  && call_تعبير_nargs (t2) >= 2)
		بدل (DECL_FUNCTION_CODE (fndecl))
		  {
		  حالة BUILT_IN_ATOMIC_STORE:
		    arg = CALL_تعبير_ARG (t2, 1);
		    اكسر;
		  حالة BUILT_IN_ATOMIC_STORE_1:
		  حالة BUILT_IN_ATOMIC_STORE_2:
		  حالة BUILT_IN_ATOMIC_STORE_4:
		  حالة BUILT_IN_ATOMIC_STORE_8:
		  حالة BUILT_IN_ATOMIC_STORE_16:
		    arg = CALL_تعبير_ARG (t2, 0);
		    اكسر;
		  افتراضي:
		    اكسر;
		  }
	      إذا (arg)
		{
		  STRIP_NOPS (arg);
		  إذا (شجرة_CODE (arg) == ADDR_تعبير
		      && DECL_P (شجرة_OPERAND (arg, 0))
		      && TYPE_ATOMIC (شجرة_TYPE (شجرة_OPERAND (arg, 0))))
		    mark_exp_read (شجرة_OPERAND (arg, 0));
		}
	    }
	}
      /* FALLTHRU */
    حالة C_MAYBE_CONST_تعبير:
      mark_exp_read (شجرة_OPERAND (exp, 1));
      اكسر;
    حالة OMP_ARRAY_SECTION:
      mark_exp_read (شجرة_OPERAND (exp, 0));
      إذا (شجرة_OPERAND (exp, 1))
	mark_exp_read (شجرة_OPERAND (exp, 1));
      إذا (شجرة_OPERAND (exp, 2))
	mark_exp_read (شجرة_OPERAND (exp, 2));
      اكسر;
    افتراضي:
      اكسر;
    }
}

/* Perform the default conversion of arrays and functions to pointers.
   Return the result of converting EXP.  For any other expression, just
   return EXP.

   LOC is the location of the expression.  */

بنية c_تعبير
default_function_array_conversion (location_t loc, بنية c_تعبير exp)
{
  شجرة orig_exp = exp.قيمة;
  شجرة type = شجرة_TYPE (exp.قيمة);
  تعداد شجرة_code code = شجرة_CODE (type);

  بدل (code)
    {
    حالة ARRAY_TYPE:
      {
	منطقي not_lvalue = خطأ;
	منطقي lvalue_array_p;

	طالما ((شجرة_CODE (exp.قيمة) == NON_LVALUE_تعبير
		|| CONVERT_تعبير_P (exp.قيمة))
	       && شجرة_TYPE (شجرة_OPERAND (exp.قيمة, 0)) == type)
	  {
	    إذا (شجرة_CODE (exp.قيمة) == NON_LVALUE_تعبير)
	      not_lvalue = true;
	    exp.قيمة = شجرة_OPERAND (exp.قيمة, 0);
	  }

	copy_warning (exp.قيمة, orig_exp);

	lvalue_array_p = !not_lvalue && lvalue_p (exp.قيمة);
	إذا (!flag_isoc99 && !lvalue_array_p)
	  {
	    /* Before C99, non-lvalue arrays do not decay to pointers.
	       Normally, using such an array would be invalid; but it can
	       be used correctly inside sizeof or as a statement expression.
	       Thus, do not give an error here; an error will result later.  */
	    أرجع exp;
	  }

	exp.قيمة = array_to_pointer_conversion (loc, exp.قيمة);
      }
      اكسر;
    حالة FUNCTION_TYPE:
      exp.قيمة = function_to_pointer_conversion (loc, exp.قيمة);
      اكسر;
    افتراضي:
      اكسر;
    }

  أرجع exp;
}

بنية c_تعبير
default_function_array_read_conversion (location_t loc, بنية c_تعبير exp)
{
  mark_exp_read (exp.قيمة);
  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  إذا (شجرة_CODE (exp.قيمة) == COMPONENT_REF
      && handle_counted_by_p (exp.قيمة))
    exp.قيمة = handle_counted_by_for_component_ref (loc, exp.قيمة);
  أرجع default_function_array_conversion (loc, exp);
}

/* Return whether EXPR should be treated as an atomic lvalue for the
   purposes of load and store handling.  */

ساكن منطقي
really_atomic_lvalue (شجرة تعبير)
{
  إذا (error_operand_p (تعبير))
    أرجع خطأ;
  إذا (!TYPE_ATOMIC (شجرة_TYPE (تعبير)))
    أرجع خطأ;
  إذا (!COMPLETE_TYPE_P (شجرة_TYPE (تعبير)))
    أرجع خطأ;
  إذا (!lvalue_p (تعبير))
    أرجع خطأ;

  /* Ignore _Atomic on register variables, since their addresses can't
     be taken so (a) atomicity is irrelevant and (b) the normal atomic
     sequences wouldn't work.  Ignore _Atomic on structures containing
     bit-fields, since accessing elements of atomic structures or
     unions is undefined behavior (C11 6.5.2.3#5), but it's unclear if
     it's undefined at translation time or execution time, and the
     normal atomic sequences again wouldn't work.  */
  طالما (handled_component_p (تعبير))
    {
      إذا (شجرة_CODE (تعبير) == COMPONENT_REF
	  && DECL_C_BIT_FIELD (شجرة_OPERAND (تعبير, 1)))
	أرجع خطأ;
      تعبير = شجرة_OPERAND (تعبير, 0);
    }
  إذا (شجرة_CODE (تعبير) == COMPOUND_LITERAL_تعبير)
    تعبير = COMPOUND_LITERAL_تعبير_DECL (تعبير);
  إذا (DECL_P (تعبير) && C_DECL_REGISTER (تعبير))
    أرجع خطأ;
  أرجع true;
}

/* If EXPR is a named constant (C23) derived from a constexpr variable
   - that is, a reference to such a variable, or a member extracted by
   a sequence of structure and union (but not array) member accesses
   (where union member accesses must access the same member as
   initialized) - then return the corresponding initializer;
   otherwise, return NULL_TREE.  */

ساكن شجرة
maybe_get_constexpr_init (شجرة تعبير)
{
  شجرة decl = NULL_شجرة;
  إذا (شجرة_CODE (تعبير) == VAR_DECL)
    decl = تعبير;
  وإلا إذا (شجرة_CODE (تعبير) == COMPOUND_LITERAL_تعبير)
    decl = COMPOUND_LITERAL_تعبير_DECL (تعبير);
  إذا (decl
      && C_DECL_DECLARED_CONSTEXPR (decl)
      && DECL_INITIAL (decl) != NULL_شجرة
      && !error_operand_p (DECL_INITIAL (decl)))
    أرجع DECL_INITIAL (decl);
  إذا (شجرة_CODE (تعبير) != COMPONENT_REF)
    أرجع NULL_شجرة;
  شجرة inner = maybe_get_constexpr_init (شجرة_OPERAND (تعبير, 0));
  إذا (inner == NULL_شجرة)
    أرجع NULL_شجرة;
  طالما ((CONVERT_تعبير_P (inner) || شجرة_CODE (inner) == NON_LVALUE_تعبير)
	 && !error_operand_p (inner)
	 && (TYPE_MAIN_VARIANT (شجرة_TYPE (inner))
	     == TYPE_MAIN_VARIANT (شجرة_TYPE (شجرة_OPERAND (inner, 0)))))
    inner = شجرة_OPERAND (inner, 0);
  إذا (شجرة_CODE (inner) != CONSTRUCTOR)
    أرجع NULL_شجرة;
  شجرة field = شجرة_OPERAND (تعبير, 1);
  unsigned HOST_WIDE_INT cidx;
  شجرة cfield, cvalue;
  منطقي have_other_init = خطأ;
  FOR_EACH_CONSTRUCTOR_ELT (CONSTRUCTOR_ELTS (inner), cidx, cfield, cvalue)
    {
      إذا (cfield == field)
	أرجع cvalue;
      have_other_init = true;
    }
  إذا (شجرة_CODE (شجرة_TYPE (inner)) == UNION_TYPE
      && (have_other_init || field != TYPE_FIELDS (شجرة_TYPE (inner))))
    أرجع NULL_شجرة;
  /* Return a default initializer.  */
  إذا (RECORD_OR_UNION_TYPE_P (شجرة_TYPE (تعبير)))
    أرجع build_constructor (شجرة_TYPE (تعبير), عدم);
  أرجع build_zero_cst (شجرة_TYPE (تعبير));
}

/* Helper function for convert_lvalue_to_rvalue called via
   walk_tree_without_duplicates.  Find DATA inside of the expression.  */

ساكن شجرة
c_find_var_r (شجرة *tp, صحيح *walk_subtrees, فراغ *data)
{
  إذا (TYPE_P (*tp))
    *walk_subtrees = 0;
  وإلا إذا (*tp == (شجرة) data)
    أرجع *tp;
  أرجع NULL_شجرة;
}

/* Convert expression EXP (location LOC) from lvalue to rvalue,
   including converting functions and arrays to pointers if CONVERT_P.
   If READ_P, also mark the expression as having been read.  If
   FOR_INIT, constexpr expressions of structure and union type should
   be replaced by the corresponding CONSTRUCTOR; otherwise, only
   constexpr scalars (including elements of structures and unions) are
   replaced by their initializers.  */

بنية c_تعبير
convert_lvalue_to_rvalue (location_t loc, بنية c_تعبير exp,
			  منطقي convert_p, منطقي read_p, منطقي for_init)
{
  منطقي force_non_npc = خطأ;
  إذا (read_p)
    mark_exp_read (exp.قيمة);
  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  إذا (read_p && شجرة_CODE (exp.قيمة) == COMPONENT_REF
      && handle_counted_by_p (exp.قيمة))
    exp.قيمة = handle_counted_by_for_component_ref (loc, exp.قيمة);

  إذا (convert_p)
    exp = default_function_array_conversion (loc, exp);
  إذا (!VOID_TYPE_P (شجرة_TYPE (exp.قيمة))
      || (flag_isoc2y
	  && TYPE_QUALS (شجرة_TYPE (exp.قيمة)) != TYPE_UNQUALIFIED))
    exp.قيمة = require_complete_type (loc, exp.قيمة);
  إذا (for_init || !RECORD_OR_UNION_TYPE_P (شجرة_TYPE (exp.قيمة)))
    {
      شجرة init = maybe_get_constexpr_init (exp.قيمة);
      إذا (init != NULL_شجرة)
	{
	  /* A named constant of pointer type or type nullptr_t is not
	     a null pointer constant even if the initializer is
	     one.  */
	  إذا (شجرة_CODE (init) == INTEGER_CST
	      && !INTEGRAL_TYPE_P (شجرة_TYPE (init))
	      && integer_zerop (init))
	    force_non_npc = true;
	  exp.قيمة = init;
	}
    }
  إذا (really_atomic_lvalue (exp.قيمة))
    {
      vec<شجرة, va_gc> *params;
      شجرة nonatomic_type, tmp, tmp_addr, fndecl, func_call;
      شجرة تعبير_type = شجرة_TYPE (exp.قيمة);
      شجرة تعبير_addr = build_unary_op (loc, ADDR_تعبير, exp.قيمة, خطأ);
      شجرة seq_cst = build_int_cst (integer_type_عقدة, MEMMODEL_SEQ_CST);

      gcc_assert (TYPE_ATOMIC (تعبير_type));

      /* Expansion of a generic atomic load may require an addition
	 element, so allocate enough to prevent a resize.  */
      vec_alloc (params, 4);

      /* Remove the qualifiers for the rest of the expressions and
	 create the VAL temp variable to hold the RHS.  */
      nonatomic_type = build_qualified_type (تعبير_type, TYPE_UNQUALIFIED);
      tmp = create_tmp_var_raw (nonatomic_type);
      tmp_addr = build_unary_op (loc, ADDR_تعبير, tmp, خطأ);
      شجرة_ADDRESSABLE (tmp) = 1;
      /* Do not disable warnings for TMP even though it's artificial.
	 -Winvalid-memory-model depends on it.  */

      /* Issue __atomic_load (&expr, &tmp, SEQ_CST);  */
      fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_LOAD);
      params->quick_ادفع (تعبير_addr);
      params->quick_ادفع (tmp_addr);
      params->quick_ادفع (seq_cst);
      func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, عدم);

      /* EXPR is always read.  */
      mark_exp_read (exp.قيمة);

      /* Optimize the common case where c_build_function_call_vec
	 immediately folds __atomic_load (&expr, &tmp, SEQ_CST); into
	 tmp = __atomic_load_<N> (&expr, SEQ_CST);
	 In that case tmp is not addressable and can be initialized
	 fully by the rhs of the MODIFY_EXPR.  */
      شجرة tem = func_call;
      إذا (CONVERT_تعبير_P (tem) && VOID_TYPE_P (شجرة_TYPE (tem)))
	{
	  tem = شجرة_OPERAND (tem, 0);
	  إذا (شجرة_CODE (tem) == MODIFY_تعبير
	      && شجرة_OPERAND (tem, 0) == tmp
	      && !walk_شجرة_without_duplicates (&شجرة_OPERAND (tem, 1),
						c_find_var_r, tmp))
	    {
	      شجرة_ADDRESSABLE (tmp) = 0;
	      func_call = شجرة_OPERAND (tem, 1);
	    }
	}

      /* Return tmp which contains the value loaded.  */
      exp.قيمة = build4 (TARGET_تعبير, nonatomic_type, tmp, func_call,
			  NULL_شجرة, NULL_شجرة);
    }
  إذا (convert_p && !error_operand_p (exp.قيمة)
      && (شجرة_CODE (شجرة_TYPE (exp.قيمة)) != ARRAY_TYPE))
    exp.قيمة = convert (build_qualified_type (شجرة_TYPE (exp.قيمة), TYPE_UNQUALIFIED), exp.قيمة);
  إذا (force_non_npc)
    exp.قيمة = build1 (NOP_تعبير, شجرة_TYPE (exp.قيمة), exp.قيمة);

  {
    شجرة false_قيمة, true_قيمة;
    إذا (convert_p && !error_operand_p (exp.قيمة)
	&& c_hardbool_type_attr (شجرة_TYPE (exp.قيمة),
				 &false_قيمة, &true_قيمة))
      {
	شجرة t = save_تعبير (exp.قيمة);

	mark_exp_read (exp.قيمة);

	شجرة trapfn = builtin_decl_explicit (BUILT_IN_TRAP);
	شجرة تعبير = build_call_تعبير_loc (loc, trapfn, 0);
	تعبير = build_compound_تعبير (loc, تعبير, boolean_true_عقدة);
	تعبير = fold_build3_loc (loc, COND_تعبير, boolean_type_عقدة,
				fold_build2_loc (loc, NE_تعبير,
						 boolean_type_عقدة,
						 t, true_قيمة),
				تعبير, boolean_true_عقدة);
	تعبير = fold_build3_loc (loc, COND_تعبير, boolean_type_عقدة,
				fold_build2_loc (loc, NE_تعبير,
						 boolean_type_عقدة,
						 t, false_قيمة),
				تعبير, boolean_false_عقدة);

	exp.قيمة = تعبير;
      }
  }

  أرجع exp;
}

/* Wrapper for the overload above, same arguments but for tree rather than
   c_expr.  This is important for hardbools to decay to bools.  */

ساكن مضمن شجرة
convert_lvalue_to_rvalue (location_t loc, شجرة val,
			  منطقي convert_p, منطقي read_p, منطقي for_init = خطأ)
{
  بنية c_تعبير تعبير;
  memset (&تعبير, 0, حجم (تعبير));
  تعبير.قيمة = val;
  تعبير = convert_lvalue_to_rvalue (loc, تعبير, convert_p, read_p, for_init);
  أرجع تعبير.قيمة;
}

/* EXP is an expression of integer type.  Apply the integer promotions
   to it and return the promoted value.  */

شجرة
perform_integral_promotions (شجرة exp)
{
  شجرة type = شجرة_TYPE (exp);
  تعداد شجرة_code code = شجرة_CODE (type);

  gcc_assert (INTEGRAL_TYPE_P (type));

  /* Convert enums to the result of applying the integer promotions to
     their underlying type.  */
  إذا (code == ENUMERAL_TYPE)
    {
      type = ENUM_UNDERLYING_TYPE (type);
      إذا (c_promoting_integer_type_p (type))
	{
	  إذا (TYPE_UNSIGNED (type)
	      && TYPE_PRECISION (type) == TYPE_PRECISION (integer_type_عقدة))
	    type = unsigned_type_عقدة;
	  وإلا
	    type = integer_type_عقدة;
	}

      أرجع convert (type, exp);
    }

  /* ??? This should no longer be needed now bit-fields have their
     proper types.  */
  إذا (شجرة_CODE (exp) == COMPONENT_REF
      && DECL_C_BIT_FIELD (شجرة_OPERAND (exp, 1)))
    {
      إذا (BITINT_TYPE_P (DECL_BIT_FIELD_TYPE (شجرة_OPERAND (exp, 1))))
	{
	  شجرة btype = DECL_BIT_FIELD_TYPE (شجرة_OPERAND (exp, 1));
	  إذا (شجرة_CODE (btype) == BITINT_TYPE)
	    أرجع convert (btype, exp);
	  وإلا
	    أرجع convert (ENUM_UNDERLYING_TYPE (btype), exp);
	}
      /* If it's thinner than an int, promote it like a
	 c_promoting_integer_type_p, otherwise leave it alone.  */
      إذا (compare_شجرة_int (DECL_SIZE (شجرة_OPERAND (exp, 1)),
			    TYPE_PRECISION (integer_type_عقدة)) < 0)
	أرجع convert (integer_type_عقدة, exp);
    }

  إذا (c_promoting_integer_type_p (type))
    {
      /* Preserve unsignedness if not really getting any wider.  */
      إذا (TYPE_UNSIGNED (type)
	  && TYPE_PRECISION (type) == TYPE_PRECISION (integer_type_عقدة))
	أرجع convert (unsigned_type_عقدة, exp);

      أرجع convert (integer_type_عقدة, exp);
    }

  أرجع exp;
}


/* Perform default promotions for C data used in expressions.
   Enumeral types or short or char are converted to int.
   In addition, manifest constants symbols are replaced by their values.  */

شجرة
default_conversion (شجرة exp)
{
  شجرة orig_exp;
  شجرة type = شجرة_TYPE (exp);
  تعداد شجرة_code code = شجرة_CODE (type);
  شجرة promoted_type;

  mark_exp_read (exp);
  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  إذا (شجرة_CODE (exp) == COMPONENT_REF
      && handle_counted_by_p (exp))
    exp = handle_counted_by_for_component_ref (تعبير_LOCATION (exp), exp);

  /* Functions and arrays have been converted during parsing.  */
  gcc_assert (code != FUNCTION_TYPE);
  إذا (code == ARRAY_TYPE)
    أرجع exp;

  /* Constants can be used directly unless they're not loadable.  */
  إذا (شجرة_CODE (exp) == CONST_DECL)
    exp = DECL_INITIAL (exp);

  /* Strip no-op conversions.  */
  orig_exp = exp;
  STRIP_TYPE_NOPS (exp);

  copy_warning (exp, orig_exp);

  إذا (code == VOID_TYPE)
    {
      error_at (تعبير_LOC_OR_LOC (exp, مدخل_location),
		"void value not ignored as it ought to be");
      أرجع error_mark_عقدة;
    }

  exp = require_complete_type (تعبير_LOC_OR_LOC (exp, مدخل_location), exp);
  إذا (exp == error_mark_عقدة)
    أرجع error_mark_عقدة;

  promoted_type = targetm.promoted_type (type);
  إذا (promoted_type)
    أرجع convert (promoted_type, exp);

  إذا (INTEGRAL_TYPE_P (type))
    {
      /* Avoid performing integral promotion of bit-precise integer
	 type bit-field to its corresponding bit-precise integer if
	 orig_exp is a cast to it to its underlying type.  */
      إذا (orig_exp != exp
	  && شجرة_CODE (exp) == COMPONENT_REF
	  && DECL_C_BIT_FIELD (شجرة_OPERAND (exp, 1))
	  && BITINT_TYPE_P (DECL_BIT_FIELD_TYPE (شجرة_OPERAND (exp, 1))))
	أرجع perform_integral_promotions (orig_exp);
      أرجع perform_integral_promotions (exp);
    }

  أرجع exp;
}

/* Look up COMPONENT in a structure or union TYPE.

   If the component name is not found, returns NULL_TREE.  Otherwise,
   the return value is a TREE_LIST, with each TREE_VALUE a FIELD_DECL
   stepping down the chain to the component, which is in the last
   TREE_VALUE of the list.  Normally the list is of length one, but if
   the component is embedded within (nested) anonymous structures or
   unions, the list steps down the chain to the component.  */

شجرة
lookup_field (const_شجرة type, شجرة component)
{
  شجرة field;

  /* If TYPE_LANG_SPECIFIC is set, then it is a sorted array of pointers
     to the field elements.  Use a binary search on this array to quickly
     find the element.  Otherwise, do a linear search.  TYPE_LANG_SPECIFIC
     will always be set for structures which have many elements.

     Duplicate field checking replaces duplicates with NULL_TREE so
     TYPE_LANG_SPECIFIC arrays are potentially no longer sorted.  In that
     case just iterate using DECL_CHAIN.  */

  إذا (TYPE_LANG_SPECIFIC (type) && TYPE_LANG_SPECIFIC (type)->s
      && !seen_error ())
    {
      صحيح bot, قمة, half;
      شجرة *field_array = &TYPE_LANG_SPECIFIC (type)->s->elts[0];

      field = TYPE_FIELDS (type);
      bot = 0;
      قمة = TYPE_LANG_SPECIFIC (type)->s->len;
      طالما (قمة - bot > 1)
	{
	  half = (قمة - bot + 1) >> 1;
	  field = field_array[bot+half];

	  إذا (DECL_NAME (field) == NULL_شجرة)
	    {
	      /* Step through all anon unions in linear fashion.  */
	      طالما (DECL_NAME (field_array[bot]) == NULL_شجرة)
		{
		  field = field_array[bot++];
		  إذا (RECORD_OR_UNION_TYPE_P (شجرة_TYPE (field)))
		    {
		      شجرة anon = lookup_field (شجرة_TYPE (field), component);

		      إذا (anon)
			أرجع شجرة_cons (NULL_شجرة, field, anon);

		      /* The Plan 9 compiler permits referring
			 directly to an anonymous struct/union field
			 using a typedef name.  */
		      إذا (flag_plan9_extensions
			  && TYPE_NAME (شجرة_TYPE (field)) != NULL_شجرة
			  && (شجرة_CODE (TYPE_NAME (شجرة_TYPE (field)))
			      == TYPE_DECL)
			  && (DECL_NAME (TYPE_NAME (شجرة_TYPE (field)))
			      == component))
			اكسر;
		    }
		}

	      /* Entire record is only anon unions.  */
	      إذا (bot > قمة)
		أرجع NULL_شجرة;

	      /* Restart the binary search, with new lower bound.  */
	      استمر;
	    }

	  إذا (DECL_NAME (field) == component)
	    اكسر;
	  إذا (DECL_NAME (field) < component)
	    bot += half;
	  وإلا
	    قمة = bot + half;
	}

      إذا (DECL_NAME (field_array[bot]) == component)
	field = field_array[bot];
      وإلا إذا (DECL_NAME (field) != component)
	أرجع NULL_شجرة;
    }
  وإلا
    {
      لكل (field = TYPE_FIELDS (type); field; field = DECL_CHAIN (field))
	{
	  إذا (DECL_NAME (field) == NULL_شجرة
	      && RECORD_OR_UNION_TYPE_P (شجرة_TYPE (field)))
	    {
	      شجرة anon = lookup_field (شجرة_TYPE (field), component);

	      إذا (anon)
		أرجع شجرة_cons (NULL_شجرة, field, anon);

	      /* The Plan 9 compiler permits referring directly to an
		 anonymous struct/union field using a typedef
		 name.  */
	      إذا (flag_plan9_extensions
		  && TYPE_NAME (شجرة_TYPE (field)) != NULL_شجرة
		  && شجرة_CODE (TYPE_NAME (شجرة_TYPE (field))) == TYPE_DECL
		  && (DECL_NAME (TYPE_NAME (شجرة_TYPE (field)))
		      == component))
		اكسر;
	    }

	  إذا (DECL_NAME (field) == component)
	    اكسر;
	}

      إذا (field == NULL_شجرة)
	أرجع NULL_شجرة;
    }

  أرجع شجرة_cons (NULL_شجرة, field, NULL_شجرة);
}

/* Recursively append candidate IDENTIFIER_NODEs to CANDIDATES.  */

ساكن فراغ
lookup_field_fuzzy_find_candidates (شجرة type, شجرة component,
				    vec<شجرة> *candidates)
{
  شجرة field;
  لكل (field = TYPE_FIELDS (type); field; field = DECL_CHAIN (field))
    {
      إذا (DECL_NAME (field) == NULL_شجرة
	  && RECORD_OR_UNION_TYPE_P (شجرة_TYPE (field)))
	lookup_field_fuzzy_find_candidates (شجرة_TYPE (field), component,
					    candidates);

      إذا (DECL_NAME (field))
	candidates->safe_ادفع (DECL_NAME (field));
    }
}

/* Like "lookup_field", but find the closest matching IDENTIFIER_NODE,
   rather than returning a TREE_LIST for an exact match.  */

ساكن شجرة
lookup_field_fuzzy (شجرة type, شجرة component)
{
  gcc_assert (شجرة_CODE (component) == IDENTIFIER_عقدة);

  /* First, gather a list of candidates.  */
  auto_vec <شجرة> candidates;

  lookup_field_fuzzy_find_candidates (type, component,
				      &candidates);

  أرجع find_closest_identifier (component, &candidates);
}

/* Support function for build_component_ref's error-handling.

   Given DATUM_TYPE, and "DATUM.COMPONENT", where DATUM is *not* a
   struct or union, should we suggest "DATUM->COMPONENT" as a hint?  */

ساكن منطقي
should_suggest_deref_p (شجرة datum_type)
{
  /* We don't do it for Objective-C, since Objective-C 2.0 dot-syntax
     allows "." for ptrs; we could be handling a failed attempt
     to access a property.  */
  إذا (c_dialect_objc ())
    أرجع خطأ;

  /* Only suggest it for pointers...  */
  إذا (شجرة_CODE (datum_type) != POINTER_TYPE)
    أرجع خطأ;

  /* ...to structs/unions.  */
  شجرة underlying_type = شجرة_TYPE (datum_type);
  تعداد شجرة_code code = شجرة_CODE (underlying_type);
  إذا (code == RECORD_TYPE || code == UNION_TYPE)
    أرجع true;
  وإلا
    أرجع خطأ;
}

/* Give a component ref REF, decide whether we should handle its counted_by
   attribute based on its context:
   Do not handle counted_by when in offsetof, typeof and alignof operator.  */

ساكن منطقي
handle_counted_by_p (شجرة ref)
{
  gcc_assert (شجرة_CODE (ref) == COMPONENT_REF);
  شجرة datum = شجرة_OPERAND (ref, 0);
  /* If the component_ref is build for a offsetof, i.e., the datum
     of the component_ref is a indirect_ref of null_pointer_node,
     we should not generate call to .ACCESS_WITH_SIZE.  */
  إذا (شجرة_CODE (datum) == INDIRECT_REF
      && شجرة_OPERAND (datum, 0) == null_pointer_عقدة)
    أرجع خطأ;
  إذا (in_typeof || in_alignof)
    أرجع خطأ;
  أرجع true;
}

/* Given a component ref REF, if there is a counted_by attribute attached,
   issue error when the element_type is a structure or union including a
   flexible array member.  */

ساكن فراغ
check_counted_by_attribute (location_t loc, شجرة ref)
{
  شجرة subdatum = شجرة_OPERAND (ref, 1);
  شجرة sub_type = شجرة_TYPE (subdatum);

  إذا (!flexible_array_member_type_p (sub_type)
      && شجرة_CODE (sub_type) != POINTER_TYPE)
    أرجع;

  شجرة element_type = شجرة_TYPE (sub_type);

  شجرة attr_counted_by = lookup_attribute ("counted_by",
					   DECL_ATTRIBUTES (subdatum));
  إذا (attr_counted_by)
    {
      /* Issue error when the element_type is a structure or
	union including a flexible array member.  */
      إذا (RECORD_OR_UNION_TYPE_P (element_type)
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

ساكن شجرة
build_counted_by_ref (شجرة datum, شجرة subdatum,
		      شجرة *counted_by_type)
{
  شجرة sub_type = شجرة_TYPE (subdatum);
  إذا (!flexible_array_member_type_p (sub_type)
      && شجرة_CODE (sub_type) != POINTER_TYPE)
    أرجع NULL_شجرة;

  شجرة attr_counted_by = lookup_attribute ("counted_by",
					   DECL_ATTRIBUTES (subdatum));
  إذا (!attr_counted_by)
    أرجع NULL_شجرة;

  شجرة counted_by_ref = NULL_شجرة;
  *counted_by_type = NULL_شجرة;

  شجرة type = شجرة_TYPE (datum);

  /* If the type of the containing structure is an anonymous struct/union,
     and this anonymous struct/union is not a root type, get the first
     outer named structure/union type.  */
  طالما (شجرة_CODE (datum) == COMPONENT_REF
	 && c_type_tag (type) == NULL_شجرة
	 && DECL_NAME (شجرة_OPERAND (datum, 1)) == NULL_شجرة)
    {
      datum = شجرة_OPERAND (datum, 0);
      type = شجرة_TYPE (datum);
    }

  شجرة field_id = شجرة_قيمة (شجرة_قيمة (attr_counted_by));
  شجرة counted_by_field = lookup_field (type, field_id);
  gcc_assert (counted_by_field);

  شجرة counted_by_subdatum;
  افعل
    {
      counted_by_subdatum = شجرة_قيمة (counted_by_field);
      /* Get the TYPE of the counted_by field.  */
      *counted_by_type = شجرة_TYPE (counted_by_subdatum);

      counted_by_ref
	= build3 (COMPONENT_REF, شجرة_TYPE (counted_by_subdatum),
		  datum, counted_by_subdatum, NULL_شجرة);

      datum = counted_by_ref;
      counted_by_field = شجرة_CHAIN (counted_by_field);
    }
  طالما (counted_by_field);

  counted_by_ref = build_fold_addr_تعبير (counted_by_ref);
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
ساكن شجرة
build_access_with_size_for_counted_by (location_t loc, شجرة ref,
				       شجرة counted_by_ref,
				       شجرة counted_by_type)
{
  gcc_assert (flexible_array_member_type_p (شجرة_TYPE (ref))
	      || شجرة_CODE (شجرة_TYPE (ref)) == POINTER_TYPE);

  منطقي is_fam = flexible_array_member_type_p (شجرة_TYPE (ref));

  /* The result type of the call is a pointer to the flexible array type;
     or is the original pointer type to the pointer field with counted_by.  */
  شجرة result_type = is_fam ? c_build_pointer_type (شجرة_TYPE (ref))
		     : شجرة_TYPE (ref);

  شجرة element_type = شجرة_TYPE (شجرة_TYPE (ref));
  شجرة element_size = VOID_TYPE_P (element_type)
		      ? size_one_عقدة
		      : TYPE_SIZE_UNIT (element_type);
  إذا (element_size == NULL_شجرة)
    أرجع ref;

  شجرة first_param = is_fam
		     ? c_fully_fold (array_to_pointer_conversion (loc, ref),
				     خطأ, عدم)
		     : c_fully_fold (ref, خطأ, عدم);
  شجرة second_param
    = c_fully_fold (counted_by_ref, خطأ, عدم);
  شجرة third_param = build_int_cst (c_build_pointer_type (counted_by_type), 0);

  شجرة call
    = build_call_تعبير_internal_loc (loc, IFN_ACCESS_WITH_SIZE,
				    result_type, 4,
				    first_param,
				    second_param,
				    third_param,
				    element_size);

  /* Wrap the call with an INDIRECT_REF with the flexible array type.  */
  إذا (is_fam)
    call = build1 (INDIRECT_REF, شجرة_TYPE (ref), call);
  SET_تعبير_LOCATION (call, loc);
  أرجع call;
}

/* For the COMPONENT_REF ref, check whether it has a counted_by attribute,
   if so, wrap this COMPONENT_REF with the corresponding CALL to the
   function .ACCESS_WITH_SIZE.
   Otherwise, return the ref itself.  */

شجرة
handle_counted_by_for_component_ref (location_t loc, شجرة ref)
{
  gcc_assert (شجرة_CODE (ref) == COMPONENT_REF);
  شجرة datum = شجرة_OPERAND (ref, 0);
  شجرة subdatum = شجرة_OPERAND (ref, 1);
  شجرة counted_by_type = NULL_شجرة;

  إذا (!(flexible_array_member_type_p (شجرة_TYPE (ref))
	|| شجرة_CODE (شجرة_TYPE (ref)) == POINTER_TYPE))
    أرجع ref;

  شجرة counted_by_ref = build_counted_by_ref (datum, subdatum,
					      &counted_by_type);
  إذا (counted_by_ref)
    ref = build_access_with_size_for_counted_by (loc, ref,
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

شجرة
build_component_ref (location_t loc, شجرة datum, شجرة component,
		     location_t component_loc, location_t arrow_loc)
{
  شجرة type = شجرة_TYPE (datum);
  تعداد شجرة_code code = شجرة_CODE (type);
  شجرة field = عدم;
  شجرة ref;
  منطقي datum_lvalue = lvalue_p (datum);

  إذا (!objc_is_public (datum, component))
    أرجع error_mark_عقدة;

  /* Detect Objective-C property syntax object.property.  */
  إذا (c_dialect_objc ()
      && (ref = objc_maybe_build_component_ref (datum, component)))
    أرجع ref;

  /* See if there is a field or component with name COMPONENT.  */

  إذا (code == RECORD_TYPE || code == UNION_TYPE)
    {
      إذا (!COMPLETE_TYPE_P (type))
	{
	  c_incomplete_type_error (loc, NULL_شجرة, type);
	  أرجع error_mark_عقدة;
	}

      field = lookup_field (type, component);

      إذا (!field)
	{
	  شجرة guessed_id = lookup_field_fuzzy (type, component);
	  إذا (guessed_id)
	    {
	      /* Attempt to provide a fixit replacement hint, if
		 we have a valid range for the component.  */
	      location_t reported_loc
		= (component_loc != UNKNOWN_LOCATION) ? component_loc : loc;
	      gcc_rich_location rich_loc (reported_loc);
	      إذا (component_loc != UNKNOWN_LOCATION)
		rich_loc.add_fixit_misspelled_id (component_loc, guessed_id);
	      error_at (&rich_loc,
			"%qT has no member named %qE; did you mean %qE?",
			type, component, guessed_id);
	    }
	  وإلا
	    error_at (loc, "%qT has no member named %qE", type, component);
	  أرجع error_mark_عقدة;
	}

      /* Accessing elements of atomic structures or unions is undefined
	 behavior (C11 6.5.2.3#5).  */
      إذا (TYPE_ATOMIC (type) && c_inhibit_evaluation_warnings == 0)
	{
	  إذا (code == RECORD_TYPE)
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
	  شجرة subdatum = شجرة_قيمة (field);
	  صحيح quals;
	  شجرة subtype;
	  منطقي use_datum_quals;

	  إذا (شجرة_TYPE (subdatum) == error_mark_عقدة)
	    أرجع error_mark_عقدة;

	  /* If this is an rvalue, it does not have qualifiers in C
	     standard terms and we must avoid propagating such
	     qualifiers down to a non-lvalue array that is then
	     converted to a pointer.  */
	  use_datum_quals = (datum_lvalue
			     || شجرة_CODE (شجرة_TYPE (subdatum)) != ARRAY_TYPE);

	  quals = TYPE_QUALS (strip_array_types (شجرة_TYPE (subdatum)));
	  إذا (use_datum_quals)
	    quals |= TYPE_QUALS (شجرة_TYPE (datum));
	  subtype = c_build_qualified_type (شجرة_TYPE (subdatum), quals);

	  ref = build3 (COMPONENT_REF, subtype, datum, subdatum,
			NULL_شجرة);
	  SET_تعبير_LOCATION (ref, loc);

	  check_counted_by_attribute (loc, ref);

	  إذا (شجرة_READONLY (subdatum)
	      || (use_datum_quals && شجرة_READONLY (datum)))
	    شجرة_READONLY (ref) = 1;
	  إذا (شجرة_THIS_VOLATILE (subdatum)
	      || (use_datum_quals && شجرة_THIS_VOLATILE (datum)))
	    شجرة_THIS_VOLATILE (ref) = 1;

	  إذا (شجرة_UNAVAILABLE (subdatum))
	    error_unavailable_use (subdatum, NULL_شجرة);
	  وإلا إذا (شجرة_DEPRECATED (subdatum))
	    warn_deprecated_use (subdatum, NULL_شجرة);

	  datum = ref;

	  field = شجرة_CHAIN (field);
	}
      طالما (field);

      أرجع ref;
    }
  وإلا إذا (should_suggest_deref_p (type))
    {
      /* Special-case the error message for "ptr.field" for the case
	 where the user has confused "." vs "->".  */
      rich_location richloc (سطر_table, loc);
      إذا (INDIRECT_REF_P (datum) && arrow_loc != UNKNOWN_LOCATION)
	{
	  richloc.add_fixit_أدرج_before (arrow_loc, "(*");
	  richloc.add_fixit_أدرج_after (arrow_loc, ")");
	  error_at (&richloc,
		    "%qE is a pointer to pointer; did you mean to dereference "
		    "it before applying %<->%> to it?",
		    شجرة_OPERAND (datum, 0));
	}
      وإلا
	{
	  /* "loc" should be the "." token.  */
	  richloc.add_fixit_replace ("->");
	  error_at (&richloc,
		    "%qE is a pointer; did you mean to use %<->%>?",
		    datum);
	}
      أرجع error_mark_عقدة;
    }
  وإلا إذا (code != ERROR_MARK)
    error_at (loc,
	      "request for member %qE in something not a structure or union",
	      component);

  أرجع error_mark_عقدة;
}

/* Given an expression PTR for a pointer, return an expression
   for the value pointed to.
   ERRORSTRING is the name of the operator to appear in error messages.

   LOC is the location to use for the generated tree.  */

شجرة
build_indirect_ref (location_t loc, شجرة ptr, ref_operator errstring)
{
  شجرة pointer = default_conversion (ptr);
  شجرة type = شجرة_TYPE (pointer);
  شجرة ref;

  إذا (شجرة_CODE (type) == POINTER_TYPE)
    {
      إذا (CONVERT_تعبير_P (pointer)
          || شجرة_CODE (pointer) == VIEW_CONVERT_تعبير)
	{
	  /* If a warning is issued, mark it to avoid duplicates from
	     the backend.  This only needs to be done at
	     warn_strict_aliasing > 2.  */
	  إذا (warn_strict_aliasing > 2)
	    إذا (strict_aliasing_warning (تعبير_LOCATION (pointer),
					 type, شجرة_OPERAND (pointer, 0)))
	      suppress_warning (pointer, OPT_Wstrict_aliasing_);
	}

      إذا (شجرة_CODE (pointer) == ADDR_تعبير
	  && (شجرة_TYPE (شجرة_OPERAND (pointer, 0))
	      == شجرة_TYPE (type)))
	{
	  ref = شجرة_OPERAND (pointer, 0);
	  protected_set_تعبير_location (ref, loc);
	  أرجع ref;
	}
      وإلا
	{
	  شجرة t = شجرة_TYPE (type);

	  ref = build1 (INDIRECT_REF, t, pointer);

	  إذا (VOID_TYPE_P (t) && c_inhibit_evaluation_warnings == 0)
	    warning_at (loc, 0, "dereferencing %<void *%> pointer");

	  /* We *must* set TREE_READONLY when dereferencing a pointer to const,
	     so that we get the proper error message if the result is used
	     to assign to.  Also, &* is supposed to be a no-op.
	     And ANSI C seems to specify that the type of the result
	     should be the const type.  */
	  /* A de-reference of a pointer to const is not a const.  It is valid
	     to change it via some other pointer.  */
	  شجرة_READONLY (ref) = TYPE_READONLY (t);
	  شجرة_SIDE_EFFECTS (ref)
	    = TYPE_VOLATILE (t) || شجرة_SIDE_EFFECTS (pointer);
	  شجرة_THIS_VOLATILE (ref) = TYPE_VOLATILE (t);
	  protected_set_تعبير_location (ref, loc);
	  أرجع ref;
	}
    }
  وإلا إذا (شجرة_CODE (pointer) != ERROR_MARK)
    invalid_indirection_error (loc, type, errstring);

  أرجع error_mark_عقدة;
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

شجرة
build_array_ref (location_t loc, شجرة array, شجرة index)
{
  شجرة ret;
  منطقي swapped = خطأ;
  إذا (شجرة_TYPE (array) == error_mark_عقدة
      || شجرة_TYPE (index) == error_mark_عقدة)
    أرجع error_mark_عقدة;

  إذا (شجرة_CODE (شجرة_TYPE (array)) != ARRAY_TYPE
      && شجرة_CODE (شجرة_TYPE (array)) != POINTER_TYPE
      /* Allow vector[index] but not index[vector].  */
      && !gnu_vector_type_p (شجرة_TYPE (array)))
    {
      إذا (شجرة_CODE (شجرة_TYPE (index)) != ARRAY_TYPE
	  && شجرة_CODE (شجرة_TYPE (index)) != POINTER_TYPE)
	{
          error_at (loc,
            "subscripted value is neither array nor pointer nor vector");

	  أرجع error_mark_عقدة;
	}
      std::swap (array, index);
      swapped = true;
    }

  إذا (!INTEGRAL_TYPE_P (شجرة_TYPE (index)))
    {
      error_at (loc, "array subscript is not an integer");
      أرجع error_mark_عقدة;
    }

  إذا (شجرة_CODE (شجرة_TYPE (شجرة_TYPE (array))) == FUNCTION_TYPE)
    {
      error_at (loc, "subscripted value is pointer to function");
      أرجع error_mark_عقدة;
    }

  /* ??? Existing practice has been to warn only when the char
     index is syntactically the index, not for char[array].  */
  إذا (!swapped)
     warn_array_subscript_with_type_char (loc, index);

  /* Apply default promotions *after* noticing character types.  */
  index = default_conversion (index);
  إذا (index == error_mark_عقدة)
    أرجع error_mark_عقدة;

  gcc_assert (شجرة_CODE (شجرة_TYPE (index)) == INTEGER_TYPE
	      || شجرة_CODE (شجرة_TYPE (index)) == BITINT_TYPE);

  منطقي was_vector = VECTOR_TYPE_P (شجرة_TYPE (array));
  منطقي non_lvalue = convert_vector_to_array_for_subscript (loc, &array, index);

  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  إذا (شجرة_CODE (array) == COMPONENT_REF
      && handle_counted_by_p (array))
    array = handle_counted_by_for_component_ref (loc, array);

  إذا (شجرة_CODE (شجرة_TYPE (array)) == ARRAY_TYPE)
    {
      شجرة rval, type;

      /* An array that is indexed by a non-constant
	 cannot be stored in a register; we must be able to do
	 address arithmetic on its address.
	 Likewise an array of elements of variable size.  */
      إذا (شجرة_CODE (index) != INTEGER_CST
	  || (COMPLETE_TYPE_P (شجرة_TYPE (شجرة_TYPE (array)))
	      && شجرة_CODE (TYPE_SIZE (شجرة_TYPE (شجرة_TYPE (array)))) != INTEGER_CST))
	{
	  إذا (!c_mark_addressable (array, true, true))
	    أرجع error_mark_عقدة;
	}
      /* An array that is indexed by a constant value which is not within
	 the array bounds cannot be stored in a register either; because we
	 would get a crash in store_bit_field/extract_bit_field when trying
	 to access a non-existent part of the register.  */
      إذا (شجرة_CODE (index) == INTEGER_CST
	  && TYPE_DOMAIN (شجرة_TYPE (array))
	  && !int_fits_type_p (index, TYPE_DOMAIN (شجرة_TYPE (array))))
	{
	  إذا (!c_mark_addressable (array, خطأ, true))
	    أرجع error_mark_عقدة;
	  /* ISO C2Y disallows a negative integer constant expression index
	     when array subscripting has an operand of array type.  */
	  إذا (flag_isoc2y
	      && !شجرة_OVERFLOW (index)
	      && شجرة_int_cst_sgn (index) < 0)
	    error_at (loc, "array subscript is negative");
	}

      إذا ((pedantic || warn_c90_c99_compat || warn_c23_c2y_compat)
	  && ! was_vector)
	{
	  شجرة foo = array;
	  طالما (شجرة_CODE (foo) == COMPONENT_REF)
	    foo = شجرة_OPERAND (foo, 0);
	  إذا ((VAR_P (foo) && C_DECL_REGISTER (foo))
	      || (شجرة_CODE (foo) == COMPOUND_LITERAL_تعبير
		  && C_DECL_REGISTER (COMPOUND_LITERAL_تعبير_DECL (foo))))
	    pedwarn_c23 (loc, OPT_Wpedantic,
			 "ISO C forbids subscripting %<register%> array "
			 "before C2Y");
	  وإلا إذا (!lvalue_p (foo))
	    pedwarn_c90 (loc, OPT_Wpedantic,
			 "ISO C90 forbids subscripting non-lvalue "
			 "array");
	}

      إذا (شجرة_CODE (شجرة_TYPE (index)) == BITINT_TYPE
	  && TYPE_PRECISION (شجرة_TYPE (index)) > TYPE_PRECISION (sizetype))
	index = fold_convert (sizetype, index);

      type = شجرة_TYPE (شجرة_TYPE (array));
      rval = build4 (ARRAY_REF, type, array, index, NULL_شجرة, NULL_شجرة);
      /* Array ref is const/volatile if the array elements are
	 or if the array is.  */
      شجرة_READONLY (rval)
	|= (TYPE_READONLY (شجرة_TYPE (شجرة_TYPE (array)))
	    | شجرة_READONLY (array));
      شجرة_SIDE_EFFECTS (rval)
	|= (TYPE_VOLATILE (شجرة_TYPE (شجرة_TYPE (array)))
	    | شجرة_SIDE_EFFECTS (array));
      شجرة_THIS_VOLATILE (rval)
	|= (TYPE_VOLATILE (شجرة_TYPE (شجرة_TYPE (array)))
	    /* This was added by rms on 16 Nov 91.
	       It fixes  vol struct foo *a;  a->elts[1]
	       in an inline function.
	       Hope it doesn't break something else.  */
	    | شجرة_THIS_VOLATILE (array));
      ret = require_complete_type (loc, rval);
      protected_set_تعبير_location (ret, loc);
      إذا (non_lvalue)
	ret = non_lvalue_loc (loc, ret);
      أرجع ret;
    }
  وإلا
    {
      شجرة ar = default_conversion (array);

      إذا (ar == error_mark_عقدة)
	أرجع ar;

      gcc_assert (شجرة_CODE (شجرة_TYPE (ar)) == POINTER_TYPE);
      gcc_assert (شجرة_CODE (شجرة_TYPE (شجرة_TYPE (ar))) != FUNCTION_TYPE);

      ret = build_indirect_ref (loc, build_ثنائي_op (loc, PLUS_تعبير, ar,
						      index, خطأ),
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

شجرة
build_omp_array_section (location_t loc, شجرة array, شجرة index, شجرة length)
{
  شجرة type = شجرة_TYPE (array);
  gcc_assert (type);

  شجرة sectype, eltype = شجرة_TYPE (type);

  /* It's not an array or pointer type.  Just reuse the type of the original
     expression as the type of the array section (an error will be raised
     anyway, later).  */
  إذا (eltype == NULL_شجرة || error_operand_p (eltype))
    sectype = شجرة_TYPE (array);
  وإلا
    {
      شجرة idxtype = NULL_شجرة;

      إذا (index != NULL_شجرة
	  && length != NULL_شجرة
	  && INTEGRAL_TYPE_P (شجرة_TYPE (index))
	  && INTEGRAL_TYPE_P (شجرة_TYPE (length)))
	{
	  شجرة أدنى = fold_convert (sizetype, index);
	  شجرة عالي = fold_convert (sizetype, length);
	  عالي = size_binop (PLUS_تعبير, أدنى, عالي);
	  عالي = size_binop (MINUS_تعبير, عالي, size_one_عقدة);
	  idxtype = build_range_type (sizetype, أدنى, عالي);
	}
      وإلا إذا ((index == NULL_شجرة || integer_zerop (index))
	       && length != NULL_شجرة
	       && INTEGRAL_TYPE_P (شجرة_TYPE (length)))
	idxtype = build_index_type (length);

      gcc_assert (!error_operand_p (idxtype));

      sectype = c_build_array_type (eltype, idxtype);
    }

  أرجع build3_loc (loc, OMP_ARRAY_SECTION, sectype, array, index, length);
}


/* Record that REF is used.  This is relevant for undeclared static
   function and declarations referenced from a non-local context.
   ADDRESS indicates whether the address is taken.  */

فراغ
mark_decl_used (شجرة ref, منطقي address)
{
  إذا (!ref || !DECL_P (ref) || in_alignof)
    أرجع;

  /* Non-file-scope and non-local reference in nested function.  */
  منطقي nonloc_p = current_function_decl && DECL_CONTEXT (ref)
		  && DECL_CONTEXT (current_function_decl)
		  && DECL_CONTEXT (ref) != current_function_decl;

  /* An undeclared static function.  */
  منطقي static_p = شجرة_CODE (ref) == FUNCTION_DECL
		  && DECL_INITIAL (ref) == NULL_شجرة
		  && DECL_EXTERNAL (ref)
		  && !شجرة_PUBLIC (ref);

  إذا (!static_p && !nonloc_p)
    أرجع;

  /* If we may be in an unevaluated context, delay the decision.  */
  إذا (in_sizeof || in_typeof || in_countof || in_generic)
    أرجع record_maybe_used_decl (ref, address);

  إذا (static_p)
    C_DECL_USED (ref) = 1;

  إذا (nonloc_p && (VAR_OR_FUNCTION_DECL_P (ref)
		   || شجرة_CODE (ref) == PARM_DECL))
    DECL_NONLOCAL (ref) = 1;

  /* Nothing to do anymore.  */
  إذا (!nonloc_p || C_FUNC_NONLOCAL_CONTEXT (current_function_decl))
    أرجع;

  /* Filter out the cases where referencing a non-local variable does not
     require a non-local context passed via the static chain.  */
  إذا (!c_type_variably_modified_p (شجرة_TYPE (ref)))
    بدل (شجرة_CODE (ref))
      {
      حالة FUNCTION_DECL:
	/* Use of another local function that requires no context is ok.  */
	إذا (!C_FUNC_NONLOCAL_CONTEXT (ref) && DECL_INITIAL (ref))
	  أرجع;
	اكسر;
      حالة VAR_DECL:
	/* Static variables and constexpr are ok, but for the later only
	   when the address is not taken.  */
	إذا (شجرة_STATIC (ref) || (C_DECL_DECLARED_CONSTEXPR (ref) && !address))
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
  لكل (شجرة cont = current_function_decl; cont; cont = DECL_CONTEXT (cont))
    {
      إذا (cont == DECL_CONTEXT (ref))
	اكسر;

      /* There should not be any other type of context used for function
	 except TRANSLATION_UNIT_DECL which we should be able to reach.  */
      gcc_checking_assert (شجرة_CODE (cont) == FUNCTION_DECL);

      إذا (شجرة_CODE (cont) == FUNCTION_DECL)
	C_FUNC_NONLOCAL_CONTEXT (cont) = 1;
    }
}


/* Build an external reference to identifier ID.  FUN indicates
   whether this will be used for a function call.  LOC is the source
   location of the identifier.  This sets *TYPE to the type of the
   identifier, which is not the same as the type of the returned value
   for CONST_DECLs defined as enum constants.  If the type of the
   identifier is not available, *TYPE is set to NULL.  */
شجرة
build_external_ref (location_t loc, شجرة id, منطقي fun, شجرة *type)
{
  شجرة ref;
  شجرة decl = lookup_name (id);

  /* In Objective-C, an instance variable (ivar) may be preferred to
     whatever lookup_name() found.  */
  decl = objc_lookup_ivar (decl, id);

  *type = عدم;
  إذا (decl && decl != error_mark_عقدة)
    {
      ref = decl;
      *type = شجرة_TYPE (ref);
      إذا (DECL_P (decl) && C_DECL_UNDERSPECIFIED (decl))
	error_at (loc, "underspecified %qD referenced in its initializer",
		  decl);
    }
  وإلا إذا (fun)
    /* Implicit function declaration.  */
    ref = implicitly_declare (loc, id);
  وإلا إذا (decl == error_mark_عقدة)
    /* Don't complain about something that's already been
       complained about.  */
    أرجع error_mark_عقدة;
  وإلا
    {
      undeclared_variable (loc, id);
      أرجع error_mark_عقدة;
    }

  /* For an OpenMP map clause, we can get better diagnostics for decls with
     unmappable types if we return the decl with an error_mark_node type,
     rather than returning error_mark_node for the decl itself.  */
  إذا (شجرة_TYPE (ref) == error_mark_عقدة
      && !c_omp_array_section_p)
    أرجع error_mark_عقدة;

  إذا (شجرة_UNAVAILABLE (ref))
    error_unavailable_use (ref, NULL_شجرة);
  وإلا إذا (شجرة_DEPRECATED (ref))
    warn_deprecated_use (ref, NULL_شجرة);

  /* Recursive call does not count as usage.  */
  إذا (ref != current_function_decl)
    {
      شجرة_USED (ref) = 1;
    }

  mark_decl_used (ref, خطأ);

  إذا (شجرة_CODE (ref) == CONST_DECL)
    {
      used_types_أدرج (شجرة_TYPE (ref));

      إذا (warn_cxx_compat
	  && شجرة_CODE (شجرة_TYPE (ref)) == ENUMERAL_TYPE
	  && C_TYPE_DEFINED_IN_STRUCT (شجرة_TYPE (ref)))
	{
	  warning_at (loc, OPT_Wc___compat,
		      "enum constant defined in struct or union "
		      "is not visible in C++");
	  inform (DECL_SOURCE_LOCATION (ref), "enum constant defined here");
	}

      ref = DECL_INITIAL (ref);
      شجرة_CONSTANT (ref) = 1;
    }
  /* C99 6.7.4p3: An inline definition of a function with external
     linkage ... shall not contain a reference to an identifier with
     internal linkage.  */
  وإلا إذا (current_function_decl != NULL_شجرة
	   && DECL_DECLARED_INLINE_P (current_function_decl)
	   && DECL_EXTERNAL (current_function_decl)
	   && VAR_OR_FUNCTION_DECL_P (ref)
	   && (!VAR_P (ref) || شجرة_STATIC (ref))
	   && ! شجرة_PUBLIC (ref)
	   && DECL_CONTEXT (ref) != current_function_decl)
    record_inline_static (loc, current_function_decl, ref,
			  csi_internal);

  أرجع ref;
}

ساكن بنية maybe_used_decl *maybe_used_decls;

/* Record that DECL, a reference seen inside sizeof or typeof or _Countof or
   _Generic, might be used if the operand of sizeof is a VLA type or the
   operand of typeof is a variably modified type or the operand of _Countof has
   a variable number of elements or the operand of _Generic is the one selected
   as the result.  */

ساكن فراغ
record_maybe_used_decl (شجرة decl, منطقي address)
{
  بنية maybe_used_decl *t = XOBNEW (&parser_obstack, بنية maybe_used_decl);
  t->decl = decl;
  t->level = in_sizeof + in_typeof + in_countof + in_generic;
  t->address = address;
  t->next = maybe_used_decls;
  maybe_used_decls = t;
}

/* Pop the stack of decls possibly used inside sizeof or typeof or _Countof or
   _Generic.  If USED is false, just discard them.  If it is true, mark them
   used (if no longer inside sizeof or typeof or _Countof or _Generic) or move
   them to the next level up (if still inside sizeof or typeof or _Countof or
   _Generic).  */

فراغ
اسحب_maybe_used (منطقي used)
{
  بنية maybe_used_decl *p = maybe_used_decls;
  صحيح cur_level = in_sizeof + in_typeof + in_countof + in_generic;
  طالما (p && p->level > cur_level)
    {
      إذا (used)
	{
	  إذا (cur_level == 0)
	    mark_decl_used (p->decl, p->address);
	  وإلا
	    p->level = cur_level;
	}
      p = p->next;
    }
  إذا (!used || cur_level == 0)
    maybe_used_decls = p;
}

/* Pop the stack of decls possibly used inside sizeof or typeof or _Countof or
   _Generic, without acting on them, and return the pointer to the previous top
   of the stack.  This for use at the end of a default generic association when
   it is not yet known whether the expression is used.  If it later turns out
   the expression is used (or treated as used before C23), restore_maybe_used
   should be called on the return value followed by pop_maybe_used (true);
   otherwise, the return value can be discarded.  */

بنية maybe_used_decl *
save_maybe_used ()
{
  بنية maybe_used_decl *p = maybe_used_decls, *orig = p;
  صحيح cur_level = in_sizeof + in_typeof + in_countof + in_generic;
  طالما (p && p->level > cur_level)
    p = p->next;
  maybe_used_decls = p;
  أرجع orig;
}

/* Restore the stack of decls possibly used inside sizeof or typeof or _Countof
   or _Generic returned by save_maybe_used.  It is required that the stack is
   at exactly the point where it was left by save_maybe_used.  */

فراغ
restore_maybe_used (بنية maybe_used_decl *مكدس)
{
  maybe_used_decls = مكدس;
}

/* Return the result of sizeof applied to EXPR.  */

بنية c_تعبير
c_تعبير_sizeof_تعبير (location_t loc, بنية c_تعبير تعبير)
{
  بنية c_تعبير ret;
  إذا (تعبير.قيمة == error_mark_عقدة)
    {
      ret.قيمة = error_mark_عقدة;
      ret.original_code = ERROR_MARK;
      ret.original_type = عدم;
      ret.m_decimal = 0;
      اسحب_maybe_used (خطأ);
    }
  وإلا
    {
      منطقي تعبير_const_operands = true;

      إذا (شجرة_CODE (تعبير.قيمة) == PARM_DECL
	  && C_ARRAY_PARAMETER (تعبير.قيمة))
	{
	  auto_diagnostic_group d;
	  إذا (warning_at (loc, OPT_Wsizeof_array_argument,
			  "%<sizeof%> on array function parameter %qE will "
			  "return size of %qT", تعبير.قيمة,
			  شجرة_TYPE (تعبير.قيمة)))
	    inform (DECL_SOURCE_LOCATION (تعبير.قيمة), "declared here");
	}
      شجرة folded_تعبير = c_fully_fold (تعبير.قيمة, require_constant_قيمة,
				       &تعبير_const_operands);
      ret.قيمة = c_sizeof (loc, شجرة_TYPE (folded_تعبير));
      c_last_sizeof_arg = تعبير.قيمة;
      c_last_sizeof_loc = loc;
      ret.original_code = SIZEOF_تعبير;
      ret.original_type = عدم;
      ret.m_decimal = 0;
      إذا (C_TYPE_VARIABLE_SIZE (شجرة_TYPE (folded_تعبير)))
	{
	  /* sizeof is evaluated when given a vla (C99 6.5.3.4p2).  */
	  ret.قيمة = build2 (C_MAYBE_CONST_تعبير, شجرة_TYPE (ret.قيمة),
			      folded_تعبير, ret.قيمة);
	  C_MAYBE_CONST_تعبير_NON_CONST (ret.قيمة) = !تعبير_const_operands;
	  SET_تعبير_LOCATION (ret.قيمة, loc);
	}
      اسحب_maybe_used (C_TYPE_VARIABLE_SIZE (شجرة_TYPE (folded_تعبير)));
    }
  أرجع ret;
}

/* Return the result of sizeof applied to T, a structure for the type
   name passed to sizeof (rather than the type itself).  LOC is the
   location of the original expression.  */

بنية c_تعبير
c_تعبير_sizeof_type (location_t loc, بنية c_type_name *t)
{
  شجرة type;
  بنية c_تعبير ret;
  شجرة type_تعبير = NULL_شجرة;
  منطقي type_تعبير_const = true;
  type = groktypename (t, &type_تعبير, &type_تعبير_const);
  ret.قيمة = c_sizeof (loc, type);
  c_last_sizeof_arg = type;
  c_last_sizeof_loc = loc;
  ret.original_code = SIZEOF_تعبير;
  ret.original_type = عدم;
  ret.m_decimal = 0;
  إذا (type == error_mark_عقدة)
    {
      ret.قيمة = error_mark_عقدة;
      ret.original_code = ERROR_MARK;
    }
  وإلا
  إذا ((type_تعبير || شجرة_CODE (ret.قيمة) == INTEGER_CST)
      && C_TYPE_VARIABLE_SIZE (type))
    {
      /* If the type is a [*] array, it is a VLA but is represented as
	 having a size of zero.  In such a case we must ensure that
	 the result of sizeof does not get folded to a constant by
	 c_fully_fold, because if the size is evaluated the result is
	 not constant and so constraints on zero or negative size
	 arrays must not be applied when this sizeof call is inside
	 another array declarator.  */
      إذا (!type_تعبير)
	type_تعبير = integer_zero_عقدة;
      ret.قيمة = build2 (C_MAYBE_CONST_تعبير, شجرة_TYPE (ret.قيمة),
			  type_تعبير, ret.قيمة);
      C_MAYBE_CONST_تعبير_NON_CONST (ret.قيمة) = !type_تعبير_const;
    }
  اسحب_maybe_used (type != error_mark_عقدة
		  ? C_TYPE_VARIABLE_SIZE (type) : خطأ);
  أرجع ret;
}

ساكن منطقي
قمة_array_vla_p (const_شجرة type)
{
  إذا (شجرة_CODE (type) != ARRAY_TYPE)
    أرجع خطأ;

  شجرة d = TYPE_DOMAIN (type);

  إذا (!d)
    أرجع خطأ;
  إذا (!TYPE_MAX_قيمة (d))
    أرجع خطأ;

  أرجع شجرة_CODE (TYPE_MAX_قيمة (d)) != INTEGER_CST
	 || شجرة_CODE (TYPE_MIN_قيمة (d)) != INTEGER_CST;
}

/* Return the result of countof applied to EXPR.  */

بنية c_تعبير
c_تعبير_countof_تعبير (location_t loc, بنية c_تعبير تعبير)
{
  بنية c_تعبير ret;
  إذا (تعبير.قيمة == error_mark_عقدة)
    {
      ret.قيمة = error_mark_عقدة;
      ret.original_code = ERROR_MARK;
      ret.original_type = عدم;
      ret.m_decimal = 0;
      اسحب_maybe_used (خطأ);
    }
  وإلا
    {
      منطقي تعبير_const_operands = true;

      شجرة folded_تعبير = c_fully_fold (تعبير.قيمة, require_constant_قيمة,
				       &تعبير_const_operands);
      ret.قيمة = c_countof_type (loc, شجرة_TYPE (folded_تعبير));
      c_last_sizeof_arg = تعبير.قيمة;
      c_last_sizeof_loc = loc;
      ret.original_code = COUNTOF_تعبير;
      ret.original_type = عدم;
      ret.m_decimal = 0;
      إذا (قمة_array_vla_p (شجرة_TYPE (folded_تعبير)))
	{
	  /* countof is evaluated when given a vla.  */
	  ret.قيمة = build2 (C_MAYBE_CONST_تعبير, شجرة_TYPE (ret.قيمة),
			      folded_تعبير, ret.قيمة);
	  C_MAYBE_CONST_تعبير_NON_CONST (ret.قيمة) = !تعبير_const_operands;
	  SET_تعبير_LOCATION (ret.قيمة, loc);
	}
      اسحب_maybe_used (قمة_array_vla_p (شجرة_TYPE (folded_تعبير)));
    }
  أرجع ret;
}

/* Return the result of countof applied to T, a structure for the type
   name passed to countof (rather than the type itself).  LOC is the
   location of the original expression.  */

بنية c_تعبير
c_تعبير_countof_type (location_t loc, بنية c_type_name *t)
{
  شجرة type;
  بنية c_تعبير ret;
  شجرة type_تعبير = NULL_شجرة;
  منطقي type_تعبير_const = true;
  type = groktypename (t, &type_تعبير, &type_تعبير_const);
  ret.قيمة = c_countof_type (loc, type);
  c_last_sizeof_arg = type;
  c_last_sizeof_loc = loc;
  ret.original_code = COUNTOF_تعبير;
  ret.original_type = عدم;
  ret.m_decimal = 0;
  إذا (type == error_mark_عقدة)
    {
      ret.قيمة = error_mark_عقدة;
      ret.original_code = ERROR_MARK;
    }
  وإلا
  إذا ((type_تعبير || شجرة_CODE (ret.قيمة) == INTEGER_CST)
      && قمة_array_vla_p (type))
    {
      /* If the type is a [*] array, it is a VLA but is represented as
	 having a size of zero.  In such a case we must ensure that
	 the result of countof does not get folded to a constant by
	 c_fully_fold, because if the number of elements is evaluated
	 the result is not constant and so
	 constraints on zero or negative size arrays must not be applied
	 when this countof call is inside another array declarator.  */
      إذا (!type_تعبير)
	type_تعبير = integer_zero_عقدة;
      ret.قيمة = build2 (C_MAYBE_CONST_تعبير, شجرة_TYPE (ret.قيمة),
			  type_تعبير, ret.قيمة);
      C_MAYBE_CONST_تعبير_NON_CONST (ret.قيمة) = !type_تعبير_const;
    }
  اسحب_maybe_used (type != error_mark_عقدة ? قمة_array_vla_p (type) : خطأ);
  أرجع ret;
}

/* Return the result of maxof applied to T, a structure for the type
   name passed to maxof (rather than the type itself).  LOC is the
   location of the original expression.  */

بنية c_تعبير
c_تعبير_maxof_type (location_t loc, بنية c_type_name *t)
{
  شجرة type;
  بنية c_تعبير ret;
  شجرة type_تعبير = NULL_شجرة;
  منطقي type_تعبير_const = true;
  type = groktypename (t, &type_تعبير, &type_تعبير_const);
  ret.قيمة = c_maxof_type (loc, type);
  c_last_sizeof_arg = type;
  c_last_sizeof_loc = loc;
  ret.original_code = MAXOF_تعبير;
  ret.original_type = عدم;
  ret.m_decimal = 0;
  إذا (type == error_mark_عقدة)
    {
      ret.قيمة = error_mark_عقدة;
      ret.original_code = ERROR_MARK;
    }
  اسحب_maybe_used (type != error_mark_عقدة);
  أرجع ret;
}

/* Return the result of minof applied to T, a structure for the type
   name passed to minof (rather than the type itself).  LOC is the
   location of the original expression.  */

بنية c_تعبير
c_تعبير_minof_type (location_t loc, بنية c_type_name *t)
{
  شجرة type;
  بنية c_تعبير ret;
  شجرة type_تعبير = NULL_شجرة;
  منطقي type_تعبير_const = true;
  type = groktypename (t, &type_تعبير, &type_تعبير_const);
  ret.قيمة = c_minof_type (loc, type);
  c_last_sizeof_arg = type;
  c_last_sizeof_loc = loc;
  ret.original_code = MINOF_تعبير;
  ret.original_type = عدم;
  ret.m_decimal = 0;
  إذا (type == error_mark_عقدة)
    {
      ret.قيمة = error_mark_عقدة;
      ret.original_code = ERROR_MARK;
    }
  اسحب_maybe_used (type != error_mark_عقدة);
  أرجع ret;
}

/* Build a function call to function FUNCTION with parameters PARAMS.
   The function call is at LOC.
   PARAMS is a list--a chain of TREE_LIST nodes--in which the
   TREE_VALUE of each node is a parameter-expression.
   FUNCTION's data type may be a function type or a pointer-to-function.  */

شجرة
build_function_call (location_t loc, شجرة function, شجرة params)
{
  vec<شجرة, va_gc> *v;
  شجرة ret;

  vec_alloc (v, list_length (params));
  لكل (; params; params = شجرة_CHAIN (params))
    v->quick_ادفع (شجرة_قيمة (params));
  ret = c_build_function_call_vec (loc, vNULL, function, v, عدم);
  vec_free (v);
  أرجع ret;
}

/* Give a note about the location of the declaration of DECL,
   or, failing that, a pertinent declaration for FUNCTION_EXPR.  */

ساكن فراغ
inform_declaration (شجرة decl, شجرة function_تعبير)
{
  إذا (decl && (شجرة_CODE (decl) != FUNCTION_DECL
	       || !DECL_IS_UNDECLARED_BUILTIN (decl)))
    inform (DECL_SOURCE_LOCATION (decl), "declared here");
  وإلا إذا (function_تعبير)
    بدل (شجرة_CODE (function_تعبير))
      {
      افتراضي:
	اكسر;
      حالة COMPONENT_REF:
	/* Show the decl of the pertinent field (e.g. for callback
	   fields in a struct.  */
	{
	  شجرة field_decl = شجرة_OPERAND (function_تعبير, 1);
	  إذا (location_t loc = DECL_SOURCE_LOCATION (field_decl))
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

شجرة
build_function_call_vec (location_t loc, vec<location_t> arg_loc,
			 شجرة function, vec<شجرة, va_gc> *params,
			 vec<شجرة, va_gc> *origtypes, شجرة orig_fundecl)
{
  شجرة fntype, fundecl = NULL_شجرة;
  شجرة name = NULL_شجرة, result;
  شجرة tem;
  صحيح nargs;
  شجرة *argarray;


  /* Strip NON_LVALUE_EXPRs, etc., since we aren't using as an lvalue.  */
  STRIP_TYPE_NOPS (function);

  /* Convert anything with function type to a pointer-to-function.  */
  إذا (شجرة_CODE (function) == FUNCTION_DECL)
    {
      name = DECL_NAME (function);

      إذا (flag_tm)
	tm_malloc_replacement (function);
      fundecl = function;
      إذا (!orig_fundecl)
	orig_fundecl = fundecl;
      /* Atomic functions have type checking/casting already done.  They are
	 often rewritten and don't match the original parameter list.  */
      إذا (name && startswith (IDENTIFIER_POINTER (name), "__atomic_"))
        origtypes = عدم;
    }
  إذا (شجرة_CODE (شجرة_TYPE (function)) == FUNCTION_TYPE)
    function = function_to_pointer_conversion (loc, function);

  /* For Objective-C, convert any calls via a cast to OBJC_TYPE_REF
     expressions, like those used for ObjC messenger dispatches.  */
  إذا (params && !params->is_empty ())
    function = objc_rewrite_function_call (function, (*params)[0]);

  function = c_fully_fold (function, خطأ, عدم);

  fntype = شجرة_TYPE (function);

  إذا (شجرة_CODE (fntype) == ERROR_MARK)
    أرجع error_mark_عقدة;

  إذا (!(شجرة_CODE (fntype) == POINTER_TYPE
	&& شجرة_CODE (شجرة_TYPE (fntype)) == FUNCTION_TYPE))
    {
      إذا (!flag_diagnostics_show_caret && !STATEMENT_CLASS_P (function))
	error_at (loc,
		  "called object %qE is not a function or function pointer",
		  function);
      وإلا إذا (DECL_P (function))
	{
	  auto_diagnostic_group d;
	  error_at (loc,
		    "called object %qD is not a function or function pointer",
		    function);
	  inform_declaration (function, NULL_شجرة);
	}
      وإلا
	error_at (loc,
		  "called object is not a function or function pointer");
      أرجع error_mark_عقدة;
    }

  إذا (fundecl && شجرة_THIS_VOLATILE (fundecl))
    current_function_returns_abnormally = 1;

  /* fntype now gets the type of function pointed to.  */
  fntype = شجرة_TYPE (fntype);
  شجرة return_type = شجرة_TYPE (fntype);

  /* Convert the parameters to the types declared in the
     function prototype, or apply default promotions.  */

  nargs = convert_arguments (loc, arg_loc, fntype, params,
			     origtypes, function, fundecl);
  إذا (nargs < 0)
    أرجع error_mark_عقدة;

  /* Check that the function is called through a compatible prototype.
     If it is not, warn.  */
  إذا (CONVERT_تعبير_P (function)
      && شجرة_CODE (tem = شجرة_OPERAND (function, 0)) == ADDR_تعبير
      && شجرة_CODE (tem = شجرة_OPERAND (tem, 0)) == FUNCTION_DECL
      && !comptypes (fntype, شجرة_TYPE (tem)))
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

  argarray = vec_safe_address (params);

  /* Check that arguments to builtin functions match the expectations.  */
  إذا (fundecl
      && fndecl_built_in_p (fundecl)
      && !check_builtin_function_arguments (loc, arg_loc, fundecl,
					    orig_fundecl, nargs, argarray))
    أرجع error_mark_عقدة;

  /* Check that the arguments to the function are valid.  */
  منطقي warned_p = check_function_arguments (loc, fundecl, fntype,
					    nargs, argarray, &arg_loc,
					    comptypes);

  إذا (TYPE_QUALS (return_type) != TYPE_UNQUALIFIED
      && !VOID_TYPE_P (return_type))
    return_type = c_build_qualified_type (return_type, TYPE_UNQUALIFIED);
  إذا (name != NULL_شجرة
      && startswith (IDENTIFIER_POINTER (name), "__builtin_"))
    {
      إذا (require_constant_قيمة)
	result
	  = fold_build_call_array_initializer_loc (loc, return_type,
						   function, nargs, argarray);
      وإلا
	result = fold_build_call_array_loc (loc, return_type,
					    function, nargs, argarray);
      إذا (شجرة_CODE (result) == NOP_تعبير
	  && شجرة_CODE (شجرة_OPERAND (result, 0)) == INTEGER_CST)
	STRIP_TYPE_NOPS (result);
    }
  وإلا
    result = build_call_array_loc (loc, return_type,
				   function, nargs, argarray);
  /* If -Wnonnull warning has been diagnosed, avoid diagnosing it again
     later.  */
  إذا (warned_p && شجرة_CODE (result) == CALL_تعبير)
    suppress_warning (result, OPT_Wnonnull);

  /* In this improbable scenario, a nested function returns a VM type.
     Create a TARGET_EXPR so that the call always has a LHS, much as
     what the C++ FE does for functions returning non-PODs.  */
  إذا (c_type_variably_modified_p (شجرة_TYPE (fntype)))
    {
      شجرة tmp = create_tmp_var_raw (شجرة_TYPE (fntype));
      result = build4 (TARGET_تعبير, شجرة_TYPE (fntype), tmp, result,
		       NULL_شجرة, NULL_شجرة);
    }

  إذا (VOID_TYPE_P (شجرة_TYPE (result)))
    {
      إذا (TYPE_QUALS (شجرة_TYPE (result)) != TYPE_UNQUALIFIED)
	pedwarn (loc, 0,
		 "function with qualified void return type called");
      أرجع result;
    }
  أرجع require_complete_type (loc, result);
}

/* Like build_function_call_vec, but call also resolve_overloaded_builtin.  */

شجرة
c_build_function_call_vec (location_t loc, ثابت vec<location_t> &arg_loc,
			   شجرة function, vec<شجرة, va_gc> *params,
			   vec<شجرة, va_gc> *origtypes)
{
  /* Strip NON_LVALUE_EXPRs, etc., since we aren't using as an lvalue.  */
  STRIP_TYPE_NOPS (function);

  /* Convert anything with function type to a pointer-to-function.  */
  إذا (شجرة_CODE (function) == FUNCTION_DECL)
    {
      /* Implement type-directed function overloading for builtins.
	 resolve_overloaded_builtin and targetm.resolve_overloaded_builtin
	 handle all the type checking.  The result is a complete expression
	 that implements this function call.  */
      شجرة tem = resolve_overloaded_builtin (loc, function, params);
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

ساكن شجرة
convert_argument (location_t ploc, شجرة function, شجرة fundecl,
		  شجرة type, شجرة origtype, شجرة val, شجرة valtype,
		  منطقي npc, شجرة rname, صحيح parmnum, صحيح argnum,
		  منطقي excess_precision, صحيح warnopt)
{
  /* Formal parm type is specified by a function prototype.  */

  إذا (type == error_mark_عقدة || !COMPLETE_TYPE_P (type))
    {
      error_at (ploc, "type of formal parameter %d is incomplete",
		parmnum + 1);
      أرجع error_mark_عقدة;
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
	  && شجرة_CODE (valtype) == COMPLEX_TYPE)
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as integer rather "
		    "than complex due to prototype",
		    argnum, rname);
      وإلا إذا (شجرة_CODE (type) == COMPLEX_TYPE
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
      وإلا إذا (شجرة_CODE (type) == COMPLEX_TYPE
	       && INTEGRAL_TYPE_P (valtype))
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as complex rather "
		    "than integer due to prototype",
		    argnum, rname);
      وإلا إذا (SCALAR_FLOAT_TYPE_P (type)
	       && شجرة_CODE (valtype) == COMPLEX_TYPE)
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
	  unsigned صحيح formal_prec = TYPE_PRECISION (type);

	  /* Warn if any argument is passed as `float',
	     since without a prototype it would be `double'.  */
	  إذا (formal_prec == TYPE_PRECISION (float_type_عقدة)
	      && type != dfloat32_type_عقدة)
	    warning_at (ploc, 0,
			"passing argument %d of %qE as %<float%> "
			"rather than %<double%> due to prototype",
			argnum, rname);

	  /* Warn if mismatch between argument and prototype
	     for decimal float types.  Warn of conversions with
	     binary float types and of precision narrowing due to
	     prototype.  */
	  وإلا إذا (type != valtype
		   && (type == dfloat32_type_عقدة
		       || type == dfloat64_type_عقدة
		       || type == dfloat128_type_عقدة
		       || valtype == dfloat32_type_عقدة
		       || valtype == dfloat64_type_عقدة
		       || valtype == dfloat128_type_عقدة)
		   && (formal_prec
		       <= TYPE_PRECISION (valtype)
		       || (type == dfloat128_type_عقدة
			   && (valtype
			       != dfloat64_type_عقدة
			       && (valtype
				   != dfloat32_type_عقدة)))
		       || (type == dfloat64_type_عقدة
			   && (valtype
			       != dfloat32_type_عقدة))))
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
	  unsigned صحيح formal_prec = TYPE_PRECISION (type);
	  شجرة would_have_been = default_conversion (val);
	  شجرة type1 = شجرة_TYPE (would_have_been);

	  إذا (val == error_mark_عقدة)
	    /* VAL could have been of incomplete type.  */;
	  وإلا إذا (شجرة_CODE (type) == ENUMERAL_TYPE
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
	  وإلا إذا (شجرة_CODE (type) == ENUMERAL_TYPE)
	    ;
	  وإلا إذا (شجرة_CODE (val) == INTEGER_CST
		   && int_fits_type_p (val, type))
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
    val = build1 (EXCESS_PRECISION_تعبير, valtype, val);

  شجرة parmval = convert_for_assignment (ploc, ploc, type,
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
convert_arguments (location_t loc, vec<location_t> arg_loc, شجرة fntype,
		   vec<شجرة, va_gc> *قيم, vec<شجرة, va_gc> *origtypes,
		   شجرة function, شجرة fundecl)
{
  شجرة typelist = TYPE_ARG_TYPES (fntype);
  unsigned صحيح parmnum;
  منطقي error_وسائط = خطأ;
  ثابت منطقي type_generic = fundecl
    && lookup_attribute ("type generic", TYPE_ATTRIBUTES (شجرة_TYPE (fundecl)));
  منطقي type_generic_remove_excess_precision = خطأ;
  منطقي type_generic_overflow_p = خطأ;
  منطقي type_generic_bit_query = خطأ;
  شجرة selector;

  /* Change pointer to function to the function itself for
     diagnostics.  */
  إذا (شجرة_CODE (function) == ADDR_تعبير
      && شجرة_CODE (شجرة_OPERAND (function, 0)) == FUNCTION_DECL)
    function = شجرة_OPERAND (function, 0);

  /* Handle an ObjC selector specially for diagnostics.  */
  selector = objc_message_selector ();

  /* For a call to a built-in function declared without a prototype,
     set to the built-in function's argument list.  */
  شجرة builtin_typelist = NULL_شجرة;

  /* For type-generic built-in functions, determine whether excess
     precision should be removed (classification) or not
     (comparison).  */
  إذا (fundecl
      && fndecl_built_in_p (fundecl, BUILT_IN_NORMAL))
    {
      built_in_function code = DECL_FUNCTION_CODE (fundecl);
      إذا (C_DECL_BUILTIN_PROTOTYPE (fundecl))
	{
	  /* For a call to a built-in function declared without a prototype
	     use the types of the parameters of the internal built-in to
	     match those of the arguments to.  */
	  إذا (شجرة bdecl = builtin_decl_explicit (code))
	    builtin_typelist = TYPE_ARG_TYPES (شجرة_TYPE (bdecl));
	}

      /* For type-generic built-in functions, determine whether excess
	 precision should be removed (classification) or not
	 (comparison).  */
      إذا (type_generic)
	بدل (code)
	  {
	  حالة BUILT_IN_ISFINITE:
	  حالة BUILT_IN_ISINF:
	  حالة BUILT_IN_ISINF_SIGN:
	  حالة BUILT_IN_ISNAN:
	  حالة BUILT_IN_ISNORMAL:
	  حالة BUILT_IN_ISSIGNALING:
	  حالة BUILT_IN_FPCLASSIFY:
	    type_generic_remove_excess_precision = true;
	    اكسر;

	  حالة BUILT_IN_ADD_OVERFLOW_P:
	  حالة BUILT_IN_SUB_OVERFLOW_P:
	  حالة BUILT_IN_MUL_OVERFLOW_P:
	    /* The last argument of these type-generic builtins
	       should not be promoted.  */
	    type_generic_overflow_p = true;
	    اكسر;

	  حالة BUILT_IN_CLZG:
	  حالة BUILT_IN_CTZG:
	  حالة BUILT_IN_CLRSBG:
	  حالة BUILT_IN_FFSG:
	  حالة BUILT_IN_PARITYG:
	  حالة BUILT_IN_POPCOUNTG:
	    /* The first argument of these type-generic builtins
	       should not be promoted.  */
	    type_generic_bit_query = true;
	    اكسر;

	  افتراضي:
	    اكسر;
	  }
    }

  /* Scan the given expressions (VALUES) and types (TYPELIST), producing
     individual converted arguments.  */

  شجرة typetail, builtin_typetail, val;
  لكل (typetail = typelist,
	 builtin_typetail = builtin_typelist,
	 parmnum = 0;
       قيم && قيم->iterate (parmnum, &val);
       ++parmnum)
    {
      /* The type of the function parameter (if it was declared with one).  */
      شجرة type = typetail ? شجرة_قيمة (typetail) : NULL_شجرة;
      /* The type of the built-in function parameter (if the function
	 is a built-in).  Used to detect type incompatibilities in
	 calls to built-ins declared without a prototype.  */
      شجرة builtin_type = (builtin_typetail
			   ? شجرة_قيمة (builtin_typetail) : NULL_شجرة);
      /* The original type of the argument being passed to the function.  */
      شجرة valtype = شجرة_TYPE (val);
      /* The called function (or function selector in Objective C).  */
      شجرة rname = function;
      صحيح argnum = parmnum + 1;
      ثابت حرف *invalid_func_diag;
      /* Set for EXCESS_PRECISION_EXPR arguments.  */
      منطقي excess_precision = خطأ;
      /* The value of the argument after conversion to the type
	 of the function parameter it is passed to.  */
      شجرة parmval;
      /* Some __atomic_* builtins have additional hidden argument at
	 position 0.  */
      location_t ploc
	= !arg_loc.is_empty () && قيم->length () == arg_loc.length ()
	  ? expansion_point_location_if_in_system_header (arg_loc[parmnum])
	  : مدخل_location;

      إذا (type == void_type_عقدة)
	{
	  auto_diagnostic_group d;
	  صحيح رقم_expected = parmnum;
	  صحيح رقم_actual = قيم->length ();
	  gcc_rich_location rich_loc (loc);
	  إذا (ploc != مدخل_location)
	    rich_loc.add_range (ploc);
	  إذا (selector)
	    error_at (&rich_loc,
		      "too many arguments to method %qE; expected %i, have %i",
		      selector, رقم_expected, رقم_actual);
	  وإلا
	    error_at (&rich_loc,
		      "too many arguments to function %qE; expected %i, have %i",
		      function, رقم_expected, رقم_actual);
	  inform_declaration (fundecl, function);
	  أرجع error_وسائط ? -1 : (صحيح) parmnum;
	}

      إذا (builtin_type == void_type_عقدة)
	{
	  auto_diagnostic_group d;
	  إذا (warning_at (loc, OPT_Wbuiltin_declaration_mismatch,
			  "too many arguments to built-in function %qE "
			  "expecting %d", function, parmnum))
	    inform_declaration (fundecl, function);
	  builtin_typetail = NULL_شجرة;
	}

      إذا (!typetail && parmnum == 0 && !TYPE_NO_NAMED_وسائط_STDARG_P (fntype)
	  && !(fundecl && fndecl_built_in_p (fundecl)))
	{
	  auto_diagnostic_group d;
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
      منطقي npc = null_pointer_constant_p (val);

      /* If there is excess precision and a prototype, convert once to
	 the required type rather than converting via the semantic
	 type.  Likewise without a prototype a float value represented
	 as long double should be converted once to double.  But for
	 type-generic classification functions excess precision must
	 be removed here.  */
      إذا (شجرة_CODE (val) == EXCESS_PRECISION_تعبير
	  && (type || !type_generic || !type_generic_remove_excess_precision))
	{
	  val = شجرة_OPERAND (val, 0);
	  excess_precision = true;
	}
      val = c_fully_fold (val, خطأ, عدم);
      STRIP_TYPE_NOPS (val);

      val = require_complete_type (ploc, val);

      /* Some floating-point arguments must be promoted to double when
	 no type is specified by a prototype.  This applies to
	 arguments of type float, and to architecture-specific types
	 (ARM __fp16), but not to _FloatN or _FloatNx types.  */
      منطقي promote_float_arg = خطأ;
      إذا (type == NULL_شجرة
	  && شجرة_CODE (valtype) == REAL_TYPE
	  && (TYPE_PRECISION (valtype)
	      <= TYPE_PRECISION (double_type_عقدة))
	  && TYPE_MAIN_VARIANT (valtype) != double_type_عقدة
	  && TYPE_MAIN_VARIANT (valtype) != long_double_type_عقدة
	  && !DECIMAL_FLOAT_MODE_P (TYPE_MODE (valtype)))
	{
	  /* Promote this argument, unless it has a _FloatN or
	     _FloatNx type.  */
	  promote_float_arg = true;
	  لكل (صحيح i = 0; i < رقم_FLOATN_NX_TYPES; i++)
	    إذا (TYPE_MAIN_VARIANT (valtype) == FLOATN_NX_TYPE_عقدة (i))
	      {
		promote_float_arg = خطأ;
		اكسر;
	      }
	  /* Don't promote __bf16 either.  */
	  إذا (TYPE_MAIN_VARIANT (valtype) == bfloat16_type_عقدة)
	    promote_float_arg = خطأ;
	}

      إذا (type != NULL_شجرة)
	{
	  شجرة origtype = (!origtypes) ? NULL_شجرة : (*origtypes)[parmnum];
	  parmval = convert_argument (ploc, function, fundecl, type, origtype,
				      val, valtype, npc, rname, parmnum, argnum,
				      excess_precision, 0);
	}
      /* A NULLPTR type is just a nullptr always.  */
      وإلا إذا (شجرة_CODE (شجرة_TYPE (val)) == NULLPTR_TYPE)
	parmval = omit_one_operand_loc (ploc, شجرة_TYPE (val), nullptr_عقدة, val);
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
			    valtype, double_type_عقدة);
	      parmval = convert (double_type_عقدة, val);
	    }
	}
      وإلا إذا ((excess_precision && !type_generic)
	       || (type_generic_overflow_p && parmnum == 2)
	       || (type_generic_bit_query && parmnum == 0))
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
      وإلا إذا (شجرة_CODE (val) == ADDR_تعبير && reject_gcc_builtin (val))
	{
	  أرجع -1;
	}
      وإلا
	/* Convert `short' and `char' to full-size `int'.  */
	parmval = default_conversion (val);

      (*قيم)[parmnum] = parmval;
      إذا (parmval == error_mark_عقدة)
	error_وسائط = true;

      إذا (!type && builtin_type && شجرة_CODE (builtin_type) != VOID_TYPE)
	{
	  /* For a call to a built-in function declared without a prototype,
	     perform the conversions from the argument to the expected type
	     but issue warnings rather than errors for any mismatches.
	     Ignore the converted argument and use the PARMVAL obtained
	     above by applying default conversions instead.  */
	  شجرة origtype = (!origtypes) ? NULL_شجرة : (*origtypes)[parmnum];
	  convert_argument (ploc, function, fundecl, builtin_type, origtype,
			    val, valtype, npc, rname, parmnum, argnum,
			    excess_precision,
			    OPT_Wbuiltin_declaration_mismatch);
	}

      إذا (typetail)
	typetail = شجرة_CHAIN (typetail);

      إذا (builtin_typetail)
	builtin_typetail = شجرة_CHAIN (builtin_typetail);
    }

  gcc_assert (parmnum == vec_safe_length (قيم));

  إذا (typetail != NULL_شجرة && شجرة_قيمة (typetail) != void_type_عقدة)
    {
      /* Not enough args.
	 Determine minimum number of arguments required.  */
      صحيح min_expected_رقم = 0;
      منطقي at_least_p = خطأ;
      شجرة iter = typelist;
      طالما (true)
	{
	  إذا (!iter)
	    {
	      /* Variadic arguments; stop iterating.  */
	      at_least_p = true;
	      اكسر;
	    }
	  إذا (iter == void_list_عقدة)
	    /* End of arguments; stop iterating.  */
	    اكسر;
	  ++min_expected_رقم;
	  iter = شجرة_CHAIN (iter);
	}
      auto_diagnostic_group d;
      صحيح actual_رقم = vec_safe_length (قيم);
      error_at (loc,
		at_least_p
		? G_("too few arguments to function %qE; expected at least %i, have %i")
		: G_("too few arguments to function %qE; expected %i, have %i"),
		function, min_expected_رقم, actual_رقم);
      inform_declaration (fundecl, function);
      أرجع -1;
    }

  إذا (builtin_typetail && شجرة_قيمة (builtin_typetail) != void_type_عقدة)
    {
      unsigned nargs = parmnum;
      لكل (شجرة t = builtin_typetail; t; t = شجرة_CHAIN (t))
	++nargs;

      auto_diagnostic_group d;
      إذا (warning_at (loc, OPT_Wbuiltin_declaration_mismatch,
		      "too few arguments to built-in function %qE "
		      "expecting %u", function, nargs - 1))
	inform_declaration (fundecl, function);
    }

  أرجع error_وسائط ? -1 : (صحيح) parmnum;
}

/* This is the entry point used by the parser to build unary operators
   in the input.  CODE, a tree_code, specifies the unary operator, and
   ARG is the operand.  For unary plus, the C parser currently uses
   CONVERT_EXPR for code.

   LOC is the location to use for the tree generated.
*/

بنية c_تعبير
parser_build_unary_op (location_t loc, تعداد شجرة_code code, بنية c_تعبير arg)
{
  بنية c_تعبير result;

  result.original_code = code;
  result.original_type = عدم;
  result.m_decimal = 0;

  إذا (reject_gcc_builtin (arg.قيمة))
    {
      result.قيمة = error_mark_عقدة;
    }
  وإلا
    {
      result.قيمة = build_unary_op (loc, code, arg.قيمة, خطأ);

      إذا (شجرة_OVERFLOW_P (result.قيمة) && !شجرة_OVERFLOW_P (arg.قيمة))
	overflow_warning (loc, result.قيمة, arg.قيمة);
    }

  /* We are typically called when parsing a prefix token at LOC acting on
     ARG.  Reflect this by updating the source range of the result to
     start at LOC and end at the end of ARG.  */
  set_c_تعبير_source_range (&result,
			   loc, arg.get_finish ());

  أرجع result;
}

/* Returns true if TYPE is a character type, *not* including wchar_t.  */

منطقي
char_type_p (شجرة type)
{
  أرجع (type == char_type_عقدة
	  || type == unsigned_char_type_عقدة
	  || type == signed_char_type_عقدة
	  || type == char16_type_عقدة
	  || type == char32_type_عقدة);
}

/* This is the entry point used by the parser to build binary operators
   in the input.  CODE, a tree_code, specifies the binary operator, and
   ARG1 and ARG2 are the operands.  In addition to constructing the
   expression, we check for operands that were written with other binary
   operators in a way that is likely to confuse the user.  ORIG_ARG1 is
   the original first operand for TRUTH_{AND,OR}IF_EXPR before it is
   converted to truth value, otherwise NULL_TREE.

   LOCATION is the location of the binary operator.  */

بنية c_تعبير
parser_build_ثنائي_op (location_t location, تعداد شجرة_code code,
			بنية c_تعبير arg1, بنية c_تعبير arg2, شجرة orig_arg1)
{
  بنية c_تعبير result;
  result.m_decimal = 0;

  تعداد شجرة_code code1 = arg1.original_code;
  تعداد شجرة_code code2 = arg2.original_code;
  شجرة type1 = (arg1.original_type
                ? arg1.original_type
                : شجرة_TYPE (arg1.قيمة));
  شجرة type2 = (arg2.original_type
                ? arg2.original_type
                : شجرة_TYPE (arg2.قيمة));

  result.قيمة = build_ثنائي_op (location, code,
				  arg1.قيمة, arg2.قيمة, true);
  result.original_code = code;
  result.original_type = عدم;
  result.m_decimal = 0;

  إذا (شجرة_CODE (result.قيمة) == ERROR_MARK)
    {
      set_c_تعبير_source_range (&result,
			       arg1.get_start (),
			       arg2.get_finish ());
      أرجع result;
    }

  إذا (location != UNKNOWN_LOCATION)
    protected_set_تعبير_location (result.قيمة, location);

  set_c_تعبير_source_range (&result,
			   arg1.get_start (),
			   arg2.get_finish ());

  /* Check for cases such as x+y<<z which users are likely
     to misinterpret.  */
  إذا (warn_parentheses)
    warn_about_parentheses (location, code, code1, arg1.قيمة, code2,
			    arg2.قيمة);

  إذا (warn_logical_op)
    warn_logical_operator (location, code, شجرة_TYPE (result.قيمة),
			   code1, arg1.قيمة, code2, arg2.قيمة);

  إذا (warn_constant_logical_operand
      && (code == TRUTH_ANDIF_تعبير || code == TRUTH_ORIF_تعبير)
      && INTEGRAL_NB_TYPE_P (type1)
      && INTEGRAL_NB_TYPE_P (type2))
    {
      ثابت حرف *name = code == TRUTH_ANDIF_تعبير ? "&&" : "||";
      إذا (orig_arg1 == NULL_شجرة)
	orig_arg1 = arg1.قيمة;
      auto enum_other_than_0_1 = [] (شجرة type) {
	إذا (شجرة_CODE (type) != ENUMERAL_TYPE)
	  أرجع خطأ;
	لكل (شجرة l = TYPE_قيم (type); l; l = شجرة_CHAIN (l))
	  {
	    شجرة v = DECL_INITIAL (شجرة_قيمة (l));
	    إذا (!integer_zerop (v) && !integer_onep (v))
	      أرجع true;
	  }
	أرجع خطأ;
      };
      auto diagnose_constant_logical_operand = [=] (شجرة val, شجرة type) {
	إذا (شجرة_CODE (val) != INTEGER_CST || integer_zerop (val))
	  أرجع خطأ;
	إذا (integer_onep (val) && !enum_other_than_0_1 (type))
	  أرجع خطأ;
	gcc_rich_location richloc (location);
	richloc.add_fixit_replace (name + 1);
	auto_diagnostic_group d;
	إذا (warning_at (location, OPT_Wconstant_logical_operand,
			"use of logical %qs with constant operand %qE",
			name, val))
	  inform (&richloc, "use %qs for bitwise operation", name + 1);
	أرجع true;
      };
      إذا (!diagnose_constant_logical_operand (arg2.قيمة, type2))
	diagnose_constant_logical_operand (orig_arg1, type1);
    }

  إذا (warn_tautological_compare)
    {
      شجرة lhs = arg1.قيمة;
      شجرة rhs = arg2.قيمة;
      إذا (شجرة_CODE (lhs) == C_MAYBE_CONST_تعبير)
	{
	  إذا (C_MAYBE_CONST_تعبير_PRE (lhs) != NULL_شجرة
	      && شجرة_SIDE_EFFECTS (C_MAYBE_CONST_تعبير_PRE (lhs)))
	    lhs = NULL_شجرة;
	  وإلا
	    lhs = C_MAYBE_CONST_تعبير_تعبير (lhs);
	}
      إذا (شجرة_CODE (rhs) == C_MAYBE_CONST_تعبير)
	{
	  إذا (C_MAYBE_CONST_تعبير_PRE (rhs) != NULL_شجرة
	      && شجرة_SIDE_EFFECTS (C_MAYBE_CONST_تعبير_PRE (rhs)))
	    rhs = NULL_شجرة;
	  وإلا
	    rhs = C_MAYBE_CONST_تعبير_تعبير (rhs);
	}
      إذا (lhs != NULL_شجرة && rhs != NULL_شجرة)
	warn_tautological_cmp (location, code, lhs, rhs);
    }

  إذا (warn_logical_not_paren
      && شجرة_CODE_CLASS (code) == tcc_comparison
      && code1 == TRUTH_NOT_تعبير
      && code2 != TRUTH_NOT_تعبير
      /* Avoid warning for !!x == y.  */
      && (شجرة_CODE (arg1.قيمة) != NE_تعبير
	  || !integer_zerop (شجرة_OPERAND (arg1.قيمة, 1))))
    {
      /* Avoid warning for !b == y where b has _Bool type.  */
      شجرة t = integer_zero_عقدة;
      إذا (شجرة_CODE (arg1.قيمة) == EQ_تعبير
	  && integer_zerop (شجرة_OPERAND (arg1.قيمة, 1))
	  && شجرة_TYPE (شجرة_OPERAND (arg1.قيمة, 0)) == integer_type_عقدة)
	{
	  t = شجرة_OPERAND (arg1.قيمة, 0);
	  افعل
	    {
	      إذا (شجرة_TYPE (t) != integer_type_عقدة)
		اكسر;
	      إذا (شجرة_CODE (t) == C_MAYBE_CONST_تعبير)
		t = C_MAYBE_CONST_تعبير_تعبير (t);
	      وإلا إذا (CONVERT_تعبير_P (t))
		t = شجرة_OPERAND (t, 0);
	      وإلا
		اكسر;
	    }
	  طالما (1);
	}
      إذا (!C_BOOLEAN_TYPE_P (شجرة_TYPE (t)))
	warn_logical_not_parentheses (location, code, arg1.قيمة, arg2.قيمة);
    }

  /* Warn about comparisons against string literals, with the exception
     of testing for equality or inequality of a string literal with NULL.  */
  إذا (code == EQ_تعبير || code == NE_تعبير)
    {
      إذا ((code1 == STRING_CST
	   && !integer_zerop (شجرة_strip_nop_conversions (arg2.قيمة)))
	  || (code2 == STRING_CST
	      && !integer_zerop (شجرة_strip_nop_conversions (arg1.قيمة))))
	warning_at (location, OPT_Waddress,
		    "comparison with string literal results in unspecified behavior");
      /* Warn for ptr == '\0', it's likely that it should've been ptr[0].  */
      إذا (POINTER_TYPE_P (type1)
	  && null_pointer_constant_p (arg2.قيمة)
	  && char_type_p (type2))
	{
	  auto_diagnostic_group d;
	  إذا (warning_at (location, OPT_Wpointer_compare,
			    "comparison between pointer and zero character "
			    "constant"))
	    inform (arg1.get_start (),
		      "did you mean to dereference the pointer?");
	}
      وإلا إذا (POINTER_TYPE_P (type2)
	       && null_pointer_constant_p (arg1.قيمة)
	       && char_type_p (type1))
	{
	  auto_diagnostic_group d;
	  إذا (warning_at (location, OPT_Wpointer_compare,
			    "comparison between pointer and zero character "
			    "constant"))
	    inform (arg2.get_start (),
		      "did you mean to dereference the pointer?");
	}
    }
  وإلا إذا (شجرة_CODE_CLASS (code) == tcc_comparison
	   && (code1 == STRING_CST || code2 == STRING_CST))
    warning_at (location, OPT_Waddress,
		"comparison with string literal results in unspecified "
		"behavior");

  إذا (warn_zero_as_null_pointer_constant
      && c_inhibit_evaluation_warnings == 0
      && شجرة_CODE_CLASS (code) == tcc_comparison)
    {
      إذا ((شجرة_CODE (type1) == POINTER_TYPE
	   || شجرة_CODE (type1) == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type2)
	  && null_pointer_constant_p (arg2.قيمة))
	warning_at (arg2.get_location(), OPT_Wzero_as_null_pointer_constant,
		    "zero as null pointer constant");

      إذا ((شجرة_CODE (type2) == POINTER_TYPE
	   || شجرة_CODE (type2) == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type1)
	  && null_pointer_constant_p (arg1.قيمة))
	warning_at (arg1.get_location(), OPT_Wzero_as_null_pointer_constant,
		    "zero as null pointer constant");
    }

  إذا (warn_array_compare
      && شجرة_CODE_CLASS (code) == tcc_comparison
      && شجرة_CODE (type1) == ARRAY_TYPE
      && شجرة_CODE (type2) == ARRAY_TYPE)
    do_warn_array_compare (location, code, arg1.قيمة, arg2.قيمة);

  إذا (شجرة_OVERFLOW_P (result.قيمة)
      && !شجرة_OVERFLOW_P (arg1.قيمة)
      && !شجرة_OVERFLOW_P (arg2.قيمة))
    overflow_warning (location, result.قيمة);

  /* Warn about comparisons of different enum types.  */
  إذا (warn_enum_compare
      && شجرة_CODE_CLASS (code) == tcc_comparison
      && شجرة_CODE (type1) == ENUMERAL_TYPE
      && شجرة_CODE (type2) == ENUMERAL_TYPE
      && TYPE_MAIN_VARIANT (type1) != TYPE_MAIN_VARIANT (type2))
    warning_at (location, OPT_Wenum_compare,
		"comparison between %qT and %qT",
		type1, type2);

  إذا (warn_xor_used_as_pow
      && code == BIT_XOR_تعبير
      && arg1.m_decimal
      && arg2.m_decimal)
    check_for_xor_used_as_pow (arg1.get_location (), arg1.قيمة,
			       location,
			       arg2.get_location (), arg2.قيمة);

  أرجع result;
}

/* Return a tree for the difference of pointers OP0 and OP1.
   The resulting tree has type ptrdiff_t.  If POINTER_SUBTRACT sanitization is
   enabled, assign to INSTRUMENT_EXPR call to libsanitizer.  */

ساكن شجرة
pointer_diff (location_t loc, شجرة op0, شجرة op1, شجرة *instrument_تعبير)
{
  شجرة restype = ptrdiff_type_عقدة;
  شجرة result, inttype;

  addr_space_t as0 = TYPE_ADDR_SPACE (شجرة_TYPE (شجرة_TYPE (op0)));
  addr_space_t as1 = TYPE_ADDR_SPACE (شجرة_TYPE (شجرة_TYPE (op1)));
  شجرة target_type = شجرة_TYPE (شجرة_TYPE (op0));
  شجرة orig_op0 = op0;
  شجرة orig_op1 = op1;

  /* If the operands point into different address spaces, we need to
     explicitly convert them to pointers into the common address space
     before we can subtract the numerical address values.  */
  إذا (as0 != as1)
    {
      addr_space_t as_common;
      شجرة common_type;

      /* Determine the common superset address space.  This is guaranteed
	 to exist because the caller verified that comp_target_types
	 returned non-zero.  */
      إذا (!addr_space_superset (as0, as1, &as_common))
	gcc_unreachable ();

      common_type = common_pointer_type (شجرة_TYPE (op0), شجرة_TYPE (op1), NULL_شجرة);
      op0 = convert (common_type, op0);
      op1 = convert (common_type, op1);
    }

  /* Determine integer type result of the subtraction.  This will usually
     be the same as the result type (ptrdiff_t), but may need to be a wider
     type if pointers for the address space are wider than ptrdiff_t.  */
  إذا (TYPE_PRECISION (restype) < TYPE_PRECISION (شجرة_TYPE (op0)))
    inttype = c_common_type_for_size (TYPE_PRECISION (شجرة_TYPE (op0)), 0);
  وإلا
    inttype = restype;

  إذا (VOID_TYPE_P (target_type))
    pedwarn (loc, OPT_Wpointer_arith,
	     "pointer of type %<void *%> used in subtraction");
  إذا (شجرة_CODE (target_type) == FUNCTION_TYPE)
    pedwarn (loc, OPT_Wpointer_arith,
	     "pointer to a function used in subtraction");

  إذا (current_function_decl != NULL_شجرة
      && sanitize_flags_p (SANITIZE_POINTER_SUBTRACT))
    {
      op0 = save_تعبير (c_fully_fold (op0, خطأ, عدم));
      op1 = save_تعبير (c_fully_fold (op1, خطأ, عدم));

      شجرة tt = builtin_decl_explicit (BUILT_IN_ASAN_POINTER_SUBTRACT);
      *instrument_تعبير = build_call_تعبير_loc (loc, tt, 2, op0, op1);
    }

  /* First do the subtraction, then build the divide operator
     and only convert at the very end.
     Do not do default conversions in case restype is a short type.  */

  /* POINTER_DIFF_EXPR requires a signed integer type of the same size as
     pointers.  If some platform cannot provide that, or has a larger
     ptrdiff_type to support differences larger than half the address
     space, cast the pointers to some larger integer type and do the
     computations in that type.  */
  إذا (TYPE_PRECISION (inttype) > TYPE_PRECISION (شجرة_TYPE (op0)))
    op0 = build_ثنائي_op (loc, MINUS_تعبير, convert (inttype, op0),
			   convert (inttype, op1), خطأ);
  وإلا
    {
      /* Cast away qualifiers.  */
      op0 = convert (c_common_type (شجرة_TYPE (op0), شجرة_TYPE (op0)), op0);
      op1 = convert (c_common_type (شجرة_TYPE (op1), شجرة_TYPE (op1)), op1);
      op0 = build2_loc (loc, POINTER_DIFF_تعبير, inttype, op0, op1);
    }

  /* This generates an error if op1 is pointer to incomplete type.  */
  إذا (!COMPLETE_OR_VOID_TYPE_P (شجرة_TYPE (شجرة_TYPE (orig_op1))))
    error_at (loc, "arithmetic on pointer to an incomplete type");
  وإلا إذا (verify_type_context (loc, TCTX_POINTER_ARITH,
				شجرة_TYPE (شجرة_TYPE (orig_op0))))
    verify_type_context (loc, TCTX_POINTER_ARITH,
			 شجرة_TYPE (شجرة_TYPE (orig_op1)));

  op1 = c_size_in_bytes (target_type);

  إذا (pointer_to_zero_sized_aggr_p (شجرة_TYPE (orig_op1)))
    error_at (loc, "arithmetic on pointer to an empty aggregate");

  /* Divide by the size, in easiest possible way.  */
  result = fold_build2_loc (loc, EXACT_DIV_تعبير, inttype,
			    op0, convert (inttype, op1));

  /* Convert to final result type if necessary.  */
  أرجع convert (restype, result);
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

ساكن شجرة
build_atomic_assign (location_t loc, شجرة lhs, تعداد شجرة_code modifycode,
		     شجرة rhs, منطقي return_old_p)
{
  شجرة fndecl, func_call;
  vec<شجرة, va_gc> *params;
  شجرة val, nonatomic_lhs_type, nonatomic_rhs_type, newval, newval_addr;
  شجرة old, old_addr;
  شجرة compound_stmt = NULL_شجرة;
  شجرة stmt, goto_stmt;
  شجرة loop_label, loop_decl, done_label, done_decl;

  شجرة lhs_type = شجرة_TYPE (lhs);
  شجرة lhs_addr = build_unary_op (loc, ADDR_تعبير, lhs, خطأ);
  شجرة seq_cst = build_int_cst (integer_type_عقدة, MEMMODEL_SEQ_CST);
  شجرة rhs_semantic_type = شجرة_TYPE (rhs);
  شجرة nonatomic_rhs_semantic_type;
  شجرة rhs_type;

  gcc_assert (TYPE_ATOMIC (lhs_type));

  إذا (return_old_p)
    gcc_assert (modifycode == PLUS_تعبير || modifycode == MINUS_تعبير);

  /* Allocate enough vector items for a compare_exchange.  */
  vec_alloc (params, 6);

  /* Create a compound statement to hold the sequence of statements
     with a loop.  */
  إذا (modifycode != NOP_تعبير)
    {
      compound_stmt = c_begin_compound_stmt (خطأ);

      /* For consistency with build_modify_expr on non-_Atomic,
	 mark the lhs as read.  Also, it would be very hard to match
	 such expressions in mark_exp_read.  */
      mark_exp_read (lhs);
    }

  /* Remove any excess precision (which is only present here in the
     case of compound assignments).  */
  إذا (شجرة_CODE (rhs) == EXCESS_PRECISION_تعبير)
    {
      gcc_assert (modifycode != NOP_تعبير);
      rhs = شجرة_OPERAND (rhs, 0);
    }
  rhs_type = شجرة_TYPE (rhs);

  /* Fold the RHS if it hasn't already been folded.  */
  إذا (modifycode != NOP_تعبير)
    rhs = c_fully_fold (rhs, خطأ, عدم);

  /* Remove the qualifiers for the rest of the expressions and create
     the VAL temp variable to hold the RHS.  */
  nonatomic_lhs_type = build_qualified_type (lhs_type, TYPE_UNQUALIFIED);
  nonatomic_rhs_type = build_qualified_type (rhs_type, TYPE_UNQUALIFIED);
  nonatomic_rhs_semantic_type = build_qualified_type (rhs_semantic_type,
						      TYPE_UNQUALIFIED);
  val = create_tmp_var_raw (nonatomic_rhs_type);
  شجرة_ADDRESSABLE (val) = 1;
  suppress_warning (val);
  rhs = build4 (TARGET_تعبير, nonatomic_rhs_type, val, rhs, NULL_شجرة,
		NULL_شجرة);
  شجرة_SIDE_EFFECTS (rhs) = 1;
  SET_تعبير_LOCATION (rhs, loc);
  إذا (modifycode != NOP_تعبير)
    add_stmt (rhs);

  /* NOP_EXPR indicates it's a straight store of the RHS. Simply issue
     an atomic_store.  */
  إذا (modifycode == NOP_تعبير)
    {
      compound_stmt = rhs;
      /* Build __atomic_store (&lhs, &val, SEQ_CST)  */
      rhs = build_unary_op (loc, ADDR_تعبير, val, خطأ);
      fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_STORE);
      params->quick_ادفع (lhs_addr);
      params->quick_ادفع (rhs);
      params->quick_ادفع (seq_cst);
      func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, عدم);

      compound_stmt = build2 (COMPOUND_تعبير, void_type_عقدة,
			      compound_stmt, func_call);

      /* VAL is the value which was stored, return a COMPOUND_STMT of
	 the statement and that value.  */
      أرجع build2 (COMPOUND_تعبير, nonatomic_lhs_type, compound_stmt, val);
    }

  /* Attempt to implement the atomic operation as an __atomic_fetch_* or
     __atomic_*_fetch built-in rather than a CAS loop.  atomic_bool type
     isn't applicable for such builtins.  ??? Do we want to handle enums?  */
  إذا ((شجرة_CODE (lhs_type) == INTEGER_TYPE || POINTER_TYPE_P (lhs_type))
      && شجرة_CODE (rhs_type) == INTEGER_TYPE)
    {
      built_in_function fncode;
      بدل (modifycode)
	{
	حالة PLUS_تعبير:
	حالة POINTER_PLUS_تعبير:
	  fncode = (return_old_p
		    ? BUILT_IN_ATOMIC_FETCH_ADD_N
		    : BUILT_IN_ATOMIC_ADD_FETCH_N);
	  اكسر;
	حالة MINUS_تعبير:
	  fncode = (return_old_p
		    ? BUILT_IN_ATOMIC_FETCH_SUB_N
		    : BUILT_IN_ATOMIC_SUB_FETCH_N);
	  اكسر;
	حالة BIT_AND_تعبير:
	  fncode = (return_old_p
		    ? BUILT_IN_ATOMIC_FETCH_AND_N
		    : BUILT_IN_ATOMIC_AND_FETCH_N);
	  اكسر;
	حالة BIT_IOR_تعبير:
	  fncode = (return_old_p
		    ? BUILT_IN_ATOMIC_FETCH_OR_N
		    : BUILT_IN_ATOMIC_OR_FETCH_N);
	  اكسر;
	حالة BIT_XOR_تعبير:
	  fncode = (return_old_p
		    ? BUILT_IN_ATOMIC_FETCH_XOR_N
		    : BUILT_IN_ATOMIC_XOR_FETCH_N);
	  اكسر;
	افتراضي:
	  اذهب cas_loop;
	}

      /* We can only use "_1" through "_16" variants of the atomic fetch
	 built-ins.  */
      unsigned HOST_WIDE_INT size = شجرة_to_uhwi (TYPE_SIZE_UNIT (lhs_type));
      إذا (size != 1 && size != 2 && size != 4 && size != 8 && size != 16)
	اذهب cas_loop;

      /* If this is a pointer type, we need to multiply by the size of
	 the pointer target type.  */
      إذا (POINTER_TYPE_P (lhs_type))
	{
	  إذا (!COMPLETE_TYPE_P (شجرة_TYPE (lhs_type))
	      /* ??? This would introduce -Wdiscarded-qualifiers
		 warning: __atomic_fetch_* expect volatile void *
		 type as the first argument.  (Assignments between
		 atomic and non-atomic objects are OK.) */
	      || TYPE_RESTRICT (lhs_type))
	    اذهب cas_loop;
	  شجرة sz = TYPE_SIZE_UNIT (شجرة_TYPE (lhs_type));
	  rhs = fold_build2_loc (loc, MULT_تعبير, ptrdiff_type_عقدة,
				 convert (ptrdiff_type_عقدة, rhs),
				 convert (ptrdiff_type_عقدة, sz));
	}

      /* Build __atomic_fetch_* (&lhs, &val, SEQ_CST), or
	 __atomic_*_fetch (&lhs, &val, SEQ_CST).  */
      fndecl = builtin_decl_explicit (fncode);
      params->quick_ادفع (lhs_addr);
      params->quick_ادفع (rhs);
      params->quick_ادفع (seq_cst);
      func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, عدم);

      newval = create_tmp_var_raw (nonatomic_lhs_type);
      شجرة_ADDRESSABLE (newval) = 1;
      suppress_warning (newval);
      rhs = build4 (TARGET_تعبير, nonatomic_lhs_type, newval, func_call,
		    NULL_شجرة, NULL_شجرة);
      SET_تعبير_LOCATION (rhs, loc);
      add_stmt (rhs);

      /* Finish the compound statement.  */
      compound_stmt = c_end_compound_stmt (loc, compound_stmt, خطأ);

      /* NEWVAL is the value which was stored, return a COMPOUND_STMT of
	 the statement and that value.  */
      أرجع build2 (COMPOUND_تعبير, nonatomic_lhs_type, compound_stmt, newval);
    }

cas_loop:
  /* Create the variables and labels required for the op= form.  */
  old = create_tmp_var_raw (nonatomic_lhs_type);
  old_addr = build_unary_op (loc, ADDR_تعبير, old, خطأ);
  شجرة_ADDRESSABLE (old) = 1;
  suppress_warning (old);

  newval = create_tmp_var_raw (nonatomic_lhs_type);
  newval_addr = build_unary_op (loc, ADDR_تعبير, newval, خطأ);
  شجرة_ADDRESSABLE (newval) = 1;
  suppress_warning (newval);

  loop_decl = create_artificial_label (loc);
  loop_label = build1 (LABEL_تعبير, void_type_عقدة, loop_decl);

  done_decl = create_artificial_label (loc);
  done_label = build1 (LABEL_تعبير, void_type_عقدة, done_decl);

  /* __atomic_load (addr, &old, SEQ_CST).  */
  fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_LOAD);
  params->quick_ادفع (lhs_addr);
  params->quick_ادفع (old_addr);
  params->quick_ادفع (seq_cst);
  func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, عدم);
  old = build4 (TARGET_تعبير, nonatomic_lhs_type, old, func_call, NULL_شجرة,
		NULL_شجرة);
  add_stmt (old);
  params->truncate (0);

  /* Create the expressions for floating-point environment
     manipulation, if required.  */
  منطقي need_fenv = (flag_trapping_math
		    && (FLOAT_TYPE_P (lhs_type) || FLOAT_TYPE_P (rhs_type)));
  شجرة hold_call = NULL_شجرة, clear_call = NULL_شجرة, update_call = NULL_شجرة;
  إذا (need_fenv)
    targetm.atomic_assign_expand_fenv (&hold_call, &clear_call, &update_call);

  إذا (hold_call)
    add_stmt (hold_call);

  /* loop:  */
  add_stmt (loop_label);

  /* newval = old + val;  */
  إذا (rhs_type != rhs_semantic_type)
    val = build1 (EXCESS_PRECISION_تعبير, nonatomic_rhs_semantic_type, val);
  rhs = build_ثنائي_op (loc, modifycode,
			 convert_lvalue_to_rvalue (loc, old, true, true),
			 val, true);
  إذا (شجرة_CODE (rhs) == EXCESS_PRECISION_تعبير)
    {
      شجرة eptype = شجرة_TYPE (rhs);
      rhs = c_fully_fold (شجرة_OPERAND (rhs, 0), خطأ, عدم);
      rhs = build1 (EXCESS_PRECISION_تعبير, eptype, rhs);
    }
  وإلا
    rhs = c_fully_fold (rhs, خطأ, عدم);
  rhs = convert_for_assignment (loc, UNKNOWN_LOCATION, nonatomic_lhs_type,
				rhs, NULL_شجرة, ic_assign, خطأ, NULL_شجرة,
				NULL_شجرة, 0);
  /* The temporary variable for NEWVAL is only gimplified correctly (in
     particular, given a DECL_CONTEXT) if used in a TARGET_EXPR.  To avoid
     subsequent ICEs in nested function processing after an error, ensure such
     a TARGET_EXPR is built even after an error.  */
  إذا (rhs == error_mark_عقدة)
    rhs = old;
  rhs = build4 (TARGET_تعبير, nonatomic_lhs_type, newval, rhs, NULL_شجرة,
		NULL_شجرة);
  SET_تعبير_LOCATION (rhs, loc);
  add_stmt (rhs);

  /* if (__atomic_compare_exchange (addr, &old, &new, false, SEQ_CST, SEQ_CST))
       goto done;  */
  fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_COMPARE_EXCHANGE);
  params->quick_ادفع (lhs_addr);
  params->quick_ادفع (old_addr);
  params->quick_ادفع (newval_addr);
  params->quick_ادفع (integer_zero_عقدة);
  params->quick_ادفع (seq_cst);
  params->quick_ادفع (seq_cst);
  func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, عدم);

  goto_stmt = build1 (GOTO_تعبير, void_type_عقدة, done_decl);
  SET_تعبير_LOCATION (goto_stmt, loc);

  stmt = build3 (COND_تعبير, void_type_عقدة, func_call, goto_stmt, NULL_شجرة);
  SET_تعبير_LOCATION (stmt, loc);
  add_stmt (stmt);

  إذا (clear_call)
    add_stmt (clear_call);

  /* goto loop;  */
  goto_stmt  = build1 (GOTO_تعبير, void_type_عقدة, loop_decl);
  SET_تعبير_LOCATION (goto_stmt, loc);
  add_stmt (goto_stmt);

  /* done:  */
  add_stmt (done_label);

  إذا (update_call)
    add_stmt (update_call);

  /* Finish the compound statement.  */
  compound_stmt = c_end_compound_stmt (loc, compound_stmt, خطأ);

  /* NEWVAL is the value that was successfully stored, return a
     COMPOUND_EXPR of the statement and the appropriate value.  */
  أرجع build2 (COMPOUND_تعبير, nonatomic_lhs_type, compound_stmt,
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

شجرة
build_unary_op (location_t location, تعداد شجرة_code code, شجرة xarg,
		منطقي noconvert)
{
  /* No default_conversion here.  It causes trouble for ADDR_EXPR.  */
  شجرة arg = xarg;
  شجرة argtype = NULL_شجرة;
  تعداد شجرة_code typecode;
  شجرة val;
  شجرة ret = error_mark_عقدة;
  شجرة eptype = NULL_شجرة;
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
  إذا (is_access_with_size_p (arg))
    xarg = arg = get_ref_from_access_with_size (arg);

  gcc_checking_assert (!is_access_with_size_p (arg));

  منطقي int_operands = تعبير_INT_CONST_OPERANDS (xarg);
  إذا (int_operands)
    arg = remove_c_maybe_const_تعبير (arg);

  إذا (code != ADDR_تعبير)
    arg = require_complete_type (location, arg);

  typecode = شجرة_CODE (شجرة_TYPE (arg));
  إذا (typecode == ERROR_MARK)
    أرجع error_mark_عقدة;
  إذا (typecode == ENUMERAL_TYPE || typecode == BOOLEAN_TYPE)
    typecode = INTEGER_TYPE;

  إذا ((invalid_op_diag
       = targetm.invalid_unary_op (code, شجرة_TYPE (xarg))))
    {
      error_at (location, invalid_op_diag);
      أرجع error_mark_عقدة;
    }

  إذا (شجرة_CODE (arg) == EXCESS_PRECISION_تعبير)
    {
      eptype = شجرة_TYPE (arg);
      arg = شجرة_OPERAND (arg, 0);
    }

  بدل (code)
    {
    حالة CONVERT_تعبير:
      /* This is used for unary plus, because a CONVERT_EXPR
	 is enough to prevent anybody from looking inside for
	 associativity, but won't generate any code.  */
      إذا (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE
	    || typecode == FIXED_POINT_TYPE || typecode == COMPLEX_TYPE
	    || typecode == BITINT_TYPE
	    || gnu_vector_type_p (شجرة_TYPE (arg))))
	{
	  error_at (location, "wrong type argument to unary plus");
	  أرجع error_mark_عقدة;
	}
      وإلا إذا (!noconvert)
	arg = default_conversion (arg);
      arg = non_lvalue_loc (location, arg);
      اكسر;

    حالة NEGATE_تعبير:
      إذا (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE
	    || typecode == FIXED_POINT_TYPE || typecode == COMPLEX_TYPE
	    || typecode == BITINT_TYPE
	    || gnu_vector_type_p (شجرة_TYPE (arg))))
	{
	  error_at (location, "wrong type argument to unary minus");
	  أرجع error_mark_عقدة;
	}
      وإلا إذا (!noconvert)
	arg = default_conversion (arg);
      اكسر;

    حالة BIT_NOT_تعبير:
      /* ~ works on integer types and non float vectors. */
      إذا (typecode == INTEGER_TYPE
	  || typecode == BITINT_TYPE
	  || (gnu_vector_type_p (شجرة_TYPE (arg))
	      && !VECTOR_FLOAT_TYPE_P (شجرة_TYPE (arg))))
	{
	  شجرة e = arg;

	  /* Warn if the expression has boolean value.  */
	  طالما (شجرة_CODE (e) == COMPOUND_تعبير)
	    e = شجرة_OPERAND (e, 1);

	  إذا ((C_BOOLEAN_TYPE_P (شجرة_TYPE (arg))
	       || truth_قيمة_p (شجرة_CODE (e))))
	    {
	      auto_diagnostic_group d;
	      إذا (warning_at (location, OPT_Wbool_operation,
				"%<~%> on a boolean expression"))
		{
		  gcc_rich_location richloc (location);
		  richloc.add_fixit_أدرج_before (location, "!");
		  inform (&richloc, "did you mean to use logical not?");
		}
	    }
	  إذا (!noconvert)
	    arg = default_conversion (arg);
	}
      وإلا إذا (typecode == COMPLEX_TYPE)
	{
	  code = CONJ_تعبير;
	  pedwarn (location, OPT_Wpedantic,
		   "ISO C does not support %<~%> for complex conjugation");
	  إذا (!noconvert)
	    arg = default_conversion (arg);
	}
      وإلا
	{
	  error_at (location, "wrong type argument to bit-complement");
	  أرجع error_mark_عقدة;
	}
      اكسر;

    حالة ABS_تعبير:
      إذا (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE))
	{
	  error_at (location, "wrong type argument to abs");
	  أرجع error_mark_عقدة;
	}
      وإلا إذا (!noconvert)
	arg = default_conversion (arg);
      اكسر;

    حالة ABSU_تعبير:
      إذا (!(typecode == INTEGER_TYPE))
	{
	  error_at (location, "wrong type argument to absu");
	  أرجع error_mark_عقدة;
	}
      وإلا إذا (!noconvert)
	arg = default_conversion (arg);
      اكسر;

    حالة CONJ_تعبير:
      /* Conjugating a real value is a no-op, but allow it anyway.  */
      إذا (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE
	    || typecode == COMPLEX_TYPE))
	{
	  error_at (location, "wrong type argument to conjugation");
	  أرجع error_mark_عقدة;
	}
      وإلا إذا (!noconvert)
	arg = default_conversion (arg);
      اكسر;

    حالة TRUTH_NOT_تعبير:
      إذا (typecode != INTEGER_TYPE && typecode != FIXED_POINT_TYPE
	  && typecode != REAL_TYPE && typecode != POINTER_TYPE
	  && typecode != COMPLEX_TYPE && typecode != NULLPTR_TYPE
	  && typecode != BITINT_TYPE)
	{
	  error_at (location,
		    "wrong type argument to unary exclamation mark");
	  أرجع error_mark_عقدة;
	}
      إذا (int_operands)
	{
	  arg = c_objc_common_truthvalue_conversion (location, xarg);
	  arg = remove_c_maybe_const_تعبير (arg);
	}
      وإلا
	arg = c_objc_common_truthvalue_conversion (location, arg);
      ret = invert_truthvalue_loc (location, arg);
      eptype = NULL_شجرة;
      /* If the TRUTH_NOT_EXPR has been folded, reset the location.  */
      إذا (تعبير_P (ret) && تعبير_HAS_LOCATION (ret))
	location = تعبير_LOCATION (ret);
      اذهب return_build_unary_op;

    حالة REALPART_تعبير:
    حالة IMAGPART_تعبير:
      ret = build_real_imag_تعبير (location, code, arg);
      إذا (ret == error_mark_عقدة)
	أرجع error_mark_عقدة;
      إذا (eptype && شجرة_CODE (eptype) == COMPLEX_TYPE)
	eptype = شجرة_TYPE (eptype);
      اذهب return_build_unary_op;

    حالة PREINCREMENT_تعبير:
    حالة POSTINCREMENT_تعبير:
    حالة PREDECREMENT_تعبير:
    حالة POSTDECREMENT_تعبير:

      إذا (شجرة_CODE (arg) == C_MAYBE_CONST_تعبير)
	{
	  شجرة inner = build_unary_op (location, code,
				       C_MAYBE_CONST_تعبير_تعبير (arg),
				       noconvert);
	  إذا (inner == error_mark_عقدة)
	    أرجع error_mark_عقدة;
	  ret = build2 (C_MAYBE_CONST_تعبير, شجرة_TYPE (inner),
			C_MAYBE_CONST_تعبير_PRE (arg), inner);
	  gcc_assert (!C_MAYBE_CONST_تعبير_INT_OPERANDS (arg));
	  C_MAYBE_CONST_تعبير_NON_CONST (ret) = 1;
	  اذهب return_build_unary_op;
	}

      /* Complain about anything that is not a true lvalue.  In
	 Objective-C, skip this check for property_refs.  */
      إذا (!objc_is_property_ref (arg)
	  && !lvalue_or_else (location,
			      arg, ((code == PREINCREMENT_تعبير
				     || code == POSTINCREMENT_تعبير)
				    ? lv_increment
				    : lv_decrement)))
	أرجع error_mark_عقدة;

      إذا (warn_cxx_compat && شجرة_CODE (شجرة_TYPE (arg)) == ENUMERAL_TYPE)
	{
	  إذا (code == PREINCREMENT_تعبير || code == POSTINCREMENT_تعبير)
	    warning_at (location, OPT_Wc___compat,
			"increment of enumeration value is invalid in C++");
	  وإلا
	    warning_at (location, OPT_Wc___compat,
			"decrement of enumeration value is invalid in C++");
	}

      إذا (C_BOOLEAN_TYPE_P (شجرة_TYPE (arg)))
	{
	  إذا (code == PREINCREMENT_تعبير || code == POSTINCREMENT_تعبير)
	    warning_at (location, OPT_Wbool_operation,
			"increment of a boolean expression");
	  وإلا
	    warning_at (location, OPT_Wbool_operation,
			"decrement of a boolean expression");
	}

      /* Ensure the argument is fully folded inside any SAVE_EXPR.  */
      arg = c_fully_fold (arg, خطأ, عدم, true);

      منطقي atomic_op;
      atomic_op = really_atomic_lvalue (arg);

      /* Increment or decrement the real part of the value,
	 and don't change the imaginary part.  */
      إذا (typecode == COMPLEX_TYPE)
	{
	  شجرة real, imag;

	  pedwarn_c23 (location, OPT_Wpedantic,
		       "ISO C does not support %<++%> and %<--%> on complex "
		       "types before C2Y");

	  إذا (!atomic_op)
	    {
	      arg = stabilize_reference (arg);
	      real = build_unary_op (تعبير_LOCATION (arg), REALPART_تعبير, arg,
				     true);
	      imag = build_unary_op (تعبير_LOCATION (arg), IMAGPART_تعبير, arg,
				     true);
	      real = build_unary_op (تعبير_LOCATION (arg), code, real, true);
	      إذا (real == error_mark_عقدة || imag == error_mark_عقدة)
		أرجع error_mark_عقدة;
	      ret = build2 (COMPLEX_تعبير, شجرة_TYPE (arg),
			    real, imag);
	      اذهب return_build_unary_op;
	    }
	}

      /* Report invalid types.  */

      إذا (typecode != POINTER_TYPE && typecode != FIXED_POINT_TYPE
	  && typecode != INTEGER_TYPE && typecode != REAL_TYPE
	  && typecode != COMPLEX_TYPE && typecode != BITINT_TYPE
	  && !gnu_vector_type_p (شجرة_TYPE (arg)))
	{
	  إذا (code == PREINCREMENT_تعبير || code == POSTINCREMENT_تعبير)
	    error_at (location, "wrong type argument to increment");
	  وإلا
	    error_at (location, "wrong type argument to decrement");

	  أرجع error_mark_عقدة;
	}

      {
	شجرة inc;

	argtype = شجرة_TYPE (arg);

	/* Compute the increment.  */

	إذا (typecode == POINTER_TYPE)
	  {
	    /* If pointer target is an incomplete type,
	       we just cannot know how to do the arithmetic.  */
	    إذا (!COMPLETE_OR_VOID_TYPE_P (شجرة_TYPE (argtype)))
	      {
		إذا (code == PREINCREMENT_تعبير || code == POSTINCREMENT_تعبير)
		  error_at (location,
			    "increment of pointer to an incomplete type %qT",
			    شجرة_TYPE (argtype));
		وإلا
		  error_at (location,
			    "decrement of pointer to an incomplete type %qT",
			    شجرة_TYPE (argtype));
	      }
	    وإلا إذا (شجرة_CODE (شجرة_TYPE (argtype)) == FUNCTION_TYPE
		     || VOID_TYPE_P (شجرة_TYPE (argtype)))
	      {
		إذا (code == PREINCREMENT_تعبير || code == POSTINCREMENT_تعبير)
		  pedwarn (location, OPT_Wpointer_arith,
			   "wrong type argument to increment");
		وإلا
		  pedwarn (location, OPT_Wpointer_arith,
			   "wrong type argument to decrement");
	      }
	    وإلا
	      verify_type_context (location, TCTX_POINTER_ARITH,
				   شجرة_TYPE (argtype));

	    inc = c_size_in_bytes (شجرة_TYPE (argtype));
	    inc = convert_to_ptrofftype_loc (location, inc);
	  }
	وإلا إذا (FRACT_MODE_P (TYPE_MODE (argtype)))
	  {
	    /* For signed fract types, we invert ++ to -- or
	       -- to ++, and change inc from 1 to -1, because
	       it is not possible to represent 1 in signed fract constants.
	       For unsigned fract types, the result always overflows and
	       we get an undefined (original) or the maximum value.  */
	    إذا (code == PREINCREMENT_تعبير)
	      code = PREDECREMENT_تعبير;
	    وإلا إذا (code == PREDECREMENT_تعبير)
	      code = PREINCREMENT_تعبير;
	    وإلا إذا (code == POSTINCREMENT_تعبير)
	      code = POSTDECREMENT_تعبير;
	    وإلا /* code == POSTDECREMENT_EXPR  */
	      code = POSTINCREMENT_تعبير;

	    inc = integer_minus_one_عقدة;
	    inc = convert (argtype, inc);
	  }
	وإلا
	  {
	    inc = VECTOR_TYPE_P (argtype)
	      ? build_one_cst (argtype)
	      : integer_one_عقدة;
	    inc = convert (argtype, inc);
	  }

	/* If 'arg' is an Objective-C PROPERTY_REF expression, then we
	   need to ask Objective-C to build the increment or decrement
	   expression for it.  */
	إذا (objc_is_property_ref (arg))
	  أرجع objc_build_incr_تعبير_for_property_ref (location, code,
							arg, inc);

	/* Report a read-only lvalue.  */
	إذا (TYPE_READONLY (argtype))
	  {
	    readonly_error (location, arg,
			    ((code == PREINCREMENT_تعبير
			      || code == POSTINCREMENT_تعبير)
			     ? lv_increment : lv_decrement));
	    أرجع error_mark_عقدة;
	  }
	وإلا إذا (شجرة_READONLY (arg))
	  readonly_warning (arg,
			    ((code == PREINCREMENT_تعبير
			      || code == POSTINCREMENT_تعبير)
			     ? lv_increment : lv_decrement));

	/* If the argument is atomic, use the special code sequences for
	   atomic compound assignment.  */
	إذا (atomic_op)
	  {
	    arg = stabilize_reference (arg);
	    ret = build_atomic_assign (location, arg,
				       ((code == PREINCREMENT_تعبير
					 || code == POSTINCREMENT_تعبير)
					? PLUS_تعبير
					: MINUS_تعبير),
				       (FRACT_MODE_P (TYPE_MODE (argtype))
					? inc
					: integer_one_عقدة),
				       (code == POSTINCREMENT_تعبير
					|| code == POSTDECREMENT_تعبير));
	    اذهب return_build_unary_op;
	  }

	شجرة true_res;
	إذا (c_hardbool_type_attr (شجرة_TYPE (arg), عدم, &true_res))
	  {
	    شجرة larg = stabilize_reference (arg);
	    شجرة sarg = save_تعبير (larg);
	    بدل (code)
	      {
	      حالة PREINCREMENT_تعبير:
		val = build2 (MODIFY_تعبير, شجرة_TYPE (larg), larg, true_res);
		val = build2 (COMPOUND_تعبير, شجرة_TYPE (larg), sarg, val);
		اكسر;
	      حالة POSTINCREMENT_تعبير:
		val = build2 (MODIFY_تعبير, شجرة_TYPE (larg), larg, true_res);
		val = build2 (COMPOUND_تعبير, شجرة_TYPE (larg), val, sarg);
		val = build2 (COMPOUND_تعبير, شجرة_TYPE (larg), sarg, val);
		اكسر;
	      حالة PREDECREMENT_تعبير:
		{
		  شجرة rarg = convert_lvalue_to_rvalue (location, sarg,
							true, true);
		  rarg = invert_truthvalue_loc (location, rarg);
		  rarg = convert (شجرة_TYPE (sarg), rarg);
		  val = build2 (MODIFY_تعبير, شجرة_TYPE (larg), larg, rarg);
		}
		اكسر;
	      حالة POSTDECREMENT_تعبير:
		{
		  شجرة rarg = convert_lvalue_to_rvalue (location, sarg,
							true, true);
		  rarg = invert_truthvalue_loc (location, rarg);
		  شجرة iarg = convert (شجرة_TYPE (larg), rarg);
		  val = build2 (MODIFY_تعبير, شجرة_TYPE (larg), larg, iarg);
		  val = build2 (COMPOUND_تعبير, شجرة_TYPE (larg), val, sarg);
		  val = build2 (COMPOUND_تعبير, شجرة_TYPE (larg), sarg, val);
		}
		اكسر;
	      افتراضي:
		gcc_unreachable ();
	      }
	    شجرة_SIDE_EFFECTS (val) = 1;
	  }
	وإلا إذا (C_BOOLEAN_TYPE_P (شجرة_TYPE (arg)))
	  val = boolean_increment (code, arg);
	وإلا
	  val = build2 (code, شجرة_TYPE (arg), arg, inc);
	شجرة_SIDE_EFFECTS (val) = 1;
	إذا (TYPE_QUALS (شجرة_TYPE (val)) != TYPE_UNQUALIFIED)
	  شجرة_TYPE (val) = c_build_qualified_type (شجرة_TYPE (val),
						    TYPE_UNQUALIFIED);
	ret = val;
	اذهب return_build_unary_op;
      }

    حالة ADDR_تعبير:
      /* Note that this operation never does default_conversion.  */

      /* The operand of unary '&' must be an lvalue (which excludes
	 expressions of type void), or, in C99, the result of a [] or
	 unary '*' operator.  */
      إذا (VOID_TYPE_P (شجرة_TYPE (arg))
	  && TYPE_QUALS (شجرة_TYPE (arg)) == TYPE_UNQUALIFIED
	  && (!INDIRECT_REF_P (arg) || !flag_isoc99))
	pedwarn (location, 0, "taking address of expression of type %<void%>");

      /* Let &* cancel out to simplify resulting code.  */
      إذا (INDIRECT_REF_P (arg))
	{
	  /* Don't let this be an lvalue.  */
	  إذا (lvalue_p (شجرة_OPERAND (arg, 0)))
	    أرجع non_lvalue_loc (location, شجرة_OPERAND (arg, 0));
	  ret = شجرة_OPERAND (arg, 0);
	  اذهب return_build_unary_op;
	}

      /* Anything not already handled and not a true memory reference
	 or a non-lvalue array is an error.  */
      إذا (typecode != FUNCTION_TYPE && !noconvert
	  && !lvalue_or_else (location, arg, lv_addressof))
	أرجع error_mark_عقدة;

      /* Move address operations inside C_MAYBE_CONST_EXPR to simplify
	 folding later.  */
      إذا (شجرة_CODE (arg) == C_MAYBE_CONST_تعبير)
	{
	  شجرة inner = build_unary_op (location, code,
				       C_MAYBE_CONST_تعبير_تعبير (arg),
				       noconvert);
	  ret = build2 (C_MAYBE_CONST_تعبير, شجرة_TYPE (inner),
			C_MAYBE_CONST_تعبير_PRE (arg), inner);
	  gcc_assert (!C_MAYBE_CONST_تعبير_INT_OPERANDS (arg));
	  C_MAYBE_CONST_تعبير_NON_CONST (ret)
	    = C_MAYBE_CONST_تعبير_NON_CONST (arg);
	  اذهب return_build_unary_op;
	}

      /* Ordinary case; arg is a COMPONENT_REF or a decl.  */

      argtype = شجرة_TYPE (arg);

      /* If the lvalue is const or volatile, merge that into the type
	 to which the address will point.  This is only needed
	 for function types.  */
      إذا ((DECL_P (arg) || REFERENCE_CLASS_P (arg))
	  && (شجرة_READONLY (arg) || شجرة_THIS_VOLATILE (arg))
	  && شجرة_CODE (argtype) == FUNCTION_TYPE)
	{
	  صحيح orig_quals = TYPE_QUALS (strip_array_types (argtype));
	  صحيح quals = orig_quals;

	  إذا (شجرة_READONLY (arg))
	    quals |= TYPE_QUAL_CONST;
	  إذا (شجرة_THIS_VOLATILE (arg))
	    quals |= TYPE_QUAL_VOLATILE;

	  argtype = c_build_qualified_type (argtype, quals);
	}

      بدل (شجرة_CODE (arg))
	{
	حالة COMPONENT_REF:
	  إذا (DECL_C_BIT_FIELD (شجرة_OPERAND (arg, 1)))
	    {
	      error_at (location, "cannot take address of bit-field %qD",
			شجرة_OPERAND (arg, 1));
	      أرجع error_mark_عقدة;
	    }

	  /* fall through */

	حالة ARRAY_REF:
	  إذا (TYPE_REVERSE_STORAGE_ORDER (شجرة_TYPE (شجرة_OPERAND (arg, 0))))
	    {
	      إذا (!AGGREGATE_TYPE_P (شجرة_TYPE (arg))
		  && !POINTER_TYPE_P (شجرة_TYPE (arg))
		  && !VECTOR_TYPE_P (شجرة_TYPE (arg)))
		{
		  error_at (location, "cannot take address of scalar with "
			    "reverse storage order");
		  أرجع error_mark_عقدة;
		}

	      إذا (شجرة_CODE (شجرة_TYPE (arg)) == ARRAY_TYPE
		  && TYPE_REVERSE_STORAGE_ORDER (شجرة_TYPE (arg)))
		warning_at (location, OPT_Wscalar_storage_order,
			    "address of array with reverse scalar storage "
			    "order requested");
	    }

	افتراضي:
	  اكسر;
	}

      إذا (!c_mark_addressable (arg))
	أرجع error_mark_عقدة;

      gcc_assert (شجرة_CODE (arg) != COMPONENT_REF
		  || !DECL_C_BIT_FIELD (شجرة_OPERAND (arg, 1)));

      argtype = c_build_pointer_type (argtype);

      /* ??? Cope with user tricks that amount to offsetof.  Delete this
	 when we have proper support for integer constant expressions.  */
      val = get_base_address (arg);
      إذا (val && INDIRECT_REF_P (val)
          && شجرة_CONSTANT (شجرة_OPERAND (val, 0)))
	{
	  ret = fold_offsetof (arg, argtype);
	  اذهب return_build_unary_op;
	}

      val = build1 (ADDR_تعبير, argtype, arg);

      ret = val;
      اذهب return_build_unary_op;

    حالة PAREN_تعبير:
      ret = build1 (code, شجرة_TYPE (arg), arg);
      اذهب return_build_unary_op;

    افتراضي:
      gcc_unreachable ();
    }

  إذا (argtype == NULL_شجرة)
    argtype = شجرة_TYPE (arg);
  إذا (شجرة_CODE (arg) == INTEGER_CST)
    ret = (require_constant_قيمة
	   ? fold_build1_initializer_loc (location, code, argtype, arg)
	   : fold_build1_loc (location, code, argtype, arg));
  وإلا
    ret = build1 (code, argtype, arg);
 return_build_unary_op:
  gcc_assert (ret != error_mark_عقدة);
  إذا (شجرة_CODE (ret) == INTEGER_CST && !شجرة_OVERFLOW (ret)
      && !(شجرة_CODE (xarg) == INTEGER_CST && !شجرة_OVERFLOW (xarg)))
    ret = build1 (NOP_تعبير, شجرة_TYPE (ret), ret);
  وإلا إذا (شجرة_CODE (ret) != INTEGER_CST && int_operands)
    ret = note_integer_operands (ret);
  إذا (eptype)
    ret = build1 (EXCESS_PRECISION_تعبير, eptype, ret);
  protected_set_تعبير_location (ret, location);
  أرجع ret;
}

/* Return nonzero if REF is an lvalue valid for this language.
   Lvalues can be assigned, unless their type has TYPE_READONLY.
   Lvalues can have their address taken, unless they have C_DECL_REGISTER.  */

منطقي
lvalue_p (const_شجرة ref)
{
  ثابت تعداد شجرة_code code = شجرة_CODE (ref);

  بدل (code)
    {
    حالة REALPART_تعبير:
    حالة IMAGPART_تعبير:
    حالة COMPONENT_REF:
      أرجع lvalue_p (شجرة_OPERAND (ref, 0));

    حالة C_MAYBE_CONST_تعبير:
      أرجع lvalue_p (شجرة_OPERAND (ref, 1));

    حالة COMPOUND_LITERAL_تعبير:
    حالة STRING_CST:
      أرجع true;

    حالة MEM_REF:
    حالة TARGET_MEM_REF:
      /* MEM_REFs can appear from -fgimple parsing or folding, so allow them
	 here as well.  */
    حالة INDIRECT_REF:
    حالة ARRAY_REF:
    حالة VAR_DECL:
    حالة PARM_DECL:
    حالة RESULT_DECL:
    حالة ERROR_MARK:
      أرجع (شجرة_CODE (شجرة_TYPE (ref)) != FUNCTION_TYPE
	      && شجرة_CODE (شجرة_TYPE (ref)) != METHOD_TYPE);

    حالة BIND_تعبير:
      أرجع شجرة_CODE (شجرة_TYPE (ref)) == ARRAY_TYPE;

    حالة CALL_تعبير:
      أرجع is_access_with_size_p (ref);

    افتراضي:
      أرجع خطأ;
    }
}

/* Give a warning for storing in something that is read-only in GCC
   terms but not const in ISO C terms.  */

ساكن فراغ
readonly_warning (شجرة arg, تعداد lvalue_use use)
{
  بدل (use)
    {
    حالة lv_assign:
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
lvalue_or_else (location_t loc, const_شجرة ref, تعداد lvalue_use use)
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
c_mark_addressable (شجرة exp, منطقي array_ref_p, منطقي override_register)
{
  شجرة x = exp;

  طالما (1)
    بدل (شجرة_CODE (x))
      {
      حالة VIEW_CONVERT_تعبير:
	إذا (array_ref_p
	    && شجرة_CODE (شجرة_TYPE (x)) == ARRAY_TYPE
	    && VECTOR_TYPE_P (شجرة_TYPE (شجرة_OPERAND (x, 0))))
	  أرجع true;
	x = شجرة_OPERAND (x, 0);
	اكسر;

      حالة COMPONENT_REF:
	إذا (DECL_C_BIT_FIELD (شجرة_OPERAND (x, 1)))
	  {
	    error ("cannot take address of bit-field %qD",
		   شجرة_OPERAND (x, 1));
	    أرجع خطأ;
	  }
	/* FALLTHRU */
      حالة ADDR_تعبير:
      حالة ARRAY_REF:
      حالة REALPART_تعبير:
      حالة IMAGPART_تعبير:
	x = شجرة_OPERAND (x, 0);
	اكسر;

      حالة COMPOUND_LITERAL_تعبير:
	إذا (C_DECL_REGISTER (COMPOUND_LITERAL_تعبير_DECL (x)))
	  {
	    إذا (override_register)
	      DECL_REGISTER (COMPOUND_LITERAL_تعبير_DECL (x)) = 0;
	    وإلا
	      {
		error ("address of register compound literal requested");
		أرجع خطأ;
	      }
	  }
	شجرة_ADDRESSABLE (x) = 1;
	شجرة_ADDRESSABLE (COMPOUND_LITERAL_تعبير_DECL (x)) = 1;
	أرجع true;

      حالة CONSTRUCTOR:
	شجرة_ADDRESSABLE (x) = 1;
	أرجع true;

      حالة VAR_DECL:
      حالة CONST_DECL:
      حالة PARM_DECL:
      حالة RESULT_DECL:
	إذا (C_DECL_REGISTER (x)
	    && DECL_NONLOCAL (x))
	  {
	    إذا (شجرة_PUBLIC (x) || is_global_var (x))
	      {
		error
		  ("global register variable %qD used in nested function", x);
		أرجع خطأ;
	      }
	    pedwarn (مدخل_location, 0, "register variable %qD used in nested function", x);
	  }
	وإلا إذا (C_DECL_REGISTER (x))
	  {
	    إذا (شجرة_PUBLIC (x) || is_global_var (x))
	      error ("address of global register variable %qD requested", x);
	    وإلا إذا (override_register && !DECL_HARD_REGISTER (x))
	      {
		DECL_REGISTER (x) = 0;
		شجرة_ADDRESSABLE (x) = 1;
		mark_decl_used (x, true);
		أرجع true;
	      }
	    وإلا
	      error ("address of register variable %qD requested", x);
	    أرجع خطأ;
	  }

	/* FALLTHRU */
      حالة FUNCTION_DECL:
	شجرة_ADDRESSABLE (x) = 1;
	mark_decl_used (x, true);
	/* FALLTHRU */
      افتراضي:
	أرجع true;
    }
}

/* Convert EXPR to TYPE, warning about conversion problems with
   constants.  SEMANTIC_TYPE is the type this conversion would use
   without excess precision. If SEMANTIC_TYPE is NULL, this function
   is equivalent to convert_and_check. This function is a wrapper that
   handles conversions that may be different than
   the usual ones because of excess precision.  */

ساكن شجرة
ep_convert_and_check (location_t loc, شجرة type, شجرة تعبير,
		      شجرة semantic_type)
{
  إذا (شجرة_TYPE (تعبير) == type)
    أرجع تعبير;

  /* For C11, integer conversions may have results with excess
     precision.  */
  إذا (flag_isoc11 || !semantic_type)
    أرجع convert_and_check (loc, type, تعبير);

  إذا (شجرة_CODE (شجرة_TYPE (تعبير)) == INTEGER_TYPE
      && شجرة_TYPE (تعبير) != semantic_type)
    {
      /* For integers, we need to check the real conversion, not
	 the conversion to the excess precision type.  */
      تعبير = convert_and_check (loc, semantic_type, تعبير);
    }
  /* Result type is the excess precision type, which should be
     large enough, so do not check.  */
  أرجع convert (type, تعبير);
}

/* If EXPR refers to a built-in declared without a prototype returns
   the actual type of the built-in and, if non-null, set *BLTIN to
   a pointer to the built-in.  Otherwise return the type of EXPR
   and clear *BLTIN if non-null.  */

ساكن شجرة
type_or_builtin_type (شجرة تعبير, شجرة *bltin = عدم)
{
  شجرة dummy;
  إذا (!bltin)
    bltin = &dummy;

  *bltin = NULL_شجرة;

  شجرة type = شجرة_TYPE (تعبير);
  إذا (شجرة_CODE (تعبير) != ADDR_تعبير)
    أرجع type;

  شجرة oper = شجرة_OPERAND (تعبير, 0);
  إذا (!DECL_P (oper)
      || شجرة_CODE (oper) != FUNCTION_DECL
      || !fndecl_built_in_p (oper, BUILT_IN_NORMAL))
    أرجع type;

  built_in_function code = DECL_FUNCTION_CODE (oper);
  إذا (!C_DECL_BUILTIN_PROTOTYPE (oper))
    أرجع type;

  إذا ((*bltin = builtin_decl_implicit (code)))
    type = c_build_pointer_type (شجرة_TYPE (*bltin));

  أرجع type;
}

/* Build and return a conditional expression IFEXP ? OP1 : OP2.  If
   IFEXP_BCP then the condition is a call to __builtin_constant_p, and
   if folded to an integer constant then the unselected half may
   contain arbitrary operations not normally permitted in constant
   expressions.  Set the location of the expression to LOC.  */

شجرة
build_conditional_تعبير (location_t colon_loc, شجرة ifexp, منطقي ifexp_bcp,
			شجرة op1, شجرة op1_original_type, location_t op1_loc,
			شجرة op2, شجرة op2_original_type, location_t op2_loc)
{
  شجرة type1;
  شجرة type2;
  شجرة result_type = عدم;
  شجرة semantic_result_type = عدم;
  شجرة orig_op1 = op1, orig_op2 = op2;
  منطقي int_const, op1_int_operands, op2_int_operands, int_operands;
  منطقي ifexp_int_operands;
  شجرة ret;

  op1_int_operands = تعبير_INT_CONST_OPERANDS (orig_op1);
  إذا (op1_int_operands)
    op1 = remove_c_maybe_const_تعبير (op1);
  op2_int_operands = تعبير_INT_CONST_OPERANDS (orig_op2);
  إذا (op2_int_operands)
    op2 = remove_c_maybe_const_تعبير (op2);
  ifexp_int_operands = تعبير_INT_CONST_OPERANDS (ifexp);
  إذا (ifexp_int_operands)
    ifexp = remove_c_maybe_const_تعبير (ifexp);

  /* Promote both alternatives.  */

  إذا (شجرة_CODE (شجرة_TYPE (op1)) != VOID_TYPE)
    op1 = default_conversion (op1);
  إذا (شجرة_CODE (شجرة_TYPE (op2)) != VOID_TYPE)
    op2 = default_conversion (op2);

  إذا (شجرة_CODE (ifexp) == ERROR_MARK
      || شجرة_CODE (شجرة_TYPE (op1)) == ERROR_MARK
      || شجرة_CODE (شجرة_TYPE (op2)) == ERROR_MARK)
    أرجع error_mark_عقدة;

  شجرة bltin1 = NULL_شجرة;
  شجرة bltin2 = NULL_شجرة;
  type1 = type_or_builtin_type (op1, &bltin1);
  ثابت تعداد شجرة_code code1 = شجرة_CODE (type1);
  type2 = type_or_builtin_type (op2, &bltin2);
  ثابت تعداد شجرة_code code2 = شجرة_CODE (type2);

  إذا (code1 == POINTER_TYPE && reject_gcc_builtin (op1))
    أرجع error_mark_عقدة;

  إذا (code2 == POINTER_TYPE && reject_gcc_builtin (op2))
    أرجع error_mark_عقدة;

  /* C90 does not permit non-lvalue arrays in conditional expressions.
     In C99 they will be pointers by now.  */
  إذا (code1 == ARRAY_TYPE || code2 == ARRAY_TYPE)
    {
      error_at (colon_loc, "non-lvalue array in conditional expression");
      أرجع error_mark_عقدة;
    }

  إذا ((شجرة_CODE (op1) == EXCESS_PRECISION_تعبير
       || شجرة_CODE (op2) == EXCESS_PRECISION_تعبير)
      && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	  || code1 == COMPLEX_TYPE || code1 == BITINT_TYPE)
      && (code2 == INTEGER_TYPE || code2 == REAL_TYPE
	  || code2 == COMPLEX_TYPE || code2 == BITINT_TYPE))
    {
      semantic_result_type = c_common_type (type1, type2);
      إذا (شجرة_CODE (op1) == EXCESS_PRECISION_تعبير)
	{
	  op1 = شجرة_OPERAND (op1, 0);
	  type1 = شجرة_TYPE (op1);
	  gcc_assert (شجرة_CODE (type1) == code1);
	}
      إذا (شجرة_CODE (op2) == EXCESS_PRECISION_تعبير)
	{
	  op2 = شجرة_OPERAND (op2, 0);
	  type2 = شجرة_TYPE (op2);
	  gcc_assert (شجرة_CODE (type2) == code2);
	}
    }

  إذا (warn_cxx_compat)
    {
      شجرة t1 = op1_original_type ? op1_original_type : شجرة_TYPE (orig_op1);
      شجرة t2 = op2_original_type ? op2_original_type : شجرة_TYPE (orig_op2);

      إذا (شجرة_CODE (t1) == ENUMERAL_TYPE
	  && شجرة_CODE (t2) == ENUMERAL_TYPE
	  && TYPE_MAIN_VARIANT (t1) != TYPE_MAIN_VARIANT (t2))
	warning_at (colon_loc, OPT_Wc___compat,
		    "different enum types in conditional is "
		    "invalid in C++: %qT vs %qT", t1, t2);
    }

  إذا (warn_zero_as_null_pointer_constant
      && c_inhibit_evaluation_warnings == 0)
    {
      إذا ((code1 == POINTER_TYPE || code1 == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type2) && null_pointer_constant_p (orig_op2))
	warning_at (op2_loc, OPT_Wzero_as_null_pointer_constant,
		    "zero as null pointer constant");

      إذا ((code2 == POINTER_TYPE || code2 == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type1) && null_pointer_constant_p (orig_op1))
	warning_at (op1_loc, OPT_Wzero_as_null_pointer_constant,
		    "zero as null pointer constant");
    }

  /* Quickly detect the usual case where op1 and op2 have the same type
     after promotion.  */
  إذا (TYPE_MAIN_VARIANT (type1) == TYPE_MAIN_VARIANT (type2))
    {
      إذا (type1 == type2)
	result_type = type1;
      وإلا
	result_type = TYPE_MAIN_VARIANT (type1);
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
      شجرة eptype1 = type1;
      شجرة eptype2 = type2;
      إذا (flag_isoc11)
	{
	  شجرة eptype;
	  إذا (ANY_INTEGRAL_TYPE_P (type1)
	      && (eptype = excess_precision_type (type2)) != NULL_شجرة)
	    {
	      eptype2 = eptype;
	      إذا (!semantic_result_type)
		semantic_result_type = c_common_type (type1, type2);
	    }
	  وإلا إذا (ANY_INTEGRAL_TYPE_P (type2)
		   && (eptype = excess_precision_type (type1)) != NULL_شجرة)
	    {
	      eptype1 = eptype;
	      إذا (!semantic_result_type)
		semantic_result_type = c_common_type (type1, type2);
	    }
	}
      result_type = c_common_type (eptype1, eptype2);
      إذا (result_type == error_mark_عقدة)
	أرجع error_mark_عقدة;
      do_warn_double_promotion (result_type, type1, type2,
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
	  صحيح unsigned_op1 = TYPE_UNSIGNED (شجرة_TYPE (orig_op1));
	  صحيح unsigned_op2 = TYPE_UNSIGNED (شجرة_TYPE (orig_op2));

	  إذا (unsigned_op1 ^ unsigned_op2)
	    {
	      /* Do not warn if the result type is signed, since the
		 signed type will only be chosen if it can represent
		 all the values of the unsigned type.  */
	      إذا (!TYPE_UNSIGNED (result_type))
		/* OK */;
	      وإلا
		{
		  منطقي op1_maybe_const = true;
		  منطقي op2_maybe_const = true;

		  /* Do not warn if the signed quantity is an
		     unsuffixed integer literal (or some static
		     constant expression involving such literals) and
		     it is non-negative.  This warning requires the
		     operands to be folded for best results, so do
		     that folding in this case even without
		     warn_sign_compare to avoid warning options
		     possibly affecting code generation.  */
		  c_inhibit_evaluation_warnings
		    += (ifexp == truthvalue_false_عقدة);
		  op1 = c_fully_fold (op1, require_constant_قيمة,
				      &op1_maybe_const);
		  c_inhibit_evaluation_warnings
		    -= (ifexp == truthvalue_false_عقدة);

		  c_inhibit_evaluation_warnings
		    += (ifexp == truthvalue_true_عقدة);
		  op2 = c_fully_fold (op2, require_constant_قيمة,
				      &op2_maybe_const);
		  c_inhibit_evaluation_warnings
		    -= (ifexp == truthvalue_true_عقدة);

		  إذا (warn_sign_compare)
		    {
		      إذا ((unsigned_op2
			   && شجرة_تعبير_nonnegative_p (op1))
			  || (unsigned_op1
			      && شجرة_تعبير_nonnegative_p (op2)))
			/* OK */;
		      وإلا إذا (unsigned_op2)
			warning_at (op1_loc, OPT_Wsign_compare,
				    "operand of %<?:%> changes signedness from "
				    "%qT to %qT due to unsignedness of other "
				    "operand", شجرة_TYPE (orig_op1),
				    شجرة_TYPE (orig_op2));
		      وإلا
			warning_at (op2_loc, OPT_Wsign_compare,
				    "operand of %<?:%> changes signedness from "
				    "%qT to %qT due to unsignedness of other "
				    "operand", شجرة_TYPE (orig_op2),
				    شجرة_TYPE (orig_op1));
		    }
		  إذا (!op1_maybe_const || شجرة_CODE (op1) != INTEGER_CST)
		    op1 = c_wrap_maybe_const (op1, !op1_maybe_const);
		  إذا (!op2_maybe_const || شجرة_CODE (op2) != INTEGER_CST)
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
      result_type = void_type_عقدة;
    }
  وإلا إذا (code1 == POINTER_TYPE && code2 == POINTER_TYPE)
    {
      addr_space_t as1 = TYPE_ADDR_SPACE (شجرة_TYPE (type1));
      addr_space_t as2 = TYPE_ADDR_SPACE (شجرة_TYPE (type2));
      addr_space_t as_common;

      إذا (comp_target_types (colon_loc, type1, type2))
	{
	  ifexp = save_تعبير (ifexp);
	  result_type = common_pointer_type (type1, type2, ifexp);
	}
      وإلا إذا (null_pointer_constant_p (orig_op1))
	result_type = type2;
      وإلا إذا (null_pointer_constant_p (orig_op2))
	result_type = type1;
      وإلا إذا (!addr_space_superset (as1, as2, &as_common))
	{
	  error_at (colon_loc, "pointers to disjoint address spaces "
		    "used in conditional expression");
	  أرجع error_mark_عقدة;
	}
      وإلا إذا ((VOID_TYPE_P (شجرة_TYPE (type1))
		&& !TYPE_ATOMIC (شجرة_TYPE (type1)))
	       || (VOID_TYPE_P (شجرة_TYPE (type2))
		   && !TYPE_ATOMIC (شجرة_TYPE (type2))))
	{
	  شجرة t1 = شجرة_TYPE (type1);
	  شجرة t2 = شجرة_TYPE (type2);
	  إذا (!(VOID_TYPE_P (t1)
		&& !TYPE_ATOMIC (t1)))
	   {
	     /* roles are swapped */
	     t1 = t2;
	     t2 = شجرة_TYPE (type1);
	   }
	  شجرة t2_stripped = strip_array_types (t2);
	  إذا ((شجرة_CODE (t2) == ARRAY_TYPE)
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
	  إذا (شجرة_CODE (t2) == FUNCTION_TYPE)
	    pedwarn (colon_loc, OPT_Wpedantic,
		     "ISO C forbids conditional expr between "
		     "%<void *%> and function pointer");
	  /* for array, use qualifiers of element type */
	  إذا (flag_isoc23)
	    t2 = t2_stripped;
	  result_type = c_build_pointer_type (qualify_type (t1, t2));
	}
      /* Objective-C pointer comparisons are a bit more lenient.  */
      وإلا إذا (objc_have_common_type (type1, type2, -3, NULL_شجرة))
	result_type = objc_common_type (type1, type2);
      وإلا
	{
	  صحيح qual = ENCODE_QUAL_ADDR_SPACE (as_common);
	  تعداد diagnostics::kind kind = diagnostics::kind::permerror;
	  إذا (!flag_isoc99)
	    /* This downgrade to a warning ensures that -std=gnu89
	       -pedantic-errors does not flag these mismatches between
	       builtins as errors (as diagnostics::kind::permerror would)
	       ISO C99 and later do not have implicit function declarations,
	       so the mismatch cannot occur naturally there.  */
	    kind = (bltin1 && bltin2
		    ? diagnostics::kind::warning
		    : diagnostics::kind::pedwarn);
	  إذا (emit_diagnostic (kind, colon_loc, OPT_Wincompatible_pointer_types,
			       "pointer type mismatch "
			       "in conditional expression"))
	    {
	      inform (op1_loc, "first expression has type %qT", type1);
	      inform (op2_loc, "second expression has type %qT", type2);
	    }
	  result_type = c_build_pointer_type
			  (c_build_qualified_type (void_type_عقدة, qual));
	}
    }
  وإلا إذا (code1 == POINTER_TYPE
	   && (code2 == INTEGER_TYPE || code2 == BITINT_TYPE))
    {
      إذا (!null_pointer_constant_p (orig_op2))
	permerror_opt (colon_loc, OPT_Wint_conversion,
		       "pointer/integer type mismatch "
		       "in conditional expression");
      وإلا
	{
	  op2 = null_pointer_عقدة;
	}
      result_type = type1;
    }
  وإلا إذا (code2 == POINTER_TYPE
	   && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
    {
      إذا (!null_pointer_constant_p (orig_op1))
	permerror_opt (colon_loc, OPT_Wint_conversion,
		       "pointer/integer type mismatch "
		       "in conditional expression");
      وإلا
	{
	  op1 = null_pointer_عقدة;
	}
      result_type = type2;
    }
  /* 6.5.15: "if one is a null pointer constant (other than a pointer) or has
     type nullptr_t and the other is a pointer, the result type is the pointer
     type."  */
  وإلا إذا (code1 == NULLPTR_TYPE && code2 == POINTER_TYPE)
    result_type = type2;
  وإلا إذا (code1 == POINTER_TYPE && code2 == NULLPTR_TYPE)
    result_type = type1;
  وإلا إذا (RECORD_OR_UNION_TYPE_P (type1) && RECORD_OR_UNION_TYPE_P (type2)
	   && comptypes (TYPE_MAIN_VARIANT (type1),
			 TYPE_MAIN_VARIANT (type2)))
    result_type = composite_type (TYPE_MAIN_VARIANT (type1),
				  TYPE_MAIN_VARIANT (type2));

  إذا (!result_type)
    {
      إذا (flag_cond_mismatch)
	result_type = void_type_عقدة;
      وإلا
	{
	  error_at (colon_loc, "type mismatch in conditional expression");
	  أرجع error_mark_عقدة;
	}
    }

  /* Merge const and volatile flags of the incoming types.  */
  result_type
    = build_type_variant (result_type,
			  TYPE_READONLY (type1) || TYPE_READONLY (type2),
			  TYPE_VOLATILE (type1) || TYPE_VOLATILE (type2));

  op1 = ep_convert_and_check (colon_loc, result_type, op1,
			      semantic_result_type);
  op2 = ep_convert_and_check (colon_loc, result_type, op2,
			      semantic_result_type);

  إذا (ifexp_bcp && ifexp == truthvalue_true_عقدة)
    {
      op2_int_operands = true;
      op1 = c_fully_fold (op1, require_constant_قيمة, عدم);
    }
  إذا (ifexp_bcp && ifexp == truthvalue_false_عقدة)
    {
      op1_int_operands = true;
      op2 = c_fully_fold (op2, require_constant_قيمة, عدم);
    }
  int_const = int_operands = (ifexp_int_operands
			      && op1_int_operands
			      && op2_int_operands);
  إذا (int_operands)
    {
      int_const = ((ifexp == truthvalue_true_عقدة
		    && شجرة_CODE (orig_op1) == INTEGER_CST
		    && !شجرة_OVERFLOW (orig_op1))
		   || (ifexp == truthvalue_false_عقدة
		       && شجرة_CODE (orig_op2) == INTEGER_CST
		       && !شجرة_OVERFLOW (orig_op2)));
    }

  /* Need to convert condition operand into a vector mask.  */
  إذا (VECTOR_TYPE_P (شجرة_TYPE (ifexp)))
    {
      شجرة vectype = شجرة_TYPE (ifexp);
      شجرة elem_type = شجرة_TYPE (vectype);
      شجرة zero = build_int_cst (elem_type, 0);
      شجرة zero_vec = build_vector_from_val (vectype, zero);
      شجرة cmp_type = truth_type_for (vectype);
      ifexp = build2 (NE_تعبير, cmp_type, ifexp, zero_vec);
    }

  إذا (int_const || (ifexp_bcp && شجرة_CODE (ifexp) == INTEGER_CST))
    ret = fold_build3_loc (colon_loc, COND_تعبير, result_type, ifexp, op1, op2);
  وإلا
    {
      إذا (int_operands)
	{
	  /* Use c_fully_fold here, since C_MAYBE_CONST_EXPR might be
	     nested inside of the expression.  */
	  op1 = c_fully_fold (op1, خطأ, عدم);
	  op2 = c_fully_fold (op2, خطأ, عدم);
	}
      ret = build3 (COND_تعبير, result_type, ifexp, op1, op2);
      إذا (int_operands)
	ret = note_integer_operands (ret);
    }
  إذا (semantic_result_type)
    ret = build1 (EXCESS_PRECISION_تعبير, semantic_result_type, ret);

  protected_set_تعبير_location (ret, colon_loc);

  /* If the OP1 and OP2 are the same and don't have side-effects,
     warn here, because the COND_EXPR will be turned into OP1.  */
  إذا (warn_duplicated_branches
      && شجرة_CODE (ret) == COND_تعبير
      && (op1 == op2 || operand_equal_p (op1, op2, OEP_ADDRESS_OF_SAME_FIELD)))
    warning_at (تعبير_LOCATION (ret), OPT_Wduplicated_branches,
		"this condition has identical branches");

  أرجع ret;
}

/* EXPR is an expression, location LOC, whose result is discarded.
   Warn if it is a call to a nodiscard function (or a COMPOUND_EXPR
   whose right-hand operand is such a call, possibly recursively).  */

ساكن فراغ
maybe_warn_nodiscard (location_t loc, شجرة تعبير)
{
  إذا (VOID_TYPE_P (شجرة_TYPE (تعبير)))
    أرجع;
  طالما (شجرة_CODE (تعبير) == COMPOUND_تعبير)
    {
      تعبير = شجرة_OPERAND (تعبير, 1);
      إذا (تعبير_HAS_LOCATION (تعبير))
	loc = تعبير_LOCATION (تعبير);
    }
  إذا (شجرة_CODE (تعبير) != CALL_تعبير)
    أرجع;
  شجرة fn = CALL_تعبير_FN (تعبير);
  إذا (!fn)
    أرجع;
  شجرة attr;
  إذا (شجرة_CODE (fn) == ADDR_تعبير
      && شجرة_CODE (شجرة_OPERAND (fn, 0)) == FUNCTION_DECL
      && (attr = lookup_attribute ("nodiscard",
				   DECL_ATTRIBUTES (شجرة_OPERAND (fn, 0)))))
    {
      fn = شجرة_OPERAND (fn, 0);
      شجرة وسائط = شجرة_قيمة (attr);
      إذا (وسائط)
	وسائط = شجرة_قيمة (وسائط);
      auto_diagnostic_group d;
      auto_urlify_attributes sentinel;
      صحيح warned;
      إذا (وسائط)
	warned = warning_at (loc, OPT_Wunused_result,
			     "ignoring return value of %qD, declared with "
			     "attribute %<nodiscard%>: %E", fn, وسائط);
      وإلا
	warned = warning_at (loc, OPT_Wunused_result,
			     "ignoring return value of %qD, declared with "
			     "attribute %<nodiscard%>", fn);
      إذا (warned)
	inform (DECL_SOURCE_LOCATION (fn), "declared here");
    }
  وإلا
    {
      شجرة rettype = شجرة_TYPE (شجرة_TYPE (شجرة_TYPE (fn)));
      attr = lookup_attribute ("nodiscard", TYPE_ATTRIBUTES (rettype));
      إذا (!attr)
	أرجع;
      شجرة وسائط = شجرة_قيمة (attr);
      إذا (وسائط)
	وسائط = شجرة_قيمة (وسائط);
      auto_diagnostic_group d;
      auto_urlify_attributes sentinel;
      صحيح warned;
      إذا (وسائط)
	warned = warning_at (loc, OPT_Wunused_result,
			     "ignoring return value of type %qT, declared "
			     "with attribute %<nodiscard%>: %E",
			     rettype, وسائط);
      وإلا
	warned = warning_at (loc, OPT_Wunused_result,
			     "ignoring return value of type %qT, declared "
			     "with attribute %<nodiscard%>", rettype);
      إذا (warned)
	{
	  إذا (شجرة_CODE (fn) == ADDR_تعبير)
	    {
	      fn = شجرة_OPERAND (fn, 0);
	      إذا (شجرة_CODE (fn) == FUNCTION_DECL)
		inform (DECL_SOURCE_LOCATION (fn),
			"in call to %qD, declared here", fn);
	    }
	}
    }
}

/* Return a compound expression that performs two expressions and
   returns the value of the second of them.

   LOC is the location of the COMPOUND_EXPR.  */

شجرة
build_compound_تعبير (location_t loc, شجرة expr1, شجرة expr2)
{
  منطقي expr1_int_operands, expr2_int_operands;
  شجرة eptype = NULL_شجرة;
  شجرة ret;

  expr1_int_operands = تعبير_INT_CONST_OPERANDS (expr1);
  إذا (expr1_int_operands)
    expr1 = remove_c_maybe_const_تعبير (expr1);
  expr2_int_operands = تعبير_INT_CONST_OPERANDS (expr2);
  إذا (expr2_int_operands)
    expr2 = remove_c_maybe_const_تعبير (expr2);

  إذا (شجرة_CODE (expr1) == EXCESS_PRECISION_تعبير)
    expr1 = شجرة_OPERAND (expr1, 0);
  إذا (شجرة_CODE (expr2) == EXCESS_PRECISION_تعبير)
    {
      eptype = شجرة_TYPE (expr2);
      expr2 = شجرة_OPERAND (expr2, 0);
    }

  إذا (!شجرة_SIDE_EFFECTS (expr1))
    {
      /* The left-hand operand of a comma expression is like an expression
	 statement: with -Wunused, we should warn if it doesn't have
	 any side-effects, unless it was explicitly cast to (void).  */
      إذا (warn_unused_قيمة)
	{
	  إذا (VOID_TYPE_P (شجرة_TYPE (expr1))
	      && CONVERT_تعبير_P (expr1))
	    ; /* (void) a, b */
	  وإلا إذا (VOID_TYPE_P (شجرة_TYPE (expr1))
		   && شجرة_CODE (expr1) == COMPOUND_تعبير
		   && CONVERT_تعبير_P (شجرة_OPERAND (expr1, 1)))
	    ; /* (void) a, (void) b, c */
	  وإلا
	    warning_at (loc, OPT_Wunused_قيمة,
			"left-hand operand of comma expression has no effect");
	}
    }
  وإلا إذا (شجرة_CODE (expr1) == COMPOUND_تعبير
	   && warn_unused_قيمة)
    {
      شجرة r = expr1;
      location_t cloc = loc;
      طالما (شجرة_CODE (r) == COMPOUND_تعبير)
        {
	  إذا (تعبير_HAS_LOCATION (r))
	    cloc = تعبير_LOCATION (r);
	  r = شجرة_OPERAND (r, 1);
	}
      إذا (!شجرة_SIDE_EFFECTS (r)
	  && !VOID_TYPE_P (شجرة_TYPE (r))
	  && !CONVERT_تعبير_P (r))
	warning_at (cloc, OPT_Wunused_قيمة,
	            "right-hand operand of comma expression has no effect");
    }

  /* With -Wunused, we should also warn if the left-hand operand does have
     side-effects, but computes a value which is not used.  For example, in
     `foo() + bar(), baz()' the result of the `+' operator is not used,
     so we should issue a warning.  */
  وإلا إذا (warn_unused_قيمة)
    warn_if_unused_قيمة (expr1, loc);

  maybe_warn_nodiscard (loc, expr1);

  إذا (expr2 == error_mark_عقدة)
    أرجع error_mark_عقدة;

  ret = build2 (COMPOUND_تعبير, شجرة_TYPE (expr2), expr1, expr2);

  إذا (flag_isoc99
      && expr1_int_operands
      && expr2_int_operands)
    ret = note_integer_operands (ret);

  إذا (eptype)
    ret = build1 (EXCESS_PRECISION_تعبير, eptype, ret);

  protected_set_تعبير_location (ret, loc);
  أرجع ret;
}

/* Issue -Wcast-qual warnings when appropriate.  TYPE is the type to
   which we are casting.  OTYPE is the type of the expression being
   cast.  Both TYPE and OTYPE are pointer types.  LOC is the location
   of the cast.  -Wcast-qual appeared on the command line.  Named
   address space qualifiers are not handled here, because they result
   in different warnings.  */

ساكن فراغ
handle_warn_cast_qual (location_t loc, شجرة type, شجرة otype)
{
  شجرة in_type = type;
  شجرة in_otype = otype;
  صحيح added = 0;
  صحيح discarded = 0;
  منطقي is_const;

  /* Check that the qualifiers on IN_TYPE are a superset of the
     qualifiers of IN_OTYPE.  The outermost level of POINTER_TYPE
     nodes is uninteresting and we stop as soon as we hit a
     non-POINTER_TYPE node on either type.  */
  افعل
    {
      in_otype = شجرة_TYPE (in_otype);
      in_type = شجرة_TYPE (in_type);

      /* GNU C allows cv-qualified function types.  'const' means the
	 function is very pure, 'volatile' means it can't return.  We
	 need to warn when such qualifiers are added, not when they're
	 taken away.  */
      إذا (شجرة_CODE (in_otype) == FUNCTION_TYPE
	  && شجرة_CODE (in_type) == FUNCTION_TYPE)
	added |= (TYPE_QUALS_NO_ADDR_SPACE (in_type)
		  & ~TYPE_QUALS_NO_ADDR_SPACE (in_otype));
      وإلا
	discarded |= (TYPE_QUALS_NO_ADDR_SPACE (in_otype)
		      & ~TYPE_QUALS_NO_ADDR_SPACE (in_type));
    }
  طالما (شجرة_CODE (in_type) == POINTER_TYPE
	 && شجرة_CODE (in_otype) == POINTER_TYPE);

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

  إذا (TYPE_MAIN_VARIANT (in_type) != TYPE_MAIN_VARIANT (in_otype))
    أرجع;
  إذا (شجرة_CODE (شجرة_TYPE (type)) != POINTER_TYPE)
    أرجع;

  in_type = type;
  in_otype = otype;
  is_const = TYPE_READONLY (شجرة_TYPE (in_type));
  افعل
    {
      in_type = شجرة_TYPE (in_type);
      in_otype = شجرة_TYPE (in_otype);
      إذا ((TYPE_QUALS (in_type) &~ TYPE_QUALS (in_otype)) != 0
	  && !is_const)
	{
	  warning_at (loc, OPT_Wcast_qual,
		      "to be safe all intermediate pointers in cast from "
                      "%qT to %qT must be %<const%> qualified",
		      otype, type);
	  اكسر;
	}
      إذا (is_const)
	is_const = TYPE_READONLY (in_type);
    }
  طالما (شجرة_CODE (in_type) == POINTER_TYPE);
}

/* Heuristic check if two parameter types can be considered ABI-equivalent.  */

ساكن منطقي
c_safe_arg_type_equiv_p (شجرة t1, شجرة t2)
{
  إذا (error_operand_p (t1) || error_operand_p (t2))
    أرجع true;

  t1 = TYPE_MAIN_VARIANT (t1);
  t2 = TYPE_MAIN_VARIANT (t2);

  إذا (شجرة_CODE (t1) == POINTER_TYPE
      && شجرة_CODE (t2) == POINTER_TYPE)
    أرجع true;

  /* Only the precision of the parameter matters.  This check should
     make sure that the callee does not see undefined values in argument
     registers.  */
  إذا (INTEGRAL_TYPE_P (t1)
      && INTEGRAL_TYPE_P (t2)
      && TYPE_PRECISION (t1) == TYPE_PRECISION (t2))
    أرجع true;

  أرجع comptypes (t1, t2);
}

/* Check if a type cast between two function types can be considered safe.  */

ساكن منطقي
c_safe_function_type_cast_p (شجرة t1, شجرة t2)
{
  إذا (شجرة_TYPE (t1) == void_type_عقدة &&
      TYPE_ARG_TYPES (t1) == void_list_عقدة)
    أرجع true;

  إذا (شجرة_TYPE (t2) == void_type_عقدة &&
      TYPE_ARG_TYPES (t2) == void_list_عقدة)
    أرجع true;

  إذا (!c_safe_arg_type_equiv_p (شجرة_TYPE (t1), شجرة_TYPE (t2)))
    أرجع خطأ;

  لكل (t1 = TYPE_ARG_TYPES (t1), t2 = TYPE_ARG_TYPES (t2);
       t1 && t2;
       t1 = شجرة_CHAIN (t1), t2 = شجرة_CHAIN (t2))
    إذا (!c_safe_arg_type_equiv_p (شجرة_قيمة (t1), شجرة_قيمة (t2)))
      أرجع خطأ;

  أرجع true;
}

/* Build an expression representing a cast to type TYPE of expression EXPR.
   LOC is the location of the cast-- typically the open paren of the cast.  */

شجرة
build_c_cast (location_t loc, شجرة type, شجرة تعبير)
{
  شجرة قيمة;

  منطقي int_operands = تعبير_INT_CONST_OPERANDS (تعبير);

  إذا (شجرة_CODE (تعبير) == EXCESS_PRECISION_تعبير)
    تعبير = شجرة_OPERAND (تعبير, 0);

  قيمة = تعبير;
  إذا (int_operands)
    قيمة = remove_c_maybe_const_تعبير (قيمة);

  إذا (type == error_mark_عقدة || تعبير == error_mark_عقدة)
    أرجع error_mark_عقدة;

  /* The ObjC front-end uses TYPE_MAIN_VARIANT to tie together types differing
     only in <protocol> qualifications.  But when constructing cast expressions,
     the protocols do matter and must be kept around.  */
  إذا (objc_is_object_ptr (type) && objc_is_object_ptr (شجرة_TYPE (تعبير)))
    أرجع build1 (NOP_تعبير, type, تعبير);

  type = TYPE_MAIN_VARIANT (type);

  إذا (شجرة_CODE (type) == ARRAY_TYPE)
    {
      error_at (loc, "cast specifies array type");
      أرجع error_mark_عقدة;
    }

  إذا (شجرة_CODE (type) == FUNCTION_TYPE)
    {
      error_at (loc, "cast specifies function type");
      أرجع error_mark_عقدة;
    }

  إذا (!VOID_TYPE_P (type))
    {
      قيمة = require_complete_type (loc, قيمة);
      إذا (قيمة == error_mark_عقدة)
	أرجع error_mark_عقدة;
    }

  إذا (type == TYPE_MAIN_VARIANT (شجرة_TYPE (قيمة)))
    {
      إذا (RECORD_OR_UNION_TYPE_P (type)
	  && pedwarn (loc, OPT_Wpedantic,
		      "ISO C forbids casting nonscalar to the same type"))
	      ;
      وإلا إذا (warn_useless_cast && c_inhibit_evaluation_warnings == 0)
	warning_at (loc, OPT_Wuseless_cast,
		    "useless cast to type %qT", type);

      /* Convert to remove any qualifiers from VALUE's type.  */
      قيمة = convert (type, قيمة);
    }
  وإلا إذا (شجرة_CODE (type) == UNION_TYPE)
    {
      شجرة field;

      لكل (field = TYPE_FIELDS (type); field; field = DECL_CHAIN (field))
	إذا (شجرة_TYPE (field) != error_mark_عقدة
	    && comptypes (TYPE_MAIN_VARIANT (شجرة_TYPE (field)),
			  TYPE_MAIN_VARIANT (شجرة_TYPE (قيمة))))
	  اكسر;

      إذا (field)
	{
	  شجرة t;
	  منطقي maybe_const = true;

	  pedwarn (loc, OPT_Wpedantic, "ISO C forbids casts to union type");
	  t = c_fully_fold (قيمة, خطأ, &maybe_const);
	  t = build_constructor_single (type, field, t);
	  إذا (!maybe_const)
	    t = c_wrap_maybe_const (t, true);
	  t = digest_init (loc, field, type, t,
			   NULL_شجرة, خطأ, خطأ, خطأ, true, خطأ, خطأ);
	  شجرة_CONSTANT (t) = شجرة_CONSTANT (قيمة);
	  أرجع t;
	}
      error_at (loc, "cast to union type from type not present in union");
      أرجع error_mark_عقدة;
    }
  وإلا
    {
      شجرة otype, ovalue;

      إذا (type == void_type_عقدة)
	{
	  شجرة t = build1 (CONVERT_تعبير, type, قيمة);
	  SET_تعبير_LOCATION (t, loc);
	  أرجع t;
	}

      otype = شجرة_TYPE (قيمة);

      /* Optionally warn about potentially worrisome casts.  */
      إذا (warn_cast_qual
	  && شجرة_CODE (type) == POINTER_TYPE
	  && شجرة_CODE (otype) == POINTER_TYPE)
	handle_warn_cast_qual (loc, type, otype);

      /* Warn about conversions between pointers to disjoint
	 address spaces.  */
      إذا (شجرة_CODE (type) == POINTER_TYPE
	  && شجرة_CODE (otype) == POINTER_TYPE
	  && !null_pointer_constant_p (قيمة))
	{
	  addr_space_t as_to = TYPE_ADDR_SPACE (شجرة_TYPE (type));
	  addr_space_t as_from = TYPE_ADDR_SPACE (شجرة_TYPE (otype));
	  addr_space_t as_common;

	  إذا (!addr_space_superset (as_to, as_from, &as_common))
	    {
	      إذا (ADDR_SPACE_GENERIC_P (as_from))
		warning_at (loc, 0, "cast to %qs address space pointer "
			    "from disjoint generic address space pointer",
			    c_addr_space_name (as_to));

	      وإلا إذا (ADDR_SPACE_GENERIC_P (as_to))
		warning_at (loc, 0, "cast to generic address space pointer "
			    "from disjoint %qs address space pointer",
			    c_addr_space_name (as_from));

	      وإلا
		warning_at (loc, 0, "cast to %qs address space pointer "
			    "from disjoint %qs address space pointer",
			    c_addr_space_name (as_to),
			    c_addr_space_name (as_from));
	    }

	  /* Warn of new allocations that are not big enough for the target
	     type.  */
	  إذا (warn_alloc_size && شجرة_CODE (قيمة) == CALL_تعبير)
	    إذا (شجرة fndecl = get_callee_fndecl (قيمة))
	      إذا (DECL_IS_MALLOC (fndecl))
		{
		  شجرة attrs = TYPE_ATTRIBUTES (شجرة_TYPE (fndecl));
		  شجرة alloc_size = lookup_attribute ("alloc_size", attrs);
		  إذا (alloc_size)
		    warn_for_alloc_size (loc, شجرة_TYPE (type), قيمة,
					 alloc_size);
		}
	}

      /* Warn about possible alignment problems.  */
      إذا ((STRICT_ALIGNMENT || warn_cast_align == 2)
	  && شجرة_CODE (type) == POINTER_TYPE
	  && شجرة_CODE (otype) == POINTER_TYPE
	  && شجرة_CODE (شجرة_TYPE (otype)) != VOID_TYPE
	  && شجرة_CODE (شجرة_TYPE (otype)) != FUNCTION_TYPE
	  /* Don't warn about opaque types, where the actual alignment
	     restriction is unknown.  */
	  && !(RECORD_OR_UNION_TYPE_P (شجرة_TYPE (otype))
	       && TYPE_MODE (شجرة_TYPE (otype)) == VOIDmode)
	  && min_align_of_type (شجرة_TYPE (type))
	     > min_align_of_type (شجرة_TYPE (otype)))
	warning_at (loc, OPT_Wcast_align,
		    "cast increases required alignment of target type");

      إذا ((شجرة_CODE (type) == INTEGER_TYPE
	   || شجرة_CODE (type) == BITINT_TYPE)
	  && شجرة_CODE (otype) == POINTER_TYPE
	  && TYPE_PRECISION (type) != TYPE_PRECISION (otype))
      /* Unlike conversion of integers to pointers, where the
         warning is disabled for converting constants because
         of cases such as SIG_*, warn about converting constant
         pointers to integers. In some cases it may cause unwanted
         sign extension, and a warning is appropriate.  */
	warning_at (loc, OPT_Wpointer_to_int_cast,
		    "cast from pointer to integer of different size");

      إذا ((شجرة_CODE (قيمة) == CALL_تعبير
	   && !is_access_with_size_p (قيمة))
	  && شجرة_CODE (type) != شجرة_CODE (otype))
	warning_at (loc, OPT_Wbad_function_cast,
		    "cast from function call of type %qT "
		    "to non-matching type %qT", otype, type);

      إذا (شجرة_CODE (type) == POINTER_TYPE
	  && (شجرة_CODE (otype) == INTEGER_TYPE
	      || شجرة_CODE (otype) == BITINT_TYPE)
	  && TYPE_PRECISION (type) != TYPE_PRECISION (otype)
	  /* Don't warn about converting any constant.  */
	  && !شجرة_CONSTANT (قيمة))
	warning_at (loc,
		    OPT_Wint_to_pointer_cast, "cast to pointer from integer "
		    "of different size");

      إذا (warn_strict_aliasing <= 2)
        strict_aliasing_warning (تعبير_LOCATION (قيمة), type, تعبير);

      /* If pedantic, warn for conversions between function and object
	 pointer types, except for converting a null pointer constant
	 to function pointer type.  */
      إذا (pedantic
	  && شجرة_CODE (type) == POINTER_TYPE
	  && شجرة_CODE (otype) == POINTER_TYPE
	  && شجرة_CODE (شجرة_TYPE (otype)) == FUNCTION_TYPE
	  && شجرة_CODE (شجرة_TYPE (type)) != FUNCTION_TYPE)
	pedwarn (loc, OPT_Wpedantic, "ISO C forbids "
		 "conversion of function pointer to object pointer type");

      إذا (pedantic
	  && شجرة_CODE (type) == POINTER_TYPE
	  && شجرة_CODE (otype) == POINTER_TYPE
	  && شجرة_CODE (شجرة_TYPE (type)) == FUNCTION_TYPE
	  && شجرة_CODE (شجرة_TYPE (otype)) != FUNCTION_TYPE
	  && !null_pointer_constant_p (قيمة))
	pedwarn (loc, OPT_Wpedantic, "ISO C forbids "
		 "conversion of object pointer to function pointer type");

      إذا (شجرة_CODE (type) == POINTER_TYPE
	  && شجرة_CODE (otype) == POINTER_TYPE
	  && شجرة_CODE (شجرة_TYPE (type)) == FUNCTION_TYPE
	  && شجرة_CODE (شجرة_TYPE (otype)) == FUNCTION_TYPE
	  && !c_safe_function_type_cast_p (شجرة_TYPE (type),
					   شجرة_TYPE (otype)))
	warning_at (loc, OPT_Wcast_function_type,
		    "cast between incompatible function types"
		    " from %qT to %qT", otype, type);

      ovalue = قيمة;
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
	  && شجرة_CODE (قيمة) != INTEGER_CST
	  && (شجرة_CODE (type) == BOOLEAN_TYPE
	      || (شجرة_CODE (type) == ENUMERAL_TYPE
		  && ENUM_UNDERLYING_TYPE (type) != NULL_شجرة
		  && شجرة_CODE (ENUM_UNDERLYING_TYPE (type)) == BOOLEAN_TYPE)))
	قيمة = note_integer_operands (قيمة);
      قيمة = convert (type, قيمة);

      /* Ignore any integer overflow caused by the cast.  */
      إذا (شجرة_CODE (قيمة) == INTEGER_CST && !FLOAT_TYPE_P (otype))
	{
	  إذا (شجرة_OVERFLOW_P (ovalue))
	    {
	      إذا (!شجرة_OVERFLOW (قيمة))
		{
		  /* Avoid clobbering a shared constant.  */
		  قيمة = copy_عقدة (قيمة);
		  شجرة_OVERFLOW (قيمة) = شجرة_OVERFLOW (ovalue);
		}
	    }
	  وإلا إذا (شجرة_OVERFLOW (قيمة))
	    /* Reset VALUE's overflow flags, ensuring constant sharing.  */
	    قيمة = wide_int_to_شجرة (شجرة_TYPE (قيمة), wi::to_wide (قيمة));
	}
    }

  /* Don't let a cast be an lvalue.  */
  إذا (lvalue_p (قيمة)
      /* Also, don't let a cast be a bit-field of a bit-precise integer type,
	 otherwise it could be incorrectly subject of integer promotions.  */
      || (شجرة_CODE (قيمة) == COMPONENT_REF
	  && DECL_C_BIT_FIELD (شجرة_OPERAND (قيمة, 1))
	  && BITINT_TYPE_P (DECL_BIT_FIELD_TYPE (شجرة_OPERAND (قيمة, 1)))))
    قيمة = non_lvalue_loc (loc, قيمة);

  /* Don't allow the results of casting to floating-point or complex
     types be confused with actual constants, or casts involving
     integer and pointer types other than direct integer-to-integer
     and integer-to-pointer be confused with integer constant
     expressions and null pointer constants.  */
  إذا (شجرة_CODE (قيمة) == REAL_CST
      || شجرة_CODE (قيمة) == COMPLEX_CST
      || (شجرة_CODE (قيمة) == INTEGER_CST
	  && !((شجرة_CODE (تعبير) == INTEGER_CST
		&& INTEGRAL_TYPE_P (شجرة_TYPE (تعبير)))
	       || شجرة_CODE (تعبير) == REAL_CST
	       || شجرة_CODE (تعبير) == COMPLEX_CST)))
      قيمة = build1 (NOP_تعبير, type, قيمة);

  /* If the expression has integer operands and so can occur in an
     unevaluated part of an integer constant expression, ensure the
     return value reflects this.  */
  إذا (int_operands
      && INTEGRAL_TYPE_P (type)
      && قيمة != error_mark_عقدة
      && !تعبير_INT_CONST_OPERANDS (قيمة))
    قيمة = note_integer_operands (قيمة);

  protected_set_تعبير_location (قيمة, loc);
  أرجع قيمة;
}

/* Interpret a cast of expression EXPR to type TYPE.  LOC is the
   location of the open paren of the cast, or the position of the cast
   expr.  */
شجرة
c_cast_تعبير (location_t loc, بنية c_type_name *type_name, شجرة تعبير)
{
  شجرة type;
  شجرة type_تعبير = NULL_شجرة;
  منطقي type_تعبير_const = true;
  شجرة ret;
  صحيح saved_wsp = warn_strict_prototypes;

  /* This avoids warnings about unprototyped casts on
     integers.  E.g. "#define SIG_DFL (void(*)())0".  */
  إذا (شجرة_CODE (تعبير) == INTEGER_CST)
    warn_strict_prototypes = 0;
  type = groktypename (type_name, &type_تعبير, &type_تعبير_const);
  warn_strict_prototypes = saved_wsp;

  إذا (شجرة_CODE (تعبير) == ADDR_تعبير && !VOID_TYPE_P (type)
      && reject_gcc_builtin (تعبير))
    أرجع error_mark_عقدة;

  ret = build_c_cast (loc, type, تعبير);
  إذا (ret == error_mark_عقدة)
    أرجع error_mark_عقدة;

  إذا (type_تعبير)
    {
      منطقي inner_تعبير_const = true;
      ret = c_fully_fold (ret, require_constant_قيمة, &inner_تعبير_const);
      ret = build2 (C_MAYBE_CONST_تعبير, شجرة_TYPE (ret), type_تعبير, ret);
      C_MAYBE_CONST_تعبير_NON_CONST (ret) = !(type_تعبير_const
					     && inner_تعبير_const);
      SET_تعبير_LOCATION (ret, loc);
    }

  إذا (!تعبير_HAS_LOCATION (ret))
    protected_set_تعبير_location (ret, loc);

  /* C++ does not permits types to be defined in a cast, but it
     allows references to incomplete types.  */
  إذا (warn_cxx_compat && type_name->specs->typespec_kind == ctsk_tagdef)
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

شجرة
build_modify_تعبير (location_t location, شجرة lhs, شجرة lhs_origtype,
		   تعداد شجرة_code modifycode,
		   location_t rhs_loc, شجرة rhs, شجرة rhs_origtype)
{
  شجرة result;
  شجرة newrhs;
  شجرة rhseval = NULL_شجرة;
  شجرة lhstype = شجرة_TYPE (lhs);
  شجرة olhstype = lhstype;
  منطقي npc;
  منطقي is_atomic_op;

  /* Types that aren't fully specified cannot be used in assignments.  */
  lhs = require_complete_type (location, lhs);
  rhs = require_complete_type (location, rhs);

  /* Avoid duplicate error messages from operands that had errors.  */
  إذا (شجرة_CODE (lhs) == ERROR_MARK || شجرة_CODE (rhs) == ERROR_MARK)
    أرجع error_mark_عقدة;

  /* Ensure an error for assigning a non-lvalue array to an array in
     C90.  */
  إذا (شجرة_CODE (lhstype) == ARRAY_TYPE)
    {
      error_at (location, "assignment to expression with array type");
      أرجع error_mark_عقدة;
    }

  /* For ObjC properties, defer this check.  */
  إذا (!objc_is_property_ref (lhs) && !lvalue_or_else (location, lhs, lv_assign))
    أرجع error_mark_عقدة;

  is_atomic_op = really_atomic_lvalue (lhs);

  newrhs = rhs;

  إذا (شجرة_CODE (lhs) == C_MAYBE_CONST_تعبير)
    {
      شجرة inner = build_modify_تعبير (location, C_MAYBE_CONST_تعبير_تعبير (lhs),
				      lhs_origtype, modifycode, rhs_loc, rhs,
				      rhs_origtype);
      إذا (inner == error_mark_عقدة)
	أرجع error_mark_عقدة;
      result = build2 (C_MAYBE_CONST_تعبير, شجرة_TYPE (inner),
		       C_MAYBE_CONST_تعبير_PRE (lhs), inner);
      gcc_assert (!C_MAYBE_CONST_تعبير_INT_OPERANDS (lhs));
      C_MAYBE_CONST_تعبير_NON_CONST (result) = 1;
      protected_set_تعبير_location (result, location);
      أرجع result;
    }

  /* If a binary op has been requested, combine the old LHS value with the RHS
     producing the value we should actually store into the LHS.  */

  إذا (modifycode != NOP_تعبير)
    {
      lhs = c_fully_fold (lhs, خطأ, عدم, true);
      lhs = stabilize_reference (lhs);

      /* Construct the RHS for any non-atomic compound assignment. */
      إذا (!is_atomic_op)
        {
	  /* If in LHS op= RHS the RHS has side-effects, ensure they
	     are preevaluated before the rest of the assignment expression's
	     side-effects, because RHS could contain e.g. function calls
	     that modify LHS.  */
	  إذا (شجرة_SIDE_EFFECTS (rhs))
	    {
	      إذا (شجرة_CODE (rhs) == EXCESS_PRECISION_تعبير)
		newrhs = save_تعبير (شجرة_OPERAND (rhs, 0));
	      وإلا
		newrhs = save_تعبير (rhs);
	      rhseval = newrhs;
	      إذا (شجرة_CODE (rhs) == EXCESS_PRECISION_تعبير)
		newrhs = build1 (EXCESS_PRECISION_تعبير, شجرة_TYPE (rhs),
				 newrhs);
	    }
	  منطقي clear_decl_read = خطأ;
	  إذا ((VAR_P (lhs) || شجرة_CODE (lhs) == PARM_DECL)
	      && !DECL_READ_P (lhs)
	      && (VAR_P (lhs) ? warn_unused_but_set_variable
			      : warn_unused_but_set_parameter) > 2)
	    {
	      mark_exp_read (newrhs);
	      إذا (!DECL_READ_P (lhs))
		clear_decl_read = true;
	    }

	  newrhs = build_ثنائي_op (location, modifycode,
				    convert_lvalue_to_rvalue (location, lhs,
							      true, true),
				    newrhs, true);
	  إذا (clear_decl_read)
	    DECL_READ_P (lhs) = 0;

	  /* The original type of the right hand side is no longer
	     meaningful.  */
	  rhs_origtype = NULL_شجرة;
	}
    }

  إذا (c_dialect_objc ())
    {
      /* Check if we are modifying an Objective-C property reference;
	 if so, we need to generate setter calls.  */
      إذا (شجرة_CODE (newrhs) == EXCESS_PRECISION_تعبير)
	result = objc_maybe_build_modify_تعبير (lhs, شجرة_OPERAND (newrhs, 0));
      وإلا
	result = objc_maybe_build_modify_تعبير (lhs, newrhs);
      إذا (result)
	اذهب return_result;

      /* Else, do the check that we postponed for Objective-C.  */
      إذا (!lvalue_or_else (location, lhs, lv_assign))
	أرجع error_mark_عقدة;
    }

  /* Give an error for storing in something that is 'const'.  */

  إذا (TYPE_READONLY (lhstype)
      || (RECORD_OR_UNION_TYPE_P (lhstype)
	  && C_TYPE_FIELDS_READONLY (lhstype)))
    {
      readonly_error (location, lhs, lv_assign);
      أرجع error_mark_عقدة;
    }
  وإلا إذا (شجرة_READONLY (lhs))
    readonly_warning (lhs, lv_assign);

  /* If storing into a structure or union member,
     it has probably been given type `int'.
     Compute the type that would go with
     the actual amount of storage the member occupies.  */

  إذا (شجرة_CODE (lhs) == COMPONENT_REF
      && (شجرة_CODE (lhstype) == INTEGER_TYPE
	  || شجرة_CODE (lhstype) == BOOLEAN_TYPE
	  || SCALAR_FLOAT_TYPE_P (lhstype)
	  || شجرة_CODE (lhstype) == ENUMERAL_TYPE))
    lhstype = شجرة_TYPE (get_unwidened (lhs, 0));

  /* If storing in a field that is in actuality a short or narrower than one,
     we must store in the field in its actual type.  */

  إذا (lhstype != شجرة_TYPE (lhs))
    {
      lhs = copy_عقدة (lhs);
      شجرة_TYPE (lhs) = lhstype;
    }

  /* Issue -Wc++-compat warnings about an assignment to an enum type
     when LHS does not have its original type.  This happens for,
     e.g., an enum bitfield in a struct.  */
  إذا (warn_cxx_compat
      && lhs_origtype != NULL_شجرة
      && lhs_origtype != lhstype
      && شجرة_CODE (lhs_origtype) == ENUMERAL_TYPE)
    {
      شجرة checktype = (rhs_origtype != NULL_شجرة
			? rhs_origtype
			: شجرة_TYPE (rhs));
      إذا (checktype != error_mark_عقدة
	  && (TYPE_MAIN_VARIANT (checktype) != TYPE_MAIN_VARIANT (lhs_origtype)
	      || (is_atomic_op && modifycode != NOP_تعبير)))
	warning_at (location, OPT_Wc___compat,
		    "enum conversion in assignment is invalid in C++");
    }

  /* Remove qualifiers.  */
  lhstype = c_build_qualified_type (lhstype, TYPE_UNQUALIFIED);
  olhstype = c_build_qualified_type (olhstype, TYPE_UNQUALIFIED);

  /* Convert new value to destination type.  Fold it first, then
     restore any excess precision information, for the sake of
     conversion warnings.  */

  إذا (!(is_atomic_op && modifycode != NOP_تعبير))
    {
      شجرة rhs_semantic_type = NULL_شجرة;
      إذا (!c_in_omp_for)
	{
	  إذا (شجرة_CODE (newrhs) == EXCESS_PRECISION_تعبير)
	    {
	      rhs_semantic_type = شجرة_TYPE (newrhs);
	      newrhs = شجرة_OPERAND (newrhs, 0);
	    }
	  npc = null_pointer_constant_p (newrhs);
	  newrhs = c_fully_fold (newrhs, خطأ, عدم);
	  إذا (rhs_semantic_type)
	    newrhs = build1 (EXCESS_PRECISION_تعبير, rhs_semantic_type, newrhs);
	}
      وإلا
	npc = null_pointer_constant_p (newrhs);
      newrhs = convert_for_assignment (location, rhs_loc, lhstype, newrhs,
				       rhs_origtype, ic_assign, npc,
				       NULL_شجرة, NULL_شجرة, 0);
      إذا (شجرة_CODE (newrhs) == ERROR_MARK)
	أرجع error_mark_عقدة;
    }

  /* Emit ObjC write barrier, if necessary.  */
  إذا (c_dialect_objc () && flag_objc_gc)
    {
      result = objc_generate_write_barrier (lhs, modifycode, newrhs);
      إذا (result)
	{
	  protected_set_تعبير_location (result, location);
	  اذهب return_result;
	}
    }

  /* Scan operands.  */

  إذا (is_atomic_op)
    result = build_atomic_assign (location, lhs, modifycode, newrhs, خطأ);
  وإلا
    {
      result = build2 (MODIFY_تعبير, lhstype, lhs, newrhs);
      شجرة_SIDE_EFFECTS (result) = 1;
      protected_set_تعبير_location (result, location);
    }

  /* If we got the LHS in a different type for storing in,
     convert the result back to the nominal type of LHS
     so that the value we return always has the same type
     as the LHS argument.  */

  إذا (olhstype == شجرة_TYPE (result))
    اذهب return_result;

  result = convert_for_assignment (location, rhs_loc, olhstype, result,
				   rhs_origtype, ic_assign, خطأ, NULL_شجرة,
				   NULL_شجرة, 0);
  protected_set_تعبير_location (result, location);

return_result:
  إذا (rhseval)
    result = build2 (COMPOUND_تعبير, شجرة_TYPE (result), rhseval, result);
  أرجع result;
}

/* Return whether STRUCT_TYPE has an anonymous field with type TYPE.
   This is used to implement -fplan9-extensions.  */

ساكن منطقي
find_anonymous_field_with_type (شجرة struct_type, شجرة type)
{
  شجرة field;
  منطقي found;

  gcc_assert (RECORD_OR_UNION_TYPE_P (struct_type));
  found = خطأ;
  لكل (field = TYPE_FIELDS (struct_type);
       field != NULL_شجرة;
       field = شجرة_CHAIN (field))
    {
      شجرة fieldtype = remove_qualifiers (شجرة_TYPE (field));
      إذا (DECL_NAME (field) == عدم
	  && comptypes (type, fieldtype))
	{
	  إذا (found)
	    أرجع خطأ;
	  found = true;
	}
      وإلا إذا (DECL_NAME (field) == عدم
	       && RECORD_OR_UNION_TYPE_P (شجرة_TYPE (field))
	       && find_anonymous_field_with_type (شجرة_TYPE (field), type))
	{
	  إذا (found)
	    أرجع خطأ;
	  found = true;
	}
    }
  أرجع found;
}

/* RHS is an expression whose type is pointer to struct.  If there is
   an anonymous field in RHS with type TYPE, then return a pointer to
   that field in RHS.  This is used with -fplan9-extensions.  This
   returns NULL if no conversion could be found.  */

ساكن شجرة
convert_to_anonymous_field (location_t location, شجرة type, شجرة rhs)
{
  شجرة rhs_struct_type, lhs_main_type;
  شجرة field, found_field;
  منطقي found_sub_field;
  شجرة ret;

  gcc_assert (POINTER_TYPE_P (شجرة_TYPE (rhs)));
  rhs_struct_type = شجرة_TYPE (شجرة_TYPE (rhs));
  gcc_assert (RECORD_OR_UNION_TYPE_P (rhs_struct_type));

  gcc_assert (POINTER_TYPE_P (type));
  lhs_main_type = remove_qualifiers (شجرة_TYPE (type));

  found_field = NULL_شجرة;
  found_sub_field = خطأ;
  لكل (field = TYPE_FIELDS (rhs_struct_type);
       field != NULL_شجرة;
       field = شجرة_CHAIN (field))
    {
      إذا (DECL_NAME (field) != NULL_شجرة
	  || !RECORD_OR_UNION_TYPE_P (شجرة_TYPE (field)))
	استمر;
      شجرة fieldtype = remove_qualifiers (شجرة_TYPE (field));
      إذا (comptypes (lhs_main_type, fieldtype))
	{
	  إذا (found_field != NULL_شجرة)
	    أرجع NULL_شجرة;
	  found_field = field;
	}
      وإلا إذا (find_anonymous_field_with_type (شجرة_TYPE (field),
					       lhs_main_type))
	{
	  إذا (found_field != NULL_شجرة)
	    أرجع NULL_شجرة;
	  found_field = field;
	  found_sub_field = true;
	}
    }

  إذا (found_field == NULL_شجرة)
    أرجع NULL_شجرة;

  ret = fold_build3_loc (location, COMPONENT_REF, شجرة_TYPE (found_field),
			 build_fold_indirect_ref (rhs), found_field,
			 NULL_شجرة);
  ret = build_fold_addr_تعبير_loc (location, ret);

  إذا (found_sub_field)
    {
      ret = convert_to_anonymous_field (location, type, ret);
      gcc_assert (ret != NULL_شجرة);
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

  auto_diagnostic_group d;

  /* The gmsgid may be a format string with %< and %>. */
  va_list ap;
  va_start (ap, gmsgid);
  منطقي warned = emit_diagnostic_valist (diagnostics::kind::error,
					loc, -1, gmsgid, &ap);
  va_end (ap);

  ofwhat = اطبع_spelling ((حرف *) alloca (spelling_length () + 1));
  إذا (*ofwhat && warned)
    inform (loc, "(near initialization for %qs)", ofwhat);
}

/* Used to implement pedwarn_init and permerror_init.  */

ساكن منطقي ATTRIBUTE_GCC_DIAG (3,0)
pedwarn_permerror_init (location_t loc, صحيح opt, ثابت حرف *gmsgid,
			va_list *ap, تعداد diagnostics::kind kind)
{
  /* Use the location where a macro was expanded rather than where
     it was defined to make sure macros defined in system headers
     but used incorrectly elsewhere are diagnosed.  */
  location_t exploc = expansion_point_location_if_in_system_header (loc);
  auto_diagnostic_group d;
  منطقي warned = emit_diagnostic_valist (kind, exploc, opt, gmsgid, ap);
  إذا (warned)
    {
      حرف *ofwhat = اطبع_spelling ((حرف *) alloca (spelling_length () + 1));
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
  va_start (ap, gmsgid);
  منطقي warned = pedwarn_permerror_init (loc, opt, gmsgid, &ap,
					diagnostics::kind::pedwarn);
  va_end (ap);
  أرجع warned;
}

/* Like pedwarn_init, but issue a permerror.  */

ساكن منطقي ATTRIBUTE_GCC_DIAG (3,0)
permerror_init (location_t loc, صحيح opt, ثابت حرف *gmsgid, ...)
{
  va_list ap;
  va_start (ap, gmsgid);
  منطقي warned = pedwarn_permerror_init (loc, opt, gmsgid, &ap,
					diagnostics::kind::permerror);
  va_end (ap);
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

  auto_diagnostic_group d;

  /* Use the location where a macro was expanded rather than where
     it was defined to make sure macros defined in system headers
     but used incorrectly elsewhere are diagnosed.  */
  location_t exploc = expansion_point_location_if_in_system_header (loc);

  /* The gmsgid may be a format string with %< and %>. */
  warned = warning_at (exploc, opt, gmsgid);
  إذا (warned)
    {
      ofwhat = اطبع_spelling ((حرف *) alloca (spelling_length () + 1));
      إذا (*ofwhat)
	inform (exploc, "(near initialization for %qs)", ofwhat);
    }
}

/* If TYPE is an array type and EXPR is a parenthesized string
   constant, warn if pedantic that EXPR is being used to initialize an
   object of type TYPE.  */

فراغ
maybe_warn_string_init (location_t loc, شجرة type, بنية c_تعبير تعبير)
{
  إذا (pedantic
      && شجرة_CODE (type) == ARRAY_TYPE
      && شجرة_CODE (تعبير.قيمة) == STRING_CST
      && تعبير.original_code != STRING_CST)
    pedwarn_init (loc, OPT_Wpedantic,
		  "array initialized from parenthesized string constant");
}

/* Attempt to locate the parameter with the given index within FNDECL,
   returning DECL_SOURCE_LOCATION (FNDECL) if it can't be found.  */

ساكن location_t
get_fndecl_argument_location (شجرة fndecl, صحيح argnum)
{
  صحيح i;
  شجرة param;

  /* Locate param by index within DECL_ARGUMENTS (fndecl).  */
  لكل (i = 0, param = DECL_ARGUMENTS (fndecl);
       i < argnum && param;
       i++, param = شجرة_CHAIN (param))
    ;

  /* If something went wrong (e.g. if we have a builtin and thus no arguments),
     return DECL_SOURCE_LOCATION (FNDECL).  */
  إذا (param == عدم)
    أرجع DECL_SOURCE_LOCATION (fndecl);

  أرجع DECL_SOURCE_LOCATION (param);
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
inform_for_arg (شجرة fundecl, location_t ploc, صحيح parmnum,
		شجرة expected_type, شجرة actual_type)
{
  location_t loc;
  إذا (fundecl && !DECL_IS_UNDECLARED_BUILTIN (fundecl))
    loc = get_fndecl_argument_location (fundecl, parmnum - 1);
  وإلا
    loc = ploc;

  gcc_rich_location richloc (loc, nullptr, highlight_colors::expected);

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
maybe_warn_builtin_no_proto_arg (location_t loc, شجرة fundecl, صحيح parmnum,
				 شجرة parmtype, شجرة argtype)
{
  شجرة_code parmcode = شجرة_CODE (parmtype);
  شجرة_code argcode = شجرة_CODE (argtype);
  شجرة promoted = c_type_promotes_to (argtype);

  /* Avoid warning for enum arguments that promote to an integer type
     of the same size/mode.  */
  إذا (parmcode == INTEGER_TYPE
      && argcode == ENUMERAL_TYPE
      && TYPE_MODE (parmtype) == TYPE_MODE (argtype))
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
    inform (DECL_SOURCE_LOCATION (fundecl),
	    "built-in %qD declared here",
	    fundecl);
}

/* Print a declaration in quotes, with the given highlight_color.
   Analogous to handler for %qD, but with a specific highlight color.  */

صنف pp_element_quoted_decl : عام pp_element
{
عام:
  pp_element_quoted_decl (شجرة decl, ثابت حرف *highlight_color)
  : m_decl (decl),
    m_highlight_color (highlight_color)
  {
  }

  فراغ add_to_phase_2 (pp_markup::context &ctxt) override
  {
    ctxt.begin_quote ();
    ctxt.begin_highlight_color (m_highlight_color);

    اطبع_decl (ctxt);

    ctxt.end_highlight_color ();
    ctxt.end_quote ();
  }

  فراغ اطبع_decl (pp_markup::context &ctxt)
  {
    pretty_printer *ثابت pp = &ctxt.m_pp;
    pp->set_padding (pp_none);
    إذا (DECL_NAME (m_decl))
      pp_identifier (pp, lang_hooks.decl_printable_name (m_decl, 2));
    وإلا
      pp_string (pp, _("({anonymous})"));
  }

خاص:
  شجرة m_decl;
  ثابت حرف *m_highlight_color;
};

/* If TYPE is from a typedef, issue a note showing the location
   to the user.
   Use HIGHLIGHT_COLOR as the highlight color.  */

ساكن فراغ
maybe_inform_typedef_location (شجرة type, ثابت حرف *highlight_color)
{
  إذا (!typedef_variant_p (type))
    أرجع;

  شجرة typedef_decl = TYPE_NAME (type);
  gcc_assert (شجرة_CODE (typedef_decl) == TYPE_DECL);
  gcc_rich_location richloc (DECL_SOURCE_LOCATION (typedef_decl),
			     nullptr, highlight_color);
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

ساكن شجرة
convert_for_assignment (location_t location, location_t تعبير_loc, شجرة type,
			شجرة rhs, شجرة origtype, تعداد impl_conv errtype,
			منطقي null_pointer_constant, شجرة fundecl,
			شجرة function, صحيح parmnum, صحيح warnopt /* = 0 */)
{
  تعداد شجرة_code codel = شجرة_CODE (type);
  شجرة orig_rhs = rhs;
  شجرة rhstype;
  تعداد شجرة_code coder;
  شجرة rname = NULL_شجرة;
  منطقي objc_ok = خطأ;

  /* Use the expansion point location to handle cases such as user's
     function returning a wrong-type macro defined in a system header.  */
  location = expansion_point_location_if_in_system_header (location);

  إذا (errtype == ic_argpass)
    {
      شجرة selector;
      /* Change pointer to function to the function itself for
	 diagnostics.  */
      إذا (شجرة_CODE (function) == ADDR_تعبير
	  && شجرة_CODE (شجرة_OPERAND (function, 0)) == FUNCTION_DECL)
	function = شجرة_OPERAND (function, 0);

      /* Handle an ObjC selector specially for diagnostics.  */
      selector = objc_message_selector ();
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
#define PEDWARN_FOR_ASSIGNMENT(LOCATION, PLOC, OPT, AR, AS, IN, RE)	 \
  افعل {                                                                   \
    بدل (errtype)                                                     \
      {                                                                  \
      حالة ic_argpass:                                                   \
	{								\
	  auto_diagnostic_group d;						\
	  إذا (pedwarn (PLOC, OPT, AR, parmnum, rname))		\
	    inform_for_arg (fundecl, (PLOC), parmnum, type, rhstype); \
	}								\
        اكسر;                                                           \
      حالة ic_assign:                                                    \
        pedwarn (LOCATION, OPT, AS);                                     \
        اكسر;                                                           \
      حالة ic_init:                                                      \
      حالة ic_init_const:                                                \
        pedwarn_init (LOCATION, OPT, IN);                                \
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
#define WARNING_FOR_QUALIFIERS(PEDWARN, LOCATION, PLOC, OPT, AR, AS, IN, RE, QUALS) \
  افعل {                                                                   \
    بدل (errtype)                                                     \
      {                                                                  \
      حالة ic_argpass:                                                   \
	{								 \
	  auto_diagnostic_group d;					 \
	  إذا (PEDWARN) {						 \
	    إذا (pedwarn (PLOC, OPT, AR, parmnum, rname, QUALS))          \
	      inform_for_arg (fundecl, (PLOC), parmnum, type, rhstype);  \
	  } وإلا {							 \
	    إذا (warning_at (PLOC, OPT, AR, parmnum, rname, QUALS))	 \
	      inform_for_arg (fundecl, (PLOC), parmnum, type, rhstype);  \
	  }								 \
	}								 \
        اكسر;                                                           \
      حالة ic_assign:                                                    \
	إذا (PEDWARN)							 \
	  pedwarn (LOCATION, OPT, AS, QUALS);                            \
	وإلا								 \
	  warning_at (LOCATION, OPT, AS, QUALS);                         \
        اكسر;                                                           \
      حالة ic_init:                                                      \
      حالة ic_init_const:                                                \
	إذا (PEDWARN)							 \
	  pedwarn (LOCATION, OPT, IN, QUALS);                            \
	وإلا								 \
	  warning_at (LOCATION, OPT, IN, QUALS);                         \
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
#define PEDWARN_FOR_QUALIFIERS(LOCATION, PLOC, OPT, AR, AS, IN, RE, QUALS) \
   WARNING_FOR_QUALIFIERS (true, LOCATION, PLOC, OPT, AR, AS, IN, RE, QUALS)


  إذا (شجرة_CODE (rhs) == EXCESS_PRECISION_تعبير)
    rhs = شجرة_OPERAND (rhs, 0);

  rhstype = شجرة_TYPE (rhs);
  coder = شجرة_CODE (rhstype);

  إذا (coder == ERROR_MARK)
    أرجع error_mark_عقدة;

  إذا (c_dialect_objc ())
    {
      صحيح parmno;

      بدل (errtype)
	{
	حالة ic_return:
	  parmno = 0;
	  اكسر;

	حالة ic_assign:
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
      شجرة checktype = origtype != NULL_شجرة ? origtype : rhstype;
      إذا (checktype != error_mark_عقدة
	  && شجرة_CODE (type) == ENUMERAL_TYPE
	  && TYPE_MAIN_VARIANT (checktype) != TYPE_MAIN_VARIANT (type))
	بدل (errtype)
	  {
	  حالة ic_argpass:
	    إذا (pedwarn (تعبير_loc, OPT_Wc___compat, "enum conversion when "
			 "passing argument %d of %qE is invalid in C++",
			 parmnum, rname))
	      inform ((fundecl && !DECL_IS_UNDECLARED_BUILTIN (fundecl))
		      ? DECL_SOURCE_LOCATION (fundecl) : تعبير_loc,
		      "expected %qT but argument is of type %qT",
		      type, rhstype);
	    اكسر;
	  حالة ic_assign:
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
      شجرة checktype = origtype != NULL_شجرة ? origtype : rhstype;
      إذا (checktype != error_mark_عقدة
	  && شجرة_CODE (checktype) == ENUMERAL_TYPE
	  && شجرة_CODE (type) == ENUMERAL_TYPE
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
      warn_for_address_of_packed_member (type, orig_rhs);
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
      ثابت حرف رسالة[] = "void value not ignored as it ought to be";
      إذا (warnopt)
	warning_at (location, warnopt, رسالة);
      وإلا
	error_at (location, رسالة);
      أرجع error_mark_عقدة;
    }
  rhs = require_complete_type (location, rhs);
  إذا (rhs == error_mark_عقدة)
    أرجع error_mark_عقدة;

  إذا (coder == POINTER_TYPE && reject_gcc_builtin (rhs))
    أرجع error_mark_عقدة;

  /* A non-reference type can convert to a reference.  This handles
     va_start, va_copy and possibly port built-ins.  */
  إذا (codel == REFERENCE_TYPE && coder != REFERENCE_TYPE)
    {
      إذا (!lvalue_p (rhs))
	{
	  ثابت حرف رسالة[] = "cannot pass rvalue to reference parameter";
	  إذا (warnopt)
	    warning_at (location, warnopt, رسالة);
	  وإلا
	    error_at (location, رسالة);
	  أرجع error_mark_عقدة;
	}
      إذا (!c_mark_addressable (rhs))
	أرجع error_mark_عقدة;
      rhs = build1 (ADDR_تعبير, c_build_pointer_type (شجرة_TYPE (rhs)), rhs);
      SET_تعبير_LOCATION (rhs, location);

      rhs = convert_for_assignment (location, تعبير_loc,
				    c_build_pointer_type (شجرة_TYPE (type)),
				    rhs, origtype, errtype,
				    null_pointer_constant, fundecl, function,
				    parmnum, warnopt);
      إذا (rhs == error_mark_عقدة)
	أرجع error_mark_عقدة;

      rhs = build1 (NOP_تعبير, type, rhs);
      SET_تعبير_LOCATION (rhs, location);
      أرجع rhs;
    }
  /* Some types can interconvert without explicit casts.  */
  وإلا إذا (codel == VECTOR_TYPE && coder == VECTOR_TYPE
	   && vector_types_convertible_p (type, شجرة_TYPE (rhs), true))
    أرجع convert (type, rhs);
  /* Arithmetic types all interconvert, and enum is treated like int.  */
  وإلا إذا ((codel == INTEGER_TYPE || codel == REAL_TYPE
	    || codel == FIXED_POINT_TYPE
	    || codel == ENUMERAL_TYPE || codel == COMPLEX_TYPE
	    || codel == BOOLEAN_TYPE || codel == BITINT_TYPE)
	   && (coder == INTEGER_TYPE || coder == REAL_TYPE
	       || coder == FIXED_POINT_TYPE
	       || coder == ENUMERAL_TYPE || coder == COMPLEX_TYPE
	       || coder == BOOLEAN_TYPE || coder == BITINT_TYPE))
    {
      إذا (warnopt && errtype == ic_argpass)
	maybe_warn_builtin_no_proto_arg (تعبير_loc, fundecl, parmnum, type,
					 rhstype);

      منطقي save = in_late_ثنائي_op;
      إذا (C_BOOLEAN_TYPE_P (type) || codel == COMPLEX_TYPE
	  || (coder == REAL_TYPE
	      && (codel == INTEGER_TYPE || codel == ENUMERAL_TYPE)
	      && sanitize_flags_p (SANITIZE_FLOAT_CAST)))
	in_late_ثنائي_op = true;
      شجرة ret = convert_and_check (تعبير_loc != UNKNOWN_LOCATION
				    ? تعبير_loc : location, type, orig_rhs,
				    errtype == ic_init_const);
      in_late_ثنائي_op = save;
      أرجع ret;
    }

  /* Aggregates in different TUs might need conversion.  */
  إذا ((codel == RECORD_TYPE || codel == UNION_TYPE)
      && codel == coder
      && comptypes (TYPE_MAIN_VARIANT (type), TYPE_MAIN_VARIANT (rhstype)))
    أرجع convert_and_check (تعبير_loc != UNKNOWN_LOCATION
			      ? تعبير_loc : location, type, rhs);

  /* Conversion to a transparent union or record from its member types.
     This applies only to function arguments.  */
  إذا (((codel == UNION_TYPE || codel == RECORD_TYPE)
      && TYPE_TRANSPARENT_AGGR (type))
      && errtype == ic_argpass)
    {
      شجرة memb, marginal_memb = NULL_شجرة;

      لكل (memb = TYPE_FIELDS (type); memb ; memb = DECL_CHAIN (memb))
	{
	  شجرة memb_type = شجرة_TYPE (memb);

	  إذا (comptypes (TYPE_MAIN_VARIANT (memb_type),
			 TYPE_MAIN_VARIANT (rhstype)))
	    اكسر;

	  إذا (شجرة_CODE (memb_type) != POINTER_TYPE)
	    استمر;

	  إذا (coder == POINTER_TYPE)
	    {
	      شجرة ttl = شجرة_TYPE (memb_type);
	      شجرة ttr = شجرة_TYPE (rhstype);

	      /* Any non-function converts to a [const][volatile] void *
		 and vice versa; otherwise, targets must be the same.
		 Meanwhile, the lhs target must have all the qualifiers of
		 the rhs.  */
	      إذا ((VOID_TYPE_P (ttl) && !TYPE_ATOMIC (ttl))
		  || (VOID_TYPE_P (ttr) && !TYPE_ATOMIC (ttr))
		  || comp_target_types (location, memb_type, rhstype))
		{
		  صحيح lquals = TYPE_QUALS (ttl) & ~TYPE_QUAL_ATOMIC;
		  صحيح rquals = TYPE_QUALS (ttr) & ~TYPE_QUAL_ATOMIC;
		  /* If this type won't generate any warnings, use it.  */
		  إذا (lquals == rquals
		      || ((شجرة_CODE (ttr) == FUNCTION_TYPE
			   && شجرة_CODE (ttl) == FUNCTION_TYPE)
			  ? ((lquals | rquals) == rquals)
			  : ((lquals | rquals) == lquals)))
		    اكسر;

		  /* Keep looking for a better type, but remember this one.  */
		  إذا (!marginal_memb)
		    marginal_memb = memb;
		}
	    }

	  /* Can convert integer zero to any pointer type.  */
	  إذا (null_pointer_constant)
	    {
	      rhs = null_pointer_عقدة;
	      اكسر;
	    }
	}

      إذا (memb || marginal_memb)
	{
	  إذا (!memb)
	    {
	      /* We have only a marginally acceptable member type;
		 it needs a warning.  */
	      شجرة ttl = شجرة_TYPE (شجرة_TYPE (marginal_memb));
	      شجرة ttr = شجرة_TYPE (rhstype);

	      /* Const and volatile mean something different for function
		 types, so the usual warnings are not appropriate.  */
	      إذا (شجرة_CODE (ttr) == FUNCTION_TYPE
		  && شجرة_CODE (ttl) == FUNCTION_TYPE)
		{
		  /* Because const and volatile on functions are
		     restrictions that say the function will not do
		     certain things, it is okay to use a const or volatile
		     function where an ordinary one is wanted, but not
		     vice-versa.  */
		  إذا (TYPE_QUALS_NO_ADDR_SPACE (ttl)
		      & ~TYPE_QUALS_NO_ADDR_SPACE (ttr))
		    PEDWARN_FOR_QUALIFIERS (location, تعبير_loc,
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
		PEDWARN_FOR_QUALIFIERS (location, تعبير_loc,
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

	  إذا (!fundecl || !DECL_IN_SYSTEM_HEADER (fundecl))
	    pedwarn (location, OPT_Wpedantic,
		     "ISO C prohibits argument conversion to union type");

	  rhs = fold_convert_loc (location, شجرة_TYPE (memb), rhs);
	  أرجع build_constructor_single (type, memb, rhs);
	}
    }

  /* Conversions among pointers */
  وإلا إذا ((codel == POINTER_TYPE || codel == REFERENCE_TYPE)
	   && (coder == codel))
    {
      /* If RHS refers to a built-in declared without a prototype
	 BLTIN is the declaration of the built-in with a prototype
	 and RHSTYPE is set to the actual type of the built-in.  */
      شجرة bltin;
      rhstype = type_or_builtin_type (rhs, &bltin);

      شجرة ttl = شجرة_TYPE (type);
      شجرة ttr = شجرة_TYPE (rhstype);
      منطقي is_opaque_pointer;
      منطقي target_cmp = خطأ;   /* Cache comp_target_types () result.  */
      addr_space_t asl;
      addr_space_t asr;

      شجرة mvl = remove_qualifiers (ttl);
      شجرة mvr = remove_qualifiers (ttr);

      /* Opaque pointers are treated like void pointers.  */
      is_opaque_pointer = vector_targets_convertible_p (ttl, ttr);

      /* The Plan 9 compiler permits a pointer to a struct to be
	 automatically converted into a pointer to an anonymous field
	 within the struct.  */
      إذا (flag_plan9_extensions
	  && RECORD_OR_UNION_TYPE_P (mvl)
	  && RECORD_OR_UNION_TYPE_P (mvr)
	  && mvl != mvr)
	{
	  شجرة new_rhs = convert_to_anonymous_field (location, type, rhs);
	  إذا (new_rhs != NULL_شجرة)
	    {
	      rhs = new_rhs;
	      rhstype = شجرة_TYPE (rhs);
	      coder = شجرة_CODE (rhstype);
	      ttr = شجرة_TYPE (rhstype);
	      mvr = TYPE_MAIN_VARIANT (ttr);
	    }
	}

      /* C++ does not allow the implicit conversion void* -> T*.  However,
	 for the purpose of reducing the number of false positives, we
	 tolerate the special case of

		int *p = NULL;

	 where NULL is typically defined in C to be '(void *) 0'.  */
      إذا (VOID_TYPE_P (ttr) && rhs != null_pointer_عقدة && !VOID_TYPE_P (ttl))
	warning_at (errtype == ic_argpass ? تعبير_loc : location,
		    OPT_Wc___compat,
		    "request for implicit conversion "
		    "from %qT to %qT not permitted in C++", rhstype, type);

      /* Warn of new allocations that are not big enough for the target
	 type.  */
      إذا (warn_alloc_size && شجرة_CODE (rhs) == CALL_تعبير)
	إذا (شجرة fndecl = get_callee_fndecl (rhs))
	  إذا (DECL_IS_MALLOC (fndecl))
	    {
	      شجرة attrs = TYPE_ATTRIBUTES (شجرة_TYPE (fndecl));
	      شجرة alloc_size = lookup_attribute ("alloc_size", attrs);
	      إذا (alloc_size)
		warn_for_alloc_size (location, ttl, rhs, alloc_size);
	    }

      /* See if the pointers point to incompatible address spaces.  */
      asl = TYPE_ADDR_SPACE (ttl);
      asr = TYPE_ADDR_SPACE (ttr);
      إذا (!null_pointer_constant_p (rhs)
	  && asr != asl && !targetm.addr_space.subset_p (asr, asl))
	{
	  auto_diagnostic_group d;
	  منطقي diagnosed = true;
	  بدل (errtype)
	    {
	    حالة ic_argpass:
	      {
		ثابت حرف رسالة[] = G_("passing argument %d of %qE from "
				      "pointer to non-enclosed address space");
		إذا (warnopt)
		  diagnosed
		    = warning_at (تعبير_loc, warnopt, رسالة, parmnum, rname);
		وإلا
		  error_at (تعبير_loc, رسالة, parmnum, rname);
	      اكسر;
	      }
	    حالة ic_assign:
	      {
		ثابت حرف رسالة[] = G_("assignment from pointer to "
				      "non-enclosed address space");
		إذا (warnopt)
		  diagnosed = warning_at (location, warnopt, رسالة);
		وإلا
		  error_at (location, رسالة);
		اكسر;
	      }
	    حالة ic_init:
	    حالة ic_init_const:
	      {
		ثابت حرف رسالة[] = G_("initialization from pointer to "
				      "non-enclosed address space");
		إذا (warnopt)
		  diagnosed = warning_at (location, warnopt, رسالة);
		وإلا
		  error_at (location, رسالة);
		اكسر;
	      }
	    حالة ic_return:
	      {
		ثابت حرف رسالة[] = G_("return from pointer to "
				      "non-enclosed address space");
		إذا (warnopt)
		  diagnosed = warning_at (location, warnopt, رسالة);
		وإلا
		  error_at (location, رسالة);
		اكسر;
	      }
	    افتراضي:
	      gcc_unreachable ();
	    }
	  إذا (diagnosed)
	    {
	      إذا (errtype == ic_argpass)
		inform_for_arg (fundecl, تعبير_loc, parmnum, type, rhstype);
	      وإلا
		inform (location, "expected %qT but pointer is of type %qT",
			type, rhstype);
	    }
	  أرجع error_mark_عقدة;
	}

      /* Check if the right-hand side has a format attribute but the
	 left-hand side doesn't.  */
      إذا (warn_suggest_attribute_format
	  && check_missing_format_attribute (type, rhstype))
	{
	  بدل (errtype)
	  {
	  حالة ic_argpass:
	    warning_at (تعبير_loc, OPT_Wsuggest_attribute_format,
			"argument %d of %qE might be "
			"a candidate for a format attribute",
			parmnum, rname);
	    اكسر;
	  حالة ic_assign:
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
      إذا (warn_scalar_storage_order
	  && !null_pointer_constant_p (rhs)
	  && (AGGREGATE_TYPE_P (ttl) && TYPE_REVERSE_STORAGE_ORDER (ttl))
	     != (AGGREGATE_TYPE_P (ttr) && TYPE_REVERSE_STORAGE_ORDER (ttr)))
	{
	  شجرة t;

	  بدل (errtype)
	  {
	  حالة ic_argpass:
	    /* Do not warn for built-in functions, for example memcpy, since we
	       control how they behave and they can be useful in this area.  */
	    إذا (شجرة_CODE (rname) != FUNCTION_DECL
		|| !fndecl_built_in_p (rname))
	      warning_at (location, OPT_Wscalar_storage_order,
			  "passing argument %d of %qE from incompatible "
			  "scalar storage order", parmnum, rname);
	    اكسر;
	  حالة ic_assign:
	    /* Do not warn if the RHS is a call to a function that returns a
	       pointer that is not an alias.  */
	    إذا (شجرة_CODE (rhs) != CALL_تعبير
		|| (t = get_callee_fndecl (rhs)) == NULL_شجرة
		|| !DECL_IS_MALLOC (t))
	      warning_at (location, OPT_Wscalar_storage_order,
			  "assignment to %qT from pointer type %qT with "
			  "incompatible scalar storage order", type, rhstype);
	    اكسر;
	  حالة ic_init:
	  حالة ic_init_const:
	    /* Likewise.  */
	    إذا (شجرة_CODE (rhs) != CALL_تعبير
		|| (t = get_callee_fndecl (rhs)) == NULL_شجرة
		|| !DECL_IS_MALLOC (t))
	      warning_at (location, OPT_Wscalar_storage_order,
			  "initialization of %qT from pointer type %qT with "
			  "incompatible scalar storage order", type, rhstype);
	    اكسر;
	  حالة ic_return:
	    warning_at (location, OPT_Wscalar_storage_order,
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
	  || (target_cmp = comp_target_types (location, type, rhstype))
	  || is_opaque_pointer
	  || ((c_common_unsigned_type (mvl)
	       == c_common_unsigned_type (mvr))
	      && (c_common_signed_type (mvl)
		  == c_common_signed_type (mvr))
	      && TYPE_ATOMIC (mvl) == TYPE_ATOMIC (mvr)))
	{
	  /* Warn about loss of qualifers from pointers to arrays with
	     qualifiers on the element type. */
	  إذا (شجرة_CODE (ttr) == ARRAY_TYPE)
	    {
	      ttr = strip_array_types (ttr);
	      ttl = strip_array_types (ttl);

	      إذا (TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttr)
		  & ~TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttl))
		WARNING_FOR_QUALIFIERS (flag_isoc23,
					location, تعبير_loc,
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
	      && ((VOID_TYPE_P (ttl) && شجرة_CODE (ttr) == FUNCTION_TYPE)
		  ||
		  (VOID_TYPE_P (ttr)
		   && !null_pointer_constant
		   && شجرة_CODE (ttl) == FUNCTION_TYPE)))
	    PEDWARN_FOR_ASSIGNMENT (location, تعبير_loc, OPT_Wpedantic,
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
	  وإلا إذا (شجرة_CODE (ttr) != FUNCTION_TYPE
		   && شجرة_CODE (ttl) != FUNCTION_TYPE)
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
		PEDWARN_FOR_QUALIFIERS (location, تعبير_loc,
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
		       || target_cmp)
		;
	      /* If there is a mismatch, do warn.  */
	      وإلا إذا (warn_pointer_sign)
		بدل (errtype)
		  {
		  حالة ic_argpass:
		    {
		      auto_diagnostic_group d;
		      range_label_for_type_mismatch rhs_label (rhstype, type);
		      gcc_rich_location richloc (تعبير_loc, &rhs_label,
						 highlight_colors::actual);
		      إذا (pedwarn (&richloc, OPT_Wpointer_sign,
				   "pointer targets in passing argument %d of "
				   "%qE differ in signedness", parmnum, rname))
			inform_for_arg (fundecl, تعبير_loc, parmnum, type,
					rhstype);
		    }
		    اكسر;
		  حالة ic_assign:
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
	  وإلا إذا (شجرة_CODE (ttl) == FUNCTION_TYPE
		   && شجرة_CODE (ttr) == FUNCTION_TYPE)
	    {
	      /* Because const and volatile on functions are restrictions
		 that say the function will not do certain things,
		 it is okay to use a const or volatile function
		 where an ordinary one is wanted, but not vice-versa.  */
	      إذا (TYPE_QUALS_NO_ADDR_SPACE (ttl)
		  & ~TYPE_QUALS_NO_ADDR_SPACE (ttr))
		PEDWARN_FOR_QUALIFIERS (location, تعبير_loc,
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
	  auto_diagnostic_group d;
	  منطقي warned = خطأ;
	  pp_markup::element_expected_type e_type (type);
	  pp_markup::element_actual_type e_rhstype (rhstype);
	  بدل (errtype)
	    {
	    حالة ic_argpass:
	      {
		range_label_for_type_mismatch rhs_label (rhstype, type);
		gcc_rich_location richloc (تعبير_loc, &rhs_label,
					   highlight_colors::actual);
		warned
		  = permerror_opt (&richloc, OPT_Wincompatible_pointer_types,
				   "passing argument %d of %qE from "
				   "incompatible pointer type",
				   parmnum, rname);
		إذا (warned)
		  inform_for_arg (fundecl, تعبير_loc, parmnum, type, rhstype);
	      }
	      اكسر;
	    حالة ic_assign:
	      إذا (bltin)
		warned
		  = permerror_opt (location, OPT_Wincompatible_pointer_types,
				   "assignment to %e from pointer to "
				   "%qD with incompatible type %e",
				   &e_type, bltin, &e_rhstype);
	      وإلا
		warned
		  = permerror_opt (location, OPT_Wincompatible_pointer_types,
				   "assignment to %e from incompatible "
				   "pointer type %e",
				   &e_type, &e_rhstype);
	      اكسر;
	    حالة ic_init:
	    حالة ic_init_const:
	      إذا (bltin)
		warned
		  = permerror_init (location, OPT_Wincompatible_pointer_types,
				    "initialization of %e from pointer to "
				    "%qD with incompatible type %e",
				    &e_type, bltin, &e_rhstype);
	      وإلا
		warned
		  = permerror_init (location, OPT_Wincompatible_pointer_types,
				    "initialization of %e from incompatible "
				    "pointer type %e",
				    &e_type, &e_rhstype);
	      اكسر;
	    حالة ic_return:
	      إذا (bltin)
		warned
		  = permerror_opt (location, OPT_Wincompatible_pointer_types,
				   "returning pointer to %qD of type %e from "
				   "a function with incompatible type %e",
				   bltin, &e_rhstype, &e_type);
	      وإلا
		warned
		  = permerror_opt (location, OPT_Wincompatible_pointer_types,
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
	      إذا (شجرة_CODE (rhs) == ADDR_تعبير
		  && شجرة_CODE (شجرة_OPERAND (rhs, 0)) == FUNCTION_DECL)
		{
		  شجرة rhs_fndecl = شجرة_OPERAND (rhs, 0);
		  إذا (!DECL_IS_UNDECLARED_BUILTIN (rhs_fndecl))
		    {
		      gcc_rich_location richloc
			(DECL_SOURCE_LOCATION (rhs_fndecl), nullptr,
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
      warn_for_address_of_packed_member (type, orig_rhs);

      أرجع convert (type, rhs);
    }
  وإلا إذا (codel == POINTER_TYPE && coder == ARRAY_TYPE)
    {
      /* ??? This should not be an error when inlining calls to
	 unprototyped functions.  */
      ثابت حرف رسالة[] = "invalid use of non-lvalue array";
      إذا (warnopt)
	warning_at (location, warnopt, رسالة);
      وإلا
	error_at (location, رسالة);
      أرجع error_mark_عقدة;
    }
  وإلا إذا (codel == POINTER_TYPE
	   && (coder == INTEGER_TYPE
	       || coder == ENUMERAL_TYPE
	       || coder == BOOLEAN_TYPE
	       || coder == NULLPTR_TYPE
	       || coder == BITINT_TYPE))
    {
      إذا (null_pointer_constant && c_inhibit_evaluation_warnings == 0
	  && coder != NULLPTR_TYPE)
	warning_at (location, OPT_Wzero_as_null_pointer_constant,
		    "zero as null pointer constant");
      /* A NULLPTR type is just a nullptr always.  */
      إذا (coder == NULLPTR_TYPE)
	أرجع omit_one_operand_loc (تعبير_loc, type, nullptr_عقدة, rhs);
      /* An explicit constant 0 or type nullptr_t can convert to a pointer,
	 or one that results from arithmetic, even including a cast to
	 integer type.  */
      وإلا إذا (!null_pointer_constant)
	بدل (errtype)
	  {
	  حالة ic_argpass:
	    {
	      auto_diagnostic_group d;
	      range_label_for_type_mismatch rhs_label (rhstype, type);
	      gcc_rich_location richloc (تعبير_loc, &rhs_label,
					 highlight_colors::actual);
	      إذا (permerror_opt (&richloc, OPT_Wint_conversion,
				 "passing argument %d of %qE makes pointer "
				 "from integer without a cast", parmnum, rname))
		{
		  maybe_emit_indirection_note (تعبير_loc, rhs, type);
		  inform_for_arg (fundecl, تعبير_loc, parmnum, type, rhstype);
		}
	    }
	    اكسر;
	  حالة ic_assign:
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
	   && coder == POINTER_TYPE)
    {
      بدل (errtype)
	{
	حالة ic_argpass:
	  {
	    auto_diagnostic_group d;
	    range_label_for_type_mismatch rhs_label (rhstype, type);
	    gcc_rich_location richloc (تعبير_loc, &rhs_label,
				       highlight_colors::actual);
	    إذا (permerror_opt (&richloc, OPT_Wint_conversion,
			       "passing argument %d of %qE makes integer from "
			       "pointer without a cast", parmnum, rname))
	      {
		maybe_emit_indirection_note (تعبير_loc, rhs, type);
		inform_for_arg (fundecl, تعبير_loc, parmnum, type, rhstype);
	      }
	  }
	  اكسر;
	حالة ic_assign:
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
	   && (coder == POINTER_TYPE || coder == NULLPTR_TYPE))
    {
      شجرة ret;
      منطقي save = in_late_ثنائي_op;
      in_late_ثنائي_op = true;
      ret = convert (type, rhs);
      in_late_ثنائي_op = save;
      أرجع ret;
    }
  وإلا إذا (codel == NULLPTR_TYPE && null_pointer_constant)
    أرجع convert (type, rhs);

  بدل (errtype)
    {
    حالة ic_argpass:
      {
	auto_diagnostic_group d;
	range_label_for_type_mismatch rhs_label (rhstype, type);
	gcc_rich_location richloc (تعبير_loc, &rhs_label,
				   highlight_colors::actual);
	ثابت حرف رسالة[] = G_("incompatible type for argument %d of %qE");
	إذا (warnopt)
	  warning_at (تعبير_loc, warnopt, رسالة, parmnum, rname);
	وإلا
	  error_at (&richloc, رسالة, parmnum, rname);
	inform_for_arg (fundecl, تعبير_loc, parmnum, type, rhstype);
      }
      اكسر;
    حالة ic_assign:
      {
	ثابت حرف رسالة[]
	  = G_("incompatible types when assigning to type %qT from type %qT");
	إذا (warnopt)
	  warning_at (تعبير_loc, 0, رسالة, type, rhstype);
	وإلا
	  error_at (تعبير_loc, رسالة, type, rhstype);
	اكسر;
      }
    حالة ic_init:
    حالة ic_init_const:
      {
	ثابت حرف رسالة[]
	  = G_("incompatible types when initializing type %qT using type %qT");
	إذا (warnopt)
	  warning_at (location, 0, رسالة, type, rhstype);
	وإلا
	  error_at (location, رسالة, type, rhstype);
	اكسر;
      }
    حالة ic_return:
      {
	ثابت حرف رسالة[]
	  = G_("incompatible types when returning type %qT but %qT was expected");
	إذا (warnopt)
	  warning_at (location, 0, رسالة, rhstype, type);
	وإلا
	  error_at (location, رسالة, rhstype, type);
	اكسر;
      }
    افتراضي:
      gcc_unreachable ();
    }

  أرجع error_mark_عقدة;
}

/* If VALUE is a compound expr all of whose expressions are constant, then
   return its value.  Otherwise, return error_mark_node.

   This is for handling COMPOUND_EXPRs as initializer elements
   which is allowed with a warning when -pedantic is specified.  */

ساكن شجرة
valid_compound_تعبير_initializer (شجرة قيمة, شجرة endtype)
{
  إذا (شجرة_CODE (قيمة) == COMPOUND_تعبير)
    {
      إذا (valid_compound_تعبير_initializer (شجرة_OPERAND (قيمة, 0), endtype)
	  == error_mark_عقدة)
	أرجع error_mark_عقدة;
      أرجع valid_compound_تعبير_initializer (شجرة_OPERAND (قيمة, 1),
					      endtype);
    }
  وإلا إذا (!initializer_constant_valid_p (قيمة, endtype))
    أرجع error_mark_عقدة;
  وإلا
    أرجع قيمة;
}

/* Perform appropriate conversions on the initial value of a variable,
   store it in the declaration DECL,
   and print any error messages that are appropriate.
   If ORIGTYPE is not NULL_TREE, it is the original type of INIT.
   If the init is invalid, store an ERROR_MARK.

   INIT_LOC is the location of the initial value.  */

فراغ
store_init_قيمة (location_t init_loc, شجرة decl, شجرة init, شجرة origtype)
{
  شجرة قيمة, type;
  منطقي npc = خطأ;
  منطقي int_const_تعبير = خطأ;
  منطقي arith_const_تعبير = خطأ;

  /* If variable's type was invalidly declared, just ignore it.  */

  type = شجرة_TYPE (decl);
  إذا (شجرة_CODE (type) == ERROR_MARK)
    أرجع;

  /* Digest the specified initializer into an expression.  */

  إذا (init)
    {
      npc = null_pointer_constant_p (init);
      int_const_تعبير = (شجرة_CODE (init) == INTEGER_CST
			&& !شجرة_OVERFLOW (init)
			&& INTEGRAL_TYPE_P (شجرة_TYPE (init)));
      /* Not fully determined before folding.  */
      arith_const_تعبير = true;
    }
  منطقي constexpr_p = (VAR_P (decl)
		      && C_DECL_DECLARED_CONSTEXPR (decl));
  قيمة = digest_init (init_loc, decl, type, init, origtype, npc,
		       int_const_تعبير, arith_const_تعبير, true,
		       شجرة_STATIC (decl) || constexpr_p, constexpr_p);

  /* Store the expression if valid; else report error.  */

  إذا (!in_system_header_at (مدخل_location)
      && AGGREGATE_TYPE_P (شجرة_TYPE (decl)) && !شجرة_STATIC (decl))
    warning (OPT_Wtraditional, "traditional C rejects automatic "
	     "aggregate initialization");

  إذا (قيمة != error_mark_عقدة || شجرة_CODE (decl) != FUNCTION_DECL)
    DECL_INITIAL (decl) = قيمة;

  /* ANSI wants warnings about out-of-range constant initializers.  */
  STRIP_TYPE_NOPS (قيمة);
  إذا (شجرة_STATIC (decl))
    constant_expression_warning (قيمة);

  /* Check if we need to set array size from compound literal size.  */
  إذا (شجرة_CODE (type) == ARRAY_TYPE
      && TYPE_DOMAIN (type) == NULL_شجرة
      && قيمة != error_mark_عقدة)
    {
      شجرة inside_init = init;

      STRIP_TYPE_NOPS (inside_init);
      inside_init = fold (inside_init);

      إذا (شجرة_CODE (inside_init) == COMPOUND_LITERAL_تعبير)
	{
	  شجرة cldecl = COMPOUND_LITERAL_تعبير_DECL (inside_init);

	  إذا (TYPE_DOMAIN (شجرة_TYPE (cldecl)))
	    {
	      /* For int foo[] = (int [3]){1}; we need to set array size
		 now since later on array initializer will be just the
		 brace enclosed list of the compound literal.  */
	      شجرة etype = strip_array_types (شجرة_TYPE (decl));
	      type = build_distinct_type_copy (TYPE_MAIN_VARIANT (type));
	      TYPE_DOMAIN (type) = TYPE_DOMAIN (شجرة_TYPE (cldecl));
	      layout_type (type);
	      layout_decl (cldecl, 0);
	      شجرة_TYPE (decl)
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
  صحيح kind;
  اتحاد
    {
      unsigned HOST_WIDE_INT i;
      ثابت حرف *s;
    } u;
};

#define SPELLING_STRING 1
#define SPELLING_MEMBER 2
#define SPELLING_BOUNDS 3

ساكن بنية spelling *spelling;	/* Next stack element (unused).  */
ساكن بنية spelling *spelling_base;	/* Spelling stack base.  */
ساكن صحيح spelling_size;		/* Size of the spelling stack.  */

/* Macros to save and restore the spelling stack around push_... functions.
   Alternative to SAVE_SPELLING_STACK.  */

#define SPELLING_DEPTH() (spelling - spelling_base)
#define RESTORE_SPELLING_DEPTH(DEPTH) (spelling = spelling_base + (DEPTH))

/* Push an element on the spelling stack with type KIND and assign VALUE
   to MEMBER.  */

#define ادفع_SPELLING(KIND, قيمة_2, MEMBER)				\
{									\
  صحيح depth = SPELLING_DEPTH ();					\
									\
  إذا (depth >= spelling_size)						\
    {									\
      spelling_size += 10;						\
      spelling_base = XRESIZEVEC (بنية spelling, spelling_base,	\
				  spelling_size);			\
      RESTORE_SPELLING_DEPTH (depth);					\
    }									\
									\
  spelling->kind = (KIND);						\
  spelling->MEMBER = (قيمة_2);						\
  spelling++;								\
}

/* Push STRING on the stack.  Printed literally.  */

ساكن فراغ
ادفع_string (ثابت حرف *string)
{
  ادفع_SPELLING (SPELLING_STRING, string, u.s);
}

/* Push a member name on the stack.  Printed as '.' STRING.  */

ساكن فراغ
ادفع_member_name (شجرة decl)
{
  ثابت حرف *ثابت string
    = (DECL_NAME (decl)
       ? identifier_to_locale (IDENTIFIER_POINTER (DECL_NAME (decl)))
       : _("<anonymous>"));
  ادفع_SPELLING (SPELLING_MEMBER, string, u.s);
}

/* Push an array bounds on the stack.  Printed as [BOUNDS].  */

ساكن فراغ
ادفع_array_bounds (unsigned HOST_WIDE_INT bounds)
{
  ادفع_SPELLING (SPELLING_BOUNDS, bounds, u.i);
}

/* Compute the maximum size in bytes of the printed spelling.  */

ساكن صحيح
spelling_length (فراغ)
{
  صحيح size = 0;
  بنية spelling *p;

  لكل (p = spelling_base; p < spelling; p++)
    {
      إذا (p->kind == SPELLING_BOUNDS)
	size += 25;
      وإلا
	size += strlen (p->u.s) + 1;
    }

  أرجع size;
}

/* Print the spelling to BUFFER and return it.  */

ساكن حرف *
اطبع_spelling (حرف *buffer)
{
  حرف *d = buffer;
  بنية spelling *p;

  لكل (p = spelling_base; p < spelling; p++)
    إذا (p->kind == SPELLING_BOUNDS)
      {
	sprintf (d, "[" HOST_WIDE_INT_اطبع_UNSIGNED "]", p->u.i);
	d += strlen (d);
      }
    وإلا
      {
	ثابت حرف *s;
	إذا (p->kind == SPELLING_MEMBER)
	  *d++ = '.';
	لكل (s = p->u.s; (*d = *s++); d++)
	  ;
      }
  *d++ = '\0';
  أرجع buffer;
}

/* Check whether INIT, a floating or integer constant, is
   representable in TYPE, a real floating type with the same radix or
   a decimal floating type initialized with a binary floating
   constant.  Return true if OK, false if not.  */
ساكن منطقي
constexpr_init_fits_real_type (شجرة type, شجرة init)
{
  gcc_assert (SCALAR_FLOAT_TYPE_P (type));
  gcc_assert (شجرة_CODE (init) == INTEGER_CST || شجرة_CODE (init) == REAL_CST);
  إذا (شجرة_CODE (init) == REAL_CST
      && TYPE_MODE (شجرة_TYPE (init)) == TYPE_MODE (type))
    {
      /* Same mode, no conversion required except for the case of
	 signaling NaNs if the types are incompatible (e.g. double and
	 long double with the same mode).  */
      إذا (REAL_قيمة_ISSIGNALING_NAN (شجرة_REAL_CST (init))
	  && !comptypes (TYPE_MAIN_VARIANT (type),
			 TYPE_MAIN_VARIANT (شجرة_TYPE (init))))
	أرجع خطأ;
      أرجع true;
    }
  إذا (شجرة_CODE (init) == INTEGER_CST)
    {
      شجرة converted = build_real_from_int_cst (type, init);
      منطقي fail = خطأ;
      wide_int w = real_to_integer (&شجرة_REAL_CST (converted), &fail,
				    TYPE_PRECISION (شجرة_TYPE (init)));
      أرجع !fail && wi::eq_p (w, wi::to_wide (init));
    }
  إذا (REAL_قيمة_ISSIGNALING_NAN (شجرة_REAL_CST (init)))
    أرجع خطأ;
  إذا ((REAL_قيمة_ISINF (شجرة_REAL_CST (init))
       && MODE_HAS_INFINITIES (TYPE_MODE (type)))
      || (REAL_قيمة_ISNAN (شجرة_REAL_CST (init))
	  && MODE_HAS_NANS (TYPE_MODE (type))))
    أرجع true;
  إذا (DECIMAL_FLOAT_TYPE_P (type)
      && !DECIMAL_FLOAT_TYPE_P (شجرة_TYPE (init)))
    {
      /* This is valid if the real number represented by the
	 initializer can be exactly represented in the decimal
	 type.  Compare the values using MPFR.  */
      REAL_قيمة_TYPE t;
      real_convert (&t, TYPE_MODE (type), &شجرة_REAL_CST (init));
      mpfr_t bin_val, dec_val;
      mpfr_init2 (bin_val, REAL_MODE_FORMAT (TYPE_MODE (شجرة_TYPE (init)))->p);
      mpfr_init2 (dec_val, REAL_MODE_FORMAT (TYPE_MODE (شجرة_TYPE (init)))->p);
      mpfr_from_real (bin_val, &شجرة_REAL_CST (init), MPFR_RNDN);
      حرف string[256];
      real_to_decimal (string, &t, حجم string, 0, 1);
      منطقي res = (mpfr_strtofr (dec_val, string, عدم, 10, MPFR_RNDN) == 0
		  && mpfr_equal_p (bin_val, dec_val));
      mpfr_clear (bin_val);
      mpfr_clear (dec_val);
      أرجع res;
    }
  /* exact_real_truncate is not quite right here, since it doesn't
     allow even an exact conversion to subnormal values.  */
  REAL_قيمة_TYPE t;
  real_convert (&t, TYPE_MODE (type), &شجرة_REAL_CST (init));
  أرجع real_identical (&t, &شجرة_REAL_CST (init));
}

/* Check whether INIT (location LOC) is valid as a 'constexpr'
   initializer for type TYPE, and give an error if not.  INIT has
   already been folded and verified to be constant.  INT_CONST_EXPR
   and ARITH_CONST_EXPR say whether it is an integer constant
   expression or arithmetic constant expression, respectively.  If
   TYPE is not a scalar type, this function does nothing.  */

ساكن فراغ
check_constexpr_init (location_t loc, شجرة type, شجرة init,
		      منطقي int_const_تعبير, منطقي arith_const_تعبير)
{
  إذا (POINTER_TYPE_P (type))
    {
      /* The initializer must be null.  */
      إذا (شجرة_CODE (init) != INTEGER_CST || !integer_zerop (init))
	error_at (loc, "%<constexpr%> pointer initializer is not null");
      أرجع;
    }
  إذا (INTEGRAL_TYPE_P (type))
    {
      /* The initializer must be an integer constant expression,
	 representable in the target type.  */
      إذا (!int_const_تعبير)
	{
	  إذا (شجرة_CODE (init) == RAW_DATA_CST
	      && TYPE_PRECISION (type) == CHAR_BIT)
	    {
	      إذا (!TYPE_UNSIGNED (type))
		لكل (unsigned صحيح i = 0;
		     i < (unsigned) RAW_DATA_LENGTH (init); ++i)
		  إذا (RAW_DATA_SCHAR_ELT (init, i) < 0)
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
      وإلا إذا (!int_fits_type_p (init, type))
	error_at (loc, "%<constexpr%> initializer not representable in "
		  "type of object");
      أرجع;
    }
  /* We don't apply any extra checks to extension types such as vector
     or fixed-point types.  */
  إذا (شجرة_CODE (type) != REAL_TYPE && شجرة_CODE (type) != COMPLEX_TYPE)
    أرجع;
  إذا (!arith_const_تعبير)
    {
      error_at (loc, "%<constexpr%> initializer is not an arithmetic "
		"constant expression");
      أرجع;
    }
  /* We don't apply any extra checks to complex integers.  */
  إذا (شجرة_CODE (type) == COMPLEX_TYPE
      && شجرة_CODE (شجرة_TYPE (type)) != REAL_TYPE)
    أرجع;
  /* Following N3082, a real type cannot be initialized from a complex
     type and a binary type cannot be initialized from a decimal type
     (but initializing a decimal type from a binary type is OK).
     Signaling NaN initializers are OK only if the types are
     compatible (not just the same mode); all quiet NaN and infinity
     initializations are considered to preserve the value.  */
  إذا (شجرة_CODE (شجرة_TYPE (init)) == COMPLEX_TYPE
      && SCALAR_FLOAT_TYPE_P (type))
    {
      error_at (loc, "%<constexpr%> initializer for a real type is of "
		"complex type");
      أرجع;
    }
  إذا (SCALAR_FLOAT_TYPE_P (type)
      && SCALAR_FLOAT_TYPE_P (شجرة_TYPE (init))
      && DECIMAL_FLOAT_TYPE_P (شجرة_TYPE (init))
      && !DECIMAL_FLOAT_TYPE_P (type))
    {
      error_at (loc, "%<constexpr%> initializer for a binary "
		"floating-point type is of decimal type");
      أرجع;
    }
  منطقي fits;
  إذا (شجرة_CODE (type) == COMPLEX_TYPE)
    {
      بدل (شجرة_CODE (init))
	{
	حالة INTEGER_CST:
	حالة REAL_CST:
	  fits = constexpr_init_fits_real_type (شجرة_TYPE (type), init);
	  اكسر;
	حالة COMPLEX_CST:
	  fits = (constexpr_init_fits_real_type (شجرة_TYPE (type),
						 شجرة_REALPART (init))
		  && constexpr_init_fits_real_type (شجرة_TYPE (type),
						    شجرة_IMAGPART (init)));
	  اكسر;
	افتراضي:
	  gcc_unreachable ();
	}
    }
  وإلا
    fits = constexpr_init_fits_real_type (type, init);
  إذا (!fits)
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

ساكن شجرة
digest_init (location_t init_loc, شجرة decl, شجرة type, شجرة init,
	     شجرة origtype, منطقي null_pointer_constant, منطقي int_const_تعبير,
	     منطقي arith_const_تعبير, منطقي strict_string,
	     منطقي require_constant, منطقي require_constexpr)
{
  تعداد شجرة_code code = شجرة_CODE (type);
  شجرة inside_init = init;
  شجرة semantic_type = NULL_شجرة;
  منطقي maybe_const = true;

  إذا (type == error_mark_عقدة
      || !init
      || error_operand_p (init))
    أرجع error_mark_عقدة;

  STRIP_TYPE_NOPS (inside_init);

  /* If require_constant is TRUE,  when the initializer is a call to
     .ACCESS_WITH_SIZE, use the first argument as the initializer.
     For example:
     y = (char *) .ACCESS_WITH_SIZE ((char *) &static_annotated.c,...)
     will be converted to
     y = &static_annotated.c.  */

  إذا (require_constant
      && شجرة_CODE (inside_init) == NOP_تعبير
      && شجرة_CODE (شجرة_OPERAND (inside_init, 0)) == CALL_تعبير
      && is_access_with_size_p (شجرة_OPERAND (inside_init, 0)))
    inside_init
      = get_ref_from_access_with_size (شجرة_OPERAND (inside_init, 0));

  إذا (!c_in_omp_for)
    {
      إذا (شجرة_CODE (inside_init) == EXCESS_PRECISION_تعبير)
	{
	  semantic_type = شجرة_TYPE (inside_init);
	  inside_init = شجرة_OPERAND (inside_init, 0);
	}
      inside_init = c_fully_fold (inside_init, require_constant, &maybe_const);
    }
  /* TODO: this may not detect all cases of expressions folding to
     constants that are not arithmetic constant expressions.  */
  إذا (!maybe_const)
    arith_const_تعبير = خطأ;
  وإلا إذا (!INTEGRAL_TYPE_P (شجرة_TYPE (inside_init))
	   && شجرة_CODE (شجرة_TYPE (inside_init)) != REAL_TYPE
	   && شجرة_CODE (شجرة_TYPE (inside_init)) != COMPLEX_TYPE)
    arith_const_تعبير = خطأ;
  وإلا إذا (شجرة_CODE (inside_init) != INTEGER_CST
	   && شجرة_CODE (inside_init) != REAL_CST
	   && شجرة_CODE (inside_init) != COMPLEX_CST
	   && شجرة_CODE (inside_init) != RAW_DATA_CST)
    arith_const_تعبير = خطأ;
  وإلا إذا (شجرة_OVERFLOW (inside_init))
    arith_const_تعبير = خطأ;

  /* Initialization of an array of chars from a string constant
     optionally enclosed in braces.  */

  إذا (code == ARRAY_TYPE && inside_init
      && شجرة_CODE (inside_init) == STRING_CST)
    {
      شجرة typ1
	= (TYPE_ATOMIC (شجرة_TYPE (type))
	   ? c_build_qualified_type (TYPE_MAIN_VARIANT (شجرة_TYPE (type)),
				     TYPE_QUAL_ATOMIC)
	   : TYPE_MAIN_VARIANT (شجرة_TYPE (type)));
      /* Note that an array could be both an array of character type
	 and an array of wchar_t if wchar_t is signed char or unsigned
	 char.  */
      منطقي char_array = (typ1 == char_type_عقدة
			 || typ1 == signed_char_type_عقدة
			 || typ1 == unsigned_char_type_عقدة);
      منطقي wchar_array = comptypes (typ1, wchar_type_عقدة);
      منطقي char16_array = comptypes (typ1, char16_type_عقدة);
      منطقي char32_array = comptypes (typ1, char32_type_عقدة);

      إذا (char_array || wchar_array || char16_array || char32_array)
	{
	  بنية c_تعبير تعبير;
	  شجرة typ2 = TYPE_MAIN_VARIANT (شجرة_TYPE (شجرة_TYPE (inside_init)));
	  منطقي incompat_string_cst = خطأ;
	  تعبير.قيمة = inside_init;
	  تعبير.original_code = (strict_string ? STRING_CST : ERROR_MARK);
	  تعبير.original_type = عدم;
	  تعبير.m_decimal = 0;
	  maybe_warn_string_init (init_loc, type, تعبير);

	  إذا (flexible_array_member_type_p (type))
	    pedwarn_init (init_loc, OPT_Wpedantic,
			  "initialization of a flexible array member");

	  إذا (comptypes (TYPE_MAIN_VARIANT (شجرة_TYPE (inside_init)),
			 TYPE_MAIN_VARIANT (type)))
	    أرجع inside_init;

	  إذا (char_array)
	    {
	      إذا (typ2 != char_type_عقدة && typ2 != char8_type_عقدة)
		incompat_string_cst = true;
	    }
	  وإلا إذا (!comptypes (typ1, typ2))
	    incompat_string_cst = true;

          إذا (incompat_string_cst)
            {
	      error_init (init_loc, "cannot initialize array of %qT from "
			  "a string literal with type array of %qT",
			  typ1, typ2);
	      أرجع error_mark_عقدة;
            }

	  إذا (require_constexpr
	      && TYPE_UNSIGNED (typ1) != TYPE_UNSIGNED (typ2))
	    {
	      /* Check if all characters of the string can be
		 represented in the type of the constexpr object being
		 initialized.  */
	      unsigned HOST_WIDE_INT len = شجرة_STRING_LENGTH (inside_init);
	      ثابت unsigned حرف *p =
		(ثابت unsigned حرف *) شجرة_STRING_POINTER (inside_init);
	      gcc_assert (CHAR_TYPE_SIZE == 8 && CHAR_BIT == 8);
	      لكل (unsigned i = 0; i < len; i++)
		إذا (p[i] > 127)
		  {
		    error_init (init_loc, "%<constexpr%> initializer not "
				"representable in type of object");
		    اكسر;
		  }
	    }

	  إذا (TYPE_DOMAIN (type) != NULL_شجرة
	      && TYPE_SIZE (type) != NULL_شجرة
	      && شجرة_CODE (TYPE_SIZE (type)) == INTEGER_CST)
	    {
	      unsigned HOST_WIDE_INT len = شجرة_STRING_LENGTH (inside_init);

	      إذا (compare_شجرة_int (TYPE_SIZE_UNIT (type), len) < 0)
		{
		  unsigned HOST_WIDE_INT avail
		    = شجرة_to_uhwi (TYPE_SIZE_UNIT (type));
		  unsigned unit = TYPE_PRECISION (typ1) / BITS_PER_UNIT;
		  ثابت حرف *p = شجرة_STRING_POINTER (inside_init);

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
			   && get_attr_nonstring_decl (decl) == NULL_شجرة)
		    warning_at (init_loc,
				OPT_Wunterminated_string_initialization,
				"initializer-string for array of %qT "
				"truncates NUL terminator but destination "
				"lacks %qs attribute (%wu chars into %wu "
				"available)", typ1, "nonstring", len, avail);
		}
	    }

	  شجرة_TYPE (inside_init) = type;
	  أرجع inside_init;
	}
      وإلا إذا (INTEGRAL_TYPE_P (typ1))
	{
	  error_init (init_loc, "array of inappropriate type initialized "
		      "from string constant");
	  أرجع error_mark_عقدة;
	}
    }

  /* Build a VECTOR_CST from a *constant* vector constructor.  If the
     vector constructor is not constant (e.g. {1,2,3,foo()}) then punt
     below and handle as a constructor.  */
  إذا (code == VECTOR_TYPE
      && VECTOR_TYPE_P (شجرة_TYPE (inside_init))
      && vector_types_convertible_p (شجرة_TYPE (inside_init), type, true)
      && شجرة_CONSTANT (inside_init))
    {
      إذا (شجرة_CODE (inside_init) == VECTOR_CST
	  && comptypes (TYPE_MAIN_VARIANT (شجرة_TYPE (inside_init)),
			TYPE_MAIN_VARIANT (type)))
	أرجع inside_init;

      إذا (شجرة_CODE (inside_init) == CONSTRUCTOR)
	{
	  unsigned HOST_WIDE_INT ix;
	  شجرة قيمة;
	  منطقي constant_p = true;

	  /* Iterate through elements and check if all constructor
	     elements are *_CSTs.  */
	  FOR_EACH_CONSTRUCTOR_قيمة (CONSTRUCTOR_ELTS (inside_init), ix, قيمة)
	    إذا (!CONSTANT_CLASS_P (قيمة))
	      {
		constant_p = خطأ;
		اكسر;
	      }

	  إذا (constant_p)
	    أرجع build_vector_from_ctor (type,
					   CONSTRUCTOR_ELTS (inside_init));
	}
    }

  إذا (warn_sequence_point)
    verify_sequence_points (inside_init);

  /* Any type can be initialized
     from an expression of the same type, optionally with braces.  */

  إذا (inside_init && شجرة_TYPE (inside_init) != NULL_شجرة
      && (comptypes (TYPE_MAIN_VARIANT (شجرة_TYPE (inside_init)),
		     TYPE_MAIN_VARIANT (type))
	  || (code == ARRAY_TYPE
	      && comptypes (شجرة_TYPE (inside_init), type))
	  || (gnu_vector_type_p (type)
	      && comptypes (شجرة_TYPE (inside_init), type))
	  || (code == POINTER_TYPE
	      && شجرة_CODE (شجرة_TYPE (inside_init)) == ARRAY_TYPE
	      && comptypes (شجرة_TYPE (شجرة_TYPE (inside_init)),
			    شجرة_TYPE (type)))))
    {
      إذا (code == POINTER_TYPE)
	{
	  إذا (شجرة_CODE (شجرة_TYPE (inside_init)) == ARRAY_TYPE)
	    {
	      إذا (شجرة_CODE (inside_init) == STRING_CST
		  || شجرة_CODE (inside_init) == COMPOUND_LITERAL_تعبير)
		inside_init = array_to_pointer_conversion
		  (init_loc, inside_init);
	      وإلا
		{
		  error_init (init_loc, "invalid use of non-lvalue array");
		  أرجع error_mark_عقدة;
		}
	    }
	}

      إذا (code == VECTOR_TYPE || c_hardbool_type_attr (type))
	/* Although the types are compatible, we may require a
	   conversion.  */
	inside_init = convert (type, inside_init);

      إذا ((code == RECORD_TYPE || code == UNION_TYPE)
	  && !comptypes (TYPE_MAIN_VARIANT (type), TYPE_MAIN_VARIANT (شجرة_TYPE (inside_init))))
	{
	  error_init (init_loc, "invalid initializer");
	  أرجع error_mark_عقدة;
	}

      إذا (require_constant
	  && شجرة_CODE (inside_init) == COMPOUND_LITERAL_تعبير)
	{
	  /* As an extension, allow initializing objects with static storage
	     duration with compound literals (which are then treated just as
	     the brace enclosed list they contain).  Also allow this for
	     vectors, as we can only assign them with compound literals.  */
	  إذا (flag_isoc99 && code != VECTOR_TYPE)
	    pedwarn_init (init_loc, OPT_Wpedantic, "initializer element "
			  "is not constant");
	  شجرة decl = COMPOUND_LITERAL_تعبير_DECL (inside_init);
	  inside_init = DECL_INITIAL (decl);
	}

      إذا (code == ARRAY_TYPE && شجرة_CODE (inside_init) != STRING_CST
	  && شجرة_CODE (inside_init) != CONSTRUCTOR)
	{
	  error_init (init_loc, "array initialized from non-constant array "
		      "expression");
	  أرجع error_mark_عقدة;
	}

      /* Compound expressions can only occur here if -Wpedantic or
	 -pedantic-errors is specified.  In the later case, we always want
	 an error.  In the former case, we simply want a warning.  */
      إذا (require_constant && pedantic
	  && شجرة_CODE (inside_init) == COMPOUND_تعبير)
	{
	  inside_init
	    = valid_compound_تعبير_initializer (inside_init,
					       شجرة_TYPE (inside_init));
	  إذا (inside_init == error_mark_عقدة)
	    error_init (init_loc, "initializer element is not constant");
	  وإلا
	    pedwarn_init (init_loc, OPT_Wpedantic,
			  "initializer element is not constant");
	  إذا (flag_pedantic_errors)
	    inside_init = error_mark_عقدة;
	}
      وإلا إذا (require_constant
	       && !initializer_constant_valid_p (inside_init,
						 شجرة_TYPE (inside_init)))
	{
	  error_init (init_loc, "initializer element is not constant");
	  inside_init = error_mark_عقدة;
	}
      وإلا إذا (require_constant && !maybe_const)
	pedwarn_init (init_loc, OPT_Wpedantic,
		      "initializer element is not a constant expression");
      وإلا إذا (require_constexpr)
	check_constexpr_init (init_loc, type, inside_init,
			      int_const_تعبير, arith_const_تعبير);

      /* Added to enable additional -Wsuggest-attribute=format warnings.  */
      إذا (شجرة_CODE (شجرة_TYPE (inside_init)) == POINTER_TYPE)
	inside_init = convert_for_assignment (init_loc, UNKNOWN_LOCATION,
					      type, inside_init, origtype,
					      (require_constant
					       ? ic_init_const
					       : ic_init), null_pointer_constant,
					      NULL_شجرة, NULL_شجرة, 0);
      إذا (شجرة_CODE (inside_init) == RAW_DATA_CST
	  && c_inhibit_evaluation_warnings == 0
	  && warn_conversion
	  && !TYPE_UNSIGNED (type)
	  && TYPE_PRECISION (type) == CHAR_BIT)
	لكل (unsigned صحيح i = 0;
	     i < (unsigned) RAW_DATA_LENGTH (inside_init); ++i)
	  إذا (RAW_DATA_SCHAR_ELT (inside_init, i) < 0)
	    warning_at (init_loc, OPT_Wconversion,
			"conversion from %qT to %qT changes value from "
			"%qd to %qd",
			integer_type_عقدة, type,
			RAW_DATA_UCHAR_ELT (inside_init, i),
			RAW_DATA_SCHAR_ELT (inside_init, i));
      أرجع inside_init;
    }

  /* Handle scalar types, including conversions.  */

  إذا (code == INTEGER_TYPE || code == REAL_TYPE || code == FIXED_POINT_TYPE
      || code == POINTER_TYPE || code == ENUMERAL_TYPE || code == BOOLEAN_TYPE
      || code == COMPLEX_TYPE || code == VECTOR_TYPE || code == NULLPTR_TYPE
      || code == BITINT_TYPE)
    {
      شجرة unconverted_init = inside_init;
      إذا (شجرة_CODE (شجرة_TYPE (init)) == ARRAY_TYPE
	  && (شجرة_CODE (init) == STRING_CST
	      || شجرة_CODE (init) == COMPOUND_LITERAL_تعبير))
	inside_init = init = array_to_pointer_conversion (init_loc, init);
      إذا (semantic_type)
	inside_init = build1 (EXCESS_PRECISION_تعبير, semantic_type,
			      inside_init);
      inside_init
	= convert_for_assignment (init_loc, UNKNOWN_LOCATION, type,
				  inside_init, origtype,
				  require_constant ? ic_init_const : ic_init,
				  null_pointer_constant, NULL_شجرة, NULL_شجرة,
				  0);

      /* Check to see if we have already given an error message.  */
      إذا (inside_init == error_mark_عقدة)
	;
      وإلا إذا (require_constant && !شجرة_CONSTANT (inside_init))
	{
	  error_init (init_loc, "initializer element is not constant");
	  inside_init = error_mark_عقدة;
	}
      وإلا إذا (require_constant
	       && !initializer_constant_valid_p (inside_init,
						 شجرة_TYPE (inside_init)))
	{
	  error_init (init_loc, "initializer element is not computable at "
		      "load time");
	  inside_init = error_mark_عقدة;
	}
      وإلا إذا (require_constant && !maybe_const)
	pedwarn_init (init_loc, OPT_Wpedantic,
		      "initializer element is not a constant expression");
      وإلا إذا (require_constexpr)
	check_constexpr_init (init_loc, type, unconverted_init,
			      int_const_تعبير, arith_const_تعبير);

      أرجع inside_init;
    }

  /* Come here only for records and arrays.  */

  إذا (COMPLETE_TYPE_P (type) && شجرة_CODE (TYPE_SIZE (type)) != INTEGER_CST)
    {
      error_init (init_loc,
		  "variable-sized object may not be initialized except "
		  "with an empty initializer");
      أرجع error_mark_عقدة;
    }

  error_init (init_loc, "invalid initializer");
  أرجع error_mark_عقدة;
}

/* Handle initializers that use braces.  */

/* Type of object we are accumulating a constructor for.
   This type is always a RECORD_TYPE, UNION_TYPE or ARRAY_TYPE.  */
ساكن شجرة constructor_type;

/* For a RECORD_TYPE or UNION_TYPE, this is the chain of fields
   left to fill.  */
ساكن شجرة constructor_fields;

/* For an ARRAY_TYPE, this is the specified index
   at which to store the next element we get.  */
ساكن شجرة constructor_index;

/* For an ARRAY_TYPE, this is the maximum index.  */
ساكن شجرة constructor_max_index;

/* For a RECORD_TYPE, this is the first field not yet written out.  */
ساكن شجرة constructor_unfilled_fields;

/* For an ARRAY_TYPE, this is the index of the first element
   not yet written out.  */
ساكن شجرة constructor_unfilled_index;

/* In a RECORD_TYPE, the byte index of the next consecutive field.
   This is so we can generate gaps between fields, when appropriate.  */
ساكن شجرة constructor_bit_index;

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
ساكن منطقي constructor_zero_padding_bits;

/* 1 if this constructor is a braced scalar initializer (further nested levels
   of braces are an error).  */
ساكن منطقي constructor_braced_scalar;

/* Structure for managing pending initializer elements, organized as an
   AVL tree.  */

بنية init_عقدة
{
  بنية init_عقدة *يسار, *يمين;
  بنية init_عقدة *parent;
  صحيح balance;
  شجرة purpose;
  شجرة قيمة;
  شجرة origtype;
};

/* Tree of pending elements at this constructor level.
   These are elements encountered out of order
   which belong at places we haven't reached yet in actually
   writing the output.
   Will never hold tree nodes across GC runs.  */
ساكن بنية init_عقدة *constructor_pending_elts;

/* The SPELLING_DEPTH of this constructor.  */
ساكن صحيح constructor_depth;

/* DECL node for which an initializer is being read.
   0 means we are reading a constructor expression
   such as (struct foo) {...}.  */
ساكن شجرة constructor_decl;

/* Nonzero if there were any member designators in this initializer.  */
ساكن صحيح constructor_designated;

/* Nesting depth of designator list.  */
ساكن صحيح designator_depth;

/* Nonzero if there were diagnosed errors in this designator list.  */
ساكن صحيح designator_erroneous;


/* This stack has a level for each implicit or explicit level of
   structuring in the initializer, including the outermost one.  It
   saves the values of most of the variables above.  */

بنية constructor_range_مكدس;

بنية constructor_مكدس
{
  بنية constructor_مكدس *next;
  شجرة type;
  شجرة fields;
  شجرة index;
  شجرة max_index;
  شجرة unfilled_index;
  شجرة unfilled_fields;
  شجرة bit_index;
  vec<constructor_elt, va_gc> *elements;
  بنية init_عقدة *pending_elts;
  صحيح offset;
  صحيح depth;
  /* If value nonzero, this value should replace the entire
     constructor at this level.  */
  بنية c_تعبير replacement_قيمة;
  بنية constructor_range_مكدس *range_مكدس;
  حرف constant;
  حرف simple;
  حرف nonconst;
  حرف implicit;
  حرف erroneous;
  حرف outer;
  حرف incremental;
  حرف designated;
  منطقي zero_padding_bits;
  منطقي braced_scalar;
  صحيح designator_depth;
};

ساكن بنية constructor_مكدس *constructor_مكدس;

/* This stack represents designators from some range designator up to
   the last designator in the list.  */

بنية constructor_range_مكدس
{
  بنية constructor_range_مكدس *next, *prev;
  بنية constructor_مكدس *مكدس;
  شجرة range_start;
  شجرة index;
  شجرة range_end;
  شجرة fields;
};

ساكن بنية constructor_range_مكدس *constructor_range_مكدس;

/* This stack records separate initializers that are nested.
   Nested initializers can't happen in ANSI C, but GNU C allows them
   in cases like { ... (struct foo) { ... } ... }.  */

بنية initializer_مكدس
{
  بنية initializer_مكدس *next;
  شجرة decl;
  بنية constructor_مكدس *constructor_مكدس;
  بنية constructor_range_مكدس *constructor_range_مكدس;
  vec<constructor_elt, va_gc> *elements;
  بنية spelling *spelling;
  بنية spelling *spelling_base;
  صحيح spelling_size;
  حرف require_constant_قيمة;
  حرف require_constant_elements;
  حرف require_constexpr_قيمة;
  حرف designated;
  rich_location *missing_brace_richloc;
};

ساكن بنية initializer_مكدس *initializer_مكدس;

/* Prepare to parse and output the initializer for variable DECL.  */

فراغ
start_init (شجرة decl, شجرة asmspec_شجرة ATTRIBUTE_UNUSED,
	    منطقي init_require_constant, منطقي init_require_constexpr,
	    rich_location *richloc)
{
  ثابت حرف *locus;
  بنية initializer_مكدس *p = XNEW (بنية initializer_مكدس);

  p->decl = constructor_decl;
  p->require_constant_قيمة = require_constant_قيمة;
  p->require_constant_elements = require_constant_elements;
  p->require_constexpr_قيمة = require_constexpr_قيمة;
  p->constructor_مكدس = constructor_مكدس;
  p->constructor_range_مكدس = constructor_range_مكدس;
  p->elements = constructor_elements;
  p->spelling = spelling;
  p->spelling_base = spelling_base;
  p->spelling_size = spelling_size;
  p->next = initializer_مكدس;
  p->missing_brace_richloc = richloc;
  p->designated = constructor_designated;
  initializer_مكدس = p;

  constructor_decl = decl;
  constructor_designated = 0;

  require_constant_قيمة = init_require_constant;
  require_constexpr_قيمة = init_require_constexpr;
  إذا (decl != NULL_شجرة && decl != error_mark_عقدة)
    {
      require_constant_elements
	= ((init_require_constant || (pedantic && !flag_isoc99))
	   /* For a scalar, you can always use any value to initialize,
	      even within braces.  */
	   && AGGREGATE_TYPE_P (شجرة_TYPE (decl)));
      locus = identifier_to_locale (IDENTIFIER_POINTER (DECL_NAME (decl)));
    }
  وإلا
    {
      require_constant_elements = خطأ;
      locus = _("(anonymous)");
    }

  constructor_مكدس = 0;
  constructor_range_مكدس = 0;

  found_missing_braces = 0;

  spelling_base = 0;
  spelling_size = 0;
  RESTORE_SPELLING_DEPTH (0);

  إذا (locus)
    ادفع_string (locus);
}

فراغ
finish_init (فراغ)
{
  بنية initializer_مكدس *p = initializer_مكدس;

  /* Free the whole constructor stack of this initializer.  */
  طالما (constructor_مكدس)
    {
      بنية constructor_مكدس *q = constructor_مكدس;
      constructor_مكدس = q->next;
      XDELETE (q);
    }

  gcc_assert (!constructor_range_مكدس);

  /* Pop back to the data of the outer initializer (if any).  */
  XDELETE (spelling_base);

  constructor_decl = p->decl;
  require_constant_قيمة = p->require_constant_قيمة;
  require_constant_elements = p->require_constant_elements;
  require_constexpr_قيمة = p->require_constexpr_قيمة;
  constructor_مكدس = p->constructor_مكدس;
  constructor_designated = p->designated;
  constructor_range_مكدس = p->constructor_range_مكدس;
  constructor_elements = p->elements;
  spelling = p->spelling;
  spelling_base = p->spelling_base;
  spelling_size = p->spelling_size;
  initializer_مكدس = p->next;
  XDELETE (p);
}

/* Call here when we see the initializer is surrounded by braces.
   This is instead of a call to push_init_level;
   it is matched by a call to pop_init_level.

   TYPE is the type to initialize, for a constructor expression.
   For an initializer for a decl, TYPE is zero.  */

فراغ
really_start_incremental_init (شجرة type)
{
  بنية constructor_مكدس *p = XNEW (بنية constructor_مكدس);

  إذا (type == NULL_شجرة)
    type = شجرة_TYPE (constructor_decl);

  إذا (VECTOR_TYPE_P (type)
      && TYPE_VECTOR_OPAQUE (type))
    error ("opaque vector types cannot be initialized");

  p->type = constructor_type;
  p->fields = constructor_fields;
  p->index = constructor_index;
  p->max_index = constructor_max_index;
  p->unfilled_index = constructor_unfilled_index;
  p->unfilled_fields = constructor_unfilled_fields;
  p->bit_index = constructor_bit_index;
  p->elements = constructor_elements;
  p->constant = constructor_constant;
  p->simple = constructor_simple;
  p->nonconst = constructor_nonconst;
  p->erroneous = constructor_erroneous;
  p->pending_elts = constructor_pending_elts;
  p->depth = constructor_depth;
  p->replacement_قيمة.قيمة = 0;
  p->replacement_قيمة.original_code = ERROR_MARK;
  p->replacement_قيمة.original_type = عدم;
  p->implicit = 0;
  p->range_مكدس = 0;
  p->outer = 0;
  p->incremental = constructor_incremental;
  p->designated = constructor_designated;
  p->zero_padding_bits = constructor_zero_padding_bits;
  p->braced_scalar = constructor_braced_scalar;
  p->designator_depth = designator_depth;
  p->next = 0;
  constructor_مكدس = p;

  constructor_constant = 1;
  constructor_simple = 1;
  constructor_nonconst = 0;
  constructor_depth = SPELLING_DEPTH ();
  constructor_elements = عدم;
  constructor_pending_elts = 0;
  constructor_type = type;
  constructor_incremental = 1;
  constructor_designated = 0;
  constructor_zero_padding_bits = خطأ;
  constructor_zeroinit = 1;
  constructor_braced_scalar = خطأ;
  designator_depth = 0;
  designator_erroneous = 0;

  إذا (RECORD_OR_UNION_TYPE_P (constructor_type))
    {
      constructor_fields = TYPE_FIELDS (constructor_type);
      /* Skip any nameless bit fields at the beginning.  */
      طالما (constructor_fields != NULL_شجرة
	     && DECL_UNNAMED_BIT_FIELD (constructor_fields))
	constructor_fields = DECL_CHAIN (constructor_fields);

      constructor_unfilled_fields = constructor_fields;
      constructor_bit_index = bitsize_zero_عقدة;
    }
  وإلا إذا (شجرة_CODE (constructor_type) == ARRAY_TYPE)
    {
      إذا (TYPE_DOMAIN (constructor_type))
	{
	  constructor_max_index
	    = TYPE_MAX_قيمة (TYPE_DOMAIN (constructor_type));

	  /* Detect non-empty initializations of zero-length arrays.  */
	  إذا (constructor_max_index == NULL_شجرة
	      && TYPE_SIZE (constructor_type))
	    constructor_max_index = integer_minus_one_عقدة;

	  /* constructor_max_index needs to be an INTEGER_CST.  Attempts
	     to initialize VLAs with a nonempty initializer will cause a
	     proper error; avoid tree checking errors as well by setting a
	     safe value.  */
	  إذا (constructor_max_index
	      && شجرة_CODE (constructor_max_index) != INTEGER_CST)
	    constructor_max_index = integer_minus_one_عقدة;

	  constructor_index
	    = convert (bitsizetype,
		       TYPE_MIN_قيمة (TYPE_DOMAIN (constructor_type)));
	}
      وإلا
	{
	  constructor_index = bitsize_zero_عقدة;
	  constructor_max_index = NULL_شجرة;
	}

      constructor_unfilled_index = constructor_index;
    }
  وإلا إذا (gnu_vector_type_p (constructor_type))
    {
      /* Vectors are like simple fixed-size arrays.  */
      constructor_max_index =
	bitsize_int (TYPE_VECTOR_SUBPARTS (constructor_type) - 1);
      constructor_index = bitsize_zero_عقدة;
      constructor_unfilled_index = constructor_index;
    }
  وإلا
    {
      /* Handle the case of int x = {5}; */
      constructor_fields = constructor_type;
      constructor_unfilled_fields = constructor_type;
      constructor_braced_scalar = true;
    }
}

خارجي location_t last_init_list_comma;

/* Called when we see an open brace for a nested initializer.  Finish
   off any pending levels with implicit braces.  */
فراغ
finish_implicit_inits (location_t loc, بنية obstack *braced_init_obstack)
{
  طالما (constructor_مكدس->implicit)
    {
      إذا (RECORD_OR_UNION_TYPE_P (constructor_type)
	  && constructor_fields == NULL_شجرة)
	process_init_element (مدخل_location,
			      اسحب_init_level (loc, 1, braced_init_obstack,
					      last_init_list_comma),
			      true, braced_init_obstack);
      وإلا إذا (شجرة_CODE (constructor_type) == ARRAY_TYPE
	       && constructor_max_index
	       && شجرة_int_cst_lt (constructor_max_index,
				   constructor_index))
	process_init_element (مدخل_location,
			      اسحب_init_level (loc, 1, braced_init_obstack,
					      last_init_list_comma),
			      true, braced_init_obstack);
      وإلا
	اكسر;
    }
}

/* Push down into a subobject, for initialization.
   If this is for an explicit set of braces, IMPLICIT is 0.
   If it is because the next element belongs at a lower level,
   IMPLICIT is 1 (or 2 if the push is because of designator list).  */

فراغ
ادفع_init_level (location_t loc, صحيح implicit,
		 بنية obstack *braced_init_obstack)
{
  بنية constructor_مكدس *p;
  شجرة قيمة = NULL_شجرة;

  /* Unless this is an explicit brace, we need to preserve previous
     content if any.  */
  إذا (implicit)
    {
      إذا (RECORD_OR_UNION_TYPE_P (constructor_type) && constructor_fields)
	قيمة = find_init_member (constructor_fields, braced_init_obstack);
      وإلا إذا (شجرة_CODE (constructor_type) == ARRAY_TYPE)
	قيمة = find_init_member (constructor_index, braced_init_obstack);
    }

  p = XNEW (بنية constructor_مكدس);
  p->type = constructor_type;
  p->fields = constructor_fields;
  p->index = constructor_index;
  p->max_index = constructor_max_index;
  p->unfilled_index = constructor_unfilled_index;
  p->unfilled_fields = constructor_unfilled_fields;
  p->bit_index = constructor_bit_index;
  p->elements = constructor_elements;
  p->constant = constructor_constant;
  p->simple = constructor_simple;
  p->nonconst = constructor_nonconst;
  p->erroneous = constructor_erroneous;
  p->pending_elts = constructor_pending_elts;
  p->depth = constructor_depth;
  p->replacement_قيمة.قيمة = NULL_شجرة;
  p->replacement_قيمة.original_code = ERROR_MARK;
  p->replacement_قيمة.original_type = عدم;
  p->implicit = implicit;
  p->outer = 0;
  p->incremental = constructor_incremental;
  p->designated = constructor_designated;
  p->zero_padding_bits = constructor_zero_padding_bits;
  p->braced_scalar = constructor_braced_scalar;
  p->designator_depth = designator_depth;
  p->next = constructor_مكدس;
  p->range_مكدس = 0;
  constructor_مكدس = p;

  constructor_constant = 1;
  constructor_simple = 1;
  constructor_nonconst = 0;
  constructor_depth = SPELLING_DEPTH ();
  constructor_elements = عدم;
  constructor_incremental = 1;
  /* If the upper initializer is designated, then mark this as
     designated too to prevent bogus warnings.  */
  constructor_designated = p->designated;
  /* If the upper initializer has padding bits zeroed, that includes
     all nested initializers as well.  */
  constructor_zero_padding_bits = p->zero_padding_bits;
  constructor_braced_scalar = خطأ;
  constructor_pending_elts = 0;
  إذا (!implicit)
    {
      p->range_مكدس = constructor_range_مكدس;
      constructor_range_مكدس = 0;
      designator_depth = 0;
      designator_erroneous = 0;
    }

  /* Don't die if an entire brace-pair level is superfluous
     in the containing level.  */
  إذا (constructor_type == NULL_شجرة)
    ;
  وإلا إذا (RECORD_OR_UNION_TYPE_P (constructor_type))
    {
      /* Don't die if there are extra init elts at the end.  */
      إذا (constructor_fields == NULL_شجرة)
	constructor_type = NULL_شجرة;
      وإلا
	{
	  constructor_type = شجرة_TYPE (constructor_fields);
	  ادفع_member_name (constructor_fields);
	  constructor_depth++;
	}
    }
  وإلا إذا (شجرة_CODE (constructor_type) == ARRAY_TYPE)
    {
      constructor_type = شجرة_TYPE (constructor_type);
      ادفع_array_bounds (شجرة_to_uhwi (constructor_index));
      constructor_depth++;
    }

  إذا (constructor_type == NULL_شجرة)
    {
      error_init (loc, "extra brace group at end of initializer");
      constructor_fields = NULL_شجرة;
      constructor_unfilled_fields = NULL_شجرة;
      أرجع;
    }

  إذا (قيمة && شجرة_CODE (قيمة) == CONSTRUCTOR)
    {
      constructor_constant = شجرة_CONSTANT (قيمة);
      constructor_simple = شجرة_STATIC (قيمة);
      constructor_nonconst = CONSTRUCTOR_NON_CONST (قيمة);
      constructor_elements = CONSTRUCTOR_ELTS (قيمة);
      constructor_zero_padding_bits |= CONSTRUCTOR_ZERO_PADDING_BITS (قيمة);
      إذا (!vec_safe_is_empty (constructor_elements)
	  && (شجرة_CODE (constructor_type) == RECORD_TYPE
	      || شجرة_CODE (constructor_type) == ARRAY_TYPE))
	set_nonincremental_init (braced_init_obstack);
    }

  إذا (implicit == 1)
    {
      found_missing_braces = 1;
      إذا (initializer_مكدس->missing_brace_richloc)
	initializer_مكدس->missing_brace_richloc->add_fixit_أدرج_before
	  (loc, "{");
    }

  إذا (RECORD_OR_UNION_TYPE_P (constructor_type))
    {
      constructor_fields = TYPE_FIELDS (constructor_type);
      /* Skip any nameless bit fields at the beginning.  */
      طالما (constructor_fields != NULL_شجرة
	     && DECL_UNNAMED_BIT_FIELD (constructor_fields))
	constructor_fields = DECL_CHAIN (constructor_fields);

      constructor_unfilled_fields = constructor_fields;
      constructor_bit_index = bitsize_zero_عقدة;
    }
  وإلا إذا (gnu_vector_type_p (constructor_type))
    {
      /* Vectors are like simple fixed-size arrays.  */
      constructor_max_index =
	bitsize_int (TYPE_VECTOR_SUBPARTS (constructor_type) - 1);
      constructor_index = bitsize_int (0);
      constructor_unfilled_index = constructor_index;
    }
  وإلا إذا (شجرة_CODE (constructor_type) == ARRAY_TYPE)
    {
      إذا (TYPE_DOMAIN (constructor_type))
	{
	  constructor_max_index
	    = TYPE_MAX_قيمة (TYPE_DOMAIN (constructor_type));

	  /* Detect non-empty initializations of zero-length arrays.  */
	  إذا (constructor_max_index == NULL_شجرة
	      && TYPE_SIZE (constructor_type))
	    constructor_max_index = integer_minus_one_عقدة;

	  /* constructor_max_index needs to be an INTEGER_CST.  Attempts
	     to initialize VLAs will cause a proper error; avoid tree
	     checking errors as well by setting a safe value.  */
	  إذا (constructor_max_index
	      && شجرة_CODE (constructor_max_index) != INTEGER_CST)
	    constructor_max_index = integer_minus_one_عقدة;

	  constructor_index
	    = convert (bitsizetype,
		       TYPE_MIN_قيمة (TYPE_DOMAIN (constructor_type)));
	}
      وإلا
	constructor_index = bitsize_zero_عقدة;

      constructor_unfilled_index = constructor_index;
      إذا (قيمة && شجرة_CODE (قيمة) == STRING_CST)
	{
	  /* We need to split the char/wchar array into individual
	     characters, so that we don't have to special case it
	     everywhere.  */
	  set_nonincremental_init_from_string (قيمة, braced_init_obstack);
	}
    }
  وإلا
    {
      إذا (constructor_type != error_mark_عقدة)
	{
	  إذا (p->braced_scalar)
	    permerror_init (مدخل_location, 0,
			    "braces around scalar initializer");
	  وإلا
	    warning_init (مدخل_location, 0,
			  "braces around scalar initializer");
	  constructor_braced_scalar = true;
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

بنية c_تعبير
اسحب_init_level (location_t loc, صحيح implicit,
		بنية obstack *braced_init_obstack,
		location_t أدرج_before)
{
  بنية constructor_مكدس *p;
  بنية c_تعبير ret;
  ret.قيمة = NULL_شجرة;
  ret.original_code = ERROR_MARK;
  ret.original_type = عدم;
  ret.m_decimal = 0;

  إذا (implicit == 0)
    {
      /* When we come to an explicit close brace,
	 pop any inner levels that didn't have explicit braces.  */
      طالما (constructor_مكدس->implicit)
	process_init_element (مدخل_location,
			      اسحب_init_level (loc, 1, braced_init_obstack,
					      أدرج_before),
			      true, braced_init_obstack);
      gcc_assert (!constructor_range_مكدس);
    }
  وإلا
    إذا (initializer_مكدس->missing_brace_richloc)
      initializer_مكدس->missing_brace_richloc->add_fixit_أدرج_before
	(أدرج_before, "}");

  /* Now output all pending elements.  */
  constructor_incremental = 1;
  output_pending_init_elements (1, braced_init_obstack);

  p = constructor_مكدس;

  /* Error for initializing a flexible array member.  */
  إذا (constructor_type && constructor_fields
      && flexible_array_member_type_p (constructor_type))
    {
      /* Silently discard empty initializations.  The parser will
	 already have pedwarned for empty brackets for C17 and earlier.  */
      إذا (integer_zerop (constructor_unfilled_index))
	constructor_type = NULL_شجرة;
      إذا (constructor_type || flag_isoc23)
	{
	  gcc_assert (!constructor_type || !TYPE_SIZE (constructor_type));

	  إذا (constructor_depth <= 2)
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
	      && DECL_CHAIN (constructor_fields) != NULL_شجرة
	      && (!p->type || شجرة_CODE (p->type) != UNION_TYPE))
	    constructor_type = NULL_شجرة;
	}
    }

  بدل (vec_safe_length (constructor_elements))
    {
    حالة 0:
      /* Initialization with { } counts as zeroinit.  */
      constructor_zeroinit = 1;
      اكسر;
    حالة 1:
      /* This might be zeroinit as well.  */
      إذا (integer_zerop ((*constructor_elements)[0].قيمة))
	constructor_zeroinit = 1;
      اكسر;
    افتراضي:
      /* If the constructor has more than one element, it can't be { 0 }.  */
      constructor_zeroinit = 0;
      اكسر;
    }

  /* Warn when some structs are initialized with direct aggregation.  */
  إذا (!implicit && found_missing_braces && warn_missing_braces
      && !constructor_zeroinit)
    {
      gcc_assert (initializer_مكدس->missing_brace_richloc);
      warning_at (initializer_مكدس->missing_brace_richloc,
		  OPT_Wmissing_braces,
		  "missing braces around initializer");
    }

  /* Warn when some struct elements are implicitly initialized to zero.  */
  إذا (warn_missing_field_initializers
      && constructor_type
      && شجرة_CODE (constructor_type) == RECORD_TYPE
      && constructor_unfilled_fields)
    {
	/* Do not warn for flexible array members or zero-length arrays.  */
	طالما (constructor_unfilled_fields
	       && (!DECL_SIZE (constructor_unfilled_fields)
		   || integer_zerop (DECL_SIZE (constructor_unfilled_fields))))
	  constructor_unfilled_fields = DECL_CHAIN (constructor_unfilled_fields);

	إذا (constructor_unfilled_fields
	    /* Do not warn if this level of the initializer uses member
	       designators; it is likely to be deliberate.  */
	    && !constructor_designated
	    /* Do not warn about initializing with { 0 } or with { }.  */
	    && !constructor_zeroinit)
	  {
	    إذا (warning_at (مدخل_location, OPT_Wmissing_field_initializers,
			    "missing initializer for field %qD of %qT",
			    constructor_unfilled_fields,
			    constructor_type))
	      inform (DECL_SOURCE_LOCATION (constructor_unfilled_fields),
		      "%qD declared here", constructor_unfilled_fields);
	  }
    }

  /* Pad out the end of the structure.  */
  إذا (p->replacement_قيمة.قيمة)
    /* If this closes a superfluous brace pair,
       just pass out the element between them.  */
    ret = p->replacement_قيمة;
  وإلا إذا (constructor_type == NULL_شجرة)
    ;
  وإلا إذا (!RECORD_OR_UNION_TYPE_P (constructor_type)
	   && شجرة_CODE (constructor_type) != ARRAY_TYPE
	   && !gnu_vector_type_p (constructor_type))
    {
      /* A nonincremental scalar initializer--just return
	 the element, after verifying there is just one.
         Empty scalar initializers are supported in C23.  */
      إذا (vec_safe_is_empty (constructor_elements))
	{
	  إذا (constructor_erroneous || constructor_type == error_mark_عقدة)
	    ret.قيمة = error_mark_عقدة;
	  وإلا إذا (شجرة_CODE (constructor_type) == FUNCTION_TYPE)
	    {
	      error_init (loc, "invalid initializer");
	      ret.قيمة = error_mark_عقدة;
	    }
	  وإلا إذا (شجرة_CODE (constructor_type) == POINTER_TYPE)
	    /* Ensure this is a null pointer constant in the case of a
	       'constexpr' object initialized with {}.  */
	    ret.قيمة = build_zero_cst (ptr_type_عقدة);
	  وإلا
	    ret.قيمة = build_zero_cst (constructor_type);
	}
      وإلا إذا (vec_safe_length (constructor_elements) != 1)
	{
	  error_init (loc, "extra elements in scalar initializer");
	  ret.قيمة = (*constructor_elements)[0].قيمة;
	}
      وإلا
	ret.قيمة = (*constructor_elements)[0].قيمة;
    }
  وإلا
    {
      إذا (constructor_erroneous)
	ret.قيمة = error_mark_عقدة;
      وإلا
	{
	  ret.قيمة = build_constructor (constructor_type,
					 constructor_elements);
	  إذا (constructor_constant)
	    شجرة_CONSTANT (ret.قيمة) = 1;
	  إذا (constructor_constant && constructor_simple)
	    شجرة_STATIC (ret.قيمة) = 1;
	  إذا (constructor_nonconst)
	    CONSTRUCTOR_NON_CONST (ret.قيمة) = 1;
	  إذا (constructor_zero_padding_bits)
	    CONSTRUCTOR_ZERO_PADDING_BITS (ret.قيمة) = 1;
	}
    }

  إذا (ret.قيمة && شجرة_CODE (ret.قيمة) != CONSTRUCTOR)
    {
      إذا (constructor_nonconst)
	ret.original_code = C_MAYBE_CONST_تعبير;
      وإلا إذا (ret.original_code == C_MAYBE_CONST_تعبير)
	ret.original_code = ERROR_MARK;
    }

  constructor_type = p->type;
  constructor_fields = p->fields;
  constructor_index = p->index;
  constructor_max_index = p->max_index;
  constructor_unfilled_index = p->unfilled_index;
  constructor_unfilled_fields = p->unfilled_fields;
  constructor_bit_index = p->bit_index;
  constructor_elements = p->elements;
  constructor_constant = p->constant;
  constructor_simple = p->simple;
  constructor_nonconst = p->nonconst;
  constructor_erroneous = p->erroneous;
  constructor_incremental = p->incremental;
  constructor_designated = p->designated;
  constructor_zero_padding_bits = p->zero_padding_bits;
  constructor_braced_scalar = p->braced_scalar;
  designator_depth = p->designator_depth;
  constructor_pending_elts = p->pending_elts;
  constructor_depth = p->depth;
  إذا (!p->implicit)
    constructor_range_مكدس = p->range_مكدس;
  RESTORE_SPELLING_DEPTH (constructor_depth);

  constructor_مكدس = p->next;
  XDELETE (p);

  إذا (ret.قيمة == NULL_شجرة && constructor_مكدس == 0)
    ret.قيمة = error_mark_عقدة;
  أرجع ret;
}

/* Common handling for both array range and field name designators.
   ARRAY argument is nonzero for array ranges.  Returns false for success.  */

ساكن منطقي
set_designator (location_t loc, منطقي array,
		بنية obstack *braced_init_obstack)
{
  شجرة subtype;
  تعداد شجرة_code subcode;

  /* Don't die if an entire brace-pair level is superfluous
     in the containing level, or for an erroneous type.  */
  إذا (constructor_type == NULL_شجرة || constructor_type == error_mark_عقدة)
    أرجع true;

  /* If there were errors in this designator list already, bail out
     silently.  */
  إذا (designator_erroneous)
    أرجع true;

  /* Likewise for an initializer for a variable-size type.  Those are
     diagnosed in the parser, except for empty initializer braces.  */
  إذا (COMPLETE_TYPE_P (constructor_type)
      && شجرة_CODE (TYPE_SIZE (constructor_type)) != INTEGER_CST)
    أرجع true;

  إذا (!designator_depth)
    {
      gcc_assert (!constructor_range_مكدس);

      /* Designator list starts at the level of closest explicit
	 braces.  */
      طالما (constructor_مكدس->implicit)
	process_init_element (مدخل_location,
			      اسحب_init_level (loc, 1, braced_init_obstack,
					      last_init_list_comma),
			      true, braced_init_obstack);
      constructor_designated = 1;
      أرجع خطأ;
    }

  بدل (شجرة_CODE (constructor_type))
    {
    حالة  RECORD_TYPE:
    حالة  UNION_TYPE:
      subtype = شجرة_TYPE (constructor_fields);
      إذا (subtype != error_mark_عقدة)
	subtype = TYPE_MAIN_VARIANT (subtype);
      اكسر;
    حالة ARRAY_TYPE:
      subtype = TYPE_MAIN_VARIANT (شجرة_TYPE (constructor_type));
      اكسر;
    افتراضي:
      gcc_unreachable ();
    }

  subcode = شجرة_CODE (subtype);
  إذا (array && subcode != ARRAY_TYPE)
    {
      error_init (loc, "array index in non-array initializer");
      أرجع true;
    }
  وإلا إذا (!array && subcode != RECORD_TYPE && subcode != UNION_TYPE)
    {
      error_init (loc, "field name not in record or union initializer");
      أرجع true;
    }

  constructor_designated = 1;
  finish_implicit_inits (loc, braced_init_obstack);
  ادفع_init_level (loc, 2, braced_init_obstack);
  أرجع خطأ;
}

/* If there are range designators in designator list, push a new designator
   to constructor_range_stack.  RANGE_END is end of such stack range or
   NULL_TREE if there is no range designator at this level.  */

ساكن فراغ
ادفع_range_مكدس (شجرة range_end, بنية obstack * braced_init_obstack)
{
  بنية constructor_range_مكدس *p;

  p = (بنية constructor_range_مكدس *)
    obstack_alloc (braced_init_obstack,
		   حجم (بنية constructor_range_مكدس));
  p->prev = constructor_range_مكدس;
  p->next = 0;
  p->fields = constructor_fields;
  p->range_start = constructor_index;
  p->index = constructor_index;
  p->مكدس = constructor_مكدس;
  p->range_end = range_end;
  إذا (constructor_range_مكدس)
    constructor_range_مكدس->next = p;
  constructor_range_مكدس = p;
}

/* Within an array initializer, specify the next index to be initialized.
   FIRST is that index.  If LAST is nonzero, then initialize a range
   of indices, running from FIRST through LAST.  */

فراغ
set_init_index (location_t loc, شجرة first, شجرة last,
		بنية obstack *braced_init_obstack)
{
  إذا (set_designator (loc, true, braced_init_obstack))
    أرجع;

  designator_erroneous = 1;

  إذا (!INTEGRAL_TYPE_P (شجرة_TYPE (first))
      || (last && !INTEGRAL_TYPE_P (شجرة_TYPE (last))))
    {
      error_init (loc, "array index in initializer not of integer type");
      أرجع;
    }

  إذا (شجرة_CODE (first) != INTEGER_CST)
    {
      first = c_fully_fold (first, خطأ, عدم);
      إذا (شجرة_CODE (first) == INTEGER_CST)
	pedwarn_init (loc, OPT_Wpedantic,
		      "array index in initializer is not "
		      "an integer constant expression");
    }

  إذا (last && شجرة_CODE (last) != INTEGER_CST)
    {
      last = c_fully_fold (last, خطأ, عدم);
      إذا (شجرة_CODE (last) == INTEGER_CST)
	pedwarn_init (loc, OPT_Wpedantic,
		      "array index in initializer is not "
		      "an integer constant expression");
    }

  إذا (شجرة_CODE (first) != INTEGER_CST)
    error_init (loc, "nonconstant array index in initializer");
  وإلا إذا (last != NULL_شجرة && شجرة_CODE (last) != INTEGER_CST)
    error_init (loc, "nonconstant array index in initializer");
  وإلا إذا (شجرة_CODE (constructor_type) != ARRAY_TYPE)
    error_init (loc, "array index in non-array initializer");
  وإلا إذا (شجرة_int_cst_sgn (first) == -1)
    error_init (loc, "array index in initializer exceeds array bounds");
  وإلا إذا (constructor_max_index
	   && شجرة_int_cst_lt (constructor_max_index, first))
    error_init (loc, "array index in initializer exceeds array bounds");
  وإلا
    {
      constant_expression_warning (first);
      إذا (last)
	constant_expression_warning (last);
      constructor_index = convert (bitsizetype, first);
      إذا (شجرة_int_cst_lt (constructor_index, first))
	{
	  constructor_index = copy_عقدة (constructor_index);
	  شجرة_OVERFLOW (constructor_index) = 1;
	}

      إذا (last)
	{
	  إذا (شجرة_int_cst_equal (first, last))
	    last = NULL_شجرة;
	  وإلا إذا (شجرة_int_cst_lt (last, first))
	    {
	      error_init (loc, "empty index range in initializer");
	      last = NULL_شجرة;
	    }
	  وإلا
	    {
	      last = convert (bitsizetype, last);
	      إذا (constructor_max_index != NULL_شجرة
		  && شجرة_int_cst_lt (constructor_max_index, last))
		{
		  error_init (loc, "array index range in initializer exceeds "
			      "array bounds");
		  last = NULL_شجرة;
		}
	    }
	}

      designator_depth++;
      designator_erroneous = 0;
      إذا (constructor_range_مكدس || last)
	ادفع_range_مكدس (last, braced_init_obstack);
    }
}

/* Within a struct initializer, specify the next field to be initialized.  */

فراغ
set_init_label (location_t loc, شجرة fieldname, location_t fieldname_loc,
		بنية obstack *braced_init_obstack)
{
  شجرة field;

  إذا (set_designator (loc, خطأ, braced_init_obstack))
    أرجع;

  designator_erroneous = 1;

  إذا (!RECORD_OR_UNION_TYPE_P (constructor_type))
    {
      error_init (loc, "field name not in record or union initializer");
      أرجع;
    }

  field = lookup_field (constructor_type, fieldname);

  إذا (field == NULL_شجرة)
    {
      شجرة guessed_id = lookup_field_fuzzy (constructor_type, fieldname);
      إذا (guessed_id)
	{
	  gcc_rich_location rich_loc (fieldname_loc);
	  rich_loc.add_fixit_misspelled_id (fieldname_loc, guessed_id);
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
	constructor_fields = شجرة_قيمة (field);
	designator_depth++;
	designator_erroneous = 0;
	إذا (constructor_range_مكدس)
	  ادفع_range_مكدس (NULL_شجرة, braced_init_obstack);
	field = شجرة_CHAIN (field);
	إذا (field)
	  {
	    إذا (set_designator (loc, خطأ, braced_init_obstack))
	      أرجع;
	  }
      }
    طالما (field != NULL_شجرة);
}

/* Helper function for add_pending_init.  Find inorder successor of P
   in AVL tree.  */
ساكن بنية init_عقدة *
init_عقدة_successor (بنية init_عقدة *p)
{
  بنية init_عقدة *r;
  إذا (p->يمين)
    {
      r = p->يمين;
      طالما (r->يسار)
	r = r->يسار;
      أرجع r;
    }
  r = p->parent;
  طالما (r && p == r->يمين)
    {
      p = r;
      r = r->parent;
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
add_pending_init (location_t loc, شجرة purpose, شجرة قيمة, شجرة origtype,
		  منطقي implicit, بنية obstack *braced_init_obstack)
{
  بنية init_عقدة *p, **q, *r;

  q = &constructor_pending_elts;
  p = 0;

  إذا (شجرة_CODE (constructor_type) == ARRAY_TYPE)
    {
      طالما (*q != 0)
	{
	  p = *q;
	  إذا (شجرة_int_cst_lt (purpose, p->purpose))
	    q = &p->يسار;
	  وإلا إذا (شجرة_int_cst_lt (p->purpose, purpose))
	    {
	      إذا (شجرة_CODE (p->قيمة) != RAW_DATA_CST
		  || (p->يمين
		      && شجرة_int_cst_le (p->يمين->purpose, purpose)))
		q = &p->يمين;
	      وإلا
		{
		  widest_int pp = wi::to_widest (p->purpose);
		  widest_int pw = wi::to_widest (purpose);
		  إذا (pp + RAW_DATA_LENGTH (p->قيمة) <= pw)
		    q = &p->يمين;
		  وإلا
		    {
		      /* Override which should split the old RAW_DATA_CST
			 into 2 or 3 pieces.  */
		      إذا (!implicit && warn_override_init)
			warning_init (loc, OPT_Woverride_init,
				      "initialized field overwritten");
		      unsigned HOST_WIDE_INT start = (pw - pp).to_uhwi ();
		      unsigned HOST_WIDE_INT len = 1;
		      إذا (شجرة_CODE (قيمة) == RAW_DATA_CST)
			len = RAW_DATA_LENGTH (قيمة);
		      unsigned HOST_WIDE_INT end = 0;
		      unsigned plen = RAW_DATA_LENGTH (p->قيمة);
		      gcc_checking_assert (start < plen && start);
		      إذا (plen - start > len)
			end = plen - start - len;
		      شجرة v = p->قيمة;
		      شجرة origtype = p->origtype;
		      إذا (start == 1)
			p->قيمة = build_int_cst (شجرة_TYPE (v),
						  RAW_DATA_UCHAR_ELT (v, 0));
		      وإلا
			{
			  p->قيمة = v;
			  إذا (end > 1)
			    v = copy_عقدة (v);
			  RAW_DATA_LENGTH (p->قيمة) = start;
			}
		      إذا (end)
			{
			  شجرة epurpose
			    = size_binop (PLUS_تعبير, purpose,
					  bitsize_int (len));
			  إذا (end > 1)
			    {
			      RAW_DATA_LENGTH (v) -= plen - end;
			      RAW_DATA_POINTER (v) += plen - end;
			    }
			  وإلا
			    v = build_int_cst (شجرة_TYPE (v),
					       RAW_DATA_UCHAR_ELT (v, plen
								      - end));
			  add_pending_init (loc, epurpose, v, origtype,
					    implicit, braced_init_obstack);
			}
		      q = &constructor_pending_elts;
		      استمر;
		    }
		}
	    }
	  وإلا
	    {
	      إذا (شجرة_CODE (p->قيمة) == RAW_DATA_CST
		  && (RAW_DATA_LENGTH (p->قيمة)
		      > (شجرة_CODE (قيمة) == RAW_DATA_CST
			 ? RAW_DATA_LENGTH (قيمة) : 1)))
		{
		  /* Override which should split the old RAW_DATA_CST
		     into 2 pieces.  */
		  إذا (!implicit && warn_override_init)
		    warning_init (loc, OPT_Woverride_init,
				  "initialized field overwritten");
		  unsigned HOST_WIDE_INT len = 1;
		  إذا (شجرة_CODE (قيمة) == RAW_DATA_CST)
		    len = RAW_DATA_LENGTH (قيمة);
		  إذا ((unsigned) RAW_DATA_LENGTH (p->قيمة) > len + 1)
		    {
		      RAW_DATA_LENGTH (p->قيمة) -= len;
		      RAW_DATA_POINTER (p->قيمة) += len;
		    }
		  وإلا
		    {
		      unsigned صحيح l = RAW_DATA_LENGTH (p->قيمة) - 1;
		      p->قيمة
			= build_int_cst (شجرة_TYPE (p->قيمة),
					 RAW_DATA_UCHAR_ELT (p->قيمة, l));
		    }
		  p->purpose = size_binop (PLUS_تعبير, p->purpose,
					   bitsize_int (len));
		  استمر;
		}
	      إذا (شجرة_CODE (قيمة) == RAW_DATA_CST)
		{
		handle_raw_data:
		  /* RAW_DATA_CST value might overlap various further
		     prior initval entries.  Find out how many.  */
		  unsigned cnt = 0;
		  widest_int w
		    = wi::to_widest (purpose) + RAW_DATA_LENGTH (قيمة);
		  بنية init_عقدة *r = p, *last = عدم;
		  منطقي override_init = warn_override_init;
		  طالما ((r = init_عقدة_successor (r))
			 && wi::to_widest (r->purpose) < w)
		    {
		      ++cnt;
		      إذا (شجرة_SIDE_EFFECTS (r->قيمة))
			warning_init (loc, OPT_Woverride_init_side_effects,
				      "initialized field with side-effects "
				      "overwritten");
		      وإلا إذا (override_init)
			{
			  warning_init (loc, OPT_Woverride_init,
					"initialized field overwritten");
			  override_init = خطأ;
			}
		      last = r;
		    }
		  إذا (cnt)
		    {
		      إذا (شجرة_CODE (last->قيمة) == RAW_DATA_CST
			  && (wi::to_widest (last->purpose)
			      + RAW_DATA_LENGTH (last->قيمة) > w))
			{
			  /* The last overlapping prior initval overlaps
			     only partially.  Shrink it and decrease cnt.  */
			  unsigned صحيح l = (wi::to_widest (last->purpose)
					    + RAW_DATA_LENGTH (last->قيمة)
					    - w).to_uhwi ();
			  --cnt;
			  RAW_DATA_LENGTH (last->قيمة) -= l;
			  RAW_DATA_POINTER (last->قيمة) += l;
			  إذا (RAW_DATA_LENGTH (last->قيمة) == 1)
			    last->قيمة
			      = build_int_cst (شجرة_TYPE (last->قيمة),
					       RAW_DATA_UCHAR_ELT (last->قيمة,
								   0));
			  last->purpose
			    = size_binop (PLUS_تعبير, last->purpose,
					  bitsize_int (l));
			}
		      /* Instead of deleting cnt nodes from the AVL tree
			 and rebalancing, peel of last cnt bytes from the
			 RAW_DATA_CST.  Overriding thousands of previously
			 initialized array elements with #embed needs to work,
			 but doesn't need to be super efficient.  */
		      gcc_checking_assert ((unsigned) RAW_DATA_LENGTH (قيمة)
					   > cnt);
		      RAW_DATA_LENGTH (قيمة) -= cnt;
		      ثابت unsigned حرف *s
			= &RAW_DATA_UCHAR_ELT (قيمة, RAW_DATA_LENGTH (قيمة));
		      unsigned صحيح o = RAW_DATA_LENGTH (قيمة);
		      لكل (r = p; cnt--; ++o, ++s)
			{
			  r = init_عقدة_successor (r);
			  r->purpose = size_binop (PLUS_تعبير, purpose,
						   bitsize_int (o));
			  r->قيمة = build_int_cst (شجرة_TYPE (قيمة), *s);
			  r->origtype = origtype;
			}
		      إذا (RAW_DATA_LENGTH (قيمة) == 1)
			قيمة = build_int_cst (شجرة_TYPE (قيمة),
					       RAW_DATA_UCHAR_ELT (قيمة, 0));
		    }
		}
	      إذا (!implicit)
		{
		  إذا (شجرة_SIDE_EFFECTS (p->قيمة))
		    warning_init (loc, OPT_Woverride_init_side_effects,
				  "initialized field with side-effects "
				  "overwritten");
		  وإلا إذا (warn_override_init)
		    warning_init (loc, OPT_Woverride_init,
				  "initialized field overwritten");
		}
	      p->قيمة = قيمة;
	      p->origtype = origtype;
	      أرجع;
	    }
	}
      إذا (شجرة_CODE (قيمة) == RAW_DATA_CST && p)
	{
	  بنية init_عقدة *r;
	  إذا (q == &p->يسار)
	    r = p;
	  وإلا
	    r = init_عقدة_successor (p);
	  إذا (r && wi::to_widest (r->purpose) < (wi::to_widest (purpose)
						 + RAW_DATA_LENGTH (قيمة)))
	    {
	      /* Overlap with at least one prior initval in the range but
		 not at the start.  */
	      p = r;
	      p->purpose = purpose;
	      اذهب handle_raw_data;
	    }
	}
    }
  وإلا
    {
      شجرة bitpos;

      bitpos = bit_position (purpose);
      طالما (*q != عدم)
	{
	  p = *q;
	  إذا (شجرة_int_cst_lt (bitpos, bit_position (p->purpose)))
	    q = &p->يسار;
	  وإلا إذا (p->purpose != purpose)
	    q = &p->يمين;
	  وإلا
	    {
	      إذا (!implicit)
		{
		  إذا (شجرة_SIDE_EFFECTS (p->قيمة))
		    warning_init (loc, OPT_Woverride_init_side_effects,
				  "initialized field with side-effects "
				  "overwritten");
		  وإلا إذا (warn_override_init)
		    warning_init (loc, OPT_Woverride_init,
				  "initialized field overwritten");
		}
	      p->قيمة = قيمة;
	      p->origtype = origtype;
	      أرجع;
	    }
	}
    }

  r = (بنية init_عقدة *) obstack_alloc (braced_init_obstack,
					  حجم (بنية init_عقدة));
  r->purpose = purpose;
  r->قيمة = قيمة;
  r->origtype = origtype;

  *q = r;
  r->parent = p;
  r->يسار = 0;
  r->يمين = 0;
  r->balance = 0;

  طالما (p)
    {
      بنية init_عقدة *s;

      إذا (r == p->يسار)
	{
	  إذا (p->balance == 0)
	    p->balance = -1;
	  وإلا إذا (p->balance < 0)
	    {
	      إذا (r->balance < 0)
		{
		  /* L rotation.  */
		  p->يسار = r->يمين;
		  إذا (p->يسار)
		    p->يسار->parent = p;
		  r->يمين = p;

		  p->balance = 0;
		  r->balance = 0;

		  s = p->parent;
		  p->parent = r;
		  r->parent = s;
		  إذا (s)
		    {
		      إذا (s->يسار == p)
			s->يسار = r;
		      وإلا
			s->يمين = r;
		    }
		  وإلا
		    constructor_pending_elts = r;
		}
	      وإلا
		{
		  /* LR rotation.  */
		  بنية init_عقدة *t = r->يمين;

		  r->يمين = t->يسار;
		  إذا (r->يمين)
		    r->يمين->parent = r;
		  t->يسار = r;

		  p->يسار = t->يمين;
		  إذا (p->يسار)
		    p->يسار->parent = p;
		  t->يمين = p;

		  p->balance = t->balance < 0;
		  r->balance = -(t->balance > 0);
		  t->balance = 0;

		  s = p->parent;
		  p->parent = t;
		  r->parent = t;
		  t->parent = s;
		  إذا (s)
		    {
		      إذا (s->يسار == p)
			s->يسار = t;
		      وإلا
			s->يمين = t;
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
		  p->يمين = r->يسار;
		  إذا (p->يمين)
		    p->يمين->parent = p;
		  r->يسار = p;

		  p->balance = 0;
		  r->balance = 0;

		  s = p->parent;
		  p->parent = r;
		  r->parent = s;
		  إذا (s)
		    {
		      إذا (s->يسار == p)
			s->يسار = r;
		      وإلا
			s->يمين = r;
		    }
		  وإلا
		    constructor_pending_elts = r;
		}
	      وإلا /* r->balance == -1 */
		{
		  /* RL rotation */
		  بنية init_عقدة *t = r->يسار;

		  r->يسار = t->يمين;
		  إذا (r->يسار)
		    r->يسار->parent = r;
		  t->يمين = r;

		  p->يمين = t->يسار;
		  إذا (p->يمين)
		    p->يمين->parent = p;
		  t->يسار = p;

		  r->balance = (t->balance < 0);
		  p->balance = -(t->balance > 0);
		  t->balance = 0;

		  s = p->parent;
		  p->parent = t;
		  r->parent = t;
		  t->parent = s;
		  إذا (s)
		    {
		      إذا (s->يسار == p)
			s->يسار = t;
		      وإلا
			s->يمين = t;
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
      p = p->parent;
    }
}

/* Build AVL tree from a sorted chain.  */

ساكن فراغ
set_nonincremental_init (بنية obstack * braced_init_obstack)
{
  unsigned HOST_WIDE_INT ix;
  شجرة index, قيمة;

  إذا (شجرة_CODE (constructor_type) != RECORD_TYPE
      && شجرة_CODE (constructor_type) != ARRAY_TYPE)
    أرجع;

  FOR_EACH_CONSTRUCTOR_ELT (constructor_elements, ix, index, قيمة)
    add_pending_init (مدخل_location, index, قيمة, NULL_شجرة, true,
		      braced_init_obstack);
  constructor_elements = عدم;
  إذا (شجرة_CODE (constructor_type) == RECORD_TYPE)
    {
      constructor_unfilled_fields = TYPE_FIELDS (constructor_type);
      /* Skip any nameless bit fields at the beginning.  */
      طالما (constructor_unfilled_fields != NULL_شجرة
	     && DECL_UNNAMED_BIT_FIELD (constructor_unfilled_fields))
	constructor_unfilled_fields = شجرة_CHAIN (constructor_unfilled_fields);

    }
  وإلا إذا (شجرة_CODE (constructor_type) == ARRAY_TYPE)
    {
      إذا (TYPE_DOMAIN (constructor_type))
	constructor_unfilled_index
	  = convert (bitsizetype,
		     TYPE_MIN_قيمة (TYPE_DOMAIN (constructor_type)));
      وإلا
	constructor_unfilled_index = bitsize_zero_عقدة;
    }
  constructor_incremental = 0;
}

/* Build AVL tree from a string constant.  */

ساكن فراغ
set_nonincremental_init_from_string (شجرة str,
				     بنية obstack * braced_init_obstack)
{
  شجرة قيمة, purpose, type;
  HOST_WIDE_INT val[2];
  ثابت حرف *p, *end;
  صحيح byte, wchar_bytes, charwidth, bitpos;

  gcc_assert (شجرة_CODE (constructor_type) == ARRAY_TYPE);

  wchar_bytes = TYPE_PRECISION (شجرة_TYPE (شجرة_TYPE (str))) / BITS_PER_UNIT;
  charwidth = TYPE_PRECISION (char_type_عقدة);
  gcc_assert ((size_t) wchar_bytes * charwidth
	      <= ARRAY_SIZE (val) * HOST_BITS_PER_WIDE_INT);
  type = شجرة_TYPE (constructor_type);
  p = شجرة_STRING_POINTER (str);
  end = p + شجرة_STRING_LENGTH (str);

  لكل (purpose = bitsize_zero_عقدة;
       p < end
       && !(constructor_max_index
	    && شجرة_int_cst_lt (constructor_max_index, purpose));
       purpose = size_binop (PLUS_تعبير, purpose, bitsize_one_عقدة))
    {
      إذا (wchar_bytes == 1)
	{
	  val[0] = (unsigned حرف) *p++;
	  val[1] = 0;
	}
      وإلا
	{
	  val[1] = 0;
	  val[0] = 0;
	  لكل (byte = 0; byte < wchar_bytes; byte++)
	    {
	      إذا (BYTES_BIG_ENDIAN)
		bitpos = (wchar_bytes - byte - 1) * charwidth;
	      وإلا
		bitpos = byte * charwidth;
	      val[bitpos / HOST_BITS_PER_WIDE_INT]
		|= ((unsigned HOST_WIDE_INT) ((unsigned حرف) *p++))
		   << (bitpos % HOST_BITS_PER_WIDE_INT);
	    }
	}

      إذا (!TYPE_UNSIGNED (type))
	{
	  bitpos = ((wchar_bytes - 1) * charwidth) + HOST_BITS_PER_CHAR;
	  إذا (bitpos < HOST_BITS_PER_WIDE_INT)
	    {
	      إذا (val[0] & (HOST_WIDE_INT_1 << (bitpos - 1)))
		{
		  val[0] |= HOST_WIDE_INT_M1U << bitpos;
		  val[1] = -1;
		}
	    }
	  وإلا إذا (bitpos == HOST_BITS_PER_WIDE_INT)
	    {
	      إذا (val[0] < 0)
		val[1] = -1;
	    }
	  وإلا إذا (val[1] & (HOST_WIDE_INT_1
			     << (bitpos - 1 - HOST_BITS_PER_WIDE_INT)))
	    val[1] |= HOST_WIDE_INT_M1U << (bitpos - HOST_BITS_PER_WIDE_INT);
	}

      قيمة = wide_int_to_شجرة (type,
				wide_int::from_array (val, 2,
						      HOST_BITS_PER_WIDE_INT * 2));
      add_pending_init (مدخل_location, purpose, قيمة, NULL_شجرة, true,
                        braced_init_obstack);
    }

  constructor_incremental = 0;
}

/* Return value of FIELD in pending initializer or NULL_TREE if the field was
   not initialized yet.  */

ساكن شجرة
find_init_member (شجرة field, بنية obstack * braced_init_obstack)
{
  بنية init_عقدة *p;

  إذا (شجرة_CODE (constructor_type) == ARRAY_TYPE)
    {
      إذا (constructor_incremental
	  && شجرة_int_cst_lt (field, constructor_unfilled_index))
	set_nonincremental_init (braced_init_obstack);

      p = constructor_pending_elts;
      طالما (p)
	{
	  إذا (شجرة_int_cst_lt (field, p->purpose))
	    p = p->يسار;
	  وإلا إذا (شجرة_int_cst_lt (p->purpose, field))
	    p = p->يمين;
	  وإلا
	    أرجع p->قيمة;
	}
    }
  وإلا إذا (شجرة_CODE (constructor_type) == RECORD_TYPE)
    {
      شجرة bitpos = bit_position (field);

      إذا (constructor_incremental
	  && (!constructor_unfilled_fields
	      || شجرة_int_cst_lt (bitpos,
				  bit_position (constructor_unfilled_fields))))
	set_nonincremental_init (braced_init_obstack);

      p = constructor_pending_elts;
      طالما (p)
	{
	  إذا (field == p->purpose)
	    أرجع p->قيمة;
	  وإلا إذا (شجرة_int_cst_lt (bitpos, bit_position (p->purpose)))
	    p = p->يسار;
	  وإلا
	    p = p->يمين;
	}
    }
  وإلا إذا (شجرة_CODE (constructor_type) == UNION_TYPE)
    {
      إذا (!vec_safe_is_empty (constructor_elements)
	  && (constructor_elements->last ().index == field))
	أرجع constructor_elements->last ().قيمة;
    }
  أرجع NULL_شجرة;
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
output_init_element (location_t loc, شجرة قيمة, شجرة origtype,
		     منطقي strict_string, شجرة type, شجرة field, منطقي pending,
		     منطقي implicit, بنية obstack * braced_init_obstack)
{
  شجرة semantic_type = NULL_شجرة;
  منطقي maybe_const = true;
  منطقي npc, int_const_تعبير, arith_const_تعبير;

  إذا (type == error_mark_عقدة || قيمة == error_mark_عقدة)
    {
      constructor_erroneous = 1;
      أرجع;
    }
  إذا (شجرة_CODE (شجرة_TYPE (قيمة)) == ARRAY_TYPE
      && (شجرة_CODE (قيمة) == STRING_CST
	  || شجرة_CODE (قيمة) == COMPOUND_LITERAL_تعبير)
      && !(شجرة_CODE (قيمة) == STRING_CST
	   && شجرة_CODE (type) == ARRAY_TYPE
	   && INTEGRAL_TYPE_P (شجرة_TYPE (type)))
      && !comptypes (TYPE_MAIN_VARIANT (شجرة_TYPE (قيمة)),
		     TYPE_MAIN_VARIANT (type)))
    قيمة = array_to_pointer_conversion (مدخل_location, قيمة);

  إذا (شجرة_CODE (قيمة) == COMPOUND_LITERAL_تعبير
      && require_constant_قيمة && pending)
    {
      /* As an extension, allow initializing objects with static storage
	 duration with compound literals (which are then treated just as
	 the brace enclosed list they contain).  */
      إذا (flag_isoc99)
	pedwarn_init (loc, OPT_Wpedantic, "initializer element is not "
		      "constant");
      شجرة decl = COMPOUND_LITERAL_تعبير_DECL (قيمة);
      قيمة = DECL_INITIAL (decl);
    }

  npc = null_pointer_constant_p (قيمة);
  int_const_تعبير = (شجرة_CODE (قيمة) == INTEGER_CST
		    && !شجرة_OVERFLOW (قيمة)
		    && INTEGRAL_TYPE_P (شجرة_TYPE (قيمة)));
  /* Not fully determined before folding.  */
  arith_const_تعبير = true;
  إذا (شجرة_CODE (قيمة) == EXCESS_PRECISION_تعبير)
    {
      semantic_type = شجرة_TYPE (قيمة);
      قيمة = شجرة_OPERAND (قيمة, 0);
    }
  قيمة = c_fully_fold (قيمة, require_constant_قيمة, &maybe_const);
  /* TODO: this may not detect all cases of expressions folding to
     constants that are not arithmetic constant expressions.  */
  إذا (!maybe_const)
    arith_const_تعبير = خطأ;
  وإلا إذا (!INTEGRAL_TYPE_P (شجرة_TYPE (قيمة))
	   && شجرة_CODE (شجرة_TYPE (قيمة)) != REAL_TYPE
	   && شجرة_CODE (شجرة_TYPE (قيمة)) != COMPLEX_TYPE)
    arith_const_تعبير = خطأ;
  وإلا إذا (شجرة_CODE (قيمة) != INTEGER_CST
	   && شجرة_CODE (قيمة) != REAL_CST
	   && شجرة_CODE (قيمة) != COMPLEX_CST
	   && شجرة_CODE (قيمة) != RAW_DATA_CST)
    arith_const_تعبير = خطأ;
  وإلا إذا (شجرة_OVERFLOW (قيمة))
    arith_const_تعبير = خطأ;

  إذا (قيمة == error_mark_عقدة)
    constructor_erroneous = 1;
  وإلا إذا (!شجرة_CONSTANT (قيمة))
    constructor_constant = 0;
  وإلا إذا (!initializer_constant_valid_p (قيمة,
					  شجرة_TYPE (قيمة),
					  AGGREGATE_TYPE_P (constructor_type)
					  && TYPE_REVERSE_STORAGE_ORDER
					     (constructor_type))
	   || (RECORD_OR_UNION_TYPE_P (constructor_type)
	       && DECL_C_BIT_FIELD (field)
	       && شجرة_CODE (قيمة) != INTEGER_CST))
    constructor_simple = 0;
  إذا (!maybe_const)
    constructor_nonconst = 1;

  /* Digest the initializer and issue any errors about incompatible
     types before issuing errors about non-constant initializers.  */
  شجرة new_قيمة = قيمة;
  إذا (semantic_type)
    new_قيمة = build1 (EXCESS_PRECISION_تعبير, semantic_type, قيمة);
  /* In the case of braces around a scalar initializer, the result of
     this initializer processing goes through digest_init again at the
     outer level.  In the case of a constexpr initializer for a
     pointer, avoid converting a null pointer constant to something
     that is not a null pointer constant to avoid a spurious error
     from that second processing.  */
  إذا (!require_constexpr_قيمة
      || !npc
      || شجرة_CODE (constructor_type) != POINTER_TYPE)
    new_قيمة = digest_init (loc,
			     RECORD_OR_UNION_TYPE_P (constructor_type)
			     ? field : constructor_fields
			     ? constructor_fields : constructor_decl,
			     type, new_قيمة, origtype, npc,
			     int_const_تعبير, arith_const_تعبير, strict_string,
			     require_constant_قيمة, require_constexpr_قيمة);
  إذا (new_قيمة == error_mark_عقدة)
    {
      constructor_erroneous = 1;
      أرجع;
    }
  إذا (require_constant_قيمة || require_constant_elements)
    constant_expression_warning (new_قيمة);

  /* Proceed to check the constness of the original initializer.  */
  إذا (!initializer_constant_valid_p (قيمة, شجرة_TYPE (قيمة)))
    {
      إذا (require_constant_قيمة)
	{
	  error_init (loc, "initializer element is not constant");
	  قيمة = error_mark_عقدة;
	}
      وإلا إذا (require_constant_elements)
	pedwarn (loc, OPT_Wpedantic,
		 "initializer element is not computable at load time");
    }
  وإلا إذا (!maybe_const
	   && (require_constant_قيمة || require_constant_elements))
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
      && field != NULL_شجرة
      && شجرة_CODE (field) == FIELD_DECL
      && DECL_BIT_FIELD_TYPE (field) != NULL_شجرة
      && (TYPE_MAIN_VARIANT (DECL_BIT_FIELD_TYPE (field))
	  != TYPE_MAIN_VARIANT (type))
      && شجرة_CODE (DECL_BIT_FIELD_TYPE (field)) == ENUMERAL_TYPE)
    {
      شجرة checktype = origtype != NULL_شجرة ? origtype : شجرة_TYPE (قيمة);
      إذا (checktype != error_mark_عقدة
	  && (TYPE_MAIN_VARIANT (checktype)
	      != TYPE_MAIN_VARIANT (DECL_BIT_FIELD_TYPE (field))))
	warning_init (loc, OPT_Wc___compat,
		      "enum conversion in initialization is invalid in C++");
    }

  /* If this field is empty and does not have side effects (and is not at
     the end of structure), don't do anything other than checking the
     initializer.  */
  إذا (field
      && (شجرة_TYPE (field) == error_mark_عقدة
	  || (COMPLETE_TYPE_P (شجرة_TYPE (field))
	      && integer_zerop (TYPE_SIZE (شجرة_TYPE (field)))
	      && !شجرة_SIDE_EFFECTS (new_قيمة)
	      && (شجرة_CODE (constructor_type) == ARRAY_TYPE
		  || DECL_CHAIN (field)))))
    أرجع;

  /* Finally, set VALUE to the initializer value digested above.  */
  قيمة = new_قيمة;

  /* If this element doesn't come next in sequence,
     put it on constructor_pending_elts.  */
  إذا (شجرة_CODE (constructor_type) == ARRAY_TYPE
      && (!constructor_incremental
	  || !شجرة_int_cst_equal (field, constructor_unfilled_index)
	  || (شجرة_CODE (قيمة) == RAW_DATA_CST
	      && constructor_pending_elts
	      && pending)))
    {
      إذا (constructor_incremental
	  && (شجرة_int_cst_lt (field, constructor_unfilled_index)
	      || (شجرة_CODE (قيمة) == RAW_DATA_CST
		  && constructor_pending_elts
		  && pending)))
	set_nonincremental_init (braced_init_obstack);

      add_pending_init (loc, field, قيمة, origtype, implicit,
			braced_init_obstack);
      أرجع;
    }
  وإلا إذا (شجرة_CODE (constructor_type) == RECORD_TYPE
	   && (!constructor_incremental
	       || field != constructor_unfilled_fields))
    {
      /* We do this for records but not for unions.  In a union,
	 no matter which field is specified, it can be initialized
	 right away since it starts at the beginning of the union.  */
      إذا (constructor_incremental)
	{
	  إذا (!constructor_unfilled_fields)
	    set_nonincremental_init (braced_init_obstack);
	  وإلا
	    {
	      شجرة bitpos, unfillpos;

	      bitpos = bit_position (field);
	      unfillpos = bit_position (constructor_unfilled_fields);

	      إذا (شجرة_int_cst_lt (bitpos, unfillpos))
		set_nonincremental_init (braced_init_obstack);
	    }
	}

      add_pending_init (loc, field, قيمة, origtype, implicit,
			braced_init_obstack);
      أرجع;
    }
  وإلا إذا (شجرة_CODE (constructor_type) == UNION_TYPE
	   && !vec_safe_is_empty (constructor_elements))
    {
      إذا (!implicit)
	{
	  إذا (شجرة_SIDE_EFFECTS (constructor_elements->last ().قيمة))
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

  constructor_elt celt = {field, قيمة};
  vec_safe_ادفع (constructor_elements, celt);

  /* Advance the variable that indicates sequential elements output.  */
  إذا (شجرة_CODE (constructor_type) == ARRAY_TYPE)
    {
      شجرة inc = bitsize_one_عقدة;
      إذا (قيمة && شجرة_CODE (قيمة) == RAW_DATA_CST)
	inc = bitsize_int (RAW_DATA_LENGTH (قيمة));
      constructor_unfilled_index
	= size_binop_loc (مدخل_location, PLUS_تعبير,
			  constructor_unfilled_index, inc);
    }
  وإلا إذا (شجرة_CODE (constructor_type) == RECORD_TYPE)
    {
      constructor_unfilled_fields
	= DECL_CHAIN (constructor_unfilled_fields);

      /* Skip any nameless bit fields.  */
      طالما (constructor_unfilled_fields != NULL_شجرة
	     && DECL_UNNAMED_BIT_FIELD (constructor_unfilled_fields))
	constructor_unfilled_fields
	  = DECL_CHAIN (constructor_unfilled_fields);
    }
  وإلا إذا (شجرة_CODE (constructor_type) == UNION_TYPE)
    constructor_unfilled_fields = NULL_شجرة;

  /* Now output any pending elements which have become next.  */
  إذا (pending)
    output_pending_init_elements (0, braced_init_obstack);
}

/* For two FIELD_DECLs in the same chain, return -1 if field1
   comes before field2, 1 if field1 comes after field2 and
   0 if field1 == field2.  */

ساكن صحيح
init_field_decl_cmp (شجرة field1, شجرة field2)
{
  إذا (field1 == field2)
    أرجع 0;

  شجرة bitpos1 = bit_position (field1);
  شجرة bitpos2 = bit_position (field2);
  إذا (شجرة_int_cst_equal (bitpos1, bitpos2))
    {
      /* If one of the fields has non-zero bitsize, then that
	 field must be the last one in a sequence of zero
	 sized fields, fields after it will have bigger
	 bit_position.  */
      إذا (شجرة_TYPE (field1) != error_mark_عقدة
	  && COMPLETE_TYPE_P (شجرة_TYPE (field1))
	  && integer_nonzerop (شجرة_TYPE (field1)))
	أرجع 1;
      إذا (شجرة_TYPE (field2) != error_mark_عقدة
	  && COMPLETE_TYPE_P (شجرة_TYPE (field2))
	  && integer_nonzerop (شجرة_TYPE (field2)))
	أرجع -1;
      /* Otherwise, fallback to DECL_CHAIN walk to find out
	 which field comes earlier.  Walk chains of both
	 fields, so that if field1 and field2 are close to each
	 other in either order, it is found soon even for large
	 sequences of zero sized fields.  */
      شجرة f1 = field1, f2 = field2;
      طالما (1)
	{
	  f1 = DECL_CHAIN (f1);
	  f2 = DECL_CHAIN (f2);
	  إذا (f1 == NULL_شجرة)
	    {
	      gcc_assert (f2);
	      أرجع 1;
	    }
	  إذا (f2 == NULL_شجرة)
	    أرجع -1;
	  إذا (f1 == field2)
	    أرجع -1;
	  إذا (f2 == field1)
	    أرجع 1;
	  إذا (!شجرة_int_cst_equal (bit_position (f1), bitpos1))
	    أرجع 1;
	  إذا (!شجرة_int_cst_equal (bit_position (f2), bitpos1))
	    أرجع -1;
	}
    }
  وإلا إذا (شجرة_int_cst_lt (bitpos1, bitpos2))
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
  بنية init_عقدة *elt = constructor_pending_elts;
  شجرة next;

 retry:

  /* Look through the whole pending tree.
     If we find an element that should be output now,
     output it.  Otherwise, set NEXT to the element
     that comes first among those still pending.  */

  next = NULL_شجرة;
  طالما (elt)
    {
      إذا (شجرة_CODE (constructor_type) == ARRAY_TYPE)
	{
	  إذا (شجرة_int_cst_equal (elt->purpose,
				  constructor_unfilled_index))
	    output_init_element (مدخل_location, elt->قيمة, elt->origtype,
				 true, شجرة_TYPE (constructor_type),
				 constructor_unfilled_index, خطأ, خطأ,
				 braced_init_obstack);
	  وإلا إذا (شجرة_int_cst_lt (constructor_unfilled_index,
				    elt->purpose))
	    {
	      /* Advance to the next smaller node.  */
	      إذا (elt->يسار)
		elt = elt->يسار;
	      وإلا
		{
		  /* We have reached the smallest node bigger than the
		     current unfilled index.  Fill the space first.  */
		  next = elt->purpose;
		  اكسر;
		}
	    }
	  وإلا
	    {
	      /* Advance to the next bigger node.  */
	      إذا (elt->يمين)
		elt = elt->يمين;
	      وإلا
		{
		  /* We have reached the biggest node in a subtree.  Find
		     the parent of it, which is the next bigger node.  */
		  طالما (elt->parent && elt->parent->يمين == elt)
		    elt = elt->parent;
		  elt = elt->parent;
		  إذا (elt && شجرة_int_cst_lt (constructor_unfilled_index,
					      elt->purpose))
		    {
		      next = elt->purpose;
		      اكسر;
		    }
		}
	    }
	}
      وإلا إذا (RECORD_OR_UNION_TYPE_P (constructor_type))
	{
	  /* If the current record is complete we are done.  */
	  إذا (constructor_unfilled_fields == NULL_شجرة)
	    اكسر;

	  صحيح cmp = init_field_decl_cmp (constructor_unfilled_fields,
					 elt->purpose);
	  إذا (cmp == 0)
	    output_init_element (مدخل_location, elt->قيمة, elt->origtype,
				 true, شجرة_TYPE (elt->purpose),
				 elt->purpose, خطأ, خطأ,
				 braced_init_obstack);
	  وإلا إذا (cmp < 0)
	    {
	      /* Advance to the next smaller node.  */
	      إذا (elt->يسار)
		elt = elt->يسار;
	      وإلا
		{
		  /* We have reached the smallest node bigger than the
		     current unfilled field.  Fill the space first.  */
		  next = elt->purpose;
		  اكسر;
		}
	    }
	  وإلا
	    {
	      /* Advance to the next bigger node.  */
	      إذا (elt->يمين)
		elt = elt->يمين;
	      وإلا
		{
		  /* We have reached the biggest node in a subtree.  Find
		     the parent of it, which is the next bigger node.  */
		  طالما (elt->parent && elt->parent->يمين == elt)
		    elt = elt->parent;
		  elt = elt->parent;
		  إذا (elt
		      && init_field_decl_cmp (constructor_unfilled_fields,
					      elt->purpose) < 0)
		    {
		      next = elt->purpose;
		      اكسر;
		    }
		}
	    }
	}
    }

  /* Ordinarily return, but not if we want to output all
     and there are elements left.  */
  إذا (!(all && next != NULL_شجرة))
    أرجع;

  /* If it's not incremental, just skip over the gap, so that after
     jumping to retry we will output the next successive element.  */
  إذا (RECORD_OR_UNION_TYPE_P (constructor_type))
    constructor_unfilled_fields = next;
  وإلا إذا (شجرة_CODE (constructor_type) == ARRAY_TYPE)
    constructor_unfilled_index = next;

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
initialize_elementwise_p (شجرة type, شجرة قيمة)
{
  إذا (type == error_mark_عقدة || قيمة == error_mark_عقدة)
    أرجع خطأ;

  gcc_checking_assert (TYPE_MAIN_VARIANT (type) == type);

  شجرة قيمة_type = شجرة_TYPE (قيمة);
  إذا (قيمة_type == error_mark_عقدة)
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
  إذا (gnu_vector_type_p (type))
    أرجع !VECTOR_TYPE_P (قيمة_type);

  إذا (AGGREGATE_TYPE_P (type))
    أرجع !comptypes (type, TYPE_MAIN_VARIANT (قيمة_type));

  أرجع خطأ;
}

/* Helper function for process_init_element.  Split first element of
   RAW_DATA_CST and save the rest to *RAW_DATA.  */

ساكن مضمن شجرة
maybe_split_raw_data (شجرة قيمة, شجرة *raw_data)
{
  إذا (قيمة == NULL_شجرة || شجرة_CODE (قيمة) != RAW_DATA_CST)
    أرجع قيمة;
  *raw_data = قيمة;
  قيمة = build_int_cst (integer_type_عقدة,
			 RAW_DATA_UCHAR_ELT (*raw_data, 0));
  ++RAW_DATA_POINTER (*raw_data);
  --RAW_DATA_LENGTH (*raw_data);
  أرجع قيمة;
}

/* Return non-zero if c_parser_initval should attempt to optimize
   large initializers into RAW_DATA_CST.  In that case return how
   many elements to optimize at most.  */

unsigned
c_maybe_optimize_large_byte_initializer (فراغ)
{
  إذا (!constructor_type
      || شجرة_CODE (constructor_type) != ARRAY_TYPE
      || constructor_مكدس->implicit)
    أرجع 0;
  شجرة elttype = TYPE_MAIN_VARIANT (شجرة_TYPE (constructor_type));
  إذا (شجرة_CODE (elttype) != INTEGER_TYPE
      && شجرة_CODE (elttype) != BITINT_TYPE)
    أرجع 0;
  إذا (TYPE_PRECISION (elttype) != CHAR_BIT
      || constructor_مكدس->replacement_قيمة.قيمة
      || (COMPLETE_TYPE_P (constructor_type)
	  && !poly_int_شجرة_p (TYPE_SIZE (constructor_type)))
      || constructor_range_مكدس)
    أرجع 0;
  إذا (constructor_max_index == NULL_شجرة)
    أرجع INT_MAX;
  إذا (شجرة_int_cst_le (constructor_max_index, constructor_index)
      || integer_all_onesp (constructor_max_index))
    أرجع 0;
  widest_int w = wi::to_widest (constructor_max_index);
  w -= wi::to_widest (constructor_index);
  w += 1;
  إذا (w < 64)
    أرجع 0;
  إذا (w > INT_MAX)
    أرجع INT_MAX;
  أرجع w.to_uhwi ();
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
process_init_element (location_t loc, بنية c_تعبير قيمة, منطقي implicit,
		      بنية obstack * braced_init_obstack)
{
  شجرة orig_قيمة = قيمة.قيمة;
  صحيح string_flag
    = (orig_قيمة != NULL_شجرة && شجرة_CODE (orig_قيمة) == STRING_CST);
  منطقي strict_string = قيمة.original_code == STRING_CST;
  منطقي was_designated = designator_depth != 0;
  شجرة raw_data = NULL_شجرة;

retry:
  designator_depth = 0;
  designator_erroneous = 0;

  إذا (!implicit && قيمة.قيمة && !integer_zerop (قيمة.قيمة))
    constructor_zeroinit = 0;

  /* Handle superfluous braces around string cst as in
     char x[] = {"foo"}; */
  إذا (constructor_type
      && !was_designated
      && شجرة_CODE (constructor_type) == ARRAY_TYPE
      && INTEGRAL_TYPE_P (شجرة_TYPE (constructor_type))
      && integer_zerop (constructor_unfilled_index))
    {
      إذا (constructor_مكدس->replacement_قيمة.قيمة)
	{
	  error_init (loc, "excess elements in %qT initializer", constructor_type);
	  أرجع;
	}
      وإلا إذا (string_flag)
	{
	  constructor_مكدس->replacement_قيمة = قيمة;
	  أرجع;
	}
    }

  إذا (constructor_مكدس->replacement_قيمة.قيمة != NULL_شجرة)
    {
      error_init (loc, "excess elements in struct initializer");
      أرجع;
    }

  /* Ignore elements of a brace group if it is entirely superfluous
     and has already been diagnosed, or if the type is erroneous.  */
  إذا (constructor_type == NULL_شجرة || constructor_type == error_mark_عقدة)
    أرجع;

  /* Ignore elements of an initializer for a variable-size type.
     Those are diagnosed in the parser (empty initializer braces are OK).  */
  إذا (COMPLETE_TYPE_P (constructor_type)
      && !poly_int_شجرة_p (TYPE_SIZE (constructor_type)))
    أرجع;

  إذا (!implicit && warn_designated_init && !was_designated
      && شجرة_CODE (constructor_type) == RECORD_TYPE
      && lookup_attribute ("designated_init",
			   TYPE_ATTRIBUTES (constructor_type)))
    warning_init (loc,
		  OPT_Wdesignated_init,
		  "positional initialization of field "
		  "in %<struct%> declared with %<designated_init%> attribute");

  /* If we've exhausted any levels that didn't have braces,
     pop them now.  */
  طالما (constructor_مكدس->implicit)
    {
      إذا (RECORD_OR_UNION_TYPE_P (constructor_type)
	  && constructor_fields == NULL_شجرة)
	process_init_element (loc,
			      اسحب_init_level (loc, 1, braced_init_obstack,
					      last_init_list_comma),
			      true, braced_init_obstack);
      وإلا إذا ((شجرة_CODE (constructor_type) == ARRAY_TYPE
		|| gnu_vector_type_p (constructor_type))
	       && constructor_max_index
	       && شجرة_int_cst_lt (constructor_max_index,
				   constructor_index))
	process_init_element (loc,
			      اسحب_init_level (loc, 1, braced_init_obstack,
					      last_init_list_comma),
			      true, braced_init_obstack);
      وإلا
	اكسر;
    }

  /* In the case of [LO ... HI] = VALUE, only evaluate VALUE once.  */
  إذا (constructor_range_مكدس)
    {
      /* If value is a compound literal and we'll be just using its
	 content, don't put it into a SAVE_EXPR.  */
      إذا (شجرة_CODE (قيمة.قيمة) != COMPOUND_LITERAL_تعبير
	  || !require_constant_قيمة)
	{
	  شجرة semantic_type = NULL_شجرة;
	  إذا (شجرة_CODE (قيمة.قيمة) == EXCESS_PRECISION_تعبير)
	    {
	      semantic_type = شجرة_TYPE (قيمة.قيمة);
	      قيمة.قيمة = شجرة_OPERAND (قيمة.قيمة, 0);
	    }
	  قيمة.قيمة = save_تعبير (قيمة.قيمة);
	  إذا (semantic_type)
	    قيمة.قيمة = build1 (EXCESS_PRECISION_تعبير, semantic_type,
				  قيمة.قيمة);
	}
    }

  طالما (1)
    {
      إذا (شجرة_CODE (constructor_type) == RECORD_TYPE)
	{
	  شجرة fieldtype;
	  تعداد شجرة_code fieldcode;

	  إذا (constructor_fields == NULL_شجرة)
	    {
	      pedwarn_init (loc, 0, "excess elements in struct initializer");
	      اكسر;
	    }

	  fieldtype = شجرة_TYPE (constructor_fields);
	  إذا (fieldtype != error_mark_عقدة)
	    fieldtype = TYPE_MAIN_VARIANT (fieldtype);
	  fieldcode = شجرة_CODE (fieldtype);

	  /* Error for non-static initialization of a flexible array member.  */
	  إذا (fieldcode == ARRAY_TYPE
	      && !require_constant_قيمة
	      && TYPE_SIZE (fieldtype) == NULL_شجرة
	      && DECL_CHAIN (constructor_fields) == NULL_شجرة)
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
	      && constructor_depth > 1
	      && TYPE_SIZE (fieldtype) == NULL_شجرة
	      && DECL_CHAIN (constructor_fields) == NULL_شجرة)
	    {
	      منطقي in_array_p = خطأ;
	      لكل (بنية constructor_مكدس *p = constructor_مكدس;
		   p && p->type; p = p->next)
		إذا (شجرة_CODE (p->type) == ARRAY_TYPE)
		  {
		    in_array_p = true;
		    اكسر;
		  }
	      إذا (in_array_p)
		{
		  error_init (loc, "initialization of flexible array "
			      "member in a nested context");
		  اكسر;
		}
	    }

	  /* Accept a string constant to initialize a subarray.  */
	  إذا (قيمة.قيمة != NULL_شجرة
	      && fieldcode == ARRAY_TYPE
	      && INTEGRAL_TYPE_P (شجرة_TYPE (fieldtype))
	      && string_flag)
	    قيمة.قيمة = orig_قيمة;
	  /* Otherwise, if we have come to a subaggregate,
	     and we don't have an element of its type, push into it.  */
	  وإلا إذا (قيمة.قيمة != NULL_شجرة
		   && initialize_elementwise_p (fieldtype, قيمة.قيمة))
	    {
	      ادفع_init_level (loc, 1, braced_init_obstack);
	      استمر;
	    }

	  قيمة.قيمة = maybe_split_raw_data (قيمة.قيمة, &raw_data);
	  إذا (قيمة.قيمة)
	    {
	      ادفع_member_name (constructor_fields);
	      output_init_element (loc, قيمة.قيمة, قيمة.original_type,
				   strict_string, fieldtype,
				   constructor_fields, true, implicit,
				   braced_init_obstack);
	      RESTORE_SPELLING_DEPTH (constructor_depth);
	    }
	  وإلا
	    /* Do the bookkeeping for an element that was
	       directly output as a constructor.  */
	    {
	      /* For a record, keep track of end position of last field.  */
	      إذا (DECL_SIZE (constructor_fields))
		constructor_bit_index
		  = size_binop_loc (مدخل_location, PLUS_تعبير,
				    bit_position (constructor_fields),
				    DECL_SIZE (constructor_fields));

	      /* If the current field was the first one not yet written out,
		 it isn't now, so update.  */
	      إذا (constructor_unfilled_fields == constructor_fields)
		{
		  constructor_unfilled_fields = DECL_CHAIN (constructor_fields);
		  /* Skip any nameless bit fields.  */
		  طالما (constructor_unfilled_fields != 0
			 && (DECL_UNNAMED_BIT_FIELD
			     (constructor_unfilled_fields)))
		    constructor_unfilled_fields =
		      DECL_CHAIN (constructor_unfilled_fields);
		}
	    }

	  constructor_fields = DECL_CHAIN (constructor_fields);
	  /* Skip any nameless bit fields at the beginning.  */
	  طالما (constructor_fields != NULL_شجرة
		 && DECL_UNNAMED_BIT_FIELD (constructor_fields))
	    constructor_fields = DECL_CHAIN (constructor_fields);
	}
      وإلا إذا (شجرة_CODE (constructor_type) == UNION_TYPE)
	{
	  شجرة fieldtype;
	  تعداد شجرة_code fieldcode;

	  إذا (constructor_fields == NULL_شجرة)
	    {
	      pedwarn_init (loc, 0,
			    "excess elements in union initializer");
	      اكسر;
	    }

	  fieldtype = شجرة_TYPE (constructor_fields);
	  إذا (fieldtype != error_mark_عقدة)
	    fieldtype = TYPE_MAIN_VARIANT (fieldtype);
	  fieldcode = شجرة_CODE (fieldtype);

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
	  إذا (!in_system_header_at (مدخل_location) && !constructor_designated
	      && !(قيمة.قيمة && (integer_zerop (قيمة.قيمة)
				   || real_zerop (قيمة.قيمة))))
	    warning (OPT_Wtraditional, "traditional C rejects initialization "
		     "of unions");

	  /* Error for non-static initialization of a flexible array member.  */
	  إذا (fieldcode == ARRAY_TYPE
	      && !require_constant_قيمة
	      && TYPE_SIZE (fieldtype) == NULL_شجرة)
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
	      && constructor_depth > 1
	      && TYPE_SIZE (fieldtype) == NULL_شجرة)
	    {
	      منطقي in_array_p = خطأ;
	      لكل (بنية constructor_مكدس *p = constructor_مكدس;
		   p && p->type; p = p->next)
		إذا (شجرة_CODE (p->type) == ARRAY_TYPE)
		  {
		    in_array_p = true;
		    اكسر;
		  }
	      إذا (in_array_p)
		{
		  error_init (loc, "initialization of flexible array "
			      "member in a nested context");
		  اكسر;
		}
	    }

	  /* Accept a string constant to initialize a subarray.  */
	  إذا (قيمة.قيمة != NULL_شجرة
	      && fieldcode == ARRAY_TYPE
	      && INTEGRAL_TYPE_P (شجرة_TYPE (fieldtype))
	      && string_flag)
	    قيمة.قيمة = orig_قيمة;
	  /* Otherwise, if we have come to a subaggregate,
	     and we don't have an element of its type, push into it.  */
	  وإلا إذا (قيمة.قيمة != NULL_شجرة
		   && initialize_elementwise_p (fieldtype, قيمة.قيمة))
	    {
	      ادفع_init_level (loc, 1, braced_init_obstack);
	      استمر;
	    }

	  قيمة.قيمة = maybe_split_raw_data (قيمة.قيمة, &raw_data);
	  إذا (قيمة.قيمة)
	    {
	      ادفع_member_name (constructor_fields);
	      output_init_element (loc, قيمة.قيمة, قيمة.original_type,
				   strict_string, fieldtype,
				   constructor_fields, true, implicit,
				   braced_init_obstack);
	      RESTORE_SPELLING_DEPTH (constructor_depth);
	    }
	  وإلا
	    /* Do the bookkeeping for an element that was
	       directly output as a constructor.  */
	    {
	      constructor_bit_index = DECL_SIZE (constructor_fields);
	      constructor_unfilled_fields = DECL_CHAIN (constructor_fields);
	    }

	  constructor_fields = NULL_شجرة;
	}
      وإلا إذا (شجرة_CODE (constructor_type) == ARRAY_TYPE)
	{
	  شجرة elttype = TYPE_MAIN_VARIANT (شجرة_TYPE (constructor_type));
	  تعداد شجرة_code eltcode = شجرة_CODE (elttype);

	  /* Accept a string constant to initialize a subarray.  */
	  إذا (قيمة.قيمة != NULL_شجرة
	      && eltcode == ARRAY_TYPE
	      && INTEGRAL_TYPE_P (شجرة_TYPE (elttype))
	      && string_flag)
	    قيمة.قيمة = orig_قيمة;
	  /* Otherwise, if we have come to a subaggregate,
	     and we don't have an element of its type, push into it.  */
	  وإلا إذا (قيمة.قيمة != NULL_شجرة
		   && initialize_elementwise_p (elttype, قيمة.قيمة))
	    {
	      ادفع_init_level (loc, 1, braced_init_obstack);
	      استمر;
	    }

	  إذا (constructor_max_index != NULL_شجرة
	      && (شجرة_int_cst_lt (constructor_max_index, constructor_index)
		  || integer_all_onesp (constructor_max_index))
	      /* For VLA we got an error already.  */
	      && !C_TYPE_VARIABLE_SIZE (constructor_type))
	    {
	      pedwarn_init (loc, 0,
			    "excess elements in array initializer");
	      اكسر;
	    }

	  إذا (قيمة.قيمة
	      && شجرة_CODE (قيمة.قيمة) == RAW_DATA_CST
	      && RAW_DATA_LENGTH (قيمة.قيمة) > 1
	      && (شجرة_CODE (elttype) == INTEGER_TYPE
		  || شجرة_CODE (elttype) == BITINT_TYPE)
	      && TYPE_PRECISION (elttype) == CHAR_BIT
	      && (constructor_max_index == NULL_شجرة
		  || شجرة_int_cst_lt (constructor_index,
				      constructor_max_index)))
	    {
	      unsigned صحيح len = RAW_DATA_LENGTH (قيمة.قيمة);
	      إذا (constructor_max_index)
		{
		  widest_int w = wi::to_widest (constructor_max_index);
		  w -= wi::to_widest (constructor_index);
		  w += 1;
		  إذا (w < len)
		    len = w.to_uhwi ();
		}
	      إذا (len < (unsigned) RAW_DATA_LENGTH (قيمة.قيمة))
		{
		  raw_data = copy_عقدة (قيمة.قيمة);
		  RAW_DATA_LENGTH (raw_data) -= len;
		  RAW_DATA_POINTER (raw_data) += len;
		  RAW_DATA_LENGTH (قيمة.قيمة) = len;
		}
	      شجرة_TYPE (قيمة.قيمة) = elttype;
	      ادفع_array_bounds (شجرة_to_uhwi (constructor_index));
	      output_init_element (loc, قيمة.قيمة, قيمة.original_type,
				   خطأ, elttype, constructor_index, true,
				   implicit, braced_init_obstack);
	      RESTORE_SPELLING_DEPTH (constructor_depth);
	      constructor_index
		= size_binop_loc (مدخل_location, PLUS_تعبير,
				  constructor_index, bitsize_int (len));
	    }
	  وإلا
	    {
	      قيمة.قيمة = maybe_split_raw_data (قيمة.قيمة, &raw_data);
	      /* Now output the actual element.  */
	      إذا (قيمة.قيمة)
		{
		  ادفع_array_bounds (شجرة_to_uhwi (constructor_index));
		  output_init_element (loc, قيمة.قيمة, قيمة.original_type,
				       strict_string, elttype,
				       constructor_index, true, implicit,
				       braced_init_obstack);
		  RESTORE_SPELLING_DEPTH (constructor_depth);
		}

	      constructor_index
		= size_binop_loc (مدخل_location, PLUS_تعبير,
				  constructor_index, bitsize_one_عقدة);

	      إذا (!قيمة.قيمة)
		/* If we are doing the bookkeeping for an element that was
		   directly output as a constructor, we must update
		   constructor_unfilled_index.  */
		constructor_unfilled_index = constructor_index;
	    }
	}
      وإلا إذا (gnu_vector_type_p (constructor_type))
	{
	  شجرة elttype = TYPE_MAIN_VARIANT (شجرة_TYPE (constructor_type));

	  /* Do a basic check of initializer size.  Note that vectors
	     may not always have a fixed size derived from their type.  */
	  إذا (maybe_lt (شجرة_to_poly_uint64 (constructor_max_index),
			شجرة_to_poly_uint64 (constructor_index)))
	    {
	      /* Diagose VLA out-of-bounds as errors.  */
	      إذا (شجرة_to_poly_uint64 (constructor_max_index).is_constant())
		pedwarn_init (loc, 0,
			      "excess elements in vector initializer");
	      وإلا
		error_init (loc, "excess elements in vector initializer");

	      اكسر;
	    }

	  قيمة.قيمة = maybe_split_raw_data (قيمة.قيمة, &raw_data);
	  /* Now output the actual element.  */
	  إذا (قيمة.قيمة)
	    {
	      إذا (شجرة_CODE (قيمة.قيمة) == VECTOR_CST)
		elttype = TYPE_MAIN_VARIANT (constructor_type);
	      output_init_element (loc, قيمة.قيمة, قيمة.original_type,
				   strict_string, elttype,
				   constructor_index, true, implicit,
				   braced_init_obstack);
	    }

	  constructor_index
	    = size_binop_loc (مدخل_location,
			      PLUS_تعبير, constructor_index, bitsize_one_عقدة);

	  إذا (!قيمة.قيمة)
	    /* If we are doing the bookkeeping for an element that was
	       directly output as a constructor, we must update
	       constructor_unfilled_index.  */
	    constructor_unfilled_index = constructor_index;
	}

      /* Handle the sole element allowed in a braced initializer
	 for a scalar variable.  */
      وإلا إذا (constructor_type != error_mark_عقدة
	       && constructor_fields == NULL_شجرة)
	{
	  pedwarn_init (loc, 0,
			"excess elements in scalar initializer");
	  اكسر;
	}
      وإلا
	{
	  قيمة.قيمة = maybe_split_raw_data (قيمة.قيمة, &raw_data);
	  إذا (قيمة.قيمة)
	    output_init_element (loc, قيمة.قيمة, قيمة.original_type,
				 strict_string, constructor_type,
				 NULL_شجرة, true, implicit,
				 braced_init_obstack);
	  constructor_fields = NULL_شجرة;
	}

      /* Handle range initializers either at this level or anywhere higher
	 in the designator stack.  */
      إذا (constructor_range_مكدس)
	{
	  بنية constructor_range_مكدس *p, *range_مكدس;
	  صحيح finish = 0;

	  range_مكدس = constructor_range_مكدس;
	  constructor_range_مكدس = 0;
	  طالما (constructor_مكدس != range_مكدس->مكدس)
	    {
	      gcc_assert (constructor_مكدس->implicit);
	      process_init_element (loc,
				    اسحب_init_level (loc, 1,
						    braced_init_obstack,
						    last_init_list_comma),
				    true, braced_init_obstack);
	    }
	  لكل (p = range_مكدس;
	       !p->range_end || شجرة_int_cst_equal (p->index, p->range_end);
	       p = p->prev)
	    {
	      gcc_assert (constructor_مكدس->implicit);
	      process_init_element (loc,
				    اسحب_init_level (loc, 1,
						    braced_init_obstack,
						    last_init_list_comma),
				    true, braced_init_obstack);
	    }

	  p->index = size_binop_loc (مدخل_location,
				     PLUS_تعبير, p->index, bitsize_one_عقدة);
	  إذا (شجرة_int_cst_equal (p->index, p->range_end) && !p->prev)
	    finish = 1;

	  طالما (1)
	    {
	      constructor_index = p->index;
	      constructor_fields = p->fields;
	      إذا (finish && p->range_end && p->index == p->range_start)
		{
		  finish = 0;
		  p->prev = 0;
		}
	      p = p->next;
	      إذا (!p)
		اكسر;
	      finish_implicit_inits (loc, braced_init_obstack);
	      ادفع_init_level (loc, 2, braced_init_obstack);
	      p->مكدس = constructor_مكدس;
	      إذا (p->range_end && شجرة_int_cst_equal (p->index, p->range_end))
		p->index = p->range_start;
	    }

	  إذا (!finish)
	    constructor_range_مكدس = range_مكدس;
	  استمر;
	}

      اكسر;
    }

  constructor_range_مكدس = 0;

  إذا (raw_data && RAW_DATA_LENGTH (raw_data))
    {
      gcc_assert (!string_flag && !was_designated);
      قيمة.قيمة = raw_data;
      raw_data = NULL_شجرة;
      اذهب retry;
    }
}

/* Build a complete asm-statement, whose components are a CV_QUALIFIER
   (guaranteed to be 'volatile' or null) and ARGS (represented using
   an ASM_EXPR node).  */
شجرة
build_asm_stmt (منطقي is_volatile, شجرة وسائط)
{
  إذا (is_volatile)
    ASM_VOLATILE_P (وسائط) = 1;
  أرجع add_stmt (وسائط);
}

/* Build an asm-expr, whose components are a STRING, some OUTPUTS,
   some INPUTS, and some CLOBBERS.  The latter three may be NULL.
   SIMPLE indicates whether there was anything at all after the
   string in the asm expression -- asm("blah") and asm("blah" : )
   are subtly different.  We use a ASM_EXPR node to represent this.
   LOC is the location of the asm, and IS_INLINE says whether this
   is asm inline.  */
شجرة
build_asm_تعبير (location_t loc, شجرة string, شجرة outputs, شجرة inputs,
		شجرة clobbers, شجرة labels, منطقي simple, منطقي is_inline)
{
  شجرة tail;
  شجرة وسائط;
  صحيح i;
  ثابت حرف *constraint;
  ثابت حرف **oconstraints;
  منطقي allows_mem, allows_reg, is_inout;
  صحيح ninputs, noutputs;

  ninputs = list_length (inputs);
  noutputs = list_length (outputs);
  oconstraints = (ثابت حرف **) alloca (noutputs * حجم (ثابت حرف *));

  string = resolve_asm_operand_names (string, outputs, inputs, labels);

  /* Remove output conversions that change the type but not the mode.  */
  لكل (i = 0, tail = outputs; tail; ++i, tail = شجرة_CHAIN (tail))
    {
      شجرة output = شجرة_قيمة (tail);

      output = c_fully_fold (output, خطأ, عدم, true);

      /* ??? Really, this should not be here.  Users should be using a
	 proper lvalue, dammit.  But there's a long history of using casts
	 in the output operands.  In cases like longlong.h, this becomes a
	 primitive form of typechecking -- if the cast can be removed, then
	 the output operand had a type of the proper width; otherwise we'll
	 get an error.  Gross, but ...  */
      STRIP_NOPS (output);

      إذا (!lvalue_or_else (loc, output, lv_asm))
	output = error_mark_عقدة;

      إذا (output != error_mark_عقدة
	  && (شجرة_READONLY (output)
	      || TYPE_READONLY (شجرة_TYPE (output))
	      || (RECORD_OR_UNION_TYPE_P (شجرة_TYPE (output))
		  && C_TYPE_FIELDS_READONLY (شجرة_TYPE (output)))))
	readonly_error (loc, output, lv_asm);

      constraint = شجرة_STRING_POINTER (شجرة_قيمة (شجرة_PURPOSE (tail)));
      oconstraints[i] = constraint;

      إذا (parse_output_constraint (&constraint, i, ninputs, noutputs,
				   &allows_mem, &allows_reg, &is_inout,
				   nullptr))
	{
	  /* If the operand is going to end up in memory,
	     mark it addressable.  */
	  إذا (!allows_reg && !c_mark_addressable (output))
	    output = error_mark_عقدة;
	  إذا (!(!allows_reg && allows_mem)
	      && output != error_mark_عقدة
	      && VOID_TYPE_P (شجرة_TYPE (output)))
	    {
	      error_at (loc, "invalid use of void expression");
	      output = error_mark_عقدة;
	    }
	  إذا (allows_reg && current_function_decl == NULL_شجرة)
	    {
	      error_at (loc, "constraint allows registers outside of "
			     "a function");
	      output = error_mark_عقدة;
	    }
	}
      وإلا
	output = error_mark_عقدة;

      إذا (current_function_decl == NULL_شجرة && output != error_mark_عقدة)
	{
	  إذا (شجرة_SIDE_EFFECTS (output))
	    {
	      error_at (loc, "side-effects in output operand outside "
			     "of a function");
	      output = error_mark_عقدة;
	    }
	  وإلا
	    {
	      شجرة addr = build_unary_op (loc, ADDR_تعبير, output, خطأ);
	      إذا (addr == error_mark_عقدة)
		output = error_mark_عقدة;
	      وإلا إذا (!initializer_constant_valid_p (addr, شجرة_TYPE (addr)))
		{
		  error_at (loc, "output operand outside of a function is not "
				 "constant");
		  output = error_mark_عقدة;
		}
	    }
	}
      وإلا إذا (output != error_mark_عقدة && strstr (constraint, "-"))
	{
	  error_at (loc, "%<-%> modifier used inside of a function");
	  output = error_mark_عقدة;
	}

      شجرة_قيمة (tail) = output;
    }

  لكل (i = 0, tail = inputs; tail; ++i, tail = شجرة_CHAIN (tail))
    {
      شجرة مدخل;

      constraint = شجرة_STRING_POINTER (شجرة_قيمة (شجرة_PURPOSE (tail)));
      مدخل = شجرة_قيمة (tail);

      إذا (parse_مدخل_constraint (&constraint, i, ninputs, noutputs, 0,
				  oconstraints, &allows_mem, &allows_reg,
				  nullptr))
	{
	  /* If the operand is going to end up in memory,
	     mark it addressable.  */
	  إذا (!allows_reg && allows_mem)
	    {
	      مدخل = c_fully_fold (مدخل, خطأ, عدم, true);

	      /* Strip the nops as we allow this case.  FIXME, this really
		 should be rejected or made deprecated.  */
	      STRIP_NOPS (مدخل);
	      إذا (!c_mark_addressable (مدخل))
		مدخل = error_mark_عقدة;
	    }
	  وإلا
	    {
	      مدخل = c_fully_fold (convert_lvalue_to_rvalue (loc, مدخل,
							      true, خطأ),
				    خطأ, عدم);

	      إذا (مدخل != error_mark_عقدة && VOID_TYPE_P (شجرة_TYPE (مدخل)))
		{
		  error_at (loc, "invalid use of void expression");
		  مدخل = error_mark_عقدة;
		}
	    }
	  إذا (allows_reg && current_function_decl == NULL_شجرة)
	    {
	      error_at (loc, "constraint allows registers outside of "
			     "a function");
	      مدخل = error_mark_عقدة;
	    }
	  إذا (constraint[0] == ':' && مدخل != error_mark_عقدة)
	    {
	      شجرة t = مدخل;
	      STRIP_NOPS (t);
	      إذا (شجرة_CODE (t) != ADDR_تعبير
		  || !(شجرة_CODE (شجرة_OPERAND (t, 0)) == FUNCTION_DECL
		       || (VAR_P (شجرة_OPERAND (t, 0))
			   && is_global_var (شجرة_OPERAND (t, 0)))))
		{
		  error_at (loc, "%<:%> constraint operand is not address "
				 "of a function or non-automatic variable");
		  مدخل = error_mark_عقدة;
		}
	      وإلا إذا (شجرة_CODE (شجرة_OPERAND (t, 0)) == FUNCTION_DECL)
		suppress_warning (شجرة_OPERAND (t, 0), OPT_Wunused);
	    }
	}
      وإلا
	مدخل = error_mark_عقدة;

      إذا (current_function_decl == NULL_شجرة && مدخل != error_mark_عقدة)
	{
	  إذا (شجرة_SIDE_EFFECTS (مدخل))
	    {
	      error_at (loc, "side-effects in input operand outside "
			     "of a function");
	      مدخل = error_mark_عقدة;
	    }
	  وإلا
	    {
	      شجرة tem = مدخل;
	      إذا (allows_mem && lvalue_p (مدخل))
		tem = build_unary_op (loc, ADDR_تعبير, مدخل, خطأ);
	      إذا (!initializer_constant_valid_p (tem, شجرة_TYPE (tem)))
		{
		  error_at (loc, "input operand outside of a function is not "
				 "constant");
		  مدخل = error_mark_عقدة;
		}
	    }
	}
      وإلا إذا (مدخل != error_mark_عقدة && strstr (constraint, "-"))
	{
	  error_at (loc, "%<-%> modifier used inside of a function");
	  مدخل = error_mark_عقدة;
	}

      شجرة_قيمة (tail) = مدخل;
    }

  وسائط = build_stmt (loc, ASM_تعبير, string, outputs, inputs, clobbers, labels);

  /* asm statements without outputs, including simple ones, are treated
     as volatile.  */
  ASM_BASIC_P (وسائط) = simple;
  ASM_VOLATILE_P (وسائط) = (noutputs == 0);
  ASM_INLINE_P (وسائط) = is_inline;

  أرجع وسائط;
}

/* Generate a goto statement to LABEL.  LOC is the location of the
   GOTO.  */

شجرة
c_finish_goto_label (location_t loc, شجرة label)
{
  شجرة decl = lookup_label_for_goto (loc, label);
  إذا (!decl)
    أرجع NULL_شجرة;
  شجرة_USED (decl) = 1;
  mark_decl_used (decl, خطأ);
  {
    add_stmt (build_predict_تعبير (PRED_GOTO, NOT_TAKEN));
    شجرة t = build1 (GOTO_تعبير, void_type_عقدة, decl);
    SET_تعبير_LOCATION (t, loc);
    أرجع add_stmt (t);
  }
}

/* Generate a computed goto statement to EXPR.  LOC is the location of
   the GOTO.  */

شجرة
c_finish_goto_ptr (location_t loc, c_تعبير val)
{
  شجرة تعبير = val.قيمة;
  شجرة t;
  pedwarn (loc, OPT_Wpedantic, "ISO C forbids %<goto *expr;%>");
  إذا (تعبير != error_mark_عقدة
      && !POINTER_TYPE_P (شجرة_TYPE (تعبير))
      && !null_pointer_constant_p (تعبير))
    {
      error_at (val.get_location (),
		"computed goto must be pointer type");
      تعبير = build_zero_cst (ptr_type_عقدة);
    }
  تعبير = c_fully_fold (تعبير, خطأ, عدم);
  تعبير = convert (ptr_type_عقدة, تعبير);
  t = build1 (GOTO_تعبير, void_type_عقدة, تعبير);
  SET_تعبير_LOCATION (t, loc);
  أرجع add_stmt (t);
}

/* Generate a C `return' statement.  RETVAL is the expression for what
   to return, or a null pointer for `return;' with no value.  LOC is
   the location of the return statement, or the location of the expression,
   if the statement has any.  If ORIGTYPE is not NULL_TREE, it
   is the original type of RETVAL.  MUSTTAIL_P indicates a musttail
   attribute.  */

شجرة
c_finish_return (location_t loc, شجرة retval, شجرة origtype, منطقي musttail_p)
{
  شجرة valtype = شجرة_TYPE (شجرة_TYPE (current_function_decl)), ret_stmt;
  منطقي no_warning = خطأ;
  منطقي npc = خطأ;

  /* Use the expansion point to handle cases such as returning NULL
     in a function returning void.  */
  location_t xloc = expansion_point_location_if_in_system_header (loc);

  إذا (شجرة_THIS_VOLATILE (current_function_decl))
    warning_at (xloc, 0,
		"function declared %<noreturn%> has a %<return%> statement");

  set_musttail_on_return (retval, xloc, musttail_p);

  إذا (retval)
    {
      شجرة semantic_type = NULL_شجرة;
      npc = null_pointer_constant_p (retval);
      إذا (شجرة_CODE (retval) == EXCESS_PRECISION_تعبير)
	{
	  semantic_type = شجرة_TYPE (retval);
	  retval = شجرة_OPERAND (retval, 0);
	}
      retval = c_fully_fold (retval, خطأ, عدم);
      إذا (semantic_type
	  && valtype != NULL_شجرة
	  && شجرة_CODE (valtype) != VOID_TYPE)
	retval = build1 (EXCESS_PRECISION_تعبير, semantic_type, retval);
    }

  إذا (!retval)
    {
      current_function_returns_null = 1;
      إذا ((warn_return_type >= 0 || flag_isoc99)
	  && valtype != NULL_شجرة && شجرة_CODE (valtype) != VOID_TYPE)
	{
	  no_warning = true;
	  إذا (emit_diagnostic (flag_isoc99
			       ? diagnostics::kind::permerror
			       : diagnostics::kind::warning,
			       loc, OPT_Wreturn_mismatch,
			       "%<return%> with no value,"
			       " in function returning non-void"))
	    inform (DECL_SOURCE_LOCATION (current_function_decl),
		    "declared here");
	}
    }
  وإلا إذا (valtype == NULL_شجرة || VOID_TYPE_P (valtype))
    {
      current_function_returns_null = 1;
      منطقي warned_here;
      إذا (شجرة_CODE (شجرة_TYPE (retval)) != VOID_TYPE)
	warned_here = permerror_opt
	  (xloc, OPT_Wreturn_mismatch,
	   "%<return%> with a value, in function returning void");
      وإلا
	warned_here = pedwarn
	  (xloc, OPT_Wpedantic, "ISO C forbids "
	   "%<return%> with expression, in function returning void");
      إذا (warned_here)
	inform (DECL_SOURCE_LOCATION (current_function_decl),
		"declared here");
    }
  وإلا
    {
      شجرة t = convert_for_assignment (loc, UNKNOWN_LOCATION, valtype,
				       retval, origtype, ic_return,
				       npc, NULL_شجرة, NULL_شجرة, 0);
      شجرة res = DECL_RESULT (current_function_decl);
      شجرة inner;
      منطقي save;

      current_function_returns_قيمة = 1;
      إذا (t == error_mark_عقدة)
	{
	  /* Suppress -Wreturn-type for this function.  */
	  إذا (warn_return_type)
	    suppress_warning (current_function_decl, OPT_Wreturn_type);
	  أرجع NULL_شجرة;
	}

      save = in_late_ثنائي_op;
      إذا (C_BOOLEAN_TYPE_P (شجرة_TYPE (res))
	  || شجرة_CODE (شجرة_TYPE (res)) == COMPLEX_TYPE
	  || (SCALAR_FLOAT_TYPE_P (شجرة_TYPE (t))
	      && (شجرة_CODE (شجرة_TYPE (res)) == INTEGER_TYPE
		  || شجرة_CODE (شجرة_TYPE (res)) == ENUMERAL_TYPE)
	      && sanitize_flags_p (SANITIZE_FLOAT_CAST)))
        in_late_ثنائي_op = true;
      inner = t = convert (شجرة_TYPE (res), t);
      in_late_ثنائي_op = save;

      /* Strip any conversions, additions, and subtractions, and see if
	 we are returning the address of a local variable.  Warn if so.  */
      طالما (1)
	{
	  بدل (شجرة_CODE (inner))
	    {
	    CASE_CONVERT:
	    حالة NON_LVALUE_تعبير:
	    حالة PLUS_تعبير:
	    حالة POINTER_PLUS_تعبير:
	      inner = شجرة_OPERAND (inner, 0);
	      استمر;

	    حالة MINUS_تعبير:
	      /* If the second operand of the MINUS_EXPR has a pointer
		 type (or is converted from it), this may be valid, so
		 don't give a warning.  */
	      {
		شجرة op1 = شجرة_OPERAND (inner, 1);

		طالما (!POINTER_TYPE_P (شجرة_TYPE (op1))
		       && (CONVERT_تعبير_P (op1)
			   || شجرة_CODE (op1) == NON_LVALUE_تعبير))
		  op1 = شجرة_OPERAND (op1, 0);

		إذا (POINTER_TYPE_P (شجرة_TYPE (op1)))
		  اكسر;

		inner = شجرة_OPERAND (inner, 0);
		استمر;
	      }

	    حالة ADDR_تعبير:
	      inner = شجرة_OPERAND (inner, 0);

	      طالما (REFERENCE_CLASS_P (inner)
		     && !INDIRECT_REF_P (inner))
		inner = شجرة_OPERAND (inner, 0);

	      إذا (DECL_P (inner)
		  && !DECL_EXTERNAL (inner)
		  && DECL_CONTEXT (inner) == current_function_decl
		  && POINTER_TYPE_P (شجرة_TYPE (شجرة_TYPE (current_function_decl))))
		{
		  إذا (شجرة_CODE (inner) == LABEL_DECL)
		    warning_at (loc, OPT_Wreturn_local_addr,
				"function returns address of label");
		  وإلا إذا (شجرة_CODE (inner) == FUNCTION_DECL
			   && (C_FUNC_NONLOCAL_CONTEXT (inner)
			       || !DECL_INITIAL (inner)))
		    warning_at (loc, OPT_Wreturn_local_addr,
				"function returns address of nested function "
				"referencing local context");
		  وإلا إذا (شجرة_CODE (inner) != FUNCTION_DECL
			   && !شجرة_STATIC (inner))
		    {
		      warning_at (loc, OPT_Wreturn_local_addr,
				  "function returns address of local variable");
		      شجرة zero = build_zero_cst (شجرة_TYPE (res));
		      t = build2 (COMPOUND_تعبير, شجرة_TYPE (res), t, zero);
		    }
		}
	      اكسر;

	    افتراضي:
	      اكسر;
	    }

	  اكسر;
	}

      retval = build2 (MODIFY_تعبير, شجرة_TYPE (res), res, t);
      SET_تعبير_LOCATION (retval, loc);

      إذا (warn_sequence_point)
	verify_sequence_points (retval);
    }

  ret_stmt = build_stmt (loc, RETURN_تعبير, retval);
  إذا (no_warning)
    suppress_warning (ret_stmt, OPT_Wreturn_type);
  أرجع add_stmt (ret_stmt);
}

بنية c_switch {
  /* The SWITCH_STMT being built.  */
  شجرة switch_stmt;

  /* The original type of the testing expression, i.e. before the
     default conversion is applied.  */
  شجرة orig_type;

  /* A splay-tree mapping the low element of a case range to the high
     element, or NULL_TREE if there is no high element.  Used to
     determine whether or not a new case label duplicates an old case
     label.  We need a tree, rather than simply a hash table, because
     of the GNU case range extension.  */
  splay_شجرة cases;

  /* The bindings at the point of the switch.  This is used for
     warnings crossing decls when branching to a case label.  */
  بنية c_spot_bindings *bindings;

  /* Whether the switch includes any break statements.  */
  منطقي break_stmt_seen_p;

  /* The next node on the stack.  */
  بنية c_switch *next;

  /* Remember whether the controlling expression had boolean type
     before integer promotions for the sake of -Wswitch-bool.  */
  منطقي bool_cond_p;
};

/* A stack of the currently active switch statements.  The innermost
   switch statement is on the top of the stack.  There is no need to
   mark the stack for garbage collection because it is only active
   during the processing of the body of a function, and we never
   collect at that point.  */

بنية c_switch *c_switch_مكدس;

/* Start a C switch statement, testing expression EXP.  Return the new
   SWITCH_STMT.  SWITCH_LOC is the location of the `switch'.
   SWITCH_COND_LOC is the location of the switch's condition.
   EXPLICIT_CAST_P is true if the expression EXP has an explicit cast.  */

شجرة
c_start_switch (location_t switch_loc,
		location_t switch_cond_loc,
		شجرة exp, منطقي explicit_cast_p, شجرة switch_name)
{
  شجرة orig_type = error_mark_عقدة;
  منطقي bool_cond_p = خطأ;
  بنية c_switch *cs;

  إذا (exp != error_mark_عقدة)
    {
      orig_type = شجرة_TYPE (exp);

      إذا (!INTEGRAL_TYPE_P (orig_type))
	{
	  إذا (orig_type != error_mark_عقدة)
	    {
	      error_at (switch_cond_loc, "switch quantity not an integer");
	      orig_type = error_mark_عقدة;
	    }
	  exp = integer_zero_عقدة;
	}
      وإلا
	{
	  شجرة type = TYPE_MAIN_VARIANT (orig_type);
	  شجرة e = exp;

	  /* Warn if the condition has boolean value.  */
	  طالما (شجرة_CODE (e) == COMPOUND_تعبير)
	    e = شجرة_OPERAND (e, 1);

	  إذا ((C_BOOLEAN_TYPE_P (type)
	       || truth_قيمة_p (شجرة_CODE (e)))
	      /* Explicit cast to int suppresses this warning.  */
	      && !(شجرة_CODE (type) == INTEGER_TYPE
		   && explicit_cast_p))
	    bool_cond_p = true;

	  إذا (!in_system_header_at (مدخل_location)
	      && (type == long_integer_type_عقدة
		  || type == long_unsigned_type_عقدة))
	    warning_at (switch_cond_loc,
			OPT_Wtraditional, "%<long%> switch expression not "
			"converted to %<int%> in ISO C");

	  exp = c_fully_fold (exp, خطأ, عدم);
	  exp = default_conversion (exp);

	  إذا (warn_sequence_point)
	    verify_sequence_points (exp);
	}
    }

  /* Add this new SWITCH_STMT to the stack.  */
  cs = XNEW (بنية c_switch);
  cs->switch_stmt = build_stmt (switch_loc, SWITCH_STMT, exp,
				NULL_شجرة, orig_type, NULL_شجرة, switch_name);
  cs->orig_type = orig_type;
  cs->cases = splay_شجرة_new (case_compare, عدم, عدم);
  cs->bindings = c_get_switch_bindings ();
  cs->break_stmt_seen_p = خطأ;
  cs->bool_cond_p = bool_cond_p;
  cs->next = c_switch_مكدس;
  c_switch_مكدس = cs;

  أرجع add_stmt (cs->switch_stmt);
}

/* Process a case label at location LOC, with attributes ATTRS.  */

شجرة
do_case (location_t loc, شجرة أدنى_قيمة, شجرة عالي_قيمة, شجرة attrs)
{
  شجرة label = NULL_شجرة;

  إذا (أدنى_قيمة && شجرة_CODE (أدنى_قيمة) != INTEGER_CST)
    {
      أدنى_قيمة = c_fully_fold (أدنى_قيمة, خطأ, عدم);
      إذا (شجرة_CODE (أدنى_قيمة) == INTEGER_CST)
	pedwarn (loc, OPT_Wpedantic,
		 "case label is not an integer constant expression");
    }

  إذا (عالي_قيمة && شجرة_CODE (عالي_قيمة) != INTEGER_CST)
    {
      عالي_قيمة = c_fully_fold (عالي_قيمة, خطأ, عدم);
      إذا (شجرة_CODE (عالي_قيمة) == INTEGER_CST)
	pedwarn (مدخل_location, OPT_Wpedantic,
		 "case label is not an integer constant expression");
    }

  إذا (c_switch_مكدس == عدم)
    {
      إذا (أدنى_قيمة)
	error_at (loc, "case label not within a switch statement");
      وإلا
	error_at (loc, "%<default%> label not within a switch statement");
      أرجع NULL_شجرة;
    }

  إذا (c_check_switch_jump_warnings (c_switch_مكدس->bindings,
				    تعبير_LOCATION (c_switch_مكدس->switch_stmt),
				    loc))
    أرجع NULL_شجرة;

  label = c_add_case_label (loc, c_switch_مكدس->cases,
			    SWITCH_STMT_COND (c_switch_مكدس->switch_stmt),
			    أدنى_قيمة, عالي_قيمة, attrs);
  إذا (label == error_mark_عقدة)
    label = NULL_شجرة;
  أرجع label;
}

/* Finish the switch statement.  TYPE is the original type of the
   controlling expression of the switch, or NULL_TREE.  */

فراغ
c_finish_switch (شجرة body, شجرة type)
{
  بنية c_switch *cs = c_switch_مكدس;
  location_t switch_location;

  SWITCH_STMT_BODY (cs->switch_stmt) = body;

  /* Emit warnings as needed.  */
  switch_location = تعبير_LOCATION (cs->switch_stmt);
  c_do_switch_warnings (cs->cases, switch_location,
			type ? type : SWITCH_STMT_TYPE (cs->switch_stmt),
			SWITCH_STMT_COND (cs->switch_stmt), cs->bool_cond_p);
  إذا (c_switch_covers_all_cases_p (cs->cases,
				   SWITCH_STMT_TYPE (cs->switch_stmt)))
    SWITCH_STMT_ALL_CASES_P (cs->switch_stmt) = 1;
  SWITCH_STMT_NO_BREAK_P (cs->switch_stmt) = !cs->break_stmt_seen_p;

  /* Pop the stack.  */
  c_switch_مكدس = cs->next;
  splay_شجرة_delete (cs->cases);
  c_release_switch_bindings (cs->bindings);
  XDELETE (cs);
}

/* Emit an if statement.  IF_LOCUS is the location of the 'if'.  COND,
   THEN_BLOCK and ELSE_BLOCK are expressions to be used; ELSE_BLOCK
   may be null.  */

فراغ
c_finish_if_stmt (location_t if_locus, شجرة cond, شجرة then_block,
		  شجرة else_block)
{
  شجرة stmt;

  stmt = build3 (COND_تعبير, void_type_عقدة, cond, then_block, else_block);
  SET_تعبير_LOCATION (stmt, if_locus);
  add_stmt (stmt);
}

شجرة
c_finish_bc_stmt (location_t loc, شجرة label, منطقي is_break, شجرة name)
{
  /* In switch statements break is sometimes stylistically used after
     a return statement.  This can lead to spurious warnings about
     control reaching the end of a non-void function when it is
     inlined.  Note that we are calling block_may_fallthru with
     language specific tree nodes; this works because
     block_may_fallthru returns true when given something it does not
     understand.  */
  منطقي skip = !block_may_fallthru (cur_stmt_list);

  إذا (is_break)
    بدل (in_statement & ~IN_NAMED_STMT)
      {
      حالة 0:
	error_at (loc, "break statement not within loop or switch");
	أرجع NULL_شجرة;
      حالة IN_OMP_BLOCK:
	error_at (loc, "invalid exit from OpenMP structured block");
	أرجع NULL_شجرة;
      حالة IN_OMP_FOR:
	error_at (loc, "break statement used with OpenMP for loop");
	أرجع NULL_شجرة;
      حالة IN_ITERATION_STMT:
      حالة IN_OBJC_FOREACH:
	اكسر;
      افتراضي:
	gcc_assert (in_statement & IN_SWITCH_STMT);
	c_switch_مكدس->break_stmt_seen_p = true;
	اكسر;
      }
  وإلا
    بدل (in_statement & ~(IN_SWITCH_STMT | IN_NAMED_STMT))
      {
      حالة 0:
	error_at (loc, "continue statement not within a loop");
	أرجع NULL_شجرة;
      حالة IN_OMP_BLOCK:
	error_at (loc, "invalid exit from OpenMP structured block");
	أرجع NULL_شجرة;
      حالة IN_ITERATION_STMT:
      حالة IN_OMP_FOR:
      حالة IN_OBJC_FOREACH:
	اكسر;
      افتراضي:
	gcc_unreachable ();
      }

  إذا (skip)
    أرجع NULL_شجرة;
  وإلا إذا ((in_statement & IN_OBJC_FOREACH)
	   && !(is_break && (in_statement & IN_SWITCH_STMT))
	   && name == NULL_شجرة)
    {
      /* The foreach expander produces low-level code using gotos instead
	 of a structured loop construct.  */
      gcc_assert (label);
      أرجع add_stmt (build_stmt (loc, GOTO_تعبير, label));
    }
  وإلا إذا (name && C_DECL_LOOP_NAME (name) && C_DECL_SWITCH_NAME (name))
    {
      label = DECL_CHAIN (name);
      إذا (!is_break)
	label = DECL_CHAIN (label);
      /* Foreach expander from some outer level.  */
      أرجع add_stmt (build_stmt (loc, GOTO_تعبير, label));
    }
  أرجع add_stmt (build_stmt (loc, is_break ? BREAK_STMT : CONTINUE_STMT,
			       name));
}

/* A helper routine for c_process_expr_stmt and c_finish_stmt_expr.  */

ساكن فراغ
emit_side_effect_warnings (location_t loc, شجرة تعبير)
{
  maybe_warn_nodiscard (loc, تعبير);
  إذا (!warn_unused_قيمة)
    أرجع;
  إذا (تعبير == error_mark_عقدة)
    ;
  وإلا إذا (!شجرة_SIDE_EFFECTS (تعبير))
    {
      إذا (!VOID_TYPE_P (شجرة_TYPE (تعبير))
	  && !warning_suppressed_p (تعبير, OPT_Wunused_قيمة))
	warning_at (loc, OPT_Wunused_قيمة, "statement with no effect");
    }
  وإلا إذا (شجرة_CODE (تعبير) == COMPOUND_تعبير)
    {
      شجرة r = تعبير;
      location_t cloc = loc;
      طالما (شجرة_CODE (r) == COMPOUND_تعبير)
	{
	  إذا (تعبير_HAS_LOCATION (r))
	    cloc = تعبير_LOCATION (r);
	  r = شجرة_OPERAND (r, 1);
	}
      إذا (!شجرة_SIDE_EFFECTS (r)
	  && !VOID_TYPE_P (شجرة_TYPE (r))
	  && !CONVERT_تعبير_P (r)
	  && !warning_suppressed_p (r, OPT_Wunused_قيمة)
	  && !warning_suppressed_p (تعبير, OPT_Wunused_قيمة))
	warning_at (cloc, OPT_Wunused_قيمة,
		    "right-hand operand of comma expression has no effect");
    }
  وإلا
    warn_if_unused_قيمة (تعبير, loc);
}

/* Process an expression as if it were a complete statement.  Emit
   diagnostics, but do not call ADD_STMT.  LOC is the location of the
   statement.  */

شجرة
c_process_تعبير_stmt (location_t loc, شجرة تعبير)
{
  شجرة exprv;

  إذا (!تعبير)
    أرجع NULL_شجرة;

  تعبير = c_fully_fold (تعبير, خطأ, عدم);

  إذا (warn_sequence_point)
    verify_sequence_points (تعبير);

  إذا (شجرة_TYPE (تعبير) != error_mark_عقدة
      && !COMPLETE_OR_VOID_TYPE_P (شجرة_TYPE (تعبير))
      && شجرة_CODE (شجرة_TYPE (تعبير)) != ARRAY_TYPE)
    error_at (loc, "expression statement has incomplete type");

  /* If we're not processing a statement expression, warn about unused values.
     Warnings for statement expressions will be emitted later, once we figure
     out which is the result.  */
  إذا (!STATEMENT_LIST_STMT_تعبير (cur_stmt_list)
      && (warn_unused_قيمة || warn_unused_result))
    emit_side_effect_warnings (تعبير_LOC_OR_LOC (تعبير, loc), تعبير);

  exprv = تعبير;
  طالما (شجرة_CODE (exprv) == COMPOUND_تعبير)
    exprv = شجرة_OPERAND (exprv, 1);
  طالما (CONVERT_تعبير_P (exprv))
    exprv = شجرة_OPERAND (exprv, 0);
  إذا (DECL_P (exprv)
      || handled_component_p (exprv)
      || شجرة_CODE (exprv) == ADDR_تعبير)
    mark_exp_read (exprv);

  /* If the expression is not of a type to which we cannot assign a line
     number, wrap the thing in a no-op NOP_EXPR.  */
  إذا (DECL_P (تعبير) || CONSTANT_CLASS_P (تعبير))
    {
      تعبير = build1 (NOP_تعبير, شجرة_TYPE (تعبير), تعبير);
      SET_تعبير_LOCATION (تعبير, loc);
    }

  أرجع تعبير;
}

/* Emit an expression as a statement.  LOC is the location of the
   expression.  */

شجرة
c_finish_تعبير_stmt (location_t loc, شجرة تعبير)
{
  إذا (تعبير)
    أرجع add_stmt (c_process_تعبير_stmt (loc, تعبير));
  وإلا
    أرجع عدم;
}

/* Do the opposite and emit a statement as an expression.  To begin,
   create a new binding level and return it.  */

شجرة
c_begin_stmt_تعبير (فراغ)
{
  شجرة ret;

  /* We must force a BLOCK for this level so that, if it is not expanded
     later, there is a way to turn off the entire subtree of blocks that
     are contained in it.  */
  keep_next_level ();
  ret = c_begin_compound_stmt (true);

  c_bindings_start_stmt_تعبير (c_switch_مكدس == عدم
			      ? عدم
			      : c_switch_مكدس->bindings);

  /* Mark the current statement list as belonging to a statement list.  */
  STATEMENT_LIST_STMT_تعبير (ret) = 1;

  أرجع ret;
}

/* LOC is the location of the compound statement to which this body
   belongs.  */

شجرة
c_finish_stmt_تعبير (location_t loc, شجرة body)
{
  شجرة last, type, tmp, val;
  شجرة *last_p;

  body = c_end_compound_stmt (loc, body, true);

  c_bindings_end_stmt_تعبير (c_switch_مكدس == عدم
			    ? عدم
			    : c_switch_مكدس->bindings);

  /* Locate the last statement in BODY.  See c_end_compound_stmt
     about always returning a BIND_EXPR.  */
  last_p = &BIND_تعبير_BODY (body);
  last = BIND_تعبير_BODY (body);

 continue_searching:
  إذا (شجرة_CODE (last) == STATEMENT_LIST)
    {
      شجرة_stmt_iterator l = tsi_last (last);

      طالما (!tsi_end_p (l) && شجرة_CODE (tsi_stmt (l)) == DEBUG_BEGIN_STMT)
	tsi_prev (&l);

      /* This can happen with degenerate cases like ({ }).  No value.  */
      إذا (tsi_end_p (l))
	أرجع body;

      /* If we're supposed to generate side effects warnings, process
	 all of the statements except the last.  */
      إذا (warn_unused_قيمة || warn_unused_result)
	{
	  لكل (شجرة_stmt_iterator i = tsi_start (last);
	       tsi_stmt (i) != tsi_stmt (l); tsi_next (&i))
	    {
	      location_t tloc;
	      شجرة t = tsi_stmt (i);

	      tloc = تعبير_HAS_LOCATION (t) ? تعبير_LOCATION (t) : loc;
	      emit_side_effect_warnings (tloc, t);
	    }
	}
      last_p = tsi_stmt_ptr (l);
      last = *last_p;
    }

  /* If the end of the list is exception related, then the list was split
     by a call to push_cleanup.  Continue searching.  */
  إذا (شجرة_CODE (last) == TRY_FINALLY_تعبير
      || شجرة_CODE (last) == TRY_CATCH_تعبير)
    {
      last_p = &شجرة_OPERAND (last, 0);
      last = *last_p;
      اذهب continue_searching;
    }

  إذا (last == error_mark_عقدة)
    أرجع last;

  /* In the case that the BIND_EXPR is not necessary, return the
     expression out from inside it.  */
  إذا ((last == BIND_تعبير_BODY (body)
       /* Skip nested debug stmts.  */
       || last == تعبير_first (BIND_تعبير_BODY (body)))
      && BIND_تعبير_VARS (body) == عدم)
    {
      /* Even if this looks constant, do not allow it in a constant
	 expression.  */
      last = c_wrap_maybe_const (last, true);
      /* Do not warn if the return value of a statement expression is
	 unused.  */
      suppress_warning (last, OPT_Wunused);
      أرجع last;
    }

  /* Extract the type of said expression.  */
  type = شجرة_TYPE (last);

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
  val = last;
  إذا (شجرة_CODE (val) == NOP_تعبير
      && شجرة_TYPE (val) == شجرة_TYPE (شجرة_OPERAND (val, 0)))
    val = شجرة_OPERAND (val, 0);

  *last_p = build2 (MODIFY_تعبير, void_type_عقدة, tmp, val);
  SET_تعبير_LOCATION (*last_p, تعبير_LOCATION (last));

  {
    شجرة t = build4 (TARGET_تعبير, type, tmp, body, NULL_شجرة, NULL_شجرة);
    SET_تعبير_LOCATION (t, loc);
    أرجع t;
  }
}

/* Begin and end compound statements.  This is as simple as pushing
   and popping new statement lists from the tree.  */

شجرة
c_begin_compound_stmt (منطقي do_scope)
{
  شجرة stmt = ادفع_stmt_list ();
  إذا (do_scope)
    ادفع_scope ();
  أرجع stmt;
}

/* End a compound statement.  STMT is the statement.  LOC is the
   location of the compound statement-- this is usually the location
   of the opening brace.  */

شجرة
c_end_compound_stmt (location_t loc, شجرة stmt, منطقي do_scope)
{
  شجرة block = عدم;

  إذا (do_scope)
    {
      إذا (c_dialect_objc ())
	objc_clear_super_receiver ();
      block = اسحب_scope ();
    }

  stmt = اسحب_stmt_list (stmt);
  stmt = c_build_bind_تعبير (loc, block, stmt);

  /* If this compound statement is nested immediately inside a statement
     expression, then force a BIND_EXPR to be created.  Otherwise we'll
     do the wrong thing for ({ { 1; } }) or ({ 1; { } }).  In particular,
     STATEMENT_LISTs merge, and thus we can lose track of what statement
     was really last.  */
  إذا (building_stmt_list_p ()
      && STATEMENT_LIST_STMT_تعبير (cur_stmt_list)
      && شجرة_CODE (stmt) != BIND_تعبير)
    {
      stmt = build3 (BIND_تعبير, void_type_عقدة, عدم, stmt, عدم);
      شجرة_SIDE_EFFECTS (stmt) = 1;
      SET_تعبير_LOCATION (stmt, loc);
    }

  أرجع stmt;
}

/* Queue a cleanup.  CLEANUP is an expression/statement to be executed
   when the current scope is exited.  EH_ONLY is true when this is not
   meant to apply to normal control flow transfer.  */

فراغ
ادفع_cleanup (شجرة decl, شجرة cleanup, منطقي eh_only)
{
  تعداد شجرة_code code;
  شجرة stmt, list;
  منطقي stmt_تعبير;

  code = eh_only ? TRY_CATCH_تعبير : TRY_FINALLY_تعبير;
  stmt = build_stmt (DECL_SOURCE_LOCATION (decl), code, عدم, cleanup);
  add_stmt (stmt);
  stmt_تعبير = STATEMENT_LIST_STMT_تعبير (cur_stmt_list);
  list = ادفع_stmt_list ();
  شجرة_OPERAND (stmt, 0) = list;
  STATEMENT_LIST_STMT_تعبير (list) = stmt_تعبير;
}

/* Build a vector comparison of ARG0 and ARG1 using CODE opcode
   into a value of TYPE type.  Comparison is done via VEC_COND_EXPR.  */

ساكن شجرة
build_vec_cmp (شجرة_code code, شجرة type,
	       شجرة arg0, شجرة arg1)
{
  شجرة zero_vec = build_zero_cst (type);
  شجرة minus_one_vec = build_minus_one_cst (type);
  شجرة cmp_type = truth_type_for (شجرة_TYPE (arg0));
  شجرة cmp = build2 (code, cmp_type, arg0, arg1);
  أرجع build3 (VEC_COND_تعبير, type, cmp, minus_one_vec, zero_vec);
}

/* Possibly warn about an address of OP never being NULL in a comparison
   operation CODE involving null.  */

ساكن فراغ
maybe_warn_for_null_address (location_t loc, شجرة op, شجرة_code code)
{
  /* Prevent warnings issued for macro expansion.  */
  إذا (!warn_address
      || warning_suppressed_p (op, OPT_Waddress)
      || from_macro_expansion_at (loc))
    أرجع;

  إذا (شجرة_CODE (op) == NOP_تعبير)
    {
      /* Allow casts to intptr_t to suppress the warning.  */
      شجرة type = شجرة_TYPE (op);
      إذا (شجرة_CODE (type) == INTEGER_TYPE)
	أرجع;
      op = شجرة_OPERAND (op, 0);
    }

  إذا (شجرة_CODE (op) == POINTER_PLUS_تعبير)
    {
      /* Allow a cast to void* to suppress the warning.  */
      شجرة type = شجرة_TYPE (شجرة_TYPE (op));
      إذا (VOID_TYPE_P (type))
	أرجع;

      /* Adding any value to a null pointer, including zero, is undefined
	 in C.  This includes the expression &p[0] where p is the null
	 pointer, although &p[0] will have been folded to p by this point
	 and so not diagnosed.  */
      إذا (code == EQ_تعبير)
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

  إذا (شجرة_CODE (op) != ADDR_تعبير)
    أرجع;

  op = شجرة_OPERAND (op, 0);

  إذا (شجرة_CODE (op) == IMAGPART_تعبير
      || شجرة_CODE (op) == REALPART_تعبير)
    {
      /* The address of either complex part may not be null.  */
      إذا (code == EQ_تعبير)
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
      إذا (شجرة_CODE (op) == COMPONENT_REF)
	{
	  /* Get the member (its address is never null).  */
	  op = شجرة_OPERAND (op, 1);
	  اكسر;
	}

      /* Get the outer array/object to refer to in the warning.  */
      op = شجرة_OPERAND (op, 0);
      deref = true;
    }

  إذا ((!deref && !decl_with_nonnull_addr_p (op))
      || from_macro_expansion_at (loc))
    أرجع;

  منطقي w;
  إذا (code == EQ_تعبير)
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
    inform (DECL_SOURCE_LOCATION (op), "%qD declared here", op);
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

شجرة
build_ثنائي_op (location_t location, تعداد شجرة_code code,
		 شجرة orig_op0, شجرة orig_op1, منطقي convert_p)
{
  شجرة type0, type1, orig_type0, orig_type1;
  شجرة eptype;
  تعداد شجرة_code code0, code1;
  شجرة op0, op1;
  شجرة ret = error_mark_عقدة;
  ثابت حرف *invalid_op_diag;
  منطقي op0_int_operands, op1_int_operands;
  منطقي int_const, int_const_or_overflow, int_operands;

  /* Expression code to give to the expression when it is built.
     Normally this is CODE, which is what the caller asked for,
     but in some special cases we change it.  */
  تعداد شجرة_code resultcode = code;

  /* Data type in which the computation is to be performed.
     In the simplest cases this is the common type of the arguments.  */
  شجرة result_type = عدم;

  /* When the computation is in excess precision, the type of the
     final EXCESS_PRECISION_EXPR.  */
  شجرة semantic_result_type = عدم;

  /* Nonzero means operands have already been type-converted
     in whatever way is necessary.
     Zero means they need to be converted to RESULT_TYPE.  */
  صحيح converted = 0;

  /* Nonzero means create the expression with this type, rather than
     RESULT_TYPE.  */
  شجرة build_type = NULL_شجرة;

  /* Nonzero means after finally constructing the expression
     convert it to this type.  */
  شجرة final_type = NULL_شجرة;

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
  صحيح short_shift = 0;

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
  منطقي doing_shift = خطأ;

  /* Tree holding instrumentation expression.  */
  شجرة instrument_تعبير = عدم;

  إذا (location == UNKNOWN_LOCATION)
    location = مدخل_location;

  op0 = orig_op0;
  op1 = orig_op1;

  op0_int_operands = تعبير_INT_CONST_OPERANDS (orig_op0);
  إذا (op0_int_operands)
    op0 = remove_c_maybe_const_تعبير (op0);
  op1_int_operands = تعبير_INT_CONST_OPERANDS (orig_op1);
  إذا (op1_int_operands)
    op1 = remove_c_maybe_const_تعبير (op1);
  int_operands = (op0_int_operands && op1_int_operands);
  إذا (int_operands)
    {
      int_const_or_overflow = (شجرة_CODE (orig_op0) == INTEGER_CST
			       && شجرة_CODE (orig_op1) == INTEGER_CST);
      int_const = (int_const_or_overflow
		   && !شجرة_OVERFLOW (orig_op0)
		   && !شجرة_OVERFLOW (orig_op1));
    }
  وإلا
    int_const = int_const_or_overflow = خطأ;

  /* Do not apply default conversion in mixed vector/scalar expression.  */
  إذا (convert_p
      && VECTOR_TYPE_P (شجرة_TYPE (op0)) == VECTOR_TYPE_P (شجرة_TYPE (op1)))
    {
      op0 = default_conversion (op0);
      op1 = default_conversion (op1);
    }

  orig_type0 = type0 = شجرة_TYPE (op0);

  orig_type1 = type1 = شجرة_TYPE (op1);

  /* The expression codes of the data types of the arguments tell us
     whether the arguments are integers, floating, pointers, etc.  */
  code0 = شجرة_CODE (type0);
  code1 = شجرة_CODE (type1);

  /* Strip NON_LVALUE_EXPRs, etc., since we aren't using as an lvalue.  */
  STRIP_TYPE_NOPS (op0);
  STRIP_TYPE_NOPS (op1);

  /* If an error was already reported for one of the arguments,
     avoid reporting another error.  */

  إذا (code0 == ERROR_MARK || code1 == ERROR_MARK)
    أرجع error_mark_عقدة;

  إذا (code0 == POINTER_TYPE
      && reject_gcc_builtin (op0, تعبير_LOCATION (orig_op0)))
    أرجع error_mark_عقدة;

  إذا (code1 == POINTER_TYPE
      && reject_gcc_builtin (op1, تعبير_LOCATION (orig_op1)))
    أرجع error_mark_عقدة;

  إذا ((invalid_op_diag
       = targetm.invalid_ثنائي_op (code, type0, type1)))
    {
      error_at (location, invalid_op_diag);
      أرجع error_mark_عقدة;
    }

  بدل (code)
    {
    حالة PLUS_تعبير:
    حالة MINUS_تعبير:
    حالة MULT_تعبير:
    حالة TRUNC_DIV_تعبير:
    حالة CEIL_DIV_تعبير:
    حالة FLOOR_DIV_تعبير:
    حالة ROUND_DIV_تعبير:
    حالة EXACT_DIV_تعبير:
      may_need_excess_precision = true;
      اكسر;

    حالة EQ_تعبير:
    حالة NE_تعبير:
    حالة LE_تعبير:
    حالة GE_تعبير:
    حالة LT_تعبير:
    حالة GT_تعبير:
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
  إذا (شجرة_CODE (op0) == EXCESS_PRECISION_تعبير)
    {
      op0 = شجرة_OPERAND (op0, 0);
      type0 = شجرة_TYPE (op0);
    }
  وإلا إذا (may_need_excess_precision
	   && (eptype = excess_precision_type (type0)) != NULL_شجرة)
    {
      type0 = eptype;
      op0 = convert (eptype, op0);
    }
  إذا (شجرة_CODE (op1) == EXCESS_PRECISION_تعبير)
    {
      op1 = شجرة_OPERAND (op1, 0);
      type1 = شجرة_TYPE (op1);
    }
  وإلا إذا (may_need_excess_precision
	   && (eptype = excess_precision_type (type1)) != NULL_شجرة)
    {
      type1 = eptype;
      op1 = convert (eptype, op1);
    }

  objc_ok = objc_compare_types (type0, type1, -3, NULL_شجرة);

  /* In case when one of the operands of the binary operation is
     a vector and another is a scalar -- convert scalar to vector.  */
  إذا ((gnu_vector_type_p (type0) && code1 != VECTOR_TYPE)
      || (gnu_vector_type_p (type1) && code0 != VECTOR_TYPE))
    {
      تعداد stv_conv convert_flag = scalar_to_vector (location, code, orig_op0,
						     orig_op1, true);

      بدل (convert_flag)
	{
	  حالة stv_error:
	    أرجع error_mark_عقدة;
	  حالة stv_firstarg:
	    {
              منطقي maybe_const = true;
              شجرة sc;
              sc = c_fully_fold (op0, خطأ, &maybe_const);
              sc = save_تعبير (sc);
              sc = convert (شجرة_TYPE (type1), sc);
              op0 = build_vector_from_val (type1, sc);
              إذا (!maybe_const)
                op0 = c_wrap_maybe_const (op0, true);
              orig_type0 = type0 = شجرة_TYPE (op0);
              code0 = شجرة_CODE (type0);
              converted = 1;
              اكسر;
	    }
	  حالة stv_secondarg:
	    {
	      منطقي maybe_const = true;
	      شجرة sc;
	      sc = c_fully_fold (op1, خطأ, &maybe_const);
	      sc = save_تعبير (sc);
	      sc = convert (شجرة_TYPE (type0), sc);
	      op1 = build_vector_from_val (type0, sc);
	      إذا (!maybe_const)
		op1 = c_wrap_maybe_const (op1, true);
	      orig_type1 = type1 = شجرة_TYPE (op1);
	      code1 = شجرة_CODE (type1);
	      converted = 1;
	      اكسر;
	    }
	  افتراضي:
	    اكسر;
	}
    }

  بدل (code)
    {
    حالة PLUS_تعبير:
      /* Handle the pointer + int case.  */
      إذا (code0 == POINTER_TYPE
	  && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  ret = pointer_int_sum (location, PLUS_تعبير, op0, op1);
	  اذهب return_build_ثنائي_op;
	}
      وإلا إذا (code1 == POINTER_TYPE
	       && (code0 == INTEGER_TYPE || code0 == BITINT_TYPE))
	{
	  ret = pointer_int_sum (location, PLUS_تعبير, op1, op0);
	  اذهب return_build_ثنائي_op;
	}
      وإلا
	common = 1;
      اكسر;

    حالة MINUS_تعبير:
      /* Subtraction of two similar pointers.
	 We must subtract them as integers, then divide by object size.  */
      إذا (code0 == POINTER_TYPE && code1 == POINTER_TYPE
	  && comp_target_types (location, type0, type1))
	{
	  ret = pointer_diff (location, op0, op1, &instrument_تعبير);
	  اذهب return_build_ثنائي_op;
	}
      /* Handle pointer minus int.  Just like pointer plus int.  */
      وإلا إذا (code0 == POINTER_TYPE
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  ret = pointer_int_sum (location, MINUS_تعبير, op0, op1);
	  اذهب return_build_ثنائي_op;
	}
      وإلا
	common = 1;
      اكسر;

    حالة MULT_تعبير:
      common = 1;
      اكسر;

    حالة TRUNC_DIV_تعبير:
    حالة CEIL_DIV_تعبير:
    حالة FLOOR_DIV_تعبير:
    حالة ROUND_DIV_تعبير:
    حالة EXACT_DIV_تعبير:
      doing_div_or_mod = true;
      warn_for_div_by_zero (location, op1);

      إذا ((code0 == INTEGER_TYPE || code0 == REAL_TYPE
	   || code0 == FIXED_POINT_TYPE || code0 == BITINT_TYPE
	   || code0 == COMPLEX_TYPE
	   || gnu_vector_type_p (type0))
	  && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	      || code1 == FIXED_POINT_TYPE || code1 == BITINT_TYPE
	      || code1 == COMPLEX_TYPE
	      || gnu_vector_type_p (type1)))
	{
	  تعداد شجرة_code tcode0 = code0, tcode1 = code1;

	  إذا (code0 == COMPLEX_TYPE || code0 == VECTOR_TYPE)
	    tcode0 = شجرة_CODE (شجرة_TYPE (شجرة_TYPE (op0)));
	  إذا (code1 == COMPLEX_TYPE || code1 == VECTOR_TYPE)
	    tcode1 = شجرة_CODE (شجرة_TYPE (شجرة_TYPE (op1)));

	  إذا (!(((tcode0 == INTEGER_TYPE || tcode0 == BITINT_TYPE
		  || (tcode0 == ENUMERAL_TYPE && code0 == VECTOR_TYPE))
		 && (tcode1 == INTEGER_TYPE || tcode1 == BITINT_TYPE
		     || (tcode1 == ENUMERAL_TYPE && code1 == VECTOR_TYPE)))
		|| (tcode0 == FIXED_POINT_TYPE && tcode1 == FIXED_POINT_TYPE)))
	    resultcode = RDIV_تعبير;
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

    حالة BIT_AND_تعبير:
    حالة BIT_IOR_تعبير:
    حالة BIT_XOR_تعبير:
      إذا ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	shorten = -1;
      /* Allow vector types which are not floating point types.   */
      وإلا إذا (gnu_vector_type_p (type0)
	       && gnu_vector_type_p (type1)
	       && !VECTOR_FLOAT_TYPE_P (type0)
	       && !VECTOR_FLOAT_TYPE_P (type1))
	common = 1;
      اكسر;

    حالة TRUNC_MOD_تعبير:
    حالة FLOOR_MOD_تعبير:
      doing_div_or_mod = true;
      warn_for_div_by_zero (location, op1);

      إذا (gnu_vector_type_p (type0)
	  && gnu_vector_type_p (type1)
	  && شجرة_CODE (شجرة_TYPE (type0)) == INTEGER_TYPE
	  && شجرة_CODE (شجرة_TYPE (type1)) == INTEGER_TYPE)
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

    حالة TRUTH_ANDIF_تعبير:
    حالة TRUTH_ORIF_تعبير:
    حالة TRUTH_AND_تعبير:
    حالة TRUTH_OR_تعبير:
    حالة TRUTH_XOR_تعبير:
      إذا ((code0 == INTEGER_TYPE || code0 == POINTER_TYPE
	   || code0 == REAL_TYPE || code0 == COMPLEX_TYPE
	   || code0 == FIXED_POINT_TYPE || code0 == NULLPTR_TYPE
	   || code0 == BITINT_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == POINTER_TYPE
	      || code1 == REAL_TYPE || code1 == COMPLEX_TYPE
	      || code1 == FIXED_POINT_TYPE || code1 == NULLPTR_TYPE
	      || code1 == BITINT_TYPE))
	{
	  /* Result of these operations is always an int,
	     but that does not mean the operands should be
	     converted to ints!  */
	  result_type = integer_type_عقدة;
	  إذا (op0_int_operands)
	    {
	      op0 = c_objc_common_truthvalue_conversion (location, orig_op0);
	      op0 = remove_c_maybe_const_تعبير (op0);
	    }
	  وإلا
	    op0 = c_objc_common_truthvalue_conversion (location, op0);
	  إذا (op1_int_operands)
	    {
	      op1 = c_objc_common_truthvalue_conversion (location, orig_op1);
	      op1 = remove_c_maybe_const_تعبير (op1);
	    }
	  وإلا
	    op1 = c_objc_common_truthvalue_conversion (location, op1);
	  converted = 1;
	  boolean_op = true;
	}
      إذا (code == TRUTH_ANDIF_تعبير)
	{
	  int_const_or_overflow = (int_operands
				   && شجرة_CODE (orig_op0) == INTEGER_CST
				   && (op0 == truthvalue_false_عقدة
				       || شجرة_CODE (orig_op1) == INTEGER_CST));
	  int_const = (int_const_or_overflow
		       && !شجرة_OVERFLOW (orig_op0)
		       && (op0 == truthvalue_false_عقدة
			   || !شجرة_OVERFLOW (orig_op1)));
	}
      وإلا إذا (code == TRUTH_ORIF_تعبير)
	{
	  int_const_or_overflow = (int_operands
				   && شجرة_CODE (orig_op0) == INTEGER_CST
				   && (op0 == truthvalue_true_عقدة
				       || شجرة_CODE (orig_op1) == INTEGER_CST));
	  int_const = (int_const_or_overflow
		       && !شجرة_OVERFLOW (orig_op0)
		       && (op0 == truthvalue_true_عقدة
			   || !شجرة_OVERFLOW (orig_op1)));
	}
      اكسر;

      /* Shift operations: result has same type as first operand;
	 always convert second operand to int.
	 Also set SHORT_SHIFT if shifting rightward.  */

    حالة RSHIFT_تعبير:
      إذا (gnu_vector_type_p (type0)
	  && gnu_vector_type_p (type1)
	  && شجرة_CODE (شجرة_TYPE (type0)) == INTEGER_TYPE
	  && شجرة_CODE (شجرة_TYPE (type1)) == INTEGER_TYPE
	  && known_eq (TYPE_VECTOR_SUBPARTS (type0),
		       TYPE_VECTOR_SUBPARTS (type1)))
	{
	  result_type = type0;
	  converted = 1;
	}
      وإلا إذا ((code0 == INTEGER_TYPE || code0 == FIXED_POINT_TYPE
		|| code0 == BITINT_TYPE
		|| (gnu_vector_type_p (type0)
		    && شجرة_CODE (شجرة_TYPE (type0)) == INTEGER_TYPE))
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  doing_shift = true;
	  إذا (شجرة_CODE (op1) == INTEGER_CST)
	    {
	      إذا (شجرة_int_cst_sgn (op1) < 0)
		{
		  int_const = خطأ;
		  إذا (c_inhibit_evaluation_warnings == 0)
		    warning_at (location, OPT_Wshift_عدد_negative,
				"right shift count is negative");
		}
	      وإلا إذا (code0 == VECTOR_TYPE)
		{
		  إذا (compare_شجرة_int (op1,
					TYPE_PRECISION (شجرة_TYPE (type0)))
		      >= 0)
		    {
		      int_const = خطأ;
		      إذا (c_inhibit_evaluation_warnings == 0)
			warning_at (location, OPT_Wshift_عدد_overflow,
				    "right shift count >= width of vector element");
		    }
		}
	      وإلا
		{
		  إذا (!integer_zerop (op1))
		    short_shift = 1;

		  إذا (compare_شجرة_int (op1, TYPE_PRECISION (type0)) >= 0)
		    {
		      int_const = خطأ;
		      إذا (c_inhibit_evaluation_warnings == 0)
			warning_at (location, OPT_Wshift_عدد_overflow,
				    "right shift count >= width of type");
		    }
		}
	    }

	  /* Use the type of the value to be shifted.  */
	  result_type = type0;
	  /* Avoid converting op1 to result_type later.  */
	  converted = 1;
	}
      اكسر;

    حالة LSHIFT_تعبير:
      إذا (gnu_vector_type_p (type0)
	  && gnu_vector_type_p (type1)
	  && شجرة_CODE (شجرة_TYPE (type0)) == INTEGER_TYPE
	  && شجرة_CODE (شجرة_TYPE (type1)) == INTEGER_TYPE
	  && known_eq (TYPE_VECTOR_SUBPARTS (type0),
		       TYPE_VECTOR_SUBPARTS (type1)))
	{
	  result_type = type0;
	  converted = 1;
	}
      وإلا إذا ((code0 == INTEGER_TYPE || code0 == FIXED_POINT_TYPE
		|| code0 == BITINT_TYPE
		|| (gnu_vector_type_p (type0)
		    && شجرة_CODE (شجرة_TYPE (type0)) == INTEGER_TYPE))
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  doing_shift = true;
	  إذا (شجرة_CODE (op0) == INTEGER_CST
	      && شجرة_int_cst_sgn (op0) < 0
	      && !TYPE_OVERFLOW_WRAPS (type0))
	    {
	      /* Don't reject a left shift of a negative value in a context
		 where a constant expression is needed in C90.  */
	      إذا (flag_isoc99)
		int_const = خطأ;
	      إذا (c_inhibit_evaluation_warnings == 0)
		warning_at (location, OPT_Wshift_negative_قيمة,
			    "left shift of negative value");
	    }
	  إذا (شجرة_CODE (op1) == INTEGER_CST)
	    {
	      إذا (شجرة_int_cst_sgn (op1) < 0)
		{
		  int_const = خطأ;
		  إذا (c_inhibit_evaluation_warnings == 0)
		    warning_at (location, OPT_Wshift_عدد_negative,
				"left shift count is negative");
		}
	      وإلا إذا (code0 == VECTOR_TYPE)
		{
		  إذا (compare_شجرة_int (op1,
					TYPE_PRECISION (شجرة_TYPE (type0)))
		      >= 0)
		    {
		      int_const = خطأ;
		      إذا (c_inhibit_evaluation_warnings == 0)
			warning_at (location, OPT_Wshift_عدد_overflow,
				    "left shift count >= width of vector element");
		    }
		}
	      وإلا إذا (compare_شجرة_int (op1, TYPE_PRECISION (type0)) >= 0)
		{
		  int_const = خطأ;
		  إذا (c_inhibit_evaluation_warnings == 0)
		    warning_at (location, OPT_Wshift_عدد_overflow,
				"left shift count >= width of type");
		}
	      وإلا إذا (شجرة_CODE (op0) == INTEGER_CST
		       && maybe_warn_shift_overflow (location, op0, op1)
		       && flag_isoc99)
		int_const = خطأ;
	    }

	  /* Use the type of the value to be shifted.  */
	  result_type = type0;
	  /* Avoid converting op1 to result_type later.  */
	  converted = 1;
	}
      اكسر;

    حالة EQ_تعبير:
    حالة NE_تعبير:
      إذا (gnu_vector_type_p (type0) && gnu_vector_type_p (type1))
        {
          شجرة intt;
	  إذا (!vector_types_compatible_elements_p (type0, type1))
            {
              error_at (location, "comparing vectors with different "
                                  "element types");
              أرجع error_mark_عقدة;
            }

	  إذا (maybe_ne (TYPE_VECTOR_SUBPARTS (type0),
			TYPE_VECTOR_SUBPARTS (type1)))
            {
              error_at (location, "comparing vectors with different "
                                  "number of elements");
              أرجع error_mark_عقدة;
            }

	  /* It's not precisely specified how the usual arithmetic
	     conversions apply to the vector types.  Here, we use
	     the unsigned type if one of the operands is signed and
	     the other one is unsigned.  */
	  إذا (TYPE_UNSIGNED (type0) != TYPE_UNSIGNED (type1))
	    {
	      إذا (!TYPE_UNSIGNED (type0))
		op0 = build1 (VIEW_CONVERT_تعبير, type1, op0);
	      وإلا
		op1 = build1 (VIEW_CONVERT_تعبير, type0, op1);
	      warning_at (location, OPT_Wsign_compare, "comparison between "
			  "types %qT and %qT", type0, type1);
	    }

          /* Always construct signed integer vector type.  */
	  إذا (VECTOR_BOOLEAN_TYPE_P (type0) && VECTOR_BOOLEAN_TYPE_P (type1))
	    result_type = type0;
	  وإلا
	    {
	      auto nelts = TYPE_VECTOR_SUBPARTS (type0);

	      intt = c_common_type_for_size (GET_MODE_BITSIZE
					     (SCALAR_TYPE_MODE
						(شجرة_TYPE (type0))), 0);
	      إذا (!intt)
		{
		  error_at (location, "could not find an integer type "
				      "of the same size as %qT",
			    شجرة_TYPE (type0));
		  أرجع error_mark_عقدة;
		}
	      result_type = build_opaque_vector_type (intt, nelts);
	    }
          converted = 1;
	  ret = build_vec_cmp (resultcode, result_type, op0, op1);
	  اذهب return_build_ثنائي_op;
        }
      إذا (FLOAT_TYPE_P (type0) || FLOAT_TYPE_P (type1))
	warning_at (location,
		    OPT_Wfloat_equal,
		    "comparing floating-point with %<==%> or %<!=%> is unsafe");
      /* Result of comparison is always int,
	 but don't convert the args to int!  */
      build_type = integer_type_عقدة;
      إذا ((code0 == INTEGER_TYPE || code0 == REAL_TYPE || code0 == BITINT_TYPE
	   || code0 == FIXED_POINT_TYPE || code0 == COMPLEX_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	      || code1 == BITINT_TYPE
	      || code1 == FIXED_POINT_TYPE || code1 == COMPLEX_TYPE))
	short_compare = 1;
      وإلا إذا (code0 == POINTER_TYPE
	       && (code1 == NULLPTR_TYPE
		   || null_pointer_constant_p (orig_op1)))
	{
	  maybe_warn_for_null_address (location, op0, code);
	  result_type = type0;
	}
      وإلا إذا (code1 == POINTER_TYPE
	       && (code0 == NULLPTR_TYPE
		   || null_pointer_constant_p (orig_op0)))
	{
	  maybe_warn_for_null_address (location, op1, code);
	  result_type = type1;
	}
      وإلا إذا (code0 == POINTER_TYPE && code1 == POINTER_TYPE)
	{
	  شجرة tt0 = شجرة_TYPE (type0);
	  شجرة tt1 = شجرة_TYPE (type1);
	  addr_space_t as0 = TYPE_ADDR_SPACE (tt0);
	  addr_space_t as1 = TYPE_ADDR_SPACE (tt1);
	  addr_space_t as_common = ADDR_SPACE_GENERIC;

	  /* Anything compares with void *.  void * compares with anything.
	     Otherwise, the targets must be compatible
	     and both must be object or both incomplete.  */
	  إذا (comp_target_types (location, type0, type1))
	    result_type = common_pointer_type (type0, type1, NULL_شجرة);
	  وإلا إذا (!addr_space_superset (as0, as1, &as_common))
	    {
	      error_at (location, "comparison of pointers to "
			"disjoint address spaces");
	      أرجع error_mark_عقدة;
	    }
	  وإلا إذا (VOID_TYPE_P (tt0) && !TYPE_ATOMIC (tt0))
	    {
	      إذا (pedantic && شجرة_CODE (tt1) == FUNCTION_TYPE)
		pedwarn (location, OPT_Wpedantic, "ISO C forbids "
			 "comparison of %<void *%> with function pointer");
	    }
	  وإلا إذا (VOID_TYPE_P (tt1) && !TYPE_ATOMIC (tt1))
	    {
	      إذا (pedantic && شجرة_CODE (tt0) == FUNCTION_TYPE)
		pedwarn (location, OPT_Wpedantic, "ISO C forbids "
			 "comparison of %<void *%> with function pointer");
	    }
	  وإلا
	    /* Avoid warning about the volatile ObjC EH puts on decls.  */
	    إذا (!objc_ok)
	      pedwarn (location, OPT_Wcompare_distinct_pointer_types,
		       "comparison of distinct pointer types lacks a cast");

	  إذا (result_type == NULL_شجرة)
	    {
	      صحيح qual = ENCODE_QUAL_ADDR_SPACE (as_common);
	      result_type = c_build_pointer_type
			      (c_build_qualified_type (void_type_عقدة, qual));
	    }
	}
      وإلا إذا (code0 == POINTER_TYPE
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  result_type = type0;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}
      وإلا إذا ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	       && code1 == POINTER_TYPE)
	{
	  result_type = type1;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}
      /* 6.5.9: One of the following shall hold:
	 -- both operands have type nullptr_t;  */
      وإلا إذا (code0 == NULLPTR_TYPE && code1 == NULLPTR_TYPE)
	{
	  result_type = nullptr_type_عقدة;
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
      وإلا إذا (code0 == NULLPTR_TYPE && null_pointer_constant_p (orig_op1))
	result_type = (INTEGRAL_TYPE_P (type1)
		       ? c_build_pointer_type (type1) : type1);
      وإلا إذا (code1 == NULLPTR_TYPE && null_pointer_constant_p (orig_op0))
	result_type = (INTEGRAL_TYPE_P (type0)
		       ? c_build_pointer_type (type0) : type0);
      إذا ((C_BOOLEAN_TYPE_P (شجرة_TYPE (orig_op0))
	   || truth_قيمة_p (شجرة_CODE (orig_op0)))
	  ^ (C_BOOLEAN_TYPE_P (شجرة_TYPE (orig_op1))
	     || truth_قيمة_p (شجرة_CODE (orig_op1))))
	maybe_warn_bool_compare (location, code, orig_op0, orig_op1);
      اكسر;

    حالة LE_تعبير:
    حالة GE_تعبير:
    حالة LT_تعبير:
    حالة GT_تعبير:
      إذا (gnu_vector_type_p (type0) && gnu_vector_type_p (type1))
        {
          شجرة intt;
	  إذا (!vector_types_compatible_elements_p (type0, type1))
            {
              error_at (location, "comparing vectors with different "
                                  "element types");
              أرجع error_mark_عقدة;
            }

	  إذا (maybe_ne (TYPE_VECTOR_SUBPARTS (type0),
			TYPE_VECTOR_SUBPARTS (type1)))
            {
              error_at (location, "comparing vectors with different "
                                  "number of elements");
              أرجع error_mark_عقدة;
            }

	  /* It's not precisely specified how the usual arithmetic
	     conversions apply to the vector types.  Here, we use
	     the unsigned type if one of the operands is signed and
	     the other one is unsigned.  */
	  إذا (TYPE_UNSIGNED (type0) != TYPE_UNSIGNED (type1))
	    {
	      إذا (!TYPE_UNSIGNED (type0))
		op0 = build1 (VIEW_CONVERT_تعبير, type1, op0);
	      وإلا
		op1 = build1 (VIEW_CONVERT_تعبير, type0, op1);
	      warning_at (location, OPT_Wsign_compare, "comparison between "
			  "types %qT and %qT", type0, type1);
	    }

          /* Always construct signed integer vector type.  */
          intt = c_common_type_for_size (GET_MODE_BITSIZE
					 (SCALAR_TYPE_MODE
					  (شجرة_TYPE (type0))), 0);
	  إذا (!intt)
	    {
	      error_at (location, "could not find an integer type "
				  "of the same size as %qT",
			شجرة_TYPE (type0));
	      أرجع error_mark_عقدة;
	    }
          result_type = build_opaque_vector_type (intt,
						  TYPE_VECTOR_SUBPARTS (type0));
          converted = 1;
	  ret = build_vec_cmp (resultcode, result_type, op0, op1);
	  اذهب return_build_ثنائي_op;
        }
      build_type = integer_type_عقدة;
      إذا ((code0 == INTEGER_TYPE || code0 == REAL_TYPE
	   || code0 == BITINT_TYPE || code0 == FIXED_POINT_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	      || code1 == BITINT_TYPE || code1 == FIXED_POINT_TYPE))
	short_compare = 1;
      وإلا إذا (code0 == POINTER_TYPE && code1 == POINTER_TYPE)
	{
	  addr_space_t as0 = TYPE_ADDR_SPACE (شجرة_TYPE (type0));
	  addr_space_t as1 = TYPE_ADDR_SPACE (شجرة_TYPE (type1));
	  addr_space_t as_common;

	  إذا (comp_target_types (location, type0, type1))
	    {
	      result_type = common_pointer_type (type0, type1, NULL_شجرة);
	      إذا (!COMPLETE_TYPE_P (شجرة_TYPE (type0))
		  != !COMPLETE_TYPE_P (شجرة_TYPE (type1)))
		pedwarn_c99 (location, OPT_Wpedantic,
			     "comparison of complete and incomplete pointers");
	      وإلا إذا (شجرة_CODE (شجرة_TYPE (type0)) == FUNCTION_TYPE)
		pedwarn (location, OPT_Wpedantic, "ISO C forbids "
			 "ordered comparisons of pointers to functions");
	      وإلا إذا (null_pointer_constant_p (orig_op0)
		       || null_pointer_constant_p (orig_op1))
		warning_at (location, OPT_Wextra,
			    "ordered comparison of pointer with null pointer");

	    }
	  وإلا إذا (!addr_space_superset (as0, as1, &as_common))
	    {
	      error_at (location, "comparison of pointers to "
			"disjoint address spaces");
	      أرجع error_mark_عقدة;
	    }
	  وإلا
	    {
	      صحيح qual = ENCODE_QUAL_ADDR_SPACE (as_common);
	      result_type = c_build_pointer_type
			      (c_build_qualified_type (void_type_عقدة, qual));
              pedwarn (location, OPT_Wcompare_distinct_pointer_types,
                       "comparison of distinct pointer types lacks a cast");
	    }
	}
      وإلا إذا (code0 == POINTER_TYPE && null_pointer_constant_p (orig_op1))
	{
	  result_type = type0;
	  إذا (pedantic)
	    pedwarn (location, OPT_Wpedantic,
		     "ordered comparison of pointer with integer zero");
	  وإلا إذا (extra_warnings)
	    warning_at (location, OPT_Wextra,
			"ordered comparison of pointer with integer zero");
	}
      وإلا إذا (code1 == POINTER_TYPE && null_pointer_constant_p (orig_op0))
	{
	  result_type = type1;
	  إذا (pedantic)
	    pedwarn (location, OPT_Wpedantic,
		     "ordered comparison of pointer with integer zero");
	  وإلا إذا (extra_warnings)
	    warning_at (location, OPT_Wextra,
			"ordered comparison of pointer with integer zero");
	}
      وإلا إذا (code0 == POINTER_TYPE
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  result_type = type0;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}
      وإلا إذا ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	       && code1 == POINTER_TYPE)
	{
	  result_type = type1;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}

      إذا ((code0 == POINTER_TYPE || code1 == POINTER_TYPE)
	  && current_function_decl != NULL_شجرة
	  && sanitize_flags_p (SANITIZE_POINTER_COMPARE))
	{
	  op0 = save_تعبير (c_fully_fold (op0, خطأ, عدم));
	  op1 = save_تعبير (c_fully_fold (op1, خطأ, عدم));

	  شجرة tt = builtin_decl_explicit (BUILT_IN_ASAN_POINTER_COMPARE);
	  instrument_تعبير = build_call_تعبير_loc (location, tt, 2, op0, op1);
	}

      إذا ((C_BOOLEAN_TYPE_P (شجرة_TYPE (orig_op0))
	   || truth_قيمة_p (شجرة_CODE (orig_op0)))
	  ^ (C_BOOLEAN_TYPE_P (شجرة_TYPE (orig_op1))
	     || truth_قيمة_p (شجرة_CODE (orig_op1))))
	maybe_warn_bool_compare (location, code, orig_op0, orig_op1);
      اكسر;

    حالة MIN_تعبير:
    حالة MAX_تعبير:
      /* Used for OpenMP atomics.  */
      gcc_assert (flag_openmp);
      common = 1;
      اكسر;

    افتراضي:
      gcc_unreachable ();
    }

  إذا (code0 == ERROR_MARK || code1 == ERROR_MARK)
    أرجع error_mark_عقدة;

  إذا (gnu_vector_type_p (type0)
      && gnu_vector_type_p (type1)
      && (!شجرة_int_cst_equal (TYPE_SIZE (type0), TYPE_SIZE (type1))
	  || !vector_types_compatible_elements_p (type0, type1)))
    {
      gcc_rich_location richloc (location);
      maybe_range_label_for_شجرة_type_mismatch
	label_for_op0 (orig_op0, orig_op1),
	label_for_op1 (orig_op1, orig_op0);
      richloc.maybe_add_تعبير (orig_op0, &label_for_op0, highlight_colors::lhs);
      richloc.maybe_add_تعبير (orig_op1, &label_for_op1, highlight_colors::rhs);
      ثنائي_op_error (&richloc, code, type0, type1);
      أرجع error_mark_عقدة;
    }

  إذا ((code0 == INTEGER_TYPE || code0 == REAL_TYPE || code0 == COMPLEX_TYPE
       || code0 == FIXED_POINT_TYPE || code0 == BITINT_TYPE
       || gnu_vector_type_p (type0))
      && (code1 == INTEGER_TYPE || code1 == REAL_TYPE || code1 == COMPLEX_TYPE
	  || code1 == FIXED_POINT_TYPE || code1 == BITINT_TYPE
	  || gnu_vector_type_p (type1)))
    {
      منطقي first_complex = (code0 == COMPLEX_TYPE);
      منطقي second_complex = (code1 == COMPLEX_TYPE);
      صحيح none_complex = (!first_complex && !second_complex);

      إذا (shorten || common || short_compare)
	{
	  result_type = c_common_type (type0, type1);
	  do_warn_double_promotion (result_type, type0, type1,
				    "implicit conversion from %qT to %qT "
				    "to match other operand of binary "
				    "expression",
				    location);
	  إذا (result_type == error_mark_عقدة)
	    أرجع error_mark_عقدة;
	}

      إذا (first_complex != second_complex
	  && (code == PLUS_تعبير
	      || code == MINUS_تعبير
	      || code == MULT_تعبير
	      || (code == TRUNC_DIV_تعبير && first_complex))
	  && شجرة_CODE (شجرة_TYPE (result_type)) == REAL_TYPE
	  && flag_signed_zeros)
	{
	  /* An operation on mixed real/complex operands must be
	     handled specially, but the language-independent code can
	     more easily optimize the plain complex arithmetic if
	     -fno-signed-zeros.  */
	  شجرة real_type = شجرة_TYPE (result_type);
	  شجرة real, imag;
	  إذا (type0 != orig_type0 || type1 != orig_type1)
	    {
	      gcc_assert (may_need_excess_precision && common);
	      semantic_result_type = c_common_type (orig_type0, orig_type1);
	    }
	  إذا (first_complex)
	    {
	      إذا (شجرة_TYPE (op0) != result_type)
		op0 = convert_and_check (location, result_type, op0);
	      إذا (شجرة_TYPE (op1) != real_type)
		op1 = convert_and_check (location, real_type, op1);
	    }
	  وإلا
	    {
	      إذا (شجرة_TYPE (op0) != real_type)
		op0 = convert_and_check (location, real_type, op0);
	      إذا (شجرة_TYPE (op1) != result_type)
		op1 = convert_and_check (location, result_type, op1);
	    }
	  إذا (شجرة_CODE (op0) == ERROR_MARK || شجرة_CODE (op1) == ERROR_MARK)
	    أرجع error_mark_عقدة;
	  إذا (first_complex)
	    {
	      op0 = save_تعبير (op0);
	      real = build_unary_op (تعبير_LOCATION (orig_op0), REALPART_تعبير,
				     op0, true);
	      imag = build_unary_op (تعبير_LOCATION (orig_op0), IMAGPART_تعبير,
				     op0, true);
	      بدل (code)
		{
		حالة MULT_تعبير:
		حالة TRUNC_DIV_تعبير:
		  op1 = save_تعبير (op1);
		  imag = build2 (resultcode, real_type, imag, op1);
		  /* Fall through.  */
		حالة PLUS_تعبير:
		حالة MINUS_تعبير:
		  real = build2 (resultcode, real_type, real, op1);
		  اكسر;
		افتراضي:
		  gcc_unreachable();
		}
	    }
	  وإلا
	    {
	      op1 = save_تعبير (op1);
	      real = build_unary_op (تعبير_LOCATION (orig_op1), REALPART_تعبير,
				     op1, true);
	      imag = build_unary_op (تعبير_LOCATION (orig_op1), IMAGPART_تعبير,
				     op1, true);
	      بدل (code)
		{
		حالة MULT_تعبير:
		  op0 = save_تعبير (op0);
		  imag = build2 (resultcode, real_type, op0, imag);
		  /* Fall through.  */
		حالة PLUS_تعبير:
		  real = build2 (resultcode, real_type, op0, real);
		  اكسر;
		حالة MINUS_تعبير:
		  real = build2 (resultcode, real_type, op0, real);
		  imag = build1 (NEGATE_تعبير, real_type, imag);
		  اكسر;
		افتراضي:
		  gcc_unreachable();
		}
	    }
	  ret = build2 (COMPLEX_تعبير, result_type, real, imag);
	  اذهب return_build_ثنائي_op;
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
	  final_type = result_type;
	  result_type = shorten_ثنائي_op (result_type, op0, op1,
					   shorten == -1);
	}

      /* Shifts can be shortened if shifting right.  */

      إذا (short_shift)
	{
	  صحيح unsigned_arg;
	  شجرة arg0 = get_narrower (op0, &unsigned_arg);

	  final_type = result_type;

	  إذا (arg0 == op0 && final_type == شجرة_TYPE (op0))
	    unsigned_arg = TYPE_UNSIGNED (شجرة_TYPE (op0));

	  إذا (TYPE_PRECISION (شجرة_TYPE (arg0)) < TYPE_PRECISION (result_type)
	      && شجرة_int_cst_sgn (op1) > 0
	      /* We can shorten only if the shift count is less than the
		 number of bits in the smaller type size.  */
	      && compare_شجرة_int (op1, TYPE_PRECISION (شجرة_TYPE (arg0))) < 0
	      /* We cannot drop an unsigned shift after sign-extension.  */
	      && (!TYPE_UNSIGNED (final_type) || unsigned_arg))
	    {
	      /* Do an unsigned shift if the operand was zero-extended.  */
	      result_type
		= c_common_signed_or_unsigned_type (unsigned_arg,
						    شجرة_TYPE (arg0));
	      /* Convert value-to-be-shifted to that type.  */
	      إذا (شجرة_TYPE (op0) != result_type)
		op0 = convert (result_type, op0);
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
	  شجرة xop0 = op0, xop1 = op1, xresult_type = result_type;
	  تعداد شجرة_code xresultcode = resultcode;
	  شجرة val
	    = shorten_compare (location, &xop0, &xop1, &xresult_type,
			       &xresultcode);

	  إذا (val != NULL_شجرة)
	    {
	      ret = val;
	      اذهب return_build_ثنائي_op;
	    }

	  op0 = xop0, op1 = xop1;
	  converted = 1;
	  resultcode = xresultcode;

	  إذا (c_inhibit_evaluation_warnings == 0 && !c_in_omp_for)
	    {
	      منطقي op0_maybe_const = true;
	      منطقي op1_maybe_const = true;
	      شجرة orig_op0_folded, orig_op1_folded;

	      إذا (in_late_ثنائي_op)
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
		  op0 = c_fully_fold (op0, require_constant_قيمة,
				      &op0_maybe_const);
		  op1 = c_fully_fold (op1, require_constant_قيمة,
				      &op1_maybe_const);
		  c_inhibit_evaluation_warnings--;
		  orig_op0_folded = c_fully_fold (orig_op0,
						  require_constant_قيمة,
						  عدم);
		  orig_op1_folded = c_fully_fold (orig_op1,
						  require_constant_قيمة,
						  عدم);
		}

	      إذا (warn_sign_compare)
		warn_for_sign_compare (location, orig_op0_folded,
				       orig_op1_folded, op0, op1,
				       result_type, resultcode);
	      إذا (!in_late_ثنائي_op && !int_operands)
		{
		  إذا (!op0_maybe_const || شجرة_CODE (op0) != INTEGER_CST)
		    op0 = c_wrap_maybe_const (op0, !op0_maybe_const);
		  إذا (!op1_maybe_const || شجرة_CODE (op1) != INTEGER_CST)
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

  إذا (!result_type)
    {
      /* Favor showing any expression locations that are available. */
      op_location_t oploc (location, UNKNOWN_LOCATION);
      ثنائي_op_rich_location richloc (oploc, orig_op0, orig_op1, true);
      ثنائي_op_error (&richloc, code, شجرة_TYPE (op0), شجرة_TYPE (op1));
      أرجع error_mark_عقدة;
    }

  إذا (build_type == NULL_شجرة)
    {
      build_type = result_type;
      إذا ((type0 != orig_type0 || type1 != orig_type1)
	  && !boolean_op)
	{
	  gcc_assert (may_need_excess_precision && common);
	  semantic_result_type = c_common_type (orig_type0, orig_type1);
	}
    }

  إذا (!converted)
    {
      op0 = ep_convert_and_check (location, result_type, op0,
				  semantic_result_type);
      op1 = ep_convert_and_check (location, result_type, op1,
				  semantic_result_type);

      /* This can happen if one operand has a vector type, and the other
	 has a different type.  */
      إذا (شجرة_CODE (op0) == ERROR_MARK || شجرة_CODE (op1) == ERROR_MARK)
	أرجع error_mark_عقدة;
    }

  إذا (sanitize_flags_p ((SANITIZE_SHIFT
			 | SANITIZE_DIVIDE
			 | SANITIZE_FLOAT_DIVIDE
			 | SANITIZE_SI_OVERFLOW))
      && current_function_decl != NULL_شجرة
      && (doing_div_or_mod || doing_shift)
      && !require_constant_قيمة)
    {
      /* OP0 and/or OP1 might have side-effects.  */
      op0 = save_تعبير (op0);
      op1 = save_تعبير (op1);
      op0 = c_fully_fold (op0, خطأ, عدم);
      op1 = c_fully_fold (op1, خطأ, عدم);
      إذا (doing_div_or_mod && (sanitize_flags_p ((SANITIZE_DIVIDE
						  | SANITIZE_FLOAT_DIVIDE
						  | SANITIZE_SI_OVERFLOW))))
	instrument_تعبير = ubsan_instrument_division (location, op0, op1);
      وإلا إذا (doing_shift && sanitize_flags_p (SANITIZE_SHIFT))
	instrument_تعبير = ubsan_instrument_shift (location, code, op0, op1);
    }

  /* Treat expressions in initializers specially as they can't trap.  */
  إذا (int_const_or_overflow)
    ret = (require_constant_قيمة
	   ? fold_build2_initializer_loc (location, resultcode, build_type,
					  op0, op1)
	   : fold_build2_loc (location, resultcode, build_type, op0, op1));
  وإلا
    ret = build2 (resultcode, build_type, op0, op1);
  إذا (final_type != NULL_شجرة)
    ret = convert (final_type, ret);

 return_build_ثنائي_op:
  gcc_assert (ret != error_mark_عقدة);
  إذا (شجرة_CODE (ret) == INTEGER_CST && !شجرة_OVERFLOW (ret) && !int_const)
    ret = (int_operands
	   ? note_integer_operands (ret)
	   : build1 (NOP_تعبير, شجرة_TYPE (ret), ret));
  وإلا إذا (شجرة_CODE (ret) != INTEGER_CST && int_operands
	   && !in_late_ثنائي_op)
    ret = note_integer_operands (ret);
  protected_set_تعبير_location (ret, location);

  إذا (instrument_تعبير != عدم)
    ret = fold_build2 (COMPOUND_تعبير, شجرة_TYPE (ret),
		       instrument_تعبير, ret);

  إذا (semantic_result_type)
    ret = build1_loc (location, EXCESS_PRECISION_تعبير,
		      semantic_result_type, ret);

  أرجع ret;
}


/* Convert EXPR to be a truth-value (type TYPE), validating its type for this
   purpose.  LOCATION is the source location for the expression.  */

شجرة
c_objc_common_truthvalue_conversion (location_t location, شجرة تعبير, شجرة type)
{
  منطقي int_const, int_operands;

  بدل (شجرة_CODE (شجرة_TYPE (تعبير)))
    {
    حالة ARRAY_TYPE:
      error_at (location, "used array that cannot be converted to pointer where scalar is required");
      أرجع error_mark_عقدة;

    حالة RECORD_TYPE:
      error_at (location, "used struct type value where scalar is required");
      أرجع error_mark_عقدة;

    حالة UNION_TYPE:
      error_at (location, "used union type value where scalar is required");
      أرجع error_mark_عقدة;

    حالة VOID_TYPE:
      error_at (location, "void value not ignored as it ought to be");
      أرجع error_mark_عقدة;

    حالة POINTER_TYPE:
      إذا (reject_gcc_builtin (تعبير))
	أرجع error_mark_عقدة;
      اكسر;

    حالة FUNCTION_TYPE:
      gcc_unreachable ();

    حالة VECTOR_TYPE:
      error_at (location, "used vector type where scalar is required");
      أرجع error_mark_عقدة;

    افتراضي:
      اكسر;
    }

  /* Conversion of a floating constant to boolean goes through here
     and yields an integer constant expression.  Otherwise, the result
     is only an integer constant expression if the argument is.  */
  int_const = ((شجرة_CODE (تعبير) == INTEGER_CST && !شجرة_OVERFLOW (تعبير))
	       || ((شجرة_CODE (تعبير) == REAL_CST
		    || شجرة_CODE (تعبير) == COMPLEX_CST)
		   && (شجرة_CODE (type) == BOOLEAN_TYPE
		       || (شجرة_CODE (type) == ENUMERAL_TYPE
			   && ENUM_UNDERLYING_TYPE (type) != NULL_شجرة
			   && (شجرة_CODE (ENUM_UNDERLYING_TYPE (type))
			       == BOOLEAN_TYPE)))));
  int_operands = تعبير_INT_CONST_OPERANDS (تعبير);
  إذا (int_operands && شجرة_CODE (تعبير) != INTEGER_CST)
    {
      تعبير = remove_c_maybe_const_تعبير (تعبير);
      تعبير = build2 (NE_تعبير, type, تعبير,
		     convert (شجرة_TYPE (تعبير), integer_zero_عقدة));
      تعبير = note_integer_operands (تعبير);
    }
  وإلا
    {
      /* ??? Should we also give an error for vectors rather than leaving
	 those to give errors later?  */
      تعبير = c_common_truthvalue_conversion (location, تعبير);
      تعبير = fold_convert_loc (location, type, تعبير);
    }

  إذا (شجرة_CODE (تعبير) == INTEGER_CST && int_operands && !int_const)
    {
      إذا (شجرة_OVERFLOW (تعبير))
	أرجع تعبير;
      وإلا
	أرجع note_integer_operands (تعبير);
    }
  إذا (شجرة_CODE (تعبير) == INTEGER_CST && !int_const)
    أرجع build1 (NOP_تعبير, شجرة_TYPE (تعبير), تعبير);
  أرجع تعبير;
}


/* Convert EXPR to a contained DECL, updating *TC, *TI and *SE as
   required.  */

شجرة
c_تعبير_to_decl (شجرة تعبير, منطقي *tc ATTRIBUTE_UNUSED, منطقي *se)
{
  إذا (شجرة_CODE (تعبير) == COMPOUND_LITERAL_تعبير)
    {
      شجرة decl = COMPOUND_LITERAL_تعبير_DECL (تعبير);
      /* Executing a compound literal inside a function reinitializes
	 it.  */
      إذا (!شجرة_STATIC (decl))
	*se = true;
      أرجع decl;
    }
  وإلا
    أرجع تعبير;
}

/* Generate OMP construct CODE, with BODY and CLAUSES as its compound
   statement.  LOC is the location of the construct.  */

شجرة
c_finish_omp_construct (location_t loc, تعداد شجرة_code code, شجرة body,
			شجرة clauses)
{
  body = c_end_compound_stmt (loc, body, true);

  شجرة stmt = make_عقدة (code);
  شجرة_TYPE (stmt) = void_type_عقدة;
  OMP_BODY (stmt) = body;
  OMP_CLAUSES (stmt) = clauses;
  SET_تعبير_LOCATION (stmt, loc);

  أرجع add_stmt (stmt);
}

/* Generate OACC_DATA, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the OACC_DATA.  */

شجرة
c_finish_oacc_data (location_t loc, شجرة clauses, شجرة block)
{
  شجرة stmt;

  block = c_end_compound_stmt (loc, block, true);

  stmt = make_عقدة (OACC_DATA);
  شجرة_TYPE (stmt) = void_type_عقدة;
  OACC_DATA_CLAUSES (stmt) = clauses;
  OACC_DATA_BODY (stmt) = block;
  SET_تعبير_LOCATION (stmt, loc);

  أرجع add_stmt (stmt);
}

/* Generate OACC_HOST_DATA, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the OACC_HOST_DATA.  */

شجرة
c_finish_oacc_host_data (location_t loc, شجرة clauses, شجرة block)
{
  شجرة stmt;

  block = c_end_compound_stmt (loc, block, true);

  stmt = make_عقدة (OACC_HOST_DATA);
  شجرة_TYPE (stmt) = void_type_عقدة;
  OACC_HOST_DATA_CLAUSES (stmt) = clauses;
  OACC_HOST_DATA_BODY (stmt) = block;
  SET_تعبير_LOCATION (stmt, loc);

  أرجع add_stmt (stmt);
}

/* Like c_begin_compound_stmt, except force the retention of the BLOCK.  */

شجرة
c_begin_omp_parallel (فراغ)
{
  شجرة block;

  keep_next_level ();
  block = c_begin_compound_stmt (true);

  أرجع block;
}

/* Generate OMP_PARALLEL, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the OMP_PARALLEL.  */

شجرة
c_finish_omp_parallel (location_t loc, شجرة clauses, شجرة block)
{
  شجرة stmt;

  block = c_end_compound_stmt (loc, block, true);

  stmt = make_عقدة (OMP_PARALLEL);
  شجرة_TYPE (stmt) = void_type_عقدة;
  OMP_PARALLEL_CLAUSES (stmt) = clauses;
  OMP_PARALLEL_BODY (stmt) = block;
  SET_تعبير_LOCATION (stmt, loc);

  أرجع add_stmt (stmt);
}

/* Like c_begin_compound_stmt, except force the retention of the BLOCK.  */

شجرة
c_begin_omp_task (فراغ)
{
  شجرة block;

  keep_next_level ();
  block = c_begin_compound_stmt (true);

  أرجع block;
}

/* Generate OMP_TASK, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the #pragma.  */

شجرة
c_finish_omp_task (location_t loc, شجرة clauses, شجرة block)
{
  شجرة stmt;

  block = c_end_compound_stmt (loc, block, true);

  stmt = make_عقدة (OMP_TASK);
  شجرة_TYPE (stmt) = void_type_عقدة;
  OMP_TASK_CLAUSES (stmt) = clauses;
  OMP_TASK_BODY (stmt) = block;
  SET_تعبير_LOCATION (stmt, loc);

  أرجع add_stmt (stmt);
}

/* Generate GOMP_cancel call for #pragma omp cancel.  */

فراغ
c_finish_omp_cancel (location_t loc, شجرة clauses)
{
  شجرة fn = builtin_decl_explicit (BUILT_IN_GOMP_CANCEL);
  صحيح mask = 0;
  إذا (omp_find_clause (clauses, OMP_CLAUSE_PARALLEL))
    mask = 1;
  وإلا إذا (omp_find_clause (clauses, OMP_CLAUSE_FOR))
    mask = 2;
  وإلا إذا (omp_find_clause (clauses, OMP_CLAUSE_SECTIONS))
    mask = 4;
  وإلا إذا (omp_find_clause (clauses, OMP_CLAUSE_TASKGROUP))
    mask = 8;
  وإلا
    {
      error_at (loc, "%<#pragma omp cancel%> must specify one of "
		     "%<parallel%>, %<for%>, %<sections%> or %<taskgroup%> "
		     "clauses");
      أرجع;
    }
  شجرة ifc = omp_find_clause (clauses, OMP_CLAUSE_IF);
  إذا (ifc != NULL_شجرة)
    {
      إذا (OMP_CLAUSE_IF_MODIFIER (ifc) != ERROR_MARK
	  && OMP_CLAUSE_IF_MODIFIER (ifc) != VOID_CST)
	error_at (OMP_CLAUSE_LOCATION (ifc),
		  "expected %<cancel%> %<if%> clause modifier");
      وإلا
	{
	  شجرة ifc2 = omp_find_clause (OMP_CLAUSE_CHAIN (ifc), OMP_CLAUSE_IF);
	  إذا (ifc2 != NULL_شجرة)
	    {
	      gcc_assert (OMP_CLAUSE_IF_MODIFIER (ifc) == VOID_CST
			  && OMP_CLAUSE_IF_MODIFIER (ifc2) != ERROR_MARK
			  && OMP_CLAUSE_IF_MODIFIER (ifc2) != VOID_CST);
	      error_at (OMP_CLAUSE_LOCATION (ifc2),
			"expected %<cancel%> %<if%> clause modifier");
	    }
	}

      شجرة type = شجرة_TYPE (OMP_CLAUSE_IF_تعبير (ifc));
      ifc = fold_build2_loc (OMP_CLAUSE_LOCATION (ifc), NE_تعبير,
			     boolean_type_عقدة, OMP_CLAUSE_IF_تعبير (ifc),
			     build_zero_cst (type));
    }
  وإلا
    ifc = boolean_true_عقدة;
  شجرة stmt = build_call_تعبير_loc (loc, fn, 2,
				   build_int_cst (integer_type_عقدة, mask),
				   ifc);
  add_stmt (stmt);
}

/* Generate GOMP_cancellation_point call for
   #pragma omp cancellation point.  */

فراغ
c_finish_omp_cancellation_point (location_t loc, شجرة clauses)
{
  شجرة fn = builtin_decl_explicit (BUILT_IN_GOMP_CANCELLATION_POINT);
  صحيح mask = 0;
  إذا (omp_find_clause (clauses, OMP_CLAUSE_PARALLEL))
    mask = 1;
  وإلا إذا (omp_find_clause (clauses, OMP_CLAUSE_FOR))
    mask = 2;
  وإلا إذا (omp_find_clause (clauses, OMP_CLAUSE_SECTIONS))
    mask = 4;
  وإلا إذا (omp_find_clause (clauses, OMP_CLAUSE_TASKGROUP))
    mask = 8;
  وإلا
    {
      error_at (loc, "%<#pragma omp cancellation point%> must specify one of "
		     "%<parallel%>, %<for%>, %<sections%> or %<taskgroup%> "
		     "clauses");
      أرجع;
    }
  شجرة stmt = build_call_تعبير_loc (loc, fn, 1,
				   build_int_cst (integer_type_عقدة, mask));
  add_stmt (stmt);
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

ساكن شجرة
handle_omp_array_sections_1 (شجرة c, شجرة t, vec<شجرة> &types,
			     منطقي &maybe_zero_len, unsigned صحيح &first_non_one,
			     تعداد c_omp_region_type ort)
{
  شجرة ret, أدنى_bound, length, type;
  منطقي openacc = (ort & C_ORT_ACC) != 0;
  إذا (شجرة_CODE (t) != OMP_ARRAY_SECTION)
    {
      إذا (error_operand_p (t))
	أرجع error_mark_عقدة;
      c_omp_address_inspector ai (OMP_CLAUSE_LOCATION (c), t);
      ret = t;
      إذا (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
	  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
	  && TYPE_ATOMIC (strip_array_types (شجرة_TYPE (t))))
	{
	  error_at (OMP_CLAUSE_LOCATION (c), "%<_Atomic%> %qE in %qs clause",
		    t, omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  أرجع error_mark_عقدة;
	}
      إذا (!ai.check_clause (c))
	أرجع error_mark_عقدة;
      وإلا إذا (ai.component_access_p ()
	       && (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TO
		   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_FROM))
	t = ai.get_جذر_term (true);
      وإلا
	t = ai.unconverted_ref_origin ();
      إذا (t == error_mark_عقدة)
	أرجع error_mark_عقدة;
      إذا (!VAR_P (t)
	  && (ort == C_ORT_ACC || !تعبير_P (t))
	  && شجرة_CODE (t) != PARM_DECL)
	{
	  إذا (DECL_P (t))
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD is not a variable in %qs clause", t,
		      omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  وإلا
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qE is not a variable in %qs clause", t,
		      omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  أرجع error_mark_عقدة;
	}
      وإلا إذا (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
	       && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
	       && TYPE_ATOMIC (شجرة_TYPE (t)))
	{
	  error_at (OMP_CLAUSE_LOCATION (c), "%<_Atomic%> %qD in %qs clause",
		    t, omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  أرجع error_mark_عقدة;
	}
      وإلا إذا (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
	       && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
	       && VAR_P (t)
	       && DECL_THREAD_LOCAL_P (t))
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "%qD is threadprivate variable in %qs clause", t,
		    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  أرجع error_mark_عقدة;
	}
      إذا ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY
	   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND)
	  && TYPE_ATOMIC (شجرة_TYPE (t))
	  && POINTER_TYPE_P (شجرة_TYPE (t)))
	{
	  /* If the array section is pointer based and the pointer
	     itself is _Atomic qualified, we need to atomically load
	     the pointer.  */
	  ret = convert_lvalue_to_rvalue (OMP_CLAUSE_LOCATION (c),
					  ret, خطأ, خطأ);
	}
      أرجع ret;
    }

  ret = handle_omp_array_sections_1 (c, شجرة_OPERAND (t, 0), types,
				     maybe_zero_len, first_non_one, ort);
  إذا (ret == error_mark_عقدة || ret == NULL_شجرة)
    أرجع ret;

  type = شجرة_TYPE (ret);
  أدنى_bound = شجرة_OPERAND (t, 1);
  length = شجرة_OPERAND (t, 2);

  إذا (أدنى_bound == error_mark_عقدة || length == error_mark_عقدة)
    أرجع error_mark_عقدة;

  إذا (أدنى_bound && !INTEGRAL_TYPE_P (شجرة_TYPE (أدنى_bound)))
    {
      error_at (OMP_CLAUSE_LOCATION (c),
		"low bound %qE of array section does not have integral type",
		أدنى_bound);
      أرجع error_mark_عقدة;
    }
  إذا (length && !INTEGRAL_TYPE_P (شجرة_TYPE (length)))
    {
      error_at (OMP_CLAUSE_LOCATION (c),
		"length %qE of array section does not have integral type",
		length);
      أرجع error_mark_عقدة;
    }
  إذا (أدنى_bound
      && شجرة_CODE (أدنى_bound) == INTEGER_CST
      && TYPE_PRECISION (شجرة_TYPE (أدنى_bound))
	 > TYPE_PRECISION (sizetype))
    أدنى_bound = fold_convert (sizetype, أدنى_bound);
  إذا (length
      && شجرة_CODE (length) == INTEGER_CST
      && TYPE_PRECISION (شجرة_TYPE (length))
	 > TYPE_PRECISION (sizetype))
    length = fold_convert (sizetype, length);
  إذا (أدنى_bound == NULL_شجرة)
    أدنى_bound = integer_zero_عقدة;
  إذا (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
      && (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_ATTACH
	  || OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_DETACH))
    {
      إذا (length != integer_one_عقدة)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "expected single pointer in %qs clause",
		    user_omp_clause_code_name (c, openacc));
	  أرجع error_mark_عقدة;
	}
    }
  إذا (length != NULL_شجرة)
    {
      إذا (!integer_nonzerop (length))
	{
	  إذا (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY
	      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
	      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
	      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
	      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TASK_REDUCTION)
	    {
	      إذا (integer_zerop (length))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "zero length array section in %qs clause",
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  أرجع error_mark_عقدة;
		}
	    }
	  وإلا
	    maybe_zero_len = true;
	}
      إذا (first_non_one == types.length ()
	  && (شجرة_CODE (length) != INTEGER_CST || integer_onep (length)))
	first_non_one++;
    }
  إذا (شجرة_CODE (type) == ARRAY_TYPE)
    {
      إذا (length == NULL_شجرة
	  && (TYPE_DOMAIN (type) == NULL_شجرة
	      || TYPE_MAX_قيمة (TYPE_DOMAIN (type)) == NULL_شجرة))
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "for unknown bound array type length expression must "
		    "be specified");
	  أرجع error_mark_عقدة;
	}
      إذا (شجرة_CODE (أدنى_bound) == INTEGER_CST
	  && شجرة_int_cst_sgn (أدنى_bound) == -1)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "negative low bound in array section in %qs clause",
		    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  أرجع error_mark_عقدة;
	}
      إذا (length != NULL_شجرة
	  && شجرة_CODE (length) == INTEGER_CST
	  && شجرة_int_cst_sgn (length) == -1)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "negative length in array section in %qs clause",
		    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  أرجع error_mark_عقدة;
	}
      إذا (TYPE_DOMAIN (type)
	  && TYPE_MAX_قيمة (TYPE_DOMAIN (type))
	  && شجرة_CODE (TYPE_MAX_قيمة (TYPE_DOMAIN (type)))
			== INTEGER_CST)
	{
	  شجرة size
	    = fold_convert (sizetype, TYPE_MAX_قيمة (TYPE_DOMAIN (type)));
	  size = size_binop (PLUS_تعبير, size, size_one_عقدة);
	  إذا (شجرة_CODE (أدنى_bound) == INTEGER_CST)
	    {
	      إذا (شجرة_int_cst_lt (size, أدنى_bound))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "low bound %qE above array section size "
			    "in %qs clause", أدنى_bound,
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  أرجع error_mark_عقدة;
		}
	      إذا (شجرة_int_cst_equal (size, أدنى_bound))
		{
		  إذا (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TASK_REDUCTION)
		    {
		      error_at (OMP_CLAUSE_LOCATION (c),
				"zero length array section in %qs clause",
				omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		      أرجع error_mark_عقدة;
		    }
		  maybe_zero_len = true;
		}
	      وإلا إذا (length == NULL_شجرة
		       && first_non_one == types.length ()
		       && شجرة_int_cst_equal
			    (TYPE_MAX_قيمة (TYPE_DOMAIN (type)),
			     أدنى_bound))
		first_non_one++;
	    }
	  وإلا إذا (length == NULL_شجرة)
	    {
	      إذا (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
		  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
		  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_REDUCTION
		  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_IN_REDUCTION
		  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_TASK_REDUCTION)
		maybe_zero_len = true;
	      إذا (first_non_one == types.length ())
		first_non_one++;
	    }
	  إذا (length && شجرة_CODE (length) == INTEGER_CST)
	    {
	      إذا (شجرة_int_cst_lt (size, length))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "length %qE above array section size "
			    "in %qs clause", length,
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  أرجع error_mark_عقدة;
		}
	      إذا (شجرة_CODE (أدنى_bound) == INTEGER_CST)
		{
		  شجرة lbpluslen
		    = size_binop (PLUS_تعبير,
				  fold_convert (sizetype, أدنى_bound),
				  fold_convert (sizetype, length));
		  إذا (شجرة_CODE (lbpluslen) == INTEGER_CST
		      && شجرة_int_cst_lt (size, lbpluslen))
		    {
		      error_at (OMP_CLAUSE_LOCATION (c),
				"high bound %qE above array section size "
				"in %qs clause", lbpluslen,
				omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		      أرجع error_mark_عقدة;
		    }
		}
	    }
	}
      وإلا إذا (length == NULL_شجرة)
	{
	  إذا (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
	      && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
	      && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_REDUCTION
	      && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_IN_REDUCTION
	      && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_TASK_REDUCTION)
	    maybe_zero_len = true;
	  إذا (first_non_one == types.length ())
	    first_non_one++;
	}

      /* For [lb:] we will need to evaluate lb more than once.  */
      إذا (length == NULL_شجرة && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND)
	{
	  شجرة lb = save_تعبير (أدنى_bound);
	  إذا (lb != أدنى_bound)
	    {
	      شجرة_OPERAND (t, 1) = lb;
	      أدنى_bound = lb;
	    }
	}
    }
  وإلا إذا (شجرة_CODE (type) == POINTER_TYPE)
    {
      إذا (length == NULL_شجرة)
	{
	  إذا (شجرة_CODE (ret) == PARM_DECL && C_ARRAY_PARAMETER (ret))
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "for array function parameter length expression "
		      "must be specified");
	  وإلا
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "for pointer type length expression must be specified");
	  أرجع error_mark_عقدة;
	}
      إذا (length != NULL_شجرة
	  && شجرة_CODE (length) == INTEGER_CST
	  && شجرة_int_cst_sgn (length) == -1)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "negative length in array section in %qs clause",
		    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  أرجع error_mark_عقدة;
	}
      /* If there is a pointer type anywhere but in the very first
	 array-section-subscript, the array section could be non-contiguous.  */
      إذا (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
	  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
	  && شجرة_CODE (شجرة_OPERAND (t, 0)) == OMP_ARRAY_SECTION)
	{
	  /* If any prior dimension has a non-one length, then deem this
	     array section as non-contiguous.  */
	  لكل (شجرة d = شجرة_OPERAND (t, 0);
	       شجرة_CODE (d) == OMP_ARRAY_SECTION;
	       d = شجرة_OPERAND (d, 0))
	    {
	      شجرة d_length = شجرة_OPERAND (d, 2);
	      إذا (d_length == NULL_شجرة || !integer_onep (d_length))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "array section is not contiguous in %qs clause",
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  أرجع error_mark_عقدة;
		}
	    }
	}
    }
  وإلا
    {
      error_at (OMP_CLAUSE_LOCATION (c),
		"%qE does not have pointer or array type", ret);
      أرجع error_mark_عقدة;
    }
  إذا (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND)
    types.safe_ادفع (شجرة_TYPE (ret));
  /* We will need to evaluate lb more than once.  */
  شجرة lb = save_تعبير (أدنى_bound);
  إذا (lb != أدنى_bound)
    {
      شجرة_OPERAND (t, 1) = lb;
      أدنى_bound = lb;
    }
  ret = build_array_ref (OMP_CLAUSE_LOCATION (c), ret, أدنى_bound);
  أرجع ret;
}

/* Handle array sections for clause C.  */

ساكن منطقي
handle_omp_array_sections (شجرة &c, تعداد c_omp_region_type ort)
{
  منطقي maybe_zero_len = خطأ;
  unsigned صحيح first_non_one = 0;
  auto_vec<شجرة, 10> types;
  شجرة *tp = &OMP_CLAUSE_DECL (c);
  إذا ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
       || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY)
      && OMP_ITERATOR_DECL_P (*tp))
    tp = &شجرة_قيمة (*tp);
  شجرة first = handle_omp_array_sections_1 (c, *tp, types,
					    maybe_zero_len, first_non_one,
					    ort);
  إذا (first == error_mark_عقدة)
    أرجع true;
  إذا (first == NULL_شجرة)
    أرجع خطأ;
  إذا (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY)
    {
      شجرة t = *tp;
      شجرة tem = NULL_شجرة;
      /* Need to evaluate side effects in the length expressions
	 if any.  */
      طالما (شجرة_CODE (t) == شجرة_LIST)
	{
	  إذا (شجرة_قيمة (t) && شجرة_SIDE_EFFECTS (شجرة_قيمة (t)))
	    {
	      إذا (tem == NULL_شجرة)
		tem = شجرة_قيمة (t);
	      وإلا
		tem = build2 (COMPOUND_تعبير, شجرة_TYPE (tem),
			      شجرة_قيمة (t), tem);
	    }
	  t = شجرة_CHAIN (t);
	}
      إذا (tem)
	first = build2 (COMPOUND_تعبير, شجرة_TYPE (first), tem, first);
      first = c_fully_fold (first, خطأ, عدم, true);
      *tp = first;
    }
  وإلا
    {
      unsigned صحيح رقم = types.length (), i;
      شجرة t, side_effects = NULL_شجرة, size = NULL_شجرة;
      شجرة condition = NULL_شجرة;

      إذا (int_size_in_bytes (شجرة_TYPE (first)) <= 0)
	maybe_zero_len = true;

      لكل (i = رقم, t = OMP_CLAUSE_DECL (c); i > 0;
	   t = شجرة_OPERAND (t, 0))
	{
	  شجرة أدنى_bound = شجرة_OPERAND (t, 1);
	  شجرة length = شجرة_OPERAND (t, 2);

	  i--;
	  إذا (أدنى_bound
	      && شجرة_CODE (أدنى_bound) == INTEGER_CST
	      && TYPE_PRECISION (شجرة_TYPE (أدنى_bound))
		 > TYPE_PRECISION (sizetype))
	    أدنى_bound = fold_convert (sizetype, أدنى_bound);
	  إذا (length
	      && شجرة_CODE (length) == INTEGER_CST
	      && TYPE_PRECISION (شجرة_TYPE (length))
		 > TYPE_PRECISION (sizetype))
	    length = fold_convert (sizetype, length);
	  إذا (أدنى_bound == NULL_شجرة)
	    أدنى_bound = integer_zero_عقدة;
	  إذا (!maybe_zero_len && i > first_non_one)
	    {
	      إذا (integer_nonzerop (أدنى_bound))
		اذهب do_warn_noncontiguous;
	      إذا (length != NULL_شجرة
		  && شجرة_CODE (length) == INTEGER_CST
		  && TYPE_DOMAIN (types[i])
		  && TYPE_MAX_قيمة (TYPE_DOMAIN (types[i]))
		  && شجرة_CODE (TYPE_MAX_قيمة (TYPE_DOMAIN (types[i])))
		     == INTEGER_CST)
		{
		  شجرة size;
		  size = size_binop (PLUS_تعبير,
				     TYPE_MAX_قيمة (TYPE_DOMAIN (types[i])),
				     size_one_عقدة);
		  إذا (!شجرة_int_cst_equal (length, size))
		    {
		     do_warn_noncontiguous:
		      error_at (OMP_CLAUSE_LOCATION (c),
				"array section is not contiguous in %qs "
				"clause",
				omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		      أرجع true;
		    }
		}
	      إذا (length != NULL_شجرة
		  && شجرة_SIDE_EFFECTS (length))
		{
		  إذا (side_effects == NULL_شجرة)
		    side_effects = length;
		  وإلا
		    side_effects = build2 (COMPOUND_تعبير,
					   شجرة_TYPE (side_effects),
					   length, side_effects);
		}
	    }
	  وإلا
	    {
	      شجرة l;

	      إذا (i > first_non_one
		  && ((length && integer_nonzerop (length))
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TASK_REDUCTION))
		استمر;
	      إذا (length)
		l = fold_convert (sizetype, length);
	      وإلا
		{
		  l = size_binop (PLUS_تعبير,
				  TYPE_MAX_قيمة (TYPE_DOMAIN (types[i])),
				  size_one_عقدة);
		  l = size_binop (MINUS_تعبير, l,
				  fold_convert (sizetype, أدنى_bound));
		}
	      إذا (i > first_non_one)
		{
		  l = fold_build2 (NE_تعبير, boolean_type_عقدة, l,
				   size_zero_عقدة);
		  إذا (condition == NULL_شجرة)
		    condition = l;
		  وإلا
		    condition = fold_build2 (BIT_AND_تعبير, boolean_type_عقدة,
					     l, condition);
		}
	      وإلا إذا (size == NULL_شجرة)
		{
		  size = size_in_bytes (شجرة_TYPE (types[i]));
		  شجرة eltype = شجرة_TYPE (types[رقم - 1]);
		  طالما (شجرة_CODE (eltype) == ARRAY_TYPE)
		    eltype = شجرة_TYPE (eltype);
		  إذا (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TASK_REDUCTION)
		    {
		      إذا (integer_zerop (size)
			  || integer_zerop (size_in_bytes (eltype)))
			{
			  error_at (OMP_CLAUSE_LOCATION (c),
				    "zero length array section in %qs clause",
				    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
			  أرجع error_mark_عقدة;
			}
		      size = size_binop (EXACT_DIV_تعبير, size,
					 size_in_bytes (eltype));
		    }
		  size = size_binop (MULT_تعبير, size, l);
		  إذا (condition)
		    size = fold_build3 (COND_تعبير, sizetype, condition,
					size, size_zero_عقدة);
		}
	      وإلا
		size = size_binop (MULT_تعبير, size, l);
	    }
	}
      إذا (side_effects)
	size = build2 (COMPOUND_تعبير, sizetype, side_effects, size);
      إذا (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
	  || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
	  || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TASK_REDUCTION)
	{
	  size = size_binop (MINUS_تعبير, size, size_one_عقدة);
	  size = c_fully_fold (size, خطأ, عدم);
	  size = save_تعبير (size);
	  شجرة index_type = build_index_type (size);
	  شجرة eltype = شجرة_TYPE (first);
	  طالما (شجرة_CODE (eltype) == ARRAY_TYPE)
	    eltype = شجرة_TYPE (eltype);
	  شجرة type = c_build_array_type (eltype, index_type);
	  شجرة ptype = c_build_pointer_type (eltype);
	  إذا (شجرة_CODE (شجرة_TYPE (t)) == ARRAY_TYPE)
	    t = build_fold_addr_تعبير (t);
	  شجرة t2 = build_fold_addr_تعبير (first);
	  t2 = fold_convert_loc (OMP_CLAUSE_LOCATION (c),
				 ptrdiff_type_عقدة, t2);
	  t2 = fold_build2_loc (OMP_CLAUSE_LOCATION (c), MINUS_تعبير,
				ptrdiff_type_عقدة, t2,
				fold_convert_loc (OMP_CLAUSE_LOCATION (c),
						  ptrdiff_type_عقدة, t));
	  t2 = c_fully_fold (t2, خطأ, عدم);
	  إذا (شجرة_fits_shwi_p (t2))
	    t = build2 (MEM_REF, type, t,
			build_int_cst (ptype, شجرة_to_shwi (t2)));
	  وإلا
	    {
	      t2 = fold_convert_loc (OMP_CLAUSE_LOCATION (c), sizetype, t2);
	      t = build2_loc (OMP_CLAUSE_LOCATION (c), POINTER_PLUS_تعبير,
			      شجرة_TYPE (t), t, t2);
	      t = build2 (MEM_REF, type, t, build_int_cst (ptype, 0));
	    }
	  OMP_CLAUSE_DECL (c) = t;
	  أرجع خطأ;
	}
      first = c_fully_fold (first, خطأ, عدم);
      OMP_CLAUSE_DECL (c) = first;
      إذا (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_HAS_DEVICE_ADDR)
	أرجع خطأ;
      /* Don't set OMP_CLAUSE_SIZE for bare attach/detach clauses.  */
      إذا (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP
	  || (OMP_CLAUSE_MAP_KIND (c) != GOMP_MAP_ATTACH
	      && OMP_CLAUSE_MAP_KIND (c) != GOMP_MAP_DETACH
	      && OMP_CLAUSE_MAP_KIND (c) != GOMP_MAP_FORCE_DETACH))
	{
	  إذا (size)
	    size = c_fully_fold (size, خطأ, عدم);
	  OMP_CLAUSE_SIZE (c) = size;
	}

      إذا (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP)
	أرجع خطأ;

      auto_vec<omp_addr_token *, 10> addr_tokens;

      إذا (!omp_parse_تعبير (addr_tokens, first))
	أرجع true;

      c_omp_address_inspector ai (OMP_CLAUSE_LOCATION (c), t);

      شجرة nc = ai.expand_map_clause (c, first, addr_tokens, ort);
      إذا (nc != error_mark_عقدة)
	{
	  using نطاق omp_addr_tokenizer;

	  إذا (ai.maybe_zero_length_array_section (c))
	    OMP_CLAUSE_MAP_MAYBE_ZERO_LENGTH_ARRAY_SECTION (c) = 1;

	  /* !!! If we're accessing a base decl via chained access
	     methods (e.g. multiple indirections), duplicate clause
	     detection won't work properly.  Skip it in that case.  */
	  إذا ((addr_tokens[0]->type == STRUCTURE_BASE
	       || addr_tokens[0]->type == ARRAY_BASE)
	      && addr_tokens[0]->u.structure_base_kind == BASE_DECL
	      && addr_tokens[1]->type == ACCESS_METHOD
	      && omp_access_chain_p (addr_tokens, 1))
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

ساكن شجرة
c_clone_omp_udr (شجرة stmt, شجرة omp_decl1, شجرة omp_decl2,
		 شجرة decl, شجرة placeholder)
{
  copy_body_data id;
  hash_map<شجرة, شجرة> decl_map;

  decl_map.put (omp_decl1, placeholder);
  decl_map.put (omp_decl2, decl);
  memset (&id, 0, حجم (id));
  id.src_fn = DECL_CONTEXT (omp_decl1);
  id.dst_fn = current_function_decl;
  id.src_cfun = DECL_STRUCT_FUNCTION (id.src_fn);
  id.decl_map = &decl_map;

  id.copy_decl = copy_decl_no_change;
  id.transform_call_graph_edges = CB_CGE_DUPLICATE;
  id.transform_new_cfg = true;
  id.transform_return_to_modify = خطأ;
  id.eh_lp_nr = 0;
  walk_شجرة (&stmt, copy_شجرة_body_r, &id, عدم);
  أرجع stmt;
}

/* Helper function of c_finish_omp_clauses, called via walk_tree.
   Find OMP_CLAUSE_PLACEHOLDER (passed in DATA) in *TP.  */

ساكن شجرة
c_find_omp_placeholder_r (شجرة *tp, صحيح *, فراغ *data)
{
  إذا (*tp == (شجرة) data)
    أرجع *tp;
  أرجع NULL_شجرة;
}

/* Similarly, but also walk aggregate fields.  */

بنية c_find_omp_var_s { شجرة var; hash_set<شجرة> *pset; };

ساكن شجرة
c_find_omp_var_r (شجرة *tp, صحيح *, فراغ *data)
{
  إذا (*tp == ((بنية c_find_omp_var_s *) data)->var)
    أرجع *tp;
  إذا (RECORD_OR_UNION_TYPE_P (*tp))
    {
      شجرة field;
      hash_set<شجرة> *pset = ((بنية c_find_omp_var_s *) data)->pset;

      لكل (field = TYPE_FIELDS (*tp); field;
	   field = DECL_CHAIN (field))
	إذا (شجرة_CODE (field) == FIELD_DECL)
	  {
	    شجرة ret = walk_شجرة (&DECL_FIELD_OFFSET (field),
				  c_find_omp_var_r, data, pset);
	    إذا (ret)
	      أرجع ret;
	    ret = walk_شجرة (&DECL_SIZE (field), c_find_omp_var_r, data, pset);
	    إذا (ret)
	      أرجع ret;
	    ret = walk_شجرة (&DECL_SIZE_UNIT (field), c_find_omp_var_r, data,
			     pset);
	    إذا (ret)
	      أرجع ret;
	    ret = walk_شجرة (&شجرة_TYPE (field), c_find_omp_var_r, data, pset);
	    إذا (ret)
	      أرجع ret;
	  }
    }
  وإلا إذا (INTEGRAL_TYPE_P (*tp))
    أرجع walk_شجرة (&TYPE_MAX_قيمة (*tp), c_find_omp_var_r, data,
		      ((بنية c_find_omp_var_s *) data)->pset);
  أرجع NULL_شجرة;
}

/* Finish OpenMP iterators ITER.  Return true if they are erroneous
   and clauses containing them should be removed.  */

ساكن منطقي
c_omp_finish_iterators (شجرة iter)
{
  منطقي ret = خطأ;
  لكل (شجرة it = iter; it; it = شجرة_CHAIN (it))
    {
      شجرة var = OMP_ITERATOR_VAR (it);
      شجرة begin = OMP_ITERATOR_BEGIN (it);
      شجرة end = OMP_ITERATOR_END (it);
      شجرة step = OMP_ITERATOR_STEP (it);
      شجرة orig_step;
      شجرة type = شجرة_TYPE (var);
      location_t loc = DECL_SOURCE_LOCATION (var);
      إذا (type == error_mark_عقدة)
	{
	  ret = true;
	  استمر;
	}
      إذا (!INTEGRAL_TYPE_P (type) && !POINTER_TYPE_P (type))
	{
	  error_at (loc, "iterator %qD has neither integral nor pointer type",
		    var);
	  ret = true;
	  استمر;
	}
      وإلا إذا (TYPE_ATOMIC (type))
	{
	  error_at (loc, "iterator %qD has %<_Atomic%> qualified type", var);
	  ret = true;
	  استمر;
	}
      وإلا إذا (TYPE_READONLY (type))
	{
	  error_at (loc, "iterator %qD has const qualified type", var);
	  ret = true;
	  استمر;
	}
      وإلا إذا (step == error_mark_عقدة
	       || شجرة_TYPE (step) == error_mark_عقدة)
	{
	  ret = true;
	  استمر;
	}
      وإلا إذا (!INTEGRAL_TYPE_P (شجرة_TYPE (step)))
	{
	  error_at (تعبير_LOC_OR_LOC (step, loc),
		    "iterator step with non-integral type");
	  ret = true;
	  استمر;
	}
      begin = c_fully_fold (build_c_cast (loc, type, begin), خطأ, عدم);
      end = c_fully_fold (build_c_cast (loc, type, end), خطأ, عدم);
      orig_step = save_تعبير (c_fully_fold (step, خطأ, عدم));
      شجرة stype = POINTER_TYPE_P (type) ? sizetype : type;
      step = c_fully_fold (build_c_cast (loc, stype, orig_step), خطأ, عدم);
      إذا (POINTER_TYPE_P (type))
	{
	  begin = save_تعبير (begin);
	  step = pointer_int_sum (loc, PLUS_تعبير, begin, step);
	  step = fold_build2_loc (loc, MINUS_تعبير, sizetype,
				  fold_convert (sizetype, step),
				  fold_convert (sizetype, begin));
	  step = fold_convert (ssizetype, step);
	}
      إذا (integer_zerop (step))
	{
	  error_at (loc, "iterator %qD has zero step", var);
	  ret = true;
	  استمر;
	}

      إذا (begin == error_mark_عقدة
	  || end == error_mark_عقدة
	  || step == error_mark_عقدة
	  || orig_step == error_mark_عقدة)
	{
	  ret = true;
	  استمر;
	}
      hash_set<شجرة> pset;
      شجرة it2;
      لكل (it2 = شجرة_CHAIN (it); it2; it2 = شجرة_CHAIN (it2))
	{
	  شجرة var2 = OMP_ITERATOR_VAR (it2);
	  شجرة begin2 = OMP_ITERATOR_BEGIN (it2);
	  شجرة end2 = OMP_ITERATOR_END (it2);
	  شجرة step2 = OMP_ITERATOR_STEP (it2);
	  شجرة type2 = شجرة_TYPE (var2);
	  location_t loc2 = DECL_SOURCE_LOCATION (var2);
	  بنية c_find_omp_var_s data = { var, &pset };
	  إذا (walk_شجرة (&type2, c_find_omp_var_r, &data, &pset))
	    {
	      error_at (loc2,
			"type of iterator %qD refers to outer iterator %qD",
			var2, var);
	      اكسر;
	    }
	  وإلا إذا (walk_شجرة (&begin2, c_find_omp_var_r, &data, &pset))
	    {
	      error_at (تعبير_LOC_OR_LOC (begin2, loc2),
			"begin expression refers to outer iterator %qD", var);
	      اكسر;
	    }
	  وإلا إذا (walk_شجرة (&end2, c_find_omp_var_r, &data, &pset))
	    {
	      error_at (تعبير_LOC_OR_LOC (end2, loc2),
			"end expression refers to outer iterator %qD", var);
	      اكسر;
	    }
	  وإلا إذا (walk_شجرة (&step2, c_find_omp_var_r, &data, &pset))
	    {
	      error_at (تعبير_LOC_OR_LOC (step2, loc2),
			"step expression refers to outer iterator %qD", var);
	      اكسر;
	    }
	}
      إذا (it2)
	{
	  ret = true;
	  استمر;
	}
      OMP_ITERATOR_BEGIN (it) = begin;
      OMP_ITERATOR_END (it) = end;
      OMP_ITERATOR_STEP (it) = step;
      OMP_ITERATOR_ORIG_STEP (it) = orig_step;
    }
  أرجع ret;
}

/* Ensure that pointers are used in OpenACC attach and detach clauses.
   Return true if an error has been detected.  */

ساكن منطقي
c_oacc_check_attachments (شجرة c)
{
  إذا (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP)
    أرجع خطأ;

  /* OpenACC attach / detach clauses must be pointers.  */
  إذا (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_ATTACH
      || OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_DETACH)
    {
      شجرة t = OMP_CLAUSE_DECL (c);

      طالما (شجرة_CODE (t) == OMP_ARRAY_SECTION)
	t = شجرة_OPERAND (t, 0);

      إذا (شجرة_CODE (شجرة_TYPE (t)) != POINTER_TYPE)
	{
	  error_at (OMP_CLAUSE_LOCATION (c), "expected pointer in %qs clause",
		    user_omp_clause_code_name (c, true));
	  أرجع true;
	}
    }

  أرجع خطأ;
}

/* For all elements of CLAUSES, validate them against their constraints.
   Remove any elements from the list that are invalid.  */

شجرة
c_finish_omp_clauses (شجرة clauses, تعداد c_omp_region_type ort)
{
  bitmap_head generic_head, firstprivate_head, lastprivate_head;
  bitmap_head aligned_head, map_head, map_field_head, map_firstprivate_head;
  bitmap_head oacc_reduction_head, is_on_device_head;
  شجرة c, t, type, *pc;
  شجرة simdlen = NULL_شجرة, safelen = NULL_شجرة;
  منطقي branch_seen = خطأ;
  منطقي copyprivate_seen = خطأ;
  منطقي mergeable_seen = خطأ;
  شجرة *detach_seen = عدم;
  منطقي linear_variable_step_check = خطأ;
  شجرة *nowait_clause = عدم;
  شجرة *grainsize_seen = عدم;
  منطقي رقم_tasks_seen = خطأ;
  شجرة ordered_clause = NULL_شجرة;
  شجرة schedule_clause = NULL_شجرة;
  منطقي oacc_async = خطأ;
  شجرة last_iterators = NULL_شجرة;
  منطقي last_iterators_remove = خطأ;
  شجرة *nogroup_seen = عدم;
  شجرة *order_clause = عدم;
  /* 1 if normal/task reduction has been seen, -1 if inscan reduction
     has been seen, -2 if mixed inscan/normal reduction diagnosed.  */
  صحيح reduction_seen = 0;
  منطقي allocate_seen = خطأ;
  منطقي implicit_moved = خطأ;
  منطقي target_in_reduction_seen = خطأ;
  شجرة *full_seen = عدم;
  منطقي partial_seen = خطأ;
  منطقي openacc = (ort & C_ORT_ACC) != 0;
  منطقي init_seen = خطأ;
  منطقي init_use_destroy_seen = خطأ;
  شجرة init_no_targetsync_clause = NULL_شجرة;
  شجرة depend_clause = NULL_شجرة;

  إذا (!openacc)
    clauses = omp_remove_duplicate_maps (clauses, true);

  bitmap_obstack_initialize (عدم);
  bitmap_initialize (&generic_head, &bitmap_default_obstack);
  bitmap_initialize (&firstprivate_head, &bitmap_default_obstack);
  bitmap_initialize (&lastprivate_head, &bitmap_default_obstack);
  bitmap_initialize (&aligned_head, &bitmap_default_obstack);
  /* If ort == C_ORT_OMP_DECLARE_SIMD used as uniform_head instead.  */
  bitmap_initialize (&map_head, &bitmap_default_obstack);
  bitmap_initialize (&map_field_head, &bitmap_default_obstack);
  bitmap_initialize (&map_firstprivate_head, &bitmap_default_obstack);
  /* If ort == C_ORT_OMP used as nontemporal_head or use_device_xxx_head
     instead and for ort == C_ORT_OMP_TARGET used as in_reduction_head.  */
  bitmap_initialize (&oacc_reduction_head, &bitmap_default_obstack);
  bitmap_initialize (&is_on_device_head, &bitmap_default_obstack);

  إذا (openacc)
    لكل (c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
      إذا (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ASYNC)
	{
	  oacc_async = true;
	  اكسر;
	}

  شجرة *grp_start_p = عدم, grp_sentinel = NULL_شجرة;

  لكل (pc = &clauses, c = clauses; c ; c = *pc)
    {
      منطقي remove = خطأ;
      منطقي need_complete = خطأ;
      منطقي need_implicitly_determined = خطأ;

      /* We've reached the end of a list of expanded nodes.  Reset the group
	 start pointer.  */
      إذا (c == grp_sentinel)
	{
	  إذا (grp_start_p
	      && OMP_CLAUSE_HAS_ITERATORS (*grp_start_p))
	    لكل (شجرة gc = *grp_start_p; gc != grp_sentinel;
		 gc = OMP_CLAUSE_CHAIN (gc))
	      OMP_CLAUSE_ITERATORS (gc) = OMP_CLAUSE_ITERATORS (*grp_start_p);
	  grp_start_p = عدم;
	}

      بدل (OMP_CLAUSE_CODE (c))
	{
	حالة OMP_CLAUSE_SHARED:
	  need_implicitly_determined = true;
	  اذهب check_dup_generic;

	حالة OMP_CLAUSE_PRIVATE:
	  need_complete = true;
	  need_implicitly_determined = true;
	  اذهب check_dup_generic;

	حالة OMP_CLAUSE_REDUCTION:
	  إذا (reduction_seen == 0)
	    reduction_seen = OMP_CLAUSE_REDUCTION_INSCAN (c) ? -1 : 1;
	  وإلا إذا (reduction_seen != -2
		   && reduction_seen != (OMP_CLAUSE_REDUCTION_INSCAN (c)
					 ? -1 : 1))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<inscan%> and non-%<inscan%> %<reduction%> clauses "
			"on the same construct");
	      reduction_seen = -2;
	    }
	  /* FALLTHRU */
	حالة OMP_CLAUSE_IN_REDUCTION:
	حالة OMP_CLAUSE_TASK_REDUCTION:
	  need_implicitly_determined = true;
	  t = OMP_CLAUSE_DECL (c);
	  إذا (شجرة_CODE (t) == OMP_ARRAY_SECTION)
	    {
	      إذا (handle_omp_array_sections (c, ort))
		{
		  remove = true;
		  اكسر;
		}

	      t = OMP_CLAUSE_DECL (c);
	      إذا (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
		  && OMP_CLAUSE_REDUCTION_INSCAN (c))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<inscan%> %<reduction%> clause with array "
			    "section");
		  remove = true;
		  اكسر;
		}
	    }
	  t = require_complete_type (OMP_CLAUSE_LOCATION (c), t);
	  إذا (t == error_mark_عقدة)
	    {
	      remove = true;
	      اكسر;
	    }
	  إذا (oacc_async)
	    c_mark_addressable (t);
	  type = شجرة_TYPE (t);
	  إذا (شجرة_CODE (t) == MEM_REF)
	    type = شجرة_TYPE (type);
	  إذا (شجرة_CODE (type) == ARRAY_TYPE)
	    {
	      شجرة oatype = type;
	      gcc_assert (شجرة_CODE (t) != MEM_REF);
	      طالما (شجرة_CODE (type) == ARRAY_TYPE)
		type = شجرة_TYPE (type);
	      إذا (integer_zerop (TYPE_SIZE_UNIT (type)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD in %<reduction%> clause is a zero size array",
			    t);
		  remove = true;
		  اكسر;
		}
	      شجرة size = size_binop (EXACT_DIV_تعبير, TYPE_SIZE_UNIT (oatype),
				      TYPE_SIZE_UNIT (type));
	      إذا (integer_zerop (size))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD in %<reduction%> clause is a zero size array",
			    t);
		  remove = true;
		  اكسر;
		}
	      size = size_binop (MINUS_تعبير, size, size_one_عقدة);
	      size = save_تعبير (size);
	      شجرة index_type = build_index_type (size);
	      شجرة atype = c_build_array_type (TYPE_MAIN_VARIANT (type),
					       index_type);
	      atype = c_build_qualified_type (atype, TYPE_QUALS (type));
	      شجرة ptype = c_build_pointer_type (type);
	      إذا (شجرة_CODE (شجرة_TYPE (t)) == ARRAY_TYPE)
		t = build_fold_addr_تعبير (t);
	      t = build2 (MEM_REF, atype, t, build_int_cst (ptype, 0));
	      OMP_CLAUSE_DECL (c) = t;
	    }
	  إذا (TYPE_ATOMIC (type))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<_Atomic%> %qE in %<reduction%> clause", t);
	      remove = true;
	      اكسر;
	    }
	  إذا (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_REDUCTION
	      || OMP_CLAUSE_REDUCTION_TASK (c))
	    {
	      /* Disallow zero sized or potentially zero sized task
		 reductions.  */
	      إذا (integer_zerop (TYPE_SIZE_UNIT (type)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "zero sized type %qT in %qs clause", type,
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  remove = true;
		  اكسر;
		}
	      وإلا إذا (شجرة_CODE (TYPE_SIZE_UNIT (type)) != INTEGER_CST)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "variable sized type %qT in %qs clause", type,
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  remove = true;
		  اكسر;
		}
	    }
	  إذا (OMP_CLAUSE_REDUCTION_PLACEHOLDER (c) == NULL_شجرة
	      && (FLOAT_TYPE_P (type)
		  || شجرة_CODE (type) == COMPLEX_TYPE))
	    {
	      تعداد شجرة_code r_code = OMP_CLAUSE_REDUCTION_CODE (c);
	      ثابت حرف *r_name = عدم;

	      بدل (r_code)
		{
		حالة PLUS_تعبير:
		حالة MULT_تعبير:
		حالة MINUS_تعبير:
		حالة TRUTH_ANDIF_تعبير:
		حالة TRUTH_ORIF_تعبير:
		  اكسر;
		حالة MIN_تعبير:
		  إذا (شجرة_CODE (type) == COMPLEX_TYPE)
		    r_name = "min";
		  اكسر;
		حالة MAX_تعبير:
		  إذا (شجرة_CODE (type) == COMPLEX_TYPE)
		    r_name = "max";
		  اكسر;
		حالة BIT_AND_تعبير:
		  r_name = "&";
		  اكسر;
		حالة BIT_XOR_تعبير:
		  r_name = "^";
		  اكسر;
		حالة BIT_IOR_تعبير:
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
		  remove = true;
		  اكسر;
		}
	    }
	  وإلا إذا (OMP_CLAUSE_REDUCTION_PLACEHOLDER (c) == error_mark_عقدة)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"user defined reduction not found for %qE", t);
	      remove = true;
	      اكسر;
	    }
	  وإلا إذا (OMP_CLAUSE_REDUCTION_PLACEHOLDER (c))
	    {
	      شجرة list = OMP_CLAUSE_REDUCTION_PLACEHOLDER (c);
	      type = TYPE_MAIN_VARIANT (type);
	      شجرة placeholder = build_decl (OMP_CLAUSE_LOCATION (c),
					     VAR_DECL, NULL_شجرة, type);
	      شجرة decl_placeholder = NULL_شجرة;
	      OMP_CLAUSE_REDUCTION_PLACEHOLDER (c) = placeholder;
	      DECL_ARTIFICIAL (placeholder) = 1;
	      DECL_IGNORED_P (placeholder) = 1;
	      إذا (شجرة_CODE (t) == MEM_REF)
		{
		  decl_placeholder = build_decl (OMP_CLAUSE_LOCATION (c),
						 VAR_DECL, NULL_شجرة, type);
		  OMP_CLAUSE_REDUCTION_DECL_PLACEHOLDER (c) = decl_placeholder;
		  DECL_ARTIFICIAL (decl_placeholder) = 1;
		  DECL_IGNORED_P (decl_placeholder) = 1;
		}
	      إذا (شجرة_ADDRESSABLE (شجرة_VEC_ELT (list, 0)))
		c_mark_addressable (placeholder);
	      إذا (شجرة_ADDRESSABLE (شجرة_VEC_ELT (list, 1)))
		c_mark_addressable (decl_placeholder ? decl_placeholder
				    : OMP_CLAUSE_DECL (c));
	      OMP_CLAUSE_REDUCTION_MERGE (c)
		= c_clone_omp_udr (شجرة_VEC_ELT (list, 2),
				   شجرة_VEC_ELT (list, 0),
				   شجرة_VEC_ELT (list, 1),
				   decl_placeholder ? decl_placeholder
				   : OMP_CLAUSE_DECL (c), placeholder);
	      OMP_CLAUSE_REDUCTION_MERGE (c)
		= build3_loc (OMP_CLAUSE_LOCATION (c), BIND_تعبير,
			      void_type_عقدة, NULL_شجرة,
			      OMP_CLAUSE_REDUCTION_MERGE (c), NULL_شجرة);
	      شجرة_SIDE_EFFECTS (OMP_CLAUSE_REDUCTION_MERGE (c)) = 1;
	      إذا (شجرة_VEC_LENGTH (list) == 6)
		{
		  إذا (شجرة_ADDRESSABLE (شجرة_VEC_ELT (list, 3)))
		    c_mark_addressable (decl_placeholder ? decl_placeholder
					: OMP_CLAUSE_DECL (c));
		  إذا (شجرة_ADDRESSABLE (شجرة_VEC_ELT (list, 4)))
		    c_mark_addressable (placeholder);
		  شجرة init = شجرة_VEC_ELT (list, 5);
		  إذا (init == error_mark_عقدة)
		    init = DECL_INITIAL (شجرة_VEC_ELT (list, 3));
		  OMP_CLAUSE_REDUCTION_INIT (c)
		    = c_clone_omp_udr (init, شجرة_VEC_ELT (list, 4),
				       شجرة_VEC_ELT (list, 3),
				       decl_placeholder ? decl_placeholder
				       : OMP_CLAUSE_DECL (c), placeholder);
		  إذا (شجرة_VEC_ELT (list, 5) == error_mark_عقدة)
		    {
		      شجرة v = decl_placeholder ? decl_placeholder : t;
		      OMP_CLAUSE_REDUCTION_INIT (c)
			= build2 (INIT_تعبير, شجرة_TYPE (v), v,
				  OMP_CLAUSE_REDUCTION_INIT (c));
		    }
		  إذا (walk_شجرة (&OMP_CLAUSE_REDUCTION_INIT (c),
				 c_find_omp_placeholder_r,
				 placeholder, عدم))
		    OMP_CLAUSE_REDUCTION_OMP_ORIG_REF (c) = 1;
		}
	      وإلا
		{
		  شجرة init;
		  شجرة v = decl_placeholder ? decl_placeholder : t;
		  إذا (AGGREGATE_TYPE_P (شجرة_TYPE (v)))
		    init = build_constructor (شجرة_TYPE (v), عدم);
		  وإلا
		    init = fold_convert (شجرة_TYPE (v), integer_zero_عقدة);
		  OMP_CLAUSE_REDUCTION_INIT (c)
		    = build2 (INIT_تعبير, شجرة_TYPE (v), v, init);
		}
	      OMP_CLAUSE_REDUCTION_INIT (c)
		= build3_loc (OMP_CLAUSE_LOCATION (c), BIND_تعبير,
			      void_type_عقدة, NULL_شجرة,
			       OMP_CLAUSE_REDUCTION_INIT (c), NULL_شجرة);
	      شجرة_SIDE_EFFECTS (OMP_CLAUSE_REDUCTION_INIT (c)) = 1;
	    }
	  إذا (شجرة_CODE (t) == MEM_REF)
	    {
	      إذا (TYPE_SIZE_UNIT (شجرة_TYPE (شجرة_TYPE (t))) == NULL_شجرة
		  || شجرة_CODE (TYPE_SIZE_UNIT (شجرة_TYPE (شجرة_TYPE (t))))
		     != INTEGER_CST)
		{
		  sorry ("variable length element type in array "
			 "%<reduction%> clause");
		  remove = true;
		  اكسر;
		}
	      t = شجرة_OPERAND (t, 0);
	      إذا (شجرة_CODE (t) == POINTER_PLUS_تعبير)
		t = شجرة_OPERAND (t, 0);
	      إذا (شجرة_CODE (t) == ADDR_تعبير)
		t = شجرة_OPERAND (t, 0);
	    }
	  اذهب check_dup_generic_t;

	حالة OMP_CLAUSE_COPYPRIVATE:
	  copyprivate_seen = true;
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
	      remove = true;
	      اكسر;
	    }
	  اذهب check_dup_generic;

	حالة OMP_CLAUSE_LINEAR:
	  إذا (ort != C_ORT_OMP_DECLARE_SIMD)
	    need_implicitly_determined = true;
	  t = OMP_CLAUSE_DECL (c);
	  إذا (ort != C_ORT_OMP_DECLARE_SIMD
	      && OMP_CLAUSE_LINEAR_KIND (c) != OMP_CLAUSE_LINEAR_DEFAULT
	      && OMP_CLAUSE_LINEAR_OLD_LINEAR_MODIFIER (c))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"modifier should not be specified in %<linear%> "
			"clause on %<simd%> or %<for%> constructs when not "
			"using OpenMP 5.2 modifiers");
	      OMP_CLAUSE_LINEAR_KIND (c) = OMP_CLAUSE_LINEAR_DEFAULT;
	    }
	  إذا (!INTEGRAL_TYPE_P (شجرة_TYPE (t))
	      && شجرة_CODE (شجرة_TYPE (t)) != POINTER_TYPE)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"linear clause applied to non-integral non-pointer "
			"variable with type %qT", شجرة_TYPE (t));
	      remove = true;
	      اكسر;
	    }
	  إذا (TYPE_ATOMIC (شجرة_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<_Atomic%> %qD in %<linear%> clause", t);
	      remove = true;
	      اكسر;
	    }
	  إذا (ort == C_ORT_OMP_DECLARE_SIMD)
	    {
	      شجرة s = OMP_CLAUSE_LINEAR_STEP (c);
	      إذا (شجرة_CODE (s) == PARM_DECL)
		{
		  OMP_CLAUSE_LINEAR_VARIABLE_STRIDE (c) = 1;
		  /* map_head bitmap is used as uniform_head if
		     declare_simd.  */
		  إذا (!bitmap_bit_p (&map_head, DECL_UID (s)))
		    linear_variable_step_check = true;
		  اذهب check_dup_generic;
		}
	      إذا (شجرة_CODE (s) != INTEGER_CST)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<linear%> clause step %qE is neither constant "
			    "nor a parameter", s);
		  remove = true;
		  اكسر;
		}
	    }
	  إذا (شجرة_CODE (شجرة_TYPE (OMP_CLAUSE_DECL (c))) == POINTER_TYPE)
	    {
	      شجرة s = OMP_CLAUSE_LINEAR_STEP (c);
	      s = pointer_int_sum (OMP_CLAUSE_LOCATION (c), PLUS_تعبير,
				   OMP_CLAUSE_DECL (c), s);
	      s = fold_build2_loc (OMP_CLAUSE_LOCATION (c), MINUS_تعبير,
				   sizetype, fold_convert (sizetype, s),
				   fold_convert
				     (sizetype, OMP_CLAUSE_DECL (c)));
	      إذا (s == error_mark_عقدة)
		s = size_one_عقدة;
	      OMP_CLAUSE_LINEAR_STEP (c) = s;
	    }
	  وإلا
	    OMP_CLAUSE_LINEAR_STEP (c)
	      = fold_convert (شجرة_TYPE (t), OMP_CLAUSE_LINEAR_STEP (c));
	  اذهب check_dup_generic;

	check_dup_generic:
	  t = OMP_CLAUSE_DECL (c);
	check_dup_generic_t:
	  إذا (!VAR_P (t) && شجرة_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %qs", t,
			omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	      remove = true;
	    }
	  وإلا إذا ((openacc && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION)
		   || (ort == C_ORT_OMP
		       && (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_USE_DEVICE_PTR
			   || (OMP_CLAUSE_CODE (c)
			       == OMP_CLAUSE_USE_DEVICE_ADDR)))
		   || (ort == C_ORT_OMP_TARGET
		       && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION))
	    {
	      إذا (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
		  && (bitmap_bit_p (&generic_head, DECL_UID (t))
		      || bitmap_bit_p (&firstprivate_head, DECL_UID (t))))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in data-sharing "
			    "clauses", t);
		  remove = true;
		  اكسر;
		}
	      إذا (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION)
		target_in_reduction_seen = true;
	      إذا (bitmap_bit_p (&oacc_reduction_head, DECL_UID (t)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    openacc
			    ? "%qD appears more than once in reduction clauses"
			    : "%qD appears more than once in data clauses",
			    t);
		  remove = true;
		}
	      وإلا
		bitmap_set_bit (&oacc_reduction_head, DECL_UID (t));
	    }
	  وإلا إذا (bitmap_bit_p (&generic_head, DECL_UID (t))
		   || bitmap_bit_p (&firstprivate_head, DECL_UID (t))
		   || bitmap_bit_p (&lastprivate_head, DECL_UID (t))
		   || bitmap_bit_p (&map_firstprivate_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in data clauses", t);
	      remove = true;
	    }
	  وإلا إذا ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_PRIVATE
		    || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_HAS_DEVICE_ADDR
		    || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IS_DEVICE_PTR)
		   && bitmap_bit_p (&map_head, DECL_UID (t)))
	    {
	      إذا (openacc)
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears more than once in data clauses", t);
	      وإلا
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears both in data and map clauses", t);
	      remove = true;
	    }
	  وإلا
	    bitmap_set_bit (&generic_head, DECL_UID (t));
	  اكسر;

	حالة OMP_CLAUSE_FIRSTPRIVATE:
	  إذا (OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (c) && !implicit_moved)
	    {
	    move_implicit:
	      implicit_moved = true;
	      /* Move firstprivate and map clauses with
		 OMP_CLAUSE_{FIRSTPRIVATE,MAP}_IMPLICIT set to the end of
		 clauses chain.  */
	      شجرة cl1 = NULL_شجرة, cl2 = NULL_شجرة;
	      شجرة *pc1 = pc, *pc2 = &cl1, *pc3 = &cl2;
	      طالما (*pc1)
		إذا (OMP_CLAUSE_CODE (*pc1) == OMP_CLAUSE_FIRSTPRIVATE
		    && OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (*pc1))
		  {
		    *pc3 = *pc1;
		    pc3 = &OMP_CLAUSE_CHAIN (*pc3);
		    *pc1 = OMP_CLAUSE_CHAIN (*pc1);
		  }
		وإلا إذا (OMP_CLAUSE_CODE (*pc1) == OMP_CLAUSE_MAP
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
	  need_complete = true;
	  need_implicitly_determined = true;
	  إذا (!VAR_P (t) && شجرة_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %<firstprivate%>", t);
	      remove = true;
	    }
	  وإلا إذا (OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (c)
		   && !OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT_TARGET (c)
		   && bitmap_bit_p (&map_firstprivate_head, DECL_UID (t)))
	    remove = true;
	  وإلا إذا (bitmap_bit_p (&generic_head, DECL_UID (t))
		   || bitmap_bit_p (&firstprivate_head, DECL_UID (t))
		   || bitmap_bit_p (&map_firstprivate_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in data clauses", t);
	      remove = true;
	    }
	  وإلا إذا (bitmap_bit_p (&map_head, DECL_UID (t))
		   || bitmap_bit_p (&map_field_head, DECL_UID (t)))
	    {
	      إذا (openacc)
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears more than once in data clauses", t);
	      وإلا إذا (OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (c)
		       && !OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT_TARGET (c))
		/* Silently drop the clause.  */;
	      وإلا
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears both in data and map clauses", t);
	      remove = true;
	    }
	  وإلا
	    bitmap_set_bit (&firstprivate_head, DECL_UID (t));
	  اكسر;

	حالة OMP_CLAUSE_LASTPRIVATE:
	  t = OMP_CLAUSE_DECL (c);
	  need_complete = true;
	  need_implicitly_determined = true;
	  إذا (!VAR_P (t) && شجرة_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %<lastprivate%>", t);
	      remove = true;
	    }
	  وإلا إذا (bitmap_bit_p (&generic_head, DECL_UID (t))
		   || bitmap_bit_p (&lastprivate_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
		     "%qE appears more than once in data clauses", t);
	      remove = true;
	    }
	  وإلا
	    bitmap_set_bit (&lastprivate_head, DECL_UID (t));
	  اكسر;

	حالة OMP_CLAUSE_ALIGNED:
	  t = OMP_CLAUSE_DECL (c);
	  إذا (!VAR_P (t) && شجرة_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in %<aligned%> clause", t);
	      remove = true;
	    }
	  وإلا إذا (!POINTER_TYPE_P (شجرة_TYPE (t))
		   && شجرة_CODE (شجرة_TYPE (t)) != ARRAY_TYPE)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE in %<aligned%> clause is neither a pointer nor "
			"an array", t);
	      remove = true;
	    }
	  وإلا إذا (TYPE_ATOMIC (شجرة_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<_Atomic%> %qD in %<aligned%> clause", t);
	      remove = true;
	      اكسر;
	    }
	  وإلا إذا (bitmap_bit_p (&aligned_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in %<aligned%> clauses",
			t);
	      remove = true;
	    }
	  وإلا
	    bitmap_set_bit (&aligned_head, DECL_UID (t));
	  اكسر;

	حالة OMP_CLAUSE_NONTEMPORAL:
	  t = OMP_CLAUSE_DECL (c);
	  إذا (!VAR_P (t) && شجرة_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in %<nontemporal%> clause", t);
	      remove = true;
	    }
	  وإلا إذا (bitmap_bit_p (&oacc_reduction_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in %<nontemporal%> "
			"clauses", t);
	      remove = true;
	    }
	  وإلا
	    bitmap_set_bit (&oacc_reduction_head, DECL_UID (t));
	  اكسر;

	حالة OMP_CLAUSE_ALLOCATE:
	  t = OMP_CLAUSE_DECL (c);
	  إذا (!VAR_P (t) && شجرة_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in %<allocate%> clause", t);
	      remove = true;
	    }
	  وإلا إذا (bitmap_bit_p (&aligned_head, DECL_UID (t)))
	    {
	      warning_at (OMP_CLAUSE_LOCATION (c), OPT_Wopenmp,
			  "%qE appears more than once in %<allocate%> clauses",
			  t);
	      remove = true;
	    }
	  وإلا
	    {
	      bitmap_set_bit (&aligned_head, DECL_UID (t));
	      إذا (!OMP_CLAUSE_ALLOCATE_COMBINED (c))
		allocate_seen = true;
	    }
	  اكسر;

	حالة OMP_CLAUSE_DOACROSS:
	  t = OMP_CLAUSE_DECL (c);
	  إذا (t == NULL_شجرة)
	    اكسر;
	  إذا (OMP_CLAUSE_DOACROSS_KIND (c) == OMP_CLAUSE_DOACROSS_SINK)
	    {
	      gcc_assert (شجرة_CODE (t) == شجرة_LIST);
	      لكل (; t; t = شجرة_CHAIN (t))
		{
		  شجرة decl = شجرة_قيمة (t);
		  إذا (شجرة_CODE (شجرة_TYPE (decl)) == POINTER_TYPE)
		    {
		      شجرة offset = شجرة_PURPOSE (t);
		      منطقي neg = wi::neg_p (wi::to_wide (offset));
		      offset = fold_unary (ABS_تعبير, شجرة_TYPE (offset), offset);
		      شجرة t2 = pointer_int_sum (OMP_CLAUSE_LOCATION (c),
						 neg ? MINUS_تعبير : PLUS_تعبير,
						 decl, offset);
		      t2 = fold_build2_loc (OMP_CLAUSE_LOCATION (c), MINUS_تعبير,
					    sizetype,
					    fold_convert (sizetype, t2),
					    fold_convert (sizetype, decl));
		      إذا (t2 == error_mark_عقدة)
			{
			  remove = true;
			  اكسر;
			}
		      شجرة_PURPOSE (t) = t2;
		    }
		}
	      اكسر;
	    }
	  gcc_unreachable ();

	حالة OMP_CLAUSE_USES_ALLOCATORS:
	  t = OMP_CLAUSE_USES_ALLOCATORS_ALLOCATOR (c);
	  إذا (t == error_mark_عقدة)
	    {
	      remove = true;
	      اكسر;
	    }
	  إذا ((VAR_P (t) || شجرة_CODE (t) == PARM_DECL)
	      && (bitmap_bit_p (&generic_head, DECL_UID (t))
		  || bitmap_bit_p (&map_head, DECL_UID (t))
		  || bitmap_bit_p (&firstprivate_head, DECL_UID (t))
		  || bitmap_bit_p (&lastprivate_head, DECL_UID (t))))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in data clauses", t);
	      remove = true;
	      اكسر;
	    }
	  وإلا
	    bitmap_set_bit (&generic_head, DECL_UID (t));
	  إذا (شجرة_CODE (شجرة_TYPE (t)) != ENUMERAL_TYPE
	      || strcmp (IDENTIFIER_POINTER (TYPE_IDENTIFIER (شجرة_TYPE (t))),
			 "omp_allocator_handle_t") != 0)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"allocator %qE must be of %<omp_allocator_handle_t%> "
			"type", t);
	      remove = true;
	      اكسر;
	    }
	  شجرة init;
	  إذا (!DECL_P (t)
	      || (شجرة_CODE (t) == CONST_DECL
		  && ((init = DECL_INITIAL(t)) == nullptr
		      || شجرة_CODE (init) != INTEGER_CST
		      || ((wi::to_widest (init) < 0
			   || wi::to_widest (init) > GOMP_OMP_PREDEF_ALLOC_MAX)
			  && (wi::to_widest (init) < GOMP_OMPX_PREDEF_ALLOC_MIN
			      || (wi::to_widest (init)
				  > GOMP_OMPX_PREDEF_ALLOC_MAX))))))
	    {
	      remove = true;
	      error_at (OMP_CLAUSE_LOCATION (c),
			"allocator %qE must be either a variable or a "
			"predefined allocator", t);
	      اكسر;
	    }
	  وإلا إذا (شجرة_CODE (t) == CONST_DECL)
	    {
	      /* omp_null_allocator is ignored and for predefined allocators,
		 no special handling is required; thus, mark them removed. */
	      remove = true;

	      إذا (OMP_CLAUSE_USES_ALLOCATORS_MEMSPACE (c)
		  || OMP_CLAUSE_USES_ALLOCATORS_TRAITS (c))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "modifiers cannot be used with predefined "
			    "allocator %qE", t);
		  اكسر;
		}
	    }
	  t = OMP_CLAUSE_USES_ALLOCATORS_MEMSPACE (c);
	  إذا (t == error_mark_عقدة)
	    {
	      remove = true;
	      اكسر;
	    }
	  إذا (t != NULL_شجرة
	      && ((شجرة_CODE (t) != CONST_DECL && شجرة_CODE (t) != INTEGER_CST)
		  || شجرة_CODE (شجرة_TYPE (t)) != ENUMERAL_TYPE
		  || strcmp (IDENTIFIER_POINTER (TYPE_IDENTIFIER (شجرة_TYPE (t))),
			     "omp_memspace_handle_t") != 0))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c), "memspace modifier %qE must be"
			" constant enum of %<omp_memspace_handle_t%> type", t);
	      remove = true;
	      اكسر;
	    }
	  t = OMP_CLAUSE_USES_ALLOCATORS_TRAITS (c);
	  إذا (t == error_mark_عقدة)
	    {
	      remove = true;
	      اكسر;
	    }
	  إذا (t != NULL_شجرة
	      && t != error_mark_عقدة
	      && (DECL_EXTERNAL (t)
		  || شجرة_CODE (t) == PARM_DECL))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c), "traits array %qE must be "
			"defined in same scope as the construct on which the "
			"clause appears", t);
	      remove = true;
	    }
	  إذا (t != NULL_شجرة)
	    {
	      منطقي type_err = خطأ;

	      إذا (شجرة_CODE (شجرة_TYPE (t)) != ARRAY_TYPE
		  || DECL_SIZE (t) == NULL_شجرة
		  || !COMPLETE_TYPE_P (شجرة_TYPE (t)))
		type_err = true;
	      وإلا
		{
		  شجرة elem_t = شجرة_TYPE (شجرة_TYPE (t));
		  إذا (شجرة_CODE (elem_t) != RECORD_TYPE
		      || strcmp (IDENTIFIER_POINTER (TYPE_IDENTIFIER (elem_t)),
				 "omp_alloctrait_t") != 0
		      || !TYPE_READONLY (elem_t))
		    type_err = true;
		}
	      إذا (type_err)
		{
		  إذا (t != error_mark_عقدة)
		    error_at (OMP_CLAUSE_LOCATION (c), "traits array %qE must "
			      "be of %<const omp_alloctrait_t []%> type", t);
		  وإلا
		    error_at (OMP_CLAUSE_LOCATION (c), "traits array must "
			      "be of %<const omp_alloctrait_t []%> type");
		  remove = true;
		}
	      وإلا
		{
		  شجرة cst_val = decl_constant_قيمة_1 (t, true);
		  إذا (cst_val == t)
		    {
		      error_at (OMP_CLAUSE_LOCATION (c), "traits array must be "
				"initialized with constants");

		      remove = true;
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
	      إذا (شجرة_PURPOSE (t) != last_iterators)
		last_iterators_remove
		  = c_omp_finish_iterators (شجرة_PURPOSE (t));
	      last_iterators = شجرة_PURPOSE (t);
	      t = شجرة_قيمة (t);
	      إذا (last_iterators_remove)
		t = error_mark_عقدة;
	    }
	  وإلا
	    last_iterators = NULL_شجرة;
	  إذا (شجرة_CODE (t) == OMP_ARRAY_SECTION)
	    {
	      إذا (handle_omp_array_sections (c, ort))
		remove = true;
	      وإلا إذا (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
		       && OMP_CLAUSE_DEPEND_KIND (c) == OMP_CLAUSE_DEPEND_DEPOBJ)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<depend%> clause with %<depobj%> dependence "
			    "type on array section");
		  remove = true;
		}
	      اكسر;
	    }
	  إذا (t == error_mark_عقدة)
	    remove = true;
	  وإلا إذا (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
		   && t == ridpointers[RID_OMP_ALL_MEMORY])
	    {
	      إذا (OMP_CLAUSE_DEPEND_KIND (c) != OMP_CLAUSE_DEPEND_OUT
		  && OMP_CLAUSE_DEPEND_KIND (c) != OMP_CLAUSE_DEPEND_INOUT)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<omp_all_memory%> used with %<depend%> kind "
			    "other than %<out%> or %<inout%>");
		  remove = true;
		}
	    }
	  وإلا إذا (!lvalue_p (t))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not lvalue expression nor array section in "
			"%qs clause", t,
			omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	      remove = true;
	    }
	  وإلا إذا (شجرة_CODE (t) == COMPONENT_REF
		   && DECL_C_BIT_FIELD (شجرة_OPERAND (t, 1)))
	    {
	      gcc_assert (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
			  || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY);
	      error_at (OMP_CLAUSE_LOCATION (c),
			"bit-field %qE in %qs clause", t,
			omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	      remove = true;
	    }
	  وإلا إذا (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
		   && OMP_CLAUSE_DEPEND_KIND (c) == OMP_CLAUSE_DEPEND_DEPOBJ)
	    {
	      إذا (!c_omp_depend_t_p (شجرة_TYPE (t)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qE does not have %<omp_depend_t%> type in "
			    "%<depend%> clause with %<depobj%> dependence "
			    "type", t);
		  remove = true;
		}
	    }
	  وإلا إذا (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
		   && c_omp_depend_t_p (شجرة_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE should not have %<omp_depend_t%> type in "
			"%<depend%> clause with dependence type other than "
			"%<depobj%>", t);
	      remove = true;
	    }
	  إذا (!remove)
	    {
	      إذا (t == ridpointers[RID_OMP_ALL_MEMORY])
		t = null_pointer_عقدة;
	      وإلا
		{
		  شجرة addr = build_unary_op (OMP_CLAUSE_LOCATION (c),
					      ADDR_تعبير, t, خطأ);
		  إذا (addr == error_mark_عقدة)
		    {
		      remove = true;
		      اكسر;
		    }
		  t = build_indirect_ref (OMP_CLAUSE_LOCATION (c), addr,
					  RO_UNARY_STAR);
		  إذا (t == error_mark_عقدة)
		    {
		      remove = true;
		      اكسر;
		    }
		}
	      إذا (OMP_ITERATOR_DECL_P (OMP_CLAUSE_DECL (c)))
		شجرة_قيمة (OMP_CLAUSE_DECL (c)) = t;
	      وإلا
		OMP_CLAUSE_DECL (c) = t;
	    }
	  اكسر;

	حالة OMP_CLAUSE_MAP:
	  إذا (OMP_CLAUSE_MAP_IMPLICIT (c) && !implicit_moved)
	    اذهب move_implicit;
	  إذا (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_ادفع_MAPPER_NAME
	      || OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_اسحب_MAPPER_NAME)
	    {
	      remove = true;
	      اكسر;
	    }
	  /* FALLTHRU */
	حالة OMP_CLAUSE_TO:
	حالة OMP_CLAUSE_FROM:
	  إذا (OMP_CLAUSE_ITERATORS (c)
	      && c_omp_finish_iterators (OMP_CLAUSE_ITERATORS (c)))
	    {
	      t = error_mark_عقدة;
	      اكسر;
	    }
	  /* FALLTHRU */
	حالة OMP_CLAUSE__CACHE_:
	  {
	    using نطاق omp_addr_tokenizer;
	    auto_vec<omp_addr_token *, 10> addr_tokens;

	    t = OMP_CLAUSE_DECL (c);
	    إذا (شجرة_CODE (t) == OMP_ARRAY_SECTION)
	      {
		grp_start_p = pc;
		grp_sentinel = OMP_CLAUSE_CHAIN (c);

		إذا (handle_omp_array_sections (c, ort))
		  remove = true;
		وإلا
		  {
		    t = OMP_CLAUSE_DECL (c);
		    إذا (!omp_mappable_type (شجرة_TYPE (t)))
		      {
			error_at (OMP_CLAUSE_LOCATION (c),
				  "array section does not have mappable type "
				  "in %qs clause",
				  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
			remove = true;
		      }
		    وإلا إذا (TYPE_ATOMIC (شجرة_TYPE (t)))
		      {
			error_at (OMP_CLAUSE_LOCATION (c),
				  "%<_Atomic%> %qE in %qs clause", t,
				  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
			remove = true;
		      }
		    طالما (شجرة_CODE (t) == ARRAY_REF)
		      t = شجرة_OPERAND (t, 0);

		    c_omp_address_inspector ai (OMP_CLAUSE_LOCATION (c), t);

		    إذا (!omp_parse_تعبير (addr_tokens, t))
		      {
			sorry_at (OMP_CLAUSE_LOCATION (c),
				  "unsupported map expression %qE",
				  OMP_CLAUSE_DECL (c));
			remove = true;
			اكسر;
		      }

		    /* This check is to determine if this will be the only map
		       node created for this clause.  Otherwise, we'll check
		       the following FIRSTPRIVATE_POINTER or ATTACH_DETACH
		       node on the next iteration(s) of the loop.   */
		    إذا (addr_tokens.length () >= 4
			&& addr_tokens[0]->type == STRUCTURE_BASE
			&& addr_tokens[0]->u.structure_base_kind == BASE_DECL
			&& addr_tokens[1]->type == ACCESS_METHOD
			&& addr_tokens[2]->type == COMPONENT_SELECTOR
			&& addr_tokens[3]->type == ACCESS_METHOD
			&& (addr_tokens[3]->u.access_kind == ACCESS_DIRECT
			    || (addr_tokens[3]->u.access_kind
				== ACCESS_INDEXED_ARRAY)))
		      {
			شجرة rt = addr_tokens[1]->تعبير;

			gcc_assert (DECL_P (rt));

			إذا (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
			    && OMP_CLAUSE_MAP_IMPLICIT (c)
			    && (bitmap_bit_p (&map_head, DECL_UID (rt))
				|| bitmap_bit_p (&map_field_head, DECL_UID (rt))
				|| bitmap_bit_p (&map_firstprivate_head,
						 DECL_UID (rt))))
			  {
			    remove = true;
			    اكسر;
			  }
			إذا (bitmap_bit_p (&map_field_head, DECL_UID (rt)))
			  اكسر;
			إذا (bitmap_bit_p (&map_head, DECL_UID (rt)))
			  {
			    إذا (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP)
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
			    remove = true;
			  }
			وإلا
			  {
			    bitmap_set_bit (&map_head, DECL_UID (rt));
			    bitmap_set_bit (&map_field_head, DECL_UID (rt));
			  }
		      }
		  }
		إذا (c_oacc_check_attachments (c))
		  remove = true;
		إذا (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		    && (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_ATTACH
			|| OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_DETACH)
		    && !OMP_CLAUSE_SIZE (c))
		  /* In this case, we have a single array element which is a
		     pointer, and we already set OMP_CLAUSE_SIZE in
		     handle_omp_array_sections above.  For attach/detach
		     clauses, reset the OMP_CLAUSE_SIZE (representing a bias)
		     to zero here.  */
		  OMP_CLAUSE_SIZE (c) = size_zero_عقدة;
		اكسر;
	      }
	    وإلا إذا (!omp_parse_تعبير (addr_tokens, t))
	      {
		sorry_at (OMP_CLAUSE_LOCATION (c),
			  "unsupported map expression %qE",
			  OMP_CLAUSE_DECL (c));
		remove = true;
		اكسر;
	      }
	    إذا (t == error_mark_عقدة)
	      {
		remove = true;
		اكسر;
	      }

	    شجرة attr;
	    إذا (DECL_P (t)
		&& OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		&& (attr = lookup_attribute ("omp declare target",
					     DECL_ATTRIBUTES (t)))
		&& قيمة_member (get_identifier ("local"),
				 شجرة_قيمة (attr)))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "device-local variable %qD cannot appear "
			  "in map clause", t);
		remove = true;
		اكسر;
	      }

	    /* OpenACC attach / detach clauses must be pointers.  */
	    إذا (c_oacc_check_attachments (c))
	      {
		remove = true;
		اكسر;
	      }
	    إذا (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		&& (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_ATTACH
		    || OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_DETACH)
		&& !OMP_CLAUSE_SIZE (c))
	      /* For attach/detach clauses, set OMP_CLAUSE_SIZE (representing a
		 bias) to zero here, so it is not set erroneously to the pointer
		 size later on in gimplify.cc.  */
	      OMP_CLAUSE_SIZE (c) = size_zero_عقدة;

	    c_omp_address_inspector ai (OMP_CLAUSE_LOCATION (c), t);

	    إذا (!ai.check_clause (c))
	      {
		remove = true;
		اكسر;
	      }

	    إذا (!ai.map_supported_p ())
	      {
		sorry_at (OMP_CLAUSE_LOCATION (c),
			  "unsupported map expression %qE",
			  OMP_CLAUSE_DECL (c));
		remove = true;
		اكسر;
	      }

	    gcc_assert ((addr_tokens[0]->type == ARRAY_BASE
			 || addr_tokens[0]->type == STRUCTURE_BASE)
			&& addr_tokens[1]->type == ACCESS_METHOD);

	    t = addr_tokens[1]->تعبير;

	    إذا (addr_tokens[0]->u.structure_base_kind != BASE_DECL)
	      اذهب skip_decl_checks;

	    /* For OpenMP, we can access a struct "t" and "t.d" on the same
	       mapping.  OpenACC allows multiple fields of the same structure
	       to be written.  */
	    إذا (addr_tokens[0]->type == STRUCTURE_BASE
		&& (bitmap_bit_p (&map_field_head, DECL_UID (t))
		    || (!openacc && bitmap_bit_p (&map_head, DECL_UID (t)))))
	      اذهب skip_decl_checks;

	    إذا (!VAR_P (t) && شجرة_CODE (t) != PARM_DECL)
	      {
		إذا (ort != C_ORT_ACC && تعبير_P (t))
		  اكسر;

		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is not a variable in %qs clause", t,
			  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		remove = true;
	      }
	    وإلا إذا (VAR_P (t) && DECL_THREAD_LOCAL_P (t))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD is threadprivate variable in %qs clause", t,
			  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		remove = true;
	      }
	    وإلا إذا ((OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP
		      || (OMP_CLAUSE_MAP_KIND (c)
			  != GOMP_MAP_FIRSTPRIVATE_POINTER))
		     && !c_mark_addressable (t))
	      remove = true;
	    وإلا إذا (!(OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		       && (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_POINTER
			   || (OMP_CLAUSE_MAP_KIND (c)
			       == GOMP_MAP_FIRSTPRIVATE_POINTER)
			   || (OMP_CLAUSE_MAP_KIND (c)
			       == GOMP_MAP_FORCE_DEVICEPTR)))
		     && t == OMP_CLAUSE_DECL (c)
		     && !omp_mappable_type (شجرة_TYPE (t)))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD does not have a mappable type in %qs clause", t,
			  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		remove = true;
	      }
	    وإلا إذا (شجرة_TYPE (t) == error_mark_عقدة)
	      remove = true;
	    وإلا إذا (TYPE_ATOMIC (strip_array_types (شجرة_TYPE (t))))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%<_Atomic%> %qE in %qs clause", t,
			  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		remove = true;
	      }
	    وإلا إذا (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		     && OMP_CLAUSE_MAP_IMPLICIT (c)
		     && (bitmap_bit_p (&map_head, DECL_UID (t))
			 || bitmap_bit_p (&map_field_head, DECL_UID (t))
			 || bitmap_bit_p (&map_firstprivate_head,
					  DECL_UID (t))))
	      remove = true;
	    وإلا إذا (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		     && (OMP_CLAUSE_MAP_KIND (c)
			 == GOMP_MAP_FIRSTPRIVATE_POINTER))
	      {
		إذا (bitmap_bit_p (&generic_head, DECL_UID (t))
		    || bitmap_bit_p (&firstprivate_head, DECL_UID (t))
		    || bitmap_bit_p (&map_firstprivate_head, DECL_UID (t)))
		  {
		    error_at (OMP_CLAUSE_LOCATION (c),
			      "%qD appears more than once in data clauses", t);
		    remove = true;
		  }
		وإلا إذا (bitmap_bit_p (&map_head, DECL_UID (t))
			 && !bitmap_bit_p (&map_field_head, DECL_UID (t))
			 && openacc)
		  {
		    error_at (OMP_CLAUSE_LOCATION (c),
			      "%qD appears more than once in data clauses", t);
		    remove = true;
		  }
		وإلا
		  bitmap_set_bit (&map_firstprivate_head, DECL_UID (t));
	      }
	    وإلا إذا (bitmap_bit_p (&map_head, DECL_UID (t))
		     && !bitmap_bit_p (&map_field_head, DECL_UID (t))
		     && ort != C_ORT_OMP
		     && ort != C_ORT_OMP_TARGET
		     && ort != C_ORT_OMP_EXIT_DATA)
	      {
		إذا (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP)
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in motion clauses", t);
		وإلا إذا (openacc)
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in data clauses", t);
		وإلا
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in map clauses", t);
		remove = true;
	      }
	    وإلا إذا (openacc && bitmap_bit_p (&generic_head, DECL_UID (t)))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears more than once in data clauses", t);
		remove = true;
	      }
	    وإلا إذا (bitmap_bit_p (&firstprivate_head, DECL_UID (t))
		     || bitmap_bit_p (&is_on_device_head, DECL_UID (t)))
	      {
		إذا (openacc)
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in data clauses", t);
		وإلا
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears both in data and map clauses", t);
		remove = true;
	      }
	    وإلا إذا (!omp_access_chain_p (addr_tokens, 1))
	      {
		bitmap_set_bit (&map_head, DECL_UID (t));
		إذا (t != OMP_CLAUSE_DECL (c)
		    && شجرة_CODE (OMP_CLAUSE_DECL (c)) == COMPONENT_REF)
		  bitmap_set_bit (&map_field_head, DECL_UID (t));
	      }

	  skip_decl_checks:
	    /* If we call omp_expand_map_clause in handle_omp_array_sections,
	       the containing loop (here) iterates through the new nodes
	       created by that expansion.  Avoid expanding those again (just
	       by checking the node type).  */
	    إذا (!remove
		&& ort != C_ORT_DECLARE_SIMD
		&& (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP
		    || (OMP_CLAUSE_MAP_KIND (c) != GOMP_MAP_FIRSTPRIVATE_POINTER
			&& (OMP_CLAUSE_MAP_KIND (c)
			    != GOMP_MAP_FIRSTPRIVATE_REFERENCE)
			&& OMP_CLAUSE_MAP_KIND (c) != GOMP_MAP_ALWAYS_POINTER
			&& OMP_CLAUSE_MAP_KIND (c) != GOMP_MAP_ATTACH_DETACH
			&& OMP_CLAUSE_MAP_KIND (c) != GOMP_MAP_ATTACH
			&& OMP_CLAUSE_MAP_KIND (c) != GOMP_MAP_DETACH)))
	      {
		grp_start_p = pc;
		grp_sentinel = OMP_CLAUSE_CHAIN (c);
		شجرة nc = ai.expand_map_clause (c, OMP_CLAUSE_DECL (c),
						addr_tokens, ort);
		إذا (nc != error_mark_عقدة)
		  c = nc;
	      }
	  }
	  اكسر;

	حالة OMP_CLAUSE_ENTER:
	حالة OMP_CLAUSE_LINK:
	حالة OMP_CLAUSE_LOCAL:
	  t = OMP_CLAUSE_DECL (c);
	  ثابت حرف *cname;
	  cname = omp_clause_code_name[OMP_CLAUSE_CODE (c)];
	  إذا (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ENTER
	      && OMP_CLAUSE_ENTER_TO (c))
	    cname = "to";
	  إذا (شجرة_CODE (t) == FUNCTION_DECL
	      && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ENTER)
	    ;
	  وإلا إذا (!VAR_P (t))
	    {
	      إذا (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ENTER)
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is neither a variable nor a function name in "
			  "clause %qs", t, cname);
	      وإلا
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is not a variable in clause %qs", t, cname);
	      remove = true;
	    }
	  وإلا إذا (DECL_THREAD_LOCAL_P (t))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD is threadprivate variable in %qs clause", t,
			cname);
	      remove = true;
	    }
	  وإلا إذا (!omp_mappable_type (شجرة_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD does not have a mappable type in %qs clause", t,
			cname);
	      remove = true;
	    }
	  إذا (remove)
	    اكسر;
	  إذا (bitmap_bit_p (&generic_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once on the same "
			"%<declare target%> directive", t);
	      remove = true;
	    }
	  وإلا
	    bitmap_set_bit (&generic_head, DECL_UID (t));
	  اكسر;

	حالة OMP_CLAUSE_UNIFORM:
	  t = OMP_CLAUSE_DECL (c);
	  إذا (شجرة_CODE (t) != PARM_DECL)
	    {
	      إذا (DECL_P (t))
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD is not an argument in %<uniform%> clause", t);
	      وإلا
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is not an argument in %<uniform%> clause", t);
	      remove = true;
	      اكسر;
	    }
	  /* map_head bitmap is used as uniform_head if declare_simd.  */
	  bitmap_set_bit (&map_head, DECL_UID (t));
	  اذهب check_dup_generic;

	حالة OMP_CLAUSE_IS_DEVICE_PTR:
	حالة OMP_CLAUSE_USE_DEVICE_PTR:
	  t = OMP_CLAUSE_DECL (c);
	  إذا (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IS_DEVICE_PTR)
	    bitmap_set_bit (&is_on_device_head, DECL_UID (t));
	  إذا (شجرة_CODE (شجرة_TYPE (t)) != POINTER_TYPE)
	    {
	      إذا (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_USE_DEVICE_PTR
		  && !openacc)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qs variable is not a pointer",
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  remove = true;
		}
	      وإلا إذا (شجرة_CODE (شجرة_TYPE (t)) != ARRAY_TYPE)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qs variable is neither a pointer nor an array",
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  remove = true;
		}
	    }
	  اذهب check_dup_generic;

	حالة OMP_CLAUSE_HAS_DEVICE_ADDR:
	  t = OMP_CLAUSE_DECL (c);
	  إذا (شجرة_CODE (t) == OMP_ARRAY_SECTION)
	    {
	      إذا (handle_omp_array_sections (c, ort))
		remove = true;
	      وإلا
		{
		  t = OMP_CLAUSE_DECL (c);
		  طالما (شجرة_CODE (t) == ARRAY_REF)
		    t = شجرة_OPERAND (t, 0);
		}
	    }
	  bitmap_set_bit (&is_on_device_head, DECL_UID (t));
	  إذا (VAR_P (t) || شجرة_CODE (t) == PARM_DECL)
	    c_mark_addressable (t);
	  اذهب check_dup_generic_t;

	حالة OMP_CLAUSE_USE_DEVICE_ADDR:
	  t = OMP_CLAUSE_DECL (c);
	  إذا (VAR_P (t) || شجرة_CODE (t) == PARM_DECL)
	    c_mark_addressable (t);
	  اذهب check_dup_generic;

	حالة OMP_CLAUSE_NOWAIT:
	  إذا (copyprivate_seen)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<nowait%> clause must not be used together "
			"with %<copyprivate%> clause");
	      remove = true;
	      اكسر;
	    }
	  nowait_clause = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  استمر;

	حالة OMP_CLAUSE_ORDER:
	  إذا (ordered_clause)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<order%> clause must not be used together "
			"with %<ordered%> clause");
	      remove = true;
	      اكسر;
	    }
	  وإلا إذا (order_clause)
	    {
	      /* Silently remove duplicates.  */
	      remove = true;
	      اكسر;
	    }
	  order_clause = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  استمر;

	حالة OMP_CLAUSE_DETACH:
	  t = OMP_CLAUSE_DECL (c);
	  إذا (detach_seen)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"too many %qs clauses on a task construct",
			"detach");
	      remove = true;
	      اكسر;
	    }
	  detach_seen = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  c_mark_addressable (t);
	  استمر;

	حالة OMP_CLAUSE_IF:
	حالة OMP_CLAUSE_SELF:
	حالة OMP_CLAUSE_رقم_THREADS:
	حالة OMP_CLAUSE_رقم_TEAMS:
	حالة OMP_CLAUSE_THREAD_LIMIT:
	حالة OMP_CLAUSE_DEFAULT:
	حالة OMP_CLAUSE_UNTIED:
	حالة OMP_CLAUSE_COLLAPSE:
	حالة OMP_CLAUSE_FINAL:
	حالة OMP_CLAUSE_DEVICE:
	حالة OMP_CLAUSE_DIST_SCHEDULE:
	حالة OMP_CLAUSE_DYN_GROUPPRIVATE:
	حالة OMP_CLAUSE_PARALLEL:
	حالة OMP_CLAUSE_FOR:
	حالة OMP_CLAUSE_SECTIONS:
	حالة OMP_CLAUSE_TASKGROUP:
	حالة OMP_CLAUSE_PROC_BIND:
	حالة OMP_CLAUSE_DEVICE_TYPE:
	حالة OMP_CLAUSE_PRIORITY:
	حالة OMP_CLAUSE_THREADS:
	حالة OMP_CLAUSE_SIMD:
	حالة OMP_CLAUSE_HINT:
	حالة OMP_CLAUSE_FILTER:
	حالة OMP_CLAUSE_DEFAULTMAP:
	حالة OMP_CLAUSE_BIND:
	حالة OMP_CLAUSE_رقم_GANGS:
	حالة OMP_CLAUSE_رقم_WORKERS:
	حالة OMP_CLAUSE_VECTOR_LENGTH:
	حالة OMP_CLAUSE_ASYNC:
	حالة OMP_CLAUSE_WAIT:
	حالة OMP_CLAUSE_AUTO:
	حالة OMP_CLAUSE_INDEPENDENT:
	حالة OMP_CLAUSE_SEQ:
	حالة OMP_CLAUSE_GANG:
	حالة OMP_CLAUSE_WORKER:
	حالة OMP_CLAUSE_VECTOR:
	حالة OMP_CLAUSE_TILE:
	حالة OMP_CLAUSE_IF_PRESENT:
	حالة OMP_CLAUSE_FINALIZE:
	حالة OMP_CLAUSE_NOHOST:
	حالة OMP_CLAUSE_INDIRECT:
	حالة OMP_CLAUSE_NOVARIANTS:
	حالة OMP_CLAUSE_NOCONTEXT:
	  pc = &OMP_CLAUSE_CHAIN (c);
	  استمر;

	حالة OMP_CLAUSE_GRAINSIZE:
	  grainsize_seen = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  استمر;

	حالة OMP_CLAUSE_رقم_TASKS:
	  رقم_tasks_seen = true;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  استمر;

	حالة OMP_CLAUSE_MERGEABLE:
	  mergeable_seen = true;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  استمر;

	حالة OMP_CLAUSE_NOGROUP:
	  nogroup_seen = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  استمر;

	حالة OMP_CLAUSE_SCHEDULE:
	  schedule_clause = c;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  استمر;

	حالة OMP_CLAUSE_ORDERED:
	  ordered_clause = c;
	  إذا (order_clause)
	    {
	      error_at (OMP_CLAUSE_LOCATION (*order_clause),
			"%<order%> clause must not be used together "
			"with %<ordered%> clause");
	      *order_clause = OMP_CLAUSE_CHAIN (*order_clause);
	      order_clause = عدم;
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

	حالة OMP_CLAUSE_FULL:
	  full_seen = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  استمر;

	حالة OMP_CLAUSE_PARTIAL:
	  partial_seen = true;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  استمر;

	حالة OMP_CLAUSE_SIZES:
	  pc = &OMP_CLAUSE_CHAIN (c);
	  استمر;

	حالة OMP_CLAUSE_INBRANCH:
	حالة OMP_CLAUSE_NOTINBRANCH:
	  إذا (branch_seen)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<inbranch%> clause is incompatible with "
			"%<notinbranch%>");
	      remove = true;
	      اكسر;
	    }
	  branch_seen = true;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  استمر;

	حالة OMP_CLAUSE_INCLUSIVE:
	حالة OMP_CLAUSE_EXCLUSIVE:
	  need_complete = true;
	  need_implicitly_determined = true;
	  t = OMP_CLAUSE_DECL (c);
	  إذا (!VAR_P (t) && شجرة_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %qs", t,
			omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	      remove = true;
	    }
	  اكسر;

	حالة OMP_CLAUSE_INIT:
	  init_seen = true;
	  إذا (!OMP_CLAUSE_INIT_TARGETSYNC (c))
	    init_no_targetsync_clause = c;
	  /* FALLTHRU */
	حالة OMP_CLAUSE_DESTROY:
	حالة OMP_CLAUSE_USE:
	  init_use_destroy_seen = true;
	  t = OMP_CLAUSE_DECL (c);
	  إذا (bitmap_bit_p (&generic_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD appears more than once in action clauses", t);
	      remove = true;
	      اكسر;
	    }
	  bitmap_set_bit (&generic_head, DECL_UID (t));
	  /* FALLTHRU */
	حالة OMP_CLAUSE_INTEROP:
	  إذا (/* ort == C_ORT_OMP_INTEROP [uncomment for depobj init]  */
		   !c_omp_interop_t_p (شجرة_TYPE (OMP_CLAUSE_DECL (c))))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD must be of %<omp_interop_t%>",
			OMP_CLAUSE_DECL (c));
	      remove = true;
	    }
	  وإلا إذا ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_INIT
		    || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DESTROY)
		   && شجرة_READONLY (OMP_CLAUSE_DECL (c)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD shall not be const", OMP_CLAUSE_DECL (c));
	      remove = true;
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
	      إذا (t == error_mark_عقدة)
		remove = true;
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
		  إذا ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_SHARED
		       || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_FIRSTPRIVATE)
		      && c_omp_predefined_variable (t))
		    /* The __func__ variable and similar function-local
		       predefined variables may be listed in a shared or
		       firstprivate clause.  */
		    اكسر;
		  share_name = "shared";
		  اكسر;
		حالة OMP_CLAUSE_DEFAULT_PRIVATE:
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
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  remove = true;
		}
	      وإلا إذا (شجرة_READONLY (t)
		       && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_SHARED
		       && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_FIRSTPRIVATE)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<const%> qualified %qE may appear only in "
			    "%<shared%> or %<firstprivate%> clauses", t);
		  remove = true;
		}
	    }
	}

      إذا (remove)
	{
	  إذا (grp_start_p)
	    {
	      /* If we found a clause to remove, we want to remove the whole
		 expanded group, otherwise gimplify
		 (omp_resolve_clause_dependencies) can get confused.  */
	      *grp_start_p = grp_sentinel;
	      pc = grp_start_p;
	      grp_start_p = عدم;
	    }
	  وإلا
	    *pc = OMP_CLAUSE_CHAIN (c);
	}
      وإلا
	pc = &OMP_CLAUSE_CHAIN (c);
    }

  إذا (grp_start_p
      && OMP_CLAUSE_HAS_ITERATORS (*grp_start_p))
    لكل (شجرة gc = *grp_start_p; gc; gc = OMP_CLAUSE_CHAIN (gc))
      OMP_CLAUSE_ITERATORS (gc) = OMP_CLAUSE_ITERATORS (*grp_start_p);

  إذا (simdlen
      && safelen
      && شجرة_int_cst_lt (OMP_CLAUSE_SAFELEN_تعبير (safelen),
			  OMP_CLAUSE_SIMDLEN_تعبير (simdlen)))
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
      OMP_CLAUSE_SIMDLEN_تعبير (simdlen)
	= OMP_CLAUSE_SAFELEN_تعبير (safelen);
    }

  إذا (ordered_clause
      && schedule_clause
      && (OMP_CLAUSE_SCHEDULE_KIND (schedule_clause)
	  & OMP_CLAUSE_SCHEDULE_NONMONOTONIC))
    {
      error_at (OMP_CLAUSE_LOCATION (schedule_clause),
		"%<nonmonotonic%> schedule modifier specified together "
		"with %<ordered%> clause");
      OMP_CLAUSE_SCHEDULE_KIND (schedule_clause)
	= (تعداد omp_clause_schedule_kind)
	  (OMP_CLAUSE_SCHEDULE_KIND (schedule_clause)
	   & ~OMP_CLAUSE_SCHEDULE_NONMONOTONIC);
    }

  إذا (reduction_seen < 0 && ordered_clause)
    {
      error_at (OMP_CLAUSE_LOCATION (ordered_clause),
		"%qs clause specified together with %<inscan%> "
		"%<reduction%> clause", "ordered");
      reduction_seen = -2;
    }

  إذا (reduction_seen < 0 && schedule_clause)
    {
      error_at (OMP_CLAUSE_LOCATION (schedule_clause),
		"%qs clause specified together with %<inscan%> "
		"%<reduction%> clause", "schedule");
      reduction_seen = -2;
    }

  إذا (linear_variable_step_check
      || reduction_seen == -2
      || allocate_seen
      || target_in_reduction_seen)
    لكل (pc = &clauses, c = clauses; c ; c = *pc)
      {
	منطقي remove = خطأ;
	إذا (allocate_seen)
	  بدل (OMP_CLAUSE_CODE (c))
	    {
	    حالة OMP_CLAUSE_REDUCTION:
	    حالة OMP_CLAUSE_IN_REDUCTION:
	    حالة OMP_CLAUSE_TASK_REDUCTION:
	      إذا (شجرة_CODE (OMP_CLAUSE_DECL (c)) == MEM_REF)
		{
		  t = شجرة_OPERAND (OMP_CLAUSE_DECL (c), 0);
		  إذا (شجرة_CODE (t) == POINTER_PLUS_تعبير)
		    t = شجرة_OPERAND (t, 0);
		  إذا (شجرة_CODE (t) == ADDR_تعبير
		      || INDIRECT_REF_P (t))
		    t = شجرة_OPERAND (t, 0);
		  إذا (DECL_P (t))
		    bitmap_clear_bit (&aligned_head, DECL_UID (t));
		  اكسر;
		}
	      /* FALLTHRU */
	    حالة OMP_CLAUSE_PRIVATE:
	    حالة OMP_CLAUSE_FIRSTPRIVATE:
	    حالة OMP_CLAUSE_LASTPRIVATE:
	    حالة OMP_CLAUSE_LINEAR:
	      إذا (DECL_P (OMP_CLAUSE_DECL (c)))
		bitmap_clear_bit (&aligned_head,
				  DECL_UID (OMP_CLAUSE_DECL (c)));
	      اكسر;
	    افتراضي:
	      اكسر;
	    }
	إذا (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_LINEAR
	    && OMP_CLAUSE_LINEAR_VARIABLE_STRIDE (c)
	    && !bitmap_bit_p (&map_head,
			      DECL_UID (OMP_CLAUSE_LINEAR_STEP (c))))
	  {
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%<linear%> clause step is a parameter %qD not "
		      "specified in %<uniform%> clause",
		      OMP_CLAUSE_LINEAR_STEP (c));
	    remove = true;
	  }
	وإلا إذا (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
		 && reduction_seen == -2)
	  OMP_CLAUSE_REDUCTION_INSCAN (c) = 0;
	إذا (target_in_reduction_seen
	    && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP)
	  {
	    شجرة t = OMP_CLAUSE_DECL (c);
	    طالما (handled_component_p (t)
		   || INDIRECT_REF_P (t)
		   || شجرة_CODE (t) == ADDR_تعبير
		   || شجرة_CODE (t) == MEM_REF
		   || شجرة_CODE (t) == NON_LVALUE_تعبير)
	      t = شجرة_OPERAND (t, 0);
	    إذا (DECL_P (t)
		&& bitmap_bit_p (&oacc_reduction_head, DECL_UID (t)))
	      OMP_CLAUSE_MAP_IN_REDUCTION (c) = 1;
	  }

	إذا (remove)
	  *pc = OMP_CLAUSE_CHAIN (c);
	وإلا
	  pc = &OMP_CLAUSE_CHAIN (c);
      }

  إذا (allocate_seen)
    لكل (pc = &clauses, c = clauses; c ; c = *pc)
      {
	منطقي remove = خطأ;
	إذا (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ALLOCATE
	    && !OMP_CLAUSE_ALLOCATE_COMBINED (c)
	    && bitmap_bit_p (&aligned_head, DECL_UID (OMP_CLAUSE_DECL (c))))
	  {
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD specified in %<allocate%> clause but not in "
		      "an explicit privatization clause", OMP_CLAUSE_DECL (c));
	    remove = true;
	  }
	إذا (remove)
	  *pc = OMP_CLAUSE_CHAIN (c);
	وإلا
	  pc = &OMP_CLAUSE_CHAIN (c);
      }

  إذا (nogroup_seen && reduction_seen)
    {
      error_at (OMP_CLAUSE_LOCATION (*nogroup_seen),
		"%<nogroup%> clause must not be used together with "
		"%<reduction%> clause");
      *nogroup_seen = OMP_CLAUSE_CHAIN (*nogroup_seen);
    }

  إذا (grainsize_seen && رقم_tasks_seen)
    {
      error_at (OMP_CLAUSE_LOCATION (*grainsize_seen),
		"%<grainsize%> clause must not be used together with "
		"%<num_tasks%> clause");
      *grainsize_seen = OMP_CLAUSE_CHAIN (*grainsize_seen);
    }

  إذا (full_seen && partial_seen)
    {
      error_at (OMP_CLAUSE_LOCATION (*full_seen),
		"%<full%> clause must not be used together with "
		"%<partial%> clause");
      *full_seen = OMP_CLAUSE_CHAIN (*full_seen);
    }

  إذا (detach_seen)
    {
      إذا (mergeable_seen)
	{
	  error_at (OMP_CLAUSE_LOCATION (*detach_seen),
		    "%<detach%> clause must not be used together with "
		    "%<mergeable%> clause");
	  *detach_seen = OMP_CLAUSE_CHAIN (*detach_seen);
	}
      وإلا
	{
	  شجرة detach_decl = OMP_CLAUSE_DECL (*detach_seen);

	  لكل (pc = &clauses, c = clauses; c ; c = *pc)
	    {
	      منطقي remove = خطأ;
	      إذا ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_SHARED
		   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_PRIVATE
		   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_FIRSTPRIVATE
		   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_LASTPRIVATE)
		  && OMP_CLAUSE_DECL (c) == detach_decl)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "the event handle of a %<detach%> clause "
			    "should not be in a data-sharing clause");
		  remove = true;
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
      && (!init_use_destroy_seen
	  || (init_seen && init_no_targetsync_clause)))
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

شجرة
c_omp_finish_mapper_clauses (شجرة clauses)
{
  أرجع c_finish_omp_clauses (clauses, C_ORT_OMP);
}

/* Return code to initialize DST with a copy constructor from SRC.
   C doesn't have copy constructors nor assignment operators, only for
   _Atomic vars we need to perform __atomic_load from src into a temporary
   followed by __atomic_store of the temporary to dst.  */

شجرة
c_omp_clause_copy_ctor (شجرة clause, شجرة dst, شجرة src)
{
  إذا (!really_atomic_lvalue (dst) && !really_atomic_lvalue (src))
    أرجع build2 (MODIFY_تعبير, شجرة_TYPE (dst), dst, src);

  location_t loc = OMP_CLAUSE_LOCATION (clause);
  شجرة type = شجرة_TYPE (dst);
  شجرة nonatomic_type = build_qualified_type (type, TYPE_UNQUALIFIED);
  شجرة tmp = create_tmp_var (nonatomic_type);
  شجرة tmp_addr = build_fold_addr_تعبير (tmp);
  شجرة_ADDRESSABLE (tmp) = 1;
  suppress_warning (tmp);
  شجرة src_addr = build_fold_addr_تعبير (src);
  شجرة dst_addr = build_fold_addr_تعبير (dst);
  شجرة seq_cst = build_int_cst (integer_type_عقدة, MEMMODEL_SEQ_CST);
  vec<شجرة, va_gc> *params;
  /* Expansion of a generic atomic load may require an addition
     element, so allocate enough to prevent a resize.  */
  vec_alloc (params, 4);

  /* Build __atomic_load (&src, &tmp, SEQ_CST);  */
  شجرة fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_LOAD);
  params->quick_ادفع (src_addr);
  params->quick_ادفع (tmp_addr);
  params->quick_ادفع (seq_cst);
  شجرة load = c_build_function_call_vec (loc, vNULL, fndecl, params, عدم);

  vec_alloc (params, 4);

  /* Build __atomic_store (&dst, &tmp, SEQ_CST);  */
  fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_STORE);
  params->quick_ادفع (dst_addr);
  params->quick_ادفع (tmp_addr);
  params->quick_ادفع (seq_cst);
  شجرة store = c_build_function_call_vec (loc, vNULL, fndecl, params, عدم);
  أرجع build2 (COMPOUND_تعبير, void_type_عقدة, load, store);
}

/* Create a transaction node.  */

شجرة
c_finish_transaction (location_t loc, شجرة block, صحيح flags)
{
  شجرة stmt = build_stmt (loc, TRANSACTION_تعبير, block);
  إذا (flags & TM_STMT_ATTR_OUTER)
    TRANSACTION_تعبير_OUTER (stmt) = 1;
  إذا (flags & TM_STMT_ATTR_RELAXED)
    TRANSACTION_تعبير_RELAXED (stmt) = 1;
  أرجع add_stmt (stmt);
}

/* Make a variant type in the proper way for C/C++, propagating qualifiers
   down to the element type of an array.  If ORIG_QUAL_TYPE is not
   NULL, then it should be used as the qualified type
   ORIG_QUAL_INDIRECT levels down in array type derivation (to
   preserve information about the typedef name from which an array
   type was derived).  */

شجرة
c_build_qualified_type (شجرة type, صحيح type_quals, شجرة orig_qual_type,
			size_t orig_qual_indirect)
{
  إذا (type == error_mark_عقدة)
    أرجع type;

  إذا (شجرة_CODE (type) == ARRAY_TYPE)
    {
      شجرة t;
      شجرة element_type = c_build_qualified_type (شجرة_TYPE (type),
						  type_quals, orig_qual_type,
						  orig_qual_indirect - 1);

      /* See if we already have an identically qualified type.  */
      إذا (orig_qual_type && orig_qual_indirect == 0)
	t = orig_qual_type;
      وإلا
	لكل (t = TYPE_MAIN_VARIANT (type); t; t = TYPE_NEXT_VARIANT (t))
	  {
	    إذا (TYPE_QUALS (strip_array_types (t)) == type_quals
		&& TYPE_NAME (t) == TYPE_NAME (type)
		&& TYPE_CONTEXT (t) == TYPE_CONTEXT (type)
		&& attribute_list_equal (TYPE_ATTRIBUTES (t),
					 TYPE_ATTRIBUTES (type)))
	      اكسر;
	  }
      إذا (!t)
	{
          شجرة domain = TYPE_DOMAIN (type);

	  t = build_variant_type_copy (type);
	  شجرة_TYPE (t) = element_type;
	  TYPE_ADDR_SPACE (t) = TYPE_ADDR_SPACE (element_type);

          إذا (TYPE_STRUCTURAL_EQUALITY_P (element_type)
              || (domain && TYPE_STRUCTURAL_EQUALITY_P (domain)))
            SET_TYPE_STRUCTURAL_EQUALITY (t);
          وإلا إذا (TYPE_CANONICAL (element_type) != element_type
                   || (domain && TYPE_CANONICAL (domain) != domain))
            {
              شجرة unqualified_canon
		= c_build_array_type (TYPE_CANONICAL (element_type),
				      domain ? TYPE_CANONICAL (domain)
					     : NULL_شجرة);
              إذا (TYPE_REVERSE_STORAGE_ORDER (type))
                {
                  unqualified_canon
		    = build_distinct_type_copy (unqualified_canon);
                  TYPE_REVERSE_STORAGE_ORDER (unqualified_canon) = 1;
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
      && (!POINTER_TYPE_P (type)
	  || !C_TYPE_OBJECT_OR_INCOMPLETE_P (شجرة_TYPE (type))))
    {
      error ("invalid use of %<restrict%>");
      type_quals &= ~TYPE_QUAL_RESTRICT;
    }

  شجرة var_type = (orig_qual_type && orig_qual_indirect == 0
		   ? orig_qual_type
		   : build_qualified_type (type, type_quals));

  gcc_checking_assert (C_TYPE_VARIABLE_SIZE (var_type)
		       == C_TYPE_VARIABLE_SIZE (type));
  gcc_checking_assert (c_type_variably_modified_p (var_type)
		       == c_type_variably_modified_p (type));

  /* A variant type does not inherit the list of incomplete vars from the
     type main variant.  */
  إذا ((RECORD_OR_UNION_TYPE_P (var_type)
       || شجرة_CODE (var_type) == ENUMERAL_TYPE)
      && TYPE_MAIN_VARIANT (var_type) != var_type)
    C_TYPE_INCOMPLETE_VARS (var_type) = 0;
  أرجع var_type;
}

/* Build a VA_ARG_EXPR for the C parser.  */

شجرة
c_build_va_arg (location_t loc1, شجرة تعبير, location_t loc2, شجرة type,
		شجرة type_تعبير)
{
  إذا (error_operand_p (type))
    أرجع error_mark_عقدة;
  /* VA_ARG_EXPR cannot be used for a scalar va_list with reverse storage
     order because it takes the address of the expression.  */
  وإلا إذا (handled_component_p (تعبير)
	   && reverse_storage_order_for_component_p (تعبير))
    {
      error_at (loc1, "cannot use %<va_arg%> with reverse storage order");
      أرجع error_mark_عقدة;
    }
  وإلا إذا (!COMPLETE_TYPE_P (type))
    {
      error_at (loc2, "second argument to %<va_arg%> is of incomplete "
		"type %qT", type);
      أرجع error_mark_عقدة;
    }
  وإلا إذا (شجرة_CODE (type) == FUNCTION_TYPE)
    {
      error_at (loc2, "second argument to %<va_arg%> is a function type %qT",
		type);
      أرجع error_mark_عقدة;
    }
  وإلا إذا (شجرة_CODE (type) == ARRAY_TYPE && C_TYPE_VARIABLE_SIZE (type)
	   && !flag_isoc99)
    {
      error_at (loc2, "second argument to %<va_arg%> is an array type %qT",
		type);
      أرجع error_mark_عقدة;
    }
  وإلا إذا (warn_cxx_compat && شجرة_CODE (type) == ENUMERAL_TYPE)
    warning_at (loc2, OPT_Wc___compat,
		"C++ requires promoted type, not enum type, in %<va_arg%>");

  إذا (flag_isoc99 && شجرة_CODE (type) == ARRAY_TYPE)
    {
      warning_at (loc2, 0, "second argument to %<va_arg%> is an array type %qT",
		  type);
      /* We create a trap but evaluate side effects first.  */
      شجرة trapfn = builtin_decl_explicit (BUILT_IN_TRAP);
      trapfn = build_call_تعبير_loc (loc2, trapfn, 0);
      شجرة e2 = build2 (COMPOUND_تعبير, void_type_عقدة, تعبير, trapfn);
      /* Return a compound literal of the right type.  */
      شجرة e1 = build_compound_literal (loc2, type, عدم, true, 0, عدم);
      تعبير = build2 (COMPOUND_تعبير, type, e2, e1);
    }
  وإلا
    تعبير = build_va_arg (loc2, تعبير, type);

  إذا (type_تعبير)
    تعبير = build2 (COMPOUND_تعبير, شجرة_TYPE (تعبير), type_تعبير, تعبير);

  أرجع تعبير;
}

/* Return truthvalue of whether T1 is the same tree structure as T2.
   Return 1 if they are the same. Return false if they are different.  */

منطقي
c_شجرة_equal (شجرة t1, شجرة t2)
{
  تعداد شجرة_code code1, code2;

  إذا (t1 == t2)
    أرجع true;
  إذا (!t1 || !t2)
    أرجع خطأ;

  لكل (code1 = شجرة_CODE (t1); code1 == NON_LVALUE_تعبير;
       code1 = شجرة_CODE (t1))
    t1 = شجرة_OPERAND (t1, 0);
  لكل (code2 = شجرة_CODE (t2); code2 == NON_LVALUE_تعبير;
       code2 = شجرة_CODE (t2))
    t2 = شجرة_OPERAND (t2, 0);

  /* They might have become equal now.  */
  إذا (t1 == t2)
    أرجع true;

  إذا (code1 != code2)
    أرجع خطأ;

  إذا (CONSTANT_CLASS_P (t1) && !comptypes (شجرة_TYPE (t1), شجرة_TYPE (t2)))
    أرجع خطأ;

  بدل (code1)
    {
    حالة INTEGER_CST:
      أرجع wi::to_wide (t1) == wi::to_wide (t2);

    حالة REAL_CST:
      أرجع real_equal (&شجرة_REAL_CST (t1), &شجرة_REAL_CST (t2));

    حالة STRING_CST:
      أرجع شجرة_STRING_LENGTH (t1) == شجرة_STRING_LENGTH (t2)
	&& !memcmp (شجرة_STRING_POINTER (t1), شجرة_STRING_POINTER (t2),
		    شجرة_STRING_LENGTH (t1));

    حالة FIXED_CST:
      أرجع FIXED_قيم_IDENTICAL (شجرة_FIXED_CST (t1),
				     شجرة_FIXED_CST (t2));

    حالة COMPLEX_CST:
      أرجع c_شجرة_equal (شجرة_REALPART (t1), شجرة_REALPART (t2))
	     && c_شجرة_equal (شجرة_IMAGPART (t1), شجرة_IMAGPART (t2));

    حالة VECTOR_CST:
      أرجع operand_equal_p (t1, t2, OEP_ONLY_CONST);

    حالة CONSTRUCTOR:
      /* We need to do this when determining whether or not two
	 non-type pointer to member function template arguments
	 are the same.  */
      إذا (!comptypes (شجرة_TYPE (t1), شجرة_TYPE (t2))
	  || CONSTRUCTOR_NELTS (t1) != CONSTRUCTOR_NELTS (t2))
	أرجع خطأ;
      {
	شجرة field, قيمة;
	unsigned صحيح i;
	FOR_EACH_CONSTRUCTOR_ELT (CONSTRUCTOR_ELTS (t1), i, field, قيمة)
	  {
	    constructor_elt *elt2 = CONSTRUCTOR_ELT (t2, i);
	    إذا (!c_شجرة_equal (field, elt2->index)
		|| !c_شجرة_equal (قيمة, elt2->قيمة))
	      أرجع خطأ;
	  }
      }
      أرجع true;

    حالة شجرة_LIST:
      إذا (!c_شجرة_equal (شجرة_PURPOSE (t1), شجرة_PURPOSE (t2)))
	أرجع خطأ;
      إذا (!c_شجرة_equal (شجرة_قيمة (t1), شجرة_قيمة (t2)))
	أرجع خطأ;
      أرجع c_شجرة_equal (شجرة_CHAIN (t1), شجرة_CHAIN (t2));

    حالة SAVE_تعبير:
      أرجع c_شجرة_equal (شجرة_OPERAND (t1, 0), شجرة_OPERAND (t2, 0));

    حالة CALL_تعبير:
      {
	شجرة arg1, arg2;
	call_تعبير_arg_iterator iter1, iter2;
	إذا (!c_شجرة_equal (CALL_تعبير_FN (t1), CALL_تعبير_FN (t2)))
	  أرجع خطأ;
	لكل (arg1 = first_call_تعبير_arg (t1, &iter1),
	       arg2 = first_call_تعبير_arg (t2, &iter2);
	     arg1 && arg2;
	     arg1 = next_call_تعبير_arg (&iter1),
	       arg2 = next_call_تعبير_arg (&iter2))
	  إذا (!c_شجرة_equal (arg1, arg2))
	    أرجع خطأ;
	إذا (arg1 || arg2)
	  أرجع خطأ;
	أرجع true;
      }

    حالة TARGET_تعبير:
      {
	شجرة o1 = شجرة_OPERAND (t1, 0);
	شجرة o2 = شجرة_OPERAND (t2, 0);

	/* Special case: if either target is an unallocated VAR_DECL,
	   it means that it's going to be unified with whatever the
	   TARGET_EXPR is really supposed to initialize, so treat it
	   as being equivalent to anything.  */
	إذا (VAR_P (o1) && DECL_NAME (o1) == NULL_شجرة
	    && !DECL_RTL_SET_P (o1))
	  /*Nop*/;
	وإلا إذا (VAR_P (o2) && DECL_NAME (o2) == NULL_شجرة
		 && !DECL_RTL_SET_P (o2))
	  /*Nop*/;
	وإلا إذا (!c_شجرة_equal (o1, o2))
	  أرجع خطأ;

	أرجع c_شجرة_equal (شجرة_OPERAND (t1, 1), شجرة_OPERAND (t2, 1));
      }

    حالة COMPONENT_REF:
      إذا (شجرة_OPERAND (t1, 1) != شجرة_OPERAND (t2, 1))
	أرجع خطأ;
      أرجع c_شجرة_equal (شجرة_OPERAND (t1, 0), شجرة_OPERAND (t2, 0));

    حالة PARM_DECL:
    حالة VAR_DECL:
    حالة CONST_DECL:
    حالة FIELD_DECL:
    حالة FUNCTION_DECL:
    حالة IDENTIFIER_عقدة:
    حالة SSA_NAME:
      أرجع خطأ;

    حالة شجرة_VEC:
      {
	unsigned ix;
	إذا (شجرة_VEC_LENGTH (t1) != شجرة_VEC_LENGTH (t2))
	  أرجع خطأ;
	لكل (ix = شجرة_VEC_LENGTH (t1); ix--;)
	  إذا (!c_شجرة_equal (شجرة_VEC_ELT (t1, ix),
			     شجرة_VEC_ELT (t2, ix)))
	    أرجع خطأ;
	أرجع true;
      }

    CASE_CONVERT:
      إذا (!comptypes (شجرة_TYPE (t1), شجرة_TYPE (t2)))
	أرجع خطأ;
      اكسر;

    افتراضي:
      اكسر;
    }

  بدل (شجرة_CODE_CLASS (code1))
    {
    حالة tcc_unary:
    حالة tcc_ثنائي:
    حالة tcc_comparison:
    حالة tcc_expression:
    حالة tcc_vl_exp:
    حالة tcc_reference:
    حالة tcc_statement:
      {
	صحيح i, n = شجرة_OPERAND_LENGTH (t1);

	بدل (code1)
	  {
	  حالة PREINCREMENT_تعبير:
	  حالة PREDECREMENT_تعبير:
	  حالة POSTINCREMENT_تعبير:
	  حالة POSTDECREMENT_تعبير:
	    n = 1;
	    اكسر;
	  حالة ARRAY_REF:
	    n = 2;
	    اكسر;
	  افتراضي:
	    اكسر;
	  }

	إذا (شجرة_CODE_CLASS (code1) == tcc_vl_exp
	    && n != شجرة_OPERAND_LENGTH (t2))
	  أرجع خطأ;

	لكل (i = 0; i < n; ++i)
	  إذا (!c_شجرة_equal (شجرة_OPERAND (t1, i), شجرة_OPERAND (t2, i)))
	    أرجع خطأ;

	أرجع true;
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
c_decl_implicit (const_شجرة fndecl)
{
  أرجع C_DECL_IMPLICIT (fndecl);
}
