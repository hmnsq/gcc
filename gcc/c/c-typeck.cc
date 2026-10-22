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
पूर्णांक in_alignof;

/* The level of nesting inside "sizeof".  */
पूर्णांक in_sizeof;

/* The level of nesting inside "countof".  */
पूर्णांक in_countof;

/* The level of nesting inside "typeof".  */
पूर्णांक in_typeof;

/* The level of nesting inside "_Generic".  */
पूर्णांक in_generic;

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
स्थिर पूर्णांक found_missing_braces;

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
स्थिर पूर्णांक convert_arguments (location_t, vec<location_t>, वृक्ष,
			      vec<वृक्ष, va_gc> *, vec<वृक्ष, va_gc> *, वृक्ष,
			      वृक्ष);
स्थिर वृक्ष pointer_diff (location_t, वृक्ष, वृक्ष, वृक्ष *);
स्थिर वृक्ष convert_for_assignment (location_t, location_t, वृक्ष, वृक्ष, वृक्ष,
				    गणना impl_conv, तार्किक, वृक्ष, वृक्ष, पूर्णांक,
				    पूर्णांक = 0);
स्थिर वृक्ष valid_compound_अभिव्यक्ती_initializer (वृक्ष, वृक्ष);
स्थिर शून्य ढकला_string (स्थिरांक अक्षर *);
स्थिर शून्य ढकला_member_name (वृक्ष);
स्थिर पूर्णांक spelling_length (शून्य);
स्थिर अक्षर *print_spelling (अक्षर *);
स्थिर शून्य warning_init (location_t, पूर्णांक, स्थिरांक अक्षर *);
स्थिर वृक्ष digest_init (location_t, वृक्ष, वृक्ष, वृक्ष, वृक्ष, तार्किक, तार्किक, तार्किक,
			 तार्किक, तार्किक, तार्किक);
स्थिर शून्य output_init_element (location_t, वृक्ष, वृक्ष, तार्किक, वृक्ष, वृक्ष, तार्किक,
				 तार्किक, संरचना obstack *);
स्थिर शून्य output_pending_init_elements (पूर्णांक, संरचना obstack *);
स्थिर तार्किक set_designator (location_t, तार्किक, संरचना obstack *);
स्थिर शून्य ढकला_range_चळत (वृक्ष, संरचना obstack *);
स्थिर शून्य add_pending_init (location_t, वृक्ष, वृक्ष, वृक्ष, तार्किक,
			      संरचना obstack *);
स्थिर शून्य set_nonincremental_init (संरचना obstack *);
स्थिर शून्य set_nonincremental_init_from_string (वृक्ष, संरचना obstack *);
स्थिर वृक्ष find_init_member (वृक्ष, संरचना obstack *);
स्थिर शून्य readonly_warning (वृक्ष, गणना lvalue_use);
स्थिर पूर्णांक lvalue_or_else (location_t, const_वृक्ष, गणना lvalue_use);
स्थिर शून्य record_maybe_used_decl (वृक्ष, तार्किक address);
स्थिर तार्किक comptypes_internal (const_वृक्ष, const_वृक्ष,
				संरचना comptypes_data *data);
स्थिर तार्किक comptypes_check_for_composite (वृक्ष t1, वृक्ष t2);
स्थिर तार्किक handle_counted_by_p (वृक्ष);
स्थिर तार्किक शीर्ष_array_vla_p (const_वृक्ष type);


/* Return true if EXP is a null pointer constant, false otherwise.  */

तार्किक
null_pointer_constant_p (const_वृक्ष अभिव्यक्ती)
{
  /* This should really operate on c_expr structures, but they aren't
     yet available everywhere required.  */
  वृक्ष type = वृक्ष_TYPE (अभिव्यक्ती);

  /* An integer constant expression with the value 0, such an expression
     cast to type void*, or the predefined constant nullptr, are a null
     pointer constant.  */
  जर (अभिव्यक्ती == nullptr_गाठ)
    परत सत्य;

  परत (वृक्ष_CODE (अभिव्यक्ती) == INTEGER_CST
	  && !वृक्ष_OVERFLOW (अभिव्यक्ती)
	  && integer_zerop (अभिव्यक्ती)
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
note_integer_operands (वृक्ष अभिव्यक्ती)
{
  वृक्ष ret;
  जर (वृक्ष_CODE (अभिव्यक्ती) == INTEGER_CST && in_late_द्विमान_op)
    {
      ret = copy_गाठ (अभिव्यक्ती);
      वृक्ष_OVERFLOW (ret) = 1;
    }
  अन्यथा
    {
      ret = build2 (C_MAYBE_CONST_अभिव्यक्ती, वृक्ष_TYPE (अभिव्यक्ती), NULL_वृक्ष, अभिव्यक्ती);
      C_MAYBE_CONST_अभिव्यक्ती_INT_OPERANDS (ret) = 1;
    }
  परत ret;
}

/* Having checked whether EXPR may appear in an unevaluated part of an
   integer constant expression and found that it may, remove any
   C_MAYBE_CONST_EXPR noting this fact and return the resulting
   expression.  */

स्थिर ओळीत वृक्ष
remove_c_maybe_const_अभिव्यक्ती (वृक्ष अभिव्यक्ती)
{
  जर (वृक्ष_CODE (अभिव्यक्ती) == C_MAYBE_CONST_अभिव्यक्ती)
    परत C_MAYBE_CONST_अभिव्यक्ती_अभिव्यक्ती (अभिव्यक्ती);
  अन्यथा
    परत अभिव्यक्ती;
}

/* This is a cache to hold if two types are seen.  */

संरचना tagged_tu_seen_cache {
  स्थिरांक संरचना tagged_tu_seen_cache * next;
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

  जर (error_operand_p (मूल्य))
    परत error_mark_गाठ;

  /* First, detect a valid value with a complete type.  */
  जर (COMPLETE_TYPE_P (type))
    परत मूल्य;

  c_incomplete_type_error (loc, मूल्य, type);
  परत error_mark_गाठ;
}

/* Print an error message for invalid use of an incomplete type.
   VALUE is the expression that was used (or 0 if that isn't known)
   and TYPE is the type that was invalid.  LOC is the location for
   the error.  */

शून्य
c_incomplete_type_error (location_t loc, const_वृक्ष मूल्य, const_वृक्ष type)
{
  /* Avoid duplicate error message.  */
  जर (वृक्ष_CODE (type) == ERROR_MARK)
    परत;

  जर (मूल्य != NULL_वृक्ष && (VAR_P (मूल्य) || वृक्ष_CODE (मूल्य) == PARM_DECL))
    error_at (loc, "%qD has an incomplete type %qT", मूल्य, type);
  अन्यथा
    {
    retry:
      /* We must print an error message.  Be clever about what it says.  */

      निवड (वृक्ष_CODE (type))
	{
	स्थिती RECORD_TYPE:
	स्थिती UNION_TYPE:
	स्थिती ENUMERAL_TYPE:
	  थांबा;

	स्थिती VOID_TYPE:
	  error_at (loc, "invalid use of void expression");
	  परत;

	स्थिती ARRAY_TYPE:
	  जर (TYPE_DOMAIN (type))
	    {
	      जर (flexible_array_member_type_p (type))
		{
		  error_at (loc, "invalid use of flexible array member");
		  परत;
		}
	      type = वृक्ष_TYPE (type);
	      जा retry;
	    }
	  error_at (loc, "invalid use of array with unspecified bounds");
	  परत;

	पूर्वनिर्धारित:
	  gcc_unreachable ();
	}

      जर (वृक्ष_CODE (TYPE_NAME (type)) == IDENTIFIER_गाठ)
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

  जर (TYPE_MAIN_VARIANT (type) == float_type_गाठ)
    ret = double_type_गाठ;
  अन्यथा जर (c_promoting_integer_type_p (type))
    {
      /* Preserve unsignedness if not really getting any wider.  */
      जर (TYPE_UNSIGNED (type)
	  && (TYPE_PRECISION (type) == TYPE_PRECISION (integer_type_गाठ)))
	ret = unsigned_type_गाठ;
      अन्यथा
	ret = integer_type_गाठ;
    }

  जर (ret != NULL_वृक्ष)
    परत (TYPE_ATOMIC (type)
	    ? c_build_qualified_type (ret, TYPE_QUAL_ATOMIC)
	    : ret);

  परत type;
}

/* Return true if between two named address spaces, whether there is a superset
   named address space that encompasses both address spaces.  If there is a
   superset, return which address space is the superset.  */

स्थिर तार्किक
addr_space_superset (addr_space_t as1, addr_space_t as2, addr_space_t *common)
{
  जर (as1 == as2)
    {
      *common = as1;
      परत सत्य;
    }
  अन्यथा जर (targetm.addr_space.subset_p (as1, as2))
    {
      *common = as2;
      परत सत्य;
    }
  अन्यथा जर (targetm.addr_space.subset_p (as2, as1))
    {
      *common = as1;
      परत सत्य;
    }
  अन्यथा
    परत असत्य;
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
  जर (!addr_space_superset (as_type, as_like, &as_common))
    {
      as_common = as_type;
      error ("%qT and %qT are in disjoint named address spaces",
	     type, like);
    }

  परत c_build_qualified_type (type,
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
  निवड (वृक्ष_CODE (type))
    {
    स्थिती POINTER_TYPE:
    स्थिती FUNCTION_TYPE:
    स्थिती ARRAY_TYPE:
      /* Pointer, array, functions are variably modified if and only if the
	 target, element, return type is variably modified.  */
      जर (!TYPE_STRUCTURAL_EQUALITY_P (type)
	  && (C_TYPE_VARIABLY_MODIFIED (type)
	      != C_TYPE_VARIABLY_MODIFIED (वृक्ष_TYPE (type))))
	परत असत्य;
      /* If the target type is structural equality, the type should also. */
      जर (!TYPE_STRUCTURAL_EQUALITY_P (type)
	  && TYPE_STRUCTURAL_EQUALITY_P (वृक्ष_TYPE (type)))
	परत असत्य;
    पूर्वनिर्धारित:
       थांबा;
    }

  निवड (वृक्ष_CODE (type))
    {
    स्थिती POINTER_TYPE:
    स्थिती FUNCTION_TYPE:
      /* Pointer and functions can not have variable size.  */
      जर (C_TYPE_VARIABLE_SIZE (type))
	परत असत्य;
      थांबा;
    स्थिती ARRAY_TYPE:
      /* An array has variable size if and only if it has a non-constant
	 dimensions or its element type has variable size.  */
      जर ((C_TYPE_VARIABLE_SIZE (वृक्ष_TYPE (type))
	   || शीर्ष_array_vla_p (type))
	  != C_TYPE_VARIABLE_SIZE (type))
	परत असत्य;
      /* If the element type or the array has variable size, then the
	 array has variable size and is variably modified.  */
      जर (C_TYPE_VARIABLE_SIZE (वृक्ष_TYPE (type))
	  || C_TYPE_VARIABLE_SIZE (type))
	{
	  जर (!C_TYPE_VARIABLE_SIZE (type))
	    परत असत्य;
	  जर (!C_TYPE_VARIABLY_MODIFIED (type))
	    परत असत्य;
	}

      /* va_list violates this, accept such types here.  */
      जर (!COMPLETE_TYPE_P (वृक्ष_TYPE (type)))
	परत सत्य;

      जर (COMPLETE_TYPE_P (type))
	{
	  /* If the size is unknown, it can not be complete.  */
	  जर (NULL_वृक्ष == TYPE_DOMAIN (type))
	    परत असत्य;

	  /* Zero-length arrays must have size zero.  */
	  जर (zero_length_array_type_p (type)
	      && !integer_zerop (TYPE_SIZE (type)))
	    परत असत्य;
	}
      अन्यथा
	{
	  /* If not complete but has a domain, it must be a FAM.  */
	  जर (NULL_वृक्ष != TYPE_DOMAIN (type)
	      && !flexible_array_member_type_p (type))
	    परत असत्य;
	}
    पूर्वनिर्धारित:
      थांबा;
    }
  परत सत्य;
}

/* Propagate C_TYPE_VARIABLY_MODIFIED and C_TYPE_VARIABLE_SIZE
   from a base type to a newly built derived or qualified type.  */

स्थिर वृक्ष
c_set_type_bits (वृक्ष new_type, वृक्ष old_type)
{
  gcc_checking_assert (c_verify_type (old_type));

  जर (c_type_variably_modified_p (old_type))
    C_TYPE_VARIABLY_MODIFIED (new_type) = सत्य;

  जर (वृक्ष_CODE (new_type) == ARRAY_TYPE && C_TYPE_VARIABLE_SIZE (old_type))
    {
      C_TYPE_VARIABLY_MODIFIED (new_type) = सत्य;
      C_TYPE_VARIABLE_SIZE (new_type) = सत्य;
    }
  परत new_type;
}

/* Build a pointer type using the default pointer mode.  */

वृक्ष
c_build_pointer_type (वृक्ष to_type)
{
  addr_space_t as = to_type == error_mark_गाठ ? ADDR_SPACE_GENERIC
					       : TYPE_ADDR_SPACE (to_type);
  machine_mode pointer_mode;

  जर (as != ADDR_SPACE_GENERIC || c_default_pointer_mode == VOIDmode)
    pointer_mode = targetm.addr_space.pointer_mode (as);
  अन्यथा
    pointer_mode = c_default_pointer_mode;

  परत c_build_pointer_type_for_mode (to_type, pointer_mode, असत्य);
}

/* Build a pointer type using the given mode.  */

वृक्ष
c_build_pointer_type_for_mode (वृक्ष type, machine_mode mode, तार्किक m)
{
  वृक्ष ret = build_pointer_type_for_mode (type, mode, m);
  परत c_set_type_bits (ret, type);
}

/* Build a function type.  */

वृक्ष
c_build_function_type (वृक्ष type, वृक्ष args, तार्किक no)
{
  वृक्ष ret = build_function_type (type, args, no);
  परत c_set_type_bits (ret, type);
}

/* Build an array type.  This sets typeless storage as required
   by C2Y and C_TYPE_VARIABLY_MODIFIED and C_TYPE_VARIABLE_SIZE
   based on the element type and domain.  */

वृक्ष
c_build_array_type (वृक्ष type, वृक्ष domain)
{
  पूर्णांक type_quals = TYPE_QUALS (type);

  /* Identify typeless storage as introduced in C2Y
     and supported also in earlier language modes.  */
  तार्किक typeless = (char_type_p (type) && !(type_quals & TYPE_QUAL_ATOMIC))
		  || (AGGREGATE_TYPE_P (type) && TYPE_TYPELESS_STORAGE (type));

  वृक्ष ret = build_array_type (type, domain, typeless);

  जर (शीर्ष_array_vla_p (ret))
    {
      C_TYPE_VARIABLE_SIZE (ret) = 1;
      C_TYPE_VARIABLY_MODIFIED (ret) = 1;
    }

  परत c_set_type_bits (ret, type);
}

/* Build an array type of unspecified size.  */
वृक्ष
c_build_array_type_unspecified (वृक्ष type)
{
  वृक्ष upper = build2 (COMPOUND_अभिव्यक्ती, वृक्ष_TYPE (size_zero_गाठ),
		       integer_zero_गाठ, size_zero_गाठ);
  परत c_build_array_type (type, build_index_type (upper));
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
  TYPE_SIZE (type) = bitsize_zero_गाठ;
  TYPE_SIZE_UNIT (type) = size_zero_गाठ;
  SET_TYPE_STRUCTURAL_EQUALITY (type);
  परत type;
}

वृक्ष
c_build_type_attribute_qual_variant (वृक्ष type, वृक्ष attrs, पूर्णांक quals)
{
  वृक्ष ret = build_type_attribute_qual_variant (type, attrs, quals);
  परत c_set_type_bits (ret, type);
}

वृक्ष
c_build_type_attribute_variant (वृक्ष type, वृक्ष attrs)
{
  परत c_build_type_attribute_qual_variant (type, attrs, TYPE_QUALS (type));
}

/* Reconstruct a complex derived type.  This is used to re-construct types
   with the vector attribute.  It is called via a langhook.  */

वृक्ष
c_reconstruct_complex_type (वृक्ष type, वृक्ष bottom)
{
  वृक्ष inner, outer;

  जर (वृक्ष_CODE (type) == POINTER_TYPE)
    {
      inner = c_reconstruct_complex_type (वृक्ष_TYPE (type), bottom);
      outer = c_build_pointer_type_for_mode (inner, TYPE_MODE (type),
					     TYPE_REF_CAN_ALIAS_ALL (type));
    }
  अन्यथा जर (वृक्ष_CODE (type) == ARRAY_TYPE)
    {
      तार्किक rso = TYPE_REVERSE_STORAGE_ORDER (type);
      inner = c_reconstruct_complex_type (वृक्ष_TYPE (type), bottom);
      outer = c_build_array_type (inner, TYPE_DOMAIN (type));
      जर (rso)
	{
	  outer = build_distinct_type_copy (outer);
	  TYPE_REVERSE_STORAGE_ORDER (outer) = 1;
	}

      gcc_checking_assert (C_TYPE_VARIABLE_SIZE (type)
			   == C_TYPE_VARIABLE_SIZE (outer));
    }
  अन्यथा जर (वृक्ष_CODE (type) == FUNCTION_TYPE)
    {
      inner = c_reconstruct_complex_type (वृक्ष_TYPE (type), bottom);
      outer = c_build_function_type (inner, TYPE_ARG_TYPES (type),
				     TYPE_NO_NAMED_ARGS_STDARG_P (type));
    }
  अन्यथा जर (वृक्ष_CODE (type) == REFERENCE_TYPE
	   || वृक्ष_CODE (type) == OFFSET_TYPE)
    gcc_unreachable ();
  अन्यथा
    परत bottom;

  परत c_build_type_attribute_qual_variant (outer, TYPE_ATTRIBUTES (type),
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
  पर्यंत (वृक्ष_CODE (type) == ARRAY_TYPE
	 || वृक्ष_CODE (type) == FUNCTION_TYPE
	 || वृक्ष_CODE (type) == POINTER_TYPE)
    {
      जर (वृक्ष_CODE (type) == POINTER_TYPE)
	ptr_seen = सत्य;
      type = वृक्ष_TYPE (type);
    }

  जर (ptr_seen
      && RECORD_OR_UNION_TYPE_P (type)
      && NULL_वृक्ष != c_type_tag (type))
    परत type;

  परत NULL_वृक्ष;
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
  साठी (वृक्ष x = TYPE_FIELDS (type); x; x = DECL_CHAIN (x))
    {
      जर (!ptr_to_tagged_member (x))
	सुरूठेवा;
      needs_mod = सत्य;
      थांबा;
    }
  जर (!needs_mod)
    परत type;

  /* Construct new version with such members replaced.  */
  वृक्ष n = build_distinct_type_copy (type);
  वृक्ष *fields = &TYPE_FIELDS (n);
  साठी (वृक्ष x = TYPE_FIELDS (type); x; x = DECL_CHAIN (x))
    {
      वृक्ष f = copy_गाठ (x);
      जर (वृक्ष m = ptr_to_tagged_member (x))
	{
	  वृक्ष new_गाठ = make_गाठ (वृक्ष_CODE (m));
	  TYPE_NAME (new_गाठ) = TYPE_NAME (m);
	  SET_TYPE_STRUCTURAL_EQUALITY (new_गाठ);
	  new_गाठ = qualify_type (new_गाठ, m);
	  वृक्ष_TYPE (f) = c_reconstruct_complex_type (वृक्ष_TYPE (x),
						      new_गाठ);
	}
      *fields = f;
      fields = &DECL_CHAIN (f);
    }
  TYPE_CANONICAL (n) = n;
  परत n;
}


/* If NTYPE is a type of a non-variadic function with a prototype
   and OTYPE is a type of a function without a prototype and ATTRS
   contains attribute format, diagnosess and removes it from ATTRS.
   Returns the result of build_type_attribute_variant of NTYPE and
   the (possibly) modified ATTRS.  */

स्थिर वृक्ष
c_build_functype_attribute_variant (वृक्ष ntype, वृक्ष otype, वृक्ष attrs)
{
  जर (!prototype_p (otype)
      && prototype_p (ntype)
      && lookup_attribute ("format", attrs))
    {
      warning_at (आदान_location, OPT_Wattributes,
		  "%qs attribute can only be applied to variadic functions",
		  "format");
      attrs = remove_attribute ("format", attrs);
    }
  परत c_build_type_attribute_variant (ntype, attrs);

}

/* Given a type which could be a typedef name, make sure to return the
   original type.  See set_underlying_type. */
स्थिर const_वृक्ष
c_type_original (const_वृक्ष t)
{
  /* It may even be a typedef of a typedef...
     In the case of compiler-created builtin structs the TYPE_DECL
     may be a dummy, with no DECL_ORIGINAL_TYPE.  Don't fault.  */
  पर्यंत (TYPE_NAME (t)
	 && वृक्ष_CODE (TYPE_NAME (t)) == TYPE_DECL
	 && DECL_ORIGINAL_TYPE (TYPE_NAME (t)))
    t = DECL_ORIGINAL_TYPE (TYPE_NAME (t));
  परत t;
}

/* Return the tag for a tagged type.  */
वृक्ष
c_type_tag (const_वृक्ष t)
{
  gcc_assert (RECORD_OR_UNION_TYPE_P (t) || वृक्ष_CODE (t) == ENUMERAL_TYPE);
  const_वृक्ष orig = c_type_original (t);
  वृक्ष name = TYPE_NAME (orig);
  जर (!name)
    परत NULL_वृक्ष;
  जर (वृक्ष_CODE (name) == TYPE_DECL)
    {
      जर (!DECL_NAME (name))
	परत NULL_वृक्ष;
      name = DECL_NAME (name);
    }
  gcc_checking_assert (वृक्ष_CODE (name) == IDENTIFIER_गाठ);
  परत name;
}

/* Remove qualifiers but not atomic.  For arrays remove qualifiers
   on the element type but also do not remove atomic.  */
स्थिर वृक्ष
remove_qualifiers (वृक्ष t)
{
  जर (!t || t == error_mark_गाठ)
    परत t;
  परत TYPE_ATOMIC (strip_array_types (t))
	 ? c_build_qualified_type (TYPE_MAIN_VARIANT (t), TYPE_QUAL_ATOMIC)
	 : TYPE_MAIN_VARIANT (t);
}


/* Helper function for composite_type_internal.  Find a compatible type
   in a (transparent) union U compatible to T.  If found, return the
   type of the corresponding member.  Otherwise, return the union type U.  */
स्थिर वृक्ष
transparent_union_replacement (वृक्ष u, वृक्ष t)
{
  जर (u == error_mark_गाठ || t == error_mark_गाठ
      || वृक्ष_CODE (u) != UNION_TYPE
      || !(TYPE_TRANSPARENT_AGGR (u) || TYPE_NAME (u) == NULL_वृक्ष)
      || comptypes (u, t))
    परत u;

  साठी (वृक्ष memb = TYPE_FIELDS (u); memb; memb = DECL_CHAIN (memb))
    {
      वृक्ष m = remove_qualifiers (वृक्ष_TYPE (memb));
      जर (comptypes (m, t))
	{
	  pedwarn (आदान_location, OPT_Wpedantic,
		    "function types not truly compatible in ISO C");
	  परत m;
	}
    }

  परत u;
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

  जर (t1 == t2) परत t1;

  /* If one type is nonsense, use the other.  */
  जर (t1 == error_mark_गाठ)
    परत t2;
  जर (t2 == error_mark_गाठ)
    परत t1;

  code1 = वृक्ष_CODE (t1);
  code2 = वृक्ष_CODE (t2);

  /* Merge the attributes.  */
  attributes = targetm.merge_type_attributes (t1, t2);

  /* If one is an enumerated type and the other is the compatible
     integer type, the composite type might be either of the two
     (DR#013 question 3).  For consistency, use the enumerated type as
     the composite type.  */

  जर (code1 == ENUMERAL_TYPE
      && (code2 == INTEGER_TYPE
	  || code2 == BOOLEAN_TYPE))
    परत t1;
  जर (code2 == ENUMERAL_TYPE
      && (code1 == INTEGER_TYPE
	  || code1 == BOOLEAN_TYPE))
    परत t2;

  gcc_assert (code1 == code2);

  निवड (code1)
    {
    स्थिती POINTER_TYPE:
      /* For two pointers, do this recursively on the target type.  */
      {
	gcc_checking_assert (TYPE_QUALS (t1) == TYPE_QUALS (t2));
	वृक्ष target = composite_type_internal (वृक्ष_TYPE (t1), वृक्ष_TYPE (t2),
					       cond, cache);
	वृक्ष n = c_build_pointer_type_for_mode (target, TYPE_MODE (t1), असत्य);
	परत c_build_type_attribute_qual_variant (n, attributes,
						    TYPE_QUALS (t2));
      }

    स्थिती ARRAY_TYPE:
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
	जर (d2_variable && c_type_unspecified_p (t1))
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

	जर (!use0)
	  {
	    /* Save space: see if the result is identical to one of the args.  */
	    जर (elt == वृक्ष_TYPE (t1) && use1)
	      परत c_build_type_attribute_variant (t1, attributes);
	    जर (elt == वृक्ष_TYPE (t2) && use2)
	      परत c_build_type_attribute_variant (t2, attributes);

	    जर (elt == वृक्ष_TYPE (t1) && !TYPE_DOMAIN (t2) && !TYPE_DOMAIN (t1))
	      परत c_build_type_attribute_variant (t1, attributes);
	    जर (elt == वृक्ष_TYPE (t2) && !TYPE_DOMAIN (t2) && !TYPE_DOMAIN (t1))
	      परत c_build_type_attribute_variant (t2, attributes);

	    td = TYPE_DOMAIN (use1 ? t1 : t2);
	  }
	अन्यथा
	  {
	    /* Not used in C.  */
	    gcc_assert (size_zero_गाठ == TYPE_MIN_मूल्य (d1));
	    gcc_assert (size_zero_गाठ == TYPE_MIN_मूल्य (d2));

	    वृक्ष d = fold_build3_loc (UNKNOWN_LOCATION, COND_अभिव्यक्ती, sizetype,
				      cond, TYPE_MAX_मूल्य (d1),
				      TYPE_MAX_मूल्य (d2));

	    td = build_index_type (d);
	  }

	/* Merge the element types, and have a size if either arg has
	   one.  We may have qualifiers on the element types.  To set
	   up TYPE_MAIN_VARIANT correctly, we need to form the
	   composite of the unqualified types and add the qualifiers
	   back at the end.  */
	पूर्णांक quals = TYPE_QUALS (strip_array_types (elt));
	वृक्ष unqual_elt = c_build_qualified_type (elt, TYPE_UNQUALIFIED);

	जर ((!d1 || d1_zero) && (!d2 || d2_zero) && (d1 || d2))
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
	परत c_build_type_attribute_variant (t1, attributes);
      }

    स्थिती RECORD_TYPE:
    स्थिती UNION_TYPE:
      जर (flag_isoc23 && !comptypes_same_p (t1, t2))
	{
	  /* Go to the original type to get the right tag.  */
	  वृक्ष tag = c_type_tag (t1);

	  gcc_checking_assert (COMPLETE_TYPE_P (t1) && COMPLETE_TYPE_P (t2));
	  gcc_checking_assert (!tag || comptypes (t1, t2));

	  /* If a composite type for these two types is already under
	     construction, return it.  */

	  साठी (संरचना composite_cache *c = cache; c != रिक्त; c = c->next)
	    जर ((c->t1 == t1 && c->t2 == t2) || (c->t1 == t2 && c->t2 == t1))
	       परत c->composite;

	  /* Otherwise, create a new type node and link it into the cache.  */

	  वृक्ष n = make_गाठ (code1);
	  SET_TYPE_STRUCTURAL_EQUALITY (n);
	  TYPE_NAME (n) = tag;

	  संरचना composite_cache cache2 = { t1, t2, n, cache };
	  cache = &cache2;

	  वृक्ष f1 = TYPE_FIELDS (t1);
	  वृक्ष f2 = TYPE_FIELDS (t2);
	  वृक्ष fields = NULL_वृक्ष;

	  साठी (वृक्ष a = f1, b = f2; a && b;
	       a = DECL_CHAIN (a), b = DECL_CHAIN (b))
	    {
	      वृक्ष ta = वृक्ष_TYPE (a);
	      वृक्ष tb = वृक्ष_TYPE (b);

	      जर (DECL_C_BIT_FIELD (a))
		{
		  ta = DECL_BIT_FIELD_TYPE (a);
		  tb = DECL_BIT_FIELD_TYPE (b);
		}

	      gcc_assert (DECL_NAME (a) == DECL_NAME (b));
	      gcc_checking_assert (!DECL_NAME (a) || comptypes (ta, tb));

	      वृक्ष t = composite_type_internal (ta, tb, cond, cache);
	      वृक्ष f = build_decl (आदान_location, FIELD_DECL, DECL_NAME (a), t);

	      DECL_PACKED (f) = DECL_PACKED (a);
	      SET_DECL_ALIGN (f, DECL_ALIGN (a));
	      DECL_ATTRIBUTES (f) = DECL_ATTRIBUTES (a);
	      C_DECL_VARIABLE_SIZE (f) = C_TYPE_VARIABLE_SIZE (t);

	      decl_attributes (&f, DECL_ATTRIBUTES (f), 0);

	      finish_decl (f, आदान_location, रिक्त, रिक्त, रिक्त);

	      जर (DECL_C_BIT_FIELD (a))
		{
		  /* This will be processed by finish_struct.  */
		  SET_DECL_C_BIT_FIELD (f);
		  DECL_INITIAL (f) = build_int_cst (integer_type_गाठ,
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
	  वृक्ष अभिव्यक्ती = NULL_वृक्ष;

	  /* Set TYPE_STUB_DECL for debugging symbols.  */
	  TYPE_STUB_DECL (n) = pushdecl (build_decl (आदान_location, TYPE_DECL,
						     NULL_वृक्ष, n));

	  n = finish_struct (आदान_location, n, fields, attributes, रिक्त,
			     &अभिव्यक्ती);

	  परत qualify_type (n, t1);
	}
      /* FALLTHRU */
    स्थिती ENUMERAL_TYPE:
      जर (attributes != रिक्त)
	{
	  /* Try harder not to create a new aggregate type.  */
	  जर (attribute_list_equal (TYPE_ATTRIBUTES (t1), attributes))
	    परत t1;
	  जर (attribute_list_equal (TYPE_ATTRIBUTES (t2), attributes))
	    परत t2;
	}
      परत c_build_type_attribute_variant (t1, attributes);

    स्थिती FUNCTION_TYPE:
      /* Function types: prefer the one that specified arg types.
	 If both do, merge the arg types.  Also merge the return types.  */
      {
	वृक्ष valtype = composite_type_internal (वृक्ष_TYPE (t1), वृक्ष_TYPE (t2),
						cond, cache);
	वृक्ष p1 = TYPE_ARG_TYPES (t1);
	वृक्ष p2 = TYPE_ARG_TYPES (t2);

	/* Save space: see if the result is identical to one of the args.  */
	जर (valtype == वृक्ष_TYPE (t1) && !TYPE_ARG_TYPES (t2))
	  परत c_build_functype_attribute_variant (t1, t2, attributes);
	जर (valtype == वृक्ष_TYPE (t2) && !TYPE_ARG_TYPES (t1))
	  परत c_build_functype_attribute_variant (t2, t1, attributes);

	/* Simple way if one arg fails to specify argument types.  */
	जर (TYPE_ARG_TYPES (t1) == NULL_वृक्ष)
	  {
	    t1 = c_build_function_type (valtype, TYPE_ARG_TYPES (t2),
					TYPE_NO_NAMED_ARGS_STDARG_P (t2));
	    t1 = c_build_type_attribute_variant (t1, attributes);
	    परत qualify_type (t1, t2);
	 }
	जर (TYPE_ARG_TYPES (t2) == NULL_वृक्ष)
	  {
	    t1 = c_build_function_type (valtype, TYPE_ARG_TYPES (t1),
					TYPE_NO_NAMED_ARGS_STDARG_P (t1));
	    t1 = c_build_type_attribute_variant (t1, attributes);
	    परत qualify_type (t1, t2);
	  }

	/* If both args specify argument types, we must merge the two
	   lists, argument by argument.  */
	वृक्ष newargs = NULL_वृक्ष;
	वृक्ष *endp = &newargs;

	साठी (; p1; p1 = वृक्ष_CHAIN (p1), p2 = वृक्ष_CHAIN (p2))
	  {
	    जर (p1 == void_list_गाठ)
	      {
		*endp = void_list_गाठ;
		थांबा;
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

    पूर्वनिर्धारित:
      परत c_build_type_attribute_variant (t1, attributes);
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
  परत n;
}


वृक्ष
composite_type (वृक्ष t1, वृक्ष t2)
{
  परत composite_type_cond (t1, t2, NULL_वृक्ष);
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
  पूर्णांक quals1, quals2;

  /* Save time if the two types are the same.  */

  जर (t1 == t2) परत t1;

  /* If one type is nonsense, use the other.  */
  जर (t1 == error_mark_गाठ)
    परत t2;
  जर (t2 == error_mark_गाठ)
    परत t1;

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
  जर (वृक्ष_CODE (pointed_to_1) == FUNCTION_TYPE)
    target_quals = (quals1 & quals2);
  अन्यथा
    target_quals = (quals1 | quals2);

  /* If the two named address spaces are different, determine the common
     superset address space.  This is guaranteed to exist due to the
     assumption that comp_target_type returned true.  */
  as1 = TYPE_ADDR_SPACE (pointed_to_1);
  as2 = TYPE_ADDR_SPACE (pointed_to_2);
  जर (!addr_space_superset (as1, as2, &as_common))
    gcc_unreachable ();

  target_quals |= ENCODE_QUAL_ADDR_SPACE (as_common);

  t1 = c_build_pointer_type (c_build_qualified_type (target, target_quals));
  परत c_build_type_attribute_variant (t1, attributes);
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
  जर (t1 == error_mark_गाठ)
    परत t2;
  जर (t2 == error_mark_गाठ)
    परत t1;

  जर (TYPE_QUALS (t1) != TYPE_UNQUALIFIED)
    t1 = TYPE_MAIN_VARIANT (t1);

  जर (TYPE_QUALS (t2) != TYPE_UNQUALIFIED)
    t2 = TYPE_MAIN_VARIANT (t2);

  जर (TYPE_ATTRIBUTES (t1) != NULL_वृक्ष)
    {
      वृक्ष attrs = affects_type_identity_attributes (TYPE_ATTRIBUTES (t1));
      t1 = c_build_type_attribute_variant (t1, attrs);
    }

  जर (TYPE_ATTRIBUTES (t2) != NULL_वृक्ष)
    {
      वृक्ष attrs = affects_type_identity_attributes (TYPE_ATTRIBUTES (t2));
      t2 = c_build_type_attribute_variant (t2, attrs);
    }

  /* Save time if the two types are the same.  */

  जर (t1 == t2) परत t1;

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
  जर ((DECIMAL_FLOAT_TYPE_P (t1) || DECIMAL_FLOAT_TYPE_P (t2))
      && !(DECIMAL_FLOAT_TYPE_P (t1) && DECIMAL_FLOAT_TYPE_P (t2)))
    {
      जर (code1 == VECTOR_TYPE || code2 == VECTOR_TYPE)
	{
	  error ("cannot mix operands of decimal floating and vector types");
	  परत error_mark_गाठ;
	}
      जर (code1 == COMPLEX_TYPE || code2 == COMPLEX_TYPE)
	{
	  error ("cannot mix operands of decimal floating and complex types");
	  परत error_mark_गाठ;
	}
      जर (code1 == REAL_TYPE && code2 == REAL_TYPE)
	{
	  error ("cannot mix operands of decimal floating "
		 "and other floating types");
	  परत error_mark_गाठ;
	}
    }

  /* If one type is a vector type, return that type.  (How the usual
     arithmetic conversions apply to the vector types extension is not
     precisely specified.)  */
  जर (code1 == VECTOR_TYPE)
    परत t1;

  जर (code2 == VECTOR_TYPE)
    परत t2;

  /* If one type is complex, form the common type of the non-complex
     components, then make that complex.  Use T1 or T2 if it is the
     required type.  */
  जर (code1 == COMPLEX_TYPE || code2 == COMPLEX_TYPE)
    {
      वृक्ष subtype1 = code1 == COMPLEX_TYPE ? वृक्ष_TYPE (t1) : t1;
      वृक्ष subtype2 = code2 == COMPLEX_TYPE ? वृक्ष_TYPE (t2) : t2;
      वृक्ष subtype = c_common_type (subtype1, subtype2);

      जर (code1 == COMPLEX_TYPE && वृक्ष_TYPE (t1) == subtype)
	परत t1;
      अन्यथा जर (code2 == COMPLEX_TYPE && वृक्ष_TYPE (t2) == subtype)
	परत t2;
      अन्यथा जर (वृक्ष_CODE (subtype) == BITINT_TYPE)
	{
	  sorry ("%<_Complex _BitInt(%d)%> unsupported",
		 TYPE_PRECISION (subtype));
	  परत code1 == COMPLEX_TYPE ? t1 : t2;
	}
      अन्यथा
	परत build_complex_type (subtype);
    }

  /* If only one is real, use it as the result.  */

  जर (code1 == REAL_TYPE && code2 != REAL_TYPE)
    परत t1;

  जर (code2 == REAL_TYPE && code1 != REAL_TYPE)
    परत t2;

  /* If both are real and either are decimal floating point types, use
     the decimal floating point type with the greater precision. */

  जर (code1 == REAL_TYPE && code2 == REAL_TYPE)
    {
      जर (TYPE_MAIN_VARIANT (t1) == dfloat128_type_गाठ
	  || TYPE_MAIN_VARIANT (t2) == dfloat128_type_गाठ)
	परत dfloat128_type_गाठ;
      /* And prefer _Decimal128 over _Decimal64x which has in GCC's
	 implementation the same mode.  */
      अन्यथा जर (TYPE_MAIN_VARIANT (t1) == dfloat64x_type_गाठ
	       || TYPE_MAIN_VARIANT (t2) == dfloat64x_type_गाठ)
	परत dfloat64x_type_गाठ;
      अन्यथा जर (TYPE_MAIN_VARIANT (t1) == dfloat64_type_गाठ
	       || TYPE_MAIN_VARIANT (t2) == dfloat64_type_गाठ)
	परत dfloat64_type_गाठ;
      अन्यथा जर (TYPE_MAIN_VARIANT (t1) == dfloat32_type_गाठ
	       || TYPE_MAIN_VARIANT (t2) == dfloat32_type_गाठ)
	परत dfloat32_type_गाठ;
    }

  /* Deal with fixed-point types.  */
  जर (code1 == FIXED_POINT_TYPE || code2 == FIXED_POINT_TYPE)
    {
      अचिन्हित पूर्णांक unsignedp = 0, satp = 0;
      scalar_mode m1, m2;
      अचिन्हित पूर्णांक fbit1, ibit1, fbit2, ibit2, max_fbit, max_ibit;

      m1 = SCALAR_TYPE_MODE (t1);
      m2 = SCALAR_TYPE_MODE (t2);

      /* If one input type is saturating, the result type is saturating.  */
      जर (TYPE_SATURATING (t1) || TYPE_SATURATING (t2))
	satp = 1;

      /* If both fixed-point types are unsigned, the result type is unsigned.
	 When mixing fixed-point and integer types, follow the sign of the
	 fixed-point type.
	 Otherwise, the result type is signed.  */
      जर ((TYPE_UNSIGNED (t1) && TYPE_UNSIGNED (t2)
	   && code1 == FIXED_POINT_TYPE && code2 == FIXED_POINT_TYPE)
	  || (code1 == FIXED_POINT_TYPE && code2 != FIXED_POINT_TYPE
	      && TYPE_UNSIGNED (t1))
	  || (code1 != FIXED_POINT_TYPE && code2 == FIXED_POINT_TYPE
	      && TYPE_UNSIGNED (t2)))
	unsignedp = 1;

      /* The result type is signed.  */
      जर (unsignedp == 0)
	{
	  /* If the input type is unsigned, we need to convert to the
	     signed type.  */
	  जर (code1 == FIXED_POINT_TYPE && TYPE_UNSIGNED (t1))
	    {
	      गणना mode_class mclass = (गणना mode_class) 0;
	      जर (GET_MODE_CLASS (m1) == MODE_UFRACT)
		mclass = MODE_FRACT;
	      अन्यथा जर (GET_MODE_CLASS (m1) == MODE_UACCUM)
		mclass = MODE_ACCUM;
	      अन्यथा
		gcc_unreachable ();
	      m1 = as_a <scalar_mode>
		(mode_for_size (GET_MODE_PRECISION (m1), mclass, 0));
	    }
	  जर (code2 == FIXED_POINT_TYPE && TYPE_UNSIGNED (t2))
	    {
	      गणना mode_class mclass = (गणना mode_class) 0;
	      जर (GET_MODE_CLASS (m2) == MODE_UFRACT)
		mclass = MODE_FRACT;
	      अन्यथा जर (GET_MODE_CLASS (m2) == MODE_UACCUM)
		mclass = MODE_ACCUM;
	      अन्यथा
		gcc_unreachable ();
	      m2 = as_a <scalar_mode>
		(mode_for_size (GET_MODE_PRECISION (m2), mclass, 0));
	    }
	}

      जर (code1 == FIXED_POINT_TYPE)
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

      जर (code2 == FIXED_POINT_TYPE)
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
      परत c_common_fixed_point_type_for_size (max_ibit, max_fbit, unsignedp,
						 satp);
    }

  /* Both real or both integers; use the one with greater precision.  */

  जर (TYPE_PRECISION (t1) > TYPE_PRECISION (t2))
    परत t1;
  अन्यथा जर (TYPE_PRECISION (t2) > TYPE_PRECISION (t1))
    परत t2;

  /* Same precision.  Prefer long longs to longs to ints when the
     same precision, following the C99 rules on integer type rank
     (which are equivalent to the C90 rules for C90 types).  */

  जर (TYPE_MAIN_VARIANT (t1) == long_long_unsigned_type_गाठ
      || TYPE_MAIN_VARIANT (t2) == long_long_unsigned_type_गाठ)
    परत long_long_unsigned_type_गाठ;

  जर (TYPE_MAIN_VARIANT (t1) == long_long_integer_type_गाठ
      || TYPE_MAIN_VARIANT (t2) == long_long_integer_type_गाठ)
    {
      जर (TYPE_UNSIGNED (t1) || TYPE_UNSIGNED (t2))
	परत long_long_unsigned_type_गाठ;
      अन्यथा
	परत long_long_integer_type_गाठ;
    }

  जर (TYPE_MAIN_VARIANT (t1) == long_unsigned_type_गाठ
      || TYPE_MAIN_VARIANT (t2) == long_unsigned_type_गाठ)
    परत long_unsigned_type_गाठ;

  जर (TYPE_MAIN_VARIANT (t1) == long_integer_type_गाठ
      || TYPE_MAIN_VARIANT (t2) == long_integer_type_गाठ)
    {
      /* But preserve unsignedness from the other type,
	 since long cannot hold all the values of an unsigned int.  */
      जर (TYPE_UNSIGNED (t1) || TYPE_UNSIGNED (t2))
	परत long_unsigned_type_गाठ;
      अन्यथा
	परत long_integer_type_गाठ;
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

  साठी (पूर्णांक i = अंक_FLOATN_TYPES - 1; i >= 0; i--)
    जर (mv1 == FLOATN_TYPE_गाठ (i) || mv2 == FLOATN_TYPE_गाठ (i))
      परत FLOATN_TYPE_गाठ (i);

  /* Likewise, prefer long double to double even if same size.  */
  जर (mv1 == long_double_type_गाठ || mv2 == long_double_type_गाठ)
    परत long_double_type_गाठ;

  /* Likewise, prefer double to float even if same size.
     We got a couple of embedded targets with 32 bit doubles, and the
     pdp11 might have 64 bit floats.  */
  जर (mv1 == double_type_गाठ || mv2 == double_type_गाठ)
    परत double_type_गाठ;

  जर (mv1 == float_type_गाठ || mv2 == float_type_गाठ)
    परत float_type_गाठ;

  साठी (पूर्णांक i = अंक_FLOATNX_TYPES - 1; i >= 0; i--)
    जर (mv1 == FLOATNX_TYPE_गाठ (i) || mv2 == FLOATNX_TYPE_गाठ (i))
      परत FLOATNX_TYPE_गाठ (i);

  जर ((code1 == BITINT_TYPE || code2 == BITINT_TYPE) && code1 != code2)
    {
      /* Prefer any other integral types over bit-precise integer types.  */
      जर (TYPE_UNSIGNED (t1) == TYPE_UNSIGNED (t2))
	परत code1 == BITINT_TYPE ? t2 : t1;
      /* If BITINT_TYPE is unsigned and the other type is signed
	 non-BITINT_TYPE with the same precision, the latter has higher rank.
	 In that case:
	 Otherwise, both operands are converted to the unsigned integer type
	 corresponding to the type of the operand with signed integer type.  */
      जर (TYPE_UNSIGNED (code1 == BITINT_TYPE ? t1 : t2))
	परत c_common_unsigned_type (code1 == BITINT_TYPE ? t2 : t1);
    }

  /* Otherwise prefer the unsigned one.  */

  जर (TYPE_UNSIGNED (t1))
    परत t1;
  अन्यथा
    परत t2;
}

/* Wrapper around c_common_type that is used by c-common.cc and other
   front end optimizations that remove promotions.  ENUMERAL_TYPEs
   are allowed here and are converted to their compatible integer types.
   BOOLEAN_TYPEs are allowed here and return either boolean_type_node or
   preferably a non-Boolean type as the common type.  */
वृक्ष
common_type (वृक्ष t1, वृक्ष t2)
{
  जर (वृक्ष_CODE (t1) == ENUMERAL_TYPE)
    t1 = ENUM_UNDERLYING_TYPE (t1);
  जर (वृक्ष_CODE (t2) == ENUMERAL_TYPE)
    t2 = ENUM_UNDERLYING_TYPE (t2);

  /* If both types are BOOLEAN_TYPE, then return boolean_type_node.  */
  जर (वृक्ष_CODE (t1) == BOOLEAN_TYPE
      && वृक्ष_CODE (t2) == BOOLEAN_TYPE)
    परत boolean_type_गाठ;

  /* If either type is BOOLEAN_TYPE, then return the other.  */
  जर (वृक्ष_CODE (t1) == BOOLEAN_TYPE)
    परत t2;
  जर (वृक्ष_CODE (t2) == BOOLEAN_TYPE)
    परत t1;

  परत c_common_type (t1, t2);
}



/* Helper function for comptypes.  For two compatible types, return 1
   if they pass consistency checks.  In particular we test that
   TYPE_CANONICAL is set correctly, i.e. the two types can alias.  */

स्थिर तार्किक
comptypes_verify (वृक्ष type1, वृक्ष type2)
{
  जर (type1 == type2 || !type1 || !type2
      || वृक्ष_CODE (type1) == ERROR_MARK || वृक्ष_CODE (type2) == ERROR_MARK)
    परत सत्य;

  gcc_checking_assert (c_verify_type (type1));
  gcc_checking_assert (c_verify_type (type2));

  जर (TYPE_CANONICAL (type1) != TYPE_CANONICAL (type2)
      && !TYPE_STRUCTURAL_EQUALITY_P (type1)
      && !TYPE_STRUCTURAL_EQUALITY_P (type2))
    {
      /* FIXME: check other types. */
      जर (RECORD_OR_UNION_TYPE_P (type1)
	  || वृक्ष_CODE (type1) == ENUMERAL_TYPE
	  || वृक्ष_CODE (type2) == ENUMERAL_TYPE)
	परत असत्य;
    }
  परत सत्य;
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

  स्थिरांक संरचना tagged_tu_seen_cache* cache;
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
  परत comptypes_internal (t1, t2, &data);
}


/* C implementation of compatible_types_for_indirection_note_p.  */

तार्किक
compatible_types_for_indirection_note_p (वृक्ष type1, वृक्ष type2)
{
  परत comptypes (type1, type2);
}

/* Return true if TYPE1 and TYPE2 are compatible types for assignment
   or various other operations.  */

तार्किक
comptypes (वृक्ष type1, वृक्ष type2)
{
  संरचना comptypes_data data = { };
  तार्किक ret = comptypes_internal (type1, type2, &data);

  gcc_checking_assert (!ret || comptypes_verify (type1, type2));

  परत ret;
}


/* Like comptypes, but it returns non-zero only for identical
   types.  */

तार्किक
comptypes_same_p (वृक्ष type1, वृक्ष type2)
{
  संरचना comptypes_data data = { };
  तार्किक ret = comptypes_internal (type1, type2, &data);

  gcc_checking_assert (!ret || comptypes_verify (type1, type2));

  जर (data.different_types_p)
    परत असत्य;

  परत ret;
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

  परत ret;
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

  परत ret;
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

  जर (t1 == t2 || !t1 || !t2
      || वृक्ष_CODE (t1) == ERROR_MARK || वृक्ष_CODE (t2) == ERROR_MARK)
    परत सत्य;

  /* Qualifiers must match. C99 6.7.3p9 */

  जर (TYPE_QUALS (t1) != TYPE_QUALS (t2))
    परत असत्य;

  /* Enumerated types are compatible with integer types, but this is
     not transitive: two enumerated types in the same translation unit
     are compatible with each other only if they are the same type.  */

  जर (वृक्ष_CODE (t1) == ENUMERAL_TYPE
      && COMPLETE_TYPE_P (t1)
      && वृक्ष_CODE (t2) != ENUMERAL_TYPE)
    {
      t1 = ENUM_UNDERLYING_TYPE (t1);
      जर (वृक्ष_CODE (t2) != VOID_TYPE)
	{
	  data->enum_and_int_p = सत्य;
	  data->different_types_p = सत्य;
	}
    }
  अन्यथा जर (वृक्ष_CODE (t2) == ENUMERAL_TYPE
	   && COMPLETE_TYPE_P (t2)
	   && वृक्ष_CODE (t1) != ENUMERAL_TYPE)
    {
      t2 = ENUM_UNDERLYING_TYPE (t2);
      जर (वृक्ष_CODE (t1) != VOID_TYPE)
	{
	  data->enum_and_int_p = सत्य;
	  data->different_types_p = सत्य;
	}
    }

  जर (t1 == t2)
    परत सत्य;

  /* Different classes of types can't be compatible.  */

  जर (वृक्ष_CODE (t1) != वृक्ष_CODE (t2))
    परत असत्य;

  /* Allow for two different type nodes which have essentially the same
     definition.  Note that we already checked for equality of the type
     qualifiers (just above).  */

  जर (वृक्ष_CODE (t1) != ARRAY_TYPE
      && TYPE_MAIN_VARIANT (t1) == TYPE_MAIN_VARIANT (t2))
    परत सत्य;

  पूर्णांक attrval;

  /* 1 if no need for warning yet, 2 if warning cause has been seen.  */
  जर (!(attrval = comp_type_attributes (t1, t2)))
    परत असत्य;

  जर (2 == attrval)
    data->warning_needed = सत्य;

  निवड (वृक्ष_CODE (t1))
    {
    स्थिती INTEGER_TYPE:
    स्थिती FIXED_POINT_TYPE:
    स्थिती REAL_TYPE:
    स्थिती BITINT_TYPE:
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
      परत TYPE_CANONICAL (t1) == TYPE_CANONICAL (t2);

    स्थिती POINTER_TYPE:
      /* Do not remove mode information.  */
      जर (TYPE_MODE (t1) != TYPE_MODE (t2))
	परत असत्य;
      data->pointedto = सत्य;
      परत comptypes_internal (वृक्ष_TYPE (t1), वृक्ष_TYPE (t2), data);

    स्थिती FUNCTION_TYPE:
      परत function_types_compatible_p (t1, t2, data);

    स्थिती ARRAY_TYPE:
      {
	वृक्ष d1 = TYPE_DOMAIN (t1);
	वृक्ष d2 = TYPE_DOMAIN (t2);

	/* Target types must match incl. qualifiers.  */
	जर (!comptypes_internal (वृक्ष_TYPE (t1), वृक्ष_TYPE (t2), data))
	  परत असत्य;

	जर ((d1 == NULL_वृक्ष) != (d2 == NULL_वृक्ष))
	  data->different_types_p = सत्य;
	/* Ignore size mismatches when forming equivalence classes.  */
	जर (data->equiv)
	  परत सत्य;
	/* Sizes must match unless one is missing or variable.  */
	जर (d1 == NULL_वृक्ष || d2 == NULL_वृक्ष || d1 == d2)
	  परत सत्य;

	तार्किक d1_variable = शीर्ष_array_vla_p (t1);
	तार्किक d2_variable = शीर्ष_array_vla_p (t2);

	जर (d1_variable != d2_variable)
	  data->different_types_p = सत्य;
	जर (d1_variable || d2_variable)
	  परत सत्य;

	तार्किक d1_zero = zero_length_array_type_p (t1)
		       || flexible_array_member_type_p (t1);

	तार्किक d2_zero = zero_length_array_type_p (t2)
		       || flexible_array_member_type_p (t2);

	जर (d1_zero && d2_zero)
	  परत सत्य;
	जर (d1_zero || d2_zero)
	  परत असत्य;

	जर (!वृक्ष_int_cst_equal (TYPE_MIN_मूल्य (d1), TYPE_MIN_मूल्य (d2))
	    || !वृक्ष_int_cst_equal (TYPE_MAX_मूल्य (d1), TYPE_MAX_मूल्य (d2)))
	  परत असत्य;

	परत सत्य;
      }

    स्थिती ENUMERAL_TYPE:
    स्थिती RECORD_TYPE:
    स्थिती UNION_TYPE:

      जर (!flag_isoc23)
	परत असत्य;

      परत tagged_types_tu_compatible_p (t1, t2, data);

    स्थिती VECTOR_TYPE:
      परत known_eq (TYPE_VECTOR_SUBPARTS (t1), TYPE_VECTOR_SUBPARTS (t2))
	     && comptypes_internal (वृक्ष_TYPE (t1), वृक्ष_TYPE (t2), data);

    पूर्वनिर्धारित:
      परत असत्य;
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
  जर (!addr_space_superset (asl, asr, &as_common))
    परत 0;

  /* Qualifiers on element types of array types that are
     pointer targets are also removed.  */
  संरचना comptypes_data data = { };
  जर (!comptypes_internal (remove_qualifiers (mvl),
			   remove_qualifiers (mvr), &data))
    परत असत्य;

  /* For pedantic use comptypes on arrays before removing
     qualifiers on the element type. */
  जर (वृक्ष_CODE (mvl) == ARRAY_TYPE
      && वृक्ष_CODE (mvr) == ARRAY_TYPE
      && !comptypes (mvl, mvr))
    pedwarn_c11 (location, OPT_Wpedantic, "invalid use of pointers to arrays "
					  "with different qualifiers in ISO C "
					  "before C23");

  जर (data.warning_needed)
    pedwarn (location, OPT_Wpedantic, "types are not quite compatible");

  जर (data.enum_and_int_p && warn_cxx_compat)
    warning_at (location, OPT_Wc___compat,
		"pointer target types incompatible in C++");

  परत सत्य;
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

  जर (c_type_tag (t1) != c_type_tag (t2))
    परत असत्य;

  /* When forming equivalence classes for TYPE_CANONICAL in C23, we treat
     structs with the same tag as equivalent, but only when they are targets
     of pointers inside other structs.  */
  जर (data->equiv && data->pointedto && NULL_वृक्ष != c_type_tag (t1))
    परत सत्य;

  /* Different types without tag are incompatible except as an anonymous
     field or when forming equivalence classes for TYPE_CANONICAL.  */
  जर (!data->anon_field && !data->equiv && NULL_वृक्ष == c_type_tag (t1))
    परत असत्य;

  जर (!data->anon_field && TYPE_STUB_DECL (t1) != TYPE_STUB_DECL (t2))
    data->different_types_p = सत्य;

  /* Incomplete types are incompatible inside a TU.  */
  जर (TYPE_SIZE (t1) == रिक्त || TYPE_SIZE (t2) == रिक्त)
    परत असत्य;

  जर (ENUMERAL_TYPE != वृक्ष_CODE (t1)
      && (TYPE_REVERSE_STORAGE_ORDER (t1)
	  != TYPE_REVERSE_STORAGE_ORDER (t2)))
    परत असत्य;

  जर (TYPE_USER_ALIGN (t1) != TYPE_USER_ALIGN (t2))
    data->different_types_p = सत्य;

  /* For types already being looked at in some active
     invocation of this function, assume compatibility.
     The cache is built as a linked list on the stack
     with the head of the list passed downwards.  */
  साठी (स्थिरांक संरचना tagged_tu_seen_cache *t = data->cache;
       t != रिक्त; t = t->next)
    जर (t->t1 == t1 && t->t2 == t2)
      परत सत्य;

  स्थिरांक संरचना tagged_tu_seen_cache entry = { data->cache, t1, t2 };

  निवड (वृक्ष_CODE (t1))
    {
    स्थिती ENUMERAL_TYPE:
      {
	जर (!comptypes (ENUM_UNDERLYING_TYPE (t1), ENUM_UNDERLYING_TYPE (t2)))
	  परत असत्य;

	/* Speed up the case where the type values are in the same order.  */
	वृक्ष tv1 = TYPE_मूल्ये (t1);
	वृक्ष tv2 = TYPE_मूल्ये (t2);

	जर (tv1 == tv2)
	  परत सत्य;

	साठी (;tv1 && tv2; tv1 = वृक्ष_CHAIN (tv1), tv2 = वृक्ष_CHAIN (tv2))
	  {
	    जर (वृक्ष_PURPOSE (tv1) != वृक्ष_PURPOSE (tv2))
	      थांबा;

	    जर (simple_cst_equal (DECL_INITIAL (वृक्ष_मूल्य (tv1)),
				  DECL_INITIAL (वृक्ष_मूल्य (tv2))) != 1)
	      थांबा;
	  }

	जर (tv1 == NULL_वृक्ष && tv2 == NULL_वृक्ष)
	  परत सत्य;

	जर (tv1 == NULL_वृक्ष || tv2 == NULL_वृक्ष)
	  परत असत्य;

	जर (list_length (TYPE_मूल्ये (t1)) != list_length (TYPE_मूल्ये (t2)))
	  परत असत्य;

	साठी (s1 = TYPE_मूल्ये (t1); s1; s1 = वृक्ष_CHAIN (s1))
	  {
	    s2 = purpose_member (वृक्ष_PURPOSE (s1), TYPE_मूल्ये (t2));

	    जर (s2 == रिक्त
		|| simple_cst_equal (DECL_INITIAL (वृक्ष_मूल्य (s1)),
				     DECL_INITIAL (वृक्ष_मूल्य (s2))) != 1)
	      परत असत्य;
	  }

	परत सत्य;
      }

    स्थिती UNION_TYPE:
    स्थिती RECORD_TYPE:

	जर (list_length (TYPE_FIELDS (t1)) != list_length (TYPE_FIELDS (t2)))
	  परत असत्य;

	साठी (s1 = TYPE_FIELDS (t1), s2 = TYPE_FIELDS (t2);
	     s1 && s2;
	     s1 = DECL_CHAIN (s1), s2 = DECL_CHAIN (s2))
	  {
	    gcc_assert (वृक्ष_CODE (s1) == FIELD_DECL);
	    gcc_assert (वृक्ष_CODE (s2) == FIELD_DECL);

	    वृक्ष ft1 = वृक्ष_TYPE (s1);
	    वृक्ष ft2 = वृक्ष_TYPE (s2);

	    जर (DECL_NAME (s1) != DECL_NAME (s2))
	      परत असत्य;

	    जर (DECL_ALIGN (s1) != DECL_ALIGN (s2))
	      परत असत्य;

	    जर (DECL_C_BIT_FIELD (s1) != DECL_C_BIT_FIELD (s2))
	       परत असत्य;

	    जर (DECL_C_BIT_FIELD (s1))
	      {
		जर (!वृक्ष_int_cst_equal (DECL_SIZE (s1), DECL_SIZE (s2)))
		  परत असत्य;

		ft1 = DECL_BIT_FIELD_TYPE (s1);
		ft2 = DECL_BIT_FIELD_TYPE (s2);
	      }

	    जर (!ft1 || !ft2)
	      परत असत्य;

	    जर (वृक्ष_CODE (ft1) == ERROR_MARK || वृक्ष_CODE (ft2) == ERROR_MARK)
	      परत असत्य;

	    data->anon_field = !DECL_NAME (s1);
	    data->pointedto = असत्य;

	    स्थिरांक संरचना tagged_tu_seen_cache *cache = data->cache;
	    data->cache = &entry;
	    तार्किक ret = comptypes_internal (ft1, ft2, data);
	    data->cache = cache;
	    जर (!ret)
	      परत असत्य;

	    वृक्ष st1 = TYPE_SIZE (वृक्ष_TYPE (s1));
	    वृक्ष st2 = TYPE_SIZE (वृक्ष_TYPE (s2));

	    जर (data->equiv
		&& st1 && वृक्ष_CODE (st1) == INTEGER_CST
		&& st2 && वृक्ष_CODE (st2) == INTEGER_CST
		&& !वृक्ष_int_cst_equal (st1, st2))
	     परत असत्य;

	    वृक्ष counted_by1 = lookup_attribute ("counted_by",
						 DECL_ATTRIBUTES (s1));
	    वृक्ष counted_by2 = lookup_attribute ("counted_by",
						 DECL_ATTRIBUTES (s2));
	    /* If there is no counted_by attribute for both fields.  */
	    जर (!counted_by1 && !counted_by2)
	      सुरूठेवा;

	    /* If only one field has counted_by attribute.  */
	    जर ((counted_by1 && !counted_by2)
		|| (!counted_by1 && counted_by2))
	      परत असत्य;

	    /* Now both s1 and s2 have counted_by attributes, check
	       whether they are the same.  */

	    वृक्ष counted_by_field1
	      = lookup_field (t1, वृक्ष_मूल्य (वृक्ष_मूल्य (counted_by1)));
	    वृक्ष counted_by_field2
	      = lookup_field (t2, वृक्ष_मूल्य (वृक्ष_मूल्य (counted_by2)));

	    gcc_assert (counted_by_field1 && counted_by_field2);

	    पर्यंत (वृक्ष_CHAIN (counted_by_field1))
	      counted_by_field1 = वृक्ष_CHAIN (counted_by_field1);
	    पर्यंत (वृक्ष_CHAIN (counted_by_field2))
	      counted_by_field2 = वृक्ष_CHAIN (counted_by_field2);

	    जर (DECL_NAME (वृक्ष_मूल्य (counted_by_field1))
		!= DECL_NAME (वृक्ष_मूल्य (counted_by_field2)))
	      परत असत्य;
	  }
	परत सत्य;

    पूर्वनिर्धारित:
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
  जर (TYPE_VOLATILE (ret1) != TYPE_VOLATILE (ret2))
    pedwarn (आदान_location, 0, "function return types not compatible due to %<volatile%>");
  जर (TYPE_VOLATILE (ret1))
    ret1 = build_qualified_type (TYPE_MAIN_VARIANT (ret1),
				 TYPE_QUALS (ret1) & ~TYPE_QUAL_VOLATILE);
  जर (TYPE_VOLATILE (ret2))
    ret2 = build_qualified_type (TYPE_MAIN_VARIANT (ret2),
				 TYPE_QUALS (ret2) & ~TYPE_QUAL_VOLATILE);

  तार्किक ignore_pargs = data->ignore_promoting_args;
  data->ignore_promoting_args = असत्य;

  जर (!comptypes_internal (ret1, ret2, data))
    परत असत्य;

  data->ignore_promoting_args = ignore_pargs;

  वृक्ष args1 = TYPE_ARG_TYPES (f1);
  वृक्ष args2 = TYPE_ARG_TYPES (f2);

  जर ((args1 == NULL_वृक्ष) != (args2 == NULL_वृक्ष))
    data->different_types_p = सत्य;

  /* An unspecified parmlist matches any specified parmlist
     whose argument types don't need default promotions.  */

  जर (args1 == NULL_वृक्ष)
    {
      जर (TYPE_NO_NAMED_ARGS_STDARG_P (f1) != TYPE_NO_NAMED_ARGS_STDARG_P (f2))
	परत असत्य;
      जर (!(data->ignore_promoting_args || self_promoting_args_p (args2)))
	परत असत्य;
      data->ignore_promoting_args = असत्य;
      /* If one of these types comes from a non-prototype fn definition,
	 compare that with the other type's arglist.
	 If they don't match, ask for a warning (but no error).  */
      जर (TYPE_ACTUAL_ARG_TYPES (f1)
	  && !type_lists_compatible_p (args2, TYPE_ACTUAL_ARG_TYPES (f1), data))
	 data->warning_needed = सत्य;
      परत सत्य;
    }
  जर (args2 == NULL_वृक्ष)
    {
      जर (TYPE_NO_NAMED_ARGS_STDARG_P (f1) != TYPE_NO_NAMED_ARGS_STDARG_P (f2))
	परत असत्य;
      जर (!(data->ignore_promoting_args || self_promoting_args_p (args1)))
	परत असत्य;
      data->ignore_promoting_args = असत्य;
      जर (TYPE_ACTUAL_ARG_TYPES (f2)
	  && !type_lists_compatible_p (args1, TYPE_ACTUAL_ARG_TYPES (f2), data))
	data->warning_needed = सत्य;
      परत सत्य;
    }

  /* Both types have argument lists: compare them and propagate results.  */
  परत type_lists_compatible_p (args1, args2, data);
}

/* Check two lists of types for compatibility, returning false for
   incompatible, true for compatible.  */

स्थिर तार्किक
type_lists_compatible_p (const_वृक्ष args1, const_वृक्ष args2,
			 संरचना comptypes_data *data)
{
  पर्यंत (1)
    {
      जर (args1 == NULL_वृक्ष && args2 == NULL_वृक्ष)
	परत सत्य;
      /* If one list is shorter than the other,
	 they fail to match.  */
      जर (args1 == NULL_वृक्ष || args2 == NULL_वृक्ष)
	परत असत्य;
      वृक्ष a1 = वृक्ष_मूल्य (args1);
      वृक्ष a2 = वृक्ष_मूल्य (args2);
      वृक्ष mv1 = remove_qualifiers (a1);
      वृक्ष mv2 = remove_qualifiers (a2);

      gcc_assert (mv2);
      gcc_assert (mv2);

      /* If one of the lists has an error marker, ignore this arg.  */
      जर (वृक्ष_CODE (a1) == ERROR_MARK
	       || वृक्ष_CODE (a2) == ERROR_MARK)
	;
      अन्यथा जर (!comptypes_internal (mv1, mv2, data))
	{
	  data->different_types_p = सत्य;
	  /* Allow  wait (union {union wait *u; int *i} *)
	     and  wait (union wait *)  to be compatible.  */
	  जर (वृक्ष_CODE (a1) == UNION_TYPE
	      && (TYPE_NAME (a1) == NULL_वृक्ष
		  || TYPE_TRANSPARENT_AGGR (a1))
	      && वृक्ष_CODE (TYPE_SIZE (a1)) == INTEGER_CST
	      && वृक्ष_int_cst_equal (TYPE_SIZE (a1),
				     TYPE_SIZE (a2)))
	    {
	      वृक्ष memb;
	      साठी (memb = TYPE_FIELDS (a1);
		   memb; memb = DECL_CHAIN (memb))
		{
		  वृक्ष mv3 = remove_qualifiers (वृक्ष_TYPE (memb));
		  जर (comptypes_internal (mv3, mv2, data))
		    थांबा;
		}
	      जर (memb == NULL_वृक्ष)
		परत असत्य;
	    }
	  अन्यथा जर (वृक्ष_CODE (a2) == UNION_TYPE
		   && (TYPE_NAME (a2) == NULL_वृक्ष
		       || TYPE_TRANSPARENT_AGGR (a2))
		   && वृक्ष_CODE (TYPE_SIZE (a2)) == INTEGER_CST
		   && वृक्ष_int_cst_equal (TYPE_SIZE (a2),
					  TYPE_SIZE (a1)))
	    {
	      वृक्ष memb;
	      साठी (memb = TYPE_FIELDS (a2);
		   memb; memb = DECL_CHAIN (memb))
		{
		  वृक्ष mv3 = remove_qualifiers (वृक्ष_TYPE (memb));
		  जर (comptypes_internal (mv3, mv1, data))
		    थांबा;
		}
	      जर (memb == NULL_वृक्ष)
		परत असत्य;
	    }
	  अन्यथा
	    परत असत्य;
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

  जर (code == FUNCTION_TYPE || code == VOID_TYPE || code == ERROR_MARK
      || !COMPLETE_TYPE_P (type))
    परत size_one_गाठ;

  /* Convert in case a char is more than one unit.  */
  परत size_binop_loc (आदान_location, CEIL_DIV_अभिव्यक्ती, TYPE_SIZE_UNIT (type),
			 size_int (TYPE_PRECISION (char_type_गाठ)
				   / BITS_PER_UNIT));
}

/* Return either DECL or its known constant value (if it has one).  */

वृक्ष
decl_constant_मूल्य_1 (वृक्ष decl, तार्किक in_init)
{
  जर (/* Note that DECL_INITIAL isn't valid for a PARM_DECL.  */
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
    परत DECL_INITIAL (decl);
  परत decl;
}

/* Return either DECL or its known constant value (if it has one).
   Like the above, but always return decl outside of functions.  */

वृक्ष
decl_constant_मूल्य (वृक्ष decl)
{
  /* Don't change a variable array bound or initial value to a constant
     in a place where a variable is invalid.  */
  परत current_function_decl ? decl_constant_मूल्य_1 (decl, असत्य) : decl;
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

  जर (INDIRECT_REF_P (exp))
    परत convert (ptrtype, वृक्ष_OPERAND (exp, 0));

  /* In C++ array compound literals are temporary objects unless they are
     const or appear in namespace scope, so they are destroyed too soon
     to use them for much of anything  (c++/53220).  */
  जर (warn_cxx_compat && वृक्ष_CODE (exp) == COMPOUND_LITERAL_अभिव्यक्ती)
    {
      वृक्ष decl = वृक्ष_OPERAND (वृक्ष_OPERAND (exp, 0), 0);
      जर (!वृक्ष_READONLY (decl) && !वृक्ष_STATIC (decl))
	warning_at (DECL_SOURCE_LOCATION (decl), OPT_Wc___compat,
		    "converting an array compound literal to a pointer "
		    "leads to a dangling pointer in C++");
    }

  adr = build_unary_op (loc, ADDR_अभिव्यक्ती, exp, सत्य);
  परत convert (ptrtype, adr);
}

/* Convert the function expression EXP to a pointer.  */
स्थिर वृक्ष
function_to_pointer_conversion (location_t loc, वृक्ष exp)
{
  वृक्ष orig_exp = exp;

  gcc_assert (वृक्ष_CODE (वृक्ष_TYPE (exp)) == FUNCTION_TYPE);

  STRIP_TYPE_NOPS (exp);

  copy_warning (exp, orig_exp);

  वृक्ष exp2 = build_unary_op (loc, ADDR_अभिव्यक्ती, exp, असत्य);

  /* If the function is defined and known to not require a non-local
     context, make sure no trampoline is generated.  */
  जर (वृक्ष_CODE (exp) == FUNCTION_DECL
      && DECL_INITIAL (exp) && !C_FUNC_NONLOCAL_CONTEXT (exp))
   वृक्ष_NO_TRAMPOLINE (exp2) = 1;

  परत exp2;
}

/* Mark EXP as read, not just set, for set but not used -Wunused
   warning purposes.  */

शून्य
mark_exp_read (वृक्ष exp)
{
  निवड (वृक्ष_CODE (exp))
    {
    स्थिती VAR_DECL:
    स्थिती PARM_DECL:
      DECL_READ_P (exp) = 1;
      थांबा;
    CASE_CONVERT:
      जर (VOID_TYPE_P (वृक्ष_TYPE (exp)))
	निवड (वृक्ष_CODE (वृक्ष_OPERAND (exp, 0)))
	  {
	  स्थिती PREINCREMENT_अभिव्यक्ती:
	  स्थिती PREDECREMENT_अभिव्यक्ती:
	  स्थिती POSTINCREMENT_अभिव्यक्ती:
	  स्थिती POSTDECREMENT_अभिव्यक्ती:
	    परत;
	  पूर्वनिर्धारित:
	    थांबा;
	  }
      /* FALLTHRU */
    स्थिती ARRAY_REF:
    स्थिती COMPONENT_REF:
    स्थिती MODIFY_अभिव्यक्ती:
    स्थिती REALPART_अभिव्यक्ती:
    स्थिती IMAGPART_अभिव्यक्ती:
    स्थिती ADDR_अभिव्यक्ती:
    स्थिती VIEW_CONVERT_अभिव्यक्ती:
    स्थिती PREINCREMENT_अभिव्यक्ती:
    स्थिती PREDECREMENT_अभिव्यक्ती:
    स्थिती POSTINCREMENT_अभिव्यक्ती:
    स्थिती POSTDECREMENT_अभिव्यक्ती:
      mark_exp_read (वृक्ष_OPERAND (exp, 0));
      थांबा;
    स्थिती COMPOUND_अभिव्यक्ती:
      /* Pattern match what build_atomic_assign produces with modifycode
	 NOP_EXPR.  */
      जर (VAR_P (वृक्ष_OPERAND (exp, 1))
	  && DECL_ARTIFICIAL (वृक्ष_OPERAND (exp, 1))
	  && वृक्ष_CODE (वृक्ष_OPERAND (exp, 0)) == COMPOUND_अभिव्यक्ती)
	{
	  वृक्ष t1 = वृक्ष_OPERAND (वृक्ष_OPERAND (exp, 0), 0);
	  वृक्ष t2 = वृक्ष_OPERAND (वृक्ष_OPERAND (exp, 0), 1);
	  जर (वृक्ष_CODE (t1) == TARGET_अभिव्यक्ती
	      && TARGET_अभिव्यक्ती_SLOT (t1) == वृक्ष_OPERAND (exp, 1)
	      && वृक्ष_CODE (t2) == CALL_अभिव्यक्ती)
	    {
	      वृक्ष fndecl = get_callee_fndecl (t2);
	      वृक्ष arg = NULL_वृक्ष;
	      जर (fndecl
		  && वृक्ष_CODE (fndecl) == FUNCTION_DECL
		  && fndecl_built_in_p (fndecl, BUILT_IN_NORMAL)
		  && call_अभिव्यक्ती_nargs (t2) >= 2)
		निवड (DECL_FUNCTION_CODE (fndecl))
		  {
		  स्थिती BUILT_IN_ATOMIC_STORE:
		    arg = CALL_अभिव्यक्ती_ARG (t2, 1);
		    थांबा;
		  स्थिती BUILT_IN_ATOMIC_STORE_1:
		  स्थिती BUILT_IN_ATOMIC_STORE_2:
		  स्थिती BUILT_IN_ATOMIC_STORE_4:
		  स्थिती BUILT_IN_ATOMIC_STORE_8:
		  स्थिती BUILT_IN_ATOMIC_STORE_16:
		    arg = CALL_अभिव्यक्ती_ARG (t2, 0);
		    थांबा;
		  पूर्वनिर्धारित:
		    थांबा;
		  }
	      जर (arg)
		{
		  STRIP_NOPS (arg);
		  जर (वृक्ष_CODE (arg) == ADDR_अभिव्यक्ती
		      && DECL_P (वृक्ष_OPERAND (arg, 0))
		      && TYPE_ATOMIC (वृक्ष_TYPE (वृक्ष_OPERAND (arg, 0))))
		    mark_exp_read (वृक्ष_OPERAND (arg, 0));
		}
	    }
	}
      /* FALLTHRU */
    स्थिती C_MAYBE_CONST_अभिव्यक्ती:
      mark_exp_read (वृक्ष_OPERAND (exp, 1));
      थांबा;
    स्थिती OMP_ARRAY_SECTION:
      mark_exp_read (वृक्ष_OPERAND (exp, 0));
      जर (वृक्ष_OPERAND (exp, 1))
	mark_exp_read (वृक्ष_OPERAND (exp, 1));
      जर (वृक्ष_OPERAND (exp, 2))
	mark_exp_read (वृक्ष_OPERAND (exp, 2));
      थांबा;
    पूर्वनिर्धारित:
      थांबा;
    }
}

/* Perform the default conversion of arrays and functions to pointers.
   Return the result of converting EXP.  For any other expression, just
   return EXP.

   LOC is the location of the expression.  */

संरचना c_अभिव्यक्ती
default_function_array_conversion (location_t loc, संरचना c_अभिव्यक्ती exp)
{
  वृक्ष orig_exp = exp.मूल्य;
  वृक्ष type = वृक्ष_TYPE (exp.मूल्य);
  गणना वृक्ष_code code = वृक्ष_CODE (type);

  निवड (code)
    {
    स्थिती ARRAY_TYPE:
      {
	तार्किक not_lvalue = असत्य;
	तार्किक lvalue_array_p;

	पर्यंत ((वृक्ष_CODE (exp.मूल्य) == NON_LVALUE_अभिव्यक्ती
		|| CONVERT_अभिव्यक्ती_P (exp.मूल्य))
	       && वृक्ष_TYPE (वृक्ष_OPERAND (exp.मूल्य, 0)) == type)
	  {
	    जर (वृक्ष_CODE (exp.मूल्य) == NON_LVALUE_अभिव्यक्ती)
	      not_lvalue = सत्य;
	    exp.मूल्य = वृक्ष_OPERAND (exp.मूल्य, 0);
	  }

	copy_warning (exp.मूल्य, orig_exp);

	lvalue_array_p = !not_lvalue && lvalue_p (exp.मूल्य);
	जर (!flag_isoc99 && !lvalue_array_p)
	  {
	    /* Before C99, non-lvalue arrays do not decay to pointers.
	       Normally, using such an array would be invalid; but it can
	       be used correctly inside sizeof or as a statement expression.
	       Thus, do not give an error here; an error will result later.  */
	    परत exp;
	  }

	exp.मूल्य = array_to_pointer_conversion (loc, exp.मूल्य);
      }
      थांबा;
    स्थिती FUNCTION_TYPE:
      exp.मूल्य = function_to_pointer_conversion (loc, exp.मूल्य);
      थांबा;
    पूर्वनिर्धारित:
      थांबा;
    }

  परत exp;
}

संरचना c_अभिव्यक्ती
default_function_array_read_conversion (location_t loc, संरचना c_अभिव्यक्ती exp)
{
  mark_exp_read (exp.मूल्य);
  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  जर (वृक्ष_CODE (exp.मूल्य) == COMPONENT_REF
      && handle_counted_by_p (exp.मूल्य))
    exp.मूल्य = handle_counted_by_for_component_ref (loc, exp.मूल्य);
  परत default_function_array_conversion (loc, exp);
}

/* Return whether EXPR should be treated as an atomic lvalue for the
   purposes of load and store handling.  */

स्थिर तार्किक
really_atomic_lvalue (वृक्ष अभिव्यक्ती)
{
  जर (error_operand_p (अभिव्यक्ती))
    परत असत्य;
  जर (!TYPE_ATOMIC (वृक्ष_TYPE (अभिव्यक्ती)))
    परत असत्य;
  जर (!COMPLETE_TYPE_P (वृक्ष_TYPE (अभिव्यक्ती)))
    परत असत्य;
  जर (!lvalue_p (अभिव्यक्ती))
    परत असत्य;

  /* Ignore _Atomic on register variables, since their addresses can't
     be taken so (a) atomicity is irrelevant and (b) the normal atomic
     sequences wouldn't work.  Ignore _Atomic on structures containing
     bit-fields, since accessing elements of atomic structures or
     unions is undefined behavior (C11 6.5.2.3#5), but it's unclear if
     it's undefined at translation time or execution time, and the
     normal atomic sequences again wouldn't work.  */
  पर्यंत (handled_component_p (अभिव्यक्ती))
    {
      जर (वृक्ष_CODE (अभिव्यक्ती) == COMPONENT_REF
	  && DECL_C_BIT_FIELD (वृक्ष_OPERAND (अभिव्यक्ती, 1)))
	परत असत्य;
      अभिव्यक्ती = वृक्ष_OPERAND (अभिव्यक्ती, 0);
    }
  जर (वृक्ष_CODE (अभिव्यक्ती) == COMPOUND_LITERAL_अभिव्यक्ती)
    अभिव्यक्ती = COMPOUND_LITERAL_अभिव्यक्ती_DECL (अभिव्यक्ती);
  जर (DECL_P (अभिव्यक्ती) && C_DECL_REGISTER (अभिव्यक्ती))
    परत असत्य;
  परत सत्य;
}

/* If EXPR is a named constant (C23) derived from a constexpr variable
   - that is, a reference to such a variable, or a member extracted by
   a sequence of structure and union (but not array) member accesses
   (where union member accesses must access the same member as
   initialized) - then return the corresponding initializer;
   otherwise, return NULL_TREE.  */

स्थिर वृक्ष
maybe_get_constexpr_init (वृक्ष अभिव्यक्ती)
{
  वृक्ष decl = NULL_वृक्ष;
  जर (वृक्ष_CODE (अभिव्यक्ती) == VAR_DECL)
    decl = अभिव्यक्ती;
  अन्यथा जर (वृक्ष_CODE (अभिव्यक्ती) == COMPOUND_LITERAL_अभिव्यक्ती)
    decl = COMPOUND_LITERAL_अभिव्यक्ती_DECL (अभिव्यक्ती);
  जर (decl
      && C_DECL_DECLARED_CONSTEXPR (decl)
      && DECL_INITIAL (decl) != NULL_वृक्ष
      && !error_operand_p (DECL_INITIAL (decl)))
    परत DECL_INITIAL (decl);
  जर (वृक्ष_CODE (अभिव्यक्ती) != COMPONENT_REF)
    परत NULL_वृक्ष;
  वृक्ष inner = maybe_get_constexpr_init (वृक्ष_OPERAND (अभिव्यक्ती, 0));
  जर (inner == NULL_वृक्ष)
    परत NULL_वृक्ष;
  पर्यंत ((CONVERT_अभिव्यक्ती_P (inner) || वृक्ष_CODE (inner) == NON_LVALUE_अभिव्यक्ती)
	 && !error_operand_p (inner)
	 && (TYPE_MAIN_VARIANT (वृक्ष_TYPE (inner))
	     == TYPE_MAIN_VARIANT (वृक्ष_TYPE (वृक्ष_OPERAND (inner, 0)))))
    inner = वृक्ष_OPERAND (inner, 0);
  जर (वृक्ष_CODE (inner) != CONSTRUCTOR)
    परत NULL_वृक्ष;
  वृक्ष field = वृक्ष_OPERAND (अभिव्यक्ती, 1);
  अचिन्हित HOST_WIDE_INT cidx;
  वृक्ष cfield, cvalue;
  तार्किक have_other_init = असत्य;
  FOR_EACH_CONSTRUCTOR_ELT (CONSTRUCTOR_ELTS (inner), cidx, cfield, cvalue)
    {
      जर (cfield == field)
	परत cvalue;
      have_other_init = सत्य;
    }
  जर (वृक्ष_CODE (वृक्ष_TYPE (inner)) == UNION_TYPE
      && (have_other_init || field != TYPE_FIELDS (वृक्ष_TYPE (inner))))
    परत NULL_वृक्ष;
  /* Return a default initializer.  */
  जर (RECORD_OR_UNION_TYPE_P (वृक्ष_TYPE (अभिव्यक्ती)))
    परत build_constructor (वृक्ष_TYPE (अभिव्यक्ती), रिक्त);
  परत build_zero_cst (वृक्ष_TYPE (अभिव्यक्ती));
}

/* Helper function for convert_lvalue_to_rvalue called via
   walk_tree_without_duplicates.  Find DATA inside of the expression.  */

स्थिर वृक्ष
c_find_var_r (वृक्ष *tp, पूर्णांक *walk_subtrees, शून्य *data)
{
  जर (TYPE_P (*tp))
    *walk_subtrees = 0;
  अन्यथा जर (*tp == (वृक्ष) data)
    परत *tp;
  परत NULL_वृक्ष;
}

/* Convert expression EXP (location LOC) from lvalue to rvalue,
   including converting functions and arrays to pointers if CONVERT_P.
   If READ_P, also mark the expression as having been read.  If
   FOR_INIT, constexpr expressions of structure and union type should
   be replaced by the corresponding CONSTRUCTOR; otherwise, only
   constexpr scalars (including elements of structures and unions) are
   replaced by their initializers.  */

संरचना c_अभिव्यक्ती
convert_lvalue_to_rvalue (location_t loc, संरचना c_अभिव्यक्ती exp,
			  तार्किक convert_p, तार्किक read_p, तार्किक for_init)
{
  तार्किक force_non_npc = असत्य;
  जर (read_p)
    mark_exp_read (exp.मूल्य);
  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  जर (read_p && वृक्ष_CODE (exp.मूल्य) == COMPONENT_REF
      && handle_counted_by_p (exp.मूल्य))
    exp.मूल्य = handle_counted_by_for_component_ref (loc, exp.मूल्य);

  जर (convert_p)
    exp = default_function_array_conversion (loc, exp);
  जर (!VOID_TYPE_P (वृक्ष_TYPE (exp.मूल्य))
      || (flag_isoc2y
	  && TYPE_QUALS (वृक्ष_TYPE (exp.मूल्य)) != TYPE_UNQUALIFIED))
    exp.मूल्य = require_complete_type (loc, exp.मूल्य);
  जर (for_init || !RECORD_OR_UNION_TYPE_P (वृक्ष_TYPE (exp.मूल्य)))
    {
      वृक्ष init = maybe_get_constexpr_init (exp.मूल्य);
      जर (init != NULL_वृक्ष)
	{
	  /* A named constant of pointer type or type nullptr_t is not
	     a null pointer constant even if the initializer is
	     one.  */
	  जर (वृक्ष_CODE (init) == INTEGER_CST
	      && !INTEGRAL_TYPE_P (वृक्ष_TYPE (init))
	      && integer_zerop (init))
	    force_non_npc = सत्य;
	  exp.मूल्य = init;
	}
    }
  जर (really_atomic_lvalue (exp.मूल्य))
    {
      vec<वृक्ष, va_gc> *params;
      वृक्ष nonatomic_type, tmp, tmp_addr, fndecl, func_call;
      वृक्ष अभिव्यक्ती_type = वृक्ष_TYPE (exp.मूल्य);
      वृक्ष अभिव्यक्ती_addr = build_unary_op (loc, ADDR_अभिव्यक्ती, exp.मूल्य, असत्य);
      वृक्ष seq_cst = build_int_cst (integer_type_गाठ, MEMMODEL_SEQ_CST);

      gcc_assert (TYPE_ATOMIC (अभिव्यक्ती_type));

      /* Expansion of a generic atomic load may require an addition
	 element, so allocate enough to prevent a resize.  */
      vec_alloc (params, 4);

      /* Remove the qualifiers for the rest of the expressions and
	 create the VAL temp variable to hold the RHS.  */
      nonatomic_type = build_qualified_type (अभिव्यक्ती_type, TYPE_UNQUALIFIED);
      tmp = create_tmp_var_raw (nonatomic_type);
      tmp_addr = build_unary_op (loc, ADDR_अभिव्यक्ती, tmp, असत्य);
      वृक्ष_ADDRESSABLE (tmp) = 1;
      /* Do not disable warnings for TMP even though it's artificial.
	 -Winvalid-memory-model depends on it.  */

      /* Issue __atomic_load (&expr, &tmp, SEQ_CST);  */
      fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_LOAD);
      params->quick_ढकला (अभिव्यक्ती_addr);
      params->quick_ढकला (tmp_addr);
      params->quick_ढकला (seq_cst);
      func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, रिक्त);

      /* EXPR is always read.  */
      mark_exp_read (exp.मूल्य);

      /* Optimize the common case where c_build_function_call_vec
	 immediately folds __atomic_load (&expr, &tmp, SEQ_CST); into
	 tmp = __atomic_load_<N> (&expr, SEQ_CST);
	 In that case tmp is not addressable and can be initialized
	 fully by the rhs of the MODIFY_EXPR.  */
      वृक्ष tem = func_call;
      जर (CONVERT_अभिव्यक्ती_P (tem) && VOID_TYPE_P (वृक्ष_TYPE (tem)))
	{
	  tem = वृक्ष_OPERAND (tem, 0);
	  जर (वृक्ष_CODE (tem) == MODIFY_अभिव्यक्ती
	      && वृक्ष_OPERAND (tem, 0) == tmp
	      && !walk_वृक्ष_without_duplicates (&वृक्ष_OPERAND (tem, 1),
						c_find_var_r, tmp))
	    {
	      वृक्ष_ADDRESSABLE (tmp) = 0;
	      func_call = वृक्ष_OPERAND (tem, 1);
	    }
	}

      /* Return tmp which contains the value loaded.  */
      exp.मूल्य = build4 (TARGET_अभिव्यक्ती, nonatomic_type, tmp, func_call,
			  NULL_वृक्ष, NULL_वृक्ष);
    }
  जर (convert_p && !error_operand_p (exp.मूल्य)
      && (वृक्ष_CODE (वृक्ष_TYPE (exp.मूल्य)) != ARRAY_TYPE))
    exp.मूल्य = convert (build_qualified_type (वृक्ष_TYPE (exp.मूल्य), TYPE_UNQUALIFIED), exp.मूल्य);
  जर (force_non_npc)
    exp.मूल्य = build1 (NOP_अभिव्यक्ती, वृक्ष_TYPE (exp.मूल्य), exp.मूल्य);

  {
    वृक्ष false_मूल्य, true_मूल्य;
    जर (convert_p && !error_operand_p (exp.मूल्य)
	&& c_hardbool_type_attr (वृक्ष_TYPE (exp.मूल्य),
				 &false_मूल्य, &true_मूल्य))
      {
	वृक्ष t = save_अभिव्यक्ती (exp.मूल्य);

	mark_exp_read (exp.मूल्य);

	वृक्ष trapfn = builtin_decl_explicit (BUILT_IN_TRAP);
	वृक्ष अभिव्यक्ती = build_call_अभिव्यक्ती_loc (loc, trapfn, 0);
	अभिव्यक्ती = build_compound_अभिव्यक्ती (loc, अभिव्यक्ती, boolean_true_गाठ);
	अभिव्यक्ती = fold_build3_loc (loc, COND_अभिव्यक्ती, boolean_type_गाठ,
				fold_build2_loc (loc, NE_अभिव्यक्ती,
						 boolean_type_गाठ,
						 t, true_मूल्य),
				अभिव्यक्ती, boolean_true_गाठ);
	अभिव्यक्ती = fold_build3_loc (loc, COND_अभिव्यक्ती, boolean_type_गाठ,
				fold_build2_loc (loc, NE_अभिव्यक्ती,
						 boolean_type_गाठ,
						 t, false_मूल्य),
				अभिव्यक्ती, boolean_false_गाठ);

	exp.मूल्य = अभिव्यक्ती;
      }
  }

  परत exp;
}

/* Wrapper for the overload above, same arguments but for tree rather than
   c_expr.  This is important for hardbools to decay to bools.  */

स्थिर ओळीत वृक्ष
convert_lvalue_to_rvalue (location_t loc, वृक्ष val,
			  तार्किक convert_p, तार्किक read_p, तार्किक for_init = असत्य)
{
  संरचना c_अभिव्यक्ती अभिव्यक्ती;
  स_रखो (&अभिव्यक्ती, 0, आकार (अभिव्यक्ती));
  अभिव्यक्ती.मूल्य = val;
  अभिव्यक्ती = convert_lvalue_to_rvalue (loc, अभिव्यक्ती, convert_p, read_p, for_init);
  परत अभिव्यक्ती.मूल्य;
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
  जर (code == ENUMERAL_TYPE)
    {
      type = ENUM_UNDERLYING_TYPE (type);
      जर (c_promoting_integer_type_p (type))
	{
	  जर (TYPE_UNSIGNED (type)
	      && TYPE_PRECISION (type) == TYPE_PRECISION (integer_type_गाठ))
	    type = unsigned_type_गाठ;
	  अन्यथा
	    type = integer_type_गाठ;
	}

      परत convert (type, exp);
    }

  /* ??? This should no longer be needed now bit-fields have their
     proper types.  */
  जर (वृक्ष_CODE (exp) == COMPONENT_REF
      && DECL_C_BIT_FIELD (वृक्ष_OPERAND (exp, 1)))
    {
      जर (BITINT_TYPE_P (DECL_BIT_FIELD_TYPE (वृक्ष_OPERAND (exp, 1))))
	{
	  वृक्ष btype = DECL_BIT_FIELD_TYPE (वृक्ष_OPERAND (exp, 1));
	  जर (वृक्ष_CODE (btype) == BITINT_TYPE)
	    परत convert (btype, exp);
	  अन्यथा
	    परत convert (ENUM_UNDERLYING_TYPE (btype), exp);
	}
      /* If it's thinner than an int, promote it like a
	 c_promoting_integer_type_p, otherwise leave it alone.  */
      जर (compare_वृक्ष_int (DECL_SIZE (वृक्ष_OPERAND (exp, 1)),
			    TYPE_PRECISION (integer_type_गाठ)) < 0)
	परत convert (integer_type_गाठ, exp);
    }

  जर (c_promoting_integer_type_p (type))
    {
      /* Preserve unsignedness if not really getting any wider.  */
      जर (TYPE_UNSIGNED (type)
	  && TYPE_PRECISION (type) == TYPE_PRECISION (integer_type_गाठ))
	परत convert (unsigned_type_गाठ, exp);

      परत convert (integer_type_गाठ, exp);
    }

  परत exp;
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
  जर (वृक्ष_CODE (exp) == COMPONENT_REF
      && handle_counted_by_p (exp))
    exp = handle_counted_by_for_component_ref (अभिव्यक्ती_LOCATION (exp), exp);

  /* Functions and arrays have been converted during parsing.  */
  gcc_assert (code != FUNCTION_TYPE);
  जर (code == ARRAY_TYPE)
    परत exp;

  /* Constants can be used directly unless they're not loadable.  */
  जर (वृक्ष_CODE (exp) == CONST_DECL)
    exp = DECL_INITIAL (exp);

  /* Strip no-op conversions.  */
  orig_exp = exp;
  STRIP_TYPE_NOPS (exp);

  copy_warning (exp, orig_exp);

  जर (code == VOID_TYPE)
    {
      error_at (अभिव्यक्ती_LOC_OR_LOC (exp, आदान_location),
		"void value not ignored as it ought to be");
      परत error_mark_गाठ;
    }

  exp = require_complete_type (अभिव्यक्ती_LOC_OR_LOC (exp, आदान_location), exp);
  जर (exp == error_mark_गाठ)
    परत error_mark_गाठ;

  promoted_type = targetm.promoted_type (type);
  जर (promoted_type)
    परत convert (promoted_type, exp);

  जर (INTEGRAL_TYPE_P (type))
    {
      /* Avoid performing integral promotion of bit-precise integer
	 type bit-field to its corresponding bit-precise integer if
	 orig_exp is a cast to it to its underlying type.  */
      जर (orig_exp != exp
	  && वृक्ष_CODE (exp) == COMPONENT_REF
	  && DECL_C_BIT_FIELD (वृक्ष_OPERAND (exp, 1))
	  && BITINT_TYPE_P (DECL_BIT_FIELD_TYPE (वृक्ष_OPERAND (exp, 1))))
	परत perform_integral_promotions (orig_exp);
      परत perform_integral_promotions (exp);
    }

  परत exp;
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

  जर (TYPE_LANG_SPECIFIC (type) && TYPE_LANG_SPECIFIC (type)->s
      && !seen_error ())
    {
      पूर्णांक bot, शीर्ष, half;
      वृक्ष *field_array = &TYPE_LANG_SPECIFIC (type)->s->elts[0];

      field = TYPE_FIELDS (type);
      bot = 0;
      शीर्ष = TYPE_LANG_SPECIFIC (type)->s->len;
      पर्यंत (शीर्ष - bot > 1)
	{
	  half = (शीर्ष - bot + 1) >> 1;
	  field = field_array[bot+half];

	  जर (DECL_NAME (field) == NULL_वृक्ष)
	    {
	      /* Step through all anon unions in linear fashion.  */
	      पर्यंत (DECL_NAME (field_array[bot]) == NULL_वृक्ष)
		{
		  field = field_array[bot++];
		  जर (RECORD_OR_UNION_TYPE_P (वृक्ष_TYPE (field)))
		    {
		      वृक्ष anon = lookup_field (वृक्ष_TYPE (field), component);

		      जर (anon)
			परत वृक्ष_cons (NULL_वृक्ष, field, anon);

		      /* The Plan 9 compiler permits referring
			 directly to an anonymous struct/union field
			 using a typedef name.  */
		      जर (flag_plan9_extensions
			  && TYPE_NAME (वृक्ष_TYPE (field)) != NULL_वृक्ष
			  && (वृक्ष_CODE (TYPE_NAME (वृक्ष_TYPE (field)))
			      == TYPE_DECL)
			  && (DECL_NAME (TYPE_NAME (वृक्ष_TYPE (field)))
			      == component))
			थांबा;
		    }
		}

	      /* Entire record is only anon unions.  */
	      जर (bot > शीर्ष)
		परत NULL_वृक्ष;

	      /* Restart the binary search, with new lower bound.  */
	      सुरूठेवा;
	    }

	  जर (DECL_NAME (field) == component)
	    थांबा;
	  जर (DECL_NAME (field) < component)
	    bot += half;
	  अन्यथा
	    शीर्ष = bot + half;
	}

      जर (DECL_NAME (field_array[bot]) == component)
	field = field_array[bot];
      अन्यथा जर (DECL_NAME (field) != component)
	परत NULL_वृक्ष;
    }
  अन्यथा
    {
      साठी (field = TYPE_FIELDS (type); field; field = DECL_CHAIN (field))
	{
	  जर (DECL_NAME (field) == NULL_वृक्ष
	      && RECORD_OR_UNION_TYPE_P (वृक्ष_TYPE (field)))
	    {
	      वृक्ष anon = lookup_field (वृक्ष_TYPE (field), component);

	      जर (anon)
		परत वृक्ष_cons (NULL_वृक्ष, field, anon);

	      /* The Plan 9 compiler permits referring directly to an
		 anonymous struct/union field using a typedef
		 name.  */
	      जर (flag_plan9_extensions
		  && TYPE_NAME (वृक्ष_TYPE (field)) != NULL_वृक्ष
		  && वृक्ष_CODE (TYPE_NAME (वृक्ष_TYPE (field))) == TYPE_DECL
		  && (DECL_NAME (TYPE_NAME (वृक्ष_TYPE (field)))
		      == component))
		थांबा;
	    }

	  जर (DECL_NAME (field) == component)
	    थांबा;
	}

      जर (field == NULL_वृक्ष)
	परत NULL_वृक्ष;
    }

  परत वृक्ष_cons (NULL_वृक्ष, field, NULL_वृक्ष);
}

/* Recursively append candidate IDENTIFIER_NODEs to CANDIDATES.  */

स्थिर शून्य
lookup_field_fuzzy_find_candidates (वृक्ष type, वृक्ष component,
				    vec<वृक्ष> *candidates)
{
  वृक्ष field;
  साठी (field = TYPE_FIELDS (type); field; field = DECL_CHAIN (field))
    {
      जर (DECL_NAME (field) == NULL_वृक्ष
	  && RECORD_OR_UNION_TYPE_P (वृक्ष_TYPE (field)))
	lookup_field_fuzzy_find_candidates (वृक्ष_TYPE (field), component,
					    candidates);

      जर (DECL_NAME (field))
	candidates->safe_ढकला (DECL_NAME (field));
    }
}

/* Like "lookup_field", but find the closest matching IDENTIFIER_NODE,
   rather than returning a TREE_LIST for an exact match.  */

स्थिर वृक्ष
lookup_field_fuzzy (वृक्ष type, वृक्ष component)
{
  gcc_assert (वृक्ष_CODE (component) == IDENTIFIER_गाठ);

  /* First, gather a list of candidates.  */
  auto_vec <वृक्ष> candidates;

  lookup_field_fuzzy_find_candidates (type, component,
				      &candidates);

  परत find_closest_identifier (component, &candidates);
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
  जर (c_dialect_objc ())
    परत असत्य;

  /* Only suggest it for pointers...  */
  जर (वृक्ष_CODE (datum_type) != POINTER_TYPE)
    परत असत्य;

  /* ...to structs/unions.  */
  वृक्ष underlying_type = वृक्ष_TYPE (datum_type);
  गणना वृक्ष_code code = वृक्ष_CODE (underlying_type);
  जर (code == RECORD_TYPE || code == UNION_TYPE)
    परत सत्य;
  अन्यथा
    परत असत्य;
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
  जर (वृक्ष_CODE (datum) == INDIRECT_REF
      && वृक्ष_OPERAND (datum, 0) == null_pointer_गाठ)
    परत असत्य;
  जर (in_typeof || in_alignof)
    परत असत्य;
  परत सत्य;
}

/* Given a component ref REF, if there is a counted_by attribute attached,
   issue error when the element_type is a structure or union including a
   flexible array member.  */

स्थिर शून्य
check_counted_by_attribute (location_t loc, वृक्ष ref)
{
  वृक्ष subdatum = वृक्ष_OPERAND (ref, 1);
  वृक्ष sub_type = वृक्ष_TYPE (subdatum);

  जर (!flexible_array_member_type_p (sub_type)
      && वृक्ष_CODE (sub_type) != POINTER_TYPE)
    परत;

  वृक्ष element_type = वृक्ष_TYPE (sub_type);

  वृक्ष attr_counted_by = lookup_attribute ("counted_by",
					   DECL_ATTRIBUTES (subdatum));
  जर (attr_counted_by)
    {
      /* Issue error when the element_type is a structure or
	union including a flexible array member.  */
      जर (RECORD_OR_UNION_TYPE_P (element_type)
	  && TYPE_INCLUDES_FLEXARRAY (element_type))
	{
	  error_at (loc,
		    "%<counted_by%> attribute is not allowed for a pointer to"
		    " structure or union with flexible array member");
	  परत;
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
  जर (!flexible_array_member_type_p (sub_type)
      && वृक्ष_CODE (sub_type) != POINTER_TYPE)
    परत NULL_वृक्ष;

  वृक्ष attr_counted_by = lookup_attribute ("counted_by",
					   DECL_ATTRIBUTES (subdatum));
  जर (!attr_counted_by)
    परत NULL_वृक्ष;

  वृक्ष counted_by_ref = NULL_वृक्ष;
  *counted_by_type = NULL_वृक्ष;

  वृक्ष type = वृक्ष_TYPE (datum);

  /* If the type of the containing structure is an anonymous struct/union,
     and this anonymous struct/union is not a root type, get the first
     outer named structure/union type.  */
  पर्यंत (वृक्ष_CODE (datum) == COMPONENT_REF
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
  करा
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
  पर्यंत (counted_by_field);

  counted_by_ref = build_fold_addr_अभिव्यक्ती (counted_by_ref);
  परत counted_by_ref;
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
		      ? size_one_गाठ
		      : TYPE_SIZE_UNIT (element_type);
  जर (element_size == NULL_वृक्ष)
    परत ref;

  वृक्ष first_param = is_fam
		     ? c_fully_fold (array_to_pointer_conversion (loc, ref),
				     असत्य, रिक्त)
		     : c_fully_fold (ref, असत्य, रिक्त);
  वृक्ष second_param
    = c_fully_fold (counted_by_ref, असत्य, रिक्त);
  वृक्ष third_param = build_int_cst (c_build_pointer_type (counted_by_type), 0);

  वृक्ष call
    = build_call_अभिव्यक्ती_internal_loc (loc, IFN_ACCESS_WITH_SIZE,
				    result_type, 4,
				    first_param,
				    second_param,
				    third_param,
				    element_size);

  /* Wrap the call with an INDIRECT_REF with the flexible array type.  */
  जर (is_fam)
    call = build1 (INDIRECT_REF, वृक्ष_TYPE (ref), call);
  SET_अभिव्यक्ती_LOCATION (call, loc);
  परत call;
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

  जर (!(flexible_array_member_type_p (वृक्ष_TYPE (ref))
	|| वृक्ष_CODE (वृक्ष_TYPE (ref)) == POINTER_TYPE))
    परत ref;

  वृक्ष counted_by_ref = build_counted_by_ref (datum, subdatum,
					      &counted_by_type);
  जर (counted_by_ref)
    ref = build_access_with_size_for_counted_by (loc, ref,
						 counted_by_ref,
						 counted_by_type);
  परत ref;
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

  जर (!objc_is_public (datum, component))
    परत error_mark_गाठ;

  /* Detect Objective-C property syntax object.property.  */
  जर (c_dialect_objc ()
      && (ref = objc_maybe_build_component_ref (datum, component)))
    परत ref;

  /* See if there is a field or component with name COMPONENT.  */

  जर (code == RECORD_TYPE || code == UNION_TYPE)
    {
      जर (!COMPLETE_TYPE_P (type))
	{
	  c_incomplete_type_error (loc, NULL_वृक्ष, type);
	  परत error_mark_गाठ;
	}

      field = lookup_field (type, component);

      जर (!field)
	{
	  वृक्ष guessed_id = lookup_field_fuzzy (type, component);
	  जर (guessed_id)
	    {
	      /* Attempt to provide a fixit replacement hint, if
		 we have a valid range for the component.  */
	      location_t reported_loc
		= (component_loc != UNKNOWN_LOCATION) ? component_loc : loc;
	      gcc_rich_location rich_loc (reported_loc);
	      जर (component_loc != UNKNOWN_LOCATION)
		rich_loc.add_fixit_misspelled_id (component_loc, guessed_id);
	      error_at (&rich_loc,
			"%qT has no member named %qE; did you mean %qE?",
			type, component, guessed_id);
	    }
	  अन्यथा
	    error_at (loc, "%qT has no member named %qE", type, component);
	  परत error_mark_गाठ;
	}

      /* Accessing elements of atomic structures or unions is undefined
	 behavior (C11 6.5.2.3#5).  */
      जर (TYPE_ATOMIC (type) && c_inhibit_evaluation_warnings == 0)
	{
	  जर (code == RECORD_TYPE)
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
      करा
	{
	  वृक्ष subdatum = वृक्ष_मूल्य (field);
	  पूर्णांक quals;
	  वृक्ष subtype;
	  तार्किक use_datum_quals;

	  जर (वृक्ष_TYPE (subdatum) == error_mark_गाठ)
	    परत error_mark_गाठ;

	  /* If this is an rvalue, it does not have qualifiers in C
	     standard terms and we must avoid propagating such
	     qualifiers down to a non-lvalue array that is then
	     converted to a pointer.  */
	  use_datum_quals = (datum_lvalue
			     || वृक्ष_CODE (वृक्ष_TYPE (subdatum)) != ARRAY_TYPE);

	  quals = TYPE_QUALS (strip_array_types (वृक्ष_TYPE (subdatum)));
	  जर (use_datum_quals)
	    quals |= TYPE_QUALS (वृक्ष_TYPE (datum));
	  subtype = c_build_qualified_type (वृक्ष_TYPE (subdatum), quals);

	  ref = build3 (COMPONENT_REF, subtype, datum, subdatum,
			NULL_वृक्ष);
	  SET_अभिव्यक्ती_LOCATION (ref, loc);

	  check_counted_by_attribute (loc, ref);

	  जर (वृक्ष_READONLY (subdatum)
	      || (use_datum_quals && वृक्ष_READONLY (datum)))
	    वृक्ष_READONLY (ref) = 1;
	  जर (वृक्ष_THIS_VOLATILE (subdatum)
	      || (use_datum_quals && वृक्ष_THIS_VOLATILE (datum)))
	    वृक्ष_THIS_VOLATILE (ref) = 1;

	  जर (वृक्ष_UNAVAILABLE (subdatum))
	    error_unavailable_use (subdatum, NULL_वृक्ष);
	  अन्यथा जर (वृक्ष_DEPRECATED (subdatum))
	    warn_deprecated_use (subdatum, NULL_वृक्ष);

	  datum = ref;

	  field = वृक्ष_CHAIN (field);
	}
      पर्यंत (field);

      परत ref;
    }
  अन्यथा जर (should_suggest_deref_p (type))
    {
      /* Special-case the error message for "ptr.field" for the case
	 where the user has confused "." vs "->".  */
      rich_location richloc (ओळ_table, loc);
      जर (INDIRECT_REF_P (datum) && arrow_loc != UNKNOWN_LOCATION)
	{
	  richloc.add_fixit_घाला_before (arrow_loc, "(*");
	  richloc.add_fixit_घाला_after (arrow_loc, ")");
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
      परत error_mark_गाठ;
    }
  अन्यथा जर (code != ERROR_MARK)
    error_at (loc,
	      "request for member %qE in something not a structure or union",
	      component);

  परत error_mark_गाठ;
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

  जर (वृक्ष_CODE (type) == POINTER_TYPE)
    {
      जर (CONVERT_अभिव्यक्ती_P (pointer)
          || वृक्ष_CODE (pointer) == VIEW_CONVERT_अभिव्यक्ती)
	{
	  /* If a warning is issued, mark it to avoid duplicates from
	     the backend.  This only needs to be done at
	     warn_strict_aliasing > 2.  */
	  जर (warn_strict_aliasing > 2)
	    जर (strict_aliasing_warning (अभिव्यक्ती_LOCATION (pointer),
					 type, वृक्ष_OPERAND (pointer, 0)))
	      suppress_warning (pointer, OPT_Wstrict_aliasing_);
	}

      जर (वृक्ष_CODE (pointer) == ADDR_अभिव्यक्ती
	  && (वृक्ष_TYPE (वृक्ष_OPERAND (pointer, 0))
	      == वृक्ष_TYPE (type)))
	{
	  ref = वृक्ष_OPERAND (pointer, 0);
	  protected_set_अभिव्यक्ती_location (ref, loc);
	  परत ref;
	}
      अन्यथा
	{
	  वृक्ष t = वृक्ष_TYPE (type);

	  ref = build1 (INDIRECT_REF, t, pointer);

	  जर (VOID_TYPE_P (t) && c_inhibit_evaluation_warnings == 0)
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
	  protected_set_अभिव्यक्ती_location (ref, loc);
	  परत ref;
	}
    }
  अन्यथा जर (वृक्ष_CODE (pointer) != ERROR_MARK)
    invalid_indirection_error (loc, type, errstring);

  परत error_mark_गाठ;
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
  जर (वृक्ष_TYPE (array) == error_mark_गाठ
      || वृक्ष_TYPE (index) == error_mark_गाठ)
    परत error_mark_गाठ;

  जर (वृक्ष_CODE (वृक्ष_TYPE (array)) != ARRAY_TYPE
      && वृक्ष_CODE (वृक्ष_TYPE (array)) != POINTER_TYPE
      /* Allow vector[index] but not index[vector].  */
      && !gnu_vector_type_p (वृक्ष_TYPE (array)))
    {
      जर (वृक्ष_CODE (वृक्ष_TYPE (index)) != ARRAY_TYPE
	  && वृक्ष_CODE (वृक्ष_TYPE (index)) != POINTER_TYPE)
	{
          error_at (loc,
            "subscripted value is neither array nor pointer nor vector");

	  परत error_mark_गाठ;
	}
      std::swap (array, index);
      swapped = सत्य;
    }

  जर (!INTEGRAL_TYPE_P (वृक्ष_TYPE (index)))
    {
      error_at (loc, "array subscript is not an integer");
      परत error_mark_गाठ;
    }

  जर (वृक्ष_CODE (वृक्ष_TYPE (वृक्ष_TYPE (array))) == FUNCTION_TYPE)
    {
      error_at (loc, "subscripted value is pointer to function");
      परत error_mark_गाठ;
    }

  /* ??? Existing practice has been to warn only when the char
     index is syntactically the index, not for char[array].  */
  जर (!swapped)
     warn_array_subscript_with_type_char (loc, index);

  /* Apply default promotions *after* noticing character types.  */
  index = default_conversion (index);
  जर (index == error_mark_गाठ)
    परत error_mark_गाठ;

  gcc_assert (वृक्ष_CODE (वृक्ष_TYPE (index)) == INTEGER_TYPE
	      || वृक्ष_CODE (वृक्ष_TYPE (index)) == BITINT_TYPE);

  तार्किक was_vector = VECTOR_TYPE_P (वृक्ष_TYPE (array));
  तार्किक non_lvalue = convert_vector_to_array_for_subscript (loc, &array, index);

  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  जर (वृक्ष_CODE (array) == COMPONENT_REF
      && handle_counted_by_p (array))
    array = handle_counted_by_for_component_ref (loc, array);

  जर (वृक्ष_CODE (वृक्ष_TYPE (array)) == ARRAY_TYPE)
    {
      वृक्ष rval, type;

      /* An array that is indexed by a non-constant
	 cannot be stored in a register; we must be able to do
	 address arithmetic on its address.
	 Likewise an array of elements of variable size.  */
      जर (वृक्ष_CODE (index) != INTEGER_CST
	  || (COMPLETE_TYPE_P (वृक्ष_TYPE (वृक्ष_TYPE (array)))
	      && वृक्ष_CODE (TYPE_SIZE (वृक्ष_TYPE (वृक्ष_TYPE (array)))) != INTEGER_CST))
	{
	  जर (!c_mark_addressable (array, सत्य, सत्य))
	    परत error_mark_गाठ;
	}
      /* An array that is indexed by a constant value which is not within
	 the array bounds cannot be stored in a register either; because we
	 would get a crash in store_bit_field/extract_bit_field when trying
	 to access a non-existent part of the register.  */
      जर (वृक्ष_CODE (index) == INTEGER_CST
	  && TYPE_DOMAIN (वृक्ष_TYPE (array))
	  && !int_fits_type_p (index, TYPE_DOMAIN (वृक्ष_TYPE (array))))
	{
	  जर (!c_mark_addressable (array, असत्य, सत्य))
	    परत error_mark_गाठ;
	  /* ISO C2Y disallows a negative integer constant expression index
	     when array subscripting has an operand of array type.  */
	  जर (flag_isoc2y
	      && !वृक्ष_OVERFLOW (index)
	      && वृक्ष_int_cst_sgn (index) < 0)
	    error_at (loc, "array subscript is negative");
	}

      जर ((pedantic || warn_c90_c99_compat || warn_c23_c2y_compat)
	  && ! was_vector)
	{
	  वृक्ष foo = array;
	  पर्यंत (वृक्ष_CODE (foo) == COMPONENT_REF)
	    foo = वृक्ष_OPERAND (foo, 0);
	  जर ((VAR_P (foo) && C_DECL_REGISTER (foo))
	      || (वृक्ष_CODE (foo) == COMPOUND_LITERAL_अभिव्यक्ती
		  && C_DECL_REGISTER (COMPOUND_LITERAL_अभिव्यक्ती_DECL (foo))))
	    pedwarn_c23 (loc, OPT_Wpedantic,
			 "ISO C forbids subscripting %<register%> array "
			 "before C2Y");
	  अन्यथा जर (!lvalue_p (foo))
	    pedwarn_c90 (loc, OPT_Wpedantic,
			 "ISO C90 forbids subscripting non-lvalue "
			 "array");
	}

      जर (वृक्ष_CODE (वृक्ष_TYPE (index)) == BITINT_TYPE
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
      protected_set_अभिव्यक्ती_location (ret, loc);
      जर (non_lvalue)
	ret = non_lvalue_loc (loc, ret);
      परत ret;
    }
  अन्यथा
    {
      वृक्ष ar = default_conversion (array);

      जर (ar == error_mark_गाठ)
	परत ar;

      gcc_assert (वृक्ष_CODE (वृक्ष_TYPE (ar)) == POINTER_TYPE);
      gcc_assert (वृक्ष_CODE (वृक्ष_TYPE (वृक्ष_TYPE (ar))) != FUNCTION_TYPE);

      ret = build_indirect_ref (loc, build_द्विमान_op (loc, PLUS_अभिव्यक्ती, ar,
						      index, असत्य),
				RO_ARRAY_INDEXING);
      जर (non_lvalue)
	ret = non_lvalue_loc (loc, ret);
      परत ret;
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
  जर (eltype == NULL_वृक्ष || error_operand_p (eltype))
    sectype = वृक्ष_TYPE (array);
  अन्यथा
    {
      वृक्ष idxtype = NULL_वृक्ष;

      जर (index != NULL_वृक्ष
	  && length != NULL_वृक्ष
	  && INTEGRAL_TYPE_P (वृक्ष_TYPE (index))
	  && INTEGRAL_TYPE_P (वृक्ष_TYPE (length)))
	{
	  वृक्ष खालचा = fold_convert (sizetype, index);
	  वृक्ष वरचा = fold_convert (sizetype, length);
	  वरचा = size_binop (PLUS_अभिव्यक्ती, खालचा, वरचा);
	  वरचा = size_binop (MINUS_अभिव्यक्ती, वरचा, size_one_गाठ);
	  idxtype = build_range_type (sizetype, खालचा, वरचा);
	}
      अन्यथा जर ((index == NULL_वृक्ष || integer_zerop (index))
	       && length != NULL_वृक्ष
	       && INTEGRAL_TYPE_P (वृक्ष_TYPE (length)))
	idxtype = build_index_type (length);

      gcc_assert (!error_operand_p (idxtype));

      sectype = c_build_array_type (eltype, idxtype);
    }

  परत build3_loc (loc, OMP_ARRAY_SECTION, sectype, array, index, length);
}


/* Record that REF is used.  This is relevant for undeclared static
   function and declarations referenced from a non-local context.
   ADDRESS indicates whether the address is taken.  */

शून्य
mark_decl_used (वृक्ष ref, तार्किक address)
{
  जर (!ref || !DECL_P (ref) || in_alignof)
    परत;

  /* Non-file-scope and non-local reference in nested function.  */
  तार्किक nonloc_p = current_function_decl && DECL_CONTEXT (ref)
		  && DECL_CONTEXT (current_function_decl)
		  && DECL_CONTEXT (ref) != current_function_decl;

  /* An undeclared static function.  */
  तार्किक static_p = वृक्ष_CODE (ref) == FUNCTION_DECL
		  && DECL_INITIAL (ref) == NULL_वृक्ष
		  && DECL_EXTERNAL (ref)
		  && !वृक्ष_PUBLIC (ref);

  जर (!static_p && !nonloc_p)
    परत;

  /* If we may be in an unevaluated context, delay the decision.  */
  जर (in_sizeof || in_typeof || in_countof || in_generic)
    परत record_maybe_used_decl (ref, address);

  जर (static_p)
    C_DECL_USED (ref) = 1;

  जर (nonloc_p && (VAR_OR_FUNCTION_DECL_P (ref)
		   || वृक्ष_CODE (ref) == PARM_DECL))
    DECL_NONLOCAL (ref) = 1;

  /* Nothing to do anymore.  */
  जर (!nonloc_p || C_FUNC_NONLOCAL_CONTEXT (current_function_decl))
    परत;

  /* Filter out the cases where referencing a non-local variable does not
     require a non-local context passed via the static chain.  */
  जर (!c_type_variably_modified_p (वृक्ष_TYPE (ref)))
    निवड (वृक्ष_CODE (ref))
      {
      स्थिती FUNCTION_DECL:
	/* Use of another local function that requires no context is ok.  */
	जर (!C_FUNC_NONLOCAL_CONTEXT (ref) && DECL_INITIAL (ref))
	  परत;
	थांबा;
      स्थिती VAR_DECL:
	/* Static variables and constexpr are ok, but for the later only
	   when the address is not taken.  */
	जर (वृक्ष_STATIC (ref) || (C_DECL_DECLARED_CONSTEXPR (ref) && !address))
	  परत;
	थांबा;
      स्थिती TYPE_DECL:
	/* A typedef is ok when not for a variably-modified type. */
	परत;
      स्थिती CONST_DECL:
	/* An enumeration constant is ok. */
	परत;
      स्थिती PARM_DECL:
	थांबा;
      स्थिती LABEL_DECL:
	थांबा;
      पूर्वनिर्धारित:
	gcc_unreachable ();
    }

  /* Mark all parent functions up to the nesting level of the variable as
     as needing the non-local context.  */
  साठी (वृक्ष cont = current_function_decl; cont; cont = DECL_CONTEXT (cont))
    {
      जर (cont == DECL_CONTEXT (ref))
	थांबा;

      /* There should not be any other type of context used for function
	 except TRANSLATION_UNIT_DECL which we should be able to reach.  */
      gcc_checking_assert (वृक्ष_CODE (cont) == FUNCTION_DECL);

      जर (वृक्ष_CODE (cont) == FUNCTION_DECL)
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
  जर (decl && decl != error_mark_गाठ)
    {
      ref = decl;
      *type = वृक्ष_TYPE (ref);
      जर (DECL_P (decl) && C_DECL_UNDERSPECIFIED (decl))
	error_at (loc, "underspecified %qD referenced in its initializer",
		  decl);
    }
  अन्यथा जर (fun)
    /* Implicit function declaration.  */
    ref = implicitly_declare (loc, id);
  अन्यथा जर (decl == error_mark_गाठ)
    /* Don't complain about something that's already been
       complained about.  */
    परत error_mark_गाठ;
  अन्यथा
    {
      undeclared_variable (loc, id);
      परत error_mark_गाठ;
    }

  /* For an OpenMP map clause, we can get better diagnostics for decls with
     unmappable types if we return the decl with an error_mark_node type,
     rather than returning error_mark_node for the decl itself.  */
  जर (वृक्ष_TYPE (ref) == error_mark_गाठ
      && !c_omp_array_section_p)
    परत error_mark_गाठ;

  जर (वृक्ष_UNAVAILABLE (ref))
    error_unavailable_use (ref, NULL_वृक्ष);
  अन्यथा जर (वृक्ष_DEPRECATED (ref))
    warn_deprecated_use (ref, NULL_वृक्ष);

  /* Recursive call does not count as usage.  */
  जर (ref != current_function_decl)
    {
      वृक्ष_USED (ref) = 1;
    }

  mark_decl_used (ref, असत्य);

  जर (वृक्ष_CODE (ref) == CONST_DECL)
    {
      used_types_घाला (वृक्ष_TYPE (ref));

      जर (warn_cxx_compat
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
  अन्यथा जर (current_function_decl != NULL_वृक्ष
	   && DECL_DECLARED_INLINE_P (current_function_decl)
	   && DECL_EXTERNAL (current_function_decl)
	   && VAR_OR_FUNCTION_DECL_P (ref)
	   && (!VAR_P (ref) || वृक्ष_STATIC (ref))
	   && ! वृक्ष_PUBLIC (ref)
	   && DECL_CONTEXT (ref) != current_function_decl)
    record_inline_static (loc, current_function_decl, ref,
			  csi_internal);

  परत ref;
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
काढा_maybe_used (तार्किक used)
{
  संरचना maybe_used_decl *p = maybe_used_decls;
  पूर्णांक cur_level = in_sizeof + in_typeof + in_countof + in_generic;
  पर्यंत (p && p->level > cur_level)
    {
      जर (used)
	{
	  जर (cur_level == 0)
	    mark_decl_used (p->decl, p->address);
	  अन्यथा
	    p->level = cur_level;
	}
      p = p->next;
    }
  जर (!used || cur_level == 0)
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
  पूर्णांक cur_level = in_sizeof + in_typeof + in_countof + in_generic;
  पर्यंत (p && p->level > cur_level)
    p = p->next;
  maybe_used_decls = p;
  परत orig;
}

/* Restore the stack of decls possibly used inside sizeof or typeof or _Countof
   or _Generic returned by save_maybe_used.  It is required that the stack is
   at exactly the point where it was left by save_maybe_used.  */

शून्य
restore_maybe_used (संरचना maybe_used_decl *चळत)
{
  maybe_used_decls = चळत;
}

/* Return the result of sizeof applied to EXPR.  */

संरचना c_अभिव्यक्ती
c_अभिव्यक्ती_sizeof_अभिव्यक्ती (location_t loc, संरचना c_अभिव्यक्ती अभिव्यक्ती)
{
  संरचना c_अभिव्यक्ती ret;
  जर (अभिव्यक्ती.मूल्य == error_mark_गाठ)
    {
      ret.मूल्य = error_mark_गाठ;
      ret.original_code = ERROR_MARK;
      ret.original_type = रिक्त;
      ret.m_decimal = 0;
      काढा_maybe_used (असत्य);
    }
  अन्यथा
    {
      तार्किक अभिव्यक्ती_const_operands = सत्य;

      जर (वृक्ष_CODE (अभिव्यक्ती.मूल्य) == PARM_DECL
	  && C_ARRAY_PARAMETER (अभिव्यक्ती.मूल्य))
	{
	  auto_diagnostic_group d;
	  जर (warning_at (loc, OPT_Wsizeof_array_argument,
			  "%<sizeof%> on array function parameter %qE will "
			  "return size of %qT", अभिव्यक्ती.मूल्य,
			  वृक्ष_TYPE (अभिव्यक्ती.मूल्य)))
	    inform (DECL_SOURCE_LOCATION (अभिव्यक्ती.मूल्य), "declared here");
	}
      वृक्ष folded_अभिव्यक्ती = c_fully_fold (अभिव्यक्ती.मूल्य, require_constant_मूल्य,
				       &अभिव्यक्ती_const_operands);
      ret.मूल्य = c_sizeof (loc, वृक्ष_TYPE (folded_अभिव्यक्ती));
      c_last_sizeof_arg = अभिव्यक्ती.मूल्य;
      c_last_sizeof_loc = loc;
      ret.original_code = SIZEOF_अभिव्यक्ती;
      ret.original_type = रिक्त;
      ret.m_decimal = 0;
      जर (C_TYPE_VARIABLE_SIZE (वृक्ष_TYPE (folded_अभिव्यक्ती)))
	{
	  /* sizeof is evaluated when given a vla (C99 6.5.3.4p2).  */
	  ret.मूल्य = build2 (C_MAYBE_CONST_अभिव्यक्ती, वृक्ष_TYPE (ret.मूल्य),
			      folded_अभिव्यक्ती, ret.मूल्य);
	  C_MAYBE_CONST_अभिव्यक्ती_NON_CONST (ret.मूल्य) = !अभिव्यक्ती_const_operands;
	  SET_अभिव्यक्ती_LOCATION (ret.मूल्य, loc);
	}
      काढा_maybe_used (C_TYPE_VARIABLE_SIZE (वृक्ष_TYPE (folded_अभिव्यक्ती)));
    }
  परत ret;
}

/* Return the result of sizeof applied to T, a structure for the type
   name passed to sizeof (rather than the type itself).  LOC is the
   location of the original expression.  */

संरचना c_अभिव्यक्ती
c_अभिव्यक्ती_sizeof_type (location_t loc, संरचना c_type_name *t)
{
  वृक्ष type;
  संरचना c_अभिव्यक्ती ret;
  वृक्ष type_अभिव्यक्ती = NULL_वृक्ष;
  तार्किक type_अभिव्यक्ती_const = सत्य;
  type = groktypename (t, &type_अभिव्यक्ती, &type_अभिव्यक्ती_const);
  ret.मूल्य = c_sizeof (loc, type);
  c_last_sizeof_arg = type;
  c_last_sizeof_loc = loc;
  ret.original_code = SIZEOF_अभिव्यक्ती;
  ret.original_type = रिक्त;
  ret.m_decimal = 0;
  जर (type == error_mark_गाठ)
    {
      ret.मूल्य = error_mark_गाठ;
      ret.original_code = ERROR_MARK;
    }
  अन्यथा
  जर ((type_अभिव्यक्ती || वृक्ष_CODE (ret.मूल्य) == INTEGER_CST)
      && C_TYPE_VARIABLE_SIZE (type))
    {
      /* If the type is a [*] array, it is a VLA but is represented as
	 having a size of zero.  In such a case we must ensure that
	 the result of sizeof does not get folded to a constant by
	 c_fully_fold, because if the size is evaluated the result is
	 not constant and so constraints on zero or negative size
	 arrays must not be applied when this sizeof call is inside
	 another array declarator.  */
      जर (!type_अभिव्यक्ती)
	type_अभिव्यक्ती = integer_zero_गाठ;
      ret.मूल्य = build2 (C_MAYBE_CONST_अभिव्यक्ती, वृक्ष_TYPE (ret.मूल्य),
			  type_अभिव्यक्ती, ret.मूल्य);
      C_MAYBE_CONST_अभिव्यक्ती_NON_CONST (ret.मूल्य) = !type_अभिव्यक्ती_const;
    }
  काढा_maybe_used (type != error_mark_गाठ
		  ? C_TYPE_VARIABLE_SIZE (type) : असत्य);
  परत ret;
}

स्थिर तार्किक
शीर्ष_array_vla_p (const_वृक्ष type)
{
  जर (वृक्ष_CODE (type) != ARRAY_TYPE)
    परत असत्य;

  वृक्ष d = TYPE_DOMAIN (type);

  जर (!d)
    परत असत्य;
  जर (!TYPE_MAX_मूल्य (d))
    परत असत्य;

  परत वृक्ष_CODE (TYPE_MAX_मूल्य (d)) != INTEGER_CST
	 || वृक्ष_CODE (TYPE_MIN_मूल्य (d)) != INTEGER_CST;
}

/* Return the result of countof applied to EXPR.  */

संरचना c_अभिव्यक्ती
c_अभिव्यक्ती_countof_अभिव्यक्ती (location_t loc, संरचना c_अभिव्यक्ती अभिव्यक्ती)
{
  संरचना c_अभिव्यक्ती ret;
  जर (अभिव्यक्ती.मूल्य == error_mark_गाठ)
    {
      ret.मूल्य = error_mark_गाठ;
      ret.original_code = ERROR_MARK;
      ret.original_type = रिक्त;
      ret.m_decimal = 0;
      काढा_maybe_used (असत्य);
    }
  अन्यथा
    {
      तार्किक अभिव्यक्ती_const_operands = सत्य;

      वृक्ष folded_अभिव्यक्ती = c_fully_fold (अभिव्यक्ती.मूल्य, require_constant_मूल्य,
				       &अभिव्यक्ती_const_operands);
      ret.मूल्य = c_countof_type (loc, वृक्ष_TYPE (folded_अभिव्यक्ती));
      c_last_sizeof_arg = अभिव्यक्ती.मूल्य;
      c_last_sizeof_loc = loc;
      ret.original_code = COUNTOF_अभिव्यक्ती;
      ret.original_type = रिक्त;
      ret.m_decimal = 0;
      जर (शीर्ष_array_vla_p (वृक्ष_TYPE (folded_अभिव्यक्ती)))
	{
	  /* countof is evaluated when given a vla.  */
	  ret.मूल्य = build2 (C_MAYBE_CONST_अभिव्यक्ती, वृक्ष_TYPE (ret.मूल्य),
			      folded_अभिव्यक्ती, ret.मूल्य);
	  C_MAYBE_CONST_अभिव्यक्ती_NON_CONST (ret.मूल्य) = !अभिव्यक्ती_const_operands;
	  SET_अभिव्यक्ती_LOCATION (ret.मूल्य, loc);
	}
      काढा_maybe_used (शीर्ष_array_vla_p (वृक्ष_TYPE (folded_अभिव्यक्ती)));
    }
  परत ret;
}

/* Return the result of countof applied to T, a structure for the type
   name passed to countof (rather than the type itself).  LOC is the
   location of the original expression.  */

संरचना c_अभिव्यक्ती
c_अभिव्यक्ती_countof_type (location_t loc, संरचना c_type_name *t)
{
  वृक्ष type;
  संरचना c_अभिव्यक्ती ret;
  वृक्ष type_अभिव्यक्ती = NULL_वृक्ष;
  तार्किक type_अभिव्यक्ती_const = सत्य;
  type = groktypename (t, &type_अभिव्यक्ती, &type_अभिव्यक्ती_const);
  ret.मूल्य = c_countof_type (loc, type);
  c_last_sizeof_arg = type;
  c_last_sizeof_loc = loc;
  ret.original_code = COUNTOF_अभिव्यक्ती;
  ret.original_type = रिक्त;
  ret.m_decimal = 0;
  जर (type == error_mark_गाठ)
    {
      ret.मूल्य = error_mark_गाठ;
      ret.original_code = ERROR_MARK;
    }
  अन्यथा
  जर ((type_अभिव्यक्ती || वृक्ष_CODE (ret.मूल्य) == INTEGER_CST)
      && शीर्ष_array_vla_p (type))
    {
      /* If the type is a [*] array, it is a VLA but is represented as
	 having a size of zero.  In such a case we must ensure that
	 the result of countof does not get folded to a constant by
	 c_fully_fold, because if the number of elements is evaluated
	 the result is not constant and so
	 constraints on zero or negative size arrays must not be applied
	 when this countof call is inside another array declarator.  */
      जर (!type_अभिव्यक्ती)
	type_अभिव्यक्ती = integer_zero_गाठ;
      ret.मूल्य = build2 (C_MAYBE_CONST_अभिव्यक्ती, वृक्ष_TYPE (ret.मूल्य),
			  type_अभिव्यक्ती, ret.मूल्य);
      C_MAYBE_CONST_अभिव्यक्ती_NON_CONST (ret.मूल्य) = !type_अभिव्यक्ती_const;
    }
  काढा_maybe_used (type != error_mark_गाठ ? शीर्ष_array_vla_p (type) : असत्य);
  परत ret;
}

/* Return the result of maxof applied to T, a structure for the type
   name passed to maxof (rather than the type itself).  LOC is the
   location of the original expression.  */

संरचना c_अभिव्यक्ती
c_अभिव्यक्ती_maxof_type (location_t loc, संरचना c_type_name *t)
{
  वृक्ष type;
  संरचना c_अभिव्यक्ती ret;
  वृक्ष type_अभिव्यक्ती = NULL_वृक्ष;
  तार्किक type_अभिव्यक्ती_const = सत्य;
  type = groktypename (t, &type_अभिव्यक्ती, &type_अभिव्यक्ती_const);
  ret.मूल्य = c_maxof_type (loc, type);
  c_last_sizeof_arg = type;
  c_last_sizeof_loc = loc;
  ret.original_code = MAXOF_अभिव्यक्ती;
  ret.original_type = रिक्त;
  ret.m_decimal = 0;
  जर (type == error_mark_गाठ)
    {
      ret.मूल्य = error_mark_गाठ;
      ret.original_code = ERROR_MARK;
    }
  काढा_maybe_used (type != error_mark_गाठ);
  परत ret;
}

/* Return the result of minof applied to T, a structure for the type
   name passed to minof (rather than the type itself).  LOC is the
   location of the original expression.  */

संरचना c_अभिव्यक्ती
c_अभिव्यक्ती_minof_type (location_t loc, संरचना c_type_name *t)
{
  वृक्ष type;
  संरचना c_अभिव्यक्ती ret;
  वृक्ष type_अभिव्यक्ती = NULL_वृक्ष;
  तार्किक type_अभिव्यक्ती_const = सत्य;
  type = groktypename (t, &type_अभिव्यक्ती, &type_अभिव्यक्ती_const);
  ret.मूल्य = c_minof_type (loc, type);
  c_last_sizeof_arg = type;
  c_last_sizeof_loc = loc;
  ret.original_code = MINOF_अभिव्यक्ती;
  ret.original_type = रिक्त;
  ret.m_decimal = 0;
  जर (type == error_mark_गाठ)
    {
      ret.मूल्य = error_mark_गाठ;
      ret.original_code = ERROR_MARK;
    }
  काढा_maybe_used (type != error_mark_गाठ);
  परत ret;
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
  साठी (; params; params = वृक्ष_CHAIN (params))
    v->quick_ढकला (वृक्ष_मूल्य (params));
  ret = c_build_function_call_vec (loc, vNULL, function, v, रिक्त);
  vec_free (v);
  परत ret;
}

/* Give a note about the location of the declaration of DECL,
   or, failing that, a pertinent declaration for FUNCTION_EXPR.  */

स्थिर शून्य
inform_declaration (वृक्ष decl, वृक्ष function_अभिव्यक्ती)
{
  जर (decl && (वृक्ष_CODE (decl) != FUNCTION_DECL
	       || !DECL_IS_UNDECLARED_BUILTIN (decl)))
    inform (DECL_SOURCE_LOCATION (decl), "declared here");
  अन्यथा जर (function_अभिव्यक्ती)
    निवड (वृक्ष_CODE (function_अभिव्यक्ती))
      {
      पूर्वनिर्धारित:
	थांबा;
      स्थिती COMPONENT_REF:
	/* Show the decl of the pertinent field (e.g. for callback
	   fields in a struct.  */
	{
	  वृक्ष field_decl = वृक्ष_OPERAND (function_अभिव्यक्ती, 1);
	  जर (location_t loc = DECL_SOURCE_LOCATION (field_decl))
	    inform (loc, "declared here");
	}
	थांबा;
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
  पूर्णांक nargs;
  वृक्ष *argarray;


  /* Strip NON_LVALUE_EXPRs, etc., since we aren't using as an lvalue.  */
  STRIP_TYPE_NOPS (function);

  /* Convert anything with function type to a pointer-to-function.  */
  जर (वृक्ष_CODE (function) == FUNCTION_DECL)
    {
      name = DECL_NAME (function);

      जर (flag_tm)
	tm_malloc_replacement (function);
      fundecl = function;
      जर (!orig_fundecl)
	orig_fundecl = fundecl;
      /* Atomic functions have type checking/casting already done.  They are
	 often rewritten and don't match the original parameter list.  */
      जर (name && startswith (IDENTIFIER_POINTER (name), "__atomic_"))
        origtypes = रिक्त;
    }
  जर (वृक्ष_CODE (वृक्ष_TYPE (function)) == FUNCTION_TYPE)
    function = function_to_pointer_conversion (loc, function);

  /* For Objective-C, convert any calls via a cast to OBJC_TYPE_REF
     expressions, like those used for ObjC messenger dispatches.  */
  जर (params && !params->is_empty ())
    function = objc_rewrite_function_call (function, (*params)[0]);

  function = c_fully_fold (function, असत्य, रिक्त);

  fntype = वृक्ष_TYPE (function);

  जर (वृक्ष_CODE (fntype) == ERROR_MARK)
    परत error_mark_गाठ;

  जर (!(वृक्ष_CODE (fntype) == POINTER_TYPE
	&& वृक्ष_CODE (वृक्ष_TYPE (fntype)) == FUNCTION_TYPE))
    {
      जर (!flag_diagnostics_show_caret && !STATEMENT_CLASS_P (function))
	error_at (loc,
		  "called object %qE is not a function or function pointer",
		  function);
      अन्यथा जर (DECL_P (function))
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
      परत error_mark_गाठ;
    }

  जर (fundecl && वृक्ष_THIS_VOLATILE (fundecl))
    current_function_returns_abnormally = 1;

  /* fntype now gets the type of function pointed to.  */
  fntype = वृक्ष_TYPE (fntype);
  वृक्ष return_type = वृक्ष_TYPE (fntype);

  /* Convert the parameters to the types declared in the
     function prototype, or apply default promotions.  */

  nargs = convert_arguments (loc, arg_loc, fntype, params,
			     origtypes, function, fundecl);
  जर (nargs < 0)
    परत error_mark_गाठ;

  /* Check that the function is called through a compatible prototype.
     If it is not, warn.  */
  जर (CONVERT_अभिव्यक्ती_P (function)
      && वृक्ष_CODE (tem = वृक्ष_OPERAND (function, 0)) == ADDR_अभिव्यक्ती
      && वृक्ष_CODE (tem = वृक्ष_OPERAND (tem, 0)) == FUNCTION_DECL
      && !comptypes (fntype, वृक्ष_TYPE (tem)))
    {
      /* This situation leads to run-time undefined behavior.  We can't,
	 therefore, simply error unless we can prove that all possible
	 executions of the program must execute the code.  */
      warning_at (loc, 0, "function called through a non-compatible type");

      जर (VOID_TYPE_P (return_type)
	  && TYPE_QUALS (return_type) != TYPE_UNQUALIFIED)
	pedwarn (loc, 0,
		 "function with qualified void return type called");
     }

  argarray = vec_safe_address (params);

  /* Check that arguments to builtin functions match the expectations.  */
  जर (fundecl
      && fndecl_built_in_p (fundecl)
      && !check_builtin_function_arguments (loc, arg_loc, fundecl,
					    orig_fundecl, nargs, argarray))
    परत error_mark_गाठ;

  /* Check that the arguments to the function are valid.  */
  तार्किक warned_p = check_function_arguments (loc, fundecl, fntype,
					    nargs, argarray, &arg_loc,
					    comptypes);

  जर (TYPE_QUALS (return_type) != TYPE_UNQUALIFIED
      && !VOID_TYPE_P (return_type))
    return_type = c_build_qualified_type (return_type, TYPE_UNQUALIFIED);
  जर (name != NULL_वृक्ष
      && startswith (IDENTIFIER_POINTER (name), "__builtin_"))
    {
      जर (require_constant_मूल्य)
	result
	  = fold_build_call_array_initializer_loc (loc, return_type,
						   function, nargs, argarray);
      अन्यथा
	result = fold_build_call_array_loc (loc, return_type,
					    function, nargs, argarray);
      जर (वृक्ष_CODE (result) == NOP_अभिव्यक्ती
	  && वृक्ष_CODE (वृक्ष_OPERAND (result, 0)) == INTEGER_CST)
	STRIP_TYPE_NOPS (result);
    }
  अन्यथा
    result = build_call_array_loc (loc, return_type,
				   function, nargs, argarray);
  /* If -Wnonnull warning has been diagnosed, avoid diagnosing it again
     later.  */
  जर (warned_p && वृक्ष_CODE (result) == CALL_अभिव्यक्ती)
    suppress_warning (result, OPT_Wnonnull);

  /* In this improbable scenario, a nested function returns a VM type.
     Create a TARGET_EXPR so that the call always has a LHS, much as
     what the C++ FE does for functions returning non-PODs.  */
  जर (c_type_variably_modified_p (वृक्ष_TYPE (fntype)))
    {
      वृक्ष tmp = create_tmp_var_raw (वृक्ष_TYPE (fntype));
      result = build4 (TARGET_अभिव्यक्ती, वृक्ष_TYPE (fntype), tmp, result,
		       NULL_वृक्ष, NULL_वृक्ष);
    }

  जर (VOID_TYPE_P (वृक्ष_TYPE (result)))
    {
      जर (TYPE_QUALS (वृक्ष_TYPE (result)) != TYPE_UNQUALIFIED)
	pedwarn (loc, 0,
		 "function with qualified void return type called");
      परत result;
    }
  परत require_complete_type (loc, result);
}

/* Like build_function_call_vec, but call also resolve_overloaded_builtin.  */

वृक्ष
c_build_function_call_vec (location_t loc, स्थिरांक vec<location_t> &arg_loc,
			   वृक्ष function, vec<वृक्ष, va_gc> *params,
			   vec<वृक्ष, va_gc> *origtypes)
{
  /* Strip NON_LVALUE_EXPRs, etc., since we aren't using as an lvalue.  */
  STRIP_TYPE_NOPS (function);

  /* Convert anything with function type to a pointer-to-function.  */
  जर (वृक्ष_CODE (function) == FUNCTION_DECL)
    {
      /* Implement type-directed function overloading for builtins.
	 resolve_overloaded_builtin and targetm.resolve_overloaded_builtin
	 handle all the type checking.  The result is a complete expression
	 that implements this function call.  */
      वृक्ष tem = resolve_overloaded_builtin (loc, function, params);
      जर (tem)
	परत tem;
    }
  परत build_function_call_vec (loc, arg_loc, function, params, origtypes);
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
		  तार्किक npc, वृक्ष rname, पूर्णांक parmnum, पूर्णांक argnum,
		  तार्किक excess_precision, पूर्णांक warnopt)
{
  /* Formal parm type is specified by a function prototype.  */

  जर (type == error_mark_गाठ || !COMPLETE_TYPE_P (type))
    {
      error_at (ploc, "type of formal parameter %d is incomplete",
		parmnum + 1);
      परत error_mark_गाठ;
    }

  /* Optionally warn about conversions that differ from the default
     conversions.  */
  जर (warn_traditional_conversion || warn_traditional)
    {
      जर (INTEGRAL_TYPE_P (type)
	  && SCALAR_FLOAT_TYPE_P (valtype))
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as integer rather "
		    "than floating due to prototype",
		    argnum, rname);
      जर (INTEGRAL_TYPE_P (type)
	  && वृक्ष_CODE (valtype) == COMPLEX_TYPE)
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as integer rather "
		    "than complex due to prototype",
		    argnum, rname);
      अन्यथा जर (वृक्ष_CODE (type) == COMPLEX_TYPE
	       && SCALAR_FLOAT_TYPE_P (valtype))
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as complex rather "
		    "than floating due to prototype",
		    argnum, rname);
      अन्यथा जर (SCALAR_FLOAT_TYPE_P (type)
	       && INTEGRAL_TYPE_P (valtype))
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as floating rather "
		    "than integer due to prototype",
		    argnum, rname);
      अन्यथा जर (वृक्ष_CODE (type) == COMPLEX_TYPE
	       && INTEGRAL_TYPE_P (valtype))
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as complex rather "
		    "than integer due to prototype",
		    argnum, rname);
      अन्यथा जर (SCALAR_FLOAT_TYPE_P (type)
	       && वृक्ष_CODE (valtype) == COMPLEX_TYPE)
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as floating rather "
		    "than complex due to prototype",
		    argnum, rname);
      /* ??? At some point, messages should be written about
	 conversions between complex types, but that's too messy
	 to do now.  */
      अन्यथा जर (SCALAR_FLOAT_TYPE_P (type)
	       && SCALAR_FLOAT_TYPE_P (valtype))
	{
	  अचिन्हित पूर्णांक formal_prec = TYPE_PRECISION (type);

	  /* Warn if any argument is passed as `float',
	     since without a prototype it would be `double'.  */
	  जर (formal_prec == TYPE_PRECISION (float_type_गाठ)
	      && type != dfloat32_type_गाठ)
	    warning_at (ploc, 0,
			"passing argument %d of %qE as %<float%> "
			"rather than %<double%> due to prototype",
			argnum, rname);

	  /* Warn if mismatch between argument and prototype
	     for decimal float types.  Warn of conversions with
	     binary float types and of precision narrowing due to
	     prototype.  */
	  अन्यथा जर (type != valtype
		   && (type == dfloat32_type_गाठ
		       || type == dfloat64_type_गाठ
		       || type == dfloat128_type_गाठ
		       || valtype == dfloat32_type_गाठ
		       || valtype == dfloat64_type_गाठ
		       || valtype == dfloat128_type_गाठ)
		   && (formal_prec
		       <= TYPE_PRECISION (valtype)
		       || (type == dfloat128_type_गाठ
			   && (valtype
			       != dfloat64_type_गाठ
			       && (valtype
				   != dfloat32_type_गाठ)))
		       || (type == dfloat64_type_गाठ
			   && (valtype
			       != dfloat32_type_गाठ))))
	    warning_at (ploc, 0,
			"passing argument %d of %qE as %qT "
			"rather than %qT due to prototype",
			argnum, rname, type, valtype);

	}
      /* Detect integer changing in width or signedness.
	 These warnings are only activated with
	 -Wtraditional-conversion, not with -Wtraditional.  */
      अन्यथा जर (warn_traditional_conversion
	       && INTEGRAL_TYPE_P (type)
	       && INTEGRAL_TYPE_P (valtype))
	{
	  अचिन्हित पूर्णांक formal_prec = TYPE_PRECISION (type);
	  वृक्ष would_have_been = default_conversion (val);
	  वृक्ष type1 = वृक्ष_TYPE (would_have_been);

	  जर (val == error_mark_गाठ)
	    /* VAL could have been of incomplete type.  */;
	  अन्यथा जर (वृक्ष_CODE (type) == ENUMERAL_TYPE
		   && (TYPE_MAIN_VARIANT (type)
		       == TYPE_MAIN_VARIANT (valtype)))
	    /* No warning if function asks for enum
	       and the actual arg is that enum type.  */
	    ;
	  अन्यथा जर (formal_prec != TYPE_PRECISION (type1))
	    warning_at (ploc, OPT_Wtraditional_conversion,
			"passing argument %d of %qE "
			"with different width due to prototype",
			argnum, rname);
	  अन्यथा जर (TYPE_UNSIGNED (type) == TYPE_UNSIGNED (type1))
	    ;
	  /* Don't complain if the formal parameter type
	     is an enum, because we can't tell now whether
	     the value was an enum--even the same enum.  */
	  अन्यथा जर (वृक्ष_CODE (type) == ENUMERAL_TYPE)
	    ;
	  अन्यथा जर (वृक्ष_CODE (val) == INTEGER_CST
		   && int_fits_type_p (val, type))
	    /* Change in signedness doesn't matter
	       if a constant value is unaffected.  */
	    ;
	  /* If the value is extended from a narrower
	     unsigned type, it doesn't matter whether we
	     pass it as signed or unsigned; the value
	     certainly is the same either way.  */
	  अन्यथा जर (TYPE_PRECISION (valtype) < TYPE_PRECISION (type)
		   && TYPE_UNSIGNED (valtype))
	    ;
	  अन्यथा जर (TYPE_UNSIGNED (type))
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
  जर (excess_precision)
    val = build1 (EXCESS_PRECISION_अभिव्यक्ती, valtype, val);

  वृक्ष parmval = convert_for_assignment (ploc, ploc, type,
					 val, origtype, ic_argpass,
					 npc, fundecl, function,
					 parmnum + 1, warnopt);
  परत parmval;
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

स्थिर पूर्णांक
convert_arguments (location_t loc, vec<location_t> arg_loc, वृक्ष fntype,
		   vec<वृक्ष, va_gc> *मूल्ये, vec<वृक्ष, va_gc> *origtypes,
		   वृक्ष function, वृक्ष fundecl)
{
  वृक्ष typelist = TYPE_ARG_TYPES (fntype);
  अचिन्हित पूर्णांक parmnum;
  तार्किक error_args = असत्य;
  स्थिरांक तार्किक type_generic = fundecl
    && lookup_attribute ("type generic", TYPE_ATTRIBUTES (वृक्ष_TYPE (fundecl)));
  तार्किक type_generic_remove_excess_precision = असत्य;
  तार्किक type_generic_overflow_p = असत्य;
  तार्किक type_generic_bit_query = असत्य;
  वृक्ष selector;

  /* Change pointer to function to the function itself for
     diagnostics.  */
  जर (वृक्ष_CODE (function) == ADDR_अभिव्यक्ती
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
  जर (fundecl
      && fndecl_built_in_p (fundecl, BUILT_IN_NORMAL))
    {
      built_in_function code = DECL_FUNCTION_CODE (fundecl);
      जर (C_DECL_BUILTIN_PROTOTYPE (fundecl))
	{
	  /* For a call to a built-in function declared without a prototype
	     use the types of the parameters of the internal built-in to
	     match those of the arguments to.  */
	  जर (वृक्ष bdecl = builtin_decl_explicit (code))
	    builtin_typelist = TYPE_ARG_TYPES (वृक्ष_TYPE (bdecl));
	}

      /* For type-generic built-in functions, determine whether excess
	 precision should be removed (classification) or not
	 (comparison).  */
      जर (type_generic)
	निवड (code)
	  {
	  स्थिती BUILT_IN_ISFINITE:
	  स्थिती BUILT_IN_ISINF:
	  स्थिती BUILT_IN_ISINF_SIGN:
	  स्थिती BUILT_IN_ISNAN:
	  स्थिती BUILT_IN_ISNORMAL:
	  स्थिती BUILT_IN_ISSIGNALING:
	  स्थिती BUILT_IN_FPCLASSIFY:
	    type_generic_remove_excess_precision = सत्य;
	    थांबा;

	  स्थिती BUILT_IN_ADD_OVERFLOW_P:
	  स्थिती BUILT_IN_SUB_OVERFLOW_P:
	  स्थिती BUILT_IN_MUL_OVERFLOW_P:
	    /* The last argument of these type-generic builtins
	       should not be promoted.  */
	    type_generic_overflow_p = सत्य;
	    थांबा;

	  स्थिती BUILT_IN_CLZG:
	  स्थिती BUILT_IN_CTZG:
	  स्थिती BUILT_IN_CLRSBG:
	  स्थिती BUILT_IN_FFSG:
	  स्थिती BUILT_IN_PARITYG:
	  स्थिती BUILT_IN_POPCOUNTG:
	    /* The first argument of these type-generic builtins
	       should not be promoted.  */
	    type_generic_bit_query = सत्य;
	    थांबा;

	  पूर्वनिर्धारित:
	    थांबा;
	  }
    }

  /* Scan the given expressions (VALUES) and types (TYPELIST), producing
     individual converted arguments.  */

  वृक्ष typetail, builtin_typetail, val;
  साठी (typetail = typelist,
	 builtin_typetail = builtin_typelist,
	 parmnum = 0;
       मूल्ये && मूल्ये->iterate (parmnum, &val);
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
      पूर्णांक argnum = parmnum + 1;
      स्थिरांक अक्षर *invalid_func_diag;
      /* Set for EXCESS_PRECISION_EXPR arguments.  */
      तार्किक excess_precision = असत्य;
      /* The value of the argument after conversion to the type
	 of the function parameter it is passed to.  */
      वृक्ष parmval;
      /* Some __atomic_* builtins have additional hidden argument at
	 position 0.  */
      location_t ploc
	= !arg_loc.is_empty () && मूल्ये->length () == arg_loc.length ()
	  ? expansion_point_location_if_in_system_header (arg_loc[parmnum])
	  : आदान_location;

      जर (type == void_type_गाठ)
	{
	  auto_diagnostic_group d;
	  पूर्णांक अंक_expected = parmnum;
	  पूर्णांक अंक_actual = मूल्ये->length ();
	  gcc_rich_location rich_loc (loc);
	  जर (ploc != आदान_location)
	    rich_loc.add_range (ploc);
	  जर (selector)
	    error_at (&rich_loc,
		      "too many arguments to method %qE; expected %i, have %i",
		      selector, अंक_expected, अंक_actual);
	  अन्यथा
	    error_at (&rich_loc,
		      "too many arguments to function %qE; expected %i, have %i",
		      function, अंक_expected, अंक_actual);
	  inform_declaration (fundecl, function);
	  परत error_args ? -1 : (पूर्णांक) parmnum;
	}

      जर (builtin_type == void_type_गाठ)
	{
	  auto_diagnostic_group d;
	  जर (warning_at (loc, OPT_Wbuiltin_declaration_mismatch,
			  "too many arguments to built-in function %qE "
			  "expecting %d", function, parmnum))
	    inform_declaration (fundecl, function);
	  builtin_typetail = NULL_वृक्ष;
	}

      जर (!typetail && parmnum == 0 && !TYPE_NO_NAMED_ARGS_STDARG_P (fntype)
	  && !(fundecl && fndecl_built_in_p (fundecl)))
	{
	  auto_diagnostic_group d;
	  तार्किक warned;
	  जर (selector)
	    warned = warning_at (loc, OPT_Wdeprecated_non_prototype,
				 "ISO C23 does not allow arguments"
				 " for method %qE declared without parameters",
				 function);
	  अन्यथा
	    warned = warning_at (loc, OPT_Wdeprecated_non_prototype,
				 "ISO C23 does not allow arguments"
				 " for function %qE declared without parameters",
				 function);
	  जर (warned)
	    inform_declaration (fundecl, function);
	}

      जर (selector && argnum > 2)
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
      जर (वृक्ष_CODE (val) == EXCESS_PRECISION_अभिव्यक्ती
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
      जर (type == NULL_वृक्ष
	  && वृक्ष_CODE (valtype) == REAL_TYPE
	  && (TYPE_PRECISION (valtype)
	      <= TYPE_PRECISION (double_type_गाठ))
	  && TYPE_MAIN_VARIANT (valtype) != double_type_गाठ
	  && TYPE_MAIN_VARIANT (valtype) != long_double_type_गाठ
	  && !DECIMAL_FLOAT_MODE_P (TYPE_MODE (valtype)))
	{
	  /* Promote this argument, unless it has a _FloatN or
	     _FloatNx type.  */
	  promote_float_arg = सत्य;
	  साठी (पूर्णांक i = 0; i < अंक_FLOATN_NX_TYPES; i++)
	    जर (TYPE_MAIN_VARIANT (valtype) == FLOATN_NX_TYPE_गाठ (i))
	      {
		promote_float_arg = असत्य;
		थांबा;
	      }
	  /* Don't promote __bf16 either.  */
	  जर (TYPE_MAIN_VARIANT (valtype) == bfloat16_type_गाठ)
	    promote_float_arg = असत्य;
	}

      जर (type != NULL_वृक्ष)
	{
	  वृक्ष origtype = (!origtypes) ? NULL_वृक्ष : (*origtypes)[parmnum];
	  parmval = convert_argument (ploc, function, fundecl, type, origtype,
				      val, valtype, npc, rname, parmnum, argnum,
				      excess_precision, 0);
	}
      /* A NULLPTR type is just a nullptr always.  */
      अन्यथा जर (वृक्ष_CODE (वृक्ष_TYPE (val)) == NULLPTR_TYPE)
	parmval = omit_one_operand_loc (ploc, वृक्ष_TYPE (val), nullptr_गाठ, val);
      अन्यथा जर (promote_float_arg)
        {
	  जर (type_generic)
	    parmval = val;
	  अन्यथा
	    {
	      /* Convert `float' to `double'.  */
	      जर (warn_double_promotion && !c_inhibit_evaluation_warnings)
		warning_at (ploc, OPT_Wdouble_promotion,
			    "implicit conversion from %qT to %qT when passing "
			    "argument to function",
			    valtype, double_type_गाठ);
	      parmval = convert (double_type_गाठ, val);
	    }
	}
      अन्यथा जर ((excess_precision && !type_generic)
	       || (type_generic_overflow_p && parmnum == 2)
	       || (type_generic_bit_query && parmnum == 0))
	/* A "double" argument with excess precision being passed
	   without a prototype or in variable arguments.
	   The last argument of __builtin_*_overflow_p should not be
	   promoted, similarly the first argument of
	   __builtin_{clz,ctz,clrsb,ffs,parity,popcount}g.  */
	parmval = convert (valtype, val);
      अन्यथा जर ((invalid_func_diag =
		targetm.calls.invalid_arg_for_unprototyped_fn (typelist, fundecl, val)))
	{
	  error (invalid_func_diag);
	  परत -1;
	}
      अन्यथा जर (वृक्ष_CODE (val) == ADDR_अभिव्यक्ती && reject_gcc_builtin (val))
	{
	  परत -1;
	}
      अन्यथा
	/* Convert `short' and `char' to full-size `int'.  */
	parmval = default_conversion (val);

      (*मूल्ये)[parmnum] = parmval;
      जर (parmval == error_mark_गाठ)
	error_args = सत्य;

      जर (!type && builtin_type && वृक्ष_CODE (builtin_type) != VOID_TYPE)
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

      जर (typetail)
	typetail = वृक्ष_CHAIN (typetail);

      जर (builtin_typetail)
	builtin_typetail = वृक्ष_CHAIN (builtin_typetail);
    }

  gcc_assert (parmnum == vec_safe_length (मूल्ये));

  जर (typetail != NULL_वृक्ष && वृक्ष_मूल्य (typetail) != void_type_गाठ)
    {
      /* Not enough args.
	 Determine minimum number of arguments required.  */
      पूर्णांक min_expected_अंक = 0;
      तार्किक at_least_p = असत्य;
      वृक्ष iter = typelist;
      पर्यंत (सत्य)
	{
	  जर (!iter)
	    {
	      /* Variadic arguments; stop iterating.  */
	      at_least_p = सत्य;
	      थांबा;
	    }
	  जर (iter == void_list_गाठ)
	    /* End of arguments; stop iterating.  */
	    थांबा;
	  ++min_expected_अंक;
	  iter = वृक्ष_CHAIN (iter);
	}
      auto_diagnostic_group d;
      पूर्णांक actual_अंक = vec_safe_length (मूल्ये);
      error_at (loc,
		at_least_p
		? G_("too few arguments to function %qE; expected at least %i, have %i")
		: G_("too few arguments to function %qE; expected %i, have %i"),
		function, min_expected_अंक, actual_अंक);
      inform_declaration (fundecl, function);
      परत -1;
    }

  जर (builtin_typetail && वृक्ष_मूल्य (builtin_typetail) != void_type_गाठ)
    {
      अचिन्हित nargs = parmnum;
      साठी (वृक्ष t = builtin_typetail; t; t = वृक्ष_CHAIN (t))
	++nargs;

      auto_diagnostic_group d;
      जर (warning_at (loc, OPT_Wbuiltin_declaration_mismatch,
		      "too few arguments to built-in function %qE "
		      "expecting %u", function, nargs - 1))
	inform_declaration (fundecl, function);
    }

  परत error_args ? -1 : (पूर्णांक) parmnum;
}

/* This is the entry point used by the parser to build unary operators
   in the input.  CODE, a tree_code, specifies the unary operator, and
   ARG is the operand.  For unary plus, the C parser currently uses
   CONVERT_EXPR for code.

   LOC is the location to use for the tree generated.
*/

संरचना c_अभिव्यक्ती
parser_build_unary_op (location_t loc, गणना वृक्ष_code code, संरचना c_अभिव्यक्ती arg)
{
  संरचना c_अभिव्यक्ती result;

  result.original_code = code;
  result.original_type = रिक्त;
  result.m_decimal = 0;

  जर (reject_gcc_builtin (arg.मूल्य))
    {
      result.मूल्य = error_mark_गाठ;
    }
  अन्यथा
    {
      result.मूल्य = build_unary_op (loc, code, arg.मूल्य, असत्य);

      जर (वृक्ष_OVERFLOW_P (result.मूल्य) && !वृक्ष_OVERFLOW_P (arg.मूल्य))
	overflow_warning (loc, result.मूल्य, arg.मूल्य);
    }

  /* We are typically called when parsing a prefix token at LOC acting on
     ARG.  Reflect this by updating the source range of the result to
     start at LOC and end at the end of ARG.  */
  set_c_अभिव्यक्ती_source_range (&result,
			   loc, arg.get_finish ());

  परत result;
}

/* Returns true if TYPE is a character type, *not* including wchar_t.  */

तार्किक
char_type_p (वृक्ष type)
{
  परत (type == char_type_गाठ
	  || type == unsigned_char_type_गाठ
	  || type == signed_char_type_गाठ
	  || type == char16_type_गाठ
	  || type == char32_type_गाठ);
}

/* This is the entry point used by the parser to build binary operators
   in the input.  CODE, a tree_code, specifies the binary operator, and
   ARG1 and ARG2 are the operands.  In addition to constructing the
   expression, we check for operands that were written with other binary
   operators in a way that is likely to confuse the user.  ORIG_ARG1 is
   the original first operand for TRUTH_{AND,OR}IF_EXPR before it is
   converted to truth value, otherwise NULL_TREE.

   LOCATION is the location of the binary operator.  */

संरचना c_अभिव्यक्ती
parser_build_द्विमान_op (location_t location, गणना वृक्ष_code code,
			संरचना c_अभिव्यक्ती arg1, संरचना c_अभिव्यक्ती arg2, वृक्ष orig_arg1)
{
  संरचना c_अभिव्यक्ती result;
  result.m_decimal = 0;

  गणना वृक्ष_code code1 = arg1.original_code;
  गणना वृक्ष_code code2 = arg2.original_code;
  वृक्ष type1 = (arg1.original_type
                ? arg1.original_type
                : वृक्ष_TYPE (arg1.मूल्य));
  वृक्ष type2 = (arg2.original_type
                ? arg2.original_type
                : वृक्ष_TYPE (arg2.मूल्य));

  result.मूल्य = build_द्विमान_op (location, code,
				  arg1.मूल्य, arg2.मूल्य, सत्य);
  result.original_code = code;
  result.original_type = रिक्त;
  result.m_decimal = 0;

  जर (वृक्ष_CODE (result.मूल्य) == ERROR_MARK)
    {
      set_c_अभिव्यक्ती_source_range (&result,
			       arg1.get_start (),
			       arg2.get_finish ());
      परत result;
    }

  जर (location != UNKNOWN_LOCATION)
    protected_set_अभिव्यक्ती_location (result.मूल्य, location);

  set_c_अभिव्यक्ती_source_range (&result,
			   arg1.get_start (),
			   arg2.get_finish ());

  /* Check for cases such as x+y<<z which users are likely
     to misinterpret.  */
  जर (warn_parentheses)
    warn_about_parentheses (location, code, code1, arg1.मूल्य, code2,
			    arg2.मूल्य);

  जर (warn_logical_op)
    warn_logical_operator (location, code, वृक्ष_TYPE (result.मूल्य),
			   code1, arg1.मूल्य, code2, arg2.मूल्य);

  जर (warn_constant_logical_operand
      && (code == TRUTH_ANDIF_अभिव्यक्ती || code == TRUTH_ORIF_अभिव्यक्ती)
      && INTEGRAL_NB_TYPE_P (type1)
      && INTEGRAL_NB_TYPE_P (type2))
    {
      स्थिरांक अक्षर *name = code == TRUTH_ANDIF_अभिव्यक्ती ? "&&" : "||";
      जर (orig_arg1 == NULL_वृक्ष)
	orig_arg1 = arg1.मूल्य;
      स्वतः enum_other_than_0_1 = [] (वृक्ष type) {
	जर (वृक्ष_CODE (type) != ENUMERAL_TYPE)
	  परत असत्य;
	साठी (वृक्ष l = TYPE_मूल्ये (type); l; l = वृक्ष_CHAIN (l))
	  {
	    वृक्ष v = DECL_INITIAL (वृक्ष_मूल्य (l));
	    जर (!integer_zerop (v) && !integer_onep (v))
	      परत सत्य;
	  }
	परत असत्य;
      };
      स्वतः diagnose_constant_logical_operand = [=] (वृक्ष val, वृक्ष type) {
	जर (वृक्ष_CODE (val) != INTEGER_CST || integer_zerop (val))
	  परत असत्य;
	जर (integer_onep (val) && !enum_other_than_0_1 (type))
	  परत असत्य;
	gcc_rich_location richloc (location);
	richloc.add_fixit_replace (name + 1);
	auto_diagnostic_group d;
	जर (warning_at (location, OPT_Wconstant_logical_operand,
			"use of logical %qs with constant operand %qE",
			name, val))
	  inform (&richloc, "use %qs for bitwise operation", name + 1);
	परत सत्य;
      };
      जर (!diagnose_constant_logical_operand (arg2.मूल्य, type2))
	diagnose_constant_logical_operand (orig_arg1, type1);
    }

  जर (warn_tautological_compare)
    {
      वृक्ष lhs = arg1.मूल्य;
      वृक्ष rhs = arg2.मूल्य;
      जर (वृक्ष_CODE (lhs) == C_MAYBE_CONST_अभिव्यक्ती)
	{
	  जर (C_MAYBE_CONST_अभिव्यक्ती_PRE (lhs) != NULL_वृक्ष
	      && वृक्ष_SIDE_EFFECTS (C_MAYBE_CONST_अभिव्यक्ती_PRE (lhs)))
	    lhs = NULL_वृक्ष;
	  अन्यथा
	    lhs = C_MAYBE_CONST_अभिव्यक्ती_अभिव्यक्ती (lhs);
	}
      जर (वृक्ष_CODE (rhs) == C_MAYBE_CONST_अभिव्यक्ती)
	{
	  जर (C_MAYBE_CONST_अभिव्यक्ती_PRE (rhs) != NULL_वृक्ष
	      && वृक्ष_SIDE_EFFECTS (C_MAYBE_CONST_अभिव्यक्ती_PRE (rhs)))
	    rhs = NULL_वृक्ष;
	  अन्यथा
	    rhs = C_MAYBE_CONST_अभिव्यक्ती_अभिव्यक्ती (rhs);
	}
      जर (lhs != NULL_वृक्ष && rhs != NULL_वृक्ष)
	warn_tautological_cmp (location, code, lhs, rhs);
    }

  जर (warn_logical_not_paren
      && वृक्ष_CODE_CLASS (code) == tcc_comparison
      && code1 == TRUTH_NOT_अभिव्यक्ती
      && code2 != TRUTH_NOT_अभिव्यक्ती
      /* Avoid warning for !!x == y.  */
      && (वृक्ष_CODE (arg1.मूल्य) != NE_अभिव्यक्ती
	  || !integer_zerop (वृक्ष_OPERAND (arg1.मूल्य, 1))))
    {
      /* Avoid warning for !b == y where b has _Bool type.  */
      वृक्ष t = integer_zero_गाठ;
      जर (वृक्ष_CODE (arg1.मूल्य) == EQ_अभिव्यक्ती
	  && integer_zerop (वृक्ष_OPERAND (arg1.मूल्य, 1))
	  && वृक्ष_TYPE (वृक्ष_OPERAND (arg1.मूल्य, 0)) == integer_type_गाठ)
	{
	  t = वृक्ष_OPERAND (arg1.मूल्य, 0);
	  करा
	    {
	      जर (वृक्ष_TYPE (t) != integer_type_गाठ)
		थांबा;
	      जर (वृक्ष_CODE (t) == C_MAYBE_CONST_अभिव्यक्ती)
		t = C_MAYBE_CONST_अभिव्यक्ती_अभिव्यक्ती (t);
	      अन्यथा जर (CONVERT_अभिव्यक्ती_P (t))
		t = वृक्ष_OPERAND (t, 0);
	      अन्यथा
		थांबा;
	    }
	  पर्यंत (1);
	}
      जर (!C_BOOLEAN_TYPE_P (वृक्ष_TYPE (t)))
	warn_logical_not_parentheses (location, code, arg1.मूल्य, arg2.मूल्य);
    }

  /* Warn about comparisons against string literals, with the exception
     of testing for equality or inequality of a string literal with NULL.  */
  जर (code == EQ_अभिव्यक्ती || code == NE_अभिव्यक्ती)
    {
      जर ((code1 == STRING_CST
	   && !integer_zerop (वृक्ष_strip_nop_conversions (arg2.मूल्य)))
	  || (code2 == STRING_CST
	      && !integer_zerop (वृक्ष_strip_nop_conversions (arg1.मूल्य))))
	warning_at (location, OPT_Waddress,
		    "comparison with string literal results in unspecified behavior");
      /* Warn for ptr == '\0', it's likely that it should've been ptr[0].  */
      जर (POINTER_TYPE_P (type1)
	  && null_pointer_constant_p (arg2.मूल्य)
	  && char_type_p (type2))
	{
	  auto_diagnostic_group d;
	  जर (warning_at (location, OPT_Wpointer_compare,
			    "comparison between pointer and zero character "
			    "constant"))
	    inform (arg1.get_start (),
		      "did you mean to dereference the pointer?");
	}
      अन्यथा जर (POINTER_TYPE_P (type2)
	       && null_pointer_constant_p (arg1.मूल्य)
	       && char_type_p (type1))
	{
	  auto_diagnostic_group d;
	  जर (warning_at (location, OPT_Wpointer_compare,
			    "comparison between pointer and zero character "
			    "constant"))
	    inform (arg2.get_start (),
		      "did you mean to dereference the pointer?");
	}
    }
  अन्यथा जर (वृक्ष_CODE_CLASS (code) == tcc_comparison
	   && (code1 == STRING_CST || code2 == STRING_CST))
    warning_at (location, OPT_Waddress,
		"comparison with string literal results in unspecified "
		"behavior");

  जर (warn_zero_as_null_pointer_constant
      && c_inhibit_evaluation_warnings == 0
      && वृक्ष_CODE_CLASS (code) == tcc_comparison)
    {
      जर ((वृक्ष_CODE (type1) == POINTER_TYPE
	   || वृक्ष_CODE (type1) == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type2)
	  && null_pointer_constant_p (arg2.मूल्य))
	warning_at (arg2.get_location(), OPT_Wzero_as_null_pointer_constant,
		    "zero as null pointer constant");

      जर ((वृक्ष_CODE (type2) == POINTER_TYPE
	   || वृक्ष_CODE (type2) == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type1)
	  && null_pointer_constant_p (arg1.मूल्य))
	warning_at (arg1.get_location(), OPT_Wzero_as_null_pointer_constant,
		    "zero as null pointer constant");
    }

  जर (warn_array_compare
      && वृक्ष_CODE_CLASS (code) == tcc_comparison
      && वृक्ष_CODE (type1) == ARRAY_TYPE
      && वृक्ष_CODE (type2) == ARRAY_TYPE)
    do_warn_array_compare (location, code, arg1.मूल्य, arg2.मूल्य);

  जर (वृक्ष_OVERFLOW_P (result.मूल्य)
      && !वृक्ष_OVERFLOW_P (arg1.मूल्य)
      && !वृक्ष_OVERFLOW_P (arg2.मूल्य))
    overflow_warning (location, result.मूल्य);

  /* Warn about comparisons of different enum types.  */
  जर (warn_enum_compare
      && वृक्ष_CODE_CLASS (code) == tcc_comparison
      && वृक्ष_CODE (type1) == ENUMERAL_TYPE
      && वृक्ष_CODE (type2) == ENUMERAL_TYPE
      && TYPE_MAIN_VARIANT (type1) != TYPE_MAIN_VARIANT (type2))
    warning_at (location, OPT_Wenum_compare,
		"comparison between %qT and %qT",
		type1, type2);

  जर (warn_xor_used_as_pow
      && code == BIT_XOR_अभिव्यक्ती
      && arg1.m_decimal
      && arg2.m_decimal)
    check_for_xor_used_as_pow (arg1.get_location (), arg1.मूल्य,
			       location,
			       arg2.get_location (), arg2.मूल्य);

  परत result;
}

/* Return a tree for the difference of pointers OP0 and OP1.
   The resulting tree has type ptrdiff_t.  If POINTER_SUBTRACT sanitization is
   enabled, assign to INSTRUMENT_EXPR call to libsanitizer.  */

स्थिर वृक्ष
pointer_diff (location_t loc, वृक्ष op0, वृक्ष op1, वृक्ष *instrument_अभिव्यक्ती)
{
  वृक्ष restype = ptrdiff_type_गाठ;
  वृक्ष result, inttype;

  addr_space_t as0 = TYPE_ADDR_SPACE (वृक्ष_TYPE (वृक्ष_TYPE (op0)));
  addr_space_t as1 = TYPE_ADDR_SPACE (वृक्ष_TYPE (वृक्ष_TYPE (op1)));
  वृक्ष target_type = वृक्ष_TYPE (वृक्ष_TYPE (op0));
  वृक्ष orig_op0 = op0;
  वृक्ष orig_op1 = op1;

  /* If the operands point into different address spaces, we need to
     explicitly convert them to pointers into the common address space
     before we can subtract the numerical address values.  */
  जर (as0 != as1)
    {
      addr_space_t as_common;
      वृक्ष common_type;

      /* Determine the common superset address space.  This is guaranteed
	 to exist because the caller verified that comp_target_types
	 returned non-zero.  */
      जर (!addr_space_superset (as0, as1, &as_common))
	gcc_unreachable ();

      common_type = common_pointer_type (वृक्ष_TYPE (op0), वृक्ष_TYPE (op1), NULL_वृक्ष);
      op0 = convert (common_type, op0);
      op1 = convert (common_type, op1);
    }

  /* Determine integer type result of the subtraction.  This will usually
     be the same as the result type (ptrdiff_t), but may need to be a wider
     type if pointers for the address space are wider than ptrdiff_t.  */
  जर (TYPE_PRECISION (restype) < TYPE_PRECISION (वृक्ष_TYPE (op0)))
    inttype = c_common_type_for_size (TYPE_PRECISION (वृक्ष_TYPE (op0)), 0);
  अन्यथा
    inttype = restype;

  जर (VOID_TYPE_P (target_type))
    pedwarn (loc, OPT_Wpointer_arith,
	     "pointer of type %<void *%> used in subtraction");
  जर (वृक्ष_CODE (target_type) == FUNCTION_TYPE)
    pedwarn (loc, OPT_Wpointer_arith,
	     "pointer to a function used in subtraction");

  जर (current_function_decl != NULL_वृक्ष
      && sanitize_flags_p (SANITIZE_POINTER_SUBTRACT))
    {
      op0 = save_अभिव्यक्ती (c_fully_fold (op0, असत्य, रिक्त));
      op1 = save_अभिव्यक्ती (c_fully_fold (op1, असत्य, रिक्त));

      वृक्ष tt = builtin_decl_explicit (BUILT_IN_ASAN_POINTER_SUBTRACT);
      *instrument_अभिव्यक्ती = build_call_अभिव्यक्ती_loc (loc, tt, 2, op0, op1);
    }

  /* First do the subtraction, then build the divide operator
     and only convert at the very end.
     Do not do default conversions in case restype is a short type.  */

  /* POINTER_DIFF_EXPR requires a signed integer type of the same size as
     pointers.  If some platform cannot provide that, or has a larger
     ptrdiff_type to support differences larger than half the address
     space, cast the pointers to some larger integer type and do the
     computations in that type.  */
  जर (TYPE_PRECISION (inttype) > TYPE_PRECISION (वृक्ष_TYPE (op0)))
    op0 = build_द्विमान_op (loc, MINUS_अभिव्यक्ती, convert (inttype, op0),
			   convert (inttype, op1), असत्य);
  अन्यथा
    {
      /* Cast away qualifiers.  */
      op0 = convert (c_common_type (वृक्ष_TYPE (op0), वृक्ष_TYPE (op0)), op0);
      op1 = convert (c_common_type (वृक्ष_TYPE (op1), वृक्ष_TYPE (op1)), op1);
      op0 = build2_loc (loc, POINTER_DIFF_अभिव्यक्ती, inttype, op0, op1);
    }

  /* This generates an error if op1 is pointer to incomplete type.  */
  जर (!COMPLETE_OR_VOID_TYPE_P (वृक्ष_TYPE (वृक्ष_TYPE (orig_op1))))
    error_at (loc, "arithmetic on pointer to an incomplete type");
  अन्यथा जर (verify_type_context (loc, TCTX_POINTER_ARITH,
				वृक्ष_TYPE (वृक्ष_TYPE (orig_op0))))
    verify_type_context (loc, TCTX_POINTER_ARITH,
			 वृक्ष_TYPE (वृक्ष_TYPE (orig_op1)));

  op1 = c_size_in_bytes (target_type);

  जर (pointer_to_zero_sized_aggr_p (वृक्ष_TYPE (orig_op1)))
    error_at (loc, "arithmetic on pointer to an empty aggregate");

  /* Divide by the size, in easiest possible way.  */
  result = fold_build2_loc (loc, EXACT_DIV_अभिव्यक्ती, inttype,
			    op0, convert (inttype, op1));

  /* Convert to final result type if necessary.  */
  परत convert (restype, result);
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
  वृक्ष lhs_addr = build_unary_op (loc, ADDR_अभिव्यक्ती, lhs, असत्य);
  वृक्ष seq_cst = build_int_cst (integer_type_गाठ, MEMMODEL_SEQ_CST);
  वृक्ष rhs_semantic_type = वृक्ष_TYPE (rhs);
  वृक्ष nonatomic_rhs_semantic_type;
  वृक्ष rhs_type;

  gcc_assert (TYPE_ATOMIC (lhs_type));

  जर (return_old_p)
    gcc_assert (modifycode == PLUS_अभिव्यक्ती || modifycode == MINUS_अभिव्यक्ती);

  /* Allocate enough vector items for a compare_exchange.  */
  vec_alloc (params, 6);

  /* Create a compound statement to hold the sequence of statements
     with a loop.  */
  जर (modifycode != NOP_अभिव्यक्ती)
    {
      compound_stmt = c_begin_compound_stmt (असत्य);

      /* For consistency with build_modify_expr on non-_Atomic,
	 mark the lhs as read.  Also, it would be very hard to match
	 such expressions in mark_exp_read.  */
      mark_exp_read (lhs);
    }

  /* Remove any excess precision (which is only present here in the
     case of compound assignments).  */
  जर (वृक्ष_CODE (rhs) == EXCESS_PRECISION_अभिव्यक्ती)
    {
      gcc_assert (modifycode != NOP_अभिव्यक्ती);
      rhs = वृक्ष_OPERAND (rhs, 0);
    }
  rhs_type = वृक्ष_TYPE (rhs);

  /* Fold the RHS if it hasn't already been folded.  */
  जर (modifycode != NOP_अभिव्यक्ती)
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
  rhs = build4 (TARGET_अभिव्यक्ती, nonatomic_rhs_type, val, rhs, NULL_वृक्ष,
		NULL_वृक्ष);
  वृक्ष_SIDE_EFFECTS (rhs) = 1;
  SET_अभिव्यक्ती_LOCATION (rhs, loc);
  जर (modifycode != NOP_अभिव्यक्ती)
    add_stmt (rhs);

  /* NOP_EXPR indicates it's a straight store of the RHS. Simply issue
     an atomic_store.  */
  जर (modifycode == NOP_अभिव्यक्ती)
    {
      compound_stmt = rhs;
      /* Build __atomic_store (&lhs, &val, SEQ_CST)  */
      rhs = build_unary_op (loc, ADDR_अभिव्यक्ती, val, असत्य);
      fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_STORE);
      params->quick_ढकला (lhs_addr);
      params->quick_ढकला (rhs);
      params->quick_ढकला (seq_cst);
      func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, रिक्त);

      compound_stmt = build2 (COMPOUND_अभिव्यक्ती, void_type_गाठ,
			      compound_stmt, func_call);

      /* VAL is the value which was stored, return a COMPOUND_STMT of
	 the statement and that value.  */
      परत build2 (COMPOUND_अभिव्यक्ती, nonatomic_lhs_type, compound_stmt, val);
    }

  /* Attempt to implement the atomic operation as an __atomic_fetch_* or
     __atomic_*_fetch built-in rather than a CAS loop.  atomic_bool type
     isn't applicable for such builtins.  ??? Do we want to handle enums?  */
  जर ((वृक्ष_CODE (lhs_type) == INTEGER_TYPE || POINTER_TYPE_P (lhs_type))
      && वृक्ष_CODE (rhs_type) == INTEGER_TYPE)
    {
      built_in_function fncode;
      निवड (modifycode)
	{
	स्थिती PLUS_अभिव्यक्ती:
	स्थिती POINTER_PLUS_अभिव्यक्ती:
	  fncode = (return_old_p
		    ? BUILT_IN_ATOMIC_FETCH_ADD_N
		    : BUILT_IN_ATOMIC_ADD_FETCH_N);
	  थांबा;
	स्थिती MINUS_अभिव्यक्ती:
	  fncode = (return_old_p
		    ? BUILT_IN_ATOMIC_FETCH_SUB_N
		    : BUILT_IN_ATOMIC_SUB_FETCH_N);
	  थांबा;
	स्थिती BIT_AND_अभिव्यक्ती:
	  fncode = (return_old_p
		    ? BUILT_IN_ATOMIC_FETCH_AND_N
		    : BUILT_IN_ATOMIC_AND_FETCH_N);
	  थांबा;
	स्थिती BIT_IOR_अभिव्यक्ती:
	  fncode = (return_old_p
		    ? BUILT_IN_ATOMIC_FETCH_OR_N
		    : BUILT_IN_ATOMIC_OR_FETCH_N);
	  थांबा;
	स्थिती BIT_XOR_अभिव्यक्ती:
	  fncode = (return_old_p
		    ? BUILT_IN_ATOMIC_FETCH_XOR_N
		    : BUILT_IN_ATOMIC_XOR_FETCH_N);
	  थांबा;
	पूर्वनिर्धारित:
	  जा cas_loop;
	}

      /* We can only use "_1" through "_16" variants of the atomic fetch
	 built-ins.  */
      अचिन्हित HOST_WIDE_INT size = वृक्ष_to_uhwi (TYPE_SIZE_UNIT (lhs_type));
      जर (size != 1 && size != 2 && size != 4 && size != 8 && size != 16)
	जा cas_loop;

      /* If this is a pointer type, we need to multiply by the size of
	 the pointer target type.  */
      जर (POINTER_TYPE_P (lhs_type))
	{
	  जर (!COMPLETE_TYPE_P (वृक्ष_TYPE (lhs_type))
	      /* ??? This would introduce -Wdiscarded-qualifiers
		 warning: __atomic_fetch_* expect volatile void *
		 type as the first argument.  (Assignments between
		 atomic and non-atomic objects are OK.) */
	      || TYPE_RESTRICT (lhs_type))
	    जा cas_loop;
	  वृक्ष sz = TYPE_SIZE_UNIT (वृक्ष_TYPE (lhs_type));
	  rhs = fold_build2_loc (loc, MULT_अभिव्यक्ती, ptrdiff_type_गाठ,
				 convert (ptrdiff_type_गाठ, rhs),
				 convert (ptrdiff_type_गाठ, sz));
	}

      /* Build __atomic_fetch_* (&lhs, &val, SEQ_CST), or
	 __atomic_*_fetch (&lhs, &val, SEQ_CST).  */
      fndecl = builtin_decl_explicit (fncode);
      params->quick_ढकला (lhs_addr);
      params->quick_ढकला (rhs);
      params->quick_ढकला (seq_cst);
      func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, रिक्त);

      newval = create_tmp_var_raw (nonatomic_lhs_type);
      वृक्ष_ADDRESSABLE (newval) = 1;
      suppress_warning (newval);
      rhs = build4 (TARGET_अभिव्यक्ती, nonatomic_lhs_type, newval, func_call,
		    NULL_वृक्ष, NULL_वृक्ष);
      SET_अभिव्यक्ती_LOCATION (rhs, loc);
      add_stmt (rhs);

      /* Finish the compound statement.  */
      compound_stmt = c_end_compound_stmt (loc, compound_stmt, असत्य);

      /* NEWVAL is the value which was stored, return a COMPOUND_STMT of
	 the statement and that value.  */
      परत build2 (COMPOUND_अभिव्यक्ती, nonatomic_lhs_type, compound_stmt, newval);
    }

cas_loop:
  /* Create the variables and labels required for the op= form.  */
  old = create_tmp_var_raw (nonatomic_lhs_type);
  old_addr = build_unary_op (loc, ADDR_अभिव्यक्ती, old, असत्य);
  वृक्ष_ADDRESSABLE (old) = 1;
  suppress_warning (old);

  newval = create_tmp_var_raw (nonatomic_lhs_type);
  newval_addr = build_unary_op (loc, ADDR_अभिव्यक्ती, newval, असत्य);
  वृक्ष_ADDRESSABLE (newval) = 1;
  suppress_warning (newval);

  loop_decl = create_artificial_label (loc);
  loop_label = build1 (LABEL_अभिव्यक्ती, void_type_गाठ, loop_decl);

  done_decl = create_artificial_label (loc);
  done_label = build1 (LABEL_अभिव्यक्ती, void_type_गाठ, done_decl);

  /* __atomic_load (addr, &old, SEQ_CST).  */
  fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_LOAD);
  params->quick_ढकला (lhs_addr);
  params->quick_ढकला (old_addr);
  params->quick_ढकला (seq_cst);
  func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, रिक्त);
  old = build4 (TARGET_अभिव्यक्ती, nonatomic_lhs_type, old, func_call, NULL_वृक्ष,
		NULL_वृक्ष);
  add_stmt (old);
  params->truncate (0);

  /* Create the expressions for floating-point environment
     manipulation, if required.  */
  तार्किक need_fenv = (flag_trapping_math
		    && (FLOAT_TYPE_P (lhs_type) || FLOAT_TYPE_P (rhs_type)));
  वृक्ष hold_call = NULL_वृक्ष, clear_call = NULL_वृक्ष, update_call = NULL_वृक्ष;
  जर (need_fenv)
    targetm.atomic_assign_expand_fenv (&hold_call, &clear_call, &update_call);

  जर (hold_call)
    add_stmt (hold_call);

  /* loop:  */
  add_stmt (loop_label);

  /* newval = old + val;  */
  जर (rhs_type != rhs_semantic_type)
    val = build1 (EXCESS_PRECISION_अभिव्यक्ती, nonatomic_rhs_semantic_type, val);
  rhs = build_द्विमान_op (loc, modifycode,
			 convert_lvalue_to_rvalue (loc, old, सत्य, सत्य),
			 val, सत्य);
  जर (वृक्ष_CODE (rhs) == EXCESS_PRECISION_अभिव्यक्ती)
    {
      वृक्ष eptype = वृक्ष_TYPE (rhs);
      rhs = c_fully_fold (वृक्ष_OPERAND (rhs, 0), असत्य, रिक्त);
      rhs = build1 (EXCESS_PRECISION_अभिव्यक्ती, eptype, rhs);
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
  जर (rhs == error_mark_गाठ)
    rhs = old;
  rhs = build4 (TARGET_अभिव्यक्ती, nonatomic_lhs_type, newval, rhs, NULL_वृक्ष,
		NULL_वृक्ष);
  SET_अभिव्यक्ती_LOCATION (rhs, loc);
  add_stmt (rhs);

  /* if (__atomic_compare_exchange (addr, &old, &new, false, SEQ_CST, SEQ_CST))
       goto done;  */
  fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_COMPARE_EXCHANGE);
  params->quick_ढकला (lhs_addr);
  params->quick_ढकला (old_addr);
  params->quick_ढकला (newval_addr);
  params->quick_ढकला (integer_zero_गाठ);
  params->quick_ढकला (seq_cst);
  params->quick_ढकला (seq_cst);
  func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, रिक्त);

  goto_stmt = build1 (GOTO_अभिव्यक्ती, void_type_गाठ, done_decl);
  SET_अभिव्यक्ती_LOCATION (goto_stmt, loc);

  stmt = build3 (COND_अभिव्यक्ती, void_type_गाठ, func_call, goto_stmt, NULL_वृक्ष);
  SET_अभिव्यक्ती_LOCATION (stmt, loc);
  add_stmt (stmt);

  जर (clear_call)
    add_stmt (clear_call);

  /* goto loop;  */
  goto_stmt  = build1 (GOTO_अभिव्यक्ती, void_type_गाठ, loop_decl);
  SET_अभिव्यक्ती_LOCATION (goto_stmt, loc);
  add_stmt (goto_stmt);

  /* done:  */
  add_stmt (done_label);

  जर (update_call)
    add_stmt (update_call);

  /* Finish the compound statement.  */
  compound_stmt = c_end_compound_stmt (loc, compound_stmt, असत्य);

  /* NEWVAL is the value that was successfully stored, return a
     COMPOUND_EXPR of the statement and the appropriate value.  */
  परत build2 (COMPOUND_अभिव्यक्ती, nonatomic_lhs_type, compound_stmt,
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
  वृक्ष ret = error_mark_गाठ;
  वृक्ष eptype = NULL_वृक्ष;
  स्थिरांक अक्षर *invalid_op_diag;

  /* If ARG is wrapped in a call to .ACCESS_WITH_SIZE — created when the
     C parser rvalue-converts a counted_by-annotated member access (see
     PR123569) — unwrap it here.  Unary operators that consume an rvalue
     (!, -, +) read the value itself rather than dereferencing into the
     pointed-to data, so the bounds-checking wrapper is unnecessary and
     would otherwise reach build_unary_op while it is not equipped to
     handle the wrapped form.  PR123569 fixed the ++/-- side of this by
     suppressing wrapper creation in the parser; the rvalue-consuming
     ops still receive the wrapper and need to strip it here.  */
  जर (is_access_with_size_p (arg))
    xarg = arg = get_ref_from_access_with_size (arg);

  gcc_checking_assert (!is_access_with_size_p (arg));

  तार्किक int_operands = अभिव्यक्ती_INT_CONST_OPERANDS (xarg);
  जर (int_operands)
    arg = remove_c_maybe_const_अभिव्यक्ती (arg);

  जर (code != ADDR_अभिव्यक्ती)
    arg = require_complete_type (location, arg);

  typecode = वृक्ष_CODE (वृक्ष_TYPE (arg));
  जर (typecode == ERROR_MARK)
    परत error_mark_गाठ;
  जर (typecode == ENUMERAL_TYPE || typecode == BOOLEAN_TYPE)
    typecode = INTEGER_TYPE;

  जर ((invalid_op_diag
       = targetm.invalid_unary_op (code, वृक्ष_TYPE (xarg))))
    {
      error_at (location, invalid_op_diag);
      परत error_mark_गाठ;
    }

  जर (वृक्ष_CODE (arg) == EXCESS_PRECISION_अभिव्यक्ती)
    {
      eptype = वृक्ष_TYPE (arg);
      arg = वृक्ष_OPERAND (arg, 0);
    }

  निवड (code)
    {
    स्थिती CONVERT_अभिव्यक्ती:
      /* This is used for unary plus, because a CONVERT_EXPR
	 is enough to prevent anybody from looking inside for
	 associativity, but won't generate any code.  */
      जर (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE
	    || typecode == FIXED_POINT_TYPE || typecode == COMPLEX_TYPE
	    || typecode == BITINT_TYPE
	    || gnu_vector_type_p (वृक्ष_TYPE (arg))))
	{
	  error_at (location, "wrong type argument to unary plus");
	  परत error_mark_गाठ;
	}
      अन्यथा जर (!noconvert)
	arg = default_conversion (arg);
      arg = non_lvalue_loc (location, arg);
      थांबा;

    स्थिती NEGATE_अभिव्यक्ती:
      जर (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE
	    || typecode == FIXED_POINT_TYPE || typecode == COMPLEX_TYPE
	    || typecode == BITINT_TYPE
	    || gnu_vector_type_p (वृक्ष_TYPE (arg))))
	{
	  error_at (location, "wrong type argument to unary minus");
	  परत error_mark_गाठ;
	}
      अन्यथा जर (!noconvert)
	arg = default_conversion (arg);
      थांबा;

    स्थिती BIT_NOT_अभिव्यक्ती:
      /* ~ works on integer types and non float vectors. */
      जर (typecode == INTEGER_TYPE
	  || typecode == BITINT_TYPE
	  || (gnu_vector_type_p (वृक्ष_TYPE (arg))
	      && !VECTOR_FLOAT_TYPE_P (वृक्ष_TYPE (arg))))
	{
	  वृक्ष e = arg;

	  /* Warn if the expression has boolean value.  */
	  पर्यंत (वृक्ष_CODE (e) == COMPOUND_अभिव्यक्ती)
	    e = वृक्ष_OPERAND (e, 1);

	  जर ((C_BOOLEAN_TYPE_P (वृक्ष_TYPE (arg))
	       || truth_मूल्य_p (वृक्ष_CODE (e))))
	    {
	      auto_diagnostic_group d;
	      जर (warning_at (location, OPT_Wbool_operation,
				"%<~%> on a boolean expression"))
		{
		  gcc_rich_location richloc (location);
		  richloc.add_fixit_घाला_before (location, "!");
		  inform (&richloc, "did you mean to use logical not?");
		}
	    }
	  जर (!noconvert)
	    arg = default_conversion (arg);
	}
      अन्यथा जर (typecode == COMPLEX_TYPE)
	{
	  code = CONJ_अभिव्यक्ती;
	  pedwarn (location, OPT_Wpedantic,
		   "ISO C does not support %<~%> for complex conjugation");
	  जर (!noconvert)
	    arg = default_conversion (arg);
	}
      अन्यथा
	{
	  error_at (location, "wrong type argument to bit-complement");
	  परत error_mark_गाठ;
	}
      थांबा;

    स्थिती ABS_अभिव्यक्ती:
      जर (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE))
	{
	  error_at (location, "wrong type argument to abs");
	  परत error_mark_गाठ;
	}
      अन्यथा जर (!noconvert)
	arg = default_conversion (arg);
      थांबा;

    स्थिती ABSU_अभिव्यक्ती:
      जर (!(typecode == INTEGER_TYPE))
	{
	  error_at (location, "wrong type argument to absu");
	  परत error_mark_गाठ;
	}
      अन्यथा जर (!noconvert)
	arg = default_conversion (arg);
      थांबा;

    स्थिती CONJ_अभिव्यक्ती:
      /* Conjugating a real value is a no-op, but allow it anyway.  */
      जर (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE
	    || typecode == COMPLEX_TYPE))
	{
	  error_at (location, "wrong type argument to conjugation");
	  परत error_mark_गाठ;
	}
      अन्यथा जर (!noconvert)
	arg = default_conversion (arg);
      थांबा;

    स्थिती TRUTH_NOT_अभिव्यक्ती:
      जर (typecode != INTEGER_TYPE && typecode != FIXED_POINT_TYPE
	  && typecode != REAL_TYPE && typecode != POINTER_TYPE
	  && typecode != COMPLEX_TYPE && typecode != NULLPTR_TYPE
	  && typecode != BITINT_TYPE)
	{
	  error_at (location,
		    "wrong type argument to unary exclamation mark");
	  परत error_mark_गाठ;
	}
      जर (int_operands)
	{
	  arg = c_objc_common_truthvalue_conversion (location, xarg);
	  arg = remove_c_maybe_const_अभिव्यक्ती (arg);
	}
      अन्यथा
	arg = c_objc_common_truthvalue_conversion (location, arg);
      ret = invert_truthvalue_loc (location, arg);
      eptype = NULL_वृक्ष;
      /* If the TRUTH_NOT_EXPR has been folded, reset the location.  */
      जर (अभिव्यक्ती_P (ret) && अभिव्यक्ती_HAS_LOCATION (ret))
	location = अभिव्यक्ती_LOCATION (ret);
      जा return_build_unary_op;

    स्थिती REALPART_अभिव्यक्ती:
    स्थिती IMAGPART_अभिव्यक्ती:
      ret = build_real_imag_अभिव्यक्ती (location, code, arg);
      जर (ret == error_mark_गाठ)
	परत error_mark_गाठ;
      जर (eptype && वृक्ष_CODE (eptype) == COMPLEX_TYPE)
	eptype = वृक्ष_TYPE (eptype);
      जा return_build_unary_op;

    स्थिती PREINCREMENT_अभिव्यक्ती:
    स्थिती POSTINCREMENT_अभिव्यक्ती:
    स्थिती PREDECREMENT_अभिव्यक्ती:
    स्थिती POSTDECREMENT_अभिव्यक्ती:

      जर (वृक्ष_CODE (arg) == C_MAYBE_CONST_अभिव्यक्ती)
	{
	  वृक्ष inner = build_unary_op (location, code,
				       C_MAYBE_CONST_अभिव्यक्ती_अभिव्यक्ती (arg),
				       noconvert);
	  जर (inner == error_mark_गाठ)
	    परत error_mark_गाठ;
	  ret = build2 (C_MAYBE_CONST_अभिव्यक्ती, वृक्ष_TYPE (inner),
			C_MAYBE_CONST_अभिव्यक्ती_PRE (arg), inner);
	  gcc_assert (!C_MAYBE_CONST_अभिव्यक्ती_INT_OPERANDS (arg));
	  C_MAYBE_CONST_अभिव्यक्ती_NON_CONST (ret) = 1;
	  जा return_build_unary_op;
	}

      /* Complain about anything that is not a true lvalue.  In
	 Objective-C, skip this check for property_refs.  */
      जर (!objc_is_property_ref (arg)
	  && !lvalue_or_else (location,
			      arg, ((code == PREINCREMENT_अभिव्यक्ती
				     || code == POSTINCREMENT_अभिव्यक्ती)
				    ? lv_increment
				    : lv_decrement)))
	परत error_mark_गाठ;

      जर (warn_cxx_compat && वृक्ष_CODE (वृक्ष_TYPE (arg)) == ENUMERAL_TYPE)
	{
	  जर (code == PREINCREMENT_अभिव्यक्ती || code == POSTINCREMENT_अभिव्यक्ती)
	    warning_at (location, OPT_Wc___compat,
			"increment of enumeration value is invalid in C++");
	  अन्यथा
	    warning_at (location, OPT_Wc___compat,
			"decrement of enumeration value is invalid in C++");
	}

      जर (C_BOOLEAN_TYPE_P (वृक्ष_TYPE (arg)))
	{
	  जर (code == PREINCREMENT_अभिव्यक्ती || code == POSTINCREMENT_अभिव्यक्ती)
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
      जर (typecode == COMPLEX_TYPE)
	{
	  वृक्ष real, imag;

	  pedwarn_c23 (location, OPT_Wpedantic,
		       "ISO C does not support %<++%> and %<--%> on complex "
		       "types before C2Y");

	  जर (!atomic_op)
	    {
	      arg = stabilize_reference (arg);
	      real = build_unary_op (अभिव्यक्ती_LOCATION (arg), REALPART_अभिव्यक्ती, arg,
				     सत्य);
	      imag = build_unary_op (अभिव्यक्ती_LOCATION (arg), IMAGPART_अभिव्यक्ती, arg,
				     सत्य);
	      real = build_unary_op (अभिव्यक्ती_LOCATION (arg), code, real, सत्य);
	      जर (real == error_mark_गाठ || imag == error_mark_गाठ)
		परत error_mark_गाठ;
	      ret = build2 (COMPLEX_अभिव्यक्ती, वृक्ष_TYPE (arg),
			    real, imag);
	      जा return_build_unary_op;
	    }
	}

      /* Report invalid types.  */

      जर (typecode != POINTER_TYPE && typecode != FIXED_POINT_TYPE
	  && typecode != INTEGER_TYPE && typecode != REAL_TYPE
	  && typecode != COMPLEX_TYPE && typecode != BITINT_TYPE
	  && !gnu_vector_type_p (वृक्ष_TYPE (arg)))
	{
	  जर (code == PREINCREMENT_अभिव्यक्ती || code == POSTINCREMENT_अभिव्यक्ती)
	    error_at (location, "wrong type argument to increment");
	  अन्यथा
	    error_at (location, "wrong type argument to decrement");

	  परत error_mark_गाठ;
	}

      {
	वृक्ष inc;

	argtype = वृक्ष_TYPE (arg);

	/* Compute the increment.  */

	जर (typecode == POINTER_TYPE)
	  {
	    /* If pointer target is an incomplete type,
	       we just cannot know how to do the arithmetic.  */
	    जर (!COMPLETE_OR_VOID_TYPE_P (वृक्ष_TYPE (argtype)))
	      {
		जर (code == PREINCREMENT_अभिव्यक्ती || code == POSTINCREMENT_अभिव्यक्ती)
		  error_at (location,
			    "increment of pointer to an incomplete type %qT",
			    वृक्ष_TYPE (argtype));
		अन्यथा
		  error_at (location,
			    "decrement of pointer to an incomplete type %qT",
			    वृक्ष_TYPE (argtype));
	      }
	    अन्यथा जर (वृक्ष_CODE (वृक्ष_TYPE (argtype)) == FUNCTION_TYPE
		     || VOID_TYPE_P (वृक्ष_TYPE (argtype)))
	      {
		जर (code == PREINCREMENT_अभिव्यक्ती || code == POSTINCREMENT_अभिव्यक्ती)
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
	अन्यथा जर (FRACT_MODE_P (TYPE_MODE (argtype)))
	  {
	    /* For signed fract types, we invert ++ to -- or
	       -- to ++, and change inc from 1 to -1, because
	       it is not possible to represent 1 in signed fract constants.
	       For unsigned fract types, the result always overflows and
	       we get an undefined (original) or the maximum value.  */
	    जर (code == PREINCREMENT_अभिव्यक्ती)
	      code = PREDECREMENT_अभिव्यक्ती;
	    अन्यथा जर (code == PREDECREMENT_अभिव्यक्ती)
	      code = PREINCREMENT_अभिव्यक्ती;
	    अन्यथा जर (code == POSTINCREMENT_अभिव्यक्ती)
	      code = POSTDECREMENT_अभिव्यक्ती;
	    अन्यथा /* code == POSTDECREMENT_EXPR  */
	      code = POSTINCREMENT_अभिव्यक्ती;

	    inc = integer_minus_one_गाठ;
	    inc = convert (argtype, inc);
	  }
	अन्यथा
	  {
	    inc = VECTOR_TYPE_P (argtype)
	      ? build_one_cst (argtype)
	      : integer_one_गाठ;
	    inc = convert (argtype, inc);
	  }

	/* If 'arg' is an Objective-C PROPERTY_REF expression, then we
	   need to ask Objective-C to build the increment or decrement
	   expression for it.  */
	जर (objc_is_property_ref (arg))
	  परत objc_build_incr_अभिव्यक्ती_for_property_ref (location, code,
							arg, inc);

	/* Report a read-only lvalue.  */
	जर (TYPE_READONLY (argtype))
	  {
	    readonly_error (location, arg,
			    ((code == PREINCREMENT_अभिव्यक्ती
			      || code == POSTINCREMENT_अभिव्यक्ती)
			     ? lv_increment : lv_decrement));
	    परत error_mark_गाठ;
	  }
	अन्यथा जर (वृक्ष_READONLY (arg))
	  readonly_warning (arg,
			    ((code == PREINCREMENT_अभिव्यक्ती
			      || code == POSTINCREMENT_अभिव्यक्ती)
			     ? lv_increment : lv_decrement));

	/* If the argument is atomic, use the special code sequences for
	   atomic compound assignment.  */
	जर (atomic_op)
	  {
	    arg = stabilize_reference (arg);
	    ret = build_atomic_assign (location, arg,
				       ((code == PREINCREMENT_अभिव्यक्ती
					 || code == POSTINCREMENT_अभिव्यक्ती)
					? PLUS_अभिव्यक्ती
					: MINUS_अभिव्यक्ती),
				       (FRACT_MODE_P (TYPE_MODE (argtype))
					? inc
					: integer_one_गाठ),
				       (code == POSTINCREMENT_अभिव्यक्ती
					|| code == POSTDECREMENT_अभिव्यक्ती));
	    जा return_build_unary_op;
	  }

	वृक्ष true_res;
	जर (c_hardbool_type_attr (वृक्ष_TYPE (arg), रिक्त, &true_res))
	  {
	    वृक्ष larg = stabilize_reference (arg);
	    वृक्ष sarg = save_अभिव्यक्ती (larg);
	    निवड (code)
	      {
	      स्थिती PREINCREMENT_अभिव्यक्ती:
		val = build2 (MODIFY_अभिव्यक्ती, वृक्ष_TYPE (larg), larg, true_res);
		val = build2 (COMPOUND_अभिव्यक्ती, वृक्ष_TYPE (larg), sarg, val);
		थांबा;
	      स्थिती POSTINCREMENT_अभिव्यक्ती:
		val = build2 (MODIFY_अभिव्यक्ती, वृक्ष_TYPE (larg), larg, true_res);
		val = build2 (COMPOUND_अभिव्यक्ती, वृक्ष_TYPE (larg), val, sarg);
		val = build2 (COMPOUND_अभिव्यक्ती, वृक्ष_TYPE (larg), sarg, val);
		थांबा;
	      स्थिती PREDECREMENT_अभिव्यक्ती:
		{
		  वृक्ष rarg = convert_lvalue_to_rvalue (location, sarg,
							सत्य, सत्य);
		  rarg = invert_truthvalue_loc (location, rarg);
		  rarg = convert (वृक्ष_TYPE (sarg), rarg);
		  val = build2 (MODIFY_अभिव्यक्ती, वृक्ष_TYPE (larg), larg, rarg);
		}
		थांबा;
	      स्थिती POSTDECREMENT_अभिव्यक्ती:
		{
		  वृक्ष rarg = convert_lvalue_to_rvalue (location, sarg,
							सत्य, सत्य);
		  rarg = invert_truthvalue_loc (location, rarg);
		  वृक्ष iarg = convert (वृक्ष_TYPE (larg), rarg);
		  val = build2 (MODIFY_अभिव्यक्ती, वृक्ष_TYPE (larg), larg, iarg);
		  val = build2 (COMPOUND_अभिव्यक्ती, वृक्ष_TYPE (larg), val, sarg);
		  val = build2 (COMPOUND_अभिव्यक्ती, वृक्ष_TYPE (larg), sarg, val);
		}
		थांबा;
	      पूर्वनिर्धारित:
		gcc_unreachable ();
	      }
	    वृक्ष_SIDE_EFFECTS (val) = 1;
	  }
	अन्यथा जर (C_BOOLEAN_TYPE_P (वृक्ष_TYPE (arg)))
	  val = boolean_increment (code, arg);
	अन्यथा
	  val = build2 (code, वृक्ष_TYPE (arg), arg, inc);
	वृक्ष_SIDE_EFFECTS (val) = 1;
	जर (TYPE_QUALS (वृक्ष_TYPE (val)) != TYPE_UNQUALIFIED)
	  वृक्ष_TYPE (val) = c_build_qualified_type (वृक्ष_TYPE (val),
						    TYPE_UNQUALIFIED);
	ret = val;
	जा return_build_unary_op;
      }

    स्थिती ADDR_अभिव्यक्ती:
      /* Note that this operation never does default_conversion.  */

      /* The operand of unary '&' must be an lvalue (which excludes
	 expressions of type void), or, in C99, the result of a [] or
	 unary '*' operator.  */
      जर (VOID_TYPE_P (वृक्ष_TYPE (arg))
	  && TYPE_QUALS (वृक्ष_TYPE (arg)) == TYPE_UNQUALIFIED
	  && (!INDIRECT_REF_P (arg) || !flag_isoc99))
	pedwarn (location, 0, "taking address of expression of type %<void%>");

      /* Let &* cancel out to simplify resulting code.  */
      जर (INDIRECT_REF_P (arg))
	{
	  /* Don't let this be an lvalue.  */
	  जर (lvalue_p (वृक्ष_OPERAND (arg, 0)))
	    परत non_lvalue_loc (location, वृक्ष_OPERAND (arg, 0));
	  ret = वृक्ष_OPERAND (arg, 0);
	  जा return_build_unary_op;
	}

      /* Anything not already handled and not a true memory reference
	 or a non-lvalue array is an error.  */
      जर (typecode != FUNCTION_TYPE && !noconvert
	  && !lvalue_or_else (location, arg, lv_addressof))
	परत error_mark_गाठ;

      /* Move address operations inside C_MAYBE_CONST_EXPR to simplify
	 folding later.  */
      जर (वृक्ष_CODE (arg) == C_MAYBE_CONST_अभिव्यक्ती)
	{
	  वृक्ष inner = build_unary_op (location, code,
				       C_MAYBE_CONST_अभिव्यक्ती_अभिव्यक्ती (arg),
				       noconvert);
	  ret = build2 (C_MAYBE_CONST_अभिव्यक्ती, वृक्ष_TYPE (inner),
			C_MAYBE_CONST_अभिव्यक्ती_PRE (arg), inner);
	  gcc_assert (!C_MAYBE_CONST_अभिव्यक्ती_INT_OPERANDS (arg));
	  C_MAYBE_CONST_अभिव्यक्ती_NON_CONST (ret)
	    = C_MAYBE_CONST_अभिव्यक्ती_NON_CONST (arg);
	  जा return_build_unary_op;
	}

      /* Ordinary case; arg is a COMPONENT_REF or a decl.  */

      argtype = वृक्ष_TYPE (arg);

      /* If the lvalue is const or volatile, merge that into the type
	 to which the address will point.  This is only needed
	 for function types.  */
      जर ((DECL_P (arg) || REFERENCE_CLASS_P (arg))
	  && (वृक्ष_READONLY (arg) || वृक्ष_THIS_VOLATILE (arg))
	  && वृक्ष_CODE (argtype) == FUNCTION_TYPE)
	{
	  पूर्णांक orig_quals = TYPE_QUALS (strip_array_types (argtype));
	  पूर्णांक quals = orig_quals;

	  जर (वृक्ष_READONLY (arg))
	    quals |= TYPE_QUAL_CONST;
	  जर (वृक्ष_THIS_VOLATILE (arg))
	    quals |= TYPE_QUAL_VOLATILE;

	  argtype = c_build_qualified_type (argtype, quals);
	}

      निवड (वृक्ष_CODE (arg))
	{
	स्थिती COMPONENT_REF:
	  जर (DECL_C_BIT_FIELD (वृक्ष_OPERAND (arg, 1)))
	    {
	      error_at (location, "cannot take address of bit-field %qD",
			वृक्ष_OPERAND (arg, 1));
	      परत error_mark_गाठ;
	    }

	  /* fall through */

	स्थिती ARRAY_REF:
	  जर (TYPE_REVERSE_STORAGE_ORDER (वृक्ष_TYPE (वृक्ष_OPERAND (arg, 0))))
	    {
	      जर (!AGGREGATE_TYPE_P (वृक्ष_TYPE (arg))
		  && !POINTER_TYPE_P (वृक्ष_TYPE (arg))
		  && !VECTOR_TYPE_P (वृक्ष_TYPE (arg)))
		{
		  error_at (location, "cannot take address of scalar with "
			    "reverse storage order");
		  परत error_mark_गाठ;
		}

	      जर (वृक्ष_CODE (वृक्ष_TYPE (arg)) == ARRAY_TYPE
		  && TYPE_REVERSE_STORAGE_ORDER (वृक्ष_TYPE (arg)))
		warning_at (location, OPT_Wscalar_storage_order,
			    "address of array with reverse scalar storage "
			    "order requested");
	    }

	पूर्वनिर्धारित:
	  थांबा;
	}

      जर (!c_mark_addressable (arg))
	परत error_mark_गाठ;

      gcc_assert (वृक्ष_CODE (arg) != COMPONENT_REF
		  || !DECL_C_BIT_FIELD (वृक्ष_OPERAND (arg, 1)));

      argtype = c_build_pointer_type (argtype);

      /* ??? Cope with user tricks that amount to offsetof.  Delete this
	 when we have proper support for integer constant expressions.  */
      val = get_base_address (arg);
      जर (val && INDIRECT_REF_P (val)
          && वृक्ष_CONSTANT (वृक्ष_OPERAND (val, 0)))
	{
	  ret = fold_offsetof (arg, argtype);
	  जा return_build_unary_op;
	}

      val = build1 (ADDR_अभिव्यक्ती, argtype, arg);

      ret = val;
      जा return_build_unary_op;

    स्थिती PAREN_अभिव्यक्ती:
      ret = build1 (code, वृक्ष_TYPE (arg), arg);
      जा return_build_unary_op;

    पूर्वनिर्धारित:
      gcc_unreachable ();
    }

  जर (argtype == NULL_वृक्ष)
    argtype = वृक्ष_TYPE (arg);
  जर (वृक्ष_CODE (arg) == INTEGER_CST)
    ret = (require_constant_मूल्य
	   ? fold_build1_initializer_loc (location, code, argtype, arg)
	   : fold_build1_loc (location, code, argtype, arg));
  अन्यथा
    ret = build1 (code, argtype, arg);
 return_build_unary_op:
  gcc_assert (ret != error_mark_गाठ);
  जर (वृक्ष_CODE (ret) == INTEGER_CST && !वृक्ष_OVERFLOW (ret)
      && !(वृक्ष_CODE (xarg) == INTEGER_CST && !वृक्ष_OVERFLOW (xarg)))
    ret = build1 (NOP_अभिव्यक्ती, वृक्ष_TYPE (ret), ret);
  अन्यथा जर (वृक्ष_CODE (ret) != INTEGER_CST && int_operands)
    ret = note_integer_operands (ret);
  जर (eptype)
    ret = build1 (EXCESS_PRECISION_अभिव्यक्ती, eptype, ret);
  protected_set_अभिव्यक्ती_location (ret, location);
  परत ret;
}

/* Return nonzero if REF is an lvalue valid for this language.
   Lvalues can be assigned, unless their type has TYPE_READONLY.
   Lvalues can have their address taken, unless they have C_DECL_REGISTER.  */

तार्किक
lvalue_p (const_वृक्ष ref)
{
  स्थिरांक गणना वृक्ष_code code = वृक्ष_CODE (ref);

  निवड (code)
    {
    स्थिती REALPART_अभिव्यक्ती:
    स्थिती IMAGPART_अभिव्यक्ती:
    स्थिती COMPONENT_REF:
      परत lvalue_p (वृक्ष_OPERAND (ref, 0));

    स्थिती C_MAYBE_CONST_अभिव्यक्ती:
      परत lvalue_p (वृक्ष_OPERAND (ref, 1));

    स्थिती COMPOUND_LITERAL_अभिव्यक्ती:
    स्थिती STRING_CST:
      परत सत्य;

    स्थिती MEM_REF:
    स्थिती TARGET_MEM_REF:
      /* MEM_REFs can appear from -fgimple parsing or folding, so allow them
	 here as well.  */
    स्थिती INDIRECT_REF:
    स्थिती ARRAY_REF:
    स्थिती VAR_DECL:
    स्थिती PARM_DECL:
    स्थिती RESULT_DECL:
    स्थिती ERROR_MARK:
      परत (वृक्ष_CODE (वृक्ष_TYPE (ref)) != FUNCTION_TYPE
	      && वृक्ष_CODE (वृक्ष_TYPE (ref)) != METHOD_TYPE);

    स्थिती BIND_अभिव्यक्ती:
      परत वृक्ष_CODE (वृक्ष_TYPE (ref)) == ARRAY_TYPE;

    स्थिती CALL_अभिव्यक्ती:
      परत is_access_with_size_p (ref);

    पूर्वनिर्धारित:
      परत असत्य;
    }
}

/* Give a warning for storing in something that is read-only in GCC
   terms but not const in ISO C terms.  */

स्थिर शून्य
readonly_warning (वृक्ष arg, गणना lvalue_use use)
{
  निवड (use)
    {
    स्थिती lv_assign:
      warning (0, "assignment of read-only location %qE", arg);
      थांबा;
    स्थिती lv_increment:
      warning (0, "increment of read-only location %qE", arg);
      थांबा;
    स्थिती lv_decrement:
      warning (0, "decrement of read-only location %qE", arg);
      थांबा;
    पूर्वनिर्धारित:
      gcc_unreachable ();
    }
  परत;
}


/* Return nonzero if REF is an lvalue valid for this language;
   otherwise, print an error message and return zero.  USE says
   how the lvalue is being used and so selects the error message.
   LOCATION is the location at which any error should be reported.  */

स्थिर पूर्णांक
lvalue_or_else (location_t loc, const_वृक्ष ref, गणना lvalue_use use)
{
  पूर्णांक win = lvalue_p (ref);

  जर (!win)
    lvalue_error (loc, use);

  परत win;
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

  पर्यंत (1)
    निवड (वृक्ष_CODE (x))
      {
      स्थिती VIEW_CONVERT_अभिव्यक्ती:
	जर (array_ref_p
	    && वृक्ष_CODE (वृक्ष_TYPE (x)) == ARRAY_TYPE
	    && VECTOR_TYPE_P (वृक्ष_TYPE (वृक्ष_OPERAND (x, 0))))
	  परत सत्य;
	x = वृक्ष_OPERAND (x, 0);
	थांबा;

      स्थिती COMPONENT_REF:
	जर (DECL_C_BIT_FIELD (वृक्ष_OPERAND (x, 1)))
	  {
	    error ("cannot take address of bit-field %qD",
		   वृक्ष_OPERAND (x, 1));
	    परत असत्य;
	  }
	/* FALLTHRU */
      स्थिती ADDR_अभिव्यक्ती:
      स्थिती ARRAY_REF:
      स्थिती REALPART_अभिव्यक्ती:
      स्थिती IMAGPART_अभिव्यक्ती:
	x = वृक्ष_OPERAND (x, 0);
	थांबा;

      स्थिती COMPOUND_LITERAL_अभिव्यक्ती:
	जर (C_DECL_REGISTER (COMPOUND_LITERAL_अभिव्यक्ती_DECL (x)))
	  {
	    जर (override_register)
	      DECL_REGISTER (COMPOUND_LITERAL_अभिव्यक्ती_DECL (x)) = 0;
	    अन्यथा
	      {
		error ("address of register compound literal requested");
		परत असत्य;
	      }
	  }
	वृक्ष_ADDRESSABLE (x) = 1;
	वृक्ष_ADDRESSABLE (COMPOUND_LITERAL_अभिव्यक्ती_DECL (x)) = 1;
	परत सत्य;

      स्थिती CONSTRUCTOR:
	वृक्ष_ADDRESSABLE (x) = 1;
	परत सत्य;

      स्थिती VAR_DECL:
      स्थिती CONST_DECL:
      स्थिती PARM_DECL:
      स्थिती RESULT_DECL:
	जर (C_DECL_REGISTER (x)
	    && DECL_NONLOCAL (x))
	  {
	    जर (वृक्ष_PUBLIC (x) || is_global_var (x))
	      {
		error
		  ("global register variable %qD used in nested function", x);
		परत असत्य;
	      }
	    pedwarn (आदान_location, 0, "register variable %qD used in nested function", x);
	  }
	अन्यथा जर (C_DECL_REGISTER (x))
	  {
	    जर (वृक्ष_PUBLIC (x) || is_global_var (x))
	      error ("address of global register variable %qD requested", x);
	    अन्यथा जर (override_register && !DECL_HARD_REGISTER (x))
	      {
		DECL_REGISTER (x) = 0;
		वृक्ष_ADDRESSABLE (x) = 1;
		mark_decl_used (x, सत्य);
		परत सत्य;
	      }
	    अन्यथा
	      error ("address of register variable %qD requested", x);
	    परत असत्य;
	  }

	/* FALLTHRU */
      स्थिती FUNCTION_DECL:
	वृक्ष_ADDRESSABLE (x) = 1;
	mark_decl_used (x, सत्य);
	/* FALLTHRU */
      पूर्वनिर्धारित:
	परत सत्य;
    }
}

/* Convert EXPR to TYPE, warning about conversion problems with
   constants.  SEMANTIC_TYPE is the type this conversion would use
   without excess precision. If SEMANTIC_TYPE is NULL, this function
   is equivalent to convert_and_check. This function is a wrapper that
   handles conversions that may be different than
   the usual ones because of excess precision.  */

स्थिर वृक्ष
ep_convert_and_check (location_t loc, वृक्ष type, वृक्ष अभिव्यक्ती,
		      वृक्ष semantic_type)
{
  जर (वृक्ष_TYPE (अभिव्यक्ती) == type)
    परत अभिव्यक्ती;

  /* For C11, integer conversions may have results with excess
     precision.  */
  जर (flag_isoc11 || !semantic_type)
    परत convert_and_check (loc, type, अभिव्यक्ती);

  जर (वृक्ष_CODE (वृक्ष_TYPE (अभिव्यक्ती)) == INTEGER_TYPE
      && वृक्ष_TYPE (अभिव्यक्ती) != semantic_type)
    {
      /* For integers, we need to check the real conversion, not
	 the conversion to the excess precision type.  */
      अभिव्यक्ती = convert_and_check (loc, semantic_type, अभिव्यक्ती);
    }
  /* Result type is the excess precision type, which should be
     large enough, so do not check.  */
  परत convert (type, अभिव्यक्ती);
}

/* If EXPR refers to a built-in declared without a prototype returns
   the actual type of the built-in and, if non-null, set *BLTIN to
   a pointer to the built-in.  Otherwise return the type of EXPR
   and clear *BLTIN if non-null.  */

स्थिर वृक्ष
type_or_builtin_type (वृक्ष अभिव्यक्ती, वृक्ष *bltin = रिक्त)
{
  वृक्ष dummy;
  जर (!bltin)
    bltin = &dummy;

  *bltin = NULL_वृक्ष;

  वृक्ष type = वृक्ष_TYPE (अभिव्यक्ती);
  जर (वृक्ष_CODE (अभिव्यक्ती) != ADDR_अभिव्यक्ती)
    परत type;

  वृक्ष oper = वृक्ष_OPERAND (अभिव्यक्ती, 0);
  जर (!DECL_P (oper)
      || वृक्ष_CODE (oper) != FUNCTION_DECL
      || !fndecl_built_in_p (oper, BUILT_IN_NORMAL))
    परत type;

  built_in_function code = DECL_FUNCTION_CODE (oper);
  जर (!C_DECL_BUILTIN_PROTOTYPE (oper))
    परत type;

  जर ((*bltin = builtin_decl_implicit (code)))
    type = c_build_pointer_type (वृक्ष_TYPE (*bltin));

  परत type;
}

/* Build and return a conditional expression IFEXP ? OP1 : OP2.  If
   IFEXP_BCP then the condition is a call to __builtin_constant_p, and
   if folded to an integer constant then the unselected half may
   contain arbitrary operations not normally permitted in constant
   expressions.  Set the location of the expression to LOC.  */

वृक्ष
build_conditional_अभिव्यक्ती (location_t colon_loc, वृक्ष ifexp, तार्किक ifexp_bcp,
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

  op1_int_operands = अभिव्यक्ती_INT_CONST_OPERANDS (orig_op1);
  जर (op1_int_operands)
    op1 = remove_c_maybe_const_अभिव्यक्ती (op1);
  op2_int_operands = अभिव्यक्ती_INT_CONST_OPERANDS (orig_op2);
  जर (op2_int_operands)
    op2 = remove_c_maybe_const_अभिव्यक्ती (op2);
  ifexp_int_operands = अभिव्यक्ती_INT_CONST_OPERANDS (ifexp);
  जर (ifexp_int_operands)
    ifexp = remove_c_maybe_const_अभिव्यक्ती (ifexp);

  /* Promote both alternatives.  */

  जर (वृक्ष_CODE (वृक्ष_TYPE (op1)) != VOID_TYPE)
    op1 = default_conversion (op1);
  जर (वृक्ष_CODE (वृक्ष_TYPE (op2)) != VOID_TYPE)
    op2 = default_conversion (op2);

  जर (वृक्ष_CODE (ifexp) == ERROR_MARK
      || वृक्ष_CODE (वृक्ष_TYPE (op1)) == ERROR_MARK
      || वृक्ष_CODE (वृक्ष_TYPE (op2)) == ERROR_MARK)
    परत error_mark_गाठ;

  वृक्ष bltin1 = NULL_वृक्ष;
  वृक्ष bltin2 = NULL_वृक्ष;
  type1 = type_or_builtin_type (op1, &bltin1);
  स्थिरांक गणना वृक्ष_code code1 = वृक्ष_CODE (type1);
  type2 = type_or_builtin_type (op2, &bltin2);
  स्थिरांक गणना वृक्ष_code code2 = वृक्ष_CODE (type2);

  जर (code1 == POINTER_TYPE && reject_gcc_builtin (op1))
    परत error_mark_गाठ;

  जर (code2 == POINTER_TYPE && reject_gcc_builtin (op2))
    परत error_mark_गाठ;

  /* C90 does not permit non-lvalue arrays in conditional expressions.
     In C99 they will be pointers by now.  */
  जर (code1 == ARRAY_TYPE || code2 == ARRAY_TYPE)
    {
      error_at (colon_loc, "non-lvalue array in conditional expression");
      परत error_mark_गाठ;
    }

  जर ((वृक्ष_CODE (op1) == EXCESS_PRECISION_अभिव्यक्ती
       || वृक्ष_CODE (op2) == EXCESS_PRECISION_अभिव्यक्ती)
      && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	  || code1 == COMPLEX_TYPE || code1 == BITINT_TYPE)
      && (code2 == INTEGER_TYPE || code2 == REAL_TYPE
	  || code2 == COMPLEX_TYPE || code2 == BITINT_TYPE))
    {
      semantic_result_type = c_common_type (type1, type2);
      जर (वृक्ष_CODE (op1) == EXCESS_PRECISION_अभिव्यक्ती)
	{
	  op1 = वृक्ष_OPERAND (op1, 0);
	  type1 = वृक्ष_TYPE (op1);
	  gcc_assert (वृक्ष_CODE (type1) == code1);
	}
      जर (वृक्ष_CODE (op2) == EXCESS_PRECISION_अभिव्यक्ती)
	{
	  op2 = वृक्ष_OPERAND (op2, 0);
	  type2 = वृक्ष_TYPE (op2);
	  gcc_assert (वृक्ष_CODE (type2) == code2);
	}
    }

  जर (warn_cxx_compat)
    {
      वृक्ष t1 = op1_original_type ? op1_original_type : वृक्ष_TYPE (orig_op1);
      वृक्ष t2 = op2_original_type ? op2_original_type : वृक्ष_TYPE (orig_op2);

      जर (वृक्ष_CODE (t1) == ENUMERAL_TYPE
	  && वृक्ष_CODE (t2) == ENUMERAL_TYPE
	  && TYPE_MAIN_VARIANT (t1) != TYPE_MAIN_VARIANT (t2))
	warning_at (colon_loc, OPT_Wc___compat,
		    "different enum types in conditional is "
		    "invalid in C++: %qT vs %qT", t1, t2);
    }

  जर (warn_zero_as_null_pointer_constant
      && c_inhibit_evaluation_warnings == 0)
    {
      जर ((code1 == POINTER_TYPE || code1 == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type2) && null_pointer_constant_p (orig_op2))
	warning_at (op2_loc, OPT_Wzero_as_null_pointer_constant,
		    "zero as null pointer constant");

      जर ((code2 == POINTER_TYPE || code2 == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type1) && null_pointer_constant_p (orig_op1))
	warning_at (op1_loc, OPT_Wzero_as_null_pointer_constant,
		    "zero as null pointer constant");
    }

  /* Quickly detect the usual case where op1 and op2 have the same type
     after promotion.  */
  जर (TYPE_MAIN_VARIANT (type1) == TYPE_MAIN_VARIANT (type2))
    {
      जर (type1 == type2)
	result_type = type1;
      अन्यथा
	result_type = TYPE_MAIN_VARIANT (type1);
    }
  अन्यथा जर ((code1 == INTEGER_TYPE || code1 == REAL_TYPE
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
      जर (flag_isoc11)
	{
	  वृक्ष eptype;
	  जर (ANY_INTEGRAL_TYPE_P (type1)
	      && (eptype = excess_precision_type (type2)) != NULL_वृक्ष)
	    {
	      eptype2 = eptype;
	      जर (!semantic_result_type)
		semantic_result_type = c_common_type (type1, type2);
	    }
	  अन्यथा जर (ANY_INTEGRAL_TYPE_P (type2)
		   && (eptype = excess_precision_type (type1)) != NULL_वृक्ष)
	    {
	      eptype1 = eptype;
	      जर (!semantic_result_type)
		semantic_result_type = c_common_type (type1, type2);
	    }
	}
      result_type = c_common_type (eptype1, eptype2);
      जर (result_type == error_mark_गाठ)
	परत error_mark_गाठ;
      do_warn_double_promotion (result_type, type1, type2,
				"implicit conversion from %qT to %qT to "
				"match other result of conditional",
				colon_loc);

      /* If -Wsign-compare, warn here if type1 and type2 have
	 different signedness.  We'll promote the signed to unsigned
	 and later code won't know it used to be different.
	 Do this check on the original types, so that explicit casts
	 will be considered, but default promotions won't.  */
      जर (c_inhibit_evaluation_warnings == 0)
	{
	  पूर्णांक unsigned_op1 = TYPE_UNSIGNED (वृक्ष_TYPE (orig_op1));
	  पूर्णांक unsigned_op2 = TYPE_UNSIGNED (वृक्ष_TYPE (orig_op2));

	  जर (unsigned_op1 ^ unsigned_op2)
	    {
	      /* Do not warn if the result type is signed, since the
		 signed type will only be chosen if it can represent
		 all the values of the unsigned type.  */
	      जर (!TYPE_UNSIGNED (result_type))
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
		    += (ifexp == truthvalue_false_गाठ);
		  op1 = c_fully_fold (op1, require_constant_मूल्य,
				      &op1_maybe_const);
		  c_inhibit_evaluation_warnings
		    -= (ifexp == truthvalue_false_गाठ);

		  c_inhibit_evaluation_warnings
		    += (ifexp == truthvalue_true_गाठ);
		  op2 = c_fully_fold (op2, require_constant_मूल्य,
				      &op2_maybe_const);
		  c_inhibit_evaluation_warnings
		    -= (ifexp == truthvalue_true_गाठ);

		  जर (warn_sign_compare)
		    {
		      जर ((unsigned_op2
			   && वृक्ष_अभिव्यक्ती_nonnegative_p (op1))
			  || (unsigned_op1
			      && वृक्ष_अभिव्यक्ती_nonnegative_p (op2)))
			/* OK */;
		      अन्यथा जर (unsigned_op2)
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
		  जर (!op1_maybe_const || वृक्ष_CODE (op1) != INTEGER_CST)
		    op1 = c_wrap_maybe_const (op1, !op1_maybe_const);
		  जर (!op2_maybe_const || वृक्ष_CODE (op2) != INTEGER_CST)
		    op2 = c_wrap_maybe_const (op2, !op2_maybe_const);
		}
	    }
	}
    }
  अन्यथा जर (code1 == VOID_TYPE || code2 == VOID_TYPE)
    {
      जर (code1 != VOID_TYPE || code2 != VOID_TYPE)
	pedwarn (colon_loc, OPT_Wpedantic,
		 "ISO C forbids conditional expr with only one void side");
      result_type = void_type_गाठ;
    }
  अन्यथा जर (code1 == POINTER_TYPE && code2 == POINTER_TYPE)
    {
      addr_space_t as1 = TYPE_ADDR_SPACE (वृक्ष_TYPE (type1));
      addr_space_t as2 = TYPE_ADDR_SPACE (वृक्ष_TYPE (type2));
      addr_space_t as_common;

      जर (comp_target_types (colon_loc, type1, type2))
	{
	  ifexp = save_अभिव्यक्ती (ifexp);
	  result_type = common_pointer_type (type1, type2, ifexp);
	}
      अन्यथा जर (null_pointer_constant_p (orig_op1))
	result_type = type2;
      अन्यथा जर (null_pointer_constant_p (orig_op2))
	result_type = type1;
      अन्यथा जर (!addr_space_superset (as1, as2, &as_common))
	{
	  error_at (colon_loc, "pointers to disjoint address spaces "
		    "used in conditional expression");
	  परत error_mark_गाठ;
	}
      अन्यथा जर ((VOID_TYPE_P (वृक्ष_TYPE (type1))
		&& !TYPE_ATOMIC (वृक्ष_TYPE (type1)))
	       || (VOID_TYPE_P (वृक्ष_TYPE (type2))
		   && !TYPE_ATOMIC (वृक्ष_TYPE (type2))))
	{
	  वृक्ष t1 = वृक्ष_TYPE (type1);
	  वृक्ष t2 = वृक्ष_TYPE (type2);
	  जर (!(VOID_TYPE_P (t1)
		&& !TYPE_ATOMIC (t1)))
	   {
	     /* roles are swapped */
	     t1 = t2;
	     t2 = वृक्ष_TYPE (type1);
	   }
	  वृक्ष t2_stripped = strip_array_types (t2);
	  जर ((वृक्ष_CODE (t2) == ARRAY_TYPE)
	      && (TYPE_QUALS (t2_stripped) & ~TYPE_QUALS (t1)))
	    {
	      जर (!flag_isoc23)
		warning_at (colon_loc, OPT_Wdiscarded_array_qualifiers,
			    "pointer to array loses qualifier "
			    "in conditional expression");
	      अन्यथा जर (warn_c11_c23_compat > 0)
		warning_at (colon_loc, OPT_Wc11_c23_compat,
			    "pointer to array loses qualifier "
			    "in conditional expression in ISO C before C23");
	    }
	  जर (वृक्ष_CODE (t2) == FUNCTION_TYPE)
	    pedwarn (colon_loc, OPT_Wpedantic,
		     "ISO C forbids conditional expr between "
		     "%<void *%> and function pointer");
	  /* for array, use qualifiers of element type */
	  जर (flag_isoc23)
	    t2 = t2_stripped;
	  result_type = c_build_pointer_type (qualify_type (t1, t2));
	}
      /* Objective-C pointer comparisons are a bit more lenient.  */
      अन्यथा जर (objc_have_common_type (type1, type2, -3, NULL_वृक्ष))
	result_type = objc_common_type (type1, type2);
      अन्यथा
	{
	  पूर्णांक qual = ENCODE_QUAL_ADDR_SPACE (as_common);
	  गणना diagnostics::kind kind = diagnostics::kind::permerror;
	  जर (!flag_isoc99)
	    /* This downgrade to a warning ensures that -std=gnu89
	       -pedantic-errors does not flag these mismatches between
	       builtins as errors (as diagnostics::kind::permerror would)
	       ISO C99 and later do not have implicit function declarations,
	       so the mismatch cannot occur naturally there.  */
	    kind = (bltin1 && bltin2
		    ? diagnostics::kind::warning
		    : diagnostics::kind::pedwarn);
	  जर (emit_diagnostic (kind, colon_loc, OPT_Wincompatible_pointer_types,
			       "pointer type mismatch "
			       "in conditional expression"))
	    {
	      inform (op1_loc, "first expression has type %qT", type1);
	      inform (op2_loc, "second expression has type %qT", type2);
	    }
	  result_type = c_build_pointer_type
			  (c_build_qualified_type (void_type_गाठ, qual));
	}
    }
  अन्यथा जर (code1 == POINTER_TYPE
	   && (code2 == INTEGER_TYPE || code2 == BITINT_TYPE))
    {
      जर (!null_pointer_constant_p (orig_op2))
	permerror_opt (colon_loc, OPT_Wint_conversion,
		       "pointer/integer type mismatch "
		       "in conditional expression");
      अन्यथा
	{
	  op2 = null_pointer_गाठ;
	}
      result_type = type1;
    }
  अन्यथा जर (code2 == POINTER_TYPE
	   && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
    {
      जर (!null_pointer_constant_p (orig_op1))
	permerror_opt (colon_loc, OPT_Wint_conversion,
		       "pointer/integer type mismatch "
		       "in conditional expression");
      अन्यथा
	{
	  op1 = null_pointer_गाठ;
	}
      result_type = type2;
    }
  /* 6.5.15: "if one is a null pointer constant (other than a pointer) or has
     type nullptr_t and the other is a pointer, the result type is the pointer
     type."  */
  अन्यथा जर (code1 == NULLPTR_TYPE && code2 == POINTER_TYPE)
    result_type = type2;
  अन्यथा जर (code1 == POINTER_TYPE && code2 == NULLPTR_TYPE)
    result_type = type1;
  अन्यथा जर (RECORD_OR_UNION_TYPE_P (type1) && RECORD_OR_UNION_TYPE_P (type2)
	   && comptypes (TYPE_MAIN_VARIANT (type1),
			 TYPE_MAIN_VARIANT (type2)))
    result_type = composite_type (TYPE_MAIN_VARIANT (type1),
				  TYPE_MAIN_VARIANT (type2));

  जर (!result_type)
    {
      जर (flag_cond_mismatch)
	result_type = void_type_गाठ;
      अन्यथा
	{
	  error_at (colon_loc, "type mismatch in conditional expression");
	  परत error_mark_गाठ;
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

  जर (ifexp_bcp && ifexp == truthvalue_true_गाठ)
    {
      op2_int_operands = सत्य;
      op1 = c_fully_fold (op1, require_constant_मूल्य, रिक्त);
    }
  जर (ifexp_bcp && ifexp == truthvalue_false_गाठ)
    {
      op1_int_operands = सत्य;
      op2 = c_fully_fold (op2, require_constant_मूल्य, रिक्त);
    }
  int_const = int_operands = (ifexp_int_operands
			      && op1_int_operands
			      && op2_int_operands);
  जर (int_operands)
    {
      int_const = ((ifexp == truthvalue_true_गाठ
		    && वृक्ष_CODE (orig_op1) == INTEGER_CST
		    && !वृक्ष_OVERFLOW (orig_op1))
		   || (ifexp == truthvalue_false_गाठ
		       && वृक्ष_CODE (orig_op2) == INTEGER_CST
		       && !वृक्ष_OVERFLOW (orig_op2)));
    }

  /* Need to convert condition operand into a vector mask.  */
  जर (VECTOR_TYPE_P (वृक्ष_TYPE (ifexp)))
    {
      वृक्ष vectype = वृक्ष_TYPE (ifexp);
      वृक्ष elem_type = वृक्ष_TYPE (vectype);
      वृक्ष zero = build_int_cst (elem_type, 0);
      वृक्ष zero_vec = build_vector_from_val (vectype, zero);
      वृक्ष cmp_type = truth_type_for (vectype);
      ifexp = build2 (NE_अभिव्यक्ती, cmp_type, ifexp, zero_vec);
    }

  जर (int_const || (ifexp_bcp && वृक्ष_CODE (ifexp) == INTEGER_CST))
    ret = fold_build3_loc (colon_loc, COND_अभिव्यक्ती, result_type, ifexp, op1, op2);
  अन्यथा
    {
      जर (int_operands)
	{
	  /* Use c_fully_fold here, since C_MAYBE_CONST_EXPR might be
	     nested inside of the expression.  */
	  op1 = c_fully_fold (op1, असत्य, रिक्त);
	  op2 = c_fully_fold (op2, असत्य, रिक्त);
	}
      ret = build3 (COND_अभिव्यक्ती, result_type, ifexp, op1, op2);
      जर (int_operands)
	ret = note_integer_operands (ret);
    }
  जर (semantic_result_type)
    ret = build1 (EXCESS_PRECISION_अभिव्यक्ती, semantic_result_type, ret);

  protected_set_अभिव्यक्ती_location (ret, colon_loc);

  /* If the OP1 and OP2 are the same and don't have side-effects,
     warn here, because the COND_EXPR will be turned into OP1.  */
  जर (warn_duplicated_branches
      && वृक्ष_CODE (ret) == COND_अभिव्यक्ती
      && (op1 == op2 || operand_equal_p (op1, op2, OEP_ADDRESS_OF_SAME_FIELD)))
    warning_at (अभिव्यक्ती_LOCATION (ret), OPT_Wduplicated_branches,
		"this condition has identical branches");

  परत ret;
}

/* EXPR is an expression, location LOC, whose result is discarded.
   Warn if it is a call to a nodiscard function (or a COMPOUND_EXPR
   whose right-hand operand is such a call, possibly recursively).  */

स्थिर शून्य
maybe_warn_nodiscard (location_t loc, वृक्ष अभिव्यक्ती)
{
  जर (VOID_TYPE_P (वृक्ष_TYPE (अभिव्यक्ती)))
    परत;
  पर्यंत (वृक्ष_CODE (अभिव्यक्ती) == COMPOUND_अभिव्यक्ती)
    {
      अभिव्यक्ती = वृक्ष_OPERAND (अभिव्यक्ती, 1);
      जर (अभिव्यक्ती_HAS_LOCATION (अभिव्यक्ती))
	loc = अभिव्यक्ती_LOCATION (अभिव्यक्ती);
    }
  जर (वृक्ष_CODE (अभिव्यक्ती) != CALL_अभिव्यक्ती)
    परत;
  वृक्ष fn = CALL_अभिव्यक्ती_FN (अभिव्यक्ती);
  जर (!fn)
    परत;
  वृक्ष attr;
  जर (वृक्ष_CODE (fn) == ADDR_अभिव्यक्ती
      && वृक्ष_CODE (वृक्ष_OPERAND (fn, 0)) == FUNCTION_DECL
      && (attr = lookup_attribute ("nodiscard",
				   DECL_ATTRIBUTES (वृक्ष_OPERAND (fn, 0)))))
    {
      fn = वृक्ष_OPERAND (fn, 0);
      वृक्ष args = वृक्ष_मूल्य (attr);
      जर (args)
	args = वृक्ष_मूल्य (args);
      auto_diagnostic_group d;
      auto_urlify_attributes sentinel;
      पूर्णांक warned;
      जर (args)
	warned = warning_at (loc, OPT_Wunused_result,
			     "ignoring return value of %qD, declared with "
			     "attribute %<nodiscard%>: %E", fn, args);
      अन्यथा
	warned = warning_at (loc, OPT_Wunused_result,
			     "ignoring return value of %qD, declared with "
			     "attribute %<nodiscard%>", fn);
      जर (warned)
	inform (DECL_SOURCE_LOCATION (fn), "declared here");
    }
  अन्यथा
    {
      वृक्ष rettype = वृक्ष_TYPE (वृक्ष_TYPE (वृक्ष_TYPE (fn)));
      attr = lookup_attribute ("nodiscard", TYPE_ATTRIBUTES (rettype));
      जर (!attr)
	परत;
      वृक्ष args = वृक्ष_मूल्य (attr);
      जर (args)
	args = वृक्ष_मूल्य (args);
      auto_diagnostic_group d;
      auto_urlify_attributes sentinel;
      पूर्णांक warned;
      जर (args)
	warned = warning_at (loc, OPT_Wunused_result,
			     "ignoring return value of type %qT, declared "
			     "with attribute %<nodiscard%>: %E",
			     rettype, args);
      अन्यथा
	warned = warning_at (loc, OPT_Wunused_result,
			     "ignoring return value of type %qT, declared "
			     "with attribute %<nodiscard%>", rettype);
      जर (warned)
	{
	  जर (वृक्ष_CODE (fn) == ADDR_अभिव्यक्ती)
	    {
	      fn = वृक्ष_OPERAND (fn, 0);
	      जर (वृक्ष_CODE (fn) == FUNCTION_DECL)
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
build_compound_अभिव्यक्ती (location_t loc, वृक्ष expr1, वृक्ष expr2)
{
  तार्किक expr1_int_operands, expr2_int_operands;
  वृक्ष eptype = NULL_वृक्ष;
  वृक्ष ret;

  expr1_int_operands = अभिव्यक्ती_INT_CONST_OPERANDS (expr1);
  जर (expr1_int_operands)
    expr1 = remove_c_maybe_const_अभिव्यक्ती (expr1);
  expr2_int_operands = अभिव्यक्ती_INT_CONST_OPERANDS (expr2);
  जर (expr2_int_operands)
    expr2 = remove_c_maybe_const_अभिव्यक्ती (expr2);

  जर (वृक्ष_CODE (expr1) == EXCESS_PRECISION_अभिव्यक्ती)
    expr1 = वृक्ष_OPERAND (expr1, 0);
  जर (वृक्ष_CODE (expr2) == EXCESS_PRECISION_अभिव्यक्ती)
    {
      eptype = वृक्ष_TYPE (expr2);
      expr2 = वृक्ष_OPERAND (expr2, 0);
    }

  जर (!वृक्ष_SIDE_EFFECTS (expr1))
    {
      /* The left-hand operand of a comma expression is like an expression
	 statement: with -Wunused, we should warn if it doesn't have
	 any side-effects, unless it was explicitly cast to (void).  */
      जर (warn_unused_मूल्य)
	{
	  जर (VOID_TYPE_P (वृक्ष_TYPE (expr1))
	      && CONVERT_अभिव्यक्ती_P (expr1))
	    ; /* (void) a, b */
	  अन्यथा जर (VOID_TYPE_P (वृक्ष_TYPE (expr1))
		   && वृक्ष_CODE (expr1) == COMPOUND_अभिव्यक्ती
		   && CONVERT_अभिव्यक्ती_P (वृक्ष_OPERAND (expr1, 1)))
	    ; /* (void) a, (void) b, c */
	  अन्यथा
	    warning_at (loc, OPT_Wunused_मूल्य,
			"left-hand operand of comma expression has no effect");
	}
    }
  अन्यथा जर (वृक्ष_CODE (expr1) == COMPOUND_अभिव्यक्ती
	   && warn_unused_मूल्य)
    {
      वृक्ष r = expr1;
      location_t cloc = loc;
      पर्यंत (वृक्ष_CODE (r) == COMPOUND_अभिव्यक्ती)
        {
	  जर (अभिव्यक्ती_HAS_LOCATION (r))
	    cloc = अभिव्यक्ती_LOCATION (r);
	  r = वृक्ष_OPERAND (r, 1);
	}
      जर (!वृक्ष_SIDE_EFFECTS (r)
	  && !VOID_TYPE_P (वृक्ष_TYPE (r))
	  && !CONVERT_अभिव्यक्ती_P (r))
	warning_at (cloc, OPT_Wunused_मूल्य,
	            "right-hand operand of comma expression has no effect");
    }

  /* With -Wunused, we should also warn if the left-hand operand does have
     side-effects, but computes a value which is not used.  For example, in
     `foo() + bar(), baz()' the result of the `+' operator is not used,
     so we should issue a warning.  */
  अन्यथा जर (warn_unused_मूल्य)
    warn_if_unused_मूल्य (expr1, loc);

  maybe_warn_nodiscard (loc, expr1);

  जर (expr2 == error_mark_गाठ)
    परत error_mark_गाठ;

  ret = build2 (COMPOUND_अभिव्यक्ती, वृक्ष_TYPE (expr2), expr1, expr2);

  जर (flag_isoc99
      && expr1_int_operands
      && expr2_int_operands)
    ret = note_integer_operands (ret);

  जर (eptype)
    ret = build1 (EXCESS_PRECISION_अभिव्यक्ती, eptype, ret);

  protected_set_अभिव्यक्ती_location (ret, loc);
  परत ret;
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
  पूर्णांक added = 0;
  पूर्णांक discarded = 0;
  तार्किक is_const;

  /* Check that the qualifiers on IN_TYPE are a superset of the
     qualifiers of IN_OTYPE.  The outermost level of POINTER_TYPE
     nodes is uninteresting and we stop as soon as we hit a
     non-POINTER_TYPE node on either type.  */
  करा
    {
      in_otype = वृक्ष_TYPE (in_otype);
      in_type = वृक्ष_TYPE (in_type);

      /* GNU C allows cv-qualified function types.  'const' means the
	 function is very pure, 'volatile' means it can't return.  We
	 need to warn when such qualifiers are added, not when they're
	 taken away.  */
      जर (वृक्ष_CODE (in_otype) == FUNCTION_TYPE
	  && वृक्ष_CODE (in_type) == FUNCTION_TYPE)
	added |= (TYPE_QUALS_NO_ADDR_SPACE (in_type)
		  & ~TYPE_QUALS_NO_ADDR_SPACE (in_otype));
      अन्यथा
	discarded |= (TYPE_QUALS_NO_ADDR_SPACE (in_otype)
		      & ~TYPE_QUALS_NO_ADDR_SPACE (in_type));
    }
  पर्यंत (वृक्ष_CODE (in_type) == POINTER_TYPE
	 && वृक्ष_CODE (in_otype) == POINTER_TYPE);

  जर (added)
    warning_at (loc, OPT_Wcast_qual,
		"cast adds %q#v qualifier to function type", added);

  जर (discarded)
    /* There are qualifiers present in IN_OTYPE that are not present
       in IN_TYPE.  */
    warning_at (loc, OPT_Wcast_qual,
		"cast discards %qv qualifier from pointer target type",
		discarded);

  जर (added || discarded)
    परत;

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

  जर (TYPE_MAIN_VARIANT (in_type) != TYPE_MAIN_VARIANT (in_otype))
    परत;
  जर (वृक्ष_CODE (वृक्ष_TYPE (type)) != POINTER_TYPE)
    परत;

  in_type = type;
  in_otype = otype;
  is_const = TYPE_READONLY (वृक्ष_TYPE (in_type));
  करा
    {
      in_type = वृक्ष_TYPE (in_type);
      in_otype = वृक्ष_TYPE (in_otype);
      जर ((TYPE_QUALS (in_type) &~ TYPE_QUALS (in_otype)) != 0
	  && !is_const)
	{
	  warning_at (loc, OPT_Wcast_qual,
		      "to be safe all intermediate pointers in cast from "
                      "%qT to %qT must be %<const%> qualified",
		      otype, type);
	  थांबा;
	}
      जर (is_const)
	is_const = TYPE_READONLY (in_type);
    }
  पर्यंत (वृक्ष_CODE (in_type) == POINTER_TYPE);
}

/* Heuristic check if two parameter types can be considered ABI-equivalent.  */

स्थिर तार्किक
c_safe_arg_type_equiv_p (वृक्ष t1, वृक्ष t2)
{
  जर (error_operand_p (t1) || error_operand_p (t2))
    परत सत्य;

  t1 = TYPE_MAIN_VARIANT (t1);
  t2 = TYPE_MAIN_VARIANT (t2);

  जर (वृक्ष_CODE (t1) == POINTER_TYPE
      && वृक्ष_CODE (t2) == POINTER_TYPE)
    परत सत्य;

  /* Only the precision of the parameter matters.  This check should
     make sure that the callee does not see undefined values in argument
     registers.  */
  जर (INTEGRAL_TYPE_P (t1)
      && INTEGRAL_TYPE_P (t2)
      && TYPE_PRECISION (t1) == TYPE_PRECISION (t2))
    परत सत्य;

  परत comptypes (t1, t2);
}

/* Check if a type cast between two function types can be considered safe.  */

स्थिर तार्किक
c_safe_function_type_cast_p (वृक्ष t1, वृक्ष t2)
{
  जर (वृक्ष_TYPE (t1) == void_type_गाठ &&
      TYPE_ARG_TYPES (t1) == void_list_गाठ)
    परत सत्य;

  जर (वृक्ष_TYPE (t2) == void_type_गाठ &&
      TYPE_ARG_TYPES (t2) == void_list_गाठ)
    परत सत्य;

  जर (!c_safe_arg_type_equiv_p (वृक्ष_TYPE (t1), वृक्ष_TYPE (t2)))
    परत असत्य;

  साठी (t1 = TYPE_ARG_TYPES (t1), t2 = TYPE_ARG_TYPES (t2);
       t1 && t2;
       t1 = वृक्ष_CHAIN (t1), t2 = वृक्ष_CHAIN (t2))
    जर (!c_safe_arg_type_equiv_p (वृक्ष_मूल्य (t1), वृक्ष_मूल्य (t2)))
      परत असत्य;

  परत सत्य;
}

/* Build an expression representing a cast to type TYPE of expression EXPR.
   LOC is the location of the cast-- typically the open paren of the cast.  */

वृक्ष
build_c_cast (location_t loc, वृक्ष type, वृक्ष अभिव्यक्ती)
{
  वृक्ष मूल्य;

  तार्किक int_operands = अभिव्यक्ती_INT_CONST_OPERANDS (अभिव्यक्ती);

  जर (वृक्ष_CODE (अभिव्यक्ती) == EXCESS_PRECISION_अभिव्यक्ती)
    अभिव्यक्ती = वृक्ष_OPERAND (अभिव्यक्ती, 0);

  मूल्य = अभिव्यक्ती;
  जर (int_operands)
    मूल्य = remove_c_maybe_const_अभिव्यक्ती (मूल्य);

  जर (type == error_mark_गाठ || अभिव्यक्ती == error_mark_गाठ)
    परत error_mark_गाठ;

  /* The ObjC front-end uses TYPE_MAIN_VARIANT to tie together types differing
     only in <protocol> qualifications.  But when constructing cast expressions,
     the protocols do matter and must be kept around.  */
  जर (objc_is_object_ptr (type) && objc_is_object_ptr (वृक्ष_TYPE (अभिव्यक्ती)))
    परत build1 (NOP_अभिव्यक्ती, type, अभिव्यक्ती);

  type = TYPE_MAIN_VARIANT (type);

  जर (वृक्ष_CODE (type) == ARRAY_TYPE)
    {
      error_at (loc, "cast specifies array type");
      परत error_mark_गाठ;
    }

  जर (वृक्ष_CODE (type) == FUNCTION_TYPE)
    {
      error_at (loc, "cast specifies function type");
      परत error_mark_गाठ;
    }

  जर (!VOID_TYPE_P (type))
    {
      मूल्य = require_complete_type (loc, मूल्य);
      जर (मूल्य == error_mark_गाठ)
	परत error_mark_गाठ;
    }

  जर (type == TYPE_MAIN_VARIANT (वृक्ष_TYPE (मूल्य)))
    {
      जर (RECORD_OR_UNION_TYPE_P (type)
	  && pedwarn (loc, OPT_Wpedantic,
		      "ISO C forbids casting nonscalar to the same type"))
	      ;
      अन्यथा जर (warn_useless_cast && c_inhibit_evaluation_warnings == 0)
	warning_at (loc, OPT_Wuseless_cast,
		    "useless cast to type %qT", type);

      /* Convert to remove any qualifiers from VALUE's type.  */
      मूल्य = convert (type, मूल्य);
    }
  अन्यथा जर (वृक्ष_CODE (type) == UNION_TYPE)
    {
      वृक्ष field;

      साठी (field = TYPE_FIELDS (type); field; field = DECL_CHAIN (field))
	जर (वृक्ष_TYPE (field) != error_mark_गाठ
	    && comptypes (TYPE_MAIN_VARIANT (वृक्ष_TYPE (field)),
			  TYPE_MAIN_VARIANT (वृक्ष_TYPE (मूल्य))))
	  थांबा;

      जर (field)
	{
	  वृक्ष t;
	  तार्किक maybe_const = सत्य;

	  pedwarn (loc, OPT_Wpedantic, "ISO C forbids casts to union type");
	  t = c_fully_fold (मूल्य, असत्य, &maybe_const);
	  t = build_constructor_single (type, field, t);
	  जर (!maybe_const)
	    t = c_wrap_maybe_const (t, सत्य);
	  t = digest_init (loc, field, type, t,
			   NULL_वृक्ष, असत्य, असत्य, असत्य, सत्य, असत्य, असत्य);
	  वृक्ष_CONSTANT (t) = वृक्ष_CONSTANT (मूल्य);
	  परत t;
	}
      error_at (loc, "cast to union type from type not present in union");
      परत error_mark_गाठ;
    }
  अन्यथा
    {
      वृक्ष otype, ovalue;

      जर (type == void_type_गाठ)
	{
	  वृक्ष t = build1 (CONVERT_अभिव्यक्ती, type, मूल्य);
	  SET_अभिव्यक्ती_LOCATION (t, loc);
	  परत t;
	}

      otype = वृक्ष_TYPE (मूल्य);

      /* Optionally warn about potentially worrisome casts.  */
      जर (warn_cast_qual
	  && वृक्ष_CODE (type) == POINTER_TYPE
	  && वृक्ष_CODE (otype) == POINTER_TYPE)
	handle_warn_cast_qual (loc, type, otype);

      /* Warn about conversions between pointers to disjoint
	 address spaces.  */
      जर (वृक्ष_CODE (type) == POINTER_TYPE
	  && वृक्ष_CODE (otype) == POINTER_TYPE
	  && !null_pointer_constant_p (मूल्य))
	{
	  addr_space_t as_to = TYPE_ADDR_SPACE (वृक्ष_TYPE (type));
	  addr_space_t as_from = TYPE_ADDR_SPACE (वृक्ष_TYPE (otype));
	  addr_space_t as_common;

	  जर (!addr_space_superset (as_to, as_from, &as_common))
	    {
	      जर (ADDR_SPACE_GENERIC_P (as_from))
		warning_at (loc, 0, "cast to %qs address space pointer "
			    "from disjoint generic address space pointer",
			    c_addr_space_name (as_to));

	      अन्यथा जर (ADDR_SPACE_GENERIC_P (as_to))
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
	  जर (warn_alloc_size && वृक्ष_CODE (मूल्य) == CALL_अभिव्यक्ती)
	    जर (वृक्ष fndecl = get_callee_fndecl (मूल्य))
	      जर (DECL_IS_MALLOC (fndecl))
		{
		  वृक्ष attrs = TYPE_ATTRIBUTES (वृक्ष_TYPE (fndecl));
		  वृक्ष alloc_size = lookup_attribute ("alloc_size", attrs);
		  जर (alloc_size)
		    warn_for_alloc_size (loc, वृक्ष_TYPE (type), मूल्य,
					 alloc_size);
		}
	}

      /* Warn about possible alignment problems.  */
      जर ((STRICT_ALIGNMENT || warn_cast_align == 2)
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

      जर ((वृक्ष_CODE (type) == INTEGER_TYPE
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

      जर ((वृक्ष_CODE (मूल्य) == CALL_अभिव्यक्ती
	   && !is_access_with_size_p (मूल्य))
	  && वृक्ष_CODE (type) != वृक्ष_CODE (otype))
	warning_at (loc, OPT_Wbad_function_cast,
		    "cast from function call of type %qT "
		    "to non-matching type %qT", otype, type);

      जर (वृक्ष_CODE (type) == POINTER_TYPE
	  && (वृक्ष_CODE (otype) == INTEGER_TYPE
	      || वृक्ष_CODE (otype) == BITINT_TYPE)
	  && TYPE_PRECISION (type) != TYPE_PRECISION (otype)
	  /* Don't warn about converting any constant.  */
	  && !वृक्ष_CONSTANT (मूल्य))
	warning_at (loc,
		    OPT_Wint_to_pointer_cast, "cast to pointer from integer "
		    "of different size");

      जर (warn_strict_aliasing <= 2)
        strict_aliasing_warning (अभिव्यक्ती_LOCATION (मूल्य), type, अभिव्यक्ती);

      /* If pedantic, warn for conversions between function and object
	 pointer types, except for converting a null pointer constant
	 to function pointer type.  */
      जर (pedantic
	  && वृक्ष_CODE (type) == POINTER_TYPE
	  && वृक्ष_CODE (otype) == POINTER_TYPE
	  && वृक्ष_CODE (वृक्ष_TYPE (otype)) == FUNCTION_TYPE
	  && वृक्ष_CODE (वृक्ष_TYPE (type)) != FUNCTION_TYPE)
	pedwarn (loc, OPT_Wpedantic, "ISO C forbids "
		 "conversion of function pointer to object pointer type");

      जर (pedantic
	  && वृक्ष_CODE (type) == POINTER_TYPE
	  && वृक्ष_CODE (otype) == POINTER_TYPE
	  && वृक्ष_CODE (वृक्ष_TYPE (type)) == FUNCTION_TYPE
	  && वृक्ष_CODE (वृक्ष_TYPE (otype)) != FUNCTION_TYPE
	  && !null_pointer_constant_p (मूल्य))
	pedwarn (loc, OPT_Wpedantic, "ISO C forbids "
		 "conversion of object pointer to function pointer type");

      जर (वृक्ष_CODE (type) == POINTER_TYPE
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
      जर (int_operands
	  && वृक्ष_CODE (मूल्य) != INTEGER_CST
	  && (वृक्ष_CODE (type) == BOOLEAN_TYPE
	      || (वृक्ष_CODE (type) == ENUMERAL_TYPE
		  && ENUM_UNDERLYING_TYPE (type) != NULL_वृक्ष
		  && वृक्ष_CODE (ENUM_UNDERLYING_TYPE (type)) == BOOLEAN_TYPE)))
	मूल्य = note_integer_operands (मूल्य);
      मूल्य = convert (type, मूल्य);

      /* Ignore any integer overflow caused by the cast.  */
      जर (वृक्ष_CODE (मूल्य) == INTEGER_CST && !FLOAT_TYPE_P (otype))
	{
	  जर (वृक्ष_OVERFLOW_P (ovalue))
	    {
	      जर (!वृक्ष_OVERFLOW (मूल्य))
		{
		  /* Avoid clobbering a shared constant.  */
		  मूल्य = copy_गाठ (मूल्य);
		  वृक्ष_OVERFLOW (मूल्य) = वृक्ष_OVERFLOW (ovalue);
		}
	    }
	  अन्यथा जर (वृक्ष_OVERFLOW (मूल्य))
	    /* Reset VALUE's overflow flags, ensuring constant sharing.  */
	    मूल्य = wide_int_to_वृक्ष (वृक्ष_TYPE (मूल्य), wi::to_wide (मूल्य));
	}
    }

  /* Don't let a cast be an lvalue.  */
  जर (lvalue_p (मूल्य)
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
  जर (वृक्ष_CODE (मूल्य) == REAL_CST
      || वृक्ष_CODE (मूल्य) == COMPLEX_CST
      || (वृक्ष_CODE (मूल्य) == INTEGER_CST
	  && !((वृक्ष_CODE (अभिव्यक्ती) == INTEGER_CST
		&& INTEGRAL_TYPE_P (वृक्ष_TYPE (अभिव्यक्ती)))
	       || वृक्ष_CODE (अभिव्यक्ती) == REAL_CST
	       || वृक्ष_CODE (अभिव्यक्ती) == COMPLEX_CST)))
      मूल्य = build1 (NOP_अभिव्यक्ती, type, मूल्य);

  /* If the expression has integer operands and so can occur in an
     unevaluated part of an integer constant expression, ensure the
     return value reflects this.  */
  जर (int_operands
      && INTEGRAL_TYPE_P (type)
      && मूल्य != error_mark_गाठ
      && !अभिव्यक्ती_INT_CONST_OPERANDS (मूल्य))
    मूल्य = note_integer_operands (मूल्य);

  protected_set_अभिव्यक्ती_location (मूल्य, loc);
  परत मूल्य;
}

/* Interpret a cast of expression EXPR to type TYPE.  LOC is the
   location of the open paren of the cast, or the position of the cast
   expr.  */
वृक्ष
c_cast_अभिव्यक्ती (location_t loc, संरचना c_type_name *type_name, वृक्ष अभिव्यक्ती)
{
  वृक्ष type;
  वृक्ष type_अभिव्यक्ती = NULL_वृक्ष;
  तार्किक type_अभिव्यक्ती_const = सत्य;
  वृक्ष ret;
  पूर्णांक saved_wsp = warn_strict_prototypes;

  /* This avoids warnings about unprototyped casts on
     integers.  E.g. "#define SIG_DFL (void(*)())0".  */
  जर (वृक्ष_CODE (अभिव्यक्ती) == INTEGER_CST)
    warn_strict_prototypes = 0;
  type = groktypename (type_name, &type_अभिव्यक्ती, &type_अभिव्यक्ती_const);
  warn_strict_prototypes = saved_wsp;

  जर (वृक्ष_CODE (अभिव्यक्ती) == ADDR_अभिव्यक्ती && !VOID_TYPE_P (type)
      && reject_gcc_builtin (अभिव्यक्ती))
    परत error_mark_गाठ;

  ret = build_c_cast (loc, type, अभिव्यक्ती);
  जर (ret == error_mark_गाठ)
    परत error_mark_गाठ;

  जर (type_अभिव्यक्ती)
    {
      तार्किक inner_अभिव्यक्ती_const = सत्य;
      ret = c_fully_fold (ret, require_constant_मूल्य, &inner_अभिव्यक्ती_const);
      ret = build2 (C_MAYBE_CONST_अभिव्यक्ती, वृक्ष_TYPE (ret), type_अभिव्यक्ती, ret);
      C_MAYBE_CONST_अभिव्यक्ती_NON_CONST (ret) = !(type_अभिव्यक्ती_const
					     && inner_अभिव्यक्ती_const);
      SET_अभिव्यक्ती_LOCATION (ret, loc);
    }

  जर (!अभिव्यक्ती_HAS_LOCATION (ret))
    protected_set_अभिव्यक्ती_location (ret, loc);

  /* C++ does not permits types to be defined in a cast, but it
     allows references to incomplete types.  */
  जर (warn_cxx_compat && type_name->specs->typespec_kind == ctsk_tagdef)
    warning_at (loc, OPT_Wc___compat,
		"defining a type in a cast is invalid in C++");

  परत ret;
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
build_modify_अभिव्यक्ती (location_t location, वृक्ष lhs, वृक्ष lhs_origtype,
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
  जर (वृक्ष_CODE (lhs) == ERROR_MARK || वृक्ष_CODE (rhs) == ERROR_MARK)
    परत error_mark_गाठ;

  /* Ensure an error for assigning a non-lvalue array to an array in
     C90.  */
  जर (वृक्ष_CODE (lhstype) == ARRAY_TYPE)
    {
      error_at (location, "assignment to expression with array type");
      परत error_mark_गाठ;
    }

  /* For ObjC properties, defer this check.  */
  जर (!objc_is_property_ref (lhs) && !lvalue_or_else (location, lhs, lv_assign))
    परत error_mark_गाठ;

  is_atomic_op = really_atomic_lvalue (lhs);

  newrhs = rhs;

  जर (वृक्ष_CODE (lhs) == C_MAYBE_CONST_अभिव्यक्ती)
    {
      वृक्ष inner = build_modify_अभिव्यक्ती (location, C_MAYBE_CONST_अभिव्यक्ती_अभिव्यक्ती (lhs),
				      lhs_origtype, modifycode, rhs_loc, rhs,
				      rhs_origtype);
      जर (inner == error_mark_गाठ)
	परत error_mark_गाठ;
      result = build2 (C_MAYBE_CONST_अभिव्यक्ती, वृक्ष_TYPE (inner),
		       C_MAYBE_CONST_अभिव्यक्ती_PRE (lhs), inner);
      gcc_assert (!C_MAYBE_CONST_अभिव्यक्ती_INT_OPERANDS (lhs));
      C_MAYBE_CONST_अभिव्यक्ती_NON_CONST (result) = 1;
      protected_set_अभिव्यक्ती_location (result, location);
      परत result;
    }

  /* If a binary op has been requested, combine the old LHS value with the RHS
     producing the value we should actually store into the LHS.  */

  जर (modifycode != NOP_अभिव्यक्ती)
    {
      lhs = c_fully_fold (lhs, असत्य, रिक्त, सत्य);
      lhs = stabilize_reference (lhs);

      /* Construct the RHS for any non-atomic compound assignment. */
      जर (!is_atomic_op)
        {
	  /* If in LHS op= RHS the RHS has side-effects, ensure they
	     are preevaluated before the rest of the assignment expression's
	     side-effects, because RHS could contain e.g. function calls
	     that modify LHS.  */
	  जर (वृक्ष_SIDE_EFFECTS (rhs))
	    {
	      जर (वृक्ष_CODE (rhs) == EXCESS_PRECISION_अभिव्यक्ती)
		newrhs = save_अभिव्यक्ती (वृक्ष_OPERAND (rhs, 0));
	      अन्यथा
		newrhs = save_अभिव्यक्ती (rhs);
	      rhseval = newrhs;
	      जर (वृक्ष_CODE (rhs) == EXCESS_PRECISION_अभिव्यक्ती)
		newrhs = build1 (EXCESS_PRECISION_अभिव्यक्ती, वृक्ष_TYPE (rhs),
				 newrhs);
	    }
	  तार्किक clear_decl_read = असत्य;
	  जर ((VAR_P (lhs) || वृक्ष_CODE (lhs) == PARM_DECL)
	      && !DECL_READ_P (lhs)
	      && (VAR_P (lhs) ? warn_unused_but_set_variable
			      : warn_unused_but_set_parameter) > 2)
	    {
	      mark_exp_read (newrhs);
	      जर (!DECL_READ_P (lhs))
		clear_decl_read = सत्य;
	    }

	  newrhs = build_द्विमान_op (location, modifycode,
				    convert_lvalue_to_rvalue (location, lhs,
							      सत्य, सत्य),
				    newrhs, सत्य);
	  जर (clear_decl_read)
	    DECL_READ_P (lhs) = 0;

	  /* The original type of the right hand side is no longer
	     meaningful.  */
	  rhs_origtype = NULL_वृक्ष;
	}
    }

  जर (c_dialect_objc ())
    {
      /* Check if we are modifying an Objective-C property reference;
	 if so, we need to generate setter calls.  */
      जर (वृक्ष_CODE (newrhs) == EXCESS_PRECISION_अभिव्यक्ती)
	result = objc_maybe_build_modify_अभिव्यक्ती (lhs, वृक्ष_OPERAND (newrhs, 0));
      अन्यथा
	result = objc_maybe_build_modify_अभिव्यक्ती (lhs, newrhs);
      जर (result)
	जा return_result;

      /* Else, do the check that we postponed for Objective-C.  */
      जर (!lvalue_or_else (location, lhs, lv_assign))
	परत error_mark_गाठ;
    }

  /* Give an error for storing in something that is 'const'.  */

  जर (TYPE_READONLY (lhstype)
      || (RECORD_OR_UNION_TYPE_P (lhstype)
	  && C_TYPE_FIELDS_READONLY (lhstype)))
    {
      readonly_error (location, lhs, lv_assign);
      परत error_mark_गाठ;
    }
  अन्यथा जर (वृक्ष_READONLY (lhs))
    readonly_warning (lhs, lv_assign);

  /* If storing into a structure or union member,
     it has probably been given type `int'.
     Compute the type that would go with
     the actual amount of storage the member occupies.  */

  जर (वृक्ष_CODE (lhs) == COMPONENT_REF
      && (वृक्ष_CODE (lhstype) == INTEGER_TYPE
	  || वृक्ष_CODE (lhstype) == BOOLEAN_TYPE
	  || SCALAR_FLOAT_TYPE_P (lhstype)
	  || वृक्ष_CODE (lhstype) == ENUMERAL_TYPE))
    lhstype = वृक्ष_TYPE (get_unwidened (lhs, 0));

  /* If storing in a field that is in actuality a short or narrower than one,
     we must store in the field in its actual type.  */

  जर (lhstype != वृक्ष_TYPE (lhs))
    {
      lhs = copy_गाठ (lhs);
      वृक्ष_TYPE (lhs) = lhstype;
    }

  /* Issue -Wc++-compat warnings about an assignment to an enum type
     when LHS does not have its original type.  This happens for,
     e.g., an enum bitfield in a struct.  */
  जर (warn_cxx_compat
      && lhs_origtype != NULL_वृक्ष
      && lhs_origtype != lhstype
      && वृक्ष_CODE (lhs_origtype) == ENUMERAL_TYPE)
    {
      वृक्ष checktype = (rhs_origtype != NULL_वृक्ष
			? rhs_origtype
			: वृक्ष_TYPE (rhs));
      जर (checktype != error_mark_गाठ
	  && (TYPE_MAIN_VARIANT (checktype) != TYPE_MAIN_VARIANT (lhs_origtype)
	      || (is_atomic_op && modifycode != NOP_अभिव्यक्ती)))
	warning_at (location, OPT_Wc___compat,
		    "enum conversion in assignment is invalid in C++");
    }

  /* Remove qualifiers.  */
  lhstype = c_build_qualified_type (lhstype, TYPE_UNQUALIFIED);
  olhstype = c_build_qualified_type (olhstype, TYPE_UNQUALIFIED);

  /* Convert new value to destination type.  Fold it first, then
     restore any excess precision information, for the sake of
     conversion warnings.  */

  जर (!(is_atomic_op && modifycode != NOP_अभिव्यक्ती))
    {
      वृक्ष rhs_semantic_type = NULL_वृक्ष;
      जर (!c_in_omp_for)
	{
	  जर (वृक्ष_CODE (newrhs) == EXCESS_PRECISION_अभिव्यक्ती)
	    {
	      rhs_semantic_type = वृक्ष_TYPE (newrhs);
	      newrhs = वृक्ष_OPERAND (newrhs, 0);
	    }
	  npc = null_pointer_constant_p (newrhs);
	  newrhs = c_fully_fold (newrhs, असत्य, रिक्त);
	  जर (rhs_semantic_type)
	    newrhs = build1 (EXCESS_PRECISION_अभिव्यक्ती, rhs_semantic_type, newrhs);
	}
      अन्यथा
	npc = null_pointer_constant_p (newrhs);
      newrhs = convert_for_assignment (location, rhs_loc, lhstype, newrhs,
				       rhs_origtype, ic_assign, npc,
				       NULL_वृक्ष, NULL_वृक्ष, 0);
      जर (वृक्ष_CODE (newrhs) == ERROR_MARK)
	परत error_mark_गाठ;
    }

  /* Emit ObjC write barrier, if necessary.  */
  जर (c_dialect_objc () && flag_objc_gc)
    {
      result = objc_generate_write_barrier (lhs, modifycode, newrhs);
      जर (result)
	{
	  protected_set_अभिव्यक्ती_location (result, location);
	  जा return_result;
	}
    }

  /* Scan operands.  */

  जर (is_atomic_op)
    result = build_atomic_assign (location, lhs, modifycode, newrhs, असत्य);
  अन्यथा
    {
      result = build2 (MODIFY_अभिव्यक्ती, lhstype, lhs, newrhs);
      वृक्ष_SIDE_EFFECTS (result) = 1;
      protected_set_अभिव्यक्ती_location (result, location);
    }

  /* If we got the LHS in a different type for storing in,
     convert the result back to the nominal type of LHS
     so that the value we return always has the same type
     as the LHS argument.  */

  जर (olhstype == वृक्ष_TYPE (result))
    जा return_result;

  result = convert_for_assignment (location, rhs_loc, olhstype, result,
				   rhs_origtype, ic_assign, असत्य, NULL_वृक्ष,
				   NULL_वृक्ष, 0);
  protected_set_अभिव्यक्ती_location (result, location);

return_result:
  जर (rhseval)
    result = build2 (COMPOUND_अभिव्यक्ती, वृक्ष_TYPE (result), rhseval, result);
  परत result;
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
  साठी (field = TYPE_FIELDS (struct_type);
       field != NULL_वृक्ष;
       field = वृक्ष_CHAIN (field))
    {
      वृक्ष fieldtype = remove_qualifiers (वृक्ष_TYPE (field));
      जर (DECL_NAME (field) == रिक्त
	  && comptypes (type, fieldtype))
	{
	  जर (found)
	    परत असत्य;
	  found = सत्य;
	}
      अन्यथा जर (DECL_NAME (field) == रिक्त
	       && RECORD_OR_UNION_TYPE_P (वृक्ष_TYPE (field))
	       && find_anonymous_field_with_type (वृक्ष_TYPE (field), type))
	{
	  जर (found)
	    परत असत्य;
	  found = सत्य;
	}
    }
  परत found;
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
  साठी (field = TYPE_FIELDS (rhs_struct_type);
       field != NULL_वृक्ष;
       field = वृक्ष_CHAIN (field))
    {
      जर (DECL_NAME (field) != NULL_वृक्ष
	  || !RECORD_OR_UNION_TYPE_P (वृक्ष_TYPE (field)))
	सुरूठेवा;
      वृक्ष fieldtype = remove_qualifiers (वृक्ष_TYPE (field));
      जर (comptypes (lhs_main_type, fieldtype))
	{
	  जर (found_field != NULL_वृक्ष)
	    परत NULL_वृक्ष;
	  found_field = field;
	}
      अन्यथा जर (find_anonymous_field_with_type (वृक्ष_TYPE (field),
					       lhs_main_type))
	{
	  जर (found_field != NULL_वृक्ष)
	    परत NULL_वृक्ष;
	  found_field = field;
	  found_sub_field = सत्य;
	}
    }

  जर (found_field == NULL_वृक्ष)
    परत NULL_वृक्ष;

  ret = fold_build3_loc (location, COMPONENT_REF, वृक्ष_TYPE (found_field),
			 build_fold_indirect_ref (rhs), found_field,
			 NULL_वृक्ष);
  ret = build_fold_addr_अभिव्यक्ती_loc (location, ret);

  जर (found_sub_field)
    {
      ret = convert_to_anonymous_field (location, type, ret);
      gcc_assert (ret != NULL_वृक्ष);
    }

  परत ret;
}

/* Issue an error message for a bad initializer component.
   GMSGID identifies the message.
   The component name is taken from the spelling stack.  */

स्थिर शून्य ATTRIBUTE_GCC_DIAG (2,0)
error_init (location_t loc, स्थिरांक अक्षर *gmsgid, ...)
{
  अक्षर *ofwhat;

  auto_diagnostic_group d;

  /* The gmsgid may be a format string with %< and %>. */
  बहु_सूची ap;
  बहु_शुरू (ap, gmsgid);
  तार्किक warned = emit_diagnostic_valist (diagnostics::kind::error,
					loc, -1, gmsgid, &ap);
  बहु_पूर्ण (ap);

  ofwhat = print_spelling ((अक्षर *) alloca (spelling_length () + 1));
  जर (*ofwhat && warned)
    inform (loc, "(near initialization for %qs)", ofwhat);
}

/* Used to implement pedwarn_init and permerror_init.  */

स्थिर तार्किक ATTRIBUTE_GCC_DIAG (3,0)
pedwarn_permerror_init (location_t loc, पूर्णांक opt, स्थिरांक अक्षर *gmsgid,
			बहु_सूची *ap, गणना diagnostics::kind kind)
{
  /* Use the location where a macro was expanded rather than where
     it was defined to make sure macros defined in system headers
     but used incorrectly elsewhere are diagnosed.  */
  location_t exploc = expansion_point_location_if_in_system_header (loc);
  auto_diagnostic_group d;
  तार्किक warned = emit_diagnostic_valist (kind, exploc, opt, gmsgid, ap);
  जर (warned)
    {
      अक्षर *ofwhat = print_spelling ((अक्षर *) alloca (spelling_length () + 1));
      जर (*ofwhat)
	inform (exploc, "(near initialization for %qs)", ofwhat);
    }
  परत warned;
}

/* Issue a pedantic warning for a bad initializer component.  OPT is
   the option OPT_* (from options.h) controlling this warning or 0 if
   it is unconditionally given.  GMSGID identifies the message.  The
   component name is taken from the spelling stack.  */

स्थिर तार्किक ATTRIBUTE_GCC_DIAG (3,0)
pedwarn_init (location_t loc, पूर्णांक opt, स्थिरांक अक्षर *gmsgid, ...)
{
  बहु_सूची ap;
  बहु_शुरू (ap, gmsgid);
  तार्किक warned = pedwarn_permerror_init (loc, opt, gmsgid, &ap,
					diagnostics::kind::pedwarn);
  बहु_पूर्ण (ap);
  परत warned;
}

/* Like pedwarn_init, but issue a permerror.  */

स्थिर तार्किक ATTRIBUTE_GCC_DIAG (3,0)
permerror_init (location_t loc, पूर्णांक opt, स्थिरांक अक्षर *gmsgid, ...)
{
  बहु_सूची ap;
  बहु_शुरू (ap, gmsgid);
  तार्किक warned = pedwarn_permerror_init (loc, opt, gmsgid, &ap,
					diagnostics::kind::permerror);
  बहु_पूर्ण (ap);
  परत warned;
}

/* Issue a warning for a bad initializer component.

   OPT is the OPT_W* value corresponding to the warning option that
   controls this warning.  GMSGID identifies the message.  The
   component name is taken from the spelling stack.  */

स्थिर शून्य
warning_init (location_t loc, पूर्णांक opt, स्थिरांक अक्षर *gmsgid)
{
  अक्षर *ofwhat;
  तार्किक warned;

  auto_diagnostic_group d;

  /* Use the location where a macro was expanded rather than where
     it was defined to make sure macros defined in system headers
     but used incorrectly elsewhere are diagnosed.  */
  location_t exploc = expansion_point_location_if_in_system_header (loc);

  /* The gmsgid may be a format string with %< and %>. */
  warned = warning_at (exploc, opt, gmsgid);
  जर (warned)
    {
      ofwhat = print_spelling ((अक्षर *) alloca (spelling_length () + 1));
      जर (*ofwhat)
	inform (exploc, "(near initialization for %qs)", ofwhat);
    }
}

/* If TYPE is an array type and EXPR is a parenthesized string
   constant, warn if pedantic that EXPR is being used to initialize an
   object of type TYPE.  */

शून्य
maybe_warn_string_init (location_t loc, वृक्ष type, संरचना c_अभिव्यक्ती अभिव्यक्ती)
{
  जर (pedantic
      && वृक्ष_CODE (type) == ARRAY_TYPE
      && वृक्ष_CODE (अभिव्यक्ती.मूल्य) == STRING_CST
      && अभिव्यक्ती.original_code != STRING_CST)
    pedwarn_init (loc, OPT_Wpedantic,
		  "array initialized from parenthesized string constant");
}

/* Attempt to locate the parameter with the given index within FNDECL,
   returning DECL_SOURCE_LOCATION (FNDECL) if it can't be found.  */

स्थिर location_t
get_fndecl_argument_location (वृक्ष fndecl, पूर्णांक argnum)
{
  पूर्णांक i;
  वृक्ष param;

  /* Locate param by index within DECL_ARGUMENTS (fndecl).  */
  साठी (i = 0, param = DECL_ARGUMENTS (fndecl);
       i < argnum && param;
       i++, param = वृक्ष_CHAIN (param))
    ;

  /* If something went wrong (e.g. if we have a builtin and thus no arguments),
     return DECL_SOURCE_LOCATION (FNDECL).  */
  जर (param == रिक्त)
    परत DECL_SOURCE_LOCATION (fndecl);

  परत DECL_SOURCE_LOCATION (param);
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
inform_for_arg (वृक्ष fundecl, location_t ploc, पूर्णांक parmnum,
		वृक्ष expected_type, वृक्ष actual_type)
{
  location_t loc;
  जर (fundecl && !DECL_IS_UNDECLARED_BUILTIN (fundecl))
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
maybe_warn_builtin_no_proto_arg (location_t loc, वृक्ष fundecl, पूर्णांक parmnum,
				 वृक्ष parmtype, वृक्ष argtype)
{
  वृक्ष_code parmcode = वृक्ष_CODE (parmtype);
  वृक्ष_code argcode = वृक्ष_CODE (argtype);
  वृक्ष promoted = c_type_promotes_to (argtype);

  /* Avoid warning for enum arguments that promote to an integer type
     of the same size/mode.  */
  जर (parmcode == INTEGER_TYPE
      && argcode == ENUMERAL_TYPE
      && TYPE_MODE (parmtype) == TYPE_MODE (argtype))
    परत;

  जर ((parmcode == argcode
       || (parmcode == INTEGER_TYPE
	   && argcode == ENUMERAL_TYPE))
      && TYPE_MAIN_VARIANT (parmtype) == TYPE_MAIN_VARIANT (promoted))
    परत;

  /* This diagnoses even signed/unsigned mismatches.  Those might be
     safe in many cases but GCC may emit suboptimal code for them so
     warning on those cases drives efficiency improvements.  */
  जर (warning_at (loc, OPT_Wbuiltin_declaration_mismatch,
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
  pp_element_quoted_decl (वृक्ष decl, स्थिरांक अक्षर *highlight_color)
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
    pretty_printer *स्थिरांक pp = &ctxt.m_pp;
    pp->set_padding (pp_none);
    जर (DECL_NAME (m_decl))
      pp_identifier (pp, lang_hooks.decl_printable_name (m_decl, 2));
    अन्यथा
      pp_string (pp, _("({anonymous})"));
  }

खाजगी:
  वृक्ष m_decl;
  स्थिरांक अक्षर *m_highlight_color;
};

/* If TYPE is from a typedef, issue a note showing the location
   to the user.
   Use HIGHLIGHT_COLOR as the highlight color.  */

स्थिर शून्य
maybe_inform_typedef_location (वृक्ष type, स्थिरांक अक्षर *highlight_color)
{
  जर (!typedef_variant_p (type))
    परत;

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
convert_for_assignment (location_t location, location_t अभिव्यक्ती_loc, वृक्ष type,
			वृक्ष rhs, वृक्ष origtype, गणना impl_conv errtype,
			तार्किक null_pointer_constant, वृक्ष fundecl,
			वृक्ष function, पूर्णांक parmnum, पूर्णांक warnopt /* = 0 */)
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

  जर (errtype == ic_argpass)
    {
      वृक्ष selector;
      /* Change pointer to function to the function itself for
	 diagnostics.  */
      जर (वृक्ष_CODE (function) == ADDR_अभिव्यक्ती
	  && वृक्ष_CODE (वृक्ष_OPERAND (function, 0)) == FUNCTION_DECL)
	function = वृक्ष_OPERAND (function, 0);

      /* Handle an ObjC selector specially for diagnostics.  */
      selector = objc_message_selector ();
      rname = function;
      जर (selector && parmnum > 2)
	{
	  rname = selector;
	  parmnum -= 2;
	}
    }

  /* This macro is used to emit diagnostics to ensure that all format
     strings are complete sentences, visible to gettext and checked at
     compile time.  */
#define PEDWARN_FOR_ASSIGNMENT(LOCATION, PLOC, OPT, AR, AS, IN, RE)	 \
  करा {                                                                   \
    निवड (errtype)                                                     \
      {                                                                  \
      स्थिती ic_argpass:                                                   \
	{								\
	  auto_diagnostic_group d;						\
	  जर (pedwarn (PLOC, OPT, AR, parmnum, rname))		\
	    inform_for_arg (fundecl, (PLOC), parmnum, type, rhstype); \
	}								\
        थांबा;                                                           \
      स्थिती ic_assign:                                                    \
        pedwarn (LOCATION, OPT, AS);                                     \
        थांबा;                                                           \
      स्थिती ic_init:                                                      \
      स्थिती ic_init_const:                                                \
        pedwarn_init (LOCATION, OPT, IN);                                \
        थांबा;                                                           \
      स्थिती ic_return:                                                    \
        pedwarn (LOCATION, OPT, RE);					 \
        थांबा;                                                           \
      पूर्वनिर्धारित:                                                           \
        gcc_unreachable ();                                              \
      }                                                                  \
  } पर्यंत (0)

  /* This macro is used to emit diagnostics to ensure that all format
     strings are complete sentences, visible to gettext and checked at
     compile time.  It can be called with 'pedwarn' or 'warning_at'.  */
#define WARNING_FOR_QUALIFIERS(PEDWARN, LOCATION, PLOC, OPT, AR, AS, IN, RE, QUALS) \
  करा {                                                                   \
    निवड (errtype)                                                     \
      {                                                                  \
      स्थिती ic_argpass:                                                   \
	{								 \
	  auto_diagnostic_group d;					 \
	  जर (PEDWARN) {						 \
	    जर (pedwarn (PLOC, OPT, AR, parmnum, rname, QUALS))          \
	      inform_for_arg (fundecl, (PLOC), parmnum, type, rhstype);  \
	  } अन्यथा {							 \
	    जर (warning_at (PLOC, OPT, AR, parmnum, rname, QUALS))	 \
	      inform_for_arg (fundecl, (PLOC), parmnum, type, rhstype);  \
	  }								 \
	}								 \
        थांबा;                                                           \
      स्थिती ic_assign:                                                    \
	जर (PEDWARN)							 \
	  pedwarn (LOCATION, OPT, AS, QUALS);                            \
	अन्यथा								 \
	  warning_at (LOCATION, OPT, AS, QUALS);                         \
        थांबा;                                                           \
      स्थिती ic_init:                                                      \
      स्थिती ic_init_const:                                                \
	जर (PEDWARN)							 \
	  pedwarn (LOCATION, OPT, IN, QUALS);                            \
	अन्यथा								 \
	  warning_at (LOCATION, OPT, IN, QUALS);                         \
        थांबा;                                                           \
      स्थिती ic_return:                                                    \
	जर (PEDWARN)							 \
	  pedwarn (LOCATION, OPT, RE, QUALS);                            \
	अन्यथा								 \
	  warning_at (LOCATION, OPT, RE, QUALS);                         \
        थांबा;                                                           \
      पूर्वनिर्धारित:                                                           \
        gcc_unreachable ();                                              \
      }                                                                  \
  } पर्यंत (0)

  /* This macro is used to emit diagnostics to ensure that all format
     strings are complete sentences, visible to gettext and checked at
     compile time.  It is the same as PEDWARN_FOR_ASSIGNMENT but with an
     extra parameter to enumerate qualifiers.  */
#define PEDWARN_FOR_QUALIFIERS(LOCATION, PLOC, OPT, AR, AS, IN, RE, QUALS) \
   WARNING_FOR_QUALIFIERS (सत्य, LOCATION, PLOC, OPT, AR, AS, IN, RE, QUALS)


  जर (वृक्ष_CODE (rhs) == EXCESS_PRECISION_अभिव्यक्ती)
    rhs = वृक्ष_OPERAND (rhs, 0);

  rhstype = वृक्ष_TYPE (rhs);
  coder = वृक्ष_CODE (rhstype);

  जर (coder == ERROR_MARK)
    परत error_mark_गाठ;

  जर (c_dialect_objc ())
    {
      पूर्णांक parmno;

      निवड (errtype)
	{
	स्थिती ic_return:
	  parmno = 0;
	  थांबा;

	स्थिती ic_assign:
	  parmno = -1;
	  थांबा;

	स्थिती ic_init:
	स्थिती ic_init_const:
	  parmno = -2;
	  थांबा;

	पूर्वनिर्धारित:
	  parmno = parmnum;
	  थांबा;
	}

      objc_ok = objc_compare_types (type, rhstype, parmno, rname);
    }

  जर (warn_cxx_compat)
    {
      वृक्ष checktype = origtype != NULL_वृक्ष ? origtype : rhstype;
      जर (checktype != error_mark_गाठ
	  && वृक्ष_CODE (type) == ENUMERAL_TYPE
	  && TYPE_MAIN_VARIANT (checktype) != TYPE_MAIN_VARIANT (type))
	निवड (errtype)
	  {
	  स्थिती ic_argpass:
	    जर (pedwarn (अभिव्यक्ती_loc, OPT_Wc___compat, "enum conversion when "
			 "passing argument %d of %qE is invalid in C++",
			 parmnum, rname))
	      inform ((fundecl && !DECL_IS_UNDECLARED_BUILTIN (fundecl))
		      ? DECL_SOURCE_LOCATION (fundecl) : अभिव्यक्ती_loc,
		      "expected %qT but argument is of type %qT",
		      type, rhstype);
	    थांबा;
	  स्थिती ic_assign:
	    pedwarn (location, OPT_Wc___compat, "enum conversion from %qT to "
		     "%qT in assignment is invalid in C++", rhstype, type);
	    थांबा;
	  स्थिती ic_init:
	  स्थिती ic_init_const:
	    pedwarn_init (location, OPT_Wc___compat, "enum conversion from "
			  "%qT to %qT in initialization is invalid in C++",
			  rhstype, type);
	    थांबा;
	  स्थिती ic_return:
	    pedwarn (location, OPT_Wc___compat, "enum conversion from %qT to "
		     "%qT in return is invalid in C++", rhstype, type);
	    थांबा;
	  पूर्वनिर्धारित:
	    gcc_unreachable ();
	  }
    }

  जर (warn_enum_conversion)
    {
      वृक्ष checktype = origtype != NULL_वृक्ष ? origtype : rhstype;
      जर (checktype != error_mark_गाठ
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

  जर (TYPE_MAIN_VARIANT (type) == TYPE_MAIN_VARIANT (rhstype))
    {
      warn_for_address_of_packed_member (type, orig_rhs);
      जर (type != rhstype)
	/* Convert RHS to TYPE in order to not lose TYPE in diagnostics.  */
	rhs = convert (type, rhs);
      परत rhs;
    }

  जर (coder == VOID_TYPE)
    {
      /* Except for passing an argument to an unprototyped function,
	 this is a constraint violation.  When passing an argument to
	 an unprototyped function, it is compile-time undefined;
	 making it a constraint in that case was rejected in
	 DR#252.  */
      स्थिरांक अक्षर संदेश[] = "void value not ignored as it ought to be";
      जर (warnopt)
	warning_at (location, warnopt, संदेश);
      अन्यथा
	error_at (location, संदेश);
      परत error_mark_गाठ;
    }
  rhs = require_complete_type (location, rhs);
  जर (rhs == error_mark_गाठ)
    परत error_mark_गाठ;

  जर (coder == POINTER_TYPE && reject_gcc_builtin (rhs))
    परत error_mark_गाठ;

  /* A non-reference type can convert to a reference.  This handles
     va_start, va_copy and possibly port built-ins.  */
  जर (codel == REFERENCE_TYPE && coder != REFERENCE_TYPE)
    {
      जर (!lvalue_p (rhs))
	{
	  स्थिरांक अक्षर संदेश[] = "cannot pass rvalue to reference parameter";
	  जर (warnopt)
	    warning_at (location, warnopt, संदेश);
	  अन्यथा
	    error_at (location, संदेश);
	  परत error_mark_गाठ;
	}
      जर (!c_mark_addressable (rhs))
	परत error_mark_गाठ;
      rhs = build1 (ADDR_अभिव्यक्ती, c_build_pointer_type (वृक्ष_TYPE (rhs)), rhs);
      SET_अभिव्यक्ती_LOCATION (rhs, location);

      rhs = convert_for_assignment (location, अभिव्यक्ती_loc,
				    c_build_pointer_type (वृक्ष_TYPE (type)),
				    rhs, origtype, errtype,
				    null_pointer_constant, fundecl, function,
				    parmnum, warnopt);
      जर (rhs == error_mark_गाठ)
	परत error_mark_गाठ;

      rhs = build1 (NOP_अभिव्यक्ती, type, rhs);
      SET_अभिव्यक्ती_LOCATION (rhs, location);
      परत rhs;
    }
  /* Some types can interconvert without explicit casts.  */
  अन्यथा जर (codel == VECTOR_TYPE && coder == VECTOR_TYPE
	   && vector_types_convertible_p (type, वृक्ष_TYPE (rhs), सत्य))
    परत convert (type, rhs);
  /* Arithmetic types all interconvert, and enum is treated like int.  */
  अन्यथा जर ((codel == INTEGER_TYPE || codel == REAL_TYPE
	    || codel == FIXED_POINT_TYPE
	    || codel == ENUMERAL_TYPE || codel == COMPLEX_TYPE
	    || codel == BOOLEAN_TYPE || codel == BITINT_TYPE)
	   && (coder == INTEGER_TYPE || coder == REAL_TYPE
	       || coder == FIXED_POINT_TYPE
	       || coder == ENUMERAL_TYPE || coder == COMPLEX_TYPE
	       || coder == BOOLEAN_TYPE || coder == BITINT_TYPE))
    {
      जर (warnopt && errtype == ic_argpass)
	maybe_warn_builtin_no_proto_arg (अभिव्यक्ती_loc, fundecl, parmnum, type,
					 rhstype);

      तार्किक save = in_late_द्विमान_op;
      जर (C_BOOLEAN_TYPE_P (type) || codel == COMPLEX_TYPE
	  || (coder == REAL_TYPE
	      && (codel == INTEGER_TYPE || codel == ENUMERAL_TYPE)
	      && sanitize_flags_p (SANITIZE_FLOAT_CAST)))
	in_late_द्विमान_op = सत्य;
      वृक्ष ret = convert_and_check (अभिव्यक्ती_loc != UNKNOWN_LOCATION
				    ? अभिव्यक्ती_loc : location, type, orig_rhs,
				    errtype == ic_init_const);
      in_late_द्विमान_op = save;
      परत ret;
    }

  /* Aggregates in different TUs might need conversion.  */
  जर ((codel == RECORD_TYPE || codel == UNION_TYPE)
      && codel == coder
      && comptypes (TYPE_MAIN_VARIANT (type), TYPE_MAIN_VARIANT (rhstype)))
    परत convert_and_check (अभिव्यक्ती_loc != UNKNOWN_LOCATION
			      ? अभिव्यक्ती_loc : location, type, rhs);

  /* Conversion to a transparent union or record from its member types.
     This applies only to function arguments.  */
  जर (((codel == UNION_TYPE || codel == RECORD_TYPE)
      && TYPE_TRANSPARENT_AGGR (type))
      && errtype == ic_argpass)
    {
      वृक्ष memb, marginal_memb = NULL_वृक्ष;

      साठी (memb = TYPE_FIELDS (type); memb ; memb = DECL_CHAIN (memb))
	{
	  वृक्ष memb_type = वृक्ष_TYPE (memb);

	  जर (comptypes (TYPE_MAIN_VARIANT (memb_type),
			 TYPE_MAIN_VARIANT (rhstype)))
	    थांबा;

	  जर (वृक्ष_CODE (memb_type) != POINTER_TYPE)
	    सुरूठेवा;

	  जर (coder == POINTER_TYPE)
	    {
	      वृक्ष ttl = वृक्ष_TYPE (memb_type);
	      वृक्ष ttr = वृक्ष_TYPE (rhstype);

	      /* Any non-function converts to a [const][volatile] void *
		 and vice versa; otherwise, targets must be the same.
		 Meanwhile, the lhs target must have all the qualifiers of
		 the rhs.  */
	      जर ((VOID_TYPE_P (ttl) && !TYPE_ATOMIC (ttl))
		  || (VOID_TYPE_P (ttr) && !TYPE_ATOMIC (ttr))
		  || comp_target_types (location, memb_type, rhstype))
		{
		  पूर्णांक lquals = TYPE_QUALS (ttl) & ~TYPE_QUAL_ATOMIC;
		  पूर्णांक rquals = TYPE_QUALS (ttr) & ~TYPE_QUAL_ATOMIC;
		  /* If this type won't generate any warnings, use it.  */
		  जर (lquals == rquals
		      || ((वृक्ष_CODE (ttr) == FUNCTION_TYPE
			   && वृक्ष_CODE (ttl) == FUNCTION_TYPE)
			  ? ((lquals | rquals) == rquals)
			  : ((lquals | rquals) == lquals)))
		    थांबा;

		  /* Keep looking for a better type, but remember this one.  */
		  जर (!marginal_memb)
		    marginal_memb = memb;
		}
	    }

	  /* Can convert integer zero to any pointer type.  */
	  जर (null_pointer_constant)
	    {
	      rhs = null_pointer_गाठ;
	      थांबा;
	    }
	}

      जर (memb || marginal_memb)
	{
	  जर (!memb)
	    {
	      /* We have only a marginally acceptable member type;
		 it needs a warning.  */
	      वृक्ष ttl = वृक्ष_TYPE (वृक्ष_TYPE (marginal_memb));
	      वृक्ष ttr = वृक्ष_TYPE (rhstype);

	      /* Const and volatile mean something different for function
		 types, so the usual warnings are not appropriate.  */
	      जर (वृक्ष_CODE (ttr) == FUNCTION_TYPE
		  && वृक्ष_CODE (ttl) == FUNCTION_TYPE)
		{
		  /* Because const and volatile on functions are
		     restrictions that say the function will not do
		     certain things, it is okay to use a const or volatile
		     function where an ordinary one is wanted, but not
		     vice-versa.  */
		  जर (TYPE_QUALS_NO_ADDR_SPACE (ttl)
		      & ~TYPE_QUALS_NO_ADDR_SPACE (ttr))
		    PEDWARN_FOR_QUALIFIERS (location, अभिव्यक्ती_loc,
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
	      अन्यथा जर (TYPE_QUALS_NO_ADDR_SPACE (ttr)
		       & ~TYPE_QUALS_NO_ADDR_SPACE (ttl))
		PEDWARN_FOR_QUALIFIERS (location, अभिव्यक्ती_loc,
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

	  जर (!fundecl || !DECL_IN_SYSTEM_HEADER (fundecl))
	    pedwarn (location, OPT_Wpedantic,
		     "ISO C prohibits argument conversion to union type");

	  rhs = fold_convert_loc (location, वृक्ष_TYPE (memb), rhs);
	  परत build_constructor_single (type, memb, rhs);
	}
    }

  /* Conversions among pointers */
  अन्यथा जर ((codel == POINTER_TYPE || codel == REFERENCE_TYPE)
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
      जर (flag_plan9_extensions
	  && RECORD_OR_UNION_TYPE_P (mvl)
	  && RECORD_OR_UNION_TYPE_P (mvr)
	  && mvl != mvr)
	{
	  वृक्ष new_rhs = convert_to_anonymous_field (location, type, rhs);
	  जर (new_rhs != NULL_वृक्ष)
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
      जर (VOID_TYPE_P (ttr) && rhs != null_pointer_गाठ && !VOID_TYPE_P (ttl))
	warning_at (errtype == ic_argpass ? अभिव्यक्ती_loc : location,
		    OPT_Wc___compat,
		    "request for implicit conversion "
		    "from %qT to %qT not permitted in C++", rhstype, type);

      /* Warn of new allocations that are not big enough for the target
	 type.  */
      जर (warn_alloc_size && वृक्ष_CODE (rhs) == CALL_अभिव्यक्ती)
	जर (वृक्ष fndecl = get_callee_fndecl (rhs))
	  जर (DECL_IS_MALLOC (fndecl))
	    {
	      वृक्ष attrs = TYPE_ATTRIBUTES (वृक्ष_TYPE (fndecl));
	      वृक्ष alloc_size = lookup_attribute ("alloc_size", attrs);
	      जर (alloc_size)
		warn_for_alloc_size (location, ttl, rhs, alloc_size);
	    }

      /* See if the pointers point to incompatible address spaces.  */
      asl = TYPE_ADDR_SPACE (ttl);
      asr = TYPE_ADDR_SPACE (ttr);
      जर (!null_pointer_constant_p (rhs)
	  && asr != asl && !targetm.addr_space.subset_p (asr, asl))
	{
	  auto_diagnostic_group d;
	  तार्किक diagnosed = सत्य;
	  निवड (errtype)
	    {
	    स्थिती ic_argpass:
	      {
		स्थिरांक अक्षर संदेश[] = G_("passing argument %d of %qE from "
				      "pointer to non-enclosed address space");
		जर (warnopt)
		  diagnosed
		    = warning_at (अभिव्यक्ती_loc, warnopt, संदेश, parmnum, rname);
		अन्यथा
		  error_at (अभिव्यक्ती_loc, संदेश, parmnum, rname);
	      थांबा;
	      }
	    स्थिती ic_assign:
	      {
		स्थिरांक अक्षर संदेश[] = G_("assignment from pointer to "
				      "non-enclosed address space");
		जर (warnopt)
		  diagnosed = warning_at (location, warnopt, संदेश);
		अन्यथा
		  error_at (location, संदेश);
		थांबा;
	      }
	    स्थिती ic_init:
	    स्थिती ic_init_const:
	      {
		स्थिरांक अक्षर संदेश[] = G_("initialization from pointer to "
				      "non-enclosed address space");
		जर (warnopt)
		  diagnosed = warning_at (location, warnopt, संदेश);
		अन्यथा
		  error_at (location, संदेश);
		थांबा;
	      }
	    स्थिती ic_return:
	      {
		स्थिरांक अक्षर संदेश[] = G_("return from pointer to "
				      "non-enclosed address space");
		जर (warnopt)
		  diagnosed = warning_at (location, warnopt, संदेश);
		अन्यथा
		  error_at (location, संदेश);
		थांबा;
	      }
	    पूर्वनिर्धारित:
	      gcc_unreachable ();
	    }
	  जर (diagnosed)
	    {
	      जर (errtype == ic_argpass)
		inform_for_arg (fundecl, अभिव्यक्ती_loc, parmnum, type, rhstype);
	      अन्यथा
		inform (location, "expected %qT but pointer is of type %qT",
			type, rhstype);
	    }
	  परत error_mark_गाठ;
	}

      /* Check if the right-hand side has a format attribute but the
	 left-hand side doesn't.  */
      जर (warn_suggest_attribute_format
	  && check_missing_format_attribute (type, rhstype))
	{
	  निवड (errtype)
	  {
	  स्थिती ic_argpass:
	    warning_at (अभिव्यक्ती_loc, OPT_Wsuggest_attribute_format,
			"argument %d of %qE might be "
			"a candidate for a format attribute",
			parmnum, rname);
	    थांबा;
	  स्थिती ic_assign:
	    warning_at (location, OPT_Wsuggest_attribute_format,
			"assignment left-hand side might be "
			"a candidate for a format attribute");
	    थांबा;
	  स्थिती ic_init:
	  स्थिती ic_init_const:
	    warning_at (location, OPT_Wsuggest_attribute_format,
			"initialization left-hand side might be "
			"a candidate for a format attribute");
	    थांबा;
	  स्थिती ic_return:
	    warning_at (location, OPT_Wsuggest_attribute_format,
			"return type might be "
			"a candidate for a format attribute");
	    थांबा;
	  पूर्वनिर्धारित:
	    gcc_unreachable ();
	  }
	}

      /* See if the pointers point to incompatible scalar storage orders.  */
      जर (warn_scalar_storage_order
	  && !null_pointer_constant_p (rhs)
	  && (AGGREGATE_TYPE_P (ttl) && TYPE_REVERSE_STORAGE_ORDER (ttl))
	     != (AGGREGATE_TYPE_P (ttr) && TYPE_REVERSE_STORAGE_ORDER (ttr)))
	{
	  वृक्ष t;

	  निवड (errtype)
	  {
	  स्थिती ic_argpass:
	    /* Do not warn for built-in functions, for example memcpy, since we
	       control how they behave and they can be useful in this area.  */
	    जर (वृक्ष_CODE (rname) != FUNCTION_DECL
		|| !fndecl_built_in_p (rname))
	      warning_at (location, OPT_Wscalar_storage_order,
			  "passing argument %d of %qE from incompatible "
			  "scalar storage order", parmnum, rname);
	    थांबा;
	  स्थिती ic_assign:
	    /* Do not warn if the RHS is a call to a function that returns a
	       pointer that is not an alias.  */
	    जर (वृक्ष_CODE (rhs) != CALL_अभिव्यक्ती
		|| (t = get_callee_fndecl (rhs)) == NULL_वृक्ष
		|| !DECL_IS_MALLOC (t))
	      warning_at (location, OPT_Wscalar_storage_order,
			  "assignment to %qT from pointer type %qT with "
			  "incompatible scalar storage order", type, rhstype);
	    थांबा;
	  स्थिती ic_init:
	  स्थिती ic_init_const:
	    /* Likewise.  */
	    जर (वृक्ष_CODE (rhs) != CALL_अभिव्यक्ती
		|| (t = get_callee_fndecl (rhs)) == NULL_वृक्ष
		|| !DECL_IS_MALLOC (t))
	      warning_at (location, OPT_Wscalar_storage_order,
			  "initialization of %qT from pointer type %qT with "
			  "incompatible scalar storage order", type, rhstype);
	    थांबा;
	  स्थिती ic_return:
	    warning_at (location, OPT_Wscalar_storage_order,
			"returning %qT from pointer type with incompatible "
			"scalar storage order %qT", rhstype, type);
	    थांबा;
	  पूर्वनिर्धारित:
	    gcc_unreachable ();
	  }
	}

      /* Any non-function converts to a [const][volatile] void *
	 and vice versa; otherwise, targets must be the same.
	 Meanwhile, the lhs target must have all the qualifiers of the rhs.  */
      जर ((VOID_TYPE_P (ttl) && !TYPE_ATOMIC (ttl))
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
	  जर (वृक्ष_CODE (ttr) == ARRAY_TYPE)
	    {
	      ttr = strip_array_types (ttr);
	      ttl = strip_array_types (ttl);

	      जर (TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttr)
		  & ~TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttl))
		WARNING_FOR_QUALIFIERS (flag_isoc23,
					location, अभिव्यक्ती_loc,
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
          अन्यथा जर (pedantic
	      && ((VOID_TYPE_P (ttl) && वृक्ष_CODE (ttr) == FUNCTION_TYPE)
		  ||
		  (VOID_TYPE_P (ttr)
		   && !null_pointer_constant
		   && वृक्ष_CODE (ttl) == FUNCTION_TYPE)))
	    PEDWARN_FOR_ASSIGNMENT (location, अभिव्यक्ती_loc, OPT_Wpedantic,
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
	  अन्यथा जर (वृक्ष_CODE (ttr) != FUNCTION_TYPE
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
	      जर (warn_quals || (warn_quals_ped && pedantic && !flag_isoc23))
		PEDWARN_FOR_QUALIFIERS (location, अभिव्यक्ती_loc,
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
	      अन्यथा जर (warn_quals_ped)
		pedwarn_c11 (location, OPT_Wc11_c23_compat,
			     "array with qualifier on the element is not qualified before C23");

	      /* If this is not a case of ignoring a mismatch in signedness,
		 no warning.  */
	      अन्यथा जर (VOID_TYPE_P (ttl) || VOID_TYPE_P (ttr)
		       || target_cmp)
		;
	      /* If there is a mismatch, do warn.  */
	      अन्यथा जर (warn_pointer_sign)
		निवड (errtype)
		  {
		  स्थिती ic_argpass:
		    {
		      auto_diagnostic_group d;
		      range_label_for_type_mismatch rhs_label (rhstype, type);
		      gcc_rich_location richloc (अभिव्यक्ती_loc, &rhs_label,
						 highlight_colors::actual);
		      जर (pedwarn (&richloc, OPT_Wpointer_sign,
				   "pointer targets in passing argument %d of "
				   "%qE differ in signedness", parmnum, rname))
			inform_for_arg (fundecl, अभिव्यक्ती_loc, parmnum, type,
					rhstype);
		    }
		    थांबा;
		  स्थिती ic_assign:
		    pedwarn (location, OPT_Wpointer_sign,
			     "pointer targets in assignment from %qT to %qT "
			     "differ in signedness", rhstype, type);
		    थांबा;
		  स्थिती ic_init:
		  स्थिती ic_init_const:
		    pedwarn_init (location, OPT_Wpointer_sign,
				  "pointer targets in initialization of %qT "
				  "from %qT differ in signedness", type,
				  rhstype);
		    थांबा;
		  स्थिती ic_return:
		    pedwarn (location, OPT_Wpointer_sign, "pointer targets in "
			     "returning %qT from a function with return type "
			     "%qT differ in signedness", rhstype, type);
		    थांबा;
		  पूर्वनिर्धारित:
		    gcc_unreachable ();
		  }
	    }
	  अन्यथा जर (वृक्ष_CODE (ttl) == FUNCTION_TYPE
		   && वृक्ष_CODE (ttr) == FUNCTION_TYPE)
	    {
	      /* Because const and volatile on functions are restrictions
		 that say the function will not do certain things,
		 it is okay to use a const or volatile function
		 where an ordinary one is wanted, but not vice-versa.  */
	      जर (TYPE_QUALS_NO_ADDR_SPACE (ttl)
		  & ~TYPE_QUALS_NO_ADDR_SPACE (ttr))
		PEDWARN_FOR_QUALIFIERS (location, अभिव्यक्ती_loc,
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
      अन्यथा जर (!objc_ok)
	{
	  auto_diagnostic_group d;
	  तार्किक warned = असत्य;
	  pp_markup::element_expected_type e_type (type);
	  pp_markup::element_actual_type e_rhstype (rhstype);
	  निवड (errtype)
	    {
	    स्थिती ic_argpass:
	      {
		range_label_for_type_mismatch rhs_label (rhstype, type);
		gcc_rich_location richloc (अभिव्यक्ती_loc, &rhs_label,
					   highlight_colors::actual);
		warned
		  = permerror_opt (&richloc, OPT_Wincompatible_pointer_types,
				   "passing argument %d of %qE from "
				   "incompatible pointer type",
				   parmnum, rname);
		जर (warned)
		  inform_for_arg (fundecl, अभिव्यक्ती_loc, parmnum, type, rhstype);
	      }
	      थांबा;
	    स्थिती ic_assign:
	      जर (bltin)
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
	      थांबा;
	    स्थिती ic_init:
	    स्थिती ic_init_const:
	      जर (bltin)
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
	      थांबा;
	    स्थिती ic_return:
	      जर (bltin)
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
	      थांबा;
	    पूर्वनिर्धारित:
	      gcc_unreachable ();
	    }
	  जर (warned)
	    {
	      /* If the mismatching function type is a pointer to a function,
		 try to show the decl of the function.  */
	      जर (वृक्ष_CODE (rhs) == ADDR_अभिव्यक्ती
		  && वृक्ष_CODE (वृक्ष_OPERAND (rhs, 0)) == FUNCTION_DECL)
		{
		  वृक्ष rhs_fndecl = वृक्ष_OPERAND (rhs, 0);
		  जर (!DECL_IS_UNDECLARED_BUILTIN (rhs_fndecl))
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

      परत convert (type, rhs);
    }
  अन्यथा जर (codel == POINTER_TYPE && coder == ARRAY_TYPE)
    {
      /* ??? This should not be an error when inlining calls to
	 unprototyped functions.  */
      स्थिरांक अक्षर संदेश[] = "invalid use of non-lvalue array";
      जर (warnopt)
	warning_at (location, warnopt, संदेश);
      अन्यथा
	error_at (location, संदेश);
      परत error_mark_गाठ;
    }
  अन्यथा जर (codel == POINTER_TYPE
	   && (coder == INTEGER_TYPE
	       || coder == ENUMERAL_TYPE
	       || coder == BOOLEAN_TYPE
	       || coder == NULLPTR_TYPE
	       || coder == BITINT_TYPE))
    {
      जर (null_pointer_constant && c_inhibit_evaluation_warnings == 0
	  && coder != NULLPTR_TYPE)
	warning_at (location, OPT_Wzero_as_null_pointer_constant,
		    "zero as null pointer constant");
      /* A NULLPTR type is just a nullptr always.  */
      जर (coder == NULLPTR_TYPE)
	परत omit_one_operand_loc (अभिव्यक्ती_loc, type, nullptr_गाठ, rhs);
      /* An explicit constant 0 or type nullptr_t can convert to a pointer,
	 or one that results from arithmetic, even including a cast to
	 integer type.  */
      अन्यथा जर (!null_pointer_constant)
	निवड (errtype)
	  {
	  स्थिती ic_argpass:
	    {
	      auto_diagnostic_group d;
	      range_label_for_type_mismatch rhs_label (rhstype, type);
	      gcc_rich_location richloc (अभिव्यक्ती_loc, &rhs_label,
					 highlight_colors::actual);
	      जर (permerror_opt (&richloc, OPT_Wint_conversion,
				 "passing argument %d of %qE makes pointer "
				 "from integer without a cast", parmnum, rname))
		{
		  maybe_emit_indirection_note (अभिव्यक्ती_loc, rhs, type);
		  inform_for_arg (fundecl, अभिव्यक्ती_loc, parmnum, type, rhstype);
		}
	    }
	    थांबा;
	  स्थिती ic_assign:
	    permerror_opt (location, OPT_Wint_conversion,
			   "assignment to %qT from %qT makes pointer from "
			   "integer without a cast", type, rhstype);
	    थांबा;
	  स्थिती ic_init:
	  स्थिती ic_init_const:
	    permerror_init (location, OPT_Wint_conversion,
			    "initialization of %qT from %qT makes pointer "
			    "from integer without a cast", type, rhstype);
	    थांबा;
	  स्थिती ic_return:
	    permerror_init (location, OPT_Wint_conversion,
			    "returning %qT from a function with return type "
			    "%qT makes pointer from integer without a cast",
			    rhstype, type);
	    थांबा;
	  पूर्वनिर्धारित:
	    gcc_unreachable ();
	  }

      परत convert (type, rhs);
    }
  अन्यथा जर ((codel == INTEGER_TYPE || codel == BITINT_TYPE)
	   && coder == POINTER_TYPE)
    {
      निवड (errtype)
	{
	स्थिती ic_argpass:
	  {
	    auto_diagnostic_group d;
	    range_label_for_type_mismatch rhs_label (rhstype, type);
	    gcc_rich_location richloc (अभिव्यक्ती_loc, &rhs_label,
				       highlight_colors::actual);
	    जर (permerror_opt (&richloc, OPT_Wint_conversion,
			       "passing argument %d of %qE makes integer from "
			       "pointer without a cast", parmnum, rname))
	      {
		maybe_emit_indirection_note (अभिव्यक्ती_loc, rhs, type);
		inform_for_arg (fundecl, अभिव्यक्ती_loc, parmnum, type, rhstype);
	      }
	  }
	  थांबा;
	स्थिती ic_assign:
	  permerror_opt (location, OPT_Wint_conversion,
			 "assignment to %qT from %qT makes integer from "
			 "pointer without a cast", type, rhstype);
	  थांबा;
	स्थिती ic_init:
	स्थिती ic_init_const:
	  permerror_init (location, OPT_Wint_conversion,
			  "initialization of %qT from %qT makes integer "
			  "from pointer without a cast", type, rhstype);
	  थांबा;
	स्थिती ic_return:
	  permerror_opt (location, OPT_Wint_conversion, "returning %qT from a "
			 "function with return type %qT makes integer from "
			 "pointer without a cast", rhstype, type);
	  थांबा;
	पूर्वनिर्धारित:
	  gcc_unreachable ();
	}

      परत convert (type, rhs);
    }
  अन्यथा जर (C_BOOLEAN_TYPE_P (type)
	   /* The type nullptr_t may be converted to bool.  The
	      result is false.  */
	   && (coder == POINTER_TYPE || coder == NULLPTR_TYPE))
    {
      वृक्ष ret;
      तार्किक save = in_late_द्विमान_op;
      in_late_द्विमान_op = सत्य;
      ret = convert (type, rhs);
      in_late_द्विमान_op = save;
      परत ret;
    }
  अन्यथा जर (codel == NULLPTR_TYPE && null_pointer_constant)
    परत convert (type, rhs);

  निवड (errtype)
    {
    स्थिती ic_argpass:
      {
	auto_diagnostic_group d;
	range_label_for_type_mismatch rhs_label (rhstype, type);
	gcc_rich_location richloc (अभिव्यक्ती_loc, &rhs_label,
				   highlight_colors::actual);
	स्थिरांक अक्षर संदेश[] = G_("incompatible type for argument %d of %qE");
	जर (warnopt)
	  warning_at (अभिव्यक्ती_loc, warnopt, संदेश, parmnum, rname);
	अन्यथा
	  error_at (&richloc, संदेश, parmnum, rname);
	inform_for_arg (fundecl, अभिव्यक्ती_loc, parmnum, type, rhstype);
      }
      थांबा;
    स्थिती ic_assign:
      {
	स्थिरांक अक्षर संदेश[]
	  = G_("incompatible types when assigning to type %qT from type %qT");
	जर (warnopt)
	  warning_at (अभिव्यक्ती_loc, 0, संदेश, type, rhstype);
	अन्यथा
	  error_at (अभिव्यक्ती_loc, संदेश, type, rhstype);
	थांबा;
      }
    स्थिती ic_init:
    स्थिती ic_init_const:
      {
	स्थिरांक अक्षर संदेश[]
	  = G_("incompatible types when initializing type %qT using type %qT");
	जर (warnopt)
	  warning_at (location, 0, संदेश, type, rhstype);
	अन्यथा
	  error_at (location, संदेश, type, rhstype);
	थांबा;
      }
    स्थिती ic_return:
      {
	स्थिरांक अक्षर संदेश[]
	  = G_("incompatible types when returning type %qT but %qT was expected");
	जर (warnopt)
	  warning_at (location, 0, संदेश, rhstype, type);
	अन्यथा
	  error_at (location, संदेश, rhstype, type);
	थांबा;
      }
    पूर्वनिर्धारित:
      gcc_unreachable ();
    }

  परत error_mark_गाठ;
}

/* If VALUE is a compound expr all of whose expressions are constant, then
   return its value.  Otherwise, return error_mark_node.

   This is for handling COMPOUND_EXPRs as initializer elements
   which is allowed with a warning when -pedantic is specified.  */

स्थिर वृक्ष
valid_compound_अभिव्यक्ती_initializer (वृक्ष मूल्य, वृक्ष endtype)
{
  जर (वृक्ष_CODE (मूल्य) == COMPOUND_अभिव्यक्ती)
    {
      जर (valid_compound_अभिव्यक्ती_initializer (वृक्ष_OPERAND (मूल्य, 0), endtype)
	  == error_mark_गाठ)
	परत error_mark_गाठ;
      परत valid_compound_अभिव्यक्ती_initializer (वृक्ष_OPERAND (मूल्य, 1),
					      endtype);
    }
  अन्यथा जर (!initializer_constant_valid_p (मूल्य, endtype))
    परत error_mark_गाठ;
  अन्यथा
    परत मूल्य;
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
  तार्किक int_const_अभिव्यक्ती = असत्य;
  तार्किक arith_const_अभिव्यक्ती = असत्य;

  /* If variable's type was invalidly declared, just ignore it.  */

  type = वृक्ष_TYPE (decl);
  जर (वृक्ष_CODE (type) == ERROR_MARK)
    परत;

  /* Digest the specified initializer into an expression.  */

  जर (init)
    {
      npc = null_pointer_constant_p (init);
      int_const_अभिव्यक्ती = (वृक्ष_CODE (init) == INTEGER_CST
			&& !वृक्ष_OVERFLOW (init)
			&& INTEGRAL_TYPE_P (वृक्ष_TYPE (init)));
      /* Not fully determined before folding.  */
      arith_const_अभिव्यक्ती = सत्य;
    }
  तार्किक constexpr_p = (VAR_P (decl)
		      && C_DECL_DECLARED_CONSTEXPR (decl));
  मूल्य = digest_init (init_loc, decl, type, init, origtype, npc,
		       int_const_अभिव्यक्ती, arith_const_अभिव्यक्ती, सत्य,
		       वृक्ष_STATIC (decl) || constexpr_p, constexpr_p);

  /* Store the expression if valid; else report error.  */

  जर (!in_system_header_at (आदान_location)
      && AGGREGATE_TYPE_P (वृक्ष_TYPE (decl)) && !वृक्ष_STATIC (decl))
    warning (OPT_Wtraditional, "traditional C rejects automatic "
	     "aggregate initialization");

  जर (मूल्य != error_mark_गाठ || वृक्ष_CODE (decl) != FUNCTION_DECL)
    DECL_INITIAL (decl) = मूल्य;

  /* ANSI wants warnings about out-of-range constant initializers.  */
  STRIP_TYPE_NOPS (मूल्य);
  जर (वृक्ष_STATIC (decl))
    constant_expression_warning (मूल्य);

  /* Check if we need to set array size from compound literal size.  */
  जर (वृक्ष_CODE (type) == ARRAY_TYPE
      && TYPE_DOMAIN (type) == NULL_वृक्ष
      && मूल्य != error_mark_गाठ)
    {
      वृक्ष inside_init = init;

      STRIP_TYPE_NOPS (inside_init);
      inside_init = fold (inside_init);

      जर (वृक्ष_CODE (inside_init) == COMPOUND_LITERAL_अभिव्यक्ती)
	{
	  वृक्ष cldecl = COMPOUND_LITERAL_अभिव्यक्ती_DECL (inside_init);

	  जर (TYPE_DOMAIN (वृक्ष_TYPE (cldecl)))
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
  पूर्णांक kind;
  संघ
    {
      अचिन्हित HOST_WIDE_INT i;
      स्थिरांक अक्षर *s;
    } u;
};

#define SPELLING_STRING 1
#define SPELLING_MEMBER 2
#define SPELLING_BOUNDS 3

स्थिर संरचना spelling *spelling;	/* Next stack element (unused).  */
स्थिर संरचना spelling *spelling_base;	/* Spelling stack base.  */
स्थिर पूर्णांक spelling_size;		/* Size of the spelling stack.  */

/* Macros to save and restore the spelling stack around push_... functions.
   Alternative to SAVE_SPELLING_STACK.  */

#define SPELLING_DEPTH() (spelling - spelling_base)
#define RESTORE_SPELLING_DEPTH(DEPTH) (spelling = spelling_base + (DEPTH))

/* Push an element on the spelling stack with type KIND and assign VALUE
   to MEMBER.  */

#define ढकला_SPELLING(KIND, मूल्य_2, MEMBER)				\
{									\
  पूर्णांक depth = SPELLING_DEPTH ();					\
									\
  जर (depth >= spelling_size)						\
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
ढकला_string (स्थिरांक अक्षर *string)
{
  ढकला_SPELLING (SPELLING_STRING, string, u.s);
}

/* Push a member name on the stack.  Printed as '.' STRING.  */

स्थिर शून्य
ढकला_member_name (वृक्ष decl)
{
  स्थिरांक अक्षर *स्थिरांक string
    = (DECL_NAME (decl)
       ? identifier_to_locale (IDENTIFIER_POINTER (DECL_NAME (decl)))
       : _("<anonymous>"));
  ढकला_SPELLING (SPELLING_MEMBER, string, u.s);
}

/* Push an array bounds on the stack.  Printed as [BOUNDS].  */

स्थिर शून्य
ढकला_array_bounds (अचिन्हित HOST_WIDE_INT bounds)
{
  ढकला_SPELLING (SPELLING_BOUNDS, bounds, u.i);
}

/* Compute the maximum size in bytes of the printed spelling.  */

स्थिर पूर्णांक
spelling_length (शून्य)
{
  पूर्णांक size = 0;
  संरचना spelling *p;

  साठी (p = spelling_base; p < spelling; p++)
    {
      जर (p->kind == SPELLING_BOUNDS)
	size += 25;
      अन्यथा
	size += म_माप (p->u.s) + 1;
    }

  परत size;
}

/* Print the spelling to BUFFER and return it.  */

स्थिर अक्षर *
print_spelling (अक्षर *buffer)
{
  अक्षर *d = buffer;
  संरचना spelling *p;

  साठी (p = spelling_base; p < spelling; p++)
    जर (p->kind == SPELLING_BOUNDS)
      {
	प्र_लिखो (d, "[" HOST_WIDE_INT_PRINT_UNSIGNED "]", p->u.i);
	d += म_माप (d);
      }
    अन्यथा
      {
	स्थिरांक अक्षर *s;
	जर (p->kind == SPELLING_MEMBER)
	  *d++ = '.';
	साठी (s = p->u.s; (*d = *s++); d++)
	  ;
      }
  *d++ = '\0';
  परत buffer;
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
  जर (वृक्ष_CODE (init) == REAL_CST
      && TYPE_MODE (वृक्ष_TYPE (init)) == TYPE_MODE (type))
    {
      /* Same mode, no conversion required except for the case of
	 signaling NaNs if the types are incompatible (e.g. double and
	 long double with the same mode).  */
      जर (REAL_मूल्य_ISSIGNALING_NAN (वृक्ष_REAL_CST (init))
	  && !comptypes (TYPE_MAIN_VARIANT (type),
			 TYPE_MAIN_VARIANT (वृक्ष_TYPE (init))))
	परत असत्य;
      परत सत्य;
    }
  जर (वृक्ष_CODE (init) == INTEGER_CST)
    {
      वृक्ष converted = build_real_from_int_cst (type, init);
      तार्किक fail = असत्य;
      wide_int w = real_to_integer (&वृक्ष_REAL_CST (converted), &fail,
				    TYPE_PRECISION (वृक्ष_TYPE (init)));
      परत !fail && wi::eq_p (w, wi::to_wide (init));
    }
  जर (REAL_मूल्य_ISSIGNALING_NAN (वृक्ष_REAL_CST (init)))
    परत असत्य;
  जर ((REAL_मूल्य_ISINF (वृक्ष_REAL_CST (init))
       && MODE_HAS_INFINITIES (TYPE_MODE (type)))
      || (REAL_मूल्य_ISNAN (वृक्ष_REAL_CST (init))
	  && MODE_HAS_NANS (TYPE_MODE (type))))
    परत सत्य;
  जर (DECIMAL_FLOAT_TYPE_P (type)
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
      अक्षर string[256];
      real_to_decimal (string, &t, आकार string, 0, 1);
      तार्किक res = (mpfr_strtofr (dec_val, string, रिक्त, 10, MPFR_RNDN) == 0
		  && mpfr_equal_p (bin_val, dec_val));
      mpfr_clear (bin_val);
      mpfr_clear (dec_val);
      परत res;
    }
  /* exact_real_truncate is not quite right here, since it doesn't
     allow even an exact conversion to subnormal values.  */
  REAL_मूल्य_TYPE t;
  real_convert (&t, TYPE_MODE (type), &वृक्ष_REAL_CST (init));
  परत real_identical (&t, &वृक्ष_REAL_CST (init));
}

/* Check whether INIT (location LOC) is valid as a 'constexpr'
   initializer for type TYPE, and give an error if not.  INIT has
   already been folded and verified to be constant.  INT_CONST_EXPR
   and ARITH_CONST_EXPR say whether it is an integer constant
   expression or arithmetic constant expression, respectively.  If
   TYPE is not a scalar type, this function does nothing.  */

स्थिर शून्य
check_constexpr_init (location_t loc, वृक्ष type, वृक्ष init,
		      तार्किक int_const_अभिव्यक्ती, तार्किक arith_const_अभिव्यक्ती)
{
  जर (POINTER_TYPE_P (type))
    {
      /* The initializer must be null.  */
      जर (वृक्ष_CODE (init) != INTEGER_CST || !integer_zerop (init))
	error_at (loc, "%<constexpr%> pointer initializer is not null");
      परत;
    }
  जर (INTEGRAL_TYPE_P (type))
    {
      /* The initializer must be an integer constant expression,
	 representable in the target type.  */
      जर (!int_const_अभिव्यक्ती)
	{
	  जर (वृक्ष_CODE (init) == RAW_DATA_CST
	      && TYPE_PRECISION (type) == अक्षर_बिट)
	    {
	      जर (!TYPE_UNSIGNED (type))
		साठी (अचिन्हित पूर्णांक i = 0;
		     i < (अचिन्हित) RAW_DATA_LENGTH (init); ++i)
		  जर (RAW_DATA_SCHAR_ELT (init, i) < 0)
		    {
		      error_at (loc, "%<constexpr%> initializer not "
				"representable in type of object");
		      थांबा;
		    }
	    }
	  अन्यथा
	    error_at (loc, "%<constexpr%> integer initializer is not an "
		      "integer constant expression");
	}
      अन्यथा जर (!int_fits_type_p (init, type))
	error_at (loc, "%<constexpr%> initializer not representable in "
		  "type of object");
      परत;
    }
  /* We don't apply any extra checks to extension types such as vector
     or fixed-point types.  */
  जर (वृक्ष_CODE (type) != REAL_TYPE && वृक्ष_CODE (type) != COMPLEX_TYPE)
    परत;
  जर (!arith_const_अभिव्यक्ती)
    {
      error_at (loc, "%<constexpr%> initializer is not an arithmetic "
		"constant expression");
      परत;
    }
  /* We don't apply any extra checks to complex integers.  */
  जर (वृक्ष_CODE (type) == COMPLEX_TYPE
      && वृक्ष_CODE (वृक्ष_TYPE (type)) != REAL_TYPE)
    परत;
  /* Following N3082, a real type cannot be initialized from a complex
     type and a binary type cannot be initialized from a decimal type
     (but initializing a decimal type from a binary type is OK).
     Signaling NaN initializers are OK only if the types are
     compatible (not just the same mode); all quiet NaN and infinity
     initializations are considered to preserve the value.  */
  जर (वृक्ष_CODE (वृक्ष_TYPE (init)) == COMPLEX_TYPE
      && SCALAR_FLOAT_TYPE_P (type))
    {
      error_at (loc, "%<constexpr%> initializer for a real type is of "
		"complex type");
      परत;
    }
  जर (SCALAR_FLOAT_TYPE_P (type)
      && SCALAR_FLOAT_TYPE_P (वृक्ष_TYPE (init))
      && DECIMAL_FLOAT_TYPE_P (वृक्ष_TYPE (init))
      && !DECIMAL_FLOAT_TYPE_P (type))
    {
      error_at (loc, "%<constexpr%> initializer for a binary "
		"floating-point type is of decimal type");
      परत;
    }
  तार्किक fits;
  जर (वृक्ष_CODE (type) == COMPLEX_TYPE)
    {
      निवड (वृक्ष_CODE (init))
	{
	स्थिती INTEGER_CST:
	स्थिती REAL_CST:
	  fits = constexpr_init_fits_real_type (वृक्ष_TYPE (type), init);
	  थांबा;
	स्थिती COMPLEX_CST:
	  fits = (constexpr_init_fits_real_type (वृक्ष_TYPE (type),
						 वृक्ष_REALPART (init))
		  && constexpr_init_fits_real_type (वृक्ष_TYPE (type),
						    वृक्ष_IMAGPART (init)));
	  थांबा;
	पूर्वनिर्धारित:
	  gcc_unreachable ();
	}
    }
  अन्यथा
    fits = constexpr_init_fits_real_type (type, init);
  जर (!fits)
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
	     वृक्ष origtype, तार्किक null_pointer_constant, तार्किक int_const_अभिव्यक्ती,
	     तार्किक arith_const_अभिव्यक्ती, तार्किक strict_string,
	     तार्किक require_constant, तार्किक require_constexpr)
{
  गणना वृक्ष_code code = वृक्ष_CODE (type);
  वृक्ष inside_init = init;
  वृक्ष semantic_type = NULL_वृक्ष;
  तार्किक maybe_const = सत्य;

  जर (type == error_mark_गाठ
      || !init
      || error_operand_p (init))
    परत error_mark_गाठ;

  STRIP_TYPE_NOPS (inside_init);

  /* If require_constant is TRUE,  when the initializer is a call to
     .ACCESS_WITH_SIZE, use the first argument as the initializer.
     For example:
     y = (char *) .ACCESS_WITH_SIZE ((char *) &static_annotated.c,...)
     will be converted to
     y = &static_annotated.c.  */

  जर (require_constant
      && वृक्ष_CODE (inside_init) == NOP_अभिव्यक्ती
      && वृक्ष_CODE (वृक्ष_OPERAND (inside_init, 0)) == CALL_अभिव्यक्ती
      && is_access_with_size_p (वृक्ष_OPERAND (inside_init, 0)))
    inside_init
      = get_ref_from_access_with_size (वृक्ष_OPERAND (inside_init, 0));

  जर (!c_in_omp_for)
    {
      जर (वृक्ष_CODE (inside_init) == EXCESS_PRECISION_अभिव्यक्ती)
	{
	  semantic_type = वृक्ष_TYPE (inside_init);
	  inside_init = वृक्ष_OPERAND (inside_init, 0);
	}
      inside_init = c_fully_fold (inside_init, require_constant, &maybe_const);
    }
  /* TODO: this may not detect all cases of expressions folding to
     constants that are not arithmetic constant expressions.  */
  जर (!maybe_const)
    arith_const_अभिव्यक्ती = असत्य;
  अन्यथा जर (!INTEGRAL_TYPE_P (वृक्ष_TYPE (inside_init))
	   && वृक्ष_CODE (वृक्ष_TYPE (inside_init)) != REAL_TYPE
	   && वृक्ष_CODE (वृक्ष_TYPE (inside_init)) != COMPLEX_TYPE)
    arith_const_अभिव्यक्ती = असत्य;
  अन्यथा जर (वृक्ष_CODE (inside_init) != INTEGER_CST
	   && वृक्ष_CODE (inside_init) != REAL_CST
	   && वृक्ष_CODE (inside_init) != COMPLEX_CST
	   && वृक्ष_CODE (inside_init) != RAW_DATA_CST)
    arith_const_अभिव्यक्ती = असत्य;
  अन्यथा जर (वृक्ष_OVERFLOW (inside_init))
    arith_const_अभिव्यक्ती = असत्य;

  /* Initialization of an array of chars from a string constant
     optionally enclosed in braces.  */

  जर (code == ARRAY_TYPE && inside_init
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
      तार्किक char_array = (typ1 == char_type_गाठ
			 || typ1 == signed_char_type_गाठ
			 || typ1 == unsigned_char_type_गाठ);
      तार्किक wchar_array = comptypes (typ1, wchar_type_गाठ);
      तार्किक char16_array = comptypes (typ1, char16_type_गाठ);
      तार्किक char32_array = comptypes (typ1, char32_type_गाठ);

      जर (char_array || wchar_array || char16_array || char32_array)
	{
	  संरचना c_अभिव्यक्ती अभिव्यक्ती;
	  वृक्ष typ2 = TYPE_MAIN_VARIANT (वृक्ष_TYPE (वृक्ष_TYPE (inside_init)));
	  तार्किक incompat_string_cst = असत्य;
	  अभिव्यक्ती.मूल्य = inside_init;
	  अभिव्यक्ती.original_code = (strict_string ? STRING_CST : ERROR_MARK);
	  अभिव्यक्ती.original_type = रिक्त;
	  अभिव्यक्ती.m_decimal = 0;
	  maybe_warn_string_init (init_loc, type, अभिव्यक्ती);

	  जर (flexible_array_member_type_p (type))
	    pedwarn_init (init_loc, OPT_Wpedantic,
			  "initialization of a flexible array member");

	  जर (comptypes (TYPE_MAIN_VARIANT (वृक्ष_TYPE (inside_init)),
			 TYPE_MAIN_VARIANT (type)))
	    परत inside_init;

	  जर (char_array)
	    {
	      जर (typ2 != char_type_गाठ && typ2 != char8_type_गाठ)
		incompat_string_cst = सत्य;
	    }
	  अन्यथा जर (!comptypes (typ1, typ2))
	    incompat_string_cst = सत्य;

          जर (incompat_string_cst)
            {
	      error_init (init_loc, "cannot initialize array of %qT from "
			  "a string literal with type array of %qT",
			  typ1, typ2);
	      परत error_mark_गाठ;
            }

	  जर (require_constexpr
	      && TYPE_UNSIGNED (typ1) != TYPE_UNSIGNED (typ2))
	    {
	      /* Check if all characters of the string can be
		 represented in the type of the constexpr object being
		 initialized.  */
	      अचिन्हित HOST_WIDE_INT len = वृक्ष_STRING_LENGTH (inside_init);
	      स्थिरांक अचिन्हित अक्षर *p =
		(स्थिरांक अचिन्हित अक्षर *) वृक्ष_STRING_POINTER (inside_init);
	      gcc_assert (CHAR_TYPE_SIZE == 8 && अक्षर_बिट == 8);
	      साठी (अचिन्हित i = 0; i < len; i++)
		जर (p[i] > 127)
		  {
		    error_init (init_loc, "%<constexpr%> initializer not "
				"representable in type of object");
		    थांबा;
		  }
	    }

	  जर (TYPE_DOMAIN (type) != NULL_वृक्ष
	      && TYPE_SIZE (type) != NULL_वृक्ष
	      && वृक्ष_CODE (TYPE_SIZE (type)) == INTEGER_CST)
	    {
	      अचिन्हित HOST_WIDE_INT len = वृक्ष_STRING_LENGTH (inside_init);

	      जर (compare_वृक्ष_int (TYPE_SIZE_UNIT (type), len) < 0)
		{
		  अचिन्हित HOST_WIDE_INT avail
		    = वृक्ष_to_uhwi (TYPE_SIZE_UNIT (type));
		  अचिन्हित unit = TYPE_PRECISION (typ1) / BITS_PER_UNIT;
		  स्थिरांक अक्षर *p = वृक्ष_STRING_POINTER (inside_init);

		  /* Construct truncated string.  */
		  inside_init = build_string (avail, p);

		  /* Subtract the size of a single (possibly wide) character
		     because it may be ok to ignore the terminating NUL char
		     that is counted in the length of the constant.  */
		  जर (len - unit > avail)
		    pedwarn_init (init_loc, 0,
				  "initializer-string for array of %qT "
				  "is too long (%wu chars into %wu "
				  "available)", typ1, len, avail);
		  अन्यथा जर (warn_cxx_compat)
		    warning_at (init_loc, OPT_Wc___compat,
				"initializer-string for array of %qT "
				"is too long for C++ (%wu chars into %wu "
				"available)", typ1, len, avail);
		  अन्यथा जर (warn_unterminated_string_initialization
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
	  परत inside_init;
	}
      अन्यथा जर (INTEGRAL_TYPE_P (typ1))
	{
	  error_init (init_loc, "array of inappropriate type initialized "
		      "from string constant");
	  परत error_mark_गाठ;
	}
    }

  /* Build a VECTOR_CST from a *constant* vector constructor.  If the
     vector constructor is not constant (e.g. {1,2,3,foo()}) then punt
     below and handle as a constructor.  */
  जर (code == VECTOR_TYPE
      && VECTOR_TYPE_P (वृक्ष_TYPE (inside_init))
      && vector_types_convertible_p (वृक्ष_TYPE (inside_init), type, सत्य)
      && वृक्ष_CONSTANT (inside_init))
    {
      जर (वृक्ष_CODE (inside_init) == VECTOR_CST
	  && comptypes (TYPE_MAIN_VARIANT (वृक्ष_TYPE (inside_init)),
			TYPE_MAIN_VARIANT (type)))
	परत inside_init;

      जर (वृक्ष_CODE (inside_init) == CONSTRUCTOR)
	{
	  अचिन्हित HOST_WIDE_INT ix;
	  वृक्ष मूल्य;
	  तार्किक constant_p = सत्य;

	  /* Iterate through elements and check if all constructor
	     elements are *_CSTs.  */
	  FOR_EACH_CONSTRUCTOR_मूल्य (CONSTRUCTOR_ELTS (inside_init), ix, मूल्य)
	    जर (!CONSTANT_CLASS_P (मूल्य))
	      {
		constant_p = असत्य;
		थांबा;
	      }

	  जर (constant_p)
	    परत build_vector_from_ctor (type,
					   CONSTRUCTOR_ELTS (inside_init));
	}
    }

  जर (warn_sequence_point)
    verify_sequence_points (inside_init);

  /* Any type can be initialized
     from an expression of the same type, optionally with braces.  */

  जर (inside_init && वृक्ष_TYPE (inside_init) != NULL_वृक्ष
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
      जर (code == POINTER_TYPE)
	{
	  जर (वृक्ष_CODE (वृक्ष_TYPE (inside_init)) == ARRAY_TYPE)
	    {
	      जर (वृक्ष_CODE (inside_init) == STRING_CST
		  || वृक्ष_CODE (inside_init) == COMPOUND_LITERAL_अभिव्यक्ती)
		inside_init = array_to_pointer_conversion
		  (init_loc, inside_init);
	      अन्यथा
		{
		  error_init (init_loc, "invalid use of non-lvalue array");
		  परत error_mark_गाठ;
		}
	    }
	}

      जर (code == VECTOR_TYPE || c_hardbool_type_attr (type))
	/* Although the types are compatible, we may require a
	   conversion.  */
	inside_init = convert (type, inside_init);

      जर ((code == RECORD_TYPE || code == UNION_TYPE)
	  && !comptypes (TYPE_MAIN_VARIANT (type), TYPE_MAIN_VARIANT (वृक्ष_TYPE (inside_init))))
	{
	  error_init (init_loc, "invalid initializer");
	  परत error_mark_गाठ;
	}

      जर (require_constant
	  && वृक्ष_CODE (inside_init) == COMPOUND_LITERAL_अभिव्यक्ती)
	{
	  /* As an extension, allow initializing objects with static storage
	     duration with compound literals (which are then treated just as
	     the brace enclosed list they contain).  Also allow this for
	     vectors, as we can only assign them with compound literals.  */
	  जर (flag_isoc99 && code != VECTOR_TYPE)
	    pedwarn_init (init_loc, OPT_Wpedantic, "initializer element "
			  "is not constant");
	  वृक्ष decl = COMPOUND_LITERAL_अभिव्यक्ती_DECL (inside_init);
	  inside_init = DECL_INITIAL (decl);
	}

      जर (code == ARRAY_TYPE && वृक्ष_CODE (inside_init) != STRING_CST
	  && वृक्ष_CODE (inside_init) != CONSTRUCTOR)
	{
	  error_init (init_loc, "array initialized from non-constant array "
		      "expression");
	  परत error_mark_गाठ;
	}

      /* Compound expressions can only occur here if -Wpedantic or
	 -pedantic-errors is specified.  In the later case, we always want
	 an error.  In the former case, we simply want a warning.  */
      जर (require_constant && pedantic
	  && वृक्ष_CODE (inside_init) == COMPOUND_अभिव्यक्ती)
	{
	  inside_init
	    = valid_compound_अभिव्यक्ती_initializer (inside_init,
					       वृक्ष_TYPE (inside_init));
	  जर (inside_init == error_mark_गाठ)
	    error_init (init_loc, "initializer element is not constant");
	  अन्यथा
	    pedwarn_init (init_loc, OPT_Wpedantic,
			  "initializer element is not constant");
	  जर (flag_pedantic_errors)
	    inside_init = error_mark_गाठ;
	}
      अन्यथा जर (require_constant
	       && !initializer_constant_valid_p (inside_init,
						 वृक्ष_TYPE (inside_init)))
	{
	  error_init (init_loc, "initializer element is not constant");
	  inside_init = error_mark_गाठ;
	}
      अन्यथा जर (require_constant && !maybe_const)
	pedwarn_init (init_loc, OPT_Wpedantic,
		      "initializer element is not a constant expression");
      अन्यथा जर (require_constexpr)
	check_constexpr_init (init_loc, type, inside_init,
			      int_const_अभिव्यक्ती, arith_const_अभिव्यक्ती);

      /* Added to enable additional -Wsuggest-attribute=format warnings.  */
      जर (वृक्ष_CODE (वृक्ष_TYPE (inside_init)) == POINTER_TYPE)
	inside_init = convert_for_assignment (init_loc, UNKNOWN_LOCATION,
					      type, inside_init, origtype,
					      (require_constant
					       ? ic_init_const
					       : ic_init), null_pointer_constant,
					      NULL_वृक्ष, NULL_वृक्ष, 0);
      जर (वृक्ष_CODE (inside_init) == RAW_DATA_CST
	  && c_inhibit_evaluation_warnings == 0
	  && warn_conversion
	  && !TYPE_UNSIGNED (type)
	  && TYPE_PRECISION (type) == अक्षर_बिट)
	साठी (अचिन्हित पूर्णांक i = 0;
	     i < (अचिन्हित) RAW_DATA_LENGTH (inside_init); ++i)
	  जर (RAW_DATA_SCHAR_ELT (inside_init, i) < 0)
	    warning_at (init_loc, OPT_Wconversion,
			"conversion from %qT to %qT changes value from "
			"%qd to %qd",
			integer_type_गाठ, type,
			RAW_DATA_UCHAR_ELT (inside_init, i),
			RAW_DATA_SCHAR_ELT (inside_init, i));
      परत inside_init;
    }

  /* Handle scalar types, including conversions.  */

  जर (code == INTEGER_TYPE || code == REAL_TYPE || code == FIXED_POINT_TYPE
      || code == POINTER_TYPE || code == ENUMERAL_TYPE || code == BOOLEAN_TYPE
      || code == COMPLEX_TYPE || code == VECTOR_TYPE || code == NULLPTR_TYPE
      || code == BITINT_TYPE)
    {
      वृक्ष unconverted_init = inside_init;
      जर (वृक्ष_CODE (वृक्ष_TYPE (init)) == ARRAY_TYPE
	  && (वृक्ष_CODE (init) == STRING_CST
	      || वृक्ष_CODE (init) == COMPOUND_LITERAL_अभिव्यक्ती))
	inside_init = init = array_to_pointer_conversion (init_loc, init);
      जर (semantic_type)
	inside_init = build1 (EXCESS_PRECISION_अभिव्यक्ती, semantic_type,
			      inside_init);
      inside_init
	= convert_for_assignment (init_loc, UNKNOWN_LOCATION, type,
				  inside_init, origtype,
				  require_constant ? ic_init_const : ic_init,
				  null_pointer_constant, NULL_वृक्ष, NULL_वृक्ष,
				  0);

      /* Check to see if we have already given an error message.  */
      जर (inside_init == error_mark_गाठ)
	;
      अन्यथा जर (require_constant && !वृक्ष_CONSTANT (inside_init))
	{
	  error_init (init_loc, "initializer element is not constant");
	  inside_init = error_mark_गाठ;
	}
      अन्यथा जर (require_constant
	       && !initializer_constant_valid_p (inside_init,
						 वृक्ष_TYPE (inside_init)))
	{
	  error_init (init_loc, "initializer element is not computable at "
		      "load time");
	  inside_init = error_mark_गाठ;
	}
      अन्यथा जर (require_constant && !maybe_const)
	pedwarn_init (init_loc, OPT_Wpedantic,
		      "initializer element is not a constant expression");
      अन्यथा जर (require_constexpr)
	check_constexpr_init (init_loc, type, unconverted_init,
			      int_const_अभिव्यक्ती, arith_const_अभिव्यक्ती);

      परत inside_init;
    }

  /* Come here only for records and arrays.  */

  जर (COMPLETE_TYPE_P (type) && वृक्ष_CODE (TYPE_SIZE (type)) != INTEGER_CST)
    {
      error_init (init_loc,
		  "variable-sized object may not be initialized except "
		  "with an empty initializer");
      परत error_mark_गाठ;
    }

  error_init (init_loc, "invalid initializer");
  परत error_mark_गाठ;
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
स्थिर पूर्णांक constructor_incremental;

/* 1 if so far this constructor's elements are all compile-time constants.  */
स्थिर पूर्णांक constructor_constant;

/* 1 if so far this constructor's elements are all valid address constants.  */
स्थिर पूर्णांक constructor_simple;

/* 1 if this constructor has an element that cannot be part of a
   constant expression.  */
स्थिर पूर्णांक constructor_nonconst;

/* 1 if this constructor is erroneous so far.  */
स्थिर पूर्णांक constructor_erroneous;

/* 1 if this constructor is the universal zero initializer { 0 }.  */
स्थिर पूर्णांक constructor_zeroinit;

/* 1 if this constructor should have padding bits zeroed (C23 {}.  */
स्थिर तार्किक constructor_zero_padding_bits;

/* 1 if this constructor is a braced scalar initializer (further nested levels
   of braces are an error).  */
स्थिर तार्किक constructor_braced_scalar;

/* Structure for managing pending initializer elements, organized as an
   AVL tree.  */

संरचना init_गाठ
{
  संरचना init_गाठ *डावा, *उजवा;
  संरचना init_गाठ *parent;
  पूर्णांक balance;
  वृक्ष purpose;
  वृक्ष मूल्य;
  वृक्ष origtype;
};

/* Tree of pending elements at this constructor level.
   These are elements encountered out of order
   which belong at places we haven't reached yet in actually
   writing the output.
   Will never hold tree nodes across GC runs.  */
स्थिर संरचना init_गाठ *constructor_pending_elts;

/* The SPELLING_DEPTH of this constructor.  */
स्थिर पूर्णांक constructor_depth;

/* DECL node for which an initializer is being read.
   0 means we are reading a constructor expression
   such as (struct foo) {...}.  */
स्थिर वृक्ष constructor_decl;

/* Nonzero if there were any member designators in this initializer.  */
स्थिर पूर्णांक constructor_designated;

/* Nesting depth of designator list.  */
स्थिर पूर्णांक designator_depth;

/* Nonzero if there were diagnosed errors in this designator list.  */
स्थिर पूर्णांक designator_erroneous;


/* This stack has a level for each implicit or explicit level of
   structuring in the initializer, including the outermost one.  It
   saves the values of most of the variables above.  */

संरचना constructor_range_चळत;

संरचना constructor_चळत
{
  संरचना constructor_चळत *next;
  वृक्ष type;
  वृक्ष fields;
  वृक्ष index;
  वृक्ष max_index;
  वृक्ष unfilled_index;
  वृक्ष unfilled_fields;
  वृक्ष bit_index;
  vec<constructor_elt, va_gc> *elements;
  संरचना init_गाठ *pending_elts;
  पूर्णांक offset;
  पूर्णांक depth;
  /* If value nonzero, this value should replace the entire
     constructor at this level.  */
  संरचना c_अभिव्यक्ती replacement_मूल्य;
  संरचना constructor_range_चळत *range_चळत;
  अक्षर constant;
  अक्षर simple;
  अक्षर nonconst;
  अक्षर implicit;
  अक्षर erroneous;
  अक्षर outer;
  अक्षर incremental;
  अक्षर designated;
  तार्किक zero_padding_bits;
  तार्किक braced_scalar;
  पूर्णांक designator_depth;
};

स्थिर संरचना constructor_चळत *constructor_चळत;

/* This stack represents designators from some range designator up to
   the last designator in the list.  */

संरचना constructor_range_चळत
{
  संरचना constructor_range_चळत *next, *prev;
  संरचना constructor_चळत *चळत;
  वृक्ष range_start;
  वृक्ष index;
  वृक्ष range_end;
  वृक्ष fields;
};

स्थिर संरचना constructor_range_चळत *constructor_range_चळत;

/* This stack records separate initializers that are nested.
   Nested initializers can't happen in ANSI C, but GNU C allows them
   in cases like { ... (struct foo) { ... } ... }.  */

संरचना initializer_चळत
{
  संरचना initializer_चळत *next;
  वृक्ष decl;
  संरचना constructor_चळत *constructor_चळत;
  संरचना constructor_range_चळत *constructor_range_चळत;
  vec<constructor_elt, va_gc> *elements;
  संरचना spelling *spelling;
  संरचना spelling *spelling_base;
  पूर्णांक spelling_size;
  अक्षर require_constant_मूल्य;
  अक्षर require_constant_elements;
  अक्षर require_constexpr_मूल्य;
  अक्षर designated;
  rich_location *missing_brace_richloc;
};

स्थिर संरचना initializer_चळत *initializer_चळत;

/* Prepare to parse and output the initializer for variable DECL.  */

शून्य
start_init (वृक्ष decl, वृक्ष asmspec_वृक्ष ATTRIBUTE_UNUSED,
	    तार्किक init_require_constant, तार्किक init_require_constexpr,
	    rich_location *richloc)
{
  स्थिरांक अक्षर *locus;
  संरचना initializer_चळत *p = XNEW (संरचना initializer_चळत);

  p->decl = constructor_decl;
  p->require_constant_मूल्य = require_constant_मूल्य;
  p->require_constant_elements = require_constant_elements;
  p->require_constexpr_मूल्य = require_constexpr_मूल्य;
  p->constructor_चळत = constructor_चळत;
  p->constructor_range_चळत = constructor_range_चळत;
  p->elements = constructor_elements;
  p->spelling = spelling;
  p->spelling_base = spelling_base;
  p->spelling_size = spelling_size;
  p->next = initializer_चळत;
  p->missing_brace_richloc = richloc;
  p->designated = constructor_designated;
  initializer_चळत = p;

  constructor_decl = decl;
  constructor_designated = 0;

  require_constant_मूल्य = init_require_constant;
  require_constexpr_मूल्य = init_require_constexpr;
  जर (decl != NULL_वृक्ष && decl != error_mark_गाठ)
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

  constructor_चळत = 0;
  constructor_range_चळत = 0;

  found_missing_braces = 0;

  spelling_base = 0;
  spelling_size = 0;
  RESTORE_SPELLING_DEPTH (0);

  जर (locus)
    ढकला_string (locus);
}

शून्य
finish_init (शून्य)
{
  संरचना initializer_चळत *p = initializer_चळत;

  /* Free the whole constructor stack of this initializer.  */
  पर्यंत (constructor_चळत)
    {
      संरचना constructor_चळत *q = constructor_चळत;
      constructor_चळत = q->next;
      XDELETE (q);
    }

  gcc_assert (!constructor_range_चळत);

  /* Pop back to the data of the outer initializer (if any).  */
  XDELETE (spelling_base);

  constructor_decl = p->decl;
  require_constant_मूल्य = p->require_constant_मूल्य;
  require_constant_elements = p->require_constant_elements;
  require_constexpr_मूल्य = p->require_constexpr_मूल्य;
  constructor_चळत = p->constructor_चळत;
  constructor_designated = p->designated;
  constructor_range_चळत = p->constructor_range_चळत;
  constructor_elements = p->elements;
  spelling = p->spelling;
  spelling_base = p->spelling_base;
  spelling_size = p->spelling_size;
  initializer_चळत = p->next;
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
  संरचना constructor_चळत *p = XNEW (संरचना constructor_चळत);

  जर (type == NULL_वृक्ष)
    type = वृक्ष_TYPE (constructor_decl);

  जर (VECTOR_TYPE_P (type)
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
  p->range_चळत = 0;
  p->outer = 0;
  p->incremental = constructor_incremental;
  p->designated = constructor_designated;
  p->zero_padding_bits = constructor_zero_padding_bits;
  p->braced_scalar = constructor_braced_scalar;
  p->designator_depth = designator_depth;
  p->next = 0;
  constructor_चळत = p;

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

  जर (RECORD_OR_UNION_TYPE_P (constructor_type))
    {
      constructor_fields = TYPE_FIELDS (constructor_type);
      /* Skip any nameless bit fields at the beginning.  */
      पर्यंत (constructor_fields != NULL_वृक्ष
	     && DECL_UNNAMED_BIT_FIELD (constructor_fields))
	constructor_fields = DECL_CHAIN (constructor_fields);

      constructor_unfilled_fields = constructor_fields;
      constructor_bit_index = bitsize_zero_गाठ;
    }
  अन्यथा जर (वृक्ष_CODE (constructor_type) == ARRAY_TYPE)
    {
      जर (TYPE_DOMAIN (constructor_type))
	{
	  constructor_max_index
	    = TYPE_MAX_मूल्य (TYPE_DOMAIN (constructor_type));

	  /* Detect non-empty initializations of zero-length arrays.  */
	  जर (constructor_max_index == NULL_वृक्ष
	      && TYPE_SIZE (constructor_type))
	    constructor_max_index = integer_minus_one_गाठ;

	  /* constructor_max_index needs to be an INTEGER_CST.  Attempts
	     to initialize VLAs with a nonempty initializer will cause a
	     proper error; avoid tree checking errors as well by setting a
	     safe value.  */
	  जर (constructor_max_index
	      && वृक्ष_CODE (constructor_max_index) != INTEGER_CST)
	    constructor_max_index = integer_minus_one_गाठ;

	  constructor_index
	    = convert (bitsizetype,
		       TYPE_MIN_मूल्य (TYPE_DOMAIN (constructor_type)));
	}
      अन्यथा
	{
	  constructor_index = bitsize_zero_गाठ;
	  constructor_max_index = NULL_वृक्ष;
	}

      constructor_unfilled_index = constructor_index;
    }
  अन्यथा जर (gnu_vector_type_p (constructor_type))
    {
      /* Vectors are like simple fixed-size arrays.  */
      constructor_max_index =
	bitsize_int (TYPE_VECTOR_SUBPARTS (constructor_type) - 1);
      constructor_index = bitsize_zero_गाठ;
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
  पर्यंत (constructor_चळत->implicit)
    {
      जर (RECORD_OR_UNION_TYPE_P (constructor_type)
	  && constructor_fields == NULL_वृक्ष)
	process_init_element (आदान_location,
			      काढा_init_level (loc, 1, braced_init_obstack,
					      last_init_list_comma),
			      सत्य, braced_init_obstack);
      अन्यथा जर (वृक्ष_CODE (constructor_type) == ARRAY_TYPE
	       && constructor_max_index
	       && वृक्ष_int_cst_lt (constructor_max_index,
				   constructor_index))
	process_init_element (आदान_location,
			      काढा_init_level (loc, 1, braced_init_obstack,
					      last_init_list_comma),
			      सत्य, braced_init_obstack);
      अन्यथा
	थांबा;
    }
}

/* Push down into a subobject, for initialization.
   If this is for an explicit set of braces, IMPLICIT is 0.
   If it is because the next element belongs at a lower level,
   IMPLICIT is 1 (or 2 if the push is because of designator list).  */

शून्य
ढकला_init_level (location_t loc, पूर्णांक implicit,
		 संरचना obstack *braced_init_obstack)
{
  संरचना constructor_चळत *p;
  वृक्ष मूल्य = NULL_वृक्ष;

  /* Unless this is an explicit brace, we need to preserve previous
     content if any.  */
  जर (implicit)
    {
      जर (RECORD_OR_UNION_TYPE_P (constructor_type) && constructor_fields)
	मूल्य = find_init_member (constructor_fields, braced_init_obstack);
      अन्यथा जर (वृक्ष_CODE (constructor_type) == ARRAY_TYPE)
	मूल्य = find_init_member (constructor_index, braced_init_obstack);
    }

  p = XNEW (संरचना constructor_चळत);
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
  p->next = constructor_चळत;
  p->range_चळत = 0;
  constructor_चळत = p;

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
  जर (!implicit)
    {
      p->range_चळत = constructor_range_चळत;
      constructor_range_चळत = 0;
      designator_depth = 0;
      designator_erroneous = 0;
    }

  /* Don't die if an entire brace-pair level is superfluous
     in the containing level.  */
  जर (constructor_type == NULL_वृक्ष)
    ;
  अन्यथा जर (RECORD_OR_UNION_TYPE_P (constructor_type))
    {
      /* Don't die if there are extra init elts at the end.  */
      जर (constructor_fields == NULL_वृक्ष)
	constructor_type = NULL_वृक्ष;
      अन्यथा
	{
	  constructor_type = वृक्ष_TYPE (constructor_fields);
	  ढकला_member_name (constructor_fields);
	  constructor_depth++;
	}
    }
  अन्यथा जर (वृक्ष_CODE (constructor_type) == ARRAY_TYPE)
    {
      constructor_type = वृक्ष_TYPE (constructor_type);
      ढकला_array_bounds (वृक्ष_to_uhwi (constructor_index));
      constructor_depth++;
    }

  जर (constructor_type == NULL_वृक्ष)
    {
      error_init (loc, "extra brace group at end of initializer");
      constructor_fields = NULL_वृक्ष;
      constructor_unfilled_fields = NULL_वृक्ष;
      परत;
    }

  जर (मूल्य && वृक्ष_CODE (मूल्य) == CONSTRUCTOR)
    {
      constructor_constant = वृक्ष_CONSTANT (मूल्य);
      constructor_simple = वृक्ष_STATIC (मूल्य);
      constructor_nonconst = CONSTRUCTOR_NON_CONST (मूल्य);
      constructor_elements = CONSTRUCTOR_ELTS (मूल्य);
      constructor_zero_padding_bits |= CONSTRUCTOR_ZERO_PADDING_BITS (मूल्य);
      जर (!vec_safe_is_empty (constructor_elements)
	  && (वृक्ष_CODE (constructor_type) == RECORD_TYPE
	      || वृक्ष_CODE (constructor_type) == ARRAY_TYPE))
	set_nonincremental_init (braced_init_obstack);
    }

  जर (implicit == 1)
    {
      found_missing_braces = 1;
      जर (initializer_चळत->missing_brace_richloc)
	initializer_चळत->missing_brace_richloc->add_fixit_घाला_before
	  (loc, "{");
    }

  जर (RECORD_OR_UNION_TYPE_P (constructor_type))
    {
      constructor_fields = TYPE_FIELDS (constructor_type);
      /* Skip any nameless bit fields at the beginning.  */
      पर्यंत (constructor_fields != NULL_वृक्ष
	     && DECL_UNNAMED_BIT_FIELD (constructor_fields))
	constructor_fields = DECL_CHAIN (constructor_fields);

      constructor_unfilled_fields = constructor_fields;
      constructor_bit_index = bitsize_zero_गाठ;
    }
  अन्यथा जर (gnu_vector_type_p (constructor_type))
    {
      /* Vectors are like simple fixed-size arrays.  */
      constructor_max_index =
	bitsize_int (TYPE_VECTOR_SUBPARTS (constructor_type) - 1);
      constructor_index = bitsize_int (0);
      constructor_unfilled_index = constructor_index;
    }
  अन्यथा जर (वृक्ष_CODE (constructor_type) == ARRAY_TYPE)
    {
      जर (TYPE_DOMAIN (constructor_type))
	{
	  constructor_max_index
	    = TYPE_MAX_मूल्य (TYPE_DOMAIN (constructor_type));

	  /* Detect non-empty initializations of zero-length arrays.  */
	  जर (constructor_max_index == NULL_वृक्ष
	      && TYPE_SIZE (constructor_type))
	    constructor_max_index = integer_minus_one_गाठ;

	  /* constructor_max_index needs to be an INTEGER_CST.  Attempts
	     to initialize VLAs will cause a proper error; avoid tree
	     checking errors as well by setting a safe value.  */
	  जर (constructor_max_index
	      && वृक्ष_CODE (constructor_max_index) != INTEGER_CST)
	    constructor_max_index = integer_minus_one_गाठ;

	  constructor_index
	    = convert (bitsizetype,
		       TYPE_MIN_मूल्य (TYPE_DOMAIN (constructor_type)));
	}
      अन्यथा
	constructor_index = bitsize_zero_गाठ;

      constructor_unfilled_index = constructor_index;
      जर (मूल्य && वृक्ष_CODE (मूल्य) == STRING_CST)
	{
	  /* We need to split the char/wchar array into individual
	     characters, so that we don't have to special case it
	     everywhere.  */
	  set_nonincremental_init_from_string (मूल्य, braced_init_obstack);
	}
    }
  अन्यथा
    {
      जर (constructor_type != error_mark_गाठ)
	{
	  जर (p->braced_scalar)
	    permerror_init (आदान_location, 0,
			    "braces around scalar initializer");
	  अन्यथा
	    warning_init (आदान_location, 0,
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

संरचना c_अभिव्यक्ती
काढा_init_level (location_t loc, पूर्णांक implicit,
		संरचना obstack *braced_init_obstack,
		location_t घाला_before)
{
  संरचना constructor_चळत *p;
  संरचना c_अभिव्यक्ती ret;
  ret.मूल्य = NULL_वृक्ष;
  ret.original_code = ERROR_MARK;
  ret.original_type = रिक्त;
  ret.m_decimal = 0;

  जर (implicit == 0)
    {
      /* When we come to an explicit close brace,
	 pop any inner levels that didn't have explicit braces.  */
      पर्यंत (constructor_चळत->implicit)
	process_init_element (आदान_location,
			      काढा_init_level (loc, 1, braced_init_obstack,
					      घाला_before),
			      सत्य, braced_init_obstack);
      gcc_assert (!constructor_range_चळत);
    }
  अन्यथा
    जर (initializer_चळत->missing_brace_richloc)
      initializer_चळत->missing_brace_richloc->add_fixit_घाला_before
	(घाला_before, "}");

  /* Now output all pending elements.  */
  constructor_incremental = 1;
  output_pending_init_elements (1, braced_init_obstack);

  p = constructor_चळत;

  /* Error for initializing a flexible array member.  */
  जर (constructor_type && constructor_fields
      && flexible_array_member_type_p (constructor_type))
    {
      /* Silently discard empty initializations.  The parser will
	 already have pedwarned for empty brackets for C17 and earlier.  */
      जर (integer_zerop (constructor_unfilled_index))
	constructor_type = NULL_वृक्ष;
      जर (constructor_type || flag_isoc23)
	{
	  gcc_assert (!constructor_type || !TYPE_SIZE (constructor_type));

	  जर (constructor_depth <= 2)
	    pedwarn_init (loc, OPT_Wpedantic,
			  "initialization of a flexible array member");
	  अन्यथा जर (constructor_type)
	    error_init (loc, "initialization of flexible array member "
			     "in a nested context");
	  अन्यथा
	    pedwarn_init (loc, OPT_Wpedantic,
			  "initialization of flexible array member "
			  "in a nested context");

	  /* We have already issued an error message for the existence
	     of a flexible array member not at the end of the structure.
	     Discard the initializer so that we do not die later.  */
	  जर (constructor_type
	      && DECL_CHAIN (constructor_fields) != NULL_वृक्ष
	      && (!p->type || वृक्ष_CODE (p->type) != UNION_TYPE))
	    constructor_type = NULL_वृक्ष;
	}
    }

  निवड (vec_safe_length (constructor_elements))
    {
    स्थिती 0:
      /* Initialization with { } counts as zeroinit.  */
      constructor_zeroinit = 1;
      थांबा;
    स्थिती 1:
      /* This might be zeroinit as well.  */
      जर (integer_zerop ((*constructor_elements)[0].मूल्य))
	constructor_zeroinit = 1;
      थांबा;
    पूर्वनिर्धारित:
      /* If the constructor has more than one element, it can't be { 0 }.  */
      constructor_zeroinit = 0;
      थांबा;
    }

  /* Warn when some structs are initialized with direct aggregation.  */
  जर (!implicit && found_missing_braces && warn_missing_braces
      && !constructor_zeroinit)
    {
      gcc_assert (initializer_चळत->missing_brace_richloc);
      warning_at (initializer_चळत->missing_brace_richloc,
		  OPT_Wmissing_braces,
		  "missing braces around initializer");
    }

  /* Warn when some struct elements are implicitly initialized to zero.  */
  जर (warn_missing_field_initializers
      && constructor_type
      && वृक्ष_CODE (constructor_type) == RECORD_TYPE
      && constructor_unfilled_fields)
    {
	/* Do not warn for flexible array members or zero-length arrays.  */
	पर्यंत (constructor_unfilled_fields
	       && (!DECL_SIZE (constructor_unfilled_fields)
		   || integer_zerop (DECL_SIZE (constructor_unfilled_fields))))
	  constructor_unfilled_fields = DECL_CHAIN (constructor_unfilled_fields);

	जर (constructor_unfilled_fields
	    /* Do not warn if this level of the initializer uses member
	       designators; it is likely to be deliberate.  */
	    && !constructor_designated
	    /* Do not warn about initializing with { 0 } or with { }.  */
	    && !constructor_zeroinit)
	  {
	    जर (warning_at (आदान_location, OPT_Wmissing_field_initializers,
			    "missing initializer for field %qD of %qT",
			    constructor_unfilled_fields,
			    constructor_type))
	      inform (DECL_SOURCE_LOCATION (constructor_unfilled_fields),
		      "%qD declared here", constructor_unfilled_fields);
	  }
    }

  /* Pad out the end of the structure.  */
  जर (p->replacement_मूल्य.मूल्य)
    /* If this closes a superfluous brace pair,
       just pass out the element between them.  */
    ret = p->replacement_मूल्य;
  अन्यथा जर (constructor_type == NULL_वृक्ष)
    ;
  अन्यथा जर (!RECORD_OR_UNION_TYPE_P (constructor_type)
	   && वृक्ष_CODE (constructor_type) != ARRAY_TYPE
	   && !gnu_vector_type_p (constructor_type))
    {
      /* A nonincremental scalar initializer--just return
	 the element, after verifying there is just one.
         Empty scalar initializers are supported in C23.  */
      जर (vec_safe_is_empty (constructor_elements))
	{
	  जर (constructor_erroneous || constructor_type == error_mark_गाठ)
	    ret.मूल्य = error_mark_गाठ;
	  अन्यथा जर (वृक्ष_CODE (constructor_type) == FUNCTION_TYPE)
	    {
	      error_init (loc, "invalid initializer");
	      ret.मूल्य = error_mark_गाठ;
	    }
	  अन्यथा जर (वृक्ष_CODE (constructor_type) == POINTER_TYPE)
	    /* Ensure this is a null pointer constant in the case of a
	       'constexpr' object initialized with {}.  */
	    ret.मूल्य = build_zero_cst (ptr_type_गाठ);
	  अन्यथा
	    ret.मूल्य = build_zero_cst (constructor_type);
	}
      अन्यथा जर (vec_safe_length (constructor_elements) != 1)
	{
	  error_init (loc, "extra elements in scalar initializer");
	  ret.मूल्य = (*constructor_elements)[0].मूल्य;
	}
      अन्यथा
	ret.मूल्य = (*constructor_elements)[0].मूल्य;
    }
  अन्यथा
    {
      जर (constructor_erroneous)
	ret.मूल्य = error_mark_गाठ;
      अन्यथा
	{
	  ret.मूल्य = build_constructor (constructor_type,
					 constructor_elements);
	  जर (constructor_constant)
	    वृक्ष_CONSTANT (ret.मूल्य) = 1;
	  जर (constructor_constant && constructor_simple)
	    वृक्ष_STATIC (ret.मूल्य) = 1;
	  जर (constructor_nonconst)
	    CONSTRUCTOR_NON_CONST (ret.मूल्य) = 1;
	  जर (constructor_zero_padding_bits)
	    CONSTRUCTOR_ZERO_PADDING_BITS (ret.मूल्य) = 1;
	}
    }

  जर (ret.मूल्य && वृक्ष_CODE (ret.मूल्य) != CONSTRUCTOR)
    {
      जर (constructor_nonconst)
	ret.original_code = C_MAYBE_CONST_अभिव्यक्ती;
      अन्यथा जर (ret.original_code == C_MAYBE_CONST_अभिव्यक्ती)
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
  जर (!p->implicit)
    constructor_range_चळत = p->range_चळत;
  RESTORE_SPELLING_DEPTH (constructor_depth);

  constructor_चळत = p->next;
  XDELETE (p);

  जर (ret.मूल्य == NULL_वृक्ष && constructor_चळत == 0)
    ret.मूल्य = error_mark_गाठ;
  परत ret;
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
  जर (constructor_type == NULL_वृक्ष || constructor_type == error_mark_गाठ)
    परत सत्य;

  /* If there were errors in this designator list already, bail out
     silently.  */
  जर (designator_erroneous)
    परत सत्य;

  /* Likewise for an initializer for a variable-size type.  Those are
     diagnosed in the parser, except for empty initializer braces.  */
  जर (COMPLETE_TYPE_P (constructor_type)
      && वृक्ष_CODE (TYPE_SIZE (constructor_type)) != INTEGER_CST)
    परत सत्य;

  जर (!designator_depth)
    {
      gcc_assert (!constructor_range_चळत);

      /* Designator list starts at the level of closest explicit
	 braces.  */
      पर्यंत (constructor_चळत->implicit)
	process_init_element (आदान_location,
			      काढा_init_level (loc, 1, braced_init_obstack,
					      last_init_list_comma),
			      सत्य, braced_init_obstack);
      constructor_designated = 1;
      परत असत्य;
    }

  निवड (वृक्ष_CODE (constructor_type))
    {
    स्थिती  RECORD_TYPE:
    स्थिती  UNION_TYPE:
      subtype = वृक्ष_TYPE (constructor_fields);
      जर (subtype != error_mark_गाठ)
	subtype = TYPE_MAIN_VARIANT (subtype);
      थांबा;
    स्थिती ARRAY_TYPE:
      subtype = TYPE_MAIN_VARIANT (वृक्ष_TYPE (constructor_type));
      थांबा;
    पूर्वनिर्धारित:
      gcc_unreachable ();
    }

  subcode = वृक्ष_CODE (subtype);
  जर (array && subcode != ARRAY_TYPE)
    {
      error_init (loc, "array index in non-array initializer");
      परत सत्य;
    }
  अन्यथा जर (!array && subcode != RECORD_TYPE && subcode != UNION_TYPE)
    {
      error_init (loc, "field name not in record or union initializer");
      परत सत्य;
    }

  constructor_designated = 1;
  finish_implicit_inits (loc, braced_init_obstack);
  ढकला_init_level (loc, 2, braced_init_obstack);
  परत असत्य;
}

/* If there are range designators in designator list, push a new designator
   to constructor_range_stack.  RANGE_END is end of such stack range or
   NULL_TREE if there is no range designator at this level.  */

स्थिर शून्य
ढकला_range_चळत (वृक्ष range_end, संरचना obstack * braced_init_obstack)
{
  संरचना constructor_range_चळत *p;

  p = (संरचना constructor_range_चळत *)
    obstack_alloc (braced_init_obstack,
		   आकार (संरचना constructor_range_चळत));
  p->prev = constructor_range_चळत;
  p->next = 0;
  p->fields = constructor_fields;
  p->range_start = constructor_index;
  p->index = constructor_index;
  p->चळत = constructor_चळत;
  p->range_end = range_end;
  जर (constructor_range_चळत)
    constructor_range_चळत->next = p;
  constructor_range_चळत = p;
}

/* Within an array initializer, specify the next index to be initialized.
   FIRST is that index.  If LAST is nonzero, then initialize a range
   of indices, running from FIRST through LAST.  */

शून्य
set_init_index (location_t loc, वृक्ष first, वृक्ष last,
		संरचना obstack *braced_init_obstack)
{
  जर (set_designator (loc, सत्य, braced_init_obstack))
    परत;

  designator_erroneous = 1;

  जर (!INTEGRAL_TYPE_P (वृक्ष_TYPE (first))
      || (last && !INTEGRAL_TYPE_P (वृक्ष_TYPE (last))))
    {
      error_init (loc, "array index in initializer not of integer type");
      परत;
    }

  जर (वृक्ष_CODE (first) != INTEGER_CST)
    {
      first = c_fully_fold (first, असत्य, रिक्त);
      जर (वृक्ष_CODE (first) == INTEGER_CST)
	pedwarn_init (loc, OPT_Wpedantic,
		      "array index in initializer is not "
		      "an integer constant expression");
    }

  जर (last && वृक्ष_CODE (last) != INTEGER_CST)
    {
      last = c_fully_fold (last, असत्य, रिक्त);
      जर (वृक्ष_CODE (last) == INTEGER_CST)
	pedwarn_init (loc, OPT_Wpedantic,
		      "array index in initializer is not "
		      "an integer constant expression");
    }

  जर (वृक्ष_CODE (first) != INTEGER_CST)
    error_init (loc, "nonconstant array index in initializer");
  अन्यथा जर (last != NULL_वृक्ष && वृक्ष_CODE (last) != INTEGER_CST)
    error_init (loc, "nonconstant array index in initializer");
  अन्यथा जर (वृक्ष_CODE (constructor_type) != ARRAY_TYPE)
    error_init (loc, "array index in non-array initializer");
  अन्यथा जर (वृक्ष_int_cst_sgn (first) == -1)
    error_init (loc, "array index in initializer exceeds array bounds");
  अन्यथा जर (constructor_max_index
	   && वृक्ष_int_cst_lt (constructor_max_index, first))
    error_init (loc, "array index in initializer exceeds array bounds");
  अन्यथा
    {
      constant_expression_warning (first);
      जर (last)
	constant_expression_warning (last);
      constructor_index = convert (bitsizetype, first);
      जर (वृक्ष_int_cst_lt (constructor_index, first))
	{
	  constructor_index = copy_गाठ (constructor_index);
	  वृक्ष_OVERFLOW (constructor_index) = 1;
	}

      जर (last)
	{
	  जर (वृक्ष_int_cst_equal (first, last))
	    last = NULL_वृक्ष;
	  अन्यथा जर (वृक्ष_int_cst_lt (last, first))
	    {
	      error_init (loc, "empty index range in initializer");
	      last = NULL_वृक्ष;
	    }
	  अन्यथा
	    {
	      last = convert (bitsizetype, last);
	      जर (constructor_max_index != NULL_वृक्ष
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
      जर (constructor_range_चळत || last)
	ढकला_range_चळत (last, braced_init_obstack);
    }
}

/* Within a struct initializer, specify the next field to be initialized.  */

शून्य
set_init_label (location_t loc, वृक्ष fieldname, location_t fieldname_loc,
		संरचना obstack *braced_init_obstack)
{
  वृक्ष field;

  जर (set_designator (loc, असत्य, braced_init_obstack))
    परत;

  designator_erroneous = 1;

  जर (!RECORD_OR_UNION_TYPE_P (constructor_type))
    {
      error_init (loc, "field name not in record or union initializer");
      परत;
    }

  field = lookup_field (constructor_type, fieldname);

  जर (field == NULL_वृक्ष)
    {
      वृक्ष guessed_id = lookup_field_fuzzy (constructor_type, fieldname);
      जर (guessed_id)
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
    करा
      {
	constructor_fields = वृक्ष_मूल्य (field);
	designator_depth++;
	designator_erroneous = 0;
	जर (constructor_range_चळत)
	  ढकला_range_चळत (NULL_वृक्ष, braced_init_obstack);
	field = वृक्ष_CHAIN (field);
	जर (field)
	  {
	    जर (set_designator (loc, असत्य, braced_init_obstack))
	      परत;
	  }
      }
    पर्यंत (field != NULL_वृक्ष);
}

/* Helper function for add_pending_init.  Find inorder successor of P
   in AVL tree.  */
स्थिर संरचना init_गाठ *
init_गाठ_successor (संरचना init_गाठ *p)
{
  संरचना init_गाठ *r;
  जर (p->उजवा)
    {
      r = p->उजवा;
      पर्यंत (r->डावा)
	r = r->डावा;
      परत r;
    }
  r = p->parent;
  पर्यंत (r && p == r->उजवा)
    {
      p = r;
      r = r->parent;
    }
  परत r;
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
  संरचना init_गाठ *p, **q, *r;

  q = &constructor_pending_elts;
  p = 0;

  जर (वृक्ष_CODE (constructor_type) == ARRAY_TYPE)
    {
      पर्यंत (*q != 0)
	{
	  p = *q;
	  जर (वृक्ष_int_cst_lt (purpose, p->purpose))
	    q = &p->डावा;
	  अन्यथा जर (वृक्ष_int_cst_lt (p->purpose, purpose))
	    {
	      जर (वृक्ष_CODE (p->मूल्य) != RAW_DATA_CST
		  || (p->उजवा
		      && वृक्ष_int_cst_le (p->उजवा->purpose, purpose)))
		q = &p->उजवा;
	      अन्यथा
		{
		  widest_int pp = wi::to_widest (p->purpose);
		  widest_int pw = wi::to_widest (purpose);
		  जर (pp + RAW_DATA_LENGTH (p->मूल्य) <= pw)
		    q = &p->उजवा;
		  अन्यथा
		    {
		      /* Override which should split the old RAW_DATA_CST
			 into 2 or 3 pieces.  */
		      जर (!implicit && warn_override_init)
			warning_init (loc, OPT_Woverride_init,
				      "initialized field overwritten");
		      अचिन्हित HOST_WIDE_INT start = (pw - pp).to_uhwi ();
		      अचिन्हित HOST_WIDE_INT len = 1;
		      जर (वृक्ष_CODE (मूल्य) == RAW_DATA_CST)
			len = RAW_DATA_LENGTH (मूल्य);
		      अचिन्हित HOST_WIDE_INT end = 0;
		      अचिन्हित plen = RAW_DATA_LENGTH (p->मूल्य);
		      gcc_checking_assert (start < plen && start);
		      जर (plen - start > len)
			end = plen - start - len;
		      वृक्ष v = p->मूल्य;
		      वृक्ष origtype = p->origtype;
		      जर (start == 1)
			p->मूल्य = build_int_cst (वृक्ष_TYPE (v),
						  RAW_DATA_UCHAR_ELT (v, 0));
		      अन्यथा
			{
			  p->मूल्य = v;
			  जर (end > 1)
			    v = copy_गाठ (v);
			  RAW_DATA_LENGTH (p->मूल्य) = start;
			}
		      जर (end)
			{
			  वृक्ष epurpose
			    = size_binop (PLUS_अभिव्यक्ती, purpose,
					  bitsize_int (len));
			  जर (end > 1)
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
		      सुरूठेवा;
		    }
		}
	    }
	  अन्यथा
	    {
	      जर (वृक्ष_CODE (p->मूल्य) == RAW_DATA_CST
		  && (RAW_DATA_LENGTH (p->मूल्य)
		      > (वृक्ष_CODE (मूल्य) == RAW_DATA_CST
			 ? RAW_DATA_LENGTH (मूल्य) : 1)))
		{
		  /* Override which should split the old RAW_DATA_CST
		     into 2 pieces.  */
		  जर (!implicit && warn_override_init)
		    warning_init (loc, OPT_Woverride_init,
				  "initialized field overwritten");
		  अचिन्हित HOST_WIDE_INT len = 1;
		  जर (वृक्ष_CODE (मूल्य) == RAW_DATA_CST)
		    len = RAW_DATA_LENGTH (मूल्य);
		  जर ((अचिन्हित) RAW_DATA_LENGTH (p->मूल्य) > len + 1)
		    {
		      RAW_DATA_LENGTH (p->मूल्य) -= len;
		      RAW_DATA_POINTER (p->मूल्य) += len;
		    }
		  अन्यथा
		    {
		      अचिन्हित पूर्णांक l = RAW_DATA_LENGTH (p->मूल्य) - 1;
		      p->मूल्य
			= build_int_cst (वृक्ष_TYPE (p->मूल्य),
					 RAW_DATA_UCHAR_ELT (p->मूल्य, l));
		    }
		  p->purpose = size_binop (PLUS_अभिव्यक्ती, p->purpose,
					   bitsize_int (len));
		  सुरूठेवा;
		}
	      जर (वृक्ष_CODE (मूल्य) == RAW_DATA_CST)
		{
		handle_raw_data:
		  /* RAW_DATA_CST value might overlap various further
		     prior initval entries.  Find out how many.  */
		  अचिन्हित cnt = 0;
		  widest_int w
		    = wi::to_widest (purpose) + RAW_DATA_LENGTH (मूल्य);
		  संरचना init_गाठ *r = p, *last = रिक्त;
		  तार्किक override_init = warn_override_init;
		  पर्यंत ((r = init_गाठ_successor (r))
			 && wi::to_widest (r->purpose) < w)
		    {
		      ++cnt;
		      जर (वृक्ष_SIDE_EFFECTS (r->मूल्य))
			warning_init (loc, OPT_Woverride_init_side_effects,
				      "initialized field with side-effects "
				      "overwritten");
		      अन्यथा जर (override_init)
			{
			  warning_init (loc, OPT_Woverride_init,
					"initialized field overwritten");
			  override_init = असत्य;
			}
		      last = r;
		    }
		  जर (cnt)
		    {
		      जर (वृक्ष_CODE (last->मूल्य) == RAW_DATA_CST
			  && (wi::to_widest (last->purpose)
			      + RAW_DATA_LENGTH (last->मूल्य) > w))
			{
			  /* The last overlapping prior initval overlaps
			     only partially.  Shrink it and decrease cnt.  */
			  अचिन्हित पूर्णांक l = (wi::to_widest (last->purpose)
					    + RAW_DATA_LENGTH (last->मूल्य)
					    - w).to_uhwi ();
			  --cnt;
			  RAW_DATA_LENGTH (last->मूल्य) -= l;
			  RAW_DATA_POINTER (last->मूल्य) += l;
			  जर (RAW_DATA_LENGTH (last->मूल्य) == 1)
			    last->मूल्य
			      = build_int_cst (वृक्ष_TYPE (last->मूल्य),
					       RAW_DATA_UCHAR_ELT (last->मूल्य,
								   0));
			  last->purpose
			    = size_binop (PLUS_अभिव्यक्ती, last->purpose,
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
		      स्थिरांक अचिन्हित अक्षर *s
			= &RAW_DATA_UCHAR_ELT (मूल्य, RAW_DATA_LENGTH (मूल्य));
		      अचिन्हित पूर्णांक o = RAW_DATA_LENGTH (मूल्य);
		      साठी (r = p; cnt--; ++o, ++s)
			{
			  r = init_गाठ_successor (r);
			  r->purpose = size_binop (PLUS_अभिव्यक्ती, purpose,
						   bitsize_int (o));
			  r->मूल्य = build_int_cst (वृक्ष_TYPE (मूल्य), *s);
			  r->origtype = origtype;
			}
		      जर (RAW_DATA_LENGTH (मूल्य) == 1)
			मूल्य = build_int_cst (वृक्ष_TYPE (मूल्य),
					       RAW_DATA_UCHAR_ELT (मूल्य, 0));
		    }
		}
	      जर (!implicit)
		{
		  जर (वृक्ष_SIDE_EFFECTS (p->मूल्य))
		    warning_init (loc, OPT_Woverride_init_side_effects,
				  "initialized field with side-effects "
				  "overwritten");
		  अन्यथा जर (warn_override_init)
		    warning_init (loc, OPT_Woverride_init,
				  "initialized field overwritten");
		}
	      p->मूल्य = मूल्य;
	      p->origtype = origtype;
	      परत;
	    }
	}
      जर (वृक्ष_CODE (मूल्य) == RAW_DATA_CST && p)
	{
	  संरचना init_गाठ *r;
	  जर (q == &p->डावा)
	    r = p;
	  अन्यथा
	    r = init_गाठ_successor (p);
	  जर (r && wi::to_widest (r->purpose) < (wi::to_widest (purpose)
						 + RAW_DATA_LENGTH (मूल्य)))
	    {
	      /* Overlap with at least one prior initval in the range but
		 not at the start.  */
	      p = r;
	      p->purpose = purpose;
	      जा handle_raw_data;
	    }
	}
    }
  अन्यथा
    {
      वृक्ष bitpos;

      bitpos = bit_position (purpose);
      पर्यंत (*q != रिक्त)
	{
	  p = *q;
	  जर (वृक्ष_int_cst_lt (bitpos, bit_position (p->purpose)))
	    q = &p->डावा;
	  अन्यथा जर (p->purpose != purpose)
	    q = &p->उजवा;
	  अन्यथा
	    {
	      जर (!implicit)
		{
		  जर (वृक्ष_SIDE_EFFECTS (p->मूल्य))
		    warning_init (loc, OPT_Woverride_init_side_effects,
				  "initialized field with side-effects "
				  "overwritten");
		  अन्यथा जर (warn_override_init)
		    warning_init (loc, OPT_Woverride_init,
				  "initialized field overwritten");
		}
	      p->मूल्य = मूल्य;
	      p->origtype = origtype;
	      परत;
	    }
	}
    }

  r = (संरचना init_गाठ *) obstack_alloc (braced_init_obstack,
					  आकार (संरचना init_गाठ));
  r->purpose = purpose;
  r->मूल्य = मूल्य;
  r->origtype = origtype;

  *q = r;
  r->parent = p;
  r->डावा = 0;
  r->उजवा = 0;
  r->balance = 0;

  पर्यंत (p)
    {
      संरचना init_गाठ *s;

      जर (r == p->डावा)
	{
	  जर (p->balance == 0)
	    p->balance = -1;
	  अन्यथा जर (p->balance < 0)
	    {
	      जर (r->balance < 0)
		{
		  /* L rotation.  */
		  p->डावा = r->उजवा;
		  जर (p->डावा)
		    p->डावा->parent = p;
		  r->उजवा = p;

		  p->balance = 0;
		  r->balance = 0;

		  s = p->parent;
		  p->parent = r;
		  r->parent = s;
		  जर (s)
		    {
		      जर (s->डावा == p)
			s->डावा = r;
		      अन्यथा
			s->उजवा = r;
		    }
		  अन्यथा
		    constructor_pending_elts = r;
		}
	      अन्यथा
		{
		  /* LR rotation.  */
		  संरचना init_गाठ *t = r->उजवा;

		  r->उजवा = t->डावा;
		  जर (r->उजवा)
		    r->उजवा->parent = r;
		  t->डावा = r;

		  p->डावा = t->उजवा;
		  जर (p->डावा)
		    p->डावा->parent = p;
		  t->उजवा = p;

		  p->balance = t->balance < 0;
		  r->balance = -(t->balance > 0);
		  t->balance = 0;

		  s = p->parent;
		  p->parent = t;
		  r->parent = t;
		  t->parent = s;
		  जर (s)
		    {
		      जर (s->डावा == p)
			s->डावा = t;
		      अन्यथा
			s->उजवा = t;
		    }
		  अन्यथा
		    constructor_pending_elts = t;
		}
	      थांबा;
	    }
	  अन्यथा
	    {
	      /* p->balance == +1; growth of left side balances the node.  */
	      p->balance = 0;
	      थांबा;
	    }
	}
      अन्यथा /* r == p->right */
	{
	  जर (p->balance == 0)
	    /* Growth propagation from right side.  */
	    p->balance++;
	  अन्यथा जर (p->balance > 0)
	    {
	      जर (r->balance > 0)
		{
		  /* R rotation.  */
		  p->उजवा = r->डावा;
		  जर (p->उजवा)
		    p->उजवा->parent = p;
		  r->डावा = p;

		  p->balance = 0;
		  r->balance = 0;

		  s = p->parent;
		  p->parent = r;
		  r->parent = s;
		  जर (s)
		    {
		      जर (s->डावा == p)
			s->डावा = r;
		      अन्यथा
			s->उजवा = r;
		    }
		  अन्यथा
		    constructor_pending_elts = r;
		}
	      अन्यथा /* r->balance == -1 */
		{
		  /* RL rotation */
		  संरचना init_गाठ *t = r->डावा;

		  r->डावा = t->उजवा;
		  जर (r->डावा)
		    r->डावा->parent = r;
		  t->उजवा = r;

		  p->उजवा = t->डावा;
		  जर (p->उजवा)
		    p->उजवा->parent = p;
		  t->डावा = p;

		  r->balance = (t->balance < 0);
		  p->balance = -(t->balance > 0);
		  t->balance = 0;

		  s = p->parent;
		  p->parent = t;
		  r->parent = t;
		  t->parent = s;
		  जर (s)
		    {
		      जर (s->डावा == p)
			s->डावा = t;
		      अन्यथा
			s->उजवा = t;
		    }
		  अन्यथा
		    constructor_pending_elts = t;
		}
	      थांबा;
	    }
	  अन्यथा
	    {
	      /* p->balance == -1; growth of right side balances the node.  */
	      p->balance = 0;
	      थांबा;
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

  जर (वृक्ष_CODE (constructor_type) != RECORD_TYPE
      && वृक्ष_CODE (constructor_type) != ARRAY_TYPE)
    परत;

  FOR_EACH_CONSTRUCTOR_ELT (constructor_elements, ix, index, मूल्य)
    add_pending_init (आदान_location, index, मूल्य, NULL_वृक्ष, सत्य,
		      braced_init_obstack);
  constructor_elements = रिक्त;
  जर (वृक्ष_CODE (constructor_type) == RECORD_TYPE)
    {
      constructor_unfilled_fields = TYPE_FIELDS (constructor_type);
      /* Skip any nameless bit fields at the beginning.  */
      पर्यंत (constructor_unfilled_fields != NULL_वृक्ष
	     && DECL_UNNAMED_BIT_FIELD (constructor_unfilled_fields))
	constructor_unfilled_fields = वृक्ष_CHAIN (constructor_unfilled_fields);

    }
  अन्यथा जर (वृक्ष_CODE (constructor_type) == ARRAY_TYPE)
    {
      जर (TYPE_DOMAIN (constructor_type))
	constructor_unfilled_index
	  = convert (bitsizetype,
		     TYPE_MIN_मूल्य (TYPE_DOMAIN (constructor_type)));
      अन्यथा
	constructor_unfilled_index = bitsize_zero_गाठ;
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
  स्थिरांक अक्षर *p, *end;
  पूर्णांक byte, wchar_bytes, charwidth, bitpos;

  gcc_assert (वृक्ष_CODE (constructor_type) == ARRAY_TYPE);

  wchar_bytes = TYPE_PRECISION (वृक्ष_TYPE (वृक्ष_TYPE (str))) / BITS_PER_UNIT;
  charwidth = TYPE_PRECISION (char_type_गाठ);
  gcc_assert ((माप_प्रकार) wchar_bytes * charwidth
	      <= ARRAY_SIZE (val) * HOST_BITS_PER_WIDE_INT);
  type = वृक्ष_TYPE (constructor_type);
  p = वृक्ष_STRING_POINTER (str);
  end = p + वृक्ष_STRING_LENGTH (str);

  साठी (purpose = bitsize_zero_गाठ;
       p < end
       && !(constructor_max_index
	    && वृक्ष_int_cst_lt (constructor_max_index, purpose));
       purpose = size_binop (PLUS_अभिव्यक्ती, purpose, bitsize_one_गाठ))
    {
      जर (wchar_bytes == 1)
	{
	  val[0] = (अचिन्हित अक्षर) *p++;
	  val[1] = 0;
	}
      अन्यथा
	{
	  val[1] = 0;
	  val[0] = 0;
	  साठी (byte = 0; byte < wchar_bytes; byte++)
	    {
	      जर (BYTES_BIG_ENDIAN)
		bitpos = (wchar_bytes - byte - 1) * charwidth;
	      अन्यथा
		bitpos = byte * charwidth;
	      val[bitpos / HOST_BITS_PER_WIDE_INT]
		|= ((अचिन्हित HOST_WIDE_INT) ((अचिन्हित अक्षर) *p++))
		   << (bitpos % HOST_BITS_PER_WIDE_INT);
	    }
	}

      जर (!TYPE_UNSIGNED (type))
	{
	  bitpos = ((wchar_bytes - 1) * charwidth) + HOST_BITS_PER_CHAR;
	  जर (bitpos < HOST_BITS_PER_WIDE_INT)
	    {
	      जर (val[0] & (HOST_WIDE_INT_1 << (bitpos - 1)))
		{
		  val[0] |= HOST_WIDE_INT_M1U << bitpos;
		  val[1] = -1;
		}
	    }
	  अन्यथा जर (bitpos == HOST_BITS_PER_WIDE_INT)
	    {
	      जर (val[0] < 0)
		val[1] = -1;
	    }
	  अन्यथा जर (val[1] & (HOST_WIDE_INT_1
			     << (bitpos - 1 - HOST_BITS_PER_WIDE_INT)))
	    val[1] |= HOST_WIDE_INT_M1U << (bitpos - HOST_BITS_PER_WIDE_INT);
	}

      मूल्य = wide_int_to_वृक्ष (type,
				wide_int::from_array (val, 2,
						      HOST_BITS_PER_WIDE_INT * 2));
      add_pending_init (आदान_location, purpose, मूल्य, NULL_वृक्ष, सत्य,
                        braced_init_obstack);
    }

  constructor_incremental = 0;
}

/* Return value of FIELD in pending initializer or NULL_TREE if the field was
   not initialized yet.  */

स्थिर वृक्ष
find_init_member (वृक्ष field, संरचना obstack * braced_init_obstack)
{
  संरचना init_गाठ *p;

  जर (वृक्ष_CODE (constructor_type) == ARRAY_TYPE)
    {
      जर (constructor_incremental
	  && वृक्ष_int_cst_lt (field, constructor_unfilled_index))
	set_nonincremental_init (braced_init_obstack);

      p = constructor_pending_elts;
      पर्यंत (p)
	{
	  जर (वृक्ष_int_cst_lt (field, p->purpose))
	    p = p->डावा;
	  अन्यथा जर (वृक्ष_int_cst_lt (p->purpose, field))
	    p = p->उजवा;
	  अन्यथा
	    परत p->मूल्य;
	}
    }
  अन्यथा जर (वृक्ष_CODE (constructor_type) == RECORD_TYPE)
    {
      वृक्ष bitpos = bit_position (field);

      जर (constructor_incremental
	  && (!constructor_unfilled_fields
	      || वृक्ष_int_cst_lt (bitpos,
				  bit_position (constructor_unfilled_fields))))
	set_nonincremental_init (braced_init_obstack);

      p = constructor_pending_elts;
      पर्यंत (p)
	{
	  जर (field == p->purpose)
	    परत p->मूल्य;
	  अन्यथा जर (वृक्ष_int_cst_lt (bitpos, bit_position (p->purpose)))
	    p = p->डावा;
	  अन्यथा
	    p = p->उजवा;
	}
    }
  अन्यथा जर (वृक्ष_CODE (constructor_type) == UNION_TYPE)
    {
      जर (!vec_safe_is_empty (constructor_elements)
	  && (constructor_elements->last ().index == field))
	परत constructor_elements->last ().मूल्य;
    }
  परत NULL_वृक्ष;
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
  तार्किक npc, int_const_अभिव्यक्ती, arith_const_अभिव्यक्ती;

  जर (type == error_mark_गाठ || मूल्य == error_mark_गाठ)
    {
      constructor_erroneous = 1;
      परत;
    }
  जर (वृक्ष_CODE (वृक्ष_TYPE (मूल्य)) == ARRAY_TYPE
      && (वृक्ष_CODE (मूल्य) == STRING_CST
	  || वृक्ष_CODE (मूल्य) == COMPOUND_LITERAL_अभिव्यक्ती)
      && !(वृक्ष_CODE (मूल्य) == STRING_CST
	   && वृक्ष_CODE (type) == ARRAY_TYPE
	   && INTEGRAL_TYPE_P (वृक्ष_TYPE (type)))
      && !comptypes (TYPE_MAIN_VARIANT (वृक्ष_TYPE (मूल्य)),
		     TYPE_MAIN_VARIANT (type)))
    मूल्य = array_to_pointer_conversion (आदान_location, मूल्य);

  जर (वृक्ष_CODE (मूल्य) == COMPOUND_LITERAL_अभिव्यक्ती
      && require_constant_मूल्य && pending)
    {
      /* As an extension, allow initializing objects with static storage
	 duration with compound literals (which are then treated just as
	 the brace enclosed list they contain).  */
      जर (flag_isoc99)
	pedwarn_init (loc, OPT_Wpedantic, "initializer element is not "
		      "constant");
      वृक्ष decl = COMPOUND_LITERAL_अभिव्यक्ती_DECL (मूल्य);
      मूल्य = DECL_INITIAL (decl);
    }

  npc = null_pointer_constant_p (मूल्य);
  int_const_अभिव्यक्ती = (वृक्ष_CODE (मूल्य) == INTEGER_CST
		    && !वृक्ष_OVERFLOW (मूल्य)
		    && INTEGRAL_TYPE_P (वृक्ष_TYPE (मूल्य)));
  /* Not fully determined before folding.  */
  arith_const_अभिव्यक्ती = सत्य;
  जर (वृक्ष_CODE (मूल्य) == EXCESS_PRECISION_अभिव्यक्ती)
    {
      semantic_type = वृक्ष_TYPE (मूल्य);
      मूल्य = वृक्ष_OPERAND (मूल्य, 0);
    }
  मूल्य = c_fully_fold (मूल्य, require_constant_मूल्य, &maybe_const);
  /* TODO: this may not detect all cases of expressions folding to
     constants that are not arithmetic constant expressions.  */
  जर (!maybe_const)
    arith_const_अभिव्यक्ती = असत्य;
  अन्यथा जर (!INTEGRAL_TYPE_P (वृक्ष_TYPE (मूल्य))
	   && वृक्ष_CODE (वृक्ष_TYPE (मूल्य)) != REAL_TYPE
	   && वृक्ष_CODE (वृक्ष_TYPE (मूल्य)) != COMPLEX_TYPE)
    arith_const_अभिव्यक्ती = असत्य;
  अन्यथा जर (वृक्ष_CODE (मूल्य) != INTEGER_CST
	   && वृक्ष_CODE (मूल्य) != REAL_CST
	   && वृक्ष_CODE (मूल्य) != COMPLEX_CST
	   && वृक्ष_CODE (मूल्य) != RAW_DATA_CST)
    arith_const_अभिव्यक्ती = असत्य;
  अन्यथा जर (वृक्ष_OVERFLOW (मूल्य))
    arith_const_अभिव्यक्ती = असत्य;

  जर (मूल्य == error_mark_गाठ)
    constructor_erroneous = 1;
  अन्यथा जर (!वृक्ष_CONSTANT (मूल्य))
    constructor_constant = 0;
  अन्यथा जर (!initializer_constant_valid_p (मूल्य,
					  वृक्ष_TYPE (मूल्य),
					  AGGREGATE_TYPE_P (constructor_type)
					  && TYPE_REVERSE_STORAGE_ORDER
					     (constructor_type))
	   || (RECORD_OR_UNION_TYPE_P (constructor_type)
	       && DECL_C_BIT_FIELD (field)
	       && वृक्ष_CODE (मूल्य) != INTEGER_CST))
    constructor_simple = 0;
  जर (!maybe_const)
    constructor_nonconst = 1;

  /* Digest the initializer and issue any errors about incompatible
     types before issuing errors about non-constant initializers.  */
  वृक्ष new_मूल्य = मूल्य;
  जर (semantic_type)
    new_मूल्य = build1 (EXCESS_PRECISION_अभिव्यक्ती, semantic_type, मूल्य);
  /* In the case of braces around a scalar initializer, the result of
     this initializer processing goes through digest_init again at the
     outer level.  In the case of a constexpr initializer for a
     pointer, avoid converting a null pointer constant to something
     that is not a null pointer constant to avoid a spurious error
     from that second processing.  */
  जर (!require_constexpr_मूल्य
      || !npc
      || वृक्ष_CODE (constructor_type) != POINTER_TYPE)
    new_मूल्य = digest_init (loc,
			     RECORD_OR_UNION_TYPE_P (constructor_type)
			     ? field : constructor_fields
			     ? constructor_fields : constructor_decl,
			     type, new_मूल्य, origtype, npc,
			     int_const_अभिव्यक्ती, arith_const_अभिव्यक्ती, strict_string,
			     require_constant_मूल्य, require_constexpr_मूल्य);
  जर (new_मूल्य == error_mark_गाठ)
    {
      constructor_erroneous = 1;
      परत;
    }
  जर (require_constant_मूल्य || require_constant_elements)
    constant_expression_warning (new_मूल्य);

  /* Proceed to check the constness of the original initializer.  */
  जर (!initializer_constant_valid_p (मूल्य, वृक्ष_TYPE (मूल्य)))
    {
      जर (require_constant_मूल्य)
	{
	  error_init (loc, "initializer element is not constant");
	  मूल्य = error_mark_गाठ;
	}
      अन्यथा जर (require_constant_elements)
	pedwarn (loc, OPT_Wpedantic,
		 "initializer element is not computable at load time");
    }
  अन्यथा जर (!maybe_const
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
  जर (warn_cxx_compat
      && field != NULL_वृक्ष
      && वृक्ष_CODE (field) == FIELD_DECL
      && DECL_BIT_FIELD_TYPE (field) != NULL_वृक्ष
      && (TYPE_MAIN_VARIANT (DECL_BIT_FIELD_TYPE (field))
	  != TYPE_MAIN_VARIANT (type))
      && वृक्ष_CODE (DECL_BIT_FIELD_TYPE (field)) == ENUMERAL_TYPE)
    {
      वृक्ष checktype = origtype != NULL_वृक्ष ? origtype : वृक्ष_TYPE (मूल्य);
      जर (checktype != error_mark_गाठ
	  && (TYPE_MAIN_VARIANT (checktype)
	      != TYPE_MAIN_VARIANT (DECL_BIT_FIELD_TYPE (field))))
	warning_init (loc, OPT_Wc___compat,
		      "enum conversion in initialization is invalid in C++");
    }

  /* If this field is empty and does not have side effects (and is not at
     the end of structure), don't do anything other than checking the
     initializer.  */
  जर (field
      && (वृक्ष_TYPE (field) == error_mark_गाठ
	  || (COMPLETE_TYPE_P (वृक्ष_TYPE (field))
	      && integer_zerop (TYPE_SIZE (वृक्ष_TYPE (field)))
	      && !वृक्ष_SIDE_EFFECTS (new_मूल्य)
	      && (वृक्ष_CODE (constructor_type) == ARRAY_TYPE
		  || DECL_CHAIN (field)))))
    परत;

  /* Finally, set VALUE to the initializer value digested above.  */
  मूल्य = new_मूल्य;

  /* If this element doesn't come next in sequence,
     put it on constructor_pending_elts.  */
  जर (वृक्ष_CODE (constructor_type) == ARRAY_TYPE
      && (!constructor_incremental
	  || !वृक्ष_int_cst_equal (field, constructor_unfilled_index)
	  || (वृक्ष_CODE (मूल्य) == RAW_DATA_CST
	      && constructor_pending_elts
	      && pending)))
    {
      जर (constructor_incremental
	  && (वृक्ष_int_cst_lt (field, constructor_unfilled_index)
	      || (वृक्ष_CODE (मूल्य) == RAW_DATA_CST
		  && constructor_pending_elts
		  && pending)))
	set_nonincremental_init (braced_init_obstack);

      add_pending_init (loc, field, मूल्य, origtype, implicit,
			braced_init_obstack);
      परत;
    }
  अन्यथा जर (वृक्ष_CODE (constructor_type) == RECORD_TYPE
	   && (!constructor_incremental
	       || field != constructor_unfilled_fields))
    {
      /* We do this for records but not for unions.  In a union,
	 no matter which field is specified, it can be initialized
	 right away since it starts at the beginning of the union.  */
      जर (constructor_incremental)
	{
	  जर (!constructor_unfilled_fields)
	    set_nonincremental_init (braced_init_obstack);
	  अन्यथा
	    {
	      वृक्ष bitpos, unfillpos;

	      bitpos = bit_position (field);
	      unfillpos = bit_position (constructor_unfilled_fields);

	      जर (वृक्ष_int_cst_lt (bitpos, unfillpos))
		set_nonincremental_init (braced_init_obstack);
	    }
	}

      add_pending_init (loc, field, मूल्य, origtype, implicit,
			braced_init_obstack);
      परत;
    }
  अन्यथा जर (वृक्ष_CODE (constructor_type) == UNION_TYPE
	   && !vec_safe_is_empty (constructor_elements))
    {
      जर (!implicit)
	{
	  जर (वृक्ष_SIDE_EFFECTS (constructor_elements->last ().मूल्य))
	    warning_init (loc, OPT_Woverride_init_side_effects,
			  "initialized field with side-effects overwritten");
	  अन्यथा जर (warn_override_init)
	    warning_init (loc, OPT_Woverride_init,
			  "initialized field overwritten");
	}

      /* We can have just one union field set.  */
      constructor_elements = रिक्त;
    }

  /* Otherwise, output this element either to
     constructor_elements or to the assembler file.  */

  constructor_elt celt = {field, मूल्य};
  vec_safe_ढकला (constructor_elements, celt);

  /* Advance the variable that indicates sequential elements output.  */
  जर (वृक्ष_CODE (constructor_type) == ARRAY_TYPE)
    {
      वृक्ष inc = bitsize_one_गाठ;
      जर (मूल्य && वृक्ष_CODE (मूल्य) == RAW_DATA_CST)
	inc = bitsize_int (RAW_DATA_LENGTH (मूल्य));
      constructor_unfilled_index
	= size_binop_loc (आदान_location, PLUS_अभिव्यक्ती,
			  constructor_unfilled_index, inc);
    }
  अन्यथा जर (वृक्ष_CODE (constructor_type) == RECORD_TYPE)
    {
      constructor_unfilled_fields
	= DECL_CHAIN (constructor_unfilled_fields);

      /* Skip any nameless bit fields.  */
      पर्यंत (constructor_unfilled_fields != NULL_वृक्ष
	     && DECL_UNNAMED_BIT_FIELD (constructor_unfilled_fields))
	constructor_unfilled_fields
	  = DECL_CHAIN (constructor_unfilled_fields);
    }
  अन्यथा जर (वृक्ष_CODE (constructor_type) == UNION_TYPE)
    constructor_unfilled_fields = NULL_वृक्ष;

  /* Now output any pending elements which have become next.  */
  जर (pending)
    output_pending_init_elements (0, braced_init_obstack);
}

/* For two FIELD_DECLs in the same chain, return -1 if field1
   comes before field2, 1 if field1 comes after field2 and
   0 if field1 == field2.  */

स्थिर पूर्णांक
init_field_decl_cmp (वृक्ष field1, वृक्ष field2)
{
  जर (field1 == field2)
    परत 0;

  वृक्ष bitpos1 = bit_position (field1);
  वृक्ष bitpos2 = bit_position (field2);
  जर (वृक्ष_int_cst_equal (bitpos1, bitpos2))
    {
      /* If one of the fields has non-zero bitsize, then that
	 field must be the last one in a sequence of zero
	 sized fields, fields after it will have bigger
	 bit_position.  */
      जर (वृक्ष_TYPE (field1) != error_mark_गाठ
	  && COMPLETE_TYPE_P (वृक्ष_TYPE (field1))
	  && integer_nonzerop (वृक्ष_TYPE (field1)))
	परत 1;
      जर (वृक्ष_TYPE (field2) != error_mark_गाठ
	  && COMPLETE_TYPE_P (वृक्ष_TYPE (field2))
	  && integer_nonzerop (वृक्ष_TYPE (field2)))
	परत -1;
      /* Otherwise, fallback to DECL_CHAIN walk to find out
	 which field comes earlier.  Walk chains of both
	 fields, so that if field1 and field2 are close to each
	 other in either order, it is found soon even for large
	 sequences of zero sized fields.  */
      वृक्ष f1 = field1, f2 = field2;
      पर्यंत (1)
	{
	  f1 = DECL_CHAIN (f1);
	  f2 = DECL_CHAIN (f2);
	  जर (f1 == NULL_वृक्ष)
	    {
	      gcc_assert (f2);
	      परत 1;
	    }
	  जर (f2 == NULL_वृक्ष)
	    परत -1;
	  जर (f1 == field2)
	    परत -1;
	  जर (f2 == field1)
	    परत 1;
	  जर (!वृक्ष_int_cst_equal (bit_position (f1), bitpos1))
	    परत 1;
	  जर (!वृक्ष_int_cst_equal (bit_position (f2), bitpos1))
	    परत -1;
	}
    }
  अन्यथा जर (वृक्ष_int_cst_lt (bitpos1, bitpos2))
    परत -1;
  अन्यथा
    परत 1;
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
output_pending_init_elements (पूर्णांक all, संरचना obstack * braced_init_obstack)
{
  संरचना init_गाठ *elt = constructor_pending_elts;
  वृक्ष next;

 retry:

  /* Look through the whole pending tree.
     If we find an element that should be output now,
     output it.  Otherwise, set NEXT to the element
     that comes first among those still pending.  */

  next = NULL_वृक्ष;
  पर्यंत (elt)
    {
      जर (वृक्ष_CODE (constructor_type) == ARRAY_TYPE)
	{
	  जर (वृक्ष_int_cst_equal (elt->purpose,
				  constructor_unfilled_index))
	    output_init_element (आदान_location, elt->मूल्य, elt->origtype,
				 सत्य, वृक्ष_TYPE (constructor_type),
				 constructor_unfilled_index, असत्य, असत्य,
				 braced_init_obstack);
	  अन्यथा जर (वृक्ष_int_cst_lt (constructor_unfilled_index,
				    elt->purpose))
	    {
	      /* Advance to the next smaller node.  */
	      जर (elt->डावा)
		elt = elt->डावा;
	      अन्यथा
		{
		  /* We have reached the smallest node bigger than the
		     current unfilled index.  Fill the space first.  */
		  next = elt->purpose;
		  थांबा;
		}
	    }
	  अन्यथा
	    {
	      /* Advance to the next bigger node.  */
	      जर (elt->उजवा)
		elt = elt->उजवा;
	      अन्यथा
		{
		  /* We have reached the biggest node in a subtree.  Find
		     the parent of it, which is the next bigger node.  */
		  पर्यंत (elt->parent && elt->parent->उजवा == elt)
		    elt = elt->parent;
		  elt = elt->parent;
		  जर (elt && वृक्ष_int_cst_lt (constructor_unfilled_index,
					      elt->purpose))
		    {
		      next = elt->purpose;
		      थांबा;
		    }
		}
	    }
	}
      अन्यथा जर (RECORD_OR_UNION_TYPE_P (constructor_type))
	{
	  /* If the current record is complete we are done.  */
	  जर (constructor_unfilled_fields == NULL_वृक्ष)
	    थांबा;

	  पूर्णांक cmp = init_field_decl_cmp (constructor_unfilled_fields,
					 elt->purpose);
	  जर (cmp == 0)
	    output_init_element (आदान_location, elt->मूल्य, elt->origtype,
				 सत्य, वृक्ष_TYPE (elt->purpose),
				 elt->purpose, असत्य, असत्य,
				 braced_init_obstack);
	  अन्यथा जर (cmp < 0)
	    {
	      /* Advance to the next smaller node.  */
	      जर (elt->डावा)
		elt = elt->डावा;
	      अन्यथा
		{
		  /* We have reached the smallest node bigger than the
		     current unfilled field.  Fill the space first.  */
		  next = elt->purpose;
		  थांबा;
		}
	    }
	  अन्यथा
	    {
	      /* Advance to the next bigger node.  */
	      जर (elt->उजवा)
		elt = elt->उजवा;
	      अन्यथा
		{
		  /* We have reached the biggest node in a subtree.  Find
		     the parent of it, which is the next bigger node.  */
		  पर्यंत (elt->parent && elt->parent->उजवा == elt)
		    elt = elt->parent;
		  elt = elt->parent;
		  जर (elt
		      && init_field_decl_cmp (constructor_unfilled_fields,
					      elt->purpose) < 0)
		    {
		      next = elt->purpose;
		      थांबा;
		    }
		}
	    }
	}
    }

  /* Ordinarily return, but not if we want to output all
     and there are elements left.  */
  जर (!(all && next != NULL_वृक्ष))
    परत;

  /* If it's not incremental, just skip over the gap, so that after
     jumping to retry we will output the next successive element.  */
  जर (RECORD_OR_UNION_TYPE_P (constructor_type))
    constructor_unfilled_fields = next;
  अन्यथा जर (वृक्ष_CODE (constructor_type) == ARRAY_TYPE)
    constructor_unfilled_index = next;

  /* ELT now points to the node in the pending tree with the next
     initializer to output.  */
  जा retry;
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
  जर (type == error_mark_गाठ || मूल्य == error_mark_गाठ)
    परत असत्य;

  gcc_checking_assert (TYPE_MAIN_VARIANT (type) == type);

  वृक्ष मूल्य_type = वृक्ष_TYPE (मूल्य);
  जर (मूल्य_type == error_mark_गाठ)
    परत असत्य;

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
  जर (gnu_vector_type_p (type))
    परत !VECTOR_TYPE_P (मूल्य_type);

  जर (AGGREGATE_TYPE_P (type))
    परत !comptypes (type, TYPE_MAIN_VARIANT (मूल्य_type));

  परत असत्य;
}

/* Helper function for process_init_element.  Split first element of
   RAW_DATA_CST and save the rest to *RAW_DATA.  */

स्थिर ओळीत वृक्ष
maybe_split_raw_data (वृक्ष मूल्य, वृक्ष *raw_data)
{
  जर (मूल्य == NULL_वृक्ष || वृक्ष_CODE (मूल्य) != RAW_DATA_CST)
    परत मूल्य;
  *raw_data = मूल्य;
  मूल्य = build_int_cst (integer_type_गाठ,
			 RAW_DATA_UCHAR_ELT (*raw_data, 0));
  ++RAW_DATA_POINTER (*raw_data);
  --RAW_DATA_LENGTH (*raw_data);
  परत मूल्य;
}

/* Return non-zero if c_parser_initval should attempt to optimize
   large initializers into RAW_DATA_CST.  In that case return how
   many elements to optimize at most.  */

अचिन्हित
c_maybe_optimize_large_byte_initializer (शून्य)
{
  जर (!constructor_type
      || वृक्ष_CODE (constructor_type) != ARRAY_TYPE
      || constructor_चळत->implicit)
    परत 0;
  वृक्ष elttype = TYPE_MAIN_VARIANT (वृक्ष_TYPE (constructor_type));
  जर (वृक्ष_CODE (elttype) != INTEGER_TYPE
      && वृक्ष_CODE (elttype) != BITINT_TYPE)
    परत 0;
  जर (TYPE_PRECISION (elttype) != अक्षर_बिट
      || constructor_चळत->replacement_मूल्य.मूल्य
      || (COMPLETE_TYPE_P (constructor_type)
	  && !poly_int_वृक्ष_p (TYPE_SIZE (constructor_type)))
      || constructor_range_चळत)
    परत 0;
  जर (constructor_max_index == NULL_वृक्ष)
    परत पूर्णांक_उच्च;
  जर (वृक्ष_int_cst_le (constructor_max_index, constructor_index)
      || integer_all_onesp (constructor_max_index))
    परत 0;
  widest_int w = wi::to_widest (constructor_max_index);
  w -= wi::to_widest (constructor_index);
  w += 1;
  जर (w < 64)
    परत 0;
  जर (w > पूर्णांक_उच्च)
    परत पूर्णांक_उच्च;
  परत w.to_uhwi ();
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
process_init_element (location_t loc, संरचना c_अभिव्यक्ती मूल्य, तार्किक implicit,
		      संरचना obstack * braced_init_obstack)
{
  वृक्ष orig_मूल्य = मूल्य.मूल्य;
  पूर्णांक string_flag
    = (orig_मूल्य != NULL_वृक्ष && वृक्ष_CODE (orig_मूल्य) == STRING_CST);
  तार्किक strict_string = मूल्य.original_code == STRING_CST;
  तार्किक was_designated = designator_depth != 0;
  वृक्ष raw_data = NULL_वृक्ष;

retry:
  designator_depth = 0;
  designator_erroneous = 0;

  जर (!implicit && मूल्य.मूल्य && !integer_zerop (मूल्य.मूल्य))
    constructor_zeroinit = 0;

  /* Handle superfluous braces around string cst as in
     char x[] = {"foo"}; */
  जर (constructor_type
      && !was_designated
      && वृक्ष_CODE (constructor_type) == ARRAY_TYPE
      && INTEGRAL_TYPE_P (वृक्ष_TYPE (constructor_type))
      && integer_zerop (constructor_unfilled_index))
    {
      जर (constructor_चळत->replacement_मूल्य.मूल्य)
	{
	  error_init (loc, "excess elements in %qT initializer", constructor_type);
	  परत;
	}
      अन्यथा जर (string_flag)
	{
	  constructor_चळत->replacement_मूल्य = मूल्य;
	  परत;
	}
    }

  जर (constructor_चळत->replacement_मूल्य.मूल्य != NULL_वृक्ष)
    {
      error_init (loc, "excess elements in struct initializer");
      परत;
    }

  /* Ignore elements of a brace group if it is entirely superfluous
     and has already been diagnosed, or if the type is erroneous.  */
  जर (constructor_type == NULL_वृक्ष || constructor_type == error_mark_गाठ)
    परत;

  /* Ignore elements of an initializer for a variable-size type.
     Those are diagnosed in the parser (empty initializer braces are OK).  */
  जर (COMPLETE_TYPE_P (constructor_type)
      && !poly_int_वृक्ष_p (TYPE_SIZE (constructor_type)))
    परत;

  जर (!implicit && warn_designated_init && !was_designated
      && वृक्ष_CODE (constructor_type) == RECORD_TYPE
      && lookup_attribute ("designated_init",
			   TYPE_ATTRIBUTES (constructor_type)))
    warning_init (loc,
		  OPT_Wdesignated_init,
		  "positional initialization of field "
		  "in %<struct%> declared with %<designated_init%> attribute");

  /* If we've exhausted any levels that didn't have braces,
     pop them now.  */
  पर्यंत (constructor_चळत->implicit)
    {
      जर (RECORD_OR_UNION_TYPE_P (constructor_type)
	  && constructor_fields == NULL_वृक्ष)
	process_init_element (loc,
			      काढा_init_level (loc, 1, braced_init_obstack,
					      last_init_list_comma),
			      सत्य, braced_init_obstack);
      अन्यथा जर ((वृक्ष_CODE (constructor_type) == ARRAY_TYPE
		|| gnu_vector_type_p (constructor_type))
	       && constructor_max_index
	       && वृक्ष_int_cst_lt (constructor_max_index,
				   constructor_index))
	process_init_element (loc,
			      काढा_init_level (loc, 1, braced_init_obstack,
					      last_init_list_comma),
			      सत्य, braced_init_obstack);
      अन्यथा
	थांबा;
    }

  /* In the case of [LO ... HI] = VALUE, only evaluate VALUE once.  */
  जर (constructor_range_चळत)
    {
      /* If value is a compound literal and we'll be just using its
	 content, don't put it into a SAVE_EXPR.  */
      जर (वृक्ष_CODE (मूल्य.मूल्य) != COMPOUND_LITERAL_अभिव्यक्ती
	  || !require_constant_मूल्य)
	{
	  वृक्ष semantic_type = NULL_वृक्ष;
	  जर (वृक्ष_CODE (मूल्य.मूल्य) == EXCESS_PRECISION_अभिव्यक्ती)
	    {
	      semantic_type = वृक्ष_TYPE (मूल्य.मूल्य);
	      मूल्य.मूल्य = वृक्ष_OPERAND (मूल्य.मूल्य, 0);
	    }
	  मूल्य.मूल्य = save_अभिव्यक्ती (मूल्य.मूल्य);
	  जर (semantic_type)
	    मूल्य.मूल्य = build1 (EXCESS_PRECISION_अभिव्यक्ती, semantic_type,
				  मूल्य.मूल्य);
	}
    }

  पर्यंत (1)
    {
      जर (वृक्ष_CODE (constructor_type) == RECORD_TYPE)
	{
	  वृक्ष fieldtype;
	  गणना वृक्ष_code fieldcode;

	  जर (constructor_fields == NULL_वृक्ष)
	    {
	      pedwarn_init (loc, 0, "excess elements in struct initializer");
	      थांबा;
	    }

	  fieldtype = वृक्ष_TYPE (constructor_fields);
	  जर (fieldtype != error_mark_गाठ)
	    fieldtype = TYPE_MAIN_VARIANT (fieldtype);
	  fieldcode = वृक्ष_CODE (fieldtype);

	  /* Error for non-static initialization of a flexible array member.  */
	  जर (fieldcode == ARRAY_TYPE
	      && !require_constant_मूल्य
	      && TYPE_SIZE (fieldtype) == NULL_वृक्ष
	      && DECL_CHAIN (constructor_fields) == NULL_वृक्ष)
	    {
	      error_init (loc, "non-static initialization of a flexible "
			  "array member");
	      थांबा;
	    }

	  /* Error for initialization of a flexible array member with
	     a string constant if the structure is in an array.  E.g.:
	     struct S { int x; char y[]; };
	     struct S s[] = { { 1, "foo" } };
	     is invalid.  */
	  जर (string_flag
	      && fieldcode == ARRAY_TYPE
	      && constructor_depth > 1
	      && TYPE_SIZE (fieldtype) == NULL_वृक्ष
	      && DECL_CHAIN (constructor_fields) == NULL_वृक्ष)
	    {
	      तार्किक in_array_p = असत्य;
	      साठी (संरचना constructor_चळत *p = constructor_चळत;
		   p && p->type; p = p->next)
		जर (वृक्ष_CODE (p->type) == ARRAY_TYPE)
		  {
		    in_array_p = सत्य;
		    थांबा;
		  }
	      जर (in_array_p)
		{
		  error_init (loc, "initialization of flexible array "
			      "member in a nested context");
		  थांबा;
		}
	    }

	  /* Accept a string constant to initialize a subarray.  */
	  जर (मूल्य.मूल्य != NULL_वृक्ष
	      && fieldcode == ARRAY_TYPE
	      && INTEGRAL_TYPE_P (वृक्ष_TYPE (fieldtype))
	      && string_flag)
	    मूल्य.मूल्य = orig_मूल्य;
	  /* Otherwise, if we have come to a subaggregate,
	     and we don't have an element of its type, push into it.  */
	  अन्यथा जर (मूल्य.मूल्य != NULL_वृक्ष
		   && initialize_elementwise_p (fieldtype, मूल्य.मूल्य))
	    {
	      ढकला_init_level (loc, 1, braced_init_obstack);
	      सुरूठेवा;
	    }

	  मूल्य.मूल्य = maybe_split_raw_data (मूल्य.मूल्य, &raw_data);
	  जर (मूल्य.मूल्य)
	    {
	      ढकला_member_name (constructor_fields);
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
	      जर (DECL_SIZE (constructor_fields))
		constructor_bit_index
		  = size_binop_loc (आदान_location, PLUS_अभिव्यक्ती,
				    bit_position (constructor_fields),
				    DECL_SIZE (constructor_fields));

	      /* If the current field was the first one not yet written out,
		 it isn't now, so update.  */
	      जर (constructor_unfilled_fields == constructor_fields)
		{
		  constructor_unfilled_fields = DECL_CHAIN (constructor_fields);
		  /* Skip any nameless bit fields.  */
		  पर्यंत (constructor_unfilled_fields != 0
			 && (DECL_UNNAMED_BIT_FIELD
			     (constructor_unfilled_fields)))
		    constructor_unfilled_fields =
		      DECL_CHAIN (constructor_unfilled_fields);
		}
	    }

	  constructor_fields = DECL_CHAIN (constructor_fields);
	  /* Skip any nameless bit fields at the beginning.  */
	  पर्यंत (constructor_fields != NULL_वृक्ष
		 && DECL_UNNAMED_BIT_FIELD (constructor_fields))
	    constructor_fields = DECL_CHAIN (constructor_fields);
	}
      अन्यथा जर (वृक्ष_CODE (constructor_type) == UNION_TYPE)
	{
	  वृक्ष fieldtype;
	  गणना वृक्ष_code fieldcode;

	  जर (constructor_fields == NULL_वृक्ष)
	    {
	      pedwarn_init (loc, 0,
			    "excess elements in union initializer");
	      थांबा;
	    }

	  fieldtype = वृक्ष_TYPE (constructor_fields);
	  जर (fieldtype != error_mark_गाठ)
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
	  जर (!in_system_header_at (आदान_location) && !constructor_designated
	      && !(मूल्य.मूल्य && (integer_zerop (मूल्य.मूल्य)
				   || real_zerop (मूल्य.मूल्य))))
	    warning (OPT_Wtraditional, "traditional C rejects initialization "
		     "of unions");

	  /* Error for non-static initialization of a flexible array member.  */
	  जर (fieldcode == ARRAY_TYPE
	      && !require_constant_मूल्य
	      && TYPE_SIZE (fieldtype) == NULL_वृक्ष)
	    {
	      error_init (loc, "non-static initialization of a flexible "
			  "array member");
	      थांबा;
	    }

	  /* Error for initialization of a flexible array member with
	     a string constant if the structure is in an array.  E.g.:
	     union U { int x; char y[]; };
	     union U s[] = { { 1, "foo" } };
	     is invalid.  */
	  जर (string_flag
	      && fieldcode == ARRAY_TYPE
	      && constructor_depth > 1
	      && TYPE_SIZE (fieldtype) == NULL_वृक्ष)
	    {
	      तार्किक in_array_p = असत्य;
	      साठी (संरचना constructor_चळत *p = constructor_चळत;
		   p && p->type; p = p->next)
		जर (वृक्ष_CODE (p->type) == ARRAY_TYPE)
		  {
		    in_array_p = सत्य;
		    थांबा;
		  }
	      जर (in_array_p)
		{
		  error_init (loc, "initialization of flexible array "
			      "member in a nested context");
		  थांबा;
		}
	    }

	  /* Accept a string constant to initialize a subarray.  */
	  जर (मूल्य.मूल्य != NULL_वृक्ष
	      && fieldcode == ARRAY_TYPE
	      && INTEGRAL_TYPE_P (वृक्ष_TYPE (fieldtype))
	      && string_flag)
	    मूल्य.मूल्य = orig_मूल्य;
	  /* Otherwise, if we have come to a subaggregate,
	     and we don't have an element of its type, push into it.  */
	  अन्यथा जर (मूल्य.मूल्य != NULL_वृक्ष
		   && initialize_elementwise_p (fieldtype, मूल्य.मूल्य))
	    {
	      ढकला_init_level (loc, 1, braced_init_obstack);
	      सुरूठेवा;
	    }

	  मूल्य.मूल्य = maybe_split_raw_data (मूल्य.मूल्य, &raw_data);
	  जर (मूल्य.मूल्य)
	    {
	      ढकला_member_name (constructor_fields);
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
      अन्यथा जर (वृक्ष_CODE (constructor_type) == ARRAY_TYPE)
	{
	  वृक्ष elttype = TYPE_MAIN_VARIANT (वृक्ष_TYPE (constructor_type));
	  गणना वृक्ष_code eltcode = वृक्ष_CODE (elttype);

	  /* Accept a string constant to initialize a subarray.  */
	  जर (मूल्य.मूल्य != NULL_वृक्ष
	      && eltcode == ARRAY_TYPE
	      && INTEGRAL_TYPE_P (वृक्ष_TYPE (elttype))
	      && string_flag)
	    मूल्य.मूल्य = orig_मूल्य;
	  /* Otherwise, if we have come to a subaggregate,
	     and we don't have an element of its type, push into it.  */
	  अन्यथा जर (मूल्य.मूल्य != NULL_वृक्ष
		   && initialize_elementwise_p (elttype, मूल्य.मूल्य))
	    {
	      ढकला_init_level (loc, 1, braced_init_obstack);
	      सुरूठेवा;
	    }

	  जर (constructor_max_index != NULL_वृक्ष
	      && (वृक्ष_int_cst_lt (constructor_max_index, constructor_index)
		  || integer_all_onesp (constructor_max_index))
	      /* For VLA we got an error already.  */
	      && !C_TYPE_VARIABLE_SIZE (constructor_type))
	    {
	      pedwarn_init (loc, 0,
			    "excess elements in array initializer");
	      थांबा;
	    }

	  जर (मूल्य.मूल्य
	      && वृक्ष_CODE (मूल्य.मूल्य) == RAW_DATA_CST
	      && RAW_DATA_LENGTH (मूल्य.मूल्य) > 1
	      && (वृक्ष_CODE (elttype) == INTEGER_TYPE
		  || वृक्ष_CODE (elttype) == BITINT_TYPE)
	      && TYPE_PRECISION (elttype) == अक्षर_बिट
	      && (constructor_max_index == NULL_वृक्ष
		  || वृक्ष_int_cst_lt (constructor_index,
				      constructor_max_index)))
	    {
	      अचिन्हित पूर्णांक len = RAW_DATA_LENGTH (मूल्य.मूल्य);
	      जर (constructor_max_index)
		{
		  widest_int w = wi::to_widest (constructor_max_index);
		  w -= wi::to_widest (constructor_index);
		  w += 1;
		  जर (w < len)
		    len = w.to_uhwi ();
		}
	      जर (len < (अचिन्हित) RAW_DATA_LENGTH (मूल्य.मूल्य))
		{
		  raw_data = copy_गाठ (मूल्य.मूल्य);
		  RAW_DATA_LENGTH (raw_data) -= len;
		  RAW_DATA_POINTER (raw_data) += len;
		  RAW_DATA_LENGTH (मूल्य.मूल्य) = len;
		}
	      वृक्ष_TYPE (मूल्य.मूल्य) = elttype;
	      ढकला_array_bounds (वृक्ष_to_uhwi (constructor_index));
	      output_init_element (loc, मूल्य.मूल्य, मूल्य.original_type,
				   असत्य, elttype, constructor_index, सत्य,
				   implicit, braced_init_obstack);
	      RESTORE_SPELLING_DEPTH (constructor_depth);
	      constructor_index
		= size_binop_loc (आदान_location, PLUS_अभिव्यक्ती,
				  constructor_index, bitsize_int (len));
	    }
	  अन्यथा
	    {
	      मूल्य.मूल्य = maybe_split_raw_data (मूल्य.मूल्य, &raw_data);
	      /* Now output the actual element.  */
	      जर (मूल्य.मूल्य)
		{
		  ढकला_array_bounds (वृक्ष_to_uhwi (constructor_index));
		  output_init_element (loc, मूल्य.मूल्य, मूल्य.original_type,
				       strict_string, elttype,
				       constructor_index, सत्य, implicit,
				       braced_init_obstack);
		  RESTORE_SPELLING_DEPTH (constructor_depth);
		}

	      constructor_index
		= size_binop_loc (आदान_location, PLUS_अभिव्यक्ती,
				  constructor_index, bitsize_one_गाठ);

	      जर (!मूल्य.मूल्य)
		/* If we are doing the bookkeeping for an element that was
		   directly output as a constructor, we must update
		   constructor_unfilled_index.  */
		constructor_unfilled_index = constructor_index;
	    }
	}
      अन्यथा जर (gnu_vector_type_p (constructor_type))
	{
	  वृक्ष elttype = TYPE_MAIN_VARIANT (वृक्ष_TYPE (constructor_type));

	  /* Do a basic check of initializer size.  Note that vectors
	     may not always have a fixed size derived from their type.  */
	  जर (maybe_lt (वृक्ष_to_poly_uint64 (constructor_max_index),
			वृक्ष_to_poly_uint64 (constructor_index)))
	    {
	      /* Diagose VLA out-of-bounds as errors.  */
	      जर (वृक्ष_to_poly_uint64 (constructor_max_index).is_constant())
		pedwarn_init (loc, 0,
			      "excess elements in vector initializer");
	      अन्यथा
		error_init (loc, "excess elements in vector initializer");

	      थांबा;
	    }

	  मूल्य.मूल्य = maybe_split_raw_data (मूल्य.मूल्य, &raw_data);
	  /* Now output the actual element.  */
	  जर (मूल्य.मूल्य)
	    {
	      जर (वृक्ष_CODE (मूल्य.मूल्य) == VECTOR_CST)
		elttype = TYPE_MAIN_VARIANT (constructor_type);
	      output_init_element (loc, मूल्य.मूल्य, मूल्य.original_type,
				   strict_string, elttype,
				   constructor_index, सत्य, implicit,
				   braced_init_obstack);
	    }

	  constructor_index
	    = size_binop_loc (आदान_location,
			      PLUS_अभिव्यक्ती, constructor_index, bitsize_one_गाठ);

	  जर (!मूल्य.मूल्य)
	    /* If we are doing the bookkeeping for an element that was
	       directly output as a constructor, we must update
	       constructor_unfilled_index.  */
	    constructor_unfilled_index = constructor_index;
	}

      /* Handle the sole element allowed in a braced initializer
	 for a scalar variable.  */
      अन्यथा जर (constructor_type != error_mark_गाठ
	       && constructor_fields == NULL_वृक्ष)
	{
	  pedwarn_init (loc, 0,
			"excess elements in scalar initializer");
	  थांबा;
	}
      अन्यथा
	{
	  मूल्य.मूल्य = maybe_split_raw_data (मूल्य.मूल्य, &raw_data);
	  जर (मूल्य.मूल्य)
	    output_init_element (loc, मूल्य.मूल्य, मूल्य.original_type,
				 strict_string, constructor_type,
				 NULL_वृक्ष, सत्य, implicit,
				 braced_init_obstack);
	  constructor_fields = NULL_वृक्ष;
	}

      /* Handle range initializers either at this level or anywhere higher
	 in the designator stack.  */
      जर (constructor_range_चळत)
	{
	  संरचना constructor_range_चळत *p, *range_चळत;
	  पूर्णांक finish = 0;

	  range_चळत = constructor_range_चळत;
	  constructor_range_चळत = 0;
	  पर्यंत (constructor_चळत != range_चळत->चळत)
	    {
	      gcc_assert (constructor_चळत->implicit);
	      process_init_element (loc,
				    काढा_init_level (loc, 1,
						    braced_init_obstack,
						    last_init_list_comma),
				    सत्य, braced_init_obstack);
	    }
	  साठी (p = range_चळत;
	       !p->range_end || वृक्ष_int_cst_equal (p->index, p->range_end);
	       p = p->prev)
	    {
	      gcc_assert (constructor_चळत->implicit);
	      process_init_element (loc,
				    काढा_init_level (loc, 1,
						    braced_init_obstack,
						    last_init_list_comma),
				    सत्य, braced_init_obstack);
	    }

	  p->index = size_binop_loc (आदान_location,
				     PLUS_अभिव्यक्ती, p->index, bitsize_one_गाठ);
	  जर (वृक्ष_int_cst_equal (p->index, p->range_end) && !p->prev)
	    finish = 1;

	  पर्यंत (1)
	    {
	      constructor_index = p->index;
	      constructor_fields = p->fields;
	      जर (finish && p->range_end && p->index == p->range_start)
		{
		  finish = 0;
		  p->prev = 0;
		}
	      p = p->next;
	      जर (!p)
		थांबा;
	      finish_implicit_inits (loc, braced_init_obstack);
	      ढकला_init_level (loc, 2, braced_init_obstack);
	      p->चळत = constructor_चळत;
	      जर (p->range_end && वृक्ष_int_cst_equal (p->index, p->range_end))
		p->index = p->range_start;
	    }

	  जर (!finish)
	    constructor_range_चळत = range_चळत;
	  सुरूठेवा;
	}

      थांबा;
    }

  constructor_range_चळत = 0;

  जर (raw_data && RAW_DATA_LENGTH (raw_data))
    {
      gcc_assert (!string_flag && !was_designated);
      मूल्य.मूल्य = raw_data;
      raw_data = NULL_वृक्ष;
      जा retry;
    }
}

/* Build a complete asm-statement, whose components are a CV_QUALIFIER
   (guaranteed to be 'volatile' or null) and ARGS (represented using
   an ASM_EXPR node).  */
वृक्ष
build_asm_stmt (तार्किक is_volatile, वृक्ष args)
{
  जर (is_volatile)
    ASM_VOLATILE_P (args) = 1;
  परत add_stmt (args);
}

/* Build an asm-expr, whose components are a STRING, some OUTPUTS,
   some INPUTS, and some CLOBBERS.  The latter three may be NULL.
   SIMPLE indicates whether there was anything at all after the
   string in the asm expression -- asm("blah") and asm("blah" : )
   are subtly different.  We use a ASM_EXPR node to represent this.
   LOC is the location of the asm, and IS_INLINE says whether this
   is asm inline.  */
वृक्ष
build_asm_अभिव्यक्ती (location_t loc, वृक्ष string, वृक्ष outputs, वृक्ष inputs,
		वृक्ष clobbers, वृक्ष labels, तार्किक simple, तार्किक is_inline)
{
  वृक्ष tail;
  वृक्ष args;
  पूर्णांक i;
  स्थिरांक अक्षर *constraint;
  स्थिरांक अक्षर **oconstraints;
  तार्किक allows_mem, allows_reg, is_inout;
  पूर्णांक ninputs, noutputs;

  ninputs = list_length (inputs);
  noutputs = list_length (outputs);
  oconstraints = (स्थिरांक अक्षर **) alloca (noutputs * आकार (स्थिरांक अक्षर *));

  string = resolve_asm_operand_names (string, outputs, inputs, labels);

  /* Remove output conversions that change the type but not the mode.  */
  साठी (i = 0, tail = outputs; tail; ++i, tail = वृक्ष_CHAIN (tail))
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

      जर (!lvalue_or_else (loc, output, lv_asm))
	output = error_mark_गाठ;

      जर (output != error_mark_गाठ
	  && (वृक्ष_READONLY (output)
	      || TYPE_READONLY (वृक्ष_TYPE (output))
	      || (RECORD_OR_UNION_TYPE_P (वृक्ष_TYPE (output))
		  && C_TYPE_FIELDS_READONLY (वृक्ष_TYPE (output)))))
	readonly_error (loc, output, lv_asm);

      constraint = वृक्ष_STRING_POINTER (वृक्ष_मूल्य (वृक्ष_PURPOSE (tail)));
      oconstraints[i] = constraint;

      जर (parse_output_constraint (&constraint, i, ninputs, noutputs,
				   &allows_mem, &allows_reg, &is_inout,
				   nullptr))
	{
	  /* If the operand is going to end up in memory,
	     mark it addressable.  */
	  जर (!allows_reg && !c_mark_addressable (output))
	    output = error_mark_गाठ;
	  जर (!(!allows_reg && allows_mem)
	      && output != error_mark_गाठ
	      && VOID_TYPE_P (वृक्ष_TYPE (output)))
	    {
	      error_at (loc, "invalid use of void expression");
	      output = error_mark_गाठ;
	    }
	  जर (allows_reg && current_function_decl == NULL_वृक्ष)
	    {
	      error_at (loc, "constraint allows registers outside of "
			     "a function");
	      output = error_mark_गाठ;
	    }
	}
      अन्यथा
	output = error_mark_गाठ;

      जर (current_function_decl == NULL_वृक्ष && output != error_mark_गाठ)
	{
	  जर (वृक्ष_SIDE_EFFECTS (output))
	    {
	      error_at (loc, "side-effects in output operand outside "
			     "of a function");
	      output = error_mark_गाठ;
	    }
	  अन्यथा
	    {
	      वृक्ष addr = build_unary_op (loc, ADDR_अभिव्यक्ती, output, असत्य);
	      जर (addr == error_mark_गाठ)
		output = error_mark_गाठ;
	      अन्यथा जर (!initializer_constant_valid_p (addr, वृक्ष_TYPE (addr)))
		{
		  error_at (loc, "output operand outside of a function is not "
				 "constant");
		  output = error_mark_गाठ;
		}
	    }
	}
      अन्यथा जर (output != error_mark_गाठ && म_माला (constraint, "-"))
	{
	  error_at (loc, "%<-%> modifier used inside of a function");
	  output = error_mark_गाठ;
	}

      वृक्ष_मूल्य (tail) = output;
    }

  साठी (i = 0, tail = inputs; tail; ++i, tail = वृक्ष_CHAIN (tail))
    {
      वृक्ष आदान;

      constraint = वृक्ष_STRING_POINTER (वृक्ष_मूल्य (वृक्ष_PURPOSE (tail)));
      आदान = वृक्ष_मूल्य (tail);

      जर (parse_आदान_constraint (&constraint, i, ninputs, noutputs, 0,
				  oconstraints, &allows_mem, &allows_reg,
				  nullptr))
	{
	  /* If the operand is going to end up in memory,
	     mark it addressable.  */
	  जर (!allows_reg && allows_mem)
	    {
	      आदान = c_fully_fold (आदान, असत्य, रिक्त, सत्य);

	      /* Strip the nops as we allow this case.  FIXME, this really
		 should be rejected or made deprecated.  */
	      STRIP_NOPS (आदान);
	      जर (!c_mark_addressable (आदान))
		आदान = error_mark_गाठ;
	    }
	  अन्यथा
	    {
	      आदान = c_fully_fold (convert_lvalue_to_rvalue (loc, आदान,
							      सत्य, असत्य),
				    असत्य, रिक्त);

	      जर (आदान != error_mark_गाठ && VOID_TYPE_P (वृक्ष_TYPE (आदान)))
		{
		  error_at (loc, "invalid use of void expression");
		  आदान = error_mark_गाठ;
		}
	    }
	  जर (allows_reg && current_function_decl == NULL_वृक्ष)
	    {
	      error_at (loc, "constraint allows registers outside of "
			     "a function");
	      आदान = error_mark_गाठ;
	    }
	  जर (constraint[0] == ':' && आदान != error_mark_गाठ)
	    {
	      वृक्ष t = आदान;
	      STRIP_NOPS (t);
	      जर (वृक्ष_CODE (t) != ADDR_अभिव्यक्ती
		  || !(वृक्ष_CODE (वृक्ष_OPERAND (t, 0)) == FUNCTION_DECL
		       || (VAR_P (वृक्ष_OPERAND (t, 0))
			   && is_global_var (वृक्ष_OPERAND (t, 0)))))
		{
		  error_at (loc, "%<:%> constraint operand is not address "
				 "of a function or non-automatic variable");
		  आदान = error_mark_गाठ;
		}
	      अन्यथा जर (वृक्ष_CODE (वृक्ष_OPERAND (t, 0)) == FUNCTION_DECL)
		suppress_warning (वृक्ष_OPERAND (t, 0), OPT_Wunused);
	    }
	}
      अन्यथा
	आदान = error_mark_गाठ;

      जर (current_function_decl == NULL_वृक्ष && आदान != error_mark_गाठ)
	{
	  जर (वृक्ष_SIDE_EFFECTS (आदान))
	    {
	      error_at (loc, "side-effects in input operand outside "
			     "of a function");
	      आदान = error_mark_गाठ;
	    }
	  अन्यथा
	    {
	      वृक्ष tem = आदान;
	      जर (allows_mem && lvalue_p (आदान))
		tem = build_unary_op (loc, ADDR_अभिव्यक्ती, आदान, असत्य);
	      जर (!initializer_constant_valid_p (tem, वृक्ष_TYPE (tem)))
		{
		  error_at (loc, "input operand outside of a function is not "
				 "constant");
		  आदान = error_mark_गाठ;
		}
	    }
	}
      अन्यथा जर (आदान != error_mark_गाठ && म_माला (constraint, "-"))
	{
	  error_at (loc, "%<-%> modifier used inside of a function");
	  आदान = error_mark_गाठ;
	}

      वृक्ष_मूल्य (tail) = आदान;
    }

  args = build_stmt (loc, ASM_अभिव्यक्ती, string, outputs, inputs, clobbers, labels);

  /* asm statements without outputs, including simple ones, are treated
     as volatile.  */
  ASM_BASIC_P (args) = simple;
  ASM_VOLATILE_P (args) = (noutputs == 0);
  ASM_INLINE_P (args) = is_inline;

  परत args;
}

/* Generate a goto statement to LABEL.  LOC is the location of the
   GOTO.  */

वृक्ष
c_finish_goto_label (location_t loc, वृक्ष label)
{
  वृक्ष decl = lookup_label_for_goto (loc, label);
  जर (!decl)
    परत NULL_वृक्ष;
  वृक्ष_USED (decl) = 1;
  mark_decl_used (decl, असत्य);
  {
    add_stmt (build_predict_अभिव्यक्ती (PRED_GOTO, NOT_TAKEN));
    वृक्ष t = build1 (GOTO_अभिव्यक्ती, void_type_गाठ, decl);
    SET_अभिव्यक्ती_LOCATION (t, loc);
    परत add_stmt (t);
  }
}

/* Generate a computed goto statement to EXPR.  LOC is the location of
   the GOTO.  */

वृक्ष
c_finish_goto_ptr (location_t loc, c_अभिव्यक्ती val)
{
  वृक्ष अभिव्यक्ती = val.मूल्य;
  वृक्ष t;
  pedwarn (loc, OPT_Wpedantic, "ISO C forbids %<goto *expr;%>");
  जर (अभिव्यक्ती != error_mark_गाठ
      && !POINTER_TYPE_P (वृक्ष_TYPE (अभिव्यक्ती))
      && !null_pointer_constant_p (अभिव्यक्ती))
    {
      error_at (val.get_location (),
		"computed goto must be pointer type");
      अभिव्यक्ती = build_zero_cst (ptr_type_गाठ);
    }
  अभिव्यक्ती = c_fully_fold (अभिव्यक्ती, असत्य, रिक्त);
  अभिव्यक्ती = convert (ptr_type_गाठ, अभिव्यक्ती);
  t = build1 (GOTO_अभिव्यक्ती, void_type_गाठ, अभिव्यक्ती);
  SET_अभिव्यक्ती_LOCATION (t, loc);
  परत add_stmt (t);
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

  जर (वृक्ष_THIS_VOLATILE (current_function_decl))
    warning_at (xloc, 0,
		"function declared %<noreturn%> has a %<return%> statement");

  set_musttail_on_return (retval, xloc, musttail_p);

  जर (retval)
    {
      वृक्ष semantic_type = NULL_वृक्ष;
      npc = null_pointer_constant_p (retval);
      जर (वृक्ष_CODE (retval) == EXCESS_PRECISION_अभिव्यक्ती)
	{
	  semantic_type = वृक्ष_TYPE (retval);
	  retval = वृक्ष_OPERAND (retval, 0);
	}
      retval = c_fully_fold (retval, असत्य, रिक्त);
      जर (semantic_type
	  && valtype != NULL_वृक्ष
	  && वृक्ष_CODE (valtype) != VOID_TYPE)
	retval = build1 (EXCESS_PRECISION_अभिव्यक्ती, semantic_type, retval);
    }

  जर (!retval)
    {
      current_function_returns_null = 1;
      जर ((warn_return_type >= 0 || flag_isoc99)
	  && valtype != NULL_वृक्ष && वृक्ष_CODE (valtype) != VOID_TYPE)
	{
	  no_warning = सत्य;
	  जर (emit_diagnostic (flag_isoc99
			       ? diagnostics::kind::permerror
			       : diagnostics::kind::warning,
			       loc, OPT_Wreturn_mismatch,
			       "%<return%> with no value,"
			       " in function returning non-void"))
	    inform (DECL_SOURCE_LOCATION (current_function_decl),
		    "declared here");
	}
    }
  अन्यथा जर (valtype == NULL_वृक्ष || VOID_TYPE_P (valtype))
    {
      current_function_returns_null = 1;
      तार्किक warned_here;
      जर (वृक्ष_CODE (वृक्ष_TYPE (retval)) != VOID_TYPE)
	warned_here = permerror_opt
	  (xloc, OPT_Wreturn_mismatch,
	   "%<return%> with a value, in function returning void");
      अन्यथा
	warned_here = pedwarn
	  (xloc, OPT_Wpedantic, "ISO C forbids "
	   "%<return%> with expression, in function returning void");
      जर (warned_here)
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
      जर (t == error_mark_गाठ)
	{
	  /* Suppress -Wreturn-type for this function.  */
	  जर (warn_return_type)
	    suppress_warning (current_function_decl, OPT_Wreturn_type);
	  परत NULL_वृक्ष;
	}

      save = in_late_द्विमान_op;
      जर (C_BOOLEAN_TYPE_P (वृक्ष_TYPE (res))
	  || वृक्ष_CODE (वृक्ष_TYPE (res)) == COMPLEX_TYPE
	  || (SCALAR_FLOAT_TYPE_P (वृक्ष_TYPE (t))
	      && (वृक्ष_CODE (वृक्ष_TYPE (res)) == INTEGER_TYPE
		  || वृक्ष_CODE (वृक्ष_TYPE (res)) == ENUMERAL_TYPE)
	      && sanitize_flags_p (SANITIZE_FLOAT_CAST)))
        in_late_द्विमान_op = सत्य;
      inner = t = convert (वृक्ष_TYPE (res), t);
      in_late_द्विमान_op = save;

      /* Strip any conversions, additions, and subtractions, and see if
	 we are returning the address of a local variable.  Warn if so.  */
      पर्यंत (1)
	{
	  निवड (वृक्ष_CODE (inner))
	    {
	    CASE_CONVERT:
	    स्थिती NON_LVALUE_अभिव्यक्ती:
	    स्थिती PLUS_अभिव्यक्ती:
	    स्थिती POINTER_PLUS_अभिव्यक्ती:
	      inner = वृक्ष_OPERAND (inner, 0);
	      सुरूठेवा;

	    स्थिती MINUS_अभिव्यक्ती:
	      /* If the second operand of the MINUS_EXPR has a pointer
		 type (or is converted from it), this may be valid, so
		 don't give a warning.  */
	      {
		वृक्ष op1 = वृक्ष_OPERAND (inner, 1);

		पर्यंत (!POINTER_TYPE_P (वृक्ष_TYPE (op1))
		       && (CONVERT_अभिव्यक्ती_P (op1)
			   || वृक्ष_CODE (op1) == NON_LVALUE_अभिव्यक्ती))
		  op1 = वृक्ष_OPERAND (op1, 0);

		जर (POINTER_TYPE_P (वृक्ष_TYPE (op1)))
		  थांबा;

		inner = वृक्ष_OPERAND (inner, 0);
		सुरूठेवा;
	      }

	    स्थिती ADDR_अभिव्यक्ती:
	      inner = वृक्ष_OPERAND (inner, 0);

	      पर्यंत (REFERENCE_CLASS_P (inner)
		     && !INDIRECT_REF_P (inner))
		inner = वृक्ष_OPERAND (inner, 0);

	      जर (DECL_P (inner)
		  && !DECL_EXTERNAL (inner)
		  && DECL_CONTEXT (inner) == current_function_decl
		  && POINTER_TYPE_P (वृक्ष_TYPE (वृक्ष_TYPE (current_function_decl))))
		{
		  जर (वृक्ष_CODE (inner) == LABEL_DECL)
		    warning_at (loc, OPT_Wreturn_local_addr,
				"function returns address of label");
		  अन्यथा जर (वृक्ष_CODE (inner) == FUNCTION_DECL
			   && (C_FUNC_NONLOCAL_CONTEXT (inner)
			       || !DECL_INITIAL (inner)))
		    warning_at (loc, OPT_Wreturn_local_addr,
				"function returns address of nested function "
				"referencing local context");
		  अन्यथा जर (वृक्ष_CODE (inner) != FUNCTION_DECL
			   && !वृक्ष_STATIC (inner))
		    {
		      warning_at (loc, OPT_Wreturn_local_addr,
				  "function returns address of local variable");
		      वृक्ष zero = build_zero_cst (वृक्ष_TYPE (res));
		      t = build2 (COMPOUND_अभिव्यक्ती, वृक्ष_TYPE (res), t, zero);
		    }
		}
	      थांबा;

	    पूर्वनिर्धारित:
	      थांबा;
	    }

	  थांबा;
	}

      retval = build2 (MODIFY_अभिव्यक्ती, वृक्ष_TYPE (res), res, t);
      SET_अभिव्यक्ती_LOCATION (retval, loc);

      जर (warn_sequence_point)
	verify_sequence_points (retval);
    }

  ret_stmt = build_stmt (loc, RETURN_अभिव्यक्ती, retval);
  जर (no_warning)
    suppress_warning (ret_stmt, OPT_Wreturn_type);
  परत add_stmt (ret_stmt);
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

संरचना c_switch *c_switch_चळत;

/* Start a C switch statement, testing expression EXP.  Return the new
   SWITCH_STMT.  SWITCH_LOC is the location of the `switch'.
   SWITCH_COND_LOC is the location of the switch's condition.
   EXPLICIT_CAST_P is true if the expression EXP has an explicit cast.  */

वृक्ष
c_start_switch (location_t switch_loc,
		location_t switch_cond_loc,
		वृक्ष exp, तार्किक explicit_cast_p, वृक्ष switch_name)
{
  वृक्ष orig_type = error_mark_गाठ;
  तार्किक bool_cond_p = असत्य;
  संरचना c_switch *cs;

  जर (exp != error_mark_गाठ)
    {
      orig_type = वृक्ष_TYPE (exp);

      जर (!INTEGRAL_TYPE_P (orig_type))
	{
	  जर (orig_type != error_mark_गाठ)
	    {
	      error_at (switch_cond_loc, "switch quantity not an integer");
	      orig_type = error_mark_गाठ;
	    }
	  exp = integer_zero_गाठ;
	}
      अन्यथा
	{
	  वृक्ष type = TYPE_MAIN_VARIANT (orig_type);
	  वृक्ष e = exp;

	  /* Warn if the condition has boolean value.  */
	  पर्यंत (वृक्ष_CODE (e) == COMPOUND_अभिव्यक्ती)
	    e = वृक्ष_OPERAND (e, 1);

	  जर ((C_BOOLEAN_TYPE_P (type)
	       || truth_मूल्य_p (वृक्ष_CODE (e)))
	      /* Explicit cast to int suppresses this warning.  */
	      && !(वृक्ष_CODE (type) == INTEGER_TYPE
		   && explicit_cast_p))
	    bool_cond_p = सत्य;

	  जर (!in_system_header_at (आदान_location)
	      && (type == long_integer_type_गाठ
		  || type == long_unsigned_type_गाठ))
	    warning_at (switch_cond_loc,
			OPT_Wtraditional, "%<long%> switch expression not "
			"converted to %<int%> in ISO C");

	  exp = c_fully_fold (exp, असत्य, रिक्त);
	  exp = default_conversion (exp);

	  जर (warn_sequence_point)
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
  cs->next = c_switch_चळत;
  c_switch_चळत = cs;

  परत add_stmt (cs->switch_stmt);
}

/* Process a case label at location LOC, with attributes ATTRS.  */

वृक्ष
do_case (location_t loc, वृक्ष खालचा_मूल्य, वृक्ष वरचा_मूल्य, वृक्ष attrs)
{
  वृक्ष label = NULL_वृक्ष;

  जर (खालचा_मूल्य && वृक्ष_CODE (खालचा_मूल्य) != INTEGER_CST)
    {
      खालचा_मूल्य = c_fully_fold (खालचा_मूल्य, असत्य, रिक्त);
      जर (वृक्ष_CODE (खालचा_मूल्य) == INTEGER_CST)
	pedwarn (loc, OPT_Wpedantic,
		 "case label is not an integer constant expression");
    }

  जर (वरचा_मूल्य && वृक्ष_CODE (वरचा_मूल्य) != INTEGER_CST)
    {
      वरचा_मूल्य = c_fully_fold (वरचा_मूल्य, असत्य, रिक्त);
      जर (वृक्ष_CODE (वरचा_मूल्य) == INTEGER_CST)
	pedwarn (आदान_location, OPT_Wpedantic,
		 "case label is not an integer constant expression");
    }

  जर (c_switch_चळत == रिक्त)
    {
      जर (खालचा_मूल्य)
	error_at (loc, "case label not within a switch statement");
      अन्यथा
	error_at (loc, "%<default%> label not within a switch statement");
      परत NULL_वृक्ष;
    }

  जर (c_check_switch_jump_warnings (c_switch_चळत->bindings,
				    अभिव्यक्ती_LOCATION (c_switch_चळत->switch_stmt),
				    loc))
    परत NULL_वृक्ष;

  label = c_add_case_label (loc, c_switch_चळत->cases,
			    SWITCH_STMT_COND (c_switch_चळत->switch_stmt),
			    खालचा_मूल्य, वरचा_मूल्य, attrs);
  जर (label == error_mark_गाठ)
    label = NULL_वृक्ष;
  परत label;
}

/* Finish the switch statement.  TYPE is the original type of the
   controlling expression of the switch, or NULL_TREE.  */

शून्य
c_finish_switch (वृक्ष body, वृक्ष type)
{
  संरचना c_switch *cs = c_switch_चळत;
  location_t switch_location;

  SWITCH_STMT_BODY (cs->switch_stmt) = body;

  /* Emit warnings as needed.  */
  switch_location = अभिव्यक्ती_LOCATION (cs->switch_stmt);
  c_do_switch_warnings (cs->cases, switch_location,
			type ? type : SWITCH_STMT_TYPE (cs->switch_stmt),
			SWITCH_STMT_COND (cs->switch_stmt), cs->bool_cond_p);
  जर (c_switch_covers_all_cases_p (cs->cases,
				   SWITCH_STMT_TYPE (cs->switch_stmt)))
    SWITCH_STMT_ALL_CASES_P (cs->switch_stmt) = 1;
  SWITCH_STMT_NO_BREAK_P (cs->switch_stmt) = !cs->break_stmt_seen_p;

  /* Pop the stack.  */
  c_switch_चळत = cs->next;
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

  stmt = build3 (COND_अभिव्यक्ती, void_type_गाठ, cond, then_block, else_block);
  SET_अभिव्यक्ती_LOCATION (stmt, if_locus);
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

  जर (is_break)
    निवड (in_statement & ~IN_NAMED_STMT)
      {
      स्थिती 0:
	error_at (loc, "break statement not within loop or switch");
	परत NULL_वृक्ष;
      स्थिती IN_OMP_BLOCK:
	error_at (loc, "invalid exit from OpenMP structured block");
	परत NULL_वृक्ष;
      स्थिती IN_OMP_FOR:
	error_at (loc, "break statement used with OpenMP for loop");
	परत NULL_वृक्ष;
      स्थिती IN_ITERATION_STMT:
      स्थिती IN_OBJC_FOREACH:
	थांबा;
      पूर्वनिर्धारित:
	gcc_assert (in_statement & IN_SWITCH_STMT);
	c_switch_चळत->break_stmt_seen_p = सत्य;
	थांबा;
      }
  अन्यथा
    निवड (in_statement & ~(IN_SWITCH_STMT | IN_NAMED_STMT))
      {
      स्थिती 0:
	error_at (loc, "continue statement not within a loop");
	परत NULL_वृक्ष;
      स्थिती IN_OMP_BLOCK:
	error_at (loc, "invalid exit from OpenMP structured block");
	परत NULL_वृक्ष;
      स्थिती IN_ITERATION_STMT:
      स्थिती IN_OMP_FOR:
      स्थिती IN_OBJC_FOREACH:
	थांबा;
      पूर्वनिर्धारित:
	gcc_unreachable ();
      }

  जर (skip)
    परत NULL_वृक्ष;
  अन्यथा जर ((in_statement & IN_OBJC_FOREACH)
	   && !(is_break && (in_statement & IN_SWITCH_STMT))
	   && name == NULL_वृक्ष)
    {
      /* The foreach expander produces low-level code using gotos instead
	 of a structured loop construct.  */
      gcc_assert (label);
      परत add_stmt (build_stmt (loc, GOTO_अभिव्यक्ती, label));
    }
  अन्यथा जर (name && C_DECL_LOOP_NAME (name) && C_DECL_SWITCH_NAME (name))
    {
      label = DECL_CHAIN (name);
      जर (!is_break)
	label = DECL_CHAIN (label);
      /* Foreach expander from some outer level.  */
      परत add_stmt (build_stmt (loc, GOTO_अभिव्यक्ती, label));
    }
  परत add_stmt (build_stmt (loc, is_break ? BREAK_STMT : CONTINUE_STMT,
			       name));
}

/* A helper routine for c_process_expr_stmt and c_finish_stmt_expr.  */

स्थिर शून्य
emit_side_effect_warnings (location_t loc, वृक्ष अभिव्यक्ती)
{
  maybe_warn_nodiscard (loc, अभिव्यक्ती);
  जर (!warn_unused_मूल्य)
    परत;
  जर (अभिव्यक्ती == error_mark_गाठ)
    ;
  अन्यथा जर (!वृक्ष_SIDE_EFFECTS (अभिव्यक्ती))
    {
      जर (!VOID_TYPE_P (वृक्ष_TYPE (अभिव्यक्ती))
	  && !warning_suppressed_p (अभिव्यक्ती, OPT_Wunused_मूल्य))
	warning_at (loc, OPT_Wunused_मूल्य, "statement with no effect");
    }
  अन्यथा जर (वृक्ष_CODE (अभिव्यक्ती) == COMPOUND_अभिव्यक्ती)
    {
      वृक्ष r = अभिव्यक्ती;
      location_t cloc = loc;
      पर्यंत (वृक्ष_CODE (r) == COMPOUND_अभिव्यक्ती)
	{
	  जर (अभिव्यक्ती_HAS_LOCATION (r))
	    cloc = अभिव्यक्ती_LOCATION (r);
	  r = वृक्ष_OPERAND (r, 1);
	}
      जर (!वृक्ष_SIDE_EFFECTS (r)
	  && !VOID_TYPE_P (वृक्ष_TYPE (r))
	  && !CONVERT_अभिव्यक्ती_P (r)
	  && !warning_suppressed_p (r, OPT_Wunused_मूल्य)
	  && !warning_suppressed_p (अभिव्यक्ती, OPT_Wunused_मूल्य))
	warning_at (cloc, OPT_Wunused_मूल्य,
		    "right-hand operand of comma expression has no effect");
    }
  अन्यथा
    warn_if_unused_मूल्य (अभिव्यक्ती, loc);
}

/* Process an expression as if it were a complete statement.  Emit
   diagnostics, but do not call ADD_STMT.  LOC is the location of the
   statement.  */

वृक्ष
c_process_अभिव्यक्ती_stmt (location_t loc, वृक्ष अभिव्यक्ती)
{
  वृक्ष exprv;

  जर (!अभिव्यक्ती)
    परत NULL_वृक्ष;

  अभिव्यक्ती = c_fully_fold (अभिव्यक्ती, असत्य, रिक्त);

  जर (warn_sequence_point)
    verify_sequence_points (अभिव्यक्ती);

  जर (वृक्ष_TYPE (अभिव्यक्ती) != error_mark_गाठ
      && !COMPLETE_OR_VOID_TYPE_P (वृक्ष_TYPE (अभिव्यक्ती))
      && वृक्ष_CODE (वृक्ष_TYPE (अभिव्यक्ती)) != ARRAY_TYPE)
    error_at (loc, "expression statement has incomplete type");

  /* If we're not processing a statement expression, warn about unused values.
     Warnings for statement expressions will be emitted later, once we figure
     out which is the result.  */
  जर (!STATEMENT_LIST_STMT_अभिव्यक्ती (cur_stmt_list)
      && (warn_unused_मूल्य || warn_unused_result))
    emit_side_effect_warnings (अभिव्यक्ती_LOC_OR_LOC (अभिव्यक्ती, loc), अभिव्यक्ती);

  exprv = अभिव्यक्ती;
  पर्यंत (वृक्ष_CODE (exprv) == COMPOUND_अभिव्यक्ती)
    exprv = वृक्ष_OPERAND (exprv, 1);
  पर्यंत (CONVERT_अभिव्यक्ती_P (exprv))
    exprv = वृक्ष_OPERAND (exprv, 0);
  जर (DECL_P (exprv)
      || handled_component_p (exprv)
      || वृक्ष_CODE (exprv) == ADDR_अभिव्यक्ती)
    mark_exp_read (exprv);

  /* If the expression is not of a type to which we cannot assign a line
     number, wrap the thing in a no-op NOP_EXPR.  */
  जर (DECL_P (अभिव्यक्ती) || CONSTANT_CLASS_P (अभिव्यक्ती))
    {
      अभिव्यक्ती = build1 (NOP_अभिव्यक्ती, वृक्ष_TYPE (अभिव्यक्ती), अभिव्यक्ती);
      SET_अभिव्यक्ती_LOCATION (अभिव्यक्ती, loc);
    }

  परत अभिव्यक्ती;
}

/* Emit an expression as a statement.  LOC is the location of the
   expression.  */

वृक्ष
c_finish_अभिव्यक्ती_stmt (location_t loc, वृक्ष अभिव्यक्ती)
{
  जर (अभिव्यक्ती)
    परत add_stmt (c_process_अभिव्यक्ती_stmt (loc, अभिव्यक्ती));
  अन्यथा
    परत रिक्त;
}

/* Do the opposite and emit a statement as an expression.  To begin,
   create a new binding level and return it.  */

वृक्ष
c_begin_stmt_अभिव्यक्ती (शून्य)
{
  वृक्ष ret;

  /* We must force a BLOCK for this level so that, if it is not expanded
     later, there is a way to turn off the entire subtree of blocks that
     are contained in it.  */
  keep_next_level ();
  ret = c_begin_compound_stmt (सत्य);

  c_bindings_start_stmt_अभिव्यक्ती (c_switch_चळत == रिक्त
			      ? रिक्त
			      : c_switch_चळत->bindings);

  /* Mark the current statement list as belonging to a statement list.  */
  STATEMENT_LIST_STMT_अभिव्यक्ती (ret) = 1;

  परत ret;
}

/* LOC is the location of the compound statement to which this body
   belongs.  */

वृक्ष
c_finish_stmt_अभिव्यक्ती (location_t loc, वृक्ष body)
{
  वृक्ष last, type, tmp, val;
  वृक्ष *last_p;

  body = c_end_compound_stmt (loc, body, सत्य);

  c_bindings_end_stmt_अभिव्यक्ती (c_switch_चळत == रिक्त
			    ? रिक्त
			    : c_switch_चळत->bindings);

  /* Locate the last statement in BODY.  See c_end_compound_stmt
     about always returning a BIND_EXPR.  */
  last_p = &BIND_अभिव्यक्ती_BODY (body);
  last = BIND_अभिव्यक्ती_BODY (body);

 continue_searching:
  जर (वृक्ष_CODE (last) == STATEMENT_LIST)
    {
      वृक्ष_stmt_iterator l = tsi_last (last);

      पर्यंत (!tsi_end_p (l) && वृक्ष_CODE (tsi_stmt (l)) == DEBUG_BEGIN_STMT)
	tsi_prev (&l);

      /* This can happen with degenerate cases like ({ }).  No value.  */
      जर (tsi_end_p (l))
	परत body;

      /* If we're supposed to generate side effects warnings, process
	 all of the statements except the last.  */
      जर (warn_unused_मूल्य || warn_unused_result)
	{
	  साठी (वृक्ष_stmt_iterator i = tsi_start (last);
	       tsi_stmt (i) != tsi_stmt (l); tsi_next (&i))
	    {
	      location_t tloc;
	      वृक्ष t = tsi_stmt (i);

	      tloc = अभिव्यक्ती_HAS_LOCATION (t) ? अभिव्यक्ती_LOCATION (t) : loc;
	      emit_side_effect_warnings (tloc, t);
	    }
	}
      last_p = tsi_stmt_ptr (l);
      last = *last_p;
    }

  /* If the end of the list is exception related, then the list was split
     by a call to push_cleanup.  Continue searching.  */
  जर (वृक्ष_CODE (last) == TRY_FINALLY_अभिव्यक्ती
      || वृक्ष_CODE (last) == TRY_CATCH_अभिव्यक्ती)
    {
      last_p = &वृक्ष_OPERAND (last, 0);
      last = *last_p;
      जा continue_searching;
    }

  जर (last == error_mark_गाठ)
    परत last;

  /* In the case that the BIND_EXPR is not necessary, return the
     expression out from inside it.  */
  जर ((last == BIND_अभिव्यक्ती_BODY (body)
       /* Skip nested debug stmts.  */
       || last == अभिव्यक्ती_first (BIND_अभिव्यक्ती_BODY (body)))
      && BIND_अभिव्यक्ती_VARS (body) == रिक्त)
    {
      /* Even if this looks constant, do not allow it in a constant
	 expression.  */
      last = c_wrap_maybe_const (last, सत्य);
      /* Do not warn if the return value of a statement expression is
	 unused.  */
      suppress_warning (last, OPT_Wunused);
      परत last;
    }

  /* Extract the type of said expression.  */
  type = वृक्ष_TYPE (last);

  /* If we're not returning a value at all, then the BIND_EXPR that
     we already have is a fine expression to return.  */
  जर (!type || VOID_TYPE_P (type))
    परत body;

  /* Now that we've located the expression containing the value, it seems
     silly to make voidify_wrapper_expr repeat the process.  Create a
     temporary of the appropriate type and stick it in a TARGET_EXPR.  */
  tmp = create_tmp_var_raw (type);

  /* Unwrap a no-op NOP_EXPR as added by c_finish_expr_stmt.  This avoids
     tree_expr_nonnegative_p giving up immediately.  */
  val = last;
  जर (वृक्ष_CODE (val) == NOP_अभिव्यक्ती
      && वृक्ष_TYPE (val) == वृक्ष_TYPE (वृक्ष_OPERAND (val, 0)))
    val = वृक्ष_OPERAND (val, 0);

  *last_p = build2 (MODIFY_अभिव्यक्ती, void_type_गाठ, tmp, val);
  SET_अभिव्यक्ती_LOCATION (*last_p, अभिव्यक्ती_LOCATION (last));

  {
    वृक्ष t = build4 (TARGET_अभिव्यक्ती, type, tmp, body, NULL_वृक्ष, NULL_वृक्ष);
    SET_अभिव्यक्ती_LOCATION (t, loc);
    परत t;
  }
}

/* Begin and end compound statements.  This is as simple as pushing
   and popping new statement lists from the tree.  */

वृक्ष
c_begin_compound_stmt (तार्किक do_scope)
{
  वृक्ष stmt = ढकला_stmt_list ();
  जर (do_scope)
    ढकला_scope ();
  परत stmt;
}

/* End a compound statement.  STMT is the statement.  LOC is the
   location of the compound statement-- this is usually the location
   of the opening brace.  */

वृक्ष
c_end_compound_stmt (location_t loc, वृक्ष stmt, तार्किक do_scope)
{
  वृक्ष block = रिक्त;

  जर (do_scope)
    {
      जर (c_dialect_objc ())
	objc_clear_super_receiver ();
      block = काढा_scope ();
    }

  stmt = काढा_stmt_list (stmt);
  stmt = c_build_bind_अभिव्यक्ती (loc, block, stmt);

  /* If this compound statement is nested immediately inside a statement
     expression, then force a BIND_EXPR to be created.  Otherwise we'll
     do the wrong thing for ({ { 1; } }) or ({ 1; { } }).  In particular,
     STATEMENT_LISTs merge, and thus we can lose track of what statement
     was really last.  */
  जर (building_stmt_list_p ()
      && STATEMENT_LIST_STMT_अभिव्यक्ती (cur_stmt_list)
      && वृक्ष_CODE (stmt) != BIND_अभिव्यक्ती)
    {
      stmt = build3 (BIND_अभिव्यक्ती, void_type_गाठ, रिक्त, stmt, रिक्त);
      वृक्ष_SIDE_EFFECTS (stmt) = 1;
      SET_अभिव्यक्ती_LOCATION (stmt, loc);
    }

  परत stmt;
}

/* Queue a cleanup.  CLEANUP is an expression/statement to be executed
   when the current scope is exited.  EH_ONLY is true when this is not
   meant to apply to normal control flow transfer.  */

शून्य
ढकला_cleanup (वृक्ष decl, वृक्ष cleanup, तार्किक eh_only)
{
  गणना वृक्ष_code code;
  वृक्ष stmt, list;
  तार्किक stmt_अभिव्यक्ती;

  code = eh_only ? TRY_CATCH_अभिव्यक्ती : TRY_FINALLY_अभिव्यक्ती;
  stmt = build_stmt (DECL_SOURCE_LOCATION (decl), code, रिक्त, cleanup);
  add_stmt (stmt);
  stmt_अभिव्यक्ती = STATEMENT_LIST_STMT_अभिव्यक्ती (cur_stmt_list);
  list = ढकला_stmt_list ();
  वृक्ष_OPERAND (stmt, 0) = list;
  STATEMENT_LIST_STMT_अभिव्यक्ती (list) = stmt_अभिव्यक्ती;
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
  परत build3 (VEC_COND_अभिव्यक्ती, type, cmp, minus_one_vec, zero_vec);
}

/* Possibly warn about an address of OP never being NULL in a comparison
   operation CODE involving null.  */

स्थिर शून्य
maybe_warn_for_null_address (location_t loc, वृक्ष op, वृक्ष_code code)
{
  /* Prevent warnings issued for macro expansion.  */
  जर (!warn_address
      || warning_suppressed_p (op, OPT_Waddress)
      || from_macro_expansion_at (loc))
    परत;

  जर (वृक्ष_CODE (op) == NOP_अभिव्यक्ती)
    {
      /* Allow casts to intptr_t to suppress the warning.  */
      वृक्ष type = वृक्ष_TYPE (op);
      जर (वृक्ष_CODE (type) == INTEGER_TYPE)
	परत;
      op = वृक्ष_OPERAND (op, 0);
    }

  जर (वृक्ष_CODE (op) == POINTER_PLUS_अभिव्यक्ती)
    {
      /* Allow a cast to void* to suppress the warning.  */
      वृक्ष type = वृक्ष_TYPE (वृक्ष_TYPE (op));
      जर (VOID_TYPE_P (type))
	परत;

      /* Adding any value to a null pointer, including zero, is undefined
	 in C.  This includes the expression &p[0] where p is the null
	 pointer, although &p[0] will have been folded to p by this point
	 and so not diagnosed.  */
      जर (code == EQ_अभिव्यक्ती)
	warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<false%> "
		    "for the pointer operand in %qE must not be NULL",
		    op);
      अन्यथा
	warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<true%> "
		    "for the pointer operand in %qE must not be NULL",
		    op);

      परत;
    }

  जर (वृक्ष_CODE (op) != ADDR_अभिव्यक्ती)
    परत;

  op = वृक्ष_OPERAND (op, 0);

  जर (वृक्ष_CODE (op) == IMAGPART_अभिव्यक्ती
      || वृक्ष_CODE (op) == REALPART_अभिव्यक्ती)
    {
      /* The address of either complex part may not be null.  */
      जर (code == EQ_अभिव्यक्ती)
	warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<false%> "
		    "for the address of %qE will never be NULL",
		    op);
      अन्यथा
	warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<true%> "
		    "for the address of %qE will never be NULL",
		    op);
      परत;
    }

  /* Set to true in the loop below if OP dereferences is operand.
     In such a case the ultimate target need not be a decl for
     the null [in]equality test to be constant.  */
  तार्किक deref = असत्य;

  /* Get the outermost array or object, or member.  */
  पर्यंत (handled_component_p (op))
    {
      जर (वृक्ष_CODE (op) == COMPONENT_REF)
	{
	  /* Get the member (its address is never null).  */
	  op = वृक्ष_OPERAND (op, 1);
	  थांबा;
	}

      /* Get the outer array/object to refer to in the warning.  */
      op = वृक्ष_OPERAND (op, 0);
      deref = सत्य;
    }

  जर ((!deref && !decl_with_nonnull_addr_p (op))
      || from_macro_expansion_at (loc))
    परत;

  तार्किक w;
  जर (code == EQ_अभिव्यक्ती)
    w = warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<false%> "
		    "for the address of %qE will never be NULL",
		    op);
  अन्यथा
    w = warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<true%> "
		    "for the address of %qE will never be NULL",
		    op);

  जर (w && DECL_P (op))
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
build_द्विमान_op (location_t location, गणना वृक्ष_code code,
		 वृक्ष orig_op0, वृक्ष orig_op1, तार्किक convert_p)
{
  वृक्ष type0, type1, orig_type0, orig_type1;
  वृक्ष eptype;
  गणना वृक्ष_code code0, code1;
  वृक्ष op0, op1;
  वृक्ष ret = error_mark_गाठ;
  स्थिरांक अक्षर *invalid_op_diag;
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
  पूर्णांक converted = 0;

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
  पूर्णांक shorten = 0;

  /* Nonzero if this is a comparison operation;
     if both args are promoted shorts, compare the original shorts.
     Also implies COMMON.  */
  पूर्णांक short_compare = 0;

  /* Nonzero if this is a right-shift operation, which can be computed on the
     original short and then promoted if the operand is a promoted short.  */
  पूर्णांक short_shift = 0;

  /* Nonzero means set RESULT_TYPE to the common type of the args.  */
  पूर्णांक common = 0;

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
  वृक्ष instrument_अभिव्यक्ती = रिक्त;

  जर (location == UNKNOWN_LOCATION)
    location = आदान_location;

  op0 = orig_op0;
  op1 = orig_op1;

  op0_int_operands = अभिव्यक्ती_INT_CONST_OPERANDS (orig_op0);
  जर (op0_int_operands)
    op0 = remove_c_maybe_const_अभिव्यक्ती (op0);
  op1_int_operands = अभिव्यक्ती_INT_CONST_OPERANDS (orig_op1);
  जर (op1_int_operands)
    op1 = remove_c_maybe_const_अभिव्यक्ती (op1);
  int_operands = (op0_int_operands && op1_int_operands);
  जर (int_operands)
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
  जर (convert_p
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

  जर (code0 == ERROR_MARK || code1 == ERROR_MARK)
    परत error_mark_गाठ;

  जर (code0 == POINTER_TYPE
      && reject_gcc_builtin (op0, अभिव्यक्ती_LOCATION (orig_op0)))
    परत error_mark_गाठ;

  जर (code1 == POINTER_TYPE
      && reject_gcc_builtin (op1, अभिव्यक्ती_LOCATION (orig_op1)))
    परत error_mark_गाठ;

  जर ((invalid_op_diag
       = targetm.invalid_द्विमान_op (code, type0, type1)))
    {
      error_at (location, invalid_op_diag);
      परत error_mark_गाठ;
    }

  निवड (code)
    {
    स्थिती PLUS_अभिव्यक्ती:
    स्थिती MINUS_अभिव्यक्ती:
    स्थिती MULT_अभिव्यक्ती:
    स्थिती TRUNC_DIV_अभिव्यक्ती:
    स्थिती CEIL_DIV_अभिव्यक्ती:
    स्थिती FLOOR_DIV_अभिव्यक्ती:
    स्थिती ROUND_DIV_अभिव्यक्ती:
    स्थिती EXACT_DIV_अभिव्यक्ती:
      may_need_excess_precision = सत्य;
      थांबा;

    स्थिती EQ_अभिव्यक्ती:
    स्थिती NE_अभिव्यक्ती:
    स्थिती LE_अभिव्यक्ती:
    स्थिती GE_अभिव्यक्ती:
    स्थिती LT_अभिव्यक्ती:
    स्थिती GT_अभिव्यक्ती:
      /* Excess precision for implicit conversions of integers to
	 floating point in C11 and later.  */
      may_need_excess_precision = (flag_isoc11
				   && (ANY_INTEGRAL_TYPE_P (type0)
				       || ANY_INTEGRAL_TYPE_P (type1)));
      थांबा;

    पूर्वनिर्धारित:
      may_need_excess_precision = असत्य;
      थांबा;
    }
  जर (वृक्ष_CODE (op0) == EXCESS_PRECISION_अभिव्यक्ती)
    {
      op0 = वृक्ष_OPERAND (op0, 0);
      type0 = वृक्ष_TYPE (op0);
    }
  अन्यथा जर (may_need_excess_precision
	   && (eptype = excess_precision_type (type0)) != NULL_वृक्ष)
    {
      type0 = eptype;
      op0 = convert (eptype, op0);
    }
  जर (वृक्ष_CODE (op1) == EXCESS_PRECISION_अभिव्यक्ती)
    {
      op1 = वृक्ष_OPERAND (op1, 0);
      type1 = वृक्ष_TYPE (op1);
    }
  अन्यथा जर (may_need_excess_precision
	   && (eptype = excess_precision_type (type1)) != NULL_वृक्ष)
    {
      type1 = eptype;
      op1 = convert (eptype, op1);
    }

  objc_ok = objc_compare_types (type0, type1, -3, NULL_वृक्ष);

  /* In case when one of the operands of the binary operation is
     a vector and another is a scalar -- convert scalar to vector.  */
  जर ((gnu_vector_type_p (type0) && code1 != VECTOR_TYPE)
      || (gnu_vector_type_p (type1) && code0 != VECTOR_TYPE))
    {
      गणना stv_conv convert_flag = scalar_to_vector (location, code, orig_op0,
						     orig_op1, सत्य);

      निवड (convert_flag)
	{
	  स्थिती stv_error:
	    परत error_mark_गाठ;
	  स्थिती stv_firstarg:
	    {
              तार्किक maybe_const = सत्य;
              वृक्ष sc;
              sc = c_fully_fold (op0, असत्य, &maybe_const);
              sc = save_अभिव्यक्ती (sc);
              sc = convert (वृक्ष_TYPE (type1), sc);
              op0 = build_vector_from_val (type1, sc);
              जर (!maybe_const)
                op0 = c_wrap_maybe_const (op0, सत्य);
              orig_type0 = type0 = वृक्ष_TYPE (op0);
              code0 = वृक्ष_CODE (type0);
              converted = 1;
              थांबा;
	    }
	  स्थिती stv_secondarg:
	    {
	      तार्किक maybe_const = सत्य;
	      वृक्ष sc;
	      sc = c_fully_fold (op1, असत्य, &maybe_const);
	      sc = save_अभिव्यक्ती (sc);
	      sc = convert (वृक्ष_TYPE (type0), sc);
	      op1 = build_vector_from_val (type0, sc);
	      जर (!maybe_const)
		op1 = c_wrap_maybe_const (op1, सत्य);
	      orig_type1 = type1 = वृक्ष_TYPE (op1);
	      code1 = वृक्ष_CODE (type1);
	      converted = 1;
	      थांबा;
	    }
	  पूर्वनिर्धारित:
	    थांबा;
	}
    }

  निवड (code)
    {
    स्थिती PLUS_अभिव्यक्ती:
      /* Handle the pointer + int case.  */
      जर (code0 == POINTER_TYPE
	  && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  ret = pointer_int_sum (location, PLUS_अभिव्यक्ती, op0, op1);
	  जा return_build_द्विमान_op;
	}
      अन्यथा जर (code1 == POINTER_TYPE
	       && (code0 == INTEGER_TYPE || code0 == BITINT_TYPE))
	{
	  ret = pointer_int_sum (location, PLUS_अभिव्यक्ती, op1, op0);
	  जा return_build_द्विमान_op;
	}
      अन्यथा
	common = 1;
      थांबा;

    स्थिती MINUS_अभिव्यक्ती:
      /* Subtraction of two similar pointers.
	 We must subtract them as integers, then divide by object size.  */
      जर (code0 == POINTER_TYPE && code1 == POINTER_TYPE
	  && comp_target_types (location, type0, type1))
	{
	  ret = pointer_diff (location, op0, op1, &instrument_अभिव्यक्ती);
	  जा return_build_द्विमान_op;
	}
      /* Handle pointer minus int.  Just like pointer plus int.  */
      अन्यथा जर (code0 == POINTER_TYPE
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  ret = pointer_int_sum (location, MINUS_अभिव्यक्ती, op0, op1);
	  जा return_build_द्विमान_op;
	}
      अन्यथा
	common = 1;
      थांबा;

    स्थिती MULT_अभिव्यक्ती:
      common = 1;
      थांबा;

    स्थिती TRUNC_DIV_अभिव्यक्ती:
    स्थिती CEIL_DIV_अभिव्यक्ती:
    स्थिती FLOOR_DIV_अभिव्यक्ती:
    स्थिती ROUND_DIV_अभिव्यक्ती:
    स्थिती EXACT_DIV_अभिव्यक्ती:
      doing_div_or_mod = सत्य;
      warn_for_div_by_zero (location, op1);

      जर ((code0 == INTEGER_TYPE || code0 == REAL_TYPE
	   || code0 == FIXED_POINT_TYPE || code0 == BITINT_TYPE
	   || code0 == COMPLEX_TYPE
	   || gnu_vector_type_p (type0))
	  && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	      || code1 == FIXED_POINT_TYPE || code1 == BITINT_TYPE
	      || code1 == COMPLEX_TYPE
	      || gnu_vector_type_p (type1)))
	{
	  गणना वृक्ष_code tcode0 = code0, tcode1 = code1;

	  जर (code0 == COMPLEX_TYPE || code0 == VECTOR_TYPE)
	    tcode0 = वृक्ष_CODE (वृक्ष_TYPE (वृक्ष_TYPE (op0)));
	  जर (code1 == COMPLEX_TYPE || code1 == VECTOR_TYPE)
	    tcode1 = वृक्ष_CODE (वृक्ष_TYPE (वृक्ष_TYPE (op1)));

	  जर (!(((tcode0 == INTEGER_TYPE || tcode0 == BITINT_TYPE
		  || (tcode0 == ENUMERAL_TYPE && code0 == VECTOR_TYPE))
		 && (tcode1 == INTEGER_TYPE || tcode1 == BITINT_TYPE
		     || (tcode1 == ENUMERAL_TYPE && code1 == VECTOR_TYPE)))
		|| (tcode0 == FIXED_POINT_TYPE && tcode1 == FIXED_POINT_TYPE)))
	    resultcode = RDIV_अभिव्यक्ती;
	  अन्यथा
	    /* Although it would be tempting to shorten always here, that
	       loses on some targets, since the modulo instruction is
	       undefined if the quotient can't be represented in the
	       computation mode.  We shorten only if unsigned or if
	       dividing by something we know != -1.  */
	    shorten = may_shorten_divmod (op0, op1);
	  common = 1;
	}
      थांबा;

    स्थिती BIT_AND_अभिव्यक्ती:
    स्थिती BIT_IOR_अभिव्यक्ती:
    स्थिती BIT_XOR_अभिव्यक्ती:
      जर ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	shorten = -1;
      /* Allow vector types which are not floating point types.   */
      अन्यथा जर (gnu_vector_type_p (type0)
	       && gnu_vector_type_p (type1)
	       && !VECTOR_FLOAT_TYPE_P (type0)
	       && !VECTOR_FLOAT_TYPE_P (type1))
	common = 1;
      थांबा;

    स्थिती TRUNC_MOD_अभिव्यक्ती:
    स्थिती FLOOR_MOD_अभिव्यक्ती:
      doing_div_or_mod = सत्य;
      warn_for_div_by_zero (location, op1);

      जर (gnu_vector_type_p (type0)
	  && gnu_vector_type_p (type1)
	  && वृक्ष_CODE (वृक्ष_TYPE (type0)) == INTEGER_TYPE
	  && वृक्ष_CODE (वृक्ष_TYPE (type1)) == INTEGER_TYPE)
	common = 1;
      अन्यथा जर ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  /* Although it would be tempting to shorten always here, that loses
	     on some targets, since the modulo instruction is undefined if the
	     quotient can't be represented in the computation mode.  We shorten
	     only if unsigned or if dividing by something we know != -1.  */
	  shorten = may_shorten_divmod (op0, op1);
	  common = 1;
	}
      थांबा;

    स्थिती TRUTH_ANDIF_अभिव्यक्ती:
    स्थिती TRUTH_ORIF_अभिव्यक्ती:
    स्थिती TRUTH_AND_अभिव्यक्ती:
    स्थिती TRUTH_OR_अभिव्यक्ती:
    स्थिती TRUTH_XOR_अभिव्यक्ती:
      जर ((code0 == INTEGER_TYPE || code0 == POINTER_TYPE
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
	  result_type = integer_type_गाठ;
	  जर (op0_int_operands)
	    {
	      op0 = c_objc_common_truthvalue_conversion (location, orig_op0);
	      op0 = remove_c_maybe_const_अभिव्यक्ती (op0);
	    }
	  अन्यथा
	    op0 = c_objc_common_truthvalue_conversion (location, op0);
	  जर (op1_int_operands)
	    {
	      op1 = c_objc_common_truthvalue_conversion (location, orig_op1);
	      op1 = remove_c_maybe_const_अभिव्यक्ती (op1);
	    }
	  अन्यथा
	    op1 = c_objc_common_truthvalue_conversion (location, op1);
	  converted = 1;
	  boolean_op = सत्य;
	}
      जर (code == TRUTH_ANDIF_अभिव्यक्ती)
	{
	  int_const_or_overflow = (int_operands
				   && वृक्ष_CODE (orig_op0) == INTEGER_CST
				   && (op0 == truthvalue_false_गाठ
				       || वृक्ष_CODE (orig_op1) == INTEGER_CST));
	  int_const = (int_const_or_overflow
		       && !वृक्ष_OVERFLOW (orig_op0)
		       && (op0 == truthvalue_false_गाठ
			   || !वृक्ष_OVERFLOW (orig_op1)));
	}
      अन्यथा जर (code == TRUTH_ORIF_अभिव्यक्ती)
	{
	  int_const_or_overflow = (int_operands
				   && वृक्ष_CODE (orig_op0) == INTEGER_CST
				   && (op0 == truthvalue_true_गाठ
				       || वृक्ष_CODE (orig_op1) == INTEGER_CST));
	  int_const = (int_const_or_overflow
		       && !वृक्ष_OVERFLOW (orig_op0)
		       && (op0 == truthvalue_true_गाठ
			   || !वृक्ष_OVERFLOW (orig_op1)));
	}
      थांबा;

      /* Shift operations: result has same type as first operand;
	 always convert second operand to int.
	 Also set SHORT_SHIFT if shifting rightward.  */

    स्थिती RSHIFT_अभिव्यक्ती:
      जर (gnu_vector_type_p (type0)
	  && gnu_vector_type_p (type1)
	  && वृक्ष_CODE (वृक्ष_TYPE (type0)) == INTEGER_TYPE
	  && वृक्ष_CODE (वृक्ष_TYPE (type1)) == INTEGER_TYPE
	  && known_eq (TYPE_VECTOR_SUBPARTS (type0),
		       TYPE_VECTOR_SUBPARTS (type1)))
	{
	  result_type = type0;
	  converted = 1;
	}
      अन्यथा जर ((code0 == INTEGER_TYPE || code0 == FIXED_POINT_TYPE
		|| code0 == BITINT_TYPE
		|| (gnu_vector_type_p (type0)
		    && वृक्ष_CODE (वृक्ष_TYPE (type0)) == INTEGER_TYPE))
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  doing_shift = सत्य;
	  जर (वृक्ष_CODE (op1) == INTEGER_CST)
	    {
	      जर (वृक्ष_int_cst_sgn (op1) < 0)
		{
		  int_const = असत्य;
		  जर (c_inhibit_evaluation_warnings == 0)
		    warning_at (location, OPT_Wshift_मोजणी_negative,
				"right shift count is negative");
		}
	      अन्यथा जर (code0 == VECTOR_TYPE)
		{
		  जर (compare_वृक्ष_int (op1,
					TYPE_PRECISION (वृक्ष_TYPE (type0)))
		      >= 0)
		    {
		      int_const = असत्य;
		      जर (c_inhibit_evaluation_warnings == 0)
			warning_at (location, OPT_Wshift_मोजणी_overflow,
				    "right shift count >= width of vector element");
		    }
		}
	      अन्यथा
		{
		  जर (!integer_zerop (op1))
		    short_shift = 1;

		  जर (compare_वृक्ष_int (op1, TYPE_PRECISION (type0)) >= 0)
		    {
		      int_const = असत्य;
		      जर (c_inhibit_evaluation_warnings == 0)
			warning_at (location, OPT_Wshift_मोजणी_overflow,
				    "right shift count >= width of type");
		    }
		}
	    }

	  /* Use the type of the value to be shifted.  */
	  result_type = type0;
	  /* Avoid converting op1 to result_type later.  */
	  converted = 1;
	}
      थांबा;

    स्थिती LSHIFT_अभिव्यक्ती:
      जर (gnu_vector_type_p (type0)
	  && gnu_vector_type_p (type1)
	  && वृक्ष_CODE (वृक्ष_TYPE (type0)) == INTEGER_TYPE
	  && वृक्ष_CODE (वृक्ष_TYPE (type1)) == INTEGER_TYPE
	  && known_eq (TYPE_VECTOR_SUBPARTS (type0),
		       TYPE_VECTOR_SUBPARTS (type1)))
	{
	  result_type = type0;
	  converted = 1;
	}
      अन्यथा जर ((code0 == INTEGER_TYPE || code0 == FIXED_POINT_TYPE
		|| code0 == BITINT_TYPE
		|| (gnu_vector_type_p (type0)
		    && वृक्ष_CODE (वृक्ष_TYPE (type0)) == INTEGER_TYPE))
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  doing_shift = सत्य;
	  जर (वृक्ष_CODE (op0) == INTEGER_CST
	      && वृक्ष_int_cst_sgn (op0) < 0
	      && !TYPE_OVERFLOW_WRAPS (type0))
	    {
	      /* Don't reject a left shift of a negative value in a context
		 where a constant expression is needed in C90.  */
	      जर (flag_isoc99)
		int_const = असत्य;
	      जर (c_inhibit_evaluation_warnings == 0)
		warning_at (location, OPT_Wshift_negative_मूल्य,
			    "left shift of negative value");
	    }
	  जर (वृक्ष_CODE (op1) == INTEGER_CST)
	    {
	      जर (वृक्ष_int_cst_sgn (op1) < 0)
		{
		  int_const = असत्य;
		  जर (c_inhibit_evaluation_warnings == 0)
		    warning_at (location, OPT_Wshift_मोजणी_negative,
				"left shift count is negative");
		}
	      अन्यथा जर (code0 == VECTOR_TYPE)
		{
		  जर (compare_वृक्ष_int (op1,
					TYPE_PRECISION (वृक्ष_TYPE (type0)))
		      >= 0)
		    {
		      int_const = असत्य;
		      जर (c_inhibit_evaluation_warnings == 0)
			warning_at (location, OPT_Wshift_मोजणी_overflow,
				    "left shift count >= width of vector element");
		    }
		}
	      अन्यथा जर (compare_वृक्ष_int (op1, TYPE_PRECISION (type0)) >= 0)
		{
		  int_const = असत्य;
		  जर (c_inhibit_evaluation_warnings == 0)
		    warning_at (location, OPT_Wshift_मोजणी_overflow,
				"left shift count >= width of type");
		}
	      अन्यथा जर (वृक्ष_CODE (op0) == INTEGER_CST
		       && maybe_warn_shift_overflow (location, op0, op1)
		       && flag_isoc99)
		int_const = असत्य;
	    }

	  /* Use the type of the value to be shifted.  */
	  result_type = type0;
	  /* Avoid converting op1 to result_type later.  */
	  converted = 1;
	}
      थांबा;

    स्थिती EQ_अभिव्यक्ती:
    स्थिती NE_अभिव्यक्ती:
      जर (gnu_vector_type_p (type0) && gnu_vector_type_p (type1))
        {
          वृक्ष intt;
	  जर (!vector_types_compatible_elements_p (type0, type1))
            {
              error_at (location, "comparing vectors with different "
                                  "element types");
              परत error_mark_गाठ;
            }

	  जर (maybe_ne (TYPE_VECTOR_SUBPARTS (type0),
			TYPE_VECTOR_SUBPARTS (type1)))
            {
              error_at (location, "comparing vectors with different "
                                  "number of elements");
              परत error_mark_गाठ;
            }

	  /* It's not precisely specified how the usual arithmetic
	     conversions apply to the vector types.  Here, we use
	     the unsigned type if one of the operands is signed and
	     the other one is unsigned.  */
	  जर (TYPE_UNSIGNED (type0) != TYPE_UNSIGNED (type1))
	    {
	      जर (!TYPE_UNSIGNED (type0))
		op0 = build1 (VIEW_CONVERT_अभिव्यक्ती, type1, op0);
	      अन्यथा
		op1 = build1 (VIEW_CONVERT_अभिव्यक्ती, type0, op1);
	      warning_at (location, OPT_Wsign_compare, "comparison between "
			  "types %qT and %qT", type0, type1);
	    }

          /* Always construct signed integer vector type.  */
	  जर (VECTOR_BOOLEAN_TYPE_P (type0) && VECTOR_BOOLEAN_TYPE_P (type1))
	    result_type = type0;
	  अन्यथा
	    {
	      स्वतः nelts = TYPE_VECTOR_SUBPARTS (type0);

	      intt = c_common_type_for_size (GET_MODE_BITSIZE
					     (SCALAR_TYPE_MODE
						(वृक्ष_TYPE (type0))), 0);
	      जर (!intt)
		{
		  error_at (location, "could not find an integer type "
				      "of the same size as %qT",
			    वृक्ष_TYPE (type0));
		  परत error_mark_गाठ;
		}
	      result_type = build_opaque_vector_type (intt, nelts);
	    }
          converted = 1;
	  ret = build_vec_cmp (resultcode, result_type, op0, op1);
	  जा return_build_द्विमान_op;
        }
      जर (FLOAT_TYPE_P (type0) || FLOAT_TYPE_P (type1))
	warning_at (location,
		    OPT_Wfloat_equal,
		    "comparing floating-point with %<==%> or %<!=%> is unsafe");
      /* Result of comparison is always int,
	 but don't convert the args to int!  */
      build_type = integer_type_गाठ;
      जर ((code0 == INTEGER_TYPE || code0 == REAL_TYPE || code0 == BITINT_TYPE
	   || code0 == FIXED_POINT_TYPE || code0 == COMPLEX_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	      || code1 == BITINT_TYPE
	      || code1 == FIXED_POINT_TYPE || code1 == COMPLEX_TYPE))
	short_compare = 1;
      अन्यथा जर (code0 == POINTER_TYPE
	       && (code1 == NULLPTR_TYPE
		   || null_pointer_constant_p (orig_op1)))
	{
	  maybe_warn_for_null_address (location, op0, code);
	  result_type = type0;
	}
      अन्यथा जर (code1 == POINTER_TYPE
	       && (code0 == NULLPTR_TYPE
		   || null_pointer_constant_p (orig_op0)))
	{
	  maybe_warn_for_null_address (location, op1, code);
	  result_type = type1;
	}
      अन्यथा जर (code0 == POINTER_TYPE && code1 == POINTER_TYPE)
	{
	  वृक्ष tt0 = वृक्ष_TYPE (type0);
	  वृक्ष tt1 = वृक्ष_TYPE (type1);
	  addr_space_t as0 = TYPE_ADDR_SPACE (tt0);
	  addr_space_t as1 = TYPE_ADDR_SPACE (tt1);
	  addr_space_t as_common = ADDR_SPACE_GENERIC;

	  /* Anything compares with void *.  void * compares with anything.
	     Otherwise, the targets must be compatible
	     and both must be object or both incomplete.  */
	  जर (comp_target_types (location, type0, type1))
	    result_type = common_pointer_type (type0, type1, NULL_वृक्ष);
	  अन्यथा जर (!addr_space_superset (as0, as1, &as_common))
	    {
	      error_at (location, "comparison of pointers to "
			"disjoint address spaces");
	      परत error_mark_गाठ;
	    }
	  अन्यथा जर (VOID_TYPE_P (tt0) && !TYPE_ATOMIC (tt0))
	    {
	      जर (pedantic && वृक्ष_CODE (tt1) == FUNCTION_TYPE)
		pedwarn (location, OPT_Wpedantic, "ISO C forbids "
			 "comparison of %<void *%> with function pointer");
	    }
	  अन्यथा जर (VOID_TYPE_P (tt1) && !TYPE_ATOMIC (tt1))
	    {
	      जर (pedantic && वृक्ष_CODE (tt0) == FUNCTION_TYPE)
		pedwarn (location, OPT_Wpedantic, "ISO C forbids "
			 "comparison of %<void *%> with function pointer");
	    }
	  अन्यथा
	    /* Avoid warning about the volatile ObjC EH puts on decls.  */
	    जर (!objc_ok)
	      pedwarn (location, OPT_Wcompare_distinct_pointer_types,
		       "comparison of distinct pointer types lacks a cast");

	  जर (result_type == NULL_वृक्ष)
	    {
	      पूर्णांक qual = ENCODE_QUAL_ADDR_SPACE (as_common);
	      result_type = c_build_pointer_type
			      (c_build_qualified_type (void_type_गाठ, qual));
	    }
	}
      अन्यथा जर (code0 == POINTER_TYPE
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  result_type = type0;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}
      अन्यथा जर ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	       && code1 == POINTER_TYPE)
	{
	  result_type = type1;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}
      /* 6.5.9: One of the following shall hold:
	 -- both operands have type nullptr_t;  */
      अन्यथा जर (code0 == NULLPTR_TYPE && code1 == NULLPTR_TYPE)
	{
	  result_type = nullptr_type_गाठ;
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
      अन्यथा जर (code0 == NULLPTR_TYPE && null_pointer_constant_p (orig_op1))
	result_type = (INTEGRAL_TYPE_P (type1)
		       ? c_build_pointer_type (type1) : type1);
      अन्यथा जर (code1 == NULLPTR_TYPE && null_pointer_constant_p (orig_op0))
	result_type = (INTEGRAL_TYPE_P (type0)
		       ? c_build_pointer_type (type0) : type0);
      जर ((C_BOOLEAN_TYPE_P (वृक्ष_TYPE (orig_op0))
	   || truth_मूल्य_p (वृक्ष_CODE (orig_op0)))
	  ^ (C_BOOLEAN_TYPE_P (वृक्ष_TYPE (orig_op1))
	     || truth_मूल्य_p (वृक्ष_CODE (orig_op1))))
	maybe_warn_bool_compare (location, code, orig_op0, orig_op1);
      थांबा;

    स्थिती LE_अभिव्यक्ती:
    स्थिती GE_अभिव्यक्ती:
    स्थिती LT_अभिव्यक्ती:
    स्थिती GT_अभिव्यक्ती:
      जर (gnu_vector_type_p (type0) && gnu_vector_type_p (type1))
        {
          वृक्ष intt;
	  जर (!vector_types_compatible_elements_p (type0, type1))
            {
              error_at (location, "comparing vectors with different "
                                  "element types");
              परत error_mark_गाठ;
            }

	  जर (maybe_ne (TYPE_VECTOR_SUBPARTS (type0),
			TYPE_VECTOR_SUBPARTS (type1)))
            {
              error_at (location, "comparing vectors with different "
                                  "number of elements");
              परत error_mark_गाठ;
            }

	  /* It's not precisely specified how the usual arithmetic
	     conversions apply to the vector types.  Here, we use
	     the unsigned type if one of the operands is signed and
	     the other one is unsigned.  */
	  जर (TYPE_UNSIGNED (type0) != TYPE_UNSIGNED (type1))
	    {
	      जर (!TYPE_UNSIGNED (type0))
		op0 = build1 (VIEW_CONVERT_अभिव्यक्ती, type1, op0);
	      अन्यथा
		op1 = build1 (VIEW_CONVERT_अभिव्यक्ती, type0, op1);
	      warning_at (location, OPT_Wsign_compare, "comparison between "
			  "types %qT and %qT", type0, type1);
	    }

          /* Always construct signed integer vector type.  */
          intt = c_common_type_for_size (GET_MODE_BITSIZE
					 (SCALAR_TYPE_MODE
					  (वृक्ष_TYPE (type0))), 0);
	  जर (!intt)
	    {
	      error_at (location, "could not find an integer type "
				  "of the same size as %qT",
			वृक्ष_TYPE (type0));
	      परत error_mark_गाठ;
	    }
          result_type = build_opaque_vector_type (intt,
						  TYPE_VECTOR_SUBPARTS (type0));
          converted = 1;
	  ret = build_vec_cmp (resultcode, result_type, op0, op1);
	  जा return_build_द्विमान_op;
        }
      build_type = integer_type_गाठ;
      जर ((code0 == INTEGER_TYPE || code0 == REAL_TYPE
	   || code0 == BITINT_TYPE || code0 == FIXED_POINT_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	      || code1 == BITINT_TYPE || code1 == FIXED_POINT_TYPE))
	short_compare = 1;
      अन्यथा जर (code0 == POINTER_TYPE && code1 == POINTER_TYPE)
	{
	  addr_space_t as0 = TYPE_ADDR_SPACE (वृक्ष_TYPE (type0));
	  addr_space_t as1 = TYPE_ADDR_SPACE (वृक्ष_TYPE (type1));
	  addr_space_t as_common;

	  जर (comp_target_types (location, type0, type1))
	    {
	      result_type = common_pointer_type (type0, type1, NULL_वृक्ष);
	      जर (!COMPLETE_TYPE_P (वृक्ष_TYPE (type0))
		  != !COMPLETE_TYPE_P (वृक्ष_TYPE (type1)))
		pedwarn_c99 (location, OPT_Wpedantic,
			     "comparison of complete and incomplete pointers");
	      अन्यथा जर (वृक्ष_CODE (वृक्ष_TYPE (type0)) == FUNCTION_TYPE)
		pedwarn (location, OPT_Wpedantic, "ISO C forbids "
			 "ordered comparisons of pointers to functions");
	      अन्यथा जर (null_pointer_constant_p (orig_op0)
		       || null_pointer_constant_p (orig_op1))
		warning_at (location, OPT_Wextra,
			    "ordered comparison of pointer with null pointer");

	    }
	  अन्यथा जर (!addr_space_superset (as0, as1, &as_common))
	    {
	      error_at (location, "comparison of pointers to "
			"disjoint address spaces");
	      परत error_mark_गाठ;
	    }
	  अन्यथा
	    {
	      पूर्णांक qual = ENCODE_QUAL_ADDR_SPACE (as_common);
	      result_type = c_build_pointer_type
			      (c_build_qualified_type (void_type_गाठ, qual));
              pedwarn (location, OPT_Wcompare_distinct_pointer_types,
                       "comparison of distinct pointer types lacks a cast");
	    }
	}
      अन्यथा जर (code0 == POINTER_TYPE && null_pointer_constant_p (orig_op1))
	{
	  result_type = type0;
	  जर (pedantic)
	    pedwarn (location, OPT_Wpedantic,
		     "ordered comparison of pointer with integer zero");
	  अन्यथा जर (extra_warnings)
	    warning_at (location, OPT_Wextra,
			"ordered comparison of pointer with integer zero");
	}
      अन्यथा जर (code1 == POINTER_TYPE && null_pointer_constant_p (orig_op0))
	{
	  result_type = type1;
	  जर (pedantic)
	    pedwarn (location, OPT_Wpedantic,
		     "ordered comparison of pointer with integer zero");
	  अन्यथा जर (extra_warnings)
	    warning_at (location, OPT_Wextra,
			"ordered comparison of pointer with integer zero");
	}
      अन्यथा जर (code0 == POINTER_TYPE
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  result_type = type0;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}
      अन्यथा जर ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	       && code1 == POINTER_TYPE)
	{
	  result_type = type1;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}

      जर ((code0 == POINTER_TYPE || code1 == POINTER_TYPE)
	  && current_function_decl != NULL_वृक्ष
	  && sanitize_flags_p (SANITIZE_POINTER_COMPARE))
	{
	  op0 = save_अभिव्यक्ती (c_fully_fold (op0, असत्य, रिक्त));
	  op1 = save_अभिव्यक्ती (c_fully_fold (op1, असत्य, रिक्त));

	  वृक्ष tt = builtin_decl_explicit (BUILT_IN_ASAN_POINTER_COMPARE);
	  instrument_अभिव्यक्ती = build_call_अभिव्यक्ती_loc (location, tt, 2, op0, op1);
	}

      जर ((C_BOOLEAN_TYPE_P (वृक्ष_TYPE (orig_op0))
	   || truth_मूल्य_p (वृक्ष_CODE (orig_op0)))
	  ^ (C_BOOLEAN_TYPE_P (वृक्ष_TYPE (orig_op1))
	     || truth_मूल्य_p (वृक्ष_CODE (orig_op1))))
	maybe_warn_bool_compare (location, code, orig_op0, orig_op1);
      थांबा;

    स्थिती MIN_अभिव्यक्ती:
    स्थिती MAX_अभिव्यक्ती:
      /* Used for OpenMP atomics.  */
      gcc_assert (flag_openmp);
      common = 1;
      थांबा;

    पूर्वनिर्धारित:
      gcc_unreachable ();
    }

  जर (code0 == ERROR_MARK || code1 == ERROR_MARK)
    परत error_mark_गाठ;

  जर (gnu_vector_type_p (type0)
      && gnu_vector_type_p (type1)
      && (!वृक्ष_int_cst_equal (TYPE_SIZE (type0), TYPE_SIZE (type1))
	  || !vector_types_compatible_elements_p (type0, type1)))
    {
      gcc_rich_location richloc (location);
      maybe_range_label_for_वृक्ष_type_mismatch
	label_for_op0 (orig_op0, orig_op1),
	label_for_op1 (orig_op1, orig_op0);
      richloc.maybe_add_अभिव्यक्ती (orig_op0, &label_for_op0, highlight_colors::lhs);
      richloc.maybe_add_अभिव्यक्ती (orig_op1, &label_for_op1, highlight_colors::rhs);
      द्विमान_op_error (&richloc, code, type0, type1);
      परत error_mark_गाठ;
    }

  जर ((code0 == INTEGER_TYPE || code0 == REAL_TYPE || code0 == COMPLEX_TYPE
       || code0 == FIXED_POINT_TYPE || code0 == BITINT_TYPE
       || gnu_vector_type_p (type0))
      && (code1 == INTEGER_TYPE || code1 == REAL_TYPE || code1 == COMPLEX_TYPE
	  || code1 == FIXED_POINT_TYPE || code1 == BITINT_TYPE
	  || gnu_vector_type_p (type1)))
    {
      तार्किक first_complex = (code0 == COMPLEX_TYPE);
      तार्किक second_complex = (code1 == COMPLEX_TYPE);
      पूर्णांक none_complex = (!first_complex && !second_complex);

      जर (shorten || common || short_compare)
	{
	  result_type = c_common_type (type0, type1);
	  do_warn_double_promotion (result_type, type0, type1,
				    "implicit conversion from %qT to %qT "
				    "to match other operand of binary "
				    "expression",
				    location);
	  जर (result_type == error_mark_गाठ)
	    परत error_mark_गाठ;
	}

      जर (first_complex != second_complex
	  && (code == PLUS_अभिव्यक्ती
	      || code == MINUS_अभिव्यक्ती
	      || code == MULT_अभिव्यक्ती
	      || (code == TRUNC_DIV_अभिव्यक्ती && first_complex))
	  && वृक्ष_CODE (वृक्ष_TYPE (result_type)) == REAL_TYPE
	  && flag_signed_zeros)
	{
	  /* An operation on mixed real/complex operands must be
	     handled specially, but the language-independent code can
	     more easily optimize the plain complex arithmetic if
	     -fno-signed-zeros.  */
	  वृक्ष real_type = वृक्ष_TYPE (result_type);
	  वृक्ष real, imag;
	  जर (type0 != orig_type0 || type1 != orig_type1)
	    {
	      gcc_assert (may_need_excess_precision && common);
	      semantic_result_type = c_common_type (orig_type0, orig_type1);
	    }
	  जर (first_complex)
	    {
	      जर (वृक्ष_TYPE (op0) != result_type)
		op0 = convert_and_check (location, result_type, op0);
	      जर (वृक्ष_TYPE (op1) != real_type)
		op1 = convert_and_check (location, real_type, op1);
	    }
	  अन्यथा
	    {
	      जर (वृक्ष_TYPE (op0) != real_type)
		op0 = convert_and_check (location, real_type, op0);
	      जर (वृक्ष_TYPE (op1) != result_type)
		op1 = convert_and_check (location, result_type, op1);
	    }
	  जर (वृक्ष_CODE (op0) == ERROR_MARK || वृक्ष_CODE (op1) == ERROR_MARK)
	    परत error_mark_गाठ;
	  जर (first_complex)
	    {
	      op0 = save_अभिव्यक्ती (op0);
	      real = build_unary_op (अभिव्यक्ती_LOCATION (orig_op0), REALPART_अभिव्यक्ती,
				     op0, सत्य);
	      imag = build_unary_op (अभिव्यक्ती_LOCATION (orig_op0), IMAGPART_अभिव्यक्ती,
				     op0, सत्य);
	      निवड (code)
		{
		स्थिती MULT_अभिव्यक्ती:
		स्थिती TRUNC_DIV_अभिव्यक्ती:
		  op1 = save_अभिव्यक्ती (op1);
		  imag = build2 (resultcode, real_type, imag, op1);
		  /* Fall through.  */
		स्थिती PLUS_अभिव्यक्ती:
		स्थिती MINUS_अभिव्यक्ती:
		  real = build2 (resultcode, real_type, real, op1);
		  थांबा;
		पूर्वनिर्धारित:
		  gcc_unreachable();
		}
	    }
	  अन्यथा
	    {
	      op1 = save_अभिव्यक्ती (op1);
	      real = build_unary_op (अभिव्यक्ती_LOCATION (orig_op1), REALPART_अभिव्यक्ती,
				     op1, सत्य);
	      imag = build_unary_op (अभिव्यक्ती_LOCATION (orig_op1), IMAGPART_अभिव्यक्ती,
				     op1, सत्य);
	      निवड (code)
		{
		स्थिती MULT_अभिव्यक्ती:
		  op0 = save_अभिव्यक्ती (op0);
		  imag = build2 (resultcode, real_type, op0, imag);
		  /* Fall through.  */
		स्थिती PLUS_अभिव्यक्ती:
		  real = build2 (resultcode, real_type, op0, real);
		  थांबा;
		स्थिती MINUS_अभिव्यक्ती:
		  real = build2 (resultcode, real_type, op0, real);
		  imag = build1 (NEGATE_अभिव्यक्ती, real_type, imag);
		  थांबा;
		पूर्वनिर्धारित:
		  gcc_unreachable();
		}
	    }
	  ret = build2 (COMPLEX_अभिव्यक्ती, result_type, real, imag);
	  जा return_build_द्विमान_op;
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

      जर (shorten && none_complex)
	{
	  final_type = result_type;
	  result_type = shorten_द्विमान_op (result_type, op0, op1,
					   shorten == -1);
	}

      /* Shifts can be shortened if shifting right.  */

      जर (short_shift)
	{
	  पूर्णांक unsigned_arg;
	  वृक्ष arg0 = get_narrower (op0, &unsigned_arg);

	  final_type = result_type;

	  जर (arg0 == op0 && final_type == वृक्ष_TYPE (op0))
	    unsigned_arg = TYPE_UNSIGNED (वृक्ष_TYPE (op0));

	  जर (TYPE_PRECISION (वृक्ष_TYPE (arg0)) < TYPE_PRECISION (result_type)
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
	      जर (वृक्ष_TYPE (op0) != result_type)
		op0 = convert (result_type, op0);
	      converted = 1;
	    }
	}

      /* Comparison operations are shortened too but differently.
	 They identify themselves by setting short_compare = 1.  */

      जर (short_compare)
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

	  जर (val != NULL_वृक्ष)
	    {
	      ret = val;
	      जा return_build_द्विमान_op;
	    }

	  op0 = xop0, op1 = xop1;
	  converted = 1;
	  resultcode = xresultcode;

	  जर (c_inhibit_evaluation_warnings == 0 && !c_in_omp_for)
	    {
	      तार्किक op0_maybe_const = सत्य;
	      तार्किक op1_maybe_const = सत्य;
	      वृक्ष orig_op0_folded, orig_op1_folded;

	      जर (in_late_द्विमान_op)
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

	      जर (warn_sign_compare)
		warn_for_sign_compare (location, orig_op0_folded,
				       orig_op1_folded, op0, op1,
				       result_type, resultcode);
	      जर (!in_late_द्विमान_op && !int_operands)
		{
		  जर (!op0_maybe_const || वृक्ष_CODE (op0) != INTEGER_CST)
		    op0 = c_wrap_maybe_const (op0, !op0_maybe_const);
		  जर (!op1_maybe_const || वृक्ष_CODE (op1) != INTEGER_CST)
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

  जर (!result_type)
    {
      /* Favor showing any expression locations that are available. */
      op_location_t oploc (location, UNKNOWN_LOCATION);
      द्विमान_op_rich_location richloc (oploc, orig_op0, orig_op1, सत्य);
      द्विमान_op_error (&richloc, code, वृक्ष_TYPE (op0), वृक्ष_TYPE (op1));
      परत error_mark_गाठ;
    }

  जर (build_type == NULL_वृक्ष)
    {
      build_type = result_type;
      जर ((type0 != orig_type0 || type1 != orig_type1)
	  && !boolean_op)
	{
	  gcc_assert (may_need_excess_precision && common);
	  semantic_result_type = c_common_type (orig_type0, orig_type1);
	}
    }

  जर (!converted)
    {
      op0 = ep_convert_and_check (location, result_type, op0,
				  semantic_result_type);
      op1 = ep_convert_and_check (location, result_type, op1,
				  semantic_result_type);

      /* This can happen if one operand has a vector type, and the other
	 has a different type.  */
      जर (वृक्ष_CODE (op0) == ERROR_MARK || वृक्ष_CODE (op1) == ERROR_MARK)
	परत error_mark_गाठ;
    }

  जर (sanitize_flags_p ((SANITIZE_SHIFT
			 | SANITIZE_DIVIDE
			 | SANITIZE_FLOAT_DIVIDE
			 | SANITIZE_SI_OVERFLOW))
      && current_function_decl != NULL_वृक्ष
      && (doing_div_or_mod || doing_shift)
      && !require_constant_मूल्य)
    {
      /* OP0 and/or OP1 might have side-effects.  */
      op0 = save_अभिव्यक्ती (op0);
      op1 = save_अभिव्यक्ती (op1);
      op0 = c_fully_fold (op0, असत्य, रिक्त);
      op1 = c_fully_fold (op1, असत्य, रिक्त);
      जर (doing_div_or_mod && (sanitize_flags_p ((SANITIZE_DIVIDE
						  | SANITIZE_FLOAT_DIVIDE
						  | SANITIZE_SI_OVERFLOW))))
	instrument_अभिव्यक्ती = ubsan_instrument_division (location, op0, op1);
      अन्यथा जर (doing_shift && sanitize_flags_p (SANITIZE_SHIFT))
	instrument_अभिव्यक्ती = ubsan_instrument_shift (location, code, op0, op1);
    }

  /* Treat expressions in initializers specially as they can't trap.  */
  जर (int_const_or_overflow)
    ret = (require_constant_मूल्य
	   ? fold_build2_initializer_loc (location, resultcode, build_type,
					  op0, op1)
	   : fold_build2_loc (location, resultcode, build_type, op0, op1));
  अन्यथा
    ret = build2 (resultcode, build_type, op0, op1);
  जर (final_type != NULL_वृक्ष)
    ret = convert (final_type, ret);

 return_build_द्विमान_op:
  gcc_assert (ret != error_mark_गाठ);
  जर (वृक्ष_CODE (ret) == INTEGER_CST && !वृक्ष_OVERFLOW (ret) && !int_const)
    ret = (int_operands
	   ? note_integer_operands (ret)
	   : build1 (NOP_अभिव्यक्ती, वृक्ष_TYPE (ret), ret));
  अन्यथा जर (वृक्ष_CODE (ret) != INTEGER_CST && int_operands
	   && !in_late_द्विमान_op)
    ret = note_integer_operands (ret);
  protected_set_अभिव्यक्ती_location (ret, location);

  जर (instrument_अभिव्यक्ती != रिक्त)
    ret = fold_build2 (COMPOUND_अभिव्यक्ती, वृक्ष_TYPE (ret),
		       instrument_अभिव्यक्ती, ret);

  जर (semantic_result_type)
    ret = build1_loc (location, EXCESS_PRECISION_अभिव्यक्ती,
		      semantic_result_type, ret);

  परत ret;
}


/* Convert EXPR to be a truth-value (type TYPE), validating its type for this
   purpose.  LOCATION is the source location for the expression.  */

वृक्ष
c_objc_common_truthvalue_conversion (location_t location, वृक्ष अभिव्यक्ती, वृक्ष type)
{
  तार्किक int_const, int_operands;

  निवड (वृक्ष_CODE (वृक्ष_TYPE (अभिव्यक्ती)))
    {
    स्थिती ARRAY_TYPE:
      error_at (location, "used array that cannot be converted to pointer where scalar is required");
      परत error_mark_गाठ;

    स्थिती RECORD_TYPE:
      error_at (location, "used struct type value where scalar is required");
      परत error_mark_गाठ;

    स्थिती UNION_TYPE:
      error_at (location, "used union type value where scalar is required");
      परत error_mark_गाठ;

    स्थिती VOID_TYPE:
      error_at (location, "void value not ignored as it ought to be");
      परत error_mark_गाठ;

    स्थिती POINTER_TYPE:
      जर (reject_gcc_builtin (अभिव्यक्ती))
	परत error_mark_गाठ;
      थांबा;

    स्थिती FUNCTION_TYPE:
      gcc_unreachable ();

    स्थिती VECTOR_TYPE:
      error_at (location, "used vector type where scalar is required");
      परत error_mark_गाठ;

    पूर्वनिर्धारित:
      थांबा;
    }

  /* Conversion of a floating constant to boolean goes through here
     and yields an integer constant expression.  Otherwise, the result
     is only an integer constant expression if the argument is.  */
  int_const = ((वृक्ष_CODE (अभिव्यक्ती) == INTEGER_CST && !वृक्ष_OVERFLOW (अभिव्यक्ती))
	       || ((वृक्ष_CODE (अभिव्यक्ती) == REAL_CST
		    || वृक्ष_CODE (अभिव्यक्ती) == COMPLEX_CST)
		   && (वृक्ष_CODE (type) == BOOLEAN_TYPE
		       || (वृक्ष_CODE (type) == ENUMERAL_TYPE
			   && ENUM_UNDERLYING_TYPE (type) != NULL_वृक्ष
			   && (वृक्ष_CODE (ENUM_UNDERLYING_TYPE (type))
			       == BOOLEAN_TYPE)))));
  int_operands = अभिव्यक्ती_INT_CONST_OPERANDS (अभिव्यक्ती);
  जर (int_operands && वृक्ष_CODE (अभिव्यक्ती) != INTEGER_CST)
    {
      अभिव्यक्ती = remove_c_maybe_const_अभिव्यक्ती (अभिव्यक्ती);
      अभिव्यक्ती = build2 (NE_अभिव्यक्ती, type, अभिव्यक्ती,
		     convert (वृक्ष_TYPE (अभिव्यक्ती), integer_zero_गाठ));
      अभिव्यक्ती = note_integer_operands (अभिव्यक्ती);
    }
  अन्यथा
    {
      /* ??? Should we also give an error for vectors rather than leaving
	 those to give errors later?  */
      अभिव्यक्ती = c_common_truthvalue_conversion (location, अभिव्यक्ती);
      अभिव्यक्ती = fold_convert_loc (location, type, अभिव्यक्ती);
    }

  जर (वृक्ष_CODE (अभिव्यक्ती) == INTEGER_CST && int_operands && !int_const)
    {
      जर (वृक्ष_OVERFLOW (अभिव्यक्ती))
	परत अभिव्यक्ती;
      अन्यथा
	परत note_integer_operands (अभिव्यक्ती);
    }
  जर (वृक्ष_CODE (अभिव्यक्ती) == INTEGER_CST && !int_const)
    परत build1 (NOP_अभिव्यक्ती, वृक्ष_TYPE (अभिव्यक्ती), अभिव्यक्ती);
  परत अभिव्यक्ती;
}


/* Convert EXPR to a contained DECL, updating *TC, *TI and *SE as
   required.  */

वृक्ष
c_अभिव्यक्ती_to_decl (वृक्ष अभिव्यक्ती, तार्किक *tc ATTRIBUTE_UNUSED, तार्किक *se)
{
  जर (वृक्ष_CODE (अभिव्यक्ती) == COMPOUND_LITERAL_अभिव्यक्ती)
    {
      वृक्ष decl = COMPOUND_LITERAL_अभिव्यक्ती_DECL (अभिव्यक्ती);
      /* Executing a compound literal inside a function reinitializes
	 it.  */
      जर (!वृक्ष_STATIC (decl))
	*se = सत्य;
      परत decl;
    }
  अन्यथा
    परत अभिव्यक्ती;
}

/* Generate OMP construct CODE, with BODY and CLAUSES as its compound
   statement.  LOC is the location of the construct.  */

वृक्ष
c_finish_omp_construct (location_t loc, गणना वृक्ष_code code, वृक्ष body,
			वृक्ष clauses)
{
  body = c_end_compound_stmt (loc, body, सत्य);

  वृक्ष stmt = make_गाठ (code);
  वृक्ष_TYPE (stmt) = void_type_गाठ;
  OMP_BODY (stmt) = body;
  OMP_CLAUSES (stmt) = clauses;
  SET_अभिव्यक्ती_LOCATION (stmt, loc);

  परत add_stmt (stmt);
}

/* Generate OACC_DATA, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the OACC_DATA.  */

वृक्ष
c_finish_oacc_data (location_t loc, वृक्ष clauses, वृक्ष block)
{
  वृक्ष stmt;

  block = c_end_compound_stmt (loc, block, सत्य);

  stmt = make_गाठ (OACC_DATA);
  वृक्ष_TYPE (stmt) = void_type_गाठ;
  OACC_DATA_CLAUSES (stmt) = clauses;
  OACC_DATA_BODY (stmt) = block;
  SET_अभिव्यक्ती_LOCATION (stmt, loc);

  परत add_stmt (stmt);
}

/* Generate OACC_HOST_DATA, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the OACC_HOST_DATA.  */

वृक्ष
c_finish_oacc_host_data (location_t loc, वृक्ष clauses, वृक्ष block)
{
  वृक्ष stmt;

  block = c_end_compound_stmt (loc, block, सत्य);

  stmt = make_गाठ (OACC_HOST_DATA);
  वृक्ष_TYPE (stmt) = void_type_गाठ;
  OACC_HOST_DATA_CLAUSES (stmt) = clauses;
  OACC_HOST_DATA_BODY (stmt) = block;
  SET_अभिव्यक्ती_LOCATION (stmt, loc);

  परत add_stmt (stmt);
}

/* Like c_begin_compound_stmt, except force the retention of the BLOCK.  */

वृक्ष
c_begin_omp_parallel (शून्य)
{
  वृक्ष block;

  keep_next_level ();
  block = c_begin_compound_stmt (सत्य);

  परत block;
}

/* Generate OMP_PARALLEL, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the OMP_PARALLEL.  */

वृक्ष
c_finish_omp_parallel (location_t loc, वृक्ष clauses, वृक्ष block)
{
  वृक्ष stmt;

  block = c_end_compound_stmt (loc, block, सत्य);

  stmt = make_गाठ (OMP_PARALLEL);
  वृक्ष_TYPE (stmt) = void_type_गाठ;
  OMP_PARALLEL_CLAUSES (stmt) = clauses;
  OMP_PARALLEL_BODY (stmt) = block;
  SET_अभिव्यक्ती_LOCATION (stmt, loc);

  परत add_stmt (stmt);
}

/* Like c_begin_compound_stmt, except force the retention of the BLOCK.  */

वृक्ष
c_begin_omp_task (शून्य)
{
  वृक्ष block;

  keep_next_level ();
  block = c_begin_compound_stmt (सत्य);

  परत block;
}

/* Generate OMP_TASK, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the #pragma.  */

वृक्ष
c_finish_omp_task (location_t loc, वृक्ष clauses, वृक्ष block)
{
  वृक्ष stmt;

  block = c_end_compound_stmt (loc, block, सत्य);

  stmt = make_गाठ (OMP_TASK);
  वृक्ष_TYPE (stmt) = void_type_गाठ;
  OMP_TASK_CLAUSES (stmt) = clauses;
  OMP_TASK_BODY (stmt) = block;
  SET_अभिव्यक्ती_LOCATION (stmt, loc);

  परत add_stmt (stmt);
}

/* Generate GOMP_cancel call for #pragma omp cancel.  */

शून्य
c_finish_omp_cancel (location_t loc, वृक्ष clauses)
{
  वृक्ष fn = builtin_decl_explicit (BUILT_IN_GOMP_CANCEL);
  पूर्णांक mask = 0;
  जर (omp_find_clause (clauses, OMP_CLAUSE_PARALLEL))
    mask = 1;
  अन्यथा जर (omp_find_clause (clauses, OMP_CLAUSE_FOR))
    mask = 2;
  अन्यथा जर (omp_find_clause (clauses, OMP_CLAUSE_SECTIONS))
    mask = 4;
  अन्यथा जर (omp_find_clause (clauses, OMP_CLAUSE_TASKGROUP))
    mask = 8;
  अन्यथा
    {
      error_at (loc, "%<#pragma omp cancel%> must specify one of "
		     "%<parallel%>, %<for%>, %<sections%> or %<taskgroup%> "
		     "clauses");
      परत;
    }
  वृक्ष ifc = omp_find_clause (clauses, OMP_CLAUSE_IF);
  जर (ifc != NULL_वृक्ष)
    {
      जर (OMP_CLAUSE_IF_MODIFIER (ifc) != ERROR_MARK
	  && OMP_CLAUSE_IF_MODIFIER (ifc) != VOID_CST)
	error_at (OMP_CLAUSE_LOCATION (ifc),
		  "expected %<cancel%> %<if%> clause modifier");
      अन्यथा
	{
	  वृक्ष ifc2 = omp_find_clause (OMP_CLAUSE_CHAIN (ifc), OMP_CLAUSE_IF);
	  जर (ifc2 != NULL_वृक्ष)
	    {
	      gcc_assert (OMP_CLAUSE_IF_MODIFIER (ifc) == VOID_CST
			  && OMP_CLAUSE_IF_MODIFIER (ifc2) != ERROR_MARK
			  && OMP_CLAUSE_IF_MODIFIER (ifc2) != VOID_CST);
	      error_at (OMP_CLAUSE_LOCATION (ifc2),
			"expected %<cancel%> %<if%> clause modifier");
	    }
	}

      वृक्ष type = वृक्ष_TYPE (OMP_CLAUSE_IF_अभिव्यक्ती (ifc));
      ifc = fold_build2_loc (OMP_CLAUSE_LOCATION (ifc), NE_अभिव्यक्ती,
			     boolean_type_गाठ, OMP_CLAUSE_IF_अभिव्यक्ती (ifc),
			     build_zero_cst (type));
    }
  अन्यथा
    ifc = boolean_true_गाठ;
  वृक्ष stmt = build_call_अभिव्यक्ती_loc (loc, fn, 2,
				   build_int_cst (integer_type_गाठ, mask),
				   ifc);
  add_stmt (stmt);
}

/* Generate GOMP_cancellation_point call for
   #pragma omp cancellation point.  */

शून्य
c_finish_omp_cancellation_point (location_t loc, वृक्ष clauses)
{
  वृक्ष fn = builtin_decl_explicit (BUILT_IN_GOMP_CANCELLATION_POINT);
  पूर्णांक mask = 0;
  जर (omp_find_clause (clauses, OMP_CLAUSE_PARALLEL))
    mask = 1;
  अन्यथा जर (omp_find_clause (clauses, OMP_CLAUSE_FOR))
    mask = 2;
  अन्यथा जर (omp_find_clause (clauses, OMP_CLAUSE_SECTIONS))
    mask = 4;
  अन्यथा जर (omp_find_clause (clauses, OMP_CLAUSE_TASKGROUP))
    mask = 8;
  अन्यथा
    {
      error_at (loc, "%<#pragma omp cancellation point%> must specify one of "
		     "%<parallel%>, %<for%>, %<sections%> or %<taskgroup%> "
		     "clauses");
      परत;
    }
  वृक्ष stmt = build_call_अभिव्यक्ती_loc (loc, fn, 1,
				   build_int_cst (integer_type_गाठ, mask));
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
			     तार्किक &maybe_zero_len, अचिन्हित पूर्णांक &first_non_one,
			     गणना c_omp_region_type ort)
{
  वृक्ष ret, खालचा_bound, length, type;
  तार्किक openacc = (ort & C_ORT_ACC) != 0;
  जर (वृक्ष_CODE (t) != OMP_ARRAY_SECTION)
    {
      जर (error_operand_p (t))
	परत error_mark_गाठ;
      c_omp_address_inspector ai (OMP_CLAUSE_LOCATION (c), t);
      ret = t;
      जर (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
	  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
	  && TYPE_ATOMIC (strip_array_types (वृक्ष_TYPE (t))))
	{
	  error_at (OMP_CLAUSE_LOCATION (c), "%<_Atomic%> %qE in %qs clause",
		    t, omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  परत error_mark_गाठ;
	}
      जर (!ai.check_clause (c))
	परत error_mark_गाठ;
      अन्यथा जर (ai.component_access_p ()
	       && (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TO
		   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_FROM))
	t = ai.get_मूळ_term (सत्य);
      अन्यथा
	t = ai.unconverted_ref_origin ();
      जर (t == error_mark_गाठ)
	परत error_mark_गाठ;
      जर (!VAR_P (t)
	  && (ort == C_ORT_ACC || !अभिव्यक्ती_P (t))
	  && वृक्ष_CODE (t) != PARM_DECL)
	{
	  जर (DECL_P (t))
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD is not a variable in %qs clause", t,
		      omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  अन्यथा
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qE is not a variable in %qs clause", t,
		      omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  परत error_mark_गाठ;
	}
      अन्यथा जर (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
	       && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
	       && TYPE_ATOMIC (वृक्ष_TYPE (t)))
	{
	  error_at (OMP_CLAUSE_LOCATION (c), "%<_Atomic%> %qD in %qs clause",
		    t, omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  परत error_mark_गाठ;
	}
      अन्यथा जर (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
	       && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
	       && VAR_P (t)
	       && DECL_THREAD_LOCAL_P (t))
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "%qD is threadprivate variable in %qs clause", t,
		    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  परत error_mark_गाठ;
	}
      जर ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY
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
      परत ret;
    }

  ret = handle_omp_array_sections_1 (c, वृक्ष_OPERAND (t, 0), types,
				     maybe_zero_len, first_non_one, ort);
  जर (ret == error_mark_गाठ || ret == NULL_वृक्ष)
    परत ret;

  type = वृक्ष_TYPE (ret);
  खालचा_bound = वृक्ष_OPERAND (t, 1);
  length = वृक्ष_OPERAND (t, 2);

  जर (खालचा_bound == error_mark_गाठ || length == error_mark_गाठ)
    परत error_mark_गाठ;

  जर (खालचा_bound && !INTEGRAL_TYPE_P (वृक्ष_TYPE (खालचा_bound)))
    {
      error_at (OMP_CLAUSE_LOCATION (c),
		"low bound %qE of array section does not have integral type",
		खालचा_bound);
      परत error_mark_गाठ;
    }
  जर (length && !INTEGRAL_TYPE_P (वृक्ष_TYPE (length)))
    {
      error_at (OMP_CLAUSE_LOCATION (c),
		"length %qE of array section does not have integral type",
		length);
      परत error_mark_गाठ;
    }
  जर (खालचा_bound
      && वृक्ष_CODE (खालचा_bound) == INTEGER_CST
      && TYPE_PRECISION (वृक्ष_TYPE (खालचा_bound))
	 > TYPE_PRECISION (sizetype))
    खालचा_bound = fold_convert (sizetype, खालचा_bound);
  जर (length
      && वृक्ष_CODE (length) == INTEGER_CST
      && TYPE_PRECISION (वृक्ष_TYPE (length))
	 > TYPE_PRECISION (sizetype))
    length = fold_convert (sizetype, length);
  जर (खालचा_bound == NULL_वृक्ष)
    खालचा_bound = integer_zero_गाठ;
  जर (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
      && (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_ATTACH
	  || OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_DETACH))
    {
      जर (length != integer_one_गाठ)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "expected single pointer in %qs clause",
		    user_omp_clause_code_name (c, openacc));
	  परत error_mark_गाठ;
	}
    }
  जर (length != NULL_वृक्ष)
    {
      जर (!integer_nonzerop (length))
	{
	  जर (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY
	      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
	      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
	      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
	      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TASK_REDUCTION)
	    {
	      जर (integer_zerop (length))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "zero length array section in %qs clause",
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  परत error_mark_गाठ;
		}
	    }
	  अन्यथा
	    maybe_zero_len = सत्य;
	}
      जर (first_non_one == types.length ()
	  && (वृक्ष_CODE (length) != INTEGER_CST || integer_onep (length)))
	first_non_one++;
    }
  जर (वृक्ष_CODE (type) == ARRAY_TYPE)
    {
      जर (length == NULL_वृक्ष
	  && (TYPE_DOMAIN (type) == NULL_वृक्ष
	      || TYPE_MAX_मूल्य (TYPE_DOMAIN (type)) == NULL_वृक्ष))
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "for unknown bound array type length expression must "
		    "be specified");
	  परत error_mark_गाठ;
	}
      जर (वृक्ष_CODE (खालचा_bound) == INTEGER_CST
	  && वृक्ष_int_cst_sgn (खालचा_bound) == -1)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "negative low bound in array section in %qs clause",
		    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  परत error_mark_गाठ;
	}
      जर (length != NULL_वृक्ष
	  && वृक्ष_CODE (length) == INTEGER_CST
	  && वृक्ष_int_cst_sgn (length) == -1)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "negative length in array section in %qs clause",
		    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  परत error_mark_गाठ;
	}
      जर (TYPE_DOMAIN (type)
	  && TYPE_MAX_मूल्य (TYPE_DOMAIN (type))
	  && वृक्ष_CODE (TYPE_MAX_मूल्य (TYPE_DOMAIN (type)))
			== INTEGER_CST)
	{
	  वृक्ष size
	    = fold_convert (sizetype, TYPE_MAX_मूल्य (TYPE_DOMAIN (type)));
	  size = size_binop (PLUS_अभिव्यक्ती, size, size_one_गाठ);
	  जर (वृक्ष_CODE (खालचा_bound) == INTEGER_CST)
	    {
	      जर (वृक्ष_int_cst_lt (size, खालचा_bound))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "low bound %qE above array section size "
			    "in %qs clause", खालचा_bound,
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  परत error_mark_गाठ;
		}
	      जर (वृक्ष_int_cst_equal (size, खालचा_bound))
		{
		  जर (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TASK_REDUCTION)
		    {
		      error_at (OMP_CLAUSE_LOCATION (c),
				"zero length array section in %qs clause",
				omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		      परत error_mark_गाठ;
		    }
		  maybe_zero_len = सत्य;
		}
	      अन्यथा जर (length == NULL_वृक्ष
		       && first_non_one == types.length ()
		       && वृक्ष_int_cst_equal
			    (TYPE_MAX_मूल्य (TYPE_DOMAIN (type)),
			     खालचा_bound))
		first_non_one++;
	    }
	  अन्यथा जर (length == NULL_वृक्ष)
	    {
	      जर (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
		  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
		  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_REDUCTION
		  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_IN_REDUCTION
		  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_TASK_REDUCTION)
		maybe_zero_len = सत्य;
	      जर (first_non_one == types.length ())
		first_non_one++;
	    }
	  जर (length && वृक्ष_CODE (length) == INTEGER_CST)
	    {
	      जर (वृक्ष_int_cst_lt (size, length))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "length %qE above array section size "
			    "in %qs clause", length,
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  परत error_mark_गाठ;
		}
	      जर (वृक्ष_CODE (खालचा_bound) == INTEGER_CST)
		{
		  वृक्ष lbpluslen
		    = size_binop (PLUS_अभिव्यक्ती,
				  fold_convert (sizetype, खालचा_bound),
				  fold_convert (sizetype, length));
		  जर (वृक्ष_CODE (lbpluslen) == INTEGER_CST
		      && वृक्ष_int_cst_lt (size, lbpluslen))
		    {
		      error_at (OMP_CLAUSE_LOCATION (c),
				"high bound %qE above array section size "
				"in %qs clause", lbpluslen,
				omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		      परत error_mark_गाठ;
		    }
		}
	    }
	}
      अन्यथा जर (length == NULL_वृक्ष)
	{
	  जर (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
	      && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
	      && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_REDUCTION
	      && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_IN_REDUCTION
	      && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_TASK_REDUCTION)
	    maybe_zero_len = सत्य;
	  जर (first_non_one == types.length ())
	    first_non_one++;
	}

      /* For [lb:] we will need to evaluate lb more than once.  */
      जर (length == NULL_वृक्ष && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND)
	{
	  वृक्ष lb = save_अभिव्यक्ती (खालचा_bound);
	  जर (lb != खालचा_bound)
	    {
	      वृक्ष_OPERAND (t, 1) = lb;
	      खालचा_bound = lb;
	    }
	}
    }
  अन्यथा जर (वृक्ष_CODE (type) == POINTER_TYPE)
    {
      जर (length == NULL_वृक्ष)
	{
	  जर (वृक्ष_CODE (ret) == PARM_DECL && C_ARRAY_PARAMETER (ret))
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "for array function parameter length expression "
		      "must be specified");
	  अन्यथा
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "for pointer type length expression must be specified");
	  परत error_mark_गाठ;
	}
      जर (length != NULL_वृक्ष
	  && वृक्ष_CODE (length) == INTEGER_CST
	  && वृक्ष_int_cst_sgn (length) == -1)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "negative length in array section in %qs clause",
		    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  परत error_mark_गाठ;
	}
      /* If there is a pointer type anywhere but in the very first
	 array-section-subscript, the array section could be non-contiguous.  */
      जर (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
	  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
	  && वृक्ष_CODE (वृक्ष_OPERAND (t, 0)) == OMP_ARRAY_SECTION)
	{
	  /* If any prior dimension has a non-one length, then deem this
	     array section as non-contiguous.  */
	  साठी (वृक्ष d = वृक्ष_OPERAND (t, 0);
	       वृक्ष_CODE (d) == OMP_ARRAY_SECTION;
	       d = वृक्ष_OPERAND (d, 0))
	    {
	      वृक्ष d_length = वृक्ष_OPERAND (d, 2);
	      जर (d_length == NULL_वृक्ष || !integer_onep (d_length))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "array section is not contiguous in %qs clause",
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  परत error_mark_गाठ;
		}
	    }
	}
    }
  अन्यथा
    {
      error_at (OMP_CLAUSE_LOCATION (c),
		"%qE does not have pointer or array type", ret);
      परत error_mark_गाठ;
    }
  जर (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND)
    types.safe_ढकला (वृक्ष_TYPE (ret));
  /* We will need to evaluate lb more than once.  */
  वृक्ष lb = save_अभिव्यक्ती (खालचा_bound);
  जर (lb != खालचा_bound)
    {
      वृक्ष_OPERAND (t, 1) = lb;
      खालचा_bound = lb;
    }
  ret = build_array_ref (OMP_CLAUSE_LOCATION (c), ret, खालचा_bound);
  परत ret;
}

/* Handle array sections for clause C.  */

स्थिर तार्किक
handle_omp_array_sections (वृक्ष &c, गणना c_omp_region_type ort)
{
  तार्किक maybe_zero_len = असत्य;
  अचिन्हित पूर्णांक first_non_one = 0;
  auto_vec<वृक्ष, 10> types;
  वृक्ष *tp = &OMP_CLAUSE_DECL (c);
  जर ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
       || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY)
      && OMP_ITERATOR_DECL_P (*tp))
    tp = &वृक्ष_मूल्य (*tp);
  वृक्ष first = handle_omp_array_sections_1 (c, *tp, types,
					    maybe_zero_len, first_non_one,
					    ort);
  जर (first == error_mark_गाठ)
    परत सत्य;
  जर (first == NULL_वृक्ष)
    परत असत्य;
  जर (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY)
    {
      वृक्ष t = *tp;
      वृक्ष tem = NULL_वृक्ष;
      /* Need to evaluate side effects in the length expressions
	 if any.  */
      पर्यंत (वृक्ष_CODE (t) == वृक्ष_LIST)
	{
	  जर (वृक्ष_मूल्य (t) && वृक्ष_SIDE_EFFECTS (वृक्ष_मूल्य (t)))
	    {
	      जर (tem == NULL_वृक्ष)
		tem = वृक्ष_मूल्य (t);
	      अन्यथा
		tem = build2 (COMPOUND_अभिव्यक्ती, वृक्ष_TYPE (tem),
			      वृक्ष_मूल्य (t), tem);
	    }
	  t = वृक्ष_CHAIN (t);
	}
      जर (tem)
	first = build2 (COMPOUND_अभिव्यक्ती, वृक्ष_TYPE (first), tem, first);
      first = c_fully_fold (first, असत्य, रिक्त, सत्य);
      *tp = first;
    }
  अन्यथा
    {
      अचिन्हित पूर्णांक अंक = types.length (), i;
      वृक्ष t, side_effects = NULL_वृक्ष, size = NULL_वृक्ष;
      वृक्ष condition = NULL_वृक्ष;

      जर (int_size_in_bytes (वृक्ष_TYPE (first)) <= 0)
	maybe_zero_len = सत्य;

      साठी (i = अंक, t = OMP_CLAUSE_DECL (c); i > 0;
	   t = वृक्ष_OPERAND (t, 0))
	{
	  वृक्ष खालचा_bound = वृक्ष_OPERAND (t, 1);
	  वृक्ष length = वृक्ष_OPERAND (t, 2);

	  i--;
	  जर (खालचा_bound
	      && वृक्ष_CODE (खालचा_bound) == INTEGER_CST
	      && TYPE_PRECISION (वृक्ष_TYPE (खालचा_bound))
		 > TYPE_PRECISION (sizetype))
	    खालचा_bound = fold_convert (sizetype, खालचा_bound);
	  जर (length
	      && वृक्ष_CODE (length) == INTEGER_CST
	      && TYPE_PRECISION (वृक्ष_TYPE (length))
		 > TYPE_PRECISION (sizetype))
	    length = fold_convert (sizetype, length);
	  जर (खालचा_bound == NULL_वृक्ष)
	    खालचा_bound = integer_zero_गाठ;
	  जर (!maybe_zero_len && i > first_non_one)
	    {
	      जर (integer_nonzerop (खालचा_bound))
		जा do_warn_noncontiguous;
	      जर (length != NULL_वृक्ष
		  && वृक्ष_CODE (length) == INTEGER_CST
		  && TYPE_DOMAIN (types[i])
		  && TYPE_MAX_मूल्य (TYPE_DOMAIN (types[i]))
		  && वृक्ष_CODE (TYPE_MAX_मूल्य (TYPE_DOMAIN (types[i])))
		     == INTEGER_CST)
		{
		  वृक्ष size;
		  size = size_binop (PLUS_अभिव्यक्ती,
				     TYPE_MAX_मूल्य (TYPE_DOMAIN (types[i])),
				     size_one_गाठ);
		  जर (!वृक्ष_int_cst_equal (length, size))
		    {
		     do_warn_noncontiguous:
		      error_at (OMP_CLAUSE_LOCATION (c),
				"array section is not contiguous in %qs "
				"clause",
				omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		      परत सत्य;
		    }
		}
	      जर (length != NULL_वृक्ष
		  && वृक्ष_SIDE_EFFECTS (length))
		{
		  जर (side_effects == NULL_वृक्ष)
		    side_effects = length;
		  अन्यथा
		    side_effects = build2 (COMPOUND_अभिव्यक्ती,
					   वृक्ष_TYPE (side_effects),
					   length, side_effects);
		}
	    }
	  अन्यथा
	    {
	      वृक्ष l;

	      जर (i > first_non_one
		  && ((length && integer_nonzerop (length))
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TASK_REDUCTION))
		सुरूठेवा;
	      जर (length)
		l = fold_convert (sizetype, length);
	      अन्यथा
		{
		  l = size_binop (PLUS_अभिव्यक्ती,
				  TYPE_MAX_मूल्य (TYPE_DOMAIN (types[i])),
				  size_one_गाठ);
		  l = size_binop (MINUS_अभिव्यक्ती, l,
				  fold_convert (sizetype, खालचा_bound));
		}
	      जर (i > first_non_one)
		{
		  l = fold_build2 (NE_अभिव्यक्ती, boolean_type_गाठ, l,
				   size_zero_गाठ);
		  जर (condition == NULL_वृक्ष)
		    condition = l;
		  अन्यथा
		    condition = fold_build2 (BIT_AND_अभिव्यक्ती, boolean_type_गाठ,
					     l, condition);
		}
	      अन्यथा जर (size == NULL_वृक्ष)
		{
		  size = size_in_bytes (वृक्ष_TYPE (types[i]));
		  वृक्ष eltype = वृक्ष_TYPE (types[अंक - 1]);
		  पर्यंत (वृक्ष_CODE (eltype) == ARRAY_TYPE)
		    eltype = वृक्ष_TYPE (eltype);
		  जर (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TASK_REDUCTION)
		    {
		      जर (integer_zerop (size)
			  || integer_zerop (size_in_bytes (eltype)))
			{
			  error_at (OMP_CLAUSE_LOCATION (c),
				    "zero length array section in %qs clause",
				    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
			  परत error_mark_गाठ;
			}
		      size = size_binop (EXACT_DIV_अभिव्यक्ती, size,
					 size_in_bytes (eltype));
		    }
		  size = size_binop (MULT_अभिव्यक्ती, size, l);
		  जर (condition)
		    size = fold_build3 (COND_अभिव्यक्ती, sizetype, condition,
					size, size_zero_गाठ);
		}
	      अन्यथा
		size = size_binop (MULT_अभिव्यक्ती, size, l);
	    }
	}
      जर (side_effects)
	size = build2 (COMPOUND_अभिव्यक्ती, sizetype, side_effects, size);
      जर (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
	  || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
	  || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TASK_REDUCTION)
	{
	  size = size_binop (MINUS_अभिव्यक्ती, size, size_one_गाठ);
	  size = c_fully_fold (size, असत्य, रिक्त);
	  size = save_अभिव्यक्ती (size);
	  वृक्ष index_type = build_index_type (size);
	  वृक्ष eltype = वृक्ष_TYPE (first);
	  पर्यंत (वृक्ष_CODE (eltype) == ARRAY_TYPE)
	    eltype = वृक्ष_TYPE (eltype);
	  वृक्ष type = c_build_array_type (eltype, index_type);
	  वृक्ष ptype = c_build_pointer_type (eltype);
	  जर (वृक्ष_CODE (वृक्ष_TYPE (t)) == ARRAY_TYPE)
	    t = build_fold_addr_अभिव्यक्ती (t);
	  वृक्ष t2 = build_fold_addr_अभिव्यक्ती (first);
	  t2 = fold_convert_loc (OMP_CLAUSE_LOCATION (c),
				 ptrdiff_type_गाठ, t2);
	  t2 = fold_build2_loc (OMP_CLAUSE_LOCATION (c), MINUS_अभिव्यक्ती,
				ptrdiff_type_गाठ, t2,
				fold_convert_loc (OMP_CLAUSE_LOCATION (c),
						  ptrdiff_type_गाठ, t));
	  t2 = c_fully_fold (t2, असत्य, रिक्त);
	  जर (वृक्ष_fits_shwi_p (t2))
	    t = build2 (MEM_REF, type, t,
			build_int_cst (ptype, वृक्ष_to_shwi (t2)));
	  अन्यथा
	    {
	      t2 = fold_convert_loc (OMP_CLAUSE_LOCATION (c), sizetype, t2);
	      t = build2_loc (OMP_CLAUSE_LOCATION (c), POINTER_PLUS_अभिव्यक्ती,
			      वृक्ष_TYPE (t), t, t2);
	      t = build2 (MEM_REF, type, t, build_int_cst (ptype, 0));
	    }
	  OMP_CLAUSE_DECL (c) = t;
	  परत असत्य;
	}
      first = c_fully_fold (first, असत्य, रिक्त);
      OMP_CLAUSE_DECL (c) = first;
      जर (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_HAS_DEVICE_ADDR)
	परत असत्य;
      /* Don't set OMP_CLAUSE_SIZE for bare attach/detach clauses.  */
      जर (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP
	  || (OMP_CLAUSE_MAP_KIND (c) != GOMP_MAP_ATTACH
	      && OMP_CLAUSE_MAP_KIND (c) != GOMP_MAP_DETACH
	      && OMP_CLAUSE_MAP_KIND (c) != GOMP_MAP_FORCE_DETACH))
	{
	  जर (size)
	    size = c_fully_fold (size, असत्य, रिक्त);
	  OMP_CLAUSE_SIZE (c) = size;
	}

      जर (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP)
	परत असत्य;

      auto_vec<omp_addr_token *, 10> addr_tokens;

      जर (!omp_parse_अभिव्यक्ती (addr_tokens, first))
	परत सत्य;

      c_omp_address_inspector ai (OMP_CLAUSE_LOCATION (c), t);

      वृक्ष nc = ai.expand_map_clause (c, first, addr_tokens, ort);
      जर (nc != error_mark_गाठ)
	{
	  using नामाकाश omp_addr_tokenizer;

	  जर (ai.maybe_zero_length_array_section (c))
	    OMP_CLAUSE_MAP_MAYBE_ZERO_LENGTH_ARRAY_SECTION (c) = 1;

	  /* !!! If we're accessing a base decl via chained access
	     methods (e.g. multiple indirections), duplicate clause
	     detection won't work properly.  Skip it in that case.  */
	  जर ((addr_tokens[0]->type == STRUCTURE_BASE
	       || addr_tokens[0]->type == ARRAY_BASE)
	      && addr_tokens[0]->u.structure_base_kind == BASE_DECL
	      && addr_tokens[1]->type == ACCESS_METHOD
	      && omp_access_chain_p (addr_tokens, 1))
	    c = nc;

	  परत असत्य;
	}
    }
  परत असत्य;
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
  स_रखो (&id, 0, आकार (id));
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
  परत stmt;
}

/* Helper function of c_finish_omp_clauses, called via walk_tree.
   Find OMP_CLAUSE_PLACEHOLDER (passed in DATA) in *TP.  */

स्थिर वृक्ष
c_find_omp_placeholder_r (वृक्ष *tp, पूर्णांक *, शून्य *data)
{
  जर (*tp == (वृक्ष) data)
    परत *tp;
  परत NULL_वृक्ष;
}

/* Similarly, but also walk aggregate fields.  */

संरचना c_find_omp_var_s { वृक्ष var; hash_set<वृक्ष> *pset; };

स्थिर वृक्ष
c_find_omp_var_r (वृक्ष *tp, पूर्णांक *, शून्य *data)
{
  जर (*tp == ((संरचना c_find_omp_var_s *) data)->var)
    परत *tp;
  जर (RECORD_OR_UNION_TYPE_P (*tp))
    {
      वृक्ष field;
      hash_set<वृक्ष> *pset = ((संरचना c_find_omp_var_s *) data)->pset;

      साठी (field = TYPE_FIELDS (*tp); field;
	   field = DECL_CHAIN (field))
	जर (वृक्ष_CODE (field) == FIELD_DECL)
	  {
	    वृक्ष ret = walk_वृक्ष (&DECL_FIELD_OFFSET (field),
				  c_find_omp_var_r, data, pset);
	    जर (ret)
	      परत ret;
	    ret = walk_वृक्ष (&DECL_SIZE (field), c_find_omp_var_r, data, pset);
	    जर (ret)
	      परत ret;
	    ret = walk_वृक्ष (&DECL_SIZE_UNIT (field), c_find_omp_var_r, data,
			     pset);
	    जर (ret)
	      परत ret;
	    ret = walk_वृक्ष (&वृक्ष_TYPE (field), c_find_omp_var_r, data, pset);
	    जर (ret)
	      परत ret;
	  }
    }
  अन्यथा जर (INTEGRAL_TYPE_P (*tp))
    परत walk_वृक्ष (&TYPE_MAX_मूल्य (*tp), c_find_omp_var_r, data,
		      ((संरचना c_find_omp_var_s *) data)->pset);
  परत NULL_वृक्ष;
}

/* Finish OpenMP iterators ITER.  Return true if they are erroneous
   and clauses containing them should be removed.  */

स्थिर तार्किक
c_omp_finish_iterators (वृक्ष iter)
{
  तार्किक ret = असत्य;
  साठी (वृक्ष it = iter; it; it = वृक्ष_CHAIN (it))
    {
      वृक्ष var = OMP_ITERATOR_VAR (it);
      वृक्ष begin = OMP_ITERATOR_BEGIN (it);
      वृक्ष end = OMP_ITERATOR_END (it);
      वृक्ष step = OMP_ITERATOR_STEP (it);
      वृक्ष orig_step;
      वृक्ष type = वृक्ष_TYPE (var);
      location_t loc = DECL_SOURCE_LOCATION (var);
      जर (type == error_mark_गाठ)
	{
	  ret = सत्य;
	  सुरूठेवा;
	}
      जर (!INTEGRAL_TYPE_P (type) && !POINTER_TYPE_P (type))
	{
	  error_at (loc, "iterator %qD has neither integral nor pointer type",
		    var);
	  ret = सत्य;
	  सुरूठेवा;
	}
      अन्यथा जर (TYPE_ATOMIC (type))
	{
	  error_at (loc, "iterator %qD has %<_Atomic%> qualified type", var);
	  ret = सत्य;
	  सुरूठेवा;
	}
      अन्यथा जर (TYPE_READONLY (type))
	{
	  error_at (loc, "iterator %qD has const qualified type", var);
	  ret = सत्य;
	  सुरूठेवा;
	}
      अन्यथा जर (step == error_mark_गाठ
	       || वृक्ष_TYPE (step) == error_mark_गाठ)
	{
	  ret = सत्य;
	  सुरूठेवा;
	}
      अन्यथा जर (!INTEGRAL_TYPE_P (वृक्ष_TYPE (step)))
	{
	  error_at (अभिव्यक्ती_LOC_OR_LOC (step, loc),
		    "iterator step with non-integral type");
	  ret = सत्य;
	  सुरूठेवा;
	}
      begin = c_fully_fold (build_c_cast (loc, type, begin), असत्य, रिक्त);
      end = c_fully_fold (build_c_cast (loc, type, end), असत्य, रिक्त);
      orig_step = save_अभिव्यक्ती (c_fully_fold (step, असत्य, रिक्त));
      वृक्ष stype = POINTER_TYPE_P (type) ? sizetype : type;
      step = c_fully_fold (build_c_cast (loc, stype, orig_step), असत्य, रिक्त);
      जर (POINTER_TYPE_P (type))
	{
	  begin = save_अभिव्यक्ती (begin);
	  step = pointer_int_sum (loc, PLUS_अभिव्यक्ती, begin, step);
	  step = fold_build2_loc (loc, MINUS_अभिव्यक्ती, sizetype,
				  fold_convert (sizetype, step),
				  fold_convert (sizetype, begin));
	  step = fold_convert (ssizetype, step);
	}
      जर (integer_zerop (step))
	{
	  error_at (loc, "iterator %qD has zero step", var);
	  ret = सत्य;
	  सुरूठेवा;
	}

      जर (begin == error_mark_गाठ
	  || end == error_mark_गाठ
	  || step == error_mark_गाठ
	  || orig_step == error_mark_गाठ)
	{
	  ret = सत्य;
	  सुरूठेवा;
	}
      hash_set<वृक्ष> pset;
      वृक्ष it2;
      साठी (it2 = वृक्ष_CHAIN (it); it2; it2 = वृक्ष_CHAIN (it2))
	{
	  वृक्ष var2 = OMP_ITERATOR_VAR (it2);
	  वृक्ष begin2 = OMP_ITERATOR_BEGIN (it2);
	  वृक्ष end2 = OMP_ITERATOR_END (it2);
	  वृक्ष step2 = OMP_ITERATOR_STEP (it2);
	  वृक्ष type2 = वृक्ष_TYPE (var2);
	  location_t loc2 = DECL_SOURCE_LOCATION (var2);
	  संरचना c_find_omp_var_s data = { var, &pset };
	  जर (walk_वृक्ष (&type2, c_find_omp_var_r, &data, &pset))
	    {
	      error_at (loc2,
			"type of iterator %qD refers to outer iterator %qD",
			var2, var);
	      थांबा;
	    }
	  अन्यथा जर (walk_वृक्ष (&begin2, c_find_omp_var_r, &data, &pset))
	    {
	      error_at (अभिव्यक्ती_LOC_OR_LOC (begin2, loc2),
			"begin expression refers to outer iterator %qD", var);
	      थांबा;
	    }
	  अन्यथा जर (walk_वृक्ष (&end2, c_find_omp_var_r, &data, &pset))
	    {
	      error_at (अभिव्यक्ती_LOC_OR_LOC (end2, loc2),
			"end expression refers to outer iterator %qD", var);
	      थांबा;
	    }
	  अन्यथा जर (walk_वृक्ष (&step2, c_find_omp_var_r, &data, &pset))
	    {
	      error_at (अभिव्यक्ती_LOC_OR_LOC (step2, loc2),
			"step expression refers to outer iterator %qD", var);
	      थांबा;
	    }
	}
      जर (it2)
	{
	  ret = सत्य;
	  सुरूठेवा;
	}
      OMP_ITERATOR_BEGIN (it) = begin;
      OMP_ITERATOR_END (it) = end;
      OMP_ITERATOR_STEP (it) = step;
      OMP_ITERATOR_ORIG_STEP (it) = orig_step;
    }
  परत ret;
}

/* Ensure that pointers are used in OpenACC attach and detach clauses.
   Return true if an error has been detected.  */

स्थिर तार्किक
c_oacc_check_attachments (वृक्ष c)
{
  जर (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP)
    परत असत्य;

  /* OpenACC attach / detach clauses must be pointers.  */
  जर (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_ATTACH
      || OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_DETACH)
    {
      वृक्ष t = OMP_CLAUSE_DECL (c);

      पर्यंत (वृक्ष_CODE (t) == OMP_ARRAY_SECTION)
	t = वृक्ष_OPERAND (t, 0);

      जर (वृक्ष_CODE (वृक्ष_TYPE (t)) != POINTER_TYPE)
	{
	  error_at (OMP_CLAUSE_LOCATION (c), "expected pointer in %qs clause",
		    user_omp_clause_code_name (c, सत्य));
	  परत सत्य;
	}
    }

  परत असत्य;
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
  पूर्णांक reduction_seen = 0;
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

  जर (!openacc)
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

  जर (openacc)
    साठी (c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
      जर (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ASYNC)
	{
	  oacc_async = सत्य;
	  थांबा;
	}

  वृक्ष *grp_start_p = रिक्त, grp_sentinel = NULL_वृक्ष;

  साठी (pc = &clauses, c = clauses; c ; c = *pc)
    {
      तार्किक हटाओ = असत्य;
      तार्किक need_complete = असत्य;
      तार्किक need_implicitly_determined = असत्य;

      /* We've reached the end of a list of expanded nodes.  Reset the group
	 start pointer.  */
      जर (c == grp_sentinel)
	{
	  जर (grp_start_p
	      && OMP_CLAUSE_HAS_ITERATORS (*grp_start_p))
	    साठी (वृक्ष gc = *grp_start_p; gc != grp_sentinel;
		 gc = OMP_CLAUSE_CHAIN (gc))
	      OMP_CLAUSE_ITERATORS (gc) = OMP_CLAUSE_ITERATORS (*grp_start_p);
	  grp_start_p = रिक्त;
	}

      निवड (OMP_CLAUSE_CODE (c))
	{
	स्थिती OMP_CLAUSE_SHARED:
	  need_implicitly_determined = सत्य;
	  जा check_dup_generic;

	स्थिती OMP_CLAUSE_PRIVATE:
	  need_complete = सत्य;
	  need_implicitly_determined = सत्य;
	  जा check_dup_generic;

	स्थिती OMP_CLAUSE_REDUCTION:
	  जर (reduction_seen == 0)
	    reduction_seen = OMP_CLAUSE_REDUCTION_INSCAN (c) ? -1 : 1;
	  अन्यथा जर (reduction_seen != -2
		   && reduction_seen != (OMP_CLAUSE_REDUCTION_INSCAN (c)
					 ? -1 : 1))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<inscan%> and non-%<inscan%> %<reduction%> clauses "
			"on the same construct");
	      reduction_seen = -2;
	    }
	  /* FALLTHRU */
	स्थिती OMP_CLAUSE_IN_REDUCTION:
	स्थिती OMP_CLAUSE_TASK_REDUCTION:
	  need_implicitly_determined = सत्य;
	  t = OMP_CLAUSE_DECL (c);
	  जर (वृक्ष_CODE (t) == OMP_ARRAY_SECTION)
	    {
	      जर (handle_omp_array_sections (c, ort))
		{
		  हटाओ = सत्य;
		  थांबा;
		}

	      t = OMP_CLAUSE_DECL (c);
	      जर (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
		  && OMP_CLAUSE_REDUCTION_INSCAN (c))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<inscan%> %<reduction%> clause with array "
			    "section");
		  हटाओ = सत्य;
		  थांबा;
		}
	    }
	  t = require_complete_type (OMP_CLAUSE_LOCATION (c), t);
	  जर (t == error_mark_गाठ)
	    {
	      हटाओ = सत्य;
	      थांबा;
	    }
	  जर (oacc_async)
	    c_mark_addressable (t);
	  type = वृक्ष_TYPE (t);
	  जर (वृक्ष_CODE (t) == MEM_REF)
	    type = वृक्ष_TYPE (type);
	  जर (वृक्ष_CODE (type) == ARRAY_TYPE)
	    {
	      वृक्ष oatype = type;
	      gcc_assert (वृक्ष_CODE (t) != MEM_REF);
	      पर्यंत (वृक्ष_CODE (type) == ARRAY_TYPE)
		type = वृक्ष_TYPE (type);
	      जर (integer_zerop (TYPE_SIZE_UNIT (type)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD in %<reduction%> clause is a zero size array",
			    t);
		  हटाओ = सत्य;
		  थांबा;
		}
	      वृक्ष size = size_binop (EXACT_DIV_अभिव्यक्ती, TYPE_SIZE_UNIT (oatype),
				      TYPE_SIZE_UNIT (type));
	      जर (integer_zerop (size))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD in %<reduction%> clause is a zero size array",
			    t);
		  हटाओ = सत्य;
		  थांबा;
		}
	      size = size_binop (MINUS_अभिव्यक्ती, size, size_one_गाठ);
	      size = save_अभिव्यक्ती (size);
	      वृक्ष index_type = build_index_type (size);
	      वृक्ष atype = c_build_array_type (TYPE_MAIN_VARIANT (type),
					       index_type);
	      atype = c_build_qualified_type (atype, TYPE_QUALS (type));
	      वृक्ष ptype = c_build_pointer_type (type);
	      जर (वृक्ष_CODE (वृक्ष_TYPE (t)) == ARRAY_TYPE)
		t = build_fold_addr_अभिव्यक्ती (t);
	      t = build2 (MEM_REF, atype, t, build_int_cst (ptype, 0));
	      OMP_CLAUSE_DECL (c) = t;
	    }
	  जर (TYPE_ATOMIC (type))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<_Atomic%> %qE in %<reduction%> clause", t);
	      हटाओ = सत्य;
	      थांबा;
	    }
	  जर (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_REDUCTION
	      || OMP_CLAUSE_REDUCTION_TASK (c))
	    {
	      /* Disallow zero sized or potentially zero sized task
		 reductions.  */
	      जर (integer_zerop (TYPE_SIZE_UNIT (type)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "zero sized type %qT in %qs clause", type,
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  हटाओ = सत्य;
		  थांबा;
		}
	      अन्यथा जर (वृक्ष_CODE (TYPE_SIZE_UNIT (type)) != INTEGER_CST)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "variable sized type %qT in %qs clause", type,
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  हटाओ = सत्य;
		  थांबा;
		}
	    }
	  जर (OMP_CLAUSE_REDUCTION_PLACEHOLDER (c) == NULL_वृक्ष
	      && (FLOAT_TYPE_P (type)
		  || वृक्ष_CODE (type) == COMPLEX_TYPE))
	    {
	      गणना वृक्ष_code r_code = OMP_CLAUSE_REDUCTION_CODE (c);
	      स्थिरांक अक्षर *r_name = रिक्त;

	      निवड (r_code)
		{
		स्थिती PLUS_अभिव्यक्ती:
		स्थिती MULT_अभिव्यक्ती:
		स्थिती MINUS_अभिव्यक्ती:
		स्थिती TRUTH_ANDIF_अभिव्यक्ती:
		स्थिती TRUTH_ORIF_अभिव्यक्ती:
		  थांबा;
		स्थिती MIN_अभिव्यक्ती:
		  जर (वृक्ष_CODE (type) == COMPLEX_TYPE)
		    r_name = "min";
		  थांबा;
		स्थिती MAX_अभिव्यक्ती:
		  जर (वृक्ष_CODE (type) == COMPLEX_TYPE)
		    r_name = "max";
		  थांबा;
		स्थिती BIT_AND_अभिव्यक्ती:
		  r_name = "&";
		  थांबा;
		स्थिती BIT_XOR_अभिव्यक्ती:
		  r_name = "^";
		  थांबा;
		स्थिती BIT_IOR_अभिव्यक्ती:
		  r_name = "|";
		  थांबा;
		पूर्वनिर्धारित:
		  gcc_unreachable ();
		}
	      जर (r_name)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qE has invalid type for %<reduction(%s)%>",
			    t, r_name);
		  हटाओ = सत्य;
		  थांबा;
		}
	    }
	  अन्यथा जर (OMP_CLAUSE_REDUCTION_PLACEHOLDER (c) == error_mark_गाठ)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"user defined reduction not found for %qE", t);
	      हटाओ = सत्य;
	      थांबा;
	    }
	  अन्यथा जर (OMP_CLAUSE_REDUCTION_PLACEHOLDER (c))
	    {
	      वृक्ष list = OMP_CLAUSE_REDUCTION_PLACEHOLDER (c);
	      type = TYPE_MAIN_VARIANT (type);
	      वृक्ष placeholder = build_decl (OMP_CLAUSE_LOCATION (c),
					     VAR_DECL, NULL_वृक्ष, type);
	      वृक्ष decl_placeholder = NULL_वृक्ष;
	      OMP_CLAUSE_REDUCTION_PLACEHOLDER (c) = placeholder;
	      DECL_ARTIFICIAL (placeholder) = 1;
	      DECL_IGNORED_P (placeholder) = 1;
	      जर (वृक्ष_CODE (t) == MEM_REF)
		{
		  decl_placeholder = build_decl (OMP_CLAUSE_LOCATION (c),
						 VAR_DECL, NULL_वृक्ष, type);
		  OMP_CLAUSE_REDUCTION_DECL_PLACEHOLDER (c) = decl_placeholder;
		  DECL_ARTIFICIAL (decl_placeholder) = 1;
		  DECL_IGNORED_P (decl_placeholder) = 1;
		}
	      जर (वृक्ष_ADDRESSABLE (वृक्ष_VEC_ELT (list, 0)))
		c_mark_addressable (placeholder);
	      जर (वृक्ष_ADDRESSABLE (वृक्ष_VEC_ELT (list, 1)))
		c_mark_addressable (decl_placeholder ? decl_placeholder
				    : OMP_CLAUSE_DECL (c));
	      OMP_CLAUSE_REDUCTION_MERGE (c)
		= c_clone_omp_udr (वृक्ष_VEC_ELT (list, 2),
				   वृक्ष_VEC_ELT (list, 0),
				   वृक्ष_VEC_ELT (list, 1),
				   decl_placeholder ? decl_placeholder
				   : OMP_CLAUSE_DECL (c), placeholder);
	      OMP_CLAUSE_REDUCTION_MERGE (c)
		= build3_loc (OMP_CLAUSE_LOCATION (c), BIND_अभिव्यक्ती,
			      void_type_गाठ, NULL_वृक्ष,
			      OMP_CLAUSE_REDUCTION_MERGE (c), NULL_वृक्ष);
	      वृक्ष_SIDE_EFFECTS (OMP_CLAUSE_REDUCTION_MERGE (c)) = 1;
	      जर (वृक्ष_VEC_LENGTH (list) == 6)
		{
		  जर (वृक्ष_ADDRESSABLE (वृक्ष_VEC_ELT (list, 3)))
		    c_mark_addressable (decl_placeholder ? decl_placeholder
					: OMP_CLAUSE_DECL (c));
		  जर (वृक्ष_ADDRESSABLE (वृक्ष_VEC_ELT (list, 4)))
		    c_mark_addressable (placeholder);
		  वृक्ष init = वृक्ष_VEC_ELT (list, 5);
		  जर (init == error_mark_गाठ)
		    init = DECL_INITIAL (वृक्ष_VEC_ELT (list, 3));
		  OMP_CLAUSE_REDUCTION_INIT (c)
		    = c_clone_omp_udr (init, वृक्ष_VEC_ELT (list, 4),
				       वृक्ष_VEC_ELT (list, 3),
				       decl_placeholder ? decl_placeholder
				       : OMP_CLAUSE_DECL (c), placeholder);
		  जर (वृक्ष_VEC_ELT (list, 5) == error_mark_गाठ)
		    {
		      वृक्ष v = decl_placeholder ? decl_placeholder : t;
		      OMP_CLAUSE_REDUCTION_INIT (c)
			= build2 (INIT_अभिव्यक्ती, वृक्ष_TYPE (v), v,
				  OMP_CLAUSE_REDUCTION_INIT (c));
		    }
		  जर (walk_वृक्ष (&OMP_CLAUSE_REDUCTION_INIT (c),
				 c_find_omp_placeholder_r,
				 placeholder, रिक्त))
		    OMP_CLAUSE_REDUCTION_OMP_ORIG_REF (c) = 1;
		}
	      अन्यथा
		{
		  वृक्ष init;
		  वृक्ष v = decl_placeholder ? decl_placeholder : t;
		  जर (AGGREGATE_TYPE_P (वृक्ष_TYPE (v)))
		    init = build_constructor (वृक्ष_TYPE (v), रिक्त);
		  अन्यथा
		    init = fold_convert (वृक्ष_TYPE (v), integer_zero_गाठ);
		  OMP_CLAUSE_REDUCTION_INIT (c)
		    = build2 (INIT_अभिव्यक्ती, वृक्ष_TYPE (v), v, init);
		}
	      OMP_CLAUSE_REDUCTION_INIT (c)
		= build3_loc (OMP_CLAUSE_LOCATION (c), BIND_अभिव्यक्ती,
			      void_type_गाठ, NULL_वृक्ष,
			       OMP_CLAUSE_REDUCTION_INIT (c), NULL_वृक्ष);
	      वृक्ष_SIDE_EFFECTS (OMP_CLAUSE_REDUCTION_INIT (c)) = 1;
	    }
	  जर (वृक्ष_CODE (t) == MEM_REF)
	    {
	      जर (TYPE_SIZE_UNIT (वृक्ष_TYPE (वृक्ष_TYPE (t))) == NULL_वृक्ष
		  || वृक्ष_CODE (TYPE_SIZE_UNIT (वृक्ष_TYPE (वृक्ष_TYPE (t))))
		     != INTEGER_CST)
		{
		  sorry ("variable length element type in array "
			 "%<reduction%> clause");
		  हटाओ = सत्य;
		  थांबा;
		}
	      t = वृक्ष_OPERAND (t, 0);
	      जर (वृक्ष_CODE (t) == POINTER_PLUS_अभिव्यक्ती)
		t = वृक्ष_OPERAND (t, 0);
	      जर (वृक्ष_CODE (t) == ADDR_अभिव्यक्ती)
		t = वृक्ष_OPERAND (t, 0);
	    }
	  जा check_dup_generic_t;

	स्थिती OMP_CLAUSE_COPYPRIVATE:
	  copyprivate_seen = सत्य;
	  जर (nowait_clause)
	    {
	      error_at (OMP_CLAUSE_LOCATION (*nowait_clause),
			"%<nowait%> clause must not be used together "
			"with %<copyprivate%> clause");
	      *nowait_clause = OMP_CLAUSE_CHAIN (*nowait_clause);
	      nowait_clause = रिक्त;
	    }
	  जा check_dup_generic;

	स्थिती OMP_CLAUSE_COPYIN:
	  t = OMP_CLAUSE_DECL (c);
	  जर (!VAR_P (t) || !DECL_THREAD_LOCAL_P (t))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE must be %<threadprivate%> for %<copyin%>", t);
	      हटाओ = सत्य;
	      थांबा;
	    }
	  जा check_dup_generic;

	स्थिती OMP_CLAUSE_LINEAR:
	  जर (ort != C_ORT_OMP_DECLARE_SIMD)
	    need_implicitly_determined = सत्य;
	  t = OMP_CLAUSE_DECL (c);
	  जर (ort != C_ORT_OMP_DECLARE_SIMD
	      && OMP_CLAUSE_LINEAR_KIND (c) != OMP_CLAUSE_LINEAR_DEFAULT
	      && OMP_CLAUSE_LINEAR_OLD_LINEAR_MODIFIER (c))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"modifier should not be specified in %<linear%> "
			"clause on %<simd%> or %<for%> constructs when not "
			"using OpenMP 5.2 modifiers");
	      OMP_CLAUSE_LINEAR_KIND (c) = OMP_CLAUSE_LINEAR_DEFAULT;
	    }
	  जर (!INTEGRAL_TYPE_P (वृक्ष_TYPE (t))
	      && वृक्ष_CODE (वृक्ष_TYPE (t)) != POINTER_TYPE)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"linear clause applied to non-integral non-pointer "
			"variable with type %qT", वृक्ष_TYPE (t));
	      हटाओ = सत्य;
	      थांबा;
	    }
	  जर (TYPE_ATOMIC (वृक्ष_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<_Atomic%> %qD in %<linear%> clause", t);
	      हटाओ = सत्य;
	      थांबा;
	    }
	  जर (ort == C_ORT_OMP_DECLARE_SIMD)
	    {
	      वृक्ष s = OMP_CLAUSE_LINEAR_STEP (c);
	      जर (वृक्ष_CODE (s) == PARM_DECL)
		{
		  OMP_CLAUSE_LINEAR_VARIABLE_STRIDE (c) = 1;
		  /* map_head bitmap is used as uniform_head if
		     declare_simd.  */
		  जर (!bitmap_bit_p (&map_head, DECL_UID (s)))
		    linear_variable_step_check = सत्य;
		  जा check_dup_generic;
		}
	      जर (वृक्ष_CODE (s) != INTEGER_CST)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<linear%> clause step %qE is neither constant "
			    "nor a parameter", s);
		  हटाओ = सत्य;
		  थांबा;
		}
	    }
	  जर (वृक्ष_CODE (वृक्ष_TYPE (OMP_CLAUSE_DECL (c))) == POINTER_TYPE)
	    {
	      वृक्ष s = OMP_CLAUSE_LINEAR_STEP (c);
	      s = pointer_int_sum (OMP_CLAUSE_LOCATION (c), PLUS_अभिव्यक्ती,
				   OMP_CLAUSE_DECL (c), s);
	      s = fold_build2_loc (OMP_CLAUSE_LOCATION (c), MINUS_अभिव्यक्ती,
				   sizetype, fold_convert (sizetype, s),
				   fold_convert
				     (sizetype, OMP_CLAUSE_DECL (c)));
	      जर (s == error_mark_गाठ)
		s = size_one_गाठ;
	      OMP_CLAUSE_LINEAR_STEP (c) = s;
	    }
	  अन्यथा
	    OMP_CLAUSE_LINEAR_STEP (c)
	      = fold_convert (वृक्ष_TYPE (t), OMP_CLAUSE_LINEAR_STEP (c));
	  जा check_dup_generic;

	check_dup_generic:
	  t = OMP_CLAUSE_DECL (c);
	check_dup_generic_t:
	  जर (!VAR_P (t) && वृक्ष_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %qs", t,
			omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	      हटाओ = सत्य;
	    }
	  अन्यथा जर ((openacc && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION)
		   || (ort == C_ORT_OMP
		       && (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_USE_DEVICE_PTR
			   || (OMP_CLAUSE_CODE (c)
			       == OMP_CLAUSE_USE_DEVICE_ADDR)))
		   || (ort == C_ORT_OMP_TARGET
		       && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION))
	    {
	      जर (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
		  && (bitmap_bit_p (&generic_head, DECL_UID (t))
		      || bitmap_bit_p (&firstprivate_head, DECL_UID (t))))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in data-sharing "
			    "clauses", t);
		  हटाओ = सत्य;
		  थांबा;
		}
	      जर (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION)
		target_in_reduction_seen = सत्य;
	      जर (bitmap_bit_p (&oacc_reduction_head, DECL_UID (t)))
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
	  अन्यथा जर (bitmap_bit_p (&generic_head, DECL_UID (t))
		   || bitmap_bit_p (&firstprivate_head, DECL_UID (t))
		   || bitmap_bit_p (&lastprivate_head, DECL_UID (t))
		   || bitmap_bit_p (&map_firstprivate_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in data clauses", t);
	      हटाओ = सत्य;
	    }
	  अन्यथा जर ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_PRIVATE
		    || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_HAS_DEVICE_ADDR
		    || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IS_DEVICE_PTR)
		   && bitmap_bit_p (&map_head, DECL_UID (t)))
	    {
	      जर (openacc)
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears more than once in data clauses", t);
	      अन्यथा
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears both in data and map clauses", t);
	      हटाओ = सत्य;
	    }
	  अन्यथा
	    bitmap_set_bit (&generic_head, DECL_UID (t));
	  थांबा;

	स्थिती OMP_CLAUSE_FIRSTPRIVATE:
	  जर (OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (c) && !implicit_moved)
	    {
	    move_implicit:
	      implicit_moved = सत्य;
	      /* Move firstprivate and map clauses with
		 OMP_CLAUSE_{FIRSTPRIVATE,MAP}_IMPLICIT set to the end of
		 clauses chain.  */
	      वृक्ष cl1 = NULL_वृक्ष, cl2 = NULL_वृक्ष;
	      वृक्ष *pc1 = pc, *pc2 = &cl1, *pc3 = &cl2;
	      पर्यंत (*pc1)
		जर (OMP_CLAUSE_CODE (*pc1) == OMP_CLAUSE_FIRSTPRIVATE
		    && OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (*pc1))
		  {
		    *pc3 = *pc1;
		    pc3 = &OMP_CLAUSE_CHAIN (*pc3);
		    *pc1 = OMP_CLAUSE_CHAIN (*pc1);
		  }
		अन्यथा जर (OMP_CLAUSE_CODE (*pc1) == OMP_CLAUSE_MAP
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
	      सुरूठेवा;
	    }
	  t = OMP_CLAUSE_DECL (c);
	  need_complete = सत्य;
	  need_implicitly_determined = सत्य;
	  जर (!VAR_P (t) && वृक्ष_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %<firstprivate%>", t);
	      हटाओ = सत्य;
	    }
	  अन्यथा जर (OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (c)
		   && !OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT_TARGET (c)
		   && bitmap_bit_p (&map_firstprivate_head, DECL_UID (t)))
	    हटाओ = सत्य;
	  अन्यथा जर (bitmap_bit_p (&generic_head, DECL_UID (t))
		   || bitmap_bit_p (&firstprivate_head, DECL_UID (t))
		   || bitmap_bit_p (&map_firstprivate_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in data clauses", t);
	      हटाओ = सत्य;
	    }
	  अन्यथा जर (bitmap_bit_p (&map_head, DECL_UID (t))
		   || bitmap_bit_p (&map_field_head, DECL_UID (t)))
	    {
	      जर (openacc)
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears more than once in data clauses", t);
	      अन्यथा जर (OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (c)
		       && !OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT_TARGET (c))
		/* Silently drop the clause.  */;
	      अन्यथा
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears both in data and map clauses", t);
	      हटाओ = सत्य;
	    }
	  अन्यथा
	    bitmap_set_bit (&firstprivate_head, DECL_UID (t));
	  थांबा;

	स्थिती OMP_CLAUSE_LASTPRIVATE:
	  t = OMP_CLAUSE_DECL (c);
	  need_complete = सत्य;
	  need_implicitly_determined = सत्य;
	  जर (!VAR_P (t) && वृक्ष_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %<lastprivate%>", t);
	      हटाओ = सत्य;
	    }
	  अन्यथा जर (bitmap_bit_p (&generic_head, DECL_UID (t))
		   || bitmap_bit_p (&lastprivate_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
		     "%qE appears more than once in data clauses", t);
	      हटाओ = सत्य;
	    }
	  अन्यथा
	    bitmap_set_bit (&lastprivate_head, DECL_UID (t));
	  थांबा;

	स्थिती OMP_CLAUSE_ALIGNED:
	  t = OMP_CLAUSE_DECL (c);
	  जर (!VAR_P (t) && वृक्ष_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in %<aligned%> clause", t);
	      हटाओ = सत्य;
	    }
	  अन्यथा जर (!POINTER_TYPE_P (वृक्ष_TYPE (t))
		   && वृक्ष_CODE (वृक्ष_TYPE (t)) != ARRAY_TYPE)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE in %<aligned%> clause is neither a pointer nor "
			"an array", t);
	      हटाओ = सत्य;
	    }
	  अन्यथा जर (TYPE_ATOMIC (वृक्ष_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<_Atomic%> %qD in %<aligned%> clause", t);
	      हटाओ = सत्य;
	      थांबा;
	    }
	  अन्यथा जर (bitmap_bit_p (&aligned_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in %<aligned%> clauses",
			t);
	      हटाओ = सत्य;
	    }
	  अन्यथा
	    bitmap_set_bit (&aligned_head, DECL_UID (t));
	  थांबा;

	स्थिती OMP_CLAUSE_NONTEMPORAL:
	  t = OMP_CLAUSE_DECL (c);
	  जर (!VAR_P (t) && वृक्ष_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in %<nontemporal%> clause", t);
	      हटाओ = सत्य;
	    }
	  अन्यथा जर (bitmap_bit_p (&oacc_reduction_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in %<nontemporal%> "
			"clauses", t);
	      हटाओ = सत्य;
	    }
	  अन्यथा
	    bitmap_set_bit (&oacc_reduction_head, DECL_UID (t));
	  थांबा;

	स्थिती OMP_CLAUSE_ALLOCATE:
	  t = OMP_CLAUSE_DECL (c);
	  जर (!VAR_P (t) && वृक्ष_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in %<allocate%> clause", t);
	      हटाओ = सत्य;
	    }
	  अन्यथा जर (bitmap_bit_p (&aligned_head, DECL_UID (t)))
	    {
	      warning_at (OMP_CLAUSE_LOCATION (c), OPT_Wopenmp,
			  "%qE appears more than once in %<allocate%> clauses",
			  t);
	      हटाओ = सत्य;
	    }
	  अन्यथा
	    {
	      bitmap_set_bit (&aligned_head, DECL_UID (t));
	      जर (!OMP_CLAUSE_ALLOCATE_COMBINED (c))
		allocate_seen = सत्य;
	    }
	  थांबा;

	स्थिती OMP_CLAUSE_DOACROSS:
	  t = OMP_CLAUSE_DECL (c);
	  जर (t == NULL_वृक्ष)
	    थांबा;
	  जर (OMP_CLAUSE_DOACROSS_KIND (c) == OMP_CLAUSE_DOACROSS_SINK)
	    {
	      gcc_assert (वृक्ष_CODE (t) == वृक्ष_LIST);
	      साठी (; t; t = वृक्ष_CHAIN (t))
		{
		  वृक्ष decl = वृक्ष_मूल्य (t);
		  जर (वृक्ष_CODE (वृक्ष_TYPE (decl)) == POINTER_TYPE)
		    {
		      वृक्ष offset = वृक्ष_PURPOSE (t);
		      तार्किक neg = wi::neg_p (wi::to_wide (offset));
		      offset = fold_unary (ABS_अभिव्यक्ती, वृक्ष_TYPE (offset), offset);
		      वृक्ष t2 = pointer_int_sum (OMP_CLAUSE_LOCATION (c),
						 neg ? MINUS_अभिव्यक्ती : PLUS_अभिव्यक्ती,
						 decl, offset);
		      t2 = fold_build2_loc (OMP_CLAUSE_LOCATION (c), MINUS_अभिव्यक्ती,
					    sizetype,
					    fold_convert (sizetype, t2),
					    fold_convert (sizetype, decl));
		      जर (t2 == error_mark_गाठ)
			{
			  हटाओ = सत्य;
			  थांबा;
			}
		      वृक्ष_PURPOSE (t) = t2;
		    }
		}
	      थांबा;
	    }
	  gcc_unreachable ();

	स्थिती OMP_CLAUSE_USES_ALLOCATORS:
	  t = OMP_CLAUSE_USES_ALLOCATORS_ALLOCATOR (c);
	  जर (t == error_mark_गाठ)
	    {
	      हटाओ = सत्य;
	      थांबा;
	    }
	  जर ((VAR_P (t) || वृक्ष_CODE (t) == PARM_DECL)
	      && (bitmap_bit_p (&generic_head, DECL_UID (t))
		  || bitmap_bit_p (&map_head, DECL_UID (t))
		  || bitmap_bit_p (&firstprivate_head, DECL_UID (t))
		  || bitmap_bit_p (&lastprivate_head, DECL_UID (t))))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in data clauses", t);
	      हटाओ = सत्य;
	      थांबा;
	    }
	  अन्यथा
	    bitmap_set_bit (&generic_head, DECL_UID (t));
	  जर (वृक्ष_CODE (वृक्ष_TYPE (t)) != ENUMERAL_TYPE
	      || म_भेद (IDENTIFIER_POINTER (TYPE_IDENTIFIER (वृक्ष_TYPE (t))),
			 "omp_allocator_handle_t") != 0)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"allocator %qE must be of %<omp_allocator_handle_t%> "
			"type", t);
	      हटाओ = सत्य;
	      थांबा;
	    }
	  वृक्ष init;
	  जर (!DECL_P (t)
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
	      थांबा;
	    }
	  अन्यथा जर (वृक्ष_CODE (t) == CONST_DECL)
	    {
	      /* omp_null_allocator is ignored and for predefined allocators,
		 no special handling is required; thus, mark them removed. */
	      हटाओ = सत्य;

	      जर (OMP_CLAUSE_USES_ALLOCATORS_MEMSPACE (c)
		  || OMP_CLAUSE_USES_ALLOCATORS_TRAITS (c))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "modifiers cannot be used with predefined "
			    "allocator %qE", t);
		  थांबा;
		}
	    }
	  t = OMP_CLAUSE_USES_ALLOCATORS_MEMSPACE (c);
	  जर (t == error_mark_गाठ)
	    {
	      हटाओ = सत्य;
	      थांबा;
	    }
	  जर (t != NULL_वृक्ष
	      && ((वृक्ष_CODE (t) != CONST_DECL && वृक्ष_CODE (t) != INTEGER_CST)
		  || वृक्ष_CODE (वृक्ष_TYPE (t)) != ENUMERAL_TYPE
		  || म_भेद (IDENTIFIER_POINTER (TYPE_IDENTIFIER (वृक्ष_TYPE (t))),
			     "omp_memspace_handle_t") != 0))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c), "memspace modifier %qE must be"
			" constant enum of %<omp_memspace_handle_t%> type", t);
	      हटाओ = सत्य;
	      थांबा;
	    }
	  t = OMP_CLAUSE_USES_ALLOCATORS_TRAITS (c);
	  जर (t == error_mark_गाठ)
	    {
	      हटाओ = सत्य;
	      थांबा;
	    }
	  जर (t != NULL_वृक्ष
	      && t != error_mark_गाठ
	      && (DECL_EXTERNAL (t)
		  || वृक्ष_CODE (t) == PARM_DECL))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c), "traits array %qE must be "
			"defined in same scope as the construct on which the "
			"clause appears", t);
	      हटाओ = सत्य;
	    }
	  जर (t != NULL_वृक्ष)
	    {
	      तार्किक type_err = असत्य;

	      जर (वृक्ष_CODE (वृक्ष_TYPE (t)) != ARRAY_TYPE
		  || DECL_SIZE (t) == NULL_वृक्ष
		  || !COMPLETE_TYPE_P (वृक्ष_TYPE (t)))
		type_err = सत्य;
	      अन्यथा
		{
		  वृक्ष elem_t = वृक्ष_TYPE (वृक्ष_TYPE (t));
		  जर (वृक्ष_CODE (elem_t) != RECORD_TYPE
		      || म_भेद (IDENTIFIER_POINTER (TYPE_IDENTIFIER (elem_t)),
				 "omp_alloctrait_t") != 0
		      || !TYPE_READONLY (elem_t))
		    type_err = सत्य;
		}
	      जर (type_err)
		{
		  जर (t != error_mark_गाठ)
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
		  जर (cst_val == t)
		    {
		      error_at (OMP_CLAUSE_LOCATION (c), "traits array must be "
				"initialized with constants");

		      हटाओ = सत्य;
		    }
		}
	    }
	  जर (हटाओ)
	    थांबा;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  सुरूठेवा;
	स्थिती OMP_CLAUSE_DEPEND:
	  depend_clause = c;
	  /* FALLTHRU */
	स्थिती OMP_CLAUSE_AFFINITY:
	  t = OMP_CLAUSE_DECL (c);
	  जर (OMP_ITERATOR_DECL_P (t))
	    {
	      जर (वृक्ष_PURPOSE (t) != last_iterators)
		last_iterators_remove
		  = c_omp_finish_iterators (वृक्ष_PURPOSE (t));
	      last_iterators = वृक्ष_PURPOSE (t);
	      t = वृक्ष_मूल्य (t);
	      जर (last_iterators_remove)
		t = error_mark_गाठ;
	    }
	  अन्यथा
	    last_iterators = NULL_वृक्ष;
	  जर (वृक्ष_CODE (t) == OMP_ARRAY_SECTION)
	    {
	      जर (handle_omp_array_sections (c, ort))
		हटाओ = सत्य;
	      अन्यथा जर (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
		       && OMP_CLAUSE_DEPEND_KIND (c) == OMP_CLAUSE_DEPEND_DEPOBJ)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<depend%> clause with %<depobj%> dependence "
			    "type on array section");
		  हटाओ = सत्य;
		}
	      थांबा;
	    }
	  जर (t == error_mark_गाठ)
	    हटाओ = सत्य;
	  अन्यथा जर (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
		   && t == ridpointers[RID_OMP_ALL_MEMORY])
	    {
	      जर (OMP_CLAUSE_DEPEND_KIND (c) != OMP_CLAUSE_DEPEND_OUT
		  && OMP_CLAUSE_DEPEND_KIND (c) != OMP_CLAUSE_DEPEND_INOUT)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<omp_all_memory%> used with %<depend%> kind "
			    "other than %<out%> or %<inout%>");
		  हटाओ = सत्य;
		}
	    }
	  अन्यथा जर (!lvalue_p (t))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not lvalue expression nor array section in "
			"%qs clause", t,
			omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	      हटाओ = सत्य;
	    }
	  अन्यथा जर (वृक्ष_CODE (t) == COMPONENT_REF
		   && DECL_C_BIT_FIELD (वृक्ष_OPERAND (t, 1)))
	    {
	      gcc_assert (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
			  || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY);
	      error_at (OMP_CLAUSE_LOCATION (c),
			"bit-field %qE in %qs clause", t,
			omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	      हटाओ = सत्य;
	    }
	  अन्यथा जर (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
		   && OMP_CLAUSE_DEPEND_KIND (c) == OMP_CLAUSE_DEPEND_DEPOBJ)
	    {
	      जर (!c_omp_depend_t_p (वृक्ष_TYPE (t)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qE does not have %<omp_depend_t%> type in "
			    "%<depend%> clause with %<depobj%> dependence "
			    "type", t);
		  हटाओ = सत्य;
		}
	    }
	  अन्यथा जर (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
		   && c_omp_depend_t_p (वृक्ष_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE should not have %<omp_depend_t%> type in "
			"%<depend%> clause with dependence type other than "
			"%<depobj%>", t);
	      हटाओ = सत्य;
	    }
	  जर (!हटाओ)
	    {
	      जर (t == ridpointers[RID_OMP_ALL_MEMORY])
		t = null_pointer_गाठ;
	      अन्यथा
		{
		  वृक्ष addr = build_unary_op (OMP_CLAUSE_LOCATION (c),
					      ADDR_अभिव्यक्ती, t, असत्य);
		  जर (addr == error_mark_गाठ)
		    {
		      हटाओ = सत्य;
		      थांबा;
		    }
		  t = build_indirect_ref (OMP_CLAUSE_LOCATION (c), addr,
					  RO_UNARY_STAR);
		  जर (t == error_mark_गाठ)
		    {
		      हटाओ = सत्य;
		      थांबा;
		    }
		}
	      जर (OMP_ITERATOR_DECL_P (OMP_CLAUSE_DECL (c)))
		वृक्ष_मूल्य (OMP_CLAUSE_DECL (c)) = t;
	      अन्यथा
		OMP_CLAUSE_DECL (c) = t;
	    }
	  थांबा;

	स्थिती OMP_CLAUSE_MAP:
	  जर (OMP_CLAUSE_MAP_IMPLICIT (c) && !implicit_moved)
	    जा move_implicit;
	  जर (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_ढकला_MAPPER_NAME
	      || OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_काढा_MAPPER_NAME)
	    {
	      हटाओ = सत्य;
	      थांबा;
	    }
	  /* FALLTHRU */
	स्थिती OMP_CLAUSE_TO:
	स्थिती OMP_CLAUSE_FROM:
	  जर (OMP_CLAUSE_ITERATORS (c)
	      && c_omp_finish_iterators (OMP_CLAUSE_ITERATORS (c)))
	    {
	      t = error_mark_गाठ;
	      थांबा;
	    }
	  /* FALLTHRU */
	स्थिती OMP_CLAUSE__CACHE_:
	  {
	    using नामाकाश omp_addr_tokenizer;
	    auto_vec<omp_addr_token *, 10> addr_tokens;

	    t = OMP_CLAUSE_DECL (c);
	    जर (वृक्ष_CODE (t) == OMP_ARRAY_SECTION)
	      {
		grp_start_p = pc;
		grp_sentinel = OMP_CLAUSE_CHAIN (c);

		जर (handle_omp_array_sections (c, ort))
		  हटाओ = सत्य;
		अन्यथा
		  {
		    t = OMP_CLAUSE_DECL (c);
		    जर (!omp_mappable_type (वृक्ष_TYPE (t)))
		      {
			error_at (OMP_CLAUSE_LOCATION (c),
				  "array section does not have mappable type "
				  "in %qs clause",
				  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
			हटाओ = सत्य;
		      }
		    अन्यथा जर (TYPE_ATOMIC (वृक्ष_TYPE (t)))
		      {
			error_at (OMP_CLAUSE_LOCATION (c),
				  "%<_Atomic%> %qE in %qs clause", t,
				  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
			हटाओ = सत्य;
		      }
		    पर्यंत (वृक्ष_CODE (t) == ARRAY_REF)
		      t = वृक्ष_OPERAND (t, 0);

		    c_omp_address_inspector ai (OMP_CLAUSE_LOCATION (c), t);

		    जर (!omp_parse_अभिव्यक्ती (addr_tokens, t))
		      {
			sorry_at (OMP_CLAUSE_LOCATION (c),
				  "unsupported map expression %qE",
				  OMP_CLAUSE_DECL (c));
			हटाओ = सत्य;
			थांबा;
		      }

		    /* This check is to determine if this will be the only map
		       node created for this clause.  Otherwise, we'll check
		       the following FIRSTPRIVATE_POINTER or ATTACH_DETACH
		       node on the next iteration(s) of the loop.   */
		    जर (addr_tokens.length () >= 4
			&& addr_tokens[0]->type == STRUCTURE_BASE
			&& addr_tokens[0]->u.structure_base_kind == BASE_DECL
			&& addr_tokens[1]->type == ACCESS_METHOD
			&& addr_tokens[2]->type == COMPONENT_SELECTOR
			&& addr_tokens[3]->type == ACCESS_METHOD
			&& (addr_tokens[3]->u.access_kind == ACCESS_DIRECT
			    || (addr_tokens[3]->u.access_kind
				== ACCESS_INDEXED_ARRAY)))
		      {
			वृक्ष rt = addr_tokens[1]->अभिव्यक्ती;

			gcc_assert (DECL_P (rt));

			जर (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
			    && OMP_CLAUSE_MAP_IMPLICIT (c)
			    && (bitmap_bit_p (&map_head, DECL_UID (rt))
				|| bitmap_bit_p (&map_field_head, DECL_UID (rt))
				|| bitmap_bit_p (&map_firstprivate_head,
						 DECL_UID (rt))))
			  {
			    हटाओ = सत्य;
			    थांबा;
			  }
			जर (bitmap_bit_p (&map_field_head, DECL_UID (rt)))
			  थांबा;
			जर (bitmap_bit_p (&map_head, DECL_UID (rt)))
			  {
			    जर (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP)
			      error_at (OMP_CLAUSE_LOCATION (c),
					"%qD appears more than once in motion "
					"clauses", rt);
			    अन्यथा जर (openacc)
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
		जर (c_oacc_check_attachments (c))
		  हटाओ = सत्य;
		जर (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		    && (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_ATTACH
			|| OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_DETACH)
		    && !OMP_CLAUSE_SIZE (c))
		  /* In this case, we have a single array element which is a
		     pointer, and we already set OMP_CLAUSE_SIZE in
		     handle_omp_array_sections above.  For attach/detach
		     clauses, reset the OMP_CLAUSE_SIZE (representing a bias)
		     to zero here.  */
		  OMP_CLAUSE_SIZE (c) = size_zero_गाठ;
		थांबा;
	      }
	    अन्यथा जर (!omp_parse_अभिव्यक्ती (addr_tokens, t))
	      {
		sorry_at (OMP_CLAUSE_LOCATION (c),
			  "unsupported map expression %qE",
			  OMP_CLAUSE_DECL (c));
		हटाओ = सत्य;
		थांबा;
	      }
	    जर (t == error_mark_गाठ)
	      {
		हटाओ = सत्य;
		थांबा;
	      }

	    वृक्ष attr;
	    जर (DECL_P (t)
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
		थांबा;
	      }

	    /* OpenACC attach / detach clauses must be pointers.  */
	    जर (c_oacc_check_attachments (c))
	      {
		हटाओ = सत्य;
		थांबा;
	      }
	    जर (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		&& (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_ATTACH
		    || OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_DETACH)
		&& !OMP_CLAUSE_SIZE (c))
	      /* For attach/detach clauses, set OMP_CLAUSE_SIZE (representing a
		 bias) to zero here, so it is not set erroneously to the pointer
		 size later on in gimplify.cc.  */
	      OMP_CLAUSE_SIZE (c) = size_zero_गाठ;

	    c_omp_address_inspector ai (OMP_CLAUSE_LOCATION (c), t);

	    जर (!ai.check_clause (c))
	      {
		हटाओ = सत्य;
		थांबा;
	      }

	    जर (!ai.map_supported_p ())
	      {
		sorry_at (OMP_CLAUSE_LOCATION (c),
			  "unsupported map expression %qE",
			  OMP_CLAUSE_DECL (c));
		हटाओ = सत्य;
		थांबा;
	      }

	    gcc_assert ((addr_tokens[0]->type == ARRAY_BASE
			 || addr_tokens[0]->type == STRUCTURE_BASE)
			&& addr_tokens[1]->type == ACCESS_METHOD);

	    t = addr_tokens[1]->अभिव्यक्ती;

	    जर (addr_tokens[0]->u.structure_base_kind != BASE_DECL)
	      जा skip_decl_checks;

	    /* For OpenMP, we can access a struct "t" and "t.d" on the same
	       mapping.  OpenACC allows multiple fields of the same structure
	       to be written.  */
	    जर (addr_tokens[0]->type == STRUCTURE_BASE
		&& (bitmap_bit_p (&map_field_head, DECL_UID (t))
		    || (!openacc && bitmap_bit_p (&map_head, DECL_UID (t)))))
	      जा skip_decl_checks;

	    जर (!VAR_P (t) && वृक्ष_CODE (t) != PARM_DECL)
	      {
		जर (ort != C_ORT_ACC && अभिव्यक्ती_P (t))
		  थांबा;

		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is not a variable in %qs clause", t,
			  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		हटाओ = सत्य;
	      }
	    अन्यथा जर (VAR_P (t) && DECL_THREAD_LOCAL_P (t))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD is threadprivate variable in %qs clause", t,
			  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		हटाओ = सत्य;
	      }
	    अन्यथा जर ((OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP
		      || (OMP_CLAUSE_MAP_KIND (c)
			  != GOMP_MAP_FIRSTPRIVATE_POINTER))
		     && !c_mark_addressable (t))
	      हटाओ = सत्य;
	    अन्यथा जर (!(OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
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
	    अन्यथा जर (वृक्ष_TYPE (t) == error_mark_गाठ)
	      हटाओ = सत्य;
	    अन्यथा जर (TYPE_ATOMIC (strip_array_types (वृक्ष_TYPE (t))))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%<_Atomic%> %qE in %qs clause", t,
			  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		हटाओ = सत्य;
	      }
	    अन्यथा जर (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		     && OMP_CLAUSE_MAP_IMPLICIT (c)
		     && (bitmap_bit_p (&map_head, DECL_UID (t))
			 || bitmap_bit_p (&map_field_head, DECL_UID (t))
			 || bitmap_bit_p (&map_firstprivate_head,
					  DECL_UID (t))))
	      हटाओ = सत्य;
	    अन्यथा जर (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		     && (OMP_CLAUSE_MAP_KIND (c)
			 == GOMP_MAP_FIRSTPRIVATE_POINTER))
	      {
		जर (bitmap_bit_p (&generic_head, DECL_UID (t))
		    || bitmap_bit_p (&firstprivate_head, DECL_UID (t))
		    || bitmap_bit_p (&map_firstprivate_head, DECL_UID (t)))
		  {
		    error_at (OMP_CLAUSE_LOCATION (c),
			      "%qD appears more than once in data clauses", t);
		    हटाओ = सत्य;
		  }
		अन्यथा जर (bitmap_bit_p (&map_head, DECL_UID (t))
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
	    अन्यथा जर (bitmap_bit_p (&map_head, DECL_UID (t))
		     && !bitmap_bit_p (&map_field_head, DECL_UID (t))
		     && ort != C_ORT_OMP
		     && ort != C_ORT_OMP_TARGET
		     && ort != C_ORT_OMP_EXIT_DATA)
	      {
		जर (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP)
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in motion clauses", t);
		अन्यथा जर (openacc)
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in data clauses", t);
		अन्यथा
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in map clauses", t);
		हटाओ = सत्य;
	      }
	    अन्यथा जर (openacc && bitmap_bit_p (&generic_head, DECL_UID (t)))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears more than once in data clauses", t);
		हटाओ = सत्य;
	      }
	    अन्यथा जर (bitmap_bit_p (&firstprivate_head, DECL_UID (t))
		     || bitmap_bit_p (&is_on_device_head, DECL_UID (t)))
	      {
		जर (openacc)
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in data clauses", t);
		अन्यथा
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears both in data and map clauses", t);
		हटाओ = सत्य;
	      }
	    अन्यथा जर (!omp_access_chain_p (addr_tokens, 1))
	      {
		bitmap_set_bit (&map_head, DECL_UID (t));
		जर (t != OMP_CLAUSE_DECL (c)
		    && वृक्ष_CODE (OMP_CLAUSE_DECL (c)) == COMPONENT_REF)
		  bitmap_set_bit (&map_field_head, DECL_UID (t));
	      }

	  skip_decl_checks:
	    /* If we call omp_expand_map_clause in handle_omp_array_sections,
	       the containing loop (here) iterates through the new nodes
	       created by that expansion.  Avoid expanding those again (just
	       by checking the node type).  */
	    जर (!हटाओ
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
		जर (nc != error_mark_गाठ)
		  c = nc;
	      }
	  }
	  थांबा;

	स्थिती OMP_CLAUSE_ENTER:
	स्थिती OMP_CLAUSE_LINK:
	स्थिती OMP_CLAUSE_LOCAL:
	  t = OMP_CLAUSE_DECL (c);
	  स्थिरांक अक्षर *cname;
	  cname = omp_clause_code_name[OMP_CLAUSE_CODE (c)];
	  जर (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ENTER
	      && OMP_CLAUSE_ENTER_TO (c))
	    cname = "to";
	  जर (वृक्ष_CODE (t) == FUNCTION_DECL
	      && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ENTER)
	    ;
	  अन्यथा जर (!VAR_P (t))
	    {
	      जर (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ENTER)
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is neither a variable nor a function name in "
			  "clause %qs", t, cname);
	      अन्यथा
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is not a variable in clause %qs", t, cname);
	      हटाओ = सत्य;
	    }
	  अन्यथा जर (DECL_THREAD_LOCAL_P (t))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD is threadprivate variable in %qs clause", t,
			cname);
	      हटाओ = सत्य;
	    }
	  अन्यथा जर (!omp_mappable_type (वृक्ष_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD does not have a mappable type in %qs clause", t,
			cname);
	      हटाओ = सत्य;
	    }
	  जर (हटाओ)
	    थांबा;
	  जर (bitmap_bit_p (&generic_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once on the same "
			"%<declare target%> directive", t);
	      हटाओ = सत्य;
	    }
	  अन्यथा
	    bitmap_set_bit (&generic_head, DECL_UID (t));
	  थांबा;

	स्थिती OMP_CLAUSE_UNIFORM:
	  t = OMP_CLAUSE_DECL (c);
	  जर (वृक्ष_CODE (t) != PARM_DECL)
	    {
	      जर (DECL_P (t))
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD is not an argument in %<uniform%> clause", t);
	      अन्यथा
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is not an argument in %<uniform%> clause", t);
	      हटाओ = सत्य;
	      थांबा;
	    }
	  /* map_head bitmap is used as uniform_head if declare_simd.  */
	  bitmap_set_bit (&map_head, DECL_UID (t));
	  जा check_dup_generic;

	स्थिती OMP_CLAUSE_IS_DEVICE_PTR:
	स्थिती OMP_CLAUSE_USE_DEVICE_PTR:
	  t = OMP_CLAUSE_DECL (c);
	  जर (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IS_DEVICE_PTR)
	    bitmap_set_bit (&is_on_device_head, DECL_UID (t));
	  जर (वृक्ष_CODE (वृक्ष_TYPE (t)) != POINTER_TYPE)
	    {
	      जर (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_USE_DEVICE_PTR
		  && !openacc)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qs variable is not a pointer",
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  हटाओ = सत्य;
		}
	      अन्यथा जर (वृक्ष_CODE (वृक्ष_TYPE (t)) != ARRAY_TYPE)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qs variable is neither a pointer nor an array",
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  हटाओ = सत्य;
		}
	    }
	  जा check_dup_generic;

	स्थिती OMP_CLAUSE_HAS_DEVICE_ADDR:
	  t = OMP_CLAUSE_DECL (c);
	  जर (वृक्ष_CODE (t) == OMP_ARRAY_SECTION)
	    {
	      जर (handle_omp_array_sections (c, ort))
		हटाओ = सत्य;
	      अन्यथा
		{
		  t = OMP_CLAUSE_DECL (c);
		  पर्यंत (वृक्ष_CODE (t) == ARRAY_REF)
		    t = वृक्ष_OPERAND (t, 0);
		}
	    }
	  bitmap_set_bit (&is_on_device_head, DECL_UID (t));
	  जर (VAR_P (t) || वृक्ष_CODE (t) == PARM_DECL)
	    c_mark_addressable (t);
	  जा check_dup_generic_t;

	स्थिती OMP_CLAUSE_USE_DEVICE_ADDR:
	  t = OMP_CLAUSE_DECL (c);
	  जर (VAR_P (t) || वृक्ष_CODE (t) == PARM_DECL)
	    c_mark_addressable (t);
	  जा check_dup_generic;

	स्थिती OMP_CLAUSE_NOWAIT:
	  जर (copyprivate_seen)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<nowait%> clause must not be used together "
			"with %<copyprivate%> clause");
	      हटाओ = सत्य;
	      थांबा;
	    }
	  nowait_clause = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  सुरूठेवा;

	स्थिती OMP_CLAUSE_ORDER:
	  जर (ordered_clause)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<order%> clause must not be used together "
			"with %<ordered%> clause");
	      हटाओ = सत्य;
	      थांबा;
	    }
	  अन्यथा जर (order_clause)
	    {
	      /* Silently remove duplicates.  */
	      हटाओ = सत्य;
	      थांबा;
	    }
	  order_clause = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  सुरूठेवा;

	स्थिती OMP_CLAUSE_DETACH:
	  t = OMP_CLAUSE_DECL (c);
	  जर (detach_seen)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"too many %qs clauses on a task construct",
			"detach");
	      हटाओ = सत्य;
	      थांबा;
	    }
	  detach_seen = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  c_mark_addressable (t);
	  सुरूठेवा;

	स्थिती OMP_CLAUSE_IF:
	स्थिती OMP_CLAUSE_SELF:
	स्थिती OMP_CLAUSE_अंक_THREADS:
	स्थिती OMP_CLAUSE_अंक_TEAMS:
	स्थिती OMP_CLAUSE_THREAD_LIMIT:
	स्थिती OMP_CLAUSE_DEFAULT:
	स्थिती OMP_CLAUSE_UNTIED:
	स्थिती OMP_CLAUSE_COLLAPSE:
	स्थिती OMP_CLAUSE_FINAL:
	स्थिती OMP_CLAUSE_DEVICE:
	स्थिती OMP_CLAUSE_DIST_SCHEDULE:
	स्थिती OMP_CLAUSE_DYN_GROUPPRIVATE:
	स्थिती OMP_CLAUSE_PARALLEL:
	स्थिती OMP_CLAUSE_FOR:
	स्थिती OMP_CLAUSE_SECTIONS:
	स्थिती OMP_CLAUSE_TASKGROUP:
	स्थिती OMP_CLAUSE_PROC_BIND:
	स्थिती OMP_CLAUSE_DEVICE_TYPE:
	स्थिती OMP_CLAUSE_PRIORITY:
	स्थिती OMP_CLAUSE_THREADS:
	स्थिती OMP_CLAUSE_SIMD:
	स्थिती OMP_CLAUSE_HINT:
	स्थिती OMP_CLAUSE_FILTER:
	स्थिती OMP_CLAUSE_DEFAULTMAP:
	स्थिती OMP_CLAUSE_BIND:
	स्थिती OMP_CLAUSE_अंक_GANGS:
	स्थिती OMP_CLAUSE_अंक_WORKERS:
	स्थिती OMP_CLAUSE_VECTOR_LENGTH:
	स्थिती OMP_CLAUSE_ASYNC:
	स्थिती OMP_CLAUSE_WAIT:
	स्थिती OMP_CLAUSE_AUTO:
	स्थिती OMP_CLAUSE_INDEPENDENT:
	स्थिती OMP_CLAUSE_SEQ:
	स्थिती OMP_CLAUSE_GANG:
	स्थिती OMP_CLAUSE_WORKER:
	स्थिती OMP_CLAUSE_VECTOR:
	स्थिती OMP_CLAUSE_TILE:
	स्थिती OMP_CLAUSE_IF_PRESENT:
	स्थिती OMP_CLAUSE_FINALIZE:
	स्थिती OMP_CLAUSE_NOHOST:
	स्थिती OMP_CLAUSE_INDIRECT:
	स्थिती OMP_CLAUSE_NOVARIANTS:
	स्थिती OMP_CLAUSE_NOCONTEXT:
	  pc = &OMP_CLAUSE_CHAIN (c);
	  सुरूठेवा;

	स्थिती OMP_CLAUSE_GRAINSIZE:
	  grainsize_seen = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  सुरूठेवा;

	स्थिती OMP_CLAUSE_अंक_TASKS:
	  अंक_tasks_seen = सत्य;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  सुरूठेवा;

	स्थिती OMP_CLAUSE_MERGEABLE:
	  mergeable_seen = सत्य;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  सुरूठेवा;

	स्थिती OMP_CLAUSE_NOGROUP:
	  nogroup_seen = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  सुरूठेवा;

	स्थिती OMP_CLAUSE_SCHEDULE:
	  schedule_clause = c;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  सुरूठेवा;

	स्थिती OMP_CLAUSE_ORDERED:
	  ordered_clause = c;
	  जर (order_clause)
	    {
	      error_at (OMP_CLAUSE_LOCATION (*order_clause),
			"%<order%> clause must not be used together "
			"with %<ordered%> clause");
	      *order_clause = OMP_CLAUSE_CHAIN (*order_clause);
	      order_clause = रिक्त;
	    }
	  pc = &OMP_CLAUSE_CHAIN (c);
	  सुरूठेवा;

	स्थिती OMP_CLAUSE_SAFELEN:
	  safelen = c;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  सुरूठेवा;
	स्थिती OMP_CLAUSE_SIMDLEN:
	  simdlen = c;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  सुरूठेवा;

	स्थिती OMP_CLAUSE_FULL:
	  full_seen = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  सुरूठेवा;

	स्थिती OMP_CLAUSE_PARTIAL:
	  partial_seen = सत्य;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  सुरूठेवा;

	स्थिती OMP_CLAUSE_SIZES:
	  pc = &OMP_CLAUSE_CHAIN (c);
	  सुरूठेवा;

	स्थिती OMP_CLAUSE_INBRANCH:
	स्थिती OMP_CLAUSE_NOTINBRANCH:
	  जर (branch_seen)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<inbranch%> clause is incompatible with "
			"%<notinbranch%>");
	      हटाओ = सत्य;
	      थांबा;
	    }
	  branch_seen = सत्य;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  सुरूठेवा;

	स्थिती OMP_CLAUSE_INCLUSIVE:
	स्थिती OMP_CLAUSE_EXCLUSIVE:
	  need_complete = सत्य;
	  need_implicitly_determined = सत्य;
	  t = OMP_CLAUSE_DECL (c);
	  जर (!VAR_P (t) && वृक्ष_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %qs", t,
			omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	      हटाओ = सत्य;
	    }
	  थांबा;

	स्थिती OMP_CLAUSE_INIT:
	  init_seen = सत्य;
	  जर (!OMP_CLAUSE_INIT_TARGETSYNC (c))
	    init_no_targetsync_clause = c;
	  /* FALLTHRU */
	स्थिती OMP_CLAUSE_DESTROY:
	स्थिती OMP_CLAUSE_USE:
	  init_use_destroy_seen = सत्य;
	  t = OMP_CLAUSE_DECL (c);
	  जर (bitmap_bit_p (&generic_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD appears more than once in action clauses", t);
	      हटाओ = सत्य;
	      थांबा;
	    }
	  bitmap_set_bit (&generic_head, DECL_UID (t));
	  /* FALLTHRU */
	स्थिती OMP_CLAUSE_INTEROP:
	  जर (/* ort == C_ORT_OMP_INTEROP [uncomment for depobj init]  */
		   !c_omp_interop_t_p (वृक्ष_TYPE (OMP_CLAUSE_DECL (c))))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD must be of %<omp_interop_t%>",
			OMP_CLAUSE_DECL (c));
	      हटाओ = सत्य;
	    }
	  अन्यथा जर ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_INIT
		    || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DESTROY)
		   && वृक्ष_READONLY (OMP_CLAUSE_DECL (c)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD shall not be const", OMP_CLAUSE_DECL (c));
	      हटाओ = सत्य;
	    }
	  pc = &OMP_CLAUSE_CHAIN (c);
	  थांबा;
	पूर्वनिर्धारित:
	  gcc_unreachable ();
	}

      जर (!हटाओ)
	{
	  t = OMP_CLAUSE_DECL (c);

	  जर (need_complete)
	    {
	      t = require_complete_type (OMP_CLAUSE_LOCATION (c), t);
	      जर (t == error_mark_गाठ)
		हटाओ = सत्य;
	    }

	  जर (need_implicitly_determined)
	    {
	      स्थिरांक अक्षर *share_name = रिक्त;

	      जर (VAR_P (t) && DECL_THREAD_LOCAL_P (t))
		share_name = "threadprivate";
	      अन्यथा निवड (c_omp_predetermined_sharing (t))
		{
		स्थिती OMP_CLAUSE_DEFAULT_UNSPECIFIED:
		  थांबा;
		स्थिती OMP_CLAUSE_DEFAULT_SHARED:
		  जर ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_SHARED
		       || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_FIRSTPRIVATE)
		      && c_omp_predefined_variable (t))
		    /* The __func__ variable and similar function-local
		       predefined variables may be listed in a shared or
		       firstprivate clause.  */
		    थांबा;
		  share_name = "shared";
		  थांबा;
		स्थिती OMP_CLAUSE_DEFAULT_PRIVATE:
		  share_name = "private";
		  थांबा;
		पूर्वनिर्धारित:
		  gcc_unreachable ();
		}
	      जर (share_name)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qE is predetermined %qs for %qs",
			    t, share_name,
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  हटाओ = सत्य;
		}
	      अन्यथा जर (वृक्ष_READONLY (t)
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

      जर (हटाओ)
	{
	  जर (grp_start_p)
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

  जर (grp_start_p
      && OMP_CLAUSE_HAS_ITERATORS (*grp_start_p))
    साठी (वृक्ष gc = *grp_start_p; gc; gc = OMP_CLAUSE_CHAIN (gc))
      OMP_CLAUSE_ITERATORS (gc) = OMP_CLAUSE_ITERATORS (*grp_start_p);

  जर (simdlen
      && safelen
      && वृक्ष_int_cst_lt (OMP_CLAUSE_SAFELEN_अभिव्यक्ती (safelen),
			  OMP_CLAUSE_SIMDLEN_अभिव्यक्ती (simdlen)))
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
      OMP_CLAUSE_SIMDLEN_अभिव्यक्ती (simdlen)
	= OMP_CLAUSE_SAFELEN_अभिव्यक्ती (safelen);
    }

  जर (ordered_clause
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

  जर (reduction_seen < 0 && ordered_clause)
    {
      error_at (OMP_CLAUSE_LOCATION (ordered_clause),
		"%qs clause specified together with %<inscan%> "
		"%<reduction%> clause", "ordered");
      reduction_seen = -2;
    }

  जर (reduction_seen < 0 && schedule_clause)
    {
      error_at (OMP_CLAUSE_LOCATION (schedule_clause),
		"%qs clause specified together with %<inscan%> "
		"%<reduction%> clause", "schedule");
      reduction_seen = -2;
    }

  जर (linear_variable_step_check
      || reduction_seen == -2
      || allocate_seen
      || target_in_reduction_seen)
    साठी (pc = &clauses, c = clauses; c ; c = *pc)
      {
	तार्किक हटाओ = असत्य;
	जर (allocate_seen)
	  निवड (OMP_CLAUSE_CODE (c))
	    {
	    स्थिती OMP_CLAUSE_REDUCTION:
	    स्थिती OMP_CLAUSE_IN_REDUCTION:
	    स्थिती OMP_CLAUSE_TASK_REDUCTION:
	      जर (वृक्ष_CODE (OMP_CLAUSE_DECL (c)) == MEM_REF)
		{
		  t = वृक्ष_OPERAND (OMP_CLAUSE_DECL (c), 0);
		  जर (वृक्ष_CODE (t) == POINTER_PLUS_अभिव्यक्ती)
		    t = वृक्ष_OPERAND (t, 0);
		  जर (वृक्ष_CODE (t) == ADDR_अभिव्यक्ती
		      || INDIRECT_REF_P (t))
		    t = वृक्ष_OPERAND (t, 0);
		  जर (DECL_P (t))
		    bitmap_clear_bit (&aligned_head, DECL_UID (t));
		  थांबा;
		}
	      /* FALLTHRU */
	    स्थिती OMP_CLAUSE_PRIVATE:
	    स्थिती OMP_CLAUSE_FIRSTPRIVATE:
	    स्थिती OMP_CLAUSE_LASTPRIVATE:
	    स्थिती OMP_CLAUSE_LINEAR:
	      जर (DECL_P (OMP_CLAUSE_DECL (c)))
		bitmap_clear_bit (&aligned_head,
				  DECL_UID (OMP_CLAUSE_DECL (c)));
	      थांबा;
	    पूर्वनिर्धारित:
	      थांबा;
	    }
	जर (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_LINEAR
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
	अन्यथा जर (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
		 && reduction_seen == -2)
	  OMP_CLAUSE_REDUCTION_INSCAN (c) = 0;
	जर (target_in_reduction_seen
	    && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP)
	  {
	    वृक्ष t = OMP_CLAUSE_DECL (c);
	    पर्यंत (handled_component_p (t)
		   || INDIRECT_REF_P (t)
		   || वृक्ष_CODE (t) == ADDR_अभिव्यक्ती
		   || वृक्ष_CODE (t) == MEM_REF
		   || वृक्ष_CODE (t) == NON_LVALUE_अभिव्यक्ती)
	      t = वृक्ष_OPERAND (t, 0);
	    जर (DECL_P (t)
		&& bitmap_bit_p (&oacc_reduction_head, DECL_UID (t)))
	      OMP_CLAUSE_MAP_IN_REDUCTION (c) = 1;
	  }

	जर (हटाओ)
	  *pc = OMP_CLAUSE_CHAIN (c);
	अन्यथा
	  pc = &OMP_CLAUSE_CHAIN (c);
      }

  जर (allocate_seen)
    साठी (pc = &clauses, c = clauses; c ; c = *pc)
      {
	तार्किक हटाओ = असत्य;
	जर (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ALLOCATE
	    && !OMP_CLAUSE_ALLOCATE_COMBINED (c)
	    && bitmap_bit_p (&aligned_head, DECL_UID (OMP_CLAUSE_DECL (c))))
	  {
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD specified in %<allocate%> clause but not in "
		      "an explicit privatization clause", OMP_CLAUSE_DECL (c));
	    हटाओ = सत्य;
	  }
	जर (हटाओ)
	  *pc = OMP_CLAUSE_CHAIN (c);
	अन्यथा
	  pc = &OMP_CLAUSE_CHAIN (c);
      }

  जर (nogroup_seen && reduction_seen)
    {
      error_at (OMP_CLAUSE_LOCATION (*nogroup_seen),
		"%<nogroup%> clause must not be used together with "
		"%<reduction%> clause");
      *nogroup_seen = OMP_CLAUSE_CHAIN (*nogroup_seen);
    }

  जर (grainsize_seen && अंक_tasks_seen)
    {
      error_at (OMP_CLAUSE_LOCATION (*grainsize_seen),
		"%<grainsize%> clause must not be used together with "
		"%<num_tasks%> clause");
      *grainsize_seen = OMP_CLAUSE_CHAIN (*grainsize_seen);
    }

  जर (full_seen && partial_seen)
    {
      error_at (OMP_CLAUSE_LOCATION (*full_seen),
		"%<full%> clause must not be used together with "
		"%<partial%> clause");
      *full_seen = OMP_CLAUSE_CHAIN (*full_seen);
    }

  जर (detach_seen)
    {
      जर (mergeable_seen)
	{
	  error_at (OMP_CLAUSE_LOCATION (*detach_seen),
		    "%<detach%> clause must not be used together with "
		    "%<mergeable%> clause");
	  *detach_seen = OMP_CLAUSE_CHAIN (*detach_seen);
	}
      अन्यथा
	{
	  वृक्ष detach_decl = OMP_CLAUSE_DECL (*detach_seen);

	  साठी (pc = &clauses, c = clauses; c ; c = *pc)
	    {
	      तार्किक हटाओ = असत्य;
	      जर ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_SHARED
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
	      जर (हटाओ)
		*pc = OMP_CLAUSE_CHAIN (c);
	      अन्यथा
		pc = &OMP_CLAUSE_CHAIN (c);
	    }
	}
    }

  जर (ort == C_ORT_OMP_INTEROP
      && depend_clause
      && (!init_use_destroy_seen
	  || (init_seen && init_no_targetsync_clause)))
    {
      error_at (OMP_CLAUSE_LOCATION (depend_clause),
		"%<depend%> clause requires action clauses with "
		"%<targetsync%> interop-type");
      जर (init_no_targetsync_clause)
	inform (OMP_CLAUSE_LOCATION (init_no_targetsync_clause),
		"%<init%> clause lacks the %<targetsync%> modifier");
    }

  bitmap_obstack_release (रिक्त);
  परत clauses;
}

/* Do processing necessary to make CLAUSES well-formed, where CLAUSES result
   from implicit instantiation of user-defined mappers (in gimplify.cc).  */

वृक्ष
c_omp_finish_mapper_clauses (वृक्ष clauses)
{
  परत c_finish_omp_clauses (clauses, C_ORT_OMP);
}

/* Return code to initialize DST with a copy constructor from SRC.
   C doesn't have copy constructors nor assignment operators, only for
   _Atomic vars we need to perform __atomic_load from src into a temporary
   followed by __atomic_store of the temporary to dst.  */

वृक्ष
c_omp_clause_copy_ctor (वृक्ष clause, वृक्ष dst, वृक्ष src)
{
  जर (!really_atomic_lvalue (dst) && !really_atomic_lvalue (src))
    परत build2 (MODIFY_अभिव्यक्ती, वृक्ष_TYPE (dst), dst, src);

  location_t loc = OMP_CLAUSE_LOCATION (clause);
  वृक्ष type = वृक्ष_TYPE (dst);
  वृक्ष nonatomic_type = build_qualified_type (type, TYPE_UNQUALIFIED);
  वृक्ष tmp = create_tmp_var (nonatomic_type);
  वृक्ष tmp_addr = build_fold_addr_अभिव्यक्ती (tmp);
  वृक्ष_ADDRESSABLE (tmp) = 1;
  suppress_warning (tmp);
  वृक्ष src_addr = build_fold_addr_अभिव्यक्ती (src);
  वृक्ष dst_addr = build_fold_addr_अभिव्यक्ती (dst);
  वृक्ष seq_cst = build_int_cst (integer_type_गाठ, MEMMODEL_SEQ_CST);
  vec<वृक्ष, va_gc> *params;
  /* Expansion of a generic atomic load may require an addition
     element, so allocate enough to prevent a resize.  */
  vec_alloc (params, 4);

  /* Build __atomic_load (&src, &tmp, SEQ_CST);  */
  वृक्ष fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_LOAD);
  params->quick_ढकला (src_addr);
  params->quick_ढकला (tmp_addr);
  params->quick_ढकला (seq_cst);
  वृक्ष load = c_build_function_call_vec (loc, vNULL, fndecl, params, रिक्त);

  vec_alloc (params, 4);

  /* Build __atomic_store (&dst, &tmp, SEQ_CST);  */
  fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_STORE);
  params->quick_ढकला (dst_addr);
  params->quick_ढकला (tmp_addr);
  params->quick_ढकला (seq_cst);
  वृक्ष store = c_build_function_call_vec (loc, vNULL, fndecl, params, रिक्त);
  परत build2 (COMPOUND_अभिव्यक्ती, void_type_गाठ, load, store);
}

/* Create a transaction node.  */

वृक्ष
c_finish_transaction (location_t loc, वृक्ष block, पूर्णांक flags)
{
  वृक्ष stmt = build_stmt (loc, TRANSACTION_अभिव्यक्ती, block);
  जर (flags & TM_STMT_ATTR_OUTER)
    TRANSACTION_अभिव्यक्ती_OUTER (stmt) = 1;
  जर (flags & TM_STMT_ATTR_RELAXED)
    TRANSACTION_अभिव्यक्ती_RELAXED (stmt) = 1;
  परत add_stmt (stmt);
}

/* Make a variant type in the proper way for C/C++, propagating qualifiers
   down to the element type of an array.  If ORIG_QUAL_TYPE is not
   NULL, then it should be used as the qualified type
   ORIG_QUAL_INDIRECT levels down in array type derivation (to
   preserve information about the typedef name from which an array
   type was derived).  */

वृक्ष
c_build_qualified_type (वृक्ष type, पूर्णांक type_quals, वृक्ष orig_qual_type,
			माप_प्रकार orig_qual_indirect)
{
  जर (type == error_mark_गाठ)
    परत type;

  जर (वृक्ष_CODE (type) == ARRAY_TYPE)
    {
      वृक्ष t;
      वृक्ष element_type = c_build_qualified_type (वृक्ष_TYPE (type),
						  type_quals, orig_qual_type,
						  orig_qual_indirect - 1);

      /* See if we already have an identically qualified type.  */
      जर (orig_qual_type && orig_qual_indirect == 0)
	t = orig_qual_type;
      अन्यथा
	साठी (t = TYPE_MAIN_VARIANT (type); t; t = TYPE_NEXT_VARIANT (t))
	  {
	    जर (TYPE_QUALS (strip_array_types (t)) == type_quals
		&& TYPE_NAME (t) == TYPE_NAME (type)
		&& TYPE_CONTEXT (t) == TYPE_CONTEXT (type)
		&& attribute_list_equal (TYPE_ATTRIBUTES (t),
					 TYPE_ATTRIBUTES (type)))
	      थांबा;
	  }
      जर (!t)
	{
          वृक्ष domain = TYPE_DOMAIN (type);

	  t = build_variant_type_copy (type);
	  वृक्ष_TYPE (t) = element_type;
	  TYPE_ADDR_SPACE (t) = TYPE_ADDR_SPACE (element_type);

          जर (TYPE_STRUCTURAL_EQUALITY_P (element_type)
              || (domain && TYPE_STRUCTURAL_EQUALITY_P (domain)))
            SET_TYPE_STRUCTURAL_EQUALITY (t);
          अन्यथा जर (TYPE_CANONICAL (element_type) != element_type
                   || (domain && TYPE_CANONICAL (domain) != domain))
            {
              वृक्ष unqualified_canon
		= c_build_array_type (TYPE_CANONICAL (element_type),
				      domain ? TYPE_CANONICAL (domain)
					     : NULL_वृक्ष);
              जर (TYPE_REVERSE_STORAGE_ORDER (type))
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
      परत t;
    }

  /* A restrict-qualified pointer type must be a pointer to object or
     incomplete type.  Note that the use of POINTER_TYPE_P also allows
     REFERENCE_TYPEs, which is appropriate for C++.  */
  जर ((type_quals & TYPE_QUAL_RESTRICT)
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
  जर ((RECORD_OR_UNION_TYPE_P (var_type)
       || वृक्ष_CODE (var_type) == ENUMERAL_TYPE)
      && TYPE_MAIN_VARIANT (var_type) != var_type)
    C_TYPE_INCOMPLETE_VARS (var_type) = 0;
  परत var_type;
}

/* Build a VA_ARG_EXPR for the C parser.  */

वृक्ष
c_build_va_arg (location_t loc1, वृक्ष अभिव्यक्ती, location_t loc2, वृक्ष type,
		वृक्ष type_अभिव्यक्ती)
{
  जर (error_operand_p (type))
    परत error_mark_गाठ;
  /* VA_ARG_EXPR cannot be used for a scalar va_list with reverse storage
     order because it takes the address of the expression.  */
  अन्यथा जर (handled_component_p (अभिव्यक्ती)
	   && reverse_storage_order_for_component_p (अभिव्यक्ती))
    {
      error_at (loc1, "cannot use %<va_arg%> with reverse storage order");
      परत error_mark_गाठ;
    }
  अन्यथा जर (!COMPLETE_TYPE_P (type))
    {
      error_at (loc2, "second argument to %<va_arg%> is of incomplete "
		"type %qT", type);
      परत error_mark_गाठ;
    }
  अन्यथा जर (वृक्ष_CODE (type) == FUNCTION_TYPE)
    {
      error_at (loc2, "second argument to %<va_arg%> is a function type %qT",
		type);
      परत error_mark_गाठ;
    }
  अन्यथा जर (वृक्ष_CODE (type) == ARRAY_TYPE && C_TYPE_VARIABLE_SIZE (type)
	   && !flag_isoc99)
    {
      error_at (loc2, "second argument to %<va_arg%> is an array type %qT",
		type);
      परत error_mark_गाठ;
    }
  अन्यथा जर (warn_cxx_compat && वृक्ष_CODE (type) == ENUMERAL_TYPE)
    warning_at (loc2, OPT_Wc___compat,
		"C++ requires promoted type, not enum type, in %<va_arg%>");

  जर (flag_isoc99 && वृक्ष_CODE (type) == ARRAY_TYPE)
    {
      warning_at (loc2, 0, "second argument to %<va_arg%> is an array type %qT",
		  type);
      /* We create a trap but evaluate side effects first.  */
      वृक्ष trapfn = builtin_decl_explicit (BUILT_IN_TRAP);
      trapfn = build_call_अभिव्यक्ती_loc (loc2, trapfn, 0);
      वृक्ष e2 = build2 (COMPOUND_अभिव्यक्ती, void_type_गाठ, अभिव्यक्ती, trapfn);
      /* Return a compound literal of the right type.  */
      वृक्ष e1 = build_compound_literal (loc2, type, रिक्त, सत्य, 0, रिक्त);
      अभिव्यक्ती = build2 (COMPOUND_अभिव्यक्ती, type, e2, e1);
    }
  अन्यथा
    अभिव्यक्ती = build_va_arg (loc2, अभिव्यक्ती, type);

  जर (type_अभिव्यक्ती)
    अभिव्यक्ती = build2 (COMPOUND_अभिव्यक्ती, वृक्ष_TYPE (अभिव्यक्ती), type_अभिव्यक्ती, अभिव्यक्ती);

  परत अभिव्यक्ती;
}

/* Return truthvalue of whether T1 is the same tree structure as T2.
   Return 1 if they are the same. Return false if they are different.  */

तार्किक
c_वृक्ष_equal (वृक्ष t1, वृक्ष t2)
{
  गणना वृक्ष_code code1, code2;

  जर (t1 == t2)
    परत सत्य;
  जर (!t1 || !t2)
    परत असत्य;

  साठी (code1 = वृक्ष_CODE (t1); code1 == NON_LVALUE_अभिव्यक्ती;
       code1 = वृक्ष_CODE (t1))
    t1 = वृक्ष_OPERAND (t1, 0);
  साठी (code2 = वृक्ष_CODE (t2); code2 == NON_LVALUE_अभिव्यक्ती;
       code2 = वृक्ष_CODE (t2))
    t2 = वृक्ष_OPERAND (t2, 0);

  /* They might have become equal now.  */
  जर (t1 == t2)
    परत सत्य;

  जर (code1 != code2)
    परत असत्य;

  जर (CONSTANT_CLASS_P (t1) && !comptypes (वृक्ष_TYPE (t1), वृक्ष_TYPE (t2)))
    परत असत्य;

  निवड (code1)
    {
    स्थिती INTEGER_CST:
      परत wi::to_wide (t1) == wi::to_wide (t2);

    स्थिती REAL_CST:
      परत real_equal (&वृक्ष_REAL_CST (t1), &वृक्ष_REAL_CST (t2));

    स्थिती STRING_CST:
      परत वृक्ष_STRING_LENGTH (t1) == वृक्ष_STRING_LENGTH (t2)
	&& !स_भेद (वृक्ष_STRING_POINTER (t1), वृक्ष_STRING_POINTER (t2),
		    वृक्ष_STRING_LENGTH (t1));

    स्थिती FIXED_CST:
      परत FIXED_मूल्ये_IDENTICAL (वृक्ष_FIXED_CST (t1),
				     वृक्ष_FIXED_CST (t2));

    स्थिती COMPLEX_CST:
      परत c_वृक्ष_equal (वृक्ष_REALPART (t1), वृक्ष_REALPART (t2))
	     && c_वृक्ष_equal (वृक्ष_IMAGPART (t1), वृक्ष_IMAGPART (t2));

    स्थिती VECTOR_CST:
      परत operand_equal_p (t1, t2, OEP_ONLY_CONST);

    स्थिती CONSTRUCTOR:
      /* We need to do this when determining whether or not two
	 non-type pointer to member function template arguments
	 are the same.  */
      जर (!comptypes (वृक्ष_TYPE (t1), वृक्ष_TYPE (t2))
	  || CONSTRUCTOR_NELTS (t1) != CONSTRUCTOR_NELTS (t2))
	परत असत्य;
      {
	वृक्ष field, मूल्य;
	अचिन्हित पूर्णांक i;
	FOR_EACH_CONSTRUCTOR_ELT (CONSTRUCTOR_ELTS (t1), i, field, मूल्य)
	  {
	    constructor_elt *elt2 = CONSTRUCTOR_ELT (t2, i);
	    जर (!c_वृक्ष_equal (field, elt2->index)
		|| !c_वृक्ष_equal (मूल्य, elt2->मूल्य))
	      परत असत्य;
	  }
      }
      परत सत्य;

    स्थिती वृक्ष_LIST:
      जर (!c_वृक्ष_equal (वृक्ष_PURPOSE (t1), वृक्ष_PURPOSE (t2)))
	परत असत्य;
      जर (!c_वृक्ष_equal (वृक्ष_मूल्य (t1), वृक्ष_मूल्य (t2)))
	परत असत्य;
      परत c_वृक्ष_equal (वृक्ष_CHAIN (t1), वृक्ष_CHAIN (t2));

    स्थिती SAVE_अभिव्यक्ती:
      परत c_वृक्ष_equal (वृक्ष_OPERAND (t1, 0), वृक्ष_OPERAND (t2, 0));

    स्थिती CALL_अभिव्यक्ती:
      {
	वृक्ष arg1, arg2;
	call_अभिव्यक्ती_arg_iterator iter1, iter2;
	जर (!c_वृक्ष_equal (CALL_अभिव्यक्ती_FN (t1), CALL_अभिव्यक्ती_FN (t2)))
	  परत असत्य;
	साठी (arg1 = first_call_अभिव्यक्ती_arg (t1, &iter1),
	       arg2 = first_call_अभिव्यक्ती_arg (t2, &iter2);
	     arg1 && arg2;
	     arg1 = next_call_अभिव्यक्ती_arg (&iter1),
	       arg2 = next_call_अभिव्यक्ती_arg (&iter2))
	  जर (!c_वृक्ष_equal (arg1, arg2))
	    परत असत्य;
	जर (arg1 || arg2)
	  परत असत्य;
	परत सत्य;
      }

    स्थिती TARGET_अभिव्यक्ती:
      {
	वृक्ष o1 = वृक्ष_OPERAND (t1, 0);
	वृक्ष o2 = वृक्ष_OPERAND (t2, 0);

	/* Special case: if either target is an unallocated VAR_DECL,
	   it means that it's going to be unified with whatever the
	   TARGET_EXPR is really supposed to initialize, so treat it
	   as being equivalent to anything.  */
	जर (VAR_P (o1) && DECL_NAME (o1) == NULL_वृक्ष
	    && !DECL_RTL_SET_P (o1))
	  /*Nop*/;
	अन्यथा जर (VAR_P (o2) && DECL_NAME (o2) == NULL_वृक्ष
		 && !DECL_RTL_SET_P (o2))
	  /*Nop*/;
	अन्यथा जर (!c_वृक्ष_equal (o1, o2))
	  परत असत्य;

	परत c_वृक्ष_equal (वृक्ष_OPERAND (t1, 1), वृक्ष_OPERAND (t2, 1));
      }

    स्थिती COMPONENT_REF:
      जर (वृक्ष_OPERAND (t1, 1) != वृक्ष_OPERAND (t2, 1))
	परत असत्य;
      परत c_वृक्ष_equal (वृक्ष_OPERAND (t1, 0), वृक्ष_OPERAND (t2, 0));

    स्थिती PARM_DECL:
    स्थिती VAR_DECL:
    स्थिती CONST_DECL:
    स्थिती FIELD_DECL:
    स्थिती FUNCTION_DECL:
    स्थिती IDENTIFIER_गाठ:
    स्थिती SSA_NAME:
      परत असत्य;

    स्थिती वृक्ष_VEC:
      {
	अचिन्हित ix;
	जर (वृक्ष_VEC_LENGTH (t1) != वृक्ष_VEC_LENGTH (t2))
	  परत असत्य;
	साठी (ix = वृक्ष_VEC_LENGTH (t1); ix--;)
	  जर (!c_वृक्ष_equal (वृक्ष_VEC_ELT (t1, ix),
			     वृक्ष_VEC_ELT (t2, ix)))
	    परत असत्य;
	परत सत्य;
      }

    CASE_CONVERT:
      जर (!comptypes (वृक्ष_TYPE (t1), वृक्ष_TYPE (t2)))
	परत असत्य;
      थांबा;

    पूर्वनिर्धारित:
      थांबा;
    }

  निवड (वृक्ष_CODE_CLASS (code1))
    {
    स्थिती tcc_unary:
    स्थिती tcc_द्विमान:
    स्थिती tcc_comparison:
    स्थिती tcc_expression:
    स्थिती tcc_vl_exp:
    स्थिती tcc_reference:
    स्थिती tcc_statement:
      {
	पूर्णांक i, n = वृक्ष_OPERAND_LENGTH (t1);

	निवड (code1)
	  {
	  स्थिती PREINCREMENT_अभिव्यक्ती:
	  स्थिती PREDECREMENT_अभिव्यक्ती:
	  स्थिती POSTINCREMENT_अभिव्यक्ती:
	  स्थिती POSTDECREMENT_अभिव्यक्ती:
	    n = 1;
	    थांबा;
	  स्थिती ARRAY_REF:
	    n = 2;
	    थांबा;
	  पूर्वनिर्धारित:
	    थांबा;
	  }

	जर (वृक्ष_CODE_CLASS (code1) == tcc_vl_exp
	    && n != वृक्ष_OPERAND_LENGTH (t2))
	  परत असत्य;

	साठी (i = 0; i < n; ++i)
	  जर (!c_वृक्ष_equal (वृक्ष_OPERAND (t1, i), वृक्ष_OPERAND (t2, i)))
	    परत असत्य;

	परत सत्य;
      }

    स्थिती tcc_type:
      परत comptypes (t1, t2);
    पूर्वनिर्धारित:
      gcc_unreachable ();
    }
}

/* Returns true when the function declaration FNDECL is implicit,
   introduced as a result of a call to an otherwise undeclared
   function, and false otherwise.  */

तार्किक
c_decl_implicit (const_वृक्ष fndecl)
{
  परत C_DECL_IMPLICIT (fndecl);
}
