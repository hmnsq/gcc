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
شمارش impl_conv {
  ic_argpass,
  ic_assign,
  ic_init,
  ic_init_const,
  ic_return
};

/* The level of nesting inside "__alignof__".  */
صحیح in_alignof;

/* The level of nesting inside "sizeof".  */
صحیح in_sizeof;

/* The level of nesting inside "countof".  */
صحیح in_countof;

/* The level of nesting inside "typeof".  */
صحیح in_typeof;

/* The level of nesting inside "_Generic".  */
صحیح in_generic;

/* True when parsing OpenMP loop expressions.  */
منطقی c_in_omp_for;

/* True when parsing OpenMP map clause.  */
منطقی c_omp_array_section_p;

/* The argument of last parsed sizeof expression, only to be tested
   if expr.original_code == SIZEOF_EXPR.  */
درخت c_last_sizeof_arg;
location_t c_last_sizeof_loc;

/* Nonzero if we might need to print a "missing braces around
   initializer" message within this initializer.  */
ایستا صحیح found_missing_braces;

ایستا منطقی require_constant_مقدار;
ایستا منطقی require_constant_elements;
ایستا منطقی require_constexpr_مقدار;

ایستا درخت qualify_type (درخت, درخت);
ساختار comptypes_data;
ایستا منطقی tagged_types_tu_compatible_p (const_درخت, const_درخت,
					  ساختار comptypes_data *);
ایستا منطقی comp_target_types (location_t, درخت, درخت);
ایستا منطقی function_types_compatible_p (const_درخت, const_درخت,
					 ساختار comptypes_data *);
ایستا منطقی type_lists_compatible_p (const_درخت, const_درخت,
				     ساختار comptypes_data *);
ایستا صحیح convert_arguments (location_t, vec<location_t>, درخت,
			      vec<درخت, va_gc> *, vec<درخت, va_gc> *, درخت,
			      درخت);
ایستا درخت pointer_diff (location_t, درخت, درخت, درخت *);
ایستا درخت convert_for_assignment (location_t, location_t, درخت, درخت, درخت,
				    شمارش impl_conv, منطقی, درخت, درخت, صحیح,
				    صحیح = 0);
ایستا درخت valid_compound_عبارت_initializer (درخت, درخت);
ایستا تهی افزودن_string (ثابت نویسه *);
ایستا تهی افزودن_member_name (درخت);
ایستا صحیح spelling_length (تهی);
ایستا نویسه *print_spelling (نویسه *);
ایستا تهی warning_init (location_t, صحیح, ثابت نویسه *);
ایستا درخت digest_init (location_t, درخت, درخت, درخت, درخت, منطقی, منطقی, منطقی,
			 منطقی, منطقی, منطقی);
ایستا تهی output_init_element (location_t, درخت, درخت, منطقی, درخت, درخت, منطقی,
				 منطقی, ساختار obstack *);
ایستا تهی output_pending_init_elements (صحیح, ساختار obstack *);
ایستا منطقی set_designator (location_t, منطقی, ساختار obstack *);
ایستا تهی افزودن_range_پشته (درخت, ساختار obstack *);
ایستا تهی add_pending_init (location_t, درخت, درخت, درخت, منطقی,
			      ساختار obstack *);
ایستا تهی set_nonincremental_init (ساختار obstack *);
ایستا تهی set_nonincremental_init_from_string (درخت, ساختار obstack *);
ایستا درخت find_init_member (درخت, ساختار obstack *);
ایستا تهی readonly_warning (درخت, شمارش lvalue_use);
ایستا صحیح lvalue_or_else (location_t, const_درخت, شمارش lvalue_use);
ایستا تهی record_maybe_used_decl (درخت, منطقی address);
ایستا منطقی comptypes_internal (const_درخت, const_درخت,
				ساختار comptypes_data *data);
ایستا منطقی comptypes_check_for_composite (درخت t1, درخت t2);
ایستا منطقی handle_counted_by_p (درخت);
ایستا منطقی بالاترین_array_vla_p (const_درخت type);


/* Return true if EXP is a null pointer constant, false otherwise.  */

منطقی
null_pointer_constant_p (const_درخت عبارت)
{
  /* This should really operate on c_expr structures, but they aren't
     yet available everywhere required.  */
  درخت type = درخت_TYPE (عبارت);

  /* An integer constant expression with the value 0, such an expression
     cast to type void*, or the predefined constant nullptr, are a null
     pointer constant.  */
  اگر (عبارت == nullptr_گره)
    بازگشت درست;

  بازگشت (درخت_CODE (عبارت) == INTEGER_CST
	  && !درخت_OVERFLOW (عبارت)
	  && integer_zerop (عبارت)
	  && (INTEGRAL_TYPE_P (type)
	      || (درخت_CODE (type) == POINTER_TYPE
		  && VOID_TYPE_P (درخت_TYPE (type))
		  && TYPE_QUALS (درخت_TYPE (type)) == TYPE_UNQUALIFIED)));
}

/* EXPR may appear in an unevaluated part of an integer constant
   expression, but not in an evaluated part.  Wrap it in a
   C_MAYBE_CONST_EXPR, or mark it with TREE_OVERFLOW if it is just an
   INTEGER_CST and we cannot create a C_MAYBE_CONST_EXPR.  */

ایستا درخت
note_integer_operands (درخت عبارت)
{
  درخت ret;
  اگر (درخت_CODE (عبارت) == INTEGER_CST && in_late_دودویی_op)
    {
      ret = copy_گره (عبارت);
      درخت_OVERFLOW (ret) = 1;
    }
  وگرنه
    {
      ret = build2 (C_MAYBE_CONST_عبارت, درخت_TYPE (عبارت), NULL_درخت, عبارت);
      C_MAYBE_CONST_عبارت_INT_OPERANDS (ret) = 1;
    }
  بازگشت ret;
}

/* Having checked whether EXPR may appear in an unevaluated part of an
   integer constant expression and found that it may, remove any
   C_MAYBE_CONST_EXPR noting this fact and return the resulting
   expression.  */

ایستا درونخطی درخت
remove_c_maybe_const_عبارت (درخت عبارت)
{
  اگر (درخت_CODE (عبارت) == C_MAYBE_CONST_عبارت)
    بازگشت C_MAYBE_CONST_عبارت_عبارت (عبارت);
  وگرنه
    بازگشت عبارت;
}

/* This is a cache to hold if two types are seen.  */

ساختار tagged_tu_seen_cache {
  ثابت ساختار tagged_tu_seen_cache * next;
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

  اگر (error_operand_p (مقدار))
    بازگشت error_mark_گره;

  /* First, detect a valid value with a complete type.  */
  اگر (COMPLETE_TYPE_P (type))
    بازگشت مقدار;

  c_incomplete_type_error (loc, مقدار, type);
  بازگشت error_mark_گره;
}

/* Print an error message for invalid use of an incomplete type.
   VALUE is the expression that was used (or 0 if that isn't known)
   and TYPE is the type that was invalid.  LOC is the location for
   the error.  */

تهی
c_incomplete_type_error (location_t loc, const_درخت مقدار, const_درخت type)
{
  /* Avoid duplicate error message.  */
  اگر (درخت_CODE (type) == ERROR_MARK)
    بازگشت;

  اگر (مقدار != NULL_درخت && (VAR_P (مقدار) || درخت_CODE (مقدار) == PARM_DECL))
    error_at (loc, "%qD has an incomplete type %qT", مقدار, type);
  وگرنه
    {
    retry:
      /* We must print an error message.  Be clever about what it says.  */

      انتخاب (درخت_CODE (type))
	{
	حالت RECORD_TYPE:
	حالت UNION_TYPE:
	حالت ENUMERAL_TYPE:
	  بشکن;

	حالت VOID_TYPE:
	  error_at (loc, "invalid use of void expression");
	  بازگشت;

	حالت ARRAY_TYPE:
	  اگر (TYPE_DOMAIN (type))
	    {
	      اگر (flexible_array_member_type_p (type))
		{
		  error_at (loc, "invalid use of flexible array member");
		  بازگشت;
		}
	      type = درخت_TYPE (type);
	      برو retry;
	    }
	  error_at (loc, "invalid use of array with unspecified bounds");
	  بازگشت;

	پیشفرض:
	  gcc_unreachable ();
	}

      اگر (درخت_CODE (TYPE_NAME (type)) == IDENTIFIER_گره)
	error_at (loc, "invalid use of undefined type %qT", type);
      وگرنه
	/* If this type has a typedef-name, the TYPE_NAME is a TYPE_DECL.  */
	error_at (loc, "invalid use of incomplete typedef %qT", type);
    }
}

/* Given a type, apply default promotions wrt unnamed function
   arguments and return the new type.  */

درخت
c_type_promotes_to (درخت type)
{
  درخت ret = NULL_درخت;

  اگر (TYPE_MAIN_VARIANT (type) == float_type_گره)
    ret = double_type_گره;
  وگرنه اگر (c_promoting_integer_type_p (type))
    {
      /* Preserve unsignedness if not really getting any wider.  */
      اگر (TYPE_UNSIGNED (type)
	  && (TYPE_PRECISION (type) == TYPE_PRECISION (integer_type_گره)))
	ret = unsigned_type_گره;
      وگرنه
	ret = integer_type_گره;
    }

  اگر (ret != NULL_درخت)
    بازگشت (TYPE_ATOMIC (type)
	    ? c_build_qualified_type (ret, TYPE_QUAL_ATOMIC)
	    : ret);

  بازگشت type;
}

/* Return true if between two named address spaces, whether there is a superset
   named address space that encompasses both address spaces.  If there is a
   superset, return which address space is the superset.  */

ایستا منطقی
addr_space_superset (addr_space_t as1, addr_space_t as2, addr_space_t *common)
{
  اگر (as1 == as2)
    {
      *common = as1;
      بازگشت درست;
    }
  وگرنه اگر (targetm.addr_space.subset_p (as1, as2))
    {
      *common = as2;
      بازگشت درست;
    }
  وگرنه اگر (targetm.addr_space.subset_p (as2, as1))
    {
      *common = as1;
      بازگشت درست;
    }
  وگرنه
    بازگشت نادرست;
}

/* Return a variant of TYPE which has all the type qualifiers of LIKE
   as well as those of TYPE.  */

ایستا درخت
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

  بازگشت c_build_qualified_type (type,
				 TYPE_QUALS_NO_ADDR_SPACE (type)
				 | TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (like)
				 | ENCODE_QUAL_ADDR_SPACE (as_common));
}


/* Check consistency of type TYPE.  For derived types, we test that
   C_TYPE_VARIABLE_SIZE and C_TYPE_VARIABLY_MODIFIED are consistent with
   the requirements of the base type.  We also check that arrays with a
   non-constant length are marked with C_TYPE_VARIABLE_SIZE. If any
   inconsistency is detected false is returned and true otherwise.  */

ایستا منطقی
c_verify_type (درخت type)
{
  انتخاب (درخت_CODE (type))
    {
    حالت POINTER_TYPE:
    حالت FUNCTION_TYPE:
    حالت ARRAY_TYPE:
      /* Pointer, array, functions are variably modified if and only if the
	 target, element, return type is variably modified.  */
      اگر (!TYPE_STRUCTURAL_EQUALITY_P (type)
	  && (C_TYPE_VARIABLY_MODIFIED (type)
	      != C_TYPE_VARIABLY_MODIFIED (درخت_TYPE (type))))
	بازگشت نادرست;
      /* If the target type is structural equality, the type should also. */
      اگر (!TYPE_STRUCTURAL_EQUALITY_P (type)
	  && TYPE_STRUCTURAL_EQUALITY_P (درخت_TYPE (type)))
	بازگشت نادرست;
    پیشفرض:
       بشکن;
    }

  انتخاب (درخت_CODE (type))
    {
    حالت POINTER_TYPE:
    حالت FUNCTION_TYPE:
      /* Pointer and functions can not have variable size.  */
      اگر (C_TYPE_VARIABLE_SIZE (type))
	بازگشت نادرست;
      بشکن;
    حالت ARRAY_TYPE:
      /* An array has variable size if and only if it has a non-constant
	 dimensions or its element type has variable size.  */
      اگر ((C_TYPE_VARIABLE_SIZE (درخت_TYPE (type))
	   || بالاترین_array_vla_p (type))
	  != C_TYPE_VARIABLE_SIZE (type))
	بازگشت نادرست;
      /* If the element type or the array has variable size, then the
	 array has variable size and is variably modified.  */
      اگر (C_TYPE_VARIABLE_SIZE (درخت_TYPE (type))
	  || C_TYPE_VARIABLE_SIZE (type))
	{
	  اگر (!C_TYPE_VARIABLE_SIZE (type))
	    بازگشت نادرست;
	  اگر (!C_TYPE_VARIABLY_MODIFIED (type))
	    بازگشت نادرست;
	}

      /* va_list violates this, accept such types here.  */
      اگر (!COMPLETE_TYPE_P (درخت_TYPE (type)))
	بازگشت درست;

      اگر (COMPLETE_TYPE_P (type))
	{
	  /* If the size is unknown, it can not be complete.  */
	  اگر (NULL_درخت == TYPE_DOMAIN (type))
	    بازگشت نادرست;

	  /* Zero-length arrays must have size zero.  */
	  اگر (zero_length_array_type_p (type)
	      && !integer_zerop (TYPE_SIZE (type)))
	    بازگشت نادرست;
	}
      وگرنه
	{
	  /* If not complete but has a domain, it must be a FAM.  */
	  اگر (NULL_درخت != TYPE_DOMAIN (type)
	      && !flexible_array_member_type_p (type))
	    بازگشت نادرست;
	}
    پیشفرض:
      بشکن;
    }
  بازگشت درست;
}

/* Propagate C_TYPE_VARIABLY_MODIFIED and C_TYPE_VARIABLE_SIZE
   from a base type to a newly built derived or qualified type.  */

ایستا درخت
c_set_type_bits (درخت new_type, درخت old_type)
{
  gcc_checking_assert (c_verify_type (old_type));

  اگر (c_type_variably_modified_p (old_type))
    C_TYPE_VARIABLY_MODIFIED (new_type) = درست;

  اگر (درخت_CODE (new_type) == ARRAY_TYPE && C_TYPE_VARIABLE_SIZE (old_type))
    {
      C_TYPE_VARIABLY_MODIFIED (new_type) = درست;
      C_TYPE_VARIABLE_SIZE (new_type) = درست;
    }
  بازگشت new_type;
}

/* Build a pointer type using the default pointer mode.  */

درخت
c_build_pointer_type (درخت to_type)
{
  addr_space_t as = to_type == error_mark_گره ? ADDR_SPACE_GENERIC
					       : TYPE_ADDR_SPACE (to_type);
  machine_mode pointer_mode;

  اگر (as != ADDR_SPACE_GENERIC || c_default_pointer_mode == VOIDmode)
    pointer_mode = targetm.addr_space.pointer_mode (as);
  وگرنه
    pointer_mode = c_default_pointer_mode;

  بازگشت c_build_pointer_type_for_mode (to_type, pointer_mode, نادرست);
}

/* Build a pointer type using the given mode.  */

درخت
c_build_pointer_type_for_mode (درخت type, machine_mode mode, منطقی m)
{
  درخت ret = build_pointer_type_for_mode (type, mode, m);
  بازگشت c_set_type_bits (ret, type);
}

/* Build a function type.  */

درخت
c_build_function_type (درخت type, درخت args, منطقی no)
{
  درخت ret = build_function_type (type, args, no);
  بازگشت c_set_type_bits (ret, type);
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

  اگر (بالاترین_array_vla_p (ret))
    {
      C_TYPE_VARIABLE_SIZE (ret) = 1;
      C_TYPE_VARIABLY_MODIFIED (ret) = 1;
    }

  بازگشت c_set_type_bits (ret, type);
}

/* Build an array type of unspecified size.  */
درخت
c_build_array_type_unspecified (درخت type)
{
  درخت upper = build2 (COMPOUND_عبارت, درخت_TYPE (size_zero_گره),
		       integer_zero_گره, size_zero_گره);
  بازگشت c_build_array_type (type, build_index_type (upper));
}

/* Build an array type of zero size.  */
درخت
c_build_array_type_zero_size (درخت type)
{
  /* The GCC extension for zero-length arrays differs from
     ISO flexible array members in that sizeof yields
     zero.  */
  type = c_build_array_type (type, build_index_type (NULL_درخت));
  type = build_distinct_type_copy (TYPE_MAIN_VARIANT (type));
  TYPE_SIZE (type) = bitsize_zero_گره;
  TYPE_SIZE_UNIT (type) = size_zero_گره;
  SET_TYPE_STRUCTURAL_EQUALITY (type);
  بازگشت type;
}

درخت
c_build_type_attribute_qual_variant (درخت type, درخت attrs, صحیح quals)
{
  درخت ret = build_type_attribute_qual_variant (type, attrs, quals);
  بازگشت c_set_type_bits (ret, type);
}

درخت
c_build_type_attribute_variant (درخت type, درخت attrs)
{
  بازگشت c_build_type_attribute_qual_variant (type, attrs, TYPE_QUALS (type));
}

/* Reconstruct a complex derived type.  This is used to re-construct types
   with the vector attribute.  It is called via a langhook.  */

درخت
c_reconstruct_complex_type (درخت type, درخت bottom)
{
  درخت inner, outer;

  اگر (درخت_CODE (type) == POINTER_TYPE)
    {
      inner = c_reconstruct_complex_type (درخت_TYPE (type), bottom);
      outer = c_build_pointer_type_for_mode (inner, TYPE_MODE (type),
					     TYPE_REF_CAN_ALIAS_ALL (type));
    }
  وگرنه اگر (درخت_CODE (type) == ARRAY_TYPE)
    {
      منطقی rso = TYPE_REVERSE_STORAGE_ORDER (type);
      inner = c_reconstruct_complex_type (درخت_TYPE (type), bottom);
      outer = c_build_array_type (inner, TYPE_DOMAIN (type));
      اگر (rso)
	{
	  outer = build_distinct_type_copy (outer);
	  TYPE_REVERSE_STORAGE_ORDER (outer) = 1;
	}

      gcc_checking_assert (C_TYPE_VARIABLE_SIZE (type)
			   == C_TYPE_VARIABLE_SIZE (outer));
    }
  وگرنه اگر (درخت_CODE (type) == FUNCTION_TYPE)
    {
      inner = c_reconstruct_complex_type (درخت_TYPE (type), bottom);
      outer = c_build_function_type (inner, TYPE_ARG_TYPES (type),
				     TYPE_NO_NAMED_ARGS_STDARG_P (type));
    }
  وگرنه اگر (درخت_CODE (type) == REFERENCE_TYPE
	   || درخت_CODE (type) == OFFSET_TYPE)
    gcc_unreachable ();
  وگرنه
    بازگشت bottom;

  بازگشت c_build_type_attribute_qual_variant (outer, TYPE_ATTRIBUTES (type),
					      TYPE_QUALS (type));
}


/* Helper function for c_canonical_type.  Check whether FIELD
   contains a pointer to a structure or union with tag,
   possibly nested in other type derivations, and return the
   type of this nested structure or union.  */
ایستا درخت
ptr_to_tagged_member (درخت field)
{
  gcc_assert (FIELD_DECL == درخت_CODE (field));
  درخت type = درخت_TYPE (field);
  منطقی ptr_seen = نادرست;
  وقتی (درخت_CODE (type) == ARRAY_TYPE
	 || درخت_CODE (type) == FUNCTION_TYPE
	 || درخت_CODE (type) == POINTER_TYPE)
    {
      اگر (درخت_CODE (type) == POINTER_TYPE)
	ptr_seen = درست;
      type = درخت_TYPE (type);
    }

  اگر (ptr_seen
      && RECORD_OR_UNION_TYPE_P (type)
      && NULL_درخت != c_type_tag (type))
    بازگشت type;

  بازگشت NULL_درخت;
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
  gcc_assert (RECORD_OR_UNION_TYPE_P (type));

  منطقی needs_mod = نادرست;
  برای (درخت x = TYPE_FIELDS (type); x; x = DECL_CHAIN (x))
    {
      اگر (!ptr_to_tagged_member (x))
	ادامه;
      needs_mod = درست;
      بشکن;
    }
  اگر (!needs_mod)
    بازگشت type;

  /* Construct new version with such members replaced.  */
  درخت n = build_distinct_type_copy (type);
  درخت *fields = &TYPE_FIELDS (n);
  برای (درخت x = TYPE_FIELDS (type); x; x = DECL_CHAIN (x))
    {
      درخت f = copy_گره (x);
      اگر (درخت m = ptr_to_tagged_member (x))
	{
	  درخت new_گره = make_گره (درخت_CODE (m));
	  TYPE_NAME (new_گره) = TYPE_NAME (m);
	  SET_TYPE_STRUCTURAL_EQUALITY (new_گره);
	  new_گره = qualify_type (new_گره, m);
	  درخت_TYPE (f) = c_reconstruct_complex_type (درخت_TYPE (x),
						      new_گره);
	}
      *fields = f;
      fields = &DECL_CHAIN (f);
    }
  TYPE_CANONICAL (n) = n;
  بازگشت n;
}


/* If NTYPE is a type of a non-variadic function with a prototype
   and OTYPE is a type of a function without a prototype and ATTRS
   contains attribute format, diagnosess and removes it from ATTRS.
   Returns the result of build_type_attribute_variant of NTYPE and
   the (possibly) modified ATTRS.  */

ایستا درخت
c_build_functype_attribute_variant (درخت ntype, درخت otype, درخت attrs)
{
  اگر (!prototype_p (otype)
      && prototype_p (ntype)
      && lookup_attribute ("format", attrs))
    {
      warning_at (درون_داد_location, OPT_Wattributes,
		  "%qs attribute can only be applied to variadic functions",
		  "format");
      attrs = remove_attribute ("format", attrs);
    }
  بازگشت c_build_type_attribute_variant (ntype, attrs);

}

/* Given a type which could be a typedef name, make sure to return the
   original type.  See set_underlying_type. */
ایستا const_درخت
c_type_original (const_درخت t)
{
  /* It may even be a typedef of a typedef...
     In the case of compiler-created builtin structs the TYPE_DECL
     may be a dummy, with no DECL_ORIGINAL_TYPE.  Don't fault.  */
  وقتی (TYPE_NAME (t)
	 && درخت_CODE (TYPE_NAME (t)) == TYPE_DECL
	 && DECL_ORIGINAL_TYPE (TYPE_NAME (t)))
    t = DECL_ORIGINAL_TYPE (TYPE_NAME (t));
  بازگشت t;
}

/* Return the tag for a tagged type.  */
درخت
c_type_tag (const_درخت t)
{
  gcc_assert (RECORD_OR_UNION_TYPE_P (t) || درخت_CODE (t) == ENUMERAL_TYPE);
  const_درخت orig = c_type_original (t);
  درخت name = TYPE_NAME (orig);
  اگر (!name)
    بازگشت NULL_درخت;
  اگر (درخت_CODE (name) == TYPE_DECL)
    {
      اگر (!DECL_NAME (name))
	بازگشت NULL_درخت;
      name = DECL_NAME (name);
    }
  gcc_checking_assert (درخت_CODE (name) == IDENTIFIER_گره);
  بازگشت name;
}

/* Remove qualifiers but not atomic.  For arrays remove qualifiers
   on the element type but also do not remove atomic.  */
ایستا درخت
remove_qualifiers (درخت t)
{
  اگر (!t || t == error_mark_گره)
    بازگشت t;
  بازگشت TYPE_ATOMIC (strip_array_types (t))
	 ? c_build_qualified_type (TYPE_MAIN_VARIANT (t), TYPE_QUAL_ATOMIC)
	 : TYPE_MAIN_VARIANT (t);
}


/* Helper function for composite_type_internal.  Find a compatible type
   in a (transparent) union U compatible to T.  If found, return the
   type of the corresponding member.  Otherwise, return the union type U.  */
ایستا درخت
transparent_union_replacement (درخت u, درخت t)
{
  اگر (u == error_mark_گره || t == error_mark_گره
      || درخت_CODE (u) != UNION_TYPE
      || !(TYPE_TRANSPARENT_AGGR (u) || TYPE_NAME (u) == NULL_درخت)
      || comptypes (u, t))
    بازگشت u;

  برای (درخت memb = TYPE_FIELDS (u); memb; memb = DECL_CHAIN (memb))
    {
      درخت m = remove_qualifiers (درخت_TYPE (memb));
      اگر (comptypes (m, t))
	{
	  pedwarn (درون_داد_location, OPT_Wpedantic,
		    "function types not truly compatible in ISO C");
	  بازگشت m;
	}
    }

  بازگشت u;
}



/* Return the composite type of two compatible types.

   We assume that comptypes has already been done and returned
   nonzero; if that isn't so, this may crash.  In particular, we
   assume that qualifiers match.  */

ساختار composite_cache {
  درخت t1;
  درخت t2;
  درخت composite;
  ساختار composite_cache* next;
};

درخت
composite_type_internal (درخت t1, درخت t2, درخت cond,
			 ساختار composite_cache* cache)
{
  شمارش درخت_code code1;
  شمارش درخت_code code2;
  درخت attributes;

  /* Save time if the two types are the same.  */

  اگر (t1 == t2) بازگشت t1;

  /* If one type is nonsense, use the other.  */
  اگر (t1 == error_mark_گره)
    بازگشت t2;
  اگر (t2 == error_mark_گره)
    بازگشت t1;

  code1 = درخت_CODE (t1);
  code2 = درخت_CODE (t2);

  /* Merge the attributes.  */
  attributes = targetm.merge_type_attributes (t1, t2);

  /* If one is an enumerated type and the other is the compatible
     integer type, the composite type might be either of the two
     (DR#013 question 3).  For consistency, use the enumerated type as
     the composite type.  */

  اگر (code1 == ENUMERAL_TYPE
      && (code2 == INTEGER_TYPE
	  || code2 == BOOLEAN_TYPE))
    بازگشت t1;
  اگر (code2 == ENUMERAL_TYPE
      && (code1 == INTEGER_TYPE
	  || code1 == BOOLEAN_TYPE))
    بازگشت t2;

  gcc_assert (code1 == code2);

  انتخاب (code1)
    {
    حالت POINTER_TYPE:
      /* For two pointers, do this recursively on the target type.  */
      {
	gcc_checking_assert (TYPE_QUALS (t1) == TYPE_QUALS (t2));
	درخت target = composite_type_internal (درخت_TYPE (t1), درخت_TYPE (t2),
					       cond, cache);
	درخت n = c_build_pointer_type_for_mode (target, TYPE_MODE (t1), نادرست);
	بازگشت c_build_type_attribute_qual_variant (n, attributes,
						    TYPE_QUALS (t2));
      }

    حالت ARRAY_TYPE:
      {
	درخت d1 = TYPE_DOMAIN (t1);
	درخت d2 = TYPE_DOMAIN (t2);

	/* We should not have any type quals on arrays at all.  */
	gcc_assert (!TYPE_QUALS_NO_ADDR_SPACE (t1)
		    && !TYPE_QUALS_NO_ADDR_SPACE (t2));

	منطقی d1_zero = zero_length_array_type_p (t1)
		       || flexible_array_member_type_p (t1);
	منطقی d2_zero = zero_length_array_type_p (t2)
		       || flexible_array_member_type_p (t2);

	منطقی d1_variable = بالاترین_array_vla_p (t1);
	منطقی d2_variable = بالاترین_array_vla_p (t2);

	منطقی use1 = d1 && (d2_variable || !d2 || d2_zero || !d1_variable);
	منطقی use2 = d2 && (d1_variable || !d1 || d1_zero || !d2_variable);

	/* If the first is an unspecified size pick the other one.  */
	اگر (d2_variable && c_type_unspecified_p (t1))
	  {
	    gcc_assert (use1 && use2);
	    use1 = نادرست;
	  }

	/* If both are VLAs but not unspecified and we are in the
	   conditional operator, we create a conditional to select
	   the size of the active branch.  */
	منطقی use0 = cond && d1_variable && !c_type_unspecified_p (t1)
			 && d2_variable && !c_type_unspecified_p (t2);

	درخت td;
	درخت elt = composite_type_internal (درخت_TYPE (t1), درخت_TYPE (t2),
					    cond, cache);

	اگر (!use0)
	  {
	    /* Save space: see if the result is identical to one of the args.  */
	    اگر (elt == درخت_TYPE (t1) && use1)
	      بازگشت c_build_type_attribute_variant (t1, attributes);
	    اگر (elt == درخت_TYPE (t2) && use2)
	      بازگشت c_build_type_attribute_variant (t2, attributes);

	    اگر (elt == درخت_TYPE (t1) && !TYPE_DOMAIN (t2) && !TYPE_DOMAIN (t1))
	      بازگشت c_build_type_attribute_variant (t1, attributes);
	    اگر (elt == درخت_TYPE (t2) && !TYPE_DOMAIN (t2) && !TYPE_DOMAIN (t1))
	      بازگشت c_build_type_attribute_variant (t2, attributes);

	    td = TYPE_DOMAIN (use1 ? t1 : t2);
	  }
	وگرنه
	  {
	    /* Not used in C.  */
	    gcc_assert (size_zero_گره == TYPE_MIN_مقدار (d1));
	    gcc_assert (size_zero_گره == TYPE_MIN_مقدار (d2));

	    درخت d = fold_build3_loc (UNKNOWN_LOCATION, COND_عبارت, sizetype,
				      cond, TYPE_MAX_مقدار (d1),
				      TYPE_MAX_مقدار (d2));

	    td = build_index_type (d);
	  }

	/* Merge the element types, and have a size if either arg has
	   one.  We may have qualifiers on the element types.  To set
	   up TYPE_MAIN_VARIANT correctly, we need to form the
	   composite of the unqualified types and add the qualifiers
	   back at the end.  */
	صحیح quals = TYPE_QUALS (strip_array_types (elt));
	درخت unqual_elt = c_build_qualified_type (elt, TYPE_UNQUALIFIED);

	اگر ((!d1 || d1_zero) && (!d2 || d2_zero) && (d1 || d2))
	  t1 = c_build_array_type_zero_size (unqual_elt);
	وگرنه
	  t1 = c_build_array_type (unqual_elt, td);

	/* Check that a type which has a varying outermost dimension
	   got marked as having a variable size.  */
	منطقی varsize = (d1_variable && d2_variable)
		       || (d1_variable && !d2)
		       || (d2_variable && !d1);
	gcc_checking_assert (!varsize || C_TYPE_VARIABLE_SIZE (t1));

	t1 = c_build_qualified_type (t1, quals);
	بازگشت c_build_type_attribute_variant (t1, attributes);
      }

    حالت RECORD_TYPE:
    حالت UNION_TYPE:
      اگر (flag_isoc23 && !comptypes_same_p (t1, t2))
	{
	  /* Go to the original type to get the right tag.  */
	  درخت tag = c_type_tag (t1);

	  gcc_checking_assert (COMPLETE_TYPE_P (t1) && COMPLETE_TYPE_P (t2));
	  gcc_checking_assert (!tag || comptypes (t1, t2));

	  /* If a composite type for these two types is already under
	     construction, return it.  */

	  برای (ساختار composite_cache *c = cache; c != پوچ; c = c->next)
	    اگر ((c->t1 == t1 && c->t2 == t2) || (c->t1 == t2 && c->t2 == t1))
	       بازگشت c->composite;

	  /* Otherwise, create a new type node and link it into the cache.  */

	  درخت n = make_گره (code1);
	  SET_TYPE_STRUCTURAL_EQUALITY (n);
	  TYPE_NAME (n) = tag;

	  ساختار composite_cache cache2 = { t1, t2, n, cache };
	  cache = &cache2;

	  درخت f1 = TYPE_FIELDS (t1);
	  درخت f2 = TYPE_FIELDS (t2);
	  درخت fields = NULL_درخت;

	  برای (درخت a = f1, b = f2; a && b;
	       a = DECL_CHAIN (a), b = DECL_CHAIN (b))
	    {
	      درخت ta = درخت_TYPE (a);
	      درخت tb = درخت_TYPE (b);

	      اگر (DECL_C_BIT_FIELD (a))
		{
		  ta = DECL_BIT_FIELD_TYPE (a);
		  tb = DECL_BIT_FIELD_TYPE (b);
		}

	      gcc_assert (DECL_NAME (a) == DECL_NAME (b));
	      gcc_checking_assert (!DECL_NAME (a) || comptypes (ta, tb));

	      درخت t = composite_type_internal (ta, tb, cond, cache);
	      درخت f = build_decl (درون_داد_location, FIELD_DECL, DECL_NAME (a), t);

	      DECL_PACKED (f) = DECL_PACKED (a);
	      SET_DECL_ALIGN (f, DECL_ALIGN (a));
	      DECL_ATTRIBUTES (f) = DECL_ATTRIBUTES (a);
	      C_DECL_VARIABLE_SIZE (f) = C_TYPE_VARIABLE_SIZE (t);

	      decl_attributes (&f, DECL_ATTRIBUTES (f), 0);

	      finish_decl (f, درون_داد_location, پوچ, پوچ, پوچ);

	      اگر (DECL_C_BIT_FIELD (a))
		{
		  /* This will be processed by finish_struct.  */
		  SET_DECL_C_BIT_FIELD (f);
		  DECL_INITIAL (f) = build_int_cst (integer_type_گره,
						    درخت_to_uhwi (DECL_SIZE (a)));
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

	  n = finish_struct (درون_داد_location, n, fields, attributes, پوچ,
			     &عبارت);

	  بازگشت qualify_type (n, t1);
	}
      /* FALLTHRU */
    حالت ENUMERAL_TYPE:
      اگر (attributes != پوچ)
	{
	  /* Try harder not to create a new aggregate type.  */
	  اگر (attribute_list_equal (TYPE_ATTRIBUTES (t1), attributes))
	    بازگشت t1;
	  اگر (attribute_list_equal (TYPE_ATTRIBUTES (t2), attributes))
	    بازگشت t2;
	}
      بازگشت c_build_type_attribute_variant (t1, attributes);

    حالت FUNCTION_TYPE:
      /* Function types: prefer the one that specified arg types.
	 If both do, merge the arg types.  Also merge the return types.  */
      {
	درخت valtype = composite_type_internal (درخت_TYPE (t1), درخت_TYPE (t2),
						cond, cache);
	درخت p1 = TYPE_ARG_TYPES (t1);
	درخت p2 = TYPE_ARG_TYPES (t2);

	/* Save space: see if the result is identical to one of the args.  */
	اگر (valtype == درخت_TYPE (t1) && !TYPE_ARG_TYPES (t2))
	  بازگشت c_build_functype_attribute_variant (t1, t2, attributes);
	اگر (valtype == درخت_TYPE (t2) && !TYPE_ARG_TYPES (t1))
	  بازگشت c_build_functype_attribute_variant (t2, t1, attributes);

	/* Simple way if one arg fails to specify argument types.  */
	اگر (TYPE_ARG_TYPES (t1) == NULL_درخت)
	  {
	    t1 = c_build_function_type (valtype, TYPE_ARG_TYPES (t2),
					TYPE_NO_NAMED_ARGS_STDARG_P (t2));
	    t1 = c_build_type_attribute_variant (t1, attributes);
	    بازگشت qualify_type (t1, t2);
	 }
	اگر (TYPE_ARG_TYPES (t2) == NULL_درخت)
	  {
	    t1 = c_build_function_type (valtype, TYPE_ARG_TYPES (t1),
					TYPE_NO_NAMED_ARGS_STDARG_P (t1));
	    t1 = c_build_type_attribute_variant (t1, attributes);
	    بازگشت qualify_type (t1, t2);
	  }

	/* If both args specify argument types, we must merge the two
	   lists, argument by argument.  */
	درخت newargs = NULL_درخت;
	درخت *endp = &newargs;

	برای (; p1; p1 = درخت_CHAIN (p1), p2 = درخت_CHAIN (p2))
	  {
	    اگر (p1 == void_list_گره)
	      {
		*endp = void_list_گره;
		بشکن;
	      }
	    درخت mv1 = remove_qualifiers (درخت_مقدار (p1));
	    درخت mv2 = remove_qualifiers (درخت_مقدار (p2));

	    gcc_assert (mv1);
	    gcc_assert (mv2);

	    mv1 = transparent_union_replacement (mv1, mv2);
	    mv2 = transparent_union_replacement (mv2, mv1);

	    *endp = درخت_cons (NULL_درخت,
			       composite_type_internal (mv1, mv2, cond, cache),
			       NULL_درخت);

	    endp = &درخت_CHAIN (*endp);
	  }

	t1 = c_build_function_type (valtype, newargs);
	t1 = qualify_type (t1, t2);
      }
      /* FALLTHRU */

    پیشفرض:
      بازگشت c_build_type_attribute_variant (t1, attributes);
    }
}

درخت
composite_type_cond (درخت t1, درخت t2, درخت cond)
{
  gcc_checking_assert (comptypes_check_for_composite (t1, t2));

  ساختار composite_cache cache = { };
  درخت n = composite_type_internal (t1, t2, cond, &cache);

  gcc_checking_assert (comptypes_check_for_composite (n, t1));
  gcc_checking_assert (comptypes_check_for_composite (n, t2));
  بازگشت n;
}


درخت
composite_type (درخت t1, درخت t2)
{
  بازگشت composite_type_cond (t1, t2, NULL_درخت);
}

/* Return the type of a conditional expression between pointers to
   possibly differently qualified versions of compatible types.

   We assume that comp_target_types has already been done and returned
   true; if that isn't so, this may crash.  */

ایستا درخت
common_pointer_type (درخت t1, درخت t2, درخت cond)
{
  درخت attributes;
  unsigned target_quals;
  addr_space_t as1, as2, as_common;
  صحیح quals1, quals2;

  /* Save time if the two types are the same.  */

  اگر (t1 == t2) بازگشت t1;

  /* If one type is nonsense, use the other.  */
  اگر (t1 == error_mark_گره)
    بازگشت t2;
  اگر (t2 == error_mark_گره)
    بازگشت t1;

  gcc_assert (درخت_CODE (t1) == POINTER_TYPE
	      && درخت_CODE (t2) == POINTER_TYPE);

  /* Merge the attributes.  */
  attributes = targetm.merge_type_attributes (t1, t2);

  /* Find the composite type of the target types, and combine the
     qualifiers of the two types' targets.  */
  درخت pointed_to_1 = درخت_TYPE (t1);
  درخت pointed_to_2 = درخت_TYPE (t2);
  درخت target = composite_type_cond (TYPE_MAIN_VARIANT (pointed_to_1),
				     TYPE_MAIN_VARIANT (pointed_to_2), cond);

  /* Strip array types to get correct qualifier for pointers to arrays */
  quals1 = TYPE_QUALS_NO_ADDR_SPACE (strip_array_types (pointed_to_1));
  quals2 = TYPE_QUALS_NO_ADDR_SPACE (strip_array_types (pointed_to_2));

  /* For function types do not merge const qualifiers, but drop them
     if used inconsistently.  The middle-end uses these to mark const
     and noreturn functions.  */
  اگر (درخت_CODE (pointed_to_1) == FUNCTION_TYPE)
    target_quals = (quals1 & quals2);
  وگرنه
    target_quals = (quals1 | quals2);

  /* If the two named address spaces are different, determine the common
     superset address space.  This is guaranteed to exist due to the
     assumption that comp_target_type returned true.  */
  as1 = TYPE_ADDR_SPACE (pointed_to_1);
  as2 = TYPE_ADDR_SPACE (pointed_to_2);
  اگر (!addr_space_superset (as1, as2, &as_common))
    gcc_unreachable ();

  target_quals |= ENCODE_QUAL_ADDR_SPACE (as_common);

  t1 = c_build_pointer_type (c_build_qualified_type (target, target_quals));
  بازگشت c_build_type_attribute_variant (t1, attributes);
}

/* Return the common type for two arithmetic types under the usual
   arithmetic conversions.  The default conversions have already been
   applied, and enumerated types converted to their compatible integer
   types.  The resulting type is unqualified and has no attributes.

   This is the type for the result of most arithmetic operations
   if the operands have the given two types.  */

ایستا درخت
c_common_type (درخت t1, درخت t2)
{
  شمارش درخت_code code1;
  شمارش درخت_code code2;

  /* If one type is nonsense, use the other.  */
  اگر (t1 == error_mark_گره)
    بازگشت t2;
  اگر (t2 == error_mark_گره)
    بازگشت t1;

  اگر (TYPE_QUALS (t1) != TYPE_UNQUALIFIED)
    t1 = TYPE_MAIN_VARIANT (t1);

  اگر (TYPE_QUALS (t2) != TYPE_UNQUALIFIED)
    t2 = TYPE_MAIN_VARIANT (t2);

  اگر (TYPE_ATTRIBUTES (t1) != NULL_درخت)
    {
      درخت attrs = affects_type_identity_attributes (TYPE_ATTRIBUTES (t1));
      t1 = c_build_type_attribute_variant (t1, attrs);
    }

  اگر (TYPE_ATTRIBUTES (t2) != NULL_درخت)
    {
      درخت attrs = affects_type_identity_attributes (TYPE_ATTRIBUTES (t2));
      t2 = c_build_type_attribute_variant (t2, attrs);
    }

  /* Save time if the two types are the same.  */

  اگر (t1 == t2) بازگشت t1;

  code1 = درخت_CODE (t1);
  code2 = درخت_CODE (t2);

  gcc_assert (code1 == VECTOR_TYPE || code1 == COMPLEX_TYPE
	      || code1 == FIXED_POINT_TYPE || code1 == REAL_TYPE
	      || code1 == INTEGER_TYPE || code1 == BITINT_TYPE);
  gcc_assert (code2 == VECTOR_TYPE || code2 == COMPLEX_TYPE
	      || code2 == FIXED_POINT_TYPE || code2 == REAL_TYPE
	      || code2 == INTEGER_TYPE || code2 == BITINT_TYPE);

  /* When one operand is a decimal float type, the other operand cannot be
     a generic float type or a complex type.  We also disallow vector types
     here.  */
  اگر ((DECIMAL_FLOAT_TYPE_P (t1) || DECIMAL_FLOAT_TYPE_P (t2))
      && !(DECIMAL_FLOAT_TYPE_P (t1) && DECIMAL_FLOAT_TYPE_P (t2)))
    {
      اگر (code1 == VECTOR_TYPE || code2 == VECTOR_TYPE)
	{
	  error ("cannot mix operands of decimal floating and vector types");
	  بازگشت error_mark_گره;
	}
      اگر (code1 == COMPLEX_TYPE || code2 == COMPLEX_TYPE)
	{
	  error ("cannot mix operands of decimal floating and complex types");
	  بازگشت error_mark_گره;
	}
      اگر (code1 == REAL_TYPE && code2 == REAL_TYPE)
	{
	  error ("cannot mix operands of decimal floating "
		 "and other floating types");
	  بازگشت error_mark_گره;
	}
    }

  /* If one type is a vector type, return that type.  (How the usual
     arithmetic conversions apply to the vector types extension is not
     precisely specified.)  */
  اگر (code1 == VECTOR_TYPE)
    بازگشت t1;

  اگر (code2 == VECTOR_TYPE)
    بازگشت t2;

  /* If one type is complex, form the common type of the non-complex
     components, then make that complex.  Use T1 or T2 if it is the
     required type.  */
  اگر (code1 == COMPLEX_TYPE || code2 == COMPLEX_TYPE)
    {
      درخت subtype1 = code1 == COMPLEX_TYPE ? درخت_TYPE (t1) : t1;
      درخت subtype2 = code2 == COMPLEX_TYPE ? درخت_TYPE (t2) : t2;
      درخت subtype = c_common_type (subtype1, subtype2);

      اگر (code1 == COMPLEX_TYPE && درخت_TYPE (t1) == subtype)
	بازگشت t1;
      وگرنه اگر (code2 == COMPLEX_TYPE && درخت_TYPE (t2) == subtype)
	بازگشت t2;
      وگرنه اگر (درخت_CODE (subtype) == BITINT_TYPE)
	{
	  sorry ("%<_Complex _BitInt(%d)%> unsupported",
		 TYPE_PRECISION (subtype));
	  بازگشت code1 == COMPLEX_TYPE ? t1 : t2;
	}
      وگرنه
	بازگشت build_complex_type (subtype);
    }

  /* If only one is real, use it as the result.  */

  اگر (code1 == REAL_TYPE && code2 != REAL_TYPE)
    بازگشت t1;

  اگر (code2 == REAL_TYPE && code1 != REAL_TYPE)
    بازگشت t2;

  /* If both are real and either are decimal floating point types, use
     the decimal floating point type with the greater precision. */

  اگر (code1 == REAL_TYPE && code2 == REAL_TYPE)
    {
      اگر (TYPE_MAIN_VARIANT (t1) == dfloat128_type_گره
	  || TYPE_MAIN_VARIANT (t2) == dfloat128_type_گره)
	بازگشت dfloat128_type_گره;
      /* And prefer _Decimal128 over _Decimal64x which has in GCC's
	 implementation the same mode.  */
      وگرنه اگر (TYPE_MAIN_VARIANT (t1) == dfloat64x_type_گره
	       || TYPE_MAIN_VARIANT (t2) == dfloat64x_type_گره)
	بازگشت dfloat64x_type_گره;
      وگرنه اگر (TYPE_MAIN_VARIANT (t1) == dfloat64_type_گره
	       || TYPE_MAIN_VARIANT (t2) == dfloat64_type_گره)
	بازگشت dfloat64_type_گره;
      وگرنه اگر (TYPE_MAIN_VARIANT (t1) == dfloat32_type_گره
	       || TYPE_MAIN_VARIANT (t2) == dfloat32_type_گره)
	بازگشت dfloat32_type_گره;
    }

  /* Deal with fixed-point types.  */
  اگر (code1 == FIXED_POINT_TYPE || code2 == FIXED_POINT_TYPE)
    {
      unsigned صحیح unsignedp = 0, satp = 0;
      scalar_mode m1, m2;
      unsigned صحیح fbit1, ibit1, fbit2, ibit2, max_fbit, max_ibit;

      m1 = SCALAR_TYPE_MODE (t1);
      m2 = SCALAR_TYPE_MODE (t2);

      /* If one input type is saturating, the result type is saturating.  */
      اگر (TYPE_SATURATING (t1) || TYPE_SATURATING (t2))
	satp = 1;

      /* If both fixed-point types are unsigned, the result type is unsigned.
	 When mixing fixed-point and integer types, follow the sign of the
	 fixed-point type.
	 Otherwise, the result type is signed.  */
      اگر ((TYPE_UNSIGNED (t1) && TYPE_UNSIGNED (t2)
	   && code1 == FIXED_POINT_TYPE && code2 == FIXED_POINT_TYPE)
	  || (code1 == FIXED_POINT_TYPE && code2 != FIXED_POINT_TYPE
	      && TYPE_UNSIGNED (t1))
	  || (code1 != FIXED_POINT_TYPE && code2 == FIXED_POINT_TYPE
	      && TYPE_UNSIGNED (t2)))
	unsignedp = 1;

      /* The result type is signed.  */
      اگر (unsignedp == 0)
	{
	  /* If the input type is unsigned, we need to convert to the
	     signed type.  */
	  اگر (code1 == FIXED_POINT_TYPE && TYPE_UNSIGNED (t1))
	    {
	      شمارش mode_class mclass = (شمارش mode_class) 0;
	      اگر (GET_MODE_CLASS (m1) == MODE_UFRACT)
		mclass = MODE_FRACT;
	      وگرنه اگر (GET_MODE_CLASS (m1) == MODE_UACCUM)
		mclass = MODE_ACCUM;
	      وگرنه
		gcc_unreachable ();
	      m1 = as_a <scalar_mode>
		(mode_for_size (GET_MODE_PRECISION (m1), mclass, 0));
	    }
	  اگر (code2 == FIXED_POINT_TYPE && TYPE_UNSIGNED (t2))
	    {
	      شمارش mode_class mclass = (شمارش mode_class) 0;
	      اگر (GET_MODE_CLASS (m2) == MODE_UFRACT)
		mclass = MODE_FRACT;
	      وگرنه اگر (GET_MODE_CLASS (m2) == MODE_UACCUM)
		mclass = MODE_ACCUM;
	      وگرنه
		gcc_unreachable ();
	      m2 = as_a <scalar_mode>
		(mode_for_size (GET_MODE_PRECISION (m2), mclass, 0));
	    }
	}

      اگر (code1 == FIXED_POINT_TYPE)
	{
	  fbit1 = GET_MODE_FBIT (m1);
	  ibit1 = GET_MODE_IBIT (m1);
	}
      وگرنه
	{
	  fbit1 = 0;
	  /* Signed integers need to subtract one sign bit.  */
	  ibit1 = TYPE_PRECISION (t1) - (!TYPE_UNSIGNED (t1));
	}

      اگر (code2 == FIXED_POINT_TYPE)
	{
	  fbit2 = GET_MODE_FBIT (m2);
	  ibit2 = GET_MODE_IBIT (m2);
	}
      وگرنه
	{
	  fbit2 = 0;
	  /* Signed integers need to subtract one sign bit.  */
	  ibit2 = TYPE_PRECISION (t2) - (!TYPE_UNSIGNED (t2));
	}

      max_ibit = ibit1 >= ibit2 ?  ibit1 : ibit2;
      max_fbit = fbit1 >= fbit2 ?  fbit1 : fbit2;
      بازگشت c_common_fixed_point_type_for_size (max_ibit, max_fbit, unsignedp,
						 satp);
    }

  /* Both real or both integers; use the one with greater precision.  */

  اگر (TYPE_PRECISION (t1) > TYPE_PRECISION (t2))
    بازگشت t1;
  وگرنه اگر (TYPE_PRECISION (t2) > TYPE_PRECISION (t1))
    بازگشت t2;

  /* Same precision.  Prefer long longs to longs to ints when the
     same precision, following the C99 rules on integer type rank
     (which are equivalent to the C90 rules for C90 types).  */

  اگر (TYPE_MAIN_VARIANT (t1) == long_long_unsigned_type_گره
      || TYPE_MAIN_VARIANT (t2) == long_long_unsigned_type_گره)
    بازگشت long_long_unsigned_type_گره;

  اگر (TYPE_MAIN_VARIANT (t1) == long_long_integer_type_گره
      || TYPE_MAIN_VARIANT (t2) == long_long_integer_type_گره)
    {
      اگر (TYPE_UNSIGNED (t1) || TYPE_UNSIGNED (t2))
	بازگشت long_long_unsigned_type_گره;
      وگرنه
	بازگشت long_long_integer_type_گره;
    }

  اگر (TYPE_MAIN_VARIANT (t1) == long_unsigned_type_گره
      || TYPE_MAIN_VARIANT (t2) == long_unsigned_type_گره)
    بازگشت long_unsigned_type_گره;

  اگر (TYPE_MAIN_VARIANT (t1) == long_integer_type_گره
      || TYPE_MAIN_VARIANT (t2) == long_integer_type_گره)
    {
      /* But preserve unsignedness from the other type,
	 since long cannot hold all the values of an unsigned int.  */
      اگر (TYPE_UNSIGNED (t1) || TYPE_UNSIGNED (t2))
	بازگشت long_unsigned_type_گره;
      وگرنه
	بازگشت long_integer_type_گره;
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

  برای (صحیح i = رقم_FLOATN_TYPES - 1; i >= 0; i--)
    اگر (mv1 == FLOATN_TYPE_گره (i) || mv2 == FLOATN_TYPE_گره (i))
      بازگشت FLOATN_TYPE_گره (i);

  /* Likewise, prefer long double to double even if same size.  */
  اگر (mv1 == long_double_type_گره || mv2 == long_double_type_گره)
    بازگشت long_double_type_گره;

  /* Likewise, prefer double to float even if same size.
     We got a couple of embedded targets with 32 bit doubles, and the
     pdp11 might have 64 bit floats.  */
  اگر (mv1 == double_type_گره || mv2 == double_type_گره)
    بازگشت double_type_گره;

  اگر (mv1 == float_type_گره || mv2 == float_type_گره)
    بازگشت float_type_گره;

  برای (صحیح i = رقم_FLOATNX_TYPES - 1; i >= 0; i--)
    اگر (mv1 == FLOATNX_TYPE_گره (i) || mv2 == FLOATNX_TYPE_گره (i))
      بازگشت FLOATNX_TYPE_گره (i);

  اگر ((code1 == BITINT_TYPE || code2 == BITINT_TYPE) && code1 != code2)
    {
      /* Prefer any other integral types over bit-precise integer types.  */
      اگر (TYPE_UNSIGNED (t1) == TYPE_UNSIGNED (t2))
	بازگشت code1 == BITINT_TYPE ? t2 : t1;
      /* If BITINT_TYPE is unsigned and the other type is signed
	 non-BITINT_TYPE with the same precision, the latter has higher rank.
	 In that case:
	 Otherwise, both operands are converted to the unsigned integer type
	 corresponding to the type of the operand with signed integer type.  */
      اگر (TYPE_UNSIGNED (code1 == BITINT_TYPE ? t1 : t2))
	بازگشت c_common_unsigned_type (code1 == BITINT_TYPE ? t2 : t1);
    }

  /* Otherwise prefer the unsigned one.  */

  اگر (TYPE_UNSIGNED (t1))
    بازگشت t1;
  وگرنه
    بازگشت t2;
}

/* Wrapper around c_common_type that is used by c-common.cc and other
   front end optimizations that remove promotions.  ENUMERAL_TYPEs
   are allowed here and are converted to their compatible integer types.
   BOOLEAN_TYPEs are allowed here and return either boolean_type_node or
   preferably a non-Boolean type as the common type.  */
درخت
common_type (درخت t1, درخت t2)
{
  اگر (درخت_CODE (t1) == ENUMERAL_TYPE)
    t1 = ENUM_UNDERLYING_TYPE (t1);
  اگر (درخت_CODE (t2) == ENUMERAL_TYPE)
    t2 = ENUM_UNDERLYING_TYPE (t2);

  /* If both types are BOOLEAN_TYPE, then return boolean_type_node.  */
  اگر (درخت_CODE (t1) == BOOLEAN_TYPE
      && درخت_CODE (t2) == BOOLEAN_TYPE)
    بازگشت boolean_type_گره;

  /* If either type is BOOLEAN_TYPE, then return the other.  */
  اگر (درخت_CODE (t1) == BOOLEAN_TYPE)
    بازگشت t2;
  اگر (درخت_CODE (t2) == BOOLEAN_TYPE)
    بازگشت t1;

  بازگشت c_common_type (t1, t2);
}



/* Helper function for comptypes.  For two compatible types, return 1
   if they pass consistency checks.  In particular we test that
   TYPE_CANONICAL is set correctly, i.e. the two types can alias.  */

ایستا منطقی
comptypes_verify (درخت type1, درخت type2)
{
  اگر (type1 == type2 || !type1 || !type2
      || درخت_CODE (type1) == ERROR_MARK || درخت_CODE (type2) == ERROR_MARK)
    بازگشت درست;

  gcc_checking_assert (c_verify_type (type1));
  gcc_checking_assert (c_verify_type (type2));

  اگر (TYPE_CANONICAL (type1) != TYPE_CANONICAL (type2)
      && !TYPE_STRUCTURAL_EQUALITY_P (type1)
      && !TYPE_STRUCTURAL_EQUALITY_P (type2))
    {
      /* FIXME: check other types. */
      اگر (RECORD_OR_UNION_TYPE_P (type1)
	  || درخت_CODE (type1) == ENUMERAL_TYPE
	  || درخت_CODE (type2) == ENUMERAL_TYPE)
	بازگشت نادرست;
    }
  بازگشت درست;
}

ساختار comptypes_data {

  /* output */
  منطقی enum_and_int_p;
  منطقی different_types_p;
  منطقی warning_needed;

  /* context */
  منطقی anon_field;
  منطقی pointedto;

  /* configuration */
  منطقی equiv;
  منطقی ignore_promoting_args;

  ثابت ساختار tagged_tu_seen_cache* cache;
};


/* Helper function for composite_type.  This function ignores when the
   function type of an old-style declaration is incompatible with a type
   of a declaration with prototype because some are arguments are not
   self-promoting.  This is ignored only for function types but not
   ignored in a nested context.  */

ایستا منطقی
comptypes_check_for_composite (درخت t1, درخت t2)
{
  ساختار comptypes_data data = { };
  data.ignore_promoting_args = FUNCTION_TYPE == درخت_CODE (t1);
  بازگشت comptypes_internal (t1, t2, &data);
}


/* C implementation of compatible_types_for_indirection_note_p.  */

منطقی
compatible_types_for_indirection_note_p (درخت type1, درخت type2)
{
  بازگشت comptypes (type1, type2);
}

/* Return true if TYPE1 and TYPE2 are compatible types for assignment
   or various other operations.  */

منطقی
comptypes (درخت type1, درخت type2)
{
  ساختار comptypes_data data = { };
  منطقی ret = comptypes_internal (type1, type2, &data);

  gcc_checking_assert (!ret || comptypes_verify (type1, type2));

  بازگشت ret;
}


/* Like comptypes, but it returns non-zero only for identical
   types.  */

منطقی
comptypes_same_p (درخت type1, درخت type2)
{
  ساختار comptypes_data data = { };
  منطقی ret = comptypes_internal (type1, type2, &data);

  gcc_checking_assert (!ret || comptypes_verify (type1, type2));

  اگر (data.different_types_p)
    بازگشت نادرست;

  بازگشت ret;
}


/* Like comptypes, but if it returns true because enum and int are
   compatible, it sets *ENUM_AND_INT_P to true.  */

منطقی
comptypes_check_enum_int (درخت type1, درخت type2, منطقی *enum_and_int_p)
{
  ساختار comptypes_data data = { };
  منطقی ret = comptypes_internal (type1, type2, &data);
  *enum_and_int_p = data.enum_and_int_p;

  gcc_checking_assert (!ret || comptypes_verify (type1, type2));

  بازگشت ret;
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
  ساختار comptypes_data data = { };
  data.equiv = درست;
  منطقی ret = comptypes_internal (type1, type2, &data);

  /* check that different equivance classes are assigned only
     to types that are not compatible.  */
  gcc_checking_assert (ret || !comptypes (type1, type2));

  بازگشت ret;
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

ایستا منطقی
comptypes_internal (const_درخت type1, const_درخت type2,
		    ساختار comptypes_data *data)
{
  const_درخت t1 = type1;
  const_درخت t2 = type2;

  /* Suppress errors caused by previously reported errors.  */

  اگر (t1 == t2 || !t1 || !t2
      || درخت_CODE (t1) == ERROR_MARK || درخت_CODE (t2) == ERROR_MARK)
    بازگشت درست;

  /* Qualifiers must match. C99 6.7.3p9 */

  اگر (TYPE_QUALS (t1) != TYPE_QUALS (t2))
    بازگشت نادرست;

  /* Enumerated types are compatible with integer types, but this is
     not transitive: two enumerated types in the same translation unit
     are compatible with each other only if they are the same type.  */

  اگر (درخت_CODE (t1) == ENUMERAL_TYPE
      && COMPLETE_TYPE_P (t1)
      && درخت_CODE (t2) != ENUMERAL_TYPE)
    {
      t1 = ENUM_UNDERLYING_TYPE (t1);
      اگر (درخت_CODE (t2) != VOID_TYPE)
	{
	  data->enum_and_int_p = درست;
	  data->different_types_p = درست;
	}
    }
  وگرنه اگر (درخت_CODE (t2) == ENUMERAL_TYPE
	   && COMPLETE_TYPE_P (t2)
	   && درخت_CODE (t1) != ENUMERAL_TYPE)
    {
      t2 = ENUM_UNDERLYING_TYPE (t2);
      اگر (درخت_CODE (t1) != VOID_TYPE)
	{
	  data->enum_and_int_p = درست;
	  data->different_types_p = درست;
	}
    }

  اگر (t1 == t2)
    بازگشت درست;

  /* Different classes of types can't be compatible.  */

  اگر (درخت_CODE (t1) != درخت_CODE (t2))
    بازگشت نادرست;

  /* Allow for two different type nodes which have essentially the same
     definition.  Note that we already checked for equality of the type
     qualifiers (just above).  */

  اگر (درخت_CODE (t1) != ARRAY_TYPE
      && TYPE_MAIN_VARIANT (t1) == TYPE_MAIN_VARIANT (t2))
    بازگشت درست;

  صحیح attrval;

  /* 1 if no need for warning yet, 2 if warning cause has been seen.  */
  اگر (!(attrval = comp_type_attributes (t1, t2)))
    بازگشت نادرست;

  اگر (2 == attrval)
    data->warning_needed = درست;

  انتخاب (درخت_CODE (t1))
    {
    حالت INTEGER_TYPE:
    حالت FIXED_POINT_TYPE:
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
      بازگشت TYPE_CANONICAL (t1) == TYPE_CANONICAL (t2);

    حالت POINTER_TYPE:
      /* Do not remove mode information.  */
      اگر (TYPE_MODE (t1) != TYPE_MODE (t2))
	بازگشت نادرست;
      data->pointedto = درست;
      بازگشت comptypes_internal (درخت_TYPE (t1), درخت_TYPE (t2), data);

    حالت FUNCTION_TYPE:
      بازگشت function_types_compatible_p (t1, t2, data);

    حالت ARRAY_TYPE:
      {
	درخت d1 = TYPE_DOMAIN (t1);
	درخت d2 = TYPE_DOMAIN (t2);

	/* Target types must match incl. qualifiers.  */
	اگر (!comptypes_internal (درخت_TYPE (t1), درخت_TYPE (t2), data))
	  بازگشت نادرست;

	اگر ((d1 == NULL_درخت) != (d2 == NULL_درخت))
	  data->different_types_p = درست;
	/* Ignore size mismatches when forming equivalence classes.  */
	اگر (data->equiv)
	  بازگشت درست;
	/* Sizes must match unless one is missing or variable.  */
	اگر (d1 == NULL_درخت || d2 == NULL_درخت || d1 == d2)
	  بازگشت درست;

	منطقی d1_variable = بالاترین_array_vla_p (t1);
	منطقی d2_variable = بالاترین_array_vla_p (t2);

	اگر (d1_variable != d2_variable)
	  data->different_types_p = درست;
	اگر (d1_variable || d2_variable)
	  بازگشت درست;

	منطقی d1_zero = zero_length_array_type_p (t1)
		       || flexible_array_member_type_p (t1);

	منطقی d2_zero = zero_length_array_type_p (t2)
		       || flexible_array_member_type_p (t2);

	اگر (d1_zero && d2_zero)
	  بازگشت درست;
	اگر (d1_zero || d2_zero)
	  بازگشت نادرست;

	اگر (!درخت_int_cst_equal (TYPE_MIN_مقدار (d1), TYPE_MIN_مقدار (d2))
	    || !درخت_int_cst_equal (TYPE_MAX_مقدار (d1), TYPE_MAX_مقدار (d2)))
	  بازگشت نادرست;

	بازگشت درست;
      }

    حالت ENUMERAL_TYPE:
    حالت RECORD_TYPE:
    حالت UNION_TYPE:

      اگر (!flag_isoc23)
	بازگشت نادرست;

      بازگشت tagged_types_tu_compatible_p (t1, t2, data);

    حالت VECTOR_TYPE:
      بازگشت known_eq (TYPE_VECTOR_SUBPARTS (t1), TYPE_VECTOR_SUBPARTS (t2))
	     && comptypes_internal (درخت_TYPE (t1), درخت_TYPE (t2), data);

    پیشفرض:
      بازگشت نادرست;
    }
  gcc_unreachable ();
}

/* Return true if TTL and TTR are pointers to types that are equivalent, ignoring
   their qualifiers, except for named address spaces.  If the pointers point to
   different named addresses, then we must determine if one address space is a
   subset of the other.  */

ایستا منطقی
comp_target_types (location_t location, درخت ttl, درخت ttr)
{
  درخت mvl = درخت_TYPE (ttl);
  درخت mvr = درخت_TYPE (ttr);
  addr_space_t asl = TYPE_ADDR_SPACE (mvl);
  addr_space_t asr = TYPE_ADDR_SPACE (mvr);
  addr_space_t as_common;

  /* Fail if pointers point to incompatible address spaces.  */
  اگر (!addr_space_superset (asl, asr, &as_common))
    بازگشت 0;

  /* Qualifiers on element types of array types that are
     pointer targets are also removed.  */
  ساختار comptypes_data data = { };
  اگر (!comptypes_internal (remove_qualifiers (mvl),
			   remove_qualifiers (mvr), &data))
    بازگشت نادرست;

  /* For pedantic use comptypes on arrays before removing
     qualifiers on the element type. */
  اگر (درخت_CODE (mvl) == ARRAY_TYPE
      && درخت_CODE (mvr) == ARRAY_TYPE
      && !comptypes (mvl, mvr))
    pedwarn_c11 (location, OPT_Wpedantic, "invalid use of pointers to arrays "
					  "with different qualifiers in ISO C "
					  "before C23");

  اگر (data.warning_needed)
    pedwarn (location, OPT_Wpedantic, "types are not quite compatible");

  اگر (data.enum_and_int_p && warn_cxx_compat)
    warning_at (location, OPT_Wc___compat,
		"pointer target types incompatible in C++");

  بازگشت درست;
}

/* Subroutines of `comptypes'.  */

/* Return true if two 'struct', 'union', or 'enum' types T1 and T2 are
   compatible.  The two types are not the same (which has been
   checked earlier in comptypes_internal).  */

ایستا منطقی
tagged_types_tu_compatible_p (const_درخت t1, const_درخت t2,
			      ساختار comptypes_data *data)
{
  درخت s1, s2;

  اگر (c_type_tag (t1) != c_type_tag (t2))
    بازگشت نادرست;

  /* When forming equivalence classes for TYPE_CANONICAL in C23, we treat
     structs with the same tag as equivalent, but only when they are targets
     of pointers inside other structs.  */
  اگر (data->equiv && data->pointedto && NULL_درخت != c_type_tag (t1))
    بازگشت درست;

  /* Different types without tag are incompatible except as an anonymous
     field or when forming equivalence classes for TYPE_CANONICAL.  */
  اگر (!data->anon_field && !data->equiv && NULL_درخت == c_type_tag (t1))
    بازگشت نادرست;

  اگر (!data->anon_field && TYPE_STUB_DECL (t1) != TYPE_STUB_DECL (t2))
    data->different_types_p = درست;

  /* Incomplete types are incompatible inside a TU.  */
  اگر (TYPE_SIZE (t1) == پوچ || TYPE_SIZE (t2) == پوچ)
    بازگشت نادرست;

  اگر (ENUMERAL_TYPE != درخت_CODE (t1)
      && (TYPE_REVERSE_STORAGE_ORDER (t1)
	  != TYPE_REVERSE_STORAGE_ORDER (t2)))
    بازگشت نادرست;

  اگر (TYPE_USER_ALIGN (t1) != TYPE_USER_ALIGN (t2))
    data->different_types_p = درست;

  /* For types already being looked at in some active
     invocation of this function, assume compatibility.
     The cache is built as a linked list on the stack
     with the head of the list passed downwards.  */
  برای (ثابت ساختار tagged_tu_seen_cache *t = data->cache;
       t != پوچ; t = t->next)
    اگر (t->t1 == t1 && t->t2 == t2)
      بازگشت درست;

  ثابت ساختار tagged_tu_seen_cache entry = { data->cache, t1, t2 };

  انتخاب (درخت_CODE (t1))
    {
    حالت ENUMERAL_TYPE:
      {
	اگر (!comptypes (ENUM_UNDERLYING_TYPE (t1), ENUM_UNDERLYING_TYPE (t2)))
	  بازگشت نادرست;

	/* Speed up the case where the type values are in the same order.  */
	درخت tv1 = TYPE_مقادیر (t1);
	درخت tv2 = TYPE_مقادیر (t2);

	اگر (tv1 == tv2)
	  بازگشت درست;

	برای (;tv1 && tv2; tv1 = درخت_CHAIN (tv1), tv2 = درخت_CHAIN (tv2))
	  {
	    اگر (درخت_PURPOSE (tv1) != درخت_PURPOSE (tv2))
	      بشکن;

	    اگر (simple_cst_equal (DECL_INITIAL (درخت_مقدار (tv1)),
				  DECL_INITIAL (درخت_مقدار (tv2))) != 1)
	      بشکن;
	  }

	اگر (tv1 == NULL_درخت && tv2 == NULL_درخت)
	  بازگشت درست;

	اگر (tv1 == NULL_درخت || tv2 == NULL_درخت)
	  بازگشت نادرست;

	اگر (list_length (TYPE_مقادیر (t1)) != list_length (TYPE_مقادیر (t2)))
	  بازگشت نادرست;

	برای (s1 = TYPE_مقادیر (t1); s1; s1 = درخت_CHAIN (s1))
	  {
	    s2 = purpose_member (درخت_PURPOSE (s1), TYPE_مقادیر (t2));

	    اگر (s2 == پوچ
		|| simple_cst_equal (DECL_INITIAL (درخت_مقدار (s1)),
				     DECL_INITIAL (درخت_مقدار (s2))) != 1)
	      بازگشت نادرست;
	  }

	بازگشت درست;
      }

    حالت UNION_TYPE:
    حالت RECORD_TYPE:

	اگر (list_length (TYPE_FIELDS (t1)) != list_length (TYPE_FIELDS (t2)))
	  بازگشت نادرست;

	برای (s1 = TYPE_FIELDS (t1), s2 = TYPE_FIELDS (t2);
	     s1 && s2;
	     s1 = DECL_CHAIN (s1), s2 = DECL_CHAIN (s2))
	  {
	    gcc_assert (درخت_CODE (s1) == FIELD_DECL);
	    gcc_assert (درخت_CODE (s2) == FIELD_DECL);

	    درخت ft1 = درخت_TYPE (s1);
	    درخت ft2 = درخت_TYPE (s2);

	    اگر (DECL_NAME (s1) != DECL_NAME (s2))
	      بازگشت نادرست;

	    اگر (DECL_ALIGN (s1) != DECL_ALIGN (s2))
	      بازگشت نادرست;

	    اگر (DECL_C_BIT_FIELD (s1) != DECL_C_BIT_FIELD (s2))
	       بازگشت نادرست;

	    اگر (DECL_C_BIT_FIELD (s1))
	      {
		اگر (!درخت_int_cst_equal (DECL_SIZE (s1), DECL_SIZE (s2)))
		  بازگشت نادرست;

		ft1 = DECL_BIT_FIELD_TYPE (s1);
		ft2 = DECL_BIT_FIELD_TYPE (s2);
	      }

	    اگر (!ft1 || !ft2)
	      بازگشت نادرست;

	    اگر (درخت_CODE (ft1) == ERROR_MARK || درخت_CODE (ft2) == ERROR_MARK)
	      بازگشت نادرست;

	    data->anon_field = !DECL_NAME (s1);
	    data->pointedto = نادرست;

	    ثابت ساختار tagged_tu_seen_cache *cache = data->cache;
	    data->cache = &entry;
	    منطقی ret = comptypes_internal (ft1, ft2, data);
	    data->cache = cache;
	    اگر (!ret)
	      بازگشت نادرست;

	    درخت st1 = TYPE_SIZE (درخت_TYPE (s1));
	    درخت st2 = TYPE_SIZE (درخت_TYPE (s2));

	    اگر (data->equiv
		&& st1 && درخت_CODE (st1) == INTEGER_CST
		&& st2 && درخت_CODE (st2) == INTEGER_CST
		&& !درخت_int_cst_equal (st1, st2))
	     بازگشت نادرست;

	    درخت counted_by1 = lookup_attribute ("counted_by",
						 DECL_ATTRIBUTES (s1));
	    درخت counted_by2 = lookup_attribute ("counted_by",
						 DECL_ATTRIBUTES (s2));
	    /* If there is no counted_by attribute for both fields.  */
	    اگر (!counted_by1 && !counted_by2)
	      ادامه;

	    /* If only one field has counted_by attribute.  */
	    اگر ((counted_by1 && !counted_by2)
		|| (!counted_by1 && counted_by2))
	      بازگشت نادرست;

	    /* Now both s1 and s2 have counted_by attributes, check
	       whether they are the same.  */

	    درخت counted_by_field1
	      = lookup_field (t1, درخت_مقدار (درخت_مقدار (counted_by1)));
	    درخت counted_by_field2
	      = lookup_field (t2, درخت_مقدار (درخت_مقدار (counted_by2)));

	    gcc_assert (counted_by_field1 && counted_by_field2);

	    وقتی (درخت_CHAIN (counted_by_field1))
	      counted_by_field1 = درخت_CHAIN (counted_by_field1);
	    وقتی (درخت_CHAIN (counted_by_field2))
	      counted_by_field2 = درخت_CHAIN (counted_by_field2);

	    اگر (DECL_NAME (درخت_مقدار (counted_by_field1))
		!= DECL_NAME (درخت_مقدار (counted_by_field2)))
	      بازگشت نادرست;
	  }
	بازگشت درست;

    پیشفرض:
      gcc_unreachable ();
    }
}

/* Return true if two function types F1 and F2 are compatible.
   If either type specifies no argument types,
   the other must specify a fixed number of self-promoting arg types.
   Otherwise, if one type specifies only the number of arguments,
   the other must specify that number of self-promoting arg types.
   Otherwise, the argument types must match.  */

ایستا منطقی
function_types_compatible_p (const_درخت f1, const_درخت f2,
			     ساختار comptypes_data *data)
{
  درخت ret1 = درخت_TYPE (f1);
  درخت ret2 = درخت_TYPE (f2);

  /* 'volatile' qualifiers on a function's return type used to mean
     the function is noreturn.  */
  اگر (TYPE_VOLATILE (ret1) != TYPE_VOLATILE (ret2))
    pedwarn (درون_داد_location, 0, "function return types not compatible due to %<volatile%>");
  اگر (TYPE_VOLATILE (ret1))
    ret1 = build_qualified_type (TYPE_MAIN_VARIANT (ret1),
				 TYPE_QUALS (ret1) & ~TYPE_QUAL_VOLATILE);
  اگر (TYPE_VOLATILE (ret2))
    ret2 = build_qualified_type (TYPE_MAIN_VARIANT (ret2),
				 TYPE_QUALS (ret2) & ~TYPE_QUAL_VOLATILE);

  منطقی ignore_pargs = data->ignore_promoting_args;
  data->ignore_promoting_args = نادرست;

  اگر (!comptypes_internal (ret1, ret2, data))
    بازگشت نادرست;

  data->ignore_promoting_args = ignore_pargs;

  درخت args1 = TYPE_ARG_TYPES (f1);
  درخت args2 = TYPE_ARG_TYPES (f2);

  اگر ((args1 == NULL_درخت) != (args2 == NULL_درخت))
    data->different_types_p = درست;

  /* An unspecified parmlist matches any specified parmlist
     whose argument types don't need default promotions.  */

  اگر (args1 == NULL_درخت)
    {
      اگر (TYPE_NO_NAMED_ARGS_STDARG_P (f1) != TYPE_NO_NAMED_ARGS_STDARG_P (f2))
	بازگشت نادرست;
      اگر (!(data->ignore_promoting_args || self_promoting_args_p (args2)))
	بازگشت نادرست;
      data->ignore_promoting_args = نادرست;
      /* If one of these types comes from a non-prototype fn definition,
	 compare that with the other type's arglist.
	 If they don't match, ask for a warning (but no error).  */
      اگر (TYPE_ACTUAL_ARG_TYPES (f1)
	  && !type_lists_compatible_p (args2, TYPE_ACTUAL_ARG_TYPES (f1), data))
	 data->warning_needed = درست;
      بازگشت درست;
    }
  اگر (args2 == NULL_درخت)
    {
      اگر (TYPE_NO_NAMED_ARGS_STDARG_P (f1) != TYPE_NO_NAMED_ARGS_STDARG_P (f2))
	بازگشت نادرست;
      اگر (!(data->ignore_promoting_args || self_promoting_args_p (args1)))
	بازگشت نادرست;
      data->ignore_promoting_args = نادرست;
      اگر (TYPE_ACTUAL_ARG_TYPES (f2)
	  && !type_lists_compatible_p (args1, TYPE_ACTUAL_ARG_TYPES (f2), data))
	data->warning_needed = درست;
      بازگشت درست;
    }

  /* Both types have argument lists: compare them and propagate results.  */
  بازگشت type_lists_compatible_p (args1, args2, data);
}

/* Check two lists of types for compatibility, returning false for
   incompatible, true for compatible.  */

ایستا منطقی
type_lists_compatible_p (const_درخت args1, const_درخت args2,
			 ساختار comptypes_data *data)
{
  وقتی (1)
    {
      اگر (args1 == NULL_درخت && args2 == NULL_درخت)
	بازگشت درست;
      /* If one list is shorter than the other,
	 they fail to match.  */
      اگر (args1 == NULL_درخت || args2 == NULL_درخت)
	بازگشت نادرست;
      درخت a1 = درخت_مقدار (args1);
      درخت a2 = درخت_مقدار (args2);
      درخت mv1 = remove_qualifiers (a1);
      درخت mv2 = remove_qualifiers (a2);

      gcc_assert (mv2);
      gcc_assert (mv2);

      /* If one of the lists has an error marker, ignore this arg.  */
      اگر (درخت_CODE (a1) == ERROR_MARK
	       || درخت_CODE (a2) == ERROR_MARK)
	;
      وگرنه اگر (!comptypes_internal (mv1, mv2, data))
	{
	  data->different_types_p = درست;
	  /* Allow  wait (union {union wait *u; int *i} *)
	     and  wait (union wait *)  to be compatible.  */
	  اگر (درخت_CODE (a1) == UNION_TYPE
	      && (TYPE_NAME (a1) == NULL_درخت
		  || TYPE_TRANSPARENT_AGGR (a1))
	      && درخت_CODE (TYPE_SIZE (a1)) == INTEGER_CST
	      && درخت_int_cst_equal (TYPE_SIZE (a1),
				     TYPE_SIZE (a2)))
	    {
	      درخت memb;
	      برای (memb = TYPE_FIELDS (a1);
		   memb; memb = DECL_CHAIN (memb))
		{
		  درخت mv3 = remove_qualifiers (درخت_TYPE (memb));
		  اگر (comptypes_internal (mv3, mv2, data))
		    بشکن;
		}
	      اگر (memb == NULL_درخت)
		بازگشت نادرست;
	    }
	  وگرنه اگر (درخت_CODE (a2) == UNION_TYPE
		   && (TYPE_NAME (a2) == NULL_درخت
		       || TYPE_TRANSPARENT_AGGR (a2))
		   && درخت_CODE (TYPE_SIZE (a2)) == INTEGER_CST
		   && درخت_int_cst_equal (TYPE_SIZE (a2),
					  TYPE_SIZE (a1)))
	    {
	      درخت memb;
	      برای (memb = TYPE_FIELDS (a2);
		   memb; memb = DECL_CHAIN (memb))
		{
		  درخت mv3 = remove_qualifiers (درخت_TYPE (memb));
		  اگر (comptypes_internal (mv3, mv1, data))
		    بشکن;
		}
	      اگر (memb == NULL_درخت)
		بازگشت نادرست;
	    }
	  وگرنه
	    بازگشت نادرست;
	}

      args1 = درخت_CHAIN (args1);
      args2 = درخت_CHAIN (args2);
    }
}

/* Compute the size to increment a pointer by.  When a function type or void
   type or incomplete type is passed, size_one_node is returned.
   This function does not emit any diagnostics; the caller is responsible
   for that.  */

ایستا درخت
c_size_in_bytes (const_درخت type)
{
  شمارش درخت_code code = درخت_CODE (type);

  اگر (code == FUNCTION_TYPE || code == VOID_TYPE || code == ERROR_MARK
      || !COMPLETE_TYPE_P (type))
    بازگشت size_one_گره;

  /* Convert in case a char is more than one unit.  */
  بازگشت size_binop_loc (درون_داد_location, CEIL_DIV_عبارت, TYPE_SIZE_UNIT (type),
			 size_int (TYPE_PRECISION (char_type_گره)
				   / BITS_PER_UNIT));
}

/* Return either DECL or its known constant value (if it has one).  */

درخت
decl_constant_مقدار_1 (درخت decl, منطقی in_init)
{
  اگر (/* Note that DECL_INITIAL isn't valid for a PARM_DECL.  */
      درخت_CODE (decl) != PARM_DECL
      && !درخت_THIS_VOLATILE (decl)
      && درخت_READONLY (decl)
      && DECL_INITIAL (decl) != NULL_درخت
      && !error_operand_p (DECL_INITIAL (decl))
      /* This is invalid if initial value is not constant.
	 If it has either a function call, a memory reference,
	 or a variable, then re-evaluating it could give different results.  */
      && درخت_CONSTANT (DECL_INITIAL (decl))
      /* Check for cases where this is sub-optimal, even though valid.  */
      && (in_init || درخت_CODE (DECL_INITIAL (decl)) != CONSTRUCTOR))
    بازگشت DECL_INITIAL (decl);
  بازگشت decl;
}

/* Return either DECL or its known constant value (if it has one).
   Like the above, but always return decl outside of functions.  */

درخت
decl_constant_مقدار (درخت decl)
{
  /* Don't change a variable array bound or initial value to a constant
     in a place where a variable is invalid.  */
  بازگشت current_function_decl ? decl_constant_مقدار_1 (decl, نادرست) : decl;
}

/* Convert the array expression EXP to a pointer.  */
ایستا درخت
array_to_pointer_conversion (location_t loc, درخت exp)
{
  درخت orig_exp = exp;
  درخت type = درخت_TYPE (exp);
  درخت adr;
  درخت restype = درخت_TYPE (type);
  درخت ptrtype;

  gcc_assert (درخت_CODE (type) == ARRAY_TYPE);

  STRIP_TYPE_NOPS (exp);

  copy_warning (exp, orig_exp);

  ptrtype = c_build_pointer_type (restype);

  اگر (INDIRECT_REF_P (exp))
    بازگشت convert (ptrtype, درخت_OPERAND (exp, 0));

  /* In C++ array compound literals are temporary objects unless they are
     const or appear in namespace scope, so they are destroyed too soon
     to use them for much of anything  (c++/53220).  */
  اگر (warn_cxx_compat && درخت_CODE (exp) == COMPOUND_LITERAL_عبارت)
    {
      درخت decl = درخت_OPERAND (درخت_OPERAND (exp, 0), 0);
      اگر (!درخت_READONLY (decl) && !درخت_STATIC (decl))
	warning_at (DECL_SOURCE_LOCATION (decl), OPT_Wc___compat,
		    "converting an array compound literal to a pointer "
		    "leads to a dangling pointer in C++");
    }

  adr = build_unary_op (loc, ADDR_عبارت, exp, درست);
  بازگشت convert (ptrtype, adr);
}

/* Convert the function expression EXP to a pointer.  */
ایستا درخت
function_to_pointer_conversion (location_t loc, درخت exp)
{
  درخت orig_exp = exp;

  gcc_assert (درخت_CODE (درخت_TYPE (exp)) == FUNCTION_TYPE);

  STRIP_TYPE_NOPS (exp);

  copy_warning (exp, orig_exp);

  درخت exp2 = build_unary_op (loc, ADDR_عبارت, exp, نادرست);

  /* If the function is defined and known to not require a non-local
     context, make sure no trampoline is generated.  */
  اگر (درخت_CODE (exp) == FUNCTION_DECL
      && DECL_INITIAL (exp) && !C_FUNC_NONLOCAL_CONTEXT (exp))
   درخت_NO_TRAMPOLINE (exp2) = 1;

  بازگشت exp2;
}

/* Mark EXP as read, not just set, for set but not used -Wunused
   warning purposes.  */

تهی
mark_exp_read (درخت exp)
{
  انتخاب (درخت_CODE (exp))
    {
    حالت VAR_DECL:
    حالت PARM_DECL:
      DECL_READ_P (exp) = 1;
      بشکن;
    CASE_CONVERT:
      اگر (VOID_TYPE_P (درخت_TYPE (exp)))
	انتخاب (درخت_CODE (درخت_OPERAND (exp, 0)))
	  {
	  حالت PREINCREMENT_عبارت:
	  حالت PREDECREMENT_عبارت:
	  حالت POSTINCREMENT_عبارت:
	  حالت POSTDECREMENT_عبارت:
	    بازگشت;
	  پیشفرض:
	    بشکن;
	  }
      /* FALLTHRU */
    حالت ARRAY_REF:
    حالت COMPONENT_REF:
    حالت MODIFY_عبارت:
    حالت REALPART_عبارت:
    حالت IMAGPART_عبارت:
    حالت ADDR_عبارت:
    حالت VIEW_CONVERT_عبارت:
    حالت PREINCREMENT_عبارت:
    حالت PREDECREMENT_عبارت:
    حالت POSTINCREMENT_عبارت:
    حالت POSTDECREMENT_عبارت:
      mark_exp_read (درخت_OPERAND (exp, 0));
      بشکن;
    حالت COMPOUND_عبارت:
      /* Pattern match what build_atomic_assign produces with modifycode
	 NOP_EXPR.  */
      اگر (VAR_P (درخت_OPERAND (exp, 1))
	  && DECL_ARTIFICIAL (درخت_OPERAND (exp, 1))
	  && درخت_CODE (درخت_OPERAND (exp, 0)) == COMPOUND_عبارت)
	{
	  درخت t1 = درخت_OPERAND (درخت_OPERAND (exp, 0), 0);
	  درخت t2 = درخت_OPERAND (درخت_OPERAND (exp, 0), 1);
	  اگر (درخت_CODE (t1) == TARGET_عبارت
	      && TARGET_عبارت_SLOT (t1) == درخت_OPERAND (exp, 1)
	      && درخت_CODE (t2) == CALL_عبارت)
	    {
	      درخت fndecl = get_callee_fndecl (t2);
	      درخت arg = NULL_درخت;
	      اگر (fndecl
		  && درخت_CODE (fndecl) == FUNCTION_DECL
		  && fndecl_built_in_p (fndecl, BUILT_IN_NORMAL)
		  && call_عبارت_nargs (t2) >= 2)
		انتخاب (DECL_FUNCTION_CODE (fndecl))
		  {
		  حالت BUILT_IN_ATOMIC_STORE:
		    arg = CALL_عبارت_ARG (t2, 1);
		    بشکن;
		  حالت BUILT_IN_ATOMIC_STORE_1:
		  حالت BUILT_IN_ATOMIC_STORE_2:
		  حالت BUILT_IN_ATOMIC_STORE_4:
		  حالت BUILT_IN_ATOMIC_STORE_8:
		  حالت BUILT_IN_ATOMIC_STORE_16:
		    arg = CALL_عبارت_ARG (t2, 0);
		    بشکن;
		  پیشفرض:
		    بشکن;
		  }
	      اگر (arg)
		{
		  STRIP_NOPS (arg);
		  اگر (درخت_CODE (arg) == ADDR_عبارت
		      && DECL_P (درخت_OPERAND (arg, 0))
		      && TYPE_ATOMIC (درخت_TYPE (درخت_OPERAND (arg, 0))))
		    mark_exp_read (درخت_OPERAND (arg, 0));
		}
	    }
	}
      /* FALLTHRU */
    حالت C_MAYBE_CONST_عبارت:
      mark_exp_read (درخت_OPERAND (exp, 1));
      بشکن;
    حالت OMP_ARRAY_SECTION:
      mark_exp_read (درخت_OPERAND (exp, 0));
      اگر (درخت_OPERAND (exp, 1))
	mark_exp_read (درخت_OPERAND (exp, 1));
      اگر (درخت_OPERAND (exp, 2))
	mark_exp_read (درخت_OPERAND (exp, 2));
      بشکن;
    پیشفرض:
      بشکن;
    }
}

/* Perform the default conversion of arrays and functions to pointers.
   Return the result of converting EXP.  For any other expression, just
   return EXP.

   LOC is the location of the expression.  */

ساختار c_عبارت
default_function_array_conversion (location_t loc, ساختار c_عبارت exp)
{
  درخت orig_exp = exp.مقدار;
  درخت type = درخت_TYPE (exp.مقدار);
  شمارش درخت_code code = درخت_CODE (type);

  انتخاب (code)
    {
    حالت ARRAY_TYPE:
      {
	منطقی not_lvalue = نادرست;
	منطقی lvalue_array_p;

	وقتی ((درخت_CODE (exp.مقدار) == NON_LVALUE_عبارت
		|| CONVERT_عبارت_P (exp.مقدار))
	       && درخت_TYPE (درخت_OPERAND (exp.مقدار, 0)) == type)
	  {
	    اگر (درخت_CODE (exp.مقدار) == NON_LVALUE_عبارت)
	      not_lvalue = درست;
	    exp.مقدار = درخت_OPERAND (exp.مقدار, 0);
	  }

	copy_warning (exp.مقدار, orig_exp);

	lvalue_array_p = !not_lvalue && lvalue_p (exp.مقدار);
	اگر (!flag_isoc99 && !lvalue_array_p)
	  {
	    /* Before C99, non-lvalue arrays do not decay to pointers.
	       Normally, using such an array would be invalid; but it can
	       be used correctly inside sizeof or as a statement expression.
	       Thus, do not give an error here; an error will result later.  */
	    بازگشت exp;
	  }

	exp.مقدار = array_to_pointer_conversion (loc, exp.مقدار);
      }
      بشکن;
    حالت FUNCTION_TYPE:
      exp.مقدار = function_to_pointer_conversion (loc, exp.مقدار);
      بشکن;
    پیشفرض:
      بشکن;
    }

  بازگشت exp;
}

ساختار c_عبارت
default_function_array_read_conversion (location_t loc, ساختار c_عبارت exp)
{
  mark_exp_read (exp.مقدار);
  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  اگر (درخت_CODE (exp.مقدار) == COMPONENT_REF
      && handle_counted_by_p (exp.مقدار))
    exp.مقدار = handle_counted_by_for_component_ref (loc, exp.مقدار);
  بازگشت default_function_array_conversion (loc, exp);
}

/* Return whether EXPR should be treated as an atomic lvalue for the
   purposes of load and store handling.  */

ایستا منطقی
really_atomic_lvalue (درخت عبارت)
{
  اگر (error_operand_p (عبارت))
    بازگشت نادرست;
  اگر (!TYPE_ATOMIC (درخت_TYPE (عبارت)))
    بازگشت نادرست;
  اگر (!COMPLETE_TYPE_P (درخت_TYPE (عبارت)))
    بازگشت نادرست;
  اگر (!lvalue_p (عبارت))
    بازگشت نادرست;

  /* Ignore _Atomic on register variables, since their addresses can't
     be taken so (a) atomicity is irrelevant and (b) the normal atomic
     sequences wouldn't work.  Ignore _Atomic on structures containing
     bit-fields, since accessing elements of atomic structures or
     unions is undefined behavior (C11 6.5.2.3#5), but it's unclear if
     it's undefined at translation time or execution time, and the
     normal atomic sequences again wouldn't work.  */
  وقتی (handled_component_p (عبارت))
    {
      اگر (درخت_CODE (عبارت) == COMPONENT_REF
	  && DECL_C_BIT_FIELD (درخت_OPERAND (عبارت, 1)))
	بازگشت نادرست;
      عبارت = درخت_OPERAND (عبارت, 0);
    }
  اگر (درخت_CODE (عبارت) == COMPOUND_LITERAL_عبارت)
    عبارت = COMPOUND_LITERAL_عبارت_DECL (عبارت);
  اگر (DECL_P (عبارت) && C_DECL_REGISTER (عبارت))
    بازگشت نادرست;
  بازگشت درست;
}

/* If EXPR is a named constant (C23) derived from a constexpr variable
   - that is, a reference to such a variable, or a member extracted by
   a sequence of structure and union (but not array) member accesses
   (where union member accesses must access the same member as
   initialized) - then return the corresponding initializer;
   otherwise, return NULL_TREE.  */

ایستا درخت
maybe_get_constexpr_init (درخت عبارت)
{
  درخت decl = NULL_درخت;
  اگر (درخت_CODE (عبارت) == VAR_DECL)
    decl = عبارت;
  وگرنه اگر (درخت_CODE (عبارت) == COMPOUND_LITERAL_عبارت)
    decl = COMPOUND_LITERAL_عبارت_DECL (عبارت);
  اگر (decl
      && C_DECL_DECLARED_CONSTEXPR (decl)
      && DECL_INITIAL (decl) != NULL_درخت
      && !error_operand_p (DECL_INITIAL (decl)))
    بازگشت DECL_INITIAL (decl);
  اگر (درخت_CODE (عبارت) != COMPONENT_REF)
    بازگشت NULL_درخت;
  درخت inner = maybe_get_constexpr_init (درخت_OPERAND (عبارت, 0));
  اگر (inner == NULL_درخت)
    بازگشت NULL_درخت;
  وقتی ((CONVERT_عبارت_P (inner) || درخت_CODE (inner) == NON_LVALUE_عبارت)
	 && !error_operand_p (inner)
	 && (TYPE_MAIN_VARIANT (درخت_TYPE (inner))
	     == TYPE_MAIN_VARIANT (درخت_TYPE (درخت_OPERAND (inner, 0)))))
    inner = درخت_OPERAND (inner, 0);
  اگر (درخت_CODE (inner) != CONSTRUCTOR)
    بازگشت NULL_درخت;
  درخت field = درخت_OPERAND (عبارت, 1);
  unsigned HOST_WIDE_INT cidx;
  درخت cfield, cvalue;
  منطقی have_other_init = نادرست;
  FOR_EACH_CONSTRUCTOR_ELT (CONSTRUCTOR_ELTS (inner), cidx, cfield, cvalue)
    {
      اگر (cfield == field)
	بازگشت cvalue;
      have_other_init = درست;
    }
  اگر (درخت_CODE (درخت_TYPE (inner)) == UNION_TYPE
      && (have_other_init || field != TYPE_FIELDS (درخت_TYPE (inner))))
    بازگشت NULL_درخت;
  /* Return a default initializer.  */
  اگر (RECORD_OR_UNION_TYPE_P (درخت_TYPE (عبارت)))
    بازگشت build_constructor (درخت_TYPE (عبارت), پوچ);
  بازگشت build_zero_cst (درخت_TYPE (عبارت));
}

/* Helper function for convert_lvalue_to_rvalue called via
   walk_tree_without_duplicates.  Find DATA inside of the expression.  */

ایستا درخت
c_find_var_r (درخت *tp, صحیح *walk_subtrees, تهی *data)
{
  اگر (TYPE_P (*tp))
    *walk_subtrees = 0;
  وگرنه اگر (*tp == (درخت) data)
    بازگشت *tp;
  بازگشت NULL_درخت;
}

/* Convert expression EXP (location LOC) from lvalue to rvalue,
   including converting functions and arrays to pointers if CONVERT_P.
   If READ_P, also mark the expression as having been read.  If
   FOR_INIT, constexpr expressions of structure and union type should
   be replaced by the corresponding CONSTRUCTOR; otherwise, only
   constexpr scalars (including elements of structures and unions) are
   replaced by their initializers.  */

ساختار c_عبارت
convert_lvalue_to_rvalue (location_t loc, ساختار c_عبارت exp,
			  منطقی convert_p, منطقی read_p, منطقی for_init)
{
  منطقی force_non_npc = نادرست;
  اگر (read_p)
    mark_exp_read (exp.مقدار);
  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  اگر (read_p && درخت_CODE (exp.مقدار) == COMPONENT_REF
      && handle_counted_by_p (exp.مقدار))
    exp.مقدار = handle_counted_by_for_component_ref (loc, exp.مقدار);

  اگر (convert_p)
    exp = default_function_array_conversion (loc, exp);
  اگر (!VOID_TYPE_P (درخت_TYPE (exp.مقدار))
      || (flag_isoc2y
	  && TYPE_QUALS (درخت_TYPE (exp.مقدار)) != TYPE_UNQUALIFIED))
    exp.مقدار = require_complete_type (loc, exp.مقدار);
  اگر (for_init || !RECORD_OR_UNION_TYPE_P (درخت_TYPE (exp.مقدار)))
    {
      درخت init = maybe_get_constexpr_init (exp.مقدار);
      اگر (init != NULL_درخت)
	{
	  /* A named constant of pointer type or type nullptr_t is not
	     a null pointer constant even if the initializer is
	     one.  */
	  اگر (درخت_CODE (init) == INTEGER_CST
	      && !INTEGRAL_TYPE_P (درخت_TYPE (init))
	      && integer_zerop (init))
	    force_non_npc = درست;
	  exp.مقدار = init;
	}
    }
  اگر (really_atomic_lvalue (exp.مقدار))
    {
      vec<درخت, va_gc> *params;
      درخت nonatomic_type, tmp, tmp_addr, fndecl, func_call;
      درخت عبارت_type = درخت_TYPE (exp.مقدار);
      درخت عبارت_addr = build_unary_op (loc, ADDR_عبارت, exp.مقدار, نادرست);
      درخت seq_cst = build_int_cst (integer_type_گره, MEMMODEL_SEQ_CST);

      gcc_assert (TYPE_ATOMIC (عبارت_type));

      /* Expansion of a generic atomic load may require an addition
	 element, so allocate enough to prevent a resize.  */
      vec_alloc (params, 4);

      /* Remove the qualifiers for the rest of the expressions and
	 create the VAL temp variable to hold the RHS.  */
      nonatomic_type = build_qualified_type (عبارت_type, TYPE_UNQUALIFIED);
      tmp = create_tmp_var_raw (nonatomic_type);
      tmp_addr = build_unary_op (loc, ADDR_عبارت, tmp, نادرست);
      درخت_ADDRESSABLE (tmp) = 1;
      /* Do not disable warnings for TMP even though it's artificial.
	 -Winvalid-memory-model depends on it.  */

      /* Issue __atomic_load (&expr, &tmp, SEQ_CST);  */
      fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_LOAD);
      params->quick_افزودن (عبارت_addr);
      params->quick_افزودن (tmp_addr);
      params->quick_افزودن (seq_cst);
      func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, پوچ);

      /* EXPR is always read.  */
      mark_exp_read (exp.مقدار);

      /* Optimize the common case where c_build_function_call_vec
	 immediately folds __atomic_load (&expr, &tmp, SEQ_CST); into
	 tmp = __atomic_load_<N> (&expr, SEQ_CST);
	 In that case tmp is not addressable and can be initialized
	 fully by the rhs of the MODIFY_EXPR.  */
      درخت tem = func_call;
      اگر (CONVERT_عبارت_P (tem) && VOID_TYPE_P (درخت_TYPE (tem)))
	{
	  tem = درخت_OPERAND (tem, 0);
	  اگر (درخت_CODE (tem) == MODIFY_عبارت
	      && درخت_OPERAND (tem, 0) == tmp
	      && !walk_درخت_without_duplicates (&درخت_OPERAND (tem, 1),
						c_find_var_r, tmp))
	    {
	      درخت_ADDRESSABLE (tmp) = 0;
	      func_call = درخت_OPERAND (tem, 1);
	    }
	}

      /* Return tmp which contains the value loaded.  */
      exp.مقدار = build4 (TARGET_عبارت, nonatomic_type, tmp, func_call,
			  NULL_درخت, NULL_درخت);
    }
  اگر (convert_p && !error_operand_p (exp.مقدار)
      && (درخت_CODE (درخت_TYPE (exp.مقدار)) != ARRAY_TYPE))
    exp.مقدار = convert (build_qualified_type (درخت_TYPE (exp.مقدار), TYPE_UNQUALIFIED), exp.مقدار);
  اگر (force_non_npc)
    exp.مقدار = build1 (NOP_عبارت, درخت_TYPE (exp.مقدار), exp.مقدار);

  {
    درخت false_مقدار, true_مقدار;
    اگر (convert_p && !error_operand_p (exp.مقدار)
	&& c_hardbool_type_attr (درخت_TYPE (exp.مقدار),
				 &false_مقدار, &true_مقدار))
      {
	درخت t = save_عبارت (exp.مقدار);

	mark_exp_read (exp.مقدار);

	درخت trapfn = builtin_decl_explicit (BUILT_IN_TRAP);
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

	exp.مقدار = عبارت;
      }
  }

  بازگشت exp;
}

/* Wrapper for the overload above, same arguments but for tree rather than
   c_expr.  This is important for hardbools to decay to bools.  */

ایستا درونخطی درخت
convert_lvalue_to_rvalue (location_t loc, درخت val,
			  منطقی convert_p, منطقی read_p, منطقی for_init = نادرست)
{
  ساختار c_عبارت عبارت;
  memset (&عبارت, 0, اندازه (عبارت));
  عبارت.مقدار = val;
  عبارت = convert_lvalue_to_rvalue (loc, عبارت, convert_p, read_p, for_init);
  بازگشت عبارت.مقدار;
}

/* EXP is an expression of integer type.  Apply the integer promotions
   to it and return the promoted value.  */

درخت
perform_integral_promotions (درخت exp)
{
  درخت type = درخت_TYPE (exp);
  شمارش درخت_code code = درخت_CODE (type);

  gcc_assert (INTEGRAL_TYPE_P (type));

  /* Convert enums to the result of applying the integer promotions to
     their underlying type.  */
  اگر (code == ENUMERAL_TYPE)
    {
      type = ENUM_UNDERLYING_TYPE (type);
      اگر (c_promoting_integer_type_p (type))
	{
	  اگر (TYPE_UNSIGNED (type)
	      && TYPE_PRECISION (type) == TYPE_PRECISION (integer_type_گره))
	    type = unsigned_type_گره;
	  وگرنه
	    type = integer_type_گره;
	}

      بازگشت convert (type, exp);
    }

  /* ??? This should no longer be needed now bit-fields have their
     proper types.  */
  اگر (درخت_CODE (exp) == COMPONENT_REF
      && DECL_C_BIT_FIELD (درخت_OPERAND (exp, 1)))
    {
      اگر (BITINT_TYPE_P (DECL_BIT_FIELD_TYPE (درخت_OPERAND (exp, 1))))
	{
	  درخت btype = DECL_BIT_FIELD_TYPE (درخت_OPERAND (exp, 1));
	  اگر (درخت_CODE (btype) == BITINT_TYPE)
	    بازگشت convert (btype, exp);
	  وگرنه
	    بازگشت convert (ENUM_UNDERLYING_TYPE (btype), exp);
	}
      /* If it's thinner than an int, promote it like a
	 c_promoting_integer_type_p, otherwise leave it alone.  */
      اگر (compare_درخت_int (DECL_SIZE (درخت_OPERAND (exp, 1)),
			    TYPE_PRECISION (integer_type_گره)) < 0)
	بازگشت convert (integer_type_گره, exp);
    }

  اگر (c_promoting_integer_type_p (type))
    {
      /* Preserve unsignedness if not really getting any wider.  */
      اگر (TYPE_UNSIGNED (type)
	  && TYPE_PRECISION (type) == TYPE_PRECISION (integer_type_گره))
	بازگشت convert (unsigned_type_گره, exp);

      بازگشت convert (integer_type_گره, exp);
    }

  بازگشت exp;
}


/* Perform default promotions for C data used in expressions.
   Enumeral types or short or char are converted to int.
   In addition, manifest constants symbols are replaced by their values.  */

درخت
default_conversion (درخت exp)
{
  درخت orig_exp;
  درخت type = درخت_TYPE (exp);
  شمارش درخت_code code = درخت_CODE (type);
  درخت promoted_type;

  mark_exp_read (exp);
  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  اگر (درخت_CODE (exp) == COMPONENT_REF
      && handle_counted_by_p (exp))
    exp = handle_counted_by_for_component_ref (عبارت_LOCATION (exp), exp);

  /* Functions and arrays have been converted during parsing.  */
  gcc_assert (code != FUNCTION_TYPE);
  اگر (code == ARRAY_TYPE)
    بازگشت exp;

  /* Constants can be used directly unless they're not loadable.  */
  اگر (درخت_CODE (exp) == CONST_DECL)
    exp = DECL_INITIAL (exp);

  /* Strip no-op conversions.  */
  orig_exp = exp;
  STRIP_TYPE_NOPS (exp);

  copy_warning (exp, orig_exp);

  اگر (code == VOID_TYPE)
    {
      error_at (عبارت_LOC_OR_LOC (exp, درون_داد_location),
		"void value not ignored as it ought to be");
      بازگشت error_mark_گره;
    }

  exp = require_complete_type (عبارت_LOC_OR_LOC (exp, درون_داد_location), exp);
  اگر (exp == error_mark_گره)
    بازگشت error_mark_گره;

  promoted_type = targetm.promoted_type (type);
  اگر (promoted_type)
    بازگشت convert (promoted_type, exp);

  اگر (INTEGRAL_TYPE_P (type))
    {
      /* Avoid performing integral promotion of bit-precise integer
	 type bit-field to its corresponding bit-precise integer if
	 orig_exp is a cast to it to its underlying type.  */
      اگر (orig_exp != exp
	  && درخت_CODE (exp) == COMPONENT_REF
	  && DECL_C_BIT_FIELD (درخت_OPERAND (exp, 1))
	  && BITINT_TYPE_P (DECL_BIT_FIELD_TYPE (درخت_OPERAND (exp, 1))))
	بازگشت perform_integral_promotions (orig_exp);
      بازگشت perform_integral_promotions (exp);
    }

  بازگشت exp;
}

/* Look up COMPONENT in a structure or union TYPE.

   If the component name is not found, returns NULL_TREE.  Otherwise,
   the return value is a TREE_LIST, with each TREE_VALUE a FIELD_DECL
   stepping down the chain to the component, which is in the last
   TREE_VALUE of the list.  Normally the list is of length one, but if
   the component is embedded within (nested) anonymous structures or
   unions, the list steps down the chain to the component.  */

درخت
lookup_field (const_درخت type, درخت component)
{
  درخت field;

  /* If TYPE_LANG_SPECIFIC is set, then it is a sorted array of pointers
     to the field elements.  Use a binary search on this array to quickly
     find the element.  Otherwise, do a linear search.  TYPE_LANG_SPECIFIC
     will always be set for structures which have many elements.

     Duplicate field checking replaces duplicates with NULL_TREE so
     TYPE_LANG_SPECIFIC arrays are potentially no longer sorted.  In that
     case just iterate using DECL_CHAIN.  */

  اگر (TYPE_LANG_SPECIFIC (type) && TYPE_LANG_SPECIFIC (type)->s
      && !seen_error ())
    {
      صحیح bot, بالاترین, half;
      درخت *field_array = &TYPE_LANG_SPECIFIC (type)->s->elts[0];

      field = TYPE_FIELDS (type);
      bot = 0;
      بالاترین = TYPE_LANG_SPECIFIC (type)->s->len;
      وقتی (بالاترین - bot > 1)
	{
	  half = (بالاترین - bot + 1) >> 1;
	  field = field_array[bot+half];

	  اگر (DECL_NAME (field) == NULL_درخت)
	    {
	      /* Step through all anon unions in linear fashion.  */
	      وقتی (DECL_NAME (field_array[bot]) == NULL_درخت)
		{
		  field = field_array[bot++];
		  اگر (RECORD_OR_UNION_TYPE_P (درخت_TYPE (field)))
		    {
		      درخت anon = lookup_field (درخت_TYPE (field), component);

		      اگر (anon)
			بازگشت درخت_cons (NULL_درخت, field, anon);

		      /* The Plan 9 compiler permits referring
			 directly to an anonymous struct/union field
			 using a typedef name.  */
		      اگر (flag_plan9_extensions
			  && TYPE_NAME (درخت_TYPE (field)) != NULL_درخت
			  && (درخت_CODE (TYPE_NAME (درخت_TYPE (field)))
			      == TYPE_DECL)
			  && (DECL_NAME (TYPE_NAME (درخت_TYPE (field)))
			      == component))
			بشکن;
		    }
		}

	      /* Entire record is only anon unions.  */
	      اگر (bot > بالاترین)
		بازگشت NULL_درخت;

	      /* Restart the binary search, with new lower bound.  */
	      ادامه;
	    }

	  اگر (DECL_NAME (field) == component)
	    بشکن;
	  اگر (DECL_NAME (field) < component)
	    bot += half;
	  وگرنه
	    بالاترین = bot + half;
	}

      اگر (DECL_NAME (field_array[bot]) == component)
	field = field_array[bot];
      وگرنه اگر (DECL_NAME (field) != component)
	بازگشت NULL_درخت;
    }
  وگرنه
    {
      برای (field = TYPE_FIELDS (type); field; field = DECL_CHAIN (field))
	{
	  اگر (DECL_NAME (field) == NULL_درخت
	      && RECORD_OR_UNION_TYPE_P (درخت_TYPE (field)))
	    {
	      درخت anon = lookup_field (درخت_TYPE (field), component);

	      اگر (anon)
		بازگشت درخت_cons (NULL_درخت, field, anon);

	      /* The Plan 9 compiler permits referring directly to an
		 anonymous struct/union field using a typedef
		 name.  */
	      اگر (flag_plan9_extensions
		  && TYPE_NAME (درخت_TYPE (field)) != NULL_درخت
		  && درخت_CODE (TYPE_NAME (درخت_TYPE (field))) == TYPE_DECL
		  && (DECL_NAME (TYPE_NAME (درخت_TYPE (field)))
		      == component))
		بشکن;
	    }

	  اگر (DECL_NAME (field) == component)
	    بشکن;
	}

      اگر (field == NULL_درخت)
	بازگشت NULL_درخت;
    }

  بازگشت درخت_cons (NULL_درخت, field, NULL_درخت);
}

/* Recursively append candidate IDENTIFIER_NODEs to CANDIDATES.  */

ایستا تهی
lookup_field_fuzzy_find_candidates (درخت type, درخت component,
				    vec<درخت> *candidates)
{
  درخت field;
  برای (field = TYPE_FIELDS (type); field; field = DECL_CHAIN (field))
    {
      اگر (DECL_NAME (field) == NULL_درخت
	  && RECORD_OR_UNION_TYPE_P (درخت_TYPE (field)))
	lookup_field_fuzzy_find_candidates (درخت_TYPE (field), component,
					    candidates);

      اگر (DECL_NAME (field))
	candidates->safe_افزودن (DECL_NAME (field));
    }
}

/* Like "lookup_field", but find the closest matching IDENTIFIER_NODE,
   rather than returning a TREE_LIST for an exact match.  */

ایستا درخت
lookup_field_fuzzy (درخت type, درخت component)
{
  gcc_assert (درخت_CODE (component) == IDENTIFIER_گره);

  /* First, gather a list of candidates.  */
  auto_vec <درخت> candidates;

  lookup_field_fuzzy_find_candidates (type, component,
				      &candidates);

  بازگشت find_closest_identifier (component, &candidates);
}

/* Support function for build_component_ref's error-handling.

   Given DATUM_TYPE, and "DATUM.COMPONENT", where DATUM is *not* a
   struct or union, should we suggest "DATUM->COMPONENT" as a hint?  */

ایستا منطقی
should_suggest_deref_p (درخت datum_type)
{
  /* We don't do it for Objective-C, since Objective-C 2.0 dot-syntax
     allows "." for ptrs; we could be handling a failed attempt
     to access a property.  */
  اگر (c_dialect_objc ())
    بازگشت نادرست;

  /* Only suggest it for pointers...  */
  اگر (درخت_CODE (datum_type) != POINTER_TYPE)
    بازگشت نادرست;

  /* ...to structs/unions.  */
  درخت underlying_type = درخت_TYPE (datum_type);
  شمارش درخت_code code = درخت_CODE (underlying_type);
  اگر (code == RECORD_TYPE || code == UNION_TYPE)
    بازگشت درست;
  وگرنه
    بازگشت نادرست;
}

/* Give a component ref REF, decide whether we should handle its counted_by
   attribute based on its context:
   Do not handle counted_by when in offsetof, typeof and alignof operator.  */

ایستا منطقی
handle_counted_by_p (درخت ref)
{
  gcc_assert (درخت_CODE (ref) == COMPONENT_REF);
  درخت datum = درخت_OPERAND (ref, 0);
  /* If the component_ref is build for a offsetof, i.e., the datum
     of the component_ref is a indirect_ref of null_pointer_node,
     we should not generate call to .ACCESS_WITH_SIZE.  */
  اگر (درخت_CODE (datum) == INDIRECT_REF
      && درخت_OPERAND (datum, 0) == null_pointer_گره)
    بازگشت نادرست;
  اگر (in_typeof || in_alignof)
    بازگشت نادرست;
  بازگشت درست;
}

/* Given a component ref REF, if there is a counted_by attribute attached,
   issue error when the element_type is a structure or union including a
   flexible array member.  */

ایستا تهی
check_counted_by_attribute (location_t loc, درخت ref)
{
  درخت subdatum = درخت_OPERAND (ref, 1);
  درخت sub_type = درخت_TYPE (subdatum);

  اگر (!flexible_array_member_type_p (sub_type)
      && درخت_CODE (sub_type) != POINTER_TYPE)
    بازگشت;

  درخت element_type = درخت_TYPE (sub_type);

  درخت attr_counted_by = lookup_attribute ("counted_by",
					   DECL_ATTRIBUTES (subdatum));
  اگر (attr_counted_by)
    {
      /* Issue error when the element_type is a structure or
	union including a flexible array member.  */
      اگر (RECORD_OR_UNION_TYPE_P (element_type)
	  && TYPE_INCLUDES_FLEXARRAY (element_type))
	{
	  error_at (loc,
		    "%<counted_by%> attribute is not allowed for a pointer to"
		    " structure or union with flexible array member");
	  بازگشت;
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

ایستا درخت
build_counted_by_ref (درخت datum, درخت subdatum,
		      درخت *counted_by_type)
{
  درخت sub_type = درخت_TYPE (subdatum);
  اگر (!flexible_array_member_type_p (sub_type)
      && درخت_CODE (sub_type) != POINTER_TYPE)
    بازگشت NULL_درخت;

  درخت attr_counted_by = lookup_attribute ("counted_by",
					   DECL_ATTRIBUTES (subdatum));
  اگر (!attr_counted_by)
    بازگشت NULL_درخت;

  درخت counted_by_ref = NULL_درخت;
  *counted_by_type = NULL_درخت;

  درخت type = درخت_TYPE (datum);

  /* If the type of the containing structure is an anonymous struct/union,
     and this anonymous struct/union is not a root type, get the first
     outer named structure/union type.  */
  وقتی (درخت_CODE (datum) == COMPONENT_REF
	 && c_type_tag (type) == NULL_درخت
	 && DECL_NAME (درخت_OPERAND (datum, 1)) == NULL_درخت)
    {
      datum = درخت_OPERAND (datum, 0);
      type = درخت_TYPE (datum);
    }

  درخت field_id = درخت_مقدار (درخت_مقدار (attr_counted_by));
  درخت counted_by_field = lookup_field (type, field_id);
  gcc_assert (counted_by_field);

  درخت counted_by_subdatum;
  انجامبده
    {
      counted_by_subdatum = درخت_مقدار (counted_by_field);
      /* Get the TYPE of the counted_by field.  */
      *counted_by_type = درخت_TYPE (counted_by_subdatum);

      counted_by_ref
	= build3 (COMPONENT_REF, درخت_TYPE (counted_by_subdatum),
		  datum, counted_by_subdatum, NULL_درخت);

      datum = counted_by_ref;
      counted_by_field = درخت_CHAIN (counted_by_field);
    }
  وقتی (counted_by_field);

  counted_by_ref = build_fold_addr_عبارت (counted_by_ref);
  بازگشت counted_by_ref;
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
ایستا درخت
build_access_with_size_for_counted_by (location_t loc, درخت ref,
				       درخت counted_by_ref,
				       درخت counted_by_type)
{
  gcc_assert (flexible_array_member_type_p (درخت_TYPE (ref))
	      || درخت_CODE (درخت_TYPE (ref)) == POINTER_TYPE);

  منطقی is_fam = flexible_array_member_type_p (درخت_TYPE (ref));

  /* The result type of the call is a pointer to the flexible array type;
     or is the original pointer type to the pointer field with counted_by.  */
  درخت result_type = is_fam ? c_build_pointer_type (درخت_TYPE (ref))
		     : درخت_TYPE (ref);

  درخت element_type = درخت_TYPE (درخت_TYPE (ref));
  درخت element_size = VOID_TYPE_P (element_type)
		      ? size_one_گره
		      : TYPE_SIZE_UNIT (element_type);
  اگر (element_size == NULL_درخت)
    بازگشت ref;

  درخت first_param = is_fam
		     ? c_fully_fold (array_to_pointer_conversion (loc, ref),
				     نادرست, پوچ)
		     : c_fully_fold (ref, نادرست, پوچ);
  درخت second_param
    = c_fully_fold (counted_by_ref, نادرست, پوچ);
  درخت third_param = build_int_cst (c_build_pointer_type (counted_by_type), 0);

  درخت call
    = build_call_عبارت_internal_loc (loc, IFN_ACCESS_WITH_SIZE,
				    result_type, 4,
				    first_param,
				    second_param,
				    third_param,
				    element_size);

  /* Wrap the call with an INDIRECT_REF with the flexible array type.  */
  اگر (is_fam)
    call = build1 (INDIRECT_REF, درخت_TYPE (ref), call);
  SET_عبارت_LOCATION (call, loc);
  بازگشت call;
}

/* For the COMPONENT_REF ref, check whether it has a counted_by attribute,
   if so, wrap this COMPONENT_REF with the corresponding CALL to the
   function .ACCESS_WITH_SIZE.
   Otherwise, return the ref itself.  */

درخت
handle_counted_by_for_component_ref (location_t loc, درخت ref)
{
  gcc_assert (درخت_CODE (ref) == COMPONENT_REF);
  درخت datum = درخت_OPERAND (ref, 0);
  درخت subdatum = درخت_OPERAND (ref, 1);
  درخت counted_by_type = NULL_درخت;

  اگر (!(flexible_array_member_type_p (درخت_TYPE (ref))
	|| درخت_CODE (درخت_TYPE (ref)) == POINTER_TYPE))
    بازگشت ref;

  درخت counted_by_ref = build_counted_by_ref (datum, subdatum,
					      &counted_by_type);
  اگر (counted_by_ref)
    ref = build_access_with_size_for_counted_by (loc, ref,
						 counted_by_ref,
						 counted_by_type);
  بازگشت ref;
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
  شمارش درخت_code code = درخت_CODE (type);
  درخت field = پوچ;
  درخت ref;
  منطقی datum_lvalue = lvalue_p (datum);

  اگر (!objc_is_public (datum, component))
    بازگشت error_mark_گره;

  /* Detect Objective-C property syntax object.property.  */
  اگر (c_dialect_objc ()
      && (ref = objc_maybe_build_component_ref (datum, component)))
    بازگشت ref;

  /* See if there is a field or component with name COMPONENT.  */

  اگر (code == RECORD_TYPE || code == UNION_TYPE)
    {
      اگر (!COMPLETE_TYPE_P (type))
	{
	  c_incomplete_type_error (loc, NULL_درخت, type);
	  بازگشت error_mark_گره;
	}

      field = lookup_field (type, component);

      اگر (!field)
	{
	  درخت guessed_id = lookup_field_fuzzy (type, component);
	  اگر (guessed_id)
	    {
	      /* Attempt to provide a fixit replacement hint, if
		 we have a valid range for the component.  */
	      location_t reported_loc
		= (component_loc != UNKNOWN_LOCATION) ? component_loc : loc;
	      gcc_rich_location rich_loc (reported_loc);
	      اگر (component_loc != UNKNOWN_LOCATION)
		rich_loc.add_fixit_misspelled_id (component_loc, guessed_id);
	      error_at (&rich_loc,
			"%qT has no member named %qE; did you mean %qE?",
			type, component, guessed_id);
	    }
	  وگرنه
	    error_at (loc, "%qT has no member named %qE", type, component);
	  بازگشت error_mark_گره;
	}

      /* Accessing elements of atomic structures or unions is undefined
	 behavior (C11 6.5.2.3#5).  */
      اگر (TYPE_ATOMIC (type) && c_inhibit_evaluation_warnings == 0)
	{
	  اگر (code == RECORD_TYPE)
	    warning_at (loc, 0, "accessing a member %qE of an atomic "
			"structure %qE", component, datum);
	  وگرنه
	    warning_at (loc, 0, "accessing a member %qE of an atomic "
			"union %qE", component, datum);
	}

      /* Chain the COMPONENT_REFs if necessary down to the FIELD.
	 This might be better solved in future the way the C++ front
	 end does it - by giving the anonymous entities each a
	 separate name and type, and then have build_component_ref
	 recursively call itself.  We can't do that here.  */
      انجامبده
	{
	  درخت subdatum = درخت_مقدار (field);
	  صحیح quals;
	  درخت subtype;
	  منطقی use_datum_quals;

	  اگر (درخت_TYPE (subdatum) == error_mark_گره)
	    بازگشت error_mark_گره;

	  /* If this is an rvalue, it does not have qualifiers in C
	     standard terms and we must avoid propagating such
	     qualifiers down to a non-lvalue array that is then
	     converted to a pointer.  */
	  use_datum_quals = (datum_lvalue
			     || درخت_CODE (درخت_TYPE (subdatum)) != ARRAY_TYPE);

	  quals = TYPE_QUALS (strip_array_types (درخت_TYPE (subdatum)));
	  اگر (use_datum_quals)
	    quals |= TYPE_QUALS (درخت_TYPE (datum));
	  subtype = c_build_qualified_type (درخت_TYPE (subdatum), quals);

	  ref = build3 (COMPONENT_REF, subtype, datum, subdatum,
			NULL_درخت);
	  SET_عبارت_LOCATION (ref, loc);

	  check_counted_by_attribute (loc, ref);

	  اگر (درخت_READONLY (subdatum)
	      || (use_datum_quals && درخت_READONLY (datum)))
	    درخت_READONLY (ref) = 1;
	  اگر (درخت_THIS_VOLATILE (subdatum)
	      || (use_datum_quals && درخت_THIS_VOLATILE (datum)))
	    درخت_THIS_VOLATILE (ref) = 1;

	  اگر (درخت_UNAVAILABLE (subdatum))
	    error_unavailable_use (subdatum, NULL_درخت);
	  وگرنه اگر (درخت_DEPRECATED (subdatum))
	    warn_deprecated_use (subdatum, NULL_درخت);

	  datum = ref;

	  field = درخت_CHAIN (field);
	}
      وقتی (field);

      بازگشت ref;
    }
  وگرنه اگر (should_suggest_deref_p (type))
    {
      /* Special-case the error message for "ptr.field" for the case
	 where the user has confused "." vs "->".  */
      rich_location richloc (سطر_table, loc);
      اگر (INDIRECT_REF_P (datum) && arrow_loc != UNKNOWN_LOCATION)
	{
	  richloc.add_fixit_درج_before (arrow_loc, "(*");
	  richloc.add_fixit_درج_after (arrow_loc, ")");
	  error_at (&richloc,
		    "%qE is a pointer to pointer; did you mean to dereference "
		    "it before applying %<->%> to it?",
		    درخت_OPERAND (datum, 0));
	}
      وگرنه
	{
	  /* "loc" should be the "." token.  */
	  richloc.add_fixit_replace ("->");
	  error_at (&richloc,
		    "%qE is a pointer; did you mean to use %<->%>?",
		    datum);
	}
      بازگشت error_mark_گره;
    }
  وگرنه اگر (code != ERROR_MARK)
    error_at (loc,
	      "request for member %qE in something not a structure or union",
	      component);

  بازگشت error_mark_گره;
}

/* Given an expression PTR for a pointer, return an expression
   for the value pointed to.
   ERRORSTRING is the name of the operator to appear in error messages.

   LOC is the location to use for the generated tree.  */

درخت
build_indirect_ref (location_t loc, درخت ptr, ref_operator errstring)
{
  درخت pointer = default_conversion (ptr);
  درخت type = درخت_TYPE (pointer);
  درخت ref;

  اگر (درخت_CODE (type) == POINTER_TYPE)
    {
      اگر (CONVERT_عبارت_P (pointer)
          || درخت_CODE (pointer) == VIEW_CONVERT_عبارت)
	{
	  /* If a warning is issued, mark it to avoid duplicates from
	     the backend.  This only needs to be done at
	     warn_strict_aliasing > 2.  */
	  اگر (warn_strict_aliasing > 2)
	    اگر (strict_aliasing_warning (عبارت_LOCATION (pointer),
					 type, درخت_OPERAND (pointer, 0)))
	      suppress_warning (pointer, OPT_Wstrict_aliasing_);
	}

      اگر (درخت_CODE (pointer) == ADDR_عبارت
	  && (درخت_TYPE (درخت_OPERAND (pointer, 0))
	      == درخت_TYPE (type)))
	{
	  ref = درخت_OPERAND (pointer, 0);
	  protected_set_عبارت_location (ref, loc);
	  بازگشت ref;
	}
      وگرنه
	{
	  درخت t = درخت_TYPE (type);

	  ref = build1 (INDIRECT_REF, t, pointer);

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
	    = TYPE_VOLATILE (t) || درخت_SIDE_EFFECTS (pointer);
	  درخت_THIS_VOLATILE (ref) = TYPE_VOLATILE (t);
	  protected_set_عبارت_location (ref, loc);
	  بازگشت ref;
	}
    }
  وگرنه اگر (درخت_CODE (pointer) != ERROR_MARK)
    invalid_indirection_error (loc, type, errstring);

  بازگشت error_mark_گره;
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
build_array_ref (location_t loc, درخت array, درخت index)
{
  درخت ret;
  منطقی swapped = نادرست;
  اگر (درخت_TYPE (array) == error_mark_گره
      || درخت_TYPE (index) == error_mark_گره)
    بازگشت error_mark_گره;

  اگر (درخت_CODE (درخت_TYPE (array)) != ARRAY_TYPE
      && درخت_CODE (درخت_TYPE (array)) != POINTER_TYPE
      /* Allow vector[index] but not index[vector].  */
      && !gnu_vector_type_p (درخت_TYPE (array)))
    {
      اگر (درخت_CODE (درخت_TYPE (index)) != ARRAY_TYPE
	  && درخت_CODE (درخت_TYPE (index)) != POINTER_TYPE)
	{
          error_at (loc,
            "subscripted value is neither array nor pointer nor vector");

	  بازگشت error_mark_گره;
	}
      std::swap (array, index);
      swapped = درست;
    }

  اگر (!INTEGRAL_TYPE_P (درخت_TYPE (index)))
    {
      error_at (loc, "array subscript is not an integer");
      بازگشت error_mark_گره;
    }

  اگر (درخت_CODE (درخت_TYPE (درخت_TYPE (array))) == FUNCTION_TYPE)
    {
      error_at (loc, "subscripted value is pointer to function");
      بازگشت error_mark_گره;
    }

  /* ??? Existing practice has been to warn only when the char
     index is syntactically the index, not for char[array].  */
  اگر (!swapped)
     warn_array_subscript_with_type_char (loc, index);

  /* Apply default promotions *after* noticing character types.  */
  index = default_conversion (index);
  اگر (index == error_mark_گره)
    بازگشت error_mark_گره;

  gcc_assert (درخت_CODE (درخت_TYPE (index)) == INTEGER_TYPE
	      || درخت_CODE (درخت_TYPE (index)) == BITINT_TYPE);

  منطقی was_vector = VECTOR_TYPE_P (درخت_TYPE (array));
  منطقی non_lvalue = convert_vector_to_array_for_subscript (loc, &array, index);

  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  اگر (درخت_CODE (array) == COMPONENT_REF
      && handle_counted_by_p (array))
    array = handle_counted_by_for_component_ref (loc, array);

  اگر (درخت_CODE (درخت_TYPE (array)) == ARRAY_TYPE)
    {
      درخت rval, type;

      /* An array that is indexed by a non-constant
	 cannot be stored in a register; we must be able to do
	 address arithmetic on its address.
	 Likewise an array of elements of variable size.  */
      اگر (درخت_CODE (index) != INTEGER_CST
	  || (COMPLETE_TYPE_P (درخت_TYPE (درخت_TYPE (array)))
	      && درخت_CODE (TYPE_SIZE (درخت_TYPE (درخت_TYPE (array)))) != INTEGER_CST))
	{
	  اگر (!c_mark_addressable (array, درست, درست))
	    بازگشت error_mark_گره;
	}
      /* An array that is indexed by a constant value which is not within
	 the array bounds cannot be stored in a register either; because we
	 would get a crash in store_bit_field/extract_bit_field when trying
	 to access a non-existent part of the register.  */
      اگر (درخت_CODE (index) == INTEGER_CST
	  && TYPE_DOMAIN (درخت_TYPE (array))
	  && !int_fits_type_p (index, TYPE_DOMAIN (درخت_TYPE (array))))
	{
	  اگر (!c_mark_addressable (array, نادرست, درست))
	    بازگشت error_mark_گره;
	  /* ISO C2Y disallows a negative integer constant expression index
	     when array subscripting has an operand of array type.  */
	  اگر (flag_isoc2y
	      && !درخت_OVERFLOW (index)
	      && درخت_int_cst_sgn (index) < 0)
	    error_at (loc, "array subscript is negative");
	}

      اگر ((pedantic || warn_c90_c99_compat || warn_c23_c2y_compat)
	  && ! was_vector)
	{
	  درخت foo = array;
	  وقتی (درخت_CODE (foo) == COMPONENT_REF)
	    foo = درخت_OPERAND (foo, 0);
	  اگر ((VAR_P (foo) && C_DECL_REGISTER (foo))
	      || (درخت_CODE (foo) == COMPOUND_LITERAL_عبارت
		  && C_DECL_REGISTER (COMPOUND_LITERAL_عبارت_DECL (foo))))
	    pedwarn_c23 (loc, OPT_Wpedantic,
			 "ISO C forbids subscripting %<register%> array "
			 "before C2Y");
	  وگرنه اگر (!lvalue_p (foo))
	    pedwarn_c90 (loc, OPT_Wpedantic,
			 "ISO C90 forbids subscripting non-lvalue "
			 "array");
	}

      اگر (درخت_CODE (درخت_TYPE (index)) == BITINT_TYPE
	  && TYPE_PRECISION (درخت_TYPE (index)) > TYPE_PRECISION (sizetype))
	index = fold_convert (sizetype, index);

      type = درخت_TYPE (درخت_TYPE (array));
      rval = build4 (ARRAY_REF, type, array, index, NULL_درخت, NULL_درخت);
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
      protected_set_عبارت_location (ret, loc);
      اگر (non_lvalue)
	ret = non_lvalue_loc (loc, ret);
      بازگشت ret;
    }
  وگرنه
    {
      درخت ar = default_conversion (array);

      اگر (ar == error_mark_گره)
	بازگشت ar;

      gcc_assert (درخت_CODE (درخت_TYPE (ar)) == POINTER_TYPE);
      gcc_assert (درخت_CODE (درخت_TYPE (درخت_TYPE (ar))) != FUNCTION_TYPE);

      ret = build_indirect_ref (loc, build_دودویی_op (loc, PLUS_عبارت, ar,
						      index, نادرست),
				RO_ARRAY_INDEXING);
      اگر (non_lvalue)
	ret = non_lvalue_loc (loc, ret);
      بازگشت ret;
    }
}

/* Build an OpenMP array section reference, creating an exact type for the
   resulting expression based on the element type and bounds if possible.  If
   we have variable bounds, create an incomplete array type for the result
   instead.  */

درخت
build_omp_array_section (location_t loc, درخت array, درخت index, درخت length)
{
  درخت type = درخت_TYPE (array);
  gcc_assert (type);

  درخت sectype, eltype = درخت_TYPE (type);

  /* It's not an array or pointer type.  Just reuse the type of the original
     expression as the type of the array section (an error will be raised
     anyway, later).  */
  اگر (eltype == NULL_درخت || error_operand_p (eltype))
    sectype = درخت_TYPE (array);
  وگرنه
    {
      درخت idxtype = NULL_درخت;

      اگر (index != NULL_درخت
	  && length != NULL_درخت
	  && INTEGRAL_TYPE_P (درخت_TYPE (index))
	  && INTEGRAL_TYPE_P (درخت_TYPE (length)))
	{
	  درخت کم = fold_convert (sizetype, index);
	  درخت بالا = fold_convert (sizetype, length);
	  بالا = size_binop (PLUS_عبارت, کم, بالا);
	  بالا = size_binop (MINUS_عبارت, بالا, size_one_گره);
	  idxtype = build_range_type (sizetype, کم, بالا);
	}
      وگرنه اگر ((index == NULL_درخت || integer_zerop (index))
	       && length != NULL_درخت
	       && INTEGRAL_TYPE_P (درخت_TYPE (length)))
	idxtype = build_index_type (length);

      gcc_assert (!error_operand_p (idxtype));

      sectype = c_build_array_type (eltype, idxtype);
    }

  بازگشت build3_loc (loc, OMP_ARRAY_SECTION, sectype, array, index, length);
}


/* Record that REF is used.  This is relevant for undeclared static
   function and declarations referenced from a non-local context.
   ADDRESS indicates whether the address is taken.  */

تهی
mark_decl_used (درخت ref, منطقی address)
{
  اگر (!ref || !DECL_P (ref) || in_alignof)
    بازگشت;

  /* Non-file-scope and non-local reference in nested function.  */
  منطقی nonloc_p = current_function_decl && DECL_CONTEXT (ref)
		  && DECL_CONTEXT (current_function_decl)
		  && DECL_CONTEXT (ref) != current_function_decl;

  /* An undeclared static function.  */
  منطقی static_p = درخت_CODE (ref) == FUNCTION_DECL
		  && DECL_INITIAL (ref) == NULL_درخت
		  && DECL_EXTERNAL (ref)
		  && !درخت_PUBLIC (ref);

  اگر (!static_p && !nonloc_p)
    بازگشت;

  /* If we may be in an unevaluated context, delay the decision.  */
  اگر (in_sizeof || in_typeof || in_countof || in_generic)
    بازگشت record_maybe_used_decl (ref, address);

  اگر (static_p)
    C_DECL_USED (ref) = 1;

  اگر (nonloc_p && (VAR_OR_FUNCTION_DECL_P (ref)
		   || درخت_CODE (ref) == PARM_DECL))
    DECL_NONLOCAL (ref) = 1;

  /* Nothing to do anymore.  */
  اگر (!nonloc_p || C_FUNC_NONLOCAL_CONTEXT (current_function_decl))
    بازگشت;

  /* Filter out the cases where referencing a non-local variable does not
     require a non-local context passed via the static chain.  */
  اگر (!c_type_variably_modified_p (درخت_TYPE (ref)))
    انتخاب (درخت_CODE (ref))
      {
      حالت FUNCTION_DECL:
	/* Use of another local function that requires no context is ok.  */
	اگر (!C_FUNC_NONLOCAL_CONTEXT (ref) && DECL_INITIAL (ref))
	  بازگشت;
	بشکن;
      حالت VAR_DECL:
	/* Static variables and constexpr are ok, but for the later only
	   when the address is not taken.  */
	اگر (درخت_STATIC (ref) || (C_DECL_DECLARED_CONSTEXPR (ref) && !address))
	  بازگشت;
	بشکن;
      حالت TYPE_DECL:
	/* A typedef is ok when not for a variably-modified type. */
	بازگشت;
      حالت CONST_DECL:
	/* An enumeration constant is ok. */
	بازگشت;
      حالت PARM_DECL:
	بشکن;
      حالت LABEL_DECL:
	بشکن;
      پیشفرض:
	gcc_unreachable ();
    }

  /* Mark all parent functions up to the nesting level of the variable as
     as needing the non-local context.  */
  برای (درخت cont = current_function_decl; cont; cont = DECL_CONTEXT (cont))
    {
      اگر (cont == DECL_CONTEXT (ref))
	بشکن;

      /* There should not be any other type of context used for function
	 except TRANSLATION_UNIT_DECL which we should be able to reach.  */
      gcc_checking_assert (درخت_CODE (cont) == FUNCTION_DECL);

      اگر (درخت_CODE (cont) == FUNCTION_DECL)
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

  *type = پوچ;
  اگر (decl && decl != error_mark_گره)
    {
      ref = decl;
      *type = درخت_TYPE (ref);
      اگر (DECL_P (decl) && C_DECL_UNDERSPECIFIED (decl))
	error_at (loc, "underspecified %qD referenced in its initializer",
		  decl);
    }
  وگرنه اگر (fun)
    /* Implicit function declaration.  */
    ref = implicitly_declare (loc, id);
  وگرنه اگر (decl == error_mark_گره)
    /* Don't complain about something that's already been
       complained about.  */
    بازگشت error_mark_گره;
  وگرنه
    {
      undeclared_variable (loc, id);
      بازگشت error_mark_گره;
    }

  /* For an OpenMP map clause, we can get better diagnostics for decls with
     unmappable types if we return the decl with an error_mark_node type,
     rather than returning error_mark_node for the decl itself.  */
  اگر (درخت_TYPE (ref) == error_mark_گره
      && !c_omp_array_section_p)
    بازگشت error_mark_گره;

  اگر (درخت_UNAVAILABLE (ref))
    error_unavailable_use (ref, NULL_درخت);
  وگرنه اگر (درخت_DEPRECATED (ref))
    warn_deprecated_use (ref, NULL_درخت);

  /* Recursive call does not count as usage.  */
  اگر (ref != current_function_decl)
    {
      درخت_USED (ref) = 1;
    }

  mark_decl_used (ref, نادرست);

  اگر (درخت_CODE (ref) == CONST_DECL)
    {
      used_types_درج (درخت_TYPE (ref));

      اگر (warn_cxx_compat
	  && درخت_CODE (درخت_TYPE (ref)) == ENUMERAL_TYPE
	  && C_TYPE_DEFINED_IN_STRUCT (درخت_TYPE (ref)))
	{
	  warning_at (loc, OPT_Wc___compat,
		      "enum constant defined in struct or union "
		      "is not visible in C++");
	  inform (DECL_SOURCE_LOCATION (ref), "enum constant defined here");
	}

      ref = DECL_INITIAL (ref);
      درخت_CONSTANT (ref) = 1;
    }
  /* C99 6.7.4p3: An inline definition of a function with external
     linkage ... shall not contain a reference to an identifier with
     internal linkage.  */
  وگرنه اگر (current_function_decl != NULL_درخت
	   && DECL_DECLARED_INLINE_P (current_function_decl)
	   && DECL_EXTERNAL (current_function_decl)
	   && VAR_OR_FUNCTION_DECL_P (ref)
	   && (!VAR_P (ref) || درخت_STATIC (ref))
	   && ! درخت_PUBLIC (ref)
	   && DECL_CONTEXT (ref) != current_function_decl)
    record_inline_static (loc, current_function_decl, ref,
			  csi_internal);

  بازگشت ref;
}

ایستا ساختار maybe_used_decl *maybe_used_decls;

/* Record that DECL, a reference seen inside sizeof or typeof or _Countof or
   _Generic, might be used if the operand of sizeof is a VLA type or the
   operand of typeof is a variably modified type or the operand of _Countof has
   a variable number of elements or the operand of _Generic is the one selected
   as the result.  */

ایستا تهی
record_maybe_used_decl (درخت decl, منطقی address)
{
  ساختار maybe_used_decl *t = XOBNEW (&parser_obstack, ساختار maybe_used_decl);
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

تهی
برداشت_maybe_used (منطقی used)
{
  ساختار maybe_used_decl *p = maybe_used_decls;
  صحیح cur_level = in_sizeof + in_typeof + in_countof + in_generic;
  وقتی (p && p->level > cur_level)
    {
      اگر (used)
	{
	  اگر (cur_level == 0)
	    mark_decl_used (p->decl, p->address);
	  وگرنه
	    p->level = cur_level;
	}
      p = p->next;
    }
  اگر (!used || cur_level == 0)
    maybe_used_decls = p;
}

/* Pop the stack of decls possibly used inside sizeof or typeof or _Countof or
   _Generic, without acting on them, and return the pointer to the previous top
   of the stack.  This for use at the end of a default generic association when
   it is not yet known whether the expression is used.  If it later turns out
   the expression is used (or treated as used before C23), restore_maybe_used
   should be called on the return value followed by pop_maybe_used (true);
   otherwise, the return value can be discarded.  */

ساختار maybe_used_decl *
save_maybe_used ()
{
  ساختار maybe_used_decl *p = maybe_used_decls, *orig = p;
  صحیح cur_level = in_sizeof + in_typeof + in_countof + in_generic;
  وقتی (p && p->level > cur_level)
    p = p->next;
  maybe_used_decls = p;
  بازگشت orig;
}

/* Restore the stack of decls possibly used inside sizeof or typeof or _Countof
   or _Generic returned by save_maybe_used.  It is required that the stack is
   at exactly the point where it was left by save_maybe_used.  */

تهی
restore_maybe_used (ساختار maybe_used_decl *پشته)
{
  maybe_used_decls = پشته;
}

/* Return the result of sizeof applied to EXPR.  */

ساختار c_عبارت
c_عبارت_sizeof_عبارت (location_t loc, ساختار c_عبارت عبارت)
{
  ساختار c_عبارت ret;
  اگر (عبارت.مقدار == error_mark_گره)
    {
      ret.مقدار = error_mark_گره;
      ret.original_code = ERROR_MARK;
      ret.original_type = پوچ;
      ret.m_decimal = 0;
      برداشت_maybe_used (نادرست);
    }
  وگرنه
    {
      منطقی عبارت_const_operands = درست;

      اگر (درخت_CODE (عبارت.مقدار) == PARM_DECL
	  && C_ARRAY_PARAMETER (عبارت.مقدار))
	{
	  auto_diagnostic_group d;
	  اگر (warning_at (loc, OPT_Wsizeof_array_argument,
			  "%<sizeof%> on array function parameter %qE will "
			  "return size of %qT", عبارت.مقدار,
			  درخت_TYPE (عبارت.مقدار)))
	    inform (DECL_SOURCE_LOCATION (عبارت.مقدار), "declared here");
	}
      درخت folded_عبارت = c_fully_fold (عبارت.مقدار, require_constant_مقدار,
				       &عبارت_const_operands);
      ret.مقدار = c_sizeof (loc, درخت_TYPE (folded_عبارت));
      c_last_sizeof_arg = عبارت.مقدار;
      c_last_sizeof_loc = loc;
      ret.original_code = SIZEOF_عبارت;
      ret.original_type = پوچ;
      ret.m_decimal = 0;
      اگر (C_TYPE_VARIABLE_SIZE (درخت_TYPE (folded_عبارت)))
	{
	  /* sizeof is evaluated when given a vla (C99 6.5.3.4p2).  */
	  ret.مقدار = build2 (C_MAYBE_CONST_عبارت, درخت_TYPE (ret.مقدار),
			      folded_عبارت, ret.مقدار);
	  C_MAYBE_CONST_عبارت_NON_CONST (ret.مقدار) = !عبارت_const_operands;
	  SET_عبارت_LOCATION (ret.مقدار, loc);
	}
      برداشت_maybe_used (C_TYPE_VARIABLE_SIZE (درخت_TYPE (folded_عبارت)));
    }
  بازگشت ret;
}

/* Return the result of sizeof applied to T, a structure for the type
   name passed to sizeof (rather than the type itself).  LOC is the
   location of the original expression.  */

ساختار c_عبارت
c_عبارت_sizeof_type (location_t loc, ساختار c_type_name *t)
{
  درخت type;
  ساختار c_عبارت ret;
  درخت type_عبارت = NULL_درخت;
  منطقی type_عبارت_const = درست;
  type = groktypename (t, &type_عبارت, &type_عبارت_const);
  ret.مقدار = c_sizeof (loc, type);
  c_last_sizeof_arg = type;
  c_last_sizeof_loc = loc;
  ret.original_code = SIZEOF_عبارت;
  ret.original_type = پوچ;
  ret.m_decimal = 0;
  اگر (type == error_mark_گره)
    {
      ret.مقدار = error_mark_گره;
      ret.original_code = ERROR_MARK;
    }
  وگرنه
  اگر ((type_عبارت || درخت_CODE (ret.مقدار) == INTEGER_CST)
      && C_TYPE_VARIABLE_SIZE (type))
    {
      /* If the type is a [*] array, it is a VLA but is represented as
	 having a size of zero.  In such a case we must ensure that
	 the result of sizeof does not get folded to a constant by
	 c_fully_fold, because if the size is evaluated the result is
	 not constant and so constraints on zero or negative size
	 arrays must not be applied when this sizeof call is inside
	 another array declarator.  */
      اگر (!type_عبارت)
	type_عبارت = integer_zero_گره;
      ret.مقدار = build2 (C_MAYBE_CONST_عبارت, درخت_TYPE (ret.مقدار),
			  type_عبارت, ret.مقدار);
      C_MAYBE_CONST_عبارت_NON_CONST (ret.مقدار) = !type_عبارت_const;
    }
  برداشت_maybe_used (type != error_mark_گره
		  ? C_TYPE_VARIABLE_SIZE (type) : نادرست);
  بازگشت ret;
}

ایستا منطقی
بالاترین_array_vla_p (const_درخت type)
{
  اگر (درخت_CODE (type) != ARRAY_TYPE)
    بازگشت نادرست;

  درخت d = TYPE_DOMAIN (type);

  اگر (!d)
    بازگشت نادرست;
  اگر (!TYPE_MAX_مقدار (d))
    بازگشت نادرست;

  بازگشت درخت_CODE (TYPE_MAX_مقدار (d)) != INTEGER_CST
	 || درخت_CODE (TYPE_MIN_مقدار (d)) != INTEGER_CST;
}

/* Return the result of countof applied to EXPR.  */

ساختار c_عبارت
c_عبارت_countof_عبارت (location_t loc, ساختار c_عبارت عبارت)
{
  ساختار c_عبارت ret;
  اگر (عبارت.مقدار == error_mark_گره)
    {
      ret.مقدار = error_mark_گره;
      ret.original_code = ERROR_MARK;
      ret.original_type = پوچ;
      ret.m_decimal = 0;
      برداشت_maybe_used (نادرست);
    }
  وگرنه
    {
      منطقی عبارت_const_operands = درست;

      درخت folded_عبارت = c_fully_fold (عبارت.مقدار, require_constant_مقدار,
				       &عبارت_const_operands);
      ret.مقدار = c_countof_type (loc, درخت_TYPE (folded_عبارت));
      c_last_sizeof_arg = عبارت.مقدار;
      c_last_sizeof_loc = loc;
      ret.original_code = COUNTOF_عبارت;
      ret.original_type = پوچ;
      ret.m_decimal = 0;
      اگر (بالاترین_array_vla_p (درخت_TYPE (folded_عبارت)))
	{
	  /* countof is evaluated when given a vla.  */
	  ret.مقدار = build2 (C_MAYBE_CONST_عبارت, درخت_TYPE (ret.مقدار),
			      folded_عبارت, ret.مقدار);
	  C_MAYBE_CONST_عبارت_NON_CONST (ret.مقدار) = !عبارت_const_operands;
	  SET_عبارت_LOCATION (ret.مقدار, loc);
	}
      برداشت_maybe_used (بالاترین_array_vla_p (درخت_TYPE (folded_عبارت)));
    }
  بازگشت ret;
}

/* Return the result of countof applied to T, a structure for the type
   name passed to countof (rather than the type itself).  LOC is the
   location of the original expression.  */

ساختار c_عبارت
c_عبارت_countof_type (location_t loc, ساختار c_type_name *t)
{
  درخت type;
  ساختار c_عبارت ret;
  درخت type_عبارت = NULL_درخت;
  منطقی type_عبارت_const = درست;
  type = groktypename (t, &type_عبارت, &type_عبارت_const);
  ret.مقدار = c_countof_type (loc, type);
  c_last_sizeof_arg = type;
  c_last_sizeof_loc = loc;
  ret.original_code = COUNTOF_عبارت;
  ret.original_type = پوچ;
  ret.m_decimal = 0;
  اگر (type == error_mark_گره)
    {
      ret.مقدار = error_mark_گره;
      ret.original_code = ERROR_MARK;
    }
  وگرنه
  اگر ((type_عبارت || درخت_CODE (ret.مقدار) == INTEGER_CST)
      && بالاترین_array_vla_p (type))
    {
      /* If the type is a [*] array, it is a VLA but is represented as
	 having a size of zero.  In such a case we must ensure that
	 the result of countof does not get folded to a constant by
	 c_fully_fold, because if the number of elements is evaluated
	 the result is not constant and so
	 constraints on zero or negative size arrays must not be applied
	 when this countof call is inside another array declarator.  */
      اگر (!type_عبارت)
	type_عبارت = integer_zero_گره;
      ret.مقدار = build2 (C_MAYBE_CONST_عبارت, درخت_TYPE (ret.مقدار),
			  type_عبارت, ret.مقدار);
      C_MAYBE_CONST_عبارت_NON_CONST (ret.مقدار) = !type_عبارت_const;
    }
  برداشت_maybe_used (type != error_mark_گره ? بالاترین_array_vla_p (type) : نادرست);
  بازگشت ret;
}

/* Return the result of maxof applied to T, a structure for the type
   name passed to maxof (rather than the type itself).  LOC is the
   location of the original expression.  */

ساختار c_عبارت
c_عبارت_maxof_type (location_t loc, ساختار c_type_name *t)
{
  درخت type;
  ساختار c_عبارت ret;
  درخت type_عبارت = NULL_درخت;
  منطقی type_عبارت_const = درست;
  type = groktypename (t, &type_عبارت, &type_عبارت_const);
  ret.مقدار = c_maxof_type (loc, type);
  c_last_sizeof_arg = type;
  c_last_sizeof_loc = loc;
  ret.original_code = MAXOF_عبارت;
  ret.original_type = پوچ;
  ret.m_decimal = 0;
  اگر (type == error_mark_گره)
    {
      ret.مقدار = error_mark_گره;
      ret.original_code = ERROR_MARK;
    }
  برداشت_maybe_used (type != error_mark_گره);
  بازگشت ret;
}

/* Return the result of minof applied to T, a structure for the type
   name passed to minof (rather than the type itself).  LOC is the
   location of the original expression.  */

ساختار c_عبارت
c_عبارت_minof_type (location_t loc, ساختار c_type_name *t)
{
  درخت type;
  ساختار c_عبارت ret;
  درخت type_عبارت = NULL_درخت;
  منطقی type_عبارت_const = درست;
  type = groktypename (t, &type_عبارت, &type_عبارت_const);
  ret.مقدار = c_minof_type (loc, type);
  c_last_sizeof_arg = type;
  c_last_sizeof_loc = loc;
  ret.original_code = MINOF_عبارت;
  ret.original_type = پوچ;
  ret.m_decimal = 0;
  اگر (type == error_mark_گره)
    {
      ret.مقدار = error_mark_گره;
      ret.original_code = ERROR_MARK;
    }
  برداشت_maybe_used (type != error_mark_گره);
  بازگشت ret;
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

  vec_alloc (v, list_length (params));
  برای (; params; params = درخت_CHAIN (params))
    v->quick_افزودن (درخت_مقدار (params));
  ret = c_build_function_call_vec (loc, vNULL, function, v, پوچ);
  vec_free (v);
  بازگشت ret;
}

/* Give a note about the location of the declaration of DECL,
   or, failing that, a pertinent declaration for FUNCTION_EXPR.  */

ایستا تهی
inform_declaration (درخت decl, درخت function_عبارت)
{
  اگر (decl && (درخت_CODE (decl) != FUNCTION_DECL
	       || !DECL_IS_UNDECLARED_BUILTIN (decl)))
    inform (DECL_SOURCE_LOCATION (decl), "declared here");
  وگرنه اگر (function_عبارت)
    انتخاب (درخت_CODE (function_عبارت))
      {
      پیشفرض:
	بشکن;
      حالت COMPONENT_REF:
	/* Show the decl of the pertinent field (e.g. for callback
	   fields in a struct.  */
	{
	  درخت field_decl = درخت_OPERAND (function_عبارت, 1);
	  اگر (location_t loc = DECL_SOURCE_LOCATION (field_decl))
	    inform (loc, "declared here");
	}
	بشکن;
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
  درخت name = NULL_درخت, result;
  درخت tem;
  صحیح nargs;
  درخت *argarray;


  /* Strip NON_LVALUE_EXPRs, etc., since we aren't using as an lvalue.  */
  STRIP_TYPE_NOPS (function);

  /* Convert anything with function type to a pointer-to-function.  */
  اگر (درخت_CODE (function) == FUNCTION_DECL)
    {
      name = DECL_NAME (function);

      اگر (flag_tm)
	tm_malloc_replacement (function);
      fundecl = function;
      اگر (!orig_fundecl)
	orig_fundecl = fundecl;
      /* Atomic functions have type checking/casting already done.  They are
	 often rewritten and don't match the original parameter list.  */
      اگر (name && startswith (IDENTIFIER_POINTER (name), "__atomic_"))
        origtypes = پوچ;
    }
  اگر (درخت_CODE (درخت_TYPE (function)) == FUNCTION_TYPE)
    function = function_to_pointer_conversion (loc, function);

  /* For Objective-C, convert any calls via a cast to OBJC_TYPE_REF
     expressions, like those used for ObjC messenger dispatches.  */
  اگر (params && !params->is_empty ())
    function = objc_rewrite_function_call (function, (*params)[0]);

  function = c_fully_fold (function, نادرست, پوچ);

  fntype = درخت_TYPE (function);

  اگر (درخت_CODE (fntype) == ERROR_MARK)
    بازگشت error_mark_گره;

  اگر (!(درخت_CODE (fntype) == POINTER_TYPE
	&& درخت_CODE (درخت_TYPE (fntype)) == FUNCTION_TYPE))
    {
      اگر (!flag_diagnostics_show_caret && !STATEMENT_CLASS_P (function))
	error_at (loc,
		  "called object %qE is not a function or function pointer",
		  function);
      وگرنه اگر (DECL_P (function))
	{
	  auto_diagnostic_group d;
	  error_at (loc,
		    "called object %qD is not a function or function pointer",
		    function);
	  inform_declaration (function, NULL_درخت);
	}
      وگرنه
	error_at (loc,
		  "called object is not a function or function pointer");
      بازگشت error_mark_گره;
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
    بازگشت error_mark_گره;

  /* Check that the function is called through a compatible prototype.
     If it is not, warn.  */
  اگر (CONVERT_عبارت_P (function)
      && درخت_CODE (tem = درخت_OPERAND (function, 0)) == ADDR_عبارت
      && درخت_CODE (tem = درخت_OPERAND (tem, 0)) == FUNCTION_DECL
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

  argarray = vec_safe_address (params);

  /* Check that arguments to builtin functions match the expectations.  */
  اگر (fundecl
      && fndecl_built_in_p (fundecl)
      && !check_builtin_function_arguments (loc, arg_loc, fundecl,
					    orig_fundecl, nargs, argarray))
    بازگشت error_mark_گره;

  /* Check that the arguments to the function are valid.  */
  منطقی warned_p = check_function_arguments (loc, fundecl, fntype,
					    nargs, argarray, &arg_loc,
					    comptypes);

  اگر (TYPE_QUALS (return_type) != TYPE_UNQUALIFIED
      && !VOID_TYPE_P (return_type))
    return_type = c_build_qualified_type (return_type, TYPE_UNQUALIFIED);
  اگر (name != NULL_درخت
      && startswith (IDENTIFIER_POINTER (name), "__builtin_"))
    {
      اگر (require_constant_مقدار)
	result
	  = fold_build_call_array_initializer_loc (loc, return_type,
						   function, nargs, argarray);
      وگرنه
	result = fold_build_call_array_loc (loc, return_type,
					    function, nargs, argarray);
      اگر (درخت_CODE (result) == NOP_عبارت
	  && درخت_CODE (درخت_OPERAND (result, 0)) == INTEGER_CST)
	STRIP_TYPE_NOPS (result);
    }
  وگرنه
    result = build_call_array_loc (loc, return_type,
				   function, nargs, argarray);
  /* If -Wnonnull warning has been diagnosed, avoid diagnosing it again
     later.  */
  اگر (warned_p && درخت_CODE (result) == CALL_عبارت)
    suppress_warning (result, OPT_Wnonnull);

  /* In this improbable scenario, a nested function returns a VM type.
     Create a TARGET_EXPR so that the call always has a LHS, much as
     what the C++ FE does for functions returning non-PODs.  */
  اگر (c_type_variably_modified_p (درخت_TYPE (fntype)))
    {
      درخت tmp = create_tmp_var_raw (درخت_TYPE (fntype));
      result = build4 (TARGET_عبارت, درخت_TYPE (fntype), tmp, result,
		       NULL_درخت, NULL_درخت);
    }

  اگر (VOID_TYPE_P (درخت_TYPE (result)))
    {
      اگر (TYPE_QUALS (درخت_TYPE (result)) != TYPE_UNQUALIFIED)
	pedwarn (loc, 0,
		 "function with qualified void return type called");
      بازگشت result;
    }
  بازگشت require_complete_type (loc, result);
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
  اگر (درخت_CODE (function) == FUNCTION_DECL)
    {
      /* Implement type-directed function overloading for builtins.
	 resolve_overloaded_builtin and targetm.resolve_overloaded_builtin
	 handle all the type checking.  The result is a complete expression
	 that implements this function call.  */
      درخت tem = resolve_overloaded_builtin (loc, function, params);
      اگر (tem)
	بازگشت tem;
    }
  بازگشت build_function_call_vec (loc, arg_loc, function, params, origtypes);
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

ایستا درخت
convert_argument (location_t ploc, درخت function, درخت fundecl,
		  درخت type, درخت origtype, درخت val, درخت valtype,
		  منطقی npc, درخت rname, صحیح parmnum, صحیح argnum,
		  منطقی excess_precision, صحیح warnopt)
{
  /* Formal parm type is specified by a function prototype.  */

  اگر (type == error_mark_گره || !COMPLETE_TYPE_P (type))
    {
      error_at (ploc, "type of formal parameter %d is incomplete",
		parmnum + 1);
      بازگشت error_mark_گره;
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
	  && درخت_CODE (valtype) == COMPLEX_TYPE)
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as integer rather "
		    "than complex due to prototype",
		    argnum, rname);
      وگرنه اگر (درخت_CODE (type) == COMPLEX_TYPE
	       && SCALAR_FLOAT_TYPE_P (valtype))
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as complex rather "
		    "than floating due to prototype",
		    argnum, rname);
      وگرنه اگر (SCALAR_FLOAT_TYPE_P (type)
	       && INTEGRAL_TYPE_P (valtype))
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as floating rather "
		    "than integer due to prototype",
		    argnum, rname);
      وگرنه اگر (درخت_CODE (type) == COMPLEX_TYPE
	       && INTEGRAL_TYPE_P (valtype))
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as complex rather "
		    "than integer due to prototype",
		    argnum, rname);
      وگرنه اگر (SCALAR_FLOAT_TYPE_P (type)
	       && درخت_CODE (valtype) == COMPLEX_TYPE)
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as floating rather "
		    "than complex due to prototype",
		    argnum, rname);
      /* ??? At some point, messages should be written about
	 conversions between complex types, but that's too messy
	 to do now.  */
      وگرنه اگر (SCALAR_FLOAT_TYPE_P (type)
	       && SCALAR_FLOAT_TYPE_P (valtype))
	{
	  unsigned صحیح formal_prec = TYPE_PRECISION (type);

	  /* Warn if any argument is passed as `float',
	     since without a prototype it would be `double'.  */
	  اگر (formal_prec == TYPE_PRECISION (float_type_گره)
	      && type != dfloat32_type_گره)
	    warning_at (ploc, 0,
			"passing argument %d of %qE as %<float%> "
			"rather than %<double%> due to prototype",
			argnum, rname);

	  /* Warn if mismatch between argument and prototype
	     for decimal float types.  Warn of conversions with
	     binary float types and of precision narrowing due to
	     prototype.  */
	  وگرنه اگر (type != valtype
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
      وگرنه اگر (warn_traditional_conversion
	       && INTEGRAL_TYPE_P (type)
	       && INTEGRAL_TYPE_P (valtype))
	{
	  unsigned صحیح formal_prec = TYPE_PRECISION (type);
	  درخت would_have_been = default_conversion (val);
	  درخت type1 = درخت_TYPE (would_have_been);

	  اگر (val == error_mark_گره)
	    /* VAL could have been of incomplete type.  */;
	  وگرنه اگر (درخت_CODE (type) == ENUMERAL_TYPE
		   && (TYPE_MAIN_VARIANT (type)
		       == TYPE_MAIN_VARIANT (valtype)))
	    /* No warning if function asks for enum
	       and the actual arg is that enum type.  */
	    ;
	  وگرنه اگر (formal_prec != TYPE_PRECISION (type1))
	    warning_at (ploc, OPT_Wtraditional_conversion,
			"passing argument %d of %qE "
			"with different width due to prototype",
			argnum, rname);
	  وگرنه اگر (TYPE_UNSIGNED (type) == TYPE_UNSIGNED (type1))
	    ;
	  /* Don't complain if the formal parameter type
	     is an enum, because we can't tell now whether
	     the value was an enum--even the same enum.  */
	  وگرنه اگر (درخت_CODE (type) == ENUMERAL_TYPE)
	    ;
	  وگرنه اگر (درخت_CODE (val) == INTEGER_CST
		   && int_fits_type_p (val, type))
	    /* Change in signedness doesn't matter
	       if a constant value is unaffected.  */
	    ;
	  /* If the value is extended from a narrower
	     unsigned type, it doesn't matter whether we
	     pass it as signed or unsigned; the value
	     certainly is the same either way.  */
	  وگرنه اگر (TYPE_PRECISION (valtype) < TYPE_PRECISION (type)
		   && TYPE_UNSIGNED (valtype))
	    ;
	  وگرنه اگر (TYPE_UNSIGNED (type))
	    warning_at (ploc, OPT_Wtraditional_conversion,
			"passing argument %d of %qE "
			"as unsigned due to prototype",
			argnum, rname);
	  وگرنه
	    warning_at (ploc, OPT_Wtraditional_conversion,
			"passing argument %d of %qE "
			"as signed due to prototype",
			argnum, rname);
	}
    }

  /* Possibly restore an EXCESS_PRECISION_EXPR for the
     sake of better warnings from convert_and_check.  */
  اگر (excess_precision)
    val = build1 (EXCESS_PRECISION_عبارت, valtype, val);

  درخت parmval = convert_for_assignment (ploc, ploc, type,
					 val, origtype, ic_argpass,
					 npc, fundecl, function,
					 parmnum + 1, warnopt);
  بازگشت parmval;
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

ایستا صحیح
convert_arguments (location_t loc, vec<location_t> arg_loc, درخت fntype,
		   vec<درخت, va_gc> *مقادیر, vec<درخت, va_gc> *origtypes,
		   درخت function, درخت fundecl)
{
  درخت typelist = TYPE_ARG_TYPES (fntype);
  unsigned صحیح parmnum;
  منطقی error_args = نادرست;
  ثابت منطقی type_generic = fundecl
    && lookup_attribute ("type generic", TYPE_ATTRIBUTES (درخت_TYPE (fundecl)));
  منطقی type_generic_remove_excess_precision = نادرست;
  منطقی type_generic_overflow_p = نادرست;
  منطقی type_generic_bit_query = نادرست;
  درخت selector;

  /* Change pointer to function to the function itself for
     diagnostics.  */
  اگر (درخت_CODE (function) == ADDR_عبارت
      && درخت_CODE (درخت_OPERAND (function, 0)) == FUNCTION_DECL)
    function = درخت_OPERAND (function, 0);

  /* Handle an ObjC selector specially for diagnostics.  */
  selector = objc_message_selector ();

  /* For a call to a built-in function declared without a prototype,
     set to the built-in function's argument list.  */
  درخت builtin_typelist = NULL_درخت;

  /* For type-generic built-in functions, determine whether excess
     precision should be removed (classification) or not
     (comparison).  */
  اگر (fundecl
      && fndecl_built_in_p (fundecl, BUILT_IN_NORMAL))
    {
      built_in_function code = DECL_FUNCTION_CODE (fundecl);
      اگر (C_DECL_BUILTIN_PROTOTYPE (fundecl))
	{
	  /* For a call to a built-in function declared without a prototype
	     use the types of the parameters of the internal built-in to
	     match those of the arguments to.  */
	  اگر (درخت bdecl = builtin_decl_explicit (code))
	    builtin_typelist = TYPE_ARG_TYPES (درخت_TYPE (bdecl));
	}

      /* For type-generic built-in functions, determine whether excess
	 precision should be removed (classification) or not
	 (comparison).  */
      اگر (type_generic)
	انتخاب (code)
	  {
	  حالت BUILT_IN_ISFINITE:
	  حالت BUILT_IN_ISINF:
	  حالت BUILT_IN_ISINF_SIGN:
	  حالت BUILT_IN_ISNAN:
	  حالت BUILT_IN_ISNORMAL:
	  حالت BUILT_IN_ISSIGNALING:
	  حالت BUILT_IN_FPCLASSIFY:
	    type_generic_remove_excess_precision = درست;
	    بشکن;

	  حالت BUILT_IN_ADD_OVERFLOW_P:
	  حالت BUILT_IN_SUB_OVERFLOW_P:
	  حالت BUILT_IN_MUL_OVERFLOW_P:
	    /* The last argument of these type-generic builtins
	       should not be promoted.  */
	    type_generic_overflow_p = درست;
	    بشکن;

	  حالت BUILT_IN_CLZG:
	  حالت BUILT_IN_CTZG:
	  حالت BUILT_IN_CLRSBG:
	  حالت BUILT_IN_FFSG:
	  حالت BUILT_IN_PARITYG:
	  حالت BUILT_IN_POPCOUNTG:
	    /* The first argument of these type-generic builtins
	       should not be promoted.  */
	    type_generic_bit_query = درست;
	    بشکن;

	  پیشفرض:
	    بشکن;
	  }
    }

  /* Scan the given expressions (VALUES) and types (TYPELIST), producing
     individual converted arguments.  */

  درخت typetail, builtin_typetail, val;
  برای (typetail = typelist,
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
      صحیح argnum = parmnum + 1;
      ثابت نویسه *invalid_func_diag;
      /* Set for EXCESS_PRECISION_EXPR arguments.  */
      منطقی excess_precision = نادرست;
      /* The value of the argument after conversion to the type
	 of the function parameter it is passed to.  */
      درخت parmval;
      /* Some __atomic_* builtins have additional hidden argument at
	 position 0.  */
      location_t ploc
	= !arg_loc.is_empty () && مقادیر->length () == arg_loc.length ()
	  ? expansion_point_location_if_in_system_header (arg_loc[parmnum])
	  : درون_داد_location;

      اگر (type == void_type_گره)
	{
	  auto_diagnostic_group d;
	  صحیح رقم_expected = parmnum;
	  صحیح رقم_actual = مقادیر->length ();
	  gcc_rich_location rich_loc (loc);
	  اگر (ploc != درون_داد_location)
	    rich_loc.add_range (ploc);
	  اگر (selector)
	    error_at (&rich_loc,
		      "too many arguments to method %qE; expected %i, have %i",
		      selector, رقم_expected, رقم_actual);
	  وگرنه
	    error_at (&rich_loc,
		      "too many arguments to function %qE; expected %i, have %i",
		      function, رقم_expected, رقم_actual);
	  inform_declaration (fundecl, function);
	  بازگشت error_args ? -1 : (صحیح) parmnum;
	}

      اگر (builtin_type == void_type_گره)
	{
	  auto_diagnostic_group d;
	  اگر (warning_at (loc, OPT_Wbuiltin_declaration_mismatch,
			  "too many arguments to built-in function %qE "
			  "expecting %d", function, parmnum))
	    inform_declaration (fundecl, function);
	  builtin_typetail = NULL_درخت;
	}

      اگر (!typetail && parmnum == 0 && !TYPE_NO_NAMED_ARGS_STDARG_P (fntype)
	  && !(fundecl && fndecl_built_in_p (fundecl)))
	{
	  auto_diagnostic_group d;
	  منطقی warned;
	  اگر (selector)
	    warned = warning_at (loc, OPT_Wdeprecated_non_prototype,
				 "ISO C23 does not allow arguments"
				 " for method %qE declared without parameters",
				 function);
	  وگرنه
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
      منطقی npc = null_pointer_constant_p (val);

      /* If there is excess precision and a prototype, convert once to
	 the required type rather than converting via the semantic
	 type.  Likewise without a prototype a float value represented
	 as long double should be converted once to double.  But for
	 type-generic classification functions excess precision must
	 be removed here.  */
      اگر (درخت_CODE (val) == EXCESS_PRECISION_عبارت
	  && (type || !type_generic || !type_generic_remove_excess_precision))
	{
	  val = درخت_OPERAND (val, 0);
	  excess_precision = درست;
	}
      val = c_fully_fold (val, نادرست, پوچ);
      STRIP_TYPE_NOPS (val);

      val = require_complete_type (ploc, val);

      /* Some floating-point arguments must be promoted to double when
	 no type is specified by a prototype.  This applies to
	 arguments of type float, and to architecture-specific types
	 (ARM __fp16), but not to _FloatN or _FloatNx types.  */
      منطقی promote_float_arg = نادرست;
      اگر (type == NULL_درخت
	  && درخت_CODE (valtype) == REAL_TYPE
	  && (TYPE_PRECISION (valtype)
	      <= TYPE_PRECISION (double_type_گره))
	  && TYPE_MAIN_VARIANT (valtype) != double_type_گره
	  && TYPE_MAIN_VARIANT (valtype) != long_double_type_گره
	  && !DECIMAL_FLOAT_MODE_P (TYPE_MODE (valtype)))
	{
	  /* Promote this argument, unless it has a _FloatN or
	     _FloatNx type.  */
	  promote_float_arg = درست;
	  برای (صحیح i = 0; i < رقم_FLOATN_NX_TYPES; i++)
	    اگر (TYPE_MAIN_VARIANT (valtype) == FLOATN_NX_TYPE_گره (i))
	      {
		promote_float_arg = نادرست;
		بشکن;
	      }
	  /* Don't promote __bf16 either.  */
	  اگر (TYPE_MAIN_VARIANT (valtype) == bfloat16_type_گره)
	    promote_float_arg = نادرست;
	}

      اگر (type != NULL_درخت)
	{
	  درخت origtype = (!origtypes) ? NULL_درخت : (*origtypes)[parmnum];
	  parmval = convert_argument (ploc, function, fundecl, type, origtype,
				      val, valtype, npc, rname, parmnum, argnum,
				      excess_precision, 0);
	}
      /* A NULLPTR type is just a nullptr always.  */
      وگرنه اگر (درخت_CODE (درخت_TYPE (val)) == NULLPTR_TYPE)
	parmval = omit_one_operand_loc (ploc, درخت_TYPE (val), nullptr_گره, val);
      وگرنه اگر (promote_float_arg)
        {
	  اگر (type_generic)
	    parmval = val;
	  وگرنه
	    {
	      /* Convert `float' to `double'.  */
	      اگر (warn_double_promotion && !c_inhibit_evaluation_warnings)
		warning_at (ploc, OPT_Wdouble_promotion,
			    "implicit conversion from %qT to %qT when passing "
			    "argument to function",
			    valtype, double_type_گره);
	      parmval = convert (double_type_گره, val);
	    }
	}
      وگرنه اگر ((excess_precision && !type_generic)
	       || (type_generic_overflow_p && parmnum == 2)
	       || (type_generic_bit_query && parmnum == 0))
	/* A "double" argument with excess precision being passed
	   without a prototype or in variable arguments.
	   The last argument of __builtin_*_overflow_p should not be
	   promoted, similarly the first argument of
	   __builtin_{clz,ctz,clrsb,ffs,parity,popcount}g.  */
	parmval = convert (valtype, val);
      وگرنه اگر ((invalid_func_diag =
		targetm.calls.invalid_arg_for_unprototyped_fn (typelist, fundecl, val)))
	{
	  error (invalid_func_diag);
	  بازگشت -1;
	}
      وگرنه اگر (درخت_CODE (val) == ADDR_عبارت && reject_gcc_builtin (val))
	{
	  بازگشت -1;
	}
      وگرنه
	/* Convert `short' and `char' to full-size `int'.  */
	parmval = default_conversion (val);

      (*مقادیر)[parmnum] = parmval;
      اگر (parmval == error_mark_گره)
	error_args = درست;

      اگر (!type && builtin_type && درخت_CODE (builtin_type) != VOID_TYPE)
	{
	  /* For a call to a built-in function declared without a prototype,
	     perform the conversions from the argument to the expected type
	     but issue warnings rather than errors for any mismatches.
	     Ignore the converted argument and use the PARMVAL obtained
	     above by applying default conversions instead.  */
	  درخت origtype = (!origtypes) ? NULL_درخت : (*origtypes)[parmnum];
	  convert_argument (ploc, function, fundecl, builtin_type, origtype,
			    val, valtype, npc, rname, parmnum, argnum,
			    excess_precision,
			    OPT_Wbuiltin_declaration_mismatch);
	}

      اگر (typetail)
	typetail = درخت_CHAIN (typetail);

      اگر (builtin_typetail)
	builtin_typetail = درخت_CHAIN (builtin_typetail);
    }

  gcc_assert (parmnum == vec_safe_length (مقادیر));

  اگر (typetail != NULL_درخت && درخت_مقدار (typetail) != void_type_گره)
    {
      /* Not enough args.
	 Determine minimum number of arguments required.  */
      صحیح min_expected_رقم = 0;
      منطقی at_least_p = نادرست;
      درخت iter = typelist;
      وقتی (درست)
	{
	  اگر (!iter)
	    {
	      /* Variadic arguments; stop iterating.  */
	      at_least_p = درست;
	      بشکن;
	    }
	  اگر (iter == void_list_گره)
	    /* End of arguments; stop iterating.  */
	    بشکن;
	  ++min_expected_رقم;
	  iter = درخت_CHAIN (iter);
	}
      auto_diagnostic_group d;
      صحیح actual_رقم = vec_safe_length (مقادیر);
      error_at (loc,
		at_least_p
		? G_("too few arguments to function %qE; expected at least %i, have %i")
		: G_("too few arguments to function %qE; expected %i, have %i"),
		function, min_expected_رقم, actual_رقم);
      inform_declaration (fundecl, function);
      بازگشت -1;
    }

  اگر (builtin_typetail && درخت_مقدار (builtin_typetail) != void_type_گره)
    {
      unsigned nargs = parmnum;
      برای (درخت t = builtin_typetail; t; t = درخت_CHAIN (t))
	++nargs;

      auto_diagnostic_group d;
      اگر (warning_at (loc, OPT_Wbuiltin_declaration_mismatch,
		      "too few arguments to built-in function %qE "
		      "expecting %u", function, nargs - 1))
	inform_declaration (fundecl, function);
    }

  بازگشت error_args ? -1 : (صحیح) parmnum;
}

/* This is the entry point used by the parser to build unary operators
   in the input.  CODE, a tree_code, specifies the unary operator, and
   ARG is the operand.  For unary plus, the C parser currently uses
   CONVERT_EXPR for code.

   LOC is the location to use for the tree generated.
*/

ساختار c_عبارت
parser_build_unary_op (location_t loc, شمارش درخت_code code, ساختار c_عبارت arg)
{
  ساختار c_عبارت result;

  result.original_code = code;
  result.original_type = پوچ;
  result.m_decimal = 0;

  اگر (reject_gcc_builtin (arg.مقدار))
    {
      result.مقدار = error_mark_گره;
    }
  وگرنه
    {
      result.مقدار = build_unary_op (loc, code, arg.مقدار, نادرست);

      اگر (درخت_OVERFLOW_P (result.مقدار) && !درخت_OVERFLOW_P (arg.مقدار))
	overflow_warning (loc, result.مقدار, arg.مقدار);
    }

  /* We are typically called when parsing a prefix token at LOC acting on
     ARG.  Reflect this by updating the source range of the result to
     start at LOC and end at the end of ARG.  */
  set_c_عبارت_source_range (&result,
			   loc, arg.get_finish ());

  بازگشت result;
}

/* Returns true if TYPE is a character type, *not* including wchar_t.  */

منطقی
char_type_p (درخت type)
{
  بازگشت (type == char_type_گره
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

ساختار c_عبارت
parser_build_دودویی_op (location_t location, شمارش درخت_code code,
			ساختار c_عبارت arg1, ساختار c_عبارت arg2, درخت orig_arg1)
{
  ساختار c_عبارت result;
  result.m_decimal = 0;

  شمارش درخت_code code1 = arg1.original_code;
  شمارش درخت_code code2 = arg2.original_code;
  درخت type1 = (arg1.original_type
                ? arg1.original_type
                : درخت_TYPE (arg1.مقدار));
  درخت type2 = (arg2.original_type
                ? arg2.original_type
                : درخت_TYPE (arg2.مقدار));

  result.مقدار = build_دودویی_op (location, code,
				  arg1.مقدار, arg2.مقدار, درست);
  result.original_code = code;
  result.original_type = پوچ;
  result.m_decimal = 0;

  اگر (درخت_CODE (result.مقدار) == ERROR_MARK)
    {
      set_c_عبارت_source_range (&result,
			       arg1.get_start (),
			       arg2.get_finish ());
      بازگشت result;
    }

  اگر (location != UNKNOWN_LOCATION)
    protected_set_عبارت_location (result.مقدار, location);

  set_c_عبارت_source_range (&result,
			   arg1.get_start (),
			   arg2.get_finish ());

  /* Check for cases such as x+y<<z which users are likely
     to misinterpret.  */
  اگر (warn_parentheses)
    warn_about_parentheses (location, code, code1, arg1.مقدار, code2,
			    arg2.مقدار);

  اگر (warn_logical_op)
    warn_logical_operator (location, code, درخت_TYPE (result.مقدار),
			   code1, arg1.مقدار, code2, arg2.مقدار);

  اگر (warn_constant_logical_operand
      && (code == TRUTH_ANDIF_عبارت || code == TRUTH_ORIF_عبارت)
      && INTEGRAL_NB_TYPE_P (type1)
      && INTEGRAL_NB_TYPE_P (type2))
    {
      ثابت نویسه *name = code == TRUTH_ANDIF_عبارت ? "&&" : "||";
      اگر (orig_arg1 == NULL_درخت)
	orig_arg1 = arg1.مقدار;
      auto enum_other_than_0_1 = [] (درخت type) {
	اگر (درخت_CODE (type) != ENUMERAL_TYPE)
	  بازگشت نادرست;
	برای (درخت l = TYPE_مقادیر (type); l; l = درخت_CHAIN (l))
	  {
	    درخت v = DECL_INITIAL (درخت_مقدار (l));
	    اگر (!integer_zerop (v) && !integer_onep (v))
	      بازگشت درست;
	  }
	بازگشت نادرست;
      };
      auto diagnose_constant_logical_operand = [=] (درخت val, درخت type) {
	اگر (درخت_CODE (val) != INTEGER_CST || integer_zerop (val))
	  بازگشت نادرست;
	اگر (integer_onep (val) && !enum_other_than_0_1 (type))
	  بازگشت نادرست;
	gcc_rich_location richloc (location);
	richloc.add_fixit_replace (name + 1);
	auto_diagnostic_group d;
	اگر (warning_at (location, OPT_Wconstant_logical_operand,
			"use of logical %qs with constant operand %qE",
			name, val))
	  inform (&richloc, "use %qs for bitwise operation", name + 1);
	بازگشت درست;
      };
      اگر (!diagnose_constant_logical_operand (arg2.مقدار, type2))
	diagnose_constant_logical_operand (orig_arg1, type1);
    }

  اگر (warn_tautological_compare)
    {
      درخت lhs = arg1.مقدار;
      درخت rhs = arg2.مقدار;
      اگر (درخت_CODE (lhs) == C_MAYBE_CONST_عبارت)
	{
	  اگر (C_MAYBE_CONST_عبارت_PRE (lhs) != NULL_درخت
	      && درخت_SIDE_EFFECTS (C_MAYBE_CONST_عبارت_PRE (lhs)))
	    lhs = NULL_درخت;
	  وگرنه
	    lhs = C_MAYBE_CONST_عبارت_عبارت (lhs);
	}
      اگر (درخت_CODE (rhs) == C_MAYBE_CONST_عبارت)
	{
	  اگر (C_MAYBE_CONST_عبارت_PRE (rhs) != NULL_درخت
	      && درخت_SIDE_EFFECTS (C_MAYBE_CONST_عبارت_PRE (rhs)))
	    rhs = NULL_درخت;
	  وگرنه
	    rhs = C_MAYBE_CONST_عبارت_عبارت (rhs);
	}
      اگر (lhs != NULL_درخت && rhs != NULL_درخت)
	warn_tautological_cmp (location, code, lhs, rhs);
    }

  اگر (warn_logical_not_paren
      && درخت_CODE_CLASS (code) == tcc_comparison
      && code1 == TRUTH_NOT_عبارت
      && code2 != TRUTH_NOT_عبارت
      /* Avoid warning for !!x == y.  */
      && (درخت_CODE (arg1.مقدار) != NE_عبارت
	  || !integer_zerop (درخت_OPERAND (arg1.مقدار, 1))))
    {
      /* Avoid warning for !b == y where b has _Bool type.  */
      درخت t = integer_zero_گره;
      اگر (درخت_CODE (arg1.مقدار) == EQ_عبارت
	  && integer_zerop (درخت_OPERAND (arg1.مقدار, 1))
	  && درخت_TYPE (درخت_OPERAND (arg1.مقدار, 0)) == integer_type_گره)
	{
	  t = درخت_OPERAND (arg1.مقدار, 0);
	  انجامبده
	    {
	      اگر (درخت_TYPE (t) != integer_type_گره)
		بشکن;
	      اگر (درخت_CODE (t) == C_MAYBE_CONST_عبارت)
		t = C_MAYBE_CONST_عبارت_عبارت (t);
	      وگرنه اگر (CONVERT_عبارت_P (t))
		t = درخت_OPERAND (t, 0);
	      وگرنه
		بشکن;
	    }
	  وقتی (1);
	}
      اگر (!C_BOOLEAN_TYPE_P (درخت_TYPE (t)))
	warn_logical_not_parentheses (location, code, arg1.مقدار, arg2.مقدار);
    }

  /* Warn about comparisons against string literals, with the exception
     of testing for equality or inequality of a string literal with NULL.  */
  اگر (code == EQ_عبارت || code == NE_عبارت)
    {
      اگر ((code1 == STRING_CST
	   && !integer_zerop (درخت_strip_nop_conversions (arg2.مقدار)))
	  || (code2 == STRING_CST
	      && !integer_zerop (درخت_strip_nop_conversions (arg1.مقدار))))
	warning_at (location, OPT_Waddress,
		    "comparison with string literal results in unspecified behavior");
      /* Warn for ptr == '\0', it's likely that it should've been ptr[0].  */
      اگر (POINTER_TYPE_P (type1)
	  && null_pointer_constant_p (arg2.مقدار)
	  && char_type_p (type2))
	{
	  auto_diagnostic_group d;
	  اگر (warning_at (location, OPT_Wpointer_compare,
			    "comparison between pointer and zero character "
			    "constant"))
	    inform (arg1.get_start (),
		      "did you mean to dereference the pointer?");
	}
      وگرنه اگر (POINTER_TYPE_P (type2)
	       && null_pointer_constant_p (arg1.مقدار)
	       && char_type_p (type1))
	{
	  auto_diagnostic_group d;
	  اگر (warning_at (location, OPT_Wpointer_compare,
			    "comparison between pointer and zero character "
			    "constant"))
	    inform (arg2.get_start (),
		      "did you mean to dereference the pointer?");
	}
    }
  وگرنه اگر (درخت_CODE_CLASS (code) == tcc_comparison
	   && (code1 == STRING_CST || code2 == STRING_CST))
    warning_at (location, OPT_Waddress,
		"comparison with string literal results in unspecified "
		"behavior");

  اگر (warn_zero_as_null_pointer_constant
      && c_inhibit_evaluation_warnings == 0
      && درخت_CODE_CLASS (code) == tcc_comparison)
    {
      اگر ((درخت_CODE (type1) == POINTER_TYPE
	   || درخت_CODE (type1) == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type2)
	  && null_pointer_constant_p (arg2.مقدار))
	warning_at (arg2.get_location(), OPT_Wzero_as_null_pointer_constant,
		    "zero as null pointer constant");

      اگر ((درخت_CODE (type2) == POINTER_TYPE
	   || درخت_CODE (type2) == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type1)
	  && null_pointer_constant_p (arg1.مقدار))
	warning_at (arg1.get_location(), OPT_Wzero_as_null_pointer_constant,
		    "zero as null pointer constant");
    }

  اگر (warn_array_compare
      && درخت_CODE_CLASS (code) == tcc_comparison
      && درخت_CODE (type1) == ARRAY_TYPE
      && درخت_CODE (type2) == ARRAY_TYPE)
    do_warn_array_compare (location, code, arg1.مقدار, arg2.مقدار);

  اگر (درخت_OVERFLOW_P (result.مقدار)
      && !درخت_OVERFLOW_P (arg1.مقدار)
      && !درخت_OVERFLOW_P (arg2.مقدار))
    overflow_warning (location, result.مقدار);

  /* Warn about comparisons of different enum types.  */
  اگر (warn_enum_compare
      && درخت_CODE_CLASS (code) == tcc_comparison
      && درخت_CODE (type1) == ENUMERAL_TYPE
      && درخت_CODE (type2) == ENUMERAL_TYPE
      && TYPE_MAIN_VARIANT (type1) != TYPE_MAIN_VARIANT (type2))
    warning_at (location, OPT_Wenum_compare,
		"comparison between %qT and %qT",
		type1, type2);

  اگر (warn_xor_used_as_pow
      && code == BIT_XOR_عبارت
      && arg1.m_decimal
      && arg2.m_decimal)
    check_for_xor_used_as_pow (arg1.get_location (), arg1.مقدار,
			       location,
			       arg2.get_location (), arg2.مقدار);

  بازگشت result;
}

/* Return a tree for the difference of pointers OP0 and OP1.
   The resulting tree has type ptrdiff_t.  If POINTER_SUBTRACT sanitization is
   enabled, assign to INSTRUMENT_EXPR call to libsanitizer.  */

ایستا درخت
pointer_diff (location_t loc, درخت op0, درخت op1, درخت *instrument_عبارت)
{
  درخت restype = ptrdiff_type_گره;
  درخت result, inttype;

  addr_space_t as0 = TYPE_ADDR_SPACE (درخت_TYPE (درخت_TYPE (op0)));
  addr_space_t as1 = TYPE_ADDR_SPACE (درخت_TYPE (درخت_TYPE (op1)));
  درخت target_type = درخت_TYPE (درخت_TYPE (op0));
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

      common_type = common_pointer_type (درخت_TYPE (op0), درخت_TYPE (op1), NULL_درخت);
      op0 = convert (common_type, op0);
      op1 = convert (common_type, op1);
    }

  /* Determine integer type result of the subtraction.  This will usually
     be the same as the result type (ptrdiff_t), but may need to be a wider
     type if pointers for the address space are wider than ptrdiff_t.  */
  اگر (TYPE_PRECISION (restype) < TYPE_PRECISION (درخت_TYPE (op0)))
    inttype = c_common_type_for_size (TYPE_PRECISION (درخت_TYPE (op0)), 0);
  وگرنه
    inttype = restype;

  اگر (VOID_TYPE_P (target_type))
    pedwarn (loc, OPT_Wpointer_arith,
	     "pointer of type %<void *%> used in subtraction");
  اگر (درخت_CODE (target_type) == FUNCTION_TYPE)
    pedwarn (loc, OPT_Wpointer_arith,
	     "pointer to a function used in subtraction");

  اگر (current_function_decl != NULL_درخت
      && sanitize_flags_p (SANITIZE_POINTER_SUBTRACT))
    {
      op0 = save_عبارت (c_fully_fold (op0, نادرست, پوچ));
      op1 = save_عبارت (c_fully_fold (op1, نادرست, پوچ));

      درخت tt = builtin_decl_explicit (BUILT_IN_ASAN_POINTER_SUBTRACT);
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
  اگر (TYPE_PRECISION (inttype) > TYPE_PRECISION (درخت_TYPE (op0)))
    op0 = build_دودویی_op (loc, MINUS_عبارت, convert (inttype, op0),
			   convert (inttype, op1), نادرست);
  وگرنه
    {
      /* Cast away qualifiers.  */
      op0 = convert (c_common_type (درخت_TYPE (op0), درخت_TYPE (op0)), op0);
      op1 = convert (c_common_type (درخت_TYPE (op1), درخت_TYPE (op1)), op1);
      op0 = build2_loc (loc, POINTER_DIFF_عبارت, inttype, op0, op1);
    }

  /* This generates an error if op1 is pointer to incomplete type.  */
  اگر (!COMPLETE_OR_VOID_TYPE_P (درخت_TYPE (درخت_TYPE (orig_op1))))
    error_at (loc, "arithmetic on pointer to an incomplete type");
  وگرنه اگر (verify_type_context (loc, TCTX_POINTER_ARITH,
				درخت_TYPE (درخت_TYPE (orig_op0))))
    verify_type_context (loc, TCTX_POINTER_ARITH,
			 درخت_TYPE (درخت_TYPE (orig_op1)));

  op1 = c_size_in_bytes (target_type);

  اگر (pointer_to_zero_sized_aggr_p (درخت_TYPE (orig_op1)))
    error_at (loc, "arithmetic on pointer to an empty aggregate");

  /* Divide by the size, in easiest possible way.  */
  result = fold_build2_loc (loc, EXACT_DIV_عبارت, inttype,
			    op0, convert (inttype, op1));

  /* Convert to final result type if necessary.  */
  بازگشت convert (restype, result);
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

ایستا درخت
build_atomic_assign (location_t loc, درخت lhs, شمارش درخت_code modifycode,
		     درخت rhs, منطقی return_old_p)
{
  درخت fndecl, func_call;
  vec<درخت, va_gc> *params;
  درخت val, nonatomic_lhs_type, nonatomic_rhs_type, newval, newval_addr;
  درخت old, old_addr;
  درخت compound_stmt = NULL_درخت;
  درخت stmt, goto_stmt;
  درخت loop_label, loop_decl, done_label, done_decl;

  درخت lhs_type = درخت_TYPE (lhs);
  درخت lhs_addr = build_unary_op (loc, ADDR_عبارت, lhs, نادرست);
  درخت seq_cst = build_int_cst (integer_type_گره, MEMMODEL_SEQ_CST);
  درخت rhs_semantic_type = درخت_TYPE (rhs);
  درخت nonatomic_rhs_semantic_type;
  درخت rhs_type;

  gcc_assert (TYPE_ATOMIC (lhs_type));

  اگر (return_old_p)
    gcc_assert (modifycode == PLUS_عبارت || modifycode == MINUS_عبارت);

  /* Allocate enough vector items for a compare_exchange.  */
  vec_alloc (params, 6);

  /* Create a compound statement to hold the sequence of statements
     with a loop.  */
  اگر (modifycode != NOP_عبارت)
    {
      compound_stmt = c_begin_compound_stmt (نادرست);

      /* For consistency with build_modify_expr on non-_Atomic,
	 mark the lhs as read.  Also, it would be very hard to match
	 such expressions in mark_exp_read.  */
      mark_exp_read (lhs);
    }

  /* Remove any excess precision (which is only present here in the
     case of compound assignments).  */
  اگر (درخت_CODE (rhs) == EXCESS_PRECISION_عبارت)
    {
      gcc_assert (modifycode != NOP_عبارت);
      rhs = درخت_OPERAND (rhs, 0);
    }
  rhs_type = درخت_TYPE (rhs);

  /* Fold the RHS if it hasn't already been folded.  */
  اگر (modifycode != NOP_عبارت)
    rhs = c_fully_fold (rhs, نادرست, پوچ);

  /* Remove the qualifiers for the rest of the expressions and create
     the VAL temp variable to hold the RHS.  */
  nonatomic_lhs_type = build_qualified_type (lhs_type, TYPE_UNQUALIFIED);
  nonatomic_rhs_type = build_qualified_type (rhs_type, TYPE_UNQUALIFIED);
  nonatomic_rhs_semantic_type = build_qualified_type (rhs_semantic_type,
						      TYPE_UNQUALIFIED);
  val = create_tmp_var_raw (nonatomic_rhs_type);
  درخت_ADDRESSABLE (val) = 1;
  suppress_warning (val);
  rhs = build4 (TARGET_عبارت, nonatomic_rhs_type, val, rhs, NULL_درخت,
		NULL_درخت);
  درخت_SIDE_EFFECTS (rhs) = 1;
  SET_عبارت_LOCATION (rhs, loc);
  اگر (modifycode != NOP_عبارت)
    add_stmt (rhs);

  /* NOP_EXPR indicates it's a straight store of the RHS. Simply issue
     an atomic_store.  */
  اگر (modifycode == NOP_عبارت)
    {
      compound_stmt = rhs;
      /* Build __atomic_store (&lhs, &val, SEQ_CST)  */
      rhs = build_unary_op (loc, ADDR_عبارت, val, نادرست);
      fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_STORE);
      params->quick_افزودن (lhs_addr);
      params->quick_افزودن (rhs);
      params->quick_افزودن (seq_cst);
      func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, پوچ);

      compound_stmt = build2 (COMPOUND_عبارت, void_type_گره,
			      compound_stmt, func_call);

      /* VAL is the value which was stored, return a COMPOUND_STMT of
	 the statement and that value.  */
      بازگشت build2 (COMPOUND_عبارت, nonatomic_lhs_type, compound_stmt, val);
    }

  /* Attempt to implement the atomic operation as an __atomic_fetch_* or
     __atomic_*_fetch built-in rather than a CAS loop.  atomic_bool type
     isn't applicable for such builtins.  ??? Do we want to handle enums?  */
  اگر ((درخت_CODE (lhs_type) == INTEGER_TYPE || POINTER_TYPE_P (lhs_type))
      && درخت_CODE (rhs_type) == INTEGER_TYPE)
    {
      built_in_function fncode;
      انتخاب (modifycode)
	{
	حالت PLUS_عبارت:
	حالت POINTER_PLUS_عبارت:
	  fncode = (return_old_p
		    ? BUILT_IN_ATOMIC_FETCH_ADD_N
		    : BUILT_IN_ATOMIC_ADD_FETCH_N);
	  بشکن;
	حالت MINUS_عبارت:
	  fncode = (return_old_p
		    ? BUILT_IN_ATOMIC_FETCH_SUB_N
		    : BUILT_IN_ATOMIC_SUB_FETCH_N);
	  بشکن;
	حالت BIT_AND_عبارت:
	  fncode = (return_old_p
		    ? BUILT_IN_ATOMIC_FETCH_AND_N
		    : BUILT_IN_ATOMIC_AND_FETCH_N);
	  بشکن;
	حالت BIT_IOR_عبارت:
	  fncode = (return_old_p
		    ? BUILT_IN_ATOMIC_FETCH_OR_N
		    : BUILT_IN_ATOMIC_OR_FETCH_N);
	  بشکن;
	حالت BIT_XOR_عبارت:
	  fncode = (return_old_p
		    ? BUILT_IN_ATOMIC_FETCH_XOR_N
		    : BUILT_IN_ATOMIC_XOR_FETCH_N);
	  بشکن;
	پیشفرض:
	  برو cas_loop;
	}

      /* We can only use "_1" through "_16" variants of the atomic fetch
	 built-ins.  */
      unsigned HOST_WIDE_INT size = درخت_to_uhwi (TYPE_SIZE_UNIT (lhs_type));
      اگر (size != 1 && size != 2 && size != 4 && size != 8 && size != 16)
	برو cas_loop;

      /* If this is a pointer type, we need to multiply by the size of
	 the pointer target type.  */
      اگر (POINTER_TYPE_P (lhs_type))
	{
	  اگر (!COMPLETE_TYPE_P (درخت_TYPE (lhs_type))
	      /* ??? This would introduce -Wdiscarded-qualifiers
		 warning: __atomic_fetch_* expect volatile void *
		 type as the first argument.  (Assignments between
		 atomic and non-atomic objects are OK.) */
	      || TYPE_RESTRICT (lhs_type))
	    برو cas_loop;
	  درخت sz = TYPE_SIZE_UNIT (درخت_TYPE (lhs_type));
	  rhs = fold_build2_loc (loc, MULT_عبارت, ptrdiff_type_گره,
				 convert (ptrdiff_type_گره, rhs),
				 convert (ptrdiff_type_گره, sz));
	}

      /* Build __atomic_fetch_* (&lhs, &val, SEQ_CST), or
	 __atomic_*_fetch (&lhs, &val, SEQ_CST).  */
      fndecl = builtin_decl_explicit (fncode);
      params->quick_افزودن (lhs_addr);
      params->quick_افزودن (rhs);
      params->quick_افزودن (seq_cst);
      func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, پوچ);

      newval = create_tmp_var_raw (nonatomic_lhs_type);
      درخت_ADDRESSABLE (newval) = 1;
      suppress_warning (newval);
      rhs = build4 (TARGET_عبارت, nonatomic_lhs_type, newval, func_call,
		    NULL_درخت, NULL_درخت);
      SET_عبارت_LOCATION (rhs, loc);
      add_stmt (rhs);

      /* Finish the compound statement.  */
      compound_stmt = c_end_compound_stmt (loc, compound_stmt, نادرست);

      /* NEWVAL is the value which was stored, return a COMPOUND_STMT of
	 the statement and that value.  */
      بازگشت build2 (COMPOUND_عبارت, nonatomic_lhs_type, compound_stmt, newval);
    }

cas_loop:
  /* Create the variables and labels required for the op= form.  */
  old = create_tmp_var_raw (nonatomic_lhs_type);
  old_addr = build_unary_op (loc, ADDR_عبارت, old, نادرست);
  درخت_ADDRESSABLE (old) = 1;
  suppress_warning (old);

  newval = create_tmp_var_raw (nonatomic_lhs_type);
  newval_addr = build_unary_op (loc, ADDR_عبارت, newval, نادرست);
  درخت_ADDRESSABLE (newval) = 1;
  suppress_warning (newval);

  loop_decl = create_artificial_label (loc);
  loop_label = build1 (LABEL_عبارت, void_type_گره, loop_decl);

  done_decl = create_artificial_label (loc);
  done_label = build1 (LABEL_عبارت, void_type_گره, done_decl);

  /* __atomic_load (addr, &old, SEQ_CST).  */
  fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_LOAD);
  params->quick_افزودن (lhs_addr);
  params->quick_افزودن (old_addr);
  params->quick_افزودن (seq_cst);
  func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, پوچ);
  old = build4 (TARGET_عبارت, nonatomic_lhs_type, old, func_call, NULL_درخت,
		NULL_درخت);
  add_stmt (old);
  params->truncate (0);

  /* Create the expressions for floating-point environment
     manipulation, if required.  */
  منطقی need_fenv = (flag_trapping_math
		    && (FLOAT_TYPE_P (lhs_type) || FLOAT_TYPE_P (rhs_type)));
  درخت hold_call = NULL_درخت, clear_call = NULL_درخت, update_call = NULL_درخت;
  اگر (need_fenv)
    targetm.atomic_assign_expand_fenv (&hold_call, &clear_call, &update_call);

  اگر (hold_call)
    add_stmt (hold_call);

  /* loop:  */
  add_stmt (loop_label);

  /* newval = old + val;  */
  اگر (rhs_type != rhs_semantic_type)
    val = build1 (EXCESS_PRECISION_عبارت, nonatomic_rhs_semantic_type, val);
  rhs = build_دودویی_op (loc, modifycode,
			 convert_lvalue_to_rvalue (loc, old, درست, درست),
			 val, درست);
  اگر (درخت_CODE (rhs) == EXCESS_PRECISION_عبارت)
    {
      درخت eptype = درخت_TYPE (rhs);
      rhs = c_fully_fold (درخت_OPERAND (rhs, 0), نادرست, پوچ);
      rhs = build1 (EXCESS_PRECISION_عبارت, eptype, rhs);
    }
  وگرنه
    rhs = c_fully_fold (rhs, نادرست, پوچ);
  rhs = convert_for_assignment (loc, UNKNOWN_LOCATION, nonatomic_lhs_type,
				rhs, NULL_درخت, ic_assign, نادرست, NULL_درخت,
				NULL_درخت, 0);
  /* The temporary variable for NEWVAL is only gimplified correctly (in
     particular, given a DECL_CONTEXT) if used in a TARGET_EXPR.  To avoid
     subsequent ICEs in nested function processing after an error, ensure such
     a TARGET_EXPR is built even after an error.  */
  اگر (rhs == error_mark_گره)
    rhs = old;
  rhs = build4 (TARGET_عبارت, nonatomic_lhs_type, newval, rhs, NULL_درخت,
		NULL_درخت);
  SET_عبارت_LOCATION (rhs, loc);
  add_stmt (rhs);

  /* if (__atomic_compare_exchange (addr, &old, &new, false, SEQ_CST, SEQ_CST))
       goto done;  */
  fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_COMPARE_EXCHANGE);
  params->quick_افزودن (lhs_addr);
  params->quick_افزودن (old_addr);
  params->quick_افزودن (newval_addr);
  params->quick_افزودن (integer_zero_گره);
  params->quick_افزودن (seq_cst);
  params->quick_افزودن (seq_cst);
  func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, پوچ);

  goto_stmt = build1 (GOTO_عبارت, void_type_گره, done_decl);
  SET_عبارت_LOCATION (goto_stmt, loc);

  stmt = build3 (COND_عبارت, void_type_گره, func_call, goto_stmt, NULL_درخت);
  SET_عبارت_LOCATION (stmt, loc);
  add_stmt (stmt);

  اگر (clear_call)
    add_stmt (clear_call);

  /* goto loop;  */
  goto_stmt  = build1 (GOTO_عبارت, void_type_گره, loop_decl);
  SET_عبارت_LOCATION (goto_stmt, loc);
  add_stmt (goto_stmt);

  /* done:  */
  add_stmt (done_label);

  اگر (update_call)
    add_stmt (update_call);

  /* Finish the compound statement.  */
  compound_stmt = c_end_compound_stmt (loc, compound_stmt, نادرست);

  /* NEWVAL is the value that was successfully stored, return a
     COMPOUND_EXPR of the statement and the appropriate value.  */
  بازگشت build2 (COMPOUND_عبارت, nonatomic_lhs_type, compound_stmt,
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
build_unary_op (location_t location, شمارش درخت_code code, درخت xarg,
		منطقی noconvert)
{
  /* No default_conversion here.  It causes trouble for ADDR_EXPR.  */
  درخت arg = xarg;
  درخت argtype = NULL_درخت;
  شمارش درخت_code typecode;
  درخت val;
  درخت ret = error_mark_گره;
  درخت eptype = NULL_درخت;
  ثابت نویسه *invalid_op_diag;

  /* If ARG is wrapped in a call to .ACCESS_WITH_SIZE — created when the
     C parser rvalue-converts a counted_by-annotated member access (see
     PR123569) — unwrap it here.  Unary operators that consume an rvalue
     (!, -, +) read the value itself rather than dereferencing into the
     pointed-to data, so the bounds-checking wrapper is unnecessary and
     would otherwise reach build_unary_op while it is not equipped to
     handle the wrapped form.  PR123569 fixed the ++/-- side of this by
     suppressing wrapper creation in the parser; the rvalue-consuming
     ops still receive the wrapper and need to strip it here.  */
  اگر (is_access_with_size_p (arg))
    xarg = arg = get_ref_from_access_with_size (arg);

  gcc_checking_assert (!is_access_with_size_p (arg));

  منطقی int_operands = عبارت_INT_CONST_OPERANDS (xarg);
  اگر (int_operands)
    arg = remove_c_maybe_const_عبارت (arg);

  اگر (code != ADDR_عبارت)
    arg = require_complete_type (location, arg);

  typecode = درخت_CODE (درخت_TYPE (arg));
  اگر (typecode == ERROR_MARK)
    بازگشت error_mark_گره;
  اگر (typecode == ENUMERAL_TYPE || typecode == BOOLEAN_TYPE)
    typecode = INTEGER_TYPE;

  اگر ((invalid_op_diag
       = targetm.invalid_unary_op (code, درخت_TYPE (xarg))))
    {
      error_at (location, invalid_op_diag);
      بازگشت error_mark_گره;
    }

  اگر (درخت_CODE (arg) == EXCESS_PRECISION_عبارت)
    {
      eptype = درخت_TYPE (arg);
      arg = درخت_OPERAND (arg, 0);
    }

  انتخاب (code)
    {
    حالت CONVERT_عبارت:
      /* This is used for unary plus, because a CONVERT_EXPR
	 is enough to prevent anybody from looking inside for
	 associativity, but won't generate any code.  */
      اگر (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE
	    || typecode == FIXED_POINT_TYPE || typecode == COMPLEX_TYPE
	    || typecode == BITINT_TYPE
	    || gnu_vector_type_p (درخت_TYPE (arg))))
	{
	  error_at (location, "wrong type argument to unary plus");
	  بازگشت error_mark_گره;
	}
      وگرنه اگر (!noconvert)
	arg = default_conversion (arg);
      arg = non_lvalue_loc (location, arg);
      بشکن;

    حالت NEGATE_عبارت:
      اگر (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE
	    || typecode == FIXED_POINT_TYPE || typecode == COMPLEX_TYPE
	    || typecode == BITINT_TYPE
	    || gnu_vector_type_p (درخت_TYPE (arg))))
	{
	  error_at (location, "wrong type argument to unary minus");
	  بازگشت error_mark_گره;
	}
      وگرنه اگر (!noconvert)
	arg = default_conversion (arg);
      بشکن;

    حالت BIT_NOT_عبارت:
      /* ~ works on integer types and non float vectors. */
      اگر (typecode == INTEGER_TYPE
	  || typecode == BITINT_TYPE
	  || (gnu_vector_type_p (درخت_TYPE (arg))
	      && !VECTOR_FLOAT_TYPE_P (درخت_TYPE (arg))))
	{
	  درخت e = arg;

	  /* Warn if the expression has boolean value.  */
	  وقتی (درخت_CODE (e) == COMPOUND_عبارت)
	    e = درخت_OPERAND (e, 1);

	  اگر ((C_BOOLEAN_TYPE_P (درخت_TYPE (arg))
	       || truth_مقدار_p (درخت_CODE (e))))
	    {
	      auto_diagnostic_group d;
	      اگر (warning_at (location, OPT_Wbool_operation,
				"%<~%> on a boolean expression"))
		{
		  gcc_rich_location richloc (location);
		  richloc.add_fixit_درج_before (location, "!");
		  inform (&richloc, "did you mean to use logical not?");
		}
	    }
	  اگر (!noconvert)
	    arg = default_conversion (arg);
	}
      وگرنه اگر (typecode == COMPLEX_TYPE)
	{
	  code = CONJ_عبارت;
	  pedwarn (location, OPT_Wpedantic,
		   "ISO C does not support %<~%> for complex conjugation");
	  اگر (!noconvert)
	    arg = default_conversion (arg);
	}
      وگرنه
	{
	  error_at (location, "wrong type argument to bit-complement");
	  بازگشت error_mark_گره;
	}
      بشکن;

    حالت ABS_عبارت:
      اگر (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE))
	{
	  error_at (location, "wrong type argument to abs");
	  بازگشت error_mark_گره;
	}
      وگرنه اگر (!noconvert)
	arg = default_conversion (arg);
      بشکن;

    حالت ABSU_عبارت:
      اگر (!(typecode == INTEGER_TYPE))
	{
	  error_at (location, "wrong type argument to absu");
	  بازگشت error_mark_گره;
	}
      وگرنه اگر (!noconvert)
	arg = default_conversion (arg);
      بشکن;

    حالت CONJ_عبارت:
      /* Conjugating a real value is a no-op, but allow it anyway.  */
      اگر (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE
	    || typecode == COMPLEX_TYPE))
	{
	  error_at (location, "wrong type argument to conjugation");
	  بازگشت error_mark_گره;
	}
      وگرنه اگر (!noconvert)
	arg = default_conversion (arg);
      بشکن;

    حالت TRUTH_NOT_عبارت:
      اگر (typecode != INTEGER_TYPE && typecode != FIXED_POINT_TYPE
	  && typecode != REAL_TYPE && typecode != POINTER_TYPE
	  && typecode != COMPLEX_TYPE && typecode != NULLPTR_TYPE
	  && typecode != BITINT_TYPE)
	{
	  error_at (location,
		    "wrong type argument to unary exclamation mark");
	  بازگشت error_mark_گره;
	}
      اگر (int_operands)
	{
	  arg = c_objc_common_truthvalue_conversion (location, xarg);
	  arg = remove_c_maybe_const_عبارت (arg);
	}
      وگرنه
	arg = c_objc_common_truthvalue_conversion (location, arg);
      ret = invert_truthvalue_loc (location, arg);
      eptype = NULL_درخت;
      /* If the TRUTH_NOT_EXPR has been folded, reset the location.  */
      اگر (عبارت_P (ret) && عبارت_HAS_LOCATION (ret))
	location = عبارت_LOCATION (ret);
      برو return_build_unary_op;

    حالت REALPART_عبارت:
    حالت IMAGPART_عبارت:
      ret = build_real_imag_عبارت (location, code, arg);
      اگر (ret == error_mark_گره)
	بازگشت error_mark_گره;
      اگر (eptype && درخت_CODE (eptype) == COMPLEX_TYPE)
	eptype = درخت_TYPE (eptype);
      برو return_build_unary_op;

    حالت PREINCREMENT_عبارت:
    حالت POSTINCREMENT_عبارت:
    حالت PREDECREMENT_عبارت:
    حالت POSTDECREMENT_عبارت:

      اگر (درخت_CODE (arg) == C_MAYBE_CONST_عبارت)
	{
	  درخت inner = build_unary_op (location, code,
				       C_MAYBE_CONST_عبارت_عبارت (arg),
				       noconvert);
	  اگر (inner == error_mark_گره)
	    بازگشت error_mark_گره;
	  ret = build2 (C_MAYBE_CONST_عبارت, درخت_TYPE (inner),
			C_MAYBE_CONST_عبارت_PRE (arg), inner);
	  gcc_assert (!C_MAYBE_CONST_عبارت_INT_OPERANDS (arg));
	  C_MAYBE_CONST_عبارت_NON_CONST (ret) = 1;
	  برو return_build_unary_op;
	}

      /* Complain about anything that is not a true lvalue.  In
	 Objective-C, skip this check for property_refs.  */
      اگر (!objc_is_property_ref (arg)
	  && !lvalue_or_else (location,
			      arg, ((code == PREINCREMENT_عبارت
				     || code == POSTINCREMENT_عبارت)
				    ? lv_increment
				    : lv_decrement)))
	بازگشت error_mark_گره;

      اگر (warn_cxx_compat && درخت_CODE (درخت_TYPE (arg)) == ENUMERAL_TYPE)
	{
	  اگر (code == PREINCREMENT_عبارت || code == POSTINCREMENT_عبارت)
	    warning_at (location, OPT_Wc___compat,
			"increment of enumeration value is invalid in C++");
	  وگرنه
	    warning_at (location, OPT_Wc___compat,
			"decrement of enumeration value is invalid in C++");
	}

      اگر (C_BOOLEAN_TYPE_P (درخت_TYPE (arg)))
	{
	  اگر (code == PREINCREMENT_عبارت || code == POSTINCREMENT_عبارت)
	    warning_at (location, OPT_Wbool_operation,
			"increment of a boolean expression");
	  وگرنه
	    warning_at (location, OPT_Wbool_operation,
			"decrement of a boolean expression");
	}

      /* Ensure the argument is fully folded inside any SAVE_EXPR.  */
      arg = c_fully_fold (arg, نادرست, پوچ, درست);

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
	      real = build_unary_op (عبارت_LOCATION (arg), REALPART_عبارت, arg,
				     درست);
	      imag = build_unary_op (عبارت_LOCATION (arg), IMAGPART_عبارت, arg,
				     درست);
	      real = build_unary_op (عبارت_LOCATION (arg), code, real, درست);
	      اگر (real == error_mark_گره || imag == error_mark_گره)
		بازگشت error_mark_گره;
	      ret = build2 (COMPLEX_عبارت, درخت_TYPE (arg),
			    real, imag);
	      برو return_build_unary_op;
	    }
	}

      /* Report invalid types.  */

      اگر (typecode != POINTER_TYPE && typecode != FIXED_POINT_TYPE
	  && typecode != INTEGER_TYPE && typecode != REAL_TYPE
	  && typecode != COMPLEX_TYPE && typecode != BITINT_TYPE
	  && !gnu_vector_type_p (درخت_TYPE (arg)))
	{
	  اگر (code == PREINCREMENT_عبارت || code == POSTINCREMENT_عبارت)
	    error_at (location, "wrong type argument to increment");
	  وگرنه
	    error_at (location, "wrong type argument to decrement");

	  بازگشت error_mark_گره;
	}

      {
	درخت inc;

	argtype = درخت_TYPE (arg);

	/* Compute the increment.  */

	اگر (typecode == POINTER_TYPE)
	  {
	    /* If pointer target is an incomplete type,
	       we just cannot know how to do the arithmetic.  */
	    اگر (!COMPLETE_OR_VOID_TYPE_P (درخت_TYPE (argtype)))
	      {
		اگر (code == PREINCREMENT_عبارت || code == POSTINCREMENT_عبارت)
		  error_at (location,
			    "increment of pointer to an incomplete type %qT",
			    درخت_TYPE (argtype));
		وگرنه
		  error_at (location,
			    "decrement of pointer to an incomplete type %qT",
			    درخت_TYPE (argtype));
	      }
	    وگرنه اگر (درخت_CODE (درخت_TYPE (argtype)) == FUNCTION_TYPE
		     || VOID_TYPE_P (درخت_TYPE (argtype)))
	      {
		اگر (code == PREINCREMENT_عبارت || code == POSTINCREMENT_عبارت)
		  pedwarn (location, OPT_Wpointer_arith,
			   "wrong type argument to increment");
		وگرنه
		  pedwarn (location, OPT_Wpointer_arith,
			   "wrong type argument to decrement");
	      }
	    وگرنه
	      verify_type_context (location, TCTX_POINTER_ARITH,
				   درخت_TYPE (argtype));

	    inc = c_size_in_bytes (درخت_TYPE (argtype));
	    inc = convert_to_ptrofftype_loc (location, inc);
	  }
	وگرنه اگر (FRACT_MODE_P (TYPE_MODE (argtype)))
	  {
	    /* For signed fract types, we invert ++ to -- or
	       -- to ++, and change inc from 1 to -1, because
	       it is not possible to represent 1 in signed fract constants.
	       For unsigned fract types, the result always overflows and
	       we get an undefined (original) or the maximum value.  */
	    اگر (code == PREINCREMENT_عبارت)
	      code = PREDECREMENT_عبارت;
	    وگرنه اگر (code == PREDECREMENT_عبارت)
	      code = PREINCREMENT_عبارت;
	    وگرنه اگر (code == POSTINCREMENT_عبارت)
	      code = POSTDECREMENT_عبارت;
	    وگرنه /* code == POSTDECREMENT_EXPR  */
	      code = POSTINCREMENT_عبارت;

	    inc = integer_minus_one_گره;
	    inc = convert (argtype, inc);
	  }
	وگرنه
	  {
	    inc = VECTOR_TYPE_P (argtype)
	      ? build_one_cst (argtype)
	      : integer_one_گره;
	    inc = convert (argtype, inc);
	  }

	/* If 'arg' is an Objective-C PROPERTY_REF expression, then we
	   need to ask Objective-C to build the increment or decrement
	   expression for it.  */
	اگر (objc_is_property_ref (arg))
	  بازگشت objc_build_incr_عبارت_for_property_ref (location, code,
							arg, inc);

	/* Report a read-only lvalue.  */
	اگر (TYPE_READONLY (argtype))
	  {
	    readonly_error (location, arg,
			    ((code == PREINCREMENT_عبارت
			      || code == POSTINCREMENT_عبارت)
			     ? lv_increment : lv_decrement));
	    بازگشت error_mark_گره;
	  }
	وگرنه اگر (درخت_READONLY (arg))
	  readonly_warning (arg,
			    ((code == PREINCREMENT_عبارت
			      || code == POSTINCREMENT_عبارت)
			     ? lv_increment : lv_decrement));

	/* If the argument is atomic, use the special code sequences for
	   atomic compound assignment.  */
	اگر (atomic_op)
	  {
	    arg = stabilize_reference (arg);
	    ret = build_atomic_assign (location, arg,
				       ((code == PREINCREMENT_عبارت
					 || code == POSTINCREMENT_عبارت)
					? PLUS_عبارت
					: MINUS_عبارت),
				       (FRACT_MODE_P (TYPE_MODE (argtype))
					? inc
					: integer_one_گره),
				       (code == POSTINCREMENT_عبارت
					|| code == POSTDECREMENT_عبارت));
	    برو return_build_unary_op;
	  }

	درخت true_res;
	اگر (c_hardbool_type_attr (درخت_TYPE (arg), پوچ, &true_res))
	  {
	    درخت larg = stabilize_reference (arg);
	    درخت sarg = save_عبارت (larg);
	    انتخاب (code)
	      {
	      حالت PREINCREMENT_عبارت:
		val = build2 (MODIFY_عبارت, درخت_TYPE (larg), larg, true_res);
		val = build2 (COMPOUND_عبارت, درخت_TYPE (larg), sarg, val);
		بشکن;
	      حالت POSTINCREMENT_عبارت:
		val = build2 (MODIFY_عبارت, درخت_TYPE (larg), larg, true_res);
		val = build2 (COMPOUND_عبارت, درخت_TYPE (larg), val, sarg);
		val = build2 (COMPOUND_عبارت, درخت_TYPE (larg), sarg, val);
		بشکن;
	      حالت PREDECREMENT_عبارت:
		{
		  درخت rarg = convert_lvalue_to_rvalue (location, sarg,
							درست, درست);
		  rarg = invert_truthvalue_loc (location, rarg);
		  rarg = convert (درخت_TYPE (sarg), rarg);
		  val = build2 (MODIFY_عبارت, درخت_TYPE (larg), larg, rarg);
		}
		بشکن;
	      حالت POSTDECREMENT_عبارت:
		{
		  درخت rarg = convert_lvalue_to_rvalue (location, sarg,
							درست, درست);
		  rarg = invert_truthvalue_loc (location, rarg);
		  درخت iarg = convert (درخت_TYPE (larg), rarg);
		  val = build2 (MODIFY_عبارت, درخت_TYPE (larg), larg, iarg);
		  val = build2 (COMPOUND_عبارت, درخت_TYPE (larg), val, sarg);
		  val = build2 (COMPOUND_عبارت, درخت_TYPE (larg), sarg, val);
		}
		بشکن;
	      پیشفرض:
		gcc_unreachable ();
	      }
	    درخت_SIDE_EFFECTS (val) = 1;
	  }
	وگرنه اگر (C_BOOLEAN_TYPE_P (درخت_TYPE (arg)))
	  val = boolean_increment (code, arg);
	وگرنه
	  val = build2 (code, درخت_TYPE (arg), arg, inc);
	درخت_SIDE_EFFECTS (val) = 1;
	اگر (TYPE_QUALS (درخت_TYPE (val)) != TYPE_UNQUALIFIED)
	  درخت_TYPE (val) = c_build_qualified_type (درخت_TYPE (val),
						    TYPE_UNQUALIFIED);
	ret = val;
	برو return_build_unary_op;
      }

    حالت ADDR_عبارت:
      /* Note that this operation never does default_conversion.  */

      /* The operand of unary '&' must be an lvalue (which excludes
	 expressions of type void), or, in C99, the result of a [] or
	 unary '*' operator.  */
      اگر (VOID_TYPE_P (درخت_TYPE (arg))
	  && TYPE_QUALS (درخت_TYPE (arg)) == TYPE_UNQUALIFIED
	  && (!INDIRECT_REF_P (arg) || !flag_isoc99))
	pedwarn (location, 0, "taking address of expression of type %<void%>");

      /* Let &* cancel out to simplify resulting code.  */
      اگر (INDIRECT_REF_P (arg))
	{
	  /* Don't let this be an lvalue.  */
	  اگر (lvalue_p (درخت_OPERAND (arg, 0)))
	    بازگشت non_lvalue_loc (location, درخت_OPERAND (arg, 0));
	  ret = درخت_OPERAND (arg, 0);
	  برو return_build_unary_op;
	}

      /* Anything not already handled and not a true memory reference
	 or a non-lvalue array is an error.  */
      اگر (typecode != FUNCTION_TYPE && !noconvert
	  && !lvalue_or_else (location, arg, lv_addressof))
	بازگشت error_mark_گره;

      /* Move address operations inside C_MAYBE_CONST_EXPR to simplify
	 folding later.  */
      اگر (درخت_CODE (arg) == C_MAYBE_CONST_عبارت)
	{
	  درخت inner = build_unary_op (location, code,
				       C_MAYBE_CONST_عبارت_عبارت (arg),
				       noconvert);
	  ret = build2 (C_MAYBE_CONST_عبارت, درخت_TYPE (inner),
			C_MAYBE_CONST_عبارت_PRE (arg), inner);
	  gcc_assert (!C_MAYBE_CONST_عبارت_INT_OPERANDS (arg));
	  C_MAYBE_CONST_عبارت_NON_CONST (ret)
	    = C_MAYBE_CONST_عبارت_NON_CONST (arg);
	  برو return_build_unary_op;
	}

      /* Ordinary case; arg is a COMPONENT_REF or a decl.  */

      argtype = درخت_TYPE (arg);

      /* If the lvalue is const or volatile, merge that into the type
	 to which the address will point.  This is only needed
	 for function types.  */
      اگر ((DECL_P (arg) || REFERENCE_CLASS_P (arg))
	  && (درخت_READONLY (arg) || درخت_THIS_VOLATILE (arg))
	  && درخت_CODE (argtype) == FUNCTION_TYPE)
	{
	  صحیح orig_quals = TYPE_QUALS (strip_array_types (argtype));
	  صحیح quals = orig_quals;

	  اگر (درخت_READONLY (arg))
	    quals |= TYPE_QUAL_CONST;
	  اگر (درخت_THIS_VOLATILE (arg))
	    quals |= TYPE_QUAL_VOLATILE;

	  argtype = c_build_qualified_type (argtype, quals);
	}

      انتخاب (درخت_CODE (arg))
	{
	حالت COMPONENT_REF:
	  اگر (DECL_C_BIT_FIELD (درخت_OPERAND (arg, 1)))
	    {
	      error_at (location, "cannot take address of bit-field %qD",
			درخت_OPERAND (arg, 1));
	      بازگشت error_mark_گره;
	    }

	  /* fall through */

	حالت ARRAY_REF:
	  اگر (TYPE_REVERSE_STORAGE_ORDER (درخت_TYPE (درخت_OPERAND (arg, 0))))
	    {
	      اگر (!AGGREGATE_TYPE_P (درخت_TYPE (arg))
		  && !POINTER_TYPE_P (درخت_TYPE (arg))
		  && !VECTOR_TYPE_P (درخت_TYPE (arg)))
		{
		  error_at (location, "cannot take address of scalar with "
			    "reverse storage order");
		  بازگشت error_mark_گره;
		}

	      اگر (درخت_CODE (درخت_TYPE (arg)) == ARRAY_TYPE
		  && TYPE_REVERSE_STORAGE_ORDER (درخت_TYPE (arg)))
		warning_at (location, OPT_Wscalar_storage_order,
			    "address of array with reverse scalar storage "
			    "order requested");
	    }

	پیشفرض:
	  بشکن;
	}

      اگر (!c_mark_addressable (arg))
	بازگشت error_mark_گره;

      gcc_assert (درخت_CODE (arg) != COMPONENT_REF
		  || !DECL_C_BIT_FIELD (درخت_OPERAND (arg, 1)));

      argtype = c_build_pointer_type (argtype);

      /* ??? Cope with user tricks that amount to offsetof.  Delete this
	 when we have proper support for integer constant expressions.  */
      val = get_base_address (arg);
      اگر (val && INDIRECT_REF_P (val)
          && درخت_CONSTANT (درخت_OPERAND (val, 0)))
	{
	  ret = fold_offsetof (arg, argtype);
	  برو return_build_unary_op;
	}

      val = build1 (ADDR_عبارت, argtype, arg);

      ret = val;
      برو return_build_unary_op;

    حالت PAREN_عبارت:
      ret = build1 (code, درخت_TYPE (arg), arg);
      برو return_build_unary_op;

    پیشفرض:
      gcc_unreachable ();
    }

  اگر (argtype == NULL_درخت)
    argtype = درخت_TYPE (arg);
  اگر (درخت_CODE (arg) == INTEGER_CST)
    ret = (require_constant_مقدار
	   ? fold_build1_initializer_loc (location, code, argtype, arg)
	   : fold_build1_loc (location, code, argtype, arg));
  وگرنه
    ret = build1 (code, argtype, arg);
 return_build_unary_op:
  gcc_assert (ret != error_mark_گره);
  اگر (درخت_CODE (ret) == INTEGER_CST && !درخت_OVERFLOW (ret)
      && !(درخت_CODE (xarg) == INTEGER_CST && !درخت_OVERFLOW (xarg)))
    ret = build1 (NOP_عبارت, درخت_TYPE (ret), ret);
  وگرنه اگر (درخت_CODE (ret) != INTEGER_CST && int_operands)
    ret = note_integer_operands (ret);
  اگر (eptype)
    ret = build1 (EXCESS_PRECISION_عبارت, eptype, ret);
  protected_set_عبارت_location (ret, location);
  بازگشت ret;
}

/* Return nonzero if REF is an lvalue valid for this language.
   Lvalues can be assigned, unless their type has TYPE_READONLY.
   Lvalues can have their address taken, unless they have C_DECL_REGISTER.  */

منطقی
lvalue_p (const_درخت ref)
{
  ثابت شمارش درخت_code code = درخت_CODE (ref);

  انتخاب (code)
    {
    حالت REALPART_عبارت:
    حالت IMAGPART_عبارت:
    حالت COMPONENT_REF:
      بازگشت lvalue_p (درخت_OPERAND (ref, 0));

    حالت C_MAYBE_CONST_عبارت:
      بازگشت lvalue_p (درخت_OPERAND (ref, 1));

    حالت COMPOUND_LITERAL_عبارت:
    حالت STRING_CST:
      بازگشت درست;

    حالت MEM_REF:
    حالت TARGET_MEM_REF:
      /* MEM_REFs can appear from -fgimple parsing or folding, so allow them
	 here as well.  */
    حالت INDIRECT_REF:
    حالت ARRAY_REF:
    حالت VAR_DECL:
    حالت PARM_DECL:
    حالت RESULT_DECL:
    حالت ERROR_MARK:
      بازگشت (درخت_CODE (درخت_TYPE (ref)) != FUNCTION_TYPE
	      && درخت_CODE (درخت_TYPE (ref)) != METHOD_TYPE);

    حالت BIND_عبارت:
      بازگشت درخت_CODE (درخت_TYPE (ref)) == ARRAY_TYPE;

    حالت CALL_عبارت:
      بازگشت is_access_with_size_p (ref);

    پیشفرض:
      بازگشت نادرست;
    }
}

/* Give a warning for storing in something that is read-only in GCC
   terms but not const in ISO C terms.  */

ایستا تهی
readonly_warning (درخت arg, شمارش lvalue_use use)
{
  انتخاب (use)
    {
    حالت lv_assign:
      warning (0, "assignment of read-only location %qE", arg);
      بشکن;
    حالت lv_increment:
      warning (0, "increment of read-only location %qE", arg);
      بشکن;
    حالت lv_decrement:
      warning (0, "decrement of read-only location %qE", arg);
      بشکن;
    پیشفرض:
      gcc_unreachable ();
    }
  بازگشت;
}


/* Return nonzero if REF is an lvalue valid for this language;
   otherwise, print an error message and return zero.  USE says
   how the lvalue is being used and so selects the error message.
   LOCATION is the location at which any error should be reported.  */

ایستا صحیح
lvalue_or_else (location_t loc, const_درخت ref, شمارش lvalue_use use)
{
  صحیح win = lvalue_p (ref);

  اگر (!win)
    lvalue_error (loc, use);

  بازگشت win;
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
c_mark_addressable (درخت exp, منطقی array_ref_p, منطقی override_register)
{
  درخت x = exp;

  وقتی (1)
    انتخاب (درخت_CODE (x))
      {
      حالت VIEW_CONVERT_عبارت:
	اگر (array_ref_p
	    && درخت_CODE (درخت_TYPE (x)) == ARRAY_TYPE
	    && VECTOR_TYPE_P (درخت_TYPE (درخت_OPERAND (x, 0))))
	  بازگشت درست;
	x = درخت_OPERAND (x, 0);
	بشکن;

      حالت COMPONENT_REF:
	اگر (DECL_C_BIT_FIELD (درخت_OPERAND (x, 1)))
	  {
	    error ("cannot take address of bit-field %qD",
		   درخت_OPERAND (x, 1));
	    بازگشت نادرست;
	  }
	/* FALLTHRU */
      حالت ADDR_عبارت:
      حالت ARRAY_REF:
      حالت REALPART_عبارت:
      حالت IMAGPART_عبارت:
	x = درخت_OPERAND (x, 0);
	بشکن;

      حالت COMPOUND_LITERAL_عبارت:
	اگر (C_DECL_REGISTER (COMPOUND_LITERAL_عبارت_DECL (x)))
	  {
	    اگر (override_register)
	      DECL_REGISTER (COMPOUND_LITERAL_عبارت_DECL (x)) = 0;
	    وگرنه
	      {
		error ("address of register compound literal requested");
		بازگشت نادرست;
	      }
	  }
	درخت_ADDRESSABLE (x) = 1;
	درخت_ADDRESSABLE (COMPOUND_LITERAL_عبارت_DECL (x)) = 1;
	بازگشت درست;

      حالت CONSTRUCTOR:
	درخت_ADDRESSABLE (x) = 1;
	بازگشت درست;

      حالت VAR_DECL:
      حالت CONST_DECL:
      حالت PARM_DECL:
      حالت RESULT_DECL:
	اگر (C_DECL_REGISTER (x)
	    && DECL_NONLOCAL (x))
	  {
	    اگر (درخت_PUBLIC (x) || is_global_var (x))
	      {
		error
		  ("global register variable %qD used in nested function", x);
		بازگشت نادرست;
	      }
	    pedwarn (درون_داد_location, 0, "register variable %qD used in nested function", x);
	  }
	وگرنه اگر (C_DECL_REGISTER (x))
	  {
	    اگر (درخت_PUBLIC (x) || is_global_var (x))
	      error ("address of global register variable %qD requested", x);
	    وگرنه اگر (override_register && !DECL_HARD_REGISTER (x))
	      {
		DECL_REGISTER (x) = 0;
		درخت_ADDRESSABLE (x) = 1;
		mark_decl_used (x, درست);
		بازگشت درست;
	      }
	    وگرنه
	      error ("address of register variable %qD requested", x);
	    بازگشت نادرست;
	  }

	/* FALLTHRU */
      حالت FUNCTION_DECL:
	درخت_ADDRESSABLE (x) = 1;
	mark_decl_used (x, درست);
	/* FALLTHRU */
      پیشفرض:
	بازگشت درست;
    }
}

/* Convert EXPR to TYPE, warning about conversion problems with
   constants.  SEMANTIC_TYPE is the type this conversion would use
   without excess precision. If SEMANTIC_TYPE is NULL, this function
   is equivalent to convert_and_check. This function is a wrapper that
   handles conversions that may be different than
   the usual ones because of excess precision.  */

ایستا درخت
ep_convert_and_check (location_t loc, درخت type, درخت عبارت,
		      درخت semantic_type)
{
  اگر (درخت_TYPE (عبارت) == type)
    بازگشت عبارت;

  /* For C11, integer conversions may have results with excess
     precision.  */
  اگر (flag_isoc11 || !semantic_type)
    بازگشت convert_and_check (loc, type, عبارت);

  اگر (درخت_CODE (درخت_TYPE (عبارت)) == INTEGER_TYPE
      && درخت_TYPE (عبارت) != semantic_type)
    {
      /* For integers, we need to check the real conversion, not
	 the conversion to the excess precision type.  */
      عبارت = convert_and_check (loc, semantic_type, عبارت);
    }
  /* Result type is the excess precision type, which should be
     large enough, so do not check.  */
  بازگشت convert (type, عبارت);
}

/* If EXPR refers to a built-in declared without a prototype returns
   the actual type of the built-in and, if non-null, set *BLTIN to
   a pointer to the built-in.  Otherwise return the type of EXPR
   and clear *BLTIN if non-null.  */

ایستا درخت
type_or_builtin_type (درخت عبارت, درخت *bltin = پوچ)
{
  درخت dummy;
  اگر (!bltin)
    bltin = &dummy;

  *bltin = NULL_درخت;

  درخت type = درخت_TYPE (عبارت);
  اگر (درخت_CODE (عبارت) != ADDR_عبارت)
    بازگشت type;

  درخت oper = درخت_OPERAND (عبارت, 0);
  اگر (!DECL_P (oper)
      || درخت_CODE (oper) != FUNCTION_DECL
      || !fndecl_built_in_p (oper, BUILT_IN_NORMAL))
    بازگشت type;

  built_in_function code = DECL_FUNCTION_CODE (oper);
  اگر (!C_DECL_BUILTIN_PROTOTYPE (oper))
    بازگشت type;

  اگر ((*bltin = builtin_decl_implicit (code)))
    type = c_build_pointer_type (درخت_TYPE (*bltin));

  بازگشت type;
}

/* Build and return a conditional expression IFEXP ? OP1 : OP2.  If
   IFEXP_BCP then the condition is a call to __builtin_constant_p, and
   if folded to an integer constant then the unselected half may
   contain arbitrary operations not normally permitted in constant
   expressions.  Set the location of the expression to LOC.  */

درخت
build_conditional_عبارت (location_t colon_loc, درخت ifexp, منطقی ifexp_bcp,
			درخت op1, درخت op1_original_type, location_t op1_loc,
			درخت op2, درخت op2_original_type, location_t op2_loc)
{
  درخت type1;
  درخت type2;
  درخت result_type = پوچ;
  درخت semantic_result_type = پوچ;
  درخت orig_op1 = op1, orig_op2 = op2;
  منطقی int_const, op1_int_operands, op2_int_operands, int_operands;
  منطقی ifexp_int_operands;
  درخت ret;

  op1_int_operands = عبارت_INT_CONST_OPERANDS (orig_op1);
  اگر (op1_int_operands)
    op1 = remove_c_maybe_const_عبارت (op1);
  op2_int_operands = عبارت_INT_CONST_OPERANDS (orig_op2);
  اگر (op2_int_operands)
    op2 = remove_c_maybe_const_عبارت (op2);
  ifexp_int_operands = عبارت_INT_CONST_OPERANDS (ifexp);
  اگر (ifexp_int_operands)
    ifexp = remove_c_maybe_const_عبارت (ifexp);

  /* Promote both alternatives.  */

  اگر (درخت_CODE (درخت_TYPE (op1)) != VOID_TYPE)
    op1 = default_conversion (op1);
  اگر (درخت_CODE (درخت_TYPE (op2)) != VOID_TYPE)
    op2 = default_conversion (op2);

  اگر (درخت_CODE (ifexp) == ERROR_MARK
      || درخت_CODE (درخت_TYPE (op1)) == ERROR_MARK
      || درخت_CODE (درخت_TYPE (op2)) == ERROR_MARK)
    بازگشت error_mark_گره;

  درخت bltin1 = NULL_درخت;
  درخت bltin2 = NULL_درخت;
  type1 = type_or_builtin_type (op1, &bltin1);
  ثابت شمارش درخت_code code1 = درخت_CODE (type1);
  type2 = type_or_builtin_type (op2, &bltin2);
  ثابت شمارش درخت_code code2 = درخت_CODE (type2);

  اگر (code1 == POINTER_TYPE && reject_gcc_builtin (op1))
    بازگشت error_mark_گره;

  اگر (code2 == POINTER_TYPE && reject_gcc_builtin (op2))
    بازگشت error_mark_گره;

  /* C90 does not permit non-lvalue arrays in conditional expressions.
     In C99 they will be pointers by now.  */
  اگر (code1 == ARRAY_TYPE || code2 == ARRAY_TYPE)
    {
      error_at (colon_loc, "non-lvalue array in conditional expression");
      بازگشت error_mark_گره;
    }

  اگر ((درخت_CODE (op1) == EXCESS_PRECISION_عبارت
       || درخت_CODE (op2) == EXCESS_PRECISION_عبارت)
      && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	  || code1 == COMPLEX_TYPE || code1 == BITINT_TYPE)
      && (code2 == INTEGER_TYPE || code2 == REAL_TYPE
	  || code2 == COMPLEX_TYPE || code2 == BITINT_TYPE))
    {
      semantic_result_type = c_common_type (type1, type2);
      اگر (درخت_CODE (op1) == EXCESS_PRECISION_عبارت)
	{
	  op1 = درخت_OPERAND (op1, 0);
	  type1 = درخت_TYPE (op1);
	  gcc_assert (درخت_CODE (type1) == code1);
	}
      اگر (درخت_CODE (op2) == EXCESS_PRECISION_عبارت)
	{
	  op2 = درخت_OPERAND (op2, 0);
	  type2 = درخت_TYPE (op2);
	  gcc_assert (درخت_CODE (type2) == code2);
	}
    }

  اگر (warn_cxx_compat)
    {
      درخت t1 = op1_original_type ? op1_original_type : درخت_TYPE (orig_op1);
      درخت t2 = op2_original_type ? op2_original_type : درخت_TYPE (orig_op2);

      اگر (درخت_CODE (t1) == ENUMERAL_TYPE
	  && درخت_CODE (t2) == ENUMERAL_TYPE
	  && TYPE_MAIN_VARIANT (t1) != TYPE_MAIN_VARIANT (t2))
	warning_at (colon_loc, OPT_Wc___compat,
		    "different enum types in conditional is "
		    "invalid in C++: %qT vs %qT", t1, t2);
    }

  اگر (warn_zero_as_null_pointer_constant
      && c_inhibit_evaluation_warnings == 0)
    {
      اگر ((code1 == POINTER_TYPE || code1 == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type2) && null_pointer_constant_p (orig_op2))
	warning_at (op2_loc, OPT_Wzero_as_null_pointer_constant,
		    "zero as null pointer constant");

      اگر ((code2 == POINTER_TYPE || code2 == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type1) && null_pointer_constant_p (orig_op1))
	warning_at (op1_loc, OPT_Wzero_as_null_pointer_constant,
		    "zero as null pointer constant");
    }

  /* Quickly detect the usual case where op1 and op2 have the same type
     after promotion.  */
  اگر (TYPE_MAIN_VARIANT (type1) == TYPE_MAIN_VARIANT (type2))
    {
      اگر (type1 == type2)
	result_type = type1;
      وگرنه
	result_type = TYPE_MAIN_VARIANT (type1);
    }
  وگرنه اگر ((code1 == INTEGER_TYPE || code1 == REAL_TYPE
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
	      اگر (!semantic_result_type)
		semantic_result_type = c_common_type (type1, type2);
	    }
	  وگرنه اگر (ANY_INTEGRAL_TYPE_P (type2)
		   && (eptype = excess_precision_type (type1)) != NULL_درخت)
	    {
	      eptype1 = eptype;
	      اگر (!semantic_result_type)
		semantic_result_type = c_common_type (type1, type2);
	    }
	}
      result_type = c_common_type (eptype1, eptype2);
      اگر (result_type == error_mark_گره)
	بازگشت error_mark_گره;
      do_warn_double_promotion (result_type, type1, type2,
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
	      اگر (!TYPE_UNSIGNED (result_type))
		/* OK */;
	      وگرنه
		{
		  منطقی op1_maybe_const = درست;
		  منطقی op2_maybe_const = درست;

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

		  اگر (warn_sign_compare)
		    {
		      اگر ((unsigned_op2
			   && درخت_عبارت_nonnegative_p (op1))
			  || (unsigned_op1
			      && درخت_عبارت_nonnegative_p (op2)))
			/* OK */;
		      وگرنه اگر (unsigned_op2)
			warning_at (op1_loc, OPT_Wsign_compare,
				    "operand of %<?:%> changes signedness from "
				    "%qT to %qT due to unsignedness of other "
				    "operand", درخت_TYPE (orig_op1),
				    درخت_TYPE (orig_op2));
		      وگرنه
			warning_at (op2_loc, OPT_Wsign_compare,
				    "operand of %<?:%> changes signedness from "
				    "%qT to %qT due to unsignedness of other "
				    "operand", درخت_TYPE (orig_op2),
				    درخت_TYPE (orig_op1));
		    }
		  اگر (!op1_maybe_const || درخت_CODE (op1) != INTEGER_CST)
		    op1 = c_wrap_maybe_const (op1, !op1_maybe_const);
		  اگر (!op2_maybe_const || درخت_CODE (op2) != INTEGER_CST)
		    op2 = c_wrap_maybe_const (op2, !op2_maybe_const);
		}
	    }
	}
    }
  وگرنه اگر (code1 == VOID_TYPE || code2 == VOID_TYPE)
    {
      اگر (code1 != VOID_TYPE || code2 != VOID_TYPE)
	pedwarn (colon_loc, OPT_Wpedantic,
		 "ISO C forbids conditional expr with only one void side");
      result_type = void_type_گره;
    }
  وگرنه اگر (code1 == POINTER_TYPE && code2 == POINTER_TYPE)
    {
      addr_space_t as1 = TYPE_ADDR_SPACE (درخت_TYPE (type1));
      addr_space_t as2 = TYPE_ADDR_SPACE (درخت_TYPE (type2));
      addr_space_t as_common;

      اگر (comp_target_types (colon_loc, type1, type2))
	{
	  ifexp = save_عبارت (ifexp);
	  result_type = common_pointer_type (type1, type2, ifexp);
	}
      وگرنه اگر (null_pointer_constant_p (orig_op1))
	result_type = type2;
      وگرنه اگر (null_pointer_constant_p (orig_op2))
	result_type = type1;
      وگرنه اگر (!addr_space_superset (as1, as2, &as_common))
	{
	  error_at (colon_loc, "pointers to disjoint address spaces "
		    "used in conditional expression");
	  بازگشت error_mark_گره;
	}
      وگرنه اگر ((VOID_TYPE_P (درخت_TYPE (type1))
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
	  اگر ((درخت_CODE (t2) == ARRAY_TYPE)
	      && (TYPE_QUALS (t2_stripped) & ~TYPE_QUALS (t1)))
	    {
	      اگر (!flag_isoc23)
		warning_at (colon_loc, OPT_Wdiscarded_array_qualifiers,
			    "pointer to array loses qualifier "
			    "in conditional expression");
	      وگرنه اگر (warn_c11_c23_compat > 0)
		warning_at (colon_loc, OPT_Wc11_c23_compat,
			    "pointer to array loses qualifier "
			    "in conditional expression in ISO C before C23");
	    }
	  اگر (درخت_CODE (t2) == FUNCTION_TYPE)
	    pedwarn (colon_loc, OPT_Wpedantic,
		     "ISO C forbids conditional expr between "
		     "%<void *%> and function pointer");
	  /* for array, use qualifiers of element type */
	  اگر (flag_isoc23)
	    t2 = t2_stripped;
	  result_type = c_build_pointer_type (qualify_type (t1, t2));
	}
      /* Objective-C pointer comparisons are a bit more lenient.  */
      وگرنه اگر (objc_have_common_type (type1, type2, -3, NULL_درخت))
	result_type = objc_common_type (type1, type2);
      وگرنه
	{
	  صحیح qual = ENCODE_QUAL_ADDR_SPACE (as_common);
	  شمارش diagnostics::kind kind = diagnostics::kind::permerror;
	  اگر (!flag_isoc99)
	    /* This downgrade to a warning ensures that -std=gnu89
	       -pedantic-errors does not flag these mismatches between
	       builtins as errors (as diagnostics::kind::permerror would)
	       ISO C99 and later do not have implicit function declarations,
	       so the mismatch cannot occur naturally there.  */
	    kind = (bltin1 && bltin2
		    ? diagnostics::kind::warning
		    : diagnostics::kind::pedwarn);
	  اگر (emit_diagnostic (kind, colon_loc, OPT_Wincompatible_pointer_types,
			       "pointer type mismatch "
			       "in conditional expression"))
	    {
	      inform (op1_loc, "first expression has type %qT", type1);
	      inform (op2_loc, "second expression has type %qT", type2);
	    }
	  result_type = c_build_pointer_type
			  (c_build_qualified_type (void_type_گره, qual));
	}
    }
  وگرنه اگر (code1 == POINTER_TYPE
	   && (code2 == INTEGER_TYPE || code2 == BITINT_TYPE))
    {
      اگر (!null_pointer_constant_p (orig_op2))
	permerror_opt (colon_loc, OPT_Wint_conversion,
		       "pointer/integer type mismatch "
		       "in conditional expression");
      وگرنه
	{
	  op2 = null_pointer_گره;
	}
      result_type = type1;
    }
  وگرنه اگر (code2 == POINTER_TYPE
	   && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
    {
      اگر (!null_pointer_constant_p (orig_op1))
	permerror_opt (colon_loc, OPT_Wint_conversion,
		       "pointer/integer type mismatch "
		       "in conditional expression");
      وگرنه
	{
	  op1 = null_pointer_گره;
	}
      result_type = type2;
    }
  /* 6.5.15: "if one is a null pointer constant (other than a pointer) or has
     type nullptr_t and the other is a pointer, the result type is the pointer
     type."  */
  وگرنه اگر (code1 == NULLPTR_TYPE && code2 == POINTER_TYPE)
    result_type = type2;
  وگرنه اگر (code1 == POINTER_TYPE && code2 == NULLPTR_TYPE)
    result_type = type1;
  وگرنه اگر (RECORD_OR_UNION_TYPE_P (type1) && RECORD_OR_UNION_TYPE_P (type2)
	   && comptypes (TYPE_MAIN_VARIANT (type1),
			 TYPE_MAIN_VARIANT (type2)))
    result_type = composite_type (TYPE_MAIN_VARIANT (type1),
				  TYPE_MAIN_VARIANT (type2));

  اگر (!result_type)
    {
      اگر (flag_cond_mismatch)
	result_type = void_type_گره;
      وگرنه
	{
	  error_at (colon_loc, "type mismatch in conditional expression");
	  بازگشت error_mark_گره;
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

  اگر (ifexp_bcp && ifexp == truthvalue_true_گره)
    {
      op2_int_operands = درست;
      op1 = c_fully_fold (op1, require_constant_مقدار, پوچ);
    }
  اگر (ifexp_bcp && ifexp == truthvalue_false_گره)
    {
      op1_int_operands = درست;
      op2 = c_fully_fold (op2, require_constant_مقدار, پوچ);
    }
  int_const = int_operands = (ifexp_int_operands
			      && op1_int_operands
			      && op2_int_operands);
  اگر (int_operands)
    {
      int_const = ((ifexp == truthvalue_true_گره
		    && درخت_CODE (orig_op1) == INTEGER_CST
		    && !درخت_OVERFLOW (orig_op1))
		   || (ifexp == truthvalue_false_گره
		       && درخت_CODE (orig_op2) == INTEGER_CST
		       && !درخت_OVERFLOW (orig_op2)));
    }

  /* Need to convert condition operand into a vector mask.  */
  اگر (VECTOR_TYPE_P (درخت_TYPE (ifexp)))
    {
      درخت vectype = درخت_TYPE (ifexp);
      درخت elem_type = درخت_TYPE (vectype);
      درخت zero = build_int_cst (elem_type, 0);
      درخت zero_vec = build_vector_from_val (vectype, zero);
      درخت cmp_type = truth_type_for (vectype);
      ifexp = build2 (NE_عبارت, cmp_type, ifexp, zero_vec);
    }

  اگر (int_const || (ifexp_bcp && درخت_CODE (ifexp) == INTEGER_CST))
    ret = fold_build3_loc (colon_loc, COND_عبارت, result_type, ifexp, op1, op2);
  وگرنه
    {
      اگر (int_operands)
	{
	  /* Use c_fully_fold here, since C_MAYBE_CONST_EXPR might be
	     nested inside of the expression.  */
	  op1 = c_fully_fold (op1, نادرست, پوچ);
	  op2 = c_fully_fold (op2, نادرست, پوچ);
	}
      ret = build3 (COND_عبارت, result_type, ifexp, op1, op2);
      اگر (int_operands)
	ret = note_integer_operands (ret);
    }
  اگر (semantic_result_type)
    ret = build1 (EXCESS_PRECISION_عبارت, semantic_result_type, ret);

  protected_set_عبارت_location (ret, colon_loc);

  /* If the OP1 and OP2 are the same and don't have side-effects,
     warn here, because the COND_EXPR will be turned into OP1.  */
  اگر (warn_duplicated_branches
      && درخت_CODE (ret) == COND_عبارت
      && (op1 == op2 || operand_equal_p (op1, op2, OEP_ADDRESS_OF_SAME_FIELD)))
    warning_at (عبارت_LOCATION (ret), OPT_Wduplicated_branches,
		"this condition has identical branches");

  بازگشت ret;
}

/* EXPR is an expression, location LOC, whose result is discarded.
   Warn if it is a call to a nodiscard function (or a COMPOUND_EXPR
   whose right-hand operand is such a call, possibly recursively).  */

ایستا تهی
maybe_warn_nodiscard (location_t loc, درخت عبارت)
{
  اگر (VOID_TYPE_P (درخت_TYPE (عبارت)))
    بازگشت;
  وقتی (درخت_CODE (عبارت) == COMPOUND_عبارت)
    {
      عبارت = درخت_OPERAND (عبارت, 1);
      اگر (عبارت_HAS_LOCATION (عبارت))
	loc = عبارت_LOCATION (عبارت);
    }
  اگر (درخت_CODE (عبارت) != CALL_عبارت)
    بازگشت;
  درخت fn = CALL_عبارت_FN (عبارت);
  اگر (!fn)
    بازگشت;
  درخت attr;
  اگر (درخت_CODE (fn) == ADDR_عبارت
      && درخت_CODE (درخت_OPERAND (fn, 0)) == FUNCTION_DECL
      && (attr = lookup_attribute ("nodiscard",
				   DECL_ATTRIBUTES (درخت_OPERAND (fn, 0)))))
    {
      fn = درخت_OPERAND (fn, 0);
      درخت args = درخت_مقدار (attr);
      اگر (args)
	args = درخت_مقدار (args);
      auto_diagnostic_group d;
      auto_urlify_attributes sentinel;
      صحیح warned;
      اگر (args)
	warned = warning_at (loc, OPT_Wunused_result,
			     "ignoring return value of %qD, declared with "
			     "attribute %<nodiscard%>: %E", fn, args);
      وگرنه
	warned = warning_at (loc, OPT_Wunused_result,
			     "ignoring return value of %qD, declared with "
			     "attribute %<nodiscard%>", fn);
      اگر (warned)
	inform (DECL_SOURCE_LOCATION (fn), "declared here");
    }
  وگرنه
    {
      درخت rettype = درخت_TYPE (درخت_TYPE (درخت_TYPE (fn)));
      attr = lookup_attribute ("nodiscard", TYPE_ATTRIBUTES (rettype));
      اگر (!attr)
	بازگشت;
      درخت args = درخت_مقدار (attr);
      اگر (args)
	args = درخت_مقدار (args);
      auto_diagnostic_group d;
      auto_urlify_attributes sentinel;
      صحیح warned;
      اگر (args)
	warned = warning_at (loc, OPT_Wunused_result,
			     "ignoring return value of type %qT, declared "
			     "with attribute %<nodiscard%>: %E",
			     rettype, args);
      وگرنه
	warned = warning_at (loc, OPT_Wunused_result,
			     "ignoring return value of type %qT, declared "
			     "with attribute %<nodiscard%>", rettype);
      اگر (warned)
	{
	  اگر (درخت_CODE (fn) == ADDR_عبارت)
	    {
	      fn = درخت_OPERAND (fn, 0);
	      اگر (درخت_CODE (fn) == FUNCTION_DECL)
		inform (DECL_SOURCE_LOCATION (fn),
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
  منطقی expr1_int_operands, expr2_int_operands;
  درخت eptype = NULL_درخت;
  درخت ret;

  expr1_int_operands = عبارت_INT_CONST_OPERANDS (expr1);
  اگر (expr1_int_operands)
    expr1 = remove_c_maybe_const_عبارت (expr1);
  expr2_int_operands = عبارت_INT_CONST_OPERANDS (expr2);
  اگر (expr2_int_operands)
    expr2 = remove_c_maybe_const_عبارت (expr2);

  اگر (درخت_CODE (expr1) == EXCESS_PRECISION_عبارت)
    expr1 = درخت_OPERAND (expr1, 0);
  اگر (درخت_CODE (expr2) == EXCESS_PRECISION_عبارت)
    {
      eptype = درخت_TYPE (expr2);
      expr2 = درخت_OPERAND (expr2, 0);
    }

  اگر (!درخت_SIDE_EFFECTS (expr1))
    {
      /* The left-hand operand of a comma expression is like an expression
	 statement: with -Wunused, we should warn if it doesn't have
	 any side-effects, unless it was explicitly cast to (void).  */
      اگر (warn_unused_مقدار)
	{
	  اگر (VOID_TYPE_P (درخت_TYPE (expr1))
	      && CONVERT_عبارت_P (expr1))
	    ; /* (void) a, b */
	  وگرنه اگر (VOID_TYPE_P (درخت_TYPE (expr1))
		   && درخت_CODE (expr1) == COMPOUND_عبارت
		   && CONVERT_عبارت_P (درخت_OPERAND (expr1, 1)))
	    ; /* (void) a, (void) b, c */
	  وگرنه
	    warning_at (loc, OPT_Wunused_مقدار,
			"left-hand operand of comma expression has no effect");
	}
    }
  وگرنه اگر (درخت_CODE (expr1) == COMPOUND_عبارت
	   && warn_unused_مقدار)
    {
      درخت r = expr1;
      location_t cloc = loc;
      وقتی (درخت_CODE (r) == COMPOUND_عبارت)
        {
	  اگر (عبارت_HAS_LOCATION (r))
	    cloc = عبارت_LOCATION (r);
	  r = درخت_OPERAND (r, 1);
	}
      اگر (!درخت_SIDE_EFFECTS (r)
	  && !VOID_TYPE_P (درخت_TYPE (r))
	  && !CONVERT_عبارت_P (r))
	warning_at (cloc, OPT_Wunused_مقدار,
	            "right-hand operand of comma expression has no effect");
    }

  /* With -Wunused, we should also warn if the left-hand operand does have
     side-effects, but computes a value which is not used.  For example, in
     `foo() + bar(), baz()' the result of the `+' operator is not used,
     so we should issue a warning.  */
  وگرنه اگر (warn_unused_مقدار)
    warn_if_unused_مقدار (expr1, loc);

  maybe_warn_nodiscard (loc, expr1);

  اگر (expr2 == error_mark_گره)
    بازگشت error_mark_گره;

  ret = build2 (COMPOUND_عبارت, درخت_TYPE (expr2), expr1, expr2);

  اگر (flag_isoc99
      && expr1_int_operands
      && expr2_int_operands)
    ret = note_integer_operands (ret);

  اگر (eptype)
    ret = build1 (EXCESS_PRECISION_عبارت, eptype, ret);

  protected_set_عبارت_location (ret, loc);
  بازگشت ret;
}

/* Issue -Wcast-qual warnings when appropriate.  TYPE is the type to
   which we are casting.  OTYPE is the type of the expression being
   cast.  Both TYPE and OTYPE are pointer types.  LOC is the location
   of the cast.  -Wcast-qual appeared on the command line.  Named
   address space qualifiers are not handled here, because they result
   in different warnings.  */

ایستا تهی
handle_warn_cast_qual (location_t loc, درخت type, درخت otype)
{
  درخت in_type = type;
  درخت in_otype = otype;
  صحیح added = 0;
  صحیح discarded = 0;
  منطقی is_const;

  /* Check that the qualifiers on IN_TYPE are a superset of the
     qualifiers of IN_OTYPE.  The outermost level of POINTER_TYPE
     nodes is uninteresting and we stop as soon as we hit a
     non-POINTER_TYPE node on either type.  */
  انجامبده
    {
      in_otype = درخت_TYPE (in_otype);
      in_type = درخت_TYPE (in_type);

      /* GNU C allows cv-qualified function types.  'const' means the
	 function is very pure, 'volatile' means it can't return.  We
	 need to warn when such qualifiers are added, not when they're
	 taken away.  */
      اگر (درخت_CODE (in_otype) == FUNCTION_TYPE
	  && درخت_CODE (in_type) == FUNCTION_TYPE)
	added |= (TYPE_QUALS_NO_ADDR_SPACE (in_type)
		  & ~TYPE_QUALS_NO_ADDR_SPACE (in_otype));
      وگرنه
	discarded |= (TYPE_QUALS_NO_ADDR_SPACE (in_otype)
		      & ~TYPE_QUALS_NO_ADDR_SPACE (in_type));
    }
  وقتی (درخت_CODE (in_type) == POINTER_TYPE
	 && درخت_CODE (in_otype) == POINTER_TYPE);

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
    بازگشت;

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

  اگر (TYPE_MAIN_VARIANT (in_type) != TYPE_MAIN_VARIANT (in_otype))
    بازگشت;
  اگر (درخت_CODE (درخت_TYPE (type)) != POINTER_TYPE)
    بازگشت;

  in_type = type;
  in_otype = otype;
  is_const = TYPE_READONLY (درخت_TYPE (in_type));
  انجامبده
    {
      in_type = درخت_TYPE (in_type);
      in_otype = درخت_TYPE (in_otype);
      اگر ((TYPE_QUALS (in_type) &~ TYPE_QUALS (in_otype)) != 0
	  && !is_const)
	{
	  warning_at (loc, OPT_Wcast_qual,
		      "to be safe all intermediate pointers in cast from "
                      "%qT to %qT must be %<const%> qualified",
		      otype, type);
	  بشکن;
	}
      اگر (is_const)
	is_const = TYPE_READONLY (in_type);
    }
  وقتی (درخت_CODE (in_type) == POINTER_TYPE);
}

/* Heuristic check if two parameter types can be considered ABI-equivalent.  */

ایستا منطقی
c_safe_arg_type_equiv_p (درخت t1, درخت t2)
{
  اگر (error_operand_p (t1) || error_operand_p (t2))
    بازگشت درست;

  t1 = TYPE_MAIN_VARIANT (t1);
  t2 = TYPE_MAIN_VARIANT (t2);

  اگر (درخت_CODE (t1) == POINTER_TYPE
      && درخت_CODE (t2) == POINTER_TYPE)
    بازگشت درست;

  /* Only the precision of the parameter matters.  This check should
     make sure that the callee does not see undefined values in argument
     registers.  */
  اگر (INTEGRAL_TYPE_P (t1)
      && INTEGRAL_TYPE_P (t2)
      && TYPE_PRECISION (t1) == TYPE_PRECISION (t2))
    بازگشت درست;

  بازگشت comptypes (t1, t2);
}

/* Check if a type cast between two function types can be considered safe.  */

ایستا منطقی
c_safe_function_type_cast_p (درخت t1, درخت t2)
{
  اگر (درخت_TYPE (t1) == void_type_گره &&
      TYPE_ARG_TYPES (t1) == void_list_گره)
    بازگشت درست;

  اگر (درخت_TYPE (t2) == void_type_گره &&
      TYPE_ARG_TYPES (t2) == void_list_گره)
    بازگشت درست;

  اگر (!c_safe_arg_type_equiv_p (درخت_TYPE (t1), درخت_TYPE (t2)))
    بازگشت نادرست;

  برای (t1 = TYPE_ARG_TYPES (t1), t2 = TYPE_ARG_TYPES (t2);
       t1 && t2;
       t1 = درخت_CHAIN (t1), t2 = درخت_CHAIN (t2))
    اگر (!c_safe_arg_type_equiv_p (درخت_مقدار (t1), درخت_مقدار (t2)))
      بازگشت نادرست;

  بازگشت درست;
}

/* Build an expression representing a cast to type TYPE of expression EXPR.
   LOC is the location of the cast-- typically the open paren of the cast.  */

درخت
build_c_cast (location_t loc, درخت type, درخت عبارت)
{
  درخت مقدار;

  منطقی int_operands = عبارت_INT_CONST_OPERANDS (عبارت);

  اگر (درخت_CODE (عبارت) == EXCESS_PRECISION_عبارت)
    عبارت = درخت_OPERAND (عبارت, 0);

  مقدار = عبارت;
  اگر (int_operands)
    مقدار = remove_c_maybe_const_عبارت (مقدار);

  اگر (type == error_mark_گره || عبارت == error_mark_گره)
    بازگشت error_mark_گره;

  /* The ObjC front-end uses TYPE_MAIN_VARIANT to tie together types differing
     only in <protocol> qualifications.  But when constructing cast expressions,
     the protocols do matter and must be kept around.  */
  اگر (objc_is_object_ptr (type) && objc_is_object_ptr (درخت_TYPE (عبارت)))
    بازگشت build1 (NOP_عبارت, type, عبارت);

  type = TYPE_MAIN_VARIANT (type);

  اگر (درخت_CODE (type) == ARRAY_TYPE)
    {
      error_at (loc, "cast specifies array type");
      بازگشت error_mark_گره;
    }

  اگر (درخت_CODE (type) == FUNCTION_TYPE)
    {
      error_at (loc, "cast specifies function type");
      بازگشت error_mark_گره;
    }

  اگر (!VOID_TYPE_P (type))
    {
      مقدار = require_complete_type (loc, مقدار);
      اگر (مقدار == error_mark_گره)
	بازگشت error_mark_گره;
    }

  اگر (type == TYPE_MAIN_VARIANT (درخت_TYPE (مقدار)))
    {
      اگر (RECORD_OR_UNION_TYPE_P (type)
	  && pedwarn (loc, OPT_Wpedantic,
		      "ISO C forbids casting nonscalar to the same type"))
	      ;
      وگرنه اگر (warn_useless_cast && c_inhibit_evaluation_warnings == 0)
	warning_at (loc, OPT_Wuseless_cast,
		    "useless cast to type %qT", type);

      /* Convert to remove any qualifiers from VALUE's type.  */
      مقدار = convert (type, مقدار);
    }
  وگرنه اگر (درخت_CODE (type) == UNION_TYPE)
    {
      درخت field;

      برای (field = TYPE_FIELDS (type); field; field = DECL_CHAIN (field))
	اگر (درخت_TYPE (field) != error_mark_گره
	    && comptypes (TYPE_MAIN_VARIANT (درخت_TYPE (field)),
			  TYPE_MAIN_VARIANT (درخت_TYPE (مقدار))))
	  بشکن;

      اگر (field)
	{
	  درخت t;
	  منطقی maybe_const = درست;

	  pedwarn (loc, OPT_Wpedantic, "ISO C forbids casts to union type");
	  t = c_fully_fold (مقدار, نادرست, &maybe_const);
	  t = build_constructor_single (type, field, t);
	  اگر (!maybe_const)
	    t = c_wrap_maybe_const (t, درست);
	  t = digest_init (loc, field, type, t,
			   NULL_درخت, نادرست, نادرست, نادرست, درست, نادرست, نادرست);
	  درخت_CONSTANT (t) = درخت_CONSTANT (مقدار);
	  بازگشت t;
	}
      error_at (loc, "cast to union type from type not present in union");
      بازگشت error_mark_گره;
    }
  وگرنه
    {
      درخت otype, ovalue;

      اگر (type == void_type_گره)
	{
	  درخت t = build1 (CONVERT_عبارت, type, مقدار);
	  SET_عبارت_LOCATION (t, loc);
	  بازگشت t;
	}

      otype = درخت_TYPE (مقدار);

      /* Optionally warn about potentially worrisome casts.  */
      اگر (warn_cast_qual
	  && درخت_CODE (type) == POINTER_TYPE
	  && درخت_CODE (otype) == POINTER_TYPE)
	handle_warn_cast_qual (loc, type, otype);

      /* Warn about conversions between pointers to disjoint
	 address spaces.  */
      اگر (درخت_CODE (type) == POINTER_TYPE
	  && درخت_CODE (otype) == POINTER_TYPE
	  && !null_pointer_constant_p (مقدار))
	{
	  addr_space_t as_to = TYPE_ADDR_SPACE (درخت_TYPE (type));
	  addr_space_t as_from = TYPE_ADDR_SPACE (درخت_TYPE (otype));
	  addr_space_t as_common;

	  اگر (!addr_space_superset (as_to, as_from, &as_common))
	    {
	      اگر (ADDR_SPACE_GENERIC_P (as_from))
		warning_at (loc, 0, "cast to %qs address space pointer "
			    "from disjoint generic address space pointer",
			    c_addr_space_name (as_to));

	      وگرنه اگر (ADDR_SPACE_GENERIC_P (as_to))
		warning_at (loc, 0, "cast to generic address space pointer "
			    "from disjoint %qs address space pointer",
			    c_addr_space_name (as_from));

	      وگرنه
		warning_at (loc, 0, "cast to %qs address space pointer "
			    "from disjoint %qs address space pointer",
			    c_addr_space_name (as_to),
			    c_addr_space_name (as_from));
	    }

	  /* Warn of new allocations that are not big enough for the target
	     type.  */
	  اگر (warn_alloc_size && درخت_CODE (مقدار) == CALL_عبارت)
	    اگر (درخت fndecl = get_callee_fndecl (مقدار))
	      اگر (DECL_IS_MALLOC (fndecl))
		{
		  درخت attrs = TYPE_ATTRIBUTES (درخت_TYPE (fndecl));
		  درخت alloc_size = lookup_attribute ("alloc_size", attrs);
		  اگر (alloc_size)
		    warn_for_alloc_size (loc, درخت_TYPE (type), مقدار,
					 alloc_size);
		}
	}

      /* Warn about possible alignment problems.  */
      اگر ((STRICT_ALIGNMENT || warn_cast_align == 2)
	  && درخت_CODE (type) == POINTER_TYPE
	  && درخت_CODE (otype) == POINTER_TYPE
	  && درخت_CODE (درخت_TYPE (otype)) != VOID_TYPE
	  && درخت_CODE (درخت_TYPE (otype)) != FUNCTION_TYPE
	  /* Don't warn about opaque types, where the actual alignment
	     restriction is unknown.  */
	  && !(RECORD_OR_UNION_TYPE_P (درخت_TYPE (otype))
	       && TYPE_MODE (درخت_TYPE (otype)) == VOIDmode)
	  && min_align_of_type (درخت_TYPE (type))
	     > min_align_of_type (درخت_TYPE (otype)))
	warning_at (loc, OPT_Wcast_align,
		    "cast increases required alignment of target type");

      اگر ((درخت_CODE (type) == INTEGER_TYPE
	   || درخت_CODE (type) == BITINT_TYPE)
	  && درخت_CODE (otype) == POINTER_TYPE
	  && TYPE_PRECISION (type) != TYPE_PRECISION (otype))
      /* Unlike conversion of integers to pointers, where the
         warning is disabled for converting constants because
         of cases such as SIG_*, warn about converting constant
         pointers to integers. In some cases it may cause unwanted
         sign extension, and a warning is appropriate.  */
	warning_at (loc, OPT_Wpointer_to_int_cast,
		    "cast from pointer to integer of different size");

      اگر ((درخت_CODE (مقدار) == CALL_عبارت
	   && !is_access_with_size_p (مقدار))
	  && درخت_CODE (type) != درخت_CODE (otype))
	warning_at (loc, OPT_Wbad_function_cast,
		    "cast from function call of type %qT "
		    "to non-matching type %qT", otype, type);

      اگر (درخت_CODE (type) == POINTER_TYPE
	  && (درخت_CODE (otype) == INTEGER_TYPE
	      || درخت_CODE (otype) == BITINT_TYPE)
	  && TYPE_PRECISION (type) != TYPE_PRECISION (otype)
	  /* Don't warn about converting any constant.  */
	  && !درخت_CONSTANT (مقدار))
	warning_at (loc,
		    OPT_Wint_to_pointer_cast, "cast to pointer from integer "
		    "of different size");

      اگر (warn_strict_aliasing <= 2)
        strict_aliasing_warning (عبارت_LOCATION (مقدار), type, عبارت);

      /* If pedantic, warn for conversions between function and object
	 pointer types, except for converting a null pointer constant
	 to function pointer type.  */
      اگر (pedantic
	  && درخت_CODE (type) == POINTER_TYPE
	  && درخت_CODE (otype) == POINTER_TYPE
	  && درخت_CODE (درخت_TYPE (otype)) == FUNCTION_TYPE
	  && درخت_CODE (درخت_TYPE (type)) != FUNCTION_TYPE)
	pedwarn (loc, OPT_Wpedantic, "ISO C forbids "
		 "conversion of function pointer to object pointer type");

      اگر (pedantic
	  && درخت_CODE (type) == POINTER_TYPE
	  && درخت_CODE (otype) == POINTER_TYPE
	  && درخت_CODE (درخت_TYPE (type)) == FUNCTION_TYPE
	  && درخت_CODE (درخت_TYPE (otype)) != FUNCTION_TYPE
	  && !null_pointer_constant_p (مقدار))
	pedwarn (loc, OPT_Wpedantic, "ISO C forbids "
		 "conversion of object pointer to function pointer type");

      اگر (درخت_CODE (type) == POINTER_TYPE
	  && درخت_CODE (otype) == POINTER_TYPE
	  && درخت_CODE (درخت_TYPE (type)) == FUNCTION_TYPE
	  && درخت_CODE (درخت_TYPE (otype)) == FUNCTION_TYPE
	  && !c_safe_function_type_cast_p (درخت_TYPE (type),
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
      اگر (int_operands
	  && درخت_CODE (مقدار) != INTEGER_CST
	  && (درخت_CODE (type) == BOOLEAN_TYPE
	      || (درخت_CODE (type) == ENUMERAL_TYPE
		  && ENUM_UNDERLYING_TYPE (type) != NULL_درخت
		  && درخت_CODE (ENUM_UNDERLYING_TYPE (type)) == BOOLEAN_TYPE)))
	مقدار = note_integer_operands (مقدار);
      مقدار = convert (type, مقدار);

      /* Ignore any integer overflow caused by the cast.  */
      اگر (درخت_CODE (مقدار) == INTEGER_CST && !FLOAT_TYPE_P (otype))
	{
	  اگر (درخت_OVERFLOW_P (ovalue))
	    {
	      اگر (!درخت_OVERFLOW (مقدار))
		{
		  /* Avoid clobbering a shared constant.  */
		  مقدار = copy_گره (مقدار);
		  درخت_OVERFLOW (مقدار) = درخت_OVERFLOW (ovalue);
		}
	    }
	  وگرنه اگر (درخت_OVERFLOW (مقدار))
	    /* Reset VALUE's overflow flags, ensuring constant sharing.  */
	    مقدار = wide_int_to_درخت (درخت_TYPE (مقدار), wi::to_wide (مقدار));
	}
    }

  /* Don't let a cast be an lvalue.  */
  اگر (lvalue_p (مقدار)
      /* Also, don't let a cast be a bit-field of a bit-precise integer type,
	 otherwise it could be incorrectly subject of integer promotions.  */
      || (درخت_CODE (مقدار) == COMPONENT_REF
	  && DECL_C_BIT_FIELD (درخت_OPERAND (مقدار, 1))
	  && BITINT_TYPE_P (DECL_BIT_FIELD_TYPE (درخت_OPERAND (مقدار, 1)))))
    مقدار = non_lvalue_loc (loc, مقدار);

  /* Don't allow the results of casting to floating-point or complex
     types be confused with actual constants, or casts involving
     integer and pointer types other than direct integer-to-integer
     and integer-to-pointer be confused with integer constant
     expressions and null pointer constants.  */
  اگر (درخت_CODE (مقدار) == REAL_CST
      || درخت_CODE (مقدار) == COMPLEX_CST
      || (درخت_CODE (مقدار) == INTEGER_CST
	  && !((درخت_CODE (عبارت) == INTEGER_CST
		&& INTEGRAL_TYPE_P (درخت_TYPE (عبارت)))
	       || درخت_CODE (عبارت) == REAL_CST
	       || درخت_CODE (عبارت) == COMPLEX_CST)))
      مقدار = build1 (NOP_عبارت, type, مقدار);

  /* If the expression has integer operands and so can occur in an
     unevaluated part of an integer constant expression, ensure the
     return value reflects this.  */
  اگر (int_operands
      && INTEGRAL_TYPE_P (type)
      && مقدار != error_mark_گره
      && !عبارت_INT_CONST_OPERANDS (مقدار))
    مقدار = note_integer_operands (مقدار);

  protected_set_عبارت_location (مقدار, loc);
  بازگشت مقدار;
}

/* Interpret a cast of expression EXPR to type TYPE.  LOC is the
   location of the open paren of the cast, or the position of the cast
   expr.  */
درخت
c_cast_عبارت (location_t loc, ساختار c_type_name *type_name, درخت عبارت)
{
  درخت type;
  درخت type_عبارت = NULL_درخت;
  منطقی type_عبارت_const = درست;
  درخت ret;
  صحیح saved_wsp = warn_strict_prototypes;

  /* This avoids warnings about unprototyped casts on
     integers.  E.g. "#define SIG_DFL (void(*)())0".  */
  اگر (درخت_CODE (عبارت) == INTEGER_CST)
    warn_strict_prototypes = 0;
  type = groktypename (type_name, &type_عبارت, &type_عبارت_const);
  warn_strict_prototypes = saved_wsp;

  اگر (درخت_CODE (عبارت) == ADDR_عبارت && !VOID_TYPE_P (type)
      && reject_gcc_builtin (عبارت))
    بازگشت error_mark_گره;

  ret = build_c_cast (loc, type, عبارت);
  اگر (ret == error_mark_گره)
    بازگشت error_mark_گره;

  اگر (type_عبارت)
    {
      منطقی inner_عبارت_const = درست;
      ret = c_fully_fold (ret, require_constant_مقدار, &inner_عبارت_const);
      ret = build2 (C_MAYBE_CONST_عبارت, درخت_TYPE (ret), type_عبارت, ret);
      C_MAYBE_CONST_عبارت_NON_CONST (ret) = !(type_عبارت_const
					     && inner_عبارت_const);
      SET_عبارت_LOCATION (ret, loc);
    }

  اگر (!عبارت_HAS_LOCATION (ret))
    protected_set_عبارت_location (ret, loc);

  /* C++ does not permits types to be defined in a cast, but it
     allows references to incomplete types.  */
  اگر (warn_cxx_compat && type_name->specs->typespec_kind == ctsk_tagdef)
    warning_at (loc, OPT_Wc___compat,
		"defining a type in a cast is invalid in C++");

  بازگشت ret;
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
		   شمارش درخت_code modifycode,
		   location_t rhs_loc, درخت rhs, درخت rhs_origtype)
{
  درخت result;
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
  اگر (درخت_CODE (lhs) == ERROR_MARK || درخت_CODE (rhs) == ERROR_MARK)
    بازگشت error_mark_گره;

  /* Ensure an error for assigning a non-lvalue array to an array in
     C90.  */
  اگر (درخت_CODE (lhstype) == ARRAY_TYPE)
    {
      error_at (location, "assignment to expression with array type");
      بازگشت error_mark_گره;
    }

  /* For ObjC properties, defer this check.  */
  اگر (!objc_is_property_ref (lhs) && !lvalue_or_else (location, lhs, lv_assign))
    بازگشت error_mark_گره;

  is_atomic_op = really_atomic_lvalue (lhs);

  newrhs = rhs;

  اگر (درخت_CODE (lhs) == C_MAYBE_CONST_عبارت)
    {
      درخت inner = build_modify_عبارت (location, C_MAYBE_CONST_عبارت_عبارت (lhs),
				      lhs_origtype, modifycode, rhs_loc, rhs,
				      rhs_origtype);
      اگر (inner == error_mark_گره)
	بازگشت error_mark_گره;
      result = build2 (C_MAYBE_CONST_عبارت, درخت_TYPE (inner),
		       C_MAYBE_CONST_عبارت_PRE (lhs), inner);
      gcc_assert (!C_MAYBE_CONST_عبارت_INT_OPERANDS (lhs));
      C_MAYBE_CONST_عبارت_NON_CONST (result) = 1;
      protected_set_عبارت_location (result, location);
      بازگشت result;
    }

  /* If a binary op has been requested, combine the old LHS value with the RHS
     producing the value we should actually store into the LHS.  */

  اگر (modifycode != NOP_عبارت)
    {
      lhs = c_fully_fold (lhs, نادرست, پوچ, درست);
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
	      اگر (درخت_CODE (rhs) == EXCESS_PRECISION_عبارت)
		newrhs = save_عبارت (درخت_OPERAND (rhs, 0));
	      وگرنه
		newrhs = save_عبارت (rhs);
	      rhseval = newrhs;
	      اگر (درخت_CODE (rhs) == EXCESS_PRECISION_عبارت)
		newrhs = build1 (EXCESS_PRECISION_عبارت, درخت_TYPE (rhs),
				 newrhs);
	    }
	  منطقی clear_decl_read = نادرست;
	  اگر ((VAR_P (lhs) || درخت_CODE (lhs) == PARM_DECL)
	      && !DECL_READ_P (lhs)
	      && (VAR_P (lhs) ? warn_unused_but_set_variable
			      : warn_unused_but_set_parameter) > 2)
	    {
	      mark_exp_read (newrhs);
	      اگر (!DECL_READ_P (lhs))
		clear_decl_read = درست;
	    }

	  newrhs = build_دودویی_op (location, modifycode,
				    convert_lvalue_to_rvalue (location, lhs,
							      درست, درست),
				    newrhs, درست);
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
      اگر (درخت_CODE (newrhs) == EXCESS_PRECISION_عبارت)
	result = objc_maybe_build_modify_عبارت (lhs, درخت_OPERAND (newrhs, 0));
      وگرنه
	result = objc_maybe_build_modify_عبارت (lhs, newrhs);
      اگر (result)
	برو return_result;

      /* Else, do the check that we postponed for Objective-C.  */
      اگر (!lvalue_or_else (location, lhs, lv_assign))
	بازگشت error_mark_گره;
    }

  /* Give an error for storing in something that is 'const'.  */

  اگر (TYPE_READONLY (lhstype)
      || (RECORD_OR_UNION_TYPE_P (lhstype)
	  && C_TYPE_FIELDS_READONLY (lhstype)))
    {
      readonly_error (location, lhs, lv_assign);
      بازگشت error_mark_گره;
    }
  وگرنه اگر (درخت_READONLY (lhs))
    readonly_warning (lhs, lv_assign);

  /* If storing into a structure or union member,
     it has probably been given type `int'.
     Compute the type that would go with
     the actual amount of storage the member occupies.  */

  اگر (درخت_CODE (lhs) == COMPONENT_REF
      && (درخت_CODE (lhstype) == INTEGER_TYPE
	  || درخت_CODE (lhstype) == BOOLEAN_TYPE
	  || SCALAR_FLOAT_TYPE_P (lhstype)
	  || درخت_CODE (lhstype) == ENUMERAL_TYPE))
    lhstype = درخت_TYPE (get_unwidened (lhs, 0));

  /* If storing in a field that is in actuality a short or narrower than one,
     we must store in the field in its actual type.  */

  اگر (lhstype != درخت_TYPE (lhs))
    {
      lhs = copy_گره (lhs);
      درخت_TYPE (lhs) = lhstype;
    }

  /* Issue -Wc++-compat warnings about an assignment to an enum type
     when LHS does not have its original type.  This happens for,
     e.g., an enum bitfield in a struct.  */
  اگر (warn_cxx_compat
      && lhs_origtype != NULL_درخت
      && lhs_origtype != lhstype
      && درخت_CODE (lhs_origtype) == ENUMERAL_TYPE)
    {
      درخت checktype = (rhs_origtype != NULL_درخت
			? rhs_origtype
			: درخت_TYPE (rhs));
      اگر (checktype != error_mark_گره
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

  اگر (!(is_atomic_op && modifycode != NOP_عبارت))
    {
      درخت rhs_semantic_type = NULL_درخت;
      اگر (!c_in_omp_for)
	{
	  اگر (درخت_CODE (newrhs) == EXCESS_PRECISION_عبارت)
	    {
	      rhs_semantic_type = درخت_TYPE (newrhs);
	      newrhs = درخت_OPERAND (newrhs, 0);
	    }
	  npc = null_pointer_constant_p (newrhs);
	  newrhs = c_fully_fold (newrhs, نادرست, پوچ);
	  اگر (rhs_semantic_type)
	    newrhs = build1 (EXCESS_PRECISION_عبارت, rhs_semantic_type, newrhs);
	}
      وگرنه
	npc = null_pointer_constant_p (newrhs);
      newrhs = convert_for_assignment (location, rhs_loc, lhstype, newrhs,
				       rhs_origtype, ic_assign, npc,
				       NULL_درخت, NULL_درخت, 0);
      اگر (درخت_CODE (newrhs) == ERROR_MARK)
	بازگشت error_mark_گره;
    }

  /* Emit ObjC write barrier, if necessary.  */
  اگر (c_dialect_objc () && flag_objc_gc)
    {
      result = objc_generate_write_barrier (lhs, modifycode, newrhs);
      اگر (result)
	{
	  protected_set_عبارت_location (result, location);
	  برو return_result;
	}
    }

  /* Scan operands.  */

  اگر (is_atomic_op)
    result = build_atomic_assign (location, lhs, modifycode, newrhs, نادرست);
  وگرنه
    {
      result = build2 (MODIFY_عبارت, lhstype, lhs, newrhs);
      درخت_SIDE_EFFECTS (result) = 1;
      protected_set_عبارت_location (result, location);
    }

  /* If we got the LHS in a different type for storing in,
     convert the result back to the nominal type of LHS
     so that the value we return always has the same type
     as the LHS argument.  */

  اگر (olhstype == درخت_TYPE (result))
    برو return_result;

  result = convert_for_assignment (location, rhs_loc, olhstype, result,
				   rhs_origtype, ic_assign, نادرست, NULL_درخت,
				   NULL_درخت, 0);
  protected_set_عبارت_location (result, location);

return_result:
  اگر (rhseval)
    result = build2 (COMPOUND_عبارت, درخت_TYPE (result), rhseval, result);
  بازگشت result;
}

/* Return whether STRUCT_TYPE has an anonymous field with type TYPE.
   This is used to implement -fplan9-extensions.  */

ایستا منطقی
find_anonymous_field_with_type (درخت struct_type, درخت type)
{
  درخت field;
  منطقی found;

  gcc_assert (RECORD_OR_UNION_TYPE_P (struct_type));
  found = نادرست;
  برای (field = TYPE_FIELDS (struct_type);
       field != NULL_درخت;
       field = درخت_CHAIN (field))
    {
      درخت fieldtype = remove_qualifiers (درخت_TYPE (field));
      اگر (DECL_NAME (field) == پوچ
	  && comptypes (type, fieldtype))
	{
	  اگر (found)
	    بازگشت نادرست;
	  found = درست;
	}
      وگرنه اگر (DECL_NAME (field) == پوچ
	       && RECORD_OR_UNION_TYPE_P (درخت_TYPE (field))
	       && find_anonymous_field_with_type (درخت_TYPE (field), type))
	{
	  اگر (found)
	    بازگشت نادرست;
	  found = درست;
	}
    }
  بازگشت found;
}

/* RHS is an expression whose type is pointer to struct.  If there is
   an anonymous field in RHS with type TYPE, then return a pointer to
   that field in RHS.  This is used with -fplan9-extensions.  This
   returns NULL if no conversion could be found.  */

ایستا درخت
convert_to_anonymous_field (location_t location, درخت type, درخت rhs)
{
  درخت rhs_struct_type, lhs_main_type;
  درخت field, found_field;
  منطقی found_sub_field;
  درخت ret;

  gcc_assert (POINTER_TYPE_P (درخت_TYPE (rhs)));
  rhs_struct_type = درخت_TYPE (درخت_TYPE (rhs));
  gcc_assert (RECORD_OR_UNION_TYPE_P (rhs_struct_type));

  gcc_assert (POINTER_TYPE_P (type));
  lhs_main_type = remove_qualifiers (درخت_TYPE (type));

  found_field = NULL_درخت;
  found_sub_field = نادرست;
  برای (field = TYPE_FIELDS (rhs_struct_type);
       field != NULL_درخت;
       field = درخت_CHAIN (field))
    {
      اگر (DECL_NAME (field) != NULL_درخت
	  || !RECORD_OR_UNION_TYPE_P (درخت_TYPE (field)))
	ادامه;
      درخت fieldtype = remove_qualifiers (درخت_TYPE (field));
      اگر (comptypes (lhs_main_type, fieldtype))
	{
	  اگر (found_field != NULL_درخت)
	    بازگشت NULL_درخت;
	  found_field = field;
	}
      وگرنه اگر (find_anonymous_field_with_type (درخت_TYPE (field),
					       lhs_main_type))
	{
	  اگر (found_field != NULL_درخت)
	    بازگشت NULL_درخت;
	  found_field = field;
	  found_sub_field = درست;
	}
    }

  اگر (found_field == NULL_درخت)
    بازگشت NULL_درخت;

  ret = fold_build3_loc (location, COMPONENT_REF, درخت_TYPE (found_field),
			 build_fold_indirect_ref (rhs), found_field,
			 NULL_درخت);
  ret = build_fold_addr_عبارت_loc (location, ret);

  اگر (found_sub_field)
    {
      ret = convert_to_anonymous_field (location, type, ret);
      gcc_assert (ret != NULL_درخت);
    }

  بازگشت ret;
}

/* Issue an error message for a bad initializer component.
   GMSGID identifies the message.
   The component name is taken from the spelling stack.  */

ایستا تهی ATTRIBUTE_GCC_DIAG (2,0)
error_init (location_t loc, ثابت نویسه *gmsgid, ...)
{
  نویسه *ofwhat;

  auto_diagnostic_group d;

  /* The gmsgid may be a format string with %< and %>. */
  va_list ap;
  va_start (ap, gmsgid);
  منطقی warned = emit_diagnostic_valist (diagnostics::kind::error,
					loc, -1, gmsgid, &ap);
  va_end (ap);

  ofwhat = print_spelling ((نویسه *) alloca (spelling_length () + 1));
  اگر (*ofwhat && warned)
    inform (loc, "(near initialization for %qs)", ofwhat);
}

/* Used to implement pedwarn_init and permerror_init.  */

ایستا منطقی ATTRIBUTE_GCC_DIAG (3,0)
pedwarn_permerror_init (location_t loc, صحیح opt, ثابت نویسه *gmsgid,
			va_list *ap, شمارش diagnostics::kind kind)
{
  /* Use the location where a macro was expanded rather than where
     it was defined to make sure macros defined in system headers
     but used incorrectly elsewhere are diagnosed.  */
  location_t exploc = expansion_point_location_if_in_system_header (loc);
  auto_diagnostic_group d;
  منطقی warned = emit_diagnostic_valist (kind, exploc, opt, gmsgid, ap);
  اگر (warned)
    {
      نویسه *ofwhat = print_spelling ((نویسه *) alloca (spelling_length () + 1));
      اگر (*ofwhat)
	inform (exploc, "(near initialization for %qs)", ofwhat);
    }
  بازگشت warned;
}

/* Issue a pedantic warning for a bad initializer component.  OPT is
   the option OPT_* (from options.h) controlling this warning or 0 if
   it is unconditionally given.  GMSGID identifies the message.  The
   component name is taken from the spelling stack.  */

ایستا منطقی ATTRIBUTE_GCC_DIAG (3,0)
pedwarn_init (location_t loc, صحیح opt, ثابت نویسه *gmsgid, ...)
{
  va_list ap;
  va_start (ap, gmsgid);
  منطقی warned = pedwarn_permerror_init (loc, opt, gmsgid, &ap,
					diagnostics::kind::pedwarn);
  va_end (ap);
  بازگشت warned;
}

/* Like pedwarn_init, but issue a permerror.  */

ایستا منطقی ATTRIBUTE_GCC_DIAG (3,0)
permerror_init (location_t loc, صحیح opt, ثابت نویسه *gmsgid, ...)
{
  va_list ap;
  va_start (ap, gmsgid);
  منطقی warned = pedwarn_permerror_init (loc, opt, gmsgid, &ap,
					diagnostics::kind::permerror);
  va_end (ap);
  بازگشت warned;
}

/* Issue a warning for a bad initializer component.

   OPT is the OPT_W* value corresponding to the warning option that
   controls this warning.  GMSGID identifies the message.  The
   component name is taken from the spelling stack.  */

ایستا تهی
warning_init (location_t loc, صحیح opt, ثابت نویسه *gmsgid)
{
  نویسه *ofwhat;
  منطقی warned;

  auto_diagnostic_group d;

  /* Use the location where a macro was expanded rather than where
     it was defined to make sure macros defined in system headers
     but used incorrectly elsewhere are diagnosed.  */
  location_t exploc = expansion_point_location_if_in_system_header (loc);

  /* The gmsgid may be a format string with %< and %>. */
  warned = warning_at (exploc, opt, gmsgid);
  اگر (warned)
    {
      ofwhat = print_spelling ((نویسه *) alloca (spelling_length () + 1));
      اگر (*ofwhat)
	inform (exploc, "(near initialization for %qs)", ofwhat);
    }
}

/* If TYPE is an array type and EXPR is a parenthesized string
   constant, warn if pedantic that EXPR is being used to initialize an
   object of type TYPE.  */

تهی
maybe_warn_string_init (location_t loc, درخت type, ساختار c_عبارت عبارت)
{
  اگر (pedantic
      && درخت_CODE (type) == ARRAY_TYPE
      && درخت_CODE (عبارت.مقدار) == STRING_CST
      && عبارت.original_code != STRING_CST)
    pedwarn_init (loc, OPT_Wpedantic,
		  "array initialized from parenthesized string constant");
}

/* Attempt to locate the parameter with the given index within FNDECL,
   returning DECL_SOURCE_LOCATION (FNDECL) if it can't be found.  */

ایستا location_t
get_fndecl_argument_location (درخت fndecl, صحیح argnum)
{
  صحیح i;
  درخت param;

  /* Locate param by index within DECL_ARGUMENTS (fndecl).  */
  برای (i = 0, param = DECL_ARGUMENTS (fndecl);
       i < argnum && param;
       i++, param = درخت_CHAIN (param))
    ;

  /* If something went wrong (e.g. if we have a builtin and thus no arguments),
     return DECL_SOURCE_LOCATION (FNDECL).  */
  اگر (param == پوچ)
    بازگشت DECL_SOURCE_LOCATION (fndecl);

  بازگشت DECL_SOURCE_LOCATION (param);
}

/* Issue a note about a mismatching argument for parameter PARMNUM
   to FUNDECL, for types EXPECTED_TYPE and ACTUAL_TYPE.
   Attempt to issue the note at the pertinent parameter of the decl;
   failing that issue it at the location of FUNDECL; failing that
   issue it at PLOC.
   Use highlight_colors::actual for the ACTUAL_TYPE
   and highlight_colors::expected for EXPECTED_TYPE and the
   parameter of FUNDECL*/

ایستا تهی
inform_for_arg (درخت fundecl, location_t ploc, صحیح parmnum,
		درخت expected_type, درخت actual_type)
{
  location_t loc;
  اگر (fundecl && !DECL_IS_UNDECLARED_BUILTIN (fundecl))
    loc = get_fndecl_argument_location (fundecl, parmnum - 1);
  وگرنه
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

ایستا تهی
maybe_warn_builtin_no_proto_arg (location_t loc, درخت fundecl, صحیح parmnum,
				 درخت parmtype, درخت argtype)
{
  درخت_code parmcode = درخت_CODE (parmtype);
  درخت_code argcode = درخت_CODE (argtype);
  درخت promoted = c_type_promotes_to (argtype);

  /* Avoid warning for enum arguments that promote to an integer type
     of the same size/mode.  */
  اگر (parmcode == INTEGER_TYPE
      && argcode == ENUMERAL_TYPE
      && TYPE_MODE (parmtype) == TYPE_MODE (argtype))
    بازگشت;

  اگر ((parmcode == argcode
       || (parmcode == INTEGER_TYPE
	   && argcode == ENUMERAL_TYPE))
      && TYPE_MAIN_VARIANT (parmtype) == TYPE_MAIN_VARIANT (promoted))
    بازگشت;

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
    inform (DECL_SOURCE_LOCATION (fundecl),
	    "built-in %qD declared here",
	    fundecl);
}

/* Print a declaration in quotes, with the given highlight_color.
   Analogous to handler for %qD, but with a specific highlight color.  */

رده pp_element_quoted_decl : عمومی pp_element
{
عمومی:
  pp_element_quoted_decl (درخت decl, ثابت نویسه *highlight_color)
  : m_decl (decl),
    m_highlight_color (highlight_color)
  {
  }

  تهی add_to_phase_2 (pp_markup::context &ctxt) override
  {
    ctxt.begin_quote ();
    ctxt.begin_highlight_color (m_highlight_color);

    print_decl (ctxt);

    ctxt.end_highlight_color ();
    ctxt.end_quote ();
  }

  تهی print_decl (pp_markup::context &ctxt)
  {
    pretty_printer *ثابت pp = &ctxt.m_pp;
    pp->set_padding (pp_none);
    اگر (DECL_NAME (m_decl))
      pp_identifier (pp, lang_hooks.decl_printable_name (m_decl, 2));
    وگرنه
      pp_string (pp, _("({anonymous})"));
  }

خصوصی:
  درخت m_decl;
  ثابت نویسه *m_highlight_color;
};

/* If TYPE is from a typedef, issue a note showing the location
   to the user.
   Use HIGHLIGHT_COLOR as the highlight color.  */

ایستا تهی
maybe_inform_typedef_location (درخت type, ثابت نویسه *highlight_color)
{
  اگر (!typedef_variant_p (type))
    بازگشت;

  درخت typedef_decl = TYPE_NAME (type);
  gcc_assert (درخت_CODE (typedef_decl) == TYPE_DECL);
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

ایستا درخت
convert_for_assignment (location_t location, location_t عبارت_loc, درخت type,
			درخت rhs, درخت origtype, شمارش impl_conv errtype,
			منطقی null_pointer_constant, درخت fundecl,
			درخت function, صحیح parmnum, صحیح warnopt /* = 0 */)
{
  شمارش درخت_code codel = درخت_CODE (type);
  درخت orig_rhs = rhs;
  درخت rhstype;
  شمارش درخت_code coder;
  درخت rname = NULL_درخت;
  منطقی objc_ok = نادرست;

  /* Use the expansion point location to handle cases such as user's
     function returning a wrong-type macro defined in a system header.  */
  location = expansion_point_location_if_in_system_header (location);

  اگر (errtype == ic_argpass)
    {
      درخت selector;
      /* Change pointer to function to the function itself for
	 diagnostics.  */
      اگر (درخت_CODE (function) == ADDR_عبارت
	  && درخت_CODE (درخت_OPERAND (function, 0)) == FUNCTION_DECL)
	function = درخت_OPERAND (function, 0);

      /* Handle an ObjC selector specially for diagnostics.  */
      selector = objc_message_selector ();
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
#define PEDWARN_FOR_ASSIGNMENT(LOCATION, PLOC, OPT, AR, AS, IN, RE)	 \
  انجامبده {                                                                   \
    انتخاب (errtype)                                                     \
      {                                                                  \
      حالت ic_argpass:                                                   \
	{								\
	  auto_diagnostic_group d;						\
	  اگر (pedwarn (PLOC, OPT, AR, parmnum, rname))		\
	    inform_for_arg (fundecl, (PLOC), parmnum, type, rhstype); \
	}								\
        بشکن;                                                           \
      حالت ic_assign:                                                    \
        pedwarn (LOCATION, OPT, AS);                                     \
        بشکن;                                                           \
      حالت ic_init:                                                      \
      حالت ic_init_const:                                                \
        pedwarn_init (LOCATION, OPT, IN);                                \
        بشکن;                                                           \
      حالت ic_return:                                                    \
        pedwarn (LOCATION, OPT, RE);					 \
        بشکن;                                                           \
      پیشفرض:                                                           \
        gcc_unreachable ();                                              \
      }                                                                  \
  } وقتی (0)

  /* This macro is used to emit diagnostics to ensure that all format
     strings are complete sentences, visible to gettext and checked at
     compile time.  It can be called with 'pedwarn' or 'warning_at'.  */
#define WARNING_FOR_QUALIFIERS(PEDWARN, LOCATION, PLOC, OPT, AR, AS, IN, RE, QUALS) \
  انجامبده {                                                                   \
    انتخاب (errtype)                                                     \
      {                                                                  \
      حالت ic_argpass:                                                   \
	{								 \
	  auto_diagnostic_group d;					 \
	  اگر (PEDWARN) {						 \
	    اگر (pedwarn (PLOC, OPT, AR, parmnum, rname, QUALS))          \
	      inform_for_arg (fundecl, (PLOC), parmnum, type, rhstype);  \
	  } وگرنه {							 \
	    اگر (warning_at (PLOC, OPT, AR, parmnum, rname, QUALS))	 \
	      inform_for_arg (fundecl, (PLOC), parmnum, type, rhstype);  \
	  }								 \
	}								 \
        بشکن;                                                           \
      حالت ic_assign:                                                    \
	اگر (PEDWARN)							 \
	  pedwarn (LOCATION, OPT, AS, QUALS);                            \
	وگرنه								 \
	  warning_at (LOCATION, OPT, AS, QUALS);                         \
        بشکن;                                                           \
      حالت ic_init:                                                      \
      حالت ic_init_const:                                                \
	اگر (PEDWARN)							 \
	  pedwarn (LOCATION, OPT, IN, QUALS);                            \
	وگرنه								 \
	  warning_at (LOCATION, OPT, IN, QUALS);                         \
        بشکن;                                                           \
      حالت ic_return:                                                    \
	اگر (PEDWARN)							 \
	  pedwarn (LOCATION, OPT, RE, QUALS);                            \
	وگرنه								 \
	  warning_at (LOCATION, OPT, RE, QUALS);                         \
        بشکن;                                                           \
      پیشفرض:                                                           \
        gcc_unreachable ();                                              \
      }                                                                  \
  } وقتی (0)

  /* This macro is used to emit diagnostics to ensure that all format
     strings are complete sentences, visible to gettext and checked at
     compile time.  It is the same as PEDWARN_FOR_ASSIGNMENT but with an
     extra parameter to enumerate qualifiers.  */
#define PEDWARN_FOR_QUALIFIERS(LOCATION, PLOC, OPT, AR, AS, IN, RE, QUALS) \
   WARNING_FOR_QUALIFIERS (درست, LOCATION, PLOC, OPT, AR, AS, IN, RE, QUALS)


  اگر (درخت_CODE (rhs) == EXCESS_PRECISION_عبارت)
    rhs = درخت_OPERAND (rhs, 0);

  rhstype = درخت_TYPE (rhs);
  coder = درخت_CODE (rhstype);

  اگر (coder == ERROR_MARK)
    بازگشت error_mark_گره;

  اگر (c_dialect_objc ())
    {
      صحیح parmno;

      انتخاب (errtype)
	{
	حالت ic_return:
	  parmno = 0;
	  بشکن;

	حالت ic_assign:
	  parmno = -1;
	  بشکن;

	حالت ic_init:
	حالت ic_init_const:
	  parmno = -2;
	  بشکن;

	پیشفرض:
	  parmno = parmnum;
	  بشکن;
	}

      objc_ok = objc_compare_types (type, rhstype, parmno, rname);
    }

  اگر (warn_cxx_compat)
    {
      درخت checktype = origtype != NULL_درخت ? origtype : rhstype;
      اگر (checktype != error_mark_گره
	  && درخت_CODE (type) == ENUMERAL_TYPE
	  && TYPE_MAIN_VARIANT (checktype) != TYPE_MAIN_VARIANT (type))
	انتخاب (errtype)
	  {
	  حالت ic_argpass:
	    اگر (pedwarn (عبارت_loc, OPT_Wc___compat, "enum conversion when "
			 "passing argument %d of %qE is invalid in C++",
			 parmnum, rname))
	      inform ((fundecl && !DECL_IS_UNDECLARED_BUILTIN (fundecl))
		      ? DECL_SOURCE_LOCATION (fundecl) : عبارت_loc,
		      "expected %qT but argument is of type %qT",
		      type, rhstype);
	    بشکن;
	  حالت ic_assign:
	    pedwarn (location, OPT_Wc___compat, "enum conversion from %qT to "
		     "%qT in assignment is invalid in C++", rhstype, type);
	    بشکن;
	  حالت ic_init:
	  حالت ic_init_const:
	    pedwarn_init (location, OPT_Wc___compat, "enum conversion from "
			  "%qT to %qT in initialization is invalid in C++",
			  rhstype, type);
	    بشکن;
	  حالت ic_return:
	    pedwarn (location, OPT_Wc___compat, "enum conversion from %qT to "
		     "%qT in return is invalid in C++", rhstype, type);
	    بشکن;
	  پیشفرض:
	    gcc_unreachable ();
	  }
    }

  اگر (warn_enum_conversion)
    {
      درخت checktype = origtype != NULL_درخت ? origtype : rhstype;
      اگر (checktype != error_mark_گره
	  && درخت_CODE (checktype) == ENUMERAL_TYPE
	  && درخت_CODE (type) == ENUMERAL_TYPE
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
      warn_for_address_of_packed_member (type, orig_rhs);
      اگر (type != rhstype)
	/* Convert RHS to TYPE in order to not lose TYPE in diagnostics.  */
	rhs = convert (type, rhs);
      بازگشت rhs;
    }

  اگر (coder == VOID_TYPE)
    {
      /* Except for passing an argument to an unprototyped function,
	 this is a constraint violation.  When passing an argument to
	 an unprototyped function, it is compile-time undefined;
	 making it a constraint in that case was rejected in
	 DR#252.  */
      ثابت نویسه پیام[] = "void value not ignored as it ought to be";
      اگر (warnopt)
	warning_at (location, warnopt, پیام);
      وگرنه
	error_at (location, پیام);
      بازگشت error_mark_گره;
    }
  rhs = require_complete_type (location, rhs);
  اگر (rhs == error_mark_گره)
    بازگشت error_mark_گره;

  اگر (coder == POINTER_TYPE && reject_gcc_builtin (rhs))
    بازگشت error_mark_گره;

  /* A non-reference type can convert to a reference.  This handles
     va_start, va_copy and possibly port built-ins.  */
  اگر (codel == REFERENCE_TYPE && coder != REFERENCE_TYPE)
    {
      اگر (!lvalue_p (rhs))
	{
	  ثابت نویسه پیام[] = "cannot pass rvalue to reference parameter";
	  اگر (warnopt)
	    warning_at (location, warnopt, پیام);
	  وگرنه
	    error_at (location, پیام);
	  بازگشت error_mark_گره;
	}
      اگر (!c_mark_addressable (rhs))
	بازگشت error_mark_گره;
      rhs = build1 (ADDR_عبارت, c_build_pointer_type (درخت_TYPE (rhs)), rhs);
      SET_عبارت_LOCATION (rhs, location);

      rhs = convert_for_assignment (location, عبارت_loc,
				    c_build_pointer_type (درخت_TYPE (type)),
				    rhs, origtype, errtype,
				    null_pointer_constant, fundecl, function,
				    parmnum, warnopt);
      اگر (rhs == error_mark_گره)
	بازگشت error_mark_گره;

      rhs = build1 (NOP_عبارت, type, rhs);
      SET_عبارت_LOCATION (rhs, location);
      بازگشت rhs;
    }
  /* Some types can interconvert without explicit casts.  */
  وگرنه اگر (codel == VECTOR_TYPE && coder == VECTOR_TYPE
	   && vector_types_convertible_p (type, درخت_TYPE (rhs), درست))
    بازگشت convert (type, rhs);
  /* Arithmetic types all interconvert, and enum is treated like int.  */
  وگرنه اگر ((codel == INTEGER_TYPE || codel == REAL_TYPE
	    || codel == FIXED_POINT_TYPE
	    || codel == ENUMERAL_TYPE || codel == COMPLEX_TYPE
	    || codel == BOOLEAN_TYPE || codel == BITINT_TYPE)
	   && (coder == INTEGER_TYPE || coder == REAL_TYPE
	       || coder == FIXED_POINT_TYPE
	       || coder == ENUMERAL_TYPE || coder == COMPLEX_TYPE
	       || coder == BOOLEAN_TYPE || coder == BITINT_TYPE))
    {
      اگر (warnopt && errtype == ic_argpass)
	maybe_warn_builtin_no_proto_arg (عبارت_loc, fundecl, parmnum, type,
					 rhstype);

      منطقی save = in_late_دودویی_op;
      اگر (C_BOOLEAN_TYPE_P (type) || codel == COMPLEX_TYPE
	  || (coder == REAL_TYPE
	      && (codel == INTEGER_TYPE || codel == ENUMERAL_TYPE)
	      && sanitize_flags_p (SANITIZE_FLOAT_CAST)))
	in_late_دودویی_op = درست;
      درخت ret = convert_and_check (عبارت_loc != UNKNOWN_LOCATION
				    ? عبارت_loc : location, type, orig_rhs,
				    errtype == ic_init_const);
      in_late_دودویی_op = save;
      بازگشت ret;
    }

  /* Aggregates in different TUs might need conversion.  */
  اگر ((codel == RECORD_TYPE || codel == UNION_TYPE)
      && codel == coder
      && comptypes (TYPE_MAIN_VARIANT (type), TYPE_MAIN_VARIANT (rhstype)))
    بازگشت convert_and_check (عبارت_loc != UNKNOWN_LOCATION
			      ? عبارت_loc : location, type, rhs);

  /* Conversion to a transparent union or record from its member types.
     This applies only to function arguments.  */
  اگر (((codel == UNION_TYPE || codel == RECORD_TYPE)
      && TYPE_TRANSPARENT_AGGR (type))
      && errtype == ic_argpass)
    {
      درخت memb, marginal_memb = NULL_درخت;

      برای (memb = TYPE_FIELDS (type); memb ; memb = DECL_CHAIN (memb))
	{
	  درخت memb_type = درخت_TYPE (memb);

	  اگر (comptypes (TYPE_MAIN_VARIANT (memb_type),
			 TYPE_MAIN_VARIANT (rhstype)))
	    بشکن;

	  اگر (درخت_CODE (memb_type) != POINTER_TYPE)
	    ادامه;

	  اگر (coder == POINTER_TYPE)
	    {
	      درخت ttl = درخت_TYPE (memb_type);
	      درخت ttr = درخت_TYPE (rhstype);

	      /* Any non-function converts to a [const][volatile] void *
		 and vice versa; otherwise, targets must be the same.
		 Meanwhile, the lhs target must have all the qualifiers of
		 the rhs.  */
	      اگر ((VOID_TYPE_P (ttl) && !TYPE_ATOMIC (ttl))
		  || (VOID_TYPE_P (ttr) && !TYPE_ATOMIC (ttr))
		  || comp_target_types (location, memb_type, rhstype))
		{
		  صحیح lquals = TYPE_QUALS (ttl) & ~TYPE_QUAL_ATOMIC;
		  صحیح rquals = TYPE_QUALS (ttr) & ~TYPE_QUAL_ATOMIC;
		  /* If this type won't generate any warnings, use it.  */
		  اگر (lquals == rquals
		      || ((درخت_CODE (ttr) == FUNCTION_TYPE
			   && درخت_CODE (ttl) == FUNCTION_TYPE)
			  ? ((lquals | rquals) == rquals)
			  : ((lquals | rquals) == lquals)))
		    بشکن;

		  /* Keep looking for a better type, but remember this one.  */
		  اگر (!marginal_memb)
		    marginal_memb = memb;
		}
	    }

	  /* Can convert integer zero to any pointer type.  */
	  اگر (null_pointer_constant)
	    {
	      rhs = null_pointer_گره;
	      بشکن;
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
	      اگر (درخت_CODE (ttr) == FUNCTION_TYPE
		  && درخت_CODE (ttl) == FUNCTION_TYPE)
		{
		  /* Because const and volatile on functions are
		     restrictions that say the function will not do
		     certain things, it is okay to use a const or volatile
		     function where an ordinary one is wanted, but not
		     vice-versa.  */
		  اگر (TYPE_QUALS_NO_ADDR_SPACE (ttl)
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
	      وگرنه اگر (TYPE_QUALS_NO_ADDR_SPACE (ttr)
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

	  اگر (!fundecl || !DECL_IN_SYSTEM_HEADER (fundecl))
	    pedwarn (location, OPT_Wpedantic,
		     "ISO C prohibits argument conversion to union type");

	  rhs = fold_convert_loc (location, درخت_TYPE (memb), rhs);
	  بازگشت build_constructor_single (type, memb, rhs);
	}
    }

  /* Conversions among pointers */
  وگرنه اگر ((codel == POINTER_TYPE || codel == REFERENCE_TYPE)
	   && (coder == codel))
    {
      /* If RHS refers to a built-in declared without a prototype
	 BLTIN is the declaration of the built-in with a prototype
	 and RHSTYPE is set to the actual type of the built-in.  */
      درخت bltin;
      rhstype = type_or_builtin_type (rhs, &bltin);

      درخت ttl = درخت_TYPE (type);
      درخت ttr = درخت_TYPE (rhstype);
      منطقی is_opaque_pointer;
      منطقی target_cmp = نادرست;   /* Cache comp_target_types () result.  */
      addr_space_t asl;
      addr_space_t asr;

      درخت mvl = remove_qualifiers (ttl);
      درخت mvr = remove_qualifiers (ttr);

      /* Opaque pointers are treated like void pointers.  */
      is_opaque_pointer = vector_targets_convertible_p (ttl, ttr);

      /* The Plan 9 compiler permits a pointer to a struct to be
	 automatically converted into a pointer to an anonymous field
	 within the struct.  */
      اگر (flag_plan9_extensions
	  && RECORD_OR_UNION_TYPE_P (mvl)
	  && RECORD_OR_UNION_TYPE_P (mvr)
	  && mvl != mvr)
	{
	  درخت new_rhs = convert_to_anonymous_field (location, type, rhs);
	  اگر (new_rhs != NULL_درخت)
	    {
	      rhs = new_rhs;
	      rhstype = درخت_TYPE (rhs);
	      coder = درخت_CODE (rhstype);
	      ttr = درخت_TYPE (rhstype);
	      mvr = TYPE_MAIN_VARIANT (ttr);
	    }
	}

      /* C++ does not allow the implicit conversion void* -> T*.  However,
	 for the purpose of reducing the number of false positives, we
	 tolerate the special case of

		int *p = NULL;

	 where NULL is typically defined in C to be '(void *) 0'.  */
      اگر (VOID_TYPE_P (ttr) && rhs != null_pointer_گره && !VOID_TYPE_P (ttl))
	warning_at (errtype == ic_argpass ? عبارت_loc : location,
		    OPT_Wc___compat,
		    "request for implicit conversion "
		    "from %qT to %qT not permitted in C++", rhstype, type);

      /* Warn of new allocations that are not big enough for the target
	 type.  */
      اگر (warn_alloc_size && درخت_CODE (rhs) == CALL_عبارت)
	اگر (درخت fndecl = get_callee_fndecl (rhs))
	  اگر (DECL_IS_MALLOC (fndecl))
	    {
	      درخت attrs = TYPE_ATTRIBUTES (درخت_TYPE (fndecl));
	      درخت alloc_size = lookup_attribute ("alloc_size", attrs);
	      اگر (alloc_size)
		warn_for_alloc_size (location, ttl, rhs, alloc_size);
	    }

      /* See if the pointers point to incompatible address spaces.  */
      asl = TYPE_ADDR_SPACE (ttl);
      asr = TYPE_ADDR_SPACE (ttr);
      اگر (!null_pointer_constant_p (rhs)
	  && asr != asl && !targetm.addr_space.subset_p (asr, asl))
	{
	  auto_diagnostic_group d;
	  منطقی diagnosed = درست;
	  انتخاب (errtype)
	    {
	    حالت ic_argpass:
	      {
		ثابت نویسه پیام[] = G_("passing argument %d of %qE from "
				      "pointer to non-enclosed address space");
		اگر (warnopt)
		  diagnosed
		    = warning_at (عبارت_loc, warnopt, پیام, parmnum, rname);
		وگرنه
		  error_at (عبارت_loc, پیام, parmnum, rname);
	      بشکن;
	      }
	    حالت ic_assign:
	      {
		ثابت نویسه پیام[] = G_("assignment from pointer to "
				      "non-enclosed address space");
		اگر (warnopt)
		  diagnosed = warning_at (location, warnopt, پیام);
		وگرنه
		  error_at (location, پیام);
		بشکن;
	      }
	    حالت ic_init:
	    حالت ic_init_const:
	      {
		ثابت نویسه پیام[] = G_("initialization from pointer to "
				      "non-enclosed address space");
		اگر (warnopt)
		  diagnosed = warning_at (location, warnopt, پیام);
		وگرنه
		  error_at (location, پیام);
		بشکن;
	      }
	    حالت ic_return:
	      {
		ثابت نویسه پیام[] = G_("return from pointer to "
				      "non-enclosed address space");
		اگر (warnopt)
		  diagnosed = warning_at (location, warnopt, پیام);
		وگرنه
		  error_at (location, پیام);
		بشکن;
	      }
	    پیشفرض:
	      gcc_unreachable ();
	    }
	  اگر (diagnosed)
	    {
	      اگر (errtype == ic_argpass)
		inform_for_arg (fundecl, عبارت_loc, parmnum, type, rhstype);
	      وگرنه
		inform (location, "expected %qT but pointer is of type %qT",
			type, rhstype);
	    }
	  بازگشت error_mark_گره;
	}

      /* Check if the right-hand side has a format attribute but the
	 left-hand side doesn't.  */
      اگر (warn_suggest_attribute_format
	  && check_missing_format_attribute (type, rhstype))
	{
	  انتخاب (errtype)
	  {
	  حالت ic_argpass:
	    warning_at (عبارت_loc, OPT_Wsuggest_attribute_format,
			"argument %d of %qE might be "
			"a candidate for a format attribute",
			parmnum, rname);
	    بشکن;
	  حالت ic_assign:
	    warning_at (location, OPT_Wsuggest_attribute_format,
			"assignment left-hand side might be "
			"a candidate for a format attribute");
	    بشکن;
	  حالت ic_init:
	  حالت ic_init_const:
	    warning_at (location, OPT_Wsuggest_attribute_format,
			"initialization left-hand side might be "
			"a candidate for a format attribute");
	    بشکن;
	  حالت ic_return:
	    warning_at (location, OPT_Wsuggest_attribute_format,
			"return type might be "
			"a candidate for a format attribute");
	    بشکن;
	  پیشفرض:
	    gcc_unreachable ();
	  }
	}

      /* See if the pointers point to incompatible scalar storage orders.  */
      اگر (warn_scalar_storage_order
	  && !null_pointer_constant_p (rhs)
	  && (AGGREGATE_TYPE_P (ttl) && TYPE_REVERSE_STORAGE_ORDER (ttl))
	     != (AGGREGATE_TYPE_P (ttr) && TYPE_REVERSE_STORAGE_ORDER (ttr)))
	{
	  درخت t;

	  انتخاب (errtype)
	  {
	  حالت ic_argpass:
	    /* Do not warn for built-in functions, for example memcpy, since we
	       control how they behave and they can be useful in this area.  */
	    اگر (درخت_CODE (rname) != FUNCTION_DECL
		|| !fndecl_built_in_p (rname))
	      warning_at (location, OPT_Wscalar_storage_order,
			  "passing argument %d of %qE from incompatible "
			  "scalar storage order", parmnum, rname);
	    بشکن;
	  حالت ic_assign:
	    /* Do not warn if the RHS is a call to a function that returns a
	       pointer that is not an alias.  */
	    اگر (درخت_CODE (rhs) != CALL_عبارت
		|| (t = get_callee_fndecl (rhs)) == NULL_درخت
		|| !DECL_IS_MALLOC (t))
	      warning_at (location, OPT_Wscalar_storage_order,
			  "assignment to %qT from pointer type %qT with "
			  "incompatible scalar storage order", type, rhstype);
	    بشکن;
	  حالت ic_init:
	  حالت ic_init_const:
	    /* Likewise.  */
	    اگر (درخت_CODE (rhs) != CALL_عبارت
		|| (t = get_callee_fndecl (rhs)) == NULL_درخت
		|| !DECL_IS_MALLOC (t))
	      warning_at (location, OPT_Wscalar_storage_order,
			  "initialization of %qT from pointer type %qT with "
			  "incompatible scalar storage order", type, rhstype);
	    بشکن;
	  حالت ic_return:
	    warning_at (location, OPT_Wscalar_storage_order,
			"returning %qT from pointer type with incompatible "
			"scalar storage order %qT", rhstype, type);
	    بشکن;
	  پیشفرض:
	    gcc_unreachable ();
	  }
	}

      /* Any non-function converts to a [const][volatile] void *
	 and vice versa; otherwise, targets must be the same.
	 Meanwhile, the lhs target must have all the qualifiers of the rhs.  */
      اگر ((VOID_TYPE_P (ttl) && !TYPE_ATOMIC (ttl))
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
	  اگر (درخت_CODE (ttr) == ARRAY_TYPE)
	    {
	      ttr = strip_array_types (ttr);
	      ttl = strip_array_types (ttl);

	      اگر (TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttr)
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
          وگرنه اگر (pedantic
	      && ((VOID_TYPE_P (ttl) && درخت_CODE (ttr) == FUNCTION_TYPE)
		  ||
		  (VOID_TYPE_P (ttr)
		   && !null_pointer_constant
		   && درخت_CODE (ttl) == FUNCTION_TYPE)))
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
	  وگرنه اگر (درخت_CODE (ttr) != FUNCTION_TYPE
		   && درخت_CODE (ttl) != FUNCTION_TYPE)
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
	      وگرنه اگر (warn_quals_ped)
		pedwarn_c11 (location, OPT_Wc11_c23_compat,
			     "array with qualifier on the element is not qualified before C23");

	      /* If this is not a case of ignoring a mismatch in signedness,
		 no warning.  */
	      وگرنه اگر (VOID_TYPE_P (ttl) || VOID_TYPE_P (ttr)
		       || target_cmp)
		;
	      /* If there is a mismatch, do warn.  */
	      وگرنه اگر (warn_pointer_sign)
		انتخاب (errtype)
		  {
		  حالت ic_argpass:
		    {
		      auto_diagnostic_group d;
		      range_label_for_type_mismatch rhs_label (rhstype, type);
		      gcc_rich_location richloc (عبارت_loc, &rhs_label,
						 highlight_colors::actual);
		      اگر (pedwarn (&richloc, OPT_Wpointer_sign,
				   "pointer targets in passing argument %d of "
				   "%qE differ in signedness", parmnum, rname))
			inform_for_arg (fundecl, عبارت_loc, parmnum, type,
					rhstype);
		    }
		    بشکن;
		  حالت ic_assign:
		    pedwarn (location, OPT_Wpointer_sign,
			     "pointer targets in assignment from %qT to %qT "
			     "differ in signedness", rhstype, type);
		    بشکن;
		  حالت ic_init:
		  حالت ic_init_const:
		    pedwarn_init (location, OPT_Wpointer_sign,
				  "pointer targets in initialization of %qT "
				  "from %qT differ in signedness", type,
				  rhstype);
		    بشکن;
		  حالت ic_return:
		    pedwarn (location, OPT_Wpointer_sign, "pointer targets in "
			     "returning %qT from a function with return type "
			     "%qT differ in signedness", rhstype, type);
		    بشکن;
		  پیشفرض:
		    gcc_unreachable ();
		  }
	    }
	  وگرنه اگر (درخت_CODE (ttl) == FUNCTION_TYPE
		   && درخت_CODE (ttr) == FUNCTION_TYPE)
	    {
	      /* Because const and volatile on functions are restrictions
		 that say the function will not do certain things,
		 it is okay to use a const or volatile function
		 where an ordinary one is wanted, but not vice-versa.  */
	      اگر (TYPE_QUALS_NO_ADDR_SPACE (ttl)
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
      وگرنه اگر (!objc_ok)
	{
	  auto_diagnostic_group d;
	  منطقی warned = نادرست;
	  pp_markup::element_expected_type e_type (type);
	  pp_markup::element_actual_type e_rhstype (rhstype);
	  انتخاب (errtype)
	    {
	    حالت ic_argpass:
	      {
		range_label_for_type_mismatch rhs_label (rhstype, type);
		gcc_rich_location richloc (عبارت_loc, &rhs_label,
					   highlight_colors::actual);
		warned
		  = permerror_opt (&richloc, OPT_Wincompatible_pointer_types,
				   "passing argument %d of %qE from "
				   "incompatible pointer type",
				   parmnum, rname);
		اگر (warned)
		  inform_for_arg (fundecl, عبارت_loc, parmnum, type, rhstype);
	      }
	      بشکن;
	    حالت ic_assign:
	      اگر (bltin)
		warned
		  = permerror_opt (location, OPT_Wincompatible_pointer_types,
				   "assignment to %e from pointer to "
				   "%qD with incompatible type %e",
				   &e_type, bltin, &e_rhstype);
	      وگرنه
		warned
		  = permerror_opt (location, OPT_Wincompatible_pointer_types,
				   "assignment to %e from incompatible "
				   "pointer type %e",
				   &e_type, &e_rhstype);
	      بشکن;
	    حالت ic_init:
	    حالت ic_init_const:
	      اگر (bltin)
		warned
		  = permerror_init (location, OPT_Wincompatible_pointer_types,
				    "initialization of %e from pointer to "
				    "%qD with incompatible type %e",
				    &e_type, bltin, &e_rhstype);
	      وگرنه
		warned
		  = permerror_init (location, OPT_Wincompatible_pointer_types,
				    "initialization of %e from incompatible "
				    "pointer type %e",
				    &e_type, &e_rhstype);
	      بشکن;
	    حالت ic_return:
	      اگر (bltin)
		warned
		  = permerror_opt (location, OPT_Wincompatible_pointer_types,
				   "returning pointer to %qD of type %e from "
				   "a function with incompatible type %e",
				   bltin, &e_rhstype, &e_type);
	      وگرنه
		warned
		  = permerror_opt (location, OPT_Wincompatible_pointer_types,
				   "returning %e from a function with "
				   "incompatible return type %e",
				   &e_rhstype, &e_type);
	      بشکن;
	    پیشفرض:
	      gcc_unreachable ();
	    }
	  اگر (warned)
	    {
	      /* If the mismatching function type is a pointer to a function,
		 try to show the decl of the function.  */
	      اگر (درخت_CODE (rhs) == ADDR_عبارت
		  && درخت_CODE (درخت_OPERAND (rhs, 0)) == FUNCTION_DECL)
		{
		  درخت rhs_fndecl = درخت_OPERAND (rhs, 0);
		  اگر (!DECL_IS_UNDECLARED_BUILTIN (rhs_fndecl))
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

      بازگشت convert (type, rhs);
    }
  وگرنه اگر (codel == POINTER_TYPE && coder == ARRAY_TYPE)
    {
      /* ??? This should not be an error when inlining calls to
	 unprototyped functions.  */
      ثابت نویسه پیام[] = "invalid use of non-lvalue array";
      اگر (warnopt)
	warning_at (location, warnopt, پیام);
      وگرنه
	error_at (location, پیام);
      بازگشت error_mark_گره;
    }
  وگرنه اگر (codel == POINTER_TYPE
	   && (coder == INTEGER_TYPE
	       || coder == ENUMERAL_TYPE
	       || coder == BOOLEAN_TYPE
	       || coder == NULLPTR_TYPE
	       || coder == BITINT_TYPE))
    {
      اگر (null_pointer_constant && c_inhibit_evaluation_warnings == 0
	  && coder != NULLPTR_TYPE)
	warning_at (location, OPT_Wzero_as_null_pointer_constant,
		    "zero as null pointer constant");
      /* A NULLPTR type is just a nullptr always.  */
      اگر (coder == NULLPTR_TYPE)
	بازگشت omit_one_operand_loc (عبارت_loc, type, nullptr_گره, rhs);
      /* An explicit constant 0 or type nullptr_t can convert to a pointer,
	 or one that results from arithmetic, even including a cast to
	 integer type.  */
      وگرنه اگر (!null_pointer_constant)
	انتخاب (errtype)
	  {
	  حالت ic_argpass:
	    {
	      auto_diagnostic_group d;
	      range_label_for_type_mismatch rhs_label (rhstype, type);
	      gcc_rich_location richloc (عبارت_loc, &rhs_label,
					 highlight_colors::actual);
	      اگر (permerror_opt (&richloc, OPT_Wint_conversion,
				 "passing argument %d of %qE makes pointer "
				 "from integer without a cast", parmnum, rname))
		{
		  maybe_emit_indirection_note (عبارت_loc, rhs, type);
		  inform_for_arg (fundecl, عبارت_loc, parmnum, type, rhstype);
		}
	    }
	    بشکن;
	  حالت ic_assign:
	    permerror_opt (location, OPT_Wint_conversion,
			   "assignment to %qT from %qT makes pointer from "
			   "integer without a cast", type, rhstype);
	    بشکن;
	  حالت ic_init:
	  حالت ic_init_const:
	    permerror_init (location, OPT_Wint_conversion,
			    "initialization of %qT from %qT makes pointer "
			    "from integer without a cast", type, rhstype);
	    بشکن;
	  حالت ic_return:
	    permerror_init (location, OPT_Wint_conversion,
			    "returning %qT from a function with return type "
			    "%qT makes pointer from integer without a cast",
			    rhstype, type);
	    بشکن;
	  پیشفرض:
	    gcc_unreachable ();
	  }

      بازگشت convert (type, rhs);
    }
  وگرنه اگر ((codel == INTEGER_TYPE || codel == BITINT_TYPE)
	   && coder == POINTER_TYPE)
    {
      انتخاب (errtype)
	{
	حالت ic_argpass:
	  {
	    auto_diagnostic_group d;
	    range_label_for_type_mismatch rhs_label (rhstype, type);
	    gcc_rich_location richloc (عبارت_loc, &rhs_label,
				       highlight_colors::actual);
	    اگر (permerror_opt (&richloc, OPT_Wint_conversion,
			       "passing argument %d of %qE makes integer from "
			       "pointer without a cast", parmnum, rname))
	      {
		maybe_emit_indirection_note (عبارت_loc, rhs, type);
		inform_for_arg (fundecl, عبارت_loc, parmnum, type, rhstype);
	      }
	  }
	  بشکن;
	حالت ic_assign:
	  permerror_opt (location, OPT_Wint_conversion,
			 "assignment to %qT from %qT makes integer from "
			 "pointer without a cast", type, rhstype);
	  بشکن;
	حالت ic_init:
	حالت ic_init_const:
	  permerror_init (location, OPT_Wint_conversion,
			  "initialization of %qT from %qT makes integer "
			  "from pointer without a cast", type, rhstype);
	  بشکن;
	حالت ic_return:
	  permerror_opt (location, OPT_Wint_conversion, "returning %qT from a "
			 "function with return type %qT makes integer from "
			 "pointer without a cast", rhstype, type);
	  بشکن;
	پیشفرض:
	  gcc_unreachable ();
	}

      بازگشت convert (type, rhs);
    }
  وگرنه اگر (C_BOOLEAN_TYPE_P (type)
	   /* The type nullptr_t may be converted to bool.  The
	      result is false.  */
	   && (coder == POINTER_TYPE || coder == NULLPTR_TYPE))
    {
      درخت ret;
      منطقی save = in_late_دودویی_op;
      in_late_دودویی_op = درست;
      ret = convert (type, rhs);
      in_late_دودویی_op = save;
      بازگشت ret;
    }
  وگرنه اگر (codel == NULLPTR_TYPE && null_pointer_constant)
    بازگشت convert (type, rhs);

  انتخاب (errtype)
    {
    حالت ic_argpass:
      {
	auto_diagnostic_group d;
	range_label_for_type_mismatch rhs_label (rhstype, type);
	gcc_rich_location richloc (عبارت_loc, &rhs_label,
				   highlight_colors::actual);
	ثابت نویسه پیام[] = G_("incompatible type for argument %d of %qE");
	اگر (warnopt)
	  warning_at (عبارت_loc, warnopt, پیام, parmnum, rname);
	وگرنه
	  error_at (&richloc, پیام, parmnum, rname);
	inform_for_arg (fundecl, عبارت_loc, parmnum, type, rhstype);
      }
      بشکن;
    حالت ic_assign:
      {
	ثابت نویسه پیام[]
	  = G_("incompatible types when assigning to type %qT from type %qT");
	اگر (warnopt)
	  warning_at (عبارت_loc, 0, پیام, type, rhstype);
	وگرنه
	  error_at (عبارت_loc, پیام, type, rhstype);
	بشکن;
      }
    حالت ic_init:
    حالت ic_init_const:
      {
	ثابت نویسه پیام[]
	  = G_("incompatible types when initializing type %qT using type %qT");
	اگر (warnopt)
	  warning_at (location, 0, پیام, type, rhstype);
	وگرنه
	  error_at (location, پیام, type, rhstype);
	بشکن;
      }
    حالت ic_return:
      {
	ثابت نویسه پیام[]
	  = G_("incompatible types when returning type %qT but %qT was expected");
	اگر (warnopt)
	  warning_at (location, 0, پیام, rhstype, type);
	وگرنه
	  error_at (location, پیام, rhstype, type);
	بشکن;
      }
    پیشفرض:
      gcc_unreachable ();
    }

  بازگشت error_mark_گره;
}

/* If VALUE is a compound expr all of whose expressions are constant, then
   return its value.  Otherwise, return error_mark_node.

   This is for handling COMPOUND_EXPRs as initializer elements
   which is allowed with a warning when -pedantic is specified.  */

ایستا درخت
valid_compound_عبارت_initializer (درخت مقدار, درخت endtype)
{
  اگر (درخت_CODE (مقدار) == COMPOUND_عبارت)
    {
      اگر (valid_compound_عبارت_initializer (درخت_OPERAND (مقدار, 0), endtype)
	  == error_mark_گره)
	بازگشت error_mark_گره;
      بازگشت valid_compound_عبارت_initializer (درخت_OPERAND (مقدار, 1),
					      endtype);
    }
  وگرنه اگر (!initializer_constant_valid_p (مقدار, endtype))
    بازگشت error_mark_گره;
  وگرنه
    بازگشت مقدار;
}

/* Perform appropriate conversions on the initial value of a variable,
   store it in the declaration DECL,
   and print any error messages that are appropriate.
   If ORIGTYPE is not NULL_TREE, it is the original type of INIT.
   If the init is invalid, store an ERROR_MARK.

   INIT_LOC is the location of the initial value.  */

تهی
store_init_مقدار (location_t init_loc, درخت decl, درخت init, درخت origtype)
{
  درخت مقدار, type;
  منطقی npc = نادرست;
  منطقی int_const_عبارت = نادرست;
  منطقی arith_const_عبارت = نادرست;

  /* If variable's type was invalidly declared, just ignore it.  */

  type = درخت_TYPE (decl);
  اگر (درخت_CODE (type) == ERROR_MARK)
    بازگشت;

  /* Digest the specified initializer into an expression.  */

  اگر (init)
    {
      npc = null_pointer_constant_p (init);
      int_const_عبارت = (درخت_CODE (init) == INTEGER_CST
			&& !درخت_OVERFLOW (init)
			&& INTEGRAL_TYPE_P (درخت_TYPE (init)));
      /* Not fully determined before folding.  */
      arith_const_عبارت = درست;
    }
  منطقی constexpr_p = (VAR_P (decl)
		      && C_DECL_DECLARED_CONSTEXPR (decl));
  مقدار = digest_init (init_loc, decl, type, init, origtype, npc,
		       int_const_عبارت, arith_const_عبارت, درست,
		       درخت_STATIC (decl) || constexpr_p, constexpr_p);

  /* Store the expression if valid; else report error.  */

  اگر (!in_system_header_at (درون_داد_location)
      && AGGREGATE_TYPE_P (درخت_TYPE (decl)) && !درخت_STATIC (decl))
    warning (OPT_Wtraditional, "traditional C rejects automatic "
	     "aggregate initialization");

  اگر (مقدار != error_mark_گره || درخت_CODE (decl) != FUNCTION_DECL)
    DECL_INITIAL (decl) = مقدار;

  /* ANSI wants warnings about out-of-range constant initializers.  */
  STRIP_TYPE_NOPS (مقدار);
  اگر (درخت_STATIC (decl))
    constant_expression_warning (مقدار);

  /* Check if we need to set array size from compound literal size.  */
  اگر (درخت_CODE (type) == ARRAY_TYPE
      && TYPE_DOMAIN (type) == NULL_درخت
      && مقدار != error_mark_گره)
    {
      درخت inside_init = init;

      STRIP_TYPE_NOPS (inside_init);
      inside_init = fold (inside_init);

      اگر (درخت_CODE (inside_init) == COMPOUND_LITERAL_عبارت)
	{
	  درخت cldecl = COMPOUND_LITERAL_عبارت_DECL (inside_init);

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

ساختار spelling
{
  صحیح kind;
  اجتماع
    {
      unsigned HOST_WIDE_INT i;
      ثابت نویسه *s;
    } u;
};

#define SPELLING_STRING 1
#define SPELLING_MEMBER 2
#define SPELLING_BOUNDS 3

ایستا ساختار spelling *spelling;	/* Next stack element (unused).  */
ایستا ساختار spelling *spelling_base;	/* Spelling stack base.  */
ایستا صحیح spelling_size;		/* Size of the spelling stack.  */

/* Macros to save and restore the spelling stack around push_... functions.
   Alternative to SAVE_SPELLING_STACK.  */

#define SPELLING_DEPTH() (spelling - spelling_base)
#define RESTORE_SPELLING_DEPTH(DEPTH) (spelling = spelling_base + (DEPTH))

/* Push an element on the spelling stack with type KIND and assign VALUE
   to MEMBER.  */

#define افزودن_SPELLING(KIND, مقدار_2, MEMBER)				\
{									\
  صحیح depth = SPELLING_DEPTH ();					\
									\
  اگر (depth >= spelling_size)						\
    {									\
      spelling_size += 10;						\
      spelling_base = XRESIZEVEC (ساختار spelling, spelling_base,	\
				  spelling_size);			\
      RESTORE_SPELLING_DEPTH (depth);					\
    }									\
									\
  spelling->kind = (KIND);						\
  spelling->MEMBER = (مقدار_2);						\
  spelling++;								\
}

/* Push STRING on the stack.  Printed literally.  */

ایستا تهی
افزودن_string (ثابت نویسه *string)
{
  افزودن_SPELLING (SPELLING_STRING, string, u.s);
}

/* Push a member name on the stack.  Printed as '.' STRING.  */

ایستا تهی
افزودن_member_name (درخت decl)
{
  ثابت نویسه *ثابت string
    = (DECL_NAME (decl)
       ? identifier_to_locale (IDENTIFIER_POINTER (DECL_NAME (decl)))
       : _("<anonymous>"));
  افزودن_SPELLING (SPELLING_MEMBER, string, u.s);
}

/* Push an array bounds on the stack.  Printed as [BOUNDS].  */

ایستا تهی
افزودن_array_bounds (unsigned HOST_WIDE_INT bounds)
{
  افزودن_SPELLING (SPELLING_BOUNDS, bounds, u.i);
}

/* Compute the maximum size in bytes of the printed spelling.  */

ایستا صحیح
spelling_length (تهی)
{
  صحیح size = 0;
  ساختار spelling *p;

  برای (p = spelling_base; p < spelling; p++)
    {
      اگر (p->kind == SPELLING_BOUNDS)
	size += 25;
      وگرنه
	size += strlen (p->u.s) + 1;
    }

  بازگشت size;
}

/* Print the spelling to BUFFER and return it.  */

ایستا نویسه *
print_spelling (نویسه *buffer)
{
  نویسه *d = buffer;
  ساختار spelling *p;

  برای (p = spelling_base; p < spelling; p++)
    اگر (p->kind == SPELLING_BOUNDS)
      {
	sprintf (d, "[" HOST_WIDE_INT_PRINT_UNSIGNED "]", p->u.i);
	d += strlen (d);
      }
    وگرنه
      {
	ثابت نویسه *s;
	اگر (p->kind == SPELLING_MEMBER)
	  *d++ = '.';
	برای (s = p->u.s; (*d = *s++); d++)
	  ;
      }
  *d++ = '\0';
  بازگشت buffer;
}

/* Check whether INIT, a floating or integer constant, is
   representable in TYPE, a real floating type with the same radix or
   a decimal floating type initialized with a binary floating
   constant.  Return true if OK, false if not.  */
ایستا منطقی
constexpr_init_fits_real_type (درخت type, درخت init)
{
  gcc_assert (SCALAR_FLOAT_TYPE_P (type));
  gcc_assert (درخت_CODE (init) == INTEGER_CST || درخت_CODE (init) == REAL_CST);
  اگر (درخت_CODE (init) == REAL_CST
      && TYPE_MODE (درخت_TYPE (init)) == TYPE_MODE (type))
    {
      /* Same mode, no conversion required except for the case of
	 signaling NaNs if the types are incompatible (e.g. double and
	 long double with the same mode).  */
      اگر (REAL_مقدار_ISSIGNALING_NAN (درخت_REAL_CST (init))
	  && !comptypes (TYPE_MAIN_VARIANT (type),
			 TYPE_MAIN_VARIANT (درخت_TYPE (init))))
	بازگشت نادرست;
      بازگشت درست;
    }
  اگر (درخت_CODE (init) == INTEGER_CST)
    {
      درخت converted = build_real_from_int_cst (type, init);
      منطقی fail = نادرست;
      wide_int w = real_to_integer (&درخت_REAL_CST (converted), &fail,
				    TYPE_PRECISION (درخت_TYPE (init)));
      بازگشت !fail && wi::eq_p (w, wi::to_wide (init));
    }
  اگر (REAL_مقدار_ISSIGNALING_NAN (درخت_REAL_CST (init)))
    بازگشت نادرست;
  اگر ((REAL_مقدار_ISINF (درخت_REAL_CST (init))
       && MODE_HAS_INFINITIES (TYPE_MODE (type)))
      || (REAL_مقدار_ISNAN (درخت_REAL_CST (init))
	  && MODE_HAS_NANS (TYPE_MODE (type))))
    بازگشت درست;
  اگر (DECIMAL_FLOAT_TYPE_P (type)
      && !DECIMAL_FLOAT_TYPE_P (درخت_TYPE (init)))
    {
      /* This is valid if the real number represented by the
	 initializer can be exactly represented in the decimal
	 type.  Compare the values using MPFR.  */
      REAL_مقدار_TYPE t;
      real_convert (&t, TYPE_MODE (type), &درخت_REAL_CST (init));
      mpfr_t bin_val, dec_val;
      mpfr_init2 (bin_val, REAL_MODE_FORMAT (TYPE_MODE (درخت_TYPE (init)))->p);
      mpfr_init2 (dec_val, REAL_MODE_FORMAT (TYPE_MODE (درخت_TYPE (init)))->p);
      mpfr_from_real (bin_val, &درخت_REAL_CST (init), MPFR_RNDN);
      نویسه string[256];
      real_to_decimal (string, &t, اندازه string, 0, 1);
      منطقی res = (mpfr_strtofr (dec_val, string, پوچ, 10, MPFR_RNDN) == 0
		  && mpfr_equal_p (bin_val, dec_val));
      mpfr_clear (bin_val);
      mpfr_clear (dec_val);
      بازگشت res;
    }
  /* exact_real_truncate is not quite right here, since it doesn't
     allow even an exact conversion to subnormal values.  */
  REAL_مقدار_TYPE t;
  real_convert (&t, TYPE_MODE (type), &درخت_REAL_CST (init));
  بازگشت real_identical (&t, &درخت_REAL_CST (init));
}

/* Check whether INIT (location LOC) is valid as a 'constexpr'
   initializer for type TYPE, and give an error if not.  INIT has
   already been folded and verified to be constant.  INT_CONST_EXPR
   and ARITH_CONST_EXPR say whether it is an integer constant
   expression or arithmetic constant expression, respectively.  If
   TYPE is not a scalar type, this function does nothing.  */

ایستا تهی
check_constexpr_init (location_t loc, درخت type, درخت init,
		      منطقی int_const_عبارت, منطقی arith_const_عبارت)
{
  اگر (POINTER_TYPE_P (type))
    {
      /* The initializer must be null.  */
      اگر (درخت_CODE (init) != INTEGER_CST || !integer_zerop (init))
	error_at (loc, "%<constexpr%> pointer initializer is not null");
      بازگشت;
    }
  اگر (INTEGRAL_TYPE_P (type))
    {
      /* The initializer must be an integer constant expression,
	 representable in the target type.  */
      اگر (!int_const_عبارت)
	{
	  اگر (درخت_CODE (init) == RAW_DATA_CST
	      && TYPE_PRECISION (type) == CHAR_BIT)
	    {
	      اگر (!TYPE_UNSIGNED (type))
		برای (unsigned صحیح i = 0;
		     i < (unsigned) RAW_DATA_LENGTH (init); ++i)
		  اگر (RAW_DATA_SCHAR_ELT (init, i) < 0)
		    {
		      error_at (loc, "%<constexpr%> initializer not "
				"representable in type of object");
		      بشکن;
		    }
	    }
	  وگرنه
	    error_at (loc, "%<constexpr%> integer initializer is not an "
		      "integer constant expression");
	}
      وگرنه اگر (!int_fits_type_p (init, type))
	error_at (loc, "%<constexpr%> initializer not representable in "
		  "type of object");
      بازگشت;
    }
  /* We don't apply any extra checks to extension types such as vector
     or fixed-point types.  */
  اگر (درخت_CODE (type) != REAL_TYPE && درخت_CODE (type) != COMPLEX_TYPE)
    بازگشت;
  اگر (!arith_const_عبارت)
    {
      error_at (loc, "%<constexpr%> initializer is not an arithmetic "
		"constant expression");
      بازگشت;
    }
  /* We don't apply any extra checks to complex integers.  */
  اگر (درخت_CODE (type) == COMPLEX_TYPE
      && درخت_CODE (درخت_TYPE (type)) != REAL_TYPE)
    بازگشت;
  /* Following N3082, a real type cannot be initialized from a complex
     type and a binary type cannot be initialized from a decimal type
     (but initializing a decimal type from a binary type is OK).
     Signaling NaN initializers are OK only if the types are
     compatible (not just the same mode); all quiet NaN and infinity
     initializations are considered to preserve the value.  */
  اگر (درخت_CODE (درخت_TYPE (init)) == COMPLEX_TYPE
      && SCALAR_FLOAT_TYPE_P (type))
    {
      error_at (loc, "%<constexpr%> initializer for a real type is of "
		"complex type");
      بازگشت;
    }
  اگر (SCALAR_FLOAT_TYPE_P (type)
      && SCALAR_FLOAT_TYPE_P (درخت_TYPE (init))
      && DECIMAL_FLOAT_TYPE_P (درخت_TYPE (init))
      && !DECIMAL_FLOAT_TYPE_P (type))
    {
      error_at (loc, "%<constexpr%> initializer for a binary "
		"floating-point type is of decimal type");
      بازگشت;
    }
  منطقی fits;
  اگر (درخت_CODE (type) == COMPLEX_TYPE)
    {
      انتخاب (درخت_CODE (init))
	{
	حالت INTEGER_CST:
	حالت REAL_CST:
	  fits = constexpr_init_fits_real_type (درخت_TYPE (type), init);
	  بشکن;
	حالت COMPLEX_CST:
	  fits = (constexpr_init_fits_real_type (درخت_TYPE (type),
						 درخت_REALPART (init))
		  && constexpr_init_fits_real_type (درخت_TYPE (type),
						    درخت_IMAGPART (init)));
	  بشکن;
	پیشفرض:
	  gcc_unreachable ();
	}
    }
  وگرنه
    fits = constexpr_init_fits_real_type (type, init);
  اگر (!fits)
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

ایستا درخت
digest_init (location_t init_loc, درخت decl, درخت type, درخت init,
	     درخت origtype, منطقی null_pointer_constant, منطقی int_const_عبارت,
	     منطقی arith_const_عبارت, منطقی strict_string,
	     منطقی require_constant, منطقی require_constexpr)
{
  شمارش درخت_code code = درخت_CODE (type);
  درخت inside_init = init;
  درخت semantic_type = NULL_درخت;
  منطقی maybe_const = درست;

  اگر (type == error_mark_گره
      || !init
      || error_operand_p (init))
    بازگشت error_mark_گره;

  STRIP_TYPE_NOPS (inside_init);

  /* If require_constant is TRUE,  when the initializer is a call to
     .ACCESS_WITH_SIZE, use the first argument as the initializer.
     For example:
     y = (char *) .ACCESS_WITH_SIZE ((char *) &static_annotated.c,...)
     will be converted to
     y = &static_annotated.c.  */

  اگر (require_constant
      && درخت_CODE (inside_init) == NOP_عبارت
      && درخت_CODE (درخت_OPERAND (inside_init, 0)) == CALL_عبارت
      && is_access_with_size_p (درخت_OPERAND (inside_init, 0)))
    inside_init
      = get_ref_from_access_with_size (درخت_OPERAND (inside_init, 0));

  اگر (!c_in_omp_for)
    {
      اگر (درخت_CODE (inside_init) == EXCESS_PRECISION_عبارت)
	{
	  semantic_type = درخت_TYPE (inside_init);
	  inside_init = درخت_OPERAND (inside_init, 0);
	}
      inside_init = c_fully_fold (inside_init, require_constant, &maybe_const);
    }
  /* TODO: this may not detect all cases of expressions folding to
     constants that are not arithmetic constant expressions.  */
  اگر (!maybe_const)
    arith_const_عبارت = نادرست;
  وگرنه اگر (!INTEGRAL_TYPE_P (درخت_TYPE (inside_init))
	   && درخت_CODE (درخت_TYPE (inside_init)) != REAL_TYPE
	   && درخت_CODE (درخت_TYPE (inside_init)) != COMPLEX_TYPE)
    arith_const_عبارت = نادرست;
  وگرنه اگر (درخت_CODE (inside_init) != INTEGER_CST
	   && درخت_CODE (inside_init) != REAL_CST
	   && درخت_CODE (inside_init) != COMPLEX_CST
	   && درخت_CODE (inside_init) != RAW_DATA_CST)
    arith_const_عبارت = نادرست;
  وگرنه اگر (درخت_OVERFLOW (inside_init))
    arith_const_عبارت = نادرست;

  /* Initialization of an array of chars from a string constant
     optionally enclosed in braces.  */

  اگر (code == ARRAY_TYPE && inside_init
      && درخت_CODE (inside_init) == STRING_CST)
    {
      درخت typ1
	= (TYPE_ATOMIC (درخت_TYPE (type))
	   ? c_build_qualified_type (TYPE_MAIN_VARIANT (درخت_TYPE (type)),
				     TYPE_QUAL_ATOMIC)
	   : TYPE_MAIN_VARIANT (درخت_TYPE (type)));
      /* Note that an array could be both an array of character type
	 and an array of wchar_t if wchar_t is signed char or unsigned
	 char.  */
      منطقی char_array = (typ1 == char_type_گره
			 || typ1 == signed_char_type_گره
			 || typ1 == unsigned_char_type_گره);
      منطقی wchar_array = comptypes (typ1, wchar_type_گره);
      منطقی char16_array = comptypes (typ1, char16_type_گره);
      منطقی char32_array = comptypes (typ1, char32_type_گره);

      اگر (char_array || wchar_array || char16_array || char32_array)
	{
	  ساختار c_عبارت عبارت;
	  درخت typ2 = TYPE_MAIN_VARIANT (درخت_TYPE (درخت_TYPE (inside_init)));
	  منطقی incompat_string_cst = نادرست;
	  عبارت.مقدار = inside_init;
	  عبارت.original_code = (strict_string ? STRING_CST : ERROR_MARK);
	  عبارت.original_type = پوچ;
	  عبارت.m_decimal = 0;
	  maybe_warn_string_init (init_loc, type, عبارت);

	  اگر (flexible_array_member_type_p (type))
	    pedwarn_init (init_loc, OPT_Wpedantic,
			  "initialization of a flexible array member");

	  اگر (comptypes (TYPE_MAIN_VARIANT (درخت_TYPE (inside_init)),
			 TYPE_MAIN_VARIANT (type)))
	    بازگشت inside_init;

	  اگر (char_array)
	    {
	      اگر (typ2 != char_type_گره && typ2 != char8_type_گره)
		incompat_string_cst = درست;
	    }
	  وگرنه اگر (!comptypes (typ1, typ2))
	    incompat_string_cst = درست;

          اگر (incompat_string_cst)
            {
	      error_init (init_loc, "cannot initialize array of %qT from "
			  "a string literal with type array of %qT",
			  typ1, typ2);
	      بازگشت error_mark_گره;
            }

	  اگر (require_constexpr
	      && TYPE_UNSIGNED (typ1) != TYPE_UNSIGNED (typ2))
	    {
	      /* Check if all characters of the string can be
		 represented in the type of the constexpr object being
		 initialized.  */
	      unsigned HOST_WIDE_INT len = درخت_STRING_LENGTH (inside_init);
	      ثابت unsigned نویسه *p =
		(ثابت unsigned نویسه *) درخت_STRING_POINTER (inside_init);
	      gcc_assert (CHAR_TYPE_SIZE == 8 && CHAR_BIT == 8);
	      برای (unsigned i = 0; i < len; i++)
		اگر (p[i] > 127)
		  {
		    error_init (init_loc, "%<constexpr%> initializer not "
				"representable in type of object");
		    بشکن;
		  }
	    }

	  اگر (TYPE_DOMAIN (type) != NULL_درخت
	      && TYPE_SIZE (type) != NULL_درخت
	      && درخت_CODE (TYPE_SIZE (type)) == INTEGER_CST)
	    {
	      unsigned HOST_WIDE_INT len = درخت_STRING_LENGTH (inside_init);

	      اگر (compare_درخت_int (TYPE_SIZE_UNIT (type), len) < 0)
		{
		  unsigned HOST_WIDE_INT avail
		    = درخت_to_uhwi (TYPE_SIZE_UNIT (type));
		  unsigned unit = TYPE_PRECISION (typ1) / BITS_PER_UNIT;
		  ثابت نویسه *p = درخت_STRING_POINTER (inside_init);

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
		  وگرنه اگر (warn_cxx_compat)
		    warning_at (init_loc, OPT_Wc___compat,
				"initializer-string for array of %qT "
				"is too long for C++ (%wu chars into %wu "
				"available)", typ1, len, avail);
		  وگرنه اگر (warn_unterminated_string_initialization
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
	  بازگشت inside_init;
	}
      وگرنه اگر (INTEGRAL_TYPE_P (typ1))
	{
	  error_init (init_loc, "array of inappropriate type initialized "
		      "from string constant");
	  بازگشت error_mark_گره;
	}
    }

  /* Build a VECTOR_CST from a *constant* vector constructor.  If the
     vector constructor is not constant (e.g. {1,2,3,foo()}) then punt
     below and handle as a constructor.  */
  اگر (code == VECTOR_TYPE
      && VECTOR_TYPE_P (درخت_TYPE (inside_init))
      && vector_types_convertible_p (درخت_TYPE (inside_init), type, درست)
      && درخت_CONSTANT (inside_init))
    {
      اگر (درخت_CODE (inside_init) == VECTOR_CST
	  && comptypes (TYPE_MAIN_VARIANT (درخت_TYPE (inside_init)),
			TYPE_MAIN_VARIANT (type)))
	بازگشت inside_init;

      اگر (درخت_CODE (inside_init) == CONSTRUCTOR)
	{
	  unsigned HOST_WIDE_INT ix;
	  درخت مقدار;
	  منطقی constant_p = درست;

	  /* Iterate through elements and check if all constructor
	     elements are *_CSTs.  */
	  FOR_EACH_CONSTRUCTOR_مقدار (CONSTRUCTOR_ELTS (inside_init), ix, مقدار)
	    اگر (!CONSTANT_CLASS_P (مقدار))
	      {
		constant_p = نادرست;
		بشکن;
	      }

	  اگر (constant_p)
	    بازگشت build_vector_from_ctor (type,
					   CONSTRUCTOR_ELTS (inside_init));
	}
    }

  اگر (warn_sequence_point)
    verify_sequence_points (inside_init);

  /* Any type can be initialized
     from an expression of the same type, optionally with braces.  */

  اگر (inside_init && درخت_TYPE (inside_init) != NULL_درخت
      && (comptypes (TYPE_MAIN_VARIANT (درخت_TYPE (inside_init)),
		     TYPE_MAIN_VARIANT (type))
	  || (code == ARRAY_TYPE
	      && comptypes (درخت_TYPE (inside_init), type))
	  || (gnu_vector_type_p (type)
	      && comptypes (درخت_TYPE (inside_init), type))
	  || (code == POINTER_TYPE
	      && درخت_CODE (درخت_TYPE (inside_init)) == ARRAY_TYPE
	      && comptypes (درخت_TYPE (درخت_TYPE (inside_init)),
			    درخت_TYPE (type)))))
    {
      اگر (code == POINTER_TYPE)
	{
	  اگر (درخت_CODE (درخت_TYPE (inside_init)) == ARRAY_TYPE)
	    {
	      اگر (درخت_CODE (inside_init) == STRING_CST
		  || درخت_CODE (inside_init) == COMPOUND_LITERAL_عبارت)
		inside_init = array_to_pointer_conversion
		  (init_loc, inside_init);
	      وگرنه
		{
		  error_init (init_loc, "invalid use of non-lvalue array");
		  بازگشت error_mark_گره;
		}
	    }
	}

      اگر (code == VECTOR_TYPE || c_hardbool_type_attr (type))
	/* Although the types are compatible, we may require a
	   conversion.  */
	inside_init = convert (type, inside_init);

      اگر ((code == RECORD_TYPE || code == UNION_TYPE)
	  && !comptypes (TYPE_MAIN_VARIANT (type), TYPE_MAIN_VARIANT (درخت_TYPE (inside_init))))
	{
	  error_init (init_loc, "invalid initializer");
	  بازگشت error_mark_گره;
	}

      اگر (require_constant
	  && درخت_CODE (inside_init) == COMPOUND_LITERAL_عبارت)
	{
	  /* As an extension, allow initializing objects with static storage
	     duration with compound literals (which are then treated just as
	     the brace enclosed list they contain).  Also allow this for
	     vectors, as we can only assign them with compound literals.  */
	  اگر (flag_isoc99 && code != VECTOR_TYPE)
	    pedwarn_init (init_loc, OPT_Wpedantic, "initializer element "
			  "is not constant");
	  درخت decl = COMPOUND_LITERAL_عبارت_DECL (inside_init);
	  inside_init = DECL_INITIAL (decl);
	}

      اگر (code == ARRAY_TYPE && درخت_CODE (inside_init) != STRING_CST
	  && درخت_CODE (inside_init) != CONSTRUCTOR)
	{
	  error_init (init_loc, "array initialized from non-constant array "
		      "expression");
	  بازگشت error_mark_گره;
	}

      /* Compound expressions can only occur here if -Wpedantic or
	 -pedantic-errors is specified.  In the later case, we always want
	 an error.  In the former case, we simply want a warning.  */
      اگر (require_constant && pedantic
	  && درخت_CODE (inside_init) == COMPOUND_عبارت)
	{
	  inside_init
	    = valid_compound_عبارت_initializer (inside_init,
					       درخت_TYPE (inside_init));
	  اگر (inside_init == error_mark_گره)
	    error_init (init_loc, "initializer element is not constant");
	  وگرنه
	    pedwarn_init (init_loc, OPT_Wpedantic,
			  "initializer element is not constant");
	  اگر (flag_pedantic_errors)
	    inside_init = error_mark_گره;
	}
      وگرنه اگر (require_constant
	       && !initializer_constant_valid_p (inside_init,
						 درخت_TYPE (inside_init)))
	{
	  error_init (init_loc, "initializer element is not constant");
	  inside_init = error_mark_گره;
	}
      وگرنه اگر (require_constant && !maybe_const)
	pedwarn_init (init_loc, OPT_Wpedantic,
		      "initializer element is not a constant expression");
      وگرنه اگر (require_constexpr)
	check_constexpr_init (init_loc, type, inside_init,
			      int_const_عبارت, arith_const_عبارت);

      /* Added to enable additional -Wsuggest-attribute=format warnings.  */
      اگر (درخت_CODE (درخت_TYPE (inside_init)) == POINTER_TYPE)
	inside_init = convert_for_assignment (init_loc, UNKNOWN_LOCATION,
					      type, inside_init, origtype,
					      (require_constant
					       ? ic_init_const
					       : ic_init), null_pointer_constant,
					      NULL_درخت, NULL_درخت, 0);
      اگر (درخت_CODE (inside_init) == RAW_DATA_CST
	  && c_inhibit_evaluation_warnings == 0
	  && warn_conversion
	  && !TYPE_UNSIGNED (type)
	  && TYPE_PRECISION (type) == CHAR_BIT)
	برای (unsigned صحیح i = 0;
	     i < (unsigned) RAW_DATA_LENGTH (inside_init); ++i)
	  اگر (RAW_DATA_SCHAR_ELT (inside_init, i) < 0)
	    warning_at (init_loc, OPT_Wconversion,
			"conversion from %qT to %qT changes value from "
			"%qd to %qd",
			integer_type_گره, type,
			RAW_DATA_UCHAR_ELT (inside_init, i),
			RAW_DATA_SCHAR_ELT (inside_init, i));
      بازگشت inside_init;
    }

  /* Handle scalar types, including conversions.  */

  اگر (code == INTEGER_TYPE || code == REAL_TYPE || code == FIXED_POINT_TYPE
      || code == POINTER_TYPE || code == ENUMERAL_TYPE || code == BOOLEAN_TYPE
      || code == COMPLEX_TYPE || code == VECTOR_TYPE || code == NULLPTR_TYPE
      || code == BITINT_TYPE)
    {
      درخت unconverted_init = inside_init;
      اگر (درخت_CODE (درخت_TYPE (init)) == ARRAY_TYPE
	  && (درخت_CODE (init) == STRING_CST
	      || درخت_CODE (init) == COMPOUND_LITERAL_عبارت))
	inside_init = init = array_to_pointer_conversion (init_loc, init);
      اگر (semantic_type)
	inside_init = build1 (EXCESS_PRECISION_عبارت, semantic_type,
			      inside_init);
      inside_init
	= convert_for_assignment (init_loc, UNKNOWN_LOCATION, type,
				  inside_init, origtype,
				  require_constant ? ic_init_const : ic_init,
				  null_pointer_constant, NULL_درخت, NULL_درخت,
				  0);

      /* Check to see if we have already given an error message.  */
      اگر (inside_init == error_mark_گره)
	;
      وگرنه اگر (require_constant && !درخت_CONSTANT (inside_init))
	{
	  error_init (init_loc, "initializer element is not constant");
	  inside_init = error_mark_گره;
	}
      وگرنه اگر (require_constant
	       && !initializer_constant_valid_p (inside_init,
						 درخت_TYPE (inside_init)))
	{
	  error_init (init_loc, "initializer element is not computable at "
		      "load time");
	  inside_init = error_mark_گره;
	}
      وگرنه اگر (require_constant && !maybe_const)
	pedwarn_init (init_loc, OPT_Wpedantic,
		      "initializer element is not a constant expression");
      وگرنه اگر (require_constexpr)
	check_constexpr_init (init_loc, type, unconverted_init,
			      int_const_عبارت, arith_const_عبارت);

      بازگشت inside_init;
    }

  /* Come here only for records and arrays.  */

  اگر (COMPLETE_TYPE_P (type) && درخت_CODE (TYPE_SIZE (type)) != INTEGER_CST)
    {
      error_init (init_loc,
		  "variable-sized object may not be initialized except "
		  "with an empty initializer");
      بازگشت error_mark_گره;
    }

  error_init (init_loc, "invalid initializer");
  بازگشت error_mark_گره;
}

/* Handle initializers that use braces.  */

/* Type of object we are accumulating a constructor for.
   This type is always a RECORD_TYPE, UNION_TYPE or ARRAY_TYPE.  */
ایستا درخت constructor_type;

/* For a RECORD_TYPE or UNION_TYPE, this is the chain of fields
   left to fill.  */
ایستا درخت constructor_fields;

/* For an ARRAY_TYPE, this is the specified index
   at which to store the next element we get.  */
ایستا درخت constructor_index;

/* For an ARRAY_TYPE, this is the maximum index.  */
ایستا درخت constructor_max_index;

/* For a RECORD_TYPE, this is the first field not yet written out.  */
ایستا درخت constructor_unfilled_fields;

/* For an ARRAY_TYPE, this is the index of the first element
   not yet written out.  */
ایستا درخت constructor_unfilled_index;

/* In a RECORD_TYPE, the byte index of the next consecutive field.
   This is so we can generate gaps between fields, when appropriate.  */
ایستا درخت constructor_bit_index;

/* If we are saving up the elements rather than allocating them,
   this is the list of elements so far (in reverse order,
   most recent first).  */
ایستا vec<constructor_elt, va_gc> *constructor_elements;

/* 1 if constructor should be incrementally stored into a constructor chain,
   0 if all the elements should be kept in AVL tree.  */
ایستا صحیح constructor_incremental;

/* 1 if so far this constructor's elements are all compile-time constants.  */
ایستا صحیح constructor_constant;

/* 1 if so far this constructor's elements are all valid address constants.  */
ایستا صحیح constructor_simple;

/* 1 if this constructor has an element that cannot be part of a
   constant expression.  */
ایستا صحیح constructor_nonconst;

/* 1 if this constructor is erroneous so far.  */
ایستا صحیح constructor_erroneous;

/* 1 if this constructor is the universal zero initializer { 0 }.  */
ایستا صحیح constructor_zeroinit;

/* 1 if this constructor should have padding bits zeroed (C23 {}.  */
ایستا منطقی constructor_zero_padding_bits;

/* 1 if this constructor is a braced scalar initializer (further nested levels
   of braces are an error).  */
ایستا منطقی constructor_braced_scalar;

/* Structure for managing pending initializer elements, organized as an
   AVL tree.  */

ساختار init_گره
{
  ساختار init_گره *چپ, *راست;
  ساختار init_گره *parent;
  صحیح balance;
  درخت purpose;
  درخت مقدار;
  درخت origtype;
};

/* Tree of pending elements at this constructor level.
   These are elements encountered out of order
   which belong at places we haven't reached yet in actually
   writing the output.
   Will never hold tree nodes across GC runs.  */
ایستا ساختار init_گره *constructor_pending_elts;

/* The SPELLING_DEPTH of this constructor.  */
ایستا صحیح constructor_depth;

/* DECL node for which an initializer is being read.
   0 means we are reading a constructor expression
   such as (struct foo) {...}.  */
ایستا درخت constructor_decl;

/* Nonzero if there were any member designators in this initializer.  */
ایستا صحیح constructor_designated;

/* Nesting depth of designator list.  */
ایستا صحیح designator_depth;

/* Nonzero if there were diagnosed errors in this designator list.  */
ایستا صحیح designator_erroneous;


/* This stack has a level for each implicit or explicit level of
   structuring in the initializer, including the outermost one.  It
   saves the values of most of the variables above.  */

ساختار constructor_range_پشته;

ساختار constructor_پشته
{
  ساختار constructor_پشته *next;
  درخت type;
  درخت fields;
  درخت index;
  درخت max_index;
  درخت unfilled_index;
  درخت unfilled_fields;
  درخت bit_index;
  vec<constructor_elt, va_gc> *elements;
  ساختار init_گره *pending_elts;
  صحیح offset;
  صحیح depth;
  /* If value nonzero, this value should replace the entire
     constructor at this level.  */
  ساختار c_عبارت replacement_مقدار;
  ساختار constructor_range_پشته *range_پشته;
  نویسه constant;
  نویسه simple;
  نویسه nonconst;
  نویسه implicit;
  نویسه erroneous;
  نویسه outer;
  نویسه incremental;
  نویسه designated;
  منطقی zero_padding_bits;
  منطقی braced_scalar;
  صحیح designator_depth;
};

ایستا ساختار constructor_پشته *constructor_پشته;

/* This stack represents designators from some range designator up to
   the last designator in the list.  */

ساختار constructor_range_پشته
{
  ساختار constructor_range_پشته *next, *prev;
  ساختار constructor_پشته *پشته;
  درخت range_start;
  درخت index;
  درخت range_end;
  درخت fields;
};

ایستا ساختار constructor_range_پشته *constructor_range_پشته;

/* This stack records separate initializers that are nested.
   Nested initializers can't happen in ANSI C, but GNU C allows them
   in cases like { ... (struct foo) { ... } ... }.  */

ساختار initializer_پشته
{
  ساختار initializer_پشته *next;
  درخت decl;
  ساختار constructor_پشته *constructor_پشته;
  ساختار constructor_range_پشته *constructor_range_پشته;
  vec<constructor_elt, va_gc> *elements;
  ساختار spelling *spelling;
  ساختار spelling *spelling_base;
  صحیح spelling_size;
  نویسه require_constant_مقدار;
  نویسه require_constant_elements;
  نویسه require_constexpr_مقدار;
  نویسه designated;
  rich_location *missing_brace_richloc;
};

ایستا ساختار initializer_پشته *initializer_پشته;

/* Prepare to parse and output the initializer for variable DECL.  */

تهی
start_init (درخت decl, درخت asmspec_درخت ATTRIBUTE_UNUSED,
	    منطقی init_require_constant, منطقی init_require_constexpr,
	    rich_location *richloc)
{
  ثابت نویسه *locus;
  ساختار initializer_پشته *p = XNEW (ساختار initializer_پشته);

  p->decl = constructor_decl;
  p->require_constant_مقدار = require_constant_مقدار;
  p->require_constant_elements = require_constant_elements;
  p->require_constexpr_مقدار = require_constexpr_مقدار;
  p->constructor_پشته = constructor_پشته;
  p->constructor_range_پشته = constructor_range_پشته;
  p->elements = constructor_elements;
  p->spelling = spelling;
  p->spelling_base = spelling_base;
  p->spelling_size = spelling_size;
  p->next = initializer_پشته;
  p->missing_brace_richloc = richloc;
  p->designated = constructor_designated;
  initializer_پشته = p;

  constructor_decl = decl;
  constructor_designated = 0;

  require_constant_مقدار = init_require_constant;
  require_constexpr_مقدار = init_require_constexpr;
  اگر (decl != NULL_درخت && decl != error_mark_گره)
    {
      require_constant_elements
	= ((init_require_constant || (pedantic && !flag_isoc99))
	   /* For a scalar, you can always use any value to initialize,
	      even within braces.  */
	   && AGGREGATE_TYPE_P (درخت_TYPE (decl)));
      locus = identifier_to_locale (IDENTIFIER_POINTER (DECL_NAME (decl)));
    }
  وگرنه
    {
      require_constant_elements = نادرست;
      locus = _("(anonymous)");
    }

  constructor_پشته = 0;
  constructor_range_پشته = 0;

  found_missing_braces = 0;

  spelling_base = 0;
  spelling_size = 0;
  RESTORE_SPELLING_DEPTH (0);

  اگر (locus)
    افزودن_string (locus);
}

تهی
finish_init (تهی)
{
  ساختار initializer_پشته *p = initializer_پشته;

  /* Free the whole constructor stack of this initializer.  */
  وقتی (constructor_پشته)
    {
      ساختار constructor_پشته *q = constructor_پشته;
      constructor_پشته = q->next;
      XDELETE (q);
    }

  gcc_assert (!constructor_range_پشته);

  /* Pop back to the data of the outer initializer (if any).  */
  XDELETE (spelling_base);

  constructor_decl = p->decl;
  require_constant_مقدار = p->require_constant_مقدار;
  require_constant_elements = p->require_constant_elements;
  require_constexpr_مقدار = p->require_constexpr_مقدار;
  constructor_پشته = p->constructor_پشته;
  constructor_designated = p->designated;
  constructor_range_پشته = p->constructor_range_پشته;
  constructor_elements = p->elements;
  spelling = p->spelling;
  spelling_base = p->spelling_base;
  spelling_size = p->spelling_size;
  initializer_پشته = p->next;
  XDELETE (p);
}

/* Call here when we see the initializer is surrounded by braces.
   This is instead of a call to push_init_level;
   it is matched by a call to pop_init_level.

   TYPE is the type to initialize, for a constructor expression.
   For an initializer for a decl, TYPE is zero.  */

تهی
really_start_incremental_init (درخت type)
{
  ساختار constructor_پشته *p = XNEW (ساختار constructor_پشته);

  اگر (type == NULL_درخت)
    type = درخت_TYPE (constructor_decl);

  اگر (VECTOR_TYPE_P (type)
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
  p->replacement_مقدار.مقدار = 0;
  p->replacement_مقدار.original_code = ERROR_MARK;
  p->replacement_مقدار.original_type = پوچ;
  p->implicit = 0;
  p->range_پشته = 0;
  p->outer = 0;
  p->incremental = constructor_incremental;
  p->designated = constructor_designated;
  p->zero_padding_bits = constructor_zero_padding_bits;
  p->braced_scalar = constructor_braced_scalar;
  p->designator_depth = designator_depth;
  p->next = 0;
  constructor_پشته = p;

  constructor_constant = 1;
  constructor_simple = 1;
  constructor_nonconst = 0;
  constructor_depth = SPELLING_DEPTH ();
  constructor_elements = پوچ;
  constructor_pending_elts = 0;
  constructor_type = type;
  constructor_incremental = 1;
  constructor_designated = 0;
  constructor_zero_padding_bits = نادرست;
  constructor_zeroinit = 1;
  constructor_braced_scalar = نادرست;
  designator_depth = 0;
  designator_erroneous = 0;

  اگر (RECORD_OR_UNION_TYPE_P (constructor_type))
    {
      constructor_fields = TYPE_FIELDS (constructor_type);
      /* Skip any nameless bit fields at the beginning.  */
      وقتی (constructor_fields != NULL_درخت
	     && DECL_UNNAMED_BIT_FIELD (constructor_fields))
	constructor_fields = DECL_CHAIN (constructor_fields);

      constructor_unfilled_fields = constructor_fields;
      constructor_bit_index = bitsize_zero_گره;
    }
  وگرنه اگر (درخت_CODE (constructor_type) == ARRAY_TYPE)
    {
      اگر (TYPE_DOMAIN (constructor_type))
	{
	  constructor_max_index
	    = TYPE_MAX_مقدار (TYPE_DOMAIN (constructor_type));

	  /* Detect non-empty initializations of zero-length arrays.  */
	  اگر (constructor_max_index == NULL_درخت
	      && TYPE_SIZE (constructor_type))
	    constructor_max_index = integer_minus_one_گره;

	  /* constructor_max_index needs to be an INTEGER_CST.  Attempts
	     to initialize VLAs with a nonempty initializer will cause a
	     proper error; avoid tree checking errors as well by setting a
	     safe value.  */
	  اگر (constructor_max_index
	      && درخت_CODE (constructor_max_index) != INTEGER_CST)
	    constructor_max_index = integer_minus_one_گره;

	  constructor_index
	    = convert (bitsizetype,
		       TYPE_MIN_مقدار (TYPE_DOMAIN (constructor_type)));
	}
      وگرنه
	{
	  constructor_index = bitsize_zero_گره;
	  constructor_max_index = NULL_درخت;
	}

      constructor_unfilled_index = constructor_index;
    }
  وگرنه اگر (gnu_vector_type_p (constructor_type))
    {
      /* Vectors are like simple fixed-size arrays.  */
      constructor_max_index =
	bitsize_int (TYPE_VECTOR_SUBPARTS (constructor_type) - 1);
      constructor_index = bitsize_zero_گره;
      constructor_unfilled_index = constructor_index;
    }
  وگرنه
    {
      /* Handle the case of int x = {5}; */
      constructor_fields = constructor_type;
      constructor_unfilled_fields = constructor_type;
      constructor_braced_scalar = درست;
    }
}

بیرونی location_t last_init_list_comma;

/* Called when we see an open brace for a nested initializer.  Finish
   off any pending levels with implicit braces.  */
تهی
finish_implicit_inits (location_t loc, ساختار obstack *braced_init_obstack)
{
  وقتی (constructor_پشته->implicit)
    {
      اگر (RECORD_OR_UNION_TYPE_P (constructor_type)
	  && constructor_fields == NULL_درخت)
	process_init_element (درون_داد_location,
			      برداشت_init_level (loc, 1, braced_init_obstack,
					      last_init_list_comma),
			      درست, braced_init_obstack);
      وگرنه اگر (درخت_CODE (constructor_type) == ARRAY_TYPE
	       && constructor_max_index
	       && درخت_int_cst_lt (constructor_max_index,
				   constructor_index))
	process_init_element (درون_داد_location,
			      برداشت_init_level (loc, 1, braced_init_obstack,
					      last_init_list_comma),
			      درست, braced_init_obstack);
      وگرنه
	بشکن;
    }
}

/* Push down into a subobject, for initialization.
   If this is for an explicit set of braces, IMPLICIT is 0.
   If it is because the next element belongs at a lower level,
   IMPLICIT is 1 (or 2 if the push is because of designator list).  */

تهی
افزودن_init_level (location_t loc, صحیح implicit,
		 ساختار obstack *braced_init_obstack)
{
  ساختار constructor_پشته *p;
  درخت مقدار = NULL_درخت;

  /* Unless this is an explicit brace, we need to preserve previous
     content if any.  */
  اگر (implicit)
    {
      اگر (RECORD_OR_UNION_TYPE_P (constructor_type) && constructor_fields)
	مقدار = find_init_member (constructor_fields, braced_init_obstack);
      وگرنه اگر (درخت_CODE (constructor_type) == ARRAY_TYPE)
	مقدار = find_init_member (constructor_index, braced_init_obstack);
    }

  p = XNEW (ساختار constructor_پشته);
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
  p->replacement_مقدار.مقدار = NULL_درخت;
  p->replacement_مقدار.original_code = ERROR_MARK;
  p->replacement_مقدار.original_type = پوچ;
  p->implicit = implicit;
  p->outer = 0;
  p->incremental = constructor_incremental;
  p->designated = constructor_designated;
  p->zero_padding_bits = constructor_zero_padding_bits;
  p->braced_scalar = constructor_braced_scalar;
  p->designator_depth = designator_depth;
  p->next = constructor_پشته;
  p->range_پشته = 0;
  constructor_پشته = p;

  constructor_constant = 1;
  constructor_simple = 1;
  constructor_nonconst = 0;
  constructor_depth = SPELLING_DEPTH ();
  constructor_elements = پوچ;
  constructor_incremental = 1;
  /* If the upper initializer is designated, then mark this as
     designated too to prevent bogus warnings.  */
  constructor_designated = p->designated;
  /* If the upper initializer has padding bits zeroed, that includes
     all nested initializers as well.  */
  constructor_zero_padding_bits = p->zero_padding_bits;
  constructor_braced_scalar = نادرست;
  constructor_pending_elts = 0;
  اگر (!implicit)
    {
      p->range_پشته = constructor_range_پشته;
      constructor_range_پشته = 0;
      designator_depth = 0;
      designator_erroneous = 0;
    }

  /* Don't die if an entire brace-pair level is superfluous
     in the containing level.  */
  اگر (constructor_type == NULL_درخت)
    ;
  وگرنه اگر (RECORD_OR_UNION_TYPE_P (constructor_type))
    {
      /* Don't die if there are extra init elts at the end.  */
      اگر (constructor_fields == NULL_درخت)
	constructor_type = NULL_درخت;
      وگرنه
	{
	  constructor_type = درخت_TYPE (constructor_fields);
	  افزودن_member_name (constructor_fields);
	  constructor_depth++;
	}
    }
  وگرنه اگر (درخت_CODE (constructor_type) == ARRAY_TYPE)
    {
      constructor_type = درخت_TYPE (constructor_type);
      افزودن_array_bounds (درخت_to_uhwi (constructor_index));
      constructor_depth++;
    }

  اگر (constructor_type == NULL_درخت)
    {
      error_init (loc, "extra brace group at end of initializer");
      constructor_fields = NULL_درخت;
      constructor_unfilled_fields = NULL_درخت;
      بازگشت;
    }

  اگر (مقدار && درخت_CODE (مقدار) == CONSTRUCTOR)
    {
      constructor_constant = درخت_CONSTANT (مقدار);
      constructor_simple = درخت_STATIC (مقدار);
      constructor_nonconst = CONSTRUCTOR_NON_CONST (مقدار);
      constructor_elements = CONSTRUCTOR_ELTS (مقدار);
      constructor_zero_padding_bits |= CONSTRUCTOR_ZERO_PADDING_BITS (مقدار);
      اگر (!vec_safe_is_empty (constructor_elements)
	  && (درخت_CODE (constructor_type) == RECORD_TYPE
	      || درخت_CODE (constructor_type) == ARRAY_TYPE))
	set_nonincremental_init (braced_init_obstack);
    }

  اگر (implicit == 1)
    {
      found_missing_braces = 1;
      اگر (initializer_پشته->missing_brace_richloc)
	initializer_پشته->missing_brace_richloc->add_fixit_درج_before
	  (loc, "{");
    }

  اگر (RECORD_OR_UNION_TYPE_P (constructor_type))
    {
      constructor_fields = TYPE_FIELDS (constructor_type);
      /* Skip any nameless bit fields at the beginning.  */
      وقتی (constructor_fields != NULL_درخت
	     && DECL_UNNAMED_BIT_FIELD (constructor_fields))
	constructor_fields = DECL_CHAIN (constructor_fields);

      constructor_unfilled_fields = constructor_fields;
      constructor_bit_index = bitsize_zero_گره;
    }
  وگرنه اگر (gnu_vector_type_p (constructor_type))
    {
      /* Vectors are like simple fixed-size arrays.  */
      constructor_max_index =
	bitsize_int (TYPE_VECTOR_SUBPARTS (constructor_type) - 1);
      constructor_index = bitsize_int (0);
      constructor_unfilled_index = constructor_index;
    }
  وگرنه اگر (درخت_CODE (constructor_type) == ARRAY_TYPE)
    {
      اگر (TYPE_DOMAIN (constructor_type))
	{
	  constructor_max_index
	    = TYPE_MAX_مقدار (TYPE_DOMAIN (constructor_type));

	  /* Detect non-empty initializations of zero-length arrays.  */
	  اگر (constructor_max_index == NULL_درخت
	      && TYPE_SIZE (constructor_type))
	    constructor_max_index = integer_minus_one_گره;

	  /* constructor_max_index needs to be an INTEGER_CST.  Attempts
	     to initialize VLAs will cause a proper error; avoid tree
	     checking errors as well by setting a safe value.  */
	  اگر (constructor_max_index
	      && درخت_CODE (constructor_max_index) != INTEGER_CST)
	    constructor_max_index = integer_minus_one_گره;

	  constructor_index
	    = convert (bitsizetype,
		       TYPE_MIN_مقدار (TYPE_DOMAIN (constructor_type)));
	}
      وگرنه
	constructor_index = bitsize_zero_گره;

      constructor_unfilled_index = constructor_index;
      اگر (مقدار && درخت_CODE (مقدار) == STRING_CST)
	{
	  /* We need to split the char/wchar array into individual
	     characters, so that we don't have to special case it
	     everywhere.  */
	  set_nonincremental_init_from_string (مقدار, braced_init_obstack);
	}
    }
  وگرنه
    {
      اگر (constructor_type != error_mark_گره)
	{
	  اگر (p->braced_scalar)
	    permerror_init (درون_داد_location, 0,
			    "braces around scalar initializer");
	  وگرنه
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

ساختار c_عبارت
برداشت_init_level (location_t loc, صحیح implicit,
		ساختار obstack *braced_init_obstack,
		location_t درج_before)
{
  ساختار constructor_پشته *p;
  ساختار c_عبارت ret;
  ret.مقدار = NULL_درخت;
  ret.original_code = ERROR_MARK;
  ret.original_type = پوچ;
  ret.m_decimal = 0;

  اگر (implicit == 0)
    {
      /* When we come to an explicit close brace,
	 pop any inner levels that didn't have explicit braces.  */
      وقتی (constructor_پشته->implicit)
	process_init_element (درون_داد_location,
			      برداشت_init_level (loc, 1, braced_init_obstack,
					      درج_before),
			      درست, braced_init_obstack);
      gcc_assert (!constructor_range_پشته);
    }
  وگرنه
    اگر (initializer_پشته->missing_brace_richloc)
      initializer_پشته->missing_brace_richloc->add_fixit_درج_before
	(درج_before, "}");

  /* Now output all pending elements.  */
  constructor_incremental = 1;
  output_pending_init_elements (1, braced_init_obstack);

  p = constructor_پشته;

  /* Error for initializing a flexible array member.  */
  اگر (constructor_type && constructor_fields
      && flexible_array_member_type_p (constructor_type))
    {
      /* Silently discard empty initializations.  The parser will
	 already have pedwarned for empty brackets for C17 and earlier.  */
      اگر (integer_zerop (constructor_unfilled_index))
	constructor_type = NULL_درخت;
      اگر (constructor_type || flag_isoc23)
	{
	  gcc_assert (!constructor_type || !TYPE_SIZE (constructor_type));

	  اگر (constructor_depth <= 2)
	    pedwarn_init (loc, OPT_Wpedantic,
			  "initialization of a flexible array member");
	  وگرنه اگر (constructor_type)
	    error_init (loc, "initialization of flexible array member "
			     "in a nested context");
	  وگرنه
	    pedwarn_init (loc, OPT_Wpedantic,
			  "initialization of flexible array member "
			  "in a nested context");

	  /* We have already issued an error message for the existence
	     of a flexible array member not at the end of the structure.
	     Discard the initializer so that we do not die later.  */
	  اگر (constructor_type
	      && DECL_CHAIN (constructor_fields) != NULL_درخت
	      && (!p->type || درخت_CODE (p->type) != UNION_TYPE))
	    constructor_type = NULL_درخت;
	}
    }

  انتخاب (vec_safe_length (constructor_elements))
    {
    حالت 0:
      /* Initialization with { } counts as zeroinit.  */
      constructor_zeroinit = 1;
      بشکن;
    حالت 1:
      /* This might be zeroinit as well.  */
      اگر (integer_zerop ((*constructor_elements)[0].مقدار))
	constructor_zeroinit = 1;
      بشکن;
    پیشفرض:
      /* If the constructor has more than one element, it can't be { 0 }.  */
      constructor_zeroinit = 0;
      بشکن;
    }

  /* Warn when some structs are initialized with direct aggregation.  */
  اگر (!implicit && found_missing_braces && warn_missing_braces
      && !constructor_zeroinit)
    {
      gcc_assert (initializer_پشته->missing_brace_richloc);
      warning_at (initializer_پشته->missing_brace_richloc,
		  OPT_Wmissing_braces,
		  "missing braces around initializer");
    }

  /* Warn when some struct elements are implicitly initialized to zero.  */
  اگر (warn_missing_field_initializers
      && constructor_type
      && درخت_CODE (constructor_type) == RECORD_TYPE
      && constructor_unfilled_fields)
    {
	/* Do not warn for flexible array members or zero-length arrays.  */
	وقتی (constructor_unfilled_fields
	       && (!DECL_SIZE (constructor_unfilled_fields)
		   || integer_zerop (DECL_SIZE (constructor_unfilled_fields))))
	  constructor_unfilled_fields = DECL_CHAIN (constructor_unfilled_fields);

	اگر (constructor_unfilled_fields
	    /* Do not warn if this level of the initializer uses member
	       designators; it is likely to be deliberate.  */
	    && !constructor_designated
	    /* Do not warn about initializing with { 0 } or with { }.  */
	    && !constructor_zeroinit)
	  {
	    اگر (warning_at (درون_داد_location, OPT_Wmissing_field_initializers,
			    "missing initializer for field %qD of %qT",
			    constructor_unfilled_fields,
			    constructor_type))
	      inform (DECL_SOURCE_LOCATION (constructor_unfilled_fields),
		      "%qD declared here", constructor_unfilled_fields);
	  }
    }

  /* Pad out the end of the structure.  */
  اگر (p->replacement_مقدار.مقدار)
    /* If this closes a superfluous brace pair,
       just pass out the element between them.  */
    ret = p->replacement_مقدار;
  وگرنه اگر (constructor_type == NULL_درخت)
    ;
  وگرنه اگر (!RECORD_OR_UNION_TYPE_P (constructor_type)
	   && درخت_CODE (constructor_type) != ARRAY_TYPE
	   && !gnu_vector_type_p (constructor_type))
    {
      /* A nonincremental scalar initializer--just return
	 the element, after verifying there is just one.
         Empty scalar initializers are supported in C23.  */
      اگر (vec_safe_is_empty (constructor_elements))
	{
	  اگر (constructor_erroneous || constructor_type == error_mark_گره)
	    ret.مقدار = error_mark_گره;
	  وگرنه اگر (درخت_CODE (constructor_type) == FUNCTION_TYPE)
	    {
	      error_init (loc, "invalid initializer");
	      ret.مقدار = error_mark_گره;
	    }
	  وگرنه اگر (درخت_CODE (constructor_type) == POINTER_TYPE)
	    /* Ensure this is a null pointer constant in the case of a
	       'constexpr' object initialized with {}.  */
	    ret.مقدار = build_zero_cst (ptr_type_گره);
	  وگرنه
	    ret.مقدار = build_zero_cst (constructor_type);
	}
      وگرنه اگر (vec_safe_length (constructor_elements) != 1)
	{
	  error_init (loc, "extra elements in scalar initializer");
	  ret.مقدار = (*constructor_elements)[0].مقدار;
	}
      وگرنه
	ret.مقدار = (*constructor_elements)[0].مقدار;
    }
  وگرنه
    {
      اگر (constructor_erroneous)
	ret.مقدار = error_mark_گره;
      وگرنه
	{
	  ret.مقدار = build_constructor (constructor_type,
					 constructor_elements);
	  اگر (constructor_constant)
	    درخت_CONSTANT (ret.مقدار) = 1;
	  اگر (constructor_constant && constructor_simple)
	    درخت_STATIC (ret.مقدار) = 1;
	  اگر (constructor_nonconst)
	    CONSTRUCTOR_NON_CONST (ret.مقدار) = 1;
	  اگر (constructor_zero_padding_bits)
	    CONSTRUCTOR_ZERO_PADDING_BITS (ret.مقدار) = 1;
	}
    }

  اگر (ret.مقدار && درخت_CODE (ret.مقدار) != CONSTRUCTOR)
    {
      اگر (constructor_nonconst)
	ret.original_code = C_MAYBE_CONST_عبارت;
      وگرنه اگر (ret.original_code == C_MAYBE_CONST_عبارت)
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
  اگر (!p->implicit)
    constructor_range_پشته = p->range_پشته;
  RESTORE_SPELLING_DEPTH (constructor_depth);

  constructor_پشته = p->next;
  XDELETE (p);

  اگر (ret.مقدار == NULL_درخت && constructor_پشته == 0)
    ret.مقدار = error_mark_گره;
  بازگشت ret;
}

/* Common handling for both array range and field name designators.
   ARRAY argument is nonzero for array ranges.  Returns false for success.  */

ایستا منطقی
set_designator (location_t loc, منطقی array,
		ساختار obstack *braced_init_obstack)
{
  درخت subtype;
  شمارش درخت_code subcode;

  /* Don't die if an entire brace-pair level is superfluous
     in the containing level, or for an erroneous type.  */
  اگر (constructor_type == NULL_درخت || constructor_type == error_mark_گره)
    بازگشت درست;

  /* If there were errors in this designator list already, bail out
     silently.  */
  اگر (designator_erroneous)
    بازگشت درست;

  /* Likewise for an initializer for a variable-size type.  Those are
     diagnosed in the parser, except for empty initializer braces.  */
  اگر (COMPLETE_TYPE_P (constructor_type)
      && درخت_CODE (TYPE_SIZE (constructor_type)) != INTEGER_CST)
    بازگشت درست;

  اگر (!designator_depth)
    {
      gcc_assert (!constructor_range_پشته);

      /* Designator list starts at the level of closest explicit
	 braces.  */
      وقتی (constructor_پشته->implicit)
	process_init_element (درون_داد_location,
			      برداشت_init_level (loc, 1, braced_init_obstack,
					      last_init_list_comma),
			      درست, braced_init_obstack);
      constructor_designated = 1;
      بازگشت نادرست;
    }

  انتخاب (درخت_CODE (constructor_type))
    {
    حالت  RECORD_TYPE:
    حالت  UNION_TYPE:
      subtype = درخت_TYPE (constructor_fields);
      اگر (subtype != error_mark_گره)
	subtype = TYPE_MAIN_VARIANT (subtype);
      بشکن;
    حالت ARRAY_TYPE:
      subtype = TYPE_MAIN_VARIANT (درخت_TYPE (constructor_type));
      بشکن;
    پیشفرض:
      gcc_unreachable ();
    }

  subcode = درخت_CODE (subtype);
  اگر (array && subcode != ARRAY_TYPE)
    {
      error_init (loc, "array index in non-array initializer");
      بازگشت درست;
    }
  وگرنه اگر (!array && subcode != RECORD_TYPE && subcode != UNION_TYPE)
    {
      error_init (loc, "field name not in record or union initializer");
      بازگشت درست;
    }

  constructor_designated = 1;
  finish_implicit_inits (loc, braced_init_obstack);
  افزودن_init_level (loc, 2, braced_init_obstack);
  بازگشت نادرست;
}

/* If there are range designators in designator list, push a new designator
   to constructor_range_stack.  RANGE_END is end of such stack range or
   NULL_TREE if there is no range designator at this level.  */

ایستا تهی
افزودن_range_پشته (درخت range_end, ساختار obstack * braced_init_obstack)
{
  ساختار constructor_range_پشته *p;

  p = (ساختار constructor_range_پشته *)
    obstack_alloc (braced_init_obstack,
		   اندازه (ساختار constructor_range_پشته));
  p->prev = constructor_range_پشته;
  p->next = 0;
  p->fields = constructor_fields;
  p->range_start = constructor_index;
  p->index = constructor_index;
  p->پشته = constructor_پشته;
  p->range_end = range_end;
  اگر (constructor_range_پشته)
    constructor_range_پشته->next = p;
  constructor_range_پشته = p;
}

/* Within an array initializer, specify the next index to be initialized.
   FIRST is that index.  If LAST is nonzero, then initialize a range
   of indices, running from FIRST through LAST.  */

تهی
set_init_index (location_t loc, درخت first, درخت last,
		ساختار obstack *braced_init_obstack)
{
  اگر (set_designator (loc, درست, braced_init_obstack))
    بازگشت;

  designator_erroneous = 1;

  اگر (!INTEGRAL_TYPE_P (درخت_TYPE (first))
      || (last && !INTEGRAL_TYPE_P (درخت_TYPE (last))))
    {
      error_init (loc, "array index in initializer not of integer type");
      بازگشت;
    }

  اگر (درخت_CODE (first) != INTEGER_CST)
    {
      first = c_fully_fold (first, نادرست, پوچ);
      اگر (درخت_CODE (first) == INTEGER_CST)
	pedwarn_init (loc, OPT_Wpedantic,
		      "array index in initializer is not "
		      "an integer constant expression");
    }

  اگر (last && درخت_CODE (last) != INTEGER_CST)
    {
      last = c_fully_fold (last, نادرست, پوچ);
      اگر (درخت_CODE (last) == INTEGER_CST)
	pedwarn_init (loc, OPT_Wpedantic,
		      "array index in initializer is not "
		      "an integer constant expression");
    }

  اگر (درخت_CODE (first) != INTEGER_CST)
    error_init (loc, "nonconstant array index in initializer");
  وگرنه اگر (last != NULL_درخت && درخت_CODE (last) != INTEGER_CST)
    error_init (loc, "nonconstant array index in initializer");
  وگرنه اگر (درخت_CODE (constructor_type) != ARRAY_TYPE)
    error_init (loc, "array index in non-array initializer");
  وگرنه اگر (درخت_int_cst_sgn (first) == -1)
    error_init (loc, "array index in initializer exceeds array bounds");
  وگرنه اگر (constructor_max_index
	   && درخت_int_cst_lt (constructor_max_index, first))
    error_init (loc, "array index in initializer exceeds array bounds");
  وگرنه
    {
      constant_expression_warning (first);
      اگر (last)
	constant_expression_warning (last);
      constructor_index = convert (bitsizetype, first);
      اگر (درخت_int_cst_lt (constructor_index, first))
	{
	  constructor_index = copy_گره (constructor_index);
	  درخت_OVERFLOW (constructor_index) = 1;
	}

      اگر (last)
	{
	  اگر (درخت_int_cst_equal (first, last))
	    last = NULL_درخت;
	  وگرنه اگر (درخت_int_cst_lt (last, first))
	    {
	      error_init (loc, "empty index range in initializer");
	      last = NULL_درخت;
	    }
	  وگرنه
	    {
	      last = convert (bitsizetype, last);
	      اگر (constructor_max_index != NULL_درخت
		  && درخت_int_cst_lt (constructor_max_index, last))
		{
		  error_init (loc, "array index range in initializer exceeds "
			      "array bounds");
		  last = NULL_درخت;
		}
	    }
	}

      designator_depth++;
      designator_erroneous = 0;
      اگر (constructor_range_پشته || last)
	افزودن_range_پشته (last, braced_init_obstack);
    }
}

/* Within a struct initializer, specify the next field to be initialized.  */

تهی
set_init_label (location_t loc, درخت fieldname, location_t fieldname_loc,
		ساختار obstack *braced_init_obstack)
{
  درخت field;

  اگر (set_designator (loc, نادرست, braced_init_obstack))
    بازگشت;

  designator_erroneous = 1;

  اگر (!RECORD_OR_UNION_TYPE_P (constructor_type))
    {
      error_init (loc, "field name not in record or union initializer");
      بازگشت;
    }

  field = lookup_field (constructor_type, fieldname);

  اگر (field == NULL_درخت)
    {
      درخت guessed_id = lookup_field_fuzzy (constructor_type, fieldname);
      اگر (guessed_id)
	{
	  gcc_rich_location rich_loc (fieldname_loc);
	  rich_loc.add_fixit_misspelled_id (fieldname_loc, guessed_id);
	  error_at (&rich_loc,
		    "%qT has no member named %qE; did you mean %qE?",
		    constructor_type, fieldname, guessed_id);
	}
      وگرنه
	error_at (fieldname_loc, "%qT has no member named %qE",
		  constructor_type, fieldname);
    }
  وگرنه
    انجامبده
      {
	constructor_fields = درخت_مقدار (field);
	designator_depth++;
	designator_erroneous = 0;
	اگر (constructor_range_پشته)
	  افزودن_range_پشته (NULL_درخت, braced_init_obstack);
	field = درخت_CHAIN (field);
	اگر (field)
	  {
	    اگر (set_designator (loc, نادرست, braced_init_obstack))
	      بازگشت;
	  }
      }
    وقتی (field != NULL_درخت);
}

/* Helper function for add_pending_init.  Find inorder successor of P
   in AVL tree.  */
ایستا ساختار init_گره *
init_گره_successor (ساختار init_گره *p)
{
  ساختار init_گره *r;
  اگر (p->راست)
    {
      r = p->راست;
      وقتی (r->چپ)
	r = r->چپ;
      بازگشت r;
    }
  r = p->parent;
  وقتی (r && p == r->راست)
    {
      p = r;
      r = r->parent;
    }
  بازگشت r;
}

/* Add a new initializer to the tree of pending initializers.  PURPOSE
   identifies the initializer, either array index or field in a structure.
   VALUE is the value of that index or field.  If ORIGTYPE is not
   NULL_TREE, it is the original type of VALUE.

   IMPLICIT is true if value comes from pop_init_level (1),
   the new initializer has been merged with the existing one
   and thus no warnings should be emitted about overriding an
   existing initializer.  */

ایستا تهی
add_pending_init (location_t loc, درخت purpose, درخت مقدار, درخت origtype,
		  منطقی implicit, ساختار obstack *braced_init_obstack)
{
  ساختار init_گره *p, **q, *r;

  q = &constructor_pending_elts;
  p = 0;

  اگر (درخت_CODE (constructor_type) == ARRAY_TYPE)
    {
      وقتی (*q != 0)
	{
	  p = *q;
	  اگر (درخت_int_cst_lt (purpose, p->purpose))
	    q = &p->چپ;
	  وگرنه اگر (درخت_int_cst_lt (p->purpose, purpose))
	    {
	      اگر (درخت_CODE (p->مقدار) != RAW_DATA_CST
		  || (p->راست
		      && درخت_int_cst_le (p->راست->purpose, purpose)))
		q = &p->راست;
	      وگرنه
		{
		  widest_int pp = wi::to_widest (p->purpose);
		  widest_int pw = wi::to_widest (purpose);
		  اگر (pp + RAW_DATA_LENGTH (p->مقدار) <= pw)
		    q = &p->راست;
		  وگرنه
		    {
		      /* Override which should split the old RAW_DATA_CST
			 into 2 or 3 pieces.  */
		      اگر (!implicit && warn_override_init)
			warning_init (loc, OPT_Woverride_init,
				      "initialized field overwritten");
		      unsigned HOST_WIDE_INT start = (pw - pp).to_uhwi ();
		      unsigned HOST_WIDE_INT len = 1;
		      اگر (درخت_CODE (مقدار) == RAW_DATA_CST)
			len = RAW_DATA_LENGTH (مقدار);
		      unsigned HOST_WIDE_INT end = 0;
		      unsigned plen = RAW_DATA_LENGTH (p->مقدار);
		      gcc_checking_assert (start < plen && start);
		      اگر (plen - start > len)
			end = plen - start - len;
		      درخت v = p->مقدار;
		      درخت origtype = p->origtype;
		      اگر (start == 1)
			p->مقدار = build_int_cst (درخت_TYPE (v),
						  RAW_DATA_UCHAR_ELT (v, 0));
		      وگرنه
			{
			  p->مقدار = v;
			  اگر (end > 1)
			    v = copy_گره (v);
			  RAW_DATA_LENGTH (p->مقدار) = start;
			}
		      اگر (end)
			{
			  درخت epurpose
			    = size_binop (PLUS_عبارت, purpose,
					  bitsize_int (len));
			  اگر (end > 1)
			    {
			      RAW_DATA_LENGTH (v) -= plen - end;
			      RAW_DATA_POINTER (v) += plen - end;
			    }
			  وگرنه
			    v = build_int_cst (درخت_TYPE (v),
					       RAW_DATA_UCHAR_ELT (v, plen
								      - end));
			  add_pending_init (loc, epurpose, v, origtype,
					    implicit, braced_init_obstack);
			}
		      q = &constructor_pending_elts;
		      ادامه;
		    }
		}
	    }
	  وگرنه
	    {
	      اگر (درخت_CODE (p->مقدار) == RAW_DATA_CST
		  && (RAW_DATA_LENGTH (p->مقدار)
		      > (درخت_CODE (مقدار) == RAW_DATA_CST
			 ? RAW_DATA_LENGTH (مقدار) : 1)))
		{
		  /* Override which should split the old RAW_DATA_CST
		     into 2 pieces.  */
		  اگر (!implicit && warn_override_init)
		    warning_init (loc, OPT_Woverride_init,
				  "initialized field overwritten");
		  unsigned HOST_WIDE_INT len = 1;
		  اگر (درخت_CODE (مقدار) == RAW_DATA_CST)
		    len = RAW_DATA_LENGTH (مقدار);
		  اگر ((unsigned) RAW_DATA_LENGTH (p->مقدار) > len + 1)
		    {
		      RAW_DATA_LENGTH (p->مقدار) -= len;
		      RAW_DATA_POINTER (p->مقدار) += len;
		    }
		  وگرنه
		    {
		      unsigned صحیح l = RAW_DATA_LENGTH (p->مقدار) - 1;
		      p->مقدار
			= build_int_cst (درخت_TYPE (p->مقدار),
					 RAW_DATA_UCHAR_ELT (p->مقدار, l));
		    }
		  p->purpose = size_binop (PLUS_عبارت, p->purpose,
					   bitsize_int (len));
		  ادامه;
		}
	      اگر (درخت_CODE (مقدار) == RAW_DATA_CST)
		{
		handle_raw_data:
		  /* RAW_DATA_CST value might overlap various further
		     prior initval entries.  Find out how many.  */
		  unsigned cnt = 0;
		  widest_int w
		    = wi::to_widest (purpose) + RAW_DATA_LENGTH (مقدار);
		  ساختار init_گره *r = p, *last = پوچ;
		  منطقی override_init = warn_override_init;
		  وقتی ((r = init_گره_successor (r))
			 && wi::to_widest (r->purpose) < w)
		    {
		      ++cnt;
		      اگر (درخت_SIDE_EFFECTS (r->مقدار))
			warning_init (loc, OPT_Woverride_init_side_effects,
				      "initialized field with side-effects "
				      "overwritten");
		      وگرنه اگر (override_init)
			{
			  warning_init (loc, OPT_Woverride_init,
					"initialized field overwritten");
			  override_init = نادرست;
			}
		      last = r;
		    }
		  اگر (cnt)
		    {
		      اگر (درخت_CODE (last->مقدار) == RAW_DATA_CST
			  && (wi::to_widest (last->purpose)
			      + RAW_DATA_LENGTH (last->مقدار) > w))
			{
			  /* The last overlapping prior initval overlaps
			     only partially.  Shrink it and decrease cnt.  */
			  unsigned صحیح l = (wi::to_widest (last->purpose)
					    + RAW_DATA_LENGTH (last->مقدار)
					    - w).to_uhwi ();
			  --cnt;
			  RAW_DATA_LENGTH (last->مقدار) -= l;
			  RAW_DATA_POINTER (last->مقدار) += l;
			  اگر (RAW_DATA_LENGTH (last->مقدار) == 1)
			    last->مقدار
			      = build_int_cst (درخت_TYPE (last->مقدار),
					       RAW_DATA_UCHAR_ELT (last->مقدار,
								   0));
			  last->purpose
			    = size_binop (PLUS_عبارت, last->purpose,
					  bitsize_int (l));
			}
		      /* Instead of deleting cnt nodes from the AVL tree
			 and rebalancing, peel of last cnt bytes from the
			 RAW_DATA_CST.  Overriding thousands of previously
			 initialized array elements with #embed needs to work,
			 but doesn't need to be super efficient.  */
		      gcc_checking_assert ((unsigned) RAW_DATA_LENGTH (مقدار)
					   > cnt);
		      RAW_DATA_LENGTH (مقدار) -= cnt;
		      ثابت unsigned نویسه *s
			= &RAW_DATA_UCHAR_ELT (مقدار, RAW_DATA_LENGTH (مقدار));
		      unsigned صحیح o = RAW_DATA_LENGTH (مقدار);
		      برای (r = p; cnt--; ++o, ++s)
			{
			  r = init_گره_successor (r);
			  r->purpose = size_binop (PLUS_عبارت, purpose,
						   bitsize_int (o));
			  r->مقدار = build_int_cst (درخت_TYPE (مقدار), *s);
			  r->origtype = origtype;
			}
		      اگر (RAW_DATA_LENGTH (مقدار) == 1)
			مقدار = build_int_cst (درخت_TYPE (مقدار),
					       RAW_DATA_UCHAR_ELT (مقدار, 0));
		    }
		}
	      اگر (!implicit)
		{
		  اگر (درخت_SIDE_EFFECTS (p->مقدار))
		    warning_init (loc, OPT_Woverride_init_side_effects,
				  "initialized field with side-effects "
				  "overwritten");
		  وگرنه اگر (warn_override_init)
		    warning_init (loc, OPT_Woverride_init,
				  "initialized field overwritten");
		}
	      p->مقدار = مقدار;
	      p->origtype = origtype;
	      بازگشت;
	    }
	}
      اگر (درخت_CODE (مقدار) == RAW_DATA_CST && p)
	{
	  ساختار init_گره *r;
	  اگر (q == &p->چپ)
	    r = p;
	  وگرنه
	    r = init_گره_successor (p);
	  اگر (r && wi::to_widest (r->purpose) < (wi::to_widest (purpose)
						 + RAW_DATA_LENGTH (مقدار)))
	    {
	      /* Overlap with at least one prior initval in the range but
		 not at the start.  */
	      p = r;
	      p->purpose = purpose;
	      برو handle_raw_data;
	    }
	}
    }
  وگرنه
    {
      درخت bitpos;

      bitpos = bit_position (purpose);
      وقتی (*q != پوچ)
	{
	  p = *q;
	  اگر (درخت_int_cst_lt (bitpos, bit_position (p->purpose)))
	    q = &p->چپ;
	  وگرنه اگر (p->purpose != purpose)
	    q = &p->راست;
	  وگرنه
	    {
	      اگر (!implicit)
		{
		  اگر (درخت_SIDE_EFFECTS (p->مقدار))
		    warning_init (loc, OPT_Woverride_init_side_effects,
				  "initialized field with side-effects "
				  "overwritten");
		  وگرنه اگر (warn_override_init)
		    warning_init (loc, OPT_Woverride_init,
				  "initialized field overwritten");
		}
	      p->مقدار = مقدار;
	      p->origtype = origtype;
	      بازگشت;
	    }
	}
    }

  r = (ساختار init_گره *) obstack_alloc (braced_init_obstack,
					  اندازه (ساختار init_گره));
  r->purpose = purpose;
  r->مقدار = مقدار;
  r->origtype = origtype;

  *q = r;
  r->parent = p;
  r->چپ = 0;
  r->راست = 0;
  r->balance = 0;

  وقتی (p)
    {
      ساختار init_گره *s;

      اگر (r == p->چپ)
	{
	  اگر (p->balance == 0)
	    p->balance = -1;
	  وگرنه اگر (p->balance < 0)
	    {
	      اگر (r->balance < 0)
		{
		  /* L rotation.  */
		  p->چپ = r->راست;
		  اگر (p->چپ)
		    p->چپ->parent = p;
		  r->راست = p;

		  p->balance = 0;
		  r->balance = 0;

		  s = p->parent;
		  p->parent = r;
		  r->parent = s;
		  اگر (s)
		    {
		      اگر (s->چپ == p)
			s->چپ = r;
		      وگرنه
			s->راست = r;
		    }
		  وگرنه
		    constructor_pending_elts = r;
		}
	      وگرنه
		{
		  /* LR rotation.  */
		  ساختار init_گره *t = r->راست;

		  r->راست = t->چپ;
		  اگر (r->راست)
		    r->راست->parent = r;
		  t->چپ = r;

		  p->چپ = t->راست;
		  اگر (p->چپ)
		    p->چپ->parent = p;
		  t->راست = p;

		  p->balance = t->balance < 0;
		  r->balance = -(t->balance > 0);
		  t->balance = 0;

		  s = p->parent;
		  p->parent = t;
		  r->parent = t;
		  t->parent = s;
		  اگر (s)
		    {
		      اگر (s->چپ == p)
			s->چپ = t;
		      وگرنه
			s->راست = t;
		    }
		  وگرنه
		    constructor_pending_elts = t;
		}
	      بشکن;
	    }
	  وگرنه
	    {
	      /* p->balance == +1; growth of left side balances the node.  */
	      p->balance = 0;
	      بشکن;
	    }
	}
      وگرنه /* r == p->right */
	{
	  اگر (p->balance == 0)
	    /* Growth propagation from right side.  */
	    p->balance++;
	  وگرنه اگر (p->balance > 0)
	    {
	      اگر (r->balance > 0)
		{
		  /* R rotation.  */
		  p->راست = r->چپ;
		  اگر (p->راست)
		    p->راست->parent = p;
		  r->چپ = p;

		  p->balance = 0;
		  r->balance = 0;

		  s = p->parent;
		  p->parent = r;
		  r->parent = s;
		  اگر (s)
		    {
		      اگر (s->چپ == p)
			s->چپ = r;
		      وگرنه
			s->راست = r;
		    }
		  وگرنه
		    constructor_pending_elts = r;
		}
	      وگرنه /* r->balance == -1 */
		{
		  /* RL rotation */
		  ساختار init_گره *t = r->چپ;

		  r->چپ = t->راست;
		  اگر (r->چپ)
		    r->چپ->parent = r;
		  t->راست = r;

		  p->راست = t->چپ;
		  اگر (p->راست)
		    p->راست->parent = p;
		  t->چپ = p;

		  r->balance = (t->balance < 0);
		  p->balance = -(t->balance > 0);
		  t->balance = 0;

		  s = p->parent;
		  p->parent = t;
		  r->parent = t;
		  t->parent = s;
		  اگر (s)
		    {
		      اگر (s->چپ == p)
			s->چپ = t;
		      وگرنه
			s->راست = t;
		    }
		  وگرنه
		    constructor_pending_elts = t;
		}
	      بشکن;
	    }
	  وگرنه
	    {
	      /* p->balance == -1; growth of right side balances the node.  */
	      p->balance = 0;
	      بشکن;
	    }
	}

      r = p;
      p = p->parent;
    }
}

/* Build AVL tree from a sorted chain.  */

ایستا تهی
set_nonincremental_init (ساختار obstack * braced_init_obstack)
{
  unsigned HOST_WIDE_INT ix;
  درخت index, مقدار;

  اگر (درخت_CODE (constructor_type) != RECORD_TYPE
      && درخت_CODE (constructor_type) != ARRAY_TYPE)
    بازگشت;

  FOR_EACH_CONSTRUCTOR_ELT (constructor_elements, ix, index, مقدار)
    add_pending_init (درون_داد_location, index, مقدار, NULL_درخت, درست,
		      braced_init_obstack);
  constructor_elements = پوچ;
  اگر (درخت_CODE (constructor_type) == RECORD_TYPE)
    {
      constructor_unfilled_fields = TYPE_FIELDS (constructor_type);
      /* Skip any nameless bit fields at the beginning.  */
      وقتی (constructor_unfilled_fields != NULL_درخت
	     && DECL_UNNAMED_BIT_FIELD (constructor_unfilled_fields))
	constructor_unfilled_fields = درخت_CHAIN (constructor_unfilled_fields);

    }
  وگرنه اگر (درخت_CODE (constructor_type) == ARRAY_TYPE)
    {
      اگر (TYPE_DOMAIN (constructor_type))
	constructor_unfilled_index
	  = convert (bitsizetype,
		     TYPE_MIN_مقدار (TYPE_DOMAIN (constructor_type)));
      وگرنه
	constructor_unfilled_index = bitsize_zero_گره;
    }
  constructor_incremental = 0;
}

/* Build AVL tree from a string constant.  */

ایستا تهی
set_nonincremental_init_from_string (درخت str,
				     ساختار obstack * braced_init_obstack)
{
  درخت مقدار, purpose, type;
  HOST_WIDE_INT val[2];
  ثابت نویسه *p, *end;
  صحیح byte, wchar_bytes, charwidth, bitpos;

  gcc_assert (درخت_CODE (constructor_type) == ARRAY_TYPE);

  wchar_bytes = TYPE_PRECISION (درخت_TYPE (درخت_TYPE (str))) / BITS_PER_UNIT;
  charwidth = TYPE_PRECISION (char_type_گره);
  gcc_assert ((size_t) wchar_bytes * charwidth
	      <= ARRAY_SIZE (val) * HOST_BITS_PER_WIDE_INT);
  type = درخت_TYPE (constructor_type);
  p = درخت_STRING_POINTER (str);
  end = p + درخت_STRING_LENGTH (str);

  برای (purpose = bitsize_zero_گره;
       p < end
       && !(constructor_max_index
	    && درخت_int_cst_lt (constructor_max_index, purpose));
       purpose = size_binop (PLUS_عبارت, purpose, bitsize_one_گره))
    {
      اگر (wchar_bytes == 1)
	{
	  val[0] = (unsigned نویسه) *p++;
	  val[1] = 0;
	}
      وگرنه
	{
	  val[1] = 0;
	  val[0] = 0;
	  برای (byte = 0; byte < wchar_bytes; byte++)
	    {
	      اگر (BYTES_BIG_ENDIAN)
		bitpos = (wchar_bytes - byte - 1) * charwidth;
	      وگرنه
		bitpos = byte * charwidth;
	      val[bitpos / HOST_BITS_PER_WIDE_INT]
		|= ((unsigned HOST_WIDE_INT) ((unsigned نویسه) *p++))
		   << (bitpos % HOST_BITS_PER_WIDE_INT);
	    }
	}

      اگر (!TYPE_UNSIGNED (type))
	{
	  bitpos = ((wchar_bytes - 1) * charwidth) + HOST_BITS_PER_CHAR;
	  اگر (bitpos < HOST_BITS_PER_WIDE_INT)
	    {
	      اگر (val[0] & (HOST_WIDE_INT_1 << (bitpos - 1)))
		{
		  val[0] |= HOST_WIDE_INT_M1U << bitpos;
		  val[1] = -1;
		}
	    }
	  وگرنه اگر (bitpos == HOST_BITS_PER_WIDE_INT)
	    {
	      اگر (val[0] < 0)
		val[1] = -1;
	    }
	  وگرنه اگر (val[1] & (HOST_WIDE_INT_1
			     << (bitpos - 1 - HOST_BITS_PER_WIDE_INT)))
	    val[1] |= HOST_WIDE_INT_M1U << (bitpos - HOST_BITS_PER_WIDE_INT);
	}

      مقدار = wide_int_to_درخت (type,
				wide_int::from_array (val, 2,
						      HOST_BITS_PER_WIDE_INT * 2));
      add_pending_init (درون_داد_location, purpose, مقدار, NULL_درخت, درست,
                        braced_init_obstack);
    }

  constructor_incremental = 0;
}

/* Return value of FIELD in pending initializer or NULL_TREE if the field was
   not initialized yet.  */

ایستا درخت
find_init_member (درخت field, ساختار obstack * braced_init_obstack)
{
  ساختار init_گره *p;

  اگر (درخت_CODE (constructor_type) == ARRAY_TYPE)
    {
      اگر (constructor_incremental
	  && درخت_int_cst_lt (field, constructor_unfilled_index))
	set_nonincremental_init (braced_init_obstack);

      p = constructor_pending_elts;
      وقتی (p)
	{
	  اگر (درخت_int_cst_lt (field, p->purpose))
	    p = p->چپ;
	  وگرنه اگر (درخت_int_cst_lt (p->purpose, field))
	    p = p->راست;
	  وگرنه
	    بازگشت p->مقدار;
	}
    }
  وگرنه اگر (درخت_CODE (constructor_type) == RECORD_TYPE)
    {
      درخت bitpos = bit_position (field);

      اگر (constructor_incremental
	  && (!constructor_unfilled_fields
	      || درخت_int_cst_lt (bitpos,
				  bit_position (constructor_unfilled_fields))))
	set_nonincremental_init (braced_init_obstack);

      p = constructor_pending_elts;
      وقتی (p)
	{
	  اگر (field == p->purpose)
	    بازگشت p->مقدار;
	  وگرنه اگر (درخت_int_cst_lt (bitpos, bit_position (p->purpose)))
	    p = p->چپ;
	  وگرنه
	    p = p->راست;
	}
    }
  وگرنه اگر (درخت_CODE (constructor_type) == UNION_TYPE)
    {
      اگر (!vec_safe_is_empty (constructor_elements)
	  && (constructor_elements->last ().index == field))
	بازگشت constructor_elements->last ().مقدار;
    }
  بازگشت NULL_درخت;
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

ایستا تهی
output_init_element (location_t loc, درخت مقدار, درخت origtype,
		     منطقی strict_string, درخت type, درخت field, منطقی pending,
		     منطقی implicit, ساختار obstack * braced_init_obstack)
{
  درخت semantic_type = NULL_درخت;
  منطقی maybe_const = درست;
  منطقی npc, int_const_عبارت, arith_const_عبارت;

  اگر (type == error_mark_گره || مقدار == error_mark_گره)
    {
      constructor_erroneous = 1;
      بازگشت;
    }
  اگر (درخت_CODE (درخت_TYPE (مقدار)) == ARRAY_TYPE
      && (درخت_CODE (مقدار) == STRING_CST
	  || درخت_CODE (مقدار) == COMPOUND_LITERAL_عبارت)
      && !(درخت_CODE (مقدار) == STRING_CST
	   && درخت_CODE (type) == ARRAY_TYPE
	   && INTEGRAL_TYPE_P (درخت_TYPE (type)))
      && !comptypes (TYPE_MAIN_VARIANT (درخت_TYPE (مقدار)),
		     TYPE_MAIN_VARIANT (type)))
    مقدار = array_to_pointer_conversion (درون_داد_location, مقدار);

  اگر (درخت_CODE (مقدار) == COMPOUND_LITERAL_عبارت
      && require_constant_مقدار && pending)
    {
      /* As an extension, allow initializing objects with static storage
	 duration with compound literals (which are then treated just as
	 the brace enclosed list they contain).  */
      اگر (flag_isoc99)
	pedwarn_init (loc, OPT_Wpedantic, "initializer element is not "
		      "constant");
      درخت decl = COMPOUND_LITERAL_عبارت_DECL (مقدار);
      مقدار = DECL_INITIAL (decl);
    }

  npc = null_pointer_constant_p (مقدار);
  int_const_عبارت = (درخت_CODE (مقدار) == INTEGER_CST
		    && !درخت_OVERFLOW (مقدار)
		    && INTEGRAL_TYPE_P (درخت_TYPE (مقدار)));
  /* Not fully determined before folding.  */
  arith_const_عبارت = درست;
  اگر (درخت_CODE (مقدار) == EXCESS_PRECISION_عبارت)
    {
      semantic_type = درخت_TYPE (مقدار);
      مقدار = درخت_OPERAND (مقدار, 0);
    }
  مقدار = c_fully_fold (مقدار, require_constant_مقدار, &maybe_const);
  /* TODO: this may not detect all cases of expressions folding to
     constants that are not arithmetic constant expressions.  */
  اگر (!maybe_const)
    arith_const_عبارت = نادرست;
  وگرنه اگر (!INTEGRAL_TYPE_P (درخت_TYPE (مقدار))
	   && درخت_CODE (درخت_TYPE (مقدار)) != REAL_TYPE
	   && درخت_CODE (درخت_TYPE (مقدار)) != COMPLEX_TYPE)
    arith_const_عبارت = نادرست;
  وگرنه اگر (درخت_CODE (مقدار) != INTEGER_CST
	   && درخت_CODE (مقدار) != REAL_CST
	   && درخت_CODE (مقدار) != COMPLEX_CST
	   && درخت_CODE (مقدار) != RAW_DATA_CST)
    arith_const_عبارت = نادرست;
  وگرنه اگر (درخت_OVERFLOW (مقدار))
    arith_const_عبارت = نادرست;

  اگر (مقدار == error_mark_گره)
    constructor_erroneous = 1;
  وگرنه اگر (!درخت_CONSTANT (مقدار))
    constructor_constant = 0;
  وگرنه اگر (!initializer_constant_valid_p (مقدار,
					  درخت_TYPE (مقدار),
					  AGGREGATE_TYPE_P (constructor_type)
					  && TYPE_REVERSE_STORAGE_ORDER
					     (constructor_type))
	   || (RECORD_OR_UNION_TYPE_P (constructor_type)
	       && DECL_C_BIT_FIELD (field)
	       && درخت_CODE (مقدار) != INTEGER_CST))
    constructor_simple = 0;
  اگر (!maybe_const)
    constructor_nonconst = 1;

  /* Digest the initializer and issue any errors about incompatible
     types before issuing errors about non-constant initializers.  */
  درخت new_مقدار = مقدار;
  اگر (semantic_type)
    new_مقدار = build1 (EXCESS_PRECISION_عبارت, semantic_type, مقدار);
  /* In the case of braces around a scalar initializer, the result of
     this initializer processing goes through digest_init again at the
     outer level.  In the case of a constexpr initializer for a
     pointer, avoid converting a null pointer constant to something
     that is not a null pointer constant to avoid a spurious error
     from that second processing.  */
  اگر (!require_constexpr_مقدار
      || !npc
      || درخت_CODE (constructor_type) != POINTER_TYPE)
    new_مقدار = digest_init (loc,
			     RECORD_OR_UNION_TYPE_P (constructor_type)
			     ? field : constructor_fields
			     ? constructor_fields : constructor_decl,
			     type, new_مقدار, origtype, npc,
			     int_const_عبارت, arith_const_عبارت, strict_string,
			     require_constant_مقدار, require_constexpr_مقدار);
  اگر (new_مقدار == error_mark_گره)
    {
      constructor_erroneous = 1;
      بازگشت;
    }
  اگر (require_constant_مقدار || require_constant_elements)
    constant_expression_warning (new_مقدار);

  /* Proceed to check the constness of the original initializer.  */
  اگر (!initializer_constant_valid_p (مقدار, درخت_TYPE (مقدار)))
    {
      اگر (require_constant_مقدار)
	{
	  error_init (loc, "initializer element is not constant");
	  مقدار = error_mark_گره;
	}
      وگرنه اگر (require_constant_elements)
	pedwarn (loc, OPT_Wpedantic,
		 "initializer element is not computable at load time");
    }
  وگرنه اگر (!maybe_const
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
  اگر (warn_cxx_compat
      && field != NULL_درخت
      && درخت_CODE (field) == FIELD_DECL
      && DECL_BIT_FIELD_TYPE (field) != NULL_درخت
      && (TYPE_MAIN_VARIANT (DECL_BIT_FIELD_TYPE (field))
	  != TYPE_MAIN_VARIANT (type))
      && درخت_CODE (DECL_BIT_FIELD_TYPE (field)) == ENUMERAL_TYPE)
    {
      درخت checktype = origtype != NULL_درخت ? origtype : درخت_TYPE (مقدار);
      اگر (checktype != error_mark_گره
	  && (TYPE_MAIN_VARIANT (checktype)
	      != TYPE_MAIN_VARIANT (DECL_BIT_FIELD_TYPE (field))))
	warning_init (loc, OPT_Wc___compat,
		      "enum conversion in initialization is invalid in C++");
    }

  /* If this field is empty and does not have side effects (and is not at
     the end of structure), don't do anything other than checking the
     initializer.  */
  اگر (field
      && (درخت_TYPE (field) == error_mark_گره
	  || (COMPLETE_TYPE_P (درخت_TYPE (field))
	      && integer_zerop (TYPE_SIZE (درخت_TYPE (field)))
	      && !درخت_SIDE_EFFECTS (new_مقدار)
	      && (درخت_CODE (constructor_type) == ARRAY_TYPE
		  || DECL_CHAIN (field)))))
    بازگشت;

  /* Finally, set VALUE to the initializer value digested above.  */
  مقدار = new_مقدار;

  /* If this element doesn't come next in sequence,
     put it on constructor_pending_elts.  */
  اگر (درخت_CODE (constructor_type) == ARRAY_TYPE
      && (!constructor_incremental
	  || !درخت_int_cst_equal (field, constructor_unfilled_index)
	  || (درخت_CODE (مقدار) == RAW_DATA_CST
	      && constructor_pending_elts
	      && pending)))
    {
      اگر (constructor_incremental
	  && (درخت_int_cst_lt (field, constructor_unfilled_index)
	      || (درخت_CODE (مقدار) == RAW_DATA_CST
		  && constructor_pending_elts
		  && pending)))
	set_nonincremental_init (braced_init_obstack);

      add_pending_init (loc, field, مقدار, origtype, implicit,
			braced_init_obstack);
      بازگشت;
    }
  وگرنه اگر (درخت_CODE (constructor_type) == RECORD_TYPE
	   && (!constructor_incremental
	       || field != constructor_unfilled_fields))
    {
      /* We do this for records but not for unions.  In a union,
	 no matter which field is specified, it can be initialized
	 right away since it starts at the beginning of the union.  */
      اگر (constructor_incremental)
	{
	  اگر (!constructor_unfilled_fields)
	    set_nonincremental_init (braced_init_obstack);
	  وگرنه
	    {
	      درخت bitpos, unfillpos;

	      bitpos = bit_position (field);
	      unfillpos = bit_position (constructor_unfilled_fields);

	      اگر (درخت_int_cst_lt (bitpos, unfillpos))
		set_nonincremental_init (braced_init_obstack);
	    }
	}

      add_pending_init (loc, field, مقدار, origtype, implicit,
			braced_init_obstack);
      بازگشت;
    }
  وگرنه اگر (درخت_CODE (constructor_type) == UNION_TYPE
	   && !vec_safe_is_empty (constructor_elements))
    {
      اگر (!implicit)
	{
	  اگر (درخت_SIDE_EFFECTS (constructor_elements->last ().مقدار))
	    warning_init (loc, OPT_Woverride_init_side_effects,
			  "initialized field with side-effects overwritten");
	  وگرنه اگر (warn_override_init)
	    warning_init (loc, OPT_Woverride_init,
			  "initialized field overwritten");
	}

      /* We can have just one union field set.  */
      constructor_elements = پوچ;
    }

  /* Otherwise, output this element either to
     constructor_elements or to the assembler file.  */

  constructor_elt celt = {field, مقدار};
  vec_safe_افزودن (constructor_elements, celt);

  /* Advance the variable that indicates sequential elements output.  */
  اگر (درخت_CODE (constructor_type) == ARRAY_TYPE)
    {
      درخت inc = bitsize_one_گره;
      اگر (مقدار && درخت_CODE (مقدار) == RAW_DATA_CST)
	inc = bitsize_int (RAW_DATA_LENGTH (مقدار));
      constructor_unfilled_index
	= size_binop_loc (درون_داد_location, PLUS_عبارت,
			  constructor_unfilled_index, inc);
    }
  وگرنه اگر (درخت_CODE (constructor_type) == RECORD_TYPE)
    {
      constructor_unfilled_fields
	= DECL_CHAIN (constructor_unfilled_fields);

      /* Skip any nameless bit fields.  */
      وقتی (constructor_unfilled_fields != NULL_درخت
	     && DECL_UNNAMED_BIT_FIELD (constructor_unfilled_fields))
	constructor_unfilled_fields
	  = DECL_CHAIN (constructor_unfilled_fields);
    }
  وگرنه اگر (درخت_CODE (constructor_type) == UNION_TYPE)
    constructor_unfilled_fields = NULL_درخت;

  /* Now output any pending elements which have become next.  */
  اگر (pending)
    output_pending_init_elements (0, braced_init_obstack);
}

/* For two FIELD_DECLs in the same chain, return -1 if field1
   comes before field2, 1 if field1 comes after field2 and
   0 if field1 == field2.  */

ایستا صحیح
init_field_decl_cmp (درخت field1, درخت field2)
{
  اگر (field1 == field2)
    بازگشت 0;

  درخت bitpos1 = bit_position (field1);
  درخت bitpos2 = bit_position (field2);
  اگر (درخت_int_cst_equal (bitpos1, bitpos2))
    {
      /* If one of the fields has non-zero bitsize, then that
	 field must be the last one in a sequence of zero
	 sized fields, fields after it will have bigger
	 bit_position.  */
      اگر (درخت_TYPE (field1) != error_mark_گره
	  && COMPLETE_TYPE_P (درخت_TYPE (field1))
	  && integer_nonzerop (درخت_TYPE (field1)))
	بازگشت 1;
      اگر (درخت_TYPE (field2) != error_mark_گره
	  && COMPLETE_TYPE_P (درخت_TYPE (field2))
	  && integer_nonzerop (درخت_TYPE (field2)))
	بازگشت -1;
      /* Otherwise, fallback to DECL_CHAIN walk to find out
	 which field comes earlier.  Walk chains of both
	 fields, so that if field1 and field2 are close to each
	 other in either order, it is found soon even for large
	 sequences of zero sized fields.  */
      درخت f1 = field1, f2 = field2;
      وقتی (1)
	{
	  f1 = DECL_CHAIN (f1);
	  f2 = DECL_CHAIN (f2);
	  اگر (f1 == NULL_درخت)
	    {
	      gcc_assert (f2);
	      بازگشت 1;
	    }
	  اگر (f2 == NULL_درخت)
	    بازگشت -1;
	  اگر (f1 == field2)
	    بازگشت -1;
	  اگر (f2 == field1)
	    بازگشت 1;
	  اگر (!درخت_int_cst_equal (bit_position (f1), bitpos1))
	    بازگشت 1;
	  اگر (!درخت_int_cst_equal (bit_position (f2), bitpos1))
	    بازگشت -1;
	}
    }
  وگرنه اگر (درخت_int_cst_lt (bitpos1, bitpos2))
    بازگشت -1;
  وگرنه
    بازگشت 1;
}

/* Output any pending elements which have become next.
   As we output elements, constructor_unfilled_{fields,index}
   advances, which may cause other elements to become next;
   if so, they too are output.

   If ALL is 0, we return when there are
   no more pending elements to output now.

   If ALL is 1, we output space as necessary so that
   we can output all the pending elements.  */
ایستا تهی
output_pending_init_elements (صحیح all, ساختار obstack * braced_init_obstack)
{
  ساختار init_گره *elt = constructor_pending_elts;
  درخت next;

 retry:

  /* Look through the whole pending tree.
     If we find an element that should be output now,
     output it.  Otherwise, set NEXT to the element
     that comes first among those still pending.  */

  next = NULL_درخت;
  وقتی (elt)
    {
      اگر (درخت_CODE (constructor_type) == ARRAY_TYPE)
	{
	  اگر (درخت_int_cst_equal (elt->purpose,
				  constructor_unfilled_index))
	    output_init_element (درون_داد_location, elt->مقدار, elt->origtype,
				 درست, درخت_TYPE (constructor_type),
				 constructor_unfilled_index, نادرست, نادرست,
				 braced_init_obstack);
	  وگرنه اگر (درخت_int_cst_lt (constructor_unfilled_index,
				    elt->purpose))
	    {
	      /* Advance to the next smaller node.  */
	      اگر (elt->چپ)
		elt = elt->چپ;
	      وگرنه
		{
		  /* We have reached the smallest node bigger than the
		     current unfilled index.  Fill the space first.  */
		  next = elt->purpose;
		  بشکن;
		}
	    }
	  وگرنه
	    {
	      /* Advance to the next bigger node.  */
	      اگر (elt->راست)
		elt = elt->راست;
	      وگرنه
		{
		  /* We have reached the biggest node in a subtree.  Find
		     the parent of it, which is the next bigger node.  */
		  وقتی (elt->parent && elt->parent->راست == elt)
		    elt = elt->parent;
		  elt = elt->parent;
		  اگر (elt && درخت_int_cst_lt (constructor_unfilled_index,
					      elt->purpose))
		    {
		      next = elt->purpose;
		      بشکن;
		    }
		}
	    }
	}
      وگرنه اگر (RECORD_OR_UNION_TYPE_P (constructor_type))
	{
	  /* If the current record is complete we are done.  */
	  اگر (constructor_unfilled_fields == NULL_درخت)
	    بشکن;

	  صحیح cmp = init_field_decl_cmp (constructor_unfilled_fields,
					 elt->purpose);
	  اگر (cmp == 0)
	    output_init_element (درون_داد_location, elt->مقدار, elt->origtype,
				 درست, درخت_TYPE (elt->purpose),
				 elt->purpose, نادرست, نادرست,
				 braced_init_obstack);
	  وگرنه اگر (cmp < 0)
	    {
	      /* Advance to the next smaller node.  */
	      اگر (elt->چپ)
		elt = elt->چپ;
	      وگرنه
		{
		  /* We have reached the smallest node bigger than the
		     current unfilled field.  Fill the space first.  */
		  next = elt->purpose;
		  بشکن;
		}
	    }
	  وگرنه
	    {
	      /* Advance to the next bigger node.  */
	      اگر (elt->راست)
		elt = elt->راست;
	      وگرنه
		{
		  /* We have reached the biggest node in a subtree.  Find
		     the parent of it, which is the next bigger node.  */
		  وقتی (elt->parent && elt->parent->راست == elt)
		    elt = elt->parent;
		  elt = elt->parent;
		  اگر (elt
		      && init_field_decl_cmp (constructor_unfilled_fields,
					      elt->purpose) < 0)
		    {
		      next = elt->purpose;
		      بشکن;
		    }
		}
	    }
	}
    }

  /* Ordinarily return, but not if we want to output all
     and there are elements left.  */
  اگر (!(all && next != NULL_درخت))
    بازگشت;

  /* If it's not incremental, just skip over the gap, so that after
     jumping to retry we will output the next successive element.  */
  اگر (RECORD_OR_UNION_TYPE_P (constructor_type))
    constructor_unfilled_fields = next;
  وگرنه اگر (درخت_CODE (constructor_type) == ARRAY_TYPE)
    constructor_unfilled_index = next;

  /* ELT now points to the node in the pending tree with the next
     initializer to output.  */
  برو retry;
}

/* Expression VALUE coincides with the start of type TYPE in a braced
   initializer.  Return true if we should treat VALUE as initializing
   the first element of TYPE, false if we should treat it as initializing
   TYPE as a whole.

   If the initializer is clearly invalid, the question becomes:
   which choice gives the best error message?  */

ایستا منطقی
initialize_elementwise_p (درخت type, درخت مقدار)
{
  اگر (type == error_mark_گره || مقدار == error_mark_گره)
    بازگشت نادرست;

  gcc_checking_assert (TYPE_MAIN_VARIANT (type) == type);

  درخت مقدار_type = درخت_TYPE (مقدار);
  اگر (مقدار_type == error_mark_گره)
    بازگشت نادرست;

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
  اگر (gnu_vector_type_p (type))
    بازگشت !VECTOR_TYPE_P (مقدار_type);

  اگر (AGGREGATE_TYPE_P (type))
    بازگشت !comptypes (type, TYPE_MAIN_VARIANT (مقدار_type));

  بازگشت نادرست;
}

/* Helper function for process_init_element.  Split first element of
   RAW_DATA_CST and save the rest to *RAW_DATA.  */

ایستا درونخطی درخت
maybe_split_raw_data (درخت مقدار, درخت *raw_data)
{
  اگر (مقدار == NULL_درخت || درخت_CODE (مقدار) != RAW_DATA_CST)
    بازگشت مقدار;
  *raw_data = مقدار;
  مقدار = build_int_cst (integer_type_گره,
			 RAW_DATA_UCHAR_ELT (*raw_data, 0));
  ++RAW_DATA_POINTER (*raw_data);
  --RAW_DATA_LENGTH (*raw_data);
  بازگشت مقدار;
}

/* Return non-zero if c_parser_initval should attempt to optimize
   large initializers into RAW_DATA_CST.  In that case return how
   many elements to optimize at most.  */

unsigned
c_maybe_optimize_large_byte_initializer (تهی)
{
  اگر (!constructor_type
      || درخت_CODE (constructor_type) != ARRAY_TYPE
      || constructor_پشته->implicit)
    بازگشت 0;
  درخت elttype = TYPE_MAIN_VARIANT (درخت_TYPE (constructor_type));
  اگر (درخت_CODE (elttype) != INTEGER_TYPE
      && درخت_CODE (elttype) != BITINT_TYPE)
    بازگشت 0;
  اگر (TYPE_PRECISION (elttype) != CHAR_BIT
      || constructor_پشته->replacement_مقدار.مقدار
      || (COMPLETE_TYPE_P (constructor_type)
	  && !poly_int_درخت_p (TYPE_SIZE (constructor_type)))
      || constructor_range_پشته)
    بازگشت 0;
  اگر (constructor_max_index == NULL_درخت)
    بازگشت INT_MAX;
  اگر (درخت_int_cst_le (constructor_max_index, constructor_index)
      || integer_all_onesp (constructor_max_index))
    بازگشت 0;
  widest_int w = wi::to_widest (constructor_max_index);
  w -= wi::to_widest (constructor_index);
  w += 1;
  اگر (w < 64)
    بازگشت 0;
  اگر (w > INT_MAX)
    بازگشت INT_MAX;
  بازگشت w.to_uhwi ();
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

تهی
process_init_element (location_t loc, ساختار c_عبارت مقدار, منطقی implicit,
		      ساختار obstack * braced_init_obstack)
{
  درخت orig_مقدار = مقدار.مقدار;
  صحیح string_flag
    = (orig_مقدار != NULL_درخت && درخت_CODE (orig_مقدار) == STRING_CST);
  منطقی strict_string = مقدار.original_code == STRING_CST;
  منطقی was_designated = designator_depth != 0;
  درخت raw_data = NULL_درخت;

retry:
  designator_depth = 0;
  designator_erroneous = 0;

  اگر (!implicit && مقدار.مقدار && !integer_zerop (مقدار.مقدار))
    constructor_zeroinit = 0;

  /* Handle superfluous braces around string cst as in
     char x[] = {"foo"}; */
  اگر (constructor_type
      && !was_designated
      && درخت_CODE (constructor_type) == ARRAY_TYPE
      && INTEGRAL_TYPE_P (درخت_TYPE (constructor_type))
      && integer_zerop (constructor_unfilled_index))
    {
      اگر (constructor_پشته->replacement_مقدار.مقدار)
	{
	  error_init (loc, "excess elements in %qT initializer", constructor_type);
	  بازگشت;
	}
      وگرنه اگر (string_flag)
	{
	  constructor_پشته->replacement_مقدار = مقدار;
	  بازگشت;
	}
    }

  اگر (constructor_پشته->replacement_مقدار.مقدار != NULL_درخت)
    {
      error_init (loc, "excess elements in struct initializer");
      بازگشت;
    }

  /* Ignore elements of a brace group if it is entirely superfluous
     and has already been diagnosed, or if the type is erroneous.  */
  اگر (constructor_type == NULL_درخت || constructor_type == error_mark_گره)
    بازگشت;

  /* Ignore elements of an initializer for a variable-size type.
     Those are diagnosed in the parser (empty initializer braces are OK).  */
  اگر (COMPLETE_TYPE_P (constructor_type)
      && !poly_int_درخت_p (TYPE_SIZE (constructor_type)))
    بازگشت;

  اگر (!implicit && warn_designated_init && !was_designated
      && درخت_CODE (constructor_type) == RECORD_TYPE
      && lookup_attribute ("designated_init",
			   TYPE_ATTRIBUTES (constructor_type)))
    warning_init (loc,
		  OPT_Wdesignated_init,
		  "positional initialization of field "
		  "in %<struct%> declared with %<designated_init%> attribute");

  /* If we've exhausted any levels that didn't have braces,
     pop them now.  */
  وقتی (constructor_پشته->implicit)
    {
      اگر (RECORD_OR_UNION_TYPE_P (constructor_type)
	  && constructor_fields == NULL_درخت)
	process_init_element (loc,
			      برداشت_init_level (loc, 1, braced_init_obstack,
					      last_init_list_comma),
			      درست, braced_init_obstack);
      وگرنه اگر ((درخت_CODE (constructor_type) == ARRAY_TYPE
		|| gnu_vector_type_p (constructor_type))
	       && constructor_max_index
	       && درخت_int_cst_lt (constructor_max_index,
				   constructor_index))
	process_init_element (loc,
			      برداشت_init_level (loc, 1, braced_init_obstack,
					      last_init_list_comma),
			      درست, braced_init_obstack);
      وگرنه
	بشکن;
    }

  /* In the case of [LO ... HI] = VALUE, only evaluate VALUE once.  */
  اگر (constructor_range_پشته)
    {
      /* If value is a compound literal and we'll be just using its
	 content, don't put it into a SAVE_EXPR.  */
      اگر (درخت_CODE (مقدار.مقدار) != COMPOUND_LITERAL_عبارت
	  || !require_constant_مقدار)
	{
	  درخت semantic_type = NULL_درخت;
	  اگر (درخت_CODE (مقدار.مقدار) == EXCESS_PRECISION_عبارت)
	    {
	      semantic_type = درخت_TYPE (مقدار.مقدار);
	      مقدار.مقدار = درخت_OPERAND (مقدار.مقدار, 0);
	    }
	  مقدار.مقدار = save_عبارت (مقدار.مقدار);
	  اگر (semantic_type)
	    مقدار.مقدار = build1 (EXCESS_PRECISION_عبارت, semantic_type,
				  مقدار.مقدار);
	}
    }

  وقتی (1)
    {
      اگر (درخت_CODE (constructor_type) == RECORD_TYPE)
	{
	  درخت fieldtype;
	  شمارش درخت_code fieldcode;

	  اگر (constructor_fields == NULL_درخت)
	    {
	      pedwarn_init (loc, 0, "excess elements in struct initializer");
	      بشکن;
	    }

	  fieldtype = درخت_TYPE (constructor_fields);
	  اگر (fieldtype != error_mark_گره)
	    fieldtype = TYPE_MAIN_VARIANT (fieldtype);
	  fieldcode = درخت_CODE (fieldtype);

	  /* Error for non-static initialization of a flexible array member.  */
	  اگر (fieldcode == ARRAY_TYPE
	      && !require_constant_مقدار
	      && TYPE_SIZE (fieldtype) == NULL_درخت
	      && DECL_CHAIN (constructor_fields) == NULL_درخت)
	    {
	      error_init (loc, "non-static initialization of a flexible "
			  "array member");
	      بشکن;
	    }

	  /* Error for initialization of a flexible array member with
	     a string constant if the structure is in an array.  E.g.:
	     struct S { int x; char y[]; };
	     struct S s[] = { { 1, "foo" } };
	     is invalid.  */
	  اگر (string_flag
	      && fieldcode == ARRAY_TYPE
	      && constructor_depth > 1
	      && TYPE_SIZE (fieldtype) == NULL_درخت
	      && DECL_CHAIN (constructor_fields) == NULL_درخت)
	    {
	      منطقی in_array_p = نادرست;
	      برای (ساختار constructor_پشته *p = constructor_پشته;
		   p && p->type; p = p->next)
		اگر (درخت_CODE (p->type) == ARRAY_TYPE)
		  {
		    in_array_p = درست;
		    بشکن;
		  }
	      اگر (in_array_p)
		{
		  error_init (loc, "initialization of flexible array "
			      "member in a nested context");
		  بشکن;
		}
	    }

	  /* Accept a string constant to initialize a subarray.  */
	  اگر (مقدار.مقدار != NULL_درخت
	      && fieldcode == ARRAY_TYPE
	      && INTEGRAL_TYPE_P (درخت_TYPE (fieldtype))
	      && string_flag)
	    مقدار.مقدار = orig_مقدار;
	  /* Otherwise, if we have come to a subaggregate,
	     and we don't have an element of its type, push into it.  */
	  وگرنه اگر (مقدار.مقدار != NULL_درخت
		   && initialize_elementwise_p (fieldtype, مقدار.مقدار))
	    {
	      افزودن_init_level (loc, 1, braced_init_obstack);
	      ادامه;
	    }

	  مقدار.مقدار = maybe_split_raw_data (مقدار.مقدار, &raw_data);
	  اگر (مقدار.مقدار)
	    {
	      افزودن_member_name (constructor_fields);
	      output_init_element (loc, مقدار.مقدار, مقدار.original_type,
				   strict_string, fieldtype,
				   constructor_fields, درست, implicit,
				   braced_init_obstack);
	      RESTORE_SPELLING_DEPTH (constructor_depth);
	    }
	  وگرنه
	    /* Do the bookkeeping for an element that was
	       directly output as a constructor.  */
	    {
	      /* For a record, keep track of end position of last field.  */
	      اگر (DECL_SIZE (constructor_fields))
		constructor_bit_index
		  = size_binop_loc (درون_داد_location, PLUS_عبارت,
				    bit_position (constructor_fields),
				    DECL_SIZE (constructor_fields));

	      /* If the current field was the first one not yet written out,
		 it isn't now, so update.  */
	      اگر (constructor_unfilled_fields == constructor_fields)
		{
		  constructor_unfilled_fields = DECL_CHAIN (constructor_fields);
		  /* Skip any nameless bit fields.  */
		  وقتی (constructor_unfilled_fields != 0
			 && (DECL_UNNAMED_BIT_FIELD
			     (constructor_unfilled_fields)))
		    constructor_unfilled_fields =
		      DECL_CHAIN (constructor_unfilled_fields);
		}
	    }

	  constructor_fields = DECL_CHAIN (constructor_fields);
	  /* Skip any nameless bit fields at the beginning.  */
	  وقتی (constructor_fields != NULL_درخت
		 && DECL_UNNAMED_BIT_FIELD (constructor_fields))
	    constructor_fields = DECL_CHAIN (constructor_fields);
	}
      وگرنه اگر (درخت_CODE (constructor_type) == UNION_TYPE)
	{
	  درخت fieldtype;
	  شمارش درخت_code fieldcode;

	  اگر (constructor_fields == NULL_درخت)
	    {
	      pedwarn_init (loc, 0,
			    "excess elements in union initializer");
	      بشکن;
	    }

	  fieldtype = درخت_TYPE (constructor_fields);
	  اگر (fieldtype != error_mark_گره)
	    fieldtype = TYPE_MAIN_VARIANT (fieldtype);
	  fieldcode = درخت_CODE (fieldtype);

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
	  اگر (!in_system_header_at (درون_داد_location) && !constructor_designated
	      && !(مقدار.مقدار && (integer_zerop (مقدار.مقدار)
				   || real_zerop (مقدار.مقدار))))
	    warning (OPT_Wtraditional, "traditional C rejects initialization "
		     "of unions");

	  /* Error for non-static initialization of a flexible array member.  */
	  اگر (fieldcode == ARRAY_TYPE
	      && !require_constant_مقدار
	      && TYPE_SIZE (fieldtype) == NULL_درخت)
	    {
	      error_init (loc, "non-static initialization of a flexible "
			  "array member");
	      بشکن;
	    }

	  /* Error for initialization of a flexible array member with
	     a string constant if the structure is in an array.  E.g.:
	     union U { int x; char y[]; };
	     union U s[] = { { 1, "foo" } };
	     is invalid.  */
	  اگر (string_flag
	      && fieldcode == ARRAY_TYPE
	      && constructor_depth > 1
	      && TYPE_SIZE (fieldtype) == NULL_درخت)
	    {
	      منطقی in_array_p = نادرست;
	      برای (ساختار constructor_پشته *p = constructor_پشته;
		   p && p->type; p = p->next)
		اگر (درخت_CODE (p->type) == ARRAY_TYPE)
		  {
		    in_array_p = درست;
		    بشکن;
		  }
	      اگر (in_array_p)
		{
		  error_init (loc, "initialization of flexible array "
			      "member in a nested context");
		  بشکن;
		}
	    }

	  /* Accept a string constant to initialize a subarray.  */
	  اگر (مقدار.مقدار != NULL_درخت
	      && fieldcode == ARRAY_TYPE
	      && INTEGRAL_TYPE_P (درخت_TYPE (fieldtype))
	      && string_flag)
	    مقدار.مقدار = orig_مقدار;
	  /* Otherwise, if we have come to a subaggregate,
	     and we don't have an element of its type, push into it.  */
	  وگرنه اگر (مقدار.مقدار != NULL_درخت
		   && initialize_elementwise_p (fieldtype, مقدار.مقدار))
	    {
	      افزودن_init_level (loc, 1, braced_init_obstack);
	      ادامه;
	    }

	  مقدار.مقدار = maybe_split_raw_data (مقدار.مقدار, &raw_data);
	  اگر (مقدار.مقدار)
	    {
	      افزودن_member_name (constructor_fields);
	      output_init_element (loc, مقدار.مقدار, مقدار.original_type,
				   strict_string, fieldtype,
				   constructor_fields, درست, implicit,
				   braced_init_obstack);
	      RESTORE_SPELLING_DEPTH (constructor_depth);
	    }
	  وگرنه
	    /* Do the bookkeeping for an element that was
	       directly output as a constructor.  */
	    {
	      constructor_bit_index = DECL_SIZE (constructor_fields);
	      constructor_unfilled_fields = DECL_CHAIN (constructor_fields);
	    }

	  constructor_fields = NULL_درخت;
	}
      وگرنه اگر (درخت_CODE (constructor_type) == ARRAY_TYPE)
	{
	  درخت elttype = TYPE_MAIN_VARIANT (درخت_TYPE (constructor_type));
	  شمارش درخت_code eltcode = درخت_CODE (elttype);

	  /* Accept a string constant to initialize a subarray.  */
	  اگر (مقدار.مقدار != NULL_درخت
	      && eltcode == ARRAY_TYPE
	      && INTEGRAL_TYPE_P (درخت_TYPE (elttype))
	      && string_flag)
	    مقدار.مقدار = orig_مقدار;
	  /* Otherwise, if we have come to a subaggregate,
	     and we don't have an element of its type, push into it.  */
	  وگرنه اگر (مقدار.مقدار != NULL_درخت
		   && initialize_elementwise_p (elttype, مقدار.مقدار))
	    {
	      افزودن_init_level (loc, 1, braced_init_obstack);
	      ادامه;
	    }

	  اگر (constructor_max_index != NULL_درخت
	      && (درخت_int_cst_lt (constructor_max_index, constructor_index)
		  || integer_all_onesp (constructor_max_index))
	      /* For VLA we got an error already.  */
	      && !C_TYPE_VARIABLE_SIZE (constructor_type))
	    {
	      pedwarn_init (loc, 0,
			    "excess elements in array initializer");
	      بشکن;
	    }

	  اگر (مقدار.مقدار
	      && درخت_CODE (مقدار.مقدار) == RAW_DATA_CST
	      && RAW_DATA_LENGTH (مقدار.مقدار) > 1
	      && (درخت_CODE (elttype) == INTEGER_TYPE
		  || درخت_CODE (elttype) == BITINT_TYPE)
	      && TYPE_PRECISION (elttype) == CHAR_BIT
	      && (constructor_max_index == NULL_درخت
		  || درخت_int_cst_lt (constructor_index,
				      constructor_max_index)))
	    {
	      unsigned صحیح len = RAW_DATA_LENGTH (مقدار.مقدار);
	      اگر (constructor_max_index)
		{
		  widest_int w = wi::to_widest (constructor_max_index);
		  w -= wi::to_widest (constructor_index);
		  w += 1;
		  اگر (w < len)
		    len = w.to_uhwi ();
		}
	      اگر (len < (unsigned) RAW_DATA_LENGTH (مقدار.مقدار))
		{
		  raw_data = copy_گره (مقدار.مقدار);
		  RAW_DATA_LENGTH (raw_data) -= len;
		  RAW_DATA_POINTER (raw_data) += len;
		  RAW_DATA_LENGTH (مقدار.مقدار) = len;
		}
	      درخت_TYPE (مقدار.مقدار) = elttype;
	      افزودن_array_bounds (درخت_to_uhwi (constructor_index));
	      output_init_element (loc, مقدار.مقدار, مقدار.original_type,
				   نادرست, elttype, constructor_index, درست,
				   implicit, braced_init_obstack);
	      RESTORE_SPELLING_DEPTH (constructor_depth);
	      constructor_index
		= size_binop_loc (درون_داد_location, PLUS_عبارت,
				  constructor_index, bitsize_int (len));
	    }
	  وگرنه
	    {
	      مقدار.مقدار = maybe_split_raw_data (مقدار.مقدار, &raw_data);
	      /* Now output the actual element.  */
	      اگر (مقدار.مقدار)
		{
		  افزودن_array_bounds (درخت_to_uhwi (constructor_index));
		  output_init_element (loc, مقدار.مقدار, مقدار.original_type,
				       strict_string, elttype,
				       constructor_index, درست, implicit,
				       braced_init_obstack);
		  RESTORE_SPELLING_DEPTH (constructor_depth);
		}

	      constructor_index
		= size_binop_loc (درون_داد_location, PLUS_عبارت,
				  constructor_index, bitsize_one_گره);

	      اگر (!مقدار.مقدار)
		/* If we are doing the bookkeeping for an element that was
		   directly output as a constructor, we must update
		   constructor_unfilled_index.  */
		constructor_unfilled_index = constructor_index;
	    }
	}
      وگرنه اگر (gnu_vector_type_p (constructor_type))
	{
	  درخت elttype = TYPE_MAIN_VARIANT (درخت_TYPE (constructor_type));

	  /* Do a basic check of initializer size.  Note that vectors
	     may not always have a fixed size derived from their type.  */
	  اگر (maybe_lt (درخت_to_poly_uint64 (constructor_max_index),
			درخت_to_poly_uint64 (constructor_index)))
	    {
	      /* Diagose VLA out-of-bounds as errors.  */
	      اگر (درخت_to_poly_uint64 (constructor_max_index).is_constant())
		pedwarn_init (loc, 0,
			      "excess elements in vector initializer");
	      وگرنه
		error_init (loc, "excess elements in vector initializer");

	      بشکن;
	    }

	  مقدار.مقدار = maybe_split_raw_data (مقدار.مقدار, &raw_data);
	  /* Now output the actual element.  */
	  اگر (مقدار.مقدار)
	    {
	      اگر (درخت_CODE (مقدار.مقدار) == VECTOR_CST)
		elttype = TYPE_MAIN_VARIANT (constructor_type);
	      output_init_element (loc, مقدار.مقدار, مقدار.original_type,
				   strict_string, elttype,
				   constructor_index, درست, implicit,
				   braced_init_obstack);
	    }

	  constructor_index
	    = size_binop_loc (درون_داد_location,
			      PLUS_عبارت, constructor_index, bitsize_one_گره);

	  اگر (!مقدار.مقدار)
	    /* If we are doing the bookkeeping for an element that was
	       directly output as a constructor, we must update
	       constructor_unfilled_index.  */
	    constructor_unfilled_index = constructor_index;
	}

      /* Handle the sole element allowed in a braced initializer
	 for a scalar variable.  */
      وگرنه اگر (constructor_type != error_mark_گره
	       && constructor_fields == NULL_درخت)
	{
	  pedwarn_init (loc, 0,
			"excess elements in scalar initializer");
	  بشکن;
	}
      وگرنه
	{
	  مقدار.مقدار = maybe_split_raw_data (مقدار.مقدار, &raw_data);
	  اگر (مقدار.مقدار)
	    output_init_element (loc, مقدار.مقدار, مقدار.original_type,
				 strict_string, constructor_type,
				 NULL_درخت, درست, implicit,
				 braced_init_obstack);
	  constructor_fields = NULL_درخت;
	}

      /* Handle range initializers either at this level or anywhere higher
	 in the designator stack.  */
      اگر (constructor_range_پشته)
	{
	  ساختار constructor_range_پشته *p, *range_پشته;
	  صحیح finish = 0;

	  range_پشته = constructor_range_پشته;
	  constructor_range_پشته = 0;
	  وقتی (constructor_پشته != range_پشته->پشته)
	    {
	      gcc_assert (constructor_پشته->implicit);
	      process_init_element (loc,
				    برداشت_init_level (loc, 1,
						    braced_init_obstack,
						    last_init_list_comma),
				    درست, braced_init_obstack);
	    }
	  برای (p = range_پشته;
	       !p->range_end || درخت_int_cst_equal (p->index, p->range_end);
	       p = p->prev)
	    {
	      gcc_assert (constructor_پشته->implicit);
	      process_init_element (loc,
				    برداشت_init_level (loc, 1,
						    braced_init_obstack,
						    last_init_list_comma),
				    درست, braced_init_obstack);
	    }

	  p->index = size_binop_loc (درون_داد_location,
				     PLUS_عبارت, p->index, bitsize_one_گره);
	  اگر (درخت_int_cst_equal (p->index, p->range_end) && !p->prev)
	    finish = 1;

	  وقتی (1)
	    {
	      constructor_index = p->index;
	      constructor_fields = p->fields;
	      اگر (finish && p->range_end && p->index == p->range_start)
		{
		  finish = 0;
		  p->prev = 0;
		}
	      p = p->next;
	      اگر (!p)
		بشکن;
	      finish_implicit_inits (loc, braced_init_obstack);
	      افزودن_init_level (loc, 2, braced_init_obstack);
	      p->پشته = constructor_پشته;
	      اگر (p->range_end && درخت_int_cst_equal (p->index, p->range_end))
		p->index = p->range_start;
	    }

	  اگر (!finish)
	    constructor_range_پشته = range_پشته;
	  ادامه;
	}

      بشکن;
    }

  constructor_range_پشته = 0;

  اگر (raw_data && RAW_DATA_LENGTH (raw_data))
    {
      gcc_assert (!string_flag && !was_designated);
      مقدار.مقدار = raw_data;
      raw_data = NULL_درخت;
      برو retry;
    }
}

/* Build a complete asm-statement, whose components are a CV_QUALIFIER
   (guaranteed to be 'volatile' or null) and ARGS (represented using
   an ASM_EXPR node).  */
درخت
build_asm_stmt (منطقی is_volatile, درخت args)
{
  اگر (is_volatile)
    ASM_VOLATILE_P (args) = 1;
  بازگشت add_stmt (args);
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
		درخت clobbers, درخت labels, منطقی simple, منطقی is_inline)
{
  درخت tail;
  درخت args;
  صحیح i;
  ثابت نویسه *constraint;
  ثابت نویسه **oconstraints;
  منطقی allows_mem, allows_reg, is_inout;
  صحیح ninputs, noutputs;

  ninputs = list_length (inputs);
  noutputs = list_length (outputs);
  oconstraints = (ثابت نویسه **) alloca (noutputs * اندازه (ثابت نویسه *));

  string = resolve_asm_operand_names (string, outputs, inputs, labels);

  /* Remove output conversions that change the type but not the mode.  */
  برای (i = 0, tail = outputs; tail; ++i, tail = درخت_CHAIN (tail))
    {
      درخت output = درخت_مقدار (tail);

      output = c_fully_fold (output, نادرست, پوچ, درست);

      /* ??? Really, this should not be here.  Users should be using a
	 proper lvalue, dammit.  But there's a long history of using casts
	 in the output operands.  In cases like longlong.h, this becomes a
	 primitive form of typechecking -- if the cast can be removed, then
	 the output operand had a type of the proper width; otherwise we'll
	 get an error.  Gross, but ...  */
      STRIP_NOPS (output);

      اگر (!lvalue_or_else (loc, output, lv_asm))
	output = error_mark_گره;

      اگر (output != error_mark_گره
	  && (درخت_READONLY (output)
	      || TYPE_READONLY (درخت_TYPE (output))
	      || (RECORD_OR_UNION_TYPE_P (درخت_TYPE (output))
		  && C_TYPE_FIELDS_READONLY (درخت_TYPE (output)))))
	readonly_error (loc, output, lv_asm);

      constraint = درخت_STRING_POINTER (درخت_مقدار (درخت_PURPOSE (tail)));
      oconstraints[i] = constraint;

      اگر (parse_output_constraint (&constraint, i, ninputs, noutputs,
				   &allows_mem, &allows_reg, &is_inout,
				   nullptr))
	{
	  /* If the operand is going to end up in memory,
	     mark it addressable.  */
	  اگر (!allows_reg && !c_mark_addressable (output))
	    output = error_mark_گره;
	  اگر (!(!allows_reg && allows_mem)
	      && output != error_mark_گره
	      && VOID_TYPE_P (درخت_TYPE (output)))
	    {
	      error_at (loc, "invalid use of void expression");
	      output = error_mark_گره;
	    }
	  اگر (allows_reg && current_function_decl == NULL_درخت)
	    {
	      error_at (loc, "constraint allows registers outside of "
			     "a function");
	      output = error_mark_گره;
	    }
	}
      وگرنه
	output = error_mark_گره;

      اگر (current_function_decl == NULL_درخت && output != error_mark_گره)
	{
	  اگر (درخت_SIDE_EFFECTS (output))
	    {
	      error_at (loc, "side-effects in output operand outside "
			     "of a function");
	      output = error_mark_گره;
	    }
	  وگرنه
	    {
	      درخت addr = build_unary_op (loc, ADDR_عبارت, output, نادرست);
	      اگر (addr == error_mark_گره)
		output = error_mark_گره;
	      وگرنه اگر (!initializer_constant_valid_p (addr, درخت_TYPE (addr)))
		{
		  error_at (loc, "output operand outside of a function is not "
				 "constant");
		  output = error_mark_گره;
		}
	    }
	}
      وگرنه اگر (output != error_mark_گره && strstr (constraint, "-"))
	{
	  error_at (loc, "%<-%> modifier used inside of a function");
	  output = error_mark_گره;
	}

      درخت_مقدار (tail) = output;
    }

  برای (i = 0, tail = inputs; tail; ++i, tail = درخت_CHAIN (tail))
    {
      درخت درون_داد;

      constraint = درخت_STRING_POINTER (درخت_مقدار (درخت_PURPOSE (tail)));
      درون_داد = درخت_مقدار (tail);

      اگر (parse_درون_داد_constraint (&constraint, i, ninputs, noutputs, 0,
				  oconstraints, &allows_mem, &allows_reg,
				  nullptr))
	{
	  /* If the operand is going to end up in memory,
	     mark it addressable.  */
	  اگر (!allows_reg && allows_mem)
	    {
	      درون_داد = c_fully_fold (درون_داد, نادرست, پوچ, درست);

	      /* Strip the nops as we allow this case.  FIXME, this really
		 should be rejected or made deprecated.  */
	      STRIP_NOPS (درون_داد);
	      اگر (!c_mark_addressable (درون_داد))
		درون_داد = error_mark_گره;
	    }
	  وگرنه
	    {
	      درون_داد = c_fully_fold (convert_lvalue_to_rvalue (loc, درون_داد,
							      درست, نادرست),
				    نادرست, پوچ);

	      اگر (درون_داد != error_mark_گره && VOID_TYPE_P (درخت_TYPE (درون_داد)))
		{
		  error_at (loc, "invalid use of void expression");
		  درون_داد = error_mark_گره;
		}
	    }
	  اگر (allows_reg && current_function_decl == NULL_درخت)
	    {
	      error_at (loc, "constraint allows registers outside of "
			     "a function");
	      درون_داد = error_mark_گره;
	    }
	  اگر (constraint[0] == ':' && درون_داد != error_mark_گره)
	    {
	      درخت t = درون_داد;
	      STRIP_NOPS (t);
	      اگر (درخت_CODE (t) != ADDR_عبارت
		  || !(درخت_CODE (درخت_OPERAND (t, 0)) == FUNCTION_DECL
		       || (VAR_P (درخت_OPERAND (t, 0))
			   && is_global_var (درخت_OPERAND (t, 0)))))
		{
		  error_at (loc, "%<:%> constraint operand is not address "
				 "of a function or non-automatic variable");
		  درون_داد = error_mark_گره;
		}
	      وگرنه اگر (درخت_CODE (درخت_OPERAND (t, 0)) == FUNCTION_DECL)
		suppress_warning (درخت_OPERAND (t, 0), OPT_Wunused);
	    }
	}
      وگرنه
	درون_داد = error_mark_گره;

      اگر (current_function_decl == NULL_درخت && درون_داد != error_mark_گره)
	{
	  اگر (درخت_SIDE_EFFECTS (درون_داد))
	    {
	      error_at (loc, "side-effects in input operand outside "
			     "of a function");
	      درون_داد = error_mark_گره;
	    }
	  وگرنه
	    {
	      درخت tem = درون_داد;
	      اگر (allows_mem && lvalue_p (درون_داد))
		tem = build_unary_op (loc, ADDR_عبارت, درون_داد, نادرست);
	      اگر (!initializer_constant_valid_p (tem, درخت_TYPE (tem)))
		{
		  error_at (loc, "input operand outside of a function is not "
				 "constant");
		  درون_داد = error_mark_گره;
		}
	    }
	}
      وگرنه اگر (درون_داد != error_mark_گره && strstr (constraint, "-"))
	{
	  error_at (loc, "%<-%> modifier used inside of a function");
	  درون_داد = error_mark_گره;
	}

      درخت_مقدار (tail) = درون_داد;
    }

  args = build_stmt (loc, ASM_عبارت, string, outputs, inputs, clobbers, labels);

  /* asm statements without outputs, including simple ones, are treated
     as volatile.  */
  ASM_BASIC_P (args) = simple;
  ASM_VOLATILE_P (args) = (noutputs == 0);
  ASM_INLINE_P (args) = is_inline;

  بازگشت args;
}

/* Generate a goto statement to LABEL.  LOC is the location of the
   GOTO.  */

درخت
c_finish_goto_label (location_t loc, درخت label)
{
  درخت decl = lookup_label_for_goto (loc, label);
  اگر (!decl)
    بازگشت NULL_درخت;
  درخت_USED (decl) = 1;
  mark_decl_used (decl, نادرست);
  {
    add_stmt (build_predict_عبارت (PRED_GOTO, NOT_TAKEN));
    درخت t = build1 (GOTO_عبارت, void_type_گره, decl);
    SET_عبارت_LOCATION (t, loc);
    بازگشت add_stmt (t);
  }
}

/* Generate a computed goto statement to EXPR.  LOC is the location of
   the GOTO.  */

درخت
c_finish_goto_ptr (location_t loc, c_عبارت val)
{
  درخت عبارت = val.مقدار;
  درخت t;
  pedwarn (loc, OPT_Wpedantic, "ISO C forbids %<goto *expr;%>");
  اگر (عبارت != error_mark_گره
      && !POINTER_TYPE_P (درخت_TYPE (عبارت))
      && !null_pointer_constant_p (عبارت))
    {
      error_at (val.get_location (),
		"computed goto must be pointer type");
      عبارت = build_zero_cst (ptr_type_گره);
    }
  عبارت = c_fully_fold (عبارت, نادرست, پوچ);
  عبارت = convert (ptr_type_گره, عبارت);
  t = build1 (GOTO_عبارت, void_type_گره, عبارت);
  SET_عبارت_LOCATION (t, loc);
  بازگشت add_stmt (t);
}

/* Generate a C `return' statement.  RETVAL is the expression for what
   to return, or a null pointer for `return;' with no value.  LOC is
   the location of the return statement, or the location of the expression,
   if the statement has any.  If ORIGTYPE is not NULL_TREE, it
   is the original type of RETVAL.  MUSTTAIL_P indicates a musttail
   attribute.  */

درخت
c_finish_return (location_t loc, درخت retval, درخت origtype, منطقی musttail_p)
{
  درخت valtype = درخت_TYPE (درخت_TYPE (current_function_decl)), ret_stmt;
  منطقی no_warning = نادرست;
  منطقی npc = نادرست;

  /* Use the expansion point to handle cases such as returning NULL
     in a function returning void.  */
  location_t xloc = expansion_point_location_if_in_system_header (loc);

  اگر (درخت_THIS_VOLATILE (current_function_decl))
    warning_at (xloc, 0,
		"function declared %<noreturn%> has a %<return%> statement");

  set_musttail_on_return (retval, xloc, musttail_p);

  اگر (retval)
    {
      درخت semantic_type = NULL_درخت;
      npc = null_pointer_constant_p (retval);
      اگر (درخت_CODE (retval) == EXCESS_PRECISION_عبارت)
	{
	  semantic_type = درخت_TYPE (retval);
	  retval = درخت_OPERAND (retval, 0);
	}
      retval = c_fully_fold (retval, نادرست, پوچ);
      اگر (semantic_type
	  && valtype != NULL_درخت
	  && درخت_CODE (valtype) != VOID_TYPE)
	retval = build1 (EXCESS_PRECISION_عبارت, semantic_type, retval);
    }

  اگر (!retval)
    {
      current_function_returns_null = 1;
      اگر ((warn_return_type >= 0 || flag_isoc99)
	  && valtype != NULL_درخت && درخت_CODE (valtype) != VOID_TYPE)
	{
	  no_warning = درست;
	  اگر (emit_diagnostic (flag_isoc99
			       ? diagnostics::kind::permerror
			       : diagnostics::kind::warning,
			       loc, OPT_Wreturn_mismatch,
			       "%<return%> with no value,"
			       " in function returning non-void"))
	    inform (DECL_SOURCE_LOCATION (current_function_decl),
		    "declared here");
	}
    }
  وگرنه اگر (valtype == NULL_درخت || VOID_TYPE_P (valtype))
    {
      current_function_returns_null = 1;
      منطقی warned_here;
      اگر (درخت_CODE (درخت_TYPE (retval)) != VOID_TYPE)
	warned_here = permerror_opt
	  (xloc, OPT_Wreturn_mismatch,
	   "%<return%> with a value, in function returning void");
      وگرنه
	warned_here = pedwarn
	  (xloc, OPT_Wpedantic, "ISO C forbids "
	   "%<return%> with expression, in function returning void");
      اگر (warned_here)
	inform (DECL_SOURCE_LOCATION (current_function_decl),
		"declared here");
    }
  وگرنه
    {
      درخت t = convert_for_assignment (loc, UNKNOWN_LOCATION, valtype,
				       retval, origtype, ic_return,
				       npc, NULL_درخت, NULL_درخت, 0);
      درخت res = DECL_RESULT (current_function_decl);
      درخت inner;
      منطقی save;

      current_function_returns_مقدار = 1;
      اگر (t == error_mark_گره)
	{
	  /* Suppress -Wreturn-type for this function.  */
	  اگر (warn_return_type)
	    suppress_warning (current_function_decl, OPT_Wreturn_type);
	  بازگشت NULL_درخت;
	}

      save = in_late_دودویی_op;
      اگر (C_BOOLEAN_TYPE_P (درخت_TYPE (res))
	  || درخت_CODE (درخت_TYPE (res)) == COMPLEX_TYPE
	  || (SCALAR_FLOAT_TYPE_P (درخت_TYPE (t))
	      && (درخت_CODE (درخت_TYPE (res)) == INTEGER_TYPE
		  || درخت_CODE (درخت_TYPE (res)) == ENUMERAL_TYPE)
	      && sanitize_flags_p (SANITIZE_FLOAT_CAST)))
        in_late_دودویی_op = درست;
      inner = t = convert (درخت_TYPE (res), t);
      in_late_دودویی_op = save;

      /* Strip any conversions, additions, and subtractions, and see if
	 we are returning the address of a local variable.  Warn if so.  */
      وقتی (1)
	{
	  انتخاب (درخت_CODE (inner))
	    {
	    CASE_CONVERT:
	    حالت NON_LVALUE_عبارت:
	    حالت PLUS_عبارت:
	    حالت POINTER_PLUS_عبارت:
	      inner = درخت_OPERAND (inner, 0);
	      ادامه;

	    حالت MINUS_عبارت:
	      /* If the second operand of the MINUS_EXPR has a pointer
		 type (or is converted from it), this may be valid, so
		 don't give a warning.  */
	      {
		درخت op1 = درخت_OPERAND (inner, 1);

		وقتی (!POINTER_TYPE_P (درخت_TYPE (op1))
		       && (CONVERT_عبارت_P (op1)
			   || درخت_CODE (op1) == NON_LVALUE_عبارت))
		  op1 = درخت_OPERAND (op1, 0);

		اگر (POINTER_TYPE_P (درخت_TYPE (op1)))
		  بشکن;

		inner = درخت_OPERAND (inner, 0);
		ادامه;
	      }

	    حالت ADDR_عبارت:
	      inner = درخت_OPERAND (inner, 0);

	      وقتی (REFERENCE_CLASS_P (inner)
		     && !INDIRECT_REF_P (inner))
		inner = درخت_OPERAND (inner, 0);

	      اگر (DECL_P (inner)
		  && !DECL_EXTERNAL (inner)
		  && DECL_CONTEXT (inner) == current_function_decl
		  && POINTER_TYPE_P (درخت_TYPE (درخت_TYPE (current_function_decl))))
		{
		  اگر (درخت_CODE (inner) == LABEL_DECL)
		    warning_at (loc, OPT_Wreturn_local_addr,
				"function returns address of label");
		  وگرنه اگر (درخت_CODE (inner) == FUNCTION_DECL
			   && (C_FUNC_NONLOCAL_CONTEXT (inner)
			       || !DECL_INITIAL (inner)))
		    warning_at (loc, OPT_Wreturn_local_addr,
				"function returns address of nested function "
				"referencing local context");
		  وگرنه اگر (درخت_CODE (inner) != FUNCTION_DECL
			   && !درخت_STATIC (inner))
		    {
		      warning_at (loc, OPT_Wreturn_local_addr,
				  "function returns address of local variable");
		      درخت zero = build_zero_cst (درخت_TYPE (res));
		      t = build2 (COMPOUND_عبارت, درخت_TYPE (res), t, zero);
		    }
		}
	      بشکن;

	    پیشفرض:
	      بشکن;
	    }

	  بشکن;
	}

      retval = build2 (MODIFY_عبارت, درخت_TYPE (res), res, t);
      SET_عبارت_LOCATION (retval, loc);

      اگر (warn_sequence_point)
	verify_sequence_points (retval);
    }

  ret_stmt = build_stmt (loc, RETURN_عبارت, retval);
  اگر (no_warning)
    suppress_warning (ret_stmt, OPT_Wreturn_type);
  بازگشت add_stmt (ret_stmt);
}

ساختار c_switch {
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
  ساختار c_spot_bindings *bindings;

  /* Whether the switch includes any break statements.  */
  منطقی break_stmt_seen_p;

  /* The next node on the stack.  */
  ساختار c_switch *next;

  /* Remember whether the controlling expression had boolean type
     before integer promotions for the sake of -Wswitch-bool.  */
  منطقی bool_cond_p;
};

/* A stack of the currently active switch statements.  The innermost
   switch statement is on the top of the stack.  There is no need to
   mark the stack for garbage collection because it is only active
   during the processing of the body of a function, and we never
   collect at that point.  */

ساختار c_switch *c_switch_پشته;

/* Start a C switch statement, testing expression EXP.  Return the new
   SWITCH_STMT.  SWITCH_LOC is the location of the `switch'.
   SWITCH_COND_LOC is the location of the switch's condition.
   EXPLICIT_CAST_P is true if the expression EXP has an explicit cast.  */

درخت
c_start_switch (location_t switch_loc,
		location_t switch_cond_loc,
		درخت exp, منطقی explicit_cast_p, درخت switch_name)
{
  درخت orig_type = error_mark_گره;
  منطقی bool_cond_p = نادرست;
  ساختار c_switch *cs;

  اگر (exp != error_mark_گره)
    {
      orig_type = درخت_TYPE (exp);

      اگر (!INTEGRAL_TYPE_P (orig_type))
	{
	  اگر (orig_type != error_mark_گره)
	    {
	      error_at (switch_cond_loc, "switch quantity not an integer");
	      orig_type = error_mark_گره;
	    }
	  exp = integer_zero_گره;
	}
      وگرنه
	{
	  درخت type = TYPE_MAIN_VARIANT (orig_type);
	  درخت e = exp;

	  /* Warn if the condition has boolean value.  */
	  وقتی (درخت_CODE (e) == COMPOUND_عبارت)
	    e = درخت_OPERAND (e, 1);

	  اگر ((C_BOOLEAN_TYPE_P (type)
	       || truth_مقدار_p (درخت_CODE (e)))
	      /* Explicit cast to int suppresses this warning.  */
	      && !(درخت_CODE (type) == INTEGER_TYPE
		   && explicit_cast_p))
	    bool_cond_p = درست;

	  اگر (!in_system_header_at (درون_داد_location)
	      && (type == long_integer_type_گره
		  || type == long_unsigned_type_گره))
	    warning_at (switch_cond_loc,
			OPT_Wtraditional, "%<long%> switch expression not "
			"converted to %<int%> in ISO C");

	  exp = c_fully_fold (exp, نادرست, پوچ);
	  exp = default_conversion (exp);

	  اگر (warn_sequence_point)
	    verify_sequence_points (exp);
	}
    }

  /* Add this new SWITCH_STMT to the stack.  */
  cs = XNEW (ساختار c_switch);
  cs->switch_stmt = build_stmt (switch_loc, SWITCH_STMT, exp,
				NULL_درخت, orig_type, NULL_درخت, switch_name);
  cs->orig_type = orig_type;
  cs->cases = splay_درخت_new (case_compare, پوچ, پوچ);
  cs->bindings = c_get_switch_bindings ();
  cs->break_stmt_seen_p = نادرست;
  cs->bool_cond_p = bool_cond_p;
  cs->next = c_switch_پشته;
  c_switch_پشته = cs;

  بازگشت add_stmt (cs->switch_stmt);
}

/* Process a case label at location LOC, with attributes ATTRS.  */

درخت
do_case (location_t loc, درخت کم_مقدار, درخت بالا_مقدار, درخت attrs)
{
  درخت label = NULL_درخت;

  اگر (کم_مقدار && درخت_CODE (کم_مقدار) != INTEGER_CST)
    {
      کم_مقدار = c_fully_fold (کم_مقدار, نادرست, پوچ);
      اگر (درخت_CODE (کم_مقدار) == INTEGER_CST)
	pedwarn (loc, OPT_Wpedantic,
		 "case label is not an integer constant expression");
    }

  اگر (بالا_مقدار && درخت_CODE (بالا_مقدار) != INTEGER_CST)
    {
      بالا_مقدار = c_fully_fold (بالا_مقدار, نادرست, پوچ);
      اگر (درخت_CODE (بالا_مقدار) == INTEGER_CST)
	pedwarn (درون_داد_location, OPT_Wpedantic,
		 "case label is not an integer constant expression");
    }

  اگر (c_switch_پشته == پوچ)
    {
      اگر (کم_مقدار)
	error_at (loc, "case label not within a switch statement");
      وگرنه
	error_at (loc, "%<default%> label not within a switch statement");
      بازگشت NULL_درخت;
    }

  اگر (c_check_switch_jump_warnings (c_switch_پشته->bindings,
				    عبارت_LOCATION (c_switch_پشته->switch_stmt),
				    loc))
    بازگشت NULL_درخت;

  label = c_add_case_label (loc, c_switch_پشته->cases,
			    SWITCH_STMT_COND (c_switch_پشته->switch_stmt),
			    کم_مقدار, بالا_مقدار, attrs);
  اگر (label == error_mark_گره)
    label = NULL_درخت;
  بازگشت label;
}

/* Finish the switch statement.  TYPE is the original type of the
   controlling expression of the switch, or NULL_TREE.  */

تهی
c_finish_switch (درخت body, درخت type)
{
  ساختار c_switch *cs = c_switch_پشته;
  location_t switch_location;

  SWITCH_STMT_BODY (cs->switch_stmt) = body;

  /* Emit warnings as needed.  */
  switch_location = عبارت_LOCATION (cs->switch_stmt);
  c_do_switch_warnings (cs->cases, switch_location,
			type ? type : SWITCH_STMT_TYPE (cs->switch_stmt),
			SWITCH_STMT_COND (cs->switch_stmt), cs->bool_cond_p);
  اگر (c_switch_covers_all_cases_p (cs->cases,
				   SWITCH_STMT_TYPE (cs->switch_stmt)))
    SWITCH_STMT_ALL_CASES_P (cs->switch_stmt) = 1;
  SWITCH_STMT_NO_BREAK_P (cs->switch_stmt) = !cs->break_stmt_seen_p;

  /* Pop the stack.  */
  c_switch_پشته = cs->next;
  splay_درخت_delete (cs->cases);
  c_release_switch_bindings (cs->bindings);
  XDELETE (cs);
}

/* Emit an if statement.  IF_LOCUS is the location of the 'if'.  COND,
   THEN_BLOCK and ELSE_BLOCK are expressions to be used; ELSE_BLOCK
   may be null.  */

تهی
c_finish_if_stmt (location_t if_locus, درخت cond, درخت then_block,
		  درخت else_block)
{
  درخت stmt;

  stmt = build3 (COND_عبارت, void_type_گره, cond, then_block, else_block);
  SET_عبارت_LOCATION (stmt, if_locus);
  add_stmt (stmt);
}

درخت
c_finish_bc_stmt (location_t loc, درخت label, منطقی is_break, درخت name)
{
  /* In switch statements break is sometimes stylistically used after
     a return statement.  This can lead to spurious warnings about
     control reaching the end of a non-void function when it is
     inlined.  Note that we are calling block_may_fallthru with
     language specific tree nodes; this works because
     block_may_fallthru returns true when given something it does not
     understand.  */
  منطقی skip = !block_may_fallthru (cur_stmt_list);

  اگر (is_break)
    انتخاب (in_statement & ~IN_NAMED_STMT)
      {
      حالت 0:
	error_at (loc, "break statement not within loop or switch");
	بازگشت NULL_درخت;
      حالت IN_OMP_BLOCK:
	error_at (loc, "invalid exit from OpenMP structured block");
	بازگشت NULL_درخت;
      حالت IN_OMP_FOR:
	error_at (loc, "break statement used with OpenMP for loop");
	بازگشت NULL_درخت;
      حالت IN_ITERATION_STMT:
      حالت IN_OBJC_FOREACH:
	بشکن;
      پیشفرض:
	gcc_assert (in_statement & IN_SWITCH_STMT);
	c_switch_پشته->break_stmt_seen_p = درست;
	بشکن;
      }
  وگرنه
    انتخاب (in_statement & ~(IN_SWITCH_STMT | IN_NAMED_STMT))
      {
      حالت 0:
	error_at (loc, "continue statement not within a loop");
	بازگشت NULL_درخت;
      حالت IN_OMP_BLOCK:
	error_at (loc, "invalid exit from OpenMP structured block");
	بازگشت NULL_درخت;
      حالت IN_ITERATION_STMT:
      حالت IN_OMP_FOR:
      حالت IN_OBJC_FOREACH:
	بشکن;
      پیشفرض:
	gcc_unreachable ();
      }

  اگر (skip)
    بازگشت NULL_درخت;
  وگرنه اگر ((in_statement & IN_OBJC_FOREACH)
	   && !(is_break && (in_statement & IN_SWITCH_STMT))
	   && name == NULL_درخت)
    {
      /* The foreach expander produces low-level code using gotos instead
	 of a structured loop construct.  */
      gcc_assert (label);
      بازگشت add_stmt (build_stmt (loc, GOTO_عبارت, label));
    }
  وگرنه اگر (name && C_DECL_LOOP_NAME (name) && C_DECL_SWITCH_NAME (name))
    {
      label = DECL_CHAIN (name);
      اگر (!is_break)
	label = DECL_CHAIN (label);
      /* Foreach expander from some outer level.  */
      بازگشت add_stmt (build_stmt (loc, GOTO_عبارت, label));
    }
  بازگشت add_stmt (build_stmt (loc, is_break ? BREAK_STMT : CONTINUE_STMT,
			       name));
}

/* A helper routine for c_process_expr_stmt and c_finish_stmt_expr.  */

ایستا تهی
emit_side_effect_warnings (location_t loc, درخت عبارت)
{
  maybe_warn_nodiscard (loc, عبارت);
  اگر (!warn_unused_مقدار)
    بازگشت;
  اگر (عبارت == error_mark_گره)
    ;
  وگرنه اگر (!درخت_SIDE_EFFECTS (عبارت))
    {
      اگر (!VOID_TYPE_P (درخت_TYPE (عبارت))
	  && !warning_suppressed_p (عبارت, OPT_Wunused_مقدار))
	warning_at (loc, OPT_Wunused_مقدار, "statement with no effect");
    }
  وگرنه اگر (درخت_CODE (عبارت) == COMPOUND_عبارت)
    {
      درخت r = عبارت;
      location_t cloc = loc;
      وقتی (درخت_CODE (r) == COMPOUND_عبارت)
	{
	  اگر (عبارت_HAS_LOCATION (r))
	    cloc = عبارت_LOCATION (r);
	  r = درخت_OPERAND (r, 1);
	}
      اگر (!درخت_SIDE_EFFECTS (r)
	  && !VOID_TYPE_P (درخت_TYPE (r))
	  && !CONVERT_عبارت_P (r)
	  && !warning_suppressed_p (r, OPT_Wunused_مقدار)
	  && !warning_suppressed_p (عبارت, OPT_Wunused_مقدار))
	warning_at (cloc, OPT_Wunused_مقدار,
		    "right-hand operand of comma expression has no effect");
    }
  وگرنه
    warn_if_unused_مقدار (عبارت, loc);
}

/* Process an expression as if it were a complete statement.  Emit
   diagnostics, but do not call ADD_STMT.  LOC is the location of the
   statement.  */

درخت
c_process_عبارت_stmt (location_t loc, درخت عبارت)
{
  درخت exprv;

  اگر (!عبارت)
    بازگشت NULL_درخت;

  عبارت = c_fully_fold (عبارت, نادرست, پوچ);

  اگر (warn_sequence_point)
    verify_sequence_points (عبارت);

  اگر (درخت_TYPE (عبارت) != error_mark_گره
      && !COMPLETE_OR_VOID_TYPE_P (درخت_TYPE (عبارت))
      && درخت_CODE (درخت_TYPE (عبارت)) != ARRAY_TYPE)
    error_at (loc, "expression statement has incomplete type");

  /* If we're not processing a statement expression, warn about unused values.
     Warnings for statement expressions will be emitted later, once we figure
     out which is the result.  */
  اگر (!STATEMENT_LIST_STMT_عبارت (cur_stmt_list)
      && (warn_unused_مقدار || warn_unused_result))
    emit_side_effect_warnings (عبارت_LOC_OR_LOC (عبارت, loc), عبارت);

  exprv = عبارت;
  وقتی (درخت_CODE (exprv) == COMPOUND_عبارت)
    exprv = درخت_OPERAND (exprv, 1);
  وقتی (CONVERT_عبارت_P (exprv))
    exprv = درخت_OPERAND (exprv, 0);
  اگر (DECL_P (exprv)
      || handled_component_p (exprv)
      || درخت_CODE (exprv) == ADDR_عبارت)
    mark_exp_read (exprv);

  /* If the expression is not of a type to which we cannot assign a line
     number, wrap the thing in a no-op NOP_EXPR.  */
  اگر (DECL_P (عبارت) || CONSTANT_CLASS_P (عبارت))
    {
      عبارت = build1 (NOP_عبارت, درخت_TYPE (عبارت), عبارت);
      SET_عبارت_LOCATION (عبارت, loc);
    }

  بازگشت عبارت;
}

/* Emit an expression as a statement.  LOC is the location of the
   expression.  */

درخت
c_finish_عبارت_stmt (location_t loc, درخت عبارت)
{
  اگر (عبارت)
    بازگشت add_stmt (c_process_عبارت_stmt (loc, عبارت));
  وگرنه
    بازگشت پوچ;
}

/* Do the opposite and emit a statement as an expression.  To begin,
   create a new binding level and return it.  */

درخت
c_begin_stmt_عبارت (تهی)
{
  درخت ret;

  /* We must force a BLOCK for this level so that, if it is not expanded
     later, there is a way to turn off the entire subtree of blocks that
     are contained in it.  */
  keep_next_level ();
  ret = c_begin_compound_stmt (درست);

  c_bindings_start_stmt_عبارت (c_switch_پشته == پوچ
			      ? پوچ
			      : c_switch_پشته->bindings);

  /* Mark the current statement list as belonging to a statement list.  */
  STATEMENT_LIST_STMT_عبارت (ret) = 1;

  بازگشت ret;
}

/* LOC is the location of the compound statement to which this body
   belongs.  */

درخت
c_finish_stmt_عبارت (location_t loc, درخت body)
{
  درخت last, type, tmp, val;
  درخت *last_p;

  body = c_end_compound_stmt (loc, body, درست);

  c_bindings_end_stmt_عبارت (c_switch_پشته == پوچ
			    ? پوچ
			    : c_switch_پشته->bindings);

  /* Locate the last statement in BODY.  See c_end_compound_stmt
     about always returning a BIND_EXPR.  */
  last_p = &BIND_عبارت_BODY (body);
  last = BIND_عبارت_BODY (body);

 continue_searching:
  اگر (درخت_CODE (last) == STATEMENT_LIST)
    {
      درخت_stmt_iterator l = tsi_last (last);

      وقتی (!tsi_end_p (l) && درخت_CODE (tsi_stmt (l)) == DEBUG_BEGIN_STMT)
	tsi_prev (&l);

      /* This can happen with degenerate cases like ({ }).  No value.  */
      اگر (tsi_end_p (l))
	بازگشت body;

      /* If we're supposed to generate side effects warnings, process
	 all of the statements except the last.  */
      اگر (warn_unused_مقدار || warn_unused_result)
	{
	  برای (درخت_stmt_iterator i = tsi_start (last);
	       tsi_stmt (i) != tsi_stmt (l); tsi_next (&i))
	    {
	      location_t tloc;
	      درخت t = tsi_stmt (i);

	      tloc = عبارت_HAS_LOCATION (t) ? عبارت_LOCATION (t) : loc;
	      emit_side_effect_warnings (tloc, t);
	    }
	}
      last_p = tsi_stmt_ptr (l);
      last = *last_p;
    }

  /* If the end of the list is exception related, then the list was split
     by a call to push_cleanup.  Continue searching.  */
  اگر (درخت_CODE (last) == TRY_FINALLY_عبارت
      || درخت_CODE (last) == TRY_CATCH_عبارت)
    {
      last_p = &درخت_OPERAND (last, 0);
      last = *last_p;
      برو continue_searching;
    }

  اگر (last == error_mark_گره)
    بازگشت last;

  /* In the case that the BIND_EXPR is not necessary, return the
     expression out from inside it.  */
  اگر ((last == BIND_عبارت_BODY (body)
       /* Skip nested debug stmts.  */
       || last == عبارت_first (BIND_عبارت_BODY (body)))
      && BIND_عبارت_VARS (body) == پوچ)
    {
      /* Even if this looks constant, do not allow it in a constant
	 expression.  */
      last = c_wrap_maybe_const (last, درست);
      /* Do not warn if the return value of a statement expression is
	 unused.  */
      suppress_warning (last, OPT_Wunused);
      بازگشت last;
    }

  /* Extract the type of said expression.  */
  type = درخت_TYPE (last);

  /* If we're not returning a value at all, then the BIND_EXPR that
     we already have is a fine expression to return.  */
  اگر (!type || VOID_TYPE_P (type))
    بازگشت body;

  /* Now that we've located the expression containing the value, it seems
     silly to make voidify_wrapper_expr repeat the process.  Create a
     temporary of the appropriate type and stick it in a TARGET_EXPR.  */
  tmp = create_tmp_var_raw (type);

  /* Unwrap a no-op NOP_EXPR as added by c_finish_expr_stmt.  This avoids
     tree_expr_nonnegative_p giving up immediately.  */
  val = last;
  اگر (درخت_CODE (val) == NOP_عبارت
      && درخت_TYPE (val) == درخت_TYPE (درخت_OPERAND (val, 0)))
    val = درخت_OPERAND (val, 0);

  *last_p = build2 (MODIFY_عبارت, void_type_گره, tmp, val);
  SET_عبارت_LOCATION (*last_p, عبارت_LOCATION (last));

  {
    درخت t = build4 (TARGET_عبارت, type, tmp, body, NULL_درخت, NULL_درخت);
    SET_عبارت_LOCATION (t, loc);
    بازگشت t;
  }
}

/* Begin and end compound statements.  This is as simple as pushing
   and popping new statement lists from the tree.  */

درخت
c_begin_compound_stmt (منطقی do_scope)
{
  درخت stmt = افزودن_stmt_list ();
  اگر (do_scope)
    افزودن_scope ();
  بازگشت stmt;
}

/* End a compound statement.  STMT is the statement.  LOC is the
   location of the compound statement-- this is usually the location
   of the opening brace.  */

درخت
c_end_compound_stmt (location_t loc, درخت stmt, منطقی do_scope)
{
  درخت block = پوچ;

  اگر (do_scope)
    {
      اگر (c_dialect_objc ())
	objc_clear_super_receiver ();
      block = برداشت_scope ();
    }

  stmt = برداشت_stmt_list (stmt);
  stmt = c_build_bind_عبارت (loc, block, stmt);

  /* If this compound statement is nested immediately inside a statement
     expression, then force a BIND_EXPR to be created.  Otherwise we'll
     do the wrong thing for ({ { 1; } }) or ({ 1; { } }).  In particular,
     STATEMENT_LISTs merge, and thus we can lose track of what statement
     was really last.  */
  اگر (building_stmt_list_p ()
      && STATEMENT_LIST_STMT_عبارت (cur_stmt_list)
      && درخت_CODE (stmt) != BIND_عبارت)
    {
      stmt = build3 (BIND_عبارت, void_type_گره, پوچ, stmt, پوچ);
      درخت_SIDE_EFFECTS (stmt) = 1;
      SET_عبارت_LOCATION (stmt, loc);
    }

  بازگشت stmt;
}

/* Queue a cleanup.  CLEANUP is an expression/statement to be executed
   when the current scope is exited.  EH_ONLY is true when this is not
   meant to apply to normal control flow transfer.  */

تهی
افزودن_cleanup (درخت decl, درخت cleanup, منطقی eh_only)
{
  شمارش درخت_code code;
  درخت stmt, list;
  منطقی stmt_عبارت;

  code = eh_only ? TRY_CATCH_عبارت : TRY_FINALLY_عبارت;
  stmt = build_stmt (DECL_SOURCE_LOCATION (decl), code, پوچ, cleanup);
  add_stmt (stmt);
  stmt_عبارت = STATEMENT_LIST_STMT_عبارت (cur_stmt_list);
  list = افزودن_stmt_list ();
  درخت_OPERAND (stmt, 0) = list;
  STATEMENT_LIST_STMT_عبارت (list) = stmt_عبارت;
}

/* Build a vector comparison of ARG0 and ARG1 using CODE opcode
   into a value of TYPE type.  Comparison is done via VEC_COND_EXPR.  */

ایستا درخت
build_vec_cmp (درخت_code code, درخت type,
	       درخت arg0, درخت arg1)
{
  درخت zero_vec = build_zero_cst (type);
  درخت minus_one_vec = build_minus_one_cst (type);
  درخت cmp_type = truth_type_for (درخت_TYPE (arg0));
  درخت cmp = build2 (code, cmp_type, arg0, arg1);
  بازگشت build3 (VEC_COND_عبارت, type, cmp, minus_one_vec, zero_vec);
}

/* Possibly warn about an address of OP never being NULL in a comparison
   operation CODE involving null.  */

ایستا تهی
maybe_warn_for_null_address (location_t loc, درخت op, درخت_code code)
{
  /* Prevent warnings issued for macro expansion.  */
  اگر (!warn_address
      || warning_suppressed_p (op, OPT_Waddress)
      || from_macro_expansion_at (loc))
    بازگشت;

  اگر (درخت_CODE (op) == NOP_عبارت)
    {
      /* Allow casts to intptr_t to suppress the warning.  */
      درخت type = درخت_TYPE (op);
      اگر (درخت_CODE (type) == INTEGER_TYPE)
	بازگشت;
      op = درخت_OPERAND (op, 0);
    }

  اگر (درخت_CODE (op) == POINTER_PLUS_عبارت)
    {
      /* Allow a cast to void* to suppress the warning.  */
      درخت type = درخت_TYPE (درخت_TYPE (op));
      اگر (VOID_TYPE_P (type))
	بازگشت;

      /* Adding any value to a null pointer, including zero, is undefined
	 in C.  This includes the expression &p[0] where p is the null
	 pointer, although &p[0] will have been folded to p by this point
	 and so not diagnosed.  */
      اگر (code == EQ_عبارت)
	warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<false%> "
		    "for the pointer operand in %qE must not be NULL",
		    op);
      وگرنه
	warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<true%> "
		    "for the pointer operand in %qE must not be NULL",
		    op);

      بازگشت;
    }

  اگر (درخت_CODE (op) != ADDR_عبارت)
    بازگشت;

  op = درخت_OPERAND (op, 0);

  اگر (درخت_CODE (op) == IMAGPART_عبارت
      || درخت_CODE (op) == REALPART_عبارت)
    {
      /* The address of either complex part may not be null.  */
      اگر (code == EQ_عبارت)
	warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<false%> "
		    "for the address of %qE will never be NULL",
		    op);
      وگرنه
	warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<true%> "
		    "for the address of %qE will never be NULL",
		    op);
      بازگشت;
    }

  /* Set to true in the loop below if OP dereferences is operand.
     In such a case the ultimate target need not be a decl for
     the null [in]equality test to be constant.  */
  منطقی deref = نادرست;

  /* Get the outermost array or object, or member.  */
  وقتی (handled_component_p (op))
    {
      اگر (درخت_CODE (op) == COMPONENT_REF)
	{
	  /* Get the member (its address is never null).  */
	  op = درخت_OPERAND (op, 1);
	  بشکن;
	}

      /* Get the outer array/object to refer to in the warning.  */
      op = درخت_OPERAND (op, 0);
      deref = درست;
    }

  اگر ((!deref && !decl_with_nonnull_addr_p (op))
      || from_macro_expansion_at (loc))
    بازگشت;

  منطقی w;
  اگر (code == EQ_عبارت)
    w = warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<false%> "
		    "for the address of %qE will never be NULL",
		    op);
  وگرنه
    w = warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<true%> "
		    "for the address of %qE will never be NULL",
		    op);

  اگر (w && DECL_P (op))
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

درخت
build_دودویی_op (location_t location, شمارش درخت_code code,
		 درخت orig_op0, درخت orig_op1, منطقی convert_p)
{
  درخت type0, type1, orig_type0, orig_type1;
  درخت eptype;
  شمارش درخت_code code0, code1;
  درخت op0, op1;
  درخت ret = error_mark_گره;
  ثابت نویسه *invalid_op_diag;
  منطقی op0_int_operands, op1_int_operands;
  منطقی int_const, int_const_or_overflow, int_operands;

  /* Expression code to give to the expression when it is built.
     Normally this is CODE, which is what the caller asked for,
     but in some special cases we change it.  */
  شمارش درخت_code resultcode = code;

  /* Data type in which the computation is to be performed.
     In the simplest cases this is the common type of the arguments.  */
  درخت result_type = پوچ;

  /* When the computation is in excess precision, the type of the
     final EXCESS_PRECISION_EXPR.  */
  درخت semantic_result_type = پوچ;

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
  صحیح short_shift = 0;

  /* Nonzero means set RESULT_TYPE to the common type of the args.  */
  صحیح common = 0;

  /* True means types are compatible as far as ObjC is concerned.  */
  منطقی objc_ok;

  /* True means this is an arithmetic operation that may need excess
     precision.  */
  منطقی may_need_excess_precision;

  /* True means this is a boolean operation that converts both its
     operands to truth-values.  */
  منطقی boolean_op = نادرست;

  /* Remember whether we're doing / or %.  */
  منطقی doing_div_or_mod = نادرست;

  /* Remember whether we're doing << or >>.  */
  منطقی doing_shift = نادرست;

  /* Tree holding instrumentation expression.  */
  درخت instrument_عبارت = پوچ;

  اگر (location == UNKNOWN_LOCATION)
    location = درون_داد_location;

  op0 = orig_op0;
  op1 = orig_op1;

  op0_int_operands = عبارت_INT_CONST_OPERANDS (orig_op0);
  اگر (op0_int_operands)
    op0 = remove_c_maybe_const_عبارت (op0);
  op1_int_operands = عبارت_INT_CONST_OPERANDS (orig_op1);
  اگر (op1_int_operands)
    op1 = remove_c_maybe_const_عبارت (op1);
  int_operands = (op0_int_operands && op1_int_operands);
  اگر (int_operands)
    {
      int_const_or_overflow = (درخت_CODE (orig_op0) == INTEGER_CST
			       && درخت_CODE (orig_op1) == INTEGER_CST);
      int_const = (int_const_or_overflow
		   && !درخت_OVERFLOW (orig_op0)
		   && !درخت_OVERFLOW (orig_op1));
    }
  وگرنه
    int_const = int_const_or_overflow = نادرست;

  /* Do not apply default conversion in mixed vector/scalar expression.  */
  اگر (convert_p
      && VECTOR_TYPE_P (درخت_TYPE (op0)) == VECTOR_TYPE_P (درخت_TYPE (op1)))
    {
      op0 = default_conversion (op0);
      op1 = default_conversion (op1);
    }

  orig_type0 = type0 = درخت_TYPE (op0);

  orig_type1 = type1 = درخت_TYPE (op1);

  /* The expression codes of the data types of the arguments tell us
     whether the arguments are integers, floating, pointers, etc.  */
  code0 = درخت_CODE (type0);
  code1 = درخت_CODE (type1);

  /* Strip NON_LVALUE_EXPRs, etc., since we aren't using as an lvalue.  */
  STRIP_TYPE_NOPS (op0);
  STRIP_TYPE_NOPS (op1);

  /* If an error was already reported for one of the arguments,
     avoid reporting another error.  */

  اگر (code0 == ERROR_MARK || code1 == ERROR_MARK)
    بازگشت error_mark_گره;

  اگر (code0 == POINTER_TYPE
      && reject_gcc_builtin (op0, عبارت_LOCATION (orig_op0)))
    بازگشت error_mark_گره;

  اگر (code1 == POINTER_TYPE
      && reject_gcc_builtin (op1, عبارت_LOCATION (orig_op1)))
    بازگشت error_mark_گره;

  اگر ((invalid_op_diag
       = targetm.invalid_دودویی_op (code, type0, type1)))
    {
      error_at (location, invalid_op_diag);
      بازگشت error_mark_گره;
    }

  انتخاب (code)
    {
    حالت PLUS_عبارت:
    حالت MINUS_عبارت:
    حالت MULT_عبارت:
    حالت TRUNC_DIV_عبارت:
    حالت CEIL_DIV_عبارت:
    حالت FLOOR_DIV_عبارت:
    حالت ROUND_DIV_عبارت:
    حالت EXACT_DIV_عبارت:
      may_need_excess_precision = درست;
      بشکن;

    حالت EQ_عبارت:
    حالت NE_عبارت:
    حالت LE_عبارت:
    حالت GE_عبارت:
    حالت LT_عبارت:
    حالت GT_عبارت:
      /* Excess precision for implicit conversions of integers to
	 floating point in C11 and later.  */
      may_need_excess_precision = (flag_isoc11
				   && (ANY_INTEGRAL_TYPE_P (type0)
				       || ANY_INTEGRAL_TYPE_P (type1)));
      بشکن;

    پیشفرض:
      may_need_excess_precision = نادرست;
      بشکن;
    }
  اگر (درخت_CODE (op0) == EXCESS_PRECISION_عبارت)
    {
      op0 = درخت_OPERAND (op0, 0);
      type0 = درخت_TYPE (op0);
    }
  وگرنه اگر (may_need_excess_precision
	   && (eptype = excess_precision_type (type0)) != NULL_درخت)
    {
      type0 = eptype;
      op0 = convert (eptype, op0);
    }
  اگر (درخت_CODE (op1) == EXCESS_PRECISION_عبارت)
    {
      op1 = درخت_OPERAND (op1, 0);
      type1 = درخت_TYPE (op1);
    }
  وگرنه اگر (may_need_excess_precision
	   && (eptype = excess_precision_type (type1)) != NULL_درخت)
    {
      type1 = eptype;
      op1 = convert (eptype, op1);
    }

  objc_ok = objc_compare_types (type0, type1, -3, NULL_درخت);

  /* In case when one of the operands of the binary operation is
     a vector and another is a scalar -- convert scalar to vector.  */
  اگر ((gnu_vector_type_p (type0) && code1 != VECTOR_TYPE)
      || (gnu_vector_type_p (type1) && code0 != VECTOR_TYPE))
    {
      شمارش stv_conv convert_flag = scalar_to_vector (location, code, orig_op0,
						     orig_op1, درست);

      انتخاب (convert_flag)
	{
	  حالت stv_error:
	    بازگشت error_mark_گره;
	  حالت stv_firstarg:
	    {
              منطقی maybe_const = درست;
              درخت sc;
              sc = c_fully_fold (op0, نادرست, &maybe_const);
              sc = save_عبارت (sc);
              sc = convert (درخت_TYPE (type1), sc);
              op0 = build_vector_from_val (type1, sc);
              اگر (!maybe_const)
                op0 = c_wrap_maybe_const (op0, درست);
              orig_type0 = type0 = درخت_TYPE (op0);
              code0 = درخت_CODE (type0);
              converted = 1;
              بشکن;
	    }
	  حالت stv_secondarg:
	    {
	      منطقی maybe_const = درست;
	      درخت sc;
	      sc = c_fully_fold (op1, نادرست, &maybe_const);
	      sc = save_عبارت (sc);
	      sc = convert (درخت_TYPE (type0), sc);
	      op1 = build_vector_from_val (type0, sc);
	      اگر (!maybe_const)
		op1 = c_wrap_maybe_const (op1, درست);
	      orig_type1 = type1 = درخت_TYPE (op1);
	      code1 = درخت_CODE (type1);
	      converted = 1;
	      بشکن;
	    }
	  پیشفرض:
	    بشکن;
	}
    }

  انتخاب (code)
    {
    حالت PLUS_عبارت:
      /* Handle the pointer + int case.  */
      اگر (code0 == POINTER_TYPE
	  && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  ret = pointer_int_sum (location, PLUS_عبارت, op0, op1);
	  برو return_build_دودویی_op;
	}
      وگرنه اگر (code1 == POINTER_TYPE
	       && (code0 == INTEGER_TYPE || code0 == BITINT_TYPE))
	{
	  ret = pointer_int_sum (location, PLUS_عبارت, op1, op0);
	  برو return_build_دودویی_op;
	}
      وگرنه
	common = 1;
      بشکن;

    حالت MINUS_عبارت:
      /* Subtraction of two similar pointers.
	 We must subtract them as integers, then divide by object size.  */
      اگر (code0 == POINTER_TYPE && code1 == POINTER_TYPE
	  && comp_target_types (location, type0, type1))
	{
	  ret = pointer_diff (location, op0, op1, &instrument_عبارت);
	  برو return_build_دودویی_op;
	}
      /* Handle pointer minus int.  Just like pointer plus int.  */
      وگرنه اگر (code0 == POINTER_TYPE
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  ret = pointer_int_sum (location, MINUS_عبارت, op0, op1);
	  برو return_build_دودویی_op;
	}
      وگرنه
	common = 1;
      بشکن;

    حالت MULT_عبارت:
      common = 1;
      بشکن;

    حالت TRUNC_DIV_عبارت:
    حالت CEIL_DIV_عبارت:
    حالت FLOOR_DIV_عبارت:
    حالت ROUND_DIV_عبارت:
    حالت EXACT_DIV_عبارت:
      doing_div_or_mod = درست;
      warn_for_div_by_zero (location, op1);

      اگر ((code0 == INTEGER_TYPE || code0 == REAL_TYPE
	   || code0 == FIXED_POINT_TYPE || code0 == BITINT_TYPE
	   || code0 == COMPLEX_TYPE
	   || gnu_vector_type_p (type0))
	  && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	      || code1 == FIXED_POINT_TYPE || code1 == BITINT_TYPE
	      || code1 == COMPLEX_TYPE
	      || gnu_vector_type_p (type1)))
	{
	  شمارش درخت_code tcode0 = code0, tcode1 = code1;

	  اگر (code0 == COMPLEX_TYPE || code0 == VECTOR_TYPE)
	    tcode0 = درخت_CODE (درخت_TYPE (درخت_TYPE (op0)));
	  اگر (code1 == COMPLEX_TYPE || code1 == VECTOR_TYPE)
	    tcode1 = درخت_CODE (درخت_TYPE (درخت_TYPE (op1)));

	  اگر (!(((tcode0 == INTEGER_TYPE || tcode0 == BITINT_TYPE
		  || (tcode0 == ENUMERAL_TYPE && code0 == VECTOR_TYPE))
		 && (tcode1 == INTEGER_TYPE || tcode1 == BITINT_TYPE
		     || (tcode1 == ENUMERAL_TYPE && code1 == VECTOR_TYPE)))
		|| (tcode0 == FIXED_POINT_TYPE && tcode1 == FIXED_POINT_TYPE)))
	    resultcode = RDIV_عبارت;
	  وگرنه
	    /* Although it would be tempting to shorten always here, that
	       loses on some targets, since the modulo instruction is
	       undefined if the quotient can't be represented in the
	       computation mode.  We shorten only if unsigned or if
	       dividing by something we know != -1.  */
	    shorten = may_shorten_divmod (op0, op1);
	  common = 1;
	}
      بشکن;

    حالت BIT_AND_عبارت:
    حالت BIT_IOR_عبارت:
    حالت BIT_XOR_عبارت:
      اگر ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	shorten = -1;
      /* Allow vector types which are not floating point types.   */
      وگرنه اگر (gnu_vector_type_p (type0)
	       && gnu_vector_type_p (type1)
	       && !VECTOR_FLOAT_TYPE_P (type0)
	       && !VECTOR_FLOAT_TYPE_P (type1))
	common = 1;
      بشکن;

    حالت TRUNC_MOD_عبارت:
    حالت FLOOR_MOD_عبارت:
      doing_div_or_mod = درست;
      warn_for_div_by_zero (location, op1);

      اگر (gnu_vector_type_p (type0)
	  && gnu_vector_type_p (type1)
	  && درخت_CODE (درخت_TYPE (type0)) == INTEGER_TYPE
	  && درخت_CODE (درخت_TYPE (type1)) == INTEGER_TYPE)
	common = 1;
      وگرنه اگر ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  /* Although it would be tempting to shorten always here, that loses
	     on some targets, since the modulo instruction is undefined if the
	     quotient can't be represented in the computation mode.  We shorten
	     only if unsigned or if dividing by something we know != -1.  */
	  shorten = may_shorten_divmod (op0, op1);
	  common = 1;
	}
      بشکن;

    حالت TRUTH_ANDIF_عبارت:
    حالت TRUTH_ORIF_عبارت:
    حالت TRUTH_AND_عبارت:
    حالت TRUTH_OR_عبارت:
    حالت TRUTH_XOR_عبارت:
      اگر ((code0 == INTEGER_TYPE || code0 == POINTER_TYPE
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
	  result_type = integer_type_گره;
	  اگر (op0_int_operands)
	    {
	      op0 = c_objc_common_truthvalue_conversion (location, orig_op0);
	      op0 = remove_c_maybe_const_عبارت (op0);
	    }
	  وگرنه
	    op0 = c_objc_common_truthvalue_conversion (location, op0);
	  اگر (op1_int_operands)
	    {
	      op1 = c_objc_common_truthvalue_conversion (location, orig_op1);
	      op1 = remove_c_maybe_const_عبارت (op1);
	    }
	  وگرنه
	    op1 = c_objc_common_truthvalue_conversion (location, op1);
	  converted = 1;
	  boolean_op = درست;
	}
      اگر (code == TRUTH_ANDIF_عبارت)
	{
	  int_const_or_overflow = (int_operands
				   && درخت_CODE (orig_op0) == INTEGER_CST
				   && (op0 == truthvalue_false_گره
				       || درخت_CODE (orig_op1) == INTEGER_CST));
	  int_const = (int_const_or_overflow
		       && !درخت_OVERFLOW (orig_op0)
		       && (op0 == truthvalue_false_گره
			   || !درخت_OVERFLOW (orig_op1)));
	}
      وگرنه اگر (code == TRUTH_ORIF_عبارت)
	{
	  int_const_or_overflow = (int_operands
				   && درخت_CODE (orig_op0) == INTEGER_CST
				   && (op0 == truthvalue_true_گره
				       || درخت_CODE (orig_op1) == INTEGER_CST));
	  int_const = (int_const_or_overflow
		       && !درخت_OVERFLOW (orig_op0)
		       && (op0 == truthvalue_true_گره
			   || !درخت_OVERFLOW (orig_op1)));
	}
      بشکن;

      /* Shift operations: result has same type as first operand;
	 always convert second operand to int.
	 Also set SHORT_SHIFT if shifting rightward.  */

    حالت RSHIFT_عبارت:
      اگر (gnu_vector_type_p (type0)
	  && gnu_vector_type_p (type1)
	  && درخت_CODE (درخت_TYPE (type0)) == INTEGER_TYPE
	  && درخت_CODE (درخت_TYPE (type1)) == INTEGER_TYPE
	  && known_eq (TYPE_VECTOR_SUBPARTS (type0),
		       TYPE_VECTOR_SUBPARTS (type1)))
	{
	  result_type = type0;
	  converted = 1;
	}
      وگرنه اگر ((code0 == INTEGER_TYPE || code0 == FIXED_POINT_TYPE
		|| code0 == BITINT_TYPE
		|| (gnu_vector_type_p (type0)
		    && درخت_CODE (درخت_TYPE (type0)) == INTEGER_TYPE))
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  doing_shift = درست;
	  اگر (درخت_CODE (op1) == INTEGER_CST)
	    {
	      اگر (درخت_int_cst_sgn (op1) < 0)
		{
		  int_const = نادرست;
		  اگر (c_inhibit_evaluation_warnings == 0)
		    warning_at (location, OPT_Wshift_شمار_negative,
				"right shift count is negative");
		}
	      وگرنه اگر (code0 == VECTOR_TYPE)
		{
		  اگر (compare_درخت_int (op1,
					TYPE_PRECISION (درخت_TYPE (type0)))
		      >= 0)
		    {
		      int_const = نادرست;
		      اگر (c_inhibit_evaluation_warnings == 0)
			warning_at (location, OPT_Wshift_شمار_overflow,
				    "right shift count >= width of vector element");
		    }
		}
	      وگرنه
		{
		  اگر (!integer_zerop (op1))
		    short_shift = 1;

		  اگر (compare_درخت_int (op1, TYPE_PRECISION (type0)) >= 0)
		    {
		      int_const = نادرست;
		      اگر (c_inhibit_evaluation_warnings == 0)
			warning_at (location, OPT_Wshift_شمار_overflow,
				    "right shift count >= width of type");
		    }
		}
	    }

	  /* Use the type of the value to be shifted.  */
	  result_type = type0;
	  /* Avoid converting op1 to result_type later.  */
	  converted = 1;
	}
      بشکن;

    حالت LSHIFT_عبارت:
      اگر (gnu_vector_type_p (type0)
	  && gnu_vector_type_p (type1)
	  && درخت_CODE (درخت_TYPE (type0)) == INTEGER_TYPE
	  && درخت_CODE (درخت_TYPE (type1)) == INTEGER_TYPE
	  && known_eq (TYPE_VECTOR_SUBPARTS (type0),
		       TYPE_VECTOR_SUBPARTS (type1)))
	{
	  result_type = type0;
	  converted = 1;
	}
      وگرنه اگر ((code0 == INTEGER_TYPE || code0 == FIXED_POINT_TYPE
		|| code0 == BITINT_TYPE
		|| (gnu_vector_type_p (type0)
		    && درخت_CODE (درخت_TYPE (type0)) == INTEGER_TYPE))
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  doing_shift = درست;
	  اگر (درخت_CODE (op0) == INTEGER_CST
	      && درخت_int_cst_sgn (op0) < 0
	      && !TYPE_OVERFLOW_WRAPS (type0))
	    {
	      /* Don't reject a left shift of a negative value in a context
		 where a constant expression is needed in C90.  */
	      اگر (flag_isoc99)
		int_const = نادرست;
	      اگر (c_inhibit_evaluation_warnings == 0)
		warning_at (location, OPT_Wshift_negative_مقدار,
			    "left shift of negative value");
	    }
	  اگر (درخت_CODE (op1) == INTEGER_CST)
	    {
	      اگر (درخت_int_cst_sgn (op1) < 0)
		{
		  int_const = نادرست;
		  اگر (c_inhibit_evaluation_warnings == 0)
		    warning_at (location, OPT_Wshift_شمار_negative,
				"left shift count is negative");
		}
	      وگرنه اگر (code0 == VECTOR_TYPE)
		{
		  اگر (compare_درخت_int (op1,
					TYPE_PRECISION (درخت_TYPE (type0)))
		      >= 0)
		    {
		      int_const = نادرست;
		      اگر (c_inhibit_evaluation_warnings == 0)
			warning_at (location, OPT_Wshift_شمار_overflow,
				    "left shift count >= width of vector element");
		    }
		}
	      وگرنه اگر (compare_درخت_int (op1, TYPE_PRECISION (type0)) >= 0)
		{
		  int_const = نادرست;
		  اگر (c_inhibit_evaluation_warnings == 0)
		    warning_at (location, OPT_Wshift_شمار_overflow,
				"left shift count >= width of type");
		}
	      وگرنه اگر (درخت_CODE (op0) == INTEGER_CST
		       && maybe_warn_shift_overflow (location, op0, op1)
		       && flag_isoc99)
		int_const = نادرست;
	    }

	  /* Use the type of the value to be shifted.  */
	  result_type = type0;
	  /* Avoid converting op1 to result_type later.  */
	  converted = 1;
	}
      بشکن;

    حالت EQ_عبارت:
    حالت NE_عبارت:
      اگر (gnu_vector_type_p (type0) && gnu_vector_type_p (type1))
        {
          درخت intt;
	  اگر (!vector_types_compatible_elements_p (type0, type1))
            {
              error_at (location, "comparing vectors with different "
                                  "element types");
              بازگشت error_mark_گره;
            }

	  اگر (maybe_ne (TYPE_VECTOR_SUBPARTS (type0),
			TYPE_VECTOR_SUBPARTS (type1)))
            {
              error_at (location, "comparing vectors with different "
                                  "number of elements");
              بازگشت error_mark_گره;
            }

	  /* It's not precisely specified how the usual arithmetic
	     conversions apply to the vector types.  Here, we use
	     the unsigned type if one of the operands is signed and
	     the other one is unsigned.  */
	  اگر (TYPE_UNSIGNED (type0) != TYPE_UNSIGNED (type1))
	    {
	      اگر (!TYPE_UNSIGNED (type0))
		op0 = build1 (VIEW_CONVERT_عبارت, type1, op0);
	      وگرنه
		op1 = build1 (VIEW_CONVERT_عبارت, type0, op1);
	      warning_at (location, OPT_Wsign_compare, "comparison between "
			  "types %qT and %qT", type0, type1);
	    }

          /* Always construct signed integer vector type.  */
	  اگر (VECTOR_BOOLEAN_TYPE_P (type0) && VECTOR_BOOLEAN_TYPE_P (type1))
	    result_type = type0;
	  وگرنه
	    {
	      auto nelts = TYPE_VECTOR_SUBPARTS (type0);

	      intt = c_common_type_for_size (GET_MODE_BITSIZE
					     (SCALAR_TYPE_MODE
						(درخت_TYPE (type0))), 0);
	      اگر (!intt)
		{
		  error_at (location, "could not find an integer type "
				      "of the same size as %qT",
			    درخت_TYPE (type0));
		  بازگشت error_mark_گره;
		}
	      result_type = build_opaque_vector_type (intt, nelts);
	    }
          converted = 1;
	  ret = build_vec_cmp (resultcode, result_type, op0, op1);
	  برو return_build_دودویی_op;
        }
      اگر (FLOAT_TYPE_P (type0) || FLOAT_TYPE_P (type1))
	warning_at (location,
		    OPT_Wfloat_equal,
		    "comparing floating-point with %<==%> or %<!=%> is unsafe");
      /* Result of comparison is always int,
	 but don't convert the args to int!  */
      build_type = integer_type_گره;
      اگر ((code0 == INTEGER_TYPE || code0 == REAL_TYPE || code0 == BITINT_TYPE
	   || code0 == FIXED_POINT_TYPE || code0 == COMPLEX_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	      || code1 == BITINT_TYPE
	      || code1 == FIXED_POINT_TYPE || code1 == COMPLEX_TYPE))
	short_compare = 1;
      وگرنه اگر (code0 == POINTER_TYPE
	       && (code1 == NULLPTR_TYPE
		   || null_pointer_constant_p (orig_op1)))
	{
	  maybe_warn_for_null_address (location, op0, code);
	  result_type = type0;
	}
      وگرنه اگر (code1 == POINTER_TYPE
	       && (code0 == NULLPTR_TYPE
		   || null_pointer_constant_p (orig_op0)))
	{
	  maybe_warn_for_null_address (location, op1, code);
	  result_type = type1;
	}
      وگرنه اگر (code0 == POINTER_TYPE && code1 == POINTER_TYPE)
	{
	  درخت tt0 = درخت_TYPE (type0);
	  درخت tt1 = درخت_TYPE (type1);
	  addr_space_t as0 = TYPE_ADDR_SPACE (tt0);
	  addr_space_t as1 = TYPE_ADDR_SPACE (tt1);
	  addr_space_t as_common = ADDR_SPACE_GENERIC;

	  /* Anything compares with void *.  void * compares with anything.
	     Otherwise, the targets must be compatible
	     and both must be object or both incomplete.  */
	  اگر (comp_target_types (location, type0, type1))
	    result_type = common_pointer_type (type0, type1, NULL_درخت);
	  وگرنه اگر (!addr_space_superset (as0, as1, &as_common))
	    {
	      error_at (location, "comparison of pointers to "
			"disjoint address spaces");
	      بازگشت error_mark_گره;
	    }
	  وگرنه اگر (VOID_TYPE_P (tt0) && !TYPE_ATOMIC (tt0))
	    {
	      اگر (pedantic && درخت_CODE (tt1) == FUNCTION_TYPE)
		pedwarn (location, OPT_Wpedantic, "ISO C forbids "
			 "comparison of %<void *%> with function pointer");
	    }
	  وگرنه اگر (VOID_TYPE_P (tt1) && !TYPE_ATOMIC (tt1))
	    {
	      اگر (pedantic && درخت_CODE (tt0) == FUNCTION_TYPE)
		pedwarn (location, OPT_Wpedantic, "ISO C forbids "
			 "comparison of %<void *%> with function pointer");
	    }
	  وگرنه
	    /* Avoid warning about the volatile ObjC EH puts on decls.  */
	    اگر (!objc_ok)
	      pedwarn (location, OPT_Wcompare_distinct_pointer_types,
		       "comparison of distinct pointer types lacks a cast");

	  اگر (result_type == NULL_درخت)
	    {
	      صحیح qual = ENCODE_QUAL_ADDR_SPACE (as_common);
	      result_type = c_build_pointer_type
			      (c_build_qualified_type (void_type_گره, qual));
	    }
	}
      وگرنه اگر (code0 == POINTER_TYPE
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  result_type = type0;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}
      وگرنه اگر ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	       && code1 == POINTER_TYPE)
	{
	  result_type = type1;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}
      /* 6.5.9: One of the following shall hold:
	 -- both operands have type nullptr_t;  */
      وگرنه اگر (code0 == NULLPTR_TYPE && code1 == NULLPTR_TYPE)
	{
	  result_type = nullptr_type_گره;
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
      وگرنه اگر (code0 == NULLPTR_TYPE && null_pointer_constant_p (orig_op1))
	result_type = (INTEGRAL_TYPE_P (type1)
		       ? c_build_pointer_type (type1) : type1);
      وگرنه اگر (code1 == NULLPTR_TYPE && null_pointer_constant_p (orig_op0))
	result_type = (INTEGRAL_TYPE_P (type0)
		       ? c_build_pointer_type (type0) : type0);
      اگر ((C_BOOLEAN_TYPE_P (درخت_TYPE (orig_op0))
	   || truth_مقدار_p (درخت_CODE (orig_op0)))
	  ^ (C_BOOLEAN_TYPE_P (درخت_TYPE (orig_op1))
	     || truth_مقدار_p (درخت_CODE (orig_op1))))
	maybe_warn_bool_compare (location, code, orig_op0, orig_op1);
      بشکن;

    حالت LE_عبارت:
    حالت GE_عبارت:
    حالت LT_عبارت:
    حالت GT_عبارت:
      اگر (gnu_vector_type_p (type0) && gnu_vector_type_p (type1))
        {
          درخت intt;
	  اگر (!vector_types_compatible_elements_p (type0, type1))
            {
              error_at (location, "comparing vectors with different "
                                  "element types");
              بازگشت error_mark_گره;
            }

	  اگر (maybe_ne (TYPE_VECTOR_SUBPARTS (type0),
			TYPE_VECTOR_SUBPARTS (type1)))
            {
              error_at (location, "comparing vectors with different "
                                  "number of elements");
              بازگشت error_mark_گره;
            }

	  /* It's not precisely specified how the usual arithmetic
	     conversions apply to the vector types.  Here, we use
	     the unsigned type if one of the operands is signed and
	     the other one is unsigned.  */
	  اگر (TYPE_UNSIGNED (type0) != TYPE_UNSIGNED (type1))
	    {
	      اگر (!TYPE_UNSIGNED (type0))
		op0 = build1 (VIEW_CONVERT_عبارت, type1, op0);
	      وگرنه
		op1 = build1 (VIEW_CONVERT_عبارت, type0, op1);
	      warning_at (location, OPT_Wsign_compare, "comparison between "
			  "types %qT and %qT", type0, type1);
	    }

          /* Always construct signed integer vector type.  */
          intt = c_common_type_for_size (GET_MODE_BITSIZE
					 (SCALAR_TYPE_MODE
					  (درخت_TYPE (type0))), 0);
	  اگر (!intt)
	    {
	      error_at (location, "could not find an integer type "
				  "of the same size as %qT",
			درخت_TYPE (type0));
	      بازگشت error_mark_گره;
	    }
          result_type = build_opaque_vector_type (intt,
						  TYPE_VECTOR_SUBPARTS (type0));
          converted = 1;
	  ret = build_vec_cmp (resultcode, result_type, op0, op1);
	  برو return_build_دودویی_op;
        }
      build_type = integer_type_گره;
      اگر ((code0 == INTEGER_TYPE || code0 == REAL_TYPE
	   || code0 == BITINT_TYPE || code0 == FIXED_POINT_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	      || code1 == BITINT_TYPE || code1 == FIXED_POINT_TYPE))
	short_compare = 1;
      وگرنه اگر (code0 == POINTER_TYPE && code1 == POINTER_TYPE)
	{
	  addr_space_t as0 = TYPE_ADDR_SPACE (درخت_TYPE (type0));
	  addr_space_t as1 = TYPE_ADDR_SPACE (درخت_TYPE (type1));
	  addr_space_t as_common;

	  اگر (comp_target_types (location, type0, type1))
	    {
	      result_type = common_pointer_type (type0, type1, NULL_درخت);
	      اگر (!COMPLETE_TYPE_P (درخت_TYPE (type0))
		  != !COMPLETE_TYPE_P (درخت_TYPE (type1)))
		pedwarn_c99 (location, OPT_Wpedantic,
			     "comparison of complete and incomplete pointers");
	      وگرنه اگر (درخت_CODE (درخت_TYPE (type0)) == FUNCTION_TYPE)
		pedwarn (location, OPT_Wpedantic, "ISO C forbids "
			 "ordered comparisons of pointers to functions");
	      وگرنه اگر (null_pointer_constant_p (orig_op0)
		       || null_pointer_constant_p (orig_op1))
		warning_at (location, OPT_Wextra,
			    "ordered comparison of pointer with null pointer");

	    }
	  وگرنه اگر (!addr_space_superset (as0, as1, &as_common))
	    {
	      error_at (location, "comparison of pointers to "
			"disjoint address spaces");
	      بازگشت error_mark_گره;
	    }
	  وگرنه
	    {
	      صحیح qual = ENCODE_QUAL_ADDR_SPACE (as_common);
	      result_type = c_build_pointer_type
			      (c_build_qualified_type (void_type_گره, qual));
              pedwarn (location, OPT_Wcompare_distinct_pointer_types,
                       "comparison of distinct pointer types lacks a cast");
	    }
	}
      وگرنه اگر (code0 == POINTER_TYPE && null_pointer_constant_p (orig_op1))
	{
	  result_type = type0;
	  اگر (pedantic)
	    pedwarn (location, OPT_Wpedantic,
		     "ordered comparison of pointer with integer zero");
	  وگرنه اگر (extra_warnings)
	    warning_at (location, OPT_Wextra,
			"ordered comparison of pointer with integer zero");
	}
      وگرنه اگر (code1 == POINTER_TYPE && null_pointer_constant_p (orig_op0))
	{
	  result_type = type1;
	  اگر (pedantic)
	    pedwarn (location, OPT_Wpedantic,
		     "ordered comparison of pointer with integer zero");
	  وگرنه اگر (extra_warnings)
	    warning_at (location, OPT_Wextra,
			"ordered comparison of pointer with integer zero");
	}
      وگرنه اگر (code0 == POINTER_TYPE
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  result_type = type0;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}
      وگرنه اگر ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	       && code1 == POINTER_TYPE)
	{
	  result_type = type1;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}

      اگر ((code0 == POINTER_TYPE || code1 == POINTER_TYPE)
	  && current_function_decl != NULL_درخت
	  && sanitize_flags_p (SANITIZE_POINTER_COMPARE))
	{
	  op0 = save_عبارت (c_fully_fold (op0, نادرست, پوچ));
	  op1 = save_عبارت (c_fully_fold (op1, نادرست, پوچ));

	  درخت tt = builtin_decl_explicit (BUILT_IN_ASAN_POINTER_COMPARE);
	  instrument_عبارت = build_call_عبارت_loc (location, tt, 2, op0, op1);
	}

      اگر ((C_BOOLEAN_TYPE_P (درخت_TYPE (orig_op0))
	   || truth_مقدار_p (درخت_CODE (orig_op0)))
	  ^ (C_BOOLEAN_TYPE_P (درخت_TYPE (orig_op1))
	     || truth_مقدار_p (درخت_CODE (orig_op1))))
	maybe_warn_bool_compare (location, code, orig_op0, orig_op1);
      بشکن;

    حالت MIN_عبارت:
    حالت MAX_عبارت:
      /* Used for OpenMP atomics.  */
      gcc_assert (flag_openmp);
      common = 1;
      بشکن;

    پیشفرض:
      gcc_unreachable ();
    }

  اگر (code0 == ERROR_MARK || code1 == ERROR_MARK)
    بازگشت error_mark_گره;

  اگر (gnu_vector_type_p (type0)
      && gnu_vector_type_p (type1)
      && (!درخت_int_cst_equal (TYPE_SIZE (type0), TYPE_SIZE (type1))
	  || !vector_types_compatible_elements_p (type0, type1)))
    {
      gcc_rich_location richloc (location);
      maybe_range_label_for_درخت_type_mismatch
	label_for_op0 (orig_op0, orig_op1),
	label_for_op1 (orig_op1, orig_op0);
      richloc.maybe_add_عبارت (orig_op0, &label_for_op0, highlight_colors::lhs);
      richloc.maybe_add_عبارت (orig_op1, &label_for_op1, highlight_colors::rhs);
      دودویی_op_error (&richloc, code, type0, type1);
      بازگشت error_mark_گره;
    }

  اگر ((code0 == INTEGER_TYPE || code0 == REAL_TYPE || code0 == COMPLEX_TYPE
       || code0 == FIXED_POINT_TYPE || code0 == BITINT_TYPE
       || gnu_vector_type_p (type0))
      && (code1 == INTEGER_TYPE || code1 == REAL_TYPE || code1 == COMPLEX_TYPE
	  || code1 == FIXED_POINT_TYPE || code1 == BITINT_TYPE
	  || gnu_vector_type_p (type1)))
    {
      منطقی first_complex = (code0 == COMPLEX_TYPE);
      منطقی second_complex = (code1 == COMPLEX_TYPE);
      صحیح none_complex = (!first_complex && !second_complex);

      اگر (shorten || common || short_compare)
	{
	  result_type = c_common_type (type0, type1);
	  do_warn_double_promotion (result_type, type0, type1,
				    "implicit conversion from %qT to %qT "
				    "to match other operand of binary "
				    "expression",
				    location);
	  اگر (result_type == error_mark_گره)
	    بازگشت error_mark_گره;
	}

      اگر (first_complex != second_complex
	  && (code == PLUS_عبارت
	      || code == MINUS_عبارت
	      || code == MULT_عبارت
	      || (code == TRUNC_DIV_عبارت && first_complex))
	  && درخت_CODE (درخت_TYPE (result_type)) == REAL_TYPE
	  && flag_signed_zeros)
	{
	  /* An operation on mixed real/complex operands must be
	     handled specially, but the language-independent code can
	     more easily optimize the plain complex arithmetic if
	     -fno-signed-zeros.  */
	  درخت real_type = درخت_TYPE (result_type);
	  درخت real, imag;
	  اگر (type0 != orig_type0 || type1 != orig_type1)
	    {
	      gcc_assert (may_need_excess_precision && common);
	      semantic_result_type = c_common_type (orig_type0, orig_type1);
	    }
	  اگر (first_complex)
	    {
	      اگر (درخت_TYPE (op0) != result_type)
		op0 = convert_and_check (location, result_type, op0);
	      اگر (درخت_TYPE (op1) != real_type)
		op1 = convert_and_check (location, real_type, op1);
	    }
	  وگرنه
	    {
	      اگر (درخت_TYPE (op0) != real_type)
		op0 = convert_and_check (location, real_type, op0);
	      اگر (درخت_TYPE (op1) != result_type)
		op1 = convert_and_check (location, result_type, op1);
	    }
	  اگر (درخت_CODE (op0) == ERROR_MARK || درخت_CODE (op1) == ERROR_MARK)
	    بازگشت error_mark_گره;
	  اگر (first_complex)
	    {
	      op0 = save_عبارت (op0);
	      real = build_unary_op (عبارت_LOCATION (orig_op0), REALPART_عبارت,
				     op0, درست);
	      imag = build_unary_op (عبارت_LOCATION (orig_op0), IMAGPART_عبارت,
				     op0, درست);
	      انتخاب (code)
		{
		حالت MULT_عبارت:
		حالت TRUNC_DIV_عبارت:
		  op1 = save_عبارت (op1);
		  imag = build2 (resultcode, real_type, imag, op1);
		  /* Fall through.  */
		حالت PLUS_عبارت:
		حالت MINUS_عبارت:
		  real = build2 (resultcode, real_type, real, op1);
		  بشکن;
		پیشفرض:
		  gcc_unreachable();
		}
	    }
	  وگرنه
	    {
	      op1 = save_عبارت (op1);
	      real = build_unary_op (عبارت_LOCATION (orig_op1), REALPART_عبارت,
				     op1, درست);
	      imag = build_unary_op (عبارت_LOCATION (orig_op1), IMAGPART_عبارت,
				     op1, درست);
	      انتخاب (code)
		{
		حالت MULT_عبارت:
		  op0 = save_عبارت (op0);
		  imag = build2 (resultcode, real_type, op0, imag);
		  /* Fall through.  */
		حالت PLUS_عبارت:
		  real = build2 (resultcode, real_type, op0, real);
		  بشکن;
		حالت MINUS_عبارت:
		  real = build2 (resultcode, real_type, op0, real);
		  imag = build1 (NEGATE_عبارت, real_type, imag);
		  بشکن;
		پیشفرض:
		  gcc_unreachable();
		}
	    }
	  ret = build2 (COMPLEX_عبارت, result_type, real, imag);
	  برو return_build_دودویی_op;
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
	  final_type = result_type;
	  result_type = shorten_دودویی_op (result_type, op0, op1,
					   shorten == -1);
	}

      /* Shifts can be shortened if shifting right.  */

      اگر (short_shift)
	{
	  صحیح unsigned_arg;
	  درخت arg0 = get_narrower (op0, &unsigned_arg);

	  final_type = result_type;

	  اگر (arg0 == op0 && final_type == درخت_TYPE (op0))
	    unsigned_arg = TYPE_UNSIGNED (درخت_TYPE (op0));

	  اگر (TYPE_PRECISION (درخت_TYPE (arg0)) < TYPE_PRECISION (result_type)
	      && درخت_int_cst_sgn (op1) > 0
	      /* We can shorten only if the shift count is less than the
		 number of bits in the smaller type size.  */
	      && compare_درخت_int (op1, TYPE_PRECISION (درخت_TYPE (arg0))) < 0
	      /* We cannot drop an unsigned shift after sign-extension.  */
	      && (!TYPE_UNSIGNED (final_type) || unsigned_arg))
	    {
	      /* Do an unsigned shift if the operand was zero-extended.  */
	      result_type
		= c_common_signed_or_unsigned_type (unsigned_arg,
						    درخت_TYPE (arg0));
	      /* Convert value-to-be-shifted to that type.  */
	      اگر (درخت_TYPE (op0) != result_type)
		op0 = convert (result_type, op0);
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
	  درخت xop0 = op0, xop1 = op1, xresult_type = result_type;
	  شمارش درخت_code xresultcode = resultcode;
	  درخت val
	    = shorten_compare (location, &xop0, &xop1, &xresult_type,
			       &xresultcode);

	  اگر (val != NULL_درخت)
	    {
	      ret = val;
	      برو return_build_دودویی_op;
	    }

	  op0 = xop0, op1 = xop1;
	  converted = 1;
	  resultcode = xresultcode;

	  اگر (c_inhibit_evaluation_warnings == 0 && !c_in_omp_for)
	    {
	      منطقی op0_maybe_const = درست;
	      منطقی op1_maybe_const = درست;
	      درخت orig_op0_folded, orig_op1_folded;

	      اگر (in_late_دودویی_op)
		{
		  orig_op0_folded = orig_op0;
		  orig_op1_folded = orig_op1;
		}
	      وگرنه
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
						  پوچ);
		  orig_op1_folded = c_fully_fold (orig_op1,
						  require_constant_مقدار,
						  پوچ);
		}

	      اگر (warn_sign_compare)
		warn_for_sign_compare (location, orig_op0_folded,
				       orig_op1_folded, op0, op1,
				       result_type, resultcode);
	      اگر (!in_late_دودویی_op && !int_operands)
		{
		  اگر (!op0_maybe_const || درخت_CODE (op0) != INTEGER_CST)
		    op0 = c_wrap_maybe_const (op0, !op0_maybe_const);
		  اگر (!op1_maybe_const || درخت_CODE (op1) != INTEGER_CST)
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

  اگر (!result_type)
    {
      /* Favor showing any expression locations that are available. */
      op_location_t oploc (location, UNKNOWN_LOCATION);
      دودویی_op_rich_location richloc (oploc, orig_op0, orig_op1, درست);
      دودویی_op_error (&richloc, code, درخت_TYPE (op0), درخت_TYPE (op1));
      بازگشت error_mark_گره;
    }

  اگر (build_type == NULL_درخت)
    {
      build_type = result_type;
      اگر ((type0 != orig_type0 || type1 != orig_type1)
	  && !boolean_op)
	{
	  gcc_assert (may_need_excess_precision && common);
	  semantic_result_type = c_common_type (orig_type0, orig_type1);
	}
    }

  اگر (!converted)
    {
      op0 = ep_convert_and_check (location, result_type, op0,
				  semantic_result_type);
      op1 = ep_convert_and_check (location, result_type, op1,
				  semantic_result_type);

      /* This can happen if one operand has a vector type, and the other
	 has a different type.  */
      اگر (درخت_CODE (op0) == ERROR_MARK || درخت_CODE (op1) == ERROR_MARK)
	بازگشت error_mark_گره;
    }

  اگر (sanitize_flags_p ((SANITIZE_SHIFT
			 | SANITIZE_DIVIDE
			 | SANITIZE_FLOAT_DIVIDE
			 | SANITIZE_SI_OVERFLOW))
      && current_function_decl != NULL_درخت
      && (doing_div_or_mod || doing_shift)
      && !require_constant_مقدار)
    {
      /* OP0 and/or OP1 might have side-effects.  */
      op0 = save_عبارت (op0);
      op1 = save_عبارت (op1);
      op0 = c_fully_fold (op0, نادرست, پوچ);
      op1 = c_fully_fold (op1, نادرست, پوچ);
      اگر (doing_div_or_mod && (sanitize_flags_p ((SANITIZE_DIVIDE
						  | SANITIZE_FLOAT_DIVIDE
						  | SANITIZE_SI_OVERFLOW))))
	instrument_عبارت = ubsan_instrument_division (location, op0, op1);
      وگرنه اگر (doing_shift && sanitize_flags_p (SANITIZE_SHIFT))
	instrument_عبارت = ubsan_instrument_shift (location, code, op0, op1);
    }

  /* Treat expressions in initializers specially as they can't trap.  */
  اگر (int_const_or_overflow)
    ret = (require_constant_مقدار
	   ? fold_build2_initializer_loc (location, resultcode, build_type,
					  op0, op1)
	   : fold_build2_loc (location, resultcode, build_type, op0, op1));
  وگرنه
    ret = build2 (resultcode, build_type, op0, op1);
  اگر (final_type != NULL_درخت)
    ret = convert (final_type, ret);

 return_build_دودویی_op:
  gcc_assert (ret != error_mark_گره);
  اگر (درخت_CODE (ret) == INTEGER_CST && !درخت_OVERFLOW (ret) && !int_const)
    ret = (int_operands
	   ? note_integer_operands (ret)
	   : build1 (NOP_عبارت, درخت_TYPE (ret), ret));
  وگرنه اگر (درخت_CODE (ret) != INTEGER_CST && int_operands
	   && !in_late_دودویی_op)
    ret = note_integer_operands (ret);
  protected_set_عبارت_location (ret, location);

  اگر (instrument_عبارت != پوچ)
    ret = fold_build2 (COMPOUND_عبارت, درخت_TYPE (ret),
		       instrument_عبارت, ret);

  اگر (semantic_result_type)
    ret = build1_loc (location, EXCESS_PRECISION_عبارت,
		      semantic_result_type, ret);

  بازگشت ret;
}


/* Convert EXPR to be a truth-value (type TYPE), validating its type for this
   purpose.  LOCATION is the source location for the expression.  */

درخت
c_objc_common_truthvalue_conversion (location_t location, درخت عبارت, درخت type)
{
  منطقی int_const, int_operands;

  انتخاب (درخت_CODE (درخت_TYPE (عبارت)))
    {
    حالت ARRAY_TYPE:
      error_at (location, "used array that cannot be converted to pointer where scalar is required");
      بازگشت error_mark_گره;

    حالت RECORD_TYPE:
      error_at (location, "used struct type value where scalar is required");
      بازگشت error_mark_گره;

    حالت UNION_TYPE:
      error_at (location, "used union type value where scalar is required");
      بازگشت error_mark_گره;

    حالت VOID_TYPE:
      error_at (location, "void value not ignored as it ought to be");
      بازگشت error_mark_گره;

    حالت POINTER_TYPE:
      اگر (reject_gcc_builtin (عبارت))
	بازگشت error_mark_گره;
      بشکن;

    حالت FUNCTION_TYPE:
      gcc_unreachable ();

    حالت VECTOR_TYPE:
      error_at (location, "used vector type where scalar is required");
      بازگشت error_mark_گره;

    پیشفرض:
      بشکن;
    }

  /* Conversion of a floating constant to boolean goes through here
     and yields an integer constant expression.  Otherwise, the result
     is only an integer constant expression if the argument is.  */
  int_const = ((درخت_CODE (عبارت) == INTEGER_CST && !درخت_OVERFLOW (عبارت))
	       || ((درخت_CODE (عبارت) == REAL_CST
		    || درخت_CODE (عبارت) == COMPLEX_CST)
		   && (درخت_CODE (type) == BOOLEAN_TYPE
		       || (درخت_CODE (type) == ENUMERAL_TYPE
			   && ENUM_UNDERLYING_TYPE (type) != NULL_درخت
			   && (درخت_CODE (ENUM_UNDERLYING_TYPE (type))
			       == BOOLEAN_TYPE)))));
  int_operands = عبارت_INT_CONST_OPERANDS (عبارت);
  اگر (int_operands && درخت_CODE (عبارت) != INTEGER_CST)
    {
      عبارت = remove_c_maybe_const_عبارت (عبارت);
      عبارت = build2 (NE_عبارت, type, عبارت,
		     convert (درخت_TYPE (عبارت), integer_zero_گره));
      عبارت = note_integer_operands (عبارت);
    }
  وگرنه
    {
      /* ??? Should we also give an error for vectors rather than leaving
	 those to give errors later?  */
      عبارت = c_common_truthvalue_conversion (location, عبارت);
      عبارت = fold_convert_loc (location, type, عبارت);
    }

  اگر (درخت_CODE (عبارت) == INTEGER_CST && int_operands && !int_const)
    {
      اگر (درخت_OVERFLOW (عبارت))
	بازگشت عبارت;
      وگرنه
	بازگشت note_integer_operands (عبارت);
    }
  اگر (درخت_CODE (عبارت) == INTEGER_CST && !int_const)
    بازگشت build1 (NOP_عبارت, درخت_TYPE (عبارت), عبارت);
  بازگشت عبارت;
}


/* Convert EXPR to a contained DECL, updating *TC, *TI and *SE as
   required.  */

درخت
c_عبارت_to_decl (درخت عبارت, منطقی *tc ATTRIBUTE_UNUSED, منطقی *se)
{
  اگر (درخت_CODE (عبارت) == COMPOUND_LITERAL_عبارت)
    {
      درخت decl = COMPOUND_LITERAL_عبارت_DECL (عبارت);
      /* Executing a compound literal inside a function reinitializes
	 it.  */
      اگر (!درخت_STATIC (decl))
	*se = درست;
      بازگشت decl;
    }
  وگرنه
    بازگشت عبارت;
}

/* Generate OMP construct CODE, with BODY and CLAUSES as its compound
   statement.  LOC is the location of the construct.  */

درخت
c_finish_omp_construct (location_t loc, شمارش درخت_code code, درخت body,
			درخت clauses)
{
  body = c_end_compound_stmt (loc, body, درست);

  درخت stmt = make_گره (code);
  درخت_TYPE (stmt) = void_type_گره;
  OMP_BODY (stmt) = body;
  OMP_CLAUSES (stmt) = clauses;
  SET_عبارت_LOCATION (stmt, loc);

  بازگشت add_stmt (stmt);
}

/* Generate OACC_DATA, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the OACC_DATA.  */

درخت
c_finish_oacc_data (location_t loc, درخت clauses, درخت block)
{
  درخت stmt;

  block = c_end_compound_stmt (loc, block, درست);

  stmt = make_گره (OACC_DATA);
  درخت_TYPE (stmt) = void_type_گره;
  OACC_DATA_CLAUSES (stmt) = clauses;
  OACC_DATA_BODY (stmt) = block;
  SET_عبارت_LOCATION (stmt, loc);

  بازگشت add_stmt (stmt);
}

/* Generate OACC_HOST_DATA, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the OACC_HOST_DATA.  */

درخت
c_finish_oacc_host_data (location_t loc, درخت clauses, درخت block)
{
  درخت stmt;

  block = c_end_compound_stmt (loc, block, درست);

  stmt = make_گره (OACC_HOST_DATA);
  درخت_TYPE (stmt) = void_type_گره;
  OACC_HOST_DATA_CLAUSES (stmt) = clauses;
  OACC_HOST_DATA_BODY (stmt) = block;
  SET_عبارت_LOCATION (stmt, loc);

  بازگشت add_stmt (stmt);
}

/* Like c_begin_compound_stmt, except force the retention of the BLOCK.  */

درخت
c_begin_omp_parallel (تهی)
{
  درخت block;

  keep_next_level ();
  block = c_begin_compound_stmt (درست);

  بازگشت block;
}

/* Generate OMP_PARALLEL, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the OMP_PARALLEL.  */

درخت
c_finish_omp_parallel (location_t loc, درخت clauses, درخت block)
{
  درخت stmt;

  block = c_end_compound_stmt (loc, block, درست);

  stmt = make_گره (OMP_PARALLEL);
  درخت_TYPE (stmt) = void_type_گره;
  OMP_PARALLEL_CLAUSES (stmt) = clauses;
  OMP_PARALLEL_BODY (stmt) = block;
  SET_عبارت_LOCATION (stmt, loc);

  بازگشت add_stmt (stmt);
}

/* Like c_begin_compound_stmt, except force the retention of the BLOCK.  */

درخت
c_begin_omp_task (تهی)
{
  درخت block;

  keep_next_level ();
  block = c_begin_compound_stmt (درست);

  بازگشت block;
}

/* Generate OMP_TASK, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the #pragma.  */

درخت
c_finish_omp_task (location_t loc, درخت clauses, درخت block)
{
  درخت stmt;

  block = c_end_compound_stmt (loc, block, درست);

  stmt = make_گره (OMP_TASK);
  درخت_TYPE (stmt) = void_type_گره;
  OMP_TASK_CLAUSES (stmt) = clauses;
  OMP_TASK_BODY (stmt) = block;
  SET_عبارت_LOCATION (stmt, loc);

  بازگشت add_stmt (stmt);
}

/* Generate GOMP_cancel call for #pragma omp cancel.  */

تهی
c_finish_omp_cancel (location_t loc, درخت clauses)
{
  درخت fn = builtin_decl_explicit (BUILT_IN_GOMP_CANCEL);
  صحیح mask = 0;
  اگر (omp_find_clause (clauses, OMP_CLAUSE_PARALLEL))
    mask = 1;
  وگرنه اگر (omp_find_clause (clauses, OMP_CLAUSE_FOR))
    mask = 2;
  وگرنه اگر (omp_find_clause (clauses, OMP_CLAUSE_SECTIONS))
    mask = 4;
  وگرنه اگر (omp_find_clause (clauses, OMP_CLAUSE_TASKGROUP))
    mask = 8;
  وگرنه
    {
      error_at (loc, "%<#pragma omp cancel%> must specify one of "
		     "%<parallel%>, %<for%>, %<sections%> or %<taskgroup%> "
		     "clauses");
      بازگشت;
    }
  درخت ifc = omp_find_clause (clauses, OMP_CLAUSE_IF);
  اگر (ifc != NULL_درخت)
    {
      اگر (OMP_CLAUSE_IF_MODIFIER (ifc) != ERROR_MARK
	  && OMP_CLAUSE_IF_MODIFIER (ifc) != VOID_CST)
	error_at (OMP_CLAUSE_LOCATION (ifc),
		  "expected %<cancel%> %<if%> clause modifier");
      وگرنه
	{
	  درخت ifc2 = omp_find_clause (OMP_CLAUSE_CHAIN (ifc), OMP_CLAUSE_IF);
	  اگر (ifc2 != NULL_درخت)
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
  وگرنه
    ifc = boolean_true_گره;
  درخت stmt = build_call_عبارت_loc (loc, fn, 2,
				   build_int_cst (integer_type_گره, mask),
				   ifc);
  add_stmt (stmt);
}

/* Generate GOMP_cancellation_point call for
   #pragma omp cancellation point.  */

تهی
c_finish_omp_cancellation_point (location_t loc, درخت clauses)
{
  درخت fn = builtin_decl_explicit (BUILT_IN_GOMP_CANCELLATION_POINT);
  صحیح mask = 0;
  اگر (omp_find_clause (clauses, OMP_CLAUSE_PARALLEL))
    mask = 1;
  وگرنه اگر (omp_find_clause (clauses, OMP_CLAUSE_FOR))
    mask = 2;
  وگرنه اگر (omp_find_clause (clauses, OMP_CLAUSE_SECTIONS))
    mask = 4;
  وگرنه اگر (omp_find_clause (clauses, OMP_CLAUSE_TASKGROUP))
    mask = 8;
  وگرنه
    {
      error_at (loc, "%<#pragma omp cancellation point%> must specify one of "
		     "%<parallel%>, %<for%>, %<sections%> or %<taskgroup%> "
		     "clauses");
      بازگشت;
    }
  درخت stmt = build_call_عبارت_loc (loc, fn, 1,
				   build_int_cst (integer_type_گره, mask));
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

ایستا درخت
handle_omp_array_sections_1 (درخت c, درخت t, vec<درخت> &types,
			     منطقی &maybe_zero_len, unsigned صحیح &first_non_one,
			     شمارش c_omp_region_type ort)
{
  درخت ret, کم_bound, length, type;
  منطقی openacc = (ort & C_ORT_ACC) != 0;
  اگر (درخت_CODE (t) != OMP_ARRAY_SECTION)
    {
      اگر (error_operand_p (t))
	بازگشت error_mark_گره;
      c_omp_address_inspector ai (OMP_CLAUSE_LOCATION (c), t);
      ret = t;
      اگر (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
	  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
	  && TYPE_ATOMIC (strip_array_types (درخت_TYPE (t))))
	{
	  error_at (OMP_CLAUSE_LOCATION (c), "%<_Atomic%> %qE in %qs clause",
		    t, omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  بازگشت error_mark_گره;
	}
      اگر (!ai.check_clause (c))
	بازگشت error_mark_گره;
      وگرنه اگر (ai.component_access_p ()
	       && (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TO
		   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_FROM))
	t = ai.get_ریشه_term (درست);
      وگرنه
	t = ai.unconverted_ref_origin ();
      اگر (t == error_mark_گره)
	بازگشت error_mark_گره;
      اگر (!VAR_P (t)
	  && (ort == C_ORT_ACC || !عبارت_P (t))
	  && درخت_CODE (t) != PARM_DECL)
	{
	  اگر (DECL_P (t))
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD is not a variable in %qs clause", t,
		      omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  وگرنه
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qE is not a variable in %qs clause", t,
		      omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  بازگشت error_mark_گره;
	}
      وگرنه اگر (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
	       && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
	       && TYPE_ATOMIC (درخت_TYPE (t)))
	{
	  error_at (OMP_CLAUSE_LOCATION (c), "%<_Atomic%> %qD in %qs clause",
		    t, omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  بازگشت error_mark_گره;
	}
      وگرنه اگر (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
	       && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
	       && VAR_P (t)
	       && DECL_THREAD_LOCAL_P (t))
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "%qD is threadprivate variable in %qs clause", t,
		    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  بازگشت error_mark_گره;
	}
      اگر ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY
	   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND)
	  && TYPE_ATOMIC (درخت_TYPE (t))
	  && POINTER_TYPE_P (درخت_TYPE (t)))
	{
	  /* If the array section is pointer based and the pointer
	     itself is _Atomic qualified, we need to atomically load
	     the pointer.  */
	  ret = convert_lvalue_to_rvalue (OMP_CLAUSE_LOCATION (c),
					  ret, نادرست, نادرست);
	}
      بازگشت ret;
    }

  ret = handle_omp_array_sections_1 (c, درخت_OPERAND (t, 0), types,
				     maybe_zero_len, first_non_one, ort);
  اگر (ret == error_mark_گره || ret == NULL_درخت)
    بازگشت ret;

  type = درخت_TYPE (ret);
  کم_bound = درخت_OPERAND (t, 1);
  length = درخت_OPERAND (t, 2);

  اگر (کم_bound == error_mark_گره || length == error_mark_گره)
    بازگشت error_mark_گره;

  اگر (کم_bound && !INTEGRAL_TYPE_P (درخت_TYPE (کم_bound)))
    {
      error_at (OMP_CLAUSE_LOCATION (c),
		"low bound %qE of array section does not have integral type",
		کم_bound);
      بازگشت error_mark_گره;
    }
  اگر (length && !INTEGRAL_TYPE_P (درخت_TYPE (length)))
    {
      error_at (OMP_CLAUSE_LOCATION (c),
		"length %qE of array section does not have integral type",
		length);
      بازگشت error_mark_گره;
    }
  اگر (کم_bound
      && درخت_CODE (کم_bound) == INTEGER_CST
      && TYPE_PRECISION (درخت_TYPE (کم_bound))
	 > TYPE_PRECISION (sizetype))
    کم_bound = fold_convert (sizetype, کم_bound);
  اگر (length
      && درخت_CODE (length) == INTEGER_CST
      && TYPE_PRECISION (درخت_TYPE (length))
	 > TYPE_PRECISION (sizetype))
    length = fold_convert (sizetype, length);
  اگر (کم_bound == NULL_درخت)
    کم_bound = integer_zero_گره;
  اگر (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
      && (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_ATTACH
	  || OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_DETACH))
    {
      اگر (length != integer_one_گره)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "expected single pointer in %qs clause",
		    user_omp_clause_code_name (c, openacc));
	  بازگشت error_mark_گره;
	}
    }
  اگر (length != NULL_درخت)
    {
      اگر (!integer_nonzerop (length))
	{
	  اگر (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY
	      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
	      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
	      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
	      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TASK_REDUCTION)
	    {
	      اگر (integer_zerop (length))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "zero length array section in %qs clause",
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  بازگشت error_mark_گره;
		}
	    }
	  وگرنه
	    maybe_zero_len = درست;
	}
      اگر (first_non_one == types.length ()
	  && (درخت_CODE (length) != INTEGER_CST || integer_onep (length)))
	first_non_one++;
    }
  اگر (درخت_CODE (type) == ARRAY_TYPE)
    {
      اگر (length == NULL_درخت
	  && (TYPE_DOMAIN (type) == NULL_درخت
	      || TYPE_MAX_مقدار (TYPE_DOMAIN (type)) == NULL_درخت))
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "for unknown bound array type length expression must "
		    "be specified");
	  بازگشت error_mark_گره;
	}
      اگر (درخت_CODE (کم_bound) == INTEGER_CST
	  && درخت_int_cst_sgn (کم_bound) == -1)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "negative low bound in array section in %qs clause",
		    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  بازگشت error_mark_گره;
	}
      اگر (length != NULL_درخت
	  && درخت_CODE (length) == INTEGER_CST
	  && درخت_int_cst_sgn (length) == -1)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "negative length in array section in %qs clause",
		    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  بازگشت error_mark_گره;
	}
      اگر (TYPE_DOMAIN (type)
	  && TYPE_MAX_مقدار (TYPE_DOMAIN (type))
	  && درخت_CODE (TYPE_MAX_مقدار (TYPE_DOMAIN (type)))
			== INTEGER_CST)
	{
	  درخت size
	    = fold_convert (sizetype, TYPE_MAX_مقدار (TYPE_DOMAIN (type)));
	  size = size_binop (PLUS_عبارت, size, size_one_گره);
	  اگر (درخت_CODE (کم_bound) == INTEGER_CST)
	    {
	      اگر (درخت_int_cst_lt (size, کم_bound))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "low bound %qE above array section size "
			    "in %qs clause", کم_bound,
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  بازگشت error_mark_گره;
		}
	      اگر (درخت_int_cst_equal (size, کم_bound))
		{
		  اگر (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TASK_REDUCTION)
		    {
		      error_at (OMP_CLAUSE_LOCATION (c),
				"zero length array section in %qs clause",
				omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		      بازگشت error_mark_گره;
		    }
		  maybe_zero_len = درست;
		}
	      وگرنه اگر (length == NULL_درخت
		       && first_non_one == types.length ()
		       && درخت_int_cst_equal
			    (TYPE_MAX_مقدار (TYPE_DOMAIN (type)),
			     کم_bound))
		first_non_one++;
	    }
	  وگرنه اگر (length == NULL_درخت)
	    {
	      اگر (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
		  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
		  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_REDUCTION
		  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_IN_REDUCTION
		  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_TASK_REDUCTION)
		maybe_zero_len = درست;
	      اگر (first_non_one == types.length ())
		first_non_one++;
	    }
	  اگر (length && درخت_CODE (length) == INTEGER_CST)
	    {
	      اگر (درخت_int_cst_lt (size, length))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "length %qE above array section size "
			    "in %qs clause", length,
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  بازگشت error_mark_گره;
		}
	      اگر (درخت_CODE (کم_bound) == INTEGER_CST)
		{
		  درخت lbpluslen
		    = size_binop (PLUS_عبارت,
				  fold_convert (sizetype, کم_bound),
				  fold_convert (sizetype, length));
		  اگر (درخت_CODE (lbpluslen) == INTEGER_CST
		      && درخت_int_cst_lt (size, lbpluslen))
		    {
		      error_at (OMP_CLAUSE_LOCATION (c),
				"high bound %qE above array section size "
				"in %qs clause", lbpluslen,
				omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		      بازگشت error_mark_گره;
		    }
		}
	    }
	}
      وگرنه اگر (length == NULL_درخت)
	{
	  اگر (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
	      && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
	      && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_REDUCTION
	      && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_IN_REDUCTION
	      && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_TASK_REDUCTION)
	    maybe_zero_len = درست;
	  اگر (first_non_one == types.length ())
	    first_non_one++;
	}

      /* For [lb:] we will need to evaluate lb more than once.  */
      اگر (length == NULL_درخت && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND)
	{
	  درخت lb = save_عبارت (کم_bound);
	  اگر (lb != کم_bound)
	    {
	      درخت_OPERAND (t, 1) = lb;
	      کم_bound = lb;
	    }
	}
    }
  وگرنه اگر (درخت_CODE (type) == POINTER_TYPE)
    {
      اگر (length == NULL_درخت)
	{
	  اگر (درخت_CODE (ret) == PARM_DECL && C_ARRAY_PARAMETER (ret))
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "for array function parameter length expression "
		      "must be specified");
	  وگرنه
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "for pointer type length expression must be specified");
	  بازگشت error_mark_گره;
	}
      اگر (length != NULL_درخت
	  && درخت_CODE (length) == INTEGER_CST
	  && درخت_int_cst_sgn (length) == -1)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "negative length in array section in %qs clause",
		    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  بازگشت error_mark_گره;
	}
      /* If there is a pointer type anywhere but in the very first
	 array-section-subscript, the array section could be non-contiguous.  */
      اگر (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
	  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
	  && درخت_CODE (درخت_OPERAND (t, 0)) == OMP_ARRAY_SECTION)
	{
	  /* If any prior dimension has a non-one length, then deem this
	     array section as non-contiguous.  */
	  برای (درخت d = درخت_OPERAND (t, 0);
	       درخت_CODE (d) == OMP_ARRAY_SECTION;
	       d = درخت_OPERAND (d, 0))
	    {
	      درخت d_length = درخت_OPERAND (d, 2);
	      اگر (d_length == NULL_درخت || !integer_onep (d_length))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "array section is not contiguous in %qs clause",
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  بازگشت error_mark_گره;
		}
	    }
	}
    }
  وگرنه
    {
      error_at (OMP_CLAUSE_LOCATION (c),
		"%qE does not have pointer or array type", ret);
      بازگشت error_mark_گره;
    }
  اگر (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND)
    types.safe_افزودن (درخت_TYPE (ret));
  /* We will need to evaluate lb more than once.  */
  درخت lb = save_عبارت (کم_bound);
  اگر (lb != کم_bound)
    {
      درخت_OPERAND (t, 1) = lb;
      کم_bound = lb;
    }
  ret = build_array_ref (OMP_CLAUSE_LOCATION (c), ret, کم_bound);
  بازگشت ret;
}

/* Handle array sections for clause C.  */

ایستا منطقی
handle_omp_array_sections (درخت &c, شمارش c_omp_region_type ort)
{
  منطقی maybe_zero_len = نادرست;
  unsigned صحیح first_non_one = 0;
  auto_vec<درخت, 10> types;
  درخت *tp = &OMP_CLAUSE_DECL (c);
  اگر ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
       || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY)
      && OMP_ITERATOR_DECL_P (*tp))
    tp = &درخت_مقدار (*tp);
  درخت first = handle_omp_array_sections_1 (c, *tp, types,
					    maybe_zero_len, first_non_one,
					    ort);
  اگر (first == error_mark_گره)
    بازگشت درست;
  اگر (first == NULL_درخت)
    بازگشت نادرست;
  اگر (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY)
    {
      درخت t = *tp;
      درخت tem = NULL_درخت;
      /* Need to evaluate side effects in the length expressions
	 if any.  */
      وقتی (درخت_CODE (t) == درخت_LIST)
	{
	  اگر (درخت_مقدار (t) && درخت_SIDE_EFFECTS (درخت_مقدار (t)))
	    {
	      اگر (tem == NULL_درخت)
		tem = درخت_مقدار (t);
	      وگرنه
		tem = build2 (COMPOUND_عبارت, درخت_TYPE (tem),
			      درخت_مقدار (t), tem);
	    }
	  t = درخت_CHAIN (t);
	}
      اگر (tem)
	first = build2 (COMPOUND_عبارت, درخت_TYPE (first), tem, first);
      first = c_fully_fold (first, نادرست, پوچ, درست);
      *tp = first;
    }
  وگرنه
    {
      unsigned صحیح رقم = types.length (), i;
      درخت t, side_effects = NULL_درخت, size = NULL_درخت;
      درخت condition = NULL_درخت;

      اگر (int_size_in_bytes (درخت_TYPE (first)) <= 0)
	maybe_zero_len = درست;

      برای (i = رقم, t = OMP_CLAUSE_DECL (c); i > 0;
	   t = درخت_OPERAND (t, 0))
	{
	  درخت کم_bound = درخت_OPERAND (t, 1);
	  درخت length = درخت_OPERAND (t, 2);

	  i--;
	  اگر (کم_bound
	      && درخت_CODE (کم_bound) == INTEGER_CST
	      && TYPE_PRECISION (درخت_TYPE (کم_bound))
		 > TYPE_PRECISION (sizetype))
	    کم_bound = fold_convert (sizetype, کم_bound);
	  اگر (length
	      && درخت_CODE (length) == INTEGER_CST
	      && TYPE_PRECISION (درخت_TYPE (length))
		 > TYPE_PRECISION (sizetype))
	    length = fold_convert (sizetype, length);
	  اگر (کم_bound == NULL_درخت)
	    کم_bound = integer_zero_گره;
	  اگر (!maybe_zero_len && i > first_non_one)
	    {
	      اگر (integer_nonzerop (کم_bound))
		برو do_warn_noncontiguous;
	      اگر (length != NULL_درخت
		  && درخت_CODE (length) == INTEGER_CST
		  && TYPE_DOMAIN (types[i])
		  && TYPE_MAX_مقدار (TYPE_DOMAIN (types[i]))
		  && درخت_CODE (TYPE_MAX_مقدار (TYPE_DOMAIN (types[i])))
		     == INTEGER_CST)
		{
		  درخت size;
		  size = size_binop (PLUS_عبارت,
				     TYPE_MAX_مقدار (TYPE_DOMAIN (types[i])),
				     size_one_گره);
		  اگر (!درخت_int_cst_equal (length, size))
		    {
		     do_warn_noncontiguous:
		      error_at (OMP_CLAUSE_LOCATION (c),
				"array section is not contiguous in %qs "
				"clause",
				omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		      بازگشت درست;
		    }
		}
	      اگر (length != NULL_درخت
		  && درخت_SIDE_EFFECTS (length))
		{
		  اگر (side_effects == NULL_درخت)
		    side_effects = length;
		  وگرنه
		    side_effects = build2 (COMPOUND_عبارت,
					   درخت_TYPE (side_effects),
					   length, side_effects);
		}
	    }
	  وگرنه
	    {
	      درخت l;

	      اگر (i > first_non_one
		  && ((length && integer_nonzerop (length))
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TASK_REDUCTION))
		ادامه;
	      اگر (length)
		l = fold_convert (sizetype, length);
	      وگرنه
		{
		  l = size_binop (PLUS_عبارت,
				  TYPE_MAX_مقدار (TYPE_DOMAIN (types[i])),
				  size_one_گره);
		  l = size_binop (MINUS_عبارت, l,
				  fold_convert (sizetype, کم_bound));
		}
	      اگر (i > first_non_one)
		{
		  l = fold_build2 (NE_عبارت, boolean_type_گره, l,
				   size_zero_گره);
		  اگر (condition == NULL_درخت)
		    condition = l;
		  وگرنه
		    condition = fold_build2 (BIT_AND_عبارت, boolean_type_گره,
					     l, condition);
		}
	      وگرنه اگر (size == NULL_درخت)
		{
		  size = size_in_bytes (درخت_TYPE (types[i]));
		  درخت eltype = درخت_TYPE (types[رقم - 1]);
		  وقتی (درخت_CODE (eltype) == ARRAY_TYPE)
		    eltype = درخت_TYPE (eltype);
		  اگر (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TASK_REDUCTION)
		    {
		      اگر (integer_zerop (size)
			  || integer_zerop (size_in_bytes (eltype)))
			{
			  error_at (OMP_CLAUSE_LOCATION (c),
				    "zero length array section in %qs clause",
				    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
			  بازگشت error_mark_گره;
			}
		      size = size_binop (EXACT_DIV_عبارت, size,
					 size_in_bytes (eltype));
		    }
		  size = size_binop (MULT_عبارت, size, l);
		  اگر (condition)
		    size = fold_build3 (COND_عبارت, sizetype, condition,
					size, size_zero_گره);
		}
	      وگرنه
		size = size_binop (MULT_عبارت, size, l);
	    }
	}
      اگر (side_effects)
	size = build2 (COMPOUND_عبارت, sizetype, side_effects, size);
      اگر (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
	  || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
	  || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TASK_REDUCTION)
	{
	  size = size_binop (MINUS_عبارت, size, size_one_گره);
	  size = c_fully_fold (size, نادرست, پوچ);
	  size = save_عبارت (size);
	  درخت index_type = build_index_type (size);
	  درخت eltype = درخت_TYPE (first);
	  وقتی (درخت_CODE (eltype) == ARRAY_TYPE)
	    eltype = درخت_TYPE (eltype);
	  درخت type = c_build_array_type (eltype, index_type);
	  درخت ptype = c_build_pointer_type (eltype);
	  اگر (درخت_CODE (درخت_TYPE (t)) == ARRAY_TYPE)
	    t = build_fold_addr_عبارت (t);
	  درخت t2 = build_fold_addr_عبارت (first);
	  t2 = fold_convert_loc (OMP_CLAUSE_LOCATION (c),
				 ptrdiff_type_گره, t2);
	  t2 = fold_build2_loc (OMP_CLAUSE_LOCATION (c), MINUS_عبارت,
				ptrdiff_type_گره, t2,
				fold_convert_loc (OMP_CLAUSE_LOCATION (c),
						  ptrdiff_type_گره, t));
	  t2 = c_fully_fold (t2, نادرست, پوچ);
	  اگر (درخت_fits_shwi_p (t2))
	    t = build2 (MEM_REF, type, t,
			build_int_cst (ptype, درخت_to_shwi (t2)));
	  وگرنه
	    {
	      t2 = fold_convert_loc (OMP_CLAUSE_LOCATION (c), sizetype, t2);
	      t = build2_loc (OMP_CLAUSE_LOCATION (c), POINTER_PLUS_عبارت,
			      درخت_TYPE (t), t, t2);
	      t = build2 (MEM_REF, type, t, build_int_cst (ptype, 0));
	    }
	  OMP_CLAUSE_DECL (c) = t;
	  بازگشت نادرست;
	}
      first = c_fully_fold (first, نادرست, پوچ);
      OMP_CLAUSE_DECL (c) = first;
      اگر (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_HAS_DEVICE_ADDR)
	بازگشت نادرست;
      /* Don't set OMP_CLAUSE_SIZE for bare attach/detach clauses.  */
      اگر (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP
	  || (OMP_CLAUSE_MAP_KIND (c) != GOMP_MAP_ATTACH
	      && OMP_CLAUSE_MAP_KIND (c) != GOMP_MAP_DETACH
	      && OMP_CLAUSE_MAP_KIND (c) != GOMP_MAP_FORCE_DETACH))
	{
	  اگر (size)
	    size = c_fully_fold (size, نادرست, پوچ);
	  OMP_CLAUSE_SIZE (c) = size;
	}

      اگر (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP)
	بازگشت نادرست;

      auto_vec<omp_addr_token *, 10> addr_tokens;

      اگر (!omp_parse_عبارت (addr_tokens, first))
	بازگشت درست;

      c_omp_address_inspector ai (OMP_CLAUSE_LOCATION (c), t);

      درخت nc = ai.expand_map_clause (c, first, addr_tokens, ort);
      اگر (nc != error_mark_گره)
	{
	  using فضاینام omp_addr_tokenizer;

	  اگر (ai.maybe_zero_length_array_section (c))
	    OMP_CLAUSE_MAP_MAYBE_ZERO_LENGTH_ARRAY_SECTION (c) = 1;

	  /* !!! If we're accessing a base decl via chained access
	     methods (e.g. multiple indirections), duplicate clause
	     detection won't work properly.  Skip it in that case.  */
	  اگر ((addr_tokens[0]->type == STRUCTURE_BASE
	       || addr_tokens[0]->type == ARRAY_BASE)
	      && addr_tokens[0]->u.structure_base_kind == BASE_DECL
	      && addr_tokens[1]->type == ACCESS_METHOD
	      && omp_access_chain_p (addr_tokens, 1))
	    c = nc;

	  بازگشت نادرست;
	}
    }
  بازگشت نادرست;
}

/* Helper function of finish_omp_clauses.  Clone STMT as if we were making
   an inline call.  But, remap
   the OMP_DECL1 VAR_DECL (omp_out resp. omp_orig) to PLACEHOLDER
   and OMP_DECL2 VAR_DECL (omp_in resp. omp_priv) to DECL.  */

ایستا درخت
c_clone_omp_udr (درخت stmt, درخت omp_decl1, درخت omp_decl2,
		 درخت decl, درخت placeholder)
{
  copy_body_data id;
  hash_map<درخت, درخت> decl_map;

  decl_map.put (omp_decl1, placeholder);
  decl_map.put (omp_decl2, decl);
  memset (&id, 0, اندازه (id));
  id.src_fn = DECL_CONTEXT (omp_decl1);
  id.dst_fn = current_function_decl;
  id.src_cfun = DECL_STRUCT_FUNCTION (id.src_fn);
  id.decl_map = &decl_map;

  id.copy_decl = copy_decl_no_change;
  id.transform_call_graph_edges = CB_CGE_DUPLICATE;
  id.transform_new_cfg = درست;
  id.transform_return_to_modify = نادرست;
  id.eh_lp_nr = 0;
  walk_درخت (&stmt, copy_درخت_body_r, &id, پوچ);
  بازگشت stmt;
}

/* Helper function of c_finish_omp_clauses, called via walk_tree.
   Find OMP_CLAUSE_PLACEHOLDER (passed in DATA) in *TP.  */

ایستا درخت
c_find_omp_placeholder_r (درخت *tp, صحیح *, تهی *data)
{
  اگر (*tp == (درخت) data)
    بازگشت *tp;
  بازگشت NULL_درخت;
}

/* Similarly, but also walk aggregate fields.  */

ساختار c_find_omp_var_s { درخت var; hash_set<درخت> *pset; };

ایستا درخت
c_find_omp_var_r (درخت *tp, صحیح *, تهی *data)
{
  اگر (*tp == ((ساختار c_find_omp_var_s *) data)->var)
    بازگشت *tp;
  اگر (RECORD_OR_UNION_TYPE_P (*tp))
    {
      درخت field;
      hash_set<درخت> *pset = ((ساختار c_find_omp_var_s *) data)->pset;

      برای (field = TYPE_FIELDS (*tp); field;
	   field = DECL_CHAIN (field))
	اگر (درخت_CODE (field) == FIELD_DECL)
	  {
	    درخت ret = walk_درخت (&DECL_FIELD_OFFSET (field),
				  c_find_omp_var_r, data, pset);
	    اگر (ret)
	      بازگشت ret;
	    ret = walk_درخت (&DECL_SIZE (field), c_find_omp_var_r, data, pset);
	    اگر (ret)
	      بازگشت ret;
	    ret = walk_درخت (&DECL_SIZE_UNIT (field), c_find_omp_var_r, data,
			     pset);
	    اگر (ret)
	      بازگشت ret;
	    ret = walk_درخت (&درخت_TYPE (field), c_find_omp_var_r, data, pset);
	    اگر (ret)
	      بازگشت ret;
	  }
    }
  وگرنه اگر (INTEGRAL_TYPE_P (*tp))
    بازگشت walk_درخت (&TYPE_MAX_مقدار (*tp), c_find_omp_var_r, data,
		      ((ساختار c_find_omp_var_s *) data)->pset);
  بازگشت NULL_درخت;
}

/* Finish OpenMP iterators ITER.  Return true if they are erroneous
   and clauses containing them should be removed.  */

ایستا منطقی
c_omp_finish_iterators (درخت iter)
{
  منطقی ret = نادرست;
  برای (درخت it = iter; it; it = درخت_CHAIN (it))
    {
      درخت var = OMP_ITERATOR_VAR (it);
      درخت begin = OMP_ITERATOR_BEGIN (it);
      درخت end = OMP_ITERATOR_END (it);
      درخت step = OMP_ITERATOR_STEP (it);
      درخت orig_step;
      درخت type = درخت_TYPE (var);
      location_t loc = DECL_SOURCE_LOCATION (var);
      اگر (type == error_mark_گره)
	{
	  ret = درست;
	  ادامه;
	}
      اگر (!INTEGRAL_TYPE_P (type) && !POINTER_TYPE_P (type))
	{
	  error_at (loc, "iterator %qD has neither integral nor pointer type",
		    var);
	  ret = درست;
	  ادامه;
	}
      وگرنه اگر (TYPE_ATOMIC (type))
	{
	  error_at (loc, "iterator %qD has %<_Atomic%> qualified type", var);
	  ret = درست;
	  ادامه;
	}
      وگرنه اگر (TYPE_READONLY (type))
	{
	  error_at (loc, "iterator %qD has const qualified type", var);
	  ret = درست;
	  ادامه;
	}
      وگرنه اگر (step == error_mark_گره
	       || درخت_TYPE (step) == error_mark_گره)
	{
	  ret = درست;
	  ادامه;
	}
      وگرنه اگر (!INTEGRAL_TYPE_P (درخت_TYPE (step)))
	{
	  error_at (عبارت_LOC_OR_LOC (step, loc),
		    "iterator step with non-integral type");
	  ret = درست;
	  ادامه;
	}
      begin = c_fully_fold (build_c_cast (loc, type, begin), نادرست, پوچ);
      end = c_fully_fold (build_c_cast (loc, type, end), نادرست, پوچ);
      orig_step = save_عبارت (c_fully_fold (step, نادرست, پوچ));
      درخت stype = POINTER_TYPE_P (type) ? sizetype : type;
      step = c_fully_fold (build_c_cast (loc, stype, orig_step), نادرست, پوچ);
      اگر (POINTER_TYPE_P (type))
	{
	  begin = save_عبارت (begin);
	  step = pointer_int_sum (loc, PLUS_عبارت, begin, step);
	  step = fold_build2_loc (loc, MINUS_عبارت, sizetype,
				  fold_convert (sizetype, step),
				  fold_convert (sizetype, begin));
	  step = fold_convert (ssizetype, step);
	}
      اگر (integer_zerop (step))
	{
	  error_at (loc, "iterator %qD has zero step", var);
	  ret = درست;
	  ادامه;
	}

      اگر (begin == error_mark_گره
	  || end == error_mark_گره
	  || step == error_mark_گره
	  || orig_step == error_mark_گره)
	{
	  ret = درست;
	  ادامه;
	}
      hash_set<درخت> pset;
      درخت it2;
      برای (it2 = درخت_CHAIN (it); it2; it2 = درخت_CHAIN (it2))
	{
	  درخت var2 = OMP_ITERATOR_VAR (it2);
	  درخت begin2 = OMP_ITERATOR_BEGIN (it2);
	  درخت end2 = OMP_ITERATOR_END (it2);
	  درخت step2 = OMP_ITERATOR_STEP (it2);
	  درخت type2 = درخت_TYPE (var2);
	  location_t loc2 = DECL_SOURCE_LOCATION (var2);
	  ساختار c_find_omp_var_s data = { var, &pset };
	  اگر (walk_درخت (&type2, c_find_omp_var_r, &data, &pset))
	    {
	      error_at (loc2,
			"type of iterator %qD refers to outer iterator %qD",
			var2, var);
	      بشکن;
	    }
	  وگرنه اگر (walk_درخت (&begin2, c_find_omp_var_r, &data, &pset))
	    {
	      error_at (عبارت_LOC_OR_LOC (begin2, loc2),
			"begin expression refers to outer iterator %qD", var);
	      بشکن;
	    }
	  وگرنه اگر (walk_درخت (&end2, c_find_omp_var_r, &data, &pset))
	    {
	      error_at (عبارت_LOC_OR_LOC (end2, loc2),
			"end expression refers to outer iterator %qD", var);
	      بشکن;
	    }
	  وگرنه اگر (walk_درخت (&step2, c_find_omp_var_r, &data, &pset))
	    {
	      error_at (عبارت_LOC_OR_LOC (step2, loc2),
			"step expression refers to outer iterator %qD", var);
	      بشکن;
	    }
	}
      اگر (it2)
	{
	  ret = درست;
	  ادامه;
	}
      OMP_ITERATOR_BEGIN (it) = begin;
      OMP_ITERATOR_END (it) = end;
      OMP_ITERATOR_STEP (it) = step;
      OMP_ITERATOR_ORIG_STEP (it) = orig_step;
    }
  بازگشت ret;
}

/* Ensure that pointers are used in OpenACC attach and detach clauses.
   Return true if an error has been detected.  */

ایستا منطقی
c_oacc_check_attachments (درخت c)
{
  اگر (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP)
    بازگشت نادرست;

  /* OpenACC attach / detach clauses must be pointers.  */
  اگر (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_ATTACH
      || OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_DETACH)
    {
      درخت t = OMP_CLAUSE_DECL (c);

      وقتی (درخت_CODE (t) == OMP_ARRAY_SECTION)
	t = درخت_OPERAND (t, 0);

      اگر (درخت_CODE (درخت_TYPE (t)) != POINTER_TYPE)
	{
	  error_at (OMP_CLAUSE_LOCATION (c), "expected pointer in %qs clause",
		    user_omp_clause_code_name (c, درست));
	  بازگشت درست;
	}
    }

  بازگشت نادرست;
}

/* For all elements of CLAUSES, validate them against their constraints.
   Remove any elements from the list that are invalid.  */

درخت
c_finish_omp_clauses (درخت clauses, شمارش c_omp_region_type ort)
{
  bitmap_head generic_head, firstprivate_head, lastprivate_head;
  bitmap_head aligned_head, map_head, map_field_head, map_firstprivate_head;
  bitmap_head oacc_reduction_head, is_on_device_head;
  درخت c, t, type, *pc;
  درخت simdlen = NULL_درخت, safelen = NULL_درخت;
  منطقی branch_seen = نادرست;
  منطقی copyprivate_seen = نادرست;
  منطقی mergeable_seen = نادرست;
  درخت *detach_seen = پوچ;
  منطقی linear_variable_step_check = نادرست;
  درخت *nowait_clause = پوچ;
  درخت *grainsize_seen = پوچ;
  منطقی رقم_tasks_seen = نادرست;
  درخت ordered_clause = NULL_درخت;
  درخت schedule_clause = NULL_درخت;
  منطقی oacc_async = نادرست;
  درخت last_iterators = NULL_درخت;
  منطقی last_iterators_remove = نادرست;
  درخت *nogroup_seen = پوچ;
  درخت *order_clause = پوچ;
  /* 1 if normal/task reduction has been seen, -1 if inscan reduction
     has been seen, -2 if mixed inscan/normal reduction diagnosed.  */
  صحیح reduction_seen = 0;
  منطقی allocate_seen = نادرست;
  منطقی implicit_moved = نادرست;
  منطقی target_in_reduction_seen = نادرست;
  درخت *full_seen = پوچ;
  منطقی partial_seen = نادرست;
  منطقی openacc = (ort & C_ORT_ACC) != 0;
  منطقی init_seen = نادرست;
  منطقی init_use_destroy_seen = نادرست;
  درخت init_no_targetsync_clause = NULL_درخت;
  درخت depend_clause = NULL_درخت;

  اگر (!openacc)
    clauses = omp_remove_duplicate_maps (clauses, درست);

  bitmap_obstack_initialize (پوچ);
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

  اگر (openacc)
    برای (c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
      اگر (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ASYNC)
	{
	  oacc_async = درست;
	  بشکن;
	}

  درخت *grp_start_p = پوچ, grp_sentinel = NULL_درخت;

  برای (pc = &clauses, c = clauses; c ; c = *pc)
    {
      منطقی remove = نادرست;
      منطقی need_complete = نادرست;
      منطقی need_implicitly_determined = نادرست;

      /* We've reached the end of a list of expanded nodes.  Reset the group
	 start pointer.  */
      اگر (c == grp_sentinel)
	{
	  اگر (grp_start_p
	      && OMP_CLAUSE_HAS_ITERATORS (*grp_start_p))
	    برای (درخت gc = *grp_start_p; gc != grp_sentinel;
		 gc = OMP_CLAUSE_CHAIN (gc))
	      OMP_CLAUSE_ITERATORS (gc) = OMP_CLAUSE_ITERATORS (*grp_start_p);
	  grp_start_p = پوچ;
	}

      انتخاب (OMP_CLAUSE_CODE (c))
	{
	حالت OMP_CLAUSE_SHARED:
	  need_implicitly_determined = درست;
	  برو check_dup_generic;

	حالت OMP_CLAUSE_PRIVATE:
	  need_complete = درست;
	  need_implicitly_determined = درست;
	  برو check_dup_generic;

	حالت OMP_CLAUSE_REDUCTION:
	  اگر (reduction_seen == 0)
	    reduction_seen = OMP_CLAUSE_REDUCTION_INSCAN (c) ? -1 : 1;
	  وگرنه اگر (reduction_seen != -2
		   && reduction_seen != (OMP_CLAUSE_REDUCTION_INSCAN (c)
					 ? -1 : 1))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<inscan%> and non-%<inscan%> %<reduction%> clauses "
			"on the same construct");
	      reduction_seen = -2;
	    }
	  /* FALLTHRU */
	حالت OMP_CLAUSE_IN_REDUCTION:
	حالت OMP_CLAUSE_TASK_REDUCTION:
	  need_implicitly_determined = درست;
	  t = OMP_CLAUSE_DECL (c);
	  اگر (درخت_CODE (t) == OMP_ARRAY_SECTION)
	    {
	      اگر (handle_omp_array_sections (c, ort))
		{
		  remove = درست;
		  بشکن;
		}

	      t = OMP_CLAUSE_DECL (c);
	      اگر (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
		  && OMP_CLAUSE_REDUCTION_INSCAN (c))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<inscan%> %<reduction%> clause with array "
			    "section");
		  remove = درست;
		  بشکن;
		}
	    }
	  t = require_complete_type (OMP_CLAUSE_LOCATION (c), t);
	  اگر (t == error_mark_گره)
	    {
	      remove = درست;
	      بشکن;
	    }
	  اگر (oacc_async)
	    c_mark_addressable (t);
	  type = درخت_TYPE (t);
	  اگر (درخت_CODE (t) == MEM_REF)
	    type = درخت_TYPE (type);
	  اگر (درخت_CODE (type) == ARRAY_TYPE)
	    {
	      درخت oatype = type;
	      gcc_assert (درخت_CODE (t) != MEM_REF);
	      وقتی (درخت_CODE (type) == ARRAY_TYPE)
		type = درخت_TYPE (type);
	      اگر (integer_zerop (TYPE_SIZE_UNIT (type)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD in %<reduction%> clause is a zero size array",
			    t);
		  remove = درست;
		  بشکن;
		}
	      درخت size = size_binop (EXACT_DIV_عبارت, TYPE_SIZE_UNIT (oatype),
				      TYPE_SIZE_UNIT (type));
	      اگر (integer_zerop (size))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD in %<reduction%> clause is a zero size array",
			    t);
		  remove = درست;
		  بشکن;
		}
	      size = size_binop (MINUS_عبارت, size, size_one_گره);
	      size = save_عبارت (size);
	      درخت index_type = build_index_type (size);
	      درخت atype = c_build_array_type (TYPE_MAIN_VARIANT (type),
					       index_type);
	      atype = c_build_qualified_type (atype, TYPE_QUALS (type));
	      درخت ptype = c_build_pointer_type (type);
	      اگر (درخت_CODE (درخت_TYPE (t)) == ARRAY_TYPE)
		t = build_fold_addr_عبارت (t);
	      t = build2 (MEM_REF, atype, t, build_int_cst (ptype, 0));
	      OMP_CLAUSE_DECL (c) = t;
	    }
	  اگر (TYPE_ATOMIC (type))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<_Atomic%> %qE in %<reduction%> clause", t);
	      remove = درست;
	      بشکن;
	    }
	  اگر (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_REDUCTION
	      || OMP_CLAUSE_REDUCTION_TASK (c))
	    {
	      /* Disallow zero sized or potentially zero sized task
		 reductions.  */
	      اگر (integer_zerop (TYPE_SIZE_UNIT (type)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "zero sized type %qT in %qs clause", type,
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  remove = درست;
		  بشکن;
		}
	      وگرنه اگر (درخت_CODE (TYPE_SIZE_UNIT (type)) != INTEGER_CST)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "variable sized type %qT in %qs clause", type,
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  remove = درست;
		  بشکن;
		}
	    }
	  اگر (OMP_CLAUSE_REDUCTION_PLACEHOLDER (c) == NULL_درخت
	      && (FLOAT_TYPE_P (type)
		  || درخت_CODE (type) == COMPLEX_TYPE))
	    {
	      شمارش درخت_code r_code = OMP_CLAUSE_REDUCTION_CODE (c);
	      ثابت نویسه *r_name = پوچ;

	      انتخاب (r_code)
		{
		حالت PLUS_عبارت:
		حالت MULT_عبارت:
		حالت MINUS_عبارت:
		حالت TRUTH_ANDIF_عبارت:
		حالت TRUTH_ORIF_عبارت:
		  بشکن;
		حالت MIN_عبارت:
		  اگر (درخت_CODE (type) == COMPLEX_TYPE)
		    r_name = "min";
		  بشکن;
		حالت MAX_عبارت:
		  اگر (درخت_CODE (type) == COMPLEX_TYPE)
		    r_name = "max";
		  بشکن;
		حالت BIT_AND_عبارت:
		  r_name = "&";
		  بشکن;
		حالت BIT_XOR_عبارت:
		  r_name = "^";
		  بشکن;
		حالت BIT_IOR_عبارت:
		  r_name = "|";
		  بشکن;
		پیشفرض:
		  gcc_unreachable ();
		}
	      اگر (r_name)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qE has invalid type for %<reduction(%s)%>",
			    t, r_name);
		  remove = درست;
		  بشکن;
		}
	    }
	  وگرنه اگر (OMP_CLAUSE_REDUCTION_PLACEHOLDER (c) == error_mark_گره)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"user defined reduction not found for %qE", t);
	      remove = درست;
	      بشکن;
	    }
	  وگرنه اگر (OMP_CLAUSE_REDUCTION_PLACEHOLDER (c))
	    {
	      درخت list = OMP_CLAUSE_REDUCTION_PLACEHOLDER (c);
	      type = TYPE_MAIN_VARIANT (type);
	      درخت placeholder = build_decl (OMP_CLAUSE_LOCATION (c),
					     VAR_DECL, NULL_درخت, type);
	      درخت decl_placeholder = NULL_درخت;
	      OMP_CLAUSE_REDUCTION_PLACEHOLDER (c) = placeholder;
	      DECL_ARTIFICIAL (placeholder) = 1;
	      DECL_IGNORED_P (placeholder) = 1;
	      اگر (درخت_CODE (t) == MEM_REF)
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
	      OMP_CLAUSE_REDUCTION_MERGE (c)
		= c_clone_omp_udr (درخت_VEC_ELT (list, 2),
				   درخت_VEC_ELT (list, 0),
				   درخت_VEC_ELT (list, 1),
				   decl_placeholder ? decl_placeholder
				   : OMP_CLAUSE_DECL (c), placeholder);
	      OMP_CLAUSE_REDUCTION_MERGE (c)
		= build3_loc (OMP_CLAUSE_LOCATION (c), BIND_عبارت,
			      void_type_گره, NULL_درخت,
			      OMP_CLAUSE_REDUCTION_MERGE (c), NULL_درخت);
	      درخت_SIDE_EFFECTS (OMP_CLAUSE_REDUCTION_MERGE (c)) = 1;
	      اگر (درخت_VEC_LENGTH (list) == 6)
		{
		  اگر (درخت_ADDRESSABLE (درخت_VEC_ELT (list, 3)))
		    c_mark_addressable (decl_placeholder ? decl_placeholder
					: OMP_CLAUSE_DECL (c));
		  اگر (درخت_ADDRESSABLE (درخت_VEC_ELT (list, 4)))
		    c_mark_addressable (placeholder);
		  درخت init = درخت_VEC_ELT (list, 5);
		  اگر (init == error_mark_گره)
		    init = DECL_INITIAL (درخت_VEC_ELT (list, 3));
		  OMP_CLAUSE_REDUCTION_INIT (c)
		    = c_clone_omp_udr (init, درخت_VEC_ELT (list, 4),
				       درخت_VEC_ELT (list, 3),
				       decl_placeholder ? decl_placeholder
				       : OMP_CLAUSE_DECL (c), placeholder);
		  اگر (درخت_VEC_ELT (list, 5) == error_mark_گره)
		    {
		      درخت v = decl_placeholder ? decl_placeholder : t;
		      OMP_CLAUSE_REDUCTION_INIT (c)
			= build2 (INIT_عبارت, درخت_TYPE (v), v,
				  OMP_CLAUSE_REDUCTION_INIT (c));
		    }
		  اگر (walk_درخت (&OMP_CLAUSE_REDUCTION_INIT (c),
				 c_find_omp_placeholder_r,
				 placeholder, پوچ))
		    OMP_CLAUSE_REDUCTION_OMP_ORIG_REF (c) = 1;
		}
	      وگرنه
		{
		  درخت init;
		  درخت v = decl_placeholder ? decl_placeholder : t;
		  اگر (AGGREGATE_TYPE_P (درخت_TYPE (v)))
		    init = build_constructor (درخت_TYPE (v), پوچ);
		  وگرنه
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
	  اگر (درخت_CODE (t) == MEM_REF)
	    {
	      اگر (TYPE_SIZE_UNIT (درخت_TYPE (درخت_TYPE (t))) == NULL_درخت
		  || درخت_CODE (TYPE_SIZE_UNIT (درخت_TYPE (درخت_TYPE (t))))
		     != INTEGER_CST)
		{
		  sorry ("variable length element type in array "
			 "%<reduction%> clause");
		  remove = درست;
		  بشکن;
		}
	      t = درخت_OPERAND (t, 0);
	      اگر (درخت_CODE (t) == POINTER_PLUS_عبارت)
		t = درخت_OPERAND (t, 0);
	      اگر (درخت_CODE (t) == ADDR_عبارت)
		t = درخت_OPERAND (t, 0);
	    }
	  برو check_dup_generic_t;

	حالت OMP_CLAUSE_COPYPRIVATE:
	  copyprivate_seen = درست;
	  اگر (nowait_clause)
	    {
	      error_at (OMP_CLAUSE_LOCATION (*nowait_clause),
			"%<nowait%> clause must not be used together "
			"with %<copyprivate%> clause");
	      *nowait_clause = OMP_CLAUSE_CHAIN (*nowait_clause);
	      nowait_clause = پوچ;
	    }
	  برو check_dup_generic;

	حالت OMP_CLAUSE_COPYIN:
	  t = OMP_CLAUSE_DECL (c);
	  اگر (!VAR_P (t) || !DECL_THREAD_LOCAL_P (t))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE must be %<threadprivate%> for %<copyin%>", t);
	      remove = درست;
	      بشکن;
	    }
	  برو check_dup_generic;

	حالت OMP_CLAUSE_LINEAR:
	  اگر (ort != C_ORT_OMP_DECLARE_SIMD)
	    need_implicitly_determined = درست;
	  t = OMP_CLAUSE_DECL (c);
	  اگر (ort != C_ORT_OMP_DECLARE_SIMD
	      && OMP_CLAUSE_LINEAR_KIND (c) != OMP_CLAUSE_LINEAR_DEFAULT
	      && OMP_CLAUSE_LINEAR_OLD_LINEAR_MODIFIER (c))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"modifier should not be specified in %<linear%> "
			"clause on %<simd%> or %<for%> constructs when not "
			"using OpenMP 5.2 modifiers");
	      OMP_CLAUSE_LINEAR_KIND (c) = OMP_CLAUSE_LINEAR_DEFAULT;
	    }
	  اگر (!INTEGRAL_TYPE_P (درخت_TYPE (t))
	      && درخت_CODE (درخت_TYPE (t)) != POINTER_TYPE)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"linear clause applied to non-integral non-pointer "
			"variable with type %qT", درخت_TYPE (t));
	      remove = درست;
	      بشکن;
	    }
	  اگر (TYPE_ATOMIC (درخت_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<_Atomic%> %qD in %<linear%> clause", t);
	      remove = درست;
	      بشکن;
	    }
	  اگر (ort == C_ORT_OMP_DECLARE_SIMD)
	    {
	      درخت s = OMP_CLAUSE_LINEAR_STEP (c);
	      اگر (درخت_CODE (s) == PARM_DECL)
		{
		  OMP_CLAUSE_LINEAR_VARIABLE_STRIDE (c) = 1;
		  /* map_head bitmap is used as uniform_head if
		     declare_simd.  */
		  اگر (!bitmap_bit_p (&map_head, DECL_UID (s)))
		    linear_variable_step_check = درست;
		  برو check_dup_generic;
		}
	      اگر (درخت_CODE (s) != INTEGER_CST)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<linear%> clause step %qE is neither constant "
			    "nor a parameter", s);
		  remove = درست;
		  بشکن;
		}
	    }
	  اگر (درخت_CODE (درخت_TYPE (OMP_CLAUSE_DECL (c))) == POINTER_TYPE)
	    {
	      درخت s = OMP_CLAUSE_LINEAR_STEP (c);
	      s = pointer_int_sum (OMP_CLAUSE_LOCATION (c), PLUS_عبارت,
				   OMP_CLAUSE_DECL (c), s);
	      s = fold_build2_loc (OMP_CLAUSE_LOCATION (c), MINUS_عبارت,
				   sizetype, fold_convert (sizetype, s),
				   fold_convert
				     (sizetype, OMP_CLAUSE_DECL (c)));
	      اگر (s == error_mark_گره)
		s = size_one_گره;
	      OMP_CLAUSE_LINEAR_STEP (c) = s;
	    }
	  وگرنه
	    OMP_CLAUSE_LINEAR_STEP (c)
	      = fold_convert (درخت_TYPE (t), OMP_CLAUSE_LINEAR_STEP (c));
	  برو check_dup_generic;

	check_dup_generic:
	  t = OMP_CLAUSE_DECL (c);
	check_dup_generic_t:
	  اگر (!VAR_P (t) && درخت_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %qs", t,
			omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	      remove = درست;
	    }
	  وگرنه اگر ((openacc && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION)
		   || (ort == C_ORT_OMP
		       && (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_USE_DEVICE_PTR
			   || (OMP_CLAUSE_CODE (c)
			       == OMP_CLAUSE_USE_DEVICE_ADDR)))
		   || (ort == C_ORT_OMP_TARGET
		       && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION))
	    {
	      اگر (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
		  && (bitmap_bit_p (&generic_head, DECL_UID (t))
		      || bitmap_bit_p (&firstprivate_head, DECL_UID (t))))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in data-sharing "
			    "clauses", t);
		  remove = درست;
		  بشکن;
		}
	      اگر (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION)
		target_in_reduction_seen = درست;
	      اگر (bitmap_bit_p (&oacc_reduction_head, DECL_UID (t)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    openacc
			    ? "%qD appears more than once in reduction clauses"
			    : "%qD appears more than once in data clauses",
			    t);
		  remove = درست;
		}
	      وگرنه
		bitmap_set_bit (&oacc_reduction_head, DECL_UID (t));
	    }
	  وگرنه اگر (bitmap_bit_p (&generic_head, DECL_UID (t))
		   || bitmap_bit_p (&firstprivate_head, DECL_UID (t))
		   || bitmap_bit_p (&lastprivate_head, DECL_UID (t))
		   || bitmap_bit_p (&map_firstprivate_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in data clauses", t);
	      remove = درست;
	    }
	  وگرنه اگر ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_PRIVATE
		    || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_HAS_DEVICE_ADDR
		    || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IS_DEVICE_PTR)
		   && bitmap_bit_p (&map_head, DECL_UID (t)))
	    {
	      اگر (openacc)
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears more than once in data clauses", t);
	      وگرنه
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears both in data and map clauses", t);
	      remove = درست;
	    }
	  وگرنه
	    bitmap_set_bit (&generic_head, DECL_UID (t));
	  بشکن;

	حالت OMP_CLAUSE_FIRSTPRIVATE:
	  اگر (OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (c) && !implicit_moved)
	    {
	    move_implicit:
	      implicit_moved = درست;
	      /* Move firstprivate and map clauses with
		 OMP_CLAUSE_{FIRSTPRIVATE,MAP}_IMPLICIT set to the end of
		 clauses chain.  */
	      درخت cl1 = NULL_درخت, cl2 = NULL_درخت;
	      درخت *pc1 = pc, *pc2 = &cl1, *pc3 = &cl2;
	      وقتی (*pc1)
		اگر (OMP_CLAUSE_CODE (*pc1) == OMP_CLAUSE_FIRSTPRIVATE
		    && OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (*pc1))
		  {
		    *pc3 = *pc1;
		    pc3 = &OMP_CLAUSE_CHAIN (*pc3);
		    *pc1 = OMP_CLAUSE_CHAIN (*pc1);
		  }
		وگرنه اگر (OMP_CLAUSE_CODE (*pc1) == OMP_CLAUSE_MAP
			 && OMP_CLAUSE_MAP_IMPLICIT (*pc1))
		  {
		    *pc2 = *pc1;
		    pc2 = &OMP_CLAUSE_CHAIN (*pc2);
		    *pc1 = OMP_CLAUSE_CHAIN (*pc1);
		  }
		وگرنه
		  pc1 = &OMP_CLAUSE_CHAIN (*pc1);
	      *pc3 = پوچ;
	      *pc2 = cl2;
	      *pc1 = cl1;
	      ادامه;
	    }
	  t = OMP_CLAUSE_DECL (c);
	  need_complete = درست;
	  need_implicitly_determined = درست;
	  اگر (!VAR_P (t) && درخت_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %<firstprivate%>", t);
	      remove = درست;
	    }
	  وگرنه اگر (OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (c)
		   && !OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT_TARGET (c)
		   && bitmap_bit_p (&map_firstprivate_head, DECL_UID (t)))
	    remove = درست;
	  وگرنه اگر (bitmap_bit_p (&generic_head, DECL_UID (t))
		   || bitmap_bit_p (&firstprivate_head, DECL_UID (t))
		   || bitmap_bit_p (&map_firstprivate_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in data clauses", t);
	      remove = درست;
	    }
	  وگرنه اگر (bitmap_bit_p (&map_head, DECL_UID (t))
		   || bitmap_bit_p (&map_field_head, DECL_UID (t)))
	    {
	      اگر (openacc)
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears more than once in data clauses", t);
	      وگرنه اگر (OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (c)
		       && !OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT_TARGET (c))
		/* Silently drop the clause.  */;
	      وگرنه
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears both in data and map clauses", t);
	      remove = درست;
	    }
	  وگرنه
	    bitmap_set_bit (&firstprivate_head, DECL_UID (t));
	  بشکن;

	حالت OMP_CLAUSE_LASTPRIVATE:
	  t = OMP_CLAUSE_DECL (c);
	  need_complete = درست;
	  need_implicitly_determined = درست;
	  اگر (!VAR_P (t) && درخت_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %<lastprivate%>", t);
	      remove = درست;
	    }
	  وگرنه اگر (bitmap_bit_p (&generic_head, DECL_UID (t))
		   || bitmap_bit_p (&lastprivate_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
		     "%qE appears more than once in data clauses", t);
	      remove = درست;
	    }
	  وگرنه
	    bitmap_set_bit (&lastprivate_head, DECL_UID (t));
	  بشکن;

	حالت OMP_CLAUSE_ALIGNED:
	  t = OMP_CLAUSE_DECL (c);
	  اگر (!VAR_P (t) && درخت_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in %<aligned%> clause", t);
	      remove = درست;
	    }
	  وگرنه اگر (!POINTER_TYPE_P (درخت_TYPE (t))
		   && درخت_CODE (درخت_TYPE (t)) != ARRAY_TYPE)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE in %<aligned%> clause is neither a pointer nor "
			"an array", t);
	      remove = درست;
	    }
	  وگرنه اگر (TYPE_ATOMIC (درخت_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<_Atomic%> %qD in %<aligned%> clause", t);
	      remove = درست;
	      بشکن;
	    }
	  وگرنه اگر (bitmap_bit_p (&aligned_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in %<aligned%> clauses",
			t);
	      remove = درست;
	    }
	  وگرنه
	    bitmap_set_bit (&aligned_head, DECL_UID (t));
	  بشکن;

	حالت OMP_CLAUSE_NONTEMPORAL:
	  t = OMP_CLAUSE_DECL (c);
	  اگر (!VAR_P (t) && درخت_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in %<nontemporal%> clause", t);
	      remove = درست;
	    }
	  وگرنه اگر (bitmap_bit_p (&oacc_reduction_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in %<nontemporal%> "
			"clauses", t);
	      remove = درست;
	    }
	  وگرنه
	    bitmap_set_bit (&oacc_reduction_head, DECL_UID (t));
	  بشکن;

	حالت OMP_CLAUSE_ALLOCATE:
	  t = OMP_CLAUSE_DECL (c);
	  اگر (!VAR_P (t) && درخت_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in %<allocate%> clause", t);
	      remove = درست;
	    }
	  وگرنه اگر (bitmap_bit_p (&aligned_head, DECL_UID (t)))
	    {
	      warning_at (OMP_CLAUSE_LOCATION (c), OPT_Wopenmp,
			  "%qE appears more than once in %<allocate%> clauses",
			  t);
	      remove = درست;
	    }
	  وگرنه
	    {
	      bitmap_set_bit (&aligned_head, DECL_UID (t));
	      اگر (!OMP_CLAUSE_ALLOCATE_COMBINED (c))
		allocate_seen = درست;
	    }
	  بشکن;

	حالت OMP_CLAUSE_DOACROSS:
	  t = OMP_CLAUSE_DECL (c);
	  اگر (t == NULL_درخت)
	    بشکن;
	  اگر (OMP_CLAUSE_DOACROSS_KIND (c) == OMP_CLAUSE_DOACROSS_SINK)
	    {
	      gcc_assert (درخت_CODE (t) == درخت_LIST);
	      برای (; t; t = درخت_CHAIN (t))
		{
		  درخت decl = درخت_مقدار (t);
		  اگر (درخت_CODE (درخت_TYPE (decl)) == POINTER_TYPE)
		    {
		      درخت offset = درخت_PURPOSE (t);
		      منطقی neg = wi::neg_p (wi::to_wide (offset));
		      offset = fold_unary (ABS_عبارت, درخت_TYPE (offset), offset);
		      درخت t2 = pointer_int_sum (OMP_CLAUSE_LOCATION (c),
						 neg ? MINUS_عبارت : PLUS_عبارت,
						 decl, offset);
		      t2 = fold_build2_loc (OMP_CLAUSE_LOCATION (c), MINUS_عبارت,
					    sizetype,
					    fold_convert (sizetype, t2),
					    fold_convert (sizetype, decl));
		      اگر (t2 == error_mark_گره)
			{
			  remove = درست;
			  بشکن;
			}
		      درخت_PURPOSE (t) = t2;
		    }
		}
	      بشکن;
	    }
	  gcc_unreachable ();

	حالت OMP_CLAUSE_USES_ALLOCATORS:
	  t = OMP_CLAUSE_USES_ALLOCATORS_ALLOCATOR (c);
	  اگر (t == error_mark_گره)
	    {
	      remove = درست;
	      بشکن;
	    }
	  اگر ((VAR_P (t) || درخت_CODE (t) == PARM_DECL)
	      && (bitmap_bit_p (&generic_head, DECL_UID (t))
		  || bitmap_bit_p (&map_head, DECL_UID (t))
		  || bitmap_bit_p (&firstprivate_head, DECL_UID (t))
		  || bitmap_bit_p (&lastprivate_head, DECL_UID (t))))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in data clauses", t);
	      remove = درست;
	      بشکن;
	    }
	  وگرنه
	    bitmap_set_bit (&generic_head, DECL_UID (t));
	  اگر (درخت_CODE (درخت_TYPE (t)) != ENUMERAL_TYPE
	      || strcmp (IDENTIFIER_POINTER (TYPE_IDENTIFIER (درخت_TYPE (t))),
			 "omp_allocator_handle_t") != 0)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"allocator %qE must be of %<omp_allocator_handle_t%> "
			"type", t);
	      remove = درست;
	      بشکن;
	    }
	  درخت init;
	  اگر (!DECL_P (t)
	      || (درخت_CODE (t) == CONST_DECL
		  && ((init = DECL_INITIAL(t)) == nullptr
		      || درخت_CODE (init) != INTEGER_CST
		      || ((wi::to_widest (init) < 0
			   || wi::to_widest (init) > GOMP_OMP_PREDEF_ALLOC_MAX)
			  && (wi::to_widest (init) < GOMP_OMPX_PREDEF_ALLOC_MIN
			      || (wi::to_widest (init)
				  > GOMP_OMPX_PREDEF_ALLOC_MAX))))))
	    {
	      remove = درست;
	      error_at (OMP_CLAUSE_LOCATION (c),
			"allocator %qE must be either a variable or a "
			"predefined allocator", t);
	      بشکن;
	    }
	  وگرنه اگر (درخت_CODE (t) == CONST_DECL)
	    {
	      /* omp_null_allocator is ignored and for predefined allocators,
		 no special handling is required; thus, mark them removed. */
	      remove = درست;

	      اگر (OMP_CLAUSE_USES_ALLOCATORS_MEMSPACE (c)
		  || OMP_CLAUSE_USES_ALLOCATORS_TRAITS (c))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "modifiers cannot be used with predefined "
			    "allocator %qE", t);
		  بشکن;
		}
	    }
	  t = OMP_CLAUSE_USES_ALLOCATORS_MEMSPACE (c);
	  اگر (t == error_mark_گره)
	    {
	      remove = درست;
	      بشکن;
	    }
	  اگر (t != NULL_درخت
	      && ((درخت_CODE (t) != CONST_DECL && درخت_CODE (t) != INTEGER_CST)
		  || درخت_CODE (درخت_TYPE (t)) != ENUMERAL_TYPE
		  || strcmp (IDENTIFIER_POINTER (TYPE_IDENTIFIER (درخت_TYPE (t))),
			     "omp_memspace_handle_t") != 0))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c), "memspace modifier %qE must be"
			" constant enum of %<omp_memspace_handle_t%> type", t);
	      remove = درست;
	      بشکن;
	    }
	  t = OMP_CLAUSE_USES_ALLOCATORS_TRAITS (c);
	  اگر (t == error_mark_گره)
	    {
	      remove = درست;
	      بشکن;
	    }
	  اگر (t != NULL_درخت
	      && t != error_mark_گره
	      && (DECL_EXTERNAL (t)
		  || درخت_CODE (t) == PARM_DECL))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c), "traits array %qE must be "
			"defined in same scope as the construct on which the "
			"clause appears", t);
	      remove = درست;
	    }
	  اگر (t != NULL_درخت)
	    {
	      منطقی type_err = نادرست;

	      اگر (درخت_CODE (درخت_TYPE (t)) != ARRAY_TYPE
		  || DECL_SIZE (t) == NULL_درخت
		  || !COMPLETE_TYPE_P (درخت_TYPE (t)))
		type_err = درست;
	      وگرنه
		{
		  درخت elem_t = درخت_TYPE (درخت_TYPE (t));
		  اگر (درخت_CODE (elem_t) != RECORD_TYPE
		      || strcmp (IDENTIFIER_POINTER (TYPE_IDENTIFIER (elem_t)),
				 "omp_alloctrait_t") != 0
		      || !TYPE_READONLY (elem_t))
		    type_err = درست;
		}
	      اگر (type_err)
		{
		  اگر (t != error_mark_گره)
		    error_at (OMP_CLAUSE_LOCATION (c), "traits array %qE must "
			      "be of %<const omp_alloctrait_t []%> type", t);
		  وگرنه
		    error_at (OMP_CLAUSE_LOCATION (c), "traits array must "
			      "be of %<const omp_alloctrait_t []%> type");
		  remove = درست;
		}
	      وگرنه
		{
		  درخت cst_val = decl_constant_مقدار_1 (t, درست);
		  اگر (cst_val == t)
		    {
		      error_at (OMP_CLAUSE_LOCATION (c), "traits array must be "
				"initialized with constants");

		      remove = درست;
		    }
		}
	    }
	  اگر (remove)
	    بشکن;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ادامه;
	حالت OMP_CLAUSE_DEPEND:
	  depend_clause = c;
	  /* FALLTHRU */
	حالت OMP_CLAUSE_AFFINITY:
	  t = OMP_CLAUSE_DECL (c);
	  اگر (OMP_ITERATOR_DECL_P (t))
	    {
	      اگر (درخت_PURPOSE (t) != last_iterators)
		last_iterators_remove
		  = c_omp_finish_iterators (درخت_PURPOSE (t));
	      last_iterators = درخت_PURPOSE (t);
	      t = درخت_مقدار (t);
	      اگر (last_iterators_remove)
		t = error_mark_گره;
	    }
	  وگرنه
	    last_iterators = NULL_درخت;
	  اگر (درخت_CODE (t) == OMP_ARRAY_SECTION)
	    {
	      اگر (handle_omp_array_sections (c, ort))
		remove = درست;
	      وگرنه اگر (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
		       && OMP_CLAUSE_DEPEND_KIND (c) == OMP_CLAUSE_DEPEND_DEPOBJ)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<depend%> clause with %<depobj%> dependence "
			    "type on array section");
		  remove = درست;
		}
	      بشکن;
	    }
	  اگر (t == error_mark_گره)
	    remove = درست;
	  وگرنه اگر (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
		   && t == ridpointers[RID_OMP_ALL_MEMORY])
	    {
	      اگر (OMP_CLAUSE_DEPEND_KIND (c) != OMP_CLAUSE_DEPEND_OUT
		  && OMP_CLAUSE_DEPEND_KIND (c) != OMP_CLAUSE_DEPEND_INOUT)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<omp_all_memory%> used with %<depend%> kind "
			    "other than %<out%> or %<inout%>");
		  remove = درست;
		}
	    }
	  وگرنه اگر (!lvalue_p (t))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not lvalue expression nor array section in "
			"%qs clause", t,
			omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	      remove = درست;
	    }
	  وگرنه اگر (درخت_CODE (t) == COMPONENT_REF
		   && DECL_C_BIT_FIELD (درخت_OPERAND (t, 1)))
	    {
	      gcc_assert (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
			  || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY);
	      error_at (OMP_CLAUSE_LOCATION (c),
			"bit-field %qE in %qs clause", t,
			omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	      remove = درست;
	    }
	  وگرنه اگر (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
		   && OMP_CLAUSE_DEPEND_KIND (c) == OMP_CLAUSE_DEPEND_DEPOBJ)
	    {
	      اگر (!c_omp_depend_t_p (درخت_TYPE (t)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qE does not have %<omp_depend_t%> type in "
			    "%<depend%> clause with %<depobj%> dependence "
			    "type", t);
		  remove = درست;
		}
	    }
	  وگرنه اگر (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
		   && c_omp_depend_t_p (درخت_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE should not have %<omp_depend_t%> type in "
			"%<depend%> clause with dependence type other than "
			"%<depobj%>", t);
	      remove = درست;
	    }
	  اگر (!remove)
	    {
	      اگر (t == ridpointers[RID_OMP_ALL_MEMORY])
		t = null_pointer_گره;
	      وگرنه
		{
		  درخت addr = build_unary_op (OMP_CLAUSE_LOCATION (c),
					      ADDR_عبارت, t, نادرست);
		  اگر (addr == error_mark_گره)
		    {
		      remove = درست;
		      بشکن;
		    }
		  t = build_indirect_ref (OMP_CLAUSE_LOCATION (c), addr,
					  RO_UNARY_STAR);
		  اگر (t == error_mark_گره)
		    {
		      remove = درست;
		      بشکن;
		    }
		}
	      اگر (OMP_ITERATOR_DECL_P (OMP_CLAUSE_DECL (c)))
		درخت_مقدار (OMP_CLAUSE_DECL (c)) = t;
	      وگرنه
		OMP_CLAUSE_DECL (c) = t;
	    }
	  بشکن;

	حالت OMP_CLAUSE_MAP:
	  اگر (OMP_CLAUSE_MAP_IMPLICIT (c) && !implicit_moved)
	    برو move_implicit;
	  اگر (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_افزودن_MAPPER_NAME
	      || OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_برداشت_MAPPER_NAME)
	    {
	      remove = درست;
	      بشکن;
	    }
	  /* FALLTHRU */
	حالت OMP_CLAUSE_TO:
	حالت OMP_CLAUSE_FROM:
	  اگر (OMP_CLAUSE_ITERATORS (c)
	      && c_omp_finish_iterators (OMP_CLAUSE_ITERATORS (c)))
	    {
	      t = error_mark_گره;
	      بشکن;
	    }
	  /* FALLTHRU */
	حالت OMP_CLAUSE__CACHE_:
	  {
	    using فضاینام omp_addr_tokenizer;
	    auto_vec<omp_addr_token *, 10> addr_tokens;

	    t = OMP_CLAUSE_DECL (c);
	    اگر (درخت_CODE (t) == OMP_ARRAY_SECTION)
	      {
		grp_start_p = pc;
		grp_sentinel = OMP_CLAUSE_CHAIN (c);

		اگر (handle_omp_array_sections (c, ort))
		  remove = درست;
		وگرنه
		  {
		    t = OMP_CLAUSE_DECL (c);
		    اگر (!omp_mappable_type (درخت_TYPE (t)))
		      {
			error_at (OMP_CLAUSE_LOCATION (c),
				  "array section does not have mappable type "
				  "in %qs clause",
				  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
			remove = درست;
		      }
		    وگرنه اگر (TYPE_ATOMIC (درخت_TYPE (t)))
		      {
			error_at (OMP_CLAUSE_LOCATION (c),
				  "%<_Atomic%> %qE in %qs clause", t,
				  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
			remove = درست;
		      }
		    وقتی (درخت_CODE (t) == ARRAY_REF)
		      t = درخت_OPERAND (t, 0);

		    c_omp_address_inspector ai (OMP_CLAUSE_LOCATION (c), t);

		    اگر (!omp_parse_عبارت (addr_tokens, t))
		      {
			sorry_at (OMP_CLAUSE_LOCATION (c),
				  "unsupported map expression %qE",
				  OMP_CLAUSE_DECL (c));
			remove = درست;
			بشکن;
		      }

		    /* This check is to determine if this will be the only map
		       node created for this clause.  Otherwise, we'll check
		       the following FIRSTPRIVATE_POINTER or ATTACH_DETACH
		       node on the next iteration(s) of the loop.   */
		    اگر (addr_tokens.length () >= 4
			&& addr_tokens[0]->type == STRUCTURE_BASE
			&& addr_tokens[0]->u.structure_base_kind == BASE_DECL
			&& addr_tokens[1]->type == ACCESS_METHOD
			&& addr_tokens[2]->type == COMPONENT_SELECTOR
			&& addr_tokens[3]->type == ACCESS_METHOD
			&& (addr_tokens[3]->u.access_kind == ACCESS_DIRECT
			    || (addr_tokens[3]->u.access_kind
				== ACCESS_INDEXED_ARRAY)))
		      {
			درخت rt = addr_tokens[1]->عبارت;

			gcc_assert (DECL_P (rt));

			اگر (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
			    && OMP_CLAUSE_MAP_IMPLICIT (c)
			    && (bitmap_bit_p (&map_head, DECL_UID (rt))
				|| bitmap_bit_p (&map_field_head, DECL_UID (rt))
				|| bitmap_bit_p (&map_firstprivate_head,
						 DECL_UID (rt))))
			  {
			    remove = درست;
			    بشکن;
			  }
			اگر (bitmap_bit_p (&map_field_head, DECL_UID (rt)))
			  بشکن;
			اگر (bitmap_bit_p (&map_head, DECL_UID (rt)))
			  {
			    اگر (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP)
			      error_at (OMP_CLAUSE_LOCATION (c),
					"%qD appears more than once in motion "
					"clauses", rt);
			    وگرنه اگر (openacc)
			      error_at (OMP_CLAUSE_LOCATION (c),
					"%qD appears more than once in data "
					"clauses", rt);
			    وگرنه
			      error_at (OMP_CLAUSE_LOCATION (c),
					"%qD appears more than once in map "
					"clauses", rt);
			    remove = درست;
			  }
			وگرنه
			  {
			    bitmap_set_bit (&map_head, DECL_UID (rt));
			    bitmap_set_bit (&map_field_head, DECL_UID (rt));
			  }
		      }
		  }
		اگر (c_oacc_check_attachments (c))
		  remove = درست;
		اگر (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		    && (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_ATTACH
			|| OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_DETACH)
		    && !OMP_CLAUSE_SIZE (c))
		  /* In this case, we have a single array element which is a
		     pointer, and we already set OMP_CLAUSE_SIZE in
		     handle_omp_array_sections above.  For attach/detach
		     clauses, reset the OMP_CLAUSE_SIZE (representing a bias)
		     to zero here.  */
		  OMP_CLAUSE_SIZE (c) = size_zero_گره;
		بشکن;
	      }
	    وگرنه اگر (!omp_parse_عبارت (addr_tokens, t))
	      {
		sorry_at (OMP_CLAUSE_LOCATION (c),
			  "unsupported map expression %qE",
			  OMP_CLAUSE_DECL (c));
		remove = درست;
		بشکن;
	      }
	    اگر (t == error_mark_گره)
	      {
		remove = درست;
		بشکن;
	      }

	    درخت attr;
	    اگر (DECL_P (t)
		&& OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		&& (attr = lookup_attribute ("omp declare target",
					     DECL_ATTRIBUTES (t)))
		&& مقدار_member (get_identifier ("local"),
				 درخت_مقدار (attr)))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "device-local variable %qD cannot appear "
			  "in map clause", t);
		remove = درست;
		بشکن;
	      }

	    /* OpenACC attach / detach clauses must be pointers.  */
	    اگر (c_oacc_check_attachments (c))
	      {
		remove = درست;
		بشکن;
	      }
	    اگر (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		&& (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_ATTACH
		    || OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_DETACH)
		&& !OMP_CLAUSE_SIZE (c))
	      /* For attach/detach clauses, set OMP_CLAUSE_SIZE (representing a
		 bias) to zero here, so it is not set erroneously to the pointer
		 size later on in gimplify.cc.  */
	      OMP_CLAUSE_SIZE (c) = size_zero_گره;

	    c_omp_address_inspector ai (OMP_CLAUSE_LOCATION (c), t);

	    اگر (!ai.check_clause (c))
	      {
		remove = درست;
		بشکن;
	      }

	    اگر (!ai.map_supported_p ())
	      {
		sorry_at (OMP_CLAUSE_LOCATION (c),
			  "unsupported map expression %qE",
			  OMP_CLAUSE_DECL (c));
		remove = درست;
		بشکن;
	      }

	    gcc_assert ((addr_tokens[0]->type == ARRAY_BASE
			 || addr_tokens[0]->type == STRUCTURE_BASE)
			&& addr_tokens[1]->type == ACCESS_METHOD);

	    t = addr_tokens[1]->عبارت;

	    اگر (addr_tokens[0]->u.structure_base_kind != BASE_DECL)
	      برو skip_decl_checks;

	    /* For OpenMP, we can access a struct "t" and "t.d" on the same
	       mapping.  OpenACC allows multiple fields of the same structure
	       to be written.  */
	    اگر (addr_tokens[0]->type == STRUCTURE_BASE
		&& (bitmap_bit_p (&map_field_head, DECL_UID (t))
		    || (!openacc && bitmap_bit_p (&map_head, DECL_UID (t)))))
	      برو skip_decl_checks;

	    اگر (!VAR_P (t) && درخت_CODE (t) != PARM_DECL)
	      {
		اگر (ort != C_ORT_ACC && عبارت_P (t))
		  بشکن;

		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is not a variable in %qs clause", t,
			  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		remove = درست;
	      }
	    وگرنه اگر (VAR_P (t) && DECL_THREAD_LOCAL_P (t))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD is threadprivate variable in %qs clause", t,
			  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		remove = درست;
	      }
	    وگرنه اگر ((OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP
		      || (OMP_CLAUSE_MAP_KIND (c)
			  != GOMP_MAP_FIRSTPRIVATE_POINTER))
		     && !c_mark_addressable (t))
	      remove = درست;
	    وگرنه اگر (!(OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		       && (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_POINTER
			   || (OMP_CLAUSE_MAP_KIND (c)
			       == GOMP_MAP_FIRSTPRIVATE_POINTER)
			   || (OMP_CLAUSE_MAP_KIND (c)
			       == GOMP_MAP_FORCE_DEVICEPTR)))
		     && t == OMP_CLAUSE_DECL (c)
		     && !omp_mappable_type (درخت_TYPE (t)))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD does not have a mappable type in %qs clause", t,
			  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		remove = درست;
	      }
	    وگرنه اگر (درخت_TYPE (t) == error_mark_گره)
	      remove = درست;
	    وگرنه اگر (TYPE_ATOMIC (strip_array_types (درخت_TYPE (t))))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%<_Atomic%> %qE in %qs clause", t,
			  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		remove = درست;
	      }
	    وگرنه اگر (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		     && OMP_CLAUSE_MAP_IMPLICIT (c)
		     && (bitmap_bit_p (&map_head, DECL_UID (t))
			 || bitmap_bit_p (&map_field_head, DECL_UID (t))
			 || bitmap_bit_p (&map_firstprivate_head,
					  DECL_UID (t))))
	      remove = درست;
	    وگرنه اگر (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		     && (OMP_CLAUSE_MAP_KIND (c)
			 == GOMP_MAP_FIRSTPRIVATE_POINTER))
	      {
		اگر (bitmap_bit_p (&generic_head, DECL_UID (t))
		    || bitmap_bit_p (&firstprivate_head, DECL_UID (t))
		    || bitmap_bit_p (&map_firstprivate_head, DECL_UID (t)))
		  {
		    error_at (OMP_CLAUSE_LOCATION (c),
			      "%qD appears more than once in data clauses", t);
		    remove = درست;
		  }
		وگرنه اگر (bitmap_bit_p (&map_head, DECL_UID (t))
			 && !bitmap_bit_p (&map_field_head, DECL_UID (t))
			 && openacc)
		  {
		    error_at (OMP_CLAUSE_LOCATION (c),
			      "%qD appears more than once in data clauses", t);
		    remove = درست;
		  }
		وگرنه
		  bitmap_set_bit (&map_firstprivate_head, DECL_UID (t));
	      }
	    وگرنه اگر (bitmap_bit_p (&map_head, DECL_UID (t))
		     && !bitmap_bit_p (&map_field_head, DECL_UID (t))
		     && ort != C_ORT_OMP
		     && ort != C_ORT_OMP_TARGET
		     && ort != C_ORT_OMP_EXIT_DATA)
	      {
		اگر (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP)
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in motion clauses", t);
		وگرنه اگر (openacc)
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in data clauses", t);
		وگرنه
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in map clauses", t);
		remove = درست;
	      }
	    وگرنه اگر (openacc && bitmap_bit_p (&generic_head, DECL_UID (t)))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears more than once in data clauses", t);
		remove = درست;
	      }
	    وگرنه اگر (bitmap_bit_p (&firstprivate_head, DECL_UID (t))
		     || bitmap_bit_p (&is_on_device_head, DECL_UID (t)))
	      {
		اگر (openacc)
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in data clauses", t);
		وگرنه
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears both in data and map clauses", t);
		remove = درست;
	      }
	    وگرنه اگر (!omp_access_chain_p (addr_tokens, 1))
	      {
		bitmap_set_bit (&map_head, DECL_UID (t));
		اگر (t != OMP_CLAUSE_DECL (c)
		    && درخت_CODE (OMP_CLAUSE_DECL (c)) == COMPONENT_REF)
		  bitmap_set_bit (&map_field_head, DECL_UID (t));
	      }

	  skip_decl_checks:
	    /* If we call omp_expand_map_clause in handle_omp_array_sections,
	       the containing loop (here) iterates through the new nodes
	       created by that expansion.  Avoid expanding those again (just
	       by checking the node type).  */
	    اگر (!remove
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
		درخت nc = ai.expand_map_clause (c, OMP_CLAUSE_DECL (c),
						addr_tokens, ort);
		اگر (nc != error_mark_گره)
		  c = nc;
	      }
	  }
	  بشکن;

	حالت OMP_CLAUSE_ENTER:
	حالت OMP_CLAUSE_LINK:
	حالت OMP_CLAUSE_LOCAL:
	  t = OMP_CLAUSE_DECL (c);
	  ثابت نویسه *cname;
	  cname = omp_clause_code_name[OMP_CLAUSE_CODE (c)];
	  اگر (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ENTER
	      && OMP_CLAUSE_ENTER_TO (c))
	    cname = "to";
	  اگر (درخت_CODE (t) == FUNCTION_DECL
	      && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ENTER)
	    ;
	  وگرنه اگر (!VAR_P (t))
	    {
	      اگر (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ENTER)
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is neither a variable nor a function name in "
			  "clause %qs", t, cname);
	      وگرنه
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is not a variable in clause %qs", t, cname);
	      remove = درست;
	    }
	  وگرنه اگر (DECL_THREAD_LOCAL_P (t))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD is threadprivate variable in %qs clause", t,
			cname);
	      remove = درست;
	    }
	  وگرنه اگر (!omp_mappable_type (درخت_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD does not have a mappable type in %qs clause", t,
			cname);
	      remove = درست;
	    }
	  اگر (remove)
	    بشکن;
	  اگر (bitmap_bit_p (&generic_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once on the same "
			"%<declare target%> directive", t);
	      remove = درست;
	    }
	  وگرنه
	    bitmap_set_bit (&generic_head, DECL_UID (t));
	  بشکن;

	حالت OMP_CLAUSE_UNIFORM:
	  t = OMP_CLAUSE_DECL (c);
	  اگر (درخت_CODE (t) != PARM_DECL)
	    {
	      اگر (DECL_P (t))
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD is not an argument in %<uniform%> clause", t);
	      وگرنه
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is not an argument in %<uniform%> clause", t);
	      remove = درست;
	      بشکن;
	    }
	  /* map_head bitmap is used as uniform_head if declare_simd.  */
	  bitmap_set_bit (&map_head, DECL_UID (t));
	  برو check_dup_generic;

	حالت OMP_CLAUSE_IS_DEVICE_PTR:
	حالت OMP_CLAUSE_USE_DEVICE_PTR:
	  t = OMP_CLAUSE_DECL (c);
	  اگر (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IS_DEVICE_PTR)
	    bitmap_set_bit (&is_on_device_head, DECL_UID (t));
	  اگر (درخت_CODE (درخت_TYPE (t)) != POINTER_TYPE)
	    {
	      اگر (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_USE_DEVICE_PTR
		  && !openacc)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qs variable is not a pointer",
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  remove = درست;
		}
	      وگرنه اگر (درخت_CODE (درخت_TYPE (t)) != ARRAY_TYPE)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qs variable is neither a pointer nor an array",
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  remove = درست;
		}
	    }
	  برو check_dup_generic;

	حالت OMP_CLAUSE_HAS_DEVICE_ADDR:
	  t = OMP_CLAUSE_DECL (c);
	  اگر (درخت_CODE (t) == OMP_ARRAY_SECTION)
	    {
	      اگر (handle_omp_array_sections (c, ort))
		remove = درست;
	      وگرنه
		{
		  t = OMP_CLAUSE_DECL (c);
		  وقتی (درخت_CODE (t) == ARRAY_REF)
		    t = درخت_OPERAND (t, 0);
		}
	    }
	  bitmap_set_bit (&is_on_device_head, DECL_UID (t));
	  اگر (VAR_P (t) || درخت_CODE (t) == PARM_DECL)
	    c_mark_addressable (t);
	  برو check_dup_generic_t;

	حالت OMP_CLAUSE_USE_DEVICE_ADDR:
	  t = OMP_CLAUSE_DECL (c);
	  اگر (VAR_P (t) || درخت_CODE (t) == PARM_DECL)
	    c_mark_addressable (t);
	  برو check_dup_generic;

	حالت OMP_CLAUSE_NOWAIT:
	  اگر (copyprivate_seen)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<nowait%> clause must not be used together "
			"with %<copyprivate%> clause");
	      remove = درست;
	      بشکن;
	    }
	  nowait_clause = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ادامه;

	حالت OMP_CLAUSE_ORDER:
	  اگر (ordered_clause)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<order%> clause must not be used together "
			"with %<ordered%> clause");
	      remove = درست;
	      بشکن;
	    }
	  وگرنه اگر (order_clause)
	    {
	      /* Silently remove duplicates.  */
	      remove = درست;
	      بشکن;
	    }
	  order_clause = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ادامه;

	حالت OMP_CLAUSE_DETACH:
	  t = OMP_CLAUSE_DECL (c);
	  اگر (detach_seen)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"too many %qs clauses on a task construct",
			"detach");
	      remove = درست;
	      بشکن;
	    }
	  detach_seen = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  c_mark_addressable (t);
	  ادامه;

	حالت OMP_CLAUSE_IF:
	حالت OMP_CLAUSE_SELF:
	حالت OMP_CLAUSE_رقم_THREADS:
	حالت OMP_CLAUSE_رقم_TEAMS:
	حالت OMP_CLAUSE_THREAD_LIMIT:
	حالت OMP_CLAUSE_DEFAULT:
	حالت OMP_CLAUSE_UNTIED:
	حالت OMP_CLAUSE_COLLAPSE:
	حالت OMP_CLAUSE_FINAL:
	حالت OMP_CLAUSE_DEVICE:
	حالت OMP_CLAUSE_DIST_SCHEDULE:
	حالت OMP_CLAUSE_DYN_GROUPPRIVATE:
	حالت OMP_CLAUSE_PARALLEL:
	حالت OMP_CLAUSE_FOR:
	حالت OMP_CLAUSE_SECTIONS:
	حالت OMP_CLAUSE_TASKGROUP:
	حالت OMP_CLAUSE_PROC_BIND:
	حالت OMP_CLAUSE_DEVICE_TYPE:
	حالت OMP_CLAUSE_PRIORITY:
	حالت OMP_CLAUSE_THREADS:
	حالت OMP_CLAUSE_SIMD:
	حالت OMP_CLAUSE_HINT:
	حالت OMP_CLAUSE_FILTER:
	حالت OMP_CLAUSE_DEFAULTMAP:
	حالت OMP_CLAUSE_BIND:
	حالت OMP_CLAUSE_رقم_GANGS:
	حالت OMP_CLAUSE_رقم_WORKERS:
	حالت OMP_CLAUSE_VECTOR_LENGTH:
	حالت OMP_CLAUSE_ASYNC:
	حالت OMP_CLAUSE_WAIT:
	حالت OMP_CLAUSE_AUTO:
	حالت OMP_CLAUSE_INDEPENDENT:
	حالت OMP_CLAUSE_SEQ:
	حالت OMP_CLAUSE_GANG:
	حالت OMP_CLAUSE_WORKER:
	حالت OMP_CLAUSE_VECTOR:
	حالت OMP_CLAUSE_TILE:
	حالت OMP_CLAUSE_IF_PRESENT:
	حالت OMP_CLAUSE_FINALIZE:
	حالت OMP_CLAUSE_NOHOST:
	حالت OMP_CLAUSE_INDIRECT:
	حالت OMP_CLAUSE_NOVARIANTS:
	حالت OMP_CLAUSE_NOCONTEXT:
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ادامه;

	حالت OMP_CLAUSE_GRAINSIZE:
	  grainsize_seen = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ادامه;

	حالت OMP_CLAUSE_رقم_TASKS:
	  رقم_tasks_seen = درست;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ادامه;

	حالت OMP_CLAUSE_MERGEABLE:
	  mergeable_seen = درست;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ادامه;

	حالت OMP_CLAUSE_NOGROUP:
	  nogroup_seen = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ادامه;

	حالت OMP_CLAUSE_SCHEDULE:
	  schedule_clause = c;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ادامه;

	حالت OMP_CLAUSE_ORDERED:
	  ordered_clause = c;
	  اگر (order_clause)
	    {
	      error_at (OMP_CLAUSE_LOCATION (*order_clause),
			"%<order%> clause must not be used together "
			"with %<ordered%> clause");
	      *order_clause = OMP_CLAUSE_CHAIN (*order_clause);
	      order_clause = پوچ;
	    }
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ادامه;

	حالت OMP_CLAUSE_SAFELEN:
	  safelen = c;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ادامه;
	حالت OMP_CLAUSE_SIMDLEN:
	  simdlen = c;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ادامه;

	حالت OMP_CLAUSE_FULL:
	  full_seen = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ادامه;

	حالت OMP_CLAUSE_PARTIAL:
	  partial_seen = درست;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ادامه;

	حالت OMP_CLAUSE_SIZES:
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ادامه;

	حالت OMP_CLAUSE_INBRANCH:
	حالت OMP_CLAUSE_NOTINBRANCH:
	  اگر (branch_seen)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<inbranch%> clause is incompatible with "
			"%<notinbranch%>");
	      remove = درست;
	      بشکن;
	    }
	  branch_seen = درست;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ادامه;

	حالت OMP_CLAUSE_INCLUSIVE:
	حالت OMP_CLAUSE_EXCLUSIVE:
	  need_complete = درست;
	  need_implicitly_determined = درست;
	  t = OMP_CLAUSE_DECL (c);
	  اگر (!VAR_P (t) && درخت_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %qs", t,
			omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	      remove = درست;
	    }
	  بشکن;

	حالت OMP_CLAUSE_INIT:
	  init_seen = درست;
	  اگر (!OMP_CLAUSE_INIT_TARGETSYNC (c))
	    init_no_targetsync_clause = c;
	  /* FALLTHRU */
	حالت OMP_CLAUSE_DESTROY:
	حالت OMP_CLAUSE_USE:
	  init_use_destroy_seen = درست;
	  t = OMP_CLAUSE_DECL (c);
	  اگر (bitmap_bit_p (&generic_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD appears more than once in action clauses", t);
	      remove = درست;
	      بشکن;
	    }
	  bitmap_set_bit (&generic_head, DECL_UID (t));
	  /* FALLTHRU */
	حالت OMP_CLAUSE_INTEROP:
	  اگر (/* ort == C_ORT_OMP_INTEROP [uncomment for depobj init]  */
		   !c_omp_interop_t_p (درخت_TYPE (OMP_CLAUSE_DECL (c))))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD must be of %<omp_interop_t%>",
			OMP_CLAUSE_DECL (c));
	      remove = درست;
	    }
	  وگرنه اگر ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_INIT
		    || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DESTROY)
		   && درخت_READONLY (OMP_CLAUSE_DECL (c)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD shall not be const", OMP_CLAUSE_DECL (c));
	      remove = درست;
	    }
	  pc = &OMP_CLAUSE_CHAIN (c);
	  بشکن;
	پیشفرض:
	  gcc_unreachable ();
	}

      اگر (!remove)
	{
	  t = OMP_CLAUSE_DECL (c);

	  اگر (need_complete)
	    {
	      t = require_complete_type (OMP_CLAUSE_LOCATION (c), t);
	      اگر (t == error_mark_گره)
		remove = درست;
	    }

	  اگر (need_implicitly_determined)
	    {
	      ثابت نویسه *share_name = پوچ;

	      اگر (VAR_P (t) && DECL_THREAD_LOCAL_P (t))
		share_name = "threadprivate";
	      وگرنه انتخاب (c_omp_predetermined_sharing (t))
		{
		حالت OMP_CLAUSE_DEFAULT_UNSPECIFIED:
		  بشکن;
		حالت OMP_CLAUSE_DEFAULT_SHARED:
		  اگر ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_SHARED
		       || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_FIRSTPRIVATE)
		      && c_omp_predefined_variable (t))
		    /* The __func__ variable and similar function-local
		       predefined variables may be listed in a shared or
		       firstprivate clause.  */
		    بشکن;
		  share_name = "shared";
		  بشکن;
		حالت OMP_CLAUSE_DEFAULT_PRIVATE:
		  share_name = "private";
		  بشکن;
		پیشفرض:
		  gcc_unreachable ();
		}
	      اگر (share_name)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qE is predetermined %qs for %qs",
			    t, share_name,
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  remove = درست;
		}
	      وگرنه اگر (درخت_READONLY (t)
		       && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_SHARED
		       && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_FIRSTPRIVATE)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<const%> qualified %qE may appear only in "
			    "%<shared%> or %<firstprivate%> clauses", t);
		  remove = درست;
		}
	    }
	}

      اگر (remove)
	{
	  اگر (grp_start_p)
	    {
	      /* If we found a clause to remove, we want to remove the whole
		 expanded group, otherwise gimplify
		 (omp_resolve_clause_dependencies) can get confused.  */
	      *grp_start_p = grp_sentinel;
	      pc = grp_start_p;
	      grp_start_p = پوچ;
	    }
	  وگرنه
	    *pc = OMP_CLAUSE_CHAIN (c);
	}
      وگرنه
	pc = &OMP_CLAUSE_CHAIN (c);
    }

  اگر (grp_start_p
      && OMP_CLAUSE_HAS_ITERATORS (*grp_start_p))
    برای (درخت gc = *grp_start_p; gc; gc = OMP_CLAUSE_CHAIN (gc))
      OMP_CLAUSE_ITERATORS (gc) = OMP_CLAUSE_ITERATORS (*grp_start_p);

  اگر (simdlen
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

  اگر (ordered_clause
      && schedule_clause
      && (OMP_CLAUSE_SCHEDULE_KIND (schedule_clause)
	  & OMP_CLAUSE_SCHEDULE_NONMONOTONIC))
    {
      error_at (OMP_CLAUSE_LOCATION (schedule_clause),
		"%<nonmonotonic%> schedule modifier specified together "
		"with %<ordered%> clause");
      OMP_CLAUSE_SCHEDULE_KIND (schedule_clause)
	= (شمارش omp_clause_schedule_kind)
	  (OMP_CLAUSE_SCHEDULE_KIND (schedule_clause)
	   & ~OMP_CLAUSE_SCHEDULE_NONMONOTONIC);
    }

  اگر (reduction_seen < 0 && ordered_clause)
    {
      error_at (OMP_CLAUSE_LOCATION (ordered_clause),
		"%qs clause specified together with %<inscan%> "
		"%<reduction%> clause", "ordered");
      reduction_seen = -2;
    }

  اگر (reduction_seen < 0 && schedule_clause)
    {
      error_at (OMP_CLAUSE_LOCATION (schedule_clause),
		"%qs clause specified together with %<inscan%> "
		"%<reduction%> clause", "schedule");
      reduction_seen = -2;
    }

  اگر (linear_variable_step_check
      || reduction_seen == -2
      || allocate_seen
      || target_in_reduction_seen)
    برای (pc = &clauses, c = clauses; c ; c = *pc)
      {
	منطقی remove = نادرست;
	اگر (allocate_seen)
	  انتخاب (OMP_CLAUSE_CODE (c))
	    {
	    حالت OMP_CLAUSE_REDUCTION:
	    حالت OMP_CLAUSE_IN_REDUCTION:
	    حالت OMP_CLAUSE_TASK_REDUCTION:
	      اگر (درخت_CODE (OMP_CLAUSE_DECL (c)) == MEM_REF)
		{
		  t = درخت_OPERAND (OMP_CLAUSE_DECL (c), 0);
		  اگر (درخت_CODE (t) == POINTER_PLUS_عبارت)
		    t = درخت_OPERAND (t, 0);
		  اگر (درخت_CODE (t) == ADDR_عبارت
		      || INDIRECT_REF_P (t))
		    t = درخت_OPERAND (t, 0);
		  اگر (DECL_P (t))
		    bitmap_clear_bit (&aligned_head, DECL_UID (t));
		  بشکن;
		}
	      /* FALLTHRU */
	    حالت OMP_CLAUSE_PRIVATE:
	    حالت OMP_CLAUSE_FIRSTPRIVATE:
	    حالت OMP_CLAUSE_LASTPRIVATE:
	    حالت OMP_CLAUSE_LINEAR:
	      اگر (DECL_P (OMP_CLAUSE_DECL (c)))
		bitmap_clear_bit (&aligned_head,
				  DECL_UID (OMP_CLAUSE_DECL (c)));
	      بشکن;
	    پیشفرض:
	      بشکن;
	    }
	اگر (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_LINEAR
	    && OMP_CLAUSE_LINEAR_VARIABLE_STRIDE (c)
	    && !bitmap_bit_p (&map_head,
			      DECL_UID (OMP_CLAUSE_LINEAR_STEP (c))))
	  {
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%<linear%> clause step is a parameter %qD not "
		      "specified in %<uniform%> clause",
		      OMP_CLAUSE_LINEAR_STEP (c));
	    remove = درست;
	  }
	وگرنه اگر (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
		 && reduction_seen == -2)
	  OMP_CLAUSE_REDUCTION_INSCAN (c) = 0;
	اگر (target_in_reduction_seen
	    && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP)
	  {
	    درخت t = OMP_CLAUSE_DECL (c);
	    وقتی (handled_component_p (t)
		   || INDIRECT_REF_P (t)
		   || درخت_CODE (t) == ADDR_عبارت
		   || درخت_CODE (t) == MEM_REF
		   || درخت_CODE (t) == NON_LVALUE_عبارت)
	      t = درخت_OPERAND (t, 0);
	    اگر (DECL_P (t)
		&& bitmap_bit_p (&oacc_reduction_head, DECL_UID (t)))
	      OMP_CLAUSE_MAP_IN_REDUCTION (c) = 1;
	  }

	اگر (remove)
	  *pc = OMP_CLAUSE_CHAIN (c);
	وگرنه
	  pc = &OMP_CLAUSE_CHAIN (c);
      }

  اگر (allocate_seen)
    برای (pc = &clauses, c = clauses; c ; c = *pc)
      {
	منطقی remove = نادرست;
	اگر (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ALLOCATE
	    && !OMP_CLAUSE_ALLOCATE_COMBINED (c)
	    && bitmap_bit_p (&aligned_head, DECL_UID (OMP_CLAUSE_DECL (c))))
	  {
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD specified in %<allocate%> clause but not in "
		      "an explicit privatization clause", OMP_CLAUSE_DECL (c));
	    remove = درست;
	  }
	اگر (remove)
	  *pc = OMP_CLAUSE_CHAIN (c);
	وگرنه
	  pc = &OMP_CLAUSE_CHAIN (c);
      }

  اگر (nogroup_seen && reduction_seen)
    {
      error_at (OMP_CLAUSE_LOCATION (*nogroup_seen),
		"%<nogroup%> clause must not be used together with "
		"%<reduction%> clause");
      *nogroup_seen = OMP_CLAUSE_CHAIN (*nogroup_seen);
    }

  اگر (grainsize_seen && رقم_tasks_seen)
    {
      error_at (OMP_CLAUSE_LOCATION (*grainsize_seen),
		"%<grainsize%> clause must not be used together with "
		"%<num_tasks%> clause");
      *grainsize_seen = OMP_CLAUSE_CHAIN (*grainsize_seen);
    }

  اگر (full_seen && partial_seen)
    {
      error_at (OMP_CLAUSE_LOCATION (*full_seen),
		"%<full%> clause must not be used together with "
		"%<partial%> clause");
      *full_seen = OMP_CLAUSE_CHAIN (*full_seen);
    }

  اگر (detach_seen)
    {
      اگر (mergeable_seen)
	{
	  error_at (OMP_CLAUSE_LOCATION (*detach_seen),
		    "%<detach%> clause must not be used together with "
		    "%<mergeable%> clause");
	  *detach_seen = OMP_CLAUSE_CHAIN (*detach_seen);
	}
      وگرنه
	{
	  درخت detach_decl = OMP_CLAUSE_DECL (*detach_seen);

	  برای (pc = &clauses, c = clauses; c ; c = *pc)
	    {
	      منطقی remove = نادرست;
	      اگر ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_SHARED
		   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_PRIVATE
		   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_FIRSTPRIVATE
		   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_LASTPRIVATE)
		  && OMP_CLAUSE_DECL (c) == detach_decl)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "the event handle of a %<detach%> clause "
			    "should not be in a data-sharing clause");
		  remove = درست;
		}
	      اگر (remove)
		*pc = OMP_CLAUSE_CHAIN (c);
	      وگرنه
		pc = &OMP_CLAUSE_CHAIN (c);
	    }
	}
    }

  اگر (ort == C_ORT_OMP_INTEROP
      && depend_clause
      && (!init_use_destroy_seen
	  || (init_seen && init_no_targetsync_clause)))
    {
      error_at (OMP_CLAUSE_LOCATION (depend_clause),
		"%<depend%> clause requires action clauses with "
		"%<targetsync%> interop-type");
      اگر (init_no_targetsync_clause)
	inform (OMP_CLAUSE_LOCATION (init_no_targetsync_clause),
		"%<init%> clause lacks the %<targetsync%> modifier");
    }

  bitmap_obstack_release (پوچ);
  بازگشت clauses;
}

/* Do processing necessary to make CLAUSES well-formed, where CLAUSES result
   from implicit instantiation of user-defined mappers (in gimplify.cc).  */

درخت
c_omp_finish_mapper_clauses (درخت clauses)
{
  بازگشت c_finish_omp_clauses (clauses, C_ORT_OMP);
}

/* Return code to initialize DST with a copy constructor from SRC.
   C doesn't have copy constructors nor assignment operators, only for
   _Atomic vars we need to perform __atomic_load from src into a temporary
   followed by __atomic_store of the temporary to dst.  */

درخت
c_omp_clause_copy_ctor (درخت clause, درخت dst, درخت src)
{
  اگر (!really_atomic_lvalue (dst) && !really_atomic_lvalue (src))
    بازگشت build2 (MODIFY_عبارت, درخت_TYPE (dst), dst, src);

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
  درخت fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_LOAD);
  params->quick_افزودن (src_addr);
  params->quick_افزودن (tmp_addr);
  params->quick_افزودن (seq_cst);
  درخت load = c_build_function_call_vec (loc, vNULL, fndecl, params, پوچ);

  vec_alloc (params, 4);

  /* Build __atomic_store (&dst, &tmp, SEQ_CST);  */
  fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_STORE);
  params->quick_افزودن (dst_addr);
  params->quick_افزودن (tmp_addr);
  params->quick_افزودن (seq_cst);
  درخت store = c_build_function_call_vec (loc, vNULL, fndecl, params, پوچ);
  بازگشت build2 (COMPOUND_عبارت, void_type_گره, load, store);
}

/* Create a transaction node.  */

درخت
c_finish_transaction (location_t loc, درخت block, صحیح flags)
{
  درخت stmt = build_stmt (loc, TRANSACTION_عبارت, block);
  اگر (flags & TM_STMT_ATTR_OUTER)
    TRANSACTION_عبارت_OUTER (stmt) = 1;
  اگر (flags & TM_STMT_ATTR_RELAXED)
    TRANSACTION_عبارت_RELAXED (stmt) = 1;
  بازگشت add_stmt (stmt);
}

/* Make a variant type in the proper way for C/C++, propagating qualifiers
   down to the element type of an array.  If ORIG_QUAL_TYPE is not
   NULL, then it should be used as the qualified type
   ORIG_QUAL_INDIRECT levels down in array type derivation (to
   preserve information about the typedef name from which an array
   type was derived).  */

درخت
c_build_qualified_type (درخت type, صحیح type_quals, درخت orig_qual_type,
			size_t orig_qual_indirect)
{
  اگر (type == error_mark_گره)
    بازگشت type;

  اگر (درخت_CODE (type) == ARRAY_TYPE)
    {
      درخت t;
      درخت element_type = c_build_qualified_type (درخت_TYPE (type),
						  type_quals, orig_qual_type,
						  orig_qual_indirect - 1);

      /* See if we already have an identically qualified type.  */
      اگر (orig_qual_type && orig_qual_indirect == 0)
	t = orig_qual_type;
      وگرنه
	برای (t = TYPE_MAIN_VARIANT (type); t; t = TYPE_NEXT_VARIANT (t))
	  {
	    اگر (TYPE_QUALS (strip_array_types (t)) == type_quals
		&& TYPE_NAME (t) == TYPE_NAME (type)
		&& TYPE_CONTEXT (t) == TYPE_CONTEXT (type)
		&& attribute_list_equal (TYPE_ATTRIBUTES (t),
					 TYPE_ATTRIBUTES (type)))
	      بشکن;
	  }
      اگر (!t)
	{
          درخت domain = TYPE_DOMAIN (type);

	  t = build_variant_type_copy (type);
	  درخت_TYPE (t) = element_type;
	  TYPE_ADDR_SPACE (t) = TYPE_ADDR_SPACE (element_type);

          اگر (TYPE_STRUCTURAL_EQUALITY_P (element_type)
              || (domain && TYPE_STRUCTURAL_EQUALITY_P (domain)))
            SET_TYPE_STRUCTURAL_EQUALITY (t);
          وگرنه اگر (TYPE_CANONICAL (element_type) != element_type
                   || (domain && TYPE_CANONICAL (domain) != domain))
            {
              درخت unqualified_canon
		= c_build_array_type (TYPE_CANONICAL (element_type),
				      domain ? TYPE_CANONICAL (domain)
					     : NULL_درخت);
              اگر (TYPE_REVERSE_STORAGE_ORDER (type))
                {
                  unqualified_canon
		    = build_distinct_type_copy (unqualified_canon);
                  TYPE_REVERSE_STORAGE_ORDER (unqualified_canon) = 1;
                }
              TYPE_CANONICAL (t)
		= c_build_qualified_type (unqualified_canon, type_quals);
            }
          وگرنه
            TYPE_CANONICAL (t) = t;
	}
      بازگشت t;
    }

  /* A restrict-qualified pointer type must be a pointer to object or
     incomplete type.  Note that the use of POINTER_TYPE_P also allows
     REFERENCE_TYPEs, which is appropriate for C++.  */
  اگر ((type_quals & TYPE_QUAL_RESTRICT)
      && (!POINTER_TYPE_P (type)
	  || !C_TYPE_OBJECT_OR_INCOMPLETE_P (درخت_TYPE (type))))
    {
      error ("invalid use of %<restrict%>");
      type_quals &= ~TYPE_QUAL_RESTRICT;
    }

  درخت var_type = (orig_qual_type && orig_qual_indirect == 0
		   ? orig_qual_type
		   : build_qualified_type (type, type_quals));

  gcc_checking_assert (C_TYPE_VARIABLE_SIZE (var_type)
		       == C_TYPE_VARIABLE_SIZE (type));
  gcc_checking_assert (c_type_variably_modified_p (var_type)
		       == c_type_variably_modified_p (type));

  /* A variant type does not inherit the list of incomplete vars from the
     type main variant.  */
  اگر ((RECORD_OR_UNION_TYPE_P (var_type)
       || درخت_CODE (var_type) == ENUMERAL_TYPE)
      && TYPE_MAIN_VARIANT (var_type) != var_type)
    C_TYPE_INCOMPLETE_VARS (var_type) = 0;
  بازگشت var_type;
}

/* Build a VA_ARG_EXPR for the C parser.  */

درخت
c_build_va_arg (location_t loc1, درخت عبارت, location_t loc2, درخت type,
		درخت type_عبارت)
{
  اگر (error_operand_p (type))
    بازگشت error_mark_گره;
  /* VA_ARG_EXPR cannot be used for a scalar va_list with reverse storage
     order because it takes the address of the expression.  */
  وگرنه اگر (handled_component_p (عبارت)
	   && reverse_storage_order_for_component_p (عبارت))
    {
      error_at (loc1, "cannot use %<va_arg%> with reverse storage order");
      بازگشت error_mark_گره;
    }
  وگرنه اگر (!COMPLETE_TYPE_P (type))
    {
      error_at (loc2, "second argument to %<va_arg%> is of incomplete "
		"type %qT", type);
      بازگشت error_mark_گره;
    }
  وگرنه اگر (درخت_CODE (type) == FUNCTION_TYPE)
    {
      error_at (loc2, "second argument to %<va_arg%> is a function type %qT",
		type);
      بازگشت error_mark_گره;
    }
  وگرنه اگر (درخت_CODE (type) == ARRAY_TYPE && C_TYPE_VARIABLE_SIZE (type)
	   && !flag_isoc99)
    {
      error_at (loc2, "second argument to %<va_arg%> is an array type %qT",
		type);
      بازگشت error_mark_گره;
    }
  وگرنه اگر (warn_cxx_compat && درخت_CODE (type) == ENUMERAL_TYPE)
    warning_at (loc2, OPT_Wc___compat,
		"C++ requires promoted type, not enum type, in %<va_arg%>");

  اگر (flag_isoc99 && درخت_CODE (type) == ARRAY_TYPE)
    {
      warning_at (loc2, 0, "second argument to %<va_arg%> is an array type %qT",
		  type);
      /* We create a trap but evaluate side effects first.  */
      درخت trapfn = builtin_decl_explicit (BUILT_IN_TRAP);
      trapfn = build_call_عبارت_loc (loc2, trapfn, 0);
      درخت e2 = build2 (COMPOUND_عبارت, void_type_گره, عبارت, trapfn);
      /* Return a compound literal of the right type.  */
      درخت e1 = build_compound_literal (loc2, type, پوچ, درست, 0, پوچ);
      عبارت = build2 (COMPOUND_عبارت, type, e2, e1);
    }
  وگرنه
    عبارت = build_va_arg (loc2, عبارت, type);

  اگر (type_عبارت)
    عبارت = build2 (COMPOUND_عبارت, درخت_TYPE (عبارت), type_عبارت, عبارت);

  بازگشت عبارت;
}

/* Return truthvalue of whether T1 is the same tree structure as T2.
   Return 1 if they are the same. Return false if they are different.  */

منطقی
c_درخت_equal (درخت t1, درخت t2)
{
  شمارش درخت_code code1, code2;

  اگر (t1 == t2)
    بازگشت درست;
  اگر (!t1 || !t2)
    بازگشت نادرست;

  برای (code1 = درخت_CODE (t1); code1 == NON_LVALUE_عبارت;
       code1 = درخت_CODE (t1))
    t1 = درخت_OPERAND (t1, 0);
  برای (code2 = درخت_CODE (t2); code2 == NON_LVALUE_عبارت;
       code2 = درخت_CODE (t2))
    t2 = درخت_OPERAND (t2, 0);

  /* They might have become equal now.  */
  اگر (t1 == t2)
    بازگشت درست;

  اگر (code1 != code2)
    بازگشت نادرست;

  اگر (CONSTANT_CLASS_P (t1) && !comptypes (درخت_TYPE (t1), درخت_TYPE (t2)))
    بازگشت نادرست;

  انتخاب (code1)
    {
    حالت INTEGER_CST:
      بازگشت wi::to_wide (t1) == wi::to_wide (t2);

    حالت REAL_CST:
      بازگشت real_equal (&درخت_REAL_CST (t1), &درخت_REAL_CST (t2));

    حالت STRING_CST:
      بازگشت درخت_STRING_LENGTH (t1) == درخت_STRING_LENGTH (t2)
	&& !memcmp (درخت_STRING_POINTER (t1), درخت_STRING_POINTER (t2),
		    درخت_STRING_LENGTH (t1));

    حالت FIXED_CST:
      بازگشت FIXED_مقادیر_IDENTICAL (درخت_FIXED_CST (t1),
				     درخت_FIXED_CST (t2));

    حالت COMPLEX_CST:
      بازگشت c_درخت_equal (درخت_REALPART (t1), درخت_REALPART (t2))
	     && c_درخت_equal (درخت_IMAGPART (t1), درخت_IMAGPART (t2));

    حالت VECTOR_CST:
      بازگشت operand_equal_p (t1, t2, OEP_ONLY_CONST);

    حالت CONSTRUCTOR:
      /* We need to do this when determining whether or not two
	 non-type pointer to member function template arguments
	 are the same.  */
      اگر (!comptypes (درخت_TYPE (t1), درخت_TYPE (t2))
	  || CONSTRUCTOR_NELTS (t1) != CONSTRUCTOR_NELTS (t2))
	بازگشت نادرست;
      {
	درخت field, مقدار;
	unsigned صحیح i;
	FOR_EACH_CONSTRUCTOR_ELT (CONSTRUCTOR_ELTS (t1), i, field, مقدار)
	  {
	    constructor_elt *elt2 = CONSTRUCTOR_ELT (t2, i);
	    اگر (!c_درخت_equal (field, elt2->index)
		|| !c_درخت_equal (مقدار, elt2->مقدار))
	      بازگشت نادرست;
	  }
      }
      بازگشت درست;

    حالت درخت_LIST:
      اگر (!c_درخت_equal (درخت_PURPOSE (t1), درخت_PURPOSE (t2)))
	بازگشت نادرست;
      اگر (!c_درخت_equal (درخت_مقدار (t1), درخت_مقدار (t2)))
	بازگشت نادرست;
      بازگشت c_درخت_equal (درخت_CHAIN (t1), درخت_CHAIN (t2));

    حالت SAVE_عبارت:
      بازگشت c_درخت_equal (درخت_OPERAND (t1, 0), درخت_OPERAND (t2, 0));

    حالت CALL_عبارت:
      {
	درخت arg1, arg2;
	call_عبارت_arg_iterator iter1, iter2;
	اگر (!c_درخت_equal (CALL_عبارت_FN (t1), CALL_عبارت_FN (t2)))
	  بازگشت نادرست;
	برای (arg1 = first_call_عبارت_arg (t1, &iter1),
	       arg2 = first_call_عبارت_arg (t2, &iter2);
	     arg1 && arg2;
	     arg1 = next_call_عبارت_arg (&iter1),
	       arg2 = next_call_عبارت_arg (&iter2))
	  اگر (!c_درخت_equal (arg1, arg2))
	    بازگشت نادرست;
	اگر (arg1 || arg2)
	  بازگشت نادرست;
	بازگشت درست;
      }

    حالت TARGET_عبارت:
      {
	درخت o1 = درخت_OPERAND (t1, 0);
	درخت o2 = درخت_OPERAND (t2, 0);

	/* Special case: if either target is an unallocated VAR_DECL,
	   it means that it's going to be unified with whatever the
	   TARGET_EXPR is really supposed to initialize, so treat it
	   as being equivalent to anything.  */
	اگر (VAR_P (o1) && DECL_NAME (o1) == NULL_درخت
	    && !DECL_RTL_SET_P (o1))
	  /*Nop*/;
	وگرنه اگر (VAR_P (o2) && DECL_NAME (o2) == NULL_درخت
		 && !DECL_RTL_SET_P (o2))
	  /*Nop*/;
	وگرنه اگر (!c_درخت_equal (o1, o2))
	  بازگشت نادرست;

	بازگشت c_درخت_equal (درخت_OPERAND (t1, 1), درخت_OPERAND (t2, 1));
      }

    حالت COMPONENT_REF:
      اگر (درخت_OPERAND (t1, 1) != درخت_OPERAND (t2, 1))
	بازگشت نادرست;
      بازگشت c_درخت_equal (درخت_OPERAND (t1, 0), درخت_OPERAND (t2, 0));

    حالت PARM_DECL:
    حالت VAR_DECL:
    حالت CONST_DECL:
    حالت FIELD_DECL:
    حالت FUNCTION_DECL:
    حالت IDENTIFIER_گره:
    حالت SSA_NAME:
      بازگشت نادرست;

    حالت درخت_VEC:
      {
	unsigned ix;
	اگر (درخت_VEC_LENGTH (t1) != درخت_VEC_LENGTH (t2))
	  بازگشت نادرست;
	برای (ix = درخت_VEC_LENGTH (t1); ix--;)
	  اگر (!c_درخت_equal (درخت_VEC_ELT (t1, ix),
			     درخت_VEC_ELT (t2, ix)))
	    بازگشت نادرست;
	بازگشت درست;
      }

    CASE_CONVERT:
      اگر (!comptypes (درخت_TYPE (t1), درخت_TYPE (t2)))
	بازگشت نادرست;
      بشکن;

    پیشفرض:
      بشکن;
    }

  انتخاب (درخت_CODE_CLASS (code1))
    {
    حالت tcc_unary:
    حالت tcc_دودویی:
    حالت tcc_comparison:
    حالت tcc_expression:
    حالت tcc_vl_exp:
    حالت tcc_reference:
    حالت tcc_statement:
      {
	صحیح i, n = درخت_OPERAND_LENGTH (t1);

	انتخاب (code1)
	  {
	  حالت PREINCREMENT_عبارت:
	  حالت PREDECREMENT_عبارت:
	  حالت POSTINCREMENT_عبارت:
	  حالت POSTDECREMENT_عبارت:
	    n = 1;
	    بشکن;
	  حالت ARRAY_REF:
	    n = 2;
	    بشکن;
	  پیشفرض:
	    بشکن;
	  }

	اگر (درخت_CODE_CLASS (code1) == tcc_vl_exp
	    && n != درخت_OPERAND_LENGTH (t2))
	  بازگشت نادرست;

	برای (i = 0; i < n; ++i)
	  اگر (!c_درخت_equal (درخت_OPERAND (t1, i), درخت_OPERAND (t2, i)))
	    بازگشت نادرست;

	بازگشت درست;
      }

    حالت tcc_type:
      بازگشت comptypes (t1, t2);
    پیشفرض:
      gcc_unreachable ();
    }
}

/* Returns true when the function declaration FNDECL is implicit,
   introduced as a result of a call to an otherwise undeclared
   function, and false otherwise.  */

منطقی
c_decl_implicit (const_درخت fndecl)
{
  بازگشت C_DECL_IMPLICIT (fndecl);
}
