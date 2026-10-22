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

#அந்தர்பாவ "config.h"
#அந்தர்பாவ "system.h"
#அந்தர்பாவ "coretypes.h"
#அந்தர்பாவ "memmodel.h"
#அந்தர்பாவ "target.h"
#அந்தர்பாவ "function.h"
#அந்தர்பாவ "bitmap.h"
#அந்தர்பாவ "c-tree.h"
#அந்தர்பாவ "gimple-expr.h"
#அந்தர்பாவ "predict.h"
#அந்தர்பாவ "stor-layout.h"
#அந்தர்பாவ "trans-mem.h"
#அந்தர்பாவ "varasm.h"
#அந்தர்பாவ "stmt.h"
#அந்தர்பாவ "langhooks.h"
#அந்தர்பாவ "c-lang.h"
#அந்தர்பாவ "intl.h"
#அந்தர்பாவ "tree-iterator.h"
#அந்தர்பாவ "gimplify.h"
#அந்தர்பாவ "tree-inline.h"
#அந்தர்பாவ "omp-general.h"
#அந்தர்பாவ "c-family/c-objc.h"
#அந்தர்பாவ "c-family/c-ubsan.h"
#அந்தர்பாவ "gomp-constants.h"
#அந்தர்பாவ "spellcheck-tree.h"
#அந்தர்பாவ "c-family/c-type-mismatch.h"
#அந்தர்பாவ "stringpool.h"
#அந்தர்பாவ "attribs.h"
#அந்தர்பாவ "asan.h"
#அந்தர்பாவ "realmpfr.h"
#அந்தர்பாவ "tree-pretty-print-markup.h"
#அந்தர்பாவ "gcc-urlifier.h"

/* Possible cases of implicit conversions.  Used to select diagnostic messages
   and control folding initializers in convert_for_assignment.  */
எண்ணிக்கை impl_conv {
  ic_argpass,
  ic_assign,
  ic_init,
  ic_init_const,
  ic_return
};

/* The level of nesting inside "__alignof__".  */
முழு in_alignof;

/* The level of nesting inside "sizeof".  */
முழு in_sizeof;

/* The level of nesting inside "countof".  */
முழு in_countof;

/* The level of nesting inside "typeof".  */
முழு in_typeof;

/* The level of nesting inside "_Generic".  */
முழு in_generic;

/* True when parsing OpenMP loop expressions.  */
தருக்க c_in_omp_for;

/* True when parsing OpenMP map clause.  */
தருக்க c_omp_array_section_p;

/* The argument of last parsed sizeof expression, only to be tested
   if expr.original_code == SIZEOF_EXPR.  */
மரம் c_last_sizeof_arg;
location_t c_last_sizeof_loc;

/* Nonzero if we might need to print a "missing braces around
   initializer" message within this initializer.  */
நிலையான முழு found_missing_braces;

நிலையான தருக்க require_constant_மதிப்பு;
நிலையான தருக்க require_constant_elements;
நிலையான தருக்க require_constexpr_மதிப்பு;

நிலையான மரம் qualify_type (மரம், மரம்);
கட்டமைப்பு comptypes_data;
நிலையான தருக்க tagged_types_tu_compatible_p (const_மரம், const_மரம்,
					  கட்டமைப்பு comptypes_data *);
நிலையான தருக்க comp_target_types (location_t, மரம், மரம்);
நிலையான தருக்க function_types_compatible_p (const_மரம், const_மரம்,
					 கட்டமைப்பு comptypes_data *);
நிலையான தருக்க type_lists_compatible_p (const_மரம், const_மரம்,
				     கட்டமைப்பு comptypes_data *);
நிலையான முழு convert_arguments (location_t, vec<location_t>, மரம்,
			      vec<மரம், va_gc> *, vec<மரம், va_gc> *, மரம்,
			      மரம்);
நிலையான மரம் pointer_diff (location_t, மரம், மரம், மரம் *);
நிலையான மரம் convert_for_assignment (location_t, location_t, மரம், மரம், மரம்,
				    எண்ணிக்கை impl_conv, தருக்க, மரம், மரம், முழு,
				    முழு = 0);
நிலையான மரம் valid_compound_கோவை_initializer (மரம், மரம்);
நிலையான வெறுமை தள்ளு_string (மாறிலி எழுத்து *);
நிலையான வெறுமை தள்ளு_member_name (மரம்);
நிலையான முழு spelling_length (வெறுமை);
நிலையான எழுத்து *print_spelling (எழுத்து *);
நிலையான வெறுமை warning_init (location_t, முழு, மாறிலி எழுத்து *);
நிலையான மரம் digest_init (location_t, மரம், மரம், மரம், மரம், தருக்க, தருக்க, தருக்க,
			 தருக்க, தருக்க, தருக்க);
நிலையான வெறுமை output_init_element (location_t, மரம், மரம், தருக்க, மரம், மரம், தருக்க,
				 தருக்க, கட்டமைப்பு obstack *);
நிலையான வெறுமை output_pending_init_elements (முழு, கட்டமைப்பு obstack *);
நிலையான தருக்க set_designator (location_t, தருக்க, கட்டமைப்பு obstack *);
நிலையான வெறுமை தள்ளு_range_அடுக்கு (மரம், கட்டமைப்பு obstack *);
நிலையான வெறுமை add_pending_init (location_t, மரம், மரம், மரம், தருக்க,
			      கட்டமைப்பு obstack *);
நிலையான வெறுமை set_nonincremental_init (கட்டமைப்பு obstack *);
நிலையான வெறுமை set_nonincremental_init_from_string (மரம், கட்டமைப்பு obstack *);
நிலையான மரம் find_init_member (மரம், கட்டமைப்பு obstack *);
நிலையான வெறுமை readonly_warning (மரம், எண்ணிக்கை lvalue_use);
நிலையான முழு lvalue_or_else (location_t, const_மரம், எண்ணிக்கை lvalue_use);
நிலையான வெறுமை record_maybe_used_decl (மரம், தருக்க address);
நிலையான தருக்க comptypes_internal (const_மரம், const_மரம்,
				கட்டமைப்பு comptypes_data *data);
நிலையான தருக்க comptypes_check_for_composite (மரம் t1, மரம் t2);
நிலையான தருக்க handle_counted_by_p (மரம்);
நிலையான தருக்க உச்சி_array_vla_p (const_மரம் type);


/* Return true if EXP is a null pointer constant, false otherwise.  */

தருக்க
null_pointer_constant_p (const_மரம் கோவை)
{
  /* This should really operate on c_expr structures, but they aren't
     yet available everywhere required.  */
  மரம் type = மரம்_TYPE (கோவை);

  /* An integer constant expression with the value 0, such an expression
     cast to type void*, or the predefined constant nullptr, are a null
     pointer constant.  */
  எனில் (கோவை == nullptr_முனை)
    திரும்பு உண்மை;

  திரும்பு (மரம்_CODE (கோவை) == INTEGER_CST
	  && !மரம்_OVERFLOW (கோவை)
	  && integer_zerop (கோவை)
	  && (INTEGRAL_TYPE_P (type)
	      || (மரம்_CODE (type) == POINTER_TYPE
		  && VOID_TYPE_P (மரம்_TYPE (type))
		  && TYPE_QUALS (மரம்_TYPE (type)) == TYPE_UNQUALIFIED)));
}

/* EXPR may appear in an unevaluated part of an integer constant
   expression, but not in an evaluated part.  Wrap it in a
   C_MAYBE_CONST_EXPR, or mark it with TREE_OVERFLOW if it is just an
   INTEGER_CST and we cannot create a C_MAYBE_CONST_EXPR.  */

நிலையான மரம்
note_integer_operands (மரம் கோவை)
{
  மரம் ret;
  எனில் (மரம்_CODE (கோவை) == INTEGER_CST && in_late_இருமம்_op)
    {
      ret = copy_முனை (கோவை);
      மரம்_OVERFLOW (ret) = 1;
    }
  இல்லையெனில்
    {
      ret = build2 (C_MAYBE_CONST_கோவை, மரம்_TYPE (கோவை), NULL_மரம், கோவை);
      C_MAYBE_CONST_கோவை_INT_OPERANDS (ret) = 1;
    }
  திரும்பு ret;
}

/* Having checked whether EXPR may appear in an unevaluated part of an
   integer constant expression and found that it may, remove any
   C_MAYBE_CONST_EXPR noting this fact and return the resulting
   expression.  */

நிலையான உள்வரி மரம்
remove_c_maybe_const_கோவை (மரம் கோவை)
{
  எனில் (மரம்_CODE (கோவை) == C_MAYBE_CONST_கோவை)
    திரும்பு C_MAYBE_CONST_கோவை_கோவை (கோவை);
  இல்லையெனில்
    திரும்பு கோவை;
}

/* This is a cache to hold if two types are seen.  */

கட்டமைப்பு tagged_tu_seen_cache {
  மாறிலி கட்டமைப்பு tagged_tu_seen_cache * next;
  const_மரம் t1;
  const_மரம் t2;
};

/* Do `exp = require_complete_type (loc, exp);' to make sure exp
   does not have an incomplete type.  (That includes void types.)
   LOC is the location of the use.  */

மரம்
require_complete_type (location_t loc, மரம் மதிப்பு)
{
  மரம் type = மரம்_TYPE (மதிப்பு);

  எனில் (error_operand_p (மதிப்பு))
    திரும்பு error_mark_முனை;

  /* First, detect a valid value with a complete type.  */
  எனில் (COMPLETE_TYPE_P (type))
    திரும்பு மதிப்பு;

  c_incomplete_type_error (loc, மதிப்பு, type);
  திரும்பு error_mark_முனை;
}

/* Print an error message for invalid use of an incomplete type.
   VALUE is the expression that was used (or 0 if that isn't known)
   and TYPE is the type that was invalid.  LOC is the location for
   the error.  */

வெறுமை
c_incomplete_type_error (location_t loc, const_மரம் மதிப்பு, const_மரம் type)
{
  /* Avoid duplicate error message.  */
  எனில் (மரம்_CODE (type) == ERROR_MARK)
    திரும்பு;

  எனில் (மதிப்பு != NULL_மரம் && (VAR_P (மதிப்பு) || மரம்_CODE (மதிப்பு) == PARM_DECL))
    error_at (loc, "%qD has an incomplete type %qT", மதிப்பு, type);
  இல்லையெனில்
    {
    retry:
      /* We must print an error message.  Be clever about what it says.  */

      தேர்வு (மரம்_CODE (type))
	{
	நிலை RECORD_TYPE:
	நிலை UNION_TYPE:
	நிலை ENUMERAL_TYPE:
	  நிறுத்து;

	நிலை VOID_TYPE:
	  error_at (loc, "invalid use of void expression");
	  திரும்பு;

	நிலை ARRAY_TYPE:
	  எனில் (TYPE_DOMAIN (type))
	    {
	      எனில் (flexible_array_member_type_p (type))
		{
		  error_at (loc, "invalid use of flexible array member");
		  திரும்பு;
		}
	      type = மரம்_TYPE (type);
	      செல் retry;
	    }
	  error_at (loc, "invalid use of array with unspecified bounds");
	  திரும்பு;

	இயல்பு:
	  gcc_unreachable ();
	}

      எனில் (மரம்_CODE (TYPE_NAME (type)) == IDENTIFIER_முனை)
	error_at (loc, "invalid use of undefined type %qT", type);
      இல்லையெனில்
	/* If this type has a typedef-name, the TYPE_NAME is a TYPE_DECL.  */
	error_at (loc, "invalid use of incomplete typedef %qT", type);
    }
}

/* Given a type, apply default promotions wrt unnamed function
   arguments and return the new type.  */

மரம்
c_type_promotes_to (மரம் type)
{
  மரம் ret = NULL_மரம்;

  எனில் (TYPE_MAIN_VARIANT (type) == float_type_முனை)
    ret = double_type_முனை;
  இல்லையெனில் எனில் (c_promoting_integer_type_p (type))
    {
      /* Preserve unsignedness if not really getting any wider.  */
      எனில் (TYPE_UNSIGNED (type)
	  && (TYPE_PRECISION (type) == TYPE_PRECISION (integer_type_முனை)))
	ret = unsigned_type_முனை;
      இல்லையெனில்
	ret = integer_type_முனை;
    }

  எனில் (ret != NULL_மரம்)
    திரும்பு (TYPE_ATOMIC (type)
	    ? c_build_qualified_type (ret, TYPE_QUAL_ATOMIC)
	    : ret);

  திரும்பு type;
}

/* Return true if between two named address spaces, whether there is a superset
   named address space that encompasses both address spaces.  If there is a
   superset, return which address space is the superset.  */

நிலையான தருக்க
addr_space_superset (addr_space_t as1, addr_space_t as2, addr_space_t *common)
{
  எனில் (as1 == as2)
    {
      *common = as1;
      திரும்பு உண்மை;
    }
  இல்லையெனில் எனில் (targetm.addr_space.subset_p (as1, as2))
    {
      *common = as2;
      திரும்பு உண்மை;
    }
  இல்லையெனில் எனில் (targetm.addr_space.subset_p (as2, as1))
    {
      *common = as1;
      திரும்பு உண்மை;
    }
  இல்லையெனில்
    திரும்பு பொய்;
}

/* Return a variant of TYPE which has all the type qualifiers of LIKE
   as well as those of TYPE.  */

நிலையான மரம்
qualify_type (மரம் type, மரம் like)
{
  addr_space_t as_type = TYPE_ADDR_SPACE (type);
  addr_space_t as_like = TYPE_ADDR_SPACE (like);
  addr_space_t as_common;

  /* If the two named address spaces are different, determine the common
     superset address space.  If there isn't one, raise an error.  */
  எனில் (!addr_space_superset (as_type, as_like, &as_common))
    {
      as_common = as_type;
      error ("%qT and %qT are in disjoint named address spaces",
	     type, like);
    }

  திரும்பு c_build_qualified_type (type,
				 TYPE_QUALS_NO_ADDR_SPACE (type)
				 | TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (like)
				 | ENCODE_QUAL_ADDR_SPACE (as_common));
}


/* Check consistency of type TYPE.  For derived types, we test that
   C_TYPE_VARIABLE_SIZE and C_TYPE_VARIABLY_MODIFIED are consistent with
   the requirements of the base type.  We also check that arrays with a
   non-constant length are marked with C_TYPE_VARIABLE_SIZE. If any
   inconsistency is detected false is returned and true otherwise.  */

நிலையான தருக்க
c_verify_type (மரம் type)
{
  தேர்வு (மரம்_CODE (type))
    {
    நிலை POINTER_TYPE:
    நிலை FUNCTION_TYPE:
    நிலை ARRAY_TYPE:
      /* Pointer, array, functions are variably modified if and only if the
	 target, element, return type is variably modified.  */
      எனில் (!TYPE_STRUCTURAL_EQUALITY_P (type)
	  && (C_TYPE_VARIABLY_MODIFIED (type)
	      != C_TYPE_VARIABLY_MODIFIED (மரம்_TYPE (type))))
	திரும்பு பொய்;
      /* If the target type is structural equality, the type should also. */
      எனில் (!TYPE_STRUCTURAL_EQUALITY_P (type)
	  && TYPE_STRUCTURAL_EQUALITY_P (மரம்_TYPE (type)))
	திரும்பு பொய்;
    இயல்பு:
       நிறுத்து;
    }

  தேர்வு (மரம்_CODE (type))
    {
    நிலை POINTER_TYPE:
    நிலை FUNCTION_TYPE:
      /* Pointer and functions can not have variable size.  */
      எனில் (C_TYPE_VARIABLE_SIZE (type))
	திரும்பு பொய்;
      நிறுத்து;
    நிலை ARRAY_TYPE:
      /* An array has variable size if and only if it has a non-constant
	 dimensions or its element type has variable size.  */
      எனில் ((C_TYPE_VARIABLE_SIZE (மரம்_TYPE (type))
	   || உச்சி_array_vla_p (type))
	  != C_TYPE_VARIABLE_SIZE (type))
	திரும்பு பொய்;
      /* If the element type or the array has variable size, then the
	 array has variable size and is variably modified.  */
      எனில் (C_TYPE_VARIABLE_SIZE (மரம்_TYPE (type))
	  || C_TYPE_VARIABLE_SIZE (type))
	{
	  எனில் (!C_TYPE_VARIABLE_SIZE (type))
	    திரும்பு பொய்;
	  எனில் (!C_TYPE_VARIABLY_MODIFIED (type))
	    திரும்பு பொய்;
	}

      /* va_list violates this, accept such types here.  */
      எனில் (!COMPLETE_TYPE_P (மரம்_TYPE (type)))
	திரும்பு உண்மை;

      எனில் (COMPLETE_TYPE_P (type))
	{
	  /* If the size is unknown, it can not be complete.  */
	  எனில் (NULL_மரம் == TYPE_DOMAIN (type))
	    திரும்பு பொய்;

	  /* Zero-length arrays must have size zero.  */
	  எனில் (zero_length_array_type_p (type)
	      && !integer_zerop (TYPE_SIZE (type)))
	    திரும்பு பொய்;
	}
      இல்லையெனில்
	{
	  /* If not complete but has a domain, it must be a FAM.  */
	  எனில் (NULL_மரம் != TYPE_DOMAIN (type)
	      && !flexible_array_member_type_p (type))
	    திரும்பு பொய்;
	}
    இயல்பு:
      நிறுத்து;
    }
  திரும்பு உண்மை;
}

/* Propagate C_TYPE_VARIABLY_MODIFIED and C_TYPE_VARIABLE_SIZE
   from a base type to a newly built derived or qualified type.  */

நிலையான மரம்
c_set_type_bits (மரம் new_type, மரம் old_type)
{
  gcc_checking_assert (c_verify_type (old_type));

  எனில் (c_type_variably_modified_p (old_type))
    C_TYPE_VARIABLY_MODIFIED (new_type) = உண்மை;

  எனில் (மரம்_CODE (new_type) == ARRAY_TYPE && C_TYPE_VARIABLE_SIZE (old_type))
    {
      C_TYPE_VARIABLY_MODIFIED (new_type) = உண்மை;
      C_TYPE_VARIABLE_SIZE (new_type) = உண்மை;
    }
  திரும்பு new_type;
}

/* Build a pointer type using the default pointer mode.  */

மரம்
c_build_pointer_type (மரம் to_type)
{
  addr_space_t as = to_type == error_mark_முனை ? ADDR_SPACE_GENERIC
					       : TYPE_ADDR_SPACE (to_type);
  machine_mode pointer_mode;

  எனில் (as != ADDR_SPACE_GENERIC || c_default_pointer_mode == VOIDmode)
    pointer_mode = targetm.addr_space.pointer_mode (as);
  இல்லையெனில்
    pointer_mode = c_default_pointer_mode;

  திரும்பு c_build_pointer_type_for_mode (to_type, pointer_mode, பொய்);
}

/* Build a pointer type using the given mode.  */

மரம்
c_build_pointer_type_for_mode (மரம் type, machine_mode mode, தருக்க m)
{
  மரம் ret = build_pointer_type_for_mode (type, mode, m);
  திரும்பு c_set_type_bits (ret, type);
}

/* Build a function type.  */

மரம்
c_build_function_type (மரம் type, மரம் args, தருக்க no)
{
  மரம் ret = build_function_type (type, args, no);
  திரும்பு c_set_type_bits (ret, type);
}

/* Build an array type.  This sets typeless storage as required
   by C2Y and C_TYPE_VARIABLY_MODIFIED and C_TYPE_VARIABLE_SIZE
   based on the element type and domain.  */

மரம்
c_build_array_type (மரம் type, மரம் domain)
{
  முழு type_quals = TYPE_QUALS (type);

  /* Identify typeless storage as introduced in C2Y
     and supported also in earlier language modes.  */
  தருக்க typeless = (char_type_p (type) && !(type_quals & TYPE_QUAL_ATOMIC))
		  || (AGGREGATE_TYPE_P (type) && TYPE_TYPELESS_STORAGE (type));

  மரம் ret = build_array_type (type, domain, typeless);

  எனில் (உச்சி_array_vla_p (ret))
    {
      C_TYPE_VARIABLE_SIZE (ret) = 1;
      C_TYPE_VARIABLY_MODIFIED (ret) = 1;
    }

  திரும்பு c_set_type_bits (ret, type);
}

/* Build an array type of unspecified size.  */
மரம்
c_build_array_type_unspecified (மரம் type)
{
  மரம் upper = build2 (COMPOUND_கோவை, மரம்_TYPE (size_zero_முனை),
		       integer_zero_முனை, size_zero_முனை);
  திரும்பு c_build_array_type (type, build_index_type (upper));
}

/* Build an array type of zero size.  */
மரம்
c_build_array_type_zero_size (மரம் type)
{
  /* The GCC extension for zero-length arrays differs from
     ISO flexible array members in that sizeof yields
     zero.  */
  type = c_build_array_type (type, build_index_type (NULL_மரம்));
  type = build_distinct_type_copy (TYPE_MAIN_VARIANT (type));
  TYPE_SIZE (type) = bitsize_zero_முனை;
  TYPE_SIZE_UNIT (type) = size_zero_முனை;
  SET_TYPE_STRUCTURAL_EQUALITY (type);
  திரும்பு type;
}

மரம்
c_build_type_attribute_qual_variant (மரம் type, மரம் attrs, முழு quals)
{
  மரம் ret = build_type_attribute_qual_variant (type, attrs, quals);
  திரும்பு c_set_type_bits (ret, type);
}

மரம்
c_build_type_attribute_variant (மரம் type, மரம் attrs)
{
  திரும்பு c_build_type_attribute_qual_variant (type, attrs, TYPE_QUALS (type));
}

/* Reconstruct a complex derived type.  This is used to re-construct types
   with the vector attribute.  It is called via a langhook.  */

மரம்
c_reconstruct_complex_type (மரம் type, மரம் bottom)
{
  மரம் inner, outer;

  எனில் (மரம்_CODE (type) == POINTER_TYPE)
    {
      inner = c_reconstruct_complex_type (மரம்_TYPE (type), bottom);
      outer = c_build_pointer_type_for_mode (inner, TYPE_MODE (type),
					     TYPE_REF_CAN_ALIAS_ALL (type));
    }
  இல்லையெனில் எனில் (மரம்_CODE (type) == ARRAY_TYPE)
    {
      தருக்க rso = TYPE_REVERSE_STORAGE_ORDER (type);
      inner = c_reconstruct_complex_type (மரம்_TYPE (type), bottom);
      outer = c_build_array_type (inner, TYPE_DOMAIN (type));
      எனில் (rso)
	{
	  outer = build_distinct_type_copy (outer);
	  TYPE_REVERSE_STORAGE_ORDER (outer) = 1;
	}

      gcc_checking_assert (C_TYPE_VARIABLE_SIZE (type)
			   == C_TYPE_VARIABLE_SIZE (outer));
    }
  இல்லையெனில் எனில் (மரம்_CODE (type) == FUNCTION_TYPE)
    {
      inner = c_reconstruct_complex_type (மரம்_TYPE (type), bottom);
      outer = c_build_function_type (inner, TYPE_ARG_TYPES (type),
				     TYPE_NO_NAMED_ARGS_STDARG_P (type));
    }
  இல்லையெனில் எனில் (மரம்_CODE (type) == REFERENCE_TYPE
	   || மரம்_CODE (type) == OFFSET_TYPE)
    gcc_unreachable ();
  இல்லையெனில்
    திரும்பு bottom;

  திரும்பு c_build_type_attribute_qual_variant (outer, TYPE_ATTRIBUTES (type),
					      TYPE_QUALS (type));
}


/* Helper function for c_canonical_type.  Check whether FIELD
   contains a pointer to a structure or union with tag,
   possibly nested in other type derivations, and return the
   type of this nested structure or union.  */
நிலையான மரம்
ptr_to_tagged_member (மரம் field)
{
  gcc_assert (FIELD_DECL == மரம்_CODE (field));
  மரம் type = மரம்_TYPE (field);
  தருக்க ptr_seen = பொய்;
  போது (மரம்_CODE (type) == ARRAY_TYPE
	 || மரம்_CODE (type) == FUNCTION_TYPE
	 || மரம்_CODE (type) == POINTER_TYPE)
    {
      எனில் (மரம்_CODE (type) == POINTER_TYPE)
	ptr_seen = உண்மை;
      type = மரம்_TYPE (type);
    }

  எனில் (ptr_seen
      && RECORD_OR_UNION_TYPE_P (type)
      && NULL_மரம் != c_type_tag (type))
    திரும்பு type;

  திரும்பு NULL_மரம்;
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
மரம்
c_type_canonical (மரம் type)
{
  gcc_assert (RECORD_OR_UNION_TYPE_P (type));

  தருக்க needs_mod = பொய்;
  க்கு (மரம் x = TYPE_FIELDS (type); x; x = DECL_CHAIN (x))
    {
      எனில் (!ptr_to_tagged_member (x))
	தொடர்;
      needs_mod = உண்மை;
      நிறுத்து;
    }
  எனில் (!needs_mod)
    திரும்பு type;

  /* Construct new version with such members replaced.  */
  மரம் n = build_distinct_type_copy (type);
  மரம் *fields = &TYPE_FIELDS (n);
  க்கு (மரம் x = TYPE_FIELDS (type); x; x = DECL_CHAIN (x))
    {
      மரம் f = copy_முனை (x);
      எனில் (மரம் m = ptr_to_tagged_member (x))
	{
	  மரம் new_முனை = make_முனை (மரம்_CODE (m));
	  TYPE_NAME (new_முனை) = TYPE_NAME (m);
	  SET_TYPE_STRUCTURAL_EQUALITY (new_முனை);
	  new_முனை = qualify_type (new_முனை, m);
	  மரம்_TYPE (f) = c_reconstruct_complex_type (மரம்_TYPE (x),
						      new_முனை);
	}
      *fields = f;
      fields = &DECL_CHAIN (f);
    }
  TYPE_CANONICAL (n) = n;
  திரும்பு n;
}


/* If NTYPE is a type of a non-variadic function with a prototype
   and OTYPE is a type of a function without a prototype and ATTRS
   contains attribute format, diagnosess and removes it from ATTRS.
   Returns the result of build_type_attribute_variant of NTYPE and
   the (possibly) modified ATTRS.  */

நிலையான மரம்
c_build_functype_attribute_variant (மரம் ntype, மரம் otype, மரம் attrs)
{
  எனில் (!prototype_p (otype)
      && prototype_p (ntype)
      && lookup_attribute ("format", attrs))
    {
      warning_at (உள்ளீடு_location, OPT_Wattributes,
		  "%qs attribute can only be applied to variadic functions",
		  "format");
      attrs = remove_attribute ("format", attrs);
    }
  திரும்பு c_build_type_attribute_variant (ntype, attrs);

}

/* Given a type which could be a typedef name, make sure to return the
   original type.  See set_underlying_type. */
நிலையான const_மரம்
c_type_original (const_மரம் t)
{
  /* It may even be a typedef of a typedef...
     In the case of compiler-created builtin structs the TYPE_DECL
     may be a dummy, with no DECL_ORIGINAL_TYPE.  Don't fault.  */
  போது (TYPE_NAME (t)
	 && மரம்_CODE (TYPE_NAME (t)) == TYPE_DECL
	 && DECL_ORIGINAL_TYPE (TYPE_NAME (t)))
    t = DECL_ORIGINAL_TYPE (TYPE_NAME (t));
  திரும்பு t;
}

/* Return the tag for a tagged type.  */
மரம்
c_type_tag (const_மரம் t)
{
  gcc_assert (RECORD_OR_UNION_TYPE_P (t) || மரம்_CODE (t) == ENUMERAL_TYPE);
  const_மரம் orig = c_type_original (t);
  மரம் name = TYPE_NAME (orig);
  எனில் (!name)
    திரும்பு NULL_மரம்;
  எனில் (மரம்_CODE (name) == TYPE_DECL)
    {
      எனில் (!DECL_NAME (name))
	திரும்பு NULL_மரம்;
      name = DECL_NAME (name);
    }
  gcc_checking_assert (மரம்_CODE (name) == IDENTIFIER_முனை);
  திரும்பு name;
}

/* Remove qualifiers but not atomic.  For arrays remove qualifiers
   on the element type but also do not remove atomic.  */
நிலையான மரம்
remove_qualifiers (மரம் t)
{
  எனில் (!t || t == error_mark_முனை)
    திரும்பு t;
  திரும்பு TYPE_ATOMIC (strip_array_types (t))
	 ? c_build_qualified_type (TYPE_MAIN_VARIANT (t), TYPE_QUAL_ATOMIC)
	 : TYPE_MAIN_VARIANT (t);
}


/* Helper function for composite_type_internal.  Find a compatible type
   in a (transparent) union U compatible to T.  If found, return the
   type of the corresponding member.  Otherwise, return the union type U.  */
நிலையான மரம்
transparent_union_replacement (மரம் u, மரம் t)
{
  எனில் (u == error_mark_முனை || t == error_mark_முனை
      || மரம்_CODE (u) != UNION_TYPE
      || !(TYPE_TRANSPARENT_AGGR (u) || TYPE_NAME (u) == NULL_மரம்)
      || comptypes (u, t))
    திரும்பு u;

  க்கு (மரம் memb = TYPE_FIELDS (u); memb; memb = DECL_CHAIN (memb))
    {
      மரம் m = remove_qualifiers (மரம்_TYPE (memb));
      எனில் (comptypes (m, t))
	{
	  pedwarn (உள்ளீடு_location, OPT_Wpedantic,
		    "function types not truly compatible in ISO C");
	  திரும்பு m;
	}
    }

  திரும்பு u;
}



/* Return the composite type of two compatible types.

   We assume that comptypes has already been done and returned
   nonzero; if that isn't so, this may crash.  In particular, we
   assume that qualifiers match.  */

கட்டமைப்பு composite_cache {
  மரம் t1;
  மரம் t2;
  மரம் composite;
  கட்டமைப்பு composite_cache* next;
};

மரம்
composite_type_internal (மரம் t1, மரம் t2, மரம் cond,
			 கட்டமைப்பு composite_cache* cache)
{
  எண்ணிக்கை மரம்_code code1;
  எண்ணிக்கை மரம்_code code2;
  மரம் attributes;

  /* Save time if the two types are the same.  */

  எனில் (t1 == t2) திரும்பு t1;

  /* If one type is nonsense, use the other.  */
  எனில் (t1 == error_mark_முனை)
    திரும்பு t2;
  எனில் (t2 == error_mark_முனை)
    திரும்பு t1;

  code1 = மரம்_CODE (t1);
  code2 = மரம்_CODE (t2);

  /* Merge the attributes.  */
  attributes = targetm.merge_type_attributes (t1, t2);

  /* If one is an enumerated type and the other is the compatible
     integer type, the composite type might be either of the two
     (DR#013 question 3).  For consistency, use the enumerated type as
     the composite type.  */

  எனில் (code1 == ENUMERAL_TYPE
      && (code2 == INTEGER_TYPE
	  || code2 == BOOLEAN_TYPE))
    திரும்பு t1;
  எனில் (code2 == ENUMERAL_TYPE
      && (code1 == INTEGER_TYPE
	  || code1 == BOOLEAN_TYPE))
    திரும்பு t2;

  gcc_assert (code1 == code2);

  தேர்வு (code1)
    {
    நிலை POINTER_TYPE:
      /* For two pointers, do this recursively on the target type.  */
      {
	gcc_checking_assert (TYPE_QUALS (t1) == TYPE_QUALS (t2));
	மரம் target = composite_type_internal (மரம்_TYPE (t1), மரம்_TYPE (t2),
					       cond, cache);
	மரம் n = c_build_pointer_type_for_mode (target, TYPE_MODE (t1), பொய்);
	திரும்பு c_build_type_attribute_qual_variant (n, attributes,
						    TYPE_QUALS (t2));
      }

    நிலை ARRAY_TYPE:
      {
	மரம் d1 = TYPE_DOMAIN (t1);
	மரம் d2 = TYPE_DOMAIN (t2);

	/* We should not have any type quals on arrays at all.  */
	gcc_assert (!TYPE_QUALS_NO_ADDR_SPACE (t1)
		    && !TYPE_QUALS_NO_ADDR_SPACE (t2));

	தருக்க d1_zero = zero_length_array_type_p (t1)
		       || flexible_array_member_type_p (t1);
	தருக்க d2_zero = zero_length_array_type_p (t2)
		       || flexible_array_member_type_p (t2);

	தருக்க d1_variable = உச்சி_array_vla_p (t1);
	தருக்க d2_variable = உச்சி_array_vla_p (t2);

	தருக்க use1 = d1 && (d2_variable || !d2 || d2_zero || !d1_variable);
	தருக்க use2 = d2 && (d1_variable || !d1 || d1_zero || !d2_variable);

	/* If the first is an unspecified size pick the other one.  */
	எனில் (d2_variable && c_type_unspecified_p (t1))
	  {
	    gcc_assert (use1 && use2);
	    use1 = பொய்;
	  }

	/* If both are VLAs but not unspecified and we are in the
	   conditional operator, we create a conditional to select
	   the size of the active branch.  */
	தருக்க use0 = cond && d1_variable && !c_type_unspecified_p (t1)
			 && d2_variable && !c_type_unspecified_p (t2);

	மரம் td;
	மரம் elt = composite_type_internal (மரம்_TYPE (t1), மரம்_TYPE (t2),
					    cond, cache);

	எனில் (!use0)
	  {
	    /* Save space: see if the result is identical to one of the args.  */
	    எனில் (elt == மரம்_TYPE (t1) && use1)
	      திரும்பு c_build_type_attribute_variant (t1, attributes);
	    எனில் (elt == மரம்_TYPE (t2) && use2)
	      திரும்பு c_build_type_attribute_variant (t2, attributes);

	    எனில் (elt == மரம்_TYPE (t1) && !TYPE_DOMAIN (t2) && !TYPE_DOMAIN (t1))
	      திரும்பு c_build_type_attribute_variant (t1, attributes);
	    எனில் (elt == மரம்_TYPE (t2) && !TYPE_DOMAIN (t2) && !TYPE_DOMAIN (t1))
	      திரும்பு c_build_type_attribute_variant (t2, attributes);

	    td = TYPE_DOMAIN (use1 ? t1 : t2);
	  }
	இல்லையெனில்
	  {
	    /* Not used in C.  */
	    gcc_assert (size_zero_முனை == TYPE_MIN_மதிப்பு (d1));
	    gcc_assert (size_zero_முனை == TYPE_MIN_மதிப்பு (d2));

	    மரம் d = fold_build3_loc (UNKNOWN_LOCATION, COND_கோவை, sizetype,
				      cond, TYPE_MAX_மதிப்பு (d1),
				      TYPE_MAX_மதிப்பு (d2));

	    td = build_index_type (d);
	  }

	/* Merge the element types, and have a size if either arg has
	   one.  We may have qualifiers on the element types.  To set
	   up TYPE_MAIN_VARIANT correctly, we need to form the
	   composite of the unqualified types and add the qualifiers
	   back at the end.  */
	முழு quals = TYPE_QUALS (strip_array_types (elt));
	மரம் unqual_elt = c_build_qualified_type (elt, TYPE_UNQUALIFIED);

	எனில் ((!d1 || d1_zero) && (!d2 || d2_zero) && (d1 || d2))
	  t1 = c_build_array_type_zero_size (unqual_elt);
	இல்லையெனில்
	  t1 = c_build_array_type (unqual_elt, td);

	/* Check that a type which has a varying outermost dimension
	   got marked as having a variable size.  */
	தருக்க varsize = (d1_variable && d2_variable)
		       || (d1_variable && !d2)
		       || (d2_variable && !d1);
	gcc_checking_assert (!varsize || C_TYPE_VARIABLE_SIZE (t1));

	t1 = c_build_qualified_type (t1, quals);
	திரும்பு c_build_type_attribute_variant (t1, attributes);
      }

    நிலை RECORD_TYPE:
    நிலை UNION_TYPE:
      எனில் (flag_isoc23 && !comptypes_same_p (t1, t2))
	{
	  /* Go to the original type to get the right tag.  */
	  மரம் tag = c_type_tag (t1);

	  gcc_checking_assert (COMPLETE_TYPE_P (t1) && COMPLETE_TYPE_P (t2));
	  gcc_checking_assert (!tag || comptypes (t1, t2));

	  /* If a composite type for these two types is already under
	     construction, return it.  */

	  க்கு (கட்டமைப்பு composite_cache *c = cache; c != வெற்று; c = c->next)
	    எனில் ((c->t1 == t1 && c->t2 == t2) || (c->t1 == t2 && c->t2 == t1))
	       திரும்பு c->composite;

	  /* Otherwise, create a new type node and link it into the cache.  */

	  மரம் n = make_முனை (code1);
	  SET_TYPE_STRUCTURAL_EQUALITY (n);
	  TYPE_NAME (n) = tag;

	  கட்டமைப்பு composite_cache cache2 = { t1, t2, n, cache };
	  cache = &cache2;

	  மரம் f1 = TYPE_FIELDS (t1);
	  மரம் f2 = TYPE_FIELDS (t2);
	  மரம் fields = NULL_மரம்;

	  க்கு (மரம் a = f1, b = f2; a && b;
	       a = DECL_CHAIN (a), b = DECL_CHAIN (b))
	    {
	      மரம் ta = மரம்_TYPE (a);
	      மரம் tb = மரம்_TYPE (b);

	      எனில் (DECL_C_BIT_FIELD (a))
		{
		  ta = DECL_BIT_FIELD_TYPE (a);
		  tb = DECL_BIT_FIELD_TYPE (b);
		}

	      gcc_assert (DECL_NAME (a) == DECL_NAME (b));
	      gcc_checking_assert (!DECL_NAME (a) || comptypes (ta, tb));

	      மரம் t = composite_type_internal (ta, tb, cond, cache);
	      மரம் f = build_decl (உள்ளீடு_location, FIELD_DECL, DECL_NAME (a), t);

	      DECL_PACKED (f) = DECL_PACKED (a);
	      SET_DECL_ALIGN (f, DECL_ALIGN (a));
	      DECL_ATTRIBUTES (f) = DECL_ATTRIBUTES (a);
	      C_DECL_VARIABLE_SIZE (f) = C_TYPE_VARIABLE_SIZE (t);

	      decl_attributes (&f, DECL_ATTRIBUTES (f), 0);

	      finish_decl (f, உள்ளீடு_location, வெற்று, வெற்று, வெற்று);

	      எனில் (DECL_C_BIT_FIELD (a))
		{
		  /* This will be processed by finish_struct.  */
		  SET_DECL_C_BIT_FIELD (f);
		  DECL_INITIAL (f) = build_int_cst (integer_type_முனை,
						    மரம்_to_uhwi (DECL_SIZE (a)));
		  DECL_NONADDRESSABLE_P (f) = உண்மை;
		  DECL_PADDING_P (f) = !DECL_NAME (a);
		}

	      DECL_CHAIN (f) = fields;
	      fields = f;
	    }

	  fields = nreverse (fields);

	  /* Setup the struct/union type.  Because we inherit all variably
	     modified components, we can ignore the size expression.  */
	  மரம் கோவை = NULL_மரம்;

	  /* Set TYPE_STUB_DECL for debugging symbols.  */
	  TYPE_STUB_DECL (n) = pushdecl (build_decl (உள்ளீடு_location, TYPE_DECL,
						     NULL_மரம், n));

	  n = finish_struct (உள்ளீடு_location, n, fields, attributes, வெற்று,
			     &கோவை);

	  திரும்பு qualify_type (n, t1);
	}
      /* FALLTHRU */
    நிலை ENUMERAL_TYPE:
      எனில் (attributes != வெற்று)
	{
	  /* Try harder not to create a new aggregate type.  */
	  எனில் (attribute_list_equal (TYPE_ATTRIBUTES (t1), attributes))
	    திரும்பு t1;
	  எனில் (attribute_list_equal (TYPE_ATTRIBUTES (t2), attributes))
	    திரும்பு t2;
	}
      திரும்பு c_build_type_attribute_variant (t1, attributes);

    நிலை FUNCTION_TYPE:
      /* Function types: prefer the one that specified arg types.
	 If both do, merge the arg types.  Also merge the return types.  */
      {
	மரம் valtype = composite_type_internal (மரம்_TYPE (t1), மரம்_TYPE (t2),
						cond, cache);
	மரம் p1 = TYPE_ARG_TYPES (t1);
	மரம் p2 = TYPE_ARG_TYPES (t2);

	/* Save space: see if the result is identical to one of the args.  */
	எனில் (valtype == மரம்_TYPE (t1) && !TYPE_ARG_TYPES (t2))
	  திரும்பு c_build_functype_attribute_variant (t1, t2, attributes);
	எனில் (valtype == மரம்_TYPE (t2) && !TYPE_ARG_TYPES (t1))
	  திரும்பு c_build_functype_attribute_variant (t2, t1, attributes);

	/* Simple way if one arg fails to specify argument types.  */
	எனில் (TYPE_ARG_TYPES (t1) == NULL_மரம்)
	  {
	    t1 = c_build_function_type (valtype, TYPE_ARG_TYPES (t2),
					TYPE_NO_NAMED_ARGS_STDARG_P (t2));
	    t1 = c_build_type_attribute_variant (t1, attributes);
	    திரும்பு qualify_type (t1, t2);
	 }
	எனில் (TYPE_ARG_TYPES (t2) == NULL_மரம்)
	  {
	    t1 = c_build_function_type (valtype, TYPE_ARG_TYPES (t1),
					TYPE_NO_NAMED_ARGS_STDARG_P (t1));
	    t1 = c_build_type_attribute_variant (t1, attributes);
	    திரும்பு qualify_type (t1, t2);
	  }

	/* If both args specify argument types, we must merge the two
	   lists, argument by argument.  */
	மரம் newargs = NULL_மரம்;
	மரம் *endp = &newargs;

	க்கு (; p1; p1 = மரம்_CHAIN (p1), p2 = மரம்_CHAIN (p2))
	  {
	    எனில் (p1 == void_list_முனை)
	      {
		*endp = void_list_முனை;
		நிறுத்து;
	      }
	    மரம் mv1 = remove_qualifiers (மரம்_மதிப்பு (p1));
	    மரம் mv2 = remove_qualifiers (மரம்_மதிப்பு (p2));

	    gcc_assert (mv1);
	    gcc_assert (mv2);

	    mv1 = transparent_union_replacement (mv1, mv2);
	    mv2 = transparent_union_replacement (mv2, mv1);

	    *endp = மரம்_cons (NULL_மரம்,
			       composite_type_internal (mv1, mv2, cond, cache),
			       NULL_மரம்);

	    endp = &மரம்_CHAIN (*endp);
	  }

	t1 = c_build_function_type (valtype, newargs);
	t1 = qualify_type (t1, t2);
      }
      /* FALLTHRU */

    இயல்பு:
      திரும்பு c_build_type_attribute_variant (t1, attributes);
    }
}

மரம்
composite_type_cond (மரம் t1, மரம் t2, மரம் cond)
{
  gcc_checking_assert (comptypes_check_for_composite (t1, t2));

  கட்டமைப்பு composite_cache cache = { };
  மரம் n = composite_type_internal (t1, t2, cond, &cache);

  gcc_checking_assert (comptypes_check_for_composite (n, t1));
  gcc_checking_assert (comptypes_check_for_composite (n, t2));
  திரும்பு n;
}


மரம்
composite_type (மரம் t1, மரம் t2)
{
  திரும்பு composite_type_cond (t1, t2, NULL_மரம்);
}

/* Return the type of a conditional expression between pointers to
   possibly differently qualified versions of compatible types.

   We assume that comp_target_types has already been done and returned
   true; if that isn't so, this may crash.  */

நிலையான மரம்
common_pointer_type (மரம் t1, மரம் t2, மரம் cond)
{
  மரம் attributes;
  unsigned target_quals;
  addr_space_t as1, as2, as_common;
  முழு quals1, quals2;

  /* Save time if the two types are the same.  */

  எனில் (t1 == t2) திரும்பு t1;

  /* If one type is nonsense, use the other.  */
  எனில் (t1 == error_mark_முனை)
    திரும்பு t2;
  எனில் (t2 == error_mark_முனை)
    திரும்பு t1;

  gcc_assert (மரம்_CODE (t1) == POINTER_TYPE
	      && மரம்_CODE (t2) == POINTER_TYPE);

  /* Merge the attributes.  */
  attributes = targetm.merge_type_attributes (t1, t2);

  /* Find the composite type of the target types, and combine the
     qualifiers of the two types' targets.  */
  மரம் pointed_to_1 = மரம்_TYPE (t1);
  மரம் pointed_to_2 = மரம்_TYPE (t2);
  மரம் target = composite_type_cond (TYPE_MAIN_VARIANT (pointed_to_1),
				     TYPE_MAIN_VARIANT (pointed_to_2), cond);

  /* Strip array types to get correct qualifier for pointers to arrays */
  quals1 = TYPE_QUALS_NO_ADDR_SPACE (strip_array_types (pointed_to_1));
  quals2 = TYPE_QUALS_NO_ADDR_SPACE (strip_array_types (pointed_to_2));

  /* For function types do not merge const qualifiers, but drop them
     if used inconsistently.  The middle-end uses these to mark const
     and noreturn functions.  */
  எனில் (மரம்_CODE (pointed_to_1) == FUNCTION_TYPE)
    target_quals = (quals1 & quals2);
  இல்லையெனில்
    target_quals = (quals1 | quals2);

  /* If the two named address spaces are different, determine the common
     superset address space.  This is guaranteed to exist due to the
     assumption that comp_target_type returned true.  */
  as1 = TYPE_ADDR_SPACE (pointed_to_1);
  as2 = TYPE_ADDR_SPACE (pointed_to_2);
  எனில் (!addr_space_superset (as1, as2, &as_common))
    gcc_unreachable ();

  target_quals |= ENCODE_QUAL_ADDR_SPACE (as_common);

  t1 = c_build_pointer_type (c_build_qualified_type (target, target_quals));
  திரும்பு c_build_type_attribute_variant (t1, attributes);
}

/* Return the common type for two arithmetic types under the usual
   arithmetic conversions.  The default conversions have already been
   applied, and enumerated types converted to their compatible integer
   types.  The resulting type is unqualified and has no attributes.

   This is the type for the result of most arithmetic operations
   if the operands have the given two types.  */

நிலையான மரம்
c_common_type (மரம் t1, மரம் t2)
{
  எண்ணிக்கை மரம்_code code1;
  எண்ணிக்கை மரம்_code code2;

  /* If one type is nonsense, use the other.  */
  எனில் (t1 == error_mark_முனை)
    திரும்பு t2;
  எனில் (t2 == error_mark_முனை)
    திரும்பு t1;

  எனில் (TYPE_QUALS (t1) != TYPE_UNQUALIFIED)
    t1 = TYPE_MAIN_VARIANT (t1);

  எனில் (TYPE_QUALS (t2) != TYPE_UNQUALIFIED)
    t2 = TYPE_MAIN_VARIANT (t2);

  எனில் (TYPE_ATTRIBUTES (t1) != NULL_மரம்)
    {
      மரம் attrs = affects_type_identity_attributes (TYPE_ATTRIBUTES (t1));
      t1 = c_build_type_attribute_variant (t1, attrs);
    }

  எனில் (TYPE_ATTRIBUTES (t2) != NULL_மரம்)
    {
      மரம் attrs = affects_type_identity_attributes (TYPE_ATTRIBUTES (t2));
      t2 = c_build_type_attribute_variant (t2, attrs);
    }

  /* Save time if the two types are the same.  */

  எனில் (t1 == t2) திரும்பு t1;

  code1 = மரம்_CODE (t1);
  code2 = மரம்_CODE (t2);

  gcc_assert (code1 == VECTOR_TYPE || code1 == COMPLEX_TYPE
	      || code1 == FIXED_POINT_TYPE || code1 == REAL_TYPE
	      || code1 == INTEGER_TYPE || code1 == BITINT_TYPE);
  gcc_assert (code2 == VECTOR_TYPE || code2 == COMPLEX_TYPE
	      || code2 == FIXED_POINT_TYPE || code2 == REAL_TYPE
	      || code2 == INTEGER_TYPE || code2 == BITINT_TYPE);

  /* When one operand is a decimal float type, the other operand cannot be
     a generic float type or a complex type.  We also disallow vector types
     here.  */
  எனில் ((DECIMAL_FLOAT_TYPE_P (t1) || DECIMAL_FLOAT_TYPE_P (t2))
      && !(DECIMAL_FLOAT_TYPE_P (t1) && DECIMAL_FLOAT_TYPE_P (t2)))
    {
      எனில் (code1 == VECTOR_TYPE || code2 == VECTOR_TYPE)
	{
	  error ("cannot mix operands of decimal floating and vector types");
	  திரும்பு error_mark_முனை;
	}
      எனில் (code1 == COMPLEX_TYPE || code2 == COMPLEX_TYPE)
	{
	  error ("cannot mix operands of decimal floating and complex types");
	  திரும்பு error_mark_முனை;
	}
      எனில் (code1 == REAL_TYPE && code2 == REAL_TYPE)
	{
	  error ("cannot mix operands of decimal floating "
		 "and other floating types");
	  திரும்பு error_mark_முனை;
	}
    }

  /* If one type is a vector type, return that type.  (How the usual
     arithmetic conversions apply to the vector types extension is not
     precisely specified.)  */
  எனில் (code1 == VECTOR_TYPE)
    திரும்பு t1;

  எனில் (code2 == VECTOR_TYPE)
    திரும்பு t2;

  /* If one type is complex, form the common type of the non-complex
     components, then make that complex.  Use T1 or T2 if it is the
     required type.  */
  எனில் (code1 == COMPLEX_TYPE || code2 == COMPLEX_TYPE)
    {
      மரம் subtype1 = code1 == COMPLEX_TYPE ? மரம்_TYPE (t1) : t1;
      மரம் subtype2 = code2 == COMPLEX_TYPE ? மரம்_TYPE (t2) : t2;
      மரம் subtype = c_common_type (subtype1, subtype2);

      எனில் (code1 == COMPLEX_TYPE && மரம்_TYPE (t1) == subtype)
	திரும்பு t1;
      இல்லையெனில் எனில் (code2 == COMPLEX_TYPE && மரம்_TYPE (t2) == subtype)
	திரும்பு t2;
      இல்லையெனில் எனில் (மரம்_CODE (subtype) == BITINT_TYPE)
	{
	  sorry ("%<_Complex _BitInt(%d)%> unsupported",
		 TYPE_PRECISION (subtype));
	  திரும்பு code1 == COMPLEX_TYPE ? t1 : t2;
	}
      இல்லையெனில்
	திரும்பு build_complex_type (subtype);
    }

  /* If only one is real, use it as the result.  */

  எனில் (code1 == REAL_TYPE && code2 != REAL_TYPE)
    திரும்பு t1;

  எனில் (code2 == REAL_TYPE && code1 != REAL_TYPE)
    திரும்பு t2;

  /* If both are real and either are decimal floating point types, use
     the decimal floating point type with the greater precision. */

  எனில் (code1 == REAL_TYPE && code2 == REAL_TYPE)
    {
      எனில் (TYPE_MAIN_VARIANT (t1) == dfloat128_type_முனை
	  || TYPE_MAIN_VARIANT (t2) == dfloat128_type_முனை)
	திரும்பு dfloat128_type_முனை;
      /* And prefer _Decimal128 over _Decimal64x which has in GCC's
	 implementation the same mode.  */
      இல்லையெனில் எனில் (TYPE_MAIN_VARIANT (t1) == dfloat64x_type_முனை
	       || TYPE_MAIN_VARIANT (t2) == dfloat64x_type_முனை)
	திரும்பு dfloat64x_type_முனை;
      இல்லையெனில் எனில் (TYPE_MAIN_VARIANT (t1) == dfloat64_type_முனை
	       || TYPE_MAIN_VARIANT (t2) == dfloat64_type_முனை)
	திரும்பு dfloat64_type_முனை;
      இல்லையெனில் எனில் (TYPE_MAIN_VARIANT (t1) == dfloat32_type_முனை
	       || TYPE_MAIN_VARIANT (t2) == dfloat32_type_முனை)
	திரும்பு dfloat32_type_முனை;
    }

  /* Deal with fixed-point types.  */
  எனில் (code1 == FIXED_POINT_TYPE || code2 == FIXED_POINT_TYPE)
    {
      unsigned முழு unsignedp = 0, satp = 0;
      scalar_mode m1, m2;
      unsigned முழு fbit1, ibit1, fbit2, ibit2, max_fbit, max_ibit;

      m1 = SCALAR_TYPE_MODE (t1);
      m2 = SCALAR_TYPE_MODE (t2);

      /* If one input type is saturating, the result type is saturating.  */
      எனில் (TYPE_SATURATING (t1) || TYPE_SATURATING (t2))
	satp = 1;

      /* If both fixed-point types are unsigned, the result type is unsigned.
	 When mixing fixed-point and integer types, follow the sign of the
	 fixed-point type.
	 Otherwise, the result type is signed.  */
      எனில் ((TYPE_UNSIGNED (t1) && TYPE_UNSIGNED (t2)
	   && code1 == FIXED_POINT_TYPE && code2 == FIXED_POINT_TYPE)
	  || (code1 == FIXED_POINT_TYPE && code2 != FIXED_POINT_TYPE
	      && TYPE_UNSIGNED (t1))
	  || (code1 != FIXED_POINT_TYPE && code2 == FIXED_POINT_TYPE
	      && TYPE_UNSIGNED (t2)))
	unsignedp = 1;

      /* The result type is signed.  */
      எனில் (unsignedp == 0)
	{
	  /* If the input type is unsigned, we need to convert to the
	     signed type.  */
	  எனில் (code1 == FIXED_POINT_TYPE && TYPE_UNSIGNED (t1))
	    {
	      எண்ணிக்கை mode_class mclass = (எண்ணிக்கை mode_class) 0;
	      எனில் (GET_MODE_CLASS (m1) == MODE_UFRACT)
		mclass = MODE_FRACT;
	      இல்லையெனில் எனில் (GET_MODE_CLASS (m1) == MODE_UACCUM)
		mclass = MODE_ACCUM;
	      இல்லையெனில்
		gcc_unreachable ();
	      m1 = as_a <scalar_mode>
		(mode_for_size (GET_MODE_PRECISION (m1), mclass, 0));
	    }
	  எனில் (code2 == FIXED_POINT_TYPE && TYPE_UNSIGNED (t2))
	    {
	      எண்ணிக்கை mode_class mclass = (எண்ணிக்கை mode_class) 0;
	      எனில் (GET_MODE_CLASS (m2) == MODE_UFRACT)
		mclass = MODE_FRACT;
	      இல்லையெனில் எனில் (GET_MODE_CLASS (m2) == MODE_UACCUM)
		mclass = MODE_ACCUM;
	      இல்லையெனில்
		gcc_unreachable ();
	      m2 = as_a <scalar_mode>
		(mode_for_size (GET_MODE_PRECISION (m2), mclass, 0));
	    }
	}

      எனில் (code1 == FIXED_POINT_TYPE)
	{
	  fbit1 = GET_MODE_FBIT (m1);
	  ibit1 = GET_MODE_IBIT (m1);
	}
      இல்லையெனில்
	{
	  fbit1 = 0;
	  /* Signed integers need to subtract one sign bit.  */
	  ibit1 = TYPE_PRECISION (t1) - (!TYPE_UNSIGNED (t1));
	}

      எனில் (code2 == FIXED_POINT_TYPE)
	{
	  fbit2 = GET_MODE_FBIT (m2);
	  ibit2 = GET_MODE_IBIT (m2);
	}
      இல்லையெனில்
	{
	  fbit2 = 0;
	  /* Signed integers need to subtract one sign bit.  */
	  ibit2 = TYPE_PRECISION (t2) - (!TYPE_UNSIGNED (t2));
	}

      max_ibit = ibit1 >= ibit2 ?  ibit1 : ibit2;
      max_fbit = fbit1 >= fbit2 ?  fbit1 : fbit2;
      திரும்பு c_common_fixed_point_type_for_size (max_ibit, max_fbit, unsignedp,
						 satp);
    }

  /* Both real or both integers; use the one with greater precision.  */

  எனில் (TYPE_PRECISION (t1) > TYPE_PRECISION (t2))
    திரும்பு t1;
  இல்லையெனில் எனில் (TYPE_PRECISION (t2) > TYPE_PRECISION (t1))
    திரும்பு t2;

  /* Same precision.  Prefer long longs to longs to ints when the
     same precision, following the C99 rules on integer type rank
     (which are equivalent to the C90 rules for C90 types).  */

  எனில் (TYPE_MAIN_VARIANT (t1) == long_long_unsigned_type_முனை
      || TYPE_MAIN_VARIANT (t2) == long_long_unsigned_type_முனை)
    திரும்பு long_long_unsigned_type_முனை;

  எனில் (TYPE_MAIN_VARIANT (t1) == long_long_integer_type_முனை
      || TYPE_MAIN_VARIANT (t2) == long_long_integer_type_முனை)
    {
      எனில் (TYPE_UNSIGNED (t1) || TYPE_UNSIGNED (t2))
	திரும்பு long_long_unsigned_type_முனை;
      இல்லையெனில்
	திரும்பு long_long_integer_type_முனை;
    }

  எனில் (TYPE_MAIN_VARIANT (t1) == long_unsigned_type_முனை
      || TYPE_MAIN_VARIANT (t2) == long_unsigned_type_முனை)
    திரும்பு long_unsigned_type_முனை;

  எனில் (TYPE_MAIN_VARIANT (t1) == long_integer_type_முனை
      || TYPE_MAIN_VARIANT (t2) == long_integer_type_முனை)
    {
      /* But preserve unsignedness from the other type,
	 since long cannot hold all the values of an unsigned int.  */
      எனில் (TYPE_UNSIGNED (t1) || TYPE_UNSIGNED (t2))
	திரும்பு long_unsigned_type_முனை;
      இல்லையெனில்
	திரும்பு long_integer_type_முனை;
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
  மரம் mv1 = TYPE_MAIN_VARIANT (t1);
  மரம் mv2 = TYPE_MAIN_VARIANT (t2);

  க்கு (முழு i = இலக்கம்_FLOATN_TYPES - 1; i >= 0; i--)
    எனில் (mv1 == FLOATN_TYPE_முனை (i) || mv2 == FLOATN_TYPE_முனை (i))
      திரும்பு FLOATN_TYPE_முனை (i);

  /* Likewise, prefer long double to double even if same size.  */
  எனில் (mv1 == long_double_type_முனை || mv2 == long_double_type_முனை)
    திரும்பு long_double_type_முனை;

  /* Likewise, prefer double to float even if same size.
     We got a couple of embedded targets with 32 bit doubles, and the
     pdp11 might have 64 bit floats.  */
  எனில் (mv1 == double_type_முனை || mv2 == double_type_முனை)
    திரும்பு double_type_முனை;

  எனில் (mv1 == float_type_முனை || mv2 == float_type_முனை)
    திரும்பு float_type_முனை;

  க்கு (முழு i = இலக்கம்_FLOATNX_TYPES - 1; i >= 0; i--)
    எனில் (mv1 == FLOATNX_TYPE_முனை (i) || mv2 == FLOATNX_TYPE_முனை (i))
      திரும்பு FLOATNX_TYPE_முனை (i);

  எனில் ((code1 == BITINT_TYPE || code2 == BITINT_TYPE) && code1 != code2)
    {
      /* Prefer any other integral types over bit-precise integer types.  */
      எனில் (TYPE_UNSIGNED (t1) == TYPE_UNSIGNED (t2))
	திரும்பு code1 == BITINT_TYPE ? t2 : t1;
      /* If BITINT_TYPE is unsigned and the other type is signed
	 non-BITINT_TYPE with the same precision, the latter has higher rank.
	 In that case:
	 Otherwise, both operands are converted to the unsigned integer type
	 corresponding to the type of the operand with signed integer type.  */
      எனில் (TYPE_UNSIGNED (code1 == BITINT_TYPE ? t1 : t2))
	திரும்பு c_common_unsigned_type (code1 == BITINT_TYPE ? t2 : t1);
    }

  /* Otherwise prefer the unsigned one.  */

  எனில் (TYPE_UNSIGNED (t1))
    திரும்பு t1;
  இல்லையெனில்
    திரும்பு t2;
}

/* Wrapper around c_common_type that is used by c-common.cc and other
   front end optimizations that remove promotions.  ENUMERAL_TYPEs
   are allowed here and are converted to their compatible integer types.
   BOOLEAN_TYPEs are allowed here and return either boolean_type_node or
   preferably a non-Boolean type as the common type.  */
மரம்
common_type (மரம் t1, மரம் t2)
{
  எனில் (மரம்_CODE (t1) == ENUMERAL_TYPE)
    t1 = ENUM_UNDERLYING_TYPE (t1);
  எனில் (மரம்_CODE (t2) == ENUMERAL_TYPE)
    t2 = ENUM_UNDERLYING_TYPE (t2);

  /* If both types are BOOLEAN_TYPE, then return boolean_type_node.  */
  எனில் (மரம்_CODE (t1) == BOOLEAN_TYPE
      && மரம்_CODE (t2) == BOOLEAN_TYPE)
    திரும்பு boolean_type_முனை;

  /* If either type is BOOLEAN_TYPE, then return the other.  */
  எனில் (மரம்_CODE (t1) == BOOLEAN_TYPE)
    திரும்பு t2;
  எனில் (மரம்_CODE (t2) == BOOLEAN_TYPE)
    திரும்பு t1;

  திரும்பு c_common_type (t1, t2);
}



/* Helper function for comptypes.  For two compatible types, return 1
   if they pass consistency checks.  In particular we test that
   TYPE_CANONICAL is set correctly, i.e. the two types can alias.  */

நிலையான தருக்க
comptypes_verify (மரம் type1, மரம் type2)
{
  எனில் (type1 == type2 || !type1 || !type2
      || மரம்_CODE (type1) == ERROR_MARK || மரம்_CODE (type2) == ERROR_MARK)
    திரும்பு உண்மை;

  gcc_checking_assert (c_verify_type (type1));
  gcc_checking_assert (c_verify_type (type2));

  எனில் (TYPE_CANONICAL (type1) != TYPE_CANONICAL (type2)
      && !TYPE_STRUCTURAL_EQUALITY_P (type1)
      && !TYPE_STRUCTURAL_EQUALITY_P (type2))
    {
      /* FIXME: check other types. */
      எனில் (RECORD_OR_UNION_TYPE_P (type1)
	  || மரம்_CODE (type1) == ENUMERAL_TYPE
	  || மரம்_CODE (type2) == ENUMERAL_TYPE)
	திரும்பு பொய்;
    }
  திரும்பு உண்மை;
}

கட்டமைப்பு comptypes_data {

  /* output */
  தருக்க enum_and_int_p;
  தருக்க different_types_p;
  தருக்க warning_needed;

  /* context */
  தருக்க anon_field;
  தருக்க pointedto;

  /* configuration */
  தருக்க equiv;
  தருக்க ignore_promoting_args;

  மாறிலி கட்டமைப்பு tagged_tu_seen_cache* cache;
};


/* Helper function for composite_type.  This function ignores when the
   function type of an old-style declaration is incompatible with a type
   of a declaration with prototype because some are arguments are not
   self-promoting.  This is ignored only for function types but not
   ignored in a nested context.  */

நிலையான தருக்க
comptypes_check_for_composite (மரம் t1, மரம் t2)
{
  கட்டமைப்பு comptypes_data data = { };
  data.ignore_promoting_args = FUNCTION_TYPE == மரம்_CODE (t1);
  திரும்பு comptypes_internal (t1, t2, &data);
}


/* C implementation of compatible_types_for_indirection_note_p.  */

தருக்க
compatible_types_for_indirection_note_p (மரம் type1, மரம் type2)
{
  திரும்பு comptypes (type1, type2);
}

/* Return true if TYPE1 and TYPE2 are compatible types for assignment
   or various other operations.  */

தருக்க
comptypes (மரம் type1, மரம் type2)
{
  கட்டமைப்பு comptypes_data data = { };
  தருக்க ret = comptypes_internal (type1, type2, &data);

  gcc_checking_assert (!ret || comptypes_verify (type1, type2));

  திரும்பு ret;
}


/* Like comptypes, but it returns non-zero only for identical
   types.  */

தருக்க
comptypes_same_p (மரம் type1, மரம் type2)
{
  கட்டமைப்பு comptypes_data data = { };
  தருக்க ret = comptypes_internal (type1, type2, &data);

  gcc_checking_assert (!ret || comptypes_verify (type1, type2));

  எனில் (data.different_types_p)
    திரும்பு பொய்;

  திரும்பு ret;
}


/* Like comptypes, but if it returns true because enum and int are
   compatible, it sets *ENUM_AND_INT_P to true.  */

தருக்க
comptypes_check_enum_int (மரம் type1, மரம் type2, தருக்க *enum_and_int_p)
{
  கட்டமைப்பு comptypes_data data = { };
  தருக்க ret = comptypes_internal (type1, type2, &data);
  *enum_and_int_p = data.enum_and_int_p;

  gcc_checking_assert (!ret || comptypes_verify (type1, type2));

  திரும்பு ret;
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

தருக்க
comptypes_equiv_p (மரம் type1, மரம் type2)
{
  கட்டமைப்பு comptypes_data data = { };
  data.equiv = உண்மை;
  தருக்க ret = comptypes_internal (type1, type2, &data);

  /* check that different equivance classes are assigned only
     to types that are not compatible.  */
  gcc_checking_assert (ret || !comptypes (type1, type2));

  திரும்பு ret;
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

நிலையான தருக்க
comptypes_internal (const_மரம் type1, const_மரம் type2,
		    கட்டமைப்பு comptypes_data *data)
{
  const_மரம் t1 = type1;
  const_மரம் t2 = type2;

  /* Suppress errors caused by previously reported errors.  */

  எனில் (t1 == t2 || !t1 || !t2
      || மரம்_CODE (t1) == ERROR_MARK || மரம்_CODE (t2) == ERROR_MARK)
    திரும்பு உண்மை;

  /* Qualifiers must match. C99 6.7.3p9 */

  எனில் (TYPE_QUALS (t1) != TYPE_QUALS (t2))
    திரும்பு பொய்;

  /* Enumerated types are compatible with integer types, but this is
     not transitive: two enumerated types in the same translation unit
     are compatible with each other only if they are the same type.  */

  எனில் (மரம்_CODE (t1) == ENUMERAL_TYPE
      && COMPLETE_TYPE_P (t1)
      && மரம்_CODE (t2) != ENUMERAL_TYPE)
    {
      t1 = ENUM_UNDERLYING_TYPE (t1);
      எனில் (மரம்_CODE (t2) != VOID_TYPE)
	{
	  data->enum_and_int_p = உண்மை;
	  data->different_types_p = உண்மை;
	}
    }
  இல்லையெனில் எனில் (மரம்_CODE (t2) == ENUMERAL_TYPE
	   && COMPLETE_TYPE_P (t2)
	   && மரம்_CODE (t1) != ENUMERAL_TYPE)
    {
      t2 = ENUM_UNDERLYING_TYPE (t2);
      எனில் (மரம்_CODE (t1) != VOID_TYPE)
	{
	  data->enum_and_int_p = உண்மை;
	  data->different_types_p = உண்மை;
	}
    }

  எனில் (t1 == t2)
    திரும்பு உண்மை;

  /* Different classes of types can't be compatible.  */

  எனில் (மரம்_CODE (t1) != மரம்_CODE (t2))
    திரும்பு பொய்;

  /* Allow for two different type nodes which have essentially the same
     definition.  Note that we already checked for equality of the type
     qualifiers (just above).  */

  எனில் (மரம்_CODE (t1) != ARRAY_TYPE
      && TYPE_MAIN_VARIANT (t1) == TYPE_MAIN_VARIANT (t2))
    திரும்பு உண்மை;

  முழு attrval;

  /* 1 if no need for warning yet, 2 if warning cause has been seen.  */
  எனில் (!(attrval = comp_type_attributes (t1, t2)))
    திரும்பு பொய்;

  எனில் (2 == attrval)
    data->warning_needed = உண்மை;

  தேர்வு (மரம்_CODE (t1))
    {
    நிலை INTEGER_TYPE:
    நிலை FIXED_POINT_TYPE:
    நிலை REAL_TYPE:
    நிலை BITINT_TYPE:
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
      திரும்பு TYPE_CANONICAL (t1) == TYPE_CANONICAL (t2);

    நிலை POINTER_TYPE:
      /* Do not remove mode information.  */
      எனில் (TYPE_MODE (t1) != TYPE_MODE (t2))
	திரும்பு பொய்;
      data->pointedto = உண்மை;
      திரும்பு comptypes_internal (மரம்_TYPE (t1), மரம்_TYPE (t2), data);

    நிலை FUNCTION_TYPE:
      திரும்பு function_types_compatible_p (t1, t2, data);

    நிலை ARRAY_TYPE:
      {
	மரம் d1 = TYPE_DOMAIN (t1);
	மரம் d2 = TYPE_DOMAIN (t2);

	/* Target types must match incl. qualifiers.  */
	எனில் (!comptypes_internal (மரம்_TYPE (t1), மரம்_TYPE (t2), data))
	  திரும்பு பொய்;

	எனில் ((d1 == NULL_மரம்) != (d2 == NULL_மரம்))
	  data->different_types_p = உண்மை;
	/* Ignore size mismatches when forming equivalence classes.  */
	எனில் (data->equiv)
	  திரும்பு உண்மை;
	/* Sizes must match unless one is missing or variable.  */
	எனில் (d1 == NULL_மரம் || d2 == NULL_மரம் || d1 == d2)
	  திரும்பு உண்மை;

	தருக்க d1_variable = உச்சி_array_vla_p (t1);
	தருக்க d2_variable = உச்சி_array_vla_p (t2);

	எனில் (d1_variable != d2_variable)
	  data->different_types_p = உண்மை;
	எனில் (d1_variable || d2_variable)
	  திரும்பு உண்மை;

	தருக்க d1_zero = zero_length_array_type_p (t1)
		       || flexible_array_member_type_p (t1);

	தருக்க d2_zero = zero_length_array_type_p (t2)
		       || flexible_array_member_type_p (t2);

	எனில் (d1_zero && d2_zero)
	  திரும்பு உண்மை;
	எனில் (d1_zero || d2_zero)
	  திரும்பு பொய்;

	எனில் (!மரம்_int_cst_equal (TYPE_MIN_மதிப்பு (d1), TYPE_MIN_மதிப்பு (d2))
	    || !மரம்_int_cst_equal (TYPE_MAX_மதிப்பு (d1), TYPE_MAX_மதிப்பு (d2)))
	  திரும்பு பொய்;

	திரும்பு உண்மை;
      }

    நிலை ENUMERAL_TYPE:
    நிலை RECORD_TYPE:
    நிலை UNION_TYPE:

      எனில் (!flag_isoc23)
	திரும்பு பொய்;

      திரும்பு tagged_types_tu_compatible_p (t1, t2, data);

    நிலை VECTOR_TYPE:
      திரும்பு known_eq (TYPE_VECTOR_SUBPARTS (t1), TYPE_VECTOR_SUBPARTS (t2))
	     && comptypes_internal (மரம்_TYPE (t1), மரம்_TYPE (t2), data);

    இயல்பு:
      திரும்பு பொய்;
    }
  gcc_unreachable ();
}

/* Return true if TTL and TTR are pointers to types that are equivalent, ignoring
   their qualifiers, except for named address spaces.  If the pointers point to
   different named addresses, then we must determine if one address space is a
   subset of the other.  */

நிலையான தருக்க
comp_target_types (location_t location, மரம் ttl, மரம் ttr)
{
  மரம் mvl = மரம்_TYPE (ttl);
  மரம் mvr = மரம்_TYPE (ttr);
  addr_space_t asl = TYPE_ADDR_SPACE (mvl);
  addr_space_t asr = TYPE_ADDR_SPACE (mvr);
  addr_space_t as_common;

  /* Fail if pointers point to incompatible address spaces.  */
  எனில் (!addr_space_superset (asl, asr, &as_common))
    திரும்பு 0;

  /* Qualifiers on element types of array types that are
     pointer targets are also removed.  */
  கட்டமைப்பு comptypes_data data = { };
  எனில் (!comptypes_internal (remove_qualifiers (mvl),
			   remove_qualifiers (mvr), &data))
    திரும்பு பொய்;

  /* For pedantic use comptypes on arrays before removing
     qualifiers on the element type. */
  எனில் (மரம்_CODE (mvl) == ARRAY_TYPE
      && மரம்_CODE (mvr) == ARRAY_TYPE
      && !comptypes (mvl, mvr))
    pedwarn_c11 (location, OPT_Wpedantic, "invalid use of pointers to arrays "
					  "with different qualifiers in ISO C "
					  "before C23");

  எனில் (data.warning_needed)
    pedwarn (location, OPT_Wpedantic, "types are not quite compatible");

  எனில் (data.enum_and_int_p && warn_cxx_compat)
    warning_at (location, OPT_Wc___compat,
		"pointer target types incompatible in C++");

  திரும்பு உண்மை;
}

/* Subroutines of `comptypes'.  */

/* Return true if two 'struct', 'union', or 'enum' types T1 and T2 are
   compatible.  The two types are not the same (which has been
   checked earlier in comptypes_internal).  */

நிலையான தருக்க
tagged_types_tu_compatible_p (const_மரம் t1, const_மரம் t2,
			      கட்டமைப்பு comptypes_data *data)
{
  மரம் s1, s2;

  எனில் (c_type_tag (t1) != c_type_tag (t2))
    திரும்பு பொய்;

  /* When forming equivalence classes for TYPE_CANONICAL in C23, we treat
     structs with the same tag as equivalent, but only when they are targets
     of pointers inside other structs.  */
  எனில் (data->equiv && data->pointedto && NULL_மரம் != c_type_tag (t1))
    திரும்பு உண்மை;

  /* Different types without tag are incompatible except as an anonymous
     field or when forming equivalence classes for TYPE_CANONICAL.  */
  எனில் (!data->anon_field && !data->equiv && NULL_மரம் == c_type_tag (t1))
    திரும்பு பொய்;

  எனில் (!data->anon_field && TYPE_STUB_DECL (t1) != TYPE_STUB_DECL (t2))
    data->different_types_p = உண்மை;

  /* Incomplete types are incompatible inside a TU.  */
  எனில் (TYPE_SIZE (t1) == வெற்று || TYPE_SIZE (t2) == வெற்று)
    திரும்பு பொய்;

  எனில் (ENUMERAL_TYPE != மரம்_CODE (t1)
      && (TYPE_REVERSE_STORAGE_ORDER (t1)
	  != TYPE_REVERSE_STORAGE_ORDER (t2)))
    திரும்பு பொய்;

  எனில் (TYPE_USER_ALIGN (t1) != TYPE_USER_ALIGN (t2))
    data->different_types_p = உண்மை;

  /* For types already being looked at in some active
     invocation of this function, assume compatibility.
     The cache is built as a linked list on the stack
     with the head of the list passed downwards.  */
  க்கு (மாறிலி கட்டமைப்பு tagged_tu_seen_cache *t = data->cache;
       t != வெற்று; t = t->next)
    எனில் (t->t1 == t1 && t->t2 == t2)
      திரும்பு உண்மை;

  மாறிலி கட்டமைப்பு tagged_tu_seen_cache entry = { data->cache, t1, t2 };

  தேர்வு (மரம்_CODE (t1))
    {
    நிலை ENUMERAL_TYPE:
      {
	எனில் (!comptypes (ENUM_UNDERLYING_TYPE (t1), ENUM_UNDERLYING_TYPE (t2)))
	  திரும்பு பொய்;

	/* Speed up the case where the type values are in the same order.  */
	மரம் tv1 = TYPE_மதிப்புகள் (t1);
	மரம் tv2 = TYPE_மதிப்புகள் (t2);

	எனில் (tv1 == tv2)
	  திரும்பு உண்மை;

	க்கு (;tv1 && tv2; tv1 = மரம்_CHAIN (tv1), tv2 = மரம்_CHAIN (tv2))
	  {
	    எனில் (மரம்_PURPOSE (tv1) != மரம்_PURPOSE (tv2))
	      நிறுத்து;

	    எனில் (simple_cst_equal (DECL_INITIAL (மரம்_மதிப்பு (tv1)),
				  DECL_INITIAL (மரம்_மதிப்பு (tv2))) != 1)
	      நிறுத்து;
	  }

	எனில் (tv1 == NULL_மரம் && tv2 == NULL_மரம்)
	  திரும்பு உண்மை;

	எனில் (tv1 == NULL_மரம் || tv2 == NULL_மரம்)
	  திரும்பு பொய்;

	எனில் (list_length (TYPE_மதிப்புகள் (t1)) != list_length (TYPE_மதிப்புகள் (t2)))
	  திரும்பு பொய்;

	க்கு (s1 = TYPE_மதிப்புகள் (t1); s1; s1 = மரம்_CHAIN (s1))
	  {
	    s2 = purpose_member (மரம்_PURPOSE (s1), TYPE_மதிப்புகள் (t2));

	    எனில் (s2 == வெற்று
		|| simple_cst_equal (DECL_INITIAL (மரம்_மதிப்பு (s1)),
				     DECL_INITIAL (மரம்_மதிப்பு (s2))) != 1)
	      திரும்பு பொய்;
	  }

	திரும்பு உண்மை;
      }

    நிலை UNION_TYPE:
    நிலை RECORD_TYPE:

	எனில் (list_length (TYPE_FIELDS (t1)) != list_length (TYPE_FIELDS (t2)))
	  திரும்பு பொய்;

	க்கு (s1 = TYPE_FIELDS (t1), s2 = TYPE_FIELDS (t2);
	     s1 && s2;
	     s1 = DECL_CHAIN (s1), s2 = DECL_CHAIN (s2))
	  {
	    gcc_assert (மரம்_CODE (s1) == FIELD_DECL);
	    gcc_assert (மரம்_CODE (s2) == FIELD_DECL);

	    மரம் ft1 = மரம்_TYPE (s1);
	    மரம் ft2 = மரம்_TYPE (s2);

	    எனில் (DECL_NAME (s1) != DECL_NAME (s2))
	      திரும்பு பொய்;

	    எனில் (DECL_ALIGN (s1) != DECL_ALIGN (s2))
	      திரும்பு பொய்;

	    எனில் (DECL_C_BIT_FIELD (s1) != DECL_C_BIT_FIELD (s2))
	       திரும்பு பொய்;

	    எனில் (DECL_C_BIT_FIELD (s1))
	      {
		எனில் (!மரம்_int_cst_equal (DECL_SIZE (s1), DECL_SIZE (s2)))
		  திரும்பு பொய்;

		ft1 = DECL_BIT_FIELD_TYPE (s1);
		ft2 = DECL_BIT_FIELD_TYPE (s2);
	      }

	    எனில் (!ft1 || !ft2)
	      திரும்பு பொய்;

	    எனில் (மரம்_CODE (ft1) == ERROR_MARK || மரம்_CODE (ft2) == ERROR_MARK)
	      திரும்பு பொய்;

	    data->anon_field = !DECL_NAME (s1);
	    data->pointedto = பொய்;

	    மாறிலி கட்டமைப்பு tagged_tu_seen_cache *cache = data->cache;
	    data->cache = &entry;
	    தருக்க ret = comptypes_internal (ft1, ft2, data);
	    data->cache = cache;
	    எனில் (!ret)
	      திரும்பு பொய்;

	    மரம் st1 = TYPE_SIZE (மரம்_TYPE (s1));
	    மரம் st2 = TYPE_SIZE (மரம்_TYPE (s2));

	    எனில் (data->equiv
		&& st1 && மரம்_CODE (st1) == INTEGER_CST
		&& st2 && மரம்_CODE (st2) == INTEGER_CST
		&& !மரம்_int_cst_equal (st1, st2))
	     திரும்பு பொய்;

	    மரம் counted_by1 = lookup_attribute ("counted_by",
						 DECL_ATTRIBUTES (s1));
	    மரம் counted_by2 = lookup_attribute ("counted_by",
						 DECL_ATTRIBUTES (s2));
	    /* If there is no counted_by attribute for both fields.  */
	    எனில் (!counted_by1 && !counted_by2)
	      தொடர்;

	    /* If only one field has counted_by attribute.  */
	    எனில் ((counted_by1 && !counted_by2)
		|| (!counted_by1 && counted_by2))
	      திரும்பு பொய்;

	    /* Now both s1 and s2 have counted_by attributes, check
	       whether they are the same.  */

	    மரம் counted_by_field1
	      = lookup_field (t1, மரம்_மதிப்பு (மரம்_மதிப்பு (counted_by1)));
	    மரம் counted_by_field2
	      = lookup_field (t2, மரம்_மதிப்பு (மரம்_மதிப்பு (counted_by2)));

	    gcc_assert (counted_by_field1 && counted_by_field2);

	    போது (மரம்_CHAIN (counted_by_field1))
	      counted_by_field1 = மரம்_CHAIN (counted_by_field1);
	    போது (மரம்_CHAIN (counted_by_field2))
	      counted_by_field2 = மரம்_CHAIN (counted_by_field2);

	    எனில் (DECL_NAME (மரம்_மதிப்பு (counted_by_field1))
		!= DECL_NAME (மரம்_மதிப்பு (counted_by_field2)))
	      திரும்பு பொய்;
	  }
	திரும்பு உண்மை;

    இயல்பு:
      gcc_unreachable ();
    }
}

/* Return true if two function types F1 and F2 are compatible.
   If either type specifies no argument types,
   the other must specify a fixed number of self-promoting arg types.
   Otherwise, if one type specifies only the number of arguments,
   the other must specify that number of self-promoting arg types.
   Otherwise, the argument types must match.  */

நிலையான தருக்க
function_types_compatible_p (const_மரம் f1, const_மரம் f2,
			     கட்டமைப்பு comptypes_data *data)
{
  மரம் ret1 = மரம்_TYPE (f1);
  மரம் ret2 = மரம்_TYPE (f2);

  /* 'volatile' qualifiers on a function's return type used to mean
     the function is noreturn.  */
  எனில் (TYPE_VOLATILE (ret1) != TYPE_VOLATILE (ret2))
    pedwarn (உள்ளீடு_location, 0, "function return types not compatible due to %<volatile%>");
  எனில் (TYPE_VOLATILE (ret1))
    ret1 = build_qualified_type (TYPE_MAIN_VARIANT (ret1),
				 TYPE_QUALS (ret1) & ~TYPE_QUAL_VOLATILE);
  எனில் (TYPE_VOLATILE (ret2))
    ret2 = build_qualified_type (TYPE_MAIN_VARIANT (ret2),
				 TYPE_QUALS (ret2) & ~TYPE_QUAL_VOLATILE);

  தருக்க ignore_pargs = data->ignore_promoting_args;
  data->ignore_promoting_args = பொய்;

  எனில் (!comptypes_internal (ret1, ret2, data))
    திரும்பு பொய்;

  data->ignore_promoting_args = ignore_pargs;

  மரம் args1 = TYPE_ARG_TYPES (f1);
  மரம் args2 = TYPE_ARG_TYPES (f2);

  எனில் ((args1 == NULL_மரம்) != (args2 == NULL_மரம்))
    data->different_types_p = உண்மை;

  /* An unspecified parmlist matches any specified parmlist
     whose argument types don't need default promotions.  */

  எனில் (args1 == NULL_மரம்)
    {
      எனில் (TYPE_NO_NAMED_ARGS_STDARG_P (f1) != TYPE_NO_NAMED_ARGS_STDARG_P (f2))
	திரும்பு பொய்;
      எனில் (!(data->ignore_promoting_args || self_promoting_args_p (args2)))
	திரும்பு பொய்;
      data->ignore_promoting_args = பொய்;
      /* If one of these types comes from a non-prototype fn definition,
	 compare that with the other type's arglist.
	 If they don't match, ask for a warning (but no error).  */
      எனில் (TYPE_ACTUAL_ARG_TYPES (f1)
	  && !type_lists_compatible_p (args2, TYPE_ACTUAL_ARG_TYPES (f1), data))
	 data->warning_needed = உண்மை;
      திரும்பு உண்மை;
    }
  எனில் (args2 == NULL_மரம்)
    {
      எனில் (TYPE_NO_NAMED_ARGS_STDARG_P (f1) != TYPE_NO_NAMED_ARGS_STDARG_P (f2))
	திரும்பு பொய்;
      எனில் (!(data->ignore_promoting_args || self_promoting_args_p (args1)))
	திரும்பு பொய்;
      data->ignore_promoting_args = பொய்;
      எனில் (TYPE_ACTUAL_ARG_TYPES (f2)
	  && !type_lists_compatible_p (args1, TYPE_ACTUAL_ARG_TYPES (f2), data))
	data->warning_needed = உண்மை;
      திரும்பு உண்மை;
    }

  /* Both types have argument lists: compare them and propagate results.  */
  திரும்பு type_lists_compatible_p (args1, args2, data);
}

/* Check two lists of types for compatibility, returning false for
   incompatible, true for compatible.  */

நிலையான தருக்க
type_lists_compatible_p (const_மரம் args1, const_மரம் args2,
			 கட்டமைப்பு comptypes_data *data)
{
  போது (1)
    {
      எனில் (args1 == NULL_மரம் && args2 == NULL_மரம்)
	திரும்பு உண்மை;
      /* If one list is shorter than the other,
	 they fail to match.  */
      எனில் (args1 == NULL_மரம் || args2 == NULL_மரம்)
	திரும்பு பொய்;
      மரம் a1 = மரம்_மதிப்பு (args1);
      மரம் a2 = மரம்_மதிப்பு (args2);
      மரம் mv1 = remove_qualifiers (a1);
      மரம் mv2 = remove_qualifiers (a2);

      gcc_assert (mv2);
      gcc_assert (mv2);

      /* If one of the lists has an error marker, ignore this arg.  */
      எனில் (மரம்_CODE (a1) == ERROR_MARK
	       || மரம்_CODE (a2) == ERROR_MARK)
	;
      இல்லையெனில் எனில் (!comptypes_internal (mv1, mv2, data))
	{
	  data->different_types_p = உண்மை;
	  /* Allow  wait (union {union wait *u; int *i} *)
	     and  wait (union wait *)  to be compatible.  */
	  எனில் (மரம்_CODE (a1) == UNION_TYPE
	      && (TYPE_NAME (a1) == NULL_மரம்
		  || TYPE_TRANSPARENT_AGGR (a1))
	      && மரம்_CODE (TYPE_SIZE (a1)) == INTEGER_CST
	      && மரம்_int_cst_equal (TYPE_SIZE (a1),
				     TYPE_SIZE (a2)))
	    {
	      மரம் memb;
	      க்கு (memb = TYPE_FIELDS (a1);
		   memb; memb = DECL_CHAIN (memb))
		{
		  மரம் mv3 = remove_qualifiers (மரம்_TYPE (memb));
		  எனில் (comptypes_internal (mv3, mv2, data))
		    நிறுத்து;
		}
	      எனில் (memb == NULL_மரம்)
		திரும்பு பொய்;
	    }
	  இல்லையெனில் எனில் (மரம்_CODE (a2) == UNION_TYPE
		   && (TYPE_NAME (a2) == NULL_மரம்
		       || TYPE_TRANSPARENT_AGGR (a2))
		   && மரம்_CODE (TYPE_SIZE (a2)) == INTEGER_CST
		   && மரம்_int_cst_equal (TYPE_SIZE (a2),
					  TYPE_SIZE (a1)))
	    {
	      மரம் memb;
	      க்கு (memb = TYPE_FIELDS (a2);
		   memb; memb = DECL_CHAIN (memb))
		{
		  மரம் mv3 = remove_qualifiers (மரம்_TYPE (memb));
		  எனில் (comptypes_internal (mv3, mv1, data))
		    நிறுத்து;
		}
	      எனில் (memb == NULL_மரம்)
		திரும்பு பொய்;
	    }
	  இல்லையெனில்
	    திரும்பு பொய்;
	}

      args1 = மரம்_CHAIN (args1);
      args2 = மரம்_CHAIN (args2);
    }
}

/* Compute the size to increment a pointer by.  When a function type or void
   type or incomplete type is passed, size_one_node is returned.
   This function does not emit any diagnostics; the caller is responsible
   for that.  */

நிலையான மரம்
c_size_in_bytes (const_மரம் type)
{
  எண்ணிக்கை மரம்_code code = மரம்_CODE (type);

  எனில் (code == FUNCTION_TYPE || code == VOID_TYPE || code == ERROR_MARK
      || !COMPLETE_TYPE_P (type))
    திரும்பு size_one_முனை;

  /* Convert in case a char is more than one unit.  */
  திரும்பு size_binop_loc (உள்ளீடு_location, CEIL_DIV_கோவை, TYPE_SIZE_UNIT (type),
			 size_int (TYPE_PRECISION (char_type_முனை)
				   / BITS_PER_UNIT));
}

/* Return either DECL or its known constant value (if it has one).  */

மரம்
decl_constant_மதிப்பு_1 (மரம் decl, தருக்க in_init)
{
  எனில் (/* Note that DECL_INITIAL isn't valid for a PARM_DECL.  */
      மரம்_CODE (decl) != PARM_DECL
      && !மரம்_THIS_VOLATILE (decl)
      && மரம்_READONLY (decl)
      && DECL_INITIAL (decl) != NULL_மரம்
      && !error_operand_p (DECL_INITIAL (decl))
      /* This is invalid if initial value is not constant.
	 If it has either a function call, a memory reference,
	 or a variable, then re-evaluating it could give different results.  */
      && மரம்_CONSTANT (DECL_INITIAL (decl))
      /* Check for cases where this is sub-optimal, even though valid.  */
      && (in_init || மரம்_CODE (DECL_INITIAL (decl)) != CONSTRUCTOR))
    திரும்பு DECL_INITIAL (decl);
  திரும்பு decl;
}

/* Return either DECL or its known constant value (if it has one).
   Like the above, but always return decl outside of functions.  */

மரம்
decl_constant_மதிப்பு (மரம் decl)
{
  /* Don't change a variable array bound or initial value to a constant
     in a place where a variable is invalid.  */
  திரும்பு current_function_decl ? decl_constant_மதிப்பு_1 (decl, பொய்) : decl;
}

/* Convert the array expression EXP to a pointer.  */
நிலையான மரம்
array_to_pointer_conversion (location_t loc, மரம் exp)
{
  மரம் orig_exp = exp;
  மரம் type = மரம்_TYPE (exp);
  மரம் adr;
  மரம் restype = மரம்_TYPE (type);
  மரம் ptrtype;

  gcc_assert (மரம்_CODE (type) == ARRAY_TYPE);

  STRIP_TYPE_NOPS (exp);

  copy_warning (exp, orig_exp);

  ptrtype = c_build_pointer_type (restype);

  எனில் (INDIRECT_REF_P (exp))
    திரும்பு convert (ptrtype, மரம்_OPERAND (exp, 0));

  /* In C++ array compound literals are temporary objects unless they are
     const or appear in namespace scope, so they are destroyed too soon
     to use them for much of anything  (c++/53220).  */
  எனில் (warn_cxx_compat && மரம்_CODE (exp) == COMPOUND_LITERAL_கோவை)
    {
      மரம் decl = மரம்_OPERAND (மரம்_OPERAND (exp, 0), 0);
      எனில் (!மரம்_READONLY (decl) && !மரம்_STATIC (decl))
	warning_at (DECL_SOURCE_LOCATION (decl), OPT_Wc___compat,
		    "converting an array compound literal to a pointer "
		    "leads to a dangling pointer in C++");
    }

  adr = build_unary_op (loc, ADDR_கோவை, exp, உண்மை);
  திரும்பு convert (ptrtype, adr);
}

/* Convert the function expression EXP to a pointer.  */
நிலையான மரம்
function_to_pointer_conversion (location_t loc, மரம் exp)
{
  மரம் orig_exp = exp;

  gcc_assert (மரம்_CODE (மரம்_TYPE (exp)) == FUNCTION_TYPE);

  STRIP_TYPE_NOPS (exp);

  copy_warning (exp, orig_exp);

  மரம் exp2 = build_unary_op (loc, ADDR_கோவை, exp, பொய்);

  /* If the function is defined and known to not require a non-local
     context, make sure no trampoline is generated.  */
  எனில் (மரம்_CODE (exp) == FUNCTION_DECL
      && DECL_INITIAL (exp) && !C_FUNC_NONLOCAL_CONTEXT (exp))
   மரம்_NO_TRAMPOLINE (exp2) = 1;

  திரும்பு exp2;
}

/* Mark EXP as read, not just set, for set but not used -Wunused
   warning purposes.  */

வெறுமை
mark_exp_read (மரம் exp)
{
  தேர்வு (மரம்_CODE (exp))
    {
    நிலை VAR_DECL:
    நிலை PARM_DECL:
      DECL_READ_P (exp) = 1;
      நிறுத்து;
    CASE_CONVERT:
      எனில் (VOID_TYPE_P (மரம்_TYPE (exp)))
	தேர்வு (மரம்_CODE (மரம்_OPERAND (exp, 0)))
	  {
	  நிலை PREINCREMENT_கோவை:
	  நிலை PREDECREMENT_கோவை:
	  நிலை POSTINCREMENT_கோவை:
	  நிலை POSTDECREMENT_கோவை:
	    திரும்பு;
	  இயல்பு:
	    நிறுத்து;
	  }
      /* FALLTHRU */
    நிலை ARRAY_REF:
    நிலை COMPONENT_REF:
    நிலை MODIFY_கோவை:
    நிலை REALPART_கோவை:
    நிலை IMAGPART_கோவை:
    நிலை ADDR_கோவை:
    நிலை VIEW_CONVERT_கோவை:
    நிலை PREINCREMENT_கோவை:
    நிலை PREDECREMENT_கோவை:
    நிலை POSTINCREMENT_கோவை:
    நிலை POSTDECREMENT_கோவை:
      mark_exp_read (மரம்_OPERAND (exp, 0));
      நிறுத்து;
    நிலை COMPOUND_கோவை:
      /* Pattern match what build_atomic_assign produces with modifycode
	 NOP_EXPR.  */
      எனில் (VAR_P (மரம்_OPERAND (exp, 1))
	  && DECL_ARTIFICIAL (மரம்_OPERAND (exp, 1))
	  && மரம்_CODE (மரம்_OPERAND (exp, 0)) == COMPOUND_கோவை)
	{
	  மரம் t1 = மரம்_OPERAND (மரம்_OPERAND (exp, 0), 0);
	  மரம் t2 = மரம்_OPERAND (மரம்_OPERAND (exp, 0), 1);
	  எனில் (மரம்_CODE (t1) == TARGET_கோவை
	      && TARGET_கோவை_SLOT (t1) == மரம்_OPERAND (exp, 1)
	      && மரம்_CODE (t2) == CALL_கோவை)
	    {
	      மரம் fndecl = get_callee_fndecl (t2);
	      மரம் arg = NULL_மரம்;
	      எனில் (fndecl
		  && மரம்_CODE (fndecl) == FUNCTION_DECL
		  && fndecl_built_in_p (fndecl, BUILT_IN_NORMAL)
		  && call_கோவை_nargs (t2) >= 2)
		தேர்வு (DECL_FUNCTION_CODE (fndecl))
		  {
		  நிலை BUILT_IN_ATOMIC_STORE:
		    arg = CALL_கோவை_ARG (t2, 1);
		    நிறுத்து;
		  நிலை BUILT_IN_ATOMIC_STORE_1:
		  நிலை BUILT_IN_ATOMIC_STORE_2:
		  நிலை BUILT_IN_ATOMIC_STORE_4:
		  நிலை BUILT_IN_ATOMIC_STORE_8:
		  நிலை BUILT_IN_ATOMIC_STORE_16:
		    arg = CALL_கோவை_ARG (t2, 0);
		    நிறுத்து;
		  இயல்பு:
		    நிறுத்து;
		  }
	      எனில் (arg)
		{
		  STRIP_NOPS (arg);
		  எனில் (மரம்_CODE (arg) == ADDR_கோவை
		      && DECL_P (மரம்_OPERAND (arg, 0))
		      && TYPE_ATOMIC (மரம்_TYPE (மரம்_OPERAND (arg, 0))))
		    mark_exp_read (மரம்_OPERAND (arg, 0));
		}
	    }
	}
      /* FALLTHRU */
    நிலை C_MAYBE_CONST_கோவை:
      mark_exp_read (மரம்_OPERAND (exp, 1));
      நிறுத்து;
    நிலை OMP_ARRAY_SECTION:
      mark_exp_read (மரம்_OPERAND (exp, 0));
      எனில் (மரம்_OPERAND (exp, 1))
	mark_exp_read (மரம்_OPERAND (exp, 1));
      எனில் (மரம்_OPERAND (exp, 2))
	mark_exp_read (மரம்_OPERAND (exp, 2));
      நிறுத்து;
    இயல்பு:
      நிறுத்து;
    }
}

/* Perform the default conversion of arrays and functions to pointers.
   Return the result of converting EXP.  For any other expression, just
   return EXP.

   LOC is the location of the expression.  */

கட்டமைப்பு c_கோவை
default_function_array_conversion (location_t loc, கட்டமைப்பு c_கோவை exp)
{
  மரம் orig_exp = exp.மதிப்பு;
  மரம் type = மரம்_TYPE (exp.மதிப்பு);
  எண்ணிக்கை மரம்_code code = மரம்_CODE (type);

  தேர்வு (code)
    {
    நிலை ARRAY_TYPE:
      {
	தருக்க not_lvalue = பொய்;
	தருக்க lvalue_array_p;

	போது ((மரம்_CODE (exp.மதிப்பு) == NON_LVALUE_கோவை
		|| CONVERT_கோவை_P (exp.மதிப்பு))
	       && மரம்_TYPE (மரம்_OPERAND (exp.மதிப்பு, 0)) == type)
	  {
	    எனில் (மரம்_CODE (exp.மதிப்பு) == NON_LVALUE_கோவை)
	      not_lvalue = உண்மை;
	    exp.மதிப்பு = மரம்_OPERAND (exp.மதிப்பு, 0);
	  }

	copy_warning (exp.மதிப்பு, orig_exp);

	lvalue_array_p = !not_lvalue && lvalue_p (exp.மதிப்பு);
	எனில் (!flag_isoc99 && !lvalue_array_p)
	  {
	    /* Before C99, non-lvalue arrays do not decay to pointers.
	       Normally, using such an array would be invalid; but it can
	       be used correctly inside sizeof or as a statement expression.
	       Thus, do not give an error here; an error will result later.  */
	    திரும்பு exp;
	  }

	exp.மதிப்பு = array_to_pointer_conversion (loc, exp.மதிப்பு);
      }
      நிறுத்து;
    நிலை FUNCTION_TYPE:
      exp.மதிப்பு = function_to_pointer_conversion (loc, exp.மதிப்பு);
      நிறுத்து;
    இயல்பு:
      நிறுத்து;
    }

  திரும்பு exp;
}

கட்டமைப்பு c_கோவை
default_function_array_read_conversion (location_t loc, கட்டமைப்பு c_கோவை exp)
{
  mark_exp_read (exp.மதிப்பு);
  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  எனில் (மரம்_CODE (exp.மதிப்பு) == COMPONENT_REF
      && handle_counted_by_p (exp.மதிப்பு))
    exp.மதிப்பு = handle_counted_by_for_component_ref (loc, exp.மதிப்பு);
  திரும்பு default_function_array_conversion (loc, exp);
}

/* Return whether EXPR should be treated as an atomic lvalue for the
   purposes of load and store handling.  */

நிலையான தருக்க
really_atomic_lvalue (மரம் கோவை)
{
  எனில் (error_operand_p (கோவை))
    திரும்பு பொய்;
  எனில் (!TYPE_ATOMIC (மரம்_TYPE (கோவை)))
    திரும்பு பொய்;
  எனில் (!COMPLETE_TYPE_P (மரம்_TYPE (கோவை)))
    திரும்பு பொய்;
  எனில் (!lvalue_p (கோவை))
    திரும்பு பொய்;

  /* Ignore _Atomic on register variables, since their addresses can't
     be taken so (a) atomicity is irrelevant and (b) the normal atomic
     sequences wouldn't work.  Ignore _Atomic on structures containing
     bit-fields, since accessing elements of atomic structures or
     unions is undefined behavior (C11 6.5.2.3#5), but it's unclear if
     it's undefined at translation time or execution time, and the
     normal atomic sequences again wouldn't work.  */
  போது (handled_component_p (கோவை))
    {
      எனில் (மரம்_CODE (கோவை) == COMPONENT_REF
	  && DECL_C_BIT_FIELD (மரம்_OPERAND (கோவை, 1)))
	திரும்பு பொய்;
      கோவை = மரம்_OPERAND (கோவை, 0);
    }
  எனில் (மரம்_CODE (கோவை) == COMPOUND_LITERAL_கோவை)
    கோவை = COMPOUND_LITERAL_கோவை_DECL (கோவை);
  எனில் (DECL_P (கோவை) && C_DECL_REGISTER (கோவை))
    திரும்பு பொய்;
  திரும்பு உண்மை;
}

/* If EXPR is a named constant (C23) derived from a constexpr variable
   - that is, a reference to such a variable, or a member extracted by
   a sequence of structure and union (but not array) member accesses
   (where union member accesses must access the same member as
   initialized) - then return the corresponding initializer;
   otherwise, return NULL_TREE.  */

நிலையான மரம்
maybe_get_constexpr_init (மரம் கோவை)
{
  மரம் decl = NULL_மரம்;
  எனில் (மரம்_CODE (கோவை) == VAR_DECL)
    decl = கோவை;
  இல்லையெனில் எனில் (மரம்_CODE (கோவை) == COMPOUND_LITERAL_கோவை)
    decl = COMPOUND_LITERAL_கோவை_DECL (கோவை);
  எனில் (decl
      && C_DECL_DECLARED_CONSTEXPR (decl)
      && DECL_INITIAL (decl) != NULL_மரம்
      && !error_operand_p (DECL_INITIAL (decl)))
    திரும்பு DECL_INITIAL (decl);
  எனில் (மரம்_CODE (கோவை) != COMPONENT_REF)
    திரும்பு NULL_மரம்;
  மரம் inner = maybe_get_constexpr_init (மரம்_OPERAND (கோவை, 0));
  எனில் (inner == NULL_மரம்)
    திரும்பு NULL_மரம்;
  போது ((CONVERT_கோவை_P (inner) || மரம்_CODE (inner) == NON_LVALUE_கோவை)
	 && !error_operand_p (inner)
	 && (TYPE_MAIN_VARIANT (மரம்_TYPE (inner))
	     == TYPE_MAIN_VARIANT (மரம்_TYPE (மரம்_OPERAND (inner, 0)))))
    inner = மரம்_OPERAND (inner, 0);
  எனில் (மரம்_CODE (inner) != CONSTRUCTOR)
    திரும்பு NULL_மரம்;
  மரம் field = மரம்_OPERAND (கோவை, 1);
  unsigned HOST_WIDE_INT cidx;
  மரம் cfield, cvalue;
  தருக்க have_other_init = பொய்;
  FOR_EACH_CONSTRUCTOR_ELT (CONSTRUCTOR_ELTS (inner), cidx, cfield, cvalue)
    {
      எனில் (cfield == field)
	திரும்பு cvalue;
      have_other_init = உண்மை;
    }
  எனில் (மரம்_CODE (மரம்_TYPE (inner)) == UNION_TYPE
      && (have_other_init || field != TYPE_FIELDS (மரம்_TYPE (inner))))
    திரும்பு NULL_மரம்;
  /* Return a default initializer.  */
  எனில் (RECORD_OR_UNION_TYPE_P (மரம்_TYPE (கோவை)))
    திரும்பு build_constructor (மரம்_TYPE (கோவை), வெற்று);
  திரும்பு build_zero_cst (மரம்_TYPE (கோவை));
}

/* Helper function for convert_lvalue_to_rvalue called via
   walk_tree_without_duplicates.  Find DATA inside of the expression.  */

நிலையான மரம்
c_find_var_r (மரம் *tp, முழு *walk_subtrees, வெறுமை *data)
{
  எனில் (TYPE_P (*tp))
    *walk_subtrees = 0;
  இல்லையெனில் எனில் (*tp == (மரம்) data)
    திரும்பு *tp;
  திரும்பு NULL_மரம்;
}

/* Convert expression EXP (location LOC) from lvalue to rvalue,
   including converting functions and arrays to pointers if CONVERT_P.
   If READ_P, also mark the expression as having been read.  If
   FOR_INIT, constexpr expressions of structure and union type should
   be replaced by the corresponding CONSTRUCTOR; otherwise, only
   constexpr scalars (including elements of structures and unions) are
   replaced by their initializers.  */

கட்டமைப்பு c_கோவை
convert_lvalue_to_rvalue (location_t loc, கட்டமைப்பு c_கோவை exp,
			  தருக்க convert_p, தருக்க read_p, தருக்க for_init)
{
  தருக்க force_non_npc = பொய்;
  எனில் (read_p)
    mark_exp_read (exp.மதிப்பு);
  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  எனில் (read_p && மரம்_CODE (exp.மதிப்பு) == COMPONENT_REF
      && handle_counted_by_p (exp.மதிப்பு))
    exp.மதிப்பு = handle_counted_by_for_component_ref (loc, exp.மதிப்பு);

  எனில் (convert_p)
    exp = default_function_array_conversion (loc, exp);
  எனில் (!VOID_TYPE_P (மரம்_TYPE (exp.மதிப்பு))
      || (flag_isoc2y
	  && TYPE_QUALS (மரம்_TYPE (exp.மதிப்பு)) != TYPE_UNQUALIFIED))
    exp.மதிப்பு = require_complete_type (loc, exp.மதிப்பு);
  எனில் (for_init || !RECORD_OR_UNION_TYPE_P (மரம்_TYPE (exp.மதிப்பு)))
    {
      மரம் init = maybe_get_constexpr_init (exp.மதிப்பு);
      எனில் (init != NULL_மரம்)
	{
	  /* A named constant of pointer type or type nullptr_t is not
	     a null pointer constant even if the initializer is
	     one.  */
	  எனில் (மரம்_CODE (init) == INTEGER_CST
	      && !INTEGRAL_TYPE_P (மரம்_TYPE (init))
	      && integer_zerop (init))
	    force_non_npc = உண்மை;
	  exp.மதிப்பு = init;
	}
    }
  எனில் (really_atomic_lvalue (exp.மதிப்பு))
    {
      vec<மரம், va_gc> *params;
      மரம் nonatomic_type, tmp, tmp_addr, fndecl, func_call;
      மரம் கோவை_type = மரம்_TYPE (exp.மதிப்பு);
      மரம் கோவை_addr = build_unary_op (loc, ADDR_கோவை, exp.மதிப்பு, பொய்);
      மரம் seq_cst = build_int_cst (integer_type_முனை, MEMMODEL_SEQ_CST);

      gcc_assert (TYPE_ATOMIC (கோவை_type));

      /* Expansion of a generic atomic load may require an addition
	 element, so allocate enough to prevent a resize.  */
      vec_alloc (params, 4);

      /* Remove the qualifiers for the rest of the expressions and
	 create the VAL temp variable to hold the RHS.  */
      nonatomic_type = build_qualified_type (கோவை_type, TYPE_UNQUALIFIED);
      tmp = create_tmp_var_raw (nonatomic_type);
      tmp_addr = build_unary_op (loc, ADDR_கோவை, tmp, பொய்);
      மரம்_ADDRESSABLE (tmp) = 1;
      /* Do not disable warnings for TMP even though it's artificial.
	 -Winvalid-memory-model depends on it.  */

      /* Issue __atomic_load (&expr, &tmp, SEQ_CST);  */
      fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_LOAD);
      params->quick_தள்ளு (கோவை_addr);
      params->quick_தள்ளு (tmp_addr);
      params->quick_தள்ளு (seq_cst);
      func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, வெற்று);

      /* EXPR is always read.  */
      mark_exp_read (exp.மதிப்பு);

      /* Optimize the common case where c_build_function_call_vec
	 immediately folds __atomic_load (&expr, &tmp, SEQ_CST); into
	 tmp = __atomic_load_<N> (&expr, SEQ_CST);
	 In that case tmp is not addressable and can be initialized
	 fully by the rhs of the MODIFY_EXPR.  */
      மரம் tem = func_call;
      எனில் (CONVERT_கோவை_P (tem) && VOID_TYPE_P (மரம்_TYPE (tem)))
	{
	  tem = மரம்_OPERAND (tem, 0);
	  எனில் (மரம்_CODE (tem) == MODIFY_கோவை
	      && மரம்_OPERAND (tem, 0) == tmp
	      && !walk_மரம்_without_duplicates (&மரம்_OPERAND (tem, 1),
						c_find_var_r, tmp))
	    {
	      மரம்_ADDRESSABLE (tmp) = 0;
	      func_call = மரம்_OPERAND (tem, 1);
	    }
	}

      /* Return tmp which contains the value loaded.  */
      exp.மதிப்பு = build4 (TARGET_கோவை, nonatomic_type, tmp, func_call,
			  NULL_மரம், NULL_மரம்);
    }
  எனில் (convert_p && !error_operand_p (exp.மதிப்பு)
      && (மரம்_CODE (மரம்_TYPE (exp.மதிப்பு)) != ARRAY_TYPE))
    exp.மதிப்பு = convert (build_qualified_type (மரம்_TYPE (exp.மதிப்பு), TYPE_UNQUALIFIED), exp.மதிப்பு);
  எனில் (force_non_npc)
    exp.மதிப்பு = build1 (NOP_கோவை, மரம்_TYPE (exp.மதிப்பு), exp.மதிப்பு);

  {
    மரம் false_மதிப்பு, true_மதிப்பு;
    எனில் (convert_p && !error_operand_p (exp.மதிப்பு)
	&& c_hardbool_type_attr (மரம்_TYPE (exp.மதிப்பு),
				 &false_மதிப்பு, &true_மதிப்பு))
      {
	மரம் t = save_கோவை (exp.மதிப்பு);

	mark_exp_read (exp.மதிப்பு);

	மரம் trapfn = builtin_decl_explicit (BUILT_IN_TRAP);
	மரம் கோவை = build_call_கோவை_loc (loc, trapfn, 0);
	கோவை = build_compound_கோவை (loc, கோவை, boolean_true_முனை);
	கோவை = fold_build3_loc (loc, COND_கோவை, boolean_type_முனை,
				fold_build2_loc (loc, NE_கோவை,
						 boolean_type_முனை,
						 t, true_மதிப்பு),
				கோவை, boolean_true_முனை);
	கோவை = fold_build3_loc (loc, COND_கோவை, boolean_type_முனை,
				fold_build2_loc (loc, NE_கோவை,
						 boolean_type_முனை,
						 t, false_மதிப்பு),
				கோவை, boolean_false_முனை);

	exp.மதிப்பு = கோவை;
      }
  }

  திரும்பு exp;
}

/* Wrapper for the overload above, same arguments but for tree rather than
   c_expr.  This is important for hardbools to decay to bools.  */

நிலையான உள்வரி மரம்
convert_lvalue_to_rvalue (location_t loc, மரம் val,
			  தருக்க convert_p, தருக்க read_p, தருக்க for_init = பொய்)
{
  கட்டமைப்பு c_கோவை கோவை;
  memset (&கோவை, 0, அளவு (கோவை));
  கோவை.மதிப்பு = val;
  கோவை = convert_lvalue_to_rvalue (loc, கோவை, convert_p, read_p, for_init);
  திரும்பு கோவை.மதிப்பு;
}

/* EXP is an expression of integer type.  Apply the integer promotions
   to it and return the promoted value.  */

மரம்
perform_integral_promotions (மரம் exp)
{
  மரம் type = மரம்_TYPE (exp);
  எண்ணிக்கை மரம்_code code = மரம்_CODE (type);

  gcc_assert (INTEGRAL_TYPE_P (type));

  /* Convert enums to the result of applying the integer promotions to
     their underlying type.  */
  எனில் (code == ENUMERAL_TYPE)
    {
      type = ENUM_UNDERLYING_TYPE (type);
      எனில் (c_promoting_integer_type_p (type))
	{
	  எனில் (TYPE_UNSIGNED (type)
	      && TYPE_PRECISION (type) == TYPE_PRECISION (integer_type_முனை))
	    type = unsigned_type_முனை;
	  இல்லையெனில்
	    type = integer_type_முனை;
	}

      திரும்பு convert (type, exp);
    }

  /* ??? This should no longer be needed now bit-fields have their
     proper types.  */
  எனில் (மரம்_CODE (exp) == COMPONENT_REF
      && DECL_C_BIT_FIELD (மரம்_OPERAND (exp, 1)))
    {
      எனில் (BITINT_TYPE_P (DECL_BIT_FIELD_TYPE (மரம்_OPERAND (exp, 1))))
	{
	  மரம் btype = DECL_BIT_FIELD_TYPE (மரம்_OPERAND (exp, 1));
	  எனில் (மரம்_CODE (btype) == BITINT_TYPE)
	    திரும்பு convert (btype, exp);
	  இல்லையெனில்
	    திரும்பு convert (ENUM_UNDERLYING_TYPE (btype), exp);
	}
      /* If it's thinner than an int, promote it like a
	 c_promoting_integer_type_p, otherwise leave it alone.  */
      எனில் (compare_மரம்_int (DECL_SIZE (மரம்_OPERAND (exp, 1)),
			    TYPE_PRECISION (integer_type_முனை)) < 0)
	திரும்பு convert (integer_type_முனை, exp);
    }

  எனில் (c_promoting_integer_type_p (type))
    {
      /* Preserve unsignedness if not really getting any wider.  */
      எனில் (TYPE_UNSIGNED (type)
	  && TYPE_PRECISION (type) == TYPE_PRECISION (integer_type_முனை))
	திரும்பு convert (unsigned_type_முனை, exp);

      திரும்பு convert (integer_type_முனை, exp);
    }

  திரும்பு exp;
}


/* Perform default promotions for C data used in expressions.
   Enumeral types or short or char are converted to int.
   In addition, manifest constants symbols are replaced by their values.  */

மரம்
default_conversion (மரம் exp)
{
  மரம் orig_exp;
  மரம் type = மரம்_TYPE (exp);
  எண்ணிக்கை மரம்_code code = மரம்_CODE (type);
  மரம் promoted_type;

  mark_exp_read (exp);
  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  எனில் (மரம்_CODE (exp) == COMPONENT_REF
      && handle_counted_by_p (exp))
    exp = handle_counted_by_for_component_ref (கோவை_LOCATION (exp), exp);

  /* Functions and arrays have been converted during parsing.  */
  gcc_assert (code != FUNCTION_TYPE);
  எனில் (code == ARRAY_TYPE)
    திரும்பு exp;

  /* Constants can be used directly unless they're not loadable.  */
  எனில் (மரம்_CODE (exp) == CONST_DECL)
    exp = DECL_INITIAL (exp);

  /* Strip no-op conversions.  */
  orig_exp = exp;
  STRIP_TYPE_NOPS (exp);

  copy_warning (exp, orig_exp);

  எனில் (code == VOID_TYPE)
    {
      error_at (கோவை_LOC_OR_LOC (exp, உள்ளீடு_location),
		"void value not ignored as it ought to be");
      திரும்பு error_mark_முனை;
    }

  exp = require_complete_type (கோவை_LOC_OR_LOC (exp, உள்ளீடு_location), exp);
  எனில் (exp == error_mark_முனை)
    திரும்பு error_mark_முனை;

  promoted_type = targetm.promoted_type (type);
  எனில் (promoted_type)
    திரும்பு convert (promoted_type, exp);

  எனில் (INTEGRAL_TYPE_P (type))
    {
      /* Avoid performing integral promotion of bit-precise integer
	 type bit-field to its corresponding bit-precise integer if
	 orig_exp is a cast to it to its underlying type.  */
      எனில் (orig_exp != exp
	  && மரம்_CODE (exp) == COMPONENT_REF
	  && DECL_C_BIT_FIELD (மரம்_OPERAND (exp, 1))
	  && BITINT_TYPE_P (DECL_BIT_FIELD_TYPE (மரம்_OPERAND (exp, 1))))
	திரும்பு perform_integral_promotions (orig_exp);
      திரும்பு perform_integral_promotions (exp);
    }

  திரும்பு exp;
}

/* Look up COMPONENT in a structure or union TYPE.

   If the component name is not found, returns NULL_TREE.  Otherwise,
   the return value is a TREE_LIST, with each TREE_VALUE a FIELD_DECL
   stepping down the chain to the component, which is in the last
   TREE_VALUE of the list.  Normally the list is of length one, but if
   the component is embedded within (nested) anonymous structures or
   unions, the list steps down the chain to the component.  */

மரம்
lookup_field (const_மரம் type, மரம் component)
{
  மரம் field;

  /* If TYPE_LANG_SPECIFIC is set, then it is a sorted array of pointers
     to the field elements.  Use a binary search on this array to quickly
     find the element.  Otherwise, do a linear search.  TYPE_LANG_SPECIFIC
     will always be set for structures which have many elements.

     Duplicate field checking replaces duplicates with NULL_TREE so
     TYPE_LANG_SPECIFIC arrays are potentially no longer sorted.  In that
     case just iterate using DECL_CHAIN.  */

  எனில் (TYPE_LANG_SPECIFIC (type) && TYPE_LANG_SPECIFIC (type)->s
      && !seen_error ())
    {
      முழு bot, உச்சி, half;
      மரம் *field_array = &TYPE_LANG_SPECIFIC (type)->s->elts[0];

      field = TYPE_FIELDS (type);
      bot = 0;
      உச்சி = TYPE_LANG_SPECIFIC (type)->s->len;
      போது (உச்சி - bot > 1)
	{
	  half = (உச்சி - bot + 1) >> 1;
	  field = field_array[bot+half];

	  எனில் (DECL_NAME (field) == NULL_மரம்)
	    {
	      /* Step through all anon unions in linear fashion.  */
	      போது (DECL_NAME (field_array[bot]) == NULL_மரம்)
		{
		  field = field_array[bot++];
		  எனில் (RECORD_OR_UNION_TYPE_P (மரம்_TYPE (field)))
		    {
		      மரம் anon = lookup_field (மரம்_TYPE (field), component);

		      எனில் (anon)
			திரும்பு மரம்_cons (NULL_மரம், field, anon);

		      /* The Plan 9 compiler permits referring
			 directly to an anonymous struct/union field
			 using a typedef name.  */
		      எனில் (flag_plan9_extensions
			  && TYPE_NAME (மரம்_TYPE (field)) != NULL_மரம்
			  && (மரம்_CODE (TYPE_NAME (மரம்_TYPE (field)))
			      == TYPE_DECL)
			  && (DECL_NAME (TYPE_NAME (மரம்_TYPE (field)))
			      == component))
			நிறுத்து;
		    }
		}

	      /* Entire record is only anon unions.  */
	      எனில் (bot > உச்சி)
		திரும்பு NULL_மரம்;

	      /* Restart the binary search, with new lower bound.  */
	      தொடர்;
	    }

	  எனில் (DECL_NAME (field) == component)
	    நிறுத்து;
	  எனில் (DECL_NAME (field) < component)
	    bot += half;
	  இல்லையெனில்
	    உச்சி = bot + half;
	}

      எனில் (DECL_NAME (field_array[bot]) == component)
	field = field_array[bot];
      இல்லையெனில் எனில் (DECL_NAME (field) != component)
	திரும்பு NULL_மரம்;
    }
  இல்லையெனில்
    {
      க்கு (field = TYPE_FIELDS (type); field; field = DECL_CHAIN (field))
	{
	  எனில் (DECL_NAME (field) == NULL_மரம்
	      && RECORD_OR_UNION_TYPE_P (மரம்_TYPE (field)))
	    {
	      மரம் anon = lookup_field (மரம்_TYPE (field), component);

	      எனில் (anon)
		திரும்பு மரம்_cons (NULL_மரம், field, anon);

	      /* The Plan 9 compiler permits referring directly to an
		 anonymous struct/union field using a typedef
		 name.  */
	      எனில் (flag_plan9_extensions
		  && TYPE_NAME (மரம்_TYPE (field)) != NULL_மரம்
		  && மரம்_CODE (TYPE_NAME (மரம்_TYPE (field))) == TYPE_DECL
		  && (DECL_NAME (TYPE_NAME (மரம்_TYPE (field)))
		      == component))
		நிறுத்து;
	    }

	  எனில் (DECL_NAME (field) == component)
	    நிறுத்து;
	}

      எனில் (field == NULL_மரம்)
	திரும்பு NULL_மரம்;
    }

  திரும்பு மரம்_cons (NULL_மரம், field, NULL_மரம்);
}

/* Recursively append candidate IDENTIFIER_NODEs to CANDIDATES.  */

நிலையான வெறுமை
lookup_field_fuzzy_find_candidates (மரம் type, மரம் component,
				    vec<மரம்> *candidates)
{
  மரம் field;
  க்கு (field = TYPE_FIELDS (type); field; field = DECL_CHAIN (field))
    {
      எனில் (DECL_NAME (field) == NULL_மரம்
	  && RECORD_OR_UNION_TYPE_P (மரம்_TYPE (field)))
	lookup_field_fuzzy_find_candidates (மரம்_TYPE (field), component,
					    candidates);

      எனில் (DECL_NAME (field))
	candidates->safe_தள்ளு (DECL_NAME (field));
    }
}

/* Like "lookup_field", but find the closest matching IDENTIFIER_NODE,
   rather than returning a TREE_LIST for an exact match.  */

நிலையான மரம்
lookup_field_fuzzy (மரம் type, மரம் component)
{
  gcc_assert (மரம்_CODE (component) == IDENTIFIER_முனை);

  /* First, gather a list of candidates.  */
  auto_vec <மரம்> candidates;

  lookup_field_fuzzy_find_candidates (type, component,
				      &candidates);

  திரும்பு find_closest_identifier (component, &candidates);
}

/* Support function for build_component_ref's error-handling.

   Given DATUM_TYPE, and "DATUM.COMPONENT", where DATUM is *not* a
   struct or union, should we suggest "DATUM->COMPONENT" as a hint?  */

நிலையான தருக்க
should_suggest_deref_p (மரம் datum_type)
{
  /* We don't do it for Objective-C, since Objective-C 2.0 dot-syntax
     allows "." for ptrs; we could be handling a failed attempt
     to access a property.  */
  எனில் (c_dialect_objc ())
    திரும்பு பொய்;

  /* Only suggest it for pointers...  */
  எனில் (மரம்_CODE (datum_type) != POINTER_TYPE)
    திரும்பு பொய்;

  /* ...to structs/unions.  */
  மரம் underlying_type = மரம்_TYPE (datum_type);
  எண்ணிக்கை மரம்_code code = மரம்_CODE (underlying_type);
  எனில் (code == RECORD_TYPE || code == UNION_TYPE)
    திரும்பு உண்மை;
  இல்லையெனில்
    திரும்பு பொய்;
}

/* Give a component ref REF, decide whether we should handle its counted_by
   attribute based on its context:
   Do not handle counted_by when in offsetof, typeof and alignof operator.  */

நிலையான தருக்க
handle_counted_by_p (மரம் ref)
{
  gcc_assert (மரம்_CODE (ref) == COMPONENT_REF);
  மரம் datum = மரம்_OPERAND (ref, 0);
  /* If the component_ref is build for a offsetof, i.e., the datum
     of the component_ref is a indirect_ref of null_pointer_node,
     we should not generate call to .ACCESS_WITH_SIZE.  */
  எனில் (மரம்_CODE (datum) == INDIRECT_REF
      && மரம்_OPERAND (datum, 0) == null_pointer_முனை)
    திரும்பு பொய்;
  எனில் (in_typeof || in_alignof)
    திரும்பு பொய்;
  திரும்பு உண்மை;
}

/* Given a component ref REF, if there is a counted_by attribute attached,
   issue error when the element_type is a structure or union including a
   flexible array member.  */

நிலையான வெறுமை
check_counted_by_attribute (location_t loc, மரம் ref)
{
  மரம் subdatum = மரம்_OPERAND (ref, 1);
  மரம் sub_type = மரம்_TYPE (subdatum);

  எனில் (!flexible_array_member_type_p (sub_type)
      && மரம்_CODE (sub_type) != POINTER_TYPE)
    திரும்பு;

  மரம் element_type = மரம்_TYPE (sub_type);

  மரம் attr_counted_by = lookup_attribute ("counted_by",
					   DECL_ATTRIBUTES (subdatum));
  எனில் (attr_counted_by)
    {
      /* Issue error when the element_type is a structure or
	union including a flexible array member.  */
      எனில் (RECORD_OR_UNION_TYPE_P (element_type)
	  && TYPE_INCLUDES_FLEXARRAY (element_type))
	{
	  error_at (loc,
		    "%<counted_by%> attribute is not allowed for a pointer to"
		    " structure or union with flexible array member");
	  திரும்பு;
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

நிலையான மரம்
build_counted_by_ref (மரம் datum, மரம் subdatum,
		      மரம் *counted_by_type)
{
  மரம் sub_type = மரம்_TYPE (subdatum);
  எனில் (!flexible_array_member_type_p (sub_type)
      && மரம்_CODE (sub_type) != POINTER_TYPE)
    திரும்பு NULL_மரம்;

  மரம் attr_counted_by = lookup_attribute ("counted_by",
					   DECL_ATTRIBUTES (subdatum));
  எனில் (!attr_counted_by)
    திரும்பு NULL_மரம்;

  மரம் counted_by_ref = NULL_மரம்;
  *counted_by_type = NULL_மரம்;

  மரம் type = மரம்_TYPE (datum);

  /* If the type of the containing structure is an anonymous struct/union,
     and this anonymous struct/union is not a root type, get the first
     outer named structure/union type.  */
  போது (மரம்_CODE (datum) == COMPONENT_REF
	 && c_type_tag (type) == NULL_மரம்
	 && DECL_NAME (மரம்_OPERAND (datum, 1)) == NULL_மரம்)
    {
      datum = மரம்_OPERAND (datum, 0);
      type = மரம்_TYPE (datum);
    }

  மரம் field_id = மரம்_மதிப்பு (மரம்_மதிப்பு (attr_counted_by));
  மரம் counted_by_field = lookup_field (type, field_id);
  gcc_assert (counted_by_field);

  மரம் counted_by_subdatum;
  செய்
    {
      counted_by_subdatum = மரம்_மதிப்பு (counted_by_field);
      /* Get the TYPE of the counted_by field.  */
      *counted_by_type = மரம்_TYPE (counted_by_subdatum);

      counted_by_ref
	= build3 (COMPONENT_REF, மரம்_TYPE (counted_by_subdatum),
		  datum, counted_by_subdatum, NULL_மரம்);

      datum = counted_by_ref;
      counted_by_field = மரம்_CHAIN (counted_by_field);
    }
  போது (counted_by_field);

  counted_by_ref = build_fold_addr_கோவை (counted_by_ref);
  திரும்பு counted_by_ref;
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
நிலையான மரம்
build_access_with_size_for_counted_by (location_t loc, மரம் ref,
				       மரம் counted_by_ref,
				       மரம் counted_by_type)
{
  gcc_assert (flexible_array_member_type_p (மரம்_TYPE (ref))
	      || மரம்_CODE (மரம்_TYPE (ref)) == POINTER_TYPE);

  தருக்க is_fam = flexible_array_member_type_p (மரம்_TYPE (ref));

  /* The result type of the call is a pointer to the flexible array type;
     or is the original pointer type to the pointer field with counted_by.  */
  மரம் result_type = is_fam ? c_build_pointer_type (மரம்_TYPE (ref))
		     : மரம்_TYPE (ref);

  மரம் element_type = மரம்_TYPE (மரம்_TYPE (ref));
  மரம் element_size = VOID_TYPE_P (element_type)
		      ? size_one_முனை
		      : TYPE_SIZE_UNIT (element_type);
  எனில் (element_size == NULL_மரம்)
    திரும்பு ref;

  மரம் first_param = is_fam
		     ? c_fully_fold (array_to_pointer_conversion (loc, ref),
				     பொய், வெற்று)
		     : c_fully_fold (ref, பொய், வெற்று);
  மரம் second_param
    = c_fully_fold (counted_by_ref, பொய், வெற்று);
  மரம் third_param = build_int_cst (c_build_pointer_type (counted_by_type), 0);

  மரம் call
    = build_call_கோவை_internal_loc (loc, IFN_ACCESS_WITH_SIZE,
				    result_type, 4,
				    first_param,
				    second_param,
				    third_param,
				    element_size);

  /* Wrap the call with an INDIRECT_REF with the flexible array type.  */
  எனில் (is_fam)
    call = build1 (INDIRECT_REF, மரம்_TYPE (ref), call);
  SET_கோவை_LOCATION (call, loc);
  திரும்பு call;
}

/* For the COMPONENT_REF ref, check whether it has a counted_by attribute,
   if so, wrap this COMPONENT_REF with the corresponding CALL to the
   function .ACCESS_WITH_SIZE.
   Otherwise, return the ref itself.  */

மரம்
handle_counted_by_for_component_ref (location_t loc, மரம் ref)
{
  gcc_assert (மரம்_CODE (ref) == COMPONENT_REF);
  மரம் datum = மரம்_OPERAND (ref, 0);
  மரம் subdatum = மரம்_OPERAND (ref, 1);
  மரம் counted_by_type = NULL_மரம்;

  எனில் (!(flexible_array_member_type_p (மரம்_TYPE (ref))
	|| மரம்_CODE (மரம்_TYPE (ref)) == POINTER_TYPE))
    திரும்பு ref;

  மரம் counted_by_ref = build_counted_by_ref (datum, subdatum,
					      &counted_by_type);
  எனில் (counted_by_ref)
    ref = build_access_with_size_for_counted_by (loc, ref,
						 counted_by_ref,
						 counted_by_type);
  திரும்பு ref;
}

/* Make an expression to refer to the COMPONENT field of structure or
   union value DATUM.  COMPONENT is an IDENTIFIER_NODE.  LOC is the
   location of the COMPONENT_REF.  COMPONENT_LOC is the location
   of COMPONENT.  ARROW_LOC is the location of the first -> operand if
   it is from -> operator.
   If HANDLE_COUNTED_BY is true, check the counted_by attribute and generate
   a call to .ACCESS_WITH_SIZE.  Otherwise, ignore the attribute.  */

மரம்
build_component_ref (location_t loc, மரம் datum, மரம் component,
		     location_t component_loc, location_t arrow_loc)
{
  மரம் type = மரம்_TYPE (datum);
  எண்ணிக்கை மரம்_code code = மரம்_CODE (type);
  மரம் field = வெற்று;
  மரம் ref;
  தருக்க datum_lvalue = lvalue_p (datum);

  எனில் (!objc_is_public (datum, component))
    திரும்பு error_mark_முனை;

  /* Detect Objective-C property syntax object.property.  */
  எனில் (c_dialect_objc ()
      && (ref = objc_maybe_build_component_ref (datum, component)))
    திரும்பு ref;

  /* See if there is a field or component with name COMPONENT.  */

  எனில் (code == RECORD_TYPE || code == UNION_TYPE)
    {
      எனில் (!COMPLETE_TYPE_P (type))
	{
	  c_incomplete_type_error (loc, NULL_மரம், type);
	  திரும்பு error_mark_முனை;
	}

      field = lookup_field (type, component);

      எனில் (!field)
	{
	  மரம் guessed_id = lookup_field_fuzzy (type, component);
	  எனில் (guessed_id)
	    {
	      /* Attempt to provide a fixit replacement hint, if
		 we have a valid range for the component.  */
	      location_t reported_loc
		= (component_loc != UNKNOWN_LOCATION) ? component_loc : loc;
	      gcc_rich_location rich_loc (reported_loc);
	      எனில் (component_loc != UNKNOWN_LOCATION)
		rich_loc.add_fixit_misspelled_id (component_loc, guessed_id);
	      error_at (&rich_loc,
			"%qT has no member named %qE; did you mean %qE?",
			type, component, guessed_id);
	    }
	  இல்லையெனில்
	    error_at (loc, "%qT has no member named %qE", type, component);
	  திரும்பு error_mark_முனை;
	}

      /* Accessing elements of atomic structures or unions is undefined
	 behavior (C11 6.5.2.3#5).  */
      எனில் (TYPE_ATOMIC (type) && c_inhibit_evaluation_warnings == 0)
	{
	  எனில் (code == RECORD_TYPE)
	    warning_at (loc, 0, "accessing a member %qE of an atomic "
			"structure %qE", component, datum);
	  இல்லையெனில்
	    warning_at (loc, 0, "accessing a member %qE of an atomic "
			"union %qE", component, datum);
	}

      /* Chain the COMPONENT_REFs if necessary down to the FIELD.
	 This might be better solved in future the way the C++ front
	 end does it - by giving the anonymous entities each a
	 separate name and type, and then have build_component_ref
	 recursively call itself.  We can't do that here.  */
      செய்
	{
	  மரம் subdatum = மரம்_மதிப்பு (field);
	  முழு quals;
	  மரம் subtype;
	  தருக்க use_datum_quals;

	  எனில் (மரம்_TYPE (subdatum) == error_mark_முனை)
	    திரும்பு error_mark_முனை;

	  /* If this is an rvalue, it does not have qualifiers in C
	     standard terms and we must avoid propagating such
	     qualifiers down to a non-lvalue array that is then
	     converted to a pointer.  */
	  use_datum_quals = (datum_lvalue
			     || மரம்_CODE (மரம்_TYPE (subdatum)) != ARRAY_TYPE);

	  quals = TYPE_QUALS (strip_array_types (மரம்_TYPE (subdatum)));
	  எனில் (use_datum_quals)
	    quals |= TYPE_QUALS (மரம்_TYPE (datum));
	  subtype = c_build_qualified_type (மரம்_TYPE (subdatum), quals);

	  ref = build3 (COMPONENT_REF, subtype, datum, subdatum,
			NULL_மரம்);
	  SET_கோவை_LOCATION (ref, loc);

	  check_counted_by_attribute (loc, ref);

	  எனில் (மரம்_READONLY (subdatum)
	      || (use_datum_quals && மரம்_READONLY (datum)))
	    மரம்_READONLY (ref) = 1;
	  எனில் (மரம்_THIS_VOLATILE (subdatum)
	      || (use_datum_quals && மரம்_THIS_VOLATILE (datum)))
	    மரம்_THIS_VOLATILE (ref) = 1;

	  எனில் (மரம்_UNAVAILABLE (subdatum))
	    error_unavailable_use (subdatum, NULL_மரம்);
	  இல்லையெனில் எனில் (மரம்_DEPRECATED (subdatum))
	    warn_deprecated_use (subdatum, NULL_மரம்);

	  datum = ref;

	  field = மரம்_CHAIN (field);
	}
      போது (field);

      திரும்பு ref;
    }
  இல்லையெனில் எனில் (should_suggest_deref_p (type))
    {
      /* Special-case the error message for "ptr.field" for the case
	 where the user has confused "." vs "->".  */
      rich_location richloc (வரி_table, loc);
      எனில் (INDIRECT_REF_P (datum) && arrow_loc != UNKNOWN_LOCATION)
	{
	  richloc.add_fixit_செருகு_before (arrow_loc, "(*");
	  richloc.add_fixit_செருகு_after (arrow_loc, ")");
	  error_at (&richloc,
		    "%qE is a pointer to pointer; did you mean to dereference "
		    "it before applying %<->%> to it?",
		    மரம்_OPERAND (datum, 0));
	}
      இல்லையெனில்
	{
	  /* "loc" should be the "." token.  */
	  richloc.add_fixit_replace ("->");
	  error_at (&richloc,
		    "%qE is a pointer; did you mean to use %<->%>?",
		    datum);
	}
      திரும்பு error_mark_முனை;
    }
  இல்லையெனில் எனில் (code != ERROR_MARK)
    error_at (loc,
	      "request for member %qE in something not a structure or union",
	      component);

  திரும்பு error_mark_முனை;
}

/* Given an expression PTR for a pointer, return an expression
   for the value pointed to.
   ERRORSTRING is the name of the operator to appear in error messages.

   LOC is the location to use for the generated tree.  */

மரம்
build_indirect_ref (location_t loc, மரம் ptr, ref_operator errstring)
{
  மரம் pointer = default_conversion (ptr);
  மரம் type = மரம்_TYPE (pointer);
  மரம் ref;

  எனில் (மரம்_CODE (type) == POINTER_TYPE)
    {
      எனில் (CONVERT_கோவை_P (pointer)
          || மரம்_CODE (pointer) == VIEW_CONVERT_கோவை)
	{
	  /* If a warning is issued, mark it to avoid duplicates from
	     the backend.  This only needs to be done at
	     warn_strict_aliasing > 2.  */
	  எனில் (warn_strict_aliasing > 2)
	    எனில் (strict_aliasing_warning (கோவை_LOCATION (pointer),
					 type, மரம்_OPERAND (pointer, 0)))
	      suppress_warning (pointer, OPT_Wstrict_aliasing_);
	}

      எனில் (மரம்_CODE (pointer) == ADDR_கோவை
	  && (மரம்_TYPE (மரம்_OPERAND (pointer, 0))
	      == மரம்_TYPE (type)))
	{
	  ref = மரம்_OPERAND (pointer, 0);
	  protected_set_கோவை_location (ref, loc);
	  திரும்பு ref;
	}
      இல்லையெனில்
	{
	  மரம் t = மரம்_TYPE (type);

	  ref = build1 (INDIRECT_REF, t, pointer);

	  எனில் (VOID_TYPE_P (t) && c_inhibit_evaluation_warnings == 0)
	    warning_at (loc, 0, "dereferencing %<void *%> pointer");

	  /* We *must* set TREE_READONLY when dereferencing a pointer to const,
	     so that we get the proper error message if the result is used
	     to assign to.  Also, &* is supposed to be a no-op.
	     And ANSI C seems to specify that the type of the result
	     should be the const type.  */
	  /* A de-reference of a pointer to const is not a const.  It is valid
	     to change it via some other pointer.  */
	  மரம்_READONLY (ref) = TYPE_READONLY (t);
	  மரம்_SIDE_EFFECTS (ref)
	    = TYPE_VOLATILE (t) || மரம்_SIDE_EFFECTS (pointer);
	  மரம்_THIS_VOLATILE (ref) = TYPE_VOLATILE (t);
	  protected_set_கோவை_location (ref, loc);
	  திரும்பு ref;
	}
    }
  இல்லையெனில் எனில் (மரம்_CODE (pointer) != ERROR_MARK)
    invalid_indirection_error (loc, type, errstring);

  திரும்பு error_mark_முனை;
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

மரம்
build_array_ref (location_t loc, மரம் array, மரம் index)
{
  மரம் ret;
  தருக்க swapped = பொய்;
  எனில் (மரம்_TYPE (array) == error_mark_முனை
      || மரம்_TYPE (index) == error_mark_முனை)
    திரும்பு error_mark_முனை;

  எனில் (மரம்_CODE (மரம்_TYPE (array)) != ARRAY_TYPE
      && மரம்_CODE (மரம்_TYPE (array)) != POINTER_TYPE
      /* Allow vector[index] but not index[vector].  */
      && !gnu_vector_type_p (மரம்_TYPE (array)))
    {
      எனில் (மரம்_CODE (மரம்_TYPE (index)) != ARRAY_TYPE
	  && மரம்_CODE (மரம்_TYPE (index)) != POINTER_TYPE)
	{
          error_at (loc,
            "subscripted value is neither array nor pointer nor vector");

	  திரும்பு error_mark_முனை;
	}
      std::swap (array, index);
      swapped = உண்மை;
    }

  எனில் (!INTEGRAL_TYPE_P (மரம்_TYPE (index)))
    {
      error_at (loc, "array subscript is not an integer");
      திரும்பு error_mark_முனை;
    }

  எனில் (மரம்_CODE (மரம்_TYPE (மரம்_TYPE (array))) == FUNCTION_TYPE)
    {
      error_at (loc, "subscripted value is pointer to function");
      திரும்பு error_mark_முனை;
    }

  /* ??? Existing practice has been to warn only when the char
     index is syntactically the index, not for char[array].  */
  எனில் (!swapped)
     warn_array_subscript_with_type_char (loc, index);

  /* Apply default promotions *after* noticing character types.  */
  index = default_conversion (index);
  எனில் (index == error_mark_முனை)
    திரும்பு error_mark_முனை;

  gcc_assert (மரம்_CODE (மரம்_TYPE (index)) == INTEGER_TYPE
	      || மரம்_CODE (மரம்_TYPE (index)) == BITINT_TYPE);

  தருக்க was_vector = VECTOR_TYPE_P (மரம்_TYPE (array));
  தருக்க non_lvalue = convert_vector_to_array_for_subscript (loc, &array, index);

  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  எனில் (மரம்_CODE (array) == COMPONENT_REF
      && handle_counted_by_p (array))
    array = handle_counted_by_for_component_ref (loc, array);

  எனில் (மரம்_CODE (மரம்_TYPE (array)) == ARRAY_TYPE)
    {
      மரம் rval, type;

      /* An array that is indexed by a non-constant
	 cannot be stored in a register; we must be able to do
	 address arithmetic on its address.
	 Likewise an array of elements of variable size.  */
      எனில் (மரம்_CODE (index) != INTEGER_CST
	  || (COMPLETE_TYPE_P (மரம்_TYPE (மரம்_TYPE (array)))
	      && மரம்_CODE (TYPE_SIZE (மரம்_TYPE (மரம்_TYPE (array)))) != INTEGER_CST))
	{
	  எனில் (!c_mark_addressable (array, உண்மை, உண்மை))
	    திரும்பு error_mark_முனை;
	}
      /* An array that is indexed by a constant value which is not within
	 the array bounds cannot be stored in a register either; because we
	 would get a crash in store_bit_field/extract_bit_field when trying
	 to access a non-existent part of the register.  */
      எனில் (மரம்_CODE (index) == INTEGER_CST
	  && TYPE_DOMAIN (மரம்_TYPE (array))
	  && !int_fits_type_p (index, TYPE_DOMAIN (மரம்_TYPE (array))))
	{
	  எனில் (!c_mark_addressable (array, பொய், உண்மை))
	    திரும்பு error_mark_முனை;
	  /* ISO C2Y disallows a negative integer constant expression index
	     when array subscripting has an operand of array type.  */
	  எனில் (flag_isoc2y
	      && !மரம்_OVERFLOW (index)
	      && மரம்_int_cst_sgn (index) < 0)
	    error_at (loc, "array subscript is negative");
	}

      எனில் ((pedantic || warn_c90_c99_compat || warn_c23_c2y_compat)
	  && ! was_vector)
	{
	  மரம் foo = array;
	  போது (மரம்_CODE (foo) == COMPONENT_REF)
	    foo = மரம்_OPERAND (foo, 0);
	  எனில் ((VAR_P (foo) && C_DECL_REGISTER (foo))
	      || (மரம்_CODE (foo) == COMPOUND_LITERAL_கோவை
		  && C_DECL_REGISTER (COMPOUND_LITERAL_கோவை_DECL (foo))))
	    pedwarn_c23 (loc, OPT_Wpedantic,
			 "ISO C forbids subscripting %<register%> array "
			 "before C2Y");
	  இல்லையெனில் எனில் (!lvalue_p (foo))
	    pedwarn_c90 (loc, OPT_Wpedantic,
			 "ISO C90 forbids subscripting non-lvalue "
			 "array");
	}

      எனில் (மரம்_CODE (மரம்_TYPE (index)) == BITINT_TYPE
	  && TYPE_PRECISION (மரம்_TYPE (index)) > TYPE_PRECISION (sizetype))
	index = fold_convert (sizetype, index);

      type = மரம்_TYPE (மரம்_TYPE (array));
      rval = build4 (ARRAY_REF, type, array, index, NULL_மரம், NULL_மரம்);
      /* Array ref is const/volatile if the array elements are
	 or if the array is.  */
      மரம்_READONLY (rval)
	|= (TYPE_READONLY (மரம்_TYPE (மரம்_TYPE (array)))
	    | மரம்_READONLY (array));
      மரம்_SIDE_EFFECTS (rval)
	|= (TYPE_VOLATILE (மரம்_TYPE (மரம்_TYPE (array)))
	    | மரம்_SIDE_EFFECTS (array));
      மரம்_THIS_VOLATILE (rval)
	|= (TYPE_VOLATILE (மரம்_TYPE (மரம்_TYPE (array)))
	    /* This was added by rms on 16 Nov 91.
	       It fixes  vol struct foo *a;  a->elts[1]
	       in an inline function.
	       Hope it doesn't break something else.  */
	    | மரம்_THIS_VOLATILE (array));
      ret = require_complete_type (loc, rval);
      protected_set_கோவை_location (ret, loc);
      எனில் (non_lvalue)
	ret = non_lvalue_loc (loc, ret);
      திரும்பு ret;
    }
  இல்லையெனில்
    {
      மரம் ar = default_conversion (array);

      எனில் (ar == error_mark_முனை)
	திரும்பு ar;

      gcc_assert (மரம்_CODE (மரம்_TYPE (ar)) == POINTER_TYPE);
      gcc_assert (மரம்_CODE (மரம்_TYPE (மரம்_TYPE (ar))) != FUNCTION_TYPE);

      ret = build_indirect_ref (loc, build_இருமம்_op (loc, PLUS_கோவை, ar,
						      index, பொய்),
				RO_ARRAY_INDEXING);
      எனில் (non_lvalue)
	ret = non_lvalue_loc (loc, ret);
      திரும்பு ret;
    }
}

/* Build an OpenMP array section reference, creating an exact type for the
   resulting expression based on the element type and bounds if possible.  If
   we have variable bounds, create an incomplete array type for the result
   instead.  */

மரம்
build_omp_array_section (location_t loc, மரம் array, மரம் index, மரம் length)
{
  மரம் type = மரம்_TYPE (array);
  gcc_assert (type);

  மரம் sectype, eltype = மரம்_TYPE (type);

  /* It's not an array or pointer type.  Just reuse the type of the original
     expression as the type of the array section (an error will be raised
     anyway, later).  */
  எனில் (eltype == NULL_மரம் || error_operand_p (eltype))
    sectype = மரம்_TYPE (array);
  இல்லையெனில்
    {
      மரம் idxtype = NULL_மரம்;

      எனில் (index != NULL_மரம்
	  && length != NULL_மரம்
	  && INTEGRAL_TYPE_P (மரம்_TYPE (index))
	  && INTEGRAL_TYPE_P (மரம்_TYPE (length)))
	{
	  மரம் கீழ் = fold_convert (sizetype, index);
	  மரம் உயர்வு = fold_convert (sizetype, length);
	  உயர்வு = size_binop (PLUS_கோவை, கீழ், உயர்வு);
	  உயர்வு = size_binop (MINUS_கோவை, உயர்வு, size_one_முனை);
	  idxtype = build_range_type (sizetype, கீழ், உயர்வு);
	}
      இல்லையெனில் எனில் ((index == NULL_மரம் || integer_zerop (index))
	       && length != NULL_மரம்
	       && INTEGRAL_TYPE_P (மரம்_TYPE (length)))
	idxtype = build_index_type (length);

      gcc_assert (!error_operand_p (idxtype));

      sectype = c_build_array_type (eltype, idxtype);
    }

  திரும்பு build3_loc (loc, OMP_ARRAY_SECTION, sectype, array, index, length);
}


/* Record that REF is used.  This is relevant for undeclared static
   function and declarations referenced from a non-local context.
   ADDRESS indicates whether the address is taken.  */

வெறுமை
mark_decl_used (மரம் ref, தருக்க address)
{
  எனில் (!ref || !DECL_P (ref) || in_alignof)
    திரும்பு;

  /* Non-file-scope and non-local reference in nested function.  */
  தருக்க nonloc_p = current_function_decl && DECL_CONTEXT (ref)
		  && DECL_CONTEXT (current_function_decl)
		  && DECL_CONTEXT (ref) != current_function_decl;

  /* An undeclared static function.  */
  தருக்க static_p = மரம்_CODE (ref) == FUNCTION_DECL
		  && DECL_INITIAL (ref) == NULL_மரம்
		  && DECL_EXTERNAL (ref)
		  && !மரம்_PUBLIC (ref);

  எனில் (!static_p && !nonloc_p)
    திரும்பு;

  /* If we may be in an unevaluated context, delay the decision.  */
  எனில் (in_sizeof || in_typeof || in_countof || in_generic)
    திரும்பு record_maybe_used_decl (ref, address);

  எனில் (static_p)
    C_DECL_USED (ref) = 1;

  எனில் (nonloc_p && (VAR_OR_FUNCTION_DECL_P (ref)
		   || மரம்_CODE (ref) == PARM_DECL))
    DECL_NONLOCAL (ref) = 1;

  /* Nothing to do anymore.  */
  எனில் (!nonloc_p || C_FUNC_NONLOCAL_CONTEXT (current_function_decl))
    திரும்பு;

  /* Filter out the cases where referencing a non-local variable does not
     require a non-local context passed via the static chain.  */
  எனில் (!c_type_variably_modified_p (மரம்_TYPE (ref)))
    தேர்வு (மரம்_CODE (ref))
      {
      நிலை FUNCTION_DECL:
	/* Use of another local function that requires no context is ok.  */
	எனில் (!C_FUNC_NONLOCAL_CONTEXT (ref) && DECL_INITIAL (ref))
	  திரும்பு;
	நிறுத்து;
      நிலை VAR_DECL:
	/* Static variables and constexpr are ok, but for the later only
	   when the address is not taken.  */
	எனில் (மரம்_STATIC (ref) || (C_DECL_DECLARED_CONSTEXPR (ref) && !address))
	  திரும்பு;
	நிறுத்து;
      நிலை TYPE_DECL:
	/* A typedef is ok when not for a variably-modified type. */
	திரும்பு;
      நிலை CONST_DECL:
	/* An enumeration constant is ok. */
	திரும்பு;
      நிலை PARM_DECL:
	நிறுத்து;
      நிலை LABEL_DECL:
	நிறுத்து;
      இயல்பு:
	gcc_unreachable ();
    }

  /* Mark all parent functions up to the nesting level of the variable as
     as needing the non-local context.  */
  க்கு (மரம் cont = current_function_decl; cont; cont = DECL_CONTEXT (cont))
    {
      எனில் (cont == DECL_CONTEXT (ref))
	நிறுத்து;

      /* There should not be any other type of context used for function
	 except TRANSLATION_UNIT_DECL which we should be able to reach.  */
      gcc_checking_assert (மரம்_CODE (cont) == FUNCTION_DECL);

      எனில் (மரம்_CODE (cont) == FUNCTION_DECL)
	C_FUNC_NONLOCAL_CONTEXT (cont) = 1;
    }
}


/* Build an external reference to identifier ID.  FUN indicates
   whether this will be used for a function call.  LOC is the source
   location of the identifier.  This sets *TYPE to the type of the
   identifier, which is not the same as the type of the returned value
   for CONST_DECLs defined as enum constants.  If the type of the
   identifier is not available, *TYPE is set to NULL.  */
மரம்
build_external_ref (location_t loc, மரம் id, தருக்க fun, மரம் *type)
{
  மரம் ref;
  மரம் decl = lookup_name (id);

  /* In Objective-C, an instance variable (ivar) may be preferred to
     whatever lookup_name() found.  */
  decl = objc_lookup_ivar (decl, id);

  *type = வெற்று;
  எனில் (decl && decl != error_mark_முனை)
    {
      ref = decl;
      *type = மரம்_TYPE (ref);
      எனில் (DECL_P (decl) && C_DECL_UNDERSPECIFIED (decl))
	error_at (loc, "underspecified %qD referenced in its initializer",
		  decl);
    }
  இல்லையெனில் எனில் (fun)
    /* Implicit function declaration.  */
    ref = implicitly_declare (loc, id);
  இல்லையெனில் எனில் (decl == error_mark_முனை)
    /* Don't complain about something that's already been
       complained about.  */
    திரும்பு error_mark_முனை;
  இல்லையெனில்
    {
      undeclared_variable (loc, id);
      திரும்பு error_mark_முனை;
    }

  /* For an OpenMP map clause, we can get better diagnostics for decls with
     unmappable types if we return the decl with an error_mark_node type,
     rather than returning error_mark_node for the decl itself.  */
  எனில் (மரம்_TYPE (ref) == error_mark_முனை
      && !c_omp_array_section_p)
    திரும்பு error_mark_முனை;

  எனில் (மரம்_UNAVAILABLE (ref))
    error_unavailable_use (ref, NULL_மரம்);
  இல்லையெனில் எனில் (மரம்_DEPRECATED (ref))
    warn_deprecated_use (ref, NULL_மரம்);

  /* Recursive call does not count as usage.  */
  எனில் (ref != current_function_decl)
    {
      மரம்_USED (ref) = 1;
    }

  mark_decl_used (ref, பொய்);

  எனில் (மரம்_CODE (ref) == CONST_DECL)
    {
      used_types_செருகு (மரம்_TYPE (ref));

      எனில் (warn_cxx_compat
	  && மரம்_CODE (மரம்_TYPE (ref)) == ENUMERAL_TYPE
	  && C_TYPE_DEFINED_IN_STRUCT (மரம்_TYPE (ref)))
	{
	  warning_at (loc, OPT_Wc___compat,
		      "enum constant defined in struct or union "
		      "is not visible in C++");
	  inform (DECL_SOURCE_LOCATION (ref), "enum constant defined here");
	}

      ref = DECL_INITIAL (ref);
      மரம்_CONSTANT (ref) = 1;
    }
  /* C99 6.7.4p3: An inline definition of a function with external
     linkage ... shall not contain a reference to an identifier with
     internal linkage.  */
  இல்லையெனில் எனில் (current_function_decl != NULL_மரம்
	   && DECL_DECLARED_INLINE_P (current_function_decl)
	   && DECL_EXTERNAL (current_function_decl)
	   && VAR_OR_FUNCTION_DECL_P (ref)
	   && (!VAR_P (ref) || மரம்_STATIC (ref))
	   && ! மரம்_PUBLIC (ref)
	   && DECL_CONTEXT (ref) != current_function_decl)
    record_inline_static (loc, current_function_decl, ref,
			  csi_internal);

  திரும்பு ref;
}

நிலையான கட்டமைப்பு maybe_used_decl *maybe_used_decls;

/* Record that DECL, a reference seen inside sizeof or typeof or _Countof or
   _Generic, might be used if the operand of sizeof is a VLA type or the
   operand of typeof is a variably modified type or the operand of _Countof has
   a variable number of elements or the operand of _Generic is the one selected
   as the result.  */

நிலையான வெறுமை
record_maybe_used_decl (மரம் decl, தருக்க address)
{
  கட்டமைப்பு maybe_used_decl *t = XOBNEW (&parser_obstack, கட்டமைப்பு maybe_used_decl);
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

வெறுமை
எடு_maybe_used (தருக்க used)
{
  கட்டமைப்பு maybe_used_decl *p = maybe_used_decls;
  முழு cur_level = in_sizeof + in_typeof + in_countof + in_generic;
  போது (p && p->level > cur_level)
    {
      எனில் (used)
	{
	  எனில் (cur_level == 0)
	    mark_decl_used (p->decl, p->address);
	  இல்லையெனில்
	    p->level = cur_level;
	}
      p = p->next;
    }
  எனில் (!used || cur_level == 0)
    maybe_used_decls = p;
}

/* Pop the stack of decls possibly used inside sizeof or typeof or _Countof or
   _Generic, without acting on them, and return the pointer to the previous top
   of the stack.  This for use at the end of a default generic association when
   it is not yet known whether the expression is used.  If it later turns out
   the expression is used (or treated as used before C23), restore_maybe_used
   should be called on the return value followed by pop_maybe_used (true);
   otherwise, the return value can be discarded.  */

கட்டமைப்பு maybe_used_decl *
save_maybe_used ()
{
  கட்டமைப்பு maybe_used_decl *p = maybe_used_decls, *orig = p;
  முழு cur_level = in_sizeof + in_typeof + in_countof + in_generic;
  போது (p && p->level > cur_level)
    p = p->next;
  maybe_used_decls = p;
  திரும்பு orig;
}

/* Restore the stack of decls possibly used inside sizeof or typeof or _Countof
   or _Generic returned by save_maybe_used.  It is required that the stack is
   at exactly the point where it was left by save_maybe_used.  */

வெறுமை
restore_maybe_used (கட்டமைப்பு maybe_used_decl *அடுக்கு)
{
  maybe_used_decls = அடுக்கு;
}

/* Return the result of sizeof applied to EXPR.  */

கட்டமைப்பு c_கோவை
c_கோவை_sizeof_கோவை (location_t loc, கட்டமைப்பு c_கோவை கோவை)
{
  கட்டமைப்பு c_கோவை ret;
  எனில் (கோவை.மதிப்பு == error_mark_முனை)
    {
      ret.மதிப்பு = error_mark_முனை;
      ret.original_code = ERROR_MARK;
      ret.original_type = வெற்று;
      ret.m_decimal = 0;
      எடு_maybe_used (பொய்);
    }
  இல்லையெனில்
    {
      தருக்க கோவை_const_operands = உண்மை;

      எனில் (மரம்_CODE (கோவை.மதிப்பு) == PARM_DECL
	  && C_ARRAY_PARAMETER (கோவை.மதிப்பு))
	{
	  auto_diagnostic_group d;
	  எனில் (warning_at (loc, OPT_Wsizeof_array_argument,
			  "%<sizeof%> on array function parameter %qE will "
			  "return size of %qT", கோவை.மதிப்பு,
			  மரம்_TYPE (கோவை.மதிப்பு)))
	    inform (DECL_SOURCE_LOCATION (கோவை.மதிப்பு), "declared here");
	}
      மரம் folded_கோவை = c_fully_fold (கோவை.மதிப்பு, require_constant_மதிப்பு,
				       &கோவை_const_operands);
      ret.மதிப்பு = c_sizeof (loc, மரம்_TYPE (folded_கோவை));
      c_last_sizeof_arg = கோவை.மதிப்பு;
      c_last_sizeof_loc = loc;
      ret.original_code = SIZEOF_கோவை;
      ret.original_type = வெற்று;
      ret.m_decimal = 0;
      எனில் (C_TYPE_VARIABLE_SIZE (மரம்_TYPE (folded_கோவை)))
	{
	  /* sizeof is evaluated when given a vla (C99 6.5.3.4p2).  */
	  ret.மதிப்பு = build2 (C_MAYBE_CONST_கோவை, மரம்_TYPE (ret.மதிப்பு),
			      folded_கோவை, ret.மதிப்பு);
	  C_MAYBE_CONST_கோவை_NON_CONST (ret.மதிப்பு) = !கோவை_const_operands;
	  SET_கோவை_LOCATION (ret.மதிப்பு, loc);
	}
      எடு_maybe_used (C_TYPE_VARIABLE_SIZE (மரம்_TYPE (folded_கோவை)));
    }
  திரும்பு ret;
}

/* Return the result of sizeof applied to T, a structure for the type
   name passed to sizeof (rather than the type itself).  LOC is the
   location of the original expression.  */

கட்டமைப்பு c_கோவை
c_கோவை_sizeof_type (location_t loc, கட்டமைப்பு c_type_name *t)
{
  மரம் type;
  கட்டமைப்பு c_கோவை ret;
  மரம் type_கோவை = NULL_மரம்;
  தருக்க type_கோவை_const = உண்மை;
  type = groktypename (t, &type_கோவை, &type_கோவை_const);
  ret.மதிப்பு = c_sizeof (loc, type);
  c_last_sizeof_arg = type;
  c_last_sizeof_loc = loc;
  ret.original_code = SIZEOF_கோவை;
  ret.original_type = வெற்று;
  ret.m_decimal = 0;
  எனில் (type == error_mark_முனை)
    {
      ret.மதிப்பு = error_mark_முனை;
      ret.original_code = ERROR_MARK;
    }
  இல்லையெனில்
  எனில் ((type_கோவை || மரம்_CODE (ret.மதிப்பு) == INTEGER_CST)
      && C_TYPE_VARIABLE_SIZE (type))
    {
      /* If the type is a [*] array, it is a VLA but is represented as
	 having a size of zero.  In such a case we must ensure that
	 the result of sizeof does not get folded to a constant by
	 c_fully_fold, because if the size is evaluated the result is
	 not constant and so constraints on zero or negative size
	 arrays must not be applied when this sizeof call is inside
	 another array declarator.  */
      எனில் (!type_கோவை)
	type_கோவை = integer_zero_முனை;
      ret.மதிப்பு = build2 (C_MAYBE_CONST_கோவை, மரம்_TYPE (ret.மதிப்பு),
			  type_கோவை, ret.மதிப்பு);
      C_MAYBE_CONST_கோவை_NON_CONST (ret.மதிப்பு) = !type_கோவை_const;
    }
  எடு_maybe_used (type != error_mark_முனை
		  ? C_TYPE_VARIABLE_SIZE (type) : பொய்);
  திரும்பு ret;
}

நிலையான தருக்க
உச்சி_array_vla_p (const_மரம் type)
{
  எனில் (மரம்_CODE (type) != ARRAY_TYPE)
    திரும்பு பொய்;

  மரம் d = TYPE_DOMAIN (type);

  எனில் (!d)
    திரும்பு பொய்;
  எனில் (!TYPE_MAX_மதிப்பு (d))
    திரும்பு பொய்;

  திரும்பு மரம்_CODE (TYPE_MAX_மதிப்பு (d)) != INTEGER_CST
	 || மரம்_CODE (TYPE_MIN_மதிப்பு (d)) != INTEGER_CST;
}

/* Return the result of countof applied to EXPR.  */

கட்டமைப்பு c_கோவை
c_கோவை_countof_கோவை (location_t loc, கட்டமைப்பு c_கோவை கோவை)
{
  கட்டமைப்பு c_கோவை ret;
  எனில் (கோவை.மதிப்பு == error_mark_முனை)
    {
      ret.மதிப்பு = error_mark_முனை;
      ret.original_code = ERROR_MARK;
      ret.original_type = வெற்று;
      ret.m_decimal = 0;
      எடு_maybe_used (பொய்);
    }
  இல்லையெனில்
    {
      தருக்க கோவை_const_operands = உண்மை;

      மரம் folded_கோவை = c_fully_fold (கோவை.மதிப்பு, require_constant_மதிப்பு,
				       &கோவை_const_operands);
      ret.மதிப்பு = c_countof_type (loc, மரம்_TYPE (folded_கோவை));
      c_last_sizeof_arg = கோவை.மதிப்பு;
      c_last_sizeof_loc = loc;
      ret.original_code = COUNTOF_கோவை;
      ret.original_type = வெற்று;
      ret.m_decimal = 0;
      எனில் (உச்சி_array_vla_p (மரம்_TYPE (folded_கோவை)))
	{
	  /* countof is evaluated when given a vla.  */
	  ret.மதிப்பு = build2 (C_MAYBE_CONST_கோவை, மரம்_TYPE (ret.மதிப்பு),
			      folded_கோவை, ret.மதிப்பு);
	  C_MAYBE_CONST_கோவை_NON_CONST (ret.மதிப்பு) = !கோவை_const_operands;
	  SET_கோவை_LOCATION (ret.மதிப்பு, loc);
	}
      எடு_maybe_used (உச்சி_array_vla_p (மரம்_TYPE (folded_கோவை)));
    }
  திரும்பு ret;
}

/* Return the result of countof applied to T, a structure for the type
   name passed to countof (rather than the type itself).  LOC is the
   location of the original expression.  */

கட்டமைப்பு c_கோவை
c_கோவை_countof_type (location_t loc, கட்டமைப்பு c_type_name *t)
{
  மரம் type;
  கட்டமைப்பு c_கோவை ret;
  மரம் type_கோவை = NULL_மரம்;
  தருக்க type_கோவை_const = உண்மை;
  type = groktypename (t, &type_கோவை, &type_கோவை_const);
  ret.மதிப்பு = c_countof_type (loc, type);
  c_last_sizeof_arg = type;
  c_last_sizeof_loc = loc;
  ret.original_code = COUNTOF_கோவை;
  ret.original_type = வெற்று;
  ret.m_decimal = 0;
  எனில் (type == error_mark_முனை)
    {
      ret.மதிப்பு = error_mark_முனை;
      ret.original_code = ERROR_MARK;
    }
  இல்லையெனில்
  எனில் ((type_கோவை || மரம்_CODE (ret.மதிப்பு) == INTEGER_CST)
      && உச்சி_array_vla_p (type))
    {
      /* If the type is a [*] array, it is a VLA but is represented as
	 having a size of zero.  In such a case we must ensure that
	 the result of countof does not get folded to a constant by
	 c_fully_fold, because if the number of elements is evaluated
	 the result is not constant and so
	 constraints on zero or negative size arrays must not be applied
	 when this countof call is inside another array declarator.  */
      எனில் (!type_கோவை)
	type_கோவை = integer_zero_முனை;
      ret.மதிப்பு = build2 (C_MAYBE_CONST_கோவை, மரம்_TYPE (ret.மதிப்பு),
			  type_கோவை, ret.மதிப்பு);
      C_MAYBE_CONST_கோவை_NON_CONST (ret.மதிப்பு) = !type_கோவை_const;
    }
  எடு_maybe_used (type != error_mark_முனை ? உச்சி_array_vla_p (type) : பொய்);
  திரும்பு ret;
}

/* Return the result of maxof applied to T, a structure for the type
   name passed to maxof (rather than the type itself).  LOC is the
   location of the original expression.  */

கட்டமைப்பு c_கோவை
c_கோவை_maxof_type (location_t loc, கட்டமைப்பு c_type_name *t)
{
  மரம் type;
  கட்டமைப்பு c_கோவை ret;
  மரம் type_கோவை = NULL_மரம்;
  தருக்க type_கோவை_const = உண்மை;
  type = groktypename (t, &type_கோவை, &type_கோவை_const);
  ret.மதிப்பு = c_maxof_type (loc, type);
  c_last_sizeof_arg = type;
  c_last_sizeof_loc = loc;
  ret.original_code = MAXOF_கோவை;
  ret.original_type = வெற்று;
  ret.m_decimal = 0;
  எனில் (type == error_mark_முனை)
    {
      ret.மதிப்பு = error_mark_முனை;
      ret.original_code = ERROR_MARK;
    }
  எடு_maybe_used (type != error_mark_முனை);
  திரும்பு ret;
}

/* Return the result of minof applied to T, a structure for the type
   name passed to minof (rather than the type itself).  LOC is the
   location of the original expression.  */

கட்டமைப்பு c_கோவை
c_கோவை_minof_type (location_t loc, கட்டமைப்பு c_type_name *t)
{
  மரம் type;
  கட்டமைப்பு c_கோவை ret;
  மரம் type_கோவை = NULL_மரம்;
  தருக்க type_கோவை_const = உண்மை;
  type = groktypename (t, &type_கோவை, &type_கோவை_const);
  ret.மதிப்பு = c_minof_type (loc, type);
  c_last_sizeof_arg = type;
  c_last_sizeof_loc = loc;
  ret.original_code = MINOF_கோவை;
  ret.original_type = வெற்று;
  ret.m_decimal = 0;
  எனில் (type == error_mark_முனை)
    {
      ret.மதிப்பு = error_mark_முனை;
      ret.original_code = ERROR_MARK;
    }
  எடு_maybe_used (type != error_mark_முனை);
  திரும்பு ret;
}

/* Build a function call to function FUNCTION with parameters PARAMS.
   The function call is at LOC.
   PARAMS is a list--a chain of TREE_LIST nodes--in which the
   TREE_VALUE of each node is a parameter-expression.
   FUNCTION's data type may be a function type or a pointer-to-function.  */

மரம்
build_function_call (location_t loc, மரம் function, மரம் params)
{
  vec<மரம், va_gc> *v;
  மரம் ret;

  vec_alloc (v, list_length (params));
  க்கு (; params; params = மரம்_CHAIN (params))
    v->quick_தள்ளு (மரம்_மதிப்பு (params));
  ret = c_build_function_call_vec (loc, vNULL, function, v, வெற்று);
  vec_free (v);
  திரும்பு ret;
}

/* Give a note about the location of the declaration of DECL,
   or, failing that, a pertinent declaration for FUNCTION_EXPR.  */

நிலையான வெறுமை
inform_declaration (மரம் decl, மரம் function_கோவை)
{
  எனில் (decl && (மரம்_CODE (decl) != FUNCTION_DECL
	       || !DECL_IS_UNDECLARED_BUILTIN (decl)))
    inform (DECL_SOURCE_LOCATION (decl), "declared here");
  இல்லையெனில் எனில் (function_கோவை)
    தேர்வு (மரம்_CODE (function_கோவை))
      {
      இயல்பு:
	நிறுத்து;
      நிலை COMPONENT_REF:
	/* Show the decl of the pertinent field (e.g. for callback
	   fields in a struct.  */
	{
	  மரம் field_decl = மரம்_OPERAND (function_கோவை, 1);
	  எனில் (location_t loc = DECL_SOURCE_LOCATION (field_decl))
	    inform (loc, "declared here");
	}
	நிறுத்து;
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

மரம்
build_function_call_vec (location_t loc, vec<location_t> arg_loc,
			 மரம் function, vec<மரம், va_gc> *params,
			 vec<மரம், va_gc> *origtypes, மரம் orig_fundecl)
{
  மரம் fntype, fundecl = NULL_மரம்;
  மரம் name = NULL_மரம், result;
  மரம் tem;
  முழு nargs;
  மரம் *argarray;


  /* Strip NON_LVALUE_EXPRs, etc., since we aren't using as an lvalue.  */
  STRIP_TYPE_NOPS (function);

  /* Convert anything with function type to a pointer-to-function.  */
  எனில் (மரம்_CODE (function) == FUNCTION_DECL)
    {
      name = DECL_NAME (function);

      எனில் (flag_tm)
	tm_malloc_replacement (function);
      fundecl = function;
      எனில் (!orig_fundecl)
	orig_fundecl = fundecl;
      /* Atomic functions have type checking/casting already done.  They are
	 often rewritten and don't match the original parameter list.  */
      எனில் (name && startswith (IDENTIFIER_POINTER (name), "__atomic_"))
        origtypes = வெற்று;
    }
  எனில் (மரம்_CODE (மரம்_TYPE (function)) == FUNCTION_TYPE)
    function = function_to_pointer_conversion (loc, function);

  /* For Objective-C, convert any calls via a cast to OBJC_TYPE_REF
     expressions, like those used for ObjC messenger dispatches.  */
  எனில் (params && !params->is_empty ())
    function = objc_rewrite_function_call (function, (*params)[0]);

  function = c_fully_fold (function, பொய், வெற்று);

  fntype = மரம்_TYPE (function);

  எனில் (மரம்_CODE (fntype) == ERROR_MARK)
    திரும்பு error_mark_முனை;

  எனில் (!(மரம்_CODE (fntype) == POINTER_TYPE
	&& மரம்_CODE (மரம்_TYPE (fntype)) == FUNCTION_TYPE))
    {
      எனில் (!flag_diagnostics_show_caret && !STATEMENT_CLASS_P (function))
	error_at (loc,
		  "called object %qE is not a function or function pointer",
		  function);
      இல்லையெனில் எனில் (DECL_P (function))
	{
	  auto_diagnostic_group d;
	  error_at (loc,
		    "called object %qD is not a function or function pointer",
		    function);
	  inform_declaration (function, NULL_மரம்);
	}
      இல்லையெனில்
	error_at (loc,
		  "called object is not a function or function pointer");
      திரும்பு error_mark_முனை;
    }

  எனில் (fundecl && மரம்_THIS_VOLATILE (fundecl))
    current_function_returns_abnormally = 1;

  /* fntype now gets the type of function pointed to.  */
  fntype = மரம்_TYPE (fntype);
  மரம் return_type = மரம்_TYPE (fntype);

  /* Convert the parameters to the types declared in the
     function prototype, or apply default promotions.  */

  nargs = convert_arguments (loc, arg_loc, fntype, params,
			     origtypes, function, fundecl);
  எனில் (nargs < 0)
    திரும்பு error_mark_முனை;

  /* Check that the function is called through a compatible prototype.
     If it is not, warn.  */
  எனில் (CONVERT_கோவை_P (function)
      && மரம்_CODE (tem = மரம்_OPERAND (function, 0)) == ADDR_கோவை
      && மரம்_CODE (tem = மரம்_OPERAND (tem, 0)) == FUNCTION_DECL
      && !comptypes (fntype, மரம்_TYPE (tem)))
    {
      /* This situation leads to run-time undefined behavior.  We can't,
	 therefore, simply error unless we can prove that all possible
	 executions of the program must execute the code.  */
      warning_at (loc, 0, "function called through a non-compatible type");

      எனில் (VOID_TYPE_P (return_type)
	  && TYPE_QUALS (return_type) != TYPE_UNQUALIFIED)
	pedwarn (loc, 0,
		 "function with qualified void return type called");
     }

  argarray = vec_safe_address (params);

  /* Check that arguments to builtin functions match the expectations.  */
  எனில் (fundecl
      && fndecl_built_in_p (fundecl)
      && !check_builtin_function_arguments (loc, arg_loc, fundecl,
					    orig_fundecl, nargs, argarray))
    திரும்பு error_mark_முனை;

  /* Check that the arguments to the function are valid.  */
  தருக்க warned_p = check_function_arguments (loc, fundecl, fntype,
					    nargs, argarray, &arg_loc,
					    comptypes);

  எனில் (TYPE_QUALS (return_type) != TYPE_UNQUALIFIED
      && !VOID_TYPE_P (return_type))
    return_type = c_build_qualified_type (return_type, TYPE_UNQUALIFIED);
  எனில் (name != NULL_மரம்
      && startswith (IDENTIFIER_POINTER (name), "__builtin_"))
    {
      எனில் (require_constant_மதிப்பு)
	result
	  = fold_build_call_array_initializer_loc (loc, return_type,
						   function, nargs, argarray);
      இல்லையெனில்
	result = fold_build_call_array_loc (loc, return_type,
					    function, nargs, argarray);
      எனில் (மரம்_CODE (result) == NOP_கோவை
	  && மரம்_CODE (மரம்_OPERAND (result, 0)) == INTEGER_CST)
	STRIP_TYPE_NOPS (result);
    }
  இல்லையெனில்
    result = build_call_array_loc (loc, return_type,
				   function, nargs, argarray);
  /* If -Wnonnull warning has been diagnosed, avoid diagnosing it again
     later.  */
  எனில் (warned_p && மரம்_CODE (result) == CALL_கோவை)
    suppress_warning (result, OPT_Wnonnull);

  /* In this improbable scenario, a nested function returns a VM type.
     Create a TARGET_EXPR so that the call always has a LHS, much as
     what the C++ FE does for functions returning non-PODs.  */
  எனில் (c_type_variably_modified_p (மரம்_TYPE (fntype)))
    {
      மரம் tmp = create_tmp_var_raw (மரம்_TYPE (fntype));
      result = build4 (TARGET_கோவை, மரம்_TYPE (fntype), tmp, result,
		       NULL_மரம், NULL_மரம்);
    }

  எனில் (VOID_TYPE_P (மரம்_TYPE (result)))
    {
      எனில் (TYPE_QUALS (மரம்_TYPE (result)) != TYPE_UNQUALIFIED)
	pedwarn (loc, 0,
		 "function with qualified void return type called");
      திரும்பு result;
    }
  திரும்பு require_complete_type (loc, result);
}

/* Like build_function_call_vec, but call also resolve_overloaded_builtin.  */

மரம்
c_build_function_call_vec (location_t loc, மாறிலி vec<location_t> &arg_loc,
			   மரம் function, vec<மரம், va_gc> *params,
			   vec<மரம், va_gc> *origtypes)
{
  /* Strip NON_LVALUE_EXPRs, etc., since we aren't using as an lvalue.  */
  STRIP_TYPE_NOPS (function);

  /* Convert anything with function type to a pointer-to-function.  */
  எனில் (மரம்_CODE (function) == FUNCTION_DECL)
    {
      /* Implement type-directed function overloading for builtins.
	 resolve_overloaded_builtin and targetm.resolve_overloaded_builtin
	 handle all the type checking.  The result is a complete expression
	 that implements this function call.  */
      மரம் tem = resolve_overloaded_builtin (loc, function, params);
      எனில் (tem)
	திரும்பு tem;
    }
  திரும்பு build_function_call_vec (loc, arg_loc, function, params, origtypes);
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

நிலையான மரம்
convert_argument (location_t ploc, மரம் function, மரம் fundecl,
		  மரம் type, மரம் origtype, மரம் val, மரம் valtype,
		  தருக்க npc, மரம் rname, முழு parmnum, முழு argnum,
		  தருக்க excess_precision, முழு warnopt)
{
  /* Formal parm type is specified by a function prototype.  */

  எனில் (type == error_mark_முனை || !COMPLETE_TYPE_P (type))
    {
      error_at (ploc, "type of formal parameter %d is incomplete",
		parmnum + 1);
      திரும்பு error_mark_முனை;
    }

  /* Optionally warn about conversions that differ from the default
     conversions.  */
  எனில் (warn_traditional_conversion || warn_traditional)
    {
      எனில் (INTEGRAL_TYPE_P (type)
	  && SCALAR_FLOAT_TYPE_P (valtype))
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as integer rather "
		    "than floating due to prototype",
		    argnum, rname);
      எனில் (INTEGRAL_TYPE_P (type)
	  && மரம்_CODE (valtype) == COMPLEX_TYPE)
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as integer rather "
		    "than complex due to prototype",
		    argnum, rname);
      இல்லையெனில் எனில் (மரம்_CODE (type) == COMPLEX_TYPE
	       && SCALAR_FLOAT_TYPE_P (valtype))
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as complex rather "
		    "than floating due to prototype",
		    argnum, rname);
      இல்லையெனில் எனில் (SCALAR_FLOAT_TYPE_P (type)
	       && INTEGRAL_TYPE_P (valtype))
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as floating rather "
		    "than integer due to prototype",
		    argnum, rname);
      இல்லையெனில் எனில் (மரம்_CODE (type) == COMPLEX_TYPE
	       && INTEGRAL_TYPE_P (valtype))
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as complex rather "
		    "than integer due to prototype",
		    argnum, rname);
      இல்லையெனில் எனில் (SCALAR_FLOAT_TYPE_P (type)
	       && மரம்_CODE (valtype) == COMPLEX_TYPE)
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as floating rather "
		    "than complex due to prototype",
		    argnum, rname);
      /* ??? At some point, messages should be written about
	 conversions between complex types, but that's too messy
	 to do now.  */
      இல்லையெனில் எனில் (SCALAR_FLOAT_TYPE_P (type)
	       && SCALAR_FLOAT_TYPE_P (valtype))
	{
	  unsigned முழு formal_prec = TYPE_PRECISION (type);

	  /* Warn if any argument is passed as `float',
	     since without a prototype it would be `double'.  */
	  எனில் (formal_prec == TYPE_PRECISION (float_type_முனை)
	      && type != dfloat32_type_முனை)
	    warning_at (ploc, 0,
			"passing argument %d of %qE as %<float%> "
			"rather than %<double%> due to prototype",
			argnum, rname);

	  /* Warn if mismatch between argument and prototype
	     for decimal float types.  Warn of conversions with
	     binary float types and of precision narrowing due to
	     prototype.  */
	  இல்லையெனில் எனில் (type != valtype
		   && (type == dfloat32_type_முனை
		       || type == dfloat64_type_முனை
		       || type == dfloat128_type_முனை
		       || valtype == dfloat32_type_முனை
		       || valtype == dfloat64_type_முனை
		       || valtype == dfloat128_type_முனை)
		   && (formal_prec
		       <= TYPE_PRECISION (valtype)
		       || (type == dfloat128_type_முனை
			   && (valtype
			       != dfloat64_type_முனை
			       && (valtype
				   != dfloat32_type_முனை)))
		       || (type == dfloat64_type_முனை
			   && (valtype
			       != dfloat32_type_முனை))))
	    warning_at (ploc, 0,
			"passing argument %d of %qE as %qT "
			"rather than %qT due to prototype",
			argnum, rname, type, valtype);

	}
      /* Detect integer changing in width or signedness.
	 These warnings are only activated with
	 -Wtraditional-conversion, not with -Wtraditional.  */
      இல்லையெனில் எனில் (warn_traditional_conversion
	       && INTEGRAL_TYPE_P (type)
	       && INTEGRAL_TYPE_P (valtype))
	{
	  unsigned முழு formal_prec = TYPE_PRECISION (type);
	  மரம் would_have_been = default_conversion (val);
	  மரம் type1 = மரம்_TYPE (would_have_been);

	  எனில் (val == error_mark_முனை)
	    /* VAL could have been of incomplete type.  */;
	  இல்லையெனில் எனில் (மரம்_CODE (type) == ENUMERAL_TYPE
		   && (TYPE_MAIN_VARIANT (type)
		       == TYPE_MAIN_VARIANT (valtype)))
	    /* No warning if function asks for enum
	       and the actual arg is that enum type.  */
	    ;
	  இல்லையெனில் எனில் (formal_prec != TYPE_PRECISION (type1))
	    warning_at (ploc, OPT_Wtraditional_conversion,
			"passing argument %d of %qE "
			"with different width due to prototype",
			argnum, rname);
	  இல்லையெனில் எனில் (TYPE_UNSIGNED (type) == TYPE_UNSIGNED (type1))
	    ;
	  /* Don't complain if the formal parameter type
	     is an enum, because we can't tell now whether
	     the value was an enum--even the same enum.  */
	  இல்லையெனில் எனில் (மரம்_CODE (type) == ENUMERAL_TYPE)
	    ;
	  இல்லையெனில் எனில் (மரம்_CODE (val) == INTEGER_CST
		   && int_fits_type_p (val, type))
	    /* Change in signedness doesn't matter
	       if a constant value is unaffected.  */
	    ;
	  /* If the value is extended from a narrower
	     unsigned type, it doesn't matter whether we
	     pass it as signed or unsigned; the value
	     certainly is the same either way.  */
	  இல்லையெனில் எனில் (TYPE_PRECISION (valtype) < TYPE_PRECISION (type)
		   && TYPE_UNSIGNED (valtype))
	    ;
	  இல்லையெனில் எனில் (TYPE_UNSIGNED (type))
	    warning_at (ploc, OPT_Wtraditional_conversion,
			"passing argument %d of %qE "
			"as unsigned due to prototype",
			argnum, rname);
	  இல்லையெனில்
	    warning_at (ploc, OPT_Wtraditional_conversion,
			"passing argument %d of %qE "
			"as signed due to prototype",
			argnum, rname);
	}
    }

  /* Possibly restore an EXCESS_PRECISION_EXPR for the
     sake of better warnings from convert_and_check.  */
  எனில் (excess_precision)
    val = build1 (EXCESS_PRECISION_கோவை, valtype, val);

  மரம் parmval = convert_for_assignment (ploc, ploc, type,
					 val, origtype, ic_argpass,
					 npc, fundecl, function,
					 parmnum + 1, warnopt);
  திரும்பு parmval;
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

நிலையான முழு
convert_arguments (location_t loc, vec<location_t> arg_loc, மரம் fntype,
		   vec<மரம், va_gc> *மதிப்புகள், vec<மரம், va_gc> *origtypes,
		   மரம் function, மரம் fundecl)
{
  மரம் typelist = TYPE_ARG_TYPES (fntype);
  unsigned முழு parmnum;
  தருக்க error_args = பொய்;
  மாறிலி தருக்க type_generic = fundecl
    && lookup_attribute ("type generic", TYPE_ATTRIBUTES (மரம்_TYPE (fundecl)));
  தருக்க type_generic_remove_excess_precision = பொய்;
  தருக்க type_generic_overflow_p = பொய்;
  தருக்க type_generic_bit_query = பொய்;
  மரம் selector;

  /* Change pointer to function to the function itself for
     diagnostics.  */
  எனில் (மரம்_CODE (function) == ADDR_கோவை
      && மரம்_CODE (மரம்_OPERAND (function, 0)) == FUNCTION_DECL)
    function = மரம்_OPERAND (function, 0);

  /* Handle an ObjC selector specially for diagnostics.  */
  selector = objc_message_selector ();

  /* For a call to a built-in function declared without a prototype,
     set to the built-in function's argument list.  */
  மரம் builtin_typelist = NULL_மரம்;

  /* For type-generic built-in functions, determine whether excess
     precision should be removed (classification) or not
     (comparison).  */
  எனில் (fundecl
      && fndecl_built_in_p (fundecl, BUILT_IN_NORMAL))
    {
      built_in_function code = DECL_FUNCTION_CODE (fundecl);
      எனில் (C_DECL_BUILTIN_PROTOTYPE (fundecl))
	{
	  /* For a call to a built-in function declared without a prototype
	     use the types of the parameters of the internal built-in to
	     match those of the arguments to.  */
	  எனில் (மரம் bdecl = builtin_decl_explicit (code))
	    builtin_typelist = TYPE_ARG_TYPES (மரம்_TYPE (bdecl));
	}

      /* For type-generic built-in functions, determine whether excess
	 precision should be removed (classification) or not
	 (comparison).  */
      எனில் (type_generic)
	தேர்வு (code)
	  {
	  நிலை BUILT_IN_ISFINITE:
	  நிலை BUILT_IN_ISINF:
	  நிலை BUILT_IN_ISINF_SIGN:
	  நிலை BUILT_IN_ISNAN:
	  நிலை BUILT_IN_ISNORMAL:
	  நிலை BUILT_IN_ISSIGNALING:
	  நிலை BUILT_IN_FPCLASSIFY:
	    type_generic_remove_excess_precision = உண்மை;
	    நிறுத்து;

	  நிலை BUILT_IN_ADD_OVERFLOW_P:
	  நிலை BUILT_IN_SUB_OVERFLOW_P:
	  நிலை BUILT_IN_MUL_OVERFLOW_P:
	    /* The last argument of these type-generic builtins
	       should not be promoted.  */
	    type_generic_overflow_p = உண்மை;
	    நிறுத்து;

	  நிலை BUILT_IN_CLZG:
	  நிலை BUILT_IN_CTZG:
	  நிலை BUILT_IN_CLRSBG:
	  நிலை BUILT_IN_FFSG:
	  நிலை BUILT_IN_PARITYG:
	  நிலை BUILT_IN_POPCOUNTG:
	    /* The first argument of these type-generic builtins
	       should not be promoted.  */
	    type_generic_bit_query = உண்மை;
	    நிறுத்து;

	  இயல்பு:
	    நிறுத்து;
	  }
    }

  /* Scan the given expressions (VALUES) and types (TYPELIST), producing
     individual converted arguments.  */

  மரம் typetail, builtin_typetail, val;
  க்கு (typetail = typelist,
	 builtin_typetail = builtin_typelist,
	 parmnum = 0;
       மதிப்புகள் && மதிப்புகள்->iterate (parmnum, &val);
       ++parmnum)
    {
      /* The type of the function parameter (if it was declared with one).  */
      மரம் type = typetail ? மரம்_மதிப்பு (typetail) : NULL_மரம்;
      /* The type of the built-in function parameter (if the function
	 is a built-in).  Used to detect type incompatibilities in
	 calls to built-ins declared without a prototype.  */
      மரம் builtin_type = (builtin_typetail
			   ? மரம்_மதிப்பு (builtin_typetail) : NULL_மரம்);
      /* The original type of the argument being passed to the function.  */
      மரம் valtype = மரம்_TYPE (val);
      /* The called function (or function selector in Objective C).  */
      மரம் rname = function;
      முழு argnum = parmnum + 1;
      மாறிலி எழுத்து *invalid_func_diag;
      /* Set for EXCESS_PRECISION_EXPR arguments.  */
      தருக்க excess_precision = பொய்;
      /* The value of the argument after conversion to the type
	 of the function parameter it is passed to.  */
      மரம் parmval;
      /* Some __atomic_* builtins have additional hidden argument at
	 position 0.  */
      location_t ploc
	= !arg_loc.is_empty () && மதிப்புகள்->length () == arg_loc.length ()
	  ? expansion_point_location_if_in_system_header (arg_loc[parmnum])
	  : உள்ளீடு_location;

      எனில் (type == void_type_முனை)
	{
	  auto_diagnostic_group d;
	  முழு இலக்கம்_expected = parmnum;
	  முழு இலக்கம்_actual = மதிப்புகள்->length ();
	  gcc_rich_location rich_loc (loc);
	  எனில் (ploc != உள்ளீடு_location)
	    rich_loc.add_range (ploc);
	  எனில் (selector)
	    error_at (&rich_loc,
		      "too many arguments to method %qE; expected %i, have %i",
		      selector, இலக்கம்_expected, இலக்கம்_actual);
	  இல்லையெனில்
	    error_at (&rich_loc,
		      "too many arguments to function %qE; expected %i, have %i",
		      function, இலக்கம்_expected, இலக்கம்_actual);
	  inform_declaration (fundecl, function);
	  திரும்பு error_args ? -1 : (முழு) parmnum;
	}

      எனில் (builtin_type == void_type_முனை)
	{
	  auto_diagnostic_group d;
	  எனில் (warning_at (loc, OPT_Wbuiltin_declaration_mismatch,
			  "too many arguments to built-in function %qE "
			  "expecting %d", function, parmnum))
	    inform_declaration (fundecl, function);
	  builtin_typetail = NULL_மரம்;
	}

      எனில் (!typetail && parmnum == 0 && !TYPE_NO_NAMED_ARGS_STDARG_P (fntype)
	  && !(fundecl && fndecl_built_in_p (fundecl)))
	{
	  auto_diagnostic_group d;
	  தருக்க warned;
	  எனில் (selector)
	    warned = warning_at (loc, OPT_Wdeprecated_non_prototype,
				 "ISO C23 does not allow arguments"
				 " for method %qE declared without parameters",
				 function);
	  இல்லையெனில்
	    warned = warning_at (loc, OPT_Wdeprecated_non_prototype,
				 "ISO C23 does not allow arguments"
				 " for function %qE declared without parameters",
				 function);
	  எனில் (warned)
	    inform_declaration (fundecl, function);
	}

      எனில் (selector && argnum > 2)
	{
	  rname = selector;
	  argnum -= 2;
	}

      /* Determine if VAL is a null pointer constant before folding it.  */
      தருக்க npc = null_pointer_constant_p (val);

      /* If there is excess precision and a prototype, convert once to
	 the required type rather than converting via the semantic
	 type.  Likewise without a prototype a float value represented
	 as long double should be converted once to double.  But for
	 type-generic classification functions excess precision must
	 be removed here.  */
      எனில் (மரம்_CODE (val) == EXCESS_PRECISION_கோவை
	  && (type || !type_generic || !type_generic_remove_excess_precision))
	{
	  val = மரம்_OPERAND (val, 0);
	  excess_precision = உண்மை;
	}
      val = c_fully_fold (val, பொய், வெற்று);
      STRIP_TYPE_NOPS (val);

      val = require_complete_type (ploc, val);

      /* Some floating-point arguments must be promoted to double when
	 no type is specified by a prototype.  This applies to
	 arguments of type float, and to architecture-specific types
	 (ARM __fp16), but not to _FloatN or _FloatNx types.  */
      தருக்க promote_float_arg = பொய்;
      எனில் (type == NULL_மரம்
	  && மரம்_CODE (valtype) == REAL_TYPE
	  && (TYPE_PRECISION (valtype)
	      <= TYPE_PRECISION (double_type_முனை))
	  && TYPE_MAIN_VARIANT (valtype) != double_type_முனை
	  && TYPE_MAIN_VARIANT (valtype) != long_double_type_முனை
	  && !DECIMAL_FLOAT_MODE_P (TYPE_MODE (valtype)))
	{
	  /* Promote this argument, unless it has a _FloatN or
	     _FloatNx type.  */
	  promote_float_arg = உண்மை;
	  க்கு (முழு i = 0; i < இலக்கம்_FLOATN_NX_TYPES; i++)
	    எனில் (TYPE_MAIN_VARIANT (valtype) == FLOATN_NX_TYPE_முனை (i))
	      {
		promote_float_arg = பொய்;
		நிறுத்து;
	      }
	  /* Don't promote __bf16 either.  */
	  எனில் (TYPE_MAIN_VARIANT (valtype) == bfloat16_type_முனை)
	    promote_float_arg = பொய்;
	}

      எனில் (type != NULL_மரம்)
	{
	  மரம் origtype = (!origtypes) ? NULL_மரம் : (*origtypes)[parmnum];
	  parmval = convert_argument (ploc, function, fundecl, type, origtype,
				      val, valtype, npc, rname, parmnum, argnum,
				      excess_precision, 0);
	}
      /* A NULLPTR type is just a nullptr always.  */
      இல்லையெனில் எனில் (மரம்_CODE (மரம்_TYPE (val)) == NULLPTR_TYPE)
	parmval = omit_one_operand_loc (ploc, மரம்_TYPE (val), nullptr_முனை, val);
      இல்லையெனில் எனில் (promote_float_arg)
        {
	  எனில் (type_generic)
	    parmval = val;
	  இல்லையெனில்
	    {
	      /* Convert `float' to `double'.  */
	      எனில் (warn_double_promotion && !c_inhibit_evaluation_warnings)
		warning_at (ploc, OPT_Wdouble_promotion,
			    "implicit conversion from %qT to %qT when passing "
			    "argument to function",
			    valtype, double_type_முனை);
	      parmval = convert (double_type_முனை, val);
	    }
	}
      இல்லையெனில் எனில் ((excess_precision && !type_generic)
	       || (type_generic_overflow_p && parmnum == 2)
	       || (type_generic_bit_query && parmnum == 0))
	/* A "double" argument with excess precision being passed
	   without a prototype or in variable arguments.
	   The last argument of __builtin_*_overflow_p should not be
	   promoted, similarly the first argument of
	   __builtin_{clz,ctz,clrsb,ffs,parity,popcount}g.  */
	parmval = convert (valtype, val);
      இல்லையெனில் எனில் ((invalid_func_diag =
		targetm.calls.invalid_arg_for_unprototyped_fn (typelist, fundecl, val)))
	{
	  error (invalid_func_diag);
	  திரும்பு -1;
	}
      இல்லையெனில் எனில் (மரம்_CODE (val) == ADDR_கோவை && reject_gcc_builtin (val))
	{
	  திரும்பு -1;
	}
      இல்லையெனில்
	/* Convert `short' and `char' to full-size `int'.  */
	parmval = default_conversion (val);

      (*மதிப்புகள்)[parmnum] = parmval;
      எனில் (parmval == error_mark_முனை)
	error_args = உண்மை;

      எனில் (!type && builtin_type && மரம்_CODE (builtin_type) != VOID_TYPE)
	{
	  /* For a call to a built-in function declared without a prototype,
	     perform the conversions from the argument to the expected type
	     but issue warnings rather than errors for any mismatches.
	     Ignore the converted argument and use the PARMVAL obtained
	     above by applying default conversions instead.  */
	  மரம் origtype = (!origtypes) ? NULL_மரம் : (*origtypes)[parmnum];
	  convert_argument (ploc, function, fundecl, builtin_type, origtype,
			    val, valtype, npc, rname, parmnum, argnum,
			    excess_precision,
			    OPT_Wbuiltin_declaration_mismatch);
	}

      எனில் (typetail)
	typetail = மரம்_CHAIN (typetail);

      எனில் (builtin_typetail)
	builtin_typetail = மரம்_CHAIN (builtin_typetail);
    }

  gcc_assert (parmnum == vec_safe_length (மதிப்புகள்));

  எனில் (typetail != NULL_மரம் && மரம்_மதிப்பு (typetail) != void_type_முனை)
    {
      /* Not enough args.
	 Determine minimum number of arguments required.  */
      முழு min_expected_இலக்கம் = 0;
      தருக்க at_least_p = பொய்;
      மரம் iter = typelist;
      போது (உண்மை)
	{
	  எனில் (!iter)
	    {
	      /* Variadic arguments; stop iterating.  */
	      at_least_p = உண்மை;
	      நிறுத்து;
	    }
	  எனில் (iter == void_list_முனை)
	    /* End of arguments; stop iterating.  */
	    நிறுத்து;
	  ++min_expected_இலக்கம்;
	  iter = மரம்_CHAIN (iter);
	}
      auto_diagnostic_group d;
      முழு actual_இலக்கம் = vec_safe_length (மதிப்புகள்);
      error_at (loc,
		at_least_p
		? G_("too few arguments to function %qE; expected at least %i, have %i")
		: G_("too few arguments to function %qE; expected %i, have %i"),
		function, min_expected_இலக்கம், actual_இலக்கம்);
      inform_declaration (fundecl, function);
      திரும்பு -1;
    }

  எனில் (builtin_typetail && மரம்_மதிப்பு (builtin_typetail) != void_type_முனை)
    {
      unsigned nargs = parmnum;
      க்கு (மரம் t = builtin_typetail; t; t = மரம்_CHAIN (t))
	++nargs;

      auto_diagnostic_group d;
      எனில் (warning_at (loc, OPT_Wbuiltin_declaration_mismatch,
		      "too few arguments to built-in function %qE "
		      "expecting %u", function, nargs - 1))
	inform_declaration (fundecl, function);
    }

  திரும்பு error_args ? -1 : (முழு) parmnum;
}

/* This is the entry point used by the parser to build unary operators
   in the input.  CODE, a tree_code, specifies the unary operator, and
   ARG is the operand.  For unary plus, the C parser currently uses
   CONVERT_EXPR for code.

   LOC is the location to use for the tree generated.
*/

கட்டமைப்பு c_கோவை
parser_build_unary_op (location_t loc, எண்ணிக்கை மரம்_code code, கட்டமைப்பு c_கோவை arg)
{
  கட்டமைப்பு c_கோவை result;

  result.original_code = code;
  result.original_type = வெற்று;
  result.m_decimal = 0;

  எனில் (reject_gcc_builtin (arg.மதிப்பு))
    {
      result.மதிப்பு = error_mark_முனை;
    }
  இல்லையெனில்
    {
      result.மதிப்பு = build_unary_op (loc, code, arg.மதிப்பு, பொய்);

      எனில் (மரம்_OVERFLOW_P (result.மதிப்பு) && !மரம்_OVERFLOW_P (arg.மதிப்பு))
	overflow_warning (loc, result.மதிப்பு, arg.மதிப்பு);
    }

  /* We are typically called when parsing a prefix token at LOC acting on
     ARG.  Reflect this by updating the source range of the result to
     start at LOC and end at the end of ARG.  */
  set_c_கோவை_source_range (&result,
			   loc, arg.get_finish ());

  திரும்பு result;
}

/* Returns true if TYPE is a character type, *not* including wchar_t.  */

தருக்க
char_type_p (மரம் type)
{
  திரும்பு (type == char_type_முனை
	  || type == unsigned_char_type_முனை
	  || type == signed_char_type_முனை
	  || type == char16_type_முனை
	  || type == char32_type_முனை);
}

/* This is the entry point used by the parser to build binary operators
   in the input.  CODE, a tree_code, specifies the binary operator, and
   ARG1 and ARG2 are the operands.  In addition to constructing the
   expression, we check for operands that were written with other binary
   operators in a way that is likely to confuse the user.  ORIG_ARG1 is
   the original first operand for TRUTH_{AND,OR}IF_EXPR before it is
   converted to truth value, otherwise NULL_TREE.

   LOCATION is the location of the binary operator.  */

கட்டமைப்பு c_கோவை
parser_build_இருமம்_op (location_t location, எண்ணிக்கை மரம்_code code,
			கட்டமைப்பு c_கோவை arg1, கட்டமைப்பு c_கோவை arg2, மரம் orig_arg1)
{
  கட்டமைப்பு c_கோவை result;
  result.m_decimal = 0;

  எண்ணிக்கை மரம்_code code1 = arg1.original_code;
  எண்ணிக்கை மரம்_code code2 = arg2.original_code;
  மரம் type1 = (arg1.original_type
                ? arg1.original_type
                : மரம்_TYPE (arg1.மதிப்பு));
  மரம் type2 = (arg2.original_type
                ? arg2.original_type
                : மரம்_TYPE (arg2.மதிப்பு));

  result.மதிப்பு = build_இருமம்_op (location, code,
				  arg1.மதிப்பு, arg2.மதிப்பு, உண்மை);
  result.original_code = code;
  result.original_type = வெற்று;
  result.m_decimal = 0;

  எனில் (மரம்_CODE (result.மதிப்பு) == ERROR_MARK)
    {
      set_c_கோவை_source_range (&result,
			       arg1.get_start (),
			       arg2.get_finish ());
      திரும்பு result;
    }

  எனில் (location != UNKNOWN_LOCATION)
    protected_set_கோவை_location (result.மதிப்பு, location);

  set_c_கோவை_source_range (&result,
			   arg1.get_start (),
			   arg2.get_finish ());

  /* Check for cases such as x+y<<z which users are likely
     to misinterpret.  */
  எனில் (warn_parentheses)
    warn_about_parentheses (location, code, code1, arg1.மதிப்பு, code2,
			    arg2.மதிப்பு);

  எனில் (warn_logical_op)
    warn_logical_operator (location, code, மரம்_TYPE (result.மதிப்பு),
			   code1, arg1.மதிப்பு, code2, arg2.மதிப்பு);

  எனில் (warn_constant_logical_operand
      && (code == TRUTH_ANDIF_கோவை || code == TRUTH_ORIF_கோவை)
      && INTEGRAL_NB_TYPE_P (type1)
      && INTEGRAL_NB_TYPE_P (type2))
    {
      மாறிலி எழுத்து *name = code == TRUTH_ANDIF_கோவை ? "&&" : "||";
      எனில் (orig_arg1 == NULL_மரம்)
	orig_arg1 = arg1.மதிப்பு;
      auto enum_other_than_0_1 = [] (மரம் type) {
	எனில் (மரம்_CODE (type) != ENUMERAL_TYPE)
	  திரும்பு பொய்;
	க்கு (மரம் l = TYPE_மதிப்புகள் (type); l; l = மரம்_CHAIN (l))
	  {
	    மரம் v = DECL_INITIAL (மரம்_மதிப்பு (l));
	    எனில் (!integer_zerop (v) && !integer_onep (v))
	      திரும்பு உண்மை;
	  }
	திரும்பு பொய்;
      };
      auto diagnose_constant_logical_operand = [=] (மரம் val, மரம் type) {
	எனில் (மரம்_CODE (val) != INTEGER_CST || integer_zerop (val))
	  திரும்பு பொய்;
	எனில் (integer_onep (val) && !enum_other_than_0_1 (type))
	  திரும்பு பொய்;
	gcc_rich_location richloc (location);
	richloc.add_fixit_replace (name + 1);
	auto_diagnostic_group d;
	எனில் (warning_at (location, OPT_Wconstant_logical_operand,
			"use of logical %qs with constant operand %qE",
			name, val))
	  inform (&richloc, "use %qs for bitwise operation", name + 1);
	திரும்பு உண்மை;
      };
      எனில் (!diagnose_constant_logical_operand (arg2.மதிப்பு, type2))
	diagnose_constant_logical_operand (orig_arg1, type1);
    }

  எனில் (warn_tautological_compare)
    {
      மரம் lhs = arg1.மதிப்பு;
      மரம் rhs = arg2.மதிப்பு;
      எனில் (மரம்_CODE (lhs) == C_MAYBE_CONST_கோவை)
	{
	  எனில் (C_MAYBE_CONST_கோவை_PRE (lhs) != NULL_மரம்
	      && மரம்_SIDE_EFFECTS (C_MAYBE_CONST_கோவை_PRE (lhs)))
	    lhs = NULL_மரம்;
	  இல்லையெனில்
	    lhs = C_MAYBE_CONST_கோவை_கோவை (lhs);
	}
      எனில் (மரம்_CODE (rhs) == C_MAYBE_CONST_கோவை)
	{
	  எனில் (C_MAYBE_CONST_கோவை_PRE (rhs) != NULL_மரம்
	      && மரம்_SIDE_EFFECTS (C_MAYBE_CONST_கோவை_PRE (rhs)))
	    rhs = NULL_மரம்;
	  இல்லையெனில்
	    rhs = C_MAYBE_CONST_கோவை_கோவை (rhs);
	}
      எனில் (lhs != NULL_மரம் && rhs != NULL_மரம்)
	warn_tautological_cmp (location, code, lhs, rhs);
    }

  எனில் (warn_logical_not_paren
      && மரம்_CODE_CLASS (code) == tcc_comparison
      && code1 == TRUTH_NOT_கோவை
      && code2 != TRUTH_NOT_கோவை
      /* Avoid warning for !!x == y.  */
      && (மரம்_CODE (arg1.மதிப்பு) != NE_கோவை
	  || !integer_zerop (மரம்_OPERAND (arg1.மதிப்பு, 1))))
    {
      /* Avoid warning for !b == y where b has _Bool type.  */
      மரம் t = integer_zero_முனை;
      எனில் (மரம்_CODE (arg1.மதிப்பு) == EQ_கோவை
	  && integer_zerop (மரம்_OPERAND (arg1.மதிப்பு, 1))
	  && மரம்_TYPE (மரம்_OPERAND (arg1.மதிப்பு, 0)) == integer_type_முனை)
	{
	  t = மரம்_OPERAND (arg1.மதிப்பு, 0);
	  செய்
	    {
	      எனில் (மரம்_TYPE (t) != integer_type_முனை)
		நிறுத்து;
	      எனில் (மரம்_CODE (t) == C_MAYBE_CONST_கோவை)
		t = C_MAYBE_CONST_கோவை_கோவை (t);
	      இல்லையெனில் எனில் (CONVERT_கோவை_P (t))
		t = மரம்_OPERAND (t, 0);
	      இல்லையெனில்
		நிறுத்து;
	    }
	  போது (1);
	}
      எனில் (!C_BOOLEAN_TYPE_P (மரம்_TYPE (t)))
	warn_logical_not_parentheses (location, code, arg1.மதிப்பு, arg2.மதிப்பு);
    }

  /* Warn about comparisons against string literals, with the exception
     of testing for equality or inequality of a string literal with NULL.  */
  எனில் (code == EQ_கோவை || code == NE_கோவை)
    {
      எனில் ((code1 == STRING_CST
	   && !integer_zerop (மரம்_strip_nop_conversions (arg2.மதிப்பு)))
	  || (code2 == STRING_CST
	      && !integer_zerop (மரம்_strip_nop_conversions (arg1.மதிப்பு))))
	warning_at (location, OPT_Waddress,
		    "comparison with string literal results in unspecified behavior");
      /* Warn for ptr == '\0', it's likely that it should've been ptr[0].  */
      எனில் (POINTER_TYPE_P (type1)
	  && null_pointer_constant_p (arg2.மதிப்பு)
	  && char_type_p (type2))
	{
	  auto_diagnostic_group d;
	  எனில் (warning_at (location, OPT_Wpointer_compare,
			    "comparison between pointer and zero character "
			    "constant"))
	    inform (arg1.get_start (),
		      "did you mean to dereference the pointer?");
	}
      இல்லையெனில் எனில் (POINTER_TYPE_P (type2)
	       && null_pointer_constant_p (arg1.மதிப்பு)
	       && char_type_p (type1))
	{
	  auto_diagnostic_group d;
	  எனில் (warning_at (location, OPT_Wpointer_compare,
			    "comparison between pointer and zero character "
			    "constant"))
	    inform (arg2.get_start (),
		      "did you mean to dereference the pointer?");
	}
    }
  இல்லையெனில் எனில் (மரம்_CODE_CLASS (code) == tcc_comparison
	   && (code1 == STRING_CST || code2 == STRING_CST))
    warning_at (location, OPT_Waddress,
		"comparison with string literal results in unspecified "
		"behavior");

  எனில் (warn_zero_as_null_pointer_constant
      && c_inhibit_evaluation_warnings == 0
      && மரம்_CODE_CLASS (code) == tcc_comparison)
    {
      எனில் ((மரம்_CODE (type1) == POINTER_TYPE
	   || மரம்_CODE (type1) == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type2)
	  && null_pointer_constant_p (arg2.மதிப்பு))
	warning_at (arg2.get_location(), OPT_Wzero_as_null_pointer_constant,
		    "zero as null pointer constant");

      எனில் ((மரம்_CODE (type2) == POINTER_TYPE
	   || மரம்_CODE (type2) == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type1)
	  && null_pointer_constant_p (arg1.மதிப்பு))
	warning_at (arg1.get_location(), OPT_Wzero_as_null_pointer_constant,
		    "zero as null pointer constant");
    }

  எனில் (warn_array_compare
      && மரம்_CODE_CLASS (code) == tcc_comparison
      && மரம்_CODE (type1) == ARRAY_TYPE
      && மரம்_CODE (type2) == ARRAY_TYPE)
    do_warn_array_compare (location, code, arg1.மதிப்பு, arg2.மதிப்பு);

  எனில் (மரம்_OVERFLOW_P (result.மதிப்பு)
      && !மரம்_OVERFLOW_P (arg1.மதிப்பு)
      && !மரம்_OVERFLOW_P (arg2.மதிப்பு))
    overflow_warning (location, result.மதிப்பு);

  /* Warn about comparisons of different enum types.  */
  எனில் (warn_enum_compare
      && மரம்_CODE_CLASS (code) == tcc_comparison
      && மரம்_CODE (type1) == ENUMERAL_TYPE
      && மரம்_CODE (type2) == ENUMERAL_TYPE
      && TYPE_MAIN_VARIANT (type1) != TYPE_MAIN_VARIANT (type2))
    warning_at (location, OPT_Wenum_compare,
		"comparison between %qT and %qT",
		type1, type2);

  எனில் (warn_xor_used_as_pow
      && code == BIT_XOR_கோவை
      && arg1.m_decimal
      && arg2.m_decimal)
    check_for_xor_used_as_pow (arg1.get_location (), arg1.மதிப்பு,
			       location,
			       arg2.get_location (), arg2.மதிப்பு);

  திரும்பு result;
}

/* Return a tree for the difference of pointers OP0 and OP1.
   The resulting tree has type ptrdiff_t.  If POINTER_SUBTRACT sanitization is
   enabled, assign to INSTRUMENT_EXPR call to libsanitizer.  */

நிலையான மரம்
pointer_diff (location_t loc, மரம் op0, மரம் op1, மரம் *instrument_கோவை)
{
  மரம் restype = ptrdiff_type_முனை;
  மரம் result, inttype;

  addr_space_t as0 = TYPE_ADDR_SPACE (மரம்_TYPE (மரம்_TYPE (op0)));
  addr_space_t as1 = TYPE_ADDR_SPACE (மரம்_TYPE (மரம்_TYPE (op1)));
  மரம் target_type = மரம்_TYPE (மரம்_TYPE (op0));
  மரம் orig_op0 = op0;
  மரம் orig_op1 = op1;

  /* If the operands point into different address spaces, we need to
     explicitly convert them to pointers into the common address space
     before we can subtract the numerical address values.  */
  எனில் (as0 != as1)
    {
      addr_space_t as_common;
      மரம் common_type;

      /* Determine the common superset address space.  This is guaranteed
	 to exist because the caller verified that comp_target_types
	 returned non-zero.  */
      எனில் (!addr_space_superset (as0, as1, &as_common))
	gcc_unreachable ();

      common_type = common_pointer_type (மரம்_TYPE (op0), மரம்_TYPE (op1), NULL_மரம்);
      op0 = convert (common_type, op0);
      op1 = convert (common_type, op1);
    }

  /* Determine integer type result of the subtraction.  This will usually
     be the same as the result type (ptrdiff_t), but may need to be a wider
     type if pointers for the address space are wider than ptrdiff_t.  */
  எனில் (TYPE_PRECISION (restype) < TYPE_PRECISION (மரம்_TYPE (op0)))
    inttype = c_common_type_for_size (TYPE_PRECISION (மரம்_TYPE (op0)), 0);
  இல்லையெனில்
    inttype = restype;

  எனில் (VOID_TYPE_P (target_type))
    pedwarn (loc, OPT_Wpointer_arith,
	     "pointer of type %<void *%> used in subtraction");
  எனில் (மரம்_CODE (target_type) == FUNCTION_TYPE)
    pedwarn (loc, OPT_Wpointer_arith,
	     "pointer to a function used in subtraction");

  எனில் (current_function_decl != NULL_மரம்
      && sanitize_flags_p (SANITIZE_POINTER_SUBTRACT))
    {
      op0 = save_கோவை (c_fully_fold (op0, பொய், வெற்று));
      op1 = save_கோவை (c_fully_fold (op1, பொய், வெற்று));

      மரம் tt = builtin_decl_explicit (BUILT_IN_ASAN_POINTER_SUBTRACT);
      *instrument_கோவை = build_call_கோவை_loc (loc, tt, 2, op0, op1);
    }

  /* First do the subtraction, then build the divide operator
     and only convert at the very end.
     Do not do default conversions in case restype is a short type.  */

  /* POINTER_DIFF_EXPR requires a signed integer type of the same size as
     pointers.  If some platform cannot provide that, or has a larger
     ptrdiff_type to support differences larger than half the address
     space, cast the pointers to some larger integer type and do the
     computations in that type.  */
  எனில் (TYPE_PRECISION (inttype) > TYPE_PRECISION (மரம்_TYPE (op0)))
    op0 = build_இருமம்_op (loc, MINUS_கோவை, convert (inttype, op0),
			   convert (inttype, op1), பொய்);
  இல்லையெனில்
    {
      /* Cast away qualifiers.  */
      op0 = convert (c_common_type (மரம்_TYPE (op0), மரம்_TYPE (op0)), op0);
      op1 = convert (c_common_type (மரம்_TYPE (op1), மரம்_TYPE (op1)), op1);
      op0 = build2_loc (loc, POINTER_DIFF_கோவை, inttype, op0, op1);
    }

  /* This generates an error if op1 is pointer to incomplete type.  */
  எனில் (!COMPLETE_OR_VOID_TYPE_P (மரம்_TYPE (மரம்_TYPE (orig_op1))))
    error_at (loc, "arithmetic on pointer to an incomplete type");
  இல்லையெனில் எனில் (verify_type_context (loc, TCTX_POINTER_ARITH,
				மரம்_TYPE (மரம்_TYPE (orig_op0))))
    verify_type_context (loc, TCTX_POINTER_ARITH,
			 மரம்_TYPE (மரம்_TYPE (orig_op1)));

  op1 = c_size_in_bytes (target_type);

  எனில் (pointer_to_zero_sized_aggr_p (மரம்_TYPE (orig_op1)))
    error_at (loc, "arithmetic on pointer to an empty aggregate");

  /* Divide by the size, in easiest possible way.  */
  result = fold_build2_loc (loc, EXACT_DIV_கோவை, inttype,
			    op0, convert (inttype, op1));

  /* Convert to final result type if necessary.  */
  திரும்பு convert (restype, result);
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

நிலையான மரம்
build_atomic_assign (location_t loc, மரம் lhs, எண்ணிக்கை மரம்_code modifycode,
		     மரம் rhs, தருக்க return_old_p)
{
  மரம் fndecl, func_call;
  vec<மரம், va_gc> *params;
  மரம் val, nonatomic_lhs_type, nonatomic_rhs_type, newval, newval_addr;
  மரம் old, old_addr;
  மரம் compound_stmt = NULL_மரம்;
  மரம் stmt, goto_stmt;
  மரம் loop_label, loop_decl, done_label, done_decl;

  மரம் lhs_type = மரம்_TYPE (lhs);
  மரம் lhs_addr = build_unary_op (loc, ADDR_கோவை, lhs, பொய்);
  மரம் seq_cst = build_int_cst (integer_type_முனை, MEMMODEL_SEQ_CST);
  மரம் rhs_semantic_type = மரம்_TYPE (rhs);
  மரம் nonatomic_rhs_semantic_type;
  மரம் rhs_type;

  gcc_assert (TYPE_ATOMIC (lhs_type));

  எனில் (return_old_p)
    gcc_assert (modifycode == PLUS_கோவை || modifycode == MINUS_கோவை);

  /* Allocate enough vector items for a compare_exchange.  */
  vec_alloc (params, 6);

  /* Create a compound statement to hold the sequence of statements
     with a loop.  */
  எனில் (modifycode != NOP_கோவை)
    {
      compound_stmt = c_begin_compound_stmt (பொய்);

      /* For consistency with build_modify_expr on non-_Atomic,
	 mark the lhs as read.  Also, it would be very hard to match
	 such expressions in mark_exp_read.  */
      mark_exp_read (lhs);
    }

  /* Remove any excess precision (which is only present here in the
     case of compound assignments).  */
  எனில் (மரம்_CODE (rhs) == EXCESS_PRECISION_கோவை)
    {
      gcc_assert (modifycode != NOP_கோவை);
      rhs = மரம்_OPERAND (rhs, 0);
    }
  rhs_type = மரம்_TYPE (rhs);

  /* Fold the RHS if it hasn't already been folded.  */
  எனில் (modifycode != NOP_கோவை)
    rhs = c_fully_fold (rhs, பொய், வெற்று);

  /* Remove the qualifiers for the rest of the expressions and create
     the VAL temp variable to hold the RHS.  */
  nonatomic_lhs_type = build_qualified_type (lhs_type, TYPE_UNQUALIFIED);
  nonatomic_rhs_type = build_qualified_type (rhs_type, TYPE_UNQUALIFIED);
  nonatomic_rhs_semantic_type = build_qualified_type (rhs_semantic_type,
						      TYPE_UNQUALIFIED);
  val = create_tmp_var_raw (nonatomic_rhs_type);
  மரம்_ADDRESSABLE (val) = 1;
  suppress_warning (val);
  rhs = build4 (TARGET_கோவை, nonatomic_rhs_type, val, rhs, NULL_மரம்,
		NULL_மரம்);
  மரம்_SIDE_EFFECTS (rhs) = 1;
  SET_கோவை_LOCATION (rhs, loc);
  எனில் (modifycode != NOP_கோவை)
    add_stmt (rhs);

  /* NOP_EXPR indicates it's a straight store of the RHS. Simply issue
     an atomic_store.  */
  எனில் (modifycode == NOP_கோவை)
    {
      compound_stmt = rhs;
      /* Build __atomic_store (&lhs, &val, SEQ_CST)  */
      rhs = build_unary_op (loc, ADDR_கோவை, val, பொய்);
      fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_STORE);
      params->quick_தள்ளு (lhs_addr);
      params->quick_தள்ளு (rhs);
      params->quick_தள்ளு (seq_cst);
      func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, வெற்று);

      compound_stmt = build2 (COMPOUND_கோவை, void_type_முனை,
			      compound_stmt, func_call);

      /* VAL is the value which was stored, return a COMPOUND_STMT of
	 the statement and that value.  */
      திரும்பு build2 (COMPOUND_கோவை, nonatomic_lhs_type, compound_stmt, val);
    }

  /* Attempt to implement the atomic operation as an __atomic_fetch_* or
     __atomic_*_fetch built-in rather than a CAS loop.  atomic_bool type
     isn't applicable for such builtins.  ??? Do we want to handle enums?  */
  எனில் ((மரம்_CODE (lhs_type) == INTEGER_TYPE || POINTER_TYPE_P (lhs_type))
      && மரம்_CODE (rhs_type) == INTEGER_TYPE)
    {
      built_in_function fncode;
      தேர்வு (modifycode)
	{
	நிலை PLUS_கோவை:
	நிலை POINTER_PLUS_கோவை:
	  fncode = (return_old_p
		    ? BUILT_IN_ATOMIC_FETCH_ADD_N
		    : BUILT_IN_ATOMIC_ADD_FETCH_N);
	  நிறுத்து;
	நிலை MINUS_கோவை:
	  fncode = (return_old_p
		    ? BUILT_IN_ATOMIC_FETCH_SUB_N
		    : BUILT_IN_ATOMIC_SUB_FETCH_N);
	  நிறுத்து;
	நிலை BIT_AND_கோவை:
	  fncode = (return_old_p
		    ? BUILT_IN_ATOMIC_FETCH_AND_N
		    : BUILT_IN_ATOMIC_AND_FETCH_N);
	  நிறுத்து;
	நிலை BIT_IOR_கோவை:
	  fncode = (return_old_p
		    ? BUILT_IN_ATOMIC_FETCH_OR_N
		    : BUILT_IN_ATOMIC_OR_FETCH_N);
	  நிறுத்து;
	நிலை BIT_XOR_கோவை:
	  fncode = (return_old_p
		    ? BUILT_IN_ATOMIC_FETCH_XOR_N
		    : BUILT_IN_ATOMIC_XOR_FETCH_N);
	  நிறுத்து;
	இயல்பு:
	  செல் cas_loop;
	}

      /* We can only use "_1" through "_16" variants of the atomic fetch
	 built-ins.  */
      unsigned HOST_WIDE_INT size = மரம்_to_uhwi (TYPE_SIZE_UNIT (lhs_type));
      எனில் (size != 1 && size != 2 && size != 4 && size != 8 && size != 16)
	செல் cas_loop;

      /* If this is a pointer type, we need to multiply by the size of
	 the pointer target type.  */
      எனில் (POINTER_TYPE_P (lhs_type))
	{
	  எனில் (!COMPLETE_TYPE_P (மரம்_TYPE (lhs_type))
	      /* ??? This would introduce -Wdiscarded-qualifiers
		 warning: __atomic_fetch_* expect volatile void *
		 type as the first argument.  (Assignments between
		 atomic and non-atomic objects are OK.) */
	      || TYPE_RESTRICT (lhs_type))
	    செல் cas_loop;
	  மரம் sz = TYPE_SIZE_UNIT (மரம்_TYPE (lhs_type));
	  rhs = fold_build2_loc (loc, MULT_கோவை, ptrdiff_type_முனை,
				 convert (ptrdiff_type_முனை, rhs),
				 convert (ptrdiff_type_முனை, sz));
	}

      /* Build __atomic_fetch_* (&lhs, &val, SEQ_CST), or
	 __atomic_*_fetch (&lhs, &val, SEQ_CST).  */
      fndecl = builtin_decl_explicit (fncode);
      params->quick_தள்ளு (lhs_addr);
      params->quick_தள்ளு (rhs);
      params->quick_தள்ளு (seq_cst);
      func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, வெற்று);

      newval = create_tmp_var_raw (nonatomic_lhs_type);
      மரம்_ADDRESSABLE (newval) = 1;
      suppress_warning (newval);
      rhs = build4 (TARGET_கோவை, nonatomic_lhs_type, newval, func_call,
		    NULL_மரம், NULL_மரம்);
      SET_கோவை_LOCATION (rhs, loc);
      add_stmt (rhs);

      /* Finish the compound statement.  */
      compound_stmt = c_end_compound_stmt (loc, compound_stmt, பொய்);

      /* NEWVAL is the value which was stored, return a COMPOUND_STMT of
	 the statement and that value.  */
      திரும்பு build2 (COMPOUND_கோவை, nonatomic_lhs_type, compound_stmt, newval);
    }

cas_loop:
  /* Create the variables and labels required for the op= form.  */
  old = create_tmp_var_raw (nonatomic_lhs_type);
  old_addr = build_unary_op (loc, ADDR_கோவை, old, பொய்);
  மரம்_ADDRESSABLE (old) = 1;
  suppress_warning (old);

  newval = create_tmp_var_raw (nonatomic_lhs_type);
  newval_addr = build_unary_op (loc, ADDR_கோவை, newval, பொய்);
  மரம்_ADDRESSABLE (newval) = 1;
  suppress_warning (newval);

  loop_decl = create_artificial_label (loc);
  loop_label = build1 (LABEL_கோவை, void_type_முனை, loop_decl);

  done_decl = create_artificial_label (loc);
  done_label = build1 (LABEL_கோவை, void_type_முனை, done_decl);

  /* __atomic_load (addr, &old, SEQ_CST).  */
  fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_LOAD);
  params->quick_தள்ளு (lhs_addr);
  params->quick_தள்ளு (old_addr);
  params->quick_தள்ளு (seq_cst);
  func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, வெற்று);
  old = build4 (TARGET_கோவை, nonatomic_lhs_type, old, func_call, NULL_மரம்,
		NULL_மரம்);
  add_stmt (old);
  params->truncate (0);

  /* Create the expressions for floating-point environment
     manipulation, if required.  */
  தருக்க need_fenv = (flag_trapping_math
		    && (FLOAT_TYPE_P (lhs_type) || FLOAT_TYPE_P (rhs_type)));
  மரம் hold_call = NULL_மரம், clear_call = NULL_மரம், update_call = NULL_மரம்;
  எனில் (need_fenv)
    targetm.atomic_assign_expand_fenv (&hold_call, &clear_call, &update_call);

  எனில் (hold_call)
    add_stmt (hold_call);

  /* loop:  */
  add_stmt (loop_label);

  /* newval = old + val;  */
  எனில் (rhs_type != rhs_semantic_type)
    val = build1 (EXCESS_PRECISION_கோவை, nonatomic_rhs_semantic_type, val);
  rhs = build_இருமம்_op (loc, modifycode,
			 convert_lvalue_to_rvalue (loc, old, உண்மை, உண்மை),
			 val, உண்மை);
  எனில் (மரம்_CODE (rhs) == EXCESS_PRECISION_கோவை)
    {
      மரம் eptype = மரம்_TYPE (rhs);
      rhs = c_fully_fold (மரம்_OPERAND (rhs, 0), பொய், வெற்று);
      rhs = build1 (EXCESS_PRECISION_கோவை, eptype, rhs);
    }
  இல்லையெனில்
    rhs = c_fully_fold (rhs, பொய், வெற்று);
  rhs = convert_for_assignment (loc, UNKNOWN_LOCATION, nonatomic_lhs_type,
				rhs, NULL_மரம், ic_assign, பொய், NULL_மரம்,
				NULL_மரம், 0);
  /* The temporary variable for NEWVAL is only gimplified correctly (in
     particular, given a DECL_CONTEXT) if used in a TARGET_EXPR.  To avoid
     subsequent ICEs in nested function processing after an error, ensure such
     a TARGET_EXPR is built even after an error.  */
  எனில் (rhs == error_mark_முனை)
    rhs = old;
  rhs = build4 (TARGET_கோவை, nonatomic_lhs_type, newval, rhs, NULL_மரம்,
		NULL_மரம்);
  SET_கோவை_LOCATION (rhs, loc);
  add_stmt (rhs);

  /* if (__atomic_compare_exchange (addr, &old, &new, false, SEQ_CST, SEQ_CST))
       goto done;  */
  fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_COMPARE_EXCHANGE);
  params->quick_தள்ளு (lhs_addr);
  params->quick_தள்ளு (old_addr);
  params->quick_தள்ளு (newval_addr);
  params->quick_தள்ளு (integer_zero_முனை);
  params->quick_தள்ளு (seq_cst);
  params->quick_தள்ளு (seq_cst);
  func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, வெற்று);

  goto_stmt = build1 (GOTO_கோவை, void_type_முனை, done_decl);
  SET_கோவை_LOCATION (goto_stmt, loc);

  stmt = build3 (COND_கோவை, void_type_முனை, func_call, goto_stmt, NULL_மரம்);
  SET_கோவை_LOCATION (stmt, loc);
  add_stmt (stmt);

  எனில் (clear_call)
    add_stmt (clear_call);

  /* goto loop;  */
  goto_stmt  = build1 (GOTO_கோவை, void_type_முனை, loop_decl);
  SET_கோவை_LOCATION (goto_stmt, loc);
  add_stmt (goto_stmt);

  /* done:  */
  add_stmt (done_label);

  எனில் (update_call)
    add_stmt (update_call);

  /* Finish the compound statement.  */
  compound_stmt = c_end_compound_stmt (loc, compound_stmt, பொய்);

  /* NEWVAL is the value that was successfully stored, return a
     COMPOUND_EXPR of the statement and the appropriate value.  */
  திரும்பு build2 (COMPOUND_கோவை, nonatomic_lhs_type, compound_stmt,
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

மரம்
build_unary_op (location_t location, எண்ணிக்கை மரம்_code code, மரம் xarg,
		தருக்க noconvert)
{
  /* No default_conversion here.  It causes trouble for ADDR_EXPR.  */
  மரம் arg = xarg;
  மரம் argtype = NULL_மரம்;
  எண்ணிக்கை மரம்_code typecode;
  மரம் val;
  மரம் ret = error_mark_முனை;
  மரம் eptype = NULL_மரம்;
  மாறிலி எழுத்து *invalid_op_diag;

  /* If ARG is wrapped in a call to .ACCESS_WITH_SIZE — created when the
     C parser rvalue-converts a counted_by-annotated member access (see
     PR123569) — unwrap it here.  Unary operators that consume an rvalue
     (!, -, +) read the value itself rather than dereferencing into the
     pointed-to data, so the bounds-checking wrapper is unnecessary and
     would otherwise reach build_unary_op while it is not equipped to
     handle the wrapped form.  PR123569 fixed the ++/-- side of this by
     suppressing wrapper creation in the parser; the rvalue-consuming
     ops still receive the wrapper and need to strip it here.  */
  எனில் (is_access_with_size_p (arg))
    xarg = arg = get_ref_from_access_with_size (arg);

  gcc_checking_assert (!is_access_with_size_p (arg));

  தருக்க int_operands = கோவை_INT_CONST_OPERANDS (xarg);
  எனில் (int_operands)
    arg = remove_c_maybe_const_கோவை (arg);

  எனில் (code != ADDR_கோவை)
    arg = require_complete_type (location, arg);

  typecode = மரம்_CODE (மரம்_TYPE (arg));
  எனில் (typecode == ERROR_MARK)
    திரும்பு error_mark_முனை;
  எனில் (typecode == ENUMERAL_TYPE || typecode == BOOLEAN_TYPE)
    typecode = INTEGER_TYPE;

  எனில் ((invalid_op_diag
       = targetm.invalid_unary_op (code, மரம்_TYPE (xarg))))
    {
      error_at (location, invalid_op_diag);
      திரும்பு error_mark_முனை;
    }

  எனில் (மரம்_CODE (arg) == EXCESS_PRECISION_கோவை)
    {
      eptype = மரம்_TYPE (arg);
      arg = மரம்_OPERAND (arg, 0);
    }

  தேர்வு (code)
    {
    நிலை CONVERT_கோவை:
      /* This is used for unary plus, because a CONVERT_EXPR
	 is enough to prevent anybody from looking inside for
	 associativity, but won't generate any code.  */
      எனில் (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE
	    || typecode == FIXED_POINT_TYPE || typecode == COMPLEX_TYPE
	    || typecode == BITINT_TYPE
	    || gnu_vector_type_p (மரம்_TYPE (arg))))
	{
	  error_at (location, "wrong type argument to unary plus");
	  திரும்பு error_mark_முனை;
	}
      இல்லையெனில் எனில் (!noconvert)
	arg = default_conversion (arg);
      arg = non_lvalue_loc (location, arg);
      நிறுத்து;

    நிலை NEGATE_கோவை:
      எனில் (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE
	    || typecode == FIXED_POINT_TYPE || typecode == COMPLEX_TYPE
	    || typecode == BITINT_TYPE
	    || gnu_vector_type_p (மரம்_TYPE (arg))))
	{
	  error_at (location, "wrong type argument to unary minus");
	  திரும்பு error_mark_முனை;
	}
      இல்லையெனில் எனில் (!noconvert)
	arg = default_conversion (arg);
      நிறுத்து;

    நிலை BIT_NOT_கோவை:
      /* ~ works on integer types and non float vectors. */
      எனில் (typecode == INTEGER_TYPE
	  || typecode == BITINT_TYPE
	  || (gnu_vector_type_p (மரம்_TYPE (arg))
	      && !VECTOR_FLOAT_TYPE_P (மரம்_TYPE (arg))))
	{
	  மரம் e = arg;

	  /* Warn if the expression has boolean value.  */
	  போது (மரம்_CODE (e) == COMPOUND_கோவை)
	    e = மரம்_OPERAND (e, 1);

	  எனில் ((C_BOOLEAN_TYPE_P (மரம்_TYPE (arg))
	       || truth_மதிப்பு_p (மரம்_CODE (e))))
	    {
	      auto_diagnostic_group d;
	      எனில் (warning_at (location, OPT_Wbool_operation,
				"%<~%> on a boolean expression"))
		{
		  gcc_rich_location richloc (location);
		  richloc.add_fixit_செருகு_before (location, "!");
		  inform (&richloc, "did you mean to use logical not?");
		}
	    }
	  எனில் (!noconvert)
	    arg = default_conversion (arg);
	}
      இல்லையெனில் எனில் (typecode == COMPLEX_TYPE)
	{
	  code = CONJ_கோவை;
	  pedwarn (location, OPT_Wpedantic,
		   "ISO C does not support %<~%> for complex conjugation");
	  எனில் (!noconvert)
	    arg = default_conversion (arg);
	}
      இல்லையெனில்
	{
	  error_at (location, "wrong type argument to bit-complement");
	  திரும்பு error_mark_முனை;
	}
      நிறுத்து;

    நிலை ABS_கோவை:
      எனில் (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE))
	{
	  error_at (location, "wrong type argument to abs");
	  திரும்பு error_mark_முனை;
	}
      இல்லையெனில் எனில் (!noconvert)
	arg = default_conversion (arg);
      நிறுத்து;

    நிலை ABSU_கோவை:
      எனில் (!(typecode == INTEGER_TYPE))
	{
	  error_at (location, "wrong type argument to absu");
	  திரும்பு error_mark_முனை;
	}
      இல்லையெனில் எனில் (!noconvert)
	arg = default_conversion (arg);
      நிறுத்து;

    நிலை CONJ_கோவை:
      /* Conjugating a real value is a no-op, but allow it anyway.  */
      எனில் (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE
	    || typecode == COMPLEX_TYPE))
	{
	  error_at (location, "wrong type argument to conjugation");
	  திரும்பு error_mark_முனை;
	}
      இல்லையெனில் எனில் (!noconvert)
	arg = default_conversion (arg);
      நிறுத்து;

    நிலை TRUTH_NOT_கோவை:
      எனில் (typecode != INTEGER_TYPE && typecode != FIXED_POINT_TYPE
	  && typecode != REAL_TYPE && typecode != POINTER_TYPE
	  && typecode != COMPLEX_TYPE && typecode != NULLPTR_TYPE
	  && typecode != BITINT_TYPE)
	{
	  error_at (location,
		    "wrong type argument to unary exclamation mark");
	  திரும்பு error_mark_முனை;
	}
      எனில் (int_operands)
	{
	  arg = c_objc_common_truthvalue_conversion (location, xarg);
	  arg = remove_c_maybe_const_கோவை (arg);
	}
      இல்லையெனில்
	arg = c_objc_common_truthvalue_conversion (location, arg);
      ret = invert_truthvalue_loc (location, arg);
      eptype = NULL_மரம்;
      /* If the TRUTH_NOT_EXPR has been folded, reset the location.  */
      எனில் (கோவை_P (ret) && கோவை_HAS_LOCATION (ret))
	location = கோவை_LOCATION (ret);
      செல் return_build_unary_op;

    நிலை REALPART_கோவை:
    நிலை IMAGPART_கோவை:
      ret = build_real_imag_கோவை (location, code, arg);
      எனில் (ret == error_mark_முனை)
	திரும்பு error_mark_முனை;
      எனில் (eptype && மரம்_CODE (eptype) == COMPLEX_TYPE)
	eptype = மரம்_TYPE (eptype);
      செல் return_build_unary_op;

    நிலை PREINCREMENT_கோவை:
    நிலை POSTINCREMENT_கோவை:
    நிலை PREDECREMENT_கோவை:
    நிலை POSTDECREMENT_கோவை:

      எனில் (மரம்_CODE (arg) == C_MAYBE_CONST_கோவை)
	{
	  மரம் inner = build_unary_op (location, code,
				       C_MAYBE_CONST_கோவை_கோவை (arg),
				       noconvert);
	  எனில் (inner == error_mark_முனை)
	    திரும்பு error_mark_முனை;
	  ret = build2 (C_MAYBE_CONST_கோவை, மரம்_TYPE (inner),
			C_MAYBE_CONST_கோவை_PRE (arg), inner);
	  gcc_assert (!C_MAYBE_CONST_கோவை_INT_OPERANDS (arg));
	  C_MAYBE_CONST_கோவை_NON_CONST (ret) = 1;
	  செல் return_build_unary_op;
	}

      /* Complain about anything that is not a true lvalue.  In
	 Objective-C, skip this check for property_refs.  */
      எனில் (!objc_is_property_ref (arg)
	  && !lvalue_or_else (location,
			      arg, ((code == PREINCREMENT_கோவை
				     || code == POSTINCREMENT_கோவை)
				    ? lv_increment
				    : lv_decrement)))
	திரும்பு error_mark_முனை;

      எனில் (warn_cxx_compat && மரம்_CODE (மரம்_TYPE (arg)) == ENUMERAL_TYPE)
	{
	  எனில் (code == PREINCREMENT_கோவை || code == POSTINCREMENT_கோவை)
	    warning_at (location, OPT_Wc___compat,
			"increment of enumeration value is invalid in C++");
	  இல்லையெனில்
	    warning_at (location, OPT_Wc___compat,
			"decrement of enumeration value is invalid in C++");
	}

      எனில் (C_BOOLEAN_TYPE_P (மரம்_TYPE (arg)))
	{
	  எனில் (code == PREINCREMENT_கோவை || code == POSTINCREMENT_கோவை)
	    warning_at (location, OPT_Wbool_operation,
			"increment of a boolean expression");
	  இல்லையெனில்
	    warning_at (location, OPT_Wbool_operation,
			"decrement of a boolean expression");
	}

      /* Ensure the argument is fully folded inside any SAVE_EXPR.  */
      arg = c_fully_fold (arg, பொய், வெற்று, உண்மை);

      தருக்க atomic_op;
      atomic_op = really_atomic_lvalue (arg);

      /* Increment or decrement the real part of the value,
	 and don't change the imaginary part.  */
      எனில் (typecode == COMPLEX_TYPE)
	{
	  மரம் real, imag;

	  pedwarn_c23 (location, OPT_Wpedantic,
		       "ISO C does not support %<++%> and %<--%> on complex "
		       "types before C2Y");

	  எனில் (!atomic_op)
	    {
	      arg = stabilize_reference (arg);
	      real = build_unary_op (கோவை_LOCATION (arg), REALPART_கோவை, arg,
				     உண்மை);
	      imag = build_unary_op (கோவை_LOCATION (arg), IMAGPART_கோவை, arg,
				     உண்மை);
	      real = build_unary_op (கோவை_LOCATION (arg), code, real, உண்மை);
	      எனில் (real == error_mark_முனை || imag == error_mark_முனை)
		திரும்பு error_mark_முனை;
	      ret = build2 (COMPLEX_கோவை, மரம்_TYPE (arg),
			    real, imag);
	      செல் return_build_unary_op;
	    }
	}

      /* Report invalid types.  */

      எனில் (typecode != POINTER_TYPE && typecode != FIXED_POINT_TYPE
	  && typecode != INTEGER_TYPE && typecode != REAL_TYPE
	  && typecode != COMPLEX_TYPE && typecode != BITINT_TYPE
	  && !gnu_vector_type_p (மரம்_TYPE (arg)))
	{
	  எனில் (code == PREINCREMENT_கோவை || code == POSTINCREMENT_கோவை)
	    error_at (location, "wrong type argument to increment");
	  இல்லையெனில்
	    error_at (location, "wrong type argument to decrement");

	  திரும்பு error_mark_முனை;
	}

      {
	மரம் inc;

	argtype = மரம்_TYPE (arg);

	/* Compute the increment.  */

	எனில் (typecode == POINTER_TYPE)
	  {
	    /* If pointer target is an incomplete type,
	       we just cannot know how to do the arithmetic.  */
	    எனில் (!COMPLETE_OR_VOID_TYPE_P (மரம்_TYPE (argtype)))
	      {
		எனில் (code == PREINCREMENT_கோவை || code == POSTINCREMENT_கோவை)
		  error_at (location,
			    "increment of pointer to an incomplete type %qT",
			    மரம்_TYPE (argtype));
		இல்லையெனில்
		  error_at (location,
			    "decrement of pointer to an incomplete type %qT",
			    மரம்_TYPE (argtype));
	      }
	    இல்லையெனில் எனில் (மரம்_CODE (மரம்_TYPE (argtype)) == FUNCTION_TYPE
		     || VOID_TYPE_P (மரம்_TYPE (argtype)))
	      {
		எனில் (code == PREINCREMENT_கோவை || code == POSTINCREMENT_கோவை)
		  pedwarn (location, OPT_Wpointer_arith,
			   "wrong type argument to increment");
		இல்லையெனில்
		  pedwarn (location, OPT_Wpointer_arith,
			   "wrong type argument to decrement");
	      }
	    இல்லையெனில்
	      verify_type_context (location, TCTX_POINTER_ARITH,
				   மரம்_TYPE (argtype));

	    inc = c_size_in_bytes (மரம்_TYPE (argtype));
	    inc = convert_to_ptrofftype_loc (location, inc);
	  }
	இல்லையெனில் எனில் (FRACT_MODE_P (TYPE_MODE (argtype)))
	  {
	    /* For signed fract types, we invert ++ to -- or
	       -- to ++, and change inc from 1 to -1, because
	       it is not possible to represent 1 in signed fract constants.
	       For unsigned fract types, the result always overflows and
	       we get an undefined (original) or the maximum value.  */
	    எனில் (code == PREINCREMENT_கோவை)
	      code = PREDECREMENT_கோவை;
	    இல்லையெனில் எனில் (code == PREDECREMENT_கோவை)
	      code = PREINCREMENT_கோவை;
	    இல்லையெனில் எனில் (code == POSTINCREMENT_கோவை)
	      code = POSTDECREMENT_கோவை;
	    இல்லையெனில் /* code == POSTDECREMENT_EXPR  */
	      code = POSTINCREMENT_கோவை;

	    inc = integer_minus_one_முனை;
	    inc = convert (argtype, inc);
	  }
	இல்லையெனில்
	  {
	    inc = VECTOR_TYPE_P (argtype)
	      ? build_one_cst (argtype)
	      : integer_one_முனை;
	    inc = convert (argtype, inc);
	  }

	/* If 'arg' is an Objective-C PROPERTY_REF expression, then we
	   need to ask Objective-C to build the increment or decrement
	   expression for it.  */
	எனில் (objc_is_property_ref (arg))
	  திரும்பு objc_build_incr_கோவை_for_property_ref (location, code,
							arg, inc);

	/* Report a read-only lvalue.  */
	எனில் (TYPE_READONLY (argtype))
	  {
	    readonly_error (location, arg,
			    ((code == PREINCREMENT_கோவை
			      || code == POSTINCREMENT_கோவை)
			     ? lv_increment : lv_decrement));
	    திரும்பு error_mark_முனை;
	  }
	இல்லையெனில் எனில் (மரம்_READONLY (arg))
	  readonly_warning (arg,
			    ((code == PREINCREMENT_கோவை
			      || code == POSTINCREMENT_கோவை)
			     ? lv_increment : lv_decrement));

	/* If the argument is atomic, use the special code sequences for
	   atomic compound assignment.  */
	எனில் (atomic_op)
	  {
	    arg = stabilize_reference (arg);
	    ret = build_atomic_assign (location, arg,
				       ((code == PREINCREMENT_கோவை
					 || code == POSTINCREMENT_கோவை)
					? PLUS_கோவை
					: MINUS_கோவை),
				       (FRACT_MODE_P (TYPE_MODE (argtype))
					? inc
					: integer_one_முனை),
				       (code == POSTINCREMENT_கோவை
					|| code == POSTDECREMENT_கோவை));
	    செல் return_build_unary_op;
	  }

	மரம் true_res;
	எனில் (c_hardbool_type_attr (மரம்_TYPE (arg), வெற்று, &true_res))
	  {
	    மரம் larg = stabilize_reference (arg);
	    மரம் sarg = save_கோவை (larg);
	    தேர்வு (code)
	      {
	      நிலை PREINCREMENT_கோவை:
		val = build2 (MODIFY_கோவை, மரம்_TYPE (larg), larg, true_res);
		val = build2 (COMPOUND_கோவை, மரம்_TYPE (larg), sarg, val);
		நிறுத்து;
	      நிலை POSTINCREMENT_கோவை:
		val = build2 (MODIFY_கோவை, மரம்_TYPE (larg), larg, true_res);
		val = build2 (COMPOUND_கோவை, மரம்_TYPE (larg), val, sarg);
		val = build2 (COMPOUND_கோவை, மரம்_TYPE (larg), sarg, val);
		நிறுத்து;
	      நிலை PREDECREMENT_கோவை:
		{
		  மரம் rarg = convert_lvalue_to_rvalue (location, sarg,
							உண்மை, உண்மை);
		  rarg = invert_truthvalue_loc (location, rarg);
		  rarg = convert (மரம்_TYPE (sarg), rarg);
		  val = build2 (MODIFY_கோவை, மரம்_TYPE (larg), larg, rarg);
		}
		நிறுத்து;
	      நிலை POSTDECREMENT_கோவை:
		{
		  மரம் rarg = convert_lvalue_to_rvalue (location, sarg,
							உண்மை, உண்மை);
		  rarg = invert_truthvalue_loc (location, rarg);
		  மரம் iarg = convert (மரம்_TYPE (larg), rarg);
		  val = build2 (MODIFY_கோவை, மரம்_TYPE (larg), larg, iarg);
		  val = build2 (COMPOUND_கோவை, மரம்_TYPE (larg), val, sarg);
		  val = build2 (COMPOUND_கோவை, மரம்_TYPE (larg), sarg, val);
		}
		நிறுத்து;
	      இயல்பு:
		gcc_unreachable ();
	      }
	    மரம்_SIDE_EFFECTS (val) = 1;
	  }
	இல்லையெனில் எனில் (C_BOOLEAN_TYPE_P (மரம்_TYPE (arg)))
	  val = boolean_increment (code, arg);
	இல்லையெனில்
	  val = build2 (code, மரம்_TYPE (arg), arg, inc);
	மரம்_SIDE_EFFECTS (val) = 1;
	எனில் (TYPE_QUALS (மரம்_TYPE (val)) != TYPE_UNQUALIFIED)
	  மரம்_TYPE (val) = c_build_qualified_type (மரம்_TYPE (val),
						    TYPE_UNQUALIFIED);
	ret = val;
	செல் return_build_unary_op;
      }

    நிலை ADDR_கோவை:
      /* Note that this operation never does default_conversion.  */

      /* The operand of unary '&' must be an lvalue (which excludes
	 expressions of type void), or, in C99, the result of a [] or
	 unary '*' operator.  */
      எனில் (VOID_TYPE_P (மரம்_TYPE (arg))
	  && TYPE_QUALS (மரம்_TYPE (arg)) == TYPE_UNQUALIFIED
	  && (!INDIRECT_REF_P (arg) || !flag_isoc99))
	pedwarn (location, 0, "taking address of expression of type %<void%>");

      /* Let &* cancel out to simplify resulting code.  */
      எனில் (INDIRECT_REF_P (arg))
	{
	  /* Don't let this be an lvalue.  */
	  எனில் (lvalue_p (மரம்_OPERAND (arg, 0)))
	    திரும்பு non_lvalue_loc (location, மரம்_OPERAND (arg, 0));
	  ret = மரம்_OPERAND (arg, 0);
	  செல் return_build_unary_op;
	}

      /* Anything not already handled and not a true memory reference
	 or a non-lvalue array is an error.  */
      எனில் (typecode != FUNCTION_TYPE && !noconvert
	  && !lvalue_or_else (location, arg, lv_addressof))
	திரும்பு error_mark_முனை;

      /* Move address operations inside C_MAYBE_CONST_EXPR to simplify
	 folding later.  */
      எனில் (மரம்_CODE (arg) == C_MAYBE_CONST_கோவை)
	{
	  மரம் inner = build_unary_op (location, code,
				       C_MAYBE_CONST_கோவை_கோவை (arg),
				       noconvert);
	  ret = build2 (C_MAYBE_CONST_கோவை, மரம்_TYPE (inner),
			C_MAYBE_CONST_கோவை_PRE (arg), inner);
	  gcc_assert (!C_MAYBE_CONST_கோவை_INT_OPERANDS (arg));
	  C_MAYBE_CONST_கோவை_NON_CONST (ret)
	    = C_MAYBE_CONST_கோவை_NON_CONST (arg);
	  செல் return_build_unary_op;
	}

      /* Ordinary case; arg is a COMPONENT_REF or a decl.  */

      argtype = மரம்_TYPE (arg);

      /* If the lvalue is const or volatile, merge that into the type
	 to which the address will point.  This is only needed
	 for function types.  */
      எனில் ((DECL_P (arg) || REFERENCE_CLASS_P (arg))
	  && (மரம்_READONLY (arg) || மரம்_THIS_VOLATILE (arg))
	  && மரம்_CODE (argtype) == FUNCTION_TYPE)
	{
	  முழு orig_quals = TYPE_QUALS (strip_array_types (argtype));
	  முழு quals = orig_quals;

	  எனில் (மரம்_READONLY (arg))
	    quals |= TYPE_QUAL_CONST;
	  எனில் (மரம்_THIS_VOLATILE (arg))
	    quals |= TYPE_QUAL_VOLATILE;

	  argtype = c_build_qualified_type (argtype, quals);
	}

      தேர்வு (மரம்_CODE (arg))
	{
	நிலை COMPONENT_REF:
	  எனில் (DECL_C_BIT_FIELD (மரம்_OPERAND (arg, 1)))
	    {
	      error_at (location, "cannot take address of bit-field %qD",
			மரம்_OPERAND (arg, 1));
	      திரும்பு error_mark_முனை;
	    }

	  /* fall through */

	நிலை ARRAY_REF:
	  எனில் (TYPE_REVERSE_STORAGE_ORDER (மரம்_TYPE (மரம்_OPERAND (arg, 0))))
	    {
	      எனில் (!AGGREGATE_TYPE_P (மரம்_TYPE (arg))
		  && !POINTER_TYPE_P (மரம்_TYPE (arg))
		  && !VECTOR_TYPE_P (மரம்_TYPE (arg)))
		{
		  error_at (location, "cannot take address of scalar with "
			    "reverse storage order");
		  திரும்பு error_mark_முனை;
		}

	      எனில் (மரம்_CODE (மரம்_TYPE (arg)) == ARRAY_TYPE
		  && TYPE_REVERSE_STORAGE_ORDER (மரம்_TYPE (arg)))
		warning_at (location, OPT_Wscalar_storage_order,
			    "address of array with reverse scalar storage "
			    "order requested");
	    }

	இயல்பு:
	  நிறுத்து;
	}

      எனில் (!c_mark_addressable (arg))
	திரும்பு error_mark_முனை;

      gcc_assert (மரம்_CODE (arg) != COMPONENT_REF
		  || !DECL_C_BIT_FIELD (மரம்_OPERAND (arg, 1)));

      argtype = c_build_pointer_type (argtype);

      /* ??? Cope with user tricks that amount to offsetof.  Delete this
	 when we have proper support for integer constant expressions.  */
      val = get_base_address (arg);
      எனில் (val && INDIRECT_REF_P (val)
          && மரம்_CONSTANT (மரம்_OPERAND (val, 0)))
	{
	  ret = fold_offsetof (arg, argtype);
	  செல் return_build_unary_op;
	}

      val = build1 (ADDR_கோவை, argtype, arg);

      ret = val;
      செல் return_build_unary_op;

    நிலை PAREN_கோவை:
      ret = build1 (code, மரம்_TYPE (arg), arg);
      செல் return_build_unary_op;

    இயல்பு:
      gcc_unreachable ();
    }

  எனில் (argtype == NULL_மரம்)
    argtype = மரம்_TYPE (arg);
  எனில் (மரம்_CODE (arg) == INTEGER_CST)
    ret = (require_constant_மதிப்பு
	   ? fold_build1_initializer_loc (location, code, argtype, arg)
	   : fold_build1_loc (location, code, argtype, arg));
  இல்லையெனில்
    ret = build1 (code, argtype, arg);
 return_build_unary_op:
  gcc_assert (ret != error_mark_முனை);
  எனில் (மரம்_CODE (ret) == INTEGER_CST && !மரம்_OVERFLOW (ret)
      && !(மரம்_CODE (xarg) == INTEGER_CST && !மரம்_OVERFLOW (xarg)))
    ret = build1 (NOP_கோவை, மரம்_TYPE (ret), ret);
  இல்லையெனில் எனில் (மரம்_CODE (ret) != INTEGER_CST && int_operands)
    ret = note_integer_operands (ret);
  எனில் (eptype)
    ret = build1 (EXCESS_PRECISION_கோவை, eptype, ret);
  protected_set_கோவை_location (ret, location);
  திரும்பு ret;
}

/* Return nonzero if REF is an lvalue valid for this language.
   Lvalues can be assigned, unless their type has TYPE_READONLY.
   Lvalues can have their address taken, unless they have C_DECL_REGISTER.  */

தருக்க
lvalue_p (const_மரம் ref)
{
  மாறிலி எண்ணிக்கை மரம்_code code = மரம்_CODE (ref);

  தேர்வு (code)
    {
    நிலை REALPART_கோவை:
    நிலை IMAGPART_கோவை:
    நிலை COMPONENT_REF:
      திரும்பு lvalue_p (மரம்_OPERAND (ref, 0));

    நிலை C_MAYBE_CONST_கோவை:
      திரும்பு lvalue_p (மரம்_OPERAND (ref, 1));

    நிலை COMPOUND_LITERAL_கோவை:
    நிலை STRING_CST:
      திரும்பு உண்மை;

    நிலை MEM_REF:
    நிலை TARGET_MEM_REF:
      /* MEM_REFs can appear from -fgimple parsing or folding, so allow them
	 here as well.  */
    நிலை INDIRECT_REF:
    நிலை ARRAY_REF:
    நிலை VAR_DECL:
    நிலை PARM_DECL:
    நிலை RESULT_DECL:
    நிலை ERROR_MARK:
      திரும்பு (மரம்_CODE (மரம்_TYPE (ref)) != FUNCTION_TYPE
	      && மரம்_CODE (மரம்_TYPE (ref)) != METHOD_TYPE);

    நிலை BIND_கோவை:
      திரும்பு மரம்_CODE (மரம்_TYPE (ref)) == ARRAY_TYPE;

    நிலை CALL_கோவை:
      திரும்பு is_access_with_size_p (ref);

    இயல்பு:
      திரும்பு பொய்;
    }
}

/* Give a warning for storing in something that is read-only in GCC
   terms but not const in ISO C terms.  */

நிலையான வெறுமை
readonly_warning (மரம் arg, எண்ணிக்கை lvalue_use use)
{
  தேர்வு (use)
    {
    நிலை lv_assign:
      warning (0, "assignment of read-only location %qE", arg);
      நிறுத்து;
    நிலை lv_increment:
      warning (0, "increment of read-only location %qE", arg);
      நிறுத்து;
    நிலை lv_decrement:
      warning (0, "decrement of read-only location %qE", arg);
      நிறுத்து;
    இயல்பு:
      gcc_unreachable ();
    }
  திரும்பு;
}


/* Return nonzero if REF is an lvalue valid for this language;
   otherwise, print an error message and return zero.  USE says
   how the lvalue is being used and so selects the error message.
   LOCATION is the location at which any error should be reported.  */

நிலையான முழு
lvalue_or_else (location_t loc, const_மரம் ref, எண்ணிக்கை lvalue_use use)
{
  முழு win = lvalue_p (ref);

  எனில் (!win)
    lvalue_error (loc, use);

  திரும்பு win;
}

/* Mark EXP saying that we need to be able to take the
   address of it; it should not be allocated in a register.
   Returns true if successful.  ARRAY_REF_P is true if this
   is for ARRAY_REF construction - in that case we don't want
   to look through VIEW_CONVERT_EXPR from VECTOR_TYPE to ARRAY_TYPE,
   it is fine to use ARRAY_REFs for vector subscripts on vector
   register variables.  If OVERRIDE_REGISTER, clear DECL_REGISTER rather
   than producing an error for taking the address of a register.  */

தருக்க
c_mark_addressable (மரம் exp, தருக்க array_ref_p, தருக்க override_register)
{
  மரம் x = exp;

  போது (1)
    தேர்வு (மரம்_CODE (x))
      {
      நிலை VIEW_CONVERT_கோவை:
	எனில் (array_ref_p
	    && மரம்_CODE (மரம்_TYPE (x)) == ARRAY_TYPE
	    && VECTOR_TYPE_P (மரம்_TYPE (மரம்_OPERAND (x, 0))))
	  திரும்பு உண்மை;
	x = மரம்_OPERAND (x, 0);
	நிறுத்து;

      நிலை COMPONENT_REF:
	எனில் (DECL_C_BIT_FIELD (மரம்_OPERAND (x, 1)))
	  {
	    error ("cannot take address of bit-field %qD",
		   மரம்_OPERAND (x, 1));
	    திரும்பு பொய்;
	  }
	/* FALLTHRU */
      நிலை ADDR_கோவை:
      நிலை ARRAY_REF:
      நிலை REALPART_கோவை:
      நிலை IMAGPART_கோவை:
	x = மரம்_OPERAND (x, 0);
	நிறுத்து;

      நிலை COMPOUND_LITERAL_கோவை:
	எனில் (C_DECL_REGISTER (COMPOUND_LITERAL_கோவை_DECL (x)))
	  {
	    எனில் (override_register)
	      DECL_REGISTER (COMPOUND_LITERAL_கோவை_DECL (x)) = 0;
	    இல்லையெனில்
	      {
		error ("address of register compound literal requested");
		திரும்பு பொய்;
	      }
	  }
	மரம்_ADDRESSABLE (x) = 1;
	மரம்_ADDRESSABLE (COMPOUND_LITERAL_கோவை_DECL (x)) = 1;
	திரும்பு உண்மை;

      நிலை CONSTRUCTOR:
	மரம்_ADDRESSABLE (x) = 1;
	திரும்பு உண்மை;

      நிலை VAR_DECL:
      நிலை CONST_DECL:
      நிலை PARM_DECL:
      நிலை RESULT_DECL:
	எனில் (C_DECL_REGISTER (x)
	    && DECL_NONLOCAL (x))
	  {
	    எனில் (மரம்_PUBLIC (x) || is_global_var (x))
	      {
		error
		  ("global register variable %qD used in nested function", x);
		திரும்பு பொய்;
	      }
	    pedwarn (உள்ளீடு_location, 0, "register variable %qD used in nested function", x);
	  }
	இல்லையெனில் எனில் (C_DECL_REGISTER (x))
	  {
	    எனில் (மரம்_PUBLIC (x) || is_global_var (x))
	      error ("address of global register variable %qD requested", x);
	    இல்லையெனில் எனில் (override_register && !DECL_HARD_REGISTER (x))
	      {
		DECL_REGISTER (x) = 0;
		மரம்_ADDRESSABLE (x) = 1;
		mark_decl_used (x, உண்மை);
		திரும்பு உண்மை;
	      }
	    இல்லையெனில்
	      error ("address of register variable %qD requested", x);
	    திரும்பு பொய்;
	  }

	/* FALLTHRU */
      நிலை FUNCTION_DECL:
	மரம்_ADDRESSABLE (x) = 1;
	mark_decl_used (x, உண்மை);
	/* FALLTHRU */
      இயல்பு:
	திரும்பு உண்மை;
    }
}

/* Convert EXPR to TYPE, warning about conversion problems with
   constants.  SEMANTIC_TYPE is the type this conversion would use
   without excess precision. If SEMANTIC_TYPE is NULL, this function
   is equivalent to convert_and_check. This function is a wrapper that
   handles conversions that may be different than
   the usual ones because of excess precision.  */

நிலையான மரம்
ep_convert_and_check (location_t loc, மரம் type, மரம் கோவை,
		      மரம் semantic_type)
{
  எனில் (மரம்_TYPE (கோவை) == type)
    திரும்பு கோவை;

  /* For C11, integer conversions may have results with excess
     precision.  */
  எனில் (flag_isoc11 || !semantic_type)
    திரும்பு convert_and_check (loc, type, கோவை);

  எனில் (மரம்_CODE (மரம்_TYPE (கோவை)) == INTEGER_TYPE
      && மரம்_TYPE (கோவை) != semantic_type)
    {
      /* For integers, we need to check the real conversion, not
	 the conversion to the excess precision type.  */
      கோவை = convert_and_check (loc, semantic_type, கோவை);
    }
  /* Result type is the excess precision type, which should be
     large enough, so do not check.  */
  திரும்பு convert (type, கோவை);
}

/* If EXPR refers to a built-in declared without a prototype returns
   the actual type of the built-in and, if non-null, set *BLTIN to
   a pointer to the built-in.  Otherwise return the type of EXPR
   and clear *BLTIN if non-null.  */

நிலையான மரம்
type_or_builtin_type (மரம் கோவை, மரம் *bltin = வெற்று)
{
  மரம் dummy;
  எனில் (!bltin)
    bltin = &dummy;

  *bltin = NULL_மரம்;

  மரம் type = மரம்_TYPE (கோவை);
  எனில் (மரம்_CODE (கோவை) != ADDR_கோவை)
    திரும்பு type;

  மரம் oper = மரம்_OPERAND (கோவை, 0);
  எனில் (!DECL_P (oper)
      || மரம்_CODE (oper) != FUNCTION_DECL
      || !fndecl_built_in_p (oper, BUILT_IN_NORMAL))
    திரும்பு type;

  built_in_function code = DECL_FUNCTION_CODE (oper);
  எனில் (!C_DECL_BUILTIN_PROTOTYPE (oper))
    திரும்பு type;

  எனில் ((*bltin = builtin_decl_implicit (code)))
    type = c_build_pointer_type (மரம்_TYPE (*bltin));

  திரும்பு type;
}

/* Build and return a conditional expression IFEXP ? OP1 : OP2.  If
   IFEXP_BCP then the condition is a call to __builtin_constant_p, and
   if folded to an integer constant then the unselected half may
   contain arbitrary operations not normally permitted in constant
   expressions.  Set the location of the expression to LOC.  */

மரம்
build_conditional_கோவை (location_t colon_loc, மரம் ifexp, தருக்க ifexp_bcp,
			மரம் op1, மரம் op1_original_type, location_t op1_loc,
			மரம் op2, மரம் op2_original_type, location_t op2_loc)
{
  மரம் type1;
  மரம் type2;
  மரம் result_type = வெற்று;
  மரம் semantic_result_type = வெற்று;
  மரம் orig_op1 = op1, orig_op2 = op2;
  தருக்க int_const, op1_int_operands, op2_int_operands, int_operands;
  தருக்க ifexp_int_operands;
  மரம் ret;

  op1_int_operands = கோவை_INT_CONST_OPERANDS (orig_op1);
  எனில் (op1_int_operands)
    op1 = remove_c_maybe_const_கோவை (op1);
  op2_int_operands = கோவை_INT_CONST_OPERANDS (orig_op2);
  எனில் (op2_int_operands)
    op2 = remove_c_maybe_const_கோவை (op2);
  ifexp_int_operands = கோவை_INT_CONST_OPERANDS (ifexp);
  எனில் (ifexp_int_operands)
    ifexp = remove_c_maybe_const_கோவை (ifexp);

  /* Promote both alternatives.  */

  எனில் (மரம்_CODE (மரம்_TYPE (op1)) != VOID_TYPE)
    op1 = default_conversion (op1);
  எனில் (மரம்_CODE (மரம்_TYPE (op2)) != VOID_TYPE)
    op2 = default_conversion (op2);

  எனில் (மரம்_CODE (ifexp) == ERROR_MARK
      || மரம்_CODE (மரம்_TYPE (op1)) == ERROR_MARK
      || மரம்_CODE (மரம்_TYPE (op2)) == ERROR_MARK)
    திரும்பு error_mark_முனை;

  மரம் bltin1 = NULL_மரம்;
  மரம் bltin2 = NULL_மரம்;
  type1 = type_or_builtin_type (op1, &bltin1);
  மாறிலி எண்ணிக்கை மரம்_code code1 = மரம்_CODE (type1);
  type2 = type_or_builtin_type (op2, &bltin2);
  மாறிலி எண்ணிக்கை மரம்_code code2 = மரம்_CODE (type2);

  எனில் (code1 == POINTER_TYPE && reject_gcc_builtin (op1))
    திரும்பு error_mark_முனை;

  எனில் (code2 == POINTER_TYPE && reject_gcc_builtin (op2))
    திரும்பு error_mark_முனை;

  /* C90 does not permit non-lvalue arrays in conditional expressions.
     In C99 they will be pointers by now.  */
  எனில் (code1 == ARRAY_TYPE || code2 == ARRAY_TYPE)
    {
      error_at (colon_loc, "non-lvalue array in conditional expression");
      திரும்பு error_mark_முனை;
    }

  எனில் ((மரம்_CODE (op1) == EXCESS_PRECISION_கோவை
       || மரம்_CODE (op2) == EXCESS_PRECISION_கோவை)
      && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	  || code1 == COMPLEX_TYPE || code1 == BITINT_TYPE)
      && (code2 == INTEGER_TYPE || code2 == REAL_TYPE
	  || code2 == COMPLEX_TYPE || code2 == BITINT_TYPE))
    {
      semantic_result_type = c_common_type (type1, type2);
      எனில் (மரம்_CODE (op1) == EXCESS_PRECISION_கோவை)
	{
	  op1 = மரம்_OPERAND (op1, 0);
	  type1 = மரம்_TYPE (op1);
	  gcc_assert (மரம்_CODE (type1) == code1);
	}
      எனில் (மரம்_CODE (op2) == EXCESS_PRECISION_கோவை)
	{
	  op2 = மரம்_OPERAND (op2, 0);
	  type2 = மரம்_TYPE (op2);
	  gcc_assert (மரம்_CODE (type2) == code2);
	}
    }

  எனில் (warn_cxx_compat)
    {
      மரம் t1 = op1_original_type ? op1_original_type : மரம்_TYPE (orig_op1);
      மரம் t2 = op2_original_type ? op2_original_type : மரம்_TYPE (orig_op2);

      எனில் (மரம்_CODE (t1) == ENUMERAL_TYPE
	  && மரம்_CODE (t2) == ENUMERAL_TYPE
	  && TYPE_MAIN_VARIANT (t1) != TYPE_MAIN_VARIANT (t2))
	warning_at (colon_loc, OPT_Wc___compat,
		    "different enum types in conditional is "
		    "invalid in C++: %qT vs %qT", t1, t2);
    }

  எனில் (warn_zero_as_null_pointer_constant
      && c_inhibit_evaluation_warnings == 0)
    {
      எனில் ((code1 == POINTER_TYPE || code1 == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type2) && null_pointer_constant_p (orig_op2))
	warning_at (op2_loc, OPT_Wzero_as_null_pointer_constant,
		    "zero as null pointer constant");

      எனில் ((code2 == POINTER_TYPE || code2 == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type1) && null_pointer_constant_p (orig_op1))
	warning_at (op1_loc, OPT_Wzero_as_null_pointer_constant,
		    "zero as null pointer constant");
    }

  /* Quickly detect the usual case where op1 and op2 have the same type
     after promotion.  */
  எனில் (TYPE_MAIN_VARIANT (type1) == TYPE_MAIN_VARIANT (type2))
    {
      எனில் (type1 == type2)
	result_type = type1;
      இல்லையெனில்
	result_type = TYPE_MAIN_VARIANT (type1);
    }
  இல்லையெனில் எனில் ((code1 == INTEGER_TYPE || code1 == REAL_TYPE
	    || code1 == COMPLEX_TYPE || code1 == BITINT_TYPE)
	   && (code2 == INTEGER_TYPE || code2 == REAL_TYPE
	       || code2 == COMPLEX_TYPE || code2 == BITINT_TYPE))
    {
      /* In C11, a conditional expression between a floating-point
	 type and an integer type should convert the integer type to
	 the evaluation format of the floating-point type, with
	 possible excess precision.  */
      மரம் eptype1 = type1;
      மரம் eptype2 = type2;
      எனில் (flag_isoc11)
	{
	  மரம் eptype;
	  எனில் (ANY_INTEGRAL_TYPE_P (type1)
	      && (eptype = excess_precision_type (type2)) != NULL_மரம்)
	    {
	      eptype2 = eptype;
	      எனில் (!semantic_result_type)
		semantic_result_type = c_common_type (type1, type2);
	    }
	  இல்லையெனில் எனில் (ANY_INTEGRAL_TYPE_P (type2)
		   && (eptype = excess_precision_type (type1)) != NULL_மரம்)
	    {
	      eptype1 = eptype;
	      எனில் (!semantic_result_type)
		semantic_result_type = c_common_type (type1, type2);
	    }
	}
      result_type = c_common_type (eptype1, eptype2);
      எனில் (result_type == error_mark_முனை)
	திரும்பு error_mark_முனை;
      do_warn_double_promotion (result_type, type1, type2,
				"implicit conversion from %qT to %qT to "
				"match other result of conditional",
				colon_loc);

      /* If -Wsign-compare, warn here if type1 and type2 have
	 different signedness.  We'll promote the signed to unsigned
	 and later code won't know it used to be different.
	 Do this check on the original types, so that explicit casts
	 will be considered, but default promotions won't.  */
      எனில் (c_inhibit_evaluation_warnings == 0)
	{
	  முழு unsigned_op1 = TYPE_UNSIGNED (மரம்_TYPE (orig_op1));
	  முழு unsigned_op2 = TYPE_UNSIGNED (மரம்_TYPE (orig_op2));

	  எனில் (unsigned_op1 ^ unsigned_op2)
	    {
	      /* Do not warn if the result type is signed, since the
		 signed type will only be chosen if it can represent
		 all the values of the unsigned type.  */
	      எனில் (!TYPE_UNSIGNED (result_type))
		/* OK */;
	      இல்லையெனில்
		{
		  தருக்க op1_maybe_const = உண்மை;
		  தருக்க op2_maybe_const = உண்மை;

		  /* Do not warn if the signed quantity is an
		     unsuffixed integer literal (or some static
		     constant expression involving such literals) and
		     it is non-negative.  This warning requires the
		     operands to be folded for best results, so do
		     that folding in this case even without
		     warn_sign_compare to avoid warning options
		     possibly affecting code generation.  */
		  c_inhibit_evaluation_warnings
		    += (ifexp == truthvalue_false_முனை);
		  op1 = c_fully_fold (op1, require_constant_மதிப்பு,
				      &op1_maybe_const);
		  c_inhibit_evaluation_warnings
		    -= (ifexp == truthvalue_false_முனை);

		  c_inhibit_evaluation_warnings
		    += (ifexp == truthvalue_true_முனை);
		  op2 = c_fully_fold (op2, require_constant_மதிப்பு,
				      &op2_maybe_const);
		  c_inhibit_evaluation_warnings
		    -= (ifexp == truthvalue_true_முனை);

		  எனில் (warn_sign_compare)
		    {
		      எனில் ((unsigned_op2
			   && மரம்_கோவை_nonnegative_p (op1))
			  || (unsigned_op1
			      && மரம்_கோவை_nonnegative_p (op2)))
			/* OK */;
		      இல்லையெனில் எனில் (unsigned_op2)
			warning_at (op1_loc, OPT_Wsign_compare,
				    "operand of %<?:%> changes signedness from "
				    "%qT to %qT due to unsignedness of other "
				    "operand", மரம்_TYPE (orig_op1),
				    மரம்_TYPE (orig_op2));
		      இல்லையெனில்
			warning_at (op2_loc, OPT_Wsign_compare,
				    "operand of %<?:%> changes signedness from "
				    "%qT to %qT due to unsignedness of other "
				    "operand", மரம்_TYPE (orig_op2),
				    மரம்_TYPE (orig_op1));
		    }
		  எனில் (!op1_maybe_const || மரம்_CODE (op1) != INTEGER_CST)
		    op1 = c_wrap_maybe_const (op1, !op1_maybe_const);
		  எனில் (!op2_maybe_const || மரம்_CODE (op2) != INTEGER_CST)
		    op2 = c_wrap_maybe_const (op2, !op2_maybe_const);
		}
	    }
	}
    }
  இல்லையெனில் எனில் (code1 == VOID_TYPE || code2 == VOID_TYPE)
    {
      எனில் (code1 != VOID_TYPE || code2 != VOID_TYPE)
	pedwarn (colon_loc, OPT_Wpedantic,
		 "ISO C forbids conditional expr with only one void side");
      result_type = void_type_முனை;
    }
  இல்லையெனில் எனில் (code1 == POINTER_TYPE && code2 == POINTER_TYPE)
    {
      addr_space_t as1 = TYPE_ADDR_SPACE (மரம்_TYPE (type1));
      addr_space_t as2 = TYPE_ADDR_SPACE (மரம்_TYPE (type2));
      addr_space_t as_common;

      எனில் (comp_target_types (colon_loc, type1, type2))
	{
	  ifexp = save_கோவை (ifexp);
	  result_type = common_pointer_type (type1, type2, ifexp);
	}
      இல்லையெனில் எனில் (null_pointer_constant_p (orig_op1))
	result_type = type2;
      இல்லையெனில் எனில் (null_pointer_constant_p (orig_op2))
	result_type = type1;
      இல்லையெனில் எனில் (!addr_space_superset (as1, as2, &as_common))
	{
	  error_at (colon_loc, "pointers to disjoint address spaces "
		    "used in conditional expression");
	  திரும்பு error_mark_முனை;
	}
      இல்லையெனில் எனில் ((VOID_TYPE_P (மரம்_TYPE (type1))
		&& !TYPE_ATOMIC (மரம்_TYPE (type1)))
	       || (VOID_TYPE_P (மரம்_TYPE (type2))
		   && !TYPE_ATOMIC (மரம்_TYPE (type2))))
	{
	  மரம் t1 = மரம்_TYPE (type1);
	  மரம் t2 = மரம்_TYPE (type2);
	  எனில் (!(VOID_TYPE_P (t1)
		&& !TYPE_ATOMIC (t1)))
	   {
	     /* roles are swapped */
	     t1 = t2;
	     t2 = மரம்_TYPE (type1);
	   }
	  மரம் t2_stripped = strip_array_types (t2);
	  எனில் ((மரம்_CODE (t2) == ARRAY_TYPE)
	      && (TYPE_QUALS (t2_stripped) & ~TYPE_QUALS (t1)))
	    {
	      எனில் (!flag_isoc23)
		warning_at (colon_loc, OPT_Wdiscarded_array_qualifiers,
			    "pointer to array loses qualifier "
			    "in conditional expression");
	      இல்லையெனில் எனில் (warn_c11_c23_compat > 0)
		warning_at (colon_loc, OPT_Wc11_c23_compat,
			    "pointer to array loses qualifier "
			    "in conditional expression in ISO C before C23");
	    }
	  எனில் (மரம்_CODE (t2) == FUNCTION_TYPE)
	    pedwarn (colon_loc, OPT_Wpedantic,
		     "ISO C forbids conditional expr between "
		     "%<void *%> and function pointer");
	  /* for array, use qualifiers of element type */
	  எனில் (flag_isoc23)
	    t2 = t2_stripped;
	  result_type = c_build_pointer_type (qualify_type (t1, t2));
	}
      /* Objective-C pointer comparisons are a bit more lenient.  */
      இல்லையெனில் எனில் (objc_have_common_type (type1, type2, -3, NULL_மரம்))
	result_type = objc_common_type (type1, type2);
      இல்லையெனில்
	{
	  முழு qual = ENCODE_QUAL_ADDR_SPACE (as_common);
	  எண்ணிக்கை diagnostics::kind kind = diagnostics::kind::permerror;
	  எனில் (!flag_isoc99)
	    /* This downgrade to a warning ensures that -std=gnu89
	       -pedantic-errors does not flag these mismatches between
	       builtins as errors (as diagnostics::kind::permerror would)
	       ISO C99 and later do not have implicit function declarations,
	       so the mismatch cannot occur naturally there.  */
	    kind = (bltin1 && bltin2
		    ? diagnostics::kind::warning
		    : diagnostics::kind::pedwarn);
	  எனில் (emit_diagnostic (kind, colon_loc, OPT_Wincompatible_pointer_types,
			       "pointer type mismatch "
			       "in conditional expression"))
	    {
	      inform (op1_loc, "first expression has type %qT", type1);
	      inform (op2_loc, "second expression has type %qT", type2);
	    }
	  result_type = c_build_pointer_type
			  (c_build_qualified_type (void_type_முனை, qual));
	}
    }
  இல்லையெனில் எனில் (code1 == POINTER_TYPE
	   && (code2 == INTEGER_TYPE || code2 == BITINT_TYPE))
    {
      எனில் (!null_pointer_constant_p (orig_op2))
	permerror_opt (colon_loc, OPT_Wint_conversion,
		       "pointer/integer type mismatch "
		       "in conditional expression");
      இல்லையெனில்
	{
	  op2 = null_pointer_முனை;
	}
      result_type = type1;
    }
  இல்லையெனில் எனில் (code2 == POINTER_TYPE
	   && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
    {
      எனில் (!null_pointer_constant_p (orig_op1))
	permerror_opt (colon_loc, OPT_Wint_conversion,
		       "pointer/integer type mismatch "
		       "in conditional expression");
      இல்லையெனில்
	{
	  op1 = null_pointer_முனை;
	}
      result_type = type2;
    }
  /* 6.5.15: "if one is a null pointer constant (other than a pointer) or has
     type nullptr_t and the other is a pointer, the result type is the pointer
     type."  */
  இல்லையெனில் எனில் (code1 == NULLPTR_TYPE && code2 == POINTER_TYPE)
    result_type = type2;
  இல்லையெனில் எனில் (code1 == POINTER_TYPE && code2 == NULLPTR_TYPE)
    result_type = type1;
  இல்லையெனில் எனில் (RECORD_OR_UNION_TYPE_P (type1) && RECORD_OR_UNION_TYPE_P (type2)
	   && comptypes (TYPE_MAIN_VARIANT (type1),
			 TYPE_MAIN_VARIANT (type2)))
    result_type = composite_type (TYPE_MAIN_VARIANT (type1),
				  TYPE_MAIN_VARIANT (type2));

  எனில் (!result_type)
    {
      எனில் (flag_cond_mismatch)
	result_type = void_type_முனை;
      இல்லையெனில்
	{
	  error_at (colon_loc, "type mismatch in conditional expression");
	  திரும்பு error_mark_முனை;
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

  எனில் (ifexp_bcp && ifexp == truthvalue_true_முனை)
    {
      op2_int_operands = உண்மை;
      op1 = c_fully_fold (op1, require_constant_மதிப்பு, வெற்று);
    }
  எனில் (ifexp_bcp && ifexp == truthvalue_false_முனை)
    {
      op1_int_operands = உண்மை;
      op2 = c_fully_fold (op2, require_constant_மதிப்பு, வெற்று);
    }
  int_const = int_operands = (ifexp_int_operands
			      && op1_int_operands
			      && op2_int_operands);
  எனில் (int_operands)
    {
      int_const = ((ifexp == truthvalue_true_முனை
		    && மரம்_CODE (orig_op1) == INTEGER_CST
		    && !மரம்_OVERFLOW (orig_op1))
		   || (ifexp == truthvalue_false_முனை
		       && மரம்_CODE (orig_op2) == INTEGER_CST
		       && !மரம்_OVERFLOW (orig_op2)));
    }

  /* Need to convert condition operand into a vector mask.  */
  எனில் (VECTOR_TYPE_P (மரம்_TYPE (ifexp)))
    {
      மரம் vectype = மரம்_TYPE (ifexp);
      மரம் elem_type = மரம்_TYPE (vectype);
      மரம் zero = build_int_cst (elem_type, 0);
      மரம் zero_vec = build_vector_from_val (vectype, zero);
      மரம் cmp_type = truth_type_for (vectype);
      ifexp = build2 (NE_கோவை, cmp_type, ifexp, zero_vec);
    }

  எனில் (int_const || (ifexp_bcp && மரம்_CODE (ifexp) == INTEGER_CST))
    ret = fold_build3_loc (colon_loc, COND_கோவை, result_type, ifexp, op1, op2);
  இல்லையெனில்
    {
      எனில் (int_operands)
	{
	  /* Use c_fully_fold here, since C_MAYBE_CONST_EXPR might be
	     nested inside of the expression.  */
	  op1 = c_fully_fold (op1, பொய், வெற்று);
	  op2 = c_fully_fold (op2, பொய், வெற்று);
	}
      ret = build3 (COND_கோவை, result_type, ifexp, op1, op2);
      எனில் (int_operands)
	ret = note_integer_operands (ret);
    }
  எனில் (semantic_result_type)
    ret = build1 (EXCESS_PRECISION_கோவை, semantic_result_type, ret);

  protected_set_கோவை_location (ret, colon_loc);

  /* If the OP1 and OP2 are the same and don't have side-effects,
     warn here, because the COND_EXPR will be turned into OP1.  */
  எனில் (warn_duplicated_branches
      && மரம்_CODE (ret) == COND_கோவை
      && (op1 == op2 || operand_equal_p (op1, op2, OEP_ADDRESS_OF_SAME_FIELD)))
    warning_at (கோவை_LOCATION (ret), OPT_Wduplicated_branches,
		"this condition has identical branches");

  திரும்பு ret;
}

/* EXPR is an expression, location LOC, whose result is discarded.
   Warn if it is a call to a nodiscard function (or a COMPOUND_EXPR
   whose right-hand operand is such a call, possibly recursively).  */

நிலையான வெறுமை
maybe_warn_nodiscard (location_t loc, மரம் கோவை)
{
  எனில் (VOID_TYPE_P (மரம்_TYPE (கோவை)))
    திரும்பு;
  போது (மரம்_CODE (கோவை) == COMPOUND_கோவை)
    {
      கோவை = மரம்_OPERAND (கோவை, 1);
      எனில் (கோவை_HAS_LOCATION (கோவை))
	loc = கோவை_LOCATION (கோவை);
    }
  எனில் (மரம்_CODE (கோவை) != CALL_கோவை)
    திரும்பு;
  மரம் fn = CALL_கோவை_FN (கோவை);
  எனில் (!fn)
    திரும்பு;
  மரம் attr;
  எனில் (மரம்_CODE (fn) == ADDR_கோவை
      && மரம்_CODE (மரம்_OPERAND (fn, 0)) == FUNCTION_DECL
      && (attr = lookup_attribute ("nodiscard",
				   DECL_ATTRIBUTES (மரம்_OPERAND (fn, 0)))))
    {
      fn = மரம்_OPERAND (fn, 0);
      மரம் args = மரம்_மதிப்பு (attr);
      எனில் (args)
	args = மரம்_மதிப்பு (args);
      auto_diagnostic_group d;
      auto_urlify_attributes sentinel;
      முழு warned;
      எனில் (args)
	warned = warning_at (loc, OPT_Wunused_result,
			     "ignoring return value of %qD, declared with "
			     "attribute %<nodiscard%>: %E", fn, args);
      இல்லையெனில்
	warned = warning_at (loc, OPT_Wunused_result,
			     "ignoring return value of %qD, declared with "
			     "attribute %<nodiscard%>", fn);
      எனில் (warned)
	inform (DECL_SOURCE_LOCATION (fn), "declared here");
    }
  இல்லையெனில்
    {
      மரம் rettype = மரம்_TYPE (மரம்_TYPE (மரம்_TYPE (fn)));
      attr = lookup_attribute ("nodiscard", TYPE_ATTRIBUTES (rettype));
      எனில் (!attr)
	திரும்பு;
      மரம் args = மரம்_மதிப்பு (attr);
      எனில் (args)
	args = மரம்_மதிப்பு (args);
      auto_diagnostic_group d;
      auto_urlify_attributes sentinel;
      முழு warned;
      எனில் (args)
	warned = warning_at (loc, OPT_Wunused_result,
			     "ignoring return value of type %qT, declared "
			     "with attribute %<nodiscard%>: %E",
			     rettype, args);
      இல்லையெனில்
	warned = warning_at (loc, OPT_Wunused_result,
			     "ignoring return value of type %qT, declared "
			     "with attribute %<nodiscard%>", rettype);
      எனில் (warned)
	{
	  எனில் (மரம்_CODE (fn) == ADDR_கோவை)
	    {
	      fn = மரம்_OPERAND (fn, 0);
	      எனில் (மரம்_CODE (fn) == FUNCTION_DECL)
		inform (DECL_SOURCE_LOCATION (fn),
			"in call to %qD, declared here", fn);
	    }
	}
    }
}

/* Return a compound expression that performs two expressions and
   returns the value of the second of them.

   LOC is the location of the COMPOUND_EXPR.  */

மரம்
build_compound_கோவை (location_t loc, மரம் expr1, மரம் expr2)
{
  தருக்க expr1_int_operands, expr2_int_operands;
  மரம் eptype = NULL_மரம்;
  மரம் ret;

  expr1_int_operands = கோவை_INT_CONST_OPERANDS (expr1);
  எனில் (expr1_int_operands)
    expr1 = remove_c_maybe_const_கோவை (expr1);
  expr2_int_operands = கோவை_INT_CONST_OPERANDS (expr2);
  எனில் (expr2_int_operands)
    expr2 = remove_c_maybe_const_கோவை (expr2);

  எனில் (மரம்_CODE (expr1) == EXCESS_PRECISION_கோவை)
    expr1 = மரம்_OPERAND (expr1, 0);
  எனில் (மரம்_CODE (expr2) == EXCESS_PRECISION_கோவை)
    {
      eptype = மரம்_TYPE (expr2);
      expr2 = மரம்_OPERAND (expr2, 0);
    }

  எனில் (!மரம்_SIDE_EFFECTS (expr1))
    {
      /* The left-hand operand of a comma expression is like an expression
	 statement: with -Wunused, we should warn if it doesn't have
	 any side-effects, unless it was explicitly cast to (void).  */
      எனில் (warn_unused_மதிப்பு)
	{
	  எனில் (VOID_TYPE_P (மரம்_TYPE (expr1))
	      && CONVERT_கோவை_P (expr1))
	    ; /* (void) a, b */
	  இல்லையெனில் எனில் (VOID_TYPE_P (மரம்_TYPE (expr1))
		   && மரம்_CODE (expr1) == COMPOUND_கோவை
		   && CONVERT_கோவை_P (மரம்_OPERAND (expr1, 1)))
	    ; /* (void) a, (void) b, c */
	  இல்லையெனில்
	    warning_at (loc, OPT_Wunused_மதிப்பு,
			"left-hand operand of comma expression has no effect");
	}
    }
  இல்லையெனில் எனில் (மரம்_CODE (expr1) == COMPOUND_கோவை
	   && warn_unused_மதிப்பு)
    {
      மரம் r = expr1;
      location_t cloc = loc;
      போது (மரம்_CODE (r) == COMPOUND_கோவை)
        {
	  எனில் (கோவை_HAS_LOCATION (r))
	    cloc = கோவை_LOCATION (r);
	  r = மரம்_OPERAND (r, 1);
	}
      எனில் (!மரம்_SIDE_EFFECTS (r)
	  && !VOID_TYPE_P (மரம்_TYPE (r))
	  && !CONVERT_கோவை_P (r))
	warning_at (cloc, OPT_Wunused_மதிப்பு,
	            "right-hand operand of comma expression has no effect");
    }

  /* With -Wunused, we should also warn if the left-hand operand does have
     side-effects, but computes a value which is not used.  For example, in
     `foo() + bar(), baz()' the result of the `+' operator is not used,
     so we should issue a warning.  */
  இல்லையெனில் எனில் (warn_unused_மதிப்பு)
    warn_if_unused_மதிப்பு (expr1, loc);

  maybe_warn_nodiscard (loc, expr1);

  எனில் (expr2 == error_mark_முனை)
    திரும்பு error_mark_முனை;

  ret = build2 (COMPOUND_கோவை, மரம்_TYPE (expr2), expr1, expr2);

  எனில் (flag_isoc99
      && expr1_int_operands
      && expr2_int_operands)
    ret = note_integer_operands (ret);

  எனில் (eptype)
    ret = build1 (EXCESS_PRECISION_கோவை, eptype, ret);

  protected_set_கோவை_location (ret, loc);
  திரும்பு ret;
}

/* Issue -Wcast-qual warnings when appropriate.  TYPE is the type to
   which we are casting.  OTYPE is the type of the expression being
   cast.  Both TYPE and OTYPE are pointer types.  LOC is the location
   of the cast.  -Wcast-qual appeared on the command line.  Named
   address space qualifiers are not handled here, because they result
   in different warnings.  */

நிலையான வெறுமை
handle_warn_cast_qual (location_t loc, மரம் type, மரம் otype)
{
  மரம் in_type = type;
  மரம் in_otype = otype;
  முழு added = 0;
  முழு discarded = 0;
  தருக்க is_const;

  /* Check that the qualifiers on IN_TYPE are a superset of the
     qualifiers of IN_OTYPE.  The outermost level of POINTER_TYPE
     nodes is uninteresting and we stop as soon as we hit a
     non-POINTER_TYPE node on either type.  */
  செய்
    {
      in_otype = மரம்_TYPE (in_otype);
      in_type = மரம்_TYPE (in_type);

      /* GNU C allows cv-qualified function types.  'const' means the
	 function is very pure, 'volatile' means it can't return.  We
	 need to warn when such qualifiers are added, not when they're
	 taken away.  */
      எனில் (மரம்_CODE (in_otype) == FUNCTION_TYPE
	  && மரம்_CODE (in_type) == FUNCTION_TYPE)
	added |= (TYPE_QUALS_NO_ADDR_SPACE (in_type)
		  & ~TYPE_QUALS_NO_ADDR_SPACE (in_otype));
      இல்லையெனில்
	discarded |= (TYPE_QUALS_NO_ADDR_SPACE (in_otype)
		      & ~TYPE_QUALS_NO_ADDR_SPACE (in_type));
    }
  போது (மரம்_CODE (in_type) == POINTER_TYPE
	 && மரம்_CODE (in_otype) == POINTER_TYPE);

  எனில் (added)
    warning_at (loc, OPT_Wcast_qual,
		"cast adds %q#v qualifier to function type", added);

  எனில் (discarded)
    /* There are qualifiers present in IN_OTYPE that are not present
       in IN_TYPE.  */
    warning_at (loc, OPT_Wcast_qual,
		"cast discards %qv qualifier from pointer target type",
		discarded);

  எனில் (added || discarded)
    திரும்பு;

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

  எனில் (TYPE_MAIN_VARIANT (in_type) != TYPE_MAIN_VARIANT (in_otype))
    திரும்பு;
  எனில் (மரம்_CODE (மரம்_TYPE (type)) != POINTER_TYPE)
    திரும்பு;

  in_type = type;
  in_otype = otype;
  is_const = TYPE_READONLY (மரம்_TYPE (in_type));
  செய்
    {
      in_type = மரம்_TYPE (in_type);
      in_otype = மரம்_TYPE (in_otype);
      எனில் ((TYPE_QUALS (in_type) &~ TYPE_QUALS (in_otype)) != 0
	  && !is_const)
	{
	  warning_at (loc, OPT_Wcast_qual,
		      "to be safe all intermediate pointers in cast from "
                      "%qT to %qT must be %<const%> qualified",
		      otype, type);
	  நிறுத்து;
	}
      எனில் (is_const)
	is_const = TYPE_READONLY (in_type);
    }
  போது (மரம்_CODE (in_type) == POINTER_TYPE);
}

/* Heuristic check if two parameter types can be considered ABI-equivalent.  */

நிலையான தருக்க
c_safe_arg_type_equiv_p (மரம் t1, மரம் t2)
{
  எனில் (error_operand_p (t1) || error_operand_p (t2))
    திரும்பு உண்மை;

  t1 = TYPE_MAIN_VARIANT (t1);
  t2 = TYPE_MAIN_VARIANT (t2);

  எனில் (மரம்_CODE (t1) == POINTER_TYPE
      && மரம்_CODE (t2) == POINTER_TYPE)
    திரும்பு உண்மை;

  /* Only the precision of the parameter matters.  This check should
     make sure that the callee does not see undefined values in argument
     registers.  */
  எனில் (INTEGRAL_TYPE_P (t1)
      && INTEGRAL_TYPE_P (t2)
      && TYPE_PRECISION (t1) == TYPE_PRECISION (t2))
    திரும்பு உண்மை;

  திரும்பு comptypes (t1, t2);
}

/* Check if a type cast between two function types can be considered safe.  */

நிலையான தருக்க
c_safe_function_type_cast_p (மரம் t1, மரம் t2)
{
  எனில் (மரம்_TYPE (t1) == void_type_முனை &&
      TYPE_ARG_TYPES (t1) == void_list_முனை)
    திரும்பு உண்மை;

  எனில் (மரம்_TYPE (t2) == void_type_முனை &&
      TYPE_ARG_TYPES (t2) == void_list_முனை)
    திரும்பு உண்மை;

  எனில் (!c_safe_arg_type_equiv_p (மரம்_TYPE (t1), மரம்_TYPE (t2)))
    திரும்பு பொய்;

  க்கு (t1 = TYPE_ARG_TYPES (t1), t2 = TYPE_ARG_TYPES (t2);
       t1 && t2;
       t1 = மரம்_CHAIN (t1), t2 = மரம்_CHAIN (t2))
    எனில் (!c_safe_arg_type_equiv_p (மரம்_மதிப்பு (t1), மரம்_மதிப்பு (t2)))
      திரும்பு பொய்;

  திரும்பு உண்மை;
}

/* Build an expression representing a cast to type TYPE of expression EXPR.
   LOC is the location of the cast-- typically the open paren of the cast.  */

மரம்
build_c_cast (location_t loc, மரம் type, மரம் கோவை)
{
  மரம் மதிப்பு;

  தருக்க int_operands = கோவை_INT_CONST_OPERANDS (கோவை);

  எனில் (மரம்_CODE (கோவை) == EXCESS_PRECISION_கோவை)
    கோவை = மரம்_OPERAND (கோவை, 0);

  மதிப்பு = கோவை;
  எனில் (int_operands)
    மதிப்பு = remove_c_maybe_const_கோவை (மதிப்பு);

  எனில் (type == error_mark_முனை || கோவை == error_mark_முனை)
    திரும்பு error_mark_முனை;

  /* The ObjC front-end uses TYPE_MAIN_VARIANT to tie together types differing
     only in <protocol> qualifications.  But when constructing cast expressions,
     the protocols do matter and must be kept around.  */
  எனில் (objc_is_object_ptr (type) && objc_is_object_ptr (மரம்_TYPE (கோவை)))
    திரும்பு build1 (NOP_கோவை, type, கோவை);

  type = TYPE_MAIN_VARIANT (type);

  எனில் (மரம்_CODE (type) == ARRAY_TYPE)
    {
      error_at (loc, "cast specifies array type");
      திரும்பு error_mark_முனை;
    }

  எனில் (மரம்_CODE (type) == FUNCTION_TYPE)
    {
      error_at (loc, "cast specifies function type");
      திரும்பு error_mark_முனை;
    }

  எனில் (!VOID_TYPE_P (type))
    {
      மதிப்பு = require_complete_type (loc, மதிப்பு);
      எனில் (மதிப்பு == error_mark_முனை)
	திரும்பு error_mark_முனை;
    }

  எனில் (type == TYPE_MAIN_VARIANT (மரம்_TYPE (மதிப்பு)))
    {
      எனில் (RECORD_OR_UNION_TYPE_P (type)
	  && pedwarn (loc, OPT_Wpedantic,
		      "ISO C forbids casting nonscalar to the same type"))
	      ;
      இல்லையெனில் எனில் (warn_useless_cast && c_inhibit_evaluation_warnings == 0)
	warning_at (loc, OPT_Wuseless_cast,
		    "useless cast to type %qT", type);

      /* Convert to remove any qualifiers from VALUE's type.  */
      மதிப்பு = convert (type, மதிப்பு);
    }
  இல்லையெனில் எனில் (மரம்_CODE (type) == UNION_TYPE)
    {
      மரம் field;

      க்கு (field = TYPE_FIELDS (type); field; field = DECL_CHAIN (field))
	எனில் (மரம்_TYPE (field) != error_mark_முனை
	    && comptypes (TYPE_MAIN_VARIANT (மரம்_TYPE (field)),
			  TYPE_MAIN_VARIANT (மரம்_TYPE (மதிப்பு))))
	  நிறுத்து;

      எனில் (field)
	{
	  மரம் t;
	  தருக்க maybe_const = உண்மை;

	  pedwarn (loc, OPT_Wpedantic, "ISO C forbids casts to union type");
	  t = c_fully_fold (மதிப்பு, பொய், &maybe_const);
	  t = build_constructor_single (type, field, t);
	  எனில் (!maybe_const)
	    t = c_wrap_maybe_const (t, உண்மை);
	  t = digest_init (loc, field, type, t,
			   NULL_மரம், பொய், பொய், பொய், உண்மை, பொய், பொய்);
	  மரம்_CONSTANT (t) = மரம்_CONSTANT (மதிப்பு);
	  திரும்பு t;
	}
      error_at (loc, "cast to union type from type not present in union");
      திரும்பு error_mark_முனை;
    }
  இல்லையெனில்
    {
      மரம் otype, ovalue;

      எனில் (type == void_type_முனை)
	{
	  மரம் t = build1 (CONVERT_கோவை, type, மதிப்பு);
	  SET_கோவை_LOCATION (t, loc);
	  திரும்பு t;
	}

      otype = மரம்_TYPE (மதிப்பு);

      /* Optionally warn about potentially worrisome casts.  */
      எனில் (warn_cast_qual
	  && மரம்_CODE (type) == POINTER_TYPE
	  && மரம்_CODE (otype) == POINTER_TYPE)
	handle_warn_cast_qual (loc, type, otype);

      /* Warn about conversions between pointers to disjoint
	 address spaces.  */
      எனில் (மரம்_CODE (type) == POINTER_TYPE
	  && மரம்_CODE (otype) == POINTER_TYPE
	  && !null_pointer_constant_p (மதிப்பு))
	{
	  addr_space_t as_to = TYPE_ADDR_SPACE (மரம்_TYPE (type));
	  addr_space_t as_from = TYPE_ADDR_SPACE (மரம்_TYPE (otype));
	  addr_space_t as_common;

	  எனில் (!addr_space_superset (as_to, as_from, &as_common))
	    {
	      எனில் (ADDR_SPACE_GENERIC_P (as_from))
		warning_at (loc, 0, "cast to %qs address space pointer "
			    "from disjoint generic address space pointer",
			    c_addr_space_name (as_to));

	      இல்லையெனில் எனில் (ADDR_SPACE_GENERIC_P (as_to))
		warning_at (loc, 0, "cast to generic address space pointer "
			    "from disjoint %qs address space pointer",
			    c_addr_space_name (as_from));

	      இல்லையெனில்
		warning_at (loc, 0, "cast to %qs address space pointer "
			    "from disjoint %qs address space pointer",
			    c_addr_space_name (as_to),
			    c_addr_space_name (as_from));
	    }

	  /* Warn of new allocations that are not big enough for the target
	     type.  */
	  எனில் (warn_alloc_size && மரம்_CODE (மதிப்பு) == CALL_கோவை)
	    எனில் (மரம் fndecl = get_callee_fndecl (மதிப்பு))
	      எனில் (DECL_IS_MALLOC (fndecl))
		{
		  மரம் attrs = TYPE_ATTRIBUTES (மரம்_TYPE (fndecl));
		  மரம் alloc_size = lookup_attribute ("alloc_size", attrs);
		  எனில் (alloc_size)
		    warn_for_alloc_size (loc, மரம்_TYPE (type), மதிப்பு,
					 alloc_size);
		}
	}

      /* Warn about possible alignment problems.  */
      எனில் ((STRICT_ALIGNMENT || warn_cast_align == 2)
	  && மரம்_CODE (type) == POINTER_TYPE
	  && மரம்_CODE (otype) == POINTER_TYPE
	  && மரம்_CODE (மரம்_TYPE (otype)) != VOID_TYPE
	  && மரம்_CODE (மரம்_TYPE (otype)) != FUNCTION_TYPE
	  /* Don't warn about opaque types, where the actual alignment
	     restriction is unknown.  */
	  && !(RECORD_OR_UNION_TYPE_P (மரம்_TYPE (otype))
	       && TYPE_MODE (மரம்_TYPE (otype)) == VOIDmode)
	  && min_align_of_type (மரம்_TYPE (type))
	     > min_align_of_type (மரம்_TYPE (otype)))
	warning_at (loc, OPT_Wcast_align,
		    "cast increases required alignment of target type");

      எனில் ((மரம்_CODE (type) == INTEGER_TYPE
	   || மரம்_CODE (type) == BITINT_TYPE)
	  && மரம்_CODE (otype) == POINTER_TYPE
	  && TYPE_PRECISION (type) != TYPE_PRECISION (otype))
      /* Unlike conversion of integers to pointers, where the
         warning is disabled for converting constants because
         of cases such as SIG_*, warn about converting constant
         pointers to integers. In some cases it may cause unwanted
         sign extension, and a warning is appropriate.  */
	warning_at (loc, OPT_Wpointer_to_int_cast,
		    "cast from pointer to integer of different size");

      எனில் ((மரம்_CODE (மதிப்பு) == CALL_கோவை
	   && !is_access_with_size_p (மதிப்பு))
	  && மரம்_CODE (type) != மரம்_CODE (otype))
	warning_at (loc, OPT_Wbad_function_cast,
		    "cast from function call of type %qT "
		    "to non-matching type %qT", otype, type);

      எனில் (மரம்_CODE (type) == POINTER_TYPE
	  && (மரம்_CODE (otype) == INTEGER_TYPE
	      || மரம்_CODE (otype) == BITINT_TYPE)
	  && TYPE_PRECISION (type) != TYPE_PRECISION (otype)
	  /* Don't warn about converting any constant.  */
	  && !மரம்_CONSTANT (மதிப்பு))
	warning_at (loc,
		    OPT_Wint_to_pointer_cast, "cast to pointer from integer "
		    "of different size");

      எனில் (warn_strict_aliasing <= 2)
        strict_aliasing_warning (கோவை_LOCATION (மதிப்பு), type, கோவை);

      /* If pedantic, warn for conversions between function and object
	 pointer types, except for converting a null pointer constant
	 to function pointer type.  */
      எனில் (pedantic
	  && மரம்_CODE (type) == POINTER_TYPE
	  && மரம்_CODE (otype) == POINTER_TYPE
	  && மரம்_CODE (மரம்_TYPE (otype)) == FUNCTION_TYPE
	  && மரம்_CODE (மரம்_TYPE (type)) != FUNCTION_TYPE)
	pedwarn (loc, OPT_Wpedantic, "ISO C forbids "
		 "conversion of function pointer to object pointer type");

      எனில் (pedantic
	  && மரம்_CODE (type) == POINTER_TYPE
	  && மரம்_CODE (otype) == POINTER_TYPE
	  && மரம்_CODE (மரம்_TYPE (type)) == FUNCTION_TYPE
	  && மரம்_CODE (மரம்_TYPE (otype)) != FUNCTION_TYPE
	  && !null_pointer_constant_p (மதிப்பு))
	pedwarn (loc, OPT_Wpedantic, "ISO C forbids "
		 "conversion of object pointer to function pointer type");

      எனில் (மரம்_CODE (type) == POINTER_TYPE
	  && மரம்_CODE (otype) == POINTER_TYPE
	  && மரம்_CODE (மரம்_TYPE (type)) == FUNCTION_TYPE
	  && மரம்_CODE (மரம்_TYPE (otype)) == FUNCTION_TYPE
	  && !c_safe_function_type_cast_p (மரம்_TYPE (type),
					   மரம்_TYPE (otype)))
	warning_at (loc, OPT_Wcast_function_type,
		    "cast between incompatible function types"
		    " from %qT to %qT", otype, type);

      ovalue = மதிப்பு;
      /* If converting to boolean a value with integer operands that
	 is not itself represented as an INTEGER_CST, the call below
	 to note_integer_operands may insert a C_MAYBE_CONST_EXPR, but
	 build_binary_op as called by c_common_truthvalue_conversion
	 may also insert a C_MAYBE_CONST_EXPR to indicate that a
	 subexpression has been fully folded.  To avoid nested
	 C_MAYBE_CONST_EXPR, ensure that
	 c_objc_common_truthvalue_conversion receives an argument
	 properly marked as having integer operands in that case.  */
      எனில் (int_operands
	  && மரம்_CODE (மதிப்பு) != INTEGER_CST
	  && (மரம்_CODE (type) == BOOLEAN_TYPE
	      || (மரம்_CODE (type) == ENUMERAL_TYPE
		  && ENUM_UNDERLYING_TYPE (type) != NULL_மரம்
		  && மரம்_CODE (ENUM_UNDERLYING_TYPE (type)) == BOOLEAN_TYPE)))
	மதிப்பு = note_integer_operands (மதிப்பு);
      மதிப்பு = convert (type, மதிப்பு);

      /* Ignore any integer overflow caused by the cast.  */
      எனில் (மரம்_CODE (மதிப்பு) == INTEGER_CST && !FLOAT_TYPE_P (otype))
	{
	  எனில் (மரம்_OVERFLOW_P (ovalue))
	    {
	      எனில் (!மரம்_OVERFLOW (மதிப்பு))
		{
		  /* Avoid clobbering a shared constant.  */
		  மதிப்பு = copy_முனை (மதிப்பு);
		  மரம்_OVERFLOW (மதிப்பு) = மரம்_OVERFLOW (ovalue);
		}
	    }
	  இல்லையெனில் எனில் (மரம்_OVERFLOW (மதிப்பு))
	    /* Reset VALUE's overflow flags, ensuring constant sharing.  */
	    மதிப்பு = wide_int_to_மரம் (மரம்_TYPE (மதிப்பு), wi::to_wide (மதிப்பு));
	}
    }

  /* Don't let a cast be an lvalue.  */
  எனில் (lvalue_p (மதிப்பு)
      /* Also, don't let a cast be a bit-field of a bit-precise integer type,
	 otherwise it could be incorrectly subject of integer promotions.  */
      || (மரம்_CODE (மதிப்பு) == COMPONENT_REF
	  && DECL_C_BIT_FIELD (மரம்_OPERAND (மதிப்பு, 1))
	  && BITINT_TYPE_P (DECL_BIT_FIELD_TYPE (மரம்_OPERAND (மதிப்பு, 1)))))
    மதிப்பு = non_lvalue_loc (loc, மதிப்பு);

  /* Don't allow the results of casting to floating-point or complex
     types be confused with actual constants, or casts involving
     integer and pointer types other than direct integer-to-integer
     and integer-to-pointer be confused with integer constant
     expressions and null pointer constants.  */
  எனில் (மரம்_CODE (மதிப்பு) == REAL_CST
      || மரம்_CODE (மதிப்பு) == COMPLEX_CST
      || (மரம்_CODE (மதிப்பு) == INTEGER_CST
	  && !((மரம்_CODE (கோவை) == INTEGER_CST
		&& INTEGRAL_TYPE_P (மரம்_TYPE (கோவை)))
	       || மரம்_CODE (கோவை) == REAL_CST
	       || மரம்_CODE (கோவை) == COMPLEX_CST)))
      மதிப்பு = build1 (NOP_கோவை, type, மதிப்பு);

  /* If the expression has integer operands and so can occur in an
     unevaluated part of an integer constant expression, ensure the
     return value reflects this.  */
  எனில் (int_operands
      && INTEGRAL_TYPE_P (type)
      && மதிப்பு != error_mark_முனை
      && !கோவை_INT_CONST_OPERANDS (மதிப்பு))
    மதிப்பு = note_integer_operands (மதிப்பு);

  protected_set_கோவை_location (மதிப்பு, loc);
  திரும்பு மதிப்பு;
}

/* Interpret a cast of expression EXPR to type TYPE.  LOC is the
   location of the open paren of the cast, or the position of the cast
   expr.  */
மரம்
c_cast_கோவை (location_t loc, கட்டமைப்பு c_type_name *type_name, மரம் கோவை)
{
  மரம் type;
  மரம் type_கோவை = NULL_மரம்;
  தருக்க type_கோவை_const = உண்மை;
  மரம் ret;
  முழு saved_wsp = warn_strict_prototypes;

  /* This avoids warnings about unprototyped casts on
     integers.  E.g. "#define SIG_DFL (void(*)())0".  */
  எனில் (மரம்_CODE (கோவை) == INTEGER_CST)
    warn_strict_prototypes = 0;
  type = groktypename (type_name, &type_கோவை, &type_கோவை_const);
  warn_strict_prototypes = saved_wsp;

  எனில் (மரம்_CODE (கோவை) == ADDR_கோவை && !VOID_TYPE_P (type)
      && reject_gcc_builtin (கோவை))
    திரும்பு error_mark_முனை;

  ret = build_c_cast (loc, type, கோவை);
  எனில் (ret == error_mark_முனை)
    திரும்பு error_mark_முனை;

  எனில் (type_கோவை)
    {
      தருக்க inner_கோவை_const = உண்மை;
      ret = c_fully_fold (ret, require_constant_மதிப்பு, &inner_கோவை_const);
      ret = build2 (C_MAYBE_CONST_கோவை, மரம்_TYPE (ret), type_கோவை, ret);
      C_MAYBE_CONST_கோவை_NON_CONST (ret) = !(type_கோவை_const
					     && inner_கோவை_const);
      SET_கோவை_LOCATION (ret, loc);
    }

  எனில் (!கோவை_HAS_LOCATION (ret))
    protected_set_கோவை_location (ret, loc);

  /* C++ does not permits types to be defined in a cast, but it
     allows references to incomplete types.  */
  எனில் (warn_cxx_compat && type_name->specs->typespec_kind == ctsk_tagdef)
    warning_at (loc, OPT_Wc___compat,
		"defining a type in a cast is invalid in C++");

  திரும்பு ret;
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

மரம்
build_modify_கோவை (location_t location, மரம் lhs, மரம் lhs_origtype,
		   எண்ணிக்கை மரம்_code modifycode,
		   location_t rhs_loc, மரம் rhs, மரம் rhs_origtype)
{
  மரம் result;
  மரம் newrhs;
  மரம் rhseval = NULL_மரம்;
  மரம் lhstype = மரம்_TYPE (lhs);
  மரம் olhstype = lhstype;
  தருக்க npc;
  தருக்க is_atomic_op;

  /* Types that aren't fully specified cannot be used in assignments.  */
  lhs = require_complete_type (location, lhs);
  rhs = require_complete_type (location, rhs);

  /* Avoid duplicate error messages from operands that had errors.  */
  எனில் (மரம்_CODE (lhs) == ERROR_MARK || மரம்_CODE (rhs) == ERROR_MARK)
    திரும்பு error_mark_முனை;

  /* Ensure an error for assigning a non-lvalue array to an array in
     C90.  */
  எனில் (மரம்_CODE (lhstype) == ARRAY_TYPE)
    {
      error_at (location, "assignment to expression with array type");
      திரும்பு error_mark_முனை;
    }

  /* For ObjC properties, defer this check.  */
  எனில் (!objc_is_property_ref (lhs) && !lvalue_or_else (location, lhs, lv_assign))
    திரும்பு error_mark_முனை;

  is_atomic_op = really_atomic_lvalue (lhs);

  newrhs = rhs;

  எனில் (மரம்_CODE (lhs) == C_MAYBE_CONST_கோவை)
    {
      மரம் inner = build_modify_கோவை (location, C_MAYBE_CONST_கோவை_கோவை (lhs),
				      lhs_origtype, modifycode, rhs_loc, rhs,
				      rhs_origtype);
      எனில் (inner == error_mark_முனை)
	திரும்பு error_mark_முனை;
      result = build2 (C_MAYBE_CONST_கோவை, மரம்_TYPE (inner),
		       C_MAYBE_CONST_கோவை_PRE (lhs), inner);
      gcc_assert (!C_MAYBE_CONST_கோவை_INT_OPERANDS (lhs));
      C_MAYBE_CONST_கோவை_NON_CONST (result) = 1;
      protected_set_கோவை_location (result, location);
      திரும்பு result;
    }

  /* If a binary op has been requested, combine the old LHS value with the RHS
     producing the value we should actually store into the LHS.  */

  எனில் (modifycode != NOP_கோவை)
    {
      lhs = c_fully_fold (lhs, பொய், வெற்று, உண்மை);
      lhs = stabilize_reference (lhs);

      /* Construct the RHS for any non-atomic compound assignment. */
      எனில் (!is_atomic_op)
        {
	  /* If in LHS op= RHS the RHS has side-effects, ensure they
	     are preevaluated before the rest of the assignment expression's
	     side-effects, because RHS could contain e.g. function calls
	     that modify LHS.  */
	  எனில் (மரம்_SIDE_EFFECTS (rhs))
	    {
	      எனில் (மரம்_CODE (rhs) == EXCESS_PRECISION_கோவை)
		newrhs = save_கோவை (மரம்_OPERAND (rhs, 0));
	      இல்லையெனில்
		newrhs = save_கோவை (rhs);
	      rhseval = newrhs;
	      எனில் (மரம்_CODE (rhs) == EXCESS_PRECISION_கோவை)
		newrhs = build1 (EXCESS_PRECISION_கோவை, மரம்_TYPE (rhs),
				 newrhs);
	    }
	  தருக்க clear_decl_read = பொய்;
	  எனில் ((VAR_P (lhs) || மரம்_CODE (lhs) == PARM_DECL)
	      && !DECL_READ_P (lhs)
	      && (VAR_P (lhs) ? warn_unused_but_set_variable
			      : warn_unused_but_set_parameter) > 2)
	    {
	      mark_exp_read (newrhs);
	      எனில் (!DECL_READ_P (lhs))
		clear_decl_read = உண்மை;
	    }

	  newrhs = build_இருமம்_op (location, modifycode,
				    convert_lvalue_to_rvalue (location, lhs,
							      உண்மை, உண்மை),
				    newrhs, உண்மை);
	  எனில் (clear_decl_read)
	    DECL_READ_P (lhs) = 0;

	  /* The original type of the right hand side is no longer
	     meaningful.  */
	  rhs_origtype = NULL_மரம்;
	}
    }

  எனில் (c_dialect_objc ())
    {
      /* Check if we are modifying an Objective-C property reference;
	 if so, we need to generate setter calls.  */
      எனில் (மரம்_CODE (newrhs) == EXCESS_PRECISION_கோவை)
	result = objc_maybe_build_modify_கோவை (lhs, மரம்_OPERAND (newrhs, 0));
      இல்லையெனில்
	result = objc_maybe_build_modify_கோவை (lhs, newrhs);
      எனில் (result)
	செல் return_result;

      /* Else, do the check that we postponed for Objective-C.  */
      எனில் (!lvalue_or_else (location, lhs, lv_assign))
	திரும்பு error_mark_முனை;
    }

  /* Give an error for storing in something that is 'const'.  */

  எனில் (TYPE_READONLY (lhstype)
      || (RECORD_OR_UNION_TYPE_P (lhstype)
	  && C_TYPE_FIELDS_READONLY (lhstype)))
    {
      readonly_error (location, lhs, lv_assign);
      திரும்பு error_mark_முனை;
    }
  இல்லையெனில் எனில் (மரம்_READONLY (lhs))
    readonly_warning (lhs, lv_assign);

  /* If storing into a structure or union member,
     it has probably been given type `int'.
     Compute the type that would go with
     the actual amount of storage the member occupies.  */

  எனில் (மரம்_CODE (lhs) == COMPONENT_REF
      && (மரம்_CODE (lhstype) == INTEGER_TYPE
	  || மரம்_CODE (lhstype) == BOOLEAN_TYPE
	  || SCALAR_FLOAT_TYPE_P (lhstype)
	  || மரம்_CODE (lhstype) == ENUMERAL_TYPE))
    lhstype = மரம்_TYPE (get_unwidened (lhs, 0));

  /* If storing in a field that is in actuality a short or narrower than one,
     we must store in the field in its actual type.  */

  எனில் (lhstype != மரம்_TYPE (lhs))
    {
      lhs = copy_முனை (lhs);
      மரம்_TYPE (lhs) = lhstype;
    }

  /* Issue -Wc++-compat warnings about an assignment to an enum type
     when LHS does not have its original type.  This happens for,
     e.g., an enum bitfield in a struct.  */
  எனில் (warn_cxx_compat
      && lhs_origtype != NULL_மரம்
      && lhs_origtype != lhstype
      && மரம்_CODE (lhs_origtype) == ENUMERAL_TYPE)
    {
      மரம் checktype = (rhs_origtype != NULL_மரம்
			? rhs_origtype
			: மரம்_TYPE (rhs));
      எனில் (checktype != error_mark_முனை
	  && (TYPE_MAIN_VARIANT (checktype) != TYPE_MAIN_VARIANT (lhs_origtype)
	      || (is_atomic_op && modifycode != NOP_கோவை)))
	warning_at (location, OPT_Wc___compat,
		    "enum conversion in assignment is invalid in C++");
    }

  /* Remove qualifiers.  */
  lhstype = c_build_qualified_type (lhstype, TYPE_UNQUALIFIED);
  olhstype = c_build_qualified_type (olhstype, TYPE_UNQUALIFIED);

  /* Convert new value to destination type.  Fold it first, then
     restore any excess precision information, for the sake of
     conversion warnings.  */

  எனில் (!(is_atomic_op && modifycode != NOP_கோவை))
    {
      மரம் rhs_semantic_type = NULL_மரம்;
      எனில் (!c_in_omp_for)
	{
	  எனில் (மரம்_CODE (newrhs) == EXCESS_PRECISION_கோவை)
	    {
	      rhs_semantic_type = மரம்_TYPE (newrhs);
	      newrhs = மரம்_OPERAND (newrhs, 0);
	    }
	  npc = null_pointer_constant_p (newrhs);
	  newrhs = c_fully_fold (newrhs, பொய், வெற்று);
	  எனில் (rhs_semantic_type)
	    newrhs = build1 (EXCESS_PRECISION_கோவை, rhs_semantic_type, newrhs);
	}
      இல்லையெனில்
	npc = null_pointer_constant_p (newrhs);
      newrhs = convert_for_assignment (location, rhs_loc, lhstype, newrhs,
				       rhs_origtype, ic_assign, npc,
				       NULL_மரம், NULL_மரம், 0);
      எனில் (மரம்_CODE (newrhs) == ERROR_MARK)
	திரும்பு error_mark_முனை;
    }

  /* Emit ObjC write barrier, if necessary.  */
  எனில் (c_dialect_objc () && flag_objc_gc)
    {
      result = objc_generate_write_barrier (lhs, modifycode, newrhs);
      எனில் (result)
	{
	  protected_set_கோவை_location (result, location);
	  செல் return_result;
	}
    }

  /* Scan operands.  */

  எனில் (is_atomic_op)
    result = build_atomic_assign (location, lhs, modifycode, newrhs, பொய்);
  இல்லையெனில்
    {
      result = build2 (MODIFY_கோவை, lhstype, lhs, newrhs);
      மரம்_SIDE_EFFECTS (result) = 1;
      protected_set_கோவை_location (result, location);
    }

  /* If we got the LHS in a different type for storing in,
     convert the result back to the nominal type of LHS
     so that the value we return always has the same type
     as the LHS argument.  */

  எனில் (olhstype == மரம்_TYPE (result))
    செல் return_result;

  result = convert_for_assignment (location, rhs_loc, olhstype, result,
				   rhs_origtype, ic_assign, பொய், NULL_மரம்,
				   NULL_மரம், 0);
  protected_set_கோவை_location (result, location);

return_result:
  எனில் (rhseval)
    result = build2 (COMPOUND_கோவை, மரம்_TYPE (result), rhseval, result);
  திரும்பு result;
}

/* Return whether STRUCT_TYPE has an anonymous field with type TYPE.
   This is used to implement -fplan9-extensions.  */

நிலையான தருக்க
find_anonymous_field_with_type (மரம் struct_type, மரம் type)
{
  மரம் field;
  தருக்க found;

  gcc_assert (RECORD_OR_UNION_TYPE_P (struct_type));
  found = பொய்;
  க்கு (field = TYPE_FIELDS (struct_type);
       field != NULL_மரம்;
       field = மரம்_CHAIN (field))
    {
      மரம் fieldtype = remove_qualifiers (மரம்_TYPE (field));
      எனில் (DECL_NAME (field) == வெற்று
	  && comptypes (type, fieldtype))
	{
	  எனில் (found)
	    திரும்பு பொய்;
	  found = உண்மை;
	}
      இல்லையெனில் எனில் (DECL_NAME (field) == வெற்று
	       && RECORD_OR_UNION_TYPE_P (மரம்_TYPE (field))
	       && find_anonymous_field_with_type (மரம்_TYPE (field), type))
	{
	  எனில் (found)
	    திரும்பு பொய்;
	  found = உண்மை;
	}
    }
  திரும்பு found;
}

/* RHS is an expression whose type is pointer to struct.  If there is
   an anonymous field in RHS with type TYPE, then return a pointer to
   that field in RHS.  This is used with -fplan9-extensions.  This
   returns NULL if no conversion could be found.  */

நிலையான மரம்
convert_to_anonymous_field (location_t location, மரம் type, மரம் rhs)
{
  மரம் rhs_struct_type, lhs_main_type;
  மரம் field, found_field;
  தருக்க found_sub_field;
  மரம் ret;

  gcc_assert (POINTER_TYPE_P (மரம்_TYPE (rhs)));
  rhs_struct_type = மரம்_TYPE (மரம்_TYPE (rhs));
  gcc_assert (RECORD_OR_UNION_TYPE_P (rhs_struct_type));

  gcc_assert (POINTER_TYPE_P (type));
  lhs_main_type = remove_qualifiers (மரம்_TYPE (type));

  found_field = NULL_மரம்;
  found_sub_field = பொய்;
  க்கு (field = TYPE_FIELDS (rhs_struct_type);
       field != NULL_மரம்;
       field = மரம்_CHAIN (field))
    {
      எனில் (DECL_NAME (field) != NULL_மரம்
	  || !RECORD_OR_UNION_TYPE_P (மரம்_TYPE (field)))
	தொடர்;
      மரம் fieldtype = remove_qualifiers (மரம்_TYPE (field));
      எனில் (comptypes (lhs_main_type, fieldtype))
	{
	  எனில் (found_field != NULL_மரம்)
	    திரும்பு NULL_மரம்;
	  found_field = field;
	}
      இல்லையெனில் எனில் (find_anonymous_field_with_type (மரம்_TYPE (field),
					       lhs_main_type))
	{
	  எனில் (found_field != NULL_மரம்)
	    திரும்பு NULL_மரம்;
	  found_field = field;
	  found_sub_field = உண்மை;
	}
    }

  எனில் (found_field == NULL_மரம்)
    திரும்பு NULL_மரம்;

  ret = fold_build3_loc (location, COMPONENT_REF, மரம்_TYPE (found_field),
			 build_fold_indirect_ref (rhs), found_field,
			 NULL_மரம்);
  ret = build_fold_addr_கோவை_loc (location, ret);

  எனில் (found_sub_field)
    {
      ret = convert_to_anonymous_field (location, type, ret);
      gcc_assert (ret != NULL_மரம்);
    }

  திரும்பு ret;
}

/* Issue an error message for a bad initializer component.
   GMSGID identifies the message.
   The component name is taken from the spelling stack.  */

நிலையான வெறுமை ATTRIBUTE_GCC_DIAG (2,0)
error_init (location_t loc, மாறிலி எழுத்து *gmsgid, ...)
{
  எழுத்து *ofwhat;

  auto_diagnostic_group d;

  /* The gmsgid may be a format string with %< and %>. */
  va_list ap;
  va_start (ap, gmsgid);
  தருக்க warned = emit_diagnostic_valist (diagnostics::kind::error,
					loc, -1, gmsgid, &ap);
  va_end (ap);

  ofwhat = print_spelling ((எழுத்து *) alloca (spelling_length () + 1));
  எனில் (*ofwhat && warned)
    inform (loc, "(near initialization for %qs)", ofwhat);
}

/* Used to implement pedwarn_init and permerror_init.  */

நிலையான தருக்க ATTRIBUTE_GCC_DIAG (3,0)
pedwarn_permerror_init (location_t loc, முழு opt, மாறிலி எழுத்து *gmsgid,
			va_list *ap, எண்ணிக்கை diagnostics::kind kind)
{
  /* Use the location where a macro was expanded rather than where
     it was defined to make sure macros defined in system headers
     but used incorrectly elsewhere are diagnosed.  */
  location_t exploc = expansion_point_location_if_in_system_header (loc);
  auto_diagnostic_group d;
  தருக்க warned = emit_diagnostic_valist (kind, exploc, opt, gmsgid, ap);
  எனில் (warned)
    {
      எழுத்து *ofwhat = print_spelling ((எழுத்து *) alloca (spelling_length () + 1));
      எனில் (*ofwhat)
	inform (exploc, "(near initialization for %qs)", ofwhat);
    }
  திரும்பு warned;
}

/* Issue a pedantic warning for a bad initializer component.  OPT is
   the option OPT_* (from options.h) controlling this warning or 0 if
   it is unconditionally given.  GMSGID identifies the message.  The
   component name is taken from the spelling stack.  */

நிலையான தருக்க ATTRIBUTE_GCC_DIAG (3,0)
pedwarn_init (location_t loc, முழு opt, மாறிலி எழுத்து *gmsgid, ...)
{
  va_list ap;
  va_start (ap, gmsgid);
  தருக்க warned = pedwarn_permerror_init (loc, opt, gmsgid, &ap,
					diagnostics::kind::pedwarn);
  va_end (ap);
  திரும்பு warned;
}

/* Like pedwarn_init, but issue a permerror.  */

நிலையான தருக்க ATTRIBUTE_GCC_DIAG (3,0)
permerror_init (location_t loc, முழு opt, மாறிலி எழுத்து *gmsgid, ...)
{
  va_list ap;
  va_start (ap, gmsgid);
  தருக்க warned = pedwarn_permerror_init (loc, opt, gmsgid, &ap,
					diagnostics::kind::permerror);
  va_end (ap);
  திரும்பு warned;
}

/* Issue a warning for a bad initializer component.

   OPT is the OPT_W* value corresponding to the warning option that
   controls this warning.  GMSGID identifies the message.  The
   component name is taken from the spelling stack.  */

நிலையான வெறுமை
warning_init (location_t loc, முழு opt, மாறிலி எழுத்து *gmsgid)
{
  எழுத்து *ofwhat;
  தருக்க warned;

  auto_diagnostic_group d;

  /* Use the location where a macro was expanded rather than where
     it was defined to make sure macros defined in system headers
     but used incorrectly elsewhere are diagnosed.  */
  location_t exploc = expansion_point_location_if_in_system_header (loc);

  /* The gmsgid may be a format string with %< and %>. */
  warned = warning_at (exploc, opt, gmsgid);
  எனில் (warned)
    {
      ofwhat = print_spelling ((எழுத்து *) alloca (spelling_length () + 1));
      எனில் (*ofwhat)
	inform (exploc, "(near initialization for %qs)", ofwhat);
    }
}

/* If TYPE is an array type and EXPR is a parenthesized string
   constant, warn if pedantic that EXPR is being used to initialize an
   object of type TYPE.  */

வெறுமை
maybe_warn_string_init (location_t loc, மரம் type, கட்டமைப்பு c_கோவை கோவை)
{
  எனில் (pedantic
      && மரம்_CODE (type) == ARRAY_TYPE
      && மரம்_CODE (கோவை.மதிப்பு) == STRING_CST
      && கோவை.original_code != STRING_CST)
    pedwarn_init (loc, OPT_Wpedantic,
		  "array initialized from parenthesized string constant");
}

/* Attempt to locate the parameter with the given index within FNDECL,
   returning DECL_SOURCE_LOCATION (FNDECL) if it can't be found.  */

நிலையான location_t
get_fndecl_argument_location (மரம் fndecl, முழு argnum)
{
  முழு i;
  மரம் param;

  /* Locate param by index within DECL_ARGUMENTS (fndecl).  */
  க்கு (i = 0, param = DECL_ARGUMENTS (fndecl);
       i < argnum && param;
       i++, param = மரம்_CHAIN (param))
    ;

  /* If something went wrong (e.g. if we have a builtin and thus no arguments),
     return DECL_SOURCE_LOCATION (FNDECL).  */
  எனில் (param == வெற்று)
    திரும்பு DECL_SOURCE_LOCATION (fndecl);

  திரும்பு DECL_SOURCE_LOCATION (param);
}

/* Issue a note about a mismatching argument for parameter PARMNUM
   to FUNDECL, for types EXPECTED_TYPE and ACTUAL_TYPE.
   Attempt to issue the note at the pertinent parameter of the decl;
   failing that issue it at the location of FUNDECL; failing that
   issue it at PLOC.
   Use highlight_colors::actual for the ACTUAL_TYPE
   and highlight_colors::expected for EXPECTED_TYPE and the
   parameter of FUNDECL*/

நிலையான வெறுமை
inform_for_arg (மரம் fundecl, location_t ploc, முழு parmnum,
		மரம் expected_type, மரம் actual_type)
{
  location_t loc;
  எனில் (fundecl && !DECL_IS_UNDECLARED_BUILTIN (fundecl))
    loc = get_fndecl_argument_location (fundecl, parmnum - 1);
  இல்லையெனில்
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

நிலையான வெறுமை
maybe_warn_builtin_no_proto_arg (location_t loc, மரம் fundecl, முழு parmnum,
				 மரம் parmtype, மரம் argtype)
{
  மரம்_code parmcode = மரம்_CODE (parmtype);
  மரம்_code argcode = மரம்_CODE (argtype);
  மரம் promoted = c_type_promotes_to (argtype);

  /* Avoid warning for enum arguments that promote to an integer type
     of the same size/mode.  */
  எனில் (parmcode == INTEGER_TYPE
      && argcode == ENUMERAL_TYPE
      && TYPE_MODE (parmtype) == TYPE_MODE (argtype))
    திரும்பு;

  எனில் ((parmcode == argcode
       || (parmcode == INTEGER_TYPE
	   && argcode == ENUMERAL_TYPE))
      && TYPE_MAIN_VARIANT (parmtype) == TYPE_MAIN_VARIANT (promoted))
    திரும்பு;

  /* This diagnoses even signed/unsigned mismatches.  Those might be
     safe in many cases but GCC may emit suboptimal code for them so
     warning on those cases drives efficiency improvements.  */
  எனில் (warning_at (loc, OPT_Wbuiltin_declaration_mismatch,
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

வகுப்பு pp_element_quoted_decl : பொது pp_element
{
பொது:
  pp_element_quoted_decl (மரம் decl, மாறிலி எழுத்து *highlight_color)
  : m_decl (decl),
    m_highlight_color (highlight_color)
  {
  }

  வெறுமை add_to_phase_2 (pp_markup::context &ctxt) override
  {
    ctxt.begin_quote ();
    ctxt.begin_highlight_color (m_highlight_color);

    print_decl (ctxt);

    ctxt.end_highlight_color ();
    ctxt.end_quote ();
  }

  வெறுமை print_decl (pp_markup::context &ctxt)
  {
    pretty_printer *மாறிலி pp = &ctxt.m_pp;
    pp->set_padding (pp_none);
    எனில் (DECL_NAME (m_decl))
      pp_identifier (pp, lang_hooks.decl_printable_name (m_decl, 2));
    இல்லையெனில்
      pp_string (pp, _("({anonymous})"));
  }

தனிப்பட்ட:
  மரம் m_decl;
  மாறிலி எழுத்து *m_highlight_color;
};

/* If TYPE is from a typedef, issue a note showing the location
   to the user.
   Use HIGHLIGHT_COLOR as the highlight color.  */

நிலையான வெறுமை
maybe_inform_typedef_location (மரம் type, மாறிலி எழுத்து *highlight_color)
{
  எனில் (!typedef_variant_p (type))
    திரும்பு;

  மரம் typedef_decl = TYPE_NAME (type);
  gcc_assert (மரம்_CODE (typedef_decl) == TYPE_DECL);
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

நிலையான மரம்
convert_for_assignment (location_t location, location_t கோவை_loc, மரம் type,
			மரம் rhs, மரம் origtype, எண்ணிக்கை impl_conv errtype,
			தருக்க null_pointer_constant, மரம் fundecl,
			மரம் function, முழு parmnum, முழு warnopt /* = 0 */)
{
  எண்ணிக்கை மரம்_code codel = மரம்_CODE (type);
  மரம் orig_rhs = rhs;
  மரம் rhstype;
  எண்ணிக்கை மரம்_code coder;
  மரம் rname = NULL_மரம்;
  தருக்க objc_ok = பொய்;

  /* Use the expansion point location to handle cases such as user's
     function returning a wrong-type macro defined in a system header.  */
  location = expansion_point_location_if_in_system_header (location);

  எனில் (errtype == ic_argpass)
    {
      மரம் selector;
      /* Change pointer to function to the function itself for
	 diagnostics.  */
      எனில் (மரம்_CODE (function) == ADDR_கோவை
	  && மரம்_CODE (மரம்_OPERAND (function, 0)) == FUNCTION_DECL)
	function = மரம்_OPERAND (function, 0);

      /* Handle an ObjC selector specially for diagnostics.  */
      selector = objc_message_selector ();
      rname = function;
      எனில் (selector && parmnum > 2)
	{
	  rname = selector;
	  parmnum -= 2;
	}
    }

  /* This macro is used to emit diagnostics to ensure that all format
     strings are complete sentences, visible to gettext and checked at
     compile time.  */
#define PEDWARN_FOR_ASSIGNMENT(LOCATION, PLOC, OPT, AR, AS, IN, RE)	 \
  செய் {                                                                   \
    தேர்வு (errtype)                                                     \
      {                                                                  \
      நிலை ic_argpass:                                                   \
	{								\
	  auto_diagnostic_group d;						\
	  எனில் (pedwarn (PLOC, OPT, AR, parmnum, rname))		\
	    inform_for_arg (fundecl, (PLOC), parmnum, type, rhstype); \
	}								\
        நிறுத்து;                                                           \
      நிலை ic_assign:                                                    \
        pedwarn (LOCATION, OPT, AS);                                     \
        நிறுத்து;                                                           \
      நிலை ic_init:                                                      \
      நிலை ic_init_const:                                                \
        pedwarn_init (LOCATION, OPT, IN);                                \
        நிறுத்து;                                                           \
      நிலை ic_return:                                                    \
        pedwarn (LOCATION, OPT, RE);					 \
        நிறுத்து;                                                           \
      இயல்பு:                                                           \
        gcc_unreachable ();                                              \
      }                                                                  \
  } போது (0)

  /* This macro is used to emit diagnostics to ensure that all format
     strings are complete sentences, visible to gettext and checked at
     compile time.  It can be called with 'pedwarn' or 'warning_at'.  */
#define WARNING_FOR_QUALIFIERS(PEDWARN, LOCATION, PLOC, OPT, AR, AS, IN, RE, QUALS) \
  செய் {                                                                   \
    தேர்வு (errtype)                                                     \
      {                                                                  \
      நிலை ic_argpass:                                                   \
	{								 \
	  auto_diagnostic_group d;					 \
	  எனில் (PEDWARN) {						 \
	    எனில் (pedwarn (PLOC, OPT, AR, parmnum, rname, QUALS))          \
	      inform_for_arg (fundecl, (PLOC), parmnum, type, rhstype);  \
	  } இல்லையெனில் {							 \
	    எனில் (warning_at (PLOC, OPT, AR, parmnum, rname, QUALS))	 \
	      inform_for_arg (fundecl, (PLOC), parmnum, type, rhstype);  \
	  }								 \
	}								 \
        நிறுத்து;                                                           \
      நிலை ic_assign:                                                    \
	எனில் (PEDWARN)							 \
	  pedwarn (LOCATION, OPT, AS, QUALS);                            \
	இல்லையெனில்								 \
	  warning_at (LOCATION, OPT, AS, QUALS);                         \
        நிறுத்து;                                                           \
      நிலை ic_init:                                                      \
      நிலை ic_init_const:                                                \
	எனில் (PEDWARN)							 \
	  pedwarn (LOCATION, OPT, IN, QUALS);                            \
	இல்லையெனில்								 \
	  warning_at (LOCATION, OPT, IN, QUALS);                         \
        நிறுத்து;                                                           \
      நிலை ic_return:                                                    \
	எனில் (PEDWARN)							 \
	  pedwarn (LOCATION, OPT, RE, QUALS);                            \
	இல்லையெனில்								 \
	  warning_at (LOCATION, OPT, RE, QUALS);                         \
        நிறுத்து;                                                           \
      இயல்பு:                                                           \
        gcc_unreachable ();                                              \
      }                                                                  \
  } போது (0)

  /* This macro is used to emit diagnostics to ensure that all format
     strings are complete sentences, visible to gettext and checked at
     compile time.  It is the same as PEDWARN_FOR_ASSIGNMENT but with an
     extra parameter to enumerate qualifiers.  */
#define PEDWARN_FOR_QUALIFIERS(LOCATION, PLOC, OPT, AR, AS, IN, RE, QUALS) \
   WARNING_FOR_QUALIFIERS (உண்மை, LOCATION, PLOC, OPT, AR, AS, IN, RE, QUALS)


  எனில் (மரம்_CODE (rhs) == EXCESS_PRECISION_கோவை)
    rhs = மரம்_OPERAND (rhs, 0);

  rhstype = மரம்_TYPE (rhs);
  coder = மரம்_CODE (rhstype);

  எனில் (coder == ERROR_MARK)
    திரும்பு error_mark_முனை;

  எனில் (c_dialect_objc ())
    {
      முழு parmno;

      தேர்வு (errtype)
	{
	நிலை ic_return:
	  parmno = 0;
	  நிறுத்து;

	நிலை ic_assign:
	  parmno = -1;
	  நிறுத்து;

	நிலை ic_init:
	நிலை ic_init_const:
	  parmno = -2;
	  நிறுத்து;

	இயல்பு:
	  parmno = parmnum;
	  நிறுத்து;
	}

      objc_ok = objc_compare_types (type, rhstype, parmno, rname);
    }

  எனில் (warn_cxx_compat)
    {
      மரம் checktype = origtype != NULL_மரம் ? origtype : rhstype;
      எனில் (checktype != error_mark_முனை
	  && மரம்_CODE (type) == ENUMERAL_TYPE
	  && TYPE_MAIN_VARIANT (checktype) != TYPE_MAIN_VARIANT (type))
	தேர்வு (errtype)
	  {
	  நிலை ic_argpass:
	    எனில் (pedwarn (கோவை_loc, OPT_Wc___compat, "enum conversion when "
			 "passing argument %d of %qE is invalid in C++",
			 parmnum, rname))
	      inform ((fundecl && !DECL_IS_UNDECLARED_BUILTIN (fundecl))
		      ? DECL_SOURCE_LOCATION (fundecl) : கோவை_loc,
		      "expected %qT but argument is of type %qT",
		      type, rhstype);
	    நிறுத்து;
	  நிலை ic_assign:
	    pedwarn (location, OPT_Wc___compat, "enum conversion from %qT to "
		     "%qT in assignment is invalid in C++", rhstype, type);
	    நிறுத்து;
	  நிலை ic_init:
	  நிலை ic_init_const:
	    pedwarn_init (location, OPT_Wc___compat, "enum conversion from "
			  "%qT to %qT in initialization is invalid in C++",
			  rhstype, type);
	    நிறுத்து;
	  நிலை ic_return:
	    pedwarn (location, OPT_Wc___compat, "enum conversion from %qT to "
		     "%qT in return is invalid in C++", rhstype, type);
	    நிறுத்து;
	  இயல்பு:
	    gcc_unreachable ();
	  }
    }

  எனில் (warn_enum_conversion)
    {
      மரம் checktype = origtype != NULL_மரம் ? origtype : rhstype;
      எனில் (checktype != error_mark_முனை
	  && மரம்_CODE (checktype) == ENUMERAL_TYPE
	  && மரம்_CODE (type) == ENUMERAL_TYPE
	  && !comptypes (TYPE_MAIN_VARIANT (checktype), TYPE_MAIN_VARIANT (type)))
       {
	  gcc_rich_location loc (location);
	  warning_at (&loc, OPT_Wenum_conversion,
		      "implicit conversion from %qT to %qT",
		      checktype, type);
       }
    }

  எனில் (TYPE_MAIN_VARIANT (type) == TYPE_MAIN_VARIANT (rhstype))
    {
      warn_for_address_of_packed_member (type, orig_rhs);
      எனில் (type != rhstype)
	/* Convert RHS to TYPE in order to not lose TYPE in diagnostics.  */
	rhs = convert (type, rhs);
      திரும்பு rhs;
    }

  எனில் (coder == VOID_TYPE)
    {
      /* Except for passing an argument to an unprototyped function,
	 this is a constraint violation.  When passing an argument to
	 an unprototyped function, it is compile-time undefined;
	 making it a constraint in that case was rejected in
	 DR#252.  */
      மாறிலி எழுத்து செய்தி[] = "void value not ignored as it ought to be";
      எனில் (warnopt)
	warning_at (location, warnopt, செய்தி);
      இல்லையெனில்
	error_at (location, செய்தி);
      திரும்பு error_mark_முனை;
    }
  rhs = require_complete_type (location, rhs);
  எனில் (rhs == error_mark_முனை)
    திரும்பு error_mark_முனை;

  எனில் (coder == POINTER_TYPE && reject_gcc_builtin (rhs))
    திரும்பு error_mark_முனை;

  /* A non-reference type can convert to a reference.  This handles
     va_start, va_copy and possibly port built-ins.  */
  எனில் (codel == REFERENCE_TYPE && coder != REFERENCE_TYPE)
    {
      எனில் (!lvalue_p (rhs))
	{
	  மாறிலி எழுத்து செய்தி[] = "cannot pass rvalue to reference parameter";
	  எனில் (warnopt)
	    warning_at (location, warnopt, செய்தி);
	  இல்லையெனில்
	    error_at (location, செய்தி);
	  திரும்பு error_mark_முனை;
	}
      எனில் (!c_mark_addressable (rhs))
	திரும்பு error_mark_முனை;
      rhs = build1 (ADDR_கோவை, c_build_pointer_type (மரம்_TYPE (rhs)), rhs);
      SET_கோவை_LOCATION (rhs, location);

      rhs = convert_for_assignment (location, கோவை_loc,
				    c_build_pointer_type (மரம்_TYPE (type)),
				    rhs, origtype, errtype,
				    null_pointer_constant, fundecl, function,
				    parmnum, warnopt);
      எனில் (rhs == error_mark_முனை)
	திரும்பு error_mark_முனை;

      rhs = build1 (NOP_கோவை, type, rhs);
      SET_கோவை_LOCATION (rhs, location);
      திரும்பு rhs;
    }
  /* Some types can interconvert without explicit casts.  */
  இல்லையெனில் எனில் (codel == VECTOR_TYPE && coder == VECTOR_TYPE
	   && vector_types_convertible_p (type, மரம்_TYPE (rhs), உண்மை))
    திரும்பு convert (type, rhs);
  /* Arithmetic types all interconvert, and enum is treated like int.  */
  இல்லையெனில் எனில் ((codel == INTEGER_TYPE || codel == REAL_TYPE
	    || codel == FIXED_POINT_TYPE
	    || codel == ENUMERAL_TYPE || codel == COMPLEX_TYPE
	    || codel == BOOLEAN_TYPE || codel == BITINT_TYPE)
	   && (coder == INTEGER_TYPE || coder == REAL_TYPE
	       || coder == FIXED_POINT_TYPE
	       || coder == ENUMERAL_TYPE || coder == COMPLEX_TYPE
	       || coder == BOOLEAN_TYPE || coder == BITINT_TYPE))
    {
      எனில் (warnopt && errtype == ic_argpass)
	maybe_warn_builtin_no_proto_arg (கோவை_loc, fundecl, parmnum, type,
					 rhstype);

      தருக்க save = in_late_இருமம்_op;
      எனில் (C_BOOLEAN_TYPE_P (type) || codel == COMPLEX_TYPE
	  || (coder == REAL_TYPE
	      && (codel == INTEGER_TYPE || codel == ENUMERAL_TYPE)
	      && sanitize_flags_p (SANITIZE_FLOAT_CAST)))
	in_late_இருமம்_op = உண்மை;
      மரம் ret = convert_and_check (கோவை_loc != UNKNOWN_LOCATION
				    ? கோவை_loc : location, type, orig_rhs,
				    errtype == ic_init_const);
      in_late_இருமம்_op = save;
      திரும்பு ret;
    }

  /* Aggregates in different TUs might need conversion.  */
  எனில் ((codel == RECORD_TYPE || codel == UNION_TYPE)
      && codel == coder
      && comptypes (TYPE_MAIN_VARIANT (type), TYPE_MAIN_VARIANT (rhstype)))
    திரும்பு convert_and_check (கோவை_loc != UNKNOWN_LOCATION
			      ? கோவை_loc : location, type, rhs);

  /* Conversion to a transparent union or record from its member types.
     This applies only to function arguments.  */
  எனில் (((codel == UNION_TYPE || codel == RECORD_TYPE)
      && TYPE_TRANSPARENT_AGGR (type))
      && errtype == ic_argpass)
    {
      மரம் memb, marginal_memb = NULL_மரம்;

      க்கு (memb = TYPE_FIELDS (type); memb ; memb = DECL_CHAIN (memb))
	{
	  மரம் memb_type = மரம்_TYPE (memb);

	  எனில் (comptypes (TYPE_MAIN_VARIANT (memb_type),
			 TYPE_MAIN_VARIANT (rhstype)))
	    நிறுத்து;

	  எனில் (மரம்_CODE (memb_type) != POINTER_TYPE)
	    தொடர்;

	  எனில் (coder == POINTER_TYPE)
	    {
	      மரம் ttl = மரம்_TYPE (memb_type);
	      மரம் ttr = மரம்_TYPE (rhstype);

	      /* Any non-function converts to a [const][volatile] void *
		 and vice versa; otherwise, targets must be the same.
		 Meanwhile, the lhs target must have all the qualifiers of
		 the rhs.  */
	      எனில் ((VOID_TYPE_P (ttl) && !TYPE_ATOMIC (ttl))
		  || (VOID_TYPE_P (ttr) && !TYPE_ATOMIC (ttr))
		  || comp_target_types (location, memb_type, rhstype))
		{
		  முழு lquals = TYPE_QUALS (ttl) & ~TYPE_QUAL_ATOMIC;
		  முழு rquals = TYPE_QUALS (ttr) & ~TYPE_QUAL_ATOMIC;
		  /* If this type won't generate any warnings, use it.  */
		  எனில் (lquals == rquals
		      || ((மரம்_CODE (ttr) == FUNCTION_TYPE
			   && மரம்_CODE (ttl) == FUNCTION_TYPE)
			  ? ((lquals | rquals) == rquals)
			  : ((lquals | rquals) == lquals)))
		    நிறுத்து;

		  /* Keep looking for a better type, but remember this one.  */
		  எனில் (!marginal_memb)
		    marginal_memb = memb;
		}
	    }

	  /* Can convert integer zero to any pointer type.  */
	  எனில் (null_pointer_constant)
	    {
	      rhs = null_pointer_முனை;
	      நிறுத்து;
	    }
	}

      எனில் (memb || marginal_memb)
	{
	  எனில் (!memb)
	    {
	      /* We have only a marginally acceptable member type;
		 it needs a warning.  */
	      மரம் ttl = மரம்_TYPE (மரம்_TYPE (marginal_memb));
	      மரம் ttr = மரம்_TYPE (rhstype);

	      /* Const and volatile mean something different for function
		 types, so the usual warnings are not appropriate.  */
	      எனில் (மரம்_CODE (ttr) == FUNCTION_TYPE
		  && மரம்_CODE (ttl) == FUNCTION_TYPE)
		{
		  /* Because const and volatile on functions are
		     restrictions that say the function will not do
		     certain things, it is okay to use a const or volatile
		     function where an ordinary one is wanted, but not
		     vice-versa.  */
		  எனில் (TYPE_QUALS_NO_ADDR_SPACE (ttl)
		      & ~TYPE_QUALS_NO_ADDR_SPACE (ttr))
		    PEDWARN_FOR_QUALIFIERS (location, கோவை_loc,
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
	      இல்லையெனில் எனில் (TYPE_QUALS_NO_ADDR_SPACE (ttr)
		       & ~TYPE_QUALS_NO_ADDR_SPACE (ttl))
		PEDWARN_FOR_QUALIFIERS (location, கோவை_loc,
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

	  எனில் (!fundecl || !DECL_IN_SYSTEM_HEADER (fundecl))
	    pedwarn (location, OPT_Wpedantic,
		     "ISO C prohibits argument conversion to union type");

	  rhs = fold_convert_loc (location, மரம்_TYPE (memb), rhs);
	  திரும்பு build_constructor_single (type, memb, rhs);
	}
    }

  /* Conversions among pointers */
  இல்லையெனில் எனில் ((codel == POINTER_TYPE || codel == REFERENCE_TYPE)
	   && (coder == codel))
    {
      /* If RHS refers to a built-in declared without a prototype
	 BLTIN is the declaration of the built-in with a prototype
	 and RHSTYPE is set to the actual type of the built-in.  */
      மரம் bltin;
      rhstype = type_or_builtin_type (rhs, &bltin);

      மரம் ttl = மரம்_TYPE (type);
      மரம் ttr = மரம்_TYPE (rhstype);
      தருக்க is_opaque_pointer;
      தருக்க target_cmp = பொய்;   /* Cache comp_target_types () result.  */
      addr_space_t asl;
      addr_space_t asr;

      மரம் mvl = remove_qualifiers (ttl);
      மரம் mvr = remove_qualifiers (ttr);

      /* Opaque pointers are treated like void pointers.  */
      is_opaque_pointer = vector_targets_convertible_p (ttl, ttr);

      /* The Plan 9 compiler permits a pointer to a struct to be
	 automatically converted into a pointer to an anonymous field
	 within the struct.  */
      எனில் (flag_plan9_extensions
	  && RECORD_OR_UNION_TYPE_P (mvl)
	  && RECORD_OR_UNION_TYPE_P (mvr)
	  && mvl != mvr)
	{
	  மரம் new_rhs = convert_to_anonymous_field (location, type, rhs);
	  எனில் (new_rhs != NULL_மரம்)
	    {
	      rhs = new_rhs;
	      rhstype = மரம்_TYPE (rhs);
	      coder = மரம்_CODE (rhstype);
	      ttr = மரம்_TYPE (rhstype);
	      mvr = TYPE_MAIN_VARIANT (ttr);
	    }
	}

      /* C++ does not allow the implicit conversion void* -> T*.  However,
	 for the purpose of reducing the number of false positives, we
	 tolerate the special case of

		int *p = NULL;

	 where NULL is typically defined in C to be '(void *) 0'.  */
      எனில் (VOID_TYPE_P (ttr) && rhs != null_pointer_முனை && !VOID_TYPE_P (ttl))
	warning_at (errtype == ic_argpass ? கோவை_loc : location,
		    OPT_Wc___compat,
		    "request for implicit conversion "
		    "from %qT to %qT not permitted in C++", rhstype, type);

      /* Warn of new allocations that are not big enough for the target
	 type.  */
      எனில் (warn_alloc_size && மரம்_CODE (rhs) == CALL_கோவை)
	எனில் (மரம் fndecl = get_callee_fndecl (rhs))
	  எனில் (DECL_IS_MALLOC (fndecl))
	    {
	      மரம் attrs = TYPE_ATTRIBUTES (மரம்_TYPE (fndecl));
	      மரம் alloc_size = lookup_attribute ("alloc_size", attrs);
	      எனில் (alloc_size)
		warn_for_alloc_size (location, ttl, rhs, alloc_size);
	    }

      /* See if the pointers point to incompatible address spaces.  */
      asl = TYPE_ADDR_SPACE (ttl);
      asr = TYPE_ADDR_SPACE (ttr);
      எனில் (!null_pointer_constant_p (rhs)
	  && asr != asl && !targetm.addr_space.subset_p (asr, asl))
	{
	  auto_diagnostic_group d;
	  தருக்க diagnosed = உண்மை;
	  தேர்வு (errtype)
	    {
	    நிலை ic_argpass:
	      {
		மாறிலி எழுத்து செய்தி[] = G_("passing argument %d of %qE from "
				      "pointer to non-enclosed address space");
		எனில் (warnopt)
		  diagnosed
		    = warning_at (கோவை_loc, warnopt, செய்தி, parmnum, rname);
		இல்லையெனில்
		  error_at (கோவை_loc, செய்தி, parmnum, rname);
	      நிறுத்து;
	      }
	    நிலை ic_assign:
	      {
		மாறிலி எழுத்து செய்தி[] = G_("assignment from pointer to "
				      "non-enclosed address space");
		எனில் (warnopt)
		  diagnosed = warning_at (location, warnopt, செய்தி);
		இல்லையெனில்
		  error_at (location, செய்தி);
		நிறுத்து;
	      }
	    நிலை ic_init:
	    நிலை ic_init_const:
	      {
		மாறிலி எழுத்து செய்தி[] = G_("initialization from pointer to "
				      "non-enclosed address space");
		எனில் (warnopt)
		  diagnosed = warning_at (location, warnopt, செய்தி);
		இல்லையெனில்
		  error_at (location, செய்தி);
		நிறுத்து;
	      }
	    நிலை ic_return:
	      {
		மாறிலி எழுத்து செய்தி[] = G_("return from pointer to "
				      "non-enclosed address space");
		எனில் (warnopt)
		  diagnosed = warning_at (location, warnopt, செய்தி);
		இல்லையெனில்
		  error_at (location, செய்தி);
		நிறுத்து;
	      }
	    இயல்பு:
	      gcc_unreachable ();
	    }
	  எனில் (diagnosed)
	    {
	      எனில் (errtype == ic_argpass)
		inform_for_arg (fundecl, கோவை_loc, parmnum, type, rhstype);
	      இல்லையெனில்
		inform (location, "expected %qT but pointer is of type %qT",
			type, rhstype);
	    }
	  திரும்பு error_mark_முனை;
	}

      /* Check if the right-hand side has a format attribute but the
	 left-hand side doesn't.  */
      எனில் (warn_suggest_attribute_format
	  && check_missing_format_attribute (type, rhstype))
	{
	  தேர்வு (errtype)
	  {
	  நிலை ic_argpass:
	    warning_at (கோவை_loc, OPT_Wsuggest_attribute_format,
			"argument %d of %qE might be "
			"a candidate for a format attribute",
			parmnum, rname);
	    நிறுத்து;
	  நிலை ic_assign:
	    warning_at (location, OPT_Wsuggest_attribute_format,
			"assignment left-hand side might be "
			"a candidate for a format attribute");
	    நிறுத்து;
	  நிலை ic_init:
	  நிலை ic_init_const:
	    warning_at (location, OPT_Wsuggest_attribute_format,
			"initialization left-hand side might be "
			"a candidate for a format attribute");
	    நிறுத்து;
	  நிலை ic_return:
	    warning_at (location, OPT_Wsuggest_attribute_format,
			"return type might be "
			"a candidate for a format attribute");
	    நிறுத்து;
	  இயல்பு:
	    gcc_unreachable ();
	  }
	}

      /* See if the pointers point to incompatible scalar storage orders.  */
      எனில் (warn_scalar_storage_order
	  && !null_pointer_constant_p (rhs)
	  && (AGGREGATE_TYPE_P (ttl) && TYPE_REVERSE_STORAGE_ORDER (ttl))
	     != (AGGREGATE_TYPE_P (ttr) && TYPE_REVERSE_STORAGE_ORDER (ttr)))
	{
	  மரம் t;

	  தேர்வு (errtype)
	  {
	  நிலை ic_argpass:
	    /* Do not warn for built-in functions, for example memcpy, since we
	       control how they behave and they can be useful in this area.  */
	    எனில் (மரம்_CODE (rname) != FUNCTION_DECL
		|| !fndecl_built_in_p (rname))
	      warning_at (location, OPT_Wscalar_storage_order,
			  "passing argument %d of %qE from incompatible "
			  "scalar storage order", parmnum, rname);
	    நிறுத்து;
	  நிலை ic_assign:
	    /* Do not warn if the RHS is a call to a function that returns a
	       pointer that is not an alias.  */
	    எனில் (மரம்_CODE (rhs) != CALL_கோவை
		|| (t = get_callee_fndecl (rhs)) == NULL_மரம்
		|| !DECL_IS_MALLOC (t))
	      warning_at (location, OPT_Wscalar_storage_order,
			  "assignment to %qT from pointer type %qT with "
			  "incompatible scalar storage order", type, rhstype);
	    நிறுத்து;
	  நிலை ic_init:
	  நிலை ic_init_const:
	    /* Likewise.  */
	    எனில் (மரம்_CODE (rhs) != CALL_கோவை
		|| (t = get_callee_fndecl (rhs)) == NULL_மரம்
		|| !DECL_IS_MALLOC (t))
	      warning_at (location, OPT_Wscalar_storage_order,
			  "initialization of %qT from pointer type %qT with "
			  "incompatible scalar storage order", type, rhstype);
	    நிறுத்து;
	  நிலை ic_return:
	    warning_at (location, OPT_Wscalar_storage_order,
			"returning %qT from pointer type with incompatible "
			"scalar storage order %qT", rhstype, type);
	    நிறுத்து;
	  இயல்பு:
	    gcc_unreachable ();
	  }
	}

      /* Any non-function converts to a [const][volatile] void *
	 and vice versa; otherwise, targets must be the same.
	 Meanwhile, the lhs target must have all the qualifiers of the rhs.  */
      எனில் ((VOID_TYPE_P (ttl) && !TYPE_ATOMIC (ttl))
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
	  எனில் (மரம்_CODE (ttr) == ARRAY_TYPE)
	    {
	      ttr = strip_array_types (ttr);
	      ttl = strip_array_types (ttl);

	      எனில் (TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttr)
		  & ~TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttl))
		WARNING_FOR_QUALIFIERS (flag_isoc23,
					location, கோவை_loc,
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
          இல்லையெனில் எனில் (pedantic
	      && ((VOID_TYPE_P (ttl) && மரம்_CODE (ttr) == FUNCTION_TYPE)
		  ||
		  (VOID_TYPE_P (ttr)
		   && !null_pointer_constant
		   && மரம்_CODE (ttl) == FUNCTION_TYPE)))
	    PEDWARN_FOR_ASSIGNMENT (location, கோவை_loc, OPT_Wpedantic,
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
	  இல்லையெனில் எனில் (மரம்_CODE (ttr) != FUNCTION_TYPE
		   && மரம்_CODE (ttl) != FUNCTION_TYPE)
	    {
	       /* Assignments between atomic and non-atomic objects are OK.  */
	       தருக்க warn_quals_ped = TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttr)
				     & ~TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttl);
	       தருக்க warn_quals = TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttr)
				 & ~TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (strip_array_types (ttl));

	      /* Don't warn about loss of qualifier for conversions from
		 qualified void* to pointers to arrays with corresponding
		 qualifier on the element type (except for pedantic before C23). */
	      எனில் (warn_quals || (warn_quals_ped && pedantic && !flag_isoc23))
		PEDWARN_FOR_QUALIFIERS (location, கோவை_loc,
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
	      இல்லையெனில் எனில் (warn_quals_ped)
		pedwarn_c11 (location, OPT_Wc11_c23_compat,
			     "array with qualifier on the element is not qualified before C23");

	      /* If this is not a case of ignoring a mismatch in signedness,
		 no warning.  */
	      இல்லையெனில் எனில் (VOID_TYPE_P (ttl) || VOID_TYPE_P (ttr)
		       || target_cmp)
		;
	      /* If there is a mismatch, do warn.  */
	      இல்லையெனில் எனில் (warn_pointer_sign)
		தேர்வு (errtype)
		  {
		  நிலை ic_argpass:
		    {
		      auto_diagnostic_group d;
		      range_label_for_type_mismatch rhs_label (rhstype, type);
		      gcc_rich_location richloc (கோவை_loc, &rhs_label,
						 highlight_colors::actual);
		      எனில் (pedwarn (&richloc, OPT_Wpointer_sign,
				   "pointer targets in passing argument %d of "
				   "%qE differ in signedness", parmnum, rname))
			inform_for_arg (fundecl, கோவை_loc, parmnum, type,
					rhstype);
		    }
		    நிறுத்து;
		  நிலை ic_assign:
		    pedwarn (location, OPT_Wpointer_sign,
			     "pointer targets in assignment from %qT to %qT "
			     "differ in signedness", rhstype, type);
		    நிறுத்து;
		  நிலை ic_init:
		  நிலை ic_init_const:
		    pedwarn_init (location, OPT_Wpointer_sign,
				  "pointer targets in initialization of %qT "
				  "from %qT differ in signedness", type,
				  rhstype);
		    நிறுத்து;
		  நிலை ic_return:
		    pedwarn (location, OPT_Wpointer_sign, "pointer targets in "
			     "returning %qT from a function with return type "
			     "%qT differ in signedness", rhstype, type);
		    நிறுத்து;
		  இயல்பு:
		    gcc_unreachable ();
		  }
	    }
	  இல்லையெனில் எனில் (மரம்_CODE (ttl) == FUNCTION_TYPE
		   && மரம்_CODE (ttr) == FUNCTION_TYPE)
	    {
	      /* Because const and volatile on functions are restrictions
		 that say the function will not do certain things,
		 it is okay to use a const or volatile function
		 where an ordinary one is wanted, but not vice-versa.  */
	      எனில் (TYPE_QUALS_NO_ADDR_SPACE (ttl)
		  & ~TYPE_QUALS_NO_ADDR_SPACE (ttr))
		PEDWARN_FOR_QUALIFIERS (location, கோவை_loc,
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
      இல்லையெனில் எனில் (!objc_ok)
	{
	  auto_diagnostic_group d;
	  தருக்க warned = பொய்;
	  pp_markup::element_expected_type e_type (type);
	  pp_markup::element_actual_type e_rhstype (rhstype);
	  தேர்வு (errtype)
	    {
	    நிலை ic_argpass:
	      {
		range_label_for_type_mismatch rhs_label (rhstype, type);
		gcc_rich_location richloc (கோவை_loc, &rhs_label,
					   highlight_colors::actual);
		warned
		  = permerror_opt (&richloc, OPT_Wincompatible_pointer_types,
				   "passing argument %d of %qE from "
				   "incompatible pointer type",
				   parmnum, rname);
		எனில் (warned)
		  inform_for_arg (fundecl, கோவை_loc, parmnum, type, rhstype);
	      }
	      நிறுத்து;
	    நிலை ic_assign:
	      எனில் (bltin)
		warned
		  = permerror_opt (location, OPT_Wincompatible_pointer_types,
				   "assignment to %e from pointer to "
				   "%qD with incompatible type %e",
				   &e_type, bltin, &e_rhstype);
	      இல்லையெனில்
		warned
		  = permerror_opt (location, OPT_Wincompatible_pointer_types,
				   "assignment to %e from incompatible "
				   "pointer type %e",
				   &e_type, &e_rhstype);
	      நிறுத்து;
	    நிலை ic_init:
	    நிலை ic_init_const:
	      எனில் (bltin)
		warned
		  = permerror_init (location, OPT_Wincompatible_pointer_types,
				    "initialization of %e from pointer to "
				    "%qD with incompatible type %e",
				    &e_type, bltin, &e_rhstype);
	      இல்லையெனில்
		warned
		  = permerror_init (location, OPT_Wincompatible_pointer_types,
				    "initialization of %e from incompatible "
				    "pointer type %e",
				    &e_type, &e_rhstype);
	      நிறுத்து;
	    நிலை ic_return:
	      எனில் (bltin)
		warned
		  = permerror_opt (location, OPT_Wincompatible_pointer_types,
				   "returning pointer to %qD of type %e from "
				   "a function with incompatible type %e",
				   bltin, &e_rhstype, &e_type);
	      இல்லையெனில்
		warned
		  = permerror_opt (location, OPT_Wincompatible_pointer_types,
				   "returning %e from a function with "
				   "incompatible return type %e",
				   &e_rhstype, &e_type);
	      நிறுத்து;
	    இயல்பு:
	      gcc_unreachable ();
	    }
	  எனில் (warned)
	    {
	      /* If the mismatching function type is a pointer to a function,
		 try to show the decl of the function.  */
	      எனில் (மரம்_CODE (rhs) == ADDR_கோவை
		  && மரம்_CODE (மரம்_OPERAND (rhs, 0)) == FUNCTION_DECL)
		{
		  மரம் rhs_fndecl = மரம்_OPERAND (rhs, 0);
		  எனில் (!DECL_IS_UNDECLARED_BUILTIN (rhs_fndecl))
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

      திரும்பு convert (type, rhs);
    }
  இல்லையெனில் எனில் (codel == POINTER_TYPE && coder == ARRAY_TYPE)
    {
      /* ??? This should not be an error when inlining calls to
	 unprototyped functions.  */
      மாறிலி எழுத்து செய்தி[] = "invalid use of non-lvalue array";
      எனில் (warnopt)
	warning_at (location, warnopt, செய்தி);
      இல்லையெனில்
	error_at (location, செய்தி);
      திரும்பு error_mark_முனை;
    }
  இல்லையெனில் எனில் (codel == POINTER_TYPE
	   && (coder == INTEGER_TYPE
	       || coder == ENUMERAL_TYPE
	       || coder == BOOLEAN_TYPE
	       || coder == NULLPTR_TYPE
	       || coder == BITINT_TYPE))
    {
      எனில் (null_pointer_constant && c_inhibit_evaluation_warnings == 0
	  && coder != NULLPTR_TYPE)
	warning_at (location, OPT_Wzero_as_null_pointer_constant,
		    "zero as null pointer constant");
      /* A NULLPTR type is just a nullptr always.  */
      எனில் (coder == NULLPTR_TYPE)
	திரும்பு omit_one_operand_loc (கோவை_loc, type, nullptr_முனை, rhs);
      /* An explicit constant 0 or type nullptr_t can convert to a pointer,
	 or one that results from arithmetic, even including a cast to
	 integer type.  */
      இல்லையெனில் எனில் (!null_pointer_constant)
	தேர்வு (errtype)
	  {
	  நிலை ic_argpass:
	    {
	      auto_diagnostic_group d;
	      range_label_for_type_mismatch rhs_label (rhstype, type);
	      gcc_rich_location richloc (கோவை_loc, &rhs_label,
					 highlight_colors::actual);
	      எனில் (permerror_opt (&richloc, OPT_Wint_conversion,
				 "passing argument %d of %qE makes pointer "
				 "from integer without a cast", parmnum, rname))
		{
		  maybe_emit_indirection_note (கோவை_loc, rhs, type);
		  inform_for_arg (fundecl, கோவை_loc, parmnum, type, rhstype);
		}
	    }
	    நிறுத்து;
	  நிலை ic_assign:
	    permerror_opt (location, OPT_Wint_conversion,
			   "assignment to %qT from %qT makes pointer from "
			   "integer without a cast", type, rhstype);
	    நிறுத்து;
	  நிலை ic_init:
	  நிலை ic_init_const:
	    permerror_init (location, OPT_Wint_conversion,
			    "initialization of %qT from %qT makes pointer "
			    "from integer without a cast", type, rhstype);
	    நிறுத்து;
	  நிலை ic_return:
	    permerror_init (location, OPT_Wint_conversion,
			    "returning %qT from a function with return type "
			    "%qT makes pointer from integer without a cast",
			    rhstype, type);
	    நிறுத்து;
	  இயல்பு:
	    gcc_unreachable ();
	  }

      திரும்பு convert (type, rhs);
    }
  இல்லையெனில் எனில் ((codel == INTEGER_TYPE || codel == BITINT_TYPE)
	   && coder == POINTER_TYPE)
    {
      தேர்வு (errtype)
	{
	நிலை ic_argpass:
	  {
	    auto_diagnostic_group d;
	    range_label_for_type_mismatch rhs_label (rhstype, type);
	    gcc_rich_location richloc (கோவை_loc, &rhs_label,
				       highlight_colors::actual);
	    எனில் (permerror_opt (&richloc, OPT_Wint_conversion,
			       "passing argument %d of %qE makes integer from "
			       "pointer without a cast", parmnum, rname))
	      {
		maybe_emit_indirection_note (கோவை_loc, rhs, type);
		inform_for_arg (fundecl, கோவை_loc, parmnum, type, rhstype);
	      }
	  }
	  நிறுத்து;
	நிலை ic_assign:
	  permerror_opt (location, OPT_Wint_conversion,
			 "assignment to %qT from %qT makes integer from "
			 "pointer without a cast", type, rhstype);
	  நிறுத்து;
	நிலை ic_init:
	நிலை ic_init_const:
	  permerror_init (location, OPT_Wint_conversion,
			  "initialization of %qT from %qT makes integer "
			  "from pointer without a cast", type, rhstype);
	  நிறுத்து;
	நிலை ic_return:
	  permerror_opt (location, OPT_Wint_conversion, "returning %qT from a "
			 "function with return type %qT makes integer from "
			 "pointer without a cast", rhstype, type);
	  நிறுத்து;
	இயல்பு:
	  gcc_unreachable ();
	}

      திரும்பு convert (type, rhs);
    }
  இல்லையெனில் எனில் (C_BOOLEAN_TYPE_P (type)
	   /* The type nullptr_t may be converted to bool.  The
	      result is false.  */
	   && (coder == POINTER_TYPE || coder == NULLPTR_TYPE))
    {
      மரம் ret;
      தருக்க save = in_late_இருமம்_op;
      in_late_இருமம்_op = உண்மை;
      ret = convert (type, rhs);
      in_late_இருமம்_op = save;
      திரும்பு ret;
    }
  இல்லையெனில் எனில் (codel == NULLPTR_TYPE && null_pointer_constant)
    திரும்பு convert (type, rhs);

  தேர்வு (errtype)
    {
    நிலை ic_argpass:
      {
	auto_diagnostic_group d;
	range_label_for_type_mismatch rhs_label (rhstype, type);
	gcc_rich_location richloc (கோவை_loc, &rhs_label,
				   highlight_colors::actual);
	மாறிலி எழுத்து செய்தி[] = G_("incompatible type for argument %d of %qE");
	எனில் (warnopt)
	  warning_at (கோவை_loc, warnopt, செய்தி, parmnum, rname);
	இல்லையெனில்
	  error_at (&richloc, செய்தி, parmnum, rname);
	inform_for_arg (fundecl, கோவை_loc, parmnum, type, rhstype);
      }
      நிறுத்து;
    நிலை ic_assign:
      {
	மாறிலி எழுத்து செய்தி[]
	  = G_("incompatible types when assigning to type %qT from type %qT");
	எனில் (warnopt)
	  warning_at (கோவை_loc, 0, செய்தி, type, rhstype);
	இல்லையெனில்
	  error_at (கோவை_loc, செய்தி, type, rhstype);
	நிறுத்து;
      }
    நிலை ic_init:
    நிலை ic_init_const:
      {
	மாறிலி எழுத்து செய்தி[]
	  = G_("incompatible types when initializing type %qT using type %qT");
	எனில் (warnopt)
	  warning_at (location, 0, செய்தி, type, rhstype);
	இல்லையெனில்
	  error_at (location, செய்தி, type, rhstype);
	நிறுத்து;
      }
    நிலை ic_return:
      {
	மாறிலி எழுத்து செய்தி[]
	  = G_("incompatible types when returning type %qT but %qT was expected");
	எனில் (warnopt)
	  warning_at (location, 0, செய்தி, rhstype, type);
	இல்லையெனில்
	  error_at (location, செய்தி, rhstype, type);
	நிறுத்து;
      }
    இயல்பு:
      gcc_unreachable ();
    }

  திரும்பு error_mark_முனை;
}

/* If VALUE is a compound expr all of whose expressions are constant, then
   return its value.  Otherwise, return error_mark_node.

   This is for handling COMPOUND_EXPRs as initializer elements
   which is allowed with a warning when -pedantic is specified.  */

நிலையான மரம்
valid_compound_கோவை_initializer (மரம் மதிப்பு, மரம் endtype)
{
  எனில் (மரம்_CODE (மதிப்பு) == COMPOUND_கோவை)
    {
      எனில் (valid_compound_கோவை_initializer (மரம்_OPERAND (மதிப்பு, 0), endtype)
	  == error_mark_முனை)
	திரும்பு error_mark_முனை;
      திரும்பு valid_compound_கோவை_initializer (மரம்_OPERAND (மதிப்பு, 1),
					      endtype);
    }
  இல்லையெனில் எனில் (!initializer_constant_valid_p (மதிப்பு, endtype))
    திரும்பு error_mark_முனை;
  இல்லையெனில்
    திரும்பு மதிப்பு;
}

/* Perform appropriate conversions on the initial value of a variable,
   store it in the declaration DECL,
   and print any error messages that are appropriate.
   If ORIGTYPE is not NULL_TREE, it is the original type of INIT.
   If the init is invalid, store an ERROR_MARK.

   INIT_LOC is the location of the initial value.  */

வெறுமை
store_init_மதிப்பு (location_t init_loc, மரம் decl, மரம் init, மரம் origtype)
{
  மரம் மதிப்பு, type;
  தருக்க npc = பொய்;
  தருக்க int_const_கோவை = பொய்;
  தருக்க arith_const_கோவை = பொய்;

  /* If variable's type was invalidly declared, just ignore it.  */

  type = மரம்_TYPE (decl);
  எனில் (மரம்_CODE (type) == ERROR_MARK)
    திரும்பு;

  /* Digest the specified initializer into an expression.  */

  எனில் (init)
    {
      npc = null_pointer_constant_p (init);
      int_const_கோவை = (மரம்_CODE (init) == INTEGER_CST
			&& !மரம்_OVERFLOW (init)
			&& INTEGRAL_TYPE_P (மரம்_TYPE (init)));
      /* Not fully determined before folding.  */
      arith_const_கோவை = உண்மை;
    }
  தருக்க constexpr_p = (VAR_P (decl)
		      && C_DECL_DECLARED_CONSTEXPR (decl));
  மதிப்பு = digest_init (init_loc, decl, type, init, origtype, npc,
		       int_const_கோவை, arith_const_கோவை, உண்மை,
		       மரம்_STATIC (decl) || constexpr_p, constexpr_p);

  /* Store the expression if valid; else report error.  */

  எனில் (!in_system_header_at (உள்ளீடு_location)
      && AGGREGATE_TYPE_P (மரம்_TYPE (decl)) && !மரம்_STATIC (decl))
    warning (OPT_Wtraditional, "traditional C rejects automatic "
	     "aggregate initialization");

  எனில் (மதிப்பு != error_mark_முனை || மரம்_CODE (decl) != FUNCTION_DECL)
    DECL_INITIAL (decl) = மதிப்பு;

  /* ANSI wants warnings about out-of-range constant initializers.  */
  STRIP_TYPE_NOPS (மதிப்பு);
  எனில் (மரம்_STATIC (decl))
    constant_expression_warning (மதிப்பு);

  /* Check if we need to set array size from compound literal size.  */
  எனில் (மரம்_CODE (type) == ARRAY_TYPE
      && TYPE_DOMAIN (type) == NULL_மரம்
      && மதிப்பு != error_mark_முனை)
    {
      மரம் inside_init = init;

      STRIP_TYPE_NOPS (inside_init);
      inside_init = fold (inside_init);

      எனில் (மரம்_CODE (inside_init) == COMPOUND_LITERAL_கோவை)
	{
	  மரம் cldecl = COMPOUND_LITERAL_கோவை_DECL (inside_init);

	  எனில் (TYPE_DOMAIN (மரம்_TYPE (cldecl)))
	    {
	      /* For int foo[] = (int [3]){1}; we need to set array size
		 now since later on array initializer will be just the
		 brace enclosed list of the compound literal.  */
	      மரம் etype = strip_array_types (மரம்_TYPE (decl));
	      type = build_distinct_type_copy (TYPE_MAIN_VARIANT (type));
	      TYPE_DOMAIN (type) = TYPE_DOMAIN (மரம்_TYPE (cldecl));
	      layout_type (type);
	      layout_decl (cldecl, 0);
	      மரம்_TYPE (decl)
		= c_build_qualified_type (type, TYPE_QUALS (etype));
	    }
	}
    }
}

/* Methods for storing and printing names for error messages.  */

/* Implement a spelling stack that allows components of a name to be pushed
   and popped.  Each element on the stack is this structure.  */

கட்டமைப்பு spelling
{
  முழு kind;
  ஒன்றிப்பு
    {
      unsigned HOST_WIDE_INT i;
      மாறிலி எழுத்து *s;
    } u;
};

#define SPELLING_STRING 1
#define SPELLING_MEMBER 2
#define SPELLING_BOUNDS 3

நிலையான கட்டமைப்பு spelling *spelling;	/* Next stack element (unused).  */
நிலையான கட்டமைப்பு spelling *spelling_base;	/* Spelling stack base.  */
நிலையான முழு spelling_size;		/* Size of the spelling stack.  */

/* Macros to save and restore the spelling stack around push_... functions.
   Alternative to SAVE_SPELLING_STACK.  */

#define SPELLING_DEPTH() (spelling - spelling_base)
#define RESTORE_SPELLING_DEPTH(DEPTH) (spelling = spelling_base + (DEPTH))

/* Push an element on the spelling stack with type KIND and assign VALUE
   to MEMBER.  */

#define தள்ளு_SPELLING(KIND, மதிப்பு_2, MEMBER)				\
{									\
  முழு depth = SPELLING_DEPTH ();					\
									\
  எனில் (depth >= spelling_size)						\
    {									\
      spelling_size += 10;						\
      spelling_base = XRESIZEVEC (கட்டமைப்பு spelling, spelling_base,	\
				  spelling_size);			\
      RESTORE_SPELLING_DEPTH (depth);					\
    }									\
									\
  spelling->kind = (KIND);						\
  spelling->MEMBER = (மதிப்பு_2);						\
  spelling++;								\
}

/* Push STRING on the stack.  Printed literally.  */

நிலையான வெறுமை
தள்ளு_string (மாறிலி எழுத்து *string)
{
  தள்ளு_SPELLING (SPELLING_STRING, string, u.s);
}

/* Push a member name on the stack.  Printed as '.' STRING.  */

நிலையான வெறுமை
தள்ளு_member_name (மரம் decl)
{
  மாறிலி எழுத்து *மாறிலி string
    = (DECL_NAME (decl)
       ? identifier_to_locale (IDENTIFIER_POINTER (DECL_NAME (decl)))
       : _("<anonymous>"));
  தள்ளு_SPELLING (SPELLING_MEMBER, string, u.s);
}

/* Push an array bounds on the stack.  Printed as [BOUNDS].  */

நிலையான வெறுமை
தள்ளு_array_bounds (unsigned HOST_WIDE_INT bounds)
{
  தள்ளு_SPELLING (SPELLING_BOUNDS, bounds, u.i);
}

/* Compute the maximum size in bytes of the printed spelling.  */

நிலையான முழு
spelling_length (வெறுமை)
{
  முழு size = 0;
  கட்டமைப்பு spelling *p;

  க்கு (p = spelling_base; p < spelling; p++)
    {
      எனில் (p->kind == SPELLING_BOUNDS)
	size += 25;
      இல்லையெனில்
	size += strlen (p->u.s) + 1;
    }

  திரும்பு size;
}

/* Print the spelling to BUFFER and return it.  */

நிலையான எழுத்து *
print_spelling (எழுத்து *buffer)
{
  எழுத்து *d = buffer;
  கட்டமைப்பு spelling *p;

  க்கு (p = spelling_base; p < spelling; p++)
    எனில் (p->kind == SPELLING_BOUNDS)
      {
	sprintf (d, "[" HOST_WIDE_INT_PRINT_UNSIGNED "]", p->u.i);
	d += strlen (d);
      }
    இல்லையெனில்
      {
	மாறிலி எழுத்து *s;
	எனில் (p->kind == SPELLING_MEMBER)
	  *d++ = '.';
	க்கு (s = p->u.s; (*d = *s++); d++)
	  ;
      }
  *d++ = '\0';
  திரும்பு buffer;
}

/* Check whether INIT, a floating or integer constant, is
   representable in TYPE, a real floating type with the same radix or
   a decimal floating type initialized with a binary floating
   constant.  Return true if OK, false if not.  */
நிலையான தருக்க
constexpr_init_fits_real_type (மரம் type, மரம் init)
{
  gcc_assert (SCALAR_FLOAT_TYPE_P (type));
  gcc_assert (மரம்_CODE (init) == INTEGER_CST || மரம்_CODE (init) == REAL_CST);
  எனில் (மரம்_CODE (init) == REAL_CST
      && TYPE_MODE (மரம்_TYPE (init)) == TYPE_MODE (type))
    {
      /* Same mode, no conversion required except for the case of
	 signaling NaNs if the types are incompatible (e.g. double and
	 long double with the same mode).  */
      எனில் (REAL_மதிப்பு_ISSIGNALING_NAN (மரம்_REAL_CST (init))
	  && !comptypes (TYPE_MAIN_VARIANT (type),
			 TYPE_MAIN_VARIANT (மரம்_TYPE (init))))
	திரும்பு பொய்;
      திரும்பு உண்மை;
    }
  எனில் (மரம்_CODE (init) == INTEGER_CST)
    {
      மரம் converted = build_real_from_int_cst (type, init);
      தருக்க fail = பொய்;
      wide_int w = real_to_integer (&மரம்_REAL_CST (converted), &fail,
				    TYPE_PRECISION (மரம்_TYPE (init)));
      திரும்பு !fail && wi::eq_p (w, wi::to_wide (init));
    }
  எனில் (REAL_மதிப்பு_ISSIGNALING_NAN (மரம்_REAL_CST (init)))
    திரும்பு பொய்;
  எனில் ((REAL_மதிப்பு_ISINF (மரம்_REAL_CST (init))
       && MODE_HAS_INFINITIES (TYPE_MODE (type)))
      || (REAL_மதிப்பு_ISNAN (மரம்_REAL_CST (init))
	  && MODE_HAS_NANS (TYPE_MODE (type))))
    திரும்பு உண்மை;
  எனில் (DECIMAL_FLOAT_TYPE_P (type)
      && !DECIMAL_FLOAT_TYPE_P (மரம்_TYPE (init)))
    {
      /* This is valid if the real number represented by the
	 initializer can be exactly represented in the decimal
	 type.  Compare the values using MPFR.  */
      REAL_மதிப்பு_TYPE t;
      real_convert (&t, TYPE_MODE (type), &மரம்_REAL_CST (init));
      mpfr_t bin_val, dec_val;
      mpfr_init2 (bin_val, REAL_MODE_FORMAT (TYPE_MODE (மரம்_TYPE (init)))->p);
      mpfr_init2 (dec_val, REAL_MODE_FORMAT (TYPE_MODE (மரம்_TYPE (init)))->p);
      mpfr_from_real (bin_val, &மரம்_REAL_CST (init), MPFR_RNDN);
      எழுத்து string[256];
      real_to_decimal (string, &t, அளவு string, 0, 1);
      தருக்க res = (mpfr_strtofr (dec_val, string, வெற்று, 10, MPFR_RNDN) == 0
		  && mpfr_equal_p (bin_val, dec_val));
      mpfr_clear (bin_val);
      mpfr_clear (dec_val);
      திரும்பு res;
    }
  /* exact_real_truncate is not quite right here, since it doesn't
     allow even an exact conversion to subnormal values.  */
  REAL_மதிப்பு_TYPE t;
  real_convert (&t, TYPE_MODE (type), &மரம்_REAL_CST (init));
  திரும்பு real_identical (&t, &மரம்_REAL_CST (init));
}

/* Check whether INIT (location LOC) is valid as a 'constexpr'
   initializer for type TYPE, and give an error if not.  INIT has
   already been folded and verified to be constant.  INT_CONST_EXPR
   and ARITH_CONST_EXPR say whether it is an integer constant
   expression or arithmetic constant expression, respectively.  If
   TYPE is not a scalar type, this function does nothing.  */

நிலையான வெறுமை
check_constexpr_init (location_t loc, மரம் type, மரம் init,
		      தருக்க int_const_கோவை, தருக்க arith_const_கோவை)
{
  எனில் (POINTER_TYPE_P (type))
    {
      /* The initializer must be null.  */
      எனில் (மரம்_CODE (init) != INTEGER_CST || !integer_zerop (init))
	error_at (loc, "%<constexpr%> pointer initializer is not null");
      திரும்பு;
    }
  எனில் (INTEGRAL_TYPE_P (type))
    {
      /* The initializer must be an integer constant expression,
	 representable in the target type.  */
      எனில் (!int_const_கோவை)
	{
	  எனில் (மரம்_CODE (init) == RAW_DATA_CST
	      && TYPE_PRECISION (type) == CHAR_BIT)
	    {
	      எனில் (!TYPE_UNSIGNED (type))
		க்கு (unsigned முழு i = 0;
		     i < (unsigned) RAW_DATA_LENGTH (init); ++i)
		  எனில் (RAW_DATA_SCHAR_ELT (init, i) < 0)
		    {
		      error_at (loc, "%<constexpr%> initializer not "
				"representable in type of object");
		      நிறுத்து;
		    }
	    }
	  இல்லையெனில்
	    error_at (loc, "%<constexpr%> integer initializer is not an "
		      "integer constant expression");
	}
      இல்லையெனில் எனில் (!int_fits_type_p (init, type))
	error_at (loc, "%<constexpr%> initializer not representable in "
		  "type of object");
      திரும்பு;
    }
  /* We don't apply any extra checks to extension types such as vector
     or fixed-point types.  */
  எனில் (மரம்_CODE (type) != REAL_TYPE && மரம்_CODE (type) != COMPLEX_TYPE)
    திரும்பு;
  எனில் (!arith_const_கோவை)
    {
      error_at (loc, "%<constexpr%> initializer is not an arithmetic "
		"constant expression");
      திரும்பு;
    }
  /* We don't apply any extra checks to complex integers.  */
  எனில் (மரம்_CODE (type) == COMPLEX_TYPE
      && மரம்_CODE (மரம்_TYPE (type)) != REAL_TYPE)
    திரும்பு;
  /* Following N3082, a real type cannot be initialized from a complex
     type and a binary type cannot be initialized from a decimal type
     (but initializing a decimal type from a binary type is OK).
     Signaling NaN initializers are OK only if the types are
     compatible (not just the same mode); all quiet NaN and infinity
     initializations are considered to preserve the value.  */
  எனில் (மரம்_CODE (மரம்_TYPE (init)) == COMPLEX_TYPE
      && SCALAR_FLOAT_TYPE_P (type))
    {
      error_at (loc, "%<constexpr%> initializer for a real type is of "
		"complex type");
      திரும்பு;
    }
  எனில் (SCALAR_FLOAT_TYPE_P (type)
      && SCALAR_FLOAT_TYPE_P (மரம்_TYPE (init))
      && DECIMAL_FLOAT_TYPE_P (மரம்_TYPE (init))
      && !DECIMAL_FLOAT_TYPE_P (type))
    {
      error_at (loc, "%<constexpr%> initializer for a binary "
		"floating-point type is of decimal type");
      திரும்பு;
    }
  தருக்க fits;
  எனில் (மரம்_CODE (type) == COMPLEX_TYPE)
    {
      தேர்வு (மரம்_CODE (init))
	{
	நிலை INTEGER_CST:
	நிலை REAL_CST:
	  fits = constexpr_init_fits_real_type (மரம்_TYPE (type), init);
	  நிறுத்து;
	நிலை COMPLEX_CST:
	  fits = (constexpr_init_fits_real_type (மரம்_TYPE (type),
						 மரம்_REALPART (init))
		  && constexpr_init_fits_real_type (மரம்_TYPE (type),
						    மரம்_IMAGPART (init)));
	  நிறுத்து;
	இயல்பு:
	  gcc_unreachable ();
	}
    }
  இல்லையெனில்
    fits = constexpr_init_fits_real_type (type, init);
  எனில் (!fits)
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

நிலையான மரம்
digest_init (location_t init_loc, மரம் decl, மரம் type, மரம் init,
	     மரம் origtype, தருக்க null_pointer_constant, தருக்க int_const_கோவை,
	     தருக்க arith_const_கோவை, தருக்க strict_string,
	     தருக்க require_constant, தருக்க require_constexpr)
{
  எண்ணிக்கை மரம்_code code = மரம்_CODE (type);
  மரம் inside_init = init;
  மரம் semantic_type = NULL_மரம்;
  தருக்க maybe_const = உண்மை;

  எனில் (type == error_mark_முனை
      || !init
      || error_operand_p (init))
    திரும்பு error_mark_முனை;

  STRIP_TYPE_NOPS (inside_init);

  /* If require_constant is TRUE,  when the initializer is a call to
     .ACCESS_WITH_SIZE, use the first argument as the initializer.
     For example:
     y = (char *) .ACCESS_WITH_SIZE ((char *) &static_annotated.c,...)
     will be converted to
     y = &static_annotated.c.  */

  எனில் (require_constant
      && மரம்_CODE (inside_init) == NOP_கோவை
      && மரம்_CODE (மரம்_OPERAND (inside_init, 0)) == CALL_கோவை
      && is_access_with_size_p (மரம்_OPERAND (inside_init, 0)))
    inside_init
      = get_ref_from_access_with_size (மரம்_OPERAND (inside_init, 0));

  எனில் (!c_in_omp_for)
    {
      எனில் (மரம்_CODE (inside_init) == EXCESS_PRECISION_கோவை)
	{
	  semantic_type = மரம்_TYPE (inside_init);
	  inside_init = மரம்_OPERAND (inside_init, 0);
	}
      inside_init = c_fully_fold (inside_init, require_constant, &maybe_const);
    }
  /* TODO: this may not detect all cases of expressions folding to
     constants that are not arithmetic constant expressions.  */
  எனில் (!maybe_const)
    arith_const_கோவை = பொய்;
  இல்லையெனில் எனில் (!INTEGRAL_TYPE_P (மரம்_TYPE (inside_init))
	   && மரம்_CODE (மரம்_TYPE (inside_init)) != REAL_TYPE
	   && மரம்_CODE (மரம்_TYPE (inside_init)) != COMPLEX_TYPE)
    arith_const_கோவை = பொய்;
  இல்லையெனில் எனில் (மரம்_CODE (inside_init) != INTEGER_CST
	   && மரம்_CODE (inside_init) != REAL_CST
	   && மரம்_CODE (inside_init) != COMPLEX_CST
	   && மரம்_CODE (inside_init) != RAW_DATA_CST)
    arith_const_கோவை = பொய்;
  இல்லையெனில் எனில் (மரம்_OVERFLOW (inside_init))
    arith_const_கோவை = பொய்;

  /* Initialization of an array of chars from a string constant
     optionally enclosed in braces.  */

  எனில் (code == ARRAY_TYPE && inside_init
      && மரம்_CODE (inside_init) == STRING_CST)
    {
      மரம் typ1
	= (TYPE_ATOMIC (மரம்_TYPE (type))
	   ? c_build_qualified_type (TYPE_MAIN_VARIANT (மரம்_TYPE (type)),
				     TYPE_QUAL_ATOMIC)
	   : TYPE_MAIN_VARIANT (மரம்_TYPE (type)));
      /* Note that an array could be both an array of character type
	 and an array of wchar_t if wchar_t is signed char or unsigned
	 char.  */
      தருக்க char_array = (typ1 == char_type_முனை
			 || typ1 == signed_char_type_முனை
			 || typ1 == unsigned_char_type_முனை);
      தருக்க wchar_array = comptypes (typ1, wchar_type_முனை);
      தருக்க char16_array = comptypes (typ1, char16_type_முனை);
      தருக்க char32_array = comptypes (typ1, char32_type_முனை);

      எனில் (char_array || wchar_array || char16_array || char32_array)
	{
	  கட்டமைப்பு c_கோவை கோவை;
	  மரம் typ2 = TYPE_MAIN_VARIANT (மரம்_TYPE (மரம்_TYPE (inside_init)));
	  தருக்க incompat_string_cst = பொய்;
	  கோவை.மதிப்பு = inside_init;
	  கோவை.original_code = (strict_string ? STRING_CST : ERROR_MARK);
	  கோவை.original_type = வெற்று;
	  கோவை.m_decimal = 0;
	  maybe_warn_string_init (init_loc, type, கோவை);

	  எனில் (flexible_array_member_type_p (type))
	    pedwarn_init (init_loc, OPT_Wpedantic,
			  "initialization of a flexible array member");

	  எனில் (comptypes (TYPE_MAIN_VARIANT (மரம்_TYPE (inside_init)),
			 TYPE_MAIN_VARIANT (type)))
	    திரும்பு inside_init;

	  எனில் (char_array)
	    {
	      எனில் (typ2 != char_type_முனை && typ2 != char8_type_முனை)
		incompat_string_cst = உண்மை;
	    }
	  இல்லையெனில் எனில் (!comptypes (typ1, typ2))
	    incompat_string_cst = உண்மை;

          எனில் (incompat_string_cst)
            {
	      error_init (init_loc, "cannot initialize array of %qT from "
			  "a string literal with type array of %qT",
			  typ1, typ2);
	      திரும்பு error_mark_முனை;
            }

	  எனில் (require_constexpr
	      && TYPE_UNSIGNED (typ1) != TYPE_UNSIGNED (typ2))
	    {
	      /* Check if all characters of the string can be
		 represented in the type of the constexpr object being
		 initialized.  */
	      unsigned HOST_WIDE_INT len = மரம்_STRING_LENGTH (inside_init);
	      மாறிலி unsigned எழுத்து *p =
		(மாறிலி unsigned எழுத்து *) மரம்_STRING_POINTER (inside_init);
	      gcc_assert (CHAR_TYPE_SIZE == 8 && CHAR_BIT == 8);
	      க்கு (unsigned i = 0; i < len; i++)
		எனில் (p[i] > 127)
		  {
		    error_init (init_loc, "%<constexpr%> initializer not "
				"representable in type of object");
		    நிறுத்து;
		  }
	    }

	  எனில் (TYPE_DOMAIN (type) != NULL_மரம்
	      && TYPE_SIZE (type) != NULL_மரம்
	      && மரம்_CODE (TYPE_SIZE (type)) == INTEGER_CST)
	    {
	      unsigned HOST_WIDE_INT len = மரம்_STRING_LENGTH (inside_init);

	      எனில் (compare_மரம்_int (TYPE_SIZE_UNIT (type), len) < 0)
		{
		  unsigned HOST_WIDE_INT avail
		    = மரம்_to_uhwi (TYPE_SIZE_UNIT (type));
		  unsigned unit = TYPE_PRECISION (typ1) / BITS_PER_UNIT;
		  மாறிலி எழுத்து *p = மரம்_STRING_POINTER (inside_init);

		  /* Construct truncated string.  */
		  inside_init = build_string (avail, p);

		  /* Subtract the size of a single (possibly wide) character
		     because it may be ok to ignore the terminating NUL char
		     that is counted in the length of the constant.  */
		  எனில் (len - unit > avail)
		    pedwarn_init (init_loc, 0,
				  "initializer-string for array of %qT "
				  "is too long (%wu chars into %wu "
				  "available)", typ1, len, avail);
		  இல்லையெனில் எனில் (warn_cxx_compat)
		    warning_at (init_loc, OPT_Wc___compat,
				"initializer-string for array of %qT "
				"is too long for C++ (%wu chars into %wu "
				"available)", typ1, len, avail);
		  இல்லையெனில் எனில் (warn_unterminated_string_initialization
			   && get_attr_nonstring_decl (decl) == NULL_மரம்)
		    warning_at (init_loc,
				OPT_Wunterminated_string_initialization,
				"initializer-string for array of %qT "
				"truncates NUL terminator but destination "
				"lacks %qs attribute (%wu chars into %wu "
				"available)", typ1, "nonstring", len, avail);
		}
	    }

	  மரம்_TYPE (inside_init) = type;
	  திரும்பு inside_init;
	}
      இல்லையெனில் எனில் (INTEGRAL_TYPE_P (typ1))
	{
	  error_init (init_loc, "array of inappropriate type initialized "
		      "from string constant");
	  திரும்பு error_mark_முனை;
	}
    }

  /* Build a VECTOR_CST from a *constant* vector constructor.  If the
     vector constructor is not constant (e.g. {1,2,3,foo()}) then punt
     below and handle as a constructor.  */
  எனில் (code == VECTOR_TYPE
      && VECTOR_TYPE_P (மரம்_TYPE (inside_init))
      && vector_types_convertible_p (மரம்_TYPE (inside_init), type, உண்மை)
      && மரம்_CONSTANT (inside_init))
    {
      எனில் (மரம்_CODE (inside_init) == VECTOR_CST
	  && comptypes (TYPE_MAIN_VARIANT (மரம்_TYPE (inside_init)),
			TYPE_MAIN_VARIANT (type)))
	திரும்பு inside_init;

      எனில் (மரம்_CODE (inside_init) == CONSTRUCTOR)
	{
	  unsigned HOST_WIDE_INT ix;
	  மரம் மதிப்பு;
	  தருக்க constant_p = உண்மை;

	  /* Iterate through elements and check if all constructor
	     elements are *_CSTs.  */
	  FOR_EACH_CONSTRUCTOR_மதிப்பு (CONSTRUCTOR_ELTS (inside_init), ix, மதிப்பு)
	    எனில் (!CONSTANT_CLASS_P (மதிப்பு))
	      {
		constant_p = பொய்;
		நிறுத்து;
	      }

	  எனில் (constant_p)
	    திரும்பு build_vector_from_ctor (type,
					   CONSTRUCTOR_ELTS (inside_init));
	}
    }

  எனில் (warn_sequence_point)
    verify_sequence_points (inside_init);

  /* Any type can be initialized
     from an expression of the same type, optionally with braces.  */

  எனில் (inside_init && மரம்_TYPE (inside_init) != NULL_மரம்
      && (comptypes (TYPE_MAIN_VARIANT (மரம்_TYPE (inside_init)),
		     TYPE_MAIN_VARIANT (type))
	  || (code == ARRAY_TYPE
	      && comptypes (மரம்_TYPE (inside_init), type))
	  || (gnu_vector_type_p (type)
	      && comptypes (மரம்_TYPE (inside_init), type))
	  || (code == POINTER_TYPE
	      && மரம்_CODE (மரம்_TYPE (inside_init)) == ARRAY_TYPE
	      && comptypes (மரம்_TYPE (மரம்_TYPE (inside_init)),
			    மரம்_TYPE (type)))))
    {
      எனில் (code == POINTER_TYPE)
	{
	  எனில் (மரம்_CODE (மரம்_TYPE (inside_init)) == ARRAY_TYPE)
	    {
	      எனில் (மரம்_CODE (inside_init) == STRING_CST
		  || மரம்_CODE (inside_init) == COMPOUND_LITERAL_கோவை)
		inside_init = array_to_pointer_conversion
		  (init_loc, inside_init);
	      இல்லையெனில்
		{
		  error_init (init_loc, "invalid use of non-lvalue array");
		  திரும்பு error_mark_முனை;
		}
	    }
	}

      எனில் (code == VECTOR_TYPE || c_hardbool_type_attr (type))
	/* Although the types are compatible, we may require a
	   conversion.  */
	inside_init = convert (type, inside_init);

      எனில் ((code == RECORD_TYPE || code == UNION_TYPE)
	  && !comptypes (TYPE_MAIN_VARIANT (type), TYPE_MAIN_VARIANT (மரம்_TYPE (inside_init))))
	{
	  error_init (init_loc, "invalid initializer");
	  திரும்பு error_mark_முனை;
	}

      எனில் (require_constant
	  && மரம்_CODE (inside_init) == COMPOUND_LITERAL_கோவை)
	{
	  /* As an extension, allow initializing objects with static storage
	     duration with compound literals (which are then treated just as
	     the brace enclosed list they contain).  Also allow this for
	     vectors, as we can only assign them with compound literals.  */
	  எனில் (flag_isoc99 && code != VECTOR_TYPE)
	    pedwarn_init (init_loc, OPT_Wpedantic, "initializer element "
			  "is not constant");
	  மரம் decl = COMPOUND_LITERAL_கோவை_DECL (inside_init);
	  inside_init = DECL_INITIAL (decl);
	}

      எனில் (code == ARRAY_TYPE && மரம்_CODE (inside_init) != STRING_CST
	  && மரம்_CODE (inside_init) != CONSTRUCTOR)
	{
	  error_init (init_loc, "array initialized from non-constant array "
		      "expression");
	  திரும்பு error_mark_முனை;
	}

      /* Compound expressions can only occur here if -Wpedantic or
	 -pedantic-errors is specified.  In the later case, we always want
	 an error.  In the former case, we simply want a warning.  */
      எனில் (require_constant && pedantic
	  && மரம்_CODE (inside_init) == COMPOUND_கோவை)
	{
	  inside_init
	    = valid_compound_கோவை_initializer (inside_init,
					       மரம்_TYPE (inside_init));
	  எனில் (inside_init == error_mark_முனை)
	    error_init (init_loc, "initializer element is not constant");
	  இல்லையெனில்
	    pedwarn_init (init_loc, OPT_Wpedantic,
			  "initializer element is not constant");
	  எனில் (flag_pedantic_errors)
	    inside_init = error_mark_முனை;
	}
      இல்லையெனில் எனில் (require_constant
	       && !initializer_constant_valid_p (inside_init,
						 மரம்_TYPE (inside_init)))
	{
	  error_init (init_loc, "initializer element is not constant");
	  inside_init = error_mark_முனை;
	}
      இல்லையெனில் எனில் (require_constant && !maybe_const)
	pedwarn_init (init_loc, OPT_Wpedantic,
		      "initializer element is not a constant expression");
      இல்லையெனில் எனில் (require_constexpr)
	check_constexpr_init (init_loc, type, inside_init,
			      int_const_கோவை, arith_const_கோவை);

      /* Added to enable additional -Wsuggest-attribute=format warnings.  */
      எனில் (மரம்_CODE (மரம்_TYPE (inside_init)) == POINTER_TYPE)
	inside_init = convert_for_assignment (init_loc, UNKNOWN_LOCATION,
					      type, inside_init, origtype,
					      (require_constant
					       ? ic_init_const
					       : ic_init), null_pointer_constant,
					      NULL_மரம், NULL_மரம், 0);
      எனில் (மரம்_CODE (inside_init) == RAW_DATA_CST
	  && c_inhibit_evaluation_warnings == 0
	  && warn_conversion
	  && !TYPE_UNSIGNED (type)
	  && TYPE_PRECISION (type) == CHAR_BIT)
	க்கு (unsigned முழு i = 0;
	     i < (unsigned) RAW_DATA_LENGTH (inside_init); ++i)
	  எனில் (RAW_DATA_SCHAR_ELT (inside_init, i) < 0)
	    warning_at (init_loc, OPT_Wconversion,
			"conversion from %qT to %qT changes value from "
			"%qd to %qd",
			integer_type_முனை, type,
			RAW_DATA_UCHAR_ELT (inside_init, i),
			RAW_DATA_SCHAR_ELT (inside_init, i));
      திரும்பு inside_init;
    }

  /* Handle scalar types, including conversions.  */

  எனில் (code == INTEGER_TYPE || code == REAL_TYPE || code == FIXED_POINT_TYPE
      || code == POINTER_TYPE || code == ENUMERAL_TYPE || code == BOOLEAN_TYPE
      || code == COMPLEX_TYPE || code == VECTOR_TYPE || code == NULLPTR_TYPE
      || code == BITINT_TYPE)
    {
      மரம் unconverted_init = inside_init;
      எனில் (மரம்_CODE (மரம்_TYPE (init)) == ARRAY_TYPE
	  && (மரம்_CODE (init) == STRING_CST
	      || மரம்_CODE (init) == COMPOUND_LITERAL_கோவை))
	inside_init = init = array_to_pointer_conversion (init_loc, init);
      எனில் (semantic_type)
	inside_init = build1 (EXCESS_PRECISION_கோவை, semantic_type,
			      inside_init);
      inside_init
	= convert_for_assignment (init_loc, UNKNOWN_LOCATION, type,
				  inside_init, origtype,
				  require_constant ? ic_init_const : ic_init,
				  null_pointer_constant, NULL_மரம், NULL_மரம்,
				  0);

      /* Check to see if we have already given an error message.  */
      எனில் (inside_init == error_mark_முனை)
	;
      இல்லையெனில் எனில் (require_constant && !மரம்_CONSTANT (inside_init))
	{
	  error_init (init_loc, "initializer element is not constant");
	  inside_init = error_mark_முனை;
	}
      இல்லையெனில் எனில் (require_constant
	       && !initializer_constant_valid_p (inside_init,
						 மரம்_TYPE (inside_init)))
	{
	  error_init (init_loc, "initializer element is not computable at "
		      "load time");
	  inside_init = error_mark_முனை;
	}
      இல்லையெனில் எனில் (require_constant && !maybe_const)
	pedwarn_init (init_loc, OPT_Wpedantic,
		      "initializer element is not a constant expression");
      இல்லையெனில் எனில் (require_constexpr)
	check_constexpr_init (init_loc, type, unconverted_init,
			      int_const_கோவை, arith_const_கோவை);

      திரும்பு inside_init;
    }

  /* Come here only for records and arrays.  */

  எனில் (COMPLETE_TYPE_P (type) && மரம்_CODE (TYPE_SIZE (type)) != INTEGER_CST)
    {
      error_init (init_loc,
		  "variable-sized object may not be initialized except "
		  "with an empty initializer");
      திரும்பு error_mark_முனை;
    }

  error_init (init_loc, "invalid initializer");
  திரும்பு error_mark_முனை;
}

/* Handle initializers that use braces.  */

/* Type of object we are accumulating a constructor for.
   This type is always a RECORD_TYPE, UNION_TYPE or ARRAY_TYPE.  */
நிலையான மரம் constructor_type;

/* For a RECORD_TYPE or UNION_TYPE, this is the chain of fields
   left to fill.  */
நிலையான மரம் constructor_fields;

/* For an ARRAY_TYPE, this is the specified index
   at which to store the next element we get.  */
நிலையான மரம் constructor_index;

/* For an ARRAY_TYPE, this is the maximum index.  */
நிலையான மரம் constructor_max_index;

/* For a RECORD_TYPE, this is the first field not yet written out.  */
நிலையான மரம் constructor_unfilled_fields;

/* For an ARRAY_TYPE, this is the index of the first element
   not yet written out.  */
நிலையான மரம் constructor_unfilled_index;

/* In a RECORD_TYPE, the byte index of the next consecutive field.
   This is so we can generate gaps between fields, when appropriate.  */
நிலையான மரம் constructor_bit_index;

/* If we are saving up the elements rather than allocating them,
   this is the list of elements so far (in reverse order,
   most recent first).  */
நிலையான vec<constructor_elt, va_gc> *constructor_elements;

/* 1 if constructor should be incrementally stored into a constructor chain,
   0 if all the elements should be kept in AVL tree.  */
நிலையான முழு constructor_incremental;

/* 1 if so far this constructor's elements are all compile-time constants.  */
நிலையான முழு constructor_constant;

/* 1 if so far this constructor's elements are all valid address constants.  */
நிலையான முழு constructor_simple;

/* 1 if this constructor has an element that cannot be part of a
   constant expression.  */
நிலையான முழு constructor_nonconst;

/* 1 if this constructor is erroneous so far.  */
நிலையான முழு constructor_erroneous;

/* 1 if this constructor is the universal zero initializer { 0 }.  */
நிலையான முழு constructor_zeroinit;

/* 1 if this constructor should have padding bits zeroed (C23 {}.  */
நிலையான தருக்க constructor_zero_padding_bits;

/* 1 if this constructor is a braced scalar initializer (further nested levels
   of braces are an error).  */
நிலையான தருக்க constructor_braced_scalar;

/* Structure for managing pending initializer elements, organized as an
   AVL tree.  */

கட்டமைப்பு init_முனை
{
  கட்டமைப்பு init_முனை *இடது, *வலது;
  கட்டமைப்பு init_முனை *parent;
  முழு balance;
  மரம் purpose;
  மரம் மதிப்பு;
  மரம் origtype;
};

/* Tree of pending elements at this constructor level.
   These are elements encountered out of order
   which belong at places we haven't reached yet in actually
   writing the output.
   Will never hold tree nodes across GC runs.  */
நிலையான கட்டமைப்பு init_முனை *constructor_pending_elts;

/* The SPELLING_DEPTH of this constructor.  */
நிலையான முழு constructor_depth;

/* DECL node for which an initializer is being read.
   0 means we are reading a constructor expression
   such as (struct foo) {...}.  */
நிலையான மரம் constructor_decl;

/* Nonzero if there were any member designators in this initializer.  */
நிலையான முழு constructor_designated;

/* Nesting depth of designator list.  */
நிலையான முழு designator_depth;

/* Nonzero if there were diagnosed errors in this designator list.  */
நிலையான முழு designator_erroneous;


/* This stack has a level for each implicit or explicit level of
   structuring in the initializer, including the outermost one.  It
   saves the values of most of the variables above.  */

கட்டமைப்பு constructor_range_அடுக்கு;

கட்டமைப்பு constructor_அடுக்கு
{
  கட்டமைப்பு constructor_அடுக்கு *next;
  மரம் type;
  மரம் fields;
  மரம் index;
  மரம் max_index;
  மரம் unfilled_index;
  மரம் unfilled_fields;
  மரம் bit_index;
  vec<constructor_elt, va_gc> *elements;
  கட்டமைப்பு init_முனை *pending_elts;
  முழு offset;
  முழு depth;
  /* If value nonzero, this value should replace the entire
     constructor at this level.  */
  கட்டமைப்பு c_கோவை replacement_மதிப்பு;
  கட்டமைப்பு constructor_range_அடுக்கு *range_அடுக்கு;
  எழுத்து constant;
  எழுத்து simple;
  எழுத்து nonconst;
  எழுத்து implicit;
  எழுத்து erroneous;
  எழுத்து outer;
  எழுத்து incremental;
  எழுத்து designated;
  தருக்க zero_padding_bits;
  தருக்க braced_scalar;
  முழு designator_depth;
};

நிலையான கட்டமைப்பு constructor_அடுக்கு *constructor_அடுக்கு;

/* This stack represents designators from some range designator up to
   the last designator in the list.  */

கட்டமைப்பு constructor_range_அடுக்கு
{
  கட்டமைப்பு constructor_range_அடுக்கு *next, *prev;
  கட்டமைப்பு constructor_அடுக்கு *அடுக்கு;
  மரம் range_start;
  மரம் index;
  மரம் range_end;
  மரம் fields;
};

நிலையான கட்டமைப்பு constructor_range_அடுக்கு *constructor_range_அடுக்கு;

/* This stack records separate initializers that are nested.
   Nested initializers can't happen in ANSI C, but GNU C allows them
   in cases like { ... (struct foo) { ... } ... }.  */

கட்டமைப்பு initializer_அடுக்கு
{
  கட்டமைப்பு initializer_அடுக்கு *next;
  மரம் decl;
  கட்டமைப்பு constructor_அடுக்கு *constructor_அடுக்கு;
  கட்டமைப்பு constructor_range_அடுக்கு *constructor_range_அடுக்கு;
  vec<constructor_elt, va_gc> *elements;
  கட்டமைப்பு spelling *spelling;
  கட்டமைப்பு spelling *spelling_base;
  முழு spelling_size;
  எழுத்து require_constant_மதிப்பு;
  எழுத்து require_constant_elements;
  எழுத்து require_constexpr_மதிப்பு;
  எழுத்து designated;
  rich_location *missing_brace_richloc;
};

நிலையான கட்டமைப்பு initializer_அடுக்கு *initializer_அடுக்கு;

/* Prepare to parse and output the initializer for variable DECL.  */

வெறுமை
start_init (மரம் decl, மரம் asmspec_மரம் ATTRIBUTE_UNUSED,
	    தருக்க init_require_constant, தருக்க init_require_constexpr,
	    rich_location *richloc)
{
  மாறிலி எழுத்து *locus;
  கட்டமைப்பு initializer_அடுக்கு *p = XNEW (கட்டமைப்பு initializer_அடுக்கு);

  p->decl = constructor_decl;
  p->require_constant_மதிப்பு = require_constant_மதிப்பு;
  p->require_constant_elements = require_constant_elements;
  p->require_constexpr_மதிப்பு = require_constexpr_மதிப்பு;
  p->constructor_அடுக்கு = constructor_அடுக்கு;
  p->constructor_range_அடுக்கு = constructor_range_அடுக்கு;
  p->elements = constructor_elements;
  p->spelling = spelling;
  p->spelling_base = spelling_base;
  p->spelling_size = spelling_size;
  p->next = initializer_அடுக்கு;
  p->missing_brace_richloc = richloc;
  p->designated = constructor_designated;
  initializer_அடுக்கு = p;

  constructor_decl = decl;
  constructor_designated = 0;

  require_constant_மதிப்பு = init_require_constant;
  require_constexpr_மதிப்பு = init_require_constexpr;
  எனில் (decl != NULL_மரம் && decl != error_mark_முனை)
    {
      require_constant_elements
	= ((init_require_constant || (pedantic && !flag_isoc99))
	   /* For a scalar, you can always use any value to initialize,
	      even within braces.  */
	   && AGGREGATE_TYPE_P (மரம்_TYPE (decl)));
      locus = identifier_to_locale (IDENTIFIER_POINTER (DECL_NAME (decl)));
    }
  இல்லையெனில்
    {
      require_constant_elements = பொய்;
      locus = _("(anonymous)");
    }

  constructor_அடுக்கு = 0;
  constructor_range_அடுக்கு = 0;

  found_missing_braces = 0;

  spelling_base = 0;
  spelling_size = 0;
  RESTORE_SPELLING_DEPTH (0);

  எனில் (locus)
    தள்ளு_string (locus);
}

வெறுமை
finish_init (வெறுமை)
{
  கட்டமைப்பு initializer_அடுக்கு *p = initializer_அடுக்கு;

  /* Free the whole constructor stack of this initializer.  */
  போது (constructor_அடுக்கு)
    {
      கட்டமைப்பு constructor_அடுக்கு *q = constructor_அடுக்கு;
      constructor_அடுக்கு = q->next;
      XDELETE (q);
    }

  gcc_assert (!constructor_range_அடுக்கு);

  /* Pop back to the data of the outer initializer (if any).  */
  XDELETE (spelling_base);

  constructor_decl = p->decl;
  require_constant_மதிப்பு = p->require_constant_மதிப்பு;
  require_constant_elements = p->require_constant_elements;
  require_constexpr_மதிப்பு = p->require_constexpr_மதிப்பு;
  constructor_அடுக்கு = p->constructor_அடுக்கு;
  constructor_designated = p->designated;
  constructor_range_அடுக்கு = p->constructor_range_அடுக்கு;
  constructor_elements = p->elements;
  spelling = p->spelling;
  spelling_base = p->spelling_base;
  spelling_size = p->spelling_size;
  initializer_அடுக்கு = p->next;
  XDELETE (p);
}

/* Call here when we see the initializer is surrounded by braces.
   This is instead of a call to push_init_level;
   it is matched by a call to pop_init_level.

   TYPE is the type to initialize, for a constructor expression.
   For an initializer for a decl, TYPE is zero.  */

வெறுமை
really_start_incremental_init (மரம் type)
{
  கட்டமைப்பு constructor_அடுக்கு *p = XNEW (கட்டமைப்பு constructor_அடுக்கு);

  எனில் (type == NULL_மரம்)
    type = மரம்_TYPE (constructor_decl);

  எனில் (VECTOR_TYPE_P (type)
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
  p->replacement_மதிப்பு.மதிப்பு = 0;
  p->replacement_மதிப்பு.original_code = ERROR_MARK;
  p->replacement_மதிப்பு.original_type = வெற்று;
  p->implicit = 0;
  p->range_அடுக்கு = 0;
  p->outer = 0;
  p->incremental = constructor_incremental;
  p->designated = constructor_designated;
  p->zero_padding_bits = constructor_zero_padding_bits;
  p->braced_scalar = constructor_braced_scalar;
  p->designator_depth = designator_depth;
  p->next = 0;
  constructor_அடுக்கு = p;

  constructor_constant = 1;
  constructor_simple = 1;
  constructor_nonconst = 0;
  constructor_depth = SPELLING_DEPTH ();
  constructor_elements = வெற்று;
  constructor_pending_elts = 0;
  constructor_type = type;
  constructor_incremental = 1;
  constructor_designated = 0;
  constructor_zero_padding_bits = பொய்;
  constructor_zeroinit = 1;
  constructor_braced_scalar = பொய்;
  designator_depth = 0;
  designator_erroneous = 0;

  எனில் (RECORD_OR_UNION_TYPE_P (constructor_type))
    {
      constructor_fields = TYPE_FIELDS (constructor_type);
      /* Skip any nameless bit fields at the beginning.  */
      போது (constructor_fields != NULL_மரம்
	     && DECL_UNNAMED_BIT_FIELD (constructor_fields))
	constructor_fields = DECL_CHAIN (constructor_fields);

      constructor_unfilled_fields = constructor_fields;
      constructor_bit_index = bitsize_zero_முனை;
    }
  இல்லையெனில் எனில் (மரம்_CODE (constructor_type) == ARRAY_TYPE)
    {
      எனில் (TYPE_DOMAIN (constructor_type))
	{
	  constructor_max_index
	    = TYPE_MAX_மதிப்பு (TYPE_DOMAIN (constructor_type));

	  /* Detect non-empty initializations of zero-length arrays.  */
	  எனில் (constructor_max_index == NULL_மரம்
	      && TYPE_SIZE (constructor_type))
	    constructor_max_index = integer_minus_one_முனை;

	  /* constructor_max_index needs to be an INTEGER_CST.  Attempts
	     to initialize VLAs with a nonempty initializer will cause a
	     proper error; avoid tree checking errors as well by setting a
	     safe value.  */
	  எனில் (constructor_max_index
	      && மரம்_CODE (constructor_max_index) != INTEGER_CST)
	    constructor_max_index = integer_minus_one_முனை;

	  constructor_index
	    = convert (bitsizetype,
		       TYPE_MIN_மதிப்பு (TYPE_DOMAIN (constructor_type)));
	}
      இல்லையெனில்
	{
	  constructor_index = bitsize_zero_முனை;
	  constructor_max_index = NULL_மரம்;
	}

      constructor_unfilled_index = constructor_index;
    }
  இல்லையெனில் எனில் (gnu_vector_type_p (constructor_type))
    {
      /* Vectors are like simple fixed-size arrays.  */
      constructor_max_index =
	bitsize_int (TYPE_VECTOR_SUBPARTS (constructor_type) - 1);
      constructor_index = bitsize_zero_முனை;
      constructor_unfilled_index = constructor_index;
    }
  இல்லையெனில்
    {
      /* Handle the case of int x = {5}; */
      constructor_fields = constructor_type;
      constructor_unfilled_fields = constructor_type;
      constructor_braced_scalar = உண்மை;
    }
}

வெளி location_t last_init_list_comma;

/* Called when we see an open brace for a nested initializer.  Finish
   off any pending levels with implicit braces.  */
வெறுமை
finish_implicit_inits (location_t loc, கட்டமைப்பு obstack *braced_init_obstack)
{
  போது (constructor_அடுக்கு->implicit)
    {
      எனில் (RECORD_OR_UNION_TYPE_P (constructor_type)
	  && constructor_fields == NULL_மரம்)
	process_init_element (உள்ளீடு_location,
			      எடு_init_level (loc, 1, braced_init_obstack,
					      last_init_list_comma),
			      உண்மை, braced_init_obstack);
      இல்லையெனில் எனில் (மரம்_CODE (constructor_type) == ARRAY_TYPE
	       && constructor_max_index
	       && மரம்_int_cst_lt (constructor_max_index,
				   constructor_index))
	process_init_element (உள்ளீடு_location,
			      எடு_init_level (loc, 1, braced_init_obstack,
					      last_init_list_comma),
			      உண்மை, braced_init_obstack);
      இல்லையெனில்
	நிறுத்து;
    }
}

/* Push down into a subobject, for initialization.
   If this is for an explicit set of braces, IMPLICIT is 0.
   If it is because the next element belongs at a lower level,
   IMPLICIT is 1 (or 2 if the push is because of designator list).  */

வெறுமை
தள்ளு_init_level (location_t loc, முழு implicit,
		 கட்டமைப்பு obstack *braced_init_obstack)
{
  கட்டமைப்பு constructor_அடுக்கு *p;
  மரம் மதிப்பு = NULL_மரம்;

  /* Unless this is an explicit brace, we need to preserve previous
     content if any.  */
  எனில் (implicit)
    {
      எனில் (RECORD_OR_UNION_TYPE_P (constructor_type) && constructor_fields)
	மதிப்பு = find_init_member (constructor_fields, braced_init_obstack);
      இல்லையெனில் எனில் (மரம்_CODE (constructor_type) == ARRAY_TYPE)
	மதிப்பு = find_init_member (constructor_index, braced_init_obstack);
    }

  p = XNEW (கட்டமைப்பு constructor_அடுக்கு);
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
  p->replacement_மதிப்பு.மதிப்பு = NULL_மரம்;
  p->replacement_மதிப்பு.original_code = ERROR_MARK;
  p->replacement_மதிப்பு.original_type = வெற்று;
  p->implicit = implicit;
  p->outer = 0;
  p->incremental = constructor_incremental;
  p->designated = constructor_designated;
  p->zero_padding_bits = constructor_zero_padding_bits;
  p->braced_scalar = constructor_braced_scalar;
  p->designator_depth = designator_depth;
  p->next = constructor_அடுக்கு;
  p->range_அடுக்கு = 0;
  constructor_அடுக்கு = p;

  constructor_constant = 1;
  constructor_simple = 1;
  constructor_nonconst = 0;
  constructor_depth = SPELLING_DEPTH ();
  constructor_elements = வெற்று;
  constructor_incremental = 1;
  /* If the upper initializer is designated, then mark this as
     designated too to prevent bogus warnings.  */
  constructor_designated = p->designated;
  /* If the upper initializer has padding bits zeroed, that includes
     all nested initializers as well.  */
  constructor_zero_padding_bits = p->zero_padding_bits;
  constructor_braced_scalar = பொய்;
  constructor_pending_elts = 0;
  எனில் (!implicit)
    {
      p->range_அடுக்கு = constructor_range_அடுக்கு;
      constructor_range_அடுக்கு = 0;
      designator_depth = 0;
      designator_erroneous = 0;
    }

  /* Don't die if an entire brace-pair level is superfluous
     in the containing level.  */
  எனில் (constructor_type == NULL_மரம்)
    ;
  இல்லையெனில் எனில் (RECORD_OR_UNION_TYPE_P (constructor_type))
    {
      /* Don't die if there are extra init elts at the end.  */
      எனில் (constructor_fields == NULL_மரம்)
	constructor_type = NULL_மரம்;
      இல்லையெனில்
	{
	  constructor_type = மரம்_TYPE (constructor_fields);
	  தள்ளு_member_name (constructor_fields);
	  constructor_depth++;
	}
    }
  இல்லையெனில் எனில் (மரம்_CODE (constructor_type) == ARRAY_TYPE)
    {
      constructor_type = மரம்_TYPE (constructor_type);
      தள்ளு_array_bounds (மரம்_to_uhwi (constructor_index));
      constructor_depth++;
    }

  எனில் (constructor_type == NULL_மரம்)
    {
      error_init (loc, "extra brace group at end of initializer");
      constructor_fields = NULL_மரம்;
      constructor_unfilled_fields = NULL_மரம்;
      திரும்பு;
    }

  எனில் (மதிப்பு && மரம்_CODE (மதிப்பு) == CONSTRUCTOR)
    {
      constructor_constant = மரம்_CONSTANT (மதிப்பு);
      constructor_simple = மரம்_STATIC (மதிப்பு);
      constructor_nonconst = CONSTRUCTOR_NON_CONST (மதிப்பு);
      constructor_elements = CONSTRUCTOR_ELTS (மதிப்பு);
      constructor_zero_padding_bits |= CONSTRUCTOR_ZERO_PADDING_BITS (மதிப்பு);
      எனில் (!vec_safe_is_empty (constructor_elements)
	  && (மரம்_CODE (constructor_type) == RECORD_TYPE
	      || மரம்_CODE (constructor_type) == ARRAY_TYPE))
	set_nonincremental_init (braced_init_obstack);
    }

  எனில் (implicit == 1)
    {
      found_missing_braces = 1;
      எனில் (initializer_அடுக்கு->missing_brace_richloc)
	initializer_அடுக்கு->missing_brace_richloc->add_fixit_செருகு_before
	  (loc, "{");
    }

  எனில் (RECORD_OR_UNION_TYPE_P (constructor_type))
    {
      constructor_fields = TYPE_FIELDS (constructor_type);
      /* Skip any nameless bit fields at the beginning.  */
      போது (constructor_fields != NULL_மரம்
	     && DECL_UNNAMED_BIT_FIELD (constructor_fields))
	constructor_fields = DECL_CHAIN (constructor_fields);

      constructor_unfilled_fields = constructor_fields;
      constructor_bit_index = bitsize_zero_முனை;
    }
  இல்லையெனில் எனில் (gnu_vector_type_p (constructor_type))
    {
      /* Vectors are like simple fixed-size arrays.  */
      constructor_max_index =
	bitsize_int (TYPE_VECTOR_SUBPARTS (constructor_type) - 1);
      constructor_index = bitsize_int (0);
      constructor_unfilled_index = constructor_index;
    }
  இல்லையெனில் எனில் (மரம்_CODE (constructor_type) == ARRAY_TYPE)
    {
      எனில் (TYPE_DOMAIN (constructor_type))
	{
	  constructor_max_index
	    = TYPE_MAX_மதிப்பு (TYPE_DOMAIN (constructor_type));

	  /* Detect non-empty initializations of zero-length arrays.  */
	  எனில் (constructor_max_index == NULL_மரம்
	      && TYPE_SIZE (constructor_type))
	    constructor_max_index = integer_minus_one_முனை;

	  /* constructor_max_index needs to be an INTEGER_CST.  Attempts
	     to initialize VLAs will cause a proper error; avoid tree
	     checking errors as well by setting a safe value.  */
	  எனில் (constructor_max_index
	      && மரம்_CODE (constructor_max_index) != INTEGER_CST)
	    constructor_max_index = integer_minus_one_முனை;

	  constructor_index
	    = convert (bitsizetype,
		       TYPE_MIN_மதிப்பு (TYPE_DOMAIN (constructor_type)));
	}
      இல்லையெனில்
	constructor_index = bitsize_zero_முனை;

      constructor_unfilled_index = constructor_index;
      எனில் (மதிப்பு && மரம்_CODE (மதிப்பு) == STRING_CST)
	{
	  /* We need to split the char/wchar array into individual
	     characters, so that we don't have to special case it
	     everywhere.  */
	  set_nonincremental_init_from_string (மதிப்பு, braced_init_obstack);
	}
    }
  இல்லையெனில்
    {
      எனில் (constructor_type != error_mark_முனை)
	{
	  எனில் (p->braced_scalar)
	    permerror_init (உள்ளீடு_location, 0,
			    "braces around scalar initializer");
	  இல்லையெனில்
	    warning_init (உள்ளீடு_location, 0,
			  "braces around scalar initializer");
	  constructor_braced_scalar = உண்மை;
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

கட்டமைப்பு c_கோவை
எடு_init_level (location_t loc, முழு implicit,
		கட்டமைப்பு obstack *braced_init_obstack,
		location_t செருகு_before)
{
  கட்டமைப்பு constructor_அடுக்கு *p;
  கட்டமைப்பு c_கோவை ret;
  ret.மதிப்பு = NULL_மரம்;
  ret.original_code = ERROR_MARK;
  ret.original_type = வெற்று;
  ret.m_decimal = 0;

  எனில் (implicit == 0)
    {
      /* When we come to an explicit close brace,
	 pop any inner levels that didn't have explicit braces.  */
      போது (constructor_அடுக்கு->implicit)
	process_init_element (உள்ளீடு_location,
			      எடு_init_level (loc, 1, braced_init_obstack,
					      செருகு_before),
			      உண்மை, braced_init_obstack);
      gcc_assert (!constructor_range_அடுக்கு);
    }
  இல்லையெனில்
    எனில் (initializer_அடுக்கு->missing_brace_richloc)
      initializer_அடுக்கு->missing_brace_richloc->add_fixit_செருகு_before
	(செருகு_before, "}");

  /* Now output all pending elements.  */
  constructor_incremental = 1;
  output_pending_init_elements (1, braced_init_obstack);

  p = constructor_அடுக்கு;

  /* Error for initializing a flexible array member.  */
  எனில் (constructor_type && constructor_fields
      && flexible_array_member_type_p (constructor_type))
    {
      /* Silently discard empty initializations.  The parser will
	 already have pedwarned for empty brackets for C17 and earlier.  */
      எனில் (integer_zerop (constructor_unfilled_index))
	constructor_type = NULL_மரம்;
      எனில் (constructor_type || flag_isoc23)
	{
	  gcc_assert (!constructor_type || !TYPE_SIZE (constructor_type));

	  எனில் (constructor_depth <= 2)
	    pedwarn_init (loc, OPT_Wpedantic,
			  "initialization of a flexible array member");
	  இல்லையெனில் எனில் (constructor_type)
	    error_init (loc, "initialization of flexible array member "
			     "in a nested context");
	  இல்லையெனில்
	    pedwarn_init (loc, OPT_Wpedantic,
			  "initialization of flexible array member "
			  "in a nested context");

	  /* We have already issued an error message for the existence
	     of a flexible array member not at the end of the structure.
	     Discard the initializer so that we do not die later.  */
	  எனில் (constructor_type
	      && DECL_CHAIN (constructor_fields) != NULL_மரம்
	      && (!p->type || மரம்_CODE (p->type) != UNION_TYPE))
	    constructor_type = NULL_மரம்;
	}
    }

  தேர்வு (vec_safe_length (constructor_elements))
    {
    நிலை 0:
      /* Initialization with { } counts as zeroinit.  */
      constructor_zeroinit = 1;
      நிறுத்து;
    நிலை 1:
      /* This might be zeroinit as well.  */
      எனில் (integer_zerop ((*constructor_elements)[0].மதிப்பு))
	constructor_zeroinit = 1;
      நிறுத்து;
    இயல்பு:
      /* If the constructor has more than one element, it can't be { 0 }.  */
      constructor_zeroinit = 0;
      நிறுத்து;
    }

  /* Warn when some structs are initialized with direct aggregation.  */
  எனில் (!implicit && found_missing_braces && warn_missing_braces
      && !constructor_zeroinit)
    {
      gcc_assert (initializer_அடுக்கு->missing_brace_richloc);
      warning_at (initializer_அடுக்கு->missing_brace_richloc,
		  OPT_Wmissing_braces,
		  "missing braces around initializer");
    }

  /* Warn when some struct elements are implicitly initialized to zero.  */
  எனில் (warn_missing_field_initializers
      && constructor_type
      && மரம்_CODE (constructor_type) == RECORD_TYPE
      && constructor_unfilled_fields)
    {
	/* Do not warn for flexible array members or zero-length arrays.  */
	போது (constructor_unfilled_fields
	       && (!DECL_SIZE (constructor_unfilled_fields)
		   || integer_zerop (DECL_SIZE (constructor_unfilled_fields))))
	  constructor_unfilled_fields = DECL_CHAIN (constructor_unfilled_fields);

	எனில் (constructor_unfilled_fields
	    /* Do not warn if this level of the initializer uses member
	       designators; it is likely to be deliberate.  */
	    && !constructor_designated
	    /* Do not warn about initializing with { 0 } or with { }.  */
	    && !constructor_zeroinit)
	  {
	    எனில் (warning_at (உள்ளீடு_location, OPT_Wmissing_field_initializers,
			    "missing initializer for field %qD of %qT",
			    constructor_unfilled_fields,
			    constructor_type))
	      inform (DECL_SOURCE_LOCATION (constructor_unfilled_fields),
		      "%qD declared here", constructor_unfilled_fields);
	  }
    }

  /* Pad out the end of the structure.  */
  எனில் (p->replacement_மதிப்பு.மதிப்பு)
    /* If this closes a superfluous brace pair,
       just pass out the element between them.  */
    ret = p->replacement_மதிப்பு;
  இல்லையெனில் எனில் (constructor_type == NULL_மரம்)
    ;
  இல்லையெனில் எனில் (!RECORD_OR_UNION_TYPE_P (constructor_type)
	   && மரம்_CODE (constructor_type) != ARRAY_TYPE
	   && !gnu_vector_type_p (constructor_type))
    {
      /* A nonincremental scalar initializer--just return
	 the element, after verifying there is just one.
         Empty scalar initializers are supported in C23.  */
      எனில் (vec_safe_is_empty (constructor_elements))
	{
	  எனில் (constructor_erroneous || constructor_type == error_mark_முனை)
	    ret.மதிப்பு = error_mark_முனை;
	  இல்லையெனில் எனில் (மரம்_CODE (constructor_type) == FUNCTION_TYPE)
	    {
	      error_init (loc, "invalid initializer");
	      ret.மதிப்பு = error_mark_முனை;
	    }
	  இல்லையெனில் எனில் (மரம்_CODE (constructor_type) == POINTER_TYPE)
	    /* Ensure this is a null pointer constant in the case of a
	       'constexpr' object initialized with {}.  */
	    ret.மதிப்பு = build_zero_cst (ptr_type_முனை);
	  இல்லையெனில்
	    ret.மதிப்பு = build_zero_cst (constructor_type);
	}
      இல்லையெனில் எனில் (vec_safe_length (constructor_elements) != 1)
	{
	  error_init (loc, "extra elements in scalar initializer");
	  ret.மதிப்பு = (*constructor_elements)[0].மதிப்பு;
	}
      இல்லையெனில்
	ret.மதிப்பு = (*constructor_elements)[0].மதிப்பு;
    }
  இல்லையெனில்
    {
      எனில் (constructor_erroneous)
	ret.மதிப்பு = error_mark_முனை;
      இல்லையெனில்
	{
	  ret.மதிப்பு = build_constructor (constructor_type,
					 constructor_elements);
	  எனில் (constructor_constant)
	    மரம்_CONSTANT (ret.மதிப்பு) = 1;
	  எனில் (constructor_constant && constructor_simple)
	    மரம்_STATIC (ret.மதிப்பு) = 1;
	  எனில் (constructor_nonconst)
	    CONSTRUCTOR_NON_CONST (ret.மதிப்பு) = 1;
	  எனில் (constructor_zero_padding_bits)
	    CONSTRUCTOR_ZERO_PADDING_BITS (ret.மதிப்பு) = 1;
	}
    }

  எனில் (ret.மதிப்பு && மரம்_CODE (ret.மதிப்பு) != CONSTRUCTOR)
    {
      எனில் (constructor_nonconst)
	ret.original_code = C_MAYBE_CONST_கோவை;
      இல்லையெனில் எனில் (ret.original_code == C_MAYBE_CONST_கோவை)
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
  எனில் (!p->implicit)
    constructor_range_அடுக்கு = p->range_அடுக்கு;
  RESTORE_SPELLING_DEPTH (constructor_depth);

  constructor_அடுக்கு = p->next;
  XDELETE (p);

  எனில் (ret.மதிப்பு == NULL_மரம் && constructor_அடுக்கு == 0)
    ret.மதிப்பு = error_mark_முனை;
  திரும்பு ret;
}

/* Common handling for both array range and field name designators.
   ARRAY argument is nonzero for array ranges.  Returns false for success.  */

நிலையான தருக்க
set_designator (location_t loc, தருக்க array,
		கட்டமைப்பு obstack *braced_init_obstack)
{
  மரம் subtype;
  எண்ணிக்கை மரம்_code subcode;

  /* Don't die if an entire brace-pair level is superfluous
     in the containing level, or for an erroneous type.  */
  எனில் (constructor_type == NULL_மரம் || constructor_type == error_mark_முனை)
    திரும்பு உண்மை;

  /* If there were errors in this designator list already, bail out
     silently.  */
  எனில் (designator_erroneous)
    திரும்பு உண்மை;

  /* Likewise for an initializer for a variable-size type.  Those are
     diagnosed in the parser, except for empty initializer braces.  */
  எனில் (COMPLETE_TYPE_P (constructor_type)
      && மரம்_CODE (TYPE_SIZE (constructor_type)) != INTEGER_CST)
    திரும்பு உண்மை;

  எனில் (!designator_depth)
    {
      gcc_assert (!constructor_range_அடுக்கு);

      /* Designator list starts at the level of closest explicit
	 braces.  */
      போது (constructor_அடுக்கு->implicit)
	process_init_element (உள்ளீடு_location,
			      எடு_init_level (loc, 1, braced_init_obstack,
					      last_init_list_comma),
			      உண்மை, braced_init_obstack);
      constructor_designated = 1;
      திரும்பு பொய்;
    }

  தேர்வு (மரம்_CODE (constructor_type))
    {
    நிலை  RECORD_TYPE:
    நிலை  UNION_TYPE:
      subtype = மரம்_TYPE (constructor_fields);
      எனில் (subtype != error_mark_முனை)
	subtype = TYPE_MAIN_VARIANT (subtype);
      நிறுத்து;
    நிலை ARRAY_TYPE:
      subtype = TYPE_MAIN_VARIANT (மரம்_TYPE (constructor_type));
      நிறுத்து;
    இயல்பு:
      gcc_unreachable ();
    }

  subcode = மரம்_CODE (subtype);
  எனில் (array && subcode != ARRAY_TYPE)
    {
      error_init (loc, "array index in non-array initializer");
      திரும்பு உண்மை;
    }
  இல்லையெனில் எனில் (!array && subcode != RECORD_TYPE && subcode != UNION_TYPE)
    {
      error_init (loc, "field name not in record or union initializer");
      திரும்பு உண்மை;
    }

  constructor_designated = 1;
  finish_implicit_inits (loc, braced_init_obstack);
  தள்ளு_init_level (loc, 2, braced_init_obstack);
  திரும்பு பொய்;
}

/* If there are range designators in designator list, push a new designator
   to constructor_range_stack.  RANGE_END is end of such stack range or
   NULL_TREE if there is no range designator at this level.  */

நிலையான வெறுமை
தள்ளு_range_அடுக்கு (மரம் range_end, கட்டமைப்பு obstack * braced_init_obstack)
{
  கட்டமைப்பு constructor_range_அடுக்கு *p;

  p = (கட்டமைப்பு constructor_range_அடுக்கு *)
    obstack_alloc (braced_init_obstack,
		   அளவு (கட்டமைப்பு constructor_range_அடுக்கு));
  p->prev = constructor_range_அடுக்கு;
  p->next = 0;
  p->fields = constructor_fields;
  p->range_start = constructor_index;
  p->index = constructor_index;
  p->அடுக்கு = constructor_அடுக்கு;
  p->range_end = range_end;
  எனில் (constructor_range_அடுக்கு)
    constructor_range_அடுக்கு->next = p;
  constructor_range_அடுக்கு = p;
}

/* Within an array initializer, specify the next index to be initialized.
   FIRST is that index.  If LAST is nonzero, then initialize a range
   of indices, running from FIRST through LAST.  */

வெறுமை
set_init_index (location_t loc, மரம் first, மரம் last,
		கட்டமைப்பு obstack *braced_init_obstack)
{
  எனில் (set_designator (loc, உண்மை, braced_init_obstack))
    திரும்பு;

  designator_erroneous = 1;

  எனில் (!INTEGRAL_TYPE_P (மரம்_TYPE (first))
      || (last && !INTEGRAL_TYPE_P (மரம்_TYPE (last))))
    {
      error_init (loc, "array index in initializer not of integer type");
      திரும்பு;
    }

  எனில் (மரம்_CODE (first) != INTEGER_CST)
    {
      first = c_fully_fold (first, பொய், வெற்று);
      எனில் (மரம்_CODE (first) == INTEGER_CST)
	pedwarn_init (loc, OPT_Wpedantic,
		      "array index in initializer is not "
		      "an integer constant expression");
    }

  எனில் (last && மரம்_CODE (last) != INTEGER_CST)
    {
      last = c_fully_fold (last, பொய், வெற்று);
      எனில் (மரம்_CODE (last) == INTEGER_CST)
	pedwarn_init (loc, OPT_Wpedantic,
		      "array index in initializer is not "
		      "an integer constant expression");
    }

  எனில் (மரம்_CODE (first) != INTEGER_CST)
    error_init (loc, "nonconstant array index in initializer");
  இல்லையெனில் எனில் (last != NULL_மரம் && மரம்_CODE (last) != INTEGER_CST)
    error_init (loc, "nonconstant array index in initializer");
  இல்லையெனில் எனில் (மரம்_CODE (constructor_type) != ARRAY_TYPE)
    error_init (loc, "array index in non-array initializer");
  இல்லையெனில் எனில் (மரம்_int_cst_sgn (first) == -1)
    error_init (loc, "array index in initializer exceeds array bounds");
  இல்லையெனில் எனில் (constructor_max_index
	   && மரம்_int_cst_lt (constructor_max_index, first))
    error_init (loc, "array index in initializer exceeds array bounds");
  இல்லையெனில்
    {
      constant_expression_warning (first);
      எனில் (last)
	constant_expression_warning (last);
      constructor_index = convert (bitsizetype, first);
      எனில் (மரம்_int_cst_lt (constructor_index, first))
	{
	  constructor_index = copy_முனை (constructor_index);
	  மரம்_OVERFLOW (constructor_index) = 1;
	}

      எனில் (last)
	{
	  எனில் (மரம்_int_cst_equal (first, last))
	    last = NULL_மரம்;
	  இல்லையெனில் எனில் (மரம்_int_cst_lt (last, first))
	    {
	      error_init (loc, "empty index range in initializer");
	      last = NULL_மரம்;
	    }
	  இல்லையெனில்
	    {
	      last = convert (bitsizetype, last);
	      எனில் (constructor_max_index != NULL_மரம்
		  && மரம்_int_cst_lt (constructor_max_index, last))
		{
		  error_init (loc, "array index range in initializer exceeds "
			      "array bounds");
		  last = NULL_மரம்;
		}
	    }
	}

      designator_depth++;
      designator_erroneous = 0;
      எனில் (constructor_range_அடுக்கு || last)
	தள்ளு_range_அடுக்கு (last, braced_init_obstack);
    }
}

/* Within a struct initializer, specify the next field to be initialized.  */

வெறுமை
set_init_label (location_t loc, மரம் fieldname, location_t fieldname_loc,
		கட்டமைப்பு obstack *braced_init_obstack)
{
  மரம் field;

  எனில் (set_designator (loc, பொய், braced_init_obstack))
    திரும்பு;

  designator_erroneous = 1;

  எனில் (!RECORD_OR_UNION_TYPE_P (constructor_type))
    {
      error_init (loc, "field name not in record or union initializer");
      திரும்பு;
    }

  field = lookup_field (constructor_type, fieldname);

  எனில் (field == NULL_மரம்)
    {
      மரம் guessed_id = lookup_field_fuzzy (constructor_type, fieldname);
      எனில் (guessed_id)
	{
	  gcc_rich_location rich_loc (fieldname_loc);
	  rich_loc.add_fixit_misspelled_id (fieldname_loc, guessed_id);
	  error_at (&rich_loc,
		    "%qT has no member named %qE; did you mean %qE?",
		    constructor_type, fieldname, guessed_id);
	}
      இல்லையெனில்
	error_at (fieldname_loc, "%qT has no member named %qE",
		  constructor_type, fieldname);
    }
  இல்லையெனில்
    செய்
      {
	constructor_fields = மரம்_மதிப்பு (field);
	designator_depth++;
	designator_erroneous = 0;
	எனில் (constructor_range_அடுக்கு)
	  தள்ளு_range_அடுக்கு (NULL_மரம், braced_init_obstack);
	field = மரம்_CHAIN (field);
	எனில் (field)
	  {
	    எனில் (set_designator (loc, பொய், braced_init_obstack))
	      திரும்பு;
	  }
      }
    போது (field != NULL_மரம்);
}

/* Helper function for add_pending_init.  Find inorder successor of P
   in AVL tree.  */
நிலையான கட்டமைப்பு init_முனை *
init_முனை_successor (கட்டமைப்பு init_முனை *p)
{
  கட்டமைப்பு init_முனை *r;
  எனில் (p->வலது)
    {
      r = p->வலது;
      போது (r->இடது)
	r = r->இடது;
      திரும்பு r;
    }
  r = p->parent;
  போது (r && p == r->வலது)
    {
      p = r;
      r = r->parent;
    }
  திரும்பு r;
}

/* Add a new initializer to the tree of pending initializers.  PURPOSE
   identifies the initializer, either array index or field in a structure.
   VALUE is the value of that index or field.  If ORIGTYPE is not
   NULL_TREE, it is the original type of VALUE.

   IMPLICIT is true if value comes from pop_init_level (1),
   the new initializer has been merged with the existing one
   and thus no warnings should be emitted about overriding an
   existing initializer.  */

நிலையான வெறுமை
add_pending_init (location_t loc, மரம் purpose, மரம் மதிப்பு, மரம் origtype,
		  தருக்க implicit, கட்டமைப்பு obstack *braced_init_obstack)
{
  கட்டமைப்பு init_முனை *p, **q, *r;

  q = &constructor_pending_elts;
  p = 0;

  எனில் (மரம்_CODE (constructor_type) == ARRAY_TYPE)
    {
      போது (*q != 0)
	{
	  p = *q;
	  எனில் (மரம்_int_cst_lt (purpose, p->purpose))
	    q = &p->இடது;
	  இல்லையெனில் எனில் (மரம்_int_cst_lt (p->purpose, purpose))
	    {
	      எனில் (மரம்_CODE (p->மதிப்பு) != RAW_DATA_CST
		  || (p->வலது
		      && மரம்_int_cst_le (p->வலது->purpose, purpose)))
		q = &p->வலது;
	      இல்லையெனில்
		{
		  widest_int pp = wi::to_widest (p->purpose);
		  widest_int pw = wi::to_widest (purpose);
		  எனில் (pp + RAW_DATA_LENGTH (p->மதிப்பு) <= pw)
		    q = &p->வலது;
		  இல்லையெனில்
		    {
		      /* Override which should split the old RAW_DATA_CST
			 into 2 or 3 pieces.  */
		      எனில் (!implicit && warn_override_init)
			warning_init (loc, OPT_Woverride_init,
				      "initialized field overwritten");
		      unsigned HOST_WIDE_INT start = (pw - pp).to_uhwi ();
		      unsigned HOST_WIDE_INT len = 1;
		      எனில் (மரம்_CODE (மதிப்பு) == RAW_DATA_CST)
			len = RAW_DATA_LENGTH (மதிப்பு);
		      unsigned HOST_WIDE_INT end = 0;
		      unsigned plen = RAW_DATA_LENGTH (p->மதிப்பு);
		      gcc_checking_assert (start < plen && start);
		      எனில் (plen - start > len)
			end = plen - start - len;
		      மரம் v = p->மதிப்பு;
		      மரம் origtype = p->origtype;
		      எனில் (start == 1)
			p->மதிப்பு = build_int_cst (மரம்_TYPE (v),
						  RAW_DATA_UCHAR_ELT (v, 0));
		      இல்லையெனில்
			{
			  p->மதிப்பு = v;
			  எனில் (end > 1)
			    v = copy_முனை (v);
			  RAW_DATA_LENGTH (p->மதிப்பு) = start;
			}
		      எனில் (end)
			{
			  மரம் epurpose
			    = size_binop (PLUS_கோவை, purpose,
					  bitsize_int (len));
			  எனில் (end > 1)
			    {
			      RAW_DATA_LENGTH (v) -= plen - end;
			      RAW_DATA_POINTER (v) += plen - end;
			    }
			  இல்லையெனில்
			    v = build_int_cst (மரம்_TYPE (v),
					       RAW_DATA_UCHAR_ELT (v, plen
								      - end));
			  add_pending_init (loc, epurpose, v, origtype,
					    implicit, braced_init_obstack);
			}
		      q = &constructor_pending_elts;
		      தொடர்;
		    }
		}
	    }
	  இல்லையெனில்
	    {
	      எனில் (மரம்_CODE (p->மதிப்பு) == RAW_DATA_CST
		  && (RAW_DATA_LENGTH (p->மதிப்பு)
		      > (மரம்_CODE (மதிப்பு) == RAW_DATA_CST
			 ? RAW_DATA_LENGTH (மதிப்பு) : 1)))
		{
		  /* Override which should split the old RAW_DATA_CST
		     into 2 pieces.  */
		  எனில் (!implicit && warn_override_init)
		    warning_init (loc, OPT_Woverride_init,
				  "initialized field overwritten");
		  unsigned HOST_WIDE_INT len = 1;
		  எனில் (மரம்_CODE (மதிப்பு) == RAW_DATA_CST)
		    len = RAW_DATA_LENGTH (மதிப்பு);
		  எனில் ((unsigned) RAW_DATA_LENGTH (p->மதிப்பு) > len + 1)
		    {
		      RAW_DATA_LENGTH (p->மதிப்பு) -= len;
		      RAW_DATA_POINTER (p->மதிப்பு) += len;
		    }
		  இல்லையெனில்
		    {
		      unsigned முழு l = RAW_DATA_LENGTH (p->மதிப்பு) - 1;
		      p->மதிப்பு
			= build_int_cst (மரம்_TYPE (p->மதிப்பு),
					 RAW_DATA_UCHAR_ELT (p->மதிப்பு, l));
		    }
		  p->purpose = size_binop (PLUS_கோவை, p->purpose,
					   bitsize_int (len));
		  தொடர்;
		}
	      எனில் (மரம்_CODE (மதிப்பு) == RAW_DATA_CST)
		{
		handle_raw_data:
		  /* RAW_DATA_CST value might overlap various further
		     prior initval entries.  Find out how many.  */
		  unsigned cnt = 0;
		  widest_int w
		    = wi::to_widest (purpose) + RAW_DATA_LENGTH (மதிப்பு);
		  கட்டமைப்பு init_முனை *r = p, *last = வெற்று;
		  தருக்க override_init = warn_override_init;
		  போது ((r = init_முனை_successor (r))
			 && wi::to_widest (r->purpose) < w)
		    {
		      ++cnt;
		      எனில் (மரம்_SIDE_EFFECTS (r->மதிப்பு))
			warning_init (loc, OPT_Woverride_init_side_effects,
				      "initialized field with side-effects "
				      "overwritten");
		      இல்லையெனில் எனில் (override_init)
			{
			  warning_init (loc, OPT_Woverride_init,
					"initialized field overwritten");
			  override_init = பொய்;
			}
		      last = r;
		    }
		  எனில் (cnt)
		    {
		      எனில் (மரம்_CODE (last->மதிப்பு) == RAW_DATA_CST
			  && (wi::to_widest (last->purpose)
			      + RAW_DATA_LENGTH (last->மதிப்பு) > w))
			{
			  /* The last overlapping prior initval overlaps
			     only partially.  Shrink it and decrease cnt.  */
			  unsigned முழு l = (wi::to_widest (last->purpose)
					    + RAW_DATA_LENGTH (last->மதிப்பு)
					    - w).to_uhwi ();
			  --cnt;
			  RAW_DATA_LENGTH (last->மதிப்பு) -= l;
			  RAW_DATA_POINTER (last->மதிப்பு) += l;
			  எனில் (RAW_DATA_LENGTH (last->மதிப்பு) == 1)
			    last->மதிப்பு
			      = build_int_cst (மரம்_TYPE (last->மதிப்பு),
					       RAW_DATA_UCHAR_ELT (last->மதிப்பு,
								   0));
			  last->purpose
			    = size_binop (PLUS_கோவை, last->purpose,
					  bitsize_int (l));
			}
		      /* Instead of deleting cnt nodes from the AVL tree
			 and rebalancing, peel of last cnt bytes from the
			 RAW_DATA_CST.  Overriding thousands of previously
			 initialized array elements with #embed needs to work,
			 but doesn't need to be super efficient.  */
		      gcc_checking_assert ((unsigned) RAW_DATA_LENGTH (மதிப்பு)
					   > cnt);
		      RAW_DATA_LENGTH (மதிப்பு) -= cnt;
		      மாறிலி unsigned எழுத்து *s
			= &RAW_DATA_UCHAR_ELT (மதிப்பு, RAW_DATA_LENGTH (மதிப்பு));
		      unsigned முழு o = RAW_DATA_LENGTH (மதிப்பு);
		      க்கு (r = p; cnt--; ++o, ++s)
			{
			  r = init_முனை_successor (r);
			  r->purpose = size_binop (PLUS_கோவை, purpose,
						   bitsize_int (o));
			  r->மதிப்பு = build_int_cst (மரம்_TYPE (மதிப்பு), *s);
			  r->origtype = origtype;
			}
		      எனில் (RAW_DATA_LENGTH (மதிப்பு) == 1)
			மதிப்பு = build_int_cst (மரம்_TYPE (மதிப்பு),
					       RAW_DATA_UCHAR_ELT (மதிப்பு, 0));
		    }
		}
	      எனில் (!implicit)
		{
		  எனில் (மரம்_SIDE_EFFECTS (p->மதிப்பு))
		    warning_init (loc, OPT_Woverride_init_side_effects,
				  "initialized field with side-effects "
				  "overwritten");
		  இல்லையெனில் எனில் (warn_override_init)
		    warning_init (loc, OPT_Woverride_init,
				  "initialized field overwritten");
		}
	      p->மதிப்பு = மதிப்பு;
	      p->origtype = origtype;
	      திரும்பு;
	    }
	}
      எனில் (மரம்_CODE (மதிப்பு) == RAW_DATA_CST && p)
	{
	  கட்டமைப்பு init_முனை *r;
	  எனில் (q == &p->இடது)
	    r = p;
	  இல்லையெனில்
	    r = init_முனை_successor (p);
	  எனில் (r && wi::to_widest (r->purpose) < (wi::to_widest (purpose)
						 + RAW_DATA_LENGTH (மதிப்பு)))
	    {
	      /* Overlap with at least one prior initval in the range but
		 not at the start.  */
	      p = r;
	      p->purpose = purpose;
	      செல் handle_raw_data;
	    }
	}
    }
  இல்லையெனில்
    {
      மரம் bitpos;

      bitpos = bit_position (purpose);
      போது (*q != வெற்று)
	{
	  p = *q;
	  எனில் (மரம்_int_cst_lt (bitpos, bit_position (p->purpose)))
	    q = &p->இடது;
	  இல்லையெனில் எனில் (p->purpose != purpose)
	    q = &p->வலது;
	  இல்லையெனில்
	    {
	      எனில் (!implicit)
		{
		  எனில் (மரம்_SIDE_EFFECTS (p->மதிப்பு))
		    warning_init (loc, OPT_Woverride_init_side_effects,
				  "initialized field with side-effects "
				  "overwritten");
		  இல்லையெனில் எனில் (warn_override_init)
		    warning_init (loc, OPT_Woverride_init,
				  "initialized field overwritten");
		}
	      p->மதிப்பு = மதிப்பு;
	      p->origtype = origtype;
	      திரும்பு;
	    }
	}
    }

  r = (கட்டமைப்பு init_முனை *) obstack_alloc (braced_init_obstack,
					  அளவு (கட்டமைப்பு init_முனை));
  r->purpose = purpose;
  r->மதிப்பு = மதிப்பு;
  r->origtype = origtype;

  *q = r;
  r->parent = p;
  r->இடது = 0;
  r->வலது = 0;
  r->balance = 0;

  போது (p)
    {
      கட்டமைப்பு init_முனை *s;

      எனில் (r == p->இடது)
	{
	  எனில் (p->balance == 0)
	    p->balance = -1;
	  இல்லையெனில் எனில் (p->balance < 0)
	    {
	      எனில் (r->balance < 0)
		{
		  /* L rotation.  */
		  p->இடது = r->வலது;
		  எனில் (p->இடது)
		    p->இடது->parent = p;
		  r->வலது = p;

		  p->balance = 0;
		  r->balance = 0;

		  s = p->parent;
		  p->parent = r;
		  r->parent = s;
		  எனில் (s)
		    {
		      எனில் (s->இடது == p)
			s->இடது = r;
		      இல்லையெனில்
			s->வலது = r;
		    }
		  இல்லையெனில்
		    constructor_pending_elts = r;
		}
	      இல்லையெனில்
		{
		  /* LR rotation.  */
		  கட்டமைப்பு init_முனை *t = r->வலது;

		  r->வலது = t->இடது;
		  எனில் (r->வலது)
		    r->வலது->parent = r;
		  t->இடது = r;

		  p->இடது = t->வலது;
		  எனில் (p->இடது)
		    p->இடது->parent = p;
		  t->வலது = p;

		  p->balance = t->balance < 0;
		  r->balance = -(t->balance > 0);
		  t->balance = 0;

		  s = p->parent;
		  p->parent = t;
		  r->parent = t;
		  t->parent = s;
		  எனில் (s)
		    {
		      எனில் (s->இடது == p)
			s->இடது = t;
		      இல்லையெனில்
			s->வலது = t;
		    }
		  இல்லையெனில்
		    constructor_pending_elts = t;
		}
	      நிறுத்து;
	    }
	  இல்லையெனில்
	    {
	      /* p->balance == +1; growth of left side balances the node.  */
	      p->balance = 0;
	      நிறுத்து;
	    }
	}
      இல்லையெனில் /* r == p->right */
	{
	  எனில் (p->balance == 0)
	    /* Growth propagation from right side.  */
	    p->balance++;
	  இல்லையெனில் எனில் (p->balance > 0)
	    {
	      எனில் (r->balance > 0)
		{
		  /* R rotation.  */
		  p->வலது = r->இடது;
		  எனில் (p->வலது)
		    p->வலது->parent = p;
		  r->இடது = p;

		  p->balance = 0;
		  r->balance = 0;

		  s = p->parent;
		  p->parent = r;
		  r->parent = s;
		  எனில் (s)
		    {
		      எனில் (s->இடது == p)
			s->இடது = r;
		      இல்லையெனில்
			s->வலது = r;
		    }
		  இல்லையெனில்
		    constructor_pending_elts = r;
		}
	      இல்லையெனில் /* r->balance == -1 */
		{
		  /* RL rotation */
		  கட்டமைப்பு init_முனை *t = r->இடது;

		  r->இடது = t->வலது;
		  எனில் (r->இடது)
		    r->இடது->parent = r;
		  t->வலது = r;

		  p->வலது = t->இடது;
		  எனில் (p->வலது)
		    p->வலது->parent = p;
		  t->இடது = p;

		  r->balance = (t->balance < 0);
		  p->balance = -(t->balance > 0);
		  t->balance = 0;

		  s = p->parent;
		  p->parent = t;
		  r->parent = t;
		  t->parent = s;
		  எனில் (s)
		    {
		      எனில் (s->இடது == p)
			s->இடது = t;
		      இல்லையெனில்
			s->வலது = t;
		    }
		  இல்லையெனில்
		    constructor_pending_elts = t;
		}
	      நிறுத்து;
	    }
	  இல்லையெனில்
	    {
	      /* p->balance == -1; growth of right side balances the node.  */
	      p->balance = 0;
	      நிறுத்து;
	    }
	}

      r = p;
      p = p->parent;
    }
}

/* Build AVL tree from a sorted chain.  */

நிலையான வெறுமை
set_nonincremental_init (கட்டமைப்பு obstack * braced_init_obstack)
{
  unsigned HOST_WIDE_INT ix;
  மரம் index, மதிப்பு;

  எனில் (மரம்_CODE (constructor_type) != RECORD_TYPE
      && மரம்_CODE (constructor_type) != ARRAY_TYPE)
    திரும்பு;

  FOR_EACH_CONSTRUCTOR_ELT (constructor_elements, ix, index, மதிப்பு)
    add_pending_init (உள்ளீடு_location, index, மதிப்பு, NULL_மரம், உண்மை,
		      braced_init_obstack);
  constructor_elements = வெற்று;
  எனில் (மரம்_CODE (constructor_type) == RECORD_TYPE)
    {
      constructor_unfilled_fields = TYPE_FIELDS (constructor_type);
      /* Skip any nameless bit fields at the beginning.  */
      போது (constructor_unfilled_fields != NULL_மரம்
	     && DECL_UNNAMED_BIT_FIELD (constructor_unfilled_fields))
	constructor_unfilled_fields = மரம்_CHAIN (constructor_unfilled_fields);

    }
  இல்லையெனில் எனில் (மரம்_CODE (constructor_type) == ARRAY_TYPE)
    {
      எனில் (TYPE_DOMAIN (constructor_type))
	constructor_unfilled_index
	  = convert (bitsizetype,
		     TYPE_MIN_மதிப்பு (TYPE_DOMAIN (constructor_type)));
      இல்லையெனில்
	constructor_unfilled_index = bitsize_zero_முனை;
    }
  constructor_incremental = 0;
}

/* Build AVL tree from a string constant.  */

நிலையான வெறுமை
set_nonincremental_init_from_string (மரம் str,
				     கட்டமைப்பு obstack * braced_init_obstack)
{
  மரம் மதிப்பு, purpose, type;
  HOST_WIDE_INT val[2];
  மாறிலி எழுத்து *p, *end;
  முழு byte, wchar_bytes, charwidth, bitpos;

  gcc_assert (மரம்_CODE (constructor_type) == ARRAY_TYPE);

  wchar_bytes = TYPE_PRECISION (மரம்_TYPE (மரம்_TYPE (str))) / BITS_PER_UNIT;
  charwidth = TYPE_PRECISION (char_type_முனை);
  gcc_assert ((size_t) wchar_bytes * charwidth
	      <= ARRAY_SIZE (val) * HOST_BITS_PER_WIDE_INT);
  type = மரம்_TYPE (constructor_type);
  p = மரம்_STRING_POINTER (str);
  end = p + மரம்_STRING_LENGTH (str);

  க்கு (purpose = bitsize_zero_முனை;
       p < end
       && !(constructor_max_index
	    && மரம்_int_cst_lt (constructor_max_index, purpose));
       purpose = size_binop (PLUS_கோவை, purpose, bitsize_one_முனை))
    {
      எனில் (wchar_bytes == 1)
	{
	  val[0] = (unsigned எழுத்து) *p++;
	  val[1] = 0;
	}
      இல்லையெனில்
	{
	  val[1] = 0;
	  val[0] = 0;
	  க்கு (byte = 0; byte < wchar_bytes; byte++)
	    {
	      எனில் (BYTES_BIG_ENDIAN)
		bitpos = (wchar_bytes - byte - 1) * charwidth;
	      இல்லையெனில்
		bitpos = byte * charwidth;
	      val[bitpos / HOST_BITS_PER_WIDE_INT]
		|= ((unsigned HOST_WIDE_INT) ((unsigned எழுத்து) *p++))
		   << (bitpos % HOST_BITS_PER_WIDE_INT);
	    }
	}

      எனில் (!TYPE_UNSIGNED (type))
	{
	  bitpos = ((wchar_bytes - 1) * charwidth) + HOST_BITS_PER_CHAR;
	  எனில் (bitpos < HOST_BITS_PER_WIDE_INT)
	    {
	      எனில் (val[0] & (HOST_WIDE_INT_1 << (bitpos - 1)))
		{
		  val[0] |= HOST_WIDE_INT_M1U << bitpos;
		  val[1] = -1;
		}
	    }
	  இல்லையெனில் எனில் (bitpos == HOST_BITS_PER_WIDE_INT)
	    {
	      எனில் (val[0] < 0)
		val[1] = -1;
	    }
	  இல்லையெனில் எனில் (val[1] & (HOST_WIDE_INT_1
			     << (bitpos - 1 - HOST_BITS_PER_WIDE_INT)))
	    val[1] |= HOST_WIDE_INT_M1U << (bitpos - HOST_BITS_PER_WIDE_INT);
	}

      மதிப்பு = wide_int_to_மரம் (type,
				wide_int::from_array (val, 2,
						      HOST_BITS_PER_WIDE_INT * 2));
      add_pending_init (உள்ளீடு_location, purpose, மதிப்பு, NULL_மரம், உண்மை,
                        braced_init_obstack);
    }

  constructor_incremental = 0;
}

/* Return value of FIELD in pending initializer or NULL_TREE if the field was
   not initialized yet.  */

நிலையான மரம்
find_init_member (மரம் field, கட்டமைப்பு obstack * braced_init_obstack)
{
  கட்டமைப்பு init_முனை *p;

  எனில் (மரம்_CODE (constructor_type) == ARRAY_TYPE)
    {
      எனில் (constructor_incremental
	  && மரம்_int_cst_lt (field, constructor_unfilled_index))
	set_nonincremental_init (braced_init_obstack);

      p = constructor_pending_elts;
      போது (p)
	{
	  எனில் (மரம்_int_cst_lt (field, p->purpose))
	    p = p->இடது;
	  இல்லையெனில் எனில் (மரம்_int_cst_lt (p->purpose, field))
	    p = p->வலது;
	  இல்லையெனில்
	    திரும்பு p->மதிப்பு;
	}
    }
  இல்லையெனில் எனில் (மரம்_CODE (constructor_type) == RECORD_TYPE)
    {
      மரம் bitpos = bit_position (field);

      எனில் (constructor_incremental
	  && (!constructor_unfilled_fields
	      || மரம்_int_cst_lt (bitpos,
				  bit_position (constructor_unfilled_fields))))
	set_nonincremental_init (braced_init_obstack);

      p = constructor_pending_elts;
      போது (p)
	{
	  எனில் (field == p->purpose)
	    திரும்பு p->மதிப்பு;
	  இல்லையெனில் எனில் (மரம்_int_cst_lt (bitpos, bit_position (p->purpose)))
	    p = p->இடது;
	  இல்லையெனில்
	    p = p->வலது;
	}
    }
  இல்லையெனில் எனில் (மரம்_CODE (constructor_type) == UNION_TYPE)
    {
      எனில் (!vec_safe_is_empty (constructor_elements)
	  && (constructor_elements->last ().index == field))
	திரும்பு constructor_elements->last ().மதிப்பு;
    }
  திரும்பு NULL_மரம்;
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

நிலையான வெறுமை
output_init_element (location_t loc, மரம் மதிப்பு, மரம் origtype,
		     தருக்க strict_string, மரம் type, மரம் field, தருக்க pending,
		     தருக்க implicit, கட்டமைப்பு obstack * braced_init_obstack)
{
  மரம் semantic_type = NULL_மரம்;
  தருக்க maybe_const = உண்மை;
  தருக்க npc, int_const_கோவை, arith_const_கோவை;

  எனில் (type == error_mark_முனை || மதிப்பு == error_mark_முனை)
    {
      constructor_erroneous = 1;
      திரும்பு;
    }
  எனில் (மரம்_CODE (மரம்_TYPE (மதிப்பு)) == ARRAY_TYPE
      && (மரம்_CODE (மதிப்பு) == STRING_CST
	  || மரம்_CODE (மதிப்பு) == COMPOUND_LITERAL_கோவை)
      && !(மரம்_CODE (மதிப்பு) == STRING_CST
	   && மரம்_CODE (type) == ARRAY_TYPE
	   && INTEGRAL_TYPE_P (மரம்_TYPE (type)))
      && !comptypes (TYPE_MAIN_VARIANT (மரம்_TYPE (மதிப்பு)),
		     TYPE_MAIN_VARIANT (type)))
    மதிப்பு = array_to_pointer_conversion (உள்ளீடு_location, மதிப்பு);

  எனில் (மரம்_CODE (மதிப்பு) == COMPOUND_LITERAL_கோவை
      && require_constant_மதிப்பு && pending)
    {
      /* As an extension, allow initializing objects with static storage
	 duration with compound literals (which are then treated just as
	 the brace enclosed list they contain).  */
      எனில் (flag_isoc99)
	pedwarn_init (loc, OPT_Wpedantic, "initializer element is not "
		      "constant");
      மரம் decl = COMPOUND_LITERAL_கோவை_DECL (மதிப்பு);
      மதிப்பு = DECL_INITIAL (decl);
    }

  npc = null_pointer_constant_p (மதிப்பு);
  int_const_கோவை = (மரம்_CODE (மதிப்பு) == INTEGER_CST
		    && !மரம்_OVERFLOW (மதிப்பு)
		    && INTEGRAL_TYPE_P (மரம்_TYPE (மதிப்பு)));
  /* Not fully determined before folding.  */
  arith_const_கோவை = உண்மை;
  எனில் (மரம்_CODE (மதிப்பு) == EXCESS_PRECISION_கோவை)
    {
      semantic_type = மரம்_TYPE (மதிப்பு);
      மதிப்பு = மரம்_OPERAND (மதிப்பு, 0);
    }
  மதிப்பு = c_fully_fold (மதிப்பு, require_constant_மதிப்பு, &maybe_const);
  /* TODO: this may not detect all cases of expressions folding to
     constants that are not arithmetic constant expressions.  */
  எனில் (!maybe_const)
    arith_const_கோவை = பொய்;
  இல்லையெனில் எனில் (!INTEGRAL_TYPE_P (மரம்_TYPE (மதிப்பு))
	   && மரம்_CODE (மரம்_TYPE (மதிப்பு)) != REAL_TYPE
	   && மரம்_CODE (மரம்_TYPE (மதிப்பு)) != COMPLEX_TYPE)
    arith_const_கோவை = பொய்;
  இல்லையெனில் எனில் (மரம்_CODE (மதிப்பு) != INTEGER_CST
	   && மரம்_CODE (மதிப்பு) != REAL_CST
	   && மரம்_CODE (மதிப்பு) != COMPLEX_CST
	   && மரம்_CODE (மதிப்பு) != RAW_DATA_CST)
    arith_const_கோவை = பொய்;
  இல்லையெனில் எனில் (மரம்_OVERFLOW (மதிப்பு))
    arith_const_கோவை = பொய்;

  எனில் (மதிப்பு == error_mark_முனை)
    constructor_erroneous = 1;
  இல்லையெனில் எனில் (!மரம்_CONSTANT (மதிப்பு))
    constructor_constant = 0;
  இல்லையெனில் எனில் (!initializer_constant_valid_p (மதிப்பு,
					  மரம்_TYPE (மதிப்பு),
					  AGGREGATE_TYPE_P (constructor_type)
					  && TYPE_REVERSE_STORAGE_ORDER
					     (constructor_type))
	   || (RECORD_OR_UNION_TYPE_P (constructor_type)
	       && DECL_C_BIT_FIELD (field)
	       && மரம்_CODE (மதிப்பு) != INTEGER_CST))
    constructor_simple = 0;
  எனில் (!maybe_const)
    constructor_nonconst = 1;

  /* Digest the initializer and issue any errors about incompatible
     types before issuing errors about non-constant initializers.  */
  மரம் new_மதிப்பு = மதிப்பு;
  எனில் (semantic_type)
    new_மதிப்பு = build1 (EXCESS_PRECISION_கோவை, semantic_type, மதிப்பு);
  /* In the case of braces around a scalar initializer, the result of
     this initializer processing goes through digest_init again at the
     outer level.  In the case of a constexpr initializer for a
     pointer, avoid converting a null pointer constant to something
     that is not a null pointer constant to avoid a spurious error
     from that second processing.  */
  எனில் (!require_constexpr_மதிப்பு
      || !npc
      || மரம்_CODE (constructor_type) != POINTER_TYPE)
    new_மதிப்பு = digest_init (loc,
			     RECORD_OR_UNION_TYPE_P (constructor_type)
			     ? field : constructor_fields
			     ? constructor_fields : constructor_decl,
			     type, new_மதிப்பு, origtype, npc,
			     int_const_கோவை, arith_const_கோவை, strict_string,
			     require_constant_மதிப்பு, require_constexpr_மதிப்பு);
  எனில் (new_மதிப்பு == error_mark_முனை)
    {
      constructor_erroneous = 1;
      திரும்பு;
    }
  எனில் (require_constant_மதிப்பு || require_constant_elements)
    constant_expression_warning (new_மதிப்பு);

  /* Proceed to check the constness of the original initializer.  */
  எனில் (!initializer_constant_valid_p (மதிப்பு, மரம்_TYPE (மதிப்பு)))
    {
      எனில் (require_constant_மதிப்பு)
	{
	  error_init (loc, "initializer element is not constant");
	  மதிப்பு = error_mark_முனை;
	}
      இல்லையெனில் எனில் (require_constant_elements)
	pedwarn (loc, OPT_Wpedantic,
		 "initializer element is not computable at load time");
    }
  இல்லையெனில் எனில் (!maybe_const
	   && (require_constant_மதிப்பு || require_constant_elements))
    pedwarn_init (loc, OPT_Wpedantic,
		  "initializer element is not a constant expression");
  /* digest_init has already carried out the additional checks
     required for 'constexpr' initializers (using the information
     passed to it about whether the original initializer was certain
     kinds of constant expression), so that check does not need to be
     repeated here.  */

  /* Issue -Wc++-compat warnings about initializing a bitfield with
     enum type.  */
  எனில் (warn_cxx_compat
      && field != NULL_மரம்
      && மரம்_CODE (field) == FIELD_DECL
      && DECL_BIT_FIELD_TYPE (field) != NULL_மரம்
      && (TYPE_MAIN_VARIANT (DECL_BIT_FIELD_TYPE (field))
	  != TYPE_MAIN_VARIANT (type))
      && மரம்_CODE (DECL_BIT_FIELD_TYPE (field)) == ENUMERAL_TYPE)
    {
      மரம் checktype = origtype != NULL_மரம் ? origtype : மரம்_TYPE (மதிப்பு);
      எனில் (checktype != error_mark_முனை
	  && (TYPE_MAIN_VARIANT (checktype)
	      != TYPE_MAIN_VARIANT (DECL_BIT_FIELD_TYPE (field))))
	warning_init (loc, OPT_Wc___compat,
		      "enum conversion in initialization is invalid in C++");
    }

  /* If this field is empty and does not have side effects (and is not at
     the end of structure), don't do anything other than checking the
     initializer.  */
  எனில் (field
      && (மரம்_TYPE (field) == error_mark_முனை
	  || (COMPLETE_TYPE_P (மரம்_TYPE (field))
	      && integer_zerop (TYPE_SIZE (மரம்_TYPE (field)))
	      && !மரம்_SIDE_EFFECTS (new_மதிப்பு)
	      && (மரம்_CODE (constructor_type) == ARRAY_TYPE
		  || DECL_CHAIN (field)))))
    திரும்பு;

  /* Finally, set VALUE to the initializer value digested above.  */
  மதிப்பு = new_மதிப்பு;

  /* If this element doesn't come next in sequence,
     put it on constructor_pending_elts.  */
  எனில் (மரம்_CODE (constructor_type) == ARRAY_TYPE
      && (!constructor_incremental
	  || !மரம்_int_cst_equal (field, constructor_unfilled_index)
	  || (மரம்_CODE (மதிப்பு) == RAW_DATA_CST
	      && constructor_pending_elts
	      && pending)))
    {
      எனில் (constructor_incremental
	  && (மரம்_int_cst_lt (field, constructor_unfilled_index)
	      || (மரம்_CODE (மதிப்பு) == RAW_DATA_CST
		  && constructor_pending_elts
		  && pending)))
	set_nonincremental_init (braced_init_obstack);

      add_pending_init (loc, field, மதிப்பு, origtype, implicit,
			braced_init_obstack);
      திரும்பு;
    }
  இல்லையெனில் எனில் (மரம்_CODE (constructor_type) == RECORD_TYPE
	   && (!constructor_incremental
	       || field != constructor_unfilled_fields))
    {
      /* We do this for records but not for unions.  In a union,
	 no matter which field is specified, it can be initialized
	 right away since it starts at the beginning of the union.  */
      எனில் (constructor_incremental)
	{
	  எனில் (!constructor_unfilled_fields)
	    set_nonincremental_init (braced_init_obstack);
	  இல்லையெனில்
	    {
	      மரம் bitpos, unfillpos;

	      bitpos = bit_position (field);
	      unfillpos = bit_position (constructor_unfilled_fields);

	      எனில் (மரம்_int_cst_lt (bitpos, unfillpos))
		set_nonincremental_init (braced_init_obstack);
	    }
	}

      add_pending_init (loc, field, மதிப்பு, origtype, implicit,
			braced_init_obstack);
      திரும்பு;
    }
  இல்லையெனில் எனில் (மரம்_CODE (constructor_type) == UNION_TYPE
	   && !vec_safe_is_empty (constructor_elements))
    {
      எனில் (!implicit)
	{
	  எனில் (மரம்_SIDE_EFFECTS (constructor_elements->last ().மதிப்பு))
	    warning_init (loc, OPT_Woverride_init_side_effects,
			  "initialized field with side-effects overwritten");
	  இல்லையெனில் எனில் (warn_override_init)
	    warning_init (loc, OPT_Woverride_init,
			  "initialized field overwritten");
	}

      /* We can have just one union field set.  */
      constructor_elements = வெற்று;
    }

  /* Otherwise, output this element either to
     constructor_elements or to the assembler file.  */

  constructor_elt celt = {field, மதிப்பு};
  vec_safe_தள்ளு (constructor_elements, celt);

  /* Advance the variable that indicates sequential elements output.  */
  எனில் (மரம்_CODE (constructor_type) == ARRAY_TYPE)
    {
      மரம் inc = bitsize_one_முனை;
      எனில் (மதிப்பு && மரம்_CODE (மதிப்பு) == RAW_DATA_CST)
	inc = bitsize_int (RAW_DATA_LENGTH (மதிப்பு));
      constructor_unfilled_index
	= size_binop_loc (உள்ளீடு_location, PLUS_கோவை,
			  constructor_unfilled_index, inc);
    }
  இல்லையெனில் எனில் (மரம்_CODE (constructor_type) == RECORD_TYPE)
    {
      constructor_unfilled_fields
	= DECL_CHAIN (constructor_unfilled_fields);

      /* Skip any nameless bit fields.  */
      போது (constructor_unfilled_fields != NULL_மரம்
	     && DECL_UNNAMED_BIT_FIELD (constructor_unfilled_fields))
	constructor_unfilled_fields
	  = DECL_CHAIN (constructor_unfilled_fields);
    }
  இல்லையெனில் எனில் (மரம்_CODE (constructor_type) == UNION_TYPE)
    constructor_unfilled_fields = NULL_மரம்;

  /* Now output any pending elements which have become next.  */
  எனில் (pending)
    output_pending_init_elements (0, braced_init_obstack);
}

/* For two FIELD_DECLs in the same chain, return -1 if field1
   comes before field2, 1 if field1 comes after field2 and
   0 if field1 == field2.  */

நிலையான முழு
init_field_decl_cmp (மரம் field1, மரம் field2)
{
  எனில் (field1 == field2)
    திரும்பு 0;

  மரம் bitpos1 = bit_position (field1);
  மரம் bitpos2 = bit_position (field2);
  எனில் (மரம்_int_cst_equal (bitpos1, bitpos2))
    {
      /* If one of the fields has non-zero bitsize, then that
	 field must be the last one in a sequence of zero
	 sized fields, fields after it will have bigger
	 bit_position.  */
      எனில் (மரம்_TYPE (field1) != error_mark_முனை
	  && COMPLETE_TYPE_P (மரம்_TYPE (field1))
	  && integer_nonzerop (மரம்_TYPE (field1)))
	திரும்பு 1;
      எனில் (மரம்_TYPE (field2) != error_mark_முனை
	  && COMPLETE_TYPE_P (மரம்_TYPE (field2))
	  && integer_nonzerop (மரம்_TYPE (field2)))
	திரும்பு -1;
      /* Otherwise, fallback to DECL_CHAIN walk to find out
	 which field comes earlier.  Walk chains of both
	 fields, so that if field1 and field2 are close to each
	 other in either order, it is found soon even for large
	 sequences of zero sized fields.  */
      மரம் f1 = field1, f2 = field2;
      போது (1)
	{
	  f1 = DECL_CHAIN (f1);
	  f2 = DECL_CHAIN (f2);
	  எனில் (f1 == NULL_மரம்)
	    {
	      gcc_assert (f2);
	      திரும்பு 1;
	    }
	  எனில் (f2 == NULL_மரம்)
	    திரும்பு -1;
	  எனில் (f1 == field2)
	    திரும்பு -1;
	  எனில் (f2 == field1)
	    திரும்பு 1;
	  எனில் (!மரம்_int_cst_equal (bit_position (f1), bitpos1))
	    திரும்பு 1;
	  எனில் (!மரம்_int_cst_equal (bit_position (f2), bitpos1))
	    திரும்பு -1;
	}
    }
  இல்லையெனில் எனில் (மரம்_int_cst_lt (bitpos1, bitpos2))
    திரும்பு -1;
  இல்லையெனில்
    திரும்பு 1;
}

/* Output any pending elements which have become next.
   As we output elements, constructor_unfilled_{fields,index}
   advances, which may cause other elements to become next;
   if so, they too are output.

   If ALL is 0, we return when there are
   no more pending elements to output now.

   If ALL is 1, we output space as necessary so that
   we can output all the pending elements.  */
நிலையான வெறுமை
output_pending_init_elements (முழு all, கட்டமைப்பு obstack * braced_init_obstack)
{
  கட்டமைப்பு init_முனை *elt = constructor_pending_elts;
  மரம் next;

 retry:

  /* Look through the whole pending tree.
     If we find an element that should be output now,
     output it.  Otherwise, set NEXT to the element
     that comes first among those still pending.  */

  next = NULL_மரம்;
  போது (elt)
    {
      எனில் (மரம்_CODE (constructor_type) == ARRAY_TYPE)
	{
	  எனில் (மரம்_int_cst_equal (elt->purpose,
				  constructor_unfilled_index))
	    output_init_element (உள்ளீடு_location, elt->மதிப்பு, elt->origtype,
				 உண்மை, மரம்_TYPE (constructor_type),
				 constructor_unfilled_index, பொய், பொய்,
				 braced_init_obstack);
	  இல்லையெனில் எனில் (மரம்_int_cst_lt (constructor_unfilled_index,
				    elt->purpose))
	    {
	      /* Advance to the next smaller node.  */
	      எனில் (elt->இடது)
		elt = elt->இடது;
	      இல்லையெனில்
		{
		  /* We have reached the smallest node bigger than the
		     current unfilled index.  Fill the space first.  */
		  next = elt->purpose;
		  நிறுத்து;
		}
	    }
	  இல்லையெனில்
	    {
	      /* Advance to the next bigger node.  */
	      எனில் (elt->வலது)
		elt = elt->வலது;
	      இல்லையெனில்
		{
		  /* We have reached the biggest node in a subtree.  Find
		     the parent of it, which is the next bigger node.  */
		  போது (elt->parent && elt->parent->வலது == elt)
		    elt = elt->parent;
		  elt = elt->parent;
		  எனில் (elt && மரம்_int_cst_lt (constructor_unfilled_index,
					      elt->purpose))
		    {
		      next = elt->purpose;
		      நிறுத்து;
		    }
		}
	    }
	}
      இல்லையெனில் எனில் (RECORD_OR_UNION_TYPE_P (constructor_type))
	{
	  /* If the current record is complete we are done.  */
	  எனில் (constructor_unfilled_fields == NULL_மரம்)
	    நிறுத்து;

	  முழு cmp = init_field_decl_cmp (constructor_unfilled_fields,
					 elt->purpose);
	  எனில் (cmp == 0)
	    output_init_element (உள்ளீடு_location, elt->மதிப்பு, elt->origtype,
				 உண்மை, மரம்_TYPE (elt->purpose),
				 elt->purpose, பொய், பொய்,
				 braced_init_obstack);
	  இல்லையெனில் எனில் (cmp < 0)
	    {
	      /* Advance to the next smaller node.  */
	      எனில் (elt->இடது)
		elt = elt->இடது;
	      இல்லையெனில்
		{
		  /* We have reached the smallest node bigger than the
		     current unfilled field.  Fill the space first.  */
		  next = elt->purpose;
		  நிறுத்து;
		}
	    }
	  இல்லையெனில்
	    {
	      /* Advance to the next bigger node.  */
	      எனில் (elt->வலது)
		elt = elt->வலது;
	      இல்லையெனில்
		{
		  /* We have reached the biggest node in a subtree.  Find
		     the parent of it, which is the next bigger node.  */
		  போது (elt->parent && elt->parent->வலது == elt)
		    elt = elt->parent;
		  elt = elt->parent;
		  எனில் (elt
		      && init_field_decl_cmp (constructor_unfilled_fields,
					      elt->purpose) < 0)
		    {
		      next = elt->purpose;
		      நிறுத்து;
		    }
		}
	    }
	}
    }

  /* Ordinarily return, but not if we want to output all
     and there are elements left.  */
  எனில் (!(all && next != NULL_மரம்))
    திரும்பு;

  /* If it's not incremental, just skip over the gap, so that after
     jumping to retry we will output the next successive element.  */
  எனில் (RECORD_OR_UNION_TYPE_P (constructor_type))
    constructor_unfilled_fields = next;
  இல்லையெனில் எனில் (மரம்_CODE (constructor_type) == ARRAY_TYPE)
    constructor_unfilled_index = next;

  /* ELT now points to the node in the pending tree with the next
     initializer to output.  */
  செல் retry;
}

/* Expression VALUE coincides with the start of type TYPE in a braced
   initializer.  Return true if we should treat VALUE as initializing
   the first element of TYPE, false if we should treat it as initializing
   TYPE as a whole.

   If the initializer is clearly invalid, the question becomes:
   which choice gives the best error message?  */

நிலையான தருக்க
initialize_elementwise_p (மரம் type, மரம் மதிப்பு)
{
  எனில் (type == error_mark_முனை || மதிப்பு == error_mark_முனை)
    திரும்பு பொய்;

  gcc_checking_assert (TYPE_MAIN_VARIANT (type) == type);

  மரம் மதிப்பு_type = மரம்_TYPE (மதிப்பு);
  எனில் (மதிப்பு_type == error_mark_முனை)
    திரும்பு பொய்;

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
  எனில் (gnu_vector_type_p (type))
    திரும்பு !VECTOR_TYPE_P (மதிப்பு_type);

  எனில் (AGGREGATE_TYPE_P (type))
    திரும்பு !comptypes (type, TYPE_MAIN_VARIANT (மதிப்பு_type));

  திரும்பு பொய்;
}

/* Helper function for process_init_element.  Split first element of
   RAW_DATA_CST and save the rest to *RAW_DATA.  */

நிலையான உள்வரி மரம்
maybe_split_raw_data (மரம் மதிப்பு, மரம் *raw_data)
{
  எனில் (மதிப்பு == NULL_மரம் || மரம்_CODE (மதிப்பு) != RAW_DATA_CST)
    திரும்பு மதிப்பு;
  *raw_data = மதிப்பு;
  மதிப்பு = build_int_cst (integer_type_முனை,
			 RAW_DATA_UCHAR_ELT (*raw_data, 0));
  ++RAW_DATA_POINTER (*raw_data);
  --RAW_DATA_LENGTH (*raw_data);
  திரும்பு மதிப்பு;
}

/* Return non-zero if c_parser_initval should attempt to optimize
   large initializers into RAW_DATA_CST.  In that case return how
   many elements to optimize at most.  */

unsigned
c_maybe_optimize_large_byte_initializer (வெறுமை)
{
  எனில் (!constructor_type
      || மரம்_CODE (constructor_type) != ARRAY_TYPE
      || constructor_அடுக்கு->implicit)
    திரும்பு 0;
  மரம் elttype = TYPE_MAIN_VARIANT (மரம்_TYPE (constructor_type));
  எனில் (மரம்_CODE (elttype) != INTEGER_TYPE
      && மரம்_CODE (elttype) != BITINT_TYPE)
    திரும்பு 0;
  எனில் (TYPE_PRECISION (elttype) != CHAR_BIT
      || constructor_அடுக்கு->replacement_மதிப்பு.மதிப்பு
      || (COMPLETE_TYPE_P (constructor_type)
	  && !poly_int_மரம்_p (TYPE_SIZE (constructor_type)))
      || constructor_range_அடுக்கு)
    திரும்பு 0;
  எனில் (constructor_max_index == NULL_மரம்)
    திரும்பு INT_MAX;
  எனில் (மரம்_int_cst_le (constructor_max_index, constructor_index)
      || integer_all_onesp (constructor_max_index))
    திரும்பு 0;
  widest_int w = wi::to_widest (constructor_max_index);
  w -= wi::to_widest (constructor_index);
  w += 1;
  எனில் (w < 64)
    திரும்பு 0;
  எனில் (w > INT_MAX)
    திரும்பு INT_MAX;
  திரும்பு w.to_uhwi ();
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

வெறுமை
process_init_element (location_t loc, கட்டமைப்பு c_கோவை மதிப்பு, தருக்க implicit,
		      கட்டமைப்பு obstack * braced_init_obstack)
{
  மரம் orig_மதிப்பு = மதிப்பு.மதிப்பு;
  முழு string_flag
    = (orig_மதிப்பு != NULL_மரம் && மரம்_CODE (orig_மதிப்பு) == STRING_CST);
  தருக்க strict_string = மதிப்பு.original_code == STRING_CST;
  தருக்க was_designated = designator_depth != 0;
  மரம் raw_data = NULL_மரம்;

retry:
  designator_depth = 0;
  designator_erroneous = 0;

  எனில் (!implicit && மதிப்பு.மதிப்பு && !integer_zerop (மதிப்பு.மதிப்பு))
    constructor_zeroinit = 0;

  /* Handle superfluous braces around string cst as in
     char x[] = {"foo"}; */
  எனில் (constructor_type
      && !was_designated
      && மரம்_CODE (constructor_type) == ARRAY_TYPE
      && INTEGRAL_TYPE_P (மரம்_TYPE (constructor_type))
      && integer_zerop (constructor_unfilled_index))
    {
      எனில் (constructor_அடுக்கு->replacement_மதிப்பு.மதிப்பு)
	{
	  error_init (loc, "excess elements in %qT initializer", constructor_type);
	  திரும்பு;
	}
      இல்லையெனில் எனில் (string_flag)
	{
	  constructor_அடுக்கு->replacement_மதிப்பு = மதிப்பு;
	  திரும்பு;
	}
    }

  எனில் (constructor_அடுக்கு->replacement_மதிப்பு.மதிப்பு != NULL_மரம்)
    {
      error_init (loc, "excess elements in struct initializer");
      திரும்பு;
    }

  /* Ignore elements of a brace group if it is entirely superfluous
     and has already been diagnosed, or if the type is erroneous.  */
  எனில் (constructor_type == NULL_மரம் || constructor_type == error_mark_முனை)
    திரும்பு;

  /* Ignore elements of an initializer for a variable-size type.
     Those are diagnosed in the parser (empty initializer braces are OK).  */
  எனில் (COMPLETE_TYPE_P (constructor_type)
      && !poly_int_மரம்_p (TYPE_SIZE (constructor_type)))
    திரும்பு;

  எனில் (!implicit && warn_designated_init && !was_designated
      && மரம்_CODE (constructor_type) == RECORD_TYPE
      && lookup_attribute ("designated_init",
			   TYPE_ATTRIBUTES (constructor_type)))
    warning_init (loc,
		  OPT_Wdesignated_init,
		  "positional initialization of field "
		  "in %<struct%> declared with %<designated_init%> attribute");

  /* If we've exhausted any levels that didn't have braces,
     pop them now.  */
  போது (constructor_அடுக்கு->implicit)
    {
      எனில் (RECORD_OR_UNION_TYPE_P (constructor_type)
	  && constructor_fields == NULL_மரம்)
	process_init_element (loc,
			      எடு_init_level (loc, 1, braced_init_obstack,
					      last_init_list_comma),
			      உண்மை, braced_init_obstack);
      இல்லையெனில் எனில் ((மரம்_CODE (constructor_type) == ARRAY_TYPE
		|| gnu_vector_type_p (constructor_type))
	       && constructor_max_index
	       && மரம்_int_cst_lt (constructor_max_index,
				   constructor_index))
	process_init_element (loc,
			      எடு_init_level (loc, 1, braced_init_obstack,
					      last_init_list_comma),
			      உண்மை, braced_init_obstack);
      இல்லையெனில்
	நிறுத்து;
    }

  /* In the case of [LO ... HI] = VALUE, only evaluate VALUE once.  */
  எனில் (constructor_range_அடுக்கு)
    {
      /* If value is a compound literal and we'll be just using its
	 content, don't put it into a SAVE_EXPR.  */
      எனில் (மரம்_CODE (மதிப்பு.மதிப்பு) != COMPOUND_LITERAL_கோவை
	  || !require_constant_மதிப்பு)
	{
	  மரம் semantic_type = NULL_மரம்;
	  எனில் (மரம்_CODE (மதிப்பு.மதிப்பு) == EXCESS_PRECISION_கோவை)
	    {
	      semantic_type = மரம்_TYPE (மதிப்பு.மதிப்பு);
	      மதிப்பு.மதிப்பு = மரம்_OPERAND (மதிப்பு.மதிப்பு, 0);
	    }
	  மதிப்பு.மதிப்பு = save_கோவை (மதிப்பு.மதிப்பு);
	  எனில் (semantic_type)
	    மதிப்பு.மதிப்பு = build1 (EXCESS_PRECISION_கோவை, semantic_type,
				  மதிப்பு.மதிப்பு);
	}
    }

  போது (1)
    {
      எனில் (மரம்_CODE (constructor_type) == RECORD_TYPE)
	{
	  மரம் fieldtype;
	  எண்ணிக்கை மரம்_code fieldcode;

	  எனில் (constructor_fields == NULL_மரம்)
	    {
	      pedwarn_init (loc, 0, "excess elements in struct initializer");
	      நிறுத்து;
	    }

	  fieldtype = மரம்_TYPE (constructor_fields);
	  எனில் (fieldtype != error_mark_முனை)
	    fieldtype = TYPE_MAIN_VARIANT (fieldtype);
	  fieldcode = மரம்_CODE (fieldtype);

	  /* Error for non-static initialization of a flexible array member.  */
	  எனில் (fieldcode == ARRAY_TYPE
	      && !require_constant_மதிப்பு
	      && TYPE_SIZE (fieldtype) == NULL_மரம்
	      && DECL_CHAIN (constructor_fields) == NULL_மரம்)
	    {
	      error_init (loc, "non-static initialization of a flexible "
			  "array member");
	      நிறுத்து;
	    }

	  /* Error for initialization of a flexible array member with
	     a string constant if the structure is in an array.  E.g.:
	     struct S { int x; char y[]; };
	     struct S s[] = { { 1, "foo" } };
	     is invalid.  */
	  எனில் (string_flag
	      && fieldcode == ARRAY_TYPE
	      && constructor_depth > 1
	      && TYPE_SIZE (fieldtype) == NULL_மரம்
	      && DECL_CHAIN (constructor_fields) == NULL_மரம்)
	    {
	      தருக்க in_array_p = பொய்;
	      க்கு (கட்டமைப்பு constructor_அடுக்கு *p = constructor_அடுக்கு;
		   p && p->type; p = p->next)
		எனில் (மரம்_CODE (p->type) == ARRAY_TYPE)
		  {
		    in_array_p = உண்மை;
		    நிறுத்து;
		  }
	      எனில் (in_array_p)
		{
		  error_init (loc, "initialization of flexible array "
			      "member in a nested context");
		  நிறுத்து;
		}
	    }

	  /* Accept a string constant to initialize a subarray.  */
	  எனில் (மதிப்பு.மதிப்பு != NULL_மரம்
	      && fieldcode == ARRAY_TYPE
	      && INTEGRAL_TYPE_P (மரம்_TYPE (fieldtype))
	      && string_flag)
	    மதிப்பு.மதிப்பு = orig_மதிப்பு;
	  /* Otherwise, if we have come to a subaggregate,
	     and we don't have an element of its type, push into it.  */
	  இல்லையெனில் எனில் (மதிப்பு.மதிப்பு != NULL_மரம்
		   && initialize_elementwise_p (fieldtype, மதிப்பு.மதிப்பு))
	    {
	      தள்ளு_init_level (loc, 1, braced_init_obstack);
	      தொடர்;
	    }

	  மதிப்பு.மதிப்பு = maybe_split_raw_data (மதிப்பு.மதிப்பு, &raw_data);
	  எனில் (மதிப்பு.மதிப்பு)
	    {
	      தள்ளு_member_name (constructor_fields);
	      output_init_element (loc, மதிப்பு.மதிப்பு, மதிப்பு.original_type,
				   strict_string, fieldtype,
				   constructor_fields, உண்மை, implicit,
				   braced_init_obstack);
	      RESTORE_SPELLING_DEPTH (constructor_depth);
	    }
	  இல்லையெனில்
	    /* Do the bookkeeping for an element that was
	       directly output as a constructor.  */
	    {
	      /* For a record, keep track of end position of last field.  */
	      எனில் (DECL_SIZE (constructor_fields))
		constructor_bit_index
		  = size_binop_loc (உள்ளீடு_location, PLUS_கோவை,
				    bit_position (constructor_fields),
				    DECL_SIZE (constructor_fields));

	      /* If the current field was the first one not yet written out,
		 it isn't now, so update.  */
	      எனில் (constructor_unfilled_fields == constructor_fields)
		{
		  constructor_unfilled_fields = DECL_CHAIN (constructor_fields);
		  /* Skip any nameless bit fields.  */
		  போது (constructor_unfilled_fields != 0
			 && (DECL_UNNAMED_BIT_FIELD
			     (constructor_unfilled_fields)))
		    constructor_unfilled_fields =
		      DECL_CHAIN (constructor_unfilled_fields);
		}
	    }

	  constructor_fields = DECL_CHAIN (constructor_fields);
	  /* Skip any nameless bit fields at the beginning.  */
	  போது (constructor_fields != NULL_மரம்
		 && DECL_UNNAMED_BIT_FIELD (constructor_fields))
	    constructor_fields = DECL_CHAIN (constructor_fields);
	}
      இல்லையெனில் எனில் (மரம்_CODE (constructor_type) == UNION_TYPE)
	{
	  மரம் fieldtype;
	  எண்ணிக்கை மரம்_code fieldcode;

	  எனில் (constructor_fields == NULL_மரம்)
	    {
	      pedwarn_init (loc, 0,
			    "excess elements in union initializer");
	      நிறுத்து;
	    }

	  fieldtype = மரம்_TYPE (constructor_fields);
	  எனில் (fieldtype != error_mark_முனை)
	    fieldtype = TYPE_MAIN_VARIANT (fieldtype);
	  fieldcode = மரம்_CODE (fieldtype);

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
	  எனில் (!in_system_header_at (உள்ளீடு_location) && !constructor_designated
	      && !(மதிப்பு.மதிப்பு && (integer_zerop (மதிப்பு.மதிப்பு)
				   || real_zerop (மதிப்பு.மதிப்பு))))
	    warning (OPT_Wtraditional, "traditional C rejects initialization "
		     "of unions");

	  /* Error for non-static initialization of a flexible array member.  */
	  எனில் (fieldcode == ARRAY_TYPE
	      && !require_constant_மதிப்பு
	      && TYPE_SIZE (fieldtype) == NULL_மரம்)
	    {
	      error_init (loc, "non-static initialization of a flexible "
			  "array member");
	      நிறுத்து;
	    }

	  /* Error for initialization of a flexible array member with
	     a string constant if the structure is in an array.  E.g.:
	     union U { int x; char y[]; };
	     union U s[] = { { 1, "foo" } };
	     is invalid.  */
	  எனில் (string_flag
	      && fieldcode == ARRAY_TYPE
	      && constructor_depth > 1
	      && TYPE_SIZE (fieldtype) == NULL_மரம்)
	    {
	      தருக்க in_array_p = பொய்;
	      க்கு (கட்டமைப்பு constructor_அடுக்கு *p = constructor_அடுக்கு;
		   p && p->type; p = p->next)
		எனில் (மரம்_CODE (p->type) == ARRAY_TYPE)
		  {
		    in_array_p = உண்மை;
		    நிறுத்து;
		  }
	      எனில் (in_array_p)
		{
		  error_init (loc, "initialization of flexible array "
			      "member in a nested context");
		  நிறுத்து;
		}
	    }

	  /* Accept a string constant to initialize a subarray.  */
	  எனில் (மதிப்பு.மதிப்பு != NULL_மரம்
	      && fieldcode == ARRAY_TYPE
	      && INTEGRAL_TYPE_P (மரம்_TYPE (fieldtype))
	      && string_flag)
	    மதிப்பு.மதிப்பு = orig_மதிப்பு;
	  /* Otherwise, if we have come to a subaggregate,
	     and we don't have an element of its type, push into it.  */
	  இல்லையெனில் எனில் (மதிப்பு.மதிப்பு != NULL_மரம்
		   && initialize_elementwise_p (fieldtype, மதிப்பு.மதிப்பு))
	    {
	      தள்ளு_init_level (loc, 1, braced_init_obstack);
	      தொடர்;
	    }

	  மதிப்பு.மதிப்பு = maybe_split_raw_data (மதிப்பு.மதிப்பு, &raw_data);
	  எனில் (மதிப்பு.மதிப்பு)
	    {
	      தள்ளு_member_name (constructor_fields);
	      output_init_element (loc, மதிப்பு.மதிப்பு, மதிப்பு.original_type,
				   strict_string, fieldtype,
				   constructor_fields, உண்மை, implicit,
				   braced_init_obstack);
	      RESTORE_SPELLING_DEPTH (constructor_depth);
	    }
	  இல்லையெனில்
	    /* Do the bookkeeping for an element that was
	       directly output as a constructor.  */
	    {
	      constructor_bit_index = DECL_SIZE (constructor_fields);
	      constructor_unfilled_fields = DECL_CHAIN (constructor_fields);
	    }

	  constructor_fields = NULL_மரம்;
	}
      இல்லையெனில் எனில் (மரம்_CODE (constructor_type) == ARRAY_TYPE)
	{
	  மரம் elttype = TYPE_MAIN_VARIANT (மரம்_TYPE (constructor_type));
	  எண்ணிக்கை மரம்_code eltcode = மரம்_CODE (elttype);

	  /* Accept a string constant to initialize a subarray.  */
	  எனில் (மதிப்பு.மதிப்பு != NULL_மரம்
	      && eltcode == ARRAY_TYPE
	      && INTEGRAL_TYPE_P (மரம்_TYPE (elttype))
	      && string_flag)
	    மதிப்பு.மதிப்பு = orig_மதிப்பு;
	  /* Otherwise, if we have come to a subaggregate,
	     and we don't have an element of its type, push into it.  */
	  இல்லையெனில் எனில் (மதிப்பு.மதிப்பு != NULL_மரம்
		   && initialize_elementwise_p (elttype, மதிப்பு.மதிப்பு))
	    {
	      தள்ளு_init_level (loc, 1, braced_init_obstack);
	      தொடர்;
	    }

	  எனில் (constructor_max_index != NULL_மரம்
	      && (மரம்_int_cst_lt (constructor_max_index, constructor_index)
		  || integer_all_onesp (constructor_max_index))
	      /* For VLA we got an error already.  */
	      && !C_TYPE_VARIABLE_SIZE (constructor_type))
	    {
	      pedwarn_init (loc, 0,
			    "excess elements in array initializer");
	      நிறுத்து;
	    }

	  எனில் (மதிப்பு.மதிப்பு
	      && மரம்_CODE (மதிப்பு.மதிப்பு) == RAW_DATA_CST
	      && RAW_DATA_LENGTH (மதிப்பு.மதிப்பு) > 1
	      && (மரம்_CODE (elttype) == INTEGER_TYPE
		  || மரம்_CODE (elttype) == BITINT_TYPE)
	      && TYPE_PRECISION (elttype) == CHAR_BIT
	      && (constructor_max_index == NULL_மரம்
		  || மரம்_int_cst_lt (constructor_index,
				      constructor_max_index)))
	    {
	      unsigned முழு len = RAW_DATA_LENGTH (மதிப்பு.மதிப்பு);
	      எனில் (constructor_max_index)
		{
		  widest_int w = wi::to_widest (constructor_max_index);
		  w -= wi::to_widest (constructor_index);
		  w += 1;
		  எனில் (w < len)
		    len = w.to_uhwi ();
		}
	      எனில் (len < (unsigned) RAW_DATA_LENGTH (மதிப்பு.மதிப்பு))
		{
		  raw_data = copy_முனை (மதிப்பு.மதிப்பு);
		  RAW_DATA_LENGTH (raw_data) -= len;
		  RAW_DATA_POINTER (raw_data) += len;
		  RAW_DATA_LENGTH (மதிப்பு.மதிப்பு) = len;
		}
	      மரம்_TYPE (மதிப்பு.மதிப்பு) = elttype;
	      தள்ளு_array_bounds (மரம்_to_uhwi (constructor_index));
	      output_init_element (loc, மதிப்பு.மதிப்பு, மதிப்பு.original_type,
				   பொய், elttype, constructor_index, உண்மை,
				   implicit, braced_init_obstack);
	      RESTORE_SPELLING_DEPTH (constructor_depth);
	      constructor_index
		= size_binop_loc (உள்ளீடு_location, PLUS_கோவை,
				  constructor_index, bitsize_int (len));
	    }
	  இல்லையெனில்
	    {
	      மதிப்பு.மதிப்பு = maybe_split_raw_data (மதிப்பு.மதிப்பு, &raw_data);
	      /* Now output the actual element.  */
	      எனில் (மதிப்பு.மதிப்பு)
		{
		  தள்ளு_array_bounds (மரம்_to_uhwi (constructor_index));
		  output_init_element (loc, மதிப்பு.மதிப்பு, மதிப்பு.original_type,
				       strict_string, elttype,
				       constructor_index, உண்மை, implicit,
				       braced_init_obstack);
		  RESTORE_SPELLING_DEPTH (constructor_depth);
		}

	      constructor_index
		= size_binop_loc (உள்ளீடு_location, PLUS_கோவை,
				  constructor_index, bitsize_one_முனை);

	      எனில் (!மதிப்பு.மதிப்பு)
		/* If we are doing the bookkeeping for an element that was
		   directly output as a constructor, we must update
		   constructor_unfilled_index.  */
		constructor_unfilled_index = constructor_index;
	    }
	}
      இல்லையெனில் எனில் (gnu_vector_type_p (constructor_type))
	{
	  மரம் elttype = TYPE_MAIN_VARIANT (மரம்_TYPE (constructor_type));

	  /* Do a basic check of initializer size.  Note that vectors
	     may not always have a fixed size derived from their type.  */
	  எனில் (maybe_lt (மரம்_to_poly_uint64 (constructor_max_index),
			மரம்_to_poly_uint64 (constructor_index)))
	    {
	      /* Diagose VLA out-of-bounds as errors.  */
	      எனில் (மரம்_to_poly_uint64 (constructor_max_index).is_constant())
		pedwarn_init (loc, 0,
			      "excess elements in vector initializer");
	      இல்லையெனில்
		error_init (loc, "excess elements in vector initializer");

	      நிறுத்து;
	    }

	  மதிப்பு.மதிப்பு = maybe_split_raw_data (மதிப்பு.மதிப்பு, &raw_data);
	  /* Now output the actual element.  */
	  எனில் (மதிப்பு.மதிப்பு)
	    {
	      எனில் (மரம்_CODE (மதிப்பு.மதிப்பு) == VECTOR_CST)
		elttype = TYPE_MAIN_VARIANT (constructor_type);
	      output_init_element (loc, மதிப்பு.மதிப்பு, மதிப்பு.original_type,
				   strict_string, elttype,
				   constructor_index, உண்மை, implicit,
				   braced_init_obstack);
	    }

	  constructor_index
	    = size_binop_loc (உள்ளீடு_location,
			      PLUS_கோவை, constructor_index, bitsize_one_முனை);

	  எனில் (!மதிப்பு.மதிப்பு)
	    /* If we are doing the bookkeeping for an element that was
	       directly output as a constructor, we must update
	       constructor_unfilled_index.  */
	    constructor_unfilled_index = constructor_index;
	}

      /* Handle the sole element allowed in a braced initializer
	 for a scalar variable.  */
      இல்லையெனில் எனில் (constructor_type != error_mark_முனை
	       && constructor_fields == NULL_மரம்)
	{
	  pedwarn_init (loc, 0,
			"excess elements in scalar initializer");
	  நிறுத்து;
	}
      இல்லையெனில்
	{
	  மதிப்பு.மதிப்பு = maybe_split_raw_data (மதிப்பு.மதிப்பு, &raw_data);
	  எனில் (மதிப்பு.மதிப்பு)
	    output_init_element (loc, மதிப்பு.மதிப்பு, மதிப்பு.original_type,
				 strict_string, constructor_type,
				 NULL_மரம், உண்மை, implicit,
				 braced_init_obstack);
	  constructor_fields = NULL_மரம்;
	}

      /* Handle range initializers either at this level or anywhere higher
	 in the designator stack.  */
      எனில் (constructor_range_அடுக்கு)
	{
	  கட்டமைப்பு constructor_range_அடுக்கு *p, *range_அடுக்கு;
	  முழு finish = 0;

	  range_அடுக்கு = constructor_range_அடுக்கு;
	  constructor_range_அடுக்கு = 0;
	  போது (constructor_அடுக்கு != range_அடுக்கு->அடுக்கு)
	    {
	      gcc_assert (constructor_அடுக்கு->implicit);
	      process_init_element (loc,
				    எடு_init_level (loc, 1,
						    braced_init_obstack,
						    last_init_list_comma),
				    உண்மை, braced_init_obstack);
	    }
	  க்கு (p = range_அடுக்கு;
	       !p->range_end || மரம்_int_cst_equal (p->index, p->range_end);
	       p = p->prev)
	    {
	      gcc_assert (constructor_அடுக்கு->implicit);
	      process_init_element (loc,
				    எடு_init_level (loc, 1,
						    braced_init_obstack,
						    last_init_list_comma),
				    உண்மை, braced_init_obstack);
	    }

	  p->index = size_binop_loc (உள்ளீடு_location,
				     PLUS_கோவை, p->index, bitsize_one_முனை);
	  எனில் (மரம்_int_cst_equal (p->index, p->range_end) && !p->prev)
	    finish = 1;

	  போது (1)
	    {
	      constructor_index = p->index;
	      constructor_fields = p->fields;
	      எனில் (finish && p->range_end && p->index == p->range_start)
		{
		  finish = 0;
		  p->prev = 0;
		}
	      p = p->next;
	      எனில் (!p)
		நிறுத்து;
	      finish_implicit_inits (loc, braced_init_obstack);
	      தள்ளு_init_level (loc, 2, braced_init_obstack);
	      p->அடுக்கு = constructor_அடுக்கு;
	      எனில் (p->range_end && மரம்_int_cst_equal (p->index, p->range_end))
		p->index = p->range_start;
	    }

	  எனில் (!finish)
	    constructor_range_அடுக்கு = range_அடுக்கு;
	  தொடர்;
	}

      நிறுத்து;
    }

  constructor_range_அடுக்கு = 0;

  எனில் (raw_data && RAW_DATA_LENGTH (raw_data))
    {
      gcc_assert (!string_flag && !was_designated);
      மதிப்பு.மதிப்பு = raw_data;
      raw_data = NULL_மரம்;
      செல் retry;
    }
}

/* Build a complete asm-statement, whose components are a CV_QUALIFIER
   (guaranteed to be 'volatile' or null) and ARGS (represented using
   an ASM_EXPR node).  */
மரம்
build_asm_stmt (தருக்க is_volatile, மரம் args)
{
  எனில் (is_volatile)
    ASM_VOLATILE_P (args) = 1;
  திரும்பு add_stmt (args);
}

/* Build an asm-expr, whose components are a STRING, some OUTPUTS,
   some INPUTS, and some CLOBBERS.  The latter three may be NULL.
   SIMPLE indicates whether there was anything at all after the
   string in the asm expression -- asm("blah") and asm("blah" : )
   are subtly different.  We use a ASM_EXPR node to represent this.
   LOC is the location of the asm, and IS_INLINE says whether this
   is asm inline.  */
மரம்
build_asm_கோவை (location_t loc, மரம் string, மரம் outputs, மரம் inputs,
		மரம் clobbers, மரம் labels, தருக்க simple, தருக்க is_inline)
{
  மரம் tail;
  மரம் args;
  முழு i;
  மாறிலி எழுத்து *constraint;
  மாறிலி எழுத்து **oconstraints;
  தருக்க allows_mem, allows_reg, is_inout;
  முழு ninputs, noutputs;

  ninputs = list_length (inputs);
  noutputs = list_length (outputs);
  oconstraints = (மாறிலி எழுத்து **) alloca (noutputs * அளவு (மாறிலி எழுத்து *));

  string = resolve_asm_operand_names (string, outputs, inputs, labels);

  /* Remove output conversions that change the type but not the mode.  */
  க்கு (i = 0, tail = outputs; tail; ++i, tail = மரம்_CHAIN (tail))
    {
      மரம் output = மரம்_மதிப்பு (tail);

      output = c_fully_fold (output, பொய், வெற்று, உண்மை);

      /* ??? Really, this should not be here.  Users should be using a
	 proper lvalue, dammit.  But there's a long history of using casts
	 in the output operands.  In cases like longlong.h, this becomes a
	 primitive form of typechecking -- if the cast can be removed, then
	 the output operand had a type of the proper width; otherwise we'll
	 get an error.  Gross, but ...  */
      STRIP_NOPS (output);

      எனில் (!lvalue_or_else (loc, output, lv_asm))
	output = error_mark_முனை;

      எனில் (output != error_mark_முனை
	  && (மரம்_READONLY (output)
	      || TYPE_READONLY (மரம்_TYPE (output))
	      || (RECORD_OR_UNION_TYPE_P (மரம்_TYPE (output))
		  && C_TYPE_FIELDS_READONLY (மரம்_TYPE (output)))))
	readonly_error (loc, output, lv_asm);

      constraint = மரம்_STRING_POINTER (மரம்_மதிப்பு (மரம்_PURPOSE (tail)));
      oconstraints[i] = constraint;

      எனில் (parse_output_constraint (&constraint, i, ninputs, noutputs,
				   &allows_mem, &allows_reg, &is_inout,
				   nullptr))
	{
	  /* If the operand is going to end up in memory,
	     mark it addressable.  */
	  எனில் (!allows_reg && !c_mark_addressable (output))
	    output = error_mark_முனை;
	  எனில் (!(!allows_reg && allows_mem)
	      && output != error_mark_முனை
	      && VOID_TYPE_P (மரம்_TYPE (output)))
	    {
	      error_at (loc, "invalid use of void expression");
	      output = error_mark_முனை;
	    }
	  எனில் (allows_reg && current_function_decl == NULL_மரம்)
	    {
	      error_at (loc, "constraint allows registers outside of "
			     "a function");
	      output = error_mark_முனை;
	    }
	}
      இல்லையெனில்
	output = error_mark_முனை;

      எனில் (current_function_decl == NULL_மரம் && output != error_mark_முனை)
	{
	  எனில் (மரம்_SIDE_EFFECTS (output))
	    {
	      error_at (loc, "side-effects in output operand outside "
			     "of a function");
	      output = error_mark_முனை;
	    }
	  இல்லையெனில்
	    {
	      மரம் addr = build_unary_op (loc, ADDR_கோவை, output, பொய்);
	      எனில் (addr == error_mark_முனை)
		output = error_mark_முனை;
	      இல்லையெனில் எனில் (!initializer_constant_valid_p (addr, மரம்_TYPE (addr)))
		{
		  error_at (loc, "output operand outside of a function is not "
				 "constant");
		  output = error_mark_முனை;
		}
	    }
	}
      இல்லையெனில் எனில் (output != error_mark_முனை && strstr (constraint, "-"))
	{
	  error_at (loc, "%<-%> modifier used inside of a function");
	  output = error_mark_முனை;
	}

      மரம்_மதிப்பு (tail) = output;
    }

  க்கு (i = 0, tail = inputs; tail; ++i, tail = மரம்_CHAIN (tail))
    {
      மரம் உள்ளீடு;

      constraint = மரம்_STRING_POINTER (மரம்_மதிப்பு (மரம்_PURPOSE (tail)));
      உள்ளீடு = மரம்_மதிப்பு (tail);

      எனில் (parse_உள்ளீடு_constraint (&constraint, i, ninputs, noutputs, 0,
				  oconstraints, &allows_mem, &allows_reg,
				  nullptr))
	{
	  /* If the operand is going to end up in memory,
	     mark it addressable.  */
	  எனில் (!allows_reg && allows_mem)
	    {
	      உள்ளீடு = c_fully_fold (உள்ளீடு, பொய், வெற்று, உண்மை);

	      /* Strip the nops as we allow this case.  FIXME, this really
		 should be rejected or made deprecated.  */
	      STRIP_NOPS (உள்ளீடு);
	      எனில் (!c_mark_addressable (உள்ளீடு))
		உள்ளீடு = error_mark_முனை;
	    }
	  இல்லையெனில்
	    {
	      உள்ளீடு = c_fully_fold (convert_lvalue_to_rvalue (loc, உள்ளீடு,
							      உண்மை, பொய்),
				    பொய், வெற்று);

	      எனில் (உள்ளீடு != error_mark_முனை && VOID_TYPE_P (மரம்_TYPE (உள்ளீடு)))
		{
		  error_at (loc, "invalid use of void expression");
		  உள்ளீடு = error_mark_முனை;
		}
	    }
	  எனில் (allows_reg && current_function_decl == NULL_மரம்)
	    {
	      error_at (loc, "constraint allows registers outside of "
			     "a function");
	      உள்ளீடு = error_mark_முனை;
	    }
	  எனில் (constraint[0] == ':' && உள்ளீடு != error_mark_முனை)
	    {
	      மரம் t = உள்ளீடு;
	      STRIP_NOPS (t);
	      எனில் (மரம்_CODE (t) != ADDR_கோவை
		  || !(மரம்_CODE (மரம்_OPERAND (t, 0)) == FUNCTION_DECL
		       || (VAR_P (மரம்_OPERAND (t, 0))
			   && is_global_var (மரம்_OPERAND (t, 0)))))
		{
		  error_at (loc, "%<:%> constraint operand is not address "
				 "of a function or non-automatic variable");
		  உள்ளீடு = error_mark_முனை;
		}
	      இல்லையெனில் எனில் (மரம்_CODE (மரம்_OPERAND (t, 0)) == FUNCTION_DECL)
		suppress_warning (மரம்_OPERAND (t, 0), OPT_Wunused);
	    }
	}
      இல்லையெனில்
	உள்ளீடு = error_mark_முனை;

      எனில் (current_function_decl == NULL_மரம் && உள்ளீடு != error_mark_முனை)
	{
	  எனில் (மரம்_SIDE_EFFECTS (உள்ளீடு))
	    {
	      error_at (loc, "side-effects in input operand outside "
			     "of a function");
	      உள்ளீடு = error_mark_முனை;
	    }
	  இல்லையெனில்
	    {
	      மரம் tem = உள்ளீடு;
	      எனில் (allows_mem && lvalue_p (உள்ளீடு))
		tem = build_unary_op (loc, ADDR_கோவை, உள்ளீடு, பொய்);
	      எனில் (!initializer_constant_valid_p (tem, மரம்_TYPE (tem)))
		{
		  error_at (loc, "input operand outside of a function is not "
				 "constant");
		  உள்ளீடு = error_mark_முனை;
		}
	    }
	}
      இல்லையெனில் எனில் (உள்ளீடு != error_mark_முனை && strstr (constraint, "-"))
	{
	  error_at (loc, "%<-%> modifier used inside of a function");
	  உள்ளீடு = error_mark_முனை;
	}

      மரம்_மதிப்பு (tail) = உள்ளீடு;
    }

  args = build_stmt (loc, ASM_கோவை, string, outputs, inputs, clobbers, labels);

  /* asm statements without outputs, including simple ones, are treated
     as volatile.  */
  ASM_BASIC_P (args) = simple;
  ASM_VOLATILE_P (args) = (noutputs == 0);
  ASM_INLINE_P (args) = is_inline;

  திரும்பு args;
}

/* Generate a goto statement to LABEL.  LOC is the location of the
   GOTO.  */

மரம்
c_finish_goto_label (location_t loc, மரம் label)
{
  மரம் decl = lookup_label_for_goto (loc, label);
  எனில் (!decl)
    திரும்பு NULL_மரம்;
  மரம்_USED (decl) = 1;
  mark_decl_used (decl, பொய்);
  {
    add_stmt (build_predict_கோவை (PRED_GOTO, NOT_TAKEN));
    மரம் t = build1 (GOTO_கோவை, void_type_முனை, decl);
    SET_கோவை_LOCATION (t, loc);
    திரும்பு add_stmt (t);
  }
}

/* Generate a computed goto statement to EXPR.  LOC is the location of
   the GOTO.  */

மரம்
c_finish_goto_ptr (location_t loc, c_கோவை val)
{
  மரம் கோவை = val.மதிப்பு;
  மரம் t;
  pedwarn (loc, OPT_Wpedantic, "ISO C forbids %<goto *expr;%>");
  எனில் (கோவை != error_mark_முனை
      && !POINTER_TYPE_P (மரம்_TYPE (கோவை))
      && !null_pointer_constant_p (கோவை))
    {
      error_at (val.get_location (),
		"computed goto must be pointer type");
      கோவை = build_zero_cst (ptr_type_முனை);
    }
  கோவை = c_fully_fold (கோவை, பொய், வெற்று);
  கோவை = convert (ptr_type_முனை, கோவை);
  t = build1 (GOTO_கோவை, void_type_முனை, கோவை);
  SET_கோவை_LOCATION (t, loc);
  திரும்பு add_stmt (t);
}

/* Generate a C `return' statement.  RETVAL is the expression for what
   to return, or a null pointer for `return;' with no value.  LOC is
   the location of the return statement, or the location of the expression,
   if the statement has any.  If ORIGTYPE is not NULL_TREE, it
   is the original type of RETVAL.  MUSTTAIL_P indicates a musttail
   attribute.  */

மரம்
c_finish_return (location_t loc, மரம் retval, மரம் origtype, தருக்க musttail_p)
{
  மரம் valtype = மரம்_TYPE (மரம்_TYPE (current_function_decl)), ret_stmt;
  தருக்க no_warning = பொய்;
  தருக்க npc = பொய்;

  /* Use the expansion point to handle cases such as returning NULL
     in a function returning void.  */
  location_t xloc = expansion_point_location_if_in_system_header (loc);

  எனில் (மரம்_THIS_VOLATILE (current_function_decl))
    warning_at (xloc, 0,
		"function declared %<noreturn%> has a %<return%> statement");

  set_musttail_on_return (retval, xloc, musttail_p);

  எனில் (retval)
    {
      மரம் semantic_type = NULL_மரம்;
      npc = null_pointer_constant_p (retval);
      எனில் (மரம்_CODE (retval) == EXCESS_PRECISION_கோவை)
	{
	  semantic_type = மரம்_TYPE (retval);
	  retval = மரம்_OPERAND (retval, 0);
	}
      retval = c_fully_fold (retval, பொய், வெற்று);
      எனில் (semantic_type
	  && valtype != NULL_மரம்
	  && மரம்_CODE (valtype) != VOID_TYPE)
	retval = build1 (EXCESS_PRECISION_கோவை, semantic_type, retval);
    }

  எனில் (!retval)
    {
      current_function_returns_null = 1;
      எனில் ((warn_return_type >= 0 || flag_isoc99)
	  && valtype != NULL_மரம் && மரம்_CODE (valtype) != VOID_TYPE)
	{
	  no_warning = உண்மை;
	  எனில் (emit_diagnostic (flag_isoc99
			       ? diagnostics::kind::permerror
			       : diagnostics::kind::warning,
			       loc, OPT_Wreturn_mismatch,
			       "%<return%> with no value,"
			       " in function returning non-void"))
	    inform (DECL_SOURCE_LOCATION (current_function_decl),
		    "declared here");
	}
    }
  இல்லையெனில் எனில் (valtype == NULL_மரம் || VOID_TYPE_P (valtype))
    {
      current_function_returns_null = 1;
      தருக்க warned_here;
      எனில் (மரம்_CODE (மரம்_TYPE (retval)) != VOID_TYPE)
	warned_here = permerror_opt
	  (xloc, OPT_Wreturn_mismatch,
	   "%<return%> with a value, in function returning void");
      இல்லையெனில்
	warned_here = pedwarn
	  (xloc, OPT_Wpedantic, "ISO C forbids "
	   "%<return%> with expression, in function returning void");
      எனில் (warned_here)
	inform (DECL_SOURCE_LOCATION (current_function_decl),
		"declared here");
    }
  இல்லையெனில்
    {
      மரம் t = convert_for_assignment (loc, UNKNOWN_LOCATION, valtype,
				       retval, origtype, ic_return,
				       npc, NULL_மரம், NULL_மரம், 0);
      மரம் res = DECL_RESULT (current_function_decl);
      மரம் inner;
      தருக்க save;

      current_function_returns_மதிப்பு = 1;
      எனில் (t == error_mark_முனை)
	{
	  /* Suppress -Wreturn-type for this function.  */
	  எனில் (warn_return_type)
	    suppress_warning (current_function_decl, OPT_Wreturn_type);
	  திரும்பு NULL_மரம்;
	}

      save = in_late_இருமம்_op;
      எனில் (C_BOOLEAN_TYPE_P (மரம்_TYPE (res))
	  || மரம்_CODE (மரம்_TYPE (res)) == COMPLEX_TYPE
	  || (SCALAR_FLOAT_TYPE_P (மரம்_TYPE (t))
	      && (மரம்_CODE (மரம்_TYPE (res)) == INTEGER_TYPE
		  || மரம்_CODE (மரம்_TYPE (res)) == ENUMERAL_TYPE)
	      && sanitize_flags_p (SANITIZE_FLOAT_CAST)))
        in_late_இருமம்_op = உண்மை;
      inner = t = convert (மரம்_TYPE (res), t);
      in_late_இருமம்_op = save;

      /* Strip any conversions, additions, and subtractions, and see if
	 we are returning the address of a local variable.  Warn if so.  */
      போது (1)
	{
	  தேர்வு (மரம்_CODE (inner))
	    {
	    CASE_CONVERT:
	    நிலை NON_LVALUE_கோவை:
	    நிலை PLUS_கோவை:
	    நிலை POINTER_PLUS_கோவை:
	      inner = மரம்_OPERAND (inner, 0);
	      தொடர்;

	    நிலை MINUS_கோவை:
	      /* If the second operand of the MINUS_EXPR has a pointer
		 type (or is converted from it), this may be valid, so
		 don't give a warning.  */
	      {
		மரம் op1 = மரம்_OPERAND (inner, 1);

		போது (!POINTER_TYPE_P (மரம்_TYPE (op1))
		       && (CONVERT_கோவை_P (op1)
			   || மரம்_CODE (op1) == NON_LVALUE_கோவை))
		  op1 = மரம்_OPERAND (op1, 0);

		எனில் (POINTER_TYPE_P (மரம்_TYPE (op1)))
		  நிறுத்து;

		inner = மரம்_OPERAND (inner, 0);
		தொடர்;
	      }

	    நிலை ADDR_கோவை:
	      inner = மரம்_OPERAND (inner, 0);

	      போது (REFERENCE_CLASS_P (inner)
		     && !INDIRECT_REF_P (inner))
		inner = மரம்_OPERAND (inner, 0);

	      எனில் (DECL_P (inner)
		  && !DECL_EXTERNAL (inner)
		  && DECL_CONTEXT (inner) == current_function_decl
		  && POINTER_TYPE_P (மரம்_TYPE (மரம்_TYPE (current_function_decl))))
		{
		  எனில் (மரம்_CODE (inner) == LABEL_DECL)
		    warning_at (loc, OPT_Wreturn_local_addr,
				"function returns address of label");
		  இல்லையெனில் எனில் (மரம்_CODE (inner) == FUNCTION_DECL
			   && (C_FUNC_NONLOCAL_CONTEXT (inner)
			       || !DECL_INITIAL (inner)))
		    warning_at (loc, OPT_Wreturn_local_addr,
				"function returns address of nested function "
				"referencing local context");
		  இல்லையெனில் எனில் (மரம்_CODE (inner) != FUNCTION_DECL
			   && !மரம்_STATIC (inner))
		    {
		      warning_at (loc, OPT_Wreturn_local_addr,
				  "function returns address of local variable");
		      மரம் zero = build_zero_cst (மரம்_TYPE (res));
		      t = build2 (COMPOUND_கோவை, மரம்_TYPE (res), t, zero);
		    }
		}
	      நிறுத்து;

	    இயல்பு:
	      நிறுத்து;
	    }

	  நிறுத்து;
	}

      retval = build2 (MODIFY_கோவை, மரம்_TYPE (res), res, t);
      SET_கோவை_LOCATION (retval, loc);

      எனில் (warn_sequence_point)
	verify_sequence_points (retval);
    }

  ret_stmt = build_stmt (loc, RETURN_கோவை, retval);
  எனில் (no_warning)
    suppress_warning (ret_stmt, OPT_Wreturn_type);
  திரும்பு add_stmt (ret_stmt);
}

கட்டமைப்பு c_switch {
  /* The SWITCH_STMT being built.  */
  மரம் switch_stmt;

  /* The original type of the testing expression, i.e. before the
     default conversion is applied.  */
  மரம் orig_type;

  /* A splay-tree mapping the low element of a case range to the high
     element, or NULL_TREE if there is no high element.  Used to
     determine whether or not a new case label duplicates an old case
     label.  We need a tree, rather than simply a hash table, because
     of the GNU case range extension.  */
  splay_மரம் cases;

  /* The bindings at the point of the switch.  This is used for
     warnings crossing decls when branching to a case label.  */
  கட்டமைப்பு c_spot_bindings *bindings;

  /* Whether the switch includes any break statements.  */
  தருக்க break_stmt_seen_p;

  /* The next node on the stack.  */
  கட்டமைப்பு c_switch *next;

  /* Remember whether the controlling expression had boolean type
     before integer promotions for the sake of -Wswitch-bool.  */
  தருக்க bool_cond_p;
};

/* A stack of the currently active switch statements.  The innermost
   switch statement is on the top of the stack.  There is no need to
   mark the stack for garbage collection because it is only active
   during the processing of the body of a function, and we never
   collect at that point.  */

கட்டமைப்பு c_switch *c_switch_அடுக்கு;

/* Start a C switch statement, testing expression EXP.  Return the new
   SWITCH_STMT.  SWITCH_LOC is the location of the `switch'.
   SWITCH_COND_LOC is the location of the switch's condition.
   EXPLICIT_CAST_P is true if the expression EXP has an explicit cast.  */

மரம்
c_start_switch (location_t switch_loc,
		location_t switch_cond_loc,
		மரம் exp, தருக்க explicit_cast_p, மரம் switch_name)
{
  மரம் orig_type = error_mark_முனை;
  தருக்க bool_cond_p = பொய்;
  கட்டமைப்பு c_switch *cs;

  எனில் (exp != error_mark_முனை)
    {
      orig_type = மரம்_TYPE (exp);

      எனில் (!INTEGRAL_TYPE_P (orig_type))
	{
	  எனில் (orig_type != error_mark_முனை)
	    {
	      error_at (switch_cond_loc, "switch quantity not an integer");
	      orig_type = error_mark_முனை;
	    }
	  exp = integer_zero_முனை;
	}
      இல்லையெனில்
	{
	  மரம் type = TYPE_MAIN_VARIANT (orig_type);
	  மரம் e = exp;

	  /* Warn if the condition has boolean value.  */
	  போது (மரம்_CODE (e) == COMPOUND_கோவை)
	    e = மரம்_OPERAND (e, 1);

	  எனில் ((C_BOOLEAN_TYPE_P (type)
	       || truth_மதிப்பு_p (மரம்_CODE (e)))
	      /* Explicit cast to int suppresses this warning.  */
	      && !(மரம்_CODE (type) == INTEGER_TYPE
		   && explicit_cast_p))
	    bool_cond_p = உண்மை;

	  எனில் (!in_system_header_at (உள்ளீடு_location)
	      && (type == long_integer_type_முனை
		  || type == long_unsigned_type_முனை))
	    warning_at (switch_cond_loc,
			OPT_Wtraditional, "%<long%> switch expression not "
			"converted to %<int%> in ISO C");

	  exp = c_fully_fold (exp, பொய், வெற்று);
	  exp = default_conversion (exp);

	  எனில் (warn_sequence_point)
	    verify_sequence_points (exp);
	}
    }

  /* Add this new SWITCH_STMT to the stack.  */
  cs = XNEW (கட்டமைப்பு c_switch);
  cs->switch_stmt = build_stmt (switch_loc, SWITCH_STMT, exp,
				NULL_மரம், orig_type, NULL_மரம், switch_name);
  cs->orig_type = orig_type;
  cs->cases = splay_மரம்_new (case_compare, வெற்று, வெற்று);
  cs->bindings = c_get_switch_bindings ();
  cs->break_stmt_seen_p = பொய்;
  cs->bool_cond_p = bool_cond_p;
  cs->next = c_switch_அடுக்கு;
  c_switch_அடுக்கு = cs;

  திரும்பு add_stmt (cs->switch_stmt);
}

/* Process a case label at location LOC, with attributes ATTRS.  */

மரம்
do_case (location_t loc, மரம் கீழ்_மதிப்பு, மரம் உயர்வு_மதிப்பு, மரம் attrs)
{
  மரம் label = NULL_மரம்;

  எனில் (கீழ்_மதிப்பு && மரம்_CODE (கீழ்_மதிப்பு) != INTEGER_CST)
    {
      கீழ்_மதிப்பு = c_fully_fold (கீழ்_மதிப்பு, பொய், வெற்று);
      எனில் (மரம்_CODE (கீழ்_மதிப்பு) == INTEGER_CST)
	pedwarn (loc, OPT_Wpedantic,
		 "case label is not an integer constant expression");
    }

  எனில் (உயர்வு_மதிப்பு && மரம்_CODE (உயர்வு_மதிப்பு) != INTEGER_CST)
    {
      உயர்வு_மதிப்பு = c_fully_fold (உயர்வு_மதிப்பு, பொய், வெற்று);
      எனில் (மரம்_CODE (உயர்வு_மதிப்பு) == INTEGER_CST)
	pedwarn (உள்ளீடு_location, OPT_Wpedantic,
		 "case label is not an integer constant expression");
    }

  எனில் (c_switch_அடுக்கு == வெற்று)
    {
      எனில் (கீழ்_மதிப்பு)
	error_at (loc, "case label not within a switch statement");
      இல்லையெனில்
	error_at (loc, "%<default%> label not within a switch statement");
      திரும்பு NULL_மரம்;
    }

  எனில் (c_check_switch_jump_warnings (c_switch_அடுக்கு->bindings,
				    கோவை_LOCATION (c_switch_அடுக்கு->switch_stmt),
				    loc))
    திரும்பு NULL_மரம்;

  label = c_add_case_label (loc, c_switch_அடுக்கு->cases,
			    SWITCH_STMT_COND (c_switch_அடுக்கு->switch_stmt),
			    கீழ்_மதிப்பு, உயர்வு_மதிப்பு, attrs);
  எனில் (label == error_mark_முனை)
    label = NULL_மரம்;
  திரும்பு label;
}

/* Finish the switch statement.  TYPE is the original type of the
   controlling expression of the switch, or NULL_TREE.  */

வெறுமை
c_finish_switch (மரம் body, மரம் type)
{
  கட்டமைப்பு c_switch *cs = c_switch_அடுக்கு;
  location_t switch_location;

  SWITCH_STMT_BODY (cs->switch_stmt) = body;

  /* Emit warnings as needed.  */
  switch_location = கோவை_LOCATION (cs->switch_stmt);
  c_do_switch_warnings (cs->cases, switch_location,
			type ? type : SWITCH_STMT_TYPE (cs->switch_stmt),
			SWITCH_STMT_COND (cs->switch_stmt), cs->bool_cond_p);
  எனில் (c_switch_covers_all_cases_p (cs->cases,
				   SWITCH_STMT_TYPE (cs->switch_stmt)))
    SWITCH_STMT_ALL_CASES_P (cs->switch_stmt) = 1;
  SWITCH_STMT_NO_BREAK_P (cs->switch_stmt) = !cs->break_stmt_seen_p;

  /* Pop the stack.  */
  c_switch_அடுக்கு = cs->next;
  splay_மரம்_delete (cs->cases);
  c_release_switch_bindings (cs->bindings);
  XDELETE (cs);
}

/* Emit an if statement.  IF_LOCUS is the location of the 'if'.  COND,
   THEN_BLOCK and ELSE_BLOCK are expressions to be used; ELSE_BLOCK
   may be null.  */

வெறுமை
c_finish_if_stmt (location_t if_locus, மரம் cond, மரம் then_block,
		  மரம் else_block)
{
  மரம் stmt;

  stmt = build3 (COND_கோவை, void_type_முனை, cond, then_block, else_block);
  SET_கோவை_LOCATION (stmt, if_locus);
  add_stmt (stmt);
}

மரம்
c_finish_bc_stmt (location_t loc, மரம் label, தருக்க is_break, மரம் name)
{
  /* In switch statements break is sometimes stylistically used after
     a return statement.  This can lead to spurious warnings about
     control reaching the end of a non-void function when it is
     inlined.  Note that we are calling block_may_fallthru with
     language specific tree nodes; this works because
     block_may_fallthru returns true when given something it does not
     understand.  */
  தருக்க skip = !block_may_fallthru (cur_stmt_list);

  எனில் (is_break)
    தேர்வு (in_statement & ~IN_NAMED_STMT)
      {
      நிலை 0:
	error_at (loc, "break statement not within loop or switch");
	திரும்பு NULL_மரம்;
      நிலை IN_OMP_BLOCK:
	error_at (loc, "invalid exit from OpenMP structured block");
	திரும்பு NULL_மரம்;
      நிலை IN_OMP_FOR:
	error_at (loc, "break statement used with OpenMP for loop");
	திரும்பு NULL_மரம்;
      நிலை IN_ITERATION_STMT:
      நிலை IN_OBJC_FOREACH:
	நிறுத்து;
      இயல்பு:
	gcc_assert (in_statement & IN_SWITCH_STMT);
	c_switch_அடுக்கு->break_stmt_seen_p = உண்மை;
	நிறுத்து;
      }
  இல்லையெனில்
    தேர்வு (in_statement & ~(IN_SWITCH_STMT | IN_NAMED_STMT))
      {
      நிலை 0:
	error_at (loc, "continue statement not within a loop");
	திரும்பு NULL_மரம்;
      நிலை IN_OMP_BLOCK:
	error_at (loc, "invalid exit from OpenMP structured block");
	திரும்பு NULL_மரம்;
      நிலை IN_ITERATION_STMT:
      நிலை IN_OMP_FOR:
      நிலை IN_OBJC_FOREACH:
	நிறுத்து;
      இயல்பு:
	gcc_unreachable ();
      }

  எனில் (skip)
    திரும்பு NULL_மரம்;
  இல்லையெனில் எனில் ((in_statement & IN_OBJC_FOREACH)
	   && !(is_break && (in_statement & IN_SWITCH_STMT))
	   && name == NULL_மரம்)
    {
      /* The foreach expander produces low-level code using gotos instead
	 of a structured loop construct.  */
      gcc_assert (label);
      திரும்பு add_stmt (build_stmt (loc, GOTO_கோவை, label));
    }
  இல்லையெனில் எனில் (name && C_DECL_LOOP_NAME (name) && C_DECL_SWITCH_NAME (name))
    {
      label = DECL_CHAIN (name);
      எனில் (!is_break)
	label = DECL_CHAIN (label);
      /* Foreach expander from some outer level.  */
      திரும்பு add_stmt (build_stmt (loc, GOTO_கோவை, label));
    }
  திரும்பு add_stmt (build_stmt (loc, is_break ? BREAK_STMT : CONTINUE_STMT,
			       name));
}

/* A helper routine for c_process_expr_stmt and c_finish_stmt_expr.  */

நிலையான வெறுமை
emit_side_effect_warnings (location_t loc, மரம் கோவை)
{
  maybe_warn_nodiscard (loc, கோவை);
  எனில் (!warn_unused_மதிப்பு)
    திரும்பு;
  எனில் (கோவை == error_mark_முனை)
    ;
  இல்லையெனில் எனில் (!மரம்_SIDE_EFFECTS (கோவை))
    {
      எனில் (!VOID_TYPE_P (மரம்_TYPE (கோவை))
	  && !warning_suppressed_p (கோவை, OPT_Wunused_மதிப்பு))
	warning_at (loc, OPT_Wunused_மதிப்பு, "statement with no effect");
    }
  இல்லையெனில் எனில் (மரம்_CODE (கோவை) == COMPOUND_கோவை)
    {
      மரம் r = கோவை;
      location_t cloc = loc;
      போது (மரம்_CODE (r) == COMPOUND_கோவை)
	{
	  எனில் (கோவை_HAS_LOCATION (r))
	    cloc = கோவை_LOCATION (r);
	  r = மரம்_OPERAND (r, 1);
	}
      எனில் (!மரம்_SIDE_EFFECTS (r)
	  && !VOID_TYPE_P (மரம்_TYPE (r))
	  && !CONVERT_கோவை_P (r)
	  && !warning_suppressed_p (r, OPT_Wunused_மதிப்பு)
	  && !warning_suppressed_p (கோவை, OPT_Wunused_மதிப்பு))
	warning_at (cloc, OPT_Wunused_மதிப்பு,
		    "right-hand operand of comma expression has no effect");
    }
  இல்லையெனில்
    warn_if_unused_மதிப்பு (கோவை, loc);
}

/* Process an expression as if it were a complete statement.  Emit
   diagnostics, but do not call ADD_STMT.  LOC is the location of the
   statement.  */

மரம்
c_process_கோவை_stmt (location_t loc, மரம் கோவை)
{
  மரம் exprv;

  எனில் (!கோவை)
    திரும்பு NULL_மரம்;

  கோவை = c_fully_fold (கோவை, பொய், வெற்று);

  எனில் (warn_sequence_point)
    verify_sequence_points (கோவை);

  எனில் (மரம்_TYPE (கோவை) != error_mark_முனை
      && !COMPLETE_OR_VOID_TYPE_P (மரம்_TYPE (கோவை))
      && மரம்_CODE (மரம்_TYPE (கோவை)) != ARRAY_TYPE)
    error_at (loc, "expression statement has incomplete type");

  /* If we're not processing a statement expression, warn about unused values.
     Warnings for statement expressions will be emitted later, once we figure
     out which is the result.  */
  எனில் (!STATEMENT_LIST_STMT_கோவை (cur_stmt_list)
      && (warn_unused_மதிப்பு || warn_unused_result))
    emit_side_effect_warnings (கோவை_LOC_OR_LOC (கோவை, loc), கோவை);

  exprv = கோவை;
  போது (மரம்_CODE (exprv) == COMPOUND_கோவை)
    exprv = மரம்_OPERAND (exprv, 1);
  போது (CONVERT_கோவை_P (exprv))
    exprv = மரம்_OPERAND (exprv, 0);
  எனில் (DECL_P (exprv)
      || handled_component_p (exprv)
      || மரம்_CODE (exprv) == ADDR_கோவை)
    mark_exp_read (exprv);

  /* If the expression is not of a type to which we cannot assign a line
     number, wrap the thing in a no-op NOP_EXPR.  */
  எனில் (DECL_P (கோவை) || CONSTANT_CLASS_P (கோவை))
    {
      கோவை = build1 (NOP_கோவை, மரம்_TYPE (கோவை), கோவை);
      SET_கோவை_LOCATION (கோவை, loc);
    }

  திரும்பு கோவை;
}

/* Emit an expression as a statement.  LOC is the location of the
   expression.  */

மரம்
c_finish_கோவை_stmt (location_t loc, மரம் கோவை)
{
  எனில் (கோவை)
    திரும்பு add_stmt (c_process_கோவை_stmt (loc, கோவை));
  இல்லையெனில்
    திரும்பு வெற்று;
}

/* Do the opposite and emit a statement as an expression.  To begin,
   create a new binding level and return it.  */

மரம்
c_begin_stmt_கோவை (வெறுமை)
{
  மரம் ret;

  /* We must force a BLOCK for this level so that, if it is not expanded
     later, there is a way to turn off the entire subtree of blocks that
     are contained in it.  */
  keep_next_level ();
  ret = c_begin_compound_stmt (உண்மை);

  c_bindings_start_stmt_கோவை (c_switch_அடுக்கு == வெற்று
			      ? வெற்று
			      : c_switch_அடுக்கு->bindings);

  /* Mark the current statement list as belonging to a statement list.  */
  STATEMENT_LIST_STMT_கோவை (ret) = 1;

  திரும்பு ret;
}

/* LOC is the location of the compound statement to which this body
   belongs.  */

மரம்
c_finish_stmt_கோவை (location_t loc, மரம் body)
{
  மரம் last, type, tmp, val;
  மரம் *last_p;

  body = c_end_compound_stmt (loc, body, உண்மை);

  c_bindings_end_stmt_கோவை (c_switch_அடுக்கு == வெற்று
			    ? வெற்று
			    : c_switch_அடுக்கு->bindings);

  /* Locate the last statement in BODY.  See c_end_compound_stmt
     about always returning a BIND_EXPR.  */
  last_p = &BIND_கோவை_BODY (body);
  last = BIND_கோவை_BODY (body);

 continue_searching:
  எனில் (மரம்_CODE (last) == STATEMENT_LIST)
    {
      மரம்_stmt_iterator l = tsi_last (last);

      போது (!tsi_end_p (l) && மரம்_CODE (tsi_stmt (l)) == DEBUG_BEGIN_STMT)
	tsi_prev (&l);

      /* This can happen with degenerate cases like ({ }).  No value.  */
      எனில் (tsi_end_p (l))
	திரும்பு body;

      /* If we're supposed to generate side effects warnings, process
	 all of the statements except the last.  */
      எனில் (warn_unused_மதிப்பு || warn_unused_result)
	{
	  க்கு (மரம்_stmt_iterator i = tsi_start (last);
	       tsi_stmt (i) != tsi_stmt (l); tsi_next (&i))
	    {
	      location_t tloc;
	      மரம் t = tsi_stmt (i);

	      tloc = கோவை_HAS_LOCATION (t) ? கோவை_LOCATION (t) : loc;
	      emit_side_effect_warnings (tloc, t);
	    }
	}
      last_p = tsi_stmt_ptr (l);
      last = *last_p;
    }

  /* If the end of the list is exception related, then the list was split
     by a call to push_cleanup.  Continue searching.  */
  எனில் (மரம்_CODE (last) == TRY_FINALLY_கோவை
      || மரம்_CODE (last) == TRY_CATCH_கோவை)
    {
      last_p = &மரம்_OPERAND (last, 0);
      last = *last_p;
      செல் continue_searching;
    }

  எனில் (last == error_mark_முனை)
    திரும்பு last;

  /* In the case that the BIND_EXPR is not necessary, return the
     expression out from inside it.  */
  எனில் ((last == BIND_கோவை_BODY (body)
       /* Skip nested debug stmts.  */
       || last == கோவை_first (BIND_கோவை_BODY (body)))
      && BIND_கோவை_VARS (body) == வெற்று)
    {
      /* Even if this looks constant, do not allow it in a constant
	 expression.  */
      last = c_wrap_maybe_const (last, உண்மை);
      /* Do not warn if the return value of a statement expression is
	 unused.  */
      suppress_warning (last, OPT_Wunused);
      திரும்பு last;
    }

  /* Extract the type of said expression.  */
  type = மரம்_TYPE (last);

  /* If we're not returning a value at all, then the BIND_EXPR that
     we already have is a fine expression to return.  */
  எனில் (!type || VOID_TYPE_P (type))
    திரும்பு body;

  /* Now that we've located the expression containing the value, it seems
     silly to make voidify_wrapper_expr repeat the process.  Create a
     temporary of the appropriate type and stick it in a TARGET_EXPR.  */
  tmp = create_tmp_var_raw (type);

  /* Unwrap a no-op NOP_EXPR as added by c_finish_expr_stmt.  This avoids
     tree_expr_nonnegative_p giving up immediately.  */
  val = last;
  எனில் (மரம்_CODE (val) == NOP_கோவை
      && மரம்_TYPE (val) == மரம்_TYPE (மரம்_OPERAND (val, 0)))
    val = மரம்_OPERAND (val, 0);

  *last_p = build2 (MODIFY_கோவை, void_type_முனை, tmp, val);
  SET_கோவை_LOCATION (*last_p, கோவை_LOCATION (last));

  {
    மரம் t = build4 (TARGET_கோவை, type, tmp, body, NULL_மரம், NULL_மரம்);
    SET_கோவை_LOCATION (t, loc);
    திரும்பு t;
  }
}

/* Begin and end compound statements.  This is as simple as pushing
   and popping new statement lists from the tree.  */

மரம்
c_begin_compound_stmt (தருக்க do_scope)
{
  மரம் stmt = தள்ளு_stmt_list ();
  எனில் (do_scope)
    தள்ளு_scope ();
  திரும்பு stmt;
}

/* End a compound statement.  STMT is the statement.  LOC is the
   location of the compound statement-- this is usually the location
   of the opening brace.  */

மரம்
c_end_compound_stmt (location_t loc, மரம் stmt, தருக்க do_scope)
{
  மரம் block = வெற்று;

  எனில் (do_scope)
    {
      எனில் (c_dialect_objc ())
	objc_clear_super_receiver ();
      block = எடு_scope ();
    }

  stmt = எடு_stmt_list (stmt);
  stmt = c_build_bind_கோவை (loc, block, stmt);

  /* If this compound statement is nested immediately inside a statement
     expression, then force a BIND_EXPR to be created.  Otherwise we'll
     do the wrong thing for ({ { 1; } }) or ({ 1; { } }).  In particular,
     STATEMENT_LISTs merge, and thus we can lose track of what statement
     was really last.  */
  எனில் (building_stmt_list_p ()
      && STATEMENT_LIST_STMT_கோவை (cur_stmt_list)
      && மரம்_CODE (stmt) != BIND_கோவை)
    {
      stmt = build3 (BIND_கோவை, void_type_முனை, வெற்று, stmt, வெற்று);
      மரம்_SIDE_EFFECTS (stmt) = 1;
      SET_கோவை_LOCATION (stmt, loc);
    }

  திரும்பு stmt;
}

/* Queue a cleanup.  CLEANUP is an expression/statement to be executed
   when the current scope is exited.  EH_ONLY is true when this is not
   meant to apply to normal control flow transfer.  */

வெறுமை
தள்ளு_cleanup (மரம் decl, மரம் cleanup, தருக்க eh_only)
{
  எண்ணிக்கை மரம்_code code;
  மரம் stmt, list;
  தருக்க stmt_கோவை;

  code = eh_only ? TRY_CATCH_கோவை : TRY_FINALLY_கோவை;
  stmt = build_stmt (DECL_SOURCE_LOCATION (decl), code, வெற்று, cleanup);
  add_stmt (stmt);
  stmt_கோவை = STATEMENT_LIST_STMT_கோவை (cur_stmt_list);
  list = தள்ளு_stmt_list ();
  மரம்_OPERAND (stmt, 0) = list;
  STATEMENT_LIST_STMT_கோவை (list) = stmt_கோவை;
}

/* Build a vector comparison of ARG0 and ARG1 using CODE opcode
   into a value of TYPE type.  Comparison is done via VEC_COND_EXPR.  */

நிலையான மரம்
build_vec_cmp (மரம்_code code, மரம் type,
	       மரம் arg0, மரம் arg1)
{
  மரம் zero_vec = build_zero_cst (type);
  மரம் minus_one_vec = build_minus_one_cst (type);
  மரம் cmp_type = truth_type_for (மரம்_TYPE (arg0));
  மரம் cmp = build2 (code, cmp_type, arg0, arg1);
  திரும்பு build3 (VEC_COND_கோவை, type, cmp, minus_one_vec, zero_vec);
}

/* Possibly warn about an address of OP never being NULL in a comparison
   operation CODE involving null.  */

நிலையான வெறுமை
maybe_warn_for_null_address (location_t loc, மரம் op, மரம்_code code)
{
  /* Prevent warnings issued for macro expansion.  */
  எனில் (!warn_address
      || warning_suppressed_p (op, OPT_Waddress)
      || from_macro_expansion_at (loc))
    திரும்பு;

  எனில் (மரம்_CODE (op) == NOP_கோவை)
    {
      /* Allow casts to intptr_t to suppress the warning.  */
      மரம் type = மரம்_TYPE (op);
      எனில் (மரம்_CODE (type) == INTEGER_TYPE)
	திரும்பு;
      op = மரம்_OPERAND (op, 0);
    }

  எனில் (மரம்_CODE (op) == POINTER_PLUS_கோவை)
    {
      /* Allow a cast to void* to suppress the warning.  */
      மரம் type = மரம்_TYPE (மரம்_TYPE (op));
      எனில் (VOID_TYPE_P (type))
	திரும்பு;

      /* Adding any value to a null pointer, including zero, is undefined
	 in C.  This includes the expression &p[0] where p is the null
	 pointer, although &p[0] will have been folded to p by this point
	 and so not diagnosed.  */
      எனில் (code == EQ_கோவை)
	warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<false%> "
		    "for the pointer operand in %qE must not be NULL",
		    op);
      இல்லையெனில்
	warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<true%> "
		    "for the pointer operand in %qE must not be NULL",
		    op);

      திரும்பு;
    }

  எனில் (மரம்_CODE (op) != ADDR_கோவை)
    திரும்பு;

  op = மரம்_OPERAND (op, 0);

  எனில் (மரம்_CODE (op) == IMAGPART_கோவை
      || மரம்_CODE (op) == REALPART_கோவை)
    {
      /* The address of either complex part may not be null.  */
      எனில் (code == EQ_கோவை)
	warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<false%> "
		    "for the address of %qE will never be NULL",
		    op);
      இல்லையெனில்
	warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<true%> "
		    "for the address of %qE will never be NULL",
		    op);
      திரும்பு;
    }

  /* Set to true in the loop below if OP dereferences is operand.
     In such a case the ultimate target need not be a decl for
     the null [in]equality test to be constant.  */
  தருக்க deref = பொய்;

  /* Get the outermost array or object, or member.  */
  போது (handled_component_p (op))
    {
      எனில் (மரம்_CODE (op) == COMPONENT_REF)
	{
	  /* Get the member (its address is never null).  */
	  op = மரம்_OPERAND (op, 1);
	  நிறுத்து;
	}

      /* Get the outer array/object to refer to in the warning.  */
      op = மரம்_OPERAND (op, 0);
      deref = உண்மை;
    }

  எனில் ((!deref && !decl_with_nonnull_addr_p (op))
      || from_macro_expansion_at (loc))
    திரும்பு;

  தருக்க w;
  எனில் (code == EQ_கோவை)
    w = warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<false%> "
		    "for the address of %qE will never be NULL",
		    op);
  இல்லையெனில்
    w = warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<true%> "
		    "for the address of %qE will never be NULL",
		    op);

  எனில் (w && DECL_P (op))
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

மரம்
build_இருமம்_op (location_t location, எண்ணிக்கை மரம்_code code,
		 மரம் orig_op0, மரம் orig_op1, தருக்க convert_p)
{
  மரம் type0, type1, orig_type0, orig_type1;
  மரம் eptype;
  எண்ணிக்கை மரம்_code code0, code1;
  மரம் op0, op1;
  மரம் ret = error_mark_முனை;
  மாறிலி எழுத்து *invalid_op_diag;
  தருக்க op0_int_operands, op1_int_operands;
  தருக்க int_const, int_const_or_overflow, int_operands;

  /* Expression code to give to the expression when it is built.
     Normally this is CODE, which is what the caller asked for,
     but in some special cases we change it.  */
  எண்ணிக்கை மரம்_code resultcode = code;

  /* Data type in which the computation is to be performed.
     In the simplest cases this is the common type of the arguments.  */
  மரம் result_type = வெற்று;

  /* When the computation is in excess precision, the type of the
     final EXCESS_PRECISION_EXPR.  */
  மரம் semantic_result_type = வெற்று;

  /* Nonzero means operands have already been type-converted
     in whatever way is necessary.
     Zero means they need to be converted to RESULT_TYPE.  */
  முழு converted = 0;

  /* Nonzero means create the expression with this type, rather than
     RESULT_TYPE.  */
  மரம் build_type = NULL_மரம்;

  /* Nonzero means after finally constructing the expression
     convert it to this type.  */
  மரம் final_type = NULL_மரம்;

  /* Nonzero if this is an operation like MIN or MAX which can
     safely be computed in short if both args are promoted shorts.
     Also implies COMMON.
     -1 indicates a bitwise operation; this makes a difference
     in the exact conditions for when it is safe to do the operation
     in a narrower mode.  */
  முழு shorten = 0;

  /* Nonzero if this is a comparison operation;
     if both args are promoted shorts, compare the original shorts.
     Also implies COMMON.  */
  முழு short_compare = 0;

  /* Nonzero if this is a right-shift operation, which can be computed on the
     original short and then promoted if the operand is a promoted short.  */
  முழு short_shift = 0;

  /* Nonzero means set RESULT_TYPE to the common type of the args.  */
  முழு common = 0;

  /* True means types are compatible as far as ObjC is concerned.  */
  தருக்க objc_ok;

  /* True means this is an arithmetic operation that may need excess
     precision.  */
  தருக்க may_need_excess_precision;

  /* True means this is a boolean operation that converts both its
     operands to truth-values.  */
  தருக்க boolean_op = பொய்;

  /* Remember whether we're doing / or %.  */
  தருக்க doing_div_or_mod = பொய்;

  /* Remember whether we're doing << or >>.  */
  தருக்க doing_shift = பொய்;

  /* Tree holding instrumentation expression.  */
  மரம் instrument_கோவை = வெற்று;

  எனில் (location == UNKNOWN_LOCATION)
    location = உள்ளீடு_location;

  op0 = orig_op0;
  op1 = orig_op1;

  op0_int_operands = கோவை_INT_CONST_OPERANDS (orig_op0);
  எனில் (op0_int_operands)
    op0 = remove_c_maybe_const_கோவை (op0);
  op1_int_operands = கோவை_INT_CONST_OPERANDS (orig_op1);
  எனில் (op1_int_operands)
    op1 = remove_c_maybe_const_கோவை (op1);
  int_operands = (op0_int_operands && op1_int_operands);
  எனில் (int_operands)
    {
      int_const_or_overflow = (மரம்_CODE (orig_op0) == INTEGER_CST
			       && மரம்_CODE (orig_op1) == INTEGER_CST);
      int_const = (int_const_or_overflow
		   && !மரம்_OVERFLOW (orig_op0)
		   && !மரம்_OVERFLOW (orig_op1));
    }
  இல்லையெனில்
    int_const = int_const_or_overflow = பொய்;

  /* Do not apply default conversion in mixed vector/scalar expression.  */
  எனில் (convert_p
      && VECTOR_TYPE_P (மரம்_TYPE (op0)) == VECTOR_TYPE_P (மரம்_TYPE (op1)))
    {
      op0 = default_conversion (op0);
      op1 = default_conversion (op1);
    }

  orig_type0 = type0 = மரம்_TYPE (op0);

  orig_type1 = type1 = மரம்_TYPE (op1);

  /* The expression codes of the data types of the arguments tell us
     whether the arguments are integers, floating, pointers, etc.  */
  code0 = மரம்_CODE (type0);
  code1 = மரம்_CODE (type1);

  /* Strip NON_LVALUE_EXPRs, etc., since we aren't using as an lvalue.  */
  STRIP_TYPE_NOPS (op0);
  STRIP_TYPE_NOPS (op1);

  /* If an error was already reported for one of the arguments,
     avoid reporting another error.  */

  எனில் (code0 == ERROR_MARK || code1 == ERROR_MARK)
    திரும்பு error_mark_முனை;

  எனில் (code0 == POINTER_TYPE
      && reject_gcc_builtin (op0, கோவை_LOCATION (orig_op0)))
    திரும்பு error_mark_முனை;

  எனில் (code1 == POINTER_TYPE
      && reject_gcc_builtin (op1, கோவை_LOCATION (orig_op1)))
    திரும்பு error_mark_முனை;

  எனில் ((invalid_op_diag
       = targetm.invalid_இருமம்_op (code, type0, type1)))
    {
      error_at (location, invalid_op_diag);
      திரும்பு error_mark_முனை;
    }

  தேர்வு (code)
    {
    நிலை PLUS_கோவை:
    நிலை MINUS_கோவை:
    நிலை MULT_கோவை:
    நிலை TRUNC_DIV_கோவை:
    நிலை CEIL_DIV_கோவை:
    நிலை FLOOR_DIV_கோவை:
    நிலை ROUND_DIV_கோவை:
    நிலை EXACT_DIV_கோவை:
      may_need_excess_precision = உண்மை;
      நிறுத்து;

    நிலை EQ_கோவை:
    நிலை NE_கோவை:
    நிலை LE_கோவை:
    நிலை GE_கோவை:
    நிலை LT_கோவை:
    நிலை GT_கோவை:
      /* Excess precision for implicit conversions of integers to
	 floating point in C11 and later.  */
      may_need_excess_precision = (flag_isoc11
				   && (ANY_INTEGRAL_TYPE_P (type0)
				       || ANY_INTEGRAL_TYPE_P (type1)));
      நிறுத்து;

    இயல்பு:
      may_need_excess_precision = பொய்;
      நிறுத்து;
    }
  எனில் (மரம்_CODE (op0) == EXCESS_PRECISION_கோவை)
    {
      op0 = மரம்_OPERAND (op0, 0);
      type0 = மரம்_TYPE (op0);
    }
  இல்லையெனில் எனில் (may_need_excess_precision
	   && (eptype = excess_precision_type (type0)) != NULL_மரம்)
    {
      type0 = eptype;
      op0 = convert (eptype, op0);
    }
  எனில் (மரம்_CODE (op1) == EXCESS_PRECISION_கோவை)
    {
      op1 = மரம்_OPERAND (op1, 0);
      type1 = மரம்_TYPE (op1);
    }
  இல்லையெனில் எனில் (may_need_excess_precision
	   && (eptype = excess_precision_type (type1)) != NULL_மரம்)
    {
      type1 = eptype;
      op1 = convert (eptype, op1);
    }

  objc_ok = objc_compare_types (type0, type1, -3, NULL_மரம்);

  /* In case when one of the operands of the binary operation is
     a vector and another is a scalar -- convert scalar to vector.  */
  எனில் ((gnu_vector_type_p (type0) && code1 != VECTOR_TYPE)
      || (gnu_vector_type_p (type1) && code0 != VECTOR_TYPE))
    {
      எண்ணிக்கை stv_conv convert_flag = scalar_to_vector (location, code, orig_op0,
						     orig_op1, உண்மை);

      தேர்வு (convert_flag)
	{
	  நிலை stv_error:
	    திரும்பு error_mark_முனை;
	  நிலை stv_firstarg:
	    {
              தருக்க maybe_const = உண்மை;
              மரம் sc;
              sc = c_fully_fold (op0, பொய், &maybe_const);
              sc = save_கோவை (sc);
              sc = convert (மரம்_TYPE (type1), sc);
              op0 = build_vector_from_val (type1, sc);
              எனில் (!maybe_const)
                op0 = c_wrap_maybe_const (op0, உண்மை);
              orig_type0 = type0 = மரம்_TYPE (op0);
              code0 = மரம்_CODE (type0);
              converted = 1;
              நிறுத்து;
	    }
	  நிலை stv_secondarg:
	    {
	      தருக்க maybe_const = உண்மை;
	      மரம் sc;
	      sc = c_fully_fold (op1, பொய், &maybe_const);
	      sc = save_கோவை (sc);
	      sc = convert (மரம்_TYPE (type0), sc);
	      op1 = build_vector_from_val (type0, sc);
	      எனில் (!maybe_const)
		op1 = c_wrap_maybe_const (op1, உண்மை);
	      orig_type1 = type1 = மரம்_TYPE (op1);
	      code1 = மரம்_CODE (type1);
	      converted = 1;
	      நிறுத்து;
	    }
	  இயல்பு:
	    நிறுத்து;
	}
    }

  தேர்வு (code)
    {
    நிலை PLUS_கோவை:
      /* Handle the pointer + int case.  */
      எனில் (code0 == POINTER_TYPE
	  && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  ret = pointer_int_sum (location, PLUS_கோவை, op0, op1);
	  செல் return_build_இருமம்_op;
	}
      இல்லையெனில் எனில் (code1 == POINTER_TYPE
	       && (code0 == INTEGER_TYPE || code0 == BITINT_TYPE))
	{
	  ret = pointer_int_sum (location, PLUS_கோவை, op1, op0);
	  செல் return_build_இருமம்_op;
	}
      இல்லையெனில்
	common = 1;
      நிறுத்து;

    நிலை MINUS_கோவை:
      /* Subtraction of two similar pointers.
	 We must subtract them as integers, then divide by object size.  */
      எனில் (code0 == POINTER_TYPE && code1 == POINTER_TYPE
	  && comp_target_types (location, type0, type1))
	{
	  ret = pointer_diff (location, op0, op1, &instrument_கோவை);
	  செல் return_build_இருமம்_op;
	}
      /* Handle pointer minus int.  Just like pointer plus int.  */
      இல்லையெனில் எனில் (code0 == POINTER_TYPE
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  ret = pointer_int_sum (location, MINUS_கோவை, op0, op1);
	  செல் return_build_இருமம்_op;
	}
      இல்லையெனில்
	common = 1;
      நிறுத்து;

    நிலை MULT_கோவை:
      common = 1;
      நிறுத்து;

    நிலை TRUNC_DIV_கோவை:
    நிலை CEIL_DIV_கோவை:
    நிலை FLOOR_DIV_கோவை:
    நிலை ROUND_DIV_கோவை:
    நிலை EXACT_DIV_கோவை:
      doing_div_or_mod = உண்மை;
      warn_for_div_by_zero (location, op1);

      எனில் ((code0 == INTEGER_TYPE || code0 == REAL_TYPE
	   || code0 == FIXED_POINT_TYPE || code0 == BITINT_TYPE
	   || code0 == COMPLEX_TYPE
	   || gnu_vector_type_p (type0))
	  && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	      || code1 == FIXED_POINT_TYPE || code1 == BITINT_TYPE
	      || code1 == COMPLEX_TYPE
	      || gnu_vector_type_p (type1)))
	{
	  எண்ணிக்கை மரம்_code tcode0 = code0, tcode1 = code1;

	  எனில் (code0 == COMPLEX_TYPE || code0 == VECTOR_TYPE)
	    tcode0 = மரம்_CODE (மரம்_TYPE (மரம்_TYPE (op0)));
	  எனில் (code1 == COMPLEX_TYPE || code1 == VECTOR_TYPE)
	    tcode1 = மரம்_CODE (மரம்_TYPE (மரம்_TYPE (op1)));

	  எனில் (!(((tcode0 == INTEGER_TYPE || tcode0 == BITINT_TYPE
		  || (tcode0 == ENUMERAL_TYPE && code0 == VECTOR_TYPE))
		 && (tcode1 == INTEGER_TYPE || tcode1 == BITINT_TYPE
		     || (tcode1 == ENUMERAL_TYPE && code1 == VECTOR_TYPE)))
		|| (tcode0 == FIXED_POINT_TYPE && tcode1 == FIXED_POINT_TYPE)))
	    resultcode = RDIV_கோவை;
	  இல்லையெனில்
	    /* Although it would be tempting to shorten always here, that
	       loses on some targets, since the modulo instruction is
	       undefined if the quotient can't be represented in the
	       computation mode.  We shorten only if unsigned or if
	       dividing by something we know != -1.  */
	    shorten = may_shorten_divmod (op0, op1);
	  common = 1;
	}
      நிறுத்து;

    நிலை BIT_AND_கோவை:
    நிலை BIT_IOR_கோவை:
    நிலை BIT_XOR_கோவை:
      எனில் ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	shorten = -1;
      /* Allow vector types which are not floating point types.   */
      இல்லையெனில் எனில் (gnu_vector_type_p (type0)
	       && gnu_vector_type_p (type1)
	       && !VECTOR_FLOAT_TYPE_P (type0)
	       && !VECTOR_FLOAT_TYPE_P (type1))
	common = 1;
      நிறுத்து;

    நிலை TRUNC_MOD_கோவை:
    நிலை FLOOR_MOD_கோவை:
      doing_div_or_mod = உண்மை;
      warn_for_div_by_zero (location, op1);

      எனில் (gnu_vector_type_p (type0)
	  && gnu_vector_type_p (type1)
	  && மரம்_CODE (மரம்_TYPE (type0)) == INTEGER_TYPE
	  && மரம்_CODE (மரம்_TYPE (type1)) == INTEGER_TYPE)
	common = 1;
      இல்லையெனில் எனில் ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  /* Although it would be tempting to shorten always here, that loses
	     on some targets, since the modulo instruction is undefined if the
	     quotient can't be represented in the computation mode.  We shorten
	     only if unsigned or if dividing by something we know != -1.  */
	  shorten = may_shorten_divmod (op0, op1);
	  common = 1;
	}
      நிறுத்து;

    நிலை TRUTH_ANDIF_கோவை:
    நிலை TRUTH_ORIF_கோவை:
    நிலை TRUTH_AND_கோவை:
    நிலை TRUTH_OR_கோவை:
    நிலை TRUTH_XOR_கோவை:
      எனில் ((code0 == INTEGER_TYPE || code0 == POINTER_TYPE
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
	  result_type = integer_type_முனை;
	  எனில் (op0_int_operands)
	    {
	      op0 = c_objc_common_truthvalue_conversion (location, orig_op0);
	      op0 = remove_c_maybe_const_கோவை (op0);
	    }
	  இல்லையெனில்
	    op0 = c_objc_common_truthvalue_conversion (location, op0);
	  எனில் (op1_int_operands)
	    {
	      op1 = c_objc_common_truthvalue_conversion (location, orig_op1);
	      op1 = remove_c_maybe_const_கோவை (op1);
	    }
	  இல்லையெனில்
	    op1 = c_objc_common_truthvalue_conversion (location, op1);
	  converted = 1;
	  boolean_op = உண்மை;
	}
      எனில் (code == TRUTH_ANDIF_கோவை)
	{
	  int_const_or_overflow = (int_operands
				   && மரம்_CODE (orig_op0) == INTEGER_CST
				   && (op0 == truthvalue_false_முனை
				       || மரம்_CODE (orig_op1) == INTEGER_CST));
	  int_const = (int_const_or_overflow
		       && !மரம்_OVERFLOW (orig_op0)
		       && (op0 == truthvalue_false_முனை
			   || !மரம்_OVERFLOW (orig_op1)));
	}
      இல்லையெனில் எனில் (code == TRUTH_ORIF_கோவை)
	{
	  int_const_or_overflow = (int_operands
				   && மரம்_CODE (orig_op0) == INTEGER_CST
				   && (op0 == truthvalue_true_முனை
				       || மரம்_CODE (orig_op1) == INTEGER_CST));
	  int_const = (int_const_or_overflow
		       && !மரம்_OVERFLOW (orig_op0)
		       && (op0 == truthvalue_true_முனை
			   || !மரம்_OVERFLOW (orig_op1)));
	}
      நிறுத்து;

      /* Shift operations: result has same type as first operand;
	 always convert second operand to int.
	 Also set SHORT_SHIFT if shifting rightward.  */

    நிலை RSHIFT_கோவை:
      எனில் (gnu_vector_type_p (type0)
	  && gnu_vector_type_p (type1)
	  && மரம்_CODE (மரம்_TYPE (type0)) == INTEGER_TYPE
	  && மரம்_CODE (மரம்_TYPE (type1)) == INTEGER_TYPE
	  && known_eq (TYPE_VECTOR_SUBPARTS (type0),
		       TYPE_VECTOR_SUBPARTS (type1)))
	{
	  result_type = type0;
	  converted = 1;
	}
      இல்லையெனில் எனில் ((code0 == INTEGER_TYPE || code0 == FIXED_POINT_TYPE
		|| code0 == BITINT_TYPE
		|| (gnu_vector_type_p (type0)
		    && மரம்_CODE (மரம்_TYPE (type0)) == INTEGER_TYPE))
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  doing_shift = உண்மை;
	  எனில் (மரம்_CODE (op1) == INTEGER_CST)
	    {
	      எனில் (மரம்_int_cst_sgn (op1) < 0)
		{
		  int_const = பொய்;
		  எனில் (c_inhibit_evaluation_warnings == 0)
		    warning_at (location, OPT_Wshift_மொத்தம்_negative,
				"right shift count is negative");
		}
	      இல்லையெனில் எனில் (code0 == VECTOR_TYPE)
		{
		  எனில் (compare_மரம்_int (op1,
					TYPE_PRECISION (மரம்_TYPE (type0)))
		      >= 0)
		    {
		      int_const = பொய்;
		      எனில் (c_inhibit_evaluation_warnings == 0)
			warning_at (location, OPT_Wshift_மொத்தம்_overflow,
				    "right shift count >= width of vector element");
		    }
		}
	      இல்லையெனில்
		{
		  எனில் (!integer_zerop (op1))
		    short_shift = 1;

		  எனில் (compare_மரம்_int (op1, TYPE_PRECISION (type0)) >= 0)
		    {
		      int_const = பொய்;
		      எனில் (c_inhibit_evaluation_warnings == 0)
			warning_at (location, OPT_Wshift_மொத்தம்_overflow,
				    "right shift count >= width of type");
		    }
		}
	    }

	  /* Use the type of the value to be shifted.  */
	  result_type = type0;
	  /* Avoid converting op1 to result_type later.  */
	  converted = 1;
	}
      நிறுத்து;

    நிலை LSHIFT_கோவை:
      எனில் (gnu_vector_type_p (type0)
	  && gnu_vector_type_p (type1)
	  && மரம்_CODE (மரம்_TYPE (type0)) == INTEGER_TYPE
	  && மரம்_CODE (மரம்_TYPE (type1)) == INTEGER_TYPE
	  && known_eq (TYPE_VECTOR_SUBPARTS (type0),
		       TYPE_VECTOR_SUBPARTS (type1)))
	{
	  result_type = type0;
	  converted = 1;
	}
      இல்லையெனில் எனில் ((code0 == INTEGER_TYPE || code0 == FIXED_POINT_TYPE
		|| code0 == BITINT_TYPE
		|| (gnu_vector_type_p (type0)
		    && மரம்_CODE (மரம்_TYPE (type0)) == INTEGER_TYPE))
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  doing_shift = உண்மை;
	  எனில் (மரம்_CODE (op0) == INTEGER_CST
	      && மரம்_int_cst_sgn (op0) < 0
	      && !TYPE_OVERFLOW_WRAPS (type0))
	    {
	      /* Don't reject a left shift of a negative value in a context
		 where a constant expression is needed in C90.  */
	      எனில் (flag_isoc99)
		int_const = பொய்;
	      எனில் (c_inhibit_evaluation_warnings == 0)
		warning_at (location, OPT_Wshift_negative_மதிப்பு,
			    "left shift of negative value");
	    }
	  எனில் (மரம்_CODE (op1) == INTEGER_CST)
	    {
	      எனில் (மரம்_int_cst_sgn (op1) < 0)
		{
		  int_const = பொய்;
		  எனில் (c_inhibit_evaluation_warnings == 0)
		    warning_at (location, OPT_Wshift_மொத்தம்_negative,
				"left shift count is negative");
		}
	      இல்லையெனில் எனில் (code0 == VECTOR_TYPE)
		{
		  எனில் (compare_மரம்_int (op1,
					TYPE_PRECISION (மரம்_TYPE (type0)))
		      >= 0)
		    {
		      int_const = பொய்;
		      எனில் (c_inhibit_evaluation_warnings == 0)
			warning_at (location, OPT_Wshift_மொத்தம்_overflow,
				    "left shift count >= width of vector element");
		    }
		}
	      இல்லையெனில் எனில் (compare_மரம்_int (op1, TYPE_PRECISION (type0)) >= 0)
		{
		  int_const = பொய்;
		  எனில் (c_inhibit_evaluation_warnings == 0)
		    warning_at (location, OPT_Wshift_மொத்தம்_overflow,
				"left shift count >= width of type");
		}
	      இல்லையெனில் எனில் (மரம்_CODE (op0) == INTEGER_CST
		       && maybe_warn_shift_overflow (location, op0, op1)
		       && flag_isoc99)
		int_const = பொய்;
	    }

	  /* Use the type of the value to be shifted.  */
	  result_type = type0;
	  /* Avoid converting op1 to result_type later.  */
	  converted = 1;
	}
      நிறுத்து;

    நிலை EQ_கோவை:
    நிலை NE_கோவை:
      எனில் (gnu_vector_type_p (type0) && gnu_vector_type_p (type1))
        {
          மரம் intt;
	  எனில் (!vector_types_compatible_elements_p (type0, type1))
            {
              error_at (location, "comparing vectors with different "
                                  "element types");
              திரும்பு error_mark_முனை;
            }

	  எனில் (maybe_ne (TYPE_VECTOR_SUBPARTS (type0),
			TYPE_VECTOR_SUBPARTS (type1)))
            {
              error_at (location, "comparing vectors with different "
                                  "number of elements");
              திரும்பு error_mark_முனை;
            }

	  /* It's not precisely specified how the usual arithmetic
	     conversions apply to the vector types.  Here, we use
	     the unsigned type if one of the operands is signed and
	     the other one is unsigned.  */
	  எனில் (TYPE_UNSIGNED (type0) != TYPE_UNSIGNED (type1))
	    {
	      எனில் (!TYPE_UNSIGNED (type0))
		op0 = build1 (VIEW_CONVERT_கோவை, type1, op0);
	      இல்லையெனில்
		op1 = build1 (VIEW_CONVERT_கோவை, type0, op1);
	      warning_at (location, OPT_Wsign_compare, "comparison between "
			  "types %qT and %qT", type0, type1);
	    }

          /* Always construct signed integer vector type.  */
	  எனில் (VECTOR_BOOLEAN_TYPE_P (type0) && VECTOR_BOOLEAN_TYPE_P (type1))
	    result_type = type0;
	  இல்லையெனில்
	    {
	      auto nelts = TYPE_VECTOR_SUBPARTS (type0);

	      intt = c_common_type_for_size (GET_MODE_BITSIZE
					     (SCALAR_TYPE_MODE
						(மரம்_TYPE (type0))), 0);
	      எனில் (!intt)
		{
		  error_at (location, "could not find an integer type "
				      "of the same size as %qT",
			    மரம்_TYPE (type0));
		  திரும்பு error_mark_முனை;
		}
	      result_type = build_opaque_vector_type (intt, nelts);
	    }
          converted = 1;
	  ret = build_vec_cmp (resultcode, result_type, op0, op1);
	  செல் return_build_இருமம்_op;
        }
      எனில் (FLOAT_TYPE_P (type0) || FLOAT_TYPE_P (type1))
	warning_at (location,
		    OPT_Wfloat_equal,
		    "comparing floating-point with %<==%> or %<!=%> is unsafe");
      /* Result of comparison is always int,
	 but don't convert the args to int!  */
      build_type = integer_type_முனை;
      எனில் ((code0 == INTEGER_TYPE || code0 == REAL_TYPE || code0 == BITINT_TYPE
	   || code0 == FIXED_POINT_TYPE || code0 == COMPLEX_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	      || code1 == BITINT_TYPE
	      || code1 == FIXED_POINT_TYPE || code1 == COMPLEX_TYPE))
	short_compare = 1;
      இல்லையெனில் எனில் (code0 == POINTER_TYPE
	       && (code1 == NULLPTR_TYPE
		   || null_pointer_constant_p (orig_op1)))
	{
	  maybe_warn_for_null_address (location, op0, code);
	  result_type = type0;
	}
      இல்லையெனில் எனில் (code1 == POINTER_TYPE
	       && (code0 == NULLPTR_TYPE
		   || null_pointer_constant_p (orig_op0)))
	{
	  maybe_warn_for_null_address (location, op1, code);
	  result_type = type1;
	}
      இல்லையெனில் எனில் (code0 == POINTER_TYPE && code1 == POINTER_TYPE)
	{
	  மரம் tt0 = மரம்_TYPE (type0);
	  மரம் tt1 = மரம்_TYPE (type1);
	  addr_space_t as0 = TYPE_ADDR_SPACE (tt0);
	  addr_space_t as1 = TYPE_ADDR_SPACE (tt1);
	  addr_space_t as_common = ADDR_SPACE_GENERIC;

	  /* Anything compares with void *.  void * compares with anything.
	     Otherwise, the targets must be compatible
	     and both must be object or both incomplete.  */
	  எனில் (comp_target_types (location, type0, type1))
	    result_type = common_pointer_type (type0, type1, NULL_மரம்);
	  இல்லையெனில் எனில் (!addr_space_superset (as0, as1, &as_common))
	    {
	      error_at (location, "comparison of pointers to "
			"disjoint address spaces");
	      திரும்பு error_mark_முனை;
	    }
	  இல்லையெனில் எனில் (VOID_TYPE_P (tt0) && !TYPE_ATOMIC (tt0))
	    {
	      எனில் (pedantic && மரம்_CODE (tt1) == FUNCTION_TYPE)
		pedwarn (location, OPT_Wpedantic, "ISO C forbids "
			 "comparison of %<void *%> with function pointer");
	    }
	  இல்லையெனில் எனில் (VOID_TYPE_P (tt1) && !TYPE_ATOMIC (tt1))
	    {
	      எனில் (pedantic && மரம்_CODE (tt0) == FUNCTION_TYPE)
		pedwarn (location, OPT_Wpedantic, "ISO C forbids "
			 "comparison of %<void *%> with function pointer");
	    }
	  இல்லையெனில்
	    /* Avoid warning about the volatile ObjC EH puts on decls.  */
	    எனில் (!objc_ok)
	      pedwarn (location, OPT_Wcompare_distinct_pointer_types,
		       "comparison of distinct pointer types lacks a cast");

	  எனில் (result_type == NULL_மரம்)
	    {
	      முழு qual = ENCODE_QUAL_ADDR_SPACE (as_common);
	      result_type = c_build_pointer_type
			      (c_build_qualified_type (void_type_முனை, qual));
	    }
	}
      இல்லையெனில் எனில் (code0 == POINTER_TYPE
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  result_type = type0;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}
      இல்லையெனில் எனில் ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	       && code1 == POINTER_TYPE)
	{
	  result_type = type1;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}
      /* 6.5.9: One of the following shall hold:
	 -- both operands have type nullptr_t;  */
      இல்லையெனில் எனில் (code0 == NULLPTR_TYPE && code1 == NULLPTR_TYPE)
	{
	  result_type = nullptr_type_முனை;
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
      இல்லையெனில் எனில் (code0 == NULLPTR_TYPE && null_pointer_constant_p (orig_op1))
	result_type = (INTEGRAL_TYPE_P (type1)
		       ? c_build_pointer_type (type1) : type1);
      இல்லையெனில் எனில் (code1 == NULLPTR_TYPE && null_pointer_constant_p (orig_op0))
	result_type = (INTEGRAL_TYPE_P (type0)
		       ? c_build_pointer_type (type0) : type0);
      எனில் ((C_BOOLEAN_TYPE_P (மரம்_TYPE (orig_op0))
	   || truth_மதிப்பு_p (மரம்_CODE (orig_op0)))
	  ^ (C_BOOLEAN_TYPE_P (மரம்_TYPE (orig_op1))
	     || truth_மதிப்பு_p (மரம்_CODE (orig_op1))))
	maybe_warn_bool_compare (location, code, orig_op0, orig_op1);
      நிறுத்து;

    நிலை LE_கோவை:
    நிலை GE_கோவை:
    நிலை LT_கோவை:
    நிலை GT_கோவை:
      எனில் (gnu_vector_type_p (type0) && gnu_vector_type_p (type1))
        {
          மரம் intt;
	  எனில் (!vector_types_compatible_elements_p (type0, type1))
            {
              error_at (location, "comparing vectors with different "
                                  "element types");
              திரும்பு error_mark_முனை;
            }

	  எனில் (maybe_ne (TYPE_VECTOR_SUBPARTS (type0),
			TYPE_VECTOR_SUBPARTS (type1)))
            {
              error_at (location, "comparing vectors with different "
                                  "number of elements");
              திரும்பு error_mark_முனை;
            }

	  /* It's not precisely specified how the usual arithmetic
	     conversions apply to the vector types.  Here, we use
	     the unsigned type if one of the operands is signed and
	     the other one is unsigned.  */
	  எனில் (TYPE_UNSIGNED (type0) != TYPE_UNSIGNED (type1))
	    {
	      எனில் (!TYPE_UNSIGNED (type0))
		op0 = build1 (VIEW_CONVERT_கோவை, type1, op0);
	      இல்லையெனில்
		op1 = build1 (VIEW_CONVERT_கோவை, type0, op1);
	      warning_at (location, OPT_Wsign_compare, "comparison between "
			  "types %qT and %qT", type0, type1);
	    }

          /* Always construct signed integer vector type.  */
          intt = c_common_type_for_size (GET_MODE_BITSIZE
					 (SCALAR_TYPE_MODE
					  (மரம்_TYPE (type0))), 0);
	  எனில் (!intt)
	    {
	      error_at (location, "could not find an integer type "
				  "of the same size as %qT",
			மரம்_TYPE (type0));
	      திரும்பு error_mark_முனை;
	    }
          result_type = build_opaque_vector_type (intt,
						  TYPE_VECTOR_SUBPARTS (type0));
          converted = 1;
	  ret = build_vec_cmp (resultcode, result_type, op0, op1);
	  செல் return_build_இருமம்_op;
        }
      build_type = integer_type_முனை;
      எனில் ((code0 == INTEGER_TYPE || code0 == REAL_TYPE
	   || code0 == BITINT_TYPE || code0 == FIXED_POINT_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	      || code1 == BITINT_TYPE || code1 == FIXED_POINT_TYPE))
	short_compare = 1;
      இல்லையெனில் எனில் (code0 == POINTER_TYPE && code1 == POINTER_TYPE)
	{
	  addr_space_t as0 = TYPE_ADDR_SPACE (மரம்_TYPE (type0));
	  addr_space_t as1 = TYPE_ADDR_SPACE (மரம்_TYPE (type1));
	  addr_space_t as_common;

	  எனில் (comp_target_types (location, type0, type1))
	    {
	      result_type = common_pointer_type (type0, type1, NULL_மரம்);
	      எனில் (!COMPLETE_TYPE_P (மரம்_TYPE (type0))
		  != !COMPLETE_TYPE_P (மரம்_TYPE (type1)))
		pedwarn_c99 (location, OPT_Wpedantic,
			     "comparison of complete and incomplete pointers");
	      இல்லையெனில் எனில் (மரம்_CODE (மரம்_TYPE (type0)) == FUNCTION_TYPE)
		pedwarn (location, OPT_Wpedantic, "ISO C forbids "
			 "ordered comparisons of pointers to functions");
	      இல்லையெனில் எனில் (null_pointer_constant_p (orig_op0)
		       || null_pointer_constant_p (orig_op1))
		warning_at (location, OPT_Wextra,
			    "ordered comparison of pointer with null pointer");

	    }
	  இல்லையெனில் எனில் (!addr_space_superset (as0, as1, &as_common))
	    {
	      error_at (location, "comparison of pointers to "
			"disjoint address spaces");
	      திரும்பு error_mark_முனை;
	    }
	  இல்லையெனில்
	    {
	      முழு qual = ENCODE_QUAL_ADDR_SPACE (as_common);
	      result_type = c_build_pointer_type
			      (c_build_qualified_type (void_type_முனை, qual));
              pedwarn (location, OPT_Wcompare_distinct_pointer_types,
                       "comparison of distinct pointer types lacks a cast");
	    }
	}
      இல்லையெனில் எனில் (code0 == POINTER_TYPE && null_pointer_constant_p (orig_op1))
	{
	  result_type = type0;
	  எனில் (pedantic)
	    pedwarn (location, OPT_Wpedantic,
		     "ordered comparison of pointer with integer zero");
	  இல்லையெனில் எனில் (extra_warnings)
	    warning_at (location, OPT_Wextra,
			"ordered comparison of pointer with integer zero");
	}
      இல்லையெனில் எனில் (code1 == POINTER_TYPE && null_pointer_constant_p (orig_op0))
	{
	  result_type = type1;
	  எனில் (pedantic)
	    pedwarn (location, OPT_Wpedantic,
		     "ordered comparison of pointer with integer zero");
	  இல்லையெனில் எனில் (extra_warnings)
	    warning_at (location, OPT_Wextra,
			"ordered comparison of pointer with integer zero");
	}
      இல்லையெனில் எனில் (code0 == POINTER_TYPE
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  result_type = type0;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}
      இல்லையெனில் எனில் ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	       && code1 == POINTER_TYPE)
	{
	  result_type = type1;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}

      எனில் ((code0 == POINTER_TYPE || code1 == POINTER_TYPE)
	  && current_function_decl != NULL_மரம்
	  && sanitize_flags_p (SANITIZE_POINTER_COMPARE))
	{
	  op0 = save_கோவை (c_fully_fold (op0, பொய், வெற்று));
	  op1 = save_கோவை (c_fully_fold (op1, பொய், வெற்று));

	  மரம் tt = builtin_decl_explicit (BUILT_IN_ASAN_POINTER_COMPARE);
	  instrument_கோவை = build_call_கோவை_loc (location, tt, 2, op0, op1);
	}

      எனில் ((C_BOOLEAN_TYPE_P (மரம்_TYPE (orig_op0))
	   || truth_மதிப்பு_p (மரம்_CODE (orig_op0)))
	  ^ (C_BOOLEAN_TYPE_P (மரம்_TYPE (orig_op1))
	     || truth_மதிப்பு_p (மரம்_CODE (orig_op1))))
	maybe_warn_bool_compare (location, code, orig_op0, orig_op1);
      நிறுத்து;

    நிலை MIN_கோவை:
    நிலை MAX_கோவை:
      /* Used for OpenMP atomics.  */
      gcc_assert (flag_openmp);
      common = 1;
      நிறுத்து;

    இயல்பு:
      gcc_unreachable ();
    }

  எனில் (code0 == ERROR_MARK || code1 == ERROR_MARK)
    திரும்பு error_mark_முனை;

  எனில் (gnu_vector_type_p (type0)
      && gnu_vector_type_p (type1)
      && (!மரம்_int_cst_equal (TYPE_SIZE (type0), TYPE_SIZE (type1))
	  || !vector_types_compatible_elements_p (type0, type1)))
    {
      gcc_rich_location richloc (location);
      maybe_range_label_for_மரம்_type_mismatch
	label_for_op0 (orig_op0, orig_op1),
	label_for_op1 (orig_op1, orig_op0);
      richloc.maybe_add_கோவை (orig_op0, &label_for_op0, highlight_colors::lhs);
      richloc.maybe_add_கோவை (orig_op1, &label_for_op1, highlight_colors::rhs);
      இருமம்_op_error (&richloc, code, type0, type1);
      திரும்பு error_mark_முனை;
    }

  எனில் ((code0 == INTEGER_TYPE || code0 == REAL_TYPE || code0 == COMPLEX_TYPE
       || code0 == FIXED_POINT_TYPE || code0 == BITINT_TYPE
       || gnu_vector_type_p (type0))
      && (code1 == INTEGER_TYPE || code1 == REAL_TYPE || code1 == COMPLEX_TYPE
	  || code1 == FIXED_POINT_TYPE || code1 == BITINT_TYPE
	  || gnu_vector_type_p (type1)))
    {
      தருக்க first_complex = (code0 == COMPLEX_TYPE);
      தருக்க second_complex = (code1 == COMPLEX_TYPE);
      முழு none_complex = (!first_complex && !second_complex);

      எனில் (shorten || common || short_compare)
	{
	  result_type = c_common_type (type0, type1);
	  do_warn_double_promotion (result_type, type0, type1,
				    "implicit conversion from %qT to %qT "
				    "to match other operand of binary "
				    "expression",
				    location);
	  எனில் (result_type == error_mark_முனை)
	    திரும்பு error_mark_முனை;
	}

      எனில் (first_complex != second_complex
	  && (code == PLUS_கோவை
	      || code == MINUS_கோவை
	      || code == MULT_கோவை
	      || (code == TRUNC_DIV_கோவை && first_complex))
	  && மரம்_CODE (மரம்_TYPE (result_type)) == REAL_TYPE
	  && flag_signed_zeros)
	{
	  /* An operation on mixed real/complex operands must be
	     handled specially, but the language-independent code can
	     more easily optimize the plain complex arithmetic if
	     -fno-signed-zeros.  */
	  மரம் real_type = மரம்_TYPE (result_type);
	  மரம் real, imag;
	  எனில் (type0 != orig_type0 || type1 != orig_type1)
	    {
	      gcc_assert (may_need_excess_precision && common);
	      semantic_result_type = c_common_type (orig_type0, orig_type1);
	    }
	  எனில் (first_complex)
	    {
	      எனில் (மரம்_TYPE (op0) != result_type)
		op0 = convert_and_check (location, result_type, op0);
	      எனில் (மரம்_TYPE (op1) != real_type)
		op1 = convert_and_check (location, real_type, op1);
	    }
	  இல்லையெனில்
	    {
	      எனில் (மரம்_TYPE (op0) != real_type)
		op0 = convert_and_check (location, real_type, op0);
	      எனில் (மரம்_TYPE (op1) != result_type)
		op1 = convert_and_check (location, result_type, op1);
	    }
	  எனில் (மரம்_CODE (op0) == ERROR_MARK || மரம்_CODE (op1) == ERROR_MARK)
	    திரும்பு error_mark_முனை;
	  எனில் (first_complex)
	    {
	      op0 = save_கோவை (op0);
	      real = build_unary_op (கோவை_LOCATION (orig_op0), REALPART_கோவை,
				     op0, உண்மை);
	      imag = build_unary_op (கோவை_LOCATION (orig_op0), IMAGPART_கோவை,
				     op0, உண்மை);
	      தேர்வு (code)
		{
		நிலை MULT_கோவை:
		நிலை TRUNC_DIV_கோவை:
		  op1 = save_கோவை (op1);
		  imag = build2 (resultcode, real_type, imag, op1);
		  /* Fall through.  */
		நிலை PLUS_கோவை:
		நிலை MINUS_கோவை:
		  real = build2 (resultcode, real_type, real, op1);
		  நிறுத்து;
		இயல்பு:
		  gcc_unreachable();
		}
	    }
	  இல்லையெனில்
	    {
	      op1 = save_கோவை (op1);
	      real = build_unary_op (கோவை_LOCATION (orig_op1), REALPART_கோவை,
				     op1, உண்மை);
	      imag = build_unary_op (கோவை_LOCATION (orig_op1), IMAGPART_கோவை,
				     op1, உண்மை);
	      தேர்வு (code)
		{
		நிலை MULT_கோவை:
		  op0 = save_கோவை (op0);
		  imag = build2 (resultcode, real_type, op0, imag);
		  /* Fall through.  */
		நிலை PLUS_கோவை:
		  real = build2 (resultcode, real_type, op0, real);
		  நிறுத்து;
		நிலை MINUS_கோவை:
		  real = build2 (resultcode, real_type, op0, real);
		  imag = build1 (NEGATE_கோவை, real_type, imag);
		  நிறுத்து;
		இயல்பு:
		  gcc_unreachable();
		}
	    }
	  ret = build2 (COMPLEX_கோவை, result_type, real, imag);
	  செல் return_build_இருமம்_op;
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

      எனில் (shorten && none_complex)
	{
	  final_type = result_type;
	  result_type = shorten_இருமம்_op (result_type, op0, op1,
					   shorten == -1);
	}

      /* Shifts can be shortened if shifting right.  */

      எனில் (short_shift)
	{
	  முழு unsigned_arg;
	  மரம் arg0 = get_narrower (op0, &unsigned_arg);

	  final_type = result_type;

	  எனில் (arg0 == op0 && final_type == மரம்_TYPE (op0))
	    unsigned_arg = TYPE_UNSIGNED (மரம்_TYPE (op0));

	  எனில் (TYPE_PRECISION (மரம்_TYPE (arg0)) < TYPE_PRECISION (result_type)
	      && மரம்_int_cst_sgn (op1) > 0
	      /* We can shorten only if the shift count is less than the
		 number of bits in the smaller type size.  */
	      && compare_மரம்_int (op1, TYPE_PRECISION (மரம்_TYPE (arg0))) < 0
	      /* We cannot drop an unsigned shift after sign-extension.  */
	      && (!TYPE_UNSIGNED (final_type) || unsigned_arg))
	    {
	      /* Do an unsigned shift if the operand was zero-extended.  */
	      result_type
		= c_common_signed_or_unsigned_type (unsigned_arg,
						    மரம்_TYPE (arg0));
	      /* Convert value-to-be-shifted to that type.  */
	      எனில் (மரம்_TYPE (op0) != result_type)
		op0 = convert (result_type, op0);
	      converted = 1;
	    }
	}

      /* Comparison operations are shortened too but differently.
	 They identify themselves by setting short_compare = 1.  */

      எனில் (short_compare)
	{
	  /* Don't write &op0, etc., because that would prevent op0
	     from being kept in a register.
	     Instead, make copies of the our local variables and
	     pass the copies by reference, then copy them back afterward.  */
	  மரம் xop0 = op0, xop1 = op1, xresult_type = result_type;
	  எண்ணிக்கை மரம்_code xresultcode = resultcode;
	  மரம் val
	    = shorten_compare (location, &xop0, &xop1, &xresult_type,
			       &xresultcode);

	  எனில் (val != NULL_மரம்)
	    {
	      ret = val;
	      செல் return_build_இருமம்_op;
	    }

	  op0 = xop0, op1 = xop1;
	  converted = 1;
	  resultcode = xresultcode;

	  எனில் (c_inhibit_evaluation_warnings == 0 && !c_in_omp_for)
	    {
	      தருக்க op0_maybe_const = உண்மை;
	      தருக்க op1_maybe_const = உண்மை;
	      மரம் orig_op0_folded, orig_op1_folded;

	      எனில் (in_late_இருமம்_op)
		{
		  orig_op0_folded = orig_op0;
		  orig_op1_folded = orig_op1;
		}
	      இல்லையெனில்
		{
		  /* Fold for the sake of possible warnings, as in
		     build_conditional_expr.  This requires the
		     "original" values to be folded, not just op0 and
		     op1.  */
		  c_inhibit_evaluation_warnings++;
		  op0 = c_fully_fold (op0, require_constant_மதிப்பு,
				      &op0_maybe_const);
		  op1 = c_fully_fold (op1, require_constant_மதிப்பு,
				      &op1_maybe_const);
		  c_inhibit_evaluation_warnings--;
		  orig_op0_folded = c_fully_fold (orig_op0,
						  require_constant_மதிப்பு,
						  வெற்று);
		  orig_op1_folded = c_fully_fold (orig_op1,
						  require_constant_மதிப்பு,
						  வெற்று);
		}

	      எனில் (warn_sign_compare)
		warn_for_sign_compare (location, orig_op0_folded,
				       orig_op1_folded, op0, op1,
				       result_type, resultcode);
	      எனில் (!in_late_இருமம்_op && !int_operands)
		{
		  எனில் (!op0_maybe_const || மரம்_CODE (op0) != INTEGER_CST)
		    op0 = c_wrap_maybe_const (op0, !op0_maybe_const);
		  எனில் (!op1_maybe_const || மரம்_CODE (op1) != INTEGER_CST)
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

  எனில் (!result_type)
    {
      /* Favor showing any expression locations that are available. */
      op_location_t oploc (location, UNKNOWN_LOCATION);
      இருமம்_op_rich_location richloc (oploc, orig_op0, orig_op1, உண்மை);
      இருமம்_op_error (&richloc, code, மரம்_TYPE (op0), மரம்_TYPE (op1));
      திரும்பு error_mark_முனை;
    }

  எனில் (build_type == NULL_மரம்)
    {
      build_type = result_type;
      எனில் ((type0 != orig_type0 || type1 != orig_type1)
	  && !boolean_op)
	{
	  gcc_assert (may_need_excess_precision && common);
	  semantic_result_type = c_common_type (orig_type0, orig_type1);
	}
    }

  எனில் (!converted)
    {
      op0 = ep_convert_and_check (location, result_type, op0,
				  semantic_result_type);
      op1 = ep_convert_and_check (location, result_type, op1,
				  semantic_result_type);

      /* This can happen if one operand has a vector type, and the other
	 has a different type.  */
      எனில் (மரம்_CODE (op0) == ERROR_MARK || மரம்_CODE (op1) == ERROR_MARK)
	திரும்பு error_mark_முனை;
    }

  எனில் (sanitize_flags_p ((SANITIZE_SHIFT
			 | SANITIZE_DIVIDE
			 | SANITIZE_FLOAT_DIVIDE
			 | SANITIZE_SI_OVERFLOW))
      && current_function_decl != NULL_மரம்
      && (doing_div_or_mod || doing_shift)
      && !require_constant_மதிப்பு)
    {
      /* OP0 and/or OP1 might have side-effects.  */
      op0 = save_கோவை (op0);
      op1 = save_கோவை (op1);
      op0 = c_fully_fold (op0, பொய், வெற்று);
      op1 = c_fully_fold (op1, பொய், வெற்று);
      எனில் (doing_div_or_mod && (sanitize_flags_p ((SANITIZE_DIVIDE
						  | SANITIZE_FLOAT_DIVIDE
						  | SANITIZE_SI_OVERFLOW))))
	instrument_கோவை = ubsan_instrument_division (location, op0, op1);
      இல்லையெனில் எனில் (doing_shift && sanitize_flags_p (SANITIZE_SHIFT))
	instrument_கோவை = ubsan_instrument_shift (location, code, op0, op1);
    }

  /* Treat expressions in initializers specially as they can't trap.  */
  எனில் (int_const_or_overflow)
    ret = (require_constant_மதிப்பு
	   ? fold_build2_initializer_loc (location, resultcode, build_type,
					  op0, op1)
	   : fold_build2_loc (location, resultcode, build_type, op0, op1));
  இல்லையெனில்
    ret = build2 (resultcode, build_type, op0, op1);
  எனில் (final_type != NULL_மரம்)
    ret = convert (final_type, ret);

 return_build_இருமம்_op:
  gcc_assert (ret != error_mark_முனை);
  எனில் (மரம்_CODE (ret) == INTEGER_CST && !மரம்_OVERFLOW (ret) && !int_const)
    ret = (int_operands
	   ? note_integer_operands (ret)
	   : build1 (NOP_கோவை, மரம்_TYPE (ret), ret));
  இல்லையெனில் எனில் (மரம்_CODE (ret) != INTEGER_CST && int_operands
	   && !in_late_இருமம்_op)
    ret = note_integer_operands (ret);
  protected_set_கோவை_location (ret, location);

  எனில் (instrument_கோவை != வெற்று)
    ret = fold_build2 (COMPOUND_கோவை, மரம்_TYPE (ret),
		       instrument_கோவை, ret);

  எனில் (semantic_result_type)
    ret = build1_loc (location, EXCESS_PRECISION_கோவை,
		      semantic_result_type, ret);

  திரும்பு ret;
}


/* Convert EXPR to be a truth-value (type TYPE), validating its type for this
   purpose.  LOCATION is the source location for the expression.  */

மரம்
c_objc_common_truthvalue_conversion (location_t location, மரம் கோவை, மரம் type)
{
  தருக்க int_const, int_operands;

  தேர்வு (மரம்_CODE (மரம்_TYPE (கோவை)))
    {
    நிலை ARRAY_TYPE:
      error_at (location, "used array that cannot be converted to pointer where scalar is required");
      திரும்பு error_mark_முனை;

    நிலை RECORD_TYPE:
      error_at (location, "used struct type value where scalar is required");
      திரும்பு error_mark_முனை;

    நிலை UNION_TYPE:
      error_at (location, "used union type value where scalar is required");
      திரும்பு error_mark_முனை;

    நிலை VOID_TYPE:
      error_at (location, "void value not ignored as it ought to be");
      திரும்பு error_mark_முனை;

    நிலை POINTER_TYPE:
      எனில் (reject_gcc_builtin (கோவை))
	திரும்பு error_mark_முனை;
      நிறுத்து;

    நிலை FUNCTION_TYPE:
      gcc_unreachable ();

    நிலை VECTOR_TYPE:
      error_at (location, "used vector type where scalar is required");
      திரும்பு error_mark_முனை;

    இயல்பு:
      நிறுத்து;
    }

  /* Conversion of a floating constant to boolean goes through here
     and yields an integer constant expression.  Otherwise, the result
     is only an integer constant expression if the argument is.  */
  int_const = ((மரம்_CODE (கோவை) == INTEGER_CST && !மரம்_OVERFLOW (கோவை))
	       || ((மரம்_CODE (கோவை) == REAL_CST
		    || மரம்_CODE (கோவை) == COMPLEX_CST)
		   && (மரம்_CODE (type) == BOOLEAN_TYPE
		       || (மரம்_CODE (type) == ENUMERAL_TYPE
			   && ENUM_UNDERLYING_TYPE (type) != NULL_மரம்
			   && (மரம்_CODE (ENUM_UNDERLYING_TYPE (type))
			       == BOOLEAN_TYPE)))));
  int_operands = கோவை_INT_CONST_OPERANDS (கோவை);
  எனில் (int_operands && மரம்_CODE (கோவை) != INTEGER_CST)
    {
      கோவை = remove_c_maybe_const_கோவை (கோவை);
      கோவை = build2 (NE_கோவை, type, கோவை,
		     convert (மரம்_TYPE (கோவை), integer_zero_முனை));
      கோவை = note_integer_operands (கோவை);
    }
  இல்லையெனில்
    {
      /* ??? Should we also give an error for vectors rather than leaving
	 those to give errors later?  */
      கோவை = c_common_truthvalue_conversion (location, கோவை);
      கோவை = fold_convert_loc (location, type, கோவை);
    }

  எனில் (மரம்_CODE (கோவை) == INTEGER_CST && int_operands && !int_const)
    {
      எனில் (மரம்_OVERFLOW (கோவை))
	திரும்பு கோவை;
      இல்லையெனில்
	திரும்பு note_integer_operands (கோவை);
    }
  எனில் (மரம்_CODE (கோவை) == INTEGER_CST && !int_const)
    திரும்பு build1 (NOP_கோவை, மரம்_TYPE (கோவை), கோவை);
  திரும்பு கோவை;
}


/* Convert EXPR to a contained DECL, updating *TC, *TI and *SE as
   required.  */

மரம்
c_கோவை_to_decl (மரம் கோவை, தருக்க *tc ATTRIBUTE_UNUSED, தருக்க *se)
{
  எனில் (மரம்_CODE (கோவை) == COMPOUND_LITERAL_கோவை)
    {
      மரம் decl = COMPOUND_LITERAL_கோவை_DECL (கோவை);
      /* Executing a compound literal inside a function reinitializes
	 it.  */
      எனில் (!மரம்_STATIC (decl))
	*se = உண்மை;
      திரும்பு decl;
    }
  இல்லையெனில்
    திரும்பு கோவை;
}

/* Generate OMP construct CODE, with BODY and CLAUSES as its compound
   statement.  LOC is the location of the construct.  */

மரம்
c_finish_omp_construct (location_t loc, எண்ணிக்கை மரம்_code code, மரம் body,
			மரம் clauses)
{
  body = c_end_compound_stmt (loc, body, உண்மை);

  மரம் stmt = make_முனை (code);
  மரம்_TYPE (stmt) = void_type_முனை;
  OMP_BODY (stmt) = body;
  OMP_CLAUSES (stmt) = clauses;
  SET_கோவை_LOCATION (stmt, loc);

  திரும்பு add_stmt (stmt);
}

/* Generate OACC_DATA, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the OACC_DATA.  */

மரம்
c_finish_oacc_data (location_t loc, மரம் clauses, மரம் block)
{
  மரம் stmt;

  block = c_end_compound_stmt (loc, block, உண்மை);

  stmt = make_முனை (OACC_DATA);
  மரம்_TYPE (stmt) = void_type_முனை;
  OACC_DATA_CLAUSES (stmt) = clauses;
  OACC_DATA_BODY (stmt) = block;
  SET_கோவை_LOCATION (stmt, loc);

  திரும்பு add_stmt (stmt);
}

/* Generate OACC_HOST_DATA, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the OACC_HOST_DATA.  */

மரம்
c_finish_oacc_host_data (location_t loc, மரம் clauses, மரம் block)
{
  மரம் stmt;

  block = c_end_compound_stmt (loc, block, உண்மை);

  stmt = make_முனை (OACC_HOST_DATA);
  மரம்_TYPE (stmt) = void_type_முனை;
  OACC_HOST_DATA_CLAUSES (stmt) = clauses;
  OACC_HOST_DATA_BODY (stmt) = block;
  SET_கோவை_LOCATION (stmt, loc);

  திரும்பு add_stmt (stmt);
}

/* Like c_begin_compound_stmt, except force the retention of the BLOCK.  */

மரம்
c_begin_omp_parallel (வெறுமை)
{
  மரம் block;

  keep_next_level ();
  block = c_begin_compound_stmt (உண்மை);

  திரும்பு block;
}

/* Generate OMP_PARALLEL, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the OMP_PARALLEL.  */

மரம்
c_finish_omp_parallel (location_t loc, மரம் clauses, மரம் block)
{
  மரம் stmt;

  block = c_end_compound_stmt (loc, block, உண்மை);

  stmt = make_முனை (OMP_PARALLEL);
  மரம்_TYPE (stmt) = void_type_முனை;
  OMP_PARALLEL_CLAUSES (stmt) = clauses;
  OMP_PARALLEL_BODY (stmt) = block;
  SET_கோவை_LOCATION (stmt, loc);

  திரும்பு add_stmt (stmt);
}

/* Like c_begin_compound_stmt, except force the retention of the BLOCK.  */

மரம்
c_begin_omp_task (வெறுமை)
{
  மரம் block;

  keep_next_level ();
  block = c_begin_compound_stmt (உண்மை);

  திரும்பு block;
}

/* Generate OMP_TASK, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the #pragma.  */

மரம்
c_finish_omp_task (location_t loc, மரம் clauses, மரம் block)
{
  மரம் stmt;

  block = c_end_compound_stmt (loc, block, உண்மை);

  stmt = make_முனை (OMP_TASK);
  மரம்_TYPE (stmt) = void_type_முனை;
  OMP_TASK_CLAUSES (stmt) = clauses;
  OMP_TASK_BODY (stmt) = block;
  SET_கோவை_LOCATION (stmt, loc);

  திரும்பு add_stmt (stmt);
}

/* Generate GOMP_cancel call for #pragma omp cancel.  */

வெறுமை
c_finish_omp_cancel (location_t loc, மரம் clauses)
{
  மரம் fn = builtin_decl_explicit (BUILT_IN_GOMP_CANCEL);
  முழு mask = 0;
  எனில் (omp_find_clause (clauses, OMP_CLAUSE_PARALLEL))
    mask = 1;
  இல்லையெனில் எனில் (omp_find_clause (clauses, OMP_CLAUSE_FOR))
    mask = 2;
  இல்லையெனில் எனில் (omp_find_clause (clauses, OMP_CLAUSE_SECTIONS))
    mask = 4;
  இல்லையெனில் எனில் (omp_find_clause (clauses, OMP_CLAUSE_TASKGROUP))
    mask = 8;
  இல்லையெனில்
    {
      error_at (loc, "%<#pragma omp cancel%> must specify one of "
		     "%<parallel%>, %<for%>, %<sections%> or %<taskgroup%> "
		     "clauses");
      திரும்பு;
    }
  மரம் ifc = omp_find_clause (clauses, OMP_CLAUSE_IF);
  எனில் (ifc != NULL_மரம்)
    {
      எனில் (OMP_CLAUSE_IF_MODIFIER (ifc) != ERROR_MARK
	  && OMP_CLAUSE_IF_MODIFIER (ifc) != VOID_CST)
	error_at (OMP_CLAUSE_LOCATION (ifc),
		  "expected %<cancel%> %<if%> clause modifier");
      இல்லையெனில்
	{
	  மரம் ifc2 = omp_find_clause (OMP_CLAUSE_CHAIN (ifc), OMP_CLAUSE_IF);
	  எனில் (ifc2 != NULL_மரம்)
	    {
	      gcc_assert (OMP_CLAUSE_IF_MODIFIER (ifc) == VOID_CST
			  && OMP_CLAUSE_IF_MODIFIER (ifc2) != ERROR_MARK
			  && OMP_CLAUSE_IF_MODIFIER (ifc2) != VOID_CST);
	      error_at (OMP_CLAUSE_LOCATION (ifc2),
			"expected %<cancel%> %<if%> clause modifier");
	    }
	}

      மரம் type = மரம்_TYPE (OMP_CLAUSE_IF_கோவை (ifc));
      ifc = fold_build2_loc (OMP_CLAUSE_LOCATION (ifc), NE_கோவை,
			     boolean_type_முனை, OMP_CLAUSE_IF_கோவை (ifc),
			     build_zero_cst (type));
    }
  இல்லையெனில்
    ifc = boolean_true_முனை;
  மரம் stmt = build_call_கோவை_loc (loc, fn, 2,
				   build_int_cst (integer_type_முனை, mask),
				   ifc);
  add_stmt (stmt);
}

/* Generate GOMP_cancellation_point call for
   #pragma omp cancellation point.  */

வெறுமை
c_finish_omp_cancellation_point (location_t loc, மரம் clauses)
{
  மரம் fn = builtin_decl_explicit (BUILT_IN_GOMP_CANCELLATION_POINT);
  முழு mask = 0;
  எனில் (omp_find_clause (clauses, OMP_CLAUSE_PARALLEL))
    mask = 1;
  இல்லையெனில் எனில் (omp_find_clause (clauses, OMP_CLAUSE_FOR))
    mask = 2;
  இல்லையெனில் எனில் (omp_find_clause (clauses, OMP_CLAUSE_SECTIONS))
    mask = 4;
  இல்லையெனில் எனில் (omp_find_clause (clauses, OMP_CLAUSE_TASKGROUP))
    mask = 8;
  இல்லையெனில்
    {
      error_at (loc, "%<#pragma omp cancellation point%> must specify one of "
		     "%<parallel%>, %<for%>, %<sections%> or %<taskgroup%> "
		     "clauses");
      திரும்பு;
    }
  மரம் stmt = build_call_கோவை_loc (loc, fn, 1,
				   build_int_cst (integer_type_முனை, mask));
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

நிலையான மரம்
handle_omp_array_sections_1 (மரம் c, மரம் t, vec<மரம்> &types,
			     தருக்க &maybe_zero_len, unsigned முழு &first_non_one,
			     எண்ணிக்கை c_omp_region_type ort)
{
  மரம் ret, கீழ்_bound, length, type;
  தருக்க openacc = (ort & C_ORT_ACC) != 0;
  எனில் (மரம்_CODE (t) != OMP_ARRAY_SECTION)
    {
      எனில் (error_operand_p (t))
	திரும்பு error_mark_முனை;
      c_omp_address_inspector ai (OMP_CLAUSE_LOCATION (c), t);
      ret = t;
      எனில் (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
	  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
	  && TYPE_ATOMIC (strip_array_types (மரம்_TYPE (t))))
	{
	  error_at (OMP_CLAUSE_LOCATION (c), "%<_Atomic%> %qE in %qs clause",
		    t, omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  திரும்பு error_mark_முனை;
	}
      எனில் (!ai.check_clause (c))
	திரும்பு error_mark_முனை;
      இல்லையெனில் எனில் (ai.component_access_p ()
	       && (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TO
		   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_FROM))
	t = ai.get_வேர்_term (உண்மை);
      இல்லையெனில்
	t = ai.unconverted_ref_origin ();
      எனில் (t == error_mark_முனை)
	திரும்பு error_mark_முனை;
      எனில் (!VAR_P (t)
	  && (ort == C_ORT_ACC || !கோவை_P (t))
	  && மரம்_CODE (t) != PARM_DECL)
	{
	  எனில் (DECL_P (t))
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD is not a variable in %qs clause", t,
		      omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  இல்லையெனில்
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qE is not a variable in %qs clause", t,
		      omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  திரும்பு error_mark_முனை;
	}
      இல்லையெனில் எனில் (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
	       && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
	       && TYPE_ATOMIC (மரம்_TYPE (t)))
	{
	  error_at (OMP_CLAUSE_LOCATION (c), "%<_Atomic%> %qD in %qs clause",
		    t, omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  திரும்பு error_mark_முனை;
	}
      இல்லையெனில் எனில் (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
	       && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
	       && VAR_P (t)
	       && DECL_THREAD_LOCAL_P (t))
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "%qD is threadprivate variable in %qs clause", t,
		    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  திரும்பு error_mark_முனை;
	}
      எனில் ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY
	   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND)
	  && TYPE_ATOMIC (மரம்_TYPE (t))
	  && POINTER_TYPE_P (மரம்_TYPE (t)))
	{
	  /* If the array section is pointer based and the pointer
	     itself is _Atomic qualified, we need to atomically load
	     the pointer.  */
	  ret = convert_lvalue_to_rvalue (OMP_CLAUSE_LOCATION (c),
					  ret, பொய், பொய்);
	}
      திரும்பு ret;
    }

  ret = handle_omp_array_sections_1 (c, மரம்_OPERAND (t, 0), types,
				     maybe_zero_len, first_non_one, ort);
  எனில் (ret == error_mark_முனை || ret == NULL_மரம்)
    திரும்பு ret;

  type = மரம்_TYPE (ret);
  கீழ்_bound = மரம்_OPERAND (t, 1);
  length = மரம்_OPERAND (t, 2);

  எனில் (கீழ்_bound == error_mark_முனை || length == error_mark_முனை)
    திரும்பு error_mark_முனை;

  எனில் (கீழ்_bound && !INTEGRAL_TYPE_P (மரம்_TYPE (கீழ்_bound)))
    {
      error_at (OMP_CLAUSE_LOCATION (c),
		"low bound %qE of array section does not have integral type",
		கீழ்_bound);
      திரும்பு error_mark_முனை;
    }
  எனில் (length && !INTEGRAL_TYPE_P (மரம்_TYPE (length)))
    {
      error_at (OMP_CLAUSE_LOCATION (c),
		"length %qE of array section does not have integral type",
		length);
      திரும்பு error_mark_முனை;
    }
  எனில் (கீழ்_bound
      && மரம்_CODE (கீழ்_bound) == INTEGER_CST
      && TYPE_PRECISION (மரம்_TYPE (கீழ்_bound))
	 > TYPE_PRECISION (sizetype))
    கீழ்_bound = fold_convert (sizetype, கீழ்_bound);
  எனில் (length
      && மரம்_CODE (length) == INTEGER_CST
      && TYPE_PRECISION (மரம்_TYPE (length))
	 > TYPE_PRECISION (sizetype))
    length = fold_convert (sizetype, length);
  எனில் (கீழ்_bound == NULL_மரம்)
    கீழ்_bound = integer_zero_முனை;
  எனில் (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
      && (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_ATTACH
	  || OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_DETACH))
    {
      எனில் (length != integer_one_முனை)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "expected single pointer in %qs clause",
		    user_omp_clause_code_name (c, openacc));
	  திரும்பு error_mark_முனை;
	}
    }
  எனில் (length != NULL_மரம்)
    {
      எனில் (!integer_nonzerop (length))
	{
	  எனில் (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY
	      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
	      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
	      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
	      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TASK_REDUCTION)
	    {
	      எனில் (integer_zerop (length))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "zero length array section in %qs clause",
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  திரும்பு error_mark_முனை;
		}
	    }
	  இல்லையெனில்
	    maybe_zero_len = உண்மை;
	}
      எனில் (first_non_one == types.length ()
	  && (மரம்_CODE (length) != INTEGER_CST || integer_onep (length)))
	first_non_one++;
    }
  எனில் (மரம்_CODE (type) == ARRAY_TYPE)
    {
      எனில் (length == NULL_மரம்
	  && (TYPE_DOMAIN (type) == NULL_மரம்
	      || TYPE_MAX_மதிப்பு (TYPE_DOMAIN (type)) == NULL_மரம்))
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "for unknown bound array type length expression must "
		    "be specified");
	  திரும்பு error_mark_முனை;
	}
      எனில் (மரம்_CODE (கீழ்_bound) == INTEGER_CST
	  && மரம்_int_cst_sgn (கீழ்_bound) == -1)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "negative low bound in array section in %qs clause",
		    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  திரும்பு error_mark_முனை;
	}
      எனில் (length != NULL_மரம்
	  && மரம்_CODE (length) == INTEGER_CST
	  && மரம்_int_cst_sgn (length) == -1)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "negative length in array section in %qs clause",
		    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  திரும்பு error_mark_முனை;
	}
      எனில் (TYPE_DOMAIN (type)
	  && TYPE_MAX_மதிப்பு (TYPE_DOMAIN (type))
	  && மரம்_CODE (TYPE_MAX_மதிப்பு (TYPE_DOMAIN (type)))
			== INTEGER_CST)
	{
	  மரம் size
	    = fold_convert (sizetype, TYPE_MAX_மதிப்பு (TYPE_DOMAIN (type)));
	  size = size_binop (PLUS_கோவை, size, size_one_முனை);
	  எனில் (மரம்_CODE (கீழ்_bound) == INTEGER_CST)
	    {
	      எனில் (மரம்_int_cst_lt (size, கீழ்_bound))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "low bound %qE above array section size "
			    "in %qs clause", கீழ்_bound,
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  திரும்பு error_mark_முனை;
		}
	      எனில் (மரம்_int_cst_equal (size, கீழ்_bound))
		{
		  எனில் (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TASK_REDUCTION)
		    {
		      error_at (OMP_CLAUSE_LOCATION (c),
				"zero length array section in %qs clause",
				omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		      திரும்பு error_mark_முனை;
		    }
		  maybe_zero_len = உண்மை;
		}
	      இல்லையெனில் எனில் (length == NULL_மரம்
		       && first_non_one == types.length ()
		       && மரம்_int_cst_equal
			    (TYPE_MAX_மதிப்பு (TYPE_DOMAIN (type)),
			     கீழ்_bound))
		first_non_one++;
	    }
	  இல்லையெனில் எனில் (length == NULL_மரம்)
	    {
	      எனில் (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
		  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
		  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_REDUCTION
		  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_IN_REDUCTION
		  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_TASK_REDUCTION)
		maybe_zero_len = உண்மை;
	      எனில் (first_non_one == types.length ())
		first_non_one++;
	    }
	  எனில் (length && மரம்_CODE (length) == INTEGER_CST)
	    {
	      எனில் (மரம்_int_cst_lt (size, length))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "length %qE above array section size "
			    "in %qs clause", length,
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  திரும்பு error_mark_முனை;
		}
	      எனில் (மரம்_CODE (கீழ்_bound) == INTEGER_CST)
		{
		  மரம் lbpluslen
		    = size_binop (PLUS_கோவை,
				  fold_convert (sizetype, கீழ்_bound),
				  fold_convert (sizetype, length));
		  எனில் (மரம்_CODE (lbpluslen) == INTEGER_CST
		      && மரம்_int_cst_lt (size, lbpluslen))
		    {
		      error_at (OMP_CLAUSE_LOCATION (c),
				"high bound %qE above array section size "
				"in %qs clause", lbpluslen,
				omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		      திரும்பு error_mark_முனை;
		    }
		}
	    }
	}
      இல்லையெனில் எனில் (length == NULL_மரம்)
	{
	  எனில் (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
	      && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
	      && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_REDUCTION
	      && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_IN_REDUCTION
	      && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_TASK_REDUCTION)
	    maybe_zero_len = உண்மை;
	  எனில் (first_non_one == types.length ())
	    first_non_one++;
	}

      /* For [lb:] we will need to evaluate lb more than once.  */
      எனில் (length == NULL_மரம் && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND)
	{
	  மரம் lb = save_கோவை (கீழ்_bound);
	  எனில் (lb != கீழ்_bound)
	    {
	      மரம்_OPERAND (t, 1) = lb;
	      கீழ்_bound = lb;
	    }
	}
    }
  இல்லையெனில் எனில் (மரம்_CODE (type) == POINTER_TYPE)
    {
      எனில் (length == NULL_மரம்)
	{
	  எனில் (மரம்_CODE (ret) == PARM_DECL && C_ARRAY_PARAMETER (ret))
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "for array function parameter length expression "
		      "must be specified");
	  இல்லையெனில்
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "for pointer type length expression must be specified");
	  திரும்பு error_mark_முனை;
	}
      எனில் (length != NULL_மரம்
	  && மரம்_CODE (length) == INTEGER_CST
	  && மரம்_int_cst_sgn (length) == -1)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "negative length in array section in %qs clause",
		    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  திரும்பு error_mark_முனை;
	}
      /* If there is a pointer type anywhere but in the very first
	 array-section-subscript, the array section could be non-contiguous.  */
      எனில் (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
	  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
	  && மரம்_CODE (மரம்_OPERAND (t, 0)) == OMP_ARRAY_SECTION)
	{
	  /* If any prior dimension has a non-one length, then deem this
	     array section as non-contiguous.  */
	  க்கு (மரம் d = மரம்_OPERAND (t, 0);
	       மரம்_CODE (d) == OMP_ARRAY_SECTION;
	       d = மரம்_OPERAND (d, 0))
	    {
	      மரம் d_length = மரம்_OPERAND (d, 2);
	      எனில் (d_length == NULL_மரம் || !integer_onep (d_length))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "array section is not contiguous in %qs clause",
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  திரும்பு error_mark_முனை;
		}
	    }
	}
    }
  இல்லையெனில்
    {
      error_at (OMP_CLAUSE_LOCATION (c),
		"%qE does not have pointer or array type", ret);
      திரும்பு error_mark_முனை;
    }
  எனில் (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND)
    types.safe_தள்ளு (மரம்_TYPE (ret));
  /* We will need to evaluate lb more than once.  */
  மரம் lb = save_கோவை (கீழ்_bound);
  எனில் (lb != கீழ்_bound)
    {
      மரம்_OPERAND (t, 1) = lb;
      கீழ்_bound = lb;
    }
  ret = build_array_ref (OMP_CLAUSE_LOCATION (c), ret, கீழ்_bound);
  திரும்பு ret;
}

/* Handle array sections for clause C.  */

நிலையான தருக்க
handle_omp_array_sections (மரம் &c, எண்ணிக்கை c_omp_region_type ort)
{
  தருக்க maybe_zero_len = பொய்;
  unsigned முழு first_non_one = 0;
  auto_vec<மரம், 10> types;
  மரம் *tp = &OMP_CLAUSE_DECL (c);
  எனில் ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
       || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY)
      && OMP_ITERATOR_DECL_P (*tp))
    tp = &மரம்_மதிப்பு (*tp);
  மரம் first = handle_omp_array_sections_1 (c, *tp, types,
					    maybe_zero_len, first_non_one,
					    ort);
  எனில் (first == error_mark_முனை)
    திரும்பு உண்மை;
  எனில் (first == NULL_மரம்)
    திரும்பு பொய்;
  எனில் (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY)
    {
      மரம் t = *tp;
      மரம் tem = NULL_மரம்;
      /* Need to evaluate side effects in the length expressions
	 if any.  */
      போது (மரம்_CODE (t) == மரம்_LIST)
	{
	  எனில் (மரம்_மதிப்பு (t) && மரம்_SIDE_EFFECTS (மரம்_மதிப்பு (t)))
	    {
	      எனில் (tem == NULL_மரம்)
		tem = மரம்_மதிப்பு (t);
	      இல்லையெனில்
		tem = build2 (COMPOUND_கோவை, மரம்_TYPE (tem),
			      மரம்_மதிப்பு (t), tem);
	    }
	  t = மரம்_CHAIN (t);
	}
      எனில் (tem)
	first = build2 (COMPOUND_கோவை, மரம்_TYPE (first), tem, first);
      first = c_fully_fold (first, பொய், வெற்று, உண்மை);
      *tp = first;
    }
  இல்லையெனில்
    {
      unsigned முழு இலக்கம் = types.length (), i;
      மரம் t, side_effects = NULL_மரம், size = NULL_மரம்;
      மரம் condition = NULL_மரம்;

      எனில் (int_size_in_bytes (மரம்_TYPE (first)) <= 0)
	maybe_zero_len = உண்மை;

      க்கு (i = இலக்கம், t = OMP_CLAUSE_DECL (c); i > 0;
	   t = மரம்_OPERAND (t, 0))
	{
	  மரம் கீழ்_bound = மரம்_OPERAND (t, 1);
	  மரம் length = மரம்_OPERAND (t, 2);

	  i--;
	  எனில் (கீழ்_bound
	      && மரம்_CODE (கீழ்_bound) == INTEGER_CST
	      && TYPE_PRECISION (மரம்_TYPE (கீழ்_bound))
		 > TYPE_PRECISION (sizetype))
	    கீழ்_bound = fold_convert (sizetype, கீழ்_bound);
	  எனில் (length
	      && மரம்_CODE (length) == INTEGER_CST
	      && TYPE_PRECISION (மரம்_TYPE (length))
		 > TYPE_PRECISION (sizetype))
	    length = fold_convert (sizetype, length);
	  எனில் (கீழ்_bound == NULL_மரம்)
	    கீழ்_bound = integer_zero_முனை;
	  எனில் (!maybe_zero_len && i > first_non_one)
	    {
	      எனில் (integer_nonzerop (கீழ்_bound))
		செல் do_warn_noncontiguous;
	      எனில் (length != NULL_மரம்
		  && மரம்_CODE (length) == INTEGER_CST
		  && TYPE_DOMAIN (types[i])
		  && TYPE_MAX_மதிப்பு (TYPE_DOMAIN (types[i]))
		  && மரம்_CODE (TYPE_MAX_மதிப்பு (TYPE_DOMAIN (types[i])))
		     == INTEGER_CST)
		{
		  மரம் size;
		  size = size_binop (PLUS_கோவை,
				     TYPE_MAX_மதிப்பு (TYPE_DOMAIN (types[i])),
				     size_one_முனை);
		  எனில் (!மரம்_int_cst_equal (length, size))
		    {
		     do_warn_noncontiguous:
		      error_at (OMP_CLAUSE_LOCATION (c),
				"array section is not contiguous in %qs "
				"clause",
				omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		      திரும்பு உண்மை;
		    }
		}
	      எனில் (length != NULL_மரம்
		  && மரம்_SIDE_EFFECTS (length))
		{
		  எனில் (side_effects == NULL_மரம்)
		    side_effects = length;
		  இல்லையெனில்
		    side_effects = build2 (COMPOUND_கோவை,
					   மரம்_TYPE (side_effects),
					   length, side_effects);
		}
	    }
	  இல்லையெனில்
	    {
	      மரம் l;

	      எனில் (i > first_non_one
		  && ((length && integer_nonzerop (length))
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TASK_REDUCTION))
		தொடர்;
	      எனில் (length)
		l = fold_convert (sizetype, length);
	      இல்லையெனில்
		{
		  l = size_binop (PLUS_கோவை,
				  TYPE_MAX_மதிப்பு (TYPE_DOMAIN (types[i])),
				  size_one_முனை);
		  l = size_binop (MINUS_கோவை, l,
				  fold_convert (sizetype, கீழ்_bound));
		}
	      எனில் (i > first_non_one)
		{
		  l = fold_build2 (NE_கோவை, boolean_type_முனை, l,
				   size_zero_முனை);
		  எனில் (condition == NULL_மரம்)
		    condition = l;
		  இல்லையெனில்
		    condition = fold_build2 (BIT_AND_கோவை, boolean_type_முனை,
					     l, condition);
		}
	      இல்லையெனில் எனில் (size == NULL_மரம்)
		{
		  size = size_in_bytes (மரம்_TYPE (types[i]));
		  மரம் eltype = மரம்_TYPE (types[இலக்கம் - 1]);
		  போது (மரம்_CODE (eltype) == ARRAY_TYPE)
		    eltype = மரம்_TYPE (eltype);
		  எனில் (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TASK_REDUCTION)
		    {
		      எனில் (integer_zerop (size)
			  || integer_zerop (size_in_bytes (eltype)))
			{
			  error_at (OMP_CLAUSE_LOCATION (c),
				    "zero length array section in %qs clause",
				    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
			  திரும்பு error_mark_முனை;
			}
		      size = size_binop (EXACT_DIV_கோவை, size,
					 size_in_bytes (eltype));
		    }
		  size = size_binop (MULT_கோவை, size, l);
		  எனில் (condition)
		    size = fold_build3 (COND_கோவை, sizetype, condition,
					size, size_zero_முனை);
		}
	      இல்லையெனில்
		size = size_binop (MULT_கோவை, size, l);
	    }
	}
      எனில் (side_effects)
	size = build2 (COMPOUND_கோவை, sizetype, side_effects, size);
      எனில் (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
	  || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
	  || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TASK_REDUCTION)
	{
	  size = size_binop (MINUS_கோவை, size, size_one_முனை);
	  size = c_fully_fold (size, பொய், வெற்று);
	  size = save_கோவை (size);
	  மரம் index_type = build_index_type (size);
	  மரம் eltype = மரம்_TYPE (first);
	  போது (மரம்_CODE (eltype) == ARRAY_TYPE)
	    eltype = மரம்_TYPE (eltype);
	  மரம் type = c_build_array_type (eltype, index_type);
	  மரம் ptype = c_build_pointer_type (eltype);
	  எனில் (மரம்_CODE (மரம்_TYPE (t)) == ARRAY_TYPE)
	    t = build_fold_addr_கோவை (t);
	  மரம் t2 = build_fold_addr_கோவை (first);
	  t2 = fold_convert_loc (OMP_CLAUSE_LOCATION (c),
				 ptrdiff_type_முனை, t2);
	  t2 = fold_build2_loc (OMP_CLAUSE_LOCATION (c), MINUS_கோவை,
				ptrdiff_type_முனை, t2,
				fold_convert_loc (OMP_CLAUSE_LOCATION (c),
						  ptrdiff_type_முனை, t));
	  t2 = c_fully_fold (t2, பொய், வெற்று);
	  எனில் (மரம்_fits_shwi_p (t2))
	    t = build2 (MEM_REF, type, t,
			build_int_cst (ptype, மரம்_to_shwi (t2)));
	  இல்லையெனில்
	    {
	      t2 = fold_convert_loc (OMP_CLAUSE_LOCATION (c), sizetype, t2);
	      t = build2_loc (OMP_CLAUSE_LOCATION (c), POINTER_PLUS_கோவை,
			      மரம்_TYPE (t), t, t2);
	      t = build2 (MEM_REF, type, t, build_int_cst (ptype, 0));
	    }
	  OMP_CLAUSE_DECL (c) = t;
	  திரும்பு பொய்;
	}
      first = c_fully_fold (first, பொய், வெற்று);
      OMP_CLAUSE_DECL (c) = first;
      எனில் (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_HAS_DEVICE_ADDR)
	திரும்பு பொய்;
      /* Don't set OMP_CLAUSE_SIZE for bare attach/detach clauses.  */
      எனில் (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP
	  || (OMP_CLAUSE_MAP_KIND (c) != GOMP_MAP_ATTACH
	      && OMP_CLAUSE_MAP_KIND (c) != GOMP_MAP_DETACH
	      && OMP_CLAUSE_MAP_KIND (c) != GOMP_MAP_FORCE_DETACH))
	{
	  எனில் (size)
	    size = c_fully_fold (size, பொய், வெற்று);
	  OMP_CLAUSE_SIZE (c) = size;
	}

      எனில் (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP)
	திரும்பு பொய்;

      auto_vec<omp_addr_token *, 10> addr_tokens;

      எனில் (!omp_parse_கோவை (addr_tokens, first))
	திரும்பு உண்மை;

      c_omp_address_inspector ai (OMP_CLAUSE_LOCATION (c), t);

      மரம் nc = ai.expand_map_clause (c, first, addr_tokens, ort);
      எனில் (nc != error_mark_முனை)
	{
	  using நாமாகாஶ omp_addr_tokenizer;

	  எனில் (ai.maybe_zero_length_array_section (c))
	    OMP_CLAUSE_MAP_MAYBE_ZERO_LENGTH_ARRAY_SECTION (c) = 1;

	  /* !!! If we're accessing a base decl via chained access
	     methods (e.g. multiple indirections), duplicate clause
	     detection won't work properly.  Skip it in that case.  */
	  எனில் ((addr_tokens[0]->type == STRUCTURE_BASE
	       || addr_tokens[0]->type == ARRAY_BASE)
	      && addr_tokens[0]->u.structure_base_kind == BASE_DECL
	      && addr_tokens[1]->type == ACCESS_METHOD
	      && omp_access_chain_p (addr_tokens, 1))
	    c = nc;

	  திரும்பு பொய்;
	}
    }
  திரும்பு பொய்;
}

/* Helper function of finish_omp_clauses.  Clone STMT as if we were making
   an inline call.  But, remap
   the OMP_DECL1 VAR_DECL (omp_out resp. omp_orig) to PLACEHOLDER
   and OMP_DECL2 VAR_DECL (omp_in resp. omp_priv) to DECL.  */

நிலையான மரம்
c_clone_omp_udr (மரம் stmt, மரம் omp_decl1, மரம் omp_decl2,
		 மரம் decl, மரம் placeholder)
{
  copy_body_data id;
  hash_map<மரம், மரம்> decl_map;

  decl_map.put (omp_decl1, placeholder);
  decl_map.put (omp_decl2, decl);
  memset (&id, 0, அளவு (id));
  id.src_fn = DECL_CONTEXT (omp_decl1);
  id.dst_fn = current_function_decl;
  id.src_cfun = DECL_STRUCT_FUNCTION (id.src_fn);
  id.decl_map = &decl_map;

  id.copy_decl = copy_decl_no_change;
  id.transform_call_graph_edges = CB_CGE_DUPLICATE;
  id.transform_new_cfg = உண்மை;
  id.transform_return_to_modify = பொய்;
  id.eh_lp_nr = 0;
  walk_மரம் (&stmt, copy_மரம்_body_r, &id, வெற்று);
  திரும்பு stmt;
}

/* Helper function of c_finish_omp_clauses, called via walk_tree.
   Find OMP_CLAUSE_PLACEHOLDER (passed in DATA) in *TP.  */

நிலையான மரம்
c_find_omp_placeholder_r (மரம் *tp, முழு *, வெறுமை *data)
{
  எனில் (*tp == (மரம்) data)
    திரும்பு *tp;
  திரும்பு NULL_மரம்;
}

/* Similarly, but also walk aggregate fields.  */

கட்டமைப்பு c_find_omp_var_s { மரம் var; hash_set<மரம்> *pset; };

நிலையான மரம்
c_find_omp_var_r (மரம் *tp, முழு *, வெறுமை *data)
{
  எனில் (*tp == ((கட்டமைப்பு c_find_omp_var_s *) data)->var)
    திரும்பு *tp;
  எனில் (RECORD_OR_UNION_TYPE_P (*tp))
    {
      மரம் field;
      hash_set<மரம்> *pset = ((கட்டமைப்பு c_find_omp_var_s *) data)->pset;

      க்கு (field = TYPE_FIELDS (*tp); field;
	   field = DECL_CHAIN (field))
	எனில் (மரம்_CODE (field) == FIELD_DECL)
	  {
	    மரம் ret = walk_மரம் (&DECL_FIELD_OFFSET (field),
				  c_find_omp_var_r, data, pset);
	    எனில் (ret)
	      திரும்பு ret;
	    ret = walk_மரம் (&DECL_SIZE (field), c_find_omp_var_r, data, pset);
	    எனில் (ret)
	      திரும்பு ret;
	    ret = walk_மரம் (&DECL_SIZE_UNIT (field), c_find_omp_var_r, data,
			     pset);
	    எனில் (ret)
	      திரும்பு ret;
	    ret = walk_மரம் (&மரம்_TYPE (field), c_find_omp_var_r, data, pset);
	    எனில் (ret)
	      திரும்பு ret;
	  }
    }
  இல்லையெனில் எனில் (INTEGRAL_TYPE_P (*tp))
    திரும்பு walk_மரம் (&TYPE_MAX_மதிப்பு (*tp), c_find_omp_var_r, data,
		      ((கட்டமைப்பு c_find_omp_var_s *) data)->pset);
  திரும்பு NULL_மரம்;
}

/* Finish OpenMP iterators ITER.  Return true if they are erroneous
   and clauses containing them should be removed.  */

நிலையான தருக்க
c_omp_finish_iterators (மரம் iter)
{
  தருக்க ret = பொய்;
  க்கு (மரம் it = iter; it; it = மரம்_CHAIN (it))
    {
      மரம் var = OMP_ITERATOR_VAR (it);
      மரம் begin = OMP_ITERATOR_BEGIN (it);
      மரம் end = OMP_ITERATOR_END (it);
      மரம் step = OMP_ITERATOR_STEP (it);
      மரம் orig_step;
      மரம் type = மரம்_TYPE (var);
      location_t loc = DECL_SOURCE_LOCATION (var);
      எனில் (type == error_mark_முனை)
	{
	  ret = உண்மை;
	  தொடர்;
	}
      எனில் (!INTEGRAL_TYPE_P (type) && !POINTER_TYPE_P (type))
	{
	  error_at (loc, "iterator %qD has neither integral nor pointer type",
		    var);
	  ret = உண்மை;
	  தொடர்;
	}
      இல்லையெனில் எனில் (TYPE_ATOMIC (type))
	{
	  error_at (loc, "iterator %qD has %<_Atomic%> qualified type", var);
	  ret = உண்மை;
	  தொடர்;
	}
      இல்லையெனில் எனில் (TYPE_READONLY (type))
	{
	  error_at (loc, "iterator %qD has const qualified type", var);
	  ret = உண்மை;
	  தொடர்;
	}
      இல்லையெனில் எனில் (step == error_mark_முனை
	       || மரம்_TYPE (step) == error_mark_முனை)
	{
	  ret = உண்மை;
	  தொடர்;
	}
      இல்லையெனில் எனில் (!INTEGRAL_TYPE_P (மரம்_TYPE (step)))
	{
	  error_at (கோவை_LOC_OR_LOC (step, loc),
		    "iterator step with non-integral type");
	  ret = உண்மை;
	  தொடர்;
	}
      begin = c_fully_fold (build_c_cast (loc, type, begin), பொய், வெற்று);
      end = c_fully_fold (build_c_cast (loc, type, end), பொய், வெற்று);
      orig_step = save_கோவை (c_fully_fold (step, பொய், வெற்று));
      மரம் stype = POINTER_TYPE_P (type) ? sizetype : type;
      step = c_fully_fold (build_c_cast (loc, stype, orig_step), பொய், வெற்று);
      எனில் (POINTER_TYPE_P (type))
	{
	  begin = save_கோவை (begin);
	  step = pointer_int_sum (loc, PLUS_கோவை, begin, step);
	  step = fold_build2_loc (loc, MINUS_கோவை, sizetype,
				  fold_convert (sizetype, step),
				  fold_convert (sizetype, begin));
	  step = fold_convert (ssizetype, step);
	}
      எனில் (integer_zerop (step))
	{
	  error_at (loc, "iterator %qD has zero step", var);
	  ret = உண்மை;
	  தொடர்;
	}

      எனில் (begin == error_mark_முனை
	  || end == error_mark_முனை
	  || step == error_mark_முனை
	  || orig_step == error_mark_முனை)
	{
	  ret = உண்மை;
	  தொடர்;
	}
      hash_set<மரம்> pset;
      மரம் it2;
      க்கு (it2 = மரம்_CHAIN (it); it2; it2 = மரம்_CHAIN (it2))
	{
	  மரம் var2 = OMP_ITERATOR_VAR (it2);
	  மரம் begin2 = OMP_ITERATOR_BEGIN (it2);
	  மரம் end2 = OMP_ITERATOR_END (it2);
	  மரம் step2 = OMP_ITERATOR_STEP (it2);
	  மரம் type2 = மரம்_TYPE (var2);
	  location_t loc2 = DECL_SOURCE_LOCATION (var2);
	  கட்டமைப்பு c_find_omp_var_s data = { var, &pset };
	  எனில் (walk_மரம் (&type2, c_find_omp_var_r, &data, &pset))
	    {
	      error_at (loc2,
			"type of iterator %qD refers to outer iterator %qD",
			var2, var);
	      நிறுத்து;
	    }
	  இல்லையெனில் எனில் (walk_மரம் (&begin2, c_find_omp_var_r, &data, &pset))
	    {
	      error_at (கோவை_LOC_OR_LOC (begin2, loc2),
			"begin expression refers to outer iterator %qD", var);
	      நிறுத்து;
	    }
	  இல்லையெனில் எனில் (walk_மரம் (&end2, c_find_omp_var_r, &data, &pset))
	    {
	      error_at (கோவை_LOC_OR_LOC (end2, loc2),
			"end expression refers to outer iterator %qD", var);
	      நிறுத்து;
	    }
	  இல்லையெனில் எனில் (walk_மரம் (&step2, c_find_omp_var_r, &data, &pset))
	    {
	      error_at (கோவை_LOC_OR_LOC (step2, loc2),
			"step expression refers to outer iterator %qD", var);
	      நிறுத்து;
	    }
	}
      எனில் (it2)
	{
	  ret = உண்மை;
	  தொடர்;
	}
      OMP_ITERATOR_BEGIN (it) = begin;
      OMP_ITERATOR_END (it) = end;
      OMP_ITERATOR_STEP (it) = step;
      OMP_ITERATOR_ORIG_STEP (it) = orig_step;
    }
  திரும்பு ret;
}

/* Ensure that pointers are used in OpenACC attach and detach clauses.
   Return true if an error has been detected.  */

நிலையான தருக்க
c_oacc_check_attachments (மரம் c)
{
  எனில் (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP)
    திரும்பு பொய்;

  /* OpenACC attach / detach clauses must be pointers.  */
  எனில் (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_ATTACH
      || OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_DETACH)
    {
      மரம் t = OMP_CLAUSE_DECL (c);

      போது (மரம்_CODE (t) == OMP_ARRAY_SECTION)
	t = மரம்_OPERAND (t, 0);

      எனில் (மரம்_CODE (மரம்_TYPE (t)) != POINTER_TYPE)
	{
	  error_at (OMP_CLAUSE_LOCATION (c), "expected pointer in %qs clause",
		    user_omp_clause_code_name (c, உண்மை));
	  திரும்பு உண்மை;
	}
    }

  திரும்பு பொய்;
}

/* For all elements of CLAUSES, validate them against their constraints.
   Remove any elements from the list that are invalid.  */

மரம்
c_finish_omp_clauses (மரம் clauses, எண்ணிக்கை c_omp_region_type ort)
{
  bitmap_head generic_head, firstprivate_head, lastprivate_head;
  bitmap_head aligned_head, map_head, map_field_head, map_firstprivate_head;
  bitmap_head oacc_reduction_head, is_on_device_head;
  மரம் c, t, type, *pc;
  மரம் simdlen = NULL_மரம், safelen = NULL_மரம்;
  தருக்க branch_seen = பொய்;
  தருக்க copyprivate_seen = பொய்;
  தருக்க mergeable_seen = பொய்;
  மரம் *detach_seen = வெற்று;
  தருக்க linear_variable_step_check = பொய்;
  மரம் *nowait_clause = வெற்று;
  மரம் *grainsize_seen = வெற்று;
  தருக்க இலக்கம்_tasks_seen = பொய்;
  மரம் ordered_clause = NULL_மரம்;
  மரம் schedule_clause = NULL_மரம்;
  தருக்க oacc_async = பொய்;
  மரம் last_iterators = NULL_மரம்;
  தருக்க last_iterators_remove = பொய்;
  மரம் *nogroup_seen = வெற்று;
  மரம் *order_clause = வெற்று;
  /* 1 if normal/task reduction has been seen, -1 if inscan reduction
     has been seen, -2 if mixed inscan/normal reduction diagnosed.  */
  முழு reduction_seen = 0;
  தருக்க allocate_seen = பொய்;
  தருக்க implicit_moved = பொய்;
  தருக்க target_in_reduction_seen = பொய்;
  மரம் *full_seen = வெற்று;
  தருக்க partial_seen = பொய்;
  தருக்க openacc = (ort & C_ORT_ACC) != 0;
  தருக்க init_seen = பொய்;
  தருக்க init_use_destroy_seen = பொய்;
  மரம் init_no_targetsync_clause = NULL_மரம்;
  மரம் depend_clause = NULL_மரம்;

  எனில் (!openacc)
    clauses = omp_remove_duplicate_maps (clauses, உண்மை);

  bitmap_obstack_initialize (வெற்று);
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

  எனில் (openacc)
    க்கு (c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
      எனில் (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ASYNC)
	{
	  oacc_async = உண்மை;
	  நிறுத்து;
	}

  மரம் *grp_start_p = வெற்று, grp_sentinel = NULL_மரம்;

  க்கு (pc = &clauses, c = clauses; c ; c = *pc)
    {
      தருக்க remove = பொய்;
      தருக்க need_complete = பொய்;
      தருக்க need_implicitly_determined = பொய்;

      /* We've reached the end of a list of expanded nodes.  Reset the group
	 start pointer.  */
      எனில் (c == grp_sentinel)
	{
	  எனில் (grp_start_p
	      && OMP_CLAUSE_HAS_ITERATORS (*grp_start_p))
	    க்கு (மரம் gc = *grp_start_p; gc != grp_sentinel;
		 gc = OMP_CLAUSE_CHAIN (gc))
	      OMP_CLAUSE_ITERATORS (gc) = OMP_CLAUSE_ITERATORS (*grp_start_p);
	  grp_start_p = வெற்று;
	}

      தேர்வு (OMP_CLAUSE_CODE (c))
	{
	நிலை OMP_CLAUSE_SHARED:
	  need_implicitly_determined = உண்மை;
	  செல் check_dup_generic;

	நிலை OMP_CLAUSE_PRIVATE:
	  need_complete = உண்மை;
	  need_implicitly_determined = உண்மை;
	  செல் check_dup_generic;

	நிலை OMP_CLAUSE_REDUCTION:
	  எனில் (reduction_seen == 0)
	    reduction_seen = OMP_CLAUSE_REDUCTION_INSCAN (c) ? -1 : 1;
	  இல்லையெனில் எனில் (reduction_seen != -2
		   && reduction_seen != (OMP_CLAUSE_REDUCTION_INSCAN (c)
					 ? -1 : 1))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<inscan%> and non-%<inscan%> %<reduction%> clauses "
			"on the same construct");
	      reduction_seen = -2;
	    }
	  /* FALLTHRU */
	நிலை OMP_CLAUSE_IN_REDUCTION:
	நிலை OMP_CLAUSE_TASK_REDUCTION:
	  need_implicitly_determined = உண்மை;
	  t = OMP_CLAUSE_DECL (c);
	  எனில் (மரம்_CODE (t) == OMP_ARRAY_SECTION)
	    {
	      எனில் (handle_omp_array_sections (c, ort))
		{
		  remove = உண்மை;
		  நிறுத்து;
		}

	      t = OMP_CLAUSE_DECL (c);
	      எனில் (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
		  && OMP_CLAUSE_REDUCTION_INSCAN (c))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<inscan%> %<reduction%> clause with array "
			    "section");
		  remove = உண்மை;
		  நிறுத்து;
		}
	    }
	  t = require_complete_type (OMP_CLAUSE_LOCATION (c), t);
	  எனில் (t == error_mark_முனை)
	    {
	      remove = உண்மை;
	      நிறுத்து;
	    }
	  எனில் (oacc_async)
	    c_mark_addressable (t);
	  type = மரம்_TYPE (t);
	  எனில் (மரம்_CODE (t) == MEM_REF)
	    type = மரம்_TYPE (type);
	  எனில் (மரம்_CODE (type) == ARRAY_TYPE)
	    {
	      மரம் oatype = type;
	      gcc_assert (மரம்_CODE (t) != MEM_REF);
	      போது (மரம்_CODE (type) == ARRAY_TYPE)
		type = மரம்_TYPE (type);
	      எனில் (integer_zerop (TYPE_SIZE_UNIT (type)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD in %<reduction%> clause is a zero size array",
			    t);
		  remove = உண்மை;
		  நிறுத்து;
		}
	      மரம் size = size_binop (EXACT_DIV_கோவை, TYPE_SIZE_UNIT (oatype),
				      TYPE_SIZE_UNIT (type));
	      எனில் (integer_zerop (size))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD in %<reduction%> clause is a zero size array",
			    t);
		  remove = உண்மை;
		  நிறுத்து;
		}
	      size = size_binop (MINUS_கோவை, size, size_one_முனை);
	      size = save_கோவை (size);
	      மரம் index_type = build_index_type (size);
	      மரம் atype = c_build_array_type (TYPE_MAIN_VARIANT (type),
					       index_type);
	      atype = c_build_qualified_type (atype, TYPE_QUALS (type));
	      மரம் ptype = c_build_pointer_type (type);
	      எனில் (மரம்_CODE (மரம்_TYPE (t)) == ARRAY_TYPE)
		t = build_fold_addr_கோவை (t);
	      t = build2 (MEM_REF, atype, t, build_int_cst (ptype, 0));
	      OMP_CLAUSE_DECL (c) = t;
	    }
	  எனில் (TYPE_ATOMIC (type))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<_Atomic%> %qE in %<reduction%> clause", t);
	      remove = உண்மை;
	      நிறுத்து;
	    }
	  எனில் (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_REDUCTION
	      || OMP_CLAUSE_REDUCTION_TASK (c))
	    {
	      /* Disallow zero sized or potentially zero sized task
		 reductions.  */
	      எனில் (integer_zerop (TYPE_SIZE_UNIT (type)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "zero sized type %qT in %qs clause", type,
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  remove = உண்மை;
		  நிறுத்து;
		}
	      இல்லையெனில் எனில் (மரம்_CODE (TYPE_SIZE_UNIT (type)) != INTEGER_CST)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "variable sized type %qT in %qs clause", type,
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  remove = உண்மை;
		  நிறுத்து;
		}
	    }
	  எனில் (OMP_CLAUSE_REDUCTION_PLACEHOLDER (c) == NULL_மரம்
	      && (FLOAT_TYPE_P (type)
		  || மரம்_CODE (type) == COMPLEX_TYPE))
	    {
	      எண்ணிக்கை மரம்_code r_code = OMP_CLAUSE_REDUCTION_CODE (c);
	      மாறிலி எழுத்து *r_name = வெற்று;

	      தேர்வு (r_code)
		{
		நிலை PLUS_கோவை:
		நிலை MULT_கோவை:
		நிலை MINUS_கோவை:
		நிலை TRUTH_ANDIF_கோவை:
		நிலை TRUTH_ORIF_கோவை:
		  நிறுத்து;
		நிலை MIN_கோவை:
		  எனில் (மரம்_CODE (type) == COMPLEX_TYPE)
		    r_name = "min";
		  நிறுத்து;
		நிலை MAX_கோவை:
		  எனில் (மரம்_CODE (type) == COMPLEX_TYPE)
		    r_name = "max";
		  நிறுத்து;
		நிலை BIT_AND_கோவை:
		  r_name = "&";
		  நிறுத்து;
		நிலை BIT_XOR_கோவை:
		  r_name = "^";
		  நிறுத்து;
		நிலை BIT_IOR_கோவை:
		  r_name = "|";
		  நிறுத்து;
		இயல்பு:
		  gcc_unreachable ();
		}
	      எனில் (r_name)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qE has invalid type for %<reduction(%s)%>",
			    t, r_name);
		  remove = உண்மை;
		  நிறுத்து;
		}
	    }
	  இல்லையெனில் எனில் (OMP_CLAUSE_REDUCTION_PLACEHOLDER (c) == error_mark_முனை)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"user defined reduction not found for %qE", t);
	      remove = உண்மை;
	      நிறுத்து;
	    }
	  இல்லையெனில் எனில் (OMP_CLAUSE_REDUCTION_PLACEHOLDER (c))
	    {
	      மரம் list = OMP_CLAUSE_REDUCTION_PLACEHOLDER (c);
	      type = TYPE_MAIN_VARIANT (type);
	      மரம் placeholder = build_decl (OMP_CLAUSE_LOCATION (c),
					     VAR_DECL, NULL_மரம், type);
	      மரம் decl_placeholder = NULL_மரம்;
	      OMP_CLAUSE_REDUCTION_PLACEHOLDER (c) = placeholder;
	      DECL_ARTIFICIAL (placeholder) = 1;
	      DECL_IGNORED_P (placeholder) = 1;
	      எனில் (மரம்_CODE (t) == MEM_REF)
		{
		  decl_placeholder = build_decl (OMP_CLAUSE_LOCATION (c),
						 VAR_DECL, NULL_மரம், type);
		  OMP_CLAUSE_REDUCTION_DECL_PLACEHOLDER (c) = decl_placeholder;
		  DECL_ARTIFICIAL (decl_placeholder) = 1;
		  DECL_IGNORED_P (decl_placeholder) = 1;
		}
	      எனில் (மரம்_ADDRESSABLE (மரம்_VEC_ELT (list, 0)))
		c_mark_addressable (placeholder);
	      எனில் (மரம்_ADDRESSABLE (மரம்_VEC_ELT (list, 1)))
		c_mark_addressable (decl_placeholder ? decl_placeholder
				    : OMP_CLAUSE_DECL (c));
	      OMP_CLAUSE_REDUCTION_MERGE (c)
		= c_clone_omp_udr (மரம்_VEC_ELT (list, 2),
				   மரம்_VEC_ELT (list, 0),
				   மரம்_VEC_ELT (list, 1),
				   decl_placeholder ? decl_placeholder
				   : OMP_CLAUSE_DECL (c), placeholder);
	      OMP_CLAUSE_REDUCTION_MERGE (c)
		= build3_loc (OMP_CLAUSE_LOCATION (c), BIND_கோவை,
			      void_type_முனை, NULL_மரம்,
			      OMP_CLAUSE_REDUCTION_MERGE (c), NULL_மரம்);
	      மரம்_SIDE_EFFECTS (OMP_CLAUSE_REDUCTION_MERGE (c)) = 1;
	      எனில் (மரம்_VEC_LENGTH (list) == 6)
		{
		  எனில் (மரம்_ADDRESSABLE (மரம்_VEC_ELT (list, 3)))
		    c_mark_addressable (decl_placeholder ? decl_placeholder
					: OMP_CLAUSE_DECL (c));
		  எனில் (மரம்_ADDRESSABLE (மரம்_VEC_ELT (list, 4)))
		    c_mark_addressable (placeholder);
		  மரம் init = மரம்_VEC_ELT (list, 5);
		  எனில் (init == error_mark_முனை)
		    init = DECL_INITIAL (மரம்_VEC_ELT (list, 3));
		  OMP_CLAUSE_REDUCTION_INIT (c)
		    = c_clone_omp_udr (init, மரம்_VEC_ELT (list, 4),
				       மரம்_VEC_ELT (list, 3),
				       decl_placeholder ? decl_placeholder
				       : OMP_CLAUSE_DECL (c), placeholder);
		  எனில் (மரம்_VEC_ELT (list, 5) == error_mark_முனை)
		    {
		      மரம் v = decl_placeholder ? decl_placeholder : t;
		      OMP_CLAUSE_REDUCTION_INIT (c)
			= build2 (INIT_கோவை, மரம்_TYPE (v), v,
				  OMP_CLAUSE_REDUCTION_INIT (c));
		    }
		  எனில் (walk_மரம் (&OMP_CLAUSE_REDUCTION_INIT (c),
				 c_find_omp_placeholder_r,
				 placeholder, வெற்று))
		    OMP_CLAUSE_REDUCTION_OMP_ORIG_REF (c) = 1;
		}
	      இல்லையெனில்
		{
		  மரம் init;
		  மரம் v = decl_placeholder ? decl_placeholder : t;
		  எனில் (AGGREGATE_TYPE_P (மரம்_TYPE (v)))
		    init = build_constructor (மரம்_TYPE (v), வெற்று);
		  இல்லையெனில்
		    init = fold_convert (மரம்_TYPE (v), integer_zero_முனை);
		  OMP_CLAUSE_REDUCTION_INIT (c)
		    = build2 (INIT_கோவை, மரம்_TYPE (v), v, init);
		}
	      OMP_CLAUSE_REDUCTION_INIT (c)
		= build3_loc (OMP_CLAUSE_LOCATION (c), BIND_கோவை,
			      void_type_முனை, NULL_மரம்,
			       OMP_CLAUSE_REDUCTION_INIT (c), NULL_மரம்);
	      மரம்_SIDE_EFFECTS (OMP_CLAUSE_REDUCTION_INIT (c)) = 1;
	    }
	  எனில் (மரம்_CODE (t) == MEM_REF)
	    {
	      எனில் (TYPE_SIZE_UNIT (மரம்_TYPE (மரம்_TYPE (t))) == NULL_மரம்
		  || மரம்_CODE (TYPE_SIZE_UNIT (மரம்_TYPE (மரம்_TYPE (t))))
		     != INTEGER_CST)
		{
		  sorry ("variable length element type in array "
			 "%<reduction%> clause");
		  remove = உண்மை;
		  நிறுத்து;
		}
	      t = மரம்_OPERAND (t, 0);
	      எனில் (மரம்_CODE (t) == POINTER_PLUS_கோவை)
		t = மரம்_OPERAND (t, 0);
	      எனில் (மரம்_CODE (t) == ADDR_கோவை)
		t = மரம்_OPERAND (t, 0);
	    }
	  செல் check_dup_generic_t;

	நிலை OMP_CLAUSE_COPYPRIVATE:
	  copyprivate_seen = உண்மை;
	  எனில் (nowait_clause)
	    {
	      error_at (OMP_CLAUSE_LOCATION (*nowait_clause),
			"%<nowait%> clause must not be used together "
			"with %<copyprivate%> clause");
	      *nowait_clause = OMP_CLAUSE_CHAIN (*nowait_clause);
	      nowait_clause = வெற்று;
	    }
	  செல் check_dup_generic;

	நிலை OMP_CLAUSE_COPYIN:
	  t = OMP_CLAUSE_DECL (c);
	  எனில் (!VAR_P (t) || !DECL_THREAD_LOCAL_P (t))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE must be %<threadprivate%> for %<copyin%>", t);
	      remove = உண்மை;
	      நிறுத்து;
	    }
	  செல் check_dup_generic;

	நிலை OMP_CLAUSE_LINEAR:
	  எனில் (ort != C_ORT_OMP_DECLARE_SIMD)
	    need_implicitly_determined = உண்மை;
	  t = OMP_CLAUSE_DECL (c);
	  எனில் (ort != C_ORT_OMP_DECLARE_SIMD
	      && OMP_CLAUSE_LINEAR_KIND (c) != OMP_CLAUSE_LINEAR_DEFAULT
	      && OMP_CLAUSE_LINEAR_OLD_LINEAR_MODIFIER (c))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"modifier should not be specified in %<linear%> "
			"clause on %<simd%> or %<for%> constructs when not "
			"using OpenMP 5.2 modifiers");
	      OMP_CLAUSE_LINEAR_KIND (c) = OMP_CLAUSE_LINEAR_DEFAULT;
	    }
	  எனில் (!INTEGRAL_TYPE_P (மரம்_TYPE (t))
	      && மரம்_CODE (மரம்_TYPE (t)) != POINTER_TYPE)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"linear clause applied to non-integral non-pointer "
			"variable with type %qT", மரம்_TYPE (t));
	      remove = உண்மை;
	      நிறுத்து;
	    }
	  எனில் (TYPE_ATOMIC (மரம்_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<_Atomic%> %qD in %<linear%> clause", t);
	      remove = உண்மை;
	      நிறுத்து;
	    }
	  எனில் (ort == C_ORT_OMP_DECLARE_SIMD)
	    {
	      மரம் s = OMP_CLAUSE_LINEAR_STEP (c);
	      எனில் (மரம்_CODE (s) == PARM_DECL)
		{
		  OMP_CLAUSE_LINEAR_VARIABLE_STRIDE (c) = 1;
		  /* map_head bitmap is used as uniform_head if
		     declare_simd.  */
		  எனில் (!bitmap_bit_p (&map_head, DECL_UID (s)))
		    linear_variable_step_check = உண்மை;
		  செல் check_dup_generic;
		}
	      எனில் (மரம்_CODE (s) != INTEGER_CST)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<linear%> clause step %qE is neither constant "
			    "nor a parameter", s);
		  remove = உண்மை;
		  நிறுத்து;
		}
	    }
	  எனில் (மரம்_CODE (மரம்_TYPE (OMP_CLAUSE_DECL (c))) == POINTER_TYPE)
	    {
	      மரம் s = OMP_CLAUSE_LINEAR_STEP (c);
	      s = pointer_int_sum (OMP_CLAUSE_LOCATION (c), PLUS_கோவை,
				   OMP_CLAUSE_DECL (c), s);
	      s = fold_build2_loc (OMP_CLAUSE_LOCATION (c), MINUS_கோவை,
				   sizetype, fold_convert (sizetype, s),
				   fold_convert
				     (sizetype, OMP_CLAUSE_DECL (c)));
	      எனில் (s == error_mark_முனை)
		s = size_one_முனை;
	      OMP_CLAUSE_LINEAR_STEP (c) = s;
	    }
	  இல்லையெனில்
	    OMP_CLAUSE_LINEAR_STEP (c)
	      = fold_convert (மரம்_TYPE (t), OMP_CLAUSE_LINEAR_STEP (c));
	  செல் check_dup_generic;

	check_dup_generic:
	  t = OMP_CLAUSE_DECL (c);
	check_dup_generic_t:
	  எனில் (!VAR_P (t) && மரம்_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %qs", t,
			omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	      remove = உண்மை;
	    }
	  இல்லையெனில் எனில் ((openacc && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION)
		   || (ort == C_ORT_OMP
		       && (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_USE_DEVICE_PTR
			   || (OMP_CLAUSE_CODE (c)
			       == OMP_CLAUSE_USE_DEVICE_ADDR)))
		   || (ort == C_ORT_OMP_TARGET
		       && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION))
	    {
	      எனில் (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
		  && (bitmap_bit_p (&generic_head, DECL_UID (t))
		      || bitmap_bit_p (&firstprivate_head, DECL_UID (t))))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in data-sharing "
			    "clauses", t);
		  remove = உண்மை;
		  நிறுத்து;
		}
	      எனில் (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION)
		target_in_reduction_seen = உண்மை;
	      எனில் (bitmap_bit_p (&oacc_reduction_head, DECL_UID (t)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    openacc
			    ? "%qD appears more than once in reduction clauses"
			    : "%qD appears more than once in data clauses",
			    t);
		  remove = உண்மை;
		}
	      இல்லையெனில்
		bitmap_set_bit (&oacc_reduction_head, DECL_UID (t));
	    }
	  இல்லையெனில் எனில் (bitmap_bit_p (&generic_head, DECL_UID (t))
		   || bitmap_bit_p (&firstprivate_head, DECL_UID (t))
		   || bitmap_bit_p (&lastprivate_head, DECL_UID (t))
		   || bitmap_bit_p (&map_firstprivate_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in data clauses", t);
	      remove = உண்மை;
	    }
	  இல்லையெனில் எனில் ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_PRIVATE
		    || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_HAS_DEVICE_ADDR
		    || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IS_DEVICE_PTR)
		   && bitmap_bit_p (&map_head, DECL_UID (t)))
	    {
	      எனில் (openacc)
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears more than once in data clauses", t);
	      இல்லையெனில்
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears both in data and map clauses", t);
	      remove = உண்மை;
	    }
	  இல்லையெனில்
	    bitmap_set_bit (&generic_head, DECL_UID (t));
	  நிறுத்து;

	நிலை OMP_CLAUSE_FIRSTPRIVATE:
	  எனில் (OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (c) && !implicit_moved)
	    {
	    move_implicit:
	      implicit_moved = உண்மை;
	      /* Move firstprivate and map clauses with
		 OMP_CLAUSE_{FIRSTPRIVATE,MAP}_IMPLICIT set to the end of
		 clauses chain.  */
	      மரம் cl1 = NULL_மரம், cl2 = NULL_மரம்;
	      மரம் *pc1 = pc, *pc2 = &cl1, *pc3 = &cl2;
	      போது (*pc1)
		எனில் (OMP_CLAUSE_CODE (*pc1) == OMP_CLAUSE_FIRSTPRIVATE
		    && OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (*pc1))
		  {
		    *pc3 = *pc1;
		    pc3 = &OMP_CLAUSE_CHAIN (*pc3);
		    *pc1 = OMP_CLAUSE_CHAIN (*pc1);
		  }
		இல்லையெனில் எனில் (OMP_CLAUSE_CODE (*pc1) == OMP_CLAUSE_MAP
			 && OMP_CLAUSE_MAP_IMPLICIT (*pc1))
		  {
		    *pc2 = *pc1;
		    pc2 = &OMP_CLAUSE_CHAIN (*pc2);
		    *pc1 = OMP_CLAUSE_CHAIN (*pc1);
		  }
		இல்லையெனில்
		  pc1 = &OMP_CLAUSE_CHAIN (*pc1);
	      *pc3 = வெற்று;
	      *pc2 = cl2;
	      *pc1 = cl1;
	      தொடர்;
	    }
	  t = OMP_CLAUSE_DECL (c);
	  need_complete = உண்மை;
	  need_implicitly_determined = உண்மை;
	  எனில் (!VAR_P (t) && மரம்_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %<firstprivate%>", t);
	      remove = உண்மை;
	    }
	  இல்லையெனில் எனில் (OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (c)
		   && !OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT_TARGET (c)
		   && bitmap_bit_p (&map_firstprivate_head, DECL_UID (t)))
	    remove = உண்மை;
	  இல்லையெனில் எனில் (bitmap_bit_p (&generic_head, DECL_UID (t))
		   || bitmap_bit_p (&firstprivate_head, DECL_UID (t))
		   || bitmap_bit_p (&map_firstprivate_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in data clauses", t);
	      remove = உண்மை;
	    }
	  இல்லையெனில் எனில் (bitmap_bit_p (&map_head, DECL_UID (t))
		   || bitmap_bit_p (&map_field_head, DECL_UID (t)))
	    {
	      எனில் (openacc)
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears more than once in data clauses", t);
	      இல்லையெனில் எனில் (OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (c)
		       && !OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT_TARGET (c))
		/* Silently drop the clause.  */;
	      இல்லையெனில்
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears both in data and map clauses", t);
	      remove = உண்மை;
	    }
	  இல்லையெனில்
	    bitmap_set_bit (&firstprivate_head, DECL_UID (t));
	  நிறுத்து;

	நிலை OMP_CLAUSE_LASTPRIVATE:
	  t = OMP_CLAUSE_DECL (c);
	  need_complete = உண்மை;
	  need_implicitly_determined = உண்மை;
	  எனில் (!VAR_P (t) && மரம்_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %<lastprivate%>", t);
	      remove = உண்மை;
	    }
	  இல்லையெனில் எனில் (bitmap_bit_p (&generic_head, DECL_UID (t))
		   || bitmap_bit_p (&lastprivate_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
		     "%qE appears more than once in data clauses", t);
	      remove = உண்மை;
	    }
	  இல்லையெனில்
	    bitmap_set_bit (&lastprivate_head, DECL_UID (t));
	  நிறுத்து;

	நிலை OMP_CLAUSE_ALIGNED:
	  t = OMP_CLAUSE_DECL (c);
	  எனில் (!VAR_P (t) && மரம்_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in %<aligned%> clause", t);
	      remove = உண்மை;
	    }
	  இல்லையெனில் எனில் (!POINTER_TYPE_P (மரம்_TYPE (t))
		   && மரம்_CODE (மரம்_TYPE (t)) != ARRAY_TYPE)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE in %<aligned%> clause is neither a pointer nor "
			"an array", t);
	      remove = உண்மை;
	    }
	  இல்லையெனில் எனில் (TYPE_ATOMIC (மரம்_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<_Atomic%> %qD in %<aligned%> clause", t);
	      remove = உண்மை;
	      நிறுத்து;
	    }
	  இல்லையெனில் எனில் (bitmap_bit_p (&aligned_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in %<aligned%> clauses",
			t);
	      remove = உண்மை;
	    }
	  இல்லையெனில்
	    bitmap_set_bit (&aligned_head, DECL_UID (t));
	  நிறுத்து;

	நிலை OMP_CLAUSE_NONTEMPORAL:
	  t = OMP_CLAUSE_DECL (c);
	  எனில் (!VAR_P (t) && மரம்_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in %<nontemporal%> clause", t);
	      remove = உண்மை;
	    }
	  இல்லையெனில் எனில் (bitmap_bit_p (&oacc_reduction_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in %<nontemporal%> "
			"clauses", t);
	      remove = உண்மை;
	    }
	  இல்லையெனில்
	    bitmap_set_bit (&oacc_reduction_head, DECL_UID (t));
	  நிறுத்து;

	நிலை OMP_CLAUSE_ALLOCATE:
	  t = OMP_CLAUSE_DECL (c);
	  எனில் (!VAR_P (t) && மரம்_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in %<allocate%> clause", t);
	      remove = உண்மை;
	    }
	  இல்லையெனில் எனில் (bitmap_bit_p (&aligned_head, DECL_UID (t)))
	    {
	      warning_at (OMP_CLAUSE_LOCATION (c), OPT_Wopenmp,
			  "%qE appears more than once in %<allocate%> clauses",
			  t);
	      remove = உண்மை;
	    }
	  இல்லையெனில்
	    {
	      bitmap_set_bit (&aligned_head, DECL_UID (t));
	      எனில் (!OMP_CLAUSE_ALLOCATE_COMBINED (c))
		allocate_seen = உண்மை;
	    }
	  நிறுத்து;

	நிலை OMP_CLAUSE_DOACROSS:
	  t = OMP_CLAUSE_DECL (c);
	  எனில் (t == NULL_மரம்)
	    நிறுத்து;
	  எனில் (OMP_CLAUSE_DOACROSS_KIND (c) == OMP_CLAUSE_DOACROSS_SINK)
	    {
	      gcc_assert (மரம்_CODE (t) == மரம்_LIST);
	      க்கு (; t; t = மரம்_CHAIN (t))
		{
		  மரம் decl = மரம்_மதிப்பு (t);
		  எனில் (மரம்_CODE (மரம்_TYPE (decl)) == POINTER_TYPE)
		    {
		      மரம் offset = மரம்_PURPOSE (t);
		      தருக்க neg = wi::neg_p (wi::to_wide (offset));
		      offset = fold_unary (ABS_கோவை, மரம்_TYPE (offset), offset);
		      மரம் t2 = pointer_int_sum (OMP_CLAUSE_LOCATION (c),
						 neg ? MINUS_கோவை : PLUS_கோவை,
						 decl, offset);
		      t2 = fold_build2_loc (OMP_CLAUSE_LOCATION (c), MINUS_கோவை,
					    sizetype,
					    fold_convert (sizetype, t2),
					    fold_convert (sizetype, decl));
		      எனில் (t2 == error_mark_முனை)
			{
			  remove = உண்மை;
			  நிறுத்து;
			}
		      மரம்_PURPOSE (t) = t2;
		    }
		}
	      நிறுத்து;
	    }
	  gcc_unreachable ();

	நிலை OMP_CLAUSE_USES_ALLOCATORS:
	  t = OMP_CLAUSE_USES_ALLOCATORS_ALLOCATOR (c);
	  எனில் (t == error_mark_முனை)
	    {
	      remove = உண்மை;
	      நிறுத்து;
	    }
	  எனில் ((VAR_P (t) || மரம்_CODE (t) == PARM_DECL)
	      && (bitmap_bit_p (&generic_head, DECL_UID (t))
		  || bitmap_bit_p (&map_head, DECL_UID (t))
		  || bitmap_bit_p (&firstprivate_head, DECL_UID (t))
		  || bitmap_bit_p (&lastprivate_head, DECL_UID (t))))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in data clauses", t);
	      remove = உண்மை;
	      நிறுத்து;
	    }
	  இல்லையெனில்
	    bitmap_set_bit (&generic_head, DECL_UID (t));
	  எனில் (மரம்_CODE (மரம்_TYPE (t)) != ENUMERAL_TYPE
	      || strcmp (IDENTIFIER_POINTER (TYPE_IDENTIFIER (மரம்_TYPE (t))),
			 "omp_allocator_handle_t") != 0)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"allocator %qE must be of %<omp_allocator_handle_t%> "
			"type", t);
	      remove = உண்மை;
	      நிறுத்து;
	    }
	  மரம் init;
	  எனில் (!DECL_P (t)
	      || (மரம்_CODE (t) == CONST_DECL
		  && ((init = DECL_INITIAL(t)) == nullptr
		      || மரம்_CODE (init) != INTEGER_CST
		      || ((wi::to_widest (init) < 0
			   || wi::to_widest (init) > GOMP_OMP_PREDEF_ALLOC_MAX)
			  && (wi::to_widest (init) < GOMP_OMPX_PREDEF_ALLOC_MIN
			      || (wi::to_widest (init)
				  > GOMP_OMPX_PREDEF_ALLOC_MAX))))))
	    {
	      remove = உண்மை;
	      error_at (OMP_CLAUSE_LOCATION (c),
			"allocator %qE must be either a variable or a "
			"predefined allocator", t);
	      நிறுத்து;
	    }
	  இல்லையெனில் எனில் (மரம்_CODE (t) == CONST_DECL)
	    {
	      /* omp_null_allocator is ignored and for predefined allocators,
		 no special handling is required; thus, mark them removed. */
	      remove = உண்மை;

	      எனில் (OMP_CLAUSE_USES_ALLOCATORS_MEMSPACE (c)
		  || OMP_CLAUSE_USES_ALLOCATORS_TRAITS (c))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "modifiers cannot be used with predefined "
			    "allocator %qE", t);
		  நிறுத்து;
		}
	    }
	  t = OMP_CLAUSE_USES_ALLOCATORS_MEMSPACE (c);
	  எனில் (t == error_mark_முனை)
	    {
	      remove = உண்மை;
	      நிறுத்து;
	    }
	  எனில் (t != NULL_மரம்
	      && ((மரம்_CODE (t) != CONST_DECL && மரம்_CODE (t) != INTEGER_CST)
		  || மரம்_CODE (மரம்_TYPE (t)) != ENUMERAL_TYPE
		  || strcmp (IDENTIFIER_POINTER (TYPE_IDENTIFIER (மரம்_TYPE (t))),
			     "omp_memspace_handle_t") != 0))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c), "memspace modifier %qE must be"
			" constant enum of %<omp_memspace_handle_t%> type", t);
	      remove = உண்மை;
	      நிறுத்து;
	    }
	  t = OMP_CLAUSE_USES_ALLOCATORS_TRAITS (c);
	  எனில் (t == error_mark_முனை)
	    {
	      remove = உண்மை;
	      நிறுத்து;
	    }
	  எனில் (t != NULL_மரம்
	      && t != error_mark_முனை
	      && (DECL_EXTERNAL (t)
		  || மரம்_CODE (t) == PARM_DECL))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c), "traits array %qE must be "
			"defined in same scope as the construct on which the "
			"clause appears", t);
	      remove = உண்மை;
	    }
	  எனில் (t != NULL_மரம்)
	    {
	      தருக்க type_err = பொய்;

	      எனில் (மரம்_CODE (மரம்_TYPE (t)) != ARRAY_TYPE
		  || DECL_SIZE (t) == NULL_மரம்
		  || !COMPLETE_TYPE_P (மரம்_TYPE (t)))
		type_err = உண்மை;
	      இல்லையெனில்
		{
		  மரம் elem_t = மரம்_TYPE (மரம்_TYPE (t));
		  எனில் (மரம்_CODE (elem_t) != RECORD_TYPE
		      || strcmp (IDENTIFIER_POINTER (TYPE_IDENTIFIER (elem_t)),
				 "omp_alloctrait_t") != 0
		      || !TYPE_READONLY (elem_t))
		    type_err = உண்மை;
		}
	      எனில் (type_err)
		{
		  எனில் (t != error_mark_முனை)
		    error_at (OMP_CLAUSE_LOCATION (c), "traits array %qE must "
			      "be of %<const omp_alloctrait_t []%> type", t);
		  இல்லையெனில்
		    error_at (OMP_CLAUSE_LOCATION (c), "traits array must "
			      "be of %<const omp_alloctrait_t []%> type");
		  remove = உண்மை;
		}
	      இல்லையெனில்
		{
		  மரம் cst_val = decl_constant_மதிப்பு_1 (t, உண்மை);
		  எனில் (cst_val == t)
		    {
		      error_at (OMP_CLAUSE_LOCATION (c), "traits array must be "
				"initialized with constants");

		      remove = உண்மை;
		    }
		}
	    }
	  எனில் (remove)
	    நிறுத்து;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  தொடர்;
	நிலை OMP_CLAUSE_DEPEND:
	  depend_clause = c;
	  /* FALLTHRU */
	நிலை OMP_CLAUSE_AFFINITY:
	  t = OMP_CLAUSE_DECL (c);
	  எனில் (OMP_ITERATOR_DECL_P (t))
	    {
	      எனில் (மரம்_PURPOSE (t) != last_iterators)
		last_iterators_remove
		  = c_omp_finish_iterators (மரம்_PURPOSE (t));
	      last_iterators = மரம்_PURPOSE (t);
	      t = மரம்_மதிப்பு (t);
	      எனில் (last_iterators_remove)
		t = error_mark_முனை;
	    }
	  இல்லையெனில்
	    last_iterators = NULL_மரம்;
	  எனில் (மரம்_CODE (t) == OMP_ARRAY_SECTION)
	    {
	      எனில் (handle_omp_array_sections (c, ort))
		remove = உண்மை;
	      இல்லையெனில் எனில் (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
		       && OMP_CLAUSE_DEPEND_KIND (c) == OMP_CLAUSE_DEPEND_DEPOBJ)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<depend%> clause with %<depobj%> dependence "
			    "type on array section");
		  remove = உண்மை;
		}
	      நிறுத்து;
	    }
	  எனில் (t == error_mark_முனை)
	    remove = உண்மை;
	  இல்லையெனில் எனில் (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
		   && t == ridpointers[RID_OMP_ALL_MEMORY])
	    {
	      எனில் (OMP_CLAUSE_DEPEND_KIND (c) != OMP_CLAUSE_DEPEND_OUT
		  && OMP_CLAUSE_DEPEND_KIND (c) != OMP_CLAUSE_DEPEND_INOUT)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<omp_all_memory%> used with %<depend%> kind "
			    "other than %<out%> or %<inout%>");
		  remove = உண்மை;
		}
	    }
	  இல்லையெனில் எனில் (!lvalue_p (t))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not lvalue expression nor array section in "
			"%qs clause", t,
			omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	      remove = உண்மை;
	    }
	  இல்லையெனில் எனில் (மரம்_CODE (t) == COMPONENT_REF
		   && DECL_C_BIT_FIELD (மரம்_OPERAND (t, 1)))
	    {
	      gcc_assert (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
			  || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY);
	      error_at (OMP_CLAUSE_LOCATION (c),
			"bit-field %qE in %qs clause", t,
			omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	      remove = உண்மை;
	    }
	  இல்லையெனில் எனில் (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
		   && OMP_CLAUSE_DEPEND_KIND (c) == OMP_CLAUSE_DEPEND_DEPOBJ)
	    {
	      எனில் (!c_omp_depend_t_p (மரம்_TYPE (t)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qE does not have %<omp_depend_t%> type in "
			    "%<depend%> clause with %<depobj%> dependence "
			    "type", t);
		  remove = உண்மை;
		}
	    }
	  இல்லையெனில் எனில் (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
		   && c_omp_depend_t_p (மரம்_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE should not have %<omp_depend_t%> type in "
			"%<depend%> clause with dependence type other than "
			"%<depobj%>", t);
	      remove = உண்மை;
	    }
	  எனில் (!remove)
	    {
	      எனில் (t == ridpointers[RID_OMP_ALL_MEMORY])
		t = null_pointer_முனை;
	      இல்லையெனில்
		{
		  மரம் addr = build_unary_op (OMP_CLAUSE_LOCATION (c),
					      ADDR_கோவை, t, பொய்);
		  எனில் (addr == error_mark_முனை)
		    {
		      remove = உண்மை;
		      நிறுத்து;
		    }
		  t = build_indirect_ref (OMP_CLAUSE_LOCATION (c), addr,
					  RO_UNARY_STAR);
		  எனில் (t == error_mark_முனை)
		    {
		      remove = உண்மை;
		      நிறுத்து;
		    }
		}
	      எனில் (OMP_ITERATOR_DECL_P (OMP_CLAUSE_DECL (c)))
		மரம்_மதிப்பு (OMP_CLAUSE_DECL (c)) = t;
	      இல்லையெனில்
		OMP_CLAUSE_DECL (c) = t;
	    }
	  நிறுத்து;

	நிலை OMP_CLAUSE_MAP:
	  எனில் (OMP_CLAUSE_MAP_IMPLICIT (c) && !implicit_moved)
	    செல் move_implicit;
	  எனில் (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_தள்ளு_MAPPER_NAME
	      || OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_எடு_MAPPER_NAME)
	    {
	      remove = உண்மை;
	      நிறுத்து;
	    }
	  /* FALLTHRU */
	நிலை OMP_CLAUSE_TO:
	நிலை OMP_CLAUSE_FROM:
	  எனில் (OMP_CLAUSE_ITERATORS (c)
	      && c_omp_finish_iterators (OMP_CLAUSE_ITERATORS (c)))
	    {
	      t = error_mark_முனை;
	      நிறுத்து;
	    }
	  /* FALLTHRU */
	நிலை OMP_CLAUSE__CACHE_:
	  {
	    using நாமாகாஶ omp_addr_tokenizer;
	    auto_vec<omp_addr_token *, 10> addr_tokens;

	    t = OMP_CLAUSE_DECL (c);
	    எனில் (மரம்_CODE (t) == OMP_ARRAY_SECTION)
	      {
		grp_start_p = pc;
		grp_sentinel = OMP_CLAUSE_CHAIN (c);

		எனில் (handle_omp_array_sections (c, ort))
		  remove = உண்மை;
		இல்லையெனில்
		  {
		    t = OMP_CLAUSE_DECL (c);
		    எனில் (!omp_mappable_type (மரம்_TYPE (t)))
		      {
			error_at (OMP_CLAUSE_LOCATION (c),
				  "array section does not have mappable type "
				  "in %qs clause",
				  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
			remove = உண்மை;
		      }
		    இல்லையெனில் எனில் (TYPE_ATOMIC (மரம்_TYPE (t)))
		      {
			error_at (OMP_CLAUSE_LOCATION (c),
				  "%<_Atomic%> %qE in %qs clause", t,
				  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
			remove = உண்மை;
		      }
		    போது (மரம்_CODE (t) == ARRAY_REF)
		      t = மரம்_OPERAND (t, 0);

		    c_omp_address_inspector ai (OMP_CLAUSE_LOCATION (c), t);

		    எனில் (!omp_parse_கோவை (addr_tokens, t))
		      {
			sorry_at (OMP_CLAUSE_LOCATION (c),
				  "unsupported map expression %qE",
				  OMP_CLAUSE_DECL (c));
			remove = உண்மை;
			நிறுத்து;
		      }

		    /* This check is to determine if this will be the only map
		       node created for this clause.  Otherwise, we'll check
		       the following FIRSTPRIVATE_POINTER or ATTACH_DETACH
		       node on the next iteration(s) of the loop.   */
		    எனில் (addr_tokens.length () >= 4
			&& addr_tokens[0]->type == STRUCTURE_BASE
			&& addr_tokens[0]->u.structure_base_kind == BASE_DECL
			&& addr_tokens[1]->type == ACCESS_METHOD
			&& addr_tokens[2]->type == COMPONENT_SELECTOR
			&& addr_tokens[3]->type == ACCESS_METHOD
			&& (addr_tokens[3]->u.access_kind == ACCESS_DIRECT
			    || (addr_tokens[3]->u.access_kind
				== ACCESS_INDEXED_ARRAY)))
		      {
			மரம் rt = addr_tokens[1]->கோவை;

			gcc_assert (DECL_P (rt));

			எனில் (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
			    && OMP_CLAUSE_MAP_IMPLICIT (c)
			    && (bitmap_bit_p (&map_head, DECL_UID (rt))
				|| bitmap_bit_p (&map_field_head, DECL_UID (rt))
				|| bitmap_bit_p (&map_firstprivate_head,
						 DECL_UID (rt))))
			  {
			    remove = உண்மை;
			    நிறுத்து;
			  }
			எனில் (bitmap_bit_p (&map_field_head, DECL_UID (rt)))
			  நிறுத்து;
			எனில் (bitmap_bit_p (&map_head, DECL_UID (rt)))
			  {
			    எனில் (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP)
			      error_at (OMP_CLAUSE_LOCATION (c),
					"%qD appears more than once in motion "
					"clauses", rt);
			    இல்லையெனில் எனில் (openacc)
			      error_at (OMP_CLAUSE_LOCATION (c),
					"%qD appears more than once in data "
					"clauses", rt);
			    இல்லையெனில்
			      error_at (OMP_CLAUSE_LOCATION (c),
					"%qD appears more than once in map "
					"clauses", rt);
			    remove = உண்மை;
			  }
			இல்லையெனில்
			  {
			    bitmap_set_bit (&map_head, DECL_UID (rt));
			    bitmap_set_bit (&map_field_head, DECL_UID (rt));
			  }
		      }
		  }
		எனில் (c_oacc_check_attachments (c))
		  remove = உண்மை;
		எனில் (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		    && (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_ATTACH
			|| OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_DETACH)
		    && !OMP_CLAUSE_SIZE (c))
		  /* In this case, we have a single array element which is a
		     pointer, and we already set OMP_CLAUSE_SIZE in
		     handle_omp_array_sections above.  For attach/detach
		     clauses, reset the OMP_CLAUSE_SIZE (representing a bias)
		     to zero here.  */
		  OMP_CLAUSE_SIZE (c) = size_zero_முனை;
		நிறுத்து;
	      }
	    இல்லையெனில் எனில் (!omp_parse_கோவை (addr_tokens, t))
	      {
		sorry_at (OMP_CLAUSE_LOCATION (c),
			  "unsupported map expression %qE",
			  OMP_CLAUSE_DECL (c));
		remove = உண்மை;
		நிறுத்து;
	      }
	    எனில் (t == error_mark_முனை)
	      {
		remove = உண்மை;
		நிறுத்து;
	      }

	    மரம் attr;
	    எனில் (DECL_P (t)
		&& OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		&& (attr = lookup_attribute ("omp declare target",
					     DECL_ATTRIBUTES (t)))
		&& மதிப்பு_member (get_identifier ("local"),
				 மரம்_மதிப்பு (attr)))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "device-local variable %qD cannot appear "
			  "in map clause", t);
		remove = உண்மை;
		நிறுத்து;
	      }

	    /* OpenACC attach / detach clauses must be pointers.  */
	    எனில் (c_oacc_check_attachments (c))
	      {
		remove = உண்மை;
		நிறுத்து;
	      }
	    எனில் (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		&& (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_ATTACH
		    || OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_DETACH)
		&& !OMP_CLAUSE_SIZE (c))
	      /* For attach/detach clauses, set OMP_CLAUSE_SIZE (representing a
		 bias) to zero here, so it is not set erroneously to the pointer
		 size later on in gimplify.cc.  */
	      OMP_CLAUSE_SIZE (c) = size_zero_முனை;

	    c_omp_address_inspector ai (OMP_CLAUSE_LOCATION (c), t);

	    எனில் (!ai.check_clause (c))
	      {
		remove = உண்மை;
		நிறுத்து;
	      }

	    எனில் (!ai.map_supported_p ())
	      {
		sorry_at (OMP_CLAUSE_LOCATION (c),
			  "unsupported map expression %qE",
			  OMP_CLAUSE_DECL (c));
		remove = உண்மை;
		நிறுத்து;
	      }

	    gcc_assert ((addr_tokens[0]->type == ARRAY_BASE
			 || addr_tokens[0]->type == STRUCTURE_BASE)
			&& addr_tokens[1]->type == ACCESS_METHOD);

	    t = addr_tokens[1]->கோவை;

	    எனில் (addr_tokens[0]->u.structure_base_kind != BASE_DECL)
	      செல் skip_decl_checks;

	    /* For OpenMP, we can access a struct "t" and "t.d" on the same
	       mapping.  OpenACC allows multiple fields of the same structure
	       to be written.  */
	    எனில் (addr_tokens[0]->type == STRUCTURE_BASE
		&& (bitmap_bit_p (&map_field_head, DECL_UID (t))
		    || (!openacc && bitmap_bit_p (&map_head, DECL_UID (t)))))
	      செல் skip_decl_checks;

	    எனில் (!VAR_P (t) && மரம்_CODE (t) != PARM_DECL)
	      {
		எனில் (ort != C_ORT_ACC && கோவை_P (t))
		  நிறுத்து;

		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is not a variable in %qs clause", t,
			  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		remove = உண்மை;
	      }
	    இல்லையெனில் எனில் (VAR_P (t) && DECL_THREAD_LOCAL_P (t))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD is threadprivate variable in %qs clause", t,
			  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		remove = உண்மை;
	      }
	    இல்லையெனில் எனில் ((OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP
		      || (OMP_CLAUSE_MAP_KIND (c)
			  != GOMP_MAP_FIRSTPRIVATE_POINTER))
		     && !c_mark_addressable (t))
	      remove = உண்மை;
	    இல்லையெனில் எனில் (!(OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		       && (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_POINTER
			   || (OMP_CLAUSE_MAP_KIND (c)
			       == GOMP_MAP_FIRSTPRIVATE_POINTER)
			   || (OMP_CLAUSE_MAP_KIND (c)
			       == GOMP_MAP_FORCE_DEVICEPTR)))
		     && t == OMP_CLAUSE_DECL (c)
		     && !omp_mappable_type (மரம்_TYPE (t)))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD does not have a mappable type in %qs clause", t,
			  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		remove = உண்மை;
	      }
	    இல்லையெனில் எனில் (மரம்_TYPE (t) == error_mark_முனை)
	      remove = உண்மை;
	    இல்லையெனில் எனில் (TYPE_ATOMIC (strip_array_types (மரம்_TYPE (t))))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%<_Atomic%> %qE in %qs clause", t,
			  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		remove = உண்மை;
	      }
	    இல்லையெனில் எனில் (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		     && OMP_CLAUSE_MAP_IMPLICIT (c)
		     && (bitmap_bit_p (&map_head, DECL_UID (t))
			 || bitmap_bit_p (&map_field_head, DECL_UID (t))
			 || bitmap_bit_p (&map_firstprivate_head,
					  DECL_UID (t))))
	      remove = உண்மை;
	    இல்லையெனில் எனில் (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		     && (OMP_CLAUSE_MAP_KIND (c)
			 == GOMP_MAP_FIRSTPRIVATE_POINTER))
	      {
		எனில் (bitmap_bit_p (&generic_head, DECL_UID (t))
		    || bitmap_bit_p (&firstprivate_head, DECL_UID (t))
		    || bitmap_bit_p (&map_firstprivate_head, DECL_UID (t)))
		  {
		    error_at (OMP_CLAUSE_LOCATION (c),
			      "%qD appears more than once in data clauses", t);
		    remove = உண்மை;
		  }
		இல்லையெனில் எனில் (bitmap_bit_p (&map_head, DECL_UID (t))
			 && !bitmap_bit_p (&map_field_head, DECL_UID (t))
			 && openacc)
		  {
		    error_at (OMP_CLAUSE_LOCATION (c),
			      "%qD appears more than once in data clauses", t);
		    remove = உண்மை;
		  }
		இல்லையெனில்
		  bitmap_set_bit (&map_firstprivate_head, DECL_UID (t));
	      }
	    இல்லையெனில் எனில் (bitmap_bit_p (&map_head, DECL_UID (t))
		     && !bitmap_bit_p (&map_field_head, DECL_UID (t))
		     && ort != C_ORT_OMP
		     && ort != C_ORT_OMP_TARGET
		     && ort != C_ORT_OMP_EXIT_DATA)
	      {
		எனில் (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP)
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in motion clauses", t);
		இல்லையெனில் எனில் (openacc)
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in data clauses", t);
		இல்லையெனில்
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in map clauses", t);
		remove = உண்மை;
	      }
	    இல்லையெனில் எனில் (openacc && bitmap_bit_p (&generic_head, DECL_UID (t)))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears more than once in data clauses", t);
		remove = உண்மை;
	      }
	    இல்லையெனில் எனில் (bitmap_bit_p (&firstprivate_head, DECL_UID (t))
		     || bitmap_bit_p (&is_on_device_head, DECL_UID (t)))
	      {
		எனில் (openacc)
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in data clauses", t);
		இல்லையெனில்
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears both in data and map clauses", t);
		remove = உண்மை;
	      }
	    இல்லையெனில் எனில் (!omp_access_chain_p (addr_tokens, 1))
	      {
		bitmap_set_bit (&map_head, DECL_UID (t));
		எனில் (t != OMP_CLAUSE_DECL (c)
		    && மரம்_CODE (OMP_CLAUSE_DECL (c)) == COMPONENT_REF)
		  bitmap_set_bit (&map_field_head, DECL_UID (t));
	      }

	  skip_decl_checks:
	    /* If we call omp_expand_map_clause in handle_omp_array_sections,
	       the containing loop (here) iterates through the new nodes
	       created by that expansion.  Avoid expanding those again (just
	       by checking the node type).  */
	    எனில் (!remove
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
		மரம் nc = ai.expand_map_clause (c, OMP_CLAUSE_DECL (c),
						addr_tokens, ort);
		எனில் (nc != error_mark_முனை)
		  c = nc;
	      }
	  }
	  நிறுத்து;

	நிலை OMP_CLAUSE_ENTER:
	நிலை OMP_CLAUSE_LINK:
	நிலை OMP_CLAUSE_LOCAL:
	  t = OMP_CLAUSE_DECL (c);
	  மாறிலி எழுத்து *cname;
	  cname = omp_clause_code_name[OMP_CLAUSE_CODE (c)];
	  எனில் (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ENTER
	      && OMP_CLAUSE_ENTER_TO (c))
	    cname = "to";
	  எனில் (மரம்_CODE (t) == FUNCTION_DECL
	      && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ENTER)
	    ;
	  இல்லையெனில் எனில் (!VAR_P (t))
	    {
	      எனில் (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ENTER)
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is neither a variable nor a function name in "
			  "clause %qs", t, cname);
	      இல்லையெனில்
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is not a variable in clause %qs", t, cname);
	      remove = உண்மை;
	    }
	  இல்லையெனில் எனில் (DECL_THREAD_LOCAL_P (t))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD is threadprivate variable in %qs clause", t,
			cname);
	      remove = உண்மை;
	    }
	  இல்லையெனில் எனில் (!omp_mappable_type (மரம்_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD does not have a mappable type in %qs clause", t,
			cname);
	      remove = உண்மை;
	    }
	  எனில் (remove)
	    நிறுத்து;
	  எனில் (bitmap_bit_p (&generic_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once on the same "
			"%<declare target%> directive", t);
	      remove = உண்மை;
	    }
	  இல்லையெனில்
	    bitmap_set_bit (&generic_head, DECL_UID (t));
	  நிறுத்து;

	நிலை OMP_CLAUSE_UNIFORM:
	  t = OMP_CLAUSE_DECL (c);
	  எனில் (மரம்_CODE (t) != PARM_DECL)
	    {
	      எனில் (DECL_P (t))
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD is not an argument in %<uniform%> clause", t);
	      இல்லையெனில்
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is not an argument in %<uniform%> clause", t);
	      remove = உண்மை;
	      நிறுத்து;
	    }
	  /* map_head bitmap is used as uniform_head if declare_simd.  */
	  bitmap_set_bit (&map_head, DECL_UID (t));
	  செல் check_dup_generic;

	நிலை OMP_CLAUSE_IS_DEVICE_PTR:
	நிலை OMP_CLAUSE_USE_DEVICE_PTR:
	  t = OMP_CLAUSE_DECL (c);
	  எனில் (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IS_DEVICE_PTR)
	    bitmap_set_bit (&is_on_device_head, DECL_UID (t));
	  எனில் (மரம்_CODE (மரம்_TYPE (t)) != POINTER_TYPE)
	    {
	      எனில் (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_USE_DEVICE_PTR
		  && !openacc)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qs variable is not a pointer",
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  remove = உண்மை;
		}
	      இல்லையெனில் எனில் (மரம்_CODE (மரம்_TYPE (t)) != ARRAY_TYPE)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qs variable is neither a pointer nor an array",
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  remove = உண்மை;
		}
	    }
	  செல் check_dup_generic;

	நிலை OMP_CLAUSE_HAS_DEVICE_ADDR:
	  t = OMP_CLAUSE_DECL (c);
	  எனில் (மரம்_CODE (t) == OMP_ARRAY_SECTION)
	    {
	      எனில் (handle_omp_array_sections (c, ort))
		remove = உண்மை;
	      இல்லையெனில்
		{
		  t = OMP_CLAUSE_DECL (c);
		  போது (மரம்_CODE (t) == ARRAY_REF)
		    t = மரம்_OPERAND (t, 0);
		}
	    }
	  bitmap_set_bit (&is_on_device_head, DECL_UID (t));
	  எனில் (VAR_P (t) || மரம்_CODE (t) == PARM_DECL)
	    c_mark_addressable (t);
	  செல் check_dup_generic_t;

	நிலை OMP_CLAUSE_USE_DEVICE_ADDR:
	  t = OMP_CLAUSE_DECL (c);
	  எனில் (VAR_P (t) || மரம்_CODE (t) == PARM_DECL)
	    c_mark_addressable (t);
	  செல் check_dup_generic;

	நிலை OMP_CLAUSE_NOWAIT:
	  எனில் (copyprivate_seen)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<nowait%> clause must not be used together "
			"with %<copyprivate%> clause");
	      remove = உண்மை;
	      நிறுத்து;
	    }
	  nowait_clause = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  தொடர்;

	நிலை OMP_CLAUSE_ORDER:
	  எனில் (ordered_clause)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<order%> clause must not be used together "
			"with %<ordered%> clause");
	      remove = உண்மை;
	      நிறுத்து;
	    }
	  இல்லையெனில் எனில் (order_clause)
	    {
	      /* Silently remove duplicates.  */
	      remove = உண்மை;
	      நிறுத்து;
	    }
	  order_clause = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  தொடர்;

	நிலை OMP_CLAUSE_DETACH:
	  t = OMP_CLAUSE_DECL (c);
	  எனில் (detach_seen)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"too many %qs clauses on a task construct",
			"detach");
	      remove = உண்மை;
	      நிறுத்து;
	    }
	  detach_seen = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  c_mark_addressable (t);
	  தொடர்;

	நிலை OMP_CLAUSE_IF:
	நிலை OMP_CLAUSE_SELF:
	நிலை OMP_CLAUSE_இலக்கம்_THREADS:
	நிலை OMP_CLAUSE_இலக்கம்_TEAMS:
	நிலை OMP_CLAUSE_THREAD_LIMIT:
	நிலை OMP_CLAUSE_DEFAULT:
	நிலை OMP_CLAUSE_UNTIED:
	நிலை OMP_CLAUSE_COLLAPSE:
	நிலை OMP_CLAUSE_FINAL:
	நிலை OMP_CLAUSE_DEVICE:
	நிலை OMP_CLAUSE_DIST_SCHEDULE:
	நிலை OMP_CLAUSE_DYN_GROUPPRIVATE:
	நிலை OMP_CLAUSE_PARALLEL:
	நிலை OMP_CLAUSE_FOR:
	நிலை OMP_CLAUSE_SECTIONS:
	நிலை OMP_CLAUSE_TASKGROUP:
	நிலை OMP_CLAUSE_PROC_BIND:
	நிலை OMP_CLAUSE_DEVICE_TYPE:
	நிலை OMP_CLAUSE_PRIORITY:
	நிலை OMP_CLAUSE_THREADS:
	நிலை OMP_CLAUSE_SIMD:
	நிலை OMP_CLAUSE_HINT:
	நிலை OMP_CLAUSE_FILTER:
	நிலை OMP_CLAUSE_DEFAULTMAP:
	நிலை OMP_CLAUSE_BIND:
	நிலை OMP_CLAUSE_இலக்கம்_GANGS:
	நிலை OMP_CLAUSE_இலக்கம்_WORKERS:
	நிலை OMP_CLAUSE_VECTOR_LENGTH:
	நிலை OMP_CLAUSE_ASYNC:
	நிலை OMP_CLAUSE_WAIT:
	நிலை OMP_CLAUSE_AUTO:
	நிலை OMP_CLAUSE_INDEPENDENT:
	நிலை OMP_CLAUSE_SEQ:
	நிலை OMP_CLAUSE_GANG:
	நிலை OMP_CLAUSE_WORKER:
	நிலை OMP_CLAUSE_VECTOR:
	நிலை OMP_CLAUSE_TILE:
	நிலை OMP_CLAUSE_IF_PRESENT:
	நிலை OMP_CLAUSE_FINALIZE:
	நிலை OMP_CLAUSE_NOHOST:
	நிலை OMP_CLAUSE_INDIRECT:
	நிலை OMP_CLAUSE_NOVARIANTS:
	நிலை OMP_CLAUSE_NOCONTEXT:
	  pc = &OMP_CLAUSE_CHAIN (c);
	  தொடர்;

	நிலை OMP_CLAUSE_GRAINSIZE:
	  grainsize_seen = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  தொடர்;

	நிலை OMP_CLAUSE_இலக்கம்_TASKS:
	  இலக்கம்_tasks_seen = உண்மை;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  தொடர்;

	நிலை OMP_CLAUSE_MERGEABLE:
	  mergeable_seen = உண்மை;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  தொடர்;

	நிலை OMP_CLAUSE_NOGROUP:
	  nogroup_seen = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  தொடர்;

	நிலை OMP_CLAUSE_SCHEDULE:
	  schedule_clause = c;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  தொடர்;

	நிலை OMP_CLAUSE_ORDERED:
	  ordered_clause = c;
	  எனில் (order_clause)
	    {
	      error_at (OMP_CLAUSE_LOCATION (*order_clause),
			"%<order%> clause must not be used together "
			"with %<ordered%> clause");
	      *order_clause = OMP_CLAUSE_CHAIN (*order_clause);
	      order_clause = வெற்று;
	    }
	  pc = &OMP_CLAUSE_CHAIN (c);
	  தொடர்;

	நிலை OMP_CLAUSE_SAFELEN:
	  safelen = c;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  தொடர்;
	நிலை OMP_CLAUSE_SIMDLEN:
	  simdlen = c;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  தொடர்;

	நிலை OMP_CLAUSE_FULL:
	  full_seen = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  தொடர்;

	நிலை OMP_CLAUSE_PARTIAL:
	  partial_seen = உண்மை;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  தொடர்;

	நிலை OMP_CLAUSE_SIZES:
	  pc = &OMP_CLAUSE_CHAIN (c);
	  தொடர்;

	நிலை OMP_CLAUSE_INBRANCH:
	நிலை OMP_CLAUSE_NOTINBRANCH:
	  எனில் (branch_seen)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<inbranch%> clause is incompatible with "
			"%<notinbranch%>");
	      remove = உண்மை;
	      நிறுத்து;
	    }
	  branch_seen = உண்மை;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  தொடர்;

	நிலை OMP_CLAUSE_INCLUSIVE:
	நிலை OMP_CLAUSE_EXCLUSIVE:
	  need_complete = உண்மை;
	  need_implicitly_determined = உண்மை;
	  t = OMP_CLAUSE_DECL (c);
	  எனில் (!VAR_P (t) && மரம்_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %qs", t,
			omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	      remove = உண்மை;
	    }
	  நிறுத்து;

	நிலை OMP_CLAUSE_INIT:
	  init_seen = உண்மை;
	  எனில் (!OMP_CLAUSE_INIT_TARGETSYNC (c))
	    init_no_targetsync_clause = c;
	  /* FALLTHRU */
	நிலை OMP_CLAUSE_DESTROY:
	நிலை OMP_CLAUSE_USE:
	  init_use_destroy_seen = உண்மை;
	  t = OMP_CLAUSE_DECL (c);
	  எனில் (bitmap_bit_p (&generic_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD appears more than once in action clauses", t);
	      remove = உண்மை;
	      நிறுத்து;
	    }
	  bitmap_set_bit (&generic_head, DECL_UID (t));
	  /* FALLTHRU */
	நிலை OMP_CLAUSE_INTEROP:
	  எனில் (/* ort == C_ORT_OMP_INTEROP [uncomment for depobj init]  */
		   !c_omp_interop_t_p (மரம்_TYPE (OMP_CLAUSE_DECL (c))))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD must be of %<omp_interop_t%>",
			OMP_CLAUSE_DECL (c));
	      remove = உண்மை;
	    }
	  இல்லையெனில் எனில் ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_INIT
		    || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DESTROY)
		   && மரம்_READONLY (OMP_CLAUSE_DECL (c)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD shall not be const", OMP_CLAUSE_DECL (c));
	      remove = உண்மை;
	    }
	  pc = &OMP_CLAUSE_CHAIN (c);
	  நிறுத்து;
	இயல்பு:
	  gcc_unreachable ();
	}

      எனில் (!remove)
	{
	  t = OMP_CLAUSE_DECL (c);

	  எனில் (need_complete)
	    {
	      t = require_complete_type (OMP_CLAUSE_LOCATION (c), t);
	      எனில் (t == error_mark_முனை)
		remove = உண்மை;
	    }

	  எனில் (need_implicitly_determined)
	    {
	      மாறிலி எழுத்து *share_name = வெற்று;

	      எனில் (VAR_P (t) && DECL_THREAD_LOCAL_P (t))
		share_name = "threadprivate";
	      இல்லையெனில் தேர்வு (c_omp_predetermined_sharing (t))
		{
		நிலை OMP_CLAUSE_DEFAULT_UNSPECIFIED:
		  நிறுத்து;
		நிலை OMP_CLAUSE_DEFAULT_SHARED:
		  எனில் ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_SHARED
		       || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_FIRSTPRIVATE)
		      && c_omp_predefined_variable (t))
		    /* The __func__ variable and similar function-local
		       predefined variables may be listed in a shared or
		       firstprivate clause.  */
		    நிறுத்து;
		  share_name = "shared";
		  நிறுத்து;
		நிலை OMP_CLAUSE_DEFAULT_PRIVATE:
		  share_name = "private";
		  நிறுத்து;
		இயல்பு:
		  gcc_unreachable ();
		}
	      எனில் (share_name)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qE is predetermined %qs for %qs",
			    t, share_name,
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  remove = உண்மை;
		}
	      இல்லையெனில் எனில் (மரம்_READONLY (t)
		       && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_SHARED
		       && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_FIRSTPRIVATE)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<const%> qualified %qE may appear only in "
			    "%<shared%> or %<firstprivate%> clauses", t);
		  remove = உண்மை;
		}
	    }
	}

      எனில் (remove)
	{
	  எனில் (grp_start_p)
	    {
	      /* If we found a clause to remove, we want to remove the whole
		 expanded group, otherwise gimplify
		 (omp_resolve_clause_dependencies) can get confused.  */
	      *grp_start_p = grp_sentinel;
	      pc = grp_start_p;
	      grp_start_p = வெற்று;
	    }
	  இல்லையெனில்
	    *pc = OMP_CLAUSE_CHAIN (c);
	}
      இல்லையெனில்
	pc = &OMP_CLAUSE_CHAIN (c);
    }

  எனில் (grp_start_p
      && OMP_CLAUSE_HAS_ITERATORS (*grp_start_p))
    க்கு (மரம் gc = *grp_start_p; gc; gc = OMP_CLAUSE_CHAIN (gc))
      OMP_CLAUSE_ITERATORS (gc) = OMP_CLAUSE_ITERATORS (*grp_start_p);

  எனில் (simdlen
      && safelen
      && மரம்_int_cst_lt (OMP_CLAUSE_SAFELEN_கோவை (safelen),
			  OMP_CLAUSE_SIMDLEN_கோவை (simdlen)))
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
      OMP_CLAUSE_SIMDLEN_கோவை (simdlen)
	= OMP_CLAUSE_SAFELEN_கோவை (safelen);
    }

  எனில் (ordered_clause
      && schedule_clause
      && (OMP_CLAUSE_SCHEDULE_KIND (schedule_clause)
	  & OMP_CLAUSE_SCHEDULE_NONMONOTONIC))
    {
      error_at (OMP_CLAUSE_LOCATION (schedule_clause),
		"%<nonmonotonic%> schedule modifier specified together "
		"with %<ordered%> clause");
      OMP_CLAUSE_SCHEDULE_KIND (schedule_clause)
	= (எண்ணிக்கை omp_clause_schedule_kind)
	  (OMP_CLAUSE_SCHEDULE_KIND (schedule_clause)
	   & ~OMP_CLAUSE_SCHEDULE_NONMONOTONIC);
    }

  எனில் (reduction_seen < 0 && ordered_clause)
    {
      error_at (OMP_CLAUSE_LOCATION (ordered_clause),
		"%qs clause specified together with %<inscan%> "
		"%<reduction%> clause", "ordered");
      reduction_seen = -2;
    }

  எனில் (reduction_seen < 0 && schedule_clause)
    {
      error_at (OMP_CLAUSE_LOCATION (schedule_clause),
		"%qs clause specified together with %<inscan%> "
		"%<reduction%> clause", "schedule");
      reduction_seen = -2;
    }

  எனில் (linear_variable_step_check
      || reduction_seen == -2
      || allocate_seen
      || target_in_reduction_seen)
    க்கு (pc = &clauses, c = clauses; c ; c = *pc)
      {
	தருக்க remove = பொய்;
	எனில் (allocate_seen)
	  தேர்வு (OMP_CLAUSE_CODE (c))
	    {
	    நிலை OMP_CLAUSE_REDUCTION:
	    நிலை OMP_CLAUSE_IN_REDUCTION:
	    நிலை OMP_CLAUSE_TASK_REDUCTION:
	      எனில் (மரம்_CODE (OMP_CLAUSE_DECL (c)) == MEM_REF)
		{
		  t = மரம்_OPERAND (OMP_CLAUSE_DECL (c), 0);
		  எனில் (மரம்_CODE (t) == POINTER_PLUS_கோவை)
		    t = மரம்_OPERAND (t, 0);
		  எனில் (மரம்_CODE (t) == ADDR_கோவை
		      || INDIRECT_REF_P (t))
		    t = மரம்_OPERAND (t, 0);
		  எனில் (DECL_P (t))
		    bitmap_clear_bit (&aligned_head, DECL_UID (t));
		  நிறுத்து;
		}
	      /* FALLTHRU */
	    நிலை OMP_CLAUSE_PRIVATE:
	    நிலை OMP_CLAUSE_FIRSTPRIVATE:
	    நிலை OMP_CLAUSE_LASTPRIVATE:
	    நிலை OMP_CLAUSE_LINEAR:
	      எனில் (DECL_P (OMP_CLAUSE_DECL (c)))
		bitmap_clear_bit (&aligned_head,
				  DECL_UID (OMP_CLAUSE_DECL (c)));
	      நிறுத்து;
	    இயல்பு:
	      நிறுத்து;
	    }
	எனில் (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_LINEAR
	    && OMP_CLAUSE_LINEAR_VARIABLE_STRIDE (c)
	    && !bitmap_bit_p (&map_head,
			      DECL_UID (OMP_CLAUSE_LINEAR_STEP (c))))
	  {
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%<linear%> clause step is a parameter %qD not "
		      "specified in %<uniform%> clause",
		      OMP_CLAUSE_LINEAR_STEP (c));
	    remove = உண்மை;
	  }
	இல்லையெனில் எனில் (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
		 && reduction_seen == -2)
	  OMP_CLAUSE_REDUCTION_INSCAN (c) = 0;
	எனில் (target_in_reduction_seen
	    && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP)
	  {
	    மரம் t = OMP_CLAUSE_DECL (c);
	    போது (handled_component_p (t)
		   || INDIRECT_REF_P (t)
		   || மரம்_CODE (t) == ADDR_கோவை
		   || மரம்_CODE (t) == MEM_REF
		   || மரம்_CODE (t) == NON_LVALUE_கோவை)
	      t = மரம்_OPERAND (t, 0);
	    எனில் (DECL_P (t)
		&& bitmap_bit_p (&oacc_reduction_head, DECL_UID (t)))
	      OMP_CLAUSE_MAP_IN_REDUCTION (c) = 1;
	  }

	எனில் (remove)
	  *pc = OMP_CLAUSE_CHAIN (c);
	இல்லையெனில்
	  pc = &OMP_CLAUSE_CHAIN (c);
      }

  எனில் (allocate_seen)
    க்கு (pc = &clauses, c = clauses; c ; c = *pc)
      {
	தருக்க remove = பொய்;
	எனில் (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ALLOCATE
	    && !OMP_CLAUSE_ALLOCATE_COMBINED (c)
	    && bitmap_bit_p (&aligned_head, DECL_UID (OMP_CLAUSE_DECL (c))))
	  {
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD specified in %<allocate%> clause but not in "
		      "an explicit privatization clause", OMP_CLAUSE_DECL (c));
	    remove = உண்மை;
	  }
	எனில் (remove)
	  *pc = OMP_CLAUSE_CHAIN (c);
	இல்லையெனில்
	  pc = &OMP_CLAUSE_CHAIN (c);
      }

  எனில் (nogroup_seen && reduction_seen)
    {
      error_at (OMP_CLAUSE_LOCATION (*nogroup_seen),
		"%<nogroup%> clause must not be used together with "
		"%<reduction%> clause");
      *nogroup_seen = OMP_CLAUSE_CHAIN (*nogroup_seen);
    }

  எனில் (grainsize_seen && இலக்கம்_tasks_seen)
    {
      error_at (OMP_CLAUSE_LOCATION (*grainsize_seen),
		"%<grainsize%> clause must not be used together with "
		"%<num_tasks%> clause");
      *grainsize_seen = OMP_CLAUSE_CHAIN (*grainsize_seen);
    }

  எனில் (full_seen && partial_seen)
    {
      error_at (OMP_CLAUSE_LOCATION (*full_seen),
		"%<full%> clause must not be used together with "
		"%<partial%> clause");
      *full_seen = OMP_CLAUSE_CHAIN (*full_seen);
    }

  எனில் (detach_seen)
    {
      எனில் (mergeable_seen)
	{
	  error_at (OMP_CLAUSE_LOCATION (*detach_seen),
		    "%<detach%> clause must not be used together with "
		    "%<mergeable%> clause");
	  *detach_seen = OMP_CLAUSE_CHAIN (*detach_seen);
	}
      இல்லையெனில்
	{
	  மரம் detach_decl = OMP_CLAUSE_DECL (*detach_seen);

	  க்கு (pc = &clauses, c = clauses; c ; c = *pc)
	    {
	      தருக்க remove = பொய்;
	      எனில் ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_SHARED
		   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_PRIVATE
		   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_FIRSTPRIVATE
		   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_LASTPRIVATE)
		  && OMP_CLAUSE_DECL (c) == detach_decl)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "the event handle of a %<detach%> clause "
			    "should not be in a data-sharing clause");
		  remove = உண்மை;
		}
	      எனில் (remove)
		*pc = OMP_CLAUSE_CHAIN (c);
	      இல்லையெனில்
		pc = &OMP_CLAUSE_CHAIN (c);
	    }
	}
    }

  எனில் (ort == C_ORT_OMP_INTEROP
      && depend_clause
      && (!init_use_destroy_seen
	  || (init_seen && init_no_targetsync_clause)))
    {
      error_at (OMP_CLAUSE_LOCATION (depend_clause),
		"%<depend%> clause requires action clauses with "
		"%<targetsync%> interop-type");
      எனில் (init_no_targetsync_clause)
	inform (OMP_CLAUSE_LOCATION (init_no_targetsync_clause),
		"%<init%> clause lacks the %<targetsync%> modifier");
    }

  bitmap_obstack_release (வெற்று);
  திரும்பு clauses;
}

/* Do processing necessary to make CLAUSES well-formed, where CLAUSES result
   from implicit instantiation of user-defined mappers (in gimplify.cc).  */

மரம்
c_omp_finish_mapper_clauses (மரம் clauses)
{
  திரும்பு c_finish_omp_clauses (clauses, C_ORT_OMP);
}

/* Return code to initialize DST with a copy constructor from SRC.
   C doesn't have copy constructors nor assignment operators, only for
   _Atomic vars we need to perform __atomic_load from src into a temporary
   followed by __atomic_store of the temporary to dst.  */

மரம்
c_omp_clause_copy_ctor (மரம் clause, மரம் dst, மரம் src)
{
  எனில் (!really_atomic_lvalue (dst) && !really_atomic_lvalue (src))
    திரும்பு build2 (MODIFY_கோவை, மரம்_TYPE (dst), dst, src);

  location_t loc = OMP_CLAUSE_LOCATION (clause);
  மரம் type = மரம்_TYPE (dst);
  மரம் nonatomic_type = build_qualified_type (type, TYPE_UNQUALIFIED);
  மரம் tmp = create_tmp_var (nonatomic_type);
  மரம் tmp_addr = build_fold_addr_கோவை (tmp);
  மரம்_ADDRESSABLE (tmp) = 1;
  suppress_warning (tmp);
  மரம் src_addr = build_fold_addr_கோவை (src);
  மரம் dst_addr = build_fold_addr_கோவை (dst);
  மரம் seq_cst = build_int_cst (integer_type_முனை, MEMMODEL_SEQ_CST);
  vec<மரம், va_gc> *params;
  /* Expansion of a generic atomic load may require an addition
     element, so allocate enough to prevent a resize.  */
  vec_alloc (params, 4);

  /* Build __atomic_load (&src, &tmp, SEQ_CST);  */
  மரம் fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_LOAD);
  params->quick_தள்ளு (src_addr);
  params->quick_தள்ளு (tmp_addr);
  params->quick_தள்ளு (seq_cst);
  மரம் load = c_build_function_call_vec (loc, vNULL, fndecl, params, வெற்று);

  vec_alloc (params, 4);

  /* Build __atomic_store (&dst, &tmp, SEQ_CST);  */
  fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_STORE);
  params->quick_தள்ளு (dst_addr);
  params->quick_தள்ளு (tmp_addr);
  params->quick_தள்ளு (seq_cst);
  மரம் store = c_build_function_call_vec (loc, vNULL, fndecl, params, வெற்று);
  திரும்பு build2 (COMPOUND_கோவை, void_type_முனை, load, store);
}

/* Create a transaction node.  */

மரம்
c_finish_transaction (location_t loc, மரம் block, முழு flags)
{
  மரம் stmt = build_stmt (loc, TRANSACTION_கோவை, block);
  எனில் (flags & TM_STMT_ATTR_OUTER)
    TRANSACTION_கோவை_OUTER (stmt) = 1;
  எனில் (flags & TM_STMT_ATTR_RELAXED)
    TRANSACTION_கோவை_RELAXED (stmt) = 1;
  திரும்பு add_stmt (stmt);
}

/* Make a variant type in the proper way for C/C++, propagating qualifiers
   down to the element type of an array.  If ORIG_QUAL_TYPE is not
   NULL, then it should be used as the qualified type
   ORIG_QUAL_INDIRECT levels down in array type derivation (to
   preserve information about the typedef name from which an array
   type was derived).  */

மரம்
c_build_qualified_type (மரம் type, முழு type_quals, மரம் orig_qual_type,
			size_t orig_qual_indirect)
{
  எனில் (type == error_mark_முனை)
    திரும்பு type;

  எனில் (மரம்_CODE (type) == ARRAY_TYPE)
    {
      மரம் t;
      மரம் element_type = c_build_qualified_type (மரம்_TYPE (type),
						  type_quals, orig_qual_type,
						  orig_qual_indirect - 1);

      /* See if we already have an identically qualified type.  */
      எனில் (orig_qual_type && orig_qual_indirect == 0)
	t = orig_qual_type;
      இல்லையெனில்
	க்கு (t = TYPE_MAIN_VARIANT (type); t; t = TYPE_NEXT_VARIANT (t))
	  {
	    எனில் (TYPE_QUALS (strip_array_types (t)) == type_quals
		&& TYPE_NAME (t) == TYPE_NAME (type)
		&& TYPE_CONTEXT (t) == TYPE_CONTEXT (type)
		&& attribute_list_equal (TYPE_ATTRIBUTES (t),
					 TYPE_ATTRIBUTES (type)))
	      நிறுத்து;
	  }
      எனில் (!t)
	{
          மரம் domain = TYPE_DOMAIN (type);

	  t = build_variant_type_copy (type);
	  மரம்_TYPE (t) = element_type;
	  TYPE_ADDR_SPACE (t) = TYPE_ADDR_SPACE (element_type);

          எனில் (TYPE_STRUCTURAL_EQUALITY_P (element_type)
              || (domain && TYPE_STRUCTURAL_EQUALITY_P (domain)))
            SET_TYPE_STRUCTURAL_EQUALITY (t);
          இல்லையெனில் எனில் (TYPE_CANONICAL (element_type) != element_type
                   || (domain && TYPE_CANONICAL (domain) != domain))
            {
              மரம் unqualified_canon
		= c_build_array_type (TYPE_CANONICAL (element_type),
				      domain ? TYPE_CANONICAL (domain)
					     : NULL_மரம்);
              எனில் (TYPE_REVERSE_STORAGE_ORDER (type))
                {
                  unqualified_canon
		    = build_distinct_type_copy (unqualified_canon);
                  TYPE_REVERSE_STORAGE_ORDER (unqualified_canon) = 1;
                }
              TYPE_CANONICAL (t)
		= c_build_qualified_type (unqualified_canon, type_quals);
            }
          இல்லையெனில்
            TYPE_CANONICAL (t) = t;
	}
      திரும்பு t;
    }

  /* A restrict-qualified pointer type must be a pointer to object or
     incomplete type.  Note that the use of POINTER_TYPE_P also allows
     REFERENCE_TYPEs, which is appropriate for C++.  */
  எனில் ((type_quals & TYPE_QUAL_RESTRICT)
      && (!POINTER_TYPE_P (type)
	  || !C_TYPE_OBJECT_OR_INCOMPLETE_P (மரம்_TYPE (type))))
    {
      error ("invalid use of %<restrict%>");
      type_quals &= ~TYPE_QUAL_RESTRICT;
    }

  மரம் var_type = (orig_qual_type && orig_qual_indirect == 0
		   ? orig_qual_type
		   : build_qualified_type (type, type_quals));

  gcc_checking_assert (C_TYPE_VARIABLE_SIZE (var_type)
		       == C_TYPE_VARIABLE_SIZE (type));
  gcc_checking_assert (c_type_variably_modified_p (var_type)
		       == c_type_variably_modified_p (type));

  /* A variant type does not inherit the list of incomplete vars from the
     type main variant.  */
  எனில் ((RECORD_OR_UNION_TYPE_P (var_type)
       || மரம்_CODE (var_type) == ENUMERAL_TYPE)
      && TYPE_MAIN_VARIANT (var_type) != var_type)
    C_TYPE_INCOMPLETE_VARS (var_type) = 0;
  திரும்பு var_type;
}

/* Build a VA_ARG_EXPR for the C parser.  */

மரம்
c_build_va_arg (location_t loc1, மரம் கோவை, location_t loc2, மரம் type,
		மரம் type_கோவை)
{
  எனில் (error_operand_p (type))
    திரும்பு error_mark_முனை;
  /* VA_ARG_EXPR cannot be used for a scalar va_list with reverse storage
     order because it takes the address of the expression.  */
  இல்லையெனில் எனில் (handled_component_p (கோவை)
	   && reverse_storage_order_for_component_p (கோவை))
    {
      error_at (loc1, "cannot use %<va_arg%> with reverse storage order");
      திரும்பு error_mark_முனை;
    }
  இல்லையெனில் எனில் (!COMPLETE_TYPE_P (type))
    {
      error_at (loc2, "second argument to %<va_arg%> is of incomplete "
		"type %qT", type);
      திரும்பு error_mark_முனை;
    }
  இல்லையெனில் எனில் (மரம்_CODE (type) == FUNCTION_TYPE)
    {
      error_at (loc2, "second argument to %<va_arg%> is a function type %qT",
		type);
      திரும்பு error_mark_முனை;
    }
  இல்லையெனில் எனில் (மரம்_CODE (type) == ARRAY_TYPE && C_TYPE_VARIABLE_SIZE (type)
	   && !flag_isoc99)
    {
      error_at (loc2, "second argument to %<va_arg%> is an array type %qT",
		type);
      திரும்பு error_mark_முனை;
    }
  இல்லையெனில் எனில் (warn_cxx_compat && மரம்_CODE (type) == ENUMERAL_TYPE)
    warning_at (loc2, OPT_Wc___compat,
		"C++ requires promoted type, not enum type, in %<va_arg%>");

  எனில் (flag_isoc99 && மரம்_CODE (type) == ARRAY_TYPE)
    {
      warning_at (loc2, 0, "second argument to %<va_arg%> is an array type %qT",
		  type);
      /* We create a trap but evaluate side effects first.  */
      மரம் trapfn = builtin_decl_explicit (BUILT_IN_TRAP);
      trapfn = build_call_கோவை_loc (loc2, trapfn, 0);
      மரம் e2 = build2 (COMPOUND_கோவை, void_type_முனை, கோவை, trapfn);
      /* Return a compound literal of the right type.  */
      மரம் e1 = build_compound_literal (loc2, type, வெற்று, உண்மை, 0, வெற்று);
      கோவை = build2 (COMPOUND_கோவை, type, e2, e1);
    }
  இல்லையெனில்
    கோவை = build_va_arg (loc2, கோவை, type);

  எனில் (type_கோவை)
    கோவை = build2 (COMPOUND_கோவை, மரம்_TYPE (கோவை), type_கோவை, கோவை);

  திரும்பு கோவை;
}

/* Return truthvalue of whether T1 is the same tree structure as T2.
   Return 1 if they are the same. Return false if they are different.  */

தருக்க
c_மரம்_equal (மரம் t1, மரம் t2)
{
  எண்ணிக்கை மரம்_code code1, code2;

  எனில் (t1 == t2)
    திரும்பு உண்மை;
  எனில் (!t1 || !t2)
    திரும்பு பொய்;

  க்கு (code1 = மரம்_CODE (t1); code1 == NON_LVALUE_கோவை;
       code1 = மரம்_CODE (t1))
    t1 = மரம்_OPERAND (t1, 0);
  க்கு (code2 = மரம்_CODE (t2); code2 == NON_LVALUE_கோவை;
       code2 = மரம்_CODE (t2))
    t2 = மரம்_OPERAND (t2, 0);

  /* They might have become equal now.  */
  எனில் (t1 == t2)
    திரும்பு உண்மை;

  எனில் (code1 != code2)
    திரும்பு பொய்;

  எனில் (CONSTANT_CLASS_P (t1) && !comptypes (மரம்_TYPE (t1), மரம்_TYPE (t2)))
    திரும்பு பொய்;

  தேர்வு (code1)
    {
    நிலை INTEGER_CST:
      திரும்பு wi::to_wide (t1) == wi::to_wide (t2);

    நிலை REAL_CST:
      திரும்பு real_equal (&மரம்_REAL_CST (t1), &மரம்_REAL_CST (t2));

    நிலை STRING_CST:
      திரும்பு மரம்_STRING_LENGTH (t1) == மரம்_STRING_LENGTH (t2)
	&& !memcmp (மரம்_STRING_POINTER (t1), மரம்_STRING_POINTER (t2),
		    மரம்_STRING_LENGTH (t1));

    நிலை FIXED_CST:
      திரும்பு FIXED_மதிப்புகள்_IDENTICAL (மரம்_FIXED_CST (t1),
				     மரம்_FIXED_CST (t2));

    நிலை COMPLEX_CST:
      திரும்பு c_மரம்_equal (மரம்_REALPART (t1), மரம்_REALPART (t2))
	     && c_மரம்_equal (மரம்_IMAGPART (t1), மரம்_IMAGPART (t2));

    நிலை VECTOR_CST:
      திரும்பு operand_equal_p (t1, t2, OEP_ONLY_CONST);

    நிலை CONSTRUCTOR:
      /* We need to do this when determining whether or not two
	 non-type pointer to member function template arguments
	 are the same.  */
      எனில் (!comptypes (மரம்_TYPE (t1), மரம்_TYPE (t2))
	  || CONSTRUCTOR_NELTS (t1) != CONSTRUCTOR_NELTS (t2))
	திரும்பு பொய்;
      {
	மரம் field, மதிப்பு;
	unsigned முழு i;
	FOR_EACH_CONSTRUCTOR_ELT (CONSTRUCTOR_ELTS (t1), i, field, மதிப்பு)
	  {
	    constructor_elt *elt2 = CONSTRUCTOR_ELT (t2, i);
	    எனில் (!c_மரம்_equal (field, elt2->index)
		|| !c_மரம்_equal (மதிப்பு, elt2->மதிப்பு))
	      திரும்பு பொய்;
	  }
      }
      திரும்பு உண்மை;

    நிலை மரம்_LIST:
      எனில் (!c_மரம்_equal (மரம்_PURPOSE (t1), மரம்_PURPOSE (t2)))
	திரும்பு பொய்;
      எனில் (!c_மரம்_equal (மரம்_மதிப்பு (t1), மரம்_மதிப்பு (t2)))
	திரும்பு பொய்;
      திரும்பு c_மரம்_equal (மரம்_CHAIN (t1), மரம்_CHAIN (t2));

    நிலை SAVE_கோவை:
      திரும்பு c_மரம்_equal (மரம்_OPERAND (t1, 0), மரம்_OPERAND (t2, 0));

    நிலை CALL_கோவை:
      {
	மரம் arg1, arg2;
	call_கோவை_arg_iterator iter1, iter2;
	எனில் (!c_மரம்_equal (CALL_கோவை_FN (t1), CALL_கோவை_FN (t2)))
	  திரும்பு பொய்;
	க்கு (arg1 = first_call_கோவை_arg (t1, &iter1),
	       arg2 = first_call_கோவை_arg (t2, &iter2);
	     arg1 && arg2;
	     arg1 = next_call_கோவை_arg (&iter1),
	       arg2 = next_call_கோவை_arg (&iter2))
	  எனில் (!c_மரம்_equal (arg1, arg2))
	    திரும்பு பொய்;
	எனில் (arg1 || arg2)
	  திரும்பு பொய்;
	திரும்பு உண்மை;
      }

    நிலை TARGET_கோவை:
      {
	மரம் o1 = மரம்_OPERAND (t1, 0);
	மரம் o2 = மரம்_OPERAND (t2, 0);

	/* Special case: if either target is an unallocated VAR_DECL,
	   it means that it's going to be unified with whatever the
	   TARGET_EXPR is really supposed to initialize, so treat it
	   as being equivalent to anything.  */
	எனில் (VAR_P (o1) && DECL_NAME (o1) == NULL_மரம்
	    && !DECL_RTL_SET_P (o1))
	  /*Nop*/;
	இல்லையெனில் எனில் (VAR_P (o2) && DECL_NAME (o2) == NULL_மரம்
		 && !DECL_RTL_SET_P (o2))
	  /*Nop*/;
	இல்லையெனில் எனில் (!c_மரம்_equal (o1, o2))
	  திரும்பு பொய்;

	திரும்பு c_மரம்_equal (மரம்_OPERAND (t1, 1), மரம்_OPERAND (t2, 1));
      }

    நிலை COMPONENT_REF:
      எனில் (மரம்_OPERAND (t1, 1) != மரம்_OPERAND (t2, 1))
	திரும்பு பொய்;
      திரும்பு c_மரம்_equal (மரம்_OPERAND (t1, 0), மரம்_OPERAND (t2, 0));

    நிலை PARM_DECL:
    நிலை VAR_DECL:
    நிலை CONST_DECL:
    நிலை FIELD_DECL:
    நிலை FUNCTION_DECL:
    நிலை IDENTIFIER_முனை:
    நிலை SSA_NAME:
      திரும்பு பொய்;

    நிலை மரம்_VEC:
      {
	unsigned ix;
	எனில் (மரம்_VEC_LENGTH (t1) != மரம்_VEC_LENGTH (t2))
	  திரும்பு பொய்;
	க்கு (ix = மரம்_VEC_LENGTH (t1); ix--;)
	  எனில் (!c_மரம்_equal (மரம்_VEC_ELT (t1, ix),
			     மரம்_VEC_ELT (t2, ix)))
	    திரும்பு பொய்;
	திரும்பு உண்மை;
      }

    CASE_CONVERT:
      எனில் (!comptypes (மரம்_TYPE (t1), மரம்_TYPE (t2)))
	திரும்பு பொய்;
      நிறுத்து;

    இயல்பு:
      நிறுத்து;
    }

  தேர்வு (மரம்_CODE_CLASS (code1))
    {
    நிலை tcc_unary:
    நிலை tcc_இருமம்:
    நிலை tcc_comparison:
    நிலை tcc_expression:
    நிலை tcc_vl_exp:
    நிலை tcc_reference:
    நிலை tcc_statement:
      {
	முழு i, n = மரம்_OPERAND_LENGTH (t1);

	தேர்வு (code1)
	  {
	  நிலை PREINCREMENT_கோவை:
	  நிலை PREDECREMENT_கோவை:
	  நிலை POSTINCREMENT_கோவை:
	  நிலை POSTDECREMENT_கோவை:
	    n = 1;
	    நிறுத்து;
	  நிலை ARRAY_REF:
	    n = 2;
	    நிறுத்து;
	  இயல்பு:
	    நிறுத்து;
	  }

	எனில் (மரம்_CODE_CLASS (code1) == tcc_vl_exp
	    && n != மரம்_OPERAND_LENGTH (t2))
	  திரும்பு பொய்;

	க்கு (i = 0; i < n; ++i)
	  எனில் (!c_மரம்_equal (மரம்_OPERAND (t1, i), மரம்_OPERAND (t2, i)))
	    திரும்பு பொய்;

	திரும்பு உண்மை;
      }

    நிலை tcc_type:
      திரும்பு comptypes (t1, t2);
    இயல்பு:
      gcc_unreachable ();
    }
}

/* Returns true when the function declaration FNDECL is implicit,
   introduced as a result of a call to an otherwise undeclared
   function, and false otherwise.  */

தருக்க
c_decl_implicit (const_மரம் fndecl)
{
  திரும்பு C_DECL_IMPLICIT (fndecl);
}
