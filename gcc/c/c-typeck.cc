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

#অন্তর্ভাব "config.h"
#অন্তর্ভাব "system.h"
#অন্তর্ভাব "coretypes.h"
#অন্তর্ভাব "memmodel.h"
#অন্তর্ভাব "target.h"
#অন্তর্ভাব "function.h"
#অন্তর্ভাব "bitmap.h"
#অন্তর্ভাব "c-tree.h"
#অন্তর্ভাব "gimple-expr.h"
#অন্তর্ভাব "predict.h"
#অন্তর্ভাব "stor-layout.h"
#অন্তর্ভাব "trans-mem.h"
#অন্তর্ভাব "varasm.h"
#অন্তর্ভাব "stmt.h"
#অন্তর্ভাব "langhooks.h"
#অন্তর্ভাব "c-lang.h"
#অন্তর্ভাব "intl.h"
#অন্তর্ভাব "tree-iterator.h"
#অন্তর্ভাব "gimplify.h"
#অন্তর্ভাব "tree-inline.h"
#অন্তর্ভাব "omp-general.h"
#অন্তর্ভাব "c-family/c-objc.h"
#অন্তর্ভাব "c-family/c-ubsan.h"
#অন্তর্ভাব "gomp-constants.h"
#অন্তর্ভাব "spellcheck-tree.h"
#অন্তর্ভাব "c-family/c-type-mismatch.h"
#অন্তর্ভাব "stringpool.h"
#অন্তর্ভাব "attribs.h"
#অন্তর্ভাব "asan.h"
#অন্তর্ভাব "realmpfr.h"
#অন্তর্ভাব "tree-pretty-print-markup.h"
#অন্তর্ভাব "gcc-urlifier.h"

/* Possible cases of implicit conversions.  Used to select diagnostic messages
   and control folding initializers in convert_for_assignment.  */
গণনা impl_conv {
  ic_argpass,
  ic_assign,
  ic_init,
  ic_init_const,
  ic_return
};

/* The level of nesting inside "__alignof__".  */
পূর্ণসংখ্যা in_alignof;

/* The level of nesting inside "sizeof".  */
পূর্ণসংখ্যা in_sizeof;

/* The level of nesting inside "countof".  */
পূর্ণসংখ্যা in_countof;

/* The level of nesting inside "typeof".  */
পূর্ণসংখ্যা in_typeof;

/* The level of nesting inside "_Generic".  */
পূর্ণসংখ্যা in_generic;

/* True when parsing OpenMP loop expressions.  */
যৌক্তিক c_in_omp_for;

/* True when parsing OpenMP map clause.  */
যৌক্তিক c_omp_array_section_p;

/* The argument of last parsed sizeof expression, only to be tested
   if expr.original_code == SIZEOF_EXPR.  */
বৃক্ষ c_last_sizeof_arg;
location_t c_last_sizeof_loc;

/* Nonzero if we might need to print a "missing braces around
   initializer" message within this initializer.  */
স্থির পূর্ণসংখ্যা found_missing_braces;

স্থির যৌক্তিক require_constant_মান;
স্থির যৌক্তিক require_constant_elements;
স্থির যৌক্তিক require_constexpr_মান;

স্থির বৃক্ষ qualify_type (বৃক্ষ, বৃক্ষ);
কাঠামো comptypes_তথ্য;
স্থির যৌক্তিক tagged_types_tu_compatible_p (const_বৃক্ষ, const_বৃক্ষ,
					  কাঠামো comptypes_তথ্য *);
স্থির যৌক্তিক comp_target_types (location_t, বৃক্ষ, বৃক্ষ);
স্থির যৌক্তিক function_types_compatible_p (const_বৃক্ষ, const_বৃক্ষ,
					 কাঠামো comptypes_তথ্য *);
স্থির যৌক্তিক type_lists_compatible_p (const_বৃক্ষ, const_বৃক্ষ,
				     কাঠামো comptypes_তথ্য *);
স্থির পূর্ণসংখ্যা convert_arguments (location_t, vec<location_t>, বৃক্ষ,
			      vec<বৃক্ষ, va_gc> *, vec<বৃক্ষ, va_gc> *, বৃক্ষ,
			      বৃক্ষ);
স্থির বৃক্ষ pointer_diff (location_t, বৃক্ষ, বৃক্ষ, বৃক্ষ *);
স্থির বৃক্ষ convert_for_assignment (location_t, location_t, বৃক্ষ, বৃক্ষ, বৃক্ষ,
				    গণনা impl_conv, যৌক্তিক, বৃক্ষ, বৃক্ষ, পূর্ণসংখ্যা,
				    পূর্ণসংখ্যা = 0);
স্থির বৃক্ষ valid_compound_রাশিমালা_initializer (বৃক্ষ, বৃক্ষ);
স্থির শূন্য ঠেলো_string (ধ্রুবক অক্ষর *);
স্থির শূন্য ঠেলো_member_name (বৃক্ষ);
স্থির পূর্ণসংখ্যা spelling_দৈর্ঘ্য (শূন্য);
স্থির অক্ষর *print_spelling (অক্ষর *);
স্থির শূন্য warning_init (location_t, পূর্ণসংখ্যা, ধ্রুবক অক্ষর *);
স্থির বৃক্ষ digest_init (location_t, বৃক্ষ, বৃক্ষ, বৃক্ষ, বৃক্ষ, যৌক্তিক, যৌক্তিক, যৌক্তিক,
			 যৌক্তিক, যৌক্তিক, যৌক্তিক);
স্থির শূন্য output_init_element (location_t, বৃক্ষ, বৃক্ষ, যৌক্তিক, বৃক্ষ, বৃক্ষ, যৌক্তিক,
				 যৌক্তিক, কাঠামো obstack *);
স্থির শূন্য output_pending_init_elements (পূর্ণসংখ্যা, কাঠামো obstack *);
স্থির যৌক্তিক set_designator (location_t, যৌক্তিক, কাঠামো obstack *);
স্থির শূন্য ঠেলো_range_স্তূপ (বৃক্ষ, কাঠামো obstack *);
স্থির শূন্য add_pending_init (location_t, বৃক্ষ, বৃক্ষ, বৃক্ষ, যৌক্তিক,
			      কাঠামো obstack *);
স্থির শূন্য set_nonincremental_init (কাঠামো obstack *);
স্থির শূন্য set_nonincremental_init_from_string (বৃক্ষ, কাঠামো obstack *);
স্থির বৃক্ষ find_init_member (বৃক্ষ, কাঠামো obstack *);
স্থির শূন্য readonly_warning (বৃক্ষ, গণনা lvalue_use);
স্থির পূর্ণসংখ্যা lvalue_or_else (location_t, const_বৃক্ষ, গণনা lvalue_use);
স্থির শূন্য record_maybe_used_decl (বৃক্ষ, যৌক্তিক address);
স্থির যৌক্তিক comptypes_internal (const_বৃক্ষ, const_বৃক্ষ,
				কাঠামো comptypes_তথ্য *তথ্য);
স্থির যৌক্তিক comptypes_check_for_composite (বৃক্ষ t1, বৃক্ষ t2);
স্থির যৌক্তিক handle_counted_by_p (বৃক্ষ);
স্থির যৌক্তিক শীর্ষ_array_vla_p (const_বৃক্ষ type);


/* Return true if EXP is a null pointer constant, false otherwise.  */

যৌক্তিক
null_pointer_constant_p (const_বৃক্ষ রাশিমালা)
{
  /* This should really operate on c_expr structures, but they aren't
     yet available everywhere required.  */
  বৃক্ষ type = বৃক্ষ_TYPE (রাশিমালা);

  /* An integer constant expression with the value 0, such an expression
     cast to type void*, or the predefined constant nullptr, are a null
     pointer constant.  */
  যদি (রাশিমালা == nullptr_গ্রন্থি)
    ফেরত সত্য;

  ফেরত (বৃক্ষ_CODE (রাশিমালা) == INTEGER_CST
	  && !বৃক্ষ_OVERFLOW (রাশিমালা)
	  && integer_zerop (রাশিমালা)
	  && (INTEGRAL_TYPE_P (type)
	      || (বৃক্ষ_CODE (type) == POINTER_TYPE
		  && VOID_TYPE_P (বৃক্ষ_TYPE (type))
		  && TYPE_QUALS (বৃক্ষ_TYPE (type)) == TYPE_UNQUALIFIED)));
}

/* EXPR may appear in an unevaluated part of an integer constant
   expression, but not in an evaluated part.  Wrap it in a
   C_MAYBE_CONST_EXPR, or mark it with TREE_OVERFLOW if it is just an
   INTEGER_CST and we cannot create a C_MAYBE_CONST_EXPR.  */

স্থির বৃক্ষ
note_integer_operands (বৃক্ষ রাশিমালা)
{
  বৃক্ষ ret;
  যদি (বৃক্ষ_CODE (রাশিমালা) == INTEGER_CST && in_late_দ্বিমিক_op)
    {
      ret = copy_গ্রন্থি (রাশিমালা);
      বৃক্ষ_OVERFLOW (ret) = 1;
    }
  অন্যথা
    {
      ret = build2 (C_MAYBE_CONST_রাশিমালা, বৃক্ষ_TYPE (রাশিমালা), NULL_বৃক্ষ, রাশিমালা);
      C_MAYBE_CONST_রাশিমালা_INT_OPERANDS (ret) = 1;
    }
  ফেরত ret;
}

/* Having checked whether EXPR may appear in an unevaluated part of an
   integer constant expression and found that it may, remove any
   C_MAYBE_CONST_EXPR noting this fact and return the resulting
   expression.  */

স্থির অন্তঃরেখ বৃক্ষ
remove_c_maybe_const_রাশিমালা (বৃক্ষ রাশিমালা)
{
  যদি (বৃক্ষ_CODE (রাশিমালা) == C_MAYBE_CONST_রাশিমালা)
    ফেরত C_MAYBE_CONST_রাশিমালা_রাশিমালা (রাশিমালা);
  অন্যথা
    ফেরত রাশিমালা;
}

/* This is a cache to hold if two types are seen.  */

কাঠামো tagged_tu_seen_cache {
  ধ্রুবক কাঠামো tagged_tu_seen_cache * পরবর্তী;
  const_বৃক্ষ t1;
  const_বৃক্ষ t2;
};

/* Do `exp = require_complete_type (loc, exp);' to make sure exp
   does not have an incomplete type.  (That includes void types.)
   LOC is the location of the use.  */

বৃক্ষ
require_complete_type (location_t loc, বৃক্ষ মান)
{
  বৃক্ষ type = বৃক্ষ_TYPE (মান);

  যদি (error_operand_p (মান))
    ফেরত error_mark_গ্রন্থি;

  /* First, detect a valid value with a complete type.  */
  যদি (COMPLETE_TYPE_P (type))
    ফেরত মান;

  c_incomplete_type_error (loc, মান, type);
  ফেরত error_mark_গ্রন্থি;
}

/* Print an error message for invalid use of an incomplete type.
   VALUE is the expression that was used (or 0 if that isn't known)
   and TYPE is the type that was invalid.  LOC is the location for
   the error.  */

শূন্য
c_incomplete_type_error (location_t loc, const_বৃক্ষ মান, const_বৃক্ষ type)
{
  /* Avoid duplicate error message.  */
  যদি (বৃক্ষ_CODE (type) == ERROR_MARK)
    ফেরত;

  যদি (মান != NULL_বৃক্ষ && (VAR_P (মান) || বৃক্ষ_CODE (মান) == PARM_DECL))
    error_at (loc, "%qD has an incomplete type %qT", মান, type);
  অন্যথা
    {
    retry:
      /* We must print an error message.  Be clever about what it says.  */

      নির্বাচন (বৃক্ষ_CODE (type))
	{
	ক্ষেত্র RECORD_TYPE:
	ক্ষেত্র UNION_TYPE:
	ক্ষেত্র ENUMERAL_TYPE:
	  বিরতি;

	ক্ষেত্র VOID_TYPE:
	  error_at (loc, "invalid use of void expression");
	  ফেরত;

	ক্ষেত্র ARRAY_TYPE:
	  যদি (TYPE_DOMAIN (type))
	    {
	      যদি (flexible_array_member_type_p (type))
		{
		  error_at (loc, "invalid use of flexible array member");
		  ফেরত;
		}
	      type = বৃক্ষ_TYPE (type);
	      যাও retry;
	    }
	  error_at (loc, "invalid use of array with unspecified bounds");
	  ফেরত;

	পূর্বনির্ধারিত:
	  gcc_unreachable ();
	}

      যদি (বৃক্ষ_CODE (TYPE_NAME (type)) == IDENTIFIER_গ্রন্থি)
	error_at (loc, "invalid use of undefined type %qT", type);
      অন্যথা
	/* If this type has a typedef-name, the TYPE_NAME is a TYPE_DECL.  */
	error_at (loc, "invalid use of incomplete typedef %qT", type);
    }
}

/* Given a type, apply default promotions wrt unnamed function
   arguments and return the new type.  */

বৃক্ষ
c_type_promotes_to (বৃক্ষ type)
{
  বৃক্ষ ret = NULL_বৃক্ষ;

  যদি (TYPE_MAIN_VARIANT (type) == float_type_গ্রন্থি)
    ret = double_type_গ্রন্থি;
  অন্যথা যদি (c_promoting_integer_type_p (type))
    {
      /* Preserve unsignedness if not really getting any wider.  */
      যদি (TYPE_UNSIGNED (type)
	  && (TYPE_PRECISION (type) == TYPE_PRECISION (integer_type_গ্রন্থি)))
	ret = unsigned_type_গ্রন্থি;
      অন্যথা
	ret = integer_type_গ্রন্থি;
    }

  যদি (ret != NULL_বৃক্ষ)
    ফেরত (TYPE_ATOMIC (type)
	    ? c_build_qualified_type (ret, TYPE_QUAL_ATOMIC)
	    : ret);

  ফেরত type;
}

/* Return true if between two named address spaces, whether there is a superset
   named address space that encompasses both address spaces.  If there is a
   superset, return which address space is the superset.  */

স্থির যৌক্তিক
addr_space_superset (addr_space_t as1, addr_space_t as2, addr_space_t *common)
{
  যদি (as1 == as2)
    {
      *common = as1;
      ফেরত সত্য;
    }
  অন্যথা যদি (targetm.addr_space.subset_p (as1, as2))
    {
      *common = as2;
      ফেরত সত্য;
    }
  অন্যথা যদি (targetm.addr_space.subset_p (as2, as1))
    {
      *common = as1;
      ফেরত সত্য;
    }
  অন্যথা
    ফেরত মিথ্যা;
}

/* Return a variant of TYPE which has all the type qualifiers of LIKE
   as well as those of TYPE.  */

স্থির বৃক্ষ
qualify_type (বৃক্ষ type, বৃক্ষ like)
{
  addr_space_t as_type = TYPE_ADDR_SPACE (type);
  addr_space_t as_like = TYPE_ADDR_SPACE (like);
  addr_space_t as_common;

  /* If the two named address spaces are different, determine the common
     superset address space.  If there isn't one, raise an error.  */
  যদি (!addr_space_superset (as_type, as_like, &as_common))
    {
      as_common = as_type;
      error ("%qT and %qT are in disjoint named address spaces",
	     type, like);
    }

  ফেরত c_build_qualified_type (type,
				 TYPE_QUALS_NO_ADDR_SPACE (type)
				 | TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (like)
				 | ENCODE_QUAL_ADDR_SPACE (as_common));
}


/* Check consistency of type TYPE.  For derived types, we test that
   C_TYPE_VARIABLE_SIZE and C_TYPE_VARIABLY_MODIFIED are consistent with
   the requirements of the base type.  We also check that arrays with a
   non-constant length are marked with C_TYPE_VARIABLE_SIZE. If any
   inconsistency is detected false is returned and true otherwise.  */

স্থির যৌক্তিক
c_verify_type (বৃক্ষ type)
{
  নির্বাচন (বৃক্ষ_CODE (type))
    {
    ক্ষেত্র POINTER_TYPE:
    ক্ষেত্র FUNCTION_TYPE:
    ক্ষেত্র ARRAY_TYPE:
      /* Pointer, array, functions are variably modified if and only if the
	 target, element, return type is variably modified.  */
      যদি (!TYPE_STRUCTURAL_EQUALITY_P (type)
	  && (C_TYPE_VARIABLY_MODIFIED (type)
	      != C_TYPE_VARIABLY_MODIFIED (বৃক্ষ_TYPE (type))))
	ফেরত মিথ্যা;
      /* If the target type is structural equality, the type should also. */
      যদি (!TYPE_STRUCTURAL_EQUALITY_P (type)
	  && TYPE_STRUCTURAL_EQUALITY_P (বৃক্ষ_TYPE (type)))
	ফেরত মিথ্যা;
    পূর্বনির্ধারিত:
       বিরতি;
    }

  নির্বাচন (বৃক্ষ_CODE (type))
    {
    ক্ষেত্র POINTER_TYPE:
    ক্ষেত্র FUNCTION_TYPE:
      /* Pointer and functions can not have variable size.  */
      যদি (C_TYPE_VARIABLE_আকার (type))
	ফেরত মিথ্যা;
      বিরতি;
    ক্ষেত্র ARRAY_TYPE:
      /* An array has variable size if and only if it has a non-constant
	 dimensions or its element type has variable size.  */
      যদি ((C_TYPE_VARIABLE_আকার (বৃক্ষ_TYPE (type))
	   || শীর্ষ_array_vla_p (type))
	  != C_TYPE_VARIABLE_আকার (type))
	ফেরত মিথ্যা;
      /* If the element type or the array has variable size, then the
	 array has variable size and is variably modified.  */
      যদি (C_TYPE_VARIABLE_আকার (বৃক্ষ_TYPE (type))
	  || C_TYPE_VARIABLE_আকার (type))
	{
	  যদি (!C_TYPE_VARIABLE_আকার (type))
	    ফেরত মিথ্যা;
	  যদি (!C_TYPE_VARIABLY_MODIFIED (type))
	    ফেরত মিথ্যা;
	}

      /* va_list violates this, accept such types here.  */
      যদি (!COMPLETE_TYPE_P (বৃক্ষ_TYPE (type)))
	ফেরত সত্য;

      যদি (COMPLETE_TYPE_P (type))
	{
	  /* If the size is unknown, it can not be complete.  */
	  যদি (NULL_বৃক্ষ == TYPE_DOMAIN (type))
	    ফেরত মিথ্যা;

	  /* Zero-length arrays must have size zero.  */
	  যদি (zero_দৈর্ঘ্য_array_type_p (type)
	      && !integer_zerop (TYPE_আকার (type)))
	    ফেরত মিথ্যা;
	}
      অন্যথা
	{
	  /* If not complete but has a domain, it must be a FAM.  */
	  যদি (NULL_বৃক্ষ != TYPE_DOMAIN (type)
	      && !flexible_array_member_type_p (type))
	    ফেরত মিথ্যা;
	}
    পূর্বনির্ধারিত:
      বিরতি;
    }
  ফেরত সত্য;
}

/* Propagate C_TYPE_VARIABLY_MODIFIED and C_TYPE_VARIABLE_SIZE
   from a base type to a newly built derived or qualified type.  */

স্থির বৃক্ষ
c_set_type_bits (বৃক্ষ new_type, বৃক্ষ old_type)
{
  gcc_checking_assert (c_verify_type (old_type));

  যদি (c_type_variably_modified_p (old_type))
    C_TYPE_VARIABLY_MODIFIED (new_type) = সত্য;

  যদি (বৃক্ষ_CODE (new_type) == ARRAY_TYPE && C_TYPE_VARIABLE_আকার (old_type))
    {
      C_TYPE_VARIABLY_MODIFIED (new_type) = সত্য;
      C_TYPE_VARIABLE_আকার (new_type) = সত্য;
    }
  ফেরত new_type;
}

/* Build a pointer type using the default pointer mode.  */

বৃক্ষ
c_build_pointer_type (বৃক্ষ to_type)
{
  addr_space_t as = to_type == error_mark_গ্রন্থি ? ADDR_SPACE_GENERIC
					       : TYPE_ADDR_SPACE (to_type);
  machine_mode pointer_mode;

  যদি (as != ADDR_SPACE_GENERIC || c_default_pointer_mode == VOIDmode)
    pointer_mode = targetm.addr_space.pointer_mode (as);
  অন্যথা
    pointer_mode = c_default_pointer_mode;

  ফেরত c_build_pointer_type_for_mode (to_type, pointer_mode, মিথ্যা);
}

/* Build a pointer type using the given mode.  */

বৃক্ষ
c_build_pointer_type_for_mode (বৃক্ষ type, machine_mode mode, যৌক্তিক m)
{
  বৃক্ষ ret = build_pointer_type_for_mode (type, mode, m);
  ফেরত c_set_type_bits (ret, type);
}

/* Build a function type.  */

বৃক্ষ
c_build_function_type (বৃক্ষ type, বৃক্ষ args, যৌক্তিক no)
{
  বৃক্ষ ret = build_function_type (type, args, no);
  ফেরত c_set_type_bits (ret, type);
}

/* Build an array type.  This sets typeless storage as required
   by C2Y and C_TYPE_VARIABLY_MODIFIED and C_TYPE_VARIABLE_SIZE
   based on the element type and domain.  */

বৃক্ষ
c_build_array_type (বৃক্ষ type, বৃক্ষ domain)
{
  পূর্ণসংখ্যা type_quals = TYPE_QUALS (type);

  /* Identify typeless storage as introduced in C2Y
     and supported also in earlier language modes.  */
  যৌক্তিক typeless = (char_type_p (type) && !(type_quals & TYPE_QUAL_ATOMIC))
		  || (AGGREGATE_TYPE_P (type) && TYPE_TYPELESS_STORAGE (type));

  বৃক্ষ ret = build_array_type (type, domain, typeless);

  যদি (শীর্ষ_array_vla_p (ret))
    {
      C_TYPE_VARIABLE_আকার (ret) = 1;
      C_TYPE_VARIABLY_MODIFIED (ret) = 1;
    }

  ফেরত c_set_type_bits (ret, type);
}

/* Build an array type of unspecified size.  */
বৃক্ষ
c_build_array_type_unspecified (বৃক্ষ type)
{
  বৃক্ষ upper = build2 (COMPOUND_রাশিমালা, বৃক্ষ_TYPE (আকার_zero_গ্রন্থি),
		       integer_zero_গ্রন্থি, আকার_zero_গ্রন্থি);
  ফেরত c_build_array_type (type, build_সূচক_type (upper));
}

/* Build an array type of zero size.  */
বৃক্ষ
c_build_array_type_zero_আকার (বৃক্ষ type)
{
  /* The GCC extension for zero-length arrays differs from
     ISO flexible array members in that sizeof yields
     zero.  */
  type = c_build_array_type (type, build_সূচক_type (NULL_বৃক্ষ));
  type = build_distinct_type_copy (TYPE_MAIN_VARIANT (type));
  TYPE_আকার (type) = bitsize_zero_গ্রন্থি;
  TYPE_আকার_UNIT (type) = আকার_zero_গ্রন্থি;
  SET_TYPE_STRUCTURAL_EQUALITY (type);
  ফেরত type;
}

বৃক্ষ
c_build_type_attribute_qual_variant (বৃক্ষ type, বৃক্ষ attrs, পূর্ণসংখ্যা quals)
{
  বৃক্ষ ret = build_type_attribute_qual_variant (type, attrs, quals);
  ফেরত c_set_type_bits (ret, type);
}

বৃক্ষ
c_build_type_attribute_variant (বৃক্ষ type, বৃক্ষ attrs)
{
  ফেরত c_build_type_attribute_qual_variant (type, attrs, TYPE_QUALS (type));
}

/* Reconstruct a complex derived type.  This is used to re-construct types
   with the vector attribute.  It is called via a langhook.  */

বৃক্ষ
c_reconstruct_complex_type (বৃক্ষ type, বৃক্ষ bottom)
{
  বৃক্ষ inner, outer;

  যদি (বৃক্ষ_CODE (type) == POINTER_TYPE)
    {
      inner = c_reconstruct_complex_type (বৃক্ষ_TYPE (type), bottom);
      outer = c_build_pointer_type_for_mode (inner, TYPE_MODE (type),
					     TYPE_REF_CAN_ALIAS_ALL (type));
    }
  অন্যথা যদি (বৃক্ষ_CODE (type) == ARRAY_TYPE)
    {
      যৌক্তিক rso = TYPE_REVERSE_STORAGE_ORDER (type);
      inner = c_reconstruct_complex_type (বৃক্ষ_TYPE (type), bottom);
      outer = c_build_array_type (inner, TYPE_DOMAIN (type));
      যদি (rso)
	{
	  outer = build_distinct_type_copy (outer);
	  TYPE_REVERSE_STORAGE_ORDER (outer) = 1;
	}

      gcc_checking_assert (C_TYPE_VARIABLE_আকার (type)
			   == C_TYPE_VARIABLE_আকার (outer));
    }
  অন্যথা যদি (বৃক্ষ_CODE (type) == FUNCTION_TYPE)
    {
      inner = c_reconstruct_complex_type (বৃক্ষ_TYPE (type), bottom);
      outer = c_build_function_type (inner, TYPE_ARG_TYPES (type),
				     TYPE_NO_NAMED_ARGS_STDARG_P (type));
    }
  অন্যথা যদি (বৃক্ষ_CODE (type) == REFERENCE_TYPE
	   || বৃক্ষ_CODE (type) == OFFSET_TYPE)
    gcc_unreachable ();
  অন্যথা
    ফেরত bottom;

  ফেরত c_build_type_attribute_qual_variant (outer, TYPE_ATTRIBUTES (type),
					      TYPE_QUALS (type));
}


/* Helper function for c_canonical_type.  Check whether FIELD
   contains a pointer to a structure or union with tag,
   possibly nested in other type derivations, and return the
   type of this nested structure or union.  */
স্থির বৃক্ষ
ptr_to_tagged_member (বৃক্ষ field)
{
  gcc_assert (FIELD_DECL == বৃক্ষ_CODE (field));
  বৃক্ষ type = বৃক্ষ_TYPE (field);
  যৌক্তিক ptr_seen = মিথ্যা;
  যখন (বৃক্ষ_CODE (type) == ARRAY_TYPE
	 || বৃক্ষ_CODE (type) == FUNCTION_TYPE
	 || বৃক্ষ_CODE (type) == POINTER_TYPE)
    {
      যদি (বৃক্ষ_CODE (type) == POINTER_TYPE)
	ptr_seen = সত্য;
      type = বৃক্ষ_TYPE (type);
    }

  যদি (ptr_seen
      && RECORD_OR_UNION_TYPE_P (type)
      && NULL_বৃক্ষ != c_type_tag (type))
    ফেরত type;

  ফেরত NULL_বৃক্ষ;
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
বৃক্ষ
c_type_canonical (বৃক্ষ type)
{
  gcc_assert (RECORD_OR_UNION_TYPE_P (type));

  যৌক্তিক needs_mod = মিথ্যা;
  জন্য (বৃক্ষ x = TYPE_FIELDS (type); x; x = DECL_CHAIN (x))
    {
      যদি (!ptr_to_tagged_member (x))
	চালু;
      needs_mod = সত্য;
      বিরতি;
    }
  যদি (!needs_mod)
    ফেরত type;

  /* Construct new version with such members replaced.  */
  বৃক্ষ n = build_distinct_type_copy (type);
  বৃক্ষ *fields = &TYPE_FIELDS (n);
  জন্য (বৃক্ষ x = TYPE_FIELDS (type); x; x = DECL_CHAIN (x))
    {
      বৃক্ষ f = copy_গ্রন্থি (x);
      যদি (বৃক্ষ m = ptr_to_tagged_member (x))
	{
	  বৃক্ষ new_গ্রন্থি = make_গ্রন্থি (বৃক্ষ_CODE (m));
	  TYPE_NAME (new_গ্রন্থি) = TYPE_NAME (m);
	  SET_TYPE_STRUCTURAL_EQUALITY (new_গ্রন্থি);
	  new_গ্রন্থি = qualify_type (new_গ্রন্থি, m);
	  বৃক্ষ_TYPE (f) = c_reconstruct_complex_type (বৃক্ষ_TYPE (x),
						      new_গ্রন্থি);
	}
      *fields = f;
      fields = &DECL_CHAIN (f);
    }
  TYPE_CANONICAL (n) = n;
  ফেরত n;
}


/* If NTYPE is a type of a non-variadic function with a prototype
   and OTYPE is a type of a function without a prototype and ATTRS
   contains attribute format, diagnosess and removes it from ATTRS.
   Returns the result of build_type_attribute_variant of NTYPE and
   the (possibly) modified ATTRS.  */

স্থির বৃক্ষ
c_build_functype_attribute_variant (বৃক্ষ ntype, বৃক্ষ otype, বৃক্ষ attrs)
{
  যদি (!prototype_p (otype)
      && prototype_p (ntype)
      && lookup_attribute ("format", attrs))
    {
      warning_at (প্রবেশ_location, OPT_Wattributes,
		  "%qs attribute can only be applied to variadic functions",
		  "format");
      attrs = remove_attribute ("format", attrs);
    }
  ফেরত c_build_type_attribute_variant (ntype, attrs);

}

/* Given a type which could be a typedef name, make sure to return the
   original type.  See set_underlying_type. */
স্থির const_বৃক্ষ
c_type_original (const_বৃক্ষ t)
{
  /* It may even be a typedef of a typedef...
     In the case of compiler-created builtin structs the TYPE_DECL
     may be a dummy, with no DECL_ORIGINAL_TYPE.  Don't fault.  */
  যখন (TYPE_NAME (t)
	 && বৃক্ষ_CODE (TYPE_NAME (t)) == TYPE_DECL
	 && DECL_ORIGINAL_TYPE (TYPE_NAME (t)))
    t = DECL_ORIGINAL_TYPE (TYPE_NAME (t));
  ফেরত t;
}

/* Return the tag for a tagged type.  */
বৃক্ষ
c_type_tag (const_বৃক্ষ t)
{
  gcc_assert (RECORD_OR_UNION_TYPE_P (t) || বৃক্ষ_CODE (t) == ENUMERAL_TYPE);
  const_বৃক্ষ orig = c_type_original (t);
  বৃক্ষ name = TYPE_NAME (orig);
  যদি (!name)
    ফেরত NULL_বৃক্ষ;
  যদি (বৃক্ষ_CODE (name) == TYPE_DECL)
    {
      যদি (!DECL_NAME (name))
	ফেরত NULL_বৃক্ষ;
      name = DECL_NAME (name);
    }
  gcc_checking_assert (বৃক্ষ_CODE (name) == IDENTIFIER_গ্রন্থি);
  ফেরত name;
}

/* Remove qualifiers but not atomic.  For arrays remove qualifiers
   on the element type but also do not remove atomic.  */
স্থির বৃক্ষ
remove_qualifiers (বৃক্ষ t)
{
  যদি (!t || t == error_mark_গ্রন্থি)
    ফেরত t;
  ফেরত TYPE_ATOMIC (strip_array_types (t))
	 ? c_build_qualified_type (TYPE_MAIN_VARIANT (t), TYPE_QUAL_ATOMIC)
	 : TYPE_MAIN_VARIANT (t);
}


/* Helper function for composite_type_internal.  Find a compatible type
   in a (transparent) union U compatible to T.  If found, return the
   type of the corresponding member.  Otherwise, return the union type U.  */
স্থির বৃক্ষ
transparent_union_replacement (বৃক্ষ u, বৃক্ষ t)
{
  যদি (u == error_mark_গ্রন্থি || t == error_mark_গ্রন্থি
      || বৃক্ষ_CODE (u) != UNION_TYPE
      || !(TYPE_TRANSPARENT_AGGR (u) || TYPE_NAME (u) == NULL_বৃক্ষ)
      || comptypes (u, t))
    ফেরত u;

  জন্য (বৃক্ষ memb = TYPE_FIELDS (u); memb; memb = DECL_CHAIN (memb))
    {
      বৃক্ষ m = remove_qualifiers (বৃক্ষ_TYPE (memb));
      যদি (comptypes (m, t))
	{
	  pedwarn (প্রবেশ_location, OPT_Wpedantic,
		    "function types not truly compatible in ISO C");
	  ফেরত m;
	}
    }

  ফেরত u;
}



/* Return the composite type of two compatible types.

   We assume that comptypes has already been done and returned
   nonzero; if that isn't so, this may crash.  In particular, we
   assume that qualifiers match.  */

কাঠামো composite_cache {
  বৃক্ষ t1;
  বৃক্ষ t2;
  বৃক্ষ composite;
  কাঠামো composite_cache* পরবর্তী;
};

বৃক্ষ
composite_type_internal (বৃক্ষ t1, বৃক্ষ t2, বৃক্ষ cond,
			 কাঠামো composite_cache* cache)
{
  গণনা বৃক্ষ_code code1;
  গণনা বৃক্ষ_code code2;
  বৃক্ষ attributes;

  /* Save time if the two types are the same.  */

  যদি (t1 == t2) ফেরত t1;

  /* If one type is nonsense, use the other.  */
  যদি (t1 == error_mark_গ্রন্থি)
    ফেরত t2;
  যদি (t2 == error_mark_গ্রন্থি)
    ফেরত t1;

  code1 = বৃক্ষ_CODE (t1);
  code2 = বৃক্ষ_CODE (t2);

  /* Merge the attributes.  */
  attributes = targetm.merge_type_attributes (t1, t2);

  /* If one is an enumerated type and the other is the compatible
     integer type, the composite type might be either of the two
     (DR#013 question 3).  For consistency, use the enumerated type as
     the composite type.  */

  যদি (code1 == ENUMERAL_TYPE
      && (code2 == INTEGER_TYPE
	  || code2 == BOOLEAN_TYPE))
    ফেরত t1;
  যদি (code2 == ENUMERAL_TYPE
      && (code1 == INTEGER_TYPE
	  || code1 == BOOLEAN_TYPE))
    ফেরত t2;

  gcc_assert (code1 == code2);

  নির্বাচন (code1)
    {
    ক্ষেত্র POINTER_TYPE:
      /* For two pointers, do this recursively on the target type.  */
      {
	gcc_checking_assert (TYPE_QUALS (t1) == TYPE_QUALS (t2));
	বৃক্ষ target = composite_type_internal (বৃক্ষ_TYPE (t1), বৃক্ষ_TYPE (t2),
					       cond, cache);
	বৃক্ষ n = c_build_pointer_type_for_mode (target, TYPE_MODE (t1), মিথ্যা);
	ফেরত c_build_type_attribute_qual_variant (n, attributes,
						    TYPE_QUALS (t2));
      }

    ক্ষেত্র ARRAY_TYPE:
      {
	বৃক্ষ d1 = TYPE_DOMAIN (t1);
	বৃক্ষ d2 = TYPE_DOMAIN (t2);

	/* We should not have any type quals on arrays at all.  */
	gcc_assert (!TYPE_QUALS_NO_ADDR_SPACE (t1)
		    && !TYPE_QUALS_NO_ADDR_SPACE (t2));

	যৌক্তিক d1_zero = zero_দৈর্ঘ্য_array_type_p (t1)
		       || flexible_array_member_type_p (t1);
	যৌক্তিক d2_zero = zero_দৈর্ঘ্য_array_type_p (t2)
		       || flexible_array_member_type_p (t2);

	যৌক্তিক d1_variable = শীর্ষ_array_vla_p (t1);
	যৌক্তিক d2_variable = শীর্ষ_array_vla_p (t2);

	যৌক্তিক use1 = d1 && (d2_variable || !d2 || d2_zero || !d1_variable);
	যৌক্তিক use2 = d2 && (d1_variable || !d1 || d1_zero || !d2_variable);

	/* If the first is an unspecified size pick the other one.  */
	যদি (d2_variable && c_type_unspecified_p (t1))
	  {
	    gcc_assert (use1 && use2);
	    use1 = মিথ্যা;
	  }

	/* If both are VLAs but not unspecified and we are in the
	   conditional operator, we create a conditional to select
	   the size of the active branch.  */
	যৌক্তিক use0 = cond && d1_variable && !c_type_unspecified_p (t1)
			 && d2_variable && !c_type_unspecified_p (t2);

	বৃক্ষ td;
	বৃক্ষ elt = composite_type_internal (বৃক্ষ_TYPE (t1), বৃক্ষ_TYPE (t2),
					    cond, cache);

	যদি (!use0)
	  {
	    /* Save space: see if the result is identical to one of the args.  */
	    যদি (elt == বৃক্ষ_TYPE (t1) && use1)
	      ফেরত c_build_type_attribute_variant (t1, attributes);
	    যদি (elt == বৃক্ষ_TYPE (t2) && use2)
	      ফেরত c_build_type_attribute_variant (t2, attributes);

	    যদি (elt == বৃক্ষ_TYPE (t1) && !TYPE_DOMAIN (t2) && !TYPE_DOMAIN (t1))
	      ফেরত c_build_type_attribute_variant (t1, attributes);
	    যদি (elt == বৃক্ষ_TYPE (t2) && !TYPE_DOMAIN (t2) && !TYPE_DOMAIN (t1))
	      ফেরত c_build_type_attribute_variant (t2, attributes);

	    td = TYPE_DOMAIN (use1 ? t1 : t2);
	  }
	অন্যথা
	  {
	    /* Not used in C.  */
	    gcc_assert (আকার_zero_গ্রন্থি == TYPE_MIN_মান (d1));
	    gcc_assert (আকার_zero_গ্রন্থি == TYPE_MIN_মান (d2));

	    বৃক্ষ d = fold_build3_loc (UNKNOWN_LOCATION, COND_রাশিমালা, sizetype,
				      cond, TYPE_MAX_মান (d1),
				      TYPE_MAX_মান (d2));

	    td = build_সূচক_type (d);
	  }

	/* Merge the element types, and have a size if either arg has
	   one.  We may have qualifiers on the element types.  To set
	   up TYPE_MAIN_VARIANT correctly, we need to form the
	   composite of the unqualified types and add the qualifiers
	   back at the end.  */
	পূর্ণসংখ্যা quals = TYPE_QUALS (strip_array_types (elt));
	বৃক্ষ unqual_elt = c_build_qualified_type (elt, TYPE_UNQUALIFIED);

	যদি ((!d1 || d1_zero) && (!d2 || d2_zero) && (d1 || d2))
	  t1 = c_build_array_type_zero_আকার (unqual_elt);
	অন্যথা
	  t1 = c_build_array_type (unqual_elt, td);

	/* Check that a type which has a varying outermost dimension
	   got marked as having a variable size.  */
	যৌক্তিক varsize = (d1_variable && d2_variable)
		       || (d1_variable && !d2)
		       || (d2_variable && !d1);
	gcc_checking_assert (!varsize || C_TYPE_VARIABLE_আকার (t1));

	t1 = c_build_qualified_type (t1, quals);
	ফেরত c_build_type_attribute_variant (t1, attributes);
      }

    ক্ষেত্র RECORD_TYPE:
    ক্ষেত্র UNION_TYPE:
      যদি (flag_isoc23 && !comptypes_same_p (t1, t2))
	{
	  /* Go to the original type to get the right tag.  */
	  বৃক্ষ tag = c_type_tag (t1);

	  gcc_checking_assert (COMPLETE_TYPE_P (t1) && COMPLETE_TYPE_P (t2));
	  gcc_checking_assert (!tag || comptypes (t1, t2));

	  /* If a composite type for these two types is already under
	     construction, return it.  */

	  জন্য (কাঠামো composite_cache *c = cache; c != ফাঁকা; c = c->পরবর্তী)
	    যদি ((c->t1 == t1 && c->t2 == t2) || (c->t1 == t2 && c->t2 == t1))
	       ফেরত c->composite;

	  /* Otherwise, create a new type node and link it into the cache.  */

	  বৃক্ষ n = make_গ্রন্থি (code1);
	  SET_TYPE_STRUCTURAL_EQUALITY (n);
	  TYPE_NAME (n) = tag;

	  কাঠামো composite_cache cache2 = { t1, t2, n, cache };
	  cache = &cache2;

	  বৃক্ষ f1 = TYPE_FIELDS (t1);
	  বৃক্ষ f2 = TYPE_FIELDS (t2);
	  বৃক্ষ fields = NULL_বৃক্ষ;

	  জন্য (বৃক্ষ a = f1, b = f2; a && b;
	       a = DECL_CHAIN (a), b = DECL_CHAIN (b))
	    {
	      বৃক্ষ ta = বৃক্ষ_TYPE (a);
	      বৃক্ষ tb = বৃক্ষ_TYPE (b);

	      যদি (DECL_C_BIT_FIELD (a))
		{
		  ta = DECL_BIT_FIELD_TYPE (a);
		  tb = DECL_BIT_FIELD_TYPE (b);
		}

	      gcc_assert (DECL_NAME (a) == DECL_NAME (b));
	      gcc_checking_assert (!DECL_NAME (a) || comptypes (ta, tb));

	      বৃক্ষ t = composite_type_internal (ta, tb, cond, cache);
	      বৃক্ষ f = build_decl (প্রবেশ_location, FIELD_DECL, DECL_NAME (a), t);

	      DECL_PACKED (f) = DECL_PACKED (a);
	      SET_DECL_ALIGN (f, DECL_ALIGN (a));
	      DECL_ATTRIBUTES (f) = DECL_ATTRIBUTES (a);
	      C_DECL_VARIABLE_আকার (f) = C_TYPE_VARIABLE_আকার (t);

	      decl_attributes (&f, DECL_ATTRIBUTES (f), 0);

	      finish_decl (f, প্রবেশ_location, ফাঁকা, ফাঁকা, ফাঁকা);

	      যদি (DECL_C_BIT_FIELD (a))
		{
		  /* This will be processed by finish_struct.  */
		  SET_DECL_C_BIT_FIELD (f);
		  DECL_INITIAL (f) = build_int_cst (integer_type_গ্রন্থি,
						    বৃক্ষ_to_uhwi (DECL_আকার (a)));
		  DECL_NONADDRESSABLE_P (f) = সত্য;
		  DECL_PADDING_P (f) = !DECL_NAME (a);
		}

	      DECL_CHAIN (f) = fields;
	      fields = f;
	    }

	  fields = nreverse (fields);

	  /* Setup the struct/union type.  Because we inherit all variably
	     modified components, we can ignore the size expression.  */
	  বৃক্ষ রাশিমালা = NULL_বৃক্ষ;

	  /* Set TYPE_STUB_DECL for debugging symbols.  */
	  TYPE_STUB_DECL (n) = pushdecl (build_decl (প্রবেশ_location, TYPE_DECL,
						     NULL_বৃক্ষ, n));

	  n = finish_struct (প্রবেশ_location, n, fields, attributes, ফাঁকা,
			     &রাশিমালা);

	  ফেরত qualify_type (n, t1);
	}
      /* FALLTHRU */
    ক্ষেত্র ENUMERAL_TYPE:
      যদি (attributes != ফাঁকা)
	{
	  /* Try harder not to create a new aggregate type.  */
	  যদি (attribute_list_equal (TYPE_ATTRIBUTES (t1), attributes))
	    ফেরত t1;
	  যদি (attribute_list_equal (TYPE_ATTRIBUTES (t2), attributes))
	    ফেরত t2;
	}
      ফেরত c_build_type_attribute_variant (t1, attributes);

    ক্ষেত্র FUNCTION_TYPE:
      /* Function types: prefer the one that specified arg types.
	 If both do, merge the arg types.  Also merge the return types.  */
      {
	বৃক্ষ valtype = composite_type_internal (বৃক্ষ_TYPE (t1), বৃক্ষ_TYPE (t2),
						cond, cache);
	বৃক্ষ p1 = TYPE_ARG_TYPES (t1);
	বৃক্ষ p2 = TYPE_ARG_TYPES (t2);

	/* Save space: see if the result is identical to one of the args.  */
	যদি (valtype == বৃক্ষ_TYPE (t1) && !TYPE_ARG_TYPES (t2))
	  ফেরত c_build_functype_attribute_variant (t1, t2, attributes);
	যদি (valtype == বৃক্ষ_TYPE (t2) && !TYPE_ARG_TYPES (t1))
	  ফেরত c_build_functype_attribute_variant (t2, t1, attributes);

	/* Simple way if one arg fails to specify argument types.  */
	যদি (TYPE_ARG_TYPES (t1) == NULL_বৃক্ষ)
	  {
	    t1 = c_build_function_type (valtype, TYPE_ARG_TYPES (t2),
					TYPE_NO_NAMED_ARGS_STDARG_P (t2));
	    t1 = c_build_type_attribute_variant (t1, attributes);
	    ফেরত qualify_type (t1, t2);
	 }
	যদি (TYPE_ARG_TYPES (t2) == NULL_বৃক্ষ)
	  {
	    t1 = c_build_function_type (valtype, TYPE_ARG_TYPES (t1),
					TYPE_NO_NAMED_ARGS_STDARG_P (t1));
	    t1 = c_build_type_attribute_variant (t1, attributes);
	    ফেরত qualify_type (t1, t2);
	  }

	/* If both args specify argument types, we must merge the two
	   lists, argument by argument.  */
	বৃক্ষ newargs = NULL_বৃক্ষ;
	বৃক্ষ *endp = &newargs;

	জন্য (; p1; p1 = বৃক্ষ_CHAIN (p1), p2 = বৃক্ষ_CHAIN (p2))
	  {
	    যদি (p1 == void_list_গ্রন্থি)
	      {
		*endp = void_list_গ্রন্থি;
		বিরতি;
	      }
	    বৃক্ষ mv1 = remove_qualifiers (বৃক্ষ_মান (p1));
	    বৃক্ষ mv2 = remove_qualifiers (বৃক্ষ_মান (p2));

	    gcc_assert (mv1);
	    gcc_assert (mv2);

	    mv1 = transparent_union_replacement (mv1, mv2);
	    mv2 = transparent_union_replacement (mv2, mv1);

	    *endp = বৃক্ষ_cons (NULL_বৃক্ষ,
			       composite_type_internal (mv1, mv2, cond, cache),
			       NULL_বৃক্ষ);

	    endp = &বৃক্ষ_CHAIN (*endp);
	  }

	t1 = c_build_function_type (valtype, newargs);
	t1 = qualify_type (t1, t2);
      }
      /* FALLTHRU */

    পূর্বনির্ধারিত:
      ফেরত c_build_type_attribute_variant (t1, attributes);
    }
}

বৃক্ষ
composite_type_cond (বৃক্ষ t1, বৃক্ষ t2, বৃক্ষ cond)
{
  gcc_checking_assert (comptypes_check_for_composite (t1, t2));

  কাঠামো composite_cache cache = { };
  বৃক্ষ n = composite_type_internal (t1, t2, cond, &cache);

  gcc_checking_assert (comptypes_check_for_composite (n, t1));
  gcc_checking_assert (comptypes_check_for_composite (n, t2));
  ফেরত n;
}


বৃক্ষ
composite_type (বৃক্ষ t1, বৃক্ষ t2)
{
  ফেরত composite_type_cond (t1, t2, NULL_বৃক্ষ);
}

/* Return the type of a conditional expression between pointers to
   possibly differently qualified versions of compatible types.

   We assume that comp_target_types has already been done and returned
   true; if that isn't so, this may crash.  */

স্থির বৃক্ষ
common_pointer_type (বৃক্ষ t1, বৃক্ষ t2, বৃক্ষ cond)
{
  বৃক্ষ attributes;
  unsigned target_quals;
  addr_space_t as1, as2, as_common;
  পূর্ণসংখ্যা quals1, quals2;

  /* Save time if the two types are the same.  */

  যদি (t1 == t2) ফেরত t1;

  /* If one type is nonsense, use the other.  */
  যদি (t1 == error_mark_গ্রন্থি)
    ফেরত t2;
  যদি (t2 == error_mark_গ্রন্থি)
    ফেরত t1;

  gcc_assert (বৃক্ষ_CODE (t1) == POINTER_TYPE
	      && বৃক্ষ_CODE (t2) == POINTER_TYPE);

  /* Merge the attributes.  */
  attributes = targetm.merge_type_attributes (t1, t2);

  /* Find the composite type of the target types, and combine the
     qualifiers of the two types' targets.  */
  বৃক্ষ pointed_to_1 = বৃক্ষ_TYPE (t1);
  বৃক্ষ pointed_to_2 = বৃক্ষ_TYPE (t2);
  বৃক্ষ target = composite_type_cond (TYPE_MAIN_VARIANT (pointed_to_1),
				     TYPE_MAIN_VARIANT (pointed_to_2), cond);

  /* Strip array types to get correct qualifier for pointers to arrays */
  quals1 = TYPE_QUALS_NO_ADDR_SPACE (strip_array_types (pointed_to_1));
  quals2 = TYPE_QUALS_NO_ADDR_SPACE (strip_array_types (pointed_to_2));

  /* For function types do not merge const qualifiers, but drop them
     if used inconsistently.  The middle-end uses these to mark const
     and noreturn functions.  */
  যদি (বৃক্ষ_CODE (pointed_to_1) == FUNCTION_TYPE)
    target_quals = (quals1 & quals2);
  অন্যথা
    target_quals = (quals1 | quals2);

  /* If the two named address spaces are different, determine the common
     superset address space.  This is guaranteed to exist due to the
     assumption that comp_target_type returned true.  */
  as1 = TYPE_ADDR_SPACE (pointed_to_1);
  as2 = TYPE_ADDR_SPACE (pointed_to_2);
  যদি (!addr_space_superset (as1, as2, &as_common))
    gcc_unreachable ();

  target_quals |= ENCODE_QUAL_ADDR_SPACE (as_common);

  t1 = c_build_pointer_type (c_build_qualified_type (target, target_quals));
  ফেরত c_build_type_attribute_variant (t1, attributes);
}

/* Return the common type for two arithmetic types under the usual
   arithmetic conversions.  The default conversions have already been
   applied, and enumerated types converted to their compatible integer
   types.  The resulting type is unqualified and has no attributes.

   This is the type for the result of most arithmetic operations
   if the operands have the given two types.  */

স্থির বৃক্ষ
c_common_type (বৃক্ষ t1, বৃক্ষ t2)
{
  গণনা বৃক্ষ_code code1;
  গণনা বৃক্ষ_code code2;

  /* If one type is nonsense, use the other.  */
  যদি (t1 == error_mark_গ্রন্থি)
    ফেরত t2;
  যদি (t2 == error_mark_গ্রন্থি)
    ফেরত t1;

  যদি (TYPE_QUALS (t1) != TYPE_UNQUALIFIED)
    t1 = TYPE_MAIN_VARIANT (t1);

  যদি (TYPE_QUALS (t2) != TYPE_UNQUALIFIED)
    t2 = TYPE_MAIN_VARIANT (t2);

  যদি (TYPE_ATTRIBUTES (t1) != NULL_বৃক্ষ)
    {
      বৃক্ষ attrs = affects_type_identity_attributes (TYPE_ATTRIBUTES (t1));
      t1 = c_build_type_attribute_variant (t1, attrs);
    }

  যদি (TYPE_ATTRIBUTES (t2) != NULL_বৃক্ষ)
    {
      বৃক্ষ attrs = affects_type_identity_attributes (TYPE_ATTRIBUTES (t2));
      t2 = c_build_type_attribute_variant (t2, attrs);
    }

  /* Save time if the two types are the same.  */

  যদি (t1 == t2) ফেরত t1;

  code1 = বৃক্ষ_CODE (t1);
  code2 = বৃক্ষ_CODE (t2);

  gcc_assert (code1 == VECTOR_TYPE || code1 == COMPLEX_TYPE
	      || code1 == FIXED_POINT_TYPE || code1 == REAL_TYPE
	      || code1 == INTEGER_TYPE || code1 == BITINT_TYPE);
  gcc_assert (code2 == VECTOR_TYPE || code2 == COMPLEX_TYPE
	      || code2 == FIXED_POINT_TYPE || code2 == REAL_TYPE
	      || code2 == INTEGER_TYPE || code2 == BITINT_TYPE);

  /* When one operand is a decimal float type, the other operand cannot be
     a generic float type or a complex type.  We also disallow vector types
     here.  */
  যদি ((DECIMAL_FLOAT_TYPE_P (t1) || DECIMAL_FLOAT_TYPE_P (t2))
      && !(DECIMAL_FLOAT_TYPE_P (t1) && DECIMAL_FLOAT_TYPE_P (t2)))
    {
      যদি (code1 == VECTOR_TYPE || code2 == VECTOR_TYPE)
	{
	  error ("cannot mix operands of decimal floating and vector types");
	  ফেরত error_mark_গ্রন্থি;
	}
      যদি (code1 == COMPLEX_TYPE || code2 == COMPLEX_TYPE)
	{
	  error ("cannot mix operands of decimal floating and complex types");
	  ফেরত error_mark_গ্রন্থি;
	}
      যদি (code1 == REAL_TYPE && code2 == REAL_TYPE)
	{
	  error ("cannot mix operands of decimal floating "
		 "and other floating types");
	  ফেরত error_mark_গ্রন্থি;
	}
    }

  /* If one type is a vector type, return that type.  (How the usual
     arithmetic conversions apply to the vector types extension is not
     precisely specified.)  */
  যদি (code1 == VECTOR_TYPE)
    ফেরত t1;

  যদি (code2 == VECTOR_TYPE)
    ফেরত t2;

  /* If one type is complex, form the common type of the non-complex
     components, then make that complex.  Use T1 or T2 if it is the
     required type.  */
  যদি (code1 == COMPLEX_TYPE || code2 == COMPLEX_TYPE)
    {
      বৃক্ষ subtype1 = code1 == COMPLEX_TYPE ? বৃক্ষ_TYPE (t1) : t1;
      বৃক্ষ subtype2 = code2 == COMPLEX_TYPE ? বৃক্ষ_TYPE (t2) : t2;
      বৃক্ষ subtype = c_common_type (subtype1, subtype2);

      যদি (code1 == COMPLEX_TYPE && বৃক্ষ_TYPE (t1) == subtype)
	ফেরত t1;
      অন্যথা যদি (code2 == COMPLEX_TYPE && বৃক্ষ_TYPE (t2) == subtype)
	ফেরত t2;
      অন্যথা যদি (বৃক্ষ_CODE (subtype) == BITINT_TYPE)
	{
	  sorry ("%<_Complex _BitInt(%d)%> unsupported",
		 TYPE_PRECISION (subtype));
	  ফেরত code1 == COMPLEX_TYPE ? t1 : t2;
	}
      অন্যথা
	ফেরত build_complex_type (subtype);
    }

  /* If only one is real, use it as the result.  */

  যদি (code1 == REAL_TYPE && code2 != REAL_TYPE)
    ফেরত t1;

  যদি (code2 == REAL_TYPE && code1 != REAL_TYPE)
    ফেরত t2;

  /* If both are real and either are decimal floating point types, use
     the decimal floating point type with the greater precision. */

  যদি (code1 == REAL_TYPE && code2 == REAL_TYPE)
    {
      যদি (TYPE_MAIN_VARIANT (t1) == dfloat128_type_গ্রন্থি
	  || TYPE_MAIN_VARIANT (t2) == dfloat128_type_গ্রন্থি)
	ফেরত dfloat128_type_গ্রন্থি;
      /* And prefer _Decimal128 over _Decimal64x which has in GCC's
	 implementation the same mode.  */
      অন্যথা যদি (TYPE_MAIN_VARIANT (t1) == dfloat64x_type_গ্রন্থি
	       || TYPE_MAIN_VARIANT (t2) == dfloat64x_type_গ্রন্থি)
	ফেরত dfloat64x_type_গ্রন্থি;
      অন্যথা যদি (TYPE_MAIN_VARIANT (t1) == dfloat64_type_গ্রন্থি
	       || TYPE_MAIN_VARIANT (t2) == dfloat64_type_গ্রন্থি)
	ফেরত dfloat64_type_গ্রন্থি;
      অন্যথা যদি (TYPE_MAIN_VARIANT (t1) == dfloat32_type_গ্রন্থি
	       || TYPE_MAIN_VARIANT (t2) == dfloat32_type_গ্রন্থি)
	ফেরত dfloat32_type_গ্রন্থি;
    }

  /* Deal with fixed-point types.  */
  যদি (code1 == FIXED_POINT_TYPE || code2 == FIXED_POINT_TYPE)
    {
      unsigned পূর্ণসংখ্যা unsignedp = 0, satp = 0;
      scalar_mode m1, m2;
      unsigned পূর্ণসংখ্যা fbit1, ibit1, fbit2, ibit2, max_fbit, max_ibit;

      m1 = SCALAR_TYPE_MODE (t1);
      m2 = SCALAR_TYPE_MODE (t2);

      /* If one input type is saturating, the result type is saturating.  */
      যদি (TYPE_SATURATING (t1) || TYPE_SATURATING (t2))
	satp = 1;

      /* If both fixed-point types are unsigned, the result type is unsigned.
	 When mixing fixed-point and integer types, follow the sign of the
	 fixed-point type.
	 Otherwise, the result type is signed.  */
      যদি ((TYPE_UNSIGNED (t1) && TYPE_UNSIGNED (t2)
	   && code1 == FIXED_POINT_TYPE && code2 == FIXED_POINT_TYPE)
	  || (code1 == FIXED_POINT_TYPE && code2 != FIXED_POINT_TYPE
	      && TYPE_UNSIGNED (t1))
	  || (code1 != FIXED_POINT_TYPE && code2 == FIXED_POINT_TYPE
	      && TYPE_UNSIGNED (t2)))
	unsignedp = 1;

      /* The result type is signed.  */
      যদি (unsignedp == 0)
	{
	  /* If the input type is unsigned, we need to convert to the
	     signed type.  */
	  যদি (code1 == FIXED_POINT_TYPE && TYPE_UNSIGNED (t1))
	    {
	      গণনা mode_class mclass = (গণনা mode_class) 0;
	      যদি (GET_MODE_CLASS (m1) == MODE_UFRACT)
		mclass = MODE_FRACT;
	      অন্যথা যদি (GET_MODE_CLASS (m1) == MODE_UACCUM)
		mclass = MODE_ACCUM;
	      অন্যথা
		gcc_unreachable ();
	      m1 = as_a <scalar_mode>
		(mode_for_আকার (GET_MODE_PRECISION (m1), mclass, 0));
	    }
	  যদি (code2 == FIXED_POINT_TYPE && TYPE_UNSIGNED (t2))
	    {
	      গণনা mode_class mclass = (গণনা mode_class) 0;
	      যদি (GET_MODE_CLASS (m2) == MODE_UFRACT)
		mclass = MODE_FRACT;
	      অন্যথা যদি (GET_MODE_CLASS (m2) == MODE_UACCUM)
		mclass = MODE_ACCUM;
	      অন্যথা
		gcc_unreachable ();
	      m2 = as_a <scalar_mode>
		(mode_for_আকার (GET_MODE_PRECISION (m2), mclass, 0));
	    }
	}

      যদি (code1 == FIXED_POINT_TYPE)
	{
	  fbit1 = GET_MODE_FBIT (m1);
	  ibit1 = GET_MODE_IBIT (m1);
	}
      অন্যথা
	{
	  fbit1 = 0;
	  /* Signed integers need to subtract one sign bit.  */
	  ibit1 = TYPE_PRECISION (t1) - (!TYPE_UNSIGNED (t1));
	}

      যদি (code2 == FIXED_POINT_TYPE)
	{
	  fbit2 = GET_MODE_FBIT (m2);
	  ibit2 = GET_MODE_IBIT (m2);
	}
      অন্যথা
	{
	  fbit2 = 0;
	  /* Signed integers need to subtract one sign bit.  */
	  ibit2 = TYPE_PRECISION (t2) - (!TYPE_UNSIGNED (t2));
	}

      max_ibit = ibit1 >= ibit2 ?  ibit1 : ibit2;
      max_fbit = fbit1 >= fbit2 ?  fbit1 : fbit2;
      ফেরত c_common_fixed_point_type_for_আকার (max_ibit, max_fbit, unsignedp,
						 satp);
    }

  /* Both real or both integers; use the one with greater precision.  */

  যদি (TYPE_PRECISION (t1) > TYPE_PRECISION (t2))
    ফেরত t1;
  অন্যথা যদি (TYPE_PRECISION (t2) > TYPE_PRECISION (t1))
    ফেরত t2;

  /* Same precision.  Prefer long longs to longs to ints when the
     same precision, following the C99 rules on integer type rank
     (which are equivalent to the C90 rules for C90 types).  */

  যদি (TYPE_MAIN_VARIANT (t1) == long_long_unsigned_type_গ্রন্থি
      || TYPE_MAIN_VARIANT (t2) == long_long_unsigned_type_গ্রন্থি)
    ফেরত long_long_unsigned_type_গ্রন্থি;

  যদি (TYPE_MAIN_VARIANT (t1) == long_long_integer_type_গ্রন্থি
      || TYPE_MAIN_VARIANT (t2) == long_long_integer_type_গ্রন্থি)
    {
      যদি (TYPE_UNSIGNED (t1) || TYPE_UNSIGNED (t2))
	ফেরত long_long_unsigned_type_গ্রন্থি;
      অন্যথা
	ফেরত long_long_integer_type_গ্রন্থি;
    }

  যদি (TYPE_MAIN_VARIANT (t1) == long_unsigned_type_গ্রন্থি
      || TYPE_MAIN_VARIANT (t2) == long_unsigned_type_গ্রন্থি)
    ফেরত long_unsigned_type_গ্রন্থি;

  যদি (TYPE_MAIN_VARIANT (t1) == long_integer_type_গ্রন্থি
      || TYPE_MAIN_VARIANT (t2) == long_integer_type_গ্রন্থি)
    {
      /* But preserve unsignedness from the other type,
	 since long cannot hold all the values of an unsigned int.  */
      যদি (TYPE_UNSIGNED (t1) || TYPE_UNSIGNED (t2))
	ফেরত long_unsigned_type_গ্রন্থি;
      অন্যথা
	ফেরত long_integer_type_গ্রন্থি;
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
  বৃক্ষ mv1 = TYPE_MAIN_VARIANT (t1);
  বৃক্ষ mv2 = TYPE_MAIN_VARIANT (t2);

  জন্য (পূর্ণসংখ্যা i = অঙ্ক_FLOATN_TYPES - 1; i >= 0; i--)
    যদি (mv1 == FLOATN_TYPE_গ্রন্থি (i) || mv2 == FLOATN_TYPE_গ্রন্থি (i))
      ফেরত FLOATN_TYPE_গ্রন্থি (i);

  /* Likewise, prefer long double to double even if same size.  */
  যদি (mv1 == long_double_type_গ্রন্থি || mv2 == long_double_type_গ্রন্থি)
    ফেরত long_double_type_গ্রন্থি;

  /* Likewise, prefer double to float even if same size.
     We got a couple of embedded targets with 32 bit doubles, and the
     pdp11 might have 64 bit floats.  */
  যদি (mv1 == double_type_গ্রন্থি || mv2 == double_type_গ্রন্থি)
    ফেরত double_type_গ্রন্থি;

  যদি (mv1 == float_type_গ্রন্থি || mv2 == float_type_গ্রন্থি)
    ফেরত float_type_গ্রন্থি;

  জন্য (পূর্ণসংখ্যা i = অঙ্ক_FLOATNX_TYPES - 1; i >= 0; i--)
    যদি (mv1 == FLOATNX_TYPE_গ্রন্থি (i) || mv2 == FLOATNX_TYPE_গ্রন্থি (i))
      ফেরত FLOATNX_TYPE_গ্রন্থি (i);

  যদি ((code1 == BITINT_TYPE || code2 == BITINT_TYPE) && code1 != code2)
    {
      /* Prefer any other integral types over bit-precise integer types.  */
      যদি (TYPE_UNSIGNED (t1) == TYPE_UNSIGNED (t2))
	ফেরত code1 == BITINT_TYPE ? t2 : t1;
      /* If BITINT_TYPE is unsigned and the other type is signed
	 non-BITINT_TYPE with the same precision, the latter has higher rank.
	 In that case:
	 Otherwise, both operands are converted to the unsigned integer type
	 corresponding to the type of the operand with signed integer type.  */
      যদি (TYPE_UNSIGNED (code1 == BITINT_TYPE ? t1 : t2))
	ফেরত c_common_unsigned_type (code1 == BITINT_TYPE ? t2 : t1);
    }

  /* Otherwise prefer the unsigned one.  */

  যদি (TYPE_UNSIGNED (t1))
    ফেরত t1;
  অন্যথা
    ফেরত t2;
}

/* Wrapper around c_common_type that is used by c-common.cc and other
   front end optimizations that remove promotions.  ENUMERAL_TYPEs
   are allowed here and are converted to their compatible integer types.
   BOOLEAN_TYPEs are allowed here and return either boolean_type_node or
   preferably a non-Boolean type as the common type.  */
বৃক্ষ
common_type (বৃক্ষ t1, বৃক্ষ t2)
{
  যদি (বৃক্ষ_CODE (t1) == ENUMERAL_TYPE)
    t1 = ENUM_UNDERLYING_TYPE (t1);
  যদি (বৃক্ষ_CODE (t2) == ENUMERAL_TYPE)
    t2 = ENUM_UNDERLYING_TYPE (t2);

  /* If both types are BOOLEAN_TYPE, then return boolean_type_node.  */
  যদি (বৃক্ষ_CODE (t1) == BOOLEAN_TYPE
      && বৃক্ষ_CODE (t2) == BOOLEAN_TYPE)
    ফেরত boolean_type_গ্রন্থি;

  /* If either type is BOOLEAN_TYPE, then return the other.  */
  যদি (বৃক্ষ_CODE (t1) == BOOLEAN_TYPE)
    ফেরত t2;
  যদি (বৃক্ষ_CODE (t2) == BOOLEAN_TYPE)
    ফেরত t1;

  ফেরত c_common_type (t1, t2);
}



/* Helper function for comptypes.  For two compatible types, return 1
   if they pass consistency checks.  In particular we test that
   TYPE_CANONICAL is set correctly, i.e. the two types can alias.  */

স্থির যৌক্তিক
comptypes_verify (বৃক্ষ type1, বৃক্ষ type2)
{
  যদি (type1 == type2 || !type1 || !type2
      || বৃক্ষ_CODE (type1) == ERROR_MARK || বৃক্ষ_CODE (type2) == ERROR_MARK)
    ফেরত সত্য;

  gcc_checking_assert (c_verify_type (type1));
  gcc_checking_assert (c_verify_type (type2));

  যদি (TYPE_CANONICAL (type1) != TYPE_CANONICAL (type2)
      && !TYPE_STRUCTURAL_EQUALITY_P (type1)
      && !TYPE_STRUCTURAL_EQUALITY_P (type2))
    {
      /* FIXME: check other types. */
      যদি (RECORD_OR_UNION_TYPE_P (type1)
	  || বৃক্ষ_CODE (type1) == ENUMERAL_TYPE
	  || বৃক্ষ_CODE (type2) == ENUMERAL_TYPE)
	ফেরত মিথ্যা;
    }
  ফেরত সত্য;
}

কাঠামো comptypes_তথ্য {

  /* output */
  যৌক্তিক enum_and_int_p;
  যৌক্তিক different_types_p;
  যৌক্তিক warning_needed;

  /* context */
  যৌক্তিক anon_field;
  যৌক্তিক pointedto;

  /* configuration */
  যৌক্তিক equiv;
  যৌক্তিক ignore_promoting_args;

  ধ্রুবক কাঠামো tagged_tu_seen_cache* cache;
};


/* Helper function for composite_type.  This function ignores when the
   function type of an old-style declaration is incompatible with a type
   of a declaration with prototype because some are arguments are not
   self-promoting.  This is ignored only for function types but not
   ignored in a nested context.  */

স্থির যৌক্তিক
comptypes_check_for_composite (বৃক্ষ t1, বৃক্ষ t2)
{
  কাঠামো comptypes_তথ্য তথ্য = { };
  তথ্য.ignore_promoting_args = FUNCTION_TYPE == বৃক্ষ_CODE (t1);
  ফেরত comptypes_internal (t1, t2, &তথ্য);
}


/* C implementation of compatible_types_for_indirection_note_p.  */

যৌক্তিক
compatible_types_for_indirection_note_p (বৃক্ষ type1, বৃক্ষ type2)
{
  ফেরত comptypes (type1, type2);
}

/* Return true if TYPE1 and TYPE2 are compatible types for assignment
   or various other operations.  */

যৌক্তিক
comptypes (বৃক্ষ type1, বৃক্ষ type2)
{
  কাঠামো comptypes_তথ্য তথ্য = { };
  যৌক্তিক ret = comptypes_internal (type1, type2, &তথ্য);

  gcc_checking_assert (!ret || comptypes_verify (type1, type2));

  ফেরত ret;
}


/* Like comptypes, but it returns non-zero only for identical
   types.  */

যৌক্তিক
comptypes_same_p (বৃক্ষ type1, বৃক্ষ type2)
{
  কাঠামো comptypes_তথ্য তথ্য = { };
  যৌক্তিক ret = comptypes_internal (type1, type2, &তথ্য);

  gcc_checking_assert (!ret || comptypes_verify (type1, type2));

  যদি (তথ্য.different_types_p)
    ফেরত মিথ্যা;

  ফেরত ret;
}


/* Like comptypes, but if it returns true because enum and int are
   compatible, it sets *ENUM_AND_INT_P to true.  */

যৌক্তিক
comptypes_check_enum_int (বৃক্ষ type1, বৃক্ষ type2, যৌক্তিক *enum_and_int_p)
{
  কাঠামো comptypes_তথ্য তথ্য = { };
  যৌক্তিক ret = comptypes_internal (type1, type2, &তথ্য);
  *enum_and_int_p = তথ্য.enum_and_int_p;

  gcc_checking_assert (!ret || comptypes_verify (type1, type2));

  ফেরত ret;
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

যৌক্তিক
comptypes_equiv_p (বৃক্ষ type1, বৃক্ষ type2)
{
  কাঠামো comptypes_তথ্য তথ্য = { };
  তথ্য.equiv = সত্য;
  যৌক্তিক ret = comptypes_internal (type1, type2, &তথ্য);

  /* check that different equivance classes are assigned only
     to types that are not compatible.  */
  gcc_checking_assert (ret || !comptypes (type1, type2));

  ফেরত ret;
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

স্থির যৌক্তিক
comptypes_internal (const_বৃক্ষ type1, const_বৃক্ষ type2,
		    কাঠামো comptypes_তথ্য *তথ্য)
{
  const_বৃক্ষ t1 = type1;
  const_বৃক্ষ t2 = type2;

  /* Suppress errors caused by previously reported errors.  */

  যদি (t1 == t2 || !t1 || !t2
      || বৃক্ষ_CODE (t1) == ERROR_MARK || বৃক্ষ_CODE (t2) == ERROR_MARK)
    ফেরত সত্য;

  /* Qualifiers must match. C99 6.7.3p9 */

  যদি (TYPE_QUALS (t1) != TYPE_QUALS (t2))
    ফেরত মিথ্যা;

  /* Enumerated types are compatible with integer types, but this is
     not transitive: two enumerated types in the same translation unit
     are compatible with each other only if they are the same type.  */

  যদি (বৃক্ষ_CODE (t1) == ENUMERAL_TYPE
      && COMPLETE_TYPE_P (t1)
      && বৃক্ষ_CODE (t2) != ENUMERAL_TYPE)
    {
      t1 = ENUM_UNDERLYING_TYPE (t1);
      যদি (বৃক্ষ_CODE (t2) != VOID_TYPE)
	{
	  তথ্য->enum_and_int_p = সত্য;
	  তথ্য->different_types_p = সত্য;
	}
    }
  অন্যথা যদি (বৃক্ষ_CODE (t2) == ENUMERAL_TYPE
	   && COMPLETE_TYPE_P (t2)
	   && বৃক্ষ_CODE (t1) != ENUMERAL_TYPE)
    {
      t2 = ENUM_UNDERLYING_TYPE (t2);
      যদি (বৃক্ষ_CODE (t1) != VOID_TYPE)
	{
	  তথ্য->enum_and_int_p = সত্য;
	  তথ্য->different_types_p = সত্য;
	}
    }

  যদি (t1 == t2)
    ফেরত সত্য;

  /* Different classes of types can't be compatible.  */

  যদি (বৃক্ষ_CODE (t1) != বৃক্ষ_CODE (t2))
    ফেরত মিথ্যা;

  /* Allow for two different type nodes which have essentially the same
     definition.  Note that we already checked for equality of the type
     qualifiers (just above).  */

  যদি (বৃক্ষ_CODE (t1) != ARRAY_TYPE
      && TYPE_MAIN_VARIANT (t1) == TYPE_MAIN_VARIANT (t2))
    ফেরত সত্য;

  পূর্ণসংখ্যা attrval;

  /* 1 if no need for warning yet, 2 if warning cause has been seen.  */
  যদি (!(attrval = comp_type_attributes (t1, t2)))
    ফেরত মিথ্যা;

  যদি (2 == attrval)
    তথ্য->warning_needed = সত্য;

  নির্বাচন (বৃক্ষ_CODE (t1))
    {
    ক্ষেত্র INTEGER_TYPE:
    ক্ষেত্র FIXED_POINT_TYPE:
    ক্ষেত্র REAL_TYPE:
    ক্ষেত্র BITINT_TYPE:
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
      ফেরত TYPE_CANONICAL (t1) == TYPE_CANONICAL (t2);

    ক্ষেত্র POINTER_TYPE:
      /* Do not remove mode information.  */
      যদি (TYPE_MODE (t1) != TYPE_MODE (t2))
	ফেরত মিথ্যা;
      তথ্য->pointedto = সত্য;
      ফেরত comptypes_internal (বৃক্ষ_TYPE (t1), বৃক্ষ_TYPE (t2), তথ্য);

    ক্ষেত্র FUNCTION_TYPE:
      ফেরত function_types_compatible_p (t1, t2, তথ্য);

    ক্ষেত্র ARRAY_TYPE:
      {
	বৃক্ষ d1 = TYPE_DOMAIN (t1);
	বৃক্ষ d2 = TYPE_DOMAIN (t2);

	/* Target types must match incl. qualifiers.  */
	যদি (!comptypes_internal (বৃক্ষ_TYPE (t1), বৃক্ষ_TYPE (t2), তথ্য))
	  ফেরত মিথ্যা;

	যদি ((d1 == NULL_বৃক্ষ) != (d2 == NULL_বৃক্ষ))
	  তথ্য->different_types_p = সত্য;
	/* Ignore size mismatches when forming equivalence classes.  */
	যদি (তথ্য->equiv)
	  ফেরত সত্য;
	/* Sizes must match unless one is missing or variable.  */
	যদি (d1 == NULL_বৃক্ষ || d2 == NULL_বৃক্ষ || d1 == d2)
	  ফেরত সত্য;

	যৌক্তিক d1_variable = শীর্ষ_array_vla_p (t1);
	যৌক্তিক d2_variable = শীর্ষ_array_vla_p (t2);

	যদি (d1_variable != d2_variable)
	  তথ্য->different_types_p = সত্য;
	যদি (d1_variable || d2_variable)
	  ফেরত সত্য;

	যৌক্তিক d1_zero = zero_দৈর্ঘ্য_array_type_p (t1)
		       || flexible_array_member_type_p (t1);

	যৌক্তিক d2_zero = zero_দৈর্ঘ্য_array_type_p (t2)
		       || flexible_array_member_type_p (t2);

	যদি (d1_zero && d2_zero)
	  ফেরত সত্য;
	যদি (d1_zero || d2_zero)
	  ফেরত মিথ্যা;

	যদি (!বৃক্ষ_int_cst_equal (TYPE_MIN_মান (d1), TYPE_MIN_মান (d2))
	    || !বৃক্ষ_int_cst_equal (TYPE_MAX_মান (d1), TYPE_MAX_মান (d2)))
	  ফেরত মিথ্যা;

	ফেরত সত্য;
      }

    ক্ষেত্র ENUMERAL_TYPE:
    ক্ষেত্র RECORD_TYPE:
    ক্ষেত্র UNION_TYPE:

      যদি (!flag_isoc23)
	ফেরত মিথ্যা;

      ফেরত tagged_types_tu_compatible_p (t1, t2, তথ্য);

    ক্ষেত্র VECTOR_TYPE:
      ফেরত known_eq (TYPE_VECTOR_SUBPARTS (t1), TYPE_VECTOR_SUBPARTS (t2))
	     && comptypes_internal (বৃক্ষ_TYPE (t1), বৃক্ষ_TYPE (t2), তথ্য);

    পূর্বনির্ধারিত:
      ফেরত মিথ্যা;
    }
  gcc_unreachable ();
}

/* Return true if TTL and TTR are pointers to types that are equivalent, ignoring
   their qualifiers, except for named address spaces.  If the pointers point to
   different named addresses, then we must determine if one address space is a
   subset of the other.  */

স্থির যৌক্তিক
comp_target_types (location_t location, বৃক্ষ ttl, বৃক্ষ ttr)
{
  বৃক্ষ mvl = বৃক্ষ_TYPE (ttl);
  বৃক্ষ mvr = বৃক্ষ_TYPE (ttr);
  addr_space_t asl = TYPE_ADDR_SPACE (mvl);
  addr_space_t asr = TYPE_ADDR_SPACE (mvr);
  addr_space_t as_common;

  /* Fail if pointers point to incompatible address spaces.  */
  যদি (!addr_space_superset (asl, asr, &as_common))
    ফেরত 0;

  /* Qualifiers on element types of array types that are
     pointer targets are also removed.  */
  কাঠামো comptypes_তথ্য তথ্য = { };
  যদি (!comptypes_internal (remove_qualifiers (mvl),
			   remove_qualifiers (mvr), &তথ্য))
    ফেরত মিথ্যা;

  /* For pedantic use comptypes on arrays before removing
     qualifiers on the element type. */
  যদি (বৃক্ষ_CODE (mvl) == ARRAY_TYPE
      && বৃক্ষ_CODE (mvr) == ARRAY_TYPE
      && !comptypes (mvl, mvr))
    pedwarn_c11 (location, OPT_Wpedantic, "invalid use of pointers to arrays "
					  "with different qualifiers in ISO C "
					  "before C23");

  যদি (তথ্য.warning_needed)
    pedwarn (location, OPT_Wpedantic, "types are not quite compatible");

  যদি (তথ্য.enum_and_int_p && warn_cxx_compat)
    warning_at (location, OPT_Wc___compat,
		"pointer target types incompatible in C++");

  ফেরত সত্য;
}

/* Subroutines of `comptypes'.  */

/* Return true if two 'struct', 'union', or 'enum' types T1 and T2 are
   compatible.  The two types are not the same (which has been
   checked earlier in comptypes_internal).  */

স্থির যৌক্তিক
tagged_types_tu_compatible_p (const_বৃক্ষ t1, const_বৃক্ষ t2,
			      কাঠামো comptypes_তথ্য *তথ্য)
{
  বৃক্ষ s1, s2;

  যদি (c_type_tag (t1) != c_type_tag (t2))
    ফেরত মিথ্যা;

  /* When forming equivalence classes for TYPE_CANONICAL in C23, we treat
     structs with the same tag as equivalent, but only when they are targets
     of pointers inside other structs.  */
  যদি (তথ্য->equiv && তথ্য->pointedto && NULL_বৃক্ষ != c_type_tag (t1))
    ফেরত সত্য;

  /* Different types without tag are incompatible except as an anonymous
     field or when forming equivalence classes for TYPE_CANONICAL.  */
  যদি (!তথ্য->anon_field && !তথ্য->equiv && NULL_বৃক্ষ == c_type_tag (t1))
    ফেরত মিথ্যা;

  যদি (!তথ্য->anon_field && TYPE_STUB_DECL (t1) != TYPE_STUB_DECL (t2))
    তথ্য->different_types_p = সত্য;

  /* Incomplete types are incompatible inside a TU.  */
  যদি (TYPE_আকার (t1) == ফাঁকা || TYPE_আকার (t2) == ফাঁকা)
    ফেরত মিথ্যা;

  যদি (ENUMERAL_TYPE != বৃক্ষ_CODE (t1)
      && (TYPE_REVERSE_STORAGE_ORDER (t1)
	  != TYPE_REVERSE_STORAGE_ORDER (t2)))
    ফেরত মিথ্যা;

  যদি (TYPE_USER_ALIGN (t1) != TYPE_USER_ALIGN (t2))
    তথ্য->different_types_p = সত্য;

  /* For types already being looked at in some active
     invocation of this function, assume compatibility.
     The cache is built as a linked list on the stack
     with the head of the list passed downwards.  */
  জন্য (ধ্রুবক কাঠামো tagged_tu_seen_cache *t = তথ্য->cache;
       t != ফাঁকা; t = t->পরবর্তী)
    যদি (t->t1 == t1 && t->t2 == t2)
      ফেরত সত্য;

  ধ্রুবক কাঠামো tagged_tu_seen_cache entry = { তথ্য->cache, t1, t2 };

  নির্বাচন (বৃক্ষ_CODE (t1))
    {
    ক্ষেত্র ENUMERAL_TYPE:
      {
	যদি (!comptypes (ENUM_UNDERLYING_TYPE (t1), ENUM_UNDERLYING_TYPE (t2)))
	  ফেরত মিথ্যা;

	/* Speed up the case where the type values are in the same order.  */
	বৃক্ষ tv1 = TYPE_মানসমূহ (t1);
	বৃক্ষ tv2 = TYPE_মানসমূহ (t2);

	যদি (tv1 == tv2)
	  ফেরত সত্য;

	জন্য (;tv1 && tv2; tv1 = বৃক্ষ_CHAIN (tv1), tv2 = বৃক্ষ_CHAIN (tv2))
	  {
	    যদি (বৃক্ষ_PURPOSE (tv1) != বৃক্ষ_PURPOSE (tv2))
	      বিরতি;

	    যদি (simple_cst_equal (DECL_INITIAL (বৃক্ষ_মান (tv1)),
				  DECL_INITIAL (বৃক্ষ_মান (tv2))) != 1)
	      বিরতি;
	  }

	যদি (tv1 == NULL_বৃক্ষ && tv2 == NULL_বৃক্ষ)
	  ফেরত সত্য;

	যদি (tv1 == NULL_বৃক্ষ || tv2 == NULL_বৃক্ষ)
	  ফেরত মিথ্যা;

	যদি (list_দৈর্ঘ্য (TYPE_মানসমূহ (t1)) != list_দৈর্ঘ্য (TYPE_মানসমূহ (t2)))
	  ফেরত মিথ্যা;

	জন্য (s1 = TYPE_মানসমূহ (t1); s1; s1 = বৃক্ষ_CHAIN (s1))
	  {
	    s2 = purpose_member (বৃক্ষ_PURPOSE (s1), TYPE_মানসমূহ (t2));

	    যদি (s2 == ফাঁকা
		|| simple_cst_equal (DECL_INITIAL (বৃক্ষ_মান (s1)),
				     DECL_INITIAL (বৃক্ষ_মান (s2))) != 1)
	      ফেরত মিথ্যা;
	  }

	ফেরত সত্য;
      }

    ক্ষেত্র UNION_TYPE:
    ক্ষেত্র RECORD_TYPE:

	যদি (list_দৈর্ঘ্য (TYPE_FIELDS (t1)) != list_দৈর্ঘ্য (TYPE_FIELDS (t2)))
	  ফেরত মিথ্যা;

	জন্য (s1 = TYPE_FIELDS (t1), s2 = TYPE_FIELDS (t2);
	     s1 && s2;
	     s1 = DECL_CHAIN (s1), s2 = DECL_CHAIN (s2))
	  {
	    gcc_assert (বৃক্ষ_CODE (s1) == FIELD_DECL);
	    gcc_assert (বৃক্ষ_CODE (s2) == FIELD_DECL);

	    বৃক্ষ ft1 = বৃক্ষ_TYPE (s1);
	    বৃক্ষ ft2 = বৃক্ষ_TYPE (s2);

	    যদি (DECL_NAME (s1) != DECL_NAME (s2))
	      ফেরত মিথ্যা;

	    যদি (DECL_ALIGN (s1) != DECL_ALIGN (s2))
	      ফেরত মিথ্যা;

	    যদি (DECL_C_BIT_FIELD (s1) != DECL_C_BIT_FIELD (s2))
	       ফেরত মিথ্যা;

	    যদি (DECL_C_BIT_FIELD (s1))
	      {
		যদি (!বৃক্ষ_int_cst_equal (DECL_আকার (s1), DECL_আকার (s2)))
		  ফেরত মিথ্যা;

		ft1 = DECL_BIT_FIELD_TYPE (s1);
		ft2 = DECL_BIT_FIELD_TYPE (s2);
	      }

	    যদি (!ft1 || !ft2)
	      ফেরত মিথ্যা;

	    যদি (বৃক্ষ_CODE (ft1) == ERROR_MARK || বৃক্ষ_CODE (ft2) == ERROR_MARK)
	      ফেরত মিথ্যা;

	    তথ্য->anon_field = !DECL_NAME (s1);
	    তথ্য->pointedto = মিথ্যা;

	    ধ্রুবক কাঠামো tagged_tu_seen_cache *cache = তথ্য->cache;
	    তথ্য->cache = &entry;
	    যৌক্তিক ret = comptypes_internal (ft1, ft2, তথ্য);
	    তথ্য->cache = cache;
	    যদি (!ret)
	      ফেরত মিথ্যা;

	    বৃক্ষ st1 = TYPE_আকার (বৃক্ষ_TYPE (s1));
	    বৃক্ষ st2 = TYPE_আকার (বৃক্ষ_TYPE (s2));

	    যদি (তথ্য->equiv
		&& st1 && বৃক্ষ_CODE (st1) == INTEGER_CST
		&& st2 && বৃক্ষ_CODE (st2) == INTEGER_CST
		&& !বৃক্ষ_int_cst_equal (st1, st2))
	     ফেরত মিথ্যা;

	    বৃক্ষ counted_by1 = lookup_attribute ("counted_by",
						 DECL_ATTRIBUTES (s1));
	    বৃক্ষ counted_by2 = lookup_attribute ("counted_by",
						 DECL_ATTRIBUTES (s2));
	    /* If there is no counted_by attribute for both fields.  */
	    যদি (!counted_by1 && !counted_by2)
	      চালু;

	    /* If only one field has counted_by attribute.  */
	    যদি ((counted_by1 && !counted_by2)
		|| (!counted_by1 && counted_by2))
	      ফেরত মিথ্যা;

	    /* Now both s1 and s2 have counted_by attributes, check
	       whether they are the same.  */

	    বৃক্ষ counted_by_field1
	      = lookup_field (t1, বৃক্ষ_মান (বৃক্ষ_মান (counted_by1)));
	    বৃক্ষ counted_by_field2
	      = lookup_field (t2, বৃক্ষ_মান (বৃক্ষ_মান (counted_by2)));

	    gcc_assert (counted_by_field1 && counted_by_field2);

	    যখন (বৃক্ষ_CHAIN (counted_by_field1))
	      counted_by_field1 = বৃক্ষ_CHAIN (counted_by_field1);
	    যখন (বৃক্ষ_CHAIN (counted_by_field2))
	      counted_by_field2 = বৃক্ষ_CHAIN (counted_by_field2);

	    যদি (DECL_NAME (বৃক্ষ_মান (counted_by_field1))
		!= DECL_NAME (বৃক্ষ_মান (counted_by_field2)))
	      ফেরত মিথ্যা;
	  }
	ফেরত সত্য;

    পূর্বনির্ধারিত:
      gcc_unreachable ();
    }
}

/* Return true if two function types F1 and F2 are compatible.
   If either type specifies no argument types,
   the other must specify a fixed number of self-promoting arg types.
   Otherwise, if one type specifies only the number of arguments,
   the other must specify that number of self-promoting arg types.
   Otherwise, the argument types must match.  */

স্থির যৌক্তিক
function_types_compatible_p (const_বৃক্ষ f1, const_বৃক্ষ f2,
			     কাঠামো comptypes_তথ্য *তথ্য)
{
  বৃক্ষ ret1 = বৃক্ষ_TYPE (f1);
  বৃক্ষ ret2 = বৃক্ষ_TYPE (f2);

  /* 'volatile' qualifiers on a function's return type used to mean
     the function is noreturn.  */
  যদি (TYPE_VOLATILE (ret1) != TYPE_VOLATILE (ret2))
    pedwarn (প্রবেশ_location, 0, "function return types not compatible due to %<volatile%>");
  যদি (TYPE_VOLATILE (ret1))
    ret1 = build_qualified_type (TYPE_MAIN_VARIANT (ret1),
				 TYPE_QUALS (ret1) & ~TYPE_QUAL_VOLATILE);
  যদি (TYPE_VOLATILE (ret2))
    ret2 = build_qualified_type (TYPE_MAIN_VARIANT (ret2),
				 TYPE_QUALS (ret2) & ~TYPE_QUAL_VOLATILE);

  যৌক্তিক ignore_pargs = তথ্য->ignore_promoting_args;
  তথ্য->ignore_promoting_args = মিথ্যা;

  যদি (!comptypes_internal (ret1, ret2, তথ্য))
    ফেরত মিথ্যা;

  তথ্য->ignore_promoting_args = ignore_pargs;

  বৃক্ষ args1 = TYPE_ARG_TYPES (f1);
  বৃক্ষ args2 = TYPE_ARG_TYPES (f2);

  যদি ((args1 == NULL_বৃক্ষ) != (args2 == NULL_বৃক্ষ))
    তথ্য->different_types_p = সত্য;

  /* An unspecified parmlist matches any specified parmlist
     whose argument types don't need default promotions.  */

  যদি (args1 == NULL_বৃক্ষ)
    {
      যদি (TYPE_NO_NAMED_ARGS_STDARG_P (f1) != TYPE_NO_NAMED_ARGS_STDARG_P (f2))
	ফেরত মিথ্যা;
      যদি (!(তথ্য->ignore_promoting_args || self_promoting_args_p (args2)))
	ফেরত মিথ্যা;
      তথ্য->ignore_promoting_args = মিথ্যা;
      /* If one of these types comes from a non-prototype fn definition,
	 compare that with the other type's arglist.
	 If they don't match, ask for a warning (but no error).  */
      যদি (TYPE_ACTUAL_ARG_TYPES (f1)
	  && !type_lists_compatible_p (args2, TYPE_ACTUAL_ARG_TYPES (f1), তথ্য))
	 তথ্য->warning_needed = সত্য;
      ফেরত সত্য;
    }
  যদি (args2 == NULL_বৃক্ষ)
    {
      যদি (TYPE_NO_NAMED_ARGS_STDARG_P (f1) != TYPE_NO_NAMED_ARGS_STDARG_P (f2))
	ফেরত মিথ্যা;
      যদি (!(তথ্য->ignore_promoting_args || self_promoting_args_p (args1)))
	ফেরত মিথ্যা;
      তথ্য->ignore_promoting_args = মিথ্যা;
      যদি (TYPE_ACTUAL_ARG_TYPES (f2)
	  && !type_lists_compatible_p (args1, TYPE_ACTUAL_ARG_TYPES (f2), তথ্য))
	তথ্য->warning_needed = সত্য;
      ফেরত সত্য;
    }

  /* Both types have argument lists: compare them and propagate results.  */
  ফেরত type_lists_compatible_p (args1, args2, তথ্য);
}

/* Check two lists of types for compatibility, returning false for
   incompatible, true for compatible.  */

স্থির যৌক্তিক
type_lists_compatible_p (const_বৃক্ষ args1, const_বৃক্ষ args2,
			 কাঠামো comptypes_তথ্য *তথ্য)
{
  যখন (1)
    {
      যদি (args1 == NULL_বৃক্ষ && args2 == NULL_বৃক্ষ)
	ফেরত সত্য;
      /* If one list is shorter than the other,
	 they fail to match.  */
      যদি (args1 == NULL_বৃক্ষ || args2 == NULL_বৃক্ষ)
	ফেরত মিথ্যা;
      বৃক্ষ a1 = বৃক্ষ_মান (args1);
      বৃক্ষ a2 = বৃক্ষ_মান (args2);
      বৃক্ষ mv1 = remove_qualifiers (a1);
      বৃক্ষ mv2 = remove_qualifiers (a2);

      gcc_assert (mv2);
      gcc_assert (mv2);

      /* If one of the lists has an error marker, ignore this arg.  */
      যদি (বৃক্ষ_CODE (a1) == ERROR_MARK
	       || বৃক্ষ_CODE (a2) == ERROR_MARK)
	;
      অন্যথা যদি (!comptypes_internal (mv1, mv2, তথ্য))
	{
	  তথ্য->different_types_p = সত্য;
	  /* Allow  wait (union {union wait *u; int *i} *)
	     and  wait (union wait *)  to be compatible.  */
	  যদি (বৃক্ষ_CODE (a1) == UNION_TYPE
	      && (TYPE_NAME (a1) == NULL_বৃক্ষ
		  || TYPE_TRANSPARENT_AGGR (a1))
	      && বৃক্ষ_CODE (TYPE_আকার (a1)) == INTEGER_CST
	      && বৃক্ষ_int_cst_equal (TYPE_আকার (a1),
				     TYPE_আকার (a2)))
	    {
	      বৃক্ষ memb;
	      জন্য (memb = TYPE_FIELDS (a1);
		   memb; memb = DECL_CHAIN (memb))
		{
		  বৃক্ষ mv3 = remove_qualifiers (বৃক্ষ_TYPE (memb));
		  যদি (comptypes_internal (mv3, mv2, তথ্য))
		    বিরতি;
		}
	      যদি (memb == NULL_বৃক্ষ)
		ফেরত মিথ্যা;
	    }
	  অন্যথা যদি (বৃক্ষ_CODE (a2) == UNION_TYPE
		   && (TYPE_NAME (a2) == NULL_বৃক্ষ
		       || TYPE_TRANSPARENT_AGGR (a2))
		   && বৃক্ষ_CODE (TYPE_আকার (a2)) == INTEGER_CST
		   && বৃক্ষ_int_cst_equal (TYPE_আকার (a2),
					  TYPE_আকার (a1)))
	    {
	      বৃক্ষ memb;
	      জন্য (memb = TYPE_FIELDS (a2);
		   memb; memb = DECL_CHAIN (memb))
		{
		  বৃক্ষ mv3 = remove_qualifiers (বৃক্ষ_TYPE (memb));
		  যদি (comptypes_internal (mv3, mv1, তথ্য))
		    বিরতি;
		}
	      যদি (memb == NULL_বৃক্ষ)
		ফেরত মিথ্যা;
	    }
	  অন্যথা
	    ফেরত মিথ্যা;
	}

      args1 = বৃক্ষ_CHAIN (args1);
      args2 = বৃক্ষ_CHAIN (args2);
    }
}

/* Compute the size to increment a pointer by.  When a function type or void
   type or incomplete type is passed, size_one_node is returned.
   This function does not emit any diagnostics; the caller is responsible
   for that.  */

স্থির বৃক্ষ
c_আকার_in_bytes (const_বৃক্ষ type)
{
  গণনা বৃক্ষ_code code = বৃক্ষ_CODE (type);

  যদি (code == FUNCTION_TYPE || code == VOID_TYPE || code == ERROR_MARK
      || !COMPLETE_TYPE_P (type))
    ফেরত আকার_one_গ্রন্থি;

  /* Convert in case a char is more than one unit.  */
  ফেরত আকার_binop_loc (প্রবেশ_location, CEIL_DIV_রাশিমালা, TYPE_আকার_UNIT (type),
			 আকার_int (TYPE_PRECISION (char_type_গ্রন্থি)
				   / BITS_PER_UNIT));
}

/* Return either DECL or its known constant value (if it has one).  */

বৃক্ষ
decl_constant_মান_1 (বৃক্ষ decl, যৌক্তিক in_init)
{
  যদি (/* Note that DECL_INITIAL isn't valid for a PARM_DECL.  */
      বৃক্ষ_CODE (decl) != PARM_DECL
      && !বৃক্ষ_THIS_VOLATILE (decl)
      && বৃক্ষ_READONLY (decl)
      && DECL_INITIAL (decl) != NULL_বৃক্ষ
      && !error_operand_p (DECL_INITIAL (decl))
      /* This is invalid if initial value is not constant.
	 If it has either a function call, a memory reference,
	 or a variable, then re-evaluating it could give different results.  */
      && বৃক্ষ_CONSTANT (DECL_INITIAL (decl))
      /* Check for cases where this is sub-optimal, even though valid.  */
      && (in_init || বৃক্ষ_CODE (DECL_INITIAL (decl)) != CONSTRUCTOR))
    ফেরত DECL_INITIAL (decl);
  ফেরত decl;
}

/* Return either DECL or its known constant value (if it has one).
   Like the above, but always return decl outside of functions.  */

বৃক্ষ
decl_constant_মান (বৃক্ষ decl)
{
  /* Don't change a variable array bound or initial value to a constant
     in a place where a variable is invalid.  */
  ফেরত current_function_decl ? decl_constant_মান_1 (decl, মিথ্যা) : decl;
}

/* Convert the array expression EXP to a pointer.  */
স্থির বৃক্ষ
array_to_pointer_conversion (location_t loc, বৃক্ষ exp)
{
  বৃক্ষ orig_exp = exp;
  বৃক্ষ type = বৃক্ষ_TYPE (exp);
  বৃক্ষ adr;
  বৃক্ষ restype = বৃক্ষ_TYPE (type);
  বৃক্ষ ptrtype;

  gcc_assert (বৃক্ষ_CODE (type) == ARRAY_TYPE);

  STRIP_TYPE_NOPS (exp);

  copy_warning (exp, orig_exp);

  ptrtype = c_build_pointer_type (restype);

  যদি (INDIRECT_REF_P (exp))
    ফেরত convert (ptrtype, বৃক্ষ_OPERAND (exp, 0));

  /* In C++ array compound literals are temporary objects unless they are
     const or appear in namespace scope, so they are destroyed too soon
     to use them for much of anything  (c++/53220).  */
  যদি (warn_cxx_compat && বৃক্ষ_CODE (exp) == COMPOUND_LITERAL_রাশিমালা)
    {
      বৃক্ষ decl = বৃক্ষ_OPERAND (বৃক্ষ_OPERAND (exp, 0), 0);
      যদি (!বৃক্ষ_READONLY (decl) && !বৃক্ষ_STATIC (decl))
	warning_at (DECL_SOURCE_LOCATION (decl), OPT_Wc___compat,
		    "converting an array compound literal to a pointer "
		    "leads to a dangling pointer in C++");
    }

  adr = build_unary_op (loc, ADDR_রাশিমালা, exp, সত্য);
  ফেরত convert (ptrtype, adr);
}

/* Convert the function expression EXP to a pointer.  */
স্থির বৃক্ষ
function_to_pointer_conversion (location_t loc, বৃক্ষ exp)
{
  বৃক্ষ orig_exp = exp;

  gcc_assert (বৃক্ষ_CODE (বৃক্ষ_TYPE (exp)) == FUNCTION_TYPE);

  STRIP_TYPE_NOPS (exp);

  copy_warning (exp, orig_exp);

  বৃক্ষ exp2 = build_unary_op (loc, ADDR_রাশিমালা, exp, মিথ্যা);

  /* If the function is defined and known to not require a non-local
     context, make sure no trampoline is generated.  */
  যদি (বৃক্ষ_CODE (exp) == FUNCTION_DECL
      && DECL_INITIAL (exp) && !C_FUNC_NONLOCAL_CONTEXT (exp))
   বৃক্ষ_NO_TRAMPOLINE (exp2) = 1;

  ফেরত exp2;
}

/* Mark EXP as read, not just set, for set but not used -Wunused
   warning purposes.  */

শূন্য
mark_exp_read (বৃক্ষ exp)
{
  নির্বাচন (বৃক্ষ_CODE (exp))
    {
    ক্ষেত্র VAR_DECL:
    ক্ষেত্র PARM_DECL:
      DECL_READ_P (exp) = 1;
      বিরতি;
    CASE_CONVERT:
      যদি (VOID_TYPE_P (বৃক্ষ_TYPE (exp)))
	নির্বাচন (বৃক্ষ_CODE (বৃক্ষ_OPERAND (exp, 0)))
	  {
	  ক্ষেত্র PREINCREMENT_রাশিমালা:
	  ক্ষেত্র PREDECREMENT_রাশিমালা:
	  ক্ষেত্র POSTINCREMENT_রাশিমালা:
	  ক্ষেত্র POSTDECREMENT_রাশিমালা:
	    ফেরত;
	  পূর্বনির্ধারিত:
	    বিরতি;
	  }
      /* FALLTHRU */
    ক্ষেত্র ARRAY_REF:
    ক্ষেত্র COMPONENT_REF:
    ক্ষেত্র MODIFY_রাশিমালা:
    ক্ষেত্র REALPART_রাশিমালা:
    ক্ষেত্র IMAGPART_রাশিমালা:
    ক্ষেত্র ADDR_রাশিমালা:
    ক্ষেত্র VIEW_CONVERT_রাশিমালা:
    ক্ষেত্র PREINCREMENT_রাশিমালা:
    ক্ষেত্র PREDECREMENT_রাশিমালা:
    ক্ষেত্র POSTINCREMENT_রাশিমালা:
    ক্ষেত্র POSTDECREMENT_রাশিমালা:
      mark_exp_read (বৃক্ষ_OPERAND (exp, 0));
      বিরতি;
    ক্ষেত্র COMPOUND_রাশিমালা:
      /* Pattern match what build_atomic_assign produces with modifycode
	 NOP_EXPR.  */
      যদি (VAR_P (বৃক্ষ_OPERAND (exp, 1))
	  && DECL_ARTIFICIAL (বৃক্ষ_OPERAND (exp, 1))
	  && বৃক্ষ_CODE (বৃক্ষ_OPERAND (exp, 0)) == COMPOUND_রাশিমালা)
	{
	  বৃক্ষ t1 = বৃক্ষ_OPERAND (বৃক্ষ_OPERAND (exp, 0), 0);
	  বৃক্ষ t2 = বৃক্ষ_OPERAND (বৃক্ষ_OPERAND (exp, 0), 1);
	  যদি (বৃক্ষ_CODE (t1) == TARGET_রাশিমালা
	      && TARGET_রাশিমালা_SLOT (t1) == বৃক্ষ_OPERAND (exp, 1)
	      && বৃক্ষ_CODE (t2) == CALL_রাশিমালা)
	    {
	      বৃক্ষ fndecl = get_callee_fndecl (t2);
	      বৃক্ষ arg = NULL_বৃক্ষ;
	      যদি (fndecl
		  && বৃক্ষ_CODE (fndecl) == FUNCTION_DECL
		  && fndecl_built_in_p (fndecl, BUILT_IN_NORMAL)
		  && call_রাশিমালা_nargs (t2) >= 2)
		নির্বাচন (DECL_FUNCTION_CODE (fndecl))
		  {
		  ক্ষেত্র BUILT_IN_ATOMIC_STORE:
		    arg = CALL_রাশিমালা_ARG (t2, 1);
		    বিরতি;
		  ক্ষেত্র BUILT_IN_ATOMIC_STORE_1:
		  ক্ষেত্র BUILT_IN_ATOMIC_STORE_2:
		  ক্ষেত্র BUILT_IN_ATOMIC_STORE_4:
		  ক্ষেত্র BUILT_IN_ATOMIC_STORE_8:
		  ক্ষেত্র BUILT_IN_ATOMIC_STORE_16:
		    arg = CALL_রাশিমালা_ARG (t2, 0);
		    বিরতি;
		  পূর্বনির্ধারিত:
		    বিরতি;
		  }
	      যদি (arg)
		{
		  STRIP_NOPS (arg);
		  যদি (বৃক্ষ_CODE (arg) == ADDR_রাশিমালা
		      && DECL_P (বৃক্ষ_OPERAND (arg, 0))
		      && TYPE_ATOMIC (বৃক্ষ_TYPE (বৃক্ষ_OPERAND (arg, 0))))
		    mark_exp_read (বৃক্ষ_OPERAND (arg, 0));
		}
	    }
	}
      /* FALLTHRU */
    ক্ষেত্র C_MAYBE_CONST_রাশিমালা:
      mark_exp_read (বৃক্ষ_OPERAND (exp, 1));
      বিরতি;
    ক্ষেত্র OMP_ARRAY_SECTION:
      mark_exp_read (বৃক্ষ_OPERAND (exp, 0));
      যদি (বৃক্ষ_OPERAND (exp, 1))
	mark_exp_read (বৃক্ষ_OPERAND (exp, 1));
      যদি (বৃক্ষ_OPERAND (exp, 2))
	mark_exp_read (বৃক্ষ_OPERAND (exp, 2));
      বিরতি;
    পূর্বনির্ধারিত:
      বিরতি;
    }
}

/* Perform the default conversion of arrays and functions to pointers.
   Return the result of converting EXP.  For any other expression, just
   return EXP.

   LOC is the location of the expression.  */

কাঠামো c_রাশিমালা
default_function_array_conversion (location_t loc, কাঠামো c_রাশিমালা exp)
{
  বৃক্ষ orig_exp = exp.মান;
  বৃক্ষ type = বৃক্ষ_TYPE (exp.মান);
  গণনা বৃক্ষ_code code = বৃক্ষ_CODE (type);

  নির্বাচন (code)
    {
    ক্ষেত্র ARRAY_TYPE:
      {
	যৌক্তিক not_lvalue = মিথ্যা;
	যৌক্তিক lvalue_array_p;

	যখন ((বৃক্ষ_CODE (exp.মান) == NON_LVALUE_রাশিমালা
		|| CONVERT_রাশিমালা_P (exp.মান))
	       && বৃক্ষ_TYPE (বৃক্ষ_OPERAND (exp.মান, 0)) == type)
	  {
	    যদি (বৃক্ষ_CODE (exp.মান) == NON_LVALUE_রাশিমালা)
	      not_lvalue = সত্য;
	    exp.মান = বৃক্ষ_OPERAND (exp.মান, 0);
	  }

	copy_warning (exp.মান, orig_exp);

	lvalue_array_p = !not_lvalue && lvalue_p (exp.মান);
	যদি (!flag_isoc99 && !lvalue_array_p)
	  {
	    /* Before C99, non-lvalue arrays do not decay to pointers.
	       Normally, using such an array would be invalid; but it can
	       be used correctly inside sizeof or as a statement expression.
	       Thus, do not give an error here; an error will result later.  */
	    ফেরত exp;
	  }

	exp.মান = array_to_pointer_conversion (loc, exp.মান);
      }
      বিরতি;
    ক্ষেত্র FUNCTION_TYPE:
      exp.মান = function_to_pointer_conversion (loc, exp.মান);
      বিরতি;
    পূর্বনির্ধারিত:
      বিরতি;
    }

  ফেরত exp;
}

কাঠামো c_রাশিমালা
default_function_array_read_conversion (location_t loc, কাঠামো c_রাশিমালা exp)
{
  mark_exp_read (exp.মান);
  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  যদি (বৃক্ষ_CODE (exp.মান) == COMPONENT_REF
      && handle_counted_by_p (exp.মান))
    exp.মান = handle_counted_by_for_component_ref (loc, exp.মান);
  ফেরত default_function_array_conversion (loc, exp);
}

/* Return whether EXPR should be treated as an atomic lvalue for the
   purposes of load and store handling.  */

স্থির যৌক্তিক
really_atomic_lvalue (বৃক্ষ রাশিমালা)
{
  যদি (error_operand_p (রাশিমালা))
    ফেরত মিথ্যা;
  যদি (!TYPE_ATOMIC (বৃক্ষ_TYPE (রাশিমালা)))
    ফেরত মিথ্যা;
  যদি (!COMPLETE_TYPE_P (বৃক্ষ_TYPE (রাশিমালা)))
    ফেরত মিথ্যা;
  যদি (!lvalue_p (রাশিমালা))
    ফেরত মিথ্যা;

  /* Ignore _Atomic on register variables, since their addresses can't
     be taken so (a) atomicity is irrelevant and (b) the normal atomic
     sequences wouldn't work.  Ignore _Atomic on structures containing
     bit-fields, since accessing elements of atomic structures or
     unions is undefined behavior (C11 6.5.2.3#5), but it's unclear if
     it's undefined at translation time or execution time, and the
     normal atomic sequences again wouldn't work.  */
  যখন (handled_component_p (রাশিমালা))
    {
      যদি (বৃক্ষ_CODE (রাশিমালা) == COMPONENT_REF
	  && DECL_C_BIT_FIELD (বৃক্ষ_OPERAND (রাশিমালা, 1)))
	ফেরত মিথ্যা;
      রাশিমালা = বৃক্ষ_OPERAND (রাশিমালা, 0);
    }
  যদি (বৃক্ষ_CODE (রাশিমালা) == COMPOUND_LITERAL_রাশিমালা)
    রাশিমালা = COMPOUND_LITERAL_রাশিমালা_DECL (রাশিমালা);
  যদি (DECL_P (রাশিমালা) && C_DECL_REGISTER (রাশিমালা))
    ফেরত মিথ্যা;
  ফেরত সত্য;
}

/* If EXPR is a named constant (C23) derived from a constexpr variable
   - that is, a reference to such a variable, or a member extracted by
   a sequence of structure and union (but not array) member accesses
   (where union member accesses must access the same member as
   initialized) - then return the corresponding initializer;
   otherwise, return NULL_TREE.  */

স্থির বৃক্ষ
maybe_get_constexpr_init (বৃক্ষ রাশিমালা)
{
  বৃক্ষ decl = NULL_বৃক্ষ;
  যদি (বৃক্ষ_CODE (রাশিমালা) == VAR_DECL)
    decl = রাশিমালা;
  অন্যথা যদি (বৃক্ষ_CODE (রাশিমালা) == COMPOUND_LITERAL_রাশিমালা)
    decl = COMPOUND_LITERAL_রাশিমালা_DECL (রাশিমালা);
  যদি (decl
      && C_DECL_DECLARED_CONSTEXPR (decl)
      && DECL_INITIAL (decl) != NULL_বৃক্ষ
      && !error_operand_p (DECL_INITIAL (decl)))
    ফেরত DECL_INITIAL (decl);
  যদি (বৃক্ষ_CODE (রাশিমালা) != COMPONENT_REF)
    ফেরত NULL_বৃক্ষ;
  বৃক্ষ inner = maybe_get_constexpr_init (বৃক্ষ_OPERAND (রাশিমালা, 0));
  যদি (inner == NULL_বৃক্ষ)
    ফেরত NULL_বৃক্ষ;
  যখন ((CONVERT_রাশিমালা_P (inner) || বৃক্ষ_CODE (inner) == NON_LVALUE_রাশিমালা)
	 && !error_operand_p (inner)
	 && (TYPE_MAIN_VARIANT (বৃক্ষ_TYPE (inner))
	     == TYPE_MAIN_VARIANT (বৃক্ষ_TYPE (বৃক্ষ_OPERAND (inner, 0)))))
    inner = বৃক্ষ_OPERAND (inner, 0);
  যদি (বৃক্ষ_CODE (inner) != CONSTRUCTOR)
    ফেরত NULL_বৃক্ষ;
  বৃক্ষ field = বৃক্ষ_OPERAND (রাশিমালা, 1);
  unsigned HOST_WIDE_INT cidx;
  বৃক্ষ cfield, cvalue;
  যৌক্তিক have_other_init = মিথ্যা;
  FOR_EACH_CONSTRUCTOR_ELT (CONSTRUCTOR_ELTS (inner), cidx, cfield, cvalue)
    {
      যদি (cfield == field)
	ফেরত cvalue;
      have_other_init = সত্য;
    }
  যদি (বৃক্ষ_CODE (বৃক্ষ_TYPE (inner)) == UNION_TYPE
      && (have_other_init || field != TYPE_FIELDS (বৃক্ষ_TYPE (inner))))
    ফেরত NULL_বৃক্ষ;
  /* Return a default initializer.  */
  যদি (RECORD_OR_UNION_TYPE_P (বৃক্ষ_TYPE (রাশিমালা)))
    ফেরত build_constructor (বৃক্ষ_TYPE (রাশিমালা), ফাঁকা);
  ফেরত build_zero_cst (বৃক্ষ_TYPE (রাশিমালা));
}

/* Helper function for convert_lvalue_to_rvalue called via
   walk_tree_without_duplicates.  Find DATA inside of the expression.  */

স্থির বৃক্ষ
c_find_var_r (বৃক্ষ *tp, পূর্ণসংখ্যা *walk_subtrees, শূন্য *তথ্য)
{
  যদি (TYPE_P (*tp))
    *walk_subtrees = 0;
  অন্যথা যদি (*tp == (বৃক্ষ) তথ্য)
    ফেরত *tp;
  ফেরত NULL_বৃক্ষ;
}

/* Convert expression EXP (location LOC) from lvalue to rvalue,
   including converting functions and arrays to pointers if CONVERT_P.
   If READ_P, also mark the expression as having been read.  If
   FOR_INIT, constexpr expressions of structure and union type should
   be replaced by the corresponding CONSTRUCTOR; otherwise, only
   constexpr scalars (including elements of structures and unions) are
   replaced by their initializers.  */

কাঠামো c_রাশিমালা
convert_lvalue_to_rvalue (location_t loc, কাঠামো c_রাশিমালা exp,
			  যৌক্তিক convert_p, যৌক্তিক read_p, যৌক্তিক for_init)
{
  যৌক্তিক force_non_npc = মিথ্যা;
  যদি (read_p)
    mark_exp_read (exp.মান);
  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  যদি (read_p && বৃক্ষ_CODE (exp.মান) == COMPONENT_REF
      && handle_counted_by_p (exp.মান))
    exp.মান = handle_counted_by_for_component_ref (loc, exp.মান);

  যদি (convert_p)
    exp = default_function_array_conversion (loc, exp);
  যদি (!VOID_TYPE_P (বৃক্ষ_TYPE (exp.মান))
      || (flag_isoc2y
	  && TYPE_QUALS (বৃক্ষ_TYPE (exp.মান)) != TYPE_UNQUALIFIED))
    exp.মান = require_complete_type (loc, exp.মান);
  যদি (for_init || !RECORD_OR_UNION_TYPE_P (বৃক্ষ_TYPE (exp.মান)))
    {
      বৃক্ষ init = maybe_get_constexpr_init (exp.মান);
      যদি (init != NULL_বৃক্ষ)
	{
	  /* A named constant of pointer type or type nullptr_t is not
	     a null pointer constant even if the initializer is
	     one.  */
	  যদি (বৃক্ষ_CODE (init) == INTEGER_CST
	      && !INTEGRAL_TYPE_P (বৃক্ষ_TYPE (init))
	      && integer_zerop (init))
	    force_non_npc = সত্য;
	  exp.মান = init;
	}
    }
  যদি (really_atomic_lvalue (exp.মান))
    {
      vec<বৃক্ষ, va_gc> *params;
      বৃক্ষ nonatomic_type, tmp, tmp_addr, fndecl, func_call;
      বৃক্ষ রাশিমালা_type = বৃক্ষ_TYPE (exp.মান);
      বৃক্ষ রাশিমালা_addr = build_unary_op (loc, ADDR_রাশিমালা, exp.মান, মিথ্যা);
      বৃক্ষ seq_cst = build_int_cst (integer_type_গ্রন্থি, MEMMODEL_SEQ_CST);

      gcc_assert (TYPE_ATOMIC (রাশিমালা_type));

      /* Expansion of a generic atomic load may require an addition
	 element, so allocate enough to prevent a resize.  */
      vec_alloc (params, 4);

      /* Remove the qualifiers for the rest of the expressions and
	 create the VAL temp variable to hold the RHS.  */
      nonatomic_type = build_qualified_type (রাশিমালা_type, TYPE_UNQUALIFIED);
      tmp = create_tmp_var_raw (nonatomic_type);
      tmp_addr = build_unary_op (loc, ADDR_রাশিমালা, tmp, মিথ্যা);
      বৃক্ষ_ADDRESSABLE (tmp) = 1;
      /* Do not disable warnings for TMP even though it's artificial.
	 -Winvalid-memory-model depends on it.  */

      /* Issue __atomic_load (&expr, &tmp, SEQ_CST);  */
      fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_LOAD);
      params->quick_ঠেলো (রাশিমালা_addr);
      params->quick_ঠেলো (tmp_addr);
      params->quick_ঠেলো (seq_cst);
      func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, ফাঁকা);

      /* EXPR is always read.  */
      mark_exp_read (exp.মান);

      /* Optimize the common case where c_build_function_call_vec
	 immediately folds __atomic_load (&expr, &tmp, SEQ_CST); into
	 tmp = __atomic_load_<N> (&expr, SEQ_CST);
	 In that case tmp is not addressable and can be initialized
	 fully by the rhs of the MODIFY_EXPR.  */
      বৃক্ষ tem = func_call;
      যদি (CONVERT_রাশিমালা_P (tem) && VOID_TYPE_P (বৃক্ষ_TYPE (tem)))
	{
	  tem = বৃক্ষ_OPERAND (tem, 0);
	  যদি (বৃক্ষ_CODE (tem) == MODIFY_রাশিমালা
	      && বৃক্ষ_OPERAND (tem, 0) == tmp
	      && !walk_বৃক্ষ_without_duplicates (&বৃক্ষ_OPERAND (tem, 1),
						c_find_var_r, tmp))
	    {
	      বৃক্ষ_ADDRESSABLE (tmp) = 0;
	      func_call = বৃক্ষ_OPERAND (tem, 1);
	    }
	}

      /* Return tmp which contains the value loaded.  */
      exp.মান = build4 (TARGET_রাশিমালা, nonatomic_type, tmp, func_call,
			  NULL_বৃক্ষ, NULL_বৃক্ষ);
    }
  যদি (convert_p && !error_operand_p (exp.মান)
      && (বৃক্ষ_CODE (বৃক্ষ_TYPE (exp.মান)) != ARRAY_TYPE))
    exp.মান = convert (build_qualified_type (বৃক্ষ_TYPE (exp.মান), TYPE_UNQUALIFIED), exp.মান);
  যদি (force_non_npc)
    exp.মান = build1 (NOP_রাশিমালা, বৃক্ষ_TYPE (exp.মান), exp.মান);

  {
    বৃক্ষ false_মান, true_মান;
    যদি (convert_p && !error_operand_p (exp.মান)
	&& c_hardbool_type_attr (বৃক্ষ_TYPE (exp.মান),
				 &false_মান, &true_মান))
      {
	বৃক্ষ t = save_রাশিমালা (exp.মান);

	mark_exp_read (exp.মান);

	বৃক্ষ trapfn = builtin_decl_explicit (BUILT_IN_TRAP);
	বৃক্ষ রাশিমালা = build_call_রাশিমালা_loc (loc, trapfn, 0);
	রাশিমালা = build_compound_রাশিমালা (loc, রাশিমালা, boolean_true_গ্রন্থি);
	রাশিমালা = fold_build3_loc (loc, COND_রাশিমালা, boolean_type_গ্রন্থি,
				fold_build2_loc (loc, NE_রাশিমালা,
						 boolean_type_গ্রন্থি,
						 t, true_মান),
				রাশিমালা, boolean_true_গ্রন্থি);
	রাশিমালা = fold_build3_loc (loc, COND_রাশিমালা, boolean_type_গ্রন্থি,
				fold_build2_loc (loc, NE_রাশিমালা,
						 boolean_type_গ্রন্থি,
						 t, false_মান),
				রাশিমালা, boolean_false_গ্রন্থি);

	exp.মান = রাশিমালা;
      }
  }

  ফেরত exp;
}

/* Wrapper for the overload above, same arguments but for tree rather than
   c_expr.  This is important for hardbools to decay to bools.  */

স্থির অন্তঃরেখ বৃক্ষ
convert_lvalue_to_rvalue (location_t loc, বৃক্ষ val,
			  যৌক্তিক convert_p, যৌক্তিক read_p, যৌক্তিক for_init = মিথ্যা)
{
  কাঠামো c_রাশিমালা রাশিমালা;
  memset (&রাশিমালা, 0, আকার (রাশিমালা));
  রাশিমালা.মান = val;
  রাশিমালা = convert_lvalue_to_rvalue (loc, রাশিমালা, convert_p, read_p, for_init);
  ফেরত রাশিমালা.মান;
}

/* EXP is an expression of integer type.  Apply the integer promotions
   to it and return the promoted value.  */

বৃক্ষ
perform_integral_promotions (বৃক্ষ exp)
{
  বৃক্ষ type = বৃক্ষ_TYPE (exp);
  গণনা বৃক্ষ_code code = বৃক্ষ_CODE (type);

  gcc_assert (INTEGRAL_TYPE_P (type));

  /* Convert enums to the result of applying the integer promotions to
     their underlying type.  */
  যদি (code == ENUMERAL_TYPE)
    {
      type = ENUM_UNDERLYING_TYPE (type);
      যদি (c_promoting_integer_type_p (type))
	{
	  যদি (TYPE_UNSIGNED (type)
	      && TYPE_PRECISION (type) == TYPE_PRECISION (integer_type_গ্রন্থি))
	    type = unsigned_type_গ্রন্থি;
	  অন্যথা
	    type = integer_type_গ্রন্থি;
	}

      ফেরত convert (type, exp);
    }

  /* ??? This should no longer be needed now bit-fields have their
     proper types.  */
  যদি (বৃক্ষ_CODE (exp) == COMPONENT_REF
      && DECL_C_BIT_FIELD (বৃক্ষ_OPERAND (exp, 1)))
    {
      যদি (BITINT_TYPE_P (DECL_BIT_FIELD_TYPE (বৃক্ষ_OPERAND (exp, 1))))
	{
	  বৃক্ষ btype = DECL_BIT_FIELD_TYPE (বৃক্ষ_OPERAND (exp, 1));
	  যদি (বৃক্ষ_CODE (btype) == BITINT_TYPE)
	    ফেরত convert (btype, exp);
	  অন্যথা
	    ফেরত convert (ENUM_UNDERLYING_TYPE (btype), exp);
	}
      /* If it's thinner than an int, promote it like a
	 c_promoting_integer_type_p, otherwise leave it alone.  */
      যদি (compare_বৃক্ষ_int (DECL_আকার (বৃক্ষ_OPERAND (exp, 1)),
			    TYPE_PRECISION (integer_type_গ্রন্থি)) < 0)
	ফেরত convert (integer_type_গ্রন্থি, exp);
    }

  যদি (c_promoting_integer_type_p (type))
    {
      /* Preserve unsignedness if not really getting any wider.  */
      যদি (TYPE_UNSIGNED (type)
	  && TYPE_PRECISION (type) == TYPE_PRECISION (integer_type_গ্রন্থি))
	ফেরত convert (unsigned_type_গ্রন্থি, exp);

      ফেরত convert (integer_type_গ্রন্থি, exp);
    }

  ফেরত exp;
}


/* Perform default promotions for C data used in expressions.
   Enumeral types or short or char are converted to int.
   In addition, manifest constants symbols are replaced by their values.  */

বৃক্ষ
default_conversion (বৃক্ষ exp)
{
  বৃক্ষ orig_exp;
  বৃক্ষ type = বৃক্ষ_TYPE (exp);
  গণনা বৃক্ষ_code code = বৃক্ষ_CODE (type);
  বৃক্ষ promoted_type;

  mark_exp_read (exp);
  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  যদি (বৃক্ষ_CODE (exp) == COMPONENT_REF
      && handle_counted_by_p (exp))
    exp = handle_counted_by_for_component_ref (রাশিমালা_LOCATION (exp), exp);

  /* Functions and arrays have been converted during parsing.  */
  gcc_assert (code != FUNCTION_TYPE);
  যদি (code == ARRAY_TYPE)
    ফেরত exp;

  /* Constants can be used directly unless they're not loadable.  */
  যদি (বৃক্ষ_CODE (exp) == CONST_DECL)
    exp = DECL_INITIAL (exp);

  /* Strip no-op conversions.  */
  orig_exp = exp;
  STRIP_TYPE_NOPS (exp);

  copy_warning (exp, orig_exp);

  যদি (code == VOID_TYPE)
    {
      error_at (রাশিমালা_LOC_OR_LOC (exp, প্রবেশ_location),
		"void value not ignored as it ought to be");
      ফেরত error_mark_গ্রন্থি;
    }

  exp = require_complete_type (রাশিমালা_LOC_OR_LOC (exp, প্রবেশ_location), exp);
  যদি (exp == error_mark_গ্রন্থি)
    ফেরত error_mark_গ্রন্থি;

  promoted_type = targetm.promoted_type (type);
  যদি (promoted_type)
    ফেরত convert (promoted_type, exp);

  যদি (INTEGRAL_TYPE_P (type))
    {
      /* Avoid performing integral promotion of bit-precise integer
	 type bit-field to its corresponding bit-precise integer if
	 orig_exp is a cast to it to its underlying type.  */
      যদি (orig_exp != exp
	  && বৃক্ষ_CODE (exp) == COMPONENT_REF
	  && DECL_C_BIT_FIELD (বৃক্ষ_OPERAND (exp, 1))
	  && BITINT_TYPE_P (DECL_BIT_FIELD_TYPE (বৃক্ষ_OPERAND (exp, 1))))
	ফেরত perform_integral_promotions (orig_exp);
      ফেরত perform_integral_promotions (exp);
    }

  ফেরত exp;
}

/* Look up COMPONENT in a structure or union TYPE.

   If the component name is not found, returns NULL_TREE.  Otherwise,
   the return value is a TREE_LIST, with each TREE_VALUE a FIELD_DECL
   stepping down the chain to the component, which is in the last
   TREE_VALUE of the list.  Normally the list is of length one, but if
   the component is embedded within (nested) anonymous structures or
   unions, the list steps down the chain to the component.  */

বৃক্ষ
lookup_field (const_বৃক্ষ type, বৃক্ষ component)
{
  বৃক্ষ field;

  /* If TYPE_LANG_SPECIFIC is set, then it is a sorted array of pointers
     to the field elements.  Use a binary search on this array to quickly
     find the element.  Otherwise, do a linear search.  TYPE_LANG_SPECIFIC
     will always be set for structures which have many elements.

     Duplicate field checking replaces duplicates with NULL_TREE so
     TYPE_LANG_SPECIFIC arrays are potentially no longer sorted.  In that
     case just iterate using DECL_CHAIN.  */

  যদি (TYPE_LANG_SPECIFIC (type) && TYPE_LANG_SPECIFIC (type)->s
      && !seen_error ())
    {
      পূর্ণসংখ্যা bot, শীর্ষ, half;
      বৃক্ষ *field_array = &TYPE_LANG_SPECIFIC (type)->s->elts[0];

      field = TYPE_FIELDS (type);
      bot = 0;
      শীর্ষ = TYPE_LANG_SPECIFIC (type)->s->len;
      যখন (শীর্ষ - bot > 1)
	{
	  half = (শীর্ষ - bot + 1) >> 1;
	  field = field_array[bot+half];

	  যদি (DECL_NAME (field) == NULL_বৃক্ষ)
	    {
	      /* Step through all anon unions in linear fashion.  */
	      যখন (DECL_NAME (field_array[bot]) == NULL_বৃক্ষ)
		{
		  field = field_array[bot++];
		  যদি (RECORD_OR_UNION_TYPE_P (বৃক্ষ_TYPE (field)))
		    {
		      বৃক্ষ anon = lookup_field (বৃক্ষ_TYPE (field), component);

		      যদি (anon)
			ফেরত বৃক্ষ_cons (NULL_বৃক্ষ, field, anon);

		      /* The Plan 9 compiler permits referring
			 directly to an anonymous struct/union field
			 using a typedef name.  */
		      যদি (flag_plan9_extensions
			  && TYPE_NAME (বৃক্ষ_TYPE (field)) != NULL_বৃক্ষ
			  && (বৃক্ষ_CODE (TYPE_NAME (বৃক্ষ_TYPE (field)))
			      == TYPE_DECL)
			  && (DECL_NAME (TYPE_NAME (বৃক্ষ_TYPE (field)))
			      == component))
			বিরতি;
		    }
		}

	      /* Entire record is only anon unions.  */
	      যদি (bot > শীর্ষ)
		ফেরত NULL_বৃক্ষ;

	      /* Restart the binary search, with new lower bound.  */
	      চালু;
	    }

	  যদি (DECL_NAME (field) == component)
	    বিরতি;
	  যদি (DECL_NAME (field) < component)
	    bot += half;
	  অন্যথা
	    শীর্ষ = bot + half;
	}

      যদি (DECL_NAME (field_array[bot]) == component)
	field = field_array[bot];
      অন্যথা যদি (DECL_NAME (field) != component)
	ফেরত NULL_বৃক্ষ;
    }
  অন্যথা
    {
      জন্য (field = TYPE_FIELDS (type); field; field = DECL_CHAIN (field))
	{
	  যদি (DECL_NAME (field) == NULL_বৃক্ষ
	      && RECORD_OR_UNION_TYPE_P (বৃক্ষ_TYPE (field)))
	    {
	      বৃক্ষ anon = lookup_field (বৃক্ষ_TYPE (field), component);

	      যদি (anon)
		ফেরত বৃক্ষ_cons (NULL_বৃক্ষ, field, anon);

	      /* The Plan 9 compiler permits referring directly to an
		 anonymous struct/union field using a typedef
		 name.  */
	      যদি (flag_plan9_extensions
		  && TYPE_NAME (বৃক্ষ_TYPE (field)) != NULL_বৃক্ষ
		  && বৃক্ষ_CODE (TYPE_NAME (বৃক্ষ_TYPE (field))) == TYPE_DECL
		  && (DECL_NAME (TYPE_NAME (বৃক্ষ_TYPE (field)))
		      == component))
		বিরতি;
	    }

	  যদি (DECL_NAME (field) == component)
	    বিরতি;
	}

      যদি (field == NULL_বৃক্ষ)
	ফেরত NULL_বৃক্ষ;
    }

  ফেরত বৃক্ষ_cons (NULL_বৃক্ষ, field, NULL_বৃক্ষ);
}

/* Recursively append candidate IDENTIFIER_NODEs to CANDIDATES.  */

স্থির শূন্য
lookup_field_fuzzy_find_candidates (বৃক্ষ type, বৃক্ষ component,
				    vec<বৃক্ষ> *candidates)
{
  বৃক্ষ field;
  জন্য (field = TYPE_FIELDS (type); field; field = DECL_CHAIN (field))
    {
      যদি (DECL_NAME (field) == NULL_বৃক্ষ
	  && RECORD_OR_UNION_TYPE_P (বৃক্ষ_TYPE (field)))
	lookup_field_fuzzy_find_candidates (বৃক্ষ_TYPE (field), component,
					    candidates);

      যদি (DECL_NAME (field))
	candidates->safe_ঠেলো (DECL_NAME (field));
    }
}

/* Like "lookup_field", but find the closest matching IDENTIFIER_NODE,
   rather than returning a TREE_LIST for an exact match.  */

স্থির বৃক্ষ
lookup_field_fuzzy (বৃক্ষ type, বৃক্ষ component)
{
  gcc_assert (বৃক্ষ_CODE (component) == IDENTIFIER_গ্রন্থি);

  /* First, gather a list of candidates.  */
  auto_vec <বৃক্ষ> candidates;

  lookup_field_fuzzy_find_candidates (type, component,
				      &candidates);

  ফেরত find_closest_identifier (component, &candidates);
}

/* Support function for build_component_ref's error-handling.

   Given DATUM_TYPE, and "DATUM.COMPONENT", where DATUM is *not* a
   struct or union, should we suggest "DATUM->COMPONENT" as a hint?  */

স্থির যৌক্তিক
should_suggest_deref_p (বৃক্ষ datum_type)
{
  /* We don't do it for Objective-C, since Objective-C 2.0 dot-syntax
     allows "." for ptrs; we could be handling a failed attempt
     to access a property.  */
  যদি (c_dialect_objc ())
    ফেরত মিথ্যা;

  /* Only suggest it for pointers...  */
  যদি (বৃক্ষ_CODE (datum_type) != POINTER_TYPE)
    ফেরত মিথ্যা;

  /* ...to structs/unions.  */
  বৃক্ষ underlying_type = বৃক্ষ_TYPE (datum_type);
  গণনা বৃক্ষ_code code = বৃক্ষ_CODE (underlying_type);
  যদি (code == RECORD_TYPE || code == UNION_TYPE)
    ফেরত সত্য;
  অন্যথা
    ফেরত মিথ্যা;
}

/* Give a component ref REF, decide whether we should handle its counted_by
   attribute based on its context:
   Do not handle counted_by when in offsetof, typeof and alignof operator.  */

স্থির যৌক্তিক
handle_counted_by_p (বৃক্ষ ref)
{
  gcc_assert (বৃক্ষ_CODE (ref) == COMPONENT_REF);
  বৃক্ষ datum = বৃক্ষ_OPERAND (ref, 0);
  /* If the component_ref is build for a offsetof, i.e., the datum
     of the component_ref is a indirect_ref of null_pointer_node,
     we should not generate call to .ACCESS_WITH_SIZE.  */
  যদি (বৃক্ষ_CODE (datum) == INDIRECT_REF
      && বৃক্ষ_OPERAND (datum, 0) == null_pointer_গ্রন্থি)
    ফেরত মিথ্যা;
  যদি (in_typeof || in_alignof)
    ফেরত মিথ্যা;
  ফেরত সত্য;
}

/* Given a component ref REF, if there is a counted_by attribute attached,
   issue error when the element_type is a structure or union including a
   flexible array member.  */

স্থির শূন্য
check_counted_by_attribute (location_t loc, বৃক্ষ ref)
{
  বৃক্ষ subdatum = বৃক্ষ_OPERAND (ref, 1);
  বৃক্ষ sub_type = বৃক্ষ_TYPE (subdatum);

  যদি (!flexible_array_member_type_p (sub_type)
      && বৃক্ষ_CODE (sub_type) != POINTER_TYPE)
    ফেরত;

  বৃক্ষ element_type = বৃক্ষ_TYPE (sub_type);

  বৃক্ষ attr_counted_by = lookup_attribute ("counted_by",
					   DECL_ATTRIBUTES (subdatum));
  যদি (attr_counted_by)
    {
      /* Issue error when the element_type is a structure or
	union including a flexible array member.  */
      যদি (RECORD_OR_UNION_TYPE_P (element_type)
	  && TYPE_INCLUDES_FLEXARRAY (element_type))
	{
	  error_at (loc,
		    "%<counted_by%> attribute is not allowed for a pointer to"
		    " structure or union with flexible array member");
	  ফেরত;
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

স্থির বৃক্ষ
build_counted_by_ref (বৃক্ষ datum, বৃক্ষ subdatum,
		      বৃক্ষ *counted_by_type)
{
  বৃক্ষ sub_type = বৃক্ষ_TYPE (subdatum);
  যদি (!flexible_array_member_type_p (sub_type)
      && বৃক্ষ_CODE (sub_type) != POINTER_TYPE)
    ফেরত NULL_বৃক্ষ;

  বৃক্ষ attr_counted_by = lookup_attribute ("counted_by",
					   DECL_ATTRIBUTES (subdatum));
  যদি (!attr_counted_by)
    ফেরত NULL_বৃক্ষ;

  বৃক্ষ counted_by_ref = NULL_বৃক্ষ;
  *counted_by_type = NULL_বৃক্ষ;

  বৃক্ষ type = বৃক্ষ_TYPE (datum);

  /* If the type of the containing structure is an anonymous struct/union,
     and this anonymous struct/union is not a root type, get the first
     outer named structure/union type.  */
  যখন (বৃক্ষ_CODE (datum) == COMPONENT_REF
	 && c_type_tag (type) == NULL_বৃক্ষ
	 && DECL_NAME (বৃক্ষ_OPERAND (datum, 1)) == NULL_বৃক্ষ)
    {
      datum = বৃক্ষ_OPERAND (datum, 0);
      type = বৃক্ষ_TYPE (datum);
    }

  বৃক্ষ field_id = বৃক্ষ_মান (বৃক্ষ_মান (attr_counted_by));
  বৃক্ষ counted_by_field = lookup_field (type, field_id);
  gcc_assert (counted_by_field);

  বৃক্ষ counted_by_subdatum;
  করো
    {
      counted_by_subdatum = বৃক্ষ_মান (counted_by_field);
      /* Get the TYPE of the counted_by field.  */
      *counted_by_type = বৃক্ষ_TYPE (counted_by_subdatum);

      counted_by_ref
	= build3 (COMPONENT_REF, বৃক্ষ_TYPE (counted_by_subdatum),
		  datum, counted_by_subdatum, NULL_বৃক্ষ);

      datum = counted_by_ref;
      counted_by_field = বৃক্ষ_CHAIN (counted_by_field);
    }
  যখন (counted_by_field);

  counted_by_ref = build_fold_addr_রাশিমালা (counted_by_ref);
  ফেরত counted_by_ref;
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
স্থির বৃক্ষ
build_access_with_আকার_for_counted_by (location_t loc, বৃক্ষ ref,
				       বৃক্ষ counted_by_ref,
				       বৃক্ষ counted_by_type)
{
  gcc_assert (flexible_array_member_type_p (বৃক্ষ_TYPE (ref))
	      || বৃক্ষ_CODE (বৃক্ষ_TYPE (ref)) == POINTER_TYPE);

  যৌক্তিক is_fam = flexible_array_member_type_p (বৃক্ষ_TYPE (ref));

  /* The result type of the call is a pointer to the flexible array type;
     or is the original pointer type to the pointer field with counted_by.  */
  বৃক্ষ ফলাফল_type = is_fam ? c_build_pointer_type (বৃক্ষ_TYPE (ref))
		     : বৃক্ষ_TYPE (ref);

  বৃক্ষ element_type = বৃক্ষ_TYPE (বৃক্ষ_TYPE (ref));
  বৃক্ষ element_আকার = VOID_TYPE_P (element_type)
		      ? আকার_one_গ্রন্থি
		      : TYPE_আকার_UNIT (element_type);
  যদি (element_আকার == NULL_বৃক্ষ)
    ফেরত ref;

  বৃক্ষ first_param = is_fam
		     ? c_fully_fold (array_to_pointer_conversion (loc, ref),
				     মিথ্যা, ফাঁকা)
		     : c_fully_fold (ref, মিথ্যা, ফাঁকা);
  বৃক্ষ second_param
    = c_fully_fold (counted_by_ref, মিথ্যা, ফাঁকা);
  বৃক্ষ third_param = build_int_cst (c_build_pointer_type (counted_by_type), 0);

  বৃক্ষ call
    = build_call_রাশিমালা_internal_loc (loc, IFN_ACCESS_WITH_আকার,
				    ফলাফল_type, 4,
				    first_param,
				    second_param,
				    third_param,
				    element_আকার);

  /* Wrap the call with an INDIRECT_REF with the flexible array type.  */
  যদি (is_fam)
    call = build1 (INDIRECT_REF, বৃক্ষ_TYPE (ref), call);
  SET_রাশিমালা_LOCATION (call, loc);
  ফেরত call;
}

/* For the COMPONENT_REF ref, check whether it has a counted_by attribute,
   if so, wrap this COMPONENT_REF with the corresponding CALL to the
   function .ACCESS_WITH_SIZE.
   Otherwise, return the ref itself.  */

বৃক্ষ
handle_counted_by_for_component_ref (location_t loc, বৃক্ষ ref)
{
  gcc_assert (বৃক্ষ_CODE (ref) == COMPONENT_REF);
  বৃক্ষ datum = বৃক্ষ_OPERAND (ref, 0);
  বৃক্ষ subdatum = বৃক্ষ_OPERAND (ref, 1);
  বৃক্ষ counted_by_type = NULL_বৃক্ষ;

  যদি (!(flexible_array_member_type_p (বৃক্ষ_TYPE (ref))
	|| বৃক্ষ_CODE (বৃক্ষ_TYPE (ref)) == POINTER_TYPE))
    ফেরত ref;

  বৃক্ষ counted_by_ref = build_counted_by_ref (datum, subdatum,
					      &counted_by_type);
  যদি (counted_by_ref)
    ref = build_access_with_আকার_for_counted_by (loc, ref,
						 counted_by_ref,
						 counted_by_type);
  ফেরত ref;
}

/* Make an expression to refer to the COMPONENT field of structure or
   union value DATUM.  COMPONENT is an IDENTIFIER_NODE.  LOC is the
   location of the COMPONENT_REF.  COMPONENT_LOC is the location
   of COMPONENT.  ARROW_LOC is the location of the first -> operand if
   it is from -> operator.
   If HANDLE_COUNTED_BY is true, check the counted_by attribute and generate
   a call to .ACCESS_WITH_SIZE.  Otherwise, ignore the attribute.  */

বৃক্ষ
build_component_ref (location_t loc, বৃক্ষ datum, বৃক্ষ component,
		     location_t component_loc, location_t arrow_loc)
{
  বৃক্ষ type = বৃক্ষ_TYPE (datum);
  গণনা বৃক্ষ_code code = বৃক্ষ_CODE (type);
  বৃক্ষ field = ফাঁকা;
  বৃক্ষ ref;
  যৌক্তিক datum_lvalue = lvalue_p (datum);

  যদি (!objc_is_public (datum, component))
    ফেরত error_mark_গ্রন্থি;

  /* Detect Objective-C property syntax object.property.  */
  যদি (c_dialect_objc ()
      && (ref = objc_maybe_build_component_ref (datum, component)))
    ফেরত ref;

  /* See if there is a field or component with name COMPONENT.  */

  যদি (code == RECORD_TYPE || code == UNION_TYPE)
    {
      যদি (!COMPLETE_TYPE_P (type))
	{
	  c_incomplete_type_error (loc, NULL_বৃক্ষ, type);
	  ফেরত error_mark_গ্রন্থি;
	}

      field = lookup_field (type, component);

      যদি (!field)
	{
	  বৃক্ষ guessed_id = lookup_field_fuzzy (type, component);
	  যদি (guessed_id)
	    {
	      /* Attempt to provide a fixit replacement hint, if
		 we have a valid range for the component.  */
	      location_t reported_loc
		= (component_loc != UNKNOWN_LOCATION) ? component_loc : loc;
	      gcc_rich_location rich_loc (reported_loc);
	      যদি (component_loc != UNKNOWN_LOCATION)
		rich_loc.add_fixit_misspelled_id (component_loc, guessed_id);
	      error_at (&rich_loc,
			"%qT has no member named %qE; did you mean %qE?",
			type, component, guessed_id);
	    }
	  অন্যথা
	    error_at (loc, "%qT has no member named %qE", type, component);
	  ফেরত error_mark_গ্রন্থি;
	}

      /* Accessing elements of atomic structures or unions is undefined
	 behavior (C11 6.5.2.3#5).  */
      যদি (TYPE_ATOMIC (type) && c_inhibit_evaluation_warnings == 0)
	{
	  যদি (code == RECORD_TYPE)
	    warning_at (loc, 0, "accessing a member %qE of an atomic "
			"structure %qE", component, datum);
	  অন্যথা
	    warning_at (loc, 0, "accessing a member %qE of an atomic "
			"union %qE", component, datum);
	}

      /* Chain the COMPONENT_REFs if necessary down to the FIELD.
	 This might be better solved in future the way the C++ front
	 end does it - by giving the anonymous entities each a
	 separate name and type, and then have build_component_ref
	 recursively call itself.  We can't do that here.  */
      করো
	{
	  বৃক্ষ subdatum = বৃক্ষ_মান (field);
	  পূর্ণসংখ্যা quals;
	  বৃক্ষ subtype;
	  যৌক্তিক use_datum_quals;

	  যদি (বৃক্ষ_TYPE (subdatum) == error_mark_গ্রন্থি)
	    ফেরত error_mark_গ্রন্থি;

	  /* If this is an rvalue, it does not have qualifiers in C
	     standard terms and we must avoid propagating such
	     qualifiers down to a non-lvalue array that is then
	     converted to a pointer.  */
	  use_datum_quals = (datum_lvalue
			     || বৃক্ষ_CODE (বৃক্ষ_TYPE (subdatum)) != ARRAY_TYPE);

	  quals = TYPE_QUALS (strip_array_types (বৃক্ষ_TYPE (subdatum)));
	  যদি (use_datum_quals)
	    quals |= TYPE_QUALS (বৃক্ষ_TYPE (datum));
	  subtype = c_build_qualified_type (বৃক্ষ_TYPE (subdatum), quals);

	  ref = build3 (COMPONENT_REF, subtype, datum, subdatum,
			NULL_বৃক্ষ);
	  SET_রাশিমালা_LOCATION (ref, loc);

	  check_counted_by_attribute (loc, ref);

	  যদি (বৃক্ষ_READONLY (subdatum)
	      || (use_datum_quals && বৃক্ষ_READONLY (datum)))
	    বৃক্ষ_READONLY (ref) = 1;
	  যদি (বৃক্ষ_THIS_VOLATILE (subdatum)
	      || (use_datum_quals && বৃক্ষ_THIS_VOLATILE (datum)))
	    বৃক্ষ_THIS_VOLATILE (ref) = 1;

	  যদি (বৃক্ষ_UNAVAILABLE (subdatum))
	    error_unavailable_use (subdatum, NULL_বৃক্ষ);
	  অন্যথা যদি (বৃক্ষ_DEPRECATED (subdatum))
	    warn_deprecated_use (subdatum, NULL_বৃক্ষ);

	  datum = ref;

	  field = বৃক্ষ_CHAIN (field);
	}
      যখন (field);

      ফেরত ref;
    }
  অন্যথা যদি (should_suggest_deref_p (type))
    {
      /* Special-case the error message for "ptr.field" for the case
	 where the user has confused "." vs "->".  */
      rich_location richloc (সারি_table, loc);
      যদি (INDIRECT_REF_P (datum) && arrow_loc != UNKNOWN_LOCATION)
	{
	  richloc.add_fixit_ঢোকাও_before (arrow_loc, "(*");
	  richloc.add_fixit_ঢোকাও_after (arrow_loc, ")");
	  error_at (&richloc,
		    "%qE is a pointer to pointer; did you mean to dereference "
		    "it before applying %<->%> to it?",
		    বৃক্ষ_OPERAND (datum, 0));
	}
      অন্যথা
	{
	  /* "loc" should be the "." token.  */
	  richloc.add_fixit_replace ("->");
	  error_at (&richloc,
		    "%qE is a pointer; did you mean to use %<->%>?",
		    datum);
	}
      ফেরত error_mark_গ্রন্থি;
    }
  অন্যথা যদি (code != ERROR_MARK)
    error_at (loc,
	      "request for member %qE in something not a structure or union",
	      component);

  ফেরত error_mark_গ্রন্থি;
}

/* Given an expression PTR for a pointer, return an expression
   for the value pointed to.
   ERRORSTRING is the name of the operator to appear in error messages.

   LOC is the location to use for the generated tree.  */

বৃক্ষ
build_indirect_ref (location_t loc, বৃক্ষ ptr, ref_operator errstring)
{
  বৃক্ষ pointer = default_conversion (ptr);
  বৃক্ষ type = বৃক্ষ_TYPE (pointer);
  বৃক্ষ ref;

  যদি (বৃক্ষ_CODE (type) == POINTER_TYPE)
    {
      যদি (CONVERT_রাশিমালা_P (pointer)
          || বৃক্ষ_CODE (pointer) == VIEW_CONVERT_রাশিমালা)
	{
	  /* If a warning is issued, mark it to avoid duplicates from
	     the backend.  This only needs to be done at
	     warn_strict_aliasing > 2.  */
	  যদি (warn_strict_aliasing > 2)
	    যদি (strict_aliasing_warning (রাশিমালা_LOCATION (pointer),
					 type, বৃক্ষ_OPERAND (pointer, 0)))
	      suppress_warning (pointer, OPT_Wstrict_aliasing_);
	}

      যদি (বৃক্ষ_CODE (pointer) == ADDR_রাশিমালা
	  && (বৃক্ষ_TYPE (বৃক্ষ_OPERAND (pointer, 0))
	      == বৃক্ষ_TYPE (type)))
	{
	  ref = বৃক্ষ_OPERAND (pointer, 0);
	  protected_set_রাশিমালা_location (ref, loc);
	  ফেরত ref;
	}
      অন্যথা
	{
	  বৃক্ষ t = বৃক্ষ_TYPE (type);

	  ref = build1 (INDIRECT_REF, t, pointer);

	  যদি (VOID_TYPE_P (t) && c_inhibit_evaluation_warnings == 0)
	    warning_at (loc, 0, "dereferencing %<void *%> pointer");

	  /* We *must* set TREE_READONLY when dereferencing a pointer to const,
	     so that we get the proper error message if the result is used
	     to assign to.  Also, &* is supposed to be a no-op.
	     And ANSI C seems to specify that the type of the result
	     should be the const type.  */
	  /* A de-reference of a pointer to const is not a const.  It is valid
	     to change it via some other pointer.  */
	  বৃক্ষ_READONLY (ref) = TYPE_READONLY (t);
	  বৃক্ষ_SIDE_EFFECTS (ref)
	    = TYPE_VOLATILE (t) || বৃক্ষ_SIDE_EFFECTS (pointer);
	  বৃক্ষ_THIS_VOLATILE (ref) = TYPE_VOLATILE (t);
	  protected_set_রাশিমালা_location (ref, loc);
	  ফেরত ref;
	}
    }
  অন্যথা যদি (বৃক্ষ_CODE (pointer) != ERROR_MARK)
    invalid_indirection_error (loc, type, errstring);

  ফেরত error_mark_গ্রন্থি;
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

বৃক্ষ
build_array_ref (location_t loc, বৃক্ষ array, বৃক্ষ সূচক)
{
  বৃক্ষ ret;
  যৌক্তিক swapped = মিথ্যা;
  যদি (বৃক্ষ_TYPE (array) == error_mark_গ্রন্থি
      || বৃক্ষ_TYPE (সূচক) == error_mark_গ্রন্থি)
    ফেরত error_mark_গ্রন্থি;

  যদি (বৃক্ষ_CODE (বৃক্ষ_TYPE (array)) != ARRAY_TYPE
      && বৃক্ষ_CODE (বৃক্ষ_TYPE (array)) != POINTER_TYPE
      /* Allow vector[index] but not index[vector].  */
      && !gnu_vector_type_p (বৃক্ষ_TYPE (array)))
    {
      যদি (বৃক্ষ_CODE (বৃক্ষ_TYPE (সূচক)) != ARRAY_TYPE
	  && বৃক্ষ_CODE (বৃক্ষ_TYPE (সূচক)) != POINTER_TYPE)
	{
          error_at (loc,
            "subscripted value is neither array nor pointer nor vector");

	  ফেরত error_mark_গ্রন্থি;
	}
      std::swap (array, সূচক);
      swapped = সত্য;
    }

  যদি (!INTEGRAL_TYPE_P (বৃক্ষ_TYPE (সূচক)))
    {
      error_at (loc, "array subscript is not an integer");
      ফেরত error_mark_গ্রন্থি;
    }

  যদি (বৃক্ষ_CODE (বৃক্ষ_TYPE (বৃক্ষ_TYPE (array))) == FUNCTION_TYPE)
    {
      error_at (loc, "subscripted value is pointer to function");
      ফেরত error_mark_গ্রন্থি;
    }

  /* ??? Existing practice has been to warn only when the char
     index is syntactically the index, not for char[array].  */
  যদি (!swapped)
     warn_array_subscript_with_type_char (loc, সূচক);

  /* Apply default promotions *after* noticing character types.  */
  সূচক = default_conversion (সূচক);
  যদি (সূচক == error_mark_গ্রন্থি)
    ফেরত error_mark_গ্রন্থি;

  gcc_assert (বৃক্ষ_CODE (বৃক্ষ_TYPE (সূচক)) == INTEGER_TYPE
	      || বৃক্ষ_CODE (বৃক্ষ_TYPE (সূচক)) == BITINT_TYPE);

  যৌক্তিক was_vector = VECTOR_TYPE_P (বৃক্ষ_TYPE (array));
  যৌক্তিক non_lvalue = convert_vector_to_array_for_subscript (loc, &array, সূচক);

  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  যদি (বৃক্ষ_CODE (array) == COMPONENT_REF
      && handle_counted_by_p (array))
    array = handle_counted_by_for_component_ref (loc, array);

  যদি (বৃক্ষ_CODE (বৃক্ষ_TYPE (array)) == ARRAY_TYPE)
    {
      বৃক্ষ rval, type;

      /* An array that is indexed by a non-constant
	 cannot be stored in a register; we must be able to do
	 address arithmetic on its address.
	 Likewise an array of elements of variable size.  */
      যদি (বৃক্ষ_CODE (সূচক) != INTEGER_CST
	  || (COMPLETE_TYPE_P (বৃক্ষ_TYPE (বৃক্ষ_TYPE (array)))
	      && বৃক্ষ_CODE (TYPE_আকার (বৃক্ষ_TYPE (বৃক্ষ_TYPE (array)))) != INTEGER_CST))
	{
	  যদি (!c_mark_addressable (array, সত্য, সত্য))
	    ফেরত error_mark_গ্রন্থি;
	}
      /* An array that is indexed by a constant value which is not within
	 the array bounds cannot be stored in a register either; because we
	 would get a crash in store_bit_field/extract_bit_field when trying
	 to access a non-existent part of the register.  */
      যদি (বৃক্ষ_CODE (সূচক) == INTEGER_CST
	  && TYPE_DOMAIN (বৃক্ষ_TYPE (array))
	  && !int_fits_type_p (সূচক, TYPE_DOMAIN (বৃক্ষ_TYPE (array))))
	{
	  যদি (!c_mark_addressable (array, মিথ্যা, সত্য))
	    ফেরত error_mark_গ্রন্থি;
	  /* ISO C2Y disallows a negative integer constant expression index
	     when array subscripting has an operand of array type.  */
	  যদি (flag_isoc2y
	      && !বৃক্ষ_OVERFLOW (সূচক)
	      && বৃক্ষ_int_cst_sgn (সূচক) < 0)
	    error_at (loc, "array subscript is negative");
	}

      যদি ((pedantic || warn_c90_c99_compat || warn_c23_c2y_compat)
	  && ! was_vector)
	{
	  বৃক্ষ foo = array;
	  যখন (বৃক্ষ_CODE (foo) == COMPONENT_REF)
	    foo = বৃক্ষ_OPERAND (foo, 0);
	  যদি ((VAR_P (foo) && C_DECL_REGISTER (foo))
	      || (বৃক্ষ_CODE (foo) == COMPOUND_LITERAL_রাশিমালা
		  && C_DECL_REGISTER (COMPOUND_LITERAL_রাশিমালা_DECL (foo))))
	    pedwarn_c23 (loc, OPT_Wpedantic,
			 "ISO C forbids subscripting %<register%> array "
			 "before C2Y");
	  অন্যথা যদি (!lvalue_p (foo))
	    pedwarn_c90 (loc, OPT_Wpedantic,
			 "ISO C90 forbids subscripting non-lvalue "
			 "array");
	}

      যদি (বৃক্ষ_CODE (বৃক্ষ_TYPE (সূচক)) == BITINT_TYPE
	  && TYPE_PRECISION (বৃক্ষ_TYPE (সূচক)) > TYPE_PRECISION (sizetype))
	সূচক = fold_convert (sizetype, সূচক);

      type = বৃক্ষ_TYPE (বৃক্ষ_TYPE (array));
      rval = build4 (ARRAY_REF, type, array, সূচক, NULL_বৃক্ষ, NULL_বৃক্ষ);
      /* Array ref is const/volatile if the array elements are
	 or if the array is.  */
      বৃক্ষ_READONLY (rval)
	|= (TYPE_READONLY (বৃক্ষ_TYPE (বৃক্ষ_TYPE (array)))
	    | বৃক্ষ_READONLY (array));
      বৃক্ষ_SIDE_EFFECTS (rval)
	|= (TYPE_VOLATILE (বৃক্ষ_TYPE (বৃক্ষ_TYPE (array)))
	    | বৃক্ষ_SIDE_EFFECTS (array));
      বৃক্ষ_THIS_VOLATILE (rval)
	|= (TYPE_VOLATILE (বৃক্ষ_TYPE (বৃক্ষ_TYPE (array)))
	    /* This was added by rms on 16 Nov 91.
	       It fixes  vol struct foo *a;  a->elts[1]
	       in an inline function.
	       Hope it doesn't break something else.  */
	    | বৃক্ষ_THIS_VOLATILE (array));
      ret = require_complete_type (loc, rval);
      protected_set_রাশিমালা_location (ret, loc);
      যদি (non_lvalue)
	ret = non_lvalue_loc (loc, ret);
      ফেরত ret;
    }
  অন্যথা
    {
      বৃক্ষ ar = default_conversion (array);

      যদি (ar == error_mark_গ্রন্থি)
	ফেরত ar;

      gcc_assert (বৃক্ষ_CODE (বৃক্ষ_TYPE (ar)) == POINTER_TYPE);
      gcc_assert (বৃক্ষ_CODE (বৃক্ষ_TYPE (বৃক্ষ_TYPE (ar))) != FUNCTION_TYPE);

      ret = build_indirect_ref (loc, build_দ্বিমিক_op (loc, PLUS_রাশিমালা, ar,
						      সূচক, মিথ্যা),
				RO_ARRAY_INDEXING);
      যদি (non_lvalue)
	ret = non_lvalue_loc (loc, ret);
      ফেরত ret;
    }
}

/* Build an OpenMP array section reference, creating an exact type for the
   resulting expression based on the element type and bounds if possible.  If
   we have variable bounds, create an incomplete array type for the result
   instead.  */

বৃক্ষ
build_omp_array_section (location_t loc, বৃক্ষ array, বৃক্ষ সূচক, বৃক্ষ দৈর্ঘ্য)
{
  বৃক্ষ type = বৃক্ষ_TYPE (array);
  gcc_assert (type);

  বৃক্ষ sectype, eltype = বৃক্ষ_TYPE (type);

  /* It's not an array or pointer type.  Just reuse the type of the original
     expression as the type of the array section (an error will be raised
     anyway, later).  */
  যদি (eltype == NULL_বৃক্ষ || error_operand_p (eltype))
    sectype = বৃক্ষ_TYPE (array);
  অন্যথা
    {
      বৃক্ষ idxtype = NULL_বৃক্ষ;

      যদি (সূচক != NULL_বৃক্ষ
	  && দৈর্ঘ্য != NULL_বৃক্ষ
	  && INTEGRAL_TYPE_P (বৃক্ষ_TYPE (সূচক))
	  && INTEGRAL_TYPE_P (বৃক্ষ_TYPE (দৈর্ঘ্য)))
	{
	  বৃক্ষ নিচের = fold_convert (sizetype, সূচক);
	  বৃক্ষ উপরের = fold_convert (sizetype, দৈর্ঘ্য);
	  উপরের = আকার_binop (PLUS_রাশিমালা, নিচের, উপরের);
	  উপরের = আকার_binop (MINUS_রাশিমালা, উপরের, আকার_one_গ্রন্থি);
	  idxtype = build_range_type (sizetype, নিচের, উপরের);
	}
      অন্যথা যদি ((সূচক == NULL_বৃক্ষ || integer_zerop (সূচক))
	       && দৈর্ঘ্য != NULL_বৃক্ষ
	       && INTEGRAL_TYPE_P (বৃক্ষ_TYPE (দৈর্ঘ্য)))
	idxtype = build_সূচক_type (দৈর্ঘ্য);

      gcc_assert (!error_operand_p (idxtype));

      sectype = c_build_array_type (eltype, idxtype);
    }

  ফেরত build3_loc (loc, OMP_ARRAY_SECTION, sectype, array, সূচক, দৈর্ঘ্য);
}


/* Record that REF is used.  This is relevant for undeclared static
   function and declarations referenced from a non-local context.
   ADDRESS indicates whether the address is taken.  */

শূন্য
mark_decl_used (বৃক্ষ ref, যৌক্তিক address)
{
  যদি (!ref || !DECL_P (ref) || in_alignof)
    ফেরত;

  /* Non-file-scope and non-local reference in nested function.  */
  যৌক্তিক nonloc_p = current_function_decl && DECL_CONTEXT (ref)
		  && DECL_CONTEXT (current_function_decl)
		  && DECL_CONTEXT (ref) != current_function_decl;

  /* An undeclared static function.  */
  যৌক্তিক static_p = বৃক্ষ_CODE (ref) == FUNCTION_DECL
		  && DECL_INITIAL (ref) == NULL_বৃক্ষ
		  && DECL_EXTERNAL (ref)
		  && !বৃক্ষ_PUBLIC (ref);

  যদি (!static_p && !nonloc_p)
    ফেরত;

  /* If we may be in an unevaluated context, delay the decision.  */
  যদি (in_sizeof || in_typeof || in_countof || in_generic)
    ফেরত record_maybe_used_decl (ref, address);

  যদি (static_p)
    C_DECL_USED (ref) = 1;

  যদি (nonloc_p && (VAR_OR_FUNCTION_DECL_P (ref)
		   || বৃক্ষ_CODE (ref) == PARM_DECL))
    DECL_NONLOCAL (ref) = 1;

  /* Nothing to do anymore.  */
  যদি (!nonloc_p || C_FUNC_NONLOCAL_CONTEXT (current_function_decl))
    ফেরত;

  /* Filter out the cases where referencing a non-local variable does not
     require a non-local context passed via the static chain.  */
  যদি (!c_type_variably_modified_p (বৃক্ষ_TYPE (ref)))
    নির্বাচন (বৃক্ষ_CODE (ref))
      {
      ক্ষেত্র FUNCTION_DECL:
	/* Use of another local function that requires no context is ok.  */
	যদি (!C_FUNC_NONLOCAL_CONTEXT (ref) && DECL_INITIAL (ref))
	  ফেরত;
	বিরতি;
      ক্ষেত্র VAR_DECL:
	/* Static variables and constexpr are ok, but for the later only
	   when the address is not taken.  */
	যদি (বৃক্ষ_STATIC (ref) || (C_DECL_DECLARED_CONSTEXPR (ref) && !address))
	  ফেরত;
	বিরতি;
      ক্ষেত্র TYPE_DECL:
	/* A typedef is ok when not for a variably-modified type. */
	ফেরত;
      ক্ষেত্র CONST_DECL:
	/* An enumeration constant is ok. */
	ফেরত;
      ক্ষেত্র PARM_DECL:
	বিরতি;
      ক্ষেত্র LABEL_DECL:
	বিরতি;
      পূর্বনির্ধারিত:
	gcc_unreachable ();
    }

  /* Mark all parent functions up to the nesting level of the variable as
     as needing the non-local context.  */
  জন্য (বৃক্ষ cont = current_function_decl; cont; cont = DECL_CONTEXT (cont))
    {
      যদি (cont == DECL_CONTEXT (ref))
	বিরতি;

      /* There should not be any other type of context used for function
	 except TRANSLATION_UNIT_DECL which we should be able to reach.  */
      gcc_checking_assert (বৃক্ষ_CODE (cont) == FUNCTION_DECL);

      যদি (বৃক্ষ_CODE (cont) == FUNCTION_DECL)
	C_FUNC_NONLOCAL_CONTEXT (cont) = 1;
    }
}


/* Build an external reference to identifier ID.  FUN indicates
   whether this will be used for a function call.  LOC is the source
   location of the identifier.  This sets *TYPE to the type of the
   identifier, which is not the same as the type of the returned value
   for CONST_DECLs defined as enum constants.  If the type of the
   identifier is not available, *TYPE is set to NULL.  */
বৃক্ষ
build_external_ref (location_t loc, বৃক্ষ id, যৌক্তিক fun, বৃক্ষ *type)
{
  বৃক্ষ ref;
  বৃক্ষ decl = lookup_name (id);

  /* In Objective-C, an instance variable (ivar) may be preferred to
     whatever lookup_name() found.  */
  decl = objc_lookup_ivar (decl, id);

  *type = ফাঁকা;
  যদি (decl && decl != error_mark_গ্রন্থি)
    {
      ref = decl;
      *type = বৃক্ষ_TYPE (ref);
      যদি (DECL_P (decl) && C_DECL_UNDERSPECIFIED (decl))
	error_at (loc, "underspecified %qD referenced in its initializer",
		  decl);
    }
  অন্যথা যদি (fun)
    /* Implicit function declaration.  */
    ref = implicitly_declare (loc, id);
  অন্যথা যদি (decl == error_mark_গ্রন্থি)
    /* Don't complain about something that's already been
       complained about.  */
    ফেরত error_mark_গ্রন্থি;
  অন্যথা
    {
      undeclared_variable (loc, id);
      ফেরত error_mark_গ্রন্থি;
    }

  /* For an OpenMP map clause, we can get better diagnostics for decls with
     unmappable types if we return the decl with an error_mark_node type,
     rather than returning error_mark_node for the decl itself.  */
  যদি (বৃক্ষ_TYPE (ref) == error_mark_গ্রন্থি
      && !c_omp_array_section_p)
    ফেরত error_mark_গ্রন্থি;

  যদি (বৃক্ষ_UNAVAILABLE (ref))
    error_unavailable_use (ref, NULL_বৃক্ষ);
  অন্যথা যদি (বৃক্ষ_DEPRECATED (ref))
    warn_deprecated_use (ref, NULL_বৃক্ষ);

  /* Recursive call does not count as usage.  */
  যদি (ref != current_function_decl)
    {
      বৃক্ষ_USED (ref) = 1;
    }

  mark_decl_used (ref, মিথ্যা);

  যদি (বৃক্ষ_CODE (ref) == CONST_DECL)
    {
      used_types_ঢোকাও (বৃক্ষ_TYPE (ref));

      যদি (warn_cxx_compat
	  && বৃক্ষ_CODE (বৃক্ষ_TYPE (ref)) == ENUMERAL_TYPE
	  && C_TYPE_DEFINED_IN_STRUCT (বৃক্ষ_TYPE (ref)))
	{
	  warning_at (loc, OPT_Wc___compat,
		      "enum constant defined in struct or union "
		      "is not visible in C++");
	  inform (DECL_SOURCE_LOCATION (ref), "enum constant defined here");
	}

      ref = DECL_INITIAL (ref);
      বৃক্ষ_CONSTANT (ref) = 1;
    }
  /* C99 6.7.4p3: An inline definition of a function with external
     linkage ... shall not contain a reference to an identifier with
     internal linkage.  */
  অন্যথা যদি (current_function_decl != NULL_বৃক্ষ
	   && DECL_DECLARED_INLINE_P (current_function_decl)
	   && DECL_EXTERNAL (current_function_decl)
	   && VAR_OR_FUNCTION_DECL_P (ref)
	   && (!VAR_P (ref) || বৃক্ষ_STATIC (ref))
	   && ! বৃক্ষ_PUBLIC (ref)
	   && DECL_CONTEXT (ref) != current_function_decl)
    record_inline_static (loc, current_function_decl, ref,
			  csi_internal);

  ফেরত ref;
}

স্থির কাঠামো maybe_used_decl *maybe_used_decls;

/* Record that DECL, a reference seen inside sizeof or typeof or _Countof or
   _Generic, might be used if the operand of sizeof is a VLA type or the
   operand of typeof is a variably modified type or the operand of _Countof has
   a variable number of elements or the operand of _Generic is the one selected
   as the result.  */

স্থির শূন্য
record_maybe_used_decl (বৃক্ষ decl, যৌক্তিক address)
{
  কাঠামো maybe_used_decl *t = XOBNEW (&parser_obstack, কাঠামো maybe_used_decl);
  t->decl = decl;
  t->level = in_sizeof + in_typeof + in_countof + in_generic;
  t->address = address;
  t->পরবর্তী = maybe_used_decls;
  maybe_used_decls = t;
}

/* Pop the stack of decls possibly used inside sizeof or typeof or _Countof or
   _Generic.  If USED is false, just discard them.  If it is true, mark them
   used (if no longer inside sizeof or typeof or _Countof or _Generic) or move
   them to the next level up (if still inside sizeof or typeof or _Countof or
   _Generic).  */

শূন্য
বের_করো_maybe_used (যৌক্তিক used)
{
  কাঠামো maybe_used_decl *p = maybe_used_decls;
  পূর্ণসংখ্যা cur_level = in_sizeof + in_typeof + in_countof + in_generic;
  যখন (p && p->level > cur_level)
    {
      যদি (used)
	{
	  যদি (cur_level == 0)
	    mark_decl_used (p->decl, p->address);
	  অন্যথা
	    p->level = cur_level;
	}
      p = p->পরবর্তী;
    }
  যদি (!used || cur_level == 0)
    maybe_used_decls = p;
}

/* Pop the stack of decls possibly used inside sizeof or typeof or _Countof or
   _Generic, without acting on them, and return the pointer to the previous top
   of the stack.  This for use at the end of a default generic association when
   it is not yet known whether the expression is used.  If it later turns out
   the expression is used (or treated as used before C23), restore_maybe_used
   should be called on the return value followed by pop_maybe_used (true);
   otherwise, the return value can be discarded.  */

কাঠামো maybe_used_decl *
save_maybe_used ()
{
  কাঠামো maybe_used_decl *p = maybe_used_decls, *orig = p;
  পূর্ণসংখ্যা cur_level = in_sizeof + in_typeof + in_countof + in_generic;
  যখন (p && p->level > cur_level)
    p = p->পরবর্তী;
  maybe_used_decls = p;
  ফেরত orig;
}

/* Restore the stack of decls possibly used inside sizeof or typeof or _Countof
   or _Generic returned by save_maybe_used.  It is required that the stack is
   at exactly the point where it was left by save_maybe_used.  */

শূন্য
restore_maybe_used (কাঠামো maybe_used_decl *স্তূপ)
{
  maybe_used_decls = স্তূপ;
}

/* Return the result of sizeof applied to EXPR.  */

কাঠামো c_রাশিমালা
c_রাশিমালা_sizeof_রাশিমালা (location_t loc, কাঠামো c_রাশিমালা রাশিমালা)
{
  কাঠামো c_রাশিমালা ret;
  যদি (রাশিমালা.মান == error_mark_গ্রন্থি)
    {
      ret.মান = error_mark_গ্রন্থি;
      ret.original_code = ERROR_MARK;
      ret.original_type = ফাঁকা;
      ret.m_decimal = 0;
      বের_করো_maybe_used (মিথ্যা);
    }
  অন্যথা
    {
      যৌক্তিক রাশিমালা_const_operands = সত্য;

      যদি (বৃক্ষ_CODE (রাশিমালা.মান) == PARM_DECL
	  && C_ARRAY_PARAMETER (রাশিমালা.মান))
	{
	  auto_diagnostic_group d;
	  যদি (warning_at (loc, OPT_Wsizeof_array_argument,
			  "%<sizeof%> on array function parameter %qE will "
			  "return size of %qT", রাশিমালা.মান,
			  বৃক্ষ_TYPE (রাশিমালা.মান)))
	    inform (DECL_SOURCE_LOCATION (রাশিমালা.মান), "declared here");
	}
      বৃক্ষ folded_রাশিমালা = c_fully_fold (রাশিমালা.মান, require_constant_মান,
				       &রাশিমালা_const_operands);
      ret.মান = c_sizeof (loc, বৃক্ষ_TYPE (folded_রাশিমালা));
      c_last_sizeof_arg = রাশিমালা.মান;
      c_last_sizeof_loc = loc;
      ret.original_code = SIZEOF_রাশিমালা;
      ret.original_type = ফাঁকা;
      ret.m_decimal = 0;
      যদি (C_TYPE_VARIABLE_আকার (বৃক্ষ_TYPE (folded_রাশিমালা)))
	{
	  /* sizeof is evaluated when given a vla (C99 6.5.3.4p2).  */
	  ret.মান = build2 (C_MAYBE_CONST_রাশিমালা, বৃক্ষ_TYPE (ret.মান),
			      folded_রাশিমালা, ret.মান);
	  C_MAYBE_CONST_রাশিমালা_NON_CONST (ret.মান) = !রাশিমালা_const_operands;
	  SET_রাশিমালা_LOCATION (ret.মান, loc);
	}
      বের_করো_maybe_used (C_TYPE_VARIABLE_আকার (বৃক্ষ_TYPE (folded_রাশিমালা)));
    }
  ফেরত ret;
}

/* Return the result of sizeof applied to T, a structure for the type
   name passed to sizeof (rather than the type itself).  LOC is the
   location of the original expression.  */

কাঠামো c_রাশিমালা
c_রাশিমালা_sizeof_type (location_t loc, কাঠামো c_type_name *t)
{
  বৃক্ষ type;
  কাঠামো c_রাশিমালা ret;
  বৃক্ষ type_রাশিমালা = NULL_বৃক্ষ;
  যৌক্তিক type_রাশিমালা_const = সত্য;
  type = groktypename (t, &type_রাশিমালা, &type_রাশিমালা_const);
  ret.মান = c_sizeof (loc, type);
  c_last_sizeof_arg = type;
  c_last_sizeof_loc = loc;
  ret.original_code = SIZEOF_রাশিমালা;
  ret.original_type = ফাঁকা;
  ret.m_decimal = 0;
  যদি (type == error_mark_গ্রন্থি)
    {
      ret.মান = error_mark_গ্রন্থি;
      ret.original_code = ERROR_MARK;
    }
  অন্যথা
  যদি ((type_রাশিমালা || বৃক্ষ_CODE (ret.মান) == INTEGER_CST)
      && C_TYPE_VARIABLE_আকার (type))
    {
      /* If the type is a [*] array, it is a VLA but is represented as
	 having a size of zero.  In such a case we must ensure that
	 the result of sizeof does not get folded to a constant by
	 c_fully_fold, because if the size is evaluated the result is
	 not constant and so constraints on zero or negative size
	 arrays must not be applied when this sizeof call is inside
	 another array declarator.  */
      যদি (!type_রাশিমালা)
	type_রাশিমালা = integer_zero_গ্রন্থি;
      ret.মান = build2 (C_MAYBE_CONST_রাশিমালা, বৃক্ষ_TYPE (ret.মান),
			  type_রাশিমালা, ret.মান);
      C_MAYBE_CONST_রাশিমালা_NON_CONST (ret.মান) = !type_রাশিমালা_const;
    }
  বের_করো_maybe_used (type != error_mark_গ্রন্থি
		  ? C_TYPE_VARIABLE_আকার (type) : মিথ্যা);
  ফেরত ret;
}

স্থির যৌক্তিক
শীর্ষ_array_vla_p (const_বৃক্ষ type)
{
  যদি (বৃক্ষ_CODE (type) != ARRAY_TYPE)
    ফেরত মিথ্যা;

  বৃক্ষ d = TYPE_DOMAIN (type);

  যদি (!d)
    ফেরত মিথ্যা;
  যদি (!TYPE_MAX_মান (d))
    ফেরত মিথ্যা;

  ফেরত বৃক্ষ_CODE (TYPE_MAX_মান (d)) != INTEGER_CST
	 || বৃক্ষ_CODE (TYPE_MIN_মান (d)) != INTEGER_CST;
}

/* Return the result of countof applied to EXPR.  */

কাঠামো c_রাশিমালা
c_রাশিমালা_countof_রাশিমালা (location_t loc, কাঠামো c_রাশিমালা রাশিমালা)
{
  কাঠামো c_রাশিমালা ret;
  যদি (রাশিমালা.মান == error_mark_গ্রন্থি)
    {
      ret.মান = error_mark_গ্রন্থি;
      ret.original_code = ERROR_MARK;
      ret.original_type = ফাঁকা;
      ret.m_decimal = 0;
      বের_করো_maybe_used (মিথ্যা);
    }
  অন্যথা
    {
      যৌক্তিক রাশিমালা_const_operands = সত্য;

      বৃক্ষ folded_রাশিমালা = c_fully_fold (রাশিমালা.মান, require_constant_মান,
				       &রাশিমালা_const_operands);
      ret.মান = c_countof_type (loc, বৃক্ষ_TYPE (folded_রাশিমালা));
      c_last_sizeof_arg = রাশিমালা.মান;
      c_last_sizeof_loc = loc;
      ret.original_code = COUNTOF_রাশিমালা;
      ret.original_type = ফাঁকা;
      ret.m_decimal = 0;
      যদি (শীর্ষ_array_vla_p (বৃক্ষ_TYPE (folded_রাশিমালা)))
	{
	  /* countof is evaluated when given a vla.  */
	  ret.মান = build2 (C_MAYBE_CONST_রাশিমালা, বৃক্ষ_TYPE (ret.মান),
			      folded_রাশিমালা, ret.মান);
	  C_MAYBE_CONST_রাশিমালা_NON_CONST (ret.মান) = !রাশিমালা_const_operands;
	  SET_রাশিমালা_LOCATION (ret.মান, loc);
	}
      বের_করো_maybe_used (শীর্ষ_array_vla_p (বৃক্ষ_TYPE (folded_রাশিমালা)));
    }
  ফেরত ret;
}

/* Return the result of countof applied to T, a structure for the type
   name passed to countof (rather than the type itself).  LOC is the
   location of the original expression.  */

কাঠামো c_রাশিমালা
c_রাশিমালা_countof_type (location_t loc, কাঠামো c_type_name *t)
{
  বৃক্ষ type;
  কাঠামো c_রাশিমালা ret;
  বৃক্ষ type_রাশিমালা = NULL_বৃক্ষ;
  যৌক্তিক type_রাশিমালা_const = সত্য;
  type = groktypename (t, &type_রাশিমালা, &type_রাশিমালা_const);
  ret.মান = c_countof_type (loc, type);
  c_last_sizeof_arg = type;
  c_last_sizeof_loc = loc;
  ret.original_code = COUNTOF_রাশিমালা;
  ret.original_type = ফাঁকা;
  ret.m_decimal = 0;
  যদি (type == error_mark_গ্রন্থি)
    {
      ret.মান = error_mark_গ্রন্থি;
      ret.original_code = ERROR_MARK;
    }
  অন্যথা
  যদি ((type_রাশিমালা || বৃক্ষ_CODE (ret.মান) == INTEGER_CST)
      && শীর্ষ_array_vla_p (type))
    {
      /* If the type is a [*] array, it is a VLA but is represented as
	 having a size of zero.  In such a case we must ensure that
	 the result of countof does not get folded to a constant by
	 c_fully_fold, because if the number of elements is evaluated
	 the result is not constant and so
	 constraints on zero or negative size arrays must not be applied
	 when this countof call is inside another array declarator.  */
      যদি (!type_রাশিমালা)
	type_রাশিমালা = integer_zero_গ্রন্থি;
      ret.মান = build2 (C_MAYBE_CONST_রাশিমালা, বৃক্ষ_TYPE (ret.মান),
			  type_রাশিমালা, ret.মান);
      C_MAYBE_CONST_রাশিমালা_NON_CONST (ret.মান) = !type_রাশিমালা_const;
    }
  বের_করো_maybe_used (type != error_mark_গ্রন্থি ? শীর্ষ_array_vla_p (type) : মিথ্যা);
  ফেরত ret;
}

/* Return the result of maxof applied to T, a structure for the type
   name passed to maxof (rather than the type itself).  LOC is the
   location of the original expression.  */

কাঠামো c_রাশিমালা
c_রাশিমালা_maxof_type (location_t loc, কাঠামো c_type_name *t)
{
  বৃক্ষ type;
  কাঠামো c_রাশিমালা ret;
  বৃক্ষ type_রাশিমালা = NULL_বৃক্ষ;
  যৌক্তিক type_রাশিমালা_const = সত্য;
  type = groktypename (t, &type_রাশিমালা, &type_রাশিমালা_const);
  ret.মান = c_maxof_type (loc, type);
  c_last_sizeof_arg = type;
  c_last_sizeof_loc = loc;
  ret.original_code = MAXOF_রাশিমালা;
  ret.original_type = ফাঁকা;
  ret.m_decimal = 0;
  যদি (type == error_mark_গ্রন্থি)
    {
      ret.মান = error_mark_গ্রন্থি;
      ret.original_code = ERROR_MARK;
    }
  বের_করো_maybe_used (type != error_mark_গ্রন্থি);
  ফেরত ret;
}

/* Return the result of minof applied to T, a structure for the type
   name passed to minof (rather than the type itself).  LOC is the
   location of the original expression.  */

কাঠামো c_রাশিমালা
c_রাশিমালা_minof_type (location_t loc, কাঠামো c_type_name *t)
{
  বৃক্ষ type;
  কাঠামো c_রাশিমালা ret;
  বৃক্ষ type_রাশিমালা = NULL_বৃক্ষ;
  যৌক্তিক type_রাশিমালা_const = সত্য;
  type = groktypename (t, &type_রাশিমালা, &type_রাশিমালা_const);
  ret.মান = c_minof_type (loc, type);
  c_last_sizeof_arg = type;
  c_last_sizeof_loc = loc;
  ret.original_code = MINOF_রাশিমালা;
  ret.original_type = ফাঁকা;
  ret.m_decimal = 0;
  যদি (type == error_mark_গ্রন্থি)
    {
      ret.মান = error_mark_গ্রন্থি;
      ret.original_code = ERROR_MARK;
    }
  বের_করো_maybe_used (type != error_mark_গ্রন্থি);
  ফেরত ret;
}

/* Build a function call to function FUNCTION with parameters PARAMS.
   The function call is at LOC.
   PARAMS is a list--a chain of TREE_LIST nodes--in which the
   TREE_VALUE of each node is a parameter-expression.
   FUNCTION's data type may be a function type or a pointer-to-function.  */

বৃক্ষ
build_function_call (location_t loc, বৃক্ষ function, বৃক্ষ params)
{
  vec<বৃক্ষ, va_gc> *v;
  বৃক্ষ ret;

  vec_alloc (v, list_দৈর্ঘ্য (params));
  জন্য (; params; params = বৃক্ষ_CHAIN (params))
    v->quick_ঠেলো (বৃক্ষ_মান (params));
  ret = c_build_function_call_vec (loc, vNULL, function, v, ফাঁকা);
  vec_free (v);
  ফেরত ret;
}

/* Give a note about the location of the declaration of DECL,
   or, failing that, a pertinent declaration for FUNCTION_EXPR.  */

স্থির শূন্য
inform_declaration (বৃক্ষ decl, বৃক্ষ function_রাশিমালা)
{
  যদি (decl && (বৃক্ষ_CODE (decl) != FUNCTION_DECL
	       || !DECL_IS_UNDECLARED_BUILTIN (decl)))
    inform (DECL_SOURCE_LOCATION (decl), "declared here");
  অন্যথা যদি (function_রাশিমালা)
    নির্বাচন (বৃক্ষ_CODE (function_রাশিমালা))
      {
      পূর্বনির্ধারিত:
	বিরতি;
      ক্ষেত্র COMPONENT_REF:
	/* Show the decl of the pertinent field (e.g. for callback
	   fields in a struct.  */
	{
	  বৃক্ষ field_decl = বৃক্ষ_OPERAND (function_রাশিমালা, 1);
	  যদি (location_t loc = DECL_SOURCE_LOCATION (field_decl))
	    inform (loc, "declared here");
	}
	বিরতি;
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

বৃক্ষ
build_function_call_vec (location_t loc, vec<location_t> arg_loc,
			 বৃক্ষ function, vec<বৃক্ষ, va_gc> *params,
			 vec<বৃক্ষ, va_gc> *origtypes, বৃক্ষ orig_fundecl)
{
  বৃক্ষ fntype, fundecl = NULL_বৃক্ষ;
  বৃক্ষ name = NULL_বৃক্ষ, ফলাফল;
  বৃক্ষ tem;
  পূর্ণসংখ্যা nargs;
  বৃক্ষ *argarray;


  /* Strip NON_LVALUE_EXPRs, etc., since we aren't using as an lvalue.  */
  STRIP_TYPE_NOPS (function);

  /* Convert anything with function type to a pointer-to-function.  */
  যদি (বৃক্ষ_CODE (function) == FUNCTION_DECL)
    {
      name = DECL_NAME (function);

      যদি (flag_tm)
	tm_malloc_replacement (function);
      fundecl = function;
      যদি (!orig_fundecl)
	orig_fundecl = fundecl;
      /* Atomic functions have type checking/casting already done.  They are
	 often rewritten and don't match the original parameter list.  */
      যদি (name && startswith (IDENTIFIER_POINTER (name), "__atomic_"))
        origtypes = ফাঁকা;
    }
  যদি (বৃক্ষ_CODE (বৃক্ষ_TYPE (function)) == FUNCTION_TYPE)
    function = function_to_pointer_conversion (loc, function);

  /* For Objective-C, convert any calls via a cast to OBJC_TYPE_REF
     expressions, like those used for ObjC messenger dispatches.  */
  যদি (params && !params->is_empty ())
    function = objc_rewrite_function_call (function, (*params)[0]);

  function = c_fully_fold (function, মিথ্যা, ফাঁকা);

  fntype = বৃক্ষ_TYPE (function);

  যদি (বৃক্ষ_CODE (fntype) == ERROR_MARK)
    ফেরত error_mark_গ্রন্থি;

  যদি (!(বৃক্ষ_CODE (fntype) == POINTER_TYPE
	&& বৃক্ষ_CODE (বৃক্ষ_TYPE (fntype)) == FUNCTION_TYPE))
    {
      যদি (!flag_diagnostics_show_caret && !STATEMENT_CLASS_P (function))
	error_at (loc,
		  "called object %qE is not a function or function pointer",
		  function);
      অন্যথা যদি (DECL_P (function))
	{
	  auto_diagnostic_group d;
	  error_at (loc,
		    "called object %qD is not a function or function pointer",
		    function);
	  inform_declaration (function, NULL_বৃক্ষ);
	}
      অন্যথা
	error_at (loc,
		  "called object is not a function or function pointer");
      ফেরত error_mark_গ্রন্থি;
    }

  যদি (fundecl && বৃক্ষ_THIS_VOLATILE (fundecl))
    current_function_returns_abnormally = 1;

  /* fntype now gets the type of function pointed to.  */
  fntype = বৃক্ষ_TYPE (fntype);
  বৃক্ষ return_type = বৃক্ষ_TYPE (fntype);

  /* Convert the parameters to the types declared in the
     function prototype, or apply default promotions.  */

  nargs = convert_arguments (loc, arg_loc, fntype, params,
			     origtypes, function, fundecl);
  যদি (nargs < 0)
    ফেরত error_mark_গ্রন্থি;

  /* Check that the function is called through a compatible prototype.
     If it is not, warn.  */
  যদি (CONVERT_রাশিমালা_P (function)
      && বৃক্ষ_CODE (tem = বৃক্ষ_OPERAND (function, 0)) == ADDR_রাশিমালা
      && বৃক্ষ_CODE (tem = বৃক্ষ_OPERAND (tem, 0)) == FUNCTION_DECL
      && !comptypes (fntype, বৃক্ষ_TYPE (tem)))
    {
      /* This situation leads to run-time undefined behavior.  We can't,
	 therefore, simply error unless we can prove that all possible
	 executions of the program must execute the code.  */
      warning_at (loc, 0, "function called through a non-compatible type");

      যদি (VOID_TYPE_P (return_type)
	  && TYPE_QUALS (return_type) != TYPE_UNQUALIFIED)
	pedwarn (loc, 0,
		 "function with qualified void return type called");
     }

  argarray = vec_safe_address (params);

  /* Check that arguments to builtin functions match the expectations.  */
  যদি (fundecl
      && fndecl_built_in_p (fundecl)
      && !check_builtin_function_arguments (loc, arg_loc, fundecl,
					    orig_fundecl, nargs, argarray))
    ফেরত error_mark_গ্রন্থি;

  /* Check that the arguments to the function are valid.  */
  যৌক্তিক warned_p = check_function_arguments (loc, fundecl, fntype,
					    nargs, argarray, &arg_loc,
					    comptypes);

  যদি (TYPE_QUALS (return_type) != TYPE_UNQUALIFIED
      && !VOID_TYPE_P (return_type))
    return_type = c_build_qualified_type (return_type, TYPE_UNQUALIFIED);
  যদি (name != NULL_বৃক্ষ
      && startswith (IDENTIFIER_POINTER (name), "__builtin_"))
    {
      যদি (require_constant_মান)
	ফলাফল
	  = fold_build_call_array_initializer_loc (loc, return_type,
						   function, nargs, argarray);
      অন্যথা
	ফলাফল = fold_build_call_array_loc (loc, return_type,
					    function, nargs, argarray);
      যদি (বৃক্ষ_CODE (ফলাফল) == NOP_রাশিমালা
	  && বৃক্ষ_CODE (বৃক্ষ_OPERAND (ফলাফল, 0)) == INTEGER_CST)
	STRIP_TYPE_NOPS (ফলাফল);
    }
  অন্যথা
    ফলাফল = build_call_array_loc (loc, return_type,
				   function, nargs, argarray);
  /* If -Wnonnull warning has been diagnosed, avoid diagnosing it again
     later.  */
  যদি (warned_p && বৃক্ষ_CODE (ফলাফল) == CALL_রাশিমালা)
    suppress_warning (ফলাফল, OPT_Wnonnull);

  /* In this improbable scenario, a nested function returns a VM type.
     Create a TARGET_EXPR so that the call always has a LHS, much as
     what the C++ FE does for functions returning non-PODs.  */
  যদি (c_type_variably_modified_p (বৃক্ষ_TYPE (fntype)))
    {
      বৃক্ষ tmp = create_tmp_var_raw (বৃক্ষ_TYPE (fntype));
      ফলাফল = build4 (TARGET_রাশিমালা, বৃক্ষ_TYPE (fntype), tmp, ফলাফল,
		       NULL_বৃক্ষ, NULL_বৃক্ষ);
    }

  যদি (VOID_TYPE_P (বৃক্ষ_TYPE (ফলাফল)))
    {
      যদি (TYPE_QUALS (বৃক্ষ_TYPE (ফলাফল)) != TYPE_UNQUALIFIED)
	pedwarn (loc, 0,
		 "function with qualified void return type called");
      ফেরত ফলাফল;
    }
  ফেরত require_complete_type (loc, ফলাফল);
}

/* Like build_function_call_vec, but call also resolve_overloaded_builtin.  */

বৃক্ষ
c_build_function_call_vec (location_t loc, ধ্রুবক vec<location_t> &arg_loc,
			   বৃক্ষ function, vec<বৃক্ষ, va_gc> *params,
			   vec<বৃক্ষ, va_gc> *origtypes)
{
  /* Strip NON_LVALUE_EXPRs, etc., since we aren't using as an lvalue.  */
  STRIP_TYPE_NOPS (function);

  /* Convert anything with function type to a pointer-to-function.  */
  যদি (বৃক্ষ_CODE (function) == FUNCTION_DECL)
    {
      /* Implement type-directed function overloading for builtins.
	 resolve_overloaded_builtin and targetm.resolve_overloaded_builtin
	 handle all the type checking.  The result is a complete expression
	 that implements this function call.  */
      বৃক্ষ tem = resolve_overloaded_builtin (loc, function, params);
      যদি (tem)
	ফেরত tem;
    }
  ফেরত build_function_call_vec (loc, arg_loc, function, params, origtypes);
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

স্থির বৃক্ষ
convert_argument (location_t ploc, বৃক্ষ function, বৃক্ষ fundecl,
		  বৃক্ষ type, বৃক্ষ origtype, বৃক্ষ val, বৃক্ষ valtype,
		  যৌক্তিক npc, বৃক্ষ rname, পূর্ণসংখ্যা parmnum, পূর্ণসংখ্যা argnum,
		  যৌক্তিক excess_precision, পূর্ণসংখ্যা warnopt)
{
  /* Formal parm type is specified by a function prototype.  */

  যদি (type == error_mark_গ্রন্থি || !COMPLETE_TYPE_P (type))
    {
      error_at (ploc, "type of formal parameter %d is incomplete",
		parmnum + 1);
      ফেরত error_mark_গ্রন্থি;
    }

  /* Optionally warn about conversions that differ from the default
     conversions.  */
  যদি (warn_traditional_conversion || warn_traditional)
    {
      যদি (INTEGRAL_TYPE_P (type)
	  && SCALAR_FLOAT_TYPE_P (valtype))
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as integer rather "
		    "than floating due to prototype",
		    argnum, rname);
      যদি (INTEGRAL_TYPE_P (type)
	  && বৃক্ষ_CODE (valtype) == COMPLEX_TYPE)
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as integer rather "
		    "than complex due to prototype",
		    argnum, rname);
      অন্যথা যদি (বৃক্ষ_CODE (type) == COMPLEX_TYPE
	       && SCALAR_FLOAT_TYPE_P (valtype))
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as complex rather "
		    "than floating due to prototype",
		    argnum, rname);
      অন্যথা যদি (SCALAR_FLOAT_TYPE_P (type)
	       && INTEGRAL_TYPE_P (valtype))
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as floating rather "
		    "than integer due to prototype",
		    argnum, rname);
      অন্যথা যদি (বৃক্ষ_CODE (type) == COMPLEX_TYPE
	       && INTEGRAL_TYPE_P (valtype))
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as complex rather "
		    "than integer due to prototype",
		    argnum, rname);
      অন্যথা যদি (SCALAR_FLOAT_TYPE_P (type)
	       && বৃক্ষ_CODE (valtype) == COMPLEX_TYPE)
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as floating rather "
		    "than complex due to prototype",
		    argnum, rname);
      /* ??? At some point, messages should be written about
	 conversions between complex types, but that's too messy
	 to do now.  */
      অন্যথা যদি (SCALAR_FLOAT_TYPE_P (type)
	       && SCALAR_FLOAT_TYPE_P (valtype))
	{
	  unsigned পূর্ণসংখ্যা formal_prec = TYPE_PRECISION (type);

	  /* Warn if any argument is passed as `float',
	     since without a prototype it would be `double'.  */
	  যদি (formal_prec == TYPE_PRECISION (float_type_গ্রন্থি)
	      && type != dfloat32_type_গ্রন্থি)
	    warning_at (ploc, 0,
			"passing argument %d of %qE as %<float%> "
			"rather than %<double%> due to prototype",
			argnum, rname);

	  /* Warn if mismatch between argument and prototype
	     for decimal float types.  Warn of conversions with
	     binary float types and of precision narrowing due to
	     prototype.  */
	  অন্যথা যদি (type != valtype
		   && (type == dfloat32_type_গ্রন্থি
		       || type == dfloat64_type_গ্রন্থি
		       || type == dfloat128_type_গ্রন্থি
		       || valtype == dfloat32_type_গ্রন্থি
		       || valtype == dfloat64_type_গ্রন্থি
		       || valtype == dfloat128_type_গ্রন্থি)
		   && (formal_prec
		       <= TYPE_PRECISION (valtype)
		       || (type == dfloat128_type_গ্রন্থি
			   && (valtype
			       != dfloat64_type_গ্রন্থি
			       && (valtype
				   != dfloat32_type_গ্রন্থি)))
		       || (type == dfloat64_type_গ্রন্থি
			   && (valtype
			       != dfloat32_type_গ্রন্থি))))
	    warning_at (ploc, 0,
			"passing argument %d of %qE as %qT "
			"rather than %qT due to prototype",
			argnum, rname, type, valtype);

	}
      /* Detect integer changing in width or signedness.
	 These warnings are only activated with
	 -Wtraditional-conversion, not with -Wtraditional.  */
      অন্যথা যদি (warn_traditional_conversion
	       && INTEGRAL_TYPE_P (type)
	       && INTEGRAL_TYPE_P (valtype))
	{
	  unsigned পূর্ণসংখ্যা formal_prec = TYPE_PRECISION (type);
	  বৃক্ষ would_have_been = default_conversion (val);
	  বৃক্ষ type1 = বৃক্ষ_TYPE (would_have_been);

	  যদি (val == error_mark_গ্রন্থি)
	    /* VAL could have been of incomplete type.  */;
	  অন্যথা যদি (বৃক্ষ_CODE (type) == ENUMERAL_TYPE
		   && (TYPE_MAIN_VARIANT (type)
		       == TYPE_MAIN_VARIANT (valtype)))
	    /* No warning if function asks for enum
	       and the actual arg is that enum type.  */
	    ;
	  অন্যথা যদি (formal_prec != TYPE_PRECISION (type1))
	    warning_at (ploc, OPT_Wtraditional_conversion,
			"passing argument %d of %qE "
			"with different width due to prototype",
			argnum, rname);
	  অন্যথা যদি (TYPE_UNSIGNED (type) == TYPE_UNSIGNED (type1))
	    ;
	  /* Don't complain if the formal parameter type
	     is an enum, because we can't tell now whether
	     the value was an enum--even the same enum.  */
	  অন্যথা যদি (বৃক্ষ_CODE (type) == ENUMERAL_TYPE)
	    ;
	  অন্যথা যদি (বৃক্ষ_CODE (val) == INTEGER_CST
		   && int_fits_type_p (val, type))
	    /* Change in signedness doesn't matter
	       if a constant value is unaffected.  */
	    ;
	  /* If the value is extended from a narrower
	     unsigned type, it doesn't matter whether we
	     pass it as signed or unsigned; the value
	     certainly is the same either way.  */
	  অন্যথা যদি (TYPE_PRECISION (valtype) < TYPE_PRECISION (type)
		   && TYPE_UNSIGNED (valtype))
	    ;
	  অন্যথা যদি (TYPE_UNSIGNED (type))
	    warning_at (ploc, OPT_Wtraditional_conversion,
			"passing argument %d of %qE "
			"as unsigned due to prototype",
			argnum, rname);
	  অন্যথা
	    warning_at (ploc, OPT_Wtraditional_conversion,
			"passing argument %d of %qE "
			"as signed due to prototype",
			argnum, rname);
	}
    }

  /* Possibly restore an EXCESS_PRECISION_EXPR for the
     sake of better warnings from convert_and_check.  */
  যদি (excess_precision)
    val = build1 (EXCESS_PRECISION_রাশিমালা, valtype, val);

  বৃক্ষ parmval = convert_for_assignment (ploc, ploc, type,
					 val, origtype, ic_argpass,
					 npc, fundecl, function,
					 parmnum + 1, warnopt);
  ফেরত parmval;
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

স্থির পূর্ণসংখ্যা
convert_arguments (location_t loc, vec<location_t> arg_loc, বৃক্ষ fntype,
		   vec<বৃক্ষ, va_gc> *মানসমূহ, vec<বৃক্ষ, va_gc> *origtypes,
		   বৃক্ষ function, বৃক্ষ fundecl)
{
  বৃক্ষ typelist = TYPE_ARG_TYPES (fntype);
  unsigned পূর্ণসংখ্যা parmnum;
  যৌক্তিক error_args = মিথ্যা;
  ধ্রুবক যৌক্তিক type_generic = fundecl
    && lookup_attribute ("type generic", TYPE_ATTRIBUTES (বৃক্ষ_TYPE (fundecl)));
  যৌক্তিক type_generic_remove_excess_precision = মিথ্যা;
  যৌক্তিক type_generic_overflow_p = মিথ্যা;
  যৌক্তিক type_generic_bit_query = মিথ্যা;
  বৃক্ষ selector;

  /* Change pointer to function to the function itself for
     diagnostics.  */
  যদি (বৃক্ষ_CODE (function) == ADDR_রাশিমালা
      && বৃক্ষ_CODE (বৃক্ষ_OPERAND (function, 0)) == FUNCTION_DECL)
    function = বৃক্ষ_OPERAND (function, 0);

  /* Handle an ObjC selector specially for diagnostics.  */
  selector = objc_message_selector ();

  /* For a call to a built-in function declared without a prototype,
     set to the built-in function's argument list.  */
  বৃক্ষ builtin_typelist = NULL_বৃক্ষ;

  /* For type-generic built-in functions, determine whether excess
     precision should be removed (classification) or not
     (comparison).  */
  যদি (fundecl
      && fndecl_built_in_p (fundecl, BUILT_IN_NORMAL))
    {
      built_in_function code = DECL_FUNCTION_CODE (fundecl);
      যদি (C_DECL_BUILTIN_PROTOTYPE (fundecl))
	{
	  /* For a call to a built-in function declared without a prototype
	     use the types of the parameters of the internal built-in to
	     match those of the arguments to.  */
	  যদি (বৃক্ষ bdecl = builtin_decl_explicit (code))
	    builtin_typelist = TYPE_ARG_TYPES (বৃক্ষ_TYPE (bdecl));
	}

      /* For type-generic built-in functions, determine whether excess
	 precision should be removed (classification) or not
	 (comparison).  */
      যদি (type_generic)
	নির্বাচন (code)
	  {
	  ক্ষেত্র BUILT_IN_ISFINITE:
	  ক্ষেত্র BUILT_IN_ISINF:
	  ক্ষেত্র BUILT_IN_ISINF_SIGN:
	  ক্ষেত্র BUILT_IN_ISNAN:
	  ক্ষেত্র BUILT_IN_ISNORMAL:
	  ক্ষেত্র BUILT_IN_ISSIGNALING:
	  ক্ষেত্র BUILT_IN_FPCLASSIFY:
	    type_generic_remove_excess_precision = সত্য;
	    বিরতি;

	  ক্ষেত্র BUILT_IN_ADD_OVERFLOW_P:
	  ক্ষেত্র BUILT_IN_SUB_OVERFLOW_P:
	  ক্ষেত্র BUILT_IN_MUL_OVERFLOW_P:
	    /* The last argument of these type-generic builtins
	       should not be promoted.  */
	    type_generic_overflow_p = সত্য;
	    বিরতি;

	  ক্ষেত্র BUILT_IN_CLZG:
	  ক্ষেত্র BUILT_IN_CTZG:
	  ক্ষেত্র BUILT_IN_CLRSBG:
	  ক্ষেত্র BUILT_IN_FFSG:
	  ক্ষেত্র BUILT_IN_PARITYG:
	  ক্ষেত্র BUILT_IN_POPCOUNTG:
	    /* The first argument of these type-generic builtins
	       should not be promoted.  */
	    type_generic_bit_query = সত্য;
	    বিরতি;

	  পূর্বনির্ধারিত:
	    বিরতি;
	  }
    }

  /* Scan the given expressions (VALUES) and types (TYPELIST), producing
     individual converted arguments.  */

  বৃক্ষ typetail, builtin_typetail, val;
  জন্য (typetail = typelist,
	 builtin_typetail = builtin_typelist,
	 parmnum = 0;
       মানসমূহ && মানসমূহ->iterate (parmnum, &val);
       ++parmnum)
    {
      /* The type of the function parameter (if it was declared with one).  */
      বৃক্ষ type = typetail ? বৃক্ষ_মান (typetail) : NULL_বৃক্ষ;
      /* The type of the built-in function parameter (if the function
	 is a built-in).  Used to detect type incompatibilities in
	 calls to built-ins declared without a prototype.  */
      বৃক্ষ builtin_type = (builtin_typetail
			   ? বৃক্ষ_মান (builtin_typetail) : NULL_বৃক্ষ);
      /* The original type of the argument being passed to the function.  */
      বৃক্ষ valtype = বৃক্ষ_TYPE (val);
      /* The called function (or function selector in Objective C).  */
      বৃক্ষ rname = function;
      পূর্ণসংখ্যা argnum = parmnum + 1;
      ধ্রুবক অক্ষর *invalid_func_diag;
      /* Set for EXCESS_PRECISION_EXPR arguments.  */
      যৌক্তিক excess_precision = মিথ্যা;
      /* The value of the argument after conversion to the type
	 of the function parameter it is passed to.  */
      বৃক্ষ parmval;
      /* Some __atomic_* builtins have additional hidden argument at
	 position 0.  */
      location_t ploc
	= !arg_loc.is_empty () && মানসমূহ->দৈর্ঘ্য () == arg_loc.দৈর্ঘ্য ()
	  ? expansion_point_location_if_in_system_header (arg_loc[parmnum])
	  : প্রবেশ_location;

      যদি (type == void_type_গ্রন্থি)
	{
	  auto_diagnostic_group d;
	  পূর্ণসংখ্যা অঙ্ক_expected = parmnum;
	  পূর্ণসংখ্যা অঙ্ক_actual = মানসমূহ->দৈর্ঘ্য ();
	  gcc_rich_location rich_loc (loc);
	  যদি (ploc != প্রবেশ_location)
	    rich_loc.add_range (ploc);
	  যদি (selector)
	    error_at (&rich_loc,
		      "too many arguments to method %qE; expected %i, have %i",
		      selector, অঙ্ক_expected, অঙ্ক_actual);
	  অন্যথা
	    error_at (&rich_loc,
		      "too many arguments to function %qE; expected %i, have %i",
		      function, অঙ্ক_expected, অঙ্ক_actual);
	  inform_declaration (fundecl, function);
	  ফেরত error_args ? -1 : (পূর্ণসংখ্যা) parmnum;
	}

      যদি (builtin_type == void_type_গ্রন্থি)
	{
	  auto_diagnostic_group d;
	  যদি (warning_at (loc, OPT_Wbuiltin_declaration_mismatch,
			  "too many arguments to built-in function %qE "
			  "expecting %d", function, parmnum))
	    inform_declaration (fundecl, function);
	  builtin_typetail = NULL_বৃক্ষ;
	}

      যদি (!typetail && parmnum == 0 && !TYPE_NO_NAMED_ARGS_STDARG_P (fntype)
	  && !(fundecl && fndecl_built_in_p (fundecl)))
	{
	  auto_diagnostic_group d;
	  যৌক্তিক warned;
	  যদি (selector)
	    warned = warning_at (loc, OPT_Wdeprecated_non_prototype,
				 "ISO C23 does not allow arguments"
				 " for method %qE declared without parameters",
				 function);
	  অন্যথা
	    warned = warning_at (loc, OPT_Wdeprecated_non_prototype,
				 "ISO C23 does not allow arguments"
				 " for function %qE declared without parameters",
				 function);
	  যদি (warned)
	    inform_declaration (fundecl, function);
	}

      যদি (selector && argnum > 2)
	{
	  rname = selector;
	  argnum -= 2;
	}

      /* Determine if VAL is a null pointer constant before folding it.  */
      যৌক্তিক npc = null_pointer_constant_p (val);

      /* If there is excess precision and a prototype, convert once to
	 the required type rather than converting via the semantic
	 type.  Likewise without a prototype a float value represented
	 as long double should be converted once to double.  But for
	 type-generic classification functions excess precision must
	 be removed here.  */
      যদি (বৃক্ষ_CODE (val) == EXCESS_PRECISION_রাশিমালা
	  && (type || !type_generic || !type_generic_remove_excess_precision))
	{
	  val = বৃক্ষ_OPERAND (val, 0);
	  excess_precision = সত্য;
	}
      val = c_fully_fold (val, মিথ্যা, ফাঁকা);
      STRIP_TYPE_NOPS (val);

      val = require_complete_type (ploc, val);

      /* Some floating-point arguments must be promoted to double when
	 no type is specified by a prototype.  This applies to
	 arguments of type float, and to architecture-specific types
	 (ARM __fp16), but not to _FloatN or _FloatNx types.  */
      যৌক্তিক promote_float_arg = মিথ্যা;
      যদি (type == NULL_বৃক্ষ
	  && বৃক্ষ_CODE (valtype) == REAL_TYPE
	  && (TYPE_PRECISION (valtype)
	      <= TYPE_PRECISION (double_type_গ্রন্থি))
	  && TYPE_MAIN_VARIANT (valtype) != double_type_গ্রন্থি
	  && TYPE_MAIN_VARIANT (valtype) != long_double_type_গ্রন্থি
	  && !DECIMAL_FLOAT_MODE_P (TYPE_MODE (valtype)))
	{
	  /* Promote this argument, unless it has a _FloatN or
	     _FloatNx type.  */
	  promote_float_arg = সত্য;
	  জন্য (পূর্ণসংখ্যা i = 0; i < অঙ্ক_FLOATN_NX_TYPES; i++)
	    যদি (TYPE_MAIN_VARIANT (valtype) == FLOATN_NX_TYPE_গ্রন্থি (i))
	      {
		promote_float_arg = মিথ্যা;
		বিরতি;
	      }
	  /* Don't promote __bf16 either.  */
	  যদি (TYPE_MAIN_VARIANT (valtype) == bfloat16_type_গ্রন্থি)
	    promote_float_arg = মিথ্যা;
	}

      যদি (type != NULL_বৃক্ষ)
	{
	  বৃক্ষ origtype = (!origtypes) ? NULL_বৃক্ষ : (*origtypes)[parmnum];
	  parmval = convert_argument (ploc, function, fundecl, type, origtype,
				      val, valtype, npc, rname, parmnum, argnum,
				      excess_precision, 0);
	}
      /* A NULLPTR type is just a nullptr always.  */
      অন্যথা যদি (বৃক্ষ_CODE (বৃক্ষ_TYPE (val)) == NULLPTR_TYPE)
	parmval = omit_one_operand_loc (ploc, বৃক্ষ_TYPE (val), nullptr_গ্রন্থি, val);
      অন্যথা যদি (promote_float_arg)
        {
	  যদি (type_generic)
	    parmval = val;
	  অন্যথা
	    {
	      /* Convert `float' to `double'.  */
	      যদি (warn_double_promotion && !c_inhibit_evaluation_warnings)
		warning_at (ploc, OPT_Wdouble_promotion,
			    "implicit conversion from %qT to %qT when passing "
			    "argument to function",
			    valtype, double_type_গ্রন্থি);
	      parmval = convert (double_type_গ্রন্থি, val);
	    }
	}
      অন্যথা যদি ((excess_precision && !type_generic)
	       || (type_generic_overflow_p && parmnum == 2)
	       || (type_generic_bit_query && parmnum == 0))
	/* A "double" argument with excess precision being passed
	   without a prototype or in variable arguments.
	   The last argument of __builtin_*_overflow_p should not be
	   promoted, similarly the first argument of
	   __builtin_{clz,ctz,clrsb,ffs,parity,popcount}g.  */
	parmval = convert (valtype, val);
      অন্যথা যদি ((invalid_func_diag =
		targetm.calls.invalid_arg_for_unprototyped_fn (typelist, fundecl, val)))
	{
	  error (invalid_func_diag);
	  ফেরত -1;
	}
      অন্যথা যদি (বৃক্ষ_CODE (val) == ADDR_রাশিমালা && reject_gcc_builtin (val))
	{
	  ফেরত -1;
	}
      অন্যথা
	/* Convert `short' and `char' to full-size `int'.  */
	parmval = default_conversion (val);

      (*মানসমূহ)[parmnum] = parmval;
      যদি (parmval == error_mark_গ্রন্থি)
	error_args = সত্য;

      যদি (!type && builtin_type && বৃক্ষ_CODE (builtin_type) != VOID_TYPE)
	{
	  /* For a call to a built-in function declared without a prototype,
	     perform the conversions from the argument to the expected type
	     but issue warnings rather than errors for any mismatches.
	     Ignore the converted argument and use the PARMVAL obtained
	     above by applying default conversions instead.  */
	  বৃক্ষ origtype = (!origtypes) ? NULL_বৃক্ষ : (*origtypes)[parmnum];
	  convert_argument (ploc, function, fundecl, builtin_type, origtype,
			    val, valtype, npc, rname, parmnum, argnum,
			    excess_precision,
			    OPT_Wbuiltin_declaration_mismatch);
	}

      যদি (typetail)
	typetail = বৃক্ষ_CHAIN (typetail);

      যদি (builtin_typetail)
	builtin_typetail = বৃক্ষ_CHAIN (builtin_typetail);
    }

  gcc_assert (parmnum == vec_safe_দৈর্ঘ্য (মানসমূহ));

  যদি (typetail != NULL_বৃক্ষ && বৃক্ষ_মান (typetail) != void_type_গ্রন্থি)
    {
      /* Not enough args.
	 Determine minimum number of arguments required.  */
      পূর্ণসংখ্যা min_expected_অঙ্ক = 0;
      যৌক্তিক at_least_p = মিথ্যা;
      বৃক্ষ iter = typelist;
      যখন (সত্য)
	{
	  যদি (!iter)
	    {
	      /* Variadic arguments; stop iterating.  */
	      at_least_p = সত্য;
	      বিরতি;
	    }
	  যদি (iter == void_list_গ্রন্থি)
	    /* End of arguments; stop iterating.  */
	    বিরতি;
	  ++min_expected_অঙ্ক;
	  iter = বৃক্ষ_CHAIN (iter);
	}
      auto_diagnostic_group d;
      পূর্ণসংখ্যা actual_অঙ্ক = vec_safe_দৈর্ঘ্য (মানসমূহ);
      error_at (loc,
		at_least_p
		? G_("too few arguments to function %qE; expected at least %i, have %i")
		: G_("too few arguments to function %qE; expected %i, have %i"),
		function, min_expected_অঙ্ক, actual_অঙ্ক);
      inform_declaration (fundecl, function);
      ফেরত -1;
    }

  যদি (builtin_typetail && বৃক্ষ_মান (builtin_typetail) != void_type_গ্রন্থি)
    {
      unsigned nargs = parmnum;
      জন্য (বৃক্ষ t = builtin_typetail; t; t = বৃক্ষ_CHAIN (t))
	++nargs;

      auto_diagnostic_group d;
      যদি (warning_at (loc, OPT_Wbuiltin_declaration_mismatch,
		      "too few arguments to built-in function %qE "
		      "expecting %u", function, nargs - 1))
	inform_declaration (fundecl, function);
    }

  ফেরত error_args ? -1 : (পূর্ণসংখ্যা) parmnum;
}

/* This is the entry point used by the parser to build unary operators
   in the input.  CODE, a tree_code, specifies the unary operator, and
   ARG is the operand.  For unary plus, the C parser currently uses
   CONVERT_EXPR for code.

   LOC is the location to use for the tree generated.
*/

কাঠামো c_রাশিমালা
parser_build_unary_op (location_t loc, গণনা বৃক্ষ_code code, কাঠামো c_রাশিমালা arg)
{
  কাঠামো c_রাশিমালা ফলাফল;

  ফলাফল.original_code = code;
  ফলাফল.original_type = ফাঁকা;
  ফলাফল.m_decimal = 0;

  যদি (reject_gcc_builtin (arg.মান))
    {
      ফলাফল.মান = error_mark_গ্রন্থি;
    }
  অন্যথা
    {
      ফলাফল.মান = build_unary_op (loc, code, arg.মান, মিথ্যা);

      যদি (বৃক্ষ_OVERFLOW_P (ফলাফল.মান) && !বৃক্ষ_OVERFLOW_P (arg.মান))
	overflow_warning (loc, ফলাফল.মান, arg.মান);
    }

  /* We are typically called when parsing a prefix token at LOC acting on
     ARG.  Reflect this by updating the source range of the result to
     start at LOC and end at the end of ARG.  */
  set_c_রাশিমালা_source_range (&ফলাফল,
			   loc, arg.get_finish ());

  ফেরত ফলাফল;
}

/* Returns true if TYPE is a character type, *not* including wchar_t.  */

যৌক্তিক
char_type_p (বৃক্ষ type)
{
  ফেরত (type == char_type_গ্রন্থি
	  || type == unsigned_char_type_গ্রন্থি
	  || type == signed_char_type_গ্রন্থি
	  || type == char16_type_গ্রন্থি
	  || type == char32_type_গ্রন্থি);
}

/* This is the entry point used by the parser to build binary operators
   in the input.  CODE, a tree_code, specifies the binary operator, and
   ARG1 and ARG2 are the operands.  In addition to constructing the
   expression, we check for operands that were written with other binary
   operators in a way that is likely to confuse the user.  ORIG_ARG1 is
   the original first operand for TRUTH_{AND,OR}IF_EXPR before it is
   converted to truth value, otherwise NULL_TREE.

   LOCATION is the location of the binary operator.  */

কাঠামো c_রাশিমালা
parser_build_দ্বিমিক_op (location_t location, গণনা বৃক্ষ_code code,
			কাঠামো c_রাশিমালা arg1, কাঠামো c_রাশিমালা arg2, বৃক্ষ orig_arg1)
{
  কাঠামো c_রাশিমালা ফলাফল;
  ফলাফল.m_decimal = 0;

  গণনা বৃক্ষ_code code1 = arg1.original_code;
  গণনা বৃক্ষ_code code2 = arg2.original_code;
  বৃক্ষ type1 = (arg1.original_type
                ? arg1.original_type
                : বৃক্ষ_TYPE (arg1.মান));
  বৃক্ষ type2 = (arg2.original_type
                ? arg2.original_type
                : বৃক্ষ_TYPE (arg2.মান));

  ফলাফল.মান = build_দ্বিমিক_op (location, code,
				  arg1.মান, arg2.মান, সত্য);
  ফলাফল.original_code = code;
  ফলাফল.original_type = ফাঁকা;
  ফলাফল.m_decimal = 0;

  যদি (বৃক্ষ_CODE (ফলাফল.মান) == ERROR_MARK)
    {
      set_c_রাশিমালা_source_range (&ফলাফল,
			       arg1.get_start (),
			       arg2.get_finish ());
      ফেরত ফলাফল;
    }

  যদি (location != UNKNOWN_LOCATION)
    protected_set_রাশিমালা_location (ফলাফল.মান, location);

  set_c_রাশিমালা_source_range (&ফলাফল,
			   arg1.get_start (),
			   arg2.get_finish ());

  /* Check for cases such as x+y<<z which users are likely
     to misinterpret.  */
  যদি (warn_parentheses)
    warn_about_parentheses (location, code, code1, arg1.মান, code2,
			    arg2.মান);

  যদি (warn_logical_op)
    warn_logical_operator (location, code, বৃক্ষ_TYPE (ফলাফল.মান),
			   code1, arg1.মান, code2, arg2.মান);

  যদি (warn_constant_logical_operand
      && (code == TRUTH_ANDIF_রাশিমালা || code == TRUTH_ORIF_রাশিমালা)
      && INTEGRAL_NB_TYPE_P (type1)
      && INTEGRAL_NB_TYPE_P (type2))
    {
      ধ্রুবক অক্ষর *name = code == TRUTH_ANDIF_রাশিমালা ? "&&" : "||";
      যদি (orig_arg1 == NULL_বৃক্ষ)
	orig_arg1 = arg1.মান;
      auto enum_other_than_0_1 = [] (বৃক্ষ type) {
	যদি (বৃক্ষ_CODE (type) != ENUMERAL_TYPE)
	  ফেরত মিথ্যা;
	জন্য (বৃক্ষ l = TYPE_মানসমূহ (type); l; l = বৃক্ষ_CHAIN (l))
	  {
	    বৃক্ষ v = DECL_INITIAL (বৃক্ষ_মান (l));
	    যদি (!integer_zerop (v) && !integer_onep (v))
	      ফেরত সত্য;
	  }
	ফেরত মিথ্যা;
      };
      auto diagnose_constant_logical_operand = [=] (বৃক্ষ val, বৃক্ষ type) {
	যদি (বৃক্ষ_CODE (val) != INTEGER_CST || integer_zerop (val))
	  ফেরত মিথ্যা;
	যদি (integer_onep (val) && !enum_other_than_0_1 (type))
	  ফেরত মিথ্যা;
	gcc_rich_location richloc (location);
	richloc.add_fixit_replace (name + 1);
	auto_diagnostic_group d;
	যদি (warning_at (location, OPT_Wconstant_logical_operand,
			"use of logical %qs with constant operand %qE",
			name, val))
	  inform (&richloc, "use %qs for bitwise operation", name + 1);
	ফেরত সত্য;
      };
      যদি (!diagnose_constant_logical_operand (arg2.মান, type2))
	diagnose_constant_logical_operand (orig_arg1, type1);
    }

  যদি (warn_tautological_compare)
    {
      বৃক্ষ lhs = arg1.মান;
      বৃক্ষ rhs = arg2.মান;
      যদি (বৃক্ষ_CODE (lhs) == C_MAYBE_CONST_রাশিমালা)
	{
	  যদি (C_MAYBE_CONST_রাশিমালা_PRE (lhs) != NULL_বৃক্ষ
	      && বৃক্ষ_SIDE_EFFECTS (C_MAYBE_CONST_রাশিমালা_PRE (lhs)))
	    lhs = NULL_বৃক্ষ;
	  অন্যথা
	    lhs = C_MAYBE_CONST_রাশিমালা_রাশিমালা (lhs);
	}
      যদি (বৃক্ষ_CODE (rhs) == C_MAYBE_CONST_রাশিমালা)
	{
	  যদি (C_MAYBE_CONST_রাশিমালা_PRE (rhs) != NULL_বৃক্ষ
	      && বৃক্ষ_SIDE_EFFECTS (C_MAYBE_CONST_রাশিমালা_PRE (rhs)))
	    rhs = NULL_বৃক্ষ;
	  অন্যথা
	    rhs = C_MAYBE_CONST_রাশিমালা_রাশিমালা (rhs);
	}
      যদি (lhs != NULL_বৃক্ষ && rhs != NULL_বৃক্ষ)
	warn_tautological_cmp (location, code, lhs, rhs);
    }

  যদি (warn_logical_not_paren
      && বৃক্ষ_CODE_CLASS (code) == tcc_comparison
      && code1 == TRUTH_NOT_রাশিমালা
      && code2 != TRUTH_NOT_রাশিমালা
      /* Avoid warning for !!x == y.  */
      && (বৃক্ষ_CODE (arg1.মান) != NE_রাশিমালা
	  || !integer_zerop (বৃক্ষ_OPERAND (arg1.মান, 1))))
    {
      /* Avoid warning for !b == y where b has _Bool type.  */
      বৃক্ষ t = integer_zero_গ্রন্থি;
      যদি (বৃক্ষ_CODE (arg1.মান) == EQ_রাশিমালা
	  && integer_zerop (বৃক্ষ_OPERAND (arg1.মান, 1))
	  && বৃক্ষ_TYPE (বৃক্ষ_OPERAND (arg1.মান, 0)) == integer_type_গ্রন্থি)
	{
	  t = বৃক্ষ_OPERAND (arg1.মান, 0);
	  করো
	    {
	      যদি (বৃক্ষ_TYPE (t) != integer_type_গ্রন্থি)
		বিরতি;
	      যদি (বৃক্ষ_CODE (t) == C_MAYBE_CONST_রাশিমালা)
		t = C_MAYBE_CONST_রাশিমালা_রাশিমালা (t);
	      অন্যথা যদি (CONVERT_রাশিমালা_P (t))
		t = বৃক্ষ_OPERAND (t, 0);
	      অন্যথা
		বিরতি;
	    }
	  যখন (1);
	}
      যদি (!C_BOOLEAN_TYPE_P (বৃক্ষ_TYPE (t)))
	warn_logical_not_parentheses (location, code, arg1.মান, arg2.মান);
    }

  /* Warn about comparisons against string literals, with the exception
     of testing for equality or inequality of a string literal with NULL.  */
  যদি (code == EQ_রাশিমালা || code == NE_রাশিমালা)
    {
      যদি ((code1 == STRING_CST
	   && !integer_zerop (বৃক্ষ_strip_nop_conversions (arg2.মান)))
	  || (code2 == STRING_CST
	      && !integer_zerop (বৃক্ষ_strip_nop_conversions (arg1.মান))))
	warning_at (location, OPT_Waddress,
		    "comparison with string literal results in unspecified behavior");
      /* Warn for ptr == '\0', it's likely that it should've been ptr[0].  */
      যদি (POINTER_TYPE_P (type1)
	  && null_pointer_constant_p (arg2.মান)
	  && char_type_p (type2))
	{
	  auto_diagnostic_group d;
	  যদি (warning_at (location, OPT_Wpointer_compare,
			    "comparison between pointer and zero character "
			    "constant"))
	    inform (arg1.get_start (),
		      "did you mean to dereference the pointer?");
	}
      অন্যথা যদি (POINTER_TYPE_P (type2)
	       && null_pointer_constant_p (arg1.মান)
	       && char_type_p (type1))
	{
	  auto_diagnostic_group d;
	  যদি (warning_at (location, OPT_Wpointer_compare,
			    "comparison between pointer and zero character "
			    "constant"))
	    inform (arg2.get_start (),
		      "did you mean to dereference the pointer?");
	}
    }
  অন্যথা যদি (বৃক্ষ_CODE_CLASS (code) == tcc_comparison
	   && (code1 == STRING_CST || code2 == STRING_CST))
    warning_at (location, OPT_Waddress,
		"comparison with string literal results in unspecified "
		"behavior");

  যদি (warn_zero_as_null_pointer_constant
      && c_inhibit_evaluation_warnings == 0
      && বৃক্ষ_CODE_CLASS (code) == tcc_comparison)
    {
      যদি ((বৃক্ষ_CODE (type1) == POINTER_TYPE
	   || বৃক্ষ_CODE (type1) == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type2)
	  && null_pointer_constant_p (arg2.মান))
	warning_at (arg2.get_location(), OPT_Wzero_as_null_pointer_constant,
		    "zero as null pointer constant");

      যদি ((বৃক্ষ_CODE (type2) == POINTER_TYPE
	   || বৃক্ষ_CODE (type2) == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type1)
	  && null_pointer_constant_p (arg1.মান))
	warning_at (arg1.get_location(), OPT_Wzero_as_null_pointer_constant,
		    "zero as null pointer constant");
    }

  যদি (warn_array_compare
      && বৃক্ষ_CODE_CLASS (code) == tcc_comparison
      && বৃক্ষ_CODE (type1) == ARRAY_TYPE
      && বৃক্ষ_CODE (type2) == ARRAY_TYPE)
    do_warn_array_compare (location, code, arg1.মান, arg2.মান);

  যদি (বৃক্ষ_OVERFLOW_P (ফলাফল.মান)
      && !বৃক্ষ_OVERFLOW_P (arg1.মান)
      && !বৃক্ষ_OVERFLOW_P (arg2.মান))
    overflow_warning (location, ফলাফল.মান);

  /* Warn about comparisons of different enum types.  */
  যদি (warn_enum_compare
      && বৃক্ষ_CODE_CLASS (code) == tcc_comparison
      && বৃক্ষ_CODE (type1) == ENUMERAL_TYPE
      && বৃক্ষ_CODE (type2) == ENUMERAL_TYPE
      && TYPE_MAIN_VARIANT (type1) != TYPE_MAIN_VARIANT (type2))
    warning_at (location, OPT_Wenum_compare,
		"comparison between %qT and %qT",
		type1, type2);

  যদি (warn_xor_used_as_pow
      && code == BIT_XOR_রাশিমালা
      && arg1.m_decimal
      && arg2.m_decimal)
    check_for_xor_used_as_pow (arg1.get_location (), arg1.মান,
			       location,
			       arg2.get_location (), arg2.মান);

  ফেরত ফলাফল;
}

/* Return a tree for the difference of pointers OP0 and OP1.
   The resulting tree has type ptrdiff_t.  If POINTER_SUBTRACT sanitization is
   enabled, assign to INSTRUMENT_EXPR call to libsanitizer.  */

স্থির বৃক্ষ
pointer_diff (location_t loc, বৃক্ষ op0, বৃক্ষ op1, বৃক্ষ *instrument_রাশিমালা)
{
  বৃক্ষ restype = ptrdiff_type_গ্রন্থি;
  বৃক্ষ ফলাফল, inttype;

  addr_space_t as0 = TYPE_ADDR_SPACE (বৃক্ষ_TYPE (বৃক্ষ_TYPE (op0)));
  addr_space_t as1 = TYPE_ADDR_SPACE (বৃক্ষ_TYPE (বৃক্ষ_TYPE (op1)));
  বৃক্ষ target_type = বৃক্ষ_TYPE (বৃক্ষ_TYPE (op0));
  বৃক্ষ orig_op0 = op0;
  বৃক্ষ orig_op1 = op1;

  /* If the operands point into different address spaces, we need to
     explicitly convert them to pointers into the common address space
     before we can subtract the numerical address values.  */
  যদি (as0 != as1)
    {
      addr_space_t as_common;
      বৃক্ষ common_type;

      /* Determine the common superset address space.  This is guaranteed
	 to exist because the caller verified that comp_target_types
	 returned non-zero.  */
      যদি (!addr_space_superset (as0, as1, &as_common))
	gcc_unreachable ();

      common_type = common_pointer_type (বৃক্ষ_TYPE (op0), বৃক্ষ_TYPE (op1), NULL_বৃক্ষ);
      op0 = convert (common_type, op0);
      op1 = convert (common_type, op1);
    }

  /* Determine integer type result of the subtraction.  This will usually
     be the same as the result type (ptrdiff_t), but may need to be a wider
     type if pointers for the address space are wider than ptrdiff_t.  */
  যদি (TYPE_PRECISION (restype) < TYPE_PRECISION (বৃক্ষ_TYPE (op0)))
    inttype = c_common_type_for_আকার (TYPE_PRECISION (বৃক্ষ_TYPE (op0)), 0);
  অন্যথা
    inttype = restype;

  যদি (VOID_TYPE_P (target_type))
    pedwarn (loc, OPT_Wpointer_arith,
	     "pointer of type %<void *%> used in subtraction");
  যদি (বৃক্ষ_CODE (target_type) == FUNCTION_TYPE)
    pedwarn (loc, OPT_Wpointer_arith,
	     "pointer to a function used in subtraction");

  যদি (current_function_decl != NULL_বৃক্ষ
      && sanitize_flags_p (SANITIZE_POINTER_SUBTRACT))
    {
      op0 = save_রাশিমালা (c_fully_fold (op0, মিথ্যা, ফাঁকা));
      op1 = save_রাশিমালা (c_fully_fold (op1, মিথ্যা, ফাঁকা));

      বৃক্ষ tt = builtin_decl_explicit (BUILT_IN_ASAN_POINTER_SUBTRACT);
      *instrument_রাশিমালা = build_call_রাশিমালা_loc (loc, tt, 2, op0, op1);
    }

  /* First do the subtraction, then build the divide operator
     and only convert at the very end.
     Do not do default conversions in case restype is a short type.  */

  /* POINTER_DIFF_EXPR requires a signed integer type of the same size as
     pointers.  If some platform cannot provide that, or has a larger
     ptrdiff_type to support differences larger than half the address
     space, cast the pointers to some larger integer type and do the
     computations in that type.  */
  যদি (TYPE_PRECISION (inttype) > TYPE_PRECISION (বৃক্ষ_TYPE (op0)))
    op0 = build_দ্বিমিক_op (loc, MINUS_রাশিমালা, convert (inttype, op0),
			   convert (inttype, op1), মিথ্যা);
  অন্যথা
    {
      /* Cast away qualifiers.  */
      op0 = convert (c_common_type (বৃক্ষ_TYPE (op0), বৃক্ষ_TYPE (op0)), op0);
      op1 = convert (c_common_type (বৃক্ষ_TYPE (op1), বৃক্ষ_TYPE (op1)), op1);
      op0 = build2_loc (loc, POINTER_DIFF_রাশিমালা, inttype, op0, op1);
    }

  /* This generates an error if op1 is pointer to incomplete type.  */
  যদি (!COMPLETE_OR_VOID_TYPE_P (বৃক্ষ_TYPE (বৃক্ষ_TYPE (orig_op1))))
    error_at (loc, "arithmetic on pointer to an incomplete type");
  অন্যথা যদি (verify_type_context (loc, TCTX_POINTER_ARITH,
				বৃক্ষ_TYPE (বৃক্ষ_TYPE (orig_op0))))
    verify_type_context (loc, TCTX_POINTER_ARITH,
			 বৃক্ষ_TYPE (বৃক্ষ_TYPE (orig_op1)));

  op1 = c_আকার_in_bytes (target_type);

  যদি (pointer_to_zero_sized_aggr_p (বৃক্ষ_TYPE (orig_op1)))
    error_at (loc, "arithmetic on pointer to an empty aggregate");

  /* Divide by the size, in easiest possible way.  */
  ফলাফল = fold_build2_loc (loc, EXACT_DIV_রাশিমালা, inttype,
			    op0, convert (inttype, op1));

  /* Convert to final result type if necessary.  */
  ফেরত convert (restype, ফলাফল);
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

স্থির বৃক্ষ
build_atomic_assign (location_t loc, বৃক্ষ lhs, গণনা বৃক্ষ_code modifycode,
		     বৃক্ষ rhs, যৌক্তিক return_old_p)
{
  বৃক্ষ fndecl, func_call;
  vec<বৃক্ষ, va_gc> *params;
  বৃক্ষ val, nonatomic_lhs_type, nonatomic_rhs_type, newval, newval_addr;
  বৃক্ষ old, old_addr;
  বৃক্ষ compound_stmt = NULL_বৃক্ষ;
  বৃক্ষ stmt, goto_stmt;
  বৃক্ষ loop_label, loop_decl, done_label, done_decl;

  বৃক্ষ lhs_type = বৃক্ষ_TYPE (lhs);
  বৃক্ষ lhs_addr = build_unary_op (loc, ADDR_রাশিমালা, lhs, মিথ্যা);
  বৃক্ষ seq_cst = build_int_cst (integer_type_গ্রন্থি, MEMMODEL_SEQ_CST);
  বৃক্ষ rhs_semantic_type = বৃক্ষ_TYPE (rhs);
  বৃক্ষ nonatomic_rhs_semantic_type;
  বৃক্ষ rhs_type;

  gcc_assert (TYPE_ATOMIC (lhs_type));

  যদি (return_old_p)
    gcc_assert (modifycode == PLUS_রাশিমালা || modifycode == MINUS_রাশিমালা);

  /* Allocate enough vector items for a compare_exchange.  */
  vec_alloc (params, 6);

  /* Create a compound statement to hold the sequence of statements
     with a loop.  */
  যদি (modifycode != NOP_রাশিমালা)
    {
      compound_stmt = c_begin_compound_stmt (মিথ্যা);

      /* For consistency with build_modify_expr on non-_Atomic,
	 mark the lhs as read.  Also, it would be very hard to match
	 such expressions in mark_exp_read.  */
      mark_exp_read (lhs);
    }

  /* Remove any excess precision (which is only present here in the
     case of compound assignments).  */
  যদি (বৃক্ষ_CODE (rhs) == EXCESS_PRECISION_রাশিমালা)
    {
      gcc_assert (modifycode != NOP_রাশিমালা);
      rhs = বৃক্ষ_OPERAND (rhs, 0);
    }
  rhs_type = বৃক্ষ_TYPE (rhs);

  /* Fold the RHS if it hasn't already been folded.  */
  যদি (modifycode != NOP_রাশিমালা)
    rhs = c_fully_fold (rhs, মিথ্যা, ফাঁকা);

  /* Remove the qualifiers for the rest of the expressions and create
     the VAL temp variable to hold the RHS.  */
  nonatomic_lhs_type = build_qualified_type (lhs_type, TYPE_UNQUALIFIED);
  nonatomic_rhs_type = build_qualified_type (rhs_type, TYPE_UNQUALIFIED);
  nonatomic_rhs_semantic_type = build_qualified_type (rhs_semantic_type,
						      TYPE_UNQUALIFIED);
  val = create_tmp_var_raw (nonatomic_rhs_type);
  বৃক্ষ_ADDRESSABLE (val) = 1;
  suppress_warning (val);
  rhs = build4 (TARGET_রাশিমালা, nonatomic_rhs_type, val, rhs, NULL_বৃক্ষ,
		NULL_বৃক্ষ);
  বৃক্ষ_SIDE_EFFECTS (rhs) = 1;
  SET_রাশিমালা_LOCATION (rhs, loc);
  যদি (modifycode != NOP_রাশিমালা)
    add_stmt (rhs);

  /* NOP_EXPR indicates it's a straight store of the RHS. Simply issue
     an atomic_store.  */
  যদি (modifycode == NOP_রাশিমালা)
    {
      compound_stmt = rhs;
      /* Build __atomic_store (&lhs, &val, SEQ_CST)  */
      rhs = build_unary_op (loc, ADDR_রাশিমালা, val, মিথ্যা);
      fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_STORE);
      params->quick_ঠেলো (lhs_addr);
      params->quick_ঠেলো (rhs);
      params->quick_ঠেলো (seq_cst);
      func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, ফাঁকা);

      compound_stmt = build2 (COMPOUND_রাশিমালা, void_type_গ্রন্থি,
			      compound_stmt, func_call);

      /* VAL is the value which was stored, return a COMPOUND_STMT of
	 the statement and that value.  */
      ফেরত build2 (COMPOUND_রাশিমালা, nonatomic_lhs_type, compound_stmt, val);
    }

  /* Attempt to implement the atomic operation as an __atomic_fetch_* or
     __atomic_*_fetch built-in rather than a CAS loop.  atomic_bool type
     isn't applicable for such builtins.  ??? Do we want to handle enums?  */
  যদি ((বৃক্ষ_CODE (lhs_type) == INTEGER_TYPE || POINTER_TYPE_P (lhs_type))
      && বৃক্ষ_CODE (rhs_type) == INTEGER_TYPE)
    {
      built_in_function fncode;
      নির্বাচন (modifycode)
	{
	ক্ষেত্র PLUS_রাশিমালা:
	ক্ষেত্র POINTER_PLUS_রাশিমালা:
	  fncode = (return_old_p
		    ? BUILT_IN_ATOMIC_FETCH_ADD_N
		    : BUILT_IN_ATOMIC_ADD_FETCH_N);
	  বিরতি;
	ক্ষেত্র MINUS_রাশিমালা:
	  fncode = (return_old_p
		    ? BUILT_IN_ATOMIC_FETCH_SUB_N
		    : BUILT_IN_ATOMIC_SUB_FETCH_N);
	  বিরতি;
	ক্ষেত্র BIT_AND_রাশিমালা:
	  fncode = (return_old_p
		    ? BUILT_IN_ATOMIC_FETCH_AND_N
		    : BUILT_IN_ATOMIC_AND_FETCH_N);
	  বিরতি;
	ক্ষেত্র BIT_IOR_রাশিমালা:
	  fncode = (return_old_p
		    ? BUILT_IN_ATOMIC_FETCH_OR_N
		    : BUILT_IN_ATOMIC_OR_FETCH_N);
	  বিরতি;
	ক্ষেত্র BIT_XOR_রাশিমালা:
	  fncode = (return_old_p
		    ? BUILT_IN_ATOMIC_FETCH_XOR_N
		    : BUILT_IN_ATOMIC_XOR_FETCH_N);
	  বিরতি;
	পূর্বনির্ধারিত:
	  যাও cas_loop;
	}

      /* We can only use "_1" through "_16" variants of the atomic fetch
	 built-ins.  */
      unsigned HOST_WIDE_INT আকার_2 = বৃক্ষ_to_uhwi (TYPE_আকার_UNIT (lhs_type));
      যদি (আকার_2 != 1 && আকার_2 != 2 && আকার_2 != 4 && আকার_2 != 8 && আকার_2 != 16)
	যাও cas_loop;

      /* If this is a pointer type, we need to multiply by the size of
	 the pointer target type.  */
      যদি (POINTER_TYPE_P (lhs_type))
	{
	  যদি (!COMPLETE_TYPE_P (বৃক্ষ_TYPE (lhs_type))
	      /* ??? This would introduce -Wdiscarded-qualifiers
		 warning: __atomic_fetch_* expect volatile void *
		 type as the first argument.  (Assignments between
		 atomic and non-atomic objects are OK.) */
	      || TYPE_RESTRICT (lhs_type))
	    যাও cas_loop;
	  বৃক্ষ sz = TYPE_আকার_UNIT (বৃক্ষ_TYPE (lhs_type));
	  rhs = fold_build2_loc (loc, MULT_রাশিমালা, ptrdiff_type_গ্রন্থি,
				 convert (ptrdiff_type_গ্রন্থি, rhs),
				 convert (ptrdiff_type_গ্রন্থি, sz));
	}

      /* Build __atomic_fetch_* (&lhs, &val, SEQ_CST), or
	 __atomic_*_fetch (&lhs, &val, SEQ_CST).  */
      fndecl = builtin_decl_explicit (fncode);
      params->quick_ঠেলো (lhs_addr);
      params->quick_ঠেলো (rhs);
      params->quick_ঠেলো (seq_cst);
      func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, ফাঁকা);

      newval = create_tmp_var_raw (nonatomic_lhs_type);
      বৃক্ষ_ADDRESSABLE (newval) = 1;
      suppress_warning (newval);
      rhs = build4 (TARGET_রাশিমালা, nonatomic_lhs_type, newval, func_call,
		    NULL_বৃক্ষ, NULL_বৃক্ষ);
      SET_রাশিমালা_LOCATION (rhs, loc);
      add_stmt (rhs);

      /* Finish the compound statement.  */
      compound_stmt = c_end_compound_stmt (loc, compound_stmt, মিথ্যা);

      /* NEWVAL is the value which was stored, return a COMPOUND_STMT of
	 the statement and that value.  */
      ফেরত build2 (COMPOUND_রাশিমালা, nonatomic_lhs_type, compound_stmt, newval);
    }

cas_loop:
  /* Create the variables and labels required for the op= form.  */
  old = create_tmp_var_raw (nonatomic_lhs_type);
  old_addr = build_unary_op (loc, ADDR_রাশিমালা, old, মিথ্যা);
  বৃক্ষ_ADDRESSABLE (old) = 1;
  suppress_warning (old);

  newval = create_tmp_var_raw (nonatomic_lhs_type);
  newval_addr = build_unary_op (loc, ADDR_রাশিমালা, newval, মিথ্যা);
  বৃক্ষ_ADDRESSABLE (newval) = 1;
  suppress_warning (newval);

  loop_decl = create_artificial_label (loc);
  loop_label = build1 (LABEL_রাশিমালা, void_type_গ্রন্থি, loop_decl);

  done_decl = create_artificial_label (loc);
  done_label = build1 (LABEL_রাশিমালা, void_type_গ্রন্থি, done_decl);

  /* __atomic_load (addr, &old, SEQ_CST).  */
  fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_LOAD);
  params->quick_ঠেলো (lhs_addr);
  params->quick_ঠেলো (old_addr);
  params->quick_ঠেলো (seq_cst);
  func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, ফাঁকা);
  old = build4 (TARGET_রাশিমালা, nonatomic_lhs_type, old, func_call, NULL_বৃক্ষ,
		NULL_বৃক্ষ);
  add_stmt (old);
  params->truncate (0);

  /* Create the expressions for floating-point environment
     manipulation, if required.  */
  যৌক্তিক need_fenv = (flag_trapping_math
		    && (FLOAT_TYPE_P (lhs_type) || FLOAT_TYPE_P (rhs_type)));
  বৃক্ষ hold_call = NULL_বৃক্ষ, clear_call = NULL_বৃক্ষ, update_call = NULL_বৃক্ষ;
  যদি (need_fenv)
    targetm.atomic_assign_expand_fenv (&hold_call, &clear_call, &update_call);

  যদি (hold_call)
    add_stmt (hold_call);

  /* loop:  */
  add_stmt (loop_label);

  /* newval = old + val;  */
  যদি (rhs_type != rhs_semantic_type)
    val = build1 (EXCESS_PRECISION_রাশিমালা, nonatomic_rhs_semantic_type, val);
  rhs = build_দ্বিমিক_op (loc, modifycode,
			 convert_lvalue_to_rvalue (loc, old, সত্য, সত্য),
			 val, সত্য);
  যদি (বৃক্ষ_CODE (rhs) == EXCESS_PRECISION_রাশিমালা)
    {
      বৃক্ষ eptype = বৃক্ষ_TYPE (rhs);
      rhs = c_fully_fold (বৃক্ষ_OPERAND (rhs, 0), মিথ্যা, ফাঁকা);
      rhs = build1 (EXCESS_PRECISION_রাশিমালা, eptype, rhs);
    }
  অন্যথা
    rhs = c_fully_fold (rhs, মিথ্যা, ফাঁকা);
  rhs = convert_for_assignment (loc, UNKNOWN_LOCATION, nonatomic_lhs_type,
				rhs, NULL_বৃক্ষ, ic_assign, মিথ্যা, NULL_বৃক্ষ,
				NULL_বৃক্ষ, 0);
  /* The temporary variable for NEWVAL is only gimplified correctly (in
     particular, given a DECL_CONTEXT) if used in a TARGET_EXPR.  To avoid
     subsequent ICEs in nested function processing after an error, ensure such
     a TARGET_EXPR is built even after an error.  */
  যদি (rhs == error_mark_গ্রন্থি)
    rhs = old;
  rhs = build4 (TARGET_রাশিমালা, nonatomic_lhs_type, newval, rhs, NULL_বৃক্ষ,
		NULL_বৃক্ষ);
  SET_রাশিমালা_LOCATION (rhs, loc);
  add_stmt (rhs);

  /* if (__atomic_compare_exchange (addr, &old, &new, false, SEQ_CST, SEQ_CST))
       goto done;  */
  fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_COMPARE_EXCHANGE);
  params->quick_ঠেলো (lhs_addr);
  params->quick_ঠেলো (old_addr);
  params->quick_ঠেলো (newval_addr);
  params->quick_ঠেলো (integer_zero_গ্রন্থি);
  params->quick_ঠেলো (seq_cst);
  params->quick_ঠেলো (seq_cst);
  func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, ফাঁকা);

  goto_stmt = build1 (GOTO_রাশিমালা, void_type_গ্রন্থি, done_decl);
  SET_রাশিমালা_LOCATION (goto_stmt, loc);

  stmt = build3 (COND_রাশিমালা, void_type_গ্রন্থি, func_call, goto_stmt, NULL_বৃক্ষ);
  SET_রাশিমালা_LOCATION (stmt, loc);
  add_stmt (stmt);

  যদি (clear_call)
    add_stmt (clear_call);

  /* goto loop;  */
  goto_stmt  = build1 (GOTO_রাশিমালা, void_type_গ্রন্থি, loop_decl);
  SET_রাশিমালা_LOCATION (goto_stmt, loc);
  add_stmt (goto_stmt);

  /* done:  */
  add_stmt (done_label);

  যদি (update_call)
    add_stmt (update_call);

  /* Finish the compound statement.  */
  compound_stmt = c_end_compound_stmt (loc, compound_stmt, মিথ্যা);

  /* NEWVAL is the value that was successfully stored, return a
     COMPOUND_EXPR of the statement and the appropriate value.  */
  ফেরত build2 (COMPOUND_রাশিমালা, nonatomic_lhs_type, compound_stmt,
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

বৃক্ষ
build_unary_op (location_t location, গণনা বৃক্ষ_code code, বৃক্ষ xarg,
		যৌক্তিক noconvert)
{
  /* No default_conversion here.  It causes trouble for ADDR_EXPR.  */
  বৃক্ষ arg = xarg;
  বৃক্ষ argtype = NULL_বৃক্ষ;
  গণনা বৃক্ষ_code typecode;
  বৃক্ষ val;
  বৃক্ষ ret = error_mark_গ্রন্থি;
  বৃক্ষ eptype = NULL_বৃক্ষ;
  ধ্রুবক অক্ষর *invalid_op_diag;

  /* If ARG is wrapped in a call to .ACCESS_WITH_SIZE — created when the
     C parser rvalue-converts a counted_by-annotated member access (see
     PR123569) — unwrap it here.  Unary operators that consume an rvalue
     (!, -, +) read the value itself rather than dereferencing into the
     pointed-to data, so the bounds-checking wrapper is unnecessary and
     would otherwise reach build_unary_op while it is not equipped to
     handle the wrapped form.  PR123569 fixed the ++/-- side of this by
     suppressing wrapper creation in the parser; the rvalue-consuming
     ops still receive the wrapper and need to strip it here.  */
  যদি (is_access_with_আকার_p (arg))
    xarg = arg = get_ref_from_access_with_আকার (arg);

  gcc_checking_assert (!is_access_with_আকার_p (arg));

  যৌক্তিক int_operands = রাশিমালা_INT_CONST_OPERANDS (xarg);
  যদি (int_operands)
    arg = remove_c_maybe_const_রাশিমালা (arg);

  যদি (code != ADDR_রাশিমালা)
    arg = require_complete_type (location, arg);

  typecode = বৃক্ষ_CODE (বৃক্ষ_TYPE (arg));
  যদি (typecode == ERROR_MARK)
    ফেরত error_mark_গ্রন্থি;
  যদি (typecode == ENUMERAL_TYPE || typecode == BOOLEAN_TYPE)
    typecode = INTEGER_TYPE;

  যদি ((invalid_op_diag
       = targetm.invalid_unary_op (code, বৃক্ষ_TYPE (xarg))))
    {
      error_at (location, invalid_op_diag);
      ফেরত error_mark_গ্রন্থি;
    }

  যদি (বৃক্ষ_CODE (arg) == EXCESS_PRECISION_রাশিমালা)
    {
      eptype = বৃক্ষ_TYPE (arg);
      arg = বৃক্ষ_OPERAND (arg, 0);
    }

  নির্বাচন (code)
    {
    ক্ষেত্র CONVERT_রাশিমালা:
      /* This is used for unary plus, because a CONVERT_EXPR
	 is enough to prevent anybody from looking inside for
	 associativity, but won't generate any code.  */
      যদি (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE
	    || typecode == FIXED_POINT_TYPE || typecode == COMPLEX_TYPE
	    || typecode == BITINT_TYPE
	    || gnu_vector_type_p (বৃক্ষ_TYPE (arg))))
	{
	  error_at (location, "wrong type argument to unary plus");
	  ফেরত error_mark_গ্রন্থি;
	}
      অন্যথা যদি (!noconvert)
	arg = default_conversion (arg);
      arg = non_lvalue_loc (location, arg);
      বিরতি;

    ক্ষেত্র NEGATE_রাশিমালা:
      যদি (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE
	    || typecode == FIXED_POINT_TYPE || typecode == COMPLEX_TYPE
	    || typecode == BITINT_TYPE
	    || gnu_vector_type_p (বৃক্ষ_TYPE (arg))))
	{
	  error_at (location, "wrong type argument to unary minus");
	  ফেরত error_mark_গ্রন্থি;
	}
      অন্যথা যদি (!noconvert)
	arg = default_conversion (arg);
      বিরতি;

    ক্ষেত্র BIT_NOT_রাশিমালা:
      /* ~ works on integer types and non float vectors. */
      যদি (typecode == INTEGER_TYPE
	  || typecode == BITINT_TYPE
	  || (gnu_vector_type_p (বৃক্ষ_TYPE (arg))
	      && !VECTOR_FLOAT_TYPE_P (বৃক্ষ_TYPE (arg))))
	{
	  বৃক্ষ e = arg;

	  /* Warn if the expression has boolean value.  */
	  যখন (বৃক্ষ_CODE (e) == COMPOUND_রাশিমালা)
	    e = বৃক্ষ_OPERAND (e, 1);

	  যদি ((C_BOOLEAN_TYPE_P (বৃক্ষ_TYPE (arg))
	       || truth_মান_p (বৃক্ষ_CODE (e))))
	    {
	      auto_diagnostic_group d;
	      যদি (warning_at (location, OPT_Wbool_operation,
				"%<~%> on a boolean expression"))
		{
		  gcc_rich_location richloc (location);
		  richloc.add_fixit_ঢোকাও_before (location, "!");
		  inform (&richloc, "did you mean to use logical not?");
		}
	    }
	  যদি (!noconvert)
	    arg = default_conversion (arg);
	}
      অন্যথা যদি (typecode == COMPLEX_TYPE)
	{
	  code = CONJ_রাশিমালা;
	  pedwarn (location, OPT_Wpedantic,
		   "ISO C does not support %<~%> for complex conjugation");
	  যদি (!noconvert)
	    arg = default_conversion (arg);
	}
      অন্যথা
	{
	  error_at (location, "wrong type argument to bit-complement");
	  ফেরত error_mark_গ্রন্থি;
	}
      বিরতি;

    ক্ষেত্র ABS_রাশিমালা:
      যদি (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE))
	{
	  error_at (location, "wrong type argument to abs");
	  ফেরত error_mark_গ্রন্থি;
	}
      অন্যথা যদি (!noconvert)
	arg = default_conversion (arg);
      বিরতি;

    ক্ষেত্র ABSU_রাশিমালা:
      যদি (!(typecode == INTEGER_TYPE))
	{
	  error_at (location, "wrong type argument to absu");
	  ফেরত error_mark_গ্রন্থি;
	}
      অন্যথা যদি (!noconvert)
	arg = default_conversion (arg);
      বিরতি;

    ক্ষেত্র CONJ_রাশিমালা:
      /* Conjugating a real value is a no-op, but allow it anyway.  */
      যদি (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE
	    || typecode == COMPLEX_TYPE))
	{
	  error_at (location, "wrong type argument to conjugation");
	  ফেরত error_mark_গ্রন্থি;
	}
      অন্যথা যদি (!noconvert)
	arg = default_conversion (arg);
      বিরতি;

    ক্ষেত্র TRUTH_NOT_রাশিমালা:
      যদি (typecode != INTEGER_TYPE && typecode != FIXED_POINT_TYPE
	  && typecode != REAL_TYPE && typecode != POINTER_TYPE
	  && typecode != COMPLEX_TYPE && typecode != NULLPTR_TYPE
	  && typecode != BITINT_TYPE)
	{
	  error_at (location,
		    "wrong type argument to unary exclamation mark");
	  ফেরত error_mark_গ্রন্থি;
	}
      যদি (int_operands)
	{
	  arg = c_objc_common_truthvalue_conversion (location, xarg);
	  arg = remove_c_maybe_const_রাশিমালা (arg);
	}
      অন্যথা
	arg = c_objc_common_truthvalue_conversion (location, arg);
      ret = invert_truthvalue_loc (location, arg);
      eptype = NULL_বৃক্ষ;
      /* If the TRUTH_NOT_EXPR has been folded, reset the location.  */
      যদি (রাশিমালা_P (ret) && রাশিমালা_HAS_LOCATION (ret))
	location = রাশিমালা_LOCATION (ret);
      যাও return_build_unary_op;

    ক্ষেত্র REALPART_রাশিমালা:
    ক্ষেত্র IMAGPART_রাশিমালা:
      ret = build_real_imag_রাশিমালা (location, code, arg);
      যদি (ret == error_mark_গ্রন্থি)
	ফেরত error_mark_গ্রন্থি;
      যদি (eptype && বৃক্ষ_CODE (eptype) == COMPLEX_TYPE)
	eptype = বৃক্ষ_TYPE (eptype);
      যাও return_build_unary_op;

    ক্ষেত্র PREINCREMENT_রাশিমালা:
    ক্ষেত্র POSTINCREMENT_রাশিমালা:
    ক্ষেত্র PREDECREMENT_রাশিমালা:
    ক্ষেত্র POSTDECREMENT_রাশিমালা:

      যদি (বৃক্ষ_CODE (arg) == C_MAYBE_CONST_রাশিমালা)
	{
	  বৃক্ষ inner = build_unary_op (location, code,
				       C_MAYBE_CONST_রাশিমালা_রাশিমালা (arg),
				       noconvert);
	  যদি (inner == error_mark_গ্রন্থি)
	    ফেরত error_mark_গ্রন্থি;
	  ret = build2 (C_MAYBE_CONST_রাশিমালা, বৃক্ষ_TYPE (inner),
			C_MAYBE_CONST_রাশিমালা_PRE (arg), inner);
	  gcc_assert (!C_MAYBE_CONST_রাশিমালা_INT_OPERANDS (arg));
	  C_MAYBE_CONST_রাশিমালা_NON_CONST (ret) = 1;
	  যাও return_build_unary_op;
	}

      /* Complain about anything that is not a true lvalue.  In
	 Objective-C, skip this check for property_refs.  */
      যদি (!objc_is_property_ref (arg)
	  && !lvalue_or_else (location,
			      arg, ((code == PREINCREMENT_রাশিমালা
				     || code == POSTINCREMENT_রাশিমালা)
				    ? lv_increment
				    : lv_decrement)))
	ফেরত error_mark_গ্রন্থি;

      যদি (warn_cxx_compat && বৃক্ষ_CODE (বৃক্ষ_TYPE (arg)) == ENUMERAL_TYPE)
	{
	  যদি (code == PREINCREMENT_রাশিমালা || code == POSTINCREMENT_রাশিমালা)
	    warning_at (location, OPT_Wc___compat,
			"increment of enumeration value is invalid in C++");
	  অন্যথা
	    warning_at (location, OPT_Wc___compat,
			"decrement of enumeration value is invalid in C++");
	}

      যদি (C_BOOLEAN_TYPE_P (বৃক্ষ_TYPE (arg)))
	{
	  যদি (code == PREINCREMENT_রাশিমালা || code == POSTINCREMENT_রাশিমালা)
	    warning_at (location, OPT_Wbool_operation,
			"increment of a boolean expression");
	  অন্যথা
	    warning_at (location, OPT_Wbool_operation,
			"decrement of a boolean expression");
	}

      /* Ensure the argument is fully folded inside any SAVE_EXPR.  */
      arg = c_fully_fold (arg, মিথ্যা, ফাঁকা, সত্য);

      যৌক্তিক atomic_op;
      atomic_op = really_atomic_lvalue (arg);

      /* Increment or decrement the real part of the value,
	 and don't change the imaginary part.  */
      যদি (typecode == COMPLEX_TYPE)
	{
	  বৃক্ষ real, imag;

	  pedwarn_c23 (location, OPT_Wpedantic,
		       "ISO C does not support %<++%> and %<--%> on complex "
		       "types before C2Y");

	  যদি (!atomic_op)
	    {
	      arg = stabilize_reference (arg);
	      real = build_unary_op (রাশিমালা_LOCATION (arg), REALPART_রাশিমালা, arg,
				     সত্য);
	      imag = build_unary_op (রাশিমালা_LOCATION (arg), IMAGPART_রাশিমালা, arg,
				     সত্য);
	      real = build_unary_op (রাশিমালা_LOCATION (arg), code, real, সত্য);
	      যদি (real == error_mark_গ্রন্থি || imag == error_mark_গ্রন্থি)
		ফেরত error_mark_গ্রন্থি;
	      ret = build2 (COMPLEX_রাশিমালা, বৃক্ষ_TYPE (arg),
			    real, imag);
	      যাও return_build_unary_op;
	    }
	}

      /* Report invalid types.  */

      যদি (typecode != POINTER_TYPE && typecode != FIXED_POINT_TYPE
	  && typecode != INTEGER_TYPE && typecode != REAL_TYPE
	  && typecode != COMPLEX_TYPE && typecode != BITINT_TYPE
	  && !gnu_vector_type_p (বৃক্ষ_TYPE (arg)))
	{
	  যদি (code == PREINCREMENT_রাশিমালা || code == POSTINCREMENT_রাশিমালা)
	    error_at (location, "wrong type argument to increment");
	  অন্যথা
	    error_at (location, "wrong type argument to decrement");

	  ফেরত error_mark_গ্রন্থি;
	}

      {
	বৃক্ষ inc;

	argtype = বৃক্ষ_TYPE (arg);

	/* Compute the increment.  */

	যদি (typecode == POINTER_TYPE)
	  {
	    /* If pointer target is an incomplete type,
	       we just cannot know how to do the arithmetic.  */
	    যদি (!COMPLETE_OR_VOID_TYPE_P (বৃক্ষ_TYPE (argtype)))
	      {
		যদি (code == PREINCREMENT_রাশিমালা || code == POSTINCREMENT_রাশিমালা)
		  error_at (location,
			    "increment of pointer to an incomplete type %qT",
			    বৃক্ষ_TYPE (argtype));
		অন্যথা
		  error_at (location,
			    "decrement of pointer to an incomplete type %qT",
			    বৃক্ষ_TYPE (argtype));
	      }
	    অন্যথা যদি (বৃক্ষ_CODE (বৃক্ষ_TYPE (argtype)) == FUNCTION_TYPE
		     || VOID_TYPE_P (বৃক্ষ_TYPE (argtype)))
	      {
		যদি (code == PREINCREMENT_রাশিমালা || code == POSTINCREMENT_রাশিমালা)
		  pedwarn (location, OPT_Wpointer_arith,
			   "wrong type argument to increment");
		অন্যথা
		  pedwarn (location, OPT_Wpointer_arith,
			   "wrong type argument to decrement");
	      }
	    অন্যথা
	      verify_type_context (location, TCTX_POINTER_ARITH,
				   বৃক্ষ_TYPE (argtype));

	    inc = c_আকার_in_bytes (বৃক্ষ_TYPE (argtype));
	    inc = convert_to_ptrofftype_loc (location, inc);
	  }
	অন্যথা যদি (FRACT_MODE_P (TYPE_MODE (argtype)))
	  {
	    /* For signed fract types, we invert ++ to -- or
	       -- to ++, and change inc from 1 to -1, because
	       it is not possible to represent 1 in signed fract constants.
	       For unsigned fract types, the result always overflows and
	       we get an undefined (original) or the maximum value.  */
	    যদি (code == PREINCREMENT_রাশিমালা)
	      code = PREDECREMENT_রাশিমালা;
	    অন্যথা যদি (code == PREDECREMENT_রাশিমালা)
	      code = PREINCREMENT_রাশিমালা;
	    অন্যথা যদি (code == POSTINCREMENT_রাশিমালা)
	      code = POSTDECREMENT_রাশিমালা;
	    অন্যথা /* code == POSTDECREMENT_EXPR  */
	      code = POSTINCREMENT_রাশিমালা;

	    inc = integer_minus_one_গ্রন্থি;
	    inc = convert (argtype, inc);
	  }
	অন্যথা
	  {
	    inc = VECTOR_TYPE_P (argtype)
	      ? build_one_cst (argtype)
	      : integer_one_গ্রন্থি;
	    inc = convert (argtype, inc);
	  }

	/* If 'arg' is an Objective-C PROPERTY_REF expression, then we
	   need to ask Objective-C to build the increment or decrement
	   expression for it.  */
	যদি (objc_is_property_ref (arg))
	  ফেরত objc_build_incr_রাশিমালা_for_property_ref (location, code,
							arg, inc);

	/* Report a read-only lvalue.  */
	যদি (TYPE_READONLY (argtype))
	  {
	    readonly_error (location, arg,
			    ((code == PREINCREMENT_রাশিমালা
			      || code == POSTINCREMENT_রাশিমালা)
			     ? lv_increment : lv_decrement));
	    ফেরত error_mark_গ্রন্থি;
	  }
	অন্যথা যদি (বৃক্ষ_READONLY (arg))
	  readonly_warning (arg,
			    ((code == PREINCREMENT_রাশিমালা
			      || code == POSTINCREMENT_রাশিমালা)
			     ? lv_increment : lv_decrement));

	/* If the argument is atomic, use the special code sequences for
	   atomic compound assignment.  */
	যদি (atomic_op)
	  {
	    arg = stabilize_reference (arg);
	    ret = build_atomic_assign (location, arg,
				       ((code == PREINCREMENT_রাশিমালা
					 || code == POSTINCREMENT_রাশিমালা)
					? PLUS_রাশিমালা
					: MINUS_রাশিমালা),
				       (FRACT_MODE_P (TYPE_MODE (argtype))
					? inc
					: integer_one_গ্রন্থি),
				       (code == POSTINCREMENT_রাশিমালা
					|| code == POSTDECREMENT_রাশিমালা));
	    যাও return_build_unary_op;
	  }

	বৃক্ষ true_res;
	যদি (c_hardbool_type_attr (বৃক্ষ_TYPE (arg), ফাঁকা, &true_res))
	  {
	    বৃক্ষ larg = stabilize_reference (arg);
	    বৃক্ষ sarg = save_রাশিমালা (larg);
	    নির্বাচন (code)
	      {
	      ক্ষেত্র PREINCREMENT_রাশিমালা:
		val = build2 (MODIFY_রাশিমালা, বৃক্ষ_TYPE (larg), larg, true_res);
		val = build2 (COMPOUND_রাশিমালা, বৃক্ষ_TYPE (larg), sarg, val);
		বিরতি;
	      ক্ষেত্র POSTINCREMENT_রাশিমালা:
		val = build2 (MODIFY_রাশিমালা, বৃক্ষ_TYPE (larg), larg, true_res);
		val = build2 (COMPOUND_রাশিমালা, বৃক্ষ_TYPE (larg), val, sarg);
		val = build2 (COMPOUND_রাশিমালা, বৃক্ষ_TYPE (larg), sarg, val);
		বিরতি;
	      ক্ষেত্র PREDECREMENT_রাশিমালা:
		{
		  বৃক্ষ rarg = convert_lvalue_to_rvalue (location, sarg,
							সত্য, সত্য);
		  rarg = invert_truthvalue_loc (location, rarg);
		  rarg = convert (বৃক্ষ_TYPE (sarg), rarg);
		  val = build2 (MODIFY_রাশিমালা, বৃক্ষ_TYPE (larg), larg, rarg);
		}
		বিরতি;
	      ক্ষেত্র POSTDECREMENT_রাশিমালা:
		{
		  বৃক্ষ rarg = convert_lvalue_to_rvalue (location, sarg,
							সত্য, সত্য);
		  rarg = invert_truthvalue_loc (location, rarg);
		  বৃক্ষ iarg = convert (বৃক্ষ_TYPE (larg), rarg);
		  val = build2 (MODIFY_রাশিমালা, বৃক্ষ_TYPE (larg), larg, iarg);
		  val = build2 (COMPOUND_রাশিমালা, বৃক্ষ_TYPE (larg), val, sarg);
		  val = build2 (COMPOUND_রাশিমালা, বৃক্ষ_TYPE (larg), sarg, val);
		}
		বিরতি;
	      পূর্বনির্ধারিত:
		gcc_unreachable ();
	      }
	    বৃক্ষ_SIDE_EFFECTS (val) = 1;
	  }
	অন্যথা যদি (C_BOOLEAN_TYPE_P (বৃক্ষ_TYPE (arg)))
	  val = boolean_increment (code, arg);
	অন্যথা
	  val = build2 (code, বৃক্ষ_TYPE (arg), arg, inc);
	বৃক্ষ_SIDE_EFFECTS (val) = 1;
	যদি (TYPE_QUALS (বৃক্ষ_TYPE (val)) != TYPE_UNQUALIFIED)
	  বৃক্ষ_TYPE (val) = c_build_qualified_type (বৃক্ষ_TYPE (val),
						    TYPE_UNQUALIFIED);
	ret = val;
	যাও return_build_unary_op;
      }

    ক্ষেত্র ADDR_রাশিমালা:
      /* Note that this operation never does default_conversion.  */

      /* The operand of unary '&' must be an lvalue (which excludes
	 expressions of type void), or, in C99, the result of a [] or
	 unary '*' operator.  */
      যদি (VOID_TYPE_P (বৃক্ষ_TYPE (arg))
	  && TYPE_QUALS (বৃক্ষ_TYPE (arg)) == TYPE_UNQUALIFIED
	  && (!INDIRECT_REF_P (arg) || !flag_isoc99))
	pedwarn (location, 0, "taking address of expression of type %<void%>");

      /* Let &* cancel out to simplify resulting code.  */
      যদি (INDIRECT_REF_P (arg))
	{
	  /* Don't let this be an lvalue.  */
	  যদি (lvalue_p (বৃক্ষ_OPERAND (arg, 0)))
	    ফেরত non_lvalue_loc (location, বৃক্ষ_OPERAND (arg, 0));
	  ret = বৃক্ষ_OPERAND (arg, 0);
	  যাও return_build_unary_op;
	}

      /* Anything not already handled and not a true memory reference
	 or a non-lvalue array is an error.  */
      যদি (typecode != FUNCTION_TYPE && !noconvert
	  && !lvalue_or_else (location, arg, lv_addressof))
	ফেরত error_mark_গ্রন্থি;

      /* Move address operations inside C_MAYBE_CONST_EXPR to simplify
	 folding later.  */
      যদি (বৃক্ষ_CODE (arg) == C_MAYBE_CONST_রাশিমালা)
	{
	  বৃক্ষ inner = build_unary_op (location, code,
				       C_MAYBE_CONST_রাশিমালা_রাশিমালা (arg),
				       noconvert);
	  ret = build2 (C_MAYBE_CONST_রাশিমালা, বৃক্ষ_TYPE (inner),
			C_MAYBE_CONST_রাশিমালা_PRE (arg), inner);
	  gcc_assert (!C_MAYBE_CONST_রাশিমালা_INT_OPERANDS (arg));
	  C_MAYBE_CONST_রাশিমালা_NON_CONST (ret)
	    = C_MAYBE_CONST_রাশিমালা_NON_CONST (arg);
	  যাও return_build_unary_op;
	}

      /* Ordinary case; arg is a COMPONENT_REF or a decl.  */

      argtype = বৃক্ষ_TYPE (arg);

      /* If the lvalue is const or volatile, merge that into the type
	 to which the address will point.  This is only needed
	 for function types.  */
      যদি ((DECL_P (arg) || REFERENCE_CLASS_P (arg))
	  && (বৃক্ষ_READONLY (arg) || বৃক্ষ_THIS_VOLATILE (arg))
	  && বৃক্ষ_CODE (argtype) == FUNCTION_TYPE)
	{
	  পূর্ণসংখ্যা orig_quals = TYPE_QUALS (strip_array_types (argtype));
	  পূর্ণসংখ্যা quals = orig_quals;

	  যদি (বৃক্ষ_READONLY (arg))
	    quals |= TYPE_QUAL_CONST;
	  যদি (বৃক্ষ_THIS_VOLATILE (arg))
	    quals |= TYPE_QUAL_VOLATILE;

	  argtype = c_build_qualified_type (argtype, quals);
	}

      নির্বাচন (বৃক্ষ_CODE (arg))
	{
	ক্ষেত্র COMPONENT_REF:
	  যদি (DECL_C_BIT_FIELD (বৃক্ষ_OPERAND (arg, 1)))
	    {
	      error_at (location, "cannot take address of bit-field %qD",
			বৃক্ষ_OPERAND (arg, 1));
	      ফেরত error_mark_গ্রন্থি;
	    }

	  /* fall through */

	ক্ষেত্র ARRAY_REF:
	  যদি (TYPE_REVERSE_STORAGE_ORDER (বৃক্ষ_TYPE (বৃক্ষ_OPERAND (arg, 0))))
	    {
	      যদি (!AGGREGATE_TYPE_P (বৃক্ষ_TYPE (arg))
		  && !POINTER_TYPE_P (বৃক্ষ_TYPE (arg))
		  && !VECTOR_TYPE_P (বৃক্ষ_TYPE (arg)))
		{
		  error_at (location, "cannot take address of scalar with "
			    "reverse storage order");
		  ফেরত error_mark_গ্রন্থি;
		}

	      যদি (বৃক্ষ_CODE (বৃক্ষ_TYPE (arg)) == ARRAY_TYPE
		  && TYPE_REVERSE_STORAGE_ORDER (বৃক্ষ_TYPE (arg)))
		warning_at (location, OPT_Wscalar_storage_order,
			    "address of array with reverse scalar storage "
			    "order requested");
	    }

	পূর্বনির্ধারিত:
	  বিরতি;
	}

      যদি (!c_mark_addressable (arg))
	ফেরত error_mark_গ্রন্থি;

      gcc_assert (বৃক্ষ_CODE (arg) != COMPONENT_REF
		  || !DECL_C_BIT_FIELD (বৃক্ষ_OPERAND (arg, 1)));

      argtype = c_build_pointer_type (argtype);

      /* ??? Cope with user tricks that amount to offsetof.  Delete this
	 when we have proper support for integer constant expressions.  */
      val = get_base_address (arg);
      যদি (val && INDIRECT_REF_P (val)
          && বৃক্ষ_CONSTANT (বৃক্ষ_OPERAND (val, 0)))
	{
	  ret = fold_offsetof (arg, argtype);
	  যাও return_build_unary_op;
	}

      val = build1 (ADDR_রাশিমালা, argtype, arg);

      ret = val;
      যাও return_build_unary_op;

    ক্ষেত্র PAREN_রাশিমালা:
      ret = build1 (code, বৃক্ষ_TYPE (arg), arg);
      যাও return_build_unary_op;

    পূর্বনির্ধারিত:
      gcc_unreachable ();
    }

  যদি (argtype == NULL_বৃক্ষ)
    argtype = বৃক্ষ_TYPE (arg);
  যদি (বৃক্ষ_CODE (arg) == INTEGER_CST)
    ret = (require_constant_মান
	   ? fold_build1_initializer_loc (location, code, argtype, arg)
	   : fold_build1_loc (location, code, argtype, arg));
  অন্যথা
    ret = build1 (code, argtype, arg);
 return_build_unary_op:
  gcc_assert (ret != error_mark_গ্রন্থি);
  যদি (বৃক্ষ_CODE (ret) == INTEGER_CST && !বৃক্ষ_OVERFLOW (ret)
      && !(বৃক্ষ_CODE (xarg) == INTEGER_CST && !বৃক্ষ_OVERFLOW (xarg)))
    ret = build1 (NOP_রাশিমালা, বৃক্ষ_TYPE (ret), ret);
  অন্যথা যদি (বৃক্ষ_CODE (ret) != INTEGER_CST && int_operands)
    ret = note_integer_operands (ret);
  যদি (eptype)
    ret = build1 (EXCESS_PRECISION_রাশিমালা, eptype, ret);
  protected_set_রাশিমালা_location (ret, location);
  ফেরত ret;
}

/* Return nonzero if REF is an lvalue valid for this language.
   Lvalues can be assigned, unless their type has TYPE_READONLY.
   Lvalues can have their address taken, unless they have C_DECL_REGISTER.  */

যৌক্তিক
lvalue_p (const_বৃক্ষ ref)
{
  ধ্রুবক গণনা বৃক্ষ_code code = বৃক্ষ_CODE (ref);

  নির্বাচন (code)
    {
    ক্ষেত্র REALPART_রাশিমালা:
    ক্ষেত্র IMAGPART_রাশিমালা:
    ক্ষেত্র COMPONENT_REF:
      ফেরত lvalue_p (বৃক্ষ_OPERAND (ref, 0));

    ক্ষেত্র C_MAYBE_CONST_রাশিমালা:
      ফেরত lvalue_p (বৃক্ষ_OPERAND (ref, 1));

    ক্ষেত্র COMPOUND_LITERAL_রাশিমালা:
    ক্ষেত্র STRING_CST:
      ফেরত সত্য;

    ক্ষেত্র MEM_REF:
    ক্ষেত্র TARGET_MEM_REF:
      /* MEM_REFs can appear from -fgimple parsing or folding, so allow them
	 here as well.  */
    ক্ষেত্র INDIRECT_REF:
    ক্ষেত্র ARRAY_REF:
    ক্ষেত্র VAR_DECL:
    ক্ষেত্র PARM_DECL:
    ক্ষেত্র ফলাফল_DECL:
    ক্ষেত্র ERROR_MARK:
      ফেরত (বৃক্ষ_CODE (বৃক্ষ_TYPE (ref)) != FUNCTION_TYPE
	      && বৃক্ষ_CODE (বৃক্ষ_TYPE (ref)) != METHOD_TYPE);

    ক্ষেত্র BIND_রাশিমালা:
      ফেরত বৃক্ষ_CODE (বৃক্ষ_TYPE (ref)) == ARRAY_TYPE;

    ক্ষেত্র CALL_রাশিমালা:
      ফেরত is_access_with_আকার_p (ref);

    পূর্বনির্ধারিত:
      ফেরত মিথ্যা;
    }
}

/* Give a warning for storing in something that is read-only in GCC
   terms but not const in ISO C terms.  */

স্থির শূন্য
readonly_warning (বৃক্ষ arg, গণনা lvalue_use use)
{
  নির্বাচন (use)
    {
    ক্ষেত্র lv_assign:
      warning (0, "assignment of read-only location %qE", arg);
      বিরতি;
    ক্ষেত্র lv_increment:
      warning (0, "increment of read-only location %qE", arg);
      বিরতি;
    ক্ষেত্র lv_decrement:
      warning (0, "decrement of read-only location %qE", arg);
      বিরতি;
    পূর্বনির্ধারিত:
      gcc_unreachable ();
    }
  ফেরত;
}


/* Return nonzero if REF is an lvalue valid for this language;
   otherwise, print an error message and return zero.  USE says
   how the lvalue is being used and so selects the error message.
   LOCATION is the location at which any error should be reported.  */

স্থির পূর্ণসংখ্যা
lvalue_or_else (location_t loc, const_বৃক্ষ ref, গণনা lvalue_use use)
{
  পূর্ণসংখ্যা win = lvalue_p (ref);

  যদি (!win)
    lvalue_error (loc, use);

  ফেরত win;
}

/* Mark EXP saying that we need to be able to take the
   address of it; it should not be allocated in a register.
   Returns true if successful.  ARRAY_REF_P is true if this
   is for ARRAY_REF construction - in that case we don't want
   to look through VIEW_CONVERT_EXPR from VECTOR_TYPE to ARRAY_TYPE,
   it is fine to use ARRAY_REFs for vector subscripts on vector
   register variables.  If OVERRIDE_REGISTER, clear DECL_REGISTER rather
   than producing an error for taking the address of a register.  */

যৌক্তিক
c_mark_addressable (বৃক্ষ exp, যৌক্তিক array_ref_p, যৌক্তিক override_register)
{
  বৃক্ষ x = exp;

  যখন (1)
    নির্বাচন (বৃক্ষ_CODE (x))
      {
      ক্ষেত্র VIEW_CONVERT_রাশিমালা:
	যদি (array_ref_p
	    && বৃক্ষ_CODE (বৃক্ষ_TYPE (x)) == ARRAY_TYPE
	    && VECTOR_TYPE_P (বৃক্ষ_TYPE (বৃক্ষ_OPERAND (x, 0))))
	  ফেরত সত্য;
	x = বৃক্ষ_OPERAND (x, 0);
	বিরতি;

      ক্ষেত্র COMPONENT_REF:
	যদি (DECL_C_BIT_FIELD (বৃক্ষ_OPERAND (x, 1)))
	  {
	    error ("cannot take address of bit-field %qD",
		   বৃক্ষ_OPERAND (x, 1));
	    ফেরত মিথ্যা;
	  }
	/* FALLTHRU */
      ক্ষেত্র ADDR_রাশিমালা:
      ক্ষেত্র ARRAY_REF:
      ক্ষেত্র REALPART_রাশিমালা:
      ক্ষেত্র IMAGPART_রাশিমালা:
	x = বৃক্ষ_OPERAND (x, 0);
	বিরতি;

      ক্ষেত্র COMPOUND_LITERAL_রাশিমালা:
	যদি (C_DECL_REGISTER (COMPOUND_LITERAL_রাশিমালা_DECL (x)))
	  {
	    যদি (override_register)
	      DECL_REGISTER (COMPOUND_LITERAL_রাশিমালা_DECL (x)) = 0;
	    অন্যথা
	      {
		error ("address of register compound literal requested");
		ফেরত মিথ্যা;
	      }
	  }
	বৃক্ষ_ADDRESSABLE (x) = 1;
	বৃক্ষ_ADDRESSABLE (COMPOUND_LITERAL_রাশিমালা_DECL (x)) = 1;
	ফেরত সত্য;

      ক্ষেত্র CONSTRUCTOR:
	বৃক্ষ_ADDRESSABLE (x) = 1;
	ফেরত সত্য;

      ক্ষেত্র VAR_DECL:
      ক্ষেত্র CONST_DECL:
      ক্ষেত্র PARM_DECL:
      ক্ষেত্র ফলাফল_DECL:
	যদি (C_DECL_REGISTER (x)
	    && DECL_NONLOCAL (x))
	  {
	    যদি (বৃক্ষ_PUBLIC (x) || is_global_var (x))
	      {
		error
		  ("global register variable %qD used in nested function", x);
		ফেরত মিথ্যা;
	      }
	    pedwarn (প্রবেশ_location, 0, "register variable %qD used in nested function", x);
	  }
	অন্যথা যদি (C_DECL_REGISTER (x))
	  {
	    যদি (বৃক্ষ_PUBLIC (x) || is_global_var (x))
	      error ("address of global register variable %qD requested", x);
	    অন্যথা যদি (override_register && !DECL_HARD_REGISTER (x))
	      {
		DECL_REGISTER (x) = 0;
		বৃক্ষ_ADDRESSABLE (x) = 1;
		mark_decl_used (x, সত্য);
		ফেরত সত্য;
	      }
	    অন্যথা
	      error ("address of register variable %qD requested", x);
	    ফেরত মিথ্যা;
	  }

	/* FALLTHRU */
      ক্ষেত্র FUNCTION_DECL:
	বৃক্ষ_ADDRESSABLE (x) = 1;
	mark_decl_used (x, সত্য);
	/* FALLTHRU */
      পূর্বনির্ধারিত:
	ফেরত সত্য;
    }
}

/* Convert EXPR to TYPE, warning about conversion problems with
   constants.  SEMANTIC_TYPE is the type this conversion would use
   without excess precision. If SEMANTIC_TYPE is NULL, this function
   is equivalent to convert_and_check. This function is a wrapper that
   handles conversions that may be different than
   the usual ones because of excess precision.  */

স্থির বৃক্ষ
ep_convert_and_check (location_t loc, বৃক্ষ type, বৃক্ষ রাশিমালা,
		      বৃক্ষ semantic_type)
{
  যদি (বৃক্ষ_TYPE (রাশিমালা) == type)
    ফেরত রাশিমালা;

  /* For C11, integer conversions may have results with excess
     precision.  */
  যদি (flag_isoc11 || !semantic_type)
    ফেরত convert_and_check (loc, type, রাশিমালা);

  যদি (বৃক্ষ_CODE (বৃক্ষ_TYPE (রাশিমালা)) == INTEGER_TYPE
      && বৃক্ষ_TYPE (রাশিমালা) != semantic_type)
    {
      /* For integers, we need to check the real conversion, not
	 the conversion to the excess precision type.  */
      রাশিমালা = convert_and_check (loc, semantic_type, রাশিমালা);
    }
  /* Result type is the excess precision type, which should be
     large enough, so do not check.  */
  ফেরত convert (type, রাশিমালা);
}

/* If EXPR refers to a built-in declared without a prototype returns
   the actual type of the built-in and, if non-null, set *BLTIN to
   a pointer to the built-in.  Otherwise return the type of EXPR
   and clear *BLTIN if non-null.  */

স্থির বৃক্ষ
type_or_builtin_type (বৃক্ষ রাশিমালা, বৃক্ষ *bltin = ফাঁকা)
{
  বৃক্ষ dummy;
  যদি (!bltin)
    bltin = &dummy;

  *bltin = NULL_বৃক্ষ;

  বৃক্ষ type = বৃক্ষ_TYPE (রাশিমালা);
  যদি (বৃক্ষ_CODE (রাশিমালা) != ADDR_রাশিমালা)
    ফেরত type;

  বৃক্ষ oper = বৃক্ষ_OPERAND (রাশিমালা, 0);
  যদি (!DECL_P (oper)
      || বৃক্ষ_CODE (oper) != FUNCTION_DECL
      || !fndecl_built_in_p (oper, BUILT_IN_NORMAL))
    ফেরত type;

  built_in_function code = DECL_FUNCTION_CODE (oper);
  যদি (!C_DECL_BUILTIN_PROTOTYPE (oper))
    ফেরত type;

  যদি ((*bltin = builtin_decl_implicit (code)))
    type = c_build_pointer_type (বৃক্ষ_TYPE (*bltin));

  ফেরত type;
}

/* Build and return a conditional expression IFEXP ? OP1 : OP2.  If
   IFEXP_BCP then the condition is a call to __builtin_constant_p, and
   if folded to an integer constant then the unselected half may
   contain arbitrary operations not normally permitted in constant
   expressions.  Set the location of the expression to LOC.  */

বৃক্ষ
build_conditional_রাশিমালা (location_t colon_loc, বৃক্ষ ifexp, যৌক্তিক ifexp_bcp,
			বৃক্ষ op1, বৃক্ষ op1_original_type, location_t op1_loc,
			বৃক্ষ op2, বৃক্ষ op2_original_type, location_t op2_loc)
{
  বৃক্ষ type1;
  বৃক্ষ type2;
  বৃক্ষ ফলাফল_type = ফাঁকা;
  বৃক্ষ semantic_ফলাফল_type = ফাঁকা;
  বৃক্ষ orig_op1 = op1, orig_op2 = op2;
  যৌক্তিক int_const, op1_int_operands, op2_int_operands, int_operands;
  যৌক্তিক ifexp_int_operands;
  বৃক্ষ ret;

  op1_int_operands = রাশিমালা_INT_CONST_OPERANDS (orig_op1);
  যদি (op1_int_operands)
    op1 = remove_c_maybe_const_রাশিমালা (op1);
  op2_int_operands = রাশিমালা_INT_CONST_OPERANDS (orig_op2);
  যদি (op2_int_operands)
    op2 = remove_c_maybe_const_রাশিমালা (op2);
  ifexp_int_operands = রাশিমালা_INT_CONST_OPERANDS (ifexp);
  যদি (ifexp_int_operands)
    ifexp = remove_c_maybe_const_রাশিমালা (ifexp);

  /* Promote both alternatives.  */

  যদি (বৃক্ষ_CODE (বৃক্ষ_TYPE (op1)) != VOID_TYPE)
    op1 = default_conversion (op1);
  যদি (বৃক্ষ_CODE (বৃক্ষ_TYPE (op2)) != VOID_TYPE)
    op2 = default_conversion (op2);

  যদি (বৃক্ষ_CODE (ifexp) == ERROR_MARK
      || বৃক্ষ_CODE (বৃক্ষ_TYPE (op1)) == ERROR_MARK
      || বৃক্ষ_CODE (বৃক্ষ_TYPE (op2)) == ERROR_MARK)
    ফেরত error_mark_গ্রন্থি;

  বৃক্ষ bltin1 = NULL_বৃক্ষ;
  বৃক্ষ bltin2 = NULL_বৃক্ষ;
  type1 = type_or_builtin_type (op1, &bltin1);
  ধ্রুবক গণনা বৃক্ষ_code code1 = বৃক্ষ_CODE (type1);
  type2 = type_or_builtin_type (op2, &bltin2);
  ধ্রুবক গণনা বৃক্ষ_code code2 = বৃক্ষ_CODE (type2);

  যদি (code1 == POINTER_TYPE && reject_gcc_builtin (op1))
    ফেরত error_mark_গ্রন্থি;

  যদি (code2 == POINTER_TYPE && reject_gcc_builtin (op2))
    ফেরত error_mark_গ্রন্থি;

  /* C90 does not permit non-lvalue arrays in conditional expressions.
     In C99 they will be pointers by now.  */
  যদি (code1 == ARRAY_TYPE || code2 == ARRAY_TYPE)
    {
      error_at (colon_loc, "non-lvalue array in conditional expression");
      ফেরত error_mark_গ্রন্থি;
    }

  যদি ((বৃক্ষ_CODE (op1) == EXCESS_PRECISION_রাশিমালা
       || বৃক্ষ_CODE (op2) == EXCESS_PRECISION_রাশিমালা)
      && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	  || code1 == COMPLEX_TYPE || code1 == BITINT_TYPE)
      && (code2 == INTEGER_TYPE || code2 == REAL_TYPE
	  || code2 == COMPLEX_TYPE || code2 == BITINT_TYPE))
    {
      semantic_ফলাফল_type = c_common_type (type1, type2);
      যদি (বৃক্ষ_CODE (op1) == EXCESS_PRECISION_রাশিমালা)
	{
	  op1 = বৃক্ষ_OPERAND (op1, 0);
	  type1 = বৃক্ষ_TYPE (op1);
	  gcc_assert (বৃক্ষ_CODE (type1) == code1);
	}
      যদি (বৃক্ষ_CODE (op2) == EXCESS_PRECISION_রাশিমালা)
	{
	  op2 = বৃক্ষ_OPERAND (op2, 0);
	  type2 = বৃক্ষ_TYPE (op2);
	  gcc_assert (বৃক্ষ_CODE (type2) == code2);
	}
    }

  যদি (warn_cxx_compat)
    {
      বৃক্ষ t1 = op1_original_type ? op1_original_type : বৃক্ষ_TYPE (orig_op1);
      বৃক্ষ t2 = op2_original_type ? op2_original_type : বৃক্ষ_TYPE (orig_op2);

      যদি (বৃক্ষ_CODE (t1) == ENUMERAL_TYPE
	  && বৃক্ষ_CODE (t2) == ENUMERAL_TYPE
	  && TYPE_MAIN_VARIANT (t1) != TYPE_MAIN_VARIANT (t2))
	warning_at (colon_loc, OPT_Wc___compat,
		    "different enum types in conditional is "
		    "invalid in C++: %qT vs %qT", t1, t2);
    }

  যদি (warn_zero_as_null_pointer_constant
      && c_inhibit_evaluation_warnings == 0)
    {
      যদি ((code1 == POINTER_TYPE || code1 == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type2) && null_pointer_constant_p (orig_op2))
	warning_at (op2_loc, OPT_Wzero_as_null_pointer_constant,
		    "zero as null pointer constant");

      যদি ((code2 == POINTER_TYPE || code2 == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type1) && null_pointer_constant_p (orig_op1))
	warning_at (op1_loc, OPT_Wzero_as_null_pointer_constant,
		    "zero as null pointer constant");
    }

  /* Quickly detect the usual case where op1 and op2 have the same type
     after promotion.  */
  যদি (TYPE_MAIN_VARIANT (type1) == TYPE_MAIN_VARIANT (type2))
    {
      যদি (type1 == type2)
	ফলাফল_type = type1;
      অন্যথা
	ফলাফল_type = TYPE_MAIN_VARIANT (type1);
    }
  অন্যথা যদি ((code1 == INTEGER_TYPE || code1 == REAL_TYPE
	    || code1 == COMPLEX_TYPE || code1 == BITINT_TYPE)
	   && (code2 == INTEGER_TYPE || code2 == REAL_TYPE
	       || code2 == COMPLEX_TYPE || code2 == BITINT_TYPE))
    {
      /* In C11, a conditional expression between a floating-point
	 type and an integer type should convert the integer type to
	 the evaluation format of the floating-point type, with
	 possible excess precision.  */
      বৃক্ষ eptype1 = type1;
      বৃক্ষ eptype2 = type2;
      যদি (flag_isoc11)
	{
	  বৃক্ষ eptype;
	  যদি (ANY_INTEGRAL_TYPE_P (type1)
	      && (eptype = excess_precision_type (type2)) != NULL_বৃক্ষ)
	    {
	      eptype2 = eptype;
	      যদি (!semantic_ফলাফল_type)
		semantic_ফলাফল_type = c_common_type (type1, type2);
	    }
	  অন্যথা যদি (ANY_INTEGRAL_TYPE_P (type2)
		   && (eptype = excess_precision_type (type1)) != NULL_বৃক্ষ)
	    {
	      eptype1 = eptype;
	      যদি (!semantic_ফলাফল_type)
		semantic_ফলাফল_type = c_common_type (type1, type2);
	    }
	}
      ফলাফল_type = c_common_type (eptype1, eptype2);
      যদি (ফলাফল_type == error_mark_গ্রন্থি)
	ফেরত error_mark_গ্রন্থি;
      do_warn_double_promotion (ফলাফল_type, type1, type2,
				"implicit conversion from %qT to %qT to "
				"match other result of conditional",
				colon_loc);

      /* If -Wsign-compare, warn here if type1 and type2 have
	 different signedness.  We'll promote the signed to unsigned
	 and later code won't know it used to be different.
	 Do this check on the original types, so that explicit casts
	 will be considered, but default promotions won't.  */
      যদি (c_inhibit_evaluation_warnings == 0)
	{
	  পূর্ণসংখ্যা unsigned_op1 = TYPE_UNSIGNED (বৃক্ষ_TYPE (orig_op1));
	  পূর্ণসংখ্যা unsigned_op2 = TYPE_UNSIGNED (বৃক্ষ_TYPE (orig_op2));

	  যদি (unsigned_op1 ^ unsigned_op2)
	    {
	      /* Do not warn if the result type is signed, since the
		 signed type will only be chosen if it can represent
		 all the values of the unsigned type.  */
	      যদি (!TYPE_UNSIGNED (ফলাফল_type))
		/* OK */;
	      অন্যথা
		{
		  যৌক্তিক op1_maybe_const = সত্য;
		  যৌক্তিক op2_maybe_const = সত্য;

		  /* Do not warn if the signed quantity is an
		     unsuffixed integer literal (or some static
		     constant expression involving such literals) and
		     it is non-negative.  This warning requires the
		     operands to be folded for best results, so do
		     that folding in this case even without
		     warn_sign_compare to avoid warning options
		     possibly affecting code generation.  */
		  c_inhibit_evaluation_warnings
		    += (ifexp == truthvalue_false_গ্রন্থি);
		  op1 = c_fully_fold (op1, require_constant_মান,
				      &op1_maybe_const);
		  c_inhibit_evaluation_warnings
		    -= (ifexp == truthvalue_false_গ্রন্থি);

		  c_inhibit_evaluation_warnings
		    += (ifexp == truthvalue_true_গ্রন্থি);
		  op2 = c_fully_fold (op2, require_constant_মান,
				      &op2_maybe_const);
		  c_inhibit_evaluation_warnings
		    -= (ifexp == truthvalue_true_গ্রন্থি);

		  যদি (warn_sign_compare)
		    {
		      যদি ((unsigned_op2
			   && বৃক্ষ_রাশিমালা_nonnegative_p (op1))
			  || (unsigned_op1
			      && বৃক্ষ_রাশিমালা_nonnegative_p (op2)))
			/* OK */;
		      অন্যথা যদি (unsigned_op2)
			warning_at (op1_loc, OPT_Wsign_compare,
				    "operand of %<?:%> changes signedness from "
				    "%qT to %qT due to unsignedness of other "
				    "operand", বৃক্ষ_TYPE (orig_op1),
				    বৃক্ষ_TYPE (orig_op2));
		      অন্যথা
			warning_at (op2_loc, OPT_Wsign_compare,
				    "operand of %<?:%> changes signedness from "
				    "%qT to %qT due to unsignedness of other "
				    "operand", বৃক্ষ_TYPE (orig_op2),
				    বৃক্ষ_TYPE (orig_op1));
		    }
		  যদি (!op1_maybe_const || বৃক্ষ_CODE (op1) != INTEGER_CST)
		    op1 = c_wrap_maybe_const (op1, !op1_maybe_const);
		  যদি (!op2_maybe_const || বৃক্ষ_CODE (op2) != INTEGER_CST)
		    op2 = c_wrap_maybe_const (op2, !op2_maybe_const);
		}
	    }
	}
    }
  অন্যথা যদি (code1 == VOID_TYPE || code2 == VOID_TYPE)
    {
      যদি (code1 != VOID_TYPE || code2 != VOID_TYPE)
	pedwarn (colon_loc, OPT_Wpedantic,
		 "ISO C forbids conditional expr with only one void side");
      ফলাফল_type = void_type_গ্রন্থি;
    }
  অন্যথা যদি (code1 == POINTER_TYPE && code2 == POINTER_TYPE)
    {
      addr_space_t as1 = TYPE_ADDR_SPACE (বৃক্ষ_TYPE (type1));
      addr_space_t as2 = TYPE_ADDR_SPACE (বৃক্ষ_TYPE (type2));
      addr_space_t as_common;

      যদি (comp_target_types (colon_loc, type1, type2))
	{
	  ifexp = save_রাশিমালা (ifexp);
	  ফলাফল_type = common_pointer_type (type1, type2, ifexp);
	}
      অন্যথা যদি (null_pointer_constant_p (orig_op1))
	ফলাফল_type = type2;
      অন্যথা যদি (null_pointer_constant_p (orig_op2))
	ফলাফল_type = type1;
      অন্যথা যদি (!addr_space_superset (as1, as2, &as_common))
	{
	  error_at (colon_loc, "pointers to disjoint address spaces "
		    "used in conditional expression");
	  ফেরত error_mark_গ্রন্থি;
	}
      অন্যথা যদি ((VOID_TYPE_P (বৃক্ষ_TYPE (type1))
		&& !TYPE_ATOMIC (বৃক্ষ_TYPE (type1)))
	       || (VOID_TYPE_P (বৃক্ষ_TYPE (type2))
		   && !TYPE_ATOMIC (বৃক্ষ_TYPE (type2))))
	{
	  বৃক্ষ t1 = বৃক্ষ_TYPE (type1);
	  বৃক্ষ t2 = বৃক্ষ_TYPE (type2);
	  যদি (!(VOID_TYPE_P (t1)
		&& !TYPE_ATOMIC (t1)))
	   {
	     /* roles are swapped */
	     t1 = t2;
	     t2 = বৃক্ষ_TYPE (type1);
	   }
	  বৃক্ষ t2_stripped = strip_array_types (t2);
	  যদি ((বৃক্ষ_CODE (t2) == ARRAY_TYPE)
	      && (TYPE_QUALS (t2_stripped) & ~TYPE_QUALS (t1)))
	    {
	      যদি (!flag_isoc23)
		warning_at (colon_loc, OPT_Wdiscarded_array_qualifiers,
			    "pointer to array loses qualifier "
			    "in conditional expression");
	      অন্যথা যদি (warn_c11_c23_compat > 0)
		warning_at (colon_loc, OPT_Wc11_c23_compat,
			    "pointer to array loses qualifier "
			    "in conditional expression in ISO C before C23");
	    }
	  যদি (বৃক্ষ_CODE (t2) == FUNCTION_TYPE)
	    pedwarn (colon_loc, OPT_Wpedantic,
		     "ISO C forbids conditional expr between "
		     "%<void *%> and function pointer");
	  /* for array, use qualifiers of element type */
	  যদি (flag_isoc23)
	    t2 = t2_stripped;
	  ফলাফল_type = c_build_pointer_type (qualify_type (t1, t2));
	}
      /* Objective-C pointer comparisons are a bit more lenient.  */
      অন্যথা যদি (objc_have_common_type (type1, type2, -3, NULL_বৃক্ষ))
	ফলাফল_type = objc_common_type (type1, type2);
      অন্যথা
	{
	  পূর্ণসংখ্যা qual = ENCODE_QUAL_ADDR_SPACE (as_common);
	  গণনা diagnostics::kind kind = diagnostics::kind::permerror;
	  যদি (!flag_isoc99)
	    /* This downgrade to a warning ensures that -std=gnu89
	       -pedantic-errors does not flag these mismatches between
	       builtins as errors (as diagnostics::kind::permerror would)
	       ISO C99 and later do not have implicit function declarations,
	       so the mismatch cannot occur naturally there.  */
	    kind = (bltin1 && bltin2
		    ? diagnostics::kind::warning
		    : diagnostics::kind::pedwarn);
	  যদি (emit_diagnostic (kind, colon_loc, OPT_Wincompatible_pointer_types,
			       "pointer type mismatch "
			       "in conditional expression"))
	    {
	      inform (op1_loc, "first expression has type %qT", type1);
	      inform (op2_loc, "second expression has type %qT", type2);
	    }
	  ফলাফল_type = c_build_pointer_type
			  (c_build_qualified_type (void_type_গ্রন্থি, qual));
	}
    }
  অন্যথা যদি (code1 == POINTER_TYPE
	   && (code2 == INTEGER_TYPE || code2 == BITINT_TYPE))
    {
      যদি (!null_pointer_constant_p (orig_op2))
	permerror_opt (colon_loc, OPT_Wint_conversion,
		       "pointer/integer type mismatch "
		       "in conditional expression");
      অন্যথা
	{
	  op2 = null_pointer_গ্রন্থি;
	}
      ফলাফল_type = type1;
    }
  অন্যথা যদি (code2 == POINTER_TYPE
	   && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
    {
      যদি (!null_pointer_constant_p (orig_op1))
	permerror_opt (colon_loc, OPT_Wint_conversion,
		       "pointer/integer type mismatch "
		       "in conditional expression");
      অন্যথা
	{
	  op1 = null_pointer_গ্রন্থি;
	}
      ফলাফল_type = type2;
    }
  /* 6.5.15: "if one is a null pointer constant (other than a pointer) or has
     type nullptr_t and the other is a pointer, the result type is the pointer
     type."  */
  অন্যথা যদি (code1 == NULLPTR_TYPE && code2 == POINTER_TYPE)
    ফলাফল_type = type2;
  অন্যথা যদি (code1 == POINTER_TYPE && code2 == NULLPTR_TYPE)
    ফলাফল_type = type1;
  অন্যথা যদি (RECORD_OR_UNION_TYPE_P (type1) && RECORD_OR_UNION_TYPE_P (type2)
	   && comptypes (TYPE_MAIN_VARIANT (type1),
			 TYPE_MAIN_VARIANT (type2)))
    ফলাফল_type = composite_type (TYPE_MAIN_VARIANT (type1),
				  TYPE_MAIN_VARIANT (type2));

  যদি (!ফলাফল_type)
    {
      যদি (flag_cond_mismatch)
	ফলাফল_type = void_type_গ্রন্থি;
      অন্যথা
	{
	  error_at (colon_loc, "type mismatch in conditional expression");
	  ফেরত error_mark_গ্রন্থি;
	}
    }

  /* Merge const and volatile flags of the incoming types.  */
  ফলাফল_type
    = build_type_variant (ফলাফল_type,
			  TYPE_READONLY (type1) || TYPE_READONLY (type2),
			  TYPE_VOLATILE (type1) || TYPE_VOLATILE (type2));

  op1 = ep_convert_and_check (colon_loc, ফলাফল_type, op1,
			      semantic_ফলাফল_type);
  op2 = ep_convert_and_check (colon_loc, ফলাফল_type, op2,
			      semantic_ফলাফল_type);

  যদি (ifexp_bcp && ifexp == truthvalue_true_গ্রন্থি)
    {
      op2_int_operands = সত্য;
      op1 = c_fully_fold (op1, require_constant_মান, ফাঁকা);
    }
  যদি (ifexp_bcp && ifexp == truthvalue_false_গ্রন্থি)
    {
      op1_int_operands = সত্য;
      op2 = c_fully_fold (op2, require_constant_মান, ফাঁকা);
    }
  int_const = int_operands = (ifexp_int_operands
			      && op1_int_operands
			      && op2_int_operands);
  যদি (int_operands)
    {
      int_const = ((ifexp == truthvalue_true_গ্রন্থি
		    && বৃক্ষ_CODE (orig_op1) == INTEGER_CST
		    && !বৃক্ষ_OVERFLOW (orig_op1))
		   || (ifexp == truthvalue_false_গ্রন্থি
		       && বৃক্ষ_CODE (orig_op2) == INTEGER_CST
		       && !বৃক্ষ_OVERFLOW (orig_op2)));
    }

  /* Need to convert condition operand into a vector mask.  */
  যদি (VECTOR_TYPE_P (বৃক্ষ_TYPE (ifexp)))
    {
      বৃক্ষ vectype = বৃক্ষ_TYPE (ifexp);
      বৃক্ষ elem_type = বৃক্ষ_TYPE (vectype);
      বৃক্ষ zero = build_int_cst (elem_type, 0);
      বৃক্ষ zero_vec = build_vector_from_val (vectype, zero);
      বৃক্ষ cmp_type = truth_type_for (vectype);
      ifexp = build2 (NE_রাশিমালা, cmp_type, ifexp, zero_vec);
    }

  যদি (int_const || (ifexp_bcp && বৃক্ষ_CODE (ifexp) == INTEGER_CST))
    ret = fold_build3_loc (colon_loc, COND_রাশিমালা, ফলাফল_type, ifexp, op1, op2);
  অন্যথা
    {
      যদি (int_operands)
	{
	  /* Use c_fully_fold here, since C_MAYBE_CONST_EXPR might be
	     nested inside of the expression.  */
	  op1 = c_fully_fold (op1, মিথ্যা, ফাঁকা);
	  op2 = c_fully_fold (op2, মিথ্যা, ফাঁকা);
	}
      ret = build3 (COND_রাশিমালা, ফলাফল_type, ifexp, op1, op2);
      যদি (int_operands)
	ret = note_integer_operands (ret);
    }
  যদি (semantic_ফলাফল_type)
    ret = build1 (EXCESS_PRECISION_রাশিমালা, semantic_ফলাফল_type, ret);

  protected_set_রাশিমালা_location (ret, colon_loc);

  /* If the OP1 and OP2 are the same and don't have side-effects,
     warn here, because the COND_EXPR will be turned into OP1.  */
  যদি (warn_duplicated_branches
      && বৃক্ষ_CODE (ret) == COND_রাশিমালা
      && (op1 == op2 || operand_equal_p (op1, op2, OEP_ADDRESS_OF_SAME_FIELD)))
    warning_at (রাশিমালা_LOCATION (ret), OPT_Wduplicated_branches,
		"this condition has identical branches");

  ফেরত ret;
}

/* EXPR is an expression, location LOC, whose result is discarded.
   Warn if it is a call to a nodiscard function (or a COMPOUND_EXPR
   whose right-hand operand is such a call, possibly recursively).  */

স্থির শূন্য
maybe_warn_nodiscard (location_t loc, বৃক্ষ রাশিমালা)
{
  যদি (VOID_TYPE_P (বৃক্ষ_TYPE (রাশিমালা)))
    ফেরত;
  যখন (বৃক্ষ_CODE (রাশিমালা) == COMPOUND_রাশিমালা)
    {
      রাশিমালা = বৃক্ষ_OPERAND (রাশিমালা, 1);
      যদি (রাশিমালা_HAS_LOCATION (রাশিমালা))
	loc = রাশিমালা_LOCATION (রাশিমালা);
    }
  যদি (বৃক্ষ_CODE (রাশিমালা) != CALL_রাশিমালা)
    ফেরত;
  বৃক্ষ fn = CALL_রাশিমালা_FN (রাশিমালা);
  যদি (!fn)
    ফেরত;
  বৃক্ষ attr;
  যদি (বৃক্ষ_CODE (fn) == ADDR_রাশিমালা
      && বৃক্ষ_CODE (বৃক্ষ_OPERAND (fn, 0)) == FUNCTION_DECL
      && (attr = lookup_attribute ("nodiscard",
				   DECL_ATTRIBUTES (বৃক্ষ_OPERAND (fn, 0)))))
    {
      fn = বৃক্ষ_OPERAND (fn, 0);
      বৃক্ষ args = বৃক্ষ_মান (attr);
      যদি (args)
	args = বৃক্ষ_মান (args);
      auto_diagnostic_group d;
      auto_urlify_attributes sentinel;
      পূর্ণসংখ্যা warned;
      যদি (args)
	warned = warning_at (loc, OPT_Wunused_ফলাফল,
			     "ignoring return value of %qD, declared with "
			     "attribute %<nodiscard%>: %E", fn, args);
      অন্যথা
	warned = warning_at (loc, OPT_Wunused_ফলাফল,
			     "ignoring return value of %qD, declared with "
			     "attribute %<nodiscard%>", fn);
      যদি (warned)
	inform (DECL_SOURCE_LOCATION (fn), "declared here");
    }
  অন্যথা
    {
      বৃক্ষ rettype = বৃক্ষ_TYPE (বৃক্ষ_TYPE (বৃক্ষ_TYPE (fn)));
      attr = lookup_attribute ("nodiscard", TYPE_ATTRIBUTES (rettype));
      যদি (!attr)
	ফেরত;
      বৃক্ষ args = বৃক্ষ_মান (attr);
      যদি (args)
	args = বৃক্ষ_মান (args);
      auto_diagnostic_group d;
      auto_urlify_attributes sentinel;
      পূর্ণসংখ্যা warned;
      যদি (args)
	warned = warning_at (loc, OPT_Wunused_ফলাফল,
			     "ignoring return value of type %qT, declared "
			     "with attribute %<nodiscard%>: %E",
			     rettype, args);
      অন্যথা
	warned = warning_at (loc, OPT_Wunused_ফলাফল,
			     "ignoring return value of type %qT, declared "
			     "with attribute %<nodiscard%>", rettype);
      যদি (warned)
	{
	  যদি (বৃক্ষ_CODE (fn) == ADDR_রাশিমালা)
	    {
	      fn = বৃক্ষ_OPERAND (fn, 0);
	      যদি (বৃক্ষ_CODE (fn) == FUNCTION_DECL)
		inform (DECL_SOURCE_LOCATION (fn),
			"in call to %qD, declared here", fn);
	    }
	}
    }
}

/* Return a compound expression that performs two expressions and
   returns the value of the second of them.

   LOC is the location of the COMPOUND_EXPR.  */

বৃক্ষ
build_compound_রাশিমালা (location_t loc, বৃক্ষ expr1, বৃক্ষ expr2)
{
  যৌক্তিক expr1_int_operands, expr2_int_operands;
  বৃক্ষ eptype = NULL_বৃক্ষ;
  বৃক্ষ ret;

  expr1_int_operands = রাশিমালা_INT_CONST_OPERANDS (expr1);
  যদি (expr1_int_operands)
    expr1 = remove_c_maybe_const_রাশিমালা (expr1);
  expr2_int_operands = রাশিমালা_INT_CONST_OPERANDS (expr2);
  যদি (expr2_int_operands)
    expr2 = remove_c_maybe_const_রাশিমালা (expr2);

  যদি (বৃক্ষ_CODE (expr1) == EXCESS_PRECISION_রাশিমালা)
    expr1 = বৃক্ষ_OPERAND (expr1, 0);
  যদি (বৃক্ষ_CODE (expr2) == EXCESS_PRECISION_রাশিমালা)
    {
      eptype = বৃক্ষ_TYPE (expr2);
      expr2 = বৃক্ষ_OPERAND (expr2, 0);
    }

  যদি (!বৃক্ষ_SIDE_EFFECTS (expr1))
    {
      /* The left-hand operand of a comma expression is like an expression
	 statement: with -Wunused, we should warn if it doesn't have
	 any side-effects, unless it was explicitly cast to (void).  */
      যদি (warn_unused_মান)
	{
	  যদি (VOID_TYPE_P (বৃক্ষ_TYPE (expr1))
	      && CONVERT_রাশিমালা_P (expr1))
	    ; /* (void) a, b */
	  অন্যথা যদি (VOID_TYPE_P (বৃক্ষ_TYPE (expr1))
		   && বৃক্ষ_CODE (expr1) == COMPOUND_রাশিমালা
		   && CONVERT_রাশিমালা_P (বৃক্ষ_OPERAND (expr1, 1)))
	    ; /* (void) a, (void) b, c */
	  অন্যথা
	    warning_at (loc, OPT_Wunused_মান,
			"left-hand operand of comma expression has no effect");
	}
    }
  অন্যথা যদি (বৃক্ষ_CODE (expr1) == COMPOUND_রাশিমালা
	   && warn_unused_মান)
    {
      বৃক্ষ r = expr1;
      location_t cloc = loc;
      যখন (বৃক্ষ_CODE (r) == COMPOUND_রাশিমালা)
        {
	  যদি (রাশিমালা_HAS_LOCATION (r))
	    cloc = রাশিমালা_LOCATION (r);
	  r = বৃক্ষ_OPERAND (r, 1);
	}
      যদি (!বৃক্ষ_SIDE_EFFECTS (r)
	  && !VOID_TYPE_P (বৃক্ষ_TYPE (r))
	  && !CONVERT_রাশিমালা_P (r))
	warning_at (cloc, OPT_Wunused_মান,
	            "right-hand operand of comma expression has no effect");
    }

  /* With -Wunused, we should also warn if the left-hand operand does have
     side-effects, but computes a value which is not used.  For example, in
     `foo() + bar(), baz()' the result of the `+' operator is not used,
     so we should issue a warning.  */
  অন্যথা যদি (warn_unused_মান)
    warn_if_unused_মান (expr1, loc);

  maybe_warn_nodiscard (loc, expr1);

  যদি (expr2 == error_mark_গ্রন্থি)
    ফেরত error_mark_গ্রন্থি;

  ret = build2 (COMPOUND_রাশিমালা, বৃক্ষ_TYPE (expr2), expr1, expr2);

  যদি (flag_isoc99
      && expr1_int_operands
      && expr2_int_operands)
    ret = note_integer_operands (ret);

  যদি (eptype)
    ret = build1 (EXCESS_PRECISION_রাশিমালা, eptype, ret);

  protected_set_রাশিমালা_location (ret, loc);
  ফেরত ret;
}

/* Issue -Wcast-qual warnings when appropriate.  TYPE is the type to
   which we are casting.  OTYPE is the type of the expression being
   cast.  Both TYPE and OTYPE are pointer types.  LOC is the location
   of the cast.  -Wcast-qual appeared on the command line.  Named
   address space qualifiers are not handled here, because they result
   in different warnings.  */

স্থির শূন্য
handle_warn_cast_qual (location_t loc, বৃক্ষ type, বৃক্ষ otype)
{
  বৃক্ষ in_type = type;
  বৃক্ষ in_otype = otype;
  পূর্ণসংখ্যা added = 0;
  পূর্ণসংখ্যা discarded = 0;
  যৌক্তিক is_const;

  /* Check that the qualifiers on IN_TYPE are a superset of the
     qualifiers of IN_OTYPE.  The outermost level of POINTER_TYPE
     nodes is uninteresting and we stop as soon as we hit a
     non-POINTER_TYPE node on either type.  */
  করো
    {
      in_otype = বৃক্ষ_TYPE (in_otype);
      in_type = বৃক্ষ_TYPE (in_type);

      /* GNU C allows cv-qualified function types.  'const' means the
	 function is very pure, 'volatile' means it can't return.  We
	 need to warn when such qualifiers are added, not when they're
	 taken away.  */
      যদি (বৃক্ষ_CODE (in_otype) == FUNCTION_TYPE
	  && বৃক্ষ_CODE (in_type) == FUNCTION_TYPE)
	added |= (TYPE_QUALS_NO_ADDR_SPACE (in_type)
		  & ~TYPE_QUALS_NO_ADDR_SPACE (in_otype));
      অন্যথা
	discarded |= (TYPE_QUALS_NO_ADDR_SPACE (in_otype)
		      & ~TYPE_QUALS_NO_ADDR_SPACE (in_type));
    }
  যখন (বৃক্ষ_CODE (in_type) == POINTER_TYPE
	 && বৃক্ষ_CODE (in_otype) == POINTER_TYPE);

  যদি (added)
    warning_at (loc, OPT_Wcast_qual,
		"cast adds %q#v qualifier to function type", added);

  যদি (discarded)
    /* There are qualifiers present in IN_OTYPE that are not present
       in IN_TYPE.  */
    warning_at (loc, OPT_Wcast_qual,
		"cast discards %qv qualifier from pointer target type",
		discarded);

  যদি (added || discarded)
    ফেরত;

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

  যদি (TYPE_MAIN_VARIANT (in_type) != TYPE_MAIN_VARIANT (in_otype))
    ফেরত;
  যদি (বৃক্ষ_CODE (বৃক্ষ_TYPE (type)) != POINTER_TYPE)
    ফেরত;

  in_type = type;
  in_otype = otype;
  is_const = TYPE_READONLY (বৃক্ষ_TYPE (in_type));
  করো
    {
      in_type = বৃক্ষ_TYPE (in_type);
      in_otype = বৃক্ষ_TYPE (in_otype);
      যদি ((TYPE_QUALS (in_type) &~ TYPE_QUALS (in_otype)) != 0
	  && !is_const)
	{
	  warning_at (loc, OPT_Wcast_qual,
		      "to be safe all intermediate pointers in cast from "
                      "%qT to %qT must be %<const%> qualified",
		      otype, type);
	  বিরতি;
	}
      যদি (is_const)
	is_const = TYPE_READONLY (in_type);
    }
  যখন (বৃক্ষ_CODE (in_type) == POINTER_TYPE);
}

/* Heuristic check if two parameter types can be considered ABI-equivalent.  */

স্থির যৌক্তিক
c_safe_arg_type_equiv_p (বৃক্ষ t1, বৃক্ষ t2)
{
  যদি (error_operand_p (t1) || error_operand_p (t2))
    ফেরত সত্য;

  t1 = TYPE_MAIN_VARIANT (t1);
  t2 = TYPE_MAIN_VARIANT (t2);

  যদি (বৃক্ষ_CODE (t1) == POINTER_TYPE
      && বৃক্ষ_CODE (t2) == POINTER_TYPE)
    ফেরত সত্য;

  /* Only the precision of the parameter matters.  This check should
     make sure that the callee does not see undefined values in argument
     registers.  */
  যদি (INTEGRAL_TYPE_P (t1)
      && INTEGRAL_TYPE_P (t2)
      && TYPE_PRECISION (t1) == TYPE_PRECISION (t2))
    ফেরত সত্য;

  ফেরত comptypes (t1, t2);
}

/* Check if a type cast between two function types can be considered safe.  */

স্থির যৌক্তিক
c_safe_function_type_cast_p (বৃক্ষ t1, বৃক্ষ t2)
{
  যদি (বৃক্ষ_TYPE (t1) == void_type_গ্রন্থি &&
      TYPE_ARG_TYPES (t1) == void_list_গ্রন্থি)
    ফেরত সত্য;

  যদি (বৃক্ষ_TYPE (t2) == void_type_গ্রন্থি &&
      TYPE_ARG_TYPES (t2) == void_list_গ্রন্থি)
    ফেরত সত্য;

  যদি (!c_safe_arg_type_equiv_p (বৃক্ষ_TYPE (t1), বৃক্ষ_TYPE (t2)))
    ফেরত মিথ্যা;

  জন্য (t1 = TYPE_ARG_TYPES (t1), t2 = TYPE_ARG_TYPES (t2);
       t1 && t2;
       t1 = বৃক্ষ_CHAIN (t1), t2 = বৃক্ষ_CHAIN (t2))
    যদি (!c_safe_arg_type_equiv_p (বৃক্ষ_মান (t1), বৃক্ষ_মান (t2)))
      ফেরত মিথ্যা;

  ফেরত সত্য;
}

/* Build an expression representing a cast to type TYPE of expression EXPR.
   LOC is the location of the cast-- typically the open paren of the cast.  */

বৃক্ষ
build_c_cast (location_t loc, বৃক্ষ type, বৃক্ষ রাশিমালা)
{
  বৃক্ষ মান;

  যৌক্তিক int_operands = রাশিমালা_INT_CONST_OPERANDS (রাশিমালা);

  যদি (বৃক্ষ_CODE (রাশিমালা) == EXCESS_PRECISION_রাশিমালা)
    রাশিমালা = বৃক্ষ_OPERAND (রাশিমালা, 0);

  মান = রাশিমালা;
  যদি (int_operands)
    মান = remove_c_maybe_const_রাশিমালা (মান);

  যদি (type == error_mark_গ্রন্থি || রাশিমালা == error_mark_গ্রন্থি)
    ফেরত error_mark_গ্রন্থি;

  /* The ObjC front-end uses TYPE_MAIN_VARIANT to tie together types differing
     only in <protocol> qualifications.  But when constructing cast expressions,
     the protocols do matter and must be kept around.  */
  যদি (objc_is_object_ptr (type) && objc_is_object_ptr (বৃক্ষ_TYPE (রাশিমালা)))
    ফেরত build1 (NOP_রাশিমালা, type, রাশিমালা);

  type = TYPE_MAIN_VARIANT (type);

  যদি (বৃক্ষ_CODE (type) == ARRAY_TYPE)
    {
      error_at (loc, "cast specifies array type");
      ফেরত error_mark_গ্রন্থি;
    }

  যদি (বৃক্ষ_CODE (type) == FUNCTION_TYPE)
    {
      error_at (loc, "cast specifies function type");
      ফেরত error_mark_গ্রন্থি;
    }

  যদি (!VOID_TYPE_P (type))
    {
      মান = require_complete_type (loc, মান);
      যদি (মান == error_mark_গ্রন্থি)
	ফেরত error_mark_গ্রন্থি;
    }

  যদি (type == TYPE_MAIN_VARIANT (বৃক্ষ_TYPE (মান)))
    {
      যদি (RECORD_OR_UNION_TYPE_P (type)
	  && pedwarn (loc, OPT_Wpedantic,
		      "ISO C forbids casting nonscalar to the same type"))
	      ;
      অন্যথা যদি (warn_useless_cast && c_inhibit_evaluation_warnings == 0)
	warning_at (loc, OPT_Wuseless_cast,
		    "useless cast to type %qT", type);

      /* Convert to remove any qualifiers from VALUE's type.  */
      মান = convert (type, মান);
    }
  অন্যথা যদি (বৃক্ষ_CODE (type) == UNION_TYPE)
    {
      বৃক্ষ field;

      জন্য (field = TYPE_FIELDS (type); field; field = DECL_CHAIN (field))
	যদি (বৃক্ষ_TYPE (field) != error_mark_গ্রন্থি
	    && comptypes (TYPE_MAIN_VARIANT (বৃক্ষ_TYPE (field)),
			  TYPE_MAIN_VARIANT (বৃক্ষ_TYPE (মান))))
	  বিরতি;

      যদি (field)
	{
	  বৃক্ষ t;
	  যৌক্তিক maybe_const = সত্য;

	  pedwarn (loc, OPT_Wpedantic, "ISO C forbids casts to union type");
	  t = c_fully_fold (মান, মিথ্যা, &maybe_const);
	  t = build_constructor_single (type, field, t);
	  যদি (!maybe_const)
	    t = c_wrap_maybe_const (t, সত্য);
	  t = digest_init (loc, field, type, t,
			   NULL_বৃক্ষ, মিথ্যা, মিথ্যা, মিথ্যা, সত্য, মিথ্যা, মিথ্যা);
	  বৃক্ষ_CONSTANT (t) = বৃক্ষ_CONSTANT (মান);
	  ফেরত t;
	}
      error_at (loc, "cast to union type from type not present in union");
      ফেরত error_mark_গ্রন্থি;
    }
  অন্যথা
    {
      বৃক্ষ otype, ovalue;

      যদি (type == void_type_গ্রন্থি)
	{
	  বৃক্ষ t = build1 (CONVERT_রাশিমালা, type, মান);
	  SET_রাশিমালা_LOCATION (t, loc);
	  ফেরত t;
	}

      otype = বৃক্ষ_TYPE (মান);

      /* Optionally warn about potentially worrisome casts.  */
      যদি (warn_cast_qual
	  && বৃক্ষ_CODE (type) == POINTER_TYPE
	  && বৃক্ষ_CODE (otype) == POINTER_TYPE)
	handle_warn_cast_qual (loc, type, otype);

      /* Warn about conversions between pointers to disjoint
	 address spaces.  */
      যদি (বৃক্ষ_CODE (type) == POINTER_TYPE
	  && বৃক্ষ_CODE (otype) == POINTER_TYPE
	  && !null_pointer_constant_p (মান))
	{
	  addr_space_t as_to = TYPE_ADDR_SPACE (বৃক্ষ_TYPE (type));
	  addr_space_t as_from = TYPE_ADDR_SPACE (বৃক্ষ_TYPE (otype));
	  addr_space_t as_common;

	  যদি (!addr_space_superset (as_to, as_from, &as_common))
	    {
	      যদি (ADDR_SPACE_GENERIC_P (as_from))
		warning_at (loc, 0, "cast to %qs address space pointer "
			    "from disjoint generic address space pointer",
			    c_addr_space_name (as_to));

	      অন্যথা যদি (ADDR_SPACE_GENERIC_P (as_to))
		warning_at (loc, 0, "cast to generic address space pointer "
			    "from disjoint %qs address space pointer",
			    c_addr_space_name (as_from));

	      অন্যথা
		warning_at (loc, 0, "cast to %qs address space pointer "
			    "from disjoint %qs address space pointer",
			    c_addr_space_name (as_to),
			    c_addr_space_name (as_from));
	    }

	  /* Warn of new allocations that are not big enough for the target
	     type.  */
	  যদি (warn_alloc_আকার && বৃক্ষ_CODE (মান) == CALL_রাশিমালা)
	    যদি (বৃক্ষ fndecl = get_callee_fndecl (মান))
	      যদি (DECL_IS_MALLOC (fndecl))
		{
		  বৃক্ষ attrs = TYPE_ATTRIBUTES (বৃক্ষ_TYPE (fndecl));
		  বৃক্ষ alloc_আকার = lookup_attribute ("alloc_size", attrs);
		  যদি (alloc_আকার)
		    warn_for_alloc_আকার (loc, বৃক্ষ_TYPE (type), মান,
					 alloc_আকার);
		}
	}

      /* Warn about possible alignment problems.  */
      যদি ((STRICT_ALIGNMENT || warn_cast_align == 2)
	  && বৃক্ষ_CODE (type) == POINTER_TYPE
	  && বৃক্ষ_CODE (otype) == POINTER_TYPE
	  && বৃক্ষ_CODE (বৃক্ষ_TYPE (otype)) != VOID_TYPE
	  && বৃক্ষ_CODE (বৃক্ষ_TYPE (otype)) != FUNCTION_TYPE
	  /* Don't warn about opaque types, where the actual alignment
	     restriction is unknown.  */
	  && !(RECORD_OR_UNION_TYPE_P (বৃক্ষ_TYPE (otype))
	       && TYPE_MODE (বৃক্ষ_TYPE (otype)) == VOIDmode)
	  && min_align_of_type (বৃক্ষ_TYPE (type))
	     > min_align_of_type (বৃক্ষ_TYPE (otype)))
	warning_at (loc, OPT_Wcast_align,
		    "cast increases required alignment of target type");

      যদি ((বৃক্ষ_CODE (type) == INTEGER_TYPE
	   || বৃক্ষ_CODE (type) == BITINT_TYPE)
	  && বৃক্ষ_CODE (otype) == POINTER_TYPE
	  && TYPE_PRECISION (type) != TYPE_PRECISION (otype))
      /* Unlike conversion of integers to pointers, where the
         warning is disabled for converting constants because
         of cases such as SIG_*, warn about converting constant
         pointers to integers. In some cases it may cause unwanted
         sign extension, and a warning is appropriate.  */
	warning_at (loc, OPT_Wpointer_to_int_cast,
		    "cast from pointer to integer of different size");

      যদি ((বৃক্ষ_CODE (মান) == CALL_রাশিমালা
	   && !is_access_with_আকার_p (মান))
	  && বৃক্ষ_CODE (type) != বৃক্ষ_CODE (otype))
	warning_at (loc, OPT_Wbad_function_cast,
		    "cast from function call of type %qT "
		    "to non-matching type %qT", otype, type);

      যদি (বৃক্ষ_CODE (type) == POINTER_TYPE
	  && (বৃক্ষ_CODE (otype) == INTEGER_TYPE
	      || বৃক্ষ_CODE (otype) == BITINT_TYPE)
	  && TYPE_PRECISION (type) != TYPE_PRECISION (otype)
	  /* Don't warn about converting any constant.  */
	  && !বৃক্ষ_CONSTANT (মান))
	warning_at (loc,
		    OPT_Wint_to_pointer_cast, "cast to pointer from integer "
		    "of different size");

      যদি (warn_strict_aliasing <= 2)
        strict_aliasing_warning (রাশিমালা_LOCATION (মান), type, রাশিমালা);

      /* If pedantic, warn for conversions between function and object
	 pointer types, except for converting a null pointer constant
	 to function pointer type.  */
      যদি (pedantic
	  && বৃক্ষ_CODE (type) == POINTER_TYPE
	  && বৃক্ষ_CODE (otype) == POINTER_TYPE
	  && বৃক্ষ_CODE (বৃক্ষ_TYPE (otype)) == FUNCTION_TYPE
	  && বৃক্ষ_CODE (বৃক্ষ_TYPE (type)) != FUNCTION_TYPE)
	pedwarn (loc, OPT_Wpedantic, "ISO C forbids "
		 "conversion of function pointer to object pointer type");

      যদি (pedantic
	  && বৃক্ষ_CODE (type) == POINTER_TYPE
	  && বৃক্ষ_CODE (otype) == POINTER_TYPE
	  && বৃক্ষ_CODE (বৃক্ষ_TYPE (type)) == FUNCTION_TYPE
	  && বৃক্ষ_CODE (বৃক্ষ_TYPE (otype)) != FUNCTION_TYPE
	  && !null_pointer_constant_p (মান))
	pedwarn (loc, OPT_Wpedantic, "ISO C forbids "
		 "conversion of object pointer to function pointer type");

      যদি (বৃক্ষ_CODE (type) == POINTER_TYPE
	  && বৃক্ষ_CODE (otype) == POINTER_TYPE
	  && বৃক্ষ_CODE (বৃক্ষ_TYPE (type)) == FUNCTION_TYPE
	  && বৃক্ষ_CODE (বৃক্ষ_TYPE (otype)) == FUNCTION_TYPE
	  && !c_safe_function_type_cast_p (বৃক্ষ_TYPE (type),
					   বৃক্ষ_TYPE (otype)))
	warning_at (loc, OPT_Wcast_function_type,
		    "cast between incompatible function types"
		    " from %qT to %qT", otype, type);

      ovalue = মান;
      /* If converting to boolean a value with integer operands that
	 is not itself represented as an INTEGER_CST, the call below
	 to note_integer_operands may insert a C_MAYBE_CONST_EXPR, but
	 build_binary_op as called by c_common_truthvalue_conversion
	 may also insert a C_MAYBE_CONST_EXPR to indicate that a
	 subexpression has been fully folded.  To avoid nested
	 C_MAYBE_CONST_EXPR, ensure that
	 c_objc_common_truthvalue_conversion receives an argument
	 properly marked as having integer operands in that case.  */
      যদি (int_operands
	  && বৃক্ষ_CODE (মান) != INTEGER_CST
	  && (বৃক্ষ_CODE (type) == BOOLEAN_TYPE
	      || (বৃক্ষ_CODE (type) == ENUMERAL_TYPE
		  && ENUM_UNDERLYING_TYPE (type) != NULL_বৃক্ষ
		  && বৃক্ষ_CODE (ENUM_UNDERLYING_TYPE (type)) == BOOLEAN_TYPE)))
	মান = note_integer_operands (মান);
      মান = convert (type, মান);

      /* Ignore any integer overflow caused by the cast.  */
      যদি (বৃক্ষ_CODE (মান) == INTEGER_CST && !FLOAT_TYPE_P (otype))
	{
	  যদি (বৃক্ষ_OVERFLOW_P (ovalue))
	    {
	      যদি (!বৃক্ষ_OVERFLOW (মান))
		{
		  /* Avoid clobbering a shared constant.  */
		  মান = copy_গ্রন্থি (মান);
		  বৃক্ষ_OVERFLOW (মান) = বৃক্ষ_OVERFLOW (ovalue);
		}
	    }
	  অন্যথা যদি (বৃক্ষ_OVERFLOW (মান))
	    /* Reset VALUE's overflow flags, ensuring constant sharing.  */
	    মান = wide_int_to_বৃক্ষ (বৃক্ষ_TYPE (মান), wi::to_wide (মান));
	}
    }

  /* Don't let a cast be an lvalue.  */
  যদি (lvalue_p (মান)
      /* Also, don't let a cast be a bit-field of a bit-precise integer type,
	 otherwise it could be incorrectly subject of integer promotions.  */
      || (বৃক্ষ_CODE (মান) == COMPONENT_REF
	  && DECL_C_BIT_FIELD (বৃক্ষ_OPERAND (মান, 1))
	  && BITINT_TYPE_P (DECL_BIT_FIELD_TYPE (বৃক্ষ_OPERAND (মান, 1)))))
    মান = non_lvalue_loc (loc, মান);

  /* Don't allow the results of casting to floating-point or complex
     types be confused with actual constants, or casts involving
     integer and pointer types other than direct integer-to-integer
     and integer-to-pointer be confused with integer constant
     expressions and null pointer constants.  */
  যদি (বৃক্ষ_CODE (মান) == REAL_CST
      || বৃক্ষ_CODE (মান) == COMPLEX_CST
      || (বৃক্ষ_CODE (মান) == INTEGER_CST
	  && !((বৃক্ষ_CODE (রাশিমালা) == INTEGER_CST
		&& INTEGRAL_TYPE_P (বৃক্ষ_TYPE (রাশিমালা)))
	       || বৃক্ষ_CODE (রাশিমালা) == REAL_CST
	       || বৃক্ষ_CODE (রাশিমালা) == COMPLEX_CST)))
      মান = build1 (NOP_রাশিমালা, type, মান);

  /* If the expression has integer operands and so can occur in an
     unevaluated part of an integer constant expression, ensure the
     return value reflects this.  */
  যদি (int_operands
      && INTEGRAL_TYPE_P (type)
      && মান != error_mark_গ্রন্থি
      && !রাশিমালা_INT_CONST_OPERANDS (মান))
    মান = note_integer_operands (মান);

  protected_set_রাশিমালা_location (মান, loc);
  ফেরত মান;
}

/* Interpret a cast of expression EXPR to type TYPE.  LOC is the
   location of the open paren of the cast, or the position of the cast
   expr.  */
বৃক্ষ
c_cast_রাশিমালা (location_t loc, কাঠামো c_type_name *type_name, বৃক্ষ রাশিমালা)
{
  বৃক্ষ type;
  বৃক্ষ type_রাশিমালা = NULL_বৃক্ষ;
  যৌক্তিক type_রাশিমালা_const = সত্য;
  বৃক্ষ ret;
  পূর্ণসংখ্যা saved_wsp = warn_strict_prototypes;

  /* This avoids warnings about unprototyped casts on
     integers.  E.g. "#define SIG_DFL (void(*)())0".  */
  যদি (বৃক্ষ_CODE (রাশিমালা) == INTEGER_CST)
    warn_strict_prototypes = 0;
  type = groktypename (type_name, &type_রাশিমালা, &type_রাশিমালা_const);
  warn_strict_prototypes = saved_wsp;

  যদি (বৃক্ষ_CODE (রাশিমালা) == ADDR_রাশিমালা && !VOID_TYPE_P (type)
      && reject_gcc_builtin (রাশিমালা))
    ফেরত error_mark_গ্রন্থি;

  ret = build_c_cast (loc, type, রাশিমালা);
  যদি (ret == error_mark_গ্রন্থি)
    ফেরত error_mark_গ্রন্থি;

  যদি (type_রাশিমালা)
    {
      যৌক্তিক inner_রাশিমালা_const = সত্য;
      ret = c_fully_fold (ret, require_constant_মান, &inner_রাশিমালা_const);
      ret = build2 (C_MAYBE_CONST_রাশিমালা, বৃক্ষ_TYPE (ret), type_রাশিমালা, ret);
      C_MAYBE_CONST_রাশিমালা_NON_CONST (ret) = !(type_রাশিমালা_const
					     && inner_রাশিমালা_const);
      SET_রাশিমালা_LOCATION (ret, loc);
    }

  যদি (!রাশিমালা_HAS_LOCATION (ret))
    protected_set_রাশিমালা_location (ret, loc);

  /* C++ does not permits types to be defined in a cast, but it
     allows references to incomplete types.  */
  যদি (warn_cxx_compat && type_name->specs->typespec_kind == ctsk_tagdef)
    warning_at (loc, OPT_Wc___compat,
		"defining a type in a cast is invalid in C++");

  ফেরত ret;
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

বৃক্ষ
build_modify_রাশিমালা (location_t location, বৃক্ষ lhs, বৃক্ষ lhs_origtype,
		   গণনা বৃক্ষ_code modifycode,
		   location_t rhs_loc, বৃক্ষ rhs, বৃক্ষ rhs_origtype)
{
  বৃক্ষ ফলাফল;
  বৃক্ষ newrhs;
  বৃক্ষ rhseval = NULL_বৃক্ষ;
  বৃক্ষ lhstype = বৃক্ষ_TYPE (lhs);
  বৃক্ষ olhstype = lhstype;
  যৌক্তিক npc;
  যৌক্তিক is_atomic_op;

  /* Types that aren't fully specified cannot be used in assignments.  */
  lhs = require_complete_type (location, lhs);
  rhs = require_complete_type (location, rhs);

  /* Avoid duplicate error messages from operands that had errors.  */
  যদি (বৃক্ষ_CODE (lhs) == ERROR_MARK || বৃক্ষ_CODE (rhs) == ERROR_MARK)
    ফেরত error_mark_গ্রন্থি;

  /* Ensure an error for assigning a non-lvalue array to an array in
     C90.  */
  যদি (বৃক্ষ_CODE (lhstype) == ARRAY_TYPE)
    {
      error_at (location, "assignment to expression with array type");
      ফেরত error_mark_গ্রন্থি;
    }

  /* For ObjC properties, defer this check.  */
  যদি (!objc_is_property_ref (lhs) && !lvalue_or_else (location, lhs, lv_assign))
    ফেরত error_mark_গ্রন্থি;

  is_atomic_op = really_atomic_lvalue (lhs);

  newrhs = rhs;

  যদি (বৃক্ষ_CODE (lhs) == C_MAYBE_CONST_রাশিমালা)
    {
      বৃক্ষ inner = build_modify_রাশিমালা (location, C_MAYBE_CONST_রাশিমালা_রাশিমালা (lhs),
				      lhs_origtype, modifycode, rhs_loc, rhs,
				      rhs_origtype);
      যদি (inner == error_mark_গ্রন্থি)
	ফেরত error_mark_গ্রন্থি;
      ফলাফল = build2 (C_MAYBE_CONST_রাশিমালা, বৃক্ষ_TYPE (inner),
		       C_MAYBE_CONST_রাশিমালা_PRE (lhs), inner);
      gcc_assert (!C_MAYBE_CONST_রাশিমালা_INT_OPERANDS (lhs));
      C_MAYBE_CONST_রাশিমালা_NON_CONST (ফলাফল) = 1;
      protected_set_রাশিমালা_location (ফলাফল, location);
      ফেরত ফলাফল;
    }

  /* If a binary op has been requested, combine the old LHS value with the RHS
     producing the value we should actually store into the LHS.  */

  যদি (modifycode != NOP_রাশিমালা)
    {
      lhs = c_fully_fold (lhs, মিথ্যা, ফাঁকা, সত্য);
      lhs = stabilize_reference (lhs);

      /* Construct the RHS for any non-atomic compound assignment. */
      যদি (!is_atomic_op)
        {
	  /* If in LHS op= RHS the RHS has side-effects, ensure they
	     are preevaluated before the rest of the assignment expression's
	     side-effects, because RHS could contain e.g. function calls
	     that modify LHS.  */
	  যদি (বৃক্ষ_SIDE_EFFECTS (rhs))
	    {
	      যদি (বৃক্ষ_CODE (rhs) == EXCESS_PRECISION_রাশিমালা)
		newrhs = save_রাশিমালা (বৃক্ষ_OPERAND (rhs, 0));
	      অন্যথা
		newrhs = save_রাশিমালা (rhs);
	      rhseval = newrhs;
	      যদি (বৃক্ষ_CODE (rhs) == EXCESS_PRECISION_রাশিমালা)
		newrhs = build1 (EXCESS_PRECISION_রাশিমালা, বৃক্ষ_TYPE (rhs),
				 newrhs);
	    }
	  যৌক্তিক clear_decl_read = মিথ্যা;
	  যদি ((VAR_P (lhs) || বৃক্ষ_CODE (lhs) == PARM_DECL)
	      && !DECL_READ_P (lhs)
	      && (VAR_P (lhs) ? warn_unused_but_set_variable
			      : warn_unused_but_set_parameter) > 2)
	    {
	      mark_exp_read (newrhs);
	      যদি (!DECL_READ_P (lhs))
		clear_decl_read = সত্য;
	    }

	  newrhs = build_দ্বিমিক_op (location, modifycode,
				    convert_lvalue_to_rvalue (location, lhs,
							      সত্য, সত্য),
				    newrhs, সত্য);
	  যদি (clear_decl_read)
	    DECL_READ_P (lhs) = 0;

	  /* The original type of the right hand side is no longer
	     meaningful.  */
	  rhs_origtype = NULL_বৃক্ষ;
	}
    }

  যদি (c_dialect_objc ())
    {
      /* Check if we are modifying an Objective-C property reference;
	 if so, we need to generate setter calls.  */
      যদি (বৃক্ষ_CODE (newrhs) == EXCESS_PRECISION_রাশিমালা)
	ফলাফল = objc_maybe_build_modify_রাশিমালা (lhs, বৃক্ষ_OPERAND (newrhs, 0));
      অন্যথা
	ফলাফল = objc_maybe_build_modify_রাশিমালা (lhs, newrhs);
      যদি (ফলাফল)
	যাও return_ফলাফল;

      /* Else, do the check that we postponed for Objective-C.  */
      যদি (!lvalue_or_else (location, lhs, lv_assign))
	ফেরত error_mark_গ্রন্থি;
    }

  /* Give an error for storing in something that is 'const'.  */

  যদি (TYPE_READONLY (lhstype)
      || (RECORD_OR_UNION_TYPE_P (lhstype)
	  && C_TYPE_FIELDS_READONLY (lhstype)))
    {
      readonly_error (location, lhs, lv_assign);
      ফেরত error_mark_গ্রন্থি;
    }
  অন্যথা যদি (বৃক্ষ_READONLY (lhs))
    readonly_warning (lhs, lv_assign);

  /* If storing into a structure or union member,
     it has probably been given type `int'.
     Compute the type that would go with
     the actual amount of storage the member occupies.  */

  যদি (বৃক্ষ_CODE (lhs) == COMPONENT_REF
      && (বৃক্ষ_CODE (lhstype) == INTEGER_TYPE
	  || বৃক্ষ_CODE (lhstype) == BOOLEAN_TYPE
	  || SCALAR_FLOAT_TYPE_P (lhstype)
	  || বৃক্ষ_CODE (lhstype) == ENUMERAL_TYPE))
    lhstype = বৃক্ষ_TYPE (get_unwidened (lhs, 0));

  /* If storing in a field that is in actuality a short or narrower than one,
     we must store in the field in its actual type.  */

  যদি (lhstype != বৃক্ষ_TYPE (lhs))
    {
      lhs = copy_গ্রন্থি (lhs);
      বৃক্ষ_TYPE (lhs) = lhstype;
    }

  /* Issue -Wc++-compat warnings about an assignment to an enum type
     when LHS does not have its original type.  This happens for,
     e.g., an enum bitfield in a struct.  */
  যদি (warn_cxx_compat
      && lhs_origtype != NULL_বৃক্ষ
      && lhs_origtype != lhstype
      && বৃক্ষ_CODE (lhs_origtype) == ENUMERAL_TYPE)
    {
      বৃক্ষ checktype = (rhs_origtype != NULL_বৃক্ষ
			? rhs_origtype
			: বৃক্ষ_TYPE (rhs));
      যদি (checktype != error_mark_গ্রন্থি
	  && (TYPE_MAIN_VARIANT (checktype) != TYPE_MAIN_VARIANT (lhs_origtype)
	      || (is_atomic_op && modifycode != NOP_রাশিমালা)))
	warning_at (location, OPT_Wc___compat,
		    "enum conversion in assignment is invalid in C++");
    }

  /* Remove qualifiers.  */
  lhstype = c_build_qualified_type (lhstype, TYPE_UNQUALIFIED);
  olhstype = c_build_qualified_type (olhstype, TYPE_UNQUALIFIED);

  /* Convert new value to destination type.  Fold it first, then
     restore any excess precision information, for the sake of
     conversion warnings.  */

  যদি (!(is_atomic_op && modifycode != NOP_রাশিমালা))
    {
      বৃক্ষ rhs_semantic_type = NULL_বৃক্ষ;
      যদি (!c_in_omp_for)
	{
	  যদি (বৃক্ষ_CODE (newrhs) == EXCESS_PRECISION_রাশিমালা)
	    {
	      rhs_semantic_type = বৃক্ষ_TYPE (newrhs);
	      newrhs = বৃক্ষ_OPERAND (newrhs, 0);
	    }
	  npc = null_pointer_constant_p (newrhs);
	  newrhs = c_fully_fold (newrhs, মিথ্যা, ফাঁকা);
	  যদি (rhs_semantic_type)
	    newrhs = build1 (EXCESS_PRECISION_রাশিমালা, rhs_semantic_type, newrhs);
	}
      অন্যথা
	npc = null_pointer_constant_p (newrhs);
      newrhs = convert_for_assignment (location, rhs_loc, lhstype, newrhs,
				       rhs_origtype, ic_assign, npc,
				       NULL_বৃক্ষ, NULL_বৃক্ষ, 0);
      যদি (বৃক্ষ_CODE (newrhs) == ERROR_MARK)
	ফেরত error_mark_গ্রন্থি;
    }

  /* Emit ObjC write barrier, if necessary.  */
  যদি (c_dialect_objc () && flag_objc_gc)
    {
      ফলাফল = objc_generate_write_barrier (lhs, modifycode, newrhs);
      যদি (ফলাফল)
	{
	  protected_set_রাশিমালা_location (ফলাফল, location);
	  যাও return_ফলাফল;
	}
    }

  /* Scan operands.  */

  যদি (is_atomic_op)
    ফলাফল = build_atomic_assign (location, lhs, modifycode, newrhs, মিথ্যা);
  অন্যথা
    {
      ফলাফল = build2 (MODIFY_রাশিমালা, lhstype, lhs, newrhs);
      বৃক্ষ_SIDE_EFFECTS (ফলাফল) = 1;
      protected_set_রাশিমালা_location (ফলাফল, location);
    }

  /* If we got the LHS in a different type for storing in,
     convert the result back to the nominal type of LHS
     so that the value we return always has the same type
     as the LHS argument.  */

  যদি (olhstype == বৃক্ষ_TYPE (ফলাফল))
    যাও return_ফলাফল;

  ফলাফল = convert_for_assignment (location, rhs_loc, olhstype, ফলাফল,
				   rhs_origtype, ic_assign, মিথ্যা, NULL_বৃক্ষ,
				   NULL_বৃক্ষ, 0);
  protected_set_রাশিমালা_location (ফলাফল, location);

return_ফলাফল:
  যদি (rhseval)
    ফলাফল = build2 (COMPOUND_রাশিমালা, বৃক্ষ_TYPE (ফলাফল), rhseval, ফলাফল);
  ফেরত ফলাফল;
}

/* Return whether STRUCT_TYPE has an anonymous field with type TYPE.
   This is used to implement -fplan9-extensions.  */

স্থির যৌক্তিক
find_anonymous_field_with_type (বৃক্ষ struct_type, বৃক্ষ type)
{
  বৃক্ষ field;
  যৌক্তিক found;

  gcc_assert (RECORD_OR_UNION_TYPE_P (struct_type));
  found = মিথ্যা;
  জন্য (field = TYPE_FIELDS (struct_type);
       field != NULL_বৃক্ষ;
       field = বৃক্ষ_CHAIN (field))
    {
      বৃক্ষ fieldtype = remove_qualifiers (বৃক্ষ_TYPE (field));
      যদি (DECL_NAME (field) == ফাঁকা
	  && comptypes (type, fieldtype))
	{
	  যদি (found)
	    ফেরত মিথ্যা;
	  found = সত্য;
	}
      অন্যথা যদি (DECL_NAME (field) == ফাঁকা
	       && RECORD_OR_UNION_TYPE_P (বৃক্ষ_TYPE (field))
	       && find_anonymous_field_with_type (বৃক্ষ_TYPE (field), type))
	{
	  যদি (found)
	    ফেরত মিথ্যা;
	  found = সত্য;
	}
    }
  ফেরত found;
}

/* RHS is an expression whose type is pointer to struct.  If there is
   an anonymous field in RHS with type TYPE, then return a pointer to
   that field in RHS.  This is used with -fplan9-extensions.  This
   returns NULL if no conversion could be found.  */

স্থির বৃক্ষ
convert_to_anonymous_field (location_t location, বৃক্ষ type, বৃক্ষ rhs)
{
  বৃক্ষ rhs_struct_type, lhs_main_type;
  বৃক্ষ field, found_field;
  যৌক্তিক found_sub_field;
  বৃক্ষ ret;

  gcc_assert (POINTER_TYPE_P (বৃক্ষ_TYPE (rhs)));
  rhs_struct_type = বৃক্ষ_TYPE (বৃক্ষ_TYPE (rhs));
  gcc_assert (RECORD_OR_UNION_TYPE_P (rhs_struct_type));

  gcc_assert (POINTER_TYPE_P (type));
  lhs_main_type = remove_qualifiers (বৃক্ষ_TYPE (type));

  found_field = NULL_বৃক্ষ;
  found_sub_field = মিথ্যা;
  জন্য (field = TYPE_FIELDS (rhs_struct_type);
       field != NULL_বৃক্ষ;
       field = বৃক্ষ_CHAIN (field))
    {
      যদি (DECL_NAME (field) != NULL_বৃক্ষ
	  || !RECORD_OR_UNION_TYPE_P (বৃক্ষ_TYPE (field)))
	চালু;
      বৃক্ষ fieldtype = remove_qualifiers (বৃক্ষ_TYPE (field));
      যদি (comptypes (lhs_main_type, fieldtype))
	{
	  যদি (found_field != NULL_বৃক্ষ)
	    ফেরত NULL_বৃক্ষ;
	  found_field = field;
	}
      অন্যথা যদি (find_anonymous_field_with_type (বৃক্ষ_TYPE (field),
					       lhs_main_type))
	{
	  যদি (found_field != NULL_বৃক্ষ)
	    ফেরত NULL_বৃক্ষ;
	  found_field = field;
	  found_sub_field = সত্য;
	}
    }

  যদি (found_field == NULL_বৃক্ষ)
    ফেরত NULL_বৃক্ষ;

  ret = fold_build3_loc (location, COMPONENT_REF, বৃক্ষ_TYPE (found_field),
			 build_fold_indirect_ref (rhs), found_field,
			 NULL_বৃক্ষ);
  ret = build_fold_addr_রাশিমালা_loc (location, ret);

  যদি (found_sub_field)
    {
      ret = convert_to_anonymous_field (location, type, ret);
      gcc_assert (ret != NULL_বৃক্ষ);
    }

  ফেরত ret;
}

/* Issue an error message for a bad initializer component.
   GMSGID identifies the message.
   The component name is taken from the spelling stack.  */

স্থির শূন্য ATTRIBUTE_GCC_DIAG (2,0)
error_init (location_t loc, ধ্রুবক অক্ষর *gmsgid, ...)
{
  অক্ষর *ofwhat;

  auto_diagnostic_group d;

  /* The gmsgid may be a format string with %< and %>. */
  va_list ap;
  va_start (ap, gmsgid);
  যৌক্তিক warned = emit_diagnostic_valist (diagnostics::kind::error,
					loc, -1, gmsgid, &ap);
  va_end (ap);

  ofwhat = print_spelling ((অক্ষর *) alloca (spelling_দৈর্ঘ্য () + 1));
  যদি (*ofwhat && warned)
    inform (loc, "(near initialization for %qs)", ofwhat);
}

/* Used to implement pedwarn_init and permerror_init.  */

স্থির যৌক্তিক ATTRIBUTE_GCC_DIAG (3,0)
pedwarn_permerror_init (location_t loc, পূর্ণসংখ্যা opt, ধ্রুবক অক্ষর *gmsgid,
			va_list *ap, গণনা diagnostics::kind kind)
{
  /* Use the location where a macro was expanded rather than where
     it was defined to make sure macros defined in system headers
     but used incorrectly elsewhere are diagnosed.  */
  location_t exploc = expansion_point_location_if_in_system_header (loc);
  auto_diagnostic_group d;
  যৌক্তিক warned = emit_diagnostic_valist (kind, exploc, opt, gmsgid, ap);
  যদি (warned)
    {
      অক্ষর *ofwhat = print_spelling ((অক্ষর *) alloca (spelling_দৈর্ঘ্য () + 1));
      যদি (*ofwhat)
	inform (exploc, "(near initialization for %qs)", ofwhat);
    }
  ফেরত warned;
}

/* Issue a pedantic warning for a bad initializer component.  OPT is
   the option OPT_* (from options.h) controlling this warning or 0 if
   it is unconditionally given.  GMSGID identifies the message.  The
   component name is taken from the spelling stack.  */

স্থির যৌক্তিক ATTRIBUTE_GCC_DIAG (3,0)
pedwarn_init (location_t loc, পূর্ণসংখ্যা opt, ধ্রুবক অক্ষর *gmsgid, ...)
{
  va_list ap;
  va_start (ap, gmsgid);
  যৌক্তিক warned = pedwarn_permerror_init (loc, opt, gmsgid, &ap,
					diagnostics::kind::pedwarn);
  va_end (ap);
  ফেরত warned;
}

/* Like pedwarn_init, but issue a permerror.  */

স্থির যৌক্তিক ATTRIBUTE_GCC_DIAG (3,0)
permerror_init (location_t loc, পূর্ণসংখ্যা opt, ধ্রুবক অক্ষর *gmsgid, ...)
{
  va_list ap;
  va_start (ap, gmsgid);
  যৌক্তিক warned = pedwarn_permerror_init (loc, opt, gmsgid, &ap,
					diagnostics::kind::permerror);
  va_end (ap);
  ফেরত warned;
}

/* Issue a warning for a bad initializer component.

   OPT is the OPT_W* value corresponding to the warning option that
   controls this warning.  GMSGID identifies the message.  The
   component name is taken from the spelling stack.  */

স্থির শূন্য
warning_init (location_t loc, পূর্ণসংখ্যা opt, ধ্রুবক অক্ষর *gmsgid)
{
  অক্ষর *ofwhat;
  যৌক্তিক warned;

  auto_diagnostic_group d;

  /* Use the location where a macro was expanded rather than where
     it was defined to make sure macros defined in system headers
     but used incorrectly elsewhere are diagnosed.  */
  location_t exploc = expansion_point_location_if_in_system_header (loc);

  /* The gmsgid may be a format string with %< and %>. */
  warned = warning_at (exploc, opt, gmsgid);
  যদি (warned)
    {
      ofwhat = print_spelling ((অক্ষর *) alloca (spelling_দৈর্ঘ্য () + 1));
      যদি (*ofwhat)
	inform (exploc, "(near initialization for %qs)", ofwhat);
    }
}

/* If TYPE is an array type and EXPR is a parenthesized string
   constant, warn if pedantic that EXPR is being used to initialize an
   object of type TYPE.  */

শূন্য
maybe_warn_string_init (location_t loc, বৃক্ষ type, কাঠামো c_রাশিমালা রাশিমালা)
{
  যদি (pedantic
      && বৃক্ষ_CODE (type) == ARRAY_TYPE
      && বৃক্ষ_CODE (রাশিমালা.মান) == STRING_CST
      && রাশিমালা.original_code != STRING_CST)
    pedwarn_init (loc, OPT_Wpedantic,
		  "array initialized from parenthesized string constant");
}

/* Attempt to locate the parameter with the given index within FNDECL,
   returning DECL_SOURCE_LOCATION (FNDECL) if it can't be found.  */

স্থির location_t
get_fndecl_argument_location (বৃক্ষ fndecl, পূর্ণসংখ্যা argnum)
{
  পূর্ণসংখ্যা i;
  বৃক্ষ param;

  /* Locate param by index within DECL_ARGUMENTS (fndecl).  */
  জন্য (i = 0, param = DECL_ARGUMENTS (fndecl);
       i < argnum && param;
       i++, param = বৃক্ষ_CHAIN (param))
    ;

  /* If something went wrong (e.g. if we have a builtin and thus no arguments),
     return DECL_SOURCE_LOCATION (FNDECL).  */
  যদি (param == ফাঁকা)
    ফেরত DECL_SOURCE_LOCATION (fndecl);

  ফেরত DECL_SOURCE_LOCATION (param);
}

/* Issue a note about a mismatching argument for parameter PARMNUM
   to FUNDECL, for types EXPECTED_TYPE and ACTUAL_TYPE.
   Attempt to issue the note at the pertinent parameter of the decl;
   failing that issue it at the location of FUNDECL; failing that
   issue it at PLOC.
   Use highlight_colors::actual for the ACTUAL_TYPE
   and highlight_colors::expected for EXPECTED_TYPE and the
   parameter of FUNDECL*/

স্থির শূন্য
inform_for_arg (বৃক্ষ fundecl, location_t ploc, পূর্ণসংখ্যা parmnum,
		বৃক্ষ expected_type, বৃক্ষ actual_type)
{
  location_t loc;
  যদি (fundecl && !DECL_IS_UNDECLARED_BUILTIN (fundecl))
    loc = get_fndecl_argument_location (fundecl, parmnum - 1);
  অন্যথা
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

স্থির শূন্য
maybe_warn_builtin_no_proto_arg (location_t loc, বৃক্ষ fundecl, পূর্ণসংখ্যা parmnum,
				 বৃক্ষ parmtype, বৃক্ষ argtype)
{
  বৃক্ষ_code parmcode = বৃক্ষ_CODE (parmtype);
  বৃক্ষ_code argcode = বৃক্ষ_CODE (argtype);
  বৃক্ষ promoted = c_type_promotes_to (argtype);

  /* Avoid warning for enum arguments that promote to an integer type
     of the same size/mode.  */
  যদি (parmcode == INTEGER_TYPE
      && argcode == ENUMERAL_TYPE
      && TYPE_MODE (parmtype) == TYPE_MODE (argtype))
    ফেরত;

  যদি ((parmcode == argcode
       || (parmcode == INTEGER_TYPE
	   && argcode == ENUMERAL_TYPE))
      && TYPE_MAIN_VARIANT (parmtype) == TYPE_MAIN_VARIANT (promoted))
    ফেরত;

  /* This diagnoses even signed/unsigned mismatches.  Those might be
     safe in many cases but GCC may emit suboptimal code for them so
     warning on those cases drives efficiency improvements.  */
  যদি (warning_at (loc, OPT_Wbuiltin_declaration_mismatch,
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

শ্রেণী pp_element_quoted_decl : সর্বজনীন pp_element
{
সর্বজনীন:
  pp_element_quoted_decl (বৃক্ষ decl, ধ্রুবক অক্ষর *highlight_color)
  : m_decl (decl),
    m_highlight_color (highlight_color)
  {
  }

  শূন্য add_to_phase_2 (pp_markup::context &ctxt) override
  {
    ctxt.begin_quote ();
    ctxt.begin_highlight_color (m_highlight_color);

    print_decl (ctxt);

    ctxt.end_highlight_color ();
    ctxt.end_quote ();
  }

  শূন্য print_decl (pp_markup::context &ctxt)
  {
    pretty_printer *ধ্রুবক pp = &ctxt.m_pp;
    pp->set_padding (pp_none);
    যদি (DECL_NAME (m_decl))
      pp_identifier (pp, lang_hooks.decl_printable_name (m_decl, 2));
    অন্যথা
      pp_string (pp, _("({anonymous})"));
  }

ব্যক্তিগত:
  বৃক্ষ m_decl;
  ধ্রুবক অক্ষর *m_highlight_color;
};

/* If TYPE is from a typedef, issue a note showing the location
   to the user.
   Use HIGHLIGHT_COLOR as the highlight color.  */

স্থির শূন্য
maybe_inform_typedef_location (বৃক্ষ type, ধ্রুবক অক্ষর *highlight_color)
{
  যদি (!typedef_variant_p (type))
    ফেরত;

  বৃক্ষ typedef_decl = TYPE_NAME (type);
  gcc_assert (বৃক্ষ_CODE (typedef_decl) == TYPE_DECL);
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

স্থির বৃক্ষ
convert_for_assignment (location_t location, location_t রাশিমালা_loc, বৃক্ষ type,
			বৃক্ষ rhs, বৃক্ষ origtype, গণনা impl_conv errtype,
			যৌক্তিক null_pointer_constant, বৃক্ষ fundecl,
			বৃক্ষ function, পূর্ণসংখ্যা parmnum, পূর্ণসংখ্যা warnopt /* = 0 */)
{
  গণনা বৃক্ষ_code codel = বৃক্ষ_CODE (type);
  বৃক্ষ orig_rhs = rhs;
  বৃক্ষ rhstype;
  গণনা বৃক্ষ_code coder;
  বৃক্ষ rname = NULL_বৃক্ষ;
  যৌক্তিক objc_ok = মিথ্যা;

  /* Use the expansion point location to handle cases such as user's
     function returning a wrong-type macro defined in a system header.  */
  location = expansion_point_location_if_in_system_header (location);

  যদি (errtype == ic_argpass)
    {
      বৃক্ষ selector;
      /* Change pointer to function to the function itself for
	 diagnostics.  */
      যদি (বৃক্ষ_CODE (function) == ADDR_রাশিমালা
	  && বৃক্ষ_CODE (বৃক্ষ_OPERAND (function, 0)) == FUNCTION_DECL)
	function = বৃক্ষ_OPERAND (function, 0);

      /* Handle an ObjC selector specially for diagnostics.  */
      selector = objc_message_selector ();
      rname = function;
      যদি (selector && parmnum > 2)
	{
	  rname = selector;
	  parmnum -= 2;
	}
    }

  /* This macro is used to emit diagnostics to ensure that all format
     strings are complete sentences, visible to gettext and checked at
     compile time.  */
#define PEDWARN_FOR_ASSIGNMENT(LOCATION, PLOC, OPT, AR, AS, IN, RE)	 \
  করো {                                                                   \
    নির্বাচন (errtype)                                                     \
      {                                                                  \
      ক্ষেত্র ic_argpass:                                                   \
	{								\
	  auto_diagnostic_group d;						\
	  যদি (pedwarn (PLOC, OPT, AR, parmnum, rname))		\
	    inform_for_arg (fundecl, (PLOC), parmnum, type, rhstype); \
	}								\
        বিরতি;                                                           \
      ক্ষেত্র ic_assign:                                                    \
        pedwarn (LOCATION, OPT, AS);                                     \
        বিরতি;                                                           \
      ক্ষেত্র ic_init:                                                      \
      ক্ষেত্র ic_init_const:                                                \
        pedwarn_init (LOCATION, OPT, IN);                                \
        বিরতি;                                                           \
      ক্ষেত্র ic_return:                                                    \
        pedwarn (LOCATION, OPT, RE);					 \
        বিরতি;                                                           \
      পূর্বনির্ধারিত:                                                           \
        gcc_unreachable ();                                              \
      }                                                                  \
  } যখন (0)

  /* This macro is used to emit diagnostics to ensure that all format
     strings are complete sentences, visible to gettext and checked at
     compile time.  It can be called with 'pedwarn' or 'warning_at'.  */
#define WARNING_FOR_QUALIFIERS(PEDWARN, LOCATION, PLOC, OPT, AR, AS, IN, RE, QUALS) \
  করো {                                                                   \
    নির্বাচন (errtype)                                                     \
      {                                                                  \
      ক্ষেত্র ic_argpass:                                                   \
	{								 \
	  auto_diagnostic_group d;					 \
	  যদি (PEDWARN) {						 \
	    যদি (pedwarn (PLOC, OPT, AR, parmnum, rname, QUALS))          \
	      inform_for_arg (fundecl, (PLOC), parmnum, type, rhstype);  \
	  } অন্যথা {							 \
	    যদি (warning_at (PLOC, OPT, AR, parmnum, rname, QUALS))	 \
	      inform_for_arg (fundecl, (PLOC), parmnum, type, rhstype);  \
	  }								 \
	}								 \
        বিরতি;                                                           \
      ক্ষেত্র ic_assign:                                                    \
	যদি (PEDWARN)							 \
	  pedwarn (LOCATION, OPT, AS, QUALS);                            \
	অন্যথা								 \
	  warning_at (LOCATION, OPT, AS, QUALS);                         \
        বিরতি;                                                           \
      ক্ষেত্র ic_init:                                                      \
      ক্ষেত্র ic_init_const:                                                \
	যদি (PEDWARN)							 \
	  pedwarn (LOCATION, OPT, IN, QUALS);                            \
	অন্যথা								 \
	  warning_at (LOCATION, OPT, IN, QUALS);                         \
        বিরতি;                                                           \
      ক্ষেত্র ic_return:                                                    \
	যদি (PEDWARN)							 \
	  pedwarn (LOCATION, OPT, RE, QUALS);                            \
	অন্যথা								 \
	  warning_at (LOCATION, OPT, RE, QUALS);                         \
        বিরতি;                                                           \
      পূর্বনির্ধারিত:                                                           \
        gcc_unreachable ();                                              \
      }                                                                  \
  } যখন (0)

  /* This macro is used to emit diagnostics to ensure that all format
     strings are complete sentences, visible to gettext and checked at
     compile time.  It is the same as PEDWARN_FOR_ASSIGNMENT but with an
     extra parameter to enumerate qualifiers.  */
#define PEDWARN_FOR_QUALIFIERS(LOCATION, PLOC, OPT, AR, AS, IN, RE, QUALS) \
   WARNING_FOR_QUALIFIERS (সত্য, LOCATION, PLOC, OPT, AR, AS, IN, RE, QUALS)


  যদি (বৃক্ষ_CODE (rhs) == EXCESS_PRECISION_রাশিমালা)
    rhs = বৃক্ষ_OPERAND (rhs, 0);

  rhstype = বৃক্ষ_TYPE (rhs);
  coder = বৃক্ষ_CODE (rhstype);

  যদি (coder == ERROR_MARK)
    ফেরত error_mark_গ্রন্থি;

  যদি (c_dialect_objc ())
    {
      পূর্ণসংখ্যা parmno;

      নির্বাচন (errtype)
	{
	ক্ষেত্র ic_return:
	  parmno = 0;
	  বিরতি;

	ক্ষেত্র ic_assign:
	  parmno = -1;
	  বিরতি;

	ক্ষেত্র ic_init:
	ক্ষেত্র ic_init_const:
	  parmno = -2;
	  বিরতি;

	পূর্বনির্ধারিত:
	  parmno = parmnum;
	  বিরতি;
	}

      objc_ok = objc_compare_types (type, rhstype, parmno, rname);
    }

  যদি (warn_cxx_compat)
    {
      বৃক্ষ checktype = origtype != NULL_বৃক্ষ ? origtype : rhstype;
      যদি (checktype != error_mark_গ্রন্থি
	  && বৃক্ষ_CODE (type) == ENUMERAL_TYPE
	  && TYPE_MAIN_VARIANT (checktype) != TYPE_MAIN_VARIANT (type))
	নির্বাচন (errtype)
	  {
	  ক্ষেত্র ic_argpass:
	    যদি (pedwarn (রাশিমালা_loc, OPT_Wc___compat, "enum conversion when "
			 "passing argument %d of %qE is invalid in C++",
			 parmnum, rname))
	      inform ((fundecl && !DECL_IS_UNDECLARED_BUILTIN (fundecl))
		      ? DECL_SOURCE_LOCATION (fundecl) : রাশিমালা_loc,
		      "expected %qT but argument is of type %qT",
		      type, rhstype);
	    বিরতি;
	  ক্ষেত্র ic_assign:
	    pedwarn (location, OPT_Wc___compat, "enum conversion from %qT to "
		     "%qT in assignment is invalid in C++", rhstype, type);
	    বিরতি;
	  ক্ষেত্র ic_init:
	  ক্ষেত্র ic_init_const:
	    pedwarn_init (location, OPT_Wc___compat, "enum conversion from "
			  "%qT to %qT in initialization is invalid in C++",
			  rhstype, type);
	    বিরতি;
	  ক্ষেত্র ic_return:
	    pedwarn (location, OPT_Wc___compat, "enum conversion from %qT to "
		     "%qT in return is invalid in C++", rhstype, type);
	    বিরতি;
	  পূর্বনির্ধারিত:
	    gcc_unreachable ();
	  }
    }

  যদি (warn_enum_conversion)
    {
      বৃক্ষ checktype = origtype != NULL_বৃক্ষ ? origtype : rhstype;
      যদি (checktype != error_mark_গ্রন্থি
	  && বৃক্ষ_CODE (checktype) == ENUMERAL_TYPE
	  && বৃক্ষ_CODE (type) == ENUMERAL_TYPE
	  && !comptypes (TYPE_MAIN_VARIANT (checktype), TYPE_MAIN_VARIANT (type)))
       {
	  gcc_rich_location loc (location);
	  warning_at (&loc, OPT_Wenum_conversion,
		      "implicit conversion from %qT to %qT",
		      checktype, type);
       }
    }

  যদি (TYPE_MAIN_VARIANT (type) == TYPE_MAIN_VARIANT (rhstype))
    {
      warn_for_address_of_packed_member (type, orig_rhs);
      যদি (type != rhstype)
	/* Convert RHS to TYPE in order to not lose TYPE in diagnostics.  */
	rhs = convert (type, rhs);
      ফেরত rhs;
    }

  যদি (coder == VOID_TYPE)
    {
      /* Except for passing an argument to an unprototyped function,
	 this is a constraint violation.  When passing an argument to
	 an unprototyped function, it is compile-time undefined;
	 making it a constraint in that case was rejected in
	 DR#252.  */
      ধ্রুবক অক্ষর বার্তা[] = "void value not ignored as it ought to be";
      যদি (warnopt)
	warning_at (location, warnopt, বার্তা);
      অন্যথা
	error_at (location, বার্তা);
      ফেরত error_mark_গ্রন্থি;
    }
  rhs = require_complete_type (location, rhs);
  যদি (rhs == error_mark_গ্রন্থি)
    ফেরত error_mark_গ্রন্থি;

  যদি (coder == POINTER_TYPE && reject_gcc_builtin (rhs))
    ফেরত error_mark_গ্রন্থি;

  /* A non-reference type can convert to a reference.  This handles
     va_start, va_copy and possibly port built-ins.  */
  যদি (codel == REFERENCE_TYPE && coder != REFERENCE_TYPE)
    {
      যদি (!lvalue_p (rhs))
	{
	  ধ্রুবক অক্ষর বার্তা[] = "cannot pass rvalue to reference parameter";
	  যদি (warnopt)
	    warning_at (location, warnopt, বার্তা);
	  অন্যথা
	    error_at (location, বার্তা);
	  ফেরত error_mark_গ্রন্থি;
	}
      যদি (!c_mark_addressable (rhs))
	ফেরত error_mark_গ্রন্থি;
      rhs = build1 (ADDR_রাশিমালা, c_build_pointer_type (বৃক্ষ_TYPE (rhs)), rhs);
      SET_রাশিমালা_LOCATION (rhs, location);

      rhs = convert_for_assignment (location, রাশিমালা_loc,
				    c_build_pointer_type (বৃক্ষ_TYPE (type)),
				    rhs, origtype, errtype,
				    null_pointer_constant, fundecl, function,
				    parmnum, warnopt);
      যদি (rhs == error_mark_গ্রন্থি)
	ফেরত error_mark_গ্রন্থি;

      rhs = build1 (NOP_রাশিমালা, type, rhs);
      SET_রাশিমালা_LOCATION (rhs, location);
      ফেরত rhs;
    }
  /* Some types can interconvert without explicit casts.  */
  অন্যথা যদি (codel == VECTOR_TYPE && coder == VECTOR_TYPE
	   && vector_types_convertible_p (type, বৃক্ষ_TYPE (rhs), সত্য))
    ফেরত convert (type, rhs);
  /* Arithmetic types all interconvert, and enum is treated like int.  */
  অন্যথা যদি ((codel == INTEGER_TYPE || codel == REAL_TYPE
	    || codel == FIXED_POINT_TYPE
	    || codel == ENUMERAL_TYPE || codel == COMPLEX_TYPE
	    || codel == BOOLEAN_TYPE || codel == BITINT_TYPE)
	   && (coder == INTEGER_TYPE || coder == REAL_TYPE
	       || coder == FIXED_POINT_TYPE
	       || coder == ENUMERAL_TYPE || coder == COMPLEX_TYPE
	       || coder == BOOLEAN_TYPE || coder == BITINT_TYPE))
    {
      যদি (warnopt && errtype == ic_argpass)
	maybe_warn_builtin_no_proto_arg (রাশিমালা_loc, fundecl, parmnum, type,
					 rhstype);

      যৌক্তিক save = in_late_দ্বিমিক_op;
      যদি (C_BOOLEAN_TYPE_P (type) || codel == COMPLEX_TYPE
	  || (coder == REAL_TYPE
	      && (codel == INTEGER_TYPE || codel == ENUMERAL_TYPE)
	      && sanitize_flags_p (SANITIZE_FLOAT_CAST)))
	in_late_দ্বিমিক_op = সত্য;
      বৃক্ষ ret = convert_and_check (রাশিমালা_loc != UNKNOWN_LOCATION
				    ? রাশিমালা_loc : location, type, orig_rhs,
				    errtype == ic_init_const);
      in_late_দ্বিমিক_op = save;
      ফেরত ret;
    }

  /* Aggregates in different TUs might need conversion.  */
  যদি ((codel == RECORD_TYPE || codel == UNION_TYPE)
      && codel == coder
      && comptypes (TYPE_MAIN_VARIANT (type), TYPE_MAIN_VARIANT (rhstype)))
    ফেরত convert_and_check (রাশিমালা_loc != UNKNOWN_LOCATION
			      ? রাশিমালা_loc : location, type, rhs);

  /* Conversion to a transparent union or record from its member types.
     This applies only to function arguments.  */
  যদি (((codel == UNION_TYPE || codel == RECORD_TYPE)
      && TYPE_TRANSPARENT_AGGR (type))
      && errtype == ic_argpass)
    {
      বৃক্ষ memb, marginal_memb = NULL_বৃক্ষ;

      জন্য (memb = TYPE_FIELDS (type); memb ; memb = DECL_CHAIN (memb))
	{
	  বৃক্ষ memb_type = বৃক্ষ_TYPE (memb);

	  যদি (comptypes (TYPE_MAIN_VARIANT (memb_type),
			 TYPE_MAIN_VARIANT (rhstype)))
	    বিরতি;

	  যদি (বৃক্ষ_CODE (memb_type) != POINTER_TYPE)
	    চালু;

	  যদি (coder == POINTER_TYPE)
	    {
	      বৃক্ষ ttl = বৃক্ষ_TYPE (memb_type);
	      বৃক্ষ ttr = বৃক্ষ_TYPE (rhstype);

	      /* Any non-function converts to a [const][volatile] void *
		 and vice versa; otherwise, targets must be the same.
		 Meanwhile, the lhs target must have all the qualifiers of
		 the rhs.  */
	      যদি ((VOID_TYPE_P (ttl) && !TYPE_ATOMIC (ttl))
		  || (VOID_TYPE_P (ttr) && !TYPE_ATOMIC (ttr))
		  || comp_target_types (location, memb_type, rhstype))
		{
		  পূর্ণসংখ্যা lquals = TYPE_QUALS (ttl) & ~TYPE_QUAL_ATOMIC;
		  পূর্ণসংখ্যা rquals = TYPE_QUALS (ttr) & ~TYPE_QUAL_ATOMIC;
		  /* If this type won't generate any warnings, use it.  */
		  যদি (lquals == rquals
		      || ((বৃক্ষ_CODE (ttr) == FUNCTION_TYPE
			   && বৃক্ষ_CODE (ttl) == FUNCTION_TYPE)
			  ? ((lquals | rquals) == rquals)
			  : ((lquals | rquals) == lquals)))
		    বিরতি;

		  /* Keep looking for a better type, but remember this one.  */
		  যদি (!marginal_memb)
		    marginal_memb = memb;
		}
	    }

	  /* Can convert integer zero to any pointer type.  */
	  যদি (null_pointer_constant)
	    {
	      rhs = null_pointer_গ্রন্থি;
	      বিরতি;
	    }
	}

      যদি (memb || marginal_memb)
	{
	  যদি (!memb)
	    {
	      /* We have only a marginally acceptable member type;
		 it needs a warning.  */
	      বৃক্ষ ttl = বৃক্ষ_TYPE (বৃক্ষ_TYPE (marginal_memb));
	      বৃক্ষ ttr = বৃক্ষ_TYPE (rhstype);

	      /* Const and volatile mean something different for function
		 types, so the usual warnings are not appropriate.  */
	      যদি (বৃক্ষ_CODE (ttr) == FUNCTION_TYPE
		  && বৃক্ষ_CODE (ttl) == FUNCTION_TYPE)
		{
		  /* Because const and volatile on functions are
		     restrictions that say the function will not do
		     certain things, it is okay to use a const or volatile
		     function where an ordinary one is wanted, but not
		     vice-versa.  */
		  যদি (TYPE_QUALS_NO_ADDR_SPACE (ttl)
		      & ~TYPE_QUALS_NO_ADDR_SPACE (ttr))
		    PEDWARN_FOR_QUALIFIERS (location, রাশিমালা_loc,
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
	      অন্যথা যদি (TYPE_QUALS_NO_ADDR_SPACE (ttr)
		       & ~TYPE_QUALS_NO_ADDR_SPACE (ttl))
		PEDWARN_FOR_QUALIFIERS (location, রাশিমালা_loc,
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

	  যদি (!fundecl || !DECL_IN_SYSTEM_HEADER (fundecl))
	    pedwarn (location, OPT_Wpedantic,
		     "ISO C prohibits argument conversion to union type");

	  rhs = fold_convert_loc (location, বৃক্ষ_TYPE (memb), rhs);
	  ফেরত build_constructor_single (type, memb, rhs);
	}
    }

  /* Conversions among pointers */
  অন্যথা যদি ((codel == POINTER_TYPE || codel == REFERENCE_TYPE)
	   && (coder == codel))
    {
      /* If RHS refers to a built-in declared without a prototype
	 BLTIN is the declaration of the built-in with a prototype
	 and RHSTYPE is set to the actual type of the built-in.  */
      বৃক্ষ bltin;
      rhstype = type_or_builtin_type (rhs, &bltin);

      বৃক্ষ ttl = বৃক্ষ_TYPE (type);
      বৃক্ষ ttr = বৃক্ষ_TYPE (rhstype);
      যৌক্তিক is_opaque_pointer;
      যৌক্তিক target_cmp = মিথ্যা;   /* Cache comp_target_types () result.  */
      addr_space_t asl;
      addr_space_t asr;

      বৃক্ষ mvl = remove_qualifiers (ttl);
      বৃক্ষ mvr = remove_qualifiers (ttr);

      /* Opaque pointers are treated like void pointers.  */
      is_opaque_pointer = vector_targets_convertible_p (ttl, ttr);

      /* The Plan 9 compiler permits a pointer to a struct to be
	 automatically converted into a pointer to an anonymous field
	 within the struct.  */
      যদি (flag_plan9_extensions
	  && RECORD_OR_UNION_TYPE_P (mvl)
	  && RECORD_OR_UNION_TYPE_P (mvr)
	  && mvl != mvr)
	{
	  বৃক্ষ new_rhs = convert_to_anonymous_field (location, type, rhs);
	  যদি (new_rhs != NULL_বৃক্ষ)
	    {
	      rhs = new_rhs;
	      rhstype = বৃক্ষ_TYPE (rhs);
	      coder = বৃক্ষ_CODE (rhstype);
	      ttr = বৃক্ষ_TYPE (rhstype);
	      mvr = TYPE_MAIN_VARIANT (ttr);
	    }
	}

      /* C++ does not allow the implicit conversion void* -> T*.  However,
	 for the purpose of reducing the number of false positives, we
	 tolerate the special case of

		int *p = NULL;

	 where NULL is typically defined in C to be '(void *) 0'.  */
      যদি (VOID_TYPE_P (ttr) && rhs != null_pointer_গ্রন্থি && !VOID_TYPE_P (ttl))
	warning_at (errtype == ic_argpass ? রাশিমালা_loc : location,
		    OPT_Wc___compat,
		    "request for implicit conversion "
		    "from %qT to %qT not permitted in C++", rhstype, type);

      /* Warn of new allocations that are not big enough for the target
	 type.  */
      যদি (warn_alloc_আকার && বৃক্ষ_CODE (rhs) == CALL_রাশিমালা)
	যদি (বৃক্ষ fndecl = get_callee_fndecl (rhs))
	  যদি (DECL_IS_MALLOC (fndecl))
	    {
	      বৃক্ষ attrs = TYPE_ATTRIBUTES (বৃক্ষ_TYPE (fndecl));
	      বৃক্ষ alloc_আকার = lookup_attribute ("alloc_size", attrs);
	      যদি (alloc_আকার)
		warn_for_alloc_আকার (location, ttl, rhs, alloc_আকার);
	    }

      /* See if the pointers point to incompatible address spaces.  */
      asl = TYPE_ADDR_SPACE (ttl);
      asr = TYPE_ADDR_SPACE (ttr);
      যদি (!null_pointer_constant_p (rhs)
	  && asr != asl && !targetm.addr_space.subset_p (asr, asl))
	{
	  auto_diagnostic_group d;
	  যৌক্তিক diagnosed = সত্য;
	  নির্বাচন (errtype)
	    {
	    ক্ষেত্র ic_argpass:
	      {
		ধ্রুবক অক্ষর বার্তা[] = G_("passing argument %d of %qE from "
				      "pointer to non-enclosed address space");
		যদি (warnopt)
		  diagnosed
		    = warning_at (রাশিমালা_loc, warnopt, বার্তা, parmnum, rname);
		অন্যথা
		  error_at (রাশিমালা_loc, বার্তা, parmnum, rname);
	      বিরতি;
	      }
	    ক্ষেত্র ic_assign:
	      {
		ধ্রুবক অক্ষর বার্তা[] = G_("assignment from pointer to "
				      "non-enclosed address space");
		যদি (warnopt)
		  diagnosed = warning_at (location, warnopt, বার্তা);
		অন্যথা
		  error_at (location, বার্তা);
		বিরতি;
	      }
	    ক্ষেত্র ic_init:
	    ক্ষেত্র ic_init_const:
	      {
		ধ্রুবক অক্ষর বার্তা[] = G_("initialization from pointer to "
				      "non-enclosed address space");
		যদি (warnopt)
		  diagnosed = warning_at (location, warnopt, বার্তা);
		অন্যথা
		  error_at (location, বার্তা);
		বিরতি;
	      }
	    ক্ষেত্র ic_return:
	      {
		ধ্রুবক অক্ষর বার্তা[] = G_("return from pointer to "
				      "non-enclosed address space");
		যদি (warnopt)
		  diagnosed = warning_at (location, warnopt, বার্তা);
		অন্যথা
		  error_at (location, বার্তা);
		বিরতি;
	      }
	    পূর্বনির্ধারিত:
	      gcc_unreachable ();
	    }
	  যদি (diagnosed)
	    {
	      যদি (errtype == ic_argpass)
		inform_for_arg (fundecl, রাশিমালা_loc, parmnum, type, rhstype);
	      অন্যথা
		inform (location, "expected %qT but pointer is of type %qT",
			type, rhstype);
	    }
	  ফেরত error_mark_গ্রন্থি;
	}

      /* Check if the right-hand side has a format attribute but the
	 left-hand side doesn't.  */
      যদি (warn_suggest_attribute_format
	  && check_missing_format_attribute (type, rhstype))
	{
	  নির্বাচন (errtype)
	  {
	  ক্ষেত্র ic_argpass:
	    warning_at (রাশিমালা_loc, OPT_Wsuggest_attribute_format,
			"argument %d of %qE might be "
			"a candidate for a format attribute",
			parmnum, rname);
	    বিরতি;
	  ক্ষেত্র ic_assign:
	    warning_at (location, OPT_Wsuggest_attribute_format,
			"assignment left-hand side might be "
			"a candidate for a format attribute");
	    বিরতি;
	  ক্ষেত্র ic_init:
	  ক্ষেত্র ic_init_const:
	    warning_at (location, OPT_Wsuggest_attribute_format,
			"initialization left-hand side might be "
			"a candidate for a format attribute");
	    বিরতি;
	  ক্ষেত্র ic_return:
	    warning_at (location, OPT_Wsuggest_attribute_format,
			"return type might be "
			"a candidate for a format attribute");
	    বিরতি;
	  পূর্বনির্ধারিত:
	    gcc_unreachable ();
	  }
	}

      /* See if the pointers point to incompatible scalar storage orders.  */
      যদি (warn_scalar_storage_order
	  && !null_pointer_constant_p (rhs)
	  && (AGGREGATE_TYPE_P (ttl) && TYPE_REVERSE_STORAGE_ORDER (ttl))
	     != (AGGREGATE_TYPE_P (ttr) && TYPE_REVERSE_STORAGE_ORDER (ttr)))
	{
	  বৃক্ষ t;

	  নির্বাচন (errtype)
	  {
	  ক্ষেত্র ic_argpass:
	    /* Do not warn for built-in functions, for example memcpy, since we
	       control how they behave and they can be useful in this area.  */
	    যদি (বৃক্ষ_CODE (rname) != FUNCTION_DECL
		|| !fndecl_built_in_p (rname))
	      warning_at (location, OPT_Wscalar_storage_order,
			  "passing argument %d of %qE from incompatible "
			  "scalar storage order", parmnum, rname);
	    বিরতি;
	  ক্ষেত্র ic_assign:
	    /* Do not warn if the RHS is a call to a function that returns a
	       pointer that is not an alias.  */
	    যদি (বৃক্ষ_CODE (rhs) != CALL_রাশিমালা
		|| (t = get_callee_fndecl (rhs)) == NULL_বৃক্ষ
		|| !DECL_IS_MALLOC (t))
	      warning_at (location, OPT_Wscalar_storage_order,
			  "assignment to %qT from pointer type %qT with "
			  "incompatible scalar storage order", type, rhstype);
	    বিরতি;
	  ক্ষেত্র ic_init:
	  ক্ষেত্র ic_init_const:
	    /* Likewise.  */
	    যদি (বৃক্ষ_CODE (rhs) != CALL_রাশিমালা
		|| (t = get_callee_fndecl (rhs)) == NULL_বৃক্ষ
		|| !DECL_IS_MALLOC (t))
	      warning_at (location, OPT_Wscalar_storage_order,
			  "initialization of %qT from pointer type %qT with "
			  "incompatible scalar storage order", type, rhstype);
	    বিরতি;
	  ক্ষেত্র ic_return:
	    warning_at (location, OPT_Wscalar_storage_order,
			"returning %qT from pointer type with incompatible "
			"scalar storage order %qT", rhstype, type);
	    বিরতি;
	  পূর্বনির্ধারিত:
	    gcc_unreachable ();
	  }
	}

      /* Any non-function converts to a [const][volatile] void *
	 and vice versa; otherwise, targets must be the same.
	 Meanwhile, the lhs target must have all the qualifiers of the rhs.  */
      যদি ((VOID_TYPE_P (ttl) && !TYPE_ATOMIC (ttl))
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
	  যদি (বৃক্ষ_CODE (ttr) == ARRAY_TYPE)
	    {
	      ttr = strip_array_types (ttr);
	      ttl = strip_array_types (ttl);

	      যদি (TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttr)
		  & ~TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttl))
		WARNING_FOR_QUALIFIERS (flag_isoc23,
					location, রাশিমালা_loc,
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
          অন্যথা যদি (pedantic
	      && ((VOID_TYPE_P (ttl) && বৃক্ষ_CODE (ttr) == FUNCTION_TYPE)
		  ||
		  (VOID_TYPE_P (ttr)
		   && !null_pointer_constant
		   && বৃক্ষ_CODE (ttl) == FUNCTION_TYPE)))
	    PEDWARN_FOR_ASSIGNMENT (location, রাশিমালা_loc, OPT_Wpedantic,
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
	  অন্যথা যদি (বৃক্ষ_CODE (ttr) != FUNCTION_TYPE
		   && বৃক্ষ_CODE (ttl) != FUNCTION_TYPE)
	    {
	       /* Assignments between atomic and non-atomic objects are OK.  */
	       যৌক্তিক warn_quals_ped = TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttr)
				     & ~TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttl);
	       যৌক্তিক warn_quals = TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttr)
				 & ~TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (strip_array_types (ttl));

	      /* Don't warn about loss of qualifier for conversions from
		 qualified void* to pointers to arrays with corresponding
		 qualifier on the element type (except for pedantic before C23). */
	      যদি (warn_quals || (warn_quals_ped && pedantic && !flag_isoc23))
		PEDWARN_FOR_QUALIFIERS (location, রাশিমালা_loc,
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
	      অন্যথা যদি (warn_quals_ped)
		pedwarn_c11 (location, OPT_Wc11_c23_compat,
			     "array with qualifier on the element is not qualified before C23");

	      /* If this is not a case of ignoring a mismatch in signedness,
		 no warning.  */
	      অন্যথা যদি (VOID_TYPE_P (ttl) || VOID_TYPE_P (ttr)
		       || target_cmp)
		;
	      /* If there is a mismatch, do warn.  */
	      অন্যথা যদি (warn_pointer_sign)
		নির্বাচন (errtype)
		  {
		  ক্ষেত্র ic_argpass:
		    {
		      auto_diagnostic_group d;
		      range_label_for_type_mismatch rhs_label (rhstype, type);
		      gcc_rich_location richloc (রাশিমালা_loc, &rhs_label,
						 highlight_colors::actual);
		      যদি (pedwarn (&richloc, OPT_Wpointer_sign,
				   "pointer targets in passing argument %d of "
				   "%qE differ in signedness", parmnum, rname))
			inform_for_arg (fundecl, রাশিমালা_loc, parmnum, type,
					rhstype);
		    }
		    বিরতি;
		  ক্ষেত্র ic_assign:
		    pedwarn (location, OPT_Wpointer_sign,
			     "pointer targets in assignment from %qT to %qT "
			     "differ in signedness", rhstype, type);
		    বিরতি;
		  ক্ষেত্র ic_init:
		  ক্ষেত্র ic_init_const:
		    pedwarn_init (location, OPT_Wpointer_sign,
				  "pointer targets in initialization of %qT "
				  "from %qT differ in signedness", type,
				  rhstype);
		    বিরতি;
		  ক্ষেত্র ic_return:
		    pedwarn (location, OPT_Wpointer_sign, "pointer targets in "
			     "returning %qT from a function with return type "
			     "%qT differ in signedness", rhstype, type);
		    বিরতি;
		  পূর্বনির্ধারিত:
		    gcc_unreachable ();
		  }
	    }
	  অন্যথা যদি (বৃক্ষ_CODE (ttl) == FUNCTION_TYPE
		   && বৃক্ষ_CODE (ttr) == FUNCTION_TYPE)
	    {
	      /* Because const and volatile on functions are restrictions
		 that say the function will not do certain things,
		 it is okay to use a const or volatile function
		 where an ordinary one is wanted, but not vice-versa.  */
	      যদি (TYPE_QUALS_NO_ADDR_SPACE (ttl)
		  & ~TYPE_QUALS_NO_ADDR_SPACE (ttr))
		PEDWARN_FOR_QUALIFIERS (location, রাশিমালা_loc,
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
      অন্যথা যদি (!objc_ok)
	{
	  auto_diagnostic_group d;
	  যৌক্তিক warned = মিথ্যা;
	  pp_markup::element_expected_type e_type (type);
	  pp_markup::element_actual_type e_rhstype (rhstype);
	  নির্বাচন (errtype)
	    {
	    ক্ষেত্র ic_argpass:
	      {
		range_label_for_type_mismatch rhs_label (rhstype, type);
		gcc_rich_location richloc (রাশিমালা_loc, &rhs_label,
					   highlight_colors::actual);
		warned
		  = permerror_opt (&richloc, OPT_Wincompatible_pointer_types,
				   "passing argument %d of %qE from "
				   "incompatible pointer type",
				   parmnum, rname);
		যদি (warned)
		  inform_for_arg (fundecl, রাশিমালা_loc, parmnum, type, rhstype);
	      }
	      বিরতি;
	    ক্ষেত্র ic_assign:
	      যদি (bltin)
		warned
		  = permerror_opt (location, OPT_Wincompatible_pointer_types,
				   "assignment to %e from pointer to "
				   "%qD with incompatible type %e",
				   &e_type, bltin, &e_rhstype);
	      অন্যথা
		warned
		  = permerror_opt (location, OPT_Wincompatible_pointer_types,
				   "assignment to %e from incompatible "
				   "pointer type %e",
				   &e_type, &e_rhstype);
	      বিরতি;
	    ক্ষেত্র ic_init:
	    ক্ষেত্র ic_init_const:
	      যদি (bltin)
		warned
		  = permerror_init (location, OPT_Wincompatible_pointer_types,
				    "initialization of %e from pointer to "
				    "%qD with incompatible type %e",
				    &e_type, bltin, &e_rhstype);
	      অন্যথা
		warned
		  = permerror_init (location, OPT_Wincompatible_pointer_types,
				    "initialization of %e from incompatible "
				    "pointer type %e",
				    &e_type, &e_rhstype);
	      বিরতি;
	    ক্ষেত্র ic_return:
	      যদি (bltin)
		warned
		  = permerror_opt (location, OPT_Wincompatible_pointer_types,
				   "returning pointer to %qD of type %e from "
				   "a function with incompatible type %e",
				   bltin, &e_rhstype, &e_type);
	      অন্যথা
		warned
		  = permerror_opt (location, OPT_Wincompatible_pointer_types,
				   "returning %e from a function with "
				   "incompatible return type %e",
				   &e_rhstype, &e_type);
	      বিরতি;
	    পূর্বনির্ধারিত:
	      gcc_unreachable ();
	    }
	  যদি (warned)
	    {
	      /* If the mismatching function type is a pointer to a function,
		 try to show the decl of the function.  */
	      যদি (বৃক্ষ_CODE (rhs) == ADDR_রাশিমালা
		  && বৃক্ষ_CODE (বৃক্ষ_OPERAND (rhs, 0)) == FUNCTION_DECL)
		{
		  বৃক্ষ rhs_fndecl = বৃক্ষ_OPERAND (rhs, 0);
		  যদি (!DECL_IS_UNDECLARED_BUILTIN (rhs_fndecl))
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

      ফেরত convert (type, rhs);
    }
  অন্যথা যদি (codel == POINTER_TYPE && coder == ARRAY_TYPE)
    {
      /* ??? This should not be an error when inlining calls to
	 unprototyped functions.  */
      ধ্রুবক অক্ষর বার্তা[] = "invalid use of non-lvalue array";
      যদি (warnopt)
	warning_at (location, warnopt, বার্তা);
      অন্যথা
	error_at (location, বার্তা);
      ফেরত error_mark_গ্রন্থি;
    }
  অন্যথা যদি (codel == POINTER_TYPE
	   && (coder == INTEGER_TYPE
	       || coder == ENUMERAL_TYPE
	       || coder == BOOLEAN_TYPE
	       || coder == NULLPTR_TYPE
	       || coder == BITINT_TYPE))
    {
      যদি (null_pointer_constant && c_inhibit_evaluation_warnings == 0
	  && coder != NULLPTR_TYPE)
	warning_at (location, OPT_Wzero_as_null_pointer_constant,
		    "zero as null pointer constant");
      /* A NULLPTR type is just a nullptr always.  */
      যদি (coder == NULLPTR_TYPE)
	ফেরত omit_one_operand_loc (রাশিমালা_loc, type, nullptr_গ্রন্থি, rhs);
      /* An explicit constant 0 or type nullptr_t can convert to a pointer,
	 or one that results from arithmetic, even including a cast to
	 integer type.  */
      অন্যথা যদি (!null_pointer_constant)
	নির্বাচন (errtype)
	  {
	  ক্ষেত্র ic_argpass:
	    {
	      auto_diagnostic_group d;
	      range_label_for_type_mismatch rhs_label (rhstype, type);
	      gcc_rich_location richloc (রাশিমালা_loc, &rhs_label,
					 highlight_colors::actual);
	      যদি (permerror_opt (&richloc, OPT_Wint_conversion,
				 "passing argument %d of %qE makes pointer "
				 "from integer without a cast", parmnum, rname))
		{
		  maybe_emit_indirection_note (রাশিমালা_loc, rhs, type);
		  inform_for_arg (fundecl, রাশিমালা_loc, parmnum, type, rhstype);
		}
	    }
	    বিরতি;
	  ক্ষেত্র ic_assign:
	    permerror_opt (location, OPT_Wint_conversion,
			   "assignment to %qT from %qT makes pointer from "
			   "integer without a cast", type, rhstype);
	    বিরতি;
	  ক্ষেত্র ic_init:
	  ক্ষেত্র ic_init_const:
	    permerror_init (location, OPT_Wint_conversion,
			    "initialization of %qT from %qT makes pointer "
			    "from integer without a cast", type, rhstype);
	    বিরতি;
	  ক্ষেত্র ic_return:
	    permerror_init (location, OPT_Wint_conversion,
			    "returning %qT from a function with return type "
			    "%qT makes pointer from integer without a cast",
			    rhstype, type);
	    বিরতি;
	  পূর্বনির্ধারিত:
	    gcc_unreachable ();
	  }

      ফেরত convert (type, rhs);
    }
  অন্যথা যদি ((codel == INTEGER_TYPE || codel == BITINT_TYPE)
	   && coder == POINTER_TYPE)
    {
      নির্বাচন (errtype)
	{
	ক্ষেত্র ic_argpass:
	  {
	    auto_diagnostic_group d;
	    range_label_for_type_mismatch rhs_label (rhstype, type);
	    gcc_rich_location richloc (রাশিমালা_loc, &rhs_label,
				       highlight_colors::actual);
	    যদি (permerror_opt (&richloc, OPT_Wint_conversion,
			       "passing argument %d of %qE makes integer from "
			       "pointer without a cast", parmnum, rname))
	      {
		maybe_emit_indirection_note (রাশিমালা_loc, rhs, type);
		inform_for_arg (fundecl, রাশিমালা_loc, parmnum, type, rhstype);
	      }
	  }
	  বিরতি;
	ক্ষেত্র ic_assign:
	  permerror_opt (location, OPT_Wint_conversion,
			 "assignment to %qT from %qT makes integer from "
			 "pointer without a cast", type, rhstype);
	  বিরতি;
	ক্ষেত্র ic_init:
	ক্ষেত্র ic_init_const:
	  permerror_init (location, OPT_Wint_conversion,
			  "initialization of %qT from %qT makes integer "
			  "from pointer without a cast", type, rhstype);
	  বিরতি;
	ক্ষেত্র ic_return:
	  permerror_opt (location, OPT_Wint_conversion, "returning %qT from a "
			 "function with return type %qT makes integer from "
			 "pointer without a cast", rhstype, type);
	  বিরতি;
	পূর্বনির্ধারিত:
	  gcc_unreachable ();
	}

      ফেরত convert (type, rhs);
    }
  অন্যথা যদি (C_BOOLEAN_TYPE_P (type)
	   /* The type nullptr_t may be converted to bool.  The
	      result is false.  */
	   && (coder == POINTER_TYPE || coder == NULLPTR_TYPE))
    {
      বৃক্ষ ret;
      যৌক্তিক save = in_late_দ্বিমিক_op;
      in_late_দ্বিমিক_op = সত্য;
      ret = convert (type, rhs);
      in_late_দ্বিমিক_op = save;
      ফেরত ret;
    }
  অন্যথা যদি (codel == NULLPTR_TYPE && null_pointer_constant)
    ফেরত convert (type, rhs);

  নির্বাচন (errtype)
    {
    ক্ষেত্র ic_argpass:
      {
	auto_diagnostic_group d;
	range_label_for_type_mismatch rhs_label (rhstype, type);
	gcc_rich_location richloc (রাশিমালা_loc, &rhs_label,
				   highlight_colors::actual);
	ধ্রুবক অক্ষর বার্তা[] = G_("incompatible type for argument %d of %qE");
	যদি (warnopt)
	  warning_at (রাশিমালা_loc, warnopt, বার্তা, parmnum, rname);
	অন্যথা
	  error_at (&richloc, বার্তা, parmnum, rname);
	inform_for_arg (fundecl, রাশিমালা_loc, parmnum, type, rhstype);
      }
      বিরতি;
    ক্ষেত্র ic_assign:
      {
	ধ্রুবক অক্ষর বার্তা[]
	  = G_("incompatible types when assigning to type %qT from type %qT");
	যদি (warnopt)
	  warning_at (রাশিমালা_loc, 0, বার্তা, type, rhstype);
	অন্যথা
	  error_at (রাশিমালা_loc, বার্তা, type, rhstype);
	বিরতি;
      }
    ক্ষেত্র ic_init:
    ক্ষেত্র ic_init_const:
      {
	ধ্রুবক অক্ষর বার্তা[]
	  = G_("incompatible types when initializing type %qT using type %qT");
	যদি (warnopt)
	  warning_at (location, 0, বার্তা, type, rhstype);
	অন্যথা
	  error_at (location, বার্তা, type, rhstype);
	বিরতি;
      }
    ক্ষেত্র ic_return:
      {
	ধ্রুবক অক্ষর বার্তা[]
	  = G_("incompatible types when returning type %qT but %qT was expected");
	যদি (warnopt)
	  warning_at (location, 0, বার্তা, rhstype, type);
	অন্যথা
	  error_at (location, বার্তা, rhstype, type);
	বিরতি;
      }
    পূর্বনির্ধারিত:
      gcc_unreachable ();
    }

  ফেরত error_mark_গ্রন্থি;
}

/* If VALUE is a compound expr all of whose expressions are constant, then
   return its value.  Otherwise, return error_mark_node.

   This is for handling COMPOUND_EXPRs as initializer elements
   which is allowed with a warning when -pedantic is specified.  */

স্থির বৃক্ষ
valid_compound_রাশিমালা_initializer (বৃক্ষ মান, বৃক্ষ endtype)
{
  যদি (বৃক্ষ_CODE (মান) == COMPOUND_রাশিমালা)
    {
      যদি (valid_compound_রাশিমালা_initializer (বৃক্ষ_OPERAND (মান, 0), endtype)
	  == error_mark_গ্রন্থি)
	ফেরত error_mark_গ্রন্থি;
      ফেরত valid_compound_রাশিমালা_initializer (বৃক্ষ_OPERAND (মান, 1),
					      endtype);
    }
  অন্যথা যদি (!initializer_constant_valid_p (মান, endtype))
    ফেরত error_mark_গ্রন্থি;
  অন্যথা
    ফেরত মান;
}

/* Perform appropriate conversions on the initial value of a variable,
   store it in the declaration DECL,
   and print any error messages that are appropriate.
   If ORIGTYPE is not NULL_TREE, it is the original type of INIT.
   If the init is invalid, store an ERROR_MARK.

   INIT_LOC is the location of the initial value.  */

শূন্য
store_init_মান (location_t init_loc, বৃক্ষ decl, বৃক্ষ init, বৃক্ষ origtype)
{
  বৃক্ষ মান, type;
  যৌক্তিক npc = মিথ্যা;
  যৌক্তিক int_const_রাশিমালা = মিথ্যা;
  যৌক্তিক arith_const_রাশিমালা = মিথ্যা;

  /* If variable's type was invalidly declared, just ignore it.  */

  type = বৃক্ষ_TYPE (decl);
  যদি (বৃক্ষ_CODE (type) == ERROR_MARK)
    ফেরত;

  /* Digest the specified initializer into an expression.  */

  যদি (init)
    {
      npc = null_pointer_constant_p (init);
      int_const_রাশিমালা = (বৃক্ষ_CODE (init) == INTEGER_CST
			&& !বৃক্ষ_OVERFLOW (init)
			&& INTEGRAL_TYPE_P (বৃক্ষ_TYPE (init)));
      /* Not fully determined before folding.  */
      arith_const_রাশিমালা = সত্য;
    }
  যৌক্তিক constexpr_p = (VAR_P (decl)
		      && C_DECL_DECLARED_CONSTEXPR (decl));
  মান = digest_init (init_loc, decl, type, init, origtype, npc,
		       int_const_রাশিমালা, arith_const_রাশিমালা, সত্য,
		       বৃক্ষ_STATIC (decl) || constexpr_p, constexpr_p);

  /* Store the expression if valid; else report error.  */

  যদি (!in_system_header_at (প্রবেশ_location)
      && AGGREGATE_TYPE_P (বৃক্ষ_TYPE (decl)) && !বৃক্ষ_STATIC (decl))
    warning (OPT_Wtraditional, "traditional C rejects automatic "
	     "aggregate initialization");

  যদি (মান != error_mark_গ্রন্থি || বৃক্ষ_CODE (decl) != FUNCTION_DECL)
    DECL_INITIAL (decl) = মান;

  /* ANSI wants warnings about out-of-range constant initializers.  */
  STRIP_TYPE_NOPS (মান);
  যদি (বৃক্ষ_STATIC (decl))
    constant_expression_warning (মান);

  /* Check if we need to set array size from compound literal size.  */
  যদি (বৃক্ষ_CODE (type) == ARRAY_TYPE
      && TYPE_DOMAIN (type) == NULL_বৃক্ষ
      && মান != error_mark_গ্রন্থি)
    {
      বৃক্ষ inside_init = init;

      STRIP_TYPE_NOPS (inside_init);
      inside_init = fold (inside_init);

      যদি (বৃক্ষ_CODE (inside_init) == COMPOUND_LITERAL_রাশিমালা)
	{
	  বৃক্ষ cldecl = COMPOUND_LITERAL_রাশিমালা_DECL (inside_init);

	  যদি (TYPE_DOMAIN (বৃক্ষ_TYPE (cldecl)))
	    {
	      /* For int foo[] = (int [3]){1}; we need to set array size
		 now since later on array initializer will be just the
		 brace enclosed list of the compound literal.  */
	      বৃক্ষ etype = strip_array_types (বৃক্ষ_TYPE (decl));
	      type = build_distinct_type_copy (TYPE_MAIN_VARIANT (type));
	      TYPE_DOMAIN (type) = TYPE_DOMAIN (বৃক্ষ_TYPE (cldecl));
	      layout_type (type);
	      layout_decl (cldecl, 0);
	      বৃক্ষ_TYPE (decl)
		= c_build_qualified_type (type, TYPE_QUALS (etype));
	    }
	}
    }
}

/* Methods for storing and printing names for error messages.  */

/* Implement a spelling stack that allows components of a name to be pushed
   and popped.  Each element on the stack is this structure.  */

কাঠামো spelling
{
  পূর্ণসংখ্যা kind;
  সংঘ
    {
      unsigned HOST_WIDE_INT i;
      ধ্রুবক অক্ষর *s;
    } u;
};

#define SPELLING_STRING 1
#define SPELLING_MEMBER 2
#define SPELLING_BOUNDS 3

স্থির কাঠামো spelling *spelling;	/* Next stack element (unused).  */
স্থির কাঠামো spelling *spelling_base;	/* Spelling stack base.  */
স্থির পূর্ণসংখ্যা spelling_আকার;		/* Size of the spelling stack.  */

/* Macros to save and restore the spelling stack around push_... functions.
   Alternative to SAVE_SPELLING_STACK.  */

#define SPELLING_DEPTH() (spelling - spelling_base)
#define RESTORE_SPELLING_DEPTH(DEPTH) (spelling = spelling_base + (DEPTH))

/* Push an element on the spelling stack with type KIND and assign VALUE
   to MEMBER.  */

#define ঠেলো_SPELLING(KIND, মান_2, MEMBER)				\
{									\
  পূর্ণসংখ্যা depth = SPELLING_DEPTH ();					\
									\
  যদি (depth >= spelling_আকার)						\
    {									\
      spelling_আকার += 10;						\
      spelling_base = XRESIZEVEC (কাঠামো spelling, spelling_base,	\
				  spelling_আকার);			\
      RESTORE_SPELLING_DEPTH (depth);					\
    }									\
									\
  spelling->kind = (KIND);						\
  spelling->MEMBER = (মান_2);						\
  spelling++;								\
}

/* Push STRING on the stack.  Printed literally.  */

স্থির শূন্য
ঠেলো_string (ধ্রুবক অক্ষর *string)
{
  ঠেলো_SPELLING (SPELLING_STRING, string, u.s);
}

/* Push a member name on the stack.  Printed as '.' STRING.  */

স্থির শূন্য
ঠেলো_member_name (বৃক্ষ decl)
{
  ধ্রুবক অক্ষর *ধ্রুবক string
    = (DECL_NAME (decl)
       ? identifier_to_locale (IDENTIFIER_POINTER (DECL_NAME (decl)))
       : _("<anonymous>"));
  ঠেলো_SPELLING (SPELLING_MEMBER, string, u.s);
}

/* Push an array bounds on the stack.  Printed as [BOUNDS].  */

স্থির শূন্য
ঠেলো_array_bounds (unsigned HOST_WIDE_INT bounds)
{
  ঠেলো_SPELLING (SPELLING_BOUNDS, bounds, u.i);
}

/* Compute the maximum size in bytes of the printed spelling.  */

স্থির পূর্ণসংখ্যা
spelling_দৈর্ঘ্য (শূন্য)
{
  পূর্ণসংখ্যা আকার_2 = 0;
  কাঠামো spelling *p;

  জন্য (p = spelling_base; p < spelling; p++)
    {
      যদি (p->kind == SPELLING_BOUNDS)
	আকার_2 += 25;
      অন্যথা
	আকার_2 += strlen (p->u.s) + 1;
    }

  ফেরত আকার_2;
}

/* Print the spelling to BUFFER and return it.  */

স্থির অক্ষর *
print_spelling (অক্ষর *বাফার)
{
  অক্ষর *d = বাফার;
  কাঠামো spelling *p;

  জন্য (p = spelling_base; p < spelling; p++)
    যদি (p->kind == SPELLING_BOUNDS)
      {
	sprintf (d, "[" HOST_WIDE_INT_PRINT_UNSIGNED "]", p->u.i);
	d += strlen (d);
      }
    অন্যথা
      {
	ধ্রুবক অক্ষর *s;
	যদি (p->kind == SPELLING_MEMBER)
	  *d++ = '.';
	জন্য (s = p->u.s; (*d = *s++); d++)
	  ;
      }
  *d++ = '\0';
  ফেরত বাফার;
}

/* Check whether INIT, a floating or integer constant, is
   representable in TYPE, a real floating type with the same radix or
   a decimal floating type initialized with a binary floating
   constant.  Return true if OK, false if not.  */
স্থির যৌক্তিক
constexpr_init_fits_real_type (বৃক্ষ type, বৃক্ষ init)
{
  gcc_assert (SCALAR_FLOAT_TYPE_P (type));
  gcc_assert (বৃক্ষ_CODE (init) == INTEGER_CST || বৃক্ষ_CODE (init) == REAL_CST);
  যদি (বৃক্ষ_CODE (init) == REAL_CST
      && TYPE_MODE (বৃক্ষ_TYPE (init)) == TYPE_MODE (type))
    {
      /* Same mode, no conversion required except for the case of
	 signaling NaNs if the types are incompatible (e.g. double and
	 long double with the same mode).  */
      যদি (REAL_মান_ISSIGNALING_NAN (বৃক্ষ_REAL_CST (init))
	  && !comptypes (TYPE_MAIN_VARIANT (type),
			 TYPE_MAIN_VARIANT (বৃক্ষ_TYPE (init))))
	ফেরত মিথ্যা;
      ফেরত সত্য;
    }
  যদি (বৃক্ষ_CODE (init) == INTEGER_CST)
    {
      বৃক্ষ converted = build_real_from_int_cst (type, init);
      যৌক্তিক fail = মিথ্যা;
      wide_int w = real_to_integer (&বৃক্ষ_REAL_CST (converted), &fail,
				    TYPE_PRECISION (বৃক্ষ_TYPE (init)));
      ফেরত !fail && wi::eq_p (w, wi::to_wide (init));
    }
  যদি (REAL_মান_ISSIGNALING_NAN (বৃক্ষ_REAL_CST (init)))
    ফেরত মিথ্যা;
  যদি ((REAL_মান_ISINF (বৃক্ষ_REAL_CST (init))
       && MODE_HAS_INFINITIES (TYPE_MODE (type)))
      || (REAL_মান_ISNAN (বৃক্ষ_REAL_CST (init))
	  && MODE_HAS_NANS (TYPE_MODE (type))))
    ফেরত সত্য;
  যদি (DECIMAL_FLOAT_TYPE_P (type)
      && !DECIMAL_FLOAT_TYPE_P (বৃক্ষ_TYPE (init)))
    {
      /* This is valid if the real number represented by the
	 initializer can be exactly represented in the decimal
	 type.  Compare the values using MPFR.  */
      REAL_মান_TYPE t;
      real_convert (&t, TYPE_MODE (type), &বৃক্ষ_REAL_CST (init));
      mpfr_t bin_val, dec_val;
      mpfr_init2 (bin_val, REAL_MODE_FORMAT (TYPE_MODE (বৃক্ষ_TYPE (init)))->p);
      mpfr_init2 (dec_val, REAL_MODE_FORMAT (TYPE_MODE (বৃক্ষ_TYPE (init)))->p);
      mpfr_from_real (bin_val, &বৃক্ষ_REAL_CST (init), MPFR_RNDN);
      অক্ষর string[256];
      real_to_decimal (string, &t, আকার string, 0, 1);
      যৌক্তিক res = (mpfr_strtofr (dec_val, string, ফাঁকা, 10, MPFR_RNDN) == 0
		  && mpfr_equal_p (bin_val, dec_val));
      mpfr_clear (bin_val);
      mpfr_clear (dec_val);
      ফেরত res;
    }
  /* exact_real_truncate is not quite right here, since it doesn't
     allow even an exact conversion to subnormal values.  */
  REAL_মান_TYPE t;
  real_convert (&t, TYPE_MODE (type), &বৃক্ষ_REAL_CST (init));
  ফেরত real_identical (&t, &বৃক্ষ_REAL_CST (init));
}

/* Check whether INIT (location LOC) is valid as a 'constexpr'
   initializer for type TYPE, and give an error if not.  INIT has
   already been folded and verified to be constant.  INT_CONST_EXPR
   and ARITH_CONST_EXPR say whether it is an integer constant
   expression or arithmetic constant expression, respectively.  If
   TYPE is not a scalar type, this function does nothing.  */

স্থির শূন্য
check_constexpr_init (location_t loc, বৃক্ষ type, বৃক্ষ init,
		      যৌক্তিক int_const_রাশিমালা, যৌক্তিক arith_const_রাশিমালা)
{
  যদি (POINTER_TYPE_P (type))
    {
      /* The initializer must be null.  */
      যদি (বৃক্ষ_CODE (init) != INTEGER_CST || !integer_zerop (init))
	error_at (loc, "%<constexpr%> pointer initializer is not null");
      ফেরত;
    }
  যদি (INTEGRAL_TYPE_P (type))
    {
      /* The initializer must be an integer constant expression,
	 representable in the target type.  */
      যদি (!int_const_রাশিমালা)
	{
	  যদি (বৃক্ষ_CODE (init) == RAW_তথ্য_CST
	      && TYPE_PRECISION (type) == CHAR_BIT)
	    {
	      যদি (!TYPE_UNSIGNED (type))
		জন্য (unsigned পূর্ণসংখ্যা i = 0;
		     i < (unsigned) RAW_তথ্য_দৈর্ঘ্য (init); ++i)
		  যদি (RAW_তথ্য_SCHAR_ELT (init, i) < 0)
		    {
		      error_at (loc, "%<constexpr%> initializer not "
				"representable in type of object");
		      বিরতি;
		    }
	    }
	  অন্যথা
	    error_at (loc, "%<constexpr%> integer initializer is not an "
		      "integer constant expression");
	}
      অন্যথা যদি (!int_fits_type_p (init, type))
	error_at (loc, "%<constexpr%> initializer not representable in "
		  "type of object");
      ফেরত;
    }
  /* We don't apply any extra checks to extension types such as vector
     or fixed-point types.  */
  যদি (বৃক্ষ_CODE (type) != REAL_TYPE && বৃক্ষ_CODE (type) != COMPLEX_TYPE)
    ফেরত;
  যদি (!arith_const_রাশিমালা)
    {
      error_at (loc, "%<constexpr%> initializer is not an arithmetic "
		"constant expression");
      ফেরত;
    }
  /* We don't apply any extra checks to complex integers.  */
  যদি (বৃক্ষ_CODE (type) == COMPLEX_TYPE
      && বৃক্ষ_CODE (বৃক্ষ_TYPE (type)) != REAL_TYPE)
    ফেরত;
  /* Following N3082, a real type cannot be initialized from a complex
     type and a binary type cannot be initialized from a decimal type
     (but initializing a decimal type from a binary type is OK).
     Signaling NaN initializers are OK only if the types are
     compatible (not just the same mode); all quiet NaN and infinity
     initializations are considered to preserve the value.  */
  যদি (বৃক্ষ_CODE (বৃক্ষ_TYPE (init)) == COMPLEX_TYPE
      && SCALAR_FLOAT_TYPE_P (type))
    {
      error_at (loc, "%<constexpr%> initializer for a real type is of "
		"complex type");
      ফেরত;
    }
  যদি (SCALAR_FLOAT_TYPE_P (type)
      && SCALAR_FLOAT_TYPE_P (বৃক্ষ_TYPE (init))
      && DECIMAL_FLOAT_TYPE_P (বৃক্ষ_TYPE (init))
      && !DECIMAL_FLOAT_TYPE_P (type))
    {
      error_at (loc, "%<constexpr%> initializer for a binary "
		"floating-point type is of decimal type");
      ফেরত;
    }
  যৌক্তিক fits;
  যদি (বৃক্ষ_CODE (type) == COMPLEX_TYPE)
    {
      নির্বাচন (বৃক্ষ_CODE (init))
	{
	ক্ষেত্র INTEGER_CST:
	ক্ষেত্র REAL_CST:
	  fits = constexpr_init_fits_real_type (বৃক্ষ_TYPE (type), init);
	  বিরতি;
	ক্ষেত্র COMPLEX_CST:
	  fits = (constexpr_init_fits_real_type (বৃক্ষ_TYPE (type),
						 বৃক্ষ_REALPART (init))
		  && constexpr_init_fits_real_type (বৃক্ষ_TYPE (type),
						    বৃক্ষ_IMAGPART (init)));
	  বিরতি;
	পূর্বনির্ধারিত:
	  gcc_unreachable ();
	}
    }
  অন্যথা
    fits = constexpr_init_fits_real_type (type, init);
  যদি (!fits)
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

স্থির বৃক্ষ
digest_init (location_t init_loc, বৃক্ষ decl, বৃক্ষ type, বৃক্ষ init,
	     বৃক্ষ origtype, যৌক্তিক null_pointer_constant, যৌক্তিক int_const_রাশিমালা,
	     যৌক্তিক arith_const_রাশিমালা, যৌক্তিক strict_string,
	     যৌক্তিক require_constant, যৌক্তিক require_constexpr)
{
  গণনা বৃক্ষ_code code = বৃক্ষ_CODE (type);
  বৃক্ষ inside_init = init;
  বৃক্ষ semantic_type = NULL_বৃক্ষ;
  যৌক্তিক maybe_const = সত্য;

  যদি (type == error_mark_গ্রন্থি
      || !init
      || error_operand_p (init))
    ফেরত error_mark_গ্রন্থি;

  STRIP_TYPE_NOPS (inside_init);

  /* If require_constant is TRUE,  when the initializer is a call to
     .ACCESS_WITH_SIZE, use the first argument as the initializer.
     For example:
     y = (char *) .ACCESS_WITH_SIZE ((char *) &static_annotated.c,...)
     will be converted to
     y = &static_annotated.c.  */

  যদি (require_constant
      && বৃক্ষ_CODE (inside_init) == NOP_রাশিমালা
      && বৃক্ষ_CODE (বৃক্ষ_OPERAND (inside_init, 0)) == CALL_রাশিমালা
      && is_access_with_আকার_p (বৃক্ষ_OPERAND (inside_init, 0)))
    inside_init
      = get_ref_from_access_with_আকার (বৃক্ষ_OPERAND (inside_init, 0));

  যদি (!c_in_omp_for)
    {
      যদি (বৃক্ষ_CODE (inside_init) == EXCESS_PRECISION_রাশিমালা)
	{
	  semantic_type = বৃক্ষ_TYPE (inside_init);
	  inside_init = বৃক্ষ_OPERAND (inside_init, 0);
	}
      inside_init = c_fully_fold (inside_init, require_constant, &maybe_const);
    }
  /* TODO: this may not detect all cases of expressions folding to
     constants that are not arithmetic constant expressions.  */
  যদি (!maybe_const)
    arith_const_রাশিমালা = মিথ্যা;
  অন্যথা যদি (!INTEGRAL_TYPE_P (বৃক্ষ_TYPE (inside_init))
	   && বৃক্ষ_CODE (বৃক্ষ_TYPE (inside_init)) != REAL_TYPE
	   && বৃক্ষ_CODE (বৃক্ষ_TYPE (inside_init)) != COMPLEX_TYPE)
    arith_const_রাশিমালা = মিথ্যা;
  অন্যথা যদি (বৃক্ষ_CODE (inside_init) != INTEGER_CST
	   && বৃক্ষ_CODE (inside_init) != REAL_CST
	   && বৃক্ষ_CODE (inside_init) != COMPLEX_CST
	   && বৃক্ষ_CODE (inside_init) != RAW_তথ্য_CST)
    arith_const_রাশিমালা = মিথ্যা;
  অন্যথা যদি (বৃক্ষ_OVERFLOW (inside_init))
    arith_const_রাশিমালা = মিথ্যা;

  /* Initialization of an array of chars from a string constant
     optionally enclosed in braces.  */

  যদি (code == ARRAY_TYPE && inside_init
      && বৃক্ষ_CODE (inside_init) == STRING_CST)
    {
      বৃক্ষ typ1
	= (TYPE_ATOMIC (বৃক্ষ_TYPE (type))
	   ? c_build_qualified_type (TYPE_MAIN_VARIANT (বৃক্ষ_TYPE (type)),
				     TYPE_QUAL_ATOMIC)
	   : TYPE_MAIN_VARIANT (বৃক্ষ_TYPE (type)));
      /* Note that an array could be both an array of character type
	 and an array of wchar_t if wchar_t is signed char or unsigned
	 char.  */
      যৌক্তিক char_array = (typ1 == char_type_গ্রন্থি
			 || typ1 == signed_char_type_গ্রন্থি
			 || typ1 == unsigned_char_type_গ্রন্থি);
      যৌক্তিক wchar_array = comptypes (typ1, wchar_type_গ্রন্থি);
      যৌক্তিক char16_array = comptypes (typ1, char16_type_গ্রন্থি);
      যৌক্তিক char32_array = comptypes (typ1, char32_type_গ্রন্থি);

      যদি (char_array || wchar_array || char16_array || char32_array)
	{
	  কাঠামো c_রাশিমালা রাশিমালা;
	  বৃক্ষ typ2 = TYPE_MAIN_VARIANT (বৃক্ষ_TYPE (বৃক্ষ_TYPE (inside_init)));
	  যৌক্তিক incompat_string_cst = মিথ্যা;
	  রাশিমালা.মান = inside_init;
	  রাশিমালা.original_code = (strict_string ? STRING_CST : ERROR_MARK);
	  রাশিমালা.original_type = ফাঁকা;
	  রাশিমালা.m_decimal = 0;
	  maybe_warn_string_init (init_loc, type, রাশিমালা);

	  যদি (flexible_array_member_type_p (type))
	    pedwarn_init (init_loc, OPT_Wpedantic,
			  "initialization of a flexible array member");

	  যদি (comptypes (TYPE_MAIN_VARIANT (বৃক্ষ_TYPE (inside_init)),
			 TYPE_MAIN_VARIANT (type)))
	    ফেরত inside_init;

	  যদি (char_array)
	    {
	      যদি (typ2 != char_type_গ্রন্থি && typ2 != char8_type_গ্রন্থি)
		incompat_string_cst = সত্য;
	    }
	  অন্যথা যদি (!comptypes (typ1, typ2))
	    incompat_string_cst = সত্য;

          যদি (incompat_string_cst)
            {
	      error_init (init_loc, "cannot initialize array of %qT from "
			  "a string literal with type array of %qT",
			  typ1, typ2);
	      ফেরত error_mark_গ্রন্থি;
            }

	  যদি (require_constexpr
	      && TYPE_UNSIGNED (typ1) != TYPE_UNSIGNED (typ2))
	    {
	      /* Check if all characters of the string can be
		 represented in the type of the constexpr object being
		 initialized.  */
	      unsigned HOST_WIDE_INT len = বৃক্ষ_STRING_দৈর্ঘ্য (inside_init);
	      ধ্রুবক unsigned অক্ষর *p =
		(ধ্রুবক unsigned অক্ষর *) বৃক্ষ_STRING_POINTER (inside_init);
	      gcc_assert (CHAR_TYPE_আকার == 8 && CHAR_BIT == 8);
	      জন্য (unsigned i = 0; i < len; i++)
		যদি (p[i] > 127)
		  {
		    error_init (init_loc, "%<constexpr%> initializer not "
				"representable in type of object");
		    বিরতি;
		  }
	    }

	  যদি (TYPE_DOMAIN (type) != NULL_বৃক্ষ
	      && TYPE_আকার (type) != NULL_বৃক্ষ
	      && বৃক্ষ_CODE (TYPE_আকার (type)) == INTEGER_CST)
	    {
	      unsigned HOST_WIDE_INT len = বৃক্ষ_STRING_দৈর্ঘ্য (inside_init);

	      যদি (compare_বৃক্ষ_int (TYPE_আকার_UNIT (type), len) < 0)
		{
		  unsigned HOST_WIDE_INT avail
		    = বৃক্ষ_to_uhwi (TYPE_আকার_UNIT (type));
		  unsigned unit = TYPE_PRECISION (typ1) / BITS_PER_UNIT;
		  ধ্রুবক অক্ষর *p = বৃক্ষ_STRING_POINTER (inside_init);

		  /* Construct truncated string.  */
		  inside_init = build_string (avail, p);

		  /* Subtract the size of a single (possibly wide) character
		     because it may be ok to ignore the terminating NUL char
		     that is counted in the length of the constant.  */
		  যদি (len - unit > avail)
		    pedwarn_init (init_loc, 0,
				  "initializer-string for array of %qT "
				  "is too long (%wu chars into %wu "
				  "available)", typ1, len, avail);
		  অন্যথা যদি (warn_cxx_compat)
		    warning_at (init_loc, OPT_Wc___compat,
				"initializer-string for array of %qT "
				"is too long for C++ (%wu chars into %wu "
				"available)", typ1, len, avail);
		  অন্যথা যদি (warn_unterminated_string_initialization
			   && get_attr_nonstring_decl (decl) == NULL_বৃক্ষ)
		    warning_at (init_loc,
				OPT_Wunterminated_string_initialization,
				"initializer-string for array of %qT "
				"truncates NUL terminator but destination "
				"lacks %qs attribute (%wu chars into %wu "
				"available)", typ1, "nonstring", len, avail);
		}
	    }

	  বৃক্ষ_TYPE (inside_init) = type;
	  ফেরত inside_init;
	}
      অন্যথা যদি (INTEGRAL_TYPE_P (typ1))
	{
	  error_init (init_loc, "array of inappropriate type initialized "
		      "from string constant");
	  ফেরত error_mark_গ্রন্থি;
	}
    }

  /* Build a VECTOR_CST from a *constant* vector constructor.  If the
     vector constructor is not constant (e.g. {1,2,3,foo()}) then punt
     below and handle as a constructor.  */
  যদি (code == VECTOR_TYPE
      && VECTOR_TYPE_P (বৃক্ষ_TYPE (inside_init))
      && vector_types_convertible_p (বৃক্ষ_TYPE (inside_init), type, সত্য)
      && বৃক্ষ_CONSTANT (inside_init))
    {
      যদি (বৃক্ষ_CODE (inside_init) == VECTOR_CST
	  && comptypes (TYPE_MAIN_VARIANT (বৃক্ষ_TYPE (inside_init)),
			TYPE_MAIN_VARIANT (type)))
	ফেরত inside_init;

      যদি (বৃক্ষ_CODE (inside_init) == CONSTRUCTOR)
	{
	  unsigned HOST_WIDE_INT ix;
	  বৃক্ষ মান;
	  যৌক্তিক constant_p = সত্য;

	  /* Iterate through elements and check if all constructor
	     elements are *_CSTs.  */
	  FOR_EACH_CONSTRUCTOR_মান (CONSTRUCTOR_ELTS (inside_init), ix, মান)
	    যদি (!CONSTANT_CLASS_P (মান))
	      {
		constant_p = মিথ্যা;
		বিরতি;
	      }

	  যদি (constant_p)
	    ফেরত build_vector_from_ctor (type,
					   CONSTRUCTOR_ELTS (inside_init));
	}
    }

  যদি (warn_sequence_point)
    verify_sequence_points (inside_init);

  /* Any type can be initialized
     from an expression of the same type, optionally with braces.  */

  যদি (inside_init && বৃক্ষ_TYPE (inside_init) != NULL_বৃক্ষ
      && (comptypes (TYPE_MAIN_VARIANT (বৃক্ষ_TYPE (inside_init)),
		     TYPE_MAIN_VARIANT (type))
	  || (code == ARRAY_TYPE
	      && comptypes (বৃক্ষ_TYPE (inside_init), type))
	  || (gnu_vector_type_p (type)
	      && comptypes (বৃক্ষ_TYPE (inside_init), type))
	  || (code == POINTER_TYPE
	      && বৃক্ষ_CODE (বৃক্ষ_TYPE (inside_init)) == ARRAY_TYPE
	      && comptypes (বৃক্ষ_TYPE (বৃক্ষ_TYPE (inside_init)),
			    বৃক্ষ_TYPE (type)))))
    {
      যদি (code == POINTER_TYPE)
	{
	  যদি (বৃক্ষ_CODE (বৃক্ষ_TYPE (inside_init)) == ARRAY_TYPE)
	    {
	      যদি (বৃক্ষ_CODE (inside_init) == STRING_CST
		  || বৃক্ষ_CODE (inside_init) == COMPOUND_LITERAL_রাশিমালা)
		inside_init = array_to_pointer_conversion
		  (init_loc, inside_init);
	      অন্যথা
		{
		  error_init (init_loc, "invalid use of non-lvalue array");
		  ফেরত error_mark_গ্রন্থি;
		}
	    }
	}

      যদি (code == VECTOR_TYPE || c_hardbool_type_attr (type))
	/* Although the types are compatible, we may require a
	   conversion.  */
	inside_init = convert (type, inside_init);

      যদি ((code == RECORD_TYPE || code == UNION_TYPE)
	  && !comptypes (TYPE_MAIN_VARIANT (type), TYPE_MAIN_VARIANT (বৃক্ষ_TYPE (inside_init))))
	{
	  error_init (init_loc, "invalid initializer");
	  ফেরত error_mark_গ্রন্থি;
	}

      যদি (require_constant
	  && বৃক্ষ_CODE (inside_init) == COMPOUND_LITERAL_রাশিমালা)
	{
	  /* As an extension, allow initializing objects with static storage
	     duration with compound literals (which are then treated just as
	     the brace enclosed list they contain).  Also allow this for
	     vectors, as we can only assign them with compound literals.  */
	  যদি (flag_isoc99 && code != VECTOR_TYPE)
	    pedwarn_init (init_loc, OPT_Wpedantic, "initializer element "
			  "is not constant");
	  বৃক্ষ decl = COMPOUND_LITERAL_রাশিমালা_DECL (inside_init);
	  inside_init = DECL_INITIAL (decl);
	}

      যদি (code == ARRAY_TYPE && বৃক্ষ_CODE (inside_init) != STRING_CST
	  && বৃক্ষ_CODE (inside_init) != CONSTRUCTOR)
	{
	  error_init (init_loc, "array initialized from non-constant array "
		      "expression");
	  ফেরত error_mark_গ্রন্থি;
	}

      /* Compound expressions can only occur here if -Wpedantic or
	 -pedantic-errors is specified.  In the later case, we always want
	 an error.  In the former case, we simply want a warning.  */
      যদি (require_constant && pedantic
	  && বৃক্ষ_CODE (inside_init) == COMPOUND_রাশিমালা)
	{
	  inside_init
	    = valid_compound_রাশিমালা_initializer (inside_init,
					       বৃক্ষ_TYPE (inside_init));
	  যদি (inside_init == error_mark_গ্রন্থি)
	    error_init (init_loc, "initializer element is not constant");
	  অন্যথা
	    pedwarn_init (init_loc, OPT_Wpedantic,
			  "initializer element is not constant");
	  যদি (flag_pedantic_errors)
	    inside_init = error_mark_গ্রন্থি;
	}
      অন্যথা যদি (require_constant
	       && !initializer_constant_valid_p (inside_init,
						 বৃক্ষ_TYPE (inside_init)))
	{
	  error_init (init_loc, "initializer element is not constant");
	  inside_init = error_mark_গ্রন্থি;
	}
      অন্যথা যদি (require_constant && !maybe_const)
	pedwarn_init (init_loc, OPT_Wpedantic,
		      "initializer element is not a constant expression");
      অন্যথা যদি (require_constexpr)
	check_constexpr_init (init_loc, type, inside_init,
			      int_const_রাশিমালা, arith_const_রাশিমালা);

      /* Added to enable additional -Wsuggest-attribute=format warnings.  */
      যদি (বৃক্ষ_CODE (বৃক্ষ_TYPE (inside_init)) == POINTER_TYPE)
	inside_init = convert_for_assignment (init_loc, UNKNOWN_LOCATION,
					      type, inside_init, origtype,
					      (require_constant
					       ? ic_init_const
					       : ic_init), null_pointer_constant,
					      NULL_বৃক্ষ, NULL_বৃক্ষ, 0);
      যদি (বৃক্ষ_CODE (inside_init) == RAW_তথ্য_CST
	  && c_inhibit_evaluation_warnings == 0
	  && warn_conversion
	  && !TYPE_UNSIGNED (type)
	  && TYPE_PRECISION (type) == CHAR_BIT)
	জন্য (unsigned পূর্ণসংখ্যা i = 0;
	     i < (unsigned) RAW_তথ্য_দৈর্ঘ্য (inside_init); ++i)
	  যদি (RAW_তথ্য_SCHAR_ELT (inside_init, i) < 0)
	    warning_at (init_loc, OPT_Wconversion,
			"conversion from %qT to %qT changes value from "
			"%qd to %qd",
			integer_type_গ্রন্থি, type,
			RAW_তথ্য_UCHAR_ELT (inside_init, i),
			RAW_তথ্য_SCHAR_ELT (inside_init, i));
      ফেরত inside_init;
    }

  /* Handle scalar types, including conversions.  */

  যদি (code == INTEGER_TYPE || code == REAL_TYPE || code == FIXED_POINT_TYPE
      || code == POINTER_TYPE || code == ENUMERAL_TYPE || code == BOOLEAN_TYPE
      || code == COMPLEX_TYPE || code == VECTOR_TYPE || code == NULLPTR_TYPE
      || code == BITINT_TYPE)
    {
      বৃক্ষ unconverted_init = inside_init;
      যদি (বৃক্ষ_CODE (বৃক্ষ_TYPE (init)) == ARRAY_TYPE
	  && (বৃক্ষ_CODE (init) == STRING_CST
	      || বৃক্ষ_CODE (init) == COMPOUND_LITERAL_রাশিমালা))
	inside_init = init = array_to_pointer_conversion (init_loc, init);
      যদি (semantic_type)
	inside_init = build1 (EXCESS_PRECISION_রাশিমালা, semantic_type,
			      inside_init);
      inside_init
	= convert_for_assignment (init_loc, UNKNOWN_LOCATION, type,
				  inside_init, origtype,
				  require_constant ? ic_init_const : ic_init,
				  null_pointer_constant, NULL_বৃক্ষ, NULL_বৃক্ষ,
				  0);

      /* Check to see if we have already given an error message.  */
      যদি (inside_init == error_mark_গ্রন্থি)
	;
      অন্যথা যদি (require_constant && !বৃক্ষ_CONSTANT (inside_init))
	{
	  error_init (init_loc, "initializer element is not constant");
	  inside_init = error_mark_গ্রন্থি;
	}
      অন্যথা যদি (require_constant
	       && !initializer_constant_valid_p (inside_init,
						 বৃক্ষ_TYPE (inside_init)))
	{
	  error_init (init_loc, "initializer element is not computable at "
		      "load time");
	  inside_init = error_mark_গ্রন্থি;
	}
      অন্যথা যদি (require_constant && !maybe_const)
	pedwarn_init (init_loc, OPT_Wpedantic,
		      "initializer element is not a constant expression");
      অন্যথা যদি (require_constexpr)
	check_constexpr_init (init_loc, type, unconverted_init,
			      int_const_রাশিমালা, arith_const_রাশিমালা);

      ফেরত inside_init;
    }

  /* Come here only for records and arrays.  */

  যদি (COMPLETE_TYPE_P (type) && বৃক্ষ_CODE (TYPE_আকার (type)) != INTEGER_CST)
    {
      error_init (init_loc,
		  "variable-sized object may not be initialized except "
		  "with an empty initializer");
      ফেরত error_mark_গ্রন্থি;
    }

  error_init (init_loc, "invalid initializer");
  ফেরত error_mark_গ্রন্থি;
}

/* Handle initializers that use braces.  */

/* Type of object we are accumulating a constructor for.
   This type is always a RECORD_TYPE, UNION_TYPE or ARRAY_TYPE.  */
স্থির বৃক্ষ constructor_type;

/* For a RECORD_TYPE or UNION_TYPE, this is the chain of fields
   left to fill.  */
স্থির বৃক্ষ constructor_fields;

/* For an ARRAY_TYPE, this is the specified index
   at which to store the next element we get.  */
স্থির বৃক্ষ constructor_সূচক;

/* For an ARRAY_TYPE, this is the maximum index.  */
স্থির বৃক্ষ constructor_max_সূচক;

/* For a RECORD_TYPE, this is the first field not yet written out.  */
স্থির বৃক্ষ constructor_unfilled_fields;

/* For an ARRAY_TYPE, this is the index of the first element
   not yet written out.  */
স্থির বৃক্ষ constructor_unfilled_সূচক;

/* In a RECORD_TYPE, the byte index of the next consecutive field.
   This is so we can generate gaps between fields, when appropriate.  */
স্থির বৃক্ষ constructor_bit_সূচক;

/* If we are saving up the elements rather than allocating them,
   this is the list of elements so far (in reverse order,
   most recent first).  */
স্থির vec<constructor_elt, va_gc> *constructor_elements;

/* 1 if constructor should be incrementally stored into a constructor chain,
   0 if all the elements should be kept in AVL tree.  */
স্থির পূর্ণসংখ্যা constructor_incremental;

/* 1 if so far this constructor's elements are all compile-time constants.  */
স্থির পূর্ণসংখ্যা constructor_constant;

/* 1 if so far this constructor's elements are all valid address constants.  */
স্থির পূর্ণসংখ্যা constructor_simple;

/* 1 if this constructor has an element that cannot be part of a
   constant expression.  */
স্থির পূর্ণসংখ্যা constructor_nonconst;

/* 1 if this constructor is erroneous so far.  */
স্থির পূর্ণসংখ্যা constructor_erroneous;

/* 1 if this constructor is the universal zero initializer { 0 }.  */
স্থির পূর্ণসংখ্যা constructor_zeroinit;

/* 1 if this constructor should have padding bits zeroed (C23 {}.  */
স্থির যৌক্তিক constructor_zero_padding_bits;

/* 1 if this constructor is a braced scalar initializer (further nested levels
   of braces are an error).  */
স্থির যৌক্তিক constructor_braced_scalar;

/* Structure for managing pending initializer elements, organized as an
   AVL tree.  */

কাঠামো init_গ্রন্থি
{
  কাঠামো init_গ্রন্থি *বাম, *ডান;
  কাঠামো init_গ্রন্থি *parent;
  পূর্ণসংখ্যা balance;
  বৃক্ষ purpose;
  বৃক্ষ মান;
  বৃক্ষ origtype;
};

/* Tree of pending elements at this constructor level.
   These are elements encountered out of order
   which belong at places we haven't reached yet in actually
   writing the output.
   Will never hold tree nodes across GC runs.  */
স্থির কাঠামো init_গ্রন্থি *constructor_pending_elts;

/* The SPELLING_DEPTH of this constructor.  */
স্থির পূর্ণসংখ্যা constructor_depth;

/* DECL node for which an initializer is being read.
   0 means we are reading a constructor expression
   such as (struct foo) {...}.  */
স্থির বৃক্ষ constructor_decl;

/* Nonzero if there were any member designators in this initializer.  */
স্থির পূর্ণসংখ্যা constructor_designated;

/* Nesting depth of designator list.  */
স্থির পূর্ণসংখ্যা designator_depth;

/* Nonzero if there were diagnosed errors in this designator list.  */
স্থির পূর্ণসংখ্যা designator_erroneous;


/* This stack has a level for each implicit or explicit level of
   structuring in the initializer, including the outermost one.  It
   saves the values of most of the variables above.  */

কাঠামো constructor_range_স্তূপ;

কাঠামো constructor_স্তূপ
{
  কাঠামো constructor_স্তূপ *পরবর্তী;
  বৃক্ষ type;
  বৃক্ষ fields;
  বৃক্ষ সূচক;
  বৃক্ষ max_সূচক;
  বৃক্ষ unfilled_সূচক;
  বৃক্ষ unfilled_fields;
  বৃক্ষ bit_সূচক;
  vec<constructor_elt, va_gc> *elements;
  কাঠামো init_গ্রন্থি *pending_elts;
  পূর্ণসংখ্যা offset;
  পূর্ণসংখ্যা depth;
  /* If value nonzero, this value should replace the entire
     constructor at this level.  */
  কাঠামো c_রাশিমালা replacement_মান;
  কাঠামো constructor_range_স্তূপ *range_স্তূপ;
  অক্ষর constant;
  অক্ষর simple;
  অক্ষর nonconst;
  অক্ষর implicit;
  অক্ষর erroneous;
  অক্ষর outer;
  অক্ষর incremental;
  অক্ষর designated;
  যৌক্তিক zero_padding_bits;
  যৌক্তিক braced_scalar;
  পূর্ণসংখ্যা designator_depth;
};

স্থির কাঠামো constructor_স্তূপ *constructor_স্তূপ;

/* This stack represents designators from some range designator up to
   the last designator in the list.  */

কাঠামো constructor_range_স্তূপ
{
  কাঠামো constructor_range_স্তূপ *পরবর্তী, *পূর্ব;
  কাঠামো constructor_স্তূপ *স্তূপ;
  বৃক্ষ range_start;
  বৃক্ষ সূচক;
  বৃক্ষ range_end;
  বৃক্ষ fields;
};

স্থির কাঠামো constructor_range_স্তূপ *constructor_range_স্তূপ;

/* This stack records separate initializers that are nested.
   Nested initializers can't happen in ANSI C, but GNU C allows them
   in cases like { ... (struct foo) { ... } ... }.  */

কাঠামো initializer_স্তূপ
{
  কাঠামো initializer_স্তূপ *পরবর্তী;
  বৃক্ষ decl;
  কাঠামো constructor_স্তূপ *constructor_স্তূপ;
  কাঠামো constructor_range_স্তূপ *constructor_range_স্তূপ;
  vec<constructor_elt, va_gc> *elements;
  কাঠামো spelling *spelling;
  কাঠামো spelling *spelling_base;
  পূর্ণসংখ্যা spelling_আকার;
  অক্ষর require_constant_মান;
  অক্ষর require_constant_elements;
  অক্ষর require_constexpr_মান;
  অক্ষর designated;
  rich_location *missing_brace_richloc;
};

স্থির কাঠামো initializer_স্তূপ *initializer_স্তূপ;

/* Prepare to parse and output the initializer for variable DECL.  */

শূন্য
start_init (বৃক্ষ decl, বৃক্ষ asmspec_বৃক্ষ ATTRIBUTE_UNUSED,
	    যৌক্তিক init_require_constant, যৌক্তিক init_require_constexpr,
	    rich_location *richloc)
{
  ধ্রুবক অক্ষর *locus;
  কাঠামো initializer_স্তূপ *p = XNEW (কাঠামো initializer_স্তূপ);

  p->decl = constructor_decl;
  p->require_constant_মান = require_constant_মান;
  p->require_constant_elements = require_constant_elements;
  p->require_constexpr_মান = require_constexpr_মান;
  p->constructor_স্তূপ = constructor_স্তূপ;
  p->constructor_range_স্তূপ = constructor_range_স্তূপ;
  p->elements = constructor_elements;
  p->spelling = spelling;
  p->spelling_base = spelling_base;
  p->spelling_আকার = spelling_আকার;
  p->পরবর্তী = initializer_স্তূপ;
  p->missing_brace_richloc = richloc;
  p->designated = constructor_designated;
  initializer_স্তূপ = p;

  constructor_decl = decl;
  constructor_designated = 0;

  require_constant_মান = init_require_constant;
  require_constexpr_মান = init_require_constexpr;
  যদি (decl != NULL_বৃক্ষ && decl != error_mark_গ্রন্থি)
    {
      require_constant_elements
	= ((init_require_constant || (pedantic && !flag_isoc99))
	   /* For a scalar, you can always use any value to initialize,
	      even within braces.  */
	   && AGGREGATE_TYPE_P (বৃক্ষ_TYPE (decl)));
      locus = identifier_to_locale (IDENTIFIER_POINTER (DECL_NAME (decl)));
    }
  অন্যথা
    {
      require_constant_elements = মিথ্যা;
      locus = _("(anonymous)");
    }

  constructor_স্তূপ = 0;
  constructor_range_স্তূপ = 0;

  found_missing_braces = 0;

  spelling_base = 0;
  spelling_আকার = 0;
  RESTORE_SPELLING_DEPTH (0);

  যদি (locus)
    ঠেলো_string (locus);
}

শূন্য
finish_init (শূন্য)
{
  কাঠামো initializer_স্তূপ *p = initializer_স্তূপ;

  /* Free the whole constructor stack of this initializer.  */
  যখন (constructor_স্তূপ)
    {
      কাঠামো constructor_স্তূপ *q = constructor_স্তূপ;
      constructor_স্তূপ = q->পরবর্তী;
      XDELETE (q);
    }

  gcc_assert (!constructor_range_স্তূপ);

  /* Pop back to the data of the outer initializer (if any).  */
  XDELETE (spelling_base);

  constructor_decl = p->decl;
  require_constant_মান = p->require_constant_মান;
  require_constant_elements = p->require_constant_elements;
  require_constexpr_মান = p->require_constexpr_মান;
  constructor_স্তূপ = p->constructor_স্তূপ;
  constructor_designated = p->designated;
  constructor_range_স্তূপ = p->constructor_range_স্তূপ;
  constructor_elements = p->elements;
  spelling = p->spelling;
  spelling_base = p->spelling_base;
  spelling_আকার = p->spelling_আকার;
  initializer_স্তূপ = p->পরবর্তী;
  XDELETE (p);
}

/* Call here when we see the initializer is surrounded by braces.
   This is instead of a call to push_init_level;
   it is matched by a call to pop_init_level.

   TYPE is the type to initialize, for a constructor expression.
   For an initializer for a decl, TYPE is zero.  */

শূন্য
really_start_incremental_init (বৃক্ষ type)
{
  কাঠামো constructor_স্তূপ *p = XNEW (কাঠামো constructor_স্তূপ);

  যদি (type == NULL_বৃক্ষ)
    type = বৃক্ষ_TYPE (constructor_decl);

  যদি (VECTOR_TYPE_P (type)
      && TYPE_VECTOR_OPAQUE (type))
    error ("opaque vector types cannot be initialized");

  p->type = constructor_type;
  p->fields = constructor_fields;
  p->সূচক = constructor_সূচক;
  p->max_সূচক = constructor_max_সূচক;
  p->unfilled_সূচক = constructor_unfilled_সূচক;
  p->unfilled_fields = constructor_unfilled_fields;
  p->bit_সূচক = constructor_bit_সূচক;
  p->elements = constructor_elements;
  p->constant = constructor_constant;
  p->simple = constructor_simple;
  p->nonconst = constructor_nonconst;
  p->erroneous = constructor_erroneous;
  p->pending_elts = constructor_pending_elts;
  p->depth = constructor_depth;
  p->replacement_মান.মান = 0;
  p->replacement_মান.original_code = ERROR_MARK;
  p->replacement_মান.original_type = ফাঁকা;
  p->implicit = 0;
  p->range_স্তূপ = 0;
  p->outer = 0;
  p->incremental = constructor_incremental;
  p->designated = constructor_designated;
  p->zero_padding_bits = constructor_zero_padding_bits;
  p->braced_scalar = constructor_braced_scalar;
  p->designator_depth = designator_depth;
  p->পরবর্তী = 0;
  constructor_স্তূপ = p;

  constructor_constant = 1;
  constructor_simple = 1;
  constructor_nonconst = 0;
  constructor_depth = SPELLING_DEPTH ();
  constructor_elements = ফাঁকা;
  constructor_pending_elts = 0;
  constructor_type = type;
  constructor_incremental = 1;
  constructor_designated = 0;
  constructor_zero_padding_bits = মিথ্যা;
  constructor_zeroinit = 1;
  constructor_braced_scalar = মিথ্যা;
  designator_depth = 0;
  designator_erroneous = 0;

  যদি (RECORD_OR_UNION_TYPE_P (constructor_type))
    {
      constructor_fields = TYPE_FIELDS (constructor_type);
      /* Skip any nameless bit fields at the beginning.  */
      যখন (constructor_fields != NULL_বৃক্ষ
	     && DECL_UNNAMED_BIT_FIELD (constructor_fields))
	constructor_fields = DECL_CHAIN (constructor_fields);

      constructor_unfilled_fields = constructor_fields;
      constructor_bit_সূচক = bitsize_zero_গ্রন্থি;
    }
  অন্যথা যদি (বৃক্ষ_CODE (constructor_type) == ARRAY_TYPE)
    {
      যদি (TYPE_DOMAIN (constructor_type))
	{
	  constructor_max_সূচক
	    = TYPE_MAX_মান (TYPE_DOMAIN (constructor_type));

	  /* Detect non-empty initializations of zero-length arrays.  */
	  যদি (constructor_max_সূচক == NULL_বৃক্ষ
	      && TYPE_আকার (constructor_type))
	    constructor_max_সূচক = integer_minus_one_গ্রন্থি;

	  /* constructor_max_index needs to be an INTEGER_CST.  Attempts
	     to initialize VLAs with a nonempty initializer will cause a
	     proper error; avoid tree checking errors as well by setting a
	     safe value.  */
	  যদি (constructor_max_সূচক
	      && বৃক্ষ_CODE (constructor_max_সূচক) != INTEGER_CST)
	    constructor_max_সূচক = integer_minus_one_গ্রন্থি;

	  constructor_সূচক
	    = convert (bitsizetype,
		       TYPE_MIN_মান (TYPE_DOMAIN (constructor_type)));
	}
      অন্যথা
	{
	  constructor_সূচক = bitsize_zero_গ্রন্থি;
	  constructor_max_সূচক = NULL_বৃক্ষ;
	}

      constructor_unfilled_সূচক = constructor_সূচক;
    }
  অন্যথা যদি (gnu_vector_type_p (constructor_type))
    {
      /* Vectors are like simple fixed-size arrays.  */
      constructor_max_সূচক =
	bitsize_int (TYPE_VECTOR_SUBPARTS (constructor_type) - 1);
      constructor_সূচক = bitsize_zero_গ্রন্থি;
      constructor_unfilled_সূচক = constructor_সূচক;
    }
  অন্যথা
    {
      /* Handle the case of int x = {5}; */
      constructor_fields = constructor_type;
      constructor_unfilled_fields = constructor_type;
      constructor_braced_scalar = সত্য;
    }
}

বাহ্যিক location_t last_init_list_comma;

/* Called when we see an open brace for a nested initializer.  Finish
   off any pending levels with implicit braces.  */
শূন্য
finish_implicit_inits (location_t loc, কাঠামো obstack *braced_init_obstack)
{
  যখন (constructor_স্তূপ->implicit)
    {
      যদি (RECORD_OR_UNION_TYPE_P (constructor_type)
	  && constructor_fields == NULL_বৃক্ষ)
	process_init_element (প্রবেশ_location,
			      বের_করো_init_level (loc, 1, braced_init_obstack,
					      last_init_list_comma),
			      সত্য, braced_init_obstack);
      অন্যথা যদি (বৃক্ষ_CODE (constructor_type) == ARRAY_TYPE
	       && constructor_max_সূচক
	       && বৃক্ষ_int_cst_lt (constructor_max_সূচক,
				   constructor_সূচক))
	process_init_element (প্রবেশ_location,
			      বের_করো_init_level (loc, 1, braced_init_obstack,
					      last_init_list_comma),
			      সত্য, braced_init_obstack);
      অন্যথা
	বিরতি;
    }
}

/* Push down into a subobject, for initialization.
   If this is for an explicit set of braces, IMPLICIT is 0.
   If it is because the next element belongs at a lower level,
   IMPLICIT is 1 (or 2 if the push is because of designator list).  */

শূন্য
ঠেলো_init_level (location_t loc, পূর্ণসংখ্যা implicit,
		 কাঠামো obstack *braced_init_obstack)
{
  কাঠামো constructor_স্তূপ *p;
  বৃক্ষ মান = NULL_বৃক্ষ;

  /* Unless this is an explicit brace, we need to preserve previous
     content if any.  */
  যদি (implicit)
    {
      যদি (RECORD_OR_UNION_TYPE_P (constructor_type) && constructor_fields)
	মান = find_init_member (constructor_fields, braced_init_obstack);
      অন্যথা যদি (বৃক্ষ_CODE (constructor_type) == ARRAY_TYPE)
	মান = find_init_member (constructor_সূচক, braced_init_obstack);
    }

  p = XNEW (কাঠামো constructor_স্তূপ);
  p->type = constructor_type;
  p->fields = constructor_fields;
  p->সূচক = constructor_সূচক;
  p->max_সূচক = constructor_max_সূচক;
  p->unfilled_সূচক = constructor_unfilled_সূচক;
  p->unfilled_fields = constructor_unfilled_fields;
  p->bit_সূচক = constructor_bit_সূচক;
  p->elements = constructor_elements;
  p->constant = constructor_constant;
  p->simple = constructor_simple;
  p->nonconst = constructor_nonconst;
  p->erroneous = constructor_erroneous;
  p->pending_elts = constructor_pending_elts;
  p->depth = constructor_depth;
  p->replacement_মান.মান = NULL_বৃক্ষ;
  p->replacement_মান.original_code = ERROR_MARK;
  p->replacement_মান.original_type = ফাঁকা;
  p->implicit = implicit;
  p->outer = 0;
  p->incremental = constructor_incremental;
  p->designated = constructor_designated;
  p->zero_padding_bits = constructor_zero_padding_bits;
  p->braced_scalar = constructor_braced_scalar;
  p->designator_depth = designator_depth;
  p->পরবর্তী = constructor_স্তূপ;
  p->range_স্তূপ = 0;
  constructor_স্তূপ = p;

  constructor_constant = 1;
  constructor_simple = 1;
  constructor_nonconst = 0;
  constructor_depth = SPELLING_DEPTH ();
  constructor_elements = ফাঁকা;
  constructor_incremental = 1;
  /* If the upper initializer is designated, then mark this as
     designated too to prevent bogus warnings.  */
  constructor_designated = p->designated;
  /* If the upper initializer has padding bits zeroed, that includes
     all nested initializers as well.  */
  constructor_zero_padding_bits = p->zero_padding_bits;
  constructor_braced_scalar = মিথ্যা;
  constructor_pending_elts = 0;
  যদি (!implicit)
    {
      p->range_স্তূপ = constructor_range_স্তূপ;
      constructor_range_স্তূপ = 0;
      designator_depth = 0;
      designator_erroneous = 0;
    }

  /* Don't die if an entire brace-pair level is superfluous
     in the containing level.  */
  যদি (constructor_type == NULL_বৃক্ষ)
    ;
  অন্যথা যদি (RECORD_OR_UNION_TYPE_P (constructor_type))
    {
      /* Don't die if there are extra init elts at the end.  */
      যদি (constructor_fields == NULL_বৃক্ষ)
	constructor_type = NULL_বৃক্ষ;
      অন্যথা
	{
	  constructor_type = বৃক্ষ_TYPE (constructor_fields);
	  ঠেলো_member_name (constructor_fields);
	  constructor_depth++;
	}
    }
  অন্যথা যদি (বৃক্ষ_CODE (constructor_type) == ARRAY_TYPE)
    {
      constructor_type = বৃক্ষ_TYPE (constructor_type);
      ঠেলো_array_bounds (বৃক্ষ_to_uhwi (constructor_সূচক));
      constructor_depth++;
    }

  যদি (constructor_type == NULL_বৃক্ষ)
    {
      error_init (loc, "extra brace group at end of initializer");
      constructor_fields = NULL_বৃক্ষ;
      constructor_unfilled_fields = NULL_বৃক্ষ;
      ফেরত;
    }

  যদি (মান && বৃক্ষ_CODE (মান) == CONSTRUCTOR)
    {
      constructor_constant = বৃক্ষ_CONSTANT (মান);
      constructor_simple = বৃক্ষ_STATIC (মান);
      constructor_nonconst = CONSTRUCTOR_NON_CONST (মান);
      constructor_elements = CONSTRUCTOR_ELTS (মান);
      constructor_zero_padding_bits |= CONSTRUCTOR_ZERO_PADDING_BITS (মান);
      যদি (!vec_safe_is_empty (constructor_elements)
	  && (বৃক্ষ_CODE (constructor_type) == RECORD_TYPE
	      || বৃক্ষ_CODE (constructor_type) == ARRAY_TYPE))
	set_nonincremental_init (braced_init_obstack);
    }

  যদি (implicit == 1)
    {
      found_missing_braces = 1;
      যদি (initializer_স্তূপ->missing_brace_richloc)
	initializer_স্তূপ->missing_brace_richloc->add_fixit_ঢোকাও_before
	  (loc, "{");
    }

  যদি (RECORD_OR_UNION_TYPE_P (constructor_type))
    {
      constructor_fields = TYPE_FIELDS (constructor_type);
      /* Skip any nameless bit fields at the beginning.  */
      যখন (constructor_fields != NULL_বৃক্ষ
	     && DECL_UNNAMED_BIT_FIELD (constructor_fields))
	constructor_fields = DECL_CHAIN (constructor_fields);

      constructor_unfilled_fields = constructor_fields;
      constructor_bit_সূচক = bitsize_zero_গ্রন্থি;
    }
  অন্যথা যদি (gnu_vector_type_p (constructor_type))
    {
      /* Vectors are like simple fixed-size arrays.  */
      constructor_max_সূচক =
	bitsize_int (TYPE_VECTOR_SUBPARTS (constructor_type) - 1);
      constructor_সূচক = bitsize_int (0);
      constructor_unfilled_সূচক = constructor_সূচক;
    }
  অন্যথা যদি (বৃক্ষ_CODE (constructor_type) == ARRAY_TYPE)
    {
      যদি (TYPE_DOMAIN (constructor_type))
	{
	  constructor_max_সূচক
	    = TYPE_MAX_মান (TYPE_DOMAIN (constructor_type));

	  /* Detect non-empty initializations of zero-length arrays.  */
	  যদি (constructor_max_সূচক == NULL_বৃক্ষ
	      && TYPE_আকার (constructor_type))
	    constructor_max_সূচক = integer_minus_one_গ্রন্থি;

	  /* constructor_max_index needs to be an INTEGER_CST.  Attempts
	     to initialize VLAs will cause a proper error; avoid tree
	     checking errors as well by setting a safe value.  */
	  যদি (constructor_max_সূচক
	      && বৃক্ষ_CODE (constructor_max_সূচক) != INTEGER_CST)
	    constructor_max_সূচক = integer_minus_one_গ্রন্থি;

	  constructor_সূচক
	    = convert (bitsizetype,
		       TYPE_MIN_মান (TYPE_DOMAIN (constructor_type)));
	}
      অন্যথা
	constructor_সূচক = bitsize_zero_গ্রন্থি;

      constructor_unfilled_সূচক = constructor_সূচক;
      যদি (মান && বৃক্ষ_CODE (মান) == STRING_CST)
	{
	  /* We need to split the char/wchar array into individual
	     characters, so that we don't have to special case it
	     everywhere.  */
	  set_nonincremental_init_from_string (মান, braced_init_obstack);
	}
    }
  অন্যথা
    {
      যদি (constructor_type != error_mark_গ্রন্থি)
	{
	  যদি (p->braced_scalar)
	    permerror_init (প্রবেশ_location, 0,
			    "braces around scalar initializer");
	  অন্যথা
	    warning_init (প্রবেশ_location, 0,
			  "braces around scalar initializer");
	  constructor_braced_scalar = সত্য;
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

কাঠামো c_রাশিমালা
বের_করো_init_level (location_t loc, পূর্ণসংখ্যা implicit,
		কাঠামো obstack *braced_init_obstack,
		location_t ঢোকাও_before)
{
  কাঠামো constructor_স্তূপ *p;
  কাঠামো c_রাশিমালা ret;
  ret.মান = NULL_বৃক্ষ;
  ret.original_code = ERROR_MARK;
  ret.original_type = ফাঁকা;
  ret.m_decimal = 0;

  যদি (implicit == 0)
    {
      /* When we come to an explicit close brace,
	 pop any inner levels that didn't have explicit braces.  */
      যখন (constructor_স্তূপ->implicit)
	process_init_element (প্রবেশ_location,
			      বের_করো_init_level (loc, 1, braced_init_obstack,
					      ঢোকাও_before),
			      সত্য, braced_init_obstack);
      gcc_assert (!constructor_range_স্তূপ);
    }
  অন্যথা
    যদি (initializer_স্তূপ->missing_brace_richloc)
      initializer_স্তূপ->missing_brace_richloc->add_fixit_ঢোকাও_before
	(ঢোকাও_before, "}");

  /* Now output all pending elements.  */
  constructor_incremental = 1;
  output_pending_init_elements (1, braced_init_obstack);

  p = constructor_স্তূপ;

  /* Error for initializing a flexible array member.  */
  যদি (constructor_type && constructor_fields
      && flexible_array_member_type_p (constructor_type))
    {
      /* Silently discard empty initializations.  The parser will
	 already have pedwarned for empty brackets for C17 and earlier.  */
      যদি (integer_zerop (constructor_unfilled_সূচক))
	constructor_type = NULL_বৃক্ষ;
      যদি (constructor_type || flag_isoc23)
	{
	  gcc_assert (!constructor_type || !TYPE_আকার (constructor_type));

	  যদি (constructor_depth <= 2)
	    pedwarn_init (loc, OPT_Wpedantic,
			  "initialization of a flexible array member");
	  অন্যথা যদি (constructor_type)
	    error_init (loc, "initialization of flexible array member "
			     "in a nested context");
	  অন্যথা
	    pedwarn_init (loc, OPT_Wpedantic,
			  "initialization of flexible array member "
			  "in a nested context");

	  /* We have already issued an error message for the existence
	     of a flexible array member not at the end of the structure.
	     Discard the initializer so that we do not die later.  */
	  যদি (constructor_type
	      && DECL_CHAIN (constructor_fields) != NULL_বৃক্ষ
	      && (!p->type || বৃক্ষ_CODE (p->type) != UNION_TYPE))
	    constructor_type = NULL_বৃক্ষ;
	}
    }

  নির্বাচন (vec_safe_দৈর্ঘ্য (constructor_elements))
    {
    ক্ষেত্র 0:
      /* Initialization with { } counts as zeroinit.  */
      constructor_zeroinit = 1;
      বিরতি;
    ক্ষেত্র 1:
      /* This might be zeroinit as well.  */
      যদি (integer_zerop ((*constructor_elements)[0].মান))
	constructor_zeroinit = 1;
      বিরতি;
    পূর্বনির্ধারিত:
      /* If the constructor has more than one element, it can't be { 0 }.  */
      constructor_zeroinit = 0;
      বিরতি;
    }

  /* Warn when some structs are initialized with direct aggregation.  */
  যদি (!implicit && found_missing_braces && warn_missing_braces
      && !constructor_zeroinit)
    {
      gcc_assert (initializer_স্তূপ->missing_brace_richloc);
      warning_at (initializer_স্তূপ->missing_brace_richloc,
		  OPT_Wmissing_braces,
		  "missing braces around initializer");
    }

  /* Warn when some struct elements are implicitly initialized to zero.  */
  যদি (warn_missing_field_initializers
      && constructor_type
      && বৃক্ষ_CODE (constructor_type) == RECORD_TYPE
      && constructor_unfilled_fields)
    {
	/* Do not warn for flexible array members or zero-length arrays.  */
	যখন (constructor_unfilled_fields
	       && (!DECL_আকার (constructor_unfilled_fields)
		   || integer_zerop (DECL_আকার (constructor_unfilled_fields))))
	  constructor_unfilled_fields = DECL_CHAIN (constructor_unfilled_fields);

	যদি (constructor_unfilled_fields
	    /* Do not warn if this level of the initializer uses member
	       designators; it is likely to be deliberate.  */
	    && !constructor_designated
	    /* Do not warn about initializing with { 0 } or with { }.  */
	    && !constructor_zeroinit)
	  {
	    যদি (warning_at (প্রবেশ_location, OPT_Wmissing_field_initializers,
			    "missing initializer for field %qD of %qT",
			    constructor_unfilled_fields,
			    constructor_type))
	      inform (DECL_SOURCE_LOCATION (constructor_unfilled_fields),
		      "%qD declared here", constructor_unfilled_fields);
	  }
    }

  /* Pad out the end of the structure.  */
  যদি (p->replacement_মান.মান)
    /* If this closes a superfluous brace pair,
       just pass out the element between them.  */
    ret = p->replacement_মান;
  অন্যথা যদি (constructor_type == NULL_বৃক্ষ)
    ;
  অন্যথা যদি (!RECORD_OR_UNION_TYPE_P (constructor_type)
	   && বৃক্ষ_CODE (constructor_type) != ARRAY_TYPE
	   && !gnu_vector_type_p (constructor_type))
    {
      /* A nonincremental scalar initializer--just return
	 the element, after verifying there is just one.
         Empty scalar initializers are supported in C23.  */
      যদি (vec_safe_is_empty (constructor_elements))
	{
	  যদি (constructor_erroneous || constructor_type == error_mark_গ্রন্থি)
	    ret.মান = error_mark_গ্রন্থি;
	  অন্যথা যদি (বৃক্ষ_CODE (constructor_type) == FUNCTION_TYPE)
	    {
	      error_init (loc, "invalid initializer");
	      ret.মান = error_mark_গ্রন্থি;
	    }
	  অন্যথা যদি (বৃক্ষ_CODE (constructor_type) == POINTER_TYPE)
	    /* Ensure this is a null pointer constant in the case of a
	       'constexpr' object initialized with {}.  */
	    ret.মান = build_zero_cst (ptr_type_গ্রন্থি);
	  অন্যথা
	    ret.মান = build_zero_cst (constructor_type);
	}
      অন্যথা যদি (vec_safe_দৈর্ঘ্য (constructor_elements) != 1)
	{
	  error_init (loc, "extra elements in scalar initializer");
	  ret.মান = (*constructor_elements)[0].মান;
	}
      অন্যথা
	ret.মান = (*constructor_elements)[0].মান;
    }
  অন্যথা
    {
      যদি (constructor_erroneous)
	ret.মান = error_mark_গ্রন্থি;
      অন্যথা
	{
	  ret.মান = build_constructor (constructor_type,
					 constructor_elements);
	  যদি (constructor_constant)
	    বৃক্ষ_CONSTANT (ret.মান) = 1;
	  যদি (constructor_constant && constructor_simple)
	    বৃক্ষ_STATIC (ret.মান) = 1;
	  যদি (constructor_nonconst)
	    CONSTRUCTOR_NON_CONST (ret.মান) = 1;
	  যদি (constructor_zero_padding_bits)
	    CONSTRUCTOR_ZERO_PADDING_BITS (ret.মান) = 1;
	}
    }

  যদি (ret.মান && বৃক্ষ_CODE (ret.মান) != CONSTRUCTOR)
    {
      যদি (constructor_nonconst)
	ret.original_code = C_MAYBE_CONST_রাশিমালা;
      অন্যথা যদি (ret.original_code == C_MAYBE_CONST_রাশিমালা)
	ret.original_code = ERROR_MARK;
    }

  constructor_type = p->type;
  constructor_fields = p->fields;
  constructor_সূচক = p->সূচক;
  constructor_max_সূচক = p->max_সূচক;
  constructor_unfilled_সূচক = p->unfilled_সূচক;
  constructor_unfilled_fields = p->unfilled_fields;
  constructor_bit_সূচক = p->bit_সূচক;
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
  যদি (!p->implicit)
    constructor_range_স্তূপ = p->range_স্তূপ;
  RESTORE_SPELLING_DEPTH (constructor_depth);

  constructor_স্তূপ = p->পরবর্তী;
  XDELETE (p);

  যদি (ret.মান == NULL_বৃক্ষ && constructor_স্তূপ == 0)
    ret.মান = error_mark_গ্রন্থি;
  ফেরত ret;
}

/* Common handling for both array range and field name designators.
   ARRAY argument is nonzero for array ranges.  Returns false for success.  */

স্থির যৌক্তিক
set_designator (location_t loc, যৌক্তিক array,
		কাঠামো obstack *braced_init_obstack)
{
  বৃক্ষ subtype;
  গণনা বৃক্ষ_code subcode;

  /* Don't die if an entire brace-pair level is superfluous
     in the containing level, or for an erroneous type.  */
  যদি (constructor_type == NULL_বৃক্ষ || constructor_type == error_mark_গ্রন্থি)
    ফেরত সত্য;

  /* If there were errors in this designator list already, bail out
     silently.  */
  যদি (designator_erroneous)
    ফেরত সত্য;

  /* Likewise for an initializer for a variable-size type.  Those are
     diagnosed in the parser, except for empty initializer braces.  */
  যদি (COMPLETE_TYPE_P (constructor_type)
      && বৃক্ষ_CODE (TYPE_আকার (constructor_type)) != INTEGER_CST)
    ফেরত সত্য;

  যদি (!designator_depth)
    {
      gcc_assert (!constructor_range_স্তূপ);

      /* Designator list starts at the level of closest explicit
	 braces.  */
      যখন (constructor_স্তূপ->implicit)
	process_init_element (প্রবেশ_location,
			      বের_করো_init_level (loc, 1, braced_init_obstack,
					      last_init_list_comma),
			      সত্য, braced_init_obstack);
      constructor_designated = 1;
      ফেরত মিথ্যা;
    }

  নির্বাচন (বৃক্ষ_CODE (constructor_type))
    {
    ক্ষেত্র  RECORD_TYPE:
    ক্ষেত্র  UNION_TYPE:
      subtype = বৃক্ষ_TYPE (constructor_fields);
      যদি (subtype != error_mark_গ্রন্থি)
	subtype = TYPE_MAIN_VARIANT (subtype);
      বিরতি;
    ক্ষেত্র ARRAY_TYPE:
      subtype = TYPE_MAIN_VARIANT (বৃক্ষ_TYPE (constructor_type));
      বিরতি;
    পূর্বনির্ধারিত:
      gcc_unreachable ();
    }

  subcode = বৃক্ষ_CODE (subtype);
  যদি (array && subcode != ARRAY_TYPE)
    {
      error_init (loc, "array index in non-array initializer");
      ফেরত সত্য;
    }
  অন্যথা যদি (!array && subcode != RECORD_TYPE && subcode != UNION_TYPE)
    {
      error_init (loc, "field name not in record or union initializer");
      ফেরত সত্য;
    }

  constructor_designated = 1;
  finish_implicit_inits (loc, braced_init_obstack);
  ঠেলো_init_level (loc, 2, braced_init_obstack);
  ফেরত মিথ্যা;
}

/* If there are range designators in designator list, push a new designator
   to constructor_range_stack.  RANGE_END is end of such stack range or
   NULL_TREE if there is no range designator at this level.  */

স্থির শূন্য
ঠেলো_range_স্তূপ (বৃক্ষ range_end, কাঠামো obstack * braced_init_obstack)
{
  কাঠামো constructor_range_স্তূপ *p;

  p = (কাঠামো constructor_range_স্তূপ *)
    obstack_alloc (braced_init_obstack,
		   আকার (কাঠামো constructor_range_স্তূপ));
  p->পূর্ব = constructor_range_স্তূপ;
  p->পরবর্তী = 0;
  p->fields = constructor_fields;
  p->range_start = constructor_সূচক;
  p->সূচক = constructor_সূচক;
  p->স্তূপ = constructor_স্তূপ;
  p->range_end = range_end;
  যদি (constructor_range_স্তূপ)
    constructor_range_স্তূপ->পরবর্তী = p;
  constructor_range_স্তূপ = p;
}

/* Within an array initializer, specify the next index to be initialized.
   FIRST is that index.  If LAST is nonzero, then initialize a range
   of indices, running from FIRST through LAST.  */

শূন্য
set_init_সূচক (location_t loc, বৃক্ষ first, বৃক্ষ last,
		কাঠামো obstack *braced_init_obstack)
{
  যদি (set_designator (loc, সত্য, braced_init_obstack))
    ফেরত;

  designator_erroneous = 1;

  যদি (!INTEGRAL_TYPE_P (বৃক্ষ_TYPE (first))
      || (last && !INTEGRAL_TYPE_P (বৃক্ষ_TYPE (last))))
    {
      error_init (loc, "array index in initializer not of integer type");
      ফেরত;
    }

  যদি (বৃক্ষ_CODE (first) != INTEGER_CST)
    {
      first = c_fully_fold (first, মিথ্যা, ফাঁকা);
      যদি (বৃক্ষ_CODE (first) == INTEGER_CST)
	pedwarn_init (loc, OPT_Wpedantic,
		      "array index in initializer is not "
		      "an integer constant expression");
    }

  যদি (last && বৃক্ষ_CODE (last) != INTEGER_CST)
    {
      last = c_fully_fold (last, মিথ্যা, ফাঁকা);
      যদি (বৃক্ষ_CODE (last) == INTEGER_CST)
	pedwarn_init (loc, OPT_Wpedantic,
		      "array index in initializer is not "
		      "an integer constant expression");
    }

  যদি (বৃক্ষ_CODE (first) != INTEGER_CST)
    error_init (loc, "nonconstant array index in initializer");
  অন্যথা যদি (last != NULL_বৃক্ষ && বৃক্ষ_CODE (last) != INTEGER_CST)
    error_init (loc, "nonconstant array index in initializer");
  অন্যথা যদি (বৃক্ষ_CODE (constructor_type) != ARRAY_TYPE)
    error_init (loc, "array index in non-array initializer");
  অন্যথা যদি (বৃক্ষ_int_cst_sgn (first) == -1)
    error_init (loc, "array index in initializer exceeds array bounds");
  অন্যথা যদি (constructor_max_সূচক
	   && বৃক্ষ_int_cst_lt (constructor_max_সূচক, first))
    error_init (loc, "array index in initializer exceeds array bounds");
  অন্যথা
    {
      constant_expression_warning (first);
      যদি (last)
	constant_expression_warning (last);
      constructor_সূচক = convert (bitsizetype, first);
      যদি (বৃক্ষ_int_cst_lt (constructor_সূচক, first))
	{
	  constructor_সূচক = copy_গ্রন্থি (constructor_সূচক);
	  বৃক্ষ_OVERFLOW (constructor_সূচক) = 1;
	}

      যদি (last)
	{
	  যদি (বৃক্ষ_int_cst_equal (first, last))
	    last = NULL_বৃক্ষ;
	  অন্যথা যদি (বৃক্ষ_int_cst_lt (last, first))
	    {
	      error_init (loc, "empty index range in initializer");
	      last = NULL_বৃক্ষ;
	    }
	  অন্যথা
	    {
	      last = convert (bitsizetype, last);
	      যদি (constructor_max_সূচক != NULL_বৃক্ষ
		  && বৃক্ষ_int_cst_lt (constructor_max_সূচক, last))
		{
		  error_init (loc, "array index range in initializer exceeds "
			      "array bounds");
		  last = NULL_বৃক্ষ;
		}
	    }
	}

      designator_depth++;
      designator_erroneous = 0;
      যদি (constructor_range_স্তূপ || last)
	ঠেলো_range_স্তূপ (last, braced_init_obstack);
    }
}

/* Within a struct initializer, specify the next field to be initialized.  */

শূন্য
set_init_label (location_t loc, বৃক্ষ fieldname, location_t fieldname_loc,
		কাঠামো obstack *braced_init_obstack)
{
  বৃক্ষ field;

  যদি (set_designator (loc, মিথ্যা, braced_init_obstack))
    ফেরত;

  designator_erroneous = 1;

  যদি (!RECORD_OR_UNION_TYPE_P (constructor_type))
    {
      error_init (loc, "field name not in record or union initializer");
      ফেরত;
    }

  field = lookup_field (constructor_type, fieldname);

  যদি (field == NULL_বৃক্ষ)
    {
      বৃক্ষ guessed_id = lookup_field_fuzzy (constructor_type, fieldname);
      যদি (guessed_id)
	{
	  gcc_rich_location rich_loc (fieldname_loc);
	  rich_loc.add_fixit_misspelled_id (fieldname_loc, guessed_id);
	  error_at (&rich_loc,
		    "%qT has no member named %qE; did you mean %qE?",
		    constructor_type, fieldname, guessed_id);
	}
      অন্যথা
	error_at (fieldname_loc, "%qT has no member named %qE",
		  constructor_type, fieldname);
    }
  অন্যথা
    করো
      {
	constructor_fields = বৃক্ষ_মান (field);
	designator_depth++;
	designator_erroneous = 0;
	যদি (constructor_range_স্তূপ)
	  ঠেলো_range_স্তূপ (NULL_বৃক্ষ, braced_init_obstack);
	field = বৃক্ষ_CHAIN (field);
	যদি (field)
	  {
	    যদি (set_designator (loc, মিথ্যা, braced_init_obstack))
	      ফেরত;
	  }
      }
    যখন (field != NULL_বৃক্ষ);
}

/* Helper function for add_pending_init.  Find inorder successor of P
   in AVL tree.  */
স্থির কাঠামো init_গ্রন্থি *
init_গ্রন্থি_successor (কাঠামো init_গ্রন্থি *p)
{
  কাঠামো init_গ্রন্থি *r;
  যদি (p->ডান)
    {
      r = p->ডান;
      যখন (r->বাম)
	r = r->বাম;
      ফেরত r;
    }
  r = p->parent;
  যখন (r && p == r->ডান)
    {
      p = r;
      r = r->parent;
    }
  ফেরত r;
}

/* Add a new initializer to the tree of pending initializers.  PURPOSE
   identifies the initializer, either array index or field in a structure.
   VALUE is the value of that index or field.  If ORIGTYPE is not
   NULL_TREE, it is the original type of VALUE.

   IMPLICIT is true if value comes from pop_init_level (1),
   the new initializer has been merged with the existing one
   and thus no warnings should be emitted about overriding an
   existing initializer.  */

স্থির শূন্য
add_pending_init (location_t loc, বৃক্ষ purpose, বৃক্ষ মান, বৃক্ষ origtype,
		  যৌক্তিক implicit, কাঠামো obstack *braced_init_obstack)
{
  কাঠামো init_গ্রন্থি *p, **q, *r;

  q = &constructor_pending_elts;
  p = 0;

  যদি (বৃক্ষ_CODE (constructor_type) == ARRAY_TYPE)
    {
      যখন (*q != 0)
	{
	  p = *q;
	  যদি (বৃক্ষ_int_cst_lt (purpose, p->purpose))
	    q = &p->বাম;
	  অন্যথা যদি (বৃক্ষ_int_cst_lt (p->purpose, purpose))
	    {
	      যদি (বৃক্ষ_CODE (p->মান) != RAW_তথ্য_CST
		  || (p->ডান
		      && বৃক্ষ_int_cst_le (p->ডান->purpose, purpose)))
		q = &p->ডান;
	      অন্যথা
		{
		  widest_int pp = wi::to_widest (p->purpose);
		  widest_int pw = wi::to_widest (purpose);
		  যদি (pp + RAW_তথ্য_দৈর্ঘ্য (p->মান) <= pw)
		    q = &p->ডান;
		  অন্যথা
		    {
		      /* Override which should split the old RAW_DATA_CST
			 into 2 or 3 pieces.  */
		      যদি (!implicit && warn_override_init)
			warning_init (loc, OPT_Woverride_init,
				      "initialized field overwritten");
		      unsigned HOST_WIDE_INT start = (pw - pp).to_uhwi ();
		      unsigned HOST_WIDE_INT len = 1;
		      যদি (বৃক্ষ_CODE (মান) == RAW_তথ্য_CST)
			len = RAW_তথ্য_দৈর্ঘ্য (মান);
		      unsigned HOST_WIDE_INT end = 0;
		      unsigned plen = RAW_তথ্য_দৈর্ঘ্য (p->মান);
		      gcc_checking_assert (start < plen && start);
		      যদি (plen - start > len)
			end = plen - start - len;
		      বৃক্ষ v = p->মান;
		      বৃক্ষ origtype = p->origtype;
		      যদি (start == 1)
			p->মান = build_int_cst (বৃক্ষ_TYPE (v),
						  RAW_তথ্য_UCHAR_ELT (v, 0));
		      অন্যথা
			{
			  p->মান = v;
			  যদি (end > 1)
			    v = copy_গ্রন্থি (v);
			  RAW_তথ্য_দৈর্ঘ্য (p->মান) = start;
			}
		      যদি (end)
			{
			  বৃক্ষ epurpose
			    = আকার_binop (PLUS_রাশিমালা, purpose,
					  bitsize_int (len));
			  যদি (end > 1)
			    {
			      RAW_তথ্য_দৈর্ঘ্য (v) -= plen - end;
			      RAW_তথ্য_POINTER (v) += plen - end;
			    }
			  অন্যথা
			    v = build_int_cst (বৃক্ষ_TYPE (v),
					       RAW_তথ্য_UCHAR_ELT (v, plen
								      - end));
			  add_pending_init (loc, epurpose, v, origtype,
					    implicit, braced_init_obstack);
			}
		      q = &constructor_pending_elts;
		      চালু;
		    }
		}
	    }
	  অন্যথা
	    {
	      যদি (বৃক্ষ_CODE (p->মান) == RAW_তথ্য_CST
		  && (RAW_তথ্য_দৈর্ঘ্য (p->মান)
		      > (বৃক্ষ_CODE (মান) == RAW_তথ্য_CST
			 ? RAW_তথ্য_দৈর্ঘ্য (মান) : 1)))
		{
		  /* Override which should split the old RAW_DATA_CST
		     into 2 pieces.  */
		  যদি (!implicit && warn_override_init)
		    warning_init (loc, OPT_Woverride_init,
				  "initialized field overwritten");
		  unsigned HOST_WIDE_INT len = 1;
		  যদি (বৃক্ষ_CODE (মান) == RAW_তথ্য_CST)
		    len = RAW_তথ্য_দৈর্ঘ্য (মান);
		  যদি ((unsigned) RAW_তথ্য_দৈর্ঘ্য (p->মান) > len + 1)
		    {
		      RAW_তথ্য_দৈর্ঘ্য (p->মান) -= len;
		      RAW_তথ্য_POINTER (p->মান) += len;
		    }
		  অন্যথা
		    {
		      unsigned পূর্ণসংখ্যা l = RAW_তথ্য_দৈর্ঘ্য (p->মান) - 1;
		      p->মান
			= build_int_cst (বৃক্ষ_TYPE (p->মান),
					 RAW_তথ্য_UCHAR_ELT (p->মান, l));
		    }
		  p->purpose = আকার_binop (PLUS_রাশিমালা, p->purpose,
					   bitsize_int (len));
		  চালু;
		}
	      যদি (বৃক্ষ_CODE (মান) == RAW_তথ্য_CST)
		{
		handle_raw_তথ্য:
		  /* RAW_DATA_CST value might overlap various further
		     prior initval entries.  Find out how many.  */
		  unsigned cnt = 0;
		  widest_int w
		    = wi::to_widest (purpose) + RAW_তথ্য_দৈর্ঘ্য (মান);
		  কাঠামো init_গ্রন্থি *r = p, *last = ফাঁকা;
		  যৌক্তিক override_init = warn_override_init;
		  যখন ((r = init_গ্রন্থি_successor (r))
			 && wi::to_widest (r->purpose) < w)
		    {
		      ++cnt;
		      যদি (বৃক্ষ_SIDE_EFFECTS (r->মান))
			warning_init (loc, OPT_Woverride_init_side_effects,
				      "initialized field with side-effects "
				      "overwritten");
		      অন্যথা যদি (override_init)
			{
			  warning_init (loc, OPT_Woverride_init,
					"initialized field overwritten");
			  override_init = মিথ্যা;
			}
		      last = r;
		    }
		  যদি (cnt)
		    {
		      যদি (বৃক্ষ_CODE (last->মান) == RAW_তথ্য_CST
			  && (wi::to_widest (last->purpose)
			      + RAW_তথ্য_দৈর্ঘ্য (last->মান) > w))
			{
			  /* The last overlapping prior initval overlaps
			     only partially.  Shrink it and decrease cnt.  */
			  unsigned পূর্ণসংখ্যা l = (wi::to_widest (last->purpose)
					    + RAW_তথ্য_দৈর্ঘ্য (last->মান)
					    - w).to_uhwi ();
			  --cnt;
			  RAW_তথ্য_দৈর্ঘ্য (last->মান) -= l;
			  RAW_তথ্য_POINTER (last->মান) += l;
			  যদি (RAW_তথ্য_দৈর্ঘ্য (last->মান) == 1)
			    last->মান
			      = build_int_cst (বৃক্ষ_TYPE (last->মান),
					       RAW_তথ্য_UCHAR_ELT (last->মান,
								   0));
			  last->purpose
			    = আকার_binop (PLUS_রাশিমালা, last->purpose,
					  bitsize_int (l));
			}
		      /* Instead of deleting cnt nodes from the AVL tree
			 and rebalancing, peel of last cnt bytes from the
			 RAW_DATA_CST.  Overriding thousands of previously
			 initialized array elements with #embed needs to work,
			 but doesn't need to be super efficient.  */
		      gcc_checking_assert ((unsigned) RAW_তথ্য_দৈর্ঘ্য (মান)
					   > cnt);
		      RAW_তথ্য_দৈর্ঘ্য (মান) -= cnt;
		      ধ্রুবক unsigned অক্ষর *s
			= &RAW_তথ্য_UCHAR_ELT (মান, RAW_তথ্য_দৈর্ঘ্য (মান));
		      unsigned পূর্ণসংখ্যা o = RAW_তথ্য_দৈর্ঘ্য (মান);
		      জন্য (r = p; cnt--; ++o, ++s)
			{
			  r = init_গ্রন্থি_successor (r);
			  r->purpose = আকার_binop (PLUS_রাশিমালা, purpose,
						   bitsize_int (o));
			  r->মান = build_int_cst (বৃক্ষ_TYPE (মান), *s);
			  r->origtype = origtype;
			}
		      যদি (RAW_তথ্য_দৈর্ঘ্য (মান) == 1)
			মান = build_int_cst (বৃক্ষ_TYPE (মান),
					       RAW_তথ্য_UCHAR_ELT (মান, 0));
		    }
		}
	      যদি (!implicit)
		{
		  যদি (বৃক্ষ_SIDE_EFFECTS (p->মান))
		    warning_init (loc, OPT_Woverride_init_side_effects,
				  "initialized field with side-effects "
				  "overwritten");
		  অন্যথা যদি (warn_override_init)
		    warning_init (loc, OPT_Woverride_init,
				  "initialized field overwritten");
		}
	      p->মান = মান;
	      p->origtype = origtype;
	      ফেরত;
	    }
	}
      যদি (বৃক্ষ_CODE (মান) == RAW_তথ্য_CST && p)
	{
	  কাঠামো init_গ্রন্থি *r;
	  যদি (q == &p->বাম)
	    r = p;
	  অন্যথা
	    r = init_গ্রন্থি_successor (p);
	  যদি (r && wi::to_widest (r->purpose) < (wi::to_widest (purpose)
						 + RAW_তথ্য_দৈর্ঘ্য (মান)))
	    {
	      /* Overlap with at least one prior initval in the range but
		 not at the start.  */
	      p = r;
	      p->purpose = purpose;
	      যাও handle_raw_তথ্য;
	    }
	}
    }
  অন্যথা
    {
      বৃক্ষ bitpos;

      bitpos = bit_position (purpose);
      যখন (*q != ফাঁকা)
	{
	  p = *q;
	  যদি (বৃক্ষ_int_cst_lt (bitpos, bit_position (p->purpose)))
	    q = &p->বাম;
	  অন্যথা যদি (p->purpose != purpose)
	    q = &p->ডান;
	  অন্যথা
	    {
	      যদি (!implicit)
		{
		  যদি (বৃক্ষ_SIDE_EFFECTS (p->মান))
		    warning_init (loc, OPT_Woverride_init_side_effects,
				  "initialized field with side-effects "
				  "overwritten");
		  অন্যথা যদি (warn_override_init)
		    warning_init (loc, OPT_Woverride_init,
				  "initialized field overwritten");
		}
	      p->মান = মান;
	      p->origtype = origtype;
	      ফেরত;
	    }
	}
    }

  r = (কাঠামো init_গ্রন্থি *) obstack_alloc (braced_init_obstack,
					  আকার (কাঠামো init_গ্রন্থি));
  r->purpose = purpose;
  r->মান = মান;
  r->origtype = origtype;

  *q = r;
  r->parent = p;
  r->বাম = 0;
  r->ডান = 0;
  r->balance = 0;

  যখন (p)
    {
      কাঠামো init_গ্রন্থি *s;

      যদি (r == p->বাম)
	{
	  যদি (p->balance == 0)
	    p->balance = -1;
	  অন্যথা যদি (p->balance < 0)
	    {
	      যদি (r->balance < 0)
		{
		  /* L rotation.  */
		  p->বাম = r->ডান;
		  যদি (p->বাম)
		    p->বাম->parent = p;
		  r->ডান = p;

		  p->balance = 0;
		  r->balance = 0;

		  s = p->parent;
		  p->parent = r;
		  r->parent = s;
		  যদি (s)
		    {
		      যদি (s->বাম == p)
			s->বাম = r;
		      অন্যথা
			s->ডান = r;
		    }
		  অন্যথা
		    constructor_pending_elts = r;
		}
	      অন্যথা
		{
		  /* LR rotation.  */
		  কাঠামো init_গ্রন্থি *t = r->ডান;

		  r->ডান = t->বাম;
		  যদি (r->ডান)
		    r->ডান->parent = r;
		  t->বাম = r;

		  p->বাম = t->ডান;
		  যদি (p->বাম)
		    p->বাম->parent = p;
		  t->ডান = p;

		  p->balance = t->balance < 0;
		  r->balance = -(t->balance > 0);
		  t->balance = 0;

		  s = p->parent;
		  p->parent = t;
		  r->parent = t;
		  t->parent = s;
		  যদি (s)
		    {
		      যদি (s->বাম == p)
			s->বাম = t;
		      অন্যথা
			s->ডান = t;
		    }
		  অন্যথা
		    constructor_pending_elts = t;
		}
	      বিরতি;
	    }
	  অন্যথা
	    {
	      /* p->balance == +1; growth of left side balances the node.  */
	      p->balance = 0;
	      বিরতি;
	    }
	}
      অন্যথা /* r == p->right */
	{
	  যদি (p->balance == 0)
	    /* Growth propagation from right side.  */
	    p->balance++;
	  অন্যথা যদি (p->balance > 0)
	    {
	      যদি (r->balance > 0)
		{
		  /* R rotation.  */
		  p->ডান = r->বাম;
		  যদি (p->ডান)
		    p->ডান->parent = p;
		  r->বাম = p;

		  p->balance = 0;
		  r->balance = 0;

		  s = p->parent;
		  p->parent = r;
		  r->parent = s;
		  যদি (s)
		    {
		      যদি (s->বাম == p)
			s->বাম = r;
		      অন্যথা
			s->ডান = r;
		    }
		  অন্যথা
		    constructor_pending_elts = r;
		}
	      অন্যথা /* r->balance == -1 */
		{
		  /* RL rotation */
		  কাঠামো init_গ্রন্থি *t = r->বাম;

		  r->বাম = t->ডান;
		  যদি (r->বাম)
		    r->বাম->parent = r;
		  t->ডান = r;

		  p->ডান = t->বাম;
		  যদি (p->ডান)
		    p->ডান->parent = p;
		  t->বাম = p;

		  r->balance = (t->balance < 0);
		  p->balance = -(t->balance > 0);
		  t->balance = 0;

		  s = p->parent;
		  p->parent = t;
		  r->parent = t;
		  t->parent = s;
		  যদি (s)
		    {
		      যদি (s->বাম == p)
			s->বাম = t;
		      অন্যথা
			s->ডান = t;
		    }
		  অন্যথা
		    constructor_pending_elts = t;
		}
	      বিরতি;
	    }
	  অন্যথা
	    {
	      /* p->balance == -1; growth of right side balances the node.  */
	      p->balance = 0;
	      বিরতি;
	    }
	}

      r = p;
      p = p->parent;
    }
}

/* Build AVL tree from a sorted chain.  */

স্থির শূন্য
set_nonincremental_init (কাঠামো obstack * braced_init_obstack)
{
  unsigned HOST_WIDE_INT ix;
  বৃক্ষ সূচক, মান;

  যদি (বৃক্ষ_CODE (constructor_type) != RECORD_TYPE
      && বৃক্ষ_CODE (constructor_type) != ARRAY_TYPE)
    ফেরত;

  FOR_EACH_CONSTRUCTOR_ELT (constructor_elements, ix, সূচক, মান)
    add_pending_init (প্রবেশ_location, সূচক, মান, NULL_বৃক্ষ, সত্য,
		      braced_init_obstack);
  constructor_elements = ফাঁকা;
  যদি (বৃক্ষ_CODE (constructor_type) == RECORD_TYPE)
    {
      constructor_unfilled_fields = TYPE_FIELDS (constructor_type);
      /* Skip any nameless bit fields at the beginning.  */
      যখন (constructor_unfilled_fields != NULL_বৃক্ষ
	     && DECL_UNNAMED_BIT_FIELD (constructor_unfilled_fields))
	constructor_unfilled_fields = বৃক্ষ_CHAIN (constructor_unfilled_fields);

    }
  অন্যথা যদি (বৃক্ষ_CODE (constructor_type) == ARRAY_TYPE)
    {
      যদি (TYPE_DOMAIN (constructor_type))
	constructor_unfilled_সূচক
	  = convert (bitsizetype,
		     TYPE_MIN_মান (TYPE_DOMAIN (constructor_type)));
      অন্যথা
	constructor_unfilled_সূচক = bitsize_zero_গ্রন্থি;
    }
  constructor_incremental = 0;
}

/* Build AVL tree from a string constant.  */

স্থির শূন্য
set_nonincremental_init_from_string (বৃক্ষ str,
				     কাঠামো obstack * braced_init_obstack)
{
  বৃক্ষ মান, purpose, type;
  HOST_WIDE_INT val[2];
  ধ্রুবক অক্ষর *p, *end;
  পূর্ণসংখ্যা byte, wchar_bytes, charwidth, bitpos;

  gcc_assert (বৃক্ষ_CODE (constructor_type) == ARRAY_TYPE);

  wchar_bytes = TYPE_PRECISION (বৃক্ষ_TYPE (বৃক্ষ_TYPE (str))) / BITS_PER_UNIT;
  charwidth = TYPE_PRECISION (char_type_গ্রন্থি);
  gcc_assert ((আকার_t) wchar_bytes * charwidth
	      <= ARRAY_আকার (val) * HOST_BITS_PER_WIDE_INT);
  type = বৃক্ষ_TYPE (constructor_type);
  p = বৃক্ষ_STRING_POINTER (str);
  end = p + বৃক্ষ_STRING_দৈর্ঘ্য (str);

  জন্য (purpose = bitsize_zero_গ্রন্থি;
       p < end
       && !(constructor_max_সূচক
	    && বৃক্ষ_int_cst_lt (constructor_max_সূচক, purpose));
       purpose = আকার_binop (PLUS_রাশিমালা, purpose, bitsize_one_গ্রন্থি))
    {
      যদি (wchar_bytes == 1)
	{
	  val[0] = (unsigned অক্ষর) *p++;
	  val[1] = 0;
	}
      অন্যথা
	{
	  val[1] = 0;
	  val[0] = 0;
	  জন্য (byte = 0; byte < wchar_bytes; byte++)
	    {
	      যদি (BYTES_BIG_ENDIAN)
		bitpos = (wchar_bytes - byte - 1) * charwidth;
	      অন্যথা
		bitpos = byte * charwidth;
	      val[bitpos / HOST_BITS_PER_WIDE_INT]
		|= ((unsigned HOST_WIDE_INT) ((unsigned অক্ষর) *p++))
		   << (bitpos % HOST_BITS_PER_WIDE_INT);
	    }
	}

      যদি (!TYPE_UNSIGNED (type))
	{
	  bitpos = ((wchar_bytes - 1) * charwidth) + HOST_BITS_PER_CHAR;
	  যদি (bitpos < HOST_BITS_PER_WIDE_INT)
	    {
	      যদি (val[0] & (HOST_WIDE_INT_1 << (bitpos - 1)))
		{
		  val[0] |= HOST_WIDE_INT_M1U << bitpos;
		  val[1] = -1;
		}
	    }
	  অন্যথা যদি (bitpos == HOST_BITS_PER_WIDE_INT)
	    {
	      যদি (val[0] < 0)
		val[1] = -1;
	    }
	  অন্যথা যদি (val[1] & (HOST_WIDE_INT_1
			     << (bitpos - 1 - HOST_BITS_PER_WIDE_INT)))
	    val[1] |= HOST_WIDE_INT_M1U << (bitpos - HOST_BITS_PER_WIDE_INT);
	}

      মান = wide_int_to_বৃক্ষ (type,
				wide_int::from_array (val, 2,
						      HOST_BITS_PER_WIDE_INT * 2));
      add_pending_init (প্রবেশ_location, purpose, মান, NULL_বৃক্ষ, সত্য,
                        braced_init_obstack);
    }

  constructor_incremental = 0;
}

/* Return value of FIELD in pending initializer or NULL_TREE if the field was
   not initialized yet.  */

স্থির বৃক্ষ
find_init_member (বৃক্ষ field, কাঠামো obstack * braced_init_obstack)
{
  কাঠামো init_গ্রন্থি *p;

  যদি (বৃক্ষ_CODE (constructor_type) == ARRAY_TYPE)
    {
      যদি (constructor_incremental
	  && বৃক্ষ_int_cst_lt (field, constructor_unfilled_সূচক))
	set_nonincremental_init (braced_init_obstack);

      p = constructor_pending_elts;
      যখন (p)
	{
	  যদি (বৃক্ষ_int_cst_lt (field, p->purpose))
	    p = p->বাম;
	  অন্যথা যদি (বৃক্ষ_int_cst_lt (p->purpose, field))
	    p = p->ডান;
	  অন্যথা
	    ফেরত p->মান;
	}
    }
  অন্যথা যদি (বৃক্ষ_CODE (constructor_type) == RECORD_TYPE)
    {
      বৃক্ষ bitpos = bit_position (field);

      যদি (constructor_incremental
	  && (!constructor_unfilled_fields
	      || বৃক্ষ_int_cst_lt (bitpos,
				  bit_position (constructor_unfilled_fields))))
	set_nonincremental_init (braced_init_obstack);

      p = constructor_pending_elts;
      যখন (p)
	{
	  যদি (field == p->purpose)
	    ফেরত p->মান;
	  অন্যথা যদি (বৃক্ষ_int_cst_lt (bitpos, bit_position (p->purpose)))
	    p = p->বাম;
	  অন্যথা
	    p = p->ডান;
	}
    }
  অন্যথা যদি (বৃক্ষ_CODE (constructor_type) == UNION_TYPE)
    {
      যদি (!vec_safe_is_empty (constructor_elements)
	  && (constructor_elements->last ().সূচক == field))
	ফেরত constructor_elements->last ().মান;
    }
  ফেরত NULL_বৃক্ষ;
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

স্থির শূন্য
output_init_element (location_t loc, বৃক্ষ মান, বৃক্ষ origtype,
		     যৌক্তিক strict_string, বৃক্ষ type, বৃক্ষ field, যৌক্তিক pending,
		     যৌক্তিক implicit, কাঠামো obstack * braced_init_obstack)
{
  বৃক্ষ semantic_type = NULL_বৃক্ষ;
  যৌক্তিক maybe_const = সত্য;
  যৌক্তিক npc, int_const_রাশিমালা, arith_const_রাশিমালা;

  যদি (type == error_mark_গ্রন্থি || মান == error_mark_গ্রন্থি)
    {
      constructor_erroneous = 1;
      ফেরত;
    }
  যদি (বৃক্ষ_CODE (বৃক্ষ_TYPE (মান)) == ARRAY_TYPE
      && (বৃক্ষ_CODE (মান) == STRING_CST
	  || বৃক্ষ_CODE (মান) == COMPOUND_LITERAL_রাশিমালা)
      && !(বৃক্ষ_CODE (মান) == STRING_CST
	   && বৃক্ষ_CODE (type) == ARRAY_TYPE
	   && INTEGRAL_TYPE_P (বৃক্ষ_TYPE (type)))
      && !comptypes (TYPE_MAIN_VARIANT (বৃক্ষ_TYPE (মান)),
		     TYPE_MAIN_VARIANT (type)))
    মান = array_to_pointer_conversion (প্রবেশ_location, মান);

  যদি (বৃক্ষ_CODE (মান) == COMPOUND_LITERAL_রাশিমালা
      && require_constant_মান && pending)
    {
      /* As an extension, allow initializing objects with static storage
	 duration with compound literals (which are then treated just as
	 the brace enclosed list they contain).  */
      যদি (flag_isoc99)
	pedwarn_init (loc, OPT_Wpedantic, "initializer element is not "
		      "constant");
      বৃক্ষ decl = COMPOUND_LITERAL_রাশিমালা_DECL (মান);
      মান = DECL_INITIAL (decl);
    }

  npc = null_pointer_constant_p (মান);
  int_const_রাশিমালা = (বৃক্ষ_CODE (মান) == INTEGER_CST
		    && !বৃক্ষ_OVERFLOW (মান)
		    && INTEGRAL_TYPE_P (বৃক্ষ_TYPE (মান)));
  /* Not fully determined before folding.  */
  arith_const_রাশিমালা = সত্য;
  যদি (বৃক্ষ_CODE (মান) == EXCESS_PRECISION_রাশিমালা)
    {
      semantic_type = বৃক্ষ_TYPE (মান);
      মান = বৃক্ষ_OPERAND (মান, 0);
    }
  মান = c_fully_fold (মান, require_constant_মান, &maybe_const);
  /* TODO: this may not detect all cases of expressions folding to
     constants that are not arithmetic constant expressions.  */
  যদি (!maybe_const)
    arith_const_রাশিমালা = মিথ্যা;
  অন্যথা যদি (!INTEGRAL_TYPE_P (বৃক্ষ_TYPE (মান))
	   && বৃক্ষ_CODE (বৃক্ষ_TYPE (মান)) != REAL_TYPE
	   && বৃক্ষ_CODE (বৃক্ষ_TYPE (মান)) != COMPLEX_TYPE)
    arith_const_রাশিমালা = মিথ্যা;
  অন্যথা যদি (বৃক্ষ_CODE (মান) != INTEGER_CST
	   && বৃক্ষ_CODE (মান) != REAL_CST
	   && বৃক্ষ_CODE (মান) != COMPLEX_CST
	   && বৃক্ষ_CODE (মান) != RAW_তথ্য_CST)
    arith_const_রাশিমালা = মিথ্যা;
  অন্যথা যদি (বৃক্ষ_OVERFLOW (মান))
    arith_const_রাশিমালা = মিথ্যা;

  যদি (মান == error_mark_গ্রন্থি)
    constructor_erroneous = 1;
  অন্যথা যদি (!বৃক্ষ_CONSTANT (মান))
    constructor_constant = 0;
  অন্যথা যদি (!initializer_constant_valid_p (মান,
					  বৃক্ষ_TYPE (মান),
					  AGGREGATE_TYPE_P (constructor_type)
					  && TYPE_REVERSE_STORAGE_ORDER
					     (constructor_type))
	   || (RECORD_OR_UNION_TYPE_P (constructor_type)
	       && DECL_C_BIT_FIELD (field)
	       && বৃক্ষ_CODE (মান) != INTEGER_CST))
    constructor_simple = 0;
  যদি (!maybe_const)
    constructor_nonconst = 1;

  /* Digest the initializer and issue any errors about incompatible
     types before issuing errors about non-constant initializers.  */
  বৃক্ষ new_মান = মান;
  যদি (semantic_type)
    new_মান = build1 (EXCESS_PRECISION_রাশিমালা, semantic_type, মান);
  /* In the case of braces around a scalar initializer, the result of
     this initializer processing goes through digest_init again at the
     outer level.  In the case of a constexpr initializer for a
     pointer, avoid converting a null pointer constant to something
     that is not a null pointer constant to avoid a spurious error
     from that second processing.  */
  যদি (!require_constexpr_মান
      || !npc
      || বৃক্ষ_CODE (constructor_type) != POINTER_TYPE)
    new_মান = digest_init (loc,
			     RECORD_OR_UNION_TYPE_P (constructor_type)
			     ? field : constructor_fields
			     ? constructor_fields : constructor_decl,
			     type, new_মান, origtype, npc,
			     int_const_রাশিমালা, arith_const_রাশিমালা, strict_string,
			     require_constant_মান, require_constexpr_মান);
  যদি (new_মান == error_mark_গ্রন্থি)
    {
      constructor_erroneous = 1;
      ফেরত;
    }
  যদি (require_constant_মান || require_constant_elements)
    constant_expression_warning (new_মান);

  /* Proceed to check the constness of the original initializer.  */
  যদি (!initializer_constant_valid_p (মান, বৃক্ষ_TYPE (মান)))
    {
      যদি (require_constant_মান)
	{
	  error_init (loc, "initializer element is not constant");
	  মান = error_mark_গ্রন্থি;
	}
      অন্যথা যদি (require_constant_elements)
	pedwarn (loc, OPT_Wpedantic,
		 "initializer element is not computable at load time");
    }
  অন্যথা যদি (!maybe_const
	   && (require_constant_মান || require_constant_elements))
    pedwarn_init (loc, OPT_Wpedantic,
		  "initializer element is not a constant expression");
  /* digest_init has already carried out the additional checks
     required for 'constexpr' initializers (using the information
     passed to it about whether the original initializer was certain
     kinds of constant expression), so that check does not need to be
     repeated here.  */

  /* Issue -Wc++-compat warnings about initializing a bitfield with
     enum type.  */
  যদি (warn_cxx_compat
      && field != NULL_বৃক্ষ
      && বৃক্ষ_CODE (field) == FIELD_DECL
      && DECL_BIT_FIELD_TYPE (field) != NULL_বৃক্ষ
      && (TYPE_MAIN_VARIANT (DECL_BIT_FIELD_TYPE (field))
	  != TYPE_MAIN_VARIANT (type))
      && বৃক্ষ_CODE (DECL_BIT_FIELD_TYPE (field)) == ENUMERAL_TYPE)
    {
      বৃক্ষ checktype = origtype != NULL_বৃক্ষ ? origtype : বৃক্ষ_TYPE (মান);
      যদি (checktype != error_mark_গ্রন্থি
	  && (TYPE_MAIN_VARIANT (checktype)
	      != TYPE_MAIN_VARIANT (DECL_BIT_FIELD_TYPE (field))))
	warning_init (loc, OPT_Wc___compat,
		      "enum conversion in initialization is invalid in C++");
    }

  /* If this field is empty and does not have side effects (and is not at
     the end of structure), don't do anything other than checking the
     initializer.  */
  যদি (field
      && (বৃক্ষ_TYPE (field) == error_mark_গ্রন্থি
	  || (COMPLETE_TYPE_P (বৃক্ষ_TYPE (field))
	      && integer_zerop (TYPE_আকার (বৃক্ষ_TYPE (field)))
	      && !বৃক্ষ_SIDE_EFFECTS (new_মান)
	      && (বৃক্ষ_CODE (constructor_type) == ARRAY_TYPE
		  || DECL_CHAIN (field)))))
    ফেরত;

  /* Finally, set VALUE to the initializer value digested above.  */
  মান = new_মান;

  /* If this element doesn't come next in sequence,
     put it on constructor_pending_elts.  */
  যদি (বৃক্ষ_CODE (constructor_type) == ARRAY_TYPE
      && (!constructor_incremental
	  || !বৃক্ষ_int_cst_equal (field, constructor_unfilled_সূচক)
	  || (বৃক্ষ_CODE (মান) == RAW_তথ্য_CST
	      && constructor_pending_elts
	      && pending)))
    {
      যদি (constructor_incremental
	  && (বৃক্ষ_int_cst_lt (field, constructor_unfilled_সূচক)
	      || (বৃক্ষ_CODE (মান) == RAW_তথ্য_CST
		  && constructor_pending_elts
		  && pending)))
	set_nonincremental_init (braced_init_obstack);

      add_pending_init (loc, field, মান, origtype, implicit,
			braced_init_obstack);
      ফেরত;
    }
  অন্যথা যদি (বৃক্ষ_CODE (constructor_type) == RECORD_TYPE
	   && (!constructor_incremental
	       || field != constructor_unfilled_fields))
    {
      /* We do this for records but not for unions.  In a union,
	 no matter which field is specified, it can be initialized
	 right away since it starts at the beginning of the union.  */
      যদি (constructor_incremental)
	{
	  যদি (!constructor_unfilled_fields)
	    set_nonincremental_init (braced_init_obstack);
	  অন্যথা
	    {
	      বৃক্ষ bitpos, unfillpos;

	      bitpos = bit_position (field);
	      unfillpos = bit_position (constructor_unfilled_fields);

	      যদি (বৃক্ষ_int_cst_lt (bitpos, unfillpos))
		set_nonincremental_init (braced_init_obstack);
	    }
	}

      add_pending_init (loc, field, মান, origtype, implicit,
			braced_init_obstack);
      ফেরত;
    }
  অন্যথা যদি (বৃক্ষ_CODE (constructor_type) == UNION_TYPE
	   && !vec_safe_is_empty (constructor_elements))
    {
      যদি (!implicit)
	{
	  যদি (বৃক্ষ_SIDE_EFFECTS (constructor_elements->last ().মান))
	    warning_init (loc, OPT_Woverride_init_side_effects,
			  "initialized field with side-effects overwritten");
	  অন্যথা যদি (warn_override_init)
	    warning_init (loc, OPT_Woverride_init,
			  "initialized field overwritten");
	}

      /* We can have just one union field set.  */
      constructor_elements = ফাঁকা;
    }

  /* Otherwise, output this element either to
     constructor_elements or to the assembler file.  */

  constructor_elt celt = {field, মান};
  vec_safe_ঠেলো (constructor_elements, celt);

  /* Advance the variable that indicates sequential elements output.  */
  যদি (বৃক্ষ_CODE (constructor_type) == ARRAY_TYPE)
    {
      বৃক্ষ inc = bitsize_one_গ্রন্থি;
      যদি (মান && বৃক্ষ_CODE (মান) == RAW_তথ্য_CST)
	inc = bitsize_int (RAW_তথ্য_দৈর্ঘ্য (মান));
      constructor_unfilled_সূচক
	= আকার_binop_loc (প্রবেশ_location, PLUS_রাশিমালা,
			  constructor_unfilled_সূচক, inc);
    }
  অন্যথা যদি (বৃক্ষ_CODE (constructor_type) == RECORD_TYPE)
    {
      constructor_unfilled_fields
	= DECL_CHAIN (constructor_unfilled_fields);

      /* Skip any nameless bit fields.  */
      যখন (constructor_unfilled_fields != NULL_বৃক্ষ
	     && DECL_UNNAMED_BIT_FIELD (constructor_unfilled_fields))
	constructor_unfilled_fields
	  = DECL_CHAIN (constructor_unfilled_fields);
    }
  অন্যথা যদি (বৃক্ষ_CODE (constructor_type) == UNION_TYPE)
    constructor_unfilled_fields = NULL_বৃক্ষ;

  /* Now output any pending elements which have become next.  */
  যদি (pending)
    output_pending_init_elements (0, braced_init_obstack);
}

/* For two FIELD_DECLs in the same chain, return -1 if field1
   comes before field2, 1 if field1 comes after field2 and
   0 if field1 == field2.  */

স্থির পূর্ণসংখ্যা
init_field_decl_cmp (বৃক্ষ field1, বৃক্ষ field2)
{
  যদি (field1 == field2)
    ফেরত 0;

  বৃক্ষ bitpos1 = bit_position (field1);
  বৃক্ষ bitpos2 = bit_position (field2);
  যদি (বৃক্ষ_int_cst_equal (bitpos1, bitpos2))
    {
      /* If one of the fields has non-zero bitsize, then that
	 field must be the last one in a sequence of zero
	 sized fields, fields after it will have bigger
	 bit_position.  */
      যদি (বৃক্ষ_TYPE (field1) != error_mark_গ্রন্থি
	  && COMPLETE_TYPE_P (বৃক্ষ_TYPE (field1))
	  && integer_nonzerop (বৃক্ষ_TYPE (field1)))
	ফেরত 1;
      যদি (বৃক্ষ_TYPE (field2) != error_mark_গ্রন্থি
	  && COMPLETE_TYPE_P (বৃক্ষ_TYPE (field2))
	  && integer_nonzerop (বৃক্ষ_TYPE (field2)))
	ফেরত -1;
      /* Otherwise, fallback to DECL_CHAIN walk to find out
	 which field comes earlier.  Walk chains of both
	 fields, so that if field1 and field2 are close to each
	 other in either order, it is found soon even for large
	 sequences of zero sized fields.  */
      বৃক্ষ f1 = field1, f2 = field2;
      যখন (1)
	{
	  f1 = DECL_CHAIN (f1);
	  f2 = DECL_CHAIN (f2);
	  যদি (f1 == NULL_বৃক্ষ)
	    {
	      gcc_assert (f2);
	      ফেরত 1;
	    }
	  যদি (f2 == NULL_বৃক্ষ)
	    ফেরত -1;
	  যদি (f1 == field2)
	    ফেরত -1;
	  যদি (f2 == field1)
	    ফেরত 1;
	  যদি (!বৃক্ষ_int_cst_equal (bit_position (f1), bitpos1))
	    ফেরত 1;
	  যদি (!বৃক্ষ_int_cst_equal (bit_position (f2), bitpos1))
	    ফেরত -1;
	}
    }
  অন্যথা যদি (বৃক্ষ_int_cst_lt (bitpos1, bitpos2))
    ফেরত -1;
  অন্যথা
    ফেরত 1;
}

/* Output any pending elements which have become next.
   As we output elements, constructor_unfilled_{fields,index}
   advances, which may cause other elements to become next;
   if so, they too are output.

   If ALL is 0, we return when there are
   no more pending elements to output now.

   If ALL is 1, we output space as necessary so that
   we can output all the pending elements.  */
স্থির শূন্য
output_pending_init_elements (পূর্ণসংখ্যা all, কাঠামো obstack * braced_init_obstack)
{
  কাঠামো init_গ্রন্থি *elt = constructor_pending_elts;
  বৃক্ষ পরবর্তী;

 retry:

  /* Look through the whole pending tree.
     If we find an element that should be output now,
     output it.  Otherwise, set NEXT to the element
     that comes first among those still pending.  */

  পরবর্তী = NULL_বৃক্ষ;
  যখন (elt)
    {
      যদি (বৃক্ষ_CODE (constructor_type) == ARRAY_TYPE)
	{
	  যদি (বৃক্ষ_int_cst_equal (elt->purpose,
				  constructor_unfilled_সূচক))
	    output_init_element (প্রবেশ_location, elt->মান, elt->origtype,
				 সত্য, বৃক্ষ_TYPE (constructor_type),
				 constructor_unfilled_সূচক, মিথ্যা, মিথ্যা,
				 braced_init_obstack);
	  অন্যথা যদি (বৃক্ষ_int_cst_lt (constructor_unfilled_সূচক,
				    elt->purpose))
	    {
	      /* Advance to the next smaller node.  */
	      যদি (elt->বাম)
		elt = elt->বাম;
	      অন্যথা
		{
		  /* We have reached the smallest node bigger than the
		     current unfilled index.  Fill the space first.  */
		  পরবর্তী = elt->purpose;
		  বিরতি;
		}
	    }
	  অন্যথা
	    {
	      /* Advance to the next bigger node.  */
	      যদি (elt->ডান)
		elt = elt->ডান;
	      অন্যথা
		{
		  /* We have reached the biggest node in a subtree.  Find
		     the parent of it, which is the next bigger node.  */
		  যখন (elt->parent && elt->parent->ডান == elt)
		    elt = elt->parent;
		  elt = elt->parent;
		  যদি (elt && বৃক্ষ_int_cst_lt (constructor_unfilled_সূচক,
					      elt->purpose))
		    {
		      পরবর্তী = elt->purpose;
		      বিরতি;
		    }
		}
	    }
	}
      অন্যথা যদি (RECORD_OR_UNION_TYPE_P (constructor_type))
	{
	  /* If the current record is complete we are done.  */
	  যদি (constructor_unfilled_fields == NULL_বৃক্ষ)
	    বিরতি;

	  পূর্ণসংখ্যা cmp = init_field_decl_cmp (constructor_unfilled_fields,
					 elt->purpose);
	  যদি (cmp == 0)
	    output_init_element (প্রবেশ_location, elt->মান, elt->origtype,
				 সত্য, বৃক্ষ_TYPE (elt->purpose),
				 elt->purpose, মিথ্যা, মিথ্যা,
				 braced_init_obstack);
	  অন্যথা যদি (cmp < 0)
	    {
	      /* Advance to the next smaller node.  */
	      যদি (elt->বাম)
		elt = elt->বাম;
	      অন্যথা
		{
		  /* We have reached the smallest node bigger than the
		     current unfilled field.  Fill the space first.  */
		  পরবর্তী = elt->purpose;
		  বিরতি;
		}
	    }
	  অন্যথা
	    {
	      /* Advance to the next bigger node.  */
	      যদি (elt->ডান)
		elt = elt->ডান;
	      অন্যথা
		{
		  /* We have reached the biggest node in a subtree.  Find
		     the parent of it, which is the next bigger node.  */
		  যখন (elt->parent && elt->parent->ডান == elt)
		    elt = elt->parent;
		  elt = elt->parent;
		  যদি (elt
		      && init_field_decl_cmp (constructor_unfilled_fields,
					      elt->purpose) < 0)
		    {
		      পরবর্তী = elt->purpose;
		      বিরতি;
		    }
		}
	    }
	}
    }

  /* Ordinarily return, but not if we want to output all
     and there are elements left.  */
  যদি (!(all && পরবর্তী != NULL_বৃক্ষ))
    ফেরত;

  /* If it's not incremental, just skip over the gap, so that after
     jumping to retry we will output the next successive element.  */
  যদি (RECORD_OR_UNION_TYPE_P (constructor_type))
    constructor_unfilled_fields = পরবর্তী;
  অন্যথা যদি (বৃক্ষ_CODE (constructor_type) == ARRAY_TYPE)
    constructor_unfilled_সূচক = পরবর্তী;

  /* ELT now points to the node in the pending tree with the next
     initializer to output.  */
  যাও retry;
}

/* Expression VALUE coincides with the start of type TYPE in a braced
   initializer.  Return true if we should treat VALUE as initializing
   the first element of TYPE, false if we should treat it as initializing
   TYPE as a whole.

   If the initializer is clearly invalid, the question becomes:
   which choice gives the best error message?  */

স্থির যৌক্তিক
initialize_elementwise_p (বৃক্ষ type, বৃক্ষ মান)
{
  যদি (type == error_mark_গ্রন্থি || মান == error_mark_গ্রন্থি)
    ফেরত মিথ্যা;

  gcc_checking_assert (TYPE_MAIN_VARIANT (type) == type);

  বৃক্ষ মান_type = বৃক্ষ_TYPE (মান);
  যদি (মান_type == error_mark_গ্রন্থি)
    ফেরত মিথ্যা;

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
  যদি (gnu_vector_type_p (type))
    ফেরত !VECTOR_TYPE_P (মান_type);

  যদি (AGGREGATE_TYPE_P (type))
    ফেরত !comptypes (type, TYPE_MAIN_VARIANT (মান_type));

  ফেরত মিথ্যা;
}

/* Helper function for process_init_element.  Split first element of
   RAW_DATA_CST and save the rest to *RAW_DATA.  */

স্থির অন্তঃরেখ বৃক্ষ
maybe_split_raw_তথ্য (বৃক্ষ মান, বৃক্ষ *raw_তথ্য)
{
  যদি (মান == NULL_বৃক্ষ || বৃক্ষ_CODE (মান) != RAW_তথ্য_CST)
    ফেরত মান;
  *raw_তথ্য = মান;
  মান = build_int_cst (integer_type_গ্রন্থি,
			 RAW_তথ্য_UCHAR_ELT (*raw_তথ্য, 0));
  ++RAW_তথ্য_POINTER (*raw_তথ্য);
  --RAW_তথ্য_দৈর্ঘ্য (*raw_তথ্য);
  ফেরত মান;
}

/* Return non-zero if c_parser_initval should attempt to optimize
   large initializers into RAW_DATA_CST.  In that case return how
   many elements to optimize at most.  */

unsigned
c_maybe_optimize_large_byte_initializer (শূন্য)
{
  যদি (!constructor_type
      || বৃক্ষ_CODE (constructor_type) != ARRAY_TYPE
      || constructor_স্তূপ->implicit)
    ফেরত 0;
  বৃক্ষ elttype = TYPE_MAIN_VARIANT (বৃক্ষ_TYPE (constructor_type));
  যদি (বৃক্ষ_CODE (elttype) != INTEGER_TYPE
      && বৃক্ষ_CODE (elttype) != BITINT_TYPE)
    ফেরত 0;
  যদি (TYPE_PRECISION (elttype) != CHAR_BIT
      || constructor_স্তূপ->replacement_মান.মান
      || (COMPLETE_TYPE_P (constructor_type)
	  && !poly_int_বৃক্ষ_p (TYPE_আকার (constructor_type)))
      || constructor_range_স্তূপ)
    ফেরত 0;
  যদি (constructor_max_সূচক == NULL_বৃক্ষ)
    ফেরত INT_MAX;
  যদি (বৃক্ষ_int_cst_le (constructor_max_সূচক, constructor_সূচক)
      || integer_all_onesp (constructor_max_সূচক))
    ফেরত 0;
  widest_int w = wi::to_widest (constructor_max_সূচক);
  w -= wi::to_widest (constructor_সূচক);
  w += 1;
  যদি (w < 64)
    ফেরত 0;
  যদি (w > INT_MAX)
    ফেরত INT_MAX;
  ফেরত w.to_uhwi ();
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

শূন্য
process_init_element (location_t loc, কাঠামো c_রাশিমালা মান, যৌক্তিক implicit,
		      কাঠামো obstack * braced_init_obstack)
{
  বৃক্ষ orig_মান = মান.মান;
  পূর্ণসংখ্যা string_flag
    = (orig_মান != NULL_বৃক্ষ && বৃক্ষ_CODE (orig_মান) == STRING_CST);
  যৌক্তিক strict_string = মান.original_code == STRING_CST;
  যৌক্তিক was_designated = designator_depth != 0;
  বৃক্ষ raw_তথ্য = NULL_বৃক্ষ;

retry:
  designator_depth = 0;
  designator_erroneous = 0;

  যদি (!implicit && মান.মান && !integer_zerop (মান.মান))
    constructor_zeroinit = 0;

  /* Handle superfluous braces around string cst as in
     char x[] = {"foo"}; */
  যদি (constructor_type
      && !was_designated
      && বৃক্ষ_CODE (constructor_type) == ARRAY_TYPE
      && INTEGRAL_TYPE_P (বৃক্ষ_TYPE (constructor_type))
      && integer_zerop (constructor_unfilled_সূচক))
    {
      যদি (constructor_স্তূপ->replacement_মান.মান)
	{
	  error_init (loc, "excess elements in %qT initializer", constructor_type);
	  ফেরত;
	}
      অন্যথা যদি (string_flag)
	{
	  constructor_স্তূপ->replacement_মান = মান;
	  ফেরত;
	}
    }

  যদি (constructor_স্তূপ->replacement_মান.মান != NULL_বৃক্ষ)
    {
      error_init (loc, "excess elements in struct initializer");
      ফেরত;
    }

  /* Ignore elements of a brace group if it is entirely superfluous
     and has already been diagnosed, or if the type is erroneous.  */
  যদি (constructor_type == NULL_বৃক্ষ || constructor_type == error_mark_গ্রন্থি)
    ফেরত;

  /* Ignore elements of an initializer for a variable-size type.
     Those are diagnosed in the parser (empty initializer braces are OK).  */
  যদি (COMPLETE_TYPE_P (constructor_type)
      && !poly_int_বৃক্ষ_p (TYPE_আকার (constructor_type)))
    ফেরত;

  যদি (!implicit && warn_designated_init && !was_designated
      && বৃক্ষ_CODE (constructor_type) == RECORD_TYPE
      && lookup_attribute ("designated_init",
			   TYPE_ATTRIBUTES (constructor_type)))
    warning_init (loc,
		  OPT_Wdesignated_init,
		  "positional initialization of field "
		  "in %<struct%> declared with %<designated_init%> attribute");

  /* If we've exhausted any levels that didn't have braces,
     pop them now.  */
  যখন (constructor_স্তূপ->implicit)
    {
      যদি (RECORD_OR_UNION_TYPE_P (constructor_type)
	  && constructor_fields == NULL_বৃক্ষ)
	process_init_element (loc,
			      বের_করো_init_level (loc, 1, braced_init_obstack,
					      last_init_list_comma),
			      সত্য, braced_init_obstack);
      অন্যথা যদি ((বৃক্ষ_CODE (constructor_type) == ARRAY_TYPE
		|| gnu_vector_type_p (constructor_type))
	       && constructor_max_সূচক
	       && বৃক্ষ_int_cst_lt (constructor_max_সূচক,
				   constructor_সূচক))
	process_init_element (loc,
			      বের_করো_init_level (loc, 1, braced_init_obstack,
					      last_init_list_comma),
			      সত্য, braced_init_obstack);
      অন্যথা
	বিরতি;
    }

  /* In the case of [LO ... HI] = VALUE, only evaluate VALUE once.  */
  যদি (constructor_range_স্তূপ)
    {
      /* If value is a compound literal and we'll be just using its
	 content, don't put it into a SAVE_EXPR.  */
      যদি (বৃক্ষ_CODE (মান.মান) != COMPOUND_LITERAL_রাশিমালা
	  || !require_constant_মান)
	{
	  বৃক্ষ semantic_type = NULL_বৃক্ষ;
	  যদি (বৃক্ষ_CODE (মান.মান) == EXCESS_PRECISION_রাশিমালা)
	    {
	      semantic_type = বৃক্ষ_TYPE (মান.মান);
	      মান.মান = বৃক্ষ_OPERAND (মান.মান, 0);
	    }
	  মান.মান = save_রাশিমালা (মান.মান);
	  যদি (semantic_type)
	    মান.মান = build1 (EXCESS_PRECISION_রাশিমালা, semantic_type,
				  মান.মান);
	}
    }

  যখন (1)
    {
      যদি (বৃক্ষ_CODE (constructor_type) == RECORD_TYPE)
	{
	  বৃক্ষ fieldtype;
	  গণনা বৃক্ষ_code fieldcode;

	  যদি (constructor_fields == NULL_বৃক্ষ)
	    {
	      pedwarn_init (loc, 0, "excess elements in struct initializer");
	      বিরতি;
	    }

	  fieldtype = বৃক্ষ_TYPE (constructor_fields);
	  যদি (fieldtype != error_mark_গ্রন্থি)
	    fieldtype = TYPE_MAIN_VARIANT (fieldtype);
	  fieldcode = বৃক্ষ_CODE (fieldtype);

	  /* Error for non-static initialization of a flexible array member.  */
	  যদি (fieldcode == ARRAY_TYPE
	      && !require_constant_মান
	      && TYPE_আকার (fieldtype) == NULL_বৃক্ষ
	      && DECL_CHAIN (constructor_fields) == NULL_বৃক্ষ)
	    {
	      error_init (loc, "non-static initialization of a flexible "
			  "array member");
	      বিরতি;
	    }

	  /* Error for initialization of a flexible array member with
	     a string constant if the structure is in an array.  E.g.:
	     struct S { int x; char y[]; };
	     struct S s[] = { { 1, "foo" } };
	     is invalid.  */
	  যদি (string_flag
	      && fieldcode == ARRAY_TYPE
	      && constructor_depth > 1
	      && TYPE_আকার (fieldtype) == NULL_বৃক্ষ
	      && DECL_CHAIN (constructor_fields) == NULL_বৃক্ষ)
	    {
	      যৌক্তিক in_array_p = মিথ্যা;
	      জন্য (কাঠামো constructor_স্তূপ *p = constructor_স্তূপ;
		   p && p->type; p = p->পরবর্তী)
		যদি (বৃক্ষ_CODE (p->type) == ARRAY_TYPE)
		  {
		    in_array_p = সত্য;
		    বিরতি;
		  }
	      যদি (in_array_p)
		{
		  error_init (loc, "initialization of flexible array "
			      "member in a nested context");
		  বিরতি;
		}
	    }

	  /* Accept a string constant to initialize a subarray.  */
	  যদি (মান.মান != NULL_বৃক্ষ
	      && fieldcode == ARRAY_TYPE
	      && INTEGRAL_TYPE_P (বৃক্ষ_TYPE (fieldtype))
	      && string_flag)
	    মান.মান = orig_মান;
	  /* Otherwise, if we have come to a subaggregate,
	     and we don't have an element of its type, push into it.  */
	  অন্যথা যদি (মান.মান != NULL_বৃক্ষ
		   && initialize_elementwise_p (fieldtype, মান.মান))
	    {
	      ঠেলো_init_level (loc, 1, braced_init_obstack);
	      চালু;
	    }

	  মান.মান = maybe_split_raw_তথ্য (মান.মান, &raw_তথ্য);
	  যদি (মান.মান)
	    {
	      ঠেলো_member_name (constructor_fields);
	      output_init_element (loc, মান.মান, মান.original_type,
				   strict_string, fieldtype,
				   constructor_fields, সত্য, implicit,
				   braced_init_obstack);
	      RESTORE_SPELLING_DEPTH (constructor_depth);
	    }
	  অন্যথা
	    /* Do the bookkeeping for an element that was
	       directly output as a constructor.  */
	    {
	      /* For a record, keep track of end position of last field.  */
	      যদি (DECL_আকার (constructor_fields))
		constructor_bit_সূচক
		  = আকার_binop_loc (প্রবেশ_location, PLUS_রাশিমালা,
				    bit_position (constructor_fields),
				    DECL_আকার (constructor_fields));

	      /* If the current field was the first one not yet written out,
		 it isn't now, so update.  */
	      যদি (constructor_unfilled_fields == constructor_fields)
		{
		  constructor_unfilled_fields = DECL_CHAIN (constructor_fields);
		  /* Skip any nameless bit fields.  */
		  যখন (constructor_unfilled_fields != 0
			 && (DECL_UNNAMED_BIT_FIELD
			     (constructor_unfilled_fields)))
		    constructor_unfilled_fields =
		      DECL_CHAIN (constructor_unfilled_fields);
		}
	    }

	  constructor_fields = DECL_CHAIN (constructor_fields);
	  /* Skip any nameless bit fields at the beginning.  */
	  যখন (constructor_fields != NULL_বৃক্ষ
		 && DECL_UNNAMED_BIT_FIELD (constructor_fields))
	    constructor_fields = DECL_CHAIN (constructor_fields);
	}
      অন্যথা যদি (বৃক্ষ_CODE (constructor_type) == UNION_TYPE)
	{
	  বৃক্ষ fieldtype;
	  গণনা বৃক্ষ_code fieldcode;

	  যদি (constructor_fields == NULL_বৃক্ষ)
	    {
	      pedwarn_init (loc, 0,
			    "excess elements in union initializer");
	      বিরতি;
	    }

	  fieldtype = বৃক্ষ_TYPE (constructor_fields);
	  যদি (fieldtype != error_mark_গ্রন্থি)
	    fieldtype = TYPE_MAIN_VARIANT (fieldtype);
	  fieldcode = বৃক্ষ_CODE (fieldtype);

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
	  যদি (!in_system_header_at (প্রবেশ_location) && !constructor_designated
	      && !(মান.মান && (integer_zerop (মান.মান)
				   || real_zerop (মান.মান))))
	    warning (OPT_Wtraditional, "traditional C rejects initialization "
		     "of unions");

	  /* Error for non-static initialization of a flexible array member.  */
	  যদি (fieldcode == ARRAY_TYPE
	      && !require_constant_মান
	      && TYPE_আকার (fieldtype) == NULL_বৃক্ষ)
	    {
	      error_init (loc, "non-static initialization of a flexible "
			  "array member");
	      বিরতি;
	    }

	  /* Error for initialization of a flexible array member with
	     a string constant if the structure is in an array.  E.g.:
	     union U { int x; char y[]; };
	     union U s[] = { { 1, "foo" } };
	     is invalid.  */
	  যদি (string_flag
	      && fieldcode == ARRAY_TYPE
	      && constructor_depth > 1
	      && TYPE_আকার (fieldtype) == NULL_বৃক্ষ)
	    {
	      যৌক্তিক in_array_p = মিথ্যা;
	      জন্য (কাঠামো constructor_স্তূপ *p = constructor_স্তূপ;
		   p && p->type; p = p->পরবর্তী)
		যদি (বৃক্ষ_CODE (p->type) == ARRAY_TYPE)
		  {
		    in_array_p = সত্য;
		    বিরতি;
		  }
	      যদি (in_array_p)
		{
		  error_init (loc, "initialization of flexible array "
			      "member in a nested context");
		  বিরতি;
		}
	    }

	  /* Accept a string constant to initialize a subarray.  */
	  যদি (মান.মান != NULL_বৃক্ষ
	      && fieldcode == ARRAY_TYPE
	      && INTEGRAL_TYPE_P (বৃক্ষ_TYPE (fieldtype))
	      && string_flag)
	    মান.মান = orig_মান;
	  /* Otherwise, if we have come to a subaggregate,
	     and we don't have an element of its type, push into it.  */
	  অন্যথা যদি (মান.মান != NULL_বৃক্ষ
		   && initialize_elementwise_p (fieldtype, মান.মান))
	    {
	      ঠেলো_init_level (loc, 1, braced_init_obstack);
	      চালু;
	    }

	  মান.মান = maybe_split_raw_তথ্য (মান.মান, &raw_তথ্য);
	  যদি (মান.মান)
	    {
	      ঠেলো_member_name (constructor_fields);
	      output_init_element (loc, মান.মান, মান.original_type,
				   strict_string, fieldtype,
				   constructor_fields, সত্য, implicit,
				   braced_init_obstack);
	      RESTORE_SPELLING_DEPTH (constructor_depth);
	    }
	  অন্যথা
	    /* Do the bookkeeping for an element that was
	       directly output as a constructor.  */
	    {
	      constructor_bit_সূচক = DECL_আকার (constructor_fields);
	      constructor_unfilled_fields = DECL_CHAIN (constructor_fields);
	    }

	  constructor_fields = NULL_বৃক্ষ;
	}
      অন্যথা যদি (বৃক্ষ_CODE (constructor_type) == ARRAY_TYPE)
	{
	  বৃক্ষ elttype = TYPE_MAIN_VARIANT (বৃক্ষ_TYPE (constructor_type));
	  গণনা বৃক্ষ_code eltcode = বৃক্ষ_CODE (elttype);

	  /* Accept a string constant to initialize a subarray.  */
	  যদি (মান.মান != NULL_বৃক্ষ
	      && eltcode == ARRAY_TYPE
	      && INTEGRAL_TYPE_P (বৃক্ষ_TYPE (elttype))
	      && string_flag)
	    মান.মান = orig_মান;
	  /* Otherwise, if we have come to a subaggregate,
	     and we don't have an element of its type, push into it.  */
	  অন্যথা যদি (মান.মান != NULL_বৃক্ষ
		   && initialize_elementwise_p (elttype, মান.মান))
	    {
	      ঠেলো_init_level (loc, 1, braced_init_obstack);
	      চালু;
	    }

	  যদি (constructor_max_সূচক != NULL_বৃক্ষ
	      && (বৃক্ষ_int_cst_lt (constructor_max_সূচক, constructor_সূচক)
		  || integer_all_onesp (constructor_max_সূচক))
	      /* For VLA we got an error already.  */
	      && !C_TYPE_VARIABLE_আকার (constructor_type))
	    {
	      pedwarn_init (loc, 0,
			    "excess elements in array initializer");
	      বিরতি;
	    }

	  যদি (মান.মান
	      && বৃক্ষ_CODE (মান.মান) == RAW_তথ্য_CST
	      && RAW_তথ্য_দৈর্ঘ্য (মান.মান) > 1
	      && (বৃক্ষ_CODE (elttype) == INTEGER_TYPE
		  || বৃক্ষ_CODE (elttype) == BITINT_TYPE)
	      && TYPE_PRECISION (elttype) == CHAR_BIT
	      && (constructor_max_সূচক == NULL_বৃক্ষ
		  || বৃক্ষ_int_cst_lt (constructor_সূচক,
				      constructor_max_সূচক)))
	    {
	      unsigned পূর্ণসংখ্যা len = RAW_তথ্য_দৈর্ঘ্য (মান.মান);
	      যদি (constructor_max_সূচক)
		{
		  widest_int w = wi::to_widest (constructor_max_সূচক);
		  w -= wi::to_widest (constructor_সূচক);
		  w += 1;
		  যদি (w < len)
		    len = w.to_uhwi ();
		}
	      যদি (len < (unsigned) RAW_তথ্য_দৈর্ঘ্য (মান.মান))
		{
		  raw_তথ্য = copy_গ্রন্থি (মান.মান);
		  RAW_তথ্য_দৈর্ঘ্য (raw_তথ্য) -= len;
		  RAW_তথ্য_POINTER (raw_তথ্য) += len;
		  RAW_তথ্য_দৈর্ঘ্য (মান.মান) = len;
		}
	      বৃক্ষ_TYPE (মান.মান) = elttype;
	      ঠেলো_array_bounds (বৃক্ষ_to_uhwi (constructor_সূচক));
	      output_init_element (loc, মান.মান, মান.original_type,
				   মিথ্যা, elttype, constructor_সূচক, সত্য,
				   implicit, braced_init_obstack);
	      RESTORE_SPELLING_DEPTH (constructor_depth);
	      constructor_সূচক
		= আকার_binop_loc (প্রবেশ_location, PLUS_রাশিমালা,
				  constructor_সূচক, bitsize_int (len));
	    }
	  অন্যথা
	    {
	      মান.মান = maybe_split_raw_তথ্য (মান.মান, &raw_তথ্য);
	      /* Now output the actual element.  */
	      যদি (মান.মান)
		{
		  ঠেলো_array_bounds (বৃক্ষ_to_uhwi (constructor_সূচক));
		  output_init_element (loc, মান.মান, মান.original_type,
				       strict_string, elttype,
				       constructor_সূচক, সত্য, implicit,
				       braced_init_obstack);
		  RESTORE_SPELLING_DEPTH (constructor_depth);
		}

	      constructor_সূচক
		= আকার_binop_loc (প্রবেশ_location, PLUS_রাশিমালা,
				  constructor_সূচক, bitsize_one_গ্রন্থি);

	      যদি (!মান.মান)
		/* If we are doing the bookkeeping for an element that was
		   directly output as a constructor, we must update
		   constructor_unfilled_index.  */
		constructor_unfilled_সূচক = constructor_সূচক;
	    }
	}
      অন্যথা যদি (gnu_vector_type_p (constructor_type))
	{
	  বৃক্ষ elttype = TYPE_MAIN_VARIANT (বৃক্ষ_TYPE (constructor_type));

	  /* Do a basic check of initializer size.  Note that vectors
	     may not always have a fixed size derived from their type.  */
	  যদি (maybe_lt (বৃক্ষ_to_poly_uint64 (constructor_max_সূচক),
			বৃক্ষ_to_poly_uint64 (constructor_সূচক)))
	    {
	      /* Diagose VLA out-of-bounds as errors.  */
	      যদি (বৃক্ষ_to_poly_uint64 (constructor_max_সূচক).is_constant())
		pedwarn_init (loc, 0,
			      "excess elements in vector initializer");
	      অন্যথা
		error_init (loc, "excess elements in vector initializer");

	      বিরতি;
	    }

	  মান.মান = maybe_split_raw_তথ্য (মান.মান, &raw_তথ্য);
	  /* Now output the actual element.  */
	  যদি (মান.মান)
	    {
	      যদি (বৃক্ষ_CODE (মান.মান) == VECTOR_CST)
		elttype = TYPE_MAIN_VARIANT (constructor_type);
	      output_init_element (loc, মান.মান, মান.original_type,
				   strict_string, elttype,
				   constructor_সূচক, সত্য, implicit,
				   braced_init_obstack);
	    }

	  constructor_সূচক
	    = আকার_binop_loc (প্রবেশ_location,
			      PLUS_রাশিমালা, constructor_সূচক, bitsize_one_গ্রন্থি);

	  যদি (!মান.মান)
	    /* If we are doing the bookkeeping for an element that was
	       directly output as a constructor, we must update
	       constructor_unfilled_index.  */
	    constructor_unfilled_সূচক = constructor_সূচক;
	}

      /* Handle the sole element allowed in a braced initializer
	 for a scalar variable.  */
      অন্যথা যদি (constructor_type != error_mark_গ্রন্থি
	       && constructor_fields == NULL_বৃক্ষ)
	{
	  pedwarn_init (loc, 0,
			"excess elements in scalar initializer");
	  বিরতি;
	}
      অন্যথা
	{
	  মান.মান = maybe_split_raw_তথ্য (মান.মান, &raw_তথ্য);
	  যদি (মান.মান)
	    output_init_element (loc, মান.মান, মান.original_type,
				 strict_string, constructor_type,
				 NULL_বৃক্ষ, সত্য, implicit,
				 braced_init_obstack);
	  constructor_fields = NULL_বৃক্ষ;
	}

      /* Handle range initializers either at this level or anywhere higher
	 in the designator stack.  */
      যদি (constructor_range_স্তূপ)
	{
	  কাঠামো constructor_range_স্তূপ *p, *range_স্তূপ;
	  পূর্ণসংখ্যা finish = 0;

	  range_স্তূপ = constructor_range_স্তূপ;
	  constructor_range_স্তূপ = 0;
	  যখন (constructor_স্তূপ != range_স্তূপ->স্তূপ)
	    {
	      gcc_assert (constructor_স্তূপ->implicit);
	      process_init_element (loc,
				    বের_করো_init_level (loc, 1,
						    braced_init_obstack,
						    last_init_list_comma),
				    সত্য, braced_init_obstack);
	    }
	  জন্য (p = range_স্তূপ;
	       !p->range_end || বৃক্ষ_int_cst_equal (p->সূচক, p->range_end);
	       p = p->পূর্ব)
	    {
	      gcc_assert (constructor_স্তূপ->implicit);
	      process_init_element (loc,
				    বের_করো_init_level (loc, 1,
						    braced_init_obstack,
						    last_init_list_comma),
				    সত্য, braced_init_obstack);
	    }

	  p->সূচক = আকার_binop_loc (প্রবেশ_location,
				     PLUS_রাশিমালা, p->সূচক, bitsize_one_গ্রন্থি);
	  যদি (বৃক্ষ_int_cst_equal (p->সূচক, p->range_end) && !p->পূর্ব)
	    finish = 1;

	  যখন (1)
	    {
	      constructor_সূচক = p->সূচক;
	      constructor_fields = p->fields;
	      যদি (finish && p->range_end && p->সূচক == p->range_start)
		{
		  finish = 0;
		  p->পূর্ব = 0;
		}
	      p = p->পরবর্তী;
	      যদি (!p)
		বিরতি;
	      finish_implicit_inits (loc, braced_init_obstack);
	      ঠেলো_init_level (loc, 2, braced_init_obstack);
	      p->স্তূপ = constructor_স্তূপ;
	      যদি (p->range_end && বৃক্ষ_int_cst_equal (p->সূচক, p->range_end))
		p->সূচক = p->range_start;
	    }

	  যদি (!finish)
	    constructor_range_স্তূপ = range_স্তূপ;
	  চালু;
	}

      বিরতি;
    }

  constructor_range_স্তূপ = 0;

  যদি (raw_তথ্য && RAW_তথ্য_দৈর্ঘ্য (raw_তথ্য))
    {
      gcc_assert (!string_flag && !was_designated);
      মান.মান = raw_তথ্য;
      raw_তথ্য = NULL_বৃক্ষ;
      যাও retry;
    }
}

/* Build a complete asm-statement, whose components are a CV_QUALIFIER
   (guaranteed to be 'volatile' or null) and ARGS (represented using
   an ASM_EXPR node).  */
বৃক্ষ
build_asm_stmt (যৌক্তিক is_volatile, বৃক্ষ args)
{
  যদি (is_volatile)
    ASM_VOLATILE_P (args) = 1;
  ফেরত add_stmt (args);
}

/* Build an asm-expr, whose components are a STRING, some OUTPUTS,
   some INPUTS, and some CLOBBERS.  The latter three may be NULL.
   SIMPLE indicates whether there was anything at all after the
   string in the asm expression -- asm("blah") and asm("blah" : )
   are subtly different.  We use a ASM_EXPR node to represent this.
   LOC is the location of the asm, and IS_INLINE says whether this
   is asm inline.  */
বৃক্ষ
build_asm_রাশিমালা (location_t loc, বৃক্ষ string, বৃক্ষ outputs, বৃক্ষ inputs,
		বৃক্ষ clobbers, বৃক্ষ labels, যৌক্তিক simple, যৌক্তিক is_inline)
{
  বৃক্ষ লেজ;
  বৃক্ষ args;
  পূর্ণসংখ্যা i;
  ধ্রুবক অক্ষর *constraint;
  ধ্রুবক অক্ষর **oconstraints;
  যৌক্তিক allows_mem, allows_reg, is_inout;
  পূর্ণসংখ্যা ninputs, noutputs;

  ninputs = list_দৈর্ঘ্য (inputs);
  noutputs = list_দৈর্ঘ্য (outputs);
  oconstraints = (ধ্রুবক অক্ষর **) alloca (noutputs * আকার (ধ্রুবক অক্ষর *));

  string = resolve_asm_operand_names (string, outputs, inputs, labels);

  /* Remove output conversions that change the type but not the mode.  */
  জন্য (i = 0, লেজ = outputs; লেজ; ++i, লেজ = বৃক্ষ_CHAIN (লেজ))
    {
      বৃক্ষ output = বৃক্ষ_মান (লেজ);

      output = c_fully_fold (output, মিথ্যা, ফাঁকা, সত্য);

      /* ??? Really, this should not be here.  Users should be using a
	 proper lvalue, dammit.  But there's a long history of using casts
	 in the output operands.  In cases like longlong.h, this becomes a
	 primitive form of typechecking -- if the cast can be removed, then
	 the output operand had a type of the proper width; otherwise we'll
	 get an error.  Gross, but ...  */
      STRIP_NOPS (output);

      যদি (!lvalue_or_else (loc, output, lv_asm))
	output = error_mark_গ্রন্থি;

      যদি (output != error_mark_গ্রন্থি
	  && (বৃক্ষ_READONLY (output)
	      || TYPE_READONLY (বৃক্ষ_TYPE (output))
	      || (RECORD_OR_UNION_TYPE_P (বৃক্ষ_TYPE (output))
		  && C_TYPE_FIELDS_READONLY (বৃক্ষ_TYPE (output)))))
	readonly_error (loc, output, lv_asm);

      constraint = বৃক্ষ_STRING_POINTER (বৃক্ষ_মান (বৃক্ষ_PURPOSE (লেজ)));
      oconstraints[i] = constraint;

      যদি (parse_output_constraint (&constraint, i, ninputs, noutputs,
				   &allows_mem, &allows_reg, &is_inout,
				   nullptr))
	{
	  /* If the operand is going to end up in memory,
	     mark it addressable.  */
	  যদি (!allows_reg && !c_mark_addressable (output))
	    output = error_mark_গ্রন্থি;
	  যদি (!(!allows_reg && allows_mem)
	      && output != error_mark_গ্রন্থি
	      && VOID_TYPE_P (বৃক্ষ_TYPE (output)))
	    {
	      error_at (loc, "invalid use of void expression");
	      output = error_mark_গ্রন্থি;
	    }
	  যদি (allows_reg && current_function_decl == NULL_বৃক্ষ)
	    {
	      error_at (loc, "constraint allows registers outside of "
			     "a function");
	      output = error_mark_গ্রন্থি;
	    }
	}
      অন্যথা
	output = error_mark_গ্রন্থি;

      যদি (current_function_decl == NULL_বৃক্ষ && output != error_mark_গ্রন্থি)
	{
	  যদি (বৃক্ষ_SIDE_EFFECTS (output))
	    {
	      error_at (loc, "side-effects in output operand outside "
			     "of a function");
	      output = error_mark_গ্রন্থি;
	    }
	  অন্যথা
	    {
	      বৃক্ষ addr = build_unary_op (loc, ADDR_রাশিমালা, output, মিথ্যা);
	      যদি (addr == error_mark_গ্রন্থি)
		output = error_mark_গ্রন্থি;
	      অন্যথা যদি (!initializer_constant_valid_p (addr, বৃক্ষ_TYPE (addr)))
		{
		  error_at (loc, "output operand outside of a function is not "
				 "constant");
		  output = error_mark_গ্রন্থি;
		}
	    }
	}
      অন্যথা যদি (output != error_mark_গ্রন্থি && strstr (constraint, "-"))
	{
	  error_at (loc, "%<-%> modifier used inside of a function");
	  output = error_mark_গ্রন্থি;
	}

      বৃক্ষ_মান (লেজ) = output;
    }

  জন্য (i = 0, লেজ = inputs; লেজ; ++i, লেজ = বৃক্ষ_CHAIN (লেজ))
    {
      বৃক্ষ প্রবেশ;

      constraint = বৃক্ষ_STRING_POINTER (বৃক্ষ_মান (বৃক্ষ_PURPOSE (লেজ)));
      প্রবেশ = বৃক্ষ_মান (লেজ);

      যদি (parse_প্রবেশ_constraint (&constraint, i, ninputs, noutputs, 0,
				  oconstraints, &allows_mem, &allows_reg,
				  nullptr))
	{
	  /* If the operand is going to end up in memory,
	     mark it addressable.  */
	  যদি (!allows_reg && allows_mem)
	    {
	      প্রবেশ = c_fully_fold (প্রবেশ, মিথ্যা, ফাঁকা, সত্য);

	      /* Strip the nops as we allow this case.  FIXME, this really
		 should be rejected or made deprecated.  */
	      STRIP_NOPS (প্রবেশ);
	      যদি (!c_mark_addressable (প্রবেশ))
		প্রবেশ = error_mark_গ্রন্থি;
	    }
	  অন্যথা
	    {
	      প্রবেশ = c_fully_fold (convert_lvalue_to_rvalue (loc, প্রবেশ,
							      সত্য, মিথ্যা),
				    মিথ্যা, ফাঁকা);

	      যদি (প্রবেশ != error_mark_গ্রন্থি && VOID_TYPE_P (বৃক্ষ_TYPE (প্রবেশ)))
		{
		  error_at (loc, "invalid use of void expression");
		  প্রবেশ = error_mark_গ্রন্থি;
		}
	    }
	  যদি (allows_reg && current_function_decl == NULL_বৃক্ষ)
	    {
	      error_at (loc, "constraint allows registers outside of "
			     "a function");
	      প্রবেশ = error_mark_গ্রন্থি;
	    }
	  যদি (constraint[0] == ':' && প্রবেশ != error_mark_গ্রন্থি)
	    {
	      বৃক্ষ t = প্রবেশ;
	      STRIP_NOPS (t);
	      যদি (বৃক্ষ_CODE (t) != ADDR_রাশিমালা
		  || !(বৃক্ষ_CODE (বৃক্ষ_OPERAND (t, 0)) == FUNCTION_DECL
		       || (VAR_P (বৃক্ষ_OPERAND (t, 0))
			   && is_global_var (বৃক্ষ_OPERAND (t, 0)))))
		{
		  error_at (loc, "%<:%> constraint operand is not address "
				 "of a function or non-automatic variable");
		  প্রবেশ = error_mark_গ্রন্থি;
		}
	      অন্যথা যদি (বৃক্ষ_CODE (বৃক্ষ_OPERAND (t, 0)) == FUNCTION_DECL)
		suppress_warning (বৃক্ষ_OPERAND (t, 0), OPT_Wunused);
	    }
	}
      অন্যথা
	প্রবেশ = error_mark_গ্রন্থি;

      যদি (current_function_decl == NULL_বৃক্ষ && প্রবেশ != error_mark_গ্রন্থি)
	{
	  যদি (বৃক্ষ_SIDE_EFFECTS (প্রবেশ))
	    {
	      error_at (loc, "side-effects in input operand outside "
			     "of a function");
	      প্রবেশ = error_mark_গ্রন্থি;
	    }
	  অন্যথা
	    {
	      বৃক্ষ tem = প্রবেশ;
	      যদি (allows_mem && lvalue_p (প্রবেশ))
		tem = build_unary_op (loc, ADDR_রাশিমালা, প্রবেশ, মিথ্যা);
	      যদি (!initializer_constant_valid_p (tem, বৃক্ষ_TYPE (tem)))
		{
		  error_at (loc, "input operand outside of a function is not "
				 "constant");
		  প্রবেশ = error_mark_গ্রন্থি;
		}
	    }
	}
      অন্যথা যদি (প্রবেশ != error_mark_গ্রন্থি && strstr (constraint, "-"))
	{
	  error_at (loc, "%<-%> modifier used inside of a function");
	  প্রবেশ = error_mark_গ্রন্থি;
	}

      বৃক্ষ_মান (লেজ) = প্রবেশ;
    }

  args = build_stmt (loc, ASM_রাশিমালা, string, outputs, inputs, clobbers, labels);

  /* asm statements without outputs, including simple ones, are treated
     as volatile.  */
  ASM_BASIC_P (args) = simple;
  ASM_VOLATILE_P (args) = (noutputs == 0);
  ASM_INLINE_P (args) = is_inline;

  ফেরত args;
}

/* Generate a goto statement to LABEL.  LOC is the location of the
   GOTO.  */

বৃক্ষ
c_finish_goto_label (location_t loc, বৃক্ষ label)
{
  বৃক্ষ decl = lookup_label_for_goto (loc, label);
  যদি (!decl)
    ফেরত NULL_বৃক্ষ;
  বৃক্ষ_USED (decl) = 1;
  mark_decl_used (decl, মিথ্যা);
  {
    add_stmt (build_predict_রাশিমালা (PRED_GOTO, NOT_TAKEN));
    বৃক্ষ t = build1 (GOTO_রাশিমালা, void_type_গ্রন্থি, decl);
    SET_রাশিমালা_LOCATION (t, loc);
    ফেরত add_stmt (t);
  }
}

/* Generate a computed goto statement to EXPR.  LOC is the location of
   the GOTO.  */

বৃক্ষ
c_finish_goto_ptr (location_t loc, c_রাশিমালা val)
{
  বৃক্ষ রাশিমালা = val.মান;
  বৃক্ষ t;
  pedwarn (loc, OPT_Wpedantic, "ISO C forbids %<goto *expr;%>");
  যদি (রাশিমালা != error_mark_গ্রন্থি
      && !POINTER_TYPE_P (বৃক্ষ_TYPE (রাশিমালা))
      && !null_pointer_constant_p (রাশিমালা))
    {
      error_at (val.get_location (),
		"computed goto must be pointer type");
      রাশিমালা = build_zero_cst (ptr_type_গ্রন্থি);
    }
  রাশিমালা = c_fully_fold (রাশিমালা, মিথ্যা, ফাঁকা);
  রাশিমালা = convert (ptr_type_গ্রন্থি, রাশিমালা);
  t = build1 (GOTO_রাশিমালা, void_type_গ্রন্থি, রাশিমালা);
  SET_রাশিমালা_LOCATION (t, loc);
  ফেরত add_stmt (t);
}

/* Generate a C `return' statement.  RETVAL is the expression for what
   to return, or a null pointer for `return;' with no value.  LOC is
   the location of the return statement, or the location of the expression,
   if the statement has any.  If ORIGTYPE is not NULL_TREE, it
   is the original type of RETVAL.  MUSTTAIL_P indicates a musttail
   attribute.  */

বৃক্ষ
c_finish_return (location_t loc, বৃক্ষ retval, বৃক্ষ origtype, যৌক্তিক musttail_p)
{
  বৃক্ষ valtype = বৃক্ষ_TYPE (বৃক্ষ_TYPE (current_function_decl)), ret_stmt;
  যৌক্তিক no_warning = মিথ্যা;
  যৌক্তিক npc = মিথ্যা;

  /* Use the expansion point to handle cases such as returning NULL
     in a function returning void.  */
  location_t xloc = expansion_point_location_if_in_system_header (loc);

  যদি (বৃক্ষ_THIS_VOLATILE (current_function_decl))
    warning_at (xloc, 0,
		"function declared %<noreturn%> has a %<return%> statement");

  set_musttail_on_return (retval, xloc, musttail_p);

  যদি (retval)
    {
      বৃক্ষ semantic_type = NULL_বৃক্ষ;
      npc = null_pointer_constant_p (retval);
      যদি (বৃক্ষ_CODE (retval) == EXCESS_PRECISION_রাশিমালা)
	{
	  semantic_type = বৃক্ষ_TYPE (retval);
	  retval = বৃক্ষ_OPERAND (retval, 0);
	}
      retval = c_fully_fold (retval, মিথ্যা, ফাঁকা);
      যদি (semantic_type
	  && valtype != NULL_বৃক্ষ
	  && বৃক্ষ_CODE (valtype) != VOID_TYPE)
	retval = build1 (EXCESS_PRECISION_রাশিমালা, semantic_type, retval);
    }

  যদি (!retval)
    {
      current_function_returns_null = 1;
      যদি ((warn_return_type >= 0 || flag_isoc99)
	  && valtype != NULL_বৃক্ষ && বৃক্ষ_CODE (valtype) != VOID_TYPE)
	{
	  no_warning = সত্য;
	  যদি (emit_diagnostic (flag_isoc99
			       ? diagnostics::kind::permerror
			       : diagnostics::kind::warning,
			       loc, OPT_Wreturn_mismatch,
			       "%<return%> with no value,"
			       " in function returning non-void"))
	    inform (DECL_SOURCE_LOCATION (current_function_decl),
		    "declared here");
	}
    }
  অন্যথা যদি (valtype == NULL_বৃক্ষ || VOID_TYPE_P (valtype))
    {
      current_function_returns_null = 1;
      যৌক্তিক warned_here;
      যদি (বৃক্ষ_CODE (বৃক্ষ_TYPE (retval)) != VOID_TYPE)
	warned_here = permerror_opt
	  (xloc, OPT_Wreturn_mismatch,
	   "%<return%> with a value, in function returning void");
      অন্যথা
	warned_here = pedwarn
	  (xloc, OPT_Wpedantic, "ISO C forbids "
	   "%<return%> with expression, in function returning void");
      যদি (warned_here)
	inform (DECL_SOURCE_LOCATION (current_function_decl),
		"declared here");
    }
  অন্যথা
    {
      বৃক্ষ t = convert_for_assignment (loc, UNKNOWN_LOCATION, valtype,
				       retval, origtype, ic_return,
				       npc, NULL_বৃক্ষ, NULL_বৃক্ষ, 0);
      বৃক্ষ res = DECL_ফলাফল (current_function_decl);
      বৃক্ষ inner;
      যৌক্তিক save;

      current_function_returns_মান = 1;
      যদি (t == error_mark_গ্রন্থি)
	{
	  /* Suppress -Wreturn-type for this function.  */
	  যদি (warn_return_type)
	    suppress_warning (current_function_decl, OPT_Wreturn_type);
	  ফেরত NULL_বৃক্ষ;
	}

      save = in_late_দ্বিমিক_op;
      যদি (C_BOOLEAN_TYPE_P (বৃক্ষ_TYPE (res))
	  || বৃক্ষ_CODE (বৃক্ষ_TYPE (res)) == COMPLEX_TYPE
	  || (SCALAR_FLOAT_TYPE_P (বৃক্ষ_TYPE (t))
	      && (বৃক্ষ_CODE (বৃক্ষ_TYPE (res)) == INTEGER_TYPE
		  || বৃক্ষ_CODE (বৃক্ষ_TYPE (res)) == ENUMERAL_TYPE)
	      && sanitize_flags_p (SANITIZE_FLOAT_CAST)))
        in_late_দ্বিমিক_op = সত্য;
      inner = t = convert (বৃক্ষ_TYPE (res), t);
      in_late_দ্বিমিক_op = save;

      /* Strip any conversions, additions, and subtractions, and see if
	 we are returning the address of a local variable.  Warn if so.  */
      যখন (1)
	{
	  নির্বাচন (বৃক্ষ_CODE (inner))
	    {
	    CASE_CONVERT:
	    ক্ষেত্র NON_LVALUE_রাশিমালা:
	    ক্ষেত্র PLUS_রাশিমালা:
	    ক্ষেত্র POINTER_PLUS_রাশিমালা:
	      inner = বৃক্ষ_OPERAND (inner, 0);
	      চালু;

	    ক্ষেত্র MINUS_রাশিমালা:
	      /* If the second operand of the MINUS_EXPR has a pointer
		 type (or is converted from it), this may be valid, so
		 don't give a warning.  */
	      {
		বৃক্ষ op1 = বৃক্ষ_OPERAND (inner, 1);

		যখন (!POINTER_TYPE_P (বৃক্ষ_TYPE (op1))
		       && (CONVERT_রাশিমালা_P (op1)
			   || বৃক্ষ_CODE (op1) == NON_LVALUE_রাশিমালা))
		  op1 = বৃক্ষ_OPERAND (op1, 0);

		যদি (POINTER_TYPE_P (বৃক্ষ_TYPE (op1)))
		  বিরতি;

		inner = বৃক্ষ_OPERAND (inner, 0);
		চালু;
	      }

	    ক্ষেত্র ADDR_রাশিমালা:
	      inner = বৃক্ষ_OPERAND (inner, 0);

	      যখন (REFERENCE_CLASS_P (inner)
		     && !INDIRECT_REF_P (inner))
		inner = বৃক্ষ_OPERAND (inner, 0);

	      যদি (DECL_P (inner)
		  && !DECL_EXTERNAL (inner)
		  && DECL_CONTEXT (inner) == current_function_decl
		  && POINTER_TYPE_P (বৃক্ষ_TYPE (বৃক্ষ_TYPE (current_function_decl))))
		{
		  যদি (বৃক্ষ_CODE (inner) == LABEL_DECL)
		    warning_at (loc, OPT_Wreturn_local_addr,
				"function returns address of label");
		  অন্যথা যদি (বৃক্ষ_CODE (inner) == FUNCTION_DECL
			   && (C_FUNC_NONLOCAL_CONTEXT (inner)
			       || !DECL_INITIAL (inner)))
		    warning_at (loc, OPT_Wreturn_local_addr,
				"function returns address of nested function "
				"referencing local context");
		  অন্যথা যদি (বৃক্ষ_CODE (inner) != FUNCTION_DECL
			   && !বৃক্ষ_STATIC (inner))
		    {
		      warning_at (loc, OPT_Wreturn_local_addr,
				  "function returns address of local variable");
		      বৃক্ষ zero = build_zero_cst (বৃক্ষ_TYPE (res));
		      t = build2 (COMPOUND_রাশিমালা, বৃক্ষ_TYPE (res), t, zero);
		    }
		}
	      বিরতি;

	    পূর্বনির্ধারিত:
	      বিরতি;
	    }

	  বিরতি;
	}

      retval = build2 (MODIFY_রাশিমালা, বৃক্ষ_TYPE (res), res, t);
      SET_রাশিমালা_LOCATION (retval, loc);

      যদি (warn_sequence_point)
	verify_sequence_points (retval);
    }

  ret_stmt = build_stmt (loc, RETURN_রাশিমালা, retval);
  যদি (no_warning)
    suppress_warning (ret_stmt, OPT_Wreturn_type);
  ফেরত add_stmt (ret_stmt);
}

কাঠামো c_switch {
  /* The SWITCH_STMT being built.  */
  বৃক্ষ switch_stmt;

  /* The original type of the testing expression, i.e. before the
     default conversion is applied.  */
  বৃক্ষ orig_type;

  /* A splay-tree mapping the low element of a case range to the high
     element, or NULL_TREE if there is no high element.  Used to
     determine whether or not a new case label duplicates an old case
     label.  We need a tree, rather than simply a hash table, because
     of the GNU case range extension.  */
  splay_বৃক্ষ cases;

  /* The bindings at the point of the switch.  This is used for
     warnings crossing decls when branching to a case label.  */
  কাঠামো c_spot_bindings *bindings;

  /* Whether the switch includes any break statements.  */
  যৌক্তিক break_stmt_seen_p;

  /* The next node on the stack.  */
  কাঠামো c_switch *পরবর্তী;

  /* Remember whether the controlling expression had boolean type
     before integer promotions for the sake of -Wswitch-bool.  */
  যৌক্তিক bool_cond_p;
};

/* A stack of the currently active switch statements.  The innermost
   switch statement is on the top of the stack.  There is no need to
   mark the stack for garbage collection because it is only active
   during the processing of the body of a function, and we never
   collect at that point.  */

কাঠামো c_switch *c_switch_স্তূপ;

/* Start a C switch statement, testing expression EXP.  Return the new
   SWITCH_STMT.  SWITCH_LOC is the location of the `switch'.
   SWITCH_COND_LOC is the location of the switch's condition.
   EXPLICIT_CAST_P is true if the expression EXP has an explicit cast.  */

বৃক্ষ
c_start_switch (location_t switch_loc,
		location_t switch_cond_loc,
		বৃক্ষ exp, যৌক্তিক explicit_cast_p, বৃক্ষ switch_name)
{
  বৃক্ষ orig_type = error_mark_গ্রন্থি;
  যৌক্তিক bool_cond_p = মিথ্যা;
  কাঠামো c_switch *cs;

  যদি (exp != error_mark_গ্রন্থি)
    {
      orig_type = বৃক্ষ_TYPE (exp);

      যদি (!INTEGRAL_TYPE_P (orig_type))
	{
	  যদি (orig_type != error_mark_গ্রন্থি)
	    {
	      error_at (switch_cond_loc, "switch quantity not an integer");
	      orig_type = error_mark_গ্রন্থি;
	    }
	  exp = integer_zero_গ্রন্থি;
	}
      অন্যথা
	{
	  বৃক্ষ type = TYPE_MAIN_VARIANT (orig_type);
	  বৃক্ষ e = exp;

	  /* Warn if the condition has boolean value.  */
	  যখন (বৃক্ষ_CODE (e) == COMPOUND_রাশিমালা)
	    e = বৃক্ষ_OPERAND (e, 1);

	  যদি ((C_BOOLEAN_TYPE_P (type)
	       || truth_মান_p (বৃক্ষ_CODE (e)))
	      /* Explicit cast to int suppresses this warning.  */
	      && !(বৃক্ষ_CODE (type) == INTEGER_TYPE
		   && explicit_cast_p))
	    bool_cond_p = সত্য;

	  যদি (!in_system_header_at (প্রবেশ_location)
	      && (type == long_integer_type_গ্রন্থি
		  || type == long_unsigned_type_গ্রন্থি))
	    warning_at (switch_cond_loc,
			OPT_Wtraditional, "%<long%> switch expression not "
			"converted to %<int%> in ISO C");

	  exp = c_fully_fold (exp, মিথ্যা, ফাঁকা);
	  exp = default_conversion (exp);

	  যদি (warn_sequence_point)
	    verify_sequence_points (exp);
	}
    }

  /* Add this new SWITCH_STMT to the stack.  */
  cs = XNEW (কাঠামো c_switch);
  cs->switch_stmt = build_stmt (switch_loc, SWITCH_STMT, exp,
				NULL_বৃক্ষ, orig_type, NULL_বৃক্ষ, switch_name);
  cs->orig_type = orig_type;
  cs->cases = splay_বৃক্ষ_new (case_compare, ফাঁকা, ফাঁকা);
  cs->bindings = c_get_switch_bindings ();
  cs->break_stmt_seen_p = মিথ্যা;
  cs->bool_cond_p = bool_cond_p;
  cs->পরবর্তী = c_switch_স্তূপ;
  c_switch_স্তূপ = cs;

  ফেরত add_stmt (cs->switch_stmt);
}

/* Process a case label at location LOC, with attributes ATTRS.  */

বৃক্ষ
do_case (location_t loc, বৃক্ষ নিচের_মান, বৃক্ষ উপরের_মান, বৃক্ষ attrs)
{
  বৃক্ষ label = NULL_বৃক্ষ;

  যদি (নিচের_মান && বৃক্ষ_CODE (নিচের_মান) != INTEGER_CST)
    {
      নিচের_মান = c_fully_fold (নিচের_মান, মিথ্যা, ফাঁকা);
      যদি (বৃক্ষ_CODE (নিচের_মান) == INTEGER_CST)
	pedwarn (loc, OPT_Wpedantic,
		 "case label is not an integer constant expression");
    }

  যদি (উপরের_মান && বৃক্ষ_CODE (উপরের_মান) != INTEGER_CST)
    {
      উপরের_মান = c_fully_fold (উপরের_মান, মিথ্যা, ফাঁকা);
      যদি (বৃক্ষ_CODE (উপরের_মান) == INTEGER_CST)
	pedwarn (প্রবেশ_location, OPT_Wpedantic,
		 "case label is not an integer constant expression");
    }

  যদি (c_switch_স্তূপ == ফাঁকা)
    {
      যদি (নিচের_মান)
	error_at (loc, "case label not within a switch statement");
      অন্যথা
	error_at (loc, "%<default%> label not within a switch statement");
      ফেরত NULL_বৃক্ষ;
    }

  যদি (c_check_switch_jump_warnings (c_switch_স্তূপ->bindings,
				    রাশিমালা_LOCATION (c_switch_স্তূপ->switch_stmt),
				    loc))
    ফেরত NULL_বৃক্ষ;

  label = c_add_case_label (loc, c_switch_স্তূপ->cases,
			    SWITCH_STMT_COND (c_switch_স্তূপ->switch_stmt),
			    নিচের_মান, উপরের_মান, attrs);
  যদি (label == error_mark_গ্রন্থি)
    label = NULL_বৃক্ষ;
  ফেরত label;
}

/* Finish the switch statement.  TYPE is the original type of the
   controlling expression of the switch, or NULL_TREE.  */

শূন্য
c_finish_switch (বৃক্ষ body, বৃক্ষ type)
{
  কাঠামো c_switch *cs = c_switch_স্তূপ;
  location_t switch_location;

  SWITCH_STMT_BODY (cs->switch_stmt) = body;

  /* Emit warnings as needed.  */
  switch_location = রাশিমালা_LOCATION (cs->switch_stmt);
  c_do_switch_warnings (cs->cases, switch_location,
			type ? type : SWITCH_STMT_TYPE (cs->switch_stmt),
			SWITCH_STMT_COND (cs->switch_stmt), cs->bool_cond_p);
  যদি (c_switch_covers_all_cases_p (cs->cases,
				   SWITCH_STMT_TYPE (cs->switch_stmt)))
    SWITCH_STMT_ALL_CASES_P (cs->switch_stmt) = 1;
  SWITCH_STMT_NO_BREAK_P (cs->switch_stmt) = !cs->break_stmt_seen_p;

  /* Pop the stack.  */
  c_switch_স্তূপ = cs->পরবর্তী;
  splay_বৃক্ষ_delete (cs->cases);
  c_release_switch_bindings (cs->bindings);
  XDELETE (cs);
}

/* Emit an if statement.  IF_LOCUS is the location of the 'if'.  COND,
   THEN_BLOCK and ELSE_BLOCK are expressions to be used; ELSE_BLOCK
   may be null.  */

শূন্য
c_finish_if_stmt (location_t if_locus, বৃক্ষ cond, বৃক্ষ then_block,
		  বৃক্ষ else_block)
{
  বৃক্ষ stmt;

  stmt = build3 (COND_রাশিমালা, void_type_গ্রন্থি, cond, then_block, else_block);
  SET_রাশিমালা_LOCATION (stmt, if_locus);
  add_stmt (stmt);
}

বৃক্ষ
c_finish_bc_stmt (location_t loc, বৃক্ষ label, যৌক্তিক is_break, বৃক্ষ name)
{
  /* In switch statements break is sometimes stylistically used after
     a return statement.  This can lead to spurious warnings about
     control reaching the end of a non-void function when it is
     inlined.  Note that we are calling block_may_fallthru with
     language specific tree nodes; this works because
     block_may_fallthru returns true when given something it does not
     understand.  */
  যৌক্তিক skip = !block_may_fallthru (cur_stmt_list);

  যদি (is_break)
    নির্বাচন (in_statement & ~IN_NAMED_STMT)
      {
      ক্ষেত্র 0:
	error_at (loc, "break statement not within loop or switch");
	ফেরত NULL_বৃক্ষ;
      ক্ষেত্র IN_OMP_BLOCK:
	error_at (loc, "invalid exit from OpenMP structured block");
	ফেরত NULL_বৃক্ষ;
      ক্ষেত্র IN_OMP_FOR:
	error_at (loc, "break statement used with OpenMP for loop");
	ফেরত NULL_বৃক্ষ;
      ক্ষেত্র IN_ITERATION_STMT:
      ক্ষেত্র IN_OBJC_FOREACH:
	বিরতি;
      পূর্বনির্ধারিত:
	gcc_assert (in_statement & IN_SWITCH_STMT);
	c_switch_স্তূপ->break_stmt_seen_p = সত্য;
	বিরতি;
      }
  অন্যথা
    নির্বাচন (in_statement & ~(IN_SWITCH_STMT | IN_NAMED_STMT))
      {
      ক্ষেত্র 0:
	error_at (loc, "continue statement not within a loop");
	ফেরত NULL_বৃক্ষ;
      ক্ষেত্র IN_OMP_BLOCK:
	error_at (loc, "invalid exit from OpenMP structured block");
	ফেরত NULL_বৃক্ষ;
      ক্ষেত্র IN_ITERATION_STMT:
      ক্ষেত্র IN_OMP_FOR:
      ক্ষেত্র IN_OBJC_FOREACH:
	বিরতি;
      পূর্বনির্ধারিত:
	gcc_unreachable ();
      }

  যদি (skip)
    ফেরত NULL_বৃক্ষ;
  অন্যথা যদি ((in_statement & IN_OBJC_FOREACH)
	   && !(is_break && (in_statement & IN_SWITCH_STMT))
	   && name == NULL_বৃক্ষ)
    {
      /* The foreach expander produces low-level code using gotos instead
	 of a structured loop construct.  */
      gcc_assert (label);
      ফেরত add_stmt (build_stmt (loc, GOTO_রাশিমালা, label));
    }
  অন্যথা যদি (name && C_DECL_LOOP_NAME (name) && C_DECL_SWITCH_NAME (name))
    {
      label = DECL_CHAIN (name);
      যদি (!is_break)
	label = DECL_CHAIN (label);
      /* Foreach expander from some outer level.  */
      ফেরত add_stmt (build_stmt (loc, GOTO_রাশিমালা, label));
    }
  ফেরত add_stmt (build_stmt (loc, is_break ? BREAK_STMT : CONTINUE_STMT,
			       name));
}

/* A helper routine for c_process_expr_stmt and c_finish_stmt_expr.  */

স্থির শূন্য
emit_side_effect_warnings (location_t loc, বৃক্ষ রাশিমালা)
{
  maybe_warn_nodiscard (loc, রাশিমালা);
  যদি (!warn_unused_মান)
    ফেরত;
  যদি (রাশিমালা == error_mark_গ্রন্থি)
    ;
  অন্যথা যদি (!বৃক্ষ_SIDE_EFFECTS (রাশিমালা))
    {
      যদি (!VOID_TYPE_P (বৃক্ষ_TYPE (রাশিমালা))
	  && !warning_suppressed_p (রাশিমালা, OPT_Wunused_মান))
	warning_at (loc, OPT_Wunused_মান, "statement with no effect");
    }
  অন্যথা যদি (বৃক্ষ_CODE (রাশিমালা) == COMPOUND_রাশিমালা)
    {
      বৃক্ষ r = রাশিমালা;
      location_t cloc = loc;
      যখন (বৃক্ষ_CODE (r) == COMPOUND_রাশিমালা)
	{
	  যদি (রাশিমালা_HAS_LOCATION (r))
	    cloc = রাশিমালা_LOCATION (r);
	  r = বৃক্ষ_OPERAND (r, 1);
	}
      যদি (!বৃক্ষ_SIDE_EFFECTS (r)
	  && !VOID_TYPE_P (বৃক্ষ_TYPE (r))
	  && !CONVERT_রাশিমালা_P (r)
	  && !warning_suppressed_p (r, OPT_Wunused_মান)
	  && !warning_suppressed_p (রাশিমালা, OPT_Wunused_মান))
	warning_at (cloc, OPT_Wunused_মান,
		    "right-hand operand of comma expression has no effect");
    }
  অন্যথা
    warn_if_unused_মান (রাশিমালা, loc);
}

/* Process an expression as if it were a complete statement.  Emit
   diagnostics, but do not call ADD_STMT.  LOC is the location of the
   statement.  */

বৃক্ষ
c_process_রাশিমালা_stmt (location_t loc, বৃক্ষ রাশিমালা)
{
  বৃক্ষ exprv;

  যদি (!রাশিমালা)
    ফেরত NULL_বৃক্ষ;

  রাশিমালা = c_fully_fold (রাশিমালা, মিথ্যা, ফাঁকা);

  যদি (warn_sequence_point)
    verify_sequence_points (রাশিমালা);

  যদি (বৃক্ষ_TYPE (রাশিমালা) != error_mark_গ্রন্থি
      && !COMPLETE_OR_VOID_TYPE_P (বৃক্ষ_TYPE (রাশিমালা))
      && বৃক্ষ_CODE (বৃক্ষ_TYPE (রাশিমালা)) != ARRAY_TYPE)
    error_at (loc, "expression statement has incomplete type");

  /* If we're not processing a statement expression, warn about unused values.
     Warnings for statement expressions will be emitted later, once we figure
     out which is the result.  */
  যদি (!STATEMENT_LIST_STMT_রাশিমালা (cur_stmt_list)
      && (warn_unused_মান || warn_unused_ফলাফল))
    emit_side_effect_warnings (রাশিমালা_LOC_OR_LOC (রাশিমালা, loc), রাশিমালা);

  exprv = রাশিমালা;
  যখন (বৃক্ষ_CODE (exprv) == COMPOUND_রাশিমালা)
    exprv = বৃক্ষ_OPERAND (exprv, 1);
  যখন (CONVERT_রাশিমালা_P (exprv))
    exprv = বৃক্ষ_OPERAND (exprv, 0);
  যদি (DECL_P (exprv)
      || handled_component_p (exprv)
      || বৃক্ষ_CODE (exprv) == ADDR_রাশিমালা)
    mark_exp_read (exprv);

  /* If the expression is not of a type to which we cannot assign a line
     number, wrap the thing in a no-op NOP_EXPR.  */
  যদি (DECL_P (রাশিমালা) || CONSTANT_CLASS_P (রাশিমালা))
    {
      রাশিমালা = build1 (NOP_রাশিমালা, বৃক্ষ_TYPE (রাশিমালা), রাশিমালা);
      SET_রাশিমালা_LOCATION (রাশিমালা, loc);
    }

  ফেরত রাশিমালা;
}

/* Emit an expression as a statement.  LOC is the location of the
   expression.  */

বৃক্ষ
c_finish_রাশিমালা_stmt (location_t loc, বৃক্ষ রাশিমালা)
{
  যদি (রাশিমালা)
    ফেরত add_stmt (c_process_রাশিমালা_stmt (loc, রাশিমালা));
  অন্যথা
    ফেরত ফাঁকা;
}

/* Do the opposite and emit a statement as an expression.  To begin,
   create a new binding level and return it.  */

বৃক্ষ
c_begin_stmt_রাশিমালা (শূন্য)
{
  বৃক্ষ ret;

  /* We must force a BLOCK for this level so that, if it is not expanded
     later, there is a way to turn off the entire subtree of blocks that
     are contained in it.  */
  keep_পরবর্তী_level ();
  ret = c_begin_compound_stmt (সত্য);

  c_bindings_start_stmt_রাশিমালা (c_switch_স্তূপ == ফাঁকা
			      ? ফাঁকা
			      : c_switch_স্তূপ->bindings);

  /* Mark the current statement list as belonging to a statement list.  */
  STATEMENT_LIST_STMT_রাশিমালা (ret) = 1;

  ফেরত ret;
}

/* LOC is the location of the compound statement to which this body
   belongs.  */

বৃক্ষ
c_finish_stmt_রাশিমালা (location_t loc, বৃক্ষ body)
{
  বৃক্ষ last, type, tmp, val;
  বৃক্ষ *last_p;

  body = c_end_compound_stmt (loc, body, সত্য);

  c_bindings_end_stmt_রাশিমালা (c_switch_স্তূপ == ফাঁকা
			    ? ফাঁকা
			    : c_switch_স্তূপ->bindings);

  /* Locate the last statement in BODY.  See c_end_compound_stmt
     about always returning a BIND_EXPR.  */
  last_p = &BIND_রাশিমালা_BODY (body);
  last = BIND_রাশিমালা_BODY (body);

 continue_searching:
  যদি (বৃক্ষ_CODE (last) == STATEMENT_LIST)
    {
      বৃক্ষ_stmt_iterator l = tsi_last (last);

      যখন (!tsi_end_p (l) && বৃক্ষ_CODE (tsi_stmt (l)) == DEBUG_BEGIN_STMT)
	tsi_পূর্ব (&l);

      /* This can happen with degenerate cases like ({ }).  No value.  */
      যদি (tsi_end_p (l))
	ফেরত body;

      /* If we're supposed to generate side effects warnings, process
	 all of the statements except the last.  */
      যদি (warn_unused_মান || warn_unused_ফলাফল)
	{
	  জন্য (বৃক্ষ_stmt_iterator i = tsi_start (last);
	       tsi_stmt (i) != tsi_stmt (l); tsi_পরবর্তী (&i))
	    {
	      location_t tloc;
	      বৃক্ষ t = tsi_stmt (i);

	      tloc = রাশিমালা_HAS_LOCATION (t) ? রাশিমালা_LOCATION (t) : loc;
	      emit_side_effect_warnings (tloc, t);
	    }
	}
      last_p = tsi_stmt_ptr (l);
      last = *last_p;
    }

  /* If the end of the list is exception related, then the list was split
     by a call to push_cleanup.  Continue searching.  */
  যদি (বৃক্ষ_CODE (last) == TRY_FINALLY_রাশিমালা
      || বৃক্ষ_CODE (last) == TRY_CATCH_রাশিমালা)
    {
      last_p = &বৃক্ষ_OPERAND (last, 0);
      last = *last_p;
      যাও continue_searching;
    }

  যদি (last == error_mark_গ্রন্থি)
    ফেরত last;

  /* In the case that the BIND_EXPR is not necessary, return the
     expression out from inside it.  */
  যদি ((last == BIND_রাশিমালা_BODY (body)
       /* Skip nested debug stmts.  */
       || last == রাশিমালা_first (BIND_রাশিমালা_BODY (body)))
      && BIND_রাশিমালা_VARS (body) == ফাঁকা)
    {
      /* Even if this looks constant, do not allow it in a constant
	 expression.  */
      last = c_wrap_maybe_const (last, সত্য);
      /* Do not warn if the return value of a statement expression is
	 unused.  */
      suppress_warning (last, OPT_Wunused);
      ফেরত last;
    }

  /* Extract the type of said expression.  */
  type = বৃক্ষ_TYPE (last);

  /* If we're not returning a value at all, then the BIND_EXPR that
     we already have is a fine expression to return.  */
  যদি (!type || VOID_TYPE_P (type))
    ফেরত body;

  /* Now that we've located the expression containing the value, it seems
     silly to make voidify_wrapper_expr repeat the process.  Create a
     temporary of the appropriate type and stick it in a TARGET_EXPR.  */
  tmp = create_tmp_var_raw (type);

  /* Unwrap a no-op NOP_EXPR as added by c_finish_expr_stmt.  This avoids
     tree_expr_nonnegative_p giving up immediately.  */
  val = last;
  যদি (বৃক্ষ_CODE (val) == NOP_রাশিমালা
      && বৃক্ষ_TYPE (val) == বৃক্ষ_TYPE (বৃক্ষ_OPERAND (val, 0)))
    val = বৃক্ষ_OPERAND (val, 0);

  *last_p = build2 (MODIFY_রাশিমালা, void_type_গ্রন্থি, tmp, val);
  SET_রাশিমালা_LOCATION (*last_p, রাশিমালা_LOCATION (last));

  {
    বৃক্ষ t = build4 (TARGET_রাশিমালা, type, tmp, body, NULL_বৃক্ষ, NULL_বৃক্ষ);
    SET_রাশিমালা_LOCATION (t, loc);
    ফেরত t;
  }
}

/* Begin and end compound statements.  This is as simple as pushing
   and popping new statement lists from the tree.  */

বৃক্ষ
c_begin_compound_stmt (যৌক্তিক do_scope)
{
  বৃক্ষ stmt = ঠেলো_stmt_list ();
  যদি (do_scope)
    ঠেলো_scope ();
  ফেরত stmt;
}

/* End a compound statement.  STMT is the statement.  LOC is the
   location of the compound statement-- this is usually the location
   of the opening brace.  */

বৃক্ষ
c_end_compound_stmt (location_t loc, বৃক্ষ stmt, যৌক্তিক do_scope)
{
  বৃক্ষ block = ফাঁকা;

  যদি (do_scope)
    {
      যদি (c_dialect_objc ())
	objc_clear_super_receiver ();
      block = বের_করো_scope ();
    }

  stmt = বের_করো_stmt_list (stmt);
  stmt = c_build_bind_রাশিমালা (loc, block, stmt);

  /* If this compound statement is nested immediately inside a statement
     expression, then force a BIND_EXPR to be created.  Otherwise we'll
     do the wrong thing for ({ { 1; } }) or ({ 1; { } }).  In particular,
     STATEMENT_LISTs merge, and thus we can lose track of what statement
     was really last.  */
  যদি (building_stmt_list_p ()
      && STATEMENT_LIST_STMT_রাশিমালা (cur_stmt_list)
      && বৃক্ষ_CODE (stmt) != BIND_রাশিমালা)
    {
      stmt = build3 (BIND_রাশিমালা, void_type_গ্রন্থি, ফাঁকা, stmt, ফাঁকা);
      বৃক্ষ_SIDE_EFFECTS (stmt) = 1;
      SET_রাশিমালা_LOCATION (stmt, loc);
    }

  ফেরত stmt;
}

/* Queue a cleanup.  CLEANUP is an expression/statement to be executed
   when the current scope is exited.  EH_ONLY is true when this is not
   meant to apply to normal control flow transfer.  */

শূন্য
ঠেলো_cleanup (বৃক্ষ decl, বৃক্ষ cleanup, যৌক্তিক eh_only)
{
  গণনা বৃক্ষ_code code;
  বৃক্ষ stmt, list;
  যৌক্তিক stmt_রাশিমালা;

  code = eh_only ? TRY_CATCH_রাশিমালা : TRY_FINALLY_রাশিমালা;
  stmt = build_stmt (DECL_SOURCE_LOCATION (decl), code, ফাঁকা, cleanup);
  add_stmt (stmt);
  stmt_রাশিমালা = STATEMENT_LIST_STMT_রাশিমালা (cur_stmt_list);
  list = ঠেলো_stmt_list ();
  বৃক্ষ_OPERAND (stmt, 0) = list;
  STATEMENT_LIST_STMT_রাশিমালা (list) = stmt_রাশিমালা;
}

/* Build a vector comparison of ARG0 and ARG1 using CODE opcode
   into a value of TYPE type.  Comparison is done via VEC_COND_EXPR.  */

স্থির বৃক্ষ
build_vec_cmp (বৃক্ষ_code code, বৃক্ষ type,
	       বৃক্ষ arg0, বৃক্ষ arg1)
{
  বৃক্ষ zero_vec = build_zero_cst (type);
  বৃক্ষ minus_one_vec = build_minus_one_cst (type);
  বৃক্ষ cmp_type = truth_type_for (বৃক্ষ_TYPE (arg0));
  বৃক্ষ cmp = build2 (code, cmp_type, arg0, arg1);
  ফেরত build3 (VEC_COND_রাশিমালা, type, cmp, minus_one_vec, zero_vec);
}

/* Possibly warn about an address of OP never being NULL in a comparison
   operation CODE involving null.  */

স্থির শূন্য
maybe_warn_for_null_address (location_t loc, বৃক্ষ op, বৃক্ষ_code code)
{
  /* Prevent warnings issued for macro expansion.  */
  যদি (!warn_address
      || warning_suppressed_p (op, OPT_Waddress)
      || from_macro_expansion_at (loc))
    ফেরত;

  যদি (বৃক্ষ_CODE (op) == NOP_রাশিমালা)
    {
      /* Allow casts to intptr_t to suppress the warning.  */
      বৃক্ষ type = বৃক্ষ_TYPE (op);
      যদি (বৃক্ষ_CODE (type) == INTEGER_TYPE)
	ফেরত;
      op = বৃক্ষ_OPERAND (op, 0);
    }

  যদি (বৃক্ষ_CODE (op) == POINTER_PLUS_রাশিমালা)
    {
      /* Allow a cast to void* to suppress the warning.  */
      বৃক্ষ type = বৃক্ষ_TYPE (বৃক্ষ_TYPE (op));
      যদি (VOID_TYPE_P (type))
	ফেরত;

      /* Adding any value to a null pointer, including zero, is undefined
	 in C.  This includes the expression &p[0] where p is the null
	 pointer, although &p[0] will have been folded to p by this point
	 and so not diagnosed.  */
      যদি (code == EQ_রাশিমালা)
	warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<false%> "
		    "for the pointer operand in %qE must not be NULL",
		    op);
      অন্যথা
	warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<true%> "
		    "for the pointer operand in %qE must not be NULL",
		    op);

      ফেরত;
    }

  যদি (বৃক্ষ_CODE (op) != ADDR_রাশিমালা)
    ফেরত;

  op = বৃক্ষ_OPERAND (op, 0);

  যদি (বৃক্ষ_CODE (op) == IMAGPART_রাশিমালা
      || বৃক্ষ_CODE (op) == REALPART_রাশিমালা)
    {
      /* The address of either complex part may not be null.  */
      যদি (code == EQ_রাশিমালা)
	warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<false%> "
		    "for the address of %qE will never be NULL",
		    op);
      অন্যথা
	warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<true%> "
		    "for the address of %qE will never be NULL",
		    op);
      ফেরত;
    }

  /* Set to true in the loop below if OP dereferences is operand.
     In such a case the ultimate target need not be a decl for
     the null [in]equality test to be constant.  */
  যৌক্তিক deref = মিথ্যা;

  /* Get the outermost array or object, or member.  */
  যখন (handled_component_p (op))
    {
      যদি (বৃক্ষ_CODE (op) == COMPONENT_REF)
	{
	  /* Get the member (its address is never null).  */
	  op = বৃক্ষ_OPERAND (op, 1);
	  বিরতি;
	}

      /* Get the outer array/object to refer to in the warning.  */
      op = বৃক্ষ_OPERAND (op, 0);
      deref = সত্য;
    }

  যদি ((!deref && !decl_with_nonnull_addr_p (op))
      || from_macro_expansion_at (loc))
    ফেরত;

  যৌক্তিক w;
  যদি (code == EQ_রাশিমালা)
    w = warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<false%> "
		    "for the address of %qE will never be NULL",
		    op);
  অন্যথা
    w = warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<true%> "
		    "for the address of %qE will never be NULL",
		    op);

  যদি (w && DECL_P (op))
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

বৃক্ষ
build_দ্বিমিক_op (location_t location, গণনা বৃক্ষ_code code,
		 বৃক্ষ orig_op0, বৃক্ষ orig_op1, যৌক্তিক convert_p)
{
  বৃক্ষ type0, type1, orig_type0, orig_type1;
  বৃক্ষ eptype;
  গণনা বৃক্ষ_code code0, code1;
  বৃক্ষ op0, op1;
  বৃক্ষ ret = error_mark_গ্রন্থি;
  ধ্রুবক অক্ষর *invalid_op_diag;
  যৌক্তিক op0_int_operands, op1_int_operands;
  যৌক্তিক int_const, int_const_or_overflow, int_operands;

  /* Expression code to give to the expression when it is built.
     Normally this is CODE, which is what the caller asked for,
     but in some special cases we change it.  */
  গণনা বৃক্ষ_code resultcode = code;

  /* Data type in which the computation is to be performed.
     In the simplest cases this is the common type of the arguments.  */
  বৃক্ষ ফলাফল_type = ফাঁকা;

  /* When the computation is in excess precision, the type of the
     final EXCESS_PRECISION_EXPR.  */
  বৃক্ষ semantic_ফলাফল_type = ফাঁকা;

  /* Nonzero means operands have already been type-converted
     in whatever way is necessary.
     Zero means they need to be converted to RESULT_TYPE.  */
  পূর্ণসংখ্যা converted = 0;

  /* Nonzero means create the expression with this type, rather than
     RESULT_TYPE.  */
  বৃক্ষ build_type = NULL_বৃক্ষ;

  /* Nonzero means after finally constructing the expression
     convert it to this type.  */
  বৃক্ষ final_type = NULL_বৃক্ষ;

  /* Nonzero if this is an operation like MIN or MAX which can
     safely be computed in short if both args are promoted shorts.
     Also implies COMMON.
     -1 indicates a bitwise operation; this makes a difference
     in the exact conditions for when it is safe to do the operation
     in a narrower mode.  */
  পূর্ণসংখ্যা shorten = 0;

  /* Nonzero if this is a comparison operation;
     if both args are promoted shorts, compare the original shorts.
     Also implies COMMON.  */
  পূর্ণসংখ্যা short_compare = 0;

  /* Nonzero if this is a right-shift operation, which can be computed on the
     original short and then promoted if the operand is a promoted short.  */
  পূর্ণসংখ্যা short_shift = 0;

  /* Nonzero means set RESULT_TYPE to the common type of the args.  */
  পূর্ণসংখ্যা common = 0;

  /* True means types are compatible as far as ObjC is concerned.  */
  যৌক্তিক objc_ok;

  /* True means this is an arithmetic operation that may need excess
     precision.  */
  যৌক্তিক may_need_excess_precision;

  /* True means this is a boolean operation that converts both its
     operands to truth-values.  */
  যৌক্তিক boolean_op = মিথ্যা;

  /* Remember whether we're doing / or %.  */
  যৌক্তিক doing_div_or_mod = মিথ্যা;

  /* Remember whether we're doing << or >>.  */
  যৌক্তিক doing_shift = মিথ্যা;

  /* Tree holding instrumentation expression.  */
  বৃক্ষ instrument_রাশিমালা = ফাঁকা;

  যদি (location == UNKNOWN_LOCATION)
    location = প্রবেশ_location;

  op0 = orig_op0;
  op1 = orig_op1;

  op0_int_operands = রাশিমালা_INT_CONST_OPERANDS (orig_op0);
  যদি (op0_int_operands)
    op0 = remove_c_maybe_const_রাশিমালা (op0);
  op1_int_operands = রাশিমালা_INT_CONST_OPERANDS (orig_op1);
  যদি (op1_int_operands)
    op1 = remove_c_maybe_const_রাশিমালা (op1);
  int_operands = (op0_int_operands && op1_int_operands);
  যদি (int_operands)
    {
      int_const_or_overflow = (বৃক্ষ_CODE (orig_op0) == INTEGER_CST
			       && বৃক্ষ_CODE (orig_op1) == INTEGER_CST);
      int_const = (int_const_or_overflow
		   && !বৃক্ষ_OVERFLOW (orig_op0)
		   && !বৃক্ষ_OVERFLOW (orig_op1));
    }
  অন্যথা
    int_const = int_const_or_overflow = মিথ্যা;

  /* Do not apply default conversion in mixed vector/scalar expression.  */
  যদি (convert_p
      && VECTOR_TYPE_P (বৃক্ষ_TYPE (op0)) == VECTOR_TYPE_P (বৃক্ষ_TYPE (op1)))
    {
      op0 = default_conversion (op0);
      op1 = default_conversion (op1);
    }

  orig_type0 = type0 = বৃক্ষ_TYPE (op0);

  orig_type1 = type1 = বৃক্ষ_TYPE (op1);

  /* The expression codes of the data types of the arguments tell us
     whether the arguments are integers, floating, pointers, etc.  */
  code0 = বৃক্ষ_CODE (type0);
  code1 = বৃক্ষ_CODE (type1);

  /* Strip NON_LVALUE_EXPRs, etc., since we aren't using as an lvalue.  */
  STRIP_TYPE_NOPS (op0);
  STRIP_TYPE_NOPS (op1);

  /* If an error was already reported for one of the arguments,
     avoid reporting another error.  */

  যদি (code0 == ERROR_MARK || code1 == ERROR_MARK)
    ফেরত error_mark_গ্রন্থি;

  যদি (code0 == POINTER_TYPE
      && reject_gcc_builtin (op0, রাশিমালা_LOCATION (orig_op0)))
    ফেরত error_mark_গ্রন্থি;

  যদি (code1 == POINTER_TYPE
      && reject_gcc_builtin (op1, রাশিমালা_LOCATION (orig_op1)))
    ফেরত error_mark_গ্রন্থি;

  যদি ((invalid_op_diag
       = targetm.invalid_দ্বিমিক_op (code, type0, type1)))
    {
      error_at (location, invalid_op_diag);
      ফেরত error_mark_গ্রন্থি;
    }

  নির্বাচন (code)
    {
    ক্ষেত্র PLUS_রাশিমালা:
    ক্ষেত্র MINUS_রাশিমালা:
    ক্ষেত্র MULT_রাশিমালা:
    ক্ষেত্র TRUNC_DIV_রাশিমালা:
    ক্ষেত্র CEIL_DIV_রাশিমালা:
    ক্ষেত্র FLOOR_DIV_রাশিমালা:
    ক্ষেত্র ROUND_DIV_রাশিমালা:
    ক্ষেত্র EXACT_DIV_রাশিমালা:
      may_need_excess_precision = সত্য;
      বিরতি;

    ক্ষেত্র EQ_রাশিমালা:
    ক্ষেত্র NE_রাশিমালা:
    ক্ষেত্র LE_রাশিমালা:
    ক্ষেত্র GE_রাশিমালা:
    ক্ষেত্র LT_রাশিমালা:
    ক্ষেত্র GT_রাশিমালা:
      /* Excess precision for implicit conversions of integers to
	 floating point in C11 and later.  */
      may_need_excess_precision = (flag_isoc11
				   && (ANY_INTEGRAL_TYPE_P (type0)
				       || ANY_INTEGRAL_TYPE_P (type1)));
      বিরতি;

    পূর্বনির্ধারিত:
      may_need_excess_precision = মিথ্যা;
      বিরতি;
    }
  যদি (বৃক্ষ_CODE (op0) == EXCESS_PRECISION_রাশিমালা)
    {
      op0 = বৃক্ষ_OPERAND (op0, 0);
      type0 = বৃক্ষ_TYPE (op0);
    }
  অন্যথা যদি (may_need_excess_precision
	   && (eptype = excess_precision_type (type0)) != NULL_বৃক্ষ)
    {
      type0 = eptype;
      op0 = convert (eptype, op0);
    }
  যদি (বৃক্ষ_CODE (op1) == EXCESS_PRECISION_রাশিমালা)
    {
      op1 = বৃক্ষ_OPERAND (op1, 0);
      type1 = বৃক্ষ_TYPE (op1);
    }
  অন্যথা যদি (may_need_excess_precision
	   && (eptype = excess_precision_type (type1)) != NULL_বৃক্ষ)
    {
      type1 = eptype;
      op1 = convert (eptype, op1);
    }

  objc_ok = objc_compare_types (type0, type1, -3, NULL_বৃক্ষ);

  /* In case when one of the operands of the binary operation is
     a vector and another is a scalar -- convert scalar to vector.  */
  যদি ((gnu_vector_type_p (type0) && code1 != VECTOR_TYPE)
      || (gnu_vector_type_p (type1) && code0 != VECTOR_TYPE))
    {
      গণনা stv_conv convert_flag = scalar_to_vector (location, code, orig_op0,
						     orig_op1, সত্য);

      নির্বাচন (convert_flag)
	{
	  ক্ষেত্র stv_error:
	    ফেরত error_mark_গ্রন্থি;
	  ক্ষেত্র stv_firstarg:
	    {
              যৌক্তিক maybe_const = সত্য;
              বৃক্ষ sc;
              sc = c_fully_fold (op0, মিথ্যা, &maybe_const);
              sc = save_রাশিমালা (sc);
              sc = convert (বৃক্ষ_TYPE (type1), sc);
              op0 = build_vector_from_val (type1, sc);
              যদি (!maybe_const)
                op0 = c_wrap_maybe_const (op0, সত্য);
              orig_type0 = type0 = বৃক্ষ_TYPE (op0);
              code0 = বৃক্ষ_CODE (type0);
              converted = 1;
              বিরতি;
	    }
	  ক্ষেত্র stv_secondarg:
	    {
	      যৌক্তিক maybe_const = সত্য;
	      বৃক্ষ sc;
	      sc = c_fully_fold (op1, মিথ্যা, &maybe_const);
	      sc = save_রাশিমালা (sc);
	      sc = convert (বৃক্ষ_TYPE (type0), sc);
	      op1 = build_vector_from_val (type0, sc);
	      যদি (!maybe_const)
		op1 = c_wrap_maybe_const (op1, সত্য);
	      orig_type1 = type1 = বৃক্ষ_TYPE (op1);
	      code1 = বৃক্ষ_CODE (type1);
	      converted = 1;
	      বিরতি;
	    }
	  পূর্বনির্ধারিত:
	    বিরতি;
	}
    }

  নির্বাচন (code)
    {
    ক্ষেত্র PLUS_রাশিমালা:
      /* Handle the pointer + int case.  */
      যদি (code0 == POINTER_TYPE
	  && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  ret = pointer_int_যোগ (location, PLUS_রাশিমালা, op0, op1);
	  যাও return_build_দ্বিমিক_op;
	}
      অন্যথা যদি (code1 == POINTER_TYPE
	       && (code0 == INTEGER_TYPE || code0 == BITINT_TYPE))
	{
	  ret = pointer_int_যোগ (location, PLUS_রাশিমালা, op1, op0);
	  যাও return_build_দ্বিমিক_op;
	}
      অন্যথা
	common = 1;
      বিরতি;

    ক্ষেত্র MINUS_রাশিমালা:
      /* Subtraction of two similar pointers.
	 We must subtract them as integers, then divide by object size.  */
      যদি (code0 == POINTER_TYPE && code1 == POINTER_TYPE
	  && comp_target_types (location, type0, type1))
	{
	  ret = pointer_diff (location, op0, op1, &instrument_রাশিমালা);
	  যাও return_build_দ্বিমিক_op;
	}
      /* Handle pointer minus int.  Just like pointer plus int.  */
      অন্যথা যদি (code0 == POINTER_TYPE
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  ret = pointer_int_যোগ (location, MINUS_রাশিমালা, op0, op1);
	  যাও return_build_দ্বিমিক_op;
	}
      অন্যথা
	common = 1;
      বিরতি;

    ক্ষেত্র MULT_রাশিমালা:
      common = 1;
      বিরতি;

    ক্ষেত্র TRUNC_DIV_রাশিমালা:
    ক্ষেত্র CEIL_DIV_রাশিমালা:
    ক্ষেত্র FLOOR_DIV_রাশিমালা:
    ক্ষেত্র ROUND_DIV_রাশিমালা:
    ক্ষেত্র EXACT_DIV_রাশিমালা:
      doing_div_or_mod = সত্য;
      warn_for_div_by_zero (location, op1);

      যদি ((code0 == INTEGER_TYPE || code0 == REAL_TYPE
	   || code0 == FIXED_POINT_TYPE || code0 == BITINT_TYPE
	   || code0 == COMPLEX_TYPE
	   || gnu_vector_type_p (type0))
	  && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	      || code1 == FIXED_POINT_TYPE || code1 == BITINT_TYPE
	      || code1 == COMPLEX_TYPE
	      || gnu_vector_type_p (type1)))
	{
	  গণনা বৃক্ষ_code tcode0 = code0, tcode1 = code1;

	  যদি (code0 == COMPLEX_TYPE || code0 == VECTOR_TYPE)
	    tcode0 = বৃক্ষ_CODE (বৃক্ষ_TYPE (বৃক্ষ_TYPE (op0)));
	  যদি (code1 == COMPLEX_TYPE || code1 == VECTOR_TYPE)
	    tcode1 = বৃক্ষ_CODE (বৃক্ষ_TYPE (বৃক্ষ_TYPE (op1)));

	  যদি (!(((tcode0 == INTEGER_TYPE || tcode0 == BITINT_TYPE
		  || (tcode0 == ENUMERAL_TYPE && code0 == VECTOR_TYPE))
		 && (tcode1 == INTEGER_TYPE || tcode1 == BITINT_TYPE
		     || (tcode1 == ENUMERAL_TYPE && code1 == VECTOR_TYPE)))
		|| (tcode0 == FIXED_POINT_TYPE && tcode1 == FIXED_POINT_TYPE)))
	    resultcode = RDIV_রাশিমালা;
	  অন্যথা
	    /* Although it would be tempting to shorten always here, that
	       loses on some targets, since the modulo instruction is
	       undefined if the quotient can't be represented in the
	       computation mode.  We shorten only if unsigned or if
	       dividing by something we know != -1.  */
	    shorten = may_shorten_divmod (op0, op1);
	  common = 1;
	}
      বিরতি;

    ক্ষেত্র BIT_AND_রাশিমালা:
    ক্ষেত্র BIT_IOR_রাশিমালা:
    ক্ষেত্র BIT_XOR_রাশিমালা:
      যদি ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	shorten = -1;
      /* Allow vector types which are not floating point types.   */
      অন্যথা যদি (gnu_vector_type_p (type0)
	       && gnu_vector_type_p (type1)
	       && !VECTOR_FLOAT_TYPE_P (type0)
	       && !VECTOR_FLOAT_TYPE_P (type1))
	common = 1;
      বিরতি;

    ক্ষেত্র TRUNC_MOD_রাশিমালা:
    ক্ষেত্র FLOOR_MOD_রাশিমালা:
      doing_div_or_mod = সত্য;
      warn_for_div_by_zero (location, op1);

      যদি (gnu_vector_type_p (type0)
	  && gnu_vector_type_p (type1)
	  && বৃক্ষ_CODE (বৃক্ষ_TYPE (type0)) == INTEGER_TYPE
	  && বৃক্ষ_CODE (বৃক্ষ_TYPE (type1)) == INTEGER_TYPE)
	common = 1;
      অন্যথা যদি ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  /* Although it would be tempting to shorten always here, that loses
	     on some targets, since the modulo instruction is undefined if the
	     quotient can't be represented in the computation mode.  We shorten
	     only if unsigned or if dividing by something we know != -1.  */
	  shorten = may_shorten_divmod (op0, op1);
	  common = 1;
	}
      বিরতি;

    ক্ষেত্র TRUTH_ANDIF_রাশিমালা:
    ক্ষেত্র TRUTH_ORIF_রাশিমালা:
    ক্ষেত্র TRUTH_AND_রাশিমালা:
    ক্ষেত্র TRUTH_OR_রাশিমালা:
    ক্ষেত্র TRUTH_XOR_রাশিমালা:
      যদি ((code0 == INTEGER_TYPE || code0 == POINTER_TYPE
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
	  ফলাফল_type = integer_type_গ্রন্থি;
	  যদি (op0_int_operands)
	    {
	      op0 = c_objc_common_truthvalue_conversion (location, orig_op0);
	      op0 = remove_c_maybe_const_রাশিমালা (op0);
	    }
	  অন্যথা
	    op0 = c_objc_common_truthvalue_conversion (location, op0);
	  যদি (op1_int_operands)
	    {
	      op1 = c_objc_common_truthvalue_conversion (location, orig_op1);
	      op1 = remove_c_maybe_const_রাশিমালা (op1);
	    }
	  অন্যথা
	    op1 = c_objc_common_truthvalue_conversion (location, op1);
	  converted = 1;
	  boolean_op = সত্য;
	}
      যদি (code == TRUTH_ANDIF_রাশিমালা)
	{
	  int_const_or_overflow = (int_operands
				   && বৃক্ষ_CODE (orig_op0) == INTEGER_CST
				   && (op0 == truthvalue_false_গ্রন্থি
				       || বৃক্ষ_CODE (orig_op1) == INTEGER_CST));
	  int_const = (int_const_or_overflow
		       && !বৃক্ষ_OVERFLOW (orig_op0)
		       && (op0 == truthvalue_false_গ্রন্থি
			   || !বৃক্ষ_OVERFLOW (orig_op1)));
	}
      অন্যথা যদি (code == TRUTH_ORIF_রাশিমালা)
	{
	  int_const_or_overflow = (int_operands
				   && বৃক্ষ_CODE (orig_op0) == INTEGER_CST
				   && (op0 == truthvalue_true_গ্রন্থি
				       || বৃক্ষ_CODE (orig_op1) == INTEGER_CST));
	  int_const = (int_const_or_overflow
		       && !বৃক্ষ_OVERFLOW (orig_op0)
		       && (op0 == truthvalue_true_গ্রন্থি
			   || !বৃক্ষ_OVERFLOW (orig_op1)));
	}
      বিরতি;

      /* Shift operations: result has same type as first operand;
	 always convert second operand to int.
	 Also set SHORT_SHIFT if shifting rightward.  */

    ক্ষেত্র RSHIFT_রাশিমালা:
      যদি (gnu_vector_type_p (type0)
	  && gnu_vector_type_p (type1)
	  && বৃক্ষ_CODE (বৃক্ষ_TYPE (type0)) == INTEGER_TYPE
	  && বৃক্ষ_CODE (বৃক্ষ_TYPE (type1)) == INTEGER_TYPE
	  && known_eq (TYPE_VECTOR_SUBPARTS (type0),
		       TYPE_VECTOR_SUBPARTS (type1)))
	{
	  ফলাফল_type = type0;
	  converted = 1;
	}
      অন্যথা যদি ((code0 == INTEGER_TYPE || code0 == FIXED_POINT_TYPE
		|| code0 == BITINT_TYPE
		|| (gnu_vector_type_p (type0)
		    && বৃক্ষ_CODE (বৃক্ষ_TYPE (type0)) == INTEGER_TYPE))
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  doing_shift = সত্য;
	  যদি (বৃক্ষ_CODE (op1) == INTEGER_CST)
	    {
	      যদি (বৃক্ষ_int_cst_sgn (op1) < 0)
		{
		  int_const = মিথ্যা;
		  যদি (c_inhibit_evaluation_warnings == 0)
		    warning_at (location, OPT_Wshift_গুনতি_negative,
				"right shift count is negative");
		}
	      অন্যথা যদি (code0 == VECTOR_TYPE)
		{
		  যদি (compare_বৃক্ষ_int (op1,
					TYPE_PRECISION (বৃক্ষ_TYPE (type0)))
		      >= 0)
		    {
		      int_const = মিথ্যা;
		      যদি (c_inhibit_evaluation_warnings == 0)
			warning_at (location, OPT_Wshift_গুনতি_overflow,
				    "right shift count >= width of vector element");
		    }
		}
	      অন্যথা
		{
		  যদি (!integer_zerop (op1))
		    short_shift = 1;

		  যদি (compare_বৃক্ষ_int (op1, TYPE_PRECISION (type0)) >= 0)
		    {
		      int_const = মিথ্যা;
		      যদি (c_inhibit_evaluation_warnings == 0)
			warning_at (location, OPT_Wshift_গুনতি_overflow,
				    "right shift count >= width of type");
		    }
		}
	    }

	  /* Use the type of the value to be shifted.  */
	  ফলাফল_type = type0;
	  /* Avoid converting op1 to result_type later.  */
	  converted = 1;
	}
      বিরতি;

    ক্ষেত্র LSHIFT_রাশিমালা:
      যদি (gnu_vector_type_p (type0)
	  && gnu_vector_type_p (type1)
	  && বৃক্ষ_CODE (বৃক্ষ_TYPE (type0)) == INTEGER_TYPE
	  && বৃক্ষ_CODE (বৃক্ষ_TYPE (type1)) == INTEGER_TYPE
	  && known_eq (TYPE_VECTOR_SUBPARTS (type0),
		       TYPE_VECTOR_SUBPARTS (type1)))
	{
	  ফলাফল_type = type0;
	  converted = 1;
	}
      অন্যথা যদি ((code0 == INTEGER_TYPE || code0 == FIXED_POINT_TYPE
		|| code0 == BITINT_TYPE
		|| (gnu_vector_type_p (type0)
		    && বৃক্ষ_CODE (বৃক্ষ_TYPE (type0)) == INTEGER_TYPE))
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  doing_shift = সত্য;
	  যদি (বৃক্ষ_CODE (op0) == INTEGER_CST
	      && বৃক্ষ_int_cst_sgn (op0) < 0
	      && !TYPE_OVERFLOW_WRAPS (type0))
	    {
	      /* Don't reject a left shift of a negative value in a context
		 where a constant expression is needed in C90.  */
	      যদি (flag_isoc99)
		int_const = মিথ্যা;
	      যদি (c_inhibit_evaluation_warnings == 0)
		warning_at (location, OPT_Wshift_negative_মান,
			    "left shift of negative value");
	    }
	  যদি (বৃক্ষ_CODE (op1) == INTEGER_CST)
	    {
	      যদি (বৃক্ষ_int_cst_sgn (op1) < 0)
		{
		  int_const = মিথ্যা;
		  যদি (c_inhibit_evaluation_warnings == 0)
		    warning_at (location, OPT_Wshift_গুনতি_negative,
				"left shift count is negative");
		}
	      অন্যথা যদি (code0 == VECTOR_TYPE)
		{
		  যদি (compare_বৃক্ষ_int (op1,
					TYPE_PRECISION (বৃক্ষ_TYPE (type0)))
		      >= 0)
		    {
		      int_const = মিথ্যা;
		      যদি (c_inhibit_evaluation_warnings == 0)
			warning_at (location, OPT_Wshift_গুনতি_overflow,
				    "left shift count >= width of vector element");
		    }
		}
	      অন্যথা যদি (compare_বৃক্ষ_int (op1, TYPE_PRECISION (type0)) >= 0)
		{
		  int_const = মিথ্যা;
		  যদি (c_inhibit_evaluation_warnings == 0)
		    warning_at (location, OPT_Wshift_গুনতি_overflow,
				"left shift count >= width of type");
		}
	      অন্যথা যদি (বৃক্ষ_CODE (op0) == INTEGER_CST
		       && maybe_warn_shift_overflow (location, op0, op1)
		       && flag_isoc99)
		int_const = মিথ্যা;
	    }

	  /* Use the type of the value to be shifted.  */
	  ফলাফল_type = type0;
	  /* Avoid converting op1 to result_type later.  */
	  converted = 1;
	}
      বিরতি;

    ক্ষেত্র EQ_রাশিমালা:
    ক্ষেত্র NE_রাশিমালা:
      যদি (gnu_vector_type_p (type0) && gnu_vector_type_p (type1))
        {
          বৃক্ষ intt;
	  যদি (!vector_types_compatible_elements_p (type0, type1))
            {
              error_at (location, "comparing vectors with different "
                                  "element types");
              ফেরত error_mark_গ্রন্থি;
            }

	  যদি (maybe_ne (TYPE_VECTOR_SUBPARTS (type0),
			TYPE_VECTOR_SUBPARTS (type1)))
            {
              error_at (location, "comparing vectors with different "
                                  "number of elements");
              ফেরত error_mark_গ্রন্থি;
            }

	  /* It's not precisely specified how the usual arithmetic
	     conversions apply to the vector types.  Here, we use
	     the unsigned type if one of the operands is signed and
	     the other one is unsigned.  */
	  যদি (TYPE_UNSIGNED (type0) != TYPE_UNSIGNED (type1))
	    {
	      যদি (!TYPE_UNSIGNED (type0))
		op0 = build1 (VIEW_CONVERT_রাশিমালা, type1, op0);
	      অন্যথা
		op1 = build1 (VIEW_CONVERT_রাশিমালা, type0, op1);
	      warning_at (location, OPT_Wsign_compare, "comparison between "
			  "types %qT and %qT", type0, type1);
	    }

          /* Always construct signed integer vector type.  */
	  যদি (VECTOR_BOOLEAN_TYPE_P (type0) && VECTOR_BOOLEAN_TYPE_P (type1))
	    ফলাফল_type = type0;
	  অন্যথা
	    {
	      auto nelts = TYPE_VECTOR_SUBPARTS (type0);

	      intt = c_common_type_for_আকার (GET_MODE_BITSIZE
					     (SCALAR_TYPE_MODE
						(বৃক্ষ_TYPE (type0))), 0);
	      যদি (!intt)
		{
		  error_at (location, "could not find an integer type "
				      "of the same size as %qT",
			    বৃক্ষ_TYPE (type0));
		  ফেরত error_mark_গ্রন্থি;
		}
	      ফলাফল_type = build_opaque_vector_type (intt, nelts);
	    }
          converted = 1;
	  ret = build_vec_cmp (resultcode, ফলাফল_type, op0, op1);
	  যাও return_build_দ্বিমিক_op;
        }
      যদি (FLOAT_TYPE_P (type0) || FLOAT_TYPE_P (type1))
	warning_at (location,
		    OPT_Wfloat_equal,
		    "comparing floating-point with %<==%> or %<!=%> is unsafe");
      /* Result of comparison is always int,
	 but don't convert the args to int!  */
      build_type = integer_type_গ্রন্থি;
      যদি ((code0 == INTEGER_TYPE || code0 == REAL_TYPE || code0 == BITINT_TYPE
	   || code0 == FIXED_POINT_TYPE || code0 == COMPLEX_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	      || code1 == BITINT_TYPE
	      || code1 == FIXED_POINT_TYPE || code1 == COMPLEX_TYPE))
	short_compare = 1;
      অন্যথা যদি (code0 == POINTER_TYPE
	       && (code1 == NULLPTR_TYPE
		   || null_pointer_constant_p (orig_op1)))
	{
	  maybe_warn_for_null_address (location, op0, code);
	  ফলাফল_type = type0;
	}
      অন্যথা যদি (code1 == POINTER_TYPE
	       && (code0 == NULLPTR_TYPE
		   || null_pointer_constant_p (orig_op0)))
	{
	  maybe_warn_for_null_address (location, op1, code);
	  ফলাফল_type = type1;
	}
      অন্যথা যদি (code0 == POINTER_TYPE && code1 == POINTER_TYPE)
	{
	  বৃক্ষ tt0 = বৃক্ষ_TYPE (type0);
	  বৃক্ষ tt1 = বৃক্ষ_TYPE (type1);
	  addr_space_t as0 = TYPE_ADDR_SPACE (tt0);
	  addr_space_t as1 = TYPE_ADDR_SPACE (tt1);
	  addr_space_t as_common = ADDR_SPACE_GENERIC;

	  /* Anything compares with void *.  void * compares with anything.
	     Otherwise, the targets must be compatible
	     and both must be object or both incomplete.  */
	  যদি (comp_target_types (location, type0, type1))
	    ফলাফল_type = common_pointer_type (type0, type1, NULL_বৃক্ষ);
	  অন্যথা যদি (!addr_space_superset (as0, as1, &as_common))
	    {
	      error_at (location, "comparison of pointers to "
			"disjoint address spaces");
	      ফেরত error_mark_গ্রন্থি;
	    }
	  অন্যথা যদি (VOID_TYPE_P (tt0) && !TYPE_ATOMIC (tt0))
	    {
	      যদি (pedantic && বৃক্ষ_CODE (tt1) == FUNCTION_TYPE)
		pedwarn (location, OPT_Wpedantic, "ISO C forbids "
			 "comparison of %<void *%> with function pointer");
	    }
	  অন্যথা যদি (VOID_TYPE_P (tt1) && !TYPE_ATOMIC (tt1))
	    {
	      যদি (pedantic && বৃক্ষ_CODE (tt0) == FUNCTION_TYPE)
		pedwarn (location, OPT_Wpedantic, "ISO C forbids "
			 "comparison of %<void *%> with function pointer");
	    }
	  অন্যথা
	    /* Avoid warning about the volatile ObjC EH puts on decls.  */
	    যদি (!objc_ok)
	      pedwarn (location, OPT_Wcompare_distinct_pointer_types,
		       "comparison of distinct pointer types lacks a cast");

	  যদি (ফলাফল_type == NULL_বৃক্ষ)
	    {
	      পূর্ণসংখ্যা qual = ENCODE_QUAL_ADDR_SPACE (as_common);
	      ফলাফল_type = c_build_pointer_type
			      (c_build_qualified_type (void_type_গ্রন্থি, qual));
	    }
	}
      অন্যথা যদি (code0 == POINTER_TYPE
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  ফলাফল_type = type0;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}
      অন্যথা যদি ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	       && code1 == POINTER_TYPE)
	{
	  ফলাফল_type = type1;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}
      /* 6.5.9: One of the following shall hold:
	 -- both operands have type nullptr_t;  */
      অন্যথা যদি (code0 == NULLPTR_TYPE && code1 == NULLPTR_TYPE)
	{
	  ফলাফল_type = nullptr_type_গ্রন্থি;
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
      অন্যথা যদি (code0 == NULLPTR_TYPE && null_pointer_constant_p (orig_op1))
	ফলাফল_type = (INTEGRAL_TYPE_P (type1)
		       ? c_build_pointer_type (type1) : type1);
      অন্যথা যদি (code1 == NULLPTR_TYPE && null_pointer_constant_p (orig_op0))
	ফলাফল_type = (INTEGRAL_TYPE_P (type0)
		       ? c_build_pointer_type (type0) : type0);
      যদি ((C_BOOLEAN_TYPE_P (বৃক্ষ_TYPE (orig_op0))
	   || truth_মান_p (বৃক্ষ_CODE (orig_op0)))
	  ^ (C_BOOLEAN_TYPE_P (বৃক্ষ_TYPE (orig_op1))
	     || truth_মান_p (বৃক্ষ_CODE (orig_op1))))
	maybe_warn_bool_compare (location, code, orig_op0, orig_op1);
      বিরতি;

    ক্ষেত্র LE_রাশিমালা:
    ক্ষেত্র GE_রাশিমালা:
    ক্ষেত্র LT_রাশিমালা:
    ক্ষেত্র GT_রাশিমালা:
      যদি (gnu_vector_type_p (type0) && gnu_vector_type_p (type1))
        {
          বৃক্ষ intt;
	  যদি (!vector_types_compatible_elements_p (type0, type1))
            {
              error_at (location, "comparing vectors with different "
                                  "element types");
              ফেরত error_mark_গ্রন্থি;
            }

	  যদি (maybe_ne (TYPE_VECTOR_SUBPARTS (type0),
			TYPE_VECTOR_SUBPARTS (type1)))
            {
              error_at (location, "comparing vectors with different "
                                  "number of elements");
              ফেরত error_mark_গ্রন্থি;
            }

	  /* It's not precisely specified how the usual arithmetic
	     conversions apply to the vector types.  Here, we use
	     the unsigned type if one of the operands is signed and
	     the other one is unsigned.  */
	  যদি (TYPE_UNSIGNED (type0) != TYPE_UNSIGNED (type1))
	    {
	      যদি (!TYPE_UNSIGNED (type0))
		op0 = build1 (VIEW_CONVERT_রাশিমালা, type1, op0);
	      অন্যথা
		op1 = build1 (VIEW_CONVERT_রাশিমালা, type0, op1);
	      warning_at (location, OPT_Wsign_compare, "comparison between "
			  "types %qT and %qT", type0, type1);
	    }

          /* Always construct signed integer vector type.  */
          intt = c_common_type_for_আকার (GET_MODE_BITSIZE
					 (SCALAR_TYPE_MODE
					  (বৃক্ষ_TYPE (type0))), 0);
	  যদি (!intt)
	    {
	      error_at (location, "could not find an integer type "
				  "of the same size as %qT",
			বৃক্ষ_TYPE (type0));
	      ফেরত error_mark_গ্রন্থি;
	    }
          ফলাফল_type = build_opaque_vector_type (intt,
						  TYPE_VECTOR_SUBPARTS (type0));
          converted = 1;
	  ret = build_vec_cmp (resultcode, ফলাফল_type, op0, op1);
	  যাও return_build_দ্বিমিক_op;
        }
      build_type = integer_type_গ্রন্থি;
      যদি ((code0 == INTEGER_TYPE || code0 == REAL_TYPE
	   || code0 == BITINT_TYPE || code0 == FIXED_POINT_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	      || code1 == BITINT_TYPE || code1 == FIXED_POINT_TYPE))
	short_compare = 1;
      অন্যথা যদি (code0 == POINTER_TYPE && code1 == POINTER_TYPE)
	{
	  addr_space_t as0 = TYPE_ADDR_SPACE (বৃক্ষ_TYPE (type0));
	  addr_space_t as1 = TYPE_ADDR_SPACE (বৃক্ষ_TYPE (type1));
	  addr_space_t as_common;

	  যদি (comp_target_types (location, type0, type1))
	    {
	      ফলাফল_type = common_pointer_type (type0, type1, NULL_বৃক্ষ);
	      যদি (!COMPLETE_TYPE_P (বৃক্ষ_TYPE (type0))
		  != !COMPLETE_TYPE_P (বৃক্ষ_TYPE (type1)))
		pedwarn_c99 (location, OPT_Wpedantic,
			     "comparison of complete and incomplete pointers");
	      অন্যথা যদি (বৃক্ষ_CODE (বৃক্ষ_TYPE (type0)) == FUNCTION_TYPE)
		pedwarn (location, OPT_Wpedantic, "ISO C forbids "
			 "ordered comparisons of pointers to functions");
	      অন্যথা যদি (null_pointer_constant_p (orig_op0)
		       || null_pointer_constant_p (orig_op1))
		warning_at (location, OPT_Wextra,
			    "ordered comparison of pointer with null pointer");

	    }
	  অন্যথা যদি (!addr_space_superset (as0, as1, &as_common))
	    {
	      error_at (location, "comparison of pointers to "
			"disjoint address spaces");
	      ফেরত error_mark_গ্রন্থি;
	    }
	  অন্যথা
	    {
	      পূর্ণসংখ্যা qual = ENCODE_QUAL_ADDR_SPACE (as_common);
	      ফলাফল_type = c_build_pointer_type
			      (c_build_qualified_type (void_type_গ্রন্থি, qual));
              pedwarn (location, OPT_Wcompare_distinct_pointer_types,
                       "comparison of distinct pointer types lacks a cast");
	    }
	}
      অন্যথা যদি (code0 == POINTER_TYPE && null_pointer_constant_p (orig_op1))
	{
	  ফলাফল_type = type0;
	  যদি (pedantic)
	    pedwarn (location, OPT_Wpedantic,
		     "ordered comparison of pointer with integer zero");
	  অন্যথা যদি (extra_warnings)
	    warning_at (location, OPT_Wextra,
			"ordered comparison of pointer with integer zero");
	}
      অন্যথা যদি (code1 == POINTER_TYPE && null_pointer_constant_p (orig_op0))
	{
	  ফলাফল_type = type1;
	  যদি (pedantic)
	    pedwarn (location, OPT_Wpedantic,
		     "ordered comparison of pointer with integer zero");
	  অন্যথা যদি (extra_warnings)
	    warning_at (location, OPT_Wextra,
			"ordered comparison of pointer with integer zero");
	}
      অন্যথা যদি (code0 == POINTER_TYPE
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  ফলাফল_type = type0;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}
      অন্যথা যদি ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	       && code1 == POINTER_TYPE)
	{
	  ফলাফল_type = type1;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}

      যদি ((code0 == POINTER_TYPE || code1 == POINTER_TYPE)
	  && current_function_decl != NULL_বৃক্ষ
	  && sanitize_flags_p (SANITIZE_POINTER_COMPARE))
	{
	  op0 = save_রাশিমালা (c_fully_fold (op0, মিথ্যা, ফাঁকা));
	  op1 = save_রাশিমালা (c_fully_fold (op1, মিথ্যা, ফাঁকা));

	  বৃক্ষ tt = builtin_decl_explicit (BUILT_IN_ASAN_POINTER_COMPARE);
	  instrument_রাশিমালা = build_call_রাশিমালা_loc (location, tt, 2, op0, op1);
	}

      যদি ((C_BOOLEAN_TYPE_P (বৃক্ষ_TYPE (orig_op0))
	   || truth_মান_p (বৃক্ষ_CODE (orig_op0)))
	  ^ (C_BOOLEAN_TYPE_P (বৃক্ষ_TYPE (orig_op1))
	     || truth_মান_p (বৃক্ষ_CODE (orig_op1))))
	maybe_warn_bool_compare (location, code, orig_op0, orig_op1);
      বিরতি;

    ক্ষেত্র MIN_রাশিমালা:
    ক্ষেত্র MAX_রাশিমালা:
      /* Used for OpenMP atomics.  */
      gcc_assert (flag_openmp);
      common = 1;
      বিরতি;

    পূর্বনির্ধারিত:
      gcc_unreachable ();
    }

  যদি (code0 == ERROR_MARK || code1 == ERROR_MARK)
    ফেরত error_mark_গ্রন্থি;

  যদি (gnu_vector_type_p (type0)
      && gnu_vector_type_p (type1)
      && (!বৃক্ষ_int_cst_equal (TYPE_আকার (type0), TYPE_আকার (type1))
	  || !vector_types_compatible_elements_p (type0, type1)))
    {
      gcc_rich_location richloc (location);
      maybe_range_label_for_বৃক্ষ_type_mismatch
	label_for_op0 (orig_op0, orig_op1),
	label_for_op1 (orig_op1, orig_op0);
      richloc.maybe_add_রাশিমালা (orig_op0, &label_for_op0, highlight_colors::lhs);
      richloc.maybe_add_রাশিমালা (orig_op1, &label_for_op1, highlight_colors::rhs);
      দ্বিমিক_op_error (&richloc, code, type0, type1);
      ফেরত error_mark_গ্রন্থি;
    }

  যদি ((code0 == INTEGER_TYPE || code0 == REAL_TYPE || code0 == COMPLEX_TYPE
       || code0 == FIXED_POINT_TYPE || code0 == BITINT_TYPE
       || gnu_vector_type_p (type0))
      && (code1 == INTEGER_TYPE || code1 == REAL_TYPE || code1 == COMPLEX_TYPE
	  || code1 == FIXED_POINT_TYPE || code1 == BITINT_TYPE
	  || gnu_vector_type_p (type1)))
    {
      যৌক্তিক first_complex = (code0 == COMPLEX_TYPE);
      যৌক্তিক second_complex = (code1 == COMPLEX_TYPE);
      পূর্ণসংখ্যা none_complex = (!first_complex && !second_complex);

      যদি (shorten || common || short_compare)
	{
	  ফলাফল_type = c_common_type (type0, type1);
	  do_warn_double_promotion (ফলাফল_type, type0, type1,
				    "implicit conversion from %qT to %qT "
				    "to match other operand of binary "
				    "expression",
				    location);
	  যদি (ফলাফল_type == error_mark_গ্রন্থি)
	    ফেরত error_mark_গ্রন্থি;
	}

      যদি (first_complex != second_complex
	  && (code == PLUS_রাশিমালা
	      || code == MINUS_রাশিমালা
	      || code == MULT_রাশিমালা
	      || (code == TRUNC_DIV_রাশিমালা && first_complex))
	  && বৃক্ষ_CODE (বৃক্ষ_TYPE (ফলাফল_type)) == REAL_TYPE
	  && flag_signed_zeros)
	{
	  /* An operation on mixed real/complex operands must be
	     handled specially, but the language-independent code can
	     more easily optimize the plain complex arithmetic if
	     -fno-signed-zeros.  */
	  বৃক্ষ real_type = বৃক্ষ_TYPE (ফলাফল_type);
	  বৃক্ষ real, imag;
	  যদি (type0 != orig_type0 || type1 != orig_type1)
	    {
	      gcc_assert (may_need_excess_precision && common);
	      semantic_ফলাফল_type = c_common_type (orig_type0, orig_type1);
	    }
	  যদি (first_complex)
	    {
	      যদি (বৃক্ষ_TYPE (op0) != ফলাফল_type)
		op0 = convert_and_check (location, ফলাফল_type, op0);
	      যদি (বৃক্ষ_TYPE (op1) != real_type)
		op1 = convert_and_check (location, real_type, op1);
	    }
	  অন্যথা
	    {
	      যদি (বৃক্ষ_TYPE (op0) != real_type)
		op0 = convert_and_check (location, real_type, op0);
	      যদি (বৃক্ষ_TYPE (op1) != ফলাফল_type)
		op1 = convert_and_check (location, ফলাফল_type, op1);
	    }
	  যদি (বৃক্ষ_CODE (op0) == ERROR_MARK || বৃক্ষ_CODE (op1) == ERROR_MARK)
	    ফেরত error_mark_গ্রন্থি;
	  যদি (first_complex)
	    {
	      op0 = save_রাশিমালা (op0);
	      real = build_unary_op (রাশিমালা_LOCATION (orig_op0), REALPART_রাশিমালা,
				     op0, সত্য);
	      imag = build_unary_op (রাশিমালা_LOCATION (orig_op0), IMAGPART_রাশিমালা,
				     op0, সত্য);
	      নির্বাচন (code)
		{
		ক্ষেত্র MULT_রাশিমালা:
		ক্ষেত্র TRUNC_DIV_রাশিমালা:
		  op1 = save_রাশিমালা (op1);
		  imag = build2 (resultcode, real_type, imag, op1);
		  /* Fall through.  */
		ক্ষেত্র PLUS_রাশিমালা:
		ক্ষেত্র MINUS_রাশিমালা:
		  real = build2 (resultcode, real_type, real, op1);
		  বিরতি;
		পূর্বনির্ধারিত:
		  gcc_unreachable();
		}
	    }
	  অন্যথা
	    {
	      op1 = save_রাশিমালা (op1);
	      real = build_unary_op (রাশিমালা_LOCATION (orig_op1), REALPART_রাশিমালা,
				     op1, সত্য);
	      imag = build_unary_op (রাশিমালা_LOCATION (orig_op1), IMAGPART_রাশিমালা,
				     op1, সত্য);
	      নির্বাচন (code)
		{
		ক্ষেত্র MULT_রাশিমালা:
		  op0 = save_রাশিমালা (op0);
		  imag = build2 (resultcode, real_type, op0, imag);
		  /* Fall through.  */
		ক্ষেত্র PLUS_রাশিমালা:
		  real = build2 (resultcode, real_type, op0, real);
		  বিরতি;
		ক্ষেত্র MINUS_রাশিমালা:
		  real = build2 (resultcode, real_type, op0, real);
		  imag = build1 (NEGATE_রাশিমালা, real_type, imag);
		  বিরতি;
		পূর্বনির্ধারিত:
		  gcc_unreachable();
		}
	    }
	  ret = build2 (COMPLEX_রাশিমালা, ফলাফল_type, real, imag);
	  যাও return_build_দ্বিমিক_op;
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

      যদি (shorten && none_complex)
	{
	  final_type = ফলাফল_type;
	  ফলাফল_type = shorten_দ্বিমিক_op (ফলাফল_type, op0, op1,
					   shorten == -1);
	}

      /* Shifts can be shortened if shifting right.  */

      যদি (short_shift)
	{
	  পূর্ণসংখ্যা unsigned_arg;
	  বৃক্ষ arg0 = get_narrower (op0, &unsigned_arg);

	  final_type = ফলাফল_type;

	  যদি (arg0 == op0 && final_type == বৃক্ষ_TYPE (op0))
	    unsigned_arg = TYPE_UNSIGNED (বৃক্ষ_TYPE (op0));

	  যদি (TYPE_PRECISION (বৃক্ষ_TYPE (arg0)) < TYPE_PRECISION (ফলাফল_type)
	      && বৃক্ষ_int_cst_sgn (op1) > 0
	      /* We can shorten only if the shift count is less than the
		 number of bits in the smaller type size.  */
	      && compare_বৃক্ষ_int (op1, TYPE_PRECISION (বৃক্ষ_TYPE (arg0))) < 0
	      /* We cannot drop an unsigned shift after sign-extension.  */
	      && (!TYPE_UNSIGNED (final_type) || unsigned_arg))
	    {
	      /* Do an unsigned shift if the operand was zero-extended.  */
	      ফলাফল_type
		= c_common_signed_or_unsigned_type (unsigned_arg,
						    বৃক্ষ_TYPE (arg0));
	      /* Convert value-to-be-shifted to that type.  */
	      যদি (বৃক্ষ_TYPE (op0) != ফলাফল_type)
		op0 = convert (ফলাফল_type, op0);
	      converted = 1;
	    }
	}

      /* Comparison operations are shortened too but differently.
	 They identify themselves by setting short_compare = 1.  */

      যদি (short_compare)
	{
	  /* Don't write &op0, etc., because that would prevent op0
	     from being kept in a register.
	     Instead, make copies of the our local variables and
	     pass the copies by reference, then copy them back afterward.  */
	  বৃক্ষ xop0 = op0, xop1 = op1, xresult_type = ফলাফল_type;
	  গণনা বৃক্ষ_code xresultcode = resultcode;
	  বৃক্ষ val
	    = shorten_compare (location, &xop0, &xop1, &xresult_type,
			       &xresultcode);

	  যদি (val != NULL_বৃক্ষ)
	    {
	      ret = val;
	      যাও return_build_দ্বিমিক_op;
	    }

	  op0 = xop0, op1 = xop1;
	  converted = 1;
	  resultcode = xresultcode;

	  যদি (c_inhibit_evaluation_warnings == 0 && !c_in_omp_for)
	    {
	      যৌক্তিক op0_maybe_const = সত্য;
	      যৌক্তিক op1_maybe_const = সত্য;
	      বৃক্ষ orig_op0_folded, orig_op1_folded;

	      যদি (in_late_দ্বিমিক_op)
		{
		  orig_op0_folded = orig_op0;
		  orig_op1_folded = orig_op1;
		}
	      অন্যথা
		{
		  /* Fold for the sake of possible warnings, as in
		     build_conditional_expr.  This requires the
		     "original" values to be folded, not just op0 and
		     op1.  */
		  c_inhibit_evaluation_warnings++;
		  op0 = c_fully_fold (op0, require_constant_মান,
				      &op0_maybe_const);
		  op1 = c_fully_fold (op1, require_constant_মান,
				      &op1_maybe_const);
		  c_inhibit_evaluation_warnings--;
		  orig_op0_folded = c_fully_fold (orig_op0,
						  require_constant_মান,
						  ফাঁকা);
		  orig_op1_folded = c_fully_fold (orig_op1,
						  require_constant_মান,
						  ফাঁকা);
		}

	      যদি (warn_sign_compare)
		warn_for_sign_compare (location, orig_op0_folded,
				       orig_op1_folded, op0, op1,
				       ফলাফল_type, resultcode);
	      যদি (!in_late_দ্বিমিক_op && !int_operands)
		{
		  যদি (!op0_maybe_const || বৃক্ষ_CODE (op0) != INTEGER_CST)
		    op0 = c_wrap_maybe_const (op0, !op0_maybe_const);
		  যদি (!op1_maybe_const || বৃক্ষ_CODE (op1) != INTEGER_CST)
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

  যদি (!ফলাফল_type)
    {
      /* Favor showing any expression locations that are available. */
      op_location_t oploc (location, UNKNOWN_LOCATION);
      দ্বিমিক_op_rich_location richloc (oploc, orig_op0, orig_op1, সত্য);
      দ্বিমিক_op_error (&richloc, code, বৃক্ষ_TYPE (op0), বৃক্ষ_TYPE (op1));
      ফেরত error_mark_গ্রন্থি;
    }

  যদি (build_type == NULL_বৃক্ষ)
    {
      build_type = ফলাফল_type;
      যদি ((type0 != orig_type0 || type1 != orig_type1)
	  && !boolean_op)
	{
	  gcc_assert (may_need_excess_precision && common);
	  semantic_ফলাফল_type = c_common_type (orig_type0, orig_type1);
	}
    }

  যদি (!converted)
    {
      op0 = ep_convert_and_check (location, ফলাফল_type, op0,
				  semantic_ফলাফল_type);
      op1 = ep_convert_and_check (location, ফলাফল_type, op1,
				  semantic_ফলাফল_type);

      /* This can happen if one operand has a vector type, and the other
	 has a different type.  */
      যদি (বৃক্ষ_CODE (op0) == ERROR_MARK || বৃক্ষ_CODE (op1) == ERROR_MARK)
	ফেরত error_mark_গ্রন্থি;
    }

  যদি (sanitize_flags_p ((SANITIZE_SHIFT
			 | SANITIZE_DIVIDE
			 | SANITIZE_FLOAT_DIVIDE
			 | SANITIZE_SI_OVERFLOW))
      && current_function_decl != NULL_বৃক্ষ
      && (doing_div_or_mod || doing_shift)
      && !require_constant_মান)
    {
      /* OP0 and/or OP1 might have side-effects.  */
      op0 = save_রাশিমালা (op0);
      op1 = save_রাশিমালা (op1);
      op0 = c_fully_fold (op0, মিথ্যা, ফাঁকা);
      op1 = c_fully_fold (op1, মিথ্যা, ফাঁকা);
      যদি (doing_div_or_mod && (sanitize_flags_p ((SANITIZE_DIVIDE
						  | SANITIZE_FLOAT_DIVIDE
						  | SANITIZE_SI_OVERFLOW))))
	instrument_রাশিমালা = ubsan_instrument_division (location, op0, op1);
      অন্যথা যদি (doing_shift && sanitize_flags_p (SANITIZE_SHIFT))
	instrument_রাশিমালা = ubsan_instrument_shift (location, code, op0, op1);
    }

  /* Treat expressions in initializers specially as they can't trap.  */
  যদি (int_const_or_overflow)
    ret = (require_constant_মান
	   ? fold_build2_initializer_loc (location, resultcode, build_type,
					  op0, op1)
	   : fold_build2_loc (location, resultcode, build_type, op0, op1));
  অন্যথা
    ret = build2 (resultcode, build_type, op0, op1);
  যদি (final_type != NULL_বৃক্ষ)
    ret = convert (final_type, ret);

 return_build_দ্বিমিক_op:
  gcc_assert (ret != error_mark_গ্রন্থি);
  যদি (বৃক্ষ_CODE (ret) == INTEGER_CST && !বৃক্ষ_OVERFLOW (ret) && !int_const)
    ret = (int_operands
	   ? note_integer_operands (ret)
	   : build1 (NOP_রাশিমালা, বৃক্ষ_TYPE (ret), ret));
  অন্যথা যদি (বৃক্ষ_CODE (ret) != INTEGER_CST && int_operands
	   && !in_late_দ্বিমিক_op)
    ret = note_integer_operands (ret);
  protected_set_রাশিমালা_location (ret, location);

  যদি (instrument_রাশিমালা != ফাঁকা)
    ret = fold_build2 (COMPOUND_রাশিমালা, বৃক্ষ_TYPE (ret),
		       instrument_রাশিমালা, ret);

  যদি (semantic_ফলাফল_type)
    ret = build1_loc (location, EXCESS_PRECISION_রাশিমালা,
		      semantic_ফলাফল_type, ret);

  ফেরত ret;
}


/* Convert EXPR to be a truth-value (type TYPE), validating its type for this
   purpose.  LOCATION is the source location for the expression.  */

বৃক্ষ
c_objc_common_truthvalue_conversion (location_t location, বৃক্ষ রাশিমালা, বৃক্ষ type)
{
  যৌক্তিক int_const, int_operands;

  নির্বাচন (বৃক্ষ_CODE (বৃক্ষ_TYPE (রাশিমালা)))
    {
    ক্ষেত্র ARRAY_TYPE:
      error_at (location, "used array that cannot be converted to pointer where scalar is required");
      ফেরত error_mark_গ্রন্থি;

    ক্ষেত্র RECORD_TYPE:
      error_at (location, "used struct type value where scalar is required");
      ফেরত error_mark_গ্রন্থি;

    ক্ষেত্র UNION_TYPE:
      error_at (location, "used union type value where scalar is required");
      ফেরত error_mark_গ্রন্থি;

    ক্ষেত্র VOID_TYPE:
      error_at (location, "void value not ignored as it ought to be");
      ফেরত error_mark_গ্রন্থি;

    ক্ষেত্র POINTER_TYPE:
      যদি (reject_gcc_builtin (রাশিমালা))
	ফেরত error_mark_গ্রন্থি;
      বিরতি;

    ক্ষেত্র FUNCTION_TYPE:
      gcc_unreachable ();

    ক্ষেত্র VECTOR_TYPE:
      error_at (location, "used vector type where scalar is required");
      ফেরত error_mark_গ্রন্থি;

    পূর্বনির্ধারিত:
      বিরতি;
    }

  /* Conversion of a floating constant to boolean goes through here
     and yields an integer constant expression.  Otherwise, the result
     is only an integer constant expression if the argument is.  */
  int_const = ((বৃক্ষ_CODE (রাশিমালা) == INTEGER_CST && !বৃক্ষ_OVERFLOW (রাশিমালা))
	       || ((বৃক্ষ_CODE (রাশিমালা) == REAL_CST
		    || বৃক্ষ_CODE (রাশিমালা) == COMPLEX_CST)
		   && (বৃক্ষ_CODE (type) == BOOLEAN_TYPE
		       || (বৃক্ষ_CODE (type) == ENUMERAL_TYPE
			   && ENUM_UNDERLYING_TYPE (type) != NULL_বৃক্ষ
			   && (বৃক্ষ_CODE (ENUM_UNDERLYING_TYPE (type))
			       == BOOLEAN_TYPE)))));
  int_operands = রাশিমালা_INT_CONST_OPERANDS (রাশিমালা);
  যদি (int_operands && বৃক্ষ_CODE (রাশিমালা) != INTEGER_CST)
    {
      রাশিমালা = remove_c_maybe_const_রাশিমালা (রাশিমালা);
      রাশিমালা = build2 (NE_রাশিমালা, type, রাশিমালা,
		     convert (বৃক্ষ_TYPE (রাশিমালা), integer_zero_গ্রন্থি));
      রাশিমালা = note_integer_operands (রাশিমালা);
    }
  অন্যথা
    {
      /* ??? Should we also give an error for vectors rather than leaving
	 those to give errors later?  */
      রাশিমালা = c_common_truthvalue_conversion (location, রাশিমালা);
      রাশিমালা = fold_convert_loc (location, type, রাশিমালা);
    }

  যদি (বৃক্ষ_CODE (রাশিমালা) == INTEGER_CST && int_operands && !int_const)
    {
      যদি (বৃক্ষ_OVERFLOW (রাশিমালা))
	ফেরত রাশিমালা;
      অন্যথা
	ফেরত note_integer_operands (রাশিমালা);
    }
  যদি (বৃক্ষ_CODE (রাশিমালা) == INTEGER_CST && !int_const)
    ফেরত build1 (NOP_রাশিমালা, বৃক্ষ_TYPE (রাশিমালা), রাশিমালা);
  ফেরত রাশিমালা;
}


/* Convert EXPR to a contained DECL, updating *TC, *TI and *SE as
   required.  */

বৃক্ষ
c_রাশিমালা_to_decl (বৃক্ষ রাশিমালা, যৌক্তিক *tc ATTRIBUTE_UNUSED, যৌক্তিক *se)
{
  যদি (বৃক্ষ_CODE (রাশিমালা) == COMPOUND_LITERAL_রাশিমালা)
    {
      বৃক্ষ decl = COMPOUND_LITERAL_রাশিমালা_DECL (রাশিমালা);
      /* Executing a compound literal inside a function reinitializes
	 it.  */
      যদি (!বৃক্ষ_STATIC (decl))
	*se = সত্য;
      ফেরত decl;
    }
  অন্যথা
    ফেরত রাশিমালা;
}

/* Generate OMP construct CODE, with BODY and CLAUSES as its compound
   statement.  LOC is the location of the construct.  */

বৃক্ষ
c_finish_omp_construct (location_t loc, গণনা বৃক্ষ_code code, বৃক্ষ body,
			বৃক্ষ clauses)
{
  body = c_end_compound_stmt (loc, body, সত্য);

  বৃক্ষ stmt = make_গ্রন্থি (code);
  বৃক্ষ_TYPE (stmt) = void_type_গ্রন্থি;
  OMP_BODY (stmt) = body;
  OMP_CLAUSES (stmt) = clauses;
  SET_রাশিমালা_LOCATION (stmt, loc);

  ফেরত add_stmt (stmt);
}

/* Generate OACC_DATA, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the OACC_DATA.  */

বৃক্ষ
c_finish_oacc_তথ্য (location_t loc, বৃক্ষ clauses, বৃক্ষ block)
{
  বৃক্ষ stmt;

  block = c_end_compound_stmt (loc, block, সত্য);

  stmt = make_গ্রন্থি (OACC_তথ্য);
  বৃক্ষ_TYPE (stmt) = void_type_গ্রন্থি;
  OACC_তথ্য_CLAUSES (stmt) = clauses;
  OACC_তথ্য_BODY (stmt) = block;
  SET_রাশিমালা_LOCATION (stmt, loc);

  ফেরত add_stmt (stmt);
}

/* Generate OACC_HOST_DATA, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the OACC_HOST_DATA.  */

বৃক্ষ
c_finish_oacc_host_তথ্য (location_t loc, বৃক্ষ clauses, বৃক্ষ block)
{
  বৃক্ষ stmt;

  block = c_end_compound_stmt (loc, block, সত্য);

  stmt = make_গ্রন্থি (OACC_HOST_তথ্য);
  বৃক্ষ_TYPE (stmt) = void_type_গ্রন্থি;
  OACC_HOST_তথ্য_CLAUSES (stmt) = clauses;
  OACC_HOST_তথ্য_BODY (stmt) = block;
  SET_রাশিমালা_LOCATION (stmt, loc);

  ফেরত add_stmt (stmt);
}

/* Like c_begin_compound_stmt, except force the retention of the BLOCK.  */

বৃক্ষ
c_begin_omp_parallel (শূন্য)
{
  বৃক্ষ block;

  keep_পরবর্তী_level ();
  block = c_begin_compound_stmt (সত্য);

  ফেরত block;
}

/* Generate OMP_PARALLEL, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the OMP_PARALLEL.  */

বৃক্ষ
c_finish_omp_parallel (location_t loc, বৃক্ষ clauses, বৃক্ষ block)
{
  বৃক্ষ stmt;

  block = c_end_compound_stmt (loc, block, সত্য);

  stmt = make_গ্রন্থি (OMP_PARALLEL);
  বৃক্ষ_TYPE (stmt) = void_type_গ্রন্থি;
  OMP_PARALLEL_CLAUSES (stmt) = clauses;
  OMP_PARALLEL_BODY (stmt) = block;
  SET_রাশিমালা_LOCATION (stmt, loc);

  ফেরত add_stmt (stmt);
}

/* Like c_begin_compound_stmt, except force the retention of the BLOCK.  */

বৃক্ষ
c_begin_omp_task (শূন্য)
{
  বৃক্ষ block;

  keep_পরবর্তী_level ();
  block = c_begin_compound_stmt (সত্য);

  ফেরত block;
}

/* Generate OMP_TASK, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the #pragma.  */

বৃক্ষ
c_finish_omp_task (location_t loc, বৃক্ষ clauses, বৃক্ষ block)
{
  বৃক্ষ stmt;

  block = c_end_compound_stmt (loc, block, সত্য);

  stmt = make_গ্রন্থি (OMP_TASK);
  বৃক্ষ_TYPE (stmt) = void_type_গ্রন্থি;
  OMP_TASK_CLAUSES (stmt) = clauses;
  OMP_TASK_BODY (stmt) = block;
  SET_রাশিমালা_LOCATION (stmt, loc);

  ফেরত add_stmt (stmt);
}

/* Generate GOMP_cancel call for #pragma omp cancel.  */

শূন্য
c_finish_omp_cancel (location_t loc, বৃক্ষ clauses)
{
  বৃক্ষ fn = builtin_decl_explicit (BUILT_IN_GOMP_CANCEL);
  পূর্ণসংখ্যা mask = 0;
  যদি (omp_find_clause (clauses, OMP_CLAUSE_PARALLEL))
    mask = 1;
  অন্যথা যদি (omp_find_clause (clauses, OMP_CLAUSE_FOR))
    mask = 2;
  অন্যথা যদি (omp_find_clause (clauses, OMP_CLAUSE_SECTIONS))
    mask = 4;
  অন্যথা যদি (omp_find_clause (clauses, OMP_CLAUSE_TASKGROUP))
    mask = 8;
  অন্যথা
    {
      error_at (loc, "%<#pragma omp cancel%> must specify one of "
		     "%<parallel%>, %<for%>, %<sections%> or %<taskgroup%> "
		     "clauses");
      ফেরত;
    }
  বৃক্ষ ifc = omp_find_clause (clauses, OMP_CLAUSE_IF);
  যদি (ifc != NULL_বৃক্ষ)
    {
      যদি (OMP_CLAUSE_IF_MODIFIER (ifc) != ERROR_MARK
	  && OMP_CLAUSE_IF_MODIFIER (ifc) != VOID_CST)
	error_at (OMP_CLAUSE_LOCATION (ifc),
		  "expected %<cancel%> %<if%> clause modifier");
      অন্যথা
	{
	  বৃক্ষ ifc2 = omp_find_clause (OMP_CLAUSE_CHAIN (ifc), OMP_CLAUSE_IF);
	  যদি (ifc2 != NULL_বৃক্ষ)
	    {
	      gcc_assert (OMP_CLAUSE_IF_MODIFIER (ifc) == VOID_CST
			  && OMP_CLAUSE_IF_MODIFIER (ifc2) != ERROR_MARK
			  && OMP_CLAUSE_IF_MODIFIER (ifc2) != VOID_CST);
	      error_at (OMP_CLAUSE_LOCATION (ifc2),
			"expected %<cancel%> %<if%> clause modifier");
	    }
	}

      বৃক্ষ type = বৃক্ষ_TYPE (OMP_CLAUSE_IF_রাশিমালা (ifc));
      ifc = fold_build2_loc (OMP_CLAUSE_LOCATION (ifc), NE_রাশিমালা,
			     boolean_type_গ্রন্থি, OMP_CLAUSE_IF_রাশিমালা (ifc),
			     build_zero_cst (type));
    }
  অন্যথা
    ifc = boolean_true_গ্রন্থি;
  বৃক্ষ stmt = build_call_রাশিমালা_loc (loc, fn, 2,
				   build_int_cst (integer_type_গ্রন্থি, mask),
				   ifc);
  add_stmt (stmt);
}

/* Generate GOMP_cancellation_point call for
   #pragma omp cancellation point.  */

শূন্য
c_finish_omp_cancellation_point (location_t loc, বৃক্ষ clauses)
{
  বৃক্ষ fn = builtin_decl_explicit (BUILT_IN_GOMP_CANCELLATION_POINT);
  পূর্ণসংখ্যা mask = 0;
  যদি (omp_find_clause (clauses, OMP_CLAUSE_PARALLEL))
    mask = 1;
  অন্যথা যদি (omp_find_clause (clauses, OMP_CLAUSE_FOR))
    mask = 2;
  অন্যথা যদি (omp_find_clause (clauses, OMP_CLAUSE_SECTIONS))
    mask = 4;
  অন্যথা যদি (omp_find_clause (clauses, OMP_CLAUSE_TASKGROUP))
    mask = 8;
  অন্যথা
    {
      error_at (loc, "%<#pragma omp cancellation point%> must specify one of "
		     "%<parallel%>, %<for%>, %<sections%> or %<taskgroup%> "
		     "clauses");
      ফেরত;
    }
  বৃক্ষ stmt = build_call_রাশিমালা_loc (loc, fn, 1,
				   build_int_cst (integer_type_গ্রন্থি, mask));
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

স্থির বৃক্ষ
handle_omp_array_sections_1 (বৃক্ষ c, বৃক্ষ t, vec<বৃক্ষ> &types,
			     যৌক্তিক &maybe_zero_len, unsigned পূর্ণসংখ্যা &first_non_one,
			     গণনা c_omp_region_type ort)
{
  বৃক্ষ ret, নিচের_bound, দৈর্ঘ্য, type;
  যৌক্তিক openacc = (ort & C_ORT_ACC) != 0;
  যদি (বৃক্ষ_CODE (t) != OMP_ARRAY_SECTION)
    {
      যদি (error_operand_p (t))
	ফেরত error_mark_গ্রন্থি;
      c_omp_address_inspector ai (OMP_CLAUSE_LOCATION (c), t);
      ret = t;
      যদি (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
	  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
	  && TYPE_ATOMIC (strip_array_types (বৃক্ষ_TYPE (t))))
	{
	  error_at (OMP_CLAUSE_LOCATION (c), "%<_Atomic%> %qE in %qs clause",
		    t, omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  ফেরত error_mark_গ্রন্থি;
	}
      যদি (!ai.check_clause (c))
	ফেরত error_mark_গ্রন্থি;
      অন্যথা যদি (ai.component_access_p ()
	       && (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TO
		   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_FROM))
	t = ai.get_মূল_term (সত্য);
      অন্যথা
	t = ai.unconverted_ref_origin ();
      যদি (t == error_mark_গ্রন্থি)
	ফেরত error_mark_গ্রন্থি;
      যদি (!VAR_P (t)
	  && (ort == C_ORT_ACC || !রাশিমালা_P (t))
	  && বৃক্ষ_CODE (t) != PARM_DECL)
	{
	  যদি (DECL_P (t))
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD is not a variable in %qs clause", t,
		      omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  অন্যথা
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qE is not a variable in %qs clause", t,
		      omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  ফেরত error_mark_গ্রন্থি;
	}
      অন্যথা যদি (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
	       && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
	       && TYPE_ATOMIC (বৃক্ষ_TYPE (t)))
	{
	  error_at (OMP_CLAUSE_LOCATION (c), "%<_Atomic%> %qD in %qs clause",
		    t, omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  ফেরত error_mark_গ্রন্থি;
	}
      অন্যথা যদি (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
	       && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
	       && VAR_P (t)
	       && DECL_THREAD_LOCAL_P (t))
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "%qD is threadprivate variable in %qs clause", t,
		    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  ফেরত error_mark_গ্রন্থি;
	}
      যদি ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY
	   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND)
	  && TYPE_ATOMIC (বৃক্ষ_TYPE (t))
	  && POINTER_TYPE_P (বৃক্ষ_TYPE (t)))
	{
	  /* If the array section is pointer based and the pointer
	     itself is _Atomic qualified, we need to atomically load
	     the pointer.  */
	  ret = convert_lvalue_to_rvalue (OMP_CLAUSE_LOCATION (c),
					  ret, মিথ্যা, মিথ্যা);
	}
      ফেরত ret;
    }

  ret = handle_omp_array_sections_1 (c, বৃক্ষ_OPERAND (t, 0), types,
				     maybe_zero_len, first_non_one, ort);
  যদি (ret == error_mark_গ্রন্থি || ret == NULL_বৃক্ষ)
    ফেরত ret;

  type = বৃক্ষ_TYPE (ret);
  নিচের_bound = বৃক্ষ_OPERAND (t, 1);
  দৈর্ঘ্য = বৃক্ষ_OPERAND (t, 2);

  যদি (নিচের_bound == error_mark_গ্রন্থি || দৈর্ঘ্য == error_mark_গ্রন্থি)
    ফেরত error_mark_গ্রন্থি;

  যদি (নিচের_bound && !INTEGRAL_TYPE_P (বৃক্ষ_TYPE (নিচের_bound)))
    {
      error_at (OMP_CLAUSE_LOCATION (c),
		"low bound %qE of array section does not have integral type",
		নিচের_bound);
      ফেরত error_mark_গ্রন্থি;
    }
  যদি (দৈর্ঘ্য && !INTEGRAL_TYPE_P (বৃক্ষ_TYPE (দৈর্ঘ্য)))
    {
      error_at (OMP_CLAUSE_LOCATION (c),
		"length %qE of array section does not have integral type",
		দৈর্ঘ্য);
      ফেরত error_mark_গ্রন্থি;
    }
  যদি (নিচের_bound
      && বৃক্ষ_CODE (নিচের_bound) == INTEGER_CST
      && TYPE_PRECISION (বৃক্ষ_TYPE (নিচের_bound))
	 > TYPE_PRECISION (sizetype))
    নিচের_bound = fold_convert (sizetype, নিচের_bound);
  যদি (দৈর্ঘ্য
      && বৃক্ষ_CODE (দৈর্ঘ্য) == INTEGER_CST
      && TYPE_PRECISION (বৃক্ষ_TYPE (দৈর্ঘ্য))
	 > TYPE_PRECISION (sizetype))
    দৈর্ঘ্য = fold_convert (sizetype, দৈর্ঘ্য);
  যদি (নিচের_bound == NULL_বৃক্ষ)
    নিচের_bound = integer_zero_গ্রন্থি;
  যদি (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
      && (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_ATTACH
	  || OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_DETACH))
    {
      যদি (দৈর্ঘ্য != integer_one_গ্রন্থি)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "expected single pointer in %qs clause",
		    user_omp_clause_code_name (c, openacc));
	  ফেরত error_mark_গ্রন্থি;
	}
    }
  যদি (দৈর্ঘ্য != NULL_বৃক্ষ)
    {
      যদি (!integer_nonzerop (দৈর্ঘ্য))
	{
	  যদি (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY
	      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
	      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
	      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
	      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TASK_REDUCTION)
	    {
	      যদি (integer_zerop (দৈর্ঘ্য))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "zero length array section in %qs clause",
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  ফেরত error_mark_গ্রন্থি;
		}
	    }
	  অন্যথা
	    maybe_zero_len = সত্য;
	}
      যদি (first_non_one == types.দৈর্ঘ্য ()
	  && (বৃক্ষ_CODE (দৈর্ঘ্য) != INTEGER_CST || integer_onep (দৈর্ঘ্য)))
	first_non_one++;
    }
  যদি (বৃক্ষ_CODE (type) == ARRAY_TYPE)
    {
      যদি (দৈর্ঘ্য == NULL_বৃক্ষ
	  && (TYPE_DOMAIN (type) == NULL_বৃক্ষ
	      || TYPE_MAX_মান (TYPE_DOMAIN (type)) == NULL_বৃক্ষ))
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "for unknown bound array type length expression must "
		    "be specified");
	  ফেরত error_mark_গ্রন্থি;
	}
      যদি (বৃক্ষ_CODE (নিচের_bound) == INTEGER_CST
	  && বৃক্ষ_int_cst_sgn (নিচের_bound) == -1)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "negative low bound in array section in %qs clause",
		    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  ফেরত error_mark_গ্রন্থি;
	}
      যদি (দৈর্ঘ্য != NULL_বৃক্ষ
	  && বৃক্ষ_CODE (দৈর্ঘ্য) == INTEGER_CST
	  && বৃক্ষ_int_cst_sgn (দৈর্ঘ্য) == -1)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "negative length in array section in %qs clause",
		    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  ফেরত error_mark_গ্রন্থি;
	}
      যদি (TYPE_DOMAIN (type)
	  && TYPE_MAX_মান (TYPE_DOMAIN (type))
	  && বৃক্ষ_CODE (TYPE_MAX_মান (TYPE_DOMAIN (type)))
			== INTEGER_CST)
	{
	  বৃক্ষ আকার_2
	    = fold_convert (sizetype, TYPE_MAX_মান (TYPE_DOMAIN (type)));
	  আকার_2 = আকার_binop (PLUS_রাশিমালা, আকার_2, আকার_one_গ্রন্থি);
	  যদি (বৃক্ষ_CODE (নিচের_bound) == INTEGER_CST)
	    {
	      যদি (বৃক্ষ_int_cst_lt (আকার_2, নিচের_bound))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "low bound %qE above array section size "
			    "in %qs clause", নিচের_bound,
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  ফেরত error_mark_গ্রন্থি;
		}
	      যদি (বৃক্ষ_int_cst_equal (আকার_2, নিচের_bound))
		{
		  যদি (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TASK_REDUCTION)
		    {
		      error_at (OMP_CLAUSE_LOCATION (c),
				"zero length array section in %qs clause",
				omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		      ফেরত error_mark_গ্রন্থি;
		    }
		  maybe_zero_len = সত্য;
		}
	      অন্যথা যদি (দৈর্ঘ্য == NULL_বৃক্ষ
		       && first_non_one == types.দৈর্ঘ্য ()
		       && বৃক্ষ_int_cst_equal
			    (TYPE_MAX_মান (TYPE_DOMAIN (type)),
			     নিচের_bound))
		first_non_one++;
	    }
	  অন্যথা যদি (দৈর্ঘ্য == NULL_বৃক্ষ)
	    {
	      যদি (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
		  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
		  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_REDUCTION
		  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_IN_REDUCTION
		  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_TASK_REDUCTION)
		maybe_zero_len = সত্য;
	      যদি (first_non_one == types.দৈর্ঘ্য ())
		first_non_one++;
	    }
	  যদি (দৈর্ঘ্য && বৃক্ষ_CODE (দৈর্ঘ্য) == INTEGER_CST)
	    {
	      যদি (বৃক্ষ_int_cst_lt (আকার_2, দৈর্ঘ্য))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "length %qE above array section size "
			    "in %qs clause", দৈর্ঘ্য,
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  ফেরত error_mark_গ্রন্থি;
		}
	      যদি (বৃক্ষ_CODE (নিচের_bound) == INTEGER_CST)
		{
		  বৃক্ষ lbpluslen
		    = আকার_binop (PLUS_রাশিমালা,
				  fold_convert (sizetype, নিচের_bound),
				  fold_convert (sizetype, দৈর্ঘ্য));
		  যদি (বৃক্ষ_CODE (lbpluslen) == INTEGER_CST
		      && বৃক্ষ_int_cst_lt (আকার_2, lbpluslen))
		    {
		      error_at (OMP_CLAUSE_LOCATION (c),
				"high bound %qE above array section size "
				"in %qs clause", lbpluslen,
				omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		      ফেরত error_mark_গ্রন্থি;
		    }
		}
	    }
	}
      অন্যথা যদি (দৈর্ঘ্য == NULL_বৃক্ষ)
	{
	  যদি (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
	      && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
	      && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_REDUCTION
	      && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_IN_REDUCTION
	      && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_TASK_REDUCTION)
	    maybe_zero_len = সত্য;
	  যদি (first_non_one == types.দৈর্ঘ্য ())
	    first_non_one++;
	}

      /* For [lb:] we will need to evaluate lb more than once.  */
      যদি (দৈর্ঘ্য == NULL_বৃক্ষ && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND)
	{
	  বৃক্ষ lb = save_রাশিমালা (নিচের_bound);
	  যদি (lb != নিচের_bound)
	    {
	      বৃক্ষ_OPERAND (t, 1) = lb;
	      নিচের_bound = lb;
	    }
	}
    }
  অন্যথা যদি (বৃক্ষ_CODE (type) == POINTER_TYPE)
    {
      যদি (দৈর্ঘ্য == NULL_বৃক্ষ)
	{
	  যদি (বৃক্ষ_CODE (ret) == PARM_DECL && C_ARRAY_PARAMETER (ret))
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "for array function parameter length expression "
		      "must be specified");
	  অন্যথা
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "for pointer type length expression must be specified");
	  ফেরত error_mark_গ্রন্থি;
	}
      যদি (দৈর্ঘ্য != NULL_বৃক্ষ
	  && বৃক্ষ_CODE (দৈর্ঘ্য) == INTEGER_CST
	  && বৃক্ষ_int_cst_sgn (দৈর্ঘ্য) == -1)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "negative length in array section in %qs clause",
		    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  ফেরত error_mark_গ্রন্থি;
	}
      /* If there is a pointer type anywhere but in the very first
	 array-section-subscript, the array section could be non-contiguous.  */
      যদি (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
	  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
	  && বৃক্ষ_CODE (বৃক্ষ_OPERAND (t, 0)) == OMP_ARRAY_SECTION)
	{
	  /* If any prior dimension has a non-one length, then deem this
	     array section as non-contiguous.  */
	  জন্য (বৃক্ষ d = বৃক্ষ_OPERAND (t, 0);
	       বৃক্ষ_CODE (d) == OMP_ARRAY_SECTION;
	       d = বৃক্ষ_OPERAND (d, 0))
	    {
	      বৃক্ষ d_দৈর্ঘ্য = বৃক্ষ_OPERAND (d, 2);
	      যদি (d_দৈর্ঘ্য == NULL_বৃক্ষ || !integer_onep (d_দৈর্ঘ্য))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "array section is not contiguous in %qs clause",
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  ফেরত error_mark_গ্রন্থি;
		}
	    }
	}
    }
  অন্যথা
    {
      error_at (OMP_CLAUSE_LOCATION (c),
		"%qE does not have pointer or array type", ret);
      ফেরত error_mark_গ্রন্থি;
    }
  যদি (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND)
    types.safe_ঠেলো (বৃক্ষ_TYPE (ret));
  /* We will need to evaluate lb more than once.  */
  বৃক্ষ lb = save_রাশিমালা (নিচের_bound);
  যদি (lb != নিচের_bound)
    {
      বৃক্ষ_OPERAND (t, 1) = lb;
      নিচের_bound = lb;
    }
  ret = build_array_ref (OMP_CLAUSE_LOCATION (c), ret, নিচের_bound);
  ফেরত ret;
}

/* Handle array sections for clause C.  */

স্থির যৌক্তিক
handle_omp_array_sections (বৃক্ষ &c, গণনা c_omp_region_type ort)
{
  যৌক্তিক maybe_zero_len = মিথ্যা;
  unsigned পূর্ণসংখ্যা first_non_one = 0;
  auto_vec<বৃক্ষ, 10> types;
  বৃক্ষ *tp = &OMP_CLAUSE_DECL (c);
  যদি ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
       || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY)
      && OMP_ITERATOR_DECL_P (*tp))
    tp = &বৃক্ষ_মান (*tp);
  বৃক্ষ first = handle_omp_array_sections_1 (c, *tp, types,
					    maybe_zero_len, first_non_one,
					    ort);
  যদি (first == error_mark_গ্রন্থি)
    ফেরত সত্য;
  যদি (first == NULL_বৃক্ষ)
    ফেরত মিথ্যা;
  যদি (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY)
    {
      বৃক্ষ t = *tp;
      বৃক্ষ tem = NULL_বৃক্ষ;
      /* Need to evaluate side effects in the length expressions
	 if any.  */
      যখন (বৃক্ষ_CODE (t) == বৃক্ষ_LIST)
	{
	  যদি (বৃক্ষ_মান (t) && বৃক্ষ_SIDE_EFFECTS (বৃক্ষ_মান (t)))
	    {
	      যদি (tem == NULL_বৃক্ষ)
		tem = বৃক্ষ_মান (t);
	      অন্যথা
		tem = build2 (COMPOUND_রাশিমালা, বৃক্ষ_TYPE (tem),
			      বৃক্ষ_মান (t), tem);
	    }
	  t = বৃক্ষ_CHAIN (t);
	}
      যদি (tem)
	first = build2 (COMPOUND_রাশিমালা, বৃক্ষ_TYPE (first), tem, first);
      first = c_fully_fold (first, মিথ্যা, ফাঁকা, সত্য);
      *tp = first;
    }
  অন্যথা
    {
      unsigned পূর্ণসংখ্যা অঙ্ক = types.দৈর্ঘ্য (), i;
      বৃক্ষ t, side_effects = NULL_বৃক্ষ, আকার_2 = NULL_বৃক্ষ;
      বৃক্ষ condition = NULL_বৃক্ষ;

      যদি (int_আকার_in_bytes (বৃক্ষ_TYPE (first)) <= 0)
	maybe_zero_len = সত্য;

      জন্য (i = অঙ্ক, t = OMP_CLAUSE_DECL (c); i > 0;
	   t = বৃক্ষ_OPERAND (t, 0))
	{
	  বৃক্ষ নিচের_bound = বৃক্ষ_OPERAND (t, 1);
	  বৃক্ষ দৈর্ঘ্য = বৃক্ষ_OPERAND (t, 2);

	  i--;
	  যদি (নিচের_bound
	      && বৃক্ষ_CODE (নিচের_bound) == INTEGER_CST
	      && TYPE_PRECISION (বৃক্ষ_TYPE (নিচের_bound))
		 > TYPE_PRECISION (sizetype))
	    নিচের_bound = fold_convert (sizetype, নিচের_bound);
	  যদি (দৈর্ঘ্য
	      && বৃক্ষ_CODE (দৈর্ঘ্য) == INTEGER_CST
	      && TYPE_PRECISION (বৃক্ষ_TYPE (দৈর্ঘ্য))
		 > TYPE_PRECISION (sizetype))
	    দৈর্ঘ্য = fold_convert (sizetype, দৈর্ঘ্য);
	  যদি (নিচের_bound == NULL_বৃক্ষ)
	    নিচের_bound = integer_zero_গ্রন্থি;
	  যদি (!maybe_zero_len && i > first_non_one)
	    {
	      যদি (integer_nonzerop (নিচের_bound))
		যাও do_warn_noncontiguous;
	      যদি (দৈর্ঘ্য != NULL_বৃক্ষ
		  && বৃক্ষ_CODE (দৈর্ঘ্য) == INTEGER_CST
		  && TYPE_DOMAIN (types[i])
		  && TYPE_MAX_মান (TYPE_DOMAIN (types[i]))
		  && বৃক্ষ_CODE (TYPE_MAX_মান (TYPE_DOMAIN (types[i])))
		     == INTEGER_CST)
		{
		  বৃক্ষ আকার_2;
		  আকার_2 = আকার_binop (PLUS_রাশিমালা,
				     TYPE_MAX_মান (TYPE_DOMAIN (types[i])),
				     আকার_one_গ্রন্থি);
		  যদি (!বৃক্ষ_int_cst_equal (দৈর্ঘ্য, আকার_2))
		    {
		     do_warn_noncontiguous:
		      error_at (OMP_CLAUSE_LOCATION (c),
				"array section is not contiguous in %qs "
				"clause",
				omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		      ফেরত সত্য;
		    }
		}
	      যদি (দৈর্ঘ্য != NULL_বৃক্ষ
		  && বৃক্ষ_SIDE_EFFECTS (দৈর্ঘ্য))
		{
		  যদি (side_effects == NULL_বৃক্ষ)
		    side_effects = দৈর্ঘ্য;
		  অন্যথা
		    side_effects = build2 (COMPOUND_রাশিমালা,
					   বৃক্ষ_TYPE (side_effects),
					   দৈর্ঘ্য, side_effects);
		}
	    }
	  অন্যথা
	    {
	      বৃক্ষ l;

	      যদি (i > first_non_one
		  && ((দৈর্ঘ্য && integer_nonzerop (দৈর্ঘ্য))
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TASK_REDUCTION))
		চালু;
	      যদি (দৈর্ঘ্য)
		l = fold_convert (sizetype, দৈর্ঘ্য);
	      অন্যথা
		{
		  l = আকার_binop (PLUS_রাশিমালা,
				  TYPE_MAX_মান (TYPE_DOMAIN (types[i])),
				  আকার_one_গ্রন্থি);
		  l = আকার_binop (MINUS_রাশিমালা, l,
				  fold_convert (sizetype, নিচের_bound));
		}
	      যদি (i > first_non_one)
		{
		  l = fold_build2 (NE_রাশিমালা, boolean_type_গ্রন্থি, l,
				   আকার_zero_গ্রন্থি);
		  যদি (condition == NULL_বৃক্ষ)
		    condition = l;
		  অন্যথা
		    condition = fold_build2 (BIT_AND_রাশিমালা, boolean_type_গ্রন্থি,
					     l, condition);
		}
	      অন্যথা যদি (আকার_2 == NULL_বৃক্ষ)
		{
		  আকার_2 = আকার_in_bytes (বৃক্ষ_TYPE (types[i]));
		  বৃক্ষ eltype = বৃক্ষ_TYPE (types[অঙ্ক - 1]);
		  যখন (বৃক্ষ_CODE (eltype) == ARRAY_TYPE)
		    eltype = বৃক্ষ_TYPE (eltype);
		  যদি (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TASK_REDUCTION)
		    {
		      যদি (integer_zerop (আকার_2)
			  || integer_zerop (আকার_in_bytes (eltype)))
			{
			  error_at (OMP_CLAUSE_LOCATION (c),
				    "zero length array section in %qs clause",
				    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
			  ফেরত error_mark_গ্রন্থি;
			}
		      আকার_2 = আকার_binop (EXACT_DIV_রাশিমালা, আকার_2,
					 আকার_in_bytes (eltype));
		    }
		  আকার_2 = আকার_binop (MULT_রাশিমালা, আকার_2, l);
		  যদি (condition)
		    আকার_2 = fold_build3 (COND_রাশিমালা, sizetype, condition,
					আকার_2, আকার_zero_গ্রন্থি);
		}
	      অন্যথা
		আকার_2 = আকার_binop (MULT_রাশিমালা, আকার_2, l);
	    }
	}
      যদি (side_effects)
	আকার_2 = build2 (COMPOUND_রাশিমালা, sizetype, side_effects, আকার_2);
      যদি (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
	  || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
	  || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TASK_REDUCTION)
	{
	  আকার_2 = আকার_binop (MINUS_রাশিমালা, আকার_2, আকার_one_গ্রন্থি);
	  আকার_2 = c_fully_fold (আকার_2, মিথ্যা, ফাঁকা);
	  আকার_2 = save_রাশিমালা (আকার_2);
	  বৃক্ষ সূচক_type = build_সূচক_type (আকার_2);
	  বৃক্ষ eltype = বৃক্ষ_TYPE (first);
	  যখন (বৃক্ষ_CODE (eltype) == ARRAY_TYPE)
	    eltype = বৃক্ষ_TYPE (eltype);
	  বৃক্ষ type = c_build_array_type (eltype, সূচক_type);
	  বৃক্ষ ptype = c_build_pointer_type (eltype);
	  যদি (বৃক্ষ_CODE (বৃক্ষ_TYPE (t)) == ARRAY_TYPE)
	    t = build_fold_addr_রাশিমালা (t);
	  বৃক্ষ t2 = build_fold_addr_রাশিমালা (first);
	  t2 = fold_convert_loc (OMP_CLAUSE_LOCATION (c),
				 ptrdiff_type_গ্রন্থি, t2);
	  t2 = fold_build2_loc (OMP_CLAUSE_LOCATION (c), MINUS_রাশিমালা,
				ptrdiff_type_গ্রন্থি, t2,
				fold_convert_loc (OMP_CLAUSE_LOCATION (c),
						  ptrdiff_type_গ্রন্থি, t));
	  t2 = c_fully_fold (t2, মিথ্যা, ফাঁকা);
	  যদি (বৃক্ষ_fits_shwi_p (t2))
	    t = build2 (MEM_REF, type, t,
			build_int_cst (ptype, বৃক্ষ_to_shwi (t2)));
	  অন্যথা
	    {
	      t2 = fold_convert_loc (OMP_CLAUSE_LOCATION (c), sizetype, t2);
	      t = build2_loc (OMP_CLAUSE_LOCATION (c), POINTER_PLUS_রাশিমালা,
			      বৃক্ষ_TYPE (t), t, t2);
	      t = build2 (MEM_REF, type, t, build_int_cst (ptype, 0));
	    }
	  OMP_CLAUSE_DECL (c) = t;
	  ফেরত মিথ্যা;
	}
      first = c_fully_fold (first, মিথ্যা, ফাঁকা);
      OMP_CLAUSE_DECL (c) = first;
      যদি (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_HAS_DEVICE_ADDR)
	ফেরত মিথ্যা;
      /* Don't set OMP_CLAUSE_SIZE for bare attach/detach clauses.  */
      যদি (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP
	  || (OMP_CLAUSE_MAP_KIND (c) != GOMP_MAP_ATTACH
	      && OMP_CLAUSE_MAP_KIND (c) != GOMP_MAP_DETACH
	      && OMP_CLAUSE_MAP_KIND (c) != GOMP_MAP_FORCE_DETACH))
	{
	  যদি (আকার_2)
	    আকার_2 = c_fully_fold (আকার_2, মিথ্যা, ফাঁকা);
	  OMP_CLAUSE_আকার (c) = আকার_2;
	}

      যদি (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP)
	ফেরত মিথ্যা;

      auto_vec<omp_addr_token *, 10> addr_tokens;

      যদি (!omp_parse_রাশিমালা (addr_tokens, first))
	ফেরত সত্য;

      c_omp_address_inspector ai (OMP_CLAUSE_LOCATION (c), t);

      বৃক্ষ nc = ai.expand_map_clause (c, first, addr_tokens, ort);
      যদি (nc != error_mark_গ্রন্থি)
	{
	  using নামাকাশ omp_addr_tokenizer;

	  যদি (ai.maybe_zero_দৈর্ঘ্য_array_section (c))
	    OMP_CLAUSE_MAP_MAYBE_ZERO_দৈর্ঘ্য_ARRAY_SECTION (c) = 1;

	  /* !!! If we're accessing a base decl via chained access
	     methods (e.g. multiple indirections), duplicate clause
	     detection won't work properly.  Skip it in that case.  */
	  যদি ((addr_tokens[0]->type == STRUCTURE_BASE
	       || addr_tokens[0]->type == ARRAY_BASE)
	      && addr_tokens[0]->u.structure_base_kind == BASE_DECL
	      && addr_tokens[1]->type == ACCESS_METHOD
	      && omp_access_chain_p (addr_tokens, 1))
	    c = nc;

	  ফেরত মিথ্যা;
	}
    }
  ফেরত মিথ্যা;
}

/* Helper function of finish_omp_clauses.  Clone STMT as if we were making
   an inline call.  But, remap
   the OMP_DECL1 VAR_DECL (omp_out resp. omp_orig) to PLACEHOLDER
   and OMP_DECL2 VAR_DECL (omp_in resp. omp_priv) to DECL.  */

স্থির বৃক্ষ
c_clone_omp_udr (বৃক্ষ stmt, বৃক্ষ omp_decl1, বৃক্ষ omp_decl2,
		 বৃক্ষ decl, বৃক্ষ placeholder)
{
  copy_body_তথ্য id;
  hash_map<বৃক্ষ, বৃক্ষ> decl_map;

  decl_map.put (omp_decl1, placeholder);
  decl_map.put (omp_decl2, decl);
  memset (&id, 0, আকার (id));
  id.src_fn = DECL_CONTEXT (omp_decl1);
  id.dst_fn = current_function_decl;
  id.src_cfun = DECL_STRUCT_FUNCTION (id.src_fn);
  id.decl_map = &decl_map;

  id.copy_decl = copy_decl_no_change;
  id.transform_call_graph_edges = CB_CGE_DUPLICATE;
  id.transform_new_cfg = সত্য;
  id.transform_return_to_modify = মিথ্যা;
  id.eh_lp_nr = 0;
  walk_বৃক্ষ (&stmt, copy_বৃক্ষ_body_r, &id, ফাঁকা);
  ফেরত stmt;
}

/* Helper function of c_finish_omp_clauses, called via walk_tree.
   Find OMP_CLAUSE_PLACEHOLDER (passed in DATA) in *TP.  */

স্থির বৃক্ষ
c_find_omp_placeholder_r (বৃক্ষ *tp, পূর্ণসংখ্যা *, শূন্য *তথ্য)
{
  যদি (*tp == (বৃক্ষ) তথ্য)
    ফেরত *tp;
  ফেরত NULL_বৃক্ষ;
}

/* Similarly, but also walk aggregate fields.  */

কাঠামো c_find_omp_var_s { বৃক্ষ var; hash_set<বৃক্ষ> *pset; };

স্থির বৃক্ষ
c_find_omp_var_r (বৃক্ষ *tp, পূর্ণসংখ্যা *, শূন্য *তথ্য)
{
  যদি (*tp == ((কাঠামো c_find_omp_var_s *) তথ্য)->var)
    ফেরত *tp;
  যদি (RECORD_OR_UNION_TYPE_P (*tp))
    {
      বৃক্ষ field;
      hash_set<বৃক্ষ> *pset = ((কাঠামো c_find_omp_var_s *) তথ্য)->pset;

      জন্য (field = TYPE_FIELDS (*tp); field;
	   field = DECL_CHAIN (field))
	যদি (বৃক্ষ_CODE (field) == FIELD_DECL)
	  {
	    বৃক্ষ ret = walk_বৃক্ষ (&DECL_FIELD_OFFSET (field),
				  c_find_omp_var_r, তথ্য, pset);
	    যদি (ret)
	      ফেরত ret;
	    ret = walk_বৃক্ষ (&DECL_আকার (field), c_find_omp_var_r, তথ্য, pset);
	    যদি (ret)
	      ফেরত ret;
	    ret = walk_বৃক্ষ (&DECL_আকার_UNIT (field), c_find_omp_var_r, তথ্য,
			     pset);
	    যদি (ret)
	      ফেরত ret;
	    ret = walk_বৃক্ষ (&বৃক্ষ_TYPE (field), c_find_omp_var_r, তথ্য, pset);
	    যদি (ret)
	      ফেরত ret;
	  }
    }
  অন্যথা যদি (INTEGRAL_TYPE_P (*tp))
    ফেরত walk_বৃক্ষ (&TYPE_MAX_মান (*tp), c_find_omp_var_r, তথ্য,
		      ((কাঠামো c_find_omp_var_s *) তথ্য)->pset);
  ফেরত NULL_বৃক্ষ;
}

/* Finish OpenMP iterators ITER.  Return true if they are erroneous
   and clauses containing them should be removed.  */

স্থির যৌক্তিক
c_omp_finish_iterators (বৃক্ষ iter)
{
  যৌক্তিক ret = মিথ্যা;
  জন্য (বৃক্ষ it = iter; it; it = বৃক্ষ_CHAIN (it))
    {
      বৃক্ষ var = OMP_ITERATOR_VAR (it);
      বৃক্ষ begin = OMP_ITERATOR_BEGIN (it);
      বৃক্ষ end = OMP_ITERATOR_END (it);
      বৃক্ষ step = OMP_ITERATOR_STEP (it);
      বৃক্ষ orig_step;
      বৃক্ষ type = বৃক্ষ_TYPE (var);
      location_t loc = DECL_SOURCE_LOCATION (var);
      যদি (type == error_mark_গ্রন্থি)
	{
	  ret = সত্য;
	  চালু;
	}
      যদি (!INTEGRAL_TYPE_P (type) && !POINTER_TYPE_P (type))
	{
	  error_at (loc, "iterator %qD has neither integral nor pointer type",
		    var);
	  ret = সত্য;
	  চালু;
	}
      অন্যথা যদি (TYPE_ATOMIC (type))
	{
	  error_at (loc, "iterator %qD has %<_Atomic%> qualified type", var);
	  ret = সত্য;
	  চালু;
	}
      অন্যথা যদি (TYPE_READONLY (type))
	{
	  error_at (loc, "iterator %qD has const qualified type", var);
	  ret = সত্য;
	  চালু;
	}
      অন্যথা যদি (step == error_mark_গ্রন্থি
	       || বৃক্ষ_TYPE (step) == error_mark_গ্রন্থি)
	{
	  ret = সত্য;
	  চালু;
	}
      অন্যথা যদি (!INTEGRAL_TYPE_P (বৃক্ষ_TYPE (step)))
	{
	  error_at (রাশিমালা_LOC_OR_LOC (step, loc),
		    "iterator step with non-integral type");
	  ret = সত্য;
	  চালু;
	}
      begin = c_fully_fold (build_c_cast (loc, type, begin), মিথ্যা, ফাঁকা);
      end = c_fully_fold (build_c_cast (loc, type, end), মিথ্যা, ফাঁকা);
      orig_step = save_রাশিমালা (c_fully_fold (step, মিথ্যা, ফাঁকা));
      বৃক্ষ stype = POINTER_TYPE_P (type) ? sizetype : type;
      step = c_fully_fold (build_c_cast (loc, stype, orig_step), মিথ্যা, ফাঁকা);
      যদি (POINTER_TYPE_P (type))
	{
	  begin = save_রাশিমালা (begin);
	  step = pointer_int_যোগ (loc, PLUS_রাশিমালা, begin, step);
	  step = fold_build2_loc (loc, MINUS_রাশিমালা, sizetype,
				  fold_convert (sizetype, step),
				  fold_convert (sizetype, begin));
	  step = fold_convert (ssizetype, step);
	}
      যদি (integer_zerop (step))
	{
	  error_at (loc, "iterator %qD has zero step", var);
	  ret = সত্য;
	  চালু;
	}

      যদি (begin == error_mark_গ্রন্থি
	  || end == error_mark_গ্রন্থি
	  || step == error_mark_গ্রন্থি
	  || orig_step == error_mark_গ্রন্থি)
	{
	  ret = সত্য;
	  চালু;
	}
      hash_set<বৃক্ষ> pset;
      বৃক্ষ it2;
      জন্য (it2 = বৃক্ষ_CHAIN (it); it2; it2 = বৃক্ষ_CHAIN (it2))
	{
	  বৃক্ষ var2 = OMP_ITERATOR_VAR (it2);
	  বৃক্ষ begin2 = OMP_ITERATOR_BEGIN (it2);
	  বৃক্ষ end2 = OMP_ITERATOR_END (it2);
	  বৃক্ষ step2 = OMP_ITERATOR_STEP (it2);
	  বৃক্ষ type2 = বৃক্ষ_TYPE (var2);
	  location_t loc2 = DECL_SOURCE_LOCATION (var2);
	  কাঠামো c_find_omp_var_s তথ্য = { var, &pset };
	  যদি (walk_বৃক্ষ (&type2, c_find_omp_var_r, &তথ্য, &pset))
	    {
	      error_at (loc2,
			"type of iterator %qD refers to outer iterator %qD",
			var2, var);
	      বিরতি;
	    }
	  অন্যথা যদি (walk_বৃক্ষ (&begin2, c_find_omp_var_r, &তথ্য, &pset))
	    {
	      error_at (রাশিমালা_LOC_OR_LOC (begin2, loc2),
			"begin expression refers to outer iterator %qD", var);
	      বিরতি;
	    }
	  অন্যথা যদি (walk_বৃক্ষ (&end2, c_find_omp_var_r, &তথ্য, &pset))
	    {
	      error_at (রাশিমালা_LOC_OR_LOC (end2, loc2),
			"end expression refers to outer iterator %qD", var);
	      বিরতি;
	    }
	  অন্যথা যদি (walk_বৃক্ষ (&step2, c_find_omp_var_r, &তথ্য, &pset))
	    {
	      error_at (রাশিমালা_LOC_OR_LOC (step2, loc2),
			"step expression refers to outer iterator %qD", var);
	      বিরতি;
	    }
	}
      যদি (it2)
	{
	  ret = সত্য;
	  চালু;
	}
      OMP_ITERATOR_BEGIN (it) = begin;
      OMP_ITERATOR_END (it) = end;
      OMP_ITERATOR_STEP (it) = step;
      OMP_ITERATOR_ORIG_STEP (it) = orig_step;
    }
  ফেরত ret;
}

/* Ensure that pointers are used in OpenACC attach and detach clauses.
   Return true if an error has been detected.  */

স্থির যৌক্তিক
c_oacc_check_attachments (বৃক্ষ c)
{
  যদি (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP)
    ফেরত মিথ্যা;

  /* OpenACC attach / detach clauses must be pointers.  */
  যদি (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_ATTACH
      || OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_DETACH)
    {
      বৃক্ষ t = OMP_CLAUSE_DECL (c);

      যখন (বৃক্ষ_CODE (t) == OMP_ARRAY_SECTION)
	t = বৃক্ষ_OPERAND (t, 0);

      যদি (বৃক্ষ_CODE (বৃক্ষ_TYPE (t)) != POINTER_TYPE)
	{
	  error_at (OMP_CLAUSE_LOCATION (c), "expected pointer in %qs clause",
		    user_omp_clause_code_name (c, সত্য));
	  ফেরত সত্য;
	}
    }

  ফেরত মিথ্যা;
}

/* For all elements of CLAUSES, validate them against their constraints.
   Remove any elements from the list that are invalid.  */

বৃক্ষ
c_finish_omp_clauses (বৃক্ষ clauses, গণনা c_omp_region_type ort)
{
  bitmap_শীর্ষ generic_শীর্ষ, firstprivate_শীর্ষ, lastprivate_শীর্ষ;
  bitmap_শীর্ষ aligned_শীর্ষ, map_শীর্ষ, map_field_শীর্ষ, map_firstprivate_শীর্ষ;
  bitmap_শীর্ষ oacc_reduction_শীর্ষ, is_on_device_শীর্ষ;
  বৃক্ষ c, t, type, *pc;
  বৃক্ষ simdlen = NULL_বৃক্ষ, safelen = NULL_বৃক্ষ;
  যৌক্তিক branch_seen = মিথ্যা;
  যৌক্তিক copyprivate_seen = মিথ্যা;
  যৌক্তিক mergeable_seen = মিথ্যা;
  বৃক্ষ *detach_seen = ফাঁকা;
  যৌক্তিক linear_variable_step_check = মিথ্যা;
  বৃক্ষ *nowait_clause = ফাঁকা;
  বৃক্ষ *grainsize_seen = ফাঁকা;
  যৌক্তিক অঙ্ক_tasks_seen = মিথ্যা;
  বৃক্ষ ordered_clause = NULL_বৃক্ষ;
  বৃক্ষ schedule_clause = NULL_বৃক্ষ;
  যৌক্তিক oacc_async = মিথ্যা;
  বৃক্ষ last_iterators = NULL_বৃক্ষ;
  যৌক্তিক last_iterators_remove = মিথ্যা;
  বৃক্ষ *nogroup_seen = ফাঁকা;
  বৃক্ষ *order_clause = ফাঁকা;
  /* 1 if normal/task reduction has been seen, -1 if inscan reduction
     has been seen, -2 if mixed inscan/normal reduction diagnosed.  */
  পূর্ণসংখ্যা reduction_seen = 0;
  যৌক্তিক allocate_seen = মিথ্যা;
  যৌক্তিক implicit_moved = মিথ্যা;
  যৌক্তিক target_in_reduction_seen = মিথ্যা;
  বৃক্ষ *full_seen = ফাঁকা;
  যৌক্তিক partial_seen = মিথ্যা;
  যৌক্তিক openacc = (ort & C_ORT_ACC) != 0;
  যৌক্তিক init_seen = মিথ্যা;
  যৌক্তিক init_use_destroy_seen = মিথ্যা;
  বৃক্ষ init_no_targetsync_clause = NULL_বৃক্ষ;
  বৃক্ষ depend_clause = NULL_বৃক্ষ;

  যদি (!openacc)
    clauses = omp_remove_duplicate_maps (clauses, সত্য);

  bitmap_obstack_initialize (ফাঁকা);
  bitmap_initialize (&generic_শীর্ষ, &bitmap_default_obstack);
  bitmap_initialize (&firstprivate_শীর্ষ, &bitmap_default_obstack);
  bitmap_initialize (&lastprivate_শীর্ষ, &bitmap_default_obstack);
  bitmap_initialize (&aligned_শীর্ষ, &bitmap_default_obstack);
  /* If ort == C_ORT_OMP_DECLARE_SIMD used as uniform_head instead.  */
  bitmap_initialize (&map_শীর্ষ, &bitmap_default_obstack);
  bitmap_initialize (&map_field_শীর্ষ, &bitmap_default_obstack);
  bitmap_initialize (&map_firstprivate_শীর্ষ, &bitmap_default_obstack);
  /* If ort == C_ORT_OMP used as nontemporal_head or use_device_xxx_head
     instead and for ort == C_ORT_OMP_TARGET used as in_reduction_head.  */
  bitmap_initialize (&oacc_reduction_শীর্ষ, &bitmap_default_obstack);
  bitmap_initialize (&is_on_device_শীর্ষ, &bitmap_default_obstack);

  যদি (openacc)
    জন্য (c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
      যদি (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ASYNC)
	{
	  oacc_async = সত্য;
	  বিরতি;
	}

  বৃক্ষ *grp_start_p = ফাঁকা, grp_sentinel = NULL_বৃক্ষ;

  জন্য (pc = &clauses, c = clauses; c ; c = *pc)
    {
      যৌক্তিক remove = মিথ্যা;
      যৌক্তিক need_complete = মিথ্যা;
      যৌক্তিক need_implicitly_determined = মিথ্যা;

      /* We've reached the end of a list of expanded nodes.  Reset the group
	 start pointer.  */
      যদি (c == grp_sentinel)
	{
	  যদি (grp_start_p
	      && OMP_CLAUSE_HAS_ITERATORS (*grp_start_p))
	    জন্য (বৃক্ষ gc = *grp_start_p; gc != grp_sentinel;
		 gc = OMP_CLAUSE_CHAIN (gc))
	      OMP_CLAUSE_ITERATORS (gc) = OMP_CLAUSE_ITERATORS (*grp_start_p);
	  grp_start_p = ফাঁকা;
	}

      নির্বাচন (OMP_CLAUSE_CODE (c))
	{
	ক্ষেত্র OMP_CLAUSE_SHARED:
	  need_implicitly_determined = সত্য;
	  যাও check_dup_generic;

	ক্ষেত্র OMP_CLAUSE_PRIVATE:
	  need_complete = সত্য;
	  need_implicitly_determined = সত্য;
	  যাও check_dup_generic;

	ক্ষেত্র OMP_CLAUSE_REDUCTION:
	  যদি (reduction_seen == 0)
	    reduction_seen = OMP_CLAUSE_REDUCTION_INSCAN (c) ? -1 : 1;
	  অন্যথা যদি (reduction_seen != -2
		   && reduction_seen != (OMP_CLAUSE_REDUCTION_INSCAN (c)
					 ? -1 : 1))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<inscan%> and non-%<inscan%> %<reduction%> clauses "
			"on the same construct");
	      reduction_seen = -2;
	    }
	  /* FALLTHRU */
	ক্ষেত্র OMP_CLAUSE_IN_REDUCTION:
	ক্ষেত্র OMP_CLAUSE_TASK_REDUCTION:
	  need_implicitly_determined = সত্য;
	  t = OMP_CLAUSE_DECL (c);
	  যদি (বৃক্ষ_CODE (t) == OMP_ARRAY_SECTION)
	    {
	      যদি (handle_omp_array_sections (c, ort))
		{
		  remove = সত্য;
		  বিরতি;
		}

	      t = OMP_CLAUSE_DECL (c);
	      যদি (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
		  && OMP_CLAUSE_REDUCTION_INSCAN (c))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<inscan%> %<reduction%> clause with array "
			    "section");
		  remove = সত্য;
		  বিরতি;
		}
	    }
	  t = require_complete_type (OMP_CLAUSE_LOCATION (c), t);
	  যদি (t == error_mark_গ্রন্থি)
	    {
	      remove = সত্য;
	      বিরতি;
	    }
	  যদি (oacc_async)
	    c_mark_addressable (t);
	  type = বৃক্ষ_TYPE (t);
	  যদি (বৃক্ষ_CODE (t) == MEM_REF)
	    type = বৃক্ষ_TYPE (type);
	  যদি (বৃক্ষ_CODE (type) == ARRAY_TYPE)
	    {
	      বৃক্ষ oatype = type;
	      gcc_assert (বৃক্ষ_CODE (t) != MEM_REF);
	      যখন (বৃক্ষ_CODE (type) == ARRAY_TYPE)
		type = বৃক্ষ_TYPE (type);
	      যদি (integer_zerop (TYPE_আকার_UNIT (type)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD in %<reduction%> clause is a zero size array",
			    t);
		  remove = সত্য;
		  বিরতি;
		}
	      বৃক্ষ আকার_2 = আকার_binop (EXACT_DIV_রাশিমালা, TYPE_আকার_UNIT (oatype),
				      TYPE_আকার_UNIT (type));
	      যদি (integer_zerop (আকার_2))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD in %<reduction%> clause is a zero size array",
			    t);
		  remove = সত্য;
		  বিরতি;
		}
	      আকার_2 = আকার_binop (MINUS_রাশিমালা, আকার_2, আকার_one_গ্রন্থি);
	      আকার_2 = save_রাশিমালা (আকার_2);
	      বৃক্ষ সূচক_type = build_সূচক_type (আকার_2);
	      বৃক্ষ atype = c_build_array_type (TYPE_MAIN_VARIANT (type),
					       সূচক_type);
	      atype = c_build_qualified_type (atype, TYPE_QUALS (type));
	      বৃক্ষ ptype = c_build_pointer_type (type);
	      যদি (বৃক্ষ_CODE (বৃক্ষ_TYPE (t)) == ARRAY_TYPE)
		t = build_fold_addr_রাশিমালা (t);
	      t = build2 (MEM_REF, atype, t, build_int_cst (ptype, 0));
	      OMP_CLAUSE_DECL (c) = t;
	    }
	  যদি (TYPE_ATOMIC (type))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<_Atomic%> %qE in %<reduction%> clause", t);
	      remove = সত্য;
	      বিরতি;
	    }
	  যদি (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_REDUCTION
	      || OMP_CLAUSE_REDUCTION_TASK (c))
	    {
	      /* Disallow zero sized or potentially zero sized task
		 reductions.  */
	      যদি (integer_zerop (TYPE_আকার_UNIT (type)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "zero sized type %qT in %qs clause", type,
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  remove = সত্য;
		  বিরতি;
		}
	      অন্যথা যদি (বৃক্ষ_CODE (TYPE_আকার_UNIT (type)) != INTEGER_CST)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "variable sized type %qT in %qs clause", type,
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  remove = সত্য;
		  বিরতি;
		}
	    }
	  যদি (OMP_CLAUSE_REDUCTION_PLACEHOLDER (c) == NULL_বৃক্ষ
	      && (FLOAT_TYPE_P (type)
		  || বৃক্ষ_CODE (type) == COMPLEX_TYPE))
	    {
	      গণনা বৃক্ষ_code r_code = OMP_CLAUSE_REDUCTION_CODE (c);
	      ধ্রুবক অক্ষর *r_name = ফাঁকা;

	      নির্বাচন (r_code)
		{
		ক্ষেত্র PLUS_রাশিমালা:
		ক্ষেত্র MULT_রাশিমালা:
		ক্ষেত্র MINUS_রাশিমালা:
		ক্ষেত্র TRUTH_ANDIF_রাশিমালা:
		ক্ষেত্র TRUTH_ORIF_রাশিমালা:
		  বিরতি;
		ক্ষেত্র MIN_রাশিমালা:
		  যদি (বৃক্ষ_CODE (type) == COMPLEX_TYPE)
		    r_name = "min";
		  বিরতি;
		ক্ষেত্র MAX_রাশিমালা:
		  যদি (বৃক্ষ_CODE (type) == COMPLEX_TYPE)
		    r_name = "max";
		  বিরতি;
		ক্ষেত্র BIT_AND_রাশিমালা:
		  r_name = "&";
		  বিরতি;
		ক্ষেত্র BIT_XOR_রাশিমালা:
		  r_name = "^";
		  বিরতি;
		ক্ষেত্র BIT_IOR_রাশিমালা:
		  r_name = "|";
		  বিরতি;
		পূর্বনির্ধারিত:
		  gcc_unreachable ();
		}
	      যদি (r_name)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qE has invalid type for %<reduction(%s)%>",
			    t, r_name);
		  remove = সত্য;
		  বিরতি;
		}
	    }
	  অন্যথা যদি (OMP_CLAUSE_REDUCTION_PLACEHOLDER (c) == error_mark_গ্রন্থি)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"user defined reduction not found for %qE", t);
	      remove = সত্য;
	      বিরতি;
	    }
	  অন্যথা যদি (OMP_CLAUSE_REDUCTION_PLACEHOLDER (c))
	    {
	      বৃক্ষ list = OMP_CLAUSE_REDUCTION_PLACEHOLDER (c);
	      type = TYPE_MAIN_VARIANT (type);
	      বৃক্ষ placeholder = build_decl (OMP_CLAUSE_LOCATION (c),
					     VAR_DECL, NULL_বৃক্ষ, type);
	      বৃক্ষ decl_placeholder = NULL_বৃক্ষ;
	      OMP_CLAUSE_REDUCTION_PLACEHOLDER (c) = placeholder;
	      DECL_ARTIFICIAL (placeholder) = 1;
	      DECL_IGNORED_P (placeholder) = 1;
	      যদি (বৃক্ষ_CODE (t) == MEM_REF)
		{
		  decl_placeholder = build_decl (OMP_CLAUSE_LOCATION (c),
						 VAR_DECL, NULL_বৃক্ষ, type);
		  OMP_CLAUSE_REDUCTION_DECL_PLACEHOLDER (c) = decl_placeholder;
		  DECL_ARTIFICIAL (decl_placeholder) = 1;
		  DECL_IGNORED_P (decl_placeholder) = 1;
		}
	      যদি (বৃক্ষ_ADDRESSABLE (বৃক্ষ_VEC_ELT (list, 0)))
		c_mark_addressable (placeholder);
	      যদি (বৃক্ষ_ADDRESSABLE (বৃক্ষ_VEC_ELT (list, 1)))
		c_mark_addressable (decl_placeholder ? decl_placeholder
				    : OMP_CLAUSE_DECL (c));
	      OMP_CLAUSE_REDUCTION_MERGE (c)
		= c_clone_omp_udr (বৃক্ষ_VEC_ELT (list, 2),
				   বৃক্ষ_VEC_ELT (list, 0),
				   বৃক্ষ_VEC_ELT (list, 1),
				   decl_placeholder ? decl_placeholder
				   : OMP_CLAUSE_DECL (c), placeholder);
	      OMP_CLAUSE_REDUCTION_MERGE (c)
		= build3_loc (OMP_CLAUSE_LOCATION (c), BIND_রাশিমালা,
			      void_type_গ্রন্থি, NULL_বৃক্ষ,
			      OMP_CLAUSE_REDUCTION_MERGE (c), NULL_বৃক্ষ);
	      বৃক্ষ_SIDE_EFFECTS (OMP_CLAUSE_REDUCTION_MERGE (c)) = 1;
	      যদি (বৃক্ষ_VEC_দৈর্ঘ্য (list) == 6)
		{
		  যদি (বৃক্ষ_ADDRESSABLE (বৃক্ষ_VEC_ELT (list, 3)))
		    c_mark_addressable (decl_placeholder ? decl_placeholder
					: OMP_CLAUSE_DECL (c));
		  যদি (বৃক্ষ_ADDRESSABLE (বৃক্ষ_VEC_ELT (list, 4)))
		    c_mark_addressable (placeholder);
		  বৃক্ষ init = বৃক্ষ_VEC_ELT (list, 5);
		  যদি (init == error_mark_গ্রন্থি)
		    init = DECL_INITIAL (বৃক্ষ_VEC_ELT (list, 3));
		  OMP_CLAUSE_REDUCTION_INIT (c)
		    = c_clone_omp_udr (init, বৃক্ষ_VEC_ELT (list, 4),
				       বৃক্ষ_VEC_ELT (list, 3),
				       decl_placeholder ? decl_placeholder
				       : OMP_CLAUSE_DECL (c), placeholder);
		  যদি (বৃক্ষ_VEC_ELT (list, 5) == error_mark_গ্রন্থি)
		    {
		      বৃক্ষ v = decl_placeholder ? decl_placeholder : t;
		      OMP_CLAUSE_REDUCTION_INIT (c)
			= build2 (INIT_রাশিমালা, বৃক্ষ_TYPE (v), v,
				  OMP_CLAUSE_REDUCTION_INIT (c));
		    }
		  যদি (walk_বৃক্ষ (&OMP_CLAUSE_REDUCTION_INIT (c),
				 c_find_omp_placeholder_r,
				 placeholder, ফাঁকা))
		    OMP_CLAUSE_REDUCTION_OMP_ORIG_REF (c) = 1;
		}
	      অন্যথা
		{
		  বৃক্ষ init;
		  বৃক্ষ v = decl_placeholder ? decl_placeholder : t;
		  যদি (AGGREGATE_TYPE_P (বৃক্ষ_TYPE (v)))
		    init = build_constructor (বৃক্ষ_TYPE (v), ফাঁকা);
		  অন্যথা
		    init = fold_convert (বৃক্ষ_TYPE (v), integer_zero_গ্রন্থি);
		  OMP_CLAUSE_REDUCTION_INIT (c)
		    = build2 (INIT_রাশিমালা, বৃক্ষ_TYPE (v), v, init);
		}
	      OMP_CLAUSE_REDUCTION_INIT (c)
		= build3_loc (OMP_CLAUSE_LOCATION (c), BIND_রাশিমালা,
			      void_type_গ্রন্থি, NULL_বৃক্ষ,
			       OMP_CLAUSE_REDUCTION_INIT (c), NULL_বৃক্ষ);
	      বৃক্ষ_SIDE_EFFECTS (OMP_CLAUSE_REDUCTION_INIT (c)) = 1;
	    }
	  যদি (বৃক্ষ_CODE (t) == MEM_REF)
	    {
	      যদি (TYPE_আকার_UNIT (বৃক্ষ_TYPE (বৃক্ষ_TYPE (t))) == NULL_বৃক্ষ
		  || বৃক্ষ_CODE (TYPE_আকার_UNIT (বৃক্ষ_TYPE (বৃক্ষ_TYPE (t))))
		     != INTEGER_CST)
		{
		  sorry ("variable length element type in array "
			 "%<reduction%> clause");
		  remove = সত্য;
		  বিরতি;
		}
	      t = বৃক্ষ_OPERAND (t, 0);
	      যদি (বৃক্ষ_CODE (t) == POINTER_PLUS_রাশিমালা)
		t = বৃক্ষ_OPERAND (t, 0);
	      যদি (বৃক্ষ_CODE (t) == ADDR_রাশিমালা)
		t = বৃক্ষ_OPERAND (t, 0);
	    }
	  যাও check_dup_generic_t;

	ক্ষেত্র OMP_CLAUSE_COPYPRIVATE:
	  copyprivate_seen = সত্য;
	  যদি (nowait_clause)
	    {
	      error_at (OMP_CLAUSE_LOCATION (*nowait_clause),
			"%<nowait%> clause must not be used together "
			"with %<copyprivate%> clause");
	      *nowait_clause = OMP_CLAUSE_CHAIN (*nowait_clause);
	      nowait_clause = ফাঁকা;
	    }
	  যাও check_dup_generic;

	ক্ষেত্র OMP_CLAUSE_COPYIN:
	  t = OMP_CLAUSE_DECL (c);
	  যদি (!VAR_P (t) || !DECL_THREAD_LOCAL_P (t))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE must be %<threadprivate%> for %<copyin%>", t);
	      remove = সত্য;
	      বিরতি;
	    }
	  যাও check_dup_generic;

	ক্ষেত্র OMP_CLAUSE_LINEAR:
	  যদি (ort != C_ORT_OMP_DECLARE_SIMD)
	    need_implicitly_determined = সত্য;
	  t = OMP_CLAUSE_DECL (c);
	  যদি (ort != C_ORT_OMP_DECLARE_SIMD
	      && OMP_CLAUSE_LINEAR_KIND (c) != OMP_CLAUSE_LINEAR_DEFAULT
	      && OMP_CLAUSE_LINEAR_OLD_LINEAR_MODIFIER (c))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"modifier should not be specified in %<linear%> "
			"clause on %<simd%> or %<for%> constructs when not "
			"using OpenMP 5.2 modifiers");
	      OMP_CLAUSE_LINEAR_KIND (c) = OMP_CLAUSE_LINEAR_DEFAULT;
	    }
	  যদি (!INTEGRAL_TYPE_P (বৃক্ষ_TYPE (t))
	      && বৃক্ষ_CODE (বৃক্ষ_TYPE (t)) != POINTER_TYPE)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"linear clause applied to non-integral non-pointer "
			"variable with type %qT", বৃক্ষ_TYPE (t));
	      remove = সত্য;
	      বিরতি;
	    }
	  যদি (TYPE_ATOMIC (বৃক্ষ_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<_Atomic%> %qD in %<linear%> clause", t);
	      remove = সত্য;
	      বিরতি;
	    }
	  যদি (ort == C_ORT_OMP_DECLARE_SIMD)
	    {
	      বৃক্ষ s = OMP_CLAUSE_LINEAR_STEP (c);
	      যদি (বৃক্ষ_CODE (s) == PARM_DECL)
		{
		  OMP_CLAUSE_LINEAR_VARIABLE_STRIDE (c) = 1;
		  /* map_head bitmap is used as uniform_head if
		     declare_simd.  */
		  যদি (!bitmap_bit_p (&map_শীর্ষ, DECL_UID (s)))
		    linear_variable_step_check = সত্য;
		  যাও check_dup_generic;
		}
	      যদি (বৃক্ষ_CODE (s) != INTEGER_CST)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<linear%> clause step %qE is neither constant "
			    "nor a parameter", s);
		  remove = সত্য;
		  বিরতি;
		}
	    }
	  যদি (বৃক্ষ_CODE (বৃক্ষ_TYPE (OMP_CLAUSE_DECL (c))) == POINTER_TYPE)
	    {
	      বৃক্ষ s = OMP_CLAUSE_LINEAR_STEP (c);
	      s = pointer_int_যোগ (OMP_CLAUSE_LOCATION (c), PLUS_রাশিমালা,
				   OMP_CLAUSE_DECL (c), s);
	      s = fold_build2_loc (OMP_CLAUSE_LOCATION (c), MINUS_রাশিমালা,
				   sizetype, fold_convert (sizetype, s),
				   fold_convert
				     (sizetype, OMP_CLAUSE_DECL (c)));
	      যদি (s == error_mark_গ্রন্থি)
		s = আকার_one_গ্রন্থি;
	      OMP_CLAUSE_LINEAR_STEP (c) = s;
	    }
	  অন্যথা
	    OMP_CLAUSE_LINEAR_STEP (c)
	      = fold_convert (বৃক্ষ_TYPE (t), OMP_CLAUSE_LINEAR_STEP (c));
	  যাও check_dup_generic;

	check_dup_generic:
	  t = OMP_CLAUSE_DECL (c);
	check_dup_generic_t:
	  যদি (!VAR_P (t) && বৃক্ষ_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %qs", t,
			omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	      remove = সত্য;
	    }
	  অন্যথা যদি ((openacc && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION)
		   || (ort == C_ORT_OMP
		       && (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_USE_DEVICE_PTR
			   || (OMP_CLAUSE_CODE (c)
			       == OMP_CLAUSE_USE_DEVICE_ADDR)))
		   || (ort == C_ORT_OMP_TARGET
		       && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION))
	    {
	      যদি (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
		  && (bitmap_bit_p (&generic_শীর্ষ, DECL_UID (t))
		      || bitmap_bit_p (&firstprivate_শীর্ষ, DECL_UID (t))))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in data-sharing "
			    "clauses", t);
		  remove = সত্য;
		  বিরতি;
		}
	      যদি (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION)
		target_in_reduction_seen = সত্য;
	      যদি (bitmap_bit_p (&oacc_reduction_শীর্ষ, DECL_UID (t)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    openacc
			    ? "%qD appears more than once in reduction clauses"
			    : "%qD appears more than once in data clauses",
			    t);
		  remove = সত্য;
		}
	      অন্যথা
		bitmap_set_bit (&oacc_reduction_শীর্ষ, DECL_UID (t));
	    }
	  অন্যথা যদি (bitmap_bit_p (&generic_শীর্ষ, DECL_UID (t))
		   || bitmap_bit_p (&firstprivate_শীর্ষ, DECL_UID (t))
		   || bitmap_bit_p (&lastprivate_শীর্ষ, DECL_UID (t))
		   || bitmap_bit_p (&map_firstprivate_শীর্ষ, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in data clauses", t);
	      remove = সত্য;
	    }
	  অন্যথা যদি ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_PRIVATE
		    || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_HAS_DEVICE_ADDR
		    || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IS_DEVICE_PTR)
		   && bitmap_bit_p (&map_শীর্ষ, DECL_UID (t)))
	    {
	      যদি (openacc)
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears more than once in data clauses", t);
	      অন্যথা
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears both in data and map clauses", t);
	      remove = সত্য;
	    }
	  অন্যথা
	    bitmap_set_bit (&generic_শীর্ষ, DECL_UID (t));
	  বিরতি;

	ক্ষেত্র OMP_CLAUSE_FIRSTPRIVATE:
	  যদি (OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (c) && !implicit_moved)
	    {
	    move_implicit:
	      implicit_moved = সত্য;
	      /* Move firstprivate and map clauses with
		 OMP_CLAUSE_{FIRSTPRIVATE,MAP}_IMPLICIT set to the end of
		 clauses chain.  */
	      বৃক্ষ cl1 = NULL_বৃক্ষ, cl2 = NULL_বৃক্ষ;
	      বৃক্ষ *pc1 = pc, *pc2 = &cl1, *pc3 = &cl2;
	      যখন (*pc1)
		যদি (OMP_CLAUSE_CODE (*pc1) == OMP_CLAUSE_FIRSTPRIVATE
		    && OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (*pc1))
		  {
		    *pc3 = *pc1;
		    pc3 = &OMP_CLAUSE_CHAIN (*pc3);
		    *pc1 = OMP_CLAUSE_CHAIN (*pc1);
		  }
		অন্যথা যদি (OMP_CLAUSE_CODE (*pc1) == OMP_CLAUSE_MAP
			 && OMP_CLAUSE_MAP_IMPLICIT (*pc1))
		  {
		    *pc2 = *pc1;
		    pc2 = &OMP_CLAUSE_CHAIN (*pc2);
		    *pc1 = OMP_CLAUSE_CHAIN (*pc1);
		  }
		অন্যথা
		  pc1 = &OMP_CLAUSE_CHAIN (*pc1);
	      *pc3 = ফাঁকা;
	      *pc2 = cl2;
	      *pc1 = cl1;
	      চালু;
	    }
	  t = OMP_CLAUSE_DECL (c);
	  need_complete = সত্য;
	  need_implicitly_determined = সত্য;
	  যদি (!VAR_P (t) && বৃক্ষ_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %<firstprivate%>", t);
	      remove = সত্য;
	    }
	  অন্যথা যদি (OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (c)
		   && !OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT_TARGET (c)
		   && bitmap_bit_p (&map_firstprivate_শীর্ষ, DECL_UID (t)))
	    remove = সত্য;
	  অন্যথা যদি (bitmap_bit_p (&generic_শীর্ষ, DECL_UID (t))
		   || bitmap_bit_p (&firstprivate_শীর্ষ, DECL_UID (t))
		   || bitmap_bit_p (&map_firstprivate_শীর্ষ, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in data clauses", t);
	      remove = সত্য;
	    }
	  অন্যথা যদি (bitmap_bit_p (&map_শীর্ষ, DECL_UID (t))
		   || bitmap_bit_p (&map_field_শীর্ষ, DECL_UID (t)))
	    {
	      যদি (openacc)
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears more than once in data clauses", t);
	      অন্যথা যদি (OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (c)
		       && !OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT_TARGET (c))
		/* Silently drop the clause.  */;
	      অন্যথা
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears both in data and map clauses", t);
	      remove = সত্য;
	    }
	  অন্যথা
	    bitmap_set_bit (&firstprivate_শীর্ষ, DECL_UID (t));
	  বিরতি;

	ক্ষেত্র OMP_CLAUSE_LASTPRIVATE:
	  t = OMP_CLAUSE_DECL (c);
	  need_complete = সত্য;
	  need_implicitly_determined = সত্য;
	  যদি (!VAR_P (t) && বৃক্ষ_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %<lastprivate%>", t);
	      remove = সত্য;
	    }
	  অন্যথা যদি (bitmap_bit_p (&generic_শীর্ষ, DECL_UID (t))
		   || bitmap_bit_p (&lastprivate_শীর্ষ, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
		     "%qE appears more than once in data clauses", t);
	      remove = সত্য;
	    }
	  অন্যথা
	    bitmap_set_bit (&lastprivate_শীর্ষ, DECL_UID (t));
	  বিরতি;

	ক্ষেত্র OMP_CLAUSE_ALIGNED:
	  t = OMP_CLAUSE_DECL (c);
	  যদি (!VAR_P (t) && বৃক্ষ_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in %<aligned%> clause", t);
	      remove = সত্য;
	    }
	  অন্যথা যদি (!POINTER_TYPE_P (বৃক্ষ_TYPE (t))
		   && বৃক্ষ_CODE (বৃক্ষ_TYPE (t)) != ARRAY_TYPE)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE in %<aligned%> clause is neither a pointer nor "
			"an array", t);
	      remove = সত্য;
	    }
	  অন্যথা যদি (TYPE_ATOMIC (বৃক্ষ_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<_Atomic%> %qD in %<aligned%> clause", t);
	      remove = সত্য;
	      বিরতি;
	    }
	  অন্যথা যদি (bitmap_bit_p (&aligned_শীর্ষ, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in %<aligned%> clauses",
			t);
	      remove = সত্য;
	    }
	  অন্যথা
	    bitmap_set_bit (&aligned_শীর্ষ, DECL_UID (t));
	  বিরতি;

	ক্ষেত্র OMP_CLAUSE_NONTEMPORAL:
	  t = OMP_CLAUSE_DECL (c);
	  যদি (!VAR_P (t) && বৃক্ষ_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in %<nontemporal%> clause", t);
	      remove = সত্য;
	    }
	  অন্যথা যদি (bitmap_bit_p (&oacc_reduction_শীর্ষ, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in %<nontemporal%> "
			"clauses", t);
	      remove = সত্য;
	    }
	  অন্যথা
	    bitmap_set_bit (&oacc_reduction_শীর্ষ, DECL_UID (t));
	  বিরতি;

	ক্ষেত্র OMP_CLAUSE_ALLOCATE:
	  t = OMP_CLAUSE_DECL (c);
	  যদি (!VAR_P (t) && বৃক্ষ_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in %<allocate%> clause", t);
	      remove = সত্য;
	    }
	  অন্যথা যদি (bitmap_bit_p (&aligned_শীর্ষ, DECL_UID (t)))
	    {
	      warning_at (OMP_CLAUSE_LOCATION (c), OPT_Wopenmp,
			  "%qE appears more than once in %<allocate%> clauses",
			  t);
	      remove = সত্য;
	    }
	  অন্যথা
	    {
	      bitmap_set_bit (&aligned_শীর্ষ, DECL_UID (t));
	      যদি (!OMP_CLAUSE_ALLOCATE_COMBINED (c))
		allocate_seen = সত্য;
	    }
	  বিরতি;

	ক্ষেত্র OMP_CLAUSE_DOACROSS:
	  t = OMP_CLAUSE_DECL (c);
	  যদি (t == NULL_বৃক্ষ)
	    বিরতি;
	  যদি (OMP_CLAUSE_DOACROSS_KIND (c) == OMP_CLAUSE_DOACROSS_SINK)
	    {
	      gcc_assert (বৃক্ষ_CODE (t) == বৃক্ষ_LIST);
	      জন্য (; t; t = বৃক্ষ_CHAIN (t))
		{
		  বৃক্ষ decl = বৃক্ষ_মান (t);
		  যদি (বৃক্ষ_CODE (বৃক্ষ_TYPE (decl)) == POINTER_TYPE)
		    {
		      বৃক্ষ offset = বৃক্ষ_PURPOSE (t);
		      যৌক্তিক neg = wi::neg_p (wi::to_wide (offset));
		      offset = fold_unary (ABS_রাশিমালা, বৃক্ষ_TYPE (offset), offset);
		      বৃক্ষ t2 = pointer_int_যোগ (OMP_CLAUSE_LOCATION (c),
						 neg ? MINUS_রাশিমালা : PLUS_রাশিমালা,
						 decl, offset);
		      t2 = fold_build2_loc (OMP_CLAUSE_LOCATION (c), MINUS_রাশিমালা,
					    sizetype,
					    fold_convert (sizetype, t2),
					    fold_convert (sizetype, decl));
		      যদি (t2 == error_mark_গ্রন্থি)
			{
			  remove = সত্য;
			  বিরতি;
			}
		      বৃক্ষ_PURPOSE (t) = t2;
		    }
		}
	      বিরতি;
	    }
	  gcc_unreachable ();

	ক্ষেত্র OMP_CLAUSE_USES_ALLOCATORS:
	  t = OMP_CLAUSE_USES_ALLOCATORS_ALLOCATOR (c);
	  যদি (t == error_mark_গ্রন্থি)
	    {
	      remove = সত্য;
	      বিরতি;
	    }
	  যদি ((VAR_P (t) || বৃক্ষ_CODE (t) == PARM_DECL)
	      && (bitmap_bit_p (&generic_শীর্ষ, DECL_UID (t))
		  || bitmap_bit_p (&map_শীর্ষ, DECL_UID (t))
		  || bitmap_bit_p (&firstprivate_শীর্ষ, DECL_UID (t))
		  || bitmap_bit_p (&lastprivate_শীর্ষ, DECL_UID (t))))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in data clauses", t);
	      remove = সত্য;
	      বিরতি;
	    }
	  অন্যথা
	    bitmap_set_bit (&generic_শীর্ষ, DECL_UID (t));
	  যদি (বৃক্ষ_CODE (বৃক্ষ_TYPE (t)) != ENUMERAL_TYPE
	      || strcmp (IDENTIFIER_POINTER (TYPE_IDENTIFIER (বৃক্ষ_TYPE (t))),
			 "omp_allocator_handle_t") != 0)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"allocator %qE must be of %<omp_allocator_handle_t%> "
			"type", t);
	      remove = সত্য;
	      বিরতি;
	    }
	  বৃক্ষ init;
	  যদি (!DECL_P (t)
	      || (বৃক্ষ_CODE (t) == CONST_DECL
		  && ((init = DECL_INITIAL(t)) == nullptr
		      || বৃক্ষ_CODE (init) != INTEGER_CST
		      || ((wi::to_widest (init) < 0
			   || wi::to_widest (init) > GOMP_OMP_PREDEF_ALLOC_MAX)
			  && (wi::to_widest (init) < GOMP_OMPX_PREDEF_ALLOC_MIN
			      || (wi::to_widest (init)
				  > GOMP_OMPX_PREDEF_ALLOC_MAX))))))
	    {
	      remove = সত্য;
	      error_at (OMP_CLAUSE_LOCATION (c),
			"allocator %qE must be either a variable or a "
			"predefined allocator", t);
	      বিরতি;
	    }
	  অন্যথা যদি (বৃক্ষ_CODE (t) == CONST_DECL)
	    {
	      /* omp_null_allocator is ignored and for predefined allocators,
		 no special handling is required; thus, mark them removed. */
	      remove = সত্য;

	      যদি (OMP_CLAUSE_USES_ALLOCATORS_MEMSPACE (c)
		  || OMP_CLAUSE_USES_ALLOCATORS_TRAITS (c))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "modifiers cannot be used with predefined "
			    "allocator %qE", t);
		  বিরতি;
		}
	    }
	  t = OMP_CLAUSE_USES_ALLOCATORS_MEMSPACE (c);
	  যদি (t == error_mark_গ্রন্থি)
	    {
	      remove = সত্য;
	      বিরতি;
	    }
	  যদি (t != NULL_বৃক্ষ
	      && ((বৃক্ষ_CODE (t) != CONST_DECL && বৃক্ষ_CODE (t) != INTEGER_CST)
		  || বৃক্ষ_CODE (বৃক্ষ_TYPE (t)) != ENUMERAL_TYPE
		  || strcmp (IDENTIFIER_POINTER (TYPE_IDENTIFIER (বৃক্ষ_TYPE (t))),
			     "omp_memspace_handle_t") != 0))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c), "memspace modifier %qE must be"
			" constant enum of %<omp_memspace_handle_t%> type", t);
	      remove = সত্য;
	      বিরতি;
	    }
	  t = OMP_CLAUSE_USES_ALLOCATORS_TRAITS (c);
	  যদি (t == error_mark_গ্রন্থি)
	    {
	      remove = সত্য;
	      বিরতি;
	    }
	  যদি (t != NULL_বৃক্ষ
	      && t != error_mark_গ্রন্থি
	      && (DECL_EXTERNAL (t)
		  || বৃক্ষ_CODE (t) == PARM_DECL))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c), "traits array %qE must be "
			"defined in same scope as the construct on which the "
			"clause appears", t);
	      remove = সত্য;
	    }
	  যদি (t != NULL_বৃক্ষ)
	    {
	      যৌক্তিক type_err = মিথ্যা;

	      যদি (বৃক্ষ_CODE (বৃক্ষ_TYPE (t)) != ARRAY_TYPE
		  || DECL_আকার (t) == NULL_বৃক্ষ
		  || !COMPLETE_TYPE_P (বৃক্ষ_TYPE (t)))
		type_err = সত্য;
	      অন্যথা
		{
		  বৃক্ষ elem_t = বৃক্ষ_TYPE (বৃক্ষ_TYPE (t));
		  যদি (বৃক্ষ_CODE (elem_t) != RECORD_TYPE
		      || strcmp (IDENTIFIER_POINTER (TYPE_IDENTIFIER (elem_t)),
				 "omp_alloctrait_t") != 0
		      || !TYPE_READONLY (elem_t))
		    type_err = সত্য;
		}
	      যদি (type_err)
		{
		  যদি (t != error_mark_গ্রন্থি)
		    error_at (OMP_CLAUSE_LOCATION (c), "traits array %qE must "
			      "be of %<const omp_alloctrait_t []%> type", t);
		  অন্যথা
		    error_at (OMP_CLAUSE_LOCATION (c), "traits array must "
			      "be of %<const omp_alloctrait_t []%> type");
		  remove = সত্য;
		}
	      অন্যথা
		{
		  বৃক্ষ cst_val = decl_constant_মান_1 (t, সত্য);
		  যদি (cst_val == t)
		    {
		      error_at (OMP_CLAUSE_LOCATION (c), "traits array must be "
				"initialized with constants");

		      remove = সত্য;
		    }
		}
	    }
	  যদি (remove)
	    বিরতি;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  চালু;
	ক্ষেত্র OMP_CLAUSE_DEPEND:
	  depend_clause = c;
	  /* FALLTHRU */
	ক্ষেত্র OMP_CLAUSE_AFFINITY:
	  t = OMP_CLAUSE_DECL (c);
	  যদি (OMP_ITERATOR_DECL_P (t))
	    {
	      যদি (বৃক্ষ_PURPOSE (t) != last_iterators)
		last_iterators_remove
		  = c_omp_finish_iterators (বৃক্ষ_PURPOSE (t));
	      last_iterators = বৃক্ষ_PURPOSE (t);
	      t = বৃক্ষ_মান (t);
	      যদি (last_iterators_remove)
		t = error_mark_গ্রন্থি;
	    }
	  অন্যথা
	    last_iterators = NULL_বৃক্ষ;
	  যদি (বৃক্ষ_CODE (t) == OMP_ARRAY_SECTION)
	    {
	      যদি (handle_omp_array_sections (c, ort))
		remove = সত্য;
	      অন্যথা যদি (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
		       && OMP_CLAUSE_DEPEND_KIND (c) == OMP_CLAUSE_DEPEND_DEPOBJ)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<depend%> clause with %<depobj%> dependence "
			    "type on array section");
		  remove = সত্য;
		}
	      বিরতি;
	    }
	  যদি (t == error_mark_গ্রন্থি)
	    remove = সত্য;
	  অন্যথা যদি (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
		   && t == ridpointers[RID_OMP_ALL_MEMORY])
	    {
	      যদি (OMP_CLAUSE_DEPEND_KIND (c) != OMP_CLAUSE_DEPEND_OUT
		  && OMP_CLAUSE_DEPEND_KIND (c) != OMP_CLAUSE_DEPEND_INOUT)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<omp_all_memory%> used with %<depend%> kind "
			    "other than %<out%> or %<inout%>");
		  remove = সত্য;
		}
	    }
	  অন্যথা যদি (!lvalue_p (t))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not lvalue expression nor array section in "
			"%qs clause", t,
			omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	      remove = সত্য;
	    }
	  অন্যথা যদি (বৃক্ষ_CODE (t) == COMPONENT_REF
		   && DECL_C_BIT_FIELD (বৃক্ষ_OPERAND (t, 1)))
	    {
	      gcc_assert (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
			  || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY);
	      error_at (OMP_CLAUSE_LOCATION (c),
			"bit-field %qE in %qs clause", t,
			omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	      remove = সত্য;
	    }
	  অন্যথা যদি (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
		   && OMP_CLAUSE_DEPEND_KIND (c) == OMP_CLAUSE_DEPEND_DEPOBJ)
	    {
	      যদি (!c_omp_depend_t_p (বৃক্ষ_TYPE (t)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qE does not have %<omp_depend_t%> type in "
			    "%<depend%> clause with %<depobj%> dependence "
			    "type", t);
		  remove = সত্য;
		}
	    }
	  অন্যথা যদি (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
		   && c_omp_depend_t_p (বৃক্ষ_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE should not have %<omp_depend_t%> type in "
			"%<depend%> clause with dependence type other than "
			"%<depobj%>", t);
	      remove = সত্য;
	    }
	  যদি (!remove)
	    {
	      যদি (t == ridpointers[RID_OMP_ALL_MEMORY])
		t = null_pointer_গ্রন্থি;
	      অন্যথা
		{
		  বৃক্ষ addr = build_unary_op (OMP_CLAUSE_LOCATION (c),
					      ADDR_রাশিমালা, t, মিথ্যা);
		  যদি (addr == error_mark_গ্রন্থি)
		    {
		      remove = সত্য;
		      বিরতি;
		    }
		  t = build_indirect_ref (OMP_CLAUSE_LOCATION (c), addr,
					  RO_UNARY_STAR);
		  যদি (t == error_mark_গ্রন্থি)
		    {
		      remove = সত্য;
		      বিরতি;
		    }
		}
	      যদি (OMP_ITERATOR_DECL_P (OMP_CLAUSE_DECL (c)))
		বৃক্ষ_মান (OMP_CLAUSE_DECL (c)) = t;
	      অন্যথা
		OMP_CLAUSE_DECL (c) = t;
	    }
	  বিরতি;

	ক্ষেত্র OMP_CLAUSE_MAP:
	  যদি (OMP_CLAUSE_MAP_IMPLICIT (c) && !implicit_moved)
	    যাও move_implicit;
	  যদি (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_ঠেলো_MAPPER_NAME
	      || OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_বের_করো_MAPPER_NAME)
	    {
	      remove = সত্য;
	      বিরতি;
	    }
	  /* FALLTHRU */
	ক্ষেত্র OMP_CLAUSE_TO:
	ক্ষেত্র OMP_CLAUSE_FROM:
	  যদি (OMP_CLAUSE_ITERATORS (c)
	      && c_omp_finish_iterators (OMP_CLAUSE_ITERATORS (c)))
	    {
	      t = error_mark_গ্রন্থি;
	      বিরতি;
	    }
	  /* FALLTHRU */
	ক্ষেত্র OMP_CLAUSE__CACHE_:
	  {
	    using নামাকাশ omp_addr_tokenizer;
	    auto_vec<omp_addr_token *, 10> addr_tokens;

	    t = OMP_CLAUSE_DECL (c);
	    যদি (বৃক্ষ_CODE (t) == OMP_ARRAY_SECTION)
	      {
		grp_start_p = pc;
		grp_sentinel = OMP_CLAUSE_CHAIN (c);

		যদি (handle_omp_array_sections (c, ort))
		  remove = সত্য;
		অন্যথা
		  {
		    t = OMP_CLAUSE_DECL (c);
		    যদি (!omp_mappable_type (বৃক্ষ_TYPE (t)))
		      {
			error_at (OMP_CLAUSE_LOCATION (c),
				  "array section does not have mappable type "
				  "in %qs clause",
				  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
			remove = সত্য;
		      }
		    অন্যথা যদি (TYPE_ATOMIC (বৃক্ষ_TYPE (t)))
		      {
			error_at (OMP_CLAUSE_LOCATION (c),
				  "%<_Atomic%> %qE in %qs clause", t,
				  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
			remove = সত্য;
		      }
		    যখন (বৃক্ষ_CODE (t) == ARRAY_REF)
		      t = বৃক্ষ_OPERAND (t, 0);

		    c_omp_address_inspector ai (OMP_CLAUSE_LOCATION (c), t);

		    যদি (!omp_parse_রাশিমালা (addr_tokens, t))
		      {
			sorry_at (OMP_CLAUSE_LOCATION (c),
				  "unsupported map expression %qE",
				  OMP_CLAUSE_DECL (c));
			remove = সত্য;
			বিরতি;
		      }

		    /* This check is to determine if this will be the only map
		       node created for this clause.  Otherwise, we'll check
		       the following FIRSTPRIVATE_POINTER or ATTACH_DETACH
		       node on the next iteration(s) of the loop.   */
		    যদি (addr_tokens.দৈর্ঘ্য () >= 4
			&& addr_tokens[0]->type == STRUCTURE_BASE
			&& addr_tokens[0]->u.structure_base_kind == BASE_DECL
			&& addr_tokens[1]->type == ACCESS_METHOD
			&& addr_tokens[2]->type == COMPONENT_SELECTOR
			&& addr_tokens[3]->type == ACCESS_METHOD
			&& (addr_tokens[3]->u.access_kind == ACCESS_DIRECT
			    || (addr_tokens[3]->u.access_kind
				== ACCESS_INDEXED_ARRAY)))
		      {
			বৃক্ষ rt = addr_tokens[1]->রাশিমালা;

			gcc_assert (DECL_P (rt));

			যদি (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
			    && OMP_CLAUSE_MAP_IMPLICIT (c)
			    && (bitmap_bit_p (&map_শীর্ষ, DECL_UID (rt))
				|| bitmap_bit_p (&map_field_শীর্ষ, DECL_UID (rt))
				|| bitmap_bit_p (&map_firstprivate_শীর্ষ,
						 DECL_UID (rt))))
			  {
			    remove = সত্য;
			    বিরতি;
			  }
			যদি (bitmap_bit_p (&map_field_শীর্ষ, DECL_UID (rt)))
			  বিরতি;
			যদি (bitmap_bit_p (&map_শীর্ষ, DECL_UID (rt)))
			  {
			    যদি (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP)
			      error_at (OMP_CLAUSE_LOCATION (c),
					"%qD appears more than once in motion "
					"clauses", rt);
			    অন্যথা যদি (openacc)
			      error_at (OMP_CLAUSE_LOCATION (c),
					"%qD appears more than once in data "
					"clauses", rt);
			    অন্যথা
			      error_at (OMP_CLAUSE_LOCATION (c),
					"%qD appears more than once in map "
					"clauses", rt);
			    remove = সত্য;
			  }
			অন্যথা
			  {
			    bitmap_set_bit (&map_শীর্ষ, DECL_UID (rt));
			    bitmap_set_bit (&map_field_শীর্ষ, DECL_UID (rt));
			  }
		      }
		  }
		যদি (c_oacc_check_attachments (c))
		  remove = সত্য;
		যদি (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		    && (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_ATTACH
			|| OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_DETACH)
		    && !OMP_CLAUSE_আকার (c))
		  /* In this case, we have a single array element which is a
		     pointer, and we already set OMP_CLAUSE_SIZE in
		     handle_omp_array_sections above.  For attach/detach
		     clauses, reset the OMP_CLAUSE_SIZE (representing a bias)
		     to zero here.  */
		  OMP_CLAUSE_আকার (c) = আকার_zero_গ্রন্থি;
		বিরতি;
	      }
	    অন্যথা যদি (!omp_parse_রাশিমালা (addr_tokens, t))
	      {
		sorry_at (OMP_CLAUSE_LOCATION (c),
			  "unsupported map expression %qE",
			  OMP_CLAUSE_DECL (c));
		remove = সত্য;
		বিরতি;
	      }
	    যদি (t == error_mark_গ্রন্থি)
	      {
		remove = সত্য;
		বিরতি;
	      }

	    বৃক্ষ attr;
	    যদি (DECL_P (t)
		&& OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		&& (attr = lookup_attribute ("omp declare target",
					     DECL_ATTRIBUTES (t)))
		&& মান_member (get_identifier ("local"),
				 বৃক্ষ_মান (attr)))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "device-local variable %qD cannot appear "
			  "in map clause", t);
		remove = সত্য;
		বিরতি;
	      }

	    /* OpenACC attach / detach clauses must be pointers.  */
	    যদি (c_oacc_check_attachments (c))
	      {
		remove = সত্য;
		বিরতি;
	      }
	    যদি (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		&& (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_ATTACH
		    || OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_DETACH)
		&& !OMP_CLAUSE_আকার (c))
	      /* For attach/detach clauses, set OMP_CLAUSE_SIZE (representing a
		 bias) to zero here, so it is not set erroneously to the pointer
		 size later on in gimplify.cc.  */
	      OMP_CLAUSE_আকার (c) = আকার_zero_গ্রন্থি;

	    c_omp_address_inspector ai (OMP_CLAUSE_LOCATION (c), t);

	    যদি (!ai.check_clause (c))
	      {
		remove = সত্য;
		বিরতি;
	      }

	    যদি (!ai.map_supported_p ())
	      {
		sorry_at (OMP_CLAUSE_LOCATION (c),
			  "unsupported map expression %qE",
			  OMP_CLAUSE_DECL (c));
		remove = সত্য;
		বিরতি;
	      }

	    gcc_assert ((addr_tokens[0]->type == ARRAY_BASE
			 || addr_tokens[0]->type == STRUCTURE_BASE)
			&& addr_tokens[1]->type == ACCESS_METHOD);

	    t = addr_tokens[1]->রাশিমালা;

	    যদি (addr_tokens[0]->u.structure_base_kind != BASE_DECL)
	      যাও skip_decl_checks;

	    /* For OpenMP, we can access a struct "t" and "t.d" on the same
	       mapping.  OpenACC allows multiple fields of the same structure
	       to be written.  */
	    যদি (addr_tokens[0]->type == STRUCTURE_BASE
		&& (bitmap_bit_p (&map_field_শীর্ষ, DECL_UID (t))
		    || (!openacc && bitmap_bit_p (&map_শীর্ষ, DECL_UID (t)))))
	      যাও skip_decl_checks;

	    যদি (!VAR_P (t) && বৃক্ষ_CODE (t) != PARM_DECL)
	      {
		যদি (ort != C_ORT_ACC && রাশিমালা_P (t))
		  বিরতি;

		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is not a variable in %qs clause", t,
			  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		remove = সত্য;
	      }
	    অন্যথা যদি (VAR_P (t) && DECL_THREAD_LOCAL_P (t))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD is threadprivate variable in %qs clause", t,
			  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		remove = সত্য;
	      }
	    অন্যথা যদি ((OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP
		      || (OMP_CLAUSE_MAP_KIND (c)
			  != GOMP_MAP_FIRSTPRIVATE_POINTER))
		     && !c_mark_addressable (t))
	      remove = সত্য;
	    অন্যথা যদি (!(OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		       && (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_POINTER
			   || (OMP_CLAUSE_MAP_KIND (c)
			       == GOMP_MAP_FIRSTPRIVATE_POINTER)
			   || (OMP_CLAUSE_MAP_KIND (c)
			       == GOMP_MAP_FORCE_DEVICEPTR)))
		     && t == OMP_CLAUSE_DECL (c)
		     && !omp_mappable_type (বৃক্ষ_TYPE (t)))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD does not have a mappable type in %qs clause", t,
			  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		remove = সত্য;
	      }
	    অন্যথা যদি (বৃক্ষ_TYPE (t) == error_mark_গ্রন্থি)
	      remove = সত্য;
	    অন্যথা যদি (TYPE_ATOMIC (strip_array_types (বৃক্ষ_TYPE (t))))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%<_Atomic%> %qE in %qs clause", t,
			  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		remove = সত্য;
	      }
	    অন্যথা যদি (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		     && OMP_CLAUSE_MAP_IMPLICIT (c)
		     && (bitmap_bit_p (&map_শীর্ষ, DECL_UID (t))
			 || bitmap_bit_p (&map_field_শীর্ষ, DECL_UID (t))
			 || bitmap_bit_p (&map_firstprivate_শীর্ষ,
					  DECL_UID (t))))
	      remove = সত্য;
	    অন্যথা যদি (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		     && (OMP_CLAUSE_MAP_KIND (c)
			 == GOMP_MAP_FIRSTPRIVATE_POINTER))
	      {
		যদি (bitmap_bit_p (&generic_শীর্ষ, DECL_UID (t))
		    || bitmap_bit_p (&firstprivate_শীর্ষ, DECL_UID (t))
		    || bitmap_bit_p (&map_firstprivate_শীর্ষ, DECL_UID (t)))
		  {
		    error_at (OMP_CLAUSE_LOCATION (c),
			      "%qD appears more than once in data clauses", t);
		    remove = সত্য;
		  }
		অন্যথা যদি (bitmap_bit_p (&map_শীর্ষ, DECL_UID (t))
			 && !bitmap_bit_p (&map_field_শীর্ষ, DECL_UID (t))
			 && openacc)
		  {
		    error_at (OMP_CLAUSE_LOCATION (c),
			      "%qD appears more than once in data clauses", t);
		    remove = সত্য;
		  }
		অন্যথা
		  bitmap_set_bit (&map_firstprivate_শীর্ষ, DECL_UID (t));
	      }
	    অন্যথা যদি (bitmap_bit_p (&map_শীর্ষ, DECL_UID (t))
		     && !bitmap_bit_p (&map_field_শীর্ষ, DECL_UID (t))
		     && ort != C_ORT_OMP
		     && ort != C_ORT_OMP_TARGET
		     && ort != C_ORT_OMP_EXIT_তথ্য)
	      {
		যদি (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP)
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in motion clauses", t);
		অন্যথা যদি (openacc)
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in data clauses", t);
		অন্যথা
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in map clauses", t);
		remove = সত্য;
	      }
	    অন্যথা যদি (openacc && bitmap_bit_p (&generic_শীর্ষ, DECL_UID (t)))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears more than once in data clauses", t);
		remove = সত্য;
	      }
	    অন্যথা যদি (bitmap_bit_p (&firstprivate_শীর্ষ, DECL_UID (t))
		     || bitmap_bit_p (&is_on_device_শীর্ষ, DECL_UID (t)))
	      {
		যদি (openacc)
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in data clauses", t);
		অন্যথা
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears both in data and map clauses", t);
		remove = সত্য;
	      }
	    অন্যথা যদি (!omp_access_chain_p (addr_tokens, 1))
	      {
		bitmap_set_bit (&map_শীর্ষ, DECL_UID (t));
		যদি (t != OMP_CLAUSE_DECL (c)
		    && বৃক্ষ_CODE (OMP_CLAUSE_DECL (c)) == COMPONENT_REF)
		  bitmap_set_bit (&map_field_শীর্ষ, DECL_UID (t));
	      }

	  skip_decl_checks:
	    /* If we call omp_expand_map_clause in handle_omp_array_sections,
	       the containing loop (here) iterates through the new nodes
	       created by that expansion.  Avoid expanding those again (just
	       by checking the node type).  */
	    যদি (!remove
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
		বৃক্ষ nc = ai.expand_map_clause (c, OMP_CLAUSE_DECL (c),
						addr_tokens, ort);
		যদি (nc != error_mark_গ্রন্থি)
		  c = nc;
	      }
	  }
	  বিরতি;

	ক্ষেত্র OMP_CLAUSE_ENTER:
	ক্ষেত্র OMP_CLAUSE_LINK:
	ক্ষেত্র OMP_CLAUSE_LOCAL:
	  t = OMP_CLAUSE_DECL (c);
	  ধ্রুবক অক্ষর *cname;
	  cname = omp_clause_code_name[OMP_CLAUSE_CODE (c)];
	  যদি (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ENTER
	      && OMP_CLAUSE_ENTER_TO (c))
	    cname = "to";
	  যদি (বৃক্ষ_CODE (t) == FUNCTION_DECL
	      && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ENTER)
	    ;
	  অন্যথা যদি (!VAR_P (t))
	    {
	      যদি (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ENTER)
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is neither a variable nor a function name in "
			  "clause %qs", t, cname);
	      অন্যথা
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is not a variable in clause %qs", t, cname);
	      remove = সত্য;
	    }
	  অন্যথা যদি (DECL_THREAD_LOCAL_P (t))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD is threadprivate variable in %qs clause", t,
			cname);
	      remove = সত্য;
	    }
	  অন্যথা যদি (!omp_mappable_type (বৃক্ষ_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD does not have a mappable type in %qs clause", t,
			cname);
	      remove = সত্য;
	    }
	  যদি (remove)
	    বিরতি;
	  যদি (bitmap_bit_p (&generic_শীর্ষ, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once on the same "
			"%<declare target%> directive", t);
	      remove = সত্য;
	    }
	  অন্যথা
	    bitmap_set_bit (&generic_শীর্ষ, DECL_UID (t));
	  বিরতি;

	ক্ষেত্র OMP_CLAUSE_UNIFORM:
	  t = OMP_CLAUSE_DECL (c);
	  যদি (বৃক্ষ_CODE (t) != PARM_DECL)
	    {
	      যদি (DECL_P (t))
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD is not an argument in %<uniform%> clause", t);
	      অন্যথা
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is not an argument in %<uniform%> clause", t);
	      remove = সত্য;
	      বিরতি;
	    }
	  /* map_head bitmap is used as uniform_head if declare_simd.  */
	  bitmap_set_bit (&map_শীর্ষ, DECL_UID (t));
	  যাও check_dup_generic;

	ক্ষেত্র OMP_CLAUSE_IS_DEVICE_PTR:
	ক্ষেত্র OMP_CLAUSE_USE_DEVICE_PTR:
	  t = OMP_CLAUSE_DECL (c);
	  যদি (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IS_DEVICE_PTR)
	    bitmap_set_bit (&is_on_device_শীর্ষ, DECL_UID (t));
	  যদি (বৃক্ষ_CODE (বৃক্ষ_TYPE (t)) != POINTER_TYPE)
	    {
	      যদি (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_USE_DEVICE_PTR
		  && !openacc)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qs variable is not a pointer",
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  remove = সত্য;
		}
	      অন্যথা যদি (বৃক্ষ_CODE (বৃক্ষ_TYPE (t)) != ARRAY_TYPE)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qs variable is neither a pointer nor an array",
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  remove = সত্য;
		}
	    }
	  যাও check_dup_generic;

	ক্ষেত্র OMP_CLAUSE_HAS_DEVICE_ADDR:
	  t = OMP_CLAUSE_DECL (c);
	  যদি (বৃক্ষ_CODE (t) == OMP_ARRAY_SECTION)
	    {
	      যদি (handle_omp_array_sections (c, ort))
		remove = সত্য;
	      অন্যথা
		{
		  t = OMP_CLAUSE_DECL (c);
		  যখন (বৃক্ষ_CODE (t) == ARRAY_REF)
		    t = বৃক্ষ_OPERAND (t, 0);
		}
	    }
	  bitmap_set_bit (&is_on_device_শীর্ষ, DECL_UID (t));
	  যদি (VAR_P (t) || বৃক্ষ_CODE (t) == PARM_DECL)
	    c_mark_addressable (t);
	  যাও check_dup_generic_t;

	ক্ষেত্র OMP_CLAUSE_USE_DEVICE_ADDR:
	  t = OMP_CLAUSE_DECL (c);
	  যদি (VAR_P (t) || বৃক্ষ_CODE (t) == PARM_DECL)
	    c_mark_addressable (t);
	  যাও check_dup_generic;

	ক্ষেত্র OMP_CLAUSE_NOWAIT:
	  যদি (copyprivate_seen)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<nowait%> clause must not be used together "
			"with %<copyprivate%> clause");
	      remove = সত্য;
	      বিরতি;
	    }
	  nowait_clause = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  চালু;

	ক্ষেত্র OMP_CLAUSE_ORDER:
	  যদি (ordered_clause)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<order%> clause must not be used together "
			"with %<ordered%> clause");
	      remove = সত্য;
	      বিরতি;
	    }
	  অন্যথা যদি (order_clause)
	    {
	      /* Silently remove duplicates.  */
	      remove = সত্য;
	      বিরতি;
	    }
	  order_clause = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  চালু;

	ক্ষেত্র OMP_CLAUSE_DETACH:
	  t = OMP_CLAUSE_DECL (c);
	  যদি (detach_seen)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"too many %qs clauses on a task construct",
			"detach");
	      remove = সত্য;
	      বিরতি;
	    }
	  detach_seen = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  c_mark_addressable (t);
	  চালু;

	ক্ষেত্র OMP_CLAUSE_IF:
	ক্ষেত্র OMP_CLAUSE_SELF:
	ক্ষেত্র OMP_CLAUSE_অঙ্ক_THREADS:
	ক্ষেত্র OMP_CLAUSE_অঙ্ক_TEAMS:
	ক্ষেত্র OMP_CLAUSE_THREAD_LIMIT:
	ক্ষেত্র OMP_CLAUSE_DEFAULT:
	ক্ষেত্র OMP_CLAUSE_UNTIED:
	ক্ষেত্র OMP_CLAUSE_COLLAPSE:
	ক্ষেত্র OMP_CLAUSE_FINAL:
	ক্ষেত্র OMP_CLAUSE_DEVICE:
	ক্ষেত্র OMP_CLAUSE_DIST_SCHEDULE:
	ক্ষেত্র OMP_CLAUSE_DYN_GROUPPRIVATE:
	ক্ষেত্র OMP_CLAUSE_PARALLEL:
	ক্ষেত্র OMP_CLAUSE_FOR:
	ক্ষেত্র OMP_CLAUSE_SECTIONS:
	ক্ষেত্র OMP_CLAUSE_TASKGROUP:
	ক্ষেত্র OMP_CLAUSE_PROC_BIND:
	ক্ষেত্র OMP_CLAUSE_DEVICE_TYPE:
	ক্ষেত্র OMP_CLAUSE_PRIORITY:
	ক্ষেত্র OMP_CLAUSE_THREADS:
	ক্ষেত্র OMP_CLAUSE_SIMD:
	ক্ষেত্র OMP_CLAUSE_HINT:
	ক্ষেত্র OMP_CLAUSE_FILTER:
	ক্ষেত্র OMP_CLAUSE_DEFAULTMAP:
	ক্ষেত্র OMP_CLAUSE_BIND:
	ক্ষেত্র OMP_CLAUSE_অঙ্ক_GANGS:
	ক্ষেত্র OMP_CLAUSE_অঙ্ক_WORKERS:
	ক্ষেত্র OMP_CLAUSE_VECTOR_দৈর্ঘ্য:
	ক্ষেত্র OMP_CLAUSE_ASYNC:
	ক্ষেত্র OMP_CLAUSE_WAIT:
	ক্ষেত্র OMP_CLAUSE_AUTO:
	ক্ষেত্র OMP_CLAUSE_INDEPENDENT:
	ক্ষেত্র OMP_CLAUSE_SEQ:
	ক্ষেত্র OMP_CLAUSE_GANG:
	ক্ষেত্র OMP_CLAUSE_WORKER:
	ক্ষেত্র OMP_CLAUSE_VECTOR:
	ক্ষেত্র OMP_CLAUSE_TILE:
	ক্ষেত্র OMP_CLAUSE_IF_PRESENT:
	ক্ষেত্র OMP_CLAUSE_FINALIZE:
	ক্ষেত্র OMP_CLAUSE_NOHOST:
	ক্ষেত্র OMP_CLAUSE_INDIRECT:
	ক্ষেত্র OMP_CLAUSE_NOVARIANTS:
	ক্ষেত্র OMP_CLAUSE_NOCONTEXT:
	  pc = &OMP_CLAUSE_CHAIN (c);
	  চালু;

	ক্ষেত্র OMP_CLAUSE_GRAINSIZE:
	  grainsize_seen = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  চালু;

	ক্ষেত্র OMP_CLAUSE_অঙ্ক_TASKS:
	  অঙ্ক_tasks_seen = সত্য;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  চালু;

	ক্ষেত্র OMP_CLAUSE_MERGEABLE:
	  mergeable_seen = সত্য;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  চালু;

	ক্ষেত্র OMP_CLAUSE_NOGROUP:
	  nogroup_seen = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  চালু;

	ক্ষেত্র OMP_CLAUSE_SCHEDULE:
	  schedule_clause = c;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  চালু;

	ক্ষেত্র OMP_CLAUSE_ORDERED:
	  ordered_clause = c;
	  যদি (order_clause)
	    {
	      error_at (OMP_CLAUSE_LOCATION (*order_clause),
			"%<order%> clause must not be used together "
			"with %<ordered%> clause");
	      *order_clause = OMP_CLAUSE_CHAIN (*order_clause);
	      order_clause = ফাঁকা;
	    }
	  pc = &OMP_CLAUSE_CHAIN (c);
	  চালু;

	ক্ষেত্র OMP_CLAUSE_SAFELEN:
	  safelen = c;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  চালু;
	ক্ষেত্র OMP_CLAUSE_SIMDLEN:
	  simdlen = c;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  চালু;

	ক্ষেত্র OMP_CLAUSE_FULL:
	  full_seen = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  চালু;

	ক্ষেত্র OMP_CLAUSE_PARTIAL:
	  partial_seen = সত্য;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  চালু;

	ক্ষেত্র OMP_CLAUSE_SIZES:
	  pc = &OMP_CLAUSE_CHAIN (c);
	  চালু;

	ক্ষেত্র OMP_CLAUSE_INBRANCH:
	ক্ষেত্র OMP_CLAUSE_NOTINBRANCH:
	  যদি (branch_seen)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<inbranch%> clause is incompatible with "
			"%<notinbranch%>");
	      remove = সত্য;
	      বিরতি;
	    }
	  branch_seen = সত্য;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  চালু;

	ক্ষেত্র OMP_CLAUSE_INCLUSIVE:
	ক্ষেত্র OMP_CLAUSE_EXCLUSIVE:
	  need_complete = সত্য;
	  need_implicitly_determined = সত্য;
	  t = OMP_CLAUSE_DECL (c);
	  যদি (!VAR_P (t) && বৃক্ষ_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %qs", t,
			omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	      remove = সত্য;
	    }
	  বিরতি;

	ক্ষেত্র OMP_CLAUSE_INIT:
	  init_seen = সত্য;
	  যদি (!OMP_CLAUSE_INIT_TARGETSYNC (c))
	    init_no_targetsync_clause = c;
	  /* FALLTHRU */
	ক্ষেত্র OMP_CLAUSE_DESTROY:
	ক্ষেত্র OMP_CLAUSE_USE:
	  init_use_destroy_seen = সত্য;
	  t = OMP_CLAUSE_DECL (c);
	  যদি (bitmap_bit_p (&generic_শীর্ষ, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD appears more than once in action clauses", t);
	      remove = সত্য;
	      বিরতি;
	    }
	  bitmap_set_bit (&generic_শীর্ষ, DECL_UID (t));
	  /* FALLTHRU */
	ক্ষেত্র OMP_CLAUSE_INTEROP:
	  যদি (/* ort == C_ORT_OMP_INTEROP [uncomment for depobj init]  */
		   !c_omp_interop_t_p (বৃক্ষ_TYPE (OMP_CLAUSE_DECL (c))))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD must be of %<omp_interop_t%>",
			OMP_CLAUSE_DECL (c));
	      remove = সত্য;
	    }
	  অন্যথা যদি ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_INIT
		    || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DESTROY)
		   && বৃক্ষ_READONLY (OMP_CLAUSE_DECL (c)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD shall not be const", OMP_CLAUSE_DECL (c));
	      remove = সত্য;
	    }
	  pc = &OMP_CLAUSE_CHAIN (c);
	  বিরতি;
	পূর্বনির্ধারিত:
	  gcc_unreachable ();
	}

      যদি (!remove)
	{
	  t = OMP_CLAUSE_DECL (c);

	  যদি (need_complete)
	    {
	      t = require_complete_type (OMP_CLAUSE_LOCATION (c), t);
	      যদি (t == error_mark_গ্রন্থি)
		remove = সত্য;
	    }

	  যদি (need_implicitly_determined)
	    {
	      ধ্রুবক অক্ষর *share_name = ফাঁকা;

	      যদি (VAR_P (t) && DECL_THREAD_LOCAL_P (t))
		share_name = "threadprivate";
	      অন্যথা নির্বাচন (c_omp_predetermined_sharing (t))
		{
		ক্ষেত্র OMP_CLAUSE_DEFAULT_UNSPECIFIED:
		  বিরতি;
		ক্ষেত্র OMP_CLAUSE_DEFAULT_SHARED:
		  যদি ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_SHARED
		       || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_FIRSTPRIVATE)
		      && c_omp_predefined_variable (t))
		    /* The __func__ variable and similar function-local
		       predefined variables may be listed in a shared or
		       firstprivate clause.  */
		    বিরতি;
		  share_name = "shared";
		  বিরতি;
		ক্ষেত্র OMP_CLAUSE_DEFAULT_PRIVATE:
		  share_name = "private";
		  বিরতি;
		পূর্বনির্ধারিত:
		  gcc_unreachable ();
		}
	      যদি (share_name)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qE is predetermined %qs for %qs",
			    t, share_name,
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  remove = সত্য;
		}
	      অন্যথা যদি (বৃক্ষ_READONLY (t)
		       && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_SHARED
		       && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_FIRSTPRIVATE)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<const%> qualified %qE may appear only in "
			    "%<shared%> or %<firstprivate%> clauses", t);
		  remove = সত্য;
		}
	    }
	}

      যদি (remove)
	{
	  যদি (grp_start_p)
	    {
	      /* If we found a clause to remove, we want to remove the whole
		 expanded group, otherwise gimplify
		 (omp_resolve_clause_dependencies) can get confused.  */
	      *grp_start_p = grp_sentinel;
	      pc = grp_start_p;
	      grp_start_p = ফাঁকা;
	    }
	  অন্যথা
	    *pc = OMP_CLAUSE_CHAIN (c);
	}
      অন্যথা
	pc = &OMP_CLAUSE_CHAIN (c);
    }

  যদি (grp_start_p
      && OMP_CLAUSE_HAS_ITERATORS (*grp_start_p))
    জন্য (বৃক্ষ gc = *grp_start_p; gc; gc = OMP_CLAUSE_CHAIN (gc))
      OMP_CLAUSE_ITERATORS (gc) = OMP_CLAUSE_ITERATORS (*grp_start_p);

  যদি (simdlen
      && safelen
      && বৃক্ষ_int_cst_lt (OMP_CLAUSE_SAFELEN_রাশিমালা (safelen),
			  OMP_CLAUSE_SIMDLEN_রাশিমালা (simdlen)))
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
      OMP_CLAUSE_SIMDLEN_রাশিমালা (simdlen)
	= OMP_CLAUSE_SAFELEN_রাশিমালা (safelen);
    }

  যদি (ordered_clause
      && schedule_clause
      && (OMP_CLAUSE_SCHEDULE_KIND (schedule_clause)
	  & OMP_CLAUSE_SCHEDULE_NONMONOTONIC))
    {
      error_at (OMP_CLAUSE_LOCATION (schedule_clause),
		"%<nonmonotonic%> schedule modifier specified together "
		"with %<ordered%> clause");
      OMP_CLAUSE_SCHEDULE_KIND (schedule_clause)
	= (গণনা omp_clause_schedule_kind)
	  (OMP_CLAUSE_SCHEDULE_KIND (schedule_clause)
	   & ~OMP_CLAUSE_SCHEDULE_NONMONOTONIC);
    }

  যদি (reduction_seen < 0 && ordered_clause)
    {
      error_at (OMP_CLAUSE_LOCATION (ordered_clause),
		"%qs clause specified together with %<inscan%> "
		"%<reduction%> clause", "ordered");
      reduction_seen = -2;
    }

  যদি (reduction_seen < 0 && schedule_clause)
    {
      error_at (OMP_CLAUSE_LOCATION (schedule_clause),
		"%qs clause specified together with %<inscan%> "
		"%<reduction%> clause", "schedule");
      reduction_seen = -2;
    }

  যদি (linear_variable_step_check
      || reduction_seen == -2
      || allocate_seen
      || target_in_reduction_seen)
    জন্য (pc = &clauses, c = clauses; c ; c = *pc)
      {
	যৌক্তিক remove = মিথ্যা;
	যদি (allocate_seen)
	  নির্বাচন (OMP_CLAUSE_CODE (c))
	    {
	    ক্ষেত্র OMP_CLAUSE_REDUCTION:
	    ক্ষেত্র OMP_CLAUSE_IN_REDUCTION:
	    ক্ষেত্র OMP_CLAUSE_TASK_REDUCTION:
	      যদি (বৃক্ষ_CODE (OMP_CLAUSE_DECL (c)) == MEM_REF)
		{
		  t = বৃক্ষ_OPERAND (OMP_CLAUSE_DECL (c), 0);
		  যদি (বৃক্ষ_CODE (t) == POINTER_PLUS_রাশিমালা)
		    t = বৃক্ষ_OPERAND (t, 0);
		  যদি (বৃক্ষ_CODE (t) == ADDR_রাশিমালা
		      || INDIRECT_REF_P (t))
		    t = বৃক্ষ_OPERAND (t, 0);
		  যদি (DECL_P (t))
		    bitmap_clear_bit (&aligned_শীর্ষ, DECL_UID (t));
		  বিরতি;
		}
	      /* FALLTHRU */
	    ক্ষেত্র OMP_CLAUSE_PRIVATE:
	    ক্ষেত্র OMP_CLAUSE_FIRSTPRIVATE:
	    ক্ষেত্র OMP_CLAUSE_LASTPRIVATE:
	    ক্ষেত্র OMP_CLAUSE_LINEAR:
	      যদি (DECL_P (OMP_CLAUSE_DECL (c)))
		bitmap_clear_bit (&aligned_শীর্ষ,
				  DECL_UID (OMP_CLAUSE_DECL (c)));
	      বিরতি;
	    পূর্বনির্ধারিত:
	      বিরতি;
	    }
	যদি (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_LINEAR
	    && OMP_CLAUSE_LINEAR_VARIABLE_STRIDE (c)
	    && !bitmap_bit_p (&map_শীর্ষ,
			      DECL_UID (OMP_CLAUSE_LINEAR_STEP (c))))
	  {
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%<linear%> clause step is a parameter %qD not "
		      "specified in %<uniform%> clause",
		      OMP_CLAUSE_LINEAR_STEP (c));
	    remove = সত্য;
	  }
	অন্যথা যদি (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
		 && reduction_seen == -2)
	  OMP_CLAUSE_REDUCTION_INSCAN (c) = 0;
	যদি (target_in_reduction_seen
	    && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP)
	  {
	    বৃক্ষ t = OMP_CLAUSE_DECL (c);
	    যখন (handled_component_p (t)
		   || INDIRECT_REF_P (t)
		   || বৃক্ষ_CODE (t) == ADDR_রাশিমালা
		   || বৃক্ষ_CODE (t) == MEM_REF
		   || বৃক্ষ_CODE (t) == NON_LVALUE_রাশিমালা)
	      t = বৃক্ষ_OPERAND (t, 0);
	    যদি (DECL_P (t)
		&& bitmap_bit_p (&oacc_reduction_শীর্ষ, DECL_UID (t)))
	      OMP_CLAUSE_MAP_IN_REDUCTION (c) = 1;
	  }

	যদি (remove)
	  *pc = OMP_CLAUSE_CHAIN (c);
	অন্যথা
	  pc = &OMP_CLAUSE_CHAIN (c);
      }

  যদি (allocate_seen)
    জন্য (pc = &clauses, c = clauses; c ; c = *pc)
      {
	যৌক্তিক remove = মিথ্যা;
	যদি (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ALLOCATE
	    && !OMP_CLAUSE_ALLOCATE_COMBINED (c)
	    && bitmap_bit_p (&aligned_শীর্ষ, DECL_UID (OMP_CLAUSE_DECL (c))))
	  {
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD specified in %<allocate%> clause but not in "
		      "an explicit privatization clause", OMP_CLAUSE_DECL (c));
	    remove = সত্য;
	  }
	যদি (remove)
	  *pc = OMP_CLAUSE_CHAIN (c);
	অন্যথা
	  pc = &OMP_CLAUSE_CHAIN (c);
      }

  যদি (nogroup_seen && reduction_seen)
    {
      error_at (OMP_CLAUSE_LOCATION (*nogroup_seen),
		"%<nogroup%> clause must not be used together with "
		"%<reduction%> clause");
      *nogroup_seen = OMP_CLAUSE_CHAIN (*nogroup_seen);
    }

  যদি (grainsize_seen && অঙ্ক_tasks_seen)
    {
      error_at (OMP_CLAUSE_LOCATION (*grainsize_seen),
		"%<grainsize%> clause must not be used together with "
		"%<num_tasks%> clause");
      *grainsize_seen = OMP_CLAUSE_CHAIN (*grainsize_seen);
    }

  যদি (full_seen && partial_seen)
    {
      error_at (OMP_CLAUSE_LOCATION (*full_seen),
		"%<full%> clause must not be used together with "
		"%<partial%> clause");
      *full_seen = OMP_CLAUSE_CHAIN (*full_seen);
    }

  যদি (detach_seen)
    {
      যদি (mergeable_seen)
	{
	  error_at (OMP_CLAUSE_LOCATION (*detach_seen),
		    "%<detach%> clause must not be used together with "
		    "%<mergeable%> clause");
	  *detach_seen = OMP_CLAUSE_CHAIN (*detach_seen);
	}
      অন্যথা
	{
	  বৃক্ষ detach_decl = OMP_CLAUSE_DECL (*detach_seen);

	  জন্য (pc = &clauses, c = clauses; c ; c = *pc)
	    {
	      যৌক্তিক remove = মিথ্যা;
	      যদি ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_SHARED
		   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_PRIVATE
		   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_FIRSTPRIVATE
		   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_LASTPRIVATE)
		  && OMP_CLAUSE_DECL (c) == detach_decl)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "the event handle of a %<detach%> clause "
			    "should not be in a data-sharing clause");
		  remove = সত্য;
		}
	      যদি (remove)
		*pc = OMP_CLAUSE_CHAIN (c);
	      অন্যথা
		pc = &OMP_CLAUSE_CHAIN (c);
	    }
	}
    }

  যদি (ort == C_ORT_OMP_INTEROP
      && depend_clause
      && (!init_use_destroy_seen
	  || (init_seen && init_no_targetsync_clause)))
    {
      error_at (OMP_CLAUSE_LOCATION (depend_clause),
		"%<depend%> clause requires action clauses with "
		"%<targetsync%> interop-type");
      যদি (init_no_targetsync_clause)
	inform (OMP_CLAUSE_LOCATION (init_no_targetsync_clause),
		"%<init%> clause lacks the %<targetsync%> modifier");
    }

  bitmap_obstack_release (ফাঁকা);
  ফেরত clauses;
}

/* Do processing necessary to make CLAUSES well-formed, where CLAUSES result
   from implicit instantiation of user-defined mappers (in gimplify.cc).  */

বৃক্ষ
c_omp_finish_mapper_clauses (বৃক্ষ clauses)
{
  ফেরত c_finish_omp_clauses (clauses, C_ORT_OMP);
}

/* Return code to initialize DST with a copy constructor from SRC.
   C doesn't have copy constructors nor assignment operators, only for
   _Atomic vars we need to perform __atomic_load from src into a temporary
   followed by __atomic_store of the temporary to dst.  */

বৃক্ষ
c_omp_clause_copy_ctor (বৃক্ষ clause, বৃক্ষ dst, বৃক্ষ src)
{
  যদি (!really_atomic_lvalue (dst) && !really_atomic_lvalue (src))
    ফেরত build2 (MODIFY_রাশিমালা, বৃক্ষ_TYPE (dst), dst, src);

  location_t loc = OMP_CLAUSE_LOCATION (clause);
  বৃক্ষ type = বৃক্ষ_TYPE (dst);
  বৃক্ষ nonatomic_type = build_qualified_type (type, TYPE_UNQUALIFIED);
  বৃক্ষ tmp = create_tmp_var (nonatomic_type);
  বৃক্ষ tmp_addr = build_fold_addr_রাশিমালা (tmp);
  বৃক্ষ_ADDRESSABLE (tmp) = 1;
  suppress_warning (tmp);
  বৃক্ষ src_addr = build_fold_addr_রাশিমালা (src);
  বৃক্ষ dst_addr = build_fold_addr_রাশিমালা (dst);
  বৃক্ষ seq_cst = build_int_cst (integer_type_গ্রন্থি, MEMMODEL_SEQ_CST);
  vec<বৃক্ষ, va_gc> *params;
  /* Expansion of a generic atomic load may require an addition
     element, so allocate enough to prevent a resize.  */
  vec_alloc (params, 4);

  /* Build __atomic_load (&src, &tmp, SEQ_CST);  */
  বৃক্ষ fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_LOAD);
  params->quick_ঠেলো (src_addr);
  params->quick_ঠেলো (tmp_addr);
  params->quick_ঠেলো (seq_cst);
  বৃক্ষ load = c_build_function_call_vec (loc, vNULL, fndecl, params, ফাঁকা);

  vec_alloc (params, 4);

  /* Build __atomic_store (&dst, &tmp, SEQ_CST);  */
  fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_STORE);
  params->quick_ঠেলো (dst_addr);
  params->quick_ঠেলো (tmp_addr);
  params->quick_ঠেলো (seq_cst);
  বৃক্ষ store = c_build_function_call_vec (loc, vNULL, fndecl, params, ফাঁকা);
  ফেরত build2 (COMPOUND_রাশিমালা, void_type_গ্রন্থি, load, store);
}

/* Create a transaction node.  */

বৃক্ষ
c_finish_transaction (location_t loc, বৃক্ষ block, পূর্ণসংখ্যা flags)
{
  বৃক্ষ stmt = build_stmt (loc, TRANSACTION_রাশিমালা, block);
  যদি (flags & TM_STMT_ATTR_OUTER)
    TRANSACTION_রাশিমালা_OUTER (stmt) = 1;
  যদি (flags & TM_STMT_ATTR_RELAXED)
    TRANSACTION_রাশিমালা_RELAXED (stmt) = 1;
  ফেরত add_stmt (stmt);
}

/* Make a variant type in the proper way for C/C++, propagating qualifiers
   down to the element type of an array.  If ORIG_QUAL_TYPE is not
   NULL, then it should be used as the qualified type
   ORIG_QUAL_INDIRECT levels down in array type derivation (to
   preserve information about the typedef name from which an array
   type was derived).  */

বৃক্ষ
c_build_qualified_type (বৃক্ষ type, পূর্ণসংখ্যা type_quals, বৃক্ষ orig_qual_type,
			আকার_t orig_qual_indirect)
{
  যদি (type == error_mark_গ্রন্থি)
    ফেরত type;

  যদি (বৃক্ষ_CODE (type) == ARRAY_TYPE)
    {
      বৃক্ষ t;
      বৃক্ষ element_type = c_build_qualified_type (বৃক্ষ_TYPE (type),
						  type_quals, orig_qual_type,
						  orig_qual_indirect - 1);

      /* See if we already have an identically qualified type.  */
      যদি (orig_qual_type && orig_qual_indirect == 0)
	t = orig_qual_type;
      অন্যথা
	জন্য (t = TYPE_MAIN_VARIANT (type); t; t = TYPE_পরবর্তী_VARIANT (t))
	  {
	    যদি (TYPE_QUALS (strip_array_types (t)) == type_quals
		&& TYPE_NAME (t) == TYPE_NAME (type)
		&& TYPE_CONTEXT (t) == TYPE_CONTEXT (type)
		&& attribute_list_equal (TYPE_ATTRIBUTES (t),
					 TYPE_ATTRIBUTES (type)))
	      বিরতি;
	  }
      যদি (!t)
	{
          বৃক্ষ domain = TYPE_DOMAIN (type);

	  t = build_variant_type_copy (type);
	  বৃক্ষ_TYPE (t) = element_type;
	  TYPE_ADDR_SPACE (t) = TYPE_ADDR_SPACE (element_type);

          যদি (TYPE_STRUCTURAL_EQUALITY_P (element_type)
              || (domain && TYPE_STRUCTURAL_EQUALITY_P (domain)))
            SET_TYPE_STRUCTURAL_EQUALITY (t);
          অন্যথা যদি (TYPE_CANONICAL (element_type) != element_type
                   || (domain && TYPE_CANONICAL (domain) != domain))
            {
              বৃক্ষ unqualified_canon
		= c_build_array_type (TYPE_CANONICAL (element_type),
				      domain ? TYPE_CANONICAL (domain)
					     : NULL_বৃক্ষ);
              যদি (TYPE_REVERSE_STORAGE_ORDER (type))
                {
                  unqualified_canon
		    = build_distinct_type_copy (unqualified_canon);
                  TYPE_REVERSE_STORAGE_ORDER (unqualified_canon) = 1;
                }
              TYPE_CANONICAL (t)
		= c_build_qualified_type (unqualified_canon, type_quals);
            }
          অন্যথা
            TYPE_CANONICAL (t) = t;
	}
      ফেরত t;
    }

  /* A restrict-qualified pointer type must be a pointer to object or
     incomplete type.  Note that the use of POINTER_TYPE_P also allows
     REFERENCE_TYPEs, which is appropriate for C++.  */
  যদি ((type_quals & TYPE_QUAL_RESTRICT)
      && (!POINTER_TYPE_P (type)
	  || !C_TYPE_OBJECT_OR_INCOMPLETE_P (বৃক্ষ_TYPE (type))))
    {
      error ("invalid use of %<restrict%>");
      type_quals &= ~TYPE_QUAL_RESTRICT;
    }

  বৃক্ষ var_type = (orig_qual_type && orig_qual_indirect == 0
		   ? orig_qual_type
		   : build_qualified_type (type, type_quals));

  gcc_checking_assert (C_TYPE_VARIABLE_আকার (var_type)
		       == C_TYPE_VARIABLE_আকার (type));
  gcc_checking_assert (c_type_variably_modified_p (var_type)
		       == c_type_variably_modified_p (type));

  /* A variant type does not inherit the list of incomplete vars from the
     type main variant.  */
  যদি ((RECORD_OR_UNION_TYPE_P (var_type)
       || বৃক্ষ_CODE (var_type) == ENUMERAL_TYPE)
      && TYPE_MAIN_VARIANT (var_type) != var_type)
    C_TYPE_INCOMPLETE_VARS (var_type) = 0;
  ফেরত var_type;
}

/* Build a VA_ARG_EXPR for the C parser.  */

বৃক্ষ
c_build_va_arg (location_t loc1, বৃক্ষ রাশিমালা, location_t loc2, বৃক্ষ type,
		বৃক্ষ type_রাশিমালা)
{
  যদি (error_operand_p (type))
    ফেরত error_mark_গ্রন্থি;
  /* VA_ARG_EXPR cannot be used for a scalar va_list with reverse storage
     order because it takes the address of the expression.  */
  অন্যথা যদি (handled_component_p (রাশিমালা)
	   && reverse_storage_order_for_component_p (রাশিমালা))
    {
      error_at (loc1, "cannot use %<va_arg%> with reverse storage order");
      ফেরত error_mark_গ্রন্থি;
    }
  অন্যথা যদি (!COMPLETE_TYPE_P (type))
    {
      error_at (loc2, "second argument to %<va_arg%> is of incomplete "
		"type %qT", type);
      ফেরত error_mark_গ্রন্থি;
    }
  অন্যথা যদি (বৃক্ষ_CODE (type) == FUNCTION_TYPE)
    {
      error_at (loc2, "second argument to %<va_arg%> is a function type %qT",
		type);
      ফেরত error_mark_গ্রন্থি;
    }
  অন্যথা যদি (বৃক্ষ_CODE (type) == ARRAY_TYPE && C_TYPE_VARIABLE_আকার (type)
	   && !flag_isoc99)
    {
      error_at (loc2, "second argument to %<va_arg%> is an array type %qT",
		type);
      ফেরত error_mark_গ্রন্থি;
    }
  অন্যথা যদি (warn_cxx_compat && বৃক্ষ_CODE (type) == ENUMERAL_TYPE)
    warning_at (loc2, OPT_Wc___compat,
		"C++ requires promoted type, not enum type, in %<va_arg%>");

  যদি (flag_isoc99 && বৃক্ষ_CODE (type) == ARRAY_TYPE)
    {
      warning_at (loc2, 0, "second argument to %<va_arg%> is an array type %qT",
		  type);
      /* We create a trap but evaluate side effects first.  */
      বৃক্ষ trapfn = builtin_decl_explicit (BUILT_IN_TRAP);
      trapfn = build_call_রাশিমালা_loc (loc2, trapfn, 0);
      বৃক্ষ e2 = build2 (COMPOUND_রাশিমালা, void_type_গ্রন্থি, রাশিমালা, trapfn);
      /* Return a compound literal of the right type.  */
      বৃক্ষ e1 = build_compound_literal (loc2, type, ফাঁকা, সত্য, 0, ফাঁকা);
      রাশিমালা = build2 (COMPOUND_রাশিমালা, type, e2, e1);
    }
  অন্যথা
    রাশিমালা = build_va_arg (loc2, রাশিমালা, type);

  যদি (type_রাশিমালা)
    রাশিমালা = build2 (COMPOUND_রাশিমালা, বৃক্ষ_TYPE (রাশিমালা), type_রাশিমালা, রাশিমালা);

  ফেরত রাশিমালা;
}

/* Return truthvalue of whether T1 is the same tree structure as T2.
   Return 1 if they are the same. Return false if they are different.  */

যৌক্তিক
c_বৃক্ষ_equal (বৃক্ষ t1, বৃক্ষ t2)
{
  গণনা বৃক্ষ_code code1, code2;

  যদি (t1 == t2)
    ফেরত সত্য;
  যদি (!t1 || !t2)
    ফেরত মিথ্যা;

  জন্য (code1 = বৃক্ষ_CODE (t1); code1 == NON_LVALUE_রাশিমালা;
       code1 = বৃক্ষ_CODE (t1))
    t1 = বৃক্ষ_OPERAND (t1, 0);
  জন্য (code2 = বৃক্ষ_CODE (t2); code2 == NON_LVALUE_রাশিমালা;
       code2 = বৃক্ষ_CODE (t2))
    t2 = বৃক্ষ_OPERAND (t2, 0);

  /* They might have become equal now.  */
  যদি (t1 == t2)
    ফেরত সত্য;

  যদি (code1 != code2)
    ফেরত মিথ্যা;

  যদি (CONSTANT_CLASS_P (t1) && !comptypes (বৃক্ষ_TYPE (t1), বৃক্ষ_TYPE (t2)))
    ফেরত মিথ্যা;

  নির্বাচন (code1)
    {
    ক্ষেত্র INTEGER_CST:
      ফেরত wi::to_wide (t1) == wi::to_wide (t2);

    ক্ষেত্র REAL_CST:
      ফেরত real_equal (&বৃক্ষ_REAL_CST (t1), &বৃক্ষ_REAL_CST (t2));

    ক্ষেত্র STRING_CST:
      ফেরত বৃক্ষ_STRING_দৈর্ঘ্য (t1) == বৃক্ষ_STRING_দৈর্ঘ্য (t2)
	&& !memcmp (বৃক্ষ_STRING_POINTER (t1), বৃক্ষ_STRING_POINTER (t2),
		    বৃক্ষ_STRING_দৈর্ঘ্য (t1));

    ক্ষেত্র FIXED_CST:
      ফেরত FIXED_মানসমূহ_IDENTICAL (বৃক্ষ_FIXED_CST (t1),
				     বৃক্ষ_FIXED_CST (t2));

    ক্ষেত্র COMPLEX_CST:
      ফেরত c_বৃক্ষ_equal (বৃক্ষ_REALPART (t1), বৃক্ষ_REALPART (t2))
	     && c_বৃক্ষ_equal (বৃক্ষ_IMAGPART (t1), বৃক্ষ_IMAGPART (t2));

    ক্ষেত্র VECTOR_CST:
      ফেরত operand_equal_p (t1, t2, OEP_ONLY_CONST);

    ক্ষেত্র CONSTRUCTOR:
      /* We need to do this when determining whether or not two
	 non-type pointer to member function template arguments
	 are the same.  */
      যদি (!comptypes (বৃক্ষ_TYPE (t1), বৃক্ষ_TYPE (t2))
	  || CONSTRUCTOR_NELTS (t1) != CONSTRUCTOR_NELTS (t2))
	ফেরত মিথ্যা;
      {
	বৃক্ষ field, মান;
	unsigned পূর্ণসংখ্যা i;
	FOR_EACH_CONSTRUCTOR_ELT (CONSTRUCTOR_ELTS (t1), i, field, মান)
	  {
	    constructor_elt *elt2 = CONSTRUCTOR_ELT (t2, i);
	    যদি (!c_বৃক্ষ_equal (field, elt2->সূচক)
		|| !c_বৃক্ষ_equal (মান, elt2->মান))
	      ফেরত মিথ্যা;
	  }
      }
      ফেরত সত্য;

    ক্ষেত্র বৃক্ষ_LIST:
      যদি (!c_বৃক্ষ_equal (বৃক্ষ_PURPOSE (t1), বৃক্ষ_PURPOSE (t2)))
	ফেরত মিথ্যা;
      যদি (!c_বৃক্ষ_equal (বৃক্ষ_মান (t1), বৃক্ষ_মান (t2)))
	ফেরত মিথ্যা;
      ফেরত c_বৃক্ষ_equal (বৃক্ষ_CHAIN (t1), বৃক্ষ_CHAIN (t2));

    ক্ষেত্র SAVE_রাশিমালা:
      ফেরত c_বৃক্ষ_equal (বৃক্ষ_OPERAND (t1, 0), বৃক্ষ_OPERAND (t2, 0));

    ক্ষেত্র CALL_রাশিমালা:
      {
	বৃক্ষ arg1, arg2;
	call_রাশিমালা_arg_iterator iter1, iter2;
	যদি (!c_বৃক্ষ_equal (CALL_রাশিমালা_FN (t1), CALL_রাশিমালা_FN (t2)))
	  ফেরত মিথ্যা;
	জন্য (arg1 = first_call_রাশিমালা_arg (t1, &iter1),
	       arg2 = first_call_রাশিমালা_arg (t2, &iter2);
	     arg1 && arg2;
	     arg1 = পরবর্তী_call_রাশিমালা_arg (&iter1),
	       arg2 = পরবর্তী_call_রাশিমালা_arg (&iter2))
	  যদি (!c_বৃক্ষ_equal (arg1, arg2))
	    ফেরত মিথ্যা;
	যদি (arg1 || arg2)
	  ফেরত মিথ্যা;
	ফেরত সত্য;
      }

    ক্ষেত্র TARGET_রাশিমালা:
      {
	বৃক্ষ o1 = বৃক্ষ_OPERAND (t1, 0);
	বৃক্ষ o2 = বৃক্ষ_OPERAND (t2, 0);

	/* Special case: if either target is an unallocated VAR_DECL,
	   it means that it's going to be unified with whatever the
	   TARGET_EXPR is really supposed to initialize, so treat it
	   as being equivalent to anything.  */
	যদি (VAR_P (o1) && DECL_NAME (o1) == NULL_বৃক্ষ
	    && !DECL_RTL_SET_P (o1))
	  /*Nop*/;
	অন্যথা যদি (VAR_P (o2) && DECL_NAME (o2) == NULL_বৃক্ষ
		 && !DECL_RTL_SET_P (o2))
	  /*Nop*/;
	অন্যথা যদি (!c_বৃক্ষ_equal (o1, o2))
	  ফেরত মিথ্যা;

	ফেরত c_বৃক্ষ_equal (বৃক্ষ_OPERAND (t1, 1), বৃক্ষ_OPERAND (t2, 1));
      }

    ক্ষেত্র COMPONENT_REF:
      যদি (বৃক্ষ_OPERAND (t1, 1) != বৃক্ষ_OPERAND (t2, 1))
	ফেরত মিথ্যা;
      ফেরত c_বৃক্ষ_equal (বৃক্ষ_OPERAND (t1, 0), বৃক্ষ_OPERAND (t2, 0));

    ক্ষেত্র PARM_DECL:
    ক্ষেত্র VAR_DECL:
    ক্ষেত্র CONST_DECL:
    ক্ষেত্র FIELD_DECL:
    ক্ষেত্র FUNCTION_DECL:
    ক্ষেত্র IDENTIFIER_গ্রন্থি:
    ক্ষেত্র SSA_NAME:
      ফেরত মিথ্যা;

    ক্ষেত্র বৃক্ষ_VEC:
      {
	unsigned ix;
	যদি (বৃক্ষ_VEC_দৈর্ঘ্য (t1) != বৃক্ষ_VEC_দৈর্ঘ্য (t2))
	  ফেরত মিথ্যা;
	জন্য (ix = বৃক্ষ_VEC_দৈর্ঘ্য (t1); ix--;)
	  যদি (!c_বৃক্ষ_equal (বৃক্ষ_VEC_ELT (t1, ix),
			     বৃক্ষ_VEC_ELT (t2, ix)))
	    ফেরত মিথ্যা;
	ফেরত সত্য;
      }

    CASE_CONVERT:
      যদি (!comptypes (বৃক্ষ_TYPE (t1), বৃক্ষ_TYPE (t2)))
	ফেরত মিথ্যা;
      বিরতি;

    পূর্বনির্ধারিত:
      বিরতি;
    }

  নির্বাচন (বৃক্ষ_CODE_CLASS (code1))
    {
    ক্ষেত্র tcc_unary:
    ক্ষেত্র tcc_দ্বিমিক:
    ক্ষেত্র tcc_comparison:
    ক্ষেত্র tcc_expression:
    ক্ষেত্র tcc_vl_exp:
    ক্ষেত্র tcc_reference:
    ক্ষেত্র tcc_statement:
      {
	পূর্ণসংখ্যা i, n = বৃক্ষ_OPERAND_দৈর্ঘ্য (t1);

	নির্বাচন (code1)
	  {
	  ক্ষেত্র PREINCREMENT_রাশিমালা:
	  ক্ষেত্র PREDECREMENT_রাশিমালা:
	  ক্ষেত্র POSTINCREMENT_রাশিমালা:
	  ক্ষেত্র POSTDECREMENT_রাশিমালা:
	    n = 1;
	    বিরতি;
	  ক্ষেত্র ARRAY_REF:
	    n = 2;
	    বিরতি;
	  পূর্বনির্ধারিত:
	    বিরতি;
	  }

	যদি (বৃক্ষ_CODE_CLASS (code1) == tcc_vl_exp
	    && n != বৃক্ষ_OPERAND_দৈর্ঘ্য (t2))
	  ফেরত মিথ্যা;

	জন্য (i = 0; i < n; ++i)
	  যদি (!c_বৃক্ষ_equal (বৃক্ষ_OPERAND (t1, i), বৃক্ষ_OPERAND (t2, i)))
	    ফেরত মিথ্যা;

	ফেরত সত্য;
      }

    ক্ষেত্র tcc_type:
      ফেরত comptypes (t1, t2);
    পূর্বনির্ধারিত:
      gcc_unreachable ();
    }
}

/* Returns true when the function declaration FNDECL is implicit,
   introduced as a result of a call to an otherwise undeclared
   function, and false otherwise.  */

যৌক্তিক
c_decl_implicit (const_বৃক্ষ fndecl)
{
  ফেরত C_DECL_IMPLICIT (fndecl);
}
