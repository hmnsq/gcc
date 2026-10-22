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

#अन्तर्भाव "config.h"
#अन्तर्भाव "system.h"
#अन्तर्भाव "coretypes.h"
#अन्तर्भाव "memmodel.h"
#अन्तर्भाव "target.h"
#अन्तर्भाव "function.h"
#अन्तर्भाव "bitmap.h"
#अन्तर्भाव "c-tree.h"
#अन्तर्भाव "gimple-expr.h"
#अन्तर्भाव "predict.h"
#अन्तर्भाव "stor-layout.h"
#अन्तर्भाव "trans-mem.h"
#अन्तर्भाव "varasm.h"
#अन्तर्भाव "stmt.h"
#अन्तर्भाव "langhooks.h"
#अन्तर्भाव "c-lang.h"
#अन्तर्भाव "intl.h"
#अन्तर्भाव "tree-iterator.h"
#अन्तर्भाव "gimplify.h"
#अन्तर्भाव "tree-inline.h"
#अन्तर्भाव "omp-general.h"
#अन्तर्भाव "c-family/c-objc.h"
#अन्तर्भाव "c-family/c-ubsan.h"
#अन्तर्भाव "gomp-constants.h"
#अन्तर्भाव "spellcheck-tree.h"
#अन्तर्भाव "c-family/c-type-mismatch.h"
#अन्तर्भाव "stringpool.h"
#अन्तर्भाव "attribs.h"
#अन्तर्भाव "asan.h"
#अन्तर्भाव "realmpfr.h"
#अन्तर्भाव "tree-pretty-print-markup.h"
#अन्तर्भाव "gcc-urlifier.h"

/* Possible cases of implicit conversions.  Used to select diagnostic messages
   and control folding initializers in convert_for_assignment.  */
गणना impl_conv {
  ic_argpass,
  ic_assign,
  ic_init,
  ic_init_const,
  ic_return
};

/* The level of nesting inside "__alignof__".  */
पूर्णाङ्क in_alignof;

/* The level of nesting inside "sizeof".  */
पूर्णाङ्क in_sizeof;

/* The level of nesting inside "countof".  */
पूर्णाङ्क in_countof;

/* The level of nesting inside "typeof".  */
पूर्णाङ्क in_typeof;

/* The level of nesting inside "_Generic".  */
पूर्णाङ्क in_generic;

/* True when parsing OpenMP loop expressions.  */
तार्किक c_in_omp_for;

/* True when parsing OpenMP map clause.  */
तार्किक c_omp_array_section_p;

/* The argument of last parsed sizeof expression, only to be tested
   if expr.original_code == SIZEOF_EXPR.  */
वृक्ष c_last_sizeof_arg;
location_t c_last_sizeof_loc;

/* Nonzero if we might need to print a "missing braces around
   initializer" message within this initializer.  */
स्थिर पूर्णाङ्क found_missing_braces;

स्थिर तार्किक require_constant_मूल्य;
स्थिर तार्किक require_constant_elements;
स्थिर तार्किक require_constexpr_मूल्य;

स्थिर वृक्ष qualify_type (वृक्ष, वृक्ष);
संरचना comptypes_data;
स्थिर तार्किक tagged_types_tu_compatible_p (const_वृक्ष, const_वृक्ष,
					  संरचना comptypes_data *);
स्थिर तार्किक comp_target_types (location_t, वृक्ष, वृक्ष);
स्थिर तार्किक function_types_compatible_p (const_वृक्ष, const_वृक्ष,
					 संरचना comptypes_data *);
स्थिर तार्किक type_lists_compatible_p (const_वृक्ष, const_वृक्ष,
				     संरचना comptypes_data *);
स्थिर पूर्णाङ्क convert_arguments (location_t, vec<location_t>, वृक्ष,
			      vec<वृक्ष, va_gc> *, vec<वृक्ष, va_gc> *, वृक्ष,
			      वृक्ष);
स्थिर वृक्ष pointer_diff (location_t, वृक्ष, वृक्ष, वृक्ष *);
स्थिर वृक्ष convert_for_assignment (location_t, location_t, वृक्ष, वृक्ष, वृक्ष,
				    गणना impl_conv, तार्किक, वृक्ष, वृक्ष, पूर्णाङ्क,
				    पूर्णाङ्क = 0);
स्थिर वृक्ष valid_compound_व्यंजक_initializer (वृक्ष, वृक्ष);
स्थिर शून्य धकेलो_string (ध्रुव वर्ण *);
स्थिर शून्य धकेलो_member_name (वृक्ष);
स्थिर पूर्णाङ्क spelling_length (शून्य);
स्थिर वर्ण *print_spelling (वर्ण *);
स्थिर शून्य warning_init (location_t, पूर्णाङ्क, ध्रुव वर्ण *);
स्थिर वृक्ष digest_init (location_t, वृक्ष, वृक्ष, वृक्ष, वृक्ष, तार्किक, तार्किक, तार्किक,
			 तार्किक, तार्किक, तार्किक);
स्थिर शून्य output_init_element (location_t, वृक्ष, वृक्ष, तार्किक, वृक्ष, वृक्ष, तार्किक,
				 तार्किक, संरचना obstack *);
स्थिर शून्य output_pending_init_elements (पूर्णाङ्क, संरचना obstack *);
स्थिर तार्किक set_designator (location_t, तार्किक, संरचना obstack *);
स्थिर शून्य धकेलो_range_ढेर (वृक्ष, संरचना obstack *);
स्थिर शून्य add_pending_init (location_t, वृक्ष, वृक्ष, वृक्ष, तार्किक,
			      संरचना obstack *);
स्थिर शून्य set_nonincremental_init (संरचना obstack *);
स्थिर शून्य set_nonincremental_init_from_string (वृक्ष, संरचना obstack *);
स्थिर वृक्ष find_init_member (वृक्ष, संरचना obstack *);
स्थिर शून्य readonly_warning (वृक्ष, गणना lvalue_use);
स्थिर पूर्णाङ्क lvalue_or_else (location_t, const_वृक्ष, गणना lvalue_use);
स्थिर शून्य record_maybe_used_decl (वृक्ष, तार्किक address);
स्थिर तार्किक comptypes_internal (const_वृक्ष, const_वृक्ष,
				संरचना comptypes_data *data);
स्थिर तार्किक comptypes_check_for_composite (वृक्ष t1, वृक्ष t2);
स्थिर तार्किक handle_counted_by_p (वृक्ष);
स्थिर तार्किक शीर्ष_array_vla_p (const_वृक्ष type);


/* Return true if EXP is a null pointer constant, false otherwise.  */

तार्किक
null_pointer_constant_p (const_वृक्ष व्यंजक)
{
  /* This should really operate on c_expr structures, but they aren't
     yet available everywhere required.  */
  वृक्ष type = वृक्ष_TYPE (व्यंजक);

  /* An integer constant expression with the value 0, such an expression
     cast to type void*, or the predefined constant nullptr, are a null
     pointer constant.  */
  यदि (व्यंजक == nullptr_गाँठ)
    प्रत्यागम सत्य;

  प्रत्यागम (वृक्ष_CODE (व्यंजक) == INTEGER_CST
	  && !वृक्ष_OVERFLOW (व्यंजक)
	  && integer_zerop (व्यंजक)
	  && (INTEGRAL_TYPE_P (type)
	      || (वृक्ष_CODE (type) == POINTER_TYPE
		  && VOID_TYPE_P (वृक्ष_TYPE (type))
		  && TYPE_QUALS (वृक्ष_TYPE (type)) == TYPE_UNQUALIFIED)));
}

/* EXPR may appear in an unevaluated part of an integer constant
   expression, but not in an evaluated part.  Wrap it in a
   C_MAYBE_CONST_EXPR, or mark it with TREE_OVERFLOW if it is just an
   INTEGER_CST and we cannot create a C_MAYBE_CONST_EXPR.  */

स्थिर वृक्ष
note_integer_operands (वृक्ष व्यंजक)
{
  वृक्ष ret;
  यदि (वृक्ष_CODE (व्यंजक) == INTEGER_CST && in_late_द्विआधारी_op)
    {
      ret = copy_गाँठ (व्यंजक);
      वृक्ष_OVERFLOW (ret) = 1;
    }
  अन्यथा
    {
      ret = build2 (C_MAYBE_CONST_व्यंजक, वृक्ष_TYPE (व्यंजक), NULL_वृक्ष, व्यंजक);
      C_MAYBE_CONST_व्यंजक_INT_OPERANDS (ret) = 1;
    }
  प्रत्यागम ret;
}

/* Having checked whether EXPR may appear in an unevaluated part of an
   integer constant expression and found that it may, remove any
   C_MAYBE_CONST_EXPR noting this fact and return the resulting
   expression.  */

स्थिर अन्तःस्थ वृक्ष
remove_c_maybe_const_व्यंजक (वृक्ष व्यंजक)
{
  यदि (वृक्ष_CODE (व्यंजक) == C_MAYBE_CONST_व्यंजक)
    प्रत्यागम C_MAYBE_CONST_व्यंजक_व्यंजक (व्यंजक);
  अन्यथा
    प्रत्यागम व्यंजक;
}

/* This is a cache to hold if two types are seen.  */

संरचना tagged_tu_seen_cache {
  ध्रुव संरचना tagged_tu_seen_cache * next;
  const_वृक्ष t1;
  const_वृक्ष t2;
};

/* Do `exp = require_complete_type (loc, exp);' to make sure exp
   does not have an incomplete type.  (That includes void types.)
   LOC is the location of the use.  */

वृक्ष
require_complete_type (location_t loc, वृक्ष मूल्य)
{
  वृक्ष type = वृक्ष_TYPE (मूल्य);

  यदि (error_operand_p (मूल्य))
    प्रत्यागम error_mark_गाँठ;

  /* First, detect a valid value with a complete type.  */
  यदि (COMPLETE_TYPE_P (type))
    प्रत्यागम मूल्य;

  c_incomplete_type_error (loc, मूल्य, type);
  प्रत्यागम error_mark_गाँठ;
}

/* Print an error message for invalid use of an incomplete type.
   VALUE is the expression that was used (or 0 if that isn't known)
   and TYPE is the type that was invalid.  LOC is the location for
   the error.  */

शून्य
c_incomplete_type_error (location_t loc, const_वृक्ष मूल्य, const_वृक्ष type)
{
  /* Avoid duplicate error message.  */
  यदि (वृक्ष_CODE (type) == ERROR_MARK)
    प्रत्यागम;

  यदि (मूल्य != NULL_वृक्ष && (VAR_P (मूल्य) || वृक्ष_CODE (मूल्य) == PARM_DECL))
    error_at (loc, "%qD has an incomplete type %qT", मूल्य, type);
  अन्यथा
    {
    retry:
      /* We must print an error message.  Be clever about what it says.  */

      विकल्प (वृक्ष_CODE (type))
	{
	पक्ष RECORD_TYPE:
	पक्ष UNION_TYPE:
	पक्ष ENUMERAL_TYPE:
	  भङ्ग;

	पक्ष VOID_TYPE:
	  error_at (loc, "invalid use of void expression");
	  प्रत्यागम;

	पक्ष ARRAY_TYPE:
	  यदि (TYPE_DOMAIN (type))
	    {
	      यदि (flexible_array_member_type_p (type))
		{
		  error_at (loc, "invalid use of flexible array member");
		  प्रत्यागम;
		}
	      type = वृक्ष_TYPE (type);
	      गच्छ retry;
	    }
	  error_at (loc, "invalid use of array with unspecified bounds");
	  प्रत्यागम;

	स्वभाव:
	  gcc_unreachable ();
	}

      यदि (वृक्ष_CODE (TYPE_NAME (type)) == IDENTIFIER_गाँठ)
	error_at (loc, "invalid use of undefined type %qT", type);
      अन्यथा
	/* If this type has a typedef-name, the TYPE_NAME is a TYPE_DECL.  */
	error_at (loc, "invalid use of incomplete typedef %qT", type);
    }
}

/* Given a type, apply default promotions wrt unnamed function
   arguments and return the new type.  */

वृक्ष
c_type_promotes_to (वृक्ष type)
{
  वृक्ष ret = NULL_वृक्ष;

  यदि (TYPE_MAIN_VARIANT (type) == float_type_गाँठ)
    ret = double_type_गाँठ;
  अन्यथा यदि (c_promoting_integer_type_p (type))
    {
      /* Preserve unsignedness if not really getting any wider.  */
      यदि (TYPE_UNSIGNED (type)
	  && (TYPE_PRECISION (type) == TYPE_PRECISION (integer_type_गाँठ)))
	ret = unsigned_type_गाँठ;
      अन्यथा
	ret = integer_type_गाँठ;
    }

  यदि (ret != NULL_वृक्ष)
    प्रत्यागम (TYPE_ATOMIC (type)
	    ? c_build_qualified_type (ret, TYPE_QUAL_ATOMIC)
	    : ret);

  प्रत्यागम type;
}

/* Return true if between two named address spaces, whether there is a superset
   named address space that encompasses both address spaces.  If there is a
   superset, return which address space is the superset.  */

स्थिर तार्किक
addr_space_superset (addr_space_t as1, addr_space_t as2, addr_space_t *common)
{
  यदि (as1 == as2)
    {
      *common = as1;
      प्रत्यागम सत्य;
    }
  अन्यथा यदि (targetm.addr_space.subset_p (as1, as2))
    {
      *common = as2;
      प्रत्यागम सत्य;
    }
  अन्यथा यदि (targetm.addr_space.subset_p (as2, as1))
    {
      *common = as1;
      प्रत्यागम सत्य;
    }
  अन्यथा
    प्रत्यागम असत्य;
}

/* Return a variant of TYPE which has all the type qualifiers of LIKE
   as well as those of TYPE.  */

स्थिर वृक्ष
qualify_type (वृक्ष type, वृक्ष like)
{
  addr_space_t as_type = TYPE_ADDR_SPACE (type);
  addr_space_t as_like = TYPE_ADDR_SPACE (like);
  addr_space_t as_common;

  /* If the two named address spaces are different, determine the common
     superset address space.  If there isn't one, raise an error.  */
  यदि (!addr_space_superset (as_type, as_like, &as_common))
    {
      as_common = as_type;
      error ("%qT and %qT are in disjoint named address spaces",
	     type, like);
    }

  प्रत्यागम c_build_qualified_type (type,
				 TYPE_QUALS_NO_ADDR_SPACE (type)
				 | TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (like)
				 | ENCODE_QUAL_ADDR_SPACE (as_common));
}


/* Check consistency of type TYPE.  For derived types, we test that
   C_TYPE_VARIABLE_SIZE and C_TYPE_VARIABLY_MODIFIED are consistent with
   the requirements of the base type.  We also check that arrays with a
   non-constant length are marked with C_TYPE_VARIABLE_SIZE. If any
   inconsistency is detected false is returned and true otherwise.  */

स्थिर तार्किक
c_verify_type (वृक्ष type)
{
  विकल्प (वृक्ष_CODE (type))
    {
    पक्ष POINTER_TYPE:
    पक्ष FUNCTION_TYPE:
    पक्ष ARRAY_TYPE:
      /* Pointer, array, functions are variably modified if and only if the
	 target, element, return type is variably modified.  */
      यदि (!TYPE_STRUCTURAL_EQUALITY_P (type)
	  && (C_TYPE_VARIABLY_MODIFIED (type)
	      != C_TYPE_VARIABLY_MODIFIED (वृक्ष_TYPE (type))))
	प्रत्यागम असत्य;
      /* If the target type is structural equality, the type should also. */
      यदि (!TYPE_STRUCTURAL_EQUALITY_P (type)
	  && TYPE_STRUCTURAL_EQUALITY_P (वृक्ष_TYPE (type)))
	प्रत्यागम असत्य;
    स्वभाव:
       भङ्ग;
    }

  विकल्प (वृक्ष_CODE (type))
    {
    पक्ष POINTER_TYPE:
    पक्ष FUNCTION_TYPE:
      /* Pointer and functions can not have variable size.  */
      यदि (C_TYPE_VARIABLE_SIZE (type))
	प्रत्यागम असत्य;
      भङ्ग;
    पक्ष ARRAY_TYPE:
      /* An array has variable size if and only if it has a non-constant
	 dimensions or its element type has variable size.  */
      यदि ((C_TYPE_VARIABLE_SIZE (वृक्ष_TYPE (type))
	   || शीर्ष_array_vla_p (type))
	  != C_TYPE_VARIABLE_SIZE (type))
	प्रत्यागम असत्य;
      /* If the element type or the array has variable size, then the
	 array has variable size and is variably modified.  */
      यदि (C_TYPE_VARIABLE_SIZE (वृक्ष_TYPE (type))
	  || C_TYPE_VARIABLE_SIZE (type))
	{
	  यदि (!C_TYPE_VARIABLE_SIZE (type))
	    प्रत्यागम असत्य;
	  यदि (!C_TYPE_VARIABLY_MODIFIED (type))
	    प्रत्यागम असत्य;
	}

      /* va_list violates this, accept such types here.  */
      यदि (!COMPLETE_TYPE_P (वृक्ष_TYPE (type)))
	प्रत्यागम सत्य;

      यदि (COMPLETE_TYPE_P (type))
	{
	  /* If the size is unknown, it can not be complete.  */
	  यदि (NULL_वृक्ष == TYPE_DOMAIN (type))
	    प्रत्यागम असत्य;

	  /* Zero-length arrays must have size zero.  */
	  यदि (zero_length_array_type_p (type)
	      && !integer_zerop (TYPE_SIZE (type)))
	    प्रत्यागम असत्य;
	}
      अन्यथा
	{
	  /* If not complete but has a domain, it must be a FAM.  */
	  यदि (NULL_वृक्ष != TYPE_DOMAIN (type)
	      && !flexible_array_member_type_p (type))
	    प्रत्यागम असत्य;
	}
    स्वभाव:
      भङ्ग;
    }
  प्रत्यागम सत्य;
}

/* Propagate C_TYPE_VARIABLY_MODIFIED and C_TYPE_VARIABLE_SIZE
   from a base type to a newly built derived or qualified type.  */

स्थिर वृक्ष
c_set_type_bits (वृक्ष new_type, वृक्ष old_type)
{
  gcc_checking_assert (c_verify_type (old_type));

  यदि (c_type_variably_modified_p (old_type))
    C_TYPE_VARIABLY_MODIFIED (new_type) = सत्य;

  यदि (वृक्ष_CODE (new_type) == ARRAY_TYPE && C_TYPE_VARIABLE_SIZE (old_type))
    {
      C_TYPE_VARIABLY_MODIFIED (new_type) = सत्य;
      C_TYPE_VARIABLE_SIZE (new_type) = सत्य;
    }
  प्रत्यागम new_type;
}

/* Build a pointer type using the default pointer mode.  */

वृक्ष
c_build_pointer_type (वृक्ष to_type)
{
  addr_space_t as = to_type == error_mark_गाँठ ? ADDR_SPACE_GENERIC
					       : TYPE_ADDR_SPACE (to_type);
  machine_mode pointer_mode;

  यदि (as != ADDR_SPACE_GENERIC || c_default_pointer_mode == VOIDmode)
    pointer_mode = targetm.addr_space.pointer_mode (as);
  अन्यथा
    pointer_mode = c_default_pointer_mode;

  प्रत्यागम c_build_pointer_type_for_mode (to_type, pointer_mode, असत्य);
}

/* Build a pointer type using the given mode.  */

वृक्ष
c_build_pointer_type_for_mode (वृक्ष type, machine_mode mode, तार्किक m)
{
  वृक्ष ret = build_pointer_type_for_mode (type, mode, m);
  प्रत्यागम c_set_type_bits (ret, type);
}

/* Build a function type.  */

वृक्ष
c_build_function_type (वृक्ष type, वृक्ष args, तार्किक no)
{
  वृक्ष ret = build_function_type (type, args, no);
  प्रत्यागम c_set_type_bits (ret, type);
}

/* Build an array type.  This sets typeless storage as required
   by C2Y and C_TYPE_VARIABLY_MODIFIED and C_TYPE_VARIABLE_SIZE
   based on the element type and domain.  */

वृक्ष
c_build_array_type (वृक्ष type, वृक्ष domain)
{
  पूर्णाङ्क type_quals = TYPE_QUALS (type);

  /* Identify typeless storage as introduced in C2Y
     and supported also in earlier language modes.  */
  तार्किक typeless = (char_type_p (type) && !(type_quals & TYPE_QUAL_ATOMIC))
		  || (AGGREGATE_TYPE_P (type) && TYPE_TYPELESS_STORAGE (type));

  वृक्ष ret = build_array_type (type, domain, typeless);

  यदि (शीर्ष_array_vla_p (ret))
    {
      C_TYPE_VARIABLE_SIZE (ret) = 1;
      C_TYPE_VARIABLY_MODIFIED (ret) = 1;
    }

  प्रत्यागम c_set_type_bits (ret, type);
}

/* Build an array type of unspecified size.  */
वृक्ष
c_build_array_type_unspecified (वृक्ष type)
{
  वृक्ष upper = build2 (COMPOUND_व्यंजक, वृक्ष_TYPE (size_zero_गाँठ),
		       integer_zero_गाँठ, size_zero_गाँठ);
  प्रत्यागम c_build_array_type (type, build_index_type (upper));
}

/* Build an array type of zero size.  */
वृक्ष
c_build_array_type_zero_size (वृक्ष type)
{
  /* The GCC extension for zero-length arrays differs from
     ISO flexible array members in that sizeof yields
     zero.  */
  type = c_build_array_type (type, build_index_type (NULL_वृक्ष));
  type = build_distinct_type_copy (TYPE_MAIN_VARIANT (type));
  TYPE_SIZE (type) = bitsize_zero_गाँठ;
  TYPE_SIZE_UNIT (type) = size_zero_गाँठ;
  SET_TYPE_STRUCTURAL_EQUALITY (type);
  प्रत्यागम type;
}

वृक्ष
c_build_type_attribute_qual_variant (वृक्ष type, वृक्ष attrs, पूर्णाङ्क quals)
{
  वृक्ष ret = build_type_attribute_qual_variant (type, attrs, quals);
  प्रत्यागम c_set_type_bits (ret, type);
}

वृक्ष
c_build_type_attribute_variant (वृक्ष type, वृक्ष attrs)
{
  प्रत्यागम c_build_type_attribute_qual_variant (type, attrs, TYPE_QUALS (type));
}

/* Reconstruct a complex derived type.  This is used to re-construct types
   with the vector attribute.  It is called via a langhook.  */

वृक्ष
c_reconstruct_complex_type (वृक्ष type, वृक्ष bottom)
{
  वृक्ष inner, outer;

  यदि (वृक्ष_CODE (type) == POINTER_TYPE)
    {
      inner = c_reconstruct_complex_type (वृक्ष_TYPE (type), bottom);
      outer = c_build_pointer_type_for_mode (inner, TYPE_MODE (type),
					     TYPE_REF_CAN_ALIAS_ALL (type));
    }
  अन्यथा यदि (वृक्ष_CODE (type) == ARRAY_TYPE)
    {
      तार्किक rso = TYPE_REVERSE_STORAGE_ORDER (type);
      inner = c_reconstruct_complex_type (वृक्ष_TYPE (type), bottom);
      outer = c_build_array_type (inner, TYPE_DOMAIN (type));
      यदि (rso)
	{
	  outer = build_distinct_type_copy (outer);
	  TYPE_REVERSE_STORAGE_ORDER (outer) = 1;
	}

      gcc_checking_assert (C_TYPE_VARIABLE_SIZE (type)
			   == C_TYPE_VARIABLE_SIZE (outer));
    }
  अन्यथा यदि (वृक्ष_CODE (type) == FUNCTION_TYPE)
    {
      inner = c_reconstruct_complex_type (वृक्ष_TYPE (type), bottom);
      outer = c_build_function_type (inner, TYPE_ARG_TYPES (type),
				     TYPE_NO_NAMED_ARGS_STDARG_P (type));
    }
  अन्यथा यदि (वृक्ष_CODE (type) == REFERENCE_TYPE
	   || वृक्ष_CODE (type) == OFFSET_TYPE)
    gcc_unreachable ();
  अन्यथा
    प्रत्यागम bottom;

  प्रत्यागम c_build_type_attribute_qual_variant (outer, TYPE_ATTRIBUTES (type),
					      TYPE_QUALS (type));
}


/* Helper function for c_canonical_type.  Check whether FIELD
   contains a pointer to a structure or union with tag,
   possibly nested in other type derivations, and return the
   type of this nested structure or union.  */
स्थिर वृक्ष
ptr_to_tagged_member (वृक्ष field)
{
  gcc_assert (FIELD_DECL == वृक्ष_CODE (field));
  वृक्ष type = वृक्ष_TYPE (field);
  तार्किक ptr_seen = असत्य;
  यावत् (वृक्ष_CODE (type) == ARRAY_TYPE
	 || वृक्ष_CODE (type) == FUNCTION_TYPE
	 || वृक्ष_CODE (type) == POINTER_TYPE)
    {
      यदि (वृक्ष_CODE (type) == POINTER_TYPE)
	ptr_seen = सत्य;
      type = वृक्ष_TYPE (type);
    }

  यदि (ptr_seen
      && RECORD_OR_UNION_TYPE_P (type)
      && NULL_वृक्ष != c_type_tag (type))
    प्रत्यागम type;

  प्रत्यागम NULL_वृक्ष;
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
वृक्ष
c_type_canonical (वृक्ष type)
{
  gcc_assert (RECORD_OR_UNION_TYPE_P (type));

  तार्किक needs_mod = असत्य;
  प्रति (वृक्ष x = TYPE_FIELDS (type); x; x = DECL_CHAIN (x))
    {
      यदि (!ptr_to_tagged_member (x))
	अनुवर्त;
      needs_mod = सत्य;
      भङ्ग;
    }
  यदि (!needs_mod)
    प्रत्यागम type;

  /* Construct new version with such members replaced.  */
  वृक्ष n = build_distinct_type_copy (type);
  वृक्ष *fields = &TYPE_FIELDS (n);
  प्रति (वृक्ष x = TYPE_FIELDS (type); x; x = DECL_CHAIN (x))
    {
      वृक्ष f = copy_गाँठ (x);
      यदि (वृक्ष m = ptr_to_tagged_member (x))
	{
	  वृक्ष new_गाँठ = make_गाँठ (वृक्ष_CODE (m));
	  TYPE_NAME (new_गाँठ) = TYPE_NAME (m);
	  SET_TYPE_STRUCTURAL_EQUALITY (new_गाँठ);
	  new_गाँठ = qualify_type (new_गाँठ, m);
	  वृक्ष_TYPE (f) = c_reconstruct_complex_type (वृक्ष_TYPE (x),
						      new_गाँठ);
	}
      *fields = f;
      fields = &DECL_CHAIN (f);
    }
  TYPE_CANONICAL (n) = n;
  प्रत्यागम n;
}


/* If NTYPE is a type of a non-variadic function with a prototype
   and OTYPE is a type of a function without a prototype and ATTRS
   contains attribute format, diagnosess and removes it from ATTRS.
   Returns the result of build_type_attribute_variant of NTYPE and
   the (possibly) modified ATTRS.  */

स्थिर वृक्ष
c_build_functype_attribute_variant (वृक्ष ntype, वृक्ष otype, वृक्ष attrs)
{
  यदि (!prototype_p (otype)
      && prototype_p (ntype)
      && lookup_attribute ("format", attrs))
    {
      warning_at (निवेश_location, OPT_Wattributes,
		  "%qs attribute can only be applied to variadic functions",
		  "format");
      attrs = remove_attribute ("format", attrs);
    }
  प्रत्यागम c_build_type_attribute_variant (ntype, attrs);

}

/* Given a type which could be a typedef name, make sure to return the
   original type.  See set_underlying_type. */
स्थिर const_वृक्ष
c_type_original (const_वृक्ष t)
{
  /* It may even be a typedef of a typedef...
     In the case of compiler-created builtin structs the TYPE_DECL
     may be a dummy, with no DECL_ORIGINAL_TYPE.  Don't fault.  */
  यावत् (TYPE_NAME (t)
	 && वृक्ष_CODE (TYPE_NAME (t)) == TYPE_DECL
	 && DECL_ORIGINAL_TYPE (TYPE_NAME (t)))
    t = DECL_ORIGINAL_TYPE (TYPE_NAME (t));
  प्रत्यागम t;
}

/* Return the tag for a tagged type.  */
वृक्ष
c_type_tag (const_वृक्ष t)
{
  gcc_assert (RECORD_OR_UNION_TYPE_P (t) || वृक्ष_CODE (t) == ENUMERAL_TYPE);
  const_वृक्ष orig = c_type_original (t);
  वृक्ष name = TYPE_NAME (orig);
  यदि (!name)
    प्रत्यागम NULL_वृक्ष;
  यदि (वृक्ष_CODE (name) == TYPE_DECL)
    {
      यदि (!DECL_NAME (name))
	प्रत्यागम NULL_वृक्ष;
      name = DECL_NAME (name);
    }
  gcc_checking_assert (वृक्ष_CODE (name) == IDENTIFIER_गाँठ);
  प्रत्यागम name;
}

/* Remove qualifiers but not atomic.  For arrays remove qualifiers
   on the element type but also do not remove atomic.  */
स्थिर वृक्ष
remove_qualifiers (वृक्ष t)
{
  यदि (!t || t == error_mark_गाँठ)
    प्रत्यागम t;
  प्रत्यागम TYPE_ATOMIC (strip_array_types (t))
	 ? c_build_qualified_type (TYPE_MAIN_VARIANT (t), TYPE_QUAL_ATOMIC)
	 : TYPE_MAIN_VARIANT (t);
}


/* Helper function for composite_type_internal.  Find a compatible type
   in a (transparent) union U compatible to T.  If found, return the
   type of the corresponding member.  Otherwise, return the union type U.  */
स्थिर वृक्ष
transparent_union_replacement (वृक्ष u, वृक्ष t)
{
  यदि (u == error_mark_गाँठ || t == error_mark_गाँठ
      || वृक्ष_CODE (u) != UNION_TYPE
      || !(TYPE_TRANSPARENT_AGGR (u) || TYPE_NAME (u) == NULL_वृक्ष)
      || comptypes (u, t))
    प्रत्यागम u;

  प्रति (वृक्ष memb = TYPE_FIELDS (u); memb; memb = DECL_CHAIN (memb))
    {
      वृक्ष m = remove_qualifiers (वृक्ष_TYPE (memb));
      यदि (comptypes (m, t))
	{
	  pedwarn (निवेश_location, OPT_Wpedantic,
		    "function types not truly compatible in ISO C");
	  प्रत्यागम m;
	}
    }

  प्रत्यागम u;
}



/* Return the composite type of two compatible types.

   We assume that comptypes has already been done and returned
   nonzero; if that isn't so, this may crash.  In particular, we
   assume that qualifiers match.  */

संरचना composite_cache {
  वृक्ष t1;
  वृक्ष t2;
  वृक्ष composite;
  संरचना composite_cache* next;
};

वृक्ष
composite_type_internal (वृक्ष t1, वृक्ष t2, वृक्ष cond,
			 संरचना composite_cache* cache)
{
  गणना वृक्ष_code code1;
  गणना वृक्ष_code code2;
  वृक्ष attributes;

  /* Save time if the two types are the same.  */

  यदि (t1 == t2) प्रत्यागम t1;

  /* If one type is nonsense, use the other.  */
  यदि (t1 == error_mark_गाँठ)
    प्रत्यागम t2;
  यदि (t2 == error_mark_गाँठ)
    प्रत्यागम t1;

  code1 = वृक्ष_CODE (t1);
  code2 = वृक्ष_CODE (t2);

  /* Merge the attributes.  */
  attributes = targetm.merge_type_attributes (t1, t2);

  /* If one is an enumerated type and the other is the compatible
     integer type, the composite type might be either of the two
     (DR#013 question 3).  For consistency, use the enumerated type as
     the composite type.  */

  यदि (code1 == ENUMERAL_TYPE
      && (code2 == INTEGER_TYPE
	  || code2 == BOOLEAN_TYPE))
    प्रत्यागम t1;
  यदि (code2 == ENUMERAL_TYPE
      && (code1 == INTEGER_TYPE
	  || code1 == BOOLEAN_TYPE))
    प्रत्यागम t2;

  gcc_assert (code1 == code2);

  विकल्प (code1)
    {
    पक्ष POINTER_TYPE:
      /* For two pointers, do this recursively on the target type.  */
      {
	gcc_checking_assert (TYPE_QUALS (t1) == TYPE_QUALS (t2));
	वृक्ष target = composite_type_internal (वृक्ष_TYPE (t1), वृक्ष_TYPE (t2),
					       cond, cache);
	वृक्ष n = c_build_pointer_type_for_mode (target, TYPE_MODE (t1), असत्य);
	प्रत्यागम c_build_type_attribute_qual_variant (n, attributes,
						    TYPE_QUALS (t2));
      }

    पक्ष ARRAY_TYPE:
      {
	वृक्ष d1 = TYPE_DOMAIN (t1);
	वृक्ष d2 = TYPE_DOMAIN (t2);

	/* We should not have any type quals on arrays at all.  */
	gcc_assert (!TYPE_QUALS_NO_ADDR_SPACE (t1)
		    && !TYPE_QUALS_NO_ADDR_SPACE (t2));

	तार्किक d1_zero = zero_length_array_type_p (t1)
		       || flexible_array_member_type_p (t1);
	तार्किक d2_zero = zero_length_array_type_p (t2)
		       || flexible_array_member_type_p (t2);

	तार्किक d1_variable = शीर्ष_array_vla_p (t1);
	तार्किक d2_variable = शीर्ष_array_vla_p (t2);

	तार्किक use1 = d1 && (d2_variable || !d2 || d2_zero || !d1_variable);
	तार्किक use2 = d2 && (d1_variable || !d1 || d1_zero || !d2_variable);

	/* If the first is an unspecified size pick the other one.  */
	यदि (d2_variable && c_type_unspecified_p (t1))
	  {
	    gcc_assert (use1 && use2);
	    use1 = असत्य;
	  }

	/* If both are VLAs but not unspecified and we are in the
	   conditional operator, we create a conditional to select
	   the size of the active branch.  */
	तार्किक use0 = cond && d1_variable && !c_type_unspecified_p (t1)
			 && d2_variable && !c_type_unspecified_p (t2);

	वृक्ष td;
	वृक्ष elt = composite_type_internal (वृक्ष_TYPE (t1), वृक्ष_TYPE (t2),
					    cond, cache);

	यदि (!use0)
	  {
	    /* Save space: see if the result is identical to one of the args.  */
	    यदि (elt == वृक्ष_TYPE (t1) && use1)
	      प्रत्यागम c_build_type_attribute_variant (t1, attributes);
	    यदि (elt == वृक्ष_TYPE (t2) && use2)
	      प्रत्यागम c_build_type_attribute_variant (t2, attributes);

	    यदि (elt == वृक्ष_TYPE (t1) && !TYPE_DOMAIN (t2) && !TYPE_DOMAIN (t1))
	      प्रत्यागम c_build_type_attribute_variant (t1, attributes);
	    यदि (elt == वृक्ष_TYPE (t2) && !TYPE_DOMAIN (t2) && !TYPE_DOMAIN (t1))
	      प्रत्यागम c_build_type_attribute_variant (t2, attributes);

	    td = TYPE_DOMAIN (use1 ? t1 : t2);
	  }
	अन्यथा
	  {
	    /* Not used in C.  */
	    gcc_assert (size_zero_गाँठ == TYPE_MIN_मूल्य (d1));
	    gcc_assert (size_zero_गाँठ == TYPE_MIN_मूल्य (d2));

	    वृक्ष d = fold_build3_loc (UNKNOWN_LOCATION, COND_व्यंजक, sizetype,
				      cond, TYPE_MAX_मूल्य (d1),
				      TYPE_MAX_मूल्य (d2));

	    td = build_index_type (d);
	  }

	/* Merge the element types, and have a size if either arg has
	   one.  We may have qualifiers on the element types.  To set
	   up TYPE_MAIN_VARIANT correctly, we need to form the
	   composite of the unqualified types and add the qualifiers
	   back at the end.  */
	पूर्णाङ्क quals = TYPE_QUALS (strip_array_types (elt));
	वृक्ष unqual_elt = c_build_qualified_type (elt, TYPE_UNQUALIFIED);

	यदि ((!d1 || d1_zero) && (!d2 || d2_zero) && (d1 || d2))
	  t1 = c_build_array_type_zero_size (unqual_elt);
	अन्यथा
	  t1 = c_build_array_type (unqual_elt, td);

	/* Check that a type which has a varying outermost dimension
	   got marked as having a variable size.  */
	तार्किक varsize = (d1_variable && d2_variable)
		       || (d1_variable && !d2)
		       || (d2_variable && !d1);
	gcc_checking_assert (!varsize || C_TYPE_VARIABLE_SIZE (t1));

	t1 = c_build_qualified_type (t1, quals);
	प्रत्यागम c_build_type_attribute_variant (t1, attributes);
      }

    पक्ष RECORD_TYPE:
    पक्ष UNION_TYPE:
      यदि (flag_isoc23 && !comptypes_same_p (t1, t2))
	{
	  /* Go to the original type to get the right tag.  */
	  वृक्ष tag = c_type_tag (t1);

	  gcc_checking_assert (COMPLETE_TYPE_P (t1) && COMPLETE_TYPE_P (t2));
	  gcc_checking_assert (!tag || comptypes (t1, t2));

	  /* If a composite type for these two types is already under
	     construction, return it.  */

	  प्रति (संरचना composite_cache *c = cache; c != रिक्त; c = c->next)
	    यदि ((c->t1 == t1 && c->t2 == t2) || (c->t1 == t2 && c->t2 == t1))
	       प्रत्यागम c->composite;

	  /* Otherwise, create a new type node and link it into the cache.  */

	  वृक्ष n = make_गाँठ (code1);
	  SET_TYPE_STRUCTURAL_EQUALITY (n);
	  TYPE_NAME (n) = tag;

	  संरचना composite_cache cache2 = { t1, t2, n, cache };
	  cache = &cache2;

	  वृक्ष f1 = TYPE_FIELDS (t1);
	  वृक्ष f2 = TYPE_FIELDS (t2);
	  वृक्ष fields = NULL_वृक्ष;

	  प्रति (वृक्ष a = f1, b = f2; a && b;
	       a = DECL_CHAIN (a), b = DECL_CHAIN (b))
	    {
	      वृक्ष ta = वृक्ष_TYPE (a);
	      वृक्ष tb = वृक्ष_TYPE (b);

	      यदि (DECL_C_BIT_FIELD (a))
		{
		  ta = DECL_BIT_FIELD_TYPE (a);
		  tb = DECL_BIT_FIELD_TYPE (b);
		}

	      gcc_assert (DECL_NAME (a) == DECL_NAME (b));
	      gcc_checking_assert (!DECL_NAME (a) || comptypes (ta, tb));

	      वृक्ष t = composite_type_internal (ta, tb, cond, cache);
	      वृक्ष f = build_decl (निवेश_location, FIELD_DECL, DECL_NAME (a), t);

	      DECL_PACKED (f) = DECL_PACKED (a);
	      SET_DECL_ALIGN (f, DECL_ALIGN (a));
	      DECL_ATTRIBUTES (f) = DECL_ATTRIBUTES (a);
	      C_DECL_VARIABLE_SIZE (f) = C_TYPE_VARIABLE_SIZE (t);

	      decl_attributes (&f, DECL_ATTRIBUTES (f), 0);

	      finish_decl (f, निवेश_location, रिक्त, रिक्त, रिक्त);

	      यदि (DECL_C_BIT_FIELD (a))
		{
		  /* This will be processed by finish_struct.  */
		  SET_DECL_C_BIT_FIELD (f);
		  DECL_INITIAL (f) = build_int_cst (integer_type_गाँठ,
						    वृक्ष_to_uhwi (DECL_SIZE (a)));
		  DECL_NONADDRESSABLE_P (f) = सत्य;
		  DECL_PADDING_P (f) = !DECL_NAME (a);
		}

	      DECL_CHAIN (f) = fields;
	      fields = f;
	    }

	  fields = nreverse (fields);

	  /* Setup the struct/union type.  Because we inherit all variably
	     modified components, we can ignore the size expression.  */
	  वृक्ष व्यंजक = NULL_वृक्ष;

	  /* Set TYPE_STUB_DECL for debugging symbols.  */
	  TYPE_STUB_DECL (n) = pushdecl (build_decl (निवेश_location, TYPE_DECL,
						     NULL_वृक्ष, n));

	  n = finish_struct (निवेश_location, n, fields, attributes, रिक्त,
			     &व्यंजक);

	  प्रत्यागम qualify_type (n, t1);
	}
      /* FALLTHRU */
    पक्ष ENUMERAL_TYPE:
      यदि (attributes != रिक्त)
	{
	  /* Try harder not to create a new aggregate type.  */
	  यदि (attribute_list_equal (TYPE_ATTRIBUTES (t1), attributes))
	    प्रत्यागम t1;
	  यदि (attribute_list_equal (TYPE_ATTRIBUTES (t2), attributes))
	    प्रत्यागम t2;
	}
      प्रत्यागम c_build_type_attribute_variant (t1, attributes);

    पक्ष FUNCTION_TYPE:
      /* Function types: prefer the one that specified arg types.
	 If both do, merge the arg types.  Also merge the return types.  */
      {
	वृक्ष valtype = composite_type_internal (वृक्ष_TYPE (t1), वृक्ष_TYPE (t2),
						cond, cache);
	वृक्ष p1 = TYPE_ARG_TYPES (t1);
	वृक्ष p2 = TYPE_ARG_TYPES (t2);

	/* Save space: see if the result is identical to one of the args.  */
	यदि (valtype == वृक्ष_TYPE (t1) && !TYPE_ARG_TYPES (t2))
	  प्रत्यागम c_build_functype_attribute_variant (t1, t2, attributes);
	यदि (valtype == वृक्ष_TYPE (t2) && !TYPE_ARG_TYPES (t1))
	  प्रत्यागम c_build_functype_attribute_variant (t2, t1, attributes);

	/* Simple way if one arg fails to specify argument types.  */
	यदि (TYPE_ARG_TYPES (t1) == NULL_वृक्ष)
	  {
	    t1 = c_build_function_type (valtype, TYPE_ARG_TYPES (t2),
					TYPE_NO_NAMED_ARGS_STDARG_P (t2));
	    t1 = c_build_type_attribute_variant (t1, attributes);
	    प्रत्यागम qualify_type (t1, t2);
	 }
	यदि (TYPE_ARG_TYPES (t2) == NULL_वृक्ष)
	  {
	    t1 = c_build_function_type (valtype, TYPE_ARG_TYPES (t1),
					TYPE_NO_NAMED_ARGS_STDARG_P (t1));
	    t1 = c_build_type_attribute_variant (t1, attributes);
	    प्रत्यागम qualify_type (t1, t2);
	  }

	/* If both args specify argument types, we must merge the two
	   lists, argument by argument.  */
	वृक्ष newargs = NULL_वृक्ष;
	वृक्ष *endp = &newargs;

	प्रति (; p1; p1 = वृक्ष_CHAIN (p1), p2 = वृक्ष_CHAIN (p2))
	  {
	    यदि (p1 == void_list_गाँठ)
	      {
		*endp = void_list_गाँठ;
		भङ्ग;
	      }
	    वृक्ष mv1 = remove_qualifiers (वृक्ष_मूल्य (p1));
	    वृक्ष mv2 = remove_qualifiers (वृक्ष_मूल्य (p2));

	    gcc_assert (mv1);
	    gcc_assert (mv2);

	    mv1 = transparent_union_replacement (mv1, mv2);
	    mv2 = transparent_union_replacement (mv2, mv1);

	    *endp = वृक्ष_cons (NULL_वृक्ष,
			       composite_type_internal (mv1, mv2, cond, cache),
			       NULL_वृक्ष);

	    endp = &वृक्ष_CHAIN (*endp);
	  }

	t1 = c_build_function_type (valtype, newargs);
	t1 = qualify_type (t1, t2);
      }
      /* FALLTHRU */

    स्वभाव:
      प्रत्यागम c_build_type_attribute_variant (t1, attributes);
    }
}

वृक्ष
composite_type_cond (वृक्ष t1, वृक्ष t2, वृक्ष cond)
{
  gcc_checking_assert (comptypes_check_for_composite (t1, t2));

  संरचना composite_cache cache = { };
  वृक्ष n = composite_type_internal (t1, t2, cond, &cache);

  gcc_checking_assert (comptypes_check_for_composite (n, t1));
  gcc_checking_assert (comptypes_check_for_composite (n, t2));
  प्रत्यागम n;
}


वृक्ष
composite_type (वृक्ष t1, वृक्ष t2)
{
  प्रत्यागम composite_type_cond (t1, t2, NULL_वृक्ष);
}

/* Return the type of a conditional expression between pointers to
   possibly differently qualified versions of compatible types.

   We assume that comp_target_types has already been done and returned
   true; if that isn't so, this may crash.  */

स्थिर वृक्ष
common_pointer_type (वृक्ष t1, वृक्ष t2, वृक्ष cond)
{
  वृक्ष attributes;
  अचिन्हित target_quals;
  addr_space_t as1, as2, as_common;
  पूर्णाङ्क quals1, quals2;

  /* Save time if the two types are the same.  */

  यदि (t1 == t2) प्रत्यागम t1;

  /* If one type is nonsense, use the other.  */
  यदि (t1 == error_mark_गाँठ)
    प्रत्यागम t2;
  यदि (t2 == error_mark_गाँठ)
    प्रत्यागम t1;

  gcc_assert (वृक्ष_CODE (t1) == POINTER_TYPE
	      && वृक्ष_CODE (t2) == POINTER_TYPE);

  /* Merge the attributes.  */
  attributes = targetm.merge_type_attributes (t1, t2);

  /* Find the composite type of the target types, and combine the
     qualifiers of the two types' targets.  */
  वृक्ष pointed_to_1 = वृक्ष_TYPE (t1);
  वृक्ष pointed_to_2 = वृक्ष_TYPE (t2);
  वृक्ष target = composite_type_cond (TYPE_MAIN_VARIANT (pointed_to_1),
				     TYPE_MAIN_VARIANT (pointed_to_2), cond);

  /* Strip array types to get correct qualifier for pointers to arrays */
  quals1 = TYPE_QUALS_NO_ADDR_SPACE (strip_array_types (pointed_to_1));
  quals2 = TYPE_QUALS_NO_ADDR_SPACE (strip_array_types (pointed_to_2));

  /* For function types do not merge const qualifiers, but drop them
     if used inconsistently.  The middle-end uses these to mark const
     and noreturn functions.  */
  यदि (वृक्ष_CODE (pointed_to_1) == FUNCTION_TYPE)
    target_quals = (quals1 & quals2);
  अन्यथा
    target_quals = (quals1 | quals2);

  /* If the two named address spaces are different, determine the common
     superset address space.  This is guaranteed to exist due to the
     assumption that comp_target_type returned true.  */
  as1 = TYPE_ADDR_SPACE (pointed_to_1);
  as2 = TYPE_ADDR_SPACE (pointed_to_2);
  यदि (!addr_space_superset (as1, as2, &as_common))
    gcc_unreachable ();

  target_quals |= ENCODE_QUAL_ADDR_SPACE (as_common);

  t1 = c_build_pointer_type (c_build_qualified_type (target, target_quals));
  प्रत्यागम c_build_type_attribute_variant (t1, attributes);
}

/* Return the common type for two arithmetic types under the usual
   arithmetic conversions.  The default conversions have already been
   applied, and enumerated types converted to their compatible integer
   types.  The resulting type is unqualified and has no attributes.

   This is the type for the result of most arithmetic operations
   if the operands have the given two types.  */

स्थिर वृक्ष
c_common_type (वृक्ष t1, वृक्ष t2)
{
  गणना वृक्ष_code code1;
  गणना वृक्ष_code code2;

  /* If one type is nonsense, use the other.  */
  यदि (t1 == error_mark_गाँठ)
    प्रत्यागम t2;
  यदि (t2 == error_mark_गाँठ)
    प्रत्यागम t1;

  यदि (TYPE_QUALS (t1) != TYPE_UNQUALIFIED)
    t1 = TYPE_MAIN_VARIANT (t1);

  यदि (TYPE_QUALS (t2) != TYPE_UNQUALIFIED)
    t2 = TYPE_MAIN_VARIANT (t2);

  यदि (TYPE_ATTRIBUTES (t1) != NULL_वृक्ष)
    {
      वृक्ष attrs = affects_type_identity_attributes (TYPE_ATTRIBUTES (t1));
      t1 = c_build_type_attribute_variant (t1, attrs);
    }

  यदि (TYPE_ATTRIBUTES (t2) != NULL_वृक्ष)
    {
      वृक्ष attrs = affects_type_identity_attributes (TYPE_ATTRIBUTES (t2));
      t2 = c_build_type_attribute_variant (t2, attrs);
    }

  /* Save time if the two types are the same.  */

  यदि (t1 == t2) प्रत्यागम t1;

  code1 = वृक्ष_CODE (t1);
  code2 = वृक्ष_CODE (t2);

  gcc_assert (code1 == VECTOR_TYPE || code1 == COMPLEX_TYPE
	      || code1 == FIXED_POINT_TYPE || code1 == REAL_TYPE
	      || code1 == INTEGER_TYPE || code1 == BITINT_TYPE);
  gcc_assert (code2 == VECTOR_TYPE || code2 == COMPLEX_TYPE
	      || code2 == FIXED_POINT_TYPE || code2 == REAL_TYPE
	      || code2 == INTEGER_TYPE || code2 == BITINT_TYPE);

  /* When one operand is a decimal float type, the other operand cannot be
     a generic float type or a complex type.  We also disallow vector types
     here.  */
  यदि ((DECIMAL_FLOAT_TYPE_P (t1) || DECIMAL_FLOAT_TYPE_P (t2))
      && !(DECIMAL_FLOAT_TYPE_P (t1) && DECIMAL_FLOAT_TYPE_P (t2)))
    {
      यदि (code1 == VECTOR_TYPE || code2 == VECTOR_TYPE)
	{
	  error ("cannot mix operands of decimal floating and vector types");
	  प्रत्यागम error_mark_गाँठ;
	}
      यदि (code1 == COMPLEX_TYPE || code2 == COMPLEX_TYPE)
	{
	  error ("cannot mix operands of decimal floating and complex types");
	  प्रत्यागम error_mark_गाँठ;
	}
      यदि (code1 == REAL_TYPE && code2 == REAL_TYPE)
	{
	  error ("cannot mix operands of decimal floating "
		 "and other floating types");
	  प्रत्यागम error_mark_गाँठ;
	}
    }

  /* If one type is a vector type, return that type.  (How the usual
     arithmetic conversions apply to the vector types extension is not
     precisely specified.)  */
  यदि (code1 == VECTOR_TYPE)
    प्रत्यागम t1;

  यदि (code2 == VECTOR_TYPE)
    प्रत्यागम t2;

  /* If one type is complex, form the common type of the non-complex
     components, then make that complex.  Use T1 or T2 if it is the
     required type.  */
  यदि (code1 == COMPLEX_TYPE || code2 == COMPLEX_TYPE)
    {
      वृक्ष subtype1 = code1 == COMPLEX_TYPE ? वृक्ष_TYPE (t1) : t1;
      वृक्ष subtype2 = code2 == COMPLEX_TYPE ? वृक्ष_TYPE (t2) : t2;
      वृक्ष subtype = c_common_type (subtype1, subtype2);

      यदि (code1 == COMPLEX_TYPE && वृक्ष_TYPE (t1) == subtype)
	प्रत्यागम t1;
      अन्यथा यदि (code2 == COMPLEX_TYPE && वृक्ष_TYPE (t2) == subtype)
	प्रत्यागम t2;
      अन्यथा यदि (वृक्ष_CODE (subtype) == BITINT_TYPE)
	{
	  sorry ("%<_Complex _BitInt(%d)%> unsupported",
		 TYPE_PRECISION (subtype));
	  प्रत्यागम code1 == COMPLEX_TYPE ? t1 : t2;
	}
      अन्यथा
	प्रत्यागम build_complex_type (subtype);
    }

  /* If only one is real, use it as the result.  */

  यदि (code1 == REAL_TYPE && code2 != REAL_TYPE)
    प्रत्यागम t1;

  यदि (code2 == REAL_TYPE && code1 != REAL_TYPE)
    प्रत्यागम t2;

  /* If both are real and either are decimal floating point types, use
     the decimal floating point type with the greater precision. */

  यदि (code1 == REAL_TYPE && code2 == REAL_TYPE)
    {
      यदि (TYPE_MAIN_VARIANT (t1) == dfloat128_type_गाँठ
	  || TYPE_MAIN_VARIANT (t2) == dfloat128_type_गाँठ)
	प्रत्यागम dfloat128_type_गाँठ;
      /* And prefer _Decimal128 over _Decimal64x which has in GCC's
	 implementation the same mode.  */
      अन्यथा यदि (TYPE_MAIN_VARIANT (t1) == dfloat64x_type_गाँठ
	       || TYPE_MAIN_VARIANT (t2) == dfloat64x_type_गाँठ)
	प्रत्यागम dfloat64x_type_गाँठ;
      अन्यथा यदि (TYPE_MAIN_VARIANT (t1) == dfloat64_type_गाँठ
	       || TYPE_MAIN_VARIANT (t2) == dfloat64_type_गाँठ)
	प्रत्यागम dfloat64_type_गाँठ;
      अन्यथा यदि (TYPE_MAIN_VARIANT (t1) == dfloat32_type_गाँठ
	       || TYPE_MAIN_VARIANT (t2) == dfloat32_type_गाँठ)
	प्रत्यागम dfloat32_type_गाँठ;
    }

  /* Deal with fixed-point types.  */
  यदि (code1 == FIXED_POINT_TYPE || code2 == FIXED_POINT_TYPE)
    {
      अचिन्हित पूर्णाङ्क unsignedp = 0, satp = 0;
      scalar_mode m1, m2;
      अचिन्हित पूर्णाङ्क fbit1, ibit1, fbit2, ibit2, max_fbit, max_ibit;

      m1 = SCALAR_TYPE_MODE (t1);
      m2 = SCALAR_TYPE_MODE (t2);

      /* If one input type is saturating, the result type is saturating.  */
      यदि (TYPE_SATURATING (t1) || TYPE_SATURATING (t2))
	satp = 1;

      /* If both fixed-point types are unsigned, the result type is unsigned.
	 When mixing fixed-point and integer types, follow the sign of the
	 fixed-point type.
	 Otherwise, the result type is signed.  */
      यदि ((TYPE_UNSIGNED (t1) && TYPE_UNSIGNED (t2)
	   && code1 == FIXED_POINT_TYPE && code2 == FIXED_POINT_TYPE)
	  || (code1 == FIXED_POINT_TYPE && code2 != FIXED_POINT_TYPE
	      && TYPE_UNSIGNED (t1))
	  || (code1 != FIXED_POINT_TYPE && code2 == FIXED_POINT_TYPE
	      && TYPE_UNSIGNED (t2)))
	unsignedp = 1;

      /* The result type is signed.  */
      यदि (unsignedp == 0)
	{
	  /* If the input type is unsigned, we need to convert to the
	     signed type.  */
	  यदि (code1 == FIXED_POINT_TYPE && TYPE_UNSIGNED (t1))
	    {
	      गणना mode_class mclass = (गणना mode_class) 0;
	      यदि (GET_MODE_CLASS (m1) == MODE_UFRACT)
		mclass = MODE_FRACT;
	      अन्यथा यदि (GET_MODE_CLASS (m1) == MODE_UACCUM)
		mclass = MODE_ACCUM;
	      अन्यथा
		gcc_unreachable ();
	      m1 = as_a <scalar_mode>
		(mode_for_size (GET_MODE_PRECISION (m1), mclass, 0));
	    }
	  यदि (code2 == FIXED_POINT_TYPE && TYPE_UNSIGNED (t2))
	    {
	      गणना mode_class mclass = (गणना mode_class) 0;
	      यदि (GET_MODE_CLASS (m2) == MODE_UFRACT)
		mclass = MODE_FRACT;
	      अन्यथा यदि (GET_MODE_CLASS (m2) == MODE_UACCUM)
		mclass = MODE_ACCUM;
	      अन्यथा
		gcc_unreachable ();
	      m2 = as_a <scalar_mode>
		(mode_for_size (GET_MODE_PRECISION (m2), mclass, 0));
	    }
	}

      यदि (code1 == FIXED_POINT_TYPE)
	{
	  fbit1 = GET_MODE_FBIT (m1);
	  ibit1 = GET_MODE_IBIT (m1);
	}
      अन्यथा
	{
	  fbit1 = 0;
	  /* Signed integers need to subtract one sign bit.  */
	  ibit1 = TYPE_PRECISION (t1) - (!TYPE_UNSIGNED (t1));
	}

      यदि (code2 == FIXED_POINT_TYPE)
	{
	  fbit2 = GET_MODE_FBIT (m2);
	  ibit2 = GET_MODE_IBIT (m2);
	}
      अन्यथा
	{
	  fbit2 = 0;
	  /* Signed integers need to subtract one sign bit.  */
	  ibit2 = TYPE_PRECISION (t2) - (!TYPE_UNSIGNED (t2));
	}

      max_ibit = ibit1 >= ibit2 ?  ibit1 : ibit2;
      max_fbit = fbit1 >= fbit2 ?  fbit1 : fbit2;
      प्रत्यागम c_common_fixed_point_type_for_size (max_ibit, max_fbit, unsignedp,
						 satp);
    }

  /* Both real or both integers; use the one with greater precision.  */

  यदि (TYPE_PRECISION (t1) > TYPE_PRECISION (t2))
    प्रत्यागम t1;
  अन्यथा यदि (TYPE_PRECISION (t2) > TYPE_PRECISION (t1))
    प्रत्यागम t2;

  /* Same precision.  Prefer long longs to longs to ints when the
     same precision, following the C99 rules on integer type rank
     (which are equivalent to the C90 rules for C90 types).  */

  यदि (TYPE_MAIN_VARIANT (t1) == long_long_unsigned_type_गाँठ
      || TYPE_MAIN_VARIANT (t2) == long_long_unsigned_type_गाँठ)
    प्रत्यागम long_long_unsigned_type_गाँठ;

  यदि (TYPE_MAIN_VARIANT (t1) == long_long_integer_type_गाँठ
      || TYPE_MAIN_VARIANT (t2) == long_long_integer_type_गाँठ)
    {
      यदि (TYPE_UNSIGNED (t1) || TYPE_UNSIGNED (t2))
	प्रत्यागम long_long_unsigned_type_गाँठ;
      अन्यथा
	प्रत्यागम long_long_integer_type_गाँठ;
    }

  यदि (TYPE_MAIN_VARIANT (t1) == long_unsigned_type_गाँठ
      || TYPE_MAIN_VARIANT (t2) == long_unsigned_type_गाँठ)
    प्रत्यागम long_unsigned_type_गाँठ;

  यदि (TYPE_MAIN_VARIANT (t1) == long_integer_type_गाँठ
      || TYPE_MAIN_VARIANT (t2) == long_integer_type_गाँठ)
    {
      /* But preserve unsignedness from the other type,
	 since long cannot hold all the values of an unsigned int.  */
      यदि (TYPE_UNSIGNED (t1) || TYPE_UNSIGNED (t2))
	प्रत्यागम long_unsigned_type_गाँठ;
      अन्यथा
	प्रत्यागम long_integer_type_गाँठ;
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
  वृक्ष mv1 = TYPE_MAIN_VARIANT (t1);
  वृक्ष mv2 = TYPE_MAIN_VARIANT (t2);

  प्रति (पूर्णाङ्क i = अंक_FLOATN_TYPES - 1; i >= 0; i--)
    यदि (mv1 == FLOATN_TYPE_गाँठ (i) || mv2 == FLOATN_TYPE_गाँठ (i))
      प्रत्यागम FLOATN_TYPE_गाँठ (i);

  /* Likewise, prefer long double to double even if same size.  */
  यदि (mv1 == long_double_type_गाँठ || mv2 == long_double_type_गाँठ)
    प्रत्यागम long_double_type_गाँठ;

  /* Likewise, prefer double to float even if same size.
     We got a couple of embedded targets with 32 bit doubles, and the
     pdp11 might have 64 bit floats.  */
  यदि (mv1 == double_type_गाँठ || mv2 == double_type_गाँठ)
    प्रत्यागम double_type_गाँठ;

  यदि (mv1 == float_type_गाँठ || mv2 == float_type_गाँठ)
    प्रत्यागम float_type_गाँठ;

  प्रति (पूर्णाङ्क i = अंक_FLOATNX_TYPES - 1; i >= 0; i--)
    यदि (mv1 == FLOATNX_TYPE_गाँठ (i) || mv2 == FLOATNX_TYPE_गाँठ (i))
      प्रत्यागम FLOATNX_TYPE_गाँठ (i);

  यदि ((code1 == BITINT_TYPE || code2 == BITINT_TYPE) && code1 != code2)
    {
      /* Prefer any other integral types over bit-precise integer types.  */
      यदि (TYPE_UNSIGNED (t1) == TYPE_UNSIGNED (t2))
	प्रत्यागम code1 == BITINT_TYPE ? t2 : t1;
      /* If BITINT_TYPE is unsigned and the other type is signed
	 non-BITINT_TYPE with the same precision, the latter has higher rank.
	 In that case:
	 Otherwise, both operands are converted to the unsigned integer type
	 corresponding to the type of the operand with signed integer type.  */
      यदि (TYPE_UNSIGNED (code1 == BITINT_TYPE ? t1 : t2))
	प्रत्यागम c_common_unsigned_type (code1 == BITINT_TYPE ? t2 : t1);
    }

  /* Otherwise prefer the unsigned one.  */

  यदि (TYPE_UNSIGNED (t1))
    प्रत्यागम t1;
  अन्यथा
    प्रत्यागम t2;
}

/* Wrapper around c_common_type that is used by c-common.cc and other
   front end optimizations that remove promotions.  ENUMERAL_TYPEs
   are allowed here and are converted to their compatible integer types.
   BOOLEAN_TYPEs are allowed here and return either boolean_type_node or
   preferably a non-Boolean type as the common type.  */
वृक्ष
common_type (वृक्ष t1, वृक्ष t2)
{
  यदि (वृक्ष_CODE (t1) == ENUMERAL_TYPE)
    t1 = ENUM_UNDERLYING_TYPE (t1);
  यदि (वृक्ष_CODE (t2) == ENUMERAL_TYPE)
    t2 = ENUM_UNDERLYING_TYPE (t2);

  /* If both types are BOOLEAN_TYPE, then return boolean_type_node.  */
  यदि (वृक्ष_CODE (t1) == BOOLEAN_TYPE
      && वृक्ष_CODE (t2) == BOOLEAN_TYPE)
    प्रत्यागम boolean_type_गाँठ;

  /* If either type is BOOLEAN_TYPE, then return the other.  */
  यदि (वृक्ष_CODE (t1) == BOOLEAN_TYPE)
    प्रत्यागम t2;
  यदि (वृक्ष_CODE (t2) == BOOLEAN_TYPE)
    प्रत्यागम t1;

  प्रत्यागम c_common_type (t1, t2);
}



/* Helper function for comptypes.  For two compatible types, return 1
   if they pass consistency checks.  In particular we test that
   TYPE_CANONICAL is set correctly, i.e. the two types can alias.  */

स्थिर तार्किक
comptypes_verify (वृक्ष type1, वृक्ष type2)
{
  यदि (type1 == type2 || !type1 || !type2
      || वृक्ष_CODE (type1) == ERROR_MARK || वृक्ष_CODE (type2) == ERROR_MARK)
    प्रत्यागम सत्य;

  gcc_checking_assert (c_verify_type (type1));
  gcc_checking_assert (c_verify_type (type2));

  यदि (TYPE_CANONICAL (type1) != TYPE_CANONICAL (type2)
      && !TYPE_STRUCTURAL_EQUALITY_P (type1)
      && !TYPE_STRUCTURAL_EQUALITY_P (type2))
    {
      /* FIXME: check other types. */
      यदि (RECORD_OR_UNION_TYPE_P (type1)
	  || वृक्ष_CODE (type1) == ENUMERAL_TYPE
	  || वृक्ष_CODE (type2) == ENUMERAL_TYPE)
	प्रत्यागम असत्य;
    }
  प्रत्यागम सत्य;
}

संरचना comptypes_data {

  /* output */
  तार्किक enum_and_int_p;
  तार्किक different_types_p;
  तार्किक warning_needed;

  /* context */
  तार्किक anon_field;
  तार्किक pointedto;

  /* configuration */
  तार्किक equiv;
  तार्किक ignore_promoting_args;

  ध्रुव संरचना tagged_tu_seen_cache* cache;
};


/* Helper function for composite_type.  This function ignores when the
   function type of an old-style declaration is incompatible with a type
   of a declaration with prototype because some are arguments are not
   self-promoting.  This is ignored only for function types but not
   ignored in a nested context.  */

स्थिर तार्किक
comptypes_check_for_composite (वृक्ष t1, वृक्ष t2)
{
  संरचना comptypes_data data = { };
  data.ignore_promoting_args = FUNCTION_TYPE == वृक्ष_CODE (t1);
  प्रत्यागम comptypes_internal (t1, t2, &data);
}


/* C implementation of compatible_types_for_indirection_note_p.  */

तार्किक
compatible_types_for_indirection_note_p (वृक्ष type1, वृक्ष type2)
{
  प्रत्यागम comptypes (type1, type2);
}

/* Return true if TYPE1 and TYPE2 are compatible types for assignment
   or various other operations.  */

तार्किक
comptypes (वृक्ष type1, वृक्ष type2)
{
  संरचना comptypes_data data = { };
  तार्किक ret = comptypes_internal (type1, type2, &data);

  gcc_checking_assert (!ret || comptypes_verify (type1, type2));

  प्रत्यागम ret;
}


/* Like comptypes, but it returns non-zero only for identical
   types.  */

तार्किक
comptypes_same_p (वृक्ष type1, वृक्ष type2)
{
  संरचना comptypes_data data = { };
  तार्किक ret = comptypes_internal (type1, type2, &data);

  gcc_checking_assert (!ret || comptypes_verify (type1, type2));

  यदि (data.different_types_p)
    प्रत्यागम असत्य;

  प्रत्यागम ret;
}


/* Like comptypes, but if it returns true because enum and int are
   compatible, it sets *ENUM_AND_INT_P to true.  */

तार्किक
comptypes_check_enum_int (वृक्ष type1, वृक्ष type2, तार्किक *enum_and_int_p)
{
  संरचना comptypes_data data = { };
  तार्किक ret = comptypes_internal (type1, type2, &data);
  *enum_and_int_p = data.enum_and_int_p;

  gcc_checking_assert (!ret || comptypes_verify (type1, type2));

  प्रत्यागम ret;
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

तार्किक
comptypes_equiv_p (वृक्ष type1, वृक्ष type2)
{
  संरचना comptypes_data data = { };
  data.equiv = सत्य;
  तार्किक ret = comptypes_internal (type1, type2, &data);

  /* check that different equivance classes are assigned only
     to types that are not compatible.  */
  gcc_checking_assert (ret || !comptypes (type1, type2));

  प्रत्यागम ret;
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

स्थिर तार्किक
comptypes_internal (const_वृक्ष type1, const_वृक्ष type2,
		    संरचना comptypes_data *data)
{
  const_वृक्ष t1 = type1;
  const_वृक्ष t2 = type2;

  /* Suppress errors caused by previously reported errors.  */

  यदि (t1 == t2 || !t1 || !t2
      || वृक्ष_CODE (t1) == ERROR_MARK || वृक्ष_CODE (t2) == ERROR_MARK)
    प्रत्यागम सत्य;

  /* Qualifiers must match. C99 6.7.3p9 */

  यदि (TYPE_QUALS (t1) != TYPE_QUALS (t2))
    प्रत्यागम असत्य;

  /* Enumerated types are compatible with integer types, but this is
     not transitive: two enumerated types in the same translation unit
     are compatible with each other only if they are the same type.  */

  यदि (वृक्ष_CODE (t1) == ENUMERAL_TYPE
      && COMPLETE_TYPE_P (t1)
      && वृक्ष_CODE (t2) != ENUMERAL_TYPE)
    {
      t1 = ENUM_UNDERLYING_TYPE (t1);
      यदि (वृक्ष_CODE (t2) != VOID_TYPE)
	{
	  data->enum_and_int_p = सत्य;
	  data->different_types_p = सत्य;
	}
    }
  अन्यथा यदि (वृक्ष_CODE (t2) == ENUMERAL_TYPE
	   && COMPLETE_TYPE_P (t2)
	   && वृक्ष_CODE (t1) != ENUMERAL_TYPE)
    {
      t2 = ENUM_UNDERLYING_TYPE (t2);
      यदि (वृक्ष_CODE (t1) != VOID_TYPE)
	{
	  data->enum_and_int_p = सत्य;
	  data->different_types_p = सत्य;
	}
    }

  यदि (t1 == t2)
    प्रत्यागम सत्य;

  /* Different classes of types can't be compatible.  */

  यदि (वृक्ष_CODE (t1) != वृक्ष_CODE (t2))
    प्रत्यागम असत्य;

  /* Allow for two different type nodes which have essentially the same
     definition.  Note that we already checked for equality of the type
     qualifiers (just above).  */

  यदि (वृक्ष_CODE (t1) != ARRAY_TYPE
      && TYPE_MAIN_VARIANT (t1) == TYPE_MAIN_VARIANT (t2))
    प्रत्यागम सत्य;

  पूर्णाङ्क attrval;

  /* 1 if no need for warning yet, 2 if warning cause has been seen.  */
  यदि (!(attrval = comp_type_attributes (t1, t2)))
    प्रत्यागम असत्य;

  यदि (2 == attrval)
    data->warning_needed = सत्य;

  विकल्प (वृक्ष_CODE (t1))
    {
    पक्ष INTEGER_TYPE:
    पक्ष FIXED_POINT_TYPE:
    पक्ष REAL_TYPE:
    पक्ष BITINT_TYPE:
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
      प्रत्यागम TYPE_CANONICAL (t1) == TYPE_CANONICAL (t2);

    पक्ष POINTER_TYPE:
      /* Do not remove mode information.  */
      यदि (TYPE_MODE (t1) != TYPE_MODE (t2))
	प्रत्यागम असत्य;
      data->pointedto = सत्य;
      प्रत्यागम comptypes_internal (वृक्ष_TYPE (t1), वृक्ष_TYPE (t2), data);

    पक्ष FUNCTION_TYPE:
      प्रत्यागम function_types_compatible_p (t1, t2, data);

    पक्ष ARRAY_TYPE:
      {
	वृक्ष d1 = TYPE_DOMAIN (t1);
	वृक्ष d2 = TYPE_DOMAIN (t2);

	/* Target types must match incl. qualifiers.  */
	यदि (!comptypes_internal (वृक्ष_TYPE (t1), वृक्ष_TYPE (t2), data))
	  प्रत्यागम असत्य;

	यदि ((d1 == NULL_वृक्ष) != (d2 == NULL_वृक्ष))
	  data->different_types_p = सत्य;
	/* Ignore size mismatches when forming equivalence classes.  */
	यदि (data->equiv)
	  प्रत्यागम सत्य;
	/* Sizes must match unless one is missing or variable.  */
	यदि (d1 == NULL_वृक्ष || d2 == NULL_वृक्ष || d1 == d2)
	  प्रत्यागम सत्य;

	तार्किक d1_variable = शीर्ष_array_vla_p (t1);
	तार्किक d2_variable = शीर्ष_array_vla_p (t2);

	यदि (d1_variable != d2_variable)
	  data->different_types_p = सत्य;
	यदि (d1_variable || d2_variable)
	  प्रत्यागम सत्य;

	तार्किक d1_zero = zero_length_array_type_p (t1)
		       || flexible_array_member_type_p (t1);

	तार्किक d2_zero = zero_length_array_type_p (t2)
		       || flexible_array_member_type_p (t2);

	यदि (d1_zero && d2_zero)
	  प्रत्यागम सत्य;
	यदि (d1_zero || d2_zero)
	  प्रत्यागम असत्य;

	यदि (!वृक्ष_int_cst_equal (TYPE_MIN_मूल्य (d1), TYPE_MIN_मूल्य (d2))
	    || !वृक्ष_int_cst_equal (TYPE_MAX_मूल्य (d1), TYPE_MAX_मूल्य (d2)))
	  प्रत्यागम असत्य;

	प्रत्यागम सत्य;
      }

    पक्ष ENUMERAL_TYPE:
    पक्ष RECORD_TYPE:
    पक्ष UNION_TYPE:

      यदि (!flag_isoc23)
	प्रत्यागम असत्य;

      प्रत्यागम tagged_types_tu_compatible_p (t1, t2, data);

    पक्ष VECTOR_TYPE:
      प्रत्यागम known_eq (TYPE_VECTOR_SUBPARTS (t1), TYPE_VECTOR_SUBPARTS (t2))
	     && comptypes_internal (वृक्ष_TYPE (t1), वृक्ष_TYPE (t2), data);

    स्वभाव:
      प्रत्यागम असत्य;
    }
  gcc_unreachable ();
}

/* Return true if TTL and TTR are pointers to types that are equivalent, ignoring
   their qualifiers, except for named address spaces.  If the pointers point to
   different named addresses, then we must determine if one address space is a
   subset of the other.  */

स्थिर तार्किक
comp_target_types (location_t location, वृक्ष ttl, वृक्ष ttr)
{
  वृक्ष mvl = वृक्ष_TYPE (ttl);
  वृक्ष mvr = वृक्ष_TYPE (ttr);
  addr_space_t asl = TYPE_ADDR_SPACE (mvl);
  addr_space_t asr = TYPE_ADDR_SPACE (mvr);
  addr_space_t as_common;

  /* Fail if pointers point to incompatible address spaces.  */
  यदि (!addr_space_superset (asl, asr, &as_common))
    प्रत्यागम 0;

  /* Qualifiers on element types of array types that are
     pointer targets are also removed.  */
  संरचना comptypes_data data = { };
  यदि (!comptypes_internal (remove_qualifiers (mvl),
			   remove_qualifiers (mvr), &data))
    प्रत्यागम असत्य;

  /* For pedantic use comptypes on arrays before removing
     qualifiers on the element type. */
  यदि (वृक्ष_CODE (mvl) == ARRAY_TYPE
      && वृक्ष_CODE (mvr) == ARRAY_TYPE
      && !comptypes (mvl, mvr))
    pedwarn_c11 (location, OPT_Wpedantic, "invalid use of pointers to arrays "
					  "with different qualifiers in ISO C "
					  "before C23");

  यदि (data.warning_needed)
    pedwarn (location, OPT_Wpedantic, "types are not quite compatible");

  यदि (data.enum_and_int_p && warn_cxx_compat)
    warning_at (location, OPT_Wc___compat,
		"pointer target types incompatible in C++");

  प्रत्यागम सत्य;
}

/* Subroutines of `comptypes'.  */

/* Return true if two 'struct', 'union', or 'enum' types T1 and T2 are
   compatible.  The two types are not the same (which has been
   checked earlier in comptypes_internal).  */

स्थिर तार्किक
tagged_types_tu_compatible_p (const_वृक्ष t1, const_वृक्ष t2,
			      संरचना comptypes_data *data)
{
  वृक्ष s1, s2;

  यदि (c_type_tag (t1) != c_type_tag (t2))
    प्रत्यागम असत्य;

  /* When forming equivalence classes for TYPE_CANONICAL in C23, we treat
     structs with the same tag as equivalent, but only when they are targets
     of pointers inside other structs.  */
  यदि (data->equiv && data->pointedto && NULL_वृक्ष != c_type_tag (t1))
    प्रत्यागम सत्य;

  /* Different types without tag are incompatible except as an anonymous
     field or when forming equivalence classes for TYPE_CANONICAL.  */
  यदि (!data->anon_field && !data->equiv && NULL_वृक्ष == c_type_tag (t1))
    प्रत्यागम असत्य;

  यदि (!data->anon_field && TYPE_STUB_DECL (t1) != TYPE_STUB_DECL (t2))
    data->different_types_p = सत्य;

  /* Incomplete types are incompatible inside a TU.  */
  यदि (TYPE_SIZE (t1) == रिक्त || TYPE_SIZE (t2) == रिक्त)
    प्रत्यागम असत्य;

  यदि (ENUMERAL_TYPE != वृक्ष_CODE (t1)
      && (TYPE_REVERSE_STORAGE_ORDER (t1)
	  != TYPE_REVERSE_STORAGE_ORDER (t2)))
    प्रत्यागम असत्य;

  यदि (TYPE_USER_ALIGN (t1) != TYPE_USER_ALIGN (t2))
    data->different_types_p = सत्य;

  /* For types already being looked at in some active
     invocation of this function, assume compatibility.
     The cache is built as a linked list on the stack
     with the head of the list passed downwards.  */
  प्रति (ध्रुव संरचना tagged_tu_seen_cache *t = data->cache;
       t != रिक्त; t = t->next)
    यदि (t->t1 == t1 && t->t2 == t2)
      प्रत्यागम सत्य;

  ध्रुव संरचना tagged_tu_seen_cache entry = { data->cache, t1, t2 };

  विकल्प (वृक्ष_CODE (t1))
    {
    पक्ष ENUMERAL_TYPE:
      {
	यदि (!comptypes (ENUM_UNDERLYING_TYPE (t1), ENUM_UNDERLYING_TYPE (t2)))
	  प्रत्यागम असत्य;

	/* Speed up the case where the type values are in the same order.  */
	वृक्ष tv1 = TYPE_मूल्यावली (t1);
	वृक्ष tv2 = TYPE_मूल्यावली (t2);

	यदि (tv1 == tv2)
	  प्रत्यागम सत्य;

	प्रति (;tv1 && tv2; tv1 = वृक्ष_CHAIN (tv1), tv2 = वृक्ष_CHAIN (tv2))
	  {
	    यदि (वृक्ष_PURPOSE (tv1) != वृक्ष_PURPOSE (tv2))
	      भङ्ग;

	    यदि (simple_cst_equal (DECL_INITIAL (वृक्ष_मूल्य (tv1)),
				  DECL_INITIAL (वृक्ष_मूल्य (tv2))) != 1)
	      भङ्ग;
	  }

	यदि (tv1 == NULL_वृक्ष && tv2 == NULL_वृक्ष)
	  प्रत्यागम सत्य;

	यदि (tv1 == NULL_वृक्ष || tv2 == NULL_वृक्ष)
	  प्रत्यागम असत्य;

	यदि (list_length (TYPE_मूल्यावली (t1)) != list_length (TYPE_मूल्यावली (t2)))
	  प्रत्यागम असत्य;

	प्रति (s1 = TYPE_मूल्यावली (t1); s1; s1 = वृक्ष_CHAIN (s1))
	  {
	    s2 = purpose_member (वृक्ष_PURPOSE (s1), TYPE_मूल्यावली (t2));

	    यदि (s2 == रिक्त
		|| simple_cst_equal (DECL_INITIAL (वृक्ष_मूल्य (s1)),
				     DECL_INITIAL (वृक्ष_मूल्य (s2))) != 1)
	      प्रत्यागम असत्य;
	  }

	प्रत्यागम सत्य;
      }

    पक्ष UNION_TYPE:
    पक्ष RECORD_TYPE:

	यदि (list_length (TYPE_FIELDS (t1)) != list_length (TYPE_FIELDS (t2)))
	  प्रत्यागम असत्य;

	प्रति (s1 = TYPE_FIELDS (t1), s2 = TYPE_FIELDS (t2);
	     s1 && s2;
	     s1 = DECL_CHAIN (s1), s2 = DECL_CHAIN (s2))
	  {
	    gcc_assert (वृक्ष_CODE (s1) == FIELD_DECL);
	    gcc_assert (वृक्ष_CODE (s2) == FIELD_DECL);

	    वृक्ष ft1 = वृक्ष_TYPE (s1);
	    वृक्ष ft2 = वृक्ष_TYPE (s2);

	    यदि (DECL_NAME (s1) != DECL_NAME (s2))
	      प्रत्यागम असत्य;

	    यदि (DECL_ALIGN (s1) != DECL_ALIGN (s2))
	      प्रत्यागम असत्य;

	    यदि (DECL_C_BIT_FIELD (s1) != DECL_C_BIT_FIELD (s2))
	       प्रत्यागम असत्य;

	    यदि (DECL_C_BIT_FIELD (s1))
	      {
		यदि (!वृक्ष_int_cst_equal (DECL_SIZE (s1), DECL_SIZE (s2)))
		  प्रत्यागम असत्य;

		ft1 = DECL_BIT_FIELD_TYPE (s1);
		ft2 = DECL_BIT_FIELD_TYPE (s2);
	      }

	    यदि (!ft1 || !ft2)
	      प्रत्यागम असत्य;

	    यदि (वृक्ष_CODE (ft1) == ERROR_MARK || वृक्ष_CODE (ft2) == ERROR_MARK)
	      प्रत्यागम असत्य;

	    data->anon_field = !DECL_NAME (s1);
	    data->pointedto = असत्य;

	    ध्रुव संरचना tagged_tu_seen_cache *cache = data->cache;
	    data->cache = &entry;
	    तार्किक ret = comptypes_internal (ft1, ft2, data);
	    data->cache = cache;
	    यदि (!ret)
	      प्रत्यागम असत्य;

	    वृक्ष st1 = TYPE_SIZE (वृक्ष_TYPE (s1));
	    वृक्ष st2 = TYPE_SIZE (वृक्ष_TYPE (s2));

	    यदि (data->equiv
		&& st1 && वृक्ष_CODE (st1) == INTEGER_CST
		&& st2 && वृक्ष_CODE (st2) == INTEGER_CST
		&& !वृक्ष_int_cst_equal (st1, st2))
	     प्रत्यागम असत्य;

	    वृक्ष counted_by1 = lookup_attribute ("counted_by",
						 DECL_ATTRIBUTES (s1));
	    वृक्ष counted_by2 = lookup_attribute ("counted_by",
						 DECL_ATTRIBUTES (s2));
	    /* If there is no counted_by attribute for both fields.  */
	    यदि (!counted_by1 && !counted_by2)
	      अनुवर्त;

	    /* If only one field has counted_by attribute.  */
	    यदि ((counted_by1 && !counted_by2)
		|| (!counted_by1 && counted_by2))
	      प्रत्यागम असत्य;

	    /* Now both s1 and s2 have counted_by attributes, check
	       whether they are the same.  */

	    वृक्ष counted_by_field1
	      = lookup_field (t1, वृक्ष_मूल्य (वृक्ष_मूल्य (counted_by1)));
	    वृक्ष counted_by_field2
	      = lookup_field (t2, वृक्ष_मूल्य (वृक्ष_मूल्य (counted_by2)));

	    gcc_assert (counted_by_field1 && counted_by_field2);

	    यावत् (वृक्ष_CHAIN (counted_by_field1))
	      counted_by_field1 = वृक्ष_CHAIN (counted_by_field1);
	    यावत् (वृक्ष_CHAIN (counted_by_field2))
	      counted_by_field2 = वृक्ष_CHAIN (counted_by_field2);

	    यदि (DECL_NAME (वृक्ष_मूल्य (counted_by_field1))
		!= DECL_NAME (वृक्ष_मूल्य (counted_by_field2)))
	      प्रत्यागम असत्य;
	  }
	प्रत्यागम सत्य;

    स्वभाव:
      gcc_unreachable ();
    }
}

/* Return true if two function types F1 and F2 are compatible.
   If either type specifies no argument types,
   the other must specify a fixed number of self-promoting arg types.
   Otherwise, if one type specifies only the number of arguments,
   the other must specify that number of self-promoting arg types.
   Otherwise, the argument types must match.  */

स्थिर तार्किक
function_types_compatible_p (const_वृक्ष f1, const_वृक्ष f2,
			     संरचना comptypes_data *data)
{
  वृक्ष ret1 = वृक्ष_TYPE (f1);
  वृक्ष ret2 = वृक्ष_TYPE (f2);

  /* 'volatile' qualifiers on a function's return type used to mean
     the function is noreturn.  */
  यदि (TYPE_VOLATILE (ret1) != TYPE_VOLATILE (ret2))
    pedwarn (निवेश_location, 0, "function return types not compatible due to %<volatile%>");
  यदि (TYPE_VOLATILE (ret1))
    ret1 = build_qualified_type (TYPE_MAIN_VARIANT (ret1),
				 TYPE_QUALS (ret1) & ~TYPE_QUAL_VOLATILE);
  यदि (TYPE_VOLATILE (ret2))
    ret2 = build_qualified_type (TYPE_MAIN_VARIANT (ret2),
				 TYPE_QUALS (ret2) & ~TYPE_QUAL_VOLATILE);

  तार्किक ignore_pargs = data->ignore_promoting_args;
  data->ignore_promoting_args = असत्य;

  यदि (!comptypes_internal (ret1, ret2, data))
    प्रत्यागम असत्य;

  data->ignore_promoting_args = ignore_pargs;

  वृक्ष args1 = TYPE_ARG_TYPES (f1);
  वृक्ष args2 = TYPE_ARG_TYPES (f2);

  यदि ((args1 == NULL_वृक्ष) != (args2 == NULL_वृक्ष))
    data->different_types_p = सत्य;

  /* An unspecified parmlist matches any specified parmlist
     whose argument types don't need default promotions.  */

  यदि (args1 == NULL_वृक्ष)
    {
      यदि (TYPE_NO_NAMED_ARGS_STDARG_P (f1) != TYPE_NO_NAMED_ARGS_STDARG_P (f2))
	प्रत्यागम असत्य;
      यदि (!(data->ignore_promoting_args || self_promoting_args_p (args2)))
	प्रत्यागम असत्य;
      data->ignore_promoting_args = असत्य;
      /* If one of these types comes from a non-prototype fn definition,
	 compare that with the other type's arglist.
	 If they don't match, ask for a warning (but no error).  */
      यदि (TYPE_ACTUAL_ARG_TYPES (f1)
	  && !type_lists_compatible_p (args2, TYPE_ACTUAL_ARG_TYPES (f1), data))
	 data->warning_needed = सत्य;
      प्रत्यागम सत्य;
    }
  यदि (args2 == NULL_वृक्ष)
    {
      यदि (TYPE_NO_NAMED_ARGS_STDARG_P (f1) != TYPE_NO_NAMED_ARGS_STDARG_P (f2))
	प्रत्यागम असत्य;
      यदि (!(data->ignore_promoting_args || self_promoting_args_p (args1)))
	प्रत्यागम असत्य;
      data->ignore_promoting_args = असत्य;
      यदि (TYPE_ACTUAL_ARG_TYPES (f2)
	  && !type_lists_compatible_p (args1, TYPE_ACTUAL_ARG_TYPES (f2), data))
	data->warning_needed = सत्य;
      प्रत्यागम सत्य;
    }

  /* Both types have argument lists: compare them and propagate results.  */
  प्रत्यागम type_lists_compatible_p (args1, args2, data);
}

/* Check two lists of types for compatibility, returning false for
   incompatible, true for compatible.  */

स्थिर तार्किक
type_lists_compatible_p (const_वृक्ष args1, const_वृक्ष args2,
			 संरचना comptypes_data *data)
{
  यावत् (1)
    {
      यदि (args1 == NULL_वृक्ष && args2 == NULL_वृक्ष)
	प्रत्यागम सत्य;
      /* If one list is shorter than the other,
	 they fail to match.  */
      यदि (args1 == NULL_वृक्ष || args2 == NULL_वृक्ष)
	प्रत्यागम असत्य;
      वृक्ष a1 = वृक्ष_मूल्य (args1);
      वृक्ष a2 = वृक्ष_मूल्य (args2);
      वृक्ष mv1 = remove_qualifiers (a1);
      वृक्ष mv2 = remove_qualifiers (a2);

      gcc_assert (mv2);
      gcc_assert (mv2);

      /* If one of the lists has an error marker, ignore this arg.  */
      यदि (वृक्ष_CODE (a1) == ERROR_MARK
	       || वृक्ष_CODE (a2) == ERROR_MARK)
	;
      अन्यथा यदि (!comptypes_internal (mv1, mv2, data))
	{
	  data->different_types_p = सत्य;
	  /* Allow  wait (union {union wait *u; int *i} *)
	     and  wait (union wait *)  to be compatible.  */
	  यदि (वृक्ष_CODE (a1) == UNION_TYPE
	      && (TYPE_NAME (a1) == NULL_वृक्ष
		  || TYPE_TRANSPARENT_AGGR (a1))
	      && वृक्ष_CODE (TYPE_SIZE (a1)) == INTEGER_CST
	      && वृक्ष_int_cst_equal (TYPE_SIZE (a1),
				     TYPE_SIZE (a2)))
	    {
	      वृक्ष memb;
	      प्रति (memb = TYPE_FIELDS (a1);
		   memb; memb = DECL_CHAIN (memb))
		{
		  वृक्ष mv3 = remove_qualifiers (वृक्ष_TYPE (memb));
		  यदि (comptypes_internal (mv3, mv2, data))
		    भङ्ग;
		}
	      यदि (memb == NULL_वृक्ष)
		प्रत्यागम असत्य;
	    }
	  अन्यथा यदि (वृक्ष_CODE (a2) == UNION_TYPE
		   && (TYPE_NAME (a2) == NULL_वृक्ष
		       || TYPE_TRANSPARENT_AGGR (a2))
		   && वृक्ष_CODE (TYPE_SIZE (a2)) == INTEGER_CST
		   && वृक्ष_int_cst_equal (TYPE_SIZE (a2),
					  TYPE_SIZE (a1)))
	    {
	      वृक्ष memb;
	      प्रति (memb = TYPE_FIELDS (a2);
		   memb; memb = DECL_CHAIN (memb))
		{
		  वृक्ष mv3 = remove_qualifiers (वृक्ष_TYPE (memb));
		  यदि (comptypes_internal (mv3, mv1, data))
		    भङ्ग;
		}
	      यदि (memb == NULL_वृक्ष)
		प्रत्यागम असत्य;
	    }
	  अन्यथा
	    प्रत्यागम असत्य;
	}

      args1 = वृक्ष_CHAIN (args1);
      args2 = वृक्ष_CHAIN (args2);
    }
}

/* Compute the size to increment a pointer by.  When a function type or void
   type or incomplete type is passed, size_one_node is returned.
   This function does not emit any diagnostics; the caller is responsible
   for that.  */

स्थिर वृक्ष
c_size_in_bytes (const_वृक्ष type)
{
  गणना वृक्ष_code code = वृक्ष_CODE (type);

  यदि (code == FUNCTION_TYPE || code == VOID_TYPE || code == ERROR_MARK
      || !COMPLETE_TYPE_P (type))
    प्रत्यागम size_one_गाँठ;

  /* Convert in case a char is more than one unit.  */
  प्रत्यागम size_binop_loc (निवेश_location, CEIL_DIV_व्यंजक, TYPE_SIZE_UNIT (type),
			 size_int (TYPE_PRECISION (char_type_गाँठ)
				   / BITS_PER_UNIT));
}

/* Return either DECL or its known constant value (if it has one).  */

वृक्ष
decl_constant_मूल्य_1 (वृक्ष decl, तार्किक in_init)
{
  यदि (/* Note that DECL_INITIAL isn't valid for a PARM_DECL.  */
      वृक्ष_CODE (decl) != PARM_DECL
      && !वृक्ष_THIS_VOLATILE (decl)
      && वृक्ष_READONLY (decl)
      && DECL_INITIAL (decl) != NULL_वृक्ष
      && !error_operand_p (DECL_INITIAL (decl))
      /* This is invalid if initial value is not constant.
	 If it has either a function call, a memory reference,
	 or a variable, then re-evaluating it could give different results.  */
      && वृक्ष_CONSTANT (DECL_INITIAL (decl))
      /* Check for cases where this is sub-optimal, even though valid.  */
      && (in_init || वृक्ष_CODE (DECL_INITIAL (decl)) != CONSTRUCTOR))
    प्रत्यागम DECL_INITIAL (decl);
  प्रत्यागम decl;
}

/* Return either DECL or its known constant value (if it has one).
   Like the above, but always return decl outside of functions.  */

वृक्ष
decl_constant_मूल्य (वृक्ष decl)
{
  /* Don't change a variable array bound or initial value to a constant
     in a place where a variable is invalid.  */
  प्रत्यागम current_function_decl ? decl_constant_मूल्य_1 (decl, असत्य) : decl;
}

/* Convert the array expression EXP to a pointer.  */
स्थिर वृक्ष
array_to_pointer_conversion (location_t loc, वृक्ष exp)
{
  वृक्ष orig_exp = exp;
  वृक्ष type = वृक्ष_TYPE (exp);
  वृक्ष adr;
  वृक्ष restype = वृक्ष_TYPE (type);
  वृक्ष ptrtype;

  gcc_assert (वृक्ष_CODE (type) == ARRAY_TYPE);

  STRIP_TYPE_NOPS (exp);

  copy_warning (exp, orig_exp);

  ptrtype = c_build_pointer_type (restype);

  यदि (INDIRECT_REF_P (exp))
    प्रत्यागम convert (ptrtype, वृक्ष_OPERAND (exp, 0));

  /* In C++ array compound literals are temporary objects unless they are
     const or appear in namespace scope, so they are destroyed too soon
     to use them for much of anything  (c++/53220).  */
  यदि (warn_cxx_compat && वृक्ष_CODE (exp) == COMPOUND_LITERAL_व्यंजक)
    {
      वृक्ष decl = वृक्ष_OPERAND (वृक्ष_OPERAND (exp, 0), 0);
      यदि (!वृक्ष_READONLY (decl) && !वृक्ष_STATIC (decl))
	warning_at (DECL_SOURCE_LOCATION (decl), OPT_Wc___compat,
		    "converting an array compound literal to a pointer "
		    "leads to a dangling pointer in C++");
    }

  adr = build_unary_op (loc, ADDR_व्यंजक, exp, सत्य);
  प्रत्यागम convert (ptrtype, adr);
}

/* Convert the function expression EXP to a pointer.  */
स्थिर वृक्ष
function_to_pointer_conversion (location_t loc, वृक्ष exp)
{
  वृक्ष orig_exp = exp;

  gcc_assert (वृक्ष_CODE (वृक्ष_TYPE (exp)) == FUNCTION_TYPE);

  STRIP_TYPE_NOPS (exp);

  copy_warning (exp, orig_exp);

  वृक्ष exp2 = build_unary_op (loc, ADDR_व्यंजक, exp, असत्य);

  /* If the function is defined and known to not require a non-local
     context, make sure no trampoline is generated.  */
  यदि (वृक्ष_CODE (exp) == FUNCTION_DECL
      && DECL_INITIAL (exp) && !C_FUNC_NONLOCAL_CONTEXT (exp))
   वृक्ष_NO_TRAMPOLINE (exp2) = 1;

  प्रत्यागम exp2;
}

/* Mark EXP as read, not just set, for set but not used -Wunused
   warning purposes.  */

शून्य
mark_exp_read (वृक्ष exp)
{
  विकल्प (वृक्ष_CODE (exp))
    {
    पक्ष VAR_DECL:
    पक्ष PARM_DECL:
      DECL_READ_P (exp) = 1;
      भङ्ग;
    CASE_CONVERT:
      यदि (VOID_TYPE_P (वृक्ष_TYPE (exp)))
	विकल्प (वृक्ष_CODE (वृक्ष_OPERAND (exp, 0)))
	  {
	  पक्ष PREINCREMENT_व्यंजक:
	  पक्ष PREDECREMENT_व्यंजक:
	  पक्ष POSTINCREMENT_व्यंजक:
	  पक्ष POSTDECREMENT_व्यंजक:
	    प्रत्यागम;
	  स्वभाव:
	    भङ्ग;
	  }
      /* FALLTHRU */
    पक्ष ARRAY_REF:
    पक्ष COMPONENT_REF:
    पक्ष MODIFY_व्यंजक:
    पक्ष REALPART_व्यंजक:
    पक्ष IMAGPART_व्यंजक:
    पक्ष ADDR_व्यंजक:
    पक्ष VIEW_CONVERT_व्यंजक:
    पक्ष PREINCREMENT_व्यंजक:
    पक्ष PREDECREMENT_व्यंजक:
    पक्ष POSTINCREMENT_व्यंजक:
    पक्ष POSTDECREMENT_व्यंजक:
      mark_exp_read (वृक्ष_OPERAND (exp, 0));
      भङ्ग;
    पक्ष COMPOUND_व्यंजक:
      /* Pattern match what build_atomic_assign produces with modifycode
	 NOP_EXPR.  */
      यदि (VAR_P (वृक्ष_OPERAND (exp, 1))
	  && DECL_ARTIFICIAL (वृक्ष_OPERAND (exp, 1))
	  && वृक्ष_CODE (वृक्ष_OPERAND (exp, 0)) == COMPOUND_व्यंजक)
	{
	  वृक्ष t1 = वृक्ष_OPERAND (वृक्ष_OPERAND (exp, 0), 0);
	  वृक्ष t2 = वृक्ष_OPERAND (वृक्ष_OPERAND (exp, 0), 1);
	  यदि (वृक्ष_CODE (t1) == TARGET_व्यंजक
	      && TARGET_व्यंजक_SLOT (t1) == वृक्ष_OPERAND (exp, 1)
	      && वृक्ष_CODE (t2) == CALL_व्यंजक)
	    {
	      वृक्ष fndecl = get_callee_fndecl (t2);
	      वृक्ष arg = NULL_वृक्ष;
	      यदि (fndecl
		  && वृक्ष_CODE (fndecl) == FUNCTION_DECL
		  && fndecl_built_in_p (fndecl, BUILT_IN_NORMAL)
		  && call_व्यंजक_nargs (t2) >= 2)
		विकल्प (DECL_FUNCTION_CODE (fndecl))
		  {
		  पक्ष BUILT_IN_ATOMIC_STORE:
		    arg = CALL_व्यंजक_ARG (t2, 1);
		    भङ्ग;
		  पक्ष BUILT_IN_ATOMIC_STORE_1:
		  पक्ष BUILT_IN_ATOMIC_STORE_2:
		  पक्ष BUILT_IN_ATOMIC_STORE_4:
		  पक्ष BUILT_IN_ATOMIC_STORE_8:
		  पक्ष BUILT_IN_ATOMIC_STORE_16:
		    arg = CALL_व्यंजक_ARG (t2, 0);
		    भङ्ग;
		  स्वभाव:
		    भङ्ग;
		  }
	      यदि (arg)
		{
		  STRIP_NOPS (arg);
		  यदि (वृक्ष_CODE (arg) == ADDR_व्यंजक
		      && DECL_P (वृक्ष_OPERAND (arg, 0))
		      && TYPE_ATOMIC (वृक्ष_TYPE (वृक्ष_OPERAND (arg, 0))))
		    mark_exp_read (वृक्ष_OPERAND (arg, 0));
		}
	    }
	}
      /* FALLTHRU */
    पक्ष C_MAYBE_CONST_व्यंजक:
      mark_exp_read (वृक्ष_OPERAND (exp, 1));
      भङ्ग;
    पक्ष OMP_ARRAY_SECTION:
      mark_exp_read (वृक्ष_OPERAND (exp, 0));
      यदि (वृक्ष_OPERAND (exp, 1))
	mark_exp_read (वृक्ष_OPERAND (exp, 1));
      यदि (वृक्ष_OPERAND (exp, 2))
	mark_exp_read (वृक्ष_OPERAND (exp, 2));
      भङ्ग;
    स्वभाव:
      भङ्ग;
    }
}

/* Perform the default conversion of arrays and functions to pointers.
   Return the result of converting EXP.  For any other expression, just
   return EXP.

   LOC is the location of the expression.  */

संरचना c_व्यंजक
default_function_array_conversion (location_t loc, संरचना c_व्यंजक exp)
{
  वृक्ष orig_exp = exp.मूल्य;
  वृक्ष type = वृक्ष_TYPE (exp.मूल्य);
  गणना वृक्ष_code code = वृक्ष_CODE (type);

  विकल्प (code)
    {
    पक्ष ARRAY_TYPE:
      {
	तार्किक not_lvalue = असत्य;
	तार्किक lvalue_array_p;

	यावत् ((वृक्ष_CODE (exp.मूल्य) == NON_LVALUE_व्यंजक
		|| CONVERT_व्यंजक_P (exp.मूल्य))
	       && वृक्ष_TYPE (वृक्ष_OPERAND (exp.मूल्य, 0)) == type)
	  {
	    यदि (वृक्ष_CODE (exp.मूल्य) == NON_LVALUE_व्यंजक)
	      not_lvalue = सत्य;
	    exp.मूल्य = वृक्ष_OPERAND (exp.मूल्य, 0);
	  }

	copy_warning (exp.मूल्य, orig_exp);

	lvalue_array_p = !not_lvalue && lvalue_p (exp.मूल्य);
	यदि (!flag_isoc99 && !lvalue_array_p)
	  {
	    /* Before C99, non-lvalue arrays do not decay to pointers.
	       Normally, using such an array would be invalid; but it can
	       be used correctly inside sizeof or as a statement expression.
	       Thus, do not give an error here; an error will result later.  */
	    प्रत्यागम exp;
	  }

	exp.मूल्य = array_to_pointer_conversion (loc, exp.मूल्य);
      }
      भङ्ग;
    पक्ष FUNCTION_TYPE:
      exp.मूल्य = function_to_pointer_conversion (loc, exp.मूल्य);
      भङ्ग;
    स्वभाव:
      भङ्ग;
    }

  प्रत्यागम exp;
}

संरचना c_व्यंजक
default_function_array_read_conversion (location_t loc, संरचना c_व्यंजक exp)
{
  mark_exp_read (exp.मूल्य);
  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  यदि (वृक्ष_CODE (exp.मूल्य) == COMPONENT_REF
      && handle_counted_by_p (exp.मूल्य))
    exp.मूल्य = handle_counted_by_for_component_ref (loc, exp.मूल्य);
  प्रत्यागम default_function_array_conversion (loc, exp);
}

/* Return whether EXPR should be treated as an atomic lvalue for the
   purposes of load and store handling.  */

स्थिर तार्किक
really_atomic_lvalue (वृक्ष व्यंजक)
{
  यदि (error_operand_p (व्यंजक))
    प्रत्यागम असत्य;
  यदि (!TYPE_ATOMIC (वृक्ष_TYPE (व्यंजक)))
    प्रत्यागम असत्य;
  यदि (!COMPLETE_TYPE_P (वृक्ष_TYPE (व्यंजक)))
    प्रत्यागम असत्य;
  यदि (!lvalue_p (व्यंजक))
    प्रत्यागम असत्य;

  /* Ignore _Atomic on register variables, since their addresses can't
     be taken so (a) atomicity is irrelevant and (b) the normal atomic
     sequences wouldn't work.  Ignore _Atomic on structures containing
     bit-fields, since accessing elements of atomic structures or
     unions is undefined behavior (C11 6.5.2.3#5), but it's unclear if
     it's undefined at translation time or execution time, and the
     normal atomic sequences again wouldn't work.  */
  यावत् (handled_component_p (व्यंजक))
    {
      यदि (वृक्ष_CODE (व्यंजक) == COMPONENT_REF
	  && DECL_C_BIT_FIELD (वृक्ष_OPERAND (व्यंजक, 1)))
	प्रत्यागम असत्य;
      व्यंजक = वृक्ष_OPERAND (व्यंजक, 0);
    }
  यदि (वृक्ष_CODE (व्यंजक) == COMPOUND_LITERAL_व्यंजक)
    व्यंजक = COMPOUND_LITERAL_व्यंजक_DECL (व्यंजक);
  यदि (DECL_P (व्यंजक) && C_DECL_REGISTER (व्यंजक))
    प्रत्यागम असत्य;
  प्रत्यागम सत्य;
}

/* If EXPR is a named constant (C23) derived from a constexpr variable
   - that is, a reference to such a variable, or a member extracted by
   a sequence of structure and union (but not array) member accesses
   (where union member accesses must access the same member as
   initialized) - then return the corresponding initializer;
   otherwise, return NULL_TREE.  */

स्थिर वृक्ष
maybe_get_constexpr_init (वृक्ष व्यंजक)
{
  वृक्ष decl = NULL_वृक्ष;
  यदि (वृक्ष_CODE (व्यंजक) == VAR_DECL)
    decl = व्यंजक;
  अन्यथा यदि (वृक्ष_CODE (व्यंजक) == COMPOUND_LITERAL_व्यंजक)
    decl = COMPOUND_LITERAL_व्यंजक_DECL (व्यंजक);
  यदि (decl
      && C_DECL_DECLARED_CONSTEXPR (decl)
      && DECL_INITIAL (decl) != NULL_वृक्ष
      && !error_operand_p (DECL_INITIAL (decl)))
    प्रत्यागम DECL_INITIAL (decl);
  यदि (वृक्ष_CODE (व्यंजक) != COMPONENT_REF)
    प्रत्यागम NULL_वृक्ष;
  वृक्ष inner = maybe_get_constexpr_init (वृक्ष_OPERAND (व्यंजक, 0));
  यदि (inner == NULL_वृक्ष)
    प्रत्यागम NULL_वृक्ष;
  यावत् ((CONVERT_व्यंजक_P (inner) || वृक्ष_CODE (inner) == NON_LVALUE_व्यंजक)
	 && !error_operand_p (inner)
	 && (TYPE_MAIN_VARIANT (वृक्ष_TYPE (inner))
	     == TYPE_MAIN_VARIANT (वृक्ष_TYPE (वृक्ष_OPERAND (inner, 0)))))
    inner = वृक्ष_OPERAND (inner, 0);
  यदि (वृक्ष_CODE (inner) != CONSTRUCTOR)
    प्रत्यागम NULL_वृक्ष;
  वृक्ष field = वृक्ष_OPERAND (व्यंजक, 1);
  अचिन्हित HOST_WIDE_INT cidx;
  वृक्ष cfield, cvalue;
  तार्किक have_other_init = असत्य;
  FOR_EACH_CONSTRUCTOR_ELT (CONSTRUCTOR_ELTS (inner), cidx, cfield, cvalue)
    {
      यदि (cfield == field)
	प्रत्यागम cvalue;
      have_other_init = सत्य;
    }
  यदि (वृक्ष_CODE (वृक्ष_TYPE (inner)) == UNION_TYPE
      && (have_other_init || field != TYPE_FIELDS (वृक्ष_TYPE (inner))))
    प्रत्यागम NULL_वृक्ष;
  /* Return a default initializer.  */
  यदि (RECORD_OR_UNION_TYPE_P (वृक्ष_TYPE (व्यंजक)))
    प्रत्यागम build_constructor (वृक्ष_TYPE (व्यंजक), रिक्त);
  प्रत्यागम build_zero_cst (वृक्ष_TYPE (व्यंजक));
}

/* Helper function for convert_lvalue_to_rvalue called via
   walk_tree_without_duplicates.  Find DATA inside of the expression.  */

स्थिर वृक्ष
c_find_var_r (वृक्ष *tp, पूर्णाङ्क *walk_subtrees, शून्य *data)
{
  यदि (TYPE_P (*tp))
    *walk_subtrees = 0;
  अन्यथा यदि (*tp == (वृक्ष) data)
    प्रत्यागम *tp;
  प्रत्यागम NULL_वृक्ष;
}

/* Convert expression EXP (location LOC) from lvalue to rvalue,
   including converting functions and arrays to pointers if CONVERT_P.
   If READ_P, also mark the expression as having been read.  If
   FOR_INIT, constexpr expressions of structure and union type should
   be replaced by the corresponding CONSTRUCTOR; otherwise, only
   constexpr scalars (including elements of structures and unions) are
   replaced by their initializers.  */

संरचना c_व्यंजक
convert_lvalue_to_rvalue (location_t loc, संरचना c_व्यंजक exp,
			  तार्किक convert_p, तार्किक read_p, तार्किक for_init)
{
  तार्किक force_non_npc = असत्य;
  यदि (read_p)
    mark_exp_read (exp.मूल्य);
  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  यदि (read_p && वृक्ष_CODE (exp.मूल्य) == COMPONENT_REF
      && handle_counted_by_p (exp.मूल्य))
    exp.मूल्य = handle_counted_by_for_component_ref (loc, exp.मूल्य);

  यदि (convert_p)
    exp = default_function_array_conversion (loc, exp);
  यदि (!VOID_TYPE_P (वृक्ष_TYPE (exp.मूल्य))
      || (flag_isoc2y
	  && TYPE_QUALS (वृक्ष_TYPE (exp.मूल्य)) != TYPE_UNQUALIFIED))
    exp.मूल्य = require_complete_type (loc, exp.मूल्य);
  यदि (for_init || !RECORD_OR_UNION_TYPE_P (वृक्ष_TYPE (exp.मूल्य)))
    {
      वृक्ष init = maybe_get_constexpr_init (exp.मूल्य);
      यदि (init != NULL_वृक्ष)
	{
	  /* A named constant of pointer type or type nullptr_t is not
	     a null pointer constant even if the initializer is
	     one.  */
	  यदि (वृक्ष_CODE (init) == INTEGER_CST
	      && !INTEGRAL_TYPE_P (वृक्ष_TYPE (init))
	      && integer_zerop (init))
	    force_non_npc = सत्य;
	  exp.मूल्य = init;
	}
    }
  यदि (really_atomic_lvalue (exp.मूल्य))
    {
      vec<वृक्ष, va_gc> *params;
      वृक्ष nonatomic_type, tmp, tmp_addr, fndecl, func_call;
      वृक्ष व्यंजक_type = वृक्ष_TYPE (exp.मूल्य);
      वृक्ष व्यंजक_addr = build_unary_op (loc, ADDR_व्यंजक, exp.मूल्य, असत्य);
      वृक्ष seq_cst = build_int_cst (integer_type_गाँठ, MEMMODEL_SEQ_CST);

      gcc_assert (TYPE_ATOMIC (व्यंजक_type));

      /* Expansion of a generic atomic load may require an addition
	 element, so allocate enough to prevent a resize.  */
      vec_alloc (params, 4);

      /* Remove the qualifiers for the rest of the expressions and
	 create the VAL temp variable to hold the RHS.  */
      nonatomic_type = build_qualified_type (व्यंजक_type, TYPE_UNQUALIFIED);
      tmp = create_tmp_var_raw (nonatomic_type);
      tmp_addr = build_unary_op (loc, ADDR_व्यंजक, tmp, असत्य);
      वृक्ष_ADDRESSABLE (tmp) = 1;
      /* Do not disable warnings for TMP even though it's artificial.
	 -Winvalid-memory-model depends on it.  */

      /* Issue __atomic_load (&expr, &tmp, SEQ_CST);  */
      fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_LOAD);
      params->quick_धकेलो (व्यंजक_addr);
      params->quick_धकेलो (tmp_addr);
      params->quick_धकेलो (seq_cst);
      func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, रिक्त);

      /* EXPR is always read.  */
      mark_exp_read (exp.मूल्य);

      /* Optimize the common case where c_build_function_call_vec
	 immediately folds __atomic_load (&expr, &tmp, SEQ_CST); into
	 tmp = __atomic_load_<N> (&expr, SEQ_CST);
	 In that case tmp is not addressable and can be initialized
	 fully by the rhs of the MODIFY_EXPR.  */
      वृक्ष tem = func_call;
      यदि (CONVERT_व्यंजक_P (tem) && VOID_TYPE_P (वृक्ष_TYPE (tem)))
	{
	  tem = वृक्ष_OPERAND (tem, 0);
	  यदि (वृक्ष_CODE (tem) == MODIFY_व्यंजक
	      && वृक्ष_OPERAND (tem, 0) == tmp
	      && !walk_वृक्ष_without_duplicates (&वृक्ष_OPERAND (tem, 1),
						c_find_var_r, tmp))
	    {
	      वृक्ष_ADDRESSABLE (tmp) = 0;
	      func_call = वृक्ष_OPERAND (tem, 1);
	    }
	}

      /* Return tmp which contains the value loaded.  */
      exp.मूल्य = build4 (TARGET_व्यंजक, nonatomic_type, tmp, func_call,
			  NULL_वृक्ष, NULL_वृक्ष);
    }
  यदि (convert_p && !error_operand_p (exp.मूल्य)
      && (वृक्ष_CODE (वृक्ष_TYPE (exp.मूल्य)) != ARRAY_TYPE))
    exp.मूल्य = convert (build_qualified_type (वृक्ष_TYPE (exp.मूल्य), TYPE_UNQUALIFIED), exp.मूल्य);
  यदि (force_non_npc)
    exp.मूल्य = build1 (NOP_व्यंजक, वृक्ष_TYPE (exp.मूल्य), exp.मूल्य);

  {
    वृक्ष false_मूल्य, true_मूल्य;
    यदि (convert_p && !error_operand_p (exp.मूल्य)
	&& c_hardbool_type_attr (वृक्ष_TYPE (exp.मूल्य),
				 &false_मूल्य, &true_मूल्य))
      {
	वृक्ष t = save_व्यंजक (exp.मूल्य);

	mark_exp_read (exp.मूल्य);

	वृक्ष trapfn = builtin_decl_explicit (BUILT_IN_TRAP);
	वृक्ष व्यंजक = build_call_व्यंजक_loc (loc, trapfn, 0);
	व्यंजक = build_compound_व्यंजक (loc, व्यंजक, boolean_true_गाँठ);
	व्यंजक = fold_build3_loc (loc, COND_व्यंजक, boolean_type_गाँठ,
				fold_build2_loc (loc, NE_व्यंजक,
						 boolean_type_गाँठ,
						 t, true_मूल्य),
				व्यंजक, boolean_true_गाँठ);
	व्यंजक = fold_build3_loc (loc, COND_व्यंजक, boolean_type_गाँठ,
				fold_build2_loc (loc, NE_व्यंजक,
						 boolean_type_गाँठ,
						 t, false_मूल्य),
				व्यंजक, boolean_false_गाँठ);

	exp.मूल्य = व्यंजक;
      }
  }

  प्रत्यागम exp;
}

/* Wrapper for the overload above, same arguments but for tree rather than
   c_expr.  This is important for hardbools to decay to bools.  */

स्थिर अन्तःस्थ वृक्ष
convert_lvalue_to_rvalue (location_t loc, वृक्ष val,
			  तार्किक convert_p, तार्किक read_p, तार्किक for_init = असत्य)
{
  संरचना c_व्यंजक व्यंजक;
  स_रखो (&व्यंजक, 0, परिमाण (व्यंजक));
  व्यंजक.मूल्य = val;
  व्यंजक = convert_lvalue_to_rvalue (loc, व्यंजक, convert_p, read_p, for_init);
  प्रत्यागम व्यंजक.मूल्य;
}

/* EXP is an expression of integer type.  Apply the integer promotions
   to it and return the promoted value.  */

वृक्ष
perform_integral_promotions (वृक्ष exp)
{
  वृक्ष type = वृक्ष_TYPE (exp);
  गणना वृक्ष_code code = वृक्ष_CODE (type);

  gcc_assert (INTEGRAL_TYPE_P (type));

  /* Convert enums to the result of applying the integer promotions to
     their underlying type.  */
  यदि (code == ENUMERAL_TYPE)
    {
      type = ENUM_UNDERLYING_TYPE (type);
      यदि (c_promoting_integer_type_p (type))
	{
	  यदि (TYPE_UNSIGNED (type)
	      && TYPE_PRECISION (type) == TYPE_PRECISION (integer_type_गाँठ))
	    type = unsigned_type_गाँठ;
	  अन्यथा
	    type = integer_type_गाँठ;
	}

      प्रत्यागम convert (type, exp);
    }

  /* ??? This should no longer be needed now bit-fields have their
     proper types.  */
  यदि (वृक्ष_CODE (exp) == COMPONENT_REF
      && DECL_C_BIT_FIELD (वृक्ष_OPERAND (exp, 1)))
    {
      यदि (BITINT_TYPE_P (DECL_BIT_FIELD_TYPE (वृक्ष_OPERAND (exp, 1))))
	{
	  वृक्ष btype = DECL_BIT_FIELD_TYPE (वृक्ष_OPERAND (exp, 1));
	  यदि (वृक्ष_CODE (btype) == BITINT_TYPE)
	    प्रत्यागम convert (btype, exp);
	  अन्यथा
	    प्रत्यागम convert (ENUM_UNDERLYING_TYPE (btype), exp);
	}
      /* If it's thinner than an int, promote it like a
	 c_promoting_integer_type_p, otherwise leave it alone.  */
      यदि (compare_वृक्ष_int (DECL_SIZE (वृक्ष_OPERAND (exp, 1)),
			    TYPE_PRECISION (integer_type_गाँठ)) < 0)
	प्रत्यागम convert (integer_type_गाँठ, exp);
    }

  यदि (c_promoting_integer_type_p (type))
    {
      /* Preserve unsignedness if not really getting any wider.  */
      यदि (TYPE_UNSIGNED (type)
	  && TYPE_PRECISION (type) == TYPE_PRECISION (integer_type_गाँठ))
	प्रत्यागम convert (unsigned_type_गाँठ, exp);

      प्रत्यागम convert (integer_type_गाँठ, exp);
    }

  प्रत्यागम exp;
}


/* Perform default promotions for C data used in expressions.
   Enumeral types or short or char are converted to int.
   In addition, manifest constants symbols are replaced by their values.  */

वृक्ष
default_conversion (वृक्ष exp)
{
  वृक्ष orig_exp;
  वृक्ष type = वृक्ष_TYPE (exp);
  गणना वृक्ष_code code = वृक्ष_CODE (type);
  वृक्ष promoted_type;

  mark_exp_read (exp);
  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  यदि (वृक्ष_CODE (exp) == COMPONENT_REF
      && handle_counted_by_p (exp))
    exp = handle_counted_by_for_component_ref (व्यंजक_LOCATION (exp), exp);

  /* Functions and arrays have been converted during parsing.  */
  gcc_assert (code != FUNCTION_TYPE);
  यदि (code == ARRAY_TYPE)
    प्रत्यागम exp;

  /* Constants can be used directly unless they're not loadable.  */
  यदि (वृक्ष_CODE (exp) == CONST_DECL)
    exp = DECL_INITIAL (exp);

  /* Strip no-op conversions.  */
  orig_exp = exp;
  STRIP_TYPE_NOPS (exp);

  copy_warning (exp, orig_exp);

  यदि (code == VOID_TYPE)
    {
      error_at (व्यंजक_LOC_OR_LOC (exp, निवेश_location),
		"void value not ignored as it ought to be");
      प्रत्यागम error_mark_गाँठ;
    }

  exp = require_complete_type (व्यंजक_LOC_OR_LOC (exp, निवेश_location), exp);
  यदि (exp == error_mark_गाँठ)
    प्रत्यागम error_mark_गाँठ;

  promoted_type = targetm.promoted_type (type);
  यदि (promoted_type)
    प्रत्यागम convert (promoted_type, exp);

  यदि (INTEGRAL_TYPE_P (type))
    {
      /* Avoid performing integral promotion of bit-precise integer
	 type bit-field to its corresponding bit-precise integer if
	 orig_exp is a cast to it to its underlying type.  */
      यदि (orig_exp != exp
	  && वृक्ष_CODE (exp) == COMPONENT_REF
	  && DECL_C_BIT_FIELD (वृक्ष_OPERAND (exp, 1))
	  && BITINT_TYPE_P (DECL_BIT_FIELD_TYPE (वृक्ष_OPERAND (exp, 1))))
	प्रत्यागम perform_integral_promotions (orig_exp);
      प्रत्यागम perform_integral_promotions (exp);
    }

  प्रत्यागम exp;
}

/* Look up COMPONENT in a structure or union TYPE.

   If the component name is not found, returns NULL_TREE.  Otherwise,
   the return value is a TREE_LIST, with each TREE_VALUE a FIELD_DECL
   stepping down the chain to the component, which is in the last
   TREE_VALUE of the list.  Normally the list is of length one, but if
   the component is embedded within (nested) anonymous structures or
   unions, the list steps down the chain to the component.  */

वृक्ष
lookup_field (const_वृक्ष type, वृक्ष component)
{
  वृक्ष field;

  /* If TYPE_LANG_SPECIFIC is set, then it is a sorted array of pointers
     to the field elements.  Use a binary search on this array to quickly
     find the element.  Otherwise, do a linear search.  TYPE_LANG_SPECIFIC
     will always be set for structures which have many elements.

     Duplicate field checking replaces duplicates with NULL_TREE so
     TYPE_LANG_SPECIFIC arrays are potentially no longer sorted.  In that
     case just iterate using DECL_CHAIN.  */

  यदि (TYPE_LANG_SPECIFIC (type) && TYPE_LANG_SPECIFIC (type)->s
      && !seen_error ())
    {
      पूर्णाङ्क bot, शीर्ष, half;
      वृक्ष *field_array = &TYPE_LANG_SPECIFIC (type)->s->elts[0];

      field = TYPE_FIELDS (type);
      bot = 0;
      शीर्ष = TYPE_LANG_SPECIFIC (type)->s->len;
      यावत् (शीर्ष - bot > 1)
	{
	  half = (शीर्ष - bot + 1) >> 1;
	  field = field_array[bot+half];

	  यदि (DECL_NAME (field) == NULL_वृक्ष)
	    {
	      /* Step through all anon unions in linear fashion.  */
	      यावत् (DECL_NAME (field_array[bot]) == NULL_वृक्ष)
		{
		  field = field_array[bot++];
		  यदि (RECORD_OR_UNION_TYPE_P (वृक्ष_TYPE (field)))
		    {
		      वृक्ष anon = lookup_field (वृक्ष_TYPE (field), component);

		      यदि (anon)
			प्रत्यागम वृक्ष_cons (NULL_वृक्ष, field, anon);

		      /* The Plan 9 compiler permits referring
			 directly to an anonymous struct/union field
			 using a typedef name.  */
		      यदि (flag_plan9_extensions
			  && TYPE_NAME (वृक्ष_TYPE (field)) != NULL_वृक्ष
			  && (वृक्ष_CODE (TYPE_NAME (वृक्ष_TYPE (field)))
			      == TYPE_DECL)
			  && (DECL_NAME (TYPE_NAME (वृक्ष_TYPE (field)))
			      == component))
			भङ्ग;
		    }
		}

	      /* Entire record is only anon unions.  */
	      यदि (bot > शीर्ष)
		प्रत्यागम NULL_वृक्ष;

	      /* Restart the binary search, with new lower bound.  */
	      अनुवर्त;
	    }

	  यदि (DECL_NAME (field) == component)
	    भङ्ग;
	  यदि (DECL_NAME (field) < component)
	    bot += half;
	  अन्यथा
	    शीर्ष = bot + half;
	}

      यदि (DECL_NAME (field_array[bot]) == component)
	field = field_array[bot];
      अन्यथा यदि (DECL_NAME (field) != component)
	प्रत्यागम NULL_वृक्ष;
    }
  अन्यथा
    {
      प्रति (field = TYPE_FIELDS (type); field; field = DECL_CHAIN (field))
	{
	  यदि (DECL_NAME (field) == NULL_वृक्ष
	      && RECORD_OR_UNION_TYPE_P (वृक्ष_TYPE (field)))
	    {
	      वृक्ष anon = lookup_field (वृक्ष_TYPE (field), component);

	      यदि (anon)
		प्रत्यागम वृक्ष_cons (NULL_वृक्ष, field, anon);

	      /* The Plan 9 compiler permits referring directly to an
		 anonymous struct/union field using a typedef
		 name.  */
	      यदि (flag_plan9_extensions
		  && TYPE_NAME (वृक्ष_TYPE (field)) != NULL_वृक्ष
		  && वृक्ष_CODE (TYPE_NAME (वृक्ष_TYPE (field))) == TYPE_DECL
		  && (DECL_NAME (TYPE_NAME (वृक्ष_TYPE (field)))
		      == component))
		भङ्ग;
	    }

	  यदि (DECL_NAME (field) == component)
	    भङ्ग;
	}

      यदि (field == NULL_वृक्ष)
	प्रत्यागम NULL_वृक्ष;
    }

  प्रत्यागम वृक्ष_cons (NULL_वृक्ष, field, NULL_वृक्ष);
}

/* Recursively append candidate IDENTIFIER_NODEs to CANDIDATES.  */

स्थिर शून्य
lookup_field_fuzzy_find_candidates (वृक्ष type, वृक्ष component,
				    vec<वृक्ष> *candidates)
{
  वृक्ष field;
  प्रति (field = TYPE_FIELDS (type); field; field = DECL_CHAIN (field))
    {
      यदि (DECL_NAME (field) == NULL_वृक्ष
	  && RECORD_OR_UNION_TYPE_P (वृक्ष_TYPE (field)))
	lookup_field_fuzzy_find_candidates (वृक्ष_TYPE (field), component,
					    candidates);

      यदि (DECL_NAME (field))
	candidates->safe_धकेलो (DECL_NAME (field));
    }
}

/* Like "lookup_field", but find the closest matching IDENTIFIER_NODE,
   rather than returning a TREE_LIST for an exact match.  */

स्थिर वृक्ष
lookup_field_fuzzy (वृक्ष type, वृक्ष component)
{
  gcc_assert (वृक्ष_CODE (component) == IDENTIFIER_गाँठ);

  /* First, gather a list of candidates.  */
  auto_vec <वृक्ष> candidates;

  lookup_field_fuzzy_find_candidates (type, component,
				      &candidates);

  प्रत्यागम find_closest_identifier (component, &candidates);
}

/* Support function for build_component_ref's error-handling.

   Given DATUM_TYPE, and "DATUM.COMPONENT", where DATUM is *not* a
   struct or union, should we suggest "DATUM->COMPONENT" as a hint?  */

स्थिर तार्किक
should_suggest_deref_p (वृक्ष datum_type)
{
  /* We don't do it for Objective-C, since Objective-C 2.0 dot-syntax
     allows "." for ptrs; we could be handling a failed attempt
     to access a property.  */
  यदि (c_dialect_objc ())
    प्रत्यागम असत्य;

  /* Only suggest it for pointers...  */
  यदि (वृक्ष_CODE (datum_type) != POINTER_TYPE)
    प्रत्यागम असत्य;

  /* ...to structs/unions.  */
  वृक्ष underlying_type = वृक्ष_TYPE (datum_type);
  गणना वृक्ष_code code = वृक्ष_CODE (underlying_type);
  यदि (code == RECORD_TYPE || code == UNION_TYPE)
    प्रत्यागम सत्य;
  अन्यथा
    प्रत्यागम असत्य;
}

/* Give a component ref REF, decide whether we should handle its counted_by
   attribute based on its context:
   Do not handle counted_by when in offsetof, typeof and alignof operator.  */

स्थिर तार्किक
handle_counted_by_p (वृक्ष ref)
{
  gcc_assert (वृक्ष_CODE (ref) == COMPONENT_REF);
  वृक्ष datum = वृक्ष_OPERAND (ref, 0);
  /* If the component_ref is build for a offsetof, i.e., the datum
     of the component_ref is a indirect_ref of null_pointer_node,
     we should not generate call to .ACCESS_WITH_SIZE.  */
  यदि (वृक्ष_CODE (datum) == INDIRECT_REF
      && वृक्ष_OPERAND (datum, 0) == null_pointer_गाँठ)
    प्रत्यागम असत्य;
  यदि (in_typeof || in_alignof)
    प्रत्यागम असत्य;
  प्रत्यागम सत्य;
}

/* Given a component ref REF, if there is a counted_by attribute attached,
   issue error when the element_type is a structure or union including a
   flexible array member.  */

स्थिर शून्य
check_counted_by_attribute (location_t loc, वृक्ष ref)
{
  वृक्ष subdatum = वृक्ष_OPERAND (ref, 1);
  वृक्ष sub_type = वृक्ष_TYPE (subdatum);

  यदि (!flexible_array_member_type_p (sub_type)
      && वृक्ष_CODE (sub_type) != POINTER_TYPE)
    प्रत्यागम;

  वृक्ष element_type = वृक्ष_TYPE (sub_type);

  वृक्ष attr_counted_by = lookup_attribute ("counted_by",
					   DECL_ATTRIBUTES (subdatum));
  यदि (attr_counted_by)
    {
      /* Issue error when the element_type is a structure or
	union including a flexible array member.  */
      यदि (RECORD_OR_UNION_TYPE_P (element_type)
	  && TYPE_INCLUDES_FLEXARRAY (element_type))
	{
	  error_at (loc,
		    "%<counted_by%> attribute is not allowed for a pointer to"
		    " structure or union with flexible array member");
	  प्रत्यागम;
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

स्थिर वृक्ष
build_counted_by_ref (वृक्ष datum, वृक्ष subdatum,
		      वृक्ष *counted_by_type)
{
  वृक्ष sub_type = वृक्ष_TYPE (subdatum);
  यदि (!flexible_array_member_type_p (sub_type)
      && वृक्ष_CODE (sub_type) != POINTER_TYPE)
    प्रत्यागम NULL_वृक्ष;

  वृक्ष attr_counted_by = lookup_attribute ("counted_by",
					   DECL_ATTRIBUTES (subdatum));
  यदि (!attr_counted_by)
    प्रत्यागम NULL_वृक्ष;

  वृक्ष counted_by_ref = NULL_वृक्ष;
  *counted_by_type = NULL_वृक्ष;

  वृक्ष type = वृक्ष_TYPE (datum);

  /* If the type of the containing structure is an anonymous struct/union,
     and this anonymous struct/union is not a root type, get the first
     outer named structure/union type.  */
  यावत् (वृक्ष_CODE (datum) == COMPONENT_REF
	 && c_type_tag (type) == NULL_वृक्ष
	 && DECL_NAME (वृक्ष_OPERAND (datum, 1)) == NULL_वृक्ष)
    {
      datum = वृक्ष_OPERAND (datum, 0);
      type = वृक्ष_TYPE (datum);
    }

  वृक्ष field_id = वृक्ष_मूल्य (वृक्ष_मूल्य (attr_counted_by));
  वृक्ष counted_by_field = lookup_field (type, field_id);
  gcc_assert (counted_by_field);

  वृक्ष counted_by_subdatum;
  कुरु
    {
      counted_by_subdatum = वृक्ष_मूल्य (counted_by_field);
      /* Get the TYPE of the counted_by field.  */
      *counted_by_type = वृक्ष_TYPE (counted_by_subdatum);

      counted_by_ref
	= build3 (COMPONENT_REF, वृक्ष_TYPE (counted_by_subdatum),
		  datum, counted_by_subdatum, NULL_वृक्ष);

      datum = counted_by_ref;
      counted_by_field = वृक्ष_CHAIN (counted_by_field);
    }
  यावत् (counted_by_field);

  counted_by_ref = build_fold_addr_व्यंजक (counted_by_ref);
  प्रत्यागम counted_by_ref;
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
स्थिर वृक्ष
build_access_with_size_for_counted_by (location_t loc, वृक्ष ref,
				       वृक्ष counted_by_ref,
				       वृक्ष counted_by_type)
{
  gcc_assert (flexible_array_member_type_p (वृक्ष_TYPE (ref))
	      || वृक्ष_CODE (वृक्ष_TYPE (ref)) == POINTER_TYPE);

  तार्किक is_fam = flexible_array_member_type_p (वृक्ष_TYPE (ref));

  /* The result type of the call is a pointer to the flexible array type;
     or is the original pointer type to the pointer field with counted_by.  */
  वृक्ष result_type = is_fam ? c_build_pointer_type (वृक्ष_TYPE (ref))
		     : वृक्ष_TYPE (ref);

  वृक्ष element_type = वृक्ष_TYPE (वृक्ष_TYPE (ref));
  वृक्ष element_size = VOID_TYPE_P (element_type)
		      ? size_one_गाँठ
		      : TYPE_SIZE_UNIT (element_type);
  यदि (element_size == NULL_वृक्ष)
    प्रत्यागम ref;

  वृक्ष first_param = is_fam
		     ? c_fully_fold (array_to_pointer_conversion (loc, ref),
				     असत्य, रिक्त)
		     : c_fully_fold (ref, असत्य, रिक्त);
  वृक्ष second_param
    = c_fully_fold (counted_by_ref, असत्य, रिक्त);
  वृक्ष third_param = build_int_cst (c_build_pointer_type (counted_by_type), 0);

  वृक्ष call
    = build_call_व्यंजक_internal_loc (loc, IFN_ACCESS_WITH_SIZE,
				    result_type, 4,
				    first_param,
				    second_param,
				    third_param,
				    element_size);

  /* Wrap the call with an INDIRECT_REF with the flexible array type.  */
  यदि (is_fam)
    call = build1 (INDIRECT_REF, वृक्ष_TYPE (ref), call);
  SET_व्यंजक_LOCATION (call, loc);
  प्रत्यागम call;
}

/* For the COMPONENT_REF ref, check whether it has a counted_by attribute,
   if so, wrap this COMPONENT_REF with the corresponding CALL to the
   function .ACCESS_WITH_SIZE.
   Otherwise, return the ref itself.  */

वृक्ष
handle_counted_by_for_component_ref (location_t loc, वृक्ष ref)
{
  gcc_assert (वृक्ष_CODE (ref) == COMPONENT_REF);
  वृक्ष datum = वृक्ष_OPERAND (ref, 0);
  वृक्ष subdatum = वृक्ष_OPERAND (ref, 1);
  वृक्ष counted_by_type = NULL_वृक्ष;

  यदि (!(flexible_array_member_type_p (वृक्ष_TYPE (ref))
	|| वृक्ष_CODE (वृक्ष_TYPE (ref)) == POINTER_TYPE))
    प्रत्यागम ref;

  वृक्ष counted_by_ref = build_counted_by_ref (datum, subdatum,
					      &counted_by_type);
  यदि (counted_by_ref)
    ref = build_access_with_size_for_counted_by (loc, ref,
						 counted_by_ref,
						 counted_by_type);
  प्रत्यागम ref;
}

/* Make an expression to refer to the COMPONENT field of structure or
   union value DATUM.  COMPONENT is an IDENTIFIER_NODE.  LOC is the
   location of the COMPONENT_REF.  COMPONENT_LOC is the location
   of COMPONENT.  ARROW_LOC is the location of the first -> operand if
   it is from -> operator.
   If HANDLE_COUNTED_BY is true, check the counted_by attribute and generate
   a call to .ACCESS_WITH_SIZE.  Otherwise, ignore the attribute.  */

वृक्ष
build_component_ref (location_t loc, वृक्ष datum, वृक्ष component,
		     location_t component_loc, location_t arrow_loc)
{
  वृक्ष type = वृक्ष_TYPE (datum);
  गणना वृक्ष_code code = वृक्ष_CODE (type);
  वृक्ष field = रिक्त;
  वृक्ष ref;
  तार्किक datum_lvalue = lvalue_p (datum);

  यदि (!objc_is_public (datum, component))
    प्रत्यागम error_mark_गाँठ;

  /* Detect Objective-C property syntax object.property.  */
  यदि (c_dialect_objc ()
      && (ref = objc_maybe_build_component_ref (datum, component)))
    प्रत्यागम ref;

  /* See if there is a field or component with name COMPONENT.  */

  यदि (code == RECORD_TYPE || code == UNION_TYPE)
    {
      यदि (!COMPLETE_TYPE_P (type))
	{
	  c_incomplete_type_error (loc, NULL_वृक्ष, type);
	  प्रत्यागम error_mark_गाँठ;
	}

      field = lookup_field (type, component);

      यदि (!field)
	{
	  वृक्ष guessed_id = lookup_field_fuzzy (type, component);
	  यदि (guessed_id)
	    {
	      /* Attempt to provide a fixit replacement hint, if
		 we have a valid range for the component.  */
	      location_t reported_loc
		= (component_loc != UNKNOWN_LOCATION) ? component_loc : loc;
	      gcc_rich_location rich_loc (reported_loc);
	      यदि (component_loc != UNKNOWN_LOCATION)
		rich_loc.add_fixit_misspelled_id (component_loc, guessed_id);
	      error_at (&rich_loc,
			"%qT has no member named %qE; did you mean %qE?",
			type, component, guessed_id);
	    }
	  अन्यथा
	    error_at (loc, "%qT has no member named %qE", type, component);
	  प्रत्यागम error_mark_गाँठ;
	}

      /* Accessing elements of atomic structures or unions is undefined
	 behavior (C11 6.5.2.3#5).  */
      यदि (TYPE_ATOMIC (type) && c_inhibit_evaluation_warnings == 0)
	{
	  यदि (code == RECORD_TYPE)
	    warning_at (loc, 0, "accessing a member %qE of an atomic "
			"structure %qE", component, datum);
	  अन्यथा
	    warning_at (loc, 0, "accessing a member %qE of an atomic "
			"union %qE", component, datum);
	}

      /* Chain the COMPONENT_REFs if necessary down to the FIELD.
	 This might be better solved in future the way the C++ front
	 end does it - by giving the anonymous entities each a
	 separate name and type, and then have build_component_ref
	 recursively call itself.  We can't do that here.  */
      कुरु
	{
	  वृक्ष subdatum = वृक्ष_मूल्य (field);
	  पूर्णाङ्क quals;
	  वृक्ष subtype;
	  तार्किक use_datum_quals;

	  यदि (वृक्ष_TYPE (subdatum) == error_mark_गाँठ)
	    प्रत्यागम error_mark_गाँठ;

	  /* If this is an rvalue, it does not have qualifiers in C
	     standard terms and we must avoid propagating such
	     qualifiers down to a non-lvalue array that is then
	     converted to a pointer.  */
	  use_datum_quals = (datum_lvalue
			     || वृक्ष_CODE (वृक्ष_TYPE (subdatum)) != ARRAY_TYPE);

	  quals = TYPE_QUALS (strip_array_types (वृक्ष_TYPE (subdatum)));
	  यदि (use_datum_quals)
	    quals |= TYPE_QUALS (वृक्ष_TYPE (datum));
	  subtype = c_build_qualified_type (वृक्ष_TYPE (subdatum), quals);

	  ref = build3 (COMPONENT_REF, subtype, datum, subdatum,
			NULL_वृक्ष);
	  SET_व्यंजक_LOCATION (ref, loc);

	  check_counted_by_attribute (loc, ref);

	  यदि (वृक्ष_READONLY (subdatum)
	      || (use_datum_quals && वृक्ष_READONLY (datum)))
	    वृक्ष_READONLY (ref) = 1;
	  यदि (वृक्ष_THIS_VOLATILE (subdatum)
	      || (use_datum_quals && वृक्ष_THIS_VOLATILE (datum)))
	    वृक्ष_THIS_VOLATILE (ref) = 1;

	  यदि (वृक्ष_UNAVAILABLE (subdatum))
	    error_unavailable_use (subdatum, NULL_वृक्ष);
	  अन्यथा यदि (वृक्ष_DEPRECATED (subdatum))
	    warn_deprecated_use (subdatum, NULL_वृक्ष);

	  datum = ref;

	  field = वृक्ष_CHAIN (field);
	}
      यावत् (field);

      प्रत्यागम ref;
    }
  अन्यथा यदि (should_suggest_deref_p (type))
    {
      /* Special-case the error message for "ptr.field" for the case
	 where the user has confused "." vs "->".  */
      rich_location richloc (पंक्ति_table, loc);
      यदि (INDIRECT_REF_P (datum) && arrow_loc != UNKNOWN_LOCATION)
	{
	  richloc.add_fixit_जोड़ो_before (arrow_loc, "(*");
	  richloc.add_fixit_जोड़ो_after (arrow_loc, ")");
	  error_at (&richloc,
		    "%qE is a pointer to pointer; did you mean to dereference "
		    "it before applying %<->%> to it?",
		    वृक्ष_OPERAND (datum, 0));
	}
      अन्यथा
	{
	  /* "loc" should be the "." token.  */
	  richloc.add_fixit_replace ("->");
	  error_at (&richloc,
		    "%qE is a pointer; did you mean to use %<->%>?",
		    datum);
	}
      प्रत्यागम error_mark_गाँठ;
    }
  अन्यथा यदि (code != ERROR_MARK)
    error_at (loc,
	      "request for member %qE in something not a structure or union",
	      component);

  प्रत्यागम error_mark_गाँठ;
}

/* Given an expression PTR for a pointer, return an expression
   for the value pointed to.
   ERRORSTRING is the name of the operator to appear in error messages.

   LOC is the location to use for the generated tree.  */

वृक्ष
build_indirect_ref (location_t loc, वृक्ष ptr, ref_operator errstring)
{
  वृक्ष pointer = default_conversion (ptr);
  वृक्ष type = वृक्ष_TYPE (pointer);
  वृक्ष ref;

  यदि (वृक्ष_CODE (type) == POINTER_TYPE)
    {
      यदि (CONVERT_व्यंजक_P (pointer)
          || वृक्ष_CODE (pointer) == VIEW_CONVERT_व्यंजक)
	{
	  /* If a warning is issued, mark it to avoid duplicates from
	     the backend.  This only needs to be done at
	     warn_strict_aliasing > 2.  */
	  यदि (warn_strict_aliasing > 2)
	    यदि (strict_aliasing_warning (व्यंजक_LOCATION (pointer),
					 type, वृक्ष_OPERAND (pointer, 0)))
	      suppress_warning (pointer, OPT_Wstrict_aliasing_);
	}

      यदि (वृक्ष_CODE (pointer) == ADDR_व्यंजक
	  && (वृक्ष_TYPE (वृक्ष_OPERAND (pointer, 0))
	      == वृक्ष_TYPE (type)))
	{
	  ref = वृक्ष_OPERAND (pointer, 0);
	  protected_set_व्यंजक_location (ref, loc);
	  प्रत्यागम ref;
	}
      अन्यथा
	{
	  वृक्ष t = वृक्ष_TYPE (type);

	  ref = build1 (INDIRECT_REF, t, pointer);

	  यदि (VOID_TYPE_P (t) && c_inhibit_evaluation_warnings == 0)
	    warning_at (loc, 0, "dereferencing %<void *%> pointer");

	  /* We *must* set TREE_READONLY when dereferencing a pointer to const,
	     so that we get the proper error message if the result is used
	     to assign to.  Also, &* is supposed to be a no-op.
	     And ANSI C seems to specify that the type of the result
	     should be the const type.  */
	  /* A de-reference of a pointer to const is not a const.  It is valid
	     to change it via some other pointer.  */
	  वृक्ष_READONLY (ref) = TYPE_READONLY (t);
	  वृक्ष_SIDE_EFFECTS (ref)
	    = TYPE_VOLATILE (t) || वृक्ष_SIDE_EFFECTS (pointer);
	  वृक्ष_THIS_VOLATILE (ref) = TYPE_VOLATILE (t);
	  protected_set_व्यंजक_location (ref, loc);
	  प्रत्यागम ref;
	}
    }
  अन्यथा यदि (वृक्ष_CODE (pointer) != ERROR_MARK)
    invalid_indirection_error (loc, type, errstring);

  प्रत्यागम error_mark_गाँठ;
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

वृक्ष
build_array_ref (location_t loc, वृक्ष array, वृक्ष index)
{
  वृक्ष ret;
  तार्किक swapped = असत्य;
  यदि (वृक्ष_TYPE (array) == error_mark_गाँठ
      || वृक्ष_TYPE (index) == error_mark_गाँठ)
    प्रत्यागम error_mark_गाँठ;

  यदि (वृक्ष_CODE (वृक्ष_TYPE (array)) != ARRAY_TYPE
      && वृक्ष_CODE (वृक्ष_TYPE (array)) != POINTER_TYPE
      /* Allow vector[index] but not index[vector].  */
      && !gnu_vector_type_p (वृक्ष_TYPE (array)))
    {
      यदि (वृक्ष_CODE (वृक्ष_TYPE (index)) != ARRAY_TYPE
	  && वृक्ष_CODE (वृक्ष_TYPE (index)) != POINTER_TYPE)
	{
          error_at (loc,
            "subscripted value is neither array nor pointer nor vector");

	  प्रत्यागम error_mark_गाँठ;
	}
      std::swap (array, index);
      swapped = सत्य;
    }

  यदि (!INTEGRAL_TYPE_P (वृक्ष_TYPE (index)))
    {
      error_at (loc, "array subscript is not an integer");
      प्रत्यागम error_mark_गाँठ;
    }

  यदि (वृक्ष_CODE (वृक्ष_TYPE (वृक्ष_TYPE (array))) == FUNCTION_TYPE)
    {
      error_at (loc, "subscripted value is pointer to function");
      प्रत्यागम error_mark_गाँठ;
    }

  /* ??? Existing practice has been to warn only when the char
     index is syntactically the index, not for char[array].  */
  यदि (!swapped)
     warn_array_subscript_with_type_char (loc, index);

  /* Apply default promotions *after* noticing character types.  */
  index = default_conversion (index);
  यदि (index == error_mark_गाँठ)
    प्रत्यागम error_mark_गाँठ;

  gcc_assert (वृक्ष_CODE (वृक्ष_TYPE (index)) == INTEGER_TYPE
	      || वृक्ष_CODE (वृक्ष_TYPE (index)) == BITINT_TYPE);

  तार्किक was_vector = VECTOR_TYPE_P (वृक्ष_TYPE (array));
  तार्किक non_lvalue = convert_vector_to_array_for_subscript (loc, &array, index);

  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  यदि (वृक्ष_CODE (array) == COMPONENT_REF
      && handle_counted_by_p (array))
    array = handle_counted_by_for_component_ref (loc, array);

  यदि (वृक्ष_CODE (वृक्ष_TYPE (array)) == ARRAY_TYPE)
    {
      वृक्ष rval, type;

      /* An array that is indexed by a non-constant
	 cannot be stored in a register; we must be able to do
	 address arithmetic on its address.
	 Likewise an array of elements of variable size.  */
      यदि (वृक्ष_CODE (index) != INTEGER_CST
	  || (COMPLETE_TYPE_P (वृक्ष_TYPE (वृक्ष_TYPE (array)))
	      && वृक्ष_CODE (TYPE_SIZE (वृक्ष_TYPE (वृक्ष_TYPE (array)))) != INTEGER_CST))
	{
	  यदि (!c_mark_addressable (array, सत्य, सत्य))
	    प्रत्यागम error_mark_गाँठ;
	}
      /* An array that is indexed by a constant value which is not within
	 the array bounds cannot be stored in a register either; because we
	 would get a crash in store_bit_field/extract_bit_field when trying
	 to access a non-existent part of the register.  */
      यदि (वृक्ष_CODE (index) == INTEGER_CST
	  && TYPE_DOMAIN (वृक्ष_TYPE (array))
	  && !int_fits_type_p (index, TYPE_DOMAIN (वृक्ष_TYPE (array))))
	{
	  यदि (!c_mark_addressable (array, असत्य, सत्य))
	    प्रत्यागम error_mark_गाँठ;
	  /* ISO C2Y disallows a negative integer constant expression index
	     when array subscripting has an operand of array type.  */
	  यदि (flag_isoc2y
	      && !वृक्ष_OVERFLOW (index)
	      && वृक्ष_int_cst_sgn (index) < 0)
	    error_at (loc, "array subscript is negative");
	}

      यदि ((pedantic || warn_c90_c99_compat || warn_c23_c2y_compat)
	  && ! was_vector)
	{
	  वृक्ष foo = array;
	  यावत् (वृक्ष_CODE (foo) == COMPONENT_REF)
	    foo = वृक्ष_OPERAND (foo, 0);
	  यदि ((VAR_P (foo) && C_DECL_REGISTER (foo))
	      || (वृक्ष_CODE (foo) == COMPOUND_LITERAL_व्यंजक
		  && C_DECL_REGISTER (COMPOUND_LITERAL_व्यंजक_DECL (foo))))
	    pedwarn_c23 (loc, OPT_Wpedantic,
			 "ISO C forbids subscripting %<register%> array "
			 "before C2Y");
	  अन्यथा यदि (!lvalue_p (foo))
	    pedwarn_c90 (loc, OPT_Wpedantic,
			 "ISO C90 forbids subscripting non-lvalue "
			 "array");
	}

      यदि (वृक्ष_CODE (वृक्ष_TYPE (index)) == BITINT_TYPE
	  && TYPE_PRECISION (वृक्ष_TYPE (index)) > TYPE_PRECISION (sizetype))
	index = fold_convert (sizetype, index);

      type = वृक्ष_TYPE (वृक्ष_TYPE (array));
      rval = build4 (ARRAY_REF, type, array, index, NULL_वृक्ष, NULL_वृक्ष);
      /* Array ref is const/volatile if the array elements are
	 or if the array is.  */
      वृक्ष_READONLY (rval)
	|= (TYPE_READONLY (वृक्ष_TYPE (वृक्ष_TYPE (array)))
	    | वृक्ष_READONLY (array));
      वृक्ष_SIDE_EFFECTS (rval)
	|= (TYPE_VOLATILE (वृक्ष_TYPE (वृक्ष_TYPE (array)))
	    | वृक्ष_SIDE_EFFECTS (array));
      वृक्ष_THIS_VOLATILE (rval)
	|= (TYPE_VOLATILE (वृक्ष_TYPE (वृक्ष_TYPE (array)))
	    /* This was added by rms on 16 Nov 91.
	       It fixes  vol struct foo *a;  a->elts[1]
	       in an inline function.
	       Hope it doesn't break something else.  */
	    | वृक्ष_THIS_VOLATILE (array));
      ret = require_complete_type (loc, rval);
      protected_set_व्यंजक_location (ret, loc);
      यदि (non_lvalue)
	ret = non_lvalue_loc (loc, ret);
      प्रत्यागम ret;
    }
  अन्यथा
    {
      वृक्ष ar = default_conversion (array);

      यदि (ar == error_mark_गाँठ)
	प्रत्यागम ar;

      gcc_assert (वृक्ष_CODE (वृक्ष_TYPE (ar)) == POINTER_TYPE);
      gcc_assert (वृक्ष_CODE (वृक्ष_TYPE (वृक्ष_TYPE (ar))) != FUNCTION_TYPE);

      ret = build_indirect_ref (loc, build_द्विआधारी_op (loc, PLUS_व्यंजक, ar,
						      index, असत्य),
				RO_ARRAY_INDEXING);
      यदि (non_lvalue)
	ret = non_lvalue_loc (loc, ret);
      प्रत्यागम ret;
    }
}

/* Build an OpenMP array section reference, creating an exact type for the
   resulting expression based on the element type and bounds if possible.  If
   we have variable bounds, create an incomplete array type for the result
   instead.  */

वृक्ष
build_omp_array_section (location_t loc, वृक्ष array, वृक्ष index, वृक्ष length)
{
  वृक्ष type = वृक्ष_TYPE (array);
  gcc_assert (type);

  वृक्ष sectype, eltype = वृक्ष_TYPE (type);

  /* It's not an array or pointer type.  Just reuse the type of the original
     expression as the type of the array section (an error will be raised
     anyway, later).  */
  यदि (eltype == NULL_वृक्ष || error_operand_p (eltype))
    sectype = वृक्ष_TYPE (array);
  अन्यथा
    {
      वृक्ष idxtype = NULL_वृक्ष;

      यदि (index != NULL_वृक्ष
	  && length != NULL_वृक्ष
	  && INTEGRAL_TYPE_P (वृक्ष_TYPE (index))
	  && INTEGRAL_TYPE_P (वृक्ष_TYPE (length)))
	{
	  वृक्ष निचला = fold_convert (sizetype, index);
	  वृक्ष ऊपरी = fold_convert (sizetype, length);
	  ऊपरी = size_binop (PLUS_व्यंजक, निचला, ऊपरी);
	  ऊपरी = size_binop (MINUS_व्यंजक, ऊपरी, size_one_गाँठ);
	  idxtype = build_range_type (sizetype, निचला, ऊपरी);
	}
      अन्यथा यदि ((index == NULL_वृक्ष || integer_zerop (index))
	       && length != NULL_वृक्ष
	       && INTEGRAL_TYPE_P (वृक्ष_TYPE (length)))
	idxtype = build_index_type (length);

      gcc_assert (!error_operand_p (idxtype));

      sectype = c_build_array_type (eltype, idxtype);
    }

  प्रत्यागम build3_loc (loc, OMP_ARRAY_SECTION, sectype, array, index, length);
}


/* Record that REF is used.  This is relevant for undeclared static
   function and declarations referenced from a non-local context.
   ADDRESS indicates whether the address is taken.  */

शून्य
mark_decl_used (वृक्ष ref, तार्किक address)
{
  यदि (!ref || !DECL_P (ref) || in_alignof)
    प्रत्यागम;

  /* Non-file-scope and non-local reference in nested function.  */
  तार्किक nonloc_p = current_function_decl && DECL_CONTEXT (ref)
		  && DECL_CONTEXT (current_function_decl)
		  && DECL_CONTEXT (ref) != current_function_decl;

  /* An undeclared static function.  */
  तार्किक static_p = वृक्ष_CODE (ref) == FUNCTION_DECL
		  && DECL_INITIAL (ref) == NULL_वृक्ष
		  && DECL_EXTERNAL (ref)
		  && !वृक्ष_PUBLIC (ref);

  यदि (!static_p && !nonloc_p)
    प्रत्यागम;

  /* If we may be in an unevaluated context, delay the decision.  */
  यदि (in_sizeof || in_typeof || in_countof || in_generic)
    प्रत्यागम record_maybe_used_decl (ref, address);

  यदि (static_p)
    C_DECL_USED (ref) = 1;

  यदि (nonloc_p && (VAR_OR_FUNCTION_DECL_P (ref)
		   || वृक्ष_CODE (ref) == PARM_DECL))
    DECL_NONLOCAL (ref) = 1;

  /* Nothing to do anymore.  */
  यदि (!nonloc_p || C_FUNC_NONLOCAL_CONTEXT (current_function_decl))
    प्रत्यागम;

  /* Filter out the cases where referencing a non-local variable does not
     require a non-local context passed via the static chain.  */
  यदि (!c_type_variably_modified_p (वृक्ष_TYPE (ref)))
    विकल्प (वृक्ष_CODE (ref))
      {
      पक्ष FUNCTION_DECL:
	/* Use of another local function that requires no context is ok.  */
	यदि (!C_FUNC_NONLOCAL_CONTEXT (ref) && DECL_INITIAL (ref))
	  प्रत्यागम;
	भङ्ग;
      पक्ष VAR_DECL:
	/* Static variables and constexpr are ok, but for the later only
	   when the address is not taken.  */
	यदि (वृक्ष_STATIC (ref) || (C_DECL_DECLARED_CONSTEXPR (ref) && !address))
	  प्रत्यागम;
	भङ्ग;
      पक्ष TYPE_DECL:
	/* A typedef is ok when not for a variably-modified type. */
	प्रत्यागम;
      पक्ष CONST_DECL:
	/* An enumeration constant is ok. */
	प्रत्यागम;
      पक्ष PARM_DECL:
	भङ्ग;
      पक्ष LABEL_DECL:
	भङ्ग;
      स्वभाव:
	gcc_unreachable ();
    }

  /* Mark all parent functions up to the nesting level of the variable as
     as needing the non-local context.  */
  प्रति (वृक्ष cont = current_function_decl; cont; cont = DECL_CONTEXT (cont))
    {
      यदि (cont == DECL_CONTEXT (ref))
	भङ्ग;

      /* There should not be any other type of context used for function
	 except TRANSLATION_UNIT_DECL which we should be able to reach.  */
      gcc_checking_assert (वृक्ष_CODE (cont) == FUNCTION_DECL);

      यदि (वृक्ष_CODE (cont) == FUNCTION_DECL)
	C_FUNC_NONLOCAL_CONTEXT (cont) = 1;
    }
}


/* Build an external reference to identifier ID.  FUN indicates
   whether this will be used for a function call.  LOC is the source
   location of the identifier.  This sets *TYPE to the type of the
   identifier, which is not the same as the type of the returned value
   for CONST_DECLs defined as enum constants.  If the type of the
   identifier is not available, *TYPE is set to NULL.  */
वृक्ष
build_external_ref (location_t loc, वृक्ष id, तार्किक fun, वृक्ष *type)
{
  वृक्ष ref;
  वृक्ष decl = lookup_name (id);

  /* In Objective-C, an instance variable (ivar) may be preferred to
     whatever lookup_name() found.  */
  decl = objc_lookup_ivar (decl, id);

  *type = रिक्त;
  यदि (decl && decl != error_mark_गाँठ)
    {
      ref = decl;
      *type = वृक्ष_TYPE (ref);
      यदि (DECL_P (decl) && C_DECL_UNDERSPECIFIED (decl))
	error_at (loc, "underspecified %qD referenced in its initializer",
		  decl);
    }
  अन्यथा यदि (fun)
    /* Implicit function declaration.  */
    ref = implicitly_declare (loc, id);
  अन्यथा यदि (decl == error_mark_गाँठ)
    /* Don't complain about something that's already been
       complained about.  */
    प्रत्यागम error_mark_गाँठ;
  अन्यथा
    {
      undeclared_variable (loc, id);
      प्रत्यागम error_mark_गाँठ;
    }

  /* For an OpenMP map clause, we can get better diagnostics for decls with
     unmappable types if we return the decl with an error_mark_node type,
     rather than returning error_mark_node for the decl itself.  */
  यदि (वृक्ष_TYPE (ref) == error_mark_गाँठ
      && !c_omp_array_section_p)
    प्रत्यागम error_mark_गाँठ;

  यदि (वृक्ष_UNAVAILABLE (ref))
    error_unavailable_use (ref, NULL_वृक्ष);
  अन्यथा यदि (वृक्ष_DEPRECATED (ref))
    warn_deprecated_use (ref, NULL_वृक्ष);

  /* Recursive call does not count as usage.  */
  यदि (ref != current_function_decl)
    {
      वृक्ष_USED (ref) = 1;
    }

  mark_decl_used (ref, असत्य);

  यदि (वृक्ष_CODE (ref) == CONST_DECL)
    {
      used_types_जोड़ो (वृक्ष_TYPE (ref));

      यदि (warn_cxx_compat
	  && वृक्ष_CODE (वृक्ष_TYPE (ref)) == ENUMERAL_TYPE
	  && C_TYPE_DEFINED_IN_STRUCT (वृक्ष_TYPE (ref)))
	{
	  warning_at (loc, OPT_Wc___compat,
		      "enum constant defined in struct or union "
		      "is not visible in C++");
	  inform (DECL_SOURCE_LOCATION (ref), "enum constant defined here");
	}

      ref = DECL_INITIAL (ref);
      वृक्ष_CONSTANT (ref) = 1;
    }
  /* C99 6.7.4p3: An inline definition of a function with external
     linkage ... shall not contain a reference to an identifier with
     internal linkage.  */
  अन्यथा यदि (current_function_decl != NULL_वृक्ष
	   && DECL_DECLARED_INLINE_P (current_function_decl)
	   && DECL_EXTERNAL (current_function_decl)
	   && VAR_OR_FUNCTION_DECL_P (ref)
	   && (!VAR_P (ref) || वृक्ष_STATIC (ref))
	   && ! वृक्ष_PUBLIC (ref)
	   && DECL_CONTEXT (ref) != current_function_decl)
    record_inline_static (loc, current_function_decl, ref,
			  csi_internal);

  प्रत्यागम ref;
}

स्थिर संरचना maybe_used_decl *maybe_used_decls;

/* Record that DECL, a reference seen inside sizeof or typeof or _Countof or
   _Generic, might be used if the operand of sizeof is a VLA type or the
   operand of typeof is a variably modified type or the operand of _Countof has
   a variable number of elements or the operand of _Generic is the one selected
   as the result.  */

स्थिर शून्य
record_maybe_used_decl (वृक्ष decl, तार्किक address)
{
  संरचना maybe_used_decl *t = XOBNEW (&parser_obstack, संरचना maybe_used_decl);
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

शून्य
निकालो_maybe_used (तार्किक used)
{
  संरचना maybe_used_decl *p = maybe_used_decls;
  पूर्णाङ्क cur_level = in_sizeof + in_typeof + in_countof + in_generic;
  यावत् (p && p->level > cur_level)
    {
      यदि (used)
	{
	  यदि (cur_level == 0)
	    mark_decl_used (p->decl, p->address);
	  अन्यथा
	    p->level = cur_level;
	}
      p = p->next;
    }
  यदि (!used || cur_level == 0)
    maybe_used_decls = p;
}

/* Pop the stack of decls possibly used inside sizeof or typeof or _Countof or
   _Generic, without acting on them, and return the pointer to the previous top
   of the stack.  This for use at the end of a default generic association when
   it is not yet known whether the expression is used.  If it later turns out
   the expression is used (or treated as used before C23), restore_maybe_used
   should be called on the return value followed by pop_maybe_used (true);
   otherwise, the return value can be discarded.  */

संरचना maybe_used_decl *
save_maybe_used ()
{
  संरचना maybe_used_decl *p = maybe_used_decls, *orig = p;
  पूर्णाङ्क cur_level = in_sizeof + in_typeof + in_countof + in_generic;
  यावत् (p && p->level > cur_level)
    p = p->next;
  maybe_used_decls = p;
  प्रत्यागम orig;
}

/* Restore the stack of decls possibly used inside sizeof or typeof or _Countof
   or _Generic returned by save_maybe_used.  It is required that the stack is
   at exactly the point where it was left by save_maybe_used.  */

शून्य
restore_maybe_used (संरचना maybe_used_decl *ढेर)
{
  maybe_used_decls = ढेर;
}

/* Return the result of sizeof applied to EXPR.  */

संरचना c_व्यंजक
c_व्यंजक_sizeof_व्यंजक (location_t loc, संरचना c_व्यंजक व्यंजक)
{
  संरचना c_व्यंजक ret;
  यदि (व्यंजक.मूल्य == error_mark_गाँठ)
    {
      ret.मूल्य = error_mark_गाँठ;
      ret.original_code = ERROR_MARK;
      ret.original_type = रिक्त;
      ret.m_decimal = 0;
      निकालो_maybe_used (असत्य);
    }
  अन्यथा
    {
      तार्किक व्यंजक_const_operands = सत्य;

      यदि (वृक्ष_CODE (व्यंजक.मूल्य) == PARM_DECL
	  && C_ARRAY_PARAMETER (व्यंजक.मूल्य))
	{
	  auto_diagnostic_group d;
	  यदि (warning_at (loc, OPT_Wsizeof_array_argument,
			  "%<sizeof%> on array function parameter %qE will "
			  "return size of %qT", व्यंजक.मूल्य,
			  वृक्ष_TYPE (व्यंजक.मूल्य)))
	    inform (DECL_SOURCE_LOCATION (व्यंजक.मूल्य), "declared here");
	}
      वृक्ष folded_व्यंजक = c_fully_fold (व्यंजक.मूल्य, require_constant_मूल्य,
				       &व्यंजक_const_operands);
      ret.मूल्य = c_sizeof (loc, वृक्ष_TYPE (folded_व्यंजक));
      c_last_sizeof_arg = व्यंजक.मूल्य;
      c_last_sizeof_loc = loc;
      ret.original_code = SIZEOF_व्यंजक;
      ret.original_type = रिक्त;
      ret.m_decimal = 0;
      यदि (C_TYPE_VARIABLE_SIZE (वृक्ष_TYPE (folded_व्यंजक)))
	{
	  /* sizeof is evaluated when given a vla (C99 6.5.3.4p2).  */
	  ret.मूल्य = build2 (C_MAYBE_CONST_व्यंजक, वृक्ष_TYPE (ret.मूल्य),
			      folded_व्यंजक, ret.मूल्य);
	  C_MAYBE_CONST_व्यंजक_NON_CONST (ret.मूल्य) = !व्यंजक_const_operands;
	  SET_व्यंजक_LOCATION (ret.मूल्य, loc);
	}
      निकालो_maybe_used (C_TYPE_VARIABLE_SIZE (वृक्ष_TYPE (folded_व्यंजक)));
    }
  प्रत्यागम ret;
}

/* Return the result of sizeof applied to T, a structure for the type
   name passed to sizeof (rather than the type itself).  LOC is the
   location of the original expression.  */

संरचना c_व्यंजक
c_व्यंजक_sizeof_type (location_t loc, संरचना c_type_name *t)
{
  वृक्ष type;
  संरचना c_व्यंजक ret;
  वृक्ष type_व्यंजक = NULL_वृक्ष;
  तार्किक type_व्यंजक_const = सत्य;
  type = groktypename (t, &type_व्यंजक, &type_व्यंजक_const);
  ret.मूल्य = c_sizeof (loc, type);
  c_last_sizeof_arg = type;
  c_last_sizeof_loc = loc;
  ret.original_code = SIZEOF_व्यंजक;
  ret.original_type = रिक्त;
  ret.m_decimal = 0;
  यदि (type == error_mark_गाँठ)
    {
      ret.मूल्य = error_mark_गाँठ;
      ret.original_code = ERROR_MARK;
    }
  अन्यथा
  यदि ((type_व्यंजक || वृक्ष_CODE (ret.मूल्य) == INTEGER_CST)
      && C_TYPE_VARIABLE_SIZE (type))
    {
      /* If the type is a [*] array, it is a VLA but is represented as
	 having a size of zero.  In such a case we must ensure that
	 the result of sizeof does not get folded to a constant by
	 c_fully_fold, because if the size is evaluated the result is
	 not constant and so constraints on zero or negative size
	 arrays must not be applied when this sizeof call is inside
	 another array declarator.  */
      यदि (!type_व्यंजक)
	type_व्यंजक = integer_zero_गाँठ;
      ret.मूल्य = build2 (C_MAYBE_CONST_व्यंजक, वृक्ष_TYPE (ret.मूल्य),
			  type_व्यंजक, ret.मूल्य);
      C_MAYBE_CONST_व्यंजक_NON_CONST (ret.मूल्य) = !type_व्यंजक_const;
    }
  निकालो_maybe_used (type != error_mark_गाँठ
		  ? C_TYPE_VARIABLE_SIZE (type) : असत्य);
  प्रत्यागम ret;
}

स्थिर तार्किक
शीर्ष_array_vla_p (const_वृक्ष type)
{
  यदि (वृक्ष_CODE (type) != ARRAY_TYPE)
    प्रत्यागम असत्य;

  वृक्ष d = TYPE_DOMAIN (type);

  यदि (!d)
    प्रत्यागम असत्य;
  यदि (!TYPE_MAX_मूल्य (d))
    प्रत्यागम असत्य;

  प्रत्यागम वृक्ष_CODE (TYPE_MAX_मूल्य (d)) != INTEGER_CST
	 || वृक्ष_CODE (TYPE_MIN_मूल्य (d)) != INTEGER_CST;
}

/* Return the result of countof applied to EXPR.  */

संरचना c_व्यंजक
c_व्यंजक_countof_व्यंजक (location_t loc, संरचना c_व्यंजक व्यंजक)
{
  संरचना c_व्यंजक ret;
  यदि (व्यंजक.मूल्य == error_mark_गाँठ)
    {
      ret.मूल्य = error_mark_गाँठ;
      ret.original_code = ERROR_MARK;
      ret.original_type = रिक्त;
      ret.m_decimal = 0;
      निकालो_maybe_used (असत्य);
    }
  अन्यथा
    {
      तार्किक व्यंजक_const_operands = सत्य;

      वृक्ष folded_व्यंजक = c_fully_fold (व्यंजक.मूल्य, require_constant_मूल्य,
				       &व्यंजक_const_operands);
      ret.मूल्य = c_countof_type (loc, वृक्ष_TYPE (folded_व्यंजक));
      c_last_sizeof_arg = व्यंजक.मूल्य;
      c_last_sizeof_loc = loc;
      ret.original_code = COUNTOF_व्यंजक;
      ret.original_type = रिक्त;
      ret.m_decimal = 0;
      यदि (शीर्ष_array_vla_p (वृक्ष_TYPE (folded_व्यंजक)))
	{
	  /* countof is evaluated when given a vla.  */
	  ret.मूल्य = build2 (C_MAYBE_CONST_व्यंजक, वृक्ष_TYPE (ret.मूल्य),
			      folded_व्यंजक, ret.मूल्य);
	  C_MAYBE_CONST_व्यंजक_NON_CONST (ret.मूल्य) = !व्यंजक_const_operands;
	  SET_व्यंजक_LOCATION (ret.मूल्य, loc);
	}
      निकालो_maybe_used (शीर्ष_array_vla_p (वृक्ष_TYPE (folded_व्यंजक)));
    }
  प्रत्यागम ret;
}

/* Return the result of countof applied to T, a structure for the type
   name passed to countof (rather than the type itself).  LOC is the
   location of the original expression.  */

संरचना c_व्यंजक
c_व्यंजक_countof_type (location_t loc, संरचना c_type_name *t)
{
  वृक्ष type;
  संरचना c_व्यंजक ret;
  वृक्ष type_व्यंजक = NULL_वृक्ष;
  तार्किक type_व्यंजक_const = सत्य;
  type = groktypename (t, &type_व्यंजक, &type_व्यंजक_const);
  ret.मूल्य = c_countof_type (loc, type);
  c_last_sizeof_arg = type;
  c_last_sizeof_loc = loc;
  ret.original_code = COUNTOF_व्यंजक;
  ret.original_type = रिक्त;
  ret.m_decimal = 0;
  यदि (type == error_mark_गाँठ)
    {
      ret.मूल्य = error_mark_गाँठ;
      ret.original_code = ERROR_MARK;
    }
  अन्यथा
  यदि ((type_व्यंजक || वृक्ष_CODE (ret.मूल्य) == INTEGER_CST)
      && शीर्ष_array_vla_p (type))
    {
      /* If the type is a [*] array, it is a VLA but is represented as
	 having a size of zero.  In such a case we must ensure that
	 the result of countof does not get folded to a constant by
	 c_fully_fold, because if the number of elements is evaluated
	 the result is not constant and so
	 constraints on zero or negative size arrays must not be applied
	 when this countof call is inside another array declarator.  */
      यदि (!type_व्यंजक)
	type_व्यंजक = integer_zero_गाँठ;
      ret.मूल्य = build2 (C_MAYBE_CONST_व्यंजक, वृक्ष_TYPE (ret.मूल्य),
			  type_व्यंजक, ret.मूल्य);
      C_MAYBE_CONST_व्यंजक_NON_CONST (ret.मूल्य) = !type_व्यंजक_const;
    }
  निकालो_maybe_used (type != error_mark_गाँठ ? शीर्ष_array_vla_p (type) : असत्य);
  प्रत्यागम ret;
}

/* Return the result of maxof applied to T, a structure for the type
   name passed to maxof (rather than the type itself).  LOC is the
   location of the original expression.  */

संरचना c_व्यंजक
c_व्यंजक_maxof_type (location_t loc, संरचना c_type_name *t)
{
  वृक्ष type;
  संरचना c_व्यंजक ret;
  वृक्ष type_व्यंजक = NULL_वृक्ष;
  तार्किक type_व्यंजक_const = सत्य;
  type = groktypename (t, &type_व्यंजक, &type_व्यंजक_const);
  ret.मूल्य = c_maxof_type (loc, type);
  c_last_sizeof_arg = type;
  c_last_sizeof_loc = loc;
  ret.original_code = MAXOF_व्यंजक;
  ret.original_type = रिक्त;
  ret.m_decimal = 0;
  यदि (type == error_mark_गाँठ)
    {
      ret.मूल्य = error_mark_गाँठ;
      ret.original_code = ERROR_MARK;
    }
  निकालो_maybe_used (type != error_mark_गाँठ);
  प्रत्यागम ret;
}

/* Return the result of minof applied to T, a structure for the type
   name passed to minof (rather than the type itself).  LOC is the
   location of the original expression.  */

संरचना c_व्यंजक
c_व्यंजक_minof_type (location_t loc, संरचना c_type_name *t)
{
  वृक्ष type;
  संरचना c_व्यंजक ret;
  वृक्ष type_व्यंजक = NULL_वृक्ष;
  तार्किक type_व्यंजक_const = सत्य;
  type = groktypename (t, &type_व्यंजक, &type_व्यंजक_const);
  ret.मूल्य = c_minof_type (loc, type);
  c_last_sizeof_arg = type;
  c_last_sizeof_loc = loc;
  ret.original_code = MINOF_व्यंजक;
  ret.original_type = रिक्त;
  ret.m_decimal = 0;
  यदि (type == error_mark_गाँठ)
    {
      ret.मूल्य = error_mark_गाँठ;
      ret.original_code = ERROR_MARK;
    }
  निकालो_maybe_used (type != error_mark_गाँठ);
  प्रत्यागम ret;
}

/* Build a function call to function FUNCTION with parameters PARAMS.
   The function call is at LOC.
   PARAMS is a list--a chain of TREE_LIST nodes--in which the
   TREE_VALUE of each node is a parameter-expression.
   FUNCTION's data type may be a function type or a pointer-to-function.  */

वृक्ष
build_function_call (location_t loc, वृक्ष function, वृक्ष params)
{
  vec<वृक्ष, va_gc> *v;
  वृक्ष ret;

  vec_alloc (v, list_length (params));
  प्रति (; params; params = वृक्ष_CHAIN (params))
    v->quick_धकेलो (वृक्ष_मूल्य (params));
  ret = c_build_function_call_vec (loc, vNULL, function, v, रिक्त);
  vec_free (v);
  प्रत्यागम ret;
}

/* Give a note about the location of the declaration of DECL,
   or, failing that, a pertinent declaration for FUNCTION_EXPR.  */

स्थिर शून्य
inform_declaration (वृक्ष decl, वृक्ष function_व्यंजक)
{
  यदि (decl && (वृक्ष_CODE (decl) != FUNCTION_DECL
	       || !DECL_IS_UNDECLARED_BUILTIN (decl)))
    inform (DECL_SOURCE_LOCATION (decl), "declared here");
  अन्यथा यदि (function_व्यंजक)
    विकल्प (वृक्ष_CODE (function_व्यंजक))
      {
      स्वभाव:
	भङ्ग;
      पक्ष COMPONENT_REF:
	/* Show the decl of the pertinent field (e.g. for callback
	   fields in a struct.  */
	{
	  वृक्ष field_decl = वृक्ष_OPERAND (function_व्यंजक, 1);
	  यदि (location_t loc = DECL_SOURCE_LOCATION (field_decl))
	    inform (loc, "declared here");
	}
	भङ्ग;
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

वृक्ष
build_function_call_vec (location_t loc, vec<location_t> arg_loc,
			 वृक्ष function, vec<वृक्ष, va_gc> *params,
			 vec<वृक्ष, va_gc> *origtypes, वृक्ष orig_fundecl)
{
  वृक्ष fntype, fundecl = NULL_वृक्ष;
  वृक्ष name = NULL_वृक्ष, result;
  वृक्ष tem;
  पूर्णाङ्क nargs;
  वृक्ष *argarray;


  /* Strip NON_LVALUE_EXPRs, etc., since we aren't using as an lvalue.  */
  STRIP_TYPE_NOPS (function);

  /* Convert anything with function type to a pointer-to-function.  */
  यदि (वृक्ष_CODE (function) == FUNCTION_DECL)
    {
      name = DECL_NAME (function);

      यदि (flag_tm)
	tm_malloc_replacement (function);
      fundecl = function;
      यदि (!orig_fundecl)
	orig_fundecl = fundecl;
      /* Atomic functions have type checking/casting already done.  They are
	 often rewritten and don't match the original parameter list.  */
      यदि (name && startswith (IDENTIFIER_POINTER (name), "__atomic_"))
        origtypes = रिक्त;
    }
  यदि (वृक्ष_CODE (वृक्ष_TYPE (function)) == FUNCTION_TYPE)
    function = function_to_pointer_conversion (loc, function);

  /* For Objective-C, convert any calls via a cast to OBJC_TYPE_REF
     expressions, like those used for ObjC messenger dispatches.  */
  यदि (params && !params->is_empty ())
    function = objc_rewrite_function_call (function, (*params)[0]);

  function = c_fully_fold (function, असत्य, रिक्त);

  fntype = वृक्ष_TYPE (function);

  यदि (वृक्ष_CODE (fntype) == ERROR_MARK)
    प्रत्यागम error_mark_गाँठ;

  यदि (!(वृक्ष_CODE (fntype) == POINTER_TYPE
	&& वृक्ष_CODE (वृक्ष_TYPE (fntype)) == FUNCTION_TYPE))
    {
      यदि (!flag_diagnostics_show_caret && !STATEMENT_CLASS_P (function))
	error_at (loc,
		  "called object %qE is not a function or function pointer",
		  function);
      अन्यथा यदि (DECL_P (function))
	{
	  auto_diagnostic_group d;
	  error_at (loc,
		    "called object %qD is not a function or function pointer",
		    function);
	  inform_declaration (function, NULL_वृक्ष);
	}
      अन्यथा
	error_at (loc,
		  "called object is not a function or function pointer");
      प्रत्यागम error_mark_गाँठ;
    }

  यदि (fundecl && वृक्ष_THIS_VOLATILE (fundecl))
    current_function_returns_abnormally = 1;

  /* fntype now gets the type of function pointed to.  */
  fntype = वृक्ष_TYPE (fntype);
  वृक्ष return_type = वृक्ष_TYPE (fntype);

  /* Convert the parameters to the types declared in the
     function prototype, or apply default promotions.  */

  nargs = convert_arguments (loc, arg_loc, fntype, params,
			     origtypes, function, fundecl);
  यदि (nargs < 0)
    प्रत्यागम error_mark_गाँठ;

  /* Check that the function is called through a compatible prototype.
     If it is not, warn.  */
  यदि (CONVERT_व्यंजक_P (function)
      && वृक्ष_CODE (tem = वृक्ष_OPERAND (function, 0)) == ADDR_व्यंजक
      && वृक्ष_CODE (tem = वृक्ष_OPERAND (tem, 0)) == FUNCTION_DECL
      && !comptypes (fntype, वृक्ष_TYPE (tem)))
    {
      /* This situation leads to run-time undefined behavior.  We can't,
	 therefore, simply error unless we can prove that all possible
	 executions of the program must execute the code.  */
      warning_at (loc, 0, "function called through a non-compatible type");

      यदि (VOID_TYPE_P (return_type)
	  && TYPE_QUALS (return_type) != TYPE_UNQUALIFIED)
	pedwarn (loc, 0,
		 "function with qualified void return type called");
     }

  argarray = vec_safe_address (params);

  /* Check that arguments to builtin functions match the expectations.  */
  यदि (fundecl
      && fndecl_built_in_p (fundecl)
      && !check_builtin_function_arguments (loc, arg_loc, fundecl,
					    orig_fundecl, nargs, argarray))
    प्रत्यागम error_mark_गाँठ;

  /* Check that the arguments to the function are valid.  */
  तार्किक warned_p = check_function_arguments (loc, fundecl, fntype,
					    nargs, argarray, &arg_loc,
					    comptypes);

  यदि (TYPE_QUALS (return_type) != TYPE_UNQUALIFIED
      && !VOID_TYPE_P (return_type))
    return_type = c_build_qualified_type (return_type, TYPE_UNQUALIFIED);
  यदि (name != NULL_वृक्ष
      && startswith (IDENTIFIER_POINTER (name), "__builtin_"))
    {
      यदि (require_constant_मूल्य)
	result
	  = fold_build_call_array_initializer_loc (loc, return_type,
						   function, nargs, argarray);
      अन्यथा
	result = fold_build_call_array_loc (loc, return_type,
					    function, nargs, argarray);
      यदि (वृक्ष_CODE (result) == NOP_व्यंजक
	  && वृक्ष_CODE (वृक्ष_OPERAND (result, 0)) == INTEGER_CST)
	STRIP_TYPE_NOPS (result);
    }
  अन्यथा
    result = build_call_array_loc (loc, return_type,
				   function, nargs, argarray);
  /* If -Wnonnull warning has been diagnosed, avoid diagnosing it again
     later.  */
  यदि (warned_p && वृक्ष_CODE (result) == CALL_व्यंजक)
    suppress_warning (result, OPT_Wnonnull);

  /* In this improbable scenario, a nested function returns a VM type.
     Create a TARGET_EXPR so that the call always has a LHS, much as
     what the C++ FE does for functions returning non-PODs.  */
  यदि (c_type_variably_modified_p (वृक्ष_TYPE (fntype)))
    {
      वृक्ष tmp = create_tmp_var_raw (वृक्ष_TYPE (fntype));
      result = build4 (TARGET_व्यंजक, वृक्ष_TYPE (fntype), tmp, result,
		       NULL_वृक्ष, NULL_वृक्ष);
    }

  यदि (VOID_TYPE_P (वृक्ष_TYPE (result)))
    {
      यदि (TYPE_QUALS (वृक्ष_TYPE (result)) != TYPE_UNQUALIFIED)
	pedwarn (loc, 0,
		 "function with qualified void return type called");
      प्रत्यागम result;
    }
  प्रत्यागम require_complete_type (loc, result);
}

/* Like build_function_call_vec, but call also resolve_overloaded_builtin.  */

वृक्ष
c_build_function_call_vec (location_t loc, ध्रुव vec<location_t> &arg_loc,
			   वृक्ष function, vec<वृक्ष, va_gc> *params,
			   vec<वृक्ष, va_gc> *origtypes)
{
  /* Strip NON_LVALUE_EXPRs, etc., since we aren't using as an lvalue.  */
  STRIP_TYPE_NOPS (function);

  /* Convert anything with function type to a pointer-to-function.  */
  यदि (वृक्ष_CODE (function) == FUNCTION_DECL)
    {
      /* Implement type-directed function overloading for builtins.
	 resolve_overloaded_builtin and targetm.resolve_overloaded_builtin
	 handle all the type checking.  The result is a complete expression
	 that implements this function call.  */
      वृक्ष tem = resolve_overloaded_builtin (loc, function, params);
      यदि (tem)
	प्रत्यागम tem;
    }
  प्रत्यागम build_function_call_vec (loc, arg_loc, function, params, origtypes);
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

स्थिर वृक्ष
convert_argument (location_t ploc, वृक्ष function, वृक्ष fundecl,
		  वृक्ष type, वृक्ष origtype, वृक्ष val, वृक्ष valtype,
		  तार्किक npc, वृक्ष rname, पूर्णाङ्क parmnum, पूर्णाङ्क argnum,
		  तार्किक excess_precision, पूर्णाङ्क warnopt)
{
  /* Formal parm type is specified by a function prototype.  */

  यदि (type == error_mark_गाँठ || !COMPLETE_TYPE_P (type))
    {
      error_at (ploc, "type of formal parameter %d is incomplete",
		parmnum + 1);
      प्रत्यागम error_mark_गाँठ;
    }

  /* Optionally warn about conversions that differ from the default
     conversions.  */
  यदि (warn_traditional_conversion || warn_traditional)
    {
      यदि (INTEGRAL_TYPE_P (type)
	  && SCALAR_FLOAT_TYPE_P (valtype))
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as integer rather "
		    "than floating due to prototype",
		    argnum, rname);
      यदि (INTEGRAL_TYPE_P (type)
	  && वृक्ष_CODE (valtype) == COMPLEX_TYPE)
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as integer rather "
		    "than complex due to prototype",
		    argnum, rname);
      अन्यथा यदि (वृक्ष_CODE (type) == COMPLEX_TYPE
	       && SCALAR_FLOAT_TYPE_P (valtype))
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as complex rather "
		    "than floating due to prototype",
		    argnum, rname);
      अन्यथा यदि (SCALAR_FLOAT_TYPE_P (type)
	       && INTEGRAL_TYPE_P (valtype))
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as floating rather "
		    "than integer due to prototype",
		    argnum, rname);
      अन्यथा यदि (वृक्ष_CODE (type) == COMPLEX_TYPE
	       && INTEGRAL_TYPE_P (valtype))
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as complex rather "
		    "than integer due to prototype",
		    argnum, rname);
      अन्यथा यदि (SCALAR_FLOAT_TYPE_P (type)
	       && वृक्ष_CODE (valtype) == COMPLEX_TYPE)
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as floating rather "
		    "than complex due to prototype",
		    argnum, rname);
      /* ??? At some point, messages should be written about
	 conversions between complex types, but that's too messy
	 to do now.  */
      अन्यथा यदि (SCALAR_FLOAT_TYPE_P (type)
	       && SCALAR_FLOAT_TYPE_P (valtype))
	{
	  अचिन्हित पूर्णाङ्क formal_prec = TYPE_PRECISION (type);

	  /* Warn if any argument is passed as `float',
	     since without a prototype it would be `double'.  */
	  यदि (formal_prec == TYPE_PRECISION (float_type_गाँठ)
	      && type != dfloat32_type_गाँठ)
	    warning_at (ploc, 0,
			"passing argument %d of %qE as %<float%> "
			"rather than %<double%> due to prototype",
			argnum, rname);

	  /* Warn if mismatch between argument and prototype
	     for decimal float types.  Warn of conversions with
	     binary float types and of precision narrowing due to
	     prototype.  */
	  अन्यथा यदि (type != valtype
		   && (type == dfloat32_type_गाँठ
		       || type == dfloat64_type_गाँठ
		       || type == dfloat128_type_गाँठ
		       || valtype == dfloat32_type_गाँठ
		       || valtype == dfloat64_type_गाँठ
		       || valtype == dfloat128_type_गाँठ)
		   && (formal_prec
		       <= TYPE_PRECISION (valtype)
		       || (type == dfloat128_type_गाँठ
			   && (valtype
			       != dfloat64_type_गाँठ
			       && (valtype
				   != dfloat32_type_गाँठ)))
		       || (type == dfloat64_type_गाँठ
			   && (valtype
			       != dfloat32_type_गाँठ))))
	    warning_at (ploc, 0,
			"passing argument %d of %qE as %qT "
			"rather than %qT due to prototype",
			argnum, rname, type, valtype);

	}
      /* Detect integer changing in width or signedness.
	 These warnings are only activated with
	 -Wtraditional-conversion, not with -Wtraditional.  */
      अन्यथा यदि (warn_traditional_conversion
	       && INTEGRAL_TYPE_P (type)
	       && INTEGRAL_TYPE_P (valtype))
	{
	  अचिन्हित पूर्णाङ्क formal_prec = TYPE_PRECISION (type);
	  वृक्ष would_have_been = default_conversion (val);
	  वृक्ष type1 = वृक्ष_TYPE (would_have_been);

	  यदि (val == error_mark_गाँठ)
	    /* VAL could have been of incomplete type.  */;
	  अन्यथा यदि (वृक्ष_CODE (type) == ENUMERAL_TYPE
		   && (TYPE_MAIN_VARIANT (type)
		       == TYPE_MAIN_VARIANT (valtype)))
	    /* No warning if function asks for enum
	       and the actual arg is that enum type.  */
	    ;
	  अन्यथा यदि (formal_prec != TYPE_PRECISION (type1))
	    warning_at (ploc, OPT_Wtraditional_conversion,
			"passing argument %d of %qE "
			"with different width due to prototype",
			argnum, rname);
	  अन्यथा यदि (TYPE_UNSIGNED (type) == TYPE_UNSIGNED (type1))
	    ;
	  /* Don't complain if the formal parameter type
	     is an enum, because we can't tell now whether
	     the value was an enum--even the same enum.  */
	  अन्यथा यदि (वृक्ष_CODE (type) == ENUMERAL_TYPE)
	    ;
	  अन्यथा यदि (वृक्ष_CODE (val) == INTEGER_CST
		   && int_fits_type_p (val, type))
	    /* Change in signedness doesn't matter
	       if a constant value is unaffected.  */
	    ;
	  /* If the value is extended from a narrower
	     unsigned type, it doesn't matter whether we
	     pass it as signed or unsigned; the value
	     certainly is the same either way.  */
	  अन्यथा यदि (TYPE_PRECISION (valtype) < TYPE_PRECISION (type)
		   && TYPE_UNSIGNED (valtype))
	    ;
	  अन्यथा यदि (TYPE_UNSIGNED (type))
	    warning_at (ploc, OPT_Wtraditional_conversion,
			"passing argument %d of %qE "
			"as unsigned due to prototype",
			argnum, rname);
	  अन्यथा
	    warning_at (ploc, OPT_Wtraditional_conversion,
			"passing argument %d of %qE "
			"as signed due to prototype",
			argnum, rname);
	}
    }

  /* Possibly restore an EXCESS_PRECISION_EXPR for the
     sake of better warnings from convert_and_check.  */
  यदि (excess_precision)
    val = build1 (EXCESS_PRECISION_व्यंजक, valtype, val);

  वृक्ष parmval = convert_for_assignment (ploc, ploc, type,
					 val, origtype, ic_argpass,
					 npc, fundecl, function,
					 parmnum + 1, warnopt);
  प्रत्यागम parmval;
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

स्थिर पूर्णाङ्क
convert_arguments (location_t loc, vec<location_t> arg_loc, वृक्ष fntype,
		   vec<वृक्ष, va_gc> *मूल्यावली, vec<वृक्ष, va_gc> *origtypes,
		   वृक्ष function, वृक्ष fundecl)
{
  वृक्ष typelist = TYPE_ARG_TYPES (fntype);
  अचिन्हित पूर्णाङ्क parmnum;
  तार्किक error_args = असत्य;
  ध्रुव तार्किक type_generic = fundecl
    && lookup_attribute ("type generic", TYPE_ATTRIBUTES (वृक्ष_TYPE (fundecl)));
  तार्किक type_generic_remove_excess_precision = असत्य;
  तार्किक type_generic_overflow_p = असत्य;
  तार्किक type_generic_bit_query = असत्य;
  वृक्ष selector;

  /* Change pointer to function to the function itself for
     diagnostics.  */
  यदि (वृक्ष_CODE (function) == ADDR_व्यंजक
      && वृक्ष_CODE (वृक्ष_OPERAND (function, 0)) == FUNCTION_DECL)
    function = वृक्ष_OPERAND (function, 0);

  /* Handle an ObjC selector specially for diagnostics.  */
  selector = objc_message_selector ();

  /* For a call to a built-in function declared without a prototype,
     set to the built-in function's argument list.  */
  वृक्ष builtin_typelist = NULL_वृक्ष;

  /* For type-generic built-in functions, determine whether excess
     precision should be removed (classification) or not
     (comparison).  */
  यदि (fundecl
      && fndecl_built_in_p (fundecl, BUILT_IN_NORMAL))
    {
      built_in_function code = DECL_FUNCTION_CODE (fundecl);
      यदि (C_DECL_BUILTIN_PROTOTYPE (fundecl))
	{
	  /* For a call to a built-in function declared without a prototype
	     use the types of the parameters of the internal built-in to
	     match those of the arguments to.  */
	  यदि (वृक्ष bdecl = builtin_decl_explicit (code))
	    builtin_typelist = TYPE_ARG_TYPES (वृक्ष_TYPE (bdecl));
	}

      /* For type-generic built-in functions, determine whether excess
	 precision should be removed (classification) or not
	 (comparison).  */
      यदि (type_generic)
	विकल्प (code)
	  {
	  पक्ष BUILT_IN_ISFINITE:
	  पक्ष BUILT_IN_ISINF:
	  पक्ष BUILT_IN_ISINF_SIGN:
	  पक्ष BUILT_IN_ISNAN:
	  पक्ष BUILT_IN_ISNORMAL:
	  पक्ष BUILT_IN_ISSIGNALING:
	  पक्ष BUILT_IN_FPCLASSIFY:
	    type_generic_remove_excess_precision = सत्य;
	    भङ्ग;

	  पक्ष BUILT_IN_ADD_OVERFLOW_P:
	  पक्ष BUILT_IN_SUB_OVERFLOW_P:
	  पक्ष BUILT_IN_MUL_OVERFLOW_P:
	    /* The last argument of these type-generic builtins
	       should not be promoted.  */
	    type_generic_overflow_p = सत्य;
	    भङ्ग;

	  पक्ष BUILT_IN_CLZG:
	  पक्ष BUILT_IN_CTZG:
	  पक्ष BUILT_IN_CLRSBG:
	  पक्ष BUILT_IN_FFSG:
	  पक्ष BUILT_IN_PARITYG:
	  पक्ष BUILT_IN_POPCOUNTG:
	    /* The first argument of these type-generic builtins
	       should not be promoted.  */
	    type_generic_bit_query = सत्य;
	    भङ्ग;

	  स्वभाव:
	    भङ्ग;
	  }
    }

  /* Scan the given expressions (VALUES) and types (TYPELIST), producing
     individual converted arguments.  */

  वृक्ष typetail, builtin_typetail, val;
  प्रति (typetail = typelist,
	 builtin_typetail = builtin_typelist,
	 parmnum = 0;
       मूल्यावली && मूल्यावली->iterate (parmnum, &val);
       ++parmnum)
    {
      /* The type of the function parameter (if it was declared with one).  */
      वृक्ष type = typetail ? वृक्ष_मूल्य (typetail) : NULL_वृक्ष;
      /* The type of the built-in function parameter (if the function
	 is a built-in).  Used to detect type incompatibilities in
	 calls to built-ins declared without a prototype.  */
      वृक्ष builtin_type = (builtin_typetail
			   ? वृक्ष_मूल्य (builtin_typetail) : NULL_वृक्ष);
      /* The original type of the argument being passed to the function.  */
      वृक्ष valtype = वृक्ष_TYPE (val);
      /* The called function (or function selector in Objective C).  */
      वृक्ष rname = function;
      पूर्णाङ्क argnum = parmnum + 1;
      ध्रुव वर्ण *invalid_func_diag;
      /* Set for EXCESS_PRECISION_EXPR arguments.  */
      तार्किक excess_precision = असत्य;
      /* The value of the argument after conversion to the type
	 of the function parameter it is passed to.  */
      वृक्ष parmval;
      /* Some __atomic_* builtins have additional hidden argument at
	 position 0.  */
      location_t ploc
	= !arg_loc.is_empty () && मूल्यावली->length () == arg_loc.length ()
	  ? expansion_point_location_if_in_system_header (arg_loc[parmnum])
	  : निवेश_location;

      यदि (type == void_type_गाँठ)
	{
	  auto_diagnostic_group d;
	  पूर्णाङ्क अंक_expected = parmnum;
	  पूर्णाङ्क अंक_actual = मूल्यावली->length ();
	  gcc_rich_location rich_loc (loc);
	  यदि (ploc != निवेश_location)
	    rich_loc.add_range (ploc);
	  यदि (selector)
	    error_at (&rich_loc,
		      "too many arguments to method %qE; expected %i, have %i",
		      selector, अंक_expected, अंक_actual);
	  अन्यथा
	    error_at (&rich_loc,
		      "too many arguments to function %qE; expected %i, have %i",
		      function, अंक_expected, अंक_actual);
	  inform_declaration (fundecl, function);
	  प्रत्यागम error_args ? -1 : (पूर्णाङ्क) parmnum;
	}

      यदि (builtin_type == void_type_गाँठ)
	{
	  auto_diagnostic_group d;
	  यदि (warning_at (loc, OPT_Wbuiltin_declaration_mismatch,
			  "too many arguments to built-in function %qE "
			  "expecting %d", function, parmnum))
	    inform_declaration (fundecl, function);
	  builtin_typetail = NULL_वृक्ष;
	}

      यदि (!typetail && parmnum == 0 && !TYPE_NO_NAMED_ARGS_STDARG_P (fntype)
	  && !(fundecl && fndecl_built_in_p (fundecl)))
	{
	  auto_diagnostic_group d;
	  तार्किक warned;
	  यदि (selector)
	    warned = warning_at (loc, OPT_Wdeprecated_non_prototype,
				 "ISO C23 does not allow arguments"
				 " for method %qE declared without parameters",
				 function);
	  अन्यथा
	    warned = warning_at (loc, OPT_Wdeprecated_non_prototype,
				 "ISO C23 does not allow arguments"
				 " for function %qE declared without parameters",
				 function);
	  यदि (warned)
	    inform_declaration (fundecl, function);
	}

      यदि (selector && argnum > 2)
	{
	  rname = selector;
	  argnum -= 2;
	}

      /* Determine if VAL is a null pointer constant before folding it.  */
      तार्किक npc = null_pointer_constant_p (val);

      /* If there is excess precision and a prototype, convert once to
	 the required type rather than converting via the semantic
	 type.  Likewise without a prototype a float value represented
	 as long double should be converted once to double.  But for
	 type-generic classification functions excess precision must
	 be removed here.  */
      यदि (वृक्ष_CODE (val) == EXCESS_PRECISION_व्यंजक
	  && (type || !type_generic || !type_generic_remove_excess_precision))
	{
	  val = वृक्ष_OPERAND (val, 0);
	  excess_precision = सत्य;
	}
      val = c_fully_fold (val, असत्य, रिक्त);
      STRIP_TYPE_NOPS (val);

      val = require_complete_type (ploc, val);

      /* Some floating-point arguments must be promoted to double when
	 no type is specified by a prototype.  This applies to
	 arguments of type float, and to architecture-specific types
	 (ARM __fp16), but not to _FloatN or _FloatNx types.  */
      तार्किक promote_float_arg = असत्य;
      यदि (type == NULL_वृक्ष
	  && वृक्ष_CODE (valtype) == REAL_TYPE
	  && (TYPE_PRECISION (valtype)
	      <= TYPE_PRECISION (double_type_गाँठ))
	  && TYPE_MAIN_VARIANT (valtype) != double_type_गाँठ
	  && TYPE_MAIN_VARIANT (valtype) != long_double_type_गाँठ
	  && !DECIMAL_FLOAT_MODE_P (TYPE_MODE (valtype)))
	{
	  /* Promote this argument, unless it has a _FloatN or
	     _FloatNx type.  */
	  promote_float_arg = सत्य;
	  प्रति (पूर्णाङ्क i = 0; i < अंक_FLOATN_NX_TYPES; i++)
	    यदि (TYPE_MAIN_VARIANT (valtype) == FLOATN_NX_TYPE_गाँठ (i))
	      {
		promote_float_arg = असत्य;
		भङ्ग;
	      }
	  /* Don't promote __bf16 either.  */
	  यदि (TYPE_MAIN_VARIANT (valtype) == bfloat16_type_गाँठ)
	    promote_float_arg = असत्य;
	}

      यदि (type != NULL_वृक्ष)
	{
	  वृक्ष origtype = (!origtypes) ? NULL_वृक्ष : (*origtypes)[parmnum];
	  parmval = convert_argument (ploc, function, fundecl, type, origtype,
				      val, valtype, npc, rname, parmnum, argnum,
				      excess_precision, 0);
	}
      /* A NULLPTR type is just a nullptr always.  */
      अन्यथा यदि (वृक्ष_CODE (वृक्ष_TYPE (val)) == NULLPTR_TYPE)
	parmval = omit_one_operand_loc (ploc, वृक्ष_TYPE (val), nullptr_गाँठ, val);
      अन्यथा यदि (promote_float_arg)
        {
	  यदि (type_generic)
	    parmval = val;
	  अन्यथा
	    {
	      /* Convert `float' to `double'.  */
	      यदि (warn_double_promotion && !c_inhibit_evaluation_warnings)
		warning_at (ploc, OPT_Wdouble_promotion,
			    "implicit conversion from %qT to %qT when passing "
			    "argument to function",
			    valtype, double_type_गाँठ);
	      parmval = convert (double_type_गाँठ, val);
	    }
	}
      अन्यथा यदि ((excess_precision && !type_generic)
	       || (type_generic_overflow_p && parmnum == 2)
	       || (type_generic_bit_query && parmnum == 0))
	/* A "double" argument with excess precision being passed
	   without a prototype or in variable arguments.
	   The last argument of __builtin_*_overflow_p should not be
	   promoted, similarly the first argument of
	   __builtin_{clz,ctz,clrsb,ffs,parity,popcount}g.  */
	parmval = convert (valtype, val);
      अन्यथा यदि ((invalid_func_diag =
		targetm.calls.invalid_arg_for_unprototyped_fn (typelist, fundecl, val)))
	{
	  error (invalid_func_diag);
	  प्रत्यागम -1;
	}
      अन्यथा यदि (वृक्ष_CODE (val) == ADDR_व्यंजक && reject_gcc_builtin (val))
	{
	  प्रत्यागम -1;
	}
      अन्यथा
	/* Convert `short' and `char' to full-size `int'.  */
	parmval = default_conversion (val);

      (*मूल्यावली)[parmnum] = parmval;
      यदि (parmval == error_mark_गाँठ)
	error_args = सत्य;

      यदि (!type && builtin_type && वृक्ष_CODE (builtin_type) != VOID_TYPE)
	{
	  /* For a call to a built-in function declared without a prototype,
	     perform the conversions from the argument to the expected type
	     but issue warnings rather than errors for any mismatches.
	     Ignore the converted argument and use the PARMVAL obtained
	     above by applying default conversions instead.  */
	  वृक्ष origtype = (!origtypes) ? NULL_वृक्ष : (*origtypes)[parmnum];
	  convert_argument (ploc, function, fundecl, builtin_type, origtype,
			    val, valtype, npc, rname, parmnum, argnum,
			    excess_precision,
			    OPT_Wbuiltin_declaration_mismatch);
	}

      यदि (typetail)
	typetail = वृक्ष_CHAIN (typetail);

      यदि (builtin_typetail)
	builtin_typetail = वृक्ष_CHAIN (builtin_typetail);
    }

  gcc_assert (parmnum == vec_safe_length (मूल्यावली));

  यदि (typetail != NULL_वृक्ष && वृक्ष_मूल्य (typetail) != void_type_गाँठ)
    {
      /* Not enough args.
	 Determine minimum number of arguments required.  */
      पूर्णाङ्क min_expected_अंक = 0;
      तार्किक at_least_p = असत्य;
      वृक्ष iter = typelist;
      यावत् (सत्य)
	{
	  यदि (!iter)
	    {
	      /* Variadic arguments; stop iterating.  */
	      at_least_p = सत्य;
	      भङ्ग;
	    }
	  यदि (iter == void_list_गाँठ)
	    /* End of arguments; stop iterating.  */
	    भङ्ग;
	  ++min_expected_अंक;
	  iter = वृक्ष_CHAIN (iter);
	}
      auto_diagnostic_group d;
      पूर्णाङ्क actual_अंक = vec_safe_length (मूल्यावली);
      error_at (loc,
		at_least_p
		? G_("too few arguments to function %qE; expected at least %i, have %i")
		: G_("too few arguments to function %qE; expected %i, have %i"),
		function, min_expected_अंक, actual_अंक);
      inform_declaration (fundecl, function);
      प्रत्यागम -1;
    }

  यदि (builtin_typetail && वृक्ष_मूल्य (builtin_typetail) != void_type_गाँठ)
    {
      अचिन्हित nargs = parmnum;
      प्रति (वृक्ष t = builtin_typetail; t; t = वृक्ष_CHAIN (t))
	++nargs;

      auto_diagnostic_group d;
      यदि (warning_at (loc, OPT_Wbuiltin_declaration_mismatch,
		      "too few arguments to built-in function %qE "
		      "expecting %u", function, nargs - 1))
	inform_declaration (fundecl, function);
    }

  प्रत्यागम error_args ? -1 : (पूर्णाङ्क) parmnum;
}

/* This is the entry point used by the parser to build unary operators
   in the input.  CODE, a tree_code, specifies the unary operator, and
   ARG is the operand.  For unary plus, the C parser currently uses
   CONVERT_EXPR for code.

   LOC is the location to use for the tree generated.
*/

संरचना c_व्यंजक
parser_build_unary_op (location_t loc, गणना वृक्ष_code code, संरचना c_व्यंजक arg)
{
  संरचना c_व्यंजक result;

  result.original_code = code;
  result.original_type = रिक्त;
  result.m_decimal = 0;

  यदि (reject_gcc_builtin (arg.मूल्य))
    {
      result.मूल्य = error_mark_गाँठ;
    }
  अन्यथा
    {
      result.मूल्य = build_unary_op (loc, code, arg.मूल्य, असत्य);

      यदि (वृक्ष_OVERFLOW_P (result.मूल्य) && !वृक्ष_OVERFLOW_P (arg.मूल्य))
	overflow_warning (loc, result.मूल्य, arg.मूल्य);
    }

  /* We are typically called when parsing a prefix token at LOC acting on
     ARG.  Reflect this by updating the source range of the result to
     start at LOC and end at the end of ARG.  */
  set_c_व्यंजक_source_range (&result,
			   loc, arg.get_finish ());

  प्रत्यागम result;
}

/* Returns true if TYPE is a character type, *not* including wchar_t.  */

तार्किक
char_type_p (वृक्ष type)
{
  प्रत्यागम (type == char_type_गाँठ
	  || type == unsigned_char_type_गाँठ
	  || type == signed_char_type_गाँठ
	  || type == char16_type_गाँठ
	  || type == char32_type_गाँठ);
}

/* This is the entry point used by the parser to build binary operators
   in the input.  CODE, a tree_code, specifies the binary operator, and
   ARG1 and ARG2 are the operands.  In addition to constructing the
   expression, we check for operands that were written with other binary
   operators in a way that is likely to confuse the user.  ORIG_ARG1 is
   the original first operand for TRUTH_{AND,OR}IF_EXPR before it is
   converted to truth value, otherwise NULL_TREE.

   LOCATION is the location of the binary operator.  */

संरचना c_व्यंजक
parser_build_द्विआधारी_op (location_t location, गणना वृक्ष_code code,
			संरचना c_व्यंजक arg1, संरचना c_व्यंजक arg2, वृक्ष orig_arg1)
{
  संरचना c_व्यंजक result;
  result.m_decimal = 0;

  गणना वृक्ष_code code1 = arg1.original_code;
  गणना वृक्ष_code code2 = arg2.original_code;
  वृक्ष type1 = (arg1.original_type
                ? arg1.original_type
                : वृक्ष_TYPE (arg1.मूल्य));
  वृक्ष type2 = (arg2.original_type
                ? arg2.original_type
                : वृक्ष_TYPE (arg2.मूल्य));

  result.मूल्य = build_द्विआधारी_op (location, code,
				  arg1.मूल्य, arg2.मूल्य, सत्य);
  result.original_code = code;
  result.original_type = रिक्त;
  result.m_decimal = 0;

  यदि (वृक्ष_CODE (result.मूल्य) == ERROR_MARK)
    {
      set_c_व्यंजक_source_range (&result,
			       arg1.get_start (),
			       arg2.get_finish ());
      प्रत्यागम result;
    }

  यदि (location != UNKNOWN_LOCATION)
    protected_set_व्यंजक_location (result.मूल्य, location);

  set_c_व्यंजक_source_range (&result,
			   arg1.get_start (),
			   arg2.get_finish ());

  /* Check for cases such as x+y<<z which users are likely
     to misinterpret.  */
  यदि (warn_parentheses)
    warn_about_parentheses (location, code, code1, arg1.मूल्य, code2,
			    arg2.मूल्य);

  यदि (warn_logical_op)
    warn_logical_operator (location, code, वृक्ष_TYPE (result.मूल्य),
			   code1, arg1.मूल्य, code2, arg2.मूल्य);

  यदि (warn_constant_logical_operand
      && (code == TRUTH_ANDIF_व्यंजक || code == TRUTH_ORIF_व्यंजक)
      && INTEGRAL_NB_TYPE_P (type1)
      && INTEGRAL_NB_TYPE_P (type2))
    {
      ध्रुव वर्ण *name = code == TRUTH_ANDIF_व्यंजक ? "&&" : "||";
      यदि (orig_arg1 == NULL_वृक्ष)
	orig_arg1 = arg1.मूल्य;
      स्वतः enum_other_than_0_1 = [] (वृक्ष type) {
	यदि (वृक्ष_CODE (type) != ENUMERAL_TYPE)
	  प्रत्यागम असत्य;
	प्रति (वृक्ष l = TYPE_मूल्यावली (type); l; l = वृक्ष_CHAIN (l))
	  {
	    वृक्ष v = DECL_INITIAL (वृक्ष_मूल्य (l));
	    यदि (!integer_zerop (v) && !integer_onep (v))
	      प्रत्यागम सत्य;
	  }
	प्रत्यागम असत्य;
      };
      स्वतः diagnose_constant_logical_operand = [=] (वृक्ष val, वृक्ष type) {
	यदि (वृक्ष_CODE (val) != INTEGER_CST || integer_zerop (val))
	  प्रत्यागम असत्य;
	यदि (integer_onep (val) && !enum_other_than_0_1 (type))
	  प्रत्यागम असत्य;
	gcc_rich_location richloc (location);
	richloc.add_fixit_replace (name + 1);
	auto_diagnostic_group d;
	यदि (warning_at (location, OPT_Wconstant_logical_operand,
			"use of logical %qs with constant operand %qE",
			name, val))
	  inform (&richloc, "use %qs for bitwise operation", name + 1);
	प्रत्यागम सत्य;
      };
      यदि (!diagnose_constant_logical_operand (arg2.मूल्य, type2))
	diagnose_constant_logical_operand (orig_arg1, type1);
    }

  यदि (warn_tautological_compare)
    {
      वृक्ष lhs = arg1.मूल्य;
      वृक्ष rhs = arg2.मूल्य;
      यदि (वृक्ष_CODE (lhs) == C_MAYBE_CONST_व्यंजक)
	{
	  यदि (C_MAYBE_CONST_व्यंजक_PRE (lhs) != NULL_वृक्ष
	      && वृक्ष_SIDE_EFFECTS (C_MAYBE_CONST_व्यंजक_PRE (lhs)))
	    lhs = NULL_वृक्ष;
	  अन्यथा
	    lhs = C_MAYBE_CONST_व्यंजक_व्यंजक (lhs);
	}
      यदि (वृक्ष_CODE (rhs) == C_MAYBE_CONST_व्यंजक)
	{
	  यदि (C_MAYBE_CONST_व्यंजक_PRE (rhs) != NULL_वृक्ष
	      && वृक्ष_SIDE_EFFECTS (C_MAYBE_CONST_व्यंजक_PRE (rhs)))
	    rhs = NULL_वृक्ष;
	  अन्यथा
	    rhs = C_MAYBE_CONST_व्यंजक_व्यंजक (rhs);
	}
      यदि (lhs != NULL_वृक्ष && rhs != NULL_वृक्ष)
	warn_tautological_cmp (location, code, lhs, rhs);
    }

  यदि (warn_logical_not_paren
      && वृक्ष_CODE_CLASS (code) == tcc_comparison
      && code1 == TRUTH_NOT_व्यंजक
      && code2 != TRUTH_NOT_व्यंजक
      /* Avoid warning for !!x == y.  */
      && (वृक्ष_CODE (arg1.मूल्य) != NE_व्यंजक
	  || !integer_zerop (वृक्ष_OPERAND (arg1.मूल्य, 1))))
    {
      /* Avoid warning for !b == y where b has _Bool type.  */
      वृक्ष t = integer_zero_गाँठ;
      यदि (वृक्ष_CODE (arg1.मूल्य) == EQ_व्यंजक
	  && integer_zerop (वृक्ष_OPERAND (arg1.मूल्य, 1))
	  && वृक्ष_TYPE (वृक्ष_OPERAND (arg1.मूल्य, 0)) == integer_type_गाँठ)
	{
	  t = वृक्ष_OPERAND (arg1.मूल्य, 0);
	  कुरु
	    {
	      यदि (वृक्ष_TYPE (t) != integer_type_गाँठ)
		भङ्ग;
	      यदि (वृक्ष_CODE (t) == C_MAYBE_CONST_व्यंजक)
		t = C_MAYBE_CONST_व्यंजक_व्यंजक (t);
	      अन्यथा यदि (CONVERT_व्यंजक_P (t))
		t = वृक्ष_OPERAND (t, 0);
	      अन्यथा
		भङ्ग;
	    }
	  यावत् (1);
	}
      यदि (!C_BOOLEAN_TYPE_P (वृक्ष_TYPE (t)))
	warn_logical_not_parentheses (location, code, arg1.मूल्य, arg2.मूल्य);
    }

  /* Warn about comparisons against string literals, with the exception
     of testing for equality or inequality of a string literal with NULL.  */
  यदि (code == EQ_व्यंजक || code == NE_व्यंजक)
    {
      यदि ((code1 == STRING_CST
	   && !integer_zerop (वृक्ष_strip_nop_conversions (arg2.मूल्य)))
	  || (code2 == STRING_CST
	      && !integer_zerop (वृक्ष_strip_nop_conversions (arg1.मूल्य))))
	warning_at (location, OPT_Waddress,
		    "comparison with string literal results in unspecified behavior");
      /* Warn for ptr == '\0', it's likely that it should've been ptr[0].  */
      यदि (POINTER_TYPE_P (type1)
	  && null_pointer_constant_p (arg2.मूल्य)
	  && char_type_p (type2))
	{
	  auto_diagnostic_group d;
	  यदि (warning_at (location, OPT_Wpointer_compare,
			    "comparison between pointer and zero character "
			    "constant"))
	    inform (arg1.get_start (),
		      "did you mean to dereference the pointer?");
	}
      अन्यथा यदि (POINTER_TYPE_P (type2)
	       && null_pointer_constant_p (arg1.मूल्य)
	       && char_type_p (type1))
	{
	  auto_diagnostic_group d;
	  यदि (warning_at (location, OPT_Wpointer_compare,
			    "comparison between pointer and zero character "
			    "constant"))
	    inform (arg2.get_start (),
		      "did you mean to dereference the pointer?");
	}
    }
  अन्यथा यदि (वृक्ष_CODE_CLASS (code) == tcc_comparison
	   && (code1 == STRING_CST || code2 == STRING_CST))
    warning_at (location, OPT_Waddress,
		"comparison with string literal results in unspecified "
		"behavior");

  यदि (warn_zero_as_null_pointer_constant
      && c_inhibit_evaluation_warnings == 0
      && वृक्ष_CODE_CLASS (code) == tcc_comparison)
    {
      यदि ((वृक्ष_CODE (type1) == POINTER_TYPE
	   || वृक्ष_CODE (type1) == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type2)
	  && null_pointer_constant_p (arg2.मूल्य))
	warning_at (arg2.get_location(), OPT_Wzero_as_null_pointer_constant,
		    "zero as null pointer constant");

      यदि ((वृक्ष_CODE (type2) == POINTER_TYPE
	   || वृक्ष_CODE (type2) == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type1)
	  && null_pointer_constant_p (arg1.मूल्य))
	warning_at (arg1.get_location(), OPT_Wzero_as_null_pointer_constant,
		    "zero as null pointer constant");
    }

  यदि (warn_array_compare
      && वृक्ष_CODE_CLASS (code) == tcc_comparison
      && वृक्ष_CODE (type1) == ARRAY_TYPE
      && वृक्ष_CODE (type2) == ARRAY_TYPE)
    do_warn_array_compare (location, code, arg1.मूल्य, arg2.मूल्य);

  यदि (वृक्ष_OVERFLOW_P (result.मूल्य)
      && !वृक्ष_OVERFLOW_P (arg1.मूल्य)
      && !वृक्ष_OVERFLOW_P (arg2.मूल्य))
    overflow_warning (location, result.मूल्य);

  /* Warn about comparisons of different enum types.  */
  यदि (warn_enum_compare
      && वृक्ष_CODE_CLASS (code) == tcc_comparison
      && वृक्ष_CODE (type1) == ENUMERAL_TYPE
      && वृक्ष_CODE (type2) == ENUMERAL_TYPE
      && TYPE_MAIN_VARIANT (type1) != TYPE_MAIN_VARIANT (type2))
    warning_at (location, OPT_Wenum_compare,
		"comparison between %qT and %qT",
		type1, type2);

  यदि (warn_xor_used_as_pow
      && code == BIT_XOR_व्यंजक
      && arg1.m_decimal
      && arg2.m_decimal)
    check_for_xor_used_as_pow (arg1.get_location (), arg1.मूल्य,
			       location,
			       arg2.get_location (), arg2.मूल्य);

  प्रत्यागम result;
}

/* Return a tree for the difference of pointers OP0 and OP1.
   The resulting tree has type ptrdiff_t.  If POINTER_SUBTRACT sanitization is
   enabled, assign to INSTRUMENT_EXPR call to libsanitizer.  */

स्थिर वृक्ष
pointer_diff (location_t loc, वृक्ष op0, वृक्ष op1, वृक्ष *instrument_व्यंजक)
{
  वृक्ष restype = ptrdiff_type_गाँठ;
  वृक्ष result, inttype;

  addr_space_t as0 = TYPE_ADDR_SPACE (वृक्ष_TYPE (वृक्ष_TYPE (op0)));
  addr_space_t as1 = TYPE_ADDR_SPACE (वृक्ष_TYPE (वृक्ष_TYPE (op1)));
  वृक्ष target_type = वृक्ष_TYPE (वृक्ष_TYPE (op0));
  वृक्ष orig_op0 = op0;
  वृक्ष orig_op1 = op1;

  /* If the operands point into different address spaces, we need to
     explicitly convert them to pointers into the common address space
     before we can subtract the numerical address values.  */
  यदि (as0 != as1)
    {
      addr_space_t as_common;
      वृक्ष common_type;

      /* Determine the common superset address space.  This is guaranteed
	 to exist because the caller verified that comp_target_types
	 returned non-zero.  */
      यदि (!addr_space_superset (as0, as1, &as_common))
	gcc_unreachable ();

      common_type = common_pointer_type (वृक्ष_TYPE (op0), वृक्ष_TYPE (op1), NULL_वृक्ष);
      op0 = convert (common_type, op0);
      op1 = convert (common_type, op1);
    }

  /* Determine integer type result of the subtraction.  This will usually
     be the same as the result type (ptrdiff_t), but may need to be a wider
     type if pointers for the address space are wider than ptrdiff_t.  */
  यदि (TYPE_PRECISION (restype) < TYPE_PRECISION (वृक्ष_TYPE (op0)))
    inttype = c_common_type_for_size (TYPE_PRECISION (वृक्ष_TYPE (op0)), 0);
  अन्यथा
    inttype = restype;

  यदि (VOID_TYPE_P (target_type))
    pedwarn (loc, OPT_Wpointer_arith,
	     "pointer of type %<void *%> used in subtraction");
  यदि (वृक्ष_CODE (target_type) == FUNCTION_TYPE)
    pedwarn (loc, OPT_Wpointer_arith,
	     "pointer to a function used in subtraction");

  यदि (current_function_decl != NULL_वृक्ष
      && sanitize_flags_p (SANITIZE_POINTER_SUBTRACT))
    {
      op0 = save_व्यंजक (c_fully_fold (op0, असत्य, रिक्त));
      op1 = save_व्यंजक (c_fully_fold (op1, असत्य, रिक्त));

      वृक्ष tt = builtin_decl_explicit (BUILT_IN_ASAN_POINTER_SUBTRACT);
      *instrument_व्यंजक = build_call_व्यंजक_loc (loc, tt, 2, op0, op1);
    }

  /* First do the subtraction, then build the divide operator
     and only convert at the very end.
     Do not do default conversions in case restype is a short type.  */

  /* POINTER_DIFF_EXPR requires a signed integer type of the same size as
     pointers.  If some platform cannot provide that, or has a larger
     ptrdiff_type to support differences larger than half the address
     space, cast the pointers to some larger integer type and do the
     computations in that type.  */
  यदि (TYPE_PRECISION (inttype) > TYPE_PRECISION (वृक्ष_TYPE (op0)))
    op0 = build_द्विआधारी_op (loc, MINUS_व्यंजक, convert (inttype, op0),
			   convert (inttype, op1), असत्य);
  अन्यथा
    {
      /* Cast away qualifiers.  */
      op0 = convert (c_common_type (वृक्ष_TYPE (op0), वृक्ष_TYPE (op0)), op0);
      op1 = convert (c_common_type (वृक्ष_TYPE (op1), वृक्ष_TYPE (op1)), op1);
      op0 = build2_loc (loc, POINTER_DIFF_व्यंजक, inttype, op0, op1);
    }

  /* This generates an error if op1 is pointer to incomplete type.  */
  यदि (!COMPLETE_OR_VOID_TYPE_P (वृक्ष_TYPE (वृक्ष_TYPE (orig_op1))))
    error_at (loc, "arithmetic on pointer to an incomplete type");
  अन्यथा यदि (verify_type_context (loc, TCTX_POINTER_ARITH,
				वृक्ष_TYPE (वृक्ष_TYPE (orig_op0))))
    verify_type_context (loc, TCTX_POINTER_ARITH,
			 वृक्ष_TYPE (वृक्ष_TYPE (orig_op1)));

  op1 = c_size_in_bytes (target_type);

  यदि (pointer_to_zero_sized_aggr_p (वृक्ष_TYPE (orig_op1)))
    error_at (loc, "arithmetic on pointer to an empty aggregate");

  /* Divide by the size, in easiest possible way.  */
  result = fold_build2_loc (loc, EXACT_DIV_व्यंजक, inttype,
			    op0, convert (inttype, op1));

  /* Convert to final result type if necessary.  */
  प्रत्यागम convert (restype, result);
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

स्थिर वृक्ष
build_atomic_assign (location_t loc, वृक्ष lhs, गणना वृक्ष_code modifycode,
		     वृक्ष rhs, तार्किक return_old_p)
{
  वृक्ष fndecl, func_call;
  vec<वृक्ष, va_gc> *params;
  वृक्ष val, nonatomic_lhs_type, nonatomic_rhs_type, newval, newval_addr;
  वृक्ष old, old_addr;
  वृक्ष compound_stmt = NULL_वृक्ष;
  वृक्ष stmt, goto_stmt;
  वृक्ष loop_label, loop_decl, done_label, done_decl;

  वृक्ष lhs_type = वृक्ष_TYPE (lhs);
  वृक्ष lhs_addr = build_unary_op (loc, ADDR_व्यंजक, lhs, असत्य);
  वृक्ष seq_cst = build_int_cst (integer_type_गाँठ, MEMMODEL_SEQ_CST);
  वृक्ष rhs_semantic_type = वृक्ष_TYPE (rhs);
  वृक्ष nonatomic_rhs_semantic_type;
  वृक्ष rhs_type;

  gcc_assert (TYPE_ATOMIC (lhs_type));

  यदि (return_old_p)
    gcc_assert (modifycode == PLUS_व्यंजक || modifycode == MINUS_व्यंजक);

  /* Allocate enough vector items for a compare_exchange.  */
  vec_alloc (params, 6);

  /* Create a compound statement to hold the sequence of statements
     with a loop.  */
  यदि (modifycode != NOP_व्यंजक)
    {
      compound_stmt = c_begin_compound_stmt (असत्य);

      /* For consistency with build_modify_expr on non-_Atomic,
	 mark the lhs as read.  Also, it would be very hard to match
	 such expressions in mark_exp_read.  */
      mark_exp_read (lhs);
    }

  /* Remove any excess precision (which is only present here in the
     case of compound assignments).  */
  यदि (वृक्ष_CODE (rhs) == EXCESS_PRECISION_व्यंजक)
    {
      gcc_assert (modifycode != NOP_व्यंजक);
      rhs = वृक्ष_OPERAND (rhs, 0);
    }
  rhs_type = वृक्ष_TYPE (rhs);

  /* Fold the RHS if it hasn't already been folded.  */
  यदि (modifycode != NOP_व्यंजक)
    rhs = c_fully_fold (rhs, असत्य, रिक्त);

  /* Remove the qualifiers for the rest of the expressions and create
     the VAL temp variable to hold the RHS.  */
  nonatomic_lhs_type = build_qualified_type (lhs_type, TYPE_UNQUALIFIED);
  nonatomic_rhs_type = build_qualified_type (rhs_type, TYPE_UNQUALIFIED);
  nonatomic_rhs_semantic_type = build_qualified_type (rhs_semantic_type,
						      TYPE_UNQUALIFIED);
  val = create_tmp_var_raw (nonatomic_rhs_type);
  वृक्ष_ADDRESSABLE (val) = 1;
  suppress_warning (val);
  rhs = build4 (TARGET_व्यंजक, nonatomic_rhs_type, val, rhs, NULL_वृक्ष,
		NULL_वृक्ष);
  वृक्ष_SIDE_EFFECTS (rhs) = 1;
  SET_व्यंजक_LOCATION (rhs, loc);
  यदि (modifycode != NOP_व्यंजक)
    add_stmt (rhs);

  /* NOP_EXPR indicates it's a straight store of the RHS. Simply issue
     an atomic_store.  */
  यदि (modifycode == NOP_व्यंजक)
    {
      compound_stmt = rhs;
      /* Build __atomic_store (&lhs, &val, SEQ_CST)  */
      rhs = build_unary_op (loc, ADDR_व्यंजक, val, असत्य);
      fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_STORE);
      params->quick_धकेलो (lhs_addr);
      params->quick_धकेलो (rhs);
      params->quick_धकेलो (seq_cst);
      func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, रिक्त);

      compound_stmt = build2 (COMPOUND_व्यंजक, void_type_गाँठ,
			      compound_stmt, func_call);

      /* VAL is the value which was stored, return a COMPOUND_STMT of
	 the statement and that value.  */
      प्रत्यागम build2 (COMPOUND_व्यंजक, nonatomic_lhs_type, compound_stmt, val);
    }

  /* Attempt to implement the atomic operation as an __atomic_fetch_* or
     __atomic_*_fetch built-in rather than a CAS loop.  atomic_bool type
     isn't applicable for such builtins.  ??? Do we want to handle enums?  */
  यदि ((वृक्ष_CODE (lhs_type) == INTEGER_TYPE || POINTER_TYPE_P (lhs_type))
      && वृक्ष_CODE (rhs_type) == INTEGER_TYPE)
    {
      built_in_function fncode;
      विकल्प (modifycode)
	{
	पक्ष PLUS_व्यंजक:
	पक्ष POINTER_PLUS_व्यंजक:
	  fncode = (return_old_p
		    ? BUILT_IN_ATOMIC_FETCH_ADD_N
		    : BUILT_IN_ATOMIC_ADD_FETCH_N);
	  भङ्ग;
	पक्ष MINUS_व्यंजक:
	  fncode = (return_old_p
		    ? BUILT_IN_ATOMIC_FETCH_SUB_N
		    : BUILT_IN_ATOMIC_SUB_FETCH_N);
	  भङ्ग;
	पक्ष BIT_AND_व्यंजक:
	  fncode = (return_old_p
		    ? BUILT_IN_ATOMIC_FETCH_AND_N
		    : BUILT_IN_ATOMIC_AND_FETCH_N);
	  भङ्ग;
	पक्ष BIT_IOR_व्यंजक:
	  fncode = (return_old_p
		    ? BUILT_IN_ATOMIC_FETCH_OR_N
		    : BUILT_IN_ATOMIC_OR_FETCH_N);
	  भङ्ग;
	पक्ष BIT_XOR_व्यंजक:
	  fncode = (return_old_p
		    ? BUILT_IN_ATOMIC_FETCH_XOR_N
		    : BUILT_IN_ATOMIC_XOR_FETCH_N);
	  भङ्ग;
	स्वभाव:
	  गच्छ cas_loop;
	}

      /* We can only use "_1" through "_16" variants of the atomic fetch
	 built-ins.  */
      अचिन्हित HOST_WIDE_INT size = वृक्ष_to_uhwi (TYPE_SIZE_UNIT (lhs_type));
      यदि (size != 1 && size != 2 && size != 4 && size != 8 && size != 16)
	गच्छ cas_loop;

      /* If this is a pointer type, we need to multiply by the size of
	 the pointer target type.  */
      यदि (POINTER_TYPE_P (lhs_type))
	{
	  यदि (!COMPLETE_TYPE_P (वृक्ष_TYPE (lhs_type))
	      /* ??? This would introduce -Wdiscarded-qualifiers
		 warning: __atomic_fetch_* expect volatile void *
		 type as the first argument.  (Assignments between
		 atomic and non-atomic objects are OK.) */
	      || TYPE_RESTRICT (lhs_type))
	    गच्छ cas_loop;
	  वृक्ष sz = TYPE_SIZE_UNIT (वृक्ष_TYPE (lhs_type));
	  rhs = fold_build2_loc (loc, MULT_व्यंजक, ptrdiff_type_गाँठ,
				 convert (ptrdiff_type_गाँठ, rhs),
				 convert (ptrdiff_type_गाँठ, sz));
	}

      /* Build __atomic_fetch_* (&lhs, &val, SEQ_CST), or
	 __atomic_*_fetch (&lhs, &val, SEQ_CST).  */
      fndecl = builtin_decl_explicit (fncode);
      params->quick_धकेलो (lhs_addr);
      params->quick_धकेलो (rhs);
      params->quick_धकेलो (seq_cst);
      func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, रिक्त);

      newval = create_tmp_var_raw (nonatomic_lhs_type);
      वृक्ष_ADDRESSABLE (newval) = 1;
      suppress_warning (newval);
      rhs = build4 (TARGET_व्यंजक, nonatomic_lhs_type, newval, func_call,
		    NULL_वृक्ष, NULL_वृक्ष);
      SET_व्यंजक_LOCATION (rhs, loc);
      add_stmt (rhs);

      /* Finish the compound statement.  */
      compound_stmt = c_end_compound_stmt (loc, compound_stmt, असत्य);

      /* NEWVAL is the value which was stored, return a COMPOUND_STMT of
	 the statement and that value.  */
      प्रत्यागम build2 (COMPOUND_व्यंजक, nonatomic_lhs_type, compound_stmt, newval);
    }

cas_loop:
  /* Create the variables and labels required for the op= form.  */
  old = create_tmp_var_raw (nonatomic_lhs_type);
  old_addr = build_unary_op (loc, ADDR_व्यंजक, old, असत्य);
  वृक्ष_ADDRESSABLE (old) = 1;
  suppress_warning (old);

  newval = create_tmp_var_raw (nonatomic_lhs_type);
  newval_addr = build_unary_op (loc, ADDR_व्यंजक, newval, असत्य);
  वृक्ष_ADDRESSABLE (newval) = 1;
  suppress_warning (newval);

  loop_decl = create_artificial_label (loc);
  loop_label = build1 (LABEL_व्यंजक, void_type_गाँठ, loop_decl);

  done_decl = create_artificial_label (loc);
  done_label = build1 (LABEL_व्यंजक, void_type_गाँठ, done_decl);

  /* __atomic_load (addr, &old, SEQ_CST).  */
  fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_LOAD);
  params->quick_धकेलो (lhs_addr);
  params->quick_धकेलो (old_addr);
  params->quick_धकेलो (seq_cst);
  func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, रिक्त);
  old = build4 (TARGET_व्यंजक, nonatomic_lhs_type, old, func_call, NULL_वृक्ष,
		NULL_वृक्ष);
  add_stmt (old);
  params->truncate (0);

  /* Create the expressions for floating-point environment
     manipulation, if required.  */
  तार्किक need_fenv = (flag_trapping_math
		    && (FLOAT_TYPE_P (lhs_type) || FLOAT_TYPE_P (rhs_type)));
  वृक्ष hold_call = NULL_वृक्ष, clear_call = NULL_वृक्ष, update_call = NULL_वृक्ष;
  यदि (need_fenv)
    targetm.atomic_assign_expand_fenv (&hold_call, &clear_call, &update_call);

  यदि (hold_call)
    add_stmt (hold_call);

  /* loop:  */
  add_stmt (loop_label);

  /* newval = old + val;  */
  यदि (rhs_type != rhs_semantic_type)
    val = build1 (EXCESS_PRECISION_व्यंजक, nonatomic_rhs_semantic_type, val);
  rhs = build_द्विआधारी_op (loc, modifycode,
			 convert_lvalue_to_rvalue (loc, old, सत्य, सत्य),
			 val, सत्य);
  यदि (वृक्ष_CODE (rhs) == EXCESS_PRECISION_व्यंजक)
    {
      वृक्ष eptype = वृक्ष_TYPE (rhs);
      rhs = c_fully_fold (वृक्ष_OPERAND (rhs, 0), असत्य, रिक्त);
      rhs = build1 (EXCESS_PRECISION_व्यंजक, eptype, rhs);
    }
  अन्यथा
    rhs = c_fully_fold (rhs, असत्य, रिक्त);
  rhs = convert_for_assignment (loc, UNKNOWN_LOCATION, nonatomic_lhs_type,
				rhs, NULL_वृक्ष, ic_assign, असत्य, NULL_वृक्ष,
				NULL_वृक्ष, 0);
  /* The temporary variable for NEWVAL is only gimplified correctly (in
     particular, given a DECL_CONTEXT) if used in a TARGET_EXPR.  To avoid
     subsequent ICEs in nested function processing after an error, ensure such
     a TARGET_EXPR is built even after an error.  */
  यदि (rhs == error_mark_गाँठ)
    rhs = old;
  rhs = build4 (TARGET_व्यंजक, nonatomic_lhs_type, newval, rhs, NULL_वृक्ष,
		NULL_वृक्ष);
  SET_व्यंजक_LOCATION (rhs, loc);
  add_stmt (rhs);

  /* if (__atomic_compare_exchange (addr, &old, &new, false, SEQ_CST, SEQ_CST))
       goto done;  */
  fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_COMPARE_EXCHANGE);
  params->quick_धकेलो (lhs_addr);
  params->quick_धकेलो (old_addr);
  params->quick_धकेलो (newval_addr);
  params->quick_धकेलो (integer_zero_गाँठ);
  params->quick_धकेलो (seq_cst);
  params->quick_धकेलो (seq_cst);
  func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, रिक्त);

  goto_stmt = build1 (GOTO_व्यंजक, void_type_गाँठ, done_decl);
  SET_व्यंजक_LOCATION (goto_stmt, loc);

  stmt = build3 (COND_व्यंजक, void_type_गाँठ, func_call, goto_stmt, NULL_वृक्ष);
  SET_व्यंजक_LOCATION (stmt, loc);
  add_stmt (stmt);

  यदि (clear_call)
    add_stmt (clear_call);

  /* goto loop;  */
  goto_stmt  = build1 (GOTO_व्यंजक, void_type_गाँठ, loop_decl);
  SET_व्यंजक_LOCATION (goto_stmt, loc);
  add_stmt (goto_stmt);

  /* done:  */
  add_stmt (done_label);

  यदि (update_call)
    add_stmt (update_call);

  /* Finish the compound statement.  */
  compound_stmt = c_end_compound_stmt (loc, compound_stmt, असत्य);

  /* NEWVAL is the value that was successfully stored, return a
     COMPOUND_EXPR of the statement and the appropriate value.  */
  प्रत्यागम build2 (COMPOUND_व्यंजक, nonatomic_lhs_type, compound_stmt,
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

वृक्ष
build_unary_op (location_t location, गणना वृक्ष_code code, वृक्ष xarg,
		तार्किक noconvert)
{
  /* No default_conversion here.  It causes trouble for ADDR_EXPR.  */
  वृक्ष arg = xarg;
  वृक्ष argtype = NULL_वृक्ष;
  गणना वृक्ष_code typecode;
  वृक्ष val;
  वृक्ष ret = error_mark_गाँठ;
  वृक्ष eptype = NULL_वृक्ष;
  ध्रुव वर्ण *invalid_op_diag;

  /* If ARG is wrapped in a call to .ACCESS_WITH_SIZE — created when the
     C parser rvalue-converts a counted_by-annotated member access (see
     PR123569) — unwrap it here.  Unary operators that consume an rvalue
     (!, -, +) read the value itself rather than dereferencing into the
     pointed-to data, so the bounds-checking wrapper is unnecessary and
     would otherwise reach build_unary_op while it is not equipped to
     handle the wrapped form.  PR123569 fixed the ++/-- side of this by
     suppressing wrapper creation in the parser; the rvalue-consuming
     ops still receive the wrapper and need to strip it here.  */
  यदि (is_access_with_size_p (arg))
    xarg = arg = get_ref_from_access_with_size (arg);

  gcc_checking_assert (!is_access_with_size_p (arg));

  तार्किक int_operands = व्यंजक_INT_CONST_OPERANDS (xarg);
  यदि (int_operands)
    arg = remove_c_maybe_const_व्यंजक (arg);

  यदि (code != ADDR_व्यंजक)
    arg = require_complete_type (location, arg);

  typecode = वृक्ष_CODE (वृक्ष_TYPE (arg));
  यदि (typecode == ERROR_MARK)
    प्रत्यागम error_mark_गाँठ;
  यदि (typecode == ENUMERAL_TYPE || typecode == BOOLEAN_TYPE)
    typecode = INTEGER_TYPE;

  यदि ((invalid_op_diag
       = targetm.invalid_unary_op (code, वृक्ष_TYPE (xarg))))
    {
      error_at (location, invalid_op_diag);
      प्रत्यागम error_mark_गाँठ;
    }

  यदि (वृक्ष_CODE (arg) == EXCESS_PRECISION_व्यंजक)
    {
      eptype = वृक्ष_TYPE (arg);
      arg = वृक्ष_OPERAND (arg, 0);
    }

  विकल्प (code)
    {
    पक्ष CONVERT_व्यंजक:
      /* This is used for unary plus, because a CONVERT_EXPR
	 is enough to prevent anybody from looking inside for
	 associativity, but won't generate any code.  */
      यदि (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE
	    || typecode == FIXED_POINT_TYPE || typecode == COMPLEX_TYPE
	    || typecode == BITINT_TYPE
	    || gnu_vector_type_p (वृक्ष_TYPE (arg))))
	{
	  error_at (location, "wrong type argument to unary plus");
	  प्रत्यागम error_mark_गाँठ;
	}
      अन्यथा यदि (!noconvert)
	arg = default_conversion (arg);
      arg = non_lvalue_loc (location, arg);
      भङ्ग;

    पक्ष NEGATE_व्यंजक:
      यदि (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE
	    || typecode == FIXED_POINT_TYPE || typecode == COMPLEX_TYPE
	    || typecode == BITINT_TYPE
	    || gnu_vector_type_p (वृक्ष_TYPE (arg))))
	{
	  error_at (location, "wrong type argument to unary minus");
	  प्रत्यागम error_mark_गाँठ;
	}
      अन्यथा यदि (!noconvert)
	arg = default_conversion (arg);
      भङ्ग;

    पक्ष BIT_NOT_व्यंजक:
      /* ~ works on integer types and non float vectors. */
      यदि (typecode == INTEGER_TYPE
	  || typecode == BITINT_TYPE
	  || (gnu_vector_type_p (वृक्ष_TYPE (arg))
	      && !VECTOR_FLOAT_TYPE_P (वृक्ष_TYPE (arg))))
	{
	  वृक्ष e = arg;

	  /* Warn if the expression has boolean value.  */
	  यावत् (वृक्ष_CODE (e) == COMPOUND_व्यंजक)
	    e = वृक्ष_OPERAND (e, 1);

	  यदि ((C_BOOLEAN_TYPE_P (वृक्ष_TYPE (arg))
	       || truth_मूल्य_p (वृक्ष_CODE (e))))
	    {
	      auto_diagnostic_group d;
	      यदि (warning_at (location, OPT_Wbool_operation,
				"%<~%> on a boolean expression"))
		{
		  gcc_rich_location richloc (location);
		  richloc.add_fixit_जोड़ो_before (location, "!");
		  inform (&richloc, "did you mean to use logical not?");
		}
	    }
	  यदि (!noconvert)
	    arg = default_conversion (arg);
	}
      अन्यथा यदि (typecode == COMPLEX_TYPE)
	{
	  code = CONJ_व्यंजक;
	  pedwarn (location, OPT_Wpedantic,
		   "ISO C does not support %<~%> for complex conjugation");
	  यदि (!noconvert)
	    arg = default_conversion (arg);
	}
      अन्यथा
	{
	  error_at (location, "wrong type argument to bit-complement");
	  प्रत्यागम error_mark_गाँठ;
	}
      भङ्ग;

    पक्ष ABS_व्यंजक:
      यदि (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE))
	{
	  error_at (location, "wrong type argument to abs");
	  प्रत्यागम error_mark_गाँठ;
	}
      अन्यथा यदि (!noconvert)
	arg = default_conversion (arg);
      भङ्ग;

    पक्ष ABSU_व्यंजक:
      यदि (!(typecode == INTEGER_TYPE))
	{
	  error_at (location, "wrong type argument to absu");
	  प्रत्यागम error_mark_गाँठ;
	}
      अन्यथा यदि (!noconvert)
	arg = default_conversion (arg);
      भङ्ग;

    पक्ष CONJ_व्यंजक:
      /* Conjugating a real value is a no-op, but allow it anyway.  */
      यदि (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE
	    || typecode == COMPLEX_TYPE))
	{
	  error_at (location, "wrong type argument to conjugation");
	  प्रत्यागम error_mark_गाँठ;
	}
      अन्यथा यदि (!noconvert)
	arg = default_conversion (arg);
      भङ्ग;

    पक्ष TRUTH_NOT_व्यंजक:
      यदि (typecode != INTEGER_TYPE && typecode != FIXED_POINT_TYPE
	  && typecode != REAL_TYPE && typecode != POINTER_TYPE
	  && typecode != COMPLEX_TYPE && typecode != NULLPTR_TYPE
	  && typecode != BITINT_TYPE)
	{
	  error_at (location,
		    "wrong type argument to unary exclamation mark");
	  प्रत्यागम error_mark_गाँठ;
	}
      यदि (int_operands)
	{
	  arg = c_objc_common_truthvalue_conversion (location, xarg);
	  arg = remove_c_maybe_const_व्यंजक (arg);
	}
      अन्यथा
	arg = c_objc_common_truthvalue_conversion (location, arg);
      ret = invert_truthvalue_loc (location, arg);
      eptype = NULL_वृक्ष;
      /* If the TRUTH_NOT_EXPR has been folded, reset the location.  */
      यदि (व्यंजक_P (ret) && व्यंजक_HAS_LOCATION (ret))
	location = व्यंजक_LOCATION (ret);
      गच्छ return_build_unary_op;

    पक्ष REALPART_व्यंजक:
    पक्ष IMAGPART_व्यंजक:
      ret = build_real_imag_व्यंजक (location, code, arg);
      यदि (ret == error_mark_गाँठ)
	प्रत्यागम error_mark_गाँठ;
      यदि (eptype && वृक्ष_CODE (eptype) == COMPLEX_TYPE)
	eptype = वृक्ष_TYPE (eptype);
      गच्छ return_build_unary_op;

    पक्ष PREINCREMENT_व्यंजक:
    पक्ष POSTINCREMENT_व्यंजक:
    पक्ष PREDECREMENT_व्यंजक:
    पक्ष POSTDECREMENT_व्यंजक:

      यदि (वृक्ष_CODE (arg) == C_MAYBE_CONST_व्यंजक)
	{
	  वृक्ष inner = build_unary_op (location, code,
				       C_MAYBE_CONST_व्यंजक_व्यंजक (arg),
				       noconvert);
	  यदि (inner == error_mark_गाँठ)
	    प्रत्यागम error_mark_गाँठ;
	  ret = build2 (C_MAYBE_CONST_व्यंजक, वृक्ष_TYPE (inner),
			C_MAYBE_CONST_व्यंजक_PRE (arg), inner);
	  gcc_assert (!C_MAYBE_CONST_व्यंजक_INT_OPERANDS (arg));
	  C_MAYBE_CONST_व्यंजक_NON_CONST (ret) = 1;
	  गच्छ return_build_unary_op;
	}

      /* Complain about anything that is not a true lvalue.  In
	 Objective-C, skip this check for property_refs.  */
      यदि (!objc_is_property_ref (arg)
	  && !lvalue_or_else (location,
			      arg, ((code == PREINCREMENT_व्यंजक
				     || code == POSTINCREMENT_व्यंजक)
				    ? lv_increment
				    : lv_decrement)))
	प्रत्यागम error_mark_गाँठ;

      यदि (warn_cxx_compat && वृक्ष_CODE (वृक्ष_TYPE (arg)) == ENUMERAL_TYPE)
	{
	  यदि (code == PREINCREMENT_व्यंजक || code == POSTINCREMENT_व्यंजक)
	    warning_at (location, OPT_Wc___compat,
			"increment of enumeration value is invalid in C++");
	  अन्यथा
	    warning_at (location, OPT_Wc___compat,
			"decrement of enumeration value is invalid in C++");
	}

      यदि (C_BOOLEAN_TYPE_P (वृक्ष_TYPE (arg)))
	{
	  यदि (code == PREINCREMENT_व्यंजक || code == POSTINCREMENT_व्यंजक)
	    warning_at (location, OPT_Wbool_operation,
			"increment of a boolean expression");
	  अन्यथा
	    warning_at (location, OPT_Wbool_operation,
			"decrement of a boolean expression");
	}

      /* Ensure the argument is fully folded inside any SAVE_EXPR.  */
      arg = c_fully_fold (arg, असत्य, रिक्त, सत्य);

      तार्किक atomic_op;
      atomic_op = really_atomic_lvalue (arg);

      /* Increment or decrement the real part of the value,
	 and don't change the imaginary part.  */
      यदि (typecode == COMPLEX_TYPE)
	{
	  वृक्ष real, imag;

	  pedwarn_c23 (location, OPT_Wpedantic,
		       "ISO C does not support %<++%> and %<--%> on complex "
		       "types before C2Y");

	  यदि (!atomic_op)
	    {
	      arg = stabilize_reference (arg);
	      real = build_unary_op (व्यंजक_LOCATION (arg), REALPART_व्यंजक, arg,
				     सत्य);
	      imag = build_unary_op (व्यंजक_LOCATION (arg), IMAGPART_व्यंजक, arg,
				     सत्य);
	      real = build_unary_op (व्यंजक_LOCATION (arg), code, real, सत्य);
	      यदि (real == error_mark_गाँठ || imag == error_mark_गाँठ)
		प्रत्यागम error_mark_गाँठ;
	      ret = build2 (COMPLEX_व्यंजक, वृक्ष_TYPE (arg),
			    real, imag);
	      गच्छ return_build_unary_op;
	    }
	}

      /* Report invalid types.  */

      यदि (typecode != POINTER_TYPE && typecode != FIXED_POINT_TYPE
	  && typecode != INTEGER_TYPE && typecode != REAL_TYPE
	  && typecode != COMPLEX_TYPE && typecode != BITINT_TYPE
	  && !gnu_vector_type_p (वृक्ष_TYPE (arg)))
	{
	  यदि (code == PREINCREMENT_व्यंजक || code == POSTINCREMENT_व्यंजक)
	    error_at (location, "wrong type argument to increment");
	  अन्यथा
	    error_at (location, "wrong type argument to decrement");

	  प्रत्यागम error_mark_गाँठ;
	}

      {
	वृक्ष inc;

	argtype = वृक्ष_TYPE (arg);

	/* Compute the increment.  */

	यदि (typecode == POINTER_TYPE)
	  {
	    /* If pointer target is an incomplete type,
	       we just cannot know how to do the arithmetic.  */
	    यदि (!COMPLETE_OR_VOID_TYPE_P (वृक्ष_TYPE (argtype)))
	      {
		यदि (code == PREINCREMENT_व्यंजक || code == POSTINCREMENT_व्यंजक)
		  error_at (location,
			    "increment of pointer to an incomplete type %qT",
			    वृक्ष_TYPE (argtype));
		अन्यथा
		  error_at (location,
			    "decrement of pointer to an incomplete type %qT",
			    वृक्ष_TYPE (argtype));
	      }
	    अन्यथा यदि (वृक्ष_CODE (वृक्ष_TYPE (argtype)) == FUNCTION_TYPE
		     || VOID_TYPE_P (वृक्ष_TYPE (argtype)))
	      {
		यदि (code == PREINCREMENT_व्यंजक || code == POSTINCREMENT_व्यंजक)
		  pedwarn (location, OPT_Wpointer_arith,
			   "wrong type argument to increment");
		अन्यथा
		  pedwarn (location, OPT_Wpointer_arith,
			   "wrong type argument to decrement");
	      }
	    अन्यथा
	      verify_type_context (location, TCTX_POINTER_ARITH,
				   वृक्ष_TYPE (argtype));

	    inc = c_size_in_bytes (वृक्ष_TYPE (argtype));
	    inc = convert_to_ptrofftype_loc (location, inc);
	  }
	अन्यथा यदि (FRACT_MODE_P (TYPE_MODE (argtype)))
	  {
	    /* For signed fract types, we invert ++ to -- or
	       -- to ++, and change inc from 1 to -1, because
	       it is not possible to represent 1 in signed fract constants.
	       For unsigned fract types, the result always overflows and
	       we get an undefined (original) or the maximum value.  */
	    यदि (code == PREINCREMENT_व्यंजक)
	      code = PREDECREMENT_व्यंजक;
	    अन्यथा यदि (code == PREDECREMENT_व्यंजक)
	      code = PREINCREMENT_व्यंजक;
	    अन्यथा यदि (code == POSTINCREMENT_व्यंजक)
	      code = POSTDECREMENT_व्यंजक;
	    अन्यथा /* code == POSTDECREMENT_EXPR  */
	      code = POSTINCREMENT_व्यंजक;

	    inc = integer_minus_one_गाँठ;
	    inc = convert (argtype, inc);
	  }
	अन्यथा
	  {
	    inc = VECTOR_TYPE_P (argtype)
	      ? build_one_cst (argtype)
	      : integer_one_गाँठ;
	    inc = convert (argtype, inc);
	  }

	/* If 'arg' is an Objective-C PROPERTY_REF expression, then we
	   need to ask Objective-C to build the increment or decrement
	   expression for it.  */
	यदि (objc_is_property_ref (arg))
	  प्रत्यागम objc_build_incr_व्यंजक_for_property_ref (location, code,
							arg, inc);

	/* Report a read-only lvalue.  */
	यदि (TYPE_READONLY (argtype))
	  {
	    readonly_error (location, arg,
			    ((code == PREINCREMENT_व्यंजक
			      || code == POSTINCREMENT_व्यंजक)
			     ? lv_increment : lv_decrement));
	    प्रत्यागम error_mark_गाँठ;
	  }
	अन्यथा यदि (वृक्ष_READONLY (arg))
	  readonly_warning (arg,
			    ((code == PREINCREMENT_व्यंजक
			      || code == POSTINCREMENT_व्यंजक)
			     ? lv_increment : lv_decrement));

	/* If the argument is atomic, use the special code sequences for
	   atomic compound assignment.  */
	यदि (atomic_op)
	  {
	    arg = stabilize_reference (arg);
	    ret = build_atomic_assign (location, arg,
				       ((code == PREINCREMENT_व्यंजक
					 || code == POSTINCREMENT_व्यंजक)
					? PLUS_व्यंजक
					: MINUS_व्यंजक),
				       (FRACT_MODE_P (TYPE_MODE (argtype))
					? inc
					: integer_one_गाँठ),
				       (code == POSTINCREMENT_व्यंजक
					|| code == POSTDECREMENT_व्यंजक));
	    गच्छ return_build_unary_op;
	  }

	वृक्ष true_res;
	यदि (c_hardbool_type_attr (वृक्ष_TYPE (arg), रिक्त, &true_res))
	  {
	    वृक्ष larg = stabilize_reference (arg);
	    वृक्ष sarg = save_व्यंजक (larg);
	    विकल्प (code)
	      {
	      पक्ष PREINCREMENT_व्यंजक:
		val = build2 (MODIFY_व्यंजक, वृक्ष_TYPE (larg), larg, true_res);
		val = build2 (COMPOUND_व्यंजक, वृक्ष_TYPE (larg), sarg, val);
		भङ्ग;
	      पक्ष POSTINCREMENT_व्यंजक:
		val = build2 (MODIFY_व्यंजक, वृक्ष_TYPE (larg), larg, true_res);
		val = build2 (COMPOUND_व्यंजक, वृक्ष_TYPE (larg), val, sarg);
		val = build2 (COMPOUND_व्यंजक, वृक्ष_TYPE (larg), sarg, val);
		भङ्ग;
	      पक्ष PREDECREMENT_व्यंजक:
		{
		  वृक्ष rarg = convert_lvalue_to_rvalue (location, sarg,
							सत्य, सत्य);
		  rarg = invert_truthvalue_loc (location, rarg);
		  rarg = convert (वृक्ष_TYPE (sarg), rarg);
		  val = build2 (MODIFY_व्यंजक, वृक्ष_TYPE (larg), larg, rarg);
		}
		भङ्ग;
	      पक्ष POSTDECREMENT_व्यंजक:
		{
		  वृक्ष rarg = convert_lvalue_to_rvalue (location, sarg,
							सत्य, सत्य);
		  rarg = invert_truthvalue_loc (location, rarg);
		  वृक्ष iarg = convert (वृक्ष_TYPE (larg), rarg);
		  val = build2 (MODIFY_व्यंजक, वृक्ष_TYPE (larg), larg, iarg);
		  val = build2 (COMPOUND_व्यंजक, वृक्ष_TYPE (larg), val, sarg);
		  val = build2 (COMPOUND_व्यंजक, वृक्ष_TYPE (larg), sarg, val);
		}
		भङ्ग;
	      स्वभाव:
		gcc_unreachable ();
	      }
	    वृक्ष_SIDE_EFFECTS (val) = 1;
	  }
	अन्यथा यदि (C_BOOLEAN_TYPE_P (वृक्ष_TYPE (arg)))
	  val = boolean_increment (code, arg);
	अन्यथा
	  val = build2 (code, वृक्ष_TYPE (arg), arg, inc);
	वृक्ष_SIDE_EFFECTS (val) = 1;
	यदि (TYPE_QUALS (वृक्ष_TYPE (val)) != TYPE_UNQUALIFIED)
	  वृक्ष_TYPE (val) = c_build_qualified_type (वृक्ष_TYPE (val),
						    TYPE_UNQUALIFIED);
	ret = val;
	गच्छ return_build_unary_op;
      }

    पक्ष ADDR_व्यंजक:
      /* Note that this operation never does default_conversion.  */

      /* The operand of unary '&' must be an lvalue (which excludes
	 expressions of type void), or, in C99, the result of a [] or
	 unary '*' operator.  */
      यदि (VOID_TYPE_P (वृक्ष_TYPE (arg))
	  && TYPE_QUALS (वृक्ष_TYPE (arg)) == TYPE_UNQUALIFIED
	  && (!INDIRECT_REF_P (arg) || !flag_isoc99))
	pedwarn (location, 0, "taking address of expression of type %<void%>");

      /* Let &* cancel out to simplify resulting code.  */
      यदि (INDIRECT_REF_P (arg))
	{
	  /* Don't let this be an lvalue.  */
	  यदि (lvalue_p (वृक्ष_OPERAND (arg, 0)))
	    प्रत्यागम non_lvalue_loc (location, वृक्ष_OPERAND (arg, 0));
	  ret = वृक्ष_OPERAND (arg, 0);
	  गच्छ return_build_unary_op;
	}

      /* Anything not already handled and not a true memory reference
	 or a non-lvalue array is an error.  */
      यदि (typecode != FUNCTION_TYPE && !noconvert
	  && !lvalue_or_else (location, arg, lv_addressof))
	प्रत्यागम error_mark_गाँठ;

      /* Move address operations inside C_MAYBE_CONST_EXPR to simplify
	 folding later.  */
      यदि (वृक्ष_CODE (arg) == C_MAYBE_CONST_व्यंजक)
	{
	  वृक्ष inner = build_unary_op (location, code,
				       C_MAYBE_CONST_व्यंजक_व्यंजक (arg),
				       noconvert);
	  ret = build2 (C_MAYBE_CONST_व्यंजक, वृक्ष_TYPE (inner),
			C_MAYBE_CONST_व्यंजक_PRE (arg), inner);
	  gcc_assert (!C_MAYBE_CONST_व्यंजक_INT_OPERANDS (arg));
	  C_MAYBE_CONST_व्यंजक_NON_CONST (ret)
	    = C_MAYBE_CONST_व्यंजक_NON_CONST (arg);
	  गच्छ return_build_unary_op;
	}

      /* Ordinary case; arg is a COMPONENT_REF or a decl.  */

      argtype = वृक्ष_TYPE (arg);

      /* If the lvalue is const or volatile, merge that into the type
	 to which the address will point.  This is only needed
	 for function types.  */
      यदि ((DECL_P (arg) || REFERENCE_CLASS_P (arg))
	  && (वृक्ष_READONLY (arg) || वृक्ष_THIS_VOLATILE (arg))
	  && वृक्ष_CODE (argtype) == FUNCTION_TYPE)
	{
	  पूर्णाङ्क orig_quals = TYPE_QUALS (strip_array_types (argtype));
	  पूर्णाङ्क quals = orig_quals;

	  यदि (वृक्ष_READONLY (arg))
	    quals |= TYPE_QUAL_CONST;
	  यदि (वृक्ष_THIS_VOLATILE (arg))
	    quals |= TYPE_QUAL_VOLATILE;

	  argtype = c_build_qualified_type (argtype, quals);
	}

      विकल्प (वृक्ष_CODE (arg))
	{
	पक्ष COMPONENT_REF:
	  यदि (DECL_C_BIT_FIELD (वृक्ष_OPERAND (arg, 1)))
	    {
	      error_at (location, "cannot take address of bit-field %qD",
			वृक्ष_OPERAND (arg, 1));
	      प्रत्यागम error_mark_गाँठ;
	    }

	  /* fall through */

	पक्ष ARRAY_REF:
	  यदि (TYPE_REVERSE_STORAGE_ORDER (वृक्ष_TYPE (वृक्ष_OPERAND (arg, 0))))
	    {
	      यदि (!AGGREGATE_TYPE_P (वृक्ष_TYPE (arg))
		  && !POINTER_TYPE_P (वृक्ष_TYPE (arg))
		  && !VECTOR_TYPE_P (वृक्ष_TYPE (arg)))
		{
		  error_at (location, "cannot take address of scalar with "
			    "reverse storage order");
		  प्रत्यागम error_mark_गाँठ;
		}

	      यदि (वृक्ष_CODE (वृक्ष_TYPE (arg)) == ARRAY_TYPE
		  && TYPE_REVERSE_STORAGE_ORDER (वृक्ष_TYPE (arg)))
		warning_at (location, OPT_Wscalar_storage_order,
			    "address of array with reverse scalar storage "
			    "order requested");
	    }

	स्वभाव:
	  भङ्ग;
	}

      यदि (!c_mark_addressable (arg))
	प्रत्यागम error_mark_गाँठ;

      gcc_assert (वृक्ष_CODE (arg) != COMPONENT_REF
		  || !DECL_C_BIT_FIELD (वृक्ष_OPERAND (arg, 1)));

      argtype = c_build_pointer_type (argtype);

      /* ??? Cope with user tricks that amount to offsetof.  Delete this
	 when we have proper support for integer constant expressions.  */
      val = get_base_address (arg);
      यदि (val && INDIRECT_REF_P (val)
          && वृक्ष_CONSTANT (वृक्ष_OPERAND (val, 0)))
	{
	  ret = fold_offsetof (arg, argtype);
	  गच्छ return_build_unary_op;
	}

      val = build1 (ADDR_व्यंजक, argtype, arg);

      ret = val;
      गच्छ return_build_unary_op;

    पक्ष PAREN_व्यंजक:
      ret = build1 (code, वृक्ष_TYPE (arg), arg);
      गच्छ return_build_unary_op;

    स्वभाव:
      gcc_unreachable ();
    }

  यदि (argtype == NULL_वृक्ष)
    argtype = वृक्ष_TYPE (arg);
  यदि (वृक्ष_CODE (arg) == INTEGER_CST)
    ret = (require_constant_मूल्य
	   ? fold_build1_initializer_loc (location, code, argtype, arg)
	   : fold_build1_loc (location, code, argtype, arg));
  अन्यथा
    ret = build1 (code, argtype, arg);
 return_build_unary_op:
  gcc_assert (ret != error_mark_गाँठ);
  यदि (वृक्ष_CODE (ret) == INTEGER_CST && !वृक्ष_OVERFLOW (ret)
      && !(वृक्ष_CODE (xarg) == INTEGER_CST && !वृक्ष_OVERFLOW (xarg)))
    ret = build1 (NOP_व्यंजक, वृक्ष_TYPE (ret), ret);
  अन्यथा यदि (वृक्ष_CODE (ret) != INTEGER_CST && int_operands)
    ret = note_integer_operands (ret);
  यदि (eptype)
    ret = build1 (EXCESS_PRECISION_व्यंजक, eptype, ret);
  protected_set_व्यंजक_location (ret, location);
  प्रत्यागम ret;
}

/* Return nonzero if REF is an lvalue valid for this language.
   Lvalues can be assigned, unless their type has TYPE_READONLY.
   Lvalues can have their address taken, unless they have C_DECL_REGISTER.  */

तार्किक
lvalue_p (const_वृक्ष ref)
{
  ध्रुव गणना वृक्ष_code code = वृक्ष_CODE (ref);

  विकल्प (code)
    {
    पक्ष REALPART_व्यंजक:
    पक्ष IMAGPART_व्यंजक:
    पक्ष COMPONENT_REF:
      प्रत्यागम lvalue_p (वृक्ष_OPERAND (ref, 0));

    पक्ष C_MAYBE_CONST_व्यंजक:
      प्रत्यागम lvalue_p (वृक्ष_OPERAND (ref, 1));

    पक्ष COMPOUND_LITERAL_व्यंजक:
    पक्ष STRING_CST:
      प्रत्यागम सत्य;

    पक्ष MEM_REF:
    पक्ष TARGET_MEM_REF:
      /* MEM_REFs can appear from -fgimple parsing or folding, so allow them
	 here as well.  */
    पक्ष INDIRECT_REF:
    पक्ष ARRAY_REF:
    पक्ष VAR_DECL:
    पक्ष PARM_DECL:
    पक्ष RESULT_DECL:
    पक्ष ERROR_MARK:
      प्रत्यागम (वृक्ष_CODE (वृक्ष_TYPE (ref)) != FUNCTION_TYPE
	      && वृक्ष_CODE (वृक्ष_TYPE (ref)) != METHOD_TYPE);

    पक्ष BIND_व्यंजक:
      प्रत्यागम वृक्ष_CODE (वृक्ष_TYPE (ref)) == ARRAY_TYPE;

    पक्ष CALL_व्यंजक:
      प्रत्यागम is_access_with_size_p (ref);

    स्वभाव:
      प्रत्यागम असत्य;
    }
}

/* Give a warning for storing in something that is read-only in GCC
   terms but not const in ISO C terms.  */

स्थिर शून्य
readonly_warning (वृक्ष arg, गणना lvalue_use use)
{
  विकल्प (use)
    {
    पक्ष lv_assign:
      warning (0, "assignment of read-only location %qE", arg);
      भङ्ग;
    पक्ष lv_increment:
      warning (0, "increment of read-only location %qE", arg);
      भङ्ग;
    पक्ष lv_decrement:
      warning (0, "decrement of read-only location %qE", arg);
      भङ्ग;
    स्वभाव:
      gcc_unreachable ();
    }
  प्रत्यागम;
}


/* Return nonzero if REF is an lvalue valid for this language;
   otherwise, print an error message and return zero.  USE says
   how the lvalue is being used and so selects the error message.
   LOCATION is the location at which any error should be reported.  */

स्थिर पूर्णाङ्क
lvalue_or_else (location_t loc, const_वृक्ष ref, गणना lvalue_use use)
{
  पूर्णाङ्क win = lvalue_p (ref);

  यदि (!win)
    lvalue_error (loc, use);

  प्रत्यागम win;
}

/* Mark EXP saying that we need to be able to take the
   address of it; it should not be allocated in a register.
   Returns true if successful.  ARRAY_REF_P is true if this
   is for ARRAY_REF construction - in that case we don't want
   to look through VIEW_CONVERT_EXPR from VECTOR_TYPE to ARRAY_TYPE,
   it is fine to use ARRAY_REFs for vector subscripts on vector
   register variables.  If OVERRIDE_REGISTER, clear DECL_REGISTER rather
   than producing an error for taking the address of a register.  */

तार्किक
c_mark_addressable (वृक्ष exp, तार्किक array_ref_p, तार्किक override_register)
{
  वृक्ष x = exp;

  यावत् (1)
    विकल्प (वृक्ष_CODE (x))
      {
      पक्ष VIEW_CONVERT_व्यंजक:
	यदि (array_ref_p
	    && वृक्ष_CODE (वृक्ष_TYPE (x)) == ARRAY_TYPE
	    && VECTOR_TYPE_P (वृक्ष_TYPE (वृक्ष_OPERAND (x, 0))))
	  प्रत्यागम सत्य;
	x = वृक्ष_OPERAND (x, 0);
	भङ्ग;

      पक्ष COMPONENT_REF:
	यदि (DECL_C_BIT_FIELD (वृक्ष_OPERAND (x, 1)))
	  {
	    error ("cannot take address of bit-field %qD",
		   वृक्ष_OPERAND (x, 1));
	    प्रत्यागम असत्य;
	  }
	/* FALLTHRU */
      पक्ष ADDR_व्यंजक:
      पक्ष ARRAY_REF:
      पक्ष REALPART_व्यंजक:
      पक्ष IMAGPART_व्यंजक:
	x = वृक्ष_OPERAND (x, 0);
	भङ्ग;

      पक्ष COMPOUND_LITERAL_व्यंजक:
	यदि (C_DECL_REGISTER (COMPOUND_LITERAL_व्यंजक_DECL (x)))
	  {
	    यदि (override_register)
	      DECL_REGISTER (COMPOUND_LITERAL_व्यंजक_DECL (x)) = 0;
	    अन्यथा
	      {
		error ("address of register compound literal requested");
		प्रत्यागम असत्य;
	      }
	  }
	वृक्ष_ADDRESSABLE (x) = 1;
	वृक्ष_ADDRESSABLE (COMPOUND_LITERAL_व्यंजक_DECL (x)) = 1;
	प्रत्यागम सत्य;

      पक्ष CONSTRUCTOR:
	वृक्ष_ADDRESSABLE (x) = 1;
	प्रत्यागम सत्य;

      पक्ष VAR_DECL:
      पक्ष CONST_DECL:
      पक्ष PARM_DECL:
      पक्ष RESULT_DECL:
	यदि (C_DECL_REGISTER (x)
	    && DECL_NONLOCAL (x))
	  {
	    यदि (वृक्ष_PUBLIC (x) || is_global_var (x))
	      {
		error
		  ("global register variable %qD used in nested function", x);
		प्रत्यागम असत्य;
	      }
	    pedwarn (निवेश_location, 0, "register variable %qD used in nested function", x);
	  }
	अन्यथा यदि (C_DECL_REGISTER (x))
	  {
	    यदि (वृक्ष_PUBLIC (x) || is_global_var (x))
	      error ("address of global register variable %qD requested", x);
	    अन्यथा यदि (override_register && !DECL_HARD_REGISTER (x))
	      {
		DECL_REGISTER (x) = 0;
		वृक्ष_ADDRESSABLE (x) = 1;
		mark_decl_used (x, सत्य);
		प्रत्यागम सत्य;
	      }
	    अन्यथा
	      error ("address of register variable %qD requested", x);
	    प्रत्यागम असत्य;
	  }

	/* FALLTHRU */
      पक्ष FUNCTION_DECL:
	वृक्ष_ADDRESSABLE (x) = 1;
	mark_decl_used (x, सत्य);
	/* FALLTHRU */
      स्वभाव:
	प्रत्यागम सत्य;
    }
}

/* Convert EXPR to TYPE, warning about conversion problems with
   constants.  SEMANTIC_TYPE is the type this conversion would use
   without excess precision. If SEMANTIC_TYPE is NULL, this function
   is equivalent to convert_and_check. This function is a wrapper that
   handles conversions that may be different than
   the usual ones because of excess precision.  */

स्थिर वृक्ष
ep_convert_and_check (location_t loc, वृक्ष type, वृक्ष व्यंजक,
		      वृक्ष semantic_type)
{
  यदि (वृक्ष_TYPE (व्यंजक) == type)
    प्रत्यागम व्यंजक;

  /* For C11, integer conversions may have results with excess
     precision.  */
  यदि (flag_isoc11 || !semantic_type)
    प्रत्यागम convert_and_check (loc, type, व्यंजक);

  यदि (वृक्ष_CODE (वृक्ष_TYPE (व्यंजक)) == INTEGER_TYPE
      && वृक्ष_TYPE (व्यंजक) != semantic_type)
    {
      /* For integers, we need to check the real conversion, not
	 the conversion to the excess precision type.  */
      व्यंजक = convert_and_check (loc, semantic_type, व्यंजक);
    }
  /* Result type is the excess precision type, which should be
     large enough, so do not check.  */
  प्रत्यागम convert (type, व्यंजक);
}

/* If EXPR refers to a built-in declared without a prototype returns
   the actual type of the built-in and, if non-null, set *BLTIN to
   a pointer to the built-in.  Otherwise return the type of EXPR
   and clear *BLTIN if non-null.  */

स्थिर वृक्ष
type_or_builtin_type (वृक्ष व्यंजक, वृक्ष *bltin = रिक्त)
{
  वृक्ष dummy;
  यदि (!bltin)
    bltin = &dummy;

  *bltin = NULL_वृक्ष;

  वृक्ष type = वृक्ष_TYPE (व्यंजक);
  यदि (वृक्ष_CODE (व्यंजक) != ADDR_व्यंजक)
    प्रत्यागम type;

  वृक्ष oper = वृक्ष_OPERAND (व्यंजक, 0);
  यदि (!DECL_P (oper)
      || वृक्ष_CODE (oper) != FUNCTION_DECL
      || !fndecl_built_in_p (oper, BUILT_IN_NORMAL))
    प्रत्यागम type;

  built_in_function code = DECL_FUNCTION_CODE (oper);
  यदि (!C_DECL_BUILTIN_PROTOTYPE (oper))
    प्रत्यागम type;

  यदि ((*bltin = builtin_decl_implicit (code)))
    type = c_build_pointer_type (वृक्ष_TYPE (*bltin));

  प्रत्यागम type;
}

/* Build and return a conditional expression IFEXP ? OP1 : OP2.  If
   IFEXP_BCP then the condition is a call to __builtin_constant_p, and
   if folded to an integer constant then the unselected half may
   contain arbitrary operations not normally permitted in constant
   expressions.  Set the location of the expression to LOC.  */

वृक्ष
build_conditional_व्यंजक (location_t colon_loc, वृक्ष ifexp, तार्किक ifexp_bcp,
			वृक्ष op1, वृक्ष op1_original_type, location_t op1_loc,
			वृक्ष op2, वृक्ष op2_original_type, location_t op2_loc)
{
  वृक्ष type1;
  वृक्ष type2;
  वृक्ष result_type = रिक्त;
  वृक्ष semantic_result_type = रिक्त;
  वृक्ष orig_op1 = op1, orig_op2 = op2;
  तार्किक int_const, op1_int_operands, op2_int_operands, int_operands;
  तार्किक ifexp_int_operands;
  वृक्ष ret;

  op1_int_operands = व्यंजक_INT_CONST_OPERANDS (orig_op1);
  यदि (op1_int_operands)
    op1 = remove_c_maybe_const_व्यंजक (op1);
  op2_int_operands = व्यंजक_INT_CONST_OPERANDS (orig_op2);
  यदि (op2_int_operands)
    op2 = remove_c_maybe_const_व्यंजक (op2);
  ifexp_int_operands = व्यंजक_INT_CONST_OPERANDS (ifexp);
  यदि (ifexp_int_operands)
    ifexp = remove_c_maybe_const_व्यंजक (ifexp);

  /* Promote both alternatives.  */

  यदि (वृक्ष_CODE (वृक्ष_TYPE (op1)) != VOID_TYPE)
    op1 = default_conversion (op1);
  यदि (वृक्ष_CODE (वृक्ष_TYPE (op2)) != VOID_TYPE)
    op2 = default_conversion (op2);

  यदि (वृक्ष_CODE (ifexp) == ERROR_MARK
      || वृक्ष_CODE (वृक्ष_TYPE (op1)) == ERROR_MARK
      || वृक्ष_CODE (वृक्ष_TYPE (op2)) == ERROR_MARK)
    प्रत्यागम error_mark_गाँठ;

  वृक्ष bltin1 = NULL_वृक्ष;
  वृक्ष bltin2 = NULL_वृक्ष;
  type1 = type_or_builtin_type (op1, &bltin1);
  ध्रुव गणना वृक्ष_code code1 = वृक्ष_CODE (type1);
  type2 = type_or_builtin_type (op2, &bltin2);
  ध्रुव गणना वृक्ष_code code2 = वृक्ष_CODE (type2);

  यदि (code1 == POINTER_TYPE && reject_gcc_builtin (op1))
    प्रत्यागम error_mark_गाँठ;

  यदि (code2 == POINTER_TYPE && reject_gcc_builtin (op2))
    प्रत्यागम error_mark_गाँठ;

  /* C90 does not permit non-lvalue arrays in conditional expressions.
     In C99 they will be pointers by now.  */
  यदि (code1 == ARRAY_TYPE || code2 == ARRAY_TYPE)
    {
      error_at (colon_loc, "non-lvalue array in conditional expression");
      प्रत्यागम error_mark_गाँठ;
    }

  यदि ((वृक्ष_CODE (op1) == EXCESS_PRECISION_व्यंजक
       || वृक्ष_CODE (op2) == EXCESS_PRECISION_व्यंजक)
      && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	  || code1 == COMPLEX_TYPE || code1 == BITINT_TYPE)
      && (code2 == INTEGER_TYPE || code2 == REAL_TYPE
	  || code2 == COMPLEX_TYPE || code2 == BITINT_TYPE))
    {
      semantic_result_type = c_common_type (type1, type2);
      यदि (वृक्ष_CODE (op1) == EXCESS_PRECISION_व्यंजक)
	{
	  op1 = वृक्ष_OPERAND (op1, 0);
	  type1 = वृक्ष_TYPE (op1);
	  gcc_assert (वृक्ष_CODE (type1) == code1);
	}
      यदि (वृक्ष_CODE (op2) == EXCESS_PRECISION_व्यंजक)
	{
	  op2 = वृक्ष_OPERAND (op2, 0);
	  type2 = वृक्ष_TYPE (op2);
	  gcc_assert (वृक्ष_CODE (type2) == code2);
	}
    }

  यदि (warn_cxx_compat)
    {
      वृक्ष t1 = op1_original_type ? op1_original_type : वृक्ष_TYPE (orig_op1);
      वृक्ष t2 = op2_original_type ? op2_original_type : वृक्ष_TYPE (orig_op2);

      यदि (वृक्ष_CODE (t1) == ENUMERAL_TYPE
	  && वृक्ष_CODE (t2) == ENUMERAL_TYPE
	  && TYPE_MAIN_VARIANT (t1) != TYPE_MAIN_VARIANT (t2))
	warning_at (colon_loc, OPT_Wc___compat,
		    "different enum types in conditional is "
		    "invalid in C++: %qT vs %qT", t1, t2);
    }

  यदि (warn_zero_as_null_pointer_constant
      && c_inhibit_evaluation_warnings == 0)
    {
      यदि ((code1 == POINTER_TYPE || code1 == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type2) && null_pointer_constant_p (orig_op2))
	warning_at (op2_loc, OPT_Wzero_as_null_pointer_constant,
		    "zero as null pointer constant");

      यदि ((code2 == POINTER_TYPE || code2 == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type1) && null_pointer_constant_p (orig_op1))
	warning_at (op1_loc, OPT_Wzero_as_null_pointer_constant,
		    "zero as null pointer constant");
    }

  /* Quickly detect the usual case where op1 and op2 have the same type
     after promotion.  */
  यदि (TYPE_MAIN_VARIANT (type1) == TYPE_MAIN_VARIANT (type2))
    {
      यदि (type1 == type2)
	result_type = type1;
      अन्यथा
	result_type = TYPE_MAIN_VARIANT (type1);
    }
  अन्यथा यदि ((code1 == INTEGER_TYPE || code1 == REAL_TYPE
	    || code1 == COMPLEX_TYPE || code1 == BITINT_TYPE)
	   && (code2 == INTEGER_TYPE || code2 == REAL_TYPE
	       || code2 == COMPLEX_TYPE || code2 == BITINT_TYPE))
    {
      /* In C11, a conditional expression between a floating-point
	 type and an integer type should convert the integer type to
	 the evaluation format of the floating-point type, with
	 possible excess precision.  */
      वृक्ष eptype1 = type1;
      वृक्ष eptype2 = type2;
      यदि (flag_isoc11)
	{
	  वृक्ष eptype;
	  यदि (ANY_INTEGRAL_TYPE_P (type1)
	      && (eptype = excess_precision_type (type2)) != NULL_वृक्ष)
	    {
	      eptype2 = eptype;
	      यदि (!semantic_result_type)
		semantic_result_type = c_common_type (type1, type2);
	    }
	  अन्यथा यदि (ANY_INTEGRAL_TYPE_P (type2)
		   && (eptype = excess_precision_type (type1)) != NULL_वृक्ष)
	    {
	      eptype1 = eptype;
	      यदि (!semantic_result_type)
		semantic_result_type = c_common_type (type1, type2);
	    }
	}
      result_type = c_common_type (eptype1, eptype2);
      यदि (result_type == error_mark_गाँठ)
	प्रत्यागम error_mark_गाँठ;
      do_warn_double_promotion (result_type, type1, type2,
				"implicit conversion from %qT to %qT to "
				"match other result of conditional",
				colon_loc);

      /* If -Wsign-compare, warn here if type1 and type2 have
	 different signedness.  We'll promote the signed to unsigned
	 and later code won't know it used to be different.
	 Do this check on the original types, so that explicit casts
	 will be considered, but default promotions won't.  */
      यदि (c_inhibit_evaluation_warnings == 0)
	{
	  पूर्णाङ्क unsigned_op1 = TYPE_UNSIGNED (वृक्ष_TYPE (orig_op1));
	  पूर्णाङ्क unsigned_op2 = TYPE_UNSIGNED (वृक्ष_TYPE (orig_op2));

	  यदि (unsigned_op1 ^ unsigned_op2)
	    {
	      /* Do not warn if the result type is signed, since the
		 signed type will only be chosen if it can represent
		 all the values of the unsigned type.  */
	      यदि (!TYPE_UNSIGNED (result_type))
		/* OK */;
	      अन्यथा
		{
		  तार्किक op1_maybe_const = सत्य;
		  तार्किक op2_maybe_const = सत्य;

		  /* Do not warn if the signed quantity is an
		     unsuffixed integer literal (or some static
		     constant expression involving such literals) and
		     it is non-negative.  This warning requires the
		     operands to be folded for best results, so do
		     that folding in this case even without
		     warn_sign_compare to avoid warning options
		     possibly affecting code generation.  */
		  c_inhibit_evaluation_warnings
		    += (ifexp == truthvalue_false_गाँठ);
		  op1 = c_fully_fold (op1, require_constant_मूल्य,
				      &op1_maybe_const);
		  c_inhibit_evaluation_warnings
		    -= (ifexp == truthvalue_false_गाँठ);

		  c_inhibit_evaluation_warnings
		    += (ifexp == truthvalue_true_गाँठ);
		  op2 = c_fully_fold (op2, require_constant_मूल्य,
				      &op2_maybe_const);
		  c_inhibit_evaluation_warnings
		    -= (ifexp == truthvalue_true_गाँठ);

		  यदि (warn_sign_compare)
		    {
		      यदि ((unsigned_op2
			   && वृक्ष_व्यंजक_nonnegative_p (op1))
			  || (unsigned_op1
			      && वृक्ष_व्यंजक_nonnegative_p (op2)))
			/* OK */;
		      अन्यथा यदि (unsigned_op2)
			warning_at (op1_loc, OPT_Wsign_compare,
				    "operand of %<?:%> changes signedness from "
				    "%qT to %qT due to unsignedness of other "
				    "operand", वृक्ष_TYPE (orig_op1),
				    वृक्ष_TYPE (orig_op2));
		      अन्यथा
			warning_at (op2_loc, OPT_Wsign_compare,
				    "operand of %<?:%> changes signedness from "
				    "%qT to %qT due to unsignedness of other "
				    "operand", वृक्ष_TYPE (orig_op2),
				    वृक्ष_TYPE (orig_op1));
		    }
		  यदि (!op1_maybe_const || वृक्ष_CODE (op1) != INTEGER_CST)
		    op1 = c_wrap_maybe_const (op1, !op1_maybe_const);
		  यदि (!op2_maybe_const || वृक्ष_CODE (op2) != INTEGER_CST)
		    op2 = c_wrap_maybe_const (op2, !op2_maybe_const);
		}
	    }
	}
    }
  अन्यथा यदि (code1 == VOID_TYPE || code2 == VOID_TYPE)
    {
      यदि (code1 != VOID_TYPE || code2 != VOID_TYPE)
	pedwarn (colon_loc, OPT_Wpedantic,
		 "ISO C forbids conditional expr with only one void side");
      result_type = void_type_गाँठ;
    }
  अन्यथा यदि (code1 == POINTER_TYPE && code2 == POINTER_TYPE)
    {
      addr_space_t as1 = TYPE_ADDR_SPACE (वृक्ष_TYPE (type1));
      addr_space_t as2 = TYPE_ADDR_SPACE (वृक्ष_TYPE (type2));
      addr_space_t as_common;

      यदि (comp_target_types (colon_loc, type1, type2))
	{
	  ifexp = save_व्यंजक (ifexp);
	  result_type = common_pointer_type (type1, type2, ifexp);
	}
      अन्यथा यदि (null_pointer_constant_p (orig_op1))
	result_type = type2;
      अन्यथा यदि (null_pointer_constant_p (orig_op2))
	result_type = type1;
      अन्यथा यदि (!addr_space_superset (as1, as2, &as_common))
	{
	  error_at (colon_loc, "pointers to disjoint address spaces "
		    "used in conditional expression");
	  प्रत्यागम error_mark_गाँठ;
	}
      अन्यथा यदि ((VOID_TYPE_P (वृक्ष_TYPE (type1))
		&& !TYPE_ATOMIC (वृक्ष_TYPE (type1)))
	       || (VOID_TYPE_P (वृक्ष_TYPE (type2))
		   && !TYPE_ATOMIC (वृक्ष_TYPE (type2))))
	{
	  वृक्ष t1 = वृक्ष_TYPE (type1);
	  वृक्ष t2 = वृक्ष_TYPE (type2);
	  यदि (!(VOID_TYPE_P (t1)
		&& !TYPE_ATOMIC (t1)))
	   {
	     /* roles are swapped */
	     t1 = t2;
	     t2 = वृक्ष_TYPE (type1);
	   }
	  वृक्ष t2_stripped = strip_array_types (t2);
	  यदि ((वृक्ष_CODE (t2) == ARRAY_TYPE)
	      && (TYPE_QUALS (t2_stripped) & ~TYPE_QUALS (t1)))
	    {
	      यदि (!flag_isoc23)
		warning_at (colon_loc, OPT_Wdiscarded_array_qualifiers,
			    "pointer to array loses qualifier "
			    "in conditional expression");
	      अन्यथा यदि (warn_c11_c23_compat > 0)
		warning_at (colon_loc, OPT_Wc11_c23_compat,
			    "pointer to array loses qualifier "
			    "in conditional expression in ISO C before C23");
	    }
	  यदि (वृक्ष_CODE (t2) == FUNCTION_TYPE)
	    pedwarn (colon_loc, OPT_Wpedantic,
		     "ISO C forbids conditional expr between "
		     "%<void *%> and function pointer");
	  /* for array, use qualifiers of element type */
	  यदि (flag_isoc23)
	    t2 = t2_stripped;
	  result_type = c_build_pointer_type (qualify_type (t1, t2));
	}
      /* Objective-C pointer comparisons are a bit more lenient.  */
      अन्यथा यदि (objc_have_common_type (type1, type2, -3, NULL_वृक्ष))
	result_type = objc_common_type (type1, type2);
      अन्यथा
	{
	  पूर्णाङ्क qual = ENCODE_QUAL_ADDR_SPACE (as_common);
	  गणना diagnostics::kind kind = diagnostics::kind::permerror;
	  यदि (!flag_isoc99)
	    /* This downgrade to a warning ensures that -std=gnu89
	       -pedantic-errors does not flag these mismatches between
	       builtins as errors (as diagnostics::kind::permerror would)
	       ISO C99 and later do not have implicit function declarations,
	       so the mismatch cannot occur naturally there.  */
	    kind = (bltin1 && bltin2
		    ? diagnostics::kind::warning
		    : diagnostics::kind::pedwarn);
	  यदि (emit_diagnostic (kind, colon_loc, OPT_Wincompatible_pointer_types,
			       "pointer type mismatch "
			       "in conditional expression"))
	    {
	      inform (op1_loc, "first expression has type %qT", type1);
	      inform (op2_loc, "second expression has type %qT", type2);
	    }
	  result_type = c_build_pointer_type
			  (c_build_qualified_type (void_type_गाँठ, qual));
	}
    }
  अन्यथा यदि (code1 == POINTER_TYPE
	   && (code2 == INTEGER_TYPE || code2 == BITINT_TYPE))
    {
      यदि (!null_pointer_constant_p (orig_op2))
	permerror_opt (colon_loc, OPT_Wint_conversion,
		       "pointer/integer type mismatch "
		       "in conditional expression");
      अन्यथा
	{
	  op2 = null_pointer_गाँठ;
	}
      result_type = type1;
    }
  अन्यथा यदि (code2 == POINTER_TYPE
	   && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
    {
      यदि (!null_pointer_constant_p (orig_op1))
	permerror_opt (colon_loc, OPT_Wint_conversion,
		       "pointer/integer type mismatch "
		       "in conditional expression");
      अन्यथा
	{
	  op1 = null_pointer_गाँठ;
	}
      result_type = type2;
    }
  /* 6.5.15: "if one is a null pointer constant (other than a pointer) or has
     type nullptr_t and the other is a pointer, the result type is the pointer
     type."  */
  अन्यथा यदि (code1 == NULLPTR_TYPE && code2 == POINTER_TYPE)
    result_type = type2;
  अन्यथा यदि (code1 == POINTER_TYPE && code2 == NULLPTR_TYPE)
    result_type = type1;
  अन्यथा यदि (RECORD_OR_UNION_TYPE_P (type1) && RECORD_OR_UNION_TYPE_P (type2)
	   && comptypes (TYPE_MAIN_VARIANT (type1),
			 TYPE_MAIN_VARIANT (type2)))
    result_type = composite_type (TYPE_MAIN_VARIANT (type1),
				  TYPE_MAIN_VARIANT (type2));

  यदि (!result_type)
    {
      यदि (flag_cond_mismatch)
	result_type = void_type_गाँठ;
      अन्यथा
	{
	  error_at (colon_loc, "type mismatch in conditional expression");
	  प्रत्यागम error_mark_गाँठ;
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

  यदि (ifexp_bcp && ifexp == truthvalue_true_गाँठ)
    {
      op2_int_operands = सत्य;
      op1 = c_fully_fold (op1, require_constant_मूल्य, रिक्त);
    }
  यदि (ifexp_bcp && ifexp == truthvalue_false_गाँठ)
    {
      op1_int_operands = सत्य;
      op2 = c_fully_fold (op2, require_constant_मूल्य, रिक्त);
    }
  int_const = int_operands = (ifexp_int_operands
			      && op1_int_operands
			      && op2_int_operands);
  यदि (int_operands)
    {
      int_const = ((ifexp == truthvalue_true_गाँठ
		    && वृक्ष_CODE (orig_op1) == INTEGER_CST
		    && !वृक्ष_OVERFLOW (orig_op1))
		   || (ifexp == truthvalue_false_गाँठ
		       && वृक्ष_CODE (orig_op2) == INTEGER_CST
		       && !वृक्ष_OVERFLOW (orig_op2)));
    }

  /* Need to convert condition operand into a vector mask.  */
  यदि (VECTOR_TYPE_P (वृक्ष_TYPE (ifexp)))
    {
      वृक्ष vectype = वृक्ष_TYPE (ifexp);
      वृक्ष elem_type = वृक्ष_TYPE (vectype);
      वृक्ष zero = build_int_cst (elem_type, 0);
      वृक्ष zero_vec = build_vector_from_val (vectype, zero);
      वृक्ष cmp_type = truth_type_for (vectype);
      ifexp = build2 (NE_व्यंजक, cmp_type, ifexp, zero_vec);
    }

  यदि (int_const || (ifexp_bcp && वृक्ष_CODE (ifexp) == INTEGER_CST))
    ret = fold_build3_loc (colon_loc, COND_व्यंजक, result_type, ifexp, op1, op2);
  अन्यथा
    {
      यदि (int_operands)
	{
	  /* Use c_fully_fold here, since C_MAYBE_CONST_EXPR might be
	     nested inside of the expression.  */
	  op1 = c_fully_fold (op1, असत्य, रिक्त);
	  op2 = c_fully_fold (op2, असत्य, रिक्त);
	}
      ret = build3 (COND_व्यंजक, result_type, ifexp, op1, op2);
      यदि (int_operands)
	ret = note_integer_operands (ret);
    }
  यदि (semantic_result_type)
    ret = build1 (EXCESS_PRECISION_व्यंजक, semantic_result_type, ret);

  protected_set_व्यंजक_location (ret, colon_loc);

  /* If the OP1 and OP2 are the same and don't have side-effects,
     warn here, because the COND_EXPR will be turned into OP1.  */
  यदि (warn_duplicated_branches
      && वृक्ष_CODE (ret) == COND_व्यंजक
      && (op1 == op2 || operand_equal_p (op1, op2, OEP_ADDRESS_OF_SAME_FIELD)))
    warning_at (व्यंजक_LOCATION (ret), OPT_Wduplicated_branches,
		"this condition has identical branches");

  प्रत्यागम ret;
}

/* EXPR is an expression, location LOC, whose result is discarded.
   Warn if it is a call to a nodiscard function (or a COMPOUND_EXPR
   whose right-hand operand is such a call, possibly recursively).  */

स्थिर शून्य
maybe_warn_nodiscard (location_t loc, वृक्ष व्यंजक)
{
  यदि (VOID_TYPE_P (वृक्ष_TYPE (व्यंजक)))
    प्रत्यागम;
  यावत् (वृक्ष_CODE (व्यंजक) == COMPOUND_व्यंजक)
    {
      व्यंजक = वृक्ष_OPERAND (व्यंजक, 1);
      यदि (व्यंजक_HAS_LOCATION (व्यंजक))
	loc = व्यंजक_LOCATION (व्यंजक);
    }
  यदि (वृक्ष_CODE (व्यंजक) != CALL_व्यंजक)
    प्रत्यागम;
  वृक्ष fn = CALL_व्यंजक_FN (व्यंजक);
  यदि (!fn)
    प्रत्यागम;
  वृक्ष attr;
  यदि (वृक्ष_CODE (fn) == ADDR_व्यंजक
      && वृक्ष_CODE (वृक्ष_OPERAND (fn, 0)) == FUNCTION_DECL
      && (attr = lookup_attribute ("nodiscard",
				   DECL_ATTRIBUTES (वृक्ष_OPERAND (fn, 0)))))
    {
      fn = वृक्ष_OPERAND (fn, 0);
      वृक्ष args = वृक्ष_मूल्य (attr);
      यदि (args)
	args = वृक्ष_मूल्य (args);
      auto_diagnostic_group d;
      auto_urlify_attributes sentinel;
      पूर्णाङ्क warned;
      यदि (args)
	warned = warning_at (loc, OPT_Wunused_result,
			     "ignoring return value of %qD, declared with "
			     "attribute %<nodiscard%>: %E", fn, args);
      अन्यथा
	warned = warning_at (loc, OPT_Wunused_result,
			     "ignoring return value of %qD, declared with "
			     "attribute %<nodiscard%>", fn);
      यदि (warned)
	inform (DECL_SOURCE_LOCATION (fn), "declared here");
    }
  अन्यथा
    {
      वृक्ष rettype = वृक्ष_TYPE (वृक्ष_TYPE (वृक्ष_TYPE (fn)));
      attr = lookup_attribute ("nodiscard", TYPE_ATTRIBUTES (rettype));
      यदि (!attr)
	प्रत्यागम;
      वृक्ष args = वृक्ष_मूल्य (attr);
      यदि (args)
	args = वृक्ष_मूल्य (args);
      auto_diagnostic_group d;
      auto_urlify_attributes sentinel;
      पूर्णाङ्क warned;
      यदि (args)
	warned = warning_at (loc, OPT_Wunused_result,
			     "ignoring return value of type %qT, declared "
			     "with attribute %<nodiscard%>: %E",
			     rettype, args);
      अन्यथा
	warned = warning_at (loc, OPT_Wunused_result,
			     "ignoring return value of type %qT, declared "
			     "with attribute %<nodiscard%>", rettype);
      यदि (warned)
	{
	  यदि (वृक्ष_CODE (fn) == ADDR_व्यंजक)
	    {
	      fn = वृक्ष_OPERAND (fn, 0);
	      यदि (वृक्ष_CODE (fn) == FUNCTION_DECL)
		inform (DECL_SOURCE_LOCATION (fn),
			"in call to %qD, declared here", fn);
	    }
	}
    }
}

/* Return a compound expression that performs two expressions and
   returns the value of the second of them.

   LOC is the location of the COMPOUND_EXPR.  */

वृक्ष
build_compound_व्यंजक (location_t loc, वृक्ष expr1, वृक्ष expr2)
{
  तार्किक expr1_int_operands, expr2_int_operands;
  वृक्ष eptype = NULL_वृक्ष;
  वृक्ष ret;

  expr1_int_operands = व्यंजक_INT_CONST_OPERANDS (expr1);
  यदि (expr1_int_operands)
    expr1 = remove_c_maybe_const_व्यंजक (expr1);
  expr2_int_operands = व्यंजक_INT_CONST_OPERANDS (expr2);
  यदि (expr2_int_operands)
    expr2 = remove_c_maybe_const_व्यंजक (expr2);

  यदि (वृक्ष_CODE (expr1) == EXCESS_PRECISION_व्यंजक)
    expr1 = वृक्ष_OPERAND (expr1, 0);
  यदि (वृक्ष_CODE (expr2) == EXCESS_PRECISION_व्यंजक)
    {
      eptype = वृक्ष_TYPE (expr2);
      expr2 = वृक्ष_OPERAND (expr2, 0);
    }

  यदि (!वृक्ष_SIDE_EFFECTS (expr1))
    {
      /* The left-hand operand of a comma expression is like an expression
	 statement: with -Wunused, we should warn if it doesn't have
	 any side-effects, unless it was explicitly cast to (void).  */
      यदि (warn_unused_मूल्य)
	{
	  यदि (VOID_TYPE_P (वृक्ष_TYPE (expr1))
	      && CONVERT_व्यंजक_P (expr1))
	    ; /* (void) a, b */
	  अन्यथा यदि (VOID_TYPE_P (वृक्ष_TYPE (expr1))
		   && वृक्ष_CODE (expr1) == COMPOUND_व्यंजक
		   && CONVERT_व्यंजक_P (वृक्ष_OPERAND (expr1, 1)))
	    ; /* (void) a, (void) b, c */
	  अन्यथा
	    warning_at (loc, OPT_Wunused_मूल्य,
			"left-hand operand of comma expression has no effect");
	}
    }
  अन्यथा यदि (वृक्ष_CODE (expr1) == COMPOUND_व्यंजक
	   && warn_unused_मूल्य)
    {
      वृक्ष r = expr1;
      location_t cloc = loc;
      यावत् (वृक्ष_CODE (r) == COMPOUND_व्यंजक)
        {
	  यदि (व्यंजक_HAS_LOCATION (r))
	    cloc = व्यंजक_LOCATION (r);
	  r = वृक्ष_OPERAND (r, 1);
	}
      यदि (!वृक्ष_SIDE_EFFECTS (r)
	  && !VOID_TYPE_P (वृक्ष_TYPE (r))
	  && !CONVERT_व्यंजक_P (r))
	warning_at (cloc, OPT_Wunused_मूल्य,
	            "right-hand operand of comma expression has no effect");
    }

  /* With -Wunused, we should also warn if the left-hand operand does have
     side-effects, but computes a value which is not used.  For example, in
     `foo() + bar(), baz()' the result of the `+' operator is not used,
     so we should issue a warning.  */
  अन्यथा यदि (warn_unused_मूल्य)
    warn_if_unused_मूल्य (expr1, loc);

  maybe_warn_nodiscard (loc, expr1);

  यदि (expr2 == error_mark_गाँठ)
    प्रत्यागम error_mark_गाँठ;

  ret = build2 (COMPOUND_व्यंजक, वृक्ष_TYPE (expr2), expr1, expr2);

  यदि (flag_isoc99
      && expr1_int_operands
      && expr2_int_operands)
    ret = note_integer_operands (ret);

  यदि (eptype)
    ret = build1 (EXCESS_PRECISION_व्यंजक, eptype, ret);

  protected_set_व्यंजक_location (ret, loc);
  प्रत्यागम ret;
}

/* Issue -Wcast-qual warnings when appropriate.  TYPE is the type to
   which we are casting.  OTYPE is the type of the expression being
   cast.  Both TYPE and OTYPE are pointer types.  LOC is the location
   of the cast.  -Wcast-qual appeared on the command line.  Named
   address space qualifiers are not handled here, because they result
   in different warnings.  */

स्थिर शून्य
handle_warn_cast_qual (location_t loc, वृक्ष type, वृक्ष otype)
{
  वृक्ष in_type = type;
  वृक्ष in_otype = otype;
  पूर्णाङ्क added = 0;
  पूर्णाङ्क discarded = 0;
  तार्किक is_const;

  /* Check that the qualifiers on IN_TYPE are a superset of the
     qualifiers of IN_OTYPE.  The outermost level of POINTER_TYPE
     nodes is uninteresting and we stop as soon as we hit a
     non-POINTER_TYPE node on either type.  */
  कुरु
    {
      in_otype = वृक्ष_TYPE (in_otype);
      in_type = वृक्ष_TYPE (in_type);

      /* GNU C allows cv-qualified function types.  'const' means the
	 function is very pure, 'volatile' means it can't return.  We
	 need to warn when such qualifiers are added, not when they're
	 taken away.  */
      यदि (वृक्ष_CODE (in_otype) == FUNCTION_TYPE
	  && वृक्ष_CODE (in_type) == FUNCTION_TYPE)
	added |= (TYPE_QUALS_NO_ADDR_SPACE (in_type)
		  & ~TYPE_QUALS_NO_ADDR_SPACE (in_otype));
      अन्यथा
	discarded |= (TYPE_QUALS_NO_ADDR_SPACE (in_otype)
		      & ~TYPE_QUALS_NO_ADDR_SPACE (in_type));
    }
  यावत् (वृक्ष_CODE (in_type) == POINTER_TYPE
	 && वृक्ष_CODE (in_otype) == POINTER_TYPE);

  यदि (added)
    warning_at (loc, OPT_Wcast_qual,
		"cast adds %q#v qualifier to function type", added);

  यदि (discarded)
    /* There are qualifiers present in IN_OTYPE that are not present
       in IN_TYPE.  */
    warning_at (loc, OPT_Wcast_qual,
		"cast discards %qv qualifier from pointer target type",
		discarded);

  यदि (added || discarded)
    प्रत्यागम;

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

  यदि (TYPE_MAIN_VARIANT (in_type) != TYPE_MAIN_VARIANT (in_otype))
    प्रत्यागम;
  यदि (वृक्ष_CODE (वृक्ष_TYPE (type)) != POINTER_TYPE)
    प्रत्यागम;

  in_type = type;
  in_otype = otype;
  is_const = TYPE_READONLY (वृक्ष_TYPE (in_type));
  कुरु
    {
      in_type = वृक्ष_TYPE (in_type);
      in_otype = वृक्ष_TYPE (in_otype);
      यदि ((TYPE_QUALS (in_type) &~ TYPE_QUALS (in_otype)) != 0
	  && !is_const)
	{
	  warning_at (loc, OPT_Wcast_qual,
		      "to be safe all intermediate pointers in cast from "
                      "%qT to %qT must be %<const%> qualified",
		      otype, type);
	  भङ्ग;
	}
      यदि (is_const)
	is_const = TYPE_READONLY (in_type);
    }
  यावत् (वृक्ष_CODE (in_type) == POINTER_TYPE);
}

/* Heuristic check if two parameter types can be considered ABI-equivalent.  */

स्थिर तार्किक
c_safe_arg_type_equiv_p (वृक्ष t1, वृक्ष t2)
{
  यदि (error_operand_p (t1) || error_operand_p (t2))
    प्रत्यागम सत्य;

  t1 = TYPE_MAIN_VARIANT (t1);
  t2 = TYPE_MAIN_VARIANT (t2);

  यदि (वृक्ष_CODE (t1) == POINTER_TYPE
      && वृक्ष_CODE (t2) == POINTER_TYPE)
    प्रत्यागम सत्य;

  /* Only the precision of the parameter matters.  This check should
     make sure that the callee does not see undefined values in argument
     registers.  */
  यदि (INTEGRAL_TYPE_P (t1)
      && INTEGRAL_TYPE_P (t2)
      && TYPE_PRECISION (t1) == TYPE_PRECISION (t2))
    प्रत्यागम सत्य;

  प्रत्यागम comptypes (t1, t2);
}

/* Check if a type cast between two function types can be considered safe.  */

स्थिर तार्किक
c_safe_function_type_cast_p (वृक्ष t1, वृक्ष t2)
{
  यदि (वृक्ष_TYPE (t1) == void_type_गाँठ &&
      TYPE_ARG_TYPES (t1) == void_list_गाँठ)
    प्रत्यागम सत्य;

  यदि (वृक्ष_TYPE (t2) == void_type_गाँठ &&
      TYPE_ARG_TYPES (t2) == void_list_गाँठ)
    प्रत्यागम सत्य;

  यदि (!c_safe_arg_type_equiv_p (वृक्ष_TYPE (t1), वृक्ष_TYPE (t2)))
    प्रत्यागम असत्य;

  प्रति (t1 = TYPE_ARG_TYPES (t1), t2 = TYPE_ARG_TYPES (t2);
       t1 && t2;
       t1 = वृक्ष_CHAIN (t1), t2 = वृक्ष_CHAIN (t2))
    यदि (!c_safe_arg_type_equiv_p (वृक्ष_मूल्य (t1), वृक्ष_मूल्य (t2)))
      प्रत्यागम असत्य;

  प्रत्यागम सत्य;
}

/* Build an expression representing a cast to type TYPE of expression EXPR.
   LOC is the location of the cast-- typically the open paren of the cast.  */

वृक्ष
build_c_cast (location_t loc, वृक्ष type, वृक्ष व्यंजक)
{
  वृक्ष मूल्य;

  तार्किक int_operands = व्यंजक_INT_CONST_OPERANDS (व्यंजक);

  यदि (वृक्ष_CODE (व्यंजक) == EXCESS_PRECISION_व्यंजक)
    व्यंजक = वृक्ष_OPERAND (व्यंजक, 0);

  मूल्य = व्यंजक;
  यदि (int_operands)
    मूल्य = remove_c_maybe_const_व्यंजक (मूल्य);

  यदि (type == error_mark_गाँठ || व्यंजक == error_mark_गाँठ)
    प्रत्यागम error_mark_गाँठ;

  /* The ObjC front-end uses TYPE_MAIN_VARIANT to tie together types differing
     only in <protocol> qualifications.  But when constructing cast expressions,
     the protocols do matter and must be kept around.  */
  यदि (objc_is_object_ptr (type) && objc_is_object_ptr (वृक्ष_TYPE (व्यंजक)))
    प्रत्यागम build1 (NOP_व्यंजक, type, व्यंजक);

  type = TYPE_MAIN_VARIANT (type);

  यदि (वृक्ष_CODE (type) == ARRAY_TYPE)
    {
      error_at (loc, "cast specifies array type");
      प्रत्यागम error_mark_गाँठ;
    }

  यदि (वृक्ष_CODE (type) == FUNCTION_TYPE)
    {
      error_at (loc, "cast specifies function type");
      प्रत्यागम error_mark_गाँठ;
    }

  यदि (!VOID_TYPE_P (type))
    {
      मूल्य = require_complete_type (loc, मूल्य);
      यदि (मूल्य == error_mark_गाँठ)
	प्रत्यागम error_mark_गाँठ;
    }

  यदि (type == TYPE_MAIN_VARIANT (वृक्ष_TYPE (मूल्य)))
    {
      यदि (RECORD_OR_UNION_TYPE_P (type)
	  && pedwarn (loc, OPT_Wpedantic,
		      "ISO C forbids casting nonscalar to the same type"))
	      ;
      अन्यथा यदि (warn_useless_cast && c_inhibit_evaluation_warnings == 0)
	warning_at (loc, OPT_Wuseless_cast,
		    "useless cast to type %qT", type);

      /* Convert to remove any qualifiers from VALUE's type.  */
      मूल्य = convert (type, मूल्य);
    }
  अन्यथा यदि (वृक्ष_CODE (type) == UNION_TYPE)
    {
      वृक्ष field;

      प्रति (field = TYPE_FIELDS (type); field; field = DECL_CHAIN (field))
	यदि (वृक्ष_TYPE (field) != error_mark_गाँठ
	    && comptypes (TYPE_MAIN_VARIANT (वृक्ष_TYPE (field)),
			  TYPE_MAIN_VARIANT (वृक्ष_TYPE (मूल्य))))
	  भङ्ग;

      यदि (field)
	{
	  वृक्ष t;
	  तार्किक maybe_const = सत्य;

	  pedwarn (loc, OPT_Wpedantic, "ISO C forbids casts to union type");
	  t = c_fully_fold (मूल्य, असत्य, &maybe_const);
	  t = build_constructor_single (type, field, t);
	  यदि (!maybe_const)
	    t = c_wrap_maybe_const (t, सत्य);
	  t = digest_init (loc, field, type, t,
			   NULL_वृक्ष, असत्य, असत्य, असत्य, सत्य, असत्य, असत्य);
	  वृक्ष_CONSTANT (t) = वृक्ष_CONSTANT (मूल्य);
	  प्रत्यागम t;
	}
      error_at (loc, "cast to union type from type not present in union");
      प्रत्यागम error_mark_गाँठ;
    }
  अन्यथा
    {
      वृक्ष otype, ovalue;

      यदि (type == void_type_गाँठ)
	{
	  वृक्ष t = build1 (CONVERT_व्यंजक, type, मूल्य);
	  SET_व्यंजक_LOCATION (t, loc);
	  प्रत्यागम t;
	}

      otype = वृक्ष_TYPE (मूल्य);

      /* Optionally warn about potentially worrisome casts.  */
      यदि (warn_cast_qual
	  && वृक्ष_CODE (type) == POINTER_TYPE
	  && वृक्ष_CODE (otype) == POINTER_TYPE)
	handle_warn_cast_qual (loc, type, otype);

      /* Warn about conversions between pointers to disjoint
	 address spaces.  */
      यदि (वृक्ष_CODE (type) == POINTER_TYPE
	  && वृक्ष_CODE (otype) == POINTER_TYPE
	  && !null_pointer_constant_p (मूल्य))
	{
	  addr_space_t as_to = TYPE_ADDR_SPACE (वृक्ष_TYPE (type));
	  addr_space_t as_from = TYPE_ADDR_SPACE (वृक्ष_TYPE (otype));
	  addr_space_t as_common;

	  यदि (!addr_space_superset (as_to, as_from, &as_common))
	    {
	      यदि (ADDR_SPACE_GENERIC_P (as_from))
		warning_at (loc, 0, "cast to %qs address space pointer "
			    "from disjoint generic address space pointer",
			    c_addr_space_name (as_to));

	      अन्यथा यदि (ADDR_SPACE_GENERIC_P (as_to))
		warning_at (loc, 0, "cast to generic address space pointer "
			    "from disjoint %qs address space pointer",
			    c_addr_space_name (as_from));

	      अन्यथा
		warning_at (loc, 0, "cast to %qs address space pointer "
			    "from disjoint %qs address space pointer",
			    c_addr_space_name (as_to),
			    c_addr_space_name (as_from));
	    }

	  /* Warn of new allocations that are not big enough for the target
	     type.  */
	  यदि (warn_alloc_size && वृक्ष_CODE (मूल्य) == CALL_व्यंजक)
	    यदि (वृक्ष fndecl = get_callee_fndecl (मूल्य))
	      यदि (DECL_IS_MALLOC (fndecl))
		{
		  वृक्ष attrs = TYPE_ATTRIBUTES (वृक्ष_TYPE (fndecl));
		  वृक्ष alloc_size = lookup_attribute ("alloc_size", attrs);
		  यदि (alloc_size)
		    warn_for_alloc_size (loc, वृक्ष_TYPE (type), मूल्य,
					 alloc_size);
		}
	}

      /* Warn about possible alignment problems.  */
      यदि ((STRICT_ALIGNMENT || warn_cast_align == 2)
	  && वृक्ष_CODE (type) == POINTER_TYPE
	  && वृक्ष_CODE (otype) == POINTER_TYPE
	  && वृक्ष_CODE (वृक्ष_TYPE (otype)) != VOID_TYPE
	  && वृक्ष_CODE (वृक्ष_TYPE (otype)) != FUNCTION_TYPE
	  /* Don't warn about opaque types, where the actual alignment
	     restriction is unknown.  */
	  && !(RECORD_OR_UNION_TYPE_P (वृक्ष_TYPE (otype))
	       && TYPE_MODE (वृक्ष_TYPE (otype)) == VOIDmode)
	  && min_align_of_type (वृक्ष_TYPE (type))
	     > min_align_of_type (वृक्ष_TYPE (otype)))
	warning_at (loc, OPT_Wcast_align,
		    "cast increases required alignment of target type");

      यदि ((वृक्ष_CODE (type) == INTEGER_TYPE
	   || वृक्ष_CODE (type) == BITINT_TYPE)
	  && वृक्ष_CODE (otype) == POINTER_TYPE
	  && TYPE_PRECISION (type) != TYPE_PRECISION (otype))
      /* Unlike conversion of integers to pointers, where the
         warning is disabled for converting constants because
         of cases such as SIG_*, warn about converting constant
         pointers to integers. In some cases it may cause unwanted
         sign extension, and a warning is appropriate.  */
	warning_at (loc, OPT_Wpointer_to_int_cast,
		    "cast from pointer to integer of different size");

      यदि ((वृक्ष_CODE (मूल्य) == CALL_व्यंजक
	   && !is_access_with_size_p (मूल्य))
	  && वृक्ष_CODE (type) != वृक्ष_CODE (otype))
	warning_at (loc, OPT_Wbad_function_cast,
		    "cast from function call of type %qT "
		    "to non-matching type %qT", otype, type);

      यदि (वृक्ष_CODE (type) == POINTER_TYPE
	  && (वृक्ष_CODE (otype) == INTEGER_TYPE
	      || वृक्ष_CODE (otype) == BITINT_TYPE)
	  && TYPE_PRECISION (type) != TYPE_PRECISION (otype)
	  /* Don't warn about converting any constant.  */
	  && !वृक्ष_CONSTANT (मूल्य))
	warning_at (loc,
		    OPT_Wint_to_pointer_cast, "cast to pointer from integer "
		    "of different size");

      यदि (warn_strict_aliasing <= 2)
        strict_aliasing_warning (व्यंजक_LOCATION (मूल्य), type, व्यंजक);

      /* If pedantic, warn for conversions between function and object
	 pointer types, except for converting a null pointer constant
	 to function pointer type.  */
      यदि (pedantic
	  && वृक्ष_CODE (type) == POINTER_TYPE
	  && वृक्ष_CODE (otype) == POINTER_TYPE
	  && वृक्ष_CODE (वृक्ष_TYPE (otype)) == FUNCTION_TYPE
	  && वृक्ष_CODE (वृक्ष_TYPE (type)) != FUNCTION_TYPE)
	pedwarn (loc, OPT_Wpedantic, "ISO C forbids "
		 "conversion of function pointer to object pointer type");

      यदि (pedantic
	  && वृक्ष_CODE (type) == POINTER_TYPE
	  && वृक्ष_CODE (otype) == POINTER_TYPE
	  && वृक्ष_CODE (वृक्ष_TYPE (type)) == FUNCTION_TYPE
	  && वृक्ष_CODE (वृक्ष_TYPE (otype)) != FUNCTION_TYPE
	  && !null_pointer_constant_p (मूल्य))
	pedwarn (loc, OPT_Wpedantic, "ISO C forbids "
		 "conversion of object pointer to function pointer type");

      यदि (वृक्ष_CODE (type) == POINTER_TYPE
	  && वृक्ष_CODE (otype) == POINTER_TYPE
	  && वृक्ष_CODE (वृक्ष_TYPE (type)) == FUNCTION_TYPE
	  && वृक्ष_CODE (वृक्ष_TYPE (otype)) == FUNCTION_TYPE
	  && !c_safe_function_type_cast_p (वृक्ष_TYPE (type),
					   वृक्ष_TYPE (otype)))
	warning_at (loc, OPT_Wcast_function_type,
		    "cast between incompatible function types"
		    " from %qT to %qT", otype, type);

      ovalue = मूल्य;
      /* If converting to boolean a value with integer operands that
	 is not itself represented as an INTEGER_CST, the call below
	 to note_integer_operands may insert a C_MAYBE_CONST_EXPR, but
	 build_binary_op as called by c_common_truthvalue_conversion
	 may also insert a C_MAYBE_CONST_EXPR to indicate that a
	 subexpression has been fully folded.  To avoid nested
	 C_MAYBE_CONST_EXPR, ensure that
	 c_objc_common_truthvalue_conversion receives an argument
	 properly marked as having integer operands in that case.  */
      यदि (int_operands
	  && वृक्ष_CODE (मूल्य) != INTEGER_CST
	  && (वृक्ष_CODE (type) == BOOLEAN_TYPE
	      || (वृक्ष_CODE (type) == ENUMERAL_TYPE
		  && ENUM_UNDERLYING_TYPE (type) != NULL_वृक्ष
		  && वृक्ष_CODE (ENUM_UNDERLYING_TYPE (type)) == BOOLEAN_TYPE)))
	मूल्य = note_integer_operands (मूल्य);
      मूल्य = convert (type, मूल्य);

      /* Ignore any integer overflow caused by the cast.  */
      यदि (वृक्ष_CODE (मूल्य) == INTEGER_CST && !FLOAT_TYPE_P (otype))
	{
	  यदि (वृक्ष_OVERFLOW_P (ovalue))
	    {
	      यदि (!वृक्ष_OVERFLOW (मूल्य))
		{
		  /* Avoid clobbering a shared constant.  */
		  मूल्य = copy_गाँठ (मूल्य);
		  वृक्ष_OVERFLOW (मूल्य) = वृक्ष_OVERFLOW (ovalue);
		}
	    }
	  अन्यथा यदि (वृक्ष_OVERFLOW (मूल्य))
	    /* Reset VALUE's overflow flags, ensuring constant sharing.  */
	    मूल्य = wide_int_to_वृक्ष (वृक्ष_TYPE (मूल्य), wi::to_wide (मूल्य));
	}
    }

  /* Don't let a cast be an lvalue.  */
  यदि (lvalue_p (मूल्य)
      /* Also, don't let a cast be a bit-field of a bit-precise integer type,
	 otherwise it could be incorrectly subject of integer promotions.  */
      || (वृक्ष_CODE (मूल्य) == COMPONENT_REF
	  && DECL_C_BIT_FIELD (वृक्ष_OPERAND (मूल्य, 1))
	  && BITINT_TYPE_P (DECL_BIT_FIELD_TYPE (वृक्ष_OPERAND (मूल्य, 1)))))
    मूल्य = non_lvalue_loc (loc, मूल्य);

  /* Don't allow the results of casting to floating-point or complex
     types be confused with actual constants, or casts involving
     integer and pointer types other than direct integer-to-integer
     and integer-to-pointer be confused with integer constant
     expressions and null pointer constants.  */
  यदि (वृक्ष_CODE (मूल्य) == REAL_CST
      || वृक्ष_CODE (मूल्य) == COMPLEX_CST
      || (वृक्ष_CODE (मूल्य) == INTEGER_CST
	  && !((वृक्ष_CODE (व्यंजक) == INTEGER_CST
		&& INTEGRAL_TYPE_P (वृक्ष_TYPE (व्यंजक)))
	       || वृक्ष_CODE (व्यंजक) == REAL_CST
	       || वृक्ष_CODE (व्यंजक) == COMPLEX_CST)))
      मूल्य = build1 (NOP_व्यंजक, type, मूल्य);

  /* If the expression has integer operands and so can occur in an
     unevaluated part of an integer constant expression, ensure the
     return value reflects this.  */
  यदि (int_operands
      && INTEGRAL_TYPE_P (type)
      && मूल्य != error_mark_गाँठ
      && !व्यंजक_INT_CONST_OPERANDS (मूल्य))
    मूल्य = note_integer_operands (मूल्य);

  protected_set_व्यंजक_location (मूल्य, loc);
  प्रत्यागम मूल्य;
}

/* Interpret a cast of expression EXPR to type TYPE.  LOC is the
   location of the open paren of the cast, or the position of the cast
   expr.  */
वृक्ष
c_cast_व्यंजक (location_t loc, संरचना c_type_name *type_name, वृक्ष व्यंजक)
{
  वृक्ष type;
  वृक्ष type_व्यंजक = NULL_वृक्ष;
  तार्किक type_व्यंजक_const = सत्य;
  वृक्ष ret;
  पूर्णाङ्क saved_wsp = warn_strict_prototypes;

  /* This avoids warnings about unprototyped casts on
     integers.  E.g. "#define SIG_DFL (void(*)())0".  */
  यदि (वृक्ष_CODE (व्यंजक) == INTEGER_CST)
    warn_strict_prototypes = 0;
  type = groktypename (type_name, &type_व्यंजक, &type_व्यंजक_const);
  warn_strict_prototypes = saved_wsp;

  यदि (वृक्ष_CODE (व्यंजक) == ADDR_व्यंजक && !VOID_TYPE_P (type)
      && reject_gcc_builtin (व्यंजक))
    प्रत्यागम error_mark_गाँठ;

  ret = build_c_cast (loc, type, व्यंजक);
  यदि (ret == error_mark_गाँठ)
    प्रत्यागम error_mark_गाँठ;

  यदि (type_व्यंजक)
    {
      तार्किक inner_व्यंजक_const = सत्य;
      ret = c_fully_fold (ret, require_constant_मूल्य, &inner_व्यंजक_const);
      ret = build2 (C_MAYBE_CONST_व्यंजक, वृक्ष_TYPE (ret), type_व्यंजक, ret);
      C_MAYBE_CONST_व्यंजक_NON_CONST (ret) = !(type_व्यंजक_const
					     && inner_व्यंजक_const);
      SET_व्यंजक_LOCATION (ret, loc);
    }

  यदि (!व्यंजक_HAS_LOCATION (ret))
    protected_set_व्यंजक_location (ret, loc);

  /* C++ does not permits types to be defined in a cast, but it
     allows references to incomplete types.  */
  यदि (warn_cxx_compat && type_name->specs->typespec_kind == ctsk_tagdef)
    warning_at (loc, OPT_Wc___compat,
		"defining a type in a cast is invalid in C++");

  प्रत्यागम ret;
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

वृक्ष
build_modify_व्यंजक (location_t location, वृक्ष lhs, वृक्ष lhs_origtype,
		   गणना वृक्ष_code modifycode,
		   location_t rhs_loc, वृक्ष rhs, वृक्ष rhs_origtype)
{
  वृक्ष result;
  वृक्ष newrhs;
  वृक्ष rhseval = NULL_वृक्ष;
  वृक्ष lhstype = वृक्ष_TYPE (lhs);
  वृक्ष olhstype = lhstype;
  तार्किक npc;
  तार्किक is_atomic_op;

  /* Types that aren't fully specified cannot be used in assignments.  */
  lhs = require_complete_type (location, lhs);
  rhs = require_complete_type (location, rhs);

  /* Avoid duplicate error messages from operands that had errors.  */
  यदि (वृक्ष_CODE (lhs) == ERROR_MARK || वृक्ष_CODE (rhs) == ERROR_MARK)
    प्रत्यागम error_mark_गाँठ;

  /* Ensure an error for assigning a non-lvalue array to an array in
     C90.  */
  यदि (वृक्ष_CODE (lhstype) == ARRAY_TYPE)
    {
      error_at (location, "assignment to expression with array type");
      प्रत्यागम error_mark_गाँठ;
    }

  /* For ObjC properties, defer this check.  */
  यदि (!objc_is_property_ref (lhs) && !lvalue_or_else (location, lhs, lv_assign))
    प्रत्यागम error_mark_गाँठ;

  is_atomic_op = really_atomic_lvalue (lhs);

  newrhs = rhs;

  यदि (वृक्ष_CODE (lhs) == C_MAYBE_CONST_व्यंजक)
    {
      वृक्ष inner = build_modify_व्यंजक (location, C_MAYBE_CONST_व्यंजक_व्यंजक (lhs),
				      lhs_origtype, modifycode, rhs_loc, rhs,
				      rhs_origtype);
      यदि (inner == error_mark_गाँठ)
	प्रत्यागम error_mark_गाँठ;
      result = build2 (C_MAYBE_CONST_व्यंजक, वृक्ष_TYPE (inner),
		       C_MAYBE_CONST_व्यंजक_PRE (lhs), inner);
      gcc_assert (!C_MAYBE_CONST_व्यंजक_INT_OPERANDS (lhs));
      C_MAYBE_CONST_व्यंजक_NON_CONST (result) = 1;
      protected_set_व्यंजक_location (result, location);
      प्रत्यागम result;
    }

  /* If a binary op has been requested, combine the old LHS value with the RHS
     producing the value we should actually store into the LHS.  */

  यदि (modifycode != NOP_व्यंजक)
    {
      lhs = c_fully_fold (lhs, असत्य, रिक्त, सत्य);
      lhs = stabilize_reference (lhs);

      /* Construct the RHS for any non-atomic compound assignment. */
      यदि (!is_atomic_op)
        {
	  /* If in LHS op= RHS the RHS has side-effects, ensure they
	     are preevaluated before the rest of the assignment expression's
	     side-effects, because RHS could contain e.g. function calls
	     that modify LHS.  */
	  यदि (वृक्ष_SIDE_EFFECTS (rhs))
	    {
	      यदि (वृक्ष_CODE (rhs) == EXCESS_PRECISION_व्यंजक)
		newrhs = save_व्यंजक (वृक्ष_OPERAND (rhs, 0));
	      अन्यथा
		newrhs = save_व्यंजक (rhs);
	      rhseval = newrhs;
	      यदि (वृक्ष_CODE (rhs) == EXCESS_PRECISION_व्यंजक)
		newrhs = build1 (EXCESS_PRECISION_व्यंजक, वृक्ष_TYPE (rhs),
				 newrhs);
	    }
	  तार्किक clear_decl_read = असत्य;
	  यदि ((VAR_P (lhs) || वृक्ष_CODE (lhs) == PARM_DECL)
	      && !DECL_READ_P (lhs)
	      && (VAR_P (lhs) ? warn_unused_but_set_variable
			      : warn_unused_but_set_parameter) > 2)
	    {
	      mark_exp_read (newrhs);
	      यदि (!DECL_READ_P (lhs))
		clear_decl_read = सत्य;
	    }

	  newrhs = build_द्विआधारी_op (location, modifycode,
				    convert_lvalue_to_rvalue (location, lhs,
							      सत्य, सत्य),
				    newrhs, सत्य);
	  यदि (clear_decl_read)
	    DECL_READ_P (lhs) = 0;

	  /* The original type of the right hand side is no longer
	     meaningful.  */
	  rhs_origtype = NULL_वृक्ष;
	}
    }

  यदि (c_dialect_objc ())
    {
      /* Check if we are modifying an Objective-C property reference;
	 if so, we need to generate setter calls.  */
      यदि (वृक्ष_CODE (newrhs) == EXCESS_PRECISION_व्यंजक)
	result = objc_maybe_build_modify_व्यंजक (lhs, वृक्ष_OPERAND (newrhs, 0));
      अन्यथा
	result = objc_maybe_build_modify_व्यंजक (lhs, newrhs);
      यदि (result)
	गच्छ return_result;

      /* Else, do the check that we postponed for Objective-C.  */
      यदि (!lvalue_or_else (location, lhs, lv_assign))
	प्रत्यागम error_mark_गाँठ;
    }

  /* Give an error for storing in something that is 'const'.  */

  यदि (TYPE_READONLY (lhstype)
      || (RECORD_OR_UNION_TYPE_P (lhstype)
	  && C_TYPE_FIELDS_READONLY (lhstype)))
    {
      readonly_error (location, lhs, lv_assign);
      प्रत्यागम error_mark_गाँठ;
    }
  अन्यथा यदि (वृक्ष_READONLY (lhs))
    readonly_warning (lhs, lv_assign);

  /* If storing into a structure or union member,
     it has probably been given type `int'.
     Compute the type that would go with
     the actual amount of storage the member occupies.  */

  यदि (वृक्ष_CODE (lhs) == COMPONENT_REF
      && (वृक्ष_CODE (lhstype) == INTEGER_TYPE
	  || वृक्ष_CODE (lhstype) == BOOLEAN_TYPE
	  || SCALAR_FLOAT_TYPE_P (lhstype)
	  || वृक्ष_CODE (lhstype) == ENUMERAL_TYPE))
    lhstype = वृक्ष_TYPE (get_unwidened (lhs, 0));

  /* If storing in a field that is in actuality a short or narrower than one,
     we must store in the field in its actual type.  */

  यदि (lhstype != वृक्ष_TYPE (lhs))
    {
      lhs = copy_गाँठ (lhs);
      वृक्ष_TYPE (lhs) = lhstype;
    }

  /* Issue -Wc++-compat warnings about an assignment to an enum type
     when LHS does not have its original type.  This happens for,
     e.g., an enum bitfield in a struct.  */
  यदि (warn_cxx_compat
      && lhs_origtype != NULL_वृक्ष
      && lhs_origtype != lhstype
      && वृक्ष_CODE (lhs_origtype) == ENUMERAL_TYPE)
    {
      वृक्ष checktype = (rhs_origtype != NULL_वृक्ष
			? rhs_origtype
			: वृक्ष_TYPE (rhs));
      यदि (checktype != error_mark_गाँठ
	  && (TYPE_MAIN_VARIANT (checktype) != TYPE_MAIN_VARIANT (lhs_origtype)
	      || (is_atomic_op && modifycode != NOP_व्यंजक)))
	warning_at (location, OPT_Wc___compat,
		    "enum conversion in assignment is invalid in C++");
    }

  /* Remove qualifiers.  */
  lhstype = c_build_qualified_type (lhstype, TYPE_UNQUALIFIED);
  olhstype = c_build_qualified_type (olhstype, TYPE_UNQUALIFIED);

  /* Convert new value to destination type.  Fold it first, then
     restore any excess precision information, for the sake of
     conversion warnings.  */

  यदि (!(is_atomic_op && modifycode != NOP_व्यंजक))
    {
      वृक्ष rhs_semantic_type = NULL_वृक्ष;
      यदि (!c_in_omp_for)
	{
	  यदि (वृक्ष_CODE (newrhs) == EXCESS_PRECISION_व्यंजक)
	    {
	      rhs_semantic_type = वृक्ष_TYPE (newrhs);
	      newrhs = वृक्ष_OPERAND (newrhs, 0);
	    }
	  npc = null_pointer_constant_p (newrhs);
	  newrhs = c_fully_fold (newrhs, असत्य, रिक्त);
	  यदि (rhs_semantic_type)
	    newrhs = build1 (EXCESS_PRECISION_व्यंजक, rhs_semantic_type, newrhs);
	}
      अन्यथा
	npc = null_pointer_constant_p (newrhs);
      newrhs = convert_for_assignment (location, rhs_loc, lhstype, newrhs,
				       rhs_origtype, ic_assign, npc,
				       NULL_वृक्ष, NULL_वृक्ष, 0);
      यदि (वृक्ष_CODE (newrhs) == ERROR_MARK)
	प्रत्यागम error_mark_गाँठ;
    }

  /* Emit ObjC write barrier, if necessary.  */
  यदि (c_dialect_objc () && flag_objc_gc)
    {
      result = objc_generate_write_barrier (lhs, modifycode, newrhs);
      यदि (result)
	{
	  protected_set_व्यंजक_location (result, location);
	  गच्छ return_result;
	}
    }

  /* Scan operands.  */

  यदि (is_atomic_op)
    result = build_atomic_assign (location, lhs, modifycode, newrhs, असत्य);
  अन्यथा
    {
      result = build2 (MODIFY_व्यंजक, lhstype, lhs, newrhs);
      वृक्ष_SIDE_EFFECTS (result) = 1;
      protected_set_व्यंजक_location (result, location);
    }

  /* If we got the LHS in a different type for storing in,
     convert the result back to the nominal type of LHS
     so that the value we return always has the same type
     as the LHS argument.  */

  यदि (olhstype == वृक्ष_TYPE (result))
    गच्छ return_result;

  result = convert_for_assignment (location, rhs_loc, olhstype, result,
				   rhs_origtype, ic_assign, असत्य, NULL_वृक्ष,
				   NULL_वृक्ष, 0);
  protected_set_व्यंजक_location (result, location);

return_result:
  यदि (rhseval)
    result = build2 (COMPOUND_व्यंजक, वृक्ष_TYPE (result), rhseval, result);
  प्रत्यागम result;
}

/* Return whether STRUCT_TYPE has an anonymous field with type TYPE.
   This is used to implement -fplan9-extensions.  */

स्थिर तार्किक
find_anonymous_field_with_type (वृक्ष struct_type, वृक्ष type)
{
  वृक्ष field;
  तार्किक found;

  gcc_assert (RECORD_OR_UNION_TYPE_P (struct_type));
  found = असत्य;
  प्रति (field = TYPE_FIELDS (struct_type);
       field != NULL_वृक्ष;
       field = वृक्ष_CHAIN (field))
    {
      वृक्ष fieldtype = remove_qualifiers (वृक्ष_TYPE (field));
      यदि (DECL_NAME (field) == रिक्त
	  && comptypes (type, fieldtype))
	{
	  यदि (found)
	    प्रत्यागम असत्य;
	  found = सत्य;
	}
      अन्यथा यदि (DECL_NAME (field) == रिक्त
	       && RECORD_OR_UNION_TYPE_P (वृक्ष_TYPE (field))
	       && find_anonymous_field_with_type (वृक्ष_TYPE (field), type))
	{
	  यदि (found)
	    प्रत्यागम असत्य;
	  found = सत्य;
	}
    }
  प्रत्यागम found;
}

/* RHS is an expression whose type is pointer to struct.  If there is
   an anonymous field in RHS with type TYPE, then return a pointer to
   that field in RHS.  This is used with -fplan9-extensions.  This
   returns NULL if no conversion could be found.  */

स्थिर वृक्ष
convert_to_anonymous_field (location_t location, वृक्ष type, वृक्ष rhs)
{
  वृक्ष rhs_struct_type, lhs_main_type;
  वृक्ष field, found_field;
  तार्किक found_sub_field;
  वृक्ष ret;

  gcc_assert (POINTER_TYPE_P (वृक्ष_TYPE (rhs)));
  rhs_struct_type = वृक्ष_TYPE (वृक्ष_TYPE (rhs));
  gcc_assert (RECORD_OR_UNION_TYPE_P (rhs_struct_type));

  gcc_assert (POINTER_TYPE_P (type));
  lhs_main_type = remove_qualifiers (वृक्ष_TYPE (type));

  found_field = NULL_वृक्ष;
  found_sub_field = असत्य;
  प्रति (field = TYPE_FIELDS (rhs_struct_type);
       field != NULL_वृक्ष;
       field = वृक्ष_CHAIN (field))
    {
      यदि (DECL_NAME (field) != NULL_वृक्ष
	  || !RECORD_OR_UNION_TYPE_P (वृक्ष_TYPE (field)))
	अनुवर्त;
      वृक्ष fieldtype = remove_qualifiers (वृक्ष_TYPE (field));
      यदि (comptypes (lhs_main_type, fieldtype))
	{
	  यदि (found_field != NULL_वृक्ष)
	    प्रत्यागम NULL_वृक्ष;
	  found_field = field;
	}
      अन्यथा यदि (find_anonymous_field_with_type (वृक्ष_TYPE (field),
					       lhs_main_type))
	{
	  यदि (found_field != NULL_वृक्ष)
	    प्रत्यागम NULL_वृक्ष;
	  found_field = field;
	  found_sub_field = सत्य;
	}
    }

  यदि (found_field == NULL_वृक्ष)
    प्रत्यागम NULL_वृक्ष;

  ret = fold_build3_loc (location, COMPONENT_REF, वृक्ष_TYPE (found_field),
			 build_fold_indirect_ref (rhs), found_field,
			 NULL_वृक्ष);
  ret = build_fold_addr_व्यंजक_loc (location, ret);

  यदि (found_sub_field)
    {
      ret = convert_to_anonymous_field (location, type, ret);
      gcc_assert (ret != NULL_वृक्ष);
    }

  प्रत्यागम ret;
}

/* Issue an error message for a bad initializer component.
   GMSGID identifies the message.
   The component name is taken from the spelling stack.  */

स्थिर शून्य ATTRIBUTE_GCC_DIAG (2,0)
error_init (location_t loc, ध्रुव वर्ण *gmsgid, ...)
{
  वर्ण *ofwhat;

  auto_diagnostic_group d;

  /* The gmsgid may be a format string with %< and %>. */
  बहु_सूची ap;
  बहु_शुरू (ap, gmsgid);
  तार्किक warned = emit_diagnostic_valist (diagnostics::kind::error,
					loc, -1, gmsgid, &ap);
  बहु_पूर्ण (ap);

  ofwhat = print_spelling ((वर्ण *) alloca (spelling_length () + 1));
  यदि (*ofwhat && warned)
    inform (loc, "(near initialization for %qs)", ofwhat);
}

/* Used to implement pedwarn_init and permerror_init.  */

स्थिर तार्किक ATTRIBUTE_GCC_DIAG (3,0)
pedwarn_permerror_init (location_t loc, पूर्णाङ्क opt, ध्रुव वर्ण *gmsgid,
			बहु_सूची *ap, गणना diagnostics::kind kind)
{
  /* Use the location where a macro was expanded rather than where
     it was defined to make sure macros defined in system headers
     but used incorrectly elsewhere are diagnosed.  */
  location_t exploc = expansion_point_location_if_in_system_header (loc);
  auto_diagnostic_group d;
  तार्किक warned = emit_diagnostic_valist (kind, exploc, opt, gmsgid, ap);
  यदि (warned)
    {
      वर्ण *ofwhat = print_spelling ((वर्ण *) alloca (spelling_length () + 1));
      यदि (*ofwhat)
	inform (exploc, "(near initialization for %qs)", ofwhat);
    }
  प्रत्यागम warned;
}

/* Issue a pedantic warning for a bad initializer component.  OPT is
   the option OPT_* (from options.h) controlling this warning or 0 if
   it is unconditionally given.  GMSGID identifies the message.  The
   component name is taken from the spelling stack.  */

स्थिर तार्किक ATTRIBUTE_GCC_DIAG (3,0)
pedwarn_init (location_t loc, पूर्णाङ्क opt, ध्रुव वर्ण *gmsgid, ...)
{
  बहु_सूची ap;
  बहु_शुरू (ap, gmsgid);
  तार्किक warned = pedwarn_permerror_init (loc, opt, gmsgid, &ap,
					diagnostics::kind::pedwarn);
  बहु_पूर्ण (ap);
  प्रत्यागम warned;
}

/* Like pedwarn_init, but issue a permerror.  */

स्थिर तार्किक ATTRIBUTE_GCC_DIAG (3,0)
permerror_init (location_t loc, पूर्णाङ्क opt, ध्रुव वर्ण *gmsgid, ...)
{
  बहु_सूची ap;
  बहु_शुरू (ap, gmsgid);
  तार्किक warned = pedwarn_permerror_init (loc, opt, gmsgid, &ap,
					diagnostics::kind::permerror);
  बहु_पूर्ण (ap);
  प्रत्यागम warned;
}

/* Issue a warning for a bad initializer component.

   OPT is the OPT_W* value corresponding to the warning option that
   controls this warning.  GMSGID identifies the message.  The
   component name is taken from the spelling stack.  */

स्थिर शून्य
warning_init (location_t loc, पूर्णाङ्क opt, ध्रुव वर्ण *gmsgid)
{
  वर्ण *ofwhat;
  तार्किक warned;

  auto_diagnostic_group d;

  /* Use the location where a macro was expanded rather than where
     it was defined to make sure macros defined in system headers
     but used incorrectly elsewhere are diagnosed.  */
  location_t exploc = expansion_point_location_if_in_system_header (loc);

  /* The gmsgid may be a format string with %< and %>. */
  warned = warning_at (exploc, opt, gmsgid);
  यदि (warned)
    {
      ofwhat = print_spelling ((वर्ण *) alloca (spelling_length () + 1));
      यदि (*ofwhat)
	inform (exploc, "(near initialization for %qs)", ofwhat);
    }
}

/* If TYPE is an array type and EXPR is a parenthesized string
   constant, warn if pedantic that EXPR is being used to initialize an
   object of type TYPE.  */

शून्य
maybe_warn_string_init (location_t loc, वृक्ष type, संरचना c_व्यंजक व्यंजक)
{
  यदि (pedantic
      && वृक्ष_CODE (type) == ARRAY_TYPE
      && वृक्ष_CODE (व्यंजक.मूल्य) == STRING_CST
      && व्यंजक.original_code != STRING_CST)
    pedwarn_init (loc, OPT_Wpedantic,
		  "array initialized from parenthesized string constant");
}

/* Attempt to locate the parameter with the given index within FNDECL,
   returning DECL_SOURCE_LOCATION (FNDECL) if it can't be found.  */

स्थिर location_t
get_fndecl_argument_location (वृक्ष fndecl, पूर्णाङ्क argnum)
{
  पूर्णाङ्क i;
  वृक्ष param;

  /* Locate param by index within DECL_ARGUMENTS (fndecl).  */
  प्रति (i = 0, param = DECL_ARGUMENTS (fndecl);
       i < argnum && param;
       i++, param = वृक्ष_CHAIN (param))
    ;

  /* If something went wrong (e.g. if we have a builtin and thus no arguments),
     return DECL_SOURCE_LOCATION (FNDECL).  */
  यदि (param == रिक्त)
    प्रत्यागम DECL_SOURCE_LOCATION (fndecl);

  प्रत्यागम DECL_SOURCE_LOCATION (param);
}

/* Issue a note about a mismatching argument for parameter PARMNUM
   to FUNDECL, for types EXPECTED_TYPE and ACTUAL_TYPE.
   Attempt to issue the note at the pertinent parameter of the decl;
   failing that issue it at the location of FUNDECL; failing that
   issue it at PLOC.
   Use highlight_colors::actual for the ACTUAL_TYPE
   and highlight_colors::expected for EXPECTED_TYPE and the
   parameter of FUNDECL*/

स्थिर शून्य
inform_for_arg (वृक्ष fundecl, location_t ploc, पूर्णाङ्क parmnum,
		वृक्ष expected_type, वृक्ष actual_type)
{
  location_t loc;
  यदि (fundecl && !DECL_IS_UNDECLARED_BUILTIN (fundecl))
    loc = get_fndecl_argument_location (fundecl, parmnum - 1);
  अन्यथा
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

स्थिर शून्य
maybe_warn_builtin_no_proto_arg (location_t loc, वृक्ष fundecl, पूर्णाङ्क parmnum,
				 वृक्ष parmtype, वृक्ष argtype)
{
  वृक्ष_code parmcode = वृक्ष_CODE (parmtype);
  वृक्ष_code argcode = वृक्ष_CODE (argtype);
  वृक्ष promoted = c_type_promotes_to (argtype);

  /* Avoid warning for enum arguments that promote to an integer type
     of the same size/mode.  */
  यदि (parmcode == INTEGER_TYPE
      && argcode == ENUMERAL_TYPE
      && TYPE_MODE (parmtype) == TYPE_MODE (argtype))
    प्रत्यागम;

  यदि ((parmcode == argcode
       || (parmcode == INTEGER_TYPE
	   && argcode == ENUMERAL_TYPE))
      && TYPE_MAIN_VARIANT (parmtype) == TYPE_MAIN_VARIANT (promoted))
    प्रत्यागम;

  /* This diagnoses even signed/unsigned mismatches.  Those might be
     safe in many cases but GCC may emit suboptimal code for them so
     warning on those cases drives efficiency improvements.  */
  यदि (warning_at (loc, OPT_Wbuiltin_declaration_mismatch,
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

वर्ग pp_element_quoted_decl : सार्वजनिक pp_element
{
सार्वजनिक:
  pp_element_quoted_decl (वृक्ष decl, ध्रुव वर्ण *highlight_color)
  : m_decl (decl),
    m_highlight_color (highlight_color)
  {
  }

  शून्य add_to_phase_2 (pp_markup::context &ctxt) override
  {
    ctxt.begin_quote ();
    ctxt.begin_highlight_color (m_highlight_color);

    print_decl (ctxt);

    ctxt.end_highlight_color ();
    ctxt.end_quote ();
  }

  शून्य print_decl (pp_markup::context &ctxt)
  {
    pretty_printer *ध्रुव pp = &ctxt.m_pp;
    pp->set_padding (pp_none);
    यदि (DECL_NAME (m_decl))
      pp_identifier (pp, lang_hooks.decl_printable_name (m_decl, 2));
    अन्यथा
      pp_string (pp, _("({anonymous})"));
  }

गुप्त:
  वृक्ष m_decl;
  ध्रुव वर्ण *m_highlight_color;
};

/* If TYPE is from a typedef, issue a note showing the location
   to the user.
   Use HIGHLIGHT_COLOR as the highlight color.  */

स्थिर शून्य
maybe_inform_typedef_location (वृक्ष type, ध्रुव वर्ण *highlight_color)
{
  यदि (!typedef_variant_p (type))
    प्रत्यागम;

  वृक्ष typedef_decl = TYPE_NAME (type);
  gcc_assert (वृक्ष_CODE (typedef_decl) == TYPE_DECL);
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

स्थिर वृक्ष
convert_for_assignment (location_t location, location_t व्यंजक_loc, वृक्ष type,
			वृक्ष rhs, वृक्ष origtype, गणना impl_conv errtype,
			तार्किक null_pointer_constant, वृक्ष fundecl,
			वृक्ष function, पूर्णाङ्क parmnum, पूर्णाङ्क warnopt /* = 0 */)
{
  गणना वृक्ष_code codel = वृक्ष_CODE (type);
  वृक्ष orig_rhs = rhs;
  वृक्ष rhstype;
  गणना वृक्ष_code coder;
  वृक्ष rname = NULL_वृक्ष;
  तार्किक objc_ok = असत्य;

  /* Use the expansion point location to handle cases such as user's
     function returning a wrong-type macro defined in a system header.  */
  location = expansion_point_location_if_in_system_header (location);

  यदि (errtype == ic_argpass)
    {
      वृक्ष selector;
      /* Change pointer to function to the function itself for
	 diagnostics.  */
      यदि (वृक्ष_CODE (function) == ADDR_व्यंजक
	  && वृक्ष_CODE (वृक्ष_OPERAND (function, 0)) == FUNCTION_DECL)
	function = वृक्ष_OPERAND (function, 0);

      /* Handle an ObjC selector specially for diagnostics.  */
      selector = objc_message_selector ();
      rname = function;
      यदि (selector && parmnum > 2)
	{
	  rname = selector;
	  parmnum -= 2;
	}
    }

  /* This macro is used to emit diagnostics to ensure that all format
     strings are complete sentences, visible to gettext and checked at
     compile time.  */
#define PEDWARN_FOR_ASSIGNMENT(LOCATION, PLOC, OPT, AR, AS, IN, RE)	 \
  कुरु {                                                                   \
    विकल्प (errtype)                                                     \
      {                                                                  \
      पक्ष ic_argpass:                                                   \
	{								\
	  auto_diagnostic_group d;						\
	  यदि (pedwarn (PLOC, OPT, AR, parmnum, rname))		\
	    inform_for_arg (fundecl, (PLOC), parmnum, type, rhstype); \
	}								\
        भङ्ग;                                                           \
      पक्ष ic_assign:                                                    \
        pedwarn (LOCATION, OPT, AS);                                     \
        भङ्ग;                                                           \
      पक्ष ic_init:                                                      \
      पक्ष ic_init_const:                                                \
        pedwarn_init (LOCATION, OPT, IN);                                \
        भङ्ग;                                                           \
      पक्ष ic_return:                                                    \
        pedwarn (LOCATION, OPT, RE);					 \
        भङ्ग;                                                           \
      स्वभाव:                                                           \
        gcc_unreachable ();                                              \
      }                                                                  \
  } यावत् (0)

  /* This macro is used to emit diagnostics to ensure that all format
     strings are complete sentences, visible to gettext and checked at
     compile time.  It can be called with 'pedwarn' or 'warning_at'.  */
#define WARNING_FOR_QUALIFIERS(PEDWARN, LOCATION, PLOC, OPT, AR, AS, IN, RE, QUALS) \
  कुरु {                                                                   \
    विकल्प (errtype)                                                     \
      {                                                                  \
      पक्ष ic_argpass:                                                   \
	{								 \
	  auto_diagnostic_group d;					 \
	  यदि (PEDWARN) {						 \
	    यदि (pedwarn (PLOC, OPT, AR, parmnum, rname, QUALS))          \
	      inform_for_arg (fundecl, (PLOC), parmnum, type, rhstype);  \
	  } अन्यथा {							 \
	    यदि (warning_at (PLOC, OPT, AR, parmnum, rname, QUALS))	 \
	      inform_for_arg (fundecl, (PLOC), parmnum, type, rhstype);  \
	  }								 \
	}								 \
        भङ्ग;                                                           \
      पक्ष ic_assign:                                                    \
	यदि (PEDWARN)							 \
	  pedwarn (LOCATION, OPT, AS, QUALS);                            \
	अन्यथा								 \
	  warning_at (LOCATION, OPT, AS, QUALS);                         \
        भङ्ग;                                                           \
      पक्ष ic_init:                                                      \
      पक्ष ic_init_const:                                                \
	यदि (PEDWARN)							 \
	  pedwarn (LOCATION, OPT, IN, QUALS);                            \
	अन्यथा								 \
	  warning_at (LOCATION, OPT, IN, QUALS);                         \
        भङ्ग;                                                           \
      पक्ष ic_return:                                                    \
	यदि (PEDWARN)							 \
	  pedwarn (LOCATION, OPT, RE, QUALS);                            \
	अन्यथा								 \
	  warning_at (LOCATION, OPT, RE, QUALS);                         \
        भङ्ग;                                                           \
      स्वभाव:                                                           \
        gcc_unreachable ();                                              \
      }                                                                  \
  } यावत् (0)

  /* This macro is used to emit diagnostics to ensure that all format
     strings are complete sentences, visible to gettext and checked at
     compile time.  It is the same as PEDWARN_FOR_ASSIGNMENT but with an
     extra parameter to enumerate qualifiers.  */
#define PEDWARN_FOR_QUALIFIERS(LOCATION, PLOC, OPT, AR, AS, IN, RE, QUALS) \
   WARNING_FOR_QUALIFIERS (सत्य, LOCATION, PLOC, OPT, AR, AS, IN, RE, QUALS)


  यदि (वृक्ष_CODE (rhs) == EXCESS_PRECISION_व्यंजक)
    rhs = वृक्ष_OPERAND (rhs, 0);

  rhstype = वृक्ष_TYPE (rhs);
  coder = वृक्ष_CODE (rhstype);

  यदि (coder == ERROR_MARK)
    प्रत्यागम error_mark_गाँठ;

  यदि (c_dialect_objc ())
    {
      पूर्णाङ्क parmno;

      विकल्प (errtype)
	{
	पक्ष ic_return:
	  parmno = 0;
	  भङ्ग;

	पक्ष ic_assign:
	  parmno = -1;
	  भङ्ग;

	पक्ष ic_init:
	पक्ष ic_init_const:
	  parmno = -2;
	  भङ्ग;

	स्वभाव:
	  parmno = parmnum;
	  भङ्ग;
	}

      objc_ok = objc_compare_types (type, rhstype, parmno, rname);
    }

  यदि (warn_cxx_compat)
    {
      वृक्ष checktype = origtype != NULL_वृक्ष ? origtype : rhstype;
      यदि (checktype != error_mark_गाँठ
	  && वृक्ष_CODE (type) == ENUMERAL_TYPE
	  && TYPE_MAIN_VARIANT (checktype) != TYPE_MAIN_VARIANT (type))
	विकल्प (errtype)
	  {
	  पक्ष ic_argpass:
	    यदि (pedwarn (व्यंजक_loc, OPT_Wc___compat, "enum conversion when "
			 "passing argument %d of %qE is invalid in C++",
			 parmnum, rname))
	      inform ((fundecl && !DECL_IS_UNDECLARED_BUILTIN (fundecl))
		      ? DECL_SOURCE_LOCATION (fundecl) : व्यंजक_loc,
		      "expected %qT but argument is of type %qT",
		      type, rhstype);
	    भङ्ग;
	  पक्ष ic_assign:
	    pedwarn (location, OPT_Wc___compat, "enum conversion from %qT to "
		     "%qT in assignment is invalid in C++", rhstype, type);
	    भङ्ग;
	  पक्ष ic_init:
	  पक्ष ic_init_const:
	    pedwarn_init (location, OPT_Wc___compat, "enum conversion from "
			  "%qT to %qT in initialization is invalid in C++",
			  rhstype, type);
	    भङ्ग;
	  पक्ष ic_return:
	    pedwarn (location, OPT_Wc___compat, "enum conversion from %qT to "
		     "%qT in return is invalid in C++", rhstype, type);
	    भङ्ग;
	  स्वभाव:
	    gcc_unreachable ();
	  }
    }

  यदि (warn_enum_conversion)
    {
      वृक्ष checktype = origtype != NULL_वृक्ष ? origtype : rhstype;
      यदि (checktype != error_mark_गाँठ
	  && वृक्ष_CODE (checktype) == ENUMERAL_TYPE
	  && वृक्ष_CODE (type) == ENUMERAL_TYPE
	  && !comptypes (TYPE_MAIN_VARIANT (checktype), TYPE_MAIN_VARIANT (type)))
       {
	  gcc_rich_location loc (location);
	  warning_at (&loc, OPT_Wenum_conversion,
		      "implicit conversion from %qT to %qT",
		      checktype, type);
       }
    }

  यदि (TYPE_MAIN_VARIANT (type) == TYPE_MAIN_VARIANT (rhstype))
    {
      warn_for_address_of_packed_member (type, orig_rhs);
      यदि (type != rhstype)
	/* Convert RHS to TYPE in order to not lose TYPE in diagnostics.  */
	rhs = convert (type, rhs);
      प्रत्यागम rhs;
    }

  यदि (coder == VOID_TYPE)
    {
      /* Except for passing an argument to an unprototyped function,
	 this is a constraint violation.  When passing an argument to
	 an unprototyped function, it is compile-time undefined;
	 making it a constraint in that case was rejected in
	 DR#252.  */
      ध्रुव वर्ण संदेश[] = "void value not ignored as it ought to be";
      यदि (warnopt)
	warning_at (location, warnopt, संदेश);
      अन्यथा
	error_at (location, संदेश);
      प्रत्यागम error_mark_गाँठ;
    }
  rhs = require_complete_type (location, rhs);
  यदि (rhs == error_mark_गाँठ)
    प्रत्यागम error_mark_गाँठ;

  यदि (coder == POINTER_TYPE && reject_gcc_builtin (rhs))
    प्रत्यागम error_mark_गाँठ;

  /* A non-reference type can convert to a reference.  This handles
     va_start, va_copy and possibly port built-ins.  */
  यदि (codel == REFERENCE_TYPE && coder != REFERENCE_TYPE)
    {
      यदि (!lvalue_p (rhs))
	{
	  ध्रुव वर्ण संदेश[] = "cannot pass rvalue to reference parameter";
	  यदि (warnopt)
	    warning_at (location, warnopt, संदेश);
	  अन्यथा
	    error_at (location, संदेश);
	  प्रत्यागम error_mark_गाँठ;
	}
      यदि (!c_mark_addressable (rhs))
	प्रत्यागम error_mark_गाँठ;
      rhs = build1 (ADDR_व्यंजक, c_build_pointer_type (वृक्ष_TYPE (rhs)), rhs);
      SET_व्यंजक_LOCATION (rhs, location);

      rhs = convert_for_assignment (location, व्यंजक_loc,
				    c_build_pointer_type (वृक्ष_TYPE (type)),
				    rhs, origtype, errtype,
				    null_pointer_constant, fundecl, function,
				    parmnum, warnopt);
      यदि (rhs == error_mark_गाँठ)
	प्रत्यागम error_mark_गाँठ;

      rhs = build1 (NOP_व्यंजक, type, rhs);
      SET_व्यंजक_LOCATION (rhs, location);
      प्रत्यागम rhs;
    }
  /* Some types can interconvert without explicit casts.  */
  अन्यथा यदि (codel == VECTOR_TYPE && coder == VECTOR_TYPE
	   && vector_types_convertible_p (type, वृक्ष_TYPE (rhs), सत्य))
    प्रत्यागम convert (type, rhs);
  /* Arithmetic types all interconvert, and enum is treated like int.  */
  अन्यथा यदि ((codel == INTEGER_TYPE || codel == REAL_TYPE
	    || codel == FIXED_POINT_TYPE
	    || codel == ENUMERAL_TYPE || codel == COMPLEX_TYPE
	    || codel == BOOLEAN_TYPE || codel == BITINT_TYPE)
	   && (coder == INTEGER_TYPE || coder == REAL_TYPE
	       || coder == FIXED_POINT_TYPE
	       || coder == ENUMERAL_TYPE || coder == COMPLEX_TYPE
	       || coder == BOOLEAN_TYPE || coder == BITINT_TYPE))
    {
      यदि (warnopt && errtype == ic_argpass)
	maybe_warn_builtin_no_proto_arg (व्यंजक_loc, fundecl, parmnum, type,
					 rhstype);

      तार्किक save = in_late_द्विआधारी_op;
      यदि (C_BOOLEAN_TYPE_P (type) || codel == COMPLEX_TYPE
	  || (coder == REAL_TYPE
	      && (codel == INTEGER_TYPE || codel == ENUMERAL_TYPE)
	      && sanitize_flags_p (SANITIZE_FLOAT_CAST)))
	in_late_द्विआधारी_op = सत्य;
      वृक्ष ret = convert_and_check (व्यंजक_loc != UNKNOWN_LOCATION
				    ? व्यंजक_loc : location, type, orig_rhs,
				    errtype == ic_init_const);
      in_late_द्विआधारी_op = save;
      प्रत्यागम ret;
    }

  /* Aggregates in different TUs might need conversion.  */
  यदि ((codel == RECORD_TYPE || codel == UNION_TYPE)
      && codel == coder
      && comptypes (TYPE_MAIN_VARIANT (type), TYPE_MAIN_VARIANT (rhstype)))
    प्रत्यागम convert_and_check (व्यंजक_loc != UNKNOWN_LOCATION
			      ? व्यंजक_loc : location, type, rhs);

  /* Conversion to a transparent union or record from its member types.
     This applies only to function arguments.  */
  यदि (((codel == UNION_TYPE || codel == RECORD_TYPE)
      && TYPE_TRANSPARENT_AGGR (type))
      && errtype == ic_argpass)
    {
      वृक्ष memb, marginal_memb = NULL_वृक्ष;

      प्रति (memb = TYPE_FIELDS (type); memb ; memb = DECL_CHAIN (memb))
	{
	  वृक्ष memb_type = वृक्ष_TYPE (memb);

	  यदि (comptypes (TYPE_MAIN_VARIANT (memb_type),
			 TYPE_MAIN_VARIANT (rhstype)))
	    भङ्ग;

	  यदि (वृक्ष_CODE (memb_type) != POINTER_TYPE)
	    अनुवर्त;

	  यदि (coder == POINTER_TYPE)
	    {
	      वृक्ष ttl = वृक्ष_TYPE (memb_type);
	      वृक्ष ttr = वृक्ष_TYPE (rhstype);

	      /* Any non-function converts to a [const][volatile] void *
		 and vice versa; otherwise, targets must be the same.
		 Meanwhile, the lhs target must have all the qualifiers of
		 the rhs.  */
	      यदि ((VOID_TYPE_P (ttl) && !TYPE_ATOMIC (ttl))
		  || (VOID_TYPE_P (ttr) && !TYPE_ATOMIC (ttr))
		  || comp_target_types (location, memb_type, rhstype))
		{
		  पूर्णाङ्क lquals = TYPE_QUALS (ttl) & ~TYPE_QUAL_ATOMIC;
		  पूर्णाङ्क rquals = TYPE_QUALS (ttr) & ~TYPE_QUAL_ATOMIC;
		  /* If this type won't generate any warnings, use it.  */
		  यदि (lquals == rquals
		      || ((वृक्ष_CODE (ttr) == FUNCTION_TYPE
			   && वृक्ष_CODE (ttl) == FUNCTION_TYPE)
			  ? ((lquals | rquals) == rquals)
			  : ((lquals | rquals) == lquals)))
		    भङ्ग;

		  /* Keep looking for a better type, but remember this one.  */
		  यदि (!marginal_memb)
		    marginal_memb = memb;
		}
	    }

	  /* Can convert integer zero to any pointer type.  */
	  यदि (null_pointer_constant)
	    {
	      rhs = null_pointer_गाँठ;
	      भङ्ग;
	    }
	}

      यदि (memb || marginal_memb)
	{
	  यदि (!memb)
	    {
	      /* We have only a marginally acceptable member type;
		 it needs a warning.  */
	      वृक्ष ttl = वृक्ष_TYPE (वृक्ष_TYPE (marginal_memb));
	      वृक्ष ttr = वृक्ष_TYPE (rhstype);

	      /* Const and volatile mean something different for function
		 types, so the usual warnings are not appropriate.  */
	      यदि (वृक्ष_CODE (ttr) == FUNCTION_TYPE
		  && वृक्ष_CODE (ttl) == FUNCTION_TYPE)
		{
		  /* Because const and volatile on functions are
		     restrictions that say the function will not do
		     certain things, it is okay to use a const or volatile
		     function where an ordinary one is wanted, but not
		     vice-versa.  */
		  यदि (TYPE_QUALS_NO_ADDR_SPACE (ttl)
		      & ~TYPE_QUALS_NO_ADDR_SPACE (ttr))
		    PEDWARN_FOR_QUALIFIERS (location, व्यंजक_loc,
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
	      अन्यथा यदि (TYPE_QUALS_NO_ADDR_SPACE (ttr)
		       & ~TYPE_QUALS_NO_ADDR_SPACE (ttl))
		PEDWARN_FOR_QUALIFIERS (location, व्यंजक_loc,
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

	  यदि (!fundecl || !DECL_IN_SYSTEM_HEADER (fundecl))
	    pedwarn (location, OPT_Wpedantic,
		     "ISO C prohibits argument conversion to union type");

	  rhs = fold_convert_loc (location, वृक्ष_TYPE (memb), rhs);
	  प्रत्यागम build_constructor_single (type, memb, rhs);
	}
    }

  /* Conversions among pointers */
  अन्यथा यदि ((codel == POINTER_TYPE || codel == REFERENCE_TYPE)
	   && (coder == codel))
    {
      /* If RHS refers to a built-in declared without a prototype
	 BLTIN is the declaration of the built-in with a prototype
	 and RHSTYPE is set to the actual type of the built-in.  */
      वृक्ष bltin;
      rhstype = type_or_builtin_type (rhs, &bltin);

      वृक्ष ttl = वृक्ष_TYPE (type);
      वृक्ष ttr = वृक्ष_TYPE (rhstype);
      तार्किक is_opaque_pointer;
      तार्किक target_cmp = असत्य;   /* Cache comp_target_types () result.  */
      addr_space_t asl;
      addr_space_t asr;

      वृक्ष mvl = remove_qualifiers (ttl);
      वृक्ष mvr = remove_qualifiers (ttr);

      /* Opaque pointers are treated like void pointers.  */
      is_opaque_pointer = vector_targets_convertible_p (ttl, ttr);

      /* The Plan 9 compiler permits a pointer to a struct to be
	 automatically converted into a pointer to an anonymous field
	 within the struct.  */
      यदि (flag_plan9_extensions
	  && RECORD_OR_UNION_TYPE_P (mvl)
	  && RECORD_OR_UNION_TYPE_P (mvr)
	  && mvl != mvr)
	{
	  वृक्ष new_rhs = convert_to_anonymous_field (location, type, rhs);
	  यदि (new_rhs != NULL_वृक्ष)
	    {
	      rhs = new_rhs;
	      rhstype = वृक्ष_TYPE (rhs);
	      coder = वृक्ष_CODE (rhstype);
	      ttr = वृक्ष_TYPE (rhstype);
	      mvr = TYPE_MAIN_VARIANT (ttr);
	    }
	}

      /* C++ does not allow the implicit conversion void* -> T*.  However,
	 for the purpose of reducing the number of false positives, we
	 tolerate the special case of

		int *p = NULL;

	 where NULL is typically defined in C to be '(void *) 0'.  */
      यदि (VOID_TYPE_P (ttr) && rhs != null_pointer_गाँठ && !VOID_TYPE_P (ttl))
	warning_at (errtype == ic_argpass ? व्यंजक_loc : location,
		    OPT_Wc___compat,
		    "request for implicit conversion "
		    "from %qT to %qT not permitted in C++", rhstype, type);

      /* Warn of new allocations that are not big enough for the target
	 type.  */
      यदि (warn_alloc_size && वृक्ष_CODE (rhs) == CALL_व्यंजक)
	यदि (वृक्ष fndecl = get_callee_fndecl (rhs))
	  यदि (DECL_IS_MALLOC (fndecl))
	    {
	      वृक्ष attrs = TYPE_ATTRIBUTES (वृक्ष_TYPE (fndecl));
	      वृक्ष alloc_size = lookup_attribute ("alloc_size", attrs);
	      यदि (alloc_size)
		warn_for_alloc_size (location, ttl, rhs, alloc_size);
	    }

      /* See if the pointers point to incompatible address spaces.  */
      asl = TYPE_ADDR_SPACE (ttl);
      asr = TYPE_ADDR_SPACE (ttr);
      यदि (!null_pointer_constant_p (rhs)
	  && asr != asl && !targetm.addr_space.subset_p (asr, asl))
	{
	  auto_diagnostic_group d;
	  तार्किक diagnosed = सत्य;
	  विकल्प (errtype)
	    {
	    पक्ष ic_argpass:
	      {
		ध्रुव वर्ण संदेश[] = G_("passing argument %d of %qE from "
				      "pointer to non-enclosed address space");
		यदि (warnopt)
		  diagnosed
		    = warning_at (व्यंजक_loc, warnopt, संदेश, parmnum, rname);
		अन्यथा
		  error_at (व्यंजक_loc, संदेश, parmnum, rname);
	      भङ्ग;
	      }
	    पक्ष ic_assign:
	      {
		ध्रुव वर्ण संदेश[] = G_("assignment from pointer to "
				      "non-enclosed address space");
		यदि (warnopt)
		  diagnosed = warning_at (location, warnopt, संदेश);
		अन्यथा
		  error_at (location, संदेश);
		भङ्ग;
	      }
	    पक्ष ic_init:
	    पक्ष ic_init_const:
	      {
		ध्रुव वर्ण संदेश[] = G_("initialization from pointer to "
				      "non-enclosed address space");
		यदि (warnopt)
		  diagnosed = warning_at (location, warnopt, संदेश);
		अन्यथा
		  error_at (location, संदेश);
		भङ्ग;
	      }
	    पक्ष ic_return:
	      {
		ध्रुव वर्ण संदेश[] = G_("return from pointer to "
				      "non-enclosed address space");
		यदि (warnopt)
		  diagnosed = warning_at (location, warnopt, संदेश);
		अन्यथा
		  error_at (location, संदेश);
		भङ्ग;
	      }
	    स्वभाव:
	      gcc_unreachable ();
	    }
	  यदि (diagnosed)
	    {
	      यदि (errtype == ic_argpass)
		inform_for_arg (fundecl, व्यंजक_loc, parmnum, type, rhstype);
	      अन्यथा
		inform (location, "expected %qT but pointer is of type %qT",
			type, rhstype);
	    }
	  प्रत्यागम error_mark_गाँठ;
	}

      /* Check if the right-hand side has a format attribute but the
	 left-hand side doesn't.  */
      यदि (warn_suggest_attribute_format
	  && check_missing_format_attribute (type, rhstype))
	{
	  विकल्प (errtype)
	  {
	  पक्ष ic_argpass:
	    warning_at (व्यंजक_loc, OPT_Wsuggest_attribute_format,
			"argument %d of %qE might be "
			"a candidate for a format attribute",
			parmnum, rname);
	    भङ्ग;
	  पक्ष ic_assign:
	    warning_at (location, OPT_Wsuggest_attribute_format,
			"assignment left-hand side might be "
			"a candidate for a format attribute");
	    भङ्ग;
	  पक्ष ic_init:
	  पक्ष ic_init_const:
	    warning_at (location, OPT_Wsuggest_attribute_format,
			"initialization left-hand side might be "
			"a candidate for a format attribute");
	    भङ्ग;
	  पक्ष ic_return:
	    warning_at (location, OPT_Wsuggest_attribute_format,
			"return type might be "
			"a candidate for a format attribute");
	    भङ्ग;
	  स्वभाव:
	    gcc_unreachable ();
	  }
	}

      /* See if the pointers point to incompatible scalar storage orders.  */
      यदि (warn_scalar_storage_order
	  && !null_pointer_constant_p (rhs)
	  && (AGGREGATE_TYPE_P (ttl) && TYPE_REVERSE_STORAGE_ORDER (ttl))
	     != (AGGREGATE_TYPE_P (ttr) && TYPE_REVERSE_STORAGE_ORDER (ttr)))
	{
	  वृक्ष t;

	  विकल्प (errtype)
	  {
	  पक्ष ic_argpass:
	    /* Do not warn for built-in functions, for example memcpy, since we
	       control how they behave and they can be useful in this area.  */
	    यदि (वृक्ष_CODE (rname) != FUNCTION_DECL
		|| !fndecl_built_in_p (rname))
	      warning_at (location, OPT_Wscalar_storage_order,
			  "passing argument %d of %qE from incompatible "
			  "scalar storage order", parmnum, rname);
	    भङ्ग;
	  पक्ष ic_assign:
	    /* Do not warn if the RHS is a call to a function that returns a
	       pointer that is not an alias.  */
	    यदि (वृक्ष_CODE (rhs) != CALL_व्यंजक
		|| (t = get_callee_fndecl (rhs)) == NULL_वृक्ष
		|| !DECL_IS_MALLOC (t))
	      warning_at (location, OPT_Wscalar_storage_order,
			  "assignment to %qT from pointer type %qT with "
			  "incompatible scalar storage order", type, rhstype);
	    भङ्ग;
	  पक्ष ic_init:
	  पक्ष ic_init_const:
	    /* Likewise.  */
	    यदि (वृक्ष_CODE (rhs) != CALL_व्यंजक
		|| (t = get_callee_fndecl (rhs)) == NULL_वृक्ष
		|| !DECL_IS_MALLOC (t))
	      warning_at (location, OPT_Wscalar_storage_order,
			  "initialization of %qT from pointer type %qT with "
			  "incompatible scalar storage order", type, rhstype);
	    भङ्ग;
	  पक्ष ic_return:
	    warning_at (location, OPT_Wscalar_storage_order,
			"returning %qT from pointer type with incompatible "
			"scalar storage order %qT", rhstype, type);
	    भङ्ग;
	  स्वभाव:
	    gcc_unreachable ();
	  }
	}

      /* Any non-function converts to a [const][volatile] void *
	 and vice versa; otherwise, targets must be the same.
	 Meanwhile, the lhs target must have all the qualifiers of the rhs.  */
      यदि ((VOID_TYPE_P (ttl) && !TYPE_ATOMIC (ttl))
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
	  यदि (वृक्ष_CODE (ttr) == ARRAY_TYPE)
	    {
	      ttr = strip_array_types (ttr);
	      ttl = strip_array_types (ttl);

	      यदि (TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttr)
		  & ~TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttl))
		WARNING_FOR_QUALIFIERS (flag_isoc23,
					location, व्यंजक_loc,
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
          अन्यथा यदि (pedantic
	      && ((VOID_TYPE_P (ttl) && वृक्ष_CODE (ttr) == FUNCTION_TYPE)
		  ||
		  (VOID_TYPE_P (ttr)
		   && !null_pointer_constant
		   && वृक्ष_CODE (ttl) == FUNCTION_TYPE)))
	    PEDWARN_FOR_ASSIGNMENT (location, व्यंजक_loc, OPT_Wpedantic,
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
	  अन्यथा यदि (वृक्ष_CODE (ttr) != FUNCTION_TYPE
		   && वृक्ष_CODE (ttl) != FUNCTION_TYPE)
	    {
	       /* Assignments between atomic and non-atomic objects are OK.  */
	       तार्किक warn_quals_ped = TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttr)
				     & ~TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttl);
	       तार्किक warn_quals = TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttr)
				 & ~TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (strip_array_types (ttl));

	      /* Don't warn about loss of qualifier for conversions from
		 qualified void* to pointers to arrays with corresponding
		 qualifier on the element type (except for pedantic before C23). */
	      यदि (warn_quals || (warn_quals_ped && pedantic && !flag_isoc23))
		PEDWARN_FOR_QUALIFIERS (location, व्यंजक_loc,
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
	      अन्यथा यदि (warn_quals_ped)
		pedwarn_c11 (location, OPT_Wc11_c23_compat,
			     "array with qualifier on the element is not qualified before C23");

	      /* If this is not a case of ignoring a mismatch in signedness,
		 no warning.  */
	      अन्यथा यदि (VOID_TYPE_P (ttl) || VOID_TYPE_P (ttr)
		       || target_cmp)
		;
	      /* If there is a mismatch, do warn.  */
	      अन्यथा यदि (warn_pointer_sign)
		विकल्प (errtype)
		  {
		  पक्ष ic_argpass:
		    {
		      auto_diagnostic_group d;
		      range_label_for_type_mismatch rhs_label (rhstype, type);
		      gcc_rich_location richloc (व्यंजक_loc, &rhs_label,
						 highlight_colors::actual);
		      यदि (pedwarn (&richloc, OPT_Wpointer_sign,
				   "pointer targets in passing argument %d of "
				   "%qE differ in signedness", parmnum, rname))
			inform_for_arg (fundecl, व्यंजक_loc, parmnum, type,
					rhstype);
		    }
		    भङ्ग;
		  पक्ष ic_assign:
		    pedwarn (location, OPT_Wpointer_sign,
			     "pointer targets in assignment from %qT to %qT "
			     "differ in signedness", rhstype, type);
		    भङ्ग;
		  पक्ष ic_init:
		  पक्ष ic_init_const:
		    pedwarn_init (location, OPT_Wpointer_sign,
				  "pointer targets in initialization of %qT "
				  "from %qT differ in signedness", type,
				  rhstype);
		    भङ्ग;
		  पक्ष ic_return:
		    pedwarn (location, OPT_Wpointer_sign, "pointer targets in "
			     "returning %qT from a function with return type "
			     "%qT differ in signedness", rhstype, type);
		    भङ्ग;
		  स्वभाव:
		    gcc_unreachable ();
		  }
	    }
	  अन्यथा यदि (वृक्ष_CODE (ttl) == FUNCTION_TYPE
		   && वृक्ष_CODE (ttr) == FUNCTION_TYPE)
	    {
	      /* Because const and volatile on functions are restrictions
		 that say the function will not do certain things,
		 it is okay to use a const or volatile function
		 where an ordinary one is wanted, but not vice-versa.  */
	      यदि (TYPE_QUALS_NO_ADDR_SPACE (ttl)
		  & ~TYPE_QUALS_NO_ADDR_SPACE (ttr))
		PEDWARN_FOR_QUALIFIERS (location, व्यंजक_loc,
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
      अन्यथा यदि (!objc_ok)
	{
	  auto_diagnostic_group d;
	  तार्किक warned = असत्य;
	  pp_markup::element_expected_type e_type (type);
	  pp_markup::element_actual_type e_rhstype (rhstype);
	  विकल्प (errtype)
	    {
	    पक्ष ic_argpass:
	      {
		range_label_for_type_mismatch rhs_label (rhstype, type);
		gcc_rich_location richloc (व्यंजक_loc, &rhs_label,
					   highlight_colors::actual);
		warned
		  = permerror_opt (&richloc, OPT_Wincompatible_pointer_types,
				   "passing argument %d of %qE from "
				   "incompatible pointer type",
				   parmnum, rname);
		यदि (warned)
		  inform_for_arg (fundecl, व्यंजक_loc, parmnum, type, rhstype);
	      }
	      भङ्ग;
	    पक्ष ic_assign:
	      यदि (bltin)
		warned
		  = permerror_opt (location, OPT_Wincompatible_pointer_types,
				   "assignment to %e from pointer to "
				   "%qD with incompatible type %e",
				   &e_type, bltin, &e_rhstype);
	      अन्यथा
		warned
		  = permerror_opt (location, OPT_Wincompatible_pointer_types,
				   "assignment to %e from incompatible "
				   "pointer type %e",
				   &e_type, &e_rhstype);
	      भङ्ग;
	    पक्ष ic_init:
	    पक्ष ic_init_const:
	      यदि (bltin)
		warned
		  = permerror_init (location, OPT_Wincompatible_pointer_types,
				    "initialization of %e from pointer to "
				    "%qD with incompatible type %e",
				    &e_type, bltin, &e_rhstype);
	      अन्यथा
		warned
		  = permerror_init (location, OPT_Wincompatible_pointer_types,
				    "initialization of %e from incompatible "
				    "pointer type %e",
				    &e_type, &e_rhstype);
	      भङ्ग;
	    पक्ष ic_return:
	      यदि (bltin)
		warned
		  = permerror_opt (location, OPT_Wincompatible_pointer_types,
				   "returning pointer to %qD of type %e from "
				   "a function with incompatible type %e",
				   bltin, &e_rhstype, &e_type);
	      अन्यथा
		warned
		  = permerror_opt (location, OPT_Wincompatible_pointer_types,
				   "returning %e from a function with "
				   "incompatible return type %e",
				   &e_rhstype, &e_type);
	      भङ्ग;
	    स्वभाव:
	      gcc_unreachable ();
	    }
	  यदि (warned)
	    {
	      /* If the mismatching function type is a pointer to a function,
		 try to show the decl of the function.  */
	      यदि (वृक्ष_CODE (rhs) == ADDR_व्यंजक
		  && वृक्ष_CODE (वृक्ष_OPERAND (rhs, 0)) == FUNCTION_DECL)
		{
		  वृक्ष rhs_fndecl = वृक्ष_OPERAND (rhs, 0);
		  यदि (!DECL_IS_UNDECLARED_BUILTIN (rhs_fndecl))
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

      प्रत्यागम convert (type, rhs);
    }
  अन्यथा यदि (codel == POINTER_TYPE && coder == ARRAY_TYPE)
    {
      /* ??? This should not be an error when inlining calls to
	 unprototyped functions.  */
      ध्रुव वर्ण संदेश[] = "invalid use of non-lvalue array";
      यदि (warnopt)
	warning_at (location, warnopt, संदेश);
      अन्यथा
	error_at (location, संदेश);
      प्रत्यागम error_mark_गाँठ;
    }
  अन्यथा यदि (codel == POINTER_TYPE
	   && (coder == INTEGER_TYPE
	       || coder == ENUMERAL_TYPE
	       || coder == BOOLEAN_TYPE
	       || coder == NULLPTR_TYPE
	       || coder == BITINT_TYPE))
    {
      यदि (null_pointer_constant && c_inhibit_evaluation_warnings == 0
	  && coder != NULLPTR_TYPE)
	warning_at (location, OPT_Wzero_as_null_pointer_constant,
		    "zero as null pointer constant");
      /* A NULLPTR type is just a nullptr always.  */
      यदि (coder == NULLPTR_TYPE)
	प्रत्यागम omit_one_operand_loc (व्यंजक_loc, type, nullptr_गाँठ, rhs);
      /* An explicit constant 0 or type nullptr_t can convert to a pointer,
	 or one that results from arithmetic, even including a cast to
	 integer type.  */
      अन्यथा यदि (!null_pointer_constant)
	विकल्प (errtype)
	  {
	  पक्ष ic_argpass:
	    {
	      auto_diagnostic_group d;
	      range_label_for_type_mismatch rhs_label (rhstype, type);
	      gcc_rich_location richloc (व्यंजक_loc, &rhs_label,
					 highlight_colors::actual);
	      यदि (permerror_opt (&richloc, OPT_Wint_conversion,
				 "passing argument %d of %qE makes pointer "
				 "from integer without a cast", parmnum, rname))
		{
		  maybe_emit_indirection_note (व्यंजक_loc, rhs, type);
		  inform_for_arg (fundecl, व्यंजक_loc, parmnum, type, rhstype);
		}
	    }
	    भङ्ग;
	  पक्ष ic_assign:
	    permerror_opt (location, OPT_Wint_conversion,
			   "assignment to %qT from %qT makes pointer from "
			   "integer without a cast", type, rhstype);
	    भङ्ग;
	  पक्ष ic_init:
	  पक्ष ic_init_const:
	    permerror_init (location, OPT_Wint_conversion,
			    "initialization of %qT from %qT makes pointer "
			    "from integer without a cast", type, rhstype);
	    भङ्ग;
	  पक्ष ic_return:
	    permerror_init (location, OPT_Wint_conversion,
			    "returning %qT from a function with return type "
			    "%qT makes pointer from integer without a cast",
			    rhstype, type);
	    भङ्ग;
	  स्वभाव:
	    gcc_unreachable ();
	  }

      प्रत्यागम convert (type, rhs);
    }
  अन्यथा यदि ((codel == INTEGER_TYPE || codel == BITINT_TYPE)
	   && coder == POINTER_TYPE)
    {
      विकल्प (errtype)
	{
	पक्ष ic_argpass:
	  {
	    auto_diagnostic_group d;
	    range_label_for_type_mismatch rhs_label (rhstype, type);
	    gcc_rich_location richloc (व्यंजक_loc, &rhs_label,
				       highlight_colors::actual);
	    यदि (permerror_opt (&richloc, OPT_Wint_conversion,
			       "passing argument %d of %qE makes integer from "
			       "pointer without a cast", parmnum, rname))
	      {
		maybe_emit_indirection_note (व्यंजक_loc, rhs, type);
		inform_for_arg (fundecl, व्यंजक_loc, parmnum, type, rhstype);
	      }
	  }
	  भङ्ग;
	पक्ष ic_assign:
	  permerror_opt (location, OPT_Wint_conversion,
			 "assignment to %qT from %qT makes integer from "
			 "pointer without a cast", type, rhstype);
	  भङ्ग;
	पक्ष ic_init:
	पक्ष ic_init_const:
	  permerror_init (location, OPT_Wint_conversion,
			  "initialization of %qT from %qT makes integer "
			  "from pointer without a cast", type, rhstype);
	  भङ्ग;
	पक्ष ic_return:
	  permerror_opt (location, OPT_Wint_conversion, "returning %qT from a "
			 "function with return type %qT makes integer from "
			 "pointer without a cast", rhstype, type);
	  भङ्ग;
	स्वभाव:
	  gcc_unreachable ();
	}

      प्रत्यागम convert (type, rhs);
    }
  अन्यथा यदि (C_BOOLEAN_TYPE_P (type)
	   /* The type nullptr_t may be converted to bool.  The
	      result is false.  */
	   && (coder == POINTER_TYPE || coder == NULLPTR_TYPE))
    {
      वृक्ष ret;
      तार्किक save = in_late_द्विआधारी_op;
      in_late_द्विआधारी_op = सत्य;
      ret = convert (type, rhs);
      in_late_द्विआधारी_op = save;
      प्रत्यागम ret;
    }
  अन्यथा यदि (codel == NULLPTR_TYPE && null_pointer_constant)
    प्रत्यागम convert (type, rhs);

  विकल्प (errtype)
    {
    पक्ष ic_argpass:
      {
	auto_diagnostic_group d;
	range_label_for_type_mismatch rhs_label (rhstype, type);
	gcc_rich_location richloc (व्यंजक_loc, &rhs_label,
				   highlight_colors::actual);
	ध्रुव वर्ण संदेश[] = G_("incompatible type for argument %d of %qE");
	यदि (warnopt)
	  warning_at (व्यंजक_loc, warnopt, संदेश, parmnum, rname);
	अन्यथा
	  error_at (&richloc, संदेश, parmnum, rname);
	inform_for_arg (fundecl, व्यंजक_loc, parmnum, type, rhstype);
      }
      भङ्ग;
    पक्ष ic_assign:
      {
	ध्रुव वर्ण संदेश[]
	  = G_("incompatible types when assigning to type %qT from type %qT");
	यदि (warnopt)
	  warning_at (व्यंजक_loc, 0, संदेश, type, rhstype);
	अन्यथा
	  error_at (व्यंजक_loc, संदेश, type, rhstype);
	भङ्ग;
      }
    पक्ष ic_init:
    पक्ष ic_init_const:
      {
	ध्रुव वर्ण संदेश[]
	  = G_("incompatible types when initializing type %qT using type %qT");
	यदि (warnopt)
	  warning_at (location, 0, संदेश, type, rhstype);
	अन्यथा
	  error_at (location, संदेश, type, rhstype);
	भङ्ग;
      }
    पक्ष ic_return:
      {
	ध्रुव वर्ण संदेश[]
	  = G_("incompatible types when returning type %qT but %qT was expected");
	यदि (warnopt)
	  warning_at (location, 0, संदेश, rhstype, type);
	अन्यथा
	  error_at (location, संदेश, rhstype, type);
	भङ्ग;
      }
    स्वभाव:
      gcc_unreachable ();
    }

  प्रत्यागम error_mark_गाँठ;
}

/* If VALUE is a compound expr all of whose expressions are constant, then
   return its value.  Otherwise, return error_mark_node.

   This is for handling COMPOUND_EXPRs as initializer elements
   which is allowed with a warning when -pedantic is specified.  */

स्थिर वृक्ष
valid_compound_व्यंजक_initializer (वृक्ष मूल्य, वृक्ष endtype)
{
  यदि (वृक्ष_CODE (मूल्य) == COMPOUND_व्यंजक)
    {
      यदि (valid_compound_व्यंजक_initializer (वृक्ष_OPERAND (मूल्य, 0), endtype)
	  == error_mark_गाँठ)
	प्रत्यागम error_mark_गाँठ;
      प्रत्यागम valid_compound_व्यंजक_initializer (वृक्ष_OPERAND (मूल्य, 1),
					      endtype);
    }
  अन्यथा यदि (!initializer_constant_valid_p (मूल्य, endtype))
    प्रत्यागम error_mark_गाँठ;
  अन्यथा
    प्रत्यागम मूल्य;
}

/* Perform appropriate conversions on the initial value of a variable,
   store it in the declaration DECL,
   and print any error messages that are appropriate.
   If ORIGTYPE is not NULL_TREE, it is the original type of INIT.
   If the init is invalid, store an ERROR_MARK.

   INIT_LOC is the location of the initial value.  */

शून्य
store_init_मूल्य (location_t init_loc, वृक्ष decl, वृक्ष init, वृक्ष origtype)
{
  वृक्ष मूल्य, type;
  तार्किक npc = असत्य;
  तार्किक int_const_व्यंजक = असत्य;
  तार्किक arith_const_व्यंजक = असत्य;

  /* If variable's type was invalidly declared, just ignore it.  */

  type = वृक्ष_TYPE (decl);
  यदि (वृक्ष_CODE (type) == ERROR_MARK)
    प्रत्यागम;

  /* Digest the specified initializer into an expression.  */

  यदि (init)
    {
      npc = null_pointer_constant_p (init);
      int_const_व्यंजक = (वृक्ष_CODE (init) == INTEGER_CST
			&& !वृक्ष_OVERFLOW (init)
			&& INTEGRAL_TYPE_P (वृक्ष_TYPE (init)));
      /* Not fully determined before folding.  */
      arith_const_व्यंजक = सत्य;
    }
  तार्किक constexpr_p = (VAR_P (decl)
		      && C_DECL_DECLARED_CONSTEXPR (decl));
  मूल्य = digest_init (init_loc, decl, type, init, origtype, npc,
		       int_const_व्यंजक, arith_const_व्यंजक, सत्य,
		       वृक्ष_STATIC (decl) || constexpr_p, constexpr_p);

  /* Store the expression if valid; else report error.  */

  यदि (!in_system_header_at (निवेश_location)
      && AGGREGATE_TYPE_P (वृक्ष_TYPE (decl)) && !वृक्ष_STATIC (decl))
    warning (OPT_Wtraditional, "traditional C rejects automatic "
	     "aggregate initialization");

  यदि (मूल्य != error_mark_गाँठ || वृक्ष_CODE (decl) != FUNCTION_DECL)
    DECL_INITIAL (decl) = मूल्य;

  /* ANSI wants warnings about out-of-range constant initializers.  */
  STRIP_TYPE_NOPS (मूल्य);
  यदि (वृक्ष_STATIC (decl))
    constant_expression_warning (मूल्य);

  /* Check if we need to set array size from compound literal size.  */
  यदि (वृक्ष_CODE (type) == ARRAY_TYPE
      && TYPE_DOMAIN (type) == NULL_वृक्ष
      && मूल्य != error_mark_गाँठ)
    {
      वृक्ष inside_init = init;

      STRIP_TYPE_NOPS (inside_init);
      inside_init = fold (inside_init);

      यदि (वृक्ष_CODE (inside_init) == COMPOUND_LITERAL_व्यंजक)
	{
	  वृक्ष cldecl = COMPOUND_LITERAL_व्यंजक_DECL (inside_init);

	  यदि (TYPE_DOMAIN (वृक्ष_TYPE (cldecl)))
	    {
	      /* For int foo[] = (int [3]){1}; we need to set array size
		 now since later on array initializer will be just the
		 brace enclosed list of the compound literal.  */
	      वृक्ष etype = strip_array_types (वृक्ष_TYPE (decl));
	      type = build_distinct_type_copy (TYPE_MAIN_VARIANT (type));
	      TYPE_DOMAIN (type) = TYPE_DOMAIN (वृक्ष_TYPE (cldecl));
	      layout_type (type);
	      layout_decl (cldecl, 0);
	      वृक्ष_TYPE (decl)
		= c_build_qualified_type (type, TYPE_QUALS (etype));
	    }
	}
    }
}

/* Methods for storing and printing names for error messages.  */

/* Implement a spelling stack that allows components of a name to be pushed
   and popped.  Each element on the stack is this structure.  */

संरचना spelling
{
  पूर्णाङ्क kind;
  सङ्घ
    {
      अचिन्हित HOST_WIDE_INT i;
      ध्रुव वर्ण *s;
    } u;
};

#define SPELLING_STRING 1
#define SPELLING_MEMBER 2
#define SPELLING_BOUNDS 3

स्थिर संरचना spelling *spelling;	/* Next stack element (unused).  */
स्थिर संरचना spelling *spelling_base;	/* Spelling stack base.  */
स्थिर पूर्णाङ्क spelling_size;		/* Size of the spelling stack.  */

/* Macros to save and restore the spelling stack around push_... functions.
   Alternative to SAVE_SPELLING_STACK.  */

#define SPELLING_DEPTH() (spelling - spelling_base)
#define RESTORE_SPELLING_DEPTH(DEPTH) (spelling = spelling_base + (DEPTH))

/* Push an element on the spelling stack with type KIND and assign VALUE
   to MEMBER.  */

#define धकेलो_SPELLING(KIND, मूल्य_2, MEMBER)				\
{									\
  पूर्णाङ्क depth = SPELLING_DEPTH ();					\
									\
  यदि (depth >= spelling_size)						\
    {									\
      spelling_size += 10;						\
      spelling_base = XRESIZEVEC (संरचना spelling, spelling_base,	\
				  spelling_size);			\
      RESTORE_SPELLING_DEPTH (depth);					\
    }									\
									\
  spelling->kind = (KIND);						\
  spelling->MEMBER = (मूल्य_2);						\
  spelling++;								\
}

/* Push STRING on the stack.  Printed literally.  */

स्थिर शून्य
धकेलो_string (ध्रुव वर्ण *string)
{
  धकेलो_SPELLING (SPELLING_STRING, string, u.s);
}

/* Push a member name on the stack.  Printed as '.' STRING.  */

स्थिर शून्य
धकेलो_member_name (वृक्ष decl)
{
  ध्रुव वर्ण *ध्रुव string
    = (DECL_NAME (decl)
       ? identifier_to_locale (IDENTIFIER_POINTER (DECL_NAME (decl)))
       : _("<anonymous>"));
  धकेलो_SPELLING (SPELLING_MEMBER, string, u.s);
}

/* Push an array bounds on the stack.  Printed as [BOUNDS].  */

स्थिर शून्य
धकेलो_array_bounds (अचिन्हित HOST_WIDE_INT bounds)
{
  धकेलो_SPELLING (SPELLING_BOUNDS, bounds, u.i);
}

/* Compute the maximum size in bytes of the printed spelling.  */

स्थिर पूर्णाङ्क
spelling_length (शून्य)
{
  पूर्णाङ्क size = 0;
  संरचना spelling *p;

  प्रति (p = spelling_base; p < spelling; p++)
    {
      यदि (p->kind == SPELLING_BOUNDS)
	size += 25;
      अन्यथा
	size += म_माप (p->u.s) + 1;
    }

  प्रत्यागम size;
}

/* Print the spelling to BUFFER and return it.  */

स्थिर वर्ण *
print_spelling (वर्ण *buffer)
{
  वर्ण *d = buffer;
  संरचना spelling *p;

  प्रति (p = spelling_base; p < spelling; p++)
    यदि (p->kind == SPELLING_BOUNDS)
      {
	प्र_लिखो (d, "[" HOST_WIDE_INT_PRINT_UNSIGNED "]", p->u.i);
	d += म_माप (d);
      }
    अन्यथा
      {
	ध्रुव वर्ण *s;
	यदि (p->kind == SPELLING_MEMBER)
	  *d++ = '.';
	प्रति (s = p->u.s; (*d = *s++); d++)
	  ;
      }
  *d++ = '\0';
  प्रत्यागम buffer;
}

/* Check whether INIT, a floating or integer constant, is
   representable in TYPE, a real floating type with the same radix or
   a decimal floating type initialized with a binary floating
   constant.  Return true if OK, false if not.  */
स्थिर तार्किक
constexpr_init_fits_real_type (वृक्ष type, वृक्ष init)
{
  gcc_assert (SCALAR_FLOAT_TYPE_P (type));
  gcc_assert (वृक्ष_CODE (init) == INTEGER_CST || वृक्ष_CODE (init) == REAL_CST);
  यदि (वृक्ष_CODE (init) == REAL_CST
      && TYPE_MODE (वृक्ष_TYPE (init)) == TYPE_MODE (type))
    {
      /* Same mode, no conversion required except for the case of
	 signaling NaNs if the types are incompatible (e.g. double and
	 long double with the same mode).  */
      यदि (REAL_मूल्य_ISSIGNALING_NAN (वृक्ष_REAL_CST (init))
	  && !comptypes (TYPE_MAIN_VARIANT (type),
			 TYPE_MAIN_VARIANT (वृक्ष_TYPE (init))))
	प्रत्यागम असत्य;
      प्रत्यागम सत्य;
    }
  यदि (वृक्ष_CODE (init) == INTEGER_CST)
    {
      वृक्ष converted = build_real_from_int_cst (type, init);
      तार्किक fail = असत्य;
      wide_int w = real_to_integer (&वृक्ष_REAL_CST (converted), &fail,
				    TYPE_PRECISION (वृक्ष_TYPE (init)));
      प्रत्यागम !fail && wi::eq_p (w, wi::to_wide (init));
    }
  यदि (REAL_मूल्य_ISSIGNALING_NAN (वृक्ष_REAL_CST (init)))
    प्रत्यागम असत्य;
  यदि ((REAL_मूल्य_ISINF (वृक्ष_REAL_CST (init))
       && MODE_HAS_INFINITIES (TYPE_MODE (type)))
      || (REAL_मूल्य_ISNAN (वृक्ष_REAL_CST (init))
	  && MODE_HAS_NANS (TYPE_MODE (type))))
    प्रत्यागम सत्य;
  यदि (DECIMAL_FLOAT_TYPE_P (type)
      && !DECIMAL_FLOAT_TYPE_P (वृक्ष_TYPE (init)))
    {
      /* This is valid if the real number represented by the
	 initializer can be exactly represented in the decimal
	 type.  Compare the values using MPFR.  */
      REAL_मूल्य_TYPE t;
      real_convert (&t, TYPE_MODE (type), &वृक्ष_REAL_CST (init));
      mpfr_t bin_val, dec_val;
      mpfr_init2 (bin_val, REAL_MODE_FORMAT (TYPE_MODE (वृक्ष_TYPE (init)))->p);
      mpfr_init2 (dec_val, REAL_MODE_FORMAT (TYPE_MODE (वृक्ष_TYPE (init)))->p);
      mpfr_from_real (bin_val, &वृक्ष_REAL_CST (init), MPFR_RNDN);
      वर्ण string[256];
      real_to_decimal (string, &t, परिमाण string, 0, 1);
      तार्किक res = (mpfr_strtofr (dec_val, string, रिक्त, 10, MPFR_RNDN) == 0
		  && mpfr_equal_p (bin_val, dec_val));
      mpfr_clear (bin_val);
      mpfr_clear (dec_val);
      प्रत्यागम res;
    }
  /* exact_real_truncate is not quite right here, since it doesn't
     allow even an exact conversion to subnormal values.  */
  REAL_मूल्य_TYPE t;
  real_convert (&t, TYPE_MODE (type), &वृक्ष_REAL_CST (init));
  प्रत्यागम real_identical (&t, &वृक्ष_REAL_CST (init));
}

/* Check whether INIT (location LOC) is valid as a 'constexpr'
   initializer for type TYPE, and give an error if not.  INIT has
   already been folded and verified to be constant.  INT_CONST_EXPR
   and ARITH_CONST_EXPR say whether it is an integer constant
   expression or arithmetic constant expression, respectively.  If
   TYPE is not a scalar type, this function does nothing.  */

स्थिर शून्य
check_constexpr_init (location_t loc, वृक्ष type, वृक्ष init,
		      तार्किक int_const_व्यंजक, तार्किक arith_const_व्यंजक)
{
  यदि (POINTER_TYPE_P (type))
    {
      /* The initializer must be null.  */
      यदि (वृक्ष_CODE (init) != INTEGER_CST || !integer_zerop (init))
	error_at (loc, "%<constexpr%> pointer initializer is not null");
      प्रत्यागम;
    }
  यदि (INTEGRAL_TYPE_P (type))
    {
      /* The initializer must be an integer constant expression,
	 representable in the target type.  */
      यदि (!int_const_व्यंजक)
	{
	  यदि (वृक्ष_CODE (init) == RAW_DATA_CST
	      && TYPE_PRECISION (type) == अक्षर_बिट)
	    {
	      यदि (!TYPE_UNSIGNED (type))
		प्रति (अचिन्हित पूर्णाङ्क i = 0;
		     i < (अचिन्हित) RAW_DATA_LENGTH (init); ++i)
		  यदि (RAW_DATA_SCHAR_ELT (init, i) < 0)
		    {
		      error_at (loc, "%<constexpr%> initializer not "
				"representable in type of object");
		      भङ्ग;
		    }
	    }
	  अन्यथा
	    error_at (loc, "%<constexpr%> integer initializer is not an "
		      "integer constant expression");
	}
      अन्यथा यदि (!int_fits_type_p (init, type))
	error_at (loc, "%<constexpr%> initializer not representable in "
		  "type of object");
      प्रत्यागम;
    }
  /* We don't apply any extra checks to extension types such as vector
     or fixed-point types.  */
  यदि (वृक्ष_CODE (type) != REAL_TYPE && वृक्ष_CODE (type) != COMPLEX_TYPE)
    प्रत्यागम;
  यदि (!arith_const_व्यंजक)
    {
      error_at (loc, "%<constexpr%> initializer is not an arithmetic "
		"constant expression");
      प्रत्यागम;
    }
  /* We don't apply any extra checks to complex integers.  */
  यदि (वृक्ष_CODE (type) == COMPLEX_TYPE
      && वृक्ष_CODE (वृक्ष_TYPE (type)) != REAL_TYPE)
    प्रत्यागम;
  /* Following N3082, a real type cannot be initialized from a complex
     type and a binary type cannot be initialized from a decimal type
     (but initializing a decimal type from a binary type is OK).
     Signaling NaN initializers are OK only if the types are
     compatible (not just the same mode); all quiet NaN and infinity
     initializations are considered to preserve the value.  */
  यदि (वृक्ष_CODE (वृक्ष_TYPE (init)) == COMPLEX_TYPE
      && SCALAR_FLOAT_TYPE_P (type))
    {
      error_at (loc, "%<constexpr%> initializer for a real type is of "
		"complex type");
      प्रत्यागम;
    }
  यदि (SCALAR_FLOAT_TYPE_P (type)
      && SCALAR_FLOAT_TYPE_P (वृक्ष_TYPE (init))
      && DECIMAL_FLOAT_TYPE_P (वृक्ष_TYPE (init))
      && !DECIMAL_FLOAT_TYPE_P (type))
    {
      error_at (loc, "%<constexpr%> initializer for a binary "
		"floating-point type is of decimal type");
      प्रत्यागम;
    }
  तार्किक fits;
  यदि (वृक्ष_CODE (type) == COMPLEX_TYPE)
    {
      विकल्प (वृक्ष_CODE (init))
	{
	पक्ष INTEGER_CST:
	पक्ष REAL_CST:
	  fits = constexpr_init_fits_real_type (वृक्ष_TYPE (type), init);
	  भङ्ग;
	पक्ष COMPLEX_CST:
	  fits = (constexpr_init_fits_real_type (वृक्ष_TYPE (type),
						 वृक्ष_REALPART (init))
		  && constexpr_init_fits_real_type (वृक्ष_TYPE (type),
						    वृक्ष_IMAGPART (init)));
	  भङ्ग;
	स्वभाव:
	  gcc_unreachable ();
	}
    }
  अन्यथा
    fits = constexpr_init_fits_real_type (type, init);
  यदि (!fits)
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

स्थिर वृक्ष
digest_init (location_t init_loc, वृक्ष decl, वृक्ष type, वृक्ष init,
	     वृक्ष origtype, तार्किक null_pointer_constant, तार्किक int_const_व्यंजक,
	     तार्किक arith_const_व्यंजक, तार्किक strict_string,
	     तार्किक require_constant, तार्किक require_constexpr)
{
  गणना वृक्ष_code code = वृक्ष_CODE (type);
  वृक्ष inside_init = init;
  वृक्ष semantic_type = NULL_वृक्ष;
  तार्किक maybe_const = सत्य;

  यदि (type == error_mark_गाँठ
      || !init
      || error_operand_p (init))
    प्रत्यागम error_mark_गाँठ;

  STRIP_TYPE_NOPS (inside_init);

  /* If require_constant is TRUE,  when the initializer is a call to
     .ACCESS_WITH_SIZE, use the first argument as the initializer.
     For example:
     y = (char *) .ACCESS_WITH_SIZE ((char *) &static_annotated.c,...)
     will be converted to
     y = &static_annotated.c.  */

  यदि (require_constant
      && वृक्ष_CODE (inside_init) == NOP_व्यंजक
      && वृक्ष_CODE (वृक्ष_OPERAND (inside_init, 0)) == CALL_व्यंजक
      && is_access_with_size_p (वृक्ष_OPERAND (inside_init, 0)))
    inside_init
      = get_ref_from_access_with_size (वृक्ष_OPERAND (inside_init, 0));

  यदि (!c_in_omp_for)
    {
      यदि (वृक्ष_CODE (inside_init) == EXCESS_PRECISION_व्यंजक)
	{
	  semantic_type = वृक्ष_TYPE (inside_init);
	  inside_init = वृक्ष_OPERAND (inside_init, 0);
	}
      inside_init = c_fully_fold (inside_init, require_constant, &maybe_const);
    }
  /* TODO: this may not detect all cases of expressions folding to
     constants that are not arithmetic constant expressions.  */
  यदि (!maybe_const)
    arith_const_व्यंजक = असत्य;
  अन्यथा यदि (!INTEGRAL_TYPE_P (वृक्ष_TYPE (inside_init))
	   && वृक्ष_CODE (वृक्ष_TYPE (inside_init)) != REAL_TYPE
	   && वृक्ष_CODE (वृक्ष_TYPE (inside_init)) != COMPLEX_TYPE)
    arith_const_व्यंजक = असत्य;
  अन्यथा यदि (वृक्ष_CODE (inside_init) != INTEGER_CST
	   && वृक्ष_CODE (inside_init) != REAL_CST
	   && वृक्ष_CODE (inside_init) != COMPLEX_CST
	   && वृक्ष_CODE (inside_init) != RAW_DATA_CST)
    arith_const_व्यंजक = असत्य;
  अन्यथा यदि (वृक्ष_OVERFLOW (inside_init))
    arith_const_व्यंजक = असत्य;

  /* Initialization of an array of chars from a string constant
     optionally enclosed in braces.  */

  यदि (code == ARRAY_TYPE && inside_init
      && वृक्ष_CODE (inside_init) == STRING_CST)
    {
      वृक्ष typ1
	= (TYPE_ATOMIC (वृक्ष_TYPE (type))
	   ? c_build_qualified_type (TYPE_MAIN_VARIANT (वृक्ष_TYPE (type)),
				     TYPE_QUAL_ATOMIC)
	   : TYPE_MAIN_VARIANT (वृक्ष_TYPE (type)));
      /* Note that an array could be both an array of character type
	 and an array of wchar_t if wchar_t is signed char or unsigned
	 char.  */
      तार्किक char_array = (typ1 == char_type_गाँठ
			 || typ1 == signed_char_type_गाँठ
			 || typ1 == unsigned_char_type_गाँठ);
      तार्किक wchar_array = comptypes (typ1, wchar_type_गाँठ);
      तार्किक char16_array = comptypes (typ1, char16_type_गाँठ);
      तार्किक char32_array = comptypes (typ1, char32_type_गाँठ);

      यदि (char_array || wchar_array || char16_array || char32_array)
	{
	  संरचना c_व्यंजक व्यंजक;
	  वृक्ष typ2 = TYPE_MAIN_VARIANT (वृक्ष_TYPE (वृक्ष_TYPE (inside_init)));
	  तार्किक incompat_string_cst = असत्य;
	  व्यंजक.मूल्य = inside_init;
	  व्यंजक.original_code = (strict_string ? STRING_CST : ERROR_MARK);
	  व्यंजक.original_type = रिक्त;
	  व्यंजक.m_decimal = 0;
	  maybe_warn_string_init (init_loc, type, व्यंजक);

	  यदि (flexible_array_member_type_p (type))
	    pedwarn_init (init_loc, OPT_Wpedantic,
			  "initialization of a flexible array member");

	  यदि (comptypes (TYPE_MAIN_VARIANT (वृक्ष_TYPE (inside_init)),
			 TYPE_MAIN_VARIANT (type)))
	    प्रत्यागम inside_init;

	  यदि (char_array)
	    {
	      यदि (typ2 != char_type_गाँठ && typ2 != char8_type_गाँठ)
		incompat_string_cst = सत्य;
	    }
	  अन्यथा यदि (!comptypes (typ1, typ2))
	    incompat_string_cst = सत्य;

          यदि (incompat_string_cst)
            {
	      error_init (init_loc, "cannot initialize array of %qT from "
			  "a string literal with type array of %qT",
			  typ1, typ2);
	      प्रत्यागम error_mark_गाँठ;
            }

	  यदि (require_constexpr
	      && TYPE_UNSIGNED (typ1) != TYPE_UNSIGNED (typ2))
	    {
	      /* Check if all characters of the string can be
		 represented in the type of the constexpr object being
		 initialized.  */
	      अचिन्हित HOST_WIDE_INT len = वृक्ष_STRING_LENGTH (inside_init);
	      ध्रुव अचिन्हित वर्ण *p =
		(ध्रुव अचिन्हित वर्ण *) वृक्ष_STRING_POINTER (inside_init);
	      gcc_assert (CHAR_TYPE_SIZE == 8 && अक्षर_बिट == 8);
	      प्रति (अचिन्हित i = 0; i < len; i++)
		यदि (p[i] > 127)
		  {
		    error_init (init_loc, "%<constexpr%> initializer not "
				"representable in type of object");
		    भङ्ग;
		  }
	    }

	  यदि (TYPE_DOMAIN (type) != NULL_वृक्ष
	      && TYPE_SIZE (type) != NULL_वृक्ष
	      && वृक्ष_CODE (TYPE_SIZE (type)) == INTEGER_CST)
	    {
	      अचिन्हित HOST_WIDE_INT len = वृक्ष_STRING_LENGTH (inside_init);

	      यदि (compare_वृक्ष_int (TYPE_SIZE_UNIT (type), len) < 0)
		{
		  अचिन्हित HOST_WIDE_INT avail
		    = वृक्ष_to_uhwi (TYPE_SIZE_UNIT (type));
		  अचिन्हित unit = TYPE_PRECISION (typ1) / BITS_PER_UNIT;
		  ध्रुव वर्ण *p = वृक्ष_STRING_POINTER (inside_init);

		  /* Construct truncated string.  */
		  inside_init = build_string (avail, p);

		  /* Subtract the size of a single (possibly wide) character
		     because it may be ok to ignore the terminating NUL char
		     that is counted in the length of the constant.  */
		  यदि (len - unit > avail)
		    pedwarn_init (init_loc, 0,
				  "initializer-string for array of %qT "
				  "is too long (%wu chars into %wu "
				  "available)", typ1, len, avail);
		  अन्यथा यदि (warn_cxx_compat)
		    warning_at (init_loc, OPT_Wc___compat,
				"initializer-string for array of %qT "
				"is too long for C++ (%wu chars into %wu "
				"available)", typ1, len, avail);
		  अन्यथा यदि (warn_unterminated_string_initialization
			   && get_attr_nonstring_decl (decl) == NULL_वृक्ष)
		    warning_at (init_loc,
				OPT_Wunterminated_string_initialization,
				"initializer-string for array of %qT "
				"truncates NUL terminator but destination "
				"lacks %qs attribute (%wu chars into %wu "
				"available)", typ1, "nonstring", len, avail);
		}
	    }

	  वृक्ष_TYPE (inside_init) = type;
	  प्रत्यागम inside_init;
	}
      अन्यथा यदि (INTEGRAL_TYPE_P (typ1))
	{
	  error_init (init_loc, "array of inappropriate type initialized "
		      "from string constant");
	  प्रत्यागम error_mark_गाँठ;
	}
    }

  /* Build a VECTOR_CST from a *constant* vector constructor.  If the
     vector constructor is not constant (e.g. {1,2,3,foo()}) then punt
     below and handle as a constructor.  */
  यदि (code == VECTOR_TYPE
      && VECTOR_TYPE_P (वृक्ष_TYPE (inside_init))
      && vector_types_convertible_p (वृक्ष_TYPE (inside_init), type, सत्य)
      && वृक्ष_CONSTANT (inside_init))
    {
      यदि (वृक्ष_CODE (inside_init) == VECTOR_CST
	  && comptypes (TYPE_MAIN_VARIANT (वृक्ष_TYPE (inside_init)),
			TYPE_MAIN_VARIANT (type)))
	प्रत्यागम inside_init;

      यदि (वृक्ष_CODE (inside_init) == CONSTRUCTOR)
	{
	  अचिन्हित HOST_WIDE_INT ix;
	  वृक्ष मूल्य;
	  तार्किक constant_p = सत्य;

	  /* Iterate through elements and check if all constructor
	     elements are *_CSTs.  */
	  FOR_EACH_CONSTRUCTOR_मूल्य (CONSTRUCTOR_ELTS (inside_init), ix, मूल्य)
	    यदि (!CONSTANT_CLASS_P (मूल्य))
	      {
		constant_p = असत्य;
		भङ्ग;
	      }

	  यदि (constant_p)
	    प्रत्यागम build_vector_from_ctor (type,
					   CONSTRUCTOR_ELTS (inside_init));
	}
    }

  यदि (warn_sequence_point)
    verify_sequence_points (inside_init);

  /* Any type can be initialized
     from an expression of the same type, optionally with braces.  */

  यदि (inside_init && वृक्ष_TYPE (inside_init) != NULL_वृक्ष
      && (comptypes (TYPE_MAIN_VARIANT (वृक्ष_TYPE (inside_init)),
		     TYPE_MAIN_VARIANT (type))
	  || (code == ARRAY_TYPE
	      && comptypes (वृक्ष_TYPE (inside_init), type))
	  || (gnu_vector_type_p (type)
	      && comptypes (वृक्ष_TYPE (inside_init), type))
	  || (code == POINTER_TYPE
	      && वृक्ष_CODE (वृक्ष_TYPE (inside_init)) == ARRAY_TYPE
	      && comptypes (वृक्ष_TYPE (वृक्ष_TYPE (inside_init)),
			    वृक्ष_TYPE (type)))))
    {
      यदि (code == POINTER_TYPE)
	{
	  यदि (वृक्ष_CODE (वृक्ष_TYPE (inside_init)) == ARRAY_TYPE)
	    {
	      यदि (वृक्ष_CODE (inside_init) == STRING_CST
		  || वृक्ष_CODE (inside_init) == COMPOUND_LITERAL_व्यंजक)
		inside_init = array_to_pointer_conversion
		  (init_loc, inside_init);
	      अन्यथा
		{
		  error_init (init_loc, "invalid use of non-lvalue array");
		  प्रत्यागम error_mark_गाँठ;
		}
	    }
	}

      यदि (code == VECTOR_TYPE || c_hardbool_type_attr (type))
	/* Although the types are compatible, we may require a
	   conversion.  */
	inside_init = convert (type, inside_init);

      यदि ((code == RECORD_TYPE || code == UNION_TYPE)
	  && !comptypes (TYPE_MAIN_VARIANT (type), TYPE_MAIN_VARIANT (वृक्ष_TYPE (inside_init))))
	{
	  error_init (init_loc, "invalid initializer");
	  प्रत्यागम error_mark_गाँठ;
	}

      यदि (require_constant
	  && वृक्ष_CODE (inside_init) == COMPOUND_LITERAL_व्यंजक)
	{
	  /* As an extension, allow initializing objects with static storage
	     duration with compound literals (which are then treated just as
	     the brace enclosed list they contain).  Also allow this for
	     vectors, as we can only assign them with compound literals.  */
	  यदि (flag_isoc99 && code != VECTOR_TYPE)
	    pedwarn_init (init_loc, OPT_Wpedantic, "initializer element "
			  "is not constant");
	  वृक्ष decl = COMPOUND_LITERAL_व्यंजक_DECL (inside_init);
	  inside_init = DECL_INITIAL (decl);
	}

      यदि (code == ARRAY_TYPE && वृक्ष_CODE (inside_init) != STRING_CST
	  && वृक्ष_CODE (inside_init) != CONSTRUCTOR)
	{
	  error_init (init_loc, "array initialized from non-constant array "
		      "expression");
	  प्रत्यागम error_mark_गाँठ;
	}

      /* Compound expressions can only occur here if -Wpedantic or
	 -pedantic-errors is specified.  In the later case, we always want
	 an error.  In the former case, we simply want a warning.  */
      यदि (require_constant && pedantic
	  && वृक्ष_CODE (inside_init) == COMPOUND_व्यंजक)
	{
	  inside_init
	    = valid_compound_व्यंजक_initializer (inside_init,
					       वृक्ष_TYPE (inside_init));
	  यदि (inside_init == error_mark_गाँठ)
	    error_init (init_loc, "initializer element is not constant");
	  अन्यथा
	    pedwarn_init (init_loc, OPT_Wpedantic,
			  "initializer element is not constant");
	  यदि (flag_pedantic_errors)
	    inside_init = error_mark_गाँठ;
	}
      अन्यथा यदि (require_constant
	       && !initializer_constant_valid_p (inside_init,
						 वृक्ष_TYPE (inside_init)))
	{
	  error_init (init_loc, "initializer element is not constant");
	  inside_init = error_mark_गाँठ;
	}
      अन्यथा यदि (require_constant && !maybe_const)
	pedwarn_init (init_loc, OPT_Wpedantic,
		      "initializer element is not a constant expression");
      अन्यथा यदि (require_constexpr)
	check_constexpr_init (init_loc, type, inside_init,
			      int_const_व्यंजक, arith_const_व्यंजक);

      /* Added to enable additional -Wsuggest-attribute=format warnings.  */
      यदि (वृक्ष_CODE (वृक्ष_TYPE (inside_init)) == POINTER_TYPE)
	inside_init = convert_for_assignment (init_loc, UNKNOWN_LOCATION,
					      type, inside_init, origtype,
					      (require_constant
					       ? ic_init_const
					       : ic_init), null_pointer_constant,
					      NULL_वृक्ष, NULL_वृक्ष, 0);
      यदि (वृक्ष_CODE (inside_init) == RAW_DATA_CST
	  && c_inhibit_evaluation_warnings == 0
	  && warn_conversion
	  && !TYPE_UNSIGNED (type)
	  && TYPE_PRECISION (type) == अक्षर_बिट)
	प्रति (अचिन्हित पूर्णाङ्क i = 0;
	     i < (अचिन्हित) RAW_DATA_LENGTH (inside_init); ++i)
	  यदि (RAW_DATA_SCHAR_ELT (inside_init, i) < 0)
	    warning_at (init_loc, OPT_Wconversion,
			"conversion from %qT to %qT changes value from "
			"%qd to %qd",
			integer_type_गाँठ, type,
			RAW_DATA_UCHAR_ELT (inside_init, i),
			RAW_DATA_SCHAR_ELT (inside_init, i));
      प्रत्यागम inside_init;
    }

  /* Handle scalar types, including conversions.  */

  यदि (code == INTEGER_TYPE || code == REAL_TYPE || code == FIXED_POINT_TYPE
      || code == POINTER_TYPE || code == ENUMERAL_TYPE || code == BOOLEAN_TYPE
      || code == COMPLEX_TYPE || code == VECTOR_TYPE || code == NULLPTR_TYPE
      || code == BITINT_TYPE)
    {
      वृक्ष unconverted_init = inside_init;
      यदि (वृक्ष_CODE (वृक्ष_TYPE (init)) == ARRAY_TYPE
	  && (वृक्ष_CODE (init) == STRING_CST
	      || वृक्ष_CODE (init) == COMPOUND_LITERAL_व्यंजक))
	inside_init = init = array_to_pointer_conversion (init_loc, init);
      यदि (semantic_type)
	inside_init = build1 (EXCESS_PRECISION_व्यंजक, semantic_type,
			      inside_init);
      inside_init
	= convert_for_assignment (init_loc, UNKNOWN_LOCATION, type,
				  inside_init, origtype,
				  require_constant ? ic_init_const : ic_init,
				  null_pointer_constant, NULL_वृक्ष, NULL_वृक्ष,
				  0);

      /* Check to see if we have already given an error message.  */
      यदि (inside_init == error_mark_गाँठ)
	;
      अन्यथा यदि (require_constant && !वृक्ष_CONSTANT (inside_init))
	{
	  error_init (init_loc, "initializer element is not constant");
	  inside_init = error_mark_गाँठ;
	}
      अन्यथा यदि (require_constant
	       && !initializer_constant_valid_p (inside_init,
						 वृक्ष_TYPE (inside_init)))
	{
	  error_init (init_loc, "initializer element is not computable at "
		      "load time");
	  inside_init = error_mark_गाँठ;
	}
      अन्यथा यदि (require_constant && !maybe_const)
	pedwarn_init (init_loc, OPT_Wpedantic,
		      "initializer element is not a constant expression");
      अन्यथा यदि (require_constexpr)
	check_constexpr_init (init_loc, type, unconverted_init,
			      int_const_व्यंजक, arith_const_व्यंजक);

      प्रत्यागम inside_init;
    }

  /* Come here only for records and arrays.  */

  यदि (COMPLETE_TYPE_P (type) && वृक्ष_CODE (TYPE_SIZE (type)) != INTEGER_CST)
    {
      error_init (init_loc,
		  "variable-sized object may not be initialized except "
		  "with an empty initializer");
      प्रत्यागम error_mark_गाँठ;
    }

  error_init (init_loc, "invalid initializer");
  प्रत्यागम error_mark_गाँठ;
}

/* Handle initializers that use braces.  */

/* Type of object we are accumulating a constructor for.
   This type is always a RECORD_TYPE, UNION_TYPE or ARRAY_TYPE.  */
स्थिर वृक्ष constructor_type;

/* For a RECORD_TYPE or UNION_TYPE, this is the chain of fields
   left to fill.  */
स्थिर वृक्ष constructor_fields;

/* For an ARRAY_TYPE, this is the specified index
   at which to store the next element we get.  */
स्थिर वृक्ष constructor_index;

/* For an ARRAY_TYPE, this is the maximum index.  */
स्थिर वृक्ष constructor_max_index;

/* For a RECORD_TYPE, this is the first field not yet written out.  */
स्थिर वृक्ष constructor_unfilled_fields;

/* For an ARRAY_TYPE, this is the index of the first element
   not yet written out.  */
स्थिर वृक्ष constructor_unfilled_index;

/* In a RECORD_TYPE, the byte index of the next consecutive field.
   This is so we can generate gaps between fields, when appropriate.  */
स्थिर वृक्ष constructor_bit_index;

/* If we are saving up the elements rather than allocating them,
   this is the list of elements so far (in reverse order,
   most recent first).  */
स्थिर vec<constructor_elt, va_gc> *constructor_elements;

/* 1 if constructor should be incrementally stored into a constructor chain,
   0 if all the elements should be kept in AVL tree.  */
स्थिर पूर्णाङ्क constructor_incremental;

/* 1 if so far this constructor's elements are all compile-time constants.  */
स्थिर पूर्णाङ्क constructor_constant;

/* 1 if so far this constructor's elements are all valid address constants.  */
स्थिर पूर्णाङ्क constructor_simple;

/* 1 if this constructor has an element that cannot be part of a
   constant expression.  */
स्थिर पूर्णाङ्क constructor_nonconst;

/* 1 if this constructor is erroneous so far.  */
स्थिर पूर्णाङ्क constructor_erroneous;

/* 1 if this constructor is the universal zero initializer { 0 }.  */
स्थिर पूर्णाङ्क constructor_zeroinit;

/* 1 if this constructor should have padding bits zeroed (C23 {}.  */
स्थिर तार्किक constructor_zero_padding_bits;

/* 1 if this constructor is a braced scalar initializer (further nested levels
   of braces are an error).  */
स्थिर तार्किक constructor_braced_scalar;

/* Structure for managing pending initializer elements, organized as an
   AVL tree.  */

संरचना init_गाँठ
{
  संरचना init_गाँठ *बायाँ, *दायाँ;
  संरचना init_गाँठ *parent;
  पूर्णाङ्क balance;
  वृक्ष purpose;
  वृक्ष मूल्य;
  वृक्ष origtype;
};

/* Tree of pending elements at this constructor level.
   These are elements encountered out of order
   which belong at places we haven't reached yet in actually
   writing the output.
   Will never hold tree nodes across GC runs.  */
स्थिर संरचना init_गाँठ *constructor_pending_elts;

/* The SPELLING_DEPTH of this constructor.  */
स्थिर पूर्णाङ्क constructor_depth;

/* DECL node for which an initializer is being read.
   0 means we are reading a constructor expression
   such as (struct foo) {...}.  */
स्थिर वृक्ष constructor_decl;

/* Nonzero if there were any member designators in this initializer.  */
स्थिर पूर्णाङ्क constructor_designated;

/* Nesting depth of designator list.  */
स्थिर पूर्णाङ्क designator_depth;

/* Nonzero if there were diagnosed errors in this designator list.  */
स्थिर पूर्णाङ्क designator_erroneous;


/* This stack has a level for each implicit or explicit level of
   structuring in the initializer, including the outermost one.  It
   saves the values of most of the variables above.  */

संरचना constructor_range_ढेर;

संरचना constructor_ढेर
{
  संरचना constructor_ढेर *next;
  वृक्ष type;
  वृक्ष fields;
  वृक्ष index;
  वृक्ष max_index;
  वृक्ष unfilled_index;
  वृक्ष unfilled_fields;
  वृक्ष bit_index;
  vec<constructor_elt, va_gc> *elements;
  संरचना init_गाँठ *pending_elts;
  पूर्णाङ्क offset;
  पूर्णाङ्क depth;
  /* If value nonzero, this value should replace the entire
     constructor at this level.  */
  संरचना c_व्यंजक replacement_मूल्य;
  संरचना constructor_range_ढेर *range_ढेर;
  वर्ण constant;
  वर्ण simple;
  वर्ण nonconst;
  वर्ण implicit;
  वर्ण erroneous;
  वर्ण outer;
  वर्ण incremental;
  वर्ण designated;
  तार्किक zero_padding_bits;
  तार्किक braced_scalar;
  पूर्णाङ्क designator_depth;
};

स्थिर संरचना constructor_ढेर *constructor_ढेर;

/* This stack represents designators from some range designator up to
   the last designator in the list.  */

संरचना constructor_range_ढेर
{
  संरचना constructor_range_ढेर *next, *prev;
  संरचना constructor_ढेर *ढेर;
  वृक्ष range_start;
  वृक्ष index;
  वृक्ष range_end;
  वृक्ष fields;
};

स्थिर संरचना constructor_range_ढेर *constructor_range_ढेर;

/* This stack records separate initializers that are nested.
   Nested initializers can't happen in ANSI C, but GNU C allows them
   in cases like { ... (struct foo) { ... } ... }.  */

संरचना initializer_ढेर
{
  संरचना initializer_ढेर *next;
  वृक्ष decl;
  संरचना constructor_ढेर *constructor_ढेर;
  संरचना constructor_range_ढेर *constructor_range_ढेर;
  vec<constructor_elt, va_gc> *elements;
  संरचना spelling *spelling;
  संरचना spelling *spelling_base;
  पूर्णाङ्क spelling_size;
  वर्ण require_constant_मूल्य;
  वर्ण require_constant_elements;
  वर्ण require_constexpr_मूल्य;
  वर्ण designated;
  rich_location *missing_brace_richloc;
};

स्थिर संरचना initializer_ढेर *initializer_ढेर;

/* Prepare to parse and output the initializer for variable DECL.  */

शून्य
start_init (वृक्ष decl, वृक्ष asmspec_वृक्ष ATTRIBUTE_UNUSED,
	    तार्किक init_require_constant, तार्किक init_require_constexpr,
	    rich_location *richloc)
{
  ध्रुव वर्ण *locus;
  संरचना initializer_ढेर *p = XNEW (संरचना initializer_ढेर);

  p->decl = constructor_decl;
  p->require_constant_मूल्य = require_constant_मूल्य;
  p->require_constant_elements = require_constant_elements;
  p->require_constexpr_मूल्य = require_constexpr_मूल्य;
  p->constructor_ढेर = constructor_ढेर;
  p->constructor_range_ढेर = constructor_range_ढेर;
  p->elements = constructor_elements;
  p->spelling = spelling;
  p->spelling_base = spelling_base;
  p->spelling_size = spelling_size;
  p->next = initializer_ढेर;
  p->missing_brace_richloc = richloc;
  p->designated = constructor_designated;
  initializer_ढेर = p;

  constructor_decl = decl;
  constructor_designated = 0;

  require_constant_मूल्य = init_require_constant;
  require_constexpr_मूल्य = init_require_constexpr;
  यदि (decl != NULL_वृक्ष && decl != error_mark_गाँठ)
    {
      require_constant_elements
	= ((init_require_constant || (pedantic && !flag_isoc99))
	   /* For a scalar, you can always use any value to initialize,
	      even within braces.  */
	   && AGGREGATE_TYPE_P (वृक्ष_TYPE (decl)));
      locus = identifier_to_locale (IDENTIFIER_POINTER (DECL_NAME (decl)));
    }
  अन्यथा
    {
      require_constant_elements = असत्य;
      locus = _("(anonymous)");
    }

  constructor_ढेर = 0;
  constructor_range_ढेर = 0;

  found_missing_braces = 0;

  spelling_base = 0;
  spelling_size = 0;
  RESTORE_SPELLING_DEPTH (0);

  यदि (locus)
    धकेलो_string (locus);
}

शून्य
finish_init (शून्य)
{
  संरचना initializer_ढेर *p = initializer_ढेर;

  /* Free the whole constructor stack of this initializer.  */
  यावत् (constructor_ढेर)
    {
      संरचना constructor_ढेर *q = constructor_ढेर;
      constructor_ढेर = q->next;
      XDELETE (q);
    }

  gcc_assert (!constructor_range_ढेर);

  /* Pop back to the data of the outer initializer (if any).  */
  XDELETE (spelling_base);

  constructor_decl = p->decl;
  require_constant_मूल्य = p->require_constant_मूल्य;
  require_constant_elements = p->require_constant_elements;
  require_constexpr_मूल्य = p->require_constexpr_मूल्य;
  constructor_ढेर = p->constructor_ढेर;
  constructor_designated = p->designated;
  constructor_range_ढेर = p->constructor_range_ढेर;
  constructor_elements = p->elements;
  spelling = p->spelling;
  spelling_base = p->spelling_base;
  spelling_size = p->spelling_size;
  initializer_ढेर = p->next;
  XDELETE (p);
}

/* Call here when we see the initializer is surrounded by braces.
   This is instead of a call to push_init_level;
   it is matched by a call to pop_init_level.

   TYPE is the type to initialize, for a constructor expression.
   For an initializer for a decl, TYPE is zero.  */

शून्य
really_start_incremental_init (वृक्ष type)
{
  संरचना constructor_ढेर *p = XNEW (संरचना constructor_ढेर);

  यदि (type == NULL_वृक्ष)
    type = वृक्ष_TYPE (constructor_decl);

  यदि (VECTOR_TYPE_P (type)
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
  p->replacement_मूल्य.मूल्य = 0;
  p->replacement_मूल्य.original_code = ERROR_MARK;
  p->replacement_मूल्य.original_type = रिक्त;
  p->implicit = 0;
  p->range_ढेर = 0;
  p->outer = 0;
  p->incremental = constructor_incremental;
  p->designated = constructor_designated;
  p->zero_padding_bits = constructor_zero_padding_bits;
  p->braced_scalar = constructor_braced_scalar;
  p->designator_depth = designator_depth;
  p->next = 0;
  constructor_ढेर = p;

  constructor_constant = 1;
  constructor_simple = 1;
  constructor_nonconst = 0;
  constructor_depth = SPELLING_DEPTH ();
  constructor_elements = रिक्त;
  constructor_pending_elts = 0;
  constructor_type = type;
  constructor_incremental = 1;
  constructor_designated = 0;
  constructor_zero_padding_bits = असत्य;
  constructor_zeroinit = 1;
  constructor_braced_scalar = असत्य;
  designator_depth = 0;
  designator_erroneous = 0;

  यदि (RECORD_OR_UNION_TYPE_P (constructor_type))
    {
      constructor_fields = TYPE_FIELDS (constructor_type);
      /* Skip any nameless bit fields at the beginning.  */
      यावत् (constructor_fields != NULL_वृक्ष
	     && DECL_UNNAMED_BIT_FIELD (constructor_fields))
	constructor_fields = DECL_CHAIN (constructor_fields);

      constructor_unfilled_fields = constructor_fields;
      constructor_bit_index = bitsize_zero_गाँठ;
    }
  अन्यथा यदि (वृक्ष_CODE (constructor_type) == ARRAY_TYPE)
    {
      यदि (TYPE_DOMAIN (constructor_type))
	{
	  constructor_max_index
	    = TYPE_MAX_मूल्य (TYPE_DOMAIN (constructor_type));

	  /* Detect non-empty initializations of zero-length arrays.  */
	  यदि (constructor_max_index == NULL_वृक्ष
	      && TYPE_SIZE (constructor_type))
	    constructor_max_index = integer_minus_one_गाँठ;

	  /* constructor_max_index needs to be an INTEGER_CST.  Attempts
	     to initialize VLAs with a nonempty initializer will cause a
	     proper error; avoid tree checking errors as well by setting a
	     safe value.  */
	  यदि (constructor_max_index
	      && वृक्ष_CODE (constructor_max_index) != INTEGER_CST)
	    constructor_max_index = integer_minus_one_गाँठ;

	  constructor_index
	    = convert (bitsizetype,
		       TYPE_MIN_मूल्य (TYPE_DOMAIN (constructor_type)));
	}
      अन्यथा
	{
	  constructor_index = bitsize_zero_गाँठ;
	  constructor_max_index = NULL_वृक्ष;
	}

      constructor_unfilled_index = constructor_index;
    }
  अन्यथा यदि (gnu_vector_type_p (constructor_type))
    {
      /* Vectors are like simple fixed-size arrays.  */
      constructor_max_index =
	bitsize_int (TYPE_VECTOR_SUBPARTS (constructor_type) - 1);
      constructor_index = bitsize_zero_गाँठ;
      constructor_unfilled_index = constructor_index;
    }
  अन्यथा
    {
      /* Handle the case of int x = {5}; */
      constructor_fields = constructor_type;
      constructor_unfilled_fields = constructor_type;
      constructor_braced_scalar = सत्य;
    }
}

बाह्य location_t last_init_list_comma;

/* Called when we see an open brace for a nested initializer.  Finish
   off any pending levels with implicit braces.  */
शून्य
finish_implicit_inits (location_t loc, संरचना obstack *braced_init_obstack)
{
  यावत् (constructor_ढेर->implicit)
    {
      यदि (RECORD_OR_UNION_TYPE_P (constructor_type)
	  && constructor_fields == NULL_वृक्ष)
	process_init_element (निवेश_location,
			      निकालो_init_level (loc, 1, braced_init_obstack,
					      last_init_list_comma),
			      सत्य, braced_init_obstack);
      अन्यथा यदि (वृक्ष_CODE (constructor_type) == ARRAY_TYPE
	       && constructor_max_index
	       && वृक्ष_int_cst_lt (constructor_max_index,
				   constructor_index))
	process_init_element (निवेश_location,
			      निकालो_init_level (loc, 1, braced_init_obstack,
					      last_init_list_comma),
			      सत्य, braced_init_obstack);
      अन्यथा
	भङ्ग;
    }
}

/* Push down into a subobject, for initialization.
   If this is for an explicit set of braces, IMPLICIT is 0.
   If it is because the next element belongs at a lower level,
   IMPLICIT is 1 (or 2 if the push is because of designator list).  */

शून्य
धकेलो_init_level (location_t loc, पूर्णाङ्क implicit,
		 संरचना obstack *braced_init_obstack)
{
  संरचना constructor_ढेर *p;
  वृक्ष मूल्य = NULL_वृक्ष;

  /* Unless this is an explicit brace, we need to preserve previous
     content if any.  */
  यदि (implicit)
    {
      यदि (RECORD_OR_UNION_TYPE_P (constructor_type) && constructor_fields)
	मूल्य = find_init_member (constructor_fields, braced_init_obstack);
      अन्यथा यदि (वृक्ष_CODE (constructor_type) == ARRAY_TYPE)
	मूल्य = find_init_member (constructor_index, braced_init_obstack);
    }

  p = XNEW (संरचना constructor_ढेर);
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
  p->replacement_मूल्य.मूल्य = NULL_वृक्ष;
  p->replacement_मूल्य.original_code = ERROR_MARK;
  p->replacement_मूल्य.original_type = रिक्त;
  p->implicit = implicit;
  p->outer = 0;
  p->incremental = constructor_incremental;
  p->designated = constructor_designated;
  p->zero_padding_bits = constructor_zero_padding_bits;
  p->braced_scalar = constructor_braced_scalar;
  p->designator_depth = designator_depth;
  p->next = constructor_ढेर;
  p->range_ढेर = 0;
  constructor_ढेर = p;

  constructor_constant = 1;
  constructor_simple = 1;
  constructor_nonconst = 0;
  constructor_depth = SPELLING_DEPTH ();
  constructor_elements = रिक्त;
  constructor_incremental = 1;
  /* If the upper initializer is designated, then mark this as
     designated too to prevent bogus warnings.  */
  constructor_designated = p->designated;
  /* If the upper initializer has padding bits zeroed, that includes
     all nested initializers as well.  */
  constructor_zero_padding_bits = p->zero_padding_bits;
  constructor_braced_scalar = असत्य;
  constructor_pending_elts = 0;
  यदि (!implicit)
    {
      p->range_ढेर = constructor_range_ढेर;
      constructor_range_ढेर = 0;
      designator_depth = 0;
      designator_erroneous = 0;
    }

  /* Don't die if an entire brace-pair level is superfluous
     in the containing level.  */
  यदि (constructor_type == NULL_वृक्ष)
    ;
  अन्यथा यदि (RECORD_OR_UNION_TYPE_P (constructor_type))
    {
      /* Don't die if there are extra init elts at the end.  */
      यदि (constructor_fields == NULL_वृक्ष)
	constructor_type = NULL_वृक्ष;
      अन्यथा
	{
	  constructor_type = वृक्ष_TYPE (constructor_fields);
	  धकेलो_member_name (constructor_fields);
	  constructor_depth++;
	}
    }
  अन्यथा यदि (वृक्ष_CODE (constructor_type) == ARRAY_TYPE)
    {
      constructor_type = वृक्ष_TYPE (constructor_type);
      धकेलो_array_bounds (वृक्ष_to_uhwi (constructor_index));
      constructor_depth++;
    }

  यदि (constructor_type == NULL_वृक्ष)
    {
      error_init (loc, "extra brace group at end of initializer");
      constructor_fields = NULL_वृक्ष;
      constructor_unfilled_fields = NULL_वृक्ष;
      प्रत्यागम;
    }

  यदि (मूल्य && वृक्ष_CODE (मूल्य) == CONSTRUCTOR)
    {
      constructor_constant = वृक्ष_CONSTANT (मूल्य);
      constructor_simple = वृक्ष_STATIC (मूल्य);
      constructor_nonconst = CONSTRUCTOR_NON_CONST (मूल्य);
      constructor_elements = CONSTRUCTOR_ELTS (मूल्य);
      constructor_zero_padding_bits |= CONSTRUCTOR_ZERO_PADDING_BITS (मूल्य);
      यदि (!vec_safe_is_empty (constructor_elements)
	  && (वृक्ष_CODE (constructor_type) == RECORD_TYPE
	      || वृक्ष_CODE (constructor_type) == ARRAY_TYPE))
	set_nonincremental_init (braced_init_obstack);
    }

  यदि (implicit == 1)
    {
      found_missing_braces = 1;
      यदि (initializer_ढेर->missing_brace_richloc)
	initializer_ढेर->missing_brace_richloc->add_fixit_जोड़ो_before
	  (loc, "{");
    }

  यदि (RECORD_OR_UNION_TYPE_P (constructor_type))
    {
      constructor_fields = TYPE_FIELDS (constructor_type);
      /* Skip any nameless bit fields at the beginning.  */
      यावत् (constructor_fields != NULL_वृक्ष
	     && DECL_UNNAMED_BIT_FIELD (constructor_fields))
	constructor_fields = DECL_CHAIN (constructor_fields);

      constructor_unfilled_fields = constructor_fields;
      constructor_bit_index = bitsize_zero_गाँठ;
    }
  अन्यथा यदि (gnu_vector_type_p (constructor_type))
    {
      /* Vectors are like simple fixed-size arrays.  */
      constructor_max_index =
	bitsize_int (TYPE_VECTOR_SUBPARTS (constructor_type) - 1);
      constructor_index = bitsize_int (0);
      constructor_unfilled_index = constructor_index;
    }
  अन्यथा यदि (वृक्ष_CODE (constructor_type) == ARRAY_TYPE)
    {
      यदि (TYPE_DOMAIN (constructor_type))
	{
	  constructor_max_index
	    = TYPE_MAX_मूल्य (TYPE_DOMAIN (constructor_type));

	  /* Detect non-empty initializations of zero-length arrays.  */
	  यदि (constructor_max_index == NULL_वृक्ष
	      && TYPE_SIZE (constructor_type))
	    constructor_max_index = integer_minus_one_गाँठ;

	  /* constructor_max_index needs to be an INTEGER_CST.  Attempts
	     to initialize VLAs will cause a proper error; avoid tree
	     checking errors as well by setting a safe value.  */
	  यदि (constructor_max_index
	      && वृक्ष_CODE (constructor_max_index) != INTEGER_CST)
	    constructor_max_index = integer_minus_one_गाँठ;

	  constructor_index
	    = convert (bitsizetype,
		       TYPE_MIN_मूल्य (TYPE_DOMAIN (constructor_type)));
	}
      अन्यथा
	constructor_index = bitsize_zero_गाँठ;

      constructor_unfilled_index = constructor_index;
      यदि (मूल्य && वृक्ष_CODE (मूल्य) == STRING_CST)
	{
	  /* We need to split the char/wchar array into individual
	     characters, so that we don't have to special case it
	     everywhere.  */
	  set_nonincremental_init_from_string (मूल्य, braced_init_obstack);
	}
    }
  अन्यथा
    {
      यदि (constructor_type != error_mark_गाँठ)
	{
	  यदि (p->braced_scalar)
	    permerror_init (निवेश_location, 0,
			    "braces around scalar initializer");
	  अन्यथा
	    warning_init (निवेश_location, 0,
			  "braces around scalar initializer");
	  constructor_braced_scalar = सत्य;
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

संरचना c_व्यंजक
निकालो_init_level (location_t loc, पूर्णाङ्क implicit,
		संरचना obstack *braced_init_obstack,
		location_t जोड़ो_before)
{
  संरचना constructor_ढेर *p;
  संरचना c_व्यंजक ret;
  ret.मूल्य = NULL_वृक्ष;
  ret.original_code = ERROR_MARK;
  ret.original_type = रिक्त;
  ret.m_decimal = 0;

  यदि (implicit == 0)
    {
      /* When we come to an explicit close brace,
	 pop any inner levels that didn't have explicit braces.  */
      यावत् (constructor_ढेर->implicit)
	process_init_element (निवेश_location,
			      निकालो_init_level (loc, 1, braced_init_obstack,
					      जोड़ो_before),
			      सत्य, braced_init_obstack);
      gcc_assert (!constructor_range_ढेर);
    }
  अन्यथा
    यदि (initializer_ढेर->missing_brace_richloc)
      initializer_ढेर->missing_brace_richloc->add_fixit_जोड़ो_before
	(जोड़ो_before, "}");

  /* Now output all pending elements.  */
  constructor_incremental = 1;
  output_pending_init_elements (1, braced_init_obstack);

  p = constructor_ढेर;

  /* Error for initializing a flexible array member.  */
  यदि (constructor_type && constructor_fields
      && flexible_array_member_type_p (constructor_type))
    {
      /* Silently discard empty initializations.  The parser will
	 already have pedwarned for empty brackets for C17 and earlier.  */
      यदि (integer_zerop (constructor_unfilled_index))
	constructor_type = NULL_वृक्ष;
      यदि (constructor_type || flag_isoc23)
	{
	  gcc_assert (!constructor_type || !TYPE_SIZE (constructor_type));

	  यदि (constructor_depth <= 2)
	    pedwarn_init (loc, OPT_Wpedantic,
			  "initialization of a flexible array member");
	  अन्यथा यदि (constructor_type)
	    error_init (loc, "initialization of flexible array member "
			     "in a nested context");
	  अन्यथा
	    pedwarn_init (loc, OPT_Wpedantic,
			  "initialization of flexible array member "
			  "in a nested context");

	  /* We have already issued an error message for the existence
	     of a flexible array member not at the end of the structure.
	     Discard the initializer so that we do not die later.  */
	  यदि (constructor_type
	      && DECL_CHAIN (constructor_fields) != NULL_वृक्ष
	      && (!p->type || वृक्ष_CODE (p->type) != UNION_TYPE))
	    constructor_type = NULL_वृक्ष;
	}
    }

  विकल्प (vec_safe_length (constructor_elements))
    {
    पक्ष 0:
      /* Initialization with { } counts as zeroinit.  */
      constructor_zeroinit = 1;
      भङ्ग;
    पक्ष 1:
      /* This might be zeroinit as well.  */
      यदि (integer_zerop ((*constructor_elements)[0].मूल्य))
	constructor_zeroinit = 1;
      भङ्ग;
    स्वभाव:
      /* If the constructor has more than one element, it can't be { 0 }.  */
      constructor_zeroinit = 0;
      भङ्ग;
    }

  /* Warn when some structs are initialized with direct aggregation.  */
  यदि (!implicit && found_missing_braces && warn_missing_braces
      && !constructor_zeroinit)
    {
      gcc_assert (initializer_ढेर->missing_brace_richloc);
      warning_at (initializer_ढेर->missing_brace_richloc,
		  OPT_Wmissing_braces,
		  "missing braces around initializer");
    }

  /* Warn when some struct elements are implicitly initialized to zero.  */
  यदि (warn_missing_field_initializers
      && constructor_type
      && वृक्ष_CODE (constructor_type) == RECORD_TYPE
      && constructor_unfilled_fields)
    {
	/* Do not warn for flexible array members or zero-length arrays.  */
	यावत् (constructor_unfilled_fields
	       && (!DECL_SIZE (constructor_unfilled_fields)
		   || integer_zerop (DECL_SIZE (constructor_unfilled_fields))))
	  constructor_unfilled_fields = DECL_CHAIN (constructor_unfilled_fields);

	यदि (constructor_unfilled_fields
	    /* Do not warn if this level of the initializer uses member
	       designators; it is likely to be deliberate.  */
	    && !constructor_designated
	    /* Do not warn about initializing with { 0 } or with { }.  */
	    && !constructor_zeroinit)
	  {
	    यदि (warning_at (निवेश_location, OPT_Wmissing_field_initializers,
			    "missing initializer for field %qD of %qT",
			    constructor_unfilled_fields,
			    constructor_type))
	      inform (DECL_SOURCE_LOCATION (constructor_unfilled_fields),
		      "%qD declared here", constructor_unfilled_fields);
	  }
    }

  /* Pad out the end of the structure.  */
  यदि (p->replacement_मूल्य.मूल्य)
    /* If this closes a superfluous brace pair,
       just pass out the element between them.  */
    ret = p->replacement_मूल्य;
  अन्यथा यदि (constructor_type == NULL_वृक्ष)
    ;
  अन्यथा यदि (!RECORD_OR_UNION_TYPE_P (constructor_type)
	   && वृक्ष_CODE (constructor_type) != ARRAY_TYPE
	   && !gnu_vector_type_p (constructor_type))
    {
      /* A nonincremental scalar initializer--just return
	 the element, after verifying there is just one.
         Empty scalar initializers are supported in C23.  */
      यदि (vec_safe_is_empty (constructor_elements))
	{
	  यदि (constructor_erroneous || constructor_type == error_mark_गाँठ)
	    ret.मूल्य = error_mark_गाँठ;
	  अन्यथा यदि (वृक्ष_CODE (constructor_type) == FUNCTION_TYPE)
	    {
	      error_init (loc, "invalid initializer");
	      ret.मूल्य = error_mark_गाँठ;
	    }
	  अन्यथा यदि (वृक्ष_CODE (constructor_type) == POINTER_TYPE)
	    /* Ensure this is a null pointer constant in the case of a
	       'constexpr' object initialized with {}.  */
	    ret.मूल्य = build_zero_cst (ptr_type_गाँठ);
	  अन्यथा
	    ret.मूल्य = build_zero_cst (constructor_type);
	}
      अन्यथा यदि (vec_safe_length (constructor_elements) != 1)
	{
	  error_init (loc, "extra elements in scalar initializer");
	  ret.मूल्य = (*constructor_elements)[0].मूल्य;
	}
      अन्यथा
	ret.मूल्य = (*constructor_elements)[0].मूल्य;
    }
  अन्यथा
    {
      यदि (constructor_erroneous)
	ret.मूल्य = error_mark_गाँठ;
      अन्यथा
	{
	  ret.मूल्य = build_constructor (constructor_type,
					 constructor_elements);
	  यदि (constructor_constant)
	    वृक्ष_CONSTANT (ret.मूल्य) = 1;
	  यदि (constructor_constant && constructor_simple)
	    वृक्ष_STATIC (ret.मूल्य) = 1;
	  यदि (constructor_nonconst)
	    CONSTRUCTOR_NON_CONST (ret.मूल्य) = 1;
	  यदि (constructor_zero_padding_bits)
	    CONSTRUCTOR_ZERO_PADDING_BITS (ret.मूल्य) = 1;
	}
    }

  यदि (ret.मूल्य && वृक्ष_CODE (ret.मूल्य) != CONSTRUCTOR)
    {
      यदि (constructor_nonconst)
	ret.original_code = C_MAYBE_CONST_व्यंजक;
      अन्यथा यदि (ret.original_code == C_MAYBE_CONST_व्यंजक)
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
  यदि (!p->implicit)
    constructor_range_ढेर = p->range_ढेर;
  RESTORE_SPELLING_DEPTH (constructor_depth);

  constructor_ढेर = p->next;
  XDELETE (p);

  यदि (ret.मूल्य == NULL_वृक्ष && constructor_ढेर == 0)
    ret.मूल्य = error_mark_गाँठ;
  प्रत्यागम ret;
}

/* Common handling for both array range and field name designators.
   ARRAY argument is nonzero for array ranges.  Returns false for success.  */

स्थिर तार्किक
set_designator (location_t loc, तार्किक array,
		संरचना obstack *braced_init_obstack)
{
  वृक्ष subtype;
  गणना वृक्ष_code subcode;

  /* Don't die if an entire brace-pair level is superfluous
     in the containing level, or for an erroneous type.  */
  यदि (constructor_type == NULL_वृक्ष || constructor_type == error_mark_गाँठ)
    प्रत्यागम सत्य;

  /* If there were errors in this designator list already, bail out
     silently.  */
  यदि (designator_erroneous)
    प्रत्यागम सत्य;

  /* Likewise for an initializer for a variable-size type.  Those are
     diagnosed in the parser, except for empty initializer braces.  */
  यदि (COMPLETE_TYPE_P (constructor_type)
      && वृक्ष_CODE (TYPE_SIZE (constructor_type)) != INTEGER_CST)
    प्रत्यागम सत्य;

  यदि (!designator_depth)
    {
      gcc_assert (!constructor_range_ढेर);

      /* Designator list starts at the level of closest explicit
	 braces.  */
      यावत् (constructor_ढेर->implicit)
	process_init_element (निवेश_location,
			      निकालो_init_level (loc, 1, braced_init_obstack,
					      last_init_list_comma),
			      सत्य, braced_init_obstack);
      constructor_designated = 1;
      प्रत्यागम असत्य;
    }

  विकल्प (वृक्ष_CODE (constructor_type))
    {
    पक्ष  RECORD_TYPE:
    पक्ष  UNION_TYPE:
      subtype = वृक्ष_TYPE (constructor_fields);
      यदि (subtype != error_mark_गाँठ)
	subtype = TYPE_MAIN_VARIANT (subtype);
      भङ्ग;
    पक्ष ARRAY_TYPE:
      subtype = TYPE_MAIN_VARIANT (वृक्ष_TYPE (constructor_type));
      भङ्ग;
    स्वभाव:
      gcc_unreachable ();
    }

  subcode = वृक्ष_CODE (subtype);
  यदि (array && subcode != ARRAY_TYPE)
    {
      error_init (loc, "array index in non-array initializer");
      प्रत्यागम सत्य;
    }
  अन्यथा यदि (!array && subcode != RECORD_TYPE && subcode != UNION_TYPE)
    {
      error_init (loc, "field name not in record or union initializer");
      प्रत्यागम सत्य;
    }

  constructor_designated = 1;
  finish_implicit_inits (loc, braced_init_obstack);
  धकेलो_init_level (loc, 2, braced_init_obstack);
  प्रत्यागम असत्य;
}

/* If there are range designators in designator list, push a new designator
   to constructor_range_stack.  RANGE_END is end of such stack range or
   NULL_TREE if there is no range designator at this level.  */

स्थिर शून्य
धकेलो_range_ढेर (वृक्ष range_end, संरचना obstack * braced_init_obstack)
{
  संरचना constructor_range_ढेर *p;

  p = (संरचना constructor_range_ढेर *)
    obstack_alloc (braced_init_obstack,
		   परिमाण (संरचना constructor_range_ढेर));
  p->prev = constructor_range_ढेर;
  p->next = 0;
  p->fields = constructor_fields;
  p->range_start = constructor_index;
  p->index = constructor_index;
  p->ढेर = constructor_ढेर;
  p->range_end = range_end;
  यदि (constructor_range_ढेर)
    constructor_range_ढेर->next = p;
  constructor_range_ढेर = p;
}

/* Within an array initializer, specify the next index to be initialized.
   FIRST is that index.  If LAST is nonzero, then initialize a range
   of indices, running from FIRST through LAST.  */

शून्य
set_init_index (location_t loc, वृक्ष first, वृक्ष last,
		संरचना obstack *braced_init_obstack)
{
  यदि (set_designator (loc, सत्य, braced_init_obstack))
    प्रत्यागम;

  designator_erroneous = 1;

  यदि (!INTEGRAL_TYPE_P (वृक्ष_TYPE (first))
      || (last && !INTEGRAL_TYPE_P (वृक्ष_TYPE (last))))
    {
      error_init (loc, "array index in initializer not of integer type");
      प्रत्यागम;
    }

  यदि (वृक्ष_CODE (first) != INTEGER_CST)
    {
      first = c_fully_fold (first, असत्य, रिक्त);
      यदि (वृक्ष_CODE (first) == INTEGER_CST)
	pedwarn_init (loc, OPT_Wpedantic,
		      "array index in initializer is not "
		      "an integer constant expression");
    }

  यदि (last && वृक्ष_CODE (last) != INTEGER_CST)
    {
      last = c_fully_fold (last, असत्य, रिक्त);
      यदि (वृक्ष_CODE (last) == INTEGER_CST)
	pedwarn_init (loc, OPT_Wpedantic,
		      "array index in initializer is not "
		      "an integer constant expression");
    }

  यदि (वृक्ष_CODE (first) != INTEGER_CST)
    error_init (loc, "nonconstant array index in initializer");
  अन्यथा यदि (last != NULL_वृक्ष && वृक्ष_CODE (last) != INTEGER_CST)
    error_init (loc, "nonconstant array index in initializer");
  अन्यथा यदि (वृक्ष_CODE (constructor_type) != ARRAY_TYPE)
    error_init (loc, "array index in non-array initializer");
  अन्यथा यदि (वृक्ष_int_cst_sgn (first) == -1)
    error_init (loc, "array index in initializer exceeds array bounds");
  अन्यथा यदि (constructor_max_index
	   && वृक्ष_int_cst_lt (constructor_max_index, first))
    error_init (loc, "array index in initializer exceeds array bounds");
  अन्यथा
    {
      constant_expression_warning (first);
      यदि (last)
	constant_expression_warning (last);
      constructor_index = convert (bitsizetype, first);
      यदि (वृक्ष_int_cst_lt (constructor_index, first))
	{
	  constructor_index = copy_गाँठ (constructor_index);
	  वृक्ष_OVERFLOW (constructor_index) = 1;
	}

      यदि (last)
	{
	  यदि (वृक्ष_int_cst_equal (first, last))
	    last = NULL_वृक्ष;
	  अन्यथा यदि (वृक्ष_int_cst_lt (last, first))
	    {
	      error_init (loc, "empty index range in initializer");
	      last = NULL_वृक्ष;
	    }
	  अन्यथा
	    {
	      last = convert (bitsizetype, last);
	      यदि (constructor_max_index != NULL_वृक्ष
		  && वृक्ष_int_cst_lt (constructor_max_index, last))
		{
		  error_init (loc, "array index range in initializer exceeds "
			      "array bounds");
		  last = NULL_वृक्ष;
		}
	    }
	}

      designator_depth++;
      designator_erroneous = 0;
      यदि (constructor_range_ढेर || last)
	धकेलो_range_ढेर (last, braced_init_obstack);
    }
}

/* Within a struct initializer, specify the next field to be initialized.  */

शून्य
set_init_label (location_t loc, वृक्ष fieldname, location_t fieldname_loc,
		संरचना obstack *braced_init_obstack)
{
  वृक्ष field;

  यदि (set_designator (loc, असत्य, braced_init_obstack))
    प्रत्यागम;

  designator_erroneous = 1;

  यदि (!RECORD_OR_UNION_TYPE_P (constructor_type))
    {
      error_init (loc, "field name not in record or union initializer");
      प्रत्यागम;
    }

  field = lookup_field (constructor_type, fieldname);

  यदि (field == NULL_वृक्ष)
    {
      वृक्ष guessed_id = lookup_field_fuzzy (constructor_type, fieldname);
      यदि (guessed_id)
	{
	  gcc_rich_location rich_loc (fieldname_loc);
	  rich_loc.add_fixit_misspelled_id (fieldname_loc, guessed_id);
	  error_at (&rich_loc,
		    "%qT has no member named %qE; did you mean %qE?",
		    constructor_type, fieldname, guessed_id);
	}
      अन्यथा
	error_at (fieldname_loc, "%qT has no member named %qE",
		  constructor_type, fieldname);
    }
  अन्यथा
    कुरु
      {
	constructor_fields = वृक्ष_मूल्य (field);
	designator_depth++;
	designator_erroneous = 0;
	यदि (constructor_range_ढेर)
	  धकेलो_range_ढेर (NULL_वृक्ष, braced_init_obstack);
	field = वृक्ष_CHAIN (field);
	यदि (field)
	  {
	    यदि (set_designator (loc, असत्य, braced_init_obstack))
	      प्रत्यागम;
	  }
      }
    यावत् (field != NULL_वृक्ष);
}

/* Helper function for add_pending_init.  Find inorder successor of P
   in AVL tree.  */
स्थिर संरचना init_गाँठ *
init_गाँठ_successor (संरचना init_गाँठ *p)
{
  संरचना init_गाँठ *r;
  यदि (p->दायाँ)
    {
      r = p->दायाँ;
      यावत् (r->बायाँ)
	r = r->बायाँ;
      प्रत्यागम r;
    }
  r = p->parent;
  यावत् (r && p == r->दायाँ)
    {
      p = r;
      r = r->parent;
    }
  प्रत्यागम r;
}

/* Add a new initializer to the tree of pending initializers.  PURPOSE
   identifies the initializer, either array index or field in a structure.
   VALUE is the value of that index or field.  If ORIGTYPE is not
   NULL_TREE, it is the original type of VALUE.

   IMPLICIT is true if value comes from pop_init_level (1),
   the new initializer has been merged with the existing one
   and thus no warnings should be emitted about overriding an
   existing initializer.  */

स्थिर शून्य
add_pending_init (location_t loc, वृक्ष purpose, वृक्ष मूल्य, वृक्ष origtype,
		  तार्किक implicit, संरचना obstack *braced_init_obstack)
{
  संरचना init_गाँठ *p, **q, *r;

  q = &constructor_pending_elts;
  p = 0;

  यदि (वृक्ष_CODE (constructor_type) == ARRAY_TYPE)
    {
      यावत् (*q != 0)
	{
	  p = *q;
	  यदि (वृक्ष_int_cst_lt (purpose, p->purpose))
	    q = &p->बायाँ;
	  अन्यथा यदि (वृक्ष_int_cst_lt (p->purpose, purpose))
	    {
	      यदि (वृक्ष_CODE (p->मूल्य) != RAW_DATA_CST
		  || (p->दायाँ
		      && वृक्ष_int_cst_le (p->दायाँ->purpose, purpose)))
		q = &p->दायाँ;
	      अन्यथा
		{
		  widest_int pp = wi::to_widest (p->purpose);
		  widest_int pw = wi::to_widest (purpose);
		  यदि (pp + RAW_DATA_LENGTH (p->मूल्य) <= pw)
		    q = &p->दायाँ;
		  अन्यथा
		    {
		      /* Override which should split the old RAW_DATA_CST
			 into 2 or 3 pieces.  */
		      यदि (!implicit && warn_override_init)
			warning_init (loc, OPT_Woverride_init,
				      "initialized field overwritten");
		      अचिन्हित HOST_WIDE_INT start = (pw - pp).to_uhwi ();
		      अचिन्हित HOST_WIDE_INT len = 1;
		      यदि (वृक्ष_CODE (मूल्य) == RAW_DATA_CST)
			len = RAW_DATA_LENGTH (मूल्य);
		      अचिन्हित HOST_WIDE_INT end = 0;
		      अचिन्हित plen = RAW_DATA_LENGTH (p->मूल्य);
		      gcc_checking_assert (start < plen && start);
		      यदि (plen - start > len)
			end = plen - start - len;
		      वृक्ष v = p->मूल्य;
		      वृक्ष origtype = p->origtype;
		      यदि (start == 1)
			p->मूल्य = build_int_cst (वृक्ष_TYPE (v),
						  RAW_DATA_UCHAR_ELT (v, 0));
		      अन्यथा
			{
			  p->मूल्य = v;
			  यदि (end > 1)
			    v = copy_गाँठ (v);
			  RAW_DATA_LENGTH (p->मूल्य) = start;
			}
		      यदि (end)
			{
			  वृक्ष epurpose
			    = size_binop (PLUS_व्यंजक, purpose,
					  bitsize_int (len));
			  यदि (end > 1)
			    {
			      RAW_DATA_LENGTH (v) -= plen - end;
			      RAW_DATA_POINTER (v) += plen - end;
			    }
			  अन्यथा
			    v = build_int_cst (वृक्ष_TYPE (v),
					       RAW_DATA_UCHAR_ELT (v, plen
								      - end));
			  add_pending_init (loc, epurpose, v, origtype,
					    implicit, braced_init_obstack);
			}
		      q = &constructor_pending_elts;
		      अनुवर्त;
		    }
		}
	    }
	  अन्यथा
	    {
	      यदि (वृक्ष_CODE (p->मूल्य) == RAW_DATA_CST
		  && (RAW_DATA_LENGTH (p->मूल्य)
		      > (वृक्ष_CODE (मूल्य) == RAW_DATA_CST
			 ? RAW_DATA_LENGTH (मूल्य) : 1)))
		{
		  /* Override which should split the old RAW_DATA_CST
		     into 2 pieces.  */
		  यदि (!implicit && warn_override_init)
		    warning_init (loc, OPT_Woverride_init,
				  "initialized field overwritten");
		  अचिन्हित HOST_WIDE_INT len = 1;
		  यदि (वृक्ष_CODE (मूल्य) == RAW_DATA_CST)
		    len = RAW_DATA_LENGTH (मूल्य);
		  यदि ((अचिन्हित) RAW_DATA_LENGTH (p->मूल्य) > len + 1)
		    {
		      RAW_DATA_LENGTH (p->मूल्य) -= len;
		      RAW_DATA_POINTER (p->मूल्य) += len;
		    }
		  अन्यथा
		    {
		      अचिन्हित पूर्णाङ्क l = RAW_DATA_LENGTH (p->मूल्य) - 1;
		      p->मूल्य
			= build_int_cst (वृक्ष_TYPE (p->मूल्य),
					 RAW_DATA_UCHAR_ELT (p->मूल्य, l));
		    }
		  p->purpose = size_binop (PLUS_व्यंजक, p->purpose,
					   bitsize_int (len));
		  अनुवर्त;
		}
	      यदि (वृक्ष_CODE (मूल्य) == RAW_DATA_CST)
		{
		handle_raw_data:
		  /* RAW_DATA_CST value might overlap various further
		     prior initval entries.  Find out how many.  */
		  अचिन्हित cnt = 0;
		  widest_int w
		    = wi::to_widest (purpose) + RAW_DATA_LENGTH (मूल्य);
		  संरचना init_गाँठ *r = p, *last = रिक्त;
		  तार्किक override_init = warn_override_init;
		  यावत् ((r = init_गाँठ_successor (r))
			 && wi::to_widest (r->purpose) < w)
		    {
		      ++cnt;
		      यदि (वृक्ष_SIDE_EFFECTS (r->मूल्य))
			warning_init (loc, OPT_Woverride_init_side_effects,
				      "initialized field with side-effects "
				      "overwritten");
		      अन्यथा यदि (override_init)
			{
			  warning_init (loc, OPT_Woverride_init,
					"initialized field overwritten");
			  override_init = असत्य;
			}
		      last = r;
		    }
		  यदि (cnt)
		    {
		      यदि (वृक्ष_CODE (last->मूल्य) == RAW_DATA_CST
			  && (wi::to_widest (last->purpose)
			      + RAW_DATA_LENGTH (last->मूल्य) > w))
			{
			  /* The last overlapping prior initval overlaps
			     only partially.  Shrink it and decrease cnt.  */
			  अचिन्हित पूर्णाङ्क l = (wi::to_widest (last->purpose)
					    + RAW_DATA_LENGTH (last->मूल्य)
					    - w).to_uhwi ();
			  --cnt;
			  RAW_DATA_LENGTH (last->मूल्य) -= l;
			  RAW_DATA_POINTER (last->मूल्य) += l;
			  यदि (RAW_DATA_LENGTH (last->मूल्य) == 1)
			    last->मूल्य
			      = build_int_cst (वृक्ष_TYPE (last->मूल्य),
					       RAW_DATA_UCHAR_ELT (last->मूल्य,
								   0));
			  last->purpose
			    = size_binop (PLUS_व्यंजक, last->purpose,
					  bitsize_int (l));
			}
		      /* Instead of deleting cnt nodes from the AVL tree
			 and rebalancing, peel of last cnt bytes from the
			 RAW_DATA_CST.  Overriding thousands of previously
			 initialized array elements with #embed needs to work,
			 but doesn't need to be super efficient.  */
		      gcc_checking_assert ((अचिन्हित) RAW_DATA_LENGTH (मूल्य)
					   > cnt);
		      RAW_DATA_LENGTH (मूल्य) -= cnt;
		      ध्रुव अचिन्हित वर्ण *s
			= &RAW_DATA_UCHAR_ELT (मूल्य, RAW_DATA_LENGTH (मूल्य));
		      अचिन्हित पूर्णाङ्क o = RAW_DATA_LENGTH (मूल्य);
		      प्रति (r = p; cnt--; ++o, ++s)
			{
			  r = init_गाँठ_successor (r);
			  r->purpose = size_binop (PLUS_व्यंजक, purpose,
						   bitsize_int (o));
			  r->मूल्य = build_int_cst (वृक्ष_TYPE (मूल्य), *s);
			  r->origtype = origtype;
			}
		      यदि (RAW_DATA_LENGTH (मूल्य) == 1)
			मूल्य = build_int_cst (वृक्ष_TYPE (मूल्य),
					       RAW_DATA_UCHAR_ELT (मूल्य, 0));
		    }
		}
	      यदि (!implicit)
		{
		  यदि (वृक्ष_SIDE_EFFECTS (p->मूल्य))
		    warning_init (loc, OPT_Woverride_init_side_effects,
				  "initialized field with side-effects "
				  "overwritten");
		  अन्यथा यदि (warn_override_init)
		    warning_init (loc, OPT_Woverride_init,
				  "initialized field overwritten");
		}
	      p->मूल्य = मूल्य;
	      p->origtype = origtype;
	      प्रत्यागम;
	    }
	}
      यदि (वृक्ष_CODE (मूल्य) == RAW_DATA_CST && p)
	{
	  संरचना init_गाँठ *r;
	  यदि (q == &p->बायाँ)
	    r = p;
	  अन्यथा
	    r = init_गाँठ_successor (p);
	  यदि (r && wi::to_widest (r->purpose) < (wi::to_widest (purpose)
						 + RAW_DATA_LENGTH (मूल्य)))
	    {
	      /* Overlap with at least one prior initval in the range but
		 not at the start.  */
	      p = r;
	      p->purpose = purpose;
	      गच्छ handle_raw_data;
	    }
	}
    }
  अन्यथा
    {
      वृक्ष bitpos;

      bitpos = bit_position (purpose);
      यावत् (*q != रिक्त)
	{
	  p = *q;
	  यदि (वृक्ष_int_cst_lt (bitpos, bit_position (p->purpose)))
	    q = &p->बायाँ;
	  अन्यथा यदि (p->purpose != purpose)
	    q = &p->दायाँ;
	  अन्यथा
	    {
	      यदि (!implicit)
		{
		  यदि (वृक्ष_SIDE_EFFECTS (p->मूल्य))
		    warning_init (loc, OPT_Woverride_init_side_effects,
				  "initialized field with side-effects "
				  "overwritten");
		  अन्यथा यदि (warn_override_init)
		    warning_init (loc, OPT_Woverride_init,
				  "initialized field overwritten");
		}
	      p->मूल्य = मूल्य;
	      p->origtype = origtype;
	      प्रत्यागम;
	    }
	}
    }

  r = (संरचना init_गाँठ *) obstack_alloc (braced_init_obstack,
					  परिमाण (संरचना init_गाँठ));
  r->purpose = purpose;
  r->मूल्य = मूल्य;
  r->origtype = origtype;

  *q = r;
  r->parent = p;
  r->बायाँ = 0;
  r->दायाँ = 0;
  r->balance = 0;

  यावत् (p)
    {
      संरचना init_गाँठ *s;

      यदि (r == p->बायाँ)
	{
	  यदि (p->balance == 0)
	    p->balance = -1;
	  अन्यथा यदि (p->balance < 0)
	    {
	      यदि (r->balance < 0)
		{
		  /* L rotation.  */
		  p->बायाँ = r->दायाँ;
		  यदि (p->बायाँ)
		    p->बायाँ->parent = p;
		  r->दायाँ = p;

		  p->balance = 0;
		  r->balance = 0;

		  s = p->parent;
		  p->parent = r;
		  r->parent = s;
		  यदि (s)
		    {
		      यदि (s->बायाँ == p)
			s->बायाँ = r;
		      अन्यथा
			s->दायाँ = r;
		    }
		  अन्यथा
		    constructor_pending_elts = r;
		}
	      अन्यथा
		{
		  /* LR rotation.  */
		  संरचना init_गाँठ *t = r->दायाँ;

		  r->दायाँ = t->बायाँ;
		  यदि (r->दायाँ)
		    r->दायाँ->parent = r;
		  t->बायाँ = r;

		  p->बायाँ = t->दायाँ;
		  यदि (p->बायाँ)
		    p->बायाँ->parent = p;
		  t->दायाँ = p;

		  p->balance = t->balance < 0;
		  r->balance = -(t->balance > 0);
		  t->balance = 0;

		  s = p->parent;
		  p->parent = t;
		  r->parent = t;
		  t->parent = s;
		  यदि (s)
		    {
		      यदि (s->बायाँ == p)
			s->बायाँ = t;
		      अन्यथा
			s->दायाँ = t;
		    }
		  अन्यथा
		    constructor_pending_elts = t;
		}
	      भङ्ग;
	    }
	  अन्यथा
	    {
	      /* p->balance == +1; growth of left side balances the node.  */
	      p->balance = 0;
	      भङ्ग;
	    }
	}
      अन्यथा /* r == p->right */
	{
	  यदि (p->balance == 0)
	    /* Growth propagation from right side.  */
	    p->balance++;
	  अन्यथा यदि (p->balance > 0)
	    {
	      यदि (r->balance > 0)
		{
		  /* R rotation.  */
		  p->दायाँ = r->बायाँ;
		  यदि (p->दायाँ)
		    p->दायाँ->parent = p;
		  r->बायाँ = p;

		  p->balance = 0;
		  r->balance = 0;

		  s = p->parent;
		  p->parent = r;
		  r->parent = s;
		  यदि (s)
		    {
		      यदि (s->बायाँ == p)
			s->बायाँ = r;
		      अन्यथा
			s->दायाँ = r;
		    }
		  अन्यथा
		    constructor_pending_elts = r;
		}
	      अन्यथा /* r->balance == -1 */
		{
		  /* RL rotation */
		  संरचना init_गाँठ *t = r->बायाँ;

		  r->बायाँ = t->दायाँ;
		  यदि (r->बायाँ)
		    r->बायाँ->parent = r;
		  t->दायाँ = r;

		  p->दायाँ = t->बायाँ;
		  यदि (p->दायाँ)
		    p->दायाँ->parent = p;
		  t->बायाँ = p;

		  r->balance = (t->balance < 0);
		  p->balance = -(t->balance > 0);
		  t->balance = 0;

		  s = p->parent;
		  p->parent = t;
		  r->parent = t;
		  t->parent = s;
		  यदि (s)
		    {
		      यदि (s->बायाँ == p)
			s->बायाँ = t;
		      अन्यथा
			s->दायाँ = t;
		    }
		  अन्यथा
		    constructor_pending_elts = t;
		}
	      भङ्ग;
	    }
	  अन्यथा
	    {
	      /* p->balance == -1; growth of right side balances the node.  */
	      p->balance = 0;
	      भङ्ग;
	    }
	}

      r = p;
      p = p->parent;
    }
}

/* Build AVL tree from a sorted chain.  */

स्थिर शून्य
set_nonincremental_init (संरचना obstack * braced_init_obstack)
{
  अचिन्हित HOST_WIDE_INT ix;
  वृक्ष index, मूल्य;

  यदि (वृक्ष_CODE (constructor_type) != RECORD_TYPE
      && वृक्ष_CODE (constructor_type) != ARRAY_TYPE)
    प्रत्यागम;

  FOR_EACH_CONSTRUCTOR_ELT (constructor_elements, ix, index, मूल्य)
    add_pending_init (निवेश_location, index, मूल्य, NULL_वृक्ष, सत्य,
		      braced_init_obstack);
  constructor_elements = रिक्त;
  यदि (वृक्ष_CODE (constructor_type) == RECORD_TYPE)
    {
      constructor_unfilled_fields = TYPE_FIELDS (constructor_type);
      /* Skip any nameless bit fields at the beginning.  */
      यावत् (constructor_unfilled_fields != NULL_वृक्ष
	     && DECL_UNNAMED_BIT_FIELD (constructor_unfilled_fields))
	constructor_unfilled_fields = वृक्ष_CHAIN (constructor_unfilled_fields);

    }
  अन्यथा यदि (वृक्ष_CODE (constructor_type) == ARRAY_TYPE)
    {
      यदि (TYPE_DOMAIN (constructor_type))
	constructor_unfilled_index
	  = convert (bitsizetype,
		     TYPE_MIN_मूल्य (TYPE_DOMAIN (constructor_type)));
      अन्यथा
	constructor_unfilled_index = bitsize_zero_गाँठ;
    }
  constructor_incremental = 0;
}

/* Build AVL tree from a string constant.  */

स्थिर शून्य
set_nonincremental_init_from_string (वृक्ष str,
				     संरचना obstack * braced_init_obstack)
{
  वृक्ष मूल्य, purpose, type;
  HOST_WIDE_INT val[2];
  ध्रुव वर्ण *p, *end;
  पूर्णाङ्क byte, wchar_bytes, charwidth, bitpos;

  gcc_assert (वृक्ष_CODE (constructor_type) == ARRAY_TYPE);

  wchar_bytes = TYPE_PRECISION (वृक्ष_TYPE (वृक्ष_TYPE (str))) / BITS_PER_UNIT;
  charwidth = TYPE_PRECISION (char_type_गाँठ);
  gcc_assert ((माप_प्रकार) wchar_bytes * charwidth
	      <= ARRAY_SIZE (val) * HOST_BITS_PER_WIDE_INT);
  type = वृक्ष_TYPE (constructor_type);
  p = वृक्ष_STRING_POINTER (str);
  end = p + वृक्ष_STRING_LENGTH (str);

  प्रति (purpose = bitsize_zero_गाँठ;
       p < end
       && !(constructor_max_index
	    && वृक्ष_int_cst_lt (constructor_max_index, purpose));
       purpose = size_binop (PLUS_व्यंजक, purpose, bitsize_one_गाँठ))
    {
      यदि (wchar_bytes == 1)
	{
	  val[0] = (अचिन्हित वर्ण) *p++;
	  val[1] = 0;
	}
      अन्यथा
	{
	  val[1] = 0;
	  val[0] = 0;
	  प्रति (byte = 0; byte < wchar_bytes; byte++)
	    {
	      यदि (BYTES_BIG_ENDIAN)
		bitpos = (wchar_bytes - byte - 1) * charwidth;
	      अन्यथा
		bitpos = byte * charwidth;
	      val[bitpos / HOST_BITS_PER_WIDE_INT]
		|= ((अचिन्हित HOST_WIDE_INT) ((अचिन्हित वर्ण) *p++))
		   << (bitpos % HOST_BITS_PER_WIDE_INT);
	    }
	}

      यदि (!TYPE_UNSIGNED (type))
	{
	  bitpos = ((wchar_bytes - 1) * charwidth) + HOST_BITS_PER_CHAR;
	  यदि (bitpos < HOST_BITS_PER_WIDE_INT)
	    {
	      यदि (val[0] & (HOST_WIDE_INT_1 << (bitpos - 1)))
		{
		  val[0] |= HOST_WIDE_INT_M1U << bitpos;
		  val[1] = -1;
		}
	    }
	  अन्यथा यदि (bitpos == HOST_BITS_PER_WIDE_INT)
	    {
	      यदि (val[0] < 0)
		val[1] = -1;
	    }
	  अन्यथा यदि (val[1] & (HOST_WIDE_INT_1
			     << (bitpos - 1 - HOST_BITS_PER_WIDE_INT)))
	    val[1] |= HOST_WIDE_INT_M1U << (bitpos - HOST_BITS_PER_WIDE_INT);
	}

      मूल्य = wide_int_to_वृक्ष (type,
				wide_int::from_array (val, 2,
						      HOST_BITS_PER_WIDE_INT * 2));
      add_pending_init (निवेश_location, purpose, मूल्य, NULL_वृक्ष, सत्य,
                        braced_init_obstack);
    }

  constructor_incremental = 0;
}

/* Return value of FIELD in pending initializer or NULL_TREE if the field was
   not initialized yet.  */

स्थिर वृक्ष
find_init_member (वृक्ष field, संरचना obstack * braced_init_obstack)
{
  संरचना init_गाँठ *p;

  यदि (वृक्ष_CODE (constructor_type) == ARRAY_TYPE)
    {
      यदि (constructor_incremental
	  && वृक्ष_int_cst_lt (field, constructor_unfilled_index))
	set_nonincremental_init (braced_init_obstack);

      p = constructor_pending_elts;
      यावत् (p)
	{
	  यदि (वृक्ष_int_cst_lt (field, p->purpose))
	    p = p->बायाँ;
	  अन्यथा यदि (वृक्ष_int_cst_lt (p->purpose, field))
	    p = p->दायाँ;
	  अन्यथा
	    प्रत्यागम p->मूल्य;
	}
    }
  अन्यथा यदि (वृक्ष_CODE (constructor_type) == RECORD_TYPE)
    {
      वृक्ष bitpos = bit_position (field);

      यदि (constructor_incremental
	  && (!constructor_unfilled_fields
	      || वृक्ष_int_cst_lt (bitpos,
				  bit_position (constructor_unfilled_fields))))
	set_nonincremental_init (braced_init_obstack);

      p = constructor_pending_elts;
      यावत् (p)
	{
	  यदि (field == p->purpose)
	    प्रत्यागम p->मूल्य;
	  अन्यथा यदि (वृक्ष_int_cst_lt (bitpos, bit_position (p->purpose)))
	    p = p->बायाँ;
	  अन्यथा
	    p = p->दायाँ;
	}
    }
  अन्यथा यदि (वृक्ष_CODE (constructor_type) == UNION_TYPE)
    {
      यदि (!vec_safe_is_empty (constructor_elements)
	  && (constructor_elements->last ().index == field))
	प्रत्यागम constructor_elements->last ().मूल्य;
    }
  प्रत्यागम NULL_वृक्ष;
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

स्थिर शून्य
output_init_element (location_t loc, वृक्ष मूल्य, वृक्ष origtype,
		     तार्किक strict_string, वृक्ष type, वृक्ष field, तार्किक pending,
		     तार्किक implicit, संरचना obstack * braced_init_obstack)
{
  वृक्ष semantic_type = NULL_वृक्ष;
  तार्किक maybe_const = सत्य;
  तार्किक npc, int_const_व्यंजक, arith_const_व्यंजक;

  यदि (type == error_mark_गाँठ || मूल्य == error_mark_गाँठ)
    {
      constructor_erroneous = 1;
      प्रत्यागम;
    }
  यदि (वृक्ष_CODE (वृक्ष_TYPE (मूल्य)) == ARRAY_TYPE
      && (वृक्ष_CODE (मूल्य) == STRING_CST
	  || वृक्ष_CODE (मूल्य) == COMPOUND_LITERAL_व्यंजक)
      && !(वृक्ष_CODE (मूल्य) == STRING_CST
	   && वृक्ष_CODE (type) == ARRAY_TYPE
	   && INTEGRAL_TYPE_P (वृक्ष_TYPE (type)))
      && !comptypes (TYPE_MAIN_VARIANT (वृक्ष_TYPE (मूल्य)),
		     TYPE_MAIN_VARIANT (type)))
    मूल्य = array_to_pointer_conversion (निवेश_location, मूल्य);

  यदि (वृक्ष_CODE (मूल्य) == COMPOUND_LITERAL_व्यंजक
      && require_constant_मूल्य && pending)
    {
      /* As an extension, allow initializing objects with static storage
	 duration with compound literals (which are then treated just as
	 the brace enclosed list they contain).  */
      यदि (flag_isoc99)
	pedwarn_init (loc, OPT_Wpedantic, "initializer element is not "
		      "constant");
      वृक्ष decl = COMPOUND_LITERAL_व्यंजक_DECL (मूल्य);
      मूल्य = DECL_INITIAL (decl);
    }

  npc = null_pointer_constant_p (मूल्य);
  int_const_व्यंजक = (वृक्ष_CODE (मूल्य) == INTEGER_CST
		    && !वृक्ष_OVERFLOW (मूल्य)
		    && INTEGRAL_TYPE_P (वृक्ष_TYPE (मूल्य)));
  /* Not fully determined before folding.  */
  arith_const_व्यंजक = सत्य;
  यदि (वृक्ष_CODE (मूल्य) == EXCESS_PRECISION_व्यंजक)
    {
      semantic_type = वृक्ष_TYPE (मूल्य);
      मूल्य = वृक्ष_OPERAND (मूल्य, 0);
    }
  मूल्य = c_fully_fold (मूल्य, require_constant_मूल्य, &maybe_const);
  /* TODO: this may not detect all cases of expressions folding to
     constants that are not arithmetic constant expressions.  */
  यदि (!maybe_const)
    arith_const_व्यंजक = असत्य;
  अन्यथा यदि (!INTEGRAL_TYPE_P (वृक्ष_TYPE (मूल्य))
	   && वृक्ष_CODE (वृक्ष_TYPE (मूल्य)) != REAL_TYPE
	   && वृक्ष_CODE (वृक्ष_TYPE (मूल्य)) != COMPLEX_TYPE)
    arith_const_व्यंजक = असत्य;
  अन्यथा यदि (वृक्ष_CODE (मूल्य) != INTEGER_CST
	   && वृक्ष_CODE (मूल्य) != REAL_CST
	   && वृक्ष_CODE (मूल्य) != COMPLEX_CST
	   && वृक्ष_CODE (मूल्य) != RAW_DATA_CST)
    arith_const_व्यंजक = असत्य;
  अन्यथा यदि (वृक्ष_OVERFLOW (मूल्य))
    arith_const_व्यंजक = असत्य;

  यदि (मूल्य == error_mark_गाँठ)
    constructor_erroneous = 1;
  अन्यथा यदि (!वृक्ष_CONSTANT (मूल्य))
    constructor_constant = 0;
  अन्यथा यदि (!initializer_constant_valid_p (मूल्य,
					  वृक्ष_TYPE (मूल्य),
					  AGGREGATE_TYPE_P (constructor_type)
					  && TYPE_REVERSE_STORAGE_ORDER
					     (constructor_type))
	   || (RECORD_OR_UNION_TYPE_P (constructor_type)
	       && DECL_C_BIT_FIELD (field)
	       && वृक्ष_CODE (मूल्य) != INTEGER_CST))
    constructor_simple = 0;
  यदि (!maybe_const)
    constructor_nonconst = 1;

  /* Digest the initializer and issue any errors about incompatible
     types before issuing errors about non-constant initializers.  */
  वृक्ष new_मूल्य = मूल्य;
  यदि (semantic_type)
    new_मूल्य = build1 (EXCESS_PRECISION_व्यंजक, semantic_type, मूल्य);
  /* In the case of braces around a scalar initializer, the result of
     this initializer processing goes through digest_init again at the
     outer level.  In the case of a constexpr initializer for a
     pointer, avoid converting a null pointer constant to something
     that is not a null pointer constant to avoid a spurious error
     from that second processing.  */
  यदि (!require_constexpr_मूल्य
      || !npc
      || वृक्ष_CODE (constructor_type) != POINTER_TYPE)
    new_मूल्य = digest_init (loc,
			     RECORD_OR_UNION_TYPE_P (constructor_type)
			     ? field : constructor_fields
			     ? constructor_fields : constructor_decl,
			     type, new_मूल्य, origtype, npc,
			     int_const_व्यंजक, arith_const_व्यंजक, strict_string,
			     require_constant_मूल्य, require_constexpr_मूल्य);
  यदि (new_मूल्य == error_mark_गाँठ)
    {
      constructor_erroneous = 1;
      प्रत्यागम;
    }
  यदि (require_constant_मूल्य || require_constant_elements)
    constant_expression_warning (new_मूल्य);

  /* Proceed to check the constness of the original initializer.  */
  यदि (!initializer_constant_valid_p (मूल्य, वृक्ष_TYPE (मूल्य)))
    {
      यदि (require_constant_मूल्य)
	{
	  error_init (loc, "initializer element is not constant");
	  मूल्य = error_mark_गाँठ;
	}
      अन्यथा यदि (require_constant_elements)
	pedwarn (loc, OPT_Wpedantic,
		 "initializer element is not computable at load time");
    }
  अन्यथा यदि (!maybe_const
	   && (require_constant_मूल्य || require_constant_elements))
    pedwarn_init (loc, OPT_Wpedantic,
		  "initializer element is not a constant expression");
  /* digest_init has already carried out the additional checks
     required for 'constexpr' initializers (using the information
     passed to it about whether the original initializer was certain
     kinds of constant expression), so that check does not need to be
     repeated here.  */

  /* Issue -Wc++-compat warnings about initializing a bitfield with
     enum type.  */
  यदि (warn_cxx_compat
      && field != NULL_वृक्ष
      && वृक्ष_CODE (field) == FIELD_DECL
      && DECL_BIT_FIELD_TYPE (field) != NULL_वृक्ष
      && (TYPE_MAIN_VARIANT (DECL_BIT_FIELD_TYPE (field))
	  != TYPE_MAIN_VARIANT (type))
      && वृक्ष_CODE (DECL_BIT_FIELD_TYPE (field)) == ENUMERAL_TYPE)
    {
      वृक्ष checktype = origtype != NULL_वृक्ष ? origtype : वृक्ष_TYPE (मूल्य);
      यदि (checktype != error_mark_गाँठ
	  && (TYPE_MAIN_VARIANT (checktype)
	      != TYPE_MAIN_VARIANT (DECL_BIT_FIELD_TYPE (field))))
	warning_init (loc, OPT_Wc___compat,
		      "enum conversion in initialization is invalid in C++");
    }

  /* If this field is empty and does not have side effects (and is not at
     the end of structure), don't do anything other than checking the
     initializer.  */
  यदि (field
      && (वृक्ष_TYPE (field) == error_mark_गाँठ
	  || (COMPLETE_TYPE_P (वृक्ष_TYPE (field))
	      && integer_zerop (TYPE_SIZE (वृक्ष_TYPE (field)))
	      && !वृक्ष_SIDE_EFFECTS (new_मूल्य)
	      && (वृक्ष_CODE (constructor_type) == ARRAY_TYPE
		  || DECL_CHAIN (field)))))
    प्रत्यागम;

  /* Finally, set VALUE to the initializer value digested above.  */
  मूल्य = new_मूल्य;

  /* If this element doesn't come next in sequence,
     put it on constructor_pending_elts.  */
  यदि (वृक्ष_CODE (constructor_type) == ARRAY_TYPE
      && (!constructor_incremental
	  || !वृक्ष_int_cst_equal (field, constructor_unfilled_index)
	  || (वृक्ष_CODE (मूल्य) == RAW_DATA_CST
	      && constructor_pending_elts
	      && pending)))
    {
      यदि (constructor_incremental
	  && (वृक्ष_int_cst_lt (field, constructor_unfilled_index)
	      || (वृक्ष_CODE (मूल्य) == RAW_DATA_CST
		  && constructor_pending_elts
		  && pending)))
	set_nonincremental_init (braced_init_obstack);

      add_pending_init (loc, field, मूल्य, origtype, implicit,
			braced_init_obstack);
      प्रत्यागम;
    }
  अन्यथा यदि (वृक्ष_CODE (constructor_type) == RECORD_TYPE
	   && (!constructor_incremental
	       || field != constructor_unfilled_fields))
    {
      /* We do this for records but not for unions.  In a union,
	 no matter which field is specified, it can be initialized
	 right away since it starts at the beginning of the union.  */
      यदि (constructor_incremental)
	{
	  यदि (!constructor_unfilled_fields)
	    set_nonincremental_init (braced_init_obstack);
	  अन्यथा
	    {
	      वृक्ष bitpos, unfillpos;

	      bitpos = bit_position (field);
	      unfillpos = bit_position (constructor_unfilled_fields);

	      यदि (वृक्ष_int_cst_lt (bitpos, unfillpos))
		set_nonincremental_init (braced_init_obstack);
	    }
	}

      add_pending_init (loc, field, मूल्य, origtype, implicit,
			braced_init_obstack);
      प्रत्यागम;
    }
  अन्यथा यदि (वृक्ष_CODE (constructor_type) == UNION_TYPE
	   && !vec_safe_is_empty (constructor_elements))
    {
      यदि (!implicit)
	{
	  यदि (वृक्ष_SIDE_EFFECTS (constructor_elements->last ().मूल्य))
	    warning_init (loc, OPT_Woverride_init_side_effects,
			  "initialized field with side-effects overwritten");
	  अन्यथा यदि (warn_override_init)
	    warning_init (loc, OPT_Woverride_init,
			  "initialized field overwritten");
	}

      /* We can have just one union field set.  */
      constructor_elements = रिक्त;
    }

  /* Otherwise, output this element either to
     constructor_elements or to the assembler file.  */

  constructor_elt celt = {field, मूल्य};
  vec_safe_धकेलो (constructor_elements, celt);

  /* Advance the variable that indicates sequential elements output.  */
  यदि (वृक्ष_CODE (constructor_type) == ARRAY_TYPE)
    {
      वृक्ष inc = bitsize_one_गाँठ;
      यदि (मूल्य && वृक्ष_CODE (मूल्य) == RAW_DATA_CST)
	inc = bitsize_int (RAW_DATA_LENGTH (मूल्य));
      constructor_unfilled_index
	= size_binop_loc (निवेश_location, PLUS_व्यंजक,
			  constructor_unfilled_index, inc);
    }
  अन्यथा यदि (वृक्ष_CODE (constructor_type) == RECORD_TYPE)
    {
      constructor_unfilled_fields
	= DECL_CHAIN (constructor_unfilled_fields);

      /* Skip any nameless bit fields.  */
      यावत् (constructor_unfilled_fields != NULL_वृक्ष
	     && DECL_UNNAMED_BIT_FIELD (constructor_unfilled_fields))
	constructor_unfilled_fields
	  = DECL_CHAIN (constructor_unfilled_fields);
    }
  अन्यथा यदि (वृक्ष_CODE (constructor_type) == UNION_TYPE)
    constructor_unfilled_fields = NULL_वृक्ष;

  /* Now output any pending elements which have become next.  */
  यदि (pending)
    output_pending_init_elements (0, braced_init_obstack);
}

/* For two FIELD_DECLs in the same chain, return -1 if field1
   comes before field2, 1 if field1 comes after field2 and
   0 if field1 == field2.  */

स्थिर पूर्णाङ्क
init_field_decl_cmp (वृक्ष field1, वृक्ष field2)
{
  यदि (field1 == field2)
    प्रत्यागम 0;

  वृक्ष bitpos1 = bit_position (field1);
  वृक्ष bitpos2 = bit_position (field2);
  यदि (वृक्ष_int_cst_equal (bitpos1, bitpos2))
    {
      /* If one of the fields has non-zero bitsize, then that
	 field must be the last one in a sequence of zero
	 sized fields, fields after it will have bigger
	 bit_position.  */
      यदि (वृक्ष_TYPE (field1) != error_mark_गाँठ
	  && COMPLETE_TYPE_P (वृक्ष_TYPE (field1))
	  && integer_nonzerop (वृक्ष_TYPE (field1)))
	प्रत्यागम 1;
      यदि (वृक्ष_TYPE (field2) != error_mark_गाँठ
	  && COMPLETE_TYPE_P (वृक्ष_TYPE (field2))
	  && integer_nonzerop (वृक्ष_TYPE (field2)))
	प्रत्यागम -1;
      /* Otherwise, fallback to DECL_CHAIN walk to find out
	 which field comes earlier.  Walk chains of both
	 fields, so that if field1 and field2 are close to each
	 other in either order, it is found soon even for large
	 sequences of zero sized fields.  */
      वृक्ष f1 = field1, f2 = field2;
      यावत् (1)
	{
	  f1 = DECL_CHAIN (f1);
	  f2 = DECL_CHAIN (f2);
	  यदि (f1 == NULL_वृक्ष)
	    {
	      gcc_assert (f2);
	      प्रत्यागम 1;
	    }
	  यदि (f2 == NULL_वृक्ष)
	    प्रत्यागम -1;
	  यदि (f1 == field2)
	    प्रत्यागम -1;
	  यदि (f2 == field1)
	    प्रत्यागम 1;
	  यदि (!वृक्ष_int_cst_equal (bit_position (f1), bitpos1))
	    प्रत्यागम 1;
	  यदि (!वृक्ष_int_cst_equal (bit_position (f2), bitpos1))
	    प्रत्यागम -1;
	}
    }
  अन्यथा यदि (वृक्ष_int_cst_lt (bitpos1, bitpos2))
    प्रत्यागम -1;
  अन्यथा
    प्रत्यागम 1;
}

/* Output any pending elements which have become next.
   As we output elements, constructor_unfilled_{fields,index}
   advances, which may cause other elements to become next;
   if so, they too are output.

   If ALL is 0, we return when there are
   no more pending elements to output now.

   If ALL is 1, we output space as necessary so that
   we can output all the pending elements.  */
स्थिर शून्य
output_pending_init_elements (पूर्णाङ्क all, संरचना obstack * braced_init_obstack)
{
  संरचना init_गाँठ *elt = constructor_pending_elts;
  वृक्ष next;

 retry:

  /* Look through the whole pending tree.
     If we find an element that should be output now,
     output it.  Otherwise, set NEXT to the element
     that comes first among those still pending.  */

  next = NULL_वृक्ष;
  यावत् (elt)
    {
      यदि (वृक्ष_CODE (constructor_type) == ARRAY_TYPE)
	{
	  यदि (वृक्ष_int_cst_equal (elt->purpose,
				  constructor_unfilled_index))
	    output_init_element (निवेश_location, elt->मूल्य, elt->origtype,
				 सत्य, वृक्ष_TYPE (constructor_type),
				 constructor_unfilled_index, असत्य, असत्य,
				 braced_init_obstack);
	  अन्यथा यदि (वृक्ष_int_cst_lt (constructor_unfilled_index,
				    elt->purpose))
	    {
	      /* Advance to the next smaller node.  */
	      यदि (elt->बायाँ)
		elt = elt->बायाँ;
	      अन्यथा
		{
		  /* We have reached the smallest node bigger than the
		     current unfilled index.  Fill the space first.  */
		  next = elt->purpose;
		  भङ्ग;
		}
	    }
	  अन्यथा
	    {
	      /* Advance to the next bigger node.  */
	      यदि (elt->दायाँ)
		elt = elt->दायाँ;
	      अन्यथा
		{
		  /* We have reached the biggest node in a subtree.  Find
		     the parent of it, which is the next bigger node.  */
		  यावत् (elt->parent && elt->parent->दायाँ == elt)
		    elt = elt->parent;
		  elt = elt->parent;
		  यदि (elt && वृक्ष_int_cst_lt (constructor_unfilled_index,
					      elt->purpose))
		    {
		      next = elt->purpose;
		      भङ्ग;
		    }
		}
	    }
	}
      अन्यथा यदि (RECORD_OR_UNION_TYPE_P (constructor_type))
	{
	  /* If the current record is complete we are done.  */
	  यदि (constructor_unfilled_fields == NULL_वृक्ष)
	    भङ्ग;

	  पूर्णाङ्क cmp = init_field_decl_cmp (constructor_unfilled_fields,
					 elt->purpose);
	  यदि (cmp == 0)
	    output_init_element (निवेश_location, elt->मूल्य, elt->origtype,
				 सत्य, वृक्ष_TYPE (elt->purpose),
				 elt->purpose, असत्य, असत्य,
				 braced_init_obstack);
	  अन्यथा यदि (cmp < 0)
	    {
	      /* Advance to the next smaller node.  */
	      यदि (elt->बायाँ)
		elt = elt->बायाँ;
	      अन्यथा
		{
		  /* We have reached the smallest node bigger than the
		     current unfilled field.  Fill the space first.  */
		  next = elt->purpose;
		  भङ्ग;
		}
	    }
	  अन्यथा
	    {
	      /* Advance to the next bigger node.  */
	      यदि (elt->दायाँ)
		elt = elt->दायाँ;
	      अन्यथा
		{
		  /* We have reached the biggest node in a subtree.  Find
		     the parent of it, which is the next bigger node.  */
		  यावत् (elt->parent && elt->parent->दायाँ == elt)
		    elt = elt->parent;
		  elt = elt->parent;
		  यदि (elt
		      && init_field_decl_cmp (constructor_unfilled_fields,
					      elt->purpose) < 0)
		    {
		      next = elt->purpose;
		      भङ्ग;
		    }
		}
	    }
	}
    }

  /* Ordinarily return, but not if we want to output all
     and there are elements left.  */
  यदि (!(all && next != NULL_वृक्ष))
    प्रत्यागम;

  /* If it's not incremental, just skip over the gap, so that after
     jumping to retry we will output the next successive element.  */
  यदि (RECORD_OR_UNION_TYPE_P (constructor_type))
    constructor_unfilled_fields = next;
  अन्यथा यदि (वृक्ष_CODE (constructor_type) == ARRAY_TYPE)
    constructor_unfilled_index = next;

  /* ELT now points to the node in the pending tree with the next
     initializer to output.  */
  गच्छ retry;
}

/* Expression VALUE coincides with the start of type TYPE in a braced
   initializer.  Return true if we should treat VALUE as initializing
   the first element of TYPE, false if we should treat it as initializing
   TYPE as a whole.

   If the initializer is clearly invalid, the question becomes:
   which choice gives the best error message?  */

स्थिर तार्किक
initialize_elementwise_p (वृक्ष type, वृक्ष मूल्य)
{
  यदि (type == error_mark_गाँठ || मूल्य == error_mark_गाँठ)
    प्रत्यागम असत्य;

  gcc_checking_assert (TYPE_MAIN_VARIANT (type) == type);

  वृक्ष मूल्य_type = वृक्ष_TYPE (मूल्य);
  यदि (मूल्य_type == error_mark_गाँठ)
    प्रत्यागम असत्य;

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
  यदि (gnu_vector_type_p (type))
    प्रत्यागम !VECTOR_TYPE_P (मूल्य_type);

  यदि (AGGREGATE_TYPE_P (type))
    प्रत्यागम !comptypes (type, TYPE_MAIN_VARIANT (मूल्य_type));

  प्रत्यागम असत्य;
}

/* Helper function for process_init_element.  Split first element of
   RAW_DATA_CST and save the rest to *RAW_DATA.  */

स्थिर अन्तःस्थ वृक्ष
maybe_split_raw_data (वृक्ष मूल्य, वृक्ष *raw_data)
{
  यदि (मूल्य == NULL_वृक्ष || वृक्ष_CODE (मूल्य) != RAW_DATA_CST)
    प्रत्यागम मूल्य;
  *raw_data = मूल्य;
  मूल्य = build_int_cst (integer_type_गाँठ,
			 RAW_DATA_UCHAR_ELT (*raw_data, 0));
  ++RAW_DATA_POINTER (*raw_data);
  --RAW_DATA_LENGTH (*raw_data);
  प्रत्यागम मूल्य;
}

/* Return non-zero if c_parser_initval should attempt to optimize
   large initializers into RAW_DATA_CST.  In that case return how
   many elements to optimize at most.  */

अचिन्हित
c_maybe_optimize_large_byte_initializer (शून्य)
{
  यदि (!constructor_type
      || वृक्ष_CODE (constructor_type) != ARRAY_TYPE
      || constructor_ढेर->implicit)
    प्रत्यागम 0;
  वृक्ष elttype = TYPE_MAIN_VARIANT (वृक्ष_TYPE (constructor_type));
  यदि (वृक्ष_CODE (elttype) != INTEGER_TYPE
      && वृक्ष_CODE (elttype) != BITINT_TYPE)
    प्रत्यागम 0;
  यदि (TYPE_PRECISION (elttype) != अक्षर_बिट
      || constructor_ढेर->replacement_मूल्य.मूल्य
      || (COMPLETE_TYPE_P (constructor_type)
	  && !poly_int_वृक्ष_p (TYPE_SIZE (constructor_type)))
      || constructor_range_ढेर)
    प्रत्यागम 0;
  यदि (constructor_max_index == NULL_वृक्ष)
    प्रत्यागम पूर्णांक_उच्च;
  यदि (वृक्ष_int_cst_le (constructor_max_index, constructor_index)
      || integer_all_onesp (constructor_max_index))
    प्रत्यागम 0;
  widest_int w = wi::to_widest (constructor_max_index);
  w -= wi::to_widest (constructor_index);
  w += 1;
  यदि (w < 64)
    प्रत्यागम 0;
  यदि (w > पूर्णांक_उच्च)
    प्रत्यागम पूर्णांक_उच्च;
  प्रत्यागम w.to_uhwi ();
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

शून्य
process_init_element (location_t loc, संरचना c_व्यंजक मूल्य, तार्किक implicit,
		      संरचना obstack * braced_init_obstack)
{
  वृक्ष orig_मूल्य = मूल्य.मूल्य;
  पूर्णाङ्क string_flag
    = (orig_मूल्य != NULL_वृक्ष && वृक्ष_CODE (orig_मूल्य) == STRING_CST);
  तार्किक strict_string = मूल्य.original_code == STRING_CST;
  तार्किक was_designated = designator_depth != 0;
  वृक्ष raw_data = NULL_वृक्ष;

retry:
  designator_depth = 0;
  designator_erroneous = 0;

  यदि (!implicit && मूल्य.मूल्य && !integer_zerop (मूल्य.मूल्य))
    constructor_zeroinit = 0;

  /* Handle superfluous braces around string cst as in
     char x[] = {"foo"}; */
  यदि (constructor_type
      && !was_designated
      && वृक्ष_CODE (constructor_type) == ARRAY_TYPE
      && INTEGRAL_TYPE_P (वृक्ष_TYPE (constructor_type))
      && integer_zerop (constructor_unfilled_index))
    {
      यदि (constructor_ढेर->replacement_मूल्य.मूल्य)
	{
	  error_init (loc, "excess elements in %qT initializer", constructor_type);
	  प्रत्यागम;
	}
      अन्यथा यदि (string_flag)
	{
	  constructor_ढेर->replacement_मूल्य = मूल्य;
	  प्रत्यागम;
	}
    }

  यदि (constructor_ढेर->replacement_मूल्य.मूल्य != NULL_वृक्ष)
    {
      error_init (loc, "excess elements in struct initializer");
      प्रत्यागम;
    }

  /* Ignore elements of a brace group if it is entirely superfluous
     and has already been diagnosed, or if the type is erroneous.  */
  यदि (constructor_type == NULL_वृक्ष || constructor_type == error_mark_गाँठ)
    प्रत्यागम;

  /* Ignore elements of an initializer for a variable-size type.
     Those are diagnosed in the parser (empty initializer braces are OK).  */
  यदि (COMPLETE_TYPE_P (constructor_type)
      && !poly_int_वृक्ष_p (TYPE_SIZE (constructor_type)))
    प्रत्यागम;

  यदि (!implicit && warn_designated_init && !was_designated
      && वृक्ष_CODE (constructor_type) == RECORD_TYPE
      && lookup_attribute ("designated_init",
			   TYPE_ATTRIBUTES (constructor_type)))
    warning_init (loc,
		  OPT_Wdesignated_init,
		  "positional initialization of field "
		  "in %<struct%> declared with %<designated_init%> attribute");

  /* If we've exhausted any levels that didn't have braces,
     pop them now.  */
  यावत् (constructor_ढेर->implicit)
    {
      यदि (RECORD_OR_UNION_TYPE_P (constructor_type)
	  && constructor_fields == NULL_वृक्ष)
	process_init_element (loc,
			      निकालो_init_level (loc, 1, braced_init_obstack,
					      last_init_list_comma),
			      सत्य, braced_init_obstack);
      अन्यथा यदि ((वृक्ष_CODE (constructor_type) == ARRAY_TYPE
		|| gnu_vector_type_p (constructor_type))
	       && constructor_max_index
	       && वृक्ष_int_cst_lt (constructor_max_index,
				   constructor_index))
	process_init_element (loc,
			      निकालो_init_level (loc, 1, braced_init_obstack,
					      last_init_list_comma),
			      सत्य, braced_init_obstack);
      अन्यथा
	भङ्ग;
    }

  /* In the case of [LO ... HI] = VALUE, only evaluate VALUE once.  */
  यदि (constructor_range_ढेर)
    {
      /* If value is a compound literal and we'll be just using its
	 content, don't put it into a SAVE_EXPR.  */
      यदि (वृक्ष_CODE (मूल्य.मूल्य) != COMPOUND_LITERAL_व्यंजक
	  || !require_constant_मूल्य)
	{
	  वृक्ष semantic_type = NULL_वृक्ष;
	  यदि (वृक्ष_CODE (मूल्य.मूल्य) == EXCESS_PRECISION_व्यंजक)
	    {
	      semantic_type = वृक्ष_TYPE (मूल्य.मूल्य);
	      मूल्य.मूल्य = वृक्ष_OPERAND (मूल्य.मूल्य, 0);
	    }
	  मूल्य.मूल्य = save_व्यंजक (मूल्य.मूल्य);
	  यदि (semantic_type)
	    मूल्य.मूल्य = build1 (EXCESS_PRECISION_व्यंजक, semantic_type,
				  मूल्य.मूल्य);
	}
    }

  यावत् (1)
    {
      यदि (वृक्ष_CODE (constructor_type) == RECORD_TYPE)
	{
	  वृक्ष fieldtype;
	  गणना वृक्ष_code fieldcode;

	  यदि (constructor_fields == NULL_वृक्ष)
	    {
	      pedwarn_init (loc, 0, "excess elements in struct initializer");
	      भङ्ग;
	    }

	  fieldtype = वृक्ष_TYPE (constructor_fields);
	  यदि (fieldtype != error_mark_गाँठ)
	    fieldtype = TYPE_MAIN_VARIANT (fieldtype);
	  fieldcode = वृक्ष_CODE (fieldtype);

	  /* Error for non-static initialization of a flexible array member.  */
	  यदि (fieldcode == ARRAY_TYPE
	      && !require_constant_मूल्य
	      && TYPE_SIZE (fieldtype) == NULL_वृक्ष
	      && DECL_CHAIN (constructor_fields) == NULL_वृक्ष)
	    {
	      error_init (loc, "non-static initialization of a flexible "
			  "array member");
	      भङ्ग;
	    }

	  /* Error for initialization of a flexible array member with
	     a string constant if the structure is in an array.  E.g.:
	     struct S { int x; char y[]; };
	     struct S s[] = { { 1, "foo" } };
	     is invalid.  */
	  यदि (string_flag
	      && fieldcode == ARRAY_TYPE
	      && constructor_depth > 1
	      && TYPE_SIZE (fieldtype) == NULL_वृक्ष
	      && DECL_CHAIN (constructor_fields) == NULL_वृक्ष)
	    {
	      तार्किक in_array_p = असत्य;
	      प्रति (संरचना constructor_ढेर *p = constructor_ढेर;
		   p && p->type; p = p->next)
		यदि (वृक्ष_CODE (p->type) == ARRAY_TYPE)
		  {
		    in_array_p = सत्य;
		    भङ्ग;
		  }
	      यदि (in_array_p)
		{
		  error_init (loc, "initialization of flexible array "
			      "member in a nested context");
		  भङ्ग;
		}
	    }

	  /* Accept a string constant to initialize a subarray.  */
	  यदि (मूल्य.मूल्य != NULL_वृक्ष
	      && fieldcode == ARRAY_TYPE
	      && INTEGRAL_TYPE_P (वृक्ष_TYPE (fieldtype))
	      && string_flag)
	    मूल्य.मूल्य = orig_मूल्य;
	  /* Otherwise, if we have come to a subaggregate,
	     and we don't have an element of its type, push into it.  */
	  अन्यथा यदि (मूल्य.मूल्य != NULL_वृक्ष
		   && initialize_elementwise_p (fieldtype, मूल्य.मूल्य))
	    {
	      धकेलो_init_level (loc, 1, braced_init_obstack);
	      अनुवर्त;
	    }

	  मूल्य.मूल्य = maybe_split_raw_data (मूल्य.मूल्य, &raw_data);
	  यदि (मूल्य.मूल्य)
	    {
	      धकेलो_member_name (constructor_fields);
	      output_init_element (loc, मूल्य.मूल्य, मूल्य.original_type,
				   strict_string, fieldtype,
				   constructor_fields, सत्य, implicit,
				   braced_init_obstack);
	      RESTORE_SPELLING_DEPTH (constructor_depth);
	    }
	  अन्यथा
	    /* Do the bookkeeping for an element that was
	       directly output as a constructor.  */
	    {
	      /* For a record, keep track of end position of last field.  */
	      यदि (DECL_SIZE (constructor_fields))
		constructor_bit_index
		  = size_binop_loc (निवेश_location, PLUS_व्यंजक,
				    bit_position (constructor_fields),
				    DECL_SIZE (constructor_fields));

	      /* If the current field was the first one not yet written out,
		 it isn't now, so update.  */
	      यदि (constructor_unfilled_fields == constructor_fields)
		{
		  constructor_unfilled_fields = DECL_CHAIN (constructor_fields);
		  /* Skip any nameless bit fields.  */
		  यावत् (constructor_unfilled_fields != 0
			 && (DECL_UNNAMED_BIT_FIELD
			     (constructor_unfilled_fields)))
		    constructor_unfilled_fields =
		      DECL_CHAIN (constructor_unfilled_fields);
		}
	    }

	  constructor_fields = DECL_CHAIN (constructor_fields);
	  /* Skip any nameless bit fields at the beginning.  */
	  यावत् (constructor_fields != NULL_वृक्ष
		 && DECL_UNNAMED_BIT_FIELD (constructor_fields))
	    constructor_fields = DECL_CHAIN (constructor_fields);
	}
      अन्यथा यदि (वृक्ष_CODE (constructor_type) == UNION_TYPE)
	{
	  वृक्ष fieldtype;
	  गणना वृक्ष_code fieldcode;

	  यदि (constructor_fields == NULL_वृक्ष)
	    {
	      pedwarn_init (loc, 0,
			    "excess elements in union initializer");
	      भङ्ग;
	    }

	  fieldtype = वृक्ष_TYPE (constructor_fields);
	  यदि (fieldtype != error_mark_गाँठ)
	    fieldtype = TYPE_MAIN_VARIANT (fieldtype);
	  fieldcode = वृक्ष_CODE (fieldtype);

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
	  यदि (!in_system_header_at (निवेश_location) && !constructor_designated
	      && !(मूल्य.मूल्य && (integer_zerop (मूल्य.मूल्य)
				   || real_zerop (मूल्य.मूल्य))))
	    warning (OPT_Wtraditional, "traditional C rejects initialization "
		     "of unions");

	  /* Error for non-static initialization of a flexible array member.  */
	  यदि (fieldcode == ARRAY_TYPE
	      && !require_constant_मूल्य
	      && TYPE_SIZE (fieldtype) == NULL_वृक्ष)
	    {
	      error_init (loc, "non-static initialization of a flexible "
			  "array member");
	      भङ्ग;
	    }

	  /* Error for initialization of a flexible array member with
	     a string constant if the structure is in an array.  E.g.:
	     union U { int x; char y[]; };
	     union U s[] = { { 1, "foo" } };
	     is invalid.  */
	  यदि (string_flag
	      && fieldcode == ARRAY_TYPE
	      && constructor_depth > 1
	      && TYPE_SIZE (fieldtype) == NULL_वृक्ष)
	    {
	      तार्किक in_array_p = असत्य;
	      प्रति (संरचना constructor_ढेर *p = constructor_ढेर;
		   p && p->type; p = p->next)
		यदि (वृक्ष_CODE (p->type) == ARRAY_TYPE)
		  {
		    in_array_p = सत्य;
		    भङ्ग;
		  }
	      यदि (in_array_p)
		{
		  error_init (loc, "initialization of flexible array "
			      "member in a nested context");
		  भङ्ग;
		}
	    }

	  /* Accept a string constant to initialize a subarray.  */
	  यदि (मूल्य.मूल्य != NULL_वृक्ष
	      && fieldcode == ARRAY_TYPE
	      && INTEGRAL_TYPE_P (वृक्ष_TYPE (fieldtype))
	      && string_flag)
	    मूल्य.मूल्य = orig_मूल्य;
	  /* Otherwise, if we have come to a subaggregate,
	     and we don't have an element of its type, push into it.  */
	  अन्यथा यदि (मूल्य.मूल्य != NULL_वृक्ष
		   && initialize_elementwise_p (fieldtype, मूल्य.मूल्य))
	    {
	      धकेलो_init_level (loc, 1, braced_init_obstack);
	      अनुवर्त;
	    }

	  मूल्य.मूल्य = maybe_split_raw_data (मूल्य.मूल्य, &raw_data);
	  यदि (मूल्य.मूल्य)
	    {
	      धकेलो_member_name (constructor_fields);
	      output_init_element (loc, मूल्य.मूल्य, मूल्य.original_type,
				   strict_string, fieldtype,
				   constructor_fields, सत्य, implicit,
				   braced_init_obstack);
	      RESTORE_SPELLING_DEPTH (constructor_depth);
	    }
	  अन्यथा
	    /* Do the bookkeeping for an element that was
	       directly output as a constructor.  */
	    {
	      constructor_bit_index = DECL_SIZE (constructor_fields);
	      constructor_unfilled_fields = DECL_CHAIN (constructor_fields);
	    }

	  constructor_fields = NULL_वृक्ष;
	}
      अन्यथा यदि (वृक्ष_CODE (constructor_type) == ARRAY_TYPE)
	{
	  वृक्ष elttype = TYPE_MAIN_VARIANT (वृक्ष_TYPE (constructor_type));
	  गणना वृक्ष_code eltcode = वृक्ष_CODE (elttype);

	  /* Accept a string constant to initialize a subarray.  */
	  यदि (मूल्य.मूल्य != NULL_वृक्ष
	      && eltcode == ARRAY_TYPE
	      && INTEGRAL_TYPE_P (वृक्ष_TYPE (elttype))
	      && string_flag)
	    मूल्य.मूल्य = orig_मूल्य;
	  /* Otherwise, if we have come to a subaggregate,
	     and we don't have an element of its type, push into it.  */
	  अन्यथा यदि (मूल्य.मूल्य != NULL_वृक्ष
		   && initialize_elementwise_p (elttype, मूल्य.मूल्य))
	    {
	      धकेलो_init_level (loc, 1, braced_init_obstack);
	      अनुवर्त;
	    }

	  यदि (constructor_max_index != NULL_वृक्ष
	      && (वृक्ष_int_cst_lt (constructor_max_index, constructor_index)
		  || integer_all_onesp (constructor_max_index))
	      /* For VLA we got an error already.  */
	      && !C_TYPE_VARIABLE_SIZE (constructor_type))
	    {
	      pedwarn_init (loc, 0,
			    "excess elements in array initializer");
	      भङ्ग;
	    }

	  यदि (मूल्य.मूल्य
	      && वृक्ष_CODE (मूल्य.मूल्य) == RAW_DATA_CST
	      && RAW_DATA_LENGTH (मूल्य.मूल्य) > 1
	      && (वृक्ष_CODE (elttype) == INTEGER_TYPE
		  || वृक्ष_CODE (elttype) == BITINT_TYPE)
	      && TYPE_PRECISION (elttype) == अक्षर_बिट
	      && (constructor_max_index == NULL_वृक्ष
		  || वृक्ष_int_cst_lt (constructor_index,
				      constructor_max_index)))
	    {
	      अचिन्हित पूर्णाङ्क len = RAW_DATA_LENGTH (मूल्य.मूल्य);
	      यदि (constructor_max_index)
		{
		  widest_int w = wi::to_widest (constructor_max_index);
		  w -= wi::to_widest (constructor_index);
		  w += 1;
		  यदि (w < len)
		    len = w.to_uhwi ();
		}
	      यदि (len < (अचिन्हित) RAW_DATA_LENGTH (मूल्य.मूल्य))
		{
		  raw_data = copy_गाँठ (मूल्य.मूल्य);
		  RAW_DATA_LENGTH (raw_data) -= len;
		  RAW_DATA_POINTER (raw_data) += len;
		  RAW_DATA_LENGTH (मूल्य.मूल्य) = len;
		}
	      वृक्ष_TYPE (मूल्य.मूल्य) = elttype;
	      धकेलो_array_bounds (वृक्ष_to_uhwi (constructor_index));
	      output_init_element (loc, मूल्य.मूल्य, मूल्य.original_type,
				   असत्य, elttype, constructor_index, सत्य,
				   implicit, braced_init_obstack);
	      RESTORE_SPELLING_DEPTH (constructor_depth);
	      constructor_index
		= size_binop_loc (निवेश_location, PLUS_व्यंजक,
				  constructor_index, bitsize_int (len));
	    }
	  अन्यथा
	    {
	      मूल्य.मूल्य = maybe_split_raw_data (मूल्य.मूल्य, &raw_data);
	      /* Now output the actual element.  */
	      यदि (मूल्य.मूल्य)
		{
		  धकेलो_array_bounds (वृक्ष_to_uhwi (constructor_index));
		  output_init_element (loc, मूल्य.मूल्य, मूल्य.original_type,
				       strict_string, elttype,
				       constructor_index, सत्य, implicit,
				       braced_init_obstack);
		  RESTORE_SPELLING_DEPTH (constructor_depth);
		}

	      constructor_index
		= size_binop_loc (निवेश_location, PLUS_व्यंजक,
				  constructor_index, bitsize_one_गाँठ);

	      यदि (!मूल्य.मूल्य)
		/* If we are doing the bookkeeping for an element that was
		   directly output as a constructor, we must update
		   constructor_unfilled_index.  */
		constructor_unfilled_index = constructor_index;
	    }
	}
      अन्यथा यदि (gnu_vector_type_p (constructor_type))
	{
	  वृक्ष elttype = TYPE_MAIN_VARIANT (वृक्ष_TYPE (constructor_type));

	  /* Do a basic check of initializer size.  Note that vectors
	     may not always have a fixed size derived from their type.  */
	  यदि (maybe_lt (वृक्ष_to_poly_uint64 (constructor_max_index),
			वृक्ष_to_poly_uint64 (constructor_index)))
	    {
	      /* Diagose VLA out-of-bounds as errors.  */
	      यदि (वृक्ष_to_poly_uint64 (constructor_max_index).is_constant())
		pedwarn_init (loc, 0,
			      "excess elements in vector initializer");
	      अन्यथा
		error_init (loc, "excess elements in vector initializer");

	      भङ्ग;
	    }

	  मूल्य.मूल्य = maybe_split_raw_data (मूल्य.मूल्य, &raw_data);
	  /* Now output the actual element.  */
	  यदि (मूल्य.मूल्य)
	    {
	      यदि (वृक्ष_CODE (मूल्य.मूल्य) == VECTOR_CST)
		elttype = TYPE_MAIN_VARIANT (constructor_type);
	      output_init_element (loc, मूल्य.मूल्य, मूल्य.original_type,
				   strict_string, elttype,
				   constructor_index, सत्य, implicit,
				   braced_init_obstack);
	    }

	  constructor_index
	    = size_binop_loc (निवेश_location,
			      PLUS_व्यंजक, constructor_index, bitsize_one_गाँठ);

	  यदि (!मूल्य.मूल्य)
	    /* If we are doing the bookkeeping for an element that was
	       directly output as a constructor, we must update
	       constructor_unfilled_index.  */
	    constructor_unfilled_index = constructor_index;
	}

      /* Handle the sole element allowed in a braced initializer
	 for a scalar variable.  */
      अन्यथा यदि (constructor_type != error_mark_गाँठ
	       && constructor_fields == NULL_वृक्ष)
	{
	  pedwarn_init (loc, 0,
			"excess elements in scalar initializer");
	  भङ्ग;
	}
      अन्यथा
	{
	  मूल्य.मूल्य = maybe_split_raw_data (मूल्य.मूल्य, &raw_data);
	  यदि (मूल्य.मूल्य)
	    output_init_element (loc, मूल्य.मूल्य, मूल्य.original_type,
				 strict_string, constructor_type,
				 NULL_वृक्ष, सत्य, implicit,
				 braced_init_obstack);
	  constructor_fields = NULL_वृक्ष;
	}

      /* Handle range initializers either at this level or anywhere higher
	 in the designator stack.  */
      यदि (constructor_range_ढेर)
	{
	  संरचना constructor_range_ढेर *p, *range_ढेर;
	  पूर्णाङ्क finish = 0;

	  range_ढेर = constructor_range_ढेर;
	  constructor_range_ढेर = 0;
	  यावत् (constructor_ढेर != range_ढेर->ढेर)
	    {
	      gcc_assert (constructor_ढेर->implicit);
	      process_init_element (loc,
				    निकालो_init_level (loc, 1,
						    braced_init_obstack,
						    last_init_list_comma),
				    सत्य, braced_init_obstack);
	    }
	  प्रति (p = range_ढेर;
	       !p->range_end || वृक्ष_int_cst_equal (p->index, p->range_end);
	       p = p->prev)
	    {
	      gcc_assert (constructor_ढेर->implicit);
	      process_init_element (loc,
				    निकालो_init_level (loc, 1,
						    braced_init_obstack,
						    last_init_list_comma),
				    सत्य, braced_init_obstack);
	    }

	  p->index = size_binop_loc (निवेश_location,
				     PLUS_व्यंजक, p->index, bitsize_one_गाँठ);
	  यदि (वृक्ष_int_cst_equal (p->index, p->range_end) && !p->prev)
	    finish = 1;

	  यावत् (1)
	    {
	      constructor_index = p->index;
	      constructor_fields = p->fields;
	      यदि (finish && p->range_end && p->index == p->range_start)
		{
		  finish = 0;
		  p->prev = 0;
		}
	      p = p->next;
	      यदि (!p)
		भङ्ग;
	      finish_implicit_inits (loc, braced_init_obstack);
	      धकेलो_init_level (loc, 2, braced_init_obstack);
	      p->ढेर = constructor_ढेर;
	      यदि (p->range_end && वृक्ष_int_cst_equal (p->index, p->range_end))
		p->index = p->range_start;
	    }

	  यदि (!finish)
	    constructor_range_ढेर = range_ढेर;
	  अनुवर्त;
	}

      भङ्ग;
    }

  constructor_range_ढेर = 0;

  यदि (raw_data && RAW_DATA_LENGTH (raw_data))
    {
      gcc_assert (!string_flag && !was_designated);
      मूल्य.मूल्य = raw_data;
      raw_data = NULL_वृक्ष;
      गच्छ retry;
    }
}

/* Build a complete asm-statement, whose components are a CV_QUALIFIER
   (guaranteed to be 'volatile' or null) and ARGS (represented using
   an ASM_EXPR node).  */
वृक्ष
build_asm_stmt (तार्किक is_volatile, वृक्ष args)
{
  यदि (is_volatile)
    ASM_VOLATILE_P (args) = 1;
  प्रत्यागम add_stmt (args);
}

/* Build an asm-expr, whose components are a STRING, some OUTPUTS,
   some INPUTS, and some CLOBBERS.  The latter three may be NULL.
   SIMPLE indicates whether there was anything at all after the
   string in the asm expression -- asm("blah") and asm("blah" : )
   are subtly different.  We use a ASM_EXPR node to represent this.
   LOC is the location of the asm, and IS_INLINE says whether this
   is asm inline.  */
वृक्ष
build_asm_व्यंजक (location_t loc, वृक्ष string, वृक्ष outputs, वृक्ष inputs,
		वृक्ष clobbers, वृक्ष labels, तार्किक simple, तार्किक is_inline)
{
  वृक्ष tail;
  वृक्ष args;
  पूर्णाङ्क i;
  ध्रुव वर्ण *constraint;
  ध्रुव वर्ण **oconstraints;
  तार्किक allows_mem, allows_reg, is_inout;
  पूर्णाङ्क ninputs, noutputs;

  ninputs = list_length (inputs);
  noutputs = list_length (outputs);
  oconstraints = (ध्रुव वर्ण **) alloca (noutputs * परिमाण (ध्रुव वर्ण *));

  string = resolve_asm_operand_names (string, outputs, inputs, labels);

  /* Remove output conversions that change the type but not the mode.  */
  प्रति (i = 0, tail = outputs; tail; ++i, tail = वृक्ष_CHAIN (tail))
    {
      वृक्ष output = वृक्ष_मूल्य (tail);

      output = c_fully_fold (output, असत्य, रिक्त, सत्य);

      /* ??? Really, this should not be here.  Users should be using a
	 proper lvalue, dammit.  But there's a long history of using casts
	 in the output operands.  In cases like longlong.h, this becomes a
	 primitive form of typechecking -- if the cast can be removed, then
	 the output operand had a type of the proper width; otherwise we'll
	 get an error.  Gross, but ...  */
      STRIP_NOPS (output);

      यदि (!lvalue_or_else (loc, output, lv_asm))
	output = error_mark_गाँठ;

      यदि (output != error_mark_गाँठ
	  && (वृक्ष_READONLY (output)
	      || TYPE_READONLY (वृक्ष_TYPE (output))
	      || (RECORD_OR_UNION_TYPE_P (वृक्ष_TYPE (output))
		  && C_TYPE_FIELDS_READONLY (वृक्ष_TYPE (output)))))
	readonly_error (loc, output, lv_asm);

      constraint = वृक्ष_STRING_POINTER (वृक्ष_मूल्य (वृक्ष_PURPOSE (tail)));
      oconstraints[i] = constraint;

      यदि (parse_output_constraint (&constraint, i, ninputs, noutputs,
				   &allows_mem, &allows_reg, &is_inout,
				   nullptr))
	{
	  /* If the operand is going to end up in memory,
	     mark it addressable.  */
	  यदि (!allows_reg && !c_mark_addressable (output))
	    output = error_mark_गाँठ;
	  यदि (!(!allows_reg && allows_mem)
	      && output != error_mark_गाँठ
	      && VOID_TYPE_P (वृक्ष_TYPE (output)))
	    {
	      error_at (loc, "invalid use of void expression");
	      output = error_mark_गाँठ;
	    }
	  यदि (allows_reg && current_function_decl == NULL_वृक्ष)
	    {
	      error_at (loc, "constraint allows registers outside of "
			     "a function");
	      output = error_mark_गाँठ;
	    }
	}
      अन्यथा
	output = error_mark_गाँठ;

      यदि (current_function_decl == NULL_वृक्ष && output != error_mark_गाँठ)
	{
	  यदि (वृक्ष_SIDE_EFFECTS (output))
	    {
	      error_at (loc, "side-effects in output operand outside "
			     "of a function");
	      output = error_mark_गाँठ;
	    }
	  अन्यथा
	    {
	      वृक्ष addr = build_unary_op (loc, ADDR_व्यंजक, output, असत्य);
	      यदि (addr == error_mark_गाँठ)
		output = error_mark_गाँठ;
	      अन्यथा यदि (!initializer_constant_valid_p (addr, वृक्ष_TYPE (addr)))
		{
		  error_at (loc, "output operand outside of a function is not "
				 "constant");
		  output = error_mark_गाँठ;
		}
	    }
	}
      अन्यथा यदि (output != error_mark_गाँठ && म_माला (constraint, "-"))
	{
	  error_at (loc, "%<-%> modifier used inside of a function");
	  output = error_mark_गाँठ;
	}

      वृक्ष_मूल्य (tail) = output;
    }

  प्रति (i = 0, tail = inputs; tail; ++i, tail = वृक्ष_CHAIN (tail))
    {
      वृक्ष निवेश;

      constraint = वृक्ष_STRING_POINTER (वृक्ष_मूल्य (वृक्ष_PURPOSE (tail)));
      निवेश = वृक्ष_मूल्य (tail);

      यदि (parse_निवेश_constraint (&constraint, i, ninputs, noutputs, 0,
				  oconstraints, &allows_mem, &allows_reg,
				  nullptr))
	{
	  /* If the operand is going to end up in memory,
	     mark it addressable.  */
	  यदि (!allows_reg && allows_mem)
	    {
	      निवेश = c_fully_fold (निवेश, असत्य, रिक्त, सत्य);

	      /* Strip the nops as we allow this case.  FIXME, this really
		 should be rejected or made deprecated.  */
	      STRIP_NOPS (निवेश);
	      यदि (!c_mark_addressable (निवेश))
		निवेश = error_mark_गाँठ;
	    }
	  अन्यथा
	    {
	      निवेश = c_fully_fold (convert_lvalue_to_rvalue (loc, निवेश,
							      सत्य, असत्य),
				    असत्य, रिक्त);

	      यदि (निवेश != error_mark_गाँठ && VOID_TYPE_P (वृक्ष_TYPE (निवेश)))
		{
		  error_at (loc, "invalid use of void expression");
		  निवेश = error_mark_गाँठ;
		}
	    }
	  यदि (allows_reg && current_function_decl == NULL_वृक्ष)
	    {
	      error_at (loc, "constraint allows registers outside of "
			     "a function");
	      निवेश = error_mark_गाँठ;
	    }
	  यदि (constraint[0] == ':' && निवेश != error_mark_गाँठ)
	    {
	      वृक्ष t = निवेश;
	      STRIP_NOPS (t);
	      यदि (वृक्ष_CODE (t) != ADDR_व्यंजक
		  || !(वृक्ष_CODE (वृक्ष_OPERAND (t, 0)) == FUNCTION_DECL
		       || (VAR_P (वृक्ष_OPERAND (t, 0))
			   && is_global_var (वृक्ष_OPERAND (t, 0)))))
		{
		  error_at (loc, "%<:%> constraint operand is not address "
				 "of a function or non-automatic variable");
		  निवेश = error_mark_गाँठ;
		}
	      अन्यथा यदि (वृक्ष_CODE (वृक्ष_OPERAND (t, 0)) == FUNCTION_DECL)
		suppress_warning (वृक्ष_OPERAND (t, 0), OPT_Wunused);
	    }
	}
      अन्यथा
	निवेश = error_mark_गाँठ;

      यदि (current_function_decl == NULL_वृक्ष && निवेश != error_mark_गाँठ)
	{
	  यदि (वृक्ष_SIDE_EFFECTS (निवेश))
	    {
	      error_at (loc, "side-effects in input operand outside "
			     "of a function");
	      निवेश = error_mark_गाँठ;
	    }
	  अन्यथा
	    {
	      वृक्ष tem = निवेश;
	      यदि (allows_mem && lvalue_p (निवेश))
		tem = build_unary_op (loc, ADDR_व्यंजक, निवेश, असत्य);
	      यदि (!initializer_constant_valid_p (tem, वृक्ष_TYPE (tem)))
		{
		  error_at (loc, "input operand outside of a function is not "
				 "constant");
		  निवेश = error_mark_गाँठ;
		}
	    }
	}
      अन्यथा यदि (निवेश != error_mark_गाँठ && म_माला (constraint, "-"))
	{
	  error_at (loc, "%<-%> modifier used inside of a function");
	  निवेश = error_mark_गाँठ;
	}

      वृक्ष_मूल्य (tail) = निवेश;
    }

  args = build_stmt (loc, ASM_व्यंजक, string, outputs, inputs, clobbers, labels);

  /* asm statements without outputs, including simple ones, are treated
     as volatile.  */
  ASM_BASIC_P (args) = simple;
  ASM_VOLATILE_P (args) = (noutputs == 0);
  ASM_INLINE_P (args) = is_inline;

  प्रत्यागम args;
}

/* Generate a goto statement to LABEL.  LOC is the location of the
   GOTO.  */

वृक्ष
c_finish_goto_label (location_t loc, वृक्ष label)
{
  वृक्ष decl = lookup_label_for_goto (loc, label);
  यदि (!decl)
    प्रत्यागम NULL_वृक्ष;
  वृक्ष_USED (decl) = 1;
  mark_decl_used (decl, असत्य);
  {
    add_stmt (build_predict_व्यंजक (PRED_GOTO, NOT_TAKEN));
    वृक्ष t = build1 (GOTO_व्यंजक, void_type_गाँठ, decl);
    SET_व्यंजक_LOCATION (t, loc);
    प्रत्यागम add_stmt (t);
  }
}

/* Generate a computed goto statement to EXPR.  LOC is the location of
   the GOTO.  */

वृक्ष
c_finish_goto_ptr (location_t loc, c_व्यंजक val)
{
  वृक्ष व्यंजक = val.मूल्य;
  वृक्ष t;
  pedwarn (loc, OPT_Wpedantic, "ISO C forbids %<goto *expr;%>");
  यदि (व्यंजक != error_mark_गाँठ
      && !POINTER_TYPE_P (वृक्ष_TYPE (व्यंजक))
      && !null_pointer_constant_p (व्यंजक))
    {
      error_at (val.get_location (),
		"computed goto must be pointer type");
      व्यंजक = build_zero_cst (ptr_type_गाँठ);
    }
  व्यंजक = c_fully_fold (व्यंजक, असत्य, रिक्त);
  व्यंजक = convert (ptr_type_गाँठ, व्यंजक);
  t = build1 (GOTO_व्यंजक, void_type_गाँठ, व्यंजक);
  SET_व्यंजक_LOCATION (t, loc);
  प्रत्यागम add_stmt (t);
}

/* Generate a C `return' statement.  RETVAL is the expression for what
   to return, or a null pointer for `return;' with no value.  LOC is
   the location of the return statement, or the location of the expression,
   if the statement has any.  If ORIGTYPE is not NULL_TREE, it
   is the original type of RETVAL.  MUSTTAIL_P indicates a musttail
   attribute.  */

वृक्ष
c_finish_return (location_t loc, वृक्ष retval, वृक्ष origtype, तार्किक musttail_p)
{
  वृक्ष valtype = वृक्ष_TYPE (वृक्ष_TYPE (current_function_decl)), ret_stmt;
  तार्किक no_warning = असत्य;
  तार्किक npc = असत्य;

  /* Use the expansion point to handle cases such as returning NULL
     in a function returning void.  */
  location_t xloc = expansion_point_location_if_in_system_header (loc);

  यदि (वृक्ष_THIS_VOLATILE (current_function_decl))
    warning_at (xloc, 0,
		"function declared %<noreturn%> has a %<return%> statement");

  set_musttail_on_return (retval, xloc, musttail_p);

  यदि (retval)
    {
      वृक्ष semantic_type = NULL_वृक्ष;
      npc = null_pointer_constant_p (retval);
      यदि (वृक्ष_CODE (retval) == EXCESS_PRECISION_व्यंजक)
	{
	  semantic_type = वृक्ष_TYPE (retval);
	  retval = वृक्ष_OPERAND (retval, 0);
	}
      retval = c_fully_fold (retval, असत्य, रिक्त);
      यदि (semantic_type
	  && valtype != NULL_वृक्ष
	  && वृक्ष_CODE (valtype) != VOID_TYPE)
	retval = build1 (EXCESS_PRECISION_व्यंजक, semantic_type, retval);
    }

  यदि (!retval)
    {
      current_function_returns_null = 1;
      यदि ((warn_return_type >= 0 || flag_isoc99)
	  && valtype != NULL_वृक्ष && वृक्ष_CODE (valtype) != VOID_TYPE)
	{
	  no_warning = सत्य;
	  यदि (emit_diagnostic (flag_isoc99
			       ? diagnostics::kind::permerror
			       : diagnostics::kind::warning,
			       loc, OPT_Wreturn_mismatch,
			       "%<return%> with no value,"
			       " in function returning non-void"))
	    inform (DECL_SOURCE_LOCATION (current_function_decl),
		    "declared here");
	}
    }
  अन्यथा यदि (valtype == NULL_वृक्ष || VOID_TYPE_P (valtype))
    {
      current_function_returns_null = 1;
      तार्किक warned_here;
      यदि (वृक्ष_CODE (वृक्ष_TYPE (retval)) != VOID_TYPE)
	warned_here = permerror_opt
	  (xloc, OPT_Wreturn_mismatch,
	   "%<return%> with a value, in function returning void");
      अन्यथा
	warned_here = pedwarn
	  (xloc, OPT_Wpedantic, "ISO C forbids "
	   "%<return%> with expression, in function returning void");
      यदि (warned_here)
	inform (DECL_SOURCE_LOCATION (current_function_decl),
		"declared here");
    }
  अन्यथा
    {
      वृक्ष t = convert_for_assignment (loc, UNKNOWN_LOCATION, valtype,
				       retval, origtype, ic_return,
				       npc, NULL_वृक्ष, NULL_वृक्ष, 0);
      वृक्ष res = DECL_RESULT (current_function_decl);
      वृक्ष inner;
      तार्किक save;

      current_function_returns_मूल्य = 1;
      यदि (t == error_mark_गाँठ)
	{
	  /* Suppress -Wreturn-type for this function.  */
	  यदि (warn_return_type)
	    suppress_warning (current_function_decl, OPT_Wreturn_type);
	  प्रत्यागम NULL_वृक्ष;
	}

      save = in_late_द्विआधारी_op;
      यदि (C_BOOLEAN_TYPE_P (वृक्ष_TYPE (res))
	  || वृक्ष_CODE (वृक्ष_TYPE (res)) == COMPLEX_TYPE
	  || (SCALAR_FLOAT_TYPE_P (वृक्ष_TYPE (t))
	      && (वृक्ष_CODE (वृक्ष_TYPE (res)) == INTEGER_TYPE
		  || वृक्ष_CODE (वृक्ष_TYPE (res)) == ENUMERAL_TYPE)
	      && sanitize_flags_p (SANITIZE_FLOAT_CAST)))
        in_late_द्विआधारी_op = सत्य;
      inner = t = convert (वृक्ष_TYPE (res), t);
      in_late_द्विआधारी_op = save;

      /* Strip any conversions, additions, and subtractions, and see if
	 we are returning the address of a local variable.  Warn if so.  */
      यावत् (1)
	{
	  विकल्प (वृक्ष_CODE (inner))
	    {
	    CASE_CONVERT:
	    पक्ष NON_LVALUE_व्यंजक:
	    पक्ष PLUS_व्यंजक:
	    पक्ष POINTER_PLUS_व्यंजक:
	      inner = वृक्ष_OPERAND (inner, 0);
	      अनुवर्त;

	    पक्ष MINUS_व्यंजक:
	      /* If the second operand of the MINUS_EXPR has a pointer
		 type (or is converted from it), this may be valid, so
		 don't give a warning.  */
	      {
		वृक्ष op1 = वृक्ष_OPERAND (inner, 1);

		यावत् (!POINTER_TYPE_P (वृक्ष_TYPE (op1))
		       && (CONVERT_व्यंजक_P (op1)
			   || वृक्ष_CODE (op1) == NON_LVALUE_व्यंजक))
		  op1 = वृक्ष_OPERAND (op1, 0);

		यदि (POINTER_TYPE_P (वृक्ष_TYPE (op1)))
		  भङ्ग;

		inner = वृक्ष_OPERAND (inner, 0);
		अनुवर्त;
	      }

	    पक्ष ADDR_व्यंजक:
	      inner = वृक्ष_OPERAND (inner, 0);

	      यावत् (REFERENCE_CLASS_P (inner)
		     && !INDIRECT_REF_P (inner))
		inner = वृक्ष_OPERAND (inner, 0);

	      यदि (DECL_P (inner)
		  && !DECL_EXTERNAL (inner)
		  && DECL_CONTEXT (inner) == current_function_decl
		  && POINTER_TYPE_P (वृक्ष_TYPE (वृक्ष_TYPE (current_function_decl))))
		{
		  यदि (वृक्ष_CODE (inner) == LABEL_DECL)
		    warning_at (loc, OPT_Wreturn_local_addr,
				"function returns address of label");
		  अन्यथा यदि (वृक्ष_CODE (inner) == FUNCTION_DECL
			   && (C_FUNC_NONLOCAL_CONTEXT (inner)
			       || !DECL_INITIAL (inner)))
		    warning_at (loc, OPT_Wreturn_local_addr,
				"function returns address of nested function "
				"referencing local context");
		  अन्यथा यदि (वृक्ष_CODE (inner) != FUNCTION_DECL
			   && !वृक्ष_STATIC (inner))
		    {
		      warning_at (loc, OPT_Wreturn_local_addr,
				  "function returns address of local variable");
		      वृक्ष zero = build_zero_cst (वृक्ष_TYPE (res));
		      t = build2 (COMPOUND_व्यंजक, वृक्ष_TYPE (res), t, zero);
		    }
		}
	      भङ्ग;

	    स्वभाव:
	      भङ्ग;
	    }

	  भङ्ग;
	}

      retval = build2 (MODIFY_व्यंजक, वृक्ष_TYPE (res), res, t);
      SET_व्यंजक_LOCATION (retval, loc);

      यदि (warn_sequence_point)
	verify_sequence_points (retval);
    }

  ret_stmt = build_stmt (loc, RETURN_व्यंजक, retval);
  यदि (no_warning)
    suppress_warning (ret_stmt, OPT_Wreturn_type);
  प्रत्यागम add_stmt (ret_stmt);
}

संरचना c_switch {
  /* The SWITCH_STMT being built.  */
  वृक्ष switch_stmt;

  /* The original type of the testing expression, i.e. before the
     default conversion is applied.  */
  वृक्ष orig_type;

  /* A splay-tree mapping the low element of a case range to the high
     element, or NULL_TREE if there is no high element.  Used to
     determine whether or not a new case label duplicates an old case
     label.  We need a tree, rather than simply a hash table, because
     of the GNU case range extension.  */
  splay_वृक्ष cases;

  /* The bindings at the point of the switch.  This is used for
     warnings crossing decls when branching to a case label.  */
  संरचना c_spot_bindings *bindings;

  /* Whether the switch includes any break statements.  */
  तार्किक break_stmt_seen_p;

  /* The next node on the stack.  */
  संरचना c_switch *next;

  /* Remember whether the controlling expression had boolean type
     before integer promotions for the sake of -Wswitch-bool.  */
  तार्किक bool_cond_p;
};

/* A stack of the currently active switch statements.  The innermost
   switch statement is on the top of the stack.  There is no need to
   mark the stack for garbage collection because it is only active
   during the processing of the body of a function, and we never
   collect at that point.  */

संरचना c_switch *c_switch_ढेर;

/* Start a C switch statement, testing expression EXP.  Return the new
   SWITCH_STMT.  SWITCH_LOC is the location of the `switch'.
   SWITCH_COND_LOC is the location of the switch's condition.
   EXPLICIT_CAST_P is true if the expression EXP has an explicit cast.  */

वृक्ष
c_start_switch (location_t switch_loc,
		location_t switch_cond_loc,
		वृक्ष exp, तार्किक explicit_cast_p, वृक्ष switch_name)
{
  वृक्ष orig_type = error_mark_गाँठ;
  तार्किक bool_cond_p = असत्य;
  संरचना c_switch *cs;

  यदि (exp != error_mark_गाँठ)
    {
      orig_type = वृक्ष_TYPE (exp);

      यदि (!INTEGRAL_TYPE_P (orig_type))
	{
	  यदि (orig_type != error_mark_गाँठ)
	    {
	      error_at (switch_cond_loc, "switch quantity not an integer");
	      orig_type = error_mark_गाँठ;
	    }
	  exp = integer_zero_गाँठ;
	}
      अन्यथा
	{
	  वृक्ष type = TYPE_MAIN_VARIANT (orig_type);
	  वृक्ष e = exp;

	  /* Warn if the condition has boolean value.  */
	  यावत् (वृक्ष_CODE (e) == COMPOUND_व्यंजक)
	    e = वृक्ष_OPERAND (e, 1);

	  यदि ((C_BOOLEAN_TYPE_P (type)
	       || truth_मूल्य_p (वृक्ष_CODE (e)))
	      /* Explicit cast to int suppresses this warning.  */
	      && !(वृक्ष_CODE (type) == INTEGER_TYPE
		   && explicit_cast_p))
	    bool_cond_p = सत्य;

	  यदि (!in_system_header_at (निवेश_location)
	      && (type == long_integer_type_गाँठ
		  || type == long_unsigned_type_गाँठ))
	    warning_at (switch_cond_loc,
			OPT_Wtraditional, "%<long%> switch expression not "
			"converted to %<int%> in ISO C");

	  exp = c_fully_fold (exp, असत्य, रिक्त);
	  exp = default_conversion (exp);

	  यदि (warn_sequence_point)
	    verify_sequence_points (exp);
	}
    }

  /* Add this new SWITCH_STMT to the stack.  */
  cs = XNEW (संरचना c_switch);
  cs->switch_stmt = build_stmt (switch_loc, SWITCH_STMT, exp,
				NULL_वृक्ष, orig_type, NULL_वृक्ष, switch_name);
  cs->orig_type = orig_type;
  cs->cases = splay_वृक्ष_new (case_compare, रिक्त, रिक्त);
  cs->bindings = c_get_switch_bindings ();
  cs->break_stmt_seen_p = असत्य;
  cs->bool_cond_p = bool_cond_p;
  cs->next = c_switch_ढेर;
  c_switch_ढेर = cs;

  प्रत्यागम add_stmt (cs->switch_stmt);
}

/* Process a case label at location LOC, with attributes ATTRS.  */

वृक्ष
do_case (location_t loc, वृक्ष निचला_मूल्य, वृक्ष ऊपरी_मूल्य, वृक्ष attrs)
{
  वृक्ष label = NULL_वृक्ष;

  यदि (निचला_मूल्य && वृक्ष_CODE (निचला_मूल्य) != INTEGER_CST)
    {
      निचला_मूल्य = c_fully_fold (निचला_मूल्य, असत्य, रिक्त);
      यदि (वृक्ष_CODE (निचला_मूल्य) == INTEGER_CST)
	pedwarn (loc, OPT_Wpedantic,
		 "case label is not an integer constant expression");
    }

  यदि (ऊपरी_मूल्य && वृक्ष_CODE (ऊपरी_मूल्य) != INTEGER_CST)
    {
      ऊपरी_मूल्य = c_fully_fold (ऊपरी_मूल्य, असत्य, रिक्त);
      यदि (वृक्ष_CODE (ऊपरी_मूल्य) == INTEGER_CST)
	pedwarn (निवेश_location, OPT_Wpedantic,
		 "case label is not an integer constant expression");
    }

  यदि (c_switch_ढेर == रिक्त)
    {
      यदि (निचला_मूल्य)
	error_at (loc, "case label not within a switch statement");
      अन्यथा
	error_at (loc, "%<default%> label not within a switch statement");
      प्रत्यागम NULL_वृक्ष;
    }

  यदि (c_check_switch_jump_warnings (c_switch_ढेर->bindings,
				    व्यंजक_LOCATION (c_switch_ढेर->switch_stmt),
				    loc))
    प्रत्यागम NULL_वृक्ष;

  label = c_add_case_label (loc, c_switch_ढेर->cases,
			    SWITCH_STMT_COND (c_switch_ढेर->switch_stmt),
			    निचला_मूल्य, ऊपरी_मूल्य, attrs);
  यदि (label == error_mark_गाँठ)
    label = NULL_वृक्ष;
  प्रत्यागम label;
}

/* Finish the switch statement.  TYPE is the original type of the
   controlling expression of the switch, or NULL_TREE.  */

शून्य
c_finish_switch (वृक्ष body, वृक्ष type)
{
  संरचना c_switch *cs = c_switch_ढेर;
  location_t switch_location;

  SWITCH_STMT_BODY (cs->switch_stmt) = body;

  /* Emit warnings as needed.  */
  switch_location = व्यंजक_LOCATION (cs->switch_stmt);
  c_do_switch_warnings (cs->cases, switch_location,
			type ? type : SWITCH_STMT_TYPE (cs->switch_stmt),
			SWITCH_STMT_COND (cs->switch_stmt), cs->bool_cond_p);
  यदि (c_switch_covers_all_cases_p (cs->cases,
				   SWITCH_STMT_TYPE (cs->switch_stmt)))
    SWITCH_STMT_ALL_CASES_P (cs->switch_stmt) = 1;
  SWITCH_STMT_NO_BREAK_P (cs->switch_stmt) = !cs->break_stmt_seen_p;

  /* Pop the stack.  */
  c_switch_ढेर = cs->next;
  splay_वृक्ष_delete (cs->cases);
  c_release_switch_bindings (cs->bindings);
  XDELETE (cs);
}

/* Emit an if statement.  IF_LOCUS is the location of the 'if'.  COND,
   THEN_BLOCK and ELSE_BLOCK are expressions to be used; ELSE_BLOCK
   may be null.  */

शून्य
c_finish_if_stmt (location_t if_locus, वृक्ष cond, वृक्ष then_block,
		  वृक्ष else_block)
{
  वृक्ष stmt;

  stmt = build3 (COND_व्यंजक, void_type_गाँठ, cond, then_block, else_block);
  SET_व्यंजक_LOCATION (stmt, if_locus);
  add_stmt (stmt);
}

वृक्ष
c_finish_bc_stmt (location_t loc, वृक्ष label, तार्किक is_break, वृक्ष name)
{
  /* In switch statements break is sometimes stylistically used after
     a return statement.  This can lead to spurious warnings about
     control reaching the end of a non-void function when it is
     inlined.  Note that we are calling block_may_fallthru with
     language specific tree nodes; this works because
     block_may_fallthru returns true when given something it does not
     understand.  */
  तार्किक skip = !block_may_fallthru (cur_stmt_list);

  यदि (is_break)
    विकल्प (in_statement & ~IN_NAMED_STMT)
      {
      पक्ष 0:
	error_at (loc, "break statement not within loop or switch");
	प्रत्यागम NULL_वृक्ष;
      पक्ष IN_OMP_BLOCK:
	error_at (loc, "invalid exit from OpenMP structured block");
	प्रत्यागम NULL_वृक्ष;
      पक्ष IN_OMP_FOR:
	error_at (loc, "break statement used with OpenMP for loop");
	प्रत्यागम NULL_वृक्ष;
      पक्ष IN_ITERATION_STMT:
      पक्ष IN_OBJC_FOREACH:
	भङ्ग;
      स्वभाव:
	gcc_assert (in_statement & IN_SWITCH_STMT);
	c_switch_ढेर->break_stmt_seen_p = सत्य;
	भङ्ग;
      }
  अन्यथा
    विकल्प (in_statement & ~(IN_SWITCH_STMT | IN_NAMED_STMT))
      {
      पक्ष 0:
	error_at (loc, "continue statement not within a loop");
	प्रत्यागम NULL_वृक्ष;
      पक्ष IN_OMP_BLOCK:
	error_at (loc, "invalid exit from OpenMP structured block");
	प्रत्यागम NULL_वृक्ष;
      पक्ष IN_ITERATION_STMT:
      पक्ष IN_OMP_FOR:
      पक्ष IN_OBJC_FOREACH:
	भङ्ग;
      स्वभाव:
	gcc_unreachable ();
      }

  यदि (skip)
    प्रत्यागम NULL_वृक्ष;
  अन्यथा यदि ((in_statement & IN_OBJC_FOREACH)
	   && !(is_break && (in_statement & IN_SWITCH_STMT))
	   && name == NULL_वृक्ष)
    {
      /* The foreach expander produces low-level code using gotos instead
	 of a structured loop construct.  */
      gcc_assert (label);
      प्रत्यागम add_stmt (build_stmt (loc, GOTO_व्यंजक, label));
    }
  अन्यथा यदि (name && C_DECL_LOOP_NAME (name) && C_DECL_SWITCH_NAME (name))
    {
      label = DECL_CHAIN (name);
      यदि (!is_break)
	label = DECL_CHAIN (label);
      /* Foreach expander from some outer level.  */
      प्रत्यागम add_stmt (build_stmt (loc, GOTO_व्यंजक, label));
    }
  प्रत्यागम add_stmt (build_stmt (loc, is_break ? BREAK_STMT : CONTINUE_STMT,
			       name));
}

/* A helper routine for c_process_expr_stmt and c_finish_stmt_expr.  */

स्थिर शून्य
emit_side_effect_warnings (location_t loc, वृक्ष व्यंजक)
{
  maybe_warn_nodiscard (loc, व्यंजक);
  यदि (!warn_unused_मूल्य)
    प्रत्यागम;
  यदि (व्यंजक == error_mark_गाँठ)
    ;
  अन्यथा यदि (!वृक्ष_SIDE_EFFECTS (व्यंजक))
    {
      यदि (!VOID_TYPE_P (वृक्ष_TYPE (व्यंजक))
	  && !warning_suppressed_p (व्यंजक, OPT_Wunused_मूल्य))
	warning_at (loc, OPT_Wunused_मूल्य, "statement with no effect");
    }
  अन्यथा यदि (वृक्ष_CODE (व्यंजक) == COMPOUND_व्यंजक)
    {
      वृक्ष r = व्यंजक;
      location_t cloc = loc;
      यावत् (वृक्ष_CODE (r) == COMPOUND_व्यंजक)
	{
	  यदि (व्यंजक_HAS_LOCATION (r))
	    cloc = व्यंजक_LOCATION (r);
	  r = वृक्ष_OPERAND (r, 1);
	}
      यदि (!वृक्ष_SIDE_EFFECTS (r)
	  && !VOID_TYPE_P (वृक्ष_TYPE (r))
	  && !CONVERT_व्यंजक_P (r)
	  && !warning_suppressed_p (r, OPT_Wunused_मूल्य)
	  && !warning_suppressed_p (व्यंजक, OPT_Wunused_मूल्य))
	warning_at (cloc, OPT_Wunused_मूल्य,
		    "right-hand operand of comma expression has no effect");
    }
  अन्यथा
    warn_if_unused_मूल्य (व्यंजक, loc);
}

/* Process an expression as if it were a complete statement.  Emit
   diagnostics, but do not call ADD_STMT.  LOC is the location of the
   statement.  */

वृक्ष
c_process_व्यंजक_stmt (location_t loc, वृक्ष व्यंजक)
{
  वृक्ष exprv;

  यदि (!व्यंजक)
    प्रत्यागम NULL_वृक्ष;

  व्यंजक = c_fully_fold (व्यंजक, असत्य, रिक्त);

  यदि (warn_sequence_point)
    verify_sequence_points (व्यंजक);

  यदि (वृक्ष_TYPE (व्यंजक) != error_mark_गाँठ
      && !COMPLETE_OR_VOID_TYPE_P (वृक्ष_TYPE (व्यंजक))
      && वृक्ष_CODE (वृक्ष_TYPE (व्यंजक)) != ARRAY_TYPE)
    error_at (loc, "expression statement has incomplete type");

  /* If we're not processing a statement expression, warn about unused values.
     Warnings for statement expressions will be emitted later, once we figure
     out which is the result.  */
  यदि (!STATEMENT_LIST_STMT_व्यंजक (cur_stmt_list)
      && (warn_unused_मूल्य || warn_unused_result))
    emit_side_effect_warnings (व्यंजक_LOC_OR_LOC (व्यंजक, loc), व्यंजक);

  exprv = व्यंजक;
  यावत् (वृक्ष_CODE (exprv) == COMPOUND_व्यंजक)
    exprv = वृक्ष_OPERAND (exprv, 1);
  यावत् (CONVERT_व्यंजक_P (exprv))
    exprv = वृक्ष_OPERAND (exprv, 0);
  यदि (DECL_P (exprv)
      || handled_component_p (exprv)
      || वृक्ष_CODE (exprv) == ADDR_व्यंजक)
    mark_exp_read (exprv);

  /* If the expression is not of a type to which we cannot assign a line
     number, wrap the thing in a no-op NOP_EXPR.  */
  यदि (DECL_P (व्यंजक) || CONSTANT_CLASS_P (व्यंजक))
    {
      व्यंजक = build1 (NOP_व्यंजक, वृक्ष_TYPE (व्यंजक), व्यंजक);
      SET_व्यंजक_LOCATION (व्यंजक, loc);
    }

  प्रत्यागम व्यंजक;
}

/* Emit an expression as a statement.  LOC is the location of the
   expression.  */

वृक्ष
c_finish_व्यंजक_stmt (location_t loc, वृक्ष व्यंजक)
{
  यदि (व्यंजक)
    प्रत्यागम add_stmt (c_process_व्यंजक_stmt (loc, व्यंजक));
  अन्यथा
    प्रत्यागम रिक्त;
}

/* Do the opposite and emit a statement as an expression.  To begin,
   create a new binding level and return it.  */

वृक्ष
c_begin_stmt_व्यंजक (शून्य)
{
  वृक्ष ret;

  /* We must force a BLOCK for this level so that, if it is not expanded
     later, there is a way to turn off the entire subtree of blocks that
     are contained in it.  */
  keep_next_level ();
  ret = c_begin_compound_stmt (सत्य);

  c_bindings_start_stmt_व्यंजक (c_switch_ढेर == रिक्त
			      ? रिक्त
			      : c_switch_ढेर->bindings);

  /* Mark the current statement list as belonging to a statement list.  */
  STATEMENT_LIST_STMT_व्यंजक (ret) = 1;

  प्रत्यागम ret;
}

/* LOC is the location of the compound statement to which this body
   belongs.  */

वृक्ष
c_finish_stmt_व्यंजक (location_t loc, वृक्ष body)
{
  वृक्ष last, type, tmp, val;
  वृक्ष *last_p;

  body = c_end_compound_stmt (loc, body, सत्य);

  c_bindings_end_stmt_व्यंजक (c_switch_ढेर == रिक्त
			    ? रिक्त
			    : c_switch_ढेर->bindings);

  /* Locate the last statement in BODY.  See c_end_compound_stmt
     about always returning a BIND_EXPR.  */
  last_p = &BIND_व्यंजक_BODY (body);
  last = BIND_व्यंजक_BODY (body);

 continue_searching:
  यदि (वृक्ष_CODE (last) == STATEMENT_LIST)
    {
      वृक्ष_stmt_iterator l = tsi_last (last);

      यावत् (!tsi_end_p (l) && वृक्ष_CODE (tsi_stmt (l)) == DEBUG_BEGIN_STMT)
	tsi_prev (&l);

      /* This can happen with degenerate cases like ({ }).  No value.  */
      यदि (tsi_end_p (l))
	प्रत्यागम body;

      /* If we're supposed to generate side effects warnings, process
	 all of the statements except the last.  */
      यदि (warn_unused_मूल्य || warn_unused_result)
	{
	  प्रति (वृक्ष_stmt_iterator i = tsi_start (last);
	       tsi_stmt (i) != tsi_stmt (l); tsi_next (&i))
	    {
	      location_t tloc;
	      वृक्ष t = tsi_stmt (i);

	      tloc = व्यंजक_HAS_LOCATION (t) ? व्यंजक_LOCATION (t) : loc;
	      emit_side_effect_warnings (tloc, t);
	    }
	}
      last_p = tsi_stmt_ptr (l);
      last = *last_p;
    }

  /* If the end of the list is exception related, then the list was split
     by a call to push_cleanup.  Continue searching.  */
  यदि (वृक्ष_CODE (last) == TRY_FINALLY_व्यंजक
      || वृक्ष_CODE (last) == TRY_CATCH_व्यंजक)
    {
      last_p = &वृक्ष_OPERAND (last, 0);
      last = *last_p;
      गच्छ continue_searching;
    }

  यदि (last == error_mark_गाँठ)
    प्रत्यागम last;

  /* In the case that the BIND_EXPR is not necessary, return the
     expression out from inside it.  */
  यदि ((last == BIND_व्यंजक_BODY (body)
       /* Skip nested debug stmts.  */
       || last == व्यंजक_first (BIND_व्यंजक_BODY (body)))
      && BIND_व्यंजक_VARS (body) == रिक्त)
    {
      /* Even if this looks constant, do not allow it in a constant
	 expression.  */
      last = c_wrap_maybe_const (last, सत्य);
      /* Do not warn if the return value of a statement expression is
	 unused.  */
      suppress_warning (last, OPT_Wunused);
      प्रत्यागम last;
    }

  /* Extract the type of said expression.  */
  type = वृक्ष_TYPE (last);

  /* If we're not returning a value at all, then the BIND_EXPR that
     we already have is a fine expression to return.  */
  यदि (!type || VOID_TYPE_P (type))
    प्रत्यागम body;

  /* Now that we've located the expression containing the value, it seems
     silly to make voidify_wrapper_expr repeat the process.  Create a
     temporary of the appropriate type and stick it in a TARGET_EXPR.  */
  tmp = create_tmp_var_raw (type);

  /* Unwrap a no-op NOP_EXPR as added by c_finish_expr_stmt.  This avoids
     tree_expr_nonnegative_p giving up immediately.  */
  val = last;
  यदि (वृक्ष_CODE (val) == NOP_व्यंजक
      && वृक्ष_TYPE (val) == वृक्ष_TYPE (वृक्ष_OPERAND (val, 0)))
    val = वृक्ष_OPERAND (val, 0);

  *last_p = build2 (MODIFY_व्यंजक, void_type_गाँठ, tmp, val);
  SET_व्यंजक_LOCATION (*last_p, व्यंजक_LOCATION (last));

  {
    वृक्ष t = build4 (TARGET_व्यंजक, type, tmp, body, NULL_वृक्ष, NULL_वृक्ष);
    SET_व्यंजक_LOCATION (t, loc);
    प्रत्यागम t;
  }
}

/* Begin and end compound statements.  This is as simple as pushing
   and popping new statement lists from the tree.  */

वृक्ष
c_begin_compound_stmt (तार्किक do_scope)
{
  वृक्ष stmt = धकेलो_stmt_list ();
  यदि (do_scope)
    धकेलो_scope ();
  प्रत्यागम stmt;
}

/* End a compound statement.  STMT is the statement.  LOC is the
   location of the compound statement-- this is usually the location
   of the opening brace.  */

वृक्ष
c_end_compound_stmt (location_t loc, वृक्ष stmt, तार्किक do_scope)
{
  वृक्ष block = रिक्त;

  यदि (do_scope)
    {
      यदि (c_dialect_objc ())
	objc_clear_super_receiver ();
      block = निकालो_scope ();
    }

  stmt = निकालो_stmt_list (stmt);
  stmt = c_build_bind_व्यंजक (loc, block, stmt);

  /* If this compound statement is nested immediately inside a statement
     expression, then force a BIND_EXPR to be created.  Otherwise we'll
     do the wrong thing for ({ { 1; } }) or ({ 1; { } }).  In particular,
     STATEMENT_LISTs merge, and thus we can lose track of what statement
     was really last.  */
  यदि (building_stmt_list_p ()
      && STATEMENT_LIST_STMT_व्यंजक (cur_stmt_list)
      && वृक्ष_CODE (stmt) != BIND_व्यंजक)
    {
      stmt = build3 (BIND_व्यंजक, void_type_गाँठ, रिक्त, stmt, रिक्त);
      वृक्ष_SIDE_EFFECTS (stmt) = 1;
      SET_व्यंजक_LOCATION (stmt, loc);
    }

  प्रत्यागम stmt;
}

/* Queue a cleanup.  CLEANUP is an expression/statement to be executed
   when the current scope is exited.  EH_ONLY is true when this is not
   meant to apply to normal control flow transfer.  */

शून्य
धकेलो_cleanup (वृक्ष decl, वृक्ष cleanup, तार्किक eh_only)
{
  गणना वृक्ष_code code;
  वृक्ष stmt, list;
  तार्किक stmt_व्यंजक;

  code = eh_only ? TRY_CATCH_व्यंजक : TRY_FINALLY_व्यंजक;
  stmt = build_stmt (DECL_SOURCE_LOCATION (decl), code, रिक्त, cleanup);
  add_stmt (stmt);
  stmt_व्यंजक = STATEMENT_LIST_STMT_व्यंजक (cur_stmt_list);
  list = धकेलो_stmt_list ();
  वृक्ष_OPERAND (stmt, 0) = list;
  STATEMENT_LIST_STMT_व्यंजक (list) = stmt_व्यंजक;
}

/* Build a vector comparison of ARG0 and ARG1 using CODE opcode
   into a value of TYPE type.  Comparison is done via VEC_COND_EXPR.  */

स्थिर वृक्ष
build_vec_cmp (वृक्ष_code code, वृक्ष type,
	       वृक्ष arg0, वृक्ष arg1)
{
  वृक्ष zero_vec = build_zero_cst (type);
  वृक्ष minus_one_vec = build_minus_one_cst (type);
  वृक्ष cmp_type = truth_type_for (वृक्ष_TYPE (arg0));
  वृक्ष cmp = build2 (code, cmp_type, arg0, arg1);
  प्रत्यागम build3 (VEC_COND_व्यंजक, type, cmp, minus_one_vec, zero_vec);
}

/* Possibly warn about an address of OP never being NULL in a comparison
   operation CODE involving null.  */

स्थिर शून्य
maybe_warn_for_null_address (location_t loc, वृक्ष op, वृक्ष_code code)
{
  /* Prevent warnings issued for macro expansion.  */
  यदि (!warn_address
      || warning_suppressed_p (op, OPT_Waddress)
      || from_macro_expansion_at (loc))
    प्रत्यागम;

  यदि (वृक्ष_CODE (op) == NOP_व्यंजक)
    {
      /* Allow casts to intptr_t to suppress the warning.  */
      वृक्ष type = वृक्ष_TYPE (op);
      यदि (वृक्ष_CODE (type) == INTEGER_TYPE)
	प्रत्यागम;
      op = वृक्ष_OPERAND (op, 0);
    }

  यदि (वृक्ष_CODE (op) == POINTER_PLUS_व्यंजक)
    {
      /* Allow a cast to void* to suppress the warning.  */
      वृक्ष type = वृक्ष_TYPE (वृक्ष_TYPE (op));
      यदि (VOID_TYPE_P (type))
	प्रत्यागम;

      /* Adding any value to a null pointer, including zero, is undefined
	 in C.  This includes the expression &p[0] where p is the null
	 pointer, although &p[0] will have been folded to p by this point
	 and so not diagnosed.  */
      यदि (code == EQ_व्यंजक)
	warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<false%> "
		    "for the pointer operand in %qE must not be NULL",
		    op);
      अन्यथा
	warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<true%> "
		    "for the pointer operand in %qE must not be NULL",
		    op);

      प्रत्यागम;
    }

  यदि (वृक्ष_CODE (op) != ADDR_व्यंजक)
    प्रत्यागम;

  op = वृक्ष_OPERAND (op, 0);

  यदि (वृक्ष_CODE (op) == IMAGPART_व्यंजक
      || वृक्ष_CODE (op) == REALPART_व्यंजक)
    {
      /* The address of either complex part may not be null.  */
      यदि (code == EQ_व्यंजक)
	warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<false%> "
		    "for the address of %qE will never be NULL",
		    op);
      अन्यथा
	warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<true%> "
		    "for the address of %qE will never be NULL",
		    op);
      प्रत्यागम;
    }

  /* Set to true in the loop below if OP dereferences is operand.
     In such a case the ultimate target need not be a decl for
     the null [in]equality test to be constant.  */
  तार्किक deref = असत्य;

  /* Get the outermost array or object, or member.  */
  यावत् (handled_component_p (op))
    {
      यदि (वृक्ष_CODE (op) == COMPONENT_REF)
	{
	  /* Get the member (its address is never null).  */
	  op = वृक्ष_OPERAND (op, 1);
	  भङ्ग;
	}

      /* Get the outer array/object to refer to in the warning.  */
      op = वृक्ष_OPERAND (op, 0);
      deref = सत्य;
    }

  यदि ((!deref && !decl_with_nonnull_addr_p (op))
      || from_macro_expansion_at (loc))
    प्रत्यागम;

  तार्किक w;
  यदि (code == EQ_व्यंजक)
    w = warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<false%> "
		    "for the address of %qE will never be NULL",
		    op);
  अन्यथा
    w = warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<true%> "
		    "for the address of %qE will never be NULL",
		    op);

  यदि (w && DECL_P (op))
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

वृक्ष
build_द्विआधारी_op (location_t location, गणना वृक्ष_code code,
		 वृक्ष orig_op0, वृक्ष orig_op1, तार्किक convert_p)
{
  वृक्ष type0, type1, orig_type0, orig_type1;
  वृक्ष eptype;
  गणना वृक्ष_code code0, code1;
  वृक्ष op0, op1;
  वृक्ष ret = error_mark_गाँठ;
  ध्रुव वर्ण *invalid_op_diag;
  तार्किक op0_int_operands, op1_int_operands;
  तार्किक int_const, int_const_or_overflow, int_operands;

  /* Expression code to give to the expression when it is built.
     Normally this is CODE, which is what the caller asked for,
     but in some special cases we change it.  */
  गणना वृक्ष_code resultcode = code;

  /* Data type in which the computation is to be performed.
     In the simplest cases this is the common type of the arguments.  */
  वृक्ष result_type = रिक्त;

  /* When the computation is in excess precision, the type of the
     final EXCESS_PRECISION_EXPR.  */
  वृक्ष semantic_result_type = रिक्त;

  /* Nonzero means operands have already been type-converted
     in whatever way is necessary.
     Zero means they need to be converted to RESULT_TYPE.  */
  पूर्णाङ्क converted = 0;

  /* Nonzero means create the expression with this type, rather than
     RESULT_TYPE.  */
  वृक्ष build_type = NULL_वृक्ष;

  /* Nonzero means after finally constructing the expression
     convert it to this type.  */
  वृक्ष final_type = NULL_वृक्ष;

  /* Nonzero if this is an operation like MIN or MAX which can
     safely be computed in short if both args are promoted shorts.
     Also implies COMMON.
     -1 indicates a bitwise operation; this makes a difference
     in the exact conditions for when it is safe to do the operation
     in a narrower mode.  */
  पूर्णाङ्क shorten = 0;

  /* Nonzero if this is a comparison operation;
     if both args are promoted shorts, compare the original shorts.
     Also implies COMMON.  */
  पूर्णाङ्क short_compare = 0;

  /* Nonzero if this is a right-shift operation, which can be computed on the
     original short and then promoted if the operand is a promoted short.  */
  पूर्णाङ्क short_shift = 0;

  /* Nonzero means set RESULT_TYPE to the common type of the args.  */
  पूर्णाङ्क common = 0;

  /* True means types are compatible as far as ObjC is concerned.  */
  तार्किक objc_ok;

  /* True means this is an arithmetic operation that may need excess
     precision.  */
  तार्किक may_need_excess_precision;

  /* True means this is a boolean operation that converts both its
     operands to truth-values.  */
  तार्किक boolean_op = असत्य;

  /* Remember whether we're doing / or %.  */
  तार्किक doing_div_or_mod = असत्य;

  /* Remember whether we're doing << or >>.  */
  तार्किक doing_shift = असत्य;

  /* Tree holding instrumentation expression.  */
  वृक्ष instrument_व्यंजक = रिक्त;

  यदि (location == UNKNOWN_LOCATION)
    location = निवेश_location;

  op0 = orig_op0;
  op1 = orig_op1;

  op0_int_operands = व्यंजक_INT_CONST_OPERANDS (orig_op0);
  यदि (op0_int_operands)
    op0 = remove_c_maybe_const_व्यंजक (op0);
  op1_int_operands = व्यंजक_INT_CONST_OPERANDS (orig_op1);
  यदि (op1_int_operands)
    op1 = remove_c_maybe_const_व्यंजक (op1);
  int_operands = (op0_int_operands && op1_int_operands);
  यदि (int_operands)
    {
      int_const_or_overflow = (वृक्ष_CODE (orig_op0) == INTEGER_CST
			       && वृक्ष_CODE (orig_op1) == INTEGER_CST);
      int_const = (int_const_or_overflow
		   && !वृक्ष_OVERFLOW (orig_op0)
		   && !वृक्ष_OVERFLOW (orig_op1));
    }
  अन्यथा
    int_const = int_const_or_overflow = असत्य;

  /* Do not apply default conversion in mixed vector/scalar expression.  */
  यदि (convert_p
      && VECTOR_TYPE_P (वृक्ष_TYPE (op0)) == VECTOR_TYPE_P (वृक्ष_TYPE (op1)))
    {
      op0 = default_conversion (op0);
      op1 = default_conversion (op1);
    }

  orig_type0 = type0 = वृक्ष_TYPE (op0);

  orig_type1 = type1 = वृक्ष_TYPE (op1);

  /* The expression codes of the data types of the arguments tell us
     whether the arguments are integers, floating, pointers, etc.  */
  code0 = वृक्ष_CODE (type0);
  code1 = वृक्ष_CODE (type1);

  /* Strip NON_LVALUE_EXPRs, etc., since we aren't using as an lvalue.  */
  STRIP_TYPE_NOPS (op0);
  STRIP_TYPE_NOPS (op1);

  /* If an error was already reported for one of the arguments,
     avoid reporting another error.  */

  यदि (code0 == ERROR_MARK || code1 == ERROR_MARK)
    प्रत्यागम error_mark_गाँठ;

  यदि (code0 == POINTER_TYPE
      && reject_gcc_builtin (op0, व्यंजक_LOCATION (orig_op0)))
    प्रत्यागम error_mark_गाँठ;

  यदि (code1 == POINTER_TYPE
      && reject_gcc_builtin (op1, व्यंजक_LOCATION (orig_op1)))
    प्रत्यागम error_mark_गाँठ;

  यदि ((invalid_op_diag
       = targetm.invalid_द्विआधारी_op (code, type0, type1)))
    {
      error_at (location, invalid_op_diag);
      प्रत्यागम error_mark_गाँठ;
    }

  विकल्प (code)
    {
    पक्ष PLUS_व्यंजक:
    पक्ष MINUS_व्यंजक:
    पक्ष MULT_व्यंजक:
    पक्ष TRUNC_DIV_व्यंजक:
    पक्ष CEIL_DIV_व्यंजक:
    पक्ष FLOOR_DIV_व्यंजक:
    पक्ष ROUND_DIV_व्यंजक:
    पक्ष EXACT_DIV_व्यंजक:
      may_need_excess_precision = सत्य;
      भङ्ग;

    पक्ष EQ_व्यंजक:
    पक्ष NE_व्यंजक:
    पक्ष LE_व्यंजक:
    पक्ष GE_व्यंजक:
    पक्ष LT_व्यंजक:
    पक्ष GT_व्यंजक:
      /* Excess precision for implicit conversions of integers to
	 floating point in C11 and later.  */
      may_need_excess_precision = (flag_isoc11
				   && (ANY_INTEGRAL_TYPE_P (type0)
				       || ANY_INTEGRAL_TYPE_P (type1)));
      भङ्ग;

    स्वभाव:
      may_need_excess_precision = असत्य;
      भङ्ग;
    }
  यदि (वृक्ष_CODE (op0) == EXCESS_PRECISION_व्यंजक)
    {
      op0 = वृक्ष_OPERAND (op0, 0);
      type0 = वृक्ष_TYPE (op0);
    }
  अन्यथा यदि (may_need_excess_precision
	   && (eptype = excess_precision_type (type0)) != NULL_वृक्ष)
    {
      type0 = eptype;
      op0 = convert (eptype, op0);
    }
  यदि (वृक्ष_CODE (op1) == EXCESS_PRECISION_व्यंजक)
    {
      op1 = वृक्ष_OPERAND (op1, 0);
      type1 = वृक्ष_TYPE (op1);
    }
  अन्यथा यदि (may_need_excess_precision
	   && (eptype = excess_precision_type (type1)) != NULL_वृक्ष)
    {
      type1 = eptype;
      op1 = convert (eptype, op1);
    }

  objc_ok = objc_compare_types (type0, type1, -3, NULL_वृक्ष);

  /* In case when one of the operands of the binary operation is
     a vector and another is a scalar -- convert scalar to vector.  */
  यदि ((gnu_vector_type_p (type0) && code1 != VECTOR_TYPE)
      || (gnu_vector_type_p (type1) && code0 != VECTOR_TYPE))
    {
      गणना stv_conv convert_flag = scalar_to_vector (location, code, orig_op0,
						     orig_op1, सत्य);

      विकल्प (convert_flag)
	{
	  पक्ष stv_error:
	    प्रत्यागम error_mark_गाँठ;
	  पक्ष stv_firstarg:
	    {
              तार्किक maybe_const = सत्य;
              वृक्ष sc;
              sc = c_fully_fold (op0, असत्य, &maybe_const);
              sc = save_व्यंजक (sc);
              sc = convert (वृक्ष_TYPE (type1), sc);
              op0 = build_vector_from_val (type1, sc);
              यदि (!maybe_const)
                op0 = c_wrap_maybe_const (op0, सत्य);
              orig_type0 = type0 = वृक्ष_TYPE (op0);
              code0 = वृक्ष_CODE (type0);
              converted = 1;
              भङ्ग;
	    }
	  पक्ष stv_secondarg:
	    {
	      तार्किक maybe_const = सत्य;
	      वृक्ष sc;
	      sc = c_fully_fold (op1, असत्य, &maybe_const);
	      sc = save_व्यंजक (sc);
	      sc = convert (वृक्ष_TYPE (type0), sc);
	      op1 = build_vector_from_val (type0, sc);
	      यदि (!maybe_const)
		op1 = c_wrap_maybe_const (op1, सत्य);
	      orig_type1 = type1 = वृक्ष_TYPE (op1);
	      code1 = वृक्ष_CODE (type1);
	      converted = 1;
	      भङ्ग;
	    }
	  स्वभाव:
	    भङ्ग;
	}
    }

  विकल्प (code)
    {
    पक्ष PLUS_व्यंजक:
      /* Handle the pointer + int case.  */
      यदि (code0 == POINTER_TYPE
	  && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  ret = pointer_int_sum (location, PLUS_व्यंजक, op0, op1);
	  गच्छ return_build_द्विआधारी_op;
	}
      अन्यथा यदि (code1 == POINTER_TYPE
	       && (code0 == INTEGER_TYPE || code0 == BITINT_TYPE))
	{
	  ret = pointer_int_sum (location, PLUS_व्यंजक, op1, op0);
	  गच्छ return_build_द्विआधारी_op;
	}
      अन्यथा
	common = 1;
      भङ्ग;

    पक्ष MINUS_व्यंजक:
      /* Subtraction of two similar pointers.
	 We must subtract them as integers, then divide by object size.  */
      यदि (code0 == POINTER_TYPE && code1 == POINTER_TYPE
	  && comp_target_types (location, type0, type1))
	{
	  ret = pointer_diff (location, op0, op1, &instrument_व्यंजक);
	  गच्छ return_build_द्विआधारी_op;
	}
      /* Handle pointer minus int.  Just like pointer plus int.  */
      अन्यथा यदि (code0 == POINTER_TYPE
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  ret = pointer_int_sum (location, MINUS_व्यंजक, op0, op1);
	  गच्छ return_build_द्विआधारी_op;
	}
      अन्यथा
	common = 1;
      भङ्ग;

    पक्ष MULT_व्यंजक:
      common = 1;
      भङ्ग;

    पक्ष TRUNC_DIV_व्यंजक:
    पक्ष CEIL_DIV_व्यंजक:
    पक्ष FLOOR_DIV_व्यंजक:
    पक्ष ROUND_DIV_व्यंजक:
    पक्ष EXACT_DIV_व्यंजक:
      doing_div_or_mod = सत्य;
      warn_for_div_by_zero (location, op1);

      यदि ((code0 == INTEGER_TYPE || code0 == REAL_TYPE
	   || code0 == FIXED_POINT_TYPE || code0 == BITINT_TYPE
	   || code0 == COMPLEX_TYPE
	   || gnu_vector_type_p (type0))
	  && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	      || code1 == FIXED_POINT_TYPE || code1 == BITINT_TYPE
	      || code1 == COMPLEX_TYPE
	      || gnu_vector_type_p (type1)))
	{
	  गणना वृक्ष_code tcode0 = code0, tcode1 = code1;

	  यदि (code0 == COMPLEX_TYPE || code0 == VECTOR_TYPE)
	    tcode0 = वृक्ष_CODE (वृक्ष_TYPE (वृक्ष_TYPE (op0)));
	  यदि (code1 == COMPLEX_TYPE || code1 == VECTOR_TYPE)
	    tcode1 = वृक्ष_CODE (वृक्ष_TYPE (वृक्ष_TYPE (op1)));

	  यदि (!(((tcode0 == INTEGER_TYPE || tcode0 == BITINT_TYPE
		  || (tcode0 == ENUMERAL_TYPE && code0 == VECTOR_TYPE))
		 && (tcode1 == INTEGER_TYPE || tcode1 == BITINT_TYPE
		     || (tcode1 == ENUMERAL_TYPE && code1 == VECTOR_TYPE)))
		|| (tcode0 == FIXED_POINT_TYPE && tcode1 == FIXED_POINT_TYPE)))
	    resultcode = RDIV_व्यंजक;
	  अन्यथा
	    /* Although it would be tempting to shorten always here, that
	       loses on some targets, since the modulo instruction is
	       undefined if the quotient can't be represented in the
	       computation mode.  We shorten only if unsigned or if
	       dividing by something we know != -1.  */
	    shorten = may_shorten_divmod (op0, op1);
	  common = 1;
	}
      भङ्ग;

    पक्ष BIT_AND_व्यंजक:
    पक्ष BIT_IOR_व्यंजक:
    पक्ष BIT_XOR_व्यंजक:
      यदि ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	shorten = -1;
      /* Allow vector types which are not floating point types.   */
      अन्यथा यदि (gnu_vector_type_p (type0)
	       && gnu_vector_type_p (type1)
	       && !VECTOR_FLOAT_TYPE_P (type0)
	       && !VECTOR_FLOAT_TYPE_P (type1))
	common = 1;
      भङ्ग;

    पक्ष TRUNC_MOD_व्यंजक:
    पक्ष FLOOR_MOD_व्यंजक:
      doing_div_or_mod = सत्य;
      warn_for_div_by_zero (location, op1);

      यदि (gnu_vector_type_p (type0)
	  && gnu_vector_type_p (type1)
	  && वृक्ष_CODE (वृक्ष_TYPE (type0)) == INTEGER_TYPE
	  && वृक्ष_CODE (वृक्ष_TYPE (type1)) == INTEGER_TYPE)
	common = 1;
      अन्यथा यदि ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  /* Although it would be tempting to shorten always here, that loses
	     on some targets, since the modulo instruction is undefined if the
	     quotient can't be represented in the computation mode.  We shorten
	     only if unsigned or if dividing by something we know != -1.  */
	  shorten = may_shorten_divmod (op0, op1);
	  common = 1;
	}
      भङ्ग;

    पक्ष TRUTH_ANDIF_व्यंजक:
    पक्ष TRUTH_ORIF_व्यंजक:
    पक्ष TRUTH_AND_व्यंजक:
    पक्ष TRUTH_OR_व्यंजक:
    पक्ष TRUTH_XOR_व्यंजक:
      यदि ((code0 == INTEGER_TYPE || code0 == POINTER_TYPE
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
	  result_type = integer_type_गाँठ;
	  यदि (op0_int_operands)
	    {
	      op0 = c_objc_common_truthvalue_conversion (location, orig_op0);
	      op0 = remove_c_maybe_const_व्यंजक (op0);
	    }
	  अन्यथा
	    op0 = c_objc_common_truthvalue_conversion (location, op0);
	  यदि (op1_int_operands)
	    {
	      op1 = c_objc_common_truthvalue_conversion (location, orig_op1);
	      op1 = remove_c_maybe_const_व्यंजक (op1);
	    }
	  अन्यथा
	    op1 = c_objc_common_truthvalue_conversion (location, op1);
	  converted = 1;
	  boolean_op = सत्य;
	}
      यदि (code == TRUTH_ANDIF_व्यंजक)
	{
	  int_const_or_overflow = (int_operands
				   && वृक्ष_CODE (orig_op0) == INTEGER_CST
				   && (op0 == truthvalue_false_गाँठ
				       || वृक्ष_CODE (orig_op1) == INTEGER_CST));
	  int_const = (int_const_or_overflow
		       && !वृक्ष_OVERFLOW (orig_op0)
		       && (op0 == truthvalue_false_गाँठ
			   || !वृक्ष_OVERFLOW (orig_op1)));
	}
      अन्यथा यदि (code == TRUTH_ORIF_व्यंजक)
	{
	  int_const_or_overflow = (int_operands
				   && वृक्ष_CODE (orig_op0) == INTEGER_CST
				   && (op0 == truthvalue_true_गाँठ
				       || वृक्ष_CODE (orig_op1) == INTEGER_CST));
	  int_const = (int_const_or_overflow
		       && !वृक्ष_OVERFLOW (orig_op0)
		       && (op0 == truthvalue_true_गाँठ
			   || !वृक्ष_OVERFLOW (orig_op1)));
	}
      भङ्ग;

      /* Shift operations: result has same type as first operand;
	 always convert second operand to int.
	 Also set SHORT_SHIFT if shifting rightward.  */

    पक्ष RSHIFT_व्यंजक:
      यदि (gnu_vector_type_p (type0)
	  && gnu_vector_type_p (type1)
	  && वृक्ष_CODE (वृक्ष_TYPE (type0)) == INTEGER_TYPE
	  && वृक्ष_CODE (वृक्ष_TYPE (type1)) == INTEGER_TYPE
	  && known_eq (TYPE_VECTOR_SUBPARTS (type0),
		       TYPE_VECTOR_SUBPARTS (type1)))
	{
	  result_type = type0;
	  converted = 1;
	}
      अन्यथा यदि ((code0 == INTEGER_TYPE || code0 == FIXED_POINT_TYPE
		|| code0 == BITINT_TYPE
		|| (gnu_vector_type_p (type0)
		    && वृक्ष_CODE (वृक्ष_TYPE (type0)) == INTEGER_TYPE))
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  doing_shift = सत्य;
	  यदि (वृक्ष_CODE (op1) == INTEGER_CST)
	    {
	      यदि (वृक्ष_int_cst_sgn (op1) < 0)
		{
		  int_const = असत्य;
		  यदि (c_inhibit_evaluation_warnings == 0)
		    warning_at (location, OPT_Wshift_गिनती_negative,
				"right shift count is negative");
		}
	      अन्यथा यदि (code0 == VECTOR_TYPE)
		{
		  यदि (compare_वृक्ष_int (op1,
					TYPE_PRECISION (वृक्ष_TYPE (type0)))
		      >= 0)
		    {
		      int_const = असत्य;
		      यदि (c_inhibit_evaluation_warnings == 0)
			warning_at (location, OPT_Wshift_गिनती_overflow,
				    "right shift count >= width of vector element");
		    }
		}
	      अन्यथा
		{
		  यदि (!integer_zerop (op1))
		    short_shift = 1;

		  यदि (compare_वृक्ष_int (op1, TYPE_PRECISION (type0)) >= 0)
		    {
		      int_const = असत्य;
		      यदि (c_inhibit_evaluation_warnings == 0)
			warning_at (location, OPT_Wshift_गिनती_overflow,
				    "right shift count >= width of type");
		    }
		}
	    }

	  /* Use the type of the value to be shifted.  */
	  result_type = type0;
	  /* Avoid converting op1 to result_type later.  */
	  converted = 1;
	}
      भङ्ग;

    पक्ष LSHIFT_व्यंजक:
      यदि (gnu_vector_type_p (type0)
	  && gnu_vector_type_p (type1)
	  && वृक्ष_CODE (वृक्ष_TYPE (type0)) == INTEGER_TYPE
	  && वृक्ष_CODE (वृक्ष_TYPE (type1)) == INTEGER_TYPE
	  && known_eq (TYPE_VECTOR_SUBPARTS (type0),
		       TYPE_VECTOR_SUBPARTS (type1)))
	{
	  result_type = type0;
	  converted = 1;
	}
      अन्यथा यदि ((code0 == INTEGER_TYPE || code0 == FIXED_POINT_TYPE
		|| code0 == BITINT_TYPE
		|| (gnu_vector_type_p (type0)
		    && वृक्ष_CODE (वृक्ष_TYPE (type0)) == INTEGER_TYPE))
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  doing_shift = सत्य;
	  यदि (वृक्ष_CODE (op0) == INTEGER_CST
	      && वृक्ष_int_cst_sgn (op0) < 0
	      && !TYPE_OVERFLOW_WRAPS (type0))
	    {
	      /* Don't reject a left shift of a negative value in a context
		 where a constant expression is needed in C90.  */
	      यदि (flag_isoc99)
		int_const = असत्य;
	      यदि (c_inhibit_evaluation_warnings == 0)
		warning_at (location, OPT_Wshift_negative_मूल्य,
			    "left shift of negative value");
	    }
	  यदि (वृक्ष_CODE (op1) == INTEGER_CST)
	    {
	      यदि (वृक्ष_int_cst_sgn (op1) < 0)
		{
		  int_const = असत्य;
		  यदि (c_inhibit_evaluation_warnings == 0)
		    warning_at (location, OPT_Wshift_गिनती_negative,
				"left shift count is negative");
		}
	      अन्यथा यदि (code0 == VECTOR_TYPE)
		{
		  यदि (compare_वृक्ष_int (op1,
					TYPE_PRECISION (वृक्ष_TYPE (type0)))
		      >= 0)
		    {
		      int_const = असत्य;
		      यदि (c_inhibit_evaluation_warnings == 0)
			warning_at (location, OPT_Wshift_गिनती_overflow,
				    "left shift count >= width of vector element");
		    }
		}
	      अन्यथा यदि (compare_वृक्ष_int (op1, TYPE_PRECISION (type0)) >= 0)
		{
		  int_const = असत्य;
		  यदि (c_inhibit_evaluation_warnings == 0)
		    warning_at (location, OPT_Wshift_गिनती_overflow,
				"left shift count >= width of type");
		}
	      अन्यथा यदि (वृक्ष_CODE (op0) == INTEGER_CST
		       && maybe_warn_shift_overflow (location, op0, op1)
		       && flag_isoc99)
		int_const = असत्य;
	    }

	  /* Use the type of the value to be shifted.  */
	  result_type = type0;
	  /* Avoid converting op1 to result_type later.  */
	  converted = 1;
	}
      भङ्ग;

    पक्ष EQ_व्यंजक:
    पक्ष NE_व्यंजक:
      यदि (gnu_vector_type_p (type0) && gnu_vector_type_p (type1))
        {
          वृक्ष intt;
	  यदि (!vector_types_compatible_elements_p (type0, type1))
            {
              error_at (location, "comparing vectors with different "
                                  "element types");
              प्रत्यागम error_mark_गाँठ;
            }

	  यदि (maybe_ne (TYPE_VECTOR_SUBPARTS (type0),
			TYPE_VECTOR_SUBPARTS (type1)))
            {
              error_at (location, "comparing vectors with different "
                                  "number of elements");
              प्रत्यागम error_mark_गाँठ;
            }

	  /* It's not precisely specified how the usual arithmetic
	     conversions apply to the vector types.  Here, we use
	     the unsigned type if one of the operands is signed and
	     the other one is unsigned.  */
	  यदि (TYPE_UNSIGNED (type0) != TYPE_UNSIGNED (type1))
	    {
	      यदि (!TYPE_UNSIGNED (type0))
		op0 = build1 (VIEW_CONVERT_व्यंजक, type1, op0);
	      अन्यथा
		op1 = build1 (VIEW_CONVERT_व्यंजक, type0, op1);
	      warning_at (location, OPT_Wsign_compare, "comparison between "
			  "types %qT and %qT", type0, type1);
	    }

          /* Always construct signed integer vector type.  */
	  यदि (VECTOR_BOOLEAN_TYPE_P (type0) && VECTOR_BOOLEAN_TYPE_P (type1))
	    result_type = type0;
	  अन्यथा
	    {
	      स्वतः nelts = TYPE_VECTOR_SUBPARTS (type0);

	      intt = c_common_type_for_size (GET_MODE_BITSIZE
					     (SCALAR_TYPE_MODE
						(वृक्ष_TYPE (type0))), 0);
	      यदि (!intt)
		{
		  error_at (location, "could not find an integer type "
				      "of the same size as %qT",
			    वृक्ष_TYPE (type0));
		  प्रत्यागम error_mark_गाँठ;
		}
	      result_type = build_opaque_vector_type (intt, nelts);
	    }
          converted = 1;
	  ret = build_vec_cmp (resultcode, result_type, op0, op1);
	  गच्छ return_build_द्विआधारी_op;
        }
      यदि (FLOAT_TYPE_P (type0) || FLOAT_TYPE_P (type1))
	warning_at (location,
		    OPT_Wfloat_equal,
		    "comparing floating-point with %<==%> or %<!=%> is unsafe");
      /* Result of comparison is always int,
	 but don't convert the args to int!  */
      build_type = integer_type_गाँठ;
      यदि ((code0 == INTEGER_TYPE || code0 == REAL_TYPE || code0 == BITINT_TYPE
	   || code0 == FIXED_POINT_TYPE || code0 == COMPLEX_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	      || code1 == BITINT_TYPE
	      || code1 == FIXED_POINT_TYPE || code1 == COMPLEX_TYPE))
	short_compare = 1;
      अन्यथा यदि (code0 == POINTER_TYPE
	       && (code1 == NULLPTR_TYPE
		   || null_pointer_constant_p (orig_op1)))
	{
	  maybe_warn_for_null_address (location, op0, code);
	  result_type = type0;
	}
      अन्यथा यदि (code1 == POINTER_TYPE
	       && (code0 == NULLPTR_TYPE
		   || null_pointer_constant_p (orig_op0)))
	{
	  maybe_warn_for_null_address (location, op1, code);
	  result_type = type1;
	}
      अन्यथा यदि (code0 == POINTER_TYPE && code1 == POINTER_TYPE)
	{
	  वृक्ष tt0 = वृक्ष_TYPE (type0);
	  वृक्ष tt1 = वृक्ष_TYPE (type1);
	  addr_space_t as0 = TYPE_ADDR_SPACE (tt0);
	  addr_space_t as1 = TYPE_ADDR_SPACE (tt1);
	  addr_space_t as_common = ADDR_SPACE_GENERIC;

	  /* Anything compares with void *.  void * compares with anything.
	     Otherwise, the targets must be compatible
	     and both must be object or both incomplete.  */
	  यदि (comp_target_types (location, type0, type1))
	    result_type = common_pointer_type (type0, type1, NULL_वृक्ष);
	  अन्यथा यदि (!addr_space_superset (as0, as1, &as_common))
	    {
	      error_at (location, "comparison of pointers to "
			"disjoint address spaces");
	      प्रत्यागम error_mark_गाँठ;
	    }
	  अन्यथा यदि (VOID_TYPE_P (tt0) && !TYPE_ATOMIC (tt0))
	    {
	      यदि (pedantic && वृक्ष_CODE (tt1) == FUNCTION_TYPE)
		pedwarn (location, OPT_Wpedantic, "ISO C forbids "
			 "comparison of %<void *%> with function pointer");
	    }
	  अन्यथा यदि (VOID_TYPE_P (tt1) && !TYPE_ATOMIC (tt1))
	    {
	      यदि (pedantic && वृक्ष_CODE (tt0) == FUNCTION_TYPE)
		pedwarn (location, OPT_Wpedantic, "ISO C forbids "
			 "comparison of %<void *%> with function pointer");
	    }
	  अन्यथा
	    /* Avoid warning about the volatile ObjC EH puts on decls.  */
	    यदि (!objc_ok)
	      pedwarn (location, OPT_Wcompare_distinct_pointer_types,
		       "comparison of distinct pointer types lacks a cast");

	  यदि (result_type == NULL_वृक्ष)
	    {
	      पूर्णाङ्क qual = ENCODE_QUAL_ADDR_SPACE (as_common);
	      result_type = c_build_pointer_type
			      (c_build_qualified_type (void_type_गाँठ, qual));
	    }
	}
      अन्यथा यदि (code0 == POINTER_TYPE
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  result_type = type0;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}
      अन्यथा यदि ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	       && code1 == POINTER_TYPE)
	{
	  result_type = type1;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}
      /* 6.5.9: One of the following shall hold:
	 -- both operands have type nullptr_t;  */
      अन्यथा यदि (code0 == NULLPTR_TYPE && code1 == NULLPTR_TYPE)
	{
	  result_type = nullptr_type_गाँठ;
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
      अन्यथा यदि (code0 == NULLPTR_TYPE && null_pointer_constant_p (orig_op1))
	result_type = (INTEGRAL_TYPE_P (type1)
		       ? c_build_pointer_type (type1) : type1);
      अन्यथा यदि (code1 == NULLPTR_TYPE && null_pointer_constant_p (orig_op0))
	result_type = (INTEGRAL_TYPE_P (type0)
		       ? c_build_pointer_type (type0) : type0);
      यदि ((C_BOOLEAN_TYPE_P (वृक्ष_TYPE (orig_op0))
	   || truth_मूल्य_p (वृक्ष_CODE (orig_op0)))
	  ^ (C_BOOLEAN_TYPE_P (वृक्ष_TYPE (orig_op1))
	     || truth_मूल्य_p (वृक्ष_CODE (orig_op1))))
	maybe_warn_bool_compare (location, code, orig_op0, orig_op1);
      भङ्ग;

    पक्ष LE_व्यंजक:
    पक्ष GE_व्यंजक:
    पक्ष LT_व्यंजक:
    पक्ष GT_व्यंजक:
      यदि (gnu_vector_type_p (type0) && gnu_vector_type_p (type1))
        {
          वृक्ष intt;
	  यदि (!vector_types_compatible_elements_p (type0, type1))
            {
              error_at (location, "comparing vectors with different "
                                  "element types");
              प्रत्यागम error_mark_गाँठ;
            }

	  यदि (maybe_ne (TYPE_VECTOR_SUBPARTS (type0),
			TYPE_VECTOR_SUBPARTS (type1)))
            {
              error_at (location, "comparing vectors with different "
                                  "number of elements");
              प्रत्यागम error_mark_गाँठ;
            }

	  /* It's not precisely specified how the usual arithmetic
	     conversions apply to the vector types.  Here, we use
	     the unsigned type if one of the operands is signed and
	     the other one is unsigned.  */
	  यदि (TYPE_UNSIGNED (type0) != TYPE_UNSIGNED (type1))
	    {
	      यदि (!TYPE_UNSIGNED (type0))
		op0 = build1 (VIEW_CONVERT_व्यंजक, type1, op0);
	      अन्यथा
		op1 = build1 (VIEW_CONVERT_व्यंजक, type0, op1);
	      warning_at (location, OPT_Wsign_compare, "comparison between "
			  "types %qT and %qT", type0, type1);
	    }

          /* Always construct signed integer vector type.  */
          intt = c_common_type_for_size (GET_MODE_BITSIZE
					 (SCALAR_TYPE_MODE
					  (वृक्ष_TYPE (type0))), 0);
	  यदि (!intt)
	    {
	      error_at (location, "could not find an integer type "
				  "of the same size as %qT",
			वृक्ष_TYPE (type0));
	      प्रत्यागम error_mark_गाँठ;
	    }
          result_type = build_opaque_vector_type (intt,
						  TYPE_VECTOR_SUBPARTS (type0));
          converted = 1;
	  ret = build_vec_cmp (resultcode, result_type, op0, op1);
	  गच्छ return_build_द्विआधारी_op;
        }
      build_type = integer_type_गाँठ;
      यदि ((code0 == INTEGER_TYPE || code0 == REAL_TYPE
	   || code0 == BITINT_TYPE || code0 == FIXED_POINT_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	      || code1 == BITINT_TYPE || code1 == FIXED_POINT_TYPE))
	short_compare = 1;
      अन्यथा यदि (code0 == POINTER_TYPE && code1 == POINTER_TYPE)
	{
	  addr_space_t as0 = TYPE_ADDR_SPACE (वृक्ष_TYPE (type0));
	  addr_space_t as1 = TYPE_ADDR_SPACE (वृक्ष_TYPE (type1));
	  addr_space_t as_common;

	  यदि (comp_target_types (location, type0, type1))
	    {
	      result_type = common_pointer_type (type0, type1, NULL_वृक्ष);
	      यदि (!COMPLETE_TYPE_P (वृक्ष_TYPE (type0))
		  != !COMPLETE_TYPE_P (वृक्ष_TYPE (type1)))
		pedwarn_c99 (location, OPT_Wpedantic,
			     "comparison of complete and incomplete pointers");
	      अन्यथा यदि (वृक्ष_CODE (वृक्ष_TYPE (type0)) == FUNCTION_TYPE)
		pedwarn (location, OPT_Wpedantic, "ISO C forbids "
			 "ordered comparisons of pointers to functions");
	      अन्यथा यदि (null_pointer_constant_p (orig_op0)
		       || null_pointer_constant_p (orig_op1))
		warning_at (location, OPT_Wextra,
			    "ordered comparison of pointer with null pointer");

	    }
	  अन्यथा यदि (!addr_space_superset (as0, as1, &as_common))
	    {
	      error_at (location, "comparison of pointers to "
			"disjoint address spaces");
	      प्रत्यागम error_mark_गाँठ;
	    }
	  अन्यथा
	    {
	      पूर्णाङ्क qual = ENCODE_QUAL_ADDR_SPACE (as_common);
	      result_type = c_build_pointer_type
			      (c_build_qualified_type (void_type_गाँठ, qual));
              pedwarn (location, OPT_Wcompare_distinct_pointer_types,
                       "comparison of distinct pointer types lacks a cast");
	    }
	}
      अन्यथा यदि (code0 == POINTER_TYPE && null_pointer_constant_p (orig_op1))
	{
	  result_type = type0;
	  यदि (pedantic)
	    pedwarn (location, OPT_Wpedantic,
		     "ordered comparison of pointer with integer zero");
	  अन्यथा यदि (extra_warnings)
	    warning_at (location, OPT_Wextra,
			"ordered comparison of pointer with integer zero");
	}
      अन्यथा यदि (code1 == POINTER_TYPE && null_pointer_constant_p (orig_op0))
	{
	  result_type = type1;
	  यदि (pedantic)
	    pedwarn (location, OPT_Wpedantic,
		     "ordered comparison of pointer with integer zero");
	  अन्यथा यदि (extra_warnings)
	    warning_at (location, OPT_Wextra,
			"ordered comparison of pointer with integer zero");
	}
      अन्यथा यदि (code0 == POINTER_TYPE
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  result_type = type0;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}
      अन्यथा यदि ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	       && code1 == POINTER_TYPE)
	{
	  result_type = type1;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}

      यदि ((code0 == POINTER_TYPE || code1 == POINTER_TYPE)
	  && current_function_decl != NULL_वृक्ष
	  && sanitize_flags_p (SANITIZE_POINTER_COMPARE))
	{
	  op0 = save_व्यंजक (c_fully_fold (op0, असत्य, रिक्त));
	  op1 = save_व्यंजक (c_fully_fold (op1, असत्य, रिक्त));

	  वृक्ष tt = builtin_decl_explicit (BUILT_IN_ASAN_POINTER_COMPARE);
	  instrument_व्यंजक = build_call_व्यंजक_loc (location, tt, 2, op0, op1);
	}

      यदि ((C_BOOLEAN_TYPE_P (वृक्ष_TYPE (orig_op0))
	   || truth_मूल्य_p (वृक्ष_CODE (orig_op0)))
	  ^ (C_BOOLEAN_TYPE_P (वृक्ष_TYPE (orig_op1))
	     || truth_मूल्य_p (वृक्ष_CODE (orig_op1))))
	maybe_warn_bool_compare (location, code, orig_op0, orig_op1);
      भङ्ग;

    पक्ष MIN_व्यंजक:
    पक्ष MAX_व्यंजक:
      /* Used for OpenMP atomics.  */
      gcc_assert (flag_openmp);
      common = 1;
      भङ्ग;

    स्वभाव:
      gcc_unreachable ();
    }

  यदि (code0 == ERROR_MARK || code1 == ERROR_MARK)
    प्रत्यागम error_mark_गाँठ;

  यदि (gnu_vector_type_p (type0)
      && gnu_vector_type_p (type1)
      && (!वृक्ष_int_cst_equal (TYPE_SIZE (type0), TYPE_SIZE (type1))
	  || !vector_types_compatible_elements_p (type0, type1)))
    {
      gcc_rich_location richloc (location);
      maybe_range_label_for_वृक्ष_type_mismatch
	label_for_op0 (orig_op0, orig_op1),
	label_for_op1 (orig_op1, orig_op0);
      richloc.maybe_add_व्यंजक (orig_op0, &label_for_op0, highlight_colors::lhs);
      richloc.maybe_add_व्यंजक (orig_op1, &label_for_op1, highlight_colors::rhs);
      द्विआधारी_op_error (&richloc, code, type0, type1);
      प्रत्यागम error_mark_गाँठ;
    }

  यदि ((code0 == INTEGER_TYPE || code0 == REAL_TYPE || code0 == COMPLEX_TYPE
       || code0 == FIXED_POINT_TYPE || code0 == BITINT_TYPE
       || gnu_vector_type_p (type0))
      && (code1 == INTEGER_TYPE || code1 == REAL_TYPE || code1 == COMPLEX_TYPE
	  || code1 == FIXED_POINT_TYPE || code1 == BITINT_TYPE
	  || gnu_vector_type_p (type1)))
    {
      तार्किक first_complex = (code0 == COMPLEX_TYPE);
      तार्किक second_complex = (code1 == COMPLEX_TYPE);
      पूर्णाङ्क none_complex = (!first_complex && !second_complex);

      यदि (shorten || common || short_compare)
	{
	  result_type = c_common_type (type0, type1);
	  do_warn_double_promotion (result_type, type0, type1,
				    "implicit conversion from %qT to %qT "
				    "to match other operand of binary "
				    "expression",
				    location);
	  यदि (result_type == error_mark_गाँठ)
	    प्रत्यागम error_mark_गाँठ;
	}

      यदि (first_complex != second_complex
	  && (code == PLUS_व्यंजक
	      || code == MINUS_व्यंजक
	      || code == MULT_व्यंजक
	      || (code == TRUNC_DIV_व्यंजक && first_complex))
	  && वृक्ष_CODE (वृक्ष_TYPE (result_type)) == REAL_TYPE
	  && flag_signed_zeros)
	{
	  /* An operation on mixed real/complex operands must be
	     handled specially, but the language-independent code can
	     more easily optimize the plain complex arithmetic if
	     -fno-signed-zeros.  */
	  वृक्ष real_type = वृक्ष_TYPE (result_type);
	  वृक्ष real, imag;
	  यदि (type0 != orig_type0 || type1 != orig_type1)
	    {
	      gcc_assert (may_need_excess_precision && common);
	      semantic_result_type = c_common_type (orig_type0, orig_type1);
	    }
	  यदि (first_complex)
	    {
	      यदि (वृक्ष_TYPE (op0) != result_type)
		op0 = convert_and_check (location, result_type, op0);
	      यदि (वृक्ष_TYPE (op1) != real_type)
		op1 = convert_and_check (location, real_type, op1);
	    }
	  अन्यथा
	    {
	      यदि (वृक्ष_TYPE (op0) != real_type)
		op0 = convert_and_check (location, real_type, op0);
	      यदि (वृक्ष_TYPE (op1) != result_type)
		op1 = convert_and_check (location, result_type, op1);
	    }
	  यदि (वृक्ष_CODE (op0) == ERROR_MARK || वृक्ष_CODE (op1) == ERROR_MARK)
	    प्रत्यागम error_mark_गाँठ;
	  यदि (first_complex)
	    {
	      op0 = save_व्यंजक (op0);
	      real = build_unary_op (व्यंजक_LOCATION (orig_op0), REALPART_व्यंजक,
				     op0, सत्य);
	      imag = build_unary_op (व्यंजक_LOCATION (orig_op0), IMAGPART_व्यंजक,
				     op0, सत्य);
	      विकल्प (code)
		{
		पक्ष MULT_व्यंजक:
		पक्ष TRUNC_DIV_व्यंजक:
		  op1 = save_व्यंजक (op1);
		  imag = build2 (resultcode, real_type, imag, op1);
		  /* Fall through.  */
		पक्ष PLUS_व्यंजक:
		पक्ष MINUS_व्यंजक:
		  real = build2 (resultcode, real_type, real, op1);
		  भङ्ग;
		स्वभाव:
		  gcc_unreachable();
		}
	    }
	  अन्यथा
	    {
	      op1 = save_व्यंजक (op1);
	      real = build_unary_op (व्यंजक_LOCATION (orig_op1), REALPART_व्यंजक,
				     op1, सत्य);
	      imag = build_unary_op (व्यंजक_LOCATION (orig_op1), IMAGPART_व्यंजक,
				     op1, सत्य);
	      विकल्प (code)
		{
		पक्ष MULT_व्यंजक:
		  op0 = save_व्यंजक (op0);
		  imag = build2 (resultcode, real_type, op0, imag);
		  /* Fall through.  */
		पक्ष PLUS_व्यंजक:
		  real = build2 (resultcode, real_type, op0, real);
		  भङ्ग;
		पक्ष MINUS_व्यंजक:
		  real = build2 (resultcode, real_type, op0, real);
		  imag = build1 (NEGATE_व्यंजक, real_type, imag);
		  भङ्ग;
		स्वभाव:
		  gcc_unreachable();
		}
	    }
	  ret = build2 (COMPLEX_व्यंजक, result_type, real, imag);
	  गच्छ return_build_द्विआधारी_op;
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

      यदि (shorten && none_complex)
	{
	  final_type = result_type;
	  result_type = shorten_द्विआधारी_op (result_type, op0, op1,
					   shorten == -1);
	}

      /* Shifts can be shortened if shifting right.  */

      यदि (short_shift)
	{
	  पूर्णाङ्क unsigned_arg;
	  वृक्ष arg0 = get_narrower (op0, &unsigned_arg);

	  final_type = result_type;

	  यदि (arg0 == op0 && final_type == वृक्ष_TYPE (op0))
	    unsigned_arg = TYPE_UNSIGNED (वृक्ष_TYPE (op0));

	  यदि (TYPE_PRECISION (वृक्ष_TYPE (arg0)) < TYPE_PRECISION (result_type)
	      && वृक्ष_int_cst_sgn (op1) > 0
	      /* We can shorten only if the shift count is less than the
		 number of bits in the smaller type size.  */
	      && compare_वृक्ष_int (op1, TYPE_PRECISION (वृक्ष_TYPE (arg0))) < 0
	      /* We cannot drop an unsigned shift after sign-extension.  */
	      && (!TYPE_UNSIGNED (final_type) || unsigned_arg))
	    {
	      /* Do an unsigned shift if the operand was zero-extended.  */
	      result_type
		= c_common_signed_or_unsigned_type (unsigned_arg,
						    वृक्ष_TYPE (arg0));
	      /* Convert value-to-be-shifted to that type.  */
	      यदि (वृक्ष_TYPE (op0) != result_type)
		op0 = convert (result_type, op0);
	      converted = 1;
	    }
	}

      /* Comparison operations are shortened too but differently.
	 They identify themselves by setting short_compare = 1.  */

      यदि (short_compare)
	{
	  /* Don't write &op0, etc., because that would prevent op0
	     from being kept in a register.
	     Instead, make copies of the our local variables and
	     pass the copies by reference, then copy them back afterward.  */
	  वृक्ष xop0 = op0, xop1 = op1, xresult_type = result_type;
	  गणना वृक्ष_code xresultcode = resultcode;
	  वृक्ष val
	    = shorten_compare (location, &xop0, &xop1, &xresult_type,
			       &xresultcode);

	  यदि (val != NULL_वृक्ष)
	    {
	      ret = val;
	      गच्छ return_build_द्विआधारी_op;
	    }

	  op0 = xop0, op1 = xop1;
	  converted = 1;
	  resultcode = xresultcode;

	  यदि (c_inhibit_evaluation_warnings == 0 && !c_in_omp_for)
	    {
	      तार्किक op0_maybe_const = सत्य;
	      तार्किक op1_maybe_const = सत्य;
	      वृक्ष orig_op0_folded, orig_op1_folded;

	      यदि (in_late_द्विआधारी_op)
		{
		  orig_op0_folded = orig_op0;
		  orig_op1_folded = orig_op1;
		}
	      अन्यथा
		{
		  /* Fold for the sake of possible warnings, as in
		     build_conditional_expr.  This requires the
		     "original" values to be folded, not just op0 and
		     op1.  */
		  c_inhibit_evaluation_warnings++;
		  op0 = c_fully_fold (op0, require_constant_मूल्य,
				      &op0_maybe_const);
		  op1 = c_fully_fold (op1, require_constant_मूल्य,
				      &op1_maybe_const);
		  c_inhibit_evaluation_warnings--;
		  orig_op0_folded = c_fully_fold (orig_op0,
						  require_constant_मूल्य,
						  रिक्त);
		  orig_op1_folded = c_fully_fold (orig_op1,
						  require_constant_मूल्य,
						  रिक्त);
		}

	      यदि (warn_sign_compare)
		warn_for_sign_compare (location, orig_op0_folded,
				       orig_op1_folded, op0, op1,
				       result_type, resultcode);
	      यदि (!in_late_द्विआधारी_op && !int_operands)
		{
		  यदि (!op0_maybe_const || वृक्ष_CODE (op0) != INTEGER_CST)
		    op0 = c_wrap_maybe_const (op0, !op0_maybe_const);
		  यदि (!op1_maybe_const || वृक्ष_CODE (op1) != INTEGER_CST)
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

  यदि (!result_type)
    {
      /* Favor showing any expression locations that are available. */
      op_location_t oploc (location, UNKNOWN_LOCATION);
      द्विआधारी_op_rich_location richloc (oploc, orig_op0, orig_op1, सत्य);
      द्विआधारी_op_error (&richloc, code, वृक्ष_TYPE (op0), वृक्ष_TYPE (op1));
      प्रत्यागम error_mark_गाँठ;
    }

  यदि (build_type == NULL_वृक्ष)
    {
      build_type = result_type;
      यदि ((type0 != orig_type0 || type1 != orig_type1)
	  && !boolean_op)
	{
	  gcc_assert (may_need_excess_precision && common);
	  semantic_result_type = c_common_type (orig_type0, orig_type1);
	}
    }

  यदि (!converted)
    {
      op0 = ep_convert_and_check (location, result_type, op0,
				  semantic_result_type);
      op1 = ep_convert_and_check (location, result_type, op1,
				  semantic_result_type);

      /* This can happen if one operand has a vector type, and the other
	 has a different type.  */
      यदि (वृक्ष_CODE (op0) == ERROR_MARK || वृक्ष_CODE (op1) == ERROR_MARK)
	प्रत्यागम error_mark_गाँठ;
    }

  यदि (sanitize_flags_p ((SANITIZE_SHIFT
			 | SANITIZE_DIVIDE
			 | SANITIZE_FLOAT_DIVIDE
			 | SANITIZE_SI_OVERFLOW))
      && current_function_decl != NULL_वृक्ष
      && (doing_div_or_mod || doing_shift)
      && !require_constant_मूल्य)
    {
      /* OP0 and/or OP1 might have side-effects.  */
      op0 = save_व्यंजक (op0);
      op1 = save_व्यंजक (op1);
      op0 = c_fully_fold (op0, असत्य, रिक्त);
      op1 = c_fully_fold (op1, असत्य, रिक्त);
      यदि (doing_div_or_mod && (sanitize_flags_p ((SANITIZE_DIVIDE
						  | SANITIZE_FLOAT_DIVIDE
						  | SANITIZE_SI_OVERFLOW))))
	instrument_व्यंजक = ubsan_instrument_division (location, op0, op1);
      अन्यथा यदि (doing_shift && sanitize_flags_p (SANITIZE_SHIFT))
	instrument_व्यंजक = ubsan_instrument_shift (location, code, op0, op1);
    }

  /* Treat expressions in initializers specially as they can't trap.  */
  यदि (int_const_or_overflow)
    ret = (require_constant_मूल्य
	   ? fold_build2_initializer_loc (location, resultcode, build_type,
					  op0, op1)
	   : fold_build2_loc (location, resultcode, build_type, op0, op1));
  अन्यथा
    ret = build2 (resultcode, build_type, op0, op1);
  यदि (final_type != NULL_वृक्ष)
    ret = convert (final_type, ret);

 return_build_द्विआधारी_op:
  gcc_assert (ret != error_mark_गाँठ);
  यदि (वृक्ष_CODE (ret) == INTEGER_CST && !वृक्ष_OVERFLOW (ret) && !int_const)
    ret = (int_operands
	   ? note_integer_operands (ret)
	   : build1 (NOP_व्यंजक, वृक्ष_TYPE (ret), ret));
  अन्यथा यदि (वृक्ष_CODE (ret) != INTEGER_CST && int_operands
	   && !in_late_द्विआधारी_op)
    ret = note_integer_operands (ret);
  protected_set_व्यंजक_location (ret, location);

  यदि (instrument_व्यंजक != रिक्त)
    ret = fold_build2 (COMPOUND_व्यंजक, वृक्ष_TYPE (ret),
		       instrument_व्यंजक, ret);

  यदि (semantic_result_type)
    ret = build1_loc (location, EXCESS_PRECISION_व्यंजक,
		      semantic_result_type, ret);

  प्रत्यागम ret;
}


/* Convert EXPR to be a truth-value (type TYPE), validating its type for this
   purpose.  LOCATION is the source location for the expression.  */

वृक्ष
c_objc_common_truthvalue_conversion (location_t location, वृक्ष व्यंजक, वृक्ष type)
{
  तार्किक int_const, int_operands;

  विकल्प (वृक्ष_CODE (वृक्ष_TYPE (व्यंजक)))
    {
    पक्ष ARRAY_TYPE:
      error_at (location, "used array that cannot be converted to pointer where scalar is required");
      प्रत्यागम error_mark_गाँठ;

    पक्ष RECORD_TYPE:
      error_at (location, "used struct type value where scalar is required");
      प्रत्यागम error_mark_गाँठ;

    पक्ष UNION_TYPE:
      error_at (location, "used union type value where scalar is required");
      प्रत्यागम error_mark_गाँठ;

    पक्ष VOID_TYPE:
      error_at (location, "void value not ignored as it ought to be");
      प्रत्यागम error_mark_गाँठ;

    पक्ष POINTER_TYPE:
      यदि (reject_gcc_builtin (व्यंजक))
	प्रत्यागम error_mark_गाँठ;
      भङ्ग;

    पक्ष FUNCTION_TYPE:
      gcc_unreachable ();

    पक्ष VECTOR_TYPE:
      error_at (location, "used vector type where scalar is required");
      प्रत्यागम error_mark_गाँठ;

    स्वभाव:
      भङ्ग;
    }

  /* Conversion of a floating constant to boolean goes through here
     and yields an integer constant expression.  Otherwise, the result
     is only an integer constant expression if the argument is.  */
  int_const = ((वृक्ष_CODE (व्यंजक) == INTEGER_CST && !वृक्ष_OVERFLOW (व्यंजक))
	       || ((वृक्ष_CODE (व्यंजक) == REAL_CST
		    || वृक्ष_CODE (व्यंजक) == COMPLEX_CST)
		   && (वृक्ष_CODE (type) == BOOLEAN_TYPE
		       || (वृक्ष_CODE (type) == ENUMERAL_TYPE
			   && ENUM_UNDERLYING_TYPE (type) != NULL_वृक्ष
			   && (वृक्ष_CODE (ENUM_UNDERLYING_TYPE (type))
			       == BOOLEAN_TYPE)))));
  int_operands = व्यंजक_INT_CONST_OPERANDS (व्यंजक);
  यदि (int_operands && वृक्ष_CODE (व्यंजक) != INTEGER_CST)
    {
      व्यंजक = remove_c_maybe_const_व्यंजक (व्यंजक);
      व्यंजक = build2 (NE_व्यंजक, type, व्यंजक,
		     convert (वृक्ष_TYPE (व्यंजक), integer_zero_गाँठ));
      व्यंजक = note_integer_operands (व्यंजक);
    }
  अन्यथा
    {
      /* ??? Should we also give an error for vectors rather than leaving
	 those to give errors later?  */
      व्यंजक = c_common_truthvalue_conversion (location, व्यंजक);
      व्यंजक = fold_convert_loc (location, type, व्यंजक);
    }

  यदि (वृक्ष_CODE (व्यंजक) == INTEGER_CST && int_operands && !int_const)
    {
      यदि (वृक्ष_OVERFLOW (व्यंजक))
	प्रत्यागम व्यंजक;
      अन्यथा
	प्रत्यागम note_integer_operands (व्यंजक);
    }
  यदि (वृक्ष_CODE (व्यंजक) == INTEGER_CST && !int_const)
    प्रत्यागम build1 (NOP_व्यंजक, वृक्ष_TYPE (व्यंजक), व्यंजक);
  प्रत्यागम व्यंजक;
}


/* Convert EXPR to a contained DECL, updating *TC, *TI and *SE as
   required.  */

वृक्ष
c_व्यंजक_to_decl (वृक्ष व्यंजक, तार्किक *tc ATTRIBUTE_UNUSED, तार्किक *se)
{
  यदि (वृक्ष_CODE (व्यंजक) == COMPOUND_LITERAL_व्यंजक)
    {
      वृक्ष decl = COMPOUND_LITERAL_व्यंजक_DECL (व्यंजक);
      /* Executing a compound literal inside a function reinitializes
	 it.  */
      यदि (!वृक्ष_STATIC (decl))
	*se = सत्य;
      प्रत्यागम decl;
    }
  अन्यथा
    प्रत्यागम व्यंजक;
}

/* Generate OMP construct CODE, with BODY and CLAUSES as its compound
   statement.  LOC is the location of the construct.  */

वृक्ष
c_finish_omp_construct (location_t loc, गणना वृक्ष_code code, वृक्ष body,
			वृक्ष clauses)
{
  body = c_end_compound_stmt (loc, body, सत्य);

  वृक्ष stmt = make_गाँठ (code);
  वृक्ष_TYPE (stmt) = void_type_गाँठ;
  OMP_BODY (stmt) = body;
  OMP_CLAUSES (stmt) = clauses;
  SET_व्यंजक_LOCATION (stmt, loc);

  प्रत्यागम add_stmt (stmt);
}

/* Generate OACC_DATA, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the OACC_DATA.  */

वृक्ष
c_finish_oacc_data (location_t loc, वृक्ष clauses, वृक्ष block)
{
  वृक्ष stmt;

  block = c_end_compound_stmt (loc, block, सत्य);

  stmt = make_गाँठ (OACC_DATA);
  वृक्ष_TYPE (stmt) = void_type_गाँठ;
  OACC_DATA_CLAUSES (stmt) = clauses;
  OACC_DATA_BODY (stmt) = block;
  SET_व्यंजक_LOCATION (stmt, loc);

  प्रत्यागम add_stmt (stmt);
}

/* Generate OACC_HOST_DATA, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the OACC_HOST_DATA.  */

वृक्ष
c_finish_oacc_host_data (location_t loc, वृक्ष clauses, वृक्ष block)
{
  वृक्ष stmt;

  block = c_end_compound_stmt (loc, block, सत्य);

  stmt = make_गाँठ (OACC_HOST_DATA);
  वृक्ष_TYPE (stmt) = void_type_गाँठ;
  OACC_HOST_DATA_CLAUSES (stmt) = clauses;
  OACC_HOST_DATA_BODY (stmt) = block;
  SET_व्यंजक_LOCATION (stmt, loc);

  प्रत्यागम add_stmt (stmt);
}

/* Like c_begin_compound_stmt, except force the retention of the BLOCK.  */

वृक्ष
c_begin_omp_parallel (शून्य)
{
  वृक्ष block;

  keep_next_level ();
  block = c_begin_compound_stmt (सत्य);

  प्रत्यागम block;
}

/* Generate OMP_PARALLEL, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the OMP_PARALLEL.  */

वृक्ष
c_finish_omp_parallel (location_t loc, वृक्ष clauses, वृक्ष block)
{
  वृक्ष stmt;

  block = c_end_compound_stmt (loc, block, सत्य);

  stmt = make_गाँठ (OMP_PARALLEL);
  वृक्ष_TYPE (stmt) = void_type_गाँठ;
  OMP_PARALLEL_CLAUSES (stmt) = clauses;
  OMP_PARALLEL_BODY (stmt) = block;
  SET_व्यंजक_LOCATION (stmt, loc);

  प्रत्यागम add_stmt (stmt);
}

/* Like c_begin_compound_stmt, except force the retention of the BLOCK.  */

वृक्ष
c_begin_omp_task (शून्य)
{
  वृक्ष block;

  keep_next_level ();
  block = c_begin_compound_stmt (सत्य);

  प्रत्यागम block;
}

/* Generate OMP_TASK, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the #pragma.  */

वृक्ष
c_finish_omp_task (location_t loc, वृक्ष clauses, वृक्ष block)
{
  वृक्ष stmt;

  block = c_end_compound_stmt (loc, block, सत्य);

  stmt = make_गाँठ (OMP_TASK);
  वृक्ष_TYPE (stmt) = void_type_गाँठ;
  OMP_TASK_CLAUSES (stmt) = clauses;
  OMP_TASK_BODY (stmt) = block;
  SET_व्यंजक_LOCATION (stmt, loc);

  प्रत्यागम add_stmt (stmt);
}

/* Generate GOMP_cancel call for #pragma omp cancel.  */

शून्य
c_finish_omp_cancel (location_t loc, वृक्ष clauses)
{
  वृक्ष fn = builtin_decl_explicit (BUILT_IN_GOMP_CANCEL);
  पूर्णाङ्क mask = 0;
  यदि (omp_find_clause (clauses, OMP_CLAUSE_PARALLEL))
    mask = 1;
  अन्यथा यदि (omp_find_clause (clauses, OMP_CLAUSE_FOR))
    mask = 2;
  अन्यथा यदि (omp_find_clause (clauses, OMP_CLAUSE_SECTIONS))
    mask = 4;
  अन्यथा यदि (omp_find_clause (clauses, OMP_CLAUSE_TASKGROUP))
    mask = 8;
  अन्यथा
    {
      error_at (loc, "%<#pragma omp cancel%> must specify one of "
		     "%<parallel%>, %<for%>, %<sections%> or %<taskgroup%> "
		     "clauses");
      प्रत्यागम;
    }
  वृक्ष ifc = omp_find_clause (clauses, OMP_CLAUSE_IF);
  यदि (ifc != NULL_वृक्ष)
    {
      यदि (OMP_CLAUSE_IF_MODIFIER (ifc) != ERROR_MARK
	  && OMP_CLAUSE_IF_MODIFIER (ifc) != VOID_CST)
	error_at (OMP_CLAUSE_LOCATION (ifc),
		  "expected %<cancel%> %<if%> clause modifier");
      अन्यथा
	{
	  वृक्ष ifc2 = omp_find_clause (OMP_CLAUSE_CHAIN (ifc), OMP_CLAUSE_IF);
	  यदि (ifc2 != NULL_वृक्ष)
	    {
	      gcc_assert (OMP_CLAUSE_IF_MODIFIER (ifc) == VOID_CST
			  && OMP_CLAUSE_IF_MODIFIER (ifc2) != ERROR_MARK
			  && OMP_CLAUSE_IF_MODIFIER (ifc2) != VOID_CST);
	      error_at (OMP_CLAUSE_LOCATION (ifc2),
			"expected %<cancel%> %<if%> clause modifier");
	    }
	}

      वृक्ष type = वृक्ष_TYPE (OMP_CLAUSE_IF_व्यंजक (ifc));
      ifc = fold_build2_loc (OMP_CLAUSE_LOCATION (ifc), NE_व्यंजक,
			     boolean_type_गाँठ, OMP_CLAUSE_IF_व्यंजक (ifc),
			     build_zero_cst (type));
    }
  अन्यथा
    ifc = boolean_true_गाँठ;
  वृक्ष stmt = build_call_व्यंजक_loc (loc, fn, 2,
				   build_int_cst (integer_type_गाँठ, mask),
				   ifc);
  add_stmt (stmt);
}

/* Generate GOMP_cancellation_point call for
   #pragma omp cancellation point.  */

शून्य
c_finish_omp_cancellation_point (location_t loc, वृक्ष clauses)
{
  वृक्ष fn = builtin_decl_explicit (BUILT_IN_GOMP_CANCELLATION_POINT);
  पूर्णाङ्क mask = 0;
  यदि (omp_find_clause (clauses, OMP_CLAUSE_PARALLEL))
    mask = 1;
  अन्यथा यदि (omp_find_clause (clauses, OMP_CLAUSE_FOR))
    mask = 2;
  अन्यथा यदि (omp_find_clause (clauses, OMP_CLAUSE_SECTIONS))
    mask = 4;
  अन्यथा यदि (omp_find_clause (clauses, OMP_CLAUSE_TASKGROUP))
    mask = 8;
  अन्यथा
    {
      error_at (loc, "%<#pragma omp cancellation point%> must specify one of "
		     "%<parallel%>, %<for%>, %<sections%> or %<taskgroup%> "
		     "clauses");
      प्रत्यागम;
    }
  वृक्ष stmt = build_call_व्यंजक_loc (loc, fn, 1,
				   build_int_cst (integer_type_गाँठ, mask));
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

स्थिर वृक्ष
handle_omp_array_sections_1 (वृक्ष c, वृक्ष t, vec<वृक्ष> &types,
			     तार्किक &maybe_zero_len, अचिन्हित पूर्णाङ्क &first_non_one,
			     गणना c_omp_region_type ort)
{
  वृक्ष ret, निचला_bound, length, type;
  तार्किक openacc = (ort & C_ORT_ACC) != 0;
  यदि (वृक्ष_CODE (t) != OMP_ARRAY_SECTION)
    {
      यदि (error_operand_p (t))
	प्रत्यागम error_mark_गाँठ;
      c_omp_address_inspector ai (OMP_CLAUSE_LOCATION (c), t);
      ret = t;
      यदि (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
	  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
	  && TYPE_ATOMIC (strip_array_types (वृक्ष_TYPE (t))))
	{
	  error_at (OMP_CLAUSE_LOCATION (c), "%<_Atomic%> %qE in %qs clause",
		    t, omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  प्रत्यागम error_mark_गाँठ;
	}
      यदि (!ai.check_clause (c))
	प्रत्यागम error_mark_गाँठ;
      अन्यथा यदि (ai.component_access_p ()
	       && (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TO
		   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_FROM))
	t = ai.get_मूल_term (सत्य);
      अन्यथा
	t = ai.unconverted_ref_origin ();
      यदि (t == error_mark_गाँठ)
	प्रत्यागम error_mark_गाँठ;
      यदि (!VAR_P (t)
	  && (ort == C_ORT_ACC || !व्यंजक_P (t))
	  && वृक्ष_CODE (t) != PARM_DECL)
	{
	  यदि (DECL_P (t))
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD is not a variable in %qs clause", t,
		      omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  अन्यथा
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qE is not a variable in %qs clause", t,
		      omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  प्रत्यागम error_mark_गाँठ;
	}
      अन्यथा यदि (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
	       && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
	       && TYPE_ATOMIC (वृक्ष_TYPE (t)))
	{
	  error_at (OMP_CLAUSE_LOCATION (c), "%<_Atomic%> %qD in %qs clause",
		    t, omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  प्रत्यागम error_mark_गाँठ;
	}
      अन्यथा यदि (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
	       && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
	       && VAR_P (t)
	       && DECL_THREAD_LOCAL_P (t))
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "%qD is threadprivate variable in %qs clause", t,
		    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  प्रत्यागम error_mark_गाँठ;
	}
      यदि ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY
	   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND)
	  && TYPE_ATOMIC (वृक्ष_TYPE (t))
	  && POINTER_TYPE_P (वृक्ष_TYPE (t)))
	{
	  /* If the array section is pointer based and the pointer
	     itself is _Atomic qualified, we need to atomically load
	     the pointer.  */
	  ret = convert_lvalue_to_rvalue (OMP_CLAUSE_LOCATION (c),
					  ret, असत्य, असत्य);
	}
      प्रत्यागम ret;
    }

  ret = handle_omp_array_sections_1 (c, वृक्ष_OPERAND (t, 0), types,
				     maybe_zero_len, first_non_one, ort);
  यदि (ret == error_mark_गाँठ || ret == NULL_वृक्ष)
    प्रत्यागम ret;

  type = वृक्ष_TYPE (ret);
  निचला_bound = वृक्ष_OPERAND (t, 1);
  length = वृक्ष_OPERAND (t, 2);

  यदि (निचला_bound == error_mark_गाँठ || length == error_mark_गाँठ)
    प्रत्यागम error_mark_गाँठ;

  यदि (निचला_bound && !INTEGRAL_TYPE_P (वृक्ष_TYPE (निचला_bound)))
    {
      error_at (OMP_CLAUSE_LOCATION (c),
		"low bound %qE of array section does not have integral type",
		निचला_bound);
      प्रत्यागम error_mark_गाँठ;
    }
  यदि (length && !INTEGRAL_TYPE_P (वृक्ष_TYPE (length)))
    {
      error_at (OMP_CLAUSE_LOCATION (c),
		"length %qE of array section does not have integral type",
		length);
      प्रत्यागम error_mark_गाँठ;
    }
  यदि (निचला_bound
      && वृक्ष_CODE (निचला_bound) == INTEGER_CST
      && TYPE_PRECISION (वृक्ष_TYPE (निचला_bound))
	 > TYPE_PRECISION (sizetype))
    निचला_bound = fold_convert (sizetype, निचला_bound);
  यदि (length
      && वृक्ष_CODE (length) == INTEGER_CST
      && TYPE_PRECISION (वृक्ष_TYPE (length))
	 > TYPE_PRECISION (sizetype))
    length = fold_convert (sizetype, length);
  यदि (निचला_bound == NULL_वृक्ष)
    निचला_bound = integer_zero_गाँठ;
  यदि (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
      && (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_ATTACH
	  || OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_DETACH))
    {
      यदि (length != integer_one_गाँठ)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "expected single pointer in %qs clause",
		    user_omp_clause_code_name (c, openacc));
	  प्रत्यागम error_mark_गाँठ;
	}
    }
  यदि (length != NULL_वृक्ष)
    {
      यदि (!integer_nonzerop (length))
	{
	  यदि (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY
	      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
	      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
	      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
	      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TASK_REDUCTION)
	    {
	      यदि (integer_zerop (length))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "zero length array section in %qs clause",
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  प्रत्यागम error_mark_गाँठ;
		}
	    }
	  अन्यथा
	    maybe_zero_len = सत्य;
	}
      यदि (first_non_one == types.length ()
	  && (वृक्ष_CODE (length) != INTEGER_CST || integer_onep (length)))
	first_non_one++;
    }
  यदि (वृक्ष_CODE (type) == ARRAY_TYPE)
    {
      यदि (length == NULL_वृक्ष
	  && (TYPE_DOMAIN (type) == NULL_वृक्ष
	      || TYPE_MAX_मूल्य (TYPE_DOMAIN (type)) == NULL_वृक्ष))
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "for unknown bound array type length expression must "
		    "be specified");
	  प्रत्यागम error_mark_गाँठ;
	}
      यदि (वृक्ष_CODE (निचला_bound) == INTEGER_CST
	  && वृक्ष_int_cst_sgn (निचला_bound) == -1)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "negative low bound in array section in %qs clause",
		    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  प्रत्यागम error_mark_गाँठ;
	}
      यदि (length != NULL_वृक्ष
	  && वृक्ष_CODE (length) == INTEGER_CST
	  && वृक्ष_int_cst_sgn (length) == -1)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "negative length in array section in %qs clause",
		    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  प्रत्यागम error_mark_गाँठ;
	}
      यदि (TYPE_DOMAIN (type)
	  && TYPE_MAX_मूल्य (TYPE_DOMAIN (type))
	  && वृक्ष_CODE (TYPE_MAX_मूल्य (TYPE_DOMAIN (type)))
			== INTEGER_CST)
	{
	  वृक्ष size
	    = fold_convert (sizetype, TYPE_MAX_मूल्य (TYPE_DOMAIN (type)));
	  size = size_binop (PLUS_व्यंजक, size, size_one_गाँठ);
	  यदि (वृक्ष_CODE (निचला_bound) == INTEGER_CST)
	    {
	      यदि (वृक्ष_int_cst_lt (size, निचला_bound))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "low bound %qE above array section size "
			    "in %qs clause", निचला_bound,
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  प्रत्यागम error_mark_गाँठ;
		}
	      यदि (वृक्ष_int_cst_equal (size, निचला_bound))
		{
		  यदि (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TASK_REDUCTION)
		    {
		      error_at (OMP_CLAUSE_LOCATION (c),
				"zero length array section in %qs clause",
				omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		      प्रत्यागम error_mark_गाँठ;
		    }
		  maybe_zero_len = सत्य;
		}
	      अन्यथा यदि (length == NULL_वृक्ष
		       && first_non_one == types.length ()
		       && वृक्ष_int_cst_equal
			    (TYPE_MAX_मूल्य (TYPE_DOMAIN (type)),
			     निचला_bound))
		first_non_one++;
	    }
	  अन्यथा यदि (length == NULL_वृक्ष)
	    {
	      यदि (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
		  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
		  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_REDUCTION
		  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_IN_REDUCTION
		  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_TASK_REDUCTION)
		maybe_zero_len = सत्य;
	      यदि (first_non_one == types.length ())
		first_non_one++;
	    }
	  यदि (length && वृक्ष_CODE (length) == INTEGER_CST)
	    {
	      यदि (वृक्ष_int_cst_lt (size, length))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "length %qE above array section size "
			    "in %qs clause", length,
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  प्रत्यागम error_mark_गाँठ;
		}
	      यदि (वृक्ष_CODE (निचला_bound) == INTEGER_CST)
		{
		  वृक्ष lbpluslen
		    = size_binop (PLUS_व्यंजक,
				  fold_convert (sizetype, निचला_bound),
				  fold_convert (sizetype, length));
		  यदि (वृक्ष_CODE (lbpluslen) == INTEGER_CST
		      && वृक्ष_int_cst_lt (size, lbpluslen))
		    {
		      error_at (OMP_CLAUSE_LOCATION (c),
				"high bound %qE above array section size "
				"in %qs clause", lbpluslen,
				omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		      प्रत्यागम error_mark_गाँठ;
		    }
		}
	    }
	}
      अन्यथा यदि (length == NULL_वृक्ष)
	{
	  यदि (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
	      && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
	      && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_REDUCTION
	      && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_IN_REDUCTION
	      && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_TASK_REDUCTION)
	    maybe_zero_len = सत्य;
	  यदि (first_non_one == types.length ())
	    first_non_one++;
	}

      /* For [lb:] we will need to evaluate lb more than once.  */
      यदि (length == NULL_वृक्ष && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND)
	{
	  वृक्ष lb = save_व्यंजक (निचला_bound);
	  यदि (lb != निचला_bound)
	    {
	      वृक्ष_OPERAND (t, 1) = lb;
	      निचला_bound = lb;
	    }
	}
    }
  अन्यथा यदि (वृक्ष_CODE (type) == POINTER_TYPE)
    {
      यदि (length == NULL_वृक्ष)
	{
	  यदि (वृक्ष_CODE (ret) == PARM_DECL && C_ARRAY_PARAMETER (ret))
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "for array function parameter length expression "
		      "must be specified");
	  अन्यथा
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "for pointer type length expression must be specified");
	  प्रत्यागम error_mark_गाँठ;
	}
      यदि (length != NULL_वृक्ष
	  && वृक्ष_CODE (length) == INTEGER_CST
	  && वृक्ष_int_cst_sgn (length) == -1)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "negative length in array section in %qs clause",
		    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  प्रत्यागम error_mark_गाँठ;
	}
      /* If there is a pointer type anywhere but in the very first
	 array-section-subscript, the array section could be non-contiguous.  */
      यदि (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
	  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
	  && वृक्ष_CODE (वृक्ष_OPERAND (t, 0)) == OMP_ARRAY_SECTION)
	{
	  /* If any prior dimension has a non-one length, then deem this
	     array section as non-contiguous.  */
	  प्रति (वृक्ष d = वृक्ष_OPERAND (t, 0);
	       वृक्ष_CODE (d) == OMP_ARRAY_SECTION;
	       d = वृक्ष_OPERAND (d, 0))
	    {
	      वृक्ष d_length = वृक्ष_OPERAND (d, 2);
	      यदि (d_length == NULL_वृक्ष || !integer_onep (d_length))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "array section is not contiguous in %qs clause",
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  प्रत्यागम error_mark_गाँठ;
		}
	    }
	}
    }
  अन्यथा
    {
      error_at (OMP_CLAUSE_LOCATION (c),
		"%qE does not have pointer or array type", ret);
      प्रत्यागम error_mark_गाँठ;
    }
  यदि (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND)
    types.safe_धकेलो (वृक्ष_TYPE (ret));
  /* We will need to evaluate lb more than once.  */
  वृक्ष lb = save_व्यंजक (निचला_bound);
  यदि (lb != निचला_bound)
    {
      वृक्ष_OPERAND (t, 1) = lb;
      निचला_bound = lb;
    }
  ret = build_array_ref (OMP_CLAUSE_LOCATION (c), ret, निचला_bound);
  प्रत्यागम ret;
}

/* Handle array sections for clause C.  */

स्थिर तार्किक
handle_omp_array_sections (वृक्ष &c, गणना c_omp_region_type ort)
{
  तार्किक maybe_zero_len = असत्य;
  अचिन्हित पूर्णाङ्क first_non_one = 0;
  auto_vec<वृक्ष, 10> types;
  वृक्ष *tp = &OMP_CLAUSE_DECL (c);
  यदि ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
       || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY)
      && OMP_ITERATOR_DECL_P (*tp))
    tp = &वृक्ष_मूल्य (*tp);
  वृक्ष first = handle_omp_array_sections_1 (c, *tp, types,
					    maybe_zero_len, first_non_one,
					    ort);
  यदि (first == error_mark_गाँठ)
    प्रत्यागम सत्य;
  यदि (first == NULL_वृक्ष)
    प्रत्यागम असत्य;
  यदि (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY)
    {
      वृक्ष t = *tp;
      वृक्ष tem = NULL_वृक्ष;
      /* Need to evaluate side effects in the length expressions
	 if any.  */
      यावत् (वृक्ष_CODE (t) == वृक्ष_LIST)
	{
	  यदि (वृक्ष_मूल्य (t) && वृक्ष_SIDE_EFFECTS (वृक्ष_मूल्य (t)))
	    {
	      यदि (tem == NULL_वृक्ष)
		tem = वृक्ष_मूल्य (t);
	      अन्यथा
		tem = build2 (COMPOUND_व्यंजक, वृक्ष_TYPE (tem),
			      वृक्ष_मूल्य (t), tem);
	    }
	  t = वृक्ष_CHAIN (t);
	}
      यदि (tem)
	first = build2 (COMPOUND_व्यंजक, वृक्ष_TYPE (first), tem, first);
      first = c_fully_fold (first, असत्य, रिक्त, सत्य);
      *tp = first;
    }
  अन्यथा
    {
      अचिन्हित पूर्णाङ्क अंक = types.length (), i;
      वृक्ष t, side_effects = NULL_वृक्ष, size = NULL_वृक्ष;
      वृक्ष condition = NULL_वृक्ष;

      यदि (int_size_in_bytes (वृक्ष_TYPE (first)) <= 0)
	maybe_zero_len = सत्य;

      प्रति (i = अंक, t = OMP_CLAUSE_DECL (c); i > 0;
	   t = वृक्ष_OPERAND (t, 0))
	{
	  वृक्ष निचला_bound = वृक्ष_OPERAND (t, 1);
	  वृक्ष length = वृक्ष_OPERAND (t, 2);

	  i--;
	  यदि (निचला_bound
	      && वृक्ष_CODE (निचला_bound) == INTEGER_CST
	      && TYPE_PRECISION (वृक्ष_TYPE (निचला_bound))
		 > TYPE_PRECISION (sizetype))
	    निचला_bound = fold_convert (sizetype, निचला_bound);
	  यदि (length
	      && वृक्ष_CODE (length) == INTEGER_CST
	      && TYPE_PRECISION (वृक्ष_TYPE (length))
		 > TYPE_PRECISION (sizetype))
	    length = fold_convert (sizetype, length);
	  यदि (निचला_bound == NULL_वृक्ष)
	    निचला_bound = integer_zero_गाँठ;
	  यदि (!maybe_zero_len && i > first_non_one)
	    {
	      यदि (integer_nonzerop (निचला_bound))
		गच्छ do_warn_noncontiguous;
	      यदि (length != NULL_वृक्ष
		  && वृक्ष_CODE (length) == INTEGER_CST
		  && TYPE_DOMAIN (types[i])
		  && TYPE_MAX_मूल्य (TYPE_DOMAIN (types[i]))
		  && वृक्ष_CODE (TYPE_MAX_मूल्य (TYPE_DOMAIN (types[i])))
		     == INTEGER_CST)
		{
		  वृक्ष size;
		  size = size_binop (PLUS_व्यंजक,
				     TYPE_MAX_मूल्य (TYPE_DOMAIN (types[i])),
				     size_one_गाँठ);
		  यदि (!वृक्ष_int_cst_equal (length, size))
		    {
		     do_warn_noncontiguous:
		      error_at (OMP_CLAUSE_LOCATION (c),
				"array section is not contiguous in %qs "
				"clause",
				omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		      प्रत्यागम सत्य;
		    }
		}
	      यदि (length != NULL_वृक्ष
		  && वृक्ष_SIDE_EFFECTS (length))
		{
		  यदि (side_effects == NULL_वृक्ष)
		    side_effects = length;
		  अन्यथा
		    side_effects = build2 (COMPOUND_व्यंजक,
					   वृक्ष_TYPE (side_effects),
					   length, side_effects);
		}
	    }
	  अन्यथा
	    {
	      वृक्ष l;

	      यदि (i > first_non_one
		  && ((length && integer_nonzerop (length))
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TASK_REDUCTION))
		अनुवर्त;
	      यदि (length)
		l = fold_convert (sizetype, length);
	      अन्यथा
		{
		  l = size_binop (PLUS_व्यंजक,
				  TYPE_MAX_मूल्य (TYPE_DOMAIN (types[i])),
				  size_one_गाँठ);
		  l = size_binop (MINUS_व्यंजक, l,
				  fold_convert (sizetype, निचला_bound));
		}
	      यदि (i > first_non_one)
		{
		  l = fold_build2 (NE_व्यंजक, boolean_type_गाँठ, l,
				   size_zero_गाँठ);
		  यदि (condition == NULL_वृक्ष)
		    condition = l;
		  अन्यथा
		    condition = fold_build2 (BIT_AND_व्यंजक, boolean_type_गाँठ,
					     l, condition);
		}
	      अन्यथा यदि (size == NULL_वृक्ष)
		{
		  size = size_in_bytes (वृक्ष_TYPE (types[i]));
		  वृक्ष eltype = वृक्ष_TYPE (types[अंक - 1]);
		  यावत् (वृक्ष_CODE (eltype) == ARRAY_TYPE)
		    eltype = वृक्ष_TYPE (eltype);
		  यदि (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TASK_REDUCTION)
		    {
		      यदि (integer_zerop (size)
			  || integer_zerop (size_in_bytes (eltype)))
			{
			  error_at (OMP_CLAUSE_LOCATION (c),
				    "zero length array section in %qs clause",
				    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
			  प्रत्यागम error_mark_गाँठ;
			}
		      size = size_binop (EXACT_DIV_व्यंजक, size,
					 size_in_bytes (eltype));
		    }
		  size = size_binop (MULT_व्यंजक, size, l);
		  यदि (condition)
		    size = fold_build3 (COND_व्यंजक, sizetype, condition,
					size, size_zero_गाँठ);
		}
	      अन्यथा
		size = size_binop (MULT_व्यंजक, size, l);
	    }
	}
      यदि (side_effects)
	size = build2 (COMPOUND_व्यंजक, sizetype, side_effects, size);
      यदि (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
	  || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
	  || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TASK_REDUCTION)
	{
	  size = size_binop (MINUS_व्यंजक, size, size_one_गाँठ);
	  size = c_fully_fold (size, असत्य, रिक्त);
	  size = save_व्यंजक (size);
	  वृक्ष index_type = build_index_type (size);
	  वृक्ष eltype = वृक्ष_TYPE (first);
	  यावत् (वृक्ष_CODE (eltype) == ARRAY_TYPE)
	    eltype = वृक्ष_TYPE (eltype);
	  वृक्ष type = c_build_array_type (eltype, index_type);
	  वृक्ष ptype = c_build_pointer_type (eltype);
	  यदि (वृक्ष_CODE (वृक्ष_TYPE (t)) == ARRAY_TYPE)
	    t = build_fold_addr_व्यंजक (t);
	  वृक्ष t2 = build_fold_addr_व्यंजक (first);
	  t2 = fold_convert_loc (OMP_CLAUSE_LOCATION (c),
				 ptrdiff_type_गाँठ, t2);
	  t2 = fold_build2_loc (OMP_CLAUSE_LOCATION (c), MINUS_व्यंजक,
				ptrdiff_type_गाँठ, t2,
				fold_convert_loc (OMP_CLAUSE_LOCATION (c),
						  ptrdiff_type_गाँठ, t));
	  t2 = c_fully_fold (t2, असत्य, रिक्त);
	  यदि (वृक्ष_fits_shwi_p (t2))
	    t = build2 (MEM_REF, type, t,
			build_int_cst (ptype, वृक्ष_to_shwi (t2)));
	  अन्यथा
	    {
	      t2 = fold_convert_loc (OMP_CLAUSE_LOCATION (c), sizetype, t2);
	      t = build2_loc (OMP_CLAUSE_LOCATION (c), POINTER_PLUS_व्यंजक,
			      वृक्ष_TYPE (t), t, t2);
	      t = build2 (MEM_REF, type, t, build_int_cst (ptype, 0));
	    }
	  OMP_CLAUSE_DECL (c) = t;
	  प्रत्यागम असत्य;
	}
      first = c_fully_fold (first, असत्य, रिक्त);
      OMP_CLAUSE_DECL (c) = first;
      यदि (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_HAS_DEVICE_ADDR)
	प्रत्यागम असत्य;
      /* Don't set OMP_CLAUSE_SIZE for bare attach/detach clauses.  */
      यदि (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP
	  || (OMP_CLAUSE_MAP_KIND (c) != GOMP_MAP_ATTACH
	      && OMP_CLAUSE_MAP_KIND (c) != GOMP_MAP_DETACH
	      && OMP_CLAUSE_MAP_KIND (c) != GOMP_MAP_FORCE_DETACH))
	{
	  यदि (size)
	    size = c_fully_fold (size, असत्य, रिक्त);
	  OMP_CLAUSE_SIZE (c) = size;
	}

      यदि (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP)
	प्रत्यागम असत्य;

      auto_vec<omp_addr_token *, 10> addr_tokens;

      यदि (!omp_parse_व्यंजक (addr_tokens, first))
	प्रत्यागम सत्य;

      c_omp_address_inspector ai (OMP_CLAUSE_LOCATION (c), t);

      वृक्ष nc = ai.expand_map_clause (c, first, addr_tokens, ort);
      यदि (nc != error_mark_गाँठ)
	{
	  using नामाकाश omp_addr_tokenizer;

	  यदि (ai.maybe_zero_length_array_section (c))
	    OMP_CLAUSE_MAP_MAYBE_ZERO_LENGTH_ARRAY_SECTION (c) = 1;

	  /* !!! If we're accessing a base decl via chained access
	     methods (e.g. multiple indirections), duplicate clause
	     detection won't work properly.  Skip it in that case.  */
	  यदि ((addr_tokens[0]->type == STRUCTURE_BASE
	       || addr_tokens[0]->type == ARRAY_BASE)
	      && addr_tokens[0]->u.structure_base_kind == BASE_DECL
	      && addr_tokens[1]->type == ACCESS_METHOD
	      && omp_access_chain_p (addr_tokens, 1))
	    c = nc;

	  प्रत्यागम असत्य;
	}
    }
  प्रत्यागम असत्य;
}

/* Helper function of finish_omp_clauses.  Clone STMT as if we were making
   an inline call.  But, remap
   the OMP_DECL1 VAR_DECL (omp_out resp. omp_orig) to PLACEHOLDER
   and OMP_DECL2 VAR_DECL (omp_in resp. omp_priv) to DECL.  */

स्थिर वृक्ष
c_clone_omp_udr (वृक्ष stmt, वृक्ष omp_decl1, वृक्ष omp_decl2,
		 वृक्ष decl, वृक्ष placeholder)
{
  copy_body_data id;
  hash_map<वृक्ष, वृक्ष> decl_map;

  decl_map.put (omp_decl1, placeholder);
  decl_map.put (omp_decl2, decl);
  स_रखो (&id, 0, परिमाण (id));
  id.src_fn = DECL_CONTEXT (omp_decl1);
  id.dst_fn = current_function_decl;
  id.src_cfun = DECL_STRUCT_FUNCTION (id.src_fn);
  id.decl_map = &decl_map;

  id.copy_decl = copy_decl_no_change;
  id.transform_call_graph_edges = CB_CGE_DUPLICATE;
  id.transform_new_cfg = सत्य;
  id.transform_return_to_modify = असत्य;
  id.eh_lp_nr = 0;
  walk_वृक्ष (&stmt, copy_वृक्ष_body_r, &id, रिक्त);
  प्रत्यागम stmt;
}

/* Helper function of c_finish_omp_clauses, called via walk_tree.
   Find OMP_CLAUSE_PLACEHOLDER (passed in DATA) in *TP.  */

स्थिर वृक्ष
c_find_omp_placeholder_r (वृक्ष *tp, पूर्णाङ्क *, शून्य *data)
{
  यदि (*tp == (वृक्ष) data)
    प्रत्यागम *tp;
  प्रत्यागम NULL_वृक्ष;
}

/* Similarly, but also walk aggregate fields.  */

संरचना c_find_omp_var_s { वृक्ष var; hash_set<वृक्ष> *pset; };

स्थिर वृक्ष
c_find_omp_var_r (वृक्ष *tp, पूर्णाङ्क *, शून्य *data)
{
  यदि (*tp == ((संरचना c_find_omp_var_s *) data)->var)
    प्रत्यागम *tp;
  यदि (RECORD_OR_UNION_TYPE_P (*tp))
    {
      वृक्ष field;
      hash_set<वृक्ष> *pset = ((संरचना c_find_omp_var_s *) data)->pset;

      प्रति (field = TYPE_FIELDS (*tp); field;
	   field = DECL_CHAIN (field))
	यदि (वृक्ष_CODE (field) == FIELD_DECL)
	  {
	    वृक्ष ret = walk_वृक्ष (&DECL_FIELD_OFFSET (field),
				  c_find_omp_var_r, data, pset);
	    यदि (ret)
	      प्रत्यागम ret;
	    ret = walk_वृक्ष (&DECL_SIZE (field), c_find_omp_var_r, data, pset);
	    यदि (ret)
	      प्रत्यागम ret;
	    ret = walk_वृक्ष (&DECL_SIZE_UNIT (field), c_find_omp_var_r, data,
			     pset);
	    यदि (ret)
	      प्रत्यागम ret;
	    ret = walk_वृक्ष (&वृक्ष_TYPE (field), c_find_omp_var_r, data, pset);
	    यदि (ret)
	      प्रत्यागम ret;
	  }
    }
  अन्यथा यदि (INTEGRAL_TYPE_P (*tp))
    प्रत्यागम walk_वृक्ष (&TYPE_MAX_मूल्य (*tp), c_find_omp_var_r, data,
		      ((संरचना c_find_omp_var_s *) data)->pset);
  प्रत्यागम NULL_वृक्ष;
}

/* Finish OpenMP iterators ITER.  Return true if they are erroneous
   and clauses containing them should be removed.  */

स्थिर तार्किक
c_omp_finish_iterators (वृक्ष iter)
{
  तार्किक ret = असत्य;
  प्रति (वृक्ष it = iter; it; it = वृक्ष_CHAIN (it))
    {
      वृक्ष var = OMP_ITERATOR_VAR (it);
      वृक्ष begin = OMP_ITERATOR_BEGIN (it);
      वृक्ष end = OMP_ITERATOR_END (it);
      वृक्ष step = OMP_ITERATOR_STEP (it);
      वृक्ष orig_step;
      वृक्ष type = वृक्ष_TYPE (var);
      location_t loc = DECL_SOURCE_LOCATION (var);
      यदि (type == error_mark_गाँठ)
	{
	  ret = सत्य;
	  अनुवर्त;
	}
      यदि (!INTEGRAL_TYPE_P (type) && !POINTER_TYPE_P (type))
	{
	  error_at (loc, "iterator %qD has neither integral nor pointer type",
		    var);
	  ret = सत्य;
	  अनुवर्त;
	}
      अन्यथा यदि (TYPE_ATOMIC (type))
	{
	  error_at (loc, "iterator %qD has %<_Atomic%> qualified type", var);
	  ret = सत्य;
	  अनुवर्त;
	}
      अन्यथा यदि (TYPE_READONLY (type))
	{
	  error_at (loc, "iterator %qD has const qualified type", var);
	  ret = सत्य;
	  अनुवर्त;
	}
      अन्यथा यदि (step == error_mark_गाँठ
	       || वृक्ष_TYPE (step) == error_mark_गाँठ)
	{
	  ret = सत्य;
	  अनुवर्त;
	}
      अन्यथा यदि (!INTEGRAL_TYPE_P (वृक्ष_TYPE (step)))
	{
	  error_at (व्यंजक_LOC_OR_LOC (step, loc),
		    "iterator step with non-integral type");
	  ret = सत्य;
	  अनुवर्त;
	}
      begin = c_fully_fold (build_c_cast (loc, type, begin), असत्य, रिक्त);
      end = c_fully_fold (build_c_cast (loc, type, end), असत्य, रिक्त);
      orig_step = save_व्यंजक (c_fully_fold (step, असत्य, रिक्त));
      वृक्ष stype = POINTER_TYPE_P (type) ? sizetype : type;
      step = c_fully_fold (build_c_cast (loc, stype, orig_step), असत्य, रिक्त);
      यदि (POINTER_TYPE_P (type))
	{
	  begin = save_व्यंजक (begin);
	  step = pointer_int_sum (loc, PLUS_व्यंजक, begin, step);
	  step = fold_build2_loc (loc, MINUS_व्यंजक, sizetype,
				  fold_convert (sizetype, step),
				  fold_convert (sizetype, begin));
	  step = fold_convert (ssizetype, step);
	}
      यदि (integer_zerop (step))
	{
	  error_at (loc, "iterator %qD has zero step", var);
	  ret = सत्य;
	  अनुवर्त;
	}

      यदि (begin == error_mark_गाँठ
	  || end == error_mark_गाँठ
	  || step == error_mark_गाँठ
	  || orig_step == error_mark_गाँठ)
	{
	  ret = सत्य;
	  अनुवर्त;
	}
      hash_set<वृक्ष> pset;
      वृक्ष it2;
      प्रति (it2 = वृक्ष_CHAIN (it); it2; it2 = वृक्ष_CHAIN (it2))
	{
	  वृक्ष var2 = OMP_ITERATOR_VAR (it2);
	  वृक्ष begin2 = OMP_ITERATOR_BEGIN (it2);
	  वृक्ष end2 = OMP_ITERATOR_END (it2);
	  वृक्ष step2 = OMP_ITERATOR_STEP (it2);
	  वृक्ष type2 = वृक्ष_TYPE (var2);
	  location_t loc2 = DECL_SOURCE_LOCATION (var2);
	  संरचना c_find_omp_var_s data = { var, &pset };
	  यदि (walk_वृक्ष (&type2, c_find_omp_var_r, &data, &pset))
	    {
	      error_at (loc2,
			"type of iterator %qD refers to outer iterator %qD",
			var2, var);
	      भङ्ग;
	    }
	  अन्यथा यदि (walk_वृक्ष (&begin2, c_find_omp_var_r, &data, &pset))
	    {
	      error_at (व्यंजक_LOC_OR_LOC (begin2, loc2),
			"begin expression refers to outer iterator %qD", var);
	      भङ्ग;
	    }
	  अन्यथा यदि (walk_वृक्ष (&end2, c_find_omp_var_r, &data, &pset))
	    {
	      error_at (व्यंजक_LOC_OR_LOC (end2, loc2),
			"end expression refers to outer iterator %qD", var);
	      भङ्ग;
	    }
	  अन्यथा यदि (walk_वृक्ष (&step2, c_find_omp_var_r, &data, &pset))
	    {
	      error_at (व्यंजक_LOC_OR_LOC (step2, loc2),
			"step expression refers to outer iterator %qD", var);
	      भङ्ग;
	    }
	}
      यदि (it2)
	{
	  ret = सत्य;
	  अनुवर्त;
	}
      OMP_ITERATOR_BEGIN (it) = begin;
      OMP_ITERATOR_END (it) = end;
      OMP_ITERATOR_STEP (it) = step;
      OMP_ITERATOR_ORIG_STEP (it) = orig_step;
    }
  प्रत्यागम ret;
}

/* Ensure that pointers are used in OpenACC attach and detach clauses.
   Return true if an error has been detected.  */

स्थिर तार्किक
c_oacc_check_attachments (वृक्ष c)
{
  यदि (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP)
    प्रत्यागम असत्य;

  /* OpenACC attach / detach clauses must be pointers.  */
  यदि (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_ATTACH
      || OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_DETACH)
    {
      वृक्ष t = OMP_CLAUSE_DECL (c);

      यावत् (वृक्ष_CODE (t) == OMP_ARRAY_SECTION)
	t = वृक्ष_OPERAND (t, 0);

      यदि (वृक्ष_CODE (वृक्ष_TYPE (t)) != POINTER_TYPE)
	{
	  error_at (OMP_CLAUSE_LOCATION (c), "expected pointer in %qs clause",
		    user_omp_clause_code_name (c, सत्य));
	  प्रत्यागम सत्य;
	}
    }

  प्रत्यागम असत्य;
}

/* For all elements of CLAUSES, validate them against their constraints.
   Remove any elements from the list that are invalid.  */

वृक्ष
c_finish_omp_clauses (वृक्ष clauses, गणना c_omp_region_type ort)
{
  bitmap_head generic_head, firstprivate_head, lastprivate_head;
  bitmap_head aligned_head, map_head, map_field_head, map_firstprivate_head;
  bitmap_head oacc_reduction_head, is_on_device_head;
  वृक्ष c, t, type, *pc;
  वृक्ष simdlen = NULL_वृक्ष, safelen = NULL_वृक्ष;
  तार्किक branch_seen = असत्य;
  तार्किक copyprivate_seen = असत्य;
  तार्किक mergeable_seen = असत्य;
  वृक्ष *detach_seen = रिक्त;
  तार्किक linear_variable_step_check = असत्य;
  वृक्ष *nowait_clause = रिक्त;
  वृक्ष *grainsize_seen = रिक्त;
  तार्किक अंक_tasks_seen = असत्य;
  वृक्ष ordered_clause = NULL_वृक्ष;
  वृक्ष schedule_clause = NULL_वृक्ष;
  तार्किक oacc_async = असत्य;
  वृक्ष last_iterators = NULL_वृक्ष;
  तार्किक last_iterators_remove = असत्य;
  वृक्ष *nogroup_seen = रिक्त;
  वृक्ष *order_clause = रिक्त;
  /* 1 if normal/task reduction has been seen, -1 if inscan reduction
     has been seen, -2 if mixed inscan/normal reduction diagnosed.  */
  पूर्णाङ्क reduction_seen = 0;
  तार्किक allocate_seen = असत्य;
  तार्किक implicit_moved = असत्य;
  तार्किक target_in_reduction_seen = असत्य;
  वृक्ष *full_seen = रिक्त;
  तार्किक partial_seen = असत्य;
  तार्किक openacc = (ort & C_ORT_ACC) != 0;
  तार्किक init_seen = असत्य;
  तार्किक init_use_destroy_seen = असत्य;
  वृक्ष init_no_targetsync_clause = NULL_वृक्ष;
  वृक्ष depend_clause = NULL_वृक्ष;

  यदि (!openacc)
    clauses = omp_remove_duplicate_maps (clauses, सत्य);

  bitmap_obstack_initialize (रिक्त);
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

  यदि (openacc)
    प्रति (c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
      यदि (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ASYNC)
	{
	  oacc_async = सत्य;
	  भङ्ग;
	}

  वृक्ष *grp_start_p = रिक्त, grp_sentinel = NULL_वृक्ष;

  प्रति (pc = &clauses, c = clauses; c ; c = *pc)
    {
      तार्किक हटाओ = असत्य;
      तार्किक need_complete = असत्य;
      तार्किक need_implicitly_determined = असत्य;

      /* We've reached the end of a list of expanded nodes.  Reset the group
	 start pointer.  */
      यदि (c == grp_sentinel)
	{
	  यदि (grp_start_p
	      && OMP_CLAUSE_HAS_ITERATORS (*grp_start_p))
	    प्रति (वृक्ष gc = *grp_start_p; gc != grp_sentinel;
		 gc = OMP_CLAUSE_CHAIN (gc))
	      OMP_CLAUSE_ITERATORS (gc) = OMP_CLAUSE_ITERATORS (*grp_start_p);
	  grp_start_p = रिक्त;
	}

      विकल्प (OMP_CLAUSE_CODE (c))
	{
	पक्ष OMP_CLAUSE_SHARED:
	  need_implicitly_determined = सत्य;
	  गच्छ check_dup_generic;

	पक्ष OMP_CLAUSE_PRIVATE:
	  need_complete = सत्य;
	  need_implicitly_determined = सत्य;
	  गच्छ check_dup_generic;

	पक्ष OMP_CLAUSE_REDUCTION:
	  यदि (reduction_seen == 0)
	    reduction_seen = OMP_CLAUSE_REDUCTION_INSCAN (c) ? -1 : 1;
	  अन्यथा यदि (reduction_seen != -2
		   && reduction_seen != (OMP_CLAUSE_REDUCTION_INSCAN (c)
					 ? -1 : 1))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<inscan%> and non-%<inscan%> %<reduction%> clauses "
			"on the same construct");
	      reduction_seen = -2;
	    }
	  /* FALLTHRU */
	पक्ष OMP_CLAUSE_IN_REDUCTION:
	पक्ष OMP_CLAUSE_TASK_REDUCTION:
	  need_implicitly_determined = सत्य;
	  t = OMP_CLAUSE_DECL (c);
	  यदि (वृक्ष_CODE (t) == OMP_ARRAY_SECTION)
	    {
	      यदि (handle_omp_array_sections (c, ort))
		{
		  हटाओ = सत्य;
		  भङ्ग;
		}

	      t = OMP_CLAUSE_DECL (c);
	      यदि (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
		  && OMP_CLAUSE_REDUCTION_INSCAN (c))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<inscan%> %<reduction%> clause with array "
			    "section");
		  हटाओ = सत्य;
		  भङ्ग;
		}
	    }
	  t = require_complete_type (OMP_CLAUSE_LOCATION (c), t);
	  यदि (t == error_mark_गाँठ)
	    {
	      हटाओ = सत्य;
	      भङ्ग;
	    }
	  यदि (oacc_async)
	    c_mark_addressable (t);
	  type = वृक्ष_TYPE (t);
	  यदि (वृक्ष_CODE (t) == MEM_REF)
	    type = वृक्ष_TYPE (type);
	  यदि (वृक्ष_CODE (type) == ARRAY_TYPE)
	    {
	      वृक्ष oatype = type;
	      gcc_assert (वृक्ष_CODE (t) != MEM_REF);
	      यावत् (वृक्ष_CODE (type) == ARRAY_TYPE)
		type = वृक्ष_TYPE (type);
	      यदि (integer_zerop (TYPE_SIZE_UNIT (type)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD in %<reduction%> clause is a zero size array",
			    t);
		  हटाओ = सत्य;
		  भङ्ग;
		}
	      वृक्ष size = size_binop (EXACT_DIV_व्यंजक, TYPE_SIZE_UNIT (oatype),
				      TYPE_SIZE_UNIT (type));
	      यदि (integer_zerop (size))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD in %<reduction%> clause is a zero size array",
			    t);
		  हटाओ = सत्य;
		  भङ्ग;
		}
	      size = size_binop (MINUS_व्यंजक, size, size_one_गाँठ);
	      size = save_व्यंजक (size);
	      वृक्ष index_type = build_index_type (size);
	      वृक्ष atype = c_build_array_type (TYPE_MAIN_VARIANT (type),
					       index_type);
	      atype = c_build_qualified_type (atype, TYPE_QUALS (type));
	      वृक्ष ptype = c_build_pointer_type (type);
	      यदि (वृक्ष_CODE (वृक्ष_TYPE (t)) == ARRAY_TYPE)
		t = build_fold_addr_व्यंजक (t);
	      t = build2 (MEM_REF, atype, t, build_int_cst (ptype, 0));
	      OMP_CLAUSE_DECL (c) = t;
	    }
	  यदि (TYPE_ATOMIC (type))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<_Atomic%> %qE in %<reduction%> clause", t);
	      हटाओ = सत्य;
	      भङ्ग;
	    }
	  यदि (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_REDUCTION
	      || OMP_CLAUSE_REDUCTION_TASK (c))
	    {
	      /* Disallow zero sized or potentially zero sized task
		 reductions.  */
	      यदि (integer_zerop (TYPE_SIZE_UNIT (type)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "zero sized type %qT in %qs clause", type,
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  हटाओ = सत्य;
		  भङ्ग;
		}
	      अन्यथा यदि (वृक्ष_CODE (TYPE_SIZE_UNIT (type)) != INTEGER_CST)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "variable sized type %qT in %qs clause", type,
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  हटाओ = सत्य;
		  भङ्ग;
		}
	    }
	  यदि (OMP_CLAUSE_REDUCTION_PLACEHOLDER (c) == NULL_वृक्ष
	      && (FLOAT_TYPE_P (type)
		  || वृक्ष_CODE (type) == COMPLEX_TYPE))
	    {
	      गणना वृक्ष_code r_code = OMP_CLAUSE_REDUCTION_CODE (c);
	      ध्रुव वर्ण *r_name = रिक्त;

	      विकल्प (r_code)
		{
		पक्ष PLUS_व्यंजक:
		पक्ष MULT_व्यंजक:
		पक्ष MINUS_व्यंजक:
		पक्ष TRUTH_ANDIF_व्यंजक:
		पक्ष TRUTH_ORIF_व्यंजक:
		  भङ्ग;
		पक्ष MIN_व्यंजक:
		  यदि (वृक्ष_CODE (type) == COMPLEX_TYPE)
		    r_name = "min";
		  भङ्ग;
		पक्ष MAX_व्यंजक:
		  यदि (वृक्ष_CODE (type) == COMPLEX_TYPE)
		    r_name = "max";
		  भङ्ग;
		पक्ष BIT_AND_व्यंजक:
		  r_name = "&";
		  भङ्ग;
		पक्ष BIT_XOR_व्यंजक:
		  r_name = "^";
		  भङ्ग;
		पक्ष BIT_IOR_व्यंजक:
		  r_name = "|";
		  भङ्ग;
		स्वभाव:
		  gcc_unreachable ();
		}
	      यदि (r_name)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qE has invalid type for %<reduction(%s)%>",
			    t, r_name);
		  हटाओ = सत्य;
		  भङ्ग;
		}
	    }
	  अन्यथा यदि (OMP_CLAUSE_REDUCTION_PLACEHOLDER (c) == error_mark_गाँठ)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"user defined reduction not found for %qE", t);
	      हटाओ = सत्य;
	      भङ्ग;
	    }
	  अन्यथा यदि (OMP_CLAUSE_REDUCTION_PLACEHOLDER (c))
	    {
	      वृक्ष list = OMP_CLAUSE_REDUCTION_PLACEHOLDER (c);
	      type = TYPE_MAIN_VARIANT (type);
	      वृक्ष placeholder = build_decl (OMP_CLAUSE_LOCATION (c),
					     VAR_DECL, NULL_वृक्ष, type);
	      वृक्ष decl_placeholder = NULL_वृक्ष;
	      OMP_CLAUSE_REDUCTION_PLACEHOLDER (c) = placeholder;
	      DECL_ARTIFICIAL (placeholder) = 1;
	      DECL_IGNORED_P (placeholder) = 1;
	      यदि (वृक्ष_CODE (t) == MEM_REF)
		{
		  decl_placeholder = build_decl (OMP_CLAUSE_LOCATION (c),
						 VAR_DECL, NULL_वृक्ष, type);
		  OMP_CLAUSE_REDUCTION_DECL_PLACEHOLDER (c) = decl_placeholder;
		  DECL_ARTIFICIAL (decl_placeholder) = 1;
		  DECL_IGNORED_P (decl_placeholder) = 1;
		}
	      यदि (वृक्ष_ADDRESSABLE (वृक्ष_VEC_ELT (list, 0)))
		c_mark_addressable (placeholder);
	      यदि (वृक्ष_ADDRESSABLE (वृक्ष_VEC_ELT (list, 1)))
		c_mark_addressable (decl_placeholder ? decl_placeholder
				    : OMP_CLAUSE_DECL (c));
	      OMP_CLAUSE_REDUCTION_MERGE (c)
		= c_clone_omp_udr (वृक्ष_VEC_ELT (list, 2),
				   वृक्ष_VEC_ELT (list, 0),
				   वृक्ष_VEC_ELT (list, 1),
				   decl_placeholder ? decl_placeholder
				   : OMP_CLAUSE_DECL (c), placeholder);
	      OMP_CLAUSE_REDUCTION_MERGE (c)
		= build3_loc (OMP_CLAUSE_LOCATION (c), BIND_व्यंजक,
			      void_type_गाँठ, NULL_वृक्ष,
			      OMP_CLAUSE_REDUCTION_MERGE (c), NULL_वृक्ष);
	      वृक्ष_SIDE_EFFECTS (OMP_CLAUSE_REDUCTION_MERGE (c)) = 1;
	      यदि (वृक्ष_VEC_LENGTH (list) == 6)
		{
		  यदि (वृक्ष_ADDRESSABLE (वृक्ष_VEC_ELT (list, 3)))
		    c_mark_addressable (decl_placeholder ? decl_placeholder
					: OMP_CLAUSE_DECL (c));
		  यदि (वृक्ष_ADDRESSABLE (वृक्ष_VEC_ELT (list, 4)))
		    c_mark_addressable (placeholder);
		  वृक्ष init = वृक्ष_VEC_ELT (list, 5);
		  यदि (init == error_mark_गाँठ)
		    init = DECL_INITIAL (वृक्ष_VEC_ELT (list, 3));
		  OMP_CLAUSE_REDUCTION_INIT (c)
		    = c_clone_omp_udr (init, वृक्ष_VEC_ELT (list, 4),
				       वृक्ष_VEC_ELT (list, 3),
				       decl_placeholder ? decl_placeholder
				       : OMP_CLAUSE_DECL (c), placeholder);
		  यदि (वृक्ष_VEC_ELT (list, 5) == error_mark_गाँठ)
		    {
		      वृक्ष v = decl_placeholder ? decl_placeholder : t;
		      OMP_CLAUSE_REDUCTION_INIT (c)
			= build2 (INIT_व्यंजक, वृक्ष_TYPE (v), v,
				  OMP_CLAUSE_REDUCTION_INIT (c));
		    }
		  यदि (walk_वृक्ष (&OMP_CLAUSE_REDUCTION_INIT (c),
				 c_find_omp_placeholder_r,
				 placeholder, रिक्त))
		    OMP_CLAUSE_REDUCTION_OMP_ORIG_REF (c) = 1;
		}
	      अन्यथा
		{
		  वृक्ष init;
		  वृक्ष v = decl_placeholder ? decl_placeholder : t;
		  यदि (AGGREGATE_TYPE_P (वृक्ष_TYPE (v)))
		    init = build_constructor (वृक्ष_TYPE (v), रिक्त);
		  अन्यथा
		    init = fold_convert (वृक्ष_TYPE (v), integer_zero_गाँठ);
		  OMP_CLAUSE_REDUCTION_INIT (c)
		    = build2 (INIT_व्यंजक, वृक्ष_TYPE (v), v, init);
		}
	      OMP_CLAUSE_REDUCTION_INIT (c)
		= build3_loc (OMP_CLAUSE_LOCATION (c), BIND_व्यंजक,
			      void_type_गाँठ, NULL_वृक्ष,
			       OMP_CLAUSE_REDUCTION_INIT (c), NULL_वृक्ष);
	      वृक्ष_SIDE_EFFECTS (OMP_CLAUSE_REDUCTION_INIT (c)) = 1;
	    }
	  यदि (वृक्ष_CODE (t) == MEM_REF)
	    {
	      यदि (TYPE_SIZE_UNIT (वृक्ष_TYPE (वृक्ष_TYPE (t))) == NULL_वृक्ष
		  || वृक्ष_CODE (TYPE_SIZE_UNIT (वृक्ष_TYPE (वृक्ष_TYPE (t))))
		     != INTEGER_CST)
		{
		  sorry ("variable length element type in array "
			 "%<reduction%> clause");
		  हटाओ = सत्य;
		  भङ्ग;
		}
	      t = वृक्ष_OPERAND (t, 0);
	      यदि (वृक्ष_CODE (t) == POINTER_PLUS_व्यंजक)
		t = वृक्ष_OPERAND (t, 0);
	      यदि (वृक्ष_CODE (t) == ADDR_व्यंजक)
		t = वृक्ष_OPERAND (t, 0);
	    }
	  गच्छ check_dup_generic_t;

	पक्ष OMP_CLAUSE_COPYPRIVATE:
	  copyprivate_seen = सत्य;
	  यदि (nowait_clause)
	    {
	      error_at (OMP_CLAUSE_LOCATION (*nowait_clause),
			"%<nowait%> clause must not be used together "
			"with %<copyprivate%> clause");
	      *nowait_clause = OMP_CLAUSE_CHAIN (*nowait_clause);
	      nowait_clause = रिक्त;
	    }
	  गच्छ check_dup_generic;

	पक्ष OMP_CLAUSE_COPYIN:
	  t = OMP_CLAUSE_DECL (c);
	  यदि (!VAR_P (t) || !DECL_THREAD_LOCAL_P (t))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE must be %<threadprivate%> for %<copyin%>", t);
	      हटाओ = सत्य;
	      भङ्ग;
	    }
	  गच्छ check_dup_generic;

	पक्ष OMP_CLAUSE_LINEAR:
	  यदि (ort != C_ORT_OMP_DECLARE_SIMD)
	    need_implicitly_determined = सत्य;
	  t = OMP_CLAUSE_DECL (c);
	  यदि (ort != C_ORT_OMP_DECLARE_SIMD
	      && OMP_CLAUSE_LINEAR_KIND (c) != OMP_CLAUSE_LINEAR_DEFAULT
	      && OMP_CLAUSE_LINEAR_OLD_LINEAR_MODIFIER (c))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"modifier should not be specified in %<linear%> "
			"clause on %<simd%> or %<for%> constructs when not "
			"using OpenMP 5.2 modifiers");
	      OMP_CLAUSE_LINEAR_KIND (c) = OMP_CLAUSE_LINEAR_DEFAULT;
	    }
	  यदि (!INTEGRAL_TYPE_P (वृक्ष_TYPE (t))
	      && वृक्ष_CODE (वृक्ष_TYPE (t)) != POINTER_TYPE)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"linear clause applied to non-integral non-pointer "
			"variable with type %qT", वृक्ष_TYPE (t));
	      हटाओ = सत्य;
	      भङ्ग;
	    }
	  यदि (TYPE_ATOMIC (वृक्ष_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<_Atomic%> %qD in %<linear%> clause", t);
	      हटाओ = सत्य;
	      भङ्ग;
	    }
	  यदि (ort == C_ORT_OMP_DECLARE_SIMD)
	    {
	      वृक्ष s = OMP_CLAUSE_LINEAR_STEP (c);
	      यदि (वृक्ष_CODE (s) == PARM_DECL)
		{
		  OMP_CLAUSE_LINEAR_VARIABLE_STRIDE (c) = 1;
		  /* map_head bitmap is used as uniform_head if
		     declare_simd.  */
		  यदि (!bitmap_bit_p (&map_head, DECL_UID (s)))
		    linear_variable_step_check = सत्य;
		  गच्छ check_dup_generic;
		}
	      यदि (वृक्ष_CODE (s) != INTEGER_CST)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<linear%> clause step %qE is neither constant "
			    "nor a parameter", s);
		  हटाओ = सत्य;
		  भङ्ग;
		}
	    }
	  यदि (वृक्ष_CODE (वृक्ष_TYPE (OMP_CLAUSE_DECL (c))) == POINTER_TYPE)
	    {
	      वृक्ष s = OMP_CLAUSE_LINEAR_STEP (c);
	      s = pointer_int_sum (OMP_CLAUSE_LOCATION (c), PLUS_व्यंजक,
				   OMP_CLAUSE_DECL (c), s);
	      s = fold_build2_loc (OMP_CLAUSE_LOCATION (c), MINUS_व्यंजक,
				   sizetype, fold_convert (sizetype, s),
				   fold_convert
				     (sizetype, OMP_CLAUSE_DECL (c)));
	      यदि (s == error_mark_गाँठ)
		s = size_one_गाँठ;
	      OMP_CLAUSE_LINEAR_STEP (c) = s;
	    }
	  अन्यथा
	    OMP_CLAUSE_LINEAR_STEP (c)
	      = fold_convert (वृक्ष_TYPE (t), OMP_CLAUSE_LINEAR_STEP (c));
	  गच्छ check_dup_generic;

	check_dup_generic:
	  t = OMP_CLAUSE_DECL (c);
	check_dup_generic_t:
	  यदि (!VAR_P (t) && वृक्ष_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %qs", t,
			omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	      हटाओ = सत्य;
	    }
	  अन्यथा यदि ((openacc && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION)
		   || (ort == C_ORT_OMP
		       && (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_USE_DEVICE_PTR
			   || (OMP_CLAUSE_CODE (c)
			       == OMP_CLAUSE_USE_DEVICE_ADDR)))
		   || (ort == C_ORT_OMP_TARGET
		       && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION))
	    {
	      यदि (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
		  && (bitmap_bit_p (&generic_head, DECL_UID (t))
		      || bitmap_bit_p (&firstprivate_head, DECL_UID (t))))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in data-sharing "
			    "clauses", t);
		  हटाओ = सत्य;
		  भङ्ग;
		}
	      यदि (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION)
		target_in_reduction_seen = सत्य;
	      यदि (bitmap_bit_p (&oacc_reduction_head, DECL_UID (t)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    openacc
			    ? "%qD appears more than once in reduction clauses"
			    : "%qD appears more than once in data clauses",
			    t);
		  हटाओ = सत्य;
		}
	      अन्यथा
		bitmap_set_bit (&oacc_reduction_head, DECL_UID (t));
	    }
	  अन्यथा यदि (bitmap_bit_p (&generic_head, DECL_UID (t))
		   || bitmap_bit_p (&firstprivate_head, DECL_UID (t))
		   || bitmap_bit_p (&lastprivate_head, DECL_UID (t))
		   || bitmap_bit_p (&map_firstprivate_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in data clauses", t);
	      हटाओ = सत्य;
	    }
	  अन्यथा यदि ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_PRIVATE
		    || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_HAS_DEVICE_ADDR
		    || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IS_DEVICE_PTR)
		   && bitmap_bit_p (&map_head, DECL_UID (t)))
	    {
	      यदि (openacc)
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears more than once in data clauses", t);
	      अन्यथा
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears both in data and map clauses", t);
	      हटाओ = सत्य;
	    }
	  अन्यथा
	    bitmap_set_bit (&generic_head, DECL_UID (t));
	  भङ्ग;

	पक्ष OMP_CLAUSE_FIRSTPRIVATE:
	  यदि (OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (c) && !implicit_moved)
	    {
	    move_implicit:
	      implicit_moved = सत्य;
	      /* Move firstprivate and map clauses with
		 OMP_CLAUSE_{FIRSTPRIVATE,MAP}_IMPLICIT set to the end of
		 clauses chain.  */
	      वृक्ष cl1 = NULL_वृक्ष, cl2 = NULL_वृक्ष;
	      वृक्ष *pc1 = pc, *pc2 = &cl1, *pc3 = &cl2;
	      यावत् (*pc1)
		यदि (OMP_CLAUSE_CODE (*pc1) == OMP_CLAUSE_FIRSTPRIVATE
		    && OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (*pc1))
		  {
		    *pc3 = *pc1;
		    pc3 = &OMP_CLAUSE_CHAIN (*pc3);
		    *pc1 = OMP_CLAUSE_CHAIN (*pc1);
		  }
		अन्यथा यदि (OMP_CLAUSE_CODE (*pc1) == OMP_CLAUSE_MAP
			 && OMP_CLAUSE_MAP_IMPLICIT (*pc1))
		  {
		    *pc2 = *pc1;
		    pc2 = &OMP_CLAUSE_CHAIN (*pc2);
		    *pc1 = OMP_CLAUSE_CHAIN (*pc1);
		  }
		अन्यथा
		  pc1 = &OMP_CLAUSE_CHAIN (*pc1);
	      *pc3 = रिक्त;
	      *pc2 = cl2;
	      *pc1 = cl1;
	      अनुवर्त;
	    }
	  t = OMP_CLAUSE_DECL (c);
	  need_complete = सत्य;
	  need_implicitly_determined = सत्य;
	  यदि (!VAR_P (t) && वृक्ष_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %<firstprivate%>", t);
	      हटाओ = सत्य;
	    }
	  अन्यथा यदि (OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (c)
		   && !OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT_TARGET (c)
		   && bitmap_bit_p (&map_firstprivate_head, DECL_UID (t)))
	    हटाओ = सत्य;
	  अन्यथा यदि (bitmap_bit_p (&generic_head, DECL_UID (t))
		   || bitmap_bit_p (&firstprivate_head, DECL_UID (t))
		   || bitmap_bit_p (&map_firstprivate_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in data clauses", t);
	      हटाओ = सत्य;
	    }
	  अन्यथा यदि (bitmap_bit_p (&map_head, DECL_UID (t))
		   || bitmap_bit_p (&map_field_head, DECL_UID (t)))
	    {
	      यदि (openacc)
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears more than once in data clauses", t);
	      अन्यथा यदि (OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (c)
		       && !OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT_TARGET (c))
		/* Silently drop the clause.  */;
	      अन्यथा
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears both in data and map clauses", t);
	      हटाओ = सत्य;
	    }
	  अन्यथा
	    bitmap_set_bit (&firstprivate_head, DECL_UID (t));
	  भङ्ग;

	पक्ष OMP_CLAUSE_LASTPRIVATE:
	  t = OMP_CLAUSE_DECL (c);
	  need_complete = सत्य;
	  need_implicitly_determined = सत्य;
	  यदि (!VAR_P (t) && वृक्ष_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %<lastprivate%>", t);
	      हटाओ = सत्य;
	    }
	  अन्यथा यदि (bitmap_bit_p (&generic_head, DECL_UID (t))
		   || bitmap_bit_p (&lastprivate_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
		     "%qE appears more than once in data clauses", t);
	      हटाओ = सत्य;
	    }
	  अन्यथा
	    bitmap_set_bit (&lastprivate_head, DECL_UID (t));
	  भङ्ग;

	पक्ष OMP_CLAUSE_ALIGNED:
	  t = OMP_CLAUSE_DECL (c);
	  यदि (!VAR_P (t) && वृक्ष_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in %<aligned%> clause", t);
	      हटाओ = सत्य;
	    }
	  अन्यथा यदि (!POINTER_TYPE_P (वृक्ष_TYPE (t))
		   && वृक्ष_CODE (वृक्ष_TYPE (t)) != ARRAY_TYPE)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE in %<aligned%> clause is neither a pointer nor "
			"an array", t);
	      हटाओ = सत्य;
	    }
	  अन्यथा यदि (TYPE_ATOMIC (वृक्ष_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<_Atomic%> %qD in %<aligned%> clause", t);
	      हटाओ = सत्य;
	      भङ्ग;
	    }
	  अन्यथा यदि (bitmap_bit_p (&aligned_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in %<aligned%> clauses",
			t);
	      हटाओ = सत्य;
	    }
	  अन्यथा
	    bitmap_set_bit (&aligned_head, DECL_UID (t));
	  भङ्ग;

	पक्ष OMP_CLAUSE_NONTEMPORAL:
	  t = OMP_CLAUSE_DECL (c);
	  यदि (!VAR_P (t) && वृक्ष_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in %<nontemporal%> clause", t);
	      हटाओ = सत्य;
	    }
	  अन्यथा यदि (bitmap_bit_p (&oacc_reduction_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in %<nontemporal%> "
			"clauses", t);
	      हटाओ = सत्य;
	    }
	  अन्यथा
	    bitmap_set_bit (&oacc_reduction_head, DECL_UID (t));
	  भङ्ग;

	पक्ष OMP_CLAUSE_ALLOCATE:
	  t = OMP_CLAUSE_DECL (c);
	  यदि (!VAR_P (t) && वृक्ष_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in %<allocate%> clause", t);
	      हटाओ = सत्य;
	    }
	  अन्यथा यदि (bitmap_bit_p (&aligned_head, DECL_UID (t)))
	    {
	      warning_at (OMP_CLAUSE_LOCATION (c), OPT_Wopenmp,
			  "%qE appears more than once in %<allocate%> clauses",
			  t);
	      हटाओ = सत्य;
	    }
	  अन्यथा
	    {
	      bitmap_set_bit (&aligned_head, DECL_UID (t));
	      यदि (!OMP_CLAUSE_ALLOCATE_COMBINED (c))
		allocate_seen = सत्य;
	    }
	  भङ्ग;

	पक्ष OMP_CLAUSE_DOACROSS:
	  t = OMP_CLAUSE_DECL (c);
	  यदि (t == NULL_वृक्ष)
	    भङ्ग;
	  यदि (OMP_CLAUSE_DOACROSS_KIND (c) == OMP_CLAUSE_DOACROSS_SINK)
	    {
	      gcc_assert (वृक्ष_CODE (t) == वृक्ष_LIST);
	      प्रति (; t; t = वृक्ष_CHAIN (t))
		{
		  वृक्ष decl = वृक्ष_मूल्य (t);
		  यदि (वृक्ष_CODE (वृक्ष_TYPE (decl)) == POINTER_TYPE)
		    {
		      वृक्ष offset = वृक्ष_PURPOSE (t);
		      तार्किक neg = wi::neg_p (wi::to_wide (offset));
		      offset = fold_unary (ABS_व्यंजक, वृक्ष_TYPE (offset), offset);
		      वृक्ष t2 = pointer_int_sum (OMP_CLAUSE_LOCATION (c),
						 neg ? MINUS_व्यंजक : PLUS_व्यंजक,
						 decl, offset);
		      t2 = fold_build2_loc (OMP_CLAUSE_LOCATION (c), MINUS_व्यंजक,
					    sizetype,
					    fold_convert (sizetype, t2),
					    fold_convert (sizetype, decl));
		      यदि (t2 == error_mark_गाँठ)
			{
			  हटाओ = सत्य;
			  भङ्ग;
			}
		      वृक्ष_PURPOSE (t) = t2;
		    }
		}
	      भङ्ग;
	    }
	  gcc_unreachable ();

	पक्ष OMP_CLAUSE_USES_ALLOCATORS:
	  t = OMP_CLAUSE_USES_ALLOCATORS_ALLOCATOR (c);
	  यदि (t == error_mark_गाँठ)
	    {
	      हटाओ = सत्य;
	      भङ्ग;
	    }
	  यदि ((VAR_P (t) || वृक्ष_CODE (t) == PARM_DECL)
	      && (bitmap_bit_p (&generic_head, DECL_UID (t))
		  || bitmap_bit_p (&map_head, DECL_UID (t))
		  || bitmap_bit_p (&firstprivate_head, DECL_UID (t))
		  || bitmap_bit_p (&lastprivate_head, DECL_UID (t))))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in data clauses", t);
	      हटाओ = सत्य;
	      भङ्ग;
	    }
	  अन्यथा
	    bitmap_set_bit (&generic_head, DECL_UID (t));
	  यदि (वृक्ष_CODE (वृक्ष_TYPE (t)) != ENUMERAL_TYPE
	      || म_भेद (IDENTIFIER_POINTER (TYPE_IDENTIFIER (वृक्ष_TYPE (t))),
			 "omp_allocator_handle_t") != 0)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"allocator %qE must be of %<omp_allocator_handle_t%> "
			"type", t);
	      हटाओ = सत्य;
	      भङ्ग;
	    }
	  वृक्ष init;
	  यदि (!DECL_P (t)
	      || (वृक्ष_CODE (t) == CONST_DECL
		  && ((init = DECL_INITIAL(t)) == nullptr
		      || वृक्ष_CODE (init) != INTEGER_CST
		      || ((wi::to_widest (init) < 0
			   || wi::to_widest (init) > GOMP_OMP_PREDEF_ALLOC_MAX)
			  && (wi::to_widest (init) < GOMP_OMPX_PREDEF_ALLOC_MIN
			      || (wi::to_widest (init)
				  > GOMP_OMPX_PREDEF_ALLOC_MAX))))))
	    {
	      हटाओ = सत्य;
	      error_at (OMP_CLAUSE_LOCATION (c),
			"allocator %qE must be either a variable or a "
			"predefined allocator", t);
	      भङ्ग;
	    }
	  अन्यथा यदि (वृक्ष_CODE (t) == CONST_DECL)
	    {
	      /* omp_null_allocator is ignored and for predefined allocators,
		 no special handling is required; thus, mark them removed. */
	      हटाओ = सत्य;

	      यदि (OMP_CLAUSE_USES_ALLOCATORS_MEMSPACE (c)
		  || OMP_CLAUSE_USES_ALLOCATORS_TRAITS (c))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "modifiers cannot be used with predefined "
			    "allocator %qE", t);
		  भङ्ग;
		}
	    }
	  t = OMP_CLAUSE_USES_ALLOCATORS_MEMSPACE (c);
	  यदि (t == error_mark_गाँठ)
	    {
	      हटाओ = सत्य;
	      भङ्ग;
	    }
	  यदि (t != NULL_वृक्ष
	      && ((वृक्ष_CODE (t) != CONST_DECL && वृक्ष_CODE (t) != INTEGER_CST)
		  || वृक्ष_CODE (वृक्ष_TYPE (t)) != ENUMERAL_TYPE
		  || म_भेद (IDENTIFIER_POINTER (TYPE_IDENTIFIER (वृक्ष_TYPE (t))),
			     "omp_memspace_handle_t") != 0))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c), "memspace modifier %qE must be"
			" constant enum of %<omp_memspace_handle_t%> type", t);
	      हटाओ = सत्य;
	      भङ्ग;
	    }
	  t = OMP_CLAUSE_USES_ALLOCATORS_TRAITS (c);
	  यदि (t == error_mark_गाँठ)
	    {
	      हटाओ = सत्य;
	      भङ्ग;
	    }
	  यदि (t != NULL_वृक्ष
	      && t != error_mark_गाँठ
	      && (DECL_EXTERNAL (t)
		  || वृक्ष_CODE (t) == PARM_DECL))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c), "traits array %qE must be "
			"defined in same scope as the construct on which the "
			"clause appears", t);
	      हटाओ = सत्य;
	    }
	  यदि (t != NULL_वृक्ष)
	    {
	      तार्किक type_err = असत्य;

	      यदि (वृक्ष_CODE (वृक्ष_TYPE (t)) != ARRAY_TYPE
		  || DECL_SIZE (t) == NULL_वृक्ष
		  || !COMPLETE_TYPE_P (वृक्ष_TYPE (t)))
		type_err = सत्य;
	      अन्यथा
		{
		  वृक्ष elem_t = वृक्ष_TYPE (वृक्ष_TYPE (t));
		  यदि (वृक्ष_CODE (elem_t) != RECORD_TYPE
		      || म_भेद (IDENTIFIER_POINTER (TYPE_IDENTIFIER (elem_t)),
				 "omp_alloctrait_t") != 0
		      || !TYPE_READONLY (elem_t))
		    type_err = सत्य;
		}
	      यदि (type_err)
		{
		  यदि (t != error_mark_गाँठ)
		    error_at (OMP_CLAUSE_LOCATION (c), "traits array %qE must "
			      "be of %<const omp_alloctrait_t []%> type", t);
		  अन्यथा
		    error_at (OMP_CLAUSE_LOCATION (c), "traits array must "
			      "be of %<const omp_alloctrait_t []%> type");
		  हटाओ = सत्य;
		}
	      अन्यथा
		{
		  वृक्ष cst_val = decl_constant_मूल्य_1 (t, सत्य);
		  यदि (cst_val == t)
		    {
		      error_at (OMP_CLAUSE_LOCATION (c), "traits array must be "
				"initialized with constants");

		      हटाओ = सत्य;
		    }
		}
	    }
	  यदि (हटाओ)
	    भङ्ग;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  अनुवर्त;
	पक्ष OMP_CLAUSE_DEPEND:
	  depend_clause = c;
	  /* FALLTHRU */
	पक्ष OMP_CLAUSE_AFFINITY:
	  t = OMP_CLAUSE_DECL (c);
	  यदि (OMP_ITERATOR_DECL_P (t))
	    {
	      यदि (वृक्ष_PURPOSE (t) != last_iterators)
		last_iterators_remove
		  = c_omp_finish_iterators (वृक्ष_PURPOSE (t));
	      last_iterators = वृक्ष_PURPOSE (t);
	      t = वृक्ष_मूल्य (t);
	      यदि (last_iterators_remove)
		t = error_mark_गाँठ;
	    }
	  अन्यथा
	    last_iterators = NULL_वृक्ष;
	  यदि (वृक्ष_CODE (t) == OMP_ARRAY_SECTION)
	    {
	      यदि (handle_omp_array_sections (c, ort))
		हटाओ = सत्य;
	      अन्यथा यदि (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
		       && OMP_CLAUSE_DEPEND_KIND (c) == OMP_CLAUSE_DEPEND_DEPOBJ)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<depend%> clause with %<depobj%> dependence "
			    "type on array section");
		  हटाओ = सत्य;
		}
	      भङ्ग;
	    }
	  यदि (t == error_mark_गाँठ)
	    हटाओ = सत्य;
	  अन्यथा यदि (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
		   && t == ridpointers[RID_OMP_ALL_MEMORY])
	    {
	      यदि (OMP_CLAUSE_DEPEND_KIND (c) != OMP_CLAUSE_DEPEND_OUT
		  && OMP_CLAUSE_DEPEND_KIND (c) != OMP_CLAUSE_DEPEND_INOUT)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<omp_all_memory%> used with %<depend%> kind "
			    "other than %<out%> or %<inout%>");
		  हटाओ = सत्य;
		}
	    }
	  अन्यथा यदि (!lvalue_p (t))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not lvalue expression nor array section in "
			"%qs clause", t,
			omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	      हटाओ = सत्य;
	    }
	  अन्यथा यदि (वृक्ष_CODE (t) == COMPONENT_REF
		   && DECL_C_BIT_FIELD (वृक्ष_OPERAND (t, 1)))
	    {
	      gcc_assert (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
			  || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY);
	      error_at (OMP_CLAUSE_LOCATION (c),
			"bit-field %qE in %qs clause", t,
			omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	      हटाओ = सत्य;
	    }
	  अन्यथा यदि (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
		   && OMP_CLAUSE_DEPEND_KIND (c) == OMP_CLAUSE_DEPEND_DEPOBJ)
	    {
	      यदि (!c_omp_depend_t_p (वृक्ष_TYPE (t)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qE does not have %<omp_depend_t%> type in "
			    "%<depend%> clause with %<depobj%> dependence "
			    "type", t);
		  हटाओ = सत्य;
		}
	    }
	  अन्यथा यदि (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
		   && c_omp_depend_t_p (वृक्ष_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE should not have %<omp_depend_t%> type in "
			"%<depend%> clause with dependence type other than "
			"%<depobj%>", t);
	      हटाओ = सत्य;
	    }
	  यदि (!हटाओ)
	    {
	      यदि (t == ridpointers[RID_OMP_ALL_MEMORY])
		t = null_pointer_गाँठ;
	      अन्यथा
		{
		  वृक्ष addr = build_unary_op (OMP_CLAUSE_LOCATION (c),
					      ADDR_व्यंजक, t, असत्य);
		  यदि (addr == error_mark_गाँठ)
		    {
		      हटाओ = सत्य;
		      भङ्ग;
		    }
		  t = build_indirect_ref (OMP_CLAUSE_LOCATION (c), addr,
					  RO_UNARY_STAR);
		  यदि (t == error_mark_गाँठ)
		    {
		      हटाओ = सत्य;
		      भङ्ग;
		    }
		}
	      यदि (OMP_ITERATOR_DECL_P (OMP_CLAUSE_DECL (c)))
		वृक्ष_मूल्य (OMP_CLAUSE_DECL (c)) = t;
	      अन्यथा
		OMP_CLAUSE_DECL (c) = t;
	    }
	  भङ्ग;

	पक्ष OMP_CLAUSE_MAP:
	  यदि (OMP_CLAUSE_MAP_IMPLICIT (c) && !implicit_moved)
	    गच्छ move_implicit;
	  यदि (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_धकेलो_MAPPER_NAME
	      || OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_निकालो_MAPPER_NAME)
	    {
	      हटाओ = सत्य;
	      भङ्ग;
	    }
	  /* FALLTHRU */
	पक्ष OMP_CLAUSE_TO:
	पक्ष OMP_CLAUSE_FROM:
	  यदि (OMP_CLAUSE_ITERATORS (c)
	      && c_omp_finish_iterators (OMP_CLAUSE_ITERATORS (c)))
	    {
	      t = error_mark_गाँठ;
	      भङ्ग;
	    }
	  /* FALLTHRU */
	पक्ष OMP_CLAUSE__CACHE_:
	  {
	    using नामाकाश omp_addr_tokenizer;
	    auto_vec<omp_addr_token *, 10> addr_tokens;

	    t = OMP_CLAUSE_DECL (c);
	    यदि (वृक्ष_CODE (t) == OMP_ARRAY_SECTION)
	      {
		grp_start_p = pc;
		grp_sentinel = OMP_CLAUSE_CHAIN (c);

		यदि (handle_omp_array_sections (c, ort))
		  हटाओ = सत्य;
		अन्यथा
		  {
		    t = OMP_CLAUSE_DECL (c);
		    यदि (!omp_mappable_type (वृक्ष_TYPE (t)))
		      {
			error_at (OMP_CLAUSE_LOCATION (c),
				  "array section does not have mappable type "
				  "in %qs clause",
				  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
			हटाओ = सत्य;
		      }
		    अन्यथा यदि (TYPE_ATOMIC (वृक्ष_TYPE (t)))
		      {
			error_at (OMP_CLAUSE_LOCATION (c),
				  "%<_Atomic%> %qE in %qs clause", t,
				  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
			हटाओ = सत्य;
		      }
		    यावत् (वृक्ष_CODE (t) == ARRAY_REF)
		      t = वृक्ष_OPERAND (t, 0);

		    c_omp_address_inspector ai (OMP_CLAUSE_LOCATION (c), t);

		    यदि (!omp_parse_व्यंजक (addr_tokens, t))
		      {
			sorry_at (OMP_CLAUSE_LOCATION (c),
				  "unsupported map expression %qE",
				  OMP_CLAUSE_DECL (c));
			हटाओ = सत्य;
			भङ्ग;
		      }

		    /* This check is to determine if this will be the only map
		       node created for this clause.  Otherwise, we'll check
		       the following FIRSTPRIVATE_POINTER or ATTACH_DETACH
		       node on the next iteration(s) of the loop.   */
		    यदि (addr_tokens.length () >= 4
			&& addr_tokens[0]->type == STRUCTURE_BASE
			&& addr_tokens[0]->u.structure_base_kind == BASE_DECL
			&& addr_tokens[1]->type == ACCESS_METHOD
			&& addr_tokens[2]->type == COMPONENT_SELECTOR
			&& addr_tokens[3]->type == ACCESS_METHOD
			&& (addr_tokens[3]->u.access_kind == ACCESS_DIRECT
			    || (addr_tokens[3]->u.access_kind
				== ACCESS_INDEXED_ARRAY)))
		      {
			वृक्ष rt = addr_tokens[1]->व्यंजक;

			gcc_assert (DECL_P (rt));

			यदि (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
			    && OMP_CLAUSE_MAP_IMPLICIT (c)
			    && (bitmap_bit_p (&map_head, DECL_UID (rt))
				|| bitmap_bit_p (&map_field_head, DECL_UID (rt))
				|| bitmap_bit_p (&map_firstprivate_head,
						 DECL_UID (rt))))
			  {
			    हटाओ = सत्य;
			    भङ्ग;
			  }
			यदि (bitmap_bit_p (&map_field_head, DECL_UID (rt)))
			  भङ्ग;
			यदि (bitmap_bit_p (&map_head, DECL_UID (rt)))
			  {
			    यदि (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP)
			      error_at (OMP_CLAUSE_LOCATION (c),
					"%qD appears more than once in motion "
					"clauses", rt);
			    अन्यथा यदि (openacc)
			      error_at (OMP_CLAUSE_LOCATION (c),
					"%qD appears more than once in data "
					"clauses", rt);
			    अन्यथा
			      error_at (OMP_CLAUSE_LOCATION (c),
					"%qD appears more than once in map "
					"clauses", rt);
			    हटाओ = सत्य;
			  }
			अन्यथा
			  {
			    bitmap_set_bit (&map_head, DECL_UID (rt));
			    bitmap_set_bit (&map_field_head, DECL_UID (rt));
			  }
		      }
		  }
		यदि (c_oacc_check_attachments (c))
		  हटाओ = सत्य;
		यदि (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		    && (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_ATTACH
			|| OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_DETACH)
		    && !OMP_CLAUSE_SIZE (c))
		  /* In this case, we have a single array element which is a
		     pointer, and we already set OMP_CLAUSE_SIZE in
		     handle_omp_array_sections above.  For attach/detach
		     clauses, reset the OMP_CLAUSE_SIZE (representing a bias)
		     to zero here.  */
		  OMP_CLAUSE_SIZE (c) = size_zero_गाँठ;
		भङ्ग;
	      }
	    अन्यथा यदि (!omp_parse_व्यंजक (addr_tokens, t))
	      {
		sorry_at (OMP_CLAUSE_LOCATION (c),
			  "unsupported map expression %qE",
			  OMP_CLAUSE_DECL (c));
		हटाओ = सत्य;
		भङ्ग;
	      }
	    यदि (t == error_mark_गाँठ)
	      {
		हटाओ = सत्य;
		भङ्ग;
	      }

	    वृक्ष attr;
	    यदि (DECL_P (t)
		&& OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		&& (attr = lookup_attribute ("omp declare target",
					     DECL_ATTRIBUTES (t)))
		&& मूल्य_member (get_identifier ("local"),
				 वृक्ष_मूल्य (attr)))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "device-local variable %qD cannot appear "
			  "in map clause", t);
		हटाओ = सत्य;
		भङ्ग;
	      }

	    /* OpenACC attach / detach clauses must be pointers.  */
	    यदि (c_oacc_check_attachments (c))
	      {
		हटाओ = सत्य;
		भङ्ग;
	      }
	    यदि (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		&& (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_ATTACH
		    || OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_DETACH)
		&& !OMP_CLAUSE_SIZE (c))
	      /* For attach/detach clauses, set OMP_CLAUSE_SIZE (representing a
		 bias) to zero here, so it is not set erroneously to the pointer
		 size later on in gimplify.cc.  */
	      OMP_CLAUSE_SIZE (c) = size_zero_गाँठ;

	    c_omp_address_inspector ai (OMP_CLAUSE_LOCATION (c), t);

	    यदि (!ai.check_clause (c))
	      {
		हटाओ = सत्य;
		भङ्ग;
	      }

	    यदि (!ai.map_supported_p ())
	      {
		sorry_at (OMP_CLAUSE_LOCATION (c),
			  "unsupported map expression %qE",
			  OMP_CLAUSE_DECL (c));
		हटाओ = सत्य;
		भङ्ग;
	      }

	    gcc_assert ((addr_tokens[0]->type == ARRAY_BASE
			 || addr_tokens[0]->type == STRUCTURE_BASE)
			&& addr_tokens[1]->type == ACCESS_METHOD);

	    t = addr_tokens[1]->व्यंजक;

	    यदि (addr_tokens[0]->u.structure_base_kind != BASE_DECL)
	      गच्छ skip_decl_checks;

	    /* For OpenMP, we can access a struct "t" and "t.d" on the same
	       mapping.  OpenACC allows multiple fields of the same structure
	       to be written.  */
	    यदि (addr_tokens[0]->type == STRUCTURE_BASE
		&& (bitmap_bit_p (&map_field_head, DECL_UID (t))
		    || (!openacc && bitmap_bit_p (&map_head, DECL_UID (t)))))
	      गच्छ skip_decl_checks;

	    यदि (!VAR_P (t) && वृक्ष_CODE (t) != PARM_DECL)
	      {
		यदि (ort != C_ORT_ACC && व्यंजक_P (t))
		  भङ्ग;

		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is not a variable in %qs clause", t,
			  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		हटाओ = सत्य;
	      }
	    अन्यथा यदि (VAR_P (t) && DECL_THREAD_LOCAL_P (t))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD is threadprivate variable in %qs clause", t,
			  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		हटाओ = सत्य;
	      }
	    अन्यथा यदि ((OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP
		      || (OMP_CLAUSE_MAP_KIND (c)
			  != GOMP_MAP_FIRSTPRIVATE_POINTER))
		     && !c_mark_addressable (t))
	      हटाओ = सत्य;
	    अन्यथा यदि (!(OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		       && (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_POINTER
			   || (OMP_CLAUSE_MAP_KIND (c)
			       == GOMP_MAP_FIRSTPRIVATE_POINTER)
			   || (OMP_CLAUSE_MAP_KIND (c)
			       == GOMP_MAP_FORCE_DEVICEPTR)))
		     && t == OMP_CLAUSE_DECL (c)
		     && !omp_mappable_type (वृक्ष_TYPE (t)))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD does not have a mappable type in %qs clause", t,
			  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		हटाओ = सत्य;
	      }
	    अन्यथा यदि (वृक्ष_TYPE (t) == error_mark_गाँठ)
	      हटाओ = सत्य;
	    अन्यथा यदि (TYPE_ATOMIC (strip_array_types (वृक्ष_TYPE (t))))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%<_Atomic%> %qE in %qs clause", t,
			  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		हटाओ = सत्य;
	      }
	    अन्यथा यदि (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		     && OMP_CLAUSE_MAP_IMPLICIT (c)
		     && (bitmap_bit_p (&map_head, DECL_UID (t))
			 || bitmap_bit_p (&map_field_head, DECL_UID (t))
			 || bitmap_bit_p (&map_firstprivate_head,
					  DECL_UID (t))))
	      हटाओ = सत्य;
	    अन्यथा यदि (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		     && (OMP_CLAUSE_MAP_KIND (c)
			 == GOMP_MAP_FIRSTPRIVATE_POINTER))
	      {
		यदि (bitmap_bit_p (&generic_head, DECL_UID (t))
		    || bitmap_bit_p (&firstprivate_head, DECL_UID (t))
		    || bitmap_bit_p (&map_firstprivate_head, DECL_UID (t)))
		  {
		    error_at (OMP_CLAUSE_LOCATION (c),
			      "%qD appears more than once in data clauses", t);
		    हटाओ = सत्य;
		  }
		अन्यथा यदि (bitmap_bit_p (&map_head, DECL_UID (t))
			 && !bitmap_bit_p (&map_field_head, DECL_UID (t))
			 && openacc)
		  {
		    error_at (OMP_CLAUSE_LOCATION (c),
			      "%qD appears more than once in data clauses", t);
		    हटाओ = सत्य;
		  }
		अन्यथा
		  bitmap_set_bit (&map_firstprivate_head, DECL_UID (t));
	      }
	    अन्यथा यदि (bitmap_bit_p (&map_head, DECL_UID (t))
		     && !bitmap_bit_p (&map_field_head, DECL_UID (t))
		     && ort != C_ORT_OMP
		     && ort != C_ORT_OMP_TARGET
		     && ort != C_ORT_OMP_EXIT_DATA)
	      {
		यदि (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP)
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in motion clauses", t);
		अन्यथा यदि (openacc)
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in data clauses", t);
		अन्यथा
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in map clauses", t);
		हटाओ = सत्य;
	      }
	    अन्यथा यदि (openacc && bitmap_bit_p (&generic_head, DECL_UID (t)))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears more than once in data clauses", t);
		हटाओ = सत्य;
	      }
	    अन्यथा यदि (bitmap_bit_p (&firstprivate_head, DECL_UID (t))
		     || bitmap_bit_p (&is_on_device_head, DECL_UID (t)))
	      {
		यदि (openacc)
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in data clauses", t);
		अन्यथा
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears both in data and map clauses", t);
		हटाओ = सत्य;
	      }
	    अन्यथा यदि (!omp_access_chain_p (addr_tokens, 1))
	      {
		bitmap_set_bit (&map_head, DECL_UID (t));
		यदि (t != OMP_CLAUSE_DECL (c)
		    && वृक्ष_CODE (OMP_CLAUSE_DECL (c)) == COMPONENT_REF)
		  bitmap_set_bit (&map_field_head, DECL_UID (t));
	      }

	  skip_decl_checks:
	    /* If we call omp_expand_map_clause in handle_omp_array_sections,
	       the containing loop (here) iterates through the new nodes
	       created by that expansion.  Avoid expanding those again (just
	       by checking the node type).  */
	    यदि (!हटाओ
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
		वृक्ष nc = ai.expand_map_clause (c, OMP_CLAUSE_DECL (c),
						addr_tokens, ort);
		यदि (nc != error_mark_गाँठ)
		  c = nc;
	      }
	  }
	  भङ्ग;

	पक्ष OMP_CLAUSE_ENTER:
	पक्ष OMP_CLAUSE_LINK:
	पक्ष OMP_CLAUSE_LOCAL:
	  t = OMP_CLAUSE_DECL (c);
	  ध्रुव वर्ण *cname;
	  cname = omp_clause_code_name[OMP_CLAUSE_CODE (c)];
	  यदि (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ENTER
	      && OMP_CLAUSE_ENTER_TO (c))
	    cname = "to";
	  यदि (वृक्ष_CODE (t) == FUNCTION_DECL
	      && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ENTER)
	    ;
	  अन्यथा यदि (!VAR_P (t))
	    {
	      यदि (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ENTER)
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is neither a variable nor a function name in "
			  "clause %qs", t, cname);
	      अन्यथा
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is not a variable in clause %qs", t, cname);
	      हटाओ = सत्य;
	    }
	  अन्यथा यदि (DECL_THREAD_LOCAL_P (t))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD is threadprivate variable in %qs clause", t,
			cname);
	      हटाओ = सत्य;
	    }
	  अन्यथा यदि (!omp_mappable_type (वृक्ष_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD does not have a mappable type in %qs clause", t,
			cname);
	      हटाओ = सत्य;
	    }
	  यदि (हटाओ)
	    भङ्ग;
	  यदि (bitmap_bit_p (&generic_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once on the same "
			"%<declare target%> directive", t);
	      हटाओ = सत्य;
	    }
	  अन्यथा
	    bitmap_set_bit (&generic_head, DECL_UID (t));
	  भङ्ग;

	पक्ष OMP_CLAUSE_UNIFORM:
	  t = OMP_CLAUSE_DECL (c);
	  यदि (वृक्ष_CODE (t) != PARM_DECL)
	    {
	      यदि (DECL_P (t))
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD is not an argument in %<uniform%> clause", t);
	      अन्यथा
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is not an argument in %<uniform%> clause", t);
	      हटाओ = सत्य;
	      भङ्ग;
	    }
	  /* map_head bitmap is used as uniform_head if declare_simd.  */
	  bitmap_set_bit (&map_head, DECL_UID (t));
	  गच्छ check_dup_generic;

	पक्ष OMP_CLAUSE_IS_DEVICE_PTR:
	पक्ष OMP_CLAUSE_USE_DEVICE_PTR:
	  t = OMP_CLAUSE_DECL (c);
	  यदि (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IS_DEVICE_PTR)
	    bitmap_set_bit (&is_on_device_head, DECL_UID (t));
	  यदि (वृक्ष_CODE (वृक्ष_TYPE (t)) != POINTER_TYPE)
	    {
	      यदि (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_USE_DEVICE_PTR
		  && !openacc)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qs variable is not a pointer",
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  हटाओ = सत्य;
		}
	      अन्यथा यदि (वृक्ष_CODE (वृक्ष_TYPE (t)) != ARRAY_TYPE)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qs variable is neither a pointer nor an array",
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  हटाओ = सत्य;
		}
	    }
	  गच्छ check_dup_generic;

	पक्ष OMP_CLAUSE_HAS_DEVICE_ADDR:
	  t = OMP_CLAUSE_DECL (c);
	  यदि (वृक्ष_CODE (t) == OMP_ARRAY_SECTION)
	    {
	      यदि (handle_omp_array_sections (c, ort))
		हटाओ = सत्य;
	      अन्यथा
		{
		  t = OMP_CLAUSE_DECL (c);
		  यावत् (वृक्ष_CODE (t) == ARRAY_REF)
		    t = वृक्ष_OPERAND (t, 0);
		}
	    }
	  bitmap_set_bit (&is_on_device_head, DECL_UID (t));
	  यदि (VAR_P (t) || वृक्ष_CODE (t) == PARM_DECL)
	    c_mark_addressable (t);
	  गच्छ check_dup_generic_t;

	पक्ष OMP_CLAUSE_USE_DEVICE_ADDR:
	  t = OMP_CLAUSE_DECL (c);
	  यदि (VAR_P (t) || वृक्ष_CODE (t) == PARM_DECL)
	    c_mark_addressable (t);
	  गच्छ check_dup_generic;

	पक्ष OMP_CLAUSE_NOWAIT:
	  यदि (copyprivate_seen)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<nowait%> clause must not be used together "
			"with %<copyprivate%> clause");
	      हटाओ = सत्य;
	      भङ्ग;
	    }
	  nowait_clause = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  अनुवर्त;

	पक्ष OMP_CLAUSE_ORDER:
	  यदि (ordered_clause)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<order%> clause must not be used together "
			"with %<ordered%> clause");
	      हटाओ = सत्य;
	      भङ्ग;
	    }
	  अन्यथा यदि (order_clause)
	    {
	      /* Silently remove duplicates.  */
	      हटाओ = सत्य;
	      भङ्ग;
	    }
	  order_clause = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  अनुवर्त;

	पक्ष OMP_CLAUSE_DETACH:
	  t = OMP_CLAUSE_DECL (c);
	  यदि (detach_seen)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"too many %qs clauses on a task construct",
			"detach");
	      हटाओ = सत्य;
	      भङ्ग;
	    }
	  detach_seen = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  c_mark_addressable (t);
	  अनुवर्त;

	पक्ष OMP_CLAUSE_IF:
	पक्ष OMP_CLAUSE_SELF:
	पक्ष OMP_CLAUSE_अंक_THREADS:
	पक्ष OMP_CLAUSE_अंक_TEAMS:
	पक्ष OMP_CLAUSE_THREAD_LIMIT:
	पक्ष OMP_CLAUSE_DEFAULT:
	पक्ष OMP_CLAUSE_UNTIED:
	पक्ष OMP_CLAUSE_COLLAPSE:
	पक्ष OMP_CLAUSE_FINAL:
	पक्ष OMP_CLAUSE_DEVICE:
	पक्ष OMP_CLAUSE_DIST_SCHEDULE:
	पक्ष OMP_CLAUSE_DYN_GROUPPRIVATE:
	पक्ष OMP_CLAUSE_PARALLEL:
	पक्ष OMP_CLAUSE_FOR:
	पक्ष OMP_CLAUSE_SECTIONS:
	पक्ष OMP_CLAUSE_TASKGROUP:
	पक्ष OMP_CLAUSE_PROC_BIND:
	पक्ष OMP_CLAUSE_DEVICE_TYPE:
	पक्ष OMP_CLAUSE_PRIORITY:
	पक्ष OMP_CLAUSE_THREADS:
	पक्ष OMP_CLAUSE_SIMD:
	पक्ष OMP_CLAUSE_HINT:
	पक्ष OMP_CLAUSE_FILTER:
	पक्ष OMP_CLAUSE_DEFAULTMAP:
	पक्ष OMP_CLAUSE_BIND:
	पक्ष OMP_CLAUSE_अंक_GANGS:
	पक्ष OMP_CLAUSE_अंक_WORKERS:
	पक्ष OMP_CLAUSE_VECTOR_LENGTH:
	पक्ष OMP_CLAUSE_ASYNC:
	पक्ष OMP_CLAUSE_WAIT:
	पक्ष OMP_CLAUSE_AUTO:
	पक्ष OMP_CLAUSE_INDEPENDENT:
	पक्ष OMP_CLAUSE_SEQ:
	पक्ष OMP_CLAUSE_GANG:
	पक्ष OMP_CLAUSE_WORKER:
	पक्ष OMP_CLAUSE_VECTOR:
	पक्ष OMP_CLAUSE_TILE:
	पक्ष OMP_CLAUSE_IF_PRESENT:
	पक्ष OMP_CLAUSE_FINALIZE:
	पक्ष OMP_CLAUSE_NOHOST:
	पक्ष OMP_CLAUSE_INDIRECT:
	पक्ष OMP_CLAUSE_NOVARIANTS:
	पक्ष OMP_CLAUSE_NOCONTEXT:
	  pc = &OMP_CLAUSE_CHAIN (c);
	  अनुवर्त;

	पक्ष OMP_CLAUSE_GRAINSIZE:
	  grainsize_seen = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  अनुवर्त;

	पक्ष OMP_CLAUSE_अंक_TASKS:
	  अंक_tasks_seen = सत्य;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  अनुवर्त;

	पक्ष OMP_CLAUSE_MERGEABLE:
	  mergeable_seen = सत्य;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  अनुवर्त;

	पक्ष OMP_CLAUSE_NOGROUP:
	  nogroup_seen = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  अनुवर्त;

	पक्ष OMP_CLAUSE_SCHEDULE:
	  schedule_clause = c;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  अनुवर्त;

	पक्ष OMP_CLAUSE_ORDERED:
	  ordered_clause = c;
	  यदि (order_clause)
	    {
	      error_at (OMP_CLAUSE_LOCATION (*order_clause),
			"%<order%> clause must not be used together "
			"with %<ordered%> clause");
	      *order_clause = OMP_CLAUSE_CHAIN (*order_clause);
	      order_clause = रिक्त;
	    }
	  pc = &OMP_CLAUSE_CHAIN (c);
	  अनुवर्त;

	पक्ष OMP_CLAUSE_SAFELEN:
	  safelen = c;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  अनुवर्त;
	पक्ष OMP_CLAUSE_SIMDLEN:
	  simdlen = c;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  अनुवर्त;

	पक्ष OMP_CLAUSE_FULL:
	  full_seen = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  अनुवर्त;

	पक्ष OMP_CLAUSE_PARTIAL:
	  partial_seen = सत्य;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  अनुवर्त;

	पक्ष OMP_CLAUSE_SIZES:
	  pc = &OMP_CLAUSE_CHAIN (c);
	  अनुवर्त;

	पक्ष OMP_CLAUSE_INBRANCH:
	पक्ष OMP_CLAUSE_NOTINBRANCH:
	  यदि (branch_seen)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<inbranch%> clause is incompatible with "
			"%<notinbranch%>");
	      हटाओ = सत्य;
	      भङ्ग;
	    }
	  branch_seen = सत्य;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  अनुवर्त;

	पक्ष OMP_CLAUSE_INCLUSIVE:
	पक्ष OMP_CLAUSE_EXCLUSIVE:
	  need_complete = सत्य;
	  need_implicitly_determined = सत्य;
	  t = OMP_CLAUSE_DECL (c);
	  यदि (!VAR_P (t) && वृक्ष_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %qs", t,
			omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	      हटाओ = सत्य;
	    }
	  भङ्ग;

	पक्ष OMP_CLAUSE_INIT:
	  init_seen = सत्य;
	  यदि (!OMP_CLAUSE_INIT_TARGETSYNC (c))
	    init_no_targetsync_clause = c;
	  /* FALLTHRU */
	पक्ष OMP_CLAUSE_DESTROY:
	पक्ष OMP_CLAUSE_USE:
	  init_use_destroy_seen = सत्य;
	  t = OMP_CLAUSE_DECL (c);
	  यदि (bitmap_bit_p (&generic_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD appears more than once in action clauses", t);
	      हटाओ = सत्य;
	      भङ्ग;
	    }
	  bitmap_set_bit (&generic_head, DECL_UID (t));
	  /* FALLTHRU */
	पक्ष OMP_CLAUSE_INTEROP:
	  यदि (/* ort == C_ORT_OMP_INTEROP [uncomment for depobj init]  */
		   !c_omp_interop_t_p (वृक्ष_TYPE (OMP_CLAUSE_DECL (c))))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD must be of %<omp_interop_t%>",
			OMP_CLAUSE_DECL (c));
	      हटाओ = सत्य;
	    }
	  अन्यथा यदि ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_INIT
		    || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DESTROY)
		   && वृक्ष_READONLY (OMP_CLAUSE_DECL (c)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD shall not be const", OMP_CLAUSE_DECL (c));
	      हटाओ = सत्य;
	    }
	  pc = &OMP_CLAUSE_CHAIN (c);
	  भङ्ग;
	स्वभाव:
	  gcc_unreachable ();
	}

      यदि (!हटाओ)
	{
	  t = OMP_CLAUSE_DECL (c);

	  यदि (need_complete)
	    {
	      t = require_complete_type (OMP_CLAUSE_LOCATION (c), t);
	      यदि (t == error_mark_गाँठ)
		हटाओ = सत्य;
	    }

	  यदि (need_implicitly_determined)
	    {
	      ध्रुव वर्ण *share_name = रिक्त;

	      यदि (VAR_P (t) && DECL_THREAD_LOCAL_P (t))
		share_name = "threadprivate";
	      अन्यथा विकल्प (c_omp_predetermined_sharing (t))
		{
		पक्ष OMP_CLAUSE_DEFAULT_UNSPECIFIED:
		  भङ्ग;
		पक्ष OMP_CLAUSE_DEFAULT_SHARED:
		  यदि ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_SHARED
		       || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_FIRSTPRIVATE)
		      && c_omp_predefined_variable (t))
		    /* The __func__ variable and similar function-local
		       predefined variables may be listed in a shared or
		       firstprivate clause.  */
		    भङ्ग;
		  share_name = "shared";
		  भङ्ग;
		पक्ष OMP_CLAUSE_DEFAULT_PRIVATE:
		  share_name = "private";
		  भङ्ग;
		स्वभाव:
		  gcc_unreachable ();
		}
	      यदि (share_name)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qE is predetermined %qs for %qs",
			    t, share_name,
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  हटाओ = सत्य;
		}
	      अन्यथा यदि (वृक्ष_READONLY (t)
		       && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_SHARED
		       && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_FIRSTPRIVATE)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<const%> qualified %qE may appear only in "
			    "%<shared%> or %<firstprivate%> clauses", t);
		  हटाओ = सत्य;
		}
	    }
	}

      यदि (हटाओ)
	{
	  यदि (grp_start_p)
	    {
	      /* If we found a clause to remove, we want to remove the whole
		 expanded group, otherwise gimplify
		 (omp_resolve_clause_dependencies) can get confused.  */
	      *grp_start_p = grp_sentinel;
	      pc = grp_start_p;
	      grp_start_p = रिक्त;
	    }
	  अन्यथा
	    *pc = OMP_CLAUSE_CHAIN (c);
	}
      अन्यथा
	pc = &OMP_CLAUSE_CHAIN (c);
    }

  यदि (grp_start_p
      && OMP_CLAUSE_HAS_ITERATORS (*grp_start_p))
    प्रति (वृक्ष gc = *grp_start_p; gc; gc = OMP_CLAUSE_CHAIN (gc))
      OMP_CLAUSE_ITERATORS (gc) = OMP_CLAUSE_ITERATORS (*grp_start_p);

  यदि (simdlen
      && safelen
      && वृक्ष_int_cst_lt (OMP_CLAUSE_SAFELEN_व्यंजक (safelen),
			  OMP_CLAUSE_SIMDLEN_व्यंजक (simdlen)))
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
      OMP_CLAUSE_SIMDLEN_व्यंजक (simdlen)
	= OMP_CLAUSE_SAFELEN_व्यंजक (safelen);
    }

  यदि (ordered_clause
      && schedule_clause
      && (OMP_CLAUSE_SCHEDULE_KIND (schedule_clause)
	  & OMP_CLAUSE_SCHEDULE_NONMONOTONIC))
    {
      error_at (OMP_CLAUSE_LOCATION (schedule_clause),
		"%<nonmonotonic%> schedule modifier specified together "
		"with %<ordered%> clause");
      OMP_CLAUSE_SCHEDULE_KIND (schedule_clause)
	= (गणना omp_clause_schedule_kind)
	  (OMP_CLAUSE_SCHEDULE_KIND (schedule_clause)
	   & ~OMP_CLAUSE_SCHEDULE_NONMONOTONIC);
    }

  यदि (reduction_seen < 0 && ordered_clause)
    {
      error_at (OMP_CLAUSE_LOCATION (ordered_clause),
		"%qs clause specified together with %<inscan%> "
		"%<reduction%> clause", "ordered");
      reduction_seen = -2;
    }

  यदि (reduction_seen < 0 && schedule_clause)
    {
      error_at (OMP_CLAUSE_LOCATION (schedule_clause),
		"%qs clause specified together with %<inscan%> "
		"%<reduction%> clause", "schedule");
      reduction_seen = -2;
    }

  यदि (linear_variable_step_check
      || reduction_seen == -2
      || allocate_seen
      || target_in_reduction_seen)
    प्रति (pc = &clauses, c = clauses; c ; c = *pc)
      {
	तार्किक हटाओ = असत्य;
	यदि (allocate_seen)
	  विकल्प (OMP_CLAUSE_CODE (c))
	    {
	    पक्ष OMP_CLAUSE_REDUCTION:
	    पक्ष OMP_CLAUSE_IN_REDUCTION:
	    पक्ष OMP_CLAUSE_TASK_REDUCTION:
	      यदि (वृक्ष_CODE (OMP_CLAUSE_DECL (c)) == MEM_REF)
		{
		  t = वृक्ष_OPERAND (OMP_CLAUSE_DECL (c), 0);
		  यदि (वृक्ष_CODE (t) == POINTER_PLUS_व्यंजक)
		    t = वृक्ष_OPERAND (t, 0);
		  यदि (वृक्ष_CODE (t) == ADDR_व्यंजक
		      || INDIRECT_REF_P (t))
		    t = वृक्ष_OPERAND (t, 0);
		  यदि (DECL_P (t))
		    bitmap_clear_bit (&aligned_head, DECL_UID (t));
		  भङ्ग;
		}
	      /* FALLTHRU */
	    पक्ष OMP_CLAUSE_PRIVATE:
	    पक्ष OMP_CLAUSE_FIRSTPRIVATE:
	    पक्ष OMP_CLAUSE_LASTPRIVATE:
	    पक्ष OMP_CLAUSE_LINEAR:
	      यदि (DECL_P (OMP_CLAUSE_DECL (c)))
		bitmap_clear_bit (&aligned_head,
				  DECL_UID (OMP_CLAUSE_DECL (c)));
	      भङ्ग;
	    स्वभाव:
	      भङ्ग;
	    }
	यदि (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_LINEAR
	    && OMP_CLAUSE_LINEAR_VARIABLE_STRIDE (c)
	    && !bitmap_bit_p (&map_head,
			      DECL_UID (OMP_CLAUSE_LINEAR_STEP (c))))
	  {
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%<linear%> clause step is a parameter %qD not "
		      "specified in %<uniform%> clause",
		      OMP_CLAUSE_LINEAR_STEP (c));
	    हटाओ = सत्य;
	  }
	अन्यथा यदि (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
		 && reduction_seen == -2)
	  OMP_CLAUSE_REDUCTION_INSCAN (c) = 0;
	यदि (target_in_reduction_seen
	    && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP)
	  {
	    वृक्ष t = OMP_CLAUSE_DECL (c);
	    यावत् (handled_component_p (t)
		   || INDIRECT_REF_P (t)
		   || वृक्ष_CODE (t) == ADDR_व्यंजक
		   || वृक्ष_CODE (t) == MEM_REF
		   || वृक्ष_CODE (t) == NON_LVALUE_व्यंजक)
	      t = वृक्ष_OPERAND (t, 0);
	    यदि (DECL_P (t)
		&& bitmap_bit_p (&oacc_reduction_head, DECL_UID (t)))
	      OMP_CLAUSE_MAP_IN_REDUCTION (c) = 1;
	  }

	यदि (हटाओ)
	  *pc = OMP_CLAUSE_CHAIN (c);
	अन्यथा
	  pc = &OMP_CLAUSE_CHAIN (c);
      }

  यदि (allocate_seen)
    प्रति (pc = &clauses, c = clauses; c ; c = *pc)
      {
	तार्किक हटाओ = असत्य;
	यदि (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ALLOCATE
	    && !OMP_CLAUSE_ALLOCATE_COMBINED (c)
	    && bitmap_bit_p (&aligned_head, DECL_UID (OMP_CLAUSE_DECL (c))))
	  {
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD specified in %<allocate%> clause but not in "
		      "an explicit privatization clause", OMP_CLAUSE_DECL (c));
	    हटाओ = सत्य;
	  }
	यदि (हटाओ)
	  *pc = OMP_CLAUSE_CHAIN (c);
	अन्यथा
	  pc = &OMP_CLAUSE_CHAIN (c);
      }

  यदि (nogroup_seen && reduction_seen)
    {
      error_at (OMP_CLAUSE_LOCATION (*nogroup_seen),
		"%<nogroup%> clause must not be used together with "
		"%<reduction%> clause");
      *nogroup_seen = OMP_CLAUSE_CHAIN (*nogroup_seen);
    }

  यदि (grainsize_seen && अंक_tasks_seen)
    {
      error_at (OMP_CLAUSE_LOCATION (*grainsize_seen),
		"%<grainsize%> clause must not be used together with "
		"%<num_tasks%> clause");
      *grainsize_seen = OMP_CLAUSE_CHAIN (*grainsize_seen);
    }

  यदि (full_seen && partial_seen)
    {
      error_at (OMP_CLAUSE_LOCATION (*full_seen),
		"%<full%> clause must not be used together with "
		"%<partial%> clause");
      *full_seen = OMP_CLAUSE_CHAIN (*full_seen);
    }

  यदि (detach_seen)
    {
      यदि (mergeable_seen)
	{
	  error_at (OMP_CLAUSE_LOCATION (*detach_seen),
		    "%<detach%> clause must not be used together with "
		    "%<mergeable%> clause");
	  *detach_seen = OMP_CLAUSE_CHAIN (*detach_seen);
	}
      अन्यथा
	{
	  वृक्ष detach_decl = OMP_CLAUSE_DECL (*detach_seen);

	  प्रति (pc = &clauses, c = clauses; c ; c = *pc)
	    {
	      तार्किक हटाओ = असत्य;
	      यदि ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_SHARED
		   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_PRIVATE
		   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_FIRSTPRIVATE
		   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_LASTPRIVATE)
		  && OMP_CLAUSE_DECL (c) == detach_decl)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "the event handle of a %<detach%> clause "
			    "should not be in a data-sharing clause");
		  हटाओ = सत्य;
		}
	      यदि (हटाओ)
		*pc = OMP_CLAUSE_CHAIN (c);
	      अन्यथा
		pc = &OMP_CLAUSE_CHAIN (c);
	    }
	}
    }

  यदि (ort == C_ORT_OMP_INTEROP
      && depend_clause
      && (!init_use_destroy_seen
	  || (init_seen && init_no_targetsync_clause)))
    {
      error_at (OMP_CLAUSE_LOCATION (depend_clause),
		"%<depend%> clause requires action clauses with "
		"%<targetsync%> interop-type");
      यदि (init_no_targetsync_clause)
	inform (OMP_CLAUSE_LOCATION (init_no_targetsync_clause),
		"%<init%> clause lacks the %<targetsync%> modifier");
    }

  bitmap_obstack_release (रिक्त);
  प्रत्यागम clauses;
}

/* Do processing necessary to make CLAUSES well-formed, where CLAUSES result
   from implicit instantiation of user-defined mappers (in gimplify.cc).  */

वृक्ष
c_omp_finish_mapper_clauses (वृक्ष clauses)
{
  प्रत्यागम c_finish_omp_clauses (clauses, C_ORT_OMP);
}

/* Return code to initialize DST with a copy constructor from SRC.
   C doesn't have copy constructors nor assignment operators, only for
   _Atomic vars we need to perform __atomic_load from src into a temporary
   followed by __atomic_store of the temporary to dst.  */

वृक्ष
c_omp_clause_copy_ctor (वृक्ष clause, वृक्ष dst, वृक्ष src)
{
  यदि (!really_atomic_lvalue (dst) && !really_atomic_lvalue (src))
    प्रत्यागम build2 (MODIFY_व्यंजक, वृक्ष_TYPE (dst), dst, src);

  location_t loc = OMP_CLAUSE_LOCATION (clause);
  वृक्ष type = वृक्ष_TYPE (dst);
  वृक्ष nonatomic_type = build_qualified_type (type, TYPE_UNQUALIFIED);
  वृक्ष tmp = create_tmp_var (nonatomic_type);
  वृक्ष tmp_addr = build_fold_addr_व्यंजक (tmp);
  वृक्ष_ADDRESSABLE (tmp) = 1;
  suppress_warning (tmp);
  वृक्ष src_addr = build_fold_addr_व्यंजक (src);
  वृक्ष dst_addr = build_fold_addr_व्यंजक (dst);
  वृक्ष seq_cst = build_int_cst (integer_type_गाँठ, MEMMODEL_SEQ_CST);
  vec<वृक्ष, va_gc> *params;
  /* Expansion of a generic atomic load may require an addition
     element, so allocate enough to prevent a resize.  */
  vec_alloc (params, 4);

  /* Build __atomic_load (&src, &tmp, SEQ_CST);  */
  वृक्ष fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_LOAD);
  params->quick_धकेलो (src_addr);
  params->quick_धकेलो (tmp_addr);
  params->quick_धकेलो (seq_cst);
  वृक्ष load = c_build_function_call_vec (loc, vNULL, fndecl, params, रिक्त);

  vec_alloc (params, 4);

  /* Build __atomic_store (&dst, &tmp, SEQ_CST);  */
  fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_STORE);
  params->quick_धकेलो (dst_addr);
  params->quick_धकेलो (tmp_addr);
  params->quick_धकेलो (seq_cst);
  वृक्ष store = c_build_function_call_vec (loc, vNULL, fndecl, params, रिक्त);
  प्रत्यागम build2 (COMPOUND_व्यंजक, void_type_गाँठ, load, store);
}

/* Create a transaction node.  */

वृक्ष
c_finish_transaction (location_t loc, वृक्ष block, पूर्णाङ्क flags)
{
  वृक्ष stmt = build_stmt (loc, TRANSACTION_व्यंजक, block);
  यदि (flags & TM_STMT_ATTR_OUTER)
    TRANSACTION_व्यंजक_OUTER (stmt) = 1;
  यदि (flags & TM_STMT_ATTR_RELAXED)
    TRANSACTION_व्यंजक_RELAXED (stmt) = 1;
  प्रत्यागम add_stmt (stmt);
}

/* Make a variant type in the proper way for C/C++, propagating qualifiers
   down to the element type of an array.  If ORIG_QUAL_TYPE is not
   NULL, then it should be used as the qualified type
   ORIG_QUAL_INDIRECT levels down in array type derivation (to
   preserve information about the typedef name from which an array
   type was derived).  */

वृक्ष
c_build_qualified_type (वृक्ष type, पूर्णाङ्क type_quals, वृक्ष orig_qual_type,
			माप_प्रकार orig_qual_indirect)
{
  यदि (type == error_mark_गाँठ)
    प्रत्यागम type;

  यदि (वृक्ष_CODE (type) == ARRAY_TYPE)
    {
      वृक्ष t;
      वृक्ष element_type = c_build_qualified_type (वृक्ष_TYPE (type),
						  type_quals, orig_qual_type,
						  orig_qual_indirect - 1);

      /* See if we already have an identically qualified type.  */
      यदि (orig_qual_type && orig_qual_indirect == 0)
	t = orig_qual_type;
      अन्यथा
	प्रति (t = TYPE_MAIN_VARIANT (type); t; t = TYPE_NEXT_VARIANT (t))
	  {
	    यदि (TYPE_QUALS (strip_array_types (t)) == type_quals
		&& TYPE_NAME (t) == TYPE_NAME (type)
		&& TYPE_CONTEXT (t) == TYPE_CONTEXT (type)
		&& attribute_list_equal (TYPE_ATTRIBUTES (t),
					 TYPE_ATTRIBUTES (type)))
	      भङ्ग;
	  }
      यदि (!t)
	{
          वृक्ष domain = TYPE_DOMAIN (type);

	  t = build_variant_type_copy (type);
	  वृक्ष_TYPE (t) = element_type;
	  TYPE_ADDR_SPACE (t) = TYPE_ADDR_SPACE (element_type);

          यदि (TYPE_STRUCTURAL_EQUALITY_P (element_type)
              || (domain && TYPE_STRUCTURAL_EQUALITY_P (domain)))
            SET_TYPE_STRUCTURAL_EQUALITY (t);
          अन्यथा यदि (TYPE_CANONICAL (element_type) != element_type
                   || (domain && TYPE_CANONICAL (domain) != domain))
            {
              वृक्ष unqualified_canon
		= c_build_array_type (TYPE_CANONICAL (element_type),
				      domain ? TYPE_CANONICAL (domain)
					     : NULL_वृक्ष);
              यदि (TYPE_REVERSE_STORAGE_ORDER (type))
                {
                  unqualified_canon
		    = build_distinct_type_copy (unqualified_canon);
                  TYPE_REVERSE_STORAGE_ORDER (unqualified_canon) = 1;
                }
              TYPE_CANONICAL (t)
		= c_build_qualified_type (unqualified_canon, type_quals);
            }
          अन्यथा
            TYPE_CANONICAL (t) = t;
	}
      प्रत्यागम t;
    }

  /* A restrict-qualified pointer type must be a pointer to object or
     incomplete type.  Note that the use of POINTER_TYPE_P also allows
     REFERENCE_TYPEs, which is appropriate for C++.  */
  यदि ((type_quals & TYPE_QUAL_RESTRICT)
      && (!POINTER_TYPE_P (type)
	  || !C_TYPE_OBJECT_OR_INCOMPLETE_P (वृक्ष_TYPE (type))))
    {
      error ("invalid use of %<restrict%>");
      type_quals &= ~TYPE_QUAL_RESTRICT;
    }

  वृक्ष var_type = (orig_qual_type && orig_qual_indirect == 0
		   ? orig_qual_type
		   : build_qualified_type (type, type_quals));

  gcc_checking_assert (C_TYPE_VARIABLE_SIZE (var_type)
		       == C_TYPE_VARIABLE_SIZE (type));
  gcc_checking_assert (c_type_variably_modified_p (var_type)
		       == c_type_variably_modified_p (type));

  /* A variant type does not inherit the list of incomplete vars from the
     type main variant.  */
  यदि ((RECORD_OR_UNION_TYPE_P (var_type)
       || वृक्ष_CODE (var_type) == ENUMERAL_TYPE)
      && TYPE_MAIN_VARIANT (var_type) != var_type)
    C_TYPE_INCOMPLETE_VARS (var_type) = 0;
  प्रत्यागम var_type;
}

/* Build a VA_ARG_EXPR for the C parser.  */

वृक्ष
c_build_va_arg (location_t loc1, वृक्ष व्यंजक, location_t loc2, वृक्ष type,
		वृक्ष type_व्यंजक)
{
  यदि (error_operand_p (type))
    प्रत्यागम error_mark_गाँठ;
  /* VA_ARG_EXPR cannot be used for a scalar va_list with reverse storage
     order because it takes the address of the expression.  */
  अन्यथा यदि (handled_component_p (व्यंजक)
	   && reverse_storage_order_for_component_p (व्यंजक))
    {
      error_at (loc1, "cannot use %<va_arg%> with reverse storage order");
      प्रत्यागम error_mark_गाँठ;
    }
  अन्यथा यदि (!COMPLETE_TYPE_P (type))
    {
      error_at (loc2, "second argument to %<va_arg%> is of incomplete "
		"type %qT", type);
      प्रत्यागम error_mark_गाँठ;
    }
  अन्यथा यदि (वृक्ष_CODE (type) == FUNCTION_TYPE)
    {
      error_at (loc2, "second argument to %<va_arg%> is a function type %qT",
		type);
      प्रत्यागम error_mark_गाँठ;
    }
  अन्यथा यदि (वृक्ष_CODE (type) == ARRAY_TYPE && C_TYPE_VARIABLE_SIZE (type)
	   && !flag_isoc99)
    {
      error_at (loc2, "second argument to %<va_arg%> is an array type %qT",
		type);
      प्रत्यागम error_mark_गाँठ;
    }
  अन्यथा यदि (warn_cxx_compat && वृक्ष_CODE (type) == ENUMERAL_TYPE)
    warning_at (loc2, OPT_Wc___compat,
		"C++ requires promoted type, not enum type, in %<va_arg%>");

  यदि (flag_isoc99 && वृक्ष_CODE (type) == ARRAY_TYPE)
    {
      warning_at (loc2, 0, "second argument to %<va_arg%> is an array type %qT",
		  type);
      /* We create a trap but evaluate side effects first.  */
      वृक्ष trapfn = builtin_decl_explicit (BUILT_IN_TRAP);
      trapfn = build_call_व्यंजक_loc (loc2, trapfn, 0);
      वृक्ष e2 = build2 (COMPOUND_व्यंजक, void_type_गाँठ, व्यंजक, trapfn);
      /* Return a compound literal of the right type.  */
      वृक्ष e1 = build_compound_literal (loc2, type, रिक्त, सत्य, 0, रिक्त);
      व्यंजक = build2 (COMPOUND_व्यंजक, type, e2, e1);
    }
  अन्यथा
    व्यंजक = build_va_arg (loc2, व्यंजक, type);

  यदि (type_व्यंजक)
    व्यंजक = build2 (COMPOUND_व्यंजक, वृक्ष_TYPE (व्यंजक), type_व्यंजक, व्यंजक);

  प्रत्यागम व्यंजक;
}

/* Return truthvalue of whether T1 is the same tree structure as T2.
   Return 1 if they are the same. Return false if they are different.  */

तार्किक
c_वृक्ष_equal (वृक्ष t1, वृक्ष t2)
{
  गणना वृक्ष_code code1, code2;

  यदि (t1 == t2)
    प्रत्यागम सत्य;
  यदि (!t1 || !t2)
    प्रत्यागम असत्य;

  प्रति (code1 = वृक्ष_CODE (t1); code1 == NON_LVALUE_व्यंजक;
       code1 = वृक्ष_CODE (t1))
    t1 = वृक्ष_OPERAND (t1, 0);
  प्रति (code2 = वृक्ष_CODE (t2); code2 == NON_LVALUE_व्यंजक;
       code2 = वृक्ष_CODE (t2))
    t2 = वृक्ष_OPERAND (t2, 0);

  /* They might have become equal now.  */
  यदि (t1 == t2)
    प्रत्यागम सत्य;

  यदि (code1 != code2)
    प्रत्यागम असत्य;

  यदि (CONSTANT_CLASS_P (t1) && !comptypes (वृक्ष_TYPE (t1), वृक्ष_TYPE (t2)))
    प्रत्यागम असत्य;

  विकल्प (code1)
    {
    पक्ष INTEGER_CST:
      प्रत्यागम wi::to_wide (t1) == wi::to_wide (t2);

    पक्ष REAL_CST:
      प्रत्यागम real_equal (&वृक्ष_REAL_CST (t1), &वृक्ष_REAL_CST (t2));

    पक्ष STRING_CST:
      प्रत्यागम वृक्ष_STRING_LENGTH (t1) == वृक्ष_STRING_LENGTH (t2)
	&& !स_भेद (वृक्ष_STRING_POINTER (t1), वृक्ष_STRING_POINTER (t2),
		    वृक्ष_STRING_LENGTH (t1));

    पक्ष FIXED_CST:
      प्रत्यागम FIXED_मूल्यावली_IDENTICAL (वृक्ष_FIXED_CST (t1),
				     वृक्ष_FIXED_CST (t2));

    पक्ष COMPLEX_CST:
      प्रत्यागम c_वृक्ष_equal (वृक्ष_REALPART (t1), वृक्ष_REALPART (t2))
	     && c_वृक्ष_equal (वृक्ष_IMAGPART (t1), वृक्ष_IMAGPART (t2));

    पक्ष VECTOR_CST:
      प्रत्यागम operand_equal_p (t1, t2, OEP_ONLY_CONST);

    पक्ष CONSTRUCTOR:
      /* We need to do this when determining whether or not two
	 non-type pointer to member function template arguments
	 are the same.  */
      यदि (!comptypes (वृक्ष_TYPE (t1), वृक्ष_TYPE (t2))
	  || CONSTRUCTOR_NELTS (t1) != CONSTRUCTOR_NELTS (t2))
	प्रत्यागम असत्य;
      {
	वृक्ष field, मूल्य;
	अचिन्हित पूर्णाङ्क i;
	FOR_EACH_CONSTRUCTOR_ELT (CONSTRUCTOR_ELTS (t1), i, field, मूल्य)
	  {
	    constructor_elt *elt2 = CONSTRUCTOR_ELT (t2, i);
	    यदि (!c_वृक्ष_equal (field, elt2->index)
		|| !c_वृक्ष_equal (मूल्य, elt2->मूल्य))
	      प्रत्यागम असत्य;
	  }
      }
      प्रत्यागम सत्य;

    पक्ष वृक्ष_LIST:
      यदि (!c_वृक्ष_equal (वृक्ष_PURPOSE (t1), वृक्ष_PURPOSE (t2)))
	प्रत्यागम असत्य;
      यदि (!c_वृक्ष_equal (वृक्ष_मूल्य (t1), वृक्ष_मूल्य (t2)))
	प्रत्यागम असत्य;
      प्रत्यागम c_वृक्ष_equal (वृक्ष_CHAIN (t1), वृक्ष_CHAIN (t2));

    पक्ष SAVE_व्यंजक:
      प्रत्यागम c_वृक्ष_equal (वृक्ष_OPERAND (t1, 0), वृक्ष_OPERAND (t2, 0));

    पक्ष CALL_व्यंजक:
      {
	वृक्ष arg1, arg2;
	call_व्यंजक_arg_iterator iter1, iter2;
	यदि (!c_वृक्ष_equal (CALL_व्यंजक_FN (t1), CALL_व्यंजक_FN (t2)))
	  प्रत्यागम असत्य;
	प्रति (arg1 = first_call_व्यंजक_arg (t1, &iter1),
	       arg2 = first_call_व्यंजक_arg (t2, &iter2);
	     arg1 && arg2;
	     arg1 = next_call_व्यंजक_arg (&iter1),
	       arg2 = next_call_व्यंजक_arg (&iter2))
	  यदि (!c_वृक्ष_equal (arg1, arg2))
	    प्रत्यागम असत्य;
	यदि (arg1 || arg2)
	  प्रत्यागम असत्य;
	प्रत्यागम सत्य;
      }

    पक्ष TARGET_व्यंजक:
      {
	वृक्ष o1 = वृक्ष_OPERAND (t1, 0);
	वृक्ष o2 = वृक्ष_OPERAND (t2, 0);

	/* Special case: if either target is an unallocated VAR_DECL,
	   it means that it's going to be unified with whatever the
	   TARGET_EXPR is really supposed to initialize, so treat it
	   as being equivalent to anything.  */
	यदि (VAR_P (o1) && DECL_NAME (o1) == NULL_वृक्ष
	    && !DECL_RTL_SET_P (o1))
	  /*Nop*/;
	अन्यथा यदि (VAR_P (o2) && DECL_NAME (o2) == NULL_वृक्ष
		 && !DECL_RTL_SET_P (o2))
	  /*Nop*/;
	अन्यथा यदि (!c_वृक्ष_equal (o1, o2))
	  प्रत्यागम असत्य;

	प्रत्यागम c_वृक्ष_equal (वृक्ष_OPERAND (t1, 1), वृक्ष_OPERAND (t2, 1));
      }

    पक्ष COMPONENT_REF:
      यदि (वृक्ष_OPERAND (t1, 1) != वृक्ष_OPERAND (t2, 1))
	प्रत्यागम असत्य;
      प्रत्यागम c_वृक्ष_equal (वृक्ष_OPERAND (t1, 0), वृक्ष_OPERAND (t2, 0));

    पक्ष PARM_DECL:
    पक्ष VAR_DECL:
    पक्ष CONST_DECL:
    पक्ष FIELD_DECL:
    पक्ष FUNCTION_DECL:
    पक्ष IDENTIFIER_गाँठ:
    पक्ष SSA_NAME:
      प्रत्यागम असत्य;

    पक्ष वृक्ष_VEC:
      {
	अचिन्हित ix;
	यदि (वृक्ष_VEC_LENGTH (t1) != वृक्ष_VEC_LENGTH (t2))
	  प्रत्यागम असत्य;
	प्रति (ix = वृक्ष_VEC_LENGTH (t1); ix--;)
	  यदि (!c_वृक्ष_equal (वृक्ष_VEC_ELT (t1, ix),
			     वृक्ष_VEC_ELT (t2, ix)))
	    प्रत्यागम असत्य;
	प्रत्यागम सत्य;
      }

    CASE_CONVERT:
      यदि (!comptypes (वृक्ष_TYPE (t1), वृक्ष_TYPE (t2)))
	प्रत्यागम असत्य;
      भङ्ग;

    स्वभाव:
      भङ्ग;
    }

  विकल्प (वृक्ष_CODE_CLASS (code1))
    {
    पक्ष tcc_unary:
    पक्ष tcc_द्विआधारी:
    पक्ष tcc_comparison:
    पक्ष tcc_expression:
    पक्ष tcc_vl_exp:
    पक्ष tcc_reference:
    पक्ष tcc_statement:
      {
	पूर्णाङ्क i, n = वृक्ष_OPERAND_LENGTH (t1);

	विकल्प (code1)
	  {
	  पक्ष PREINCREMENT_व्यंजक:
	  पक्ष PREDECREMENT_व्यंजक:
	  पक्ष POSTINCREMENT_व्यंजक:
	  पक्ष POSTDECREMENT_व्यंजक:
	    n = 1;
	    भङ्ग;
	  पक्ष ARRAY_REF:
	    n = 2;
	    भङ्ग;
	  स्वभाव:
	    भङ्ग;
	  }

	यदि (वृक्ष_CODE_CLASS (code1) == tcc_vl_exp
	    && n != वृक्ष_OPERAND_LENGTH (t2))
	  प्रत्यागम असत्य;

	प्रति (i = 0; i < n; ++i)
	  यदि (!c_वृक्ष_equal (वृक्ष_OPERAND (t1, i), वृक्ष_OPERAND (t2, i)))
	    प्रत्यागम असत्य;

	प्रत्यागम सत्य;
      }

    पक्ष tcc_type:
      प्रत्यागम comptypes (t1, t2);
    स्वभाव:
      gcc_unreachable ();
    }
}

/* Returns true when the function declaration FNDECL is implicit,
   introduced as a result of a call to an otherwise undeclared
   function, and false otherwise.  */

तार्किक
c_decl_implicit (const_वृक्ष fndecl)
{
  प्रत्यागम C_DECL_IMPLICIT (fndecl);
}
