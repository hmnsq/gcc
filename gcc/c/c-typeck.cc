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

#ಅನ್ತರ್ಭಾವ "config.h"
#ಅನ್ತರ್ಭಾವ "system.h"
#ಅನ್ತರ್ಭಾವ "coretypes.h"
#ಅನ್ತರ್ಭಾವ "memmodel.h"
#ಅನ್ತರ್ಭಾವ "target.h"
#ಅನ್ತರ್ಭಾವ "function.h"
#ಅನ್ತರ್ಭಾವ "bitmap.h"
#ಅನ್ತರ್ಭಾವ "c-tree.h"
#ಅನ್ತರ್ಭಾವ "gimple-expr.h"
#ಅನ್ತರ್ಭಾವ "predict.h"
#ಅನ್ತರ್ಭಾವ "stor-layout.h"
#ಅನ್ತರ್ಭಾವ "trans-mem.h"
#ಅನ್ತರ್ಭಾವ "varasm.h"
#ಅನ್ತರ್ಭಾವ "stmt.h"
#ಅನ್ತರ್ಭಾವ "langhooks.h"
#ಅನ್ತರ್ಭಾವ "c-lang.h"
#ಅನ್ತರ್ಭಾವ "intl.h"
#ಅನ್ತರ್ಭಾವ "tree-iterator.h"
#ಅನ್ತರ್ಭಾವ "gimplify.h"
#ಅನ್ತರ್ಭಾವ "tree-inline.h"
#ಅನ್ತರ್ಭಾವ "omp-general.h"
#ಅನ್ತರ್ಭಾವ "c-family/c-objc.h"
#ಅನ್ತರ್ಭಾವ "c-family/c-ubsan.h"
#ಅನ್ತರ್ಭಾವ "gomp-constants.h"
#ಅನ್ತರ್ಭಾವ "spellcheck-tree.h"
#ಅನ್ತರ್ಭಾವ "c-family/c-type-mismatch.h"
#ಅನ್ತರ್ಭಾವ "stringpool.h"
#ಅನ್ತರ್ಭಾವ "attribs.h"
#ಅನ್ತರ್ಭಾವ "asan.h"
#ಅನ್ತರ್ಭಾವ "realmpfr.h"
#ಅನ್ತರ್ಭಾವ "tree-pretty-print-markup.h"
#ಅನ್ತರ್ಭಾವ "gcc-urlifier.h"

/* Possible cases of implicit conversions.  Used to select diagnostic messages
   and control folding initializers in convert_for_assignment.  */
ಗಣನಾ impl_conv {
  ic_argpass,
  ic_assign,
  ic_init,
  ic_init_const,
  ic_return
};

/* The level of nesting inside "__alignof__".  */
ಪೂರ್ಣಾಙ್ಕ in_alignof;

/* The level of nesting inside "sizeof".  */
ಪೂರ್ಣಾಙ್ಕ in_sizeof;

/* The level of nesting inside "countof".  */
ಪೂರ್ಣಾಙ್ಕ in_countof;

/* The level of nesting inside "typeof".  */
ಪೂರ್ಣಾಙ್ಕ in_typeof;

/* The level of nesting inside "_Generic".  */
ಪೂರ್ಣಾಙ್ಕ in_generic;

/* True when parsing OpenMP loop expressions.  */
ತಾರ್ಕಿಕ c_in_omp_for;

/* True when parsing OpenMP map clause.  */
ತಾರ್ಕಿಕ c_omp_array_section_p;

/* The argument of last parsed sizeof expression, only to be tested
   if expr.original_code == SIZEOF_EXPR.  */
ವೃಕ್ಷ c_last_sizeof_arg;
location_t c_last_sizeof_loc;

/* Nonzero if we might need to print a "missing braces around
   initializer" message within this initializer.  */
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ found_missing_braces;

ಸ್ಥಿರ ತಾರ್ಕಿಕ require_constant_ಮೌಲ್ಯ;
ಸ್ಥಿರ ತಾರ್ಕಿಕ require_constant_elements;
ಸ್ಥಿರ ತಾರ್ಕಿಕ require_constexpr_ಮೌಲ್ಯ;

ಸ್ಥಿರ ವೃಕ್ಷ qualify_type (ವೃಕ್ಷ, ವೃಕ್ಷ);
ಸಂರಚನಾ comptypes_data;
ಸ್ಥಿರ ತಾರ್ಕಿಕ tagged_types_tu_compatible_p (const_ವೃಕ್ಷ, const_ವೃಕ್ಷ,
					  ಸಂರಚನಾ comptypes_data *);
ಸ್ಥಿರ ತಾರ್ಕಿಕ comp_target_types (location_t, ವೃಕ್ಷ, ವೃಕ್ಷ);
ಸ್ಥಿರ ತಾರ್ಕಿಕ function_types_compatible_p (const_ವೃಕ್ಷ, const_ವೃಕ್ಷ,
					 ಸಂರಚನಾ comptypes_data *);
ಸ್ಥಿರ ತಾರ್ಕಿಕ type_lists_compatible_p (const_ವೃಕ್ಷ, const_ವೃಕ್ಷ,
				     ಸಂರಚನಾ comptypes_data *);
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ convert_arguments (location_t, vec<location_t>, ವೃಕ್ಷ,
			      vec<ವೃಕ್ಷ, va_gc> *, vec<ವೃಕ್ಷ, va_gc> *, ವೃಕ್ಷ,
			      ವೃಕ್ಷ);
ಸ್ಥಿರ ವೃಕ್ಷ pointer_diff (location_t, ವೃಕ್ಷ, ವೃಕ್ಷ, ವೃಕ್ಷ *);
ಸ್ಥಿರ ವೃಕ್ಷ convert_for_assignment (location_t, location_t, ವೃಕ್ಷ, ವೃಕ್ಷ, ವೃಕ್ಷ,
				    ಗಣನಾ impl_conv, ತಾರ್ಕಿಕ, ವೃಕ್ಷ, ವೃಕ್ಷ, ಪೂರ್ಣಾಙ್ಕ,
				    ಪೂರ್ಣಾಙ್ಕ = 0);
ಸ್ಥಿರ ವೃಕ್ಷ valid_compound_ಅಭಿವ್ಯಕ್ತಿ_initializer (ವೃಕ್ಷ, ವೃಕ್ಷ);
ಸ್ಥಿರ ಶೂನ್ಯ ತಳ್ಳು_string (ಧ್ರುವ ವರ್ಣ *);
ಸ್ಥಿರ ಶೂನ್ಯ ತಳ್ಳು_member_name (ವೃಕ್ಷ);
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ spelling_length (ಶೂನ್ಯ);
ಸ್ಥಿರ ವರ್ಣ *print_spelling (ವರ್ಣ *);
ಸ್ಥಿರ ಶೂನ್ಯ warning_init (location_t, ಪೂರ್ಣಾಙ್ಕ, ಧ್ರುವ ವರ್ಣ *);
ಸ್ಥಿರ ವೃಕ್ಷ digest_init (location_t, ವೃಕ್ಷ, ವೃಕ್ಷ, ವೃಕ್ಷ, ವೃಕ್ಷ, ತಾರ್ಕಿಕ, ತಾರ್ಕಿಕ, ತಾರ್ಕಿಕ,
			 ತಾರ್ಕಿಕ, ತಾರ್ಕಿಕ, ತಾರ್ಕಿಕ);
ಸ್ಥಿರ ಶೂನ್ಯ output_init_element (location_t, ವೃಕ್ಷ, ವೃಕ್ಷ, ತಾರ್ಕಿಕ, ವೃಕ್ಷ, ವೃಕ್ಷ, ತಾರ್ಕಿಕ,
				 ತಾರ್ಕಿಕ, ಸಂರಚನಾ obstack *);
ಸ್ಥಿರ ಶೂನ್ಯ output_pending_init_elements (ಪೂರ್ಣಾಙ್ಕ, ಸಂರಚನಾ obstack *);
ಸ್ಥಿರ ತಾರ್ಕಿಕ set_designator (location_t, ತಾರ್ಕಿಕ, ಸಂರಚನಾ obstack *);
ಸ್ಥಿರ ಶೂನ್ಯ ತಳ್ಳು_range_ರಾಶಿ (ವೃಕ್ಷ, ಸಂರಚನಾ obstack *);
ಸ್ಥಿರ ಶೂನ್ಯ add_pending_init (location_t, ವೃಕ್ಷ, ವೃಕ್ಷ, ವೃಕ್ಷ, ತಾರ್ಕಿಕ,
			      ಸಂರಚನಾ obstack *);
ಸ್ಥಿರ ಶೂನ್ಯ set_nonincremental_init (ಸಂರಚನಾ obstack *);
ಸ್ಥಿರ ಶೂನ್ಯ set_nonincremental_init_from_string (ವೃಕ್ಷ, ಸಂರಚನಾ obstack *);
ಸ್ಥಿರ ವೃಕ್ಷ find_init_member (ವೃಕ್ಷ, ಸಂರಚನಾ obstack *);
ಸ್ಥಿರ ಶೂನ್ಯ readonly_warning (ವೃಕ್ಷ, ಗಣನಾ lvalue_use);
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ lvalue_or_else (location_t, const_ವೃಕ್ಷ, ಗಣನಾ lvalue_use);
ಸ್ಥಿರ ಶೂನ್ಯ record_maybe_used_decl (ವೃಕ್ಷ, ತಾರ್ಕಿಕ address);
ಸ್ಥಿರ ತಾರ್ಕಿಕ comptypes_internal (const_ವೃಕ್ಷ, const_ವೃಕ್ಷ,
				ಸಂರಚನಾ comptypes_data *data);
ಸ್ಥಿರ ತಾರ್ಕಿಕ comptypes_check_for_composite (ವೃಕ್ಷ t1, ವೃಕ್ಷ t2);
ಸ್ಥಿರ ತಾರ್ಕಿಕ handle_counted_by_p (ವೃಕ್ಷ);
ಸ್ಥಿರ ತಾರ್ಕಿಕ ತುದಿ_array_vla_p (const_ವೃಕ್ಷ type);


/* Return true if EXP is a null pointer constant, false otherwise.  */

ತಾರ್ಕಿಕ
null_pointer_constant_p (const_ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ)
{
  /* This should really operate on c_expr structures, but they aren't
     yet available everywhere required.  */
  ವೃಕ್ಷ type = ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ);

  /* An integer constant expression with the value 0, such an expression
     cast to type void*, or the predefined constant nullptr, are a null
     pointer constant.  */
  ಯದಿ (ಅಭಿವ್ಯಕ್ತಿ == nullptr_ಗಂಟು)
    ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;

  ಪ್ರತ್ಯಾಗಮ (ವೃಕ್ಷ_CODE (ಅಭಿವ್ಯಕ್ತಿ) == INTEGER_CST
	  && !ವೃಕ್ಷ_OVERFLOW (ಅಭಿವ್ಯಕ್ತಿ)
	  && integer_zerop (ಅಭಿವ್ಯಕ್ತಿ)
	  && (INTEGRAL_TYPE_P (type)
	      || (ವೃಕ್ಷ_CODE (type) == POINTER_TYPE
		  && VOID_TYPE_P (ವೃಕ್ಷ_TYPE (type))
		  && TYPE_QUALS (ವೃಕ್ಷ_TYPE (type)) == TYPE_UNQUALIFIED)));
}

/* EXPR may appear in an unevaluated part of an integer constant
   expression, but not in an evaluated part.  Wrap it in a
   C_MAYBE_CONST_EXPR, or mark it with TREE_OVERFLOW if it is just an
   INTEGER_CST and we cannot create a C_MAYBE_CONST_EXPR.  */

ಸ್ಥಿರ ವೃಕ್ಷ
note_integer_operands (ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ)
{
  ವೃಕ್ಷ ret;
  ಯದಿ (ವೃಕ್ಷ_CODE (ಅಭಿವ್ಯಕ್ತಿ) == INTEGER_CST && in_late_ದ್ವಿಮಾನ_op)
    {
      ret = copy_ಗಂಟು (ಅಭಿವ್ಯಕ್ತಿ);
      ವೃಕ್ಷ_OVERFLOW (ret) = 1;
    }
  ಅನ್ಯಥಾ
    {
      ret = build2 (C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ), NULL_ವೃಕ್ಷ, ಅಭಿವ್ಯಕ್ತಿ);
      C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_INT_OPERANDS (ret) = 1;
    }
  ಪ್ರತ್ಯಾಗಮ ret;
}

/* Having checked whether EXPR may appear in an unevaluated part of an
   integer constant expression and found that it may, remove any
   C_MAYBE_CONST_EXPR noting this fact and return the resulting
   expression.  */

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ವೃಕ್ಷ
remove_c_maybe_const_ಅಭಿವ್ಯಕ್ತಿ (ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ)
{
  ಯದಿ (ವೃಕ್ಷ_CODE (ಅಭಿವ್ಯಕ್ತಿ) == C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ)
    ಪ್ರತ್ಯಾಗಮ C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_ಅಭಿವ್ಯಕ್ತಿ (ಅಭಿವ್ಯಕ್ತಿ);
  ಅನ್ಯಥಾ
    ಪ್ರತ್ಯಾಗಮ ಅಭಿವ್ಯಕ್ತಿ;
}

/* This is a cache to hold if two types are seen.  */

ಸಂರಚನಾ tagged_tu_seen_cache {
  ಧ್ರುವ ಸಂರಚನಾ tagged_tu_seen_cache * next;
  const_ವೃಕ್ಷ t1;
  const_ವೃಕ್ಷ t2;
};

/* Do `exp = require_complete_type (loc, exp);' to make sure exp
   does not have an incomplete type.  (That includes void types.)
   LOC is the location of the use.  */

ವೃಕ್ಷ
require_complete_type (location_t loc, ವೃಕ್ಷ ಮೌಲ್ಯ)
{
  ವೃಕ್ಷ type = ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ);

  ಯದಿ (error_operand_p (ಮೌಲ್ಯ))
    ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;

  /* First, detect a valid value with a complete type.  */
  ಯದಿ (COMPLETE_TYPE_P (type))
    ಪ್ರತ್ಯಾಗಮ ಮೌಲ್ಯ;

  c_incomplete_type_error (loc, ಮೌಲ್ಯ, type);
  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
}

/* Print an error message for invalid use of an incomplete type.
   VALUE is the expression that was used (or 0 if that isn't known)
   and TYPE is the type that was invalid.  LOC is the location for
   the error.  */

ಶೂನ್ಯ
c_incomplete_type_error (location_t loc, const_ವೃಕ್ಷ ಮೌಲ್ಯ, const_ವೃಕ್ಷ type)
{
  /* Avoid duplicate error message.  */
  ಯದಿ (ವೃಕ್ಷ_CODE (type) == ERROR_MARK)
    ಪ್ರತ್ಯಾಗಮ;

  ಯದಿ (ಮೌಲ್ಯ != NULL_ವೃಕ್ಷ && (VAR_P (ಮೌಲ್ಯ) || ವೃಕ್ಷ_CODE (ಮೌಲ್ಯ) == PARM_DECL))
    error_at (loc, "%qD has an incomplete type %qT", ಮೌಲ್ಯ, type);
  ಅನ್ಯಥಾ
    {
    retry:
      /* We must print an error message.  Be clever about what it says.  */

      ವಿಕಲ್ಪ (ವೃಕ್ಷ_CODE (type))
	{
	ಪಕ್ಷ RECORD_TYPE:
	ಪಕ್ಷ UNION_TYPE:
	ಪಕ್ಷ ENUMERAL_TYPE:
	  ಭಙ್ಗ;

	ಪಕ್ಷ VOID_TYPE:
	  error_at (loc, "invalid use of void expression");
	  ಪ್ರತ್ಯಾಗಮ;

	ಪಕ್ಷ ARRAY_TYPE:
	  ಯದಿ (TYPE_DOMAIN (type))
	    {
	      ಯದಿ (flexible_array_member_type_p (type))
		{
		  error_at (loc, "invalid use of flexible array member");
		  ಪ್ರತ್ಯಾಗಮ;
		}
	      type = ವೃಕ್ಷ_TYPE (type);
	      ಗಚ್ಛ retry;
	    }
	  error_at (loc, "invalid use of array with unspecified bounds");
	  ಪ್ರತ್ಯಾಗಮ;

	ಸ್ವಭಾವ:
	  gcc_unreachable ();
	}

      ಯದಿ (ವೃಕ್ಷ_CODE (TYPE_NAME (type)) == IDENTIFIER_ಗಂಟು)
	error_at (loc, "invalid use of undefined type %qT", type);
      ಅನ್ಯಥಾ
	/* If this type has a typedef-name, the TYPE_NAME is a TYPE_DECL.  */
	error_at (loc, "invalid use of incomplete typedef %qT", type);
    }
}

/* Given a type, apply default promotions wrt unnamed function
   arguments and return the new type.  */

ವೃಕ್ಷ
c_type_promotes_to (ವೃಕ್ಷ type)
{
  ವೃಕ್ಷ ret = NULL_ವೃಕ್ಷ;

  ಯದಿ (TYPE_MAIN_VARIANT (type) == float_type_ಗಂಟು)
    ret = double_type_ಗಂಟು;
  ಅನ್ಯಥಾ ಯದಿ (c_promoting_integer_type_p (type))
    {
      /* Preserve unsignedness if not really getting any wider.  */
      ಯದಿ (TYPE_UNSIGNED (type)
	  && (TYPE_PRECISION (type) == TYPE_PRECISION (integer_type_ಗಂಟು)))
	ret = unsigned_type_ಗಂಟು;
      ಅನ್ಯಥಾ
	ret = integer_type_ಗಂಟು;
    }

  ಯದಿ (ret != NULL_ವೃಕ್ಷ)
    ಪ್ರತ್ಯಾಗಮ (TYPE_ATOMIC (type)
	    ? c_build_qualified_type (ret, TYPE_QUAL_ATOMIC)
	    : ret);

  ಪ್ರತ್ಯಾಗಮ type;
}

/* Return true if between two named address spaces, whether there is a superset
   named address space that encompasses both address spaces.  If there is a
   superset, return which address space is the superset.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
addr_space_superset (addr_space_t as1, addr_space_t as2, addr_space_t *common)
{
  ಯದಿ (as1 == as2)
    {
      *common = as1;
      ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
    }
  ಅನ್ಯಥಾ ಯದಿ (targetm.addr_space.subset_p (as1, as2))
    {
      *common = as2;
      ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
    }
  ಅನ್ಯಥಾ ಯದಿ (targetm.addr_space.subset_p (as2, as1))
    {
      *common = as1;
      ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
    }
  ಅನ್ಯಥಾ
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
}

/* Return a variant of TYPE which has all the type qualifiers of LIKE
   as well as those of TYPE.  */

ಸ್ಥಿರ ವೃಕ್ಷ
qualify_type (ವೃಕ್ಷ type, ವೃಕ್ಷ like)
{
  addr_space_t as_type = TYPE_ADDR_SPACE (type);
  addr_space_t as_like = TYPE_ADDR_SPACE (like);
  addr_space_t as_common;

  /* If the two named address spaces are different, determine the common
     superset address space.  If there isn't one, raise an error.  */
  ಯದಿ (!addr_space_superset (as_type, as_like, &as_common))
    {
      as_common = as_type;
      error ("%qT and %qT are in disjoint named address spaces",
	     type, like);
    }

  ಪ್ರತ್ಯಾಗಮ c_build_qualified_type (type,
				 TYPE_QUALS_NO_ADDR_SPACE (type)
				 | TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (like)
				 | ENCODE_QUAL_ADDR_SPACE (as_common));
}


/* Check consistency of type TYPE.  For derived types, we test that
   C_TYPE_VARIABLE_SIZE and C_TYPE_VARIABLY_MODIFIED are consistent with
   the requirements of the base type.  We also check that arrays with a
   non-constant length are marked with C_TYPE_VARIABLE_SIZE. If any
   inconsistency is detected false is returned and true otherwise.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
c_verify_type (ವೃಕ್ಷ type)
{
  ವಿಕಲ್ಪ (ವೃಕ್ಷ_CODE (type))
    {
    ಪಕ್ಷ POINTER_TYPE:
    ಪಕ್ಷ FUNCTION_TYPE:
    ಪಕ್ಷ ARRAY_TYPE:
      /* Pointer, array, functions are variably modified if and only if the
	 target, element, return type is variably modified.  */
      ಯದಿ (!TYPE_STRUCTURAL_EQUALITY_P (type)
	  && (C_TYPE_VARIABLY_MODIFIED (type)
	      != C_TYPE_VARIABLY_MODIFIED (ವೃಕ್ಷ_TYPE (type))))
	ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
      /* If the target type is structural equality, the type should also. */
      ಯದಿ (!TYPE_STRUCTURAL_EQUALITY_P (type)
	  && TYPE_STRUCTURAL_EQUALITY_P (ವೃಕ್ಷ_TYPE (type)))
	ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
    ಸ್ವಭಾವ:
       ಭಙ್ಗ;
    }

  ವಿಕಲ್ಪ (ವೃಕ್ಷ_CODE (type))
    {
    ಪಕ್ಷ POINTER_TYPE:
    ಪಕ್ಷ FUNCTION_TYPE:
      /* Pointer and functions can not have variable size.  */
      ಯದಿ (C_TYPE_VARIABLE_SIZE (type))
	ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
      ಭಙ್ಗ;
    ಪಕ್ಷ ARRAY_TYPE:
      /* An array has variable size if and only if it has a non-constant
	 dimensions or its element type has variable size.  */
      ಯದಿ ((C_TYPE_VARIABLE_SIZE (ವೃಕ್ಷ_TYPE (type))
	   || ತುದಿ_array_vla_p (type))
	  != C_TYPE_VARIABLE_SIZE (type))
	ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
      /* If the element type or the array has variable size, then the
	 array has variable size and is variably modified.  */
      ಯದಿ (C_TYPE_VARIABLE_SIZE (ವೃಕ್ಷ_TYPE (type))
	  || C_TYPE_VARIABLE_SIZE (type))
	{
	  ಯದಿ (!C_TYPE_VARIABLE_SIZE (type))
	    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	  ಯದಿ (!C_TYPE_VARIABLY_MODIFIED (type))
	    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	}

      /* va_list violates this, accept such types here.  */
      ಯದಿ (!COMPLETE_TYPE_P (ವೃಕ್ಷ_TYPE (type)))
	ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;

      ಯದಿ (COMPLETE_TYPE_P (type))
	{
	  /* If the size is unknown, it can not be complete.  */
	  ಯದಿ (NULL_ವೃಕ್ಷ == TYPE_DOMAIN (type))
	    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

	  /* Zero-length arrays must have size zero.  */
	  ಯದಿ (zero_length_array_type_p (type)
	      && !integer_zerop (TYPE_SIZE (type)))
	    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	}
      ಅನ್ಯಥಾ
	{
	  /* If not complete but has a domain, it must be a FAM.  */
	  ಯದಿ (NULL_ವೃಕ್ಷ != TYPE_DOMAIN (type)
	      && !flexible_array_member_type_p (type))
	    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	}
    ಸ್ವಭಾವ:
      ಭಙ್ಗ;
    }
  ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
}

/* Propagate C_TYPE_VARIABLY_MODIFIED and C_TYPE_VARIABLE_SIZE
   from a base type to a newly built derived or qualified type.  */

ಸ್ಥಿರ ವೃಕ್ಷ
c_set_type_bits (ವೃಕ್ಷ new_type, ವೃಕ್ಷ old_type)
{
  gcc_checking_assert (c_verify_type (old_type));

  ಯದಿ (c_type_variably_modified_p (old_type))
    C_TYPE_VARIABLY_MODIFIED (new_type) = ಸತ್ಯ;

  ಯದಿ (ವೃಕ್ಷ_CODE (new_type) == ARRAY_TYPE && C_TYPE_VARIABLE_SIZE (old_type))
    {
      C_TYPE_VARIABLY_MODIFIED (new_type) = ಸತ್ಯ;
      C_TYPE_VARIABLE_SIZE (new_type) = ಸತ್ಯ;
    }
  ಪ್ರತ್ಯಾಗಮ new_type;
}

/* Build a pointer type using the default pointer mode.  */

ವೃಕ್ಷ
c_build_pointer_type (ವೃಕ್ಷ to_type)
{
  addr_space_t as = to_type == error_mark_ಗಂಟು ? ADDR_SPACE_GENERIC
					       : TYPE_ADDR_SPACE (to_type);
  machine_mode pointer_mode;

  ಯದಿ (as != ADDR_SPACE_GENERIC || c_default_pointer_mode == VOIDmode)
    pointer_mode = targetm.addr_space.pointer_mode (as);
  ಅನ್ಯಥಾ
    pointer_mode = c_default_pointer_mode;

  ಪ್ರತ್ಯಾಗಮ c_build_pointer_type_for_mode (to_type, pointer_mode, ಅಸತ್ಯ);
}

/* Build a pointer type using the given mode.  */

ವೃಕ್ಷ
c_build_pointer_type_for_mode (ವೃಕ್ಷ type, machine_mode mode, ತಾರ್ಕಿಕ m)
{
  ವೃಕ್ಷ ret = build_pointer_type_for_mode (type, mode, m);
  ಪ್ರತ್ಯಾಗಮ c_set_type_bits (ret, type);
}

/* Build a function type.  */

ವೃಕ್ಷ
c_build_function_type (ವೃಕ್ಷ type, ವೃಕ್ಷ args, ತಾರ್ಕಿಕ no)
{
  ವೃಕ್ಷ ret = build_function_type (type, args, no);
  ಪ್ರತ್ಯಾಗಮ c_set_type_bits (ret, type);
}

/* Build an array type.  This sets typeless storage as required
   by C2Y and C_TYPE_VARIABLY_MODIFIED and C_TYPE_VARIABLE_SIZE
   based on the element type and domain.  */

ವೃಕ್ಷ
c_build_array_type (ವೃಕ್ಷ type, ವೃಕ್ಷ domain)
{
  ಪೂರ್ಣಾಙ್ಕ type_quals = TYPE_QUALS (type);

  /* Identify typeless storage as introduced in C2Y
     and supported also in earlier language modes.  */
  ತಾರ್ಕಿಕ typeless = (char_type_p (type) && !(type_quals & TYPE_QUAL_ATOMIC))
		  || (AGGREGATE_TYPE_P (type) && TYPE_TYPELESS_STORAGE (type));

  ವೃಕ್ಷ ret = build_array_type (type, domain, typeless);

  ಯದಿ (ತುದಿ_array_vla_p (ret))
    {
      C_TYPE_VARIABLE_SIZE (ret) = 1;
      C_TYPE_VARIABLY_MODIFIED (ret) = 1;
    }

  ಪ್ರತ್ಯಾಗಮ c_set_type_bits (ret, type);
}

/* Build an array type of unspecified size.  */
ವೃಕ್ಷ
c_build_array_type_unspecified (ವೃಕ್ಷ type)
{
  ವೃಕ್ಷ upper = build2 (COMPOUND_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (size_zero_ಗಂಟು),
		       integer_zero_ಗಂಟು, size_zero_ಗಂಟು);
  ಪ್ರತ್ಯಾಗಮ c_build_array_type (type, build_index_type (upper));
}

/* Build an array type of zero size.  */
ವೃಕ್ಷ
c_build_array_type_zero_size (ವೃಕ್ಷ type)
{
  /* The GCC extension for zero-length arrays differs from
     ISO flexible array members in that sizeof yields
     zero.  */
  type = c_build_array_type (type, build_index_type (NULL_ವೃಕ್ಷ));
  type = build_distinct_type_copy (TYPE_MAIN_VARIANT (type));
  TYPE_SIZE (type) = bitsize_zero_ಗಂಟು;
  TYPE_SIZE_UNIT (type) = size_zero_ಗಂಟು;
  SET_TYPE_STRUCTURAL_EQUALITY (type);
  ಪ್ರತ್ಯಾಗಮ type;
}

ವೃಕ್ಷ
c_build_type_attribute_qual_variant (ವೃಕ್ಷ type, ವೃಕ್ಷ attrs, ಪೂರ್ಣಾಙ್ಕ quals)
{
  ವೃಕ್ಷ ret = build_type_attribute_qual_variant (type, attrs, quals);
  ಪ್ರತ್ಯಾಗಮ c_set_type_bits (ret, type);
}

ವೃಕ್ಷ
c_build_type_attribute_variant (ವೃಕ್ಷ type, ವೃಕ್ಷ attrs)
{
  ಪ್ರತ್ಯಾಗಮ c_build_type_attribute_qual_variant (type, attrs, TYPE_QUALS (type));
}

/* Reconstruct a complex derived type.  This is used to re-construct types
   with the vector attribute.  It is called via a langhook.  */

ವೃಕ್ಷ
c_reconstruct_complex_type (ವೃಕ್ಷ type, ವೃಕ್ಷ bottom)
{
  ವೃಕ್ಷ inner, outer;

  ಯದಿ (ವೃಕ್ಷ_CODE (type) == POINTER_TYPE)
    {
      inner = c_reconstruct_complex_type (ವೃಕ್ಷ_TYPE (type), bottom);
      outer = c_build_pointer_type_for_mode (inner, TYPE_MODE (type),
					     TYPE_REF_CAN_ALIAS_ALL (type));
    }
  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (type) == ARRAY_TYPE)
    {
      ತಾರ್ಕಿಕ rso = TYPE_REVERSE_STORAGE_ORDER (type);
      inner = c_reconstruct_complex_type (ವೃಕ್ಷ_TYPE (type), bottom);
      outer = c_build_array_type (inner, TYPE_DOMAIN (type));
      ಯದಿ (rso)
	{
	  outer = build_distinct_type_copy (outer);
	  TYPE_REVERSE_STORAGE_ORDER (outer) = 1;
	}

      gcc_checking_assert (C_TYPE_VARIABLE_SIZE (type)
			   == C_TYPE_VARIABLE_SIZE (outer));
    }
  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (type) == FUNCTION_TYPE)
    {
      inner = c_reconstruct_complex_type (ವೃಕ್ಷ_TYPE (type), bottom);
      outer = c_build_function_type (inner, TYPE_ARG_TYPES (type),
				     TYPE_NO_NAMED_ARGS_STDARG_P (type));
    }
  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (type) == REFERENCE_TYPE
	   || ವೃಕ್ಷ_CODE (type) == OFFSET_TYPE)
    gcc_unreachable ();
  ಅನ್ಯಥಾ
    ಪ್ರತ್ಯಾಗಮ bottom;

  ಪ್ರತ್ಯಾಗಮ c_build_type_attribute_qual_variant (outer, TYPE_ATTRIBUTES (type),
					      TYPE_QUALS (type));
}


/* Helper function for c_canonical_type.  Check whether FIELD
   contains a pointer to a structure or union with tag,
   possibly nested in other type derivations, and return the
   type of this nested structure or union.  */
ಸ್ಥಿರ ವೃಕ್ಷ
ptr_to_tagged_member (ವೃಕ್ಷ field)
{
  gcc_assert (FIELD_DECL == ವೃಕ್ಷ_CODE (field));
  ವೃಕ್ಷ type = ವೃಕ್ಷ_TYPE (field);
  ತಾರ್ಕಿಕ ptr_seen = ಅಸತ್ಯ;
  ಯಾವತ್ (ವೃಕ್ಷ_CODE (type) == ARRAY_TYPE
	 || ವೃಕ್ಷ_CODE (type) == FUNCTION_TYPE
	 || ವೃಕ್ಷ_CODE (type) == POINTER_TYPE)
    {
      ಯದಿ (ವೃಕ್ಷ_CODE (type) == POINTER_TYPE)
	ptr_seen = ಸತ್ಯ;
      type = ವೃಕ್ಷ_TYPE (type);
    }

  ಯದಿ (ptr_seen
      && RECORD_OR_UNION_TYPE_P (type)
      && NULL_ವೃಕ್ಷ != c_type_tag (type))
    ಪ್ರತ್ಯಾಗಮ type;

  ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
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
ವೃಕ್ಷ
c_type_canonical (ವೃಕ್ಷ type)
{
  gcc_assert (RECORD_OR_UNION_TYPE_P (type));

  ತಾರ್ಕಿಕ needs_mod = ಅಸತ್ಯ;
  ಪ್ರತಿ (ವೃಕ್ಷ x = TYPE_FIELDS (type); x; x = DECL_CHAIN (x))
    {
      ಯದಿ (!ptr_to_tagged_member (x))
	ಅನುವರ್ತ;
      needs_mod = ಸತ್ಯ;
      ಭಙ್ಗ;
    }
  ಯದಿ (!needs_mod)
    ಪ್ರತ್ಯಾಗಮ type;

  /* Construct new version with such members replaced.  */
  ವೃಕ್ಷ n = build_distinct_type_copy (type);
  ವೃಕ್ಷ *fields = &TYPE_FIELDS (n);
  ಪ್ರತಿ (ವೃಕ್ಷ x = TYPE_FIELDS (type); x; x = DECL_CHAIN (x))
    {
      ವೃಕ್ಷ f = copy_ಗಂಟು (x);
      ಯದಿ (ವೃಕ್ಷ m = ptr_to_tagged_member (x))
	{
	  ವೃಕ್ಷ new_ಗಂಟು = make_ಗಂಟು (ವೃಕ್ಷ_CODE (m));
	  TYPE_NAME (new_ಗಂಟು) = TYPE_NAME (m);
	  SET_TYPE_STRUCTURAL_EQUALITY (new_ಗಂಟು);
	  new_ಗಂಟು = qualify_type (new_ಗಂಟು, m);
	  ವೃಕ್ಷ_TYPE (f) = c_reconstruct_complex_type (ವೃಕ್ಷ_TYPE (x),
						      new_ಗಂಟು);
	}
      *fields = f;
      fields = &DECL_CHAIN (f);
    }
  TYPE_CANONICAL (n) = n;
  ಪ್ರತ್ಯಾಗಮ n;
}


/* If NTYPE is a type of a non-variadic function with a prototype
   and OTYPE is a type of a function without a prototype and ATTRS
   contains attribute format, diagnosess and removes it from ATTRS.
   Returns the result of build_type_attribute_variant of NTYPE and
   the (possibly) modified ATTRS.  */

ಸ್ಥಿರ ವೃಕ್ಷ
c_build_functype_attribute_variant (ವೃಕ್ಷ ntype, ವೃಕ್ಷ otype, ವೃಕ್ಷ attrs)
{
  ಯದಿ (!prototype_p (otype)
      && prototype_p (ntype)
      && lookup_attribute ("format", attrs))
    {
      warning_at (ಒಳಹರಿವು_location, OPT_Wattributes,
		  "%qs attribute can only be applied to variadic functions",
		  "format");
      attrs = remove_attribute ("format", attrs);
    }
  ಪ್ರತ್ಯಾಗಮ c_build_type_attribute_variant (ntype, attrs);

}

/* Given a type which could be a typedef name, make sure to return the
   original type.  See set_underlying_type. */
ಸ್ಥಿರ const_ವೃಕ್ಷ
c_type_original (const_ವೃಕ್ಷ t)
{
  /* It may even be a typedef of a typedef...
     In the case of compiler-created builtin structs the TYPE_DECL
     may be a dummy, with no DECL_ORIGINAL_TYPE.  Don't fault.  */
  ಯಾವತ್ (TYPE_NAME (t)
	 && ವೃಕ್ಷ_CODE (TYPE_NAME (t)) == TYPE_DECL
	 && DECL_ORIGINAL_TYPE (TYPE_NAME (t)))
    t = DECL_ORIGINAL_TYPE (TYPE_NAME (t));
  ಪ್ರತ್ಯಾಗಮ t;
}

/* Return the tag for a tagged type.  */
ವೃಕ್ಷ
c_type_tag (const_ವೃಕ್ಷ t)
{
  gcc_assert (RECORD_OR_UNION_TYPE_P (t) || ವೃಕ್ಷ_CODE (t) == ENUMERAL_TYPE);
  const_ವೃಕ್ಷ orig = c_type_original (t);
  ವೃಕ್ಷ name = TYPE_NAME (orig);
  ಯದಿ (!name)
    ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
  ಯದಿ (ವೃಕ್ಷ_CODE (name) == TYPE_DECL)
    {
      ಯದಿ (!DECL_NAME (name))
	ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
      name = DECL_NAME (name);
    }
  gcc_checking_assert (ವೃಕ್ಷ_CODE (name) == IDENTIFIER_ಗಂಟು);
  ಪ್ರತ್ಯಾಗಮ name;
}

/* Remove qualifiers but not atomic.  For arrays remove qualifiers
   on the element type but also do not remove atomic.  */
ಸ್ಥಿರ ವೃಕ್ಷ
remove_qualifiers (ವೃಕ್ಷ t)
{
  ಯದಿ (!t || t == error_mark_ಗಂಟು)
    ಪ್ರತ್ಯಾಗಮ t;
  ಪ್ರತ್ಯಾಗಮ TYPE_ATOMIC (strip_array_types (t))
	 ? c_build_qualified_type (TYPE_MAIN_VARIANT (t), TYPE_QUAL_ATOMIC)
	 : TYPE_MAIN_VARIANT (t);
}


/* Helper function for composite_type_internal.  Find a compatible type
   in a (transparent) union U compatible to T.  If found, return the
   type of the corresponding member.  Otherwise, return the union type U.  */
ಸ್ಥಿರ ವೃಕ್ಷ
transparent_union_replacement (ವೃಕ್ಷ u, ವೃಕ್ಷ t)
{
  ಯದಿ (u == error_mark_ಗಂಟು || t == error_mark_ಗಂಟು
      || ವೃಕ್ಷ_CODE (u) != UNION_TYPE
      || !(TYPE_TRANSPARENT_AGGR (u) || TYPE_NAME (u) == NULL_ವೃಕ್ಷ)
      || comptypes (u, t))
    ಪ್ರತ್ಯಾಗಮ u;

  ಪ್ರತಿ (ವೃಕ್ಷ memb = TYPE_FIELDS (u); memb; memb = DECL_CHAIN (memb))
    {
      ವೃಕ್ಷ m = remove_qualifiers (ವೃಕ್ಷ_TYPE (memb));
      ಯದಿ (comptypes (m, t))
	{
	  pedwarn (ಒಳಹರಿವು_location, OPT_Wpedantic,
		    "function types not truly compatible in ISO C");
	  ಪ್ರತ್ಯಾಗಮ m;
	}
    }

  ಪ್ರತ್ಯಾಗಮ u;
}



/* Return the composite type of two compatible types.

   We assume that comptypes has already been done and returned
   nonzero; if that isn't so, this may crash.  In particular, we
   assume that qualifiers match.  */

ಸಂರಚನಾ composite_cache {
  ವೃಕ್ಷ t1;
  ವೃಕ್ಷ t2;
  ವೃಕ್ಷ composite;
  ಸಂರಚನಾ composite_cache* next;
};

ವೃಕ್ಷ
composite_type_internal (ವೃಕ್ಷ t1, ವೃಕ್ಷ t2, ವೃಕ್ಷ cond,
			 ಸಂರಚನಾ composite_cache* cache)
{
  ಗಣನಾ ವೃಕ್ಷ_code code1;
  ಗಣನಾ ವೃಕ್ಷ_code code2;
  ವೃಕ್ಷ attributes;

  /* Save time if the two types are the same.  */

  ಯದಿ (t1 == t2) ಪ್ರತ್ಯಾಗಮ t1;

  /* If one type is nonsense, use the other.  */
  ಯದಿ (t1 == error_mark_ಗಂಟು)
    ಪ್ರತ್ಯಾಗಮ t2;
  ಯದಿ (t2 == error_mark_ಗಂಟು)
    ಪ್ರತ್ಯಾಗಮ t1;

  code1 = ವೃಕ್ಷ_CODE (t1);
  code2 = ವೃಕ್ಷ_CODE (t2);

  /* Merge the attributes.  */
  attributes = targetm.merge_type_attributes (t1, t2);

  /* If one is an enumerated type and the other is the compatible
     integer type, the composite type might be either of the two
     (DR#013 question 3).  For consistency, use the enumerated type as
     the composite type.  */

  ಯದಿ (code1 == ENUMERAL_TYPE
      && (code2 == INTEGER_TYPE
	  || code2 == BOOLEAN_TYPE))
    ಪ್ರತ್ಯಾಗಮ t1;
  ಯದಿ (code2 == ENUMERAL_TYPE
      && (code1 == INTEGER_TYPE
	  || code1 == BOOLEAN_TYPE))
    ಪ್ರತ್ಯಾಗಮ t2;

  gcc_assert (code1 == code2);

  ವಿಕಲ್ಪ (code1)
    {
    ಪಕ್ಷ POINTER_TYPE:
      /* For two pointers, do this recursively on the target type.  */
      {
	gcc_checking_assert (TYPE_QUALS (t1) == TYPE_QUALS (t2));
	ವೃಕ್ಷ target = composite_type_internal (ವೃಕ್ಷ_TYPE (t1), ವೃಕ್ಷ_TYPE (t2),
					       cond, cache);
	ವೃಕ್ಷ n = c_build_pointer_type_for_mode (target, TYPE_MODE (t1), ಅಸತ್ಯ);
	ಪ್ರತ್ಯಾಗಮ c_build_type_attribute_qual_variant (n, attributes,
						    TYPE_QUALS (t2));
      }

    ಪಕ್ಷ ARRAY_TYPE:
      {
	ವೃಕ್ಷ d1 = TYPE_DOMAIN (t1);
	ವೃಕ್ಷ d2 = TYPE_DOMAIN (t2);

	/* We should not have any type quals on arrays at all.  */
	gcc_assert (!TYPE_QUALS_NO_ADDR_SPACE (t1)
		    && !TYPE_QUALS_NO_ADDR_SPACE (t2));

	ತಾರ್ಕಿಕ d1_zero = zero_length_array_type_p (t1)
		       || flexible_array_member_type_p (t1);
	ತಾರ್ಕಿಕ d2_zero = zero_length_array_type_p (t2)
		       || flexible_array_member_type_p (t2);

	ತಾರ್ಕಿಕ d1_variable = ತುದಿ_array_vla_p (t1);
	ತಾರ್ಕಿಕ d2_variable = ತುದಿ_array_vla_p (t2);

	ತಾರ್ಕಿಕ use1 = d1 && (d2_variable || !d2 || d2_zero || !d1_variable);
	ತಾರ್ಕಿಕ use2 = d2 && (d1_variable || !d1 || d1_zero || !d2_variable);

	/* If the first is an unspecified size pick the other one.  */
	ಯದಿ (d2_variable && c_type_unspecified_p (t1))
	  {
	    gcc_assert (use1 && use2);
	    use1 = ಅಸತ್ಯ;
	  }

	/* If both are VLAs but not unspecified and we are in the
	   conditional operator, we create a conditional to select
	   the size of the active branch.  */
	ತಾರ್ಕಿಕ use0 = cond && d1_variable && !c_type_unspecified_p (t1)
			 && d2_variable && !c_type_unspecified_p (t2);

	ವೃಕ್ಷ td;
	ವೃಕ್ಷ elt = composite_type_internal (ವೃಕ್ಷ_TYPE (t1), ವೃಕ್ಷ_TYPE (t2),
					    cond, cache);

	ಯದಿ (!use0)
	  {
	    /* Save space: see if the result is identical to one of the args.  */
	    ಯದಿ (elt == ವೃಕ್ಷ_TYPE (t1) && use1)
	      ಪ್ರತ್ಯಾಗಮ c_build_type_attribute_variant (t1, attributes);
	    ಯದಿ (elt == ವೃಕ್ಷ_TYPE (t2) && use2)
	      ಪ್ರತ್ಯಾಗಮ c_build_type_attribute_variant (t2, attributes);

	    ಯದಿ (elt == ವೃಕ್ಷ_TYPE (t1) && !TYPE_DOMAIN (t2) && !TYPE_DOMAIN (t1))
	      ಪ್ರತ್ಯಾಗಮ c_build_type_attribute_variant (t1, attributes);
	    ಯದಿ (elt == ವೃಕ್ಷ_TYPE (t2) && !TYPE_DOMAIN (t2) && !TYPE_DOMAIN (t1))
	      ಪ್ರತ್ಯಾಗಮ c_build_type_attribute_variant (t2, attributes);

	    td = TYPE_DOMAIN (use1 ? t1 : t2);
	  }
	ಅನ್ಯಥಾ
	  {
	    /* Not used in C.  */
	    gcc_assert (size_zero_ಗಂಟು == TYPE_MIN_ಮೌಲ್ಯ (d1));
	    gcc_assert (size_zero_ಗಂಟು == TYPE_MIN_ಮೌಲ್ಯ (d2));

	    ವೃಕ್ಷ d = fold_build3_loc (UNKNOWN_LOCATION, COND_ಅಭಿವ್ಯಕ್ತಿ, sizetype,
				      cond, TYPE_MAX_ಮೌಲ್ಯ (d1),
				      TYPE_MAX_ಮೌಲ್ಯ (d2));

	    td = build_index_type (d);
	  }

	/* Merge the element types, and have a size if either arg has
	   one.  We may have qualifiers on the element types.  To set
	   up TYPE_MAIN_VARIANT correctly, we need to form the
	   composite of the unqualified types and add the qualifiers
	   back at the end.  */
	ಪೂರ್ಣಾಙ್ಕ quals = TYPE_QUALS (strip_array_types (elt));
	ವೃಕ್ಷ unqual_elt = c_build_qualified_type (elt, TYPE_UNQUALIFIED);

	ಯದಿ ((!d1 || d1_zero) && (!d2 || d2_zero) && (d1 || d2))
	  t1 = c_build_array_type_zero_size (unqual_elt);
	ಅನ್ಯಥಾ
	  t1 = c_build_array_type (unqual_elt, td);

	/* Check that a type which has a varying outermost dimension
	   got marked as having a variable size.  */
	ತಾರ್ಕಿಕ varsize = (d1_variable && d2_variable)
		       || (d1_variable && !d2)
		       || (d2_variable && !d1);
	gcc_checking_assert (!varsize || C_TYPE_VARIABLE_SIZE (t1));

	t1 = c_build_qualified_type (t1, quals);
	ಪ್ರತ್ಯಾಗಮ c_build_type_attribute_variant (t1, attributes);
      }

    ಪಕ್ಷ RECORD_TYPE:
    ಪಕ್ಷ UNION_TYPE:
      ಯದಿ (flag_isoc23 && !comptypes_same_p (t1, t2))
	{
	  /* Go to the original type to get the right tag.  */
	  ವೃಕ್ಷ tag = c_type_tag (t1);

	  gcc_checking_assert (COMPLETE_TYPE_P (t1) && COMPLETE_TYPE_P (t2));
	  gcc_checking_assert (!tag || comptypes (t1, t2));

	  /* If a composite type for these two types is already under
	     construction, return it.  */

	  ಪ್ರತಿ (ಸಂರಚನಾ composite_cache *c = cache; c != ರಿಕ್ತ; c = c->next)
	    ಯದಿ ((c->t1 == t1 && c->t2 == t2) || (c->t1 == t2 && c->t2 == t1))
	       ಪ್ರತ್ಯಾಗಮ c->composite;

	  /* Otherwise, create a new type node and link it into the cache.  */

	  ವೃಕ್ಷ n = make_ಗಂಟು (code1);
	  SET_TYPE_STRUCTURAL_EQUALITY (n);
	  TYPE_NAME (n) = tag;

	  ಸಂರಚನಾ composite_cache cache2 = { t1, t2, n, cache };
	  cache = &cache2;

	  ವೃಕ್ಷ f1 = TYPE_FIELDS (t1);
	  ವೃಕ್ಷ f2 = TYPE_FIELDS (t2);
	  ವೃಕ್ಷ fields = NULL_ವೃಕ್ಷ;

	  ಪ್ರತಿ (ವೃಕ್ಷ a = f1, b = f2; a && b;
	       a = DECL_CHAIN (a), b = DECL_CHAIN (b))
	    {
	      ವೃಕ್ಷ ta = ವೃಕ್ಷ_TYPE (a);
	      ವೃಕ್ಷ tb = ವೃಕ್ಷ_TYPE (b);

	      ಯದಿ (DECL_C_BIT_FIELD (a))
		{
		  ta = DECL_BIT_FIELD_TYPE (a);
		  tb = DECL_BIT_FIELD_TYPE (b);
		}

	      gcc_assert (DECL_NAME (a) == DECL_NAME (b));
	      gcc_checking_assert (!DECL_NAME (a) || comptypes (ta, tb));

	      ವೃಕ್ಷ t = composite_type_internal (ta, tb, cond, cache);
	      ವೃಕ್ಷ f = build_decl (ಒಳಹರಿವು_location, FIELD_DECL, DECL_NAME (a), t);

	      DECL_PACKED (f) = DECL_PACKED (a);
	      SET_DECL_ALIGN (f, DECL_ALIGN (a));
	      DECL_ATTRIBUTES (f) = DECL_ATTRIBUTES (a);
	      C_DECL_VARIABLE_SIZE (f) = C_TYPE_VARIABLE_SIZE (t);

	      decl_attributes (&f, DECL_ATTRIBUTES (f), 0);

	      finish_decl (f, ಒಳಹರಿವು_location, ರಿಕ್ತ, ರಿಕ್ತ, ರಿಕ್ತ);

	      ಯದಿ (DECL_C_BIT_FIELD (a))
		{
		  /* This will be processed by finish_struct.  */
		  SET_DECL_C_BIT_FIELD (f);
		  DECL_INITIAL (f) = build_int_cst (integer_type_ಗಂಟು,
						    ವೃಕ್ಷ_to_uhwi (DECL_SIZE (a)));
		  DECL_NONADDRESSABLE_P (f) = ಸತ್ಯ;
		  DECL_PADDING_P (f) = !DECL_NAME (a);
		}

	      DECL_CHAIN (f) = fields;
	      fields = f;
	    }

	  fields = nreverse (fields);

	  /* Setup the struct/union type.  Because we inherit all variably
	     modified components, we can ignore the size expression.  */
	  ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ = NULL_ವೃಕ್ಷ;

	  /* Set TYPE_STUB_DECL for debugging symbols.  */
	  TYPE_STUB_DECL (n) = pushdecl (build_decl (ಒಳಹರಿವು_location, TYPE_DECL,
						     NULL_ವೃಕ್ಷ, n));

	  n = finish_struct (ಒಳಹರಿವು_location, n, fields, attributes, ರಿಕ್ತ,
			     &ಅಭಿವ್ಯಕ್ತಿ);

	  ಪ್ರತ್ಯಾಗಮ qualify_type (n, t1);
	}
      /* FALLTHRU */
    ಪಕ್ಷ ENUMERAL_TYPE:
      ಯದಿ (attributes != ರಿಕ್ತ)
	{
	  /* Try harder not to create a new aggregate type.  */
	  ಯದಿ (attribute_list_equal (TYPE_ATTRIBUTES (t1), attributes))
	    ಪ್ರತ್ಯಾಗಮ t1;
	  ಯದಿ (attribute_list_equal (TYPE_ATTRIBUTES (t2), attributes))
	    ಪ್ರತ್ಯಾಗಮ t2;
	}
      ಪ್ರತ್ಯಾಗಮ c_build_type_attribute_variant (t1, attributes);

    ಪಕ್ಷ FUNCTION_TYPE:
      /* Function types: prefer the one that specified arg types.
	 If both do, merge the arg types.  Also merge the return types.  */
      {
	ವೃಕ್ಷ valtype = composite_type_internal (ವೃಕ್ಷ_TYPE (t1), ವೃಕ್ಷ_TYPE (t2),
						cond, cache);
	ವೃಕ್ಷ p1 = TYPE_ARG_TYPES (t1);
	ವೃಕ್ಷ p2 = TYPE_ARG_TYPES (t2);

	/* Save space: see if the result is identical to one of the args.  */
	ಯದಿ (valtype == ವೃಕ್ಷ_TYPE (t1) && !TYPE_ARG_TYPES (t2))
	  ಪ್ರತ್ಯಾಗಮ c_build_functype_attribute_variant (t1, t2, attributes);
	ಯದಿ (valtype == ವೃಕ್ಷ_TYPE (t2) && !TYPE_ARG_TYPES (t1))
	  ಪ್ರತ್ಯಾಗಮ c_build_functype_attribute_variant (t2, t1, attributes);

	/* Simple way if one arg fails to specify argument types.  */
	ಯದಿ (TYPE_ARG_TYPES (t1) == NULL_ವೃಕ್ಷ)
	  {
	    t1 = c_build_function_type (valtype, TYPE_ARG_TYPES (t2),
					TYPE_NO_NAMED_ARGS_STDARG_P (t2));
	    t1 = c_build_type_attribute_variant (t1, attributes);
	    ಪ್ರತ್ಯಾಗಮ qualify_type (t1, t2);
	 }
	ಯದಿ (TYPE_ARG_TYPES (t2) == NULL_ವೃಕ್ಷ)
	  {
	    t1 = c_build_function_type (valtype, TYPE_ARG_TYPES (t1),
					TYPE_NO_NAMED_ARGS_STDARG_P (t1));
	    t1 = c_build_type_attribute_variant (t1, attributes);
	    ಪ್ರತ್ಯಾಗಮ qualify_type (t1, t2);
	  }

	/* If both args specify argument types, we must merge the two
	   lists, argument by argument.  */
	ವೃಕ್ಷ newargs = NULL_ವೃಕ್ಷ;
	ವೃಕ್ಷ *endp = &newargs;

	ಪ್ರತಿ (; p1; p1 = ವೃಕ್ಷ_CHAIN (p1), p2 = ವೃಕ್ಷ_CHAIN (p2))
	  {
	    ಯದಿ (p1 == void_list_ಗಂಟು)
	      {
		*endp = void_list_ಗಂಟು;
		ಭಙ್ಗ;
	      }
	    ವೃಕ್ಷ mv1 = remove_qualifiers (ವೃಕ್ಷ_ಮೌಲ್ಯ (p1));
	    ವೃಕ್ಷ mv2 = remove_qualifiers (ವೃಕ್ಷ_ಮೌಲ್ಯ (p2));

	    gcc_assert (mv1);
	    gcc_assert (mv2);

	    mv1 = transparent_union_replacement (mv1, mv2);
	    mv2 = transparent_union_replacement (mv2, mv1);

	    *endp = ವೃಕ್ಷ_cons (NULL_ವೃಕ್ಷ,
			       composite_type_internal (mv1, mv2, cond, cache),
			       NULL_ವೃಕ್ಷ);

	    endp = &ವೃಕ್ಷ_CHAIN (*endp);
	  }

	t1 = c_build_function_type (valtype, newargs);
	t1 = qualify_type (t1, t2);
      }
      /* FALLTHRU */

    ಸ್ವಭಾವ:
      ಪ್ರತ್ಯಾಗಮ c_build_type_attribute_variant (t1, attributes);
    }
}

ವೃಕ್ಷ
composite_type_cond (ವೃಕ್ಷ t1, ವೃಕ್ಷ t2, ವೃಕ್ಷ cond)
{
  gcc_checking_assert (comptypes_check_for_composite (t1, t2));

  ಸಂರಚನಾ composite_cache cache = { };
  ವೃಕ್ಷ n = composite_type_internal (t1, t2, cond, &cache);

  gcc_checking_assert (comptypes_check_for_composite (n, t1));
  gcc_checking_assert (comptypes_check_for_composite (n, t2));
  ಪ್ರತ್ಯಾಗಮ n;
}


ವೃಕ್ಷ
composite_type (ವೃಕ್ಷ t1, ವೃಕ್ಷ t2)
{
  ಪ್ರತ್ಯಾಗಮ composite_type_cond (t1, t2, NULL_ವೃಕ್ಷ);
}

/* Return the type of a conditional expression between pointers to
   possibly differently qualified versions of compatible types.

   We assume that comp_target_types has already been done and returned
   true; if that isn't so, this may crash.  */

ಸ್ಥಿರ ವೃಕ್ಷ
common_pointer_type (ವೃಕ್ಷ t1, ವೃಕ್ಷ t2, ವೃಕ್ಷ cond)
{
  ವೃಕ್ಷ attributes;
  unsigned target_quals;
  addr_space_t as1, as2, as_common;
  ಪೂರ್ಣಾಙ್ಕ quals1, quals2;

  /* Save time if the two types are the same.  */

  ಯದಿ (t1 == t2) ಪ್ರತ್ಯಾಗಮ t1;

  /* If one type is nonsense, use the other.  */
  ಯದಿ (t1 == error_mark_ಗಂಟು)
    ಪ್ರತ್ಯಾಗಮ t2;
  ಯದಿ (t2 == error_mark_ಗಂಟು)
    ಪ್ರತ್ಯಾಗಮ t1;

  gcc_assert (ವೃಕ್ಷ_CODE (t1) == POINTER_TYPE
	      && ವೃಕ್ಷ_CODE (t2) == POINTER_TYPE);

  /* Merge the attributes.  */
  attributes = targetm.merge_type_attributes (t1, t2);

  /* Find the composite type of the target types, and combine the
     qualifiers of the two types' targets.  */
  ವೃಕ್ಷ pointed_to_1 = ವೃಕ್ಷ_TYPE (t1);
  ವೃಕ್ಷ pointed_to_2 = ವೃಕ್ಷ_TYPE (t2);
  ವೃಕ್ಷ target = composite_type_cond (TYPE_MAIN_VARIANT (pointed_to_1),
				     TYPE_MAIN_VARIANT (pointed_to_2), cond);

  /* Strip array types to get correct qualifier for pointers to arrays */
  quals1 = TYPE_QUALS_NO_ADDR_SPACE (strip_array_types (pointed_to_1));
  quals2 = TYPE_QUALS_NO_ADDR_SPACE (strip_array_types (pointed_to_2));

  /* For function types do not merge const qualifiers, but drop them
     if used inconsistently.  The middle-end uses these to mark const
     and noreturn functions.  */
  ಯದಿ (ವೃಕ್ಷ_CODE (pointed_to_1) == FUNCTION_TYPE)
    target_quals = (quals1 & quals2);
  ಅನ್ಯಥಾ
    target_quals = (quals1 | quals2);

  /* If the two named address spaces are different, determine the common
     superset address space.  This is guaranteed to exist due to the
     assumption that comp_target_type returned true.  */
  as1 = TYPE_ADDR_SPACE (pointed_to_1);
  as2 = TYPE_ADDR_SPACE (pointed_to_2);
  ಯದಿ (!addr_space_superset (as1, as2, &as_common))
    gcc_unreachable ();

  target_quals |= ENCODE_QUAL_ADDR_SPACE (as_common);

  t1 = c_build_pointer_type (c_build_qualified_type (target, target_quals));
  ಪ್ರತ್ಯಾಗಮ c_build_type_attribute_variant (t1, attributes);
}

/* Return the common type for two arithmetic types under the usual
   arithmetic conversions.  The default conversions have already been
   applied, and enumerated types converted to their compatible integer
   types.  The resulting type is unqualified and has no attributes.

   This is the type for the result of most arithmetic operations
   if the operands have the given two types.  */

ಸ್ಥಿರ ವೃಕ್ಷ
c_common_type (ವೃಕ್ಷ t1, ವೃಕ್ಷ t2)
{
  ಗಣನಾ ವೃಕ್ಷ_code code1;
  ಗಣನಾ ವೃಕ್ಷ_code code2;

  /* If one type is nonsense, use the other.  */
  ಯದಿ (t1 == error_mark_ಗಂಟು)
    ಪ್ರತ್ಯಾಗಮ t2;
  ಯದಿ (t2 == error_mark_ಗಂಟು)
    ಪ್ರತ್ಯಾಗಮ t1;

  ಯದಿ (TYPE_QUALS (t1) != TYPE_UNQUALIFIED)
    t1 = TYPE_MAIN_VARIANT (t1);

  ಯದಿ (TYPE_QUALS (t2) != TYPE_UNQUALIFIED)
    t2 = TYPE_MAIN_VARIANT (t2);

  ಯದಿ (TYPE_ATTRIBUTES (t1) != NULL_ವೃಕ್ಷ)
    {
      ವೃಕ್ಷ attrs = affects_type_identity_attributes (TYPE_ATTRIBUTES (t1));
      t1 = c_build_type_attribute_variant (t1, attrs);
    }

  ಯದಿ (TYPE_ATTRIBUTES (t2) != NULL_ವೃಕ್ಷ)
    {
      ವೃಕ್ಷ attrs = affects_type_identity_attributes (TYPE_ATTRIBUTES (t2));
      t2 = c_build_type_attribute_variant (t2, attrs);
    }

  /* Save time if the two types are the same.  */

  ಯದಿ (t1 == t2) ಪ್ರತ್ಯಾಗಮ t1;

  code1 = ವೃಕ್ಷ_CODE (t1);
  code2 = ವೃಕ್ಷ_CODE (t2);

  gcc_assert (code1 == VECTOR_TYPE || code1 == COMPLEX_TYPE
	      || code1 == FIXED_POINT_TYPE || code1 == REAL_TYPE
	      || code1 == INTEGER_TYPE || code1 == BITINT_TYPE);
  gcc_assert (code2 == VECTOR_TYPE || code2 == COMPLEX_TYPE
	      || code2 == FIXED_POINT_TYPE || code2 == REAL_TYPE
	      || code2 == INTEGER_TYPE || code2 == BITINT_TYPE);

  /* When one operand is a decimal float type, the other operand cannot be
     a generic float type or a complex type.  We also disallow vector types
     here.  */
  ಯದಿ ((DECIMAL_FLOAT_TYPE_P (t1) || DECIMAL_FLOAT_TYPE_P (t2))
      && !(DECIMAL_FLOAT_TYPE_P (t1) && DECIMAL_FLOAT_TYPE_P (t2)))
    {
      ಯದಿ (code1 == VECTOR_TYPE || code2 == VECTOR_TYPE)
	{
	  error ("cannot mix operands of decimal floating and vector types");
	  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	}
      ಯದಿ (code1 == COMPLEX_TYPE || code2 == COMPLEX_TYPE)
	{
	  error ("cannot mix operands of decimal floating and complex types");
	  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	}
      ಯದಿ (code1 == REAL_TYPE && code2 == REAL_TYPE)
	{
	  error ("cannot mix operands of decimal floating "
		 "and other floating types");
	  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	}
    }

  /* If one type is a vector type, return that type.  (How the usual
     arithmetic conversions apply to the vector types extension is not
     precisely specified.)  */
  ಯದಿ (code1 == VECTOR_TYPE)
    ಪ್ರತ್ಯಾಗಮ t1;

  ಯದಿ (code2 == VECTOR_TYPE)
    ಪ್ರತ್ಯಾಗಮ t2;

  /* If one type is complex, form the common type of the non-complex
     components, then make that complex.  Use T1 or T2 if it is the
     required type.  */
  ಯದಿ (code1 == COMPLEX_TYPE || code2 == COMPLEX_TYPE)
    {
      ವೃಕ್ಷ subtype1 = code1 == COMPLEX_TYPE ? ವೃಕ್ಷ_TYPE (t1) : t1;
      ವೃಕ್ಷ subtype2 = code2 == COMPLEX_TYPE ? ವೃಕ್ಷ_TYPE (t2) : t2;
      ವೃಕ್ಷ subtype = c_common_type (subtype1, subtype2);

      ಯದಿ (code1 == COMPLEX_TYPE && ವೃಕ್ಷ_TYPE (t1) == subtype)
	ಪ್ರತ್ಯಾಗಮ t1;
      ಅನ್ಯಥಾ ಯದಿ (code2 == COMPLEX_TYPE && ವೃಕ್ಷ_TYPE (t2) == subtype)
	ಪ್ರತ್ಯಾಗಮ t2;
      ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (subtype) == BITINT_TYPE)
	{
	  sorry ("%<_Complex _BitInt(%d)%> unsupported",
		 TYPE_PRECISION (subtype));
	  ಪ್ರತ್ಯಾಗಮ code1 == COMPLEX_TYPE ? t1 : t2;
	}
      ಅನ್ಯಥಾ
	ಪ್ರತ್ಯಾಗಮ build_complex_type (subtype);
    }

  /* If only one is real, use it as the result.  */

  ಯದಿ (code1 == REAL_TYPE && code2 != REAL_TYPE)
    ಪ್ರತ್ಯಾಗಮ t1;

  ಯದಿ (code2 == REAL_TYPE && code1 != REAL_TYPE)
    ಪ್ರತ್ಯಾಗಮ t2;

  /* If both are real and either are decimal floating point types, use
     the decimal floating point type with the greater precision. */

  ಯದಿ (code1 == REAL_TYPE && code2 == REAL_TYPE)
    {
      ಯದಿ (TYPE_MAIN_VARIANT (t1) == dfloat128_type_ಗಂಟು
	  || TYPE_MAIN_VARIANT (t2) == dfloat128_type_ಗಂಟು)
	ಪ್ರತ್ಯಾಗಮ dfloat128_type_ಗಂಟು;
      /* And prefer _Decimal128 over _Decimal64x which has in GCC's
	 implementation the same mode.  */
      ಅನ್ಯಥಾ ಯದಿ (TYPE_MAIN_VARIANT (t1) == dfloat64x_type_ಗಂಟು
	       || TYPE_MAIN_VARIANT (t2) == dfloat64x_type_ಗಂಟು)
	ಪ್ರತ್ಯಾಗಮ dfloat64x_type_ಗಂಟು;
      ಅನ್ಯಥಾ ಯದಿ (TYPE_MAIN_VARIANT (t1) == dfloat64_type_ಗಂಟು
	       || TYPE_MAIN_VARIANT (t2) == dfloat64_type_ಗಂಟು)
	ಪ್ರತ್ಯಾಗಮ dfloat64_type_ಗಂಟು;
      ಅನ್ಯಥಾ ಯದಿ (TYPE_MAIN_VARIANT (t1) == dfloat32_type_ಗಂಟು
	       || TYPE_MAIN_VARIANT (t2) == dfloat32_type_ಗಂಟು)
	ಪ್ರತ್ಯಾಗಮ dfloat32_type_ಗಂಟು;
    }

  /* Deal with fixed-point types.  */
  ಯದಿ (code1 == FIXED_POINT_TYPE || code2 == FIXED_POINT_TYPE)
    {
      unsigned ಪೂರ್ಣಾಙ್ಕ unsignedp = 0, satp = 0;
      scalar_mode m1, m2;
      unsigned ಪೂರ್ಣಾಙ್ಕ fbit1, ibit1, fbit2, ibit2, max_fbit, max_ibit;

      m1 = SCALAR_TYPE_MODE (t1);
      m2 = SCALAR_TYPE_MODE (t2);

      /* If one input type is saturating, the result type is saturating.  */
      ಯದಿ (TYPE_SATURATING (t1) || TYPE_SATURATING (t2))
	satp = 1;

      /* If both fixed-point types are unsigned, the result type is unsigned.
	 When mixing fixed-point and integer types, follow the sign of the
	 fixed-point type.
	 Otherwise, the result type is signed.  */
      ಯದಿ ((TYPE_UNSIGNED (t1) && TYPE_UNSIGNED (t2)
	   && code1 == FIXED_POINT_TYPE && code2 == FIXED_POINT_TYPE)
	  || (code1 == FIXED_POINT_TYPE && code2 != FIXED_POINT_TYPE
	      && TYPE_UNSIGNED (t1))
	  || (code1 != FIXED_POINT_TYPE && code2 == FIXED_POINT_TYPE
	      && TYPE_UNSIGNED (t2)))
	unsignedp = 1;

      /* The result type is signed.  */
      ಯದಿ (unsignedp == 0)
	{
	  /* If the input type is unsigned, we need to convert to the
	     signed type.  */
	  ಯದಿ (code1 == FIXED_POINT_TYPE && TYPE_UNSIGNED (t1))
	    {
	      ಗಣನಾ mode_class mclass = (ಗಣನಾ mode_class) 0;
	      ಯದಿ (GET_MODE_CLASS (m1) == MODE_UFRACT)
		mclass = MODE_FRACT;
	      ಅನ್ಯಥಾ ಯದಿ (GET_MODE_CLASS (m1) == MODE_UACCUM)
		mclass = MODE_ACCUM;
	      ಅನ್ಯಥಾ
		gcc_unreachable ();
	      m1 = as_a <scalar_mode>
		(mode_for_size (GET_MODE_PRECISION (m1), mclass, 0));
	    }
	  ಯದಿ (code2 == FIXED_POINT_TYPE && TYPE_UNSIGNED (t2))
	    {
	      ಗಣನಾ mode_class mclass = (ಗಣನಾ mode_class) 0;
	      ಯದಿ (GET_MODE_CLASS (m2) == MODE_UFRACT)
		mclass = MODE_FRACT;
	      ಅನ್ಯಥಾ ಯದಿ (GET_MODE_CLASS (m2) == MODE_UACCUM)
		mclass = MODE_ACCUM;
	      ಅನ್ಯಥಾ
		gcc_unreachable ();
	      m2 = as_a <scalar_mode>
		(mode_for_size (GET_MODE_PRECISION (m2), mclass, 0));
	    }
	}

      ಯದಿ (code1 == FIXED_POINT_TYPE)
	{
	  fbit1 = GET_MODE_FBIT (m1);
	  ibit1 = GET_MODE_IBIT (m1);
	}
      ಅನ್ಯಥಾ
	{
	  fbit1 = 0;
	  /* Signed integers need to subtract one sign bit.  */
	  ibit1 = TYPE_PRECISION (t1) - (!TYPE_UNSIGNED (t1));
	}

      ಯದಿ (code2 == FIXED_POINT_TYPE)
	{
	  fbit2 = GET_MODE_FBIT (m2);
	  ibit2 = GET_MODE_IBIT (m2);
	}
      ಅನ್ಯಥಾ
	{
	  fbit2 = 0;
	  /* Signed integers need to subtract one sign bit.  */
	  ibit2 = TYPE_PRECISION (t2) - (!TYPE_UNSIGNED (t2));
	}

      max_ibit = ibit1 >= ibit2 ?  ibit1 : ibit2;
      max_fbit = fbit1 >= fbit2 ?  fbit1 : fbit2;
      ಪ್ರತ್ಯಾಗಮ c_common_fixed_point_type_for_size (max_ibit, max_fbit, unsignedp,
						 satp);
    }

  /* Both real or both integers; use the one with greater precision.  */

  ಯದಿ (TYPE_PRECISION (t1) > TYPE_PRECISION (t2))
    ಪ್ರತ್ಯಾಗಮ t1;
  ಅನ್ಯಥಾ ಯದಿ (TYPE_PRECISION (t2) > TYPE_PRECISION (t1))
    ಪ್ರತ್ಯಾಗಮ t2;

  /* Same precision.  Prefer long longs to longs to ints when the
     same precision, following the C99 rules on integer type rank
     (which are equivalent to the C90 rules for C90 types).  */

  ಯದಿ (TYPE_MAIN_VARIANT (t1) == long_long_unsigned_type_ಗಂಟು
      || TYPE_MAIN_VARIANT (t2) == long_long_unsigned_type_ಗಂಟು)
    ಪ್ರತ್ಯಾಗಮ long_long_unsigned_type_ಗಂಟು;

  ಯದಿ (TYPE_MAIN_VARIANT (t1) == long_long_integer_type_ಗಂಟು
      || TYPE_MAIN_VARIANT (t2) == long_long_integer_type_ಗಂಟು)
    {
      ಯದಿ (TYPE_UNSIGNED (t1) || TYPE_UNSIGNED (t2))
	ಪ್ರತ್ಯಾಗಮ long_long_unsigned_type_ಗಂಟು;
      ಅನ್ಯಥಾ
	ಪ್ರತ್ಯಾಗಮ long_long_integer_type_ಗಂಟು;
    }

  ಯದಿ (TYPE_MAIN_VARIANT (t1) == long_unsigned_type_ಗಂಟು
      || TYPE_MAIN_VARIANT (t2) == long_unsigned_type_ಗಂಟು)
    ಪ್ರತ್ಯಾಗಮ long_unsigned_type_ಗಂಟು;

  ಯದಿ (TYPE_MAIN_VARIANT (t1) == long_integer_type_ಗಂಟು
      || TYPE_MAIN_VARIANT (t2) == long_integer_type_ಗಂಟು)
    {
      /* But preserve unsignedness from the other type,
	 since long cannot hold all the values of an unsigned int.  */
      ಯದಿ (TYPE_UNSIGNED (t1) || TYPE_UNSIGNED (t2))
	ಪ್ರತ್ಯಾಗಮ long_unsigned_type_ಗಂಟು;
      ಅನ್ಯಥಾ
	ಪ್ರತ್ಯಾಗಮ long_integer_type_ಗಂಟು;
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
  ವೃಕ್ಷ mv1 = TYPE_MAIN_VARIANT (t1);
  ವೃಕ್ಷ mv2 = TYPE_MAIN_VARIANT (t2);

  ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = ಅಂಕೆ_FLOATN_TYPES - 1; i >= 0; i--)
    ಯದಿ (mv1 == FLOATN_TYPE_ಗಂಟು (i) || mv2 == FLOATN_TYPE_ಗಂಟು (i))
      ಪ್ರತ್ಯಾಗಮ FLOATN_TYPE_ಗಂಟು (i);

  /* Likewise, prefer long double to double even if same size.  */
  ಯದಿ (mv1 == long_double_type_ಗಂಟು || mv2 == long_double_type_ಗಂಟು)
    ಪ್ರತ್ಯಾಗಮ long_double_type_ಗಂಟು;

  /* Likewise, prefer double to float even if same size.
     We got a couple of embedded targets with 32 bit doubles, and the
     pdp11 might have 64 bit floats.  */
  ಯದಿ (mv1 == double_type_ಗಂಟು || mv2 == double_type_ಗಂಟು)
    ಪ್ರತ್ಯಾಗಮ double_type_ಗಂಟು;

  ಯದಿ (mv1 == float_type_ಗಂಟು || mv2 == float_type_ಗಂಟು)
    ಪ್ರತ್ಯಾಗಮ float_type_ಗಂಟು;

  ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = ಅಂಕೆ_FLOATNX_TYPES - 1; i >= 0; i--)
    ಯದಿ (mv1 == FLOATNX_TYPE_ಗಂಟು (i) || mv2 == FLOATNX_TYPE_ಗಂಟು (i))
      ಪ್ರತ್ಯಾಗಮ FLOATNX_TYPE_ಗಂಟು (i);

  ಯದಿ ((code1 == BITINT_TYPE || code2 == BITINT_TYPE) && code1 != code2)
    {
      /* Prefer any other integral types over bit-precise integer types.  */
      ಯದಿ (TYPE_UNSIGNED (t1) == TYPE_UNSIGNED (t2))
	ಪ್ರತ್ಯಾಗಮ code1 == BITINT_TYPE ? t2 : t1;
      /* If BITINT_TYPE is unsigned and the other type is signed
	 non-BITINT_TYPE with the same precision, the latter has higher rank.
	 In that case:
	 Otherwise, both operands are converted to the unsigned integer type
	 corresponding to the type of the operand with signed integer type.  */
      ಯದಿ (TYPE_UNSIGNED (code1 == BITINT_TYPE ? t1 : t2))
	ಪ್ರತ್ಯಾಗಮ c_common_unsigned_type (code1 == BITINT_TYPE ? t2 : t1);
    }

  /* Otherwise prefer the unsigned one.  */

  ಯದಿ (TYPE_UNSIGNED (t1))
    ಪ್ರತ್ಯಾಗಮ t1;
  ಅನ್ಯಥಾ
    ಪ್ರತ್ಯಾಗಮ t2;
}

/* Wrapper around c_common_type that is used by c-common.cc and other
   front end optimizations that remove promotions.  ENUMERAL_TYPEs
   are allowed here and are converted to their compatible integer types.
   BOOLEAN_TYPEs are allowed here and return either boolean_type_node or
   preferably a non-Boolean type as the common type.  */
ವೃಕ್ಷ
common_type (ವೃಕ್ಷ t1, ವೃಕ್ಷ t2)
{
  ಯದಿ (ವೃಕ್ಷ_CODE (t1) == ENUMERAL_TYPE)
    t1 = ENUM_UNDERLYING_TYPE (t1);
  ಯದಿ (ವೃಕ್ಷ_CODE (t2) == ENUMERAL_TYPE)
    t2 = ENUM_UNDERLYING_TYPE (t2);

  /* If both types are BOOLEAN_TYPE, then return boolean_type_node.  */
  ಯದಿ (ವೃಕ್ಷ_CODE (t1) == BOOLEAN_TYPE
      && ವೃಕ್ಷ_CODE (t2) == BOOLEAN_TYPE)
    ಪ್ರತ್ಯಾಗಮ boolean_type_ಗಂಟು;

  /* If either type is BOOLEAN_TYPE, then return the other.  */
  ಯದಿ (ವೃಕ್ಷ_CODE (t1) == BOOLEAN_TYPE)
    ಪ್ರತ್ಯಾಗಮ t2;
  ಯದಿ (ವೃಕ್ಷ_CODE (t2) == BOOLEAN_TYPE)
    ಪ್ರತ್ಯಾಗಮ t1;

  ಪ್ರತ್ಯಾಗಮ c_common_type (t1, t2);
}



/* Helper function for comptypes.  For two compatible types, return 1
   if they pass consistency checks.  In particular we test that
   TYPE_CANONICAL is set correctly, i.e. the two types can alias.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
comptypes_verify (ವೃಕ್ಷ type1, ವೃಕ್ಷ type2)
{
  ಯದಿ (type1 == type2 || !type1 || !type2
      || ವೃಕ್ಷ_CODE (type1) == ERROR_MARK || ವೃಕ್ಷ_CODE (type2) == ERROR_MARK)
    ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;

  gcc_checking_assert (c_verify_type (type1));
  gcc_checking_assert (c_verify_type (type2));

  ಯದಿ (TYPE_CANONICAL (type1) != TYPE_CANONICAL (type2)
      && !TYPE_STRUCTURAL_EQUALITY_P (type1)
      && !TYPE_STRUCTURAL_EQUALITY_P (type2))
    {
      /* FIXME: check other types. */
      ಯದಿ (RECORD_OR_UNION_TYPE_P (type1)
	  || ವೃಕ್ಷ_CODE (type1) == ENUMERAL_TYPE
	  || ವೃಕ್ಷ_CODE (type2) == ENUMERAL_TYPE)
	ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
    }
  ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
}

ಸಂರಚನಾ comptypes_data {

  /* output */
  ತಾರ್ಕಿಕ enum_and_int_p;
  ತಾರ್ಕಿಕ different_types_p;
  ತಾರ್ಕಿಕ warning_needed;

  /* context */
  ತಾರ್ಕಿಕ anon_field;
  ತಾರ್ಕಿಕ pointedto;

  /* configuration */
  ತಾರ್ಕಿಕ equiv;
  ತಾರ್ಕಿಕ ignore_promoting_args;

  ಧ್ರುವ ಸಂರಚನಾ tagged_tu_seen_cache* cache;
};


/* Helper function for composite_type.  This function ignores when the
   function type of an old-style declaration is incompatible with a type
   of a declaration with prototype because some are arguments are not
   self-promoting.  This is ignored only for function types but not
   ignored in a nested context.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
comptypes_check_for_composite (ವೃಕ್ಷ t1, ವೃಕ್ಷ t2)
{
  ಸಂರಚನಾ comptypes_data data = { };
  data.ignore_promoting_args = FUNCTION_TYPE == ವೃಕ್ಷ_CODE (t1);
  ಪ್ರತ್ಯಾಗಮ comptypes_internal (t1, t2, &data);
}


/* C implementation of compatible_types_for_indirection_note_p.  */

ತಾರ್ಕಿಕ
compatible_types_for_indirection_note_p (ವೃಕ್ಷ type1, ವೃಕ್ಷ type2)
{
  ಪ್ರತ್ಯಾಗಮ comptypes (type1, type2);
}

/* Return true if TYPE1 and TYPE2 are compatible types for assignment
   or various other operations.  */

ತಾರ್ಕಿಕ
comptypes (ವೃಕ್ಷ type1, ವೃಕ್ಷ type2)
{
  ಸಂರಚನಾ comptypes_data data = { };
  ತಾರ್ಕಿಕ ret = comptypes_internal (type1, type2, &data);

  gcc_checking_assert (!ret || comptypes_verify (type1, type2));

  ಪ್ರತ್ಯಾಗಮ ret;
}


/* Like comptypes, but it returns non-zero only for identical
   types.  */

ತಾರ್ಕಿಕ
comptypes_same_p (ವೃಕ್ಷ type1, ವೃಕ್ಷ type2)
{
  ಸಂರಚನಾ comptypes_data data = { };
  ತಾರ್ಕಿಕ ret = comptypes_internal (type1, type2, &data);

  gcc_checking_assert (!ret || comptypes_verify (type1, type2));

  ಯದಿ (data.different_types_p)
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

  ಪ್ರತ್ಯಾಗಮ ret;
}


/* Like comptypes, but if it returns true because enum and int are
   compatible, it sets *ENUM_AND_INT_P to true.  */

ತಾರ್ಕಿಕ
comptypes_check_enum_int (ವೃಕ್ಷ type1, ವೃಕ್ಷ type2, ತಾರ್ಕಿಕ *enum_and_int_p)
{
  ಸಂರಚನಾ comptypes_data data = { };
  ತಾರ್ಕಿಕ ret = comptypes_internal (type1, type2, &data);
  *enum_and_int_p = data.enum_and_int_p;

  gcc_checking_assert (!ret || comptypes_verify (type1, type2));

  ಪ್ರತ್ಯಾಗಮ ret;
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

ತಾರ್ಕಿಕ
comptypes_equiv_p (ವೃಕ್ಷ type1, ವೃಕ್ಷ type2)
{
  ಸಂರಚನಾ comptypes_data data = { };
  data.equiv = ಸತ್ಯ;
  ತಾರ್ಕಿಕ ret = comptypes_internal (type1, type2, &data);

  /* check that different equivance classes are assigned only
     to types that are not compatible.  */
  gcc_checking_assert (ret || !comptypes (type1, type2));

  ಪ್ರತ್ಯಾಗಮ ret;
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

ಸ್ಥಿರ ತಾರ್ಕಿಕ
comptypes_internal (const_ವೃಕ್ಷ type1, const_ವೃಕ್ಷ type2,
		    ಸಂರಚನಾ comptypes_data *data)
{
  const_ವೃಕ್ಷ t1 = type1;
  const_ವೃಕ್ಷ t2 = type2;

  /* Suppress errors caused by previously reported errors.  */

  ಯದಿ (t1 == t2 || !t1 || !t2
      || ವೃಕ್ಷ_CODE (t1) == ERROR_MARK || ವೃಕ್ಷ_CODE (t2) == ERROR_MARK)
    ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;

  /* Qualifiers must match. C99 6.7.3p9 */

  ಯದಿ (TYPE_QUALS (t1) != TYPE_QUALS (t2))
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

  /* Enumerated types are compatible with integer types, but this is
     not transitive: two enumerated types in the same translation unit
     are compatible with each other only if they are the same type.  */

  ಯದಿ (ವೃಕ್ಷ_CODE (t1) == ENUMERAL_TYPE
      && COMPLETE_TYPE_P (t1)
      && ವೃಕ್ಷ_CODE (t2) != ENUMERAL_TYPE)
    {
      t1 = ENUM_UNDERLYING_TYPE (t1);
      ಯದಿ (ವೃಕ್ಷ_CODE (t2) != VOID_TYPE)
	{
	  data->enum_and_int_p = ಸತ್ಯ;
	  data->different_types_p = ಸತ್ಯ;
	}
    }
  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (t2) == ENUMERAL_TYPE
	   && COMPLETE_TYPE_P (t2)
	   && ವೃಕ್ಷ_CODE (t1) != ENUMERAL_TYPE)
    {
      t2 = ENUM_UNDERLYING_TYPE (t2);
      ಯದಿ (ವೃಕ್ಷ_CODE (t1) != VOID_TYPE)
	{
	  data->enum_and_int_p = ಸತ್ಯ;
	  data->different_types_p = ಸತ್ಯ;
	}
    }

  ಯದಿ (t1 == t2)
    ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;

  /* Different classes of types can't be compatible.  */

  ಯದಿ (ವೃಕ್ಷ_CODE (t1) != ವೃಕ್ಷ_CODE (t2))
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

  /* Allow for two different type nodes which have essentially the same
     definition.  Note that we already checked for equality of the type
     qualifiers (just above).  */

  ಯದಿ (ವೃಕ್ಷ_CODE (t1) != ARRAY_TYPE
      && TYPE_MAIN_VARIANT (t1) == TYPE_MAIN_VARIANT (t2))
    ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;

  ಪೂರ್ಣಾಙ್ಕ attrval;

  /* 1 if no need for warning yet, 2 if warning cause has been seen.  */
  ಯದಿ (!(attrval = comp_type_attributes (t1, t2)))
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

  ಯದಿ (2 == attrval)
    data->warning_needed = ಸತ್ಯ;

  ವಿಕಲ್ಪ (ವೃಕ್ಷ_CODE (t1))
    {
    ಪಕ್ಷ INTEGER_TYPE:
    ಪಕ್ಷ FIXED_POINT_TYPE:
    ಪಕ್ಷ REAL_TYPE:
    ಪಕ್ಷ BITINT_TYPE:
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
      ಪ್ರತ್ಯಾಗಮ TYPE_CANONICAL (t1) == TYPE_CANONICAL (t2);

    ಪಕ್ಷ POINTER_TYPE:
      /* Do not remove mode information.  */
      ಯದಿ (TYPE_MODE (t1) != TYPE_MODE (t2))
	ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
      data->pointedto = ಸತ್ಯ;
      ಪ್ರತ್ಯಾಗಮ comptypes_internal (ವೃಕ್ಷ_TYPE (t1), ವೃಕ್ಷ_TYPE (t2), data);

    ಪಕ್ಷ FUNCTION_TYPE:
      ಪ್ರತ್ಯಾಗಮ function_types_compatible_p (t1, t2, data);

    ಪಕ್ಷ ARRAY_TYPE:
      {
	ವೃಕ್ಷ d1 = TYPE_DOMAIN (t1);
	ವೃಕ್ಷ d2 = TYPE_DOMAIN (t2);

	/* Target types must match incl. qualifiers.  */
	ಯದಿ (!comptypes_internal (ವೃಕ್ಷ_TYPE (t1), ವೃಕ್ಷ_TYPE (t2), data))
	  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

	ಯದಿ ((d1 == NULL_ವೃಕ್ಷ) != (d2 == NULL_ವೃಕ್ಷ))
	  data->different_types_p = ಸತ್ಯ;
	/* Ignore size mismatches when forming equivalence classes.  */
	ಯದಿ (data->equiv)
	  ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
	/* Sizes must match unless one is missing or variable.  */
	ಯದಿ (d1 == NULL_ವೃಕ್ಷ || d2 == NULL_ವೃಕ್ಷ || d1 == d2)
	  ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;

	ತಾರ್ಕಿಕ d1_variable = ತುದಿ_array_vla_p (t1);
	ತಾರ್ಕಿಕ d2_variable = ತುದಿ_array_vla_p (t2);

	ಯದಿ (d1_variable != d2_variable)
	  data->different_types_p = ಸತ್ಯ;
	ಯದಿ (d1_variable || d2_variable)
	  ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;

	ತಾರ್ಕಿಕ d1_zero = zero_length_array_type_p (t1)
		       || flexible_array_member_type_p (t1);

	ತಾರ್ಕಿಕ d2_zero = zero_length_array_type_p (t2)
		       || flexible_array_member_type_p (t2);

	ಯದಿ (d1_zero && d2_zero)
	  ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
	ಯದಿ (d1_zero || d2_zero)
	  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

	ಯದಿ (!ವೃಕ್ಷ_int_cst_equal (TYPE_MIN_ಮೌಲ್ಯ (d1), TYPE_MIN_ಮೌಲ್ಯ (d2))
	    || !ವೃಕ್ಷ_int_cst_equal (TYPE_MAX_ಮೌಲ್ಯ (d1), TYPE_MAX_ಮೌಲ್ಯ (d2)))
	  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

	ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
      }

    ಪಕ್ಷ ENUMERAL_TYPE:
    ಪಕ್ಷ RECORD_TYPE:
    ಪಕ್ಷ UNION_TYPE:

      ಯದಿ (!flag_isoc23)
	ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

      ಪ್ರತ್ಯಾಗಮ tagged_types_tu_compatible_p (t1, t2, data);

    ಪಕ್ಷ VECTOR_TYPE:
      ಪ್ರತ್ಯಾಗಮ known_eq (TYPE_VECTOR_SUBPARTS (t1), TYPE_VECTOR_SUBPARTS (t2))
	     && comptypes_internal (ವೃಕ್ಷ_TYPE (t1), ವೃಕ್ಷ_TYPE (t2), data);

    ಸ್ವಭಾವ:
      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
    }
  gcc_unreachable ();
}

/* Return true if TTL and TTR are pointers to types that are equivalent, ignoring
   their qualifiers, except for named address spaces.  If the pointers point to
   different named addresses, then we must determine if one address space is a
   subset of the other.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
comp_target_types (location_t location, ವೃಕ್ಷ ttl, ವೃಕ್ಷ ttr)
{
  ವೃಕ್ಷ mvl = ವೃಕ್ಷ_TYPE (ttl);
  ವೃಕ್ಷ mvr = ವೃಕ್ಷ_TYPE (ttr);
  addr_space_t asl = TYPE_ADDR_SPACE (mvl);
  addr_space_t asr = TYPE_ADDR_SPACE (mvr);
  addr_space_t as_common;

  /* Fail if pointers point to incompatible address spaces.  */
  ಯದಿ (!addr_space_superset (asl, asr, &as_common))
    ಪ್ರತ್ಯಾಗಮ 0;

  /* Qualifiers on element types of array types that are
     pointer targets are also removed.  */
  ಸಂರಚನಾ comptypes_data data = { };
  ಯದಿ (!comptypes_internal (remove_qualifiers (mvl),
			   remove_qualifiers (mvr), &data))
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

  /* For pedantic use comptypes on arrays before removing
     qualifiers on the element type. */
  ಯದಿ (ವೃಕ್ಷ_CODE (mvl) == ARRAY_TYPE
      && ವೃಕ್ಷ_CODE (mvr) == ARRAY_TYPE
      && !comptypes (mvl, mvr))
    pedwarn_c11 (location, OPT_Wpedantic, "invalid use of pointers to arrays "
					  "with different qualifiers in ISO C "
					  "before C23");

  ಯದಿ (data.warning_needed)
    pedwarn (location, OPT_Wpedantic, "types are not quite compatible");

  ಯದಿ (data.enum_and_int_p && warn_cxx_compat)
    warning_at (location, OPT_Wc___compat,
		"pointer target types incompatible in C++");

  ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
}

/* Subroutines of `comptypes'.  */

/* Return true if two 'struct', 'union', or 'enum' types T1 and T2 are
   compatible.  The two types are not the same (which has been
   checked earlier in comptypes_internal).  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
tagged_types_tu_compatible_p (const_ವೃಕ್ಷ t1, const_ವೃಕ್ಷ t2,
			      ಸಂರಚನಾ comptypes_data *data)
{
  ವೃಕ್ಷ s1, s2;

  ಯದಿ (c_type_tag (t1) != c_type_tag (t2))
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

  /* When forming equivalence classes for TYPE_CANONICAL in C23, we treat
     structs with the same tag as equivalent, but only when they are targets
     of pointers inside other structs.  */
  ಯದಿ (data->equiv && data->pointedto && NULL_ವೃಕ್ಷ != c_type_tag (t1))
    ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;

  /* Different types without tag are incompatible except as an anonymous
     field or when forming equivalence classes for TYPE_CANONICAL.  */
  ಯದಿ (!data->anon_field && !data->equiv && NULL_ವೃಕ್ಷ == c_type_tag (t1))
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

  ಯದಿ (!data->anon_field && TYPE_STUB_DECL (t1) != TYPE_STUB_DECL (t2))
    data->different_types_p = ಸತ್ಯ;

  /* Incomplete types are incompatible inside a TU.  */
  ಯದಿ (TYPE_SIZE (t1) == ರಿಕ್ತ || TYPE_SIZE (t2) == ರಿಕ್ತ)
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

  ಯದಿ (ENUMERAL_TYPE != ವೃಕ್ಷ_CODE (t1)
      && (TYPE_REVERSE_STORAGE_ORDER (t1)
	  != TYPE_REVERSE_STORAGE_ORDER (t2)))
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

  ಯದಿ (TYPE_USER_ALIGN (t1) != TYPE_USER_ALIGN (t2))
    data->different_types_p = ಸತ್ಯ;

  /* For types already being looked at in some active
     invocation of this function, assume compatibility.
     The cache is built as a linked list on the stack
     with the head of the list passed downwards.  */
  ಪ್ರತಿ (ಧ್ರುವ ಸಂರಚನಾ tagged_tu_seen_cache *t = data->cache;
       t != ರಿಕ್ತ; t = t->next)
    ಯದಿ (t->t1 == t1 && t->t2 == t2)
      ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;

  ಧ್ರುವ ಸಂರಚನಾ tagged_tu_seen_cache entry = { data->cache, t1, t2 };

  ವಿಕಲ್ಪ (ವೃಕ್ಷ_CODE (t1))
    {
    ಪಕ್ಷ ENUMERAL_TYPE:
      {
	ಯದಿ (!comptypes (ENUM_UNDERLYING_TYPE (t1), ENUM_UNDERLYING_TYPE (t2)))
	  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

	/* Speed up the case where the type values are in the same order.  */
	ವೃಕ್ಷ tv1 = TYPE_ಮೌಲ್ಯಗಳು (t1);
	ವೃಕ್ಷ tv2 = TYPE_ಮೌಲ್ಯಗಳು (t2);

	ಯದಿ (tv1 == tv2)
	  ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;

	ಪ್ರತಿ (;tv1 && tv2; tv1 = ವೃಕ್ಷ_CHAIN (tv1), tv2 = ವೃಕ್ಷ_CHAIN (tv2))
	  {
	    ಯದಿ (ವೃಕ್ಷ_PURPOSE (tv1) != ವೃಕ್ಷ_PURPOSE (tv2))
	      ಭಙ್ಗ;

	    ಯದಿ (simple_cst_equal (DECL_INITIAL (ವೃಕ್ಷ_ಮೌಲ್ಯ (tv1)),
				  DECL_INITIAL (ವೃಕ್ಷ_ಮೌಲ್ಯ (tv2))) != 1)
	      ಭಙ್ಗ;
	  }

	ಯದಿ (tv1 == NULL_ವೃಕ್ಷ && tv2 == NULL_ವೃಕ್ಷ)
	  ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;

	ಯದಿ (tv1 == NULL_ವೃಕ್ಷ || tv2 == NULL_ವೃಕ್ಷ)
	  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

	ಯದಿ (list_length (TYPE_ಮೌಲ್ಯಗಳು (t1)) != list_length (TYPE_ಮೌಲ್ಯಗಳು (t2)))
	  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

	ಪ್ರತಿ (s1 = TYPE_ಮೌಲ್ಯಗಳು (t1); s1; s1 = ವೃಕ್ಷ_CHAIN (s1))
	  {
	    s2 = purpose_member (ವೃಕ್ಷ_PURPOSE (s1), TYPE_ಮೌಲ್ಯಗಳು (t2));

	    ಯದಿ (s2 == ರಿಕ್ತ
		|| simple_cst_equal (DECL_INITIAL (ವೃಕ್ಷ_ಮೌಲ್ಯ (s1)),
				     DECL_INITIAL (ವೃಕ್ಷ_ಮೌಲ್ಯ (s2))) != 1)
	      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	  }

	ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
      }

    ಪಕ್ಷ UNION_TYPE:
    ಪಕ್ಷ RECORD_TYPE:

	ಯದಿ (list_length (TYPE_FIELDS (t1)) != list_length (TYPE_FIELDS (t2)))
	  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

	ಪ್ರತಿ (s1 = TYPE_FIELDS (t1), s2 = TYPE_FIELDS (t2);
	     s1 && s2;
	     s1 = DECL_CHAIN (s1), s2 = DECL_CHAIN (s2))
	  {
	    gcc_assert (ವೃಕ್ಷ_CODE (s1) == FIELD_DECL);
	    gcc_assert (ವೃಕ್ಷ_CODE (s2) == FIELD_DECL);

	    ವೃಕ್ಷ ft1 = ವೃಕ್ಷ_TYPE (s1);
	    ವೃಕ್ಷ ft2 = ವೃಕ್ಷ_TYPE (s2);

	    ಯದಿ (DECL_NAME (s1) != DECL_NAME (s2))
	      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

	    ಯದಿ (DECL_ALIGN (s1) != DECL_ALIGN (s2))
	      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

	    ಯದಿ (DECL_C_BIT_FIELD (s1) != DECL_C_BIT_FIELD (s2))
	       ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

	    ಯದಿ (DECL_C_BIT_FIELD (s1))
	      {
		ಯದಿ (!ವೃಕ್ಷ_int_cst_equal (DECL_SIZE (s1), DECL_SIZE (s2)))
		  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

		ft1 = DECL_BIT_FIELD_TYPE (s1);
		ft2 = DECL_BIT_FIELD_TYPE (s2);
	      }

	    ಯದಿ (!ft1 || !ft2)
	      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

	    ಯದಿ (ವೃಕ್ಷ_CODE (ft1) == ERROR_MARK || ವೃಕ್ಷ_CODE (ft2) == ERROR_MARK)
	      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

	    data->anon_field = !DECL_NAME (s1);
	    data->pointedto = ಅಸತ್ಯ;

	    ಧ್ರುವ ಸಂರಚನಾ tagged_tu_seen_cache *cache = data->cache;
	    data->cache = &entry;
	    ತಾರ್ಕಿಕ ret = comptypes_internal (ft1, ft2, data);
	    data->cache = cache;
	    ಯದಿ (!ret)
	      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

	    ವೃಕ್ಷ st1 = TYPE_SIZE (ವೃಕ್ಷ_TYPE (s1));
	    ವೃಕ್ಷ st2 = TYPE_SIZE (ವೃಕ್ಷ_TYPE (s2));

	    ಯದಿ (data->equiv
		&& st1 && ವೃಕ್ಷ_CODE (st1) == INTEGER_CST
		&& st2 && ವೃಕ್ಷ_CODE (st2) == INTEGER_CST
		&& !ವೃಕ್ಷ_int_cst_equal (st1, st2))
	     ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

	    ವೃಕ್ಷ counted_by1 = lookup_attribute ("counted_by",
						 DECL_ATTRIBUTES (s1));
	    ವೃಕ್ಷ counted_by2 = lookup_attribute ("counted_by",
						 DECL_ATTRIBUTES (s2));
	    /* If there is no counted_by attribute for both fields.  */
	    ಯದಿ (!counted_by1 && !counted_by2)
	      ಅನುವರ್ತ;

	    /* If only one field has counted_by attribute.  */
	    ಯದಿ ((counted_by1 && !counted_by2)
		|| (!counted_by1 && counted_by2))
	      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

	    /* Now both s1 and s2 have counted_by attributes, check
	       whether they are the same.  */

	    ವೃಕ್ಷ counted_by_field1
	      = lookup_field (t1, ವೃಕ್ಷ_ಮೌಲ್ಯ (ವೃಕ್ಷ_ಮೌಲ್ಯ (counted_by1)));
	    ವೃಕ್ಷ counted_by_field2
	      = lookup_field (t2, ವೃಕ್ಷ_ಮೌಲ್ಯ (ವೃಕ್ಷ_ಮೌಲ್ಯ (counted_by2)));

	    gcc_assert (counted_by_field1 && counted_by_field2);

	    ಯಾವತ್ (ವೃಕ್ಷ_CHAIN (counted_by_field1))
	      counted_by_field1 = ವೃಕ್ಷ_CHAIN (counted_by_field1);
	    ಯಾವತ್ (ವೃಕ್ಷ_CHAIN (counted_by_field2))
	      counted_by_field2 = ವೃಕ್ಷ_CHAIN (counted_by_field2);

	    ಯದಿ (DECL_NAME (ವೃಕ್ಷ_ಮೌಲ್ಯ (counted_by_field1))
		!= DECL_NAME (ವೃಕ್ಷ_ಮೌಲ್ಯ (counted_by_field2)))
	      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	  }
	ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;

    ಸ್ವಭಾವ:
      gcc_unreachable ();
    }
}

/* Return true if two function types F1 and F2 are compatible.
   If either type specifies no argument types,
   the other must specify a fixed number of self-promoting arg types.
   Otherwise, if one type specifies only the number of arguments,
   the other must specify that number of self-promoting arg types.
   Otherwise, the argument types must match.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
function_types_compatible_p (const_ವೃಕ್ಷ f1, const_ವೃಕ್ಷ f2,
			     ಸಂರಚನಾ comptypes_data *data)
{
  ವೃಕ್ಷ ret1 = ವೃಕ್ಷ_TYPE (f1);
  ವೃಕ್ಷ ret2 = ವೃಕ್ಷ_TYPE (f2);

  /* 'volatile' qualifiers on a function's return type used to mean
     the function is noreturn.  */
  ಯದಿ (TYPE_VOLATILE (ret1) != TYPE_VOLATILE (ret2))
    pedwarn (ಒಳಹರಿವು_location, 0, "function return types not compatible due to %<volatile%>");
  ಯದಿ (TYPE_VOLATILE (ret1))
    ret1 = build_qualified_type (TYPE_MAIN_VARIANT (ret1),
				 TYPE_QUALS (ret1) & ~TYPE_QUAL_VOLATILE);
  ಯದಿ (TYPE_VOLATILE (ret2))
    ret2 = build_qualified_type (TYPE_MAIN_VARIANT (ret2),
				 TYPE_QUALS (ret2) & ~TYPE_QUAL_VOLATILE);

  ತಾರ್ಕಿಕ ignore_pargs = data->ignore_promoting_args;
  data->ignore_promoting_args = ಅಸತ್ಯ;

  ಯದಿ (!comptypes_internal (ret1, ret2, data))
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

  data->ignore_promoting_args = ignore_pargs;

  ವೃಕ್ಷ args1 = TYPE_ARG_TYPES (f1);
  ವೃಕ್ಷ args2 = TYPE_ARG_TYPES (f2);

  ಯದಿ ((args1 == NULL_ವೃಕ್ಷ) != (args2 == NULL_ವೃಕ್ಷ))
    data->different_types_p = ಸತ್ಯ;

  /* An unspecified parmlist matches any specified parmlist
     whose argument types don't need default promotions.  */

  ಯದಿ (args1 == NULL_ವೃಕ್ಷ)
    {
      ಯದಿ (TYPE_NO_NAMED_ARGS_STDARG_P (f1) != TYPE_NO_NAMED_ARGS_STDARG_P (f2))
	ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
      ಯದಿ (!(data->ignore_promoting_args || self_promoting_args_p (args2)))
	ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
      data->ignore_promoting_args = ಅಸತ್ಯ;
      /* If one of these types comes from a non-prototype fn definition,
	 compare that with the other type's arglist.
	 If they don't match, ask for a warning (but no error).  */
      ಯದಿ (TYPE_ACTUAL_ARG_TYPES (f1)
	  && !type_lists_compatible_p (args2, TYPE_ACTUAL_ARG_TYPES (f1), data))
	 data->warning_needed = ಸತ್ಯ;
      ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
    }
  ಯದಿ (args2 == NULL_ವೃಕ್ಷ)
    {
      ಯದಿ (TYPE_NO_NAMED_ARGS_STDARG_P (f1) != TYPE_NO_NAMED_ARGS_STDARG_P (f2))
	ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
      ಯದಿ (!(data->ignore_promoting_args || self_promoting_args_p (args1)))
	ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
      data->ignore_promoting_args = ಅಸತ್ಯ;
      ಯದಿ (TYPE_ACTUAL_ARG_TYPES (f2)
	  && !type_lists_compatible_p (args1, TYPE_ACTUAL_ARG_TYPES (f2), data))
	data->warning_needed = ಸತ್ಯ;
      ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
    }

  /* Both types have argument lists: compare them and propagate results.  */
  ಪ್ರತ್ಯಾಗಮ type_lists_compatible_p (args1, args2, data);
}

/* Check two lists of types for compatibility, returning false for
   incompatible, true for compatible.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
type_lists_compatible_p (const_ವೃಕ್ಷ args1, const_ವೃಕ್ಷ args2,
			 ಸಂರಚನಾ comptypes_data *data)
{
  ಯಾವತ್ (1)
    {
      ಯದಿ (args1 == NULL_ವೃಕ್ಷ && args2 == NULL_ವೃಕ್ಷ)
	ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
      /* If one list is shorter than the other,
	 they fail to match.  */
      ಯದಿ (args1 == NULL_ವೃಕ್ಷ || args2 == NULL_ವೃಕ್ಷ)
	ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
      ವೃಕ್ಷ a1 = ವೃಕ್ಷ_ಮೌಲ್ಯ (args1);
      ವೃಕ್ಷ a2 = ವೃಕ್ಷ_ಮೌಲ್ಯ (args2);
      ವೃಕ್ಷ mv1 = remove_qualifiers (a1);
      ವೃಕ್ಷ mv2 = remove_qualifiers (a2);

      gcc_assert (mv2);
      gcc_assert (mv2);

      /* If one of the lists has an error marker, ignore this arg.  */
      ಯದಿ (ವೃಕ್ಷ_CODE (a1) == ERROR_MARK
	       || ವೃಕ್ಷ_CODE (a2) == ERROR_MARK)
	;
      ಅನ್ಯಥಾ ಯದಿ (!comptypes_internal (mv1, mv2, data))
	{
	  data->different_types_p = ಸತ್ಯ;
	  /* Allow  wait (union {union wait *u; int *i} *)
	     and  wait (union wait *)  to be compatible.  */
	  ಯದಿ (ವೃಕ್ಷ_CODE (a1) == UNION_TYPE
	      && (TYPE_NAME (a1) == NULL_ವೃಕ್ಷ
		  || TYPE_TRANSPARENT_AGGR (a1))
	      && ವೃಕ್ಷ_CODE (TYPE_SIZE (a1)) == INTEGER_CST
	      && ವೃಕ್ಷ_int_cst_equal (TYPE_SIZE (a1),
				     TYPE_SIZE (a2)))
	    {
	      ವೃಕ್ಷ memb;
	      ಪ್ರತಿ (memb = TYPE_FIELDS (a1);
		   memb; memb = DECL_CHAIN (memb))
		{
		  ವೃಕ್ಷ mv3 = remove_qualifiers (ವೃಕ್ಷ_TYPE (memb));
		  ಯದಿ (comptypes_internal (mv3, mv2, data))
		    ಭಙ್ಗ;
		}
	      ಯದಿ (memb == NULL_ವೃಕ್ಷ)
		ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	    }
	  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (a2) == UNION_TYPE
		   && (TYPE_NAME (a2) == NULL_ವೃಕ್ಷ
		       || TYPE_TRANSPARENT_AGGR (a2))
		   && ವೃಕ್ಷ_CODE (TYPE_SIZE (a2)) == INTEGER_CST
		   && ವೃಕ್ಷ_int_cst_equal (TYPE_SIZE (a2),
					  TYPE_SIZE (a1)))
	    {
	      ವೃಕ್ಷ memb;
	      ಪ್ರತಿ (memb = TYPE_FIELDS (a2);
		   memb; memb = DECL_CHAIN (memb))
		{
		  ವೃಕ್ಷ mv3 = remove_qualifiers (ವೃಕ್ಷ_TYPE (memb));
		  ಯದಿ (comptypes_internal (mv3, mv1, data))
		    ಭಙ್ಗ;
		}
	      ಯದಿ (memb == NULL_ವೃಕ್ಷ)
		ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	    }
	  ಅನ್ಯಥಾ
	    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	}

      args1 = ವೃಕ್ಷ_CHAIN (args1);
      args2 = ವೃಕ್ಷ_CHAIN (args2);
    }
}

/* Compute the size to increment a pointer by.  When a function type or void
   type or incomplete type is passed, size_one_node is returned.
   This function does not emit any diagnostics; the caller is responsible
   for that.  */

ಸ್ಥಿರ ವೃಕ್ಷ
c_size_in_bytes (const_ವೃಕ್ಷ type)
{
  ಗಣನಾ ವೃಕ್ಷ_code code = ವೃಕ್ಷ_CODE (type);

  ಯದಿ (code == FUNCTION_TYPE || code == VOID_TYPE || code == ERROR_MARK
      || !COMPLETE_TYPE_P (type))
    ಪ್ರತ್ಯಾಗಮ size_one_ಗಂಟು;

  /* Convert in case a char is more than one unit.  */
  ಪ್ರತ್ಯಾಗಮ size_binop_loc (ಒಳಹರಿವು_location, CEIL_DIV_ಅಭಿವ್ಯಕ್ತಿ, TYPE_SIZE_UNIT (type),
			 size_int (TYPE_PRECISION (char_type_ಗಂಟು)
				   / BITS_PER_UNIT));
}

/* Return either DECL or its known constant value (if it has one).  */

ವೃಕ್ಷ
decl_constant_ಮೌಲ್ಯ_1 (ವೃಕ್ಷ decl, ತಾರ್ಕಿಕ in_init)
{
  ಯದಿ (/* Note that DECL_INITIAL isn't valid for a PARM_DECL.  */
      ವೃಕ್ಷ_CODE (decl) != PARM_DECL
      && !ವೃಕ್ಷ_THIS_VOLATILE (decl)
      && ವೃಕ್ಷ_READONLY (decl)
      && DECL_INITIAL (decl) != NULL_ವೃಕ್ಷ
      && !error_operand_p (DECL_INITIAL (decl))
      /* This is invalid if initial value is not constant.
	 If it has either a function call, a memory reference,
	 or a variable, then re-evaluating it could give different results.  */
      && ವೃಕ್ಷ_CONSTANT (DECL_INITIAL (decl))
      /* Check for cases where this is sub-optimal, even though valid.  */
      && (in_init || ವೃಕ್ಷ_CODE (DECL_INITIAL (decl)) != CONSTRUCTOR))
    ಪ್ರತ್ಯಾಗಮ DECL_INITIAL (decl);
  ಪ್ರತ್ಯಾಗಮ decl;
}

/* Return either DECL or its known constant value (if it has one).
   Like the above, but always return decl outside of functions.  */

ವೃಕ್ಷ
decl_constant_ಮೌಲ್ಯ (ವೃಕ್ಷ decl)
{
  /* Don't change a variable array bound or initial value to a constant
     in a place where a variable is invalid.  */
  ಪ್ರತ್ಯಾಗಮ current_function_decl ? decl_constant_ಮೌಲ್ಯ_1 (decl, ಅಸತ್ಯ) : decl;
}

/* Convert the array expression EXP to a pointer.  */
ಸ್ಥಿರ ವೃಕ್ಷ
array_to_pointer_conversion (location_t loc, ವೃಕ್ಷ exp)
{
  ವೃಕ್ಷ orig_exp = exp;
  ವೃಕ್ಷ type = ವೃಕ್ಷ_TYPE (exp);
  ವೃಕ್ಷ adr;
  ವೃಕ್ಷ restype = ವೃಕ್ಷ_TYPE (type);
  ವೃಕ್ಷ ptrtype;

  gcc_assert (ವೃಕ್ಷ_CODE (type) == ARRAY_TYPE);

  STRIP_TYPE_NOPS (exp);

  copy_warning (exp, orig_exp);

  ptrtype = c_build_pointer_type (restype);

  ಯದಿ (INDIRECT_REF_P (exp))
    ಪ್ರತ್ಯಾಗಮ convert (ptrtype, ವೃಕ್ಷ_OPERAND (exp, 0));

  /* In C++ array compound literals are temporary objects unless they are
     const or appear in namespace scope, so they are destroyed too soon
     to use them for much of anything  (c++/53220).  */
  ಯದಿ (warn_cxx_compat && ವೃಕ್ಷ_CODE (exp) == COMPOUND_LITERAL_ಅಭಿವ್ಯಕ್ತಿ)
    {
      ವೃಕ್ಷ decl = ವೃಕ್ಷ_OPERAND (ವೃಕ್ಷ_OPERAND (exp, 0), 0);
      ಯದಿ (!ವೃಕ್ಷ_READONLY (decl) && !ವೃಕ್ಷ_STATIC (decl))
	warning_at (DECL_SOURCE_LOCATION (decl), OPT_Wc___compat,
		    "converting an array compound literal to a pointer "
		    "leads to a dangling pointer in C++");
    }

  adr = build_unary_op (loc, ADDR_ಅಭಿವ್ಯಕ್ತಿ, exp, ಸತ್ಯ);
  ಪ್ರತ್ಯಾಗಮ convert (ptrtype, adr);
}

/* Convert the function expression EXP to a pointer.  */
ಸ್ಥಿರ ವೃಕ್ಷ
function_to_pointer_conversion (location_t loc, ವೃಕ್ಷ exp)
{
  ವೃಕ್ಷ orig_exp = exp;

  gcc_assert (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (exp)) == FUNCTION_TYPE);

  STRIP_TYPE_NOPS (exp);

  copy_warning (exp, orig_exp);

  ವೃಕ್ಷ exp2 = build_unary_op (loc, ADDR_ಅಭಿವ್ಯಕ್ತಿ, exp, ಅಸತ್ಯ);

  /* If the function is defined and known to not require a non-local
     context, make sure no trampoline is generated.  */
  ಯದಿ (ವೃಕ್ಷ_CODE (exp) == FUNCTION_DECL
      && DECL_INITIAL (exp) && !C_FUNC_NONLOCAL_CONTEXT (exp))
   ವೃಕ್ಷ_NO_TRAMPOLINE (exp2) = 1;

  ಪ್ರತ್ಯಾಗಮ exp2;
}

/* Mark EXP as read, not just set, for set but not used -Wunused
   warning purposes.  */

ಶೂನ್ಯ
mark_exp_read (ವೃಕ್ಷ exp)
{
  ವಿಕಲ್ಪ (ವೃಕ್ಷ_CODE (exp))
    {
    ಪಕ್ಷ VAR_DECL:
    ಪಕ್ಷ PARM_DECL:
      DECL_READ_P (exp) = 1;
      ಭಙ್ಗ;
    CASE_CONVERT:
      ಯದಿ (VOID_TYPE_P (ವೃಕ್ಷ_TYPE (exp)))
	ವಿಕಲ್ಪ (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_OPERAND (exp, 0)))
	  {
	  ಪಕ್ಷ PREINCREMENT_ಅಭಿವ್ಯಕ್ತಿ:
	  ಪಕ್ಷ PREDECREMENT_ಅಭಿವ್ಯಕ್ತಿ:
	  ಪಕ್ಷ POSTINCREMENT_ಅಭಿವ್ಯಕ್ತಿ:
	  ಪಕ್ಷ POSTDECREMENT_ಅಭಿವ್ಯಕ್ತಿ:
	    ಪ್ರತ್ಯಾಗಮ;
	  ಸ್ವಭಾವ:
	    ಭಙ್ಗ;
	  }
      /* FALLTHRU */
    ಪಕ್ಷ ARRAY_REF:
    ಪಕ್ಷ COMPONENT_REF:
    ಪಕ್ಷ MODIFY_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ REALPART_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ IMAGPART_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ ADDR_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ VIEW_CONVERT_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ PREINCREMENT_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ PREDECREMENT_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ POSTINCREMENT_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ POSTDECREMENT_ಅಭಿವ್ಯಕ್ತಿ:
      mark_exp_read (ವೃಕ್ಷ_OPERAND (exp, 0));
      ಭಙ್ಗ;
    ಪಕ್ಷ COMPOUND_ಅಭಿವ್ಯಕ್ತಿ:
      /* Pattern match what build_atomic_assign produces with modifycode
	 NOP_EXPR.  */
      ಯದಿ (VAR_P (ವೃಕ್ಷ_OPERAND (exp, 1))
	  && DECL_ARTIFICIAL (ವೃಕ್ಷ_OPERAND (exp, 1))
	  && ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_OPERAND (exp, 0)) == COMPOUND_ಅಭಿವ್ಯಕ್ತಿ)
	{
	  ವೃಕ್ಷ t1 = ವೃಕ್ಷ_OPERAND (ವೃಕ್ಷ_OPERAND (exp, 0), 0);
	  ವೃಕ್ಷ t2 = ವೃಕ್ಷ_OPERAND (ವೃಕ್ಷ_OPERAND (exp, 0), 1);
	  ಯದಿ (ವೃಕ್ಷ_CODE (t1) == TARGET_ಅಭಿವ್ಯಕ್ತಿ
	      && TARGET_ಅಭಿವ್ಯಕ್ತಿ_SLOT (t1) == ವೃಕ್ಷ_OPERAND (exp, 1)
	      && ವೃಕ್ಷ_CODE (t2) == CALL_ಅಭಿವ್ಯಕ್ತಿ)
	    {
	      ವೃಕ್ಷ fndecl = get_callee_fndecl (t2);
	      ವೃಕ್ಷ arg = NULL_ವೃಕ್ಷ;
	      ಯದಿ (fndecl
		  && ವೃಕ್ಷ_CODE (fndecl) == FUNCTION_DECL
		  && fndecl_built_in_p (fndecl, BUILT_IN_NORMAL)
		  && call_ಅಭಿವ್ಯಕ್ತಿ_nargs (t2) >= 2)
		ವಿಕಲ್ಪ (DECL_FUNCTION_CODE (fndecl))
		  {
		  ಪಕ್ಷ BUILT_IN_ATOMIC_STORE:
		    arg = CALL_ಅಭಿವ್ಯಕ್ತಿ_ARG (t2, 1);
		    ಭಙ್ಗ;
		  ಪಕ್ಷ BUILT_IN_ATOMIC_STORE_1:
		  ಪಕ್ಷ BUILT_IN_ATOMIC_STORE_2:
		  ಪಕ್ಷ BUILT_IN_ATOMIC_STORE_4:
		  ಪಕ್ಷ BUILT_IN_ATOMIC_STORE_8:
		  ಪಕ್ಷ BUILT_IN_ATOMIC_STORE_16:
		    arg = CALL_ಅಭಿವ್ಯಕ್ತಿ_ARG (t2, 0);
		    ಭಙ್ಗ;
		  ಸ್ವಭಾವ:
		    ಭಙ್ಗ;
		  }
	      ಯದಿ (arg)
		{
		  STRIP_NOPS (arg);
		  ಯದಿ (ವೃಕ್ಷ_CODE (arg) == ADDR_ಅಭಿವ್ಯಕ್ತಿ
		      && DECL_P (ವೃಕ್ಷ_OPERAND (arg, 0))
		      && TYPE_ATOMIC (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_OPERAND (arg, 0))))
		    mark_exp_read (ವೃಕ್ಷ_OPERAND (arg, 0));
		}
	    }
	}
      /* FALLTHRU */
    ಪಕ್ಷ C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ:
      mark_exp_read (ವೃಕ್ಷ_OPERAND (exp, 1));
      ಭಙ್ಗ;
    ಪಕ್ಷ OMP_ARRAY_SECTION:
      mark_exp_read (ವೃಕ್ಷ_OPERAND (exp, 0));
      ಯದಿ (ವೃಕ್ಷ_OPERAND (exp, 1))
	mark_exp_read (ವೃಕ್ಷ_OPERAND (exp, 1));
      ಯದಿ (ವೃಕ್ಷ_OPERAND (exp, 2))
	mark_exp_read (ವೃಕ್ಷ_OPERAND (exp, 2));
      ಭಙ್ಗ;
    ಸ್ವಭಾವ:
      ಭಙ್ಗ;
    }
}

/* Perform the default conversion of arrays and functions to pointers.
   Return the result of converting EXP.  For any other expression, just
   return EXP.

   LOC is the location of the expression.  */

ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ
default_function_array_conversion (location_t loc, ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ exp)
{
  ವೃಕ್ಷ orig_exp = exp.ಮೌಲ್ಯ;
  ವೃಕ್ಷ type = ವೃಕ್ಷ_TYPE (exp.ಮೌಲ್ಯ);
  ಗಣನಾ ವೃಕ್ಷ_code code = ವೃಕ್ಷ_CODE (type);

  ವಿಕಲ್ಪ (code)
    {
    ಪಕ್ಷ ARRAY_TYPE:
      {
	ತಾರ್ಕಿಕ not_lvalue = ಅಸತ್ಯ;
	ತಾರ್ಕಿಕ lvalue_array_p;

	ಯಾವತ್ ((ವೃಕ್ಷ_CODE (exp.ಮೌಲ್ಯ) == NON_LVALUE_ಅಭಿವ್ಯಕ್ತಿ
		|| CONVERT_ಅಭಿವ್ಯಕ್ತಿ_P (exp.ಮೌಲ್ಯ))
	       && ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_OPERAND (exp.ಮೌಲ್ಯ, 0)) == type)
	  {
	    ಯದಿ (ವೃಕ್ಷ_CODE (exp.ಮೌಲ್ಯ) == NON_LVALUE_ಅಭಿವ್ಯಕ್ತಿ)
	      not_lvalue = ಸತ್ಯ;
	    exp.ಮೌಲ್ಯ = ವೃಕ್ಷ_OPERAND (exp.ಮೌಲ್ಯ, 0);
	  }

	copy_warning (exp.ಮೌಲ್ಯ, orig_exp);

	lvalue_array_p = !not_lvalue && lvalue_p (exp.ಮೌಲ್ಯ);
	ಯದಿ (!flag_isoc99 && !lvalue_array_p)
	  {
	    /* Before C99, non-lvalue arrays do not decay to pointers.
	       Normally, using such an array would be invalid; but it can
	       be used correctly inside sizeof or as a statement expression.
	       Thus, do not give an error here; an error will result later.  */
	    ಪ್ರತ್ಯಾಗಮ exp;
	  }

	exp.ಮೌಲ್ಯ = array_to_pointer_conversion (loc, exp.ಮೌಲ್ಯ);
      }
      ಭಙ್ಗ;
    ಪಕ್ಷ FUNCTION_TYPE:
      exp.ಮೌಲ್ಯ = function_to_pointer_conversion (loc, exp.ಮೌಲ್ಯ);
      ಭಙ್ಗ;
    ಸ್ವಭಾವ:
      ಭಙ್ಗ;
    }

  ಪ್ರತ್ಯಾಗಮ exp;
}

ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ
default_function_array_read_conversion (location_t loc, ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ exp)
{
  mark_exp_read (exp.ಮೌಲ್ಯ);
  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  ಯದಿ (ವೃಕ್ಷ_CODE (exp.ಮೌಲ್ಯ) == COMPONENT_REF
      && handle_counted_by_p (exp.ಮೌಲ್ಯ))
    exp.ಮೌಲ್ಯ = handle_counted_by_for_component_ref (loc, exp.ಮೌಲ್ಯ);
  ಪ್ರತ್ಯಾಗಮ default_function_array_conversion (loc, exp);
}

/* Return whether EXPR should be treated as an atomic lvalue for the
   purposes of load and store handling.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
really_atomic_lvalue (ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ)
{
  ಯದಿ (error_operand_p (ಅಭಿವ್ಯಕ್ತಿ))
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
  ಯದಿ (!TYPE_ATOMIC (ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ)))
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
  ಯದಿ (!COMPLETE_TYPE_P (ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ)))
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
  ಯದಿ (!lvalue_p (ಅಭಿವ್ಯಕ್ತಿ))
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

  /* Ignore _Atomic on register variables, since their addresses can't
     be taken so (a) atomicity is irrelevant and (b) the normal atomic
     sequences wouldn't work.  Ignore _Atomic on structures containing
     bit-fields, since accessing elements of atomic structures or
     unions is undefined behavior (C11 6.5.2.3#5), but it's unclear if
     it's undefined at translation time or execution time, and the
     normal atomic sequences again wouldn't work.  */
  ಯಾವತ್ (handled_component_p (ಅಭಿವ್ಯಕ್ತಿ))
    {
      ಯದಿ (ವೃಕ್ಷ_CODE (ಅಭಿವ್ಯಕ್ತಿ) == COMPONENT_REF
	  && DECL_C_BIT_FIELD (ವೃಕ್ಷ_OPERAND (ಅಭಿವ್ಯಕ್ತಿ, 1)))
	ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
      ಅಭಿವ್ಯಕ್ತಿ = ವೃಕ್ಷ_OPERAND (ಅಭಿವ್ಯಕ್ತಿ, 0);
    }
  ಯದಿ (ವೃಕ್ಷ_CODE (ಅಭಿವ್ಯಕ್ತಿ) == COMPOUND_LITERAL_ಅಭಿವ್ಯಕ್ತಿ)
    ಅಭಿವ್ಯಕ್ತಿ = COMPOUND_LITERAL_ಅಭಿವ್ಯಕ್ತಿ_DECL (ಅಭಿವ್ಯಕ್ತಿ);
  ಯದಿ (DECL_P (ಅಭಿವ್ಯಕ್ತಿ) && C_DECL_REGISTER (ಅಭಿವ್ಯಕ್ತಿ))
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
  ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
}

/* If EXPR is a named constant (C23) derived from a constexpr variable
   - that is, a reference to such a variable, or a member extracted by
   a sequence of structure and union (but not array) member accesses
   (where union member accesses must access the same member as
   initialized) - then return the corresponding initializer;
   otherwise, return NULL_TREE.  */

ಸ್ಥಿರ ವೃಕ್ಷ
maybe_get_constexpr_init (ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ)
{
  ವೃಕ್ಷ decl = NULL_ವೃಕ್ಷ;
  ಯದಿ (ವೃಕ್ಷ_CODE (ಅಭಿವ್ಯಕ್ತಿ) == VAR_DECL)
    decl = ಅಭಿವ್ಯಕ್ತಿ;
  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (ಅಭಿವ್ಯಕ್ತಿ) == COMPOUND_LITERAL_ಅಭಿವ್ಯಕ್ತಿ)
    decl = COMPOUND_LITERAL_ಅಭಿವ್ಯಕ್ತಿ_DECL (ಅಭಿವ್ಯಕ್ತಿ);
  ಯದಿ (decl
      && C_DECL_DECLARED_CONSTEXPR (decl)
      && DECL_INITIAL (decl) != NULL_ವೃಕ್ಷ
      && !error_operand_p (DECL_INITIAL (decl)))
    ಪ್ರತ್ಯಾಗಮ DECL_INITIAL (decl);
  ಯದಿ (ವೃಕ್ಷ_CODE (ಅಭಿವ್ಯಕ್ತಿ) != COMPONENT_REF)
    ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
  ವೃಕ್ಷ inner = maybe_get_constexpr_init (ವೃಕ್ಷ_OPERAND (ಅಭಿವ್ಯಕ್ತಿ, 0));
  ಯದಿ (inner == NULL_ವೃಕ್ಷ)
    ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
  ಯಾವತ್ ((CONVERT_ಅಭಿವ್ಯಕ್ತಿ_P (inner) || ವೃಕ್ಷ_CODE (inner) == NON_LVALUE_ಅಭಿವ್ಯಕ್ತಿ)
	 && !error_operand_p (inner)
	 && (TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (inner))
	     == TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_OPERAND (inner, 0)))))
    inner = ವೃಕ್ಷ_OPERAND (inner, 0);
  ಯದಿ (ವೃಕ್ಷ_CODE (inner) != CONSTRUCTOR)
    ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
  ವೃಕ್ಷ field = ವೃಕ್ಷ_OPERAND (ಅಭಿವ್ಯಕ್ತಿ, 1);
  unsigned HOST_WIDE_INT cidx;
  ವೃಕ್ಷ cfield, cvalue;
  ತಾರ್ಕಿಕ have_other_init = ಅಸತ್ಯ;
  FOR_EACH_CONSTRUCTOR_ELT (CONSTRUCTOR_ELTS (inner), cidx, cfield, cvalue)
    {
      ಯದಿ (cfield == field)
	ಪ್ರತ್ಯಾಗಮ cvalue;
      have_other_init = ಸತ್ಯ;
    }
  ಯದಿ (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (inner)) == UNION_TYPE
      && (have_other_init || field != TYPE_FIELDS (ವೃಕ್ಷ_TYPE (inner))))
    ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
  /* Return a default initializer.  */
  ಯದಿ (RECORD_OR_UNION_TYPE_P (ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ)))
    ಪ್ರತ್ಯಾಗಮ build_constructor (ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ), ರಿಕ್ತ);
  ಪ್ರತ್ಯಾಗಮ build_zero_cst (ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ));
}

/* Helper function for convert_lvalue_to_rvalue called via
   walk_tree_without_duplicates.  Find DATA inside of the expression.  */

ಸ್ಥಿರ ವೃಕ್ಷ
c_find_var_r (ವೃಕ್ಷ *tp, ಪೂರ್ಣಾಙ್ಕ *walk_subtrees, ಶೂನ್ಯ *data)
{
  ಯದಿ (TYPE_P (*tp))
    *walk_subtrees = 0;
  ಅನ್ಯಥಾ ಯದಿ (*tp == (ವೃಕ್ಷ) data)
    ಪ್ರತ್ಯಾಗಮ *tp;
  ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
}

/* Convert expression EXP (location LOC) from lvalue to rvalue,
   including converting functions and arrays to pointers if CONVERT_P.
   If READ_P, also mark the expression as having been read.  If
   FOR_INIT, constexpr expressions of structure and union type should
   be replaced by the corresponding CONSTRUCTOR; otherwise, only
   constexpr scalars (including elements of structures and unions) are
   replaced by their initializers.  */

ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ
convert_lvalue_to_rvalue (location_t loc, ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ exp,
			  ತಾರ್ಕಿಕ convert_p, ತಾರ್ಕಿಕ read_p, ತಾರ್ಕಿಕ for_init)
{
  ತಾರ್ಕಿಕ force_non_npc = ಅಸತ್ಯ;
  ಯದಿ (read_p)
    mark_exp_read (exp.ಮೌಲ್ಯ);
  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  ಯದಿ (read_p && ವೃಕ್ಷ_CODE (exp.ಮೌಲ್ಯ) == COMPONENT_REF
      && handle_counted_by_p (exp.ಮೌಲ್ಯ))
    exp.ಮೌಲ್ಯ = handle_counted_by_for_component_ref (loc, exp.ಮೌಲ್ಯ);

  ಯದಿ (convert_p)
    exp = default_function_array_conversion (loc, exp);
  ಯದಿ (!VOID_TYPE_P (ವೃಕ್ಷ_TYPE (exp.ಮೌಲ್ಯ))
      || (flag_isoc2y
	  && TYPE_QUALS (ವೃಕ್ಷ_TYPE (exp.ಮೌಲ್ಯ)) != TYPE_UNQUALIFIED))
    exp.ಮೌಲ್ಯ = require_complete_type (loc, exp.ಮೌಲ್ಯ);
  ಯದಿ (for_init || !RECORD_OR_UNION_TYPE_P (ವೃಕ್ಷ_TYPE (exp.ಮೌಲ್ಯ)))
    {
      ವೃಕ್ಷ init = maybe_get_constexpr_init (exp.ಮೌಲ್ಯ);
      ಯದಿ (init != NULL_ವೃಕ್ಷ)
	{
	  /* A named constant of pointer type or type nullptr_t is not
	     a null pointer constant even if the initializer is
	     one.  */
	  ಯದಿ (ವೃಕ್ಷ_CODE (init) == INTEGER_CST
	      && !INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (init))
	      && integer_zerop (init))
	    force_non_npc = ಸತ್ಯ;
	  exp.ಮೌಲ್ಯ = init;
	}
    }
  ಯದಿ (really_atomic_lvalue (exp.ಮೌಲ್ಯ))
    {
      vec<ವೃಕ್ಷ, va_gc> *params;
      ವೃಕ್ಷ nonatomic_type, tmp, tmp_addr, fndecl, func_call;
      ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ_type = ವೃಕ್ಷ_TYPE (exp.ಮೌಲ್ಯ);
      ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ_addr = build_unary_op (loc, ADDR_ಅಭಿವ್ಯಕ್ತಿ, exp.ಮೌಲ್ಯ, ಅಸತ್ಯ);
      ವೃಕ್ಷ seq_cst = build_int_cst (integer_type_ಗಂಟು, MEMMODEL_SEQ_CST);

      gcc_assert (TYPE_ATOMIC (ಅಭಿವ್ಯಕ್ತಿ_type));

      /* Expansion of a generic atomic load may require an addition
	 element, so allocate enough to prevent a resize.  */
      vec_alloc (params, 4);

      /* Remove the qualifiers for the rest of the expressions and
	 create the VAL temp variable to hold the RHS.  */
      nonatomic_type = build_qualified_type (ಅಭಿವ್ಯಕ್ತಿ_type, TYPE_UNQUALIFIED);
      tmp = create_tmp_var_raw (nonatomic_type);
      tmp_addr = build_unary_op (loc, ADDR_ಅಭಿವ್ಯಕ್ತಿ, tmp, ಅಸತ್ಯ);
      ವೃಕ್ಷ_ADDRESSABLE (tmp) = 1;
      /* Do not disable warnings for TMP even though it's artificial.
	 -Winvalid-memory-model depends on it.  */

      /* Issue __atomic_load (&expr, &tmp, SEQ_CST);  */
      fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_LOAD);
      params->quick_ತಳ್ಳು (ಅಭಿವ್ಯಕ್ತಿ_addr);
      params->quick_ತಳ್ಳು (tmp_addr);
      params->quick_ತಳ್ಳು (seq_cst);
      func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, ರಿಕ್ತ);

      /* EXPR is always read.  */
      mark_exp_read (exp.ಮೌಲ್ಯ);

      /* Optimize the common case where c_build_function_call_vec
	 immediately folds __atomic_load (&expr, &tmp, SEQ_CST); into
	 tmp = __atomic_load_<N> (&expr, SEQ_CST);
	 In that case tmp is not addressable and can be initialized
	 fully by the rhs of the MODIFY_EXPR.  */
      ವೃಕ್ಷ tem = func_call;
      ಯದಿ (CONVERT_ಅಭಿವ್ಯಕ್ತಿ_P (tem) && VOID_TYPE_P (ವೃಕ್ಷ_TYPE (tem)))
	{
	  tem = ವೃಕ್ಷ_OPERAND (tem, 0);
	  ಯದಿ (ವೃಕ್ಷ_CODE (tem) == MODIFY_ಅಭಿವ್ಯಕ್ತಿ
	      && ವೃಕ್ಷ_OPERAND (tem, 0) == tmp
	      && !walk_ವೃಕ್ಷ_without_duplicates (&ವೃಕ್ಷ_OPERAND (tem, 1),
						c_find_var_r, tmp))
	    {
	      ವೃಕ್ಷ_ADDRESSABLE (tmp) = 0;
	      func_call = ವೃಕ್ಷ_OPERAND (tem, 1);
	    }
	}

      /* Return tmp which contains the value loaded.  */
      exp.ಮೌಲ್ಯ = build4 (TARGET_ಅಭಿವ್ಯಕ್ತಿ, nonatomic_type, tmp, func_call,
			  NULL_ವೃಕ್ಷ, NULL_ವೃಕ್ಷ);
    }
  ಯದಿ (convert_p && !error_operand_p (exp.ಮೌಲ್ಯ)
      && (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (exp.ಮೌಲ್ಯ)) != ARRAY_TYPE))
    exp.ಮೌಲ್ಯ = convert (build_qualified_type (ವೃಕ್ಷ_TYPE (exp.ಮೌಲ್ಯ), TYPE_UNQUALIFIED), exp.ಮೌಲ್ಯ);
  ಯದಿ (force_non_npc)
    exp.ಮೌಲ್ಯ = build1 (NOP_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (exp.ಮೌಲ್ಯ), exp.ಮೌಲ್ಯ);

  {
    ವೃಕ್ಷ false_ಮೌಲ್ಯ, true_ಮೌಲ್ಯ;
    ಯದಿ (convert_p && !error_operand_p (exp.ಮೌಲ್ಯ)
	&& c_hardbool_type_attr (ವೃಕ್ಷ_TYPE (exp.ಮೌಲ್ಯ),
				 &false_ಮೌಲ್ಯ, &true_ಮೌಲ್ಯ))
      {
	ವೃಕ್ಷ t = save_ಅಭಿವ್ಯಕ್ತಿ (exp.ಮೌಲ್ಯ);

	mark_exp_read (exp.ಮೌಲ್ಯ);

	ವೃಕ್ಷ trapfn = builtin_decl_explicit (BUILT_IN_TRAP);
	ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ = build_call_ಅಭಿವ್ಯಕ್ತಿ_loc (loc, trapfn, 0);
	ಅಭಿವ್ಯಕ್ತಿ = build_compound_ಅಭಿವ್ಯಕ್ತಿ (loc, ಅಭಿವ್ಯಕ್ತಿ, boolean_true_ಗಂಟು);
	ಅಭಿವ್ಯಕ್ತಿ = fold_build3_loc (loc, COND_ಅಭಿವ್ಯಕ್ತಿ, boolean_type_ಗಂಟು,
				fold_build2_loc (loc, NE_ಅಭಿವ್ಯಕ್ತಿ,
						 boolean_type_ಗಂಟು,
						 t, true_ಮೌಲ್ಯ),
				ಅಭಿವ್ಯಕ್ತಿ, boolean_true_ಗಂಟು);
	ಅಭಿವ್ಯಕ್ತಿ = fold_build3_loc (loc, COND_ಅಭಿವ್ಯಕ್ತಿ, boolean_type_ಗಂಟು,
				fold_build2_loc (loc, NE_ಅಭಿವ್ಯಕ್ತಿ,
						 boolean_type_ಗಂಟು,
						 t, false_ಮೌಲ್ಯ),
				ಅಭಿವ್ಯಕ್ತಿ, boolean_false_ಗಂಟು);

	exp.ಮೌಲ್ಯ = ಅಭಿವ್ಯಕ್ತಿ;
      }
  }

  ಪ್ರತ್ಯಾಗಮ exp;
}

/* Wrapper for the overload above, same arguments but for tree rather than
   c_expr.  This is important for hardbools to decay to bools.  */

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ವೃಕ್ಷ
convert_lvalue_to_rvalue (location_t loc, ವೃಕ್ಷ val,
			  ತಾರ್ಕಿಕ convert_p, ತಾರ್ಕಿಕ read_p, ತಾರ್ಕಿಕ for_init = ಅಸತ್ಯ)
{
  ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ;
  memset (&ಅಭಿವ್ಯಕ್ತಿ, 0, ಪರಿಮಾಣ (ಅಭಿವ್ಯಕ್ತಿ));
  ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = val;
  ಅಭಿವ್ಯಕ್ತಿ = convert_lvalue_to_rvalue (loc, ಅಭಿವ್ಯಕ್ತಿ, convert_p, read_p, for_init);
  ಪ್ರತ್ಯಾಗಮ ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ;
}

/* EXP is an expression of integer type.  Apply the integer promotions
   to it and return the promoted value.  */

ವೃಕ್ಷ
perform_integral_promotions (ವೃಕ್ಷ exp)
{
  ವೃಕ್ಷ type = ವೃಕ್ಷ_TYPE (exp);
  ಗಣನಾ ವೃಕ್ಷ_code code = ವೃಕ್ಷ_CODE (type);

  gcc_assert (INTEGRAL_TYPE_P (type));

  /* Convert enums to the result of applying the integer promotions to
     their underlying type.  */
  ಯದಿ (code == ENUMERAL_TYPE)
    {
      type = ENUM_UNDERLYING_TYPE (type);
      ಯದಿ (c_promoting_integer_type_p (type))
	{
	  ಯದಿ (TYPE_UNSIGNED (type)
	      && TYPE_PRECISION (type) == TYPE_PRECISION (integer_type_ಗಂಟು))
	    type = unsigned_type_ಗಂಟು;
	  ಅನ್ಯಥಾ
	    type = integer_type_ಗಂಟು;
	}

      ಪ್ರತ್ಯಾಗಮ convert (type, exp);
    }

  /* ??? This should no longer be needed now bit-fields have their
     proper types.  */
  ಯದಿ (ವೃಕ್ಷ_CODE (exp) == COMPONENT_REF
      && DECL_C_BIT_FIELD (ವೃಕ್ಷ_OPERAND (exp, 1)))
    {
      ಯದಿ (BITINT_TYPE_P (DECL_BIT_FIELD_TYPE (ವೃಕ್ಷ_OPERAND (exp, 1))))
	{
	  ವೃಕ್ಷ btype = DECL_BIT_FIELD_TYPE (ವೃಕ್ಷ_OPERAND (exp, 1));
	  ಯದಿ (ವೃಕ್ಷ_CODE (btype) == BITINT_TYPE)
	    ಪ್ರತ್ಯಾಗಮ convert (btype, exp);
	  ಅನ್ಯಥಾ
	    ಪ್ರತ್ಯಾಗಮ convert (ENUM_UNDERLYING_TYPE (btype), exp);
	}
      /* If it's thinner than an int, promote it like a
	 c_promoting_integer_type_p, otherwise leave it alone.  */
      ಯದಿ (compare_ವೃಕ್ಷ_int (DECL_SIZE (ವೃಕ್ಷ_OPERAND (exp, 1)),
			    TYPE_PRECISION (integer_type_ಗಂಟು)) < 0)
	ಪ್ರತ್ಯಾಗಮ convert (integer_type_ಗಂಟು, exp);
    }

  ಯದಿ (c_promoting_integer_type_p (type))
    {
      /* Preserve unsignedness if not really getting any wider.  */
      ಯದಿ (TYPE_UNSIGNED (type)
	  && TYPE_PRECISION (type) == TYPE_PRECISION (integer_type_ಗಂಟು))
	ಪ್ರತ್ಯಾಗಮ convert (unsigned_type_ಗಂಟು, exp);

      ಪ್ರತ್ಯಾಗಮ convert (integer_type_ಗಂಟು, exp);
    }

  ಪ್ರತ್ಯಾಗಮ exp;
}


/* Perform default promotions for C data used in expressions.
   Enumeral types or short or char are converted to int.
   In addition, manifest constants symbols are replaced by their values.  */

ವೃಕ್ಷ
default_conversion (ವೃಕ್ಷ exp)
{
  ವೃಕ್ಷ orig_exp;
  ವೃಕ್ಷ type = ವೃಕ್ಷ_TYPE (exp);
  ಗಣನಾ ವೃಕ್ಷ_code code = ವೃಕ್ಷ_CODE (type);
  ವೃಕ್ಷ promoted_type;

  mark_exp_read (exp);
  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  ಯದಿ (ವೃಕ್ಷ_CODE (exp) == COMPONENT_REF
      && handle_counted_by_p (exp))
    exp = handle_counted_by_for_component_ref (ಅಭಿವ್ಯಕ್ತಿ_LOCATION (exp), exp);

  /* Functions and arrays have been converted during parsing.  */
  gcc_assert (code != FUNCTION_TYPE);
  ಯದಿ (code == ARRAY_TYPE)
    ಪ್ರತ್ಯಾಗಮ exp;

  /* Constants can be used directly unless they're not loadable.  */
  ಯದಿ (ವೃಕ್ಷ_CODE (exp) == CONST_DECL)
    exp = DECL_INITIAL (exp);

  /* Strip no-op conversions.  */
  orig_exp = exp;
  STRIP_TYPE_NOPS (exp);

  copy_warning (exp, orig_exp);

  ಯದಿ (code == VOID_TYPE)
    {
      error_at (ಅಭಿವ್ಯಕ್ತಿ_LOC_OR_LOC (exp, ಒಳಹರಿವು_location),
		"void value not ignored as it ought to be");
      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
    }

  exp = require_complete_type (ಅಭಿವ್ಯಕ್ತಿ_LOC_OR_LOC (exp, ಒಳಹರಿವು_location), exp);
  ಯದಿ (exp == error_mark_ಗಂಟು)
    ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;

  promoted_type = targetm.promoted_type (type);
  ಯದಿ (promoted_type)
    ಪ್ರತ್ಯಾಗಮ convert (promoted_type, exp);

  ಯದಿ (INTEGRAL_TYPE_P (type))
    {
      /* Avoid performing integral promotion of bit-precise integer
	 type bit-field to its corresponding bit-precise integer if
	 orig_exp is a cast to it to its underlying type.  */
      ಯದಿ (orig_exp != exp
	  && ವೃಕ್ಷ_CODE (exp) == COMPONENT_REF
	  && DECL_C_BIT_FIELD (ವೃಕ್ಷ_OPERAND (exp, 1))
	  && BITINT_TYPE_P (DECL_BIT_FIELD_TYPE (ವೃಕ್ಷ_OPERAND (exp, 1))))
	ಪ್ರತ್ಯಾಗಮ perform_integral_promotions (orig_exp);
      ಪ್ರತ್ಯಾಗಮ perform_integral_promotions (exp);
    }

  ಪ್ರತ್ಯಾಗಮ exp;
}

/* Look up COMPONENT in a structure or union TYPE.

   If the component name is not found, returns NULL_TREE.  Otherwise,
   the return value is a TREE_LIST, with each TREE_VALUE a FIELD_DECL
   stepping down the chain to the component, which is in the last
   TREE_VALUE of the list.  Normally the list is of length one, but if
   the component is embedded within (nested) anonymous structures or
   unions, the list steps down the chain to the component.  */

ವೃಕ್ಷ
lookup_field (const_ವೃಕ್ಷ type, ವೃಕ್ಷ component)
{
  ವೃಕ್ಷ field;

  /* If TYPE_LANG_SPECIFIC is set, then it is a sorted array of pointers
     to the field elements.  Use a binary search on this array to quickly
     find the element.  Otherwise, do a linear search.  TYPE_LANG_SPECIFIC
     will always be set for structures which have many elements.

     Duplicate field checking replaces duplicates with NULL_TREE so
     TYPE_LANG_SPECIFIC arrays are potentially no longer sorted.  In that
     case just iterate using DECL_CHAIN.  */

  ಯದಿ (TYPE_LANG_SPECIFIC (type) && TYPE_LANG_SPECIFIC (type)->s
      && !seen_error ())
    {
      ಪೂರ್ಣಾಙ್ಕ bot, ತುದಿ, half;
      ವೃಕ್ಷ *field_array = &TYPE_LANG_SPECIFIC (type)->s->elts[0];

      field = TYPE_FIELDS (type);
      bot = 0;
      ತುದಿ = TYPE_LANG_SPECIFIC (type)->s->len;
      ಯಾವತ್ (ತುದಿ - bot > 1)
	{
	  half = (ತುದಿ - bot + 1) >> 1;
	  field = field_array[bot+half];

	  ಯದಿ (DECL_NAME (field) == NULL_ವೃಕ್ಷ)
	    {
	      /* Step through all anon unions in linear fashion.  */
	      ಯಾವತ್ (DECL_NAME (field_array[bot]) == NULL_ವೃಕ್ಷ)
		{
		  field = field_array[bot++];
		  ಯದಿ (RECORD_OR_UNION_TYPE_P (ವೃಕ್ಷ_TYPE (field)))
		    {
		      ವೃಕ್ಷ anon = lookup_field (ವೃಕ್ಷ_TYPE (field), component);

		      ಯದಿ (anon)
			ಪ್ರತ್ಯಾಗಮ ವೃಕ್ಷ_cons (NULL_ವೃಕ್ಷ, field, anon);

		      /* The Plan 9 compiler permits referring
			 directly to an anonymous struct/union field
			 using a typedef name.  */
		      ಯದಿ (flag_plan9_extensions
			  && TYPE_NAME (ವೃಕ್ಷ_TYPE (field)) != NULL_ವೃಕ್ಷ
			  && (ವೃಕ್ಷ_CODE (TYPE_NAME (ವೃಕ್ಷ_TYPE (field)))
			      == TYPE_DECL)
			  && (DECL_NAME (TYPE_NAME (ವೃಕ್ಷ_TYPE (field)))
			      == component))
			ಭಙ್ಗ;
		    }
		}

	      /* Entire record is only anon unions.  */
	      ಯದಿ (bot > ತುದಿ)
		ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;

	      /* Restart the binary search, with new lower bound.  */
	      ಅನುವರ್ತ;
	    }

	  ಯದಿ (DECL_NAME (field) == component)
	    ಭಙ್ಗ;
	  ಯದಿ (DECL_NAME (field) < component)
	    bot += half;
	  ಅನ್ಯಥಾ
	    ತುದಿ = bot + half;
	}

      ಯದಿ (DECL_NAME (field_array[bot]) == component)
	field = field_array[bot];
      ಅನ್ಯಥಾ ಯದಿ (DECL_NAME (field) != component)
	ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
    }
  ಅನ್ಯಥಾ
    {
      ಪ್ರತಿ (field = TYPE_FIELDS (type); field; field = DECL_CHAIN (field))
	{
	  ಯದಿ (DECL_NAME (field) == NULL_ವೃಕ್ಷ
	      && RECORD_OR_UNION_TYPE_P (ವೃಕ್ಷ_TYPE (field)))
	    {
	      ವೃಕ್ಷ anon = lookup_field (ವೃಕ್ಷ_TYPE (field), component);

	      ಯದಿ (anon)
		ಪ್ರತ್ಯಾಗಮ ವೃಕ್ಷ_cons (NULL_ವೃಕ್ಷ, field, anon);

	      /* The Plan 9 compiler permits referring directly to an
		 anonymous struct/union field using a typedef
		 name.  */
	      ಯದಿ (flag_plan9_extensions
		  && TYPE_NAME (ವೃಕ್ಷ_TYPE (field)) != NULL_ವೃಕ್ಷ
		  && ವೃಕ್ಷ_CODE (TYPE_NAME (ವೃಕ್ಷ_TYPE (field))) == TYPE_DECL
		  && (DECL_NAME (TYPE_NAME (ವೃಕ್ಷ_TYPE (field)))
		      == component))
		ಭಙ್ಗ;
	    }

	  ಯದಿ (DECL_NAME (field) == component)
	    ಭಙ್ಗ;
	}

      ಯದಿ (field == NULL_ವೃಕ್ಷ)
	ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
    }

  ಪ್ರತ್ಯಾಗಮ ವೃಕ್ಷ_cons (NULL_ವೃಕ್ಷ, field, NULL_ವೃಕ್ಷ);
}

/* Recursively append candidate IDENTIFIER_NODEs to CANDIDATES.  */

ಸ್ಥಿರ ಶೂನ್ಯ
lookup_field_fuzzy_find_candidates (ವೃಕ್ಷ type, ವೃಕ್ಷ component,
				    vec<ವೃಕ್ಷ> *candidates)
{
  ವೃಕ್ಷ field;
  ಪ್ರತಿ (field = TYPE_FIELDS (type); field; field = DECL_CHAIN (field))
    {
      ಯದಿ (DECL_NAME (field) == NULL_ವೃಕ್ಷ
	  && RECORD_OR_UNION_TYPE_P (ವೃಕ್ಷ_TYPE (field)))
	lookup_field_fuzzy_find_candidates (ವೃಕ್ಷ_TYPE (field), component,
					    candidates);

      ಯದಿ (DECL_NAME (field))
	candidates->safe_ತಳ್ಳು (DECL_NAME (field));
    }
}

/* Like "lookup_field", but find the closest matching IDENTIFIER_NODE,
   rather than returning a TREE_LIST for an exact match.  */

ಸ್ಥಿರ ವೃಕ್ಷ
lookup_field_fuzzy (ವೃಕ್ಷ type, ವೃಕ್ಷ component)
{
  gcc_assert (ವೃಕ್ಷ_CODE (component) == IDENTIFIER_ಗಂಟು);

  /* First, gather a list of candidates.  */
  auto_vec <ವೃಕ್ಷ> candidates;

  lookup_field_fuzzy_find_candidates (type, component,
				      &candidates);

  ಪ್ರತ್ಯಾಗಮ find_closest_identifier (component, &candidates);
}

/* Support function for build_component_ref's error-handling.

   Given DATUM_TYPE, and "DATUM.COMPONENT", where DATUM is *not* a
   struct or union, should we suggest "DATUM->COMPONENT" as a hint?  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
should_suggest_deref_p (ವೃಕ್ಷ datum_type)
{
  /* We don't do it for Objective-C, since Objective-C 2.0 dot-syntax
     allows "." for ptrs; we could be handling a failed attempt
     to access a property.  */
  ಯದಿ (c_dialect_objc ())
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

  /* Only suggest it for pointers...  */
  ಯದಿ (ವೃಕ್ಷ_CODE (datum_type) != POINTER_TYPE)
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

  /* ...to structs/unions.  */
  ವೃಕ್ಷ underlying_type = ವೃಕ್ಷ_TYPE (datum_type);
  ಗಣನಾ ವೃಕ್ಷ_code code = ವೃಕ್ಷ_CODE (underlying_type);
  ಯದಿ (code == RECORD_TYPE || code == UNION_TYPE)
    ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
  ಅನ್ಯಥಾ
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
}

/* Give a component ref REF, decide whether we should handle its counted_by
   attribute based on its context:
   Do not handle counted_by when in offsetof, typeof and alignof operator.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
handle_counted_by_p (ವೃಕ್ಷ ref)
{
  gcc_assert (ವೃಕ್ಷ_CODE (ref) == COMPONENT_REF);
  ವೃಕ್ಷ datum = ವೃಕ್ಷ_OPERAND (ref, 0);
  /* If the component_ref is build for a offsetof, i.e., the datum
     of the component_ref is a indirect_ref of null_pointer_node,
     we should not generate call to .ACCESS_WITH_SIZE.  */
  ಯದಿ (ವೃಕ್ಷ_CODE (datum) == INDIRECT_REF
      && ವೃಕ್ಷ_OPERAND (datum, 0) == null_pointer_ಗಂಟು)
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
  ಯದಿ (in_typeof || in_alignof)
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
  ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
}

/* Given a component ref REF, if there is a counted_by attribute attached,
   issue error when the element_type is a structure or union including a
   flexible array member.  */

ಸ್ಥಿರ ಶೂನ್ಯ
check_counted_by_attribute (location_t loc, ವೃಕ್ಷ ref)
{
  ವೃಕ್ಷ subdatum = ವೃಕ್ಷ_OPERAND (ref, 1);
  ವೃಕ್ಷ sub_type = ವೃಕ್ಷ_TYPE (subdatum);

  ಯದಿ (!flexible_array_member_type_p (sub_type)
      && ವೃಕ್ಷ_CODE (sub_type) != POINTER_TYPE)
    ಪ್ರತ್ಯಾಗಮ;

  ವೃಕ್ಷ element_type = ವೃಕ್ಷ_TYPE (sub_type);

  ವೃಕ್ಷ attr_counted_by = lookup_attribute ("counted_by",
					   DECL_ATTRIBUTES (subdatum));
  ಯದಿ (attr_counted_by)
    {
      /* Issue error when the element_type is a structure or
	union including a flexible array member.  */
      ಯದಿ (RECORD_OR_UNION_TYPE_P (element_type)
	  && TYPE_INCLUDES_FLEXARRAY (element_type))
	{
	  error_at (loc,
		    "%<counted_by%> attribute is not allowed for a pointer to"
		    " structure or union with flexible array member");
	  ಪ್ರತ್ಯಾಗಮ;
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

ಸ್ಥಿರ ವೃಕ್ಷ
build_counted_by_ref (ವೃಕ್ಷ datum, ವೃಕ್ಷ subdatum,
		      ವೃಕ್ಷ *counted_by_type)
{
  ವೃಕ್ಷ sub_type = ವೃಕ್ಷ_TYPE (subdatum);
  ಯದಿ (!flexible_array_member_type_p (sub_type)
      && ವೃಕ್ಷ_CODE (sub_type) != POINTER_TYPE)
    ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;

  ವೃಕ್ಷ attr_counted_by = lookup_attribute ("counted_by",
					   DECL_ATTRIBUTES (subdatum));
  ಯದಿ (!attr_counted_by)
    ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;

  ವೃಕ್ಷ counted_by_ref = NULL_ವೃಕ್ಷ;
  *counted_by_type = NULL_ವೃಕ್ಷ;

  ವೃಕ್ಷ type = ವೃಕ್ಷ_TYPE (datum);

  /* If the type of the containing structure is an anonymous struct/union,
     and this anonymous struct/union is not a root type, get the first
     outer named structure/union type.  */
  ಯಾವತ್ (ವೃಕ್ಷ_CODE (datum) == COMPONENT_REF
	 && c_type_tag (type) == NULL_ವೃಕ್ಷ
	 && DECL_NAME (ವೃಕ್ಷ_OPERAND (datum, 1)) == NULL_ವೃಕ್ಷ)
    {
      datum = ವೃಕ್ಷ_OPERAND (datum, 0);
      type = ವೃಕ್ಷ_TYPE (datum);
    }

  ವೃಕ್ಷ field_id = ವೃಕ್ಷ_ಮೌಲ್ಯ (ವೃಕ್ಷ_ಮೌಲ್ಯ (attr_counted_by));
  ವೃಕ್ಷ counted_by_field = lookup_field (type, field_id);
  gcc_assert (counted_by_field);

  ವೃಕ್ಷ counted_by_subdatum;
  ಕುರು
    {
      counted_by_subdatum = ವೃಕ್ಷ_ಮೌಲ್ಯ (counted_by_field);
      /* Get the TYPE of the counted_by field.  */
      *counted_by_type = ವೃಕ್ಷ_TYPE (counted_by_subdatum);

      counted_by_ref
	= build3 (COMPONENT_REF, ವೃಕ್ಷ_TYPE (counted_by_subdatum),
		  datum, counted_by_subdatum, NULL_ವೃಕ್ಷ);

      datum = counted_by_ref;
      counted_by_field = ವೃಕ್ಷ_CHAIN (counted_by_field);
    }
  ಯಾವತ್ (counted_by_field);

  counted_by_ref = build_fold_addr_ಅಭಿವ್ಯಕ್ತಿ (counted_by_ref);
  ಪ್ರತ್ಯಾಗಮ counted_by_ref;
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
ಸ್ಥಿರ ವೃಕ್ಷ
build_access_with_size_for_counted_by (location_t loc, ವೃಕ್ಷ ref,
				       ವೃಕ್ಷ counted_by_ref,
				       ವೃಕ್ಷ counted_by_type)
{
  gcc_assert (flexible_array_member_type_p (ವೃಕ್ಷ_TYPE (ref))
	      || ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (ref)) == POINTER_TYPE);

  ತಾರ್ಕಿಕ is_fam = flexible_array_member_type_p (ವೃಕ್ಷ_TYPE (ref));

  /* The result type of the call is a pointer to the flexible array type;
     or is the original pointer type to the pointer field with counted_by.  */
  ವೃಕ್ಷ result_type = is_fam ? c_build_pointer_type (ವೃಕ್ಷ_TYPE (ref))
		     : ವೃಕ್ಷ_TYPE (ref);

  ವೃಕ್ಷ element_type = ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (ref));
  ವೃಕ್ಷ element_size = VOID_TYPE_P (element_type)
		      ? size_one_ಗಂಟು
		      : TYPE_SIZE_UNIT (element_type);
  ಯದಿ (element_size == NULL_ವೃಕ್ಷ)
    ಪ್ರತ್ಯಾಗಮ ref;

  ವೃಕ್ಷ first_param = is_fam
		     ? c_fully_fold (array_to_pointer_conversion (loc, ref),
				     ಅಸತ್ಯ, ರಿಕ್ತ)
		     : c_fully_fold (ref, ಅಸತ್ಯ, ರಿಕ್ತ);
  ವೃಕ್ಷ second_param
    = c_fully_fold (counted_by_ref, ಅಸತ್ಯ, ರಿಕ್ತ);
  ವೃಕ್ಷ third_param = build_int_cst (c_build_pointer_type (counted_by_type), 0);

  ವೃಕ್ಷ call
    = build_call_ಅಭಿವ್ಯಕ್ತಿ_internal_loc (loc, IFN_ACCESS_WITH_SIZE,
				    result_type, 4,
				    first_param,
				    second_param,
				    third_param,
				    element_size);

  /* Wrap the call with an INDIRECT_REF with the flexible array type.  */
  ಯದಿ (is_fam)
    call = build1 (INDIRECT_REF, ವೃಕ್ಷ_TYPE (ref), call);
  SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (call, loc);
  ಪ್ರತ್ಯಾಗಮ call;
}

/* For the COMPONENT_REF ref, check whether it has a counted_by attribute,
   if so, wrap this COMPONENT_REF with the corresponding CALL to the
   function .ACCESS_WITH_SIZE.
   Otherwise, return the ref itself.  */

ವೃಕ್ಷ
handle_counted_by_for_component_ref (location_t loc, ವೃಕ್ಷ ref)
{
  gcc_assert (ವೃಕ್ಷ_CODE (ref) == COMPONENT_REF);
  ವೃಕ್ಷ datum = ವೃಕ್ಷ_OPERAND (ref, 0);
  ವೃಕ್ಷ subdatum = ವೃಕ್ಷ_OPERAND (ref, 1);
  ವೃಕ್ಷ counted_by_type = NULL_ವೃಕ್ಷ;

  ಯದಿ (!(flexible_array_member_type_p (ವೃಕ್ಷ_TYPE (ref))
	|| ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (ref)) == POINTER_TYPE))
    ಪ್ರತ್ಯಾಗಮ ref;

  ವೃಕ್ಷ counted_by_ref = build_counted_by_ref (datum, subdatum,
					      &counted_by_type);
  ಯದಿ (counted_by_ref)
    ref = build_access_with_size_for_counted_by (loc, ref,
						 counted_by_ref,
						 counted_by_type);
  ಪ್ರತ್ಯಾಗಮ ref;
}

/* Make an expression to refer to the COMPONENT field of structure or
   union value DATUM.  COMPONENT is an IDENTIFIER_NODE.  LOC is the
   location of the COMPONENT_REF.  COMPONENT_LOC is the location
   of COMPONENT.  ARROW_LOC is the location of the first -> operand if
   it is from -> operator.
   If HANDLE_COUNTED_BY is true, check the counted_by attribute and generate
   a call to .ACCESS_WITH_SIZE.  Otherwise, ignore the attribute.  */

ವೃಕ್ಷ
build_component_ref (location_t loc, ವೃಕ್ಷ datum, ವೃಕ್ಷ component,
		     location_t component_loc, location_t arrow_loc)
{
  ವೃಕ್ಷ type = ವೃಕ್ಷ_TYPE (datum);
  ಗಣನಾ ವೃಕ್ಷ_code code = ವೃಕ್ಷ_CODE (type);
  ವೃಕ್ಷ field = ರಿಕ್ತ;
  ವೃಕ್ಷ ref;
  ತಾರ್ಕಿಕ datum_lvalue = lvalue_p (datum);

  ಯದಿ (!objc_is_public (datum, component))
    ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;

  /* Detect Objective-C property syntax object.property.  */
  ಯದಿ (c_dialect_objc ()
      && (ref = objc_maybe_build_component_ref (datum, component)))
    ಪ್ರತ್ಯಾಗಮ ref;

  /* See if there is a field or component with name COMPONENT.  */

  ಯದಿ (code == RECORD_TYPE || code == UNION_TYPE)
    {
      ಯದಿ (!COMPLETE_TYPE_P (type))
	{
	  c_incomplete_type_error (loc, NULL_ವೃಕ್ಷ, type);
	  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	}

      field = lookup_field (type, component);

      ಯದಿ (!field)
	{
	  ವೃಕ್ಷ guessed_id = lookup_field_fuzzy (type, component);
	  ಯದಿ (guessed_id)
	    {
	      /* Attempt to provide a fixit replacement hint, if
		 we have a valid range for the component.  */
	      location_t reported_loc
		= (component_loc != UNKNOWN_LOCATION) ? component_loc : loc;
	      gcc_rich_location rich_loc (reported_loc);
	      ಯದಿ (component_loc != UNKNOWN_LOCATION)
		rich_loc.add_fixit_misspelled_id (component_loc, guessed_id);
	      error_at (&rich_loc,
			"%qT has no member named %qE; did you mean %qE?",
			type, component, guessed_id);
	    }
	  ಅನ್ಯಥಾ
	    error_at (loc, "%qT has no member named %qE", type, component);
	  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	}

      /* Accessing elements of atomic structures or unions is undefined
	 behavior (C11 6.5.2.3#5).  */
      ಯದಿ (TYPE_ATOMIC (type) && c_inhibit_evaluation_warnings == 0)
	{
	  ಯದಿ (code == RECORD_TYPE)
	    warning_at (loc, 0, "accessing a member %qE of an atomic "
			"structure %qE", component, datum);
	  ಅನ್ಯಥಾ
	    warning_at (loc, 0, "accessing a member %qE of an atomic "
			"union %qE", component, datum);
	}

      /* Chain the COMPONENT_REFs if necessary down to the FIELD.
	 This might be better solved in future the way the C++ front
	 end does it - by giving the anonymous entities each a
	 separate name and type, and then have build_component_ref
	 recursively call itself.  We can't do that here.  */
      ಕುರು
	{
	  ವೃಕ್ಷ subdatum = ವೃಕ್ಷ_ಮೌಲ್ಯ (field);
	  ಪೂರ್ಣಾಙ್ಕ quals;
	  ವೃಕ್ಷ subtype;
	  ತಾರ್ಕಿಕ use_datum_quals;

	  ಯದಿ (ವೃಕ್ಷ_TYPE (subdatum) == error_mark_ಗಂಟು)
	    ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;

	  /* If this is an rvalue, it does not have qualifiers in C
	     standard terms and we must avoid propagating such
	     qualifiers down to a non-lvalue array that is then
	     converted to a pointer.  */
	  use_datum_quals = (datum_lvalue
			     || ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (subdatum)) != ARRAY_TYPE);

	  quals = TYPE_QUALS (strip_array_types (ವೃಕ್ಷ_TYPE (subdatum)));
	  ಯದಿ (use_datum_quals)
	    quals |= TYPE_QUALS (ವೃಕ್ಷ_TYPE (datum));
	  subtype = c_build_qualified_type (ವೃಕ್ಷ_TYPE (subdatum), quals);

	  ref = build3 (COMPONENT_REF, subtype, datum, subdatum,
			NULL_ವೃಕ್ಷ);
	  SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (ref, loc);

	  check_counted_by_attribute (loc, ref);

	  ಯದಿ (ವೃಕ್ಷ_READONLY (subdatum)
	      || (use_datum_quals && ವೃಕ್ಷ_READONLY (datum)))
	    ವೃಕ್ಷ_READONLY (ref) = 1;
	  ಯದಿ (ವೃಕ್ಷ_THIS_VOLATILE (subdatum)
	      || (use_datum_quals && ವೃಕ್ಷ_THIS_VOLATILE (datum)))
	    ವೃಕ್ಷ_THIS_VOLATILE (ref) = 1;

	  ಯದಿ (ವೃಕ್ಷ_UNAVAILABLE (subdatum))
	    error_unavailable_use (subdatum, NULL_ವೃಕ್ಷ);
	  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_DEPRECATED (subdatum))
	    warn_deprecated_use (subdatum, NULL_ವೃಕ್ಷ);

	  datum = ref;

	  field = ವೃಕ್ಷ_CHAIN (field);
	}
      ಯಾವತ್ (field);

      ಪ್ರತ್ಯಾಗಮ ref;
    }
  ಅನ್ಯಥಾ ಯದಿ (should_suggest_deref_p (type))
    {
      /* Special-case the error message for "ptr.field" for the case
	 where the user has confused "." vs "->".  */
      rich_location richloc (ಸಾಲು_table, loc);
      ಯದಿ (INDIRECT_REF_P (datum) && arrow_loc != UNKNOWN_LOCATION)
	{
	  richloc.add_fixit_ಸೇರಿಸು_before (arrow_loc, "(*");
	  richloc.add_fixit_ಸೇರಿಸು_after (arrow_loc, ")");
	  error_at (&richloc,
		    "%qE is a pointer to pointer; did you mean to dereference "
		    "it before applying %<->%> to it?",
		    ವೃಕ್ಷ_OPERAND (datum, 0));
	}
      ಅನ್ಯಥಾ
	{
	  /* "loc" should be the "." token.  */
	  richloc.add_fixit_replace ("->");
	  error_at (&richloc,
		    "%qE is a pointer; did you mean to use %<->%>?",
		    datum);
	}
      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
    }
  ಅನ್ಯಥಾ ಯದಿ (code != ERROR_MARK)
    error_at (loc,
	      "request for member %qE in something not a structure or union",
	      component);

  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
}

/* Given an expression PTR for a pointer, return an expression
   for the value pointed to.
   ERRORSTRING is the name of the operator to appear in error messages.

   LOC is the location to use for the generated tree.  */

ವೃಕ್ಷ
build_indirect_ref (location_t loc, ವೃಕ್ಷ ptr, ref_operator errstring)
{
  ವೃಕ್ಷ pointer = default_conversion (ptr);
  ವೃಕ್ಷ type = ವೃಕ್ಷ_TYPE (pointer);
  ವೃಕ್ಷ ref;

  ಯದಿ (ವೃಕ್ಷ_CODE (type) == POINTER_TYPE)
    {
      ಯದಿ (CONVERT_ಅಭಿವ್ಯಕ್ತಿ_P (pointer)
          || ವೃಕ್ಷ_CODE (pointer) == VIEW_CONVERT_ಅಭಿವ್ಯಕ್ತಿ)
	{
	  /* If a warning is issued, mark it to avoid duplicates from
	     the backend.  This only needs to be done at
	     warn_strict_aliasing > 2.  */
	  ಯದಿ (warn_strict_aliasing > 2)
	    ಯದಿ (strict_aliasing_warning (ಅಭಿವ್ಯಕ್ತಿ_LOCATION (pointer),
					 type, ವೃಕ್ಷ_OPERAND (pointer, 0)))
	      suppress_warning (pointer, OPT_Wstrict_aliasing_);
	}

      ಯದಿ (ವೃಕ್ಷ_CODE (pointer) == ADDR_ಅಭಿವ್ಯಕ್ತಿ
	  && (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_OPERAND (pointer, 0))
	      == ವೃಕ್ಷ_TYPE (type)))
	{
	  ref = ವೃಕ್ಷ_OPERAND (pointer, 0);
	  protected_set_ಅಭಿವ್ಯಕ್ತಿ_location (ref, loc);
	  ಪ್ರತ್ಯಾಗಮ ref;
	}
      ಅನ್ಯಥಾ
	{
	  ವೃಕ್ಷ t = ವೃಕ್ಷ_TYPE (type);

	  ref = build1 (INDIRECT_REF, t, pointer);

	  ಯದಿ (VOID_TYPE_P (t) && c_inhibit_evaluation_warnings == 0)
	    warning_at (loc, 0, "dereferencing %<void *%> pointer");

	  /* We *must* set TREE_READONLY when dereferencing a pointer to const,
	     so that we get the proper error message if the result is used
	     to assign to.  Also, &* is supposed to be a no-op.
	     And ANSI C seems to specify that the type of the result
	     should be the const type.  */
	  /* A de-reference of a pointer to const is not a const.  It is valid
	     to change it via some other pointer.  */
	  ವೃಕ್ಷ_READONLY (ref) = TYPE_READONLY (t);
	  ವೃಕ್ಷ_SIDE_EFFECTS (ref)
	    = TYPE_VOLATILE (t) || ವೃಕ್ಷ_SIDE_EFFECTS (pointer);
	  ವೃಕ್ಷ_THIS_VOLATILE (ref) = TYPE_VOLATILE (t);
	  protected_set_ಅಭಿವ್ಯಕ್ತಿ_location (ref, loc);
	  ಪ್ರತ್ಯಾಗಮ ref;
	}
    }
  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (pointer) != ERROR_MARK)
    invalid_indirection_error (loc, type, errstring);

  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
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

ವೃಕ್ಷ
build_array_ref (location_t loc, ವೃಕ್ಷ array, ವೃಕ್ಷ index)
{
  ವೃಕ್ಷ ret;
  ತಾರ್ಕಿಕ swapped = ಅಸತ್ಯ;
  ಯದಿ (ವೃಕ್ಷ_TYPE (array) == error_mark_ಗಂಟು
      || ವೃಕ್ಷ_TYPE (index) == error_mark_ಗಂಟು)
    ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;

  ಯದಿ (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (array)) != ARRAY_TYPE
      && ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (array)) != POINTER_TYPE
      /* Allow vector[index] but not index[vector].  */
      && !gnu_vector_type_p (ವೃಕ್ಷ_TYPE (array)))
    {
      ಯದಿ (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (index)) != ARRAY_TYPE
	  && ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (index)) != POINTER_TYPE)
	{
          error_at (loc,
            "subscripted value is neither array nor pointer nor vector");

	  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	}
      std::swap (array, index);
      swapped = ಸತ್ಯ;
    }

  ಯದಿ (!INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (index)))
    {
      error_at (loc, "array subscript is not an integer");
      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
    }

  ಯದಿ (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (array))) == FUNCTION_TYPE)
    {
      error_at (loc, "subscripted value is pointer to function");
      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
    }

  /* ??? Existing practice has been to warn only when the char
     index is syntactically the index, not for char[array].  */
  ಯದಿ (!swapped)
     warn_array_subscript_with_type_char (loc, index);

  /* Apply default promotions *after* noticing character types.  */
  index = default_conversion (index);
  ಯದಿ (index == error_mark_ಗಂಟು)
    ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;

  gcc_assert (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (index)) == INTEGER_TYPE
	      || ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (index)) == BITINT_TYPE);

  ತಾರ್ಕಿಕ was_vector = VECTOR_TYPE_P (ವೃಕ್ಷ_TYPE (array));
  ತಾರ್ಕಿಕ non_lvalue = convert_vector_to_array_for_subscript (loc, &array, index);

  /* We only generate a call to .ACCESS_WITH_SIZE when it is a read.  */
  ಯದಿ (ವೃಕ್ಷ_CODE (array) == COMPONENT_REF
      && handle_counted_by_p (array))
    array = handle_counted_by_for_component_ref (loc, array);

  ಯದಿ (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (array)) == ARRAY_TYPE)
    {
      ವೃಕ್ಷ rval, type;

      /* An array that is indexed by a non-constant
	 cannot be stored in a register; we must be able to do
	 address arithmetic on its address.
	 Likewise an array of elements of variable size.  */
      ಯದಿ (ವೃಕ್ಷ_CODE (index) != INTEGER_CST
	  || (COMPLETE_TYPE_P (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (array)))
	      && ವೃಕ್ಷ_CODE (TYPE_SIZE (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (array)))) != INTEGER_CST))
	{
	  ಯದಿ (!c_mark_addressable (array, ಸತ್ಯ, ಸತ್ಯ))
	    ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	}
      /* An array that is indexed by a constant value which is not within
	 the array bounds cannot be stored in a register either; because we
	 would get a crash in store_bit_field/extract_bit_field when trying
	 to access a non-existent part of the register.  */
      ಯದಿ (ವೃಕ್ಷ_CODE (index) == INTEGER_CST
	  && TYPE_DOMAIN (ವೃಕ್ಷ_TYPE (array))
	  && !int_fits_type_p (index, TYPE_DOMAIN (ವೃಕ್ಷ_TYPE (array))))
	{
	  ಯದಿ (!c_mark_addressable (array, ಅಸತ್ಯ, ಸತ್ಯ))
	    ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	  /* ISO C2Y disallows a negative integer constant expression index
	     when array subscripting has an operand of array type.  */
	  ಯದಿ (flag_isoc2y
	      && !ವೃಕ್ಷ_OVERFLOW (index)
	      && ವೃಕ್ಷ_int_cst_sgn (index) < 0)
	    error_at (loc, "array subscript is negative");
	}

      ಯದಿ ((pedantic || warn_c90_c99_compat || warn_c23_c2y_compat)
	  && ! was_vector)
	{
	  ವೃಕ್ಷ foo = array;
	  ಯಾವತ್ (ವೃಕ್ಷ_CODE (foo) == COMPONENT_REF)
	    foo = ವೃಕ್ಷ_OPERAND (foo, 0);
	  ಯದಿ ((VAR_P (foo) && C_DECL_REGISTER (foo))
	      || (ವೃಕ್ಷ_CODE (foo) == COMPOUND_LITERAL_ಅಭಿವ್ಯಕ್ತಿ
		  && C_DECL_REGISTER (COMPOUND_LITERAL_ಅಭಿವ್ಯಕ್ತಿ_DECL (foo))))
	    pedwarn_c23 (loc, OPT_Wpedantic,
			 "ISO C forbids subscripting %<register%> array "
			 "before C2Y");
	  ಅನ್ಯಥಾ ಯದಿ (!lvalue_p (foo))
	    pedwarn_c90 (loc, OPT_Wpedantic,
			 "ISO C90 forbids subscripting non-lvalue "
			 "array");
	}

      ಯದಿ (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (index)) == BITINT_TYPE
	  && TYPE_PRECISION (ವೃಕ್ಷ_TYPE (index)) > TYPE_PRECISION (sizetype))
	index = fold_convert (sizetype, index);

      type = ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (array));
      rval = build4 (ARRAY_REF, type, array, index, NULL_ವೃಕ್ಷ, NULL_ವೃಕ್ಷ);
      /* Array ref is const/volatile if the array elements are
	 or if the array is.  */
      ವೃಕ್ಷ_READONLY (rval)
	|= (TYPE_READONLY (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (array)))
	    | ವೃಕ್ಷ_READONLY (array));
      ವೃಕ್ಷ_SIDE_EFFECTS (rval)
	|= (TYPE_VOLATILE (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (array)))
	    | ವೃಕ್ಷ_SIDE_EFFECTS (array));
      ವೃಕ್ಷ_THIS_VOLATILE (rval)
	|= (TYPE_VOLATILE (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (array)))
	    /* This was added by rms on 16 Nov 91.
	       It fixes  vol struct foo *a;  a->elts[1]
	       in an inline function.
	       Hope it doesn't break something else.  */
	    | ವೃಕ್ಷ_THIS_VOLATILE (array));
      ret = require_complete_type (loc, rval);
      protected_set_ಅಭಿವ್ಯಕ್ತಿ_location (ret, loc);
      ಯದಿ (non_lvalue)
	ret = non_lvalue_loc (loc, ret);
      ಪ್ರತ್ಯಾಗಮ ret;
    }
  ಅನ್ಯಥಾ
    {
      ವೃಕ್ಷ ar = default_conversion (array);

      ಯದಿ (ar == error_mark_ಗಂಟು)
	ಪ್ರತ್ಯಾಗಮ ar;

      gcc_assert (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (ar)) == POINTER_TYPE);
      gcc_assert (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (ar))) != FUNCTION_TYPE);

      ret = build_indirect_ref (loc, build_ದ್ವಿಮಾನ_op (loc, PLUS_ಅಭಿವ್ಯಕ್ತಿ, ar,
						      index, ಅಸತ್ಯ),
				RO_ARRAY_INDEXING);
      ಯದಿ (non_lvalue)
	ret = non_lvalue_loc (loc, ret);
      ಪ್ರತ್ಯಾಗಮ ret;
    }
}

/* Build an OpenMP array section reference, creating an exact type for the
   resulting expression based on the element type and bounds if possible.  If
   we have variable bounds, create an incomplete array type for the result
   instead.  */

ವೃಕ್ಷ
build_omp_array_section (location_t loc, ವೃಕ್ಷ array, ವೃಕ್ಷ index, ವೃಕ್ಷ length)
{
  ವೃಕ್ಷ type = ವೃಕ್ಷ_TYPE (array);
  gcc_assert (type);

  ವೃಕ್ಷ sectype, eltype = ವೃಕ್ಷ_TYPE (type);

  /* It's not an array or pointer type.  Just reuse the type of the original
     expression as the type of the array section (an error will be raised
     anyway, later).  */
  ಯದಿ (eltype == NULL_ವೃಕ್ಷ || error_operand_p (eltype))
    sectype = ವೃಕ್ಷ_TYPE (array);
  ಅನ್ಯಥಾ
    {
      ವೃಕ್ಷ idxtype = NULL_ವೃಕ್ಷ;

      ಯದಿ (index != NULL_ವೃಕ್ಷ
	  && length != NULL_ವೃಕ್ಷ
	  && INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (index))
	  && INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (length)))
	{
	  ವೃಕ್ಷ ಕೆಳಗಿನ = fold_convert (sizetype, index);
	  ವೃಕ್ಷ ಮೇಲಿನ = fold_convert (sizetype, length);
	  ಮೇಲಿನ = size_binop (PLUS_ಅಭಿವ್ಯಕ್ತಿ, ಕೆಳಗಿನ, ಮೇಲಿನ);
	  ಮೇಲಿನ = size_binop (MINUS_ಅಭಿವ್ಯಕ್ತಿ, ಮೇಲಿನ, size_one_ಗಂಟು);
	  idxtype = build_range_type (sizetype, ಕೆಳಗಿನ, ಮೇಲಿನ);
	}
      ಅನ್ಯಥಾ ಯದಿ ((index == NULL_ವೃಕ್ಷ || integer_zerop (index))
	       && length != NULL_ವೃಕ್ಷ
	       && INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (length)))
	idxtype = build_index_type (length);

      gcc_assert (!error_operand_p (idxtype));

      sectype = c_build_array_type (eltype, idxtype);
    }

  ಪ್ರತ್ಯಾಗಮ build3_loc (loc, OMP_ARRAY_SECTION, sectype, array, index, length);
}


/* Record that REF is used.  This is relevant for undeclared static
   function and declarations referenced from a non-local context.
   ADDRESS indicates whether the address is taken.  */

ಶೂನ್ಯ
mark_decl_used (ವೃಕ್ಷ ref, ತಾರ್ಕಿಕ address)
{
  ಯದಿ (!ref || !DECL_P (ref) || in_alignof)
    ಪ್ರತ್ಯಾಗಮ;

  /* Non-file-scope and non-local reference in nested function.  */
  ತಾರ್ಕಿಕ nonloc_p = current_function_decl && DECL_CONTEXT (ref)
		  && DECL_CONTEXT (current_function_decl)
		  && DECL_CONTEXT (ref) != current_function_decl;

  /* An undeclared static function.  */
  ತಾರ್ಕಿಕ static_p = ವೃಕ್ಷ_CODE (ref) == FUNCTION_DECL
		  && DECL_INITIAL (ref) == NULL_ವೃಕ್ಷ
		  && DECL_EXTERNAL (ref)
		  && !ವೃಕ್ಷ_PUBLIC (ref);

  ಯದಿ (!static_p && !nonloc_p)
    ಪ್ರತ್ಯಾಗಮ;

  /* If we may be in an unevaluated context, delay the decision.  */
  ಯದಿ (in_sizeof || in_typeof || in_countof || in_generic)
    ಪ್ರತ್ಯಾಗಮ record_maybe_used_decl (ref, address);

  ಯದಿ (static_p)
    C_DECL_USED (ref) = 1;

  ಯದಿ (nonloc_p && (VAR_OR_FUNCTION_DECL_P (ref)
		   || ವೃಕ್ಷ_CODE (ref) == PARM_DECL))
    DECL_NONLOCAL (ref) = 1;

  /* Nothing to do anymore.  */
  ಯದಿ (!nonloc_p || C_FUNC_NONLOCAL_CONTEXT (current_function_decl))
    ಪ್ರತ್ಯಾಗಮ;

  /* Filter out the cases where referencing a non-local variable does not
     require a non-local context passed via the static chain.  */
  ಯದಿ (!c_type_variably_modified_p (ವೃಕ್ಷ_TYPE (ref)))
    ವಿಕಲ್ಪ (ವೃಕ್ಷ_CODE (ref))
      {
      ಪಕ್ಷ FUNCTION_DECL:
	/* Use of another local function that requires no context is ok.  */
	ಯದಿ (!C_FUNC_NONLOCAL_CONTEXT (ref) && DECL_INITIAL (ref))
	  ಪ್ರತ್ಯಾಗಮ;
	ಭಙ್ಗ;
      ಪಕ್ಷ VAR_DECL:
	/* Static variables and constexpr are ok, but for the later only
	   when the address is not taken.  */
	ಯದಿ (ವೃಕ್ಷ_STATIC (ref) || (C_DECL_DECLARED_CONSTEXPR (ref) && !address))
	  ಪ್ರತ್ಯಾಗಮ;
	ಭಙ್ಗ;
      ಪಕ್ಷ TYPE_DECL:
	/* A typedef is ok when not for a variably-modified type. */
	ಪ್ರತ್ಯಾಗಮ;
      ಪಕ್ಷ CONST_DECL:
	/* An enumeration constant is ok. */
	ಪ್ರತ್ಯಾಗಮ;
      ಪಕ್ಷ PARM_DECL:
	ಭಙ್ಗ;
      ಪಕ್ಷ LABEL_DECL:
	ಭಙ್ಗ;
      ಸ್ವಭಾವ:
	gcc_unreachable ();
    }

  /* Mark all parent functions up to the nesting level of the variable as
     as needing the non-local context.  */
  ಪ್ರತಿ (ವೃಕ್ಷ cont = current_function_decl; cont; cont = DECL_CONTEXT (cont))
    {
      ಯದಿ (cont == DECL_CONTEXT (ref))
	ಭಙ್ಗ;

      /* There should not be any other type of context used for function
	 except TRANSLATION_UNIT_DECL which we should be able to reach.  */
      gcc_checking_assert (ವೃಕ್ಷ_CODE (cont) == FUNCTION_DECL);

      ಯದಿ (ವೃಕ್ಷ_CODE (cont) == FUNCTION_DECL)
	C_FUNC_NONLOCAL_CONTEXT (cont) = 1;
    }
}


/* Build an external reference to identifier ID.  FUN indicates
   whether this will be used for a function call.  LOC is the source
   location of the identifier.  This sets *TYPE to the type of the
   identifier, which is not the same as the type of the returned value
   for CONST_DECLs defined as enum constants.  If the type of the
   identifier is not available, *TYPE is set to NULL.  */
ವೃಕ್ಷ
build_external_ref (location_t loc, ವೃಕ್ಷ id, ತಾರ್ಕಿಕ fun, ವೃಕ್ಷ *type)
{
  ವೃಕ್ಷ ref;
  ವೃಕ್ಷ decl = lookup_name (id);

  /* In Objective-C, an instance variable (ivar) may be preferred to
     whatever lookup_name() found.  */
  decl = objc_lookup_ivar (decl, id);

  *type = ರಿಕ್ತ;
  ಯದಿ (decl && decl != error_mark_ಗಂಟು)
    {
      ref = decl;
      *type = ವೃಕ್ಷ_TYPE (ref);
      ಯದಿ (DECL_P (decl) && C_DECL_UNDERSPECIFIED (decl))
	error_at (loc, "underspecified %qD referenced in its initializer",
		  decl);
    }
  ಅನ್ಯಥಾ ಯದಿ (fun)
    /* Implicit function declaration.  */
    ref = implicitly_declare (loc, id);
  ಅನ್ಯಥಾ ಯದಿ (decl == error_mark_ಗಂಟು)
    /* Don't complain about something that's already been
       complained about.  */
    ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
  ಅನ್ಯಥಾ
    {
      undeclared_variable (loc, id);
      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
    }

  /* For an OpenMP map clause, we can get better diagnostics for decls with
     unmappable types if we return the decl with an error_mark_node type,
     rather than returning error_mark_node for the decl itself.  */
  ಯದಿ (ವೃಕ್ಷ_TYPE (ref) == error_mark_ಗಂಟು
      && !c_omp_array_section_p)
    ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;

  ಯದಿ (ವೃಕ್ಷ_UNAVAILABLE (ref))
    error_unavailable_use (ref, NULL_ವೃಕ್ಷ);
  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_DEPRECATED (ref))
    warn_deprecated_use (ref, NULL_ವೃಕ್ಷ);

  /* Recursive call does not count as usage.  */
  ಯದಿ (ref != current_function_decl)
    {
      ವೃಕ್ಷ_USED (ref) = 1;
    }

  mark_decl_used (ref, ಅಸತ್ಯ);

  ಯದಿ (ವೃಕ್ಷ_CODE (ref) == CONST_DECL)
    {
      used_types_ಸೇರಿಸು (ವೃಕ್ಷ_TYPE (ref));

      ಯದಿ (warn_cxx_compat
	  && ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (ref)) == ENUMERAL_TYPE
	  && C_TYPE_DEFINED_IN_STRUCT (ವೃಕ್ಷ_TYPE (ref)))
	{
	  warning_at (loc, OPT_Wc___compat,
		      "enum constant defined in struct or union "
		      "is not visible in C++");
	  inform (DECL_SOURCE_LOCATION (ref), "enum constant defined here");
	}

      ref = DECL_INITIAL (ref);
      ವೃಕ್ಷ_CONSTANT (ref) = 1;
    }
  /* C99 6.7.4p3: An inline definition of a function with external
     linkage ... shall not contain a reference to an identifier with
     internal linkage.  */
  ಅನ್ಯಥಾ ಯದಿ (current_function_decl != NULL_ವೃಕ್ಷ
	   && DECL_DECLARED_INLINE_P (current_function_decl)
	   && DECL_EXTERNAL (current_function_decl)
	   && VAR_OR_FUNCTION_DECL_P (ref)
	   && (!VAR_P (ref) || ವೃಕ್ಷ_STATIC (ref))
	   && ! ವೃಕ್ಷ_PUBLIC (ref)
	   && DECL_CONTEXT (ref) != current_function_decl)
    record_inline_static (loc, current_function_decl, ref,
			  csi_internal);

  ಪ್ರತ್ಯಾಗಮ ref;
}

ಸ್ಥಿರ ಸಂರಚನಾ maybe_used_decl *maybe_used_decls;

/* Record that DECL, a reference seen inside sizeof or typeof or _Countof or
   _Generic, might be used if the operand of sizeof is a VLA type or the
   operand of typeof is a variably modified type or the operand of _Countof has
   a variable number of elements or the operand of _Generic is the one selected
   as the result.  */

ಸ್ಥಿರ ಶೂನ್ಯ
record_maybe_used_decl (ವೃಕ್ಷ decl, ತಾರ್ಕಿಕ address)
{
  ಸಂರಚನಾ maybe_used_decl *t = XOBNEW (&parser_obstack, ಸಂರಚನಾ maybe_used_decl);
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

ಶೂನ್ಯ
ತೆಗೆ_maybe_used (ತಾರ್ಕಿಕ used)
{
  ಸಂರಚನಾ maybe_used_decl *p = maybe_used_decls;
  ಪೂರ್ಣಾಙ್ಕ cur_level = in_sizeof + in_typeof + in_countof + in_generic;
  ಯಾವತ್ (p && p->level > cur_level)
    {
      ಯದಿ (used)
	{
	  ಯದಿ (cur_level == 0)
	    mark_decl_used (p->decl, p->address);
	  ಅನ್ಯಥಾ
	    p->level = cur_level;
	}
      p = p->next;
    }
  ಯದಿ (!used || cur_level == 0)
    maybe_used_decls = p;
}

/* Pop the stack of decls possibly used inside sizeof or typeof or _Countof or
   _Generic, without acting on them, and return the pointer to the previous top
   of the stack.  This for use at the end of a default generic association when
   it is not yet known whether the expression is used.  If it later turns out
   the expression is used (or treated as used before C23), restore_maybe_used
   should be called on the return value followed by pop_maybe_used (true);
   otherwise, the return value can be discarded.  */

ಸಂರಚನಾ maybe_used_decl *
save_maybe_used ()
{
  ಸಂರಚನಾ maybe_used_decl *p = maybe_used_decls, *orig = p;
  ಪೂರ್ಣಾಙ್ಕ cur_level = in_sizeof + in_typeof + in_countof + in_generic;
  ಯಾವತ್ (p && p->level > cur_level)
    p = p->next;
  maybe_used_decls = p;
  ಪ್ರತ್ಯಾಗಮ orig;
}

/* Restore the stack of decls possibly used inside sizeof or typeof or _Countof
   or _Generic returned by save_maybe_used.  It is required that the stack is
   at exactly the point where it was left by save_maybe_used.  */

ಶೂನ್ಯ
restore_maybe_used (ಸಂರಚನಾ maybe_used_decl *ರಾಶಿ)
{
  maybe_used_decls = ರಾಶಿ;
}

/* Return the result of sizeof applied to EXPR.  */

ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ
c_ಅಭಿವ್ಯಕ್ತಿ_sizeof_ಅಭಿವ್ಯಕ್ತಿ (location_t loc, ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ)
{
  ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ ret;
  ಯದಿ (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ == error_mark_ಗಂಟು)
    {
      ret.ಮೌಲ್ಯ = error_mark_ಗಂಟು;
      ret.original_code = ERROR_MARK;
      ret.original_type = ರಿಕ್ತ;
      ret.m_decimal = 0;
      ತೆಗೆ_maybe_used (ಅಸತ್ಯ);
    }
  ಅನ್ಯಥಾ
    {
      ತಾರ್ಕಿಕ ಅಭಿವ್ಯಕ್ತಿ_const_operands = ಸತ್ಯ;

      ಯದಿ (ವೃಕ್ಷ_CODE (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ) == PARM_DECL
	  && C_ARRAY_PARAMETER (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ))
	{
	  auto_diagnostic_group d;
	  ಯದಿ (warning_at (loc, OPT_Wsizeof_array_argument,
			  "%<sizeof%> on array function parameter %qE will "
			  "return size of %qT", ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ,
			  ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ)))
	    inform (DECL_SOURCE_LOCATION (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ), "declared here");
	}
      ವೃಕ್ಷ folded_ಅಭಿವ್ಯಕ್ತಿ = c_fully_fold (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, require_constant_ಮೌಲ್ಯ,
				       &ಅಭಿವ್ಯಕ್ತಿ_const_operands);
      ret.ಮೌಲ್ಯ = c_sizeof (loc, ವೃಕ್ಷ_TYPE (folded_ಅಭಿವ್ಯಕ್ತಿ));
      c_last_sizeof_arg = ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ;
      c_last_sizeof_loc = loc;
      ret.original_code = SIZEOF_ಅಭಿವ್ಯಕ್ತಿ;
      ret.original_type = ರಿಕ್ತ;
      ret.m_decimal = 0;
      ಯದಿ (C_TYPE_VARIABLE_SIZE (ವೃಕ್ಷ_TYPE (folded_ಅಭಿವ್ಯಕ್ತಿ)))
	{
	  /* sizeof is evaluated when given a vla (C99 6.5.3.4p2).  */
	  ret.ಮೌಲ್ಯ = build2 (C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (ret.ಮೌಲ್ಯ),
			      folded_ಅಭಿವ್ಯಕ್ತಿ, ret.ಮೌಲ್ಯ);
	  C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_NON_CONST (ret.ಮೌಲ್ಯ) = !ಅಭಿವ್ಯಕ್ತಿ_const_operands;
	  SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (ret.ಮೌಲ್ಯ, loc);
	}
      ತೆಗೆ_maybe_used (C_TYPE_VARIABLE_SIZE (ವೃಕ್ಷ_TYPE (folded_ಅಭಿವ್ಯಕ್ತಿ)));
    }
  ಪ್ರತ್ಯಾಗಮ ret;
}

/* Return the result of sizeof applied to T, a structure for the type
   name passed to sizeof (rather than the type itself).  LOC is the
   location of the original expression.  */

ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ
c_ಅಭಿವ್ಯಕ್ತಿ_sizeof_type (location_t loc, ಸಂರಚನಾ c_type_name *t)
{
  ವೃಕ್ಷ type;
  ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ ret;
  ವೃಕ್ಷ type_ಅಭಿವ್ಯಕ್ತಿ = NULL_ವೃಕ್ಷ;
  ತಾರ್ಕಿಕ type_ಅಭಿವ್ಯಕ್ತಿ_const = ಸತ್ಯ;
  type = groktypename (t, &type_ಅಭಿವ್ಯಕ್ತಿ, &type_ಅಭಿವ್ಯಕ್ತಿ_const);
  ret.ಮೌಲ್ಯ = c_sizeof (loc, type);
  c_last_sizeof_arg = type;
  c_last_sizeof_loc = loc;
  ret.original_code = SIZEOF_ಅಭಿವ್ಯಕ್ತಿ;
  ret.original_type = ರಿಕ್ತ;
  ret.m_decimal = 0;
  ಯದಿ (type == error_mark_ಗಂಟು)
    {
      ret.ಮೌಲ್ಯ = error_mark_ಗಂಟು;
      ret.original_code = ERROR_MARK;
    }
  ಅನ್ಯಥಾ
  ಯದಿ ((type_ಅಭಿವ್ಯಕ್ತಿ || ವೃಕ್ಷ_CODE (ret.ಮೌಲ್ಯ) == INTEGER_CST)
      && C_TYPE_VARIABLE_SIZE (type))
    {
      /* If the type is a [*] array, it is a VLA but is represented as
	 having a size of zero.  In such a case we must ensure that
	 the result of sizeof does not get folded to a constant by
	 c_fully_fold, because if the size is evaluated the result is
	 not constant and so constraints on zero or negative size
	 arrays must not be applied when this sizeof call is inside
	 another array declarator.  */
      ಯದಿ (!type_ಅಭಿವ್ಯಕ್ತಿ)
	type_ಅಭಿವ್ಯಕ್ತಿ = integer_zero_ಗಂಟು;
      ret.ಮೌಲ್ಯ = build2 (C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (ret.ಮೌಲ್ಯ),
			  type_ಅಭಿವ್ಯಕ್ತಿ, ret.ಮೌಲ್ಯ);
      C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_NON_CONST (ret.ಮೌಲ್ಯ) = !type_ಅಭಿವ್ಯಕ್ತಿ_const;
    }
  ತೆಗೆ_maybe_used (type != error_mark_ಗಂಟು
		  ? C_TYPE_VARIABLE_SIZE (type) : ಅಸತ್ಯ);
  ಪ್ರತ್ಯಾಗಮ ret;
}

ಸ್ಥಿರ ತಾರ್ಕಿಕ
ತುದಿ_array_vla_p (const_ವೃಕ್ಷ type)
{
  ಯದಿ (ವೃಕ್ಷ_CODE (type) != ARRAY_TYPE)
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

  ವೃಕ್ಷ d = TYPE_DOMAIN (type);

  ಯದಿ (!d)
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
  ಯದಿ (!TYPE_MAX_ಮೌಲ್ಯ (d))
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

  ಪ್ರತ್ಯಾಗಮ ವೃಕ್ಷ_CODE (TYPE_MAX_ಮೌಲ್ಯ (d)) != INTEGER_CST
	 || ವೃಕ್ಷ_CODE (TYPE_MIN_ಮೌಲ್ಯ (d)) != INTEGER_CST;
}

/* Return the result of countof applied to EXPR.  */

ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ
c_ಅಭಿವ್ಯಕ್ತಿ_countof_ಅಭಿವ್ಯಕ್ತಿ (location_t loc, ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ)
{
  ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ ret;
  ಯದಿ (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ == error_mark_ಗಂಟು)
    {
      ret.ಮೌಲ್ಯ = error_mark_ಗಂಟು;
      ret.original_code = ERROR_MARK;
      ret.original_type = ರಿಕ್ತ;
      ret.m_decimal = 0;
      ತೆಗೆ_maybe_used (ಅಸತ್ಯ);
    }
  ಅನ್ಯಥಾ
    {
      ತಾರ್ಕಿಕ ಅಭಿವ್ಯಕ್ತಿ_const_operands = ಸತ್ಯ;

      ವೃಕ್ಷ folded_ಅಭಿವ್ಯಕ್ತಿ = c_fully_fold (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ, require_constant_ಮೌಲ್ಯ,
				       &ಅಭಿವ್ಯಕ್ತಿ_const_operands);
      ret.ಮೌಲ್ಯ = c_countof_type (loc, ವೃಕ್ಷ_TYPE (folded_ಅಭಿವ್ಯಕ್ತಿ));
      c_last_sizeof_arg = ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ;
      c_last_sizeof_loc = loc;
      ret.original_code = COUNTOF_ಅಭಿವ್ಯಕ್ತಿ;
      ret.original_type = ರಿಕ್ತ;
      ret.m_decimal = 0;
      ಯದಿ (ತುದಿ_array_vla_p (ವೃಕ್ಷ_TYPE (folded_ಅಭಿವ್ಯಕ್ತಿ)))
	{
	  /* countof is evaluated when given a vla.  */
	  ret.ಮೌಲ್ಯ = build2 (C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (ret.ಮೌಲ್ಯ),
			      folded_ಅಭಿವ್ಯಕ್ತಿ, ret.ಮೌಲ್ಯ);
	  C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_NON_CONST (ret.ಮೌಲ್ಯ) = !ಅಭಿವ್ಯಕ್ತಿ_const_operands;
	  SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (ret.ಮೌಲ್ಯ, loc);
	}
      ತೆಗೆ_maybe_used (ತುದಿ_array_vla_p (ವೃಕ್ಷ_TYPE (folded_ಅಭಿವ್ಯಕ್ತಿ)));
    }
  ಪ್ರತ್ಯಾಗಮ ret;
}

/* Return the result of countof applied to T, a structure for the type
   name passed to countof (rather than the type itself).  LOC is the
   location of the original expression.  */

ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ
c_ಅಭಿವ್ಯಕ್ತಿ_countof_type (location_t loc, ಸಂರಚನಾ c_type_name *t)
{
  ವೃಕ್ಷ type;
  ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ ret;
  ವೃಕ್ಷ type_ಅಭಿವ್ಯಕ್ತಿ = NULL_ವೃಕ್ಷ;
  ತಾರ್ಕಿಕ type_ಅಭಿವ್ಯಕ್ತಿ_const = ಸತ್ಯ;
  type = groktypename (t, &type_ಅಭಿವ್ಯಕ್ತಿ, &type_ಅಭಿವ್ಯಕ್ತಿ_const);
  ret.ಮೌಲ್ಯ = c_countof_type (loc, type);
  c_last_sizeof_arg = type;
  c_last_sizeof_loc = loc;
  ret.original_code = COUNTOF_ಅಭಿವ್ಯಕ್ತಿ;
  ret.original_type = ರಿಕ್ತ;
  ret.m_decimal = 0;
  ಯದಿ (type == error_mark_ಗಂಟು)
    {
      ret.ಮೌಲ್ಯ = error_mark_ಗಂಟು;
      ret.original_code = ERROR_MARK;
    }
  ಅನ್ಯಥಾ
  ಯದಿ ((type_ಅಭಿವ್ಯಕ್ತಿ || ವೃಕ್ಷ_CODE (ret.ಮೌಲ್ಯ) == INTEGER_CST)
      && ತುದಿ_array_vla_p (type))
    {
      /* If the type is a [*] array, it is a VLA but is represented as
	 having a size of zero.  In such a case we must ensure that
	 the result of countof does not get folded to a constant by
	 c_fully_fold, because if the number of elements is evaluated
	 the result is not constant and so
	 constraints on zero or negative size arrays must not be applied
	 when this countof call is inside another array declarator.  */
      ಯದಿ (!type_ಅಭಿವ್ಯಕ್ತಿ)
	type_ಅಭಿವ್ಯಕ್ತಿ = integer_zero_ಗಂಟು;
      ret.ಮೌಲ್ಯ = build2 (C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (ret.ಮೌಲ್ಯ),
			  type_ಅಭಿವ್ಯಕ್ತಿ, ret.ಮೌಲ್ಯ);
      C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_NON_CONST (ret.ಮೌಲ್ಯ) = !type_ಅಭಿವ್ಯಕ್ತಿ_const;
    }
  ತೆಗೆ_maybe_used (type != error_mark_ಗಂಟು ? ತುದಿ_array_vla_p (type) : ಅಸತ್ಯ);
  ಪ್ರತ್ಯಾಗಮ ret;
}

/* Return the result of maxof applied to T, a structure for the type
   name passed to maxof (rather than the type itself).  LOC is the
   location of the original expression.  */

ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ
c_ಅಭಿವ್ಯಕ್ತಿ_maxof_type (location_t loc, ಸಂರಚನಾ c_type_name *t)
{
  ವೃಕ್ಷ type;
  ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ ret;
  ವೃಕ್ಷ type_ಅಭಿವ್ಯಕ್ತಿ = NULL_ವೃಕ್ಷ;
  ತಾರ್ಕಿಕ type_ಅಭಿವ್ಯಕ್ತಿ_const = ಸತ್ಯ;
  type = groktypename (t, &type_ಅಭಿವ್ಯಕ್ತಿ, &type_ಅಭಿವ್ಯಕ್ತಿ_const);
  ret.ಮೌಲ್ಯ = c_maxof_type (loc, type);
  c_last_sizeof_arg = type;
  c_last_sizeof_loc = loc;
  ret.original_code = MAXOF_ಅಭಿವ್ಯಕ್ತಿ;
  ret.original_type = ರಿಕ್ತ;
  ret.m_decimal = 0;
  ಯದಿ (type == error_mark_ಗಂಟು)
    {
      ret.ಮೌಲ್ಯ = error_mark_ಗಂಟು;
      ret.original_code = ERROR_MARK;
    }
  ತೆಗೆ_maybe_used (type != error_mark_ಗಂಟು);
  ಪ್ರತ್ಯಾಗಮ ret;
}

/* Return the result of minof applied to T, a structure for the type
   name passed to minof (rather than the type itself).  LOC is the
   location of the original expression.  */

ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ
c_ಅಭಿವ್ಯಕ್ತಿ_minof_type (location_t loc, ಸಂರಚನಾ c_type_name *t)
{
  ವೃಕ್ಷ type;
  ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ ret;
  ವೃಕ್ಷ type_ಅಭಿವ್ಯಕ್ತಿ = NULL_ವೃಕ್ಷ;
  ತಾರ್ಕಿಕ type_ಅಭಿವ್ಯಕ್ತಿ_const = ಸತ್ಯ;
  type = groktypename (t, &type_ಅಭಿವ್ಯಕ್ತಿ, &type_ಅಭಿವ್ಯಕ್ತಿ_const);
  ret.ಮೌಲ್ಯ = c_minof_type (loc, type);
  c_last_sizeof_arg = type;
  c_last_sizeof_loc = loc;
  ret.original_code = MINOF_ಅಭಿವ್ಯಕ್ತಿ;
  ret.original_type = ರಿಕ್ತ;
  ret.m_decimal = 0;
  ಯದಿ (type == error_mark_ಗಂಟು)
    {
      ret.ಮೌಲ್ಯ = error_mark_ಗಂಟು;
      ret.original_code = ERROR_MARK;
    }
  ತೆಗೆ_maybe_used (type != error_mark_ಗಂಟು);
  ಪ್ರತ್ಯಾಗಮ ret;
}

/* Build a function call to function FUNCTION with parameters PARAMS.
   The function call is at LOC.
   PARAMS is a list--a chain of TREE_LIST nodes--in which the
   TREE_VALUE of each node is a parameter-expression.
   FUNCTION's data type may be a function type or a pointer-to-function.  */

ವೃಕ್ಷ
build_function_call (location_t loc, ವೃಕ್ಷ function, ವೃಕ್ಷ params)
{
  vec<ವೃಕ್ಷ, va_gc> *v;
  ವೃಕ್ಷ ret;

  vec_alloc (v, list_length (params));
  ಪ್ರತಿ (; params; params = ವೃಕ್ಷ_CHAIN (params))
    v->quick_ತಳ್ಳು (ವೃಕ್ಷ_ಮೌಲ್ಯ (params));
  ret = c_build_function_call_vec (loc, vNULL, function, v, ರಿಕ್ತ);
  vec_free (v);
  ಪ್ರತ್ಯಾಗಮ ret;
}

/* Give a note about the location of the declaration of DECL,
   or, failing that, a pertinent declaration for FUNCTION_EXPR.  */

ಸ್ಥಿರ ಶೂನ್ಯ
inform_declaration (ವೃಕ್ಷ decl, ವೃಕ್ಷ function_ಅಭಿವ್ಯಕ್ತಿ)
{
  ಯದಿ (decl && (ವೃಕ್ಷ_CODE (decl) != FUNCTION_DECL
	       || !DECL_IS_UNDECLARED_BUILTIN (decl)))
    inform (DECL_SOURCE_LOCATION (decl), "declared here");
  ಅನ್ಯಥಾ ಯದಿ (function_ಅಭಿವ್ಯಕ್ತಿ)
    ವಿಕಲ್ಪ (ವೃಕ್ಷ_CODE (function_ಅಭಿವ್ಯಕ್ತಿ))
      {
      ಸ್ವಭಾವ:
	ಭಙ್ಗ;
      ಪಕ್ಷ COMPONENT_REF:
	/* Show the decl of the pertinent field (e.g. for callback
	   fields in a struct.  */
	{
	  ವೃಕ್ಷ field_decl = ವೃಕ್ಷ_OPERAND (function_ಅಭಿವ್ಯಕ್ತಿ, 1);
	  ಯದಿ (location_t loc = DECL_SOURCE_LOCATION (field_decl))
	    inform (loc, "declared here");
	}
	ಭಙ್ಗ;
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

ವೃಕ್ಷ
build_function_call_vec (location_t loc, vec<location_t> arg_loc,
			 ವೃಕ್ಷ function, vec<ವೃಕ್ಷ, va_gc> *params,
			 vec<ವೃಕ್ಷ, va_gc> *origtypes, ವೃಕ್ಷ orig_fundecl)
{
  ವೃಕ್ಷ fntype, fundecl = NULL_ವೃಕ್ಷ;
  ವೃಕ್ಷ name = NULL_ವೃಕ್ಷ, result;
  ವೃಕ್ಷ tem;
  ಪೂರ್ಣಾಙ್ಕ nargs;
  ವೃಕ್ಷ *argarray;


  /* Strip NON_LVALUE_EXPRs, etc., since we aren't using as an lvalue.  */
  STRIP_TYPE_NOPS (function);

  /* Convert anything with function type to a pointer-to-function.  */
  ಯದಿ (ವೃಕ್ಷ_CODE (function) == FUNCTION_DECL)
    {
      name = DECL_NAME (function);

      ಯದಿ (flag_tm)
	tm_malloc_replacement (function);
      fundecl = function;
      ಯದಿ (!orig_fundecl)
	orig_fundecl = fundecl;
      /* Atomic functions have type checking/casting already done.  They are
	 often rewritten and don't match the original parameter list.  */
      ಯದಿ (name && startswith (IDENTIFIER_POINTER (name), "__atomic_"))
        origtypes = ರಿಕ್ತ;
    }
  ಯದಿ (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (function)) == FUNCTION_TYPE)
    function = function_to_pointer_conversion (loc, function);

  /* For Objective-C, convert any calls via a cast to OBJC_TYPE_REF
     expressions, like those used for ObjC messenger dispatches.  */
  ಯದಿ (params && !params->is_empty ())
    function = objc_rewrite_function_call (function, (*params)[0]);

  function = c_fully_fold (function, ಅಸತ್ಯ, ರಿಕ್ತ);

  fntype = ವೃಕ್ಷ_TYPE (function);

  ಯದಿ (ವೃಕ್ಷ_CODE (fntype) == ERROR_MARK)
    ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;

  ಯದಿ (!(ವೃಕ್ಷ_CODE (fntype) == POINTER_TYPE
	&& ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (fntype)) == FUNCTION_TYPE))
    {
      ಯದಿ (!flag_diagnostics_show_caret && !STATEMENT_CLASS_P (function))
	error_at (loc,
		  "called object %qE is not a function or function pointer",
		  function);
      ಅನ್ಯಥಾ ಯದಿ (DECL_P (function))
	{
	  auto_diagnostic_group d;
	  error_at (loc,
		    "called object %qD is not a function or function pointer",
		    function);
	  inform_declaration (function, NULL_ವೃಕ್ಷ);
	}
      ಅನ್ಯಥಾ
	error_at (loc,
		  "called object is not a function or function pointer");
      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
    }

  ಯದಿ (fundecl && ವೃಕ್ಷ_THIS_VOLATILE (fundecl))
    current_function_returns_abnormally = 1;

  /* fntype now gets the type of function pointed to.  */
  fntype = ವೃಕ್ಷ_TYPE (fntype);
  ವೃಕ್ಷ return_type = ವೃಕ್ಷ_TYPE (fntype);

  /* Convert the parameters to the types declared in the
     function prototype, or apply default promotions.  */

  nargs = convert_arguments (loc, arg_loc, fntype, params,
			     origtypes, function, fundecl);
  ಯದಿ (nargs < 0)
    ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;

  /* Check that the function is called through a compatible prototype.
     If it is not, warn.  */
  ಯದಿ (CONVERT_ಅಭಿವ್ಯಕ್ತಿ_P (function)
      && ವೃಕ್ಷ_CODE (tem = ವೃಕ್ಷ_OPERAND (function, 0)) == ADDR_ಅಭಿವ್ಯಕ್ತಿ
      && ವೃಕ್ಷ_CODE (tem = ವೃಕ್ಷ_OPERAND (tem, 0)) == FUNCTION_DECL
      && !comptypes (fntype, ವೃಕ್ಷ_TYPE (tem)))
    {
      /* This situation leads to run-time undefined behavior.  We can't,
	 therefore, simply error unless we can prove that all possible
	 executions of the program must execute the code.  */
      warning_at (loc, 0, "function called through a non-compatible type");

      ಯದಿ (VOID_TYPE_P (return_type)
	  && TYPE_QUALS (return_type) != TYPE_UNQUALIFIED)
	pedwarn (loc, 0,
		 "function with qualified void return type called");
     }

  argarray = vec_safe_address (params);

  /* Check that arguments to builtin functions match the expectations.  */
  ಯದಿ (fundecl
      && fndecl_built_in_p (fundecl)
      && !check_builtin_function_arguments (loc, arg_loc, fundecl,
					    orig_fundecl, nargs, argarray))
    ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;

  /* Check that the arguments to the function are valid.  */
  ತಾರ್ಕಿಕ warned_p = check_function_arguments (loc, fundecl, fntype,
					    nargs, argarray, &arg_loc,
					    comptypes);

  ಯದಿ (TYPE_QUALS (return_type) != TYPE_UNQUALIFIED
      && !VOID_TYPE_P (return_type))
    return_type = c_build_qualified_type (return_type, TYPE_UNQUALIFIED);
  ಯದಿ (name != NULL_ವೃಕ್ಷ
      && startswith (IDENTIFIER_POINTER (name), "__builtin_"))
    {
      ಯದಿ (require_constant_ಮೌಲ್ಯ)
	result
	  = fold_build_call_array_initializer_loc (loc, return_type,
						   function, nargs, argarray);
      ಅನ್ಯಥಾ
	result = fold_build_call_array_loc (loc, return_type,
					    function, nargs, argarray);
      ಯದಿ (ವೃಕ್ಷ_CODE (result) == NOP_ಅಭಿವ್ಯಕ್ತಿ
	  && ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_OPERAND (result, 0)) == INTEGER_CST)
	STRIP_TYPE_NOPS (result);
    }
  ಅನ್ಯಥಾ
    result = build_call_array_loc (loc, return_type,
				   function, nargs, argarray);
  /* If -Wnonnull warning has been diagnosed, avoid diagnosing it again
     later.  */
  ಯದಿ (warned_p && ವೃಕ್ಷ_CODE (result) == CALL_ಅಭಿವ್ಯಕ್ತಿ)
    suppress_warning (result, OPT_Wnonnull);

  /* In this improbable scenario, a nested function returns a VM type.
     Create a TARGET_EXPR so that the call always has a LHS, much as
     what the C++ FE does for functions returning non-PODs.  */
  ಯದಿ (c_type_variably_modified_p (ವೃಕ್ಷ_TYPE (fntype)))
    {
      ವೃಕ್ಷ tmp = create_tmp_var_raw (ವೃಕ್ಷ_TYPE (fntype));
      result = build4 (TARGET_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (fntype), tmp, result,
		       NULL_ವೃಕ್ಷ, NULL_ವೃಕ್ಷ);
    }

  ಯದಿ (VOID_TYPE_P (ವೃಕ್ಷ_TYPE (result)))
    {
      ಯದಿ (TYPE_QUALS (ವೃಕ್ಷ_TYPE (result)) != TYPE_UNQUALIFIED)
	pedwarn (loc, 0,
		 "function with qualified void return type called");
      ಪ್ರತ್ಯಾಗಮ result;
    }
  ಪ್ರತ್ಯಾಗಮ require_complete_type (loc, result);
}

/* Like build_function_call_vec, but call also resolve_overloaded_builtin.  */

ವೃಕ್ಷ
c_build_function_call_vec (location_t loc, ಧ್ರುವ vec<location_t> &arg_loc,
			   ವೃಕ್ಷ function, vec<ವೃಕ್ಷ, va_gc> *params,
			   vec<ವೃಕ್ಷ, va_gc> *origtypes)
{
  /* Strip NON_LVALUE_EXPRs, etc., since we aren't using as an lvalue.  */
  STRIP_TYPE_NOPS (function);

  /* Convert anything with function type to a pointer-to-function.  */
  ಯದಿ (ವೃಕ್ಷ_CODE (function) == FUNCTION_DECL)
    {
      /* Implement type-directed function overloading for builtins.
	 resolve_overloaded_builtin and targetm.resolve_overloaded_builtin
	 handle all the type checking.  The result is a complete expression
	 that implements this function call.  */
      ವೃಕ್ಷ tem = resolve_overloaded_builtin (loc, function, params);
      ಯದಿ (tem)
	ಪ್ರತ್ಯಾಗಮ tem;
    }
  ಪ್ರತ್ಯಾಗಮ build_function_call_vec (loc, arg_loc, function, params, origtypes);
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

ಸ್ಥಿರ ವೃಕ್ಷ
convert_argument (location_t ploc, ವೃಕ್ಷ function, ವೃಕ್ಷ fundecl,
		  ವೃಕ್ಷ type, ವೃಕ್ಷ origtype, ವೃಕ್ಷ val, ವೃಕ್ಷ valtype,
		  ತಾರ್ಕಿಕ npc, ವೃಕ್ಷ rname, ಪೂರ್ಣಾಙ್ಕ parmnum, ಪೂರ್ಣಾಙ್ಕ argnum,
		  ತಾರ್ಕಿಕ excess_precision, ಪೂರ್ಣಾಙ್ಕ warnopt)
{
  /* Formal parm type is specified by a function prototype.  */

  ಯದಿ (type == error_mark_ಗಂಟು || !COMPLETE_TYPE_P (type))
    {
      error_at (ploc, "type of formal parameter %d is incomplete",
		parmnum + 1);
      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
    }

  /* Optionally warn about conversions that differ from the default
     conversions.  */
  ಯದಿ (warn_traditional_conversion || warn_traditional)
    {
      ಯದಿ (INTEGRAL_TYPE_P (type)
	  && SCALAR_FLOAT_TYPE_P (valtype))
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as integer rather "
		    "than floating due to prototype",
		    argnum, rname);
      ಯದಿ (INTEGRAL_TYPE_P (type)
	  && ವೃಕ್ಷ_CODE (valtype) == COMPLEX_TYPE)
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as integer rather "
		    "than complex due to prototype",
		    argnum, rname);
      ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (type) == COMPLEX_TYPE
	       && SCALAR_FLOAT_TYPE_P (valtype))
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as complex rather "
		    "than floating due to prototype",
		    argnum, rname);
      ಅನ್ಯಥಾ ಯದಿ (SCALAR_FLOAT_TYPE_P (type)
	       && INTEGRAL_TYPE_P (valtype))
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as floating rather "
		    "than integer due to prototype",
		    argnum, rname);
      ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (type) == COMPLEX_TYPE
	       && INTEGRAL_TYPE_P (valtype))
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as complex rather "
		    "than integer due to prototype",
		    argnum, rname);
      ಅನ್ಯಥಾ ಯದಿ (SCALAR_FLOAT_TYPE_P (type)
	       && ವೃಕ್ಷ_CODE (valtype) == COMPLEX_TYPE)
	warning_at (ploc, OPT_Wtraditional_conversion,
		    "passing argument %d of %qE as floating rather "
		    "than complex due to prototype",
		    argnum, rname);
      /* ??? At some point, messages should be written about
	 conversions between complex types, but that's too messy
	 to do now.  */
      ಅನ್ಯಥಾ ಯದಿ (SCALAR_FLOAT_TYPE_P (type)
	       && SCALAR_FLOAT_TYPE_P (valtype))
	{
	  unsigned ಪೂರ್ಣಾಙ್ಕ formal_prec = TYPE_PRECISION (type);

	  /* Warn if any argument is passed as `float',
	     since without a prototype it would be `double'.  */
	  ಯದಿ (formal_prec == TYPE_PRECISION (float_type_ಗಂಟು)
	      && type != dfloat32_type_ಗಂಟು)
	    warning_at (ploc, 0,
			"passing argument %d of %qE as %<float%> "
			"rather than %<double%> due to prototype",
			argnum, rname);

	  /* Warn if mismatch between argument and prototype
	     for decimal float types.  Warn of conversions with
	     binary float types and of precision narrowing due to
	     prototype.  */
	  ಅನ್ಯಥಾ ಯದಿ (type != valtype
		   && (type == dfloat32_type_ಗಂಟು
		       || type == dfloat64_type_ಗಂಟು
		       || type == dfloat128_type_ಗಂಟು
		       || valtype == dfloat32_type_ಗಂಟು
		       || valtype == dfloat64_type_ಗಂಟು
		       || valtype == dfloat128_type_ಗಂಟು)
		   && (formal_prec
		       <= TYPE_PRECISION (valtype)
		       || (type == dfloat128_type_ಗಂಟು
			   && (valtype
			       != dfloat64_type_ಗಂಟು
			       && (valtype
				   != dfloat32_type_ಗಂಟು)))
		       || (type == dfloat64_type_ಗಂಟು
			   && (valtype
			       != dfloat32_type_ಗಂಟು))))
	    warning_at (ploc, 0,
			"passing argument %d of %qE as %qT "
			"rather than %qT due to prototype",
			argnum, rname, type, valtype);

	}
      /* Detect integer changing in width or signedness.
	 These warnings are only activated with
	 -Wtraditional-conversion, not with -Wtraditional.  */
      ಅನ್ಯಥಾ ಯದಿ (warn_traditional_conversion
	       && INTEGRAL_TYPE_P (type)
	       && INTEGRAL_TYPE_P (valtype))
	{
	  unsigned ಪೂರ್ಣಾಙ್ಕ formal_prec = TYPE_PRECISION (type);
	  ವೃಕ್ಷ would_have_been = default_conversion (val);
	  ವೃಕ್ಷ type1 = ವೃಕ್ಷ_TYPE (would_have_been);

	  ಯದಿ (val == error_mark_ಗಂಟು)
	    /* VAL could have been of incomplete type.  */;
	  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (type) == ENUMERAL_TYPE
		   && (TYPE_MAIN_VARIANT (type)
		       == TYPE_MAIN_VARIANT (valtype)))
	    /* No warning if function asks for enum
	       and the actual arg is that enum type.  */
	    ;
	  ಅನ್ಯಥಾ ಯದಿ (formal_prec != TYPE_PRECISION (type1))
	    warning_at (ploc, OPT_Wtraditional_conversion,
			"passing argument %d of %qE "
			"with different width due to prototype",
			argnum, rname);
	  ಅನ್ಯಥಾ ಯದಿ (TYPE_UNSIGNED (type) == TYPE_UNSIGNED (type1))
	    ;
	  /* Don't complain if the formal parameter type
	     is an enum, because we can't tell now whether
	     the value was an enum--even the same enum.  */
	  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (type) == ENUMERAL_TYPE)
	    ;
	  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (val) == INTEGER_CST
		   && int_fits_type_p (val, type))
	    /* Change in signedness doesn't matter
	       if a constant value is unaffected.  */
	    ;
	  /* If the value is extended from a narrower
	     unsigned type, it doesn't matter whether we
	     pass it as signed or unsigned; the value
	     certainly is the same either way.  */
	  ಅನ್ಯಥಾ ಯದಿ (TYPE_PRECISION (valtype) < TYPE_PRECISION (type)
		   && TYPE_UNSIGNED (valtype))
	    ;
	  ಅನ್ಯಥಾ ಯದಿ (TYPE_UNSIGNED (type))
	    warning_at (ploc, OPT_Wtraditional_conversion,
			"passing argument %d of %qE "
			"as unsigned due to prototype",
			argnum, rname);
	  ಅನ್ಯಥಾ
	    warning_at (ploc, OPT_Wtraditional_conversion,
			"passing argument %d of %qE "
			"as signed due to prototype",
			argnum, rname);
	}
    }

  /* Possibly restore an EXCESS_PRECISION_EXPR for the
     sake of better warnings from convert_and_check.  */
  ಯದಿ (excess_precision)
    val = build1 (EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ, valtype, val);

  ವೃಕ್ಷ parmval = convert_for_assignment (ploc, ploc, type,
					 val, origtype, ic_argpass,
					 npc, fundecl, function,
					 parmnum + 1, warnopt);
  ಪ್ರತ್ಯಾಗಮ parmval;
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

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ
convert_arguments (location_t loc, vec<location_t> arg_loc, ವೃಕ್ಷ fntype,
		   vec<ವೃಕ್ಷ, va_gc> *ಮೌಲ್ಯಗಳು, vec<ವೃಕ್ಷ, va_gc> *origtypes,
		   ವೃಕ್ಷ function, ವೃಕ್ಷ fundecl)
{
  ವೃಕ್ಷ typelist = TYPE_ARG_TYPES (fntype);
  unsigned ಪೂರ್ಣಾಙ್ಕ parmnum;
  ತಾರ್ಕಿಕ error_args = ಅಸತ್ಯ;
  ಧ್ರುವ ತಾರ್ಕಿಕ type_generic = fundecl
    && lookup_attribute ("type generic", TYPE_ATTRIBUTES (ವೃಕ್ಷ_TYPE (fundecl)));
  ತಾರ್ಕಿಕ type_generic_remove_excess_precision = ಅಸತ್ಯ;
  ತಾರ್ಕಿಕ type_generic_overflow_p = ಅಸತ್ಯ;
  ತಾರ್ಕಿಕ type_generic_bit_query = ಅಸತ್ಯ;
  ವೃಕ್ಷ selector;

  /* Change pointer to function to the function itself for
     diagnostics.  */
  ಯದಿ (ವೃಕ್ಷ_CODE (function) == ADDR_ಅಭಿವ್ಯಕ್ತಿ
      && ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_OPERAND (function, 0)) == FUNCTION_DECL)
    function = ವೃಕ್ಷ_OPERAND (function, 0);

  /* Handle an ObjC selector specially for diagnostics.  */
  selector = objc_message_selector ();

  /* For a call to a built-in function declared without a prototype,
     set to the built-in function's argument list.  */
  ವೃಕ್ಷ builtin_typelist = NULL_ವೃಕ್ಷ;

  /* For type-generic built-in functions, determine whether excess
     precision should be removed (classification) or not
     (comparison).  */
  ಯದಿ (fundecl
      && fndecl_built_in_p (fundecl, BUILT_IN_NORMAL))
    {
      built_in_function code = DECL_FUNCTION_CODE (fundecl);
      ಯದಿ (C_DECL_BUILTIN_PROTOTYPE (fundecl))
	{
	  /* For a call to a built-in function declared without a prototype
	     use the types of the parameters of the internal built-in to
	     match those of the arguments to.  */
	  ಯದಿ (ವೃಕ್ಷ bdecl = builtin_decl_explicit (code))
	    builtin_typelist = TYPE_ARG_TYPES (ವೃಕ್ಷ_TYPE (bdecl));
	}

      /* For type-generic built-in functions, determine whether excess
	 precision should be removed (classification) or not
	 (comparison).  */
      ಯದಿ (type_generic)
	ವಿಕಲ್ಪ (code)
	  {
	  ಪಕ್ಷ BUILT_IN_ISFINITE:
	  ಪಕ್ಷ BUILT_IN_ISINF:
	  ಪಕ್ಷ BUILT_IN_ISINF_SIGN:
	  ಪಕ್ಷ BUILT_IN_ISNAN:
	  ಪಕ್ಷ BUILT_IN_ISNORMAL:
	  ಪಕ್ಷ BUILT_IN_ISSIGNALING:
	  ಪಕ್ಷ BUILT_IN_FPCLASSIFY:
	    type_generic_remove_excess_precision = ಸತ್ಯ;
	    ಭಙ್ಗ;

	  ಪಕ್ಷ BUILT_IN_ADD_OVERFLOW_P:
	  ಪಕ್ಷ BUILT_IN_SUB_OVERFLOW_P:
	  ಪಕ್ಷ BUILT_IN_MUL_OVERFLOW_P:
	    /* The last argument of these type-generic builtins
	       should not be promoted.  */
	    type_generic_overflow_p = ಸತ್ಯ;
	    ಭಙ್ಗ;

	  ಪಕ್ಷ BUILT_IN_CLZG:
	  ಪಕ್ಷ BUILT_IN_CTZG:
	  ಪಕ್ಷ BUILT_IN_CLRSBG:
	  ಪಕ್ಷ BUILT_IN_FFSG:
	  ಪಕ್ಷ BUILT_IN_PARITYG:
	  ಪಕ್ಷ BUILT_IN_POPCOUNTG:
	    /* The first argument of these type-generic builtins
	       should not be promoted.  */
	    type_generic_bit_query = ಸತ್ಯ;
	    ಭಙ್ಗ;

	  ಸ್ವಭಾವ:
	    ಭಙ್ಗ;
	  }
    }

  /* Scan the given expressions (VALUES) and types (TYPELIST), producing
     individual converted arguments.  */

  ವೃಕ್ಷ typetail, builtin_typetail, val;
  ಪ್ರತಿ (typetail = typelist,
	 builtin_typetail = builtin_typelist,
	 parmnum = 0;
       ಮೌಲ್ಯಗಳು && ಮೌಲ್ಯಗಳು->iterate (parmnum, &val);
       ++parmnum)
    {
      /* The type of the function parameter (if it was declared with one).  */
      ವೃಕ್ಷ type = typetail ? ವೃಕ್ಷ_ಮೌಲ್ಯ (typetail) : NULL_ವೃಕ್ಷ;
      /* The type of the built-in function parameter (if the function
	 is a built-in).  Used to detect type incompatibilities in
	 calls to built-ins declared without a prototype.  */
      ವೃಕ್ಷ builtin_type = (builtin_typetail
			   ? ವೃಕ್ಷ_ಮೌಲ್ಯ (builtin_typetail) : NULL_ವೃಕ್ಷ);
      /* The original type of the argument being passed to the function.  */
      ವೃಕ್ಷ valtype = ವೃಕ್ಷ_TYPE (val);
      /* The called function (or function selector in Objective C).  */
      ವೃಕ್ಷ rname = function;
      ಪೂರ್ಣಾಙ್ಕ argnum = parmnum + 1;
      ಧ್ರುವ ವರ್ಣ *invalid_func_diag;
      /* Set for EXCESS_PRECISION_EXPR arguments.  */
      ತಾರ್ಕಿಕ excess_precision = ಅಸತ್ಯ;
      /* The value of the argument after conversion to the type
	 of the function parameter it is passed to.  */
      ವೃಕ್ಷ parmval;
      /* Some __atomic_* builtins have additional hidden argument at
	 position 0.  */
      location_t ploc
	= !arg_loc.is_empty () && ಮೌಲ್ಯಗಳು->length () == arg_loc.length ()
	  ? expansion_point_location_if_in_system_header (arg_loc[parmnum])
	  : ಒಳಹರಿವು_location;

      ಯದಿ (type == void_type_ಗಂಟು)
	{
	  auto_diagnostic_group d;
	  ಪೂರ್ಣಾಙ್ಕ ಅಂಕೆ_expected = parmnum;
	  ಪೂರ್ಣಾಙ್ಕ ಅಂಕೆ_actual = ಮೌಲ್ಯಗಳು->length ();
	  gcc_rich_location rich_loc (loc);
	  ಯದಿ (ploc != ಒಳಹರಿವು_location)
	    rich_loc.add_range (ploc);
	  ಯದಿ (selector)
	    error_at (&rich_loc,
		      "too many arguments to method %qE; expected %i, have %i",
		      selector, ಅಂಕೆ_expected, ಅಂಕೆ_actual);
	  ಅನ್ಯಥಾ
	    error_at (&rich_loc,
		      "too many arguments to function %qE; expected %i, have %i",
		      function, ಅಂಕೆ_expected, ಅಂಕೆ_actual);
	  inform_declaration (fundecl, function);
	  ಪ್ರತ್ಯಾಗಮ error_args ? -1 : (ಪೂರ್ಣಾಙ್ಕ) parmnum;
	}

      ಯದಿ (builtin_type == void_type_ಗಂಟು)
	{
	  auto_diagnostic_group d;
	  ಯದಿ (warning_at (loc, OPT_Wbuiltin_declaration_mismatch,
			  "too many arguments to built-in function %qE "
			  "expecting %d", function, parmnum))
	    inform_declaration (fundecl, function);
	  builtin_typetail = NULL_ವೃಕ್ಷ;
	}

      ಯದಿ (!typetail && parmnum == 0 && !TYPE_NO_NAMED_ARGS_STDARG_P (fntype)
	  && !(fundecl && fndecl_built_in_p (fundecl)))
	{
	  auto_diagnostic_group d;
	  ತಾರ್ಕಿಕ warned;
	  ಯದಿ (selector)
	    warned = warning_at (loc, OPT_Wdeprecated_non_prototype,
				 "ISO C23 does not allow arguments"
				 " for method %qE declared without parameters",
				 function);
	  ಅನ್ಯಥಾ
	    warned = warning_at (loc, OPT_Wdeprecated_non_prototype,
				 "ISO C23 does not allow arguments"
				 " for function %qE declared without parameters",
				 function);
	  ಯದಿ (warned)
	    inform_declaration (fundecl, function);
	}

      ಯದಿ (selector && argnum > 2)
	{
	  rname = selector;
	  argnum -= 2;
	}

      /* Determine if VAL is a null pointer constant before folding it.  */
      ತಾರ್ಕಿಕ npc = null_pointer_constant_p (val);

      /* If there is excess precision and a prototype, convert once to
	 the required type rather than converting via the semantic
	 type.  Likewise without a prototype a float value represented
	 as long double should be converted once to double.  But for
	 type-generic classification functions excess precision must
	 be removed here.  */
      ಯದಿ (ವೃಕ್ಷ_CODE (val) == EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ
	  && (type || !type_generic || !type_generic_remove_excess_precision))
	{
	  val = ವೃಕ್ಷ_OPERAND (val, 0);
	  excess_precision = ಸತ್ಯ;
	}
      val = c_fully_fold (val, ಅಸತ್ಯ, ರಿಕ್ತ);
      STRIP_TYPE_NOPS (val);

      val = require_complete_type (ploc, val);

      /* Some floating-point arguments must be promoted to double when
	 no type is specified by a prototype.  This applies to
	 arguments of type float, and to architecture-specific types
	 (ARM __fp16), but not to _FloatN or _FloatNx types.  */
      ತಾರ್ಕಿಕ promote_float_arg = ಅಸತ್ಯ;
      ಯದಿ (type == NULL_ವೃಕ್ಷ
	  && ವೃಕ್ಷ_CODE (valtype) == REAL_TYPE
	  && (TYPE_PRECISION (valtype)
	      <= TYPE_PRECISION (double_type_ಗಂಟು))
	  && TYPE_MAIN_VARIANT (valtype) != double_type_ಗಂಟು
	  && TYPE_MAIN_VARIANT (valtype) != long_double_type_ಗಂಟು
	  && !DECIMAL_FLOAT_MODE_P (TYPE_MODE (valtype)))
	{
	  /* Promote this argument, unless it has a _FloatN or
	     _FloatNx type.  */
	  promote_float_arg = ಸತ್ಯ;
	  ಪ್ರತಿ (ಪೂರ್ಣಾಙ್ಕ i = 0; i < ಅಂಕೆ_FLOATN_NX_TYPES; i++)
	    ಯದಿ (TYPE_MAIN_VARIANT (valtype) == FLOATN_NX_TYPE_ಗಂಟು (i))
	      {
		promote_float_arg = ಅಸತ್ಯ;
		ಭಙ್ಗ;
	      }
	  /* Don't promote __bf16 either.  */
	  ಯದಿ (TYPE_MAIN_VARIANT (valtype) == bfloat16_type_ಗಂಟು)
	    promote_float_arg = ಅಸತ್ಯ;
	}

      ಯದಿ (type != NULL_ವೃಕ್ಷ)
	{
	  ವೃಕ್ಷ origtype = (!origtypes) ? NULL_ವೃಕ್ಷ : (*origtypes)[parmnum];
	  parmval = convert_argument (ploc, function, fundecl, type, origtype,
				      val, valtype, npc, rname, parmnum, argnum,
				      excess_precision, 0);
	}
      /* A NULLPTR type is just a nullptr always.  */
      ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (val)) == NULLPTR_TYPE)
	parmval = omit_one_operand_loc (ploc, ವೃಕ್ಷ_TYPE (val), nullptr_ಗಂಟು, val);
      ಅನ್ಯಥಾ ಯದಿ (promote_float_arg)
        {
	  ಯದಿ (type_generic)
	    parmval = val;
	  ಅನ್ಯಥಾ
	    {
	      /* Convert `float' to `double'.  */
	      ಯದಿ (warn_double_promotion && !c_inhibit_evaluation_warnings)
		warning_at (ploc, OPT_Wdouble_promotion,
			    "implicit conversion from %qT to %qT when passing "
			    "argument to function",
			    valtype, double_type_ಗಂಟು);
	      parmval = convert (double_type_ಗಂಟು, val);
	    }
	}
      ಅನ್ಯಥಾ ಯದಿ ((excess_precision && !type_generic)
	       || (type_generic_overflow_p && parmnum == 2)
	       || (type_generic_bit_query && parmnum == 0))
	/* A "double" argument with excess precision being passed
	   without a prototype or in variable arguments.
	   The last argument of __builtin_*_overflow_p should not be
	   promoted, similarly the first argument of
	   __builtin_{clz,ctz,clrsb,ffs,parity,popcount}g.  */
	parmval = convert (valtype, val);
      ಅನ್ಯಥಾ ಯದಿ ((invalid_func_diag =
		targetm.calls.invalid_arg_for_unprototyped_fn (typelist, fundecl, val)))
	{
	  error (invalid_func_diag);
	  ಪ್ರತ್ಯಾಗಮ -1;
	}
      ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (val) == ADDR_ಅಭಿವ್ಯಕ್ತಿ && reject_gcc_builtin (val))
	{
	  ಪ್ರತ್ಯಾಗಮ -1;
	}
      ಅನ್ಯಥಾ
	/* Convert `short' and `char' to full-size `int'.  */
	parmval = default_conversion (val);

      (*ಮೌಲ್ಯಗಳು)[parmnum] = parmval;
      ಯದಿ (parmval == error_mark_ಗಂಟು)
	error_args = ಸತ್ಯ;

      ಯದಿ (!type && builtin_type && ವೃಕ್ಷ_CODE (builtin_type) != VOID_TYPE)
	{
	  /* For a call to a built-in function declared without a prototype,
	     perform the conversions from the argument to the expected type
	     but issue warnings rather than errors for any mismatches.
	     Ignore the converted argument and use the PARMVAL obtained
	     above by applying default conversions instead.  */
	  ವೃಕ್ಷ origtype = (!origtypes) ? NULL_ವೃಕ್ಷ : (*origtypes)[parmnum];
	  convert_argument (ploc, function, fundecl, builtin_type, origtype,
			    val, valtype, npc, rname, parmnum, argnum,
			    excess_precision,
			    OPT_Wbuiltin_declaration_mismatch);
	}

      ಯದಿ (typetail)
	typetail = ವೃಕ್ಷ_CHAIN (typetail);

      ಯದಿ (builtin_typetail)
	builtin_typetail = ವೃಕ್ಷ_CHAIN (builtin_typetail);
    }

  gcc_assert (parmnum == vec_safe_length (ಮೌಲ್ಯಗಳು));

  ಯದಿ (typetail != NULL_ವೃಕ್ಷ && ವೃಕ್ಷ_ಮೌಲ್ಯ (typetail) != void_type_ಗಂಟು)
    {
      /* Not enough args.
	 Determine minimum number of arguments required.  */
      ಪೂರ್ಣಾಙ್ಕ min_expected_ಅಂಕೆ = 0;
      ತಾರ್ಕಿಕ at_least_p = ಅಸತ್ಯ;
      ವೃಕ್ಷ iter = typelist;
      ಯಾವತ್ (ಸತ್ಯ)
	{
	  ಯದಿ (!iter)
	    {
	      /* Variadic arguments; stop iterating.  */
	      at_least_p = ಸತ್ಯ;
	      ಭಙ್ಗ;
	    }
	  ಯದಿ (iter == void_list_ಗಂಟು)
	    /* End of arguments; stop iterating.  */
	    ಭಙ್ಗ;
	  ++min_expected_ಅಂಕೆ;
	  iter = ವೃಕ್ಷ_CHAIN (iter);
	}
      auto_diagnostic_group d;
      ಪೂರ್ಣಾಙ್ಕ actual_ಅಂಕೆ = vec_safe_length (ಮೌಲ್ಯಗಳು);
      error_at (loc,
		at_least_p
		? G_("too few arguments to function %qE; expected at least %i, have %i")
		: G_("too few arguments to function %qE; expected %i, have %i"),
		function, min_expected_ಅಂಕೆ, actual_ಅಂಕೆ);
      inform_declaration (fundecl, function);
      ಪ್ರತ್ಯಾಗಮ -1;
    }

  ಯದಿ (builtin_typetail && ವೃಕ್ಷ_ಮೌಲ್ಯ (builtin_typetail) != void_type_ಗಂಟು)
    {
      unsigned nargs = parmnum;
      ಪ್ರತಿ (ವೃಕ್ಷ t = builtin_typetail; t; t = ವೃಕ್ಷ_CHAIN (t))
	++nargs;

      auto_diagnostic_group d;
      ಯದಿ (warning_at (loc, OPT_Wbuiltin_declaration_mismatch,
		      "too few arguments to built-in function %qE "
		      "expecting %u", function, nargs - 1))
	inform_declaration (fundecl, function);
    }

  ಪ್ರತ್ಯಾಗಮ error_args ? -1 : (ಪೂರ್ಣಾಙ್ಕ) parmnum;
}

/* This is the entry point used by the parser to build unary operators
   in the input.  CODE, a tree_code, specifies the unary operator, and
   ARG is the operand.  For unary plus, the C parser currently uses
   CONVERT_EXPR for code.

   LOC is the location to use for the tree generated.
*/

ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ
parser_build_unary_op (location_t loc, ಗಣನಾ ವೃಕ್ಷ_code code, ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ arg)
{
  ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ result;

  result.original_code = code;
  result.original_type = ರಿಕ್ತ;
  result.m_decimal = 0;

  ಯದಿ (reject_gcc_builtin (arg.ಮೌಲ್ಯ))
    {
      result.ಮೌಲ್ಯ = error_mark_ಗಂಟು;
    }
  ಅನ್ಯಥಾ
    {
      result.ಮೌಲ್ಯ = build_unary_op (loc, code, arg.ಮೌಲ್ಯ, ಅಸತ್ಯ);

      ಯದಿ (ವೃಕ್ಷ_OVERFLOW_P (result.ಮೌಲ್ಯ) && !ವೃಕ್ಷ_OVERFLOW_P (arg.ಮೌಲ್ಯ))
	overflow_warning (loc, result.ಮೌಲ್ಯ, arg.ಮೌಲ್ಯ);
    }

  /* We are typically called when parsing a prefix token at LOC acting on
     ARG.  Reflect this by updating the source range of the result to
     start at LOC and end at the end of ARG.  */
  set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&result,
			   loc, arg.get_finish ());

  ಪ್ರತ್ಯಾಗಮ result;
}

/* Returns true if TYPE is a character type, *not* including wchar_t.  */

ತಾರ್ಕಿಕ
char_type_p (ವೃಕ್ಷ type)
{
  ಪ್ರತ್ಯಾಗಮ (type == char_type_ಗಂಟು
	  || type == unsigned_char_type_ಗಂಟು
	  || type == signed_char_type_ಗಂಟು
	  || type == char16_type_ಗಂಟು
	  || type == char32_type_ಗಂಟು);
}

/* This is the entry point used by the parser to build binary operators
   in the input.  CODE, a tree_code, specifies the binary operator, and
   ARG1 and ARG2 are the operands.  In addition to constructing the
   expression, we check for operands that were written with other binary
   operators in a way that is likely to confuse the user.  ORIG_ARG1 is
   the original first operand for TRUTH_{AND,OR}IF_EXPR before it is
   converted to truth value, otherwise NULL_TREE.

   LOCATION is the location of the binary operator.  */

ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ
parser_build_ದ್ವಿಮಾನ_op (location_t location, ಗಣನಾ ವೃಕ್ಷ_code code,
			ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ arg1, ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ arg2, ವೃಕ್ಷ orig_arg1)
{
  ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ result;
  result.m_decimal = 0;

  ಗಣನಾ ವೃಕ್ಷ_code code1 = arg1.original_code;
  ಗಣನಾ ವೃಕ್ಷ_code code2 = arg2.original_code;
  ವೃಕ್ಷ type1 = (arg1.original_type
                ? arg1.original_type
                : ವೃಕ್ಷ_TYPE (arg1.ಮೌಲ್ಯ));
  ವೃಕ್ಷ type2 = (arg2.original_type
                ? arg2.original_type
                : ವೃಕ್ಷ_TYPE (arg2.ಮೌಲ್ಯ));

  result.ಮೌಲ್ಯ = build_ದ್ವಿಮಾನ_op (location, code,
				  arg1.ಮೌಲ್ಯ, arg2.ಮೌಲ್ಯ, ಸತ್ಯ);
  result.original_code = code;
  result.original_type = ರಿಕ್ತ;
  result.m_decimal = 0;

  ಯದಿ (ವೃಕ್ಷ_CODE (result.ಮೌಲ್ಯ) == ERROR_MARK)
    {
      set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&result,
			       arg1.get_start (),
			       arg2.get_finish ());
      ಪ್ರತ್ಯಾಗಮ result;
    }

  ಯದಿ (location != UNKNOWN_LOCATION)
    protected_set_ಅಭಿವ್ಯಕ್ತಿ_location (result.ಮೌಲ್ಯ, location);

  set_c_ಅಭಿವ್ಯಕ್ತಿ_source_range (&result,
			   arg1.get_start (),
			   arg2.get_finish ());

  /* Check for cases such as x+y<<z which users are likely
     to misinterpret.  */
  ಯದಿ (warn_parentheses)
    warn_about_parentheses (location, code, code1, arg1.ಮೌಲ್ಯ, code2,
			    arg2.ಮೌಲ್ಯ);

  ಯದಿ (warn_logical_op)
    warn_logical_operator (location, code, ವೃಕ್ಷ_TYPE (result.ಮೌಲ್ಯ),
			   code1, arg1.ಮೌಲ್ಯ, code2, arg2.ಮೌಲ್ಯ);

  ಯದಿ (warn_constant_logical_operand
      && (code == TRUTH_ANDIF_ಅಭಿವ್ಯಕ್ತಿ || code == TRUTH_ORIF_ಅಭಿವ್ಯಕ್ತಿ)
      && INTEGRAL_NB_TYPE_P (type1)
      && INTEGRAL_NB_TYPE_P (type2))
    {
      ಧ್ರುವ ವರ್ಣ *name = code == TRUTH_ANDIF_ಅಭಿವ್ಯಕ್ತಿ ? "&&" : "||";
      ಯದಿ (orig_arg1 == NULL_ವೃಕ್ಷ)
	orig_arg1 = arg1.ಮೌಲ್ಯ;
      auto enum_other_than_0_1 = [] (ವೃಕ್ಷ type) {
	ಯದಿ (ವೃಕ್ಷ_CODE (type) != ENUMERAL_TYPE)
	  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	ಪ್ರತಿ (ವೃಕ್ಷ l = TYPE_ಮೌಲ್ಯಗಳು (type); l; l = ವೃಕ್ಷ_CHAIN (l))
	  {
	    ವೃಕ್ಷ v = DECL_INITIAL (ವೃಕ್ಷ_ಮೌಲ್ಯ (l));
	    ಯದಿ (!integer_zerop (v) && !integer_onep (v))
	      ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
	  }
	ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
      };
      auto diagnose_constant_logical_operand = [=] (ವೃಕ್ಷ val, ವೃಕ್ಷ type) {
	ಯದಿ (ವೃಕ್ಷ_CODE (val) != INTEGER_CST || integer_zerop (val))
	  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	ಯದಿ (integer_onep (val) && !enum_other_than_0_1 (type))
	  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	gcc_rich_location richloc (location);
	richloc.add_fixit_replace (name + 1);
	auto_diagnostic_group d;
	ಯದಿ (warning_at (location, OPT_Wconstant_logical_operand,
			"use of logical %qs with constant operand %qE",
			name, val))
	  inform (&richloc, "use %qs for bitwise operation", name + 1);
	ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
      };
      ಯದಿ (!diagnose_constant_logical_operand (arg2.ಮೌಲ್ಯ, type2))
	diagnose_constant_logical_operand (orig_arg1, type1);
    }

  ಯದಿ (warn_tautological_compare)
    {
      ವೃಕ್ಷ lhs = arg1.ಮೌಲ್ಯ;
      ವೃಕ್ಷ rhs = arg2.ಮೌಲ್ಯ;
      ಯದಿ (ವೃಕ್ಷ_CODE (lhs) == C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ)
	{
	  ಯದಿ (C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_PRE (lhs) != NULL_ವೃಕ್ಷ
	      && ವೃಕ್ಷ_SIDE_EFFECTS (C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_PRE (lhs)))
	    lhs = NULL_ವೃಕ್ಷ;
	  ಅನ್ಯಥಾ
	    lhs = C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_ಅಭಿವ್ಯಕ್ತಿ (lhs);
	}
      ಯದಿ (ವೃಕ್ಷ_CODE (rhs) == C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ)
	{
	  ಯದಿ (C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_PRE (rhs) != NULL_ವೃಕ್ಷ
	      && ವೃಕ್ಷ_SIDE_EFFECTS (C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_PRE (rhs)))
	    rhs = NULL_ವೃಕ್ಷ;
	  ಅನ್ಯಥಾ
	    rhs = C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_ಅಭಿವ್ಯಕ್ತಿ (rhs);
	}
      ಯದಿ (lhs != NULL_ವೃಕ್ಷ && rhs != NULL_ವೃಕ್ಷ)
	warn_tautological_cmp (location, code, lhs, rhs);
    }

  ಯದಿ (warn_logical_not_paren
      && ವೃಕ್ಷ_CODE_CLASS (code) == tcc_comparison
      && code1 == TRUTH_NOT_ಅಭಿವ್ಯಕ್ತಿ
      && code2 != TRUTH_NOT_ಅಭಿವ್ಯಕ್ತಿ
      /* Avoid warning for !!x == y.  */
      && (ವೃಕ್ಷ_CODE (arg1.ಮೌಲ್ಯ) != NE_ಅಭಿವ್ಯಕ್ತಿ
	  || !integer_zerop (ವೃಕ್ಷ_OPERAND (arg1.ಮೌಲ್ಯ, 1))))
    {
      /* Avoid warning for !b == y where b has _Bool type.  */
      ವೃಕ್ಷ t = integer_zero_ಗಂಟು;
      ಯದಿ (ವೃಕ್ಷ_CODE (arg1.ಮೌಲ್ಯ) == EQ_ಅಭಿವ್ಯಕ್ತಿ
	  && integer_zerop (ವೃಕ್ಷ_OPERAND (arg1.ಮೌಲ್ಯ, 1))
	  && ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_OPERAND (arg1.ಮೌಲ್ಯ, 0)) == integer_type_ಗಂಟು)
	{
	  t = ವೃಕ್ಷ_OPERAND (arg1.ಮೌಲ್ಯ, 0);
	  ಕುರು
	    {
	      ಯದಿ (ವೃಕ್ಷ_TYPE (t) != integer_type_ಗಂಟು)
		ಭಙ್ಗ;
	      ಯದಿ (ವೃಕ್ಷ_CODE (t) == C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ)
		t = C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_ಅಭಿವ್ಯಕ್ತಿ (t);
	      ಅನ್ಯಥಾ ಯದಿ (CONVERT_ಅಭಿವ್ಯಕ್ತಿ_P (t))
		t = ವೃಕ್ಷ_OPERAND (t, 0);
	      ಅನ್ಯಥಾ
		ಭಙ್ಗ;
	    }
	  ಯಾವತ್ (1);
	}
      ಯದಿ (!C_BOOLEAN_TYPE_P (ವೃಕ್ಷ_TYPE (t)))
	warn_logical_not_parentheses (location, code, arg1.ಮೌಲ್ಯ, arg2.ಮೌಲ್ಯ);
    }

  /* Warn about comparisons against string literals, with the exception
     of testing for equality or inequality of a string literal with NULL.  */
  ಯದಿ (code == EQ_ಅಭಿವ್ಯಕ್ತಿ || code == NE_ಅಭಿವ್ಯಕ್ತಿ)
    {
      ಯದಿ ((code1 == STRING_CST
	   && !integer_zerop (ವೃಕ್ಷ_strip_nop_conversions (arg2.ಮೌಲ್ಯ)))
	  || (code2 == STRING_CST
	      && !integer_zerop (ವೃಕ್ಷ_strip_nop_conversions (arg1.ಮೌಲ್ಯ))))
	warning_at (location, OPT_Waddress,
		    "comparison with string literal results in unspecified behavior");
      /* Warn for ptr == '\0', it's likely that it should've been ptr[0].  */
      ಯದಿ (POINTER_TYPE_P (type1)
	  && null_pointer_constant_p (arg2.ಮೌಲ್ಯ)
	  && char_type_p (type2))
	{
	  auto_diagnostic_group d;
	  ಯದಿ (warning_at (location, OPT_Wpointer_compare,
			    "comparison between pointer and zero character "
			    "constant"))
	    inform (arg1.get_start (),
		      "did you mean to dereference the pointer?");
	}
      ಅನ್ಯಥಾ ಯದಿ (POINTER_TYPE_P (type2)
	       && null_pointer_constant_p (arg1.ಮೌಲ್ಯ)
	       && char_type_p (type1))
	{
	  auto_diagnostic_group d;
	  ಯದಿ (warning_at (location, OPT_Wpointer_compare,
			    "comparison between pointer and zero character "
			    "constant"))
	    inform (arg2.get_start (),
		      "did you mean to dereference the pointer?");
	}
    }
  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE_CLASS (code) == tcc_comparison
	   && (code1 == STRING_CST || code2 == STRING_CST))
    warning_at (location, OPT_Waddress,
		"comparison with string literal results in unspecified "
		"behavior");

  ಯದಿ (warn_zero_as_null_pointer_constant
      && c_inhibit_evaluation_warnings == 0
      && ವೃಕ್ಷ_CODE_CLASS (code) == tcc_comparison)
    {
      ಯದಿ ((ವೃಕ್ಷ_CODE (type1) == POINTER_TYPE
	   || ವೃಕ್ಷ_CODE (type1) == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type2)
	  && null_pointer_constant_p (arg2.ಮೌಲ್ಯ))
	warning_at (arg2.get_location(), OPT_Wzero_as_null_pointer_constant,
		    "zero as null pointer constant");

      ಯದಿ ((ವೃಕ್ಷ_CODE (type2) == POINTER_TYPE
	   || ವೃಕ್ಷ_CODE (type2) == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type1)
	  && null_pointer_constant_p (arg1.ಮೌಲ್ಯ))
	warning_at (arg1.get_location(), OPT_Wzero_as_null_pointer_constant,
		    "zero as null pointer constant");
    }

  ಯದಿ (warn_array_compare
      && ವೃಕ್ಷ_CODE_CLASS (code) == tcc_comparison
      && ವೃಕ್ಷ_CODE (type1) == ARRAY_TYPE
      && ವೃಕ್ಷ_CODE (type2) == ARRAY_TYPE)
    do_warn_array_compare (location, code, arg1.ಮೌಲ್ಯ, arg2.ಮೌಲ್ಯ);

  ಯದಿ (ವೃಕ್ಷ_OVERFLOW_P (result.ಮೌಲ್ಯ)
      && !ವೃಕ್ಷ_OVERFLOW_P (arg1.ಮೌಲ್ಯ)
      && !ವೃಕ್ಷ_OVERFLOW_P (arg2.ಮೌಲ್ಯ))
    overflow_warning (location, result.ಮೌಲ್ಯ);

  /* Warn about comparisons of different enum types.  */
  ಯದಿ (warn_enum_compare
      && ವೃಕ್ಷ_CODE_CLASS (code) == tcc_comparison
      && ವೃಕ್ಷ_CODE (type1) == ENUMERAL_TYPE
      && ವೃಕ್ಷ_CODE (type2) == ENUMERAL_TYPE
      && TYPE_MAIN_VARIANT (type1) != TYPE_MAIN_VARIANT (type2))
    warning_at (location, OPT_Wenum_compare,
		"comparison between %qT and %qT",
		type1, type2);

  ಯದಿ (warn_xor_used_as_pow
      && code == BIT_XOR_ಅಭಿವ್ಯಕ್ತಿ
      && arg1.m_decimal
      && arg2.m_decimal)
    check_for_xor_used_as_pow (arg1.get_location (), arg1.ಮೌಲ್ಯ,
			       location,
			       arg2.get_location (), arg2.ಮೌಲ್ಯ);

  ಪ್ರತ್ಯಾಗಮ result;
}

/* Return a tree for the difference of pointers OP0 and OP1.
   The resulting tree has type ptrdiff_t.  If POINTER_SUBTRACT sanitization is
   enabled, assign to INSTRUMENT_EXPR call to libsanitizer.  */

ಸ್ಥಿರ ವೃಕ್ಷ
pointer_diff (location_t loc, ವೃಕ್ಷ op0, ವೃಕ್ಷ op1, ವೃಕ್ಷ *instrument_ಅಭಿವ್ಯಕ್ತಿ)
{
  ವೃಕ್ಷ restype = ptrdiff_type_ಗಂಟು;
  ವೃಕ್ಷ result, inttype;

  addr_space_t as0 = TYPE_ADDR_SPACE (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (op0)));
  addr_space_t as1 = TYPE_ADDR_SPACE (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (op1)));
  ವೃಕ್ಷ target_type = ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (op0));
  ವೃಕ್ಷ orig_op0 = op0;
  ವೃಕ್ಷ orig_op1 = op1;

  /* If the operands point into different address spaces, we need to
     explicitly convert them to pointers into the common address space
     before we can subtract the numerical address values.  */
  ಯದಿ (as0 != as1)
    {
      addr_space_t as_common;
      ವೃಕ್ಷ common_type;

      /* Determine the common superset address space.  This is guaranteed
	 to exist because the caller verified that comp_target_types
	 returned non-zero.  */
      ಯದಿ (!addr_space_superset (as0, as1, &as_common))
	gcc_unreachable ();

      common_type = common_pointer_type (ವೃಕ್ಷ_TYPE (op0), ವೃಕ್ಷ_TYPE (op1), NULL_ವೃಕ್ಷ);
      op0 = convert (common_type, op0);
      op1 = convert (common_type, op1);
    }

  /* Determine integer type result of the subtraction.  This will usually
     be the same as the result type (ptrdiff_t), but may need to be a wider
     type if pointers for the address space are wider than ptrdiff_t.  */
  ಯದಿ (TYPE_PRECISION (restype) < TYPE_PRECISION (ವೃಕ್ಷ_TYPE (op0)))
    inttype = c_common_type_for_size (TYPE_PRECISION (ವೃಕ್ಷ_TYPE (op0)), 0);
  ಅನ್ಯಥಾ
    inttype = restype;

  ಯದಿ (VOID_TYPE_P (target_type))
    pedwarn (loc, OPT_Wpointer_arith,
	     "pointer of type %<void *%> used in subtraction");
  ಯದಿ (ವೃಕ್ಷ_CODE (target_type) == FUNCTION_TYPE)
    pedwarn (loc, OPT_Wpointer_arith,
	     "pointer to a function used in subtraction");

  ಯದಿ (current_function_decl != NULL_ವೃಕ್ಷ
      && sanitize_flags_p (SANITIZE_POINTER_SUBTRACT))
    {
      op0 = save_ಅಭಿವ್ಯಕ್ತಿ (c_fully_fold (op0, ಅಸತ್ಯ, ರಿಕ್ತ));
      op1 = save_ಅಭಿವ್ಯಕ್ತಿ (c_fully_fold (op1, ಅಸತ್ಯ, ರಿಕ್ತ));

      ವೃಕ್ಷ tt = builtin_decl_explicit (BUILT_IN_ASAN_POINTER_SUBTRACT);
      *instrument_ಅಭಿವ್ಯಕ್ತಿ = build_call_ಅಭಿವ್ಯಕ್ತಿ_loc (loc, tt, 2, op0, op1);
    }

  /* First do the subtraction, then build the divide operator
     and only convert at the very end.
     Do not do default conversions in case restype is a short type.  */

  /* POINTER_DIFF_EXPR requires a signed integer type of the same size as
     pointers.  If some platform cannot provide that, or has a larger
     ptrdiff_type to support differences larger than half the address
     space, cast the pointers to some larger integer type and do the
     computations in that type.  */
  ಯದಿ (TYPE_PRECISION (inttype) > TYPE_PRECISION (ವೃಕ್ಷ_TYPE (op0)))
    op0 = build_ದ್ವಿಮಾನ_op (loc, MINUS_ಅಭಿವ್ಯಕ್ತಿ, convert (inttype, op0),
			   convert (inttype, op1), ಅಸತ್ಯ);
  ಅನ್ಯಥಾ
    {
      /* Cast away qualifiers.  */
      op0 = convert (c_common_type (ವೃಕ್ಷ_TYPE (op0), ವೃಕ್ಷ_TYPE (op0)), op0);
      op1 = convert (c_common_type (ವೃಕ್ಷ_TYPE (op1), ವೃಕ್ಷ_TYPE (op1)), op1);
      op0 = build2_loc (loc, POINTER_DIFF_ಅಭಿವ್ಯಕ್ತಿ, inttype, op0, op1);
    }

  /* This generates an error if op1 is pointer to incomplete type.  */
  ಯದಿ (!COMPLETE_OR_VOID_TYPE_P (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (orig_op1))))
    error_at (loc, "arithmetic on pointer to an incomplete type");
  ಅನ್ಯಥಾ ಯದಿ (verify_type_context (loc, TCTX_POINTER_ARITH,
				ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (orig_op0))))
    verify_type_context (loc, TCTX_POINTER_ARITH,
			 ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (orig_op1)));

  op1 = c_size_in_bytes (target_type);

  ಯದಿ (pointer_to_zero_sized_aggr_p (ವೃಕ್ಷ_TYPE (orig_op1)))
    error_at (loc, "arithmetic on pointer to an empty aggregate");

  /* Divide by the size, in easiest possible way.  */
  result = fold_build2_loc (loc, EXACT_DIV_ಅಭಿವ್ಯಕ್ತಿ, inttype,
			    op0, convert (inttype, op1));

  /* Convert to final result type if necessary.  */
  ಪ್ರತ್ಯಾಗಮ convert (restype, result);
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

ಸ್ಥಿರ ವೃಕ್ಷ
build_atomic_assign (location_t loc, ವೃಕ್ಷ lhs, ಗಣನಾ ವೃಕ್ಷ_code modifycode,
		     ವೃಕ್ಷ rhs, ತಾರ್ಕಿಕ return_old_p)
{
  ವೃಕ್ಷ fndecl, func_call;
  vec<ವೃಕ್ಷ, va_gc> *params;
  ವೃಕ್ಷ val, nonatomic_lhs_type, nonatomic_rhs_type, newval, newval_addr;
  ವೃಕ್ಷ old, old_addr;
  ವೃಕ್ಷ compound_stmt = NULL_ವೃಕ್ಷ;
  ವೃಕ್ಷ stmt, goto_stmt;
  ವೃಕ್ಷ loop_label, loop_decl, done_label, done_decl;

  ವೃಕ್ಷ lhs_type = ವೃಕ್ಷ_TYPE (lhs);
  ವೃಕ್ಷ lhs_addr = build_unary_op (loc, ADDR_ಅಭಿವ್ಯಕ್ತಿ, lhs, ಅಸತ್ಯ);
  ವೃಕ್ಷ seq_cst = build_int_cst (integer_type_ಗಂಟು, MEMMODEL_SEQ_CST);
  ವೃಕ್ಷ rhs_semantic_type = ವೃಕ್ಷ_TYPE (rhs);
  ವೃಕ್ಷ nonatomic_rhs_semantic_type;
  ವೃಕ್ಷ rhs_type;

  gcc_assert (TYPE_ATOMIC (lhs_type));

  ಯದಿ (return_old_p)
    gcc_assert (modifycode == PLUS_ಅಭಿವ್ಯಕ್ತಿ || modifycode == MINUS_ಅಭಿವ್ಯಕ್ತಿ);

  /* Allocate enough vector items for a compare_exchange.  */
  vec_alloc (params, 6);

  /* Create a compound statement to hold the sequence of statements
     with a loop.  */
  ಯದಿ (modifycode != NOP_ಅಭಿವ್ಯಕ್ತಿ)
    {
      compound_stmt = c_begin_compound_stmt (ಅಸತ್ಯ);

      /* For consistency with build_modify_expr on non-_Atomic,
	 mark the lhs as read.  Also, it would be very hard to match
	 such expressions in mark_exp_read.  */
      mark_exp_read (lhs);
    }

  /* Remove any excess precision (which is only present here in the
     case of compound assignments).  */
  ಯದಿ (ವೃಕ್ಷ_CODE (rhs) == EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ)
    {
      gcc_assert (modifycode != NOP_ಅಭಿವ್ಯಕ್ತಿ);
      rhs = ವೃಕ್ಷ_OPERAND (rhs, 0);
    }
  rhs_type = ವೃಕ್ಷ_TYPE (rhs);

  /* Fold the RHS if it hasn't already been folded.  */
  ಯದಿ (modifycode != NOP_ಅಭಿವ್ಯಕ್ತಿ)
    rhs = c_fully_fold (rhs, ಅಸತ್ಯ, ರಿಕ್ತ);

  /* Remove the qualifiers for the rest of the expressions and create
     the VAL temp variable to hold the RHS.  */
  nonatomic_lhs_type = build_qualified_type (lhs_type, TYPE_UNQUALIFIED);
  nonatomic_rhs_type = build_qualified_type (rhs_type, TYPE_UNQUALIFIED);
  nonatomic_rhs_semantic_type = build_qualified_type (rhs_semantic_type,
						      TYPE_UNQUALIFIED);
  val = create_tmp_var_raw (nonatomic_rhs_type);
  ವೃಕ್ಷ_ADDRESSABLE (val) = 1;
  suppress_warning (val);
  rhs = build4 (TARGET_ಅಭಿವ್ಯಕ್ತಿ, nonatomic_rhs_type, val, rhs, NULL_ವೃಕ್ಷ,
		NULL_ವೃಕ್ಷ);
  ವೃಕ್ಷ_SIDE_EFFECTS (rhs) = 1;
  SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (rhs, loc);
  ಯದಿ (modifycode != NOP_ಅಭಿವ್ಯಕ್ತಿ)
    add_stmt (rhs);

  /* NOP_EXPR indicates it's a straight store of the RHS. Simply issue
     an atomic_store.  */
  ಯದಿ (modifycode == NOP_ಅಭಿವ್ಯಕ್ತಿ)
    {
      compound_stmt = rhs;
      /* Build __atomic_store (&lhs, &val, SEQ_CST)  */
      rhs = build_unary_op (loc, ADDR_ಅಭಿವ್ಯಕ್ತಿ, val, ಅಸತ್ಯ);
      fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_STORE);
      params->quick_ತಳ್ಳು (lhs_addr);
      params->quick_ತಳ್ಳು (rhs);
      params->quick_ತಳ್ಳು (seq_cst);
      func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, ರಿಕ್ತ);

      compound_stmt = build2 (COMPOUND_ಅಭಿವ್ಯಕ್ತಿ, void_type_ಗಂಟು,
			      compound_stmt, func_call);

      /* VAL is the value which was stored, return a COMPOUND_STMT of
	 the statement and that value.  */
      ಪ್ರತ್ಯಾಗಮ build2 (COMPOUND_ಅಭಿವ್ಯಕ್ತಿ, nonatomic_lhs_type, compound_stmt, val);
    }

  /* Attempt to implement the atomic operation as an __atomic_fetch_* or
     __atomic_*_fetch built-in rather than a CAS loop.  atomic_bool type
     isn't applicable for such builtins.  ??? Do we want to handle enums?  */
  ಯದಿ ((ವೃಕ್ಷ_CODE (lhs_type) == INTEGER_TYPE || POINTER_TYPE_P (lhs_type))
      && ವೃಕ್ಷ_CODE (rhs_type) == INTEGER_TYPE)
    {
      built_in_function fncode;
      ವಿಕಲ್ಪ (modifycode)
	{
	ಪಕ್ಷ PLUS_ಅಭಿವ್ಯಕ್ತಿ:
	ಪಕ್ಷ POINTER_PLUS_ಅಭಿವ್ಯಕ್ತಿ:
	  fncode = (return_old_p
		    ? BUILT_IN_ATOMIC_FETCH_ADD_N
		    : BUILT_IN_ATOMIC_ADD_FETCH_N);
	  ಭಙ್ಗ;
	ಪಕ್ಷ MINUS_ಅಭಿವ್ಯಕ್ತಿ:
	  fncode = (return_old_p
		    ? BUILT_IN_ATOMIC_FETCH_SUB_N
		    : BUILT_IN_ATOMIC_SUB_FETCH_N);
	  ಭಙ್ಗ;
	ಪಕ್ಷ BIT_AND_ಅಭಿವ್ಯಕ್ತಿ:
	  fncode = (return_old_p
		    ? BUILT_IN_ATOMIC_FETCH_AND_N
		    : BUILT_IN_ATOMIC_AND_FETCH_N);
	  ಭಙ್ಗ;
	ಪಕ್ಷ BIT_IOR_ಅಭಿವ್ಯಕ್ತಿ:
	  fncode = (return_old_p
		    ? BUILT_IN_ATOMIC_FETCH_OR_N
		    : BUILT_IN_ATOMIC_OR_FETCH_N);
	  ಭಙ್ಗ;
	ಪಕ್ಷ BIT_XOR_ಅಭಿವ್ಯಕ್ತಿ:
	  fncode = (return_old_p
		    ? BUILT_IN_ATOMIC_FETCH_XOR_N
		    : BUILT_IN_ATOMIC_XOR_FETCH_N);
	  ಭಙ್ಗ;
	ಸ್ವಭಾವ:
	  ಗಚ್ಛ cas_loop;
	}

      /* We can only use "_1" through "_16" variants of the atomic fetch
	 built-ins.  */
      unsigned HOST_WIDE_INT size = ವೃಕ್ಷ_to_uhwi (TYPE_SIZE_UNIT (lhs_type));
      ಯದಿ (size != 1 && size != 2 && size != 4 && size != 8 && size != 16)
	ಗಚ್ಛ cas_loop;

      /* If this is a pointer type, we need to multiply by the size of
	 the pointer target type.  */
      ಯದಿ (POINTER_TYPE_P (lhs_type))
	{
	  ಯದಿ (!COMPLETE_TYPE_P (ವೃಕ್ಷ_TYPE (lhs_type))
	      /* ??? This would introduce -Wdiscarded-qualifiers
		 warning: __atomic_fetch_* expect volatile void *
		 type as the first argument.  (Assignments between
		 atomic and non-atomic objects are OK.) */
	      || TYPE_RESTRICT (lhs_type))
	    ಗಚ್ಛ cas_loop;
	  ವೃಕ್ಷ sz = TYPE_SIZE_UNIT (ವೃಕ್ಷ_TYPE (lhs_type));
	  rhs = fold_build2_loc (loc, MULT_ಅಭಿವ್ಯಕ್ತಿ, ptrdiff_type_ಗಂಟು,
				 convert (ptrdiff_type_ಗಂಟು, rhs),
				 convert (ptrdiff_type_ಗಂಟು, sz));
	}

      /* Build __atomic_fetch_* (&lhs, &val, SEQ_CST), or
	 __atomic_*_fetch (&lhs, &val, SEQ_CST).  */
      fndecl = builtin_decl_explicit (fncode);
      params->quick_ತಳ್ಳು (lhs_addr);
      params->quick_ತಳ್ಳು (rhs);
      params->quick_ತಳ್ಳು (seq_cst);
      func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, ರಿಕ್ತ);

      newval = create_tmp_var_raw (nonatomic_lhs_type);
      ವೃಕ್ಷ_ADDRESSABLE (newval) = 1;
      suppress_warning (newval);
      rhs = build4 (TARGET_ಅಭಿವ್ಯಕ್ತಿ, nonatomic_lhs_type, newval, func_call,
		    NULL_ವೃಕ್ಷ, NULL_ವೃಕ್ಷ);
      SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (rhs, loc);
      add_stmt (rhs);

      /* Finish the compound statement.  */
      compound_stmt = c_end_compound_stmt (loc, compound_stmt, ಅಸತ್ಯ);

      /* NEWVAL is the value which was stored, return a COMPOUND_STMT of
	 the statement and that value.  */
      ಪ್ರತ್ಯಾಗಮ build2 (COMPOUND_ಅಭಿವ್ಯಕ್ತಿ, nonatomic_lhs_type, compound_stmt, newval);
    }

cas_loop:
  /* Create the variables and labels required for the op= form.  */
  old = create_tmp_var_raw (nonatomic_lhs_type);
  old_addr = build_unary_op (loc, ADDR_ಅಭಿವ್ಯಕ್ತಿ, old, ಅಸತ್ಯ);
  ವೃಕ್ಷ_ADDRESSABLE (old) = 1;
  suppress_warning (old);

  newval = create_tmp_var_raw (nonatomic_lhs_type);
  newval_addr = build_unary_op (loc, ADDR_ಅಭಿವ್ಯಕ್ತಿ, newval, ಅಸತ್ಯ);
  ವೃಕ್ಷ_ADDRESSABLE (newval) = 1;
  suppress_warning (newval);

  loop_decl = create_artificial_label (loc);
  loop_label = build1 (LABEL_ಅಭಿವ್ಯಕ್ತಿ, void_type_ಗಂಟು, loop_decl);

  done_decl = create_artificial_label (loc);
  done_label = build1 (LABEL_ಅಭಿವ್ಯಕ್ತಿ, void_type_ಗಂಟು, done_decl);

  /* __atomic_load (addr, &old, SEQ_CST).  */
  fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_LOAD);
  params->quick_ತಳ್ಳು (lhs_addr);
  params->quick_ತಳ್ಳು (old_addr);
  params->quick_ತಳ್ಳು (seq_cst);
  func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, ರಿಕ್ತ);
  old = build4 (TARGET_ಅಭಿವ್ಯಕ್ತಿ, nonatomic_lhs_type, old, func_call, NULL_ವೃಕ್ಷ,
		NULL_ವೃಕ್ಷ);
  add_stmt (old);
  params->truncate (0);

  /* Create the expressions for floating-point environment
     manipulation, if required.  */
  ತಾರ್ಕಿಕ need_fenv = (flag_trapping_math
		    && (FLOAT_TYPE_P (lhs_type) || FLOAT_TYPE_P (rhs_type)));
  ವೃಕ್ಷ hold_call = NULL_ವೃಕ್ಷ, clear_call = NULL_ವೃಕ್ಷ, update_call = NULL_ವೃಕ್ಷ;
  ಯದಿ (need_fenv)
    targetm.atomic_assign_expand_fenv (&hold_call, &clear_call, &update_call);

  ಯದಿ (hold_call)
    add_stmt (hold_call);

  /* loop:  */
  add_stmt (loop_label);

  /* newval = old + val;  */
  ಯದಿ (rhs_type != rhs_semantic_type)
    val = build1 (EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ, nonatomic_rhs_semantic_type, val);
  rhs = build_ದ್ವಿಮಾನ_op (loc, modifycode,
			 convert_lvalue_to_rvalue (loc, old, ಸತ್ಯ, ಸತ್ಯ),
			 val, ಸತ್ಯ);
  ಯದಿ (ವೃಕ್ಷ_CODE (rhs) == EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ)
    {
      ವೃಕ್ಷ eptype = ವೃಕ್ಷ_TYPE (rhs);
      rhs = c_fully_fold (ವೃಕ್ಷ_OPERAND (rhs, 0), ಅಸತ್ಯ, ರಿಕ್ತ);
      rhs = build1 (EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ, eptype, rhs);
    }
  ಅನ್ಯಥಾ
    rhs = c_fully_fold (rhs, ಅಸತ್ಯ, ರಿಕ್ತ);
  rhs = convert_for_assignment (loc, UNKNOWN_LOCATION, nonatomic_lhs_type,
				rhs, NULL_ವೃಕ್ಷ, ic_assign, ಅಸತ್ಯ, NULL_ವೃಕ್ಷ,
				NULL_ವೃಕ್ಷ, 0);
  /* The temporary variable for NEWVAL is only gimplified correctly (in
     particular, given a DECL_CONTEXT) if used in a TARGET_EXPR.  To avoid
     subsequent ICEs in nested function processing after an error, ensure such
     a TARGET_EXPR is built even after an error.  */
  ಯದಿ (rhs == error_mark_ಗಂಟು)
    rhs = old;
  rhs = build4 (TARGET_ಅಭಿವ್ಯಕ್ತಿ, nonatomic_lhs_type, newval, rhs, NULL_ವೃಕ್ಷ,
		NULL_ವೃಕ್ಷ);
  SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (rhs, loc);
  add_stmt (rhs);

  /* if (__atomic_compare_exchange (addr, &old, &new, false, SEQ_CST, SEQ_CST))
       goto done;  */
  fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_COMPARE_EXCHANGE);
  params->quick_ತಳ್ಳು (lhs_addr);
  params->quick_ತಳ್ಳು (old_addr);
  params->quick_ತಳ್ಳು (newval_addr);
  params->quick_ತಳ್ಳು (integer_zero_ಗಂಟು);
  params->quick_ತಳ್ಳು (seq_cst);
  params->quick_ತಳ್ಳು (seq_cst);
  func_call = c_build_function_call_vec (loc, vNULL, fndecl, params, ರಿಕ್ತ);

  goto_stmt = build1 (GOTO_ಅಭಿವ್ಯಕ್ತಿ, void_type_ಗಂಟು, done_decl);
  SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (goto_stmt, loc);

  stmt = build3 (COND_ಅಭಿವ್ಯಕ್ತಿ, void_type_ಗಂಟು, func_call, goto_stmt, NULL_ವೃಕ್ಷ);
  SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (stmt, loc);
  add_stmt (stmt);

  ಯದಿ (clear_call)
    add_stmt (clear_call);

  /* goto loop;  */
  goto_stmt  = build1 (GOTO_ಅಭಿವ್ಯಕ್ತಿ, void_type_ಗಂಟು, loop_decl);
  SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (goto_stmt, loc);
  add_stmt (goto_stmt);

  /* done:  */
  add_stmt (done_label);

  ಯದಿ (update_call)
    add_stmt (update_call);

  /* Finish the compound statement.  */
  compound_stmt = c_end_compound_stmt (loc, compound_stmt, ಅಸತ್ಯ);

  /* NEWVAL is the value that was successfully stored, return a
     COMPOUND_EXPR of the statement and the appropriate value.  */
  ಪ್ರತ್ಯಾಗಮ build2 (COMPOUND_ಅಭಿವ್ಯಕ್ತಿ, nonatomic_lhs_type, compound_stmt,
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

ವೃಕ್ಷ
build_unary_op (location_t location, ಗಣನಾ ವೃಕ್ಷ_code code, ವೃಕ್ಷ xarg,
		ತಾರ್ಕಿಕ noconvert)
{
  /* No default_conversion here.  It causes trouble for ADDR_EXPR.  */
  ವೃಕ್ಷ arg = xarg;
  ವೃಕ್ಷ argtype = NULL_ವೃಕ್ಷ;
  ಗಣನಾ ವೃಕ್ಷ_code typecode;
  ವೃಕ್ಷ val;
  ವೃಕ್ಷ ret = error_mark_ಗಂಟು;
  ವೃಕ್ಷ eptype = NULL_ವೃಕ್ಷ;
  ಧ್ರುವ ವರ್ಣ *invalid_op_diag;

  /* If ARG is wrapped in a call to .ACCESS_WITH_SIZE — created when the
     C parser rvalue-converts a counted_by-annotated member access (see
     PR123569) — unwrap it here.  Unary operators that consume an rvalue
     (!, -, +) read the value itself rather than dereferencing into the
     pointed-to data, so the bounds-checking wrapper is unnecessary and
     would otherwise reach build_unary_op while it is not equipped to
     handle the wrapped form.  PR123569 fixed the ++/-- side of this by
     suppressing wrapper creation in the parser; the rvalue-consuming
     ops still receive the wrapper and need to strip it here.  */
  ಯದಿ (is_access_with_size_p (arg))
    xarg = arg = get_ref_from_access_with_size (arg);

  gcc_checking_assert (!is_access_with_size_p (arg));

  ತಾರ್ಕಿಕ int_operands = ಅಭಿವ್ಯಕ್ತಿ_INT_CONST_OPERANDS (xarg);
  ಯದಿ (int_operands)
    arg = remove_c_maybe_const_ಅಭಿವ್ಯಕ್ತಿ (arg);

  ಯದಿ (code != ADDR_ಅಭಿವ್ಯಕ್ತಿ)
    arg = require_complete_type (location, arg);

  typecode = ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (arg));
  ಯದಿ (typecode == ERROR_MARK)
    ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
  ಯದಿ (typecode == ENUMERAL_TYPE || typecode == BOOLEAN_TYPE)
    typecode = INTEGER_TYPE;

  ಯದಿ ((invalid_op_diag
       = targetm.invalid_unary_op (code, ವೃಕ್ಷ_TYPE (xarg))))
    {
      error_at (location, invalid_op_diag);
      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
    }

  ಯದಿ (ವೃಕ್ಷ_CODE (arg) == EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ)
    {
      eptype = ವೃಕ್ಷ_TYPE (arg);
      arg = ವೃಕ್ಷ_OPERAND (arg, 0);
    }

  ವಿಕಲ್ಪ (code)
    {
    ಪಕ್ಷ CONVERT_ಅಭಿವ್ಯಕ್ತಿ:
      /* This is used for unary plus, because a CONVERT_EXPR
	 is enough to prevent anybody from looking inside for
	 associativity, but won't generate any code.  */
      ಯದಿ (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE
	    || typecode == FIXED_POINT_TYPE || typecode == COMPLEX_TYPE
	    || typecode == BITINT_TYPE
	    || gnu_vector_type_p (ವೃಕ್ಷ_TYPE (arg))))
	{
	  error_at (location, "wrong type argument to unary plus");
	  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	}
      ಅನ್ಯಥಾ ಯದಿ (!noconvert)
	arg = default_conversion (arg);
      arg = non_lvalue_loc (location, arg);
      ಭಙ್ಗ;

    ಪಕ್ಷ NEGATE_ಅಭಿವ್ಯಕ್ತಿ:
      ಯದಿ (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE
	    || typecode == FIXED_POINT_TYPE || typecode == COMPLEX_TYPE
	    || typecode == BITINT_TYPE
	    || gnu_vector_type_p (ವೃಕ್ಷ_TYPE (arg))))
	{
	  error_at (location, "wrong type argument to unary minus");
	  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	}
      ಅನ್ಯಥಾ ಯದಿ (!noconvert)
	arg = default_conversion (arg);
      ಭಙ್ಗ;

    ಪಕ್ಷ BIT_NOT_ಅಭಿವ್ಯಕ್ತಿ:
      /* ~ works on integer types and non float vectors. */
      ಯದಿ (typecode == INTEGER_TYPE
	  || typecode == BITINT_TYPE
	  || (gnu_vector_type_p (ವೃಕ್ಷ_TYPE (arg))
	      && !VECTOR_FLOAT_TYPE_P (ವೃಕ್ಷ_TYPE (arg))))
	{
	  ವೃಕ್ಷ e = arg;

	  /* Warn if the expression has boolean value.  */
	  ಯಾವತ್ (ವೃಕ್ಷ_CODE (e) == COMPOUND_ಅಭಿವ್ಯಕ್ತಿ)
	    e = ವೃಕ್ಷ_OPERAND (e, 1);

	  ಯದಿ ((C_BOOLEAN_TYPE_P (ವೃಕ್ಷ_TYPE (arg))
	       || truth_ಮೌಲ್ಯ_p (ವೃಕ್ಷ_CODE (e))))
	    {
	      auto_diagnostic_group d;
	      ಯದಿ (warning_at (location, OPT_Wbool_operation,
				"%<~%> on a boolean expression"))
		{
		  gcc_rich_location richloc (location);
		  richloc.add_fixit_ಸೇರಿಸು_before (location, "!");
		  inform (&richloc, "did you mean to use logical not?");
		}
	    }
	  ಯದಿ (!noconvert)
	    arg = default_conversion (arg);
	}
      ಅನ್ಯಥಾ ಯದಿ (typecode == COMPLEX_TYPE)
	{
	  code = CONJ_ಅಭಿವ್ಯಕ್ತಿ;
	  pedwarn (location, OPT_Wpedantic,
		   "ISO C does not support %<~%> for complex conjugation");
	  ಯದಿ (!noconvert)
	    arg = default_conversion (arg);
	}
      ಅನ್ಯಥಾ
	{
	  error_at (location, "wrong type argument to bit-complement");
	  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	}
      ಭಙ್ಗ;

    ಪಕ್ಷ ABS_ಅಭಿವ್ಯಕ್ತಿ:
      ಯದಿ (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE))
	{
	  error_at (location, "wrong type argument to abs");
	  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	}
      ಅನ್ಯಥಾ ಯದಿ (!noconvert)
	arg = default_conversion (arg);
      ಭಙ್ಗ;

    ಪಕ್ಷ ABSU_ಅಭಿವ್ಯಕ್ತಿ:
      ಯದಿ (!(typecode == INTEGER_TYPE))
	{
	  error_at (location, "wrong type argument to absu");
	  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	}
      ಅನ್ಯಥಾ ಯದಿ (!noconvert)
	arg = default_conversion (arg);
      ಭಙ್ಗ;

    ಪಕ್ಷ CONJ_ಅಭಿವ್ಯಕ್ತಿ:
      /* Conjugating a real value is a no-op, but allow it anyway.  */
      ಯದಿ (!(typecode == INTEGER_TYPE || typecode == REAL_TYPE
	    || typecode == COMPLEX_TYPE))
	{
	  error_at (location, "wrong type argument to conjugation");
	  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	}
      ಅನ್ಯಥಾ ಯದಿ (!noconvert)
	arg = default_conversion (arg);
      ಭಙ್ಗ;

    ಪಕ್ಷ TRUTH_NOT_ಅಭಿವ್ಯಕ್ತಿ:
      ಯದಿ (typecode != INTEGER_TYPE && typecode != FIXED_POINT_TYPE
	  && typecode != REAL_TYPE && typecode != POINTER_TYPE
	  && typecode != COMPLEX_TYPE && typecode != NULLPTR_TYPE
	  && typecode != BITINT_TYPE)
	{
	  error_at (location,
		    "wrong type argument to unary exclamation mark");
	  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	}
      ಯದಿ (int_operands)
	{
	  arg = c_objc_common_truthvalue_conversion (location, xarg);
	  arg = remove_c_maybe_const_ಅಭಿವ್ಯಕ್ತಿ (arg);
	}
      ಅನ್ಯಥಾ
	arg = c_objc_common_truthvalue_conversion (location, arg);
      ret = invert_truthvalue_loc (location, arg);
      eptype = NULL_ವೃಕ್ಷ;
      /* If the TRUTH_NOT_EXPR has been folded, reset the location.  */
      ಯದಿ (ಅಭಿವ್ಯಕ್ತಿ_P (ret) && ಅಭಿವ್ಯಕ್ತಿ_HAS_LOCATION (ret))
	location = ಅಭಿವ್ಯಕ್ತಿ_LOCATION (ret);
      ಗಚ್ಛ return_build_unary_op;

    ಪಕ್ಷ REALPART_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ IMAGPART_ಅಭಿವ್ಯಕ್ತಿ:
      ret = build_real_imag_ಅಭಿವ್ಯಕ್ತಿ (location, code, arg);
      ಯದಿ (ret == error_mark_ಗಂಟು)
	ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
      ಯದಿ (eptype && ವೃಕ್ಷ_CODE (eptype) == COMPLEX_TYPE)
	eptype = ವೃಕ್ಷ_TYPE (eptype);
      ಗಚ್ಛ return_build_unary_op;

    ಪಕ್ಷ PREINCREMENT_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ POSTINCREMENT_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ PREDECREMENT_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ POSTDECREMENT_ಅಭಿವ್ಯಕ್ತಿ:

      ಯದಿ (ವೃಕ್ಷ_CODE (arg) == C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ)
	{
	  ವೃಕ್ಷ inner = build_unary_op (location, code,
				       C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_ಅಭಿವ್ಯಕ್ತಿ (arg),
				       noconvert);
	  ಯದಿ (inner == error_mark_ಗಂಟು)
	    ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	  ret = build2 (C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (inner),
			C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_PRE (arg), inner);
	  gcc_assert (!C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_INT_OPERANDS (arg));
	  C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_NON_CONST (ret) = 1;
	  ಗಚ್ಛ return_build_unary_op;
	}

      /* Complain about anything that is not a true lvalue.  In
	 Objective-C, skip this check for property_refs.  */
      ಯದಿ (!objc_is_property_ref (arg)
	  && !lvalue_or_else (location,
			      arg, ((code == PREINCREMENT_ಅಭಿವ್ಯಕ್ತಿ
				     || code == POSTINCREMENT_ಅಭಿವ್ಯಕ್ತಿ)
				    ? lv_increment
				    : lv_decrement)))
	ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;

      ಯದಿ (warn_cxx_compat && ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (arg)) == ENUMERAL_TYPE)
	{
	  ಯದಿ (code == PREINCREMENT_ಅಭಿವ್ಯಕ್ತಿ || code == POSTINCREMENT_ಅಭಿವ್ಯಕ್ತಿ)
	    warning_at (location, OPT_Wc___compat,
			"increment of enumeration value is invalid in C++");
	  ಅನ್ಯಥಾ
	    warning_at (location, OPT_Wc___compat,
			"decrement of enumeration value is invalid in C++");
	}

      ಯದಿ (C_BOOLEAN_TYPE_P (ವೃಕ್ಷ_TYPE (arg)))
	{
	  ಯದಿ (code == PREINCREMENT_ಅಭಿವ್ಯಕ್ತಿ || code == POSTINCREMENT_ಅಭಿವ್ಯಕ್ತಿ)
	    warning_at (location, OPT_Wbool_operation,
			"increment of a boolean expression");
	  ಅನ್ಯಥಾ
	    warning_at (location, OPT_Wbool_operation,
			"decrement of a boolean expression");
	}

      /* Ensure the argument is fully folded inside any SAVE_EXPR.  */
      arg = c_fully_fold (arg, ಅಸತ್ಯ, ರಿಕ್ತ, ಸತ್ಯ);

      ತಾರ್ಕಿಕ atomic_op;
      atomic_op = really_atomic_lvalue (arg);

      /* Increment or decrement the real part of the value,
	 and don't change the imaginary part.  */
      ಯದಿ (typecode == COMPLEX_TYPE)
	{
	  ವೃಕ್ಷ real, imag;

	  pedwarn_c23 (location, OPT_Wpedantic,
		       "ISO C does not support %<++%> and %<--%> on complex "
		       "types before C2Y");

	  ಯದಿ (!atomic_op)
	    {
	      arg = stabilize_reference (arg);
	      real = build_unary_op (ಅಭಿವ್ಯಕ್ತಿ_LOCATION (arg), REALPART_ಅಭಿವ್ಯಕ್ತಿ, arg,
				     ಸತ್ಯ);
	      imag = build_unary_op (ಅಭಿವ್ಯಕ್ತಿ_LOCATION (arg), IMAGPART_ಅಭಿವ್ಯಕ್ತಿ, arg,
				     ಸತ್ಯ);
	      real = build_unary_op (ಅಭಿವ್ಯಕ್ತಿ_LOCATION (arg), code, real, ಸತ್ಯ);
	      ಯದಿ (real == error_mark_ಗಂಟು || imag == error_mark_ಗಂಟು)
		ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	      ret = build2 (COMPLEX_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (arg),
			    real, imag);
	      ಗಚ್ಛ return_build_unary_op;
	    }
	}

      /* Report invalid types.  */

      ಯದಿ (typecode != POINTER_TYPE && typecode != FIXED_POINT_TYPE
	  && typecode != INTEGER_TYPE && typecode != REAL_TYPE
	  && typecode != COMPLEX_TYPE && typecode != BITINT_TYPE
	  && !gnu_vector_type_p (ವೃಕ್ಷ_TYPE (arg)))
	{
	  ಯದಿ (code == PREINCREMENT_ಅಭಿವ್ಯಕ್ತಿ || code == POSTINCREMENT_ಅಭಿವ್ಯಕ್ತಿ)
	    error_at (location, "wrong type argument to increment");
	  ಅನ್ಯಥಾ
	    error_at (location, "wrong type argument to decrement");

	  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	}

      {
	ವೃಕ್ಷ inc;

	argtype = ವೃಕ್ಷ_TYPE (arg);

	/* Compute the increment.  */

	ಯದಿ (typecode == POINTER_TYPE)
	  {
	    /* If pointer target is an incomplete type,
	       we just cannot know how to do the arithmetic.  */
	    ಯದಿ (!COMPLETE_OR_VOID_TYPE_P (ವೃಕ್ಷ_TYPE (argtype)))
	      {
		ಯದಿ (code == PREINCREMENT_ಅಭಿವ್ಯಕ್ತಿ || code == POSTINCREMENT_ಅಭಿವ್ಯಕ್ತಿ)
		  error_at (location,
			    "increment of pointer to an incomplete type %qT",
			    ವೃಕ್ಷ_TYPE (argtype));
		ಅನ್ಯಥಾ
		  error_at (location,
			    "decrement of pointer to an incomplete type %qT",
			    ವೃಕ್ಷ_TYPE (argtype));
	      }
	    ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (argtype)) == FUNCTION_TYPE
		     || VOID_TYPE_P (ವೃಕ್ಷ_TYPE (argtype)))
	      {
		ಯದಿ (code == PREINCREMENT_ಅಭಿವ್ಯಕ್ತಿ || code == POSTINCREMENT_ಅಭಿವ್ಯಕ್ತಿ)
		  pedwarn (location, OPT_Wpointer_arith,
			   "wrong type argument to increment");
		ಅನ್ಯಥಾ
		  pedwarn (location, OPT_Wpointer_arith,
			   "wrong type argument to decrement");
	      }
	    ಅನ್ಯಥಾ
	      verify_type_context (location, TCTX_POINTER_ARITH,
				   ವೃಕ್ಷ_TYPE (argtype));

	    inc = c_size_in_bytes (ವೃಕ್ಷ_TYPE (argtype));
	    inc = convert_to_ptrofftype_loc (location, inc);
	  }
	ಅನ್ಯಥಾ ಯದಿ (FRACT_MODE_P (TYPE_MODE (argtype)))
	  {
	    /* For signed fract types, we invert ++ to -- or
	       -- to ++, and change inc from 1 to -1, because
	       it is not possible to represent 1 in signed fract constants.
	       For unsigned fract types, the result always overflows and
	       we get an undefined (original) or the maximum value.  */
	    ಯದಿ (code == PREINCREMENT_ಅಭಿವ್ಯಕ್ತಿ)
	      code = PREDECREMENT_ಅಭಿವ್ಯಕ್ತಿ;
	    ಅನ್ಯಥಾ ಯದಿ (code == PREDECREMENT_ಅಭಿವ್ಯಕ್ತಿ)
	      code = PREINCREMENT_ಅಭಿವ್ಯಕ್ತಿ;
	    ಅನ್ಯಥಾ ಯದಿ (code == POSTINCREMENT_ಅಭಿವ್ಯಕ್ತಿ)
	      code = POSTDECREMENT_ಅಭಿವ್ಯಕ್ತಿ;
	    ಅನ್ಯಥಾ /* code == POSTDECREMENT_EXPR  */
	      code = POSTINCREMENT_ಅಭಿವ್ಯಕ್ತಿ;

	    inc = integer_minus_one_ಗಂಟು;
	    inc = convert (argtype, inc);
	  }
	ಅನ್ಯಥಾ
	  {
	    inc = VECTOR_TYPE_P (argtype)
	      ? build_one_cst (argtype)
	      : integer_one_ಗಂಟು;
	    inc = convert (argtype, inc);
	  }

	/* If 'arg' is an Objective-C PROPERTY_REF expression, then we
	   need to ask Objective-C to build the increment or decrement
	   expression for it.  */
	ಯದಿ (objc_is_property_ref (arg))
	  ಪ್ರತ್ಯಾಗಮ objc_build_incr_ಅಭಿವ್ಯಕ್ತಿ_for_property_ref (location, code,
							arg, inc);

	/* Report a read-only lvalue.  */
	ಯದಿ (TYPE_READONLY (argtype))
	  {
	    readonly_error (location, arg,
			    ((code == PREINCREMENT_ಅಭಿವ್ಯಕ್ತಿ
			      || code == POSTINCREMENT_ಅಭಿವ್ಯಕ್ತಿ)
			     ? lv_increment : lv_decrement));
	    ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	  }
	ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_READONLY (arg))
	  readonly_warning (arg,
			    ((code == PREINCREMENT_ಅಭಿವ್ಯಕ್ತಿ
			      || code == POSTINCREMENT_ಅಭಿವ್ಯಕ್ತಿ)
			     ? lv_increment : lv_decrement));

	/* If the argument is atomic, use the special code sequences for
	   atomic compound assignment.  */
	ಯದಿ (atomic_op)
	  {
	    arg = stabilize_reference (arg);
	    ret = build_atomic_assign (location, arg,
				       ((code == PREINCREMENT_ಅಭಿವ್ಯಕ್ತಿ
					 || code == POSTINCREMENT_ಅಭಿವ್ಯಕ್ತಿ)
					? PLUS_ಅಭಿವ್ಯಕ್ತಿ
					: MINUS_ಅಭಿವ್ಯಕ್ತಿ),
				       (FRACT_MODE_P (TYPE_MODE (argtype))
					? inc
					: integer_one_ಗಂಟು),
				       (code == POSTINCREMENT_ಅಭಿವ್ಯಕ್ತಿ
					|| code == POSTDECREMENT_ಅಭಿವ್ಯಕ್ತಿ));
	    ಗಚ್ಛ return_build_unary_op;
	  }

	ವೃಕ್ಷ true_res;
	ಯದಿ (c_hardbool_type_attr (ವೃಕ್ಷ_TYPE (arg), ರಿಕ್ತ, &true_res))
	  {
	    ವೃಕ್ಷ larg = stabilize_reference (arg);
	    ವೃಕ್ಷ sarg = save_ಅಭಿವ್ಯಕ್ತಿ (larg);
	    ವಿಕಲ್ಪ (code)
	      {
	      ಪಕ್ಷ PREINCREMENT_ಅಭಿವ್ಯಕ್ತಿ:
		val = build2 (MODIFY_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (larg), larg, true_res);
		val = build2 (COMPOUND_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (larg), sarg, val);
		ಭಙ್ಗ;
	      ಪಕ್ಷ POSTINCREMENT_ಅಭಿವ್ಯಕ್ತಿ:
		val = build2 (MODIFY_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (larg), larg, true_res);
		val = build2 (COMPOUND_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (larg), val, sarg);
		val = build2 (COMPOUND_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (larg), sarg, val);
		ಭಙ್ಗ;
	      ಪಕ್ಷ PREDECREMENT_ಅಭಿವ್ಯಕ್ತಿ:
		{
		  ವೃಕ್ಷ rarg = convert_lvalue_to_rvalue (location, sarg,
							ಸತ್ಯ, ಸತ್ಯ);
		  rarg = invert_truthvalue_loc (location, rarg);
		  rarg = convert (ವೃಕ್ಷ_TYPE (sarg), rarg);
		  val = build2 (MODIFY_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (larg), larg, rarg);
		}
		ಭಙ್ಗ;
	      ಪಕ್ಷ POSTDECREMENT_ಅಭಿವ್ಯಕ್ತಿ:
		{
		  ವೃಕ್ಷ rarg = convert_lvalue_to_rvalue (location, sarg,
							ಸತ್ಯ, ಸತ್ಯ);
		  rarg = invert_truthvalue_loc (location, rarg);
		  ವೃಕ್ಷ iarg = convert (ವೃಕ್ಷ_TYPE (larg), rarg);
		  val = build2 (MODIFY_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (larg), larg, iarg);
		  val = build2 (COMPOUND_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (larg), val, sarg);
		  val = build2 (COMPOUND_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (larg), sarg, val);
		}
		ಭಙ್ಗ;
	      ಸ್ವಭಾವ:
		gcc_unreachable ();
	      }
	    ವೃಕ್ಷ_SIDE_EFFECTS (val) = 1;
	  }
	ಅನ್ಯಥಾ ಯದಿ (C_BOOLEAN_TYPE_P (ವೃಕ್ಷ_TYPE (arg)))
	  val = boolean_increment (code, arg);
	ಅನ್ಯಥಾ
	  val = build2 (code, ವೃಕ್ಷ_TYPE (arg), arg, inc);
	ವೃಕ್ಷ_SIDE_EFFECTS (val) = 1;
	ಯದಿ (TYPE_QUALS (ವೃಕ್ಷ_TYPE (val)) != TYPE_UNQUALIFIED)
	  ವೃಕ್ಷ_TYPE (val) = c_build_qualified_type (ವೃಕ್ಷ_TYPE (val),
						    TYPE_UNQUALIFIED);
	ret = val;
	ಗಚ್ಛ return_build_unary_op;
      }

    ಪಕ್ಷ ADDR_ಅಭಿವ್ಯಕ್ತಿ:
      /* Note that this operation never does default_conversion.  */

      /* The operand of unary '&' must be an lvalue (which excludes
	 expressions of type void), or, in C99, the result of a [] or
	 unary '*' operator.  */
      ಯದಿ (VOID_TYPE_P (ವೃಕ್ಷ_TYPE (arg))
	  && TYPE_QUALS (ವೃಕ್ಷ_TYPE (arg)) == TYPE_UNQUALIFIED
	  && (!INDIRECT_REF_P (arg) || !flag_isoc99))
	pedwarn (location, 0, "taking address of expression of type %<void%>");

      /* Let &* cancel out to simplify resulting code.  */
      ಯದಿ (INDIRECT_REF_P (arg))
	{
	  /* Don't let this be an lvalue.  */
	  ಯದಿ (lvalue_p (ವೃಕ್ಷ_OPERAND (arg, 0)))
	    ಪ್ರತ್ಯಾಗಮ non_lvalue_loc (location, ವೃಕ್ಷ_OPERAND (arg, 0));
	  ret = ವೃಕ್ಷ_OPERAND (arg, 0);
	  ಗಚ್ಛ return_build_unary_op;
	}

      /* Anything not already handled and not a true memory reference
	 or a non-lvalue array is an error.  */
      ಯದಿ (typecode != FUNCTION_TYPE && !noconvert
	  && !lvalue_or_else (location, arg, lv_addressof))
	ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;

      /* Move address operations inside C_MAYBE_CONST_EXPR to simplify
	 folding later.  */
      ಯದಿ (ವೃಕ್ಷ_CODE (arg) == C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ)
	{
	  ವೃಕ್ಷ inner = build_unary_op (location, code,
				       C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_ಅಭಿವ್ಯಕ್ತಿ (arg),
				       noconvert);
	  ret = build2 (C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (inner),
			C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_PRE (arg), inner);
	  gcc_assert (!C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_INT_OPERANDS (arg));
	  C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_NON_CONST (ret)
	    = C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_NON_CONST (arg);
	  ಗಚ್ಛ return_build_unary_op;
	}

      /* Ordinary case; arg is a COMPONENT_REF or a decl.  */

      argtype = ವೃಕ್ಷ_TYPE (arg);

      /* If the lvalue is const or volatile, merge that into the type
	 to which the address will point.  This is only needed
	 for function types.  */
      ಯದಿ ((DECL_P (arg) || REFERENCE_CLASS_P (arg))
	  && (ವೃಕ್ಷ_READONLY (arg) || ವೃಕ್ಷ_THIS_VOLATILE (arg))
	  && ವೃಕ್ಷ_CODE (argtype) == FUNCTION_TYPE)
	{
	  ಪೂರ್ಣಾಙ್ಕ orig_quals = TYPE_QUALS (strip_array_types (argtype));
	  ಪೂರ್ಣಾಙ್ಕ quals = orig_quals;

	  ಯದಿ (ವೃಕ್ಷ_READONLY (arg))
	    quals |= TYPE_QUAL_CONST;
	  ಯದಿ (ವೃಕ್ಷ_THIS_VOLATILE (arg))
	    quals |= TYPE_QUAL_VOLATILE;

	  argtype = c_build_qualified_type (argtype, quals);
	}

      ವಿಕಲ್ಪ (ವೃಕ್ಷ_CODE (arg))
	{
	ಪಕ್ಷ COMPONENT_REF:
	  ಯದಿ (DECL_C_BIT_FIELD (ವೃಕ್ಷ_OPERAND (arg, 1)))
	    {
	      error_at (location, "cannot take address of bit-field %qD",
			ವೃಕ್ಷ_OPERAND (arg, 1));
	      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	    }

	  /* fall through */

	ಪಕ್ಷ ARRAY_REF:
	  ಯದಿ (TYPE_REVERSE_STORAGE_ORDER (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_OPERAND (arg, 0))))
	    {
	      ಯದಿ (!AGGREGATE_TYPE_P (ವೃಕ್ಷ_TYPE (arg))
		  && !POINTER_TYPE_P (ವೃಕ್ಷ_TYPE (arg))
		  && !VECTOR_TYPE_P (ವೃಕ್ಷ_TYPE (arg)))
		{
		  error_at (location, "cannot take address of scalar with "
			    "reverse storage order");
		  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
		}

	      ಯದಿ (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (arg)) == ARRAY_TYPE
		  && TYPE_REVERSE_STORAGE_ORDER (ವೃಕ್ಷ_TYPE (arg)))
		warning_at (location, OPT_Wscalar_storage_order,
			    "address of array with reverse scalar storage "
			    "order requested");
	    }

	ಸ್ವಭಾವ:
	  ಭಙ್ಗ;
	}

      ಯದಿ (!c_mark_addressable (arg))
	ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;

      gcc_assert (ವೃಕ್ಷ_CODE (arg) != COMPONENT_REF
		  || !DECL_C_BIT_FIELD (ವೃಕ್ಷ_OPERAND (arg, 1)));

      argtype = c_build_pointer_type (argtype);

      /* ??? Cope with user tricks that amount to offsetof.  Delete this
	 when we have proper support for integer constant expressions.  */
      val = get_base_address (arg);
      ಯದಿ (val && INDIRECT_REF_P (val)
          && ವೃಕ್ಷ_CONSTANT (ವೃಕ್ಷ_OPERAND (val, 0)))
	{
	  ret = fold_offsetof (arg, argtype);
	  ಗಚ್ಛ return_build_unary_op;
	}

      val = build1 (ADDR_ಅಭಿವ್ಯಕ್ತಿ, argtype, arg);

      ret = val;
      ಗಚ್ಛ return_build_unary_op;

    ಪಕ್ಷ PAREN_ಅಭಿವ್ಯಕ್ತಿ:
      ret = build1 (code, ವೃಕ್ಷ_TYPE (arg), arg);
      ಗಚ್ಛ return_build_unary_op;

    ಸ್ವಭಾವ:
      gcc_unreachable ();
    }

  ಯದಿ (argtype == NULL_ವೃಕ್ಷ)
    argtype = ವೃಕ್ಷ_TYPE (arg);
  ಯದಿ (ವೃಕ್ಷ_CODE (arg) == INTEGER_CST)
    ret = (require_constant_ಮೌಲ್ಯ
	   ? fold_build1_initializer_loc (location, code, argtype, arg)
	   : fold_build1_loc (location, code, argtype, arg));
  ಅನ್ಯಥಾ
    ret = build1 (code, argtype, arg);
 return_build_unary_op:
  gcc_assert (ret != error_mark_ಗಂಟು);
  ಯದಿ (ವೃಕ್ಷ_CODE (ret) == INTEGER_CST && !ವೃಕ್ಷ_OVERFLOW (ret)
      && !(ವೃಕ್ಷ_CODE (xarg) == INTEGER_CST && !ವೃಕ್ಷ_OVERFLOW (xarg)))
    ret = build1 (NOP_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (ret), ret);
  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (ret) != INTEGER_CST && int_operands)
    ret = note_integer_operands (ret);
  ಯದಿ (eptype)
    ret = build1 (EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ, eptype, ret);
  protected_set_ಅಭಿವ್ಯಕ್ತಿ_location (ret, location);
  ಪ್ರತ್ಯಾಗಮ ret;
}

/* Return nonzero if REF is an lvalue valid for this language.
   Lvalues can be assigned, unless their type has TYPE_READONLY.
   Lvalues can have their address taken, unless they have C_DECL_REGISTER.  */

ತಾರ್ಕಿಕ
lvalue_p (const_ವೃಕ್ಷ ref)
{
  ಧ್ರುವ ಗಣನಾ ವೃಕ್ಷ_code code = ವೃಕ್ಷ_CODE (ref);

  ವಿಕಲ್ಪ (code)
    {
    ಪಕ್ಷ REALPART_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ IMAGPART_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ COMPONENT_REF:
      ಪ್ರತ್ಯಾಗಮ lvalue_p (ವೃಕ್ಷ_OPERAND (ref, 0));

    ಪಕ್ಷ C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ:
      ಪ್ರತ್ಯಾಗಮ lvalue_p (ವೃಕ್ಷ_OPERAND (ref, 1));

    ಪಕ್ಷ COMPOUND_LITERAL_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ STRING_CST:
      ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;

    ಪಕ್ಷ MEM_REF:
    ಪಕ್ಷ TARGET_MEM_REF:
      /* MEM_REFs can appear from -fgimple parsing or folding, so allow them
	 here as well.  */
    ಪಕ್ಷ INDIRECT_REF:
    ಪಕ್ಷ ARRAY_REF:
    ಪಕ್ಷ VAR_DECL:
    ಪಕ್ಷ PARM_DECL:
    ಪಕ್ಷ RESULT_DECL:
    ಪಕ್ಷ ERROR_MARK:
      ಪ್ರತ್ಯಾಗಮ (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (ref)) != FUNCTION_TYPE
	      && ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (ref)) != METHOD_TYPE);

    ಪಕ್ಷ BIND_ಅಭಿವ್ಯಕ್ತಿ:
      ಪ್ರತ್ಯಾಗಮ ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (ref)) == ARRAY_TYPE;

    ಪಕ್ಷ CALL_ಅಭಿವ್ಯಕ್ತಿ:
      ಪ್ರತ್ಯಾಗಮ is_access_with_size_p (ref);

    ಸ್ವಭಾವ:
      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
    }
}

/* Give a warning for storing in something that is read-only in GCC
   terms but not const in ISO C terms.  */

ಸ್ಥಿರ ಶೂನ್ಯ
readonly_warning (ವೃಕ್ಷ arg, ಗಣನಾ lvalue_use use)
{
  ವಿಕಲ್ಪ (use)
    {
    ಪಕ್ಷ lv_assign:
      warning (0, "assignment of read-only location %qE", arg);
      ಭಙ್ಗ;
    ಪಕ್ಷ lv_increment:
      warning (0, "increment of read-only location %qE", arg);
      ಭಙ್ಗ;
    ಪಕ್ಷ lv_decrement:
      warning (0, "decrement of read-only location %qE", arg);
      ಭಙ್ಗ;
    ಸ್ವಭಾವ:
      gcc_unreachable ();
    }
  ಪ್ರತ್ಯಾಗಮ;
}


/* Return nonzero if REF is an lvalue valid for this language;
   otherwise, print an error message and return zero.  USE says
   how the lvalue is being used and so selects the error message.
   LOCATION is the location at which any error should be reported.  */

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ
lvalue_or_else (location_t loc, const_ವೃಕ್ಷ ref, ಗಣನಾ lvalue_use use)
{
  ಪೂರ್ಣಾಙ್ಕ win = lvalue_p (ref);

  ಯದಿ (!win)
    lvalue_error (loc, use);

  ಪ್ರತ್ಯಾಗಮ win;
}

/* Mark EXP saying that we need to be able to take the
   address of it; it should not be allocated in a register.
   Returns true if successful.  ARRAY_REF_P is true if this
   is for ARRAY_REF construction - in that case we don't want
   to look through VIEW_CONVERT_EXPR from VECTOR_TYPE to ARRAY_TYPE,
   it is fine to use ARRAY_REFs for vector subscripts on vector
   register variables.  If OVERRIDE_REGISTER, clear DECL_REGISTER rather
   than producing an error for taking the address of a register.  */

ತಾರ್ಕಿಕ
c_mark_addressable (ವೃಕ್ಷ exp, ತಾರ್ಕಿಕ array_ref_p, ತಾರ್ಕಿಕ override_register)
{
  ವೃಕ್ಷ x = exp;

  ಯಾವತ್ (1)
    ವಿಕಲ್ಪ (ವೃಕ್ಷ_CODE (x))
      {
      ಪಕ್ಷ VIEW_CONVERT_ಅಭಿವ್ಯಕ್ತಿ:
	ಯದಿ (array_ref_p
	    && ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (x)) == ARRAY_TYPE
	    && VECTOR_TYPE_P (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_OPERAND (x, 0))))
	  ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
	x = ವೃಕ್ಷ_OPERAND (x, 0);
	ಭಙ್ಗ;

      ಪಕ್ಷ COMPONENT_REF:
	ಯದಿ (DECL_C_BIT_FIELD (ವೃಕ್ಷ_OPERAND (x, 1)))
	  {
	    error ("cannot take address of bit-field %qD",
		   ವೃಕ್ಷ_OPERAND (x, 1));
	    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	  }
	/* FALLTHRU */
      ಪಕ್ಷ ADDR_ಅಭಿವ್ಯಕ್ತಿ:
      ಪಕ್ಷ ARRAY_REF:
      ಪಕ್ಷ REALPART_ಅಭಿವ್ಯಕ್ತಿ:
      ಪಕ್ಷ IMAGPART_ಅಭಿವ್ಯಕ್ತಿ:
	x = ವೃಕ್ಷ_OPERAND (x, 0);
	ಭಙ್ಗ;

      ಪಕ್ಷ COMPOUND_LITERAL_ಅಭಿವ್ಯಕ್ತಿ:
	ಯದಿ (C_DECL_REGISTER (COMPOUND_LITERAL_ಅಭಿವ್ಯಕ್ತಿ_DECL (x)))
	  {
	    ಯದಿ (override_register)
	      DECL_REGISTER (COMPOUND_LITERAL_ಅಭಿವ್ಯಕ್ತಿ_DECL (x)) = 0;
	    ಅನ್ಯಥಾ
	      {
		error ("address of register compound literal requested");
		ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	      }
	  }
	ವೃಕ್ಷ_ADDRESSABLE (x) = 1;
	ವೃಕ್ಷ_ADDRESSABLE (COMPOUND_LITERAL_ಅಭಿವ್ಯಕ್ತಿ_DECL (x)) = 1;
	ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;

      ಪಕ್ಷ CONSTRUCTOR:
	ವೃಕ್ಷ_ADDRESSABLE (x) = 1;
	ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;

      ಪಕ್ಷ VAR_DECL:
      ಪಕ್ಷ CONST_DECL:
      ಪಕ್ಷ PARM_DECL:
      ಪಕ್ಷ RESULT_DECL:
	ಯದಿ (C_DECL_REGISTER (x)
	    && DECL_NONLOCAL (x))
	  {
	    ಯದಿ (ವೃಕ್ಷ_PUBLIC (x) || is_global_var (x))
	      {
		error
		  ("global register variable %qD used in nested function", x);
		ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	      }
	    pedwarn (ಒಳಹರಿವು_location, 0, "register variable %qD used in nested function", x);
	  }
	ಅನ್ಯಥಾ ಯದಿ (C_DECL_REGISTER (x))
	  {
	    ಯದಿ (ವೃಕ್ಷ_PUBLIC (x) || is_global_var (x))
	      error ("address of global register variable %qD requested", x);
	    ಅನ್ಯಥಾ ಯದಿ (override_register && !DECL_HARD_REGISTER (x))
	      {
		DECL_REGISTER (x) = 0;
		ವೃಕ್ಷ_ADDRESSABLE (x) = 1;
		mark_decl_used (x, ಸತ್ಯ);
		ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
	      }
	    ಅನ್ಯಥಾ
	      error ("address of register variable %qD requested", x);
	    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	  }

	/* FALLTHRU */
      ಪಕ್ಷ FUNCTION_DECL:
	ವೃಕ್ಷ_ADDRESSABLE (x) = 1;
	mark_decl_used (x, ಸತ್ಯ);
	/* FALLTHRU */
      ಸ್ವಭಾವ:
	ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
    }
}

/* Convert EXPR to TYPE, warning about conversion problems with
   constants.  SEMANTIC_TYPE is the type this conversion would use
   without excess precision. If SEMANTIC_TYPE is NULL, this function
   is equivalent to convert_and_check. This function is a wrapper that
   handles conversions that may be different than
   the usual ones because of excess precision.  */

ಸ್ಥಿರ ವೃಕ್ಷ
ep_convert_and_check (location_t loc, ವೃಕ್ಷ type, ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ,
		      ವೃಕ್ಷ semantic_type)
{
  ಯದಿ (ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ) == type)
    ಪ್ರತ್ಯಾಗಮ ಅಭಿವ್ಯಕ್ತಿ;

  /* For C11, integer conversions may have results with excess
     precision.  */
  ಯದಿ (flag_isoc11 || !semantic_type)
    ಪ್ರತ್ಯಾಗಮ convert_and_check (loc, type, ಅಭಿವ್ಯಕ್ತಿ);

  ಯದಿ (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ)) == INTEGER_TYPE
      && ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ) != semantic_type)
    {
      /* For integers, we need to check the real conversion, not
	 the conversion to the excess precision type.  */
      ಅಭಿವ್ಯಕ್ತಿ = convert_and_check (loc, semantic_type, ಅಭಿವ್ಯಕ್ತಿ);
    }
  /* Result type is the excess precision type, which should be
     large enough, so do not check.  */
  ಪ್ರತ್ಯಾಗಮ convert (type, ಅಭಿವ್ಯಕ್ತಿ);
}

/* If EXPR refers to a built-in declared without a prototype returns
   the actual type of the built-in and, if non-null, set *BLTIN to
   a pointer to the built-in.  Otherwise return the type of EXPR
   and clear *BLTIN if non-null.  */

ಸ್ಥಿರ ವೃಕ್ಷ
type_or_builtin_type (ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ *bltin = ರಿಕ್ತ)
{
  ವೃಕ್ಷ dummy;
  ಯದಿ (!bltin)
    bltin = &dummy;

  *bltin = NULL_ವೃಕ್ಷ;

  ವೃಕ್ಷ type = ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ);
  ಯದಿ (ವೃಕ್ಷ_CODE (ಅಭಿವ್ಯಕ್ತಿ) != ADDR_ಅಭಿವ್ಯಕ್ತಿ)
    ಪ್ರತ್ಯಾಗಮ type;

  ವೃಕ್ಷ oper = ವೃಕ್ಷ_OPERAND (ಅಭಿವ್ಯಕ್ತಿ, 0);
  ಯದಿ (!DECL_P (oper)
      || ವೃಕ್ಷ_CODE (oper) != FUNCTION_DECL
      || !fndecl_built_in_p (oper, BUILT_IN_NORMAL))
    ಪ್ರತ್ಯಾಗಮ type;

  built_in_function code = DECL_FUNCTION_CODE (oper);
  ಯದಿ (!C_DECL_BUILTIN_PROTOTYPE (oper))
    ಪ್ರತ್ಯಾಗಮ type;

  ಯದಿ ((*bltin = builtin_decl_implicit (code)))
    type = c_build_pointer_type (ವೃಕ್ಷ_TYPE (*bltin));

  ಪ್ರತ್ಯಾಗಮ type;
}

/* Build and return a conditional expression IFEXP ? OP1 : OP2.  If
   IFEXP_BCP then the condition is a call to __builtin_constant_p, and
   if folded to an integer constant then the unselected half may
   contain arbitrary operations not normally permitted in constant
   expressions.  Set the location of the expression to LOC.  */

ವೃಕ್ಷ
build_conditional_ಅಭಿವ್ಯಕ್ತಿ (location_t colon_loc, ವೃಕ್ಷ ifexp, ತಾರ್ಕಿಕ ifexp_bcp,
			ವೃಕ್ಷ op1, ವೃಕ್ಷ op1_original_type, location_t op1_loc,
			ವೃಕ್ಷ op2, ವೃಕ್ಷ op2_original_type, location_t op2_loc)
{
  ವೃಕ್ಷ type1;
  ವೃಕ್ಷ type2;
  ವೃಕ್ಷ result_type = ರಿಕ್ತ;
  ವೃಕ್ಷ semantic_result_type = ರಿಕ್ತ;
  ವೃಕ್ಷ orig_op1 = op1, orig_op2 = op2;
  ತಾರ್ಕಿಕ int_const, op1_int_operands, op2_int_operands, int_operands;
  ತಾರ್ಕಿಕ ifexp_int_operands;
  ವೃಕ್ಷ ret;

  op1_int_operands = ಅಭಿವ್ಯಕ್ತಿ_INT_CONST_OPERANDS (orig_op1);
  ಯದಿ (op1_int_operands)
    op1 = remove_c_maybe_const_ಅಭಿವ್ಯಕ್ತಿ (op1);
  op2_int_operands = ಅಭಿವ್ಯಕ್ತಿ_INT_CONST_OPERANDS (orig_op2);
  ಯದಿ (op2_int_operands)
    op2 = remove_c_maybe_const_ಅಭಿವ್ಯಕ್ತಿ (op2);
  ifexp_int_operands = ಅಭಿವ್ಯಕ್ತಿ_INT_CONST_OPERANDS (ifexp);
  ಯದಿ (ifexp_int_operands)
    ifexp = remove_c_maybe_const_ಅಭಿವ್ಯಕ್ತಿ (ifexp);

  /* Promote both alternatives.  */

  ಯದಿ (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (op1)) != VOID_TYPE)
    op1 = default_conversion (op1);
  ಯದಿ (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (op2)) != VOID_TYPE)
    op2 = default_conversion (op2);

  ಯದಿ (ವೃಕ್ಷ_CODE (ifexp) == ERROR_MARK
      || ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (op1)) == ERROR_MARK
      || ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (op2)) == ERROR_MARK)
    ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;

  ವೃಕ್ಷ bltin1 = NULL_ವೃಕ್ಷ;
  ವೃಕ್ಷ bltin2 = NULL_ವೃಕ್ಷ;
  type1 = type_or_builtin_type (op1, &bltin1);
  ಧ್ರುವ ಗಣನಾ ವೃಕ್ಷ_code code1 = ವೃಕ್ಷ_CODE (type1);
  type2 = type_or_builtin_type (op2, &bltin2);
  ಧ್ರುವ ಗಣನಾ ವೃಕ್ಷ_code code2 = ವೃಕ್ಷ_CODE (type2);

  ಯದಿ (code1 == POINTER_TYPE && reject_gcc_builtin (op1))
    ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;

  ಯದಿ (code2 == POINTER_TYPE && reject_gcc_builtin (op2))
    ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;

  /* C90 does not permit non-lvalue arrays in conditional expressions.
     In C99 they will be pointers by now.  */
  ಯದಿ (code1 == ARRAY_TYPE || code2 == ARRAY_TYPE)
    {
      error_at (colon_loc, "non-lvalue array in conditional expression");
      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
    }

  ಯದಿ ((ವೃಕ್ಷ_CODE (op1) == EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ
       || ವೃಕ್ಷ_CODE (op2) == EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ)
      && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	  || code1 == COMPLEX_TYPE || code1 == BITINT_TYPE)
      && (code2 == INTEGER_TYPE || code2 == REAL_TYPE
	  || code2 == COMPLEX_TYPE || code2 == BITINT_TYPE))
    {
      semantic_result_type = c_common_type (type1, type2);
      ಯದಿ (ವೃಕ್ಷ_CODE (op1) == EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ)
	{
	  op1 = ವೃಕ್ಷ_OPERAND (op1, 0);
	  type1 = ವೃಕ್ಷ_TYPE (op1);
	  gcc_assert (ವೃಕ್ಷ_CODE (type1) == code1);
	}
      ಯದಿ (ವೃಕ್ಷ_CODE (op2) == EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ)
	{
	  op2 = ವೃಕ್ಷ_OPERAND (op2, 0);
	  type2 = ವೃಕ್ಷ_TYPE (op2);
	  gcc_assert (ವೃಕ್ಷ_CODE (type2) == code2);
	}
    }

  ಯದಿ (warn_cxx_compat)
    {
      ವೃಕ್ಷ t1 = op1_original_type ? op1_original_type : ವೃಕ್ಷ_TYPE (orig_op1);
      ವೃಕ್ಷ t2 = op2_original_type ? op2_original_type : ವೃಕ್ಷ_TYPE (orig_op2);

      ಯದಿ (ವೃಕ್ಷ_CODE (t1) == ENUMERAL_TYPE
	  && ವೃಕ್ಷ_CODE (t2) == ENUMERAL_TYPE
	  && TYPE_MAIN_VARIANT (t1) != TYPE_MAIN_VARIANT (t2))
	warning_at (colon_loc, OPT_Wc___compat,
		    "different enum types in conditional is "
		    "invalid in C++: %qT vs %qT", t1, t2);
    }

  ಯದಿ (warn_zero_as_null_pointer_constant
      && c_inhibit_evaluation_warnings == 0)
    {
      ಯದಿ ((code1 == POINTER_TYPE || code1 == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type2) && null_pointer_constant_p (orig_op2))
	warning_at (op2_loc, OPT_Wzero_as_null_pointer_constant,
		    "zero as null pointer constant");

      ಯದಿ ((code2 == POINTER_TYPE || code2 == NULLPTR_TYPE)
	  && INTEGRAL_TYPE_P (type1) && null_pointer_constant_p (orig_op1))
	warning_at (op1_loc, OPT_Wzero_as_null_pointer_constant,
		    "zero as null pointer constant");
    }

  /* Quickly detect the usual case where op1 and op2 have the same type
     after promotion.  */
  ಯದಿ (TYPE_MAIN_VARIANT (type1) == TYPE_MAIN_VARIANT (type2))
    {
      ಯದಿ (type1 == type2)
	result_type = type1;
      ಅನ್ಯಥಾ
	result_type = TYPE_MAIN_VARIANT (type1);
    }
  ಅನ್ಯಥಾ ಯದಿ ((code1 == INTEGER_TYPE || code1 == REAL_TYPE
	    || code1 == COMPLEX_TYPE || code1 == BITINT_TYPE)
	   && (code2 == INTEGER_TYPE || code2 == REAL_TYPE
	       || code2 == COMPLEX_TYPE || code2 == BITINT_TYPE))
    {
      /* In C11, a conditional expression between a floating-point
	 type and an integer type should convert the integer type to
	 the evaluation format of the floating-point type, with
	 possible excess precision.  */
      ವೃಕ್ಷ eptype1 = type1;
      ವೃಕ್ಷ eptype2 = type2;
      ಯದಿ (flag_isoc11)
	{
	  ವೃಕ್ಷ eptype;
	  ಯದಿ (ANY_INTEGRAL_TYPE_P (type1)
	      && (eptype = excess_precision_type (type2)) != NULL_ವೃಕ್ಷ)
	    {
	      eptype2 = eptype;
	      ಯದಿ (!semantic_result_type)
		semantic_result_type = c_common_type (type1, type2);
	    }
	  ಅನ್ಯಥಾ ಯದಿ (ANY_INTEGRAL_TYPE_P (type2)
		   && (eptype = excess_precision_type (type1)) != NULL_ವೃಕ್ಷ)
	    {
	      eptype1 = eptype;
	      ಯದಿ (!semantic_result_type)
		semantic_result_type = c_common_type (type1, type2);
	    }
	}
      result_type = c_common_type (eptype1, eptype2);
      ಯದಿ (result_type == error_mark_ಗಂಟು)
	ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
      do_warn_double_promotion (result_type, type1, type2,
				"implicit conversion from %qT to %qT to "
				"match other result of conditional",
				colon_loc);

      /* If -Wsign-compare, warn here if type1 and type2 have
	 different signedness.  We'll promote the signed to unsigned
	 and later code won't know it used to be different.
	 Do this check on the original types, so that explicit casts
	 will be considered, but default promotions won't.  */
      ಯದಿ (c_inhibit_evaluation_warnings == 0)
	{
	  ಪೂರ್ಣಾಙ್ಕ unsigned_op1 = TYPE_UNSIGNED (ವೃಕ್ಷ_TYPE (orig_op1));
	  ಪೂರ್ಣಾಙ್ಕ unsigned_op2 = TYPE_UNSIGNED (ವೃಕ್ಷ_TYPE (orig_op2));

	  ಯದಿ (unsigned_op1 ^ unsigned_op2)
	    {
	      /* Do not warn if the result type is signed, since the
		 signed type will only be chosen if it can represent
		 all the values of the unsigned type.  */
	      ಯದಿ (!TYPE_UNSIGNED (result_type))
		/* OK */;
	      ಅನ್ಯಥಾ
		{
		  ತಾರ್ಕಿಕ op1_maybe_const = ಸತ್ಯ;
		  ತಾರ್ಕಿಕ op2_maybe_const = ಸತ್ಯ;

		  /* Do not warn if the signed quantity is an
		     unsuffixed integer literal (or some static
		     constant expression involving such literals) and
		     it is non-negative.  This warning requires the
		     operands to be folded for best results, so do
		     that folding in this case even without
		     warn_sign_compare to avoid warning options
		     possibly affecting code generation.  */
		  c_inhibit_evaluation_warnings
		    += (ifexp == truthvalue_false_ಗಂಟು);
		  op1 = c_fully_fold (op1, require_constant_ಮೌಲ್ಯ,
				      &op1_maybe_const);
		  c_inhibit_evaluation_warnings
		    -= (ifexp == truthvalue_false_ಗಂಟು);

		  c_inhibit_evaluation_warnings
		    += (ifexp == truthvalue_true_ಗಂಟು);
		  op2 = c_fully_fold (op2, require_constant_ಮೌಲ್ಯ,
				      &op2_maybe_const);
		  c_inhibit_evaluation_warnings
		    -= (ifexp == truthvalue_true_ಗಂಟು);

		  ಯದಿ (warn_sign_compare)
		    {
		      ಯದಿ ((unsigned_op2
			   && ವೃಕ್ಷ_ಅಭಿವ್ಯಕ್ತಿ_nonnegative_p (op1))
			  || (unsigned_op1
			      && ವೃಕ್ಷ_ಅಭಿವ್ಯಕ್ತಿ_nonnegative_p (op2)))
			/* OK */;
		      ಅನ್ಯಥಾ ಯದಿ (unsigned_op2)
			warning_at (op1_loc, OPT_Wsign_compare,
				    "operand of %<?:%> changes signedness from "
				    "%qT to %qT due to unsignedness of other "
				    "operand", ವೃಕ್ಷ_TYPE (orig_op1),
				    ವೃಕ್ಷ_TYPE (orig_op2));
		      ಅನ್ಯಥಾ
			warning_at (op2_loc, OPT_Wsign_compare,
				    "operand of %<?:%> changes signedness from "
				    "%qT to %qT due to unsignedness of other "
				    "operand", ವೃಕ್ಷ_TYPE (orig_op2),
				    ವೃಕ್ಷ_TYPE (orig_op1));
		    }
		  ಯದಿ (!op1_maybe_const || ವೃಕ್ಷ_CODE (op1) != INTEGER_CST)
		    op1 = c_wrap_maybe_const (op1, !op1_maybe_const);
		  ಯದಿ (!op2_maybe_const || ವೃಕ್ಷ_CODE (op2) != INTEGER_CST)
		    op2 = c_wrap_maybe_const (op2, !op2_maybe_const);
		}
	    }
	}
    }
  ಅನ್ಯಥಾ ಯದಿ (code1 == VOID_TYPE || code2 == VOID_TYPE)
    {
      ಯದಿ (code1 != VOID_TYPE || code2 != VOID_TYPE)
	pedwarn (colon_loc, OPT_Wpedantic,
		 "ISO C forbids conditional expr with only one void side");
      result_type = void_type_ಗಂಟು;
    }
  ಅನ್ಯಥಾ ಯದಿ (code1 == POINTER_TYPE && code2 == POINTER_TYPE)
    {
      addr_space_t as1 = TYPE_ADDR_SPACE (ವೃಕ್ಷ_TYPE (type1));
      addr_space_t as2 = TYPE_ADDR_SPACE (ವೃಕ್ಷ_TYPE (type2));
      addr_space_t as_common;

      ಯದಿ (comp_target_types (colon_loc, type1, type2))
	{
	  ifexp = save_ಅಭಿವ್ಯಕ್ತಿ (ifexp);
	  result_type = common_pointer_type (type1, type2, ifexp);
	}
      ಅನ್ಯಥಾ ಯದಿ (null_pointer_constant_p (orig_op1))
	result_type = type2;
      ಅನ್ಯಥಾ ಯದಿ (null_pointer_constant_p (orig_op2))
	result_type = type1;
      ಅನ್ಯಥಾ ಯದಿ (!addr_space_superset (as1, as2, &as_common))
	{
	  error_at (colon_loc, "pointers to disjoint address spaces "
		    "used in conditional expression");
	  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	}
      ಅನ್ಯಥಾ ಯದಿ ((VOID_TYPE_P (ವೃಕ್ಷ_TYPE (type1))
		&& !TYPE_ATOMIC (ವೃಕ್ಷ_TYPE (type1)))
	       || (VOID_TYPE_P (ವೃಕ್ಷ_TYPE (type2))
		   && !TYPE_ATOMIC (ವೃಕ್ಷ_TYPE (type2))))
	{
	  ವೃಕ್ಷ t1 = ವೃಕ್ಷ_TYPE (type1);
	  ವೃಕ್ಷ t2 = ವೃಕ್ಷ_TYPE (type2);
	  ಯದಿ (!(VOID_TYPE_P (t1)
		&& !TYPE_ATOMIC (t1)))
	   {
	     /* roles are swapped */
	     t1 = t2;
	     t2 = ವೃಕ್ಷ_TYPE (type1);
	   }
	  ವೃಕ್ಷ t2_stripped = strip_array_types (t2);
	  ಯದಿ ((ವೃಕ್ಷ_CODE (t2) == ARRAY_TYPE)
	      && (TYPE_QUALS (t2_stripped) & ~TYPE_QUALS (t1)))
	    {
	      ಯದಿ (!flag_isoc23)
		warning_at (colon_loc, OPT_Wdiscarded_array_qualifiers,
			    "pointer to array loses qualifier "
			    "in conditional expression");
	      ಅನ್ಯಥಾ ಯದಿ (warn_c11_c23_compat > 0)
		warning_at (colon_loc, OPT_Wc11_c23_compat,
			    "pointer to array loses qualifier "
			    "in conditional expression in ISO C before C23");
	    }
	  ಯದಿ (ವೃಕ್ಷ_CODE (t2) == FUNCTION_TYPE)
	    pedwarn (colon_loc, OPT_Wpedantic,
		     "ISO C forbids conditional expr between "
		     "%<void *%> and function pointer");
	  /* for array, use qualifiers of element type */
	  ಯದಿ (flag_isoc23)
	    t2 = t2_stripped;
	  result_type = c_build_pointer_type (qualify_type (t1, t2));
	}
      /* Objective-C pointer comparisons are a bit more lenient.  */
      ಅನ್ಯಥಾ ಯದಿ (objc_have_common_type (type1, type2, -3, NULL_ವೃಕ್ಷ))
	result_type = objc_common_type (type1, type2);
      ಅನ್ಯಥಾ
	{
	  ಪೂರ್ಣಾಙ್ಕ qual = ENCODE_QUAL_ADDR_SPACE (as_common);
	  ಗಣನಾ diagnostics::kind kind = diagnostics::kind::permerror;
	  ಯದಿ (!flag_isoc99)
	    /* This downgrade to a warning ensures that -std=gnu89
	       -pedantic-errors does not flag these mismatches between
	       builtins as errors (as diagnostics::kind::permerror would)
	       ISO C99 and later do not have implicit function declarations,
	       so the mismatch cannot occur naturally there.  */
	    kind = (bltin1 && bltin2
		    ? diagnostics::kind::warning
		    : diagnostics::kind::pedwarn);
	  ಯದಿ (emit_diagnostic (kind, colon_loc, OPT_Wincompatible_pointer_types,
			       "pointer type mismatch "
			       "in conditional expression"))
	    {
	      inform (op1_loc, "first expression has type %qT", type1);
	      inform (op2_loc, "second expression has type %qT", type2);
	    }
	  result_type = c_build_pointer_type
			  (c_build_qualified_type (void_type_ಗಂಟು, qual));
	}
    }
  ಅನ್ಯಥಾ ಯದಿ (code1 == POINTER_TYPE
	   && (code2 == INTEGER_TYPE || code2 == BITINT_TYPE))
    {
      ಯದಿ (!null_pointer_constant_p (orig_op2))
	permerror_opt (colon_loc, OPT_Wint_conversion,
		       "pointer/integer type mismatch "
		       "in conditional expression");
      ಅನ್ಯಥಾ
	{
	  op2 = null_pointer_ಗಂಟು;
	}
      result_type = type1;
    }
  ಅನ್ಯಥಾ ಯದಿ (code2 == POINTER_TYPE
	   && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
    {
      ಯದಿ (!null_pointer_constant_p (orig_op1))
	permerror_opt (colon_loc, OPT_Wint_conversion,
		       "pointer/integer type mismatch "
		       "in conditional expression");
      ಅನ್ಯಥಾ
	{
	  op1 = null_pointer_ಗಂಟು;
	}
      result_type = type2;
    }
  /* 6.5.15: "if one is a null pointer constant (other than a pointer) or has
     type nullptr_t and the other is a pointer, the result type is the pointer
     type."  */
  ಅನ್ಯಥಾ ಯದಿ (code1 == NULLPTR_TYPE && code2 == POINTER_TYPE)
    result_type = type2;
  ಅನ್ಯಥಾ ಯದಿ (code1 == POINTER_TYPE && code2 == NULLPTR_TYPE)
    result_type = type1;
  ಅನ್ಯಥಾ ಯದಿ (RECORD_OR_UNION_TYPE_P (type1) && RECORD_OR_UNION_TYPE_P (type2)
	   && comptypes (TYPE_MAIN_VARIANT (type1),
			 TYPE_MAIN_VARIANT (type2)))
    result_type = composite_type (TYPE_MAIN_VARIANT (type1),
				  TYPE_MAIN_VARIANT (type2));

  ಯದಿ (!result_type)
    {
      ಯದಿ (flag_cond_mismatch)
	result_type = void_type_ಗಂಟು;
      ಅನ್ಯಥಾ
	{
	  error_at (colon_loc, "type mismatch in conditional expression");
	  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
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

  ಯದಿ (ifexp_bcp && ifexp == truthvalue_true_ಗಂಟು)
    {
      op2_int_operands = ಸತ್ಯ;
      op1 = c_fully_fold (op1, require_constant_ಮೌಲ್ಯ, ರಿಕ್ತ);
    }
  ಯದಿ (ifexp_bcp && ifexp == truthvalue_false_ಗಂಟು)
    {
      op1_int_operands = ಸತ್ಯ;
      op2 = c_fully_fold (op2, require_constant_ಮೌಲ್ಯ, ರಿಕ್ತ);
    }
  int_const = int_operands = (ifexp_int_operands
			      && op1_int_operands
			      && op2_int_operands);
  ಯದಿ (int_operands)
    {
      int_const = ((ifexp == truthvalue_true_ಗಂಟು
		    && ವೃಕ್ಷ_CODE (orig_op1) == INTEGER_CST
		    && !ವೃಕ್ಷ_OVERFLOW (orig_op1))
		   || (ifexp == truthvalue_false_ಗಂಟು
		       && ವೃಕ್ಷ_CODE (orig_op2) == INTEGER_CST
		       && !ವೃಕ್ಷ_OVERFLOW (orig_op2)));
    }

  /* Need to convert condition operand into a vector mask.  */
  ಯದಿ (VECTOR_TYPE_P (ವೃಕ್ಷ_TYPE (ifexp)))
    {
      ವೃಕ್ಷ vectype = ವೃಕ್ಷ_TYPE (ifexp);
      ವೃಕ್ಷ elem_type = ವೃಕ್ಷ_TYPE (vectype);
      ವೃಕ್ಷ zero = build_int_cst (elem_type, 0);
      ವೃಕ್ಷ zero_vec = build_vector_from_val (vectype, zero);
      ವೃಕ್ಷ cmp_type = truth_type_for (vectype);
      ifexp = build2 (NE_ಅಭಿವ್ಯಕ್ತಿ, cmp_type, ifexp, zero_vec);
    }

  ಯದಿ (int_const || (ifexp_bcp && ವೃಕ್ಷ_CODE (ifexp) == INTEGER_CST))
    ret = fold_build3_loc (colon_loc, COND_ಅಭಿವ್ಯಕ್ತಿ, result_type, ifexp, op1, op2);
  ಅನ್ಯಥಾ
    {
      ಯದಿ (int_operands)
	{
	  /* Use c_fully_fold here, since C_MAYBE_CONST_EXPR might be
	     nested inside of the expression.  */
	  op1 = c_fully_fold (op1, ಅಸತ್ಯ, ರಿಕ್ತ);
	  op2 = c_fully_fold (op2, ಅಸತ್ಯ, ರಿಕ್ತ);
	}
      ret = build3 (COND_ಅಭಿವ್ಯಕ್ತಿ, result_type, ifexp, op1, op2);
      ಯದಿ (int_operands)
	ret = note_integer_operands (ret);
    }
  ಯದಿ (semantic_result_type)
    ret = build1 (EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ, semantic_result_type, ret);

  protected_set_ಅಭಿವ್ಯಕ್ತಿ_location (ret, colon_loc);

  /* If the OP1 and OP2 are the same and don't have side-effects,
     warn here, because the COND_EXPR will be turned into OP1.  */
  ಯದಿ (warn_duplicated_branches
      && ವೃಕ್ಷ_CODE (ret) == COND_ಅಭಿವ್ಯಕ್ತಿ
      && (op1 == op2 || operand_equal_p (op1, op2, OEP_ADDRESS_OF_SAME_FIELD)))
    warning_at (ಅಭಿವ್ಯಕ್ತಿ_LOCATION (ret), OPT_Wduplicated_branches,
		"this condition has identical branches");

  ಪ್ರತ್ಯಾಗಮ ret;
}

/* EXPR is an expression, location LOC, whose result is discarded.
   Warn if it is a call to a nodiscard function (or a COMPOUND_EXPR
   whose right-hand operand is such a call, possibly recursively).  */

ಸ್ಥಿರ ಶೂನ್ಯ
maybe_warn_nodiscard (location_t loc, ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ)
{
  ಯದಿ (VOID_TYPE_P (ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ)))
    ಪ್ರತ್ಯಾಗಮ;
  ಯಾವತ್ (ವೃಕ್ಷ_CODE (ಅಭಿವ್ಯಕ್ತಿ) == COMPOUND_ಅಭಿವ್ಯಕ್ತಿ)
    {
      ಅಭಿವ್ಯಕ್ತಿ = ವೃಕ್ಷ_OPERAND (ಅಭಿವ್ಯಕ್ತಿ, 1);
      ಯದಿ (ಅಭಿವ್ಯಕ್ತಿ_HAS_LOCATION (ಅಭಿವ್ಯಕ್ತಿ))
	loc = ಅಭಿವ್ಯಕ್ತಿ_LOCATION (ಅಭಿವ್ಯಕ್ತಿ);
    }
  ಯದಿ (ವೃಕ್ಷ_CODE (ಅಭಿವ್ಯಕ್ತಿ) != CALL_ಅಭಿವ್ಯಕ್ತಿ)
    ಪ್ರತ್ಯಾಗಮ;
  ವೃಕ್ಷ fn = CALL_ಅಭಿವ್ಯಕ್ತಿ_FN (ಅಭಿವ್ಯಕ್ತಿ);
  ಯದಿ (!fn)
    ಪ್ರತ್ಯಾಗಮ;
  ವೃಕ್ಷ attr;
  ಯದಿ (ವೃಕ್ಷ_CODE (fn) == ADDR_ಅಭಿವ್ಯಕ್ತಿ
      && ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_OPERAND (fn, 0)) == FUNCTION_DECL
      && (attr = lookup_attribute ("nodiscard",
				   DECL_ATTRIBUTES (ವೃಕ್ಷ_OPERAND (fn, 0)))))
    {
      fn = ವೃಕ್ಷ_OPERAND (fn, 0);
      ವೃಕ್ಷ args = ವೃಕ್ಷ_ಮೌಲ್ಯ (attr);
      ಯದಿ (args)
	args = ವೃಕ್ಷ_ಮೌಲ್ಯ (args);
      auto_diagnostic_group d;
      auto_urlify_attributes sentinel;
      ಪೂರ್ಣಾಙ್ಕ warned;
      ಯದಿ (args)
	warned = warning_at (loc, OPT_Wunused_result,
			     "ignoring return value of %qD, declared with "
			     "attribute %<nodiscard%>: %E", fn, args);
      ಅನ್ಯಥಾ
	warned = warning_at (loc, OPT_Wunused_result,
			     "ignoring return value of %qD, declared with "
			     "attribute %<nodiscard%>", fn);
      ಯದಿ (warned)
	inform (DECL_SOURCE_LOCATION (fn), "declared here");
    }
  ಅನ್ಯಥಾ
    {
      ವೃಕ್ಷ rettype = ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (fn)));
      attr = lookup_attribute ("nodiscard", TYPE_ATTRIBUTES (rettype));
      ಯದಿ (!attr)
	ಪ್ರತ್ಯಾಗಮ;
      ವೃಕ್ಷ args = ವೃಕ್ಷ_ಮೌಲ್ಯ (attr);
      ಯದಿ (args)
	args = ವೃಕ್ಷ_ಮೌಲ್ಯ (args);
      auto_diagnostic_group d;
      auto_urlify_attributes sentinel;
      ಪೂರ್ಣಾಙ್ಕ warned;
      ಯದಿ (args)
	warned = warning_at (loc, OPT_Wunused_result,
			     "ignoring return value of type %qT, declared "
			     "with attribute %<nodiscard%>: %E",
			     rettype, args);
      ಅನ್ಯಥಾ
	warned = warning_at (loc, OPT_Wunused_result,
			     "ignoring return value of type %qT, declared "
			     "with attribute %<nodiscard%>", rettype);
      ಯದಿ (warned)
	{
	  ಯದಿ (ವೃಕ್ಷ_CODE (fn) == ADDR_ಅಭಿವ್ಯಕ್ತಿ)
	    {
	      fn = ವೃಕ್ಷ_OPERAND (fn, 0);
	      ಯದಿ (ವೃಕ್ಷ_CODE (fn) == FUNCTION_DECL)
		inform (DECL_SOURCE_LOCATION (fn),
			"in call to %qD, declared here", fn);
	    }
	}
    }
}

/* Return a compound expression that performs two expressions and
   returns the value of the second of them.

   LOC is the location of the COMPOUND_EXPR.  */

ವೃಕ್ಷ
build_compound_ಅಭಿವ್ಯಕ್ತಿ (location_t loc, ವೃಕ್ಷ expr1, ವೃಕ್ಷ expr2)
{
  ತಾರ್ಕಿಕ expr1_int_operands, expr2_int_operands;
  ವೃಕ್ಷ eptype = NULL_ವೃಕ್ಷ;
  ವೃಕ್ಷ ret;

  expr1_int_operands = ಅಭಿವ್ಯಕ್ತಿ_INT_CONST_OPERANDS (expr1);
  ಯದಿ (expr1_int_operands)
    expr1 = remove_c_maybe_const_ಅಭಿವ್ಯಕ್ತಿ (expr1);
  expr2_int_operands = ಅಭಿವ್ಯಕ್ತಿ_INT_CONST_OPERANDS (expr2);
  ಯದಿ (expr2_int_operands)
    expr2 = remove_c_maybe_const_ಅಭಿವ್ಯಕ್ತಿ (expr2);

  ಯದಿ (ವೃಕ್ಷ_CODE (expr1) == EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ)
    expr1 = ವೃಕ್ಷ_OPERAND (expr1, 0);
  ಯದಿ (ವೃಕ್ಷ_CODE (expr2) == EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ)
    {
      eptype = ವೃಕ್ಷ_TYPE (expr2);
      expr2 = ವೃಕ್ಷ_OPERAND (expr2, 0);
    }

  ಯದಿ (!ವೃಕ್ಷ_SIDE_EFFECTS (expr1))
    {
      /* The left-hand operand of a comma expression is like an expression
	 statement: with -Wunused, we should warn if it doesn't have
	 any side-effects, unless it was explicitly cast to (void).  */
      ಯದಿ (warn_unused_ಮೌಲ್ಯ)
	{
	  ಯದಿ (VOID_TYPE_P (ವೃಕ್ಷ_TYPE (expr1))
	      && CONVERT_ಅಭಿವ್ಯಕ್ತಿ_P (expr1))
	    ; /* (void) a, b */
	  ಅನ್ಯಥಾ ಯದಿ (VOID_TYPE_P (ವೃಕ್ಷ_TYPE (expr1))
		   && ವೃಕ್ಷ_CODE (expr1) == COMPOUND_ಅಭಿವ್ಯಕ್ತಿ
		   && CONVERT_ಅಭಿವ್ಯಕ್ತಿ_P (ವೃಕ್ಷ_OPERAND (expr1, 1)))
	    ; /* (void) a, (void) b, c */
	  ಅನ್ಯಥಾ
	    warning_at (loc, OPT_Wunused_ಮೌಲ್ಯ,
			"left-hand operand of comma expression has no effect");
	}
    }
  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (expr1) == COMPOUND_ಅಭಿವ್ಯಕ್ತಿ
	   && warn_unused_ಮೌಲ್ಯ)
    {
      ವೃಕ್ಷ r = expr1;
      location_t cloc = loc;
      ಯಾವತ್ (ವೃಕ್ಷ_CODE (r) == COMPOUND_ಅಭಿವ್ಯಕ್ತಿ)
        {
	  ಯದಿ (ಅಭಿವ್ಯಕ್ತಿ_HAS_LOCATION (r))
	    cloc = ಅಭಿವ್ಯಕ್ತಿ_LOCATION (r);
	  r = ವೃಕ್ಷ_OPERAND (r, 1);
	}
      ಯದಿ (!ವೃಕ್ಷ_SIDE_EFFECTS (r)
	  && !VOID_TYPE_P (ವೃಕ್ಷ_TYPE (r))
	  && !CONVERT_ಅಭಿವ್ಯಕ್ತಿ_P (r))
	warning_at (cloc, OPT_Wunused_ಮೌಲ್ಯ,
	            "right-hand operand of comma expression has no effect");
    }

  /* With -Wunused, we should also warn if the left-hand operand does have
     side-effects, but computes a value which is not used.  For example, in
     `foo() + bar(), baz()' the result of the `+' operator is not used,
     so we should issue a warning.  */
  ಅನ್ಯಥಾ ಯದಿ (warn_unused_ಮೌಲ್ಯ)
    warn_if_unused_ಮೌಲ್ಯ (expr1, loc);

  maybe_warn_nodiscard (loc, expr1);

  ಯದಿ (expr2 == error_mark_ಗಂಟು)
    ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;

  ret = build2 (COMPOUND_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (expr2), expr1, expr2);

  ಯದಿ (flag_isoc99
      && expr1_int_operands
      && expr2_int_operands)
    ret = note_integer_operands (ret);

  ಯದಿ (eptype)
    ret = build1 (EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ, eptype, ret);

  protected_set_ಅಭಿವ್ಯಕ್ತಿ_location (ret, loc);
  ಪ್ರತ್ಯಾಗಮ ret;
}

/* Issue -Wcast-qual warnings when appropriate.  TYPE is the type to
   which we are casting.  OTYPE is the type of the expression being
   cast.  Both TYPE and OTYPE are pointer types.  LOC is the location
   of the cast.  -Wcast-qual appeared on the command line.  Named
   address space qualifiers are not handled here, because they result
   in different warnings.  */

ಸ್ಥಿರ ಶೂನ್ಯ
handle_warn_cast_qual (location_t loc, ವೃಕ್ಷ type, ವೃಕ್ಷ otype)
{
  ವೃಕ್ಷ in_type = type;
  ವೃಕ್ಷ in_otype = otype;
  ಪೂರ್ಣಾಙ್ಕ added = 0;
  ಪೂರ್ಣಾಙ್ಕ discarded = 0;
  ತಾರ್ಕಿಕ is_const;

  /* Check that the qualifiers on IN_TYPE are a superset of the
     qualifiers of IN_OTYPE.  The outermost level of POINTER_TYPE
     nodes is uninteresting and we stop as soon as we hit a
     non-POINTER_TYPE node on either type.  */
  ಕುರು
    {
      in_otype = ವೃಕ್ಷ_TYPE (in_otype);
      in_type = ವೃಕ್ಷ_TYPE (in_type);

      /* GNU C allows cv-qualified function types.  'const' means the
	 function is very pure, 'volatile' means it can't return.  We
	 need to warn when such qualifiers are added, not when they're
	 taken away.  */
      ಯದಿ (ವೃಕ್ಷ_CODE (in_otype) == FUNCTION_TYPE
	  && ವೃಕ್ಷ_CODE (in_type) == FUNCTION_TYPE)
	added |= (TYPE_QUALS_NO_ADDR_SPACE (in_type)
		  & ~TYPE_QUALS_NO_ADDR_SPACE (in_otype));
      ಅನ್ಯಥಾ
	discarded |= (TYPE_QUALS_NO_ADDR_SPACE (in_otype)
		      & ~TYPE_QUALS_NO_ADDR_SPACE (in_type));
    }
  ಯಾವತ್ (ವೃಕ್ಷ_CODE (in_type) == POINTER_TYPE
	 && ವೃಕ್ಷ_CODE (in_otype) == POINTER_TYPE);

  ಯದಿ (added)
    warning_at (loc, OPT_Wcast_qual,
		"cast adds %q#v qualifier to function type", added);

  ಯದಿ (discarded)
    /* There are qualifiers present in IN_OTYPE that are not present
       in IN_TYPE.  */
    warning_at (loc, OPT_Wcast_qual,
		"cast discards %qv qualifier from pointer target type",
		discarded);

  ಯದಿ (added || discarded)
    ಪ್ರತ್ಯಾಗಮ;

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

  ಯದಿ (TYPE_MAIN_VARIANT (in_type) != TYPE_MAIN_VARIANT (in_otype))
    ಪ್ರತ್ಯಾಗಮ;
  ಯದಿ (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (type)) != POINTER_TYPE)
    ಪ್ರತ್ಯಾಗಮ;

  in_type = type;
  in_otype = otype;
  is_const = TYPE_READONLY (ವೃಕ್ಷ_TYPE (in_type));
  ಕುರು
    {
      in_type = ವೃಕ್ಷ_TYPE (in_type);
      in_otype = ವೃಕ್ಷ_TYPE (in_otype);
      ಯದಿ ((TYPE_QUALS (in_type) &~ TYPE_QUALS (in_otype)) != 0
	  && !is_const)
	{
	  warning_at (loc, OPT_Wcast_qual,
		      "to be safe all intermediate pointers in cast from "
                      "%qT to %qT must be %<const%> qualified",
		      otype, type);
	  ಭಙ್ಗ;
	}
      ಯದಿ (is_const)
	is_const = TYPE_READONLY (in_type);
    }
  ಯಾವತ್ (ವೃಕ್ಷ_CODE (in_type) == POINTER_TYPE);
}

/* Heuristic check if two parameter types can be considered ABI-equivalent.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
c_safe_arg_type_equiv_p (ವೃಕ್ಷ t1, ವೃಕ್ಷ t2)
{
  ಯದಿ (error_operand_p (t1) || error_operand_p (t2))
    ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;

  t1 = TYPE_MAIN_VARIANT (t1);
  t2 = TYPE_MAIN_VARIANT (t2);

  ಯದಿ (ವೃಕ್ಷ_CODE (t1) == POINTER_TYPE
      && ವೃಕ್ಷ_CODE (t2) == POINTER_TYPE)
    ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;

  /* Only the precision of the parameter matters.  This check should
     make sure that the callee does not see undefined values in argument
     registers.  */
  ಯದಿ (INTEGRAL_TYPE_P (t1)
      && INTEGRAL_TYPE_P (t2)
      && TYPE_PRECISION (t1) == TYPE_PRECISION (t2))
    ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;

  ಪ್ರತ್ಯಾಗಮ comptypes (t1, t2);
}

/* Check if a type cast between two function types can be considered safe.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
c_safe_function_type_cast_p (ವೃಕ್ಷ t1, ವೃಕ್ಷ t2)
{
  ಯದಿ (ವೃಕ್ಷ_TYPE (t1) == void_type_ಗಂಟು &&
      TYPE_ARG_TYPES (t1) == void_list_ಗಂಟು)
    ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;

  ಯದಿ (ವೃಕ್ಷ_TYPE (t2) == void_type_ಗಂಟು &&
      TYPE_ARG_TYPES (t2) == void_list_ಗಂಟು)
    ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;

  ಯದಿ (!c_safe_arg_type_equiv_p (ವೃಕ್ಷ_TYPE (t1), ವೃಕ್ಷ_TYPE (t2)))
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

  ಪ್ರತಿ (t1 = TYPE_ARG_TYPES (t1), t2 = TYPE_ARG_TYPES (t2);
       t1 && t2;
       t1 = ವೃಕ್ಷ_CHAIN (t1), t2 = ವೃಕ್ಷ_CHAIN (t2))
    ಯದಿ (!c_safe_arg_type_equiv_p (ವೃಕ್ಷ_ಮೌಲ್ಯ (t1), ವೃಕ್ಷ_ಮೌಲ್ಯ (t2)))
      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

  ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
}

/* Build an expression representing a cast to type TYPE of expression EXPR.
   LOC is the location of the cast-- typically the open paren of the cast.  */

ವೃಕ್ಷ
build_c_cast (location_t loc, ವೃಕ್ಷ type, ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ)
{
  ವೃಕ್ಷ ಮೌಲ್ಯ;

  ತಾರ್ಕಿಕ int_operands = ಅಭಿವ್ಯಕ್ತಿ_INT_CONST_OPERANDS (ಅಭಿವ್ಯಕ್ತಿ);

  ಯದಿ (ವೃಕ್ಷ_CODE (ಅಭಿವ್ಯಕ್ತಿ) == EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ)
    ಅಭಿವ್ಯಕ್ತಿ = ವೃಕ್ಷ_OPERAND (ಅಭಿವ್ಯಕ್ತಿ, 0);

  ಮೌಲ್ಯ = ಅಭಿವ್ಯಕ್ತಿ;
  ಯದಿ (int_operands)
    ಮೌಲ್ಯ = remove_c_maybe_const_ಅಭಿವ್ಯಕ್ತಿ (ಮೌಲ್ಯ);

  ಯದಿ (type == error_mark_ಗಂಟು || ಅಭಿವ್ಯಕ್ತಿ == error_mark_ಗಂಟು)
    ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;

  /* The ObjC front-end uses TYPE_MAIN_VARIANT to tie together types differing
     only in <protocol> qualifications.  But when constructing cast expressions,
     the protocols do matter and must be kept around.  */
  ಯದಿ (objc_is_object_ptr (type) && objc_is_object_ptr (ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ)))
    ಪ್ರತ್ಯಾಗಮ build1 (NOP_ಅಭಿವ್ಯಕ್ತಿ, type, ಅಭಿವ್ಯಕ್ತಿ);

  type = TYPE_MAIN_VARIANT (type);

  ಯದಿ (ವೃಕ್ಷ_CODE (type) == ARRAY_TYPE)
    {
      error_at (loc, "cast specifies array type");
      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
    }

  ಯದಿ (ವೃಕ್ಷ_CODE (type) == FUNCTION_TYPE)
    {
      error_at (loc, "cast specifies function type");
      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
    }

  ಯದಿ (!VOID_TYPE_P (type))
    {
      ಮೌಲ್ಯ = require_complete_type (loc, ಮೌಲ್ಯ);
      ಯದಿ (ಮೌಲ್ಯ == error_mark_ಗಂಟು)
	ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
    }

  ಯದಿ (type == TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ)))
    {
      ಯದಿ (RECORD_OR_UNION_TYPE_P (type)
	  && pedwarn (loc, OPT_Wpedantic,
		      "ISO C forbids casting nonscalar to the same type"))
	      ;
      ಅನ್ಯಥಾ ಯದಿ (warn_useless_cast && c_inhibit_evaluation_warnings == 0)
	warning_at (loc, OPT_Wuseless_cast,
		    "useless cast to type %qT", type);

      /* Convert to remove any qualifiers from VALUE's type.  */
      ಮೌಲ್ಯ = convert (type, ಮೌಲ್ಯ);
    }
  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (type) == UNION_TYPE)
    {
      ವೃಕ್ಷ field;

      ಪ್ರತಿ (field = TYPE_FIELDS (type); field; field = DECL_CHAIN (field))
	ಯದಿ (ವೃಕ್ಷ_TYPE (field) != error_mark_ಗಂಟು
	    && comptypes (TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (field)),
			  TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ))))
	  ಭಙ್ಗ;

      ಯದಿ (field)
	{
	  ವೃಕ್ಷ t;
	  ತಾರ್ಕಿಕ maybe_const = ಸತ್ಯ;

	  pedwarn (loc, OPT_Wpedantic, "ISO C forbids casts to union type");
	  t = c_fully_fold (ಮೌಲ್ಯ, ಅಸತ್ಯ, &maybe_const);
	  t = build_constructor_single (type, field, t);
	  ಯದಿ (!maybe_const)
	    t = c_wrap_maybe_const (t, ಸತ್ಯ);
	  t = digest_init (loc, field, type, t,
			   NULL_ವೃಕ್ಷ, ಅಸತ್ಯ, ಅಸತ್ಯ, ಅಸತ್ಯ, ಸತ್ಯ, ಅಸತ್ಯ, ಅಸತ್ಯ);
	  ವೃಕ್ಷ_CONSTANT (t) = ವೃಕ್ಷ_CONSTANT (ಮೌಲ್ಯ);
	  ಪ್ರತ್ಯಾಗಮ t;
	}
      error_at (loc, "cast to union type from type not present in union");
      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
    }
  ಅನ್ಯಥಾ
    {
      ವೃಕ್ಷ otype, ovalue;

      ಯದಿ (type == void_type_ಗಂಟು)
	{
	  ವೃಕ್ಷ t = build1 (CONVERT_ಅಭಿವ್ಯಕ್ತಿ, type, ಮೌಲ್ಯ);
	  SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (t, loc);
	  ಪ್ರತ್ಯಾಗಮ t;
	}

      otype = ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ);

      /* Optionally warn about potentially worrisome casts.  */
      ಯದಿ (warn_cast_qual
	  && ವೃಕ್ಷ_CODE (type) == POINTER_TYPE
	  && ವೃಕ್ಷ_CODE (otype) == POINTER_TYPE)
	handle_warn_cast_qual (loc, type, otype);

      /* Warn about conversions between pointers to disjoint
	 address spaces.  */
      ಯದಿ (ವೃಕ್ಷ_CODE (type) == POINTER_TYPE
	  && ವೃಕ್ಷ_CODE (otype) == POINTER_TYPE
	  && !null_pointer_constant_p (ಮೌಲ್ಯ))
	{
	  addr_space_t as_to = TYPE_ADDR_SPACE (ವೃಕ್ಷ_TYPE (type));
	  addr_space_t as_from = TYPE_ADDR_SPACE (ವೃಕ್ಷ_TYPE (otype));
	  addr_space_t as_common;

	  ಯದಿ (!addr_space_superset (as_to, as_from, &as_common))
	    {
	      ಯದಿ (ADDR_SPACE_GENERIC_P (as_from))
		warning_at (loc, 0, "cast to %qs address space pointer "
			    "from disjoint generic address space pointer",
			    c_addr_space_name (as_to));

	      ಅನ್ಯಥಾ ಯದಿ (ADDR_SPACE_GENERIC_P (as_to))
		warning_at (loc, 0, "cast to generic address space pointer "
			    "from disjoint %qs address space pointer",
			    c_addr_space_name (as_from));

	      ಅನ್ಯಥಾ
		warning_at (loc, 0, "cast to %qs address space pointer "
			    "from disjoint %qs address space pointer",
			    c_addr_space_name (as_to),
			    c_addr_space_name (as_from));
	    }

	  /* Warn of new allocations that are not big enough for the target
	     type.  */
	  ಯದಿ (warn_alloc_size && ವೃಕ್ಷ_CODE (ಮೌಲ್ಯ) == CALL_ಅಭಿವ್ಯಕ್ತಿ)
	    ಯದಿ (ವೃಕ್ಷ fndecl = get_callee_fndecl (ಮೌಲ್ಯ))
	      ಯದಿ (DECL_IS_MALLOC (fndecl))
		{
		  ವೃಕ್ಷ attrs = TYPE_ATTRIBUTES (ವೃಕ್ಷ_TYPE (fndecl));
		  ವೃಕ್ಷ alloc_size = lookup_attribute ("alloc_size", attrs);
		  ಯದಿ (alloc_size)
		    warn_for_alloc_size (loc, ವೃಕ್ಷ_TYPE (type), ಮೌಲ್ಯ,
					 alloc_size);
		}
	}

      /* Warn about possible alignment problems.  */
      ಯದಿ ((STRICT_ALIGNMENT || warn_cast_align == 2)
	  && ವೃಕ್ಷ_CODE (type) == POINTER_TYPE
	  && ವೃಕ್ಷ_CODE (otype) == POINTER_TYPE
	  && ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (otype)) != VOID_TYPE
	  && ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (otype)) != FUNCTION_TYPE
	  /* Don't warn about opaque types, where the actual alignment
	     restriction is unknown.  */
	  && !(RECORD_OR_UNION_TYPE_P (ವೃಕ್ಷ_TYPE (otype))
	       && TYPE_MODE (ವೃಕ್ಷ_TYPE (otype)) == VOIDmode)
	  && min_align_of_type (ವೃಕ್ಷ_TYPE (type))
	     > min_align_of_type (ವೃಕ್ಷ_TYPE (otype)))
	warning_at (loc, OPT_Wcast_align,
		    "cast increases required alignment of target type");

      ಯದಿ ((ವೃಕ್ಷ_CODE (type) == INTEGER_TYPE
	   || ವೃಕ್ಷ_CODE (type) == BITINT_TYPE)
	  && ವೃಕ್ಷ_CODE (otype) == POINTER_TYPE
	  && TYPE_PRECISION (type) != TYPE_PRECISION (otype))
      /* Unlike conversion of integers to pointers, where the
         warning is disabled for converting constants because
         of cases such as SIG_*, warn about converting constant
         pointers to integers. In some cases it may cause unwanted
         sign extension, and a warning is appropriate.  */
	warning_at (loc, OPT_Wpointer_to_int_cast,
		    "cast from pointer to integer of different size");

      ಯದಿ ((ವೃಕ್ಷ_CODE (ಮೌಲ್ಯ) == CALL_ಅಭಿವ್ಯಕ್ತಿ
	   && !is_access_with_size_p (ಮೌಲ್ಯ))
	  && ವೃಕ್ಷ_CODE (type) != ವೃಕ್ಷ_CODE (otype))
	warning_at (loc, OPT_Wbad_function_cast,
		    "cast from function call of type %qT "
		    "to non-matching type %qT", otype, type);

      ಯದಿ (ವೃಕ್ಷ_CODE (type) == POINTER_TYPE
	  && (ವೃಕ್ಷ_CODE (otype) == INTEGER_TYPE
	      || ವೃಕ್ಷ_CODE (otype) == BITINT_TYPE)
	  && TYPE_PRECISION (type) != TYPE_PRECISION (otype)
	  /* Don't warn about converting any constant.  */
	  && !ವೃಕ್ಷ_CONSTANT (ಮೌಲ್ಯ))
	warning_at (loc,
		    OPT_Wint_to_pointer_cast, "cast to pointer from integer "
		    "of different size");

      ಯದಿ (warn_strict_aliasing <= 2)
        strict_aliasing_warning (ಅಭಿವ್ಯಕ್ತಿ_LOCATION (ಮೌಲ್ಯ), type, ಅಭಿವ್ಯಕ್ತಿ);

      /* If pedantic, warn for conversions between function and object
	 pointer types, except for converting a null pointer constant
	 to function pointer type.  */
      ಯದಿ (pedantic
	  && ವೃಕ್ಷ_CODE (type) == POINTER_TYPE
	  && ವೃಕ್ಷ_CODE (otype) == POINTER_TYPE
	  && ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (otype)) == FUNCTION_TYPE
	  && ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (type)) != FUNCTION_TYPE)
	pedwarn (loc, OPT_Wpedantic, "ISO C forbids "
		 "conversion of function pointer to object pointer type");

      ಯದಿ (pedantic
	  && ವೃಕ್ಷ_CODE (type) == POINTER_TYPE
	  && ವೃಕ್ಷ_CODE (otype) == POINTER_TYPE
	  && ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (type)) == FUNCTION_TYPE
	  && ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (otype)) != FUNCTION_TYPE
	  && !null_pointer_constant_p (ಮೌಲ್ಯ))
	pedwarn (loc, OPT_Wpedantic, "ISO C forbids "
		 "conversion of object pointer to function pointer type");

      ಯದಿ (ವೃಕ್ಷ_CODE (type) == POINTER_TYPE
	  && ವೃಕ್ಷ_CODE (otype) == POINTER_TYPE
	  && ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (type)) == FUNCTION_TYPE
	  && ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (otype)) == FUNCTION_TYPE
	  && !c_safe_function_type_cast_p (ವೃಕ್ಷ_TYPE (type),
					   ವೃಕ್ಷ_TYPE (otype)))
	warning_at (loc, OPT_Wcast_function_type,
		    "cast between incompatible function types"
		    " from %qT to %qT", otype, type);

      ovalue = ಮೌಲ್ಯ;
      /* If converting to boolean a value with integer operands that
	 is not itself represented as an INTEGER_CST, the call below
	 to note_integer_operands may insert a C_MAYBE_CONST_EXPR, but
	 build_binary_op as called by c_common_truthvalue_conversion
	 may also insert a C_MAYBE_CONST_EXPR to indicate that a
	 subexpression has been fully folded.  To avoid nested
	 C_MAYBE_CONST_EXPR, ensure that
	 c_objc_common_truthvalue_conversion receives an argument
	 properly marked as having integer operands in that case.  */
      ಯದಿ (int_operands
	  && ವೃಕ್ಷ_CODE (ಮೌಲ್ಯ) != INTEGER_CST
	  && (ವೃಕ್ಷ_CODE (type) == BOOLEAN_TYPE
	      || (ವೃಕ್ಷ_CODE (type) == ENUMERAL_TYPE
		  && ENUM_UNDERLYING_TYPE (type) != NULL_ವೃಕ್ಷ
		  && ವೃಕ್ಷ_CODE (ENUM_UNDERLYING_TYPE (type)) == BOOLEAN_TYPE)))
	ಮೌಲ್ಯ = note_integer_operands (ಮೌಲ್ಯ);
      ಮೌಲ್ಯ = convert (type, ಮೌಲ್ಯ);

      /* Ignore any integer overflow caused by the cast.  */
      ಯದಿ (ವೃಕ್ಷ_CODE (ಮೌಲ್ಯ) == INTEGER_CST && !FLOAT_TYPE_P (otype))
	{
	  ಯದಿ (ವೃಕ್ಷ_OVERFLOW_P (ovalue))
	    {
	      ಯದಿ (!ವೃಕ್ಷ_OVERFLOW (ಮೌಲ್ಯ))
		{
		  /* Avoid clobbering a shared constant.  */
		  ಮೌಲ್ಯ = copy_ಗಂಟು (ಮೌಲ್ಯ);
		  ವೃಕ್ಷ_OVERFLOW (ಮೌಲ್ಯ) = ವೃಕ್ಷ_OVERFLOW (ovalue);
		}
	    }
	  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_OVERFLOW (ಮೌಲ್ಯ))
	    /* Reset VALUE's overflow flags, ensuring constant sharing.  */
	    ಮೌಲ್ಯ = wide_int_to_ವೃಕ್ಷ (ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ), wi::to_wide (ಮೌಲ್ಯ));
	}
    }

  /* Don't let a cast be an lvalue.  */
  ಯದಿ (lvalue_p (ಮೌಲ್ಯ)
      /* Also, don't let a cast be a bit-field of a bit-precise integer type,
	 otherwise it could be incorrectly subject of integer promotions.  */
      || (ವೃಕ್ಷ_CODE (ಮೌಲ್ಯ) == COMPONENT_REF
	  && DECL_C_BIT_FIELD (ವೃಕ್ಷ_OPERAND (ಮೌಲ್ಯ, 1))
	  && BITINT_TYPE_P (DECL_BIT_FIELD_TYPE (ವೃಕ್ಷ_OPERAND (ಮೌಲ್ಯ, 1)))))
    ಮೌಲ್ಯ = non_lvalue_loc (loc, ಮೌಲ್ಯ);

  /* Don't allow the results of casting to floating-point or complex
     types be confused with actual constants, or casts involving
     integer and pointer types other than direct integer-to-integer
     and integer-to-pointer be confused with integer constant
     expressions and null pointer constants.  */
  ಯದಿ (ವೃಕ್ಷ_CODE (ಮೌಲ್ಯ) == REAL_CST
      || ವೃಕ್ಷ_CODE (ಮೌಲ್ಯ) == COMPLEX_CST
      || (ವೃಕ್ಷ_CODE (ಮೌಲ್ಯ) == INTEGER_CST
	  && !((ವೃಕ್ಷ_CODE (ಅಭಿವ್ಯಕ್ತಿ) == INTEGER_CST
		&& INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ)))
	       || ವೃಕ್ಷ_CODE (ಅಭಿವ್ಯಕ್ತಿ) == REAL_CST
	       || ವೃಕ್ಷ_CODE (ಅಭಿವ್ಯಕ್ತಿ) == COMPLEX_CST)))
      ಮೌಲ್ಯ = build1 (NOP_ಅಭಿವ್ಯಕ್ತಿ, type, ಮೌಲ್ಯ);

  /* If the expression has integer operands and so can occur in an
     unevaluated part of an integer constant expression, ensure the
     return value reflects this.  */
  ಯದಿ (int_operands
      && INTEGRAL_TYPE_P (type)
      && ಮೌಲ್ಯ != error_mark_ಗಂಟು
      && !ಅಭಿವ್ಯಕ್ತಿ_INT_CONST_OPERANDS (ಮೌಲ್ಯ))
    ಮೌಲ್ಯ = note_integer_operands (ಮೌಲ್ಯ);

  protected_set_ಅಭಿವ್ಯಕ್ತಿ_location (ಮೌಲ್ಯ, loc);
  ಪ್ರತ್ಯಾಗಮ ಮೌಲ್ಯ;
}

/* Interpret a cast of expression EXPR to type TYPE.  LOC is the
   location of the open paren of the cast, or the position of the cast
   expr.  */
ವೃಕ್ಷ
c_cast_ಅಭಿವ್ಯಕ್ತಿ (location_t loc, ಸಂರಚನಾ c_type_name *type_name, ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ)
{
  ವೃಕ್ಷ type;
  ವೃಕ್ಷ type_ಅಭಿವ್ಯಕ್ತಿ = NULL_ವೃಕ್ಷ;
  ತಾರ್ಕಿಕ type_ಅಭಿವ್ಯಕ್ತಿ_const = ಸತ್ಯ;
  ವೃಕ್ಷ ret;
  ಪೂರ್ಣಾಙ್ಕ saved_wsp = warn_strict_prototypes;

  /* This avoids warnings about unprototyped casts on
     integers.  E.g. "#define SIG_DFL (void(*)())0".  */
  ಯದಿ (ವೃಕ್ಷ_CODE (ಅಭಿವ್ಯಕ್ತಿ) == INTEGER_CST)
    warn_strict_prototypes = 0;
  type = groktypename (type_name, &type_ಅಭಿವ್ಯಕ್ತಿ, &type_ಅಭಿವ್ಯಕ್ತಿ_const);
  warn_strict_prototypes = saved_wsp;

  ಯದಿ (ವೃಕ್ಷ_CODE (ಅಭಿವ್ಯಕ್ತಿ) == ADDR_ಅಭಿವ್ಯಕ್ತಿ && !VOID_TYPE_P (type)
      && reject_gcc_builtin (ಅಭಿವ್ಯಕ್ತಿ))
    ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;

  ret = build_c_cast (loc, type, ಅಭಿವ್ಯಕ್ತಿ);
  ಯದಿ (ret == error_mark_ಗಂಟು)
    ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;

  ಯದಿ (type_ಅಭಿವ್ಯಕ್ತಿ)
    {
      ತಾರ್ಕಿಕ inner_ಅಭಿವ್ಯಕ್ತಿ_const = ಸತ್ಯ;
      ret = c_fully_fold (ret, require_constant_ಮೌಲ್ಯ, &inner_ಅಭಿವ್ಯಕ್ತಿ_const);
      ret = build2 (C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (ret), type_ಅಭಿವ್ಯಕ್ತಿ, ret);
      C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_NON_CONST (ret) = !(type_ಅಭಿವ್ಯಕ್ತಿ_const
					     && inner_ಅಭಿವ್ಯಕ್ತಿ_const);
      SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (ret, loc);
    }

  ಯದಿ (!ಅಭಿವ್ಯಕ್ತಿ_HAS_LOCATION (ret))
    protected_set_ಅಭಿವ್ಯಕ್ತಿ_location (ret, loc);

  /* C++ does not permits types to be defined in a cast, but it
     allows references to incomplete types.  */
  ಯದಿ (warn_cxx_compat && type_name->specs->typespec_kind == ctsk_tagdef)
    warning_at (loc, OPT_Wc___compat,
		"defining a type in a cast is invalid in C++");

  ಪ್ರತ್ಯಾಗಮ ret;
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

ವೃಕ್ಷ
build_modify_ಅಭಿವ್ಯಕ್ತಿ (location_t location, ವೃಕ್ಷ lhs, ವೃಕ್ಷ lhs_origtype,
		   ಗಣನಾ ವೃಕ್ಷ_code modifycode,
		   location_t rhs_loc, ವೃಕ್ಷ rhs, ವೃಕ್ಷ rhs_origtype)
{
  ವೃಕ್ಷ result;
  ವೃಕ್ಷ newrhs;
  ವೃಕ್ಷ rhseval = NULL_ವೃಕ್ಷ;
  ವೃಕ್ಷ lhstype = ವೃಕ್ಷ_TYPE (lhs);
  ವೃಕ್ಷ olhstype = lhstype;
  ತಾರ್ಕಿಕ npc;
  ತಾರ್ಕಿಕ is_atomic_op;

  /* Types that aren't fully specified cannot be used in assignments.  */
  lhs = require_complete_type (location, lhs);
  rhs = require_complete_type (location, rhs);

  /* Avoid duplicate error messages from operands that had errors.  */
  ಯದಿ (ವೃಕ್ಷ_CODE (lhs) == ERROR_MARK || ವೃಕ್ಷ_CODE (rhs) == ERROR_MARK)
    ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;

  /* Ensure an error for assigning a non-lvalue array to an array in
     C90.  */
  ಯದಿ (ವೃಕ್ಷ_CODE (lhstype) == ARRAY_TYPE)
    {
      error_at (location, "assignment to expression with array type");
      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
    }

  /* For ObjC properties, defer this check.  */
  ಯದಿ (!objc_is_property_ref (lhs) && !lvalue_or_else (location, lhs, lv_assign))
    ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;

  is_atomic_op = really_atomic_lvalue (lhs);

  newrhs = rhs;

  ಯದಿ (ವೃಕ್ಷ_CODE (lhs) == C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ)
    {
      ವೃಕ್ಷ inner = build_modify_ಅಭಿವ್ಯಕ್ತಿ (location, C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_ಅಭಿವ್ಯಕ್ತಿ (lhs),
				      lhs_origtype, modifycode, rhs_loc, rhs,
				      rhs_origtype);
      ಯದಿ (inner == error_mark_ಗಂಟು)
	ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
      result = build2 (C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (inner),
		       C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_PRE (lhs), inner);
      gcc_assert (!C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_INT_OPERANDS (lhs));
      C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ_NON_CONST (result) = 1;
      protected_set_ಅಭಿವ್ಯಕ್ತಿ_location (result, location);
      ಪ್ರತ್ಯಾಗಮ result;
    }

  /* If a binary op has been requested, combine the old LHS value with the RHS
     producing the value we should actually store into the LHS.  */

  ಯದಿ (modifycode != NOP_ಅಭಿವ್ಯಕ್ತಿ)
    {
      lhs = c_fully_fold (lhs, ಅಸತ್ಯ, ರಿಕ್ತ, ಸತ್ಯ);
      lhs = stabilize_reference (lhs);

      /* Construct the RHS for any non-atomic compound assignment. */
      ಯದಿ (!is_atomic_op)
        {
	  /* If in LHS op= RHS the RHS has side-effects, ensure they
	     are preevaluated before the rest of the assignment expression's
	     side-effects, because RHS could contain e.g. function calls
	     that modify LHS.  */
	  ಯದಿ (ವೃಕ್ಷ_SIDE_EFFECTS (rhs))
	    {
	      ಯದಿ (ವೃಕ್ಷ_CODE (rhs) == EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ)
		newrhs = save_ಅಭಿವ್ಯಕ್ತಿ (ವೃಕ್ಷ_OPERAND (rhs, 0));
	      ಅನ್ಯಥಾ
		newrhs = save_ಅಭಿವ್ಯಕ್ತಿ (rhs);
	      rhseval = newrhs;
	      ಯದಿ (ವೃಕ್ಷ_CODE (rhs) == EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ)
		newrhs = build1 (EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (rhs),
				 newrhs);
	    }
	  ತಾರ್ಕಿಕ clear_decl_read = ಅಸತ್ಯ;
	  ಯದಿ ((VAR_P (lhs) || ವೃಕ್ಷ_CODE (lhs) == PARM_DECL)
	      && !DECL_READ_P (lhs)
	      && (VAR_P (lhs) ? warn_unused_but_set_variable
			      : warn_unused_but_set_parameter) > 2)
	    {
	      mark_exp_read (newrhs);
	      ಯದಿ (!DECL_READ_P (lhs))
		clear_decl_read = ಸತ್ಯ;
	    }

	  newrhs = build_ದ್ವಿಮಾನ_op (location, modifycode,
				    convert_lvalue_to_rvalue (location, lhs,
							      ಸತ್ಯ, ಸತ್ಯ),
				    newrhs, ಸತ್ಯ);
	  ಯದಿ (clear_decl_read)
	    DECL_READ_P (lhs) = 0;

	  /* The original type of the right hand side is no longer
	     meaningful.  */
	  rhs_origtype = NULL_ವೃಕ್ಷ;
	}
    }

  ಯದಿ (c_dialect_objc ())
    {
      /* Check if we are modifying an Objective-C property reference;
	 if so, we need to generate setter calls.  */
      ಯದಿ (ವೃಕ್ಷ_CODE (newrhs) == EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ)
	result = objc_maybe_build_modify_ಅಭಿವ್ಯಕ್ತಿ (lhs, ವೃಕ್ಷ_OPERAND (newrhs, 0));
      ಅನ್ಯಥಾ
	result = objc_maybe_build_modify_ಅಭಿವ್ಯಕ್ತಿ (lhs, newrhs);
      ಯದಿ (result)
	ಗಚ್ಛ return_result;

      /* Else, do the check that we postponed for Objective-C.  */
      ಯದಿ (!lvalue_or_else (location, lhs, lv_assign))
	ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
    }

  /* Give an error for storing in something that is 'const'.  */

  ಯದಿ (TYPE_READONLY (lhstype)
      || (RECORD_OR_UNION_TYPE_P (lhstype)
	  && C_TYPE_FIELDS_READONLY (lhstype)))
    {
      readonly_error (location, lhs, lv_assign);
      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
    }
  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_READONLY (lhs))
    readonly_warning (lhs, lv_assign);

  /* If storing into a structure or union member,
     it has probably been given type `int'.
     Compute the type that would go with
     the actual amount of storage the member occupies.  */

  ಯದಿ (ವೃಕ್ಷ_CODE (lhs) == COMPONENT_REF
      && (ವೃಕ್ಷ_CODE (lhstype) == INTEGER_TYPE
	  || ವೃಕ್ಷ_CODE (lhstype) == BOOLEAN_TYPE
	  || SCALAR_FLOAT_TYPE_P (lhstype)
	  || ವೃಕ್ಷ_CODE (lhstype) == ENUMERAL_TYPE))
    lhstype = ವೃಕ್ಷ_TYPE (get_unwidened (lhs, 0));

  /* If storing in a field that is in actuality a short or narrower than one,
     we must store in the field in its actual type.  */

  ಯದಿ (lhstype != ವೃಕ್ಷ_TYPE (lhs))
    {
      lhs = copy_ಗಂಟು (lhs);
      ವೃಕ್ಷ_TYPE (lhs) = lhstype;
    }

  /* Issue -Wc++-compat warnings about an assignment to an enum type
     when LHS does not have its original type.  This happens for,
     e.g., an enum bitfield in a struct.  */
  ಯದಿ (warn_cxx_compat
      && lhs_origtype != NULL_ವೃಕ್ಷ
      && lhs_origtype != lhstype
      && ವೃಕ್ಷ_CODE (lhs_origtype) == ENUMERAL_TYPE)
    {
      ವೃಕ್ಷ checktype = (rhs_origtype != NULL_ವೃಕ್ಷ
			? rhs_origtype
			: ವೃಕ್ಷ_TYPE (rhs));
      ಯದಿ (checktype != error_mark_ಗಂಟು
	  && (TYPE_MAIN_VARIANT (checktype) != TYPE_MAIN_VARIANT (lhs_origtype)
	      || (is_atomic_op && modifycode != NOP_ಅಭಿವ್ಯಕ್ತಿ)))
	warning_at (location, OPT_Wc___compat,
		    "enum conversion in assignment is invalid in C++");
    }

  /* Remove qualifiers.  */
  lhstype = c_build_qualified_type (lhstype, TYPE_UNQUALIFIED);
  olhstype = c_build_qualified_type (olhstype, TYPE_UNQUALIFIED);

  /* Convert new value to destination type.  Fold it first, then
     restore any excess precision information, for the sake of
     conversion warnings.  */

  ಯದಿ (!(is_atomic_op && modifycode != NOP_ಅಭಿವ್ಯಕ್ತಿ))
    {
      ವೃಕ್ಷ rhs_semantic_type = NULL_ವೃಕ್ಷ;
      ಯದಿ (!c_in_omp_for)
	{
	  ಯದಿ (ವೃಕ್ಷ_CODE (newrhs) == EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ)
	    {
	      rhs_semantic_type = ವೃಕ್ಷ_TYPE (newrhs);
	      newrhs = ವೃಕ್ಷ_OPERAND (newrhs, 0);
	    }
	  npc = null_pointer_constant_p (newrhs);
	  newrhs = c_fully_fold (newrhs, ಅಸತ್ಯ, ರಿಕ್ತ);
	  ಯದಿ (rhs_semantic_type)
	    newrhs = build1 (EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ, rhs_semantic_type, newrhs);
	}
      ಅನ್ಯಥಾ
	npc = null_pointer_constant_p (newrhs);
      newrhs = convert_for_assignment (location, rhs_loc, lhstype, newrhs,
				       rhs_origtype, ic_assign, npc,
				       NULL_ವೃಕ್ಷ, NULL_ವೃಕ್ಷ, 0);
      ಯದಿ (ವೃಕ್ಷ_CODE (newrhs) == ERROR_MARK)
	ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
    }

  /* Emit ObjC write barrier, if necessary.  */
  ಯದಿ (c_dialect_objc () && flag_objc_gc)
    {
      result = objc_generate_write_barrier (lhs, modifycode, newrhs);
      ಯದಿ (result)
	{
	  protected_set_ಅಭಿವ್ಯಕ್ತಿ_location (result, location);
	  ಗಚ್ಛ return_result;
	}
    }

  /* Scan operands.  */

  ಯದಿ (is_atomic_op)
    result = build_atomic_assign (location, lhs, modifycode, newrhs, ಅಸತ್ಯ);
  ಅನ್ಯಥಾ
    {
      result = build2 (MODIFY_ಅಭಿವ್ಯಕ್ತಿ, lhstype, lhs, newrhs);
      ವೃಕ್ಷ_SIDE_EFFECTS (result) = 1;
      protected_set_ಅಭಿವ್ಯಕ್ತಿ_location (result, location);
    }

  /* If we got the LHS in a different type for storing in,
     convert the result back to the nominal type of LHS
     so that the value we return always has the same type
     as the LHS argument.  */

  ಯದಿ (olhstype == ವೃಕ್ಷ_TYPE (result))
    ಗಚ್ಛ return_result;

  result = convert_for_assignment (location, rhs_loc, olhstype, result,
				   rhs_origtype, ic_assign, ಅಸತ್ಯ, NULL_ವೃಕ್ಷ,
				   NULL_ವೃಕ್ಷ, 0);
  protected_set_ಅಭಿವ್ಯಕ್ತಿ_location (result, location);

return_result:
  ಯದಿ (rhseval)
    result = build2 (COMPOUND_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (result), rhseval, result);
  ಪ್ರತ್ಯಾಗಮ result;
}

/* Return whether STRUCT_TYPE has an anonymous field with type TYPE.
   This is used to implement -fplan9-extensions.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
find_anonymous_field_with_type (ವೃಕ್ಷ struct_type, ವೃಕ್ಷ type)
{
  ವೃಕ್ಷ field;
  ತಾರ್ಕಿಕ found;

  gcc_assert (RECORD_OR_UNION_TYPE_P (struct_type));
  found = ಅಸತ್ಯ;
  ಪ್ರತಿ (field = TYPE_FIELDS (struct_type);
       field != NULL_ವೃಕ್ಷ;
       field = ವೃಕ್ಷ_CHAIN (field))
    {
      ವೃಕ್ಷ fieldtype = remove_qualifiers (ವೃಕ್ಷ_TYPE (field));
      ಯದಿ (DECL_NAME (field) == ರಿಕ್ತ
	  && comptypes (type, fieldtype))
	{
	  ಯದಿ (found)
	    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	  found = ಸತ್ಯ;
	}
      ಅನ್ಯಥಾ ಯದಿ (DECL_NAME (field) == ರಿಕ್ತ
	       && RECORD_OR_UNION_TYPE_P (ವೃಕ್ಷ_TYPE (field))
	       && find_anonymous_field_with_type (ವೃಕ್ಷ_TYPE (field), type))
	{
	  ಯದಿ (found)
	    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	  found = ಸತ್ಯ;
	}
    }
  ಪ್ರತ್ಯಾಗಮ found;
}

/* RHS is an expression whose type is pointer to struct.  If there is
   an anonymous field in RHS with type TYPE, then return a pointer to
   that field in RHS.  This is used with -fplan9-extensions.  This
   returns NULL if no conversion could be found.  */

ಸ್ಥಿರ ವೃಕ್ಷ
convert_to_anonymous_field (location_t location, ವೃಕ್ಷ type, ವೃಕ್ಷ rhs)
{
  ವೃಕ್ಷ rhs_struct_type, lhs_main_type;
  ವೃಕ್ಷ field, found_field;
  ತಾರ್ಕಿಕ found_sub_field;
  ವೃಕ್ಷ ret;

  gcc_assert (POINTER_TYPE_P (ವೃಕ್ಷ_TYPE (rhs)));
  rhs_struct_type = ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (rhs));
  gcc_assert (RECORD_OR_UNION_TYPE_P (rhs_struct_type));

  gcc_assert (POINTER_TYPE_P (type));
  lhs_main_type = remove_qualifiers (ವೃಕ್ಷ_TYPE (type));

  found_field = NULL_ವೃಕ್ಷ;
  found_sub_field = ಅಸತ್ಯ;
  ಪ್ರತಿ (field = TYPE_FIELDS (rhs_struct_type);
       field != NULL_ವೃಕ್ಷ;
       field = ವೃಕ್ಷ_CHAIN (field))
    {
      ಯದಿ (DECL_NAME (field) != NULL_ವೃಕ್ಷ
	  || !RECORD_OR_UNION_TYPE_P (ವೃಕ್ಷ_TYPE (field)))
	ಅನುವರ್ತ;
      ವೃಕ್ಷ fieldtype = remove_qualifiers (ವೃಕ್ಷ_TYPE (field));
      ಯದಿ (comptypes (lhs_main_type, fieldtype))
	{
	  ಯದಿ (found_field != NULL_ವೃಕ್ಷ)
	    ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
	  found_field = field;
	}
      ಅನ್ಯಥಾ ಯದಿ (find_anonymous_field_with_type (ವೃಕ್ಷ_TYPE (field),
					       lhs_main_type))
	{
	  ಯದಿ (found_field != NULL_ವೃಕ್ಷ)
	    ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
	  found_field = field;
	  found_sub_field = ಸತ್ಯ;
	}
    }

  ಯದಿ (found_field == NULL_ವೃಕ್ಷ)
    ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;

  ret = fold_build3_loc (location, COMPONENT_REF, ವೃಕ್ಷ_TYPE (found_field),
			 build_fold_indirect_ref (rhs), found_field,
			 NULL_ವೃಕ್ಷ);
  ret = build_fold_addr_ಅಭಿವ್ಯಕ್ತಿ_loc (location, ret);

  ಯದಿ (found_sub_field)
    {
      ret = convert_to_anonymous_field (location, type, ret);
      gcc_assert (ret != NULL_ವೃಕ್ಷ);
    }

  ಪ್ರತ್ಯಾಗಮ ret;
}

/* Issue an error message for a bad initializer component.
   GMSGID identifies the message.
   The component name is taken from the spelling stack.  */

ಸ್ಥಿರ ಶೂನ್ಯ ATTRIBUTE_GCC_DIAG (2,0)
error_init (location_t loc, ಧ್ರುವ ವರ್ಣ *gmsgid, ...)
{
  ವರ್ಣ *ofwhat;

  auto_diagnostic_group d;

  /* The gmsgid may be a format string with %< and %>. */
  va_list ap;
  va_start (ap, gmsgid);
  ತಾರ್ಕಿಕ warned = emit_diagnostic_valist (diagnostics::kind::error,
					loc, -1, gmsgid, &ap);
  va_end (ap);

  ofwhat = print_spelling ((ವರ್ಣ *) alloca (spelling_length () + 1));
  ಯದಿ (*ofwhat && warned)
    inform (loc, "(near initialization for %qs)", ofwhat);
}

/* Used to implement pedwarn_init and permerror_init.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ ATTRIBUTE_GCC_DIAG (3,0)
pedwarn_permerror_init (location_t loc, ಪೂರ್ಣಾಙ್ಕ opt, ಧ್ರುವ ವರ್ಣ *gmsgid,
			va_list *ap, ಗಣನಾ diagnostics::kind kind)
{
  /* Use the location where a macro was expanded rather than where
     it was defined to make sure macros defined in system headers
     but used incorrectly elsewhere are diagnosed.  */
  location_t exploc = expansion_point_location_if_in_system_header (loc);
  auto_diagnostic_group d;
  ತಾರ್ಕಿಕ warned = emit_diagnostic_valist (kind, exploc, opt, gmsgid, ap);
  ಯದಿ (warned)
    {
      ವರ್ಣ *ofwhat = print_spelling ((ವರ್ಣ *) alloca (spelling_length () + 1));
      ಯದಿ (*ofwhat)
	inform (exploc, "(near initialization for %qs)", ofwhat);
    }
  ಪ್ರತ್ಯಾಗಮ warned;
}

/* Issue a pedantic warning for a bad initializer component.  OPT is
   the option OPT_* (from options.h) controlling this warning or 0 if
   it is unconditionally given.  GMSGID identifies the message.  The
   component name is taken from the spelling stack.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ ATTRIBUTE_GCC_DIAG (3,0)
pedwarn_init (location_t loc, ಪೂರ್ಣಾಙ್ಕ opt, ಧ್ರುವ ವರ್ಣ *gmsgid, ...)
{
  va_list ap;
  va_start (ap, gmsgid);
  ತಾರ್ಕಿಕ warned = pedwarn_permerror_init (loc, opt, gmsgid, &ap,
					diagnostics::kind::pedwarn);
  va_end (ap);
  ಪ್ರತ್ಯಾಗಮ warned;
}

/* Like pedwarn_init, but issue a permerror.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ ATTRIBUTE_GCC_DIAG (3,0)
permerror_init (location_t loc, ಪೂರ್ಣಾಙ್ಕ opt, ಧ್ರುವ ವರ್ಣ *gmsgid, ...)
{
  va_list ap;
  va_start (ap, gmsgid);
  ತಾರ್ಕಿಕ warned = pedwarn_permerror_init (loc, opt, gmsgid, &ap,
					diagnostics::kind::permerror);
  va_end (ap);
  ಪ್ರತ್ಯಾಗಮ warned;
}

/* Issue a warning for a bad initializer component.

   OPT is the OPT_W* value corresponding to the warning option that
   controls this warning.  GMSGID identifies the message.  The
   component name is taken from the spelling stack.  */

ಸ್ಥಿರ ಶೂನ್ಯ
warning_init (location_t loc, ಪೂರ್ಣಾಙ್ಕ opt, ಧ್ರುವ ವರ್ಣ *gmsgid)
{
  ವರ್ಣ *ofwhat;
  ತಾರ್ಕಿಕ warned;

  auto_diagnostic_group d;

  /* Use the location where a macro was expanded rather than where
     it was defined to make sure macros defined in system headers
     but used incorrectly elsewhere are diagnosed.  */
  location_t exploc = expansion_point_location_if_in_system_header (loc);

  /* The gmsgid may be a format string with %< and %>. */
  warned = warning_at (exploc, opt, gmsgid);
  ಯದಿ (warned)
    {
      ofwhat = print_spelling ((ವರ್ಣ *) alloca (spelling_length () + 1));
      ಯದಿ (*ofwhat)
	inform (exploc, "(near initialization for %qs)", ofwhat);
    }
}

/* If TYPE is an array type and EXPR is a parenthesized string
   constant, warn if pedantic that EXPR is being used to initialize an
   object of type TYPE.  */

ಶೂನ್ಯ
maybe_warn_string_init (location_t loc, ವೃಕ್ಷ type, ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ)
{
  ಯದಿ (pedantic
      && ವೃಕ್ಷ_CODE (type) == ARRAY_TYPE
      && ವೃಕ್ಷ_CODE (ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ) == STRING_CST
      && ಅಭಿವ್ಯಕ್ತಿ.original_code != STRING_CST)
    pedwarn_init (loc, OPT_Wpedantic,
		  "array initialized from parenthesized string constant");
}

/* Attempt to locate the parameter with the given index within FNDECL,
   returning DECL_SOURCE_LOCATION (FNDECL) if it can't be found.  */

ಸ್ಥಿರ location_t
get_fndecl_argument_location (ವೃಕ್ಷ fndecl, ಪೂರ್ಣಾಙ್ಕ argnum)
{
  ಪೂರ್ಣಾಙ್ಕ i;
  ವೃಕ್ಷ param;

  /* Locate param by index within DECL_ARGUMENTS (fndecl).  */
  ಪ್ರತಿ (i = 0, param = DECL_ARGUMENTS (fndecl);
       i < argnum && param;
       i++, param = ವೃಕ್ಷ_CHAIN (param))
    ;

  /* If something went wrong (e.g. if we have a builtin and thus no arguments),
     return DECL_SOURCE_LOCATION (FNDECL).  */
  ಯದಿ (param == ರಿಕ್ತ)
    ಪ್ರತ್ಯಾಗಮ DECL_SOURCE_LOCATION (fndecl);

  ಪ್ರತ್ಯಾಗಮ DECL_SOURCE_LOCATION (param);
}

/* Issue a note about a mismatching argument for parameter PARMNUM
   to FUNDECL, for types EXPECTED_TYPE and ACTUAL_TYPE.
   Attempt to issue the note at the pertinent parameter of the decl;
   failing that issue it at the location of FUNDECL; failing that
   issue it at PLOC.
   Use highlight_colors::actual for the ACTUAL_TYPE
   and highlight_colors::expected for EXPECTED_TYPE and the
   parameter of FUNDECL*/

ಸ್ಥಿರ ಶೂನ್ಯ
inform_for_arg (ವೃಕ್ಷ fundecl, location_t ploc, ಪೂರ್ಣಾಙ್ಕ parmnum,
		ವೃಕ್ಷ expected_type, ವೃಕ್ಷ actual_type)
{
  location_t loc;
  ಯದಿ (fundecl && !DECL_IS_UNDECLARED_BUILTIN (fundecl))
    loc = get_fndecl_argument_location (fundecl, parmnum - 1);
  ಅನ್ಯಥಾ
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

ಸ್ಥಿರ ಶೂನ್ಯ
maybe_warn_builtin_no_proto_arg (location_t loc, ವೃಕ್ಷ fundecl, ಪೂರ್ಣಾಙ್ಕ parmnum,
				 ವೃಕ್ಷ parmtype, ವೃಕ್ಷ argtype)
{
  ವೃಕ್ಷ_code parmcode = ವೃಕ್ಷ_CODE (parmtype);
  ವೃಕ್ಷ_code argcode = ವೃಕ್ಷ_CODE (argtype);
  ವೃಕ್ಷ promoted = c_type_promotes_to (argtype);

  /* Avoid warning for enum arguments that promote to an integer type
     of the same size/mode.  */
  ಯದಿ (parmcode == INTEGER_TYPE
      && argcode == ENUMERAL_TYPE
      && TYPE_MODE (parmtype) == TYPE_MODE (argtype))
    ಪ್ರತ್ಯಾಗಮ;

  ಯದಿ ((parmcode == argcode
       || (parmcode == INTEGER_TYPE
	   && argcode == ENUMERAL_TYPE))
      && TYPE_MAIN_VARIANT (parmtype) == TYPE_MAIN_VARIANT (promoted))
    ಪ್ರತ್ಯಾಗಮ;

  /* This diagnoses even signed/unsigned mismatches.  Those might be
     safe in many cases but GCC may emit suboptimal code for them so
     warning on those cases drives efficiency improvements.  */
  ಯದಿ (warning_at (loc, OPT_Wbuiltin_declaration_mismatch,
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

ವರ್ಗ pp_element_quoted_decl : ಸಾರ್ವಜನಿಕ pp_element
{
ಸಾರ್ವಜನಿಕ:
  pp_element_quoted_decl (ವೃಕ್ಷ decl, ಧ್ರುವ ವರ್ಣ *highlight_color)
  : m_decl (decl),
    m_highlight_color (highlight_color)
  {
  }

  ಶೂನ್ಯ add_to_phase_2 (pp_markup::context &ctxt) override
  {
    ctxt.begin_quote ();
    ctxt.begin_highlight_color (m_highlight_color);

    print_decl (ctxt);

    ctxt.end_highlight_color ();
    ctxt.end_quote ();
  }

  ಶೂನ್ಯ print_decl (pp_markup::context &ctxt)
  {
    pretty_printer *ಧ್ರುವ pp = &ctxt.m_pp;
    pp->set_padding (pp_none);
    ಯದಿ (DECL_NAME (m_decl))
      pp_identifier (pp, lang_hooks.decl_printable_name (m_decl, 2));
    ಅನ್ಯಥಾ
      pp_string (pp, _("({anonymous})"));
  }

ಗುಪ್ತ:
  ವೃಕ್ಷ m_decl;
  ಧ್ರುವ ವರ್ಣ *m_highlight_color;
};

/* If TYPE is from a typedef, issue a note showing the location
   to the user.
   Use HIGHLIGHT_COLOR as the highlight color.  */

ಸ್ಥಿರ ಶೂನ್ಯ
maybe_inform_typedef_location (ವೃಕ್ಷ type, ಧ್ರುವ ವರ್ಣ *highlight_color)
{
  ಯದಿ (!typedef_variant_p (type))
    ಪ್ರತ್ಯಾಗಮ;

  ವೃಕ್ಷ typedef_decl = TYPE_NAME (type);
  gcc_assert (ವೃಕ್ಷ_CODE (typedef_decl) == TYPE_DECL);
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

ಸ್ಥಿರ ವೃಕ್ಷ
convert_for_assignment (location_t location, location_t ಅಭಿವ್ಯಕ್ತಿ_loc, ವೃಕ್ಷ type,
			ವೃಕ್ಷ rhs, ವೃಕ್ಷ origtype, ಗಣನಾ impl_conv errtype,
			ತಾರ್ಕಿಕ null_pointer_constant, ವೃಕ್ಷ fundecl,
			ವೃಕ್ಷ function, ಪೂರ್ಣಾಙ್ಕ parmnum, ಪೂರ್ಣಾಙ್ಕ warnopt /* = 0 */)
{
  ಗಣನಾ ವೃಕ್ಷ_code codel = ವೃಕ್ಷ_CODE (type);
  ವೃಕ್ಷ orig_rhs = rhs;
  ವೃಕ್ಷ rhstype;
  ಗಣನಾ ವೃಕ್ಷ_code coder;
  ವೃಕ್ಷ rname = NULL_ವೃಕ್ಷ;
  ತಾರ್ಕಿಕ objc_ok = ಅಸತ್ಯ;

  /* Use the expansion point location to handle cases such as user's
     function returning a wrong-type macro defined in a system header.  */
  location = expansion_point_location_if_in_system_header (location);

  ಯದಿ (errtype == ic_argpass)
    {
      ವೃಕ್ಷ selector;
      /* Change pointer to function to the function itself for
	 diagnostics.  */
      ಯದಿ (ವೃಕ್ಷ_CODE (function) == ADDR_ಅಭಿವ್ಯಕ್ತಿ
	  && ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_OPERAND (function, 0)) == FUNCTION_DECL)
	function = ವೃಕ್ಷ_OPERAND (function, 0);

      /* Handle an ObjC selector specially for diagnostics.  */
      selector = objc_message_selector ();
      rname = function;
      ಯದಿ (selector && parmnum > 2)
	{
	  rname = selector;
	  parmnum -= 2;
	}
    }

  /* This macro is used to emit diagnostics to ensure that all format
     strings are complete sentences, visible to gettext and checked at
     compile time.  */
#define PEDWARN_FOR_ASSIGNMENT(LOCATION, PLOC, OPT, AR, AS, IN, RE)	 \
  ಕುರು {                                                                   \
    ವಿಕಲ್ಪ (errtype)                                                     \
      {                                                                  \
      ಪಕ್ಷ ic_argpass:                                                   \
	{								\
	  auto_diagnostic_group d;						\
	  ಯದಿ (pedwarn (PLOC, OPT, AR, parmnum, rname))		\
	    inform_for_arg (fundecl, (PLOC), parmnum, type, rhstype); \
	}								\
        ಭಙ್ಗ;                                                           \
      ಪಕ್ಷ ic_assign:                                                    \
        pedwarn (LOCATION, OPT, AS);                                     \
        ಭಙ್ಗ;                                                           \
      ಪಕ್ಷ ic_init:                                                      \
      ಪಕ್ಷ ic_init_const:                                                \
        pedwarn_init (LOCATION, OPT, IN);                                \
        ಭಙ್ಗ;                                                           \
      ಪಕ್ಷ ic_return:                                                    \
        pedwarn (LOCATION, OPT, RE);					 \
        ಭಙ್ಗ;                                                           \
      ಸ್ವಭಾವ:                                                           \
        gcc_unreachable ();                                              \
      }                                                                  \
  } ಯಾವತ್ (0)

  /* This macro is used to emit diagnostics to ensure that all format
     strings are complete sentences, visible to gettext and checked at
     compile time.  It can be called with 'pedwarn' or 'warning_at'.  */
#define WARNING_FOR_QUALIFIERS(PEDWARN, LOCATION, PLOC, OPT, AR, AS, IN, RE, QUALS) \
  ಕುರು {                                                                   \
    ವಿಕಲ್ಪ (errtype)                                                     \
      {                                                                  \
      ಪಕ್ಷ ic_argpass:                                                   \
	{								 \
	  auto_diagnostic_group d;					 \
	  ಯದಿ (PEDWARN) {						 \
	    ಯದಿ (pedwarn (PLOC, OPT, AR, parmnum, rname, QUALS))          \
	      inform_for_arg (fundecl, (PLOC), parmnum, type, rhstype);  \
	  } ಅನ್ಯಥಾ {							 \
	    ಯದಿ (warning_at (PLOC, OPT, AR, parmnum, rname, QUALS))	 \
	      inform_for_arg (fundecl, (PLOC), parmnum, type, rhstype);  \
	  }								 \
	}								 \
        ಭಙ್ಗ;                                                           \
      ಪಕ್ಷ ic_assign:                                                    \
	ಯದಿ (PEDWARN)							 \
	  pedwarn (LOCATION, OPT, AS, QUALS);                            \
	ಅನ್ಯಥಾ								 \
	  warning_at (LOCATION, OPT, AS, QUALS);                         \
        ಭಙ್ಗ;                                                           \
      ಪಕ್ಷ ic_init:                                                      \
      ಪಕ್ಷ ic_init_const:                                                \
	ಯದಿ (PEDWARN)							 \
	  pedwarn (LOCATION, OPT, IN, QUALS);                            \
	ಅನ್ಯಥಾ								 \
	  warning_at (LOCATION, OPT, IN, QUALS);                         \
        ಭಙ್ಗ;                                                           \
      ಪಕ್ಷ ic_return:                                                    \
	ಯದಿ (PEDWARN)							 \
	  pedwarn (LOCATION, OPT, RE, QUALS);                            \
	ಅನ್ಯಥಾ								 \
	  warning_at (LOCATION, OPT, RE, QUALS);                         \
        ಭಙ್ಗ;                                                           \
      ಸ್ವಭಾವ:                                                           \
        gcc_unreachable ();                                              \
      }                                                                  \
  } ಯಾವತ್ (0)

  /* This macro is used to emit diagnostics to ensure that all format
     strings are complete sentences, visible to gettext and checked at
     compile time.  It is the same as PEDWARN_FOR_ASSIGNMENT but with an
     extra parameter to enumerate qualifiers.  */
#define PEDWARN_FOR_QUALIFIERS(LOCATION, PLOC, OPT, AR, AS, IN, RE, QUALS) \
   WARNING_FOR_QUALIFIERS (ಸತ್ಯ, LOCATION, PLOC, OPT, AR, AS, IN, RE, QUALS)


  ಯದಿ (ವೃಕ್ಷ_CODE (rhs) == EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ)
    rhs = ವೃಕ್ಷ_OPERAND (rhs, 0);

  rhstype = ವೃಕ್ಷ_TYPE (rhs);
  coder = ವೃಕ್ಷ_CODE (rhstype);

  ಯದಿ (coder == ERROR_MARK)
    ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;

  ಯದಿ (c_dialect_objc ())
    {
      ಪೂರ್ಣಾಙ್ಕ parmno;

      ವಿಕಲ್ಪ (errtype)
	{
	ಪಕ್ಷ ic_return:
	  parmno = 0;
	  ಭಙ್ಗ;

	ಪಕ್ಷ ic_assign:
	  parmno = -1;
	  ಭಙ್ಗ;

	ಪಕ್ಷ ic_init:
	ಪಕ್ಷ ic_init_const:
	  parmno = -2;
	  ಭಙ್ಗ;

	ಸ್ವಭಾವ:
	  parmno = parmnum;
	  ಭಙ್ಗ;
	}

      objc_ok = objc_compare_types (type, rhstype, parmno, rname);
    }

  ಯದಿ (warn_cxx_compat)
    {
      ವೃಕ್ಷ checktype = origtype != NULL_ವೃಕ್ಷ ? origtype : rhstype;
      ಯದಿ (checktype != error_mark_ಗಂಟು
	  && ವೃಕ್ಷ_CODE (type) == ENUMERAL_TYPE
	  && TYPE_MAIN_VARIANT (checktype) != TYPE_MAIN_VARIANT (type))
	ವಿಕಲ್ಪ (errtype)
	  {
	  ಪಕ್ಷ ic_argpass:
	    ಯದಿ (pedwarn (ಅಭಿವ್ಯಕ್ತಿ_loc, OPT_Wc___compat, "enum conversion when "
			 "passing argument %d of %qE is invalid in C++",
			 parmnum, rname))
	      inform ((fundecl && !DECL_IS_UNDECLARED_BUILTIN (fundecl))
		      ? DECL_SOURCE_LOCATION (fundecl) : ಅಭಿವ್ಯಕ್ತಿ_loc,
		      "expected %qT but argument is of type %qT",
		      type, rhstype);
	    ಭಙ್ಗ;
	  ಪಕ್ಷ ic_assign:
	    pedwarn (location, OPT_Wc___compat, "enum conversion from %qT to "
		     "%qT in assignment is invalid in C++", rhstype, type);
	    ಭಙ್ಗ;
	  ಪಕ್ಷ ic_init:
	  ಪಕ್ಷ ic_init_const:
	    pedwarn_init (location, OPT_Wc___compat, "enum conversion from "
			  "%qT to %qT in initialization is invalid in C++",
			  rhstype, type);
	    ಭಙ್ಗ;
	  ಪಕ್ಷ ic_return:
	    pedwarn (location, OPT_Wc___compat, "enum conversion from %qT to "
		     "%qT in return is invalid in C++", rhstype, type);
	    ಭಙ್ಗ;
	  ಸ್ವಭಾವ:
	    gcc_unreachable ();
	  }
    }

  ಯದಿ (warn_enum_conversion)
    {
      ವೃಕ್ಷ checktype = origtype != NULL_ವೃಕ್ಷ ? origtype : rhstype;
      ಯದಿ (checktype != error_mark_ಗಂಟು
	  && ವೃಕ್ಷ_CODE (checktype) == ENUMERAL_TYPE
	  && ವೃಕ್ಷ_CODE (type) == ENUMERAL_TYPE
	  && !comptypes (TYPE_MAIN_VARIANT (checktype), TYPE_MAIN_VARIANT (type)))
       {
	  gcc_rich_location loc (location);
	  warning_at (&loc, OPT_Wenum_conversion,
		      "implicit conversion from %qT to %qT",
		      checktype, type);
       }
    }

  ಯದಿ (TYPE_MAIN_VARIANT (type) == TYPE_MAIN_VARIANT (rhstype))
    {
      warn_for_address_of_packed_member (type, orig_rhs);
      ಯದಿ (type != rhstype)
	/* Convert RHS to TYPE in order to not lose TYPE in diagnostics.  */
	rhs = convert (type, rhs);
      ಪ್ರತ್ಯಾಗಮ rhs;
    }

  ಯದಿ (coder == VOID_TYPE)
    {
      /* Except for passing an argument to an unprototyped function,
	 this is a constraint violation.  When passing an argument to
	 an unprototyped function, it is compile-time undefined;
	 making it a constraint in that case was rejected in
	 DR#252.  */
      ಧ್ರುವ ವರ್ಣ ಸಂದೇಶ[] = "void value not ignored as it ought to be";
      ಯದಿ (warnopt)
	warning_at (location, warnopt, ಸಂದೇಶ);
      ಅನ್ಯಥಾ
	error_at (location, ಸಂದೇಶ);
      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
    }
  rhs = require_complete_type (location, rhs);
  ಯದಿ (rhs == error_mark_ಗಂಟು)
    ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;

  ಯದಿ (coder == POINTER_TYPE && reject_gcc_builtin (rhs))
    ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;

  /* A non-reference type can convert to a reference.  This handles
     va_start, va_copy and possibly port built-ins.  */
  ಯದಿ (codel == REFERENCE_TYPE && coder != REFERENCE_TYPE)
    {
      ಯದಿ (!lvalue_p (rhs))
	{
	  ಧ್ರುವ ವರ್ಣ ಸಂದೇಶ[] = "cannot pass rvalue to reference parameter";
	  ಯದಿ (warnopt)
	    warning_at (location, warnopt, ಸಂದೇಶ);
	  ಅನ್ಯಥಾ
	    error_at (location, ಸಂದೇಶ);
	  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	}
      ಯದಿ (!c_mark_addressable (rhs))
	ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
      rhs = build1 (ADDR_ಅಭಿವ್ಯಕ್ತಿ, c_build_pointer_type (ವೃಕ್ಷ_TYPE (rhs)), rhs);
      SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (rhs, location);

      rhs = convert_for_assignment (location, ಅಭಿವ್ಯಕ್ತಿ_loc,
				    c_build_pointer_type (ವೃಕ್ಷ_TYPE (type)),
				    rhs, origtype, errtype,
				    null_pointer_constant, fundecl, function,
				    parmnum, warnopt);
      ಯದಿ (rhs == error_mark_ಗಂಟು)
	ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;

      rhs = build1 (NOP_ಅಭಿವ್ಯಕ್ತಿ, type, rhs);
      SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (rhs, location);
      ಪ್ರತ್ಯಾಗಮ rhs;
    }
  /* Some types can interconvert without explicit casts.  */
  ಅನ್ಯಥಾ ಯದಿ (codel == VECTOR_TYPE && coder == VECTOR_TYPE
	   && vector_types_convertible_p (type, ವೃಕ್ಷ_TYPE (rhs), ಸತ್ಯ))
    ಪ್ರತ್ಯಾಗಮ convert (type, rhs);
  /* Arithmetic types all interconvert, and enum is treated like int.  */
  ಅನ್ಯಥಾ ಯದಿ ((codel == INTEGER_TYPE || codel == REAL_TYPE
	    || codel == FIXED_POINT_TYPE
	    || codel == ENUMERAL_TYPE || codel == COMPLEX_TYPE
	    || codel == BOOLEAN_TYPE || codel == BITINT_TYPE)
	   && (coder == INTEGER_TYPE || coder == REAL_TYPE
	       || coder == FIXED_POINT_TYPE
	       || coder == ENUMERAL_TYPE || coder == COMPLEX_TYPE
	       || coder == BOOLEAN_TYPE || coder == BITINT_TYPE))
    {
      ಯದಿ (warnopt && errtype == ic_argpass)
	maybe_warn_builtin_no_proto_arg (ಅಭಿವ್ಯಕ್ತಿ_loc, fundecl, parmnum, type,
					 rhstype);

      ತಾರ್ಕಿಕ save = in_late_ದ್ವಿಮಾನ_op;
      ಯದಿ (C_BOOLEAN_TYPE_P (type) || codel == COMPLEX_TYPE
	  || (coder == REAL_TYPE
	      && (codel == INTEGER_TYPE || codel == ENUMERAL_TYPE)
	      && sanitize_flags_p (SANITIZE_FLOAT_CAST)))
	in_late_ದ್ವಿಮಾನ_op = ಸತ್ಯ;
      ವೃಕ್ಷ ret = convert_and_check (ಅಭಿವ್ಯಕ್ತಿ_loc != UNKNOWN_LOCATION
				    ? ಅಭಿವ್ಯಕ್ತಿ_loc : location, type, orig_rhs,
				    errtype == ic_init_const);
      in_late_ದ್ವಿಮಾನ_op = save;
      ಪ್ರತ್ಯಾಗಮ ret;
    }

  /* Aggregates in different TUs might need conversion.  */
  ಯದಿ ((codel == RECORD_TYPE || codel == UNION_TYPE)
      && codel == coder
      && comptypes (TYPE_MAIN_VARIANT (type), TYPE_MAIN_VARIANT (rhstype)))
    ಪ್ರತ್ಯಾಗಮ convert_and_check (ಅಭಿವ್ಯಕ್ತಿ_loc != UNKNOWN_LOCATION
			      ? ಅಭಿವ್ಯಕ್ತಿ_loc : location, type, rhs);

  /* Conversion to a transparent union or record from its member types.
     This applies only to function arguments.  */
  ಯದಿ (((codel == UNION_TYPE || codel == RECORD_TYPE)
      && TYPE_TRANSPARENT_AGGR (type))
      && errtype == ic_argpass)
    {
      ವೃಕ್ಷ memb, marginal_memb = NULL_ವೃಕ್ಷ;

      ಪ್ರತಿ (memb = TYPE_FIELDS (type); memb ; memb = DECL_CHAIN (memb))
	{
	  ವೃಕ್ಷ memb_type = ವೃಕ್ಷ_TYPE (memb);

	  ಯದಿ (comptypes (TYPE_MAIN_VARIANT (memb_type),
			 TYPE_MAIN_VARIANT (rhstype)))
	    ಭಙ್ಗ;

	  ಯದಿ (ವೃಕ್ಷ_CODE (memb_type) != POINTER_TYPE)
	    ಅನುವರ್ತ;

	  ಯದಿ (coder == POINTER_TYPE)
	    {
	      ವೃಕ್ಷ ttl = ವೃಕ್ಷ_TYPE (memb_type);
	      ವೃಕ್ಷ ttr = ವೃಕ್ಷ_TYPE (rhstype);

	      /* Any non-function converts to a [const][volatile] void *
		 and vice versa; otherwise, targets must be the same.
		 Meanwhile, the lhs target must have all the qualifiers of
		 the rhs.  */
	      ಯದಿ ((VOID_TYPE_P (ttl) && !TYPE_ATOMIC (ttl))
		  || (VOID_TYPE_P (ttr) && !TYPE_ATOMIC (ttr))
		  || comp_target_types (location, memb_type, rhstype))
		{
		  ಪೂರ್ಣಾಙ್ಕ lquals = TYPE_QUALS (ttl) & ~TYPE_QUAL_ATOMIC;
		  ಪೂರ್ಣಾಙ್ಕ rquals = TYPE_QUALS (ttr) & ~TYPE_QUAL_ATOMIC;
		  /* If this type won't generate any warnings, use it.  */
		  ಯದಿ (lquals == rquals
		      || ((ವೃಕ್ಷ_CODE (ttr) == FUNCTION_TYPE
			   && ವೃಕ್ಷ_CODE (ttl) == FUNCTION_TYPE)
			  ? ((lquals | rquals) == rquals)
			  : ((lquals | rquals) == lquals)))
		    ಭಙ್ಗ;

		  /* Keep looking for a better type, but remember this one.  */
		  ಯದಿ (!marginal_memb)
		    marginal_memb = memb;
		}
	    }

	  /* Can convert integer zero to any pointer type.  */
	  ಯದಿ (null_pointer_constant)
	    {
	      rhs = null_pointer_ಗಂಟು;
	      ಭಙ್ಗ;
	    }
	}

      ಯದಿ (memb || marginal_memb)
	{
	  ಯದಿ (!memb)
	    {
	      /* We have only a marginally acceptable member type;
		 it needs a warning.  */
	      ವೃಕ್ಷ ttl = ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (marginal_memb));
	      ವೃಕ್ಷ ttr = ವೃಕ್ಷ_TYPE (rhstype);

	      /* Const and volatile mean something different for function
		 types, so the usual warnings are not appropriate.  */
	      ಯದಿ (ವೃಕ್ಷ_CODE (ttr) == FUNCTION_TYPE
		  && ವೃಕ್ಷ_CODE (ttl) == FUNCTION_TYPE)
		{
		  /* Because const and volatile on functions are
		     restrictions that say the function will not do
		     certain things, it is okay to use a const or volatile
		     function where an ordinary one is wanted, but not
		     vice-versa.  */
		  ಯದಿ (TYPE_QUALS_NO_ADDR_SPACE (ttl)
		      & ~TYPE_QUALS_NO_ADDR_SPACE (ttr))
		    PEDWARN_FOR_QUALIFIERS (location, ಅಭಿವ್ಯಕ್ತಿ_loc,
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
	      ಅನ್ಯಥಾ ಯದಿ (TYPE_QUALS_NO_ADDR_SPACE (ttr)
		       & ~TYPE_QUALS_NO_ADDR_SPACE (ttl))
		PEDWARN_FOR_QUALIFIERS (location, ಅಭಿವ್ಯಕ್ತಿ_loc,
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

	  ಯದಿ (!fundecl || !DECL_IN_SYSTEM_HEADER (fundecl))
	    pedwarn (location, OPT_Wpedantic,
		     "ISO C prohibits argument conversion to union type");

	  rhs = fold_convert_loc (location, ವೃಕ್ಷ_TYPE (memb), rhs);
	  ಪ್ರತ್ಯಾಗಮ build_constructor_single (type, memb, rhs);
	}
    }

  /* Conversions among pointers */
  ಅನ್ಯಥಾ ಯದಿ ((codel == POINTER_TYPE || codel == REFERENCE_TYPE)
	   && (coder == codel))
    {
      /* If RHS refers to a built-in declared without a prototype
	 BLTIN is the declaration of the built-in with a prototype
	 and RHSTYPE is set to the actual type of the built-in.  */
      ವೃಕ್ಷ bltin;
      rhstype = type_or_builtin_type (rhs, &bltin);

      ವೃಕ್ಷ ttl = ವೃಕ್ಷ_TYPE (type);
      ವೃಕ್ಷ ttr = ವೃಕ್ಷ_TYPE (rhstype);
      ತಾರ್ಕಿಕ is_opaque_pointer;
      ತಾರ್ಕಿಕ target_cmp = ಅಸತ್ಯ;   /* Cache comp_target_types () result.  */
      addr_space_t asl;
      addr_space_t asr;

      ವೃಕ್ಷ mvl = remove_qualifiers (ttl);
      ವೃಕ್ಷ mvr = remove_qualifiers (ttr);

      /* Opaque pointers are treated like void pointers.  */
      is_opaque_pointer = vector_targets_convertible_p (ttl, ttr);

      /* The Plan 9 compiler permits a pointer to a struct to be
	 automatically converted into a pointer to an anonymous field
	 within the struct.  */
      ಯದಿ (flag_plan9_extensions
	  && RECORD_OR_UNION_TYPE_P (mvl)
	  && RECORD_OR_UNION_TYPE_P (mvr)
	  && mvl != mvr)
	{
	  ವೃಕ್ಷ new_rhs = convert_to_anonymous_field (location, type, rhs);
	  ಯದಿ (new_rhs != NULL_ವೃಕ್ಷ)
	    {
	      rhs = new_rhs;
	      rhstype = ವೃಕ್ಷ_TYPE (rhs);
	      coder = ವೃಕ್ಷ_CODE (rhstype);
	      ttr = ವೃಕ್ಷ_TYPE (rhstype);
	      mvr = TYPE_MAIN_VARIANT (ttr);
	    }
	}

      /* C++ does not allow the implicit conversion void* -> T*.  However,
	 for the purpose of reducing the number of false positives, we
	 tolerate the special case of

		int *p = NULL;

	 where NULL is typically defined in C to be '(void *) 0'.  */
      ಯದಿ (VOID_TYPE_P (ttr) && rhs != null_pointer_ಗಂಟು && !VOID_TYPE_P (ttl))
	warning_at (errtype == ic_argpass ? ಅಭಿವ್ಯಕ್ತಿ_loc : location,
		    OPT_Wc___compat,
		    "request for implicit conversion "
		    "from %qT to %qT not permitted in C++", rhstype, type);

      /* Warn of new allocations that are not big enough for the target
	 type.  */
      ಯದಿ (warn_alloc_size && ವೃಕ್ಷ_CODE (rhs) == CALL_ಅಭಿವ್ಯಕ್ತಿ)
	ಯದಿ (ವೃಕ್ಷ fndecl = get_callee_fndecl (rhs))
	  ಯದಿ (DECL_IS_MALLOC (fndecl))
	    {
	      ವೃಕ್ಷ attrs = TYPE_ATTRIBUTES (ವೃಕ್ಷ_TYPE (fndecl));
	      ವೃಕ್ಷ alloc_size = lookup_attribute ("alloc_size", attrs);
	      ಯದಿ (alloc_size)
		warn_for_alloc_size (location, ttl, rhs, alloc_size);
	    }

      /* See if the pointers point to incompatible address spaces.  */
      asl = TYPE_ADDR_SPACE (ttl);
      asr = TYPE_ADDR_SPACE (ttr);
      ಯದಿ (!null_pointer_constant_p (rhs)
	  && asr != asl && !targetm.addr_space.subset_p (asr, asl))
	{
	  auto_diagnostic_group d;
	  ತಾರ್ಕಿಕ diagnosed = ಸತ್ಯ;
	  ವಿಕಲ್ಪ (errtype)
	    {
	    ಪಕ್ಷ ic_argpass:
	      {
		ಧ್ರುವ ವರ್ಣ ಸಂದೇಶ[] = G_("passing argument %d of %qE from "
				      "pointer to non-enclosed address space");
		ಯದಿ (warnopt)
		  diagnosed
		    = warning_at (ಅಭಿವ್ಯಕ್ತಿ_loc, warnopt, ಸಂದೇಶ, parmnum, rname);
		ಅನ್ಯಥಾ
		  error_at (ಅಭಿವ್ಯಕ್ತಿ_loc, ಸಂದೇಶ, parmnum, rname);
	      ಭಙ್ಗ;
	      }
	    ಪಕ್ಷ ic_assign:
	      {
		ಧ್ರುವ ವರ್ಣ ಸಂದೇಶ[] = G_("assignment from pointer to "
				      "non-enclosed address space");
		ಯದಿ (warnopt)
		  diagnosed = warning_at (location, warnopt, ಸಂದೇಶ);
		ಅನ್ಯಥಾ
		  error_at (location, ಸಂದೇಶ);
		ಭಙ್ಗ;
	      }
	    ಪಕ್ಷ ic_init:
	    ಪಕ್ಷ ic_init_const:
	      {
		ಧ್ರುವ ವರ್ಣ ಸಂದೇಶ[] = G_("initialization from pointer to "
				      "non-enclosed address space");
		ಯದಿ (warnopt)
		  diagnosed = warning_at (location, warnopt, ಸಂದೇಶ);
		ಅನ್ಯಥಾ
		  error_at (location, ಸಂದೇಶ);
		ಭಙ್ಗ;
	      }
	    ಪಕ್ಷ ic_return:
	      {
		ಧ್ರುವ ವರ್ಣ ಸಂದೇಶ[] = G_("return from pointer to "
				      "non-enclosed address space");
		ಯದಿ (warnopt)
		  diagnosed = warning_at (location, warnopt, ಸಂದೇಶ);
		ಅನ್ಯಥಾ
		  error_at (location, ಸಂದೇಶ);
		ಭಙ್ಗ;
	      }
	    ಸ್ವಭಾವ:
	      gcc_unreachable ();
	    }
	  ಯದಿ (diagnosed)
	    {
	      ಯದಿ (errtype == ic_argpass)
		inform_for_arg (fundecl, ಅಭಿವ್ಯಕ್ತಿ_loc, parmnum, type, rhstype);
	      ಅನ್ಯಥಾ
		inform (location, "expected %qT but pointer is of type %qT",
			type, rhstype);
	    }
	  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	}

      /* Check if the right-hand side has a format attribute but the
	 left-hand side doesn't.  */
      ಯದಿ (warn_suggest_attribute_format
	  && check_missing_format_attribute (type, rhstype))
	{
	  ವಿಕಲ್ಪ (errtype)
	  {
	  ಪಕ್ಷ ic_argpass:
	    warning_at (ಅಭಿವ್ಯಕ್ತಿ_loc, OPT_Wsuggest_attribute_format,
			"argument %d of %qE might be "
			"a candidate for a format attribute",
			parmnum, rname);
	    ಭಙ್ಗ;
	  ಪಕ್ಷ ic_assign:
	    warning_at (location, OPT_Wsuggest_attribute_format,
			"assignment left-hand side might be "
			"a candidate for a format attribute");
	    ಭಙ್ಗ;
	  ಪಕ್ಷ ic_init:
	  ಪಕ್ಷ ic_init_const:
	    warning_at (location, OPT_Wsuggest_attribute_format,
			"initialization left-hand side might be "
			"a candidate for a format attribute");
	    ಭಙ್ಗ;
	  ಪಕ್ಷ ic_return:
	    warning_at (location, OPT_Wsuggest_attribute_format,
			"return type might be "
			"a candidate for a format attribute");
	    ಭಙ್ಗ;
	  ಸ್ವಭಾವ:
	    gcc_unreachable ();
	  }
	}

      /* See if the pointers point to incompatible scalar storage orders.  */
      ಯದಿ (warn_scalar_storage_order
	  && !null_pointer_constant_p (rhs)
	  && (AGGREGATE_TYPE_P (ttl) && TYPE_REVERSE_STORAGE_ORDER (ttl))
	     != (AGGREGATE_TYPE_P (ttr) && TYPE_REVERSE_STORAGE_ORDER (ttr)))
	{
	  ವೃಕ್ಷ t;

	  ವಿಕಲ್ಪ (errtype)
	  {
	  ಪಕ್ಷ ic_argpass:
	    /* Do not warn for built-in functions, for example memcpy, since we
	       control how they behave and they can be useful in this area.  */
	    ಯದಿ (ವೃಕ್ಷ_CODE (rname) != FUNCTION_DECL
		|| !fndecl_built_in_p (rname))
	      warning_at (location, OPT_Wscalar_storage_order,
			  "passing argument %d of %qE from incompatible "
			  "scalar storage order", parmnum, rname);
	    ಭಙ್ಗ;
	  ಪಕ್ಷ ic_assign:
	    /* Do not warn if the RHS is a call to a function that returns a
	       pointer that is not an alias.  */
	    ಯದಿ (ವೃಕ್ಷ_CODE (rhs) != CALL_ಅಭಿವ್ಯಕ್ತಿ
		|| (t = get_callee_fndecl (rhs)) == NULL_ವೃಕ್ಷ
		|| !DECL_IS_MALLOC (t))
	      warning_at (location, OPT_Wscalar_storage_order,
			  "assignment to %qT from pointer type %qT with "
			  "incompatible scalar storage order", type, rhstype);
	    ಭಙ್ಗ;
	  ಪಕ್ಷ ic_init:
	  ಪಕ್ಷ ic_init_const:
	    /* Likewise.  */
	    ಯದಿ (ವೃಕ್ಷ_CODE (rhs) != CALL_ಅಭಿವ್ಯಕ್ತಿ
		|| (t = get_callee_fndecl (rhs)) == NULL_ವೃಕ್ಷ
		|| !DECL_IS_MALLOC (t))
	      warning_at (location, OPT_Wscalar_storage_order,
			  "initialization of %qT from pointer type %qT with "
			  "incompatible scalar storage order", type, rhstype);
	    ಭಙ್ಗ;
	  ಪಕ್ಷ ic_return:
	    warning_at (location, OPT_Wscalar_storage_order,
			"returning %qT from pointer type with incompatible "
			"scalar storage order %qT", rhstype, type);
	    ಭಙ್ಗ;
	  ಸ್ವಭಾವ:
	    gcc_unreachable ();
	  }
	}

      /* Any non-function converts to a [const][volatile] void *
	 and vice versa; otherwise, targets must be the same.
	 Meanwhile, the lhs target must have all the qualifiers of the rhs.  */
      ಯದಿ ((VOID_TYPE_P (ttl) && !TYPE_ATOMIC (ttl))
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
	  ಯದಿ (ವೃಕ್ಷ_CODE (ttr) == ARRAY_TYPE)
	    {
	      ttr = strip_array_types (ttr);
	      ttl = strip_array_types (ttl);

	      ಯದಿ (TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttr)
		  & ~TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttl))
		WARNING_FOR_QUALIFIERS (flag_isoc23,
					location, ಅಭಿವ್ಯಕ್ತಿ_loc,
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
          ಅನ್ಯಥಾ ಯದಿ (pedantic
	      && ((VOID_TYPE_P (ttl) && ವೃಕ್ಷ_CODE (ttr) == FUNCTION_TYPE)
		  ||
		  (VOID_TYPE_P (ttr)
		   && !null_pointer_constant
		   && ವೃಕ್ಷ_CODE (ttl) == FUNCTION_TYPE)))
	    PEDWARN_FOR_ASSIGNMENT (location, ಅಭಿವ್ಯಕ್ತಿ_loc, OPT_Wpedantic,
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
	  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (ttr) != FUNCTION_TYPE
		   && ವೃಕ್ಷ_CODE (ttl) != FUNCTION_TYPE)
	    {
	       /* Assignments between atomic and non-atomic objects are OK.  */
	       ತಾರ್ಕಿಕ warn_quals_ped = TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttr)
				     & ~TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttl);
	       ತಾರ್ಕಿಕ warn_quals = TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (ttr)
				 & ~TYPE_QUALS_NO_ADDR_SPACE_NO_ATOMIC (strip_array_types (ttl));

	      /* Don't warn about loss of qualifier for conversions from
		 qualified void* to pointers to arrays with corresponding
		 qualifier on the element type (except for pedantic before C23). */
	      ಯದಿ (warn_quals || (warn_quals_ped && pedantic && !flag_isoc23))
		PEDWARN_FOR_QUALIFIERS (location, ಅಭಿವ್ಯಕ್ತಿ_loc,
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
	      ಅನ್ಯಥಾ ಯದಿ (warn_quals_ped)
		pedwarn_c11 (location, OPT_Wc11_c23_compat,
			     "array with qualifier on the element is not qualified before C23");

	      /* If this is not a case of ignoring a mismatch in signedness,
		 no warning.  */
	      ಅನ್ಯಥಾ ಯದಿ (VOID_TYPE_P (ttl) || VOID_TYPE_P (ttr)
		       || target_cmp)
		;
	      /* If there is a mismatch, do warn.  */
	      ಅನ್ಯಥಾ ಯದಿ (warn_pointer_sign)
		ವಿಕಲ್ಪ (errtype)
		  {
		  ಪಕ್ಷ ic_argpass:
		    {
		      auto_diagnostic_group d;
		      range_label_for_type_mismatch rhs_label (rhstype, type);
		      gcc_rich_location richloc (ಅಭಿವ್ಯಕ್ತಿ_loc, &rhs_label,
						 highlight_colors::actual);
		      ಯದಿ (pedwarn (&richloc, OPT_Wpointer_sign,
				   "pointer targets in passing argument %d of "
				   "%qE differ in signedness", parmnum, rname))
			inform_for_arg (fundecl, ಅಭಿವ್ಯಕ್ತಿ_loc, parmnum, type,
					rhstype);
		    }
		    ಭಙ್ಗ;
		  ಪಕ್ಷ ic_assign:
		    pedwarn (location, OPT_Wpointer_sign,
			     "pointer targets in assignment from %qT to %qT "
			     "differ in signedness", rhstype, type);
		    ಭಙ್ಗ;
		  ಪಕ್ಷ ic_init:
		  ಪಕ್ಷ ic_init_const:
		    pedwarn_init (location, OPT_Wpointer_sign,
				  "pointer targets in initialization of %qT "
				  "from %qT differ in signedness", type,
				  rhstype);
		    ಭಙ್ಗ;
		  ಪಕ್ಷ ic_return:
		    pedwarn (location, OPT_Wpointer_sign, "pointer targets in "
			     "returning %qT from a function with return type "
			     "%qT differ in signedness", rhstype, type);
		    ಭಙ್ಗ;
		  ಸ್ವಭಾವ:
		    gcc_unreachable ();
		  }
	    }
	  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (ttl) == FUNCTION_TYPE
		   && ವೃಕ್ಷ_CODE (ttr) == FUNCTION_TYPE)
	    {
	      /* Because const and volatile on functions are restrictions
		 that say the function will not do certain things,
		 it is okay to use a const or volatile function
		 where an ordinary one is wanted, but not vice-versa.  */
	      ಯದಿ (TYPE_QUALS_NO_ADDR_SPACE (ttl)
		  & ~TYPE_QUALS_NO_ADDR_SPACE (ttr))
		PEDWARN_FOR_QUALIFIERS (location, ಅಭಿವ್ಯಕ್ತಿ_loc,
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
      ಅನ್ಯಥಾ ಯದಿ (!objc_ok)
	{
	  auto_diagnostic_group d;
	  ತಾರ್ಕಿಕ warned = ಅಸತ್ಯ;
	  pp_markup::element_expected_type e_type (type);
	  pp_markup::element_actual_type e_rhstype (rhstype);
	  ವಿಕಲ್ಪ (errtype)
	    {
	    ಪಕ್ಷ ic_argpass:
	      {
		range_label_for_type_mismatch rhs_label (rhstype, type);
		gcc_rich_location richloc (ಅಭಿವ್ಯಕ್ತಿ_loc, &rhs_label,
					   highlight_colors::actual);
		warned
		  = permerror_opt (&richloc, OPT_Wincompatible_pointer_types,
				   "passing argument %d of %qE from "
				   "incompatible pointer type",
				   parmnum, rname);
		ಯದಿ (warned)
		  inform_for_arg (fundecl, ಅಭಿವ್ಯಕ್ತಿ_loc, parmnum, type, rhstype);
	      }
	      ಭಙ್ಗ;
	    ಪಕ್ಷ ic_assign:
	      ಯದಿ (bltin)
		warned
		  = permerror_opt (location, OPT_Wincompatible_pointer_types,
				   "assignment to %e from pointer to "
				   "%qD with incompatible type %e",
				   &e_type, bltin, &e_rhstype);
	      ಅನ್ಯಥಾ
		warned
		  = permerror_opt (location, OPT_Wincompatible_pointer_types,
				   "assignment to %e from incompatible "
				   "pointer type %e",
				   &e_type, &e_rhstype);
	      ಭಙ್ಗ;
	    ಪಕ್ಷ ic_init:
	    ಪಕ್ಷ ic_init_const:
	      ಯದಿ (bltin)
		warned
		  = permerror_init (location, OPT_Wincompatible_pointer_types,
				    "initialization of %e from pointer to "
				    "%qD with incompatible type %e",
				    &e_type, bltin, &e_rhstype);
	      ಅನ್ಯಥಾ
		warned
		  = permerror_init (location, OPT_Wincompatible_pointer_types,
				    "initialization of %e from incompatible "
				    "pointer type %e",
				    &e_type, &e_rhstype);
	      ಭಙ್ಗ;
	    ಪಕ್ಷ ic_return:
	      ಯದಿ (bltin)
		warned
		  = permerror_opt (location, OPT_Wincompatible_pointer_types,
				   "returning pointer to %qD of type %e from "
				   "a function with incompatible type %e",
				   bltin, &e_rhstype, &e_type);
	      ಅನ್ಯಥಾ
		warned
		  = permerror_opt (location, OPT_Wincompatible_pointer_types,
				   "returning %e from a function with "
				   "incompatible return type %e",
				   &e_rhstype, &e_type);
	      ಭಙ್ಗ;
	    ಸ್ವಭಾವ:
	      gcc_unreachable ();
	    }
	  ಯದಿ (warned)
	    {
	      /* If the mismatching function type is a pointer to a function,
		 try to show the decl of the function.  */
	      ಯದಿ (ವೃಕ್ಷ_CODE (rhs) == ADDR_ಅಭಿವ್ಯಕ್ತಿ
		  && ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_OPERAND (rhs, 0)) == FUNCTION_DECL)
		{
		  ವೃಕ್ಷ rhs_fndecl = ವೃಕ್ಷ_OPERAND (rhs, 0);
		  ಯದಿ (!DECL_IS_UNDECLARED_BUILTIN (rhs_fndecl))
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

      ಪ್ರತ್ಯಾಗಮ convert (type, rhs);
    }
  ಅನ್ಯಥಾ ಯದಿ (codel == POINTER_TYPE && coder == ARRAY_TYPE)
    {
      /* ??? This should not be an error when inlining calls to
	 unprototyped functions.  */
      ಧ್ರುವ ವರ್ಣ ಸಂದೇಶ[] = "invalid use of non-lvalue array";
      ಯದಿ (warnopt)
	warning_at (location, warnopt, ಸಂದೇಶ);
      ಅನ್ಯಥಾ
	error_at (location, ಸಂದೇಶ);
      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
    }
  ಅನ್ಯಥಾ ಯದಿ (codel == POINTER_TYPE
	   && (coder == INTEGER_TYPE
	       || coder == ENUMERAL_TYPE
	       || coder == BOOLEAN_TYPE
	       || coder == NULLPTR_TYPE
	       || coder == BITINT_TYPE))
    {
      ಯದಿ (null_pointer_constant && c_inhibit_evaluation_warnings == 0
	  && coder != NULLPTR_TYPE)
	warning_at (location, OPT_Wzero_as_null_pointer_constant,
		    "zero as null pointer constant");
      /* A NULLPTR type is just a nullptr always.  */
      ಯದಿ (coder == NULLPTR_TYPE)
	ಪ್ರತ್ಯಾಗಮ omit_one_operand_loc (ಅಭಿವ್ಯಕ್ತಿ_loc, type, nullptr_ಗಂಟು, rhs);
      /* An explicit constant 0 or type nullptr_t can convert to a pointer,
	 or one that results from arithmetic, even including a cast to
	 integer type.  */
      ಅನ್ಯಥಾ ಯದಿ (!null_pointer_constant)
	ವಿಕಲ್ಪ (errtype)
	  {
	  ಪಕ್ಷ ic_argpass:
	    {
	      auto_diagnostic_group d;
	      range_label_for_type_mismatch rhs_label (rhstype, type);
	      gcc_rich_location richloc (ಅಭಿವ್ಯಕ್ತಿ_loc, &rhs_label,
					 highlight_colors::actual);
	      ಯದಿ (permerror_opt (&richloc, OPT_Wint_conversion,
				 "passing argument %d of %qE makes pointer "
				 "from integer without a cast", parmnum, rname))
		{
		  maybe_emit_indirection_note (ಅಭಿವ್ಯಕ್ತಿ_loc, rhs, type);
		  inform_for_arg (fundecl, ಅಭಿವ್ಯಕ್ತಿ_loc, parmnum, type, rhstype);
		}
	    }
	    ಭಙ್ಗ;
	  ಪಕ್ಷ ic_assign:
	    permerror_opt (location, OPT_Wint_conversion,
			   "assignment to %qT from %qT makes pointer from "
			   "integer without a cast", type, rhstype);
	    ಭಙ್ಗ;
	  ಪಕ್ಷ ic_init:
	  ಪಕ್ಷ ic_init_const:
	    permerror_init (location, OPT_Wint_conversion,
			    "initialization of %qT from %qT makes pointer "
			    "from integer without a cast", type, rhstype);
	    ಭಙ್ಗ;
	  ಪಕ್ಷ ic_return:
	    permerror_init (location, OPT_Wint_conversion,
			    "returning %qT from a function with return type "
			    "%qT makes pointer from integer without a cast",
			    rhstype, type);
	    ಭಙ್ಗ;
	  ಸ್ವಭಾವ:
	    gcc_unreachable ();
	  }

      ಪ್ರತ್ಯಾಗಮ convert (type, rhs);
    }
  ಅನ್ಯಥಾ ಯದಿ ((codel == INTEGER_TYPE || codel == BITINT_TYPE)
	   && coder == POINTER_TYPE)
    {
      ವಿಕಲ್ಪ (errtype)
	{
	ಪಕ್ಷ ic_argpass:
	  {
	    auto_diagnostic_group d;
	    range_label_for_type_mismatch rhs_label (rhstype, type);
	    gcc_rich_location richloc (ಅಭಿವ್ಯಕ್ತಿ_loc, &rhs_label,
				       highlight_colors::actual);
	    ಯದಿ (permerror_opt (&richloc, OPT_Wint_conversion,
			       "passing argument %d of %qE makes integer from "
			       "pointer without a cast", parmnum, rname))
	      {
		maybe_emit_indirection_note (ಅಭಿವ್ಯಕ್ತಿ_loc, rhs, type);
		inform_for_arg (fundecl, ಅಭಿವ್ಯಕ್ತಿ_loc, parmnum, type, rhstype);
	      }
	  }
	  ಭಙ್ಗ;
	ಪಕ್ಷ ic_assign:
	  permerror_opt (location, OPT_Wint_conversion,
			 "assignment to %qT from %qT makes integer from "
			 "pointer without a cast", type, rhstype);
	  ಭಙ್ಗ;
	ಪಕ್ಷ ic_init:
	ಪಕ್ಷ ic_init_const:
	  permerror_init (location, OPT_Wint_conversion,
			  "initialization of %qT from %qT makes integer "
			  "from pointer without a cast", type, rhstype);
	  ಭಙ್ಗ;
	ಪಕ್ಷ ic_return:
	  permerror_opt (location, OPT_Wint_conversion, "returning %qT from a "
			 "function with return type %qT makes integer from "
			 "pointer without a cast", rhstype, type);
	  ಭಙ್ಗ;
	ಸ್ವಭಾವ:
	  gcc_unreachable ();
	}

      ಪ್ರತ್ಯಾಗಮ convert (type, rhs);
    }
  ಅನ್ಯಥಾ ಯದಿ (C_BOOLEAN_TYPE_P (type)
	   /* The type nullptr_t may be converted to bool.  The
	      result is false.  */
	   && (coder == POINTER_TYPE || coder == NULLPTR_TYPE))
    {
      ವೃಕ್ಷ ret;
      ತಾರ್ಕಿಕ save = in_late_ದ್ವಿಮಾನ_op;
      in_late_ದ್ವಿಮಾನ_op = ಸತ್ಯ;
      ret = convert (type, rhs);
      in_late_ದ್ವಿಮಾನ_op = save;
      ಪ್ರತ್ಯಾಗಮ ret;
    }
  ಅನ್ಯಥಾ ಯದಿ (codel == NULLPTR_TYPE && null_pointer_constant)
    ಪ್ರತ್ಯಾಗಮ convert (type, rhs);

  ವಿಕಲ್ಪ (errtype)
    {
    ಪಕ್ಷ ic_argpass:
      {
	auto_diagnostic_group d;
	range_label_for_type_mismatch rhs_label (rhstype, type);
	gcc_rich_location richloc (ಅಭಿವ್ಯಕ್ತಿ_loc, &rhs_label,
				   highlight_colors::actual);
	ಧ್ರುವ ವರ್ಣ ಸಂದೇಶ[] = G_("incompatible type for argument %d of %qE");
	ಯದಿ (warnopt)
	  warning_at (ಅಭಿವ್ಯಕ್ತಿ_loc, warnopt, ಸಂದೇಶ, parmnum, rname);
	ಅನ್ಯಥಾ
	  error_at (&richloc, ಸಂದೇಶ, parmnum, rname);
	inform_for_arg (fundecl, ಅಭಿವ್ಯಕ್ತಿ_loc, parmnum, type, rhstype);
      }
      ಭಙ್ಗ;
    ಪಕ್ಷ ic_assign:
      {
	ಧ್ರುವ ವರ್ಣ ಸಂದೇಶ[]
	  = G_("incompatible types when assigning to type %qT from type %qT");
	ಯದಿ (warnopt)
	  warning_at (ಅಭಿವ್ಯಕ್ತಿ_loc, 0, ಸಂದೇಶ, type, rhstype);
	ಅನ್ಯಥಾ
	  error_at (ಅಭಿವ್ಯಕ್ತಿ_loc, ಸಂದೇಶ, type, rhstype);
	ಭಙ್ಗ;
      }
    ಪಕ್ಷ ic_init:
    ಪಕ್ಷ ic_init_const:
      {
	ಧ್ರುವ ವರ್ಣ ಸಂದೇಶ[]
	  = G_("incompatible types when initializing type %qT using type %qT");
	ಯದಿ (warnopt)
	  warning_at (location, 0, ಸಂದೇಶ, type, rhstype);
	ಅನ್ಯಥಾ
	  error_at (location, ಸಂದೇಶ, type, rhstype);
	ಭಙ್ಗ;
      }
    ಪಕ್ಷ ic_return:
      {
	ಧ್ರುವ ವರ್ಣ ಸಂದೇಶ[]
	  = G_("incompatible types when returning type %qT but %qT was expected");
	ಯದಿ (warnopt)
	  warning_at (location, 0, ಸಂದೇಶ, rhstype, type);
	ಅನ್ಯಥಾ
	  error_at (location, ಸಂದೇಶ, rhstype, type);
	ಭಙ್ಗ;
      }
    ಸ್ವಭಾವ:
      gcc_unreachable ();
    }

  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
}

/* If VALUE is a compound expr all of whose expressions are constant, then
   return its value.  Otherwise, return error_mark_node.

   This is for handling COMPOUND_EXPRs as initializer elements
   which is allowed with a warning when -pedantic is specified.  */

ಸ್ಥಿರ ವೃಕ್ಷ
valid_compound_ಅಭಿವ್ಯಕ್ತಿ_initializer (ವೃಕ್ಷ ಮೌಲ್ಯ, ವೃಕ್ಷ endtype)
{
  ಯದಿ (ವೃಕ್ಷ_CODE (ಮೌಲ್ಯ) == COMPOUND_ಅಭಿವ್ಯಕ್ತಿ)
    {
      ಯದಿ (valid_compound_ಅಭಿವ್ಯಕ್ತಿ_initializer (ವೃಕ್ಷ_OPERAND (ಮೌಲ್ಯ, 0), endtype)
	  == error_mark_ಗಂಟು)
	ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
      ಪ್ರತ್ಯಾಗಮ valid_compound_ಅಭಿವ್ಯಕ್ತಿ_initializer (ವೃಕ್ಷ_OPERAND (ಮೌಲ್ಯ, 1),
					      endtype);
    }
  ಅನ್ಯಥಾ ಯದಿ (!initializer_constant_valid_p (ಮೌಲ್ಯ, endtype))
    ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
  ಅನ್ಯಥಾ
    ಪ್ರತ್ಯಾಗಮ ಮೌಲ್ಯ;
}

/* Perform appropriate conversions on the initial value of a variable,
   store it in the declaration DECL,
   and print any error messages that are appropriate.
   If ORIGTYPE is not NULL_TREE, it is the original type of INIT.
   If the init is invalid, store an ERROR_MARK.

   INIT_LOC is the location of the initial value.  */

ಶೂನ್ಯ
store_init_ಮೌಲ್ಯ (location_t init_loc, ವೃಕ್ಷ decl, ವೃಕ್ಷ init, ವೃಕ್ಷ origtype)
{
  ವೃಕ್ಷ ಮೌಲ್ಯ, type;
  ತಾರ್ಕಿಕ npc = ಅಸತ್ಯ;
  ತಾರ್ಕಿಕ int_const_ಅಭಿವ್ಯಕ್ತಿ = ಅಸತ್ಯ;
  ತಾರ್ಕಿಕ arith_const_ಅಭಿವ್ಯಕ್ತಿ = ಅಸತ್ಯ;

  /* If variable's type was invalidly declared, just ignore it.  */

  type = ವೃಕ್ಷ_TYPE (decl);
  ಯದಿ (ವೃಕ್ಷ_CODE (type) == ERROR_MARK)
    ಪ್ರತ್ಯಾಗಮ;

  /* Digest the specified initializer into an expression.  */

  ಯದಿ (init)
    {
      npc = null_pointer_constant_p (init);
      int_const_ಅಭಿವ್ಯಕ್ತಿ = (ವೃಕ್ಷ_CODE (init) == INTEGER_CST
			&& !ವೃಕ್ಷ_OVERFLOW (init)
			&& INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (init)));
      /* Not fully determined before folding.  */
      arith_const_ಅಭಿವ್ಯಕ್ತಿ = ಸತ್ಯ;
    }
  ತಾರ್ಕಿಕ constexpr_p = (VAR_P (decl)
		      && C_DECL_DECLARED_CONSTEXPR (decl));
  ಮೌಲ್ಯ = digest_init (init_loc, decl, type, init, origtype, npc,
		       int_const_ಅಭಿವ್ಯಕ್ತಿ, arith_const_ಅಭಿವ್ಯಕ್ತಿ, ಸತ್ಯ,
		       ವೃಕ್ಷ_STATIC (decl) || constexpr_p, constexpr_p);

  /* Store the expression if valid; else report error.  */

  ಯದಿ (!in_system_header_at (ಒಳಹರಿವು_location)
      && AGGREGATE_TYPE_P (ವೃಕ್ಷ_TYPE (decl)) && !ವೃಕ್ಷ_STATIC (decl))
    warning (OPT_Wtraditional, "traditional C rejects automatic "
	     "aggregate initialization");

  ಯದಿ (ಮೌಲ್ಯ != error_mark_ಗಂಟು || ವೃಕ್ಷ_CODE (decl) != FUNCTION_DECL)
    DECL_INITIAL (decl) = ಮೌಲ್ಯ;

  /* ANSI wants warnings about out-of-range constant initializers.  */
  STRIP_TYPE_NOPS (ಮೌಲ್ಯ);
  ಯದಿ (ವೃಕ್ಷ_STATIC (decl))
    constant_expression_warning (ಮೌಲ್ಯ);

  /* Check if we need to set array size from compound literal size.  */
  ಯದಿ (ವೃಕ್ಷ_CODE (type) == ARRAY_TYPE
      && TYPE_DOMAIN (type) == NULL_ವೃಕ್ಷ
      && ಮೌಲ್ಯ != error_mark_ಗಂಟು)
    {
      ವೃಕ್ಷ inside_init = init;

      STRIP_TYPE_NOPS (inside_init);
      inside_init = fold (inside_init);

      ಯದಿ (ವೃಕ್ಷ_CODE (inside_init) == COMPOUND_LITERAL_ಅಭಿವ್ಯಕ್ತಿ)
	{
	  ವೃಕ್ಷ cldecl = COMPOUND_LITERAL_ಅಭಿವ್ಯಕ್ತಿ_DECL (inside_init);

	  ಯದಿ (TYPE_DOMAIN (ವೃಕ್ಷ_TYPE (cldecl)))
	    {
	      /* For int foo[] = (int [3]){1}; we need to set array size
		 now since later on array initializer will be just the
		 brace enclosed list of the compound literal.  */
	      ವೃಕ್ಷ etype = strip_array_types (ವೃಕ್ಷ_TYPE (decl));
	      type = build_distinct_type_copy (TYPE_MAIN_VARIANT (type));
	      TYPE_DOMAIN (type) = TYPE_DOMAIN (ವೃಕ್ಷ_TYPE (cldecl));
	      layout_type (type);
	      layout_decl (cldecl, 0);
	      ವೃಕ್ಷ_TYPE (decl)
		= c_build_qualified_type (type, TYPE_QUALS (etype));
	    }
	}
    }
}

/* Methods for storing and printing names for error messages.  */

/* Implement a spelling stack that allows components of a name to be pushed
   and popped.  Each element on the stack is this structure.  */

ಸಂರಚನಾ spelling
{
  ಪೂರ್ಣಾಙ್ಕ kind;
  ಸಙ್ಘ
    {
      unsigned HOST_WIDE_INT i;
      ಧ್ರುವ ವರ್ಣ *s;
    } u;
};

#define SPELLING_STRING 1
#define SPELLING_MEMBER 2
#define SPELLING_BOUNDS 3

ಸ್ಥಿರ ಸಂರಚನಾ spelling *spelling;	/* Next stack element (unused).  */
ಸ್ಥಿರ ಸಂರಚನಾ spelling *spelling_base;	/* Spelling stack base.  */
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ spelling_size;		/* Size of the spelling stack.  */

/* Macros to save and restore the spelling stack around push_... functions.
   Alternative to SAVE_SPELLING_STACK.  */

#define SPELLING_DEPTH() (spelling - spelling_base)
#define RESTORE_SPELLING_DEPTH(DEPTH) (spelling = spelling_base + (DEPTH))

/* Push an element on the spelling stack with type KIND and assign VALUE
   to MEMBER.  */

#define ತಳ್ಳು_SPELLING(KIND, ಮೌಲ್ಯ_2, MEMBER)				\
{									\
  ಪೂರ್ಣಾಙ್ಕ depth = SPELLING_DEPTH ();					\
									\
  ಯದಿ (depth >= spelling_size)						\
    {									\
      spelling_size += 10;						\
      spelling_base = XRESIZEVEC (ಸಂರಚನಾ spelling, spelling_base,	\
				  spelling_size);			\
      RESTORE_SPELLING_DEPTH (depth);					\
    }									\
									\
  spelling->kind = (KIND);						\
  spelling->MEMBER = (ಮೌಲ್ಯ_2);						\
  spelling++;								\
}

/* Push STRING on the stack.  Printed literally.  */

ಸ್ಥಿರ ಶೂನ್ಯ
ತಳ್ಳು_string (ಧ್ರುವ ವರ್ಣ *string)
{
  ತಳ್ಳು_SPELLING (SPELLING_STRING, string, u.s);
}

/* Push a member name on the stack.  Printed as '.' STRING.  */

ಸ್ಥಿರ ಶೂನ್ಯ
ತಳ್ಳು_member_name (ವೃಕ್ಷ decl)
{
  ಧ್ರುವ ವರ್ಣ *ಧ್ರುವ string
    = (DECL_NAME (decl)
       ? identifier_to_locale (IDENTIFIER_POINTER (DECL_NAME (decl)))
       : _("<anonymous>"));
  ತಳ್ಳು_SPELLING (SPELLING_MEMBER, string, u.s);
}

/* Push an array bounds on the stack.  Printed as [BOUNDS].  */

ಸ್ಥಿರ ಶೂನ್ಯ
ತಳ್ಳು_array_bounds (unsigned HOST_WIDE_INT bounds)
{
  ತಳ್ಳು_SPELLING (SPELLING_BOUNDS, bounds, u.i);
}

/* Compute the maximum size in bytes of the printed spelling.  */

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ
spelling_length (ಶೂನ್ಯ)
{
  ಪೂರ್ಣಾಙ್ಕ size = 0;
  ಸಂರಚನಾ spelling *p;

  ಪ್ರತಿ (p = spelling_base; p < spelling; p++)
    {
      ಯದಿ (p->kind == SPELLING_BOUNDS)
	size += 25;
      ಅನ್ಯಥಾ
	size += strlen (p->u.s) + 1;
    }

  ಪ್ರತ್ಯಾಗಮ size;
}

/* Print the spelling to BUFFER and return it.  */

ಸ್ಥಿರ ವರ್ಣ *
print_spelling (ವರ್ಣ *buffer)
{
  ವರ್ಣ *d = buffer;
  ಸಂರಚನಾ spelling *p;

  ಪ್ರತಿ (p = spelling_base; p < spelling; p++)
    ಯದಿ (p->kind == SPELLING_BOUNDS)
      {
	sprintf (d, "[" HOST_WIDE_INT_PRINT_UNSIGNED "]", p->u.i);
	d += strlen (d);
      }
    ಅನ್ಯಥಾ
      {
	ಧ್ರುವ ವರ್ಣ *s;
	ಯದಿ (p->kind == SPELLING_MEMBER)
	  *d++ = '.';
	ಪ್ರತಿ (s = p->u.s; (*d = *s++); d++)
	  ;
      }
  *d++ = '\0';
  ಪ್ರತ್ಯಾಗಮ buffer;
}

/* Check whether INIT, a floating or integer constant, is
   representable in TYPE, a real floating type with the same radix or
   a decimal floating type initialized with a binary floating
   constant.  Return true if OK, false if not.  */
ಸ್ಥಿರ ತಾರ್ಕಿಕ
constexpr_init_fits_real_type (ವೃಕ್ಷ type, ವೃಕ್ಷ init)
{
  gcc_assert (SCALAR_FLOAT_TYPE_P (type));
  gcc_assert (ವೃಕ್ಷ_CODE (init) == INTEGER_CST || ವೃಕ್ಷ_CODE (init) == REAL_CST);
  ಯದಿ (ವೃಕ್ಷ_CODE (init) == REAL_CST
      && TYPE_MODE (ವೃಕ್ಷ_TYPE (init)) == TYPE_MODE (type))
    {
      /* Same mode, no conversion required except for the case of
	 signaling NaNs if the types are incompatible (e.g. double and
	 long double with the same mode).  */
      ಯದಿ (REAL_ಮೌಲ್ಯ_ISSIGNALING_NAN (ವೃಕ್ಷ_REAL_CST (init))
	  && !comptypes (TYPE_MAIN_VARIANT (type),
			 TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (init))))
	ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
      ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
    }
  ಯದಿ (ವೃಕ್ಷ_CODE (init) == INTEGER_CST)
    {
      ವೃಕ್ಷ converted = build_real_from_int_cst (type, init);
      ತಾರ್ಕಿಕ fail = ಅಸತ್ಯ;
      wide_int w = real_to_integer (&ವೃಕ್ಷ_REAL_CST (converted), &fail,
				    TYPE_PRECISION (ವೃಕ್ಷ_TYPE (init)));
      ಪ್ರತ್ಯಾಗಮ !fail && wi::eq_p (w, wi::to_wide (init));
    }
  ಯದಿ (REAL_ಮೌಲ್ಯ_ISSIGNALING_NAN (ವೃಕ್ಷ_REAL_CST (init)))
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
  ಯದಿ ((REAL_ಮೌಲ್ಯ_ISINF (ವೃಕ್ಷ_REAL_CST (init))
       && MODE_HAS_INFINITIES (TYPE_MODE (type)))
      || (REAL_ಮೌಲ್ಯ_ISNAN (ವೃಕ್ಷ_REAL_CST (init))
	  && MODE_HAS_NANS (TYPE_MODE (type))))
    ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
  ಯದಿ (DECIMAL_FLOAT_TYPE_P (type)
      && !DECIMAL_FLOAT_TYPE_P (ವೃಕ್ಷ_TYPE (init)))
    {
      /* This is valid if the real number represented by the
	 initializer can be exactly represented in the decimal
	 type.  Compare the values using MPFR.  */
      REAL_ಮೌಲ್ಯ_TYPE t;
      real_convert (&t, TYPE_MODE (type), &ವೃಕ್ಷ_REAL_CST (init));
      mpfr_t bin_val, dec_val;
      mpfr_init2 (bin_val, REAL_MODE_FORMAT (TYPE_MODE (ವೃಕ್ಷ_TYPE (init)))->p);
      mpfr_init2 (dec_val, REAL_MODE_FORMAT (TYPE_MODE (ವೃಕ್ಷ_TYPE (init)))->p);
      mpfr_from_real (bin_val, &ವೃಕ್ಷ_REAL_CST (init), MPFR_RNDN);
      ವರ್ಣ string[256];
      real_to_decimal (string, &t, ಪರಿಮಾಣ string, 0, 1);
      ತಾರ್ಕಿಕ res = (mpfr_strtofr (dec_val, string, ರಿಕ್ತ, 10, MPFR_RNDN) == 0
		  && mpfr_equal_p (bin_val, dec_val));
      mpfr_clear (bin_val);
      mpfr_clear (dec_val);
      ಪ್ರತ್ಯಾಗಮ res;
    }
  /* exact_real_truncate is not quite right here, since it doesn't
     allow even an exact conversion to subnormal values.  */
  REAL_ಮೌಲ್ಯ_TYPE t;
  real_convert (&t, TYPE_MODE (type), &ವೃಕ್ಷ_REAL_CST (init));
  ಪ್ರತ್ಯಾಗಮ real_identical (&t, &ವೃಕ್ಷ_REAL_CST (init));
}

/* Check whether INIT (location LOC) is valid as a 'constexpr'
   initializer for type TYPE, and give an error if not.  INIT has
   already been folded and verified to be constant.  INT_CONST_EXPR
   and ARITH_CONST_EXPR say whether it is an integer constant
   expression or arithmetic constant expression, respectively.  If
   TYPE is not a scalar type, this function does nothing.  */

ಸ್ಥಿರ ಶೂನ್ಯ
check_constexpr_init (location_t loc, ವೃಕ್ಷ type, ವೃಕ್ಷ init,
		      ತಾರ್ಕಿಕ int_const_ಅಭಿವ್ಯಕ್ತಿ, ತಾರ್ಕಿಕ arith_const_ಅಭಿವ್ಯಕ್ತಿ)
{
  ಯದಿ (POINTER_TYPE_P (type))
    {
      /* The initializer must be null.  */
      ಯದಿ (ವೃಕ್ಷ_CODE (init) != INTEGER_CST || !integer_zerop (init))
	error_at (loc, "%<constexpr%> pointer initializer is not null");
      ಪ್ರತ್ಯಾಗಮ;
    }
  ಯದಿ (INTEGRAL_TYPE_P (type))
    {
      /* The initializer must be an integer constant expression,
	 representable in the target type.  */
      ಯದಿ (!int_const_ಅಭಿವ್ಯಕ್ತಿ)
	{
	  ಯದಿ (ವೃಕ್ಷ_CODE (init) == RAW_DATA_CST
	      && TYPE_PRECISION (type) == CHAR_BIT)
	    {
	      ಯದಿ (!TYPE_UNSIGNED (type))
		ಪ್ರತಿ (unsigned ಪೂರ್ಣಾಙ್ಕ i = 0;
		     i < (unsigned) RAW_DATA_LENGTH (init); ++i)
		  ಯದಿ (RAW_DATA_SCHAR_ELT (init, i) < 0)
		    {
		      error_at (loc, "%<constexpr%> initializer not "
				"representable in type of object");
		      ಭಙ್ಗ;
		    }
	    }
	  ಅನ್ಯಥಾ
	    error_at (loc, "%<constexpr%> integer initializer is not an "
		      "integer constant expression");
	}
      ಅನ್ಯಥಾ ಯದಿ (!int_fits_type_p (init, type))
	error_at (loc, "%<constexpr%> initializer not representable in "
		  "type of object");
      ಪ್ರತ್ಯಾಗಮ;
    }
  /* We don't apply any extra checks to extension types such as vector
     or fixed-point types.  */
  ಯದಿ (ವೃಕ್ಷ_CODE (type) != REAL_TYPE && ವೃಕ್ಷ_CODE (type) != COMPLEX_TYPE)
    ಪ್ರತ್ಯಾಗಮ;
  ಯದಿ (!arith_const_ಅಭಿವ್ಯಕ್ತಿ)
    {
      error_at (loc, "%<constexpr%> initializer is not an arithmetic "
		"constant expression");
      ಪ್ರತ್ಯಾಗಮ;
    }
  /* We don't apply any extra checks to complex integers.  */
  ಯದಿ (ವೃಕ್ಷ_CODE (type) == COMPLEX_TYPE
      && ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (type)) != REAL_TYPE)
    ಪ್ರತ್ಯಾಗಮ;
  /* Following N3082, a real type cannot be initialized from a complex
     type and a binary type cannot be initialized from a decimal type
     (but initializing a decimal type from a binary type is OK).
     Signaling NaN initializers are OK only if the types are
     compatible (not just the same mode); all quiet NaN and infinity
     initializations are considered to preserve the value.  */
  ಯದಿ (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (init)) == COMPLEX_TYPE
      && SCALAR_FLOAT_TYPE_P (type))
    {
      error_at (loc, "%<constexpr%> initializer for a real type is of "
		"complex type");
      ಪ್ರತ್ಯಾಗಮ;
    }
  ಯದಿ (SCALAR_FLOAT_TYPE_P (type)
      && SCALAR_FLOAT_TYPE_P (ವೃಕ್ಷ_TYPE (init))
      && DECIMAL_FLOAT_TYPE_P (ವೃಕ್ಷ_TYPE (init))
      && !DECIMAL_FLOAT_TYPE_P (type))
    {
      error_at (loc, "%<constexpr%> initializer for a binary "
		"floating-point type is of decimal type");
      ಪ್ರತ್ಯಾಗಮ;
    }
  ತಾರ್ಕಿಕ fits;
  ಯದಿ (ವೃಕ್ಷ_CODE (type) == COMPLEX_TYPE)
    {
      ವಿಕಲ್ಪ (ವೃಕ್ಷ_CODE (init))
	{
	ಪಕ್ಷ INTEGER_CST:
	ಪಕ್ಷ REAL_CST:
	  fits = constexpr_init_fits_real_type (ವೃಕ್ಷ_TYPE (type), init);
	  ಭಙ್ಗ;
	ಪಕ್ಷ COMPLEX_CST:
	  fits = (constexpr_init_fits_real_type (ವೃಕ್ಷ_TYPE (type),
						 ವೃಕ್ಷ_REALPART (init))
		  && constexpr_init_fits_real_type (ವೃಕ್ಷ_TYPE (type),
						    ವೃಕ್ಷ_IMAGPART (init)));
	  ಭಙ್ಗ;
	ಸ್ವಭಾವ:
	  gcc_unreachable ();
	}
    }
  ಅನ್ಯಥಾ
    fits = constexpr_init_fits_real_type (type, init);
  ಯದಿ (!fits)
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

ಸ್ಥಿರ ವೃಕ್ಷ
digest_init (location_t init_loc, ವೃಕ್ಷ decl, ವೃಕ್ಷ type, ವೃಕ್ಷ init,
	     ವೃಕ್ಷ origtype, ತಾರ್ಕಿಕ null_pointer_constant, ತಾರ್ಕಿಕ int_const_ಅಭಿವ್ಯಕ್ತಿ,
	     ತಾರ್ಕಿಕ arith_const_ಅಭಿವ್ಯಕ್ತಿ, ತಾರ್ಕಿಕ strict_string,
	     ತಾರ್ಕಿಕ require_constant, ತಾರ್ಕಿಕ require_constexpr)
{
  ಗಣನಾ ವೃಕ್ಷ_code code = ವೃಕ್ಷ_CODE (type);
  ವೃಕ್ಷ inside_init = init;
  ವೃಕ್ಷ semantic_type = NULL_ವೃಕ್ಷ;
  ತಾರ್ಕಿಕ maybe_const = ಸತ್ಯ;

  ಯದಿ (type == error_mark_ಗಂಟು
      || !init
      || error_operand_p (init))
    ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;

  STRIP_TYPE_NOPS (inside_init);

  /* If require_constant is TRUE,  when the initializer is a call to
     .ACCESS_WITH_SIZE, use the first argument as the initializer.
     For example:
     y = (char *) .ACCESS_WITH_SIZE ((char *) &static_annotated.c,...)
     will be converted to
     y = &static_annotated.c.  */

  ಯದಿ (require_constant
      && ವೃಕ್ಷ_CODE (inside_init) == NOP_ಅಭಿವ್ಯಕ್ತಿ
      && ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_OPERAND (inside_init, 0)) == CALL_ಅಭಿವ್ಯಕ್ತಿ
      && is_access_with_size_p (ವೃಕ್ಷ_OPERAND (inside_init, 0)))
    inside_init
      = get_ref_from_access_with_size (ವೃಕ್ಷ_OPERAND (inside_init, 0));

  ಯದಿ (!c_in_omp_for)
    {
      ಯದಿ (ವೃಕ್ಷ_CODE (inside_init) == EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ)
	{
	  semantic_type = ವೃಕ್ಷ_TYPE (inside_init);
	  inside_init = ವೃಕ್ಷ_OPERAND (inside_init, 0);
	}
      inside_init = c_fully_fold (inside_init, require_constant, &maybe_const);
    }
  /* TODO: this may not detect all cases of expressions folding to
     constants that are not arithmetic constant expressions.  */
  ಯದಿ (!maybe_const)
    arith_const_ಅಭಿವ್ಯಕ್ತಿ = ಅಸತ್ಯ;
  ಅನ್ಯಥಾ ಯದಿ (!INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (inside_init))
	   && ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (inside_init)) != REAL_TYPE
	   && ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (inside_init)) != COMPLEX_TYPE)
    arith_const_ಅಭಿವ್ಯಕ್ತಿ = ಅಸತ್ಯ;
  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (inside_init) != INTEGER_CST
	   && ವೃಕ್ಷ_CODE (inside_init) != REAL_CST
	   && ವೃಕ್ಷ_CODE (inside_init) != COMPLEX_CST
	   && ವೃಕ್ಷ_CODE (inside_init) != RAW_DATA_CST)
    arith_const_ಅಭಿವ್ಯಕ್ತಿ = ಅಸತ್ಯ;
  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_OVERFLOW (inside_init))
    arith_const_ಅಭಿವ್ಯಕ್ತಿ = ಅಸತ್ಯ;

  /* Initialization of an array of chars from a string constant
     optionally enclosed in braces.  */

  ಯದಿ (code == ARRAY_TYPE && inside_init
      && ವೃಕ್ಷ_CODE (inside_init) == STRING_CST)
    {
      ವೃಕ್ಷ typ1
	= (TYPE_ATOMIC (ವೃಕ್ಷ_TYPE (type))
	   ? c_build_qualified_type (TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (type)),
				     TYPE_QUAL_ATOMIC)
	   : TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (type)));
      /* Note that an array could be both an array of character type
	 and an array of wchar_t if wchar_t is signed char or unsigned
	 char.  */
      ತಾರ್ಕಿಕ char_array = (typ1 == char_type_ಗಂಟು
			 || typ1 == signed_char_type_ಗಂಟು
			 || typ1 == unsigned_char_type_ಗಂಟು);
      ತಾರ್ಕಿಕ wchar_array = comptypes (typ1, wchar_type_ಗಂಟು);
      ತಾರ್ಕಿಕ char16_array = comptypes (typ1, char16_type_ಗಂಟು);
      ತಾರ್ಕಿಕ char32_array = comptypes (typ1, char32_type_ಗಂಟು);

      ಯದಿ (char_array || wchar_array || char16_array || char32_array)
	{
	  ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ ಅಭಿವ್ಯಕ್ತಿ;
	  ವೃಕ್ಷ typ2 = TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (inside_init)));
	  ತಾರ್ಕಿಕ incompat_string_cst = ಅಸತ್ಯ;
	  ಅಭಿವ್ಯಕ್ತಿ.ಮೌಲ್ಯ = inside_init;
	  ಅಭಿವ್ಯಕ್ತಿ.original_code = (strict_string ? STRING_CST : ERROR_MARK);
	  ಅಭಿವ್ಯಕ್ತಿ.original_type = ರಿಕ್ತ;
	  ಅಭಿವ್ಯಕ್ತಿ.m_decimal = 0;
	  maybe_warn_string_init (init_loc, type, ಅಭಿವ್ಯಕ್ತಿ);

	  ಯದಿ (flexible_array_member_type_p (type))
	    pedwarn_init (init_loc, OPT_Wpedantic,
			  "initialization of a flexible array member");

	  ಯದಿ (comptypes (TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (inside_init)),
			 TYPE_MAIN_VARIANT (type)))
	    ಪ್ರತ್ಯಾಗಮ inside_init;

	  ಯದಿ (char_array)
	    {
	      ಯದಿ (typ2 != char_type_ಗಂಟು && typ2 != char8_type_ಗಂಟು)
		incompat_string_cst = ಸತ್ಯ;
	    }
	  ಅನ್ಯಥಾ ಯದಿ (!comptypes (typ1, typ2))
	    incompat_string_cst = ಸತ್ಯ;

          ಯದಿ (incompat_string_cst)
            {
	      error_init (init_loc, "cannot initialize array of %qT from "
			  "a string literal with type array of %qT",
			  typ1, typ2);
	      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
            }

	  ಯದಿ (require_constexpr
	      && TYPE_UNSIGNED (typ1) != TYPE_UNSIGNED (typ2))
	    {
	      /* Check if all characters of the string can be
		 represented in the type of the constexpr object being
		 initialized.  */
	      unsigned HOST_WIDE_INT len = ವೃಕ್ಷ_STRING_LENGTH (inside_init);
	      ಧ್ರುವ unsigned ವರ್ಣ *p =
		(ಧ್ರುವ unsigned ವರ್ಣ *) ವೃಕ್ಷ_STRING_POINTER (inside_init);
	      gcc_assert (CHAR_TYPE_SIZE == 8 && CHAR_BIT == 8);
	      ಪ್ರತಿ (unsigned i = 0; i < len; i++)
		ಯದಿ (p[i] > 127)
		  {
		    error_init (init_loc, "%<constexpr%> initializer not "
				"representable in type of object");
		    ಭಙ್ಗ;
		  }
	    }

	  ಯದಿ (TYPE_DOMAIN (type) != NULL_ವೃಕ್ಷ
	      && TYPE_SIZE (type) != NULL_ವೃಕ್ಷ
	      && ವೃಕ್ಷ_CODE (TYPE_SIZE (type)) == INTEGER_CST)
	    {
	      unsigned HOST_WIDE_INT len = ವೃಕ್ಷ_STRING_LENGTH (inside_init);

	      ಯದಿ (compare_ವೃಕ್ಷ_int (TYPE_SIZE_UNIT (type), len) < 0)
		{
		  unsigned HOST_WIDE_INT avail
		    = ವೃಕ್ಷ_to_uhwi (TYPE_SIZE_UNIT (type));
		  unsigned unit = TYPE_PRECISION (typ1) / BITS_PER_UNIT;
		  ಧ್ರುವ ವರ್ಣ *p = ವೃಕ್ಷ_STRING_POINTER (inside_init);

		  /* Construct truncated string.  */
		  inside_init = build_string (avail, p);

		  /* Subtract the size of a single (possibly wide) character
		     because it may be ok to ignore the terminating NUL char
		     that is counted in the length of the constant.  */
		  ಯದಿ (len - unit > avail)
		    pedwarn_init (init_loc, 0,
				  "initializer-string for array of %qT "
				  "is too long (%wu chars into %wu "
				  "available)", typ1, len, avail);
		  ಅನ್ಯಥಾ ಯದಿ (warn_cxx_compat)
		    warning_at (init_loc, OPT_Wc___compat,
				"initializer-string for array of %qT "
				"is too long for C++ (%wu chars into %wu "
				"available)", typ1, len, avail);
		  ಅನ್ಯಥಾ ಯದಿ (warn_unterminated_string_initialization
			   && get_attr_nonstring_decl (decl) == NULL_ವೃಕ್ಷ)
		    warning_at (init_loc,
				OPT_Wunterminated_string_initialization,
				"initializer-string for array of %qT "
				"truncates NUL terminator but destination "
				"lacks %qs attribute (%wu chars into %wu "
				"available)", typ1, "nonstring", len, avail);
		}
	    }

	  ವೃಕ್ಷ_TYPE (inside_init) = type;
	  ಪ್ರತ್ಯಾಗಮ inside_init;
	}
      ಅನ್ಯಥಾ ಯದಿ (INTEGRAL_TYPE_P (typ1))
	{
	  error_init (init_loc, "array of inappropriate type initialized "
		      "from string constant");
	  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	}
    }

  /* Build a VECTOR_CST from a *constant* vector constructor.  If the
     vector constructor is not constant (e.g. {1,2,3,foo()}) then punt
     below and handle as a constructor.  */
  ಯದಿ (code == VECTOR_TYPE
      && VECTOR_TYPE_P (ವೃಕ್ಷ_TYPE (inside_init))
      && vector_types_convertible_p (ವೃಕ್ಷ_TYPE (inside_init), type, ಸತ್ಯ)
      && ವೃಕ್ಷ_CONSTANT (inside_init))
    {
      ಯದಿ (ವೃಕ್ಷ_CODE (inside_init) == VECTOR_CST
	  && comptypes (TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (inside_init)),
			TYPE_MAIN_VARIANT (type)))
	ಪ್ರತ್ಯಾಗಮ inside_init;

      ಯದಿ (ವೃಕ್ಷ_CODE (inside_init) == CONSTRUCTOR)
	{
	  unsigned HOST_WIDE_INT ix;
	  ವೃಕ್ಷ ಮೌಲ್ಯ;
	  ತಾರ್ಕಿಕ constant_p = ಸತ್ಯ;

	  /* Iterate through elements and check if all constructor
	     elements are *_CSTs.  */
	  FOR_EACH_CONSTRUCTOR_ಮೌಲ್ಯ (CONSTRUCTOR_ELTS (inside_init), ix, ಮೌಲ್ಯ)
	    ಯದಿ (!CONSTANT_CLASS_P (ಮೌಲ್ಯ))
	      {
		constant_p = ಅಸತ್ಯ;
		ಭಙ್ಗ;
	      }

	  ಯದಿ (constant_p)
	    ಪ್ರತ್ಯಾಗಮ build_vector_from_ctor (type,
					   CONSTRUCTOR_ELTS (inside_init));
	}
    }

  ಯದಿ (warn_sequence_point)
    verify_sequence_points (inside_init);

  /* Any type can be initialized
     from an expression of the same type, optionally with braces.  */

  ಯದಿ (inside_init && ವೃಕ್ಷ_TYPE (inside_init) != NULL_ವೃಕ್ಷ
      && (comptypes (TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (inside_init)),
		     TYPE_MAIN_VARIANT (type))
	  || (code == ARRAY_TYPE
	      && comptypes (ವೃಕ್ಷ_TYPE (inside_init), type))
	  || (gnu_vector_type_p (type)
	      && comptypes (ವೃಕ್ಷ_TYPE (inside_init), type))
	  || (code == POINTER_TYPE
	      && ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (inside_init)) == ARRAY_TYPE
	      && comptypes (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (inside_init)),
			    ವೃಕ್ಷ_TYPE (type)))))
    {
      ಯದಿ (code == POINTER_TYPE)
	{
	  ಯದಿ (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (inside_init)) == ARRAY_TYPE)
	    {
	      ಯದಿ (ವೃಕ್ಷ_CODE (inside_init) == STRING_CST
		  || ವೃಕ್ಷ_CODE (inside_init) == COMPOUND_LITERAL_ಅಭಿವ್ಯಕ್ತಿ)
		inside_init = array_to_pointer_conversion
		  (init_loc, inside_init);
	      ಅನ್ಯಥಾ
		{
		  error_init (init_loc, "invalid use of non-lvalue array");
		  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
		}
	    }
	}

      ಯದಿ (code == VECTOR_TYPE || c_hardbool_type_attr (type))
	/* Although the types are compatible, we may require a
	   conversion.  */
	inside_init = convert (type, inside_init);

      ಯದಿ ((code == RECORD_TYPE || code == UNION_TYPE)
	  && !comptypes (TYPE_MAIN_VARIANT (type), TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (inside_init))))
	{
	  error_init (init_loc, "invalid initializer");
	  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	}

      ಯದಿ (require_constant
	  && ವೃಕ್ಷ_CODE (inside_init) == COMPOUND_LITERAL_ಅಭಿವ್ಯಕ್ತಿ)
	{
	  /* As an extension, allow initializing objects with static storage
	     duration with compound literals (which are then treated just as
	     the brace enclosed list they contain).  Also allow this for
	     vectors, as we can only assign them with compound literals.  */
	  ಯದಿ (flag_isoc99 && code != VECTOR_TYPE)
	    pedwarn_init (init_loc, OPT_Wpedantic, "initializer element "
			  "is not constant");
	  ವೃಕ್ಷ decl = COMPOUND_LITERAL_ಅಭಿವ್ಯಕ್ತಿ_DECL (inside_init);
	  inside_init = DECL_INITIAL (decl);
	}

      ಯದಿ (code == ARRAY_TYPE && ವೃಕ್ಷ_CODE (inside_init) != STRING_CST
	  && ವೃಕ್ಷ_CODE (inside_init) != CONSTRUCTOR)
	{
	  error_init (init_loc, "array initialized from non-constant array "
		      "expression");
	  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	}

      /* Compound expressions can only occur here if -Wpedantic or
	 -pedantic-errors is specified.  In the later case, we always want
	 an error.  In the former case, we simply want a warning.  */
      ಯದಿ (require_constant && pedantic
	  && ವೃಕ್ಷ_CODE (inside_init) == COMPOUND_ಅಭಿವ್ಯಕ್ತಿ)
	{
	  inside_init
	    = valid_compound_ಅಭಿವ್ಯಕ್ತಿ_initializer (inside_init,
					       ವೃಕ್ಷ_TYPE (inside_init));
	  ಯದಿ (inside_init == error_mark_ಗಂಟು)
	    error_init (init_loc, "initializer element is not constant");
	  ಅನ್ಯಥಾ
	    pedwarn_init (init_loc, OPT_Wpedantic,
			  "initializer element is not constant");
	  ಯದಿ (flag_pedantic_errors)
	    inside_init = error_mark_ಗಂಟು;
	}
      ಅನ್ಯಥಾ ಯದಿ (require_constant
	       && !initializer_constant_valid_p (inside_init,
						 ವೃಕ್ಷ_TYPE (inside_init)))
	{
	  error_init (init_loc, "initializer element is not constant");
	  inside_init = error_mark_ಗಂಟು;
	}
      ಅನ್ಯಥಾ ಯದಿ (require_constant && !maybe_const)
	pedwarn_init (init_loc, OPT_Wpedantic,
		      "initializer element is not a constant expression");
      ಅನ್ಯಥಾ ಯದಿ (require_constexpr)
	check_constexpr_init (init_loc, type, inside_init,
			      int_const_ಅಭಿವ್ಯಕ್ತಿ, arith_const_ಅಭಿವ್ಯಕ್ತಿ);

      /* Added to enable additional -Wsuggest-attribute=format warnings.  */
      ಯದಿ (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (inside_init)) == POINTER_TYPE)
	inside_init = convert_for_assignment (init_loc, UNKNOWN_LOCATION,
					      type, inside_init, origtype,
					      (require_constant
					       ? ic_init_const
					       : ic_init), null_pointer_constant,
					      NULL_ವೃಕ್ಷ, NULL_ವೃಕ್ಷ, 0);
      ಯದಿ (ವೃಕ್ಷ_CODE (inside_init) == RAW_DATA_CST
	  && c_inhibit_evaluation_warnings == 0
	  && warn_conversion
	  && !TYPE_UNSIGNED (type)
	  && TYPE_PRECISION (type) == CHAR_BIT)
	ಪ್ರತಿ (unsigned ಪೂರ್ಣಾಙ್ಕ i = 0;
	     i < (unsigned) RAW_DATA_LENGTH (inside_init); ++i)
	  ಯದಿ (RAW_DATA_SCHAR_ELT (inside_init, i) < 0)
	    warning_at (init_loc, OPT_Wconversion,
			"conversion from %qT to %qT changes value from "
			"%qd to %qd",
			integer_type_ಗಂಟು, type,
			RAW_DATA_UCHAR_ELT (inside_init, i),
			RAW_DATA_SCHAR_ELT (inside_init, i));
      ಪ್ರತ್ಯಾಗಮ inside_init;
    }

  /* Handle scalar types, including conversions.  */

  ಯದಿ (code == INTEGER_TYPE || code == REAL_TYPE || code == FIXED_POINT_TYPE
      || code == POINTER_TYPE || code == ENUMERAL_TYPE || code == BOOLEAN_TYPE
      || code == COMPLEX_TYPE || code == VECTOR_TYPE || code == NULLPTR_TYPE
      || code == BITINT_TYPE)
    {
      ವೃಕ್ಷ unconverted_init = inside_init;
      ಯದಿ (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (init)) == ARRAY_TYPE
	  && (ವೃಕ್ಷ_CODE (init) == STRING_CST
	      || ವೃಕ್ಷ_CODE (init) == COMPOUND_LITERAL_ಅಭಿವ್ಯಕ್ತಿ))
	inside_init = init = array_to_pointer_conversion (init_loc, init);
      ಯದಿ (semantic_type)
	inside_init = build1 (EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ, semantic_type,
			      inside_init);
      inside_init
	= convert_for_assignment (init_loc, UNKNOWN_LOCATION, type,
				  inside_init, origtype,
				  require_constant ? ic_init_const : ic_init,
				  null_pointer_constant, NULL_ವೃಕ್ಷ, NULL_ವೃಕ್ಷ,
				  0);

      /* Check to see if we have already given an error message.  */
      ಯದಿ (inside_init == error_mark_ಗಂಟು)
	;
      ಅನ್ಯಥಾ ಯದಿ (require_constant && !ವೃಕ್ಷ_CONSTANT (inside_init))
	{
	  error_init (init_loc, "initializer element is not constant");
	  inside_init = error_mark_ಗಂಟು;
	}
      ಅನ್ಯಥಾ ಯದಿ (require_constant
	       && !initializer_constant_valid_p (inside_init,
						 ವೃಕ್ಷ_TYPE (inside_init)))
	{
	  error_init (init_loc, "initializer element is not computable at "
		      "load time");
	  inside_init = error_mark_ಗಂಟು;
	}
      ಅನ್ಯಥಾ ಯದಿ (require_constant && !maybe_const)
	pedwarn_init (init_loc, OPT_Wpedantic,
		      "initializer element is not a constant expression");
      ಅನ್ಯಥಾ ಯದಿ (require_constexpr)
	check_constexpr_init (init_loc, type, unconverted_init,
			      int_const_ಅಭಿವ್ಯಕ್ತಿ, arith_const_ಅಭಿವ್ಯಕ್ತಿ);

      ಪ್ರತ್ಯಾಗಮ inside_init;
    }

  /* Come here only for records and arrays.  */

  ಯದಿ (COMPLETE_TYPE_P (type) && ವೃಕ್ಷ_CODE (TYPE_SIZE (type)) != INTEGER_CST)
    {
      error_init (init_loc,
		  "variable-sized object may not be initialized except "
		  "with an empty initializer");
      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
    }

  error_init (init_loc, "invalid initializer");
  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
}

/* Handle initializers that use braces.  */

/* Type of object we are accumulating a constructor for.
   This type is always a RECORD_TYPE, UNION_TYPE or ARRAY_TYPE.  */
ಸ್ಥಿರ ವೃಕ್ಷ constructor_type;

/* For a RECORD_TYPE or UNION_TYPE, this is the chain of fields
   left to fill.  */
ಸ್ಥಿರ ವೃಕ್ಷ constructor_fields;

/* For an ARRAY_TYPE, this is the specified index
   at which to store the next element we get.  */
ಸ್ಥಿರ ವೃಕ್ಷ constructor_index;

/* For an ARRAY_TYPE, this is the maximum index.  */
ಸ್ಥಿರ ವೃಕ್ಷ constructor_max_index;

/* For a RECORD_TYPE, this is the first field not yet written out.  */
ಸ್ಥಿರ ವೃಕ್ಷ constructor_unfilled_fields;

/* For an ARRAY_TYPE, this is the index of the first element
   not yet written out.  */
ಸ್ಥಿರ ವೃಕ್ಷ constructor_unfilled_index;

/* In a RECORD_TYPE, the byte index of the next consecutive field.
   This is so we can generate gaps between fields, when appropriate.  */
ಸ್ಥಿರ ವೃಕ್ಷ constructor_bit_index;

/* If we are saving up the elements rather than allocating them,
   this is the list of elements so far (in reverse order,
   most recent first).  */
ಸ್ಥಿರ vec<constructor_elt, va_gc> *constructor_elements;

/* 1 if constructor should be incrementally stored into a constructor chain,
   0 if all the elements should be kept in AVL tree.  */
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ constructor_incremental;

/* 1 if so far this constructor's elements are all compile-time constants.  */
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ constructor_constant;

/* 1 if so far this constructor's elements are all valid address constants.  */
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ constructor_simple;

/* 1 if this constructor has an element that cannot be part of a
   constant expression.  */
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ constructor_nonconst;

/* 1 if this constructor is erroneous so far.  */
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ constructor_erroneous;

/* 1 if this constructor is the universal zero initializer { 0 }.  */
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ constructor_zeroinit;

/* 1 if this constructor should have padding bits zeroed (C23 {}.  */
ಸ್ಥಿರ ತಾರ್ಕಿಕ constructor_zero_padding_bits;

/* 1 if this constructor is a braced scalar initializer (further nested levels
   of braces are an error).  */
ಸ್ಥಿರ ತಾರ್ಕಿಕ constructor_braced_scalar;

/* Structure for managing pending initializer elements, organized as an
   AVL tree.  */

ಸಂರಚನಾ init_ಗಂಟು
{
  ಸಂರಚನಾ init_ಗಂಟು *ಎಡ, *ಬಲ;
  ಸಂರಚನಾ init_ಗಂಟು *parent;
  ಪೂರ್ಣಾಙ್ಕ balance;
  ವೃಕ್ಷ purpose;
  ವೃಕ್ಷ ಮೌಲ್ಯ;
  ವೃಕ್ಷ origtype;
};

/* Tree of pending elements at this constructor level.
   These are elements encountered out of order
   which belong at places we haven't reached yet in actually
   writing the output.
   Will never hold tree nodes across GC runs.  */
ಸ್ಥಿರ ಸಂರಚನಾ init_ಗಂಟು *constructor_pending_elts;

/* The SPELLING_DEPTH of this constructor.  */
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ constructor_depth;

/* DECL node for which an initializer is being read.
   0 means we are reading a constructor expression
   such as (struct foo) {...}.  */
ಸ್ಥಿರ ವೃಕ್ಷ constructor_decl;

/* Nonzero if there were any member designators in this initializer.  */
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ constructor_designated;

/* Nesting depth of designator list.  */
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ designator_depth;

/* Nonzero if there were diagnosed errors in this designator list.  */
ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ designator_erroneous;


/* This stack has a level for each implicit or explicit level of
   structuring in the initializer, including the outermost one.  It
   saves the values of most of the variables above.  */

ಸಂರಚನಾ constructor_range_ರಾಶಿ;

ಸಂರಚನಾ constructor_ರಾಶಿ
{
  ಸಂರಚನಾ constructor_ರಾಶಿ *next;
  ವೃಕ್ಷ type;
  ವೃಕ್ಷ fields;
  ವೃಕ್ಷ index;
  ವೃಕ್ಷ max_index;
  ವೃಕ್ಷ unfilled_index;
  ವೃಕ್ಷ unfilled_fields;
  ವೃಕ್ಷ bit_index;
  vec<constructor_elt, va_gc> *elements;
  ಸಂರಚನಾ init_ಗಂಟು *pending_elts;
  ಪೂರ್ಣಾಙ್ಕ offset;
  ಪೂರ್ಣಾಙ್ಕ depth;
  /* If value nonzero, this value should replace the entire
     constructor at this level.  */
  ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ replacement_ಮೌಲ್ಯ;
  ಸಂರಚನಾ constructor_range_ರಾಶಿ *range_ರಾಶಿ;
  ವರ್ಣ constant;
  ವರ್ಣ simple;
  ವರ್ಣ nonconst;
  ವರ್ಣ implicit;
  ವರ್ಣ erroneous;
  ವರ್ಣ outer;
  ವರ್ಣ incremental;
  ವರ್ಣ designated;
  ತಾರ್ಕಿಕ zero_padding_bits;
  ತಾರ್ಕಿಕ braced_scalar;
  ಪೂರ್ಣಾಙ್ಕ designator_depth;
};

ಸ್ಥಿರ ಸಂರಚನಾ constructor_ರಾಶಿ *constructor_ರಾಶಿ;

/* This stack represents designators from some range designator up to
   the last designator in the list.  */

ಸಂರಚನಾ constructor_range_ರಾಶಿ
{
  ಸಂರಚನಾ constructor_range_ರಾಶಿ *next, *prev;
  ಸಂರಚನಾ constructor_ರಾಶಿ *ರಾಶಿ;
  ವೃಕ್ಷ range_start;
  ವೃಕ್ಷ index;
  ವೃಕ್ಷ range_end;
  ವೃಕ್ಷ fields;
};

ಸ್ಥಿರ ಸಂರಚನಾ constructor_range_ರಾಶಿ *constructor_range_ರಾಶಿ;

/* This stack records separate initializers that are nested.
   Nested initializers can't happen in ANSI C, but GNU C allows them
   in cases like { ... (struct foo) { ... } ... }.  */

ಸಂರಚನಾ initializer_ರಾಶಿ
{
  ಸಂರಚನಾ initializer_ರಾಶಿ *next;
  ವೃಕ್ಷ decl;
  ಸಂರಚನಾ constructor_ರಾಶಿ *constructor_ರಾಶಿ;
  ಸಂರಚನಾ constructor_range_ರಾಶಿ *constructor_range_ರಾಶಿ;
  vec<constructor_elt, va_gc> *elements;
  ಸಂರಚನಾ spelling *spelling;
  ಸಂರಚನಾ spelling *spelling_base;
  ಪೂರ್ಣಾಙ್ಕ spelling_size;
  ವರ್ಣ require_constant_ಮೌಲ್ಯ;
  ವರ್ಣ require_constant_elements;
  ವರ್ಣ require_constexpr_ಮೌಲ್ಯ;
  ವರ್ಣ designated;
  rich_location *missing_brace_richloc;
};

ಸ್ಥಿರ ಸಂರಚನಾ initializer_ರಾಶಿ *initializer_ರಾಶಿ;

/* Prepare to parse and output the initializer for variable DECL.  */

ಶೂನ್ಯ
start_init (ವೃಕ್ಷ decl, ವೃಕ್ಷ asmspec_ವೃಕ್ಷ ATTRIBUTE_UNUSED,
	    ತಾರ್ಕಿಕ init_require_constant, ತಾರ್ಕಿಕ init_require_constexpr,
	    rich_location *richloc)
{
  ಧ್ರುವ ವರ್ಣ *locus;
  ಸಂರಚನಾ initializer_ರಾಶಿ *p = XNEW (ಸಂರಚನಾ initializer_ರಾಶಿ);

  p->decl = constructor_decl;
  p->require_constant_ಮೌಲ್ಯ = require_constant_ಮೌಲ್ಯ;
  p->require_constant_elements = require_constant_elements;
  p->require_constexpr_ಮೌಲ್ಯ = require_constexpr_ಮೌಲ್ಯ;
  p->constructor_ರಾಶಿ = constructor_ರಾಶಿ;
  p->constructor_range_ರಾಶಿ = constructor_range_ರಾಶಿ;
  p->elements = constructor_elements;
  p->spelling = spelling;
  p->spelling_base = spelling_base;
  p->spelling_size = spelling_size;
  p->next = initializer_ರಾಶಿ;
  p->missing_brace_richloc = richloc;
  p->designated = constructor_designated;
  initializer_ರಾಶಿ = p;

  constructor_decl = decl;
  constructor_designated = 0;

  require_constant_ಮೌಲ್ಯ = init_require_constant;
  require_constexpr_ಮೌಲ್ಯ = init_require_constexpr;
  ಯದಿ (decl != NULL_ವೃಕ್ಷ && decl != error_mark_ಗಂಟು)
    {
      require_constant_elements
	= ((init_require_constant || (pedantic && !flag_isoc99))
	   /* For a scalar, you can always use any value to initialize,
	      even within braces.  */
	   && AGGREGATE_TYPE_P (ವೃಕ್ಷ_TYPE (decl)));
      locus = identifier_to_locale (IDENTIFIER_POINTER (DECL_NAME (decl)));
    }
  ಅನ್ಯಥಾ
    {
      require_constant_elements = ಅಸತ್ಯ;
      locus = _("(anonymous)");
    }

  constructor_ರಾಶಿ = 0;
  constructor_range_ರಾಶಿ = 0;

  found_missing_braces = 0;

  spelling_base = 0;
  spelling_size = 0;
  RESTORE_SPELLING_DEPTH (0);

  ಯದಿ (locus)
    ತಳ್ಳು_string (locus);
}

ಶೂನ್ಯ
finish_init (ಶೂನ್ಯ)
{
  ಸಂರಚನಾ initializer_ರಾಶಿ *p = initializer_ರಾಶಿ;

  /* Free the whole constructor stack of this initializer.  */
  ಯಾವತ್ (constructor_ರಾಶಿ)
    {
      ಸಂರಚನಾ constructor_ರಾಶಿ *q = constructor_ರಾಶಿ;
      constructor_ರಾಶಿ = q->next;
      XDELETE (q);
    }

  gcc_assert (!constructor_range_ರಾಶಿ);

  /* Pop back to the data of the outer initializer (if any).  */
  XDELETE (spelling_base);

  constructor_decl = p->decl;
  require_constant_ಮೌಲ್ಯ = p->require_constant_ಮೌಲ್ಯ;
  require_constant_elements = p->require_constant_elements;
  require_constexpr_ಮೌಲ್ಯ = p->require_constexpr_ಮೌಲ್ಯ;
  constructor_ರಾಶಿ = p->constructor_ರಾಶಿ;
  constructor_designated = p->designated;
  constructor_range_ರಾಶಿ = p->constructor_range_ರಾಶಿ;
  constructor_elements = p->elements;
  spelling = p->spelling;
  spelling_base = p->spelling_base;
  spelling_size = p->spelling_size;
  initializer_ರಾಶಿ = p->next;
  XDELETE (p);
}

/* Call here when we see the initializer is surrounded by braces.
   This is instead of a call to push_init_level;
   it is matched by a call to pop_init_level.

   TYPE is the type to initialize, for a constructor expression.
   For an initializer for a decl, TYPE is zero.  */

ಶೂನ್ಯ
really_start_incremental_init (ವೃಕ್ಷ type)
{
  ಸಂರಚನಾ constructor_ರಾಶಿ *p = XNEW (ಸಂರಚನಾ constructor_ರಾಶಿ);

  ಯದಿ (type == NULL_ವೃಕ್ಷ)
    type = ವೃಕ್ಷ_TYPE (constructor_decl);

  ಯದಿ (VECTOR_TYPE_P (type)
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
  p->replacement_ಮೌಲ್ಯ.ಮೌಲ್ಯ = 0;
  p->replacement_ಮೌಲ್ಯ.original_code = ERROR_MARK;
  p->replacement_ಮೌಲ್ಯ.original_type = ರಿಕ್ತ;
  p->implicit = 0;
  p->range_ರಾಶಿ = 0;
  p->outer = 0;
  p->incremental = constructor_incremental;
  p->designated = constructor_designated;
  p->zero_padding_bits = constructor_zero_padding_bits;
  p->braced_scalar = constructor_braced_scalar;
  p->designator_depth = designator_depth;
  p->next = 0;
  constructor_ರಾಶಿ = p;

  constructor_constant = 1;
  constructor_simple = 1;
  constructor_nonconst = 0;
  constructor_depth = SPELLING_DEPTH ();
  constructor_elements = ರಿಕ್ತ;
  constructor_pending_elts = 0;
  constructor_type = type;
  constructor_incremental = 1;
  constructor_designated = 0;
  constructor_zero_padding_bits = ಅಸತ್ಯ;
  constructor_zeroinit = 1;
  constructor_braced_scalar = ಅಸತ್ಯ;
  designator_depth = 0;
  designator_erroneous = 0;

  ಯದಿ (RECORD_OR_UNION_TYPE_P (constructor_type))
    {
      constructor_fields = TYPE_FIELDS (constructor_type);
      /* Skip any nameless bit fields at the beginning.  */
      ಯಾವತ್ (constructor_fields != NULL_ವೃಕ್ಷ
	     && DECL_UNNAMED_BIT_FIELD (constructor_fields))
	constructor_fields = DECL_CHAIN (constructor_fields);

      constructor_unfilled_fields = constructor_fields;
      constructor_bit_index = bitsize_zero_ಗಂಟು;
    }
  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (constructor_type) == ARRAY_TYPE)
    {
      ಯದಿ (TYPE_DOMAIN (constructor_type))
	{
	  constructor_max_index
	    = TYPE_MAX_ಮೌಲ್ಯ (TYPE_DOMAIN (constructor_type));

	  /* Detect non-empty initializations of zero-length arrays.  */
	  ಯದಿ (constructor_max_index == NULL_ವೃಕ್ಷ
	      && TYPE_SIZE (constructor_type))
	    constructor_max_index = integer_minus_one_ಗಂಟು;

	  /* constructor_max_index needs to be an INTEGER_CST.  Attempts
	     to initialize VLAs with a nonempty initializer will cause a
	     proper error; avoid tree checking errors as well by setting a
	     safe value.  */
	  ಯದಿ (constructor_max_index
	      && ವೃಕ್ಷ_CODE (constructor_max_index) != INTEGER_CST)
	    constructor_max_index = integer_minus_one_ಗಂಟು;

	  constructor_index
	    = convert (bitsizetype,
		       TYPE_MIN_ಮೌಲ್ಯ (TYPE_DOMAIN (constructor_type)));
	}
      ಅನ್ಯಥಾ
	{
	  constructor_index = bitsize_zero_ಗಂಟು;
	  constructor_max_index = NULL_ವೃಕ್ಷ;
	}

      constructor_unfilled_index = constructor_index;
    }
  ಅನ್ಯಥಾ ಯದಿ (gnu_vector_type_p (constructor_type))
    {
      /* Vectors are like simple fixed-size arrays.  */
      constructor_max_index =
	bitsize_int (TYPE_VECTOR_SUBPARTS (constructor_type) - 1);
      constructor_index = bitsize_zero_ಗಂಟು;
      constructor_unfilled_index = constructor_index;
    }
  ಅನ್ಯಥಾ
    {
      /* Handle the case of int x = {5}; */
      constructor_fields = constructor_type;
      constructor_unfilled_fields = constructor_type;
      constructor_braced_scalar = ಸತ್ಯ;
    }
}

ಬಾಹ್ಯ location_t last_init_list_comma;

/* Called when we see an open brace for a nested initializer.  Finish
   off any pending levels with implicit braces.  */
ಶೂನ್ಯ
finish_implicit_inits (location_t loc, ಸಂರಚನಾ obstack *braced_init_obstack)
{
  ಯಾವತ್ (constructor_ರಾಶಿ->implicit)
    {
      ಯದಿ (RECORD_OR_UNION_TYPE_P (constructor_type)
	  && constructor_fields == NULL_ವೃಕ್ಷ)
	process_init_element (ಒಳಹರಿವು_location,
			      ತೆಗೆ_init_level (loc, 1, braced_init_obstack,
					      last_init_list_comma),
			      ಸತ್ಯ, braced_init_obstack);
      ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (constructor_type) == ARRAY_TYPE
	       && constructor_max_index
	       && ವೃಕ್ಷ_int_cst_lt (constructor_max_index,
				   constructor_index))
	process_init_element (ಒಳಹರಿವು_location,
			      ತೆಗೆ_init_level (loc, 1, braced_init_obstack,
					      last_init_list_comma),
			      ಸತ್ಯ, braced_init_obstack);
      ಅನ್ಯಥಾ
	ಭಙ್ಗ;
    }
}

/* Push down into a subobject, for initialization.
   If this is for an explicit set of braces, IMPLICIT is 0.
   If it is because the next element belongs at a lower level,
   IMPLICIT is 1 (or 2 if the push is because of designator list).  */

ಶೂನ್ಯ
ತಳ್ಳು_init_level (location_t loc, ಪೂರ್ಣಾಙ್ಕ implicit,
		 ಸಂರಚನಾ obstack *braced_init_obstack)
{
  ಸಂರಚನಾ constructor_ರಾಶಿ *p;
  ವೃಕ್ಷ ಮೌಲ್ಯ = NULL_ವೃಕ್ಷ;

  /* Unless this is an explicit brace, we need to preserve previous
     content if any.  */
  ಯದಿ (implicit)
    {
      ಯದಿ (RECORD_OR_UNION_TYPE_P (constructor_type) && constructor_fields)
	ಮೌಲ್ಯ = find_init_member (constructor_fields, braced_init_obstack);
      ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (constructor_type) == ARRAY_TYPE)
	ಮೌಲ್ಯ = find_init_member (constructor_index, braced_init_obstack);
    }

  p = XNEW (ಸಂರಚನಾ constructor_ರಾಶಿ);
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
  p->replacement_ಮೌಲ್ಯ.ಮೌಲ್ಯ = NULL_ವೃಕ್ಷ;
  p->replacement_ಮೌಲ್ಯ.original_code = ERROR_MARK;
  p->replacement_ಮೌಲ್ಯ.original_type = ರಿಕ್ತ;
  p->implicit = implicit;
  p->outer = 0;
  p->incremental = constructor_incremental;
  p->designated = constructor_designated;
  p->zero_padding_bits = constructor_zero_padding_bits;
  p->braced_scalar = constructor_braced_scalar;
  p->designator_depth = designator_depth;
  p->next = constructor_ರಾಶಿ;
  p->range_ರಾಶಿ = 0;
  constructor_ರಾಶಿ = p;

  constructor_constant = 1;
  constructor_simple = 1;
  constructor_nonconst = 0;
  constructor_depth = SPELLING_DEPTH ();
  constructor_elements = ರಿಕ್ತ;
  constructor_incremental = 1;
  /* If the upper initializer is designated, then mark this as
     designated too to prevent bogus warnings.  */
  constructor_designated = p->designated;
  /* If the upper initializer has padding bits zeroed, that includes
     all nested initializers as well.  */
  constructor_zero_padding_bits = p->zero_padding_bits;
  constructor_braced_scalar = ಅಸತ್ಯ;
  constructor_pending_elts = 0;
  ಯದಿ (!implicit)
    {
      p->range_ರಾಶಿ = constructor_range_ರಾಶಿ;
      constructor_range_ರಾಶಿ = 0;
      designator_depth = 0;
      designator_erroneous = 0;
    }

  /* Don't die if an entire brace-pair level is superfluous
     in the containing level.  */
  ಯದಿ (constructor_type == NULL_ವೃಕ್ಷ)
    ;
  ಅನ್ಯಥಾ ಯದಿ (RECORD_OR_UNION_TYPE_P (constructor_type))
    {
      /* Don't die if there are extra init elts at the end.  */
      ಯದಿ (constructor_fields == NULL_ವೃಕ್ಷ)
	constructor_type = NULL_ವೃಕ್ಷ;
      ಅನ್ಯಥಾ
	{
	  constructor_type = ವೃಕ್ಷ_TYPE (constructor_fields);
	  ತಳ್ಳು_member_name (constructor_fields);
	  constructor_depth++;
	}
    }
  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (constructor_type) == ARRAY_TYPE)
    {
      constructor_type = ವೃಕ್ಷ_TYPE (constructor_type);
      ತಳ್ಳು_array_bounds (ವೃಕ್ಷ_to_uhwi (constructor_index));
      constructor_depth++;
    }

  ಯದಿ (constructor_type == NULL_ವೃಕ್ಷ)
    {
      error_init (loc, "extra brace group at end of initializer");
      constructor_fields = NULL_ವೃಕ್ಷ;
      constructor_unfilled_fields = NULL_ವೃಕ್ಷ;
      ಪ್ರತ್ಯಾಗಮ;
    }

  ಯದಿ (ಮೌಲ್ಯ && ವೃಕ್ಷ_CODE (ಮೌಲ್ಯ) == CONSTRUCTOR)
    {
      constructor_constant = ವೃಕ್ಷ_CONSTANT (ಮೌಲ್ಯ);
      constructor_simple = ವೃಕ್ಷ_STATIC (ಮೌಲ್ಯ);
      constructor_nonconst = CONSTRUCTOR_NON_CONST (ಮೌಲ್ಯ);
      constructor_elements = CONSTRUCTOR_ELTS (ಮೌಲ್ಯ);
      constructor_zero_padding_bits |= CONSTRUCTOR_ZERO_PADDING_BITS (ಮೌಲ್ಯ);
      ಯದಿ (!vec_safe_is_empty (constructor_elements)
	  && (ವೃಕ್ಷ_CODE (constructor_type) == RECORD_TYPE
	      || ವೃಕ್ಷ_CODE (constructor_type) == ARRAY_TYPE))
	set_nonincremental_init (braced_init_obstack);
    }

  ಯದಿ (implicit == 1)
    {
      found_missing_braces = 1;
      ಯದಿ (initializer_ರಾಶಿ->missing_brace_richloc)
	initializer_ರಾಶಿ->missing_brace_richloc->add_fixit_ಸೇರಿಸು_before
	  (loc, "{");
    }

  ಯದಿ (RECORD_OR_UNION_TYPE_P (constructor_type))
    {
      constructor_fields = TYPE_FIELDS (constructor_type);
      /* Skip any nameless bit fields at the beginning.  */
      ಯಾವತ್ (constructor_fields != NULL_ವೃಕ್ಷ
	     && DECL_UNNAMED_BIT_FIELD (constructor_fields))
	constructor_fields = DECL_CHAIN (constructor_fields);

      constructor_unfilled_fields = constructor_fields;
      constructor_bit_index = bitsize_zero_ಗಂಟು;
    }
  ಅನ್ಯಥಾ ಯದಿ (gnu_vector_type_p (constructor_type))
    {
      /* Vectors are like simple fixed-size arrays.  */
      constructor_max_index =
	bitsize_int (TYPE_VECTOR_SUBPARTS (constructor_type) - 1);
      constructor_index = bitsize_int (0);
      constructor_unfilled_index = constructor_index;
    }
  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (constructor_type) == ARRAY_TYPE)
    {
      ಯದಿ (TYPE_DOMAIN (constructor_type))
	{
	  constructor_max_index
	    = TYPE_MAX_ಮೌಲ್ಯ (TYPE_DOMAIN (constructor_type));

	  /* Detect non-empty initializations of zero-length arrays.  */
	  ಯದಿ (constructor_max_index == NULL_ವೃಕ್ಷ
	      && TYPE_SIZE (constructor_type))
	    constructor_max_index = integer_minus_one_ಗಂಟು;

	  /* constructor_max_index needs to be an INTEGER_CST.  Attempts
	     to initialize VLAs will cause a proper error; avoid tree
	     checking errors as well by setting a safe value.  */
	  ಯದಿ (constructor_max_index
	      && ವೃಕ್ಷ_CODE (constructor_max_index) != INTEGER_CST)
	    constructor_max_index = integer_minus_one_ಗಂಟು;

	  constructor_index
	    = convert (bitsizetype,
		       TYPE_MIN_ಮೌಲ್ಯ (TYPE_DOMAIN (constructor_type)));
	}
      ಅನ್ಯಥಾ
	constructor_index = bitsize_zero_ಗಂಟು;

      constructor_unfilled_index = constructor_index;
      ಯದಿ (ಮೌಲ್ಯ && ವೃಕ್ಷ_CODE (ಮೌಲ್ಯ) == STRING_CST)
	{
	  /* We need to split the char/wchar array into individual
	     characters, so that we don't have to special case it
	     everywhere.  */
	  set_nonincremental_init_from_string (ಮೌಲ್ಯ, braced_init_obstack);
	}
    }
  ಅನ್ಯಥಾ
    {
      ಯದಿ (constructor_type != error_mark_ಗಂಟು)
	{
	  ಯದಿ (p->braced_scalar)
	    permerror_init (ಒಳಹರಿವು_location, 0,
			    "braces around scalar initializer");
	  ಅನ್ಯಥಾ
	    warning_init (ಒಳಹರಿವು_location, 0,
			  "braces around scalar initializer");
	  constructor_braced_scalar = ಸತ್ಯ;
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

ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ
ತೆಗೆ_init_level (location_t loc, ಪೂರ್ಣಾಙ್ಕ implicit,
		ಸಂರಚನಾ obstack *braced_init_obstack,
		location_t ಸೇರಿಸು_before)
{
  ಸಂರಚನಾ constructor_ರಾಶಿ *p;
  ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ ret;
  ret.ಮೌಲ್ಯ = NULL_ವೃಕ್ಷ;
  ret.original_code = ERROR_MARK;
  ret.original_type = ರಿಕ್ತ;
  ret.m_decimal = 0;

  ಯದಿ (implicit == 0)
    {
      /* When we come to an explicit close brace,
	 pop any inner levels that didn't have explicit braces.  */
      ಯಾವತ್ (constructor_ರಾಶಿ->implicit)
	process_init_element (ಒಳಹರಿವು_location,
			      ತೆಗೆ_init_level (loc, 1, braced_init_obstack,
					      ಸೇರಿಸು_before),
			      ಸತ್ಯ, braced_init_obstack);
      gcc_assert (!constructor_range_ರಾಶಿ);
    }
  ಅನ್ಯಥಾ
    ಯದಿ (initializer_ರಾಶಿ->missing_brace_richloc)
      initializer_ರಾಶಿ->missing_brace_richloc->add_fixit_ಸೇರಿಸು_before
	(ಸೇರಿಸು_before, "}");

  /* Now output all pending elements.  */
  constructor_incremental = 1;
  output_pending_init_elements (1, braced_init_obstack);

  p = constructor_ರಾಶಿ;

  /* Error for initializing a flexible array member.  */
  ಯದಿ (constructor_type && constructor_fields
      && flexible_array_member_type_p (constructor_type))
    {
      /* Silently discard empty initializations.  The parser will
	 already have pedwarned for empty brackets for C17 and earlier.  */
      ಯದಿ (integer_zerop (constructor_unfilled_index))
	constructor_type = NULL_ವೃಕ್ಷ;
      ಯದಿ (constructor_type || flag_isoc23)
	{
	  gcc_assert (!constructor_type || !TYPE_SIZE (constructor_type));

	  ಯದಿ (constructor_depth <= 2)
	    pedwarn_init (loc, OPT_Wpedantic,
			  "initialization of a flexible array member");
	  ಅನ್ಯಥಾ ಯದಿ (constructor_type)
	    error_init (loc, "initialization of flexible array member "
			     "in a nested context");
	  ಅನ್ಯಥಾ
	    pedwarn_init (loc, OPT_Wpedantic,
			  "initialization of flexible array member "
			  "in a nested context");

	  /* We have already issued an error message for the existence
	     of a flexible array member not at the end of the structure.
	     Discard the initializer so that we do not die later.  */
	  ಯದಿ (constructor_type
	      && DECL_CHAIN (constructor_fields) != NULL_ವೃಕ್ಷ
	      && (!p->type || ವೃಕ್ಷ_CODE (p->type) != UNION_TYPE))
	    constructor_type = NULL_ವೃಕ್ಷ;
	}
    }

  ವಿಕಲ್ಪ (vec_safe_length (constructor_elements))
    {
    ಪಕ್ಷ 0:
      /* Initialization with { } counts as zeroinit.  */
      constructor_zeroinit = 1;
      ಭಙ್ಗ;
    ಪಕ್ಷ 1:
      /* This might be zeroinit as well.  */
      ಯದಿ (integer_zerop ((*constructor_elements)[0].ಮೌಲ್ಯ))
	constructor_zeroinit = 1;
      ಭಙ್ಗ;
    ಸ್ವಭಾವ:
      /* If the constructor has more than one element, it can't be { 0 }.  */
      constructor_zeroinit = 0;
      ಭಙ್ಗ;
    }

  /* Warn when some structs are initialized with direct aggregation.  */
  ಯದಿ (!implicit && found_missing_braces && warn_missing_braces
      && !constructor_zeroinit)
    {
      gcc_assert (initializer_ರಾಶಿ->missing_brace_richloc);
      warning_at (initializer_ರಾಶಿ->missing_brace_richloc,
		  OPT_Wmissing_braces,
		  "missing braces around initializer");
    }

  /* Warn when some struct elements are implicitly initialized to zero.  */
  ಯದಿ (warn_missing_field_initializers
      && constructor_type
      && ವೃಕ್ಷ_CODE (constructor_type) == RECORD_TYPE
      && constructor_unfilled_fields)
    {
	/* Do not warn for flexible array members or zero-length arrays.  */
	ಯಾವತ್ (constructor_unfilled_fields
	       && (!DECL_SIZE (constructor_unfilled_fields)
		   || integer_zerop (DECL_SIZE (constructor_unfilled_fields))))
	  constructor_unfilled_fields = DECL_CHAIN (constructor_unfilled_fields);

	ಯದಿ (constructor_unfilled_fields
	    /* Do not warn if this level of the initializer uses member
	       designators; it is likely to be deliberate.  */
	    && !constructor_designated
	    /* Do not warn about initializing with { 0 } or with { }.  */
	    && !constructor_zeroinit)
	  {
	    ಯದಿ (warning_at (ಒಳಹರಿವು_location, OPT_Wmissing_field_initializers,
			    "missing initializer for field %qD of %qT",
			    constructor_unfilled_fields,
			    constructor_type))
	      inform (DECL_SOURCE_LOCATION (constructor_unfilled_fields),
		      "%qD declared here", constructor_unfilled_fields);
	  }
    }

  /* Pad out the end of the structure.  */
  ಯದಿ (p->replacement_ಮೌಲ್ಯ.ಮೌಲ್ಯ)
    /* If this closes a superfluous brace pair,
       just pass out the element between them.  */
    ret = p->replacement_ಮೌಲ್ಯ;
  ಅನ್ಯಥಾ ಯದಿ (constructor_type == NULL_ವೃಕ್ಷ)
    ;
  ಅನ್ಯಥಾ ಯದಿ (!RECORD_OR_UNION_TYPE_P (constructor_type)
	   && ವೃಕ್ಷ_CODE (constructor_type) != ARRAY_TYPE
	   && !gnu_vector_type_p (constructor_type))
    {
      /* A nonincremental scalar initializer--just return
	 the element, after verifying there is just one.
         Empty scalar initializers are supported in C23.  */
      ಯದಿ (vec_safe_is_empty (constructor_elements))
	{
	  ಯದಿ (constructor_erroneous || constructor_type == error_mark_ಗಂಟು)
	    ret.ಮೌಲ್ಯ = error_mark_ಗಂಟು;
	  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (constructor_type) == FUNCTION_TYPE)
	    {
	      error_init (loc, "invalid initializer");
	      ret.ಮೌಲ್ಯ = error_mark_ಗಂಟು;
	    }
	  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (constructor_type) == POINTER_TYPE)
	    /* Ensure this is a null pointer constant in the case of a
	       'constexpr' object initialized with {}.  */
	    ret.ಮೌಲ್ಯ = build_zero_cst (ptr_type_ಗಂಟು);
	  ಅನ್ಯಥಾ
	    ret.ಮೌಲ್ಯ = build_zero_cst (constructor_type);
	}
      ಅನ್ಯಥಾ ಯದಿ (vec_safe_length (constructor_elements) != 1)
	{
	  error_init (loc, "extra elements in scalar initializer");
	  ret.ಮೌಲ್ಯ = (*constructor_elements)[0].ಮೌಲ್ಯ;
	}
      ಅನ್ಯಥಾ
	ret.ಮೌಲ್ಯ = (*constructor_elements)[0].ಮೌಲ್ಯ;
    }
  ಅನ್ಯಥಾ
    {
      ಯದಿ (constructor_erroneous)
	ret.ಮೌಲ್ಯ = error_mark_ಗಂಟು;
      ಅನ್ಯಥಾ
	{
	  ret.ಮೌಲ್ಯ = build_constructor (constructor_type,
					 constructor_elements);
	  ಯದಿ (constructor_constant)
	    ವೃಕ್ಷ_CONSTANT (ret.ಮೌಲ್ಯ) = 1;
	  ಯದಿ (constructor_constant && constructor_simple)
	    ವೃಕ್ಷ_STATIC (ret.ಮೌಲ್ಯ) = 1;
	  ಯದಿ (constructor_nonconst)
	    CONSTRUCTOR_NON_CONST (ret.ಮೌಲ್ಯ) = 1;
	  ಯದಿ (constructor_zero_padding_bits)
	    CONSTRUCTOR_ZERO_PADDING_BITS (ret.ಮೌಲ್ಯ) = 1;
	}
    }

  ಯದಿ (ret.ಮೌಲ್ಯ && ವೃಕ್ಷ_CODE (ret.ಮೌಲ್ಯ) != CONSTRUCTOR)
    {
      ಯದಿ (constructor_nonconst)
	ret.original_code = C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ;
      ಅನ್ಯಥಾ ಯದಿ (ret.original_code == C_MAYBE_CONST_ಅಭಿವ್ಯಕ್ತಿ)
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
  ಯದಿ (!p->implicit)
    constructor_range_ರಾಶಿ = p->range_ರಾಶಿ;
  RESTORE_SPELLING_DEPTH (constructor_depth);

  constructor_ರಾಶಿ = p->next;
  XDELETE (p);

  ಯದಿ (ret.ಮೌಲ್ಯ == NULL_ವೃಕ್ಷ && constructor_ರಾಶಿ == 0)
    ret.ಮೌಲ್ಯ = error_mark_ಗಂಟು;
  ಪ್ರತ್ಯಾಗಮ ret;
}

/* Common handling for both array range and field name designators.
   ARRAY argument is nonzero for array ranges.  Returns false for success.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
set_designator (location_t loc, ತಾರ್ಕಿಕ array,
		ಸಂರಚನಾ obstack *braced_init_obstack)
{
  ವೃಕ್ಷ subtype;
  ಗಣನಾ ವೃಕ್ಷ_code subcode;

  /* Don't die if an entire brace-pair level is superfluous
     in the containing level, or for an erroneous type.  */
  ಯದಿ (constructor_type == NULL_ವೃಕ್ಷ || constructor_type == error_mark_ಗಂಟು)
    ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;

  /* If there were errors in this designator list already, bail out
     silently.  */
  ಯದಿ (designator_erroneous)
    ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;

  /* Likewise for an initializer for a variable-size type.  Those are
     diagnosed in the parser, except for empty initializer braces.  */
  ಯದಿ (COMPLETE_TYPE_P (constructor_type)
      && ವೃಕ್ಷ_CODE (TYPE_SIZE (constructor_type)) != INTEGER_CST)
    ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;

  ಯದಿ (!designator_depth)
    {
      gcc_assert (!constructor_range_ರಾಶಿ);

      /* Designator list starts at the level of closest explicit
	 braces.  */
      ಯಾವತ್ (constructor_ರಾಶಿ->implicit)
	process_init_element (ಒಳಹರಿವು_location,
			      ತೆಗೆ_init_level (loc, 1, braced_init_obstack,
					      last_init_list_comma),
			      ಸತ್ಯ, braced_init_obstack);
      constructor_designated = 1;
      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
    }

  ವಿಕಲ್ಪ (ವೃಕ್ಷ_CODE (constructor_type))
    {
    ಪಕ್ಷ  RECORD_TYPE:
    ಪಕ್ಷ  UNION_TYPE:
      subtype = ವೃಕ್ಷ_TYPE (constructor_fields);
      ಯದಿ (subtype != error_mark_ಗಂಟು)
	subtype = TYPE_MAIN_VARIANT (subtype);
      ಭಙ್ಗ;
    ಪಕ್ಷ ARRAY_TYPE:
      subtype = TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (constructor_type));
      ಭಙ್ಗ;
    ಸ್ವಭಾವ:
      gcc_unreachable ();
    }

  subcode = ವೃಕ್ಷ_CODE (subtype);
  ಯದಿ (array && subcode != ARRAY_TYPE)
    {
      error_init (loc, "array index in non-array initializer");
      ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
    }
  ಅನ್ಯಥಾ ಯದಿ (!array && subcode != RECORD_TYPE && subcode != UNION_TYPE)
    {
      error_init (loc, "field name not in record or union initializer");
      ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
    }

  constructor_designated = 1;
  finish_implicit_inits (loc, braced_init_obstack);
  ತಳ್ಳು_init_level (loc, 2, braced_init_obstack);
  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
}

/* If there are range designators in designator list, push a new designator
   to constructor_range_stack.  RANGE_END is end of such stack range or
   NULL_TREE if there is no range designator at this level.  */

ಸ್ಥಿರ ಶೂನ್ಯ
ತಳ್ಳು_range_ರಾಶಿ (ವೃಕ್ಷ range_end, ಸಂರಚನಾ obstack * braced_init_obstack)
{
  ಸಂರಚನಾ constructor_range_ರಾಶಿ *p;

  p = (ಸಂರಚನಾ constructor_range_ರಾಶಿ *)
    obstack_alloc (braced_init_obstack,
		   ಪರಿಮಾಣ (ಸಂರಚನಾ constructor_range_ರಾಶಿ));
  p->prev = constructor_range_ರಾಶಿ;
  p->next = 0;
  p->fields = constructor_fields;
  p->range_start = constructor_index;
  p->index = constructor_index;
  p->ರಾಶಿ = constructor_ರಾಶಿ;
  p->range_end = range_end;
  ಯದಿ (constructor_range_ರಾಶಿ)
    constructor_range_ರಾಶಿ->next = p;
  constructor_range_ರಾಶಿ = p;
}

/* Within an array initializer, specify the next index to be initialized.
   FIRST is that index.  If LAST is nonzero, then initialize a range
   of indices, running from FIRST through LAST.  */

ಶೂನ್ಯ
set_init_index (location_t loc, ವೃಕ್ಷ first, ವೃಕ್ಷ last,
		ಸಂರಚನಾ obstack *braced_init_obstack)
{
  ಯದಿ (set_designator (loc, ಸತ್ಯ, braced_init_obstack))
    ಪ್ರತ್ಯಾಗಮ;

  designator_erroneous = 1;

  ಯದಿ (!INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (first))
      || (last && !INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (last))))
    {
      error_init (loc, "array index in initializer not of integer type");
      ಪ್ರತ್ಯಾಗಮ;
    }

  ಯದಿ (ವೃಕ್ಷ_CODE (first) != INTEGER_CST)
    {
      first = c_fully_fold (first, ಅಸತ್ಯ, ರಿಕ್ತ);
      ಯದಿ (ವೃಕ್ಷ_CODE (first) == INTEGER_CST)
	pedwarn_init (loc, OPT_Wpedantic,
		      "array index in initializer is not "
		      "an integer constant expression");
    }

  ಯದಿ (last && ವೃಕ್ಷ_CODE (last) != INTEGER_CST)
    {
      last = c_fully_fold (last, ಅಸತ್ಯ, ರಿಕ್ತ);
      ಯದಿ (ವೃಕ್ಷ_CODE (last) == INTEGER_CST)
	pedwarn_init (loc, OPT_Wpedantic,
		      "array index in initializer is not "
		      "an integer constant expression");
    }

  ಯದಿ (ವೃಕ್ಷ_CODE (first) != INTEGER_CST)
    error_init (loc, "nonconstant array index in initializer");
  ಅನ್ಯಥಾ ಯದಿ (last != NULL_ವೃಕ್ಷ && ವೃಕ್ಷ_CODE (last) != INTEGER_CST)
    error_init (loc, "nonconstant array index in initializer");
  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (constructor_type) != ARRAY_TYPE)
    error_init (loc, "array index in non-array initializer");
  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_int_cst_sgn (first) == -1)
    error_init (loc, "array index in initializer exceeds array bounds");
  ಅನ್ಯಥಾ ಯದಿ (constructor_max_index
	   && ವೃಕ್ಷ_int_cst_lt (constructor_max_index, first))
    error_init (loc, "array index in initializer exceeds array bounds");
  ಅನ್ಯಥಾ
    {
      constant_expression_warning (first);
      ಯದಿ (last)
	constant_expression_warning (last);
      constructor_index = convert (bitsizetype, first);
      ಯದಿ (ವೃಕ್ಷ_int_cst_lt (constructor_index, first))
	{
	  constructor_index = copy_ಗಂಟು (constructor_index);
	  ವೃಕ್ಷ_OVERFLOW (constructor_index) = 1;
	}

      ಯದಿ (last)
	{
	  ಯದಿ (ವೃಕ್ಷ_int_cst_equal (first, last))
	    last = NULL_ವೃಕ್ಷ;
	  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_int_cst_lt (last, first))
	    {
	      error_init (loc, "empty index range in initializer");
	      last = NULL_ವೃಕ್ಷ;
	    }
	  ಅನ್ಯಥಾ
	    {
	      last = convert (bitsizetype, last);
	      ಯದಿ (constructor_max_index != NULL_ವೃಕ್ಷ
		  && ವೃಕ್ಷ_int_cst_lt (constructor_max_index, last))
		{
		  error_init (loc, "array index range in initializer exceeds "
			      "array bounds");
		  last = NULL_ವೃಕ್ಷ;
		}
	    }
	}

      designator_depth++;
      designator_erroneous = 0;
      ಯದಿ (constructor_range_ರಾಶಿ || last)
	ತಳ್ಳು_range_ರಾಶಿ (last, braced_init_obstack);
    }
}

/* Within a struct initializer, specify the next field to be initialized.  */

ಶೂನ್ಯ
set_init_label (location_t loc, ವೃಕ್ಷ fieldname, location_t fieldname_loc,
		ಸಂರಚನಾ obstack *braced_init_obstack)
{
  ವೃಕ್ಷ field;

  ಯದಿ (set_designator (loc, ಅಸತ್ಯ, braced_init_obstack))
    ಪ್ರತ್ಯಾಗಮ;

  designator_erroneous = 1;

  ಯದಿ (!RECORD_OR_UNION_TYPE_P (constructor_type))
    {
      error_init (loc, "field name not in record or union initializer");
      ಪ್ರತ್ಯಾಗಮ;
    }

  field = lookup_field (constructor_type, fieldname);

  ಯದಿ (field == NULL_ವೃಕ್ಷ)
    {
      ವೃಕ್ಷ guessed_id = lookup_field_fuzzy (constructor_type, fieldname);
      ಯದಿ (guessed_id)
	{
	  gcc_rich_location rich_loc (fieldname_loc);
	  rich_loc.add_fixit_misspelled_id (fieldname_loc, guessed_id);
	  error_at (&rich_loc,
		    "%qT has no member named %qE; did you mean %qE?",
		    constructor_type, fieldname, guessed_id);
	}
      ಅನ್ಯಥಾ
	error_at (fieldname_loc, "%qT has no member named %qE",
		  constructor_type, fieldname);
    }
  ಅನ್ಯಥಾ
    ಕುರು
      {
	constructor_fields = ವೃಕ್ಷ_ಮೌಲ್ಯ (field);
	designator_depth++;
	designator_erroneous = 0;
	ಯದಿ (constructor_range_ರಾಶಿ)
	  ತಳ್ಳು_range_ರಾಶಿ (NULL_ವೃಕ್ಷ, braced_init_obstack);
	field = ವೃಕ್ಷ_CHAIN (field);
	ಯದಿ (field)
	  {
	    ಯದಿ (set_designator (loc, ಅಸತ್ಯ, braced_init_obstack))
	      ಪ್ರತ್ಯಾಗಮ;
	  }
      }
    ಯಾವತ್ (field != NULL_ವೃಕ್ಷ);
}

/* Helper function for add_pending_init.  Find inorder successor of P
   in AVL tree.  */
ಸ್ಥಿರ ಸಂರಚನಾ init_ಗಂಟು *
init_ಗಂಟು_successor (ಸಂರಚನಾ init_ಗಂಟು *p)
{
  ಸಂರಚನಾ init_ಗಂಟು *r;
  ಯದಿ (p->ಬಲ)
    {
      r = p->ಬಲ;
      ಯಾವತ್ (r->ಎಡ)
	r = r->ಎಡ;
      ಪ್ರತ್ಯಾಗಮ r;
    }
  r = p->parent;
  ಯಾವತ್ (r && p == r->ಬಲ)
    {
      p = r;
      r = r->parent;
    }
  ಪ್ರತ್ಯಾಗಮ r;
}

/* Add a new initializer to the tree of pending initializers.  PURPOSE
   identifies the initializer, either array index or field in a structure.
   VALUE is the value of that index or field.  If ORIGTYPE is not
   NULL_TREE, it is the original type of VALUE.

   IMPLICIT is true if value comes from pop_init_level (1),
   the new initializer has been merged with the existing one
   and thus no warnings should be emitted about overriding an
   existing initializer.  */

ಸ್ಥಿರ ಶೂನ್ಯ
add_pending_init (location_t loc, ವೃಕ್ಷ purpose, ವೃಕ್ಷ ಮೌಲ್ಯ, ವೃಕ್ಷ origtype,
		  ತಾರ್ಕಿಕ implicit, ಸಂರಚನಾ obstack *braced_init_obstack)
{
  ಸಂರಚನಾ init_ಗಂಟು *p, **q, *r;

  q = &constructor_pending_elts;
  p = 0;

  ಯದಿ (ವೃಕ್ಷ_CODE (constructor_type) == ARRAY_TYPE)
    {
      ಯಾವತ್ (*q != 0)
	{
	  p = *q;
	  ಯದಿ (ವೃಕ್ಷ_int_cst_lt (purpose, p->purpose))
	    q = &p->ಎಡ;
	  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_int_cst_lt (p->purpose, purpose))
	    {
	      ಯದಿ (ವೃಕ್ಷ_CODE (p->ಮೌಲ್ಯ) != RAW_DATA_CST
		  || (p->ಬಲ
		      && ವೃಕ್ಷ_int_cst_le (p->ಬಲ->purpose, purpose)))
		q = &p->ಬಲ;
	      ಅನ್ಯಥಾ
		{
		  widest_int pp = wi::to_widest (p->purpose);
		  widest_int pw = wi::to_widest (purpose);
		  ಯದಿ (pp + RAW_DATA_LENGTH (p->ಮೌಲ್ಯ) <= pw)
		    q = &p->ಬಲ;
		  ಅನ್ಯಥಾ
		    {
		      /* Override which should split the old RAW_DATA_CST
			 into 2 or 3 pieces.  */
		      ಯದಿ (!implicit && warn_override_init)
			warning_init (loc, OPT_Woverride_init,
				      "initialized field overwritten");
		      unsigned HOST_WIDE_INT start = (pw - pp).to_uhwi ();
		      unsigned HOST_WIDE_INT len = 1;
		      ಯದಿ (ವೃಕ್ಷ_CODE (ಮೌಲ್ಯ) == RAW_DATA_CST)
			len = RAW_DATA_LENGTH (ಮೌಲ್ಯ);
		      unsigned HOST_WIDE_INT end = 0;
		      unsigned plen = RAW_DATA_LENGTH (p->ಮೌಲ್ಯ);
		      gcc_checking_assert (start < plen && start);
		      ಯದಿ (plen - start > len)
			end = plen - start - len;
		      ವೃಕ್ಷ v = p->ಮೌಲ್ಯ;
		      ವೃಕ್ಷ origtype = p->origtype;
		      ಯದಿ (start == 1)
			p->ಮೌಲ್ಯ = build_int_cst (ವೃಕ್ಷ_TYPE (v),
						  RAW_DATA_UCHAR_ELT (v, 0));
		      ಅನ್ಯಥಾ
			{
			  p->ಮೌಲ್ಯ = v;
			  ಯದಿ (end > 1)
			    v = copy_ಗಂಟು (v);
			  RAW_DATA_LENGTH (p->ಮೌಲ್ಯ) = start;
			}
		      ಯದಿ (end)
			{
			  ವೃಕ್ಷ epurpose
			    = size_binop (PLUS_ಅಭಿವ್ಯಕ್ತಿ, purpose,
					  bitsize_int (len));
			  ಯದಿ (end > 1)
			    {
			      RAW_DATA_LENGTH (v) -= plen - end;
			      RAW_DATA_POINTER (v) += plen - end;
			    }
			  ಅನ್ಯಥಾ
			    v = build_int_cst (ವೃಕ್ಷ_TYPE (v),
					       RAW_DATA_UCHAR_ELT (v, plen
								      - end));
			  add_pending_init (loc, epurpose, v, origtype,
					    implicit, braced_init_obstack);
			}
		      q = &constructor_pending_elts;
		      ಅನುವರ್ತ;
		    }
		}
	    }
	  ಅನ್ಯಥಾ
	    {
	      ಯದಿ (ವೃಕ್ಷ_CODE (p->ಮೌಲ್ಯ) == RAW_DATA_CST
		  && (RAW_DATA_LENGTH (p->ಮೌಲ್ಯ)
		      > (ವೃಕ್ಷ_CODE (ಮೌಲ್ಯ) == RAW_DATA_CST
			 ? RAW_DATA_LENGTH (ಮೌಲ್ಯ) : 1)))
		{
		  /* Override which should split the old RAW_DATA_CST
		     into 2 pieces.  */
		  ಯದಿ (!implicit && warn_override_init)
		    warning_init (loc, OPT_Woverride_init,
				  "initialized field overwritten");
		  unsigned HOST_WIDE_INT len = 1;
		  ಯದಿ (ವೃಕ್ಷ_CODE (ಮೌಲ್ಯ) == RAW_DATA_CST)
		    len = RAW_DATA_LENGTH (ಮೌಲ್ಯ);
		  ಯದಿ ((unsigned) RAW_DATA_LENGTH (p->ಮೌಲ್ಯ) > len + 1)
		    {
		      RAW_DATA_LENGTH (p->ಮೌಲ್ಯ) -= len;
		      RAW_DATA_POINTER (p->ಮೌಲ್ಯ) += len;
		    }
		  ಅನ್ಯಥಾ
		    {
		      unsigned ಪೂರ್ಣಾಙ್ಕ l = RAW_DATA_LENGTH (p->ಮೌಲ್ಯ) - 1;
		      p->ಮೌಲ್ಯ
			= build_int_cst (ವೃಕ್ಷ_TYPE (p->ಮೌಲ್ಯ),
					 RAW_DATA_UCHAR_ELT (p->ಮೌಲ್ಯ, l));
		    }
		  p->purpose = size_binop (PLUS_ಅಭಿವ್ಯಕ್ತಿ, p->purpose,
					   bitsize_int (len));
		  ಅನುವರ್ತ;
		}
	      ಯದಿ (ವೃಕ್ಷ_CODE (ಮೌಲ್ಯ) == RAW_DATA_CST)
		{
		handle_raw_data:
		  /* RAW_DATA_CST value might overlap various further
		     prior initval entries.  Find out how many.  */
		  unsigned cnt = 0;
		  widest_int w
		    = wi::to_widest (purpose) + RAW_DATA_LENGTH (ಮೌಲ್ಯ);
		  ಸಂರಚನಾ init_ಗಂಟು *r = p, *last = ರಿಕ್ತ;
		  ತಾರ್ಕಿಕ override_init = warn_override_init;
		  ಯಾವತ್ ((r = init_ಗಂಟು_successor (r))
			 && wi::to_widest (r->purpose) < w)
		    {
		      ++cnt;
		      ಯದಿ (ವೃಕ್ಷ_SIDE_EFFECTS (r->ಮೌಲ್ಯ))
			warning_init (loc, OPT_Woverride_init_side_effects,
				      "initialized field with side-effects "
				      "overwritten");
		      ಅನ್ಯಥಾ ಯದಿ (override_init)
			{
			  warning_init (loc, OPT_Woverride_init,
					"initialized field overwritten");
			  override_init = ಅಸತ್ಯ;
			}
		      last = r;
		    }
		  ಯದಿ (cnt)
		    {
		      ಯದಿ (ವೃಕ್ಷ_CODE (last->ಮೌಲ್ಯ) == RAW_DATA_CST
			  && (wi::to_widest (last->purpose)
			      + RAW_DATA_LENGTH (last->ಮೌಲ್ಯ) > w))
			{
			  /* The last overlapping prior initval overlaps
			     only partially.  Shrink it and decrease cnt.  */
			  unsigned ಪೂರ್ಣಾಙ್ಕ l = (wi::to_widest (last->purpose)
					    + RAW_DATA_LENGTH (last->ಮೌಲ್ಯ)
					    - w).to_uhwi ();
			  --cnt;
			  RAW_DATA_LENGTH (last->ಮೌಲ್ಯ) -= l;
			  RAW_DATA_POINTER (last->ಮೌಲ್ಯ) += l;
			  ಯದಿ (RAW_DATA_LENGTH (last->ಮೌಲ್ಯ) == 1)
			    last->ಮೌಲ್ಯ
			      = build_int_cst (ವೃಕ್ಷ_TYPE (last->ಮೌಲ್ಯ),
					       RAW_DATA_UCHAR_ELT (last->ಮೌಲ್ಯ,
								   0));
			  last->purpose
			    = size_binop (PLUS_ಅಭಿವ್ಯಕ್ತಿ, last->purpose,
					  bitsize_int (l));
			}
		      /* Instead of deleting cnt nodes from the AVL tree
			 and rebalancing, peel of last cnt bytes from the
			 RAW_DATA_CST.  Overriding thousands of previously
			 initialized array elements with #embed needs to work,
			 but doesn't need to be super efficient.  */
		      gcc_checking_assert ((unsigned) RAW_DATA_LENGTH (ಮೌಲ್ಯ)
					   > cnt);
		      RAW_DATA_LENGTH (ಮೌಲ್ಯ) -= cnt;
		      ಧ್ರುವ unsigned ವರ್ಣ *s
			= &RAW_DATA_UCHAR_ELT (ಮೌಲ್ಯ, RAW_DATA_LENGTH (ಮೌಲ್ಯ));
		      unsigned ಪೂರ್ಣಾಙ್ಕ o = RAW_DATA_LENGTH (ಮೌಲ್ಯ);
		      ಪ್ರತಿ (r = p; cnt--; ++o, ++s)
			{
			  r = init_ಗಂಟು_successor (r);
			  r->purpose = size_binop (PLUS_ಅಭಿವ್ಯಕ್ತಿ, purpose,
						   bitsize_int (o));
			  r->ಮೌಲ್ಯ = build_int_cst (ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ), *s);
			  r->origtype = origtype;
			}
		      ಯದಿ (RAW_DATA_LENGTH (ಮೌಲ್ಯ) == 1)
			ಮೌಲ್ಯ = build_int_cst (ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ),
					       RAW_DATA_UCHAR_ELT (ಮೌಲ್ಯ, 0));
		    }
		}
	      ಯದಿ (!implicit)
		{
		  ಯದಿ (ವೃಕ್ಷ_SIDE_EFFECTS (p->ಮೌಲ್ಯ))
		    warning_init (loc, OPT_Woverride_init_side_effects,
				  "initialized field with side-effects "
				  "overwritten");
		  ಅನ್ಯಥಾ ಯದಿ (warn_override_init)
		    warning_init (loc, OPT_Woverride_init,
				  "initialized field overwritten");
		}
	      p->ಮೌಲ್ಯ = ಮೌಲ್ಯ;
	      p->origtype = origtype;
	      ಪ್ರತ್ಯಾಗಮ;
	    }
	}
      ಯದಿ (ವೃಕ್ಷ_CODE (ಮೌಲ್ಯ) == RAW_DATA_CST && p)
	{
	  ಸಂರಚನಾ init_ಗಂಟು *r;
	  ಯದಿ (q == &p->ಎಡ)
	    r = p;
	  ಅನ್ಯಥಾ
	    r = init_ಗಂಟು_successor (p);
	  ಯದಿ (r && wi::to_widest (r->purpose) < (wi::to_widest (purpose)
						 + RAW_DATA_LENGTH (ಮೌಲ್ಯ)))
	    {
	      /* Overlap with at least one prior initval in the range but
		 not at the start.  */
	      p = r;
	      p->purpose = purpose;
	      ಗಚ್ಛ handle_raw_data;
	    }
	}
    }
  ಅನ್ಯಥಾ
    {
      ವೃಕ್ಷ bitpos;

      bitpos = bit_position (purpose);
      ಯಾವತ್ (*q != ರಿಕ್ತ)
	{
	  p = *q;
	  ಯದಿ (ವೃಕ್ಷ_int_cst_lt (bitpos, bit_position (p->purpose)))
	    q = &p->ಎಡ;
	  ಅನ್ಯಥಾ ಯದಿ (p->purpose != purpose)
	    q = &p->ಬಲ;
	  ಅನ್ಯಥಾ
	    {
	      ಯದಿ (!implicit)
		{
		  ಯದಿ (ವೃಕ್ಷ_SIDE_EFFECTS (p->ಮೌಲ್ಯ))
		    warning_init (loc, OPT_Woverride_init_side_effects,
				  "initialized field with side-effects "
				  "overwritten");
		  ಅನ್ಯಥಾ ಯದಿ (warn_override_init)
		    warning_init (loc, OPT_Woverride_init,
				  "initialized field overwritten");
		}
	      p->ಮೌಲ್ಯ = ಮೌಲ್ಯ;
	      p->origtype = origtype;
	      ಪ್ರತ್ಯಾಗಮ;
	    }
	}
    }

  r = (ಸಂರಚನಾ init_ಗಂಟು *) obstack_alloc (braced_init_obstack,
					  ಪರಿಮಾಣ (ಸಂರಚನಾ init_ಗಂಟು));
  r->purpose = purpose;
  r->ಮೌಲ್ಯ = ಮೌಲ್ಯ;
  r->origtype = origtype;

  *q = r;
  r->parent = p;
  r->ಎಡ = 0;
  r->ಬಲ = 0;
  r->balance = 0;

  ಯಾವತ್ (p)
    {
      ಸಂರಚನಾ init_ಗಂಟು *s;

      ಯದಿ (r == p->ಎಡ)
	{
	  ಯದಿ (p->balance == 0)
	    p->balance = -1;
	  ಅನ್ಯಥಾ ಯದಿ (p->balance < 0)
	    {
	      ಯದಿ (r->balance < 0)
		{
		  /* L rotation.  */
		  p->ಎಡ = r->ಬಲ;
		  ಯದಿ (p->ಎಡ)
		    p->ಎಡ->parent = p;
		  r->ಬಲ = p;

		  p->balance = 0;
		  r->balance = 0;

		  s = p->parent;
		  p->parent = r;
		  r->parent = s;
		  ಯದಿ (s)
		    {
		      ಯದಿ (s->ಎಡ == p)
			s->ಎಡ = r;
		      ಅನ್ಯಥಾ
			s->ಬಲ = r;
		    }
		  ಅನ್ಯಥಾ
		    constructor_pending_elts = r;
		}
	      ಅನ್ಯಥಾ
		{
		  /* LR rotation.  */
		  ಸಂರಚನಾ init_ಗಂಟು *t = r->ಬಲ;

		  r->ಬಲ = t->ಎಡ;
		  ಯದಿ (r->ಬಲ)
		    r->ಬಲ->parent = r;
		  t->ಎಡ = r;

		  p->ಎಡ = t->ಬಲ;
		  ಯದಿ (p->ಎಡ)
		    p->ಎಡ->parent = p;
		  t->ಬಲ = p;

		  p->balance = t->balance < 0;
		  r->balance = -(t->balance > 0);
		  t->balance = 0;

		  s = p->parent;
		  p->parent = t;
		  r->parent = t;
		  t->parent = s;
		  ಯದಿ (s)
		    {
		      ಯದಿ (s->ಎಡ == p)
			s->ಎಡ = t;
		      ಅನ್ಯಥಾ
			s->ಬಲ = t;
		    }
		  ಅನ್ಯಥಾ
		    constructor_pending_elts = t;
		}
	      ಭಙ್ಗ;
	    }
	  ಅನ್ಯಥಾ
	    {
	      /* p->balance == +1; growth of left side balances the node.  */
	      p->balance = 0;
	      ಭಙ್ಗ;
	    }
	}
      ಅನ್ಯಥಾ /* r == p->right */
	{
	  ಯದಿ (p->balance == 0)
	    /* Growth propagation from right side.  */
	    p->balance++;
	  ಅನ್ಯಥಾ ಯದಿ (p->balance > 0)
	    {
	      ಯದಿ (r->balance > 0)
		{
		  /* R rotation.  */
		  p->ಬಲ = r->ಎಡ;
		  ಯದಿ (p->ಬಲ)
		    p->ಬಲ->parent = p;
		  r->ಎಡ = p;

		  p->balance = 0;
		  r->balance = 0;

		  s = p->parent;
		  p->parent = r;
		  r->parent = s;
		  ಯದಿ (s)
		    {
		      ಯದಿ (s->ಎಡ == p)
			s->ಎಡ = r;
		      ಅನ್ಯಥಾ
			s->ಬಲ = r;
		    }
		  ಅನ್ಯಥಾ
		    constructor_pending_elts = r;
		}
	      ಅನ್ಯಥಾ /* r->balance == -1 */
		{
		  /* RL rotation */
		  ಸಂರಚನಾ init_ಗಂಟು *t = r->ಎಡ;

		  r->ಎಡ = t->ಬಲ;
		  ಯದಿ (r->ಎಡ)
		    r->ಎಡ->parent = r;
		  t->ಬಲ = r;

		  p->ಬಲ = t->ಎಡ;
		  ಯದಿ (p->ಬಲ)
		    p->ಬಲ->parent = p;
		  t->ಎಡ = p;

		  r->balance = (t->balance < 0);
		  p->balance = -(t->balance > 0);
		  t->balance = 0;

		  s = p->parent;
		  p->parent = t;
		  r->parent = t;
		  t->parent = s;
		  ಯದಿ (s)
		    {
		      ಯದಿ (s->ಎಡ == p)
			s->ಎಡ = t;
		      ಅನ್ಯಥಾ
			s->ಬಲ = t;
		    }
		  ಅನ್ಯಥಾ
		    constructor_pending_elts = t;
		}
	      ಭಙ್ಗ;
	    }
	  ಅನ್ಯಥಾ
	    {
	      /* p->balance == -1; growth of right side balances the node.  */
	      p->balance = 0;
	      ಭಙ್ಗ;
	    }
	}

      r = p;
      p = p->parent;
    }
}

/* Build AVL tree from a sorted chain.  */

ಸ್ಥಿರ ಶೂನ್ಯ
set_nonincremental_init (ಸಂರಚನಾ obstack * braced_init_obstack)
{
  unsigned HOST_WIDE_INT ix;
  ವೃಕ್ಷ index, ಮೌಲ್ಯ;

  ಯದಿ (ವೃಕ್ಷ_CODE (constructor_type) != RECORD_TYPE
      && ವೃಕ್ಷ_CODE (constructor_type) != ARRAY_TYPE)
    ಪ್ರತ್ಯಾಗಮ;

  FOR_EACH_CONSTRUCTOR_ELT (constructor_elements, ix, index, ಮೌಲ್ಯ)
    add_pending_init (ಒಳಹರಿವು_location, index, ಮೌಲ್ಯ, NULL_ವೃಕ್ಷ, ಸತ್ಯ,
		      braced_init_obstack);
  constructor_elements = ರಿಕ್ತ;
  ಯದಿ (ವೃಕ್ಷ_CODE (constructor_type) == RECORD_TYPE)
    {
      constructor_unfilled_fields = TYPE_FIELDS (constructor_type);
      /* Skip any nameless bit fields at the beginning.  */
      ಯಾವತ್ (constructor_unfilled_fields != NULL_ವೃಕ್ಷ
	     && DECL_UNNAMED_BIT_FIELD (constructor_unfilled_fields))
	constructor_unfilled_fields = ವೃಕ್ಷ_CHAIN (constructor_unfilled_fields);

    }
  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (constructor_type) == ARRAY_TYPE)
    {
      ಯದಿ (TYPE_DOMAIN (constructor_type))
	constructor_unfilled_index
	  = convert (bitsizetype,
		     TYPE_MIN_ಮೌಲ್ಯ (TYPE_DOMAIN (constructor_type)));
      ಅನ್ಯಥಾ
	constructor_unfilled_index = bitsize_zero_ಗಂಟು;
    }
  constructor_incremental = 0;
}

/* Build AVL tree from a string constant.  */

ಸ್ಥಿರ ಶೂನ್ಯ
set_nonincremental_init_from_string (ವೃಕ್ಷ str,
				     ಸಂರಚನಾ obstack * braced_init_obstack)
{
  ವೃಕ್ಷ ಮೌಲ್ಯ, purpose, type;
  HOST_WIDE_INT val[2];
  ಧ್ರುವ ವರ್ಣ *p, *end;
  ಪೂರ್ಣಾಙ್ಕ byte, wchar_bytes, charwidth, bitpos;

  gcc_assert (ವೃಕ್ಷ_CODE (constructor_type) == ARRAY_TYPE);

  wchar_bytes = TYPE_PRECISION (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (str))) / BITS_PER_UNIT;
  charwidth = TYPE_PRECISION (char_type_ಗಂಟು);
  gcc_assert ((size_t) wchar_bytes * charwidth
	      <= ARRAY_SIZE (val) * HOST_BITS_PER_WIDE_INT);
  type = ವೃಕ್ಷ_TYPE (constructor_type);
  p = ವೃಕ್ಷ_STRING_POINTER (str);
  end = p + ವೃಕ್ಷ_STRING_LENGTH (str);

  ಪ್ರತಿ (purpose = bitsize_zero_ಗಂಟು;
       p < end
       && !(constructor_max_index
	    && ವೃಕ್ಷ_int_cst_lt (constructor_max_index, purpose));
       purpose = size_binop (PLUS_ಅಭಿವ್ಯಕ್ತಿ, purpose, bitsize_one_ಗಂಟು))
    {
      ಯದಿ (wchar_bytes == 1)
	{
	  val[0] = (unsigned ವರ್ಣ) *p++;
	  val[1] = 0;
	}
      ಅನ್ಯಥಾ
	{
	  val[1] = 0;
	  val[0] = 0;
	  ಪ್ರತಿ (byte = 0; byte < wchar_bytes; byte++)
	    {
	      ಯದಿ (BYTES_BIG_ENDIAN)
		bitpos = (wchar_bytes - byte - 1) * charwidth;
	      ಅನ್ಯಥಾ
		bitpos = byte * charwidth;
	      val[bitpos / HOST_BITS_PER_WIDE_INT]
		|= ((unsigned HOST_WIDE_INT) ((unsigned ವರ್ಣ) *p++))
		   << (bitpos % HOST_BITS_PER_WIDE_INT);
	    }
	}

      ಯದಿ (!TYPE_UNSIGNED (type))
	{
	  bitpos = ((wchar_bytes - 1) * charwidth) + HOST_BITS_PER_CHAR;
	  ಯದಿ (bitpos < HOST_BITS_PER_WIDE_INT)
	    {
	      ಯದಿ (val[0] & (HOST_WIDE_INT_1 << (bitpos - 1)))
		{
		  val[0] |= HOST_WIDE_INT_M1U << bitpos;
		  val[1] = -1;
		}
	    }
	  ಅನ್ಯಥಾ ಯದಿ (bitpos == HOST_BITS_PER_WIDE_INT)
	    {
	      ಯದಿ (val[0] < 0)
		val[1] = -1;
	    }
	  ಅನ್ಯಥಾ ಯದಿ (val[1] & (HOST_WIDE_INT_1
			     << (bitpos - 1 - HOST_BITS_PER_WIDE_INT)))
	    val[1] |= HOST_WIDE_INT_M1U << (bitpos - HOST_BITS_PER_WIDE_INT);
	}

      ಮೌಲ್ಯ = wide_int_to_ವೃಕ್ಷ (type,
				wide_int::from_array (val, 2,
						      HOST_BITS_PER_WIDE_INT * 2));
      add_pending_init (ಒಳಹರಿವು_location, purpose, ಮೌಲ್ಯ, NULL_ವೃಕ್ಷ, ಸತ್ಯ,
                        braced_init_obstack);
    }

  constructor_incremental = 0;
}

/* Return value of FIELD in pending initializer or NULL_TREE if the field was
   not initialized yet.  */

ಸ್ಥಿರ ವೃಕ್ಷ
find_init_member (ವೃಕ್ಷ field, ಸಂರಚನಾ obstack * braced_init_obstack)
{
  ಸಂರಚನಾ init_ಗಂಟು *p;

  ಯದಿ (ವೃಕ್ಷ_CODE (constructor_type) == ARRAY_TYPE)
    {
      ಯದಿ (constructor_incremental
	  && ವೃಕ್ಷ_int_cst_lt (field, constructor_unfilled_index))
	set_nonincremental_init (braced_init_obstack);

      p = constructor_pending_elts;
      ಯಾವತ್ (p)
	{
	  ಯದಿ (ವೃಕ್ಷ_int_cst_lt (field, p->purpose))
	    p = p->ಎಡ;
	  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_int_cst_lt (p->purpose, field))
	    p = p->ಬಲ;
	  ಅನ್ಯಥಾ
	    ಪ್ರತ್ಯಾಗಮ p->ಮೌಲ್ಯ;
	}
    }
  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (constructor_type) == RECORD_TYPE)
    {
      ವೃಕ್ಷ bitpos = bit_position (field);

      ಯದಿ (constructor_incremental
	  && (!constructor_unfilled_fields
	      || ವೃಕ್ಷ_int_cst_lt (bitpos,
				  bit_position (constructor_unfilled_fields))))
	set_nonincremental_init (braced_init_obstack);

      p = constructor_pending_elts;
      ಯಾವತ್ (p)
	{
	  ಯದಿ (field == p->purpose)
	    ಪ್ರತ್ಯಾಗಮ p->ಮೌಲ್ಯ;
	  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_int_cst_lt (bitpos, bit_position (p->purpose)))
	    p = p->ಎಡ;
	  ಅನ್ಯಥಾ
	    p = p->ಬಲ;
	}
    }
  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (constructor_type) == UNION_TYPE)
    {
      ಯದಿ (!vec_safe_is_empty (constructor_elements)
	  && (constructor_elements->last ().index == field))
	ಪ್ರತ್ಯಾಗಮ constructor_elements->last ().ಮೌಲ್ಯ;
    }
  ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
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

ಸ್ಥಿರ ಶೂನ್ಯ
output_init_element (location_t loc, ವೃಕ್ಷ ಮೌಲ್ಯ, ವೃಕ್ಷ origtype,
		     ತಾರ್ಕಿಕ strict_string, ವೃಕ್ಷ type, ವೃಕ್ಷ field, ತಾರ್ಕಿಕ pending,
		     ತಾರ್ಕಿಕ implicit, ಸಂರಚನಾ obstack * braced_init_obstack)
{
  ವೃಕ್ಷ semantic_type = NULL_ವೃಕ್ಷ;
  ತಾರ್ಕಿಕ maybe_const = ಸತ್ಯ;
  ತಾರ್ಕಿಕ npc, int_const_ಅಭಿವ್ಯಕ್ತಿ, arith_const_ಅಭಿವ್ಯಕ್ತಿ;

  ಯದಿ (type == error_mark_ಗಂಟು || ಮೌಲ್ಯ == error_mark_ಗಂಟು)
    {
      constructor_erroneous = 1;
      ಪ್ರತ್ಯಾಗಮ;
    }
  ಯದಿ (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ)) == ARRAY_TYPE
      && (ವೃಕ್ಷ_CODE (ಮೌಲ್ಯ) == STRING_CST
	  || ವೃಕ್ಷ_CODE (ಮೌಲ್ಯ) == COMPOUND_LITERAL_ಅಭಿವ್ಯಕ್ತಿ)
      && !(ವೃಕ್ಷ_CODE (ಮೌಲ್ಯ) == STRING_CST
	   && ವೃಕ್ಷ_CODE (type) == ARRAY_TYPE
	   && INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (type)))
      && !comptypes (TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ)),
		     TYPE_MAIN_VARIANT (type)))
    ಮೌಲ್ಯ = array_to_pointer_conversion (ಒಳಹರಿವು_location, ಮೌಲ್ಯ);

  ಯದಿ (ವೃಕ್ಷ_CODE (ಮೌಲ್ಯ) == COMPOUND_LITERAL_ಅಭಿವ್ಯಕ್ತಿ
      && require_constant_ಮೌಲ್ಯ && pending)
    {
      /* As an extension, allow initializing objects with static storage
	 duration with compound literals (which are then treated just as
	 the brace enclosed list they contain).  */
      ಯದಿ (flag_isoc99)
	pedwarn_init (loc, OPT_Wpedantic, "initializer element is not "
		      "constant");
      ವೃಕ್ಷ decl = COMPOUND_LITERAL_ಅಭಿವ್ಯಕ್ತಿ_DECL (ಮೌಲ್ಯ);
      ಮೌಲ್ಯ = DECL_INITIAL (decl);
    }

  npc = null_pointer_constant_p (ಮೌಲ್ಯ);
  int_const_ಅಭಿವ್ಯಕ್ತಿ = (ವೃಕ್ಷ_CODE (ಮೌಲ್ಯ) == INTEGER_CST
		    && !ವೃಕ್ಷ_OVERFLOW (ಮೌಲ್ಯ)
		    && INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ)));
  /* Not fully determined before folding.  */
  arith_const_ಅಭಿವ್ಯಕ್ತಿ = ಸತ್ಯ;
  ಯದಿ (ವೃಕ್ಷ_CODE (ಮೌಲ್ಯ) == EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ)
    {
      semantic_type = ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ);
      ಮೌಲ್ಯ = ವೃಕ್ಷ_OPERAND (ಮೌಲ್ಯ, 0);
    }
  ಮೌಲ್ಯ = c_fully_fold (ಮೌಲ್ಯ, require_constant_ಮೌಲ್ಯ, &maybe_const);
  /* TODO: this may not detect all cases of expressions folding to
     constants that are not arithmetic constant expressions.  */
  ಯದಿ (!maybe_const)
    arith_const_ಅಭಿವ್ಯಕ್ತಿ = ಅಸತ್ಯ;
  ಅನ್ಯಥಾ ಯದಿ (!INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ))
	   && ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ)) != REAL_TYPE
	   && ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ)) != COMPLEX_TYPE)
    arith_const_ಅಭಿವ್ಯಕ್ತಿ = ಅಸತ್ಯ;
  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (ಮೌಲ್ಯ) != INTEGER_CST
	   && ವೃಕ್ಷ_CODE (ಮೌಲ್ಯ) != REAL_CST
	   && ವೃಕ್ಷ_CODE (ಮೌಲ್ಯ) != COMPLEX_CST
	   && ವೃಕ್ಷ_CODE (ಮೌಲ್ಯ) != RAW_DATA_CST)
    arith_const_ಅಭಿವ್ಯಕ್ತಿ = ಅಸತ್ಯ;
  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_OVERFLOW (ಮೌಲ್ಯ))
    arith_const_ಅಭಿವ್ಯಕ್ತಿ = ಅಸತ್ಯ;

  ಯದಿ (ಮೌಲ್ಯ == error_mark_ಗಂಟು)
    constructor_erroneous = 1;
  ಅನ್ಯಥಾ ಯದಿ (!ವೃಕ್ಷ_CONSTANT (ಮೌಲ್ಯ))
    constructor_constant = 0;
  ಅನ್ಯಥಾ ಯದಿ (!initializer_constant_valid_p (ಮೌಲ್ಯ,
					  ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ),
					  AGGREGATE_TYPE_P (constructor_type)
					  && TYPE_REVERSE_STORAGE_ORDER
					     (constructor_type))
	   || (RECORD_OR_UNION_TYPE_P (constructor_type)
	       && DECL_C_BIT_FIELD (field)
	       && ವೃಕ್ಷ_CODE (ಮೌಲ್ಯ) != INTEGER_CST))
    constructor_simple = 0;
  ಯದಿ (!maybe_const)
    constructor_nonconst = 1;

  /* Digest the initializer and issue any errors about incompatible
     types before issuing errors about non-constant initializers.  */
  ವೃಕ್ಷ new_ಮೌಲ್ಯ = ಮೌಲ್ಯ;
  ಯದಿ (semantic_type)
    new_ಮೌಲ್ಯ = build1 (EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ, semantic_type, ಮೌಲ್ಯ);
  /* In the case of braces around a scalar initializer, the result of
     this initializer processing goes through digest_init again at the
     outer level.  In the case of a constexpr initializer for a
     pointer, avoid converting a null pointer constant to something
     that is not a null pointer constant to avoid a spurious error
     from that second processing.  */
  ಯದಿ (!require_constexpr_ಮೌಲ್ಯ
      || !npc
      || ವೃಕ್ಷ_CODE (constructor_type) != POINTER_TYPE)
    new_ಮೌಲ್ಯ = digest_init (loc,
			     RECORD_OR_UNION_TYPE_P (constructor_type)
			     ? field : constructor_fields
			     ? constructor_fields : constructor_decl,
			     type, new_ಮೌಲ್ಯ, origtype, npc,
			     int_const_ಅಭಿವ್ಯಕ್ತಿ, arith_const_ಅಭಿವ್ಯಕ್ತಿ, strict_string,
			     require_constant_ಮೌಲ್ಯ, require_constexpr_ಮೌಲ್ಯ);
  ಯದಿ (new_ಮೌಲ್ಯ == error_mark_ಗಂಟು)
    {
      constructor_erroneous = 1;
      ಪ್ರತ್ಯಾಗಮ;
    }
  ಯದಿ (require_constant_ಮೌಲ್ಯ || require_constant_elements)
    constant_expression_warning (new_ಮೌಲ್ಯ);

  /* Proceed to check the constness of the original initializer.  */
  ಯದಿ (!initializer_constant_valid_p (ಮೌಲ್ಯ, ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ)))
    {
      ಯದಿ (require_constant_ಮೌಲ್ಯ)
	{
	  error_init (loc, "initializer element is not constant");
	  ಮೌಲ್ಯ = error_mark_ಗಂಟು;
	}
      ಅನ್ಯಥಾ ಯದಿ (require_constant_elements)
	pedwarn (loc, OPT_Wpedantic,
		 "initializer element is not computable at load time");
    }
  ಅನ್ಯಥಾ ಯದಿ (!maybe_const
	   && (require_constant_ಮೌಲ್ಯ || require_constant_elements))
    pedwarn_init (loc, OPT_Wpedantic,
		  "initializer element is not a constant expression");
  /* digest_init has already carried out the additional checks
     required for 'constexpr' initializers (using the information
     passed to it about whether the original initializer was certain
     kinds of constant expression), so that check does not need to be
     repeated here.  */

  /* Issue -Wc++-compat warnings about initializing a bitfield with
     enum type.  */
  ಯದಿ (warn_cxx_compat
      && field != NULL_ವೃಕ್ಷ
      && ವೃಕ್ಷ_CODE (field) == FIELD_DECL
      && DECL_BIT_FIELD_TYPE (field) != NULL_ವೃಕ್ಷ
      && (TYPE_MAIN_VARIANT (DECL_BIT_FIELD_TYPE (field))
	  != TYPE_MAIN_VARIANT (type))
      && ವೃಕ್ಷ_CODE (DECL_BIT_FIELD_TYPE (field)) == ENUMERAL_TYPE)
    {
      ವೃಕ್ಷ checktype = origtype != NULL_ವೃಕ್ಷ ? origtype : ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ);
      ಯದಿ (checktype != error_mark_ಗಂಟು
	  && (TYPE_MAIN_VARIANT (checktype)
	      != TYPE_MAIN_VARIANT (DECL_BIT_FIELD_TYPE (field))))
	warning_init (loc, OPT_Wc___compat,
		      "enum conversion in initialization is invalid in C++");
    }

  /* If this field is empty and does not have side effects (and is not at
     the end of structure), don't do anything other than checking the
     initializer.  */
  ಯದಿ (field
      && (ವೃಕ್ಷ_TYPE (field) == error_mark_ಗಂಟು
	  || (COMPLETE_TYPE_P (ವೃಕ್ಷ_TYPE (field))
	      && integer_zerop (TYPE_SIZE (ವೃಕ್ಷ_TYPE (field)))
	      && !ವೃಕ್ಷ_SIDE_EFFECTS (new_ಮೌಲ್ಯ)
	      && (ವೃಕ್ಷ_CODE (constructor_type) == ARRAY_TYPE
		  || DECL_CHAIN (field)))))
    ಪ್ರತ್ಯಾಗಮ;

  /* Finally, set VALUE to the initializer value digested above.  */
  ಮೌಲ್ಯ = new_ಮೌಲ್ಯ;

  /* If this element doesn't come next in sequence,
     put it on constructor_pending_elts.  */
  ಯದಿ (ವೃಕ್ಷ_CODE (constructor_type) == ARRAY_TYPE
      && (!constructor_incremental
	  || !ವೃಕ್ಷ_int_cst_equal (field, constructor_unfilled_index)
	  || (ವೃಕ್ಷ_CODE (ಮೌಲ್ಯ) == RAW_DATA_CST
	      && constructor_pending_elts
	      && pending)))
    {
      ಯದಿ (constructor_incremental
	  && (ವೃಕ್ಷ_int_cst_lt (field, constructor_unfilled_index)
	      || (ವೃಕ್ಷ_CODE (ಮೌಲ್ಯ) == RAW_DATA_CST
		  && constructor_pending_elts
		  && pending)))
	set_nonincremental_init (braced_init_obstack);

      add_pending_init (loc, field, ಮೌಲ್ಯ, origtype, implicit,
			braced_init_obstack);
      ಪ್ರತ್ಯಾಗಮ;
    }
  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (constructor_type) == RECORD_TYPE
	   && (!constructor_incremental
	       || field != constructor_unfilled_fields))
    {
      /* We do this for records but not for unions.  In a union,
	 no matter which field is specified, it can be initialized
	 right away since it starts at the beginning of the union.  */
      ಯದಿ (constructor_incremental)
	{
	  ಯದಿ (!constructor_unfilled_fields)
	    set_nonincremental_init (braced_init_obstack);
	  ಅನ್ಯಥಾ
	    {
	      ವೃಕ್ಷ bitpos, unfillpos;

	      bitpos = bit_position (field);
	      unfillpos = bit_position (constructor_unfilled_fields);

	      ಯದಿ (ವೃಕ್ಷ_int_cst_lt (bitpos, unfillpos))
		set_nonincremental_init (braced_init_obstack);
	    }
	}

      add_pending_init (loc, field, ಮೌಲ್ಯ, origtype, implicit,
			braced_init_obstack);
      ಪ್ರತ್ಯಾಗಮ;
    }
  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (constructor_type) == UNION_TYPE
	   && !vec_safe_is_empty (constructor_elements))
    {
      ಯದಿ (!implicit)
	{
	  ಯದಿ (ವೃಕ್ಷ_SIDE_EFFECTS (constructor_elements->last ().ಮೌಲ್ಯ))
	    warning_init (loc, OPT_Woverride_init_side_effects,
			  "initialized field with side-effects overwritten");
	  ಅನ್ಯಥಾ ಯದಿ (warn_override_init)
	    warning_init (loc, OPT_Woverride_init,
			  "initialized field overwritten");
	}

      /* We can have just one union field set.  */
      constructor_elements = ರಿಕ್ತ;
    }

  /* Otherwise, output this element either to
     constructor_elements or to the assembler file.  */

  constructor_elt celt = {field, ಮೌಲ್ಯ};
  vec_safe_ತಳ್ಳು (constructor_elements, celt);

  /* Advance the variable that indicates sequential elements output.  */
  ಯದಿ (ವೃಕ್ಷ_CODE (constructor_type) == ARRAY_TYPE)
    {
      ವೃಕ್ಷ inc = bitsize_one_ಗಂಟು;
      ಯದಿ (ಮೌಲ್ಯ && ವೃಕ್ಷ_CODE (ಮೌಲ್ಯ) == RAW_DATA_CST)
	inc = bitsize_int (RAW_DATA_LENGTH (ಮೌಲ್ಯ));
      constructor_unfilled_index
	= size_binop_loc (ಒಳಹರಿವು_location, PLUS_ಅಭಿವ್ಯಕ್ತಿ,
			  constructor_unfilled_index, inc);
    }
  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (constructor_type) == RECORD_TYPE)
    {
      constructor_unfilled_fields
	= DECL_CHAIN (constructor_unfilled_fields);

      /* Skip any nameless bit fields.  */
      ಯಾವತ್ (constructor_unfilled_fields != NULL_ವೃಕ್ಷ
	     && DECL_UNNAMED_BIT_FIELD (constructor_unfilled_fields))
	constructor_unfilled_fields
	  = DECL_CHAIN (constructor_unfilled_fields);
    }
  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (constructor_type) == UNION_TYPE)
    constructor_unfilled_fields = NULL_ವೃಕ್ಷ;

  /* Now output any pending elements which have become next.  */
  ಯದಿ (pending)
    output_pending_init_elements (0, braced_init_obstack);
}

/* For two FIELD_DECLs in the same chain, return -1 if field1
   comes before field2, 1 if field1 comes after field2 and
   0 if field1 == field2.  */

ಸ್ಥಿರ ಪೂರ್ಣಾಙ್ಕ
init_field_decl_cmp (ವೃಕ್ಷ field1, ವೃಕ್ಷ field2)
{
  ಯದಿ (field1 == field2)
    ಪ್ರತ್ಯಾಗಮ 0;

  ವೃಕ್ಷ bitpos1 = bit_position (field1);
  ವೃಕ್ಷ bitpos2 = bit_position (field2);
  ಯದಿ (ವೃಕ್ಷ_int_cst_equal (bitpos1, bitpos2))
    {
      /* If one of the fields has non-zero bitsize, then that
	 field must be the last one in a sequence of zero
	 sized fields, fields after it will have bigger
	 bit_position.  */
      ಯದಿ (ವೃಕ್ಷ_TYPE (field1) != error_mark_ಗಂಟು
	  && COMPLETE_TYPE_P (ವೃಕ್ಷ_TYPE (field1))
	  && integer_nonzerop (ವೃಕ್ಷ_TYPE (field1)))
	ಪ್ರತ್ಯಾಗಮ 1;
      ಯದಿ (ವೃಕ್ಷ_TYPE (field2) != error_mark_ಗಂಟು
	  && COMPLETE_TYPE_P (ವೃಕ್ಷ_TYPE (field2))
	  && integer_nonzerop (ವೃಕ್ಷ_TYPE (field2)))
	ಪ್ರತ್ಯಾಗಮ -1;
      /* Otherwise, fallback to DECL_CHAIN walk to find out
	 which field comes earlier.  Walk chains of both
	 fields, so that if field1 and field2 are close to each
	 other in either order, it is found soon even for large
	 sequences of zero sized fields.  */
      ವೃಕ್ಷ f1 = field1, f2 = field2;
      ಯಾವತ್ (1)
	{
	  f1 = DECL_CHAIN (f1);
	  f2 = DECL_CHAIN (f2);
	  ಯದಿ (f1 == NULL_ವೃಕ್ಷ)
	    {
	      gcc_assert (f2);
	      ಪ್ರತ್ಯಾಗಮ 1;
	    }
	  ಯದಿ (f2 == NULL_ವೃಕ್ಷ)
	    ಪ್ರತ್ಯಾಗಮ -1;
	  ಯದಿ (f1 == field2)
	    ಪ್ರತ್ಯಾಗಮ -1;
	  ಯದಿ (f2 == field1)
	    ಪ್ರತ್ಯಾಗಮ 1;
	  ಯದಿ (!ವೃಕ್ಷ_int_cst_equal (bit_position (f1), bitpos1))
	    ಪ್ರತ್ಯಾಗಮ 1;
	  ಯದಿ (!ವೃಕ್ಷ_int_cst_equal (bit_position (f2), bitpos1))
	    ಪ್ರತ್ಯಾಗಮ -1;
	}
    }
  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_int_cst_lt (bitpos1, bitpos2))
    ಪ್ರತ್ಯಾಗಮ -1;
  ಅನ್ಯಥಾ
    ಪ್ರತ್ಯಾಗಮ 1;
}

/* Output any pending elements which have become next.
   As we output elements, constructor_unfilled_{fields,index}
   advances, which may cause other elements to become next;
   if so, they too are output.

   If ALL is 0, we return when there are
   no more pending elements to output now.

   If ALL is 1, we output space as necessary so that
   we can output all the pending elements.  */
ಸ್ಥಿರ ಶೂನ್ಯ
output_pending_init_elements (ಪೂರ್ಣಾಙ್ಕ all, ಸಂರಚನಾ obstack * braced_init_obstack)
{
  ಸಂರಚನಾ init_ಗಂಟು *elt = constructor_pending_elts;
  ವೃಕ್ಷ next;

 retry:

  /* Look through the whole pending tree.
     If we find an element that should be output now,
     output it.  Otherwise, set NEXT to the element
     that comes first among those still pending.  */

  next = NULL_ವೃಕ್ಷ;
  ಯಾವತ್ (elt)
    {
      ಯದಿ (ವೃಕ್ಷ_CODE (constructor_type) == ARRAY_TYPE)
	{
	  ಯದಿ (ವೃಕ್ಷ_int_cst_equal (elt->purpose,
				  constructor_unfilled_index))
	    output_init_element (ಒಳಹರಿವು_location, elt->ಮೌಲ್ಯ, elt->origtype,
				 ಸತ್ಯ, ವೃಕ್ಷ_TYPE (constructor_type),
				 constructor_unfilled_index, ಅಸತ್ಯ, ಅಸತ್ಯ,
				 braced_init_obstack);
	  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_int_cst_lt (constructor_unfilled_index,
				    elt->purpose))
	    {
	      /* Advance to the next smaller node.  */
	      ಯದಿ (elt->ಎಡ)
		elt = elt->ಎಡ;
	      ಅನ್ಯಥಾ
		{
		  /* We have reached the smallest node bigger than the
		     current unfilled index.  Fill the space first.  */
		  next = elt->purpose;
		  ಭಙ್ಗ;
		}
	    }
	  ಅನ್ಯಥಾ
	    {
	      /* Advance to the next bigger node.  */
	      ಯದಿ (elt->ಬಲ)
		elt = elt->ಬಲ;
	      ಅನ್ಯಥಾ
		{
		  /* We have reached the biggest node in a subtree.  Find
		     the parent of it, which is the next bigger node.  */
		  ಯಾವತ್ (elt->parent && elt->parent->ಬಲ == elt)
		    elt = elt->parent;
		  elt = elt->parent;
		  ಯದಿ (elt && ವೃಕ್ಷ_int_cst_lt (constructor_unfilled_index,
					      elt->purpose))
		    {
		      next = elt->purpose;
		      ಭಙ್ಗ;
		    }
		}
	    }
	}
      ಅನ್ಯಥಾ ಯದಿ (RECORD_OR_UNION_TYPE_P (constructor_type))
	{
	  /* If the current record is complete we are done.  */
	  ಯದಿ (constructor_unfilled_fields == NULL_ವೃಕ್ಷ)
	    ಭಙ್ಗ;

	  ಪೂರ್ಣಾಙ್ಕ cmp = init_field_decl_cmp (constructor_unfilled_fields,
					 elt->purpose);
	  ಯದಿ (cmp == 0)
	    output_init_element (ಒಳಹರಿವು_location, elt->ಮೌಲ್ಯ, elt->origtype,
				 ಸತ್ಯ, ವೃಕ್ಷ_TYPE (elt->purpose),
				 elt->purpose, ಅಸತ್ಯ, ಅಸತ್ಯ,
				 braced_init_obstack);
	  ಅನ್ಯಥಾ ಯದಿ (cmp < 0)
	    {
	      /* Advance to the next smaller node.  */
	      ಯದಿ (elt->ಎಡ)
		elt = elt->ಎಡ;
	      ಅನ್ಯಥಾ
		{
		  /* We have reached the smallest node bigger than the
		     current unfilled field.  Fill the space first.  */
		  next = elt->purpose;
		  ಭಙ್ಗ;
		}
	    }
	  ಅನ್ಯಥಾ
	    {
	      /* Advance to the next bigger node.  */
	      ಯದಿ (elt->ಬಲ)
		elt = elt->ಬಲ;
	      ಅನ್ಯಥಾ
		{
		  /* We have reached the biggest node in a subtree.  Find
		     the parent of it, which is the next bigger node.  */
		  ಯಾವತ್ (elt->parent && elt->parent->ಬಲ == elt)
		    elt = elt->parent;
		  elt = elt->parent;
		  ಯದಿ (elt
		      && init_field_decl_cmp (constructor_unfilled_fields,
					      elt->purpose) < 0)
		    {
		      next = elt->purpose;
		      ಭಙ್ಗ;
		    }
		}
	    }
	}
    }

  /* Ordinarily return, but not if we want to output all
     and there are elements left.  */
  ಯದಿ (!(all && next != NULL_ವೃಕ್ಷ))
    ಪ್ರತ್ಯಾಗಮ;

  /* If it's not incremental, just skip over the gap, so that after
     jumping to retry we will output the next successive element.  */
  ಯದಿ (RECORD_OR_UNION_TYPE_P (constructor_type))
    constructor_unfilled_fields = next;
  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (constructor_type) == ARRAY_TYPE)
    constructor_unfilled_index = next;

  /* ELT now points to the node in the pending tree with the next
     initializer to output.  */
  ಗಚ್ಛ retry;
}

/* Expression VALUE coincides with the start of type TYPE in a braced
   initializer.  Return true if we should treat VALUE as initializing
   the first element of TYPE, false if we should treat it as initializing
   TYPE as a whole.

   If the initializer is clearly invalid, the question becomes:
   which choice gives the best error message?  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
initialize_elementwise_p (ವೃಕ್ಷ type, ವೃಕ್ಷ ಮೌಲ್ಯ)
{
  ಯದಿ (type == error_mark_ಗಂಟು || ಮೌಲ್ಯ == error_mark_ಗಂಟು)
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

  gcc_checking_assert (TYPE_MAIN_VARIANT (type) == type);

  ವೃಕ್ಷ ಮೌಲ್ಯ_type = ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ);
  ಯದಿ (ಮೌಲ್ಯ_type == error_mark_ಗಂಟು)
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

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
  ಯದಿ (gnu_vector_type_p (type))
    ಪ್ರತ್ಯಾಗಮ !VECTOR_TYPE_P (ಮೌಲ್ಯ_type);

  ಯದಿ (AGGREGATE_TYPE_P (type))
    ಪ್ರತ್ಯಾಗಮ !comptypes (type, TYPE_MAIN_VARIANT (ಮೌಲ್ಯ_type));

  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
}

/* Helper function for process_init_element.  Split first element of
   RAW_DATA_CST and save the rest to *RAW_DATA.  */

ಸ್ಥಿರ ಅನ್ತಃಸ್ಥ ವೃಕ್ಷ
maybe_split_raw_data (ವೃಕ್ಷ ಮೌಲ್ಯ, ವೃಕ್ಷ *raw_data)
{
  ಯದಿ (ಮೌಲ್ಯ == NULL_ವೃಕ್ಷ || ವೃಕ್ಷ_CODE (ಮೌಲ್ಯ) != RAW_DATA_CST)
    ಪ್ರತ್ಯಾಗಮ ಮೌಲ್ಯ;
  *raw_data = ಮೌಲ್ಯ;
  ಮೌಲ್ಯ = build_int_cst (integer_type_ಗಂಟು,
			 RAW_DATA_UCHAR_ELT (*raw_data, 0));
  ++RAW_DATA_POINTER (*raw_data);
  --RAW_DATA_LENGTH (*raw_data);
  ಪ್ರತ್ಯಾಗಮ ಮೌಲ್ಯ;
}

/* Return non-zero if c_parser_initval should attempt to optimize
   large initializers into RAW_DATA_CST.  In that case return how
   many elements to optimize at most.  */

unsigned
c_maybe_optimize_large_byte_initializer (ಶೂನ್ಯ)
{
  ಯದಿ (!constructor_type
      || ವೃಕ್ಷ_CODE (constructor_type) != ARRAY_TYPE
      || constructor_ರಾಶಿ->implicit)
    ಪ್ರತ್ಯಾಗಮ 0;
  ವೃಕ್ಷ elttype = TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (constructor_type));
  ಯದಿ (ವೃಕ್ಷ_CODE (elttype) != INTEGER_TYPE
      && ವೃಕ್ಷ_CODE (elttype) != BITINT_TYPE)
    ಪ್ರತ್ಯಾಗಮ 0;
  ಯದಿ (TYPE_PRECISION (elttype) != CHAR_BIT
      || constructor_ರಾಶಿ->replacement_ಮೌಲ್ಯ.ಮೌಲ್ಯ
      || (COMPLETE_TYPE_P (constructor_type)
	  && !poly_int_ವೃಕ್ಷ_p (TYPE_SIZE (constructor_type)))
      || constructor_range_ರಾಶಿ)
    ಪ್ರತ್ಯಾಗಮ 0;
  ಯದಿ (constructor_max_index == NULL_ವೃಕ್ಷ)
    ಪ್ರತ್ಯಾಗಮ INT_MAX;
  ಯದಿ (ವೃಕ್ಷ_int_cst_le (constructor_max_index, constructor_index)
      || integer_all_onesp (constructor_max_index))
    ಪ್ರತ್ಯಾಗಮ 0;
  widest_int w = wi::to_widest (constructor_max_index);
  w -= wi::to_widest (constructor_index);
  w += 1;
  ಯದಿ (w < 64)
    ಪ್ರತ್ಯಾಗಮ 0;
  ಯದಿ (w > INT_MAX)
    ಪ್ರತ್ಯಾಗಮ INT_MAX;
  ಪ್ರತ್ಯಾಗಮ w.to_uhwi ();
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

ಶೂನ್ಯ
process_init_element (location_t loc, ಸಂರಚನಾ c_ಅಭಿವ್ಯಕ್ತಿ ಮೌಲ್ಯ, ತಾರ್ಕಿಕ implicit,
		      ಸಂರಚನಾ obstack * braced_init_obstack)
{
  ವೃಕ್ಷ orig_ಮೌಲ್ಯ = ಮೌಲ್ಯ.ಮೌಲ್ಯ;
  ಪೂರ್ಣಾಙ್ಕ string_flag
    = (orig_ಮೌಲ್ಯ != NULL_ವೃಕ್ಷ && ವೃಕ್ಷ_CODE (orig_ಮೌಲ್ಯ) == STRING_CST);
  ತಾರ್ಕಿಕ strict_string = ಮೌಲ್ಯ.original_code == STRING_CST;
  ತಾರ್ಕಿಕ was_designated = designator_depth != 0;
  ವೃಕ್ಷ raw_data = NULL_ವೃಕ್ಷ;

retry:
  designator_depth = 0;
  designator_erroneous = 0;

  ಯದಿ (!implicit && ಮೌಲ್ಯ.ಮೌಲ್ಯ && !integer_zerop (ಮೌಲ್ಯ.ಮೌಲ್ಯ))
    constructor_zeroinit = 0;

  /* Handle superfluous braces around string cst as in
     char x[] = {"foo"}; */
  ಯದಿ (constructor_type
      && !was_designated
      && ವೃಕ್ಷ_CODE (constructor_type) == ARRAY_TYPE
      && INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (constructor_type))
      && integer_zerop (constructor_unfilled_index))
    {
      ಯದಿ (constructor_ರಾಶಿ->replacement_ಮೌಲ್ಯ.ಮೌಲ್ಯ)
	{
	  error_init (loc, "excess elements in %qT initializer", constructor_type);
	  ಪ್ರತ್ಯಾಗಮ;
	}
      ಅನ್ಯಥಾ ಯದಿ (string_flag)
	{
	  constructor_ರಾಶಿ->replacement_ಮೌಲ್ಯ = ಮೌಲ್ಯ;
	  ಪ್ರತ್ಯಾಗಮ;
	}
    }

  ಯದಿ (constructor_ರಾಶಿ->replacement_ಮೌಲ್ಯ.ಮೌಲ್ಯ != NULL_ವೃಕ್ಷ)
    {
      error_init (loc, "excess elements in struct initializer");
      ಪ್ರತ್ಯಾಗಮ;
    }

  /* Ignore elements of a brace group if it is entirely superfluous
     and has already been diagnosed, or if the type is erroneous.  */
  ಯದಿ (constructor_type == NULL_ವೃಕ್ಷ || constructor_type == error_mark_ಗಂಟು)
    ಪ್ರತ್ಯಾಗಮ;

  /* Ignore elements of an initializer for a variable-size type.
     Those are diagnosed in the parser (empty initializer braces are OK).  */
  ಯದಿ (COMPLETE_TYPE_P (constructor_type)
      && !poly_int_ವೃಕ್ಷ_p (TYPE_SIZE (constructor_type)))
    ಪ್ರತ್ಯಾಗಮ;

  ಯದಿ (!implicit && warn_designated_init && !was_designated
      && ವೃಕ್ಷ_CODE (constructor_type) == RECORD_TYPE
      && lookup_attribute ("designated_init",
			   TYPE_ATTRIBUTES (constructor_type)))
    warning_init (loc,
		  OPT_Wdesignated_init,
		  "positional initialization of field "
		  "in %<struct%> declared with %<designated_init%> attribute");

  /* If we've exhausted any levels that didn't have braces,
     pop them now.  */
  ಯಾವತ್ (constructor_ರಾಶಿ->implicit)
    {
      ಯದಿ (RECORD_OR_UNION_TYPE_P (constructor_type)
	  && constructor_fields == NULL_ವೃಕ್ಷ)
	process_init_element (loc,
			      ತೆಗೆ_init_level (loc, 1, braced_init_obstack,
					      last_init_list_comma),
			      ಸತ್ಯ, braced_init_obstack);
      ಅನ್ಯಥಾ ಯದಿ ((ವೃಕ್ಷ_CODE (constructor_type) == ARRAY_TYPE
		|| gnu_vector_type_p (constructor_type))
	       && constructor_max_index
	       && ವೃಕ್ಷ_int_cst_lt (constructor_max_index,
				   constructor_index))
	process_init_element (loc,
			      ತೆಗೆ_init_level (loc, 1, braced_init_obstack,
					      last_init_list_comma),
			      ಸತ್ಯ, braced_init_obstack);
      ಅನ್ಯಥಾ
	ಭಙ್ಗ;
    }

  /* In the case of [LO ... HI] = VALUE, only evaluate VALUE once.  */
  ಯದಿ (constructor_range_ರಾಶಿ)
    {
      /* If value is a compound literal and we'll be just using its
	 content, don't put it into a SAVE_EXPR.  */
      ಯದಿ (ವೃಕ್ಷ_CODE (ಮೌಲ್ಯ.ಮೌಲ್ಯ) != COMPOUND_LITERAL_ಅಭಿವ್ಯಕ್ತಿ
	  || !require_constant_ಮೌಲ್ಯ)
	{
	  ವೃಕ್ಷ semantic_type = NULL_ವೃಕ್ಷ;
	  ಯದಿ (ವೃಕ್ಷ_CODE (ಮೌಲ್ಯ.ಮೌಲ್ಯ) == EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ)
	    {
	      semantic_type = ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ.ಮೌಲ್ಯ);
	      ಮೌಲ್ಯ.ಮೌಲ್ಯ = ವೃಕ್ಷ_OPERAND (ಮೌಲ್ಯ.ಮೌಲ್ಯ, 0);
	    }
	  ಮೌಲ್ಯ.ಮೌಲ್ಯ = save_ಅಭಿವ್ಯಕ್ತಿ (ಮೌಲ್ಯ.ಮೌಲ್ಯ);
	  ಯದಿ (semantic_type)
	    ಮೌಲ್ಯ.ಮೌಲ್ಯ = build1 (EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ, semantic_type,
				  ಮೌಲ್ಯ.ಮೌಲ್ಯ);
	}
    }

  ಯಾವತ್ (1)
    {
      ಯದಿ (ವೃಕ್ಷ_CODE (constructor_type) == RECORD_TYPE)
	{
	  ವೃಕ್ಷ fieldtype;
	  ಗಣನಾ ವೃಕ್ಷ_code fieldcode;

	  ಯದಿ (constructor_fields == NULL_ವೃಕ್ಷ)
	    {
	      pedwarn_init (loc, 0, "excess elements in struct initializer");
	      ಭಙ್ಗ;
	    }

	  fieldtype = ವೃಕ್ಷ_TYPE (constructor_fields);
	  ಯದಿ (fieldtype != error_mark_ಗಂಟು)
	    fieldtype = TYPE_MAIN_VARIANT (fieldtype);
	  fieldcode = ವೃಕ್ಷ_CODE (fieldtype);

	  /* Error for non-static initialization of a flexible array member.  */
	  ಯದಿ (fieldcode == ARRAY_TYPE
	      && !require_constant_ಮೌಲ್ಯ
	      && TYPE_SIZE (fieldtype) == NULL_ವೃಕ್ಷ
	      && DECL_CHAIN (constructor_fields) == NULL_ವೃಕ್ಷ)
	    {
	      error_init (loc, "non-static initialization of a flexible "
			  "array member");
	      ಭಙ್ಗ;
	    }

	  /* Error for initialization of a flexible array member with
	     a string constant if the structure is in an array.  E.g.:
	     struct S { int x; char y[]; };
	     struct S s[] = { { 1, "foo" } };
	     is invalid.  */
	  ಯದಿ (string_flag
	      && fieldcode == ARRAY_TYPE
	      && constructor_depth > 1
	      && TYPE_SIZE (fieldtype) == NULL_ವೃಕ್ಷ
	      && DECL_CHAIN (constructor_fields) == NULL_ವೃಕ್ಷ)
	    {
	      ತಾರ್ಕಿಕ in_array_p = ಅಸತ್ಯ;
	      ಪ್ರತಿ (ಸಂರಚನಾ constructor_ರಾಶಿ *p = constructor_ರಾಶಿ;
		   p && p->type; p = p->next)
		ಯದಿ (ವೃಕ್ಷ_CODE (p->type) == ARRAY_TYPE)
		  {
		    in_array_p = ಸತ್ಯ;
		    ಭಙ್ಗ;
		  }
	      ಯದಿ (in_array_p)
		{
		  error_init (loc, "initialization of flexible array "
			      "member in a nested context");
		  ಭಙ್ಗ;
		}
	    }

	  /* Accept a string constant to initialize a subarray.  */
	  ಯದಿ (ಮೌಲ್ಯ.ಮೌಲ್ಯ != NULL_ವೃಕ್ಷ
	      && fieldcode == ARRAY_TYPE
	      && INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (fieldtype))
	      && string_flag)
	    ಮೌಲ್ಯ.ಮೌಲ್ಯ = orig_ಮೌಲ್ಯ;
	  /* Otherwise, if we have come to a subaggregate,
	     and we don't have an element of its type, push into it.  */
	  ಅನ್ಯಥಾ ಯದಿ (ಮೌಲ್ಯ.ಮೌಲ್ಯ != NULL_ವೃಕ್ಷ
		   && initialize_elementwise_p (fieldtype, ಮೌಲ್ಯ.ಮೌಲ್ಯ))
	    {
	      ತಳ್ಳು_init_level (loc, 1, braced_init_obstack);
	      ಅನುವರ್ತ;
	    }

	  ಮೌಲ್ಯ.ಮೌಲ್ಯ = maybe_split_raw_data (ಮೌಲ್ಯ.ಮೌಲ್ಯ, &raw_data);
	  ಯದಿ (ಮೌಲ್ಯ.ಮೌಲ್ಯ)
	    {
	      ತಳ್ಳು_member_name (constructor_fields);
	      output_init_element (loc, ಮೌಲ್ಯ.ಮೌಲ್ಯ, ಮೌಲ್ಯ.original_type,
				   strict_string, fieldtype,
				   constructor_fields, ಸತ್ಯ, implicit,
				   braced_init_obstack);
	      RESTORE_SPELLING_DEPTH (constructor_depth);
	    }
	  ಅನ್ಯಥಾ
	    /* Do the bookkeeping for an element that was
	       directly output as a constructor.  */
	    {
	      /* For a record, keep track of end position of last field.  */
	      ಯದಿ (DECL_SIZE (constructor_fields))
		constructor_bit_index
		  = size_binop_loc (ಒಳಹರಿವು_location, PLUS_ಅಭಿವ್ಯಕ್ತಿ,
				    bit_position (constructor_fields),
				    DECL_SIZE (constructor_fields));

	      /* If the current field was the first one not yet written out,
		 it isn't now, so update.  */
	      ಯದಿ (constructor_unfilled_fields == constructor_fields)
		{
		  constructor_unfilled_fields = DECL_CHAIN (constructor_fields);
		  /* Skip any nameless bit fields.  */
		  ಯಾವತ್ (constructor_unfilled_fields != 0
			 && (DECL_UNNAMED_BIT_FIELD
			     (constructor_unfilled_fields)))
		    constructor_unfilled_fields =
		      DECL_CHAIN (constructor_unfilled_fields);
		}
	    }

	  constructor_fields = DECL_CHAIN (constructor_fields);
	  /* Skip any nameless bit fields at the beginning.  */
	  ಯಾವತ್ (constructor_fields != NULL_ವೃಕ್ಷ
		 && DECL_UNNAMED_BIT_FIELD (constructor_fields))
	    constructor_fields = DECL_CHAIN (constructor_fields);
	}
      ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (constructor_type) == UNION_TYPE)
	{
	  ವೃಕ್ಷ fieldtype;
	  ಗಣನಾ ವೃಕ್ಷ_code fieldcode;

	  ಯದಿ (constructor_fields == NULL_ವೃಕ್ಷ)
	    {
	      pedwarn_init (loc, 0,
			    "excess elements in union initializer");
	      ಭಙ್ಗ;
	    }

	  fieldtype = ವೃಕ್ಷ_TYPE (constructor_fields);
	  ಯದಿ (fieldtype != error_mark_ಗಂಟು)
	    fieldtype = TYPE_MAIN_VARIANT (fieldtype);
	  fieldcode = ವೃಕ್ಷ_CODE (fieldtype);

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
	  ಯದಿ (!in_system_header_at (ಒಳಹರಿವು_location) && !constructor_designated
	      && !(ಮೌಲ್ಯ.ಮೌಲ್ಯ && (integer_zerop (ಮೌಲ್ಯ.ಮೌಲ್ಯ)
				   || real_zerop (ಮೌಲ್ಯ.ಮೌಲ್ಯ))))
	    warning (OPT_Wtraditional, "traditional C rejects initialization "
		     "of unions");

	  /* Error for non-static initialization of a flexible array member.  */
	  ಯದಿ (fieldcode == ARRAY_TYPE
	      && !require_constant_ಮೌಲ್ಯ
	      && TYPE_SIZE (fieldtype) == NULL_ವೃಕ್ಷ)
	    {
	      error_init (loc, "non-static initialization of a flexible "
			  "array member");
	      ಭಙ್ಗ;
	    }

	  /* Error for initialization of a flexible array member with
	     a string constant if the structure is in an array.  E.g.:
	     union U { int x; char y[]; };
	     union U s[] = { { 1, "foo" } };
	     is invalid.  */
	  ಯದಿ (string_flag
	      && fieldcode == ARRAY_TYPE
	      && constructor_depth > 1
	      && TYPE_SIZE (fieldtype) == NULL_ವೃಕ್ಷ)
	    {
	      ತಾರ್ಕಿಕ in_array_p = ಅಸತ್ಯ;
	      ಪ್ರತಿ (ಸಂರಚನಾ constructor_ರಾಶಿ *p = constructor_ರಾಶಿ;
		   p && p->type; p = p->next)
		ಯದಿ (ವೃಕ್ಷ_CODE (p->type) == ARRAY_TYPE)
		  {
		    in_array_p = ಸತ್ಯ;
		    ಭಙ್ಗ;
		  }
	      ಯದಿ (in_array_p)
		{
		  error_init (loc, "initialization of flexible array "
			      "member in a nested context");
		  ಭಙ್ಗ;
		}
	    }

	  /* Accept a string constant to initialize a subarray.  */
	  ಯದಿ (ಮೌಲ್ಯ.ಮೌಲ್ಯ != NULL_ವೃಕ್ಷ
	      && fieldcode == ARRAY_TYPE
	      && INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (fieldtype))
	      && string_flag)
	    ಮೌಲ್ಯ.ಮೌಲ್ಯ = orig_ಮೌಲ್ಯ;
	  /* Otherwise, if we have come to a subaggregate,
	     and we don't have an element of its type, push into it.  */
	  ಅನ್ಯಥಾ ಯದಿ (ಮೌಲ್ಯ.ಮೌಲ್ಯ != NULL_ವೃಕ್ಷ
		   && initialize_elementwise_p (fieldtype, ಮೌಲ್ಯ.ಮೌಲ್ಯ))
	    {
	      ತಳ್ಳು_init_level (loc, 1, braced_init_obstack);
	      ಅನುವರ್ತ;
	    }

	  ಮೌಲ್ಯ.ಮೌಲ್ಯ = maybe_split_raw_data (ಮೌಲ್ಯ.ಮೌಲ್ಯ, &raw_data);
	  ಯದಿ (ಮೌಲ್ಯ.ಮೌಲ್ಯ)
	    {
	      ತಳ್ಳು_member_name (constructor_fields);
	      output_init_element (loc, ಮೌಲ್ಯ.ಮೌಲ್ಯ, ಮೌಲ್ಯ.original_type,
				   strict_string, fieldtype,
				   constructor_fields, ಸತ್ಯ, implicit,
				   braced_init_obstack);
	      RESTORE_SPELLING_DEPTH (constructor_depth);
	    }
	  ಅನ್ಯಥಾ
	    /* Do the bookkeeping for an element that was
	       directly output as a constructor.  */
	    {
	      constructor_bit_index = DECL_SIZE (constructor_fields);
	      constructor_unfilled_fields = DECL_CHAIN (constructor_fields);
	    }

	  constructor_fields = NULL_ವೃಕ್ಷ;
	}
      ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (constructor_type) == ARRAY_TYPE)
	{
	  ವೃಕ್ಷ elttype = TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (constructor_type));
	  ಗಣನಾ ವೃಕ್ಷ_code eltcode = ವೃಕ್ಷ_CODE (elttype);

	  /* Accept a string constant to initialize a subarray.  */
	  ಯದಿ (ಮೌಲ್ಯ.ಮೌಲ್ಯ != NULL_ವೃಕ್ಷ
	      && eltcode == ARRAY_TYPE
	      && INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (elttype))
	      && string_flag)
	    ಮೌಲ್ಯ.ಮೌಲ್ಯ = orig_ಮೌಲ್ಯ;
	  /* Otherwise, if we have come to a subaggregate,
	     and we don't have an element of its type, push into it.  */
	  ಅನ್ಯಥಾ ಯದಿ (ಮೌಲ್ಯ.ಮೌಲ್ಯ != NULL_ವೃಕ್ಷ
		   && initialize_elementwise_p (elttype, ಮೌಲ್ಯ.ಮೌಲ್ಯ))
	    {
	      ತಳ್ಳು_init_level (loc, 1, braced_init_obstack);
	      ಅನುವರ್ತ;
	    }

	  ಯದಿ (constructor_max_index != NULL_ವೃಕ್ಷ
	      && (ವೃಕ್ಷ_int_cst_lt (constructor_max_index, constructor_index)
		  || integer_all_onesp (constructor_max_index))
	      /* For VLA we got an error already.  */
	      && !C_TYPE_VARIABLE_SIZE (constructor_type))
	    {
	      pedwarn_init (loc, 0,
			    "excess elements in array initializer");
	      ಭಙ್ಗ;
	    }

	  ಯದಿ (ಮೌಲ್ಯ.ಮೌಲ್ಯ
	      && ವೃಕ್ಷ_CODE (ಮೌಲ್ಯ.ಮೌಲ್ಯ) == RAW_DATA_CST
	      && RAW_DATA_LENGTH (ಮೌಲ್ಯ.ಮೌಲ್ಯ) > 1
	      && (ವೃಕ್ಷ_CODE (elttype) == INTEGER_TYPE
		  || ವೃಕ್ಷ_CODE (elttype) == BITINT_TYPE)
	      && TYPE_PRECISION (elttype) == CHAR_BIT
	      && (constructor_max_index == NULL_ವೃಕ್ಷ
		  || ವೃಕ್ಷ_int_cst_lt (constructor_index,
				      constructor_max_index)))
	    {
	      unsigned ಪೂರ್ಣಾಙ್ಕ len = RAW_DATA_LENGTH (ಮೌಲ್ಯ.ಮೌಲ್ಯ);
	      ಯದಿ (constructor_max_index)
		{
		  widest_int w = wi::to_widest (constructor_max_index);
		  w -= wi::to_widest (constructor_index);
		  w += 1;
		  ಯದಿ (w < len)
		    len = w.to_uhwi ();
		}
	      ಯದಿ (len < (unsigned) RAW_DATA_LENGTH (ಮೌಲ್ಯ.ಮೌಲ್ಯ))
		{
		  raw_data = copy_ಗಂಟು (ಮೌಲ್ಯ.ಮೌಲ್ಯ);
		  RAW_DATA_LENGTH (raw_data) -= len;
		  RAW_DATA_POINTER (raw_data) += len;
		  RAW_DATA_LENGTH (ಮೌಲ್ಯ.ಮೌಲ್ಯ) = len;
		}
	      ವೃಕ್ಷ_TYPE (ಮೌಲ್ಯ.ಮೌಲ್ಯ) = elttype;
	      ತಳ್ಳು_array_bounds (ವೃಕ್ಷ_to_uhwi (constructor_index));
	      output_init_element (loc, ಮೌಲ್ಯ.ಮೌಲ್ಯ, ಮೌಲ್ಯ.original_type,
				   ಅಸತ್ಯ, elttype, constructor_index, ಸತ್ಯ,
				   implicit, braced_init_obstack);
	      RESTORE_SPELLING_DEPTH (constructor_depth);
	      constructor_index
		= size_binop_loc (ಒಳಹರಿವು_location, PLUS_ಅಭಿವ್ಯಕ್ತಿ,
				  constructor_index, bitsize_int (len));
	    }
	  ಅನ್ಯಥಾ
	    {
	      ಮೌಲ್ಯ.ಮೌಲ್ಯ = maybe_split_raw_data (ಮೌಲ್ಯ.ಮೌಲ್ಯ, &raw_data);
	      /* Now output the actual element.  */
	      ಯದಿ (ಮೌಲ್ಯ.ಮೌಲ್ಯ)
		{
		  ತಳ್ಳು_array_bounds (ವೃಕ್ಷ_to_uhwi (constructor_index));
		  output_init_element (loc, ಮೌಲ್ಯ.ಮೌಲ್ಯ, ಮೌಲ್ಯ.original_type,
				       strict_string, elttype,
				       constructor_index, ಸತ್ಯ, implicit,
				       braced_init_obstack);
		  RESTORE_SPELLING_DEPTH (constructor_depth);
		}

	      constructor_index
		= size_binop_loc (ಒಳಹರಿವು_location, PLUS_ಅಭಿವ್ಯಕ್ತಿ,
				  constructor_index, bitsize_one_ಗಂಟು);

	      ಯದಿ (!ಮೌಲ್ಯ.ಮೌಲ್ಯ)
		/* If we are doing the bookkeeping for an element that was
		   directly output as a constructor, we must update
		   constructor_unfilled_index.  */
		constructor_unfilled_index = constructor_index;
	    }
	}
      ಅನ್ಯಥಾ ಯದಿ (gnu_vector_type_p (constructor_type))
	{
	  ವೃಕ್ಷ elttype = TYPE_MAIN_VARIANT (ವೃಕ್ಷ_TYPE (constructor_type));

	  /* Do a basic check of initializer size.  Note that vectors
	     may not always have a fixed size derived from their type.  */
	  ಯದಿ (maybe_lt (ವೃಕ್ಷ_to_poly_uint64 (constructor_max_index),
			ವೃಕ್ಷ_to_poly_uint64 (constructor_index)))
	    {
	      /* Diagose VLA out-of-bounds as errors.  */
	      ಯದಿ (ವೃಕ್ಷ_to_poly_uint64 (constructor_max_index).is_constant())
		pedwarn_init (loc, 0,
			      "excess elements in vector initializer");
	      ಅನ್ಯಥಾ
		error_init (loc, "excess elements in vector initializer");

	      ಭಙ್ಗ;
	    }

	  ಮೌಲ್ಯ.ಮೌಲ್ಯ = maybe_split_raw_data (ಮೌಲ್ಯ.ಮೌಲ್ಯ, &raw_data);
	  /* Now output the actual element.  */
	  ಯದಿ (ಮೌಲ್ಯ.ಮೌಲ್ಯ)
	    {
	      ಯದಿ (ವೃಕ್ಷ_CODE (ಮೌಲ್ಯ.ಮೌಲ್ಯ) == VECTOR_CST)
		elttype = TYPE_MAIN_VARIANT (constructor_type);
	      output_init_element (loc, ಮೌಲ್ಯ.ಮೌಲ್ಯ, ಮೌಲ್ಯ.original_type,
				   strict_string, elttype,
				   constructor_index, ಸತ್ಯ, implicit,
				   braced_init_obstack);
	    }

	  constructor_index
	    = size_binop_loc (ಒಳಹರಿವು_location,
			      PLUS_ಅಭಿವ್ಯಕ್ತಿ, constructor_index, bitsize_one_ಗಂಟು);

	  ಯದಿ (!ಮೌಲ್ಯ.ಮೌಲ್ಯ)
	    /* If we are doing the bookkeeping for an element that was
	       directly output as a constructor, we must update
	       constructor_unfilled_index.  */
	    constructor_unfilled_index = constructor_index;
	}

      /* Handle the sole element allowed in a braced initializer
	 for a scalar variable.  */
      ಅನ್ಯಥಾ ಯದಿ (constructor_type != error_mark_ಗಂಟು
	       && constructor_fields == NULL_ವೃಕ್ಷ)
	{
	  pedwarn_init (loc, 0,
			"excess elements in scalar initializer");
	  ಭಙ್ಗ;
	}
      ಅನ್ಯಥಾ
	{
	  ಮೌಲ್ಯ.ಮೌಲ್ಯ = maybe_split_raw_data (ಮೌಲ್ಯ.ಮೌಲ್ಯ, &raw_data);
	  ಯದಿ (ಮೌಲ್ಯ.ಮೌಲ್ಯ)
	    output_init_element (loc, ಮೌಲ್ಯ.ಮೌಲ್ಯ, ಮೌಲ್ಯ.original_type,
				 strict_string, constructor_type,
				 NULL_ವೃಕ್ಷ, ಸತ್ಯ, implicit,
				 braced_init_obstack);
	  constructor_fields = NULL_ವೃಕ್ಷ;
	}

      /* Handle range initializers either at this level or anywhere higher
	 in the designator stack.  */
      ಯದಿ (constructor_range_ರಾಶಿ)
	{
	  ಸಂರಚನಾ constructor_range_ರಾಶಿ *p, *range_ರಾಶಿ;
	  ಪೂರ್ಣಾಙ್ಕ finish = 0;

	  range_ರಾಶಿ = constructor_range_ರಾಶಿ;
	  constructor_range_ರಾಶಿ = 0;
	  ಯಾವತ್ (constructor_ರಾಶಿ != range_ರಾಶಿ->ರಾಶಿ)
	    {
	      gcc_assert (constructor_ರಾಶಿ->implicit);
	      process_init_element (loc,
				    ತೆಗೆ_init_level (loc, 1,
						    braced_init_obstack,
						    last_init_list_comma),
				    ಸತ್ಯ, braced_init_obstack);
	    }
	  ಪ್ರತಿ (p = range_ರಾಶಿ;
	       !p->range_end || ವೃಕ್ಷ_int_cst_equal (p->index, p->range_end);
	       p = p->prev)
	    {
	      gcc_assert (constructor_ರಾಶಿ->implicit);
	      process_init_element (loc,
				    ತೆಗೆ_init_level (loc, 1,
						    braced_init_obstack,
						    last_init_list_comma),
				    ಸತ್ಯ, braced_init_obstack);
	    }

	  p->index = size_binop_loc (ಒಳಹರಿವು_location,
				     PLUS_ಅಭಿವ್ಯಕ್ತಿ, p->index, bitsize_one_ಗಂಟು);
	  ಯದಿ (ವೃಕ್ಷ_int_cst_equal (p->index, p->range_end) && !p->prev)
	    finish = 1;

	  ಯಾವತ್ (1)
	    {
	      constructor_index = p->index;
	      constructor_fields = p->fields;
	      ಯದಿ (finish && p->range_end && p->index == p->range_start)
		{
		  finish = 0;
		  p->prev = 0;
		}
	      p = p->next;
	      ಯದಿ (!p)
		ಭಙ್ಗ;
	      finish_implicit_inits (loc, braced_init_obstack);
	      ತಳ್ಳು_init_level (loc, 2, braced_init_obstack);
	      p->ರಾಶಿ = constructor_ರಾಶಿ;
	      ಯದಿ (p->range_end && ವೃಕ್ಷ_int_cst_equal (p->index, p->range_end))
		p->index = p->range_start;
	    }

	  ಯದಿ (!finish)
	    constructor_range_ರಾಶಿ = range_ರಾಶಿ;
	  ಅನುವರ್ತ;
	}

      ಭಙ್ಗ;
    }

  constructor_range_ರಾಶಿ = 0;

  ಯದಿ (raw_data && RAW_DATA_LENGTH (raw_data))
    {
      gcc_assert (!string_flag && !was_designated);
      ಮೌಲ್ಯ.ಮೌಲ್ಯ = raw_data;
      raw_data = NULL_ವೃಕ್ಷ;
      ಗಚ್ಛ retry;
    }
}

/* Build a complete asm-statement, whose components are a CV_QUALIFIER
   (guaranteed to be 'volatile' or null) and ARGS (represented using
   an ASM_EXPR node).  */
ವೃಕ್ಷ
build_asm_stmt (ತಾರ್ಕಿಕ is_volatile, ವೃಕ್ಷ args)
{
  ಯದಿ (is_volatile)
    ASM_VOLATILE_P (args) = 1;
  ಪ್ರತ್ಯಾಗಮ add_stmt (args);
}

/* Build an asm-expr, whose components are a STRING, some OUTPUTS,
   some INPUTS, and some CLOBBERS.  The latter three may be NULL.
   SIMPLE indicates whether there was anything at all after the
   string in the asm expression -- asm("blah") and asm("blah" : )
   are subtly different.  We use a ASM_EXPR node to represent this.
   LOC is the location of the asm, and IS_INLINE says whether this
   is asm inline.  */
ವೃಕ್ಷ
build_asm_ಅಭಿವ್ಯಕ್ತಿ (location_t loc, ವೃಕ್ಷ string, ವೃಕ್ಷ outputs, ವೃಕ್ಷ inputs,
		ವೃಕ್ಷ clobbers, ವೃಕ್ಷ labels, ತಾರ್ಕಿಕ simple, ತಾರ್ಕಿಕ is_inline)
{
  ವೃಕ್ಷ tail;
  ವೃಕ್ಷ args;
  ಪೂರ್ಣಾಙ್ಕ i;
  ಧ್ರುವ ವರ್ಣ *constraint;
  ಧ್ರುವ ವರ್ಣ **oconstraints;
  ತಾರ್ಕಿಕ allows_mem, allows_reg, is_inout;
  ಪೂರ್ಣಾಙ್ಕ ninputs, noutputs;

  ninputs = list_length (inputs);
  noutputs = list_length (outputs);
  oconstraints = (ಧ್ರುವ ವರ್ಣ **) alloca (noutputs * ಪರಿಮಾಣ (ಧ್ರುವ ವರ್ಣ *));

  string = resolve_asm_operand_names (string, outputs, inputs, labels);

  /* Remove output conversions that change the type but not the mode.  */
  ಪ್ರತಿ (i = 0, tail = outputs; tail; ++i, tail = ವೃಕ್ಷ_CHAIN (tail))
    {
      ವೃಕ್ಷ output = ವೃಕ್ಷ_ಮೌಲ್ಯ (tail);

      output = c_fully_fold (output, ಅಸತ್ಯ, ರಿಕ್ತ, ಸತ್ಯ);

      /* ??? Really, this should not be here.  Users should be using a
	 proper lvalue, dammit.  But there's a long history of using casts
	 in the output operands.  In cases like longlong.h, this becomes a
	 primitive form of typechecking -- if the cast can be removed, then
	 the output operand had a type of the proper width; otherwise we'll
	 get an error.  Gross, but ...  */
      STRIP_NOPS (output);

      ಯದಿ (!lvalue_or_else (loc, output, lv_asm))
	output = error_mark_ಗಂಟು;

      ಯದಿ (output != error_mark_ಗಂಟು
	  && (ವೃಕ್ಷ_READONLY (output)
	      || TYPE_READONLY (ವೃಕ್ಷ_TYPE (output))
	      || (RECORD_OR_UNION_TYPE_P (ವೃಕ್ಷ_TYPE (output))
		  && C_TYPE_FIELDS_READONLY (ವೃಕ್ಷ_TYPE (output)))))
	readonly_error (loc, output, lv_asm);

      constraint = ವೃಕ್ಷ_STRING_POINTER (ವೃಕ್ಷ_ಮೌಲ್ಯ (ವೃಕ್ಷ_PURPOSE (tail)));
      oconstraints[i] = constraint;

      ಯದಿ (parse_output_constraint (&constraint, i, ninputs, noutputs,
				   &allows_mem, &allows_reg, &is_inout,
				   nullptr))
	{
	  /* If the operand is going to end up in memory,
	     mark it addressable.  */
	  ಯದಿ (!allows_reg && !c_mark_addressable (output))
	    output = error_mark_ಗಂಟು;
	  ಯದಿ (!(!allows_reg && allows_mem)
	      && output != error_mark_ಗಂಟು
	      && VOID_TYPE_P (ವೃಕ್ಷ_TYPE (output)))
	    {
	      error_at (loc, "invalid use of void expression");
	      output = error_mark_ಗಂಟು;
	    }
	  ಯದಿ (allows_reg && current_function_decl == NULL_ವೃಕ್ಷ)
	    {
	      error_at (loc, "constraint allows registers outside of "
			     "a function");
	      output = error_mark_ಗಂಟು;
	    }
	}
      ಅನ್ಯಥಾ
	output = error_mark_ಗಂಟು;

      ಯದಿ (current_function_decl == NULL_ವೃಕ್ಷ && output != error_mark_ಗಂಟು)
	{
	  ಯದಿ (ವೃಕ್ಷ_SIDE_EFFECTS (output))
	    {
	      error_at (loc, "side-effects in output operand outside "
			     "of a function");
	      output = error_mark_ಗಂಟು;
	    }
	  ಅನ್ಯಥಾ
	    {
	      ವೃಕ್ಷ addr = build_unary_op (loc, ADDR_ಅಭಿವ್ಯಕ್ತಿ, output, ಅಸತ್ಯ);
	      ಯದಿ (addr == error_mark_ಗಂಟು)
		output = error_mark_ಗಂಟು;
	      ಅನ್ಯಥಾ ಯದಿ (!initializer_constant_valid_p (addr, ವೃಕ್ಷ_TYPE (addr)))
		{
		  error_at (loc, "output operand outside of a function is not "
				 "constant");
		  output = error_mark_ಗಂಟು;
		}
	    }
	}
      ಅನ್ಯಥಾ ಯದಿ (output != error_mark_ಗಂಟು && strstr (constraint, "-"))
	{
	  error_at (loc, "%<-%> modifier used inside of a function");
	  output = error_mark_ಗಂಟು;
	}

      ವೃಕ್ಷ_ಮೌಲ್ಯ (tail) = output;
    }

  ಪ್ರತಿ (i = 0, tail = inputs; tail; ++i, tail = ವೃಕ್ಷ_CHAIN (tail))
    {
      ವೃಕ್ಷ ಒಳಹರಿವು;

      constraint = ವೃಕ್ಷ_STRING_POINTER (ವೃಕ್ಷ_ಮೌಲ್ಯ (ವೃಕ್ಷ_PURPOSE (tail)));
      ಒಳಹರಿವು = ವೃಕ್ಷ_ಮೌಲ್ಯ (tail);

      ಯದಿ (parse_ಒಳಹರಿವು_constraint (&constraint, i, ninputs, noutputs, 0,
				  oconstraints, &allows_mem, &allows_reg,
				  nullptr))
	{
	  /* If the operand is going to end up in memory,
	     mark it addressable.  */
	  ಯದಿ (!allows_reg && allows_mem)
	    {
	      ಒಳಹರಿವು = c_fully_fold (ಒಳಹರಿವು, ಅಸತ್ಯ, ರಿಕ್ತ, ಸತ್ಯ);

	      /* Strip the nops as we allow this case.  FIXME, this really
		 should be rejected or made deprecated.  */
	      STRIP_NOPS (ಒಳಹರಿವು);
	      ಯದಿ (!c_mark_addressable (ಒಳಹರಿವು))
		ಒಳಹರಿವು = error_mark_ಗಂಟು;
	    }
	  ಅನ್ಯಥಾ
	    {
	      ಒಳಹರಿವು = c_fully_fold (convert_lvalue_to_rvalue (loc, ಒಳಹರಿವು,
							      ಸತ್ಯ, ಅಸತ್ಯ),
				    ಅಸತ್ಯ, ರಿಕ್ತ);

	      ಯದಿ (ಒಳಹರಿವು != error_mark_ಗಂಟು && VOID_TYPE_P (ವೃಕ್ಷ_TYPE (ಒಳಹರಿವು)))
		{
		  error_at (loc, "invalid use of void expression");
		  ಒಳಹರಿವು = error_mark_ಗಂಟು;
		}
	    }
	  ಯದಿ (allows_reg && current_function_decl == NULL_ವೃಕ್ಷ)
	    {
	      error_at (loc, "constraint allows registers outside of "
			     "a function");
	      ಒಳಹರಿವು = error_mark_ಗಂಟು;
	    }
	  ಯದಿ (constraint[0] == ':' && ಒಳಹರಿವು != error_mark_ಗಂಟು)
	    {
	      ವೃಕ್ಷ t = ಒಳಹರಿವು;
	      STRIP_NOPS (t);
	      ಯದಿ (ವೃಕ್ಷ_CODE (t) != ADDR_ಅಭಿವ್ಯಕ್ತಿ
		  || !(ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_OPERAND (t, 0)) == FUNCTION_DECL
		       || (VAR_P (ವೃಕ್ಷ_OPERAND (t, 0))
			   && is_global_var (ವೃಕ್ಷ_OPERAND (t, 0)))))
		{
		  error_at (loc, "%<:%> constraint operand is not address "
				 "of a function or non-automatic variable");
		  ಒಳಹರಿವು = error_mark_ಗಂಟು;
		}
	      ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_OPERAND (t, 0)) == FUNCTION_DECL)
		suppress_warning (ವೃಕ್ಷ_OPERAND (t, 0), OPT_Wunused);
	    }
	}
      ಅನ್ಯಥಾ
	ಒಳಹರಿವು = error_mark_ಗಂಟು;

      ಯದಿ (current_function_decl == NULL_ವೃಕ್ಷ && ಒಳಹರಿವು != error_mark_ಗಂಟು)
	{
	  ಯದಿ (ವೃಕ್ಷ_SIDE_EFFECTS (ಒಳಹರಿವು))
	    {
	      error_at (loc, "side-effects in input operand outside "
			     "of a function");
	      ಒಳಹರಿವು = error_mark_ಗಂಟು;
	    }
	  ಅನ್ಯಥಾ
	    {
	      ವೃಕ್ಷ tem = ಒಳಹರಿವು;
	      ಯದಿ (allows_mem && lvalue_p (ಒಳಹರಿವು))
		tem = build_unary_op (loc, ADDR_ಅಭಿವ್ಯಕ್ತಿ, ಒಳಹರಿವು, ಅಸತ್ಯ);
	      ಯದಿ (!initializer_constant_valid_p (tem, ವೃಕ್ಷ_TYPE (tem)))
		{
		  error_at (loc, "input operand outside of a function is not "
				 "constant");
		  ಒಳಹರಿವು = error_mark_ಗಂಟು;
		}
	    }
	}
      ಅನ್ಯಥಾ ಯದಿ (ಒಳಹರಿವು != error_mark_ಗಂಟು && strstr (constraint, "-"))
	{
	  error_at (loc, "%<-%> modifier used inside of a function");
	  ಒಳಹರಿವು = error_mark_ಗಂಟು;
	}

      ವೃಕ್ಷ_ಮೌಲ್ಯ (tail) = ಒಳಹರಿವು;
    }

  args = build_stmt (loc, ASM_ಅಭಿವ್ಯಕ್ತಿ, string, outputs, inputs, clobbers, labels);

  /* asm statements without outputs, including simple ones, are treated
     as volatile.  */
  ASM_BASIC_P (args) = simple;
  ASM_VOLATILE_P (args) = (noutputs == 0);
  ASM_INLINE_P (args) = is_inline;

  ಪ್ರತ್ಯಾಗಮ args;
}

/* Generate a goto statement to LABEL.  LOC is the location of the
   GOTO.  */

ವೃಕ್ಷ
c_finish_goto_label (location_t loc, ವೃಕ್ಷ label)
{
  ವೃಕ್ಷ decl = lookup_label_for_goto (loc, label);
  ಯದಿ (!decl)
    ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
  ವೃಕ್ಷ_USED (decl) = 1;
  mark_decl_used (decl, ಅಸತ್ಯ);
  {
    add_stmt (build_predict_ಅಭಿವ್ಯಕ್ತಿ (PRED_GOTO, NOT_TAKEN));
    ವೃಕ್ಷ t = build1 (GOTO_ಅಭಿವ್ಯಕ್ತಿ, void_type_ಗಂಟು, decl);
    SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (t, loc);
    ಪ್ರತ್ಯಾಗಮ add_stmt (t);
  }
}

/* Generate a computed goto statement to EXPR.  LOC is the location of
   the GOTO.  */

ವೃಕ್ಷ
c_finish_goto_ptr (location_t loc, c_ಅಭಿವ್ಯಕ್ತಿ val)
{
  ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ = val.ಮೌಲ್ಯ;
  ವೃಕ್ಷ t;
  pedwarn (loc, OPT_Wpedantic, "ISO C forbids %<goto *expr;%>");
  ಯದಿ (ಅಭಿವ್ಯಕ್ತಿ != error_mark_ಗಂಟು
      && !POINTER_TYPE_P (ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ))
      && !null_pointer_constant_p (ಅಭಿವ್ಯಕ್ತಿ))
    {
      error_at (val.get_location (),
		"computed goto must be pointer type");
      ಅಭಿವ್ಯಕ್ತಿ = build_zero_cst (ptr_type_ಗಂಟು);
    }
  ಅಭಿವ್ಯಕ್ತಿ = c_fully_fold (ಅಭಿವ್ಯಕ್ತಿ, ಅಸತ್ಯ, ರಿಕ್ತ);
  ಅಭಿವ್ಯಕ್ತಿ = convert (ptr_type_ಗಂಟು, ಅಭಿವ್ಯಕ್ತಿ);
  t = build1 (GOTO_ಅಭಿವ್ಯಕ್ತಿ, void_type_ಗಂಟು, ಅಭಿವ್ಯಕ್ತಿ);
  SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (t, loc);
  ಪ್ರತ್ಯಾಗಮ add_stmt (t);
}

/* Generate a C `return' statement.  RETVAL is the expression for what
   to return, or a null pointer for `return;' with no value.  LOC is
   the location of the return statement, or the location of the expression,
   if the statement has any.  If ORIGTYPE is not NULL_TREE, it
   is the original type of RETVAL.  MUSTTAIL_P indicates a musttail
   attribute.  */

ವೃಕ್ಷ
c_finish_return (location_t loc, ವೃಕ್ಷ retval, ವೃಕ್ಷ origtype, ತಾರ್ಕಿಕ musttail_p)
{
  ವೃಕ್ಷ valtype = ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (current_function_decl)), ret_stmt;
  ತಾರ್ಕಿಕ no_warning = ಅಸತ್ಯ;
  ತಾರ್ಕಿಕ npc = ಅಸತ್ಯ;

  /* Use the expansion point to handle cases such as returning NULL
     in a function returning void.  */
  location_t xloc = expansion_point_location_if_in_system_header (loc);

  ಯದಿ (ವೃಕ್ಷ_THIS_VOLATILE (current_function_decl))
    warning_at (xloc, 0,
		"function declared %<noreturn%> has a %<return%> statement");

  set_musttail_on_return (retval, xloc, musttail_p);

  ಯದಿ (retval)
    {
      ವೃಕ್ಷ semantic_type = NULL_ವೃಕ್ಷ;
      npc = null_pointer_constant_p (retval);
      ಯದಿ (ವೃಕ್ಷ_CODE (retval) == EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ)
	{
	  semantic_type = ವೃಕ್ಷ_TYPE (retval);
	  retval = ವೃಕ್ಷ_OPERAND (retval, 0);
	}
      retval = c_fully_fold (retval, ಅಸತ್ಯ, ರಿಕ್ತ);
      ಯದಿ (semantic_type
	  && valtype != NULL_ವೃಕ್ಷ
	  && ವೃಕ್ಷ_CODE (valtype) != VOID_TYPE)
	retval = build1 (EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ, semantic_type, retval);
    }

  ಯದಿ (!retval)
    {
      current_function_returns_null = 1;
      ಯದಿ ((warn_return_type >= 0 || flag_isoc99)
	  && valtype != NULL_ವೃಕ್ಷ && ವೃಕ್ಷ_CODE (valtype) != VOID_TYPE)
	{
	  no_warning = ಸತ್ಯ;
	  ಯದಿ (emit_diagnostic (flag_isoc99
			       ? diagnostics::kind::permerror
			       : diagnostics::kind::warning,
			       loc, OPT_Wreturn_mismatch,
			       "%<return%> with no value,"
			       " in function returning non-void"))
	    inform (DECL_SOURCE_LOCATION (current_function_decl),
		    "declared here");
	}
    }
  ಅನ್ಯಥಾ ಯದಿ (valtype == NULL_ವೃಕ್ಷ || VOID_TYPE_P (valtype))
    {
      current_function_returns_null = 1;
      ತಾರ್ಕಿಕ warned_here;
      ಯದಿ (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (retval)) != VOID_TYPE)
	warned_here = permerror_opt
	  (xloc, OPT_Wreturn_mismatch,
	   "%<return%> with a value, in function returning void");
      ಅನ್ಯಥಾ
	warned_here = pedwarn
	  (xloc, OPT_Wpedantic, "ISO C forbids "
	   "%<return%> with expression, in function returning void");
      ಯದಿ (warned_here)
	inform (DECL_SOURCE_LOCATION (current_function_decl),
		"declared here");
    }
  ಅನ್ಯಥಾ
    {
      ವೃಕ್ಷ t = convert_for_assignment (loc, UNKNOWN_LOCATION, valtype,
				       retval, origtype, ic_return,
				       npc, NULL_ವೃಕ್ಷ, NULL_ವೃಕ್ಷ, 0);
      ವೃಕ್ಷ res = DECL_RESULT (current_function_decl);
      ವೃಕ್ಷ inner;
      ತಾರ್ಕಿಕ save;

      current_function_returns_ಮೌಲ್ಯ = 1;
      ಯದಿ (t == error_mark_ಗಂಟು)
	{
	  /* Suppress -Wreturn-type for this function.  */
	  ಯದಿ (warn_return_type)
	    suppress_warning (current_function_decl, OPT_Wreturn_type);
	  ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
	}

      save = in_late_ದ್ವಿಮಾನ_op;
      ಯದಿ (C_BOOLEAN_TYPE_P (ವೃಕ್ಷ_TYPE (res))
	  || ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (res)) == COMPLEX_TYPE
	  || (SCALAR_FLOAT_TYPE_P (ವೃಕ್ಷ_TYPE (t))
	      && (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (res)) == INTEGER_TYPE
		  || ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (res)) == ENUMERAL_TYPE)
	      && sanitize_flags_p (SANITIZE_FLOAT_CAST)))
        in_late_ದ್ವಿಮಾನ_op = ಸತ್ಯ;
      inner = t = convert (ವೃಕ್ಷ_TYPE (res), t);
      in_late_ದ್ವಿಮಾನ_op = save;

      /* Strip any conversions, additions, and subtractions, and see if
	 we are returning the address of a local variable.  Warn if so.  */
      ಯಾವತ್ (1)
	{
	  ವಿಕಲ್ಪ (ವೃಕ್ಷ_CODE (inner))
	    {
	    CASE_CONVERT:
	    ಪಕ್ಷ NON_LVALUE_ಅಭಿವ್ಯಕ್ತಿ:
	    ಪಕ್ಷ PLUS_ಅಭಿವ್ಯಕ್ತಿ:
	    ಪಕ್ಷ POINTER_PLUS_ಅಭಿವ್ಯಕ್ತಿ:
	      inner = ವೃಕ್ಷ_OPERAND (inner, 0);
	      ಅನುವರ್ತ;

	    ಪಕ್ಷ MINUS_ಅಭಿವ್ಯಕ್ತಿ:
	      /* If the second operand of the MINUS_EXPR has a pointer
		 type (or is converted from it), this may be valid, so
		 don't give a warning.  */
	      {
		ವೃಕ್ಷ op1 = ವೃಕ್ಷ_OPERAND (inner, 1);

		ಯಾವತ್ (!POINTER_TYPE_P (ವೃಕ್ಷ_TYPE (op1))
		       && (CONVERT_ಅಭಿವ್ಯಕ್ತಿ_P (op1)
			   || ವೃಕ್ಷ_CODE (op1) == NON_LVALUE_ಅಭಿವ್ಯಕ್ತಿ))
		  op1 = ವೃಕ್ಷ_OPERAND (op1, 0);

		ಯದಿ (POINTER_TYPE_P (ವೃಕ್ಷ_TYPE (op1)))
		  ಭಙ್ಗ;

		inner = ವೃಕ್ಷ_OPERAND (inner, 0);
		ಅನುವರ್ತ;
	      }

	    ಪಕ್ಷ ADDR_ಅಭಿವ್ಯಕ್ತಿ:
	      inner = ವೃಕ್ಷ_OPERAND (inner, 0);

	      ಯಾವತ್ (REFERENCE_CLASS_P (inner)
		     && !INDIRECT_REF_P (inner))
		inner = ವೃಕ್ಷ_OPERAND (inner, 0);

	      ಯದಿ (DECL_P (inner)
		  && !DECL_EXTERNAL (inner)
		  && DECL_CONTEXT (inner) == current_function_decl
		  && POINTER_TYPE_P (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (current_function_decl))))
		{
		  ಯದಿ (ವೃಕ್ಷ_CODE (inner) == LABEL_DECL)
		    warning_at (loc, OPT_Wreturn_local_addr,
				"function returns address of label");
		  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (inner) == FUNCTION_DECL
			   && (C_FUNC_NONLOCAL_CONTEXT (inner)
			       || !DECL_INITIAL (inner)))
		    warning_at (loc, OPT_Wreturn_local_addr,
				"function returns address of nested function "
				"referencing local context");
		  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (inner) != FUNCTION_DECL
			   && !ವೃಕ್ಷ_STATIC (inner))
		    {
		      warning_at (loc, OPT_Wreturn_local_addr,
				  "function returns address of local variable");
		      ವೃಕ್ಷ zero = build_zero_cst (ವೃಕ್ಷ_TYPE (res));
		      t = build2 (COMPOUND_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (res), t, zero);
		    }
		}
	      ಭಙ್ಗ;

	    ಸ್ವಭಾವ:
	      ಭಙ್ಗ;
	    }

	  ಭಙ್ಗ;
	}

      retval = build2 (MODIFY_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (res), res, t);
      SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (retval, loc);

      ಯದಿ (warn_sequence_point)
	verify_sequence_points (retval);
    }

  ret_stmt = build_stmt (loc, RETURN_ಅಭಿವ್ಯಕ್ತಿ, retval);
  ಯದಿ (no_warning)
    suppress_warning (ret_stmt, OPT_Wreturn_type);
  ಪ್ರತ್ಯಾಗಮ add_stmt (ret_stmt);
}

ಸಂರಚನಾ c_switch {
  /* The SWITCH_STMT being built.  */
  ವೃಕ್ಷ switch_stmt;

  /* The original type of the testing expression, i.e. before the
     default conversion is applied.  */
  ವೃಕ್ಷ orig_type;

  /* A splay-tree mapping the low element of a case range to the high
     element, or NULL_TREE if there is no high element.  Used to
     determine whether or not a new case label duplicates an old case
     label.  We need a tree, rather than simply a hash table, because
     of the GNU case range extension.  */
  splay_ವೃಕ್ಷ cases;

  /* The bindings at the point of the switch.  This is used for
     warnings crossing decls when branching to a case label.  */
  ಸಂರಚನಾ c_spot_bindings *bindings;

  /* Whether the switch includes any break statements.  */
  ತಾರ್ಕಿಕ break_stmt_seen_p;

  /* The next node on the stack.  */
  ಸಂರಚನಾ c_switch *next;

  /* Remember whether the controlling expression had boolean type
     before integer promotions for the sake of -Wswitch-bool.  */
  ತಾರ್ಕಿಕ bool_cond_p;
};

/* A stack of the currently active switch statements.  The innermost
   switch statement is on the top of the stack.  There is no need to
   mark the stack for garbage collection because it is only active
   during the processing of the body of a function, and we never
   collect at that point.  */

ಸಂರಚನಾ c_switch *c_switch_ರಾಶಿ;

/* Start a C switch statement, testing expression EXP.  Return the new
   SWITCH_STMT.  SWITCH_LOC is the location of the `switch'.
   SWITCH_COND_LOC is the location of the switch's condition.
   EXPLICIT_CAST_P is true if the expression EXP has an explicit cast.  */

ವೃಕ್ಷ
c_start_switch (location_t switch_loc,
		location_t switch_cond_loc,
		ವೃಕ್ಷ exp, ತಾರ್ಕಿಕ explicit_cast_p, ವೃಕ್ಷ switch_name)
{
  ವೃಕ್ಷ orig_type = error_mark_ಗಂಟು;
  ತಾರ್ಕಿಕ bool_cond_p = ಅಸತ್ಯ;
  ಸಂರಚನಾ c_switch *cs;

  ಯದಿ (exp != error_mark_ಗಂಟು)
    {
      orig_type = ವೃಕ್ಷ_TYPE (exp);

      ಯದಿ (!INTEGRAL_TYPE_P (orig_type))
	{
	  ಯದಿ (orig_type != error_mark_ಗಂಟು)
	    {
	      error_at (switch_cond_loc, "switch quantity not an integer");
	      orig_type = error_mark_ಗಂಟು;
	    }
	  exp = integer_zero_ಗಂಟು;
	}
      ಅನ್ಯಥಾ
	{
	  ವೃಕ್ಷ type = TYPE_MAIN_VARIANT (orig_type);
	  ವೃಕ್ಷ e = exp;

	  /* Warn if the condition has boolean value.  */
	  ಯಾವತ್ (ವೃಕ್ಷ_CODE (e) == COMPOUND_ಅಭಿವ್ಯಕ್ತಿ)
	    e = ವೃಕ್ಷ_OPERAND (e, 1);

	  ಯದಿ ((C_BOOLEAN_TYPE_P (type)
	       || truth_ಮೌಲ್ಯ_p (ವೃಕ್ಷ_CODE (e)))
	      /* Explicit cast to int suppresses this warning.  */
	      && !(ವೃಕ್ಷ_CODE (type) == INTEGER_TYPE
		   && explicit_cast_p))
	    bool_cond_p = ಸತ್ಯ;

	  ಯದಿ (!in_system_header_at (ಒಳಹರಿವು_location)
	      && (type == long_integer_type_ಗಂಟು
		  || type == long_unsigned_type_ಗಂಟು))
	    warning_at (switch_cond_loc,
			OPT_Wtraditional, "%<long%> switch expression not "
			"converted to %<int%> in ISO C");

	  exp = c_fully_fold (exp, ಅಸತ್ಯ, ರಿಕ್ತ);
	  exp = default_conversion (exp);

	  ಯದಿ (warn_sequence_point)
	    verify_sequence_points (exp);
	}
    }

  /* Add this new SWITCH_STMT to the stack.  */
  cs = XNEW (ಸಂರಚನಾ c_switch);
  cs->switch_stmt = build_stmt (switch_loc, SWITCH_STMT, exp,
				NULL_ವೃಕ್ಷ, orig_type, NULL_ವೃಕ್ಷ, switch_name);
  cs->orig_type = orig_type;
  cs->cases = splay_ವೃಕ್ಷ_new (case_compare, ರಿಕ್ತ, ರಿಕ್ತ);
  cs->bindings = c_get_switch_bindings ();
  cs->break_stmt_seen_p = ಅಸತ್ಯ;
  cs->bool_cond_p = bool_cond_p;
  cs->next = c_switch_ರಾಶಿ;
  c_switch_ರಾಶಿ = cs;

  ಪ್ರತ್ಯಾಗಮ add_stmt (cs->switch_stmt);
}

/* Process a case label at location LOC, with attributes ATTRS.  */

ವೃಕ್ಷ
do_case (location_t loc, ವೃಕ್ಷ ಕೆಳಗಿನ_ಮೌಲ್ಯ, ವೃಕ್ಷ ಮೇಲಿನ_ಮೌಲ್ಯ, ವೃಕ್ಷ attrs)
{
  ವೃಕ್ಷ label = NULL_ವೃಕ್ಷ;

  ಯದಿ (ಕೆಳಗಿನ_ಮೌಲ್ಯ && ವೃಕ್ಷ_CODE (ಕೆಳಗಿನ_ಮೌಲ್ಯ) != INTEGER_CST)
    {
      ಕೆಳಗಿನ_ಮೌಲ್ಯ = c_fully_fold (ಕೆಳಗಿನ_ಮೌಲ್ಯ, ಅಸತ್ಯ, ರಿಕ್ತ);
      ಯದಿ (ವೃಕ್ಷ_CODE (ಕೆಳಗಿನ_ಮೌಲ್ಯ) == INTEGER_CST)
	pedwarn (loc, OPT_Wpedantic,
		 "case label is not an integer constant expression");
    }

  ಯದಿ (ಮೇಲಿನ_ಮೌಲ್ಯ && ವೃಕ್ಷ_CODE (ಮೇಲಿನ_ಮೌಲ್ಯ) != INTEGER_CST)
    {
      ಮೇಲಿನ_ಮೌಲ್ಯ = c_fully_fold (ಮೇಲಿನ_ಮೌಲ್ಯ, ಅಸತ್ಯ, ರಿಕ್ತ);
      ಯದಿ (ವೃಕ್ಷ_CODE (ಮೇಲಿನ_ಮೌಲ್ಯ) == INTEGER_CST)
	pedwarn (ಒಳಹರಿವು_location, OPT_Wpedantic,
		 "case label is not an integer constant expression");
    }

  ಯದಿ (c_switch_ರಾಶಿ == ರಿಕ್ತ)
    {
      ಯದಿ (ಕೆಳಗಿನ_ಮೌಲ್ಯ)
	error_at (loc, "case label not within a switch statement");
      ಅನ್ಯಥಾ
	error_at (loc, "%<default%> label not within a switch statement");
      ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
    }

  ಯದಿ (c_check_switch_jump_warnings (c_switch_ರಾಶಿ->bindings,
				    ಅಭಿವ್ಯಕ್ತಿ_LOCATION (c_switch_ರಾಶಿ->switch_stmt),
				    loc))
    ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;

  label = c_add_case_label (loc, c_switch_ರಾಶಿ->cases,
			    SWITCH_STMT_COND (c_switch_ರಾಶಿ->switch_stmt),
			    ಕೆಳಗಿನ_ಮೌಲ್ಯ, ಮೇಲಿನ_ಮೌಲ್ಯ, attrs);
  ಯದಿ (label == error_mark_ಗಂಟು)
    label = NULL_ವೃಕ್ಷ;
  ಪ್ರತ್ಯಾಗಮ label;
}

/* Finish the switch statement.  TYPE is the original type of the
   controlling expression of the switch, or NULL_TREE.  */

ಶೂನ್ಯ
c_finish_switch (ವೃಕ್ಷ body, ವೃಕ್ಷ type)
{
  ಸಂರಚನಾ c_switch *cs = c_switch_ರಾಶಿ;
  location_t switch_location;

  SWITCH_STMT_BODY (cs->switch_stmt) = body;

  /* Emit warnings as needed.  */
  switch_location = ಅಭಿವ್ಯಕ್ತಿ_LOCATION (cs->switch_stmt);
  c_do_switch_warnings (cs->cases, switch_location,
			type ? type : SWITCH_STMT_TYPE (cs->switch_stmt),
			SWITCH_STMT_COND (cs->switch_stmt), cs->bool_cond_p);
  ಯದಿ (c_switch_covers_all_cases_p (cs->cases,
				   SWITCH_STMT_TYPE (cs->switch_stmt)))
    SWITCH_STMT_ALL_CASES_P (cs->switch_stmt) = 1;
  SWITCH_STMT_NO_BREAK_P (cs->switch_stmt) = !cs->break_stmt_seen_p;

  /* Pop the stack.  */
  c_switch_ರಾಶಿ = cs->next;
  splay_ವೃಕ್ಷ_delete (cs->cases);
  c_release_switch_bindings (cs->bindings);
  XDELETE (cs);
}

/* Emit an if statement.  IF_LOCUS is the location of the 'if'.  COND,
   THEN_BLOCK and ELSE_BLOCK are expressions to be used; ELSE_BLOCK
   may be null.  */

ಶೂನ್ಯ
c_finish_if_stmt (location_t if_locus, ವೃಕ್ಷ cond, ವೃಕ್ಷ then_block,
		  ವೃಕ್ಷ else_block)
{
  ವೃಕ್ಷ stmt;

  stmt = build3 (COND_ಅಭಿವ್ಯಕ್ತಿ, void_type_ಗಂಟು, cond, then_block, else_block);
  SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (stmt, if_locus);
  add_stmt (stmt);
}

ವೃಕ್ಷ
c_finish_bc_stmt (location_t loc, ವೃಕ್ಷ label, ತಾರ್ಕಿಕ is_break, ವೃಕ್ಷ name)
{
  /* In switch statements break is sometimes stylistically used after
     a return statement.  This can lead to spurious warnings about
     control reaching the end of a non-void function when it is
     inlined.  Note that we are calling block_may_fallthru with
     language specific tree nodes; this works because
     block_may_fallthru returns true when given something it does not
     understand.  */
  ತಾರ್ಕಿಕ skip = !block_may_fallthru (cur_stmt_list);

  ಯದಿ (is_break)
    ವಿಕಲ್ಪ (in_statement & ~IN_NAMED_STMT)
      {
      ಪಕ್ಷ 0:
	error_at (loc, "break statement not within loop or switch");
	ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
      ಪಕ್ಷ IN_OMP_BLOCK:
	error_at (loc, "invalid exit from OpenMP structured block");
	ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
      ಪಕ್ಷ IN_OMP_FOR:
	error_at (loc, "break statement used with OpenMP for loop");
	ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
      ಪಕ್ಷ IN_ITERATION_STMT:
      ಪಕ್ಷ IN_OBJC_FOREACH:
	ಭಙ್ಗ;
      ಸ್ವಭಾವ:
	gcc_assert (in_statement & IN_SWITCH_STMT);
	c_switch_ರಾಶಿ->break_stmt_seen_p = ಸತ್ಯ;
	ಭಙ್ಗ;
      }
  ಅನ್ಯಥಾ
    ವಿಕಲ್ಪ (in_statement & ~(IN_SWITCH_STMT | IN_NAMED_STMT))
      {
      ಪಕ್ಷ 0:
	error_at (loc, "continue statement not within a loop");
	ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
      ಪಕ್ಷ IN_OMP_BLOCK:
	error_at (loc, "invalid exit from OpenMP structured block");
	ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
      ಪಕ್ಷ IN_ITERATION_STMT:
      ಪಕ್ಷ IN_OMP_FOR:
      ಪಕ್ಷ IN_OBJC_FOREACH:
	ಭಙ್ಗ;
      ಸ್ವಭಾವ:
	gcc_unreachable ();
      }

  ಯದಿ (skip)
    ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
  ಅನ್ಯಥಾ ಯದಿ ((in_statement & IN_OBJC_FOREACH)
	   && !(is_break && (in_statement & IN_SWITCH_STMT))
	   && name == NULL_ವೃಕ್ಷ)
    {
      /* The foreach expander produces low-level code using gotos instead
	 of a structured loop construct.  */
      gcc_assert (label);
      ಪ್ರತ್ಯಾಗಮ add_stmt (build_stmt (loc, GOTO_ಅಭಿವ್ಯಕ್ತಿ, label));
    }
  ಅನ್ಯಥಾ ಯದಿ (name && C_DECL_LOOP_NAME (name) && C_DECL_SWITCH_NAME (name))
    {
      label = DECL_CHAIN (name);
      ಯದಿ (!is_break)
	label = DECL_CHAIN (label);
      /* Foreach expander from some outer level.  */
      ಪ್ರತ್ಯಾಗಮ add_stmt (build_stmt (loc, GOTO_ಅಭಿವ್ಯಕ್ತಿ, label));
    }
  ಪ್ರತ್ಯಾಗಮ add_stmt (build_stmt (loc, is_break ? BREAK_STMT : CONTINUE_STMT,
			       name));
}

/* A helper routine for c_process_expr_stmt and c_finish_stmt_expr.  */

ಸ್ಥಿರ ಶೂನ್ಯ
emit_side_effect_warnings (location_t loc, ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ)
{
  maybe_warn_nodiscard (loc, ಅಭಿವ್ಯಕ್ತಿ);
  ಯದಿ (!warn_unused_ಮೌಲ್ಯ)
    ಪ್ರತ್ಯಾಗಮ;
  ಯದಿ (ಅಭಿವ್ಯಕ್ತಿ == error_mark_ಗಂಟು)
    ;
  ಅನ್ಯಥಾ ಯದಿ (!ವೃಕ್ಷ_SIDE_EFFECTS (ಅಭಿವ್ಯಕ್ತಿ))
    {
      ಯದಿ (!VOID_TYPE_P (ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ))
	  && !warning_suppressed_p (ಅಭಿವ್ಯಕ್ತಿ, OPT_Wunused_ಮೌಲ್ಯ))
	warning_at (loc, OPT_Wunused_ಮೌಲ್ಯ, "statement with no effect");
    }
  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (ಅಭಿವ್ಯಕ್ತಿ) == COMPOUND_ಅಭಿವ್ಯಕ್ತಿ)
    {
      ವೃಕ್ಷ r = ಅಭಿವ್ಯಕ್ತಿ;
      location_t cloc = loc;
      ಯಾವತ್ (ವೃಕ್ಷ_CODE (r) == COMPOUND_ಅಭಿವ್ಯಕ್ತಿ)
	{
	  ಯದಿ (ಅಭಿವ್ಯಕ್ತಿ_HAS_LOCATION (r))
	    cloc = ಅಭಿವ್ಯಕ್ತಿ_LOCATION (r);
	  r = ವೃಕ್ಷ_OPERAND (r, 1);
	}
      ಯದಿ (!ವೃಕ್ಷ_SIDE_EFFECTS (r)
	  && !VOID_TYPE_P (ವೃಕ್ಷ_TYPE (r))
	  && !CONVERT_ಅಭಿವ್ಯಕ್ತಿ_P (r)
	  && !warning_suppressed_p (r, OPT_Wunused_ಮೌಲ್ಯ)
	  && !warning_suppressed_p (ಅಭಿವ್ಯಕ್ತಿ, OPT_Wunused_ಮೌಲ್ಯ))
	warning_at (cloc, OPT_Wunused_ಮೌಲ್ಯ,
		    "right-hand operand of comma expression has no effect");
    }
  ಅನ್ಯಥಾ
    warn_if_unused_ಮೌಲ್ಯ (ಅಭಿವ್ಯಕ್ತಿ, loc);
}

/* Process an expression as if it were a complete statement.  Emit
   diagnostics, but do not call ADD_STMT.  LOC is the location of the
   statement.  */

ವೃಕ್ಷ
c_process_ಅಭಿವ್ಯಕ್ತಿ_stmt (location_t loc, ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ)
{
  ವೃಕ್ಷ exprv;

  ಯದಿ (!ಅಭಿವ್ಯಕ್ತಿ)
    ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;

  ಅಭಿವ್ಯಕ್ತಿ = c_fully_fold (ಅಭಿವ್ಯಕ್ತಿ, ಅಸತ್ಯ, ರಿಕ್ತ);

  ಯದಿ (warn_sequence_point)
    verify_sequence_points (ಅಭಿವ್ಯಕ್ತಿ);

  ಯದಿ (ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ) != error_mark_ಗಂಟು
      && !COMPLETE_OR_VOID_TYPE_P (ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ))
      && ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ)) != ARRAY_TYPE)
    error_at (loc, "expression statement has incomplete type");

  /* If we're not processing a statement expression, warn about unused values.
     Warnings for statement expressions will be emitted later, once we figure
     out which is the result.  */
  ಯದಿ (!STATEMENT_LIST_STMT_ಅಭಿವ್ಯಕ್ತಿ (cur_stmt_list)
      && (warn_unused_ಮೌಲ್ಯ || warn_unused_result))
    emit_side_effect_warnings (ಅಭಿವ್ಯಕ್ತಿ_LOC_OR_LOC (ಅಭಿವ್ಯಕ್ತಿ, loc), ಅಭಿವ್ಯಕ್ತಿ);

  exprv = ಅಭಿವ್ಯಕ್ತಿ;
  ಯಾವತ್ (ವೃಕ್ಷ_CODE (exprv) == COMPOUND_ಅಭಿವ್ಯಕ್ತಿ)
    exprv = ವೃಕ್ಷ_OPERAND (exprv, 1);
  ಯಾವತ್ (CONVERT_ಅಭಿವ್ಯಕ್ತಿ_P (exprv))
    exprv = ವೃಕ್ಷ_OPERAND (exprv, 0);
  ಯದಿ (DECL_P (exprv)
      || handled_component_p (exprv)
      || ವೃಕ್ಷ_CODE (exprv) == ADDR_ಅಭಿವ್ಯಕ್ತಿ)
    mark_exp_read (exprv);

  /* If the expression is not of a type to which we cannot assign a line
     number, wrap the thing in a no-op NOP_EXPR.  */
  ಯದಿ (DECL_P (ಅಭಿವ್ಯಕ್ತಿ) || CONSTANT_CLASS_P (ಅಭಿವ್ಯಕ್ತಿ))
    {
      ಅಭಿವ್ಯಕ್ತಿ = build1 (NOP_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ), ಅಭಿವ್ಯಕ್ತಿ);
      SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (ಅಭಿವ್ಯಕ್ತಿ, loc);
    }

  ಪ್ರತ್ಯಾಗಮ ಅಭಿವ್ಯಕ್ತಿ;
}

/* Emit an expression as a statement.  LOC is the location of the
   expression.  */

ವೃಕ್ಷ
c_finish_ಅಭಿವ್ಯಕ್ತಿ_stmt (location_t loc, ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ)
{
  ಯದಿ (ಅಭಿವ್ಯಕ್ತಿ)
    ಪ್ರತ್ಯಾಗಮ add_stmt (c_process_ಅಭಿವ್ಯಕ್ತಿ_stmt (loc, ಅಭಿವ್ಯಕ್ತಿ));
  ಅನ್ಯಥಾ
    ಪ್ರತ್ಯಾಗಮ ರಿಕ್ತ;
}

/* Do the opposite and emit a statement as an expression.  To begin,
   create a new binding level and return it.  */

ವೃಕ್ಷ
c_begin_stmt_ಅಭಿವ್ಯಕ್ತಿ (ಶೂನ್ಯ)
{
  ವೃಕ್ಷ ret;

  /* We must force a BLOCK for this level so that, if it is not expanded
     later, there is a way to turn off the entire subtree of blocks that
     are contained in it.  */
  keep_next_level ();
  ret = c_begin_compound_stmt (ಸತ್ಯ);

  c_bindings_start_stmt_ಅಭಿವ್ಯಕ್ತಿ (c_switch_ರಾಶಿ == ರಿಕ್ತ
			      ? ರಿಕ್ತ
			      : c_switch_ರಾಶಿ->bindings);

  /* Mark the current statement list as belonging to a statement list.  */
  STATEMENT_LIST_STMT_ಅಭಿವ್ಯಕ್ತಿ (ret) = 1;

  ಪ್ರತ್ಯಾಗಮ ret;
}

/* LOC is the location of the compound statement to which this body
   belongs.  */

ವೃಕ್ಷ
c_finish_stmt_ಅಭಿವ್ಯಕ್ತಿ (location_t loc, ವೃಕ್ಷ body)
{
  ವೃಕ್ಷ last, type, tmp, val;
  ವೃಕ್ಷ *last_p;

  body = c_end_compound_stmt (loc, body, ಸತ್ಯ);

  c_bindings_end_stmt_ಅಭಿವ್ಯಕ್ತಿ (c_switch_ರಾಶಿ == ರಿಕ್ತ
			    ? ರಿಕ್ತ
			    : c_switch_ರಾಶಿ->bindings);

  /* Locate the last statement in BODY.  See c_end_compound_stmt
     about always returning a BIND_EXPR.  */
  last_p = &BIND_ಅಭಿವ್ಯಕ್ತಿ_BODY (body);
  last = BIND_ಅಭಿವ್ಯಕ್ತಿ_BODY (body);

 continue_searching:
  ಯದಿ (ವೃಕ್ಷ_CODE (last) == STATEMENT_LIST)
    {
      ವೃಕ್ಷ_stmt_iterator l = tsi_last (last);

      ಯಾವತ್ (!tsi_end_p (l) && ವೃಕ್ಷ_CODE (tsi_stmt (l)) == DEBUG_BEGIN_STMT)
	tsi_prev (&l);

      /* This can happen with degenerate cases like ({ }).  No value.  */
      ಯದಿ (tsi_end_p (l))
	ಪ್ರತ್ಯಾಗಮ body;

      /* If we're supposed to generate side effects warnings, process
	 all of the statements except the last.  */
      ಯದಿ (warn_unused_ಮೌಲ್ಯ || warn_unused_result)
	{
	  ಪ್ರತಿ (ವೃಕ್ಷ_stmt_iterator i = tsi_start (last);
	       tsi_stmt (i) != tsi_stmt (l); tsi_next (&i))
	    {
	      location_t tloc;
	      ವೃಕ್ಷ t = tsi_stmt (i);

	      tloc = ಅಭಿವ್ಯಕ್ತಿ_HAS_LOCATION (t) ? ಅಭಿವ್ಯಕ್ತಿ_LOCATION (t) : loc;
	      emit_side_effect_warnings (tloc, t);
	    }
	}
      last_p = tsi_stmt_ptr (l);
      last = *last_p;
    }

  /* If the end of the list is exception related, then the list was split
     by a call to push_cleanup.  Continue searching.  */
  ಯದಿ (ವೃಕ್ಷ_CODE (last) == TRY_FINALLY_ಅಭಿವ್ಯಕ್ತಿ
      || ವೃಕ್ಷ_CODE (last) == TRY_CATCH_ಅಭಿವ್ಯಕ್ತಿ)
    {
      last_p = &ವೃಕ್ಷ_OPERAND (last, 0);
      last = *last_p;
      ಗಚ್ಛ continue_searching;
    }

  ಯದಿ (last == error_mark_ಗಂಟು)
    ಪ್ರತ್ಯಾಗಮ last;

  /* In the case that the BIND_EXPR is not necessary, return the
     expression out from inside it.  */
  ಯದಿ ((last == BIND_ಅಭಿವ್ಯಕ್ತಿ_BODY (body)
       /* Skip nested debug stmts.  */
       || last == ಅಭಿವ್ಯಕ್ತಿ_first (BIND_ಅಭಿವ್ಯಕ್ತಿ_BODY (body)))
      && BIND_ಅಭಿವ್ಯಕ್ತಿ_VARS (body) == ರಿಕ್ತ)
    {
      /* Even if this looks constant, do not allow it in a constant
	 expression.  */
      last = c_wrap_maybe_const (last, ಸತ್ಯ);
      /* Do not warn if the return value of a statement expression is
	 unused.  */
      suppress_warning (last, OPT_Wunused);
      ಪ್ರತ್ಯಾಗಮ last;
    }

  /* Extract the type of said expression.  */
  type = ವೃಕ್ಷ_TYPE (last);

  /* If we're not returning a value at all, then the BIND_EXPR that
     we already have is a fine expression to return.  */
  ಯದಿ (!type || VOID_TYPE_P (type))
    ಪ್ರತ್ಯಾಗಮ body;

  /* Now that we've located the expression containing the value, it seems
     silly to make voidify_wrapper_expr repeat the process.  Create a
     temporary of the appropriate type and stick it in a TARGET_EXPR.  */
  tmp = create_tmp_var_raw (type);

  /* Unwrap a no-op NOP_EXPR as added by c_finish_expr_stmt.  This avoids
     tree_expr_nonnegative_p giving up immediately.  */
  val = last;
  ಯದಿ (ವೃಕ್ಷ_CODE (val) == NOP_ಅಭಿವ್ಯಕ್ತಿ
      && ವೃಕ್ಷ_TYPE (val) == ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_OPERAND (val, 0)))
    val = ವೃಕ್ಷ_OPERAND (val, 0);

  *last_p = build2 (MODIFY_ಅಭಿವ್ಯಕ್ತಿ, void_type_ಗಂಟು, tmp, val);
  SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (*last_p, ಅಭಿವ್ಯಕ್ತಿ_LOCATION (last));

  {
    ವೃಕ್ಷ t = build4 (TARGET_ಅಭಿವ್ಯಕ್ತಿ, type, tmp, body, NULL_ವೃಕ್ಷ, NULL_ವೃಕ್ಷ);
    SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (t, loc);
    ಪ್ರತ್ಯಾಗಮ t;
  }
}

/* Begin and end compound statements.  This is as simple as pushing
   and popping new statement lists from the tree.  */

ವೃಕ್ಷ
c_begin_compound_stmt (ತಾರ್ಕಿಕ do_scope)
{
  ವೃಕ್ಷ stmt = ತಳ್ಳು_stmt_list ();
  ಯದಿ (do_scope)
    ತಳ್ಳು_scope ();
  ಪ್ರತ್ಯಾಗಮ stmt;
}

/* End a compound statement.  STMT is the statement.  LOC is the
   location of the compound statement-- this is usually the location
   of the opening brace.  */

ವೃಕ್ಷ
c_end_compound_stmt (location_t loc, ವೃಕ್ಷ stmt, ತಾರ್ಕಿಕ do_scope)
{
  ವೃಕ್ಷ block = ರಿಕ್ತ;

  ಯದಿ (do_scope)
    {
      ಯದಿ (c_dialect_objc ())
	objc_clear_super_receiver ();
      block = ತೆಗೆ_scope ();
    }

  stmt = ತೆಗೆ_stmt_list (stmt);
  stmt = c_build_bind_ಅಭಿವ್ಯಕ್ತಿ (loc, block, stmt);

  /* If this compound statement is nested immediately inside a statement
     expression, then force a BIND_EXPR to be created.  Otherwise we'll
     do the wrong thing for ({ { 1; } }) or ({ 1; { } }).  In particular,
     STATEMENT_LISTs merge, and thus we can lose track of what statement
     was really last.  */
  ಯದಿ (building_stmt_list_p ()
      && STATEMENT_LIST_STMT_ಅಭಿವ್ಯಕ್ತಿ (cur_stmt_list)
      && ವೃಕ್ಷ_CODE (stmt) != BIND_ಅಭಿವ್ಯಕ್ತಿ)
    {
      stmt = build3 (BIND_ಅಭಿವ್ಯಕ್ತಿ, void_type_ಗಂಟು, ರಿಕ್ತ, stmt, ರಿಕ್ತ);
      ವೃಕ್ಷ_SIDE_EFFECTS (stmt) = 1;
      SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (stmt, loc);
    }

  ಪ್ರತ್ಯಾಗಮ stmt;
}

/* Queue a cleanup.  CLEANUP is an expression/statement to be executed
   when the current scope is exited.  EH_ONLY is true when this is not
   meant to apply to normal control flow transfer.  */

ಶೂನ್ಯ
ತಳ್ಳು_cleanup (ವೃಕ್ಷ decl, ವೃಕ್ಷ cleanup, ತಾರ್ಕಿಕ eh_only)
{
  ಗಣನಾ ವೃಕ್ಷ_code code;
  ವೃಕ್ಷ stmt, list;
  ತಾರ್ಕಿಕ stmt_ಅಭಿವ್ಯಕ್ತಿ;

  code = eh_only ? TRY_CATCH_ಅಭಿವ್ಯಕ್ತಿ : TRY_FINALLY_ಅಭಿವ್ಯಕ್ತಿ;
  stmt = build_stmt (DECL_SOURCE_LOCATION (decl), code, ರಿಕ್ತ, cleanup);
  add_stmt (stmt);
  stmt_ಅಭಿವ್ಯಕ್ತಿ = STATEMENT_LIST_STMT_ಅಭಿವ್ಯಕ್ತಿ (cur_stmt_list);
  list = ತಳ್ಳು_stmt_list ();
  ವೃಕ್ಷ_OPERAND (stmt, 0) = list;
  STATEMENT_LIST_STMT_ಅಭಿವ್ಯಕ್ತಿ (list) = stmt_ಅಭಿವ್ಯಕ್ತಿ;
}

/* Build a vector comparison of ARG0 and ARG1 using CODE opcode
   into a value of TYPE type.  Comparison is done via VEC_COND_EXPR.  */

ಸ್ಥಿರ ವೃಕ್ಷ
build_vec_cmp (ವೃಕ್ಷ_code code, ವೃಕ್ಷ type,
	       ವೃಕ್ಷ arg0, ವೃಕ್ಷ arg1)
{
  ವೃಕ್ಷ zero_vec = build_zero_cst (type);
  ವೃಕ್ಷ minus_one_vec = build_minus_one_cst (type);
  ವೃಕ್ಷ cmp_type = truth_type_for (ವೃಕ್ಷ_TYPE (arg0));
  ವೃಕ್ಷ cmp = build2 (code, cmp_type, arg0, arg1);
  ಪ್ರತ್ಯಾಗಮ build3 (VEC_COND_ಅಭಿವ್ಯಕ್ತಿ, type, cmp, minus_one_vec, zero_vec);
}

/* Possibly warn about an address of OP never being NULL in a comparison
   operation CODE involving null.  */

ಸ್ಥಿರ ಶೂನ್ಯ
maybe_warn_for_null_address (location_t loc, ವೃಕ್ಷ op, ವೃಕ್ಷ_code code)
{
  /* Prevent warnings issued for macro expansion.  */
  ಯದಿ (!warn_address
      || warning_suppressed_p (op, OPT_Waddress)
      || from_macro_expansion_at (loc))
    ಪ್ರತ್ಯಾಗಮ;

  ಯದಿ (ವೃಕ್ಷ_CODE (op) == NOP_ಅಭಿವ್ಯಕ್ತಿ)
    {
      /* Allow casts to intptr_t to suppress the warning.  */
      ವೃಕ್ಷ type = ವೃಕ್ಷ_TYPE (op);
      ಯದಿ (ವೃಕ್ಷ_CODE (type) == INTEGER_TYPE)
	ಪ್ರತ್ಯಾಗಮ;
      op = ವೃಕ್ಷ_OPERAND (op, 0);
    }

  ಯದಿ (ವೃಕ್ಷ_CODE (op) == POINTER_PLUS_ಅಭಿವ್ಯಕ್ತಿ)
    {
      /* Allow a cast to void* to suppress the warning.  */
      ವೃಕ್ಷ type = ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (op));
      ಯದಿ (VOID_TYPE_P (type))
	ಪ್ರತ್ಯಾಗಮ;

      /* Adding any value to a null pointer, including zero, is undefined
	 in C.  This includes the expression &p[0] where p is the null
	 pointer, although &p[0] will have been folded to p by this point
	 and so not diagnosed.  */
      ಯದಿ (code == EQ_ಅಭಿವ್ಯಕ್ತಿ)
	warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<false%> "
		    "for the pointer operand in %qE must not be NULL",
		    op);
      ಅನ್ಯಥಾ
	warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<true%> "
		    "for the pointer operand in %qE must not be NULL",
		    op);

      ಪ್ರತ್ಯಾಗಮ;
    }

  ಯದಿ (ವೃಕ್ಷ_CODE (op) != ADDR_ಅಭಿವ್ಯಕ್ತಿ)
    ಪ್ರತ್ಯಾಗಮ;

  op = ವೃಕ್ಷ_OPERAND (op, 0);

  ಯದಿ (ವೃಕ್ಷ_CODE (op) == IMAGPART_ಅಭಿವ್ಯಕ್ತಿ
      || ವೃಕ್ಷ_CODE (op) == REALPART_ಅಭಿವ್ಯಕ್ತಿ)
    {
      /* The address of either complex part may not be null.  */
      ಯದಿ (code == EQ_ಅಭಿವ್ಯಕ್ತಿ)
	warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<false%> "
		    "for the address of %qE will never be NULL",
		    op);
      ಅನ್ಯಥಾ
	warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<true%> "
		    "for the address of %qE will never be NULL",
		    op);
      ಪ್ರತ್ಯಾಗಮ;
    }

  /* Set to true in the loop below if OP dereferences is operand.
     In such a case the ultimate target need not be a decl for
     the null [in]equality test to be constant.  */
  ತಾರ್ಕಿಕ deref = ಅಸತ್ಯ;

  /* Get the outermost array or object, or member.  */
  ಯಾವತ್ (handled_component_p (op))
    {
      ಯದಿ (ವೃಕ್ಷ_CODE (op) == COMPONENT_REF)
	{
	  /* Get the member (its address is never null).  */
	  op = ವೃಕ್ಷ_OPERAND (op, 1);
	  ಭಙ್ಗ;
	}

      /* Get the outer array/object to refer to in the warning.  */
      op = ವೃಕ್ಷ_OPERAND (op, 0);
      deref = ಸತ್ಯ;
    }

  ಯದಿ ((!deref && !decl_with_nonnull_addr_p (op))
      || from_macro_expansion_at (loc))
    ಪ್ರತ್ಯಾಗಮ;

  ತಾರ್ಕಿಕ w;
  ಯದಿ (code == EQ_ಅಭಿವ್ಯಕ್ತಿ)
    w = warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<false%> "
		    "for the address of %qE will never be NULL",
		    op);
  ಅನ್ಯಥಾ
    w = warning_at (loc, OPT_Waddress,
		    "the comparison will always evaluate as %<true%> "
		    "for the address of %qE will never be NULL",
		    op);

  ಯದಿ (w && DECL_P (op))
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

ವೃಕ್ಷ
build_ದ್ವಿಮಾನ_op (location_t location, ಗಣನಾ ವೃಕ್ಷ_code code,
		 ವೃಕ್ಷ orig_op0, ವೃಕ್ಷ orig_op1, ತಾರ್ಕಿಕ convert_p)
{
  ವೃಕ್ಷ type0, type1, orig_type0, orig_type1;
  ವೃಕ್ಷ eptype;
  ಗಣನಾ ವೃಕ್ಷ_code code0, code1;
  ವೃಕ್ಷ op0, op1;
  ವೃಕ್ಷ ret = error_mark_ಗಂಟು;
  ಧ್ರುವ ವರ್ಣ *invalid_op_diag;
  ತಾರ್ಕಿಕ op0_int_operands, op1_int_operands;
  ತಾರ್ಕಿಕ int_const, int_const_or_overflow, int_operands;

  /* Expression code to give to the expression when it is built.
     Normally this is CODE, which is what the caller asked for,
     but in some special cases we change it.  */
  ಗಣನಾ ವೃಕ್ಷ_code resultcode = code;

  /* Data type in which the computation is to be performed.
     In the simplest cases this is the common type of the arguments.  */
  ವೃಕ್ಷ result_type = ರಿಕ್ತ;

  /* When the computation is in excess precision, the type of the
     final EXCESS_PRECISION_EXPR.  */
  ವೃಕ್ಷ semantic_result_type = ರಿಕ್ತ;

  /* Nonzero means operands have already been type-converted
     in whatever way is necessary.
     Zero means they need to be converted to RESULT_TYPE.  */
  ಪೂರ್ಣಾಙ್ಕ converted = 0;

  /* Nonzero means create the expression with this type, rather than
     RESULT_TYPE.  */
  ವೃಕ್ಷ build_type = NULL_ವೃಕ್ಷ;

  /* Nonzero means after finally constructing the expression
     convert it to this type.  */
  ವೃಕ್ಷ final_type = NULL_ವೃಕ್ಷ;

  /* Nonzero if this is an operation like MIN or MAX which can
     safely be computed in short if both args are promoted shorts.
     Also implies COMMON.
     -1 indicates a bitwise operation; this makes a difference
     in the exact conditions for when it is safe to do the operation
     in a narrower mode.  */
  ಪೂರ್ಣಾಙ್ಕ shorten = 0;

  /* Nonzero if this is a comparison operation;
     if both args are promoted shorts, compare the original shorts.
     Also implies COMMON.  */
  ಪೂರ್ಣಾಙ್ಕ short_compare = 0;

  /* Nonzero if this is a right-shift operation, which can be computed on the
     original short and then promoted if the operand is a promoted short.  */
  ಪೂರ್ಣಾಙ್ಕ short_shift = 0;

  /* Nonzero means set RESULT_TYPE to the common type of the args.  */
  ಪೂರ್ಣಾಙ್ಕ common = 0;

  /* True means types are compatible as far as ObjC is concerned.  */
  ತಾರ್ಕಿಕ objc_ok;

  /* True means this is an arithmetic operation that may need excess
     precision.  */
  ತಾರ್ಕಿಕ may_need_excess_precision;

  /* True means this is a boolean operation that converts both its
     operands to truth-values.  */
  ತಾರ್ಕಿಕ boolean_op = ಅಸತ್ಯ;

  /* Remember whether we're doing / or %.  */
  ತಾರ್ಕಿಕ doing_div_or_mod = ಅಸತ್ಯ;

  /* Remember whether we're doing << or >>.  */
  ತಾರ್ಕಿಕ doing_shift = ಅಸತ್ಯ;

  /* Tree holding instrumentation expression.  */
  ವೃಕ್ಷ instrument_ಅಭಿವ್ಯಕ್ತಿ = ರಿಕ್ತ;

  ಯದಿ (location == UNKNOWN_LOCATION)
    location = ಒಳಹರಿವು_location;

  op0 = orig_op0;
  op1 = orig_op1;

  op0_int_operands = ಅಭಿವ್ಯಕ್ತಿ_INT_CONST_OPERANDS (orig_op0);
  ಯದಿ (op0_int_operands)
    op0 = remove_c_maybe_const_ಅಭಿವ್ಯಕ್ತಿ (op0);
  op1_int_operands = ಅಭಿವ್ಯಕ್ತಿ_INT_CONST_OPERANDS (orig_op1);
  ಯದಿ (op1_int_operands)
    op1 = remove_c_maybe_const_ಅಭಿವ್ಯಕ್ತಿ (op1);
  int_operands = (op0_int_operands && op1_int_operands);
  ಯದಿ (int_operands)
    {
      int_const_or_overflow = (ವೃಕ್ಷ_CODE (orig_op0) == INTEGER_CST
			       && ವೃಕ್ಷ_CODE (orig_op1) == INTEGER_CST);
      int_const = (int_const_or_overflow
		   && !ವೃಕ್ಷ_OVERFLOW (orig_op0)
		   && !ವೃಕ್ಷ_OVERFLOW (orig_op1));
    }
  ಅನ್ಯಥಾ
    int_const = int_const_or_overflow = ಅಸತ್ಯ;

  /* Do not apply default conversion in mixed vector/scalar expression.  */
  ಯದಿ (convert_p
      && VECTOR_TYPE_P (ವೃಕ್ಷ_TYPE (op0)) == VECTOR_TYPE_P (ವೃಕ್ಷ_TYPE (op1)))
    {
      op0 = default_conversion (op0);
      op1 = default_conversion (op1);
    }

  orig_type0 = type0 = ವೃಕ್ಷ_TYPE (op0);

  orig_type1 = type1 = ವೃಕ್ಷ_TYPE (op1);

  /* The expression codes of the data types of the arguments tell us
     whether the arguments are integers, floating, pointers, etc.  */
  code0 = ವೃಕ್ಷ_CODE (type0);
  code1 = ವೃಕ್ಷ_CODE (type1);

  /* Strip NON_LVALUE_EXPRs, etc., since we aren't using as an lvalue.  */
  STRIP_TYPE_NOPS (op0);
  STRIP_TYPE_NOPS (op1);

  /* If an error was already reported for one of the arguments,
     avoid reporting another error.  */

  ಯದಿ (code0 == ERROR_MARK || code1 == ERROR_MARK)
    ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;

  ಯದಿ (code0 == POINTER_TYPE
      && reject_gcc_builtin (op0, ಅಭಿವ್ಯಕ್ತಿ_LOCATION (orig_op0)))
    ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;

  ಯದಿ (code1 == POINTER_TYPE
      && reject_gcc_builtin (op1, ಅಭಿವ್ಯಕ್ತಿ_LOCATION (orig_op1)))
    ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;

  ಯದಿ ((invalid_op_diag
       = targetm.invalid_ದ್ವಿಮಾನ_op (code, type0, type1)))
    {
      error_at (location, invalid_op_diag);
      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
    }

  ವಿಕಲ್ಪ (code)
    {
    ಪಕ್ಷ PLUS_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ MINUS_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ MULT_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ TRUNC_DIV_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ CEIL_DIV_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ FLOOR_DIV_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ ROUND_DIV_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ EXACT_DIV_ಅಭಿವ್ಯಕ್ತಿ:
      may_need_excess_precision = ಸತ್ಯ;
      ಭಙ್ಗ;

    ಪಕ್ಷ EQ_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ NE_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ LE_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ GE_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ LT_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ GT_ಅಭಿವ್ಯಕ್ತಿ:
      /* Excess precision for implicit conversions of integers to
	 floating point in C11 and later.  */
      may_need_excess_precision = (flag_isoc11
				   && (ANY_INTEGRAL_TYPE_P (type0)
				       || ANY_INTEGRAL_TYPE_P (type1)));
      ಭಙ್ಗ;

    ಸ್ವಭಾವ:
      may_need_excess_precision = ಅಸತ್ಯ;
      ಭಙ್ಗ;
    }
  ಯದಿ (ವೃಕ್ಷ_CODE (op0) == EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ)
    {
      op0 = ವೃಕ್ಷ_OPERAND (op0, 0);
      type0 = ವೃಕ್ಷ_TYPE (op0);
    }
  ಅನ್ಯಥಾ ಯದಿ (may_need_excess_precision
	   && (eptype = excess_precision_type (type0)) != NULL_ವೃಕ್ಷ)
    {
      type0 = eptype;
      op0 = convert (eptype, op0);
    }
  ಯದಿ (ವೃಕ್ಷ_CODE (op1) == EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ)
    {
      op1 = ವೃಕ್ಷ_OPERAND (op1, 0);
      type1 = ವೃಕ್ಷ_TYPE (op1);
    }
  ಅನ್ಯಥಾ ಯದಿ (may_need_excess_precision
	   && (eptype = excess_precision_type (type1)) != NULL_ವೃಕ್ಷ)
    {
      type1 = eptype;
      op1 = convert (eptype, op1);
    }

  objc_ok = objc_compare_types (type0, type1, -3, NULL_ವೃಕ್ಷ);

  /* In case when one of the operands of the binary operation is
     a vector and another is a scalar -- convert scalar to vector.  */
  ಯದಿ ((gnu_vector_type_p (type0) && code1 != VECTOR_TYPE)
      || (gnu_vector_type_p (type1) && code0 != VECTOR_TYPE))
    {
      ಗಣನಾ stv_conv convert_flag = scalar_to_vector (location, code, orig_op0,
						     orig_op1, ಸತ್ಯ);

      ವಿಕಲ್ಪ (convert_flag)
	{
	  ಪಕ್ಷ stv_error:
	    ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	  ಪಕ್ಷ stv_firstarg:
	    {
              ತಾರ್ಕಿಕ maybe_const = ಸತ್ಯ;
              ವೃಕ್ಷ sc;
              sc = c_fully_fold (op0, ಅಸತ್ಯ, &maybe_const);
              sc = save_ಅಭಿವ್ಯಕ್ತಿ (sc);
              sc = convert (ವೃಕ್ಷ_TYPE (type1), sc);
              op0 = build_vector_from_val (type1, sc);
              ಯದಿ (!maybe_const)
                op0 = c_wrap_maybe_const (op0, ಸತ್ಯ);
              orig_type0 = type0 = ವೃಕ್ಷ_TYPE (op0);
              code0 = ವೃಕ್ಷ_CODE (type0);
              converted = 1;
              ಭಙ್ಗ;
	    }
	  ಪಕ್ಷ stv_secondarg:
	    {
	      ತಾರ್ಕಿಕ maybe_const = ಸತ್ಯ;
	      ವೃಕ್ಷ sc;
	      sc = c_fully_fold (op1, ಅಸತ್ಯ, &maybe_const);
	      sc = save_ಅಭಿವ್ಯಕ್ತಿ (sc);
	      sc = convert (ವೃಕ್ಷ_TYPE (type0), sc);
	      op1 = build_vector_from_val (type0, sc);
	      ಯದಿ (!maybe_const)
		op1 = c_wrap_maybe_const (op1, ಸತ್ಯ);
	      orig_type1 = type1 = ವೃಕ್ಷ_TYPE (op1);
	      code1 = ವೃಕ್ಷ_CODE (type1);
	      converted = 1;
	      ಭಙ್ಗ;
	    }
	  ಸ್ವಭಾವ:
	    ಭಙ್ಗ;
	}
    }

  ವಿಕಲ್ಪ (code)
    {
    ಪಕ್ಷ PLUS_ಅಭಿವ್ಯಕ್ತಿ:
      /* Handle the pointer + int case.  */
      ಯದಿ (code0 == POINTER_TYPE
	  && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  ret = pointer_int_sum (location, PLUS_ಅಭಿವ್ಯಕ್ತಿ, op0, op1);
	  ಗಚ್ಛ return_build_ದ್ವಿಮಾನ_op;
	}
      ಅನ್ಯಥಾ ಯದಿ (code1 == POINTER_TYPE
	       && (code0 == INTEGER_TYPE || code0 == BITINT_TYPE))
	{
	  ret = pointer_int_sum (location, PLUS_ಅಭಿವ್ಯಕ್ತಿ, op1, op0);
	  ಗಚ್ಛ return_build_ದ್ವಿಮಾನ_op;
	}
      ಅನ್ಯಥಾ
	common = 1;
      ಭಙ್ಗ;

    ಪಕ್ಷ MINUS_ಅಭಿವ್ಯಕ್ತಿ:
      /* Subtraction of two similar pointers.
	 We must subtract them as integers, then divide by object size.  */
      ಯದಿ (code0 == POINTER_TYPE && code1 == POINTER_TYPE
	  && comp_target_types (location, type0, type1))
	{
	  ret = pointer_diff (location, op0, op1, &instrument_ಅಭಿವ್ಯಕ್ತಿ);
	  ಗಚ್ಛ return_build_ದ್ವಿಮಾನ_op;
	}
      /* Handle pointer minus int.  Just like pointer plus int.  */
      ಅನ್ಯಥಾ ಯದಿ (code0 == POINTER_TYPE
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  ret = pointer_int_sum (location, MINUS_ಅಭಿವ್ಯಕ್ತಿ, op0, op1);
	  ಗಚ್ಛ return_build_ದ್ವಿಮಾನ_op;
	}
      ಅನ್ಯಥಾ
	common = 1;
      ಭಙ್ಗ;

    ಪಕ್ಷ MULT_ಅಭಿವ್ಯಕ್ತಿ:
      common = 1;
      ಭಙ್ಗ;

    ಪಕ್ಷ TRUNC_DIV_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ CEIL_DIV_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ FLOOR_DIV_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ ROUND_DIV_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ EXACT_DIV_ಅಭಿವ್ಯಕ್ತಿ:
      doing_div_or_mod = ಸತ್ಯ;
      warn_for_div_by_zero (location, op1);

      ಯದಿ ((code0 == INTEGER_TYPE || code0 == REAL_TYPE
	   || code0 == FIXED_POINT_TYPE || code0 == BITINT_TYPE
	   || code0 == COMPLEX_TYPE
	   || gnu_vector_type_p (type0))
	  && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	      || code1 == FIXED_POINT_TYPE || code1 == BITINT_TYPE
	      || code1 == COMPLEX_TYPE
	      || gnu_vector_type_p (type1)))
	{
	  ಗಣನಾ ವೃಕ್ಷ_code tcode0 = code0, tcode1 = code1;

	  ಯದಿ (code0 == COMPLEX_TYPE || code0 == VECTOR_TYPE)
	    tcode0 = ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (op0)));
	  ಯದಿ (code1 == COMPLEX_TYPE || code1 == VECTOR_TYPE)
	    tcode1 = ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (op1)));

	  ಯದಿ (!(((tcode0 == INTEGER_TYPE || tcode0 == BITINT_TYPE
		  || (tcode0 == ENUMERAL_TYPE && code0 == VECTOR_TYPE))
		 && (tcode1 == INTEGER_TYPE || tcode1 == BITINT_TYPE
		     || (tcode1 == ENUMERAL_TYPE && code1 == VECTOR_TYPE)))
		|| (tcode0 == FIXED_POINT_TYPE && tcode1 == FIXED_POINT_TYPE)))
	    resultcode = RDIV_ಅಭಿವ್ಯಕ್ತಿ;
	  ಅನ್ಯಥಾ
	    /* Although it would be tempting to shorten always here, that
	       loses on some targets, since the modulo instruction is
	       undefined if the quotient can't be represented in the
	       computation mode.  We shorten only if unsigned or if
	       dividing by something we know != -1.  */
	    shorten = may_shorten_divmod (op0, op1);
	  common = 1;
	}
      ಭಙ್ಗ;

    ಪಕ್ಷ BIT_AND_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ BIT_IOR_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ BIT_XOR_ಅಭಿವ್ಯಕ್ತಿ:
      ಯದಿ ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	shorten = -1;
      /* Allow vector types which are not floating point types.   */
      ಅನ್ಯಥಾ ಯದಿ (gnu_vector_type_p (type0)
	       && gnu_vector_type_p (type1)
	       && !VECTOR_FLOAT_TYPE_P (type0)
	       && !VECTOR_FLOAT_TYPE_P (type1))
	common = 1;
      ಭಙ್ಗ;

    ಪಕ್ಷ TRUNC_MOD_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ FLOOR_MOD_ಅಭಿವ್ಯಕ್ತಿ:
      doing_div_or_mod = ಸತ್ಯ;
      warn_for_div_by_zero (location, op1);

      ಯದಿ (gnu_vector_type_p (type0)
	  && gnu_vector_type_p (type1)
	  && ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (type0)) == INTEGER_TYPE
	  && ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (type1)) == INTEGER_TYPE)
	common = 1;
      ಅನ್ಯಥಾ ಯದಿ ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  /* Although it would be tempting to shorten always here, that loses
	     on some targets, since the modulo instruction is undefined if the
	     quotient can't be represented in the computation mode.  We shorten
	     only if unsigned or if dividing by something we know != -1.  */
	  shorten = may_shorten_divmod (op0, op1);
	  common = 1;
	}
      ಭಙ್ಗ;

    ಪಕ್ಷ TRUTH_ANDIF_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ TRUTH_ORIF_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ TRUTH_AND_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ TRUTH_OR_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ TRUTH_XOR_ಅಭಿವ್ಯಕ್ತಿ:
      ಯದಿ ((code0 == INTEGER_TYPE || code0 == POINTER_TYPE
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
	  result_type = integer_type_ಗಂಟು;
	  ಯದಿ (op0_int_operands)
	    {
	      op0 = c_objc_common_truthvalue_conversion (location, orig_op0);
	      op0 = remove_c_maybe_const_ಅಭಿವ್ಯಕ್ತಿ (op0);
	    }
	  ಅನ್ಯಥಾ
	    op0 = c_objc_common_truthvalue_conversion (location, op0);
	  ಯದಿ (op1_int_operands)
	    {
	      op1 = c_objc_common_truthvalue_conversion (location, orig_op1);
	      op1 = remove_c_maybe_const_ಅಭಿವ್ಯಕ್ತಿ (op1);
	    }
	  ಅನ್ಯಥಾ
	    op1 = c_objc_common_truthvalue_conversion (location, op1);
	  converted = 1;
	  boolean_op = ಸತ್ಯ;
	}
      ಯದಿ (code == TRUTH_ANDIF_ಅಭಿವ್ಯಕ್ತಿ)
	{
	  int_const_or_overflow = (int_operands
				   && ವೃಕ್ಷ_CODE (orig_op0) == INTEGER_CST
				   && (op0 == truthvalue_false_ಗಂಟು
				       || ವೃಕ್ಷ_CODE (orig_op1) == INTEGER_CST));
	  int_const = (int_const_or_overflow
		       && !ವೃಕ್ಷ_OVERFLOW (orig_op0)
		       && (op0 == truthvalue_false_ಗಂಟು
			   || !ವೃಕ್ಷ_OVERFLOW (orig_op1)));
	}
      ಅನ್ಯಥಾ ಯದಿ (code == TRUTH_ORIF_ಅಭಿವ್ಯಕ್ತಿ)
	{
	  int_const_or_overflow = (int_operands
				   && ವೃಕ್ಷ_CODE (orig_op0) == INTEGER_CST
				   && (op0 == truthvalue_true_ಗಂಟು
				       || ವೃಕ್ಷ_CODE (orig_op1) == INTEGER_CST));
	  int_const = (int_const_or_overflow
		       && !ವೃಕ್ಷ_OVERFLOW (orig_op0)
		       && (op0 == truthvalue_true_ಗಂಟು
			   || !ವೃಕ್ಷ_OVERFLOW (orig_op1)));
	}
      ಭಙ್ಗ;

      /* Shift operations: result has same type as first operand;
	 always convert second operand to int.
	 Also set SHORT_SHIFT if shifting rightward.  */

    ಪಕ್ಷ RSHIFT_ಅಭಿವ್ಯಕ್ತಿ:
      ಯದಿ (gnu_vector_type_p (type0)
	  && gnu_vector_type_p (type1)
	  && ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (type0)) == INTEGER_TYPE
	  && ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (type1)) == INTEGER_TYPE
	  && known_eq (TYPE_VECTOR_SUBPARTS (type0),
		       TYPE_VECTOR_SUBPARTS (type1)))
	{
	  result_type = type0;
	  converted = 1;
	}
      ಅನ್ಯಥಾ ಯದಿ ((code0 == INTEGER_TYPE || code0 == FIXED_POINT_TYPE
		|| code0 == BITINT_TYPE
		|| (gnu_vector_type_p (type0)
		    && ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (type0)) == INTEGER_TYPE))
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  doing_shift = ಸತ್ಯ;
	  ಯದಿ (ವೃಕ್ಷ_CODE (op1) == INTEGER_CST)
	    {
	      ಯದಿ (ವೃಕ್ಷ_int_cst_sgn (op1) < 0)
		{
		  int_const = ಅಸತ್ಯ;
		  ಯದಿ (c_inhibit_evaluation_warnings == 0)
		    warning_at (location, OPT_Wshift_ಎಣಿಕೆ_negative,
				"right shift count is negative");
		}
	      ಅನ್ಯಥಾ ಯದಿ (code0 == VECTOR_TYPE)
		{
		  ಯದಿ (compare_ವೃಕ್ಷ_int (op1,
					TYPE_PRECISION (ವೃಕ್ಷ_TYPE (type0)))
		      >= 0)
		    {
		      int_const = ಅಸತ್ಯ;
		      ಯದಿ (c_inhibit_evaluation_warnings == 0)
			warning_at (location, OPT_Wshift_ಎಣಿಕೆ_overflow,
				    "right shift count >= width of vector element");
		    }
		}
	      ಅನ್ಯಥಾ
		{
		  ಯದಿ (!integer_zerop (op1))
		    short_shift = 1;

		  ಯದಿ (compare_ವೃಕ್ಷ_int (op1, TYPE_PRECISION (type0)) >= 0)
		    {
		      int_const = ಅಸತ್ಯ;
		      ಯದಿ (c_inhibit_evaluation_warnings == 0)
			warning_at (location, OPT_Wshift_ಎಣಿಕೆ_overflow,
				    "right shift count >= width of type");
		    }
		}
	    }

	  /* Use the type of the value to be shifted.  */
	  result_type = type0;
	  /* Avoid converting op1 to result_type later.  */
	  converted = 1;
	}
      ಭಙ್ಗ;

    ಪಕ್ಷ LSHIFT_ಅಭಿವ್ಯಕ್ತಿ:
      ಯದಿ (gnu_vector_type_p (type0)
	  && gnu_vector_type_p (type1)
	  && ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (type0)) == INTEGER_TYPE
	  && ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (type1)) == INTEGER_TYPE
	  && known_eq (TYPE_VECTOR_SUBPARTS (type0),
		       TYPE_VECTOR_SUBPARTS (type1)))
	{
	  result_type = type0;
	  converted = 1;
	}
      ಅನ್ಯಥಾ ಯದಿ ((code0 == INTEGER_TYPE || code0 == FIXED_POINT_TYPE
		|| code0 == BITINT_TYPE
		|| (gnu_vector_type_p (type0)
		    && ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (type0)) == INTEGER_TYPE))
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  doing_shift = ಸತ್ಯ;
	  ಯದಿ (ವೃಕ್ಷ_CODE (op0) == INTEGER_CST
	      && ವೃಕ್ಷ_int_cst_sgn (op0) < 0
	      && !TYPE_OVERFLOW_WRAPS (type0))
	    {
	      /* Don't reject a left shift of a negative value in a context
		 where a constant expression is needed in C90.  */
	      ಯದಿ (flag_isoc99)
		int_const = ಅಸತ್ಯ;
	      ಯದಿ (c_inhibit_evaluation_warnings == 0)
		warning_at (location, OPT_Wshift_negative_ಮೌಲ್ಯ,
			    "left shift of negative value");
	    }
	  ಯದಿ (ವೃಕ್ಷ_CODE (op1) == INTEGER_CST)
	    {
	      ಯದಿ (ವೃಕ್ಷ_int_cst_sgn (op1) < 0)
		{
		  int_const = ಅಸತ್ಯ;
		  ಯದಿ (c_inhibit_evaluation_warnings == 0)
		    warning_at (location, OPT_Wshift_ಎಣಿಕೆ_negative,
				"left shift count is negative");
		}
	      ಅನ್ಯಥಾ ಯದಿ (code0 == VECTOR_TYPE)
		{
		  ಯದಿ (compare_ವೃಕ್ಷ_int (op1,
					TYPE_PRECISION (ವೃಕ್ಷ_TYPE (type0)))
		      >= 0)
		    {
		      int_const = ಅಸತ್ಯ;
		      ಯದಿ (c_inhibit_evaluation_warnings == 0)
			warning_at (location, OPT_Wshift_ಎಣಿಕೆ_overflow,
				    "left shift count >= width of vector element");
		    }
		}
	      ಅನ್ಯಥಾ ಯದಿ (compare_ವೃಕ್ಷ_int (op1, TYPE_PRECISION (type0)) >= 0)
		{
		  int_const = ಅಸತ್ಯ;
		  ಯದಿ (c_inhibit_evaluation_warnings == 0)
		    warning_at (location, OPT_Wshift_ಎಣಿಕೆ_overflow,
				"left shift count >= width of type");
		}
	      ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (op0) == INTEGER_CST
		       && maybe_warn_shift_overflow (location, op0, op1)
		       && flag_isoc99)
		int_const = ಅಸತ್ಯ;
	    }

	  /* Use the type of the value to be shifted.  */
	  result_type = type0;
	  /* Avoid converting op1 to result_type later.  */
	  converted = 1;
	}
      ಭಙ್ಗ;

    ಪಕ್ಷ EQ_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ NE_ಅಭಿವ್ಯಕ್ತಿ:
      ಯದಿ (gnu_vector_type_p (type0) && gnu_vector_type_p (type1))
        {
          ವೃಕ್ಷ intt;
	  ಯದಿ (!vector_types_compatible_elements_p (type0, type1))
            {
              error_at (location, "comparing vectors with different "
                                  "element types");
              ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
            }

	  ಯದಿ (maybe_ne (TYPE_VECTOR_SUBPARTS (type0),
			TYPE_VECTOR_SUBPARTS (type1)))
            {
              error_at (location, "comparing vectors with different "
                                  "number of elements");
              ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
            }

	  /* It's not precisely specified how the usual arithmetic
	     conversions apply to the vector types.  Here, we use
	     the unsigned type if one of the operands is signed and
	     the other one is unsigned.  */
	  ಯದಿ (TYPE_UNSIGNED (type0) != TYPE_UNSIGNED (type1))
	    {
	      ಯದಿ (!TYPE_UNSIGNED (type0))
		op0 = build1 (VIEW_CONVERT_ಅಭಿವ್ಯಕ್ತಿ, type1, op0);
	      ಅನ್ಯಥಾ
		op1 = build1 (VIEW_CONVERT_ಅಭಿವ್ಯಕ್ತಿ, type0, op1);
	      warning_at (location, OPT_Wsign_compare, "comparison between "
			  "types %qT and %qT", type0, type1);
	    }

          /* Always construct signed integer vector type.  */
	  ಯದಿ (VECTOR_BOOLEAN_TYPE_P (type0) && VECTOR_BOOLEAN_TYPE_P (type1))
	    result_type = type0;
	  ಅನ್ಯಥಾ
	    {
	      auto nelts = TYPE_VECTOR_SUBPARTS (type0);

	      intt = c_common_type_for_size (GET_MODE_BITSIZE
					     (SCALAR_TYPE_MODE
						(ವೃಕ್ಷ_TYPE (type0))), 0);
	      ಯದಿ (!intt)
		{
		  error_at (location, "could not find an integer type "
				      "of the same size as %qT",
			    ವೃಕ್ಷ_TYPE (type0));
		  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
		}
	      result_type = build_opaque_vector_type (intt, nelts);
	    }
          converted = 1;
	  ret = build_vec_cmp (resultcode, result_type, op0, op1);
	  ಗಚ್ಛ return_build_ದ್ವಿಮಾನ_op;
        }
      ಯದಿ (FLOAT_TYPE_P (type0) || FLOAT_TYPE_P (type1))
	warning_at (location,
		    OPT_Wfloat_equal,
		    "comparing floating-point with %<==%> or %<!=%> is unsafe");
      /* Result of comparison is always int,
	 but don't convert the args to int!  */
      build_type = integer_type_ಗಂಟು;
      ಯದಿ ((code0 == INTEGER_TYPE || code0 == REAL_TYPE || code0 == BITINT_TYPE
	   || code0 == FIXED_POINT_TYPE || code0 == COMPLEX_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	      || code1 == BITINT_TYPE
	      || code1 == FIXED_POINT_TYPE || code1 == COMPLEX_TYPE))
	short_compare = 1;
      ಅನ್ಯಥಾ ಯದಿ (code0 == POINTER_TYPE
	       && (code1 == NULLPTR_TYPE
		   || null_pointer_constant_p (orig_op1)))
	{
	  maybe_warn_for_null_address (location, op0, code);
	  result_type = type0;
	}
      ಅನ್ಯಥಾ ಯದಿ (code1 == POINTER_TYPE
	       && (code0 == NULLPTR_TYPE
		   || null_pointer_constant_p (orig_op0)))
	{
	  maybe_warn_for_null_address (location, op1, code);
	  result_type = type1;
	}
      ಅನ್ಯಥಾ ಯದಿ (code0 == POINTER_TYPE && code1 == POINTER_TYPE)
	{
	  ವೃಕ್ಷ tt0 = ವೃಕ್ಷ_TYPE (type0);
	  ವೃಕ್ಷ tt1 = ವೃಕ್ಷ_TYPE (type1);
	  addr_space_t as0 = TYPE_ADDR_SPACE (tt0);
	  addr_space_t as1 = TYPE_ADDR_SPACE (tt1);
	  addr_space_t as_common = ADDR_SPACE_GENERIC;

	  /* Anything compares with void *.  void * compares with anything.
	     Otherwise, the targets must be compatible
	     and both must be object or both incomplete.  */
	  ಯದಿ (comp_target_types (location, type0, type1))
	    result_type = common_pointer_type (type0, type1, NULL_ವೃಕ್ಷ);
	  ಅನ್ಯಥಾ ಯದಿ (!addr_space_superset (as0, as1, &as_common))
	    {
	      error_at (location, "comparison of pointers to "
			"disjoint address spaces");
	      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	    }
	  ಅನ್ಯಥಾ ಯದಿ (VOID_TYPE_P (tt0) && !TYPE_ATOMIC (tt0))
	    {
	      ಯದಿ (pedantic && ವೃಕ್ಷ_CODE (tt1) == FUNCTION_TYPE)
		pedwarn (location, OPT_Wpedantic, "ISO C forbids "
			 "comparison of %<void *%> with function pointer");
	    }
	  ಅನ್ಯಥಾ ಯದಿ (VOID_TYPE_P (tt1) && !TYPE_ATOMIC (tt1))
	    {
	      ಯದಿ (pedantic && ವೃಕ್ಷ_CODE (tt0) == FUNCTION_TYPE)
		pedwarn (location, OPT_Wpedantic, "ISO C forbids "
			 "comparison of %<void *%> with function pointer");
	    }
	  ಅನ್ಯಥಾ
	    /* Avoid warning about the volatile ObjC EH puts on decls.  */
	    ಯದಿ (!objc_ok)
	      pedwarn (location, OPT_Wcompare_distinct_pointer_types,
		       "comparison of distinct pointer types lacks a cast");

	  ಯದಿ (result_type == NULL_ವೃಕ್ಷ)
	    {
	      ಪೂರ್ಣಾಙ್ಕ qual = ENCODE_QUAL_ADDR_SPACE (as_common);
	      result_type = c_build_pointer_type
			      (c_build_qualified_type (void_type_ಗಂಟು, qual));
	    }
	}
      ಅನ್ಯಥಾ ಯದಿ (code0 == POINTER_TYPE
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  result_type = type0;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}
      ಅನ್ಯಥಾ ಯದಿ ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	       && code1 == POINTER_TYPE)
	{
	  result_type = type1;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}
      /* 6.5.9: One of the following shall hold:
	 -- both operands have type nullptr_t;  */
      ಅನ್ಯಥಾ ಯದಿ (code0 == NULLPTR_TYPE && code1 == NULLPTR_TYPE)
	{
	  result_type = nullptr_type_ಗಂಟು;
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
      ಅನ್ಯಥಾ ಯದಿ (code0 == NULLPTR_TYPE && null_pointer_constant_p (orig_op1))
	result_type = (INTEGRAL_TYPE_P (type1)
		       ? c_build_pointer_type (type1) : type1);
      ಅನ್ಯಥಾ ಯದಿ (code1 == NULLPTR_TYPE && null_pointer_constant_p (orig_op0))
	result_type = (INTEGRAL_TYPE_P (type0)
		       ? c_build_pointer_type (type0) : type0);
      ಯದಿ ((C_BOOLEAN_TYPE_P (ವೃಕ್ಷ_TYPE (orig_op0))
	   || truth_ಮೌಲ್ಯ_p (ವೃಕ್ಷ_CODE (orig_op0)))
	  ^ (C_BOOLEAN_TYPE_P (ವೃಕ್ಷ_TYPE (orig_op1))
	     || truth_ಮೌಲ್ಯ_p (ವೃಕ್ಷ_CODE (orig_op1))))
	maybe_warn_bool_compare (location, code, orig_op0, orig_op1);
      ಭಙ್ಗ;

    ಪಕ್ಷ LE_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ GE_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ LT_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ GT_ಅಭಿವ್ಯಕ್ತಿ:
      ಯದಿ (gnu_vector_type_p (type0) && gnu_vector_type_p (type1))
        {
          ವೃಕ್ಷ intt;
	  ಯದಿ (!vector_types_compatible_elements_p (type0, type1))
            {
              error_at (location, "comparing vectors with different "
                                  "element types");
              ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
            }

	  ಯದಿ (maybe_ne (TYPE_VECTOR_SUBPARTS (type0),
			TYPE_VECTOR_SUBPARTS (type1)))
            {
              error_at (location, "comparing vectors with different "
                                  "number of elements");
              ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
            }

	  /* It's not precisely specified how the usual arithmetic
	     conversions apply to the vector types.  Here, we use
	     the unsigned type if one of the operands is signed and
	     the other one is unsigned.  */
	  ಯದಿ (TYPE_UNSIGNED (type0) != TYPE_UNSIGNED (type1))
	    {
	      ಯದಿ (!TYPE_UNSIGNED (type0))
		op0 = build1 (VIEW_CONVERT_ಅಭಿವ್ಯಕ್ತಿ, type1, op0);
	      ಅನ್ಯಥಾ
		op1 = build1 (VIEW_CONVERT_ಅಭಿವ್ಯಕ್ತಿ, type0, op1);
	      warning_at (location, OPT_Wsign_compare, "comparison between "
			  "types %qT and %qT", type0, type1);
	    }

          /* Always construct signed integer vector type.  */
          intt = c_common_type_for_size (GET_MODE_BITSIZE
					 (SCALAR_TYPE_MODE
					  (ವೃಕ್ಷ_TYPE (type0))), 0);
	  ಯದಿ (!intt)
	    {
	      error_at (location, "could not find an integer type "
				  "of the same size as %qT",
			ವೃಕ್ಷ_TYPE (type0));
	      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	    }
          result_type = build_opaque_vector_type (intt,
						  TYPE_VECTOR_SUBPARTS (type0));
          converted = 1;
	  ret = build_vec_cmp (resultcode, result_type, op0, op1);
	  ಗಚ್ಛ return_build_ದ್ವಿಮಾನ_op;
        }
      build_type = integer_type_ಗಂಟು;
      ಯದಿ ((code0 == INTEGER_TYPE || code0 == REAL_TYPE
	   || code0 == BITINT_TYPE || code0 == FIXED_POINT_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	      || code1 == BITINT_TYPE || code1 == FIXED_POINT_TYPE))
	short_compare = 1;
      ಅನ್ಯಥಾ ಯದಿ (code0 == POINTER_TYPE && code1 == POINTER_TYPE)
	{
	  addr_space_t as0 = TYPE_ADDR_SPACE (ವೃಕ್ಷ_TYPE (type0));
	  addr_space_t as1 = TYPE_ADDR_SPACE (ವೃಕ್ಷ_TYPE (type1));
	  addr_space_t as_common;

	  ಯದಿ (comp_target_types (location, type0, type1))
	    {
	      result_type = common_pointer_type (type0, type1, NULL_ವೃಕ್ಷ);
	      ಯದಿ (!COMPLETE_TYPE_P (ವೃಕ್ಷ_TYPE (type0))
		  != !COMPLETE_TYPE_P (ವೃಕ್ಷ_TYPE (type1)))
		pedwarn_c99 (location, OPT_Wpedantic,
			     "comparison of complete and incomplete pointers");
	      ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (type0)) == FUNCTION_TYPE)
		pedwarn (location, OPT_Wpedantic, "ISO C forbids "
			 "ordered comparisons of pointers to functions");
	      ಅನ್ಯಥಾ ಯದಿ (null_pointer_constant_p (orig_op0)
		       || null_pointer_constant_p (orig_op1))
		warning_at (location, OPT_Wextra,
			    "ordered comparison of pointer with null pointer");

	    }
	  ಅನ್ಯಥಾ ಯದಿ (!addr_space_superset (as0, as1, &as_common))
	    {
	      error_at (location, "comparison of pointers to "
			"disjoint address spaces");
	      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	    }
	  ಅನ್ಯಥಾ
	    {
	      ಪೂರ್ಣಾಙ್ಕ qual = ENCODE_QUAL_ADDR_SPACE (as_common);
	      result_type = c_build_pointer_type
			      (c_build_qualified_type (void_type_ಗಂಟು, qual));
              pedwarn (location, OPT_Wcompare_distinct_pointer_types,
                       "comparison of distinct pointer types lacks a cast");
	    }
	}
      ಅನ್ಯಥಾ ಯದಿ (code0 == POINTER_TYPE && null_pointer_constant_p (orig_op1))
	{
	  result_type = type0;
	  ಯದಿ (pedantic)
	    pedwarn (location, OPT_Wpedantic,
		     "ordered comparison of pointer with integer zero");
	  ಅನ್ಯಥಾ ಯದಿ (extra_warnings)
	    warning_at (location, OPT_Wextra,
			"ordered comparison of pointer with integer zero");
	}
      ಅನ್ಯಥಾ ಯದಿ (code1 == POINTER_TYPE && null_pointer_constant_p (orig_op0))
	{
	  result_type = type1;
	  ಯದಿ (pedantic)
	    pedwarn (location, OPT_Wpedantic,
		     "ordered comparison of pointer with integer zero");
	  ಅನ್ಯಥಾ ಯದಿ (extra_warnings)
	    warning_at (location, OPT_Wextra,
			"ordered comparison of pointer with integer zero");
	}
      ಅನ್ಯಥಾ ಯದಿ (code0 == POINTER_TYPE
	       && (code1 == INTEGER_TYPE || code1 == BITINT_TYPE))
	{
	  result_type = type0;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}
      ಅನ್ಯಥಾ ಯದಿ ((code0 == INTEGER_TYPE || code0 == BITINT_TYPE)
	       && code1 == POINTER_TYPE)
	{
	  result_type = type1;
	  pedwarn (location, 0, "comparison between pointer and integer");
	}

      ಯದಿ ((code0 == POINTER_TYPE || code1 == POINTER_TYPE)
	  && current_function_decl != NULL_ವೃಕ್ಷ
	  && sanitize_flags_p (SANITIZE_POINTER_COMPARE))
	{
	  op0 = save_ಅಭಿವ್ಯಕ್ತಿ (c_fully_fold (op0, ಅಸತ್ಯ, ರಿಕ್ತ));
	  op1 = save_ಅಭಿವ್ಯಕ್ತಿ (c_fully_fold (op1, ಅಸತ್ಯ, ರಿಕ್ತ));

	  ವೃಕ್ಷ tt = builtin_decl_explicit (BUILT_IN_ASAN_POINTER_COMPARE);
	  instrument_ಅಭಿವ್ಯಕ್ತಿ = build_call_ಅಭಿವ್ಯಕ್ತಿ_loc (location, tt, 2, op0, op1);
	}

      ಯದಿ ((C_BOOLEAN_TYPE_P (ವೃಕ್ಷ_TYPE (orig_op0))
	   || truth_ಮೌಲ್ಯ_p (ವೃಕ್ಷ_CODE (orig_op0)))
	  ^ (C_BOOLEAN_TYPE_P (ವೃಕ್ಷ_TYPE (orig_op1))
	     || truth_ಮೌಲ್ಯ_p (ವೃಕ್ಷ_CODE (orig_op1))))
	maybe_warn_bool_compare (location, code, orig_op0, orig_op1);
      ಭಙ್ಗ;

    ಪಕ್ಷ MIN_ಅಭಿವ್ಯಕ್ತಿ:
    ಪಕ್ಷ MAX_ಅಭಿವ್ಯಕ್ತಿ:
      /* Used for OpenMP atomics.  */
      gcc_assert (flag_openmp);
      common = 1;
      ಭಙ್ಗ;

    ಸ್ವಭಾವ:
      gcc_unreachable ();
    }

  ಯದಿ (code0 == ERROR_MARK || code1 == ERROR_MARK)
    ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;

  ಯದಿ (gnu_vector_type_p (type0)
      && gnu_vector_type_p (type1)
      && (!ವೃಕ್ಷ_int_cst_equal (TYPE_SIZE (type0), TYPE_SIZE (type1))
	  || !vector_types_compatible_elements_p (type0, type1)))
    {
      gcc_rich_location richloc (location);
      maybe_range_label_for_ವೃಕ್ಷ_type_mismatch
	label_for_op0 (orig_op0, orig_op1),
	label_for_op1 (orig_op1, orig_op0);
      richloc.maybe_add_ಅಭಿವ್ಯಕ್ತಿ (orig_op0, &label_for_op0, highlight_colors::lhs);
      richloc.maybe_add_ಅಭಿವ್ಯಕ್ತಿ (orig_op1, &label_for_op1, highlight_colors::rhs);
      ದ್ವಿಮಾನ_op_error (&richloc, code, type0, type1);
      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
    }

  ಯದಿ ((code0 == INTEGER_TYPE || code0 == REAL_TYPE || code0 == COMPLEX_TYPE
       || code0 == FIXED_POINT_TYPE || code0 == BITINT_TYPE
       || gnu_vector_type_p (type0))
      && (code1 == INTEGER_TYPE || code1 == REAL_TYPE || code1 == COMPLEX_TYPE
	  || code1 == FIXED_POINT_TYPE || code1 == BITINT_TYPE
	  || gnu_vector_type_p (type1)))
    {
      ತಾರ್ಕಿಕ first_complex = (code0 == COMPLEX_TYPE);
      ತಾರ್ಕಿಕ second_complex = (code1 == COMPLEX_TYPE);
      ಪೂರ್ಣಾಙ್ಕ none_complex = (!first_complex && !second_complex);

      ಯದಿ (shorten || common || short_compare)
	{
	  result_type = c_common_type (type0, type1);
	  do_warn_double_promotion (result_type, type0, type1,
				    "implicit conversion from %qT to %qT "
				    "to match other operand of binary "
				    "expression",
				    location);
	  ಯದಿ (result_type == error_mark_ಗಂಟು)
	    ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	}

      ಯದಿ (first_complex != second_complex
	  && (code == PLUS_ಅಭಿವ್ಯಕ್ತಿ
	      || code == MINUS_ಅಭಿವ್ಯಕ್ತಿ
	      || code == MULT_ಅಭಿವ್ಯಕ್ತಿ
	      || (code == TRUNC_DIV_ಅಭಿವ್ಯಕ್ತಿ && first_complex))
	  && ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (result_type)) == REAL_TYPE
	  && flag_signed_zeros)
	{
	  /* An operation on mixed real/complex operands must be
	     handled specially, but the language-independent code can
	     more easily optimize the plain complex arithmetic if
	     -fno-signed-zeros.  */
	  ವೃಕ್ಷ real_type = ವೃಕ್ಷ_TYPE (result_type);
	  ವೃಕ್ಷ real, imag;
	  ಯದಿ (type0 != orig_type0 || type1 != orig_type1)
	    {
	      gcc_assert (may_need_excess_precision && common);
	      semantic_result_type = c_common_type (orig_type0, orig_type1);
	    }
	  ಯದಿ (first_complex)
	    {
	      ಯದಿ (ವೃಕ್ಷ_TYPE (op0) != result_type)
		op0 = convert_and_check (location, result_type, op0);
	      ಯದಿ (ವೃಕ್ಷ_TYPE (op1) != real_type)
		op1 = convert_and_check (location, real_type, op1);
	    }
	  ಅನ್ಯಥಾ
	    {
	      ಯದಿ (ವೃಕ್ಷ_TYPE (op0) != real_type)
		op0 = convert_and_check (location, real_type, op0);
	      ಯದಿ (ವೃಕ್ಷ_TYPE (op1) != result_type)
		op1 = convert_and_check (location, result_type, op1);
	    }
	  ಯದಿ (ವೃಕ್ಷ_CODE (op0) == ERROR_MARK || ವೃಕ್ಷ_CODE (op1) == ERROR_MARK)
	    ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	  ಯದಿ (first_complex)
	    {
	      op0 = save_ಅಭಿವ್ಯಕ್ತಿ (op0);
	      real = build_unary_op (ಅಭಿವ್ಯಕ್ತಿ_LOCATION (orig_op0), REALPART_ಅಭಿವ್ಯಕ್ತಿ,
				     op0, ಸತ್ಯ);
	      imag = build_unary_op (ಅಭಿವ್ಯಕ್ತಿ_LOCATION (orig_op0), IMAGPART_ಅಭಿವ್ಯಕ್ತಿ,
				     op0, ಸತ್ಯ);
	      ವಿಕಲ್ಪ (code)
		{
		ಪಕ್ಷ MULT_ಅಭಿವ್ಯಕ್ತಿ:
		ಪಕ್ಷ TRUNC_DIV_ಅಭಿವ್ಯಕ್ತಿ:
		  op1 = save_ಅಭಿವ್ಯಕ್ತಿ (op1);
		  imag = build2 (resultcode, real_type, imag, op1);
		  /* Fall through.  */
		ಪಕ್ಷ PLUS_ಅಭಿವ್ಯಕ್ತಿ:
		ಪಕ್ಷ MINUS_ಅಭಿವ್ಯಕ್ತಿ:
		  real = build2 (resultcode, real_type, real, op1);
		  ಭಙ್ಗ;
		ಸ್ವಭಾವ:
		  gcc_unreachable();
		}
	    }
	  ಅನ್ಯಥಾ
	    {
	      op1 = save_ಅಭಿವ್ಯಕ್ತಿ (op1);
	      real = build_unary_op (ಅಭಿವ್ಯಕ್ತಿ_LOCATION (orig_op1), REALPART_ಅಭಿವ್ಯಕ್ತಿ,
				     op1, ಸತ್ಯ);
	      imag = build_unary_op (ಅಭಿವ್ಯಕ್ತಿ_LOCATION (orig_op1), IMAGPART_ಅಭಿವ್ಯಕ್ತಿ,
				     op1, ಸತ್ಯ);
	      ವಿಕಲ್ಪ (code)
		{
		ಪಕ್ಷ MULT_ಅಭಿವ್ಯಕ್ತಿ:
		  op0 = save_ಅಭಿವ್ಯಕ್ತಿ (op0);
		  imag = build2 (resultcode, real_type, op0, imag);
		  /* Fall through.  */
		ಪಕ್ಷ PLUS_ಅಭಿವ್ಯಕ್ತಿ:
		  real = build2 (resultcode, real_type, op0, real);
		  ಭಙ್ಗ;
		ಪಕ್ಷ MINUS_ಅಭಿವ್ಯಕ್ತಿ:
		  real = build2 (resultcode, real_type, op0, real);
		  imag = build1 (NEGATE_ಅಭಿವ್ಯಕ್ತಿ, real_type, imag);
		  ಭಙ್ಗ;
		ಸ್ವಭಾವ:
		  gcc_unreachable();
		}
	    }
	  ret = build2 (COMPLEX_ಅಭಿವ್ಯಕ್ತಿ, result_type, real, imag);
	  ಗಚ್ಛ return_build_ದ್ವಿಮಾನ_op;
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

      ಯದಿ (shorten && none_complex)
	{
	  final_type = result_type;
	  result_type = shorten_ದ್ವಿಮಾನ_op (result_type, op0, op1,
					   shorten == -1);
	}

      /* Shifts can be shortened if shifting right.  */

      ಯದಿ (short_shift)
	{
	  ಪೂರ್ಣಾಙ್ಕ unsigned_arg;
	  ವೃಕ್ಷ arg0 = get_narrower (op0, &unsigned_arg);

	  final_type = result_type;

	  ಯದಿ (arg0 == op0 && final_type == ವೃಕ್ಷ_TYPE (op0))
	    unsigned_arg = TYPE_UNSIGNED (ವೃಕ್ಷ_TYPE (op0));

	  ಯದಿ (TYPE_PRECISION (ವೃಕ್ಷ_TYPE (arg0)) < TYPE_PRECISION (result_type)
	      && ವೃಕ್ಷ_int_cst_sgn (op1) > 0
	      /* We can shorten only if the shift count is less than the
		 number of bits in the smaller type size.  */
	      && compare_ವೃಕ್ಷ_int (op1, TYPE_PRECISION (ವೃಕ್ಷ_TYPE (arg0))) < 0
	      /* We cannot drop an unsigned shift after sign-extension.  */
	      && (!TYPE_UNSIGNED (final_type) || unsigned_arg))
	    {
	      /* Do an unsigned shift if the operand was zero-extended.  */
	      result_type
		= c_common_signed_or_unsigned_type (unsigned_arg,
						    ವೃಕ್ಷ_TYPE (arg0));
	      /* Convert value-to-be-shifted to that type.  */
	      ಯದಿ (ವೃಕ್ಷ_TYPE (op0) != result_type)
		op0 = convert (result_type, op0);
	      converted = 1;
	    }
	}

      /* Comparison operations are shortened too but differently.
	 They identify themselves by setting short_compare = 1.  */

      ಯದಿ (short_compare)
	{
	  /* Don't write &op0, etc., because that would prevent op0
	     from being kept in a register.
	     Instead, make copies of the our local variables and
	     pass the copies by reference, then copy them back afterward.  */
	  ವೃಕ್ಷ xop0 = op0, xop1 = op1, xresult_type = result_type;
	  ಗಣನಾ ವೃಕ್ಷ_code xresultcode = resultcode;
	  ವೃಕ್ಷ val
	    = shorten_compare (location, &xop0, &xop1, &xresult_type,
			       &xresultcode);

	  ಯದಿ (val != NULL_ವೃಕ್ಷ)
	    {
	      ret = val;
	      ಗಚ್ಛ return_build_ದ್ವಿಮಾನ_op;
	    }

	  op0 = xop0, op1 = xop1;
	  converted = 1;
	  resultcode = xresultcode;

	  ಯದಿ (c_inhibit_evaluation_warnings == 0 && !c_in_omp_for)
	    {
	      ತಾರ್ಕಿಕ op0_maybe_const = ಸತ್ಯ;
	      ತಾರ್ಕಿಕ op1_maybe_const = ಸತ್ಯ;
	      ವೃಕ್ಷ orig_op0_folded, orig_op1_folded;

	      ಯದಿ (in_late_ದ್ವಿಮಾನ_op)
		{
		  orig_op0_folded = orig_op0;
		  orig_op1_folded = orig_op1;
		}
	      ಅನ್ಯಥಾ
		{
		  /* Fold for the sake of possible warnings, as in
		     build_conditional_expr.  This requires the
		     "original" values to be folded, not just op0 and
		     op1.  */
		  c_inhibit_evaluation_warnings++;
		  op0 = c_fully_fold (op0, require_constant_ಮೌಲ್ಯ,
				      &op0_maybe_const);
		  op1 = c_fully_fold (op1, require_constant_ಮೌಲ್ಯ,
				      &op1_maybe_const);
		  c_inhibit_evaluation_warnings--;
		  orig_op0_folded = c_fully_fold (orig_op0,
						  require_constant_ಮೌಲ್ಯ,
						  ರಿಕ್ತ);
		  orig_op1_folded = c_fully_fold (orig_op1,
						  require_constant_ಮೌಲ್ಯ,
						  ರಿಕ್ತ);
		}

	      ಯದಿ (warn_sign_compare)
		warn_for_sign_compare (location, orig_op0_folded,
				       orig_op1_folded, op0, op1,
				       result_type, resultcode);
	      ಯದಿ (!in_late_ದ್ವಿಮಾನ_op && !int_operands)
		{
		  ಯದಿ (!op0_maybe_const || ವೃಕ್ಷ_CODE (op0) != INTEGER_CST)
		    op0 = c_wrap_maybe_const (op0, !op0_maybe_const);
		  ಯದಿ (!op1_maybe_const || ವೃಕ್ಷ_CODE (op1) != INTEGER_CST)
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

  ಯದಿ (!result_type)
    {
      /* Favor showing any expression locations that are available. */
      op_location_t oploc (location, UNKNOWN_LOCATION);
      ದ್ವಿಮಾನ_op_rich_location richloc (oploc, orig_op0, orig_op1, ಸತ್ಯ);
      ದ್ವಿಮಾನ_op_error (&richloc, code, ವೃಕ್ಷ_TYPE (op0), ವೃಕ್ಷ_TYPE (op1));
      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
    }

  ಯದಿ (build_type == NULL_ವೃಕ್ಷ)
    {
      build_type = result_type;
      ಯದಿ ((type0 != orig_type0 || type1 != orig_type1)
	  && !boolean_op)
	{
	  gcc_assert (may_need_excess_precision && common);
	  semantic_result_type = c_common_type (orig_type0, orig_type1);
	}
    }

  ಯದಿ (!converted)
    {
      op0 = ep_convert_and_check (location, result_type, op0,
				  semantic_result_type);
      op1 = ep_convert_and_check (location, result_type, op1,
				  semantic_result_type);

      /* This can happen if one operand has a vector type, and the other
	 has a different type.  */
      ಯದಿ (ವೃಕ್ಷ_CODE (op0) == ERROR_MARK || ವೃಕ್ಷ_CODE (op1) == ERROR_MARK)
	ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
    }

  ಯದಿ (sanitize_flags_p ((SANITIZE_SHIFT
			 | SANITIZE_DIVIDE
			 | SANITIZE_FLOAT_DIVIDE
			 | SANITIZE_SI_OVERFLOW))
      && current_function_decl != NULL_ವೃಕ್ಷ
      && (doing_div_or_mod || doing_shift)
      && !require_constant_ಮೌಲ್ಯ)
    {
      /* OP0 and/or OP1 might have side-effects.  */
      op0 = save_ಅಭಿವ್ಯಕ್ತಿ (op0);
      op1 = save_ಅಭಿವ್ಯಕ್ತಿ (op1);
      op0 = c_fully_fold (op0, ಅಸತ್ಯ, ರಿಕ್ತ);
      op1 = c_fully_fold (op1, ಅಸತ್ಯ, ರಿಕ್ತ);
      ಯದಿ (doing_div_or_mod && (sanitize_flags_p ((SANITIZE_DIVIDE
						  | SANITIZE_FLOAT_DIVIDE
						  | SANITIZE_SI_OVERFLOW))))
	instrument_ಅಭಿವ್ಯಕ್ತಿ = ubsan_instrument_division (location, op0, op1);
      ಅನ್ಯಥಾ ಯದಿ (doing_shift && sanitize_flags_p (SANITIZE_SHIFT))
	instrument_ಅಭಿವ್ಯಕ್ತಿ = ubsan_instrument_shift (location, code, op0, op1);
    }

  /* Treat expressions in initializers specially as they can't trap.  */
  ಯದಿ (int_const_or_overflow)
    ret = (require_constant_ಮೌಲ್ಯ
	   ? fold_build2_initializer_loc (location, resultcode, build_type,
					  op0, op1)
	   : fold_build2_loc (location, resultcode, build_type, op0, op1));
  ಅನ್ಯಥಾ
    ret = build2 (resultcode, build_type, op0, op1);
  ಯದಿ (final_type != NULL_ವೃಕ್ಷ)
    ret = convert (final_type, ret);

 return_build_ದ್ವಿಮಾನ_op:
  gcc_assert (ret != error_mark_ಗಂಟು);
  ಯದಿ (ವೃಕ್ಷ_CODE (ret) == INTEGER_CST && !ವೃಕ್ಷ_OVERFLOW (ret) && !int_const)
    ret = (int_operands
	   ? note_integer_operands (ret)
	   : build1 (NOP_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (ret), ret));
  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (ret) != INTEGER_CST && int_operands
	   && !in_late_ದ್ವಿಮಾನ_op)
    ret = note_integer_operands (ret);
  protected_set_ಅಭಿವ್ಯಕ್ತಿ_location (ret, location);

  ಯದಿ (instrument_ಅಭಿವ್ಯಕ್ತಿ != ರಿಕ್ತ)
    ret = fold_build2 (COMPOUND_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (ret),
		       instrument_ಅಭಿವ್ಯಕ್ತಿ, ret);

  ಯದಿ (semantic_result_type)
    ret = build1_loc (location, EXCESS_PRECISION_ಅಭಿವ್ಯಕ್ತಿ,
		      semantic_result_type, ret);

  ಪ್ರತ್ಯಾಗಮ ret;
}


/* Convert EXPR to be a truth-value (type TYPE), validating its type for this
   purpose.  LOCATION is the source location for the expression.  */

ವೃಕ್ಷ
c_objc_common_truthvalue_conversion (location_t location, ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ type)
{
  ತಾರ್ಕಿಕ int_const, int_operands;

  ವಿಕಲ್ಪ (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ)))
    {
    ಪಕ್ಷ ARRAY_TYPE:
      error_at (location, "used array that cannot be converted to pointer where scalar is required");
      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;

    ಪಕ್ಷ RECORD_TYPE:
      error_at (location, "used struct type value where scalar is required");
      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;

    ಪಕ್ಷ UNION_TYPE:
      error_at (location, "used union type value where scalar is required");
      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;

    ಪಕ್ಷ VOID_TYPE:
      error_at (location, "void value not ignored as it ought to be");
      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;

    ಪಕ್ಷ POINTER_TYPE:
      ಯದಿ (reject_gcc_builtin (ಅಭಿವ್ಯಕ್ತಿ))
	ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
      ಭಙ್ಗ;

    ಪಕ್ಷ FUNCTION_TYPE:
      gcc_unreachable ();

    ಪಕ್ಷ VECTOR_TYPE:
      error_at (location, "used vector type where scalar is required");
      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;

    ಸ್ವಭಾವ:
      ಭಙ್ಗ;
    }

  /* Conversion of a floating constant to boolean goes through here
     and yields an integer constant expression.  Otherwise, the result
     is only an integer constant expression if the argument is.  */
  int_const = ((ವೃಕ್ಷ_CODE (ಅಭಿವ್ಯಕ್ತಿ) == INTEGER_CST && !ವೃಕ್ಷ_OVERFLOW (ಅಭಿವ್ಯಕ್ತಿ))
	       || ((ವೃಕ್ಷ_CODE (ಅಭಿವ್ಯಕ್ತಿ) == REAL_CST
		    || ವೃಕ್ಷ_CODE (ಅಭಿವ್ಯಕ್ತಿ) == COMPLEX_CST)
		   && (ವೃಕ್ಷ_CODE (type) == BOOLEAN_TYPE
		       || (ವೃಕ್ಷ_CODE (type) == ENUMERAL_TYPE
			   && ENUM_UNDERLYING_TYPE (type) != NULL_ವೃಕ್ಷ
			   && (ವೃಕ್ಷ_CODE (ENUM_UNDERLYING_TYPE (type))
			       == BOOLEAN_TYPE)))));
  int_operands = ಅಭಿವ್ಯಕ್ತಿ_INT_CONST_OPERANDS (ಅಭಿವ್ಯಕ್ತಿ);
  ಯದಿ (int_operands && ವೃಕ್ಷ_CODE (ಅಭಿವ್ಯಕ್ತಿ) != INTEGER_CST)
    {
      ಅಭಿವ್ಯಕ್ತಿ = remove_c_maybe_const_ಅಭಿವ್ಯಕ್ತಿ (ಅಭಿವ್ಯಕ್ತಿ);
      ಅಭಿವ್ಯಕ್ತಿ = build2 (NE_ಅಭಿವ್ಯಕ್ತಿ, type, ಅಭಿವ್ಯಕ್ತಿ,
		     convert (ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ), integer_zero_ಗಂಟು));
      ಅಭಿವ್ಯಕ್ತಿ = note_integer_operands (ಅಭಿವ್ಯಕ್ತಿ);
    }
  ಅನ್ಯಥಾ
    {
      /* ??? Should we also give an error for vectors rather than leaving
	 those to give errors later?  */
      ಅಭಿವ್ಯಕ್ತಿ = c_common_truthvalue_conversion (location, ಅಭಿವ್ಯಕ್ತಿ);
      ಅಭಿವ್ಯಕ್ತಿ = fold_convert_loc (location, type, ಅಭಿವ್ಯಕ್ತಿ);
    }

  ಯದಿ (ವೃಕ್ಷ_CODE (ಅಭಿವ್ಯಕ್ತಿ) == INTEGER_CST && int_operands && !int_const)
    {
      ಯದಿ (ವೃಕ್ಷ_OVERFLOW (ಅಭಿವ್ಯಕ್ತಿ))
	ಪ್ರತ್ಯಾಗಮ ಅಭಿವ್ಯಕ್ತಿ;
      ಅನ್ಯಥಾ
	ಪ್ರತ್ಯಾಗಮ note_integer_operands (ಅಭಿವ್ಯಕ್ತಿ);
    }
  ಯದಿ (ವೃಕ್ಷ_CODE (ಅಭಿವ್ಯಕ್ತಿ) == INTEGER_CST && !int_const)
    ಪ್ರತ್ಯಾಗಮ build1 (NOP_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ), ಅಭಿವ್ಯಕ್ತಿ);
  ಪ್ರತ್ಯಾಗಮ ಅಭಿವ್ಯಕ್ತಿ;
}


/* Convert EXPR to a contained DECL, updating *TC, *TI and *SE as
   required.  */

ವೃಕ್ಷ
c_ಅಭಿವ್ಯಕ್ತಿ_to_decl (ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ, ತಾರ್ಕಿಕ *tc ATTRIBUTE_UNUSED, ತಾರ್ಕಿಕ *se)
{
  ಯದಿ (ವೃಕ್ಷ_CODE (ಅಭಿವ್ಯಕ್ತಿ) == COMPOUND_LITERAL_ಅಭಿವ್ಯಕ್ತಿ)
    {
      ವೃಕ್ಷ decl = COMPOUND_LITERAL_ಅಭಿವ್ಯಕ್ತಿ_DECL (ಅಭಿವ್ಯಕ್ತಿ);
      /* Executing a compound literal inside a function reinitializes
	 it.  */
      ಯದಿ (!ವೃಕ್ಷ_STATIC (decl))
	*se = ಸತ್ಯ;
      ಪ್ರತ್ಯಾಗಮ decl;
    }
  ಅನ್ಯಥಾ
    ಪ್ರತ್ಯಾಗಮ ಅಭಿವ್ಯಕ್ತಿ;
}

/* Generate OMP construct CODE, with BODY and CLAUSES as its compound
   statement.  LOC is the location of the construct.  */

ವೃಕ್ಷ
c_finish_omp_construct (location_t loc, ಗಣನಾ ವೃಕ್ಷ_code code, ವೃಕ್ಷ body,
			ವೃಕ್ಷ clauses)
{
  body = c_end_compound_stmt (loc, body, ಸತ್ಯ);

  ವೃಕ್ಷ stmt = make_ಗಂಟು (code);
  ವೃಕ್ಷ_TYPE (stmt) = void_type_ಗಂಟು;
  OMP_BODY (stmt) = body;
  OMP_CLAUSES (stmt) = clauses;
  SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (stmt, loc);

  ಪ್ರತ್ಯಾಗಮ add_stmt (stmt);
}

/* Generate OACC_DATA, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the OACC_DATA.  */

ವೃಕ್ಷ
c_finish_oacc_data (location_t loc, ವೃಕ್ಷ clauses, ವೃಕ್ಷ block)
{
  ವೃಕ್ಷ stmt;

  block = c_end_compound_stmt (loc, block, ಸತ್ಯ);

  stmt = make_ಗಂಟು (OACC_DATA);
  ವೃಕ್ಷ_TYPE (stmt) = void_type_ಗಂಟು;
  OACC_DATA_CLAUSES (stmt) = clauses;
  OACC_DATA_BODY (stmt) = block;
  SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (stmt, loc);

  ಪ್ರತ್ಯಾಗಮ add_stmt (stmt);
}

/* Generate OACC_HOST_DATA, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the OACC_HOST_DATA.  */

ವೃಕ್ಷ
c_finish_oacc_host_data (location_t loc, ವೃಕ್ಷ clauses, ವೃಕ್ಷ block)
{
  ವೃಕ್ಷ stmt;

  block = c_end_compound_stmt (loc, block, ಸತ್ಯ);

  stmt = make_ಗಂಟು (OACC_HOST_DATA);
  ವೃಕ್ಷ_TYPE (stmt) = void_type_ಗಂಟು;
  OACC_HOST_DATA_CLAUSES (stmt) = clauses;
  OACC_HOST_DATA_BODY (stmt) = block;
  SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (stmt, loc);

  ಪ್ರತ್ಯಾಗಮ add_stmt (stmt);
}

/* Like c_begin_compound_stmt, except force the retention of the BLOCK.  */

ವೃಕ್ಷ
c_begin_omp_parallel (ಶೂನ್ಯ)
{
  ವೃಕ್ಷ block;

  keep_next_level ();
  block = c_begin_compound_stmt (ಸತ್ಯ);

  ಪ್ರತ್ಯಾಗಮ block;
}

/* Generate OMP_PARALLEL, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the OMP_PARALLEL.  */

ವೃಕ್ಷ
c_finish_omp_parallel (location_t loc, ವೃಕ್ಷ clauses, ವೃಕ್ಷ block)
{
  ವೃಕ್ಷ stmt;

  block = c_end_compound_stmt (loc, block, ಸತ್ಯ);

  stmt = make_ಗಂಟು (OMP_PARALLEL);
  ವೃಕ್ಷ_TYPE (stmt) = void_type_ಗಂಟು;
  OMP_PARALLEL_CLAUSES (stmt) = clauses;
  OMP_PARALLEL_BODY (stmt) = block;
  SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (stmt, loc);

  ಪ್ರತ್ಯಾಗಮ add_stmt (stmt);
}

/* Like c_begin_compound_stmt, except force the retention of the BLOCK.  */

ವೃಕ್ಷ
c_begin_omp_task (ಶೂನ್ಯ)
{
  ವೃಕ್ಷ block;

  keep_next_level ();
  block = c_begin_compound_stmt (ಸತ್ಯ);

  ಪ್ರತ್ಯಾಗಮ block;
}

/* Generate OMP_TASK, with CLAUSES and BLOCK as its compound
   statement.  LOC is the location of the #pragma.  */

ವೃಕ್ಷ
c_finish_omp_task (location_t loc, ವೃಕ್ಷ clauses, ವೃಕ್ಷ block)
{
  ವೃಕ್ಷ stmt;

  block = c_end_compound_stmt (loc, block, ಸತ್ಯ);

  stmt = make_ಗಂಟು (OMP_TASK);
  ವೃಕ್ಷ_TYPE (stmt) = void_type_ಗಂಟು;
  OMP_TASK_CLAUSES (stmt) = clauses;
  OMP_TASK_BODY (stmt) = block;
  SET_ಅಭಿವ್ಯಕ್ತಿ_LOCATION (stmt, loc);

  ಪ್ರತ್ಯಾಗಮ add_stmt (stmt);
}

/* Generate GOMP_cancel call for #pragma omp cancel.  */

ಶೂನ್ಯ
c_finish_omp_cancel (location_t loc, ವೃಕ್ಷ clauses)
{
  ವೃಕ್ಷ fn = builtin_decl_explicit (BUILT_IN_GOMP_CANCEL);
  ಪೂರ್ಣಾಙ್ಕ mask = 0;
  ಯದಿ (omp_find_clause (clauses, OMP_CLAUSE_PARALLEL))
    mask = 1;
  ಅನ್ಯಥಾ ಯದಿ (omp_find_clause (clauses, OMP_CLAUSE_FOR))
    mask = 2;
  ಅನ್ಯಥಾ ಯದಿ (omp_find_clause (clauses, OMP_CLAUSE_SECTIONS))
    mask = 4;
  ಅನ್ಯಥಾ ಯದಿ (omp_find_clause (clauses, OMP_CLAUSE_TASKGROUP))
    mask = 8;
  ಅನ್ಯಥಾ
    {
      error_at (loc, "%<#pragma omp cancel%> must specify one of "
		     "%<parallel%>, %<for%>, %<sections%> or %<taskgroup%> "
		     "clauses");
      ಪ್ರತ್ಯಾಗಮ;
    }
  ವೃಕ್ಷ ifc = omp_find_clause (clauses, OMP_CLAUSE_IF);
  ಯದಿ (ifc != NULL_ವೃಕ್ಷ)
    {
      ಯದಿ (OMP_CLAUSE_IF_MODIFIER (ifc) != ERROR_MARK
	  && OMP_CLAUSE_IF_MODIFIER (ifc) != VOID_CST)
	error_at (OMP_CLAUSE_LOCATION (ifc),
		  "expected %<cancel%> %<if%> clause modifier");
      ಅನ್ಯಥಾ
	{
	  ವೃಕ್ಷ ifc2 = omp_find_clause (OMP_CLAUSE_CHAIN (ifc), OMP_CLAUSE_IF);
	  ಯದಿ (ifc2 != NULL_ವೃಕ್ಷ)
	    {
	      gcc_assert (OMP_CLAUSE_IF_MODIFIER (ifc) == VOID_CST
			  && OMP_CLAUSE_IF_MODIFIER (ifc2) != ERROR_MARK
			  && OMP_CLAUSE_IF_MODIFIER (ifc2) != VOID_CST);
	      error_at (OMP_CLAUSE_LOCATION (ifc2),
			"expected %<cancel%> %<if%> clause modifier");
	    }
	}

      ವೃಕ್ಷ type = ವೃಕ್ಷ_TYPE (OMP_CLAUSE_IF_ಅಭಿವ್ಯಕ್ತಿ (ifc));
      ifc = fold_build2_loc (OMP_CLAUSE_LOCATION (ifc), NE_ಅಭಿವ್ಯಕ್ತಿ,
			     boolean_type_ಗಂಟು, OMP_CLAUSE_IF_ಅಭಿವ್ಯಕ್ತಿ (ifc),
			     build_zero_cst (type));
    }
  ಅನ್ಯಥಾ
    ifc = boolean_true_ಗಂಟು;
  ವೃಕ್ಷ stmt = build_call_ಅಭಿವ್ಯಕ್ತಿ_loc (loc, fn, 2,
				   build_int_cst (integer_type_ಗಂಟು, mask),
				   ifc);
  add_stmt (stmt);
}

/* Generate GOMP_cancellation_point call for
   #pragma omp cancellation point.  */

ಶೂನ್ಯ
c_finish_omp_cancellation_point (location_t loc, ವೃಕ್ಷ clauses)
{
  ವೃಕ್ಷ fn = builtin_decl_explicit (BUILT_IN_GOMP_CANCELLATION_POINT);
  ಪೂರ್ಣಾಙ್ಕ mask = 0;
  ಯದಿ (omp_find_clause (clauses, OMP_CLAUSE_PARALLEL))
    mask = 1;
  ಅನ್ಯಥಾ ಯದಿ (omp_find_clause (clauses, OMP_CLAUSE_FOR))
    mask = 2;
  ಅನ್ಯಥಾ ಯದಿ (omp_find_clause (clauses, OMP_CLAUSE_SECTIONS))
    mask = 4;
  ಅನ್ಯಥಾ ಯದಿ (omp_find_clause (clauses, OMP_CLAUSE_TASKGROUP))
    mask = 8;
  ಅನ್ಯಥಾ
    {
      error_at (loc, "%<#pragma omp cancellation point%> must specify one of "
		     "%<parallel%>, %<for%>, %<sections%> or %<taskgroup%> "
		     "clauses");
      ಪ್ರತ್ಯಾಗಮ;
    }
  ವೃಕ್ಷ stmt = build_call_ಅಭಿವ್ಯಕ್ತಿ_loc (loc, fn, 1,
				   build_int_cst (integer_type_ಗಂಟು, mask));
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

ಸ್ಥಿರ ವೃಕ್ಷ
handle_omp_array_sections_1 (ವೃಕ್ಷ c, ವೃಕ್ಷ t, vec<ವೃಕ್ಷ> &types,
			     ತಾರ್ಕಿಕ &maybe_zero_len, unsigned ಪೂರ್ಣಾಙ್ಕ &first_non_one,
			     ಗಣನಾ c_omp_region_type ort)
{
  ವೃಕ್ಷ ret, ಕೆಳಗಿನ_bound, length, type;
  ತಾರ್ಕಿಕ openacc = (ort & C_ORT_ACC) != 0;
  ಯದಿ (ವೃಕ್ಷ_CODE (t) != OMP_ARRAY_SECTION)
    {
      ಯದಿ (error_operand_p (t))
	ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
      c_omp_address_inspector ai (OMP_CLAUSE_LOCATION (c), t);
      ret = t;
      ಯದಿ (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
	  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
	  && TYPE_ATOMIC (strip_array_types (ವೃಕ್ಷ_TYPE (t))))
	{
	  error_at (OMP_CLAUSE_LOCATION (c), "%<_Atomic%> %qE in %qs clause",
		    t, omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	}
      ಯದಿ (!ai.check_clause (c))
	ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
      ಅನ್ಯಥಾ ಯದಿ (ai.component_access_p ()
	       && (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TO
		   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_FROM))
	t = ai.get_ಬೇರು_term (ಸತ್ಯ);
      ಅನ್ಯಥಾ
	t = ai.unconverted_ref_origin ();
      ಯದಿ (t == error_mark_ಗಂಟು)
	ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
      ಯದಿ (!VAR_P (t)
	  && (ort == C_ORT_ACC || !ಅಭಿವ್ಯಕ್ತಿ_P (t))
	  && ವೃಕ್ಷ_CODE (t) != PARM_DECL)
	{
	  ಯದಿ (DECL_P (t))
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD is not a variable in %qs clause", t,
		      omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  ಅನ್ಯಥಾ
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qE is not a variable in %qs clause", t,
		      omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	}
      ಅನ್ಯಥಾ ಯದಿ (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
	       && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
	       && TYPE_ATOMIC (ವೃಕ್ಷ_TYPE (t)))
	{
	  error_at (OMP_CLAUSE_LOCATION (c), "%<_Atomic%> %qD in %qs clause",
		    t, omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	}
      ಅನ್ಯಥಾ ಯದಿ (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
	       && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
	       && VAR_P (t)
	       && DECL_THREAD_LOCAL_P (t))
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "%qD is threadprivate variable in %qs clause", t,
		    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	}
      ಯದಿ ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY
	   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND)
	  && TYPE_ATOMIC (ವೃಕ್ಷ_TYPE (t))
	  && POINTER_TYPE_P (ವೃಕ್ಷ_TYPE (t)))
	{
	  /* If the array section is pointer based and the pointer
	     itself is _Atomic qualified, we need to atomically load
	     the pointer.  */
	  ret = convert_lvalue_to_rvalue (OMP_CLAUSE_LOCATION (c),
					  ret, ಅಸತ್ಯ, ಅಸತ್ಯ);
	}
      ಪ್ರತ್ಯಾಗಮ ret;
    }

  ret = handle_omp_array_sections_1 (c, ವೃಕ್ಷ_OPERAND (t, 0), types,
				     maybe_zero_len, first_non_one, ort);
  ಯದಿ (ret == error_mark_ಗಂಟು || ret == NULL_ವೃಕ್ಷ)
    ಪ್ರತ್ಯಾಗಮ ret;

  type = ವೃಕ್ಷ_TYPE (ret);
  ಕೆಳಗಿನ_bound = ವೃಕ್ಷ_OPERAND (t, 1);
  length = ವೃಕ್ಷ_OPERAND (t, 2);

  ಯದಿ (ಕೆಳಗಿನ_bound == error_mark_ಗಂಟು || length == error_mark_ಗಂಟು)
    ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;

  ಯದಿ (ಕೆಳಗಿನ_bound && !INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (ಕೆಳಗಿನ_bound)))
    {
      error_at (OMP_CLAUSE_LOCATION (c),
		"low bound %qE of array section does not have integral type",
		ಕೆಳಗಿನ_bound);
      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
    }
  ಯದಿ (length && !INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (length)))
    {
      error_at (OMP_CLAUSE_LOCATION (c),
		"length %qE of array section does not have integral type",
		length);
      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
    }
  ಯದಿ (ಕೆಳಗಿನ_bound
      && ವೃಕ್ಷ_CODE (ಕೆಳಗಿನ_bound) == INTEGER_CST
      && TYPE_PRECISION (ವೃಕ್ಷ_TYPE (ಕೆಳಗಿನ_bound))
	 > TYPE_PRECISION (sizetype))
    ಕೆಳಗಿನ_bound = fold_convert (sizetype, ಕೆಳಗಿನ_bound);
  ಯದಿ (length
      && ವೃಕ್ಷ_CODE (length) == INTEGER_CST
      && TYPE_PRECISION (ವೃಕ್ಷ_TYPE (length))
	 > TYPE_PRECISION (sizetype))
    length = fold_convert (sizetype, length);
  ಯದಿ (ಕೆಳಗಿನ_bound == NULL_ವೃಕ್ಷ)
    ಕೆಳಗಿನ_bound = integer_zero_ಗಂಟು;
  ಯದಿ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
      && (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_ATTACH
	  || OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_DETACH))
    {
      ಯದಿ (length != integer_one_ಗಂಟು)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "expected single pointer in %qs clause",
		    user_omp_clause_code_name (c, openacc));
	  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	}
    }
  ಯದಿ (length != NULL_ವೃಕ್ಷ)
    {
      ಯದಿ (!integer_nonzerop (length))
	{
	  ಯದಿ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY
	      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
	      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
	      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
	      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TASK_REDUCTION)
	    {
	      ಯದಿ (integer_zerop (length))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "zero length array section in %qs clause",
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
		}
	    }
	  ಅನ್ಯಥಾ
	    maybe_zero_len = ಸತ್ಯ;
	}
      ಯದಿ (first_non_one == types.length ()
	  && (ವೃಕ್ಷ_CODE (length) != INTEGER_CST || integer_onep (length)))
	first_non_one++;
    }
  ಯದಿ (ವೃಕ್ಷ_CODE (type) == ARRAY_TYPE)
    {
      ಯದಿ (length == NULL_ವೃಕ್ಷ
	  && (TYPE_DOMAIN (type) == NULL_ವೃಕ್ಷ
	      || TYPE_MAX_ಮೌಲ್ಯ (TYPE_DOMAIN (type)) == NULL_ವೃಕ್ಷ))
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "for unknown bound array type length expression must "
		    "be specified");
	  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	}
      ಯದಿ (ವೃಕ್ಷ_CODE (ಕೆಳಗಿನ_bound) == INTEGER_CST
	  && ವೃಕ್ಷ_int_cst_sgn (ಕೆಳಗಿನ_bound) == -1)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "negative low bound in array section in %qs clause",
		    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	}
      ಯದಿ (length != NULL_ವೃಕ್ಷ
	  && ವೃಕ್ಷ_CODE (length) == INTEGER_CST
	  && ವೃಕ್ಷ_int_cst_sgn (length) == -1)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "negative length in array section in %qs clause",
		    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	}
      ಯದಿ (TYPE_DOMAIN (type)
	  && TYPE_MAX_ಮೌಲ್ಯ (TYPE_DOMAIN (type))
	  && ವೃಕ್ಷ_CODE (TYPE_MAX_ಮೌಲ್ಯ (TYPE_DOMAIN (type)))
			== INTEGER_CST)
	{
	  ವೃಕ್ಷ size
	    = fold_convert (sizetype, TYPE_MAX_ಮೌಲ್ಯ (TYPE_DOMAIN (type)));
	  size = size_binop (PLUS_ಅಭಿವ್ಯಕ್ತಿ, size, size_one_ಗಂಟು);
	  ಯದಿ (ವೃಕ್ಷ_CODE (ಕೆಳಗಿನ_bound) == INTEGER_CST)
	    {
	      ಯದಿ (ವೃಕ್ಷ_int_cst_lt (size, ಕೆಳಗಿನ_bound))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "low bound %qE above array section size "
			    "in %qs clause", ಕೆಳಗಿನ_bound,
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
		}
	      ಯದಿ (ವೃಕ್ಷ_int_cst_equal (size, ಕೆಳಗಿನ_bound))
		{
		  ಯದಿ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TASK_REDUCTION)
		    {
		      error_at (OMP_CLAUSE_LOCATION (c),
				"zero length array section in %qs clause",
				omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
		    }
		  maybe_zero_len = ಸತ್ಯ;
		}
	      ಅನ್ಯಥಾ ಯದಿ (length == NULL_ವೃಕ್ಷ
		       && first_non_one == types.length ()
		       && ವೃಕ್ಷ_int_cst_equal
			    (TYPE_MAX_ಮೌಲ್ಯ (TYPE_DOMAIN (type)),
			     ಕೆಳಗಿನ_bound))
		first_non_one++;
	    }
	  ಅನ್ಯಥಾ ಯದಿ (length == NULL_ವೃಕ್ಷ)
	    {
	      ಯದಿ (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
		  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
		  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_REDUCTION
		  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_IN_REDUCTION
		  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_TASK_REDUCTION)
		maybe_zero_len = ಸತ್ಯ;
	      ಯದಿ (first_non_one == types.length ())
		first_non_one++;
	    }
	  ಯದಿ (length && ವೃಕ್ಷ_CODE (length) == INTEGER_CST)
	    {
	      ಯದಿ (ವೃಕ್ಷ_int_cst_lt (size, length))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "length %qE above array section size "
			    "in %qs clause", length,
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
		}
	      ಯದಿ (ವೃಕ್ಷ_CODE (ಕೆಳಗಿನ_bound) == INTEGER_CST)
		{
		  ವೃಕ್ಷ lbpluslen
		    = size_binop (PLUS_ಅಭಿವ್ಯಕ್ತಿ,
				  fold_convert (sizetype, ಕೆಳಗಿನ_bound),
				  fold_convert (sizetype, length));
		  ಯದಿ (ವೃಕ್ಷ_CODE (lbpluslen) == INTEGER_CST
		      && ವೃಕ್ಷ_int_cst_lt (size, lbpluslen))
		    {
		      error_at (OMP_CLAUSE_LOCATION (c),
				"high bound %qE above array section size "
				"in %qs clause", lbpluslen,
				omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
		    }
		}
	    }
	}
      ಅನ್ಯಥಾ ಯದಿ (length == NULL_ವೃಕ್ಷ)
	{
	  ಯದಿ (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
	      && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
	      && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_REDUCTION
	      && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_IN_REDUCTION
	      && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_TASK_REDUCTION)
	    maybe_zero_len = ಸತ್ಯ;
	  ಯದಿ (first_non_one == types.length ())
	    first_non_one++;
	}

      /* For [lb:] we will need to evaluate lb more than once.  */
      ಯದಿ (length == NULL_ವೃಕ್ಷ && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND)
	{
	  ವೃಕ್ಷ lb = save_ಅಭಿವ್ಯಕ್ತಿ (ಕೆಳಗಿನ_bound);
	  ಯದಿ (lb != ಕೆಳಗಿನ_bound)
	    {
	      ವೃಕ್ಷ_OPERAND (t, 1) = lb;
	      ಕೆಳಗಿನ_bound = lb;
	    }
	}
    }
  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (type) == POINTER_TYPE)
    {
      ಯದಿ (length == NULL_ವೃಕ್ಷ)
	{
	  ಯದಿ (ವೃಕ್ಷ_CODE (ret) == PARM_DECL && C_ARRAY_PARAMETER (ret))
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "for array function parameter length expression "
		      "must be specified");
	  ಅನ್ಯಥಾ
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "for pointer type length expression must be specified");
	  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	}
      ಯದಿ (length != NULL_ವೃಕ್ಷ
	  && ವೃಕ್ಷ_CODE (length) == INTEGER_CST
	  && ವೃಕ್ಷ_int_cst_sgn (length) == -1)
	{
	  error_at (OMP_CLAUSE_LOCATION (c),
		    "negative length in array section in %qs clause",
		    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
	}
      /* If there is a pointer type anywhere but in the very first
	 array-section-subscript, the array section could be non-contiguous.  */
      ಯದಿ (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND
	  && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_AFFINITY
	  && ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_OPERAND (t, 0)) == OMP_ARRAY_SECTION)
	{
	  /* If any prior dimension has a non-one length, then deem this
	     array section as non-contiguous.  */
	  ಪ್ರತಿ (ವೃಕ್ಷ d = ವೃಕ್ಷ_OPERAND (t, 0);
	       ವೃಕ್ಷ_CODE (d) == OMP_ARRAY_SECTION;
	       d = ವೃಕ್ಷ_OPERAND (d, 0))
	    {
	      ವೃಕ್ಷ d_length = ವೃಕ್ಷ_OPERAND (d, 2);
	      ಯದಿ (d_length == NULL_ವೃಕ್ಷ || !integer_onep (d_length))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "array section is not contiguous in %qs clause",
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
		}
	    }
	}
    }
  ಅನ್ಯಥಾ
    {
      error_at (OMP_CLAUSE_LOCATION (c),
		"%qE does not have pointer or array type", ret);
      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
    }
  ಯದಿ (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_DEPEND)
    types.safe_ತಳ್ಳು (ವೃಕ್ಷ_TYPE (ret));
  /* We will need to evaluate lb more than once.  */
  ವೃಕ್ಷ lb = save_ಅಭಿವ್ಯಕ್ತಿ (ಕೆಳಗಿನ_bound);
  ಯದಿ (lb != ಕೆಳಗಿನ_bound)
    {
      ವೃಕ್ಷ_OPERAND (t, 1) = lb;
      ಕೆಳಗಿನ_bound = lb;
    }
  ret = build_array_ref (OMP_CLAUSE_LOCATION (c), ret, ಕೆಳಗಿನ_bound);
  ಪ್ರತ್ಯಾಗಮ ret;
}

/* Handle array sections for clause C.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
handle_omp_array_sections (ವೃಕ್ಷ &c, ಗಣನಾ c_omp_region_type ort)
{
  ತಾರ್ಕಿಕ maybe_zero_len = ಅಸತ್ಯ;
  unsigned ಪೂರ್ಣಾಙ್ಕ first_non_one = 0;
  auto_vec<ವೃಕ್ಷ, 10> types;
  ವೃಕ್ಷ *tp = &OMP_CLAUSE_DECL (c);
  ಯದಿ ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
       || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY)
      && OMP_ITERATOR_DECL_P (*tp))
    tp = &ವೃಕ್ಷ_ಮೌಲ್ಯ (*tp);
  ವೃಕ್ಷ first = handle_omp_array_sections_1 (c, *tp, types,
					    maybe_zero_len, first_non_one,
					    ort);
  ಯದಿ (first == error_mark_ಗಂಟು)
    ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
  ಯದಿ (first == NULL_ವೃಕ್ಷ)
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
  ಯದಿ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY)
    {
      ವೃಕ್ಷ t = *tp;
      ವೃಕ್ಷ tem = NULL_ವೃಕ್ಷ;
      /* Need to evaluate side effects in the length expressions
	 if any.  */
      ಯಾವತ್ (ವೃಕ್ಷ_CODE (t) == ವೃಕ್ಷ_LIST)
	{
	  ಯದಿ (ವೃಕ್ಷ_ಮೌಲ್ಯ (t) && ವೃಕ್ಷ_SIDE_EFFECTS (ವೃಕ್ಷ_ಮೌಲ್ಯ (t)))
	    {
	      ಯದಿ (tem == NULL_ವೃಕ್ಷ)
		tem = ವೃಕ್ಷ_ಮೌಲ್ಯ (t);
	      ಅನ್ಯಥಾ
		tem = build2 (COMPOUND_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (tem),
			      ವೃಕ್ಷ_ಮೌಲ್ಯ (t), tem);
	    }
	  t = ವೃಕ್ಷ_CHAIN (t);
	}
      ಯದಿ (tem)
	first = build2 (COMPOUND_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (first), tem, first);
      first = c_fully_fold (first, ಅಸತ್ಯ, ರಿಕ್ತ, ಸತ್ಯ);
      *tp = first;
    }
  ಅನ್ಯಥಾ
    {
      unsigned ಪೂರ್ಣಾಙ್ಕ ಅಂಕೆ = types.length (), i;
      ವೃಕ್ಷ t, side_effects = NULL_ವೃಕ್ಷ, size = NULL_ವೃಕ್ಷ;
      ವೃಕ್ಷ condition = NULL_ವೃಕ್ಷ;

      ಯದಿ (int_size_in_bytes (ವೃಕ್ಷ_TYPE (first)) <= 0)
	maybe_zero_len = ಸತ್ಯ;

      ಪ್ರತಿ (i = ಅಂಕೆ, t = OMP_CLAUSE_DECL (c); i > 0;
	   t = ವೃಕ್ಷ_OPERAND (t, 0))
	{
	  ವೃಕ್ಷ ಕೆಳಗಿನ_bound = ವೃಕ್ಷ_OPERAND (t, 1);
	  ವೃಕ್ಷ length = ವೃಕ್ಷ_OPERAND (t, 2);

	  i--;
	  ಯದಿ (ಕೆಳಗಿನ_bound
	      && ವೃಕ್ಷ_CODE (ಕೆಳಗಿನ_bound) == INTEGER_CST
	      && TYPE_PRECISION (ವೃಕ್ಷ_TYPE (ಕೆಳಗಿನ_bound))
		 > TYPE_PRECISION (sizetype))
	    ಕೆಳಗಿನ_bound = fold_convert (sizetype, ಕೆಳಗಿನ_bound);
	  ಯದಿ (length
	      && ವೃಕ್ಷ_CODE (length) == INTEGER_CST
	      && TYPE_PRECISION (ವೃಕ್ಷ_TYPE (length))
		 > TYPE_PRECISION (sizetype))
	    length = fold_convert (sizetype, length);
	  ಯದಿ (ಕೆಳಗಿನ_bound == NULL_ವೃಕ್ಷ)
	    ಕೆಳಗಿನ_bound = integer_zero_ಗಂಟು;
	  ಯದಿ (!maybe_zero_len && i > first_non_one)
	    {
	      ಯದಿ (integer_nonzerop (ಕೆಳಗಿನ_bound))
		ಗಚ್ಛ do_warn_noncontiguous;
	      ಯದಿ (length != NULL_ವೃಕ್ಷ
		  && ವೃಕ್ಷ_CODE (length) == INTEGER_CST
		  && TYPE_DOMAIN (types[i])
		  && TYPE_MAX_ಮೌಲ್ಯ (TYPE_DOMAIN (types[i]))
		  && ವೃಕ್ಷ_CODE (TYPE_MAX_ಮೌಲ್ಯ (TYPE_DOMAIN (types[i])))
		     == INTEGER_CST)
		{
		  ವೃಕ್ಷ size;
		  size = size_binop (PLUS_ಅಭಿವ್ಯಕ್ತಿ,
				     TYPE_MAX_ಮೌಲ್ಯ (TYPE_DOMAIN (types[i])),
				     size_one_ಗಂಟು);
		  ಯದಿ (!ವೃಕ್ಷ_int_cst_equal (length, size))
		    {
		     do_warn_noncontiguous:
		      error_at (OMP_CLAUSE_LOCATION (c),
				"array section is not contiguous in %qs "
				"clause",
				omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		      ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
		    }
		}
	      ಯದಿ (length != NULL_ವೃಕ್ಷ
		  && ವೃಕ್ಷ_SIDE_EFFECTS (length))
		{
		  ಯದಿ (side_effects == NULL_ವೃಕ್ಷ)
		    side_effects = length;
		  ಅನ್ಯಥಾ
		    side_effects = build2 (COMPOUND_ಅಭಿವ್ಯಕ್ತಿ,
					   ವೃಕ್ಷ_TYPE (side_effects),
					   length, side_effects);
		}
	    }
	  ಅನ್ಯಥಾ
	    {
	      ವೃಕ್ಷ l;

	      ಯದಿ (i > first_non_one
		  && ((length && integer_nonzerop (length))
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TASK_REDUCTION))
		ಅನುವರ್ತ;
	      ಯದಿ (length)
		l = fold_convert (sizetype, length);
	      ಅನ್ಯಥಾ
		{
		  l = size_binop (PLUS_ಅಭಿವ್ಯಕ್ತಿ,
				  TYPE_MAX_ಮೌಲ್ಯ (TYPE_DOMAIN (types[i])),
				  size_one_ಗಂಟು);
		  l = size_binop (MINUS_ಅಭಿವ್ಯಕ್ತಿ, l,
				  fold_convert (sizetype, ಕೆಳಗಿನ_bound));
		}
	      ಯದಿ (i > first_non_one)
		{
		  l = fold_build2 (NE_ಅಭಿವ್ಯಕ್ತಿ, boolean_type_ಗಂಟು, l,
				   size_zero_ಗಂಟು);
		  ಯದಿ (condition == NULL_ವೃಕ್ಷ)
		    condition = l;
		  ಅನ್ಯಥಾ
		    condition = fold_build2 (BIT_AND_ಅಭಿವ್ಯಕ್ತಿ, boolean_type_ಗಂಟು,
					     l, condition);
		}
	      ಅನ್ಯಥಾ ಯದಿ (size == NULL_ವೃಕ್ಷ)
		{
		  size = size_in_bytes (ವೃಕ್ಷ_TYPE (types[i]));
		  ವೃಕ್ಷ eltype = ವೃಕ್ಷ_TYPE (types[ಅಂಕೆ - 1]);
		  ಯಾವತ್ (ವೃಕ್ಷ_CODE (eltype) == ARRAY_TYPE)
		    eltype = ವೃಕ್ಷ_TYPE (eltype);
		  ಯದಿ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
		      || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TASK_REDUCTION)
		    {
		      ಯದಿ (integer_zerop (size)
			  || integer_zerop (size_in_bytes (eltype)))
			{
			  error_at (OMP_CLAUSE_LOCATION (c),
				    "zero length array section in %qs clause",
				    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
			  ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
			}
		      size = size_binop (EXACT_DIV_ಅಭಿವ್ಯಕ್ತಿ, size,
					 size_in_bytes (eltype));
		    }
		  size = size_binop (MULT_ಅಭಿವ್ಯಕ್ತಿ, size, l);
		  ಯದಿ (condition)
		    size = fold_build3 (COND_ಅಭಿವ್ಯಕ್ತಿ, sizetype, condition,
					size, size_zero_ಗಂಟು);
		}
	      ಅನ್ಯಥಾ
		size = size_binop (MULT_ಅಭಿವ್ಯಕ್ತಿ, size, l);
	    }
	}
      ಯದಿ (side_effects)
	size = build2 (COMPOUND_ಅಭಿವ್ಯಕ್ತಿ, sizetype, side_effects, size);
      ಯದಿ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
	  || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
	  || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_TASK_REDUCTION)
	{
	  size = size_binop (MINUS_ಅಭಿವ್ಯಕ್ತಿ, size, size_one_ಗಂಟು);
	  size = c_fully_fold (size, ಅಸತ್ಯ, ರಿಕ್ತ);
	  size = save_ಅಭಿವ್ಯಕ್ತಿ (size);
	  ವೃಕ್ಷ index_type = build_index_type (size);
	  ವೃಕ್ಷ eltype = ವೃಕ್ಷ_TYPE (first);
	  ಯಾವತ್ (ವೃಕ್ಷ_CODE (eltype) == ARRAY_TYPE)
	    eltype = ವೃಕ್ಷ_TYPE (eltype);
	  ವೃಕ್ಷ type = c_build_array_type (eltype, index_type);
	  ವೃಕ್ಷ ptype = c_build_pointer_type (eltype);
	  ಯದಿ (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (t)) == ARRAY_TYPE)
	    t = build_fold_addr_ಅಭಿವ್ಯಕ್ತಿ (t);
	  ವೃಕ್ಷ t2 = build_fold_addr_ಅಭಿವ್ಯಕ್ತಿ (first);
	  t2 = fold_convert_loc (OMP_CLAUSE_LOCATION (c),
				 ptrdiff_type_ಗಂಟು, t2);
	  t2 = fold_build2_loc (OMP_CLAUSE_LOCATION (c), MINUS_ಅಭಿವ್ಯಕ್ತಿ,
				ptrdiff_type_ಗಂಟು, t2,
				fold_convert_loc (OMP_CLAUSE_LOCATION (c),
						  ptrdiff_type_ಗಂಟು, t));
	  t2 = c_fully_fold (t2, ಅಸತ್ಯ, ರಿಕ್ತ);
	  ಯದಿ (ವೃಕ್ಷ_fits_shwi_p (t2))
	    t = build2 (MEM_REF, type, t,
			build_int_cst (ptype, ವೃಕ್ಷ_to_shwi (t2)));
	  ಅನ್ಯಥಾ
	    {
	      t2 = fold_convert_loc (OMP_CLAUSE_LOCATION (c), sizetype, t2);
	      t = build2_loc (OMP_CLAUSE_LOCATION (c), POINTER_PLUS_ಅಭಿವ್ಯಕ್ತಿ,
			      ವೃಕ್ಷ_TYPE (t), t, t2);
	      t = build2 (MEM_REF, type, t, build_int_cst (ptype, 0));
	    }
	  OMP_CLAUSE_DECL (c) = t;
	  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	}
      first = c_fully_fold (first, ಅಸತ್ಯ, ರಿಕ್ತ);
      OMP_CLAUSE_DECL (c) = first;
      ಯದಿ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_HAS_DEVICE_ADDR)
	ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
      /* Don't set OMP_CLAUSE_SIZE for bare attach/detach clauses.  */
      ಯದಿ (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP
	  || (OMP_CLAUSE_MAP_KIND (c) != GOMP_MAP_ATTACH
	      && OMP_CLAUSE_MAP_KIND (c) != GOMP_MAP_DETACH
	      && OMP_CLAUSE_MAP_KIND (c) != GOMP_MAP_FORCE_DETACH))
	{
	  ಯದಿ (size)
	    size = c_fully_fold (size, ಅಸತ್ಯ, ರಿಕ್ತ);
	  OMP_CLAUSE_SIZE (c) = size;
	}

      ಯದಿ (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP)
	ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

      auto_vec<omp_addr_token *, 10> addr_tokens;

      ಯದಿ (!omp_parse_ಅಭಿವ್ಯಕ್ತಿ (addr_tokens, first))
	ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;

      c_omp_address_inspector ai (OMP_CLAUSE_LOCATION (c), t);

      ವೃಕ್ಷ nc = ai.expand_map_clause (c, first, addr_tokens, ort);
      ಯದಿ (nc != error_mark_ಗಂಟು)
	{
	  using ನಾಮಾಕಾಶ omp_addr_tokenizer;

	  ಯದಿ (ai.maybe_zero_length_array_section (c))
	    OMP_CLAUSE_MAP_MAYBE_ZERO_LENGTH_ARRAY_SECTION (c) = 1;

	  /* !!! If we're accessing a base decl via chained access
	     methods (e.g. multiple indirections), duplicate clause
	     detection won't work properly.  Skip it in that case.  */
	  ಯದಿ ((addr_tokens[0]->type == STRUCTURE_BASE
	       || addr_tokens[0]->type == ARRAY_BASE)
	      && addr_tokens[0]->u.structure_base_kind == BASE_DECL
	      && addr_tokens[1]->type == ACCESS_METHOD
	      && omp_access_chain_p (addr_tokens, 1))
	    c = nc;

	  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	}
    }
  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
}

/* Helper function of finish_omp_clauses.  Clone STMT as if we were making
   an inline call.  But, remap
   the OMP_DECL1 VAR_DECL (omp_out resp. omp_orig) to PLACEHOLDER
   and OMP_DECL2 VAR_DECL (omp_in resp. omp_priv) to DECL.  */

ಸ್ಥಿರ ವೃಕ್ಷ
c_clone_omp_udr (ವೃಕ್ಷ stmt, ವೃಕ್ಷ omp_decl1, ವೃಕ್ಷ omp_decl2,
		 ವೃಕ್ಷ decl, ವೃಕ್ಷ placeholder)
{
  copy_body_data id;
  hash_map<ವೃಕ್ಷ, ವೃಕ್ಷ> decl_map;

  decl_map.put (omp_decl1, placeholder);
  decl_map.put (omp_decl2, decl);
  memset (&id, 0, ಪರಿಮಾಣ (id));
  id.src_fn = DECL_CONTEXT (omp_decl1);
  id.dst_fn = current_function_decl;
  id.src_cfun = DECL_STRUCT_FUNCTION (id.src_fn);
  id.decl_map = &decl_map;

  id.copy_decl = copy_decl_no_change;
  id.transform_call_graph_edges = CB_CGE_DUPLICATE;
  id.transform_new_cfg = ಸತ್ಯ;
  id.transform_return_to_modify = ಅಸತ್ಯ;
  id.eh_lp_nr = 0;
  walk_ವೃಕ್ಷ (&stmt, copy_ವೃಕ್ಷ_body_r, &id, ರಿಕ್ತ);
  ಪ್ರತ್ಯಾಗಮ stmt;
}

/* Helper function of c_finish_omp_clauses, called via walk_tree.
   Find OMP_CLAUSE_PLACEHOLDER (passed in DATA) in *TP.  */

ಸ್ಥಿರ ವೃಕ್ಷ
c_find_omp_placeholder_r (ವೃಕ್ಷ *tp, ಪೂರ್ಣಾಙ್ಕ *, ಶೂನ್ಯ *data)
{
  ಯದಿ (*tp == (ವೃಕ್ಷ) data)
    ಪ್ರತ್ಯಾಗಮ *tp;
  ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
}

/* Similarly, but also walk aggregate fields.  */

ಸಂರಚನಾ c_find_omp_var_s { ವೃಕ್ಷ var; hash_set<ವೃಕ್ಷ> *pset; };

ಸ್ಥಿರ ವೃಕ್ಷ
c_find_omp_var_r (ವೃಕ್ಷ *tp, ಪೂರ್ಣಾಙ್ಕ *, ಶೂನ್ಯ *data)
{
  ಯದಿ (*tp == ((ಸಂರಚನಾ c_find_omp_var_s *) data)->var)
    ಪ್ರತ್ಯಾಗಮ *tp;
  ಯದಿ (RECORD_OR_UNION_TYPE_P (*tp))
    {
      ವೃಕ್ಷ field;
      hash_set<ವೃಕ್ಷ> *pset = ((ಸಂರಚನಾ c_find_omp_var_s *) data)->pset;

      ಪ್ರತಿ (field = TYPE_FIELDS (*tp); field;
	   field = DECL_CHAIN (field))
	ಯದಿ (ವೃಕ್ಷ_CODE (field) == FIELD_DECL)
	  {
	    ವೃಕ್ಷ ret = walk_ವೃಕ್ಷ (&DECL_FIELD_OFFSET (field),
				  c_find_omp_var_r, data, pset);
	    ಯದಿ (ret)
	      ಪ್ರತ್ಯಾಗಮ ret;
	    ret = walk_ವೃಕ್ಷ (&DECL_SIZE (field), c_find_omp_var_r, data, pset);
	    ಯದಿ (ret)
	      ಪ್ರತ್ಯಾಗಮ ret;
	    ret = walk_ವೃಕ್ಷ (&DECL_SIZE_UNIT (field), c_find_omp_var_r, data,
			     pset);
	    ಯದಿ (ret)
	      ಪ್ರತ್ಯಾಗಮ ret;
	    ret = walk_ವೃಕ್ಷ (&ವೃಕ್ಷ_TYPE (field), c_find_omp_var_r, data, pset);
	    ಯದಿ (ret)
	      ಪ್ರತ್ಯಾಗಮ ret;
	  }
    }
  ಅನ್ಯಥಾ ಯದಿ (INTEGRAL_TYPE_P (*tp))
    ಪ್ರತ್ಯಾಗಮ walk_ವೃಕ್ಷ (&TYPE_MAX_ಮೌಲ್ಯ (*tp), c_find_omp_var_r, data,
		      ((ಸಂರಚನಾ c_find_omp_var_s *) data)->pset);
  ಪ್ರತ್ಯಾಗಮ NULL_ವೃಕ್ಷ;
}

/* Finish OpenMP iterators ITER.  Return true if they are erroneous
   and clauses containing them should be removed.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
c_omp_finish_iterators (ವೃಕ್ಷ iter)
{
  ತಾರ್ಕಿಕ ret = ಅಸತ್ಯ;
  ಪ್ರತಿ (ವೃಕ್ಷ it = iter; it; it = ವೃಕ್ಷ_CHAIN (it))
    {
      ವೃಕ್ಷ var = OMP_ITERATOR_VAR (it);
      ವೃಕ್ಷ begin = OMP_ITERATOR_BEGIN (it);
      ವೃಕ್ಷ end = OMP_ITERATOR_END (it);
      ವೃಕ್ಷ step = OMP_ITERATOR_STEP (it);
      ವೃಕ್ಷ orig_step;
      ವೃಕ್ಷ type = ವೃಕ್ಷ_TYPE (var);
      location_t loc = DECL_SOURCE_LOCATION (var);
      ಯದಿ (type == error_mark_ಗಂಟು)
	{
	  ret = ಸತ್ಯ;
	  ಅನುವರ್ತ;
	}
      ಯದಿ (!INTEGRAL_TYPE_P (type) && !POINTER_TYPE_P (type))
	{
	  error_at (loc, "iterator %qD has neither integral nor pointer type",
		    var);
	  ret = ಸತ್ಯ;
	  ಅನುವರ್ತ;
	}
      ಅನ್ಯಥಾ ಯದಿ (TYPE_ATOMIC (type))
	{
	  error_at (loc, "iterator %qD has %<_Atomic%> qualified type", var);
	  ret = ಸತ್ಯ;
	  ಅನುವರ್ತ;
	}
      ಅನ್ಯಥಾ ಯದಿ (TYPE_READONLY (type))
	{
	  error_at (loc, "iterator %qD has const qualified type", var);
	  ret = ಸತ್ಯ;
	  ಅನುವರ್ತ;
	}
      ಅನ್ಯಥಾ ಯದಿ (step == error_mark_ಗಂಟು
	       || ವೃಕ್ಷ_TYPE (step) == error_mark_ಗಂಟು)
	{
	  ret = ಸತ್ಯ;
	  ಅನುವರ್ತ;
	}
      ಅನ್ಯಥಾ ಯದಿ (!INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (step)))
	{
	  error_at (ಅಭಿವ್ಯಕ್ತಿ_LOC_OR_LOC (step, loc),
		    "iterator step with non-integral type");
	  ret = ಸತ್ಯ;
	  ಅನುವರ್ತ;
	}
      begin = c_fully_fold (build_c_cast (loc, type, begin), ಅಸತ್ಯ, ರಿಕ್ತ);
      end = c_fully_fold (build_c_cast (loc, type, end), ಅಸತ್ಯ, ರಿಕ್ತ);
      orig_step = save_ಅಭಿವ್ಯಕ್ತಿ (c_fully_fold (step, ಅಸತ್ಯ, ರಿಕ್ತ));
      ವೃಕ್ಷ stype = POINTER_TYPE_P (type) ? sizetype : type;
      step = c_fully_fold (build_c_cast (loc, stype, orig_step), ಅಸತ್ಯ, ರಿಕ್ತ);
      ಯದಿ (POINTER_TYPE_P (type))
	{
	  begin = save_ಅಭಿವ್ಯಕ್ತಿ (begin);
	  step = pointer_int_sum (loc, PLUS_ಅಭಿವ್ಯಕ್ತಿ, begin, step);
	  step = fold_build2_loc (loc, MINUS_ಅಭಿವ್ಯಕ್ತಿ, sizetype,
				  fold_convert (sizetype, step),
				  fold_convert (sizetype, begin));
	  step = fold_convert (ssizetype, step);
	}
      ಯದಿ (integer_zerop (step))
	{
	  error_at (loc, "iterator %qD has zero step", var);
	  ret = ಸತ್ಯ;
	  ಅನುವರ್ತ;
	}

      ಯದಿ (begin == error_mark_ಗಂಟು
	  || end == error_mark_ಗಂಟು
	  || step == error_mark_ಗಂಟು
	  || orig_step == error_mark_ಗಂಟು)
	{
	  ret = ಸತ್ಯ;
	  ಅನುವರ್ತ;
	}
      hash_set<ವೃಕ್ಷ> pset;
      ವೃಕ್ಷ it2;
      ಪ್ರತಿ (it2 = ವೃಕ್ಷ_CHAIN (it); it2; it2 = ವೃಕ್ಷ_CHAIN (it2))
	{
	  ವೃಕ್ಷ var2 = OMP_ITERATOR_VAR (it2);
	  ವೃಕ್ಷ begin2 = OMP_ITERATOR_BEGIN (it2);
	  ವೃಕ್ಷ end2 = OMP_ITERATOR_END (it2);
	  ವೃಕ್ಷ step2 = OMP_ITERATOR_STEP (it2);
	  ವೃಕ್ಷ type2 = ವೃಕ್ಷ_TYPE (var2);
	  location_t loc2 = DECL_SOURCE_LOCATION (var2);
	  ಸಂರಚನಾ c_find_omp_var_s data = { var, &pset };
	  ಯದಿ (walk_ವೃಕ್ಷ (&type2, c_find_omp_var_r, &data, &pset))
	    {
	      error_at (loc2,
			"type of iterator %qD refers to outer iterator %qD",
			var2, var);
	      ಭಙ್ಗ;
	    }
	  ಅನ್ಯಥಾ ಯದಿ (walk_ವೃಕ್ಷ (&begin2, c_find_omp_var_r, &data, &pset))
	    {
	      error_at (ಅಭಿವ್ಯಕ್ತಿ_LOC_OR_LOC (begin2, loc2),
			"begin expression refers to outer iterator %qD", var);
	      ಭಙ್ಗ;
	    }
	  ಅನ್ಯಥಾ ಯದಿ (walk_ವೃಕ್ಷ (&end2, c_find_omp_var_r, &data, &pset))
	    {
	      error_at (ಅಭಿವ್ಯಕ್ತಿ_LOC_OR_LOC (end2, loc2),
			"end expression refers to outer iterator %qD", var);
	      ಭಙ್ಗ;
	    }
	  ಅನ್ಯಥಾ ಯದಿ (walk_ವೃಕ್ಷ (&step2, c_find_omp_var_r, &data, &pset))
	    {
	      error_at (ಅಭಿವ್ಯಕ್ತಿ_LOC_OR_LOC (step2, loc2),
			"step expression refers to outer iterator %qD", var);
	      ಭಙ್ಗ;
	    }
	}
      ಯದಿ (it2)
	{
	  ret = ಸತ್ಯ;
	  ಅನುವರ್ತ;
	}
      OMP_ITERATOR_BEGIN (it) = begin;
      OMP_ITERATOR_END (it) = end;
      OMP_ITERATOR_STEP (it) = step;
      OMP_ITERATOR_ORIG_STEP (it) = orig_step;
    }
  ಪ್ರತ್ಯಾಗಮ ret;
}

/* Ensure that pointers are used in OpenACC attach and detach clauses.
   Return true if an error has been detected.  */

ಸ್ಥಿರ ತಾರ್ಕಿಕ
c_oacc_check_attachments (ವೃಕ್ಷ c)
{
  ಯದಿ (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP)
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

  /* OpenACC attach / detach clauses must be pointers.  */
  ಯದಿ (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_ATTACH
      || OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_DETACH)
    {
      ವೃಕ್ಷ t = OMP_CLAUSE_DECL (c);

      ಯಾವತ್ (ವೃಕ್ಷ_CODE (t) == OMP_ARRAY_SECTION)
	t = ವೃಕ್ಷ_OPERAND (t, 0);

      ಯದಿ (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (t)) != POINTER_TYPE)
	{
	  error_at (OMP_CLAUSE_LOCATION (c), "expected pointer in %qs clause",
		    user_omp_clause_code_name (c, ಸತ್ಯ));
	  ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
	}
    }

  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
}

/* For all elements of CLAUSES, validate them against their constraints.
   Remove any elements from the list that are invalid.  */

ವೃಕ್ಷ
c_finish_omp_clauses (ವೃಕ್ಷ clauses, ಗಣನಾ c_omp_region_type ort)
{
  bitmap_head generic_head, firstprivate_head, lastprivate_head;
  bitmap_head aligned_head, map_head, map_field_head, map_firstprivate_head;
  bitmap_head oacc_reduction_head, is_on_device_head;
  ವೃಕ್ಷ c, t, type, *pc;
  ವೃಕ್ಷ simdlen = NULL_ವೃಕ್ಷ, safelen = NULL_ವೃಕ್ಷ;
  ತಾರ್ಕಿಕ branch_seen = ಅಸತ್ಯ;
  ತಾರ್ಕಿಕ copyprivate_seen = ಅಸತ್ಯ;
  ತಾರ್ಕಿಕ mergeable_seen = ಅಸತ್ಯ;
  ವೃಕ್ಷ *detach_seen = ರಿಕ್ತ;
  ತಾರ್ಕಿಕ linear_variable_step_check = ಅಸತ್ಯ;
  ವೃಕ್ಷ *nowait_clause = ರಿಕ್ತ;
  ವೃಕ್ಷ *grainsize_seen = ರಿಕ್ತ;
  ತಾರ್ಕಿಕ ಅಂಕೆ_tasks_seen = ಅಸತ್ಯ;
  ವೃಕ್ಷ ordered_clause = NULL_ವೃಕ್ಷ;
  ವೃಕ್ಷ schedule_clause = NULL_ವೃಕ್ಷ;
  ತಾರ್ಕಿಕ oacc_async = ಅಸತ್ಯ;
  ವೃಕ್ಷ last_iterators = NULL_ವೃಕ್ಷ;
  ತಾರ್ಕಿಕ last_iterators_remove = ಅಸತ್ಯ;
  ವೃಕ್ಷ *nogroup_seen = ರಿಕ್ತ;
  ವೃಕ್ಷ *order_clause = ರಿಕ್ತ;
  /* 1 if normal/task reduction has been seen, -1 if inscan reduction
     has been seen, -2 if mixed inscan/normal reduction diagnosed.  */
  ಪೂರ್ಣಾಙ್ಕ reduction_seen = 0;
  ತಾರ್ಕಿಕ allocate_seen = ಅಸತ್ಯ;
  ತಾರ್ಕಿಕ implicit_moved = ಅಸತ್ಯ;
  ತಾರ್ಕಿಕ target_in_reduction_seen = ಅಸತ್ಯ;
  ವೃಕ್ಷ *full_seen = ರಿಕ್ತ;
  ತಾರ್ಕಿಕ partial_seen = ಅಸತ್ಯ;
  ತಾರ್ಕಿಕ openacc = (ort & C_ORT_ACC) != 0;
  ತಾರ್ಕಿಕ init_seen = ಅಸತ್ಯ;
  ತಾರ್ಕಿಕ init_use_destroy_seen = ಅಸತ್ಯ;
  ವೃಕ್ಷ init_no_targetsync_clause = NULL_ವೃಕ್ಷ;
  ವೃಕ್ಷ depend_clause = NULL_ವೃಕ್ಷ;

  ಯದಿ (!openacc)
    clauses = omp_remove_duplicate_maps (clauses, ಸತ್ಯ);

  bitmap_obstack_initialize (ರಿಕ್ತ);
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

  ಯದಿ (openacc)
    ಪ್ರತಿ (c = clauses; c; c = OMP_CLAUSE_CHAIN (c))
      ಯದಿ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ASYNC)
	{
	  oacc_async = ಸತ್ಯ;
	  ಭಙ್ಗ;
	}

  ವೃಕ್ಷ *grp_start_p = ರಿಕ್ತ, grp_sentinel = NULL_ವೃಕ್ಷ;

  ಪ್ರತಿ (pc = &clauses, c = clauses; c ; c = *pc)
    {
      ತಾರ್ಕಿಕ remove = ಅಸತ್ಯ;
      ತಾರ್ಕಿಕ need_complete = ಅಸತ್ಯ;
      ತಾರ್ಕಿಕ need_implicitly_determined = ಅಸತ್ಯ;

      /* We've reached the end of a list of expanded nodes.  Reset the group
	 start pointer.  */
      ಯದಿ (c == grp_sentinel)
	{
	  ಯದಿ (grp_start_p
	      && OMP_CLAUSE_HAS_ITERATORS (*grp_start_p))
	    ಪ್ರತಿ (ವೃಕ್ಷ gc = *grp_start_p; gc != grp_sentinel;
		 gc = OMP_CLAUSE_CHAIN (gc))
	      OMP_CLAUSE_ITERATORS (gc) = OMP_CLAUSE_ITERATORS (*grp_start_p);
	  grp_start_p = ರಿಕ್ತ;
	}

      ವಿಕಲ್ಪ (OMP_CLAUSE_CODE (c))
	{
	ಪಕ್ಷ OMP_CLAUSE_SHARED:
	  need_implicitly_determined = ಸತ್ಯ;
	  ಗಚ್ಛ check_dup_generic;

	ಪಕ್ಷ OMP_CLAUSE_PRIVATE:
	  need_complete = ಸತ್ಯ;
	  need_implicitly_determined = ಸತ್ಯ;
	  ಗಚ್ಛ check_dup_generic;

	ಪಕ್ಷ OMP_CLAUSE_REDUCTION:
	  ಯದಿ (reduction_seen == 0)
	    reduction_seen = OMP_CLAUSE_REDUCTION_INSCAN (c) ? -1 : 1;
	  ಅನ್ಯಥಾ ಯದಿ (reduction_seen != -2
		   && reduction_seen != (OMP_CLAUSE_REDUCTION_INSCAN (c)
					 ? -1 : 1))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<inscan%> and non-%<inscan%> %<reduction%> clauses "
			"on the same construct");
	      reduction_seen = -2;
	    }
	  /* FALLTHRU */
	ಪಕ್ಷ OMP_CLAUSE_IN_REDUCTION:
	ಪಕ್ಷ OMP_CLAUSE_TASK_REDUCTION:
	  need_implicitly_determined = ಸತ್ಯ;
	  t = OMP_CLAUSE_DECL (c);
	  ಯದಿ (ವೃಕ್ಷ_CODE (t) == OMP_ARRAY_SECTION)
	    {
	      ಯದಿ (handle_omp_array_sections (c, ort))
		{
		  remove = ಸತ್ಯ;
		  ಭಙ್ಗ;
		}

	      t = OMP_CLAUSE_DECL (c);
	      ಯದಿ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
		  && OMP_CLAUSE_REDUCTION_INSCAN (c))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<inscan%> %<reduction%> clause with array "
			    "section");
		  remove = ಸತ್ಯ;
		  ಭಙ್ಗ;
		}
	    }
	  t = require_complete_type (OMP_CLAUSE_LOCATION (c), t);
	  ಯದಿ (t == error_mark_ಗಂಟು)
	    {
	      remove = ಸತ್ಯ;
	      ಭಙ್ಗ;
	    }
	  ಯದಿ (oacc_async)
	    c_mark_addressable (t);
	  type = ವೃಕ್ಷ_TYPE (t);
	  ಯದಿ (ವೃಕ್ಷ_CODE (t) == MEM_REF)
	    type = ವೃಕ್ಷ_TYPE (type);
	  ಯದಿ (ವೃಕ್ಷ_CODE (type) == ARRAY_TYPE)
	    {
	      ವೃಕ್ಷ oatype = type;
	      gcc_assert (ವೃಕ್ಷ_CODE (t) != MEM_REF);
	      ಯಾವತ್ (ವೃಕ್ಷ_CODE (type) == ARRAY_TYPE)
		type = ವೃಕ್ಷ_TYPE (type);
	      ಯದಿ (integer_zerop (TYPE_SIZE_UNIT (type)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD in %<reduction%> clause is a zero size array",
			    t);
		  remove = ಸತ್ಯ;
		  ಭಙ್ಗ;
		}
	      ವೃಕ್ಷ size = size_binop (EXACT_DIV_ಅಭಿವ್ಯಕ್ತಿ, TYPE_SIZE_UNIT (oatype),
				      TYPE_SIZE_UNIT (type));
	      ಯದಿ (integer_zerop (size))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD in %<reduction%> clause is a zero size array",
			    t);
		  remove = ಸತ್ಯ;
		  ಭಙ್ಗ;
		}
	      size = size_binop (MINUS_ಅಭಿವ್ಯಕ್ತಿ, size, size_one_ಗಂಟು);
	      size = save_ಅಭಿವ್ಯಕ್ತಿ (size);
	      ವೃಕ್ಷ index_type = build_index_type (size);
	      ವೃಕ್ಷ atype = c_build_array_type (TYPE_MAIN_VARIANT (type),
					       index_type);
	      atype = c_build_qualified_type (atype, TYPE_QUALS (type));
	      ವೃಕ್ಷ ptype = c_build_pointer_type (type);
	      ಯದಿ (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (t)) == ARRAY_TYPE)
		t = build_fold_addr_ಅಭಿವ್ಯಕ್ತಿ (t);
	      t = build2 (MEM_REF, atype, t, build_int_cst (ptype, 0));
	      OMP_CLAUSE_DECL (c) = t;
	    }
	  ಯದಿ (TYPE_ATOMIC (type))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<_Atomic%> %qE in %<reduction%> clause", t);
	      remove = ಸತ್ಯ;
	      ಭಙ್ಗ;
	    }
	  ಯದಿ (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_REDUCTION
	      || OMP_CLAUSE_REDUCTION_TASK (c))
	    {
	      /* Disallow zero sized or potentially zero sized task
		 reductions.  */
	      ಯದಿ (integer_zerop (TYPE_SIZE_UNIT (type)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "zero sized type %qT in %qs clause", type,
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  remove = ಸತ್ಯ;
		  ಭಙ್ಗ;
		}
	      ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (TYPE_SIZE_UNIT (type)) != INTEGER_CST)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "variable sized type %qT in %qs clause", type,
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  remove = ಸತ್ಯ;
		  ಭಙ್ಗ;
		}
	    }
	  ಯದಿ (OMP_CLAUSE_REDUCTION_PLACEHOLDER (c) == NULL_ವೃಕ್ಷ
	      && (FLOAT_TYPE_P (type)
		  || ವೃಕ್ಷ_CODE (type) == COMPLEX_TYPE))
	    {
	      ಗಣನಾ ವೃಕ್ಷ_code r_code = OMP_CLAUSE_REDUCTION_CODE (c);
	      ಧ್ರುವ ವರ್ಣ *r_name = ರಿಕ್ತ;

	      ವಿಕಲ್ಪ (r_code)
		{
		ಪಕ್ಷ PLUS_ಅಭಿವ್ಯಕ್ತಿ:
		ಪಕ್ಷ MULT_ಅಭಿವ್ಯಕ್ತಿ:
		ಪಕ್ಷ MINUS_ಅಭಿವ್ಯಕ್ತಿ:
		ಪಕ್ಷ TRUTH_ANDIF_ಅಭಿವ್ಯಕ್ತಿ:
		ಪಕ್ಷ TRUTH_ORIF_ಅಭಿವ್ಯಕ್ತಿ:
		  ಭಙ್ಗ;
		ಪಕ್ಷ MIN_ಅಭಿವ್ಯಕ್ತಿ:
		  ಯದಿ (ವೃಕ್ಷ_CODE (type) == COMPLEX_TYPE)
		    r_name = "min";
		  ಭಙ್ಗ;
		ಪಕ್ಷ MAX_ಅಭಿವ್ಯಕ್ತಿ:
		  ಯದಿ (ವೃಕ್ಷ_CODE (type) == COMPLEX_TYPE)
		    r_name = "max";
		  ಭಙ್ಗ;
		ಪಕ್ಷ BIT_AND_ಅಭಿವ್ಯಕ್ತಿ:
		  r_name = "&";
		  ಭಙ್ಗ;
		ಪಕ್ಷ BIT_XOR_ಅಭಿವ್ಯಕ್ತಿ:
		  r_name = "^";
		  ಭಙ್ಗ;
		ಪಕ್ಷ BIT_IOR_ಅಭಿವ್ಯಕ್ತಿ:
		  r_name = "|";
		  ಭಙ್ಗ;
		ಸ್ವಭಾವ:
		  gcc_unreachable ();
		}
	      ಯದಿ (r_name)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qE has invalid type for %<reduction(%s)%>",
			    t, r_name);
		  remove = ಸತ್ಯ;
		  ಭಙ್ಗ;
		}
	    }
	  ಅನ್ಯಥಾ ಯದಿ (OMP_CLAUSE_REDUCTION_PLACEHOLDER (c) == error_mark_ಗಂಟು)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"user defined reduction not found for %qE", t);
	      remove = ಸತ್ಯ;
	      ಭಙ್ಗ;
	    }
	  ಅನ್ಯಥಾ ಯದಿ (OMP_CLAUSE_REDUCTION_PLACEHOLDER (c))
	    {
	      ವೃಕ್ಷ list = OMP_CLAUSE_REDUCTION_PLACEHOLDER (c);
	      type = TYPE_MAIN_VARIANT (type);
	      ವೃಕ್ಷ placeholder = build_decl (OMP_CLAUSE_LOCATION (c),
					     VAR_DECL, NULL_ವೃಕ್ಷ, type);
	      ವೃಕ್ಷ decl_placeholder = NULL_ವೃಕ್ಷ;
	      OMP_CLAUSE_REDUCTION_PLACEHOLDER (c) = placeholder;
	      DECL_ARTIFICIAL (placeholder) = 1;
	      DECL_IGNORED_P (placeholder) = 1;
	      ಯದಿ (ವೃಕ್ಷ_CODE (t) == MEM_REF)
		{
		  decl_placeholder = build_decl (OMP_CLAUSE_LOCATION (c),
						 VAR_DECL, NULL_ವೃಕ್ಷ, type);
		  OMP_CLAUSE_REDUCTION_DECL_PLACEHOLDER (c) = decl_placeholder;
		  DECL_ARTIFICIAL (decl_placeholder) = 1;
		  DECL_IGNORED_P (decl_placeholder) = 1;
		}
	      ಯದಿ (ವೃಕ್ಷ_ADDRESSABLE (ವೃಕ್ಷ_VEC_ELT (list, 0)))
		c_mark_addressable (placeholder);
	      ಯದಿ (ವೃಕ್ಷ_ADDRESSABLE (ವೃಕ್ಷ_VEC_ELT (list, 1)))
		c_mark_addressable (decl_placeholder ? decl_placeholder
				    : OMP_CLAUSE_DECL (c));
	      OMP_CLAUSE_REDUCTION_MERGE (c)
		= c_clone_omp_udr (ವೃಕ್ಷ_VEC_ELT (list, 2),
				   ವೃಕ್ಷ_VEC_ELT (list, 0),
				   ವೃಕ್ಷ_VEC_ELT (list, 1),
				   decl_placeholder ? decl_placeholder
				   : OMP_CLAUSE_DECL (c), placeholder);
	      OMP_CLAUSE_REDUCTION_MERGE (c)
		= build3_loc (OMP_CLAUSE_LOCATION (c), BIND_ಅಭಿವ್ಯಕ್ತಿ,
			      void_type_ಗಂಟು, NULL_ವೃಕ್ಷ,
			      OMP_CLAUSE_REDUCTION_MERGE (c), NULL_ವೃಕ್ಷ);
	      ವೃಕ್ಷ_SIDE_EFFECTS (OMP_CLAUSE_REDUCTION_MERGE (c)) = 1;
	      ಯದಿ (ವೃಕ್ಷ_VEC_LENGTH (list) == 6)
		{
		  ಯದಿ (ವೃಕ್ಷ_ADDRESSABLE (ವೃಕ್ಷ_VEC_ELT (list, 3)))
		    c_mark_addressable (decl_placeholder ? decl_placeholder
					: OMP_CLAUSE_DECL (c));
		  ಯದಿ (ವೃಕ್ಷ_ADDRESSABLE (ವೃಕ್ಷ_VEC_ELT (list, 4)))
		    c_mark_addressable (placeholder);
		  ವೃಕ್ಷ init = ವೃಕ್ಷ_VEC_ELT (list, 5);
		  ಯದಿ (init == error_mark_ಗಂಟು)
		    init = DECL_INITIAL (ವೃಕ್ಷ_VEC_ELT (list, 3));
		  OMP_CLAUSE_REDUCTION_INIT (c)
		    = c_clone_omp_udr (init, ವೃಕ್ಷ_VEC_ELT (list, 4),
				       ವೃಕ್ಷ_VEC_ELT (list, 3),
				       decl_placeholder ? decl_placeholder
				       : OMP_CLAUSE_DECL (c), placeholder);
		  ಯದಿ (ವೃಕ್ಷ_VEC_ELT (list, 5) == error_mark_ಗಂಟು)
		    {
		      ವೃಕ್ಷ v = decl_placeholder ? decl_placeholder : t;
		      OMP_CLAUSE_REDUCTION_INIT (c)
			= build2 (INIT_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (v), v,
				  OMP_CLAUSE_REDUCTION_INIT (c));
		    }
		  ಯದಿ (walk_ವೃಕ್ಷ (&OMP_CLAUSE_REDUCTION_INIT (c),
				 c_find_omp_placeholder_r,
				 placeholder, ರಿಕ್ತ))
		    OMP_CLAUSE_REDUCTION_OMP_ORIG_REF (c) = 1;
		}
	      ಅನ್ಯಥಾ
		{
		  ವೃಕ್ಷ init;
		  ವೃಕ್ಷ v = decl_placeholder ? decl_placeholder : t;
		  ಯದಿ (AGGREGATE_TYPE_P (ವೃಕ್ಷ_TYPE (v)))
		    init = build_constructor (ವೃಕ್ಷ_TYPE (v), ರಿಕ್ತ);
		  ಅನ್ಯಥಾ
		    init = fold_convert (ವೃಕ್ಷ_TYPE (v), integer_zero_ಗಂಟು);
		  OMP_CLAUSE_REDUCTION_INIT (c)
		    = build2 (INIT_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (v), v, init);
		}
	      OMP_CLAUSE_REDUCTION_INIT (c)
		= build3_loc (OMP_CLAUSE_LOCATION (c), BIND_ಅಭಿವ್ಯಕ್ತಿ,
			      void_type_ಗಂಟು, NULL_ವೃಕ್ಷ,
			       OMP_CLAUSE_REDUCTION_INIT (c), NULL_ವೃಕ್ಷ);
	      ವೃಕ್ಷ_SIDE_EFFECTS (OMP_CLAUSE_REDUCTION_INIT (c)) = 1;
	    }
	  ಯದಿ (ವೃಕ್ಷ_CODE (t) == MEM_REF)
	    {
	      ಯದಿ (TYPE_SIZE_UNIT (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (t))) == NULL_ವೃಕ್ಷ
		  || ವೃಕ್ಷ_CODE (TYPE_SIZE_UNIT (ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (t))))
		     != INTEGER_CST)
		{
		  sorry ("variable length element type in array "
			 "%<reduction%> clause");
		  remove = ಸತ್ಯ;
		  ಭಙ್ಗ;
		}
	      t = ವೃಕ್ಷ_OPERAND (t, 0);
	      ಯದಿ (ವೃಕ್ಷ_CODE (t) == POINTER_PLUS_ಅಭಿವ್ಯಕ್ತಿ)
		t = ವೃಕ್ಷ_OPERAND (t, 0);
	      ಯದಿ (ವೃಕ್ಷ_CODE (t) == ADDR_ಅಭಿವ್ಯಕ್ತಿ)
		t = ವೃಕ್ಷ_OPERAND (t, 0);
	    }
	  ಗಚ್ಛ check_dup_generic_t;

	ಪಕ್ಷ OMP_CLAUSE_COPYPRIVATE:
	  copyprivate_seen = ಸತ್ಯ;
	  ಯದಿ (nowait_clause)
	    {
	      error_at (OMP_CLAUSE_LOCATION (*nowait_clause),
			"%<nowait%> clause must not be used together "
			"with %<copyprivate%> clause");
	      *nowait_clause = OMP_CLAUSE_CHAIN (*nowait_clause);
	      nowait_clause = ರಿಕ್ತ;
	    }
	  ಗಚ್ಛ check_dup_generic;

	ಪಕ್ಷ OMP_CLAUSE_COPYIN:
	  t = OMP_CLAUSE_DECL (c);
	  ಯದಿ (!VAR_P (t) || !DECL_THREAD_LOCAL_P (t))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE must be %<threadprivate%> for %<copyin%>", t);
	      remove = ಸತ್ಯ;
	      ಭಙ್ಗ;
	    }
	  ಗಚ್ಛ check_dup_generic;

	ಪಕ್ಷ OMP_CLAUSE_LINEAR:
	  ಯದಿ (ort != C_ORT_OMP_DECLARE_SIMD)
	    need_implicitly_determined = ಸತ್ಯ;
	  t = OMP_CLAUSE_DECL (c);
	  ಯದಿ (ort != C_ORT_OMP_DECLARE_SIMD
	      && OMP_CLAUSE_LINEAR_KIND (c) != OMP_CLAUSE_LINEAR_DEFAULT
	      && OMP_CLAUSE_LINEAR_OLD_LINEAR_MODIFIER (c))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"modifier should not be specified in %<linear%> "
			"clause on %<simd%> or %<for%> constructs when not "
			"using OpenMP 5.2 modifiers");
	      OMP_CLAUSE_LINEAR_KIND (c) = OMP_CLAUSE_LINEAR_DEFAULT;
	    }
	  ಯದಿ (!INTEGRAL_TYPE_P (ವೃಕ್ಷ_TYPE (t))
	      && ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (t)) != POINTER_TYPE)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"linear clause applied to non-integral non-pointer "
			"variable with type %qT", ವೃಕ್ಷ_TYPE (t));
	      remove = ಸತ್ಯ;
	      ಭಙ್ಗ;
	    }
	  ಯದಿ (TYPE_ATOMIC (ವೃಕ್ಷ_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<_Atomic%> %qD in %<linear%> clause", t);
	      remove = ಸತ್ಯ;
	      ಭಙ್ಗ;
	    }
	  ಯದಿ (ort == C_ORT_OMP_DECLARE_SIMD)
	    {
	      ವೃಕ್ಷ s = OMP_CLAUSE_LINEAR_STEP (c);
	      ಯದಿ (ವೃಕ್ಷ_CODE (s) == PARM_DECL)
		{
		  OMP_CLAUSE_LINEAR_VARIABLE_STRIDE (c) = 1;
		  /* map_head bitmap is used as uniform_head if
		     declare_simd.  */
		  ಯದಿ (!bitmap_bit_p (&map_head, DECL_UID (s)))
		    linear_variable_step_check = ಸತ್ಯ;
		  ಗಚ್ಛ check_dup_generic;
		}
	      ಯದಿ (ವೃಕ್ಷ_CODE (s) != INTEGER_CST)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<linear%> clause step %qE is neither constant "
			    "nor a parameter", s);
		  remove = ಸತ್ಯ;
		  ಭಙ್ಗ;
		}
	    }
	  ಯದಿ (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (OMP_CLAUSE_DECL (c))) == POINTER_TYPE)
	    {
	      ವೃಕ್ಷ s = OMP_CLAUSE_LINEAR_STEP (c);
	      s = pointer_int_sum (OMP_CLAUSE_LOCATION (c), PLUS_ಅಭಿವ್ಯಕ್ತಿ,
				   OMP_CLAUSE_DECL (c), s);
	      s = fold_build2_loc (OMP_CLAUSE_LOCATION (c), MINUS_ಅಭಿವ್ಯಕ್ತಿ,
				   sizetype, fold_convert (sizetype, s),
				   fold_convert
				     (sizetype, OMP_CLAUSE_DECL (c)));
	      ಯದಿ (s == error_mark_ಗಂಟು)
		s = size_one_ಗಂಟು;
	      OMP_CLAUSE_LINEAR_STEP (c) = s;
	    }
	  ಅನ್ಯಥಾ
	    OMP_CLAUSE_LINEAR_STEP (c)
	      = fold_convert (ವೃಕ್ಷ_TYPE (t), OMP_CLAUSE_LINEAR_STEP (c));
	  ಗಚ್ಛ check_dup_generic;

	check_dup_generic:
	  t = OMP_CLAUSE_DECL (c);
	check_dup_generic_t:
	  ಯದಿ (!VAR_P (t) && ವೃಕ್ಷ_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %qs", t,
			omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	      remove = ಸತ್ಯ;
	    }
	  ಅನ್ಯಥಾ ಯದಿ ((openacc && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION)
		   || (ort == C_ORT_OMP
		       && (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_USE_DEVICE_PTR
			   || (OMP_CLAUSE_CODE (c)
			       == OMP_CLAUSE_USE_DEVICE_ADDR)))
		   || (ort == C_ORT_OMP_TARGET
		       && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION))
	    {
	      ಯದಿ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION
		  && (bitmap_bit_p (&generic_head, DECL_UID (t))
		      || bitmap_bit_p (&firstprivate_head, DECL_UID (t))))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in data-sharing "
			    "clauses", t);
		  remove = ಸತ್ಯ;
		  ಭಙ್ಗ;
		}
	      ಯದಿ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IN_REDUCTION)
		target_in_reduction_seen = ಸತ್ಯ;
	      ಯದಿ (bitmap_bit_p (&oacc_reduction_head, DECL_UID (t)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    openacc
			    ? "%qD appears more than once in reduction clauses"
			    : "%qD appears more than once in data clauses",
			    t);
		  remove = ಸತ್ಯ;
		}
	      ಅನ್ಯಥಾ
		bitmap_set_bit (&oacc_reduction_head, DECL_UID (t));
	    }
	  ಅನ್ಯಥಾ ಯದಿ (bitmap_bit_p (&generic_head, DECL_UID (t))
		   || bitmap_bit_p (&firstprivate_head, DECL_UID (t))
		   || bitmap_bit_p (&lastprivate_head, DECL_UID (t))
		   || bitmap_bit_p (&map_firstprivate_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in data clauses", t);
	      remove = ಸತ್ಯ;
	    }
	  ಅನ್ಯಥಾ ಯದಿ ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_PRIVATE
		    || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_HAS_DEVICE_ADDR
		    || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IS_DEVICE_PTR)
		   && bitmap_bit_p (&map_head, DECL_UID (t)))
	    {
	      ಯದಿ (openacc)
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears more than once in data clauses", t);
	      ಅನ್ಯಥಾ
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears both in data and map clauses", t);
	      remove = ಸತ್ಯ;
	    }
	  ಅನ್ಯಥಾ
	    bitmap_set_bit (&generic_head, DECL_UID (t));
	  ಭಙ್ಗ;

	ಪಕ್ಷ OMP_CLAUSE_FIRSTPRIVATE:
	  ಯದಿ (OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (c) && !implicit_moved)
	    {
	    move_implicit:
	      implicit_moved = ಸತ್ಯ;
	      /* Move firstprivate and map clauses with
		 OMP_CLAUSE_{FIRSTPRIVATE,MAP}_IMPLICIT set to the end of
		 clauses chain.  */
	      ವೃಕ್ಷ cl1 = NULL_ವೃಕ್ಷ, cl2 = NULL_ವೃಕ್ಷ;
	      ವೃಕ್ಷ *pc1 = pc, *pc2 = &cl1, *pc3 = &cl2;
	      ಯಾವತ್ (*pc1)
		ಯದಿ (OMP_CLAUSE_CODE (*pc1) == OMP_CLAUSE_FIRSTPRIVATE
		    && OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (*pc1))
		  {
		    *pc3 = *pc1;
		    pc3 = &OMP_CLAUSE_CHAIN (*pc3);
		    *pc1 = OMP_CLAUSE_CHAIN (*pc1);
		  }
		ಅನ್ಯಥಾ ಯದಿ (OMP_CLAUSE_CODE (*pc1) == OMP_CLAUSE_MAP
			 && OMP_CLAUSE_MAP_IMPLICIT (*pc1))
		  {
		    *pc2 = *pc1;
		    pc2 = &OMP_CLAUSE_CHAIN (*pc2);
		    *pc1 = OMP_CLAUSE_CHAIN (*pc1);
		  }
		ಅನ್ಯಥಾ
		  pc1 = &OMP_CLAUSE_CHAIN (*pc1);
	      *pc3 = ರಿಕ್ತ;
	      *pc2 = cl2;
	      *pc1 = cl1;
	      ಅನುವರ್ತ;
	    }
	  t = OMP_CLAUSE_DECL (c);
	  need_complete = ಸತ್ಯ;
	  need_implicitly_determined = ಸತ್ಯ;
	  ಯದಿ (!VAR_P (t) && ವೃಕ್ಷ_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %<firstprivate%>", t);
	      remove = ಸತ್ಯ;
	    }
	  ಅನ್ಯಥಾ ಯದಿ (OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (c)
		   && !OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT_TARGET (c)
		   && bitmap_bit_p (&map_firstprivate_head, DECL_UID (t)))
	    remove = ಸತ್ಯ;
	  ಅನ್ಯಥಾ ಯದಿ (bitmap_bit_p (&generic_head, DECL_UID (t))
		   || bitmap_bit_p (&firstprivate_head, DECL_UID (t))
		   || bitmap_bit_p (&map_firstprivate_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in data clauses", t);
	      remove = ಸತ್ಯ;
	    }
	  ಅನ್ಯಥಾ ಯದಿ (bitmap_bit_p (&map_head, DECL_UID (t))
		   || bitmap_bit_p (&map_field_head, DECL_UID (t)))
	    {
	      ಯದಿ (openacc)
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears more than once in data clauses", t);
	      ಅನ್ಯಥಾ ಯದಿ (OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT (c)
		       && !OMP_CLAUSE_FIRSTPRIVATE_IMPLICIT_TARGET (c))
		/* Silently drop the clause.  */;
	      ಅನ್ಯಥಾ
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears both in data and map clauses", t);
	      remove = ಸತ್ಯ;
	    }
	  ಅನ್ಯಥಾ
	    bitmap_set_bit (&firstprivate_head, DECL_UID (t));
	  ಭಙ್ಗ;

	ಪಕ್ಷ OMP_CLAUSE_LASTPRIVATE:
	  t = OMP_CLAUSE_DECL (c);
	  need_complete = ಸತ್ಯ;
	  need_implicitly_determined = ಸತ್ಯ;
	  ಯದಿ (!VAR_P (t) && ವೃಕ್ಷ_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %<lastprivate%>", t);
	      remove = ಸತ್ಯ;
	    }
	  ಅನ್ಯಥಾ ಯದಿ (bitmap_bit_p (&generic_head, DECL_UID (t))
		   || bitmap_bit_p (&lastprivate_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
		     "%qE appears more than once in data clauses", t);
	      remove = ಸತ್ಯ;
	    }
	  ಅನ್ಯಥಾ
	    bitmap_set_bit (&lastprivate_head, DECL_UID (t));
	  ಭಙ್ಗ;

	ಪಕ್ಷ OMP_CLAUSE_ALIGNED:
	  t = OMP_CLAUSE_DECL (c);
	  ಯದಿ (!VAR_P (t) && ವೃಕ್ಷ_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in %<aligned%> clause", t);
	      remove = ಸತ್ಯ;
	    }
	  ಅನ್ಯಥಾ ಯದಿ (!POINTER_TYPE_P (ವೃಕ್ಷ_TYPE (t))
		   && ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (t)) != ARRAY_TYPE)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE in %<aligned%> clause is neither a pointer nor "
			"an array", t);
	      remove = ಸತ್ಯ;
	    }
	  ಅನ್ಯಥಾ ಯದಿ (TYPE_ATOMIC (ವೃಕ್ಷ_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<_Atomic%> %qD in %<aligned%> clause", t);
	      remove = ಸತ್ಯ;
	      ಭಙ್ಗ;
	    }
	  ಅನ್ಯಥಾ ಯದಿ (bitmap_bit_p (&aligned_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in %<aligned%> clauses",
			t);
	      remove = ಸತ್ಯ;
	    }
	  ಅನ್ಯಥಾ
	    bitmap_set_bit (&aligned_head, DECL_UID (t));
	  ಭಙ್ಗ;

	ಪಕ್ಷ OMP_CLAUSE_NONTEMPORAL:
	  t = OMP_CLAUSE_DECL (c);
	  ಯದಿ (!VAR_P (t) && ವೃಕ್ಷ_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in %<nontemporal%> clause", t);
	      remove = ಸತ್ಯ;
	    }
	  ಅನ್ಯಥಾ ಯದಿ (bitmap_bit_p (&oacc_reduction_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in %<nontemporal%> "
			"clauses", t);
	      remove = ಸತ್ಯ;
	    }
	  ಅನ್ಯಥಾ
	    bitmap_set_bit (&oacc_reduction_head, DECL_UID (t));
	  ಭಙ್ಗ;

	ಪಕ್ಷ OMP_CLAUSE_ALLOCATE:
	  t = OMP_CLAUSE_DECL (c);
	  ಯದಿ (!VAR_P (t) && ವೃಕ್ಷ_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in %<allocate%> clause", t);
	      remove = ಸತ್ಯ;
	    }
	  ಅನ್ಯಥಾ ಯದಿ (bitmap_bit_p (&aligned_head, DECL_UID (t)))
	    {
	      warning_at (OMP_CLAUSE_LOCATION (c), OPT_Wopenmp,
			  "%qE appears more than once in %<allocate%> clauses",
			  t);
	      remove = ಸತ್ಯ;
	    }
	  ಅನ್ಯಥಾ
	    {
	      bitmap_set_bit (&aligned_head, DECL_UID (t));
	      ಯದಿ (!OMP_CLAUSE_ALLOCATE_COMBINED (c))
		allocate_seen = ಸತ್ಯ;
	    }
	  ಭಙ್ಗ;

	ಪಕ್ಷ OMP_CLAUSE_DOACROSS:
	  t = OMP_CLAUSE_DECL (c);
	  ಯದಿ (t == NULL_ವೃಕ್ಷ)
	    ಭಙ್ಗ;
	  ಯದಿ (OMP_CLAUSE_DOACROSS_KIND (c) == OMP_CLAUSE_DOACROSS_SINK)
	    {
	      gcc_assert (ವೃಕ್ಷ_CODE (t) == ವೃಕ್ಷ_LIST);
	      ಪ್ರತಿ (; t; t = ವೃಕ್ಷ_CHAIN (t))
		{
		  ವೃಕ್ಷ decl = ವೃಕ್ಷ_ಮೌಲ್ಯ (t);
		  ಯದಿ (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (decl)) == POINTER_TYPE)
		    {
		      ವೃಕ್ಷ offset = ವೃಕ್ಷ_PURPOSE (t);
		      ತಾರ್ಕಿಕ neg = wi::neg_p (wi::to_wide (offset));
		      offset = fold_unary (ABS_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (offset), offset);
		      ವೃಕ್ಷ t2 = pointer_int_sum (OMP_CLAUSE_LOCATION (c),
						 neg ? MINUS_ಅಭಿವ್ಯಕ್ತಿ : PLUS_ಅಭಿವ್ಯಕ್ತಿ,
						 decl, offset);
		      t2 = fold_build2_loc (OMP_CLAUSE_LOCATION (c), MINUS_ಅಭಿವ್ಯಕ್ತಿ,
					    sizetype,
					    fold_convert (sizetype, t2),
					    fold_convert (sizetype, decl));
		      ಯದಿ (t2 == error_mark_ಗಂಟು)
			{
			  remove = ಸತ್ಯ;
			  ಭಙ್ಗ;
			}
		      ವೃಕ್ಷ_PURPOSE (t) = t2;
		    }
		}
	      ಭಙ್ಗ;
	    }
	  gcc_unreachable ();

	ಪಕ್ಷ OMP_CLAUSE_USES_ALLOCATORS:
	  t = OMP_CLAUSE_USES_ALLOCATORS_ALLOCATOR (c);
	  ಯದಿ (t == error_mark_ಗಂಟು)
	    {
	      remove = ಸತ್ಯ;
	      ಭಙ್ಗ;
	    }
	  ಯದಿ ((VAR_P (t) || ವೃಕ್ಷ_CODE (t) == PARM_DECL)
	      && (bitmap_bit_p (&generic_head, DECL_UID (t))
		  || bitmap_bit_p (&map_head, DECL_UID (t))
		  || bitmap_bit_p (&firstprivate_head, DECL_UID (t))
		  || bitmap_bit_p (&lastprivate_head, DECL_UID (t))))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once in data clauses", t);
	      remove = ಸತ್ಯ;
	      ಭಙ್ಗ;
	    }
	  ಅನ್ಯಥಾ
	    bitmap_set_bit (&generic_head, DECL_UID (t));
	  ಯದಿ (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (t)) != ENUMERAL_TYPE
	      || strcmp (IDENTIFIER_POINTER (TYPE_IDENTIFIER (ವೃಕ್ಷ_TYPE (t))),
			 "omp_allocator_handle_t") != 0)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"allocator %qE must be of %<omp_allocator_handle_t%> "
			"type", t);
	      remove = ಸತ್ಯ;
	      ಭಙ್ಗ;
	    }
	  ವೃಕ್ಷ init;
	  ಯದಿ (!DECL_P (t)
	      || (ವೃಕ್ಷ_CODE (t) == CONST_DECL
		  && ((init = DECL_INITIAL(t)) == nullptr
		      || ವೃಕ್ಷ_CODE (init) != INTEGER_CST
		      || ((wi::to_widest (init) < 0
			   || wi::to_widest (init) > GOMP_OMP_PREDEF_ALLOC_MAX)
			  && (wi::to_widest (init) < GOMP_OMPX_PREDEF_ALLOC_MIN
			      || (wi::to_widest (init)
				  > GOMP_OMPX_PREDEF_ALLOC_MAX))))))
	    {
	      remove = ಸತ್ಯ;
	      error_at (OMP_CLAUSE_LOCATION (c),
			"allocator %qE must be either a variable or a "
			"predefined allocator", t);
	      ಭಙ್ಗ;
	    }
	  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (t) == CONST_DECL)
	    {
	      /* omp_null_allocator is ignored and for predefined allocators,
		 no special handling is required; thus, mark them removed. */
	      remove = ಸತ್ಯ;

	      ಯದಿ (OMP_CLAUSE_USES_ALLOCATORS_MEMSPACE (c)
		  || OMP_CLAUSE_USES_ALLOCATORS_TRAITS (c))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "modifiers cannot be used with predefined "
			    "allocator %qE", t);
		  ಭಙ್ಗ;
		}
	    }
	  t = OMP_CLAUSE_USES_ALLOCATORS_MEMSPACE (c);
	  ಯದಿ (t == error_mark_ಗಂಟು)
	    {
	      remove = ಸತ್ಯ;
	      ಭಙ್ಗ;
	    }
	  ಯದಿ (t != NULL_ವೃಕ್ಷ
	      && ((ವೃಕ್ಷ_CODE (t) != CONST_DECL && ವೃಕ್ಷ_CODE (t) != INTEGER_CST)
		  || ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (t)) != ENUMERAL_TYPE
		  || strcmp (IDENTIFIER_POINTER (TYPE_IDENTIFIER (ವೃಕ್ಷ_TYPE (t))),
			     "omp_memspace_handle_t") != 0))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c), "memspace modifier %qE must be"
			" constant enum of %<omp_memspace_handle_t%> type", t);
	      remove = ಸತ್ಯ;
	      ಭಙ್ಗ;
	    }
	  t = OMP_CLAUSE_USES_ALLOCATORS_TRAITS (c);
	  ಯದಿ (t == error_mark_ಗಂಟು)
	    {
	      remove = ಸತ್ಯ;
	      ಭಙ್ಗ;
	    }
	  ಯದಿ (t != NULL_ವೃಕ್ಷ
	      && t != error_mark_ಗಂಟು
	      && (DECL_EXTERNAL (t)
		  || ವೃಕ್ಷ_CODE (t) == PARM_DECL))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c), "traits array %qE must be "
			"defined in same scope as the construct on which the "
			"clause appears", t);
	      remove = ಸತ್ಯ;
	    }
	  ಯದಿ (t != NULL_ವೃಕ್ಷ)
	    {
	      ತಾರ್ಕಿಕ type_err = ಅಸತ್ಯ;

	      ಯದಿ (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (t)) != ARRAY_TYPE
		  || DECL_SIZE (t) == NULL_ವೃಕ್ಷ
		  || !COMPLETE_TYPE_P (ವೃಕ್ಷ_TYPE (t)))
		type_err = ಸತ್ಯ;
	      ಅನ್ಯಥಾ
		{
		  ವೃಕ್ಷ elem_t = ವೃಕ್ಷ_TYPE (ವೃಕ್ಷ_TYPE (t));
		  ಯದಿ (ವೃಕ್ಷ_CODE (elem_t) != RECORD_TYPE
		      || strcmp (IDENTIFIER_POINTER (TYPE_IDENTIFIER (elem_t)),
				 "omp_alloctrait_t") != 0
		      || !TYPE_READONLY (elem_t))
		    type_err = ಸತ್ಯ;
		}
	      ಯದಿ (type_err)
		{
		  ಯದಿ (t != error_mark_ಗಂಟು)
		    error_at (OMP_CLAUSE_LOCATION (c), "traits array %qE must "
			      "be of %<const omp_alloctrait_t []%> type", t);
		  ಅನ್ಯಥಾ
		    error_at (OMP_CLAUSE_LOCATION (c), "traits array must "
			      "be of %<const omp_alloctrait_t []%> type");
		  remove = ಸತ್ಯ;
		}
	      ಅನ್ಯಥಾ
		{
		  ವೃಕ್ಷ cst_val = decl_constant_ಮೌಲ್ಯ_1 (t, ಸತ್ಯ);
		  ಯದಿ (cst_val == t)
		    {
		      error_at (OMP_CLAUSE_LOCATION (c), "traits array must be "
				"initialized with constants");

		      remove = ಸತ್ಯ;
		    }
		}
	    }
	  ಯದಿ (remove)
	    ಭಙ್ಗ;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ಅನುವರ್ತ;
	ಪಕ್ಷ OMP_CLAUSE_DEPEND:
	  depend_clause = c;
	  /* FALLTHRU */
	ಪಕ್ಷ OMP_CLAUSE_AFFINITY:
	  t = OMP_CLAUSE_DECL (c);
	  ಯದಿ (OMP_ITERATOR_DECL_P (t))
	    {
	      ಯದಿ (ವೃಕ್ಷ_PURPOSE (t) != last_iterators)
		last_iterators_remove
		  = c_omp_finish_iterators (ವೃಕ್ಷ_PURPOSE (t));
	      last_iterators = ವೃಕ್ಷ_PURPOSE (t);
	      t = ವೃಕ್ಷ_ಮೌಲ್ಯ (t);
	      ಯದಿ (last_iterators_remove)
		t = error_mark_ಗಂಟು;
	    }
	  ಅನ್ಯಥಾ
	    last_iterators = NULL_ವೃಕ್ಷ;
	  ಯದಿ (ವೃಕ್ಷ_CODE (t) == OMP_ARRAY_SECTION)
	    {
	      ಯದಿ (handle_omp_array_sections (c, ort))
		remove = ಸತ್ಯ;
	      ಅನ್ಯಥಾ ಯದಿ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
		       && OMP_CLAUSE_DEPEND_KIND (c) == OMP_CLAUSE_DEPEND_DEPOBJ)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<depend%> clause with %<depobj%> dependence "
			    "type on array section");
		  remove = ಸತ್ಯ;
		}
	      ಭಙ್ಗ;
	    }
	  ಯದಿ (t == error_mark_ಗಂಟು)
	    remove = ಸತ್ಯ;
	  ಅನ್ಯಥಾ ಯದಿ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
		   && t == ridpointers[RID_OMP_ALL_MEMORY])
	    {
	      ಯದಿ (OMP_CLAUSE_DEPEND_KIND (c) != OMP_CLAUSE_DEPEND_OUT
		  && OMP_CLAUSE_DEPEND_KIND (c) != OMP_CLAUSE_DEPEND_INOUT)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<omp_all_memory%> used with %<depend%> kind "
			    "other than %<out%> or %<inout%>");
		  remove = ಸತ್ಯ;
		}
	    }
	  ಅನ್ಯಥಾ ಯದಿ (!lvalue_p (t))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not lvalue expression nor array section in "
			"%qs clause", t,
			omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	      remove = ಸತ್ಯ;
	    }
	  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (t) == COMPONENT_REF
		   && DECL_C_BIT_FIELD (ವೃಕ್ಷ_OPERAND (t, 1)))
	    {
	      gcc_assert (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
			  || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_AFFINITY);
	      error_at (OMP_CLAUSE_LOCATION (c),
			"bit-field %qE in %qs clause", t,
			omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	      remove = ಸತ್ಯ;
	    }
	  ಅನ್ಯಥಾ ಯದಿ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
		   && OMP_CLAUSE_DEPEND_KIND (c) == OMP_CLAUSE_DEPEND_DEPOBJ)
	    {
	      ಯದಿ (!c_omp_depend_t_p (ವೃಕ್ಷ_TYPE (t)))
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qE does not have %<omp_depend_t%> type in "
			    "%<depend%> clause with %<depobj%> dependence "
			    "type", t);
		  remove = ಸತ್ಯ;
		}
	    }
	  ಅನ್ಯಥಾ ಯದಿ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DEPEND
		   && c_omp_depend_t_p (ವೃಕ್ಷ_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE should not have %<omp_depend_t%> type in "
			"%<depend%> clause with dependence type other than "
			"%<depobj%>", t);
	      remove = ಸತ್ಯ;
	    }
	  ಯದಿ (!remove)
	    {
	      ಯದಿ (t == ridpointers[RID_OMP_ALL_MEMORY])
		t = null_pointer_ಗಂಟು;
	      ಅನ್ಯಥಾ
		{
		  ವೃಕ್ಷ addr = build_unary_op (OMP_CLAUSE_LOCATION (c),
					      ADDR_ಅಭಿವ್ಯಕ್ತಿ, t, ಅಸತ್ಯ);
		  ಯದಿ (addr == error_mark_ಗಂಟು)
		    {
		      remove = ಸತ್ಯ;
		      ಭಙ್ಗ;
		    }
		  t = build_indirect_ref (OMP_CLAUSE_LOCATION (c), addr,
					  RO_UNARY_STAR);
		  ಯದಿ (t == error_mark_ಗಂಟು)
		    {
		      remove = ಸತ್ಯ;
		      ಭಙ್ಗ;
		    }
		}
	      ಯದಿ (OMP_ITERATOR_DECL_P (OMP_CLAUSE_DECL (c)))
		ವೃಕ್ಷ_ಮೌಲ್ಯ (OMP_CLAUSE_DECL (c)) = t;
	      ಅನ್ಯಥಾ
		OMP_CLAUSE_DECL (c) = t;
	    }
	  ಭಙ್ಗ;

	ಪಕ್ಷ OMP_CLAUSE_MAP:
	  ಯದಿ (OMP_CLAUSE_MAP_IMPLICIT (c) && !implicit_moved)
	    ಗಚ್ಛ move_implicit;
	  ಯದಿ (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_ತಳ್ಳು_MAPPER_NAME
	      || OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_ತೆಗೆ_MAPPER_NAME)
	    {
	      remove = ಸತ್ಯ;
	      ಭಙ್ಗ;
	    }
	  /* FALLTHRU */
	ಪಕ್ಷ OMP_CLAUSE_TO:
	ಪಕ್ಷ OMP_CLAUSE_FROM:
	  ಯದಿ (OMP_CLAUSE_ITERATORS (c)
	      && c_omp_finish_iterators (OMP_CLAUSE_ITERATORS (c)))
	    {
	      t = error_mark_ಗಂಟು;
	      ಭಙ್ಗ;
	    }
	  /* FALLTHRU */
	ಪಕ್ಷ OMP_CLAUSE__CACHE_:
	  {
	    using ನಾಮಾಕಾಶ omp_addr_tokenizer;
	    auto_vec<omp_addr_token *, 10> addr_tokens;

	    t = OMP_CLAUSE_DECL (c);
	    ಯದಿ (ವೃಕ್ಷ_CODE (t) == OMP_ARRAY_SECTION)
	      {
		grp_start_p = pc;
		grp_sentinel = OMP_CLAUSE_CHAIN (c);

		ಯದಿ (handle_omp_array_sections (c, ort))
		  remove = ಸತ್ಯ;
		ಅನ್ಯಥಾ
		  {
		    t = OMP_CLAUSE_DECL (c);
		    ಯದಿ (!omp_mappable_type (ವೃಕ್ಷ_TYPE (t)))
		      {
			error_at (OMP_CLAUSE_LOCATION (c),
				  "array section does not have mappable type "
				  "in %qs clause",
				  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
			remove = ಸತ್ಯ;
		      }
		    ಅನ್ಯಥಾ ಯದಿ (TYPE_ATOMIC (ವೃಕ್ಷ_TYPE (t)))
		      {
			error_at (OMP_CLAUSE_LOCATION (c),
				  "%<_Atomic%> %qE in %qs clause", t,
				  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
			remove = ಸತ್ಯ;
		      }
		    ಯಾವತ್ (ವೃಕ್ಷ_CODE (t) == ARRAY_REF)
		      t = ವೃಕ್ಷ_OPERAND (t, 0);

		    c_omp_address_inspector ai (OMP_CLAUSE_LOCATION (c), t);

		    ಯದಿ (!omp_parse_ಅಭಿವ್ಯಕ್ತಿ (addr_tokens, t))
		      {
			sorry_at (OMP_CLAUSE_LOCATION (c),
				  "unsupported map expression %qE",
				  OMP_CLAUSE_DECL (c));
			remove = ಸತ್ಯ;
			ಭಙ್ಗ;
		      }

		    /* This check is to determine if this will be the only map
		       node created for this clause.  Otherwise, we'll check
		       the following FIRSTPRIVATE_POINTER or ATTACH_DETACH
		       node on the next iteration(s) of the loop.   */
		    ಯದಿ (addr_tokens.length () >= 4
			&& addr_tokens[0]->type == STRUCTURE_BASE
			&& addr_tokens[0]->u.structure_base_kind == BASE_DECL
			&& addr_tokens[1]->type == ACCESS_METHOD
			&& addr_tokens[2]->type == COMPONENT_SELECTOR
			&& addr_tokens[3]->type == ACCESS_METHOD
			&& (addr_tokens[3]->u.access_kind == ACCESS_DIRECT
			    || (addr_tokens[3]->u.access_kind
				== ACCESS_INDEXED_ARRAY)))
		      {
			ವೃಕ್ಷ rt = addr_tokens[1]->ಅಭಿವ್ಯಕ್ತಿ;

			gcc_assert (DECL_P (rt));

			ಯದಿ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
			    && OMP_CLAUSE_MAP_IMPLICIT (c)
			    && (bitmap_bit_p (&map_head, DECL_UID (rt))
				|| bitmap_bit_p (&map_field_head, DECL_UID (rt))
				|| bitmap_bit_p (&map_firstprivate_head,
						 DECL_UID (rt))))
			  {
			    remove = ಸತ್ಯ;
			    ಭಙ್ಗ;
			  }
			ಯದಿ (bitmap_bit_p (&map_field_head, DECL_UID (rt)))
			  ಭಙ್ಗ;
			ಯದಿ (bitmap_bit_p (&map_head, DECL_UID (rt)))
			  {
			    ಯದಿ (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP)
			      error_at (OMP_CLAUSE_LOCATION (c),
					"%qD appears more than once in motion "
					"clauses", rt);
			    ಅನ್ಯಥಾ ಯದಿ (openacc)
			      error_at (OMP_CLAUSE_LOCATION (c),
					"%qD appears more than once in data "
					"clauses", rt);
			    ಅನ್ಯಥಾ
			      error_at (OMP_CLAUSE_LOCATION (c),
					"%qD appears more than once in map "
					"clauses", rt);
			    remove = ಸತ್ಯ;
			  }
			ಅನ್ಯಥಾ
			  {
			    bitmap_set_bit (&map_head, DECL_UID (rt));
			    bitmap_set_bit (&map_field_head, DECL_UID (rt));
			  }
		      }
		  }
		ಯದಿ (c_oacc_check_attachments (c))
		  remove = ಸತ್ಯ;
		ಯದಿ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		    && (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_ATTACH
			|| OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_DETACH)
		    && !OMP_CLAUSE_SIZE (c))
		  /* In this case, we have a single array element which is a
		     pointer, and we already set OMP_CLAUSE_SIZE in
		     handle_omp_array_sections above.  For attach/detach
		     clauses, reset the OMP_CLAUSE_SIZE (representing a bias)
		     to zero here.  */
		  OMP_CLAUSE_SIZE (c) = size_zero_ಗಂಟು;
		ಭಙ್ಗ;
	      }
	    ಅನ್ಯಥಾ ಯದಿ (!omp_parse_ಅಭಿವ್ಯಕ್ತಿ (addr_tokens, t))
	      {
		sorry_at (OMP_CLAUSE_LOCATION (c),
			  "unsupported map expression %qE",
			  OMP_CLAUSE_DECL (c));
		remove = ಸತ್ಯ;
		ಭಙ್ಗ;
	      }
	    ಯದಿ (t == error_mark_ಗಂಟು)
	      {
		remove = ಸತ್ಯ;
		ಭಙ್ಗ;
	      }

	    ವೃಕ್ಷ attr;
	    ಯದಿ (DECL_P (t)
		&& OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		&& (attr = lookup_attribute ("omp declare target",
					     DECL_ATTRIBUTES (t)))
		&& ಮೌಲ್ಯ_member (get_identifier ("local"),
				 ವೃಕ್ಷ_ಮೌಲ್ಯ (attr)))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "device-local variable %qD cannot appear "
			  "in map clause", t);
		remove = ಸತ್ಯ;
		ಭಙ್ಗ;
	      }

	    /* OpenACC attach / detach clauses must be pointers.  */
	    ಯದಿ (c_oacc_check_attachments (c))
	      {
		remove = ಸತ್ಯ;
		ಭಙ್ಗ;
	      }
	    ಯದಿ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		&& (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_ATTACH
		    || OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_DETACH)
		&& !OMP_CLAUSE_SIZE (c))
	      /* For attach/detach clauses, set OMP_CLAUSE_SIZE (representing a
		 bias) to zero here, so it is not set erroneously to the pointer
		 size later on in gimplify.cc.  */
	      OMP_CLAUSE_SIZE (c) = size_zero_ಗಂಟು;

	    c_omp_address_inspector ai (OMP_CLAUSE_LOCATION (c), t);

	    ಯದಿ (!ai.check_clause (c))
	      {
		remove = ಸತ್ಯ;
		ಭಙ್ಗ;
	      }

	    ಯದಿ (!ai.map_supported_p ())
	      {
		sorry_at (OMP_CLAUSE_LOCATION (c),
			  "unsupported map expression %qE",
			  OMP_CLAUSE_DECL (c));
		remove = ಸತ್ಯ;
		ಭಙ್ಗ;
	      }

	    gcc_assert ((addr_tokens[0]->type == ARRAY_BASE
			 || addr_tokens[0]->type == STRUCTURE_BASE)
			&& addr_tokens[1]->type == ACCESS_METHOD);

	    t = addr_tokens[1]->ಅಭಿವ್ಯಕ್ತಿ;

	    ಯದಿ (addr_tokens[0]->u.structure_base_kind != BASE_DECL)
	      ಗಚ್ಛ skip_decl_checks;

	    /* For OpenMP, we can access a struct "t" and "t.d" on the same
	       mapping.  OpenACC allows multiple fields of the same structure
	       to be written.  */
	    ಯದಿ (addr_tokens[0]->type == STRUCTURE_BASE
		&& (bitmap_bit_p (&map_field_head, DECL_UID (t))
		    || (!openacc && bitmap_bit_p (&map_head, DECL_UID (t)))))
	      ಗಚ್ಛ skip_decl_checks;

	    ಯದಿ (!VAR_P (t) && ವೃಕ್ಷ_CODE (t) != PARM_DECL)
	      {
		ಯದಿ (ort != C_ORT_ACC && ಅಭಿವ್ಯಕ್ತಿ_P (t))
		  ಭಙ್ಗ;

		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is not a variable in %qs clause", t,
			  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		remove = ಸತ್ಯ;
	      }
	    ಅನ್ಯಥಾ ಯದಿ (VAR_P (t) && DECL_THREAD_LOCAL_P (t))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD is threadprivate variable in %qs clause", t,
			  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		remove = ಸತ್ಯ;
	      }
	    ಅನ್ಯಥಾ ಯದಿ ((OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP
		      || (OMP_CLAUSE_MAP_KIND (c)
			  != GOMP_MAP_FIRSTPRIVATE_POINTER))
		     && !c_mark_addressable (t))
	      remove = ಸತ್ಯ;
	    ಅನ್ಯಥಾ ಯದಿ (!(OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		       && (OMP_CLAUSE_MAP_KIND (c) == GOMP_MAP_POINTER
			   || (OMP_CLAUSE_MAP_KIND (c)
			       == GOMP_MAP_FIRSTPRIVATE_POINTER)
			   || (OMP_CLAUSE_MAP_KIND (c)
			       == GOMP_MAP_FORCE_DEVICEPTR)))
		     && t == OMP_CLAUSE_DECL (c)
		     && !omp_mappable_type (ವೃಕ್ಷ_TYPE (t)))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD does not have a mappable type in %qs clause", t,
			  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		remove = ಸತ್ಯ;
	      }
	    ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_TYPE (t) == error_mark_ಗಂಟು)
	      remove = ಸತ್ಯ;
	    ಅನ್ಯಥಾ ಯದಿ (TYPE_ATOMIC (strip_array_types (ವೃಕ್ಷ_TYPE (t))))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%<_Atomic%> %qE in %qs clause", t,
			  omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		remove = ಸತ್ಯ;
	      }
	    ಅನ್ಯಥಾ ಯದಿ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		     && OMP_CLAUSE_MAP_IMPLICIT (c)
		     && (bitmap_bit_p (&map_head, DECL_UID (t))
			 || bitmap_bit_p (&map_field_head, DECL_UID (t))
			 || bitmap_bit_p (&map_firstprivate_head,
					  DECL_UID (t))))
	      remove = ಸತ್ಯ;
	    ಅನ್ಯಥಾ ಯದಿ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP
		     && (OMP_CLAUSE_MAP_KIND (c)
			 == GOMP_MAP_FIRSTPRIVATE_POINTER))
	      {
		ಯದಿ (bitmap_bit_p (&generic_head, DECL_UID (t))
		    || bitmap_bit_p (&firstprivate_head, DECL_UID (t))
		    || bitmap_bit_p (&map_firstprivate_head, DECL_UID (t)))
		  {
		    error_at (OMP_CLAUSE_LOCATION (c),
			      "%qD appears more than once in data clauses", t);
		    remove = ಸತ್ಯ;
		  }
		ಅನ್ಯಥಾ ಯದಿ (bitmap_bit_p (&map_head, DECL_UID (t))
			 && !bitmap_bit_p (&map_field_head, DECL_UID (t))
			 && openacc)
		  {
		    error_at (OMP_CLAUSE_LOCATION (c),
			      "%qD appears more than once in data clauses", t);
		    remove = ಸತ್ಯ;
		  }
		ಅನ್ಯಥಾ
		  bitmap_set_bit (&map_firstprivate_head, DECL_UID (t));
	      }
	    ಅನ್ಯಥಾ ಯದಿ (bitmap_bit_p (&map_head, DECL_UID (t))
		     && !bitmap_bit_p (&map_field_head, DECL_UID (t))
		     && ort != C_ORT_OMP
		     && ort != C_ORT_OMP_TARGET
		     && ort != C_ORT_OMP_EXIT_DATA)
	      {
		ಯದಿ (OMP_CLAUSE_CODE (c) != OMP_CLAUSE_MAP)
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in motion clauses", t);
		ಅನ್ಯಥಾ ಯದಿ (openacc)
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in data clauses", t);
		ಅನ್ಯಥಾ
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in map clauses", t);
		remove = ಸತ್ಯ;
	      }
	    ಅನ್ಯಥಾ ಯದಿ (openacc && bitmap_bit_p (&generic_head, DECL_UID (t)))
	      {
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD appears more than once in data clauses", t);
		remove = ಸತ್ಯ;
	      }
	    ಅನ್ಯಥಾ ಯದಿ (bitmap_bit_p (&firstprivate_head, DECL_UID (t))
		     || bitmap_bit_p (&is_on_device_head, DECL_UID (t)))
	      {
		ಯದಿ (openacc)
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears more than once in data clauses", t);
		ಅನ್ಯಥಾ
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qD appears both in data and map clauses", t);
		remove = ಸತ್ಯ;
	      }
	    ಅನ್ಯಥಾ ಯದಿ (!omp_access_chain_p (addr_tokens, 1))
	      {
		bitmap_set_bit (&map_head, DECL_UID (t));
		ಯದಿ (t != OMP_CLAUSE_DECL (c)
		    && ವೃಕ್ಷ_CODE (OMP_CLAUSE_DECL (c)) == COMPONENT_REF)
		  bitmap_set_bit (&map_field_head, DECL_UID (t));
	      }

	  skip_decl_checks:
	    /* If we call omp_expand_map_clause in handle_omp_array_sections,
	       the containing loop (here) iterates through the new nodes
	       created by that expansion.  Avoid expanding those again (just
	       by checking the node type).  */
	    ಯದಿ (!remove
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
		ವೃಕ್ಷ nc = ai.expand_map_clause (c, OMP_CLAUSE_DECL (c),
						addr_tokens, ort);
		ಯದಿ (nc != error_mark_ಗಂಟು)
		  c = nc;
	      }
	  }
	  ಭಙ್ಗ;

	ಪಕ್ಷ OMP_CLAUSE_ENTER:
	ಪಕ್ಷ OMP_CLAUSE_LINK:
	ಪಕ್ಷ OMP_CLAUSE_LOCAL:
	  t = OMP_CLAUSE_DECL (c);
	  ಧ್ರುವ ವರ್ಣ *cname;
	  cname = omp_clause_code_name[OMP_CLAUSE_CODE (c)];
	  ಯದಿ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ENTER
	      && OMP_CLAUSE_ENTER_TO (c))
	    cname = "to";
	  ಯದಿ (ವೃಕ್ಷ_CODE (t) == FUNCTION_DECL
	      && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ENTER)
	    ;
	  ಅನ್ಯಥಾ ಯದಿ (!VAR_P (t))
	    {
	      ಯದಿ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ENTER)
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is neither a variable nor a function name in "
			  "clause %qs", t, cname);
	      ಅನ್ಯಥಾ
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is not a variable in clause %qs", t, cname);
	      remove = ಸತ್ಯ;
	    }
	  ಅನ್ಯಥಾ ಯದಿ (DECL_THREAD_LOCAL_P (t))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD is threadprivate variable in %qs clause", t,
			cname);
	      remove = ಸತ್ಯ;
	    }
	  ಅನ್ಯಥಾ ಯದಿ (!omp_mappable_type (ವೃಕ್ಷ_TYPE (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD does not have a mappable type in %qs clause", t,
			cname);
	      remove = ಸತ್ಯ;
	    }
	  ಯದಿ (remove)
	    ಭಙ್ಗ;
	  ಯದಿ (bitmap_bit_p (&generic_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE appears more than once on the same "
			"%<declare target%> directive", t);
	      remove = ಸತ್ಯ;
	    }
	  ಅನ್ಯಥಾ
	    bitmap_set_bit (&generic_head, DECL_UID (t));
	  ಭಙ್ಗ;

	ಪಕ್ಷ OMP_CLAUSE_UNIFORM:
	  t = OMP_CLAUSE_DECL (c);
	  ಯದಿ (ವೃಕ್ಷ_CODE (t) != PARM_DECL)
	    {
	      ಯದಿ (DECL_P (t))
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qD is not an argument in %<uniform%> clause", t);
	      ಅನ್ಯಥಾ
		error_at (OMP_CLAUSE_LOCATION (c),
			  "%qE is not an argument in %<uniform%> clause", t);
	      remove = ಸತ್ಯ;
	      ಭಙ್ಗ;
	    }
	  /* map_head bitmap is used as uniform_head if declare_simd.  */
	  bitmap_set_bit (&map_head, DECL_UID (t));
	  ಗಚ್ಛ check_dup_generic;

	ಪಕ್ಷ OMP_CLAUSE_IS_DEVICE_PTR:
	ಪಕ್ಷ OMP_CLAUSE_USE_DEVICE_PTR:
	  t = OMP_CLAUSE_DECL (c);
	  ಯದಿ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_IS_DEVICE_PTR)
	    bitmap_set_bit (&is_on_device_head, DECL_UID (t));
	  ಯದಿ (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (t)) != POINTER_TYPE)
	    {
	      ಯದಿ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_USE_DEVICE_PTR
		  && !openacc)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qs variable is not a pointer",
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  remove = ಸತ್ಯ;
		}
	      ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (ವೃಕ್ಷ_TYPE (t)) != ARRAY_TYPE)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qs variable is neither a pointer nor an array",
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  remove = ಸತ್ಯ;
		}
	    }
	  ಗಚ್ಛ check_dup_generic;

	ಪಕ್ಷ OMP_CLAUSE_HAS_DEVICE_ADDR:
	  t = OMP_CLAUSE_DECL (c);
	  ಯದಿ (ವೃಕ್ಷ_CODE (t) == OMP_ARRAY_SECTION)
	    {
	      ಯದಿ (handle_omp_array_sections (c, ort))
		remove = ಸತ್ಯ;
	      ಅನ್ಯಥಾ
		{
		  t = OMP_CLAUSE_DECL (c);
		  ಯಾವತ್ (ವೃಕ್ಷ_CODE (t) == ARRAY_REF)
		    t = ವೃಕ್ಷ_OPERAND (t, 0);
		}
	    }
	  bitmap_set_bit (&is_on_device_head, DECL_UID (t));
	  ಯದಿ (VAR_P (t) || ವೃಕ್ಷ_CODE (t) == PARM_DECL)
	    c_mark_addressable (t);
	  ಗಚ್ಛ check_dup_generic_t;

	ಪಕ್ಷ OMP_CLAUSE_USE_DEVICE_ADDR:
	  t = OMP_CLAUSE_DECL (c);
	  ಯದಿ (VAR_P (t) || ವೃಕ್ಷ_CODE (t) == PARM_DECL)
	    c_mark_addressable (t);
	  ಗಚ್ಛ check_dup_generic;

	ಪಕ್ಷ OMP_CLAUSE_NOWAIT:
	  ಯದಿ (copyprivate_seen)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<nowait%> clause must not be used together "
			"with %<copyprivate%> clause");
	      remove = ಸತ್ಯ;
	      ಭಙ್ಗ;
	    }
	  nowait_clause = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ಅನುವರ್ತ;

	ಪಕ್ಷ OMP_CLAUSE_ORDER:
	  ಯದಿ (ordered_clause)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<order%> clause must not be used together "
			"with %<ordered%> clause");
	      remove = ಸತ್ಯ;
	      ಭಙ್ಗ;
	    }
	  ಅನ್ಯಥಾ ಯದಿ (order_clause)
	    {
	      /* Silently remove duplicates.  */
	      remove = ಸತ್ಯ;
	      ಭಙ್ಗ;
	    }
	  order_clause = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ಅನುವರ್ತ;

	ಪಕ್ಷ OMP_CLAUSE_DETACH:
	  t = OMP_CLAUSE_DECL (c);
	  ಯದಿ (detach_seen)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"too many %qs clauses on a task construct",
			"detach");
	      remove = ಸತ್ಯ;
	      ಭಙ್ಗ;
	    }
	  detach_seen = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  c_mark_addressable (t);
	  ಅನುವರ್ತ;

	ಪಕ್ಷ OMP_CLAUSE_IF:
	ಪಕ್ಷ OMP_CLAUSE_SELF:
	ಪಕ್ಷ OMP_CLAUSE_ಅಂಕೆ_THREADS:
	ಪಕ್ಷ OMP_CLAUSE_ಅಂಕೆ_TEAMS:
	ಪಕ್ಷ OMP_CLAUSE_THREAD_LIMIT:
	ಪಕ್ಷ OMP_CLAUSE_DEFAULT:
	ಪಕ್ಷ OMP_CLAUSE_UNTIED:
	ಪಕ್ಷ OMP_CLAUSE_COLLAPSE:
	ಪಕ್ಷ OMP_CLAUSE_FINAL:
	ಪಕ್ಷ OMP_CLAUSE_DEVICE:
	ಪಕ್ಷ OMP_CLAUSE_DIST_SCHEDULE:
	ಪಕ್ಷ OMP_CLAUSE_DYN_GROUPPRIVATE:
	ಪಕ್ಷ OMP_CLAUSE_PARALLEL:
	ಪಕ್ಷ OMP_CLAUSE_FOR:
	ಪಕ್ಷ OMP_CLAUSE_SECTIONS:
	ಪಕ್ಷ OMP_CLAUSE_TASKGROUP:
	ಪಕ್ಷ OMP_CLAUSE_PROC_BIND:
	ಪಕ್ಷ OMP_CLAUSE_DEVICE_TYPE:
	ಪಕ್ಷ OMP_CLAUSE_PRIORITY:
	ಪಕ್ಷ OMP_CLAUSE_THREADS:
	ಪಕ್ಷ OMP_CLAUSE_SIMD:
	ಪಕ್ಷ OMP_CLAUSE_HINT:
	ಪಕ್ಷ OMP_CLAUSE_FILTER:
	ಪಕ್ಷ OMP_CLAUSE_DEFAULTMAP:
	ಪಕ್ಷ OMP_CLAUSE_BIND:
	ಪಕ್ಷ OMP_CLAUSE_ಅಂಕೆ_GANGS:
	ಪಕ್ಷ OMP_CLAUSE_ಅಂಕೆ_WORKERS:
	ಪಕ್ಷ OMP_CLAUSE_VECTOR_LENGTH:
	ಪಕ್ಷ OMP_CLAUSE_ASYNC:
	ಪಕ್ಷ OMP_CLAUSE_WAIT:
	ಪಕ್ಷ OMP_CLAUSE_AUTO:
	ಪಕ್ಷ OMP_CLAUSE_INDEPENDENT:
	ಪಕ್ಷ OMP_CLAUSE_SEQ:
	ಪಕ್ಷ OMP_CLAUSE_GANG:
	ಪಕ್ಷ OMP_CLAUSE_WORKER:
	ಪಕ್ಷ OMP_CLAUSE_VECTOR:
	ಪಕ್ಷ OMP_CLAUSE_TILE:
	ಪಕ್ಷ OMP_CLAUSE_IF_PRESENT:
	ಪಕ್ಷ OMP_CLAUSE_FINALIZE:
	ಪಕ್ಷ OMP_CLAUSE_NOHOST:
	ಪಕ್ಷ OMP_CLAUSE_INDIRECT:
	ಪಕ್ಷ OMP_CLAUSE_NOVARIANTS:
	ಪಕ್ಷ OMP_CLAUSE_NOCONTEXT:
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ಅನುವರ್ತ;

	ಪಕ್ಷ OMP_CLAUSE_GRAINSIZE:
	  grainsize_seen = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ಅನುವರ್ತ;

	ಪಕ್ಷ OMP_CLAUSE_ಅಂಕೆ_TASKS:
	  ಅಂಕೆ_tasks_seen = ಸತ್ಯ;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ಅನುವರ್ತ;

	ಪಕ್ಷ OMP_CLAUSE_MERGEABLE:
	  mergeable_seen = ಸತ್ಯ;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ಅನುವರ್ತ;

	ಪಕ್ಷ OMP_CLAUSE_NOGROUP:
	  nogroup_seen = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ಅನುವರ್ತ;

	ಪಕ್ಷ OMP_CLAUSE_SCHEDULE:
	  schedule_clause = c;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ಅನುವರ್ತ;

	ಪಕ್ಷ OMP_CLAUSE_ORDERED:
	  ordered_clause = c;
	  ಯದಿ (order_clause)
	    {
	      error_at (OMP_CLAUSE_LOCATION (*order_clause),
			"%<order%> clause must not be used together "
			"with %<ordered%> clause");
	      *order_clause = OMP_CLAUSE_CHAIN (*order_clause);
	      order_clause = ರಿಕ್ತ;
	    }
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ಅನುವರ್ತ;

	ಪಕ್ಷ OMP_CLAUSE_SAFELEN:
	  safelen = c;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ಅನುವರ್ತ;
	ಪಕ್ಷ OMP_CLAUSE_SIMDLEN:
	  simdlen = c;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ಅನುವರ್ತ;

	ಪಕ್ಷ OMP_CLAUSE_FULL:
	  full_seen = pc;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ಅನುವರ್ತ;

	ಪಕ್ಷ OMP_CLAUSE_PARTIAL:
	  partial_seen = ಸತ್ಯ;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ಅನುವರ್ತ;

	ಪಕ್ಷ OMP_CLAUSE_SIZES:
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ಅನುವರ್ತ;

	ಪಕ್ಷ OMP_CLAUSE_INBRANCH:
	ಪಕ್ಷ OMP_CLAUSE_NOTINBRANCH:
	  ಯದಿ (branch_seen)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%<inbranch%> clause is incompatible with "
			"%<notinbranch%>");
	      remove = ಸತ್ಯ;
	      ಭಙ್ಗ;
	    }
	  branch_seen = ಸತ್ಯ;
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ಅನುವರ್ತ;

	ಪಕ್ಷ OMP_CLAUSE_INCLUSIVE:
	ಪಕ್ಷ OMP_CLAUSE_EXCLUSIVE:
	  need_complete = ಸತ್ಯ;
	  need_implicitly_determined = ಸತ್ಯ;
	  t = OMP_CLAUSE_DECL (c);
	  ಯದಿ (!VAR_P (t) && ವೃಕ್ಷ_CODE (t) != PARM_DECL)
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qE is not a variable in clause %qs", t,
			omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
	      remove = ಸತ್ಯ;
	    }
	  ಭಙ್ಗ;

	ಪಕ್ಷ OMP_CLAUSE_INIT:
	  init_seen = ಸತ್ಯ;
	  ಯದಿ (!OMP_CLAUSE_INIT_TARGETSYNC (c))
	    init_no_targetsync_clause = c;
	  /* FALLTHRU */
	ಪಕ್ಷ OMP_CLAUSE_DESTROY:
	ಪಕ್ಷ OMP_CLAUSE_USE:
	  init_use_destroy_seen = ಸತ್ಯ;
	  t = OMP_CLAUSE_DECL (c);
	  ಯದಿ (bitmap_bit_p (&generic_head, DECL_UID (t)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD appears more than once in action clauses", t);
	      remove = ಸತ್ಯ;
	      ಭಙ್ಗ;
	    }
	  bitmap_set_bit (&generic_head, DECL_UID (t));
	  /* FALLTHRU */
	ಪಕ್ಷ OMP_CLAUSE_INTEROP:
	  ಯದಿ (/* ort == C_ORT_OMP_INTEROP [uncomment for depobj init]  */
		   !c_omp_interop_t_p (ವೃಕ್ಷ_TYPE (OMP_CLAUSE_DECL (c))))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
			"%qD must be of %<omp_interop_t%>",
			OMP_CLAUSE_DECL (c));
	      remove = ಸತ್ಯ;
	    }
	  ಅನ್ಯಥಾ ಯದಿ ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_INIT
		    || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_DESTROY)
		   && ವೃಕ್ಷ_READONLY (OMP_CLAUSE_DECL (c)))
	    {
	      error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD shall not be const", OMP_CLAUSE_DECL (c));
	      remove = ಸತ್ಯ;
	    }
	  pc = &OMP_CLAUSE_CHAIN (c);
	  ಭಙ್ಗ;
	ಸ್ವಭಾವ:
	  gcc_unreachable ();
	}

      ಯದಿ (!remove)
	{
	  t = OMP_CLAUSE_DECL (c);

	  ಯದಿ (need_complete)
	    {
	      t = require_complete_type (OMP_CLAUSE_LOCATION (c), t);
	      ಯದಿ (t == error_mark_ಗಂಟು)
		remove = ಸತ್ಯ;
	    }

	  ಯದಿ (need_implicitly_determined)
	    {
	      ಧ್ರುವ ವರ್ಣ *share_name = ರಿಕ್ತ;

	      ಯದಿ (VAR_P (t) && DECL_THREAD_LOCAL_P (t))
		share_name = "threadprivate";
	      ಅನ್ಯಥಾ ವಿಕಲ್ಪ (c_omp_predetermined_sharing (t))
		{
		ಪಕ್ಷ OMP_CLAUSE_DEFAULT_UNSPECIFIED:
		  ಭಙ್ಗ;
		ಪಕ್ಷ OMP_CLAUSE_DEFAULT_SHARED:
		  ಯದಿ ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_SHARED
		       || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_FIRSTPRIVATE)
		      && c_omp_predefined_variable (t))
		    /* The __func__ variable and similar function-local
		       predefined variables may be listed in a shared or
		       firstprivate clause.  */
		    ಭಙ್ಗ;
		  share_name = "shared";
		  ಭಙ್ಗ;
		ಪಕ್ಷ OMP_CLAUSE_DEFAULT_PRIVATE:
		  share_name = "private";
		  ಭಙ್ಗ;
		ಸ್ವಭಾವ:
		  gcc_unreachable ();
		}
	      ಯದಿ (share_name)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%qE is predetermined %qs for %qs",
			    t, share_name,
			    omp_clause_code_name[OMP_CLAUSE_CODE (c)]);
		  remove = ಸತ್ಯ;
		}
	      ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_READONLY (t)
		       && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_SHARED
		       && OMP_CLAUSE_CODE (c) != OMP_CLAUSE_FIRSTPRIVATE)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "%<const%> qualified %qE may appear only in "
			    "%<shared%> or %<firstprivate%> clauses", t);
		  remove = ಸತ್ಯ;
		}
	    }
	}

      ಯದಿ (remove)
	{
	  ಯದಿ (grp_start_p)
	    {
	      /* If we found a clause to remove, we want to remove the whole
		 expanded group, otherwise gimplify
		 (omp_resolve_clause_dependencies) can get confused.  */
	      *grp_start_p = grp_sentinel;
	      pc = grp_start_p;
	      grp_start_p = ರಿಕ್ತ;
	    }
	  ಅನ್ಯಥಾ
	    *pc = OMP_CLAUSE_CHAIN (c);
	}
      ಅನ್ಯಥಾ
	pc = &OMP_CLAUSE_CHAIN (c);
    }

  ಯದಿ (grp_start_p
      && OMP_CLAUSE_HAS_ITERATORS (*grp_start_p))
    ಪ್ರತಿ (ವೃಕ್ಷ gc = *grp_start_p; gc; gc = OMP_CLAUSE_CHAIN (gc))
      OMP_CLAUSE_ITERATORS (gc) = OMP_CLAUSE_ITERATORS (*grp_start_p);

  ಯದಿ (simdlen
      && safelen
      && ವೃಕ್ಷ_int_cst_lt (OMP_CLAUSE_SAFELEN_ಅಭಿವ್ಯಕ್ತಿ (safelen),
			  OMP_CLAUSE_SIMDLEN_ಅಭಿವ್ಯಕ್ತಿ (simdlen)))
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
      OMP_CLAUSE_SIMDLEN_ಅಭಿವ್ಯಕ್ತಿ (simdlen)
	= OMP_CLAUSE_SAFELEN_ಅಭಿವ್ಯಕ್ತಿ (safelen);
    }

  ಯದಿ (ordered_clause
      && schedule_clause
      && (OMP_CLAUSE_SCHEDULE_KIND (schedule_clause)
	  & OMP_CLAUSE_SCHEDULE_NONMONOTONIC))
    {
      error_at (OMP_CLAUSE_LOCATION (schedule_clause),
		"%<nonmonotonic%> schedule modifier specified together "
		"with %<ordered%> clause");
      OMP_CLAUSE_SCHEDULE_KIND (schedule_clause)
	= (ಗಣನಾ omp_clause_schedule_kind)
	  (OMP_CLAUSE_SCHEDULE_KIND (schedule_clause)
	   & ~OMP_CLAUSE_SCHEDULE_NONMONOTONIC);
    }

  ಯದಿ (reduction_seen < 0 && ordered_clause)
    {
      error_at (OMP_CLAUSE_LOCATION (ordered_clause),
		"%qs clause specified together with %<inscan%> "
		"%<reduction%> clause", "ordered");
      reduction_seen = -2;
    }

  ಯದಿ (reduction_seen < 0 && schedule_clause)
    {
      error_at (OMP_CLAUSE_LOCATION (schedule_clause),
		"%qs clause specified together with %<inscan%> "
		"%<reduction%> clause", "schedule");
      reduction_seen = -2;
    }

  ಯದಿ (linear_variable_step_check
      || reduction_seen == -2
      || allocate_seen
      || target_in_reduction_seen)
    ಪ್ರತಿ (pc = &clauses, c = clauses; c ; c = *pc)
      {
	ತಾರ್ಕಿಕ remove = ಅಸತ್ಯ;
	ಯದಿ (allocate_seen)
	  ವಿಕಲ್ಪ (OMP_CLAUSE_CODE (c))
	    {
	    ಪಕ್ಷ OMP_CLAUSE_REDUCTION:
	    ಪಕ್ಷ OMP_CLAUSE_IN_REDUCTION:
	    ಪಕ್ಷ OMP_CLAUSE_TASK_REDUCTION:
	      ಯದಿ (ವೃಕ್ಷ_CODE (OMP_CLAUSE_DECL (c)) == MEM_REF)
		{
		  t = ವೃಕ್ಷ_OPERAND (OMP_CLAUSE_DECL (c), 0);
		  ಯದಿ (ವೃಕ್ಷ_CODE (t) == POINTER_PLUS_ಅಭಿವ್ಯಕ್ತಿ)
		    t = ವೃಕ್ಷ_OPERAND (t, 0);
		  ಯದಿ (ವೃಕ್ಷ_CODE (t) == ADDR_ಅಭಿವ್ಯಕ್ತಿ
		      || INDIRECT_REF_P (t))
		    t = ವೃಕ್ಷ_OPERAND (t, 0);
		  ಯದಿ (DECL_P (t))
		    bitmap_clear_bit (&aligned_head, DECL_UID (t));
		  ಭಙ್ಗ;
		}
	      /* FALLTHRU */
	    ಪಕ್ಷ OMP_CLAUSE_PRIVATE:
	    ಪಕ್ಷ OMP_CLAUSE_FIRSTPRIVATE:
	    ಪಕ್ಷ OMP_CLAUSE_LASTPRIVATE:
	    ಪಕ್ಷ OMP_CLAUSE_LINEAR:
	      ಯದಿ (DECL_P (OMP_CLAUSE_DECL (c)))
		bitmap_clear_bit (&aligned_head,
				  DECL_UID (OMP_CLAUSE_DECL (c)));
	      ಭಙ್ಗ;
	    ಸ್ವಭಾವ:
	      ಭಙ್ಗ;
	    }
	ಯದಿ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_LINEAR
	    && OMP_CLAUSE_LINEAR_VARIABLE_STRIDE (c)
	    && !bitmap_bit_p (&map_head,
			      DECL_UID (OMP_CLAUSE_LINEAR_STEP (c))))
	  {
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%<linear%> clause step is a parameter %qD not "
		      "specified in %<uniform%> clause",
		      OMP_CLAUSE_LINEAR_STEP (c));
	    remove = ಸತ್ಯ;
	  }
	ಅನ್ಯಥಾ ಯದಿ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_REDUCTION
		 && reduction_seen == -2)
	  OMP_CLAUSE_REDUCTION_INSCAN (c) = 0;
	ಯದಿ (target_in_reduction_seen
	    && OMP_CLAUSE_CODE (c) == OMP_CLAUSE_MAP)
	  {
	    ವೃಕ್ಷ t = OMP_CLAUSE_DECL (c);
	    ಯಾವತ್ (handled_component_p (t)
		   || INDIRECT_REF_P (t)
		   || ವೃಕ್ಷ_CODE (t) == ADDR_ಅಭಿವ್ಯಕ್ತಿ
		   || ವೃಕ್ಷ_CODE (t) == MEM_REF
		   || ವೃಕ್ಷ_CODE (t) == NON_LVALUE_ಅಭಿವ್ಯಕ್ತಿ)
	      t = ವೃಕ್ಷ_OPERAND (t, 0);
	    ಯದಿ (DECL_P (t)
		&& bitmap_bit_p (&oacc_reduction_head, DECL_UID (t)))
	      OMP_CLAUSE_MAP_IN_REDUCTION (c) = 1;
	  }

	ಯದಿ (remove)
	  *pc = OMP_CLAUSE_CHAIN (c);
	ಅನ್ಯಥಾ
	  pc = &OMP_CLAUSE_CHAIN (c);
      }

  ಯದಿ (allocate_seen)
    ಪ್ರತಿ (pc = &clauses, c = clauses; c ; c = *pc)
      {
	ತಾರ್ಕಿಕ remove = ಅಸತ್ಯ;
	ಯದಿ (OMP_CLAUSE_CODE (c) == OMP_CLAUSE_ALLOCATE
	    && !OMP_CLAUSE_ALLOCATE_COMBINED (c)
	    && bitmap_bit_p (&aligned_head, DECL_UID (OMP_CLAUSE_DECL (c))))
	  {
	    error_at (OMP_CLAUSE_LOCATION (c),
		      "%qD specified in %<allocate%> clause but not in "
		      "an explicit privatization clause", OMP_CLAUSE_DECL (c));
	    remove = ಸತ್ಯ;
	  }
	ಯದಿ (remove)
	  *pc = OMP_CLAUSE_CHAIN (c);
	ಅನ್ಯಥಾ
	  pc = &OMP_CLAUSE_CHAIN (c);
      }

  ಯದಿ (nogroup_seen && reduction_seen)
    {
      error_at (OMP_CLAUSE_LOCATION (*nogroup_seen),
		"%<nogroup%> clause must not be used together with "
		"%<reduction%> clause");
      *nogroup_seen = OMP_CLAUSE_CHAIN (*nogroup_seen);
    }

  ಯದಿ (grainsize_seen && ಅಂಕೆ_tasks_seen)
    {
      error_at (OMP_CLAUSE_LOCATION (*grainsize_seen),
		"%<grainsize%> clause must not be used together with "
		"%<num_tasks%> clause");
      *grainsize_seen = OMP_CLAUSE_CHAIN (*grainsize_seen);
    }

  ಯದಿ (full_seen && partial_seen)
    {
      error_at (OMP_CLAUSE_LOCATION (*full_seen),
		"%<full%> clause must not be used together with "
		"%<partial%> clause");
      *full_seen = OMP_CLAUSE_CHAIN (*full_seen);
    }

  ಯದಿ (detach_seen)
    {
      ಯದಿ (mergeable_seen)
	{
	  error_at (OMP_CLAUSE_LOCATION (*detach_seen),
		    "%<detach%> clause must not be used together with "
		    "%<mergeable%> clause");
	  *detach_seen = OMP_CLAUSE_CHAIN (*detach_seen);
	}
      ಅನ್ಯಥಾ
	{
	  ವೃಕ್ಷ detach_decl = OMP_CLAUSE_DECL (*detach_seen);

	  ಪ್ರತಿ (pc = &clauses, c = clauses; c ; c = *pc)
	    {
	      ತಾರ್ಕಿಕ remove = ಅಸತ್ಯ;
	      ಯದಿ ((OMP_CLAUSE_CODE (c) == OMP_CLAUSE_SHARED
		   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_PRIVATE
		   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_FIRSTPRIVATE
		   || OMP_CLAUSE_CODE (c) == OMP_CLAUSE_LASTPRIVATE)
		  && OMP_CLAUSE_DECL (c) == detach_decl)
		{
		  error_at (OMP_CLAUSE_LOCATION (c),
			    "the event handle of a %<detach%> clause "
			    "should not be in a data-sharing clause");
		  remove = ಸತ್ಯ;
		}
	      ಯದಿ (remove)
		*pc = OMP_CLAUSE_CHAIN (c);
	      ಅನ್ಯಥಾ
		pc = &OMP_CLAUSE_CHAIN (c);
	    }
	}
    }

  ಯದಿ (ort == C_ORT_OMP_INTEROP
      && depend_clause
      && (!init_use_destroy_seen
	  || (init_seen && init_no_targetsync_clause)))
    {
      error_at (OMP_CLAUSE_LOCATION (depend_clause),
		"%<depend%> clause requires action clauses with "
		"%<targetsync%> interop-type");
      ಯದಿ (init_no_targetsync_clause)
	inform (OMP_CLAUSE_LOCATION (init_no_targetsync_clause),
		"%<init%> clause lacks the %<targetsync%> modifier");
    }

  bitmap_obstack_release (ರಿಕ್ತ);
  ಪ್ರತ್ಯಾಗಮ clauses;
}

/* Do processing necessary to make CLAUSES well-formed, where CLAUSES result
   from implicit instantiation of user-defined mappers (in gimplify.cc).  */

ವೃಕ್ಷ
c_omp_finish_mapper_clauses (ವೃಕ್ಷ clauses)
{
  ಪ್ರತ್ಯಾಗಮ c_finish_omp_clauses (clauses, C_ORT_OMP);
}

/* Return code to initialize DST with a copy constructor from SRC.
   C doesn't have copy constructors nor assignment operators, only for
   _Atomic vars we need to perform __atomic_load from src into a temporary
   followed by __atomic_store of the temporary to dst.  */

ವೃಕ್ಷ
c_omp_clause_copy_ctor (ವೃಕ್ಷ clause, ವೃಕ್ಷ dst, ವೃಕ್ಷ src)
{
  ಯದಿ (!really_atomic_lvalue (dst) && !really_atomic_lvalue (src))
    ಪ್ರತ್ಯಾಗಮ build2 (MODIFY_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (dst), dst, src);

  location_t loc = OMP_CLAUSE_LOCATION (clause);
  ವೃಕ್ಷ type = ವೃಕ್ಷ_TYPE (dst);
  ವೃಕ್ಷ nonatomic_type = build_qualified_type (type, TYPE_UNQUALIFIED);
  ವೃಕ್ಷ tmp = create_tmp_var (nonatomic_type);
  ವೃಕ್ಷ tmp_addr = build_fold_addr_ಅಭಿವ್ಯಕ್ತಿ (tmp);
  ವೃಕ್ಷ_ADDRESSABLE (tmp) = 1;
  suppress_warning (tmp);
  ವೃಕ್ಷ src_addr = build_fold_addr_ಅಭಿವ್ಯಕ್ತಿ (src);
  ವೃಕ್ಷ dst_addr = build_fold_addr_ಅಭಿವ್ಯಕ್ತಿ (dst);
  ವೃಕ್ಷ seq_cst = build_int_cst (integer_type_ಗಂಟು, MEMMODEL_SEQ_CST);
  vec<ವೃಕ್ಷ, va_gc> *params;
  /* Expansion of a generic atomic load may require an addition
     element, so allocate enough to prevent a resize.  */
  vec_alloc (params, 4);

  /* Build __atomic_load (&src, &tmp, SEQ_CST);  */
  ವೃಕ್ಷ fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_LOAD);
  params->quick_ತಳ್ಳು (src_addr);
  params->quick_ತಳ್ಳು (tmp_addr);
  params->quick_ತಳ್ಳು (seq_cst);
  ವೃಕ್ಷ load = c_build_function_call_vec (loc, vNULL, fndecl, params, ರಿಕ್ತ);

  vec_alloc (params, 4);

  /* Build __atomic_store (&dst, &tmp, SEQ_CST);  */
  fndecl = builtin_decl_explicit (BUILT_IN_ATOMIC_STORE);
  params->quick_ತಳ್ಳು (dst_addr);
  params->quick_ತಳ್ಳು (tmp_addr);
  params->quick_ತಳ್ಳು (seq_cst);
  ವೃಕ್ಷ store = c_build_function_call_vec (loc, vNULL, fndecl, params, ರಿಕ್ತ);
  ಪ್ರತ್ಯಾಗಮ build2 (COMPOUND_ಅಭಿವ್ಯಕ್ತಿ, void_type_ಗಂಟು, load, store);
}

/* Create a transaction node.  */

ವೃಕ್ಷ
c_finish_transaction (location_t loc, ವೃಕ್ಷ block, ಪೂರ್ಣಾಙ್ಕ flags)
{
  ವೃಕ್ಷ stmt = build_stmt (loc, TRANSACTION_ಅಭಿವ್ಯಕ್ತಿ, block);
  ಯದಿ (flags & TM_STMT_ATTR_OUTER)
    TRANSACTION_ಅಭಿವ್ಯಕ್ತಿ_OUTER (stmt) = 1;
  ಯದಿ (flags & TM_STMT_ATTR_RELAXED)
    TRANSACTION_ಅಭಿವ್ಯಕ್ತಿ_RELAXED (stmt) = 1;
  ಪ್ರತ್ಯಾಗಮ add_stmt (stmt);
}

/* Make a variant type in the proper way for C/C++, propagating qualifiers
   down to the element type of an array.  If ORIG_QUAL_TYPE is not
   NULL, then it should be used as the qualified type
   ORIG_QUAL_INDIRECT levels down in array type derivation (to
   preserve information about the typedef name from which an array
   type was derived).  */

ವೃಕ್ಷ
c_build_qualified_type (ವೃಕ್ಷ type, ಪೂರ್ಣಾಙ್ಕ type_quals, ವೃಕ್ಷ orig_qual_type,
			size_t orig_qual_indirect)
{
  ಯದಿ (type == error_mark_ಗಂಟು)
    ಪ್ರತ್ಯಾಗಮ type;

  ಯದಿ (ವೃಕ್ಷ_CODE (type) == ARRAY_TYPE)
    {
      ವೃಕ್ಷ t;
      ವೃಕ್ಷ element_type = c_build_qualified_type (ವೃಕ್ಷ_TYPE (type),
						  type_quals, orig_qual_type,
						  orig_qual_indirect - 1);

      /* See if we already have an identically qualified type.  */
      ಯದಿ (orig_qual_type && orig_qual_indirect == 0)
	t = orig_qual_type;
      ಅನ್ಯಥಾ
	ಪ್ರತಿ (t = TYPE_MAIN_VARIANT (type); t; t = TYPE_NEXT_VARIANT (t))
	  {
	    ಯದಿ (TYPE_QUALS (strip_array_types (t)) == type_quals
		&& TYPE_NAME (t) == TYPE_NAME (type)
		&& TYPE_CONTEXT (t) == TYPE_CONTEXT (type)
		&& attribute_list_equal (TYPE_ATTRIBUTES (t),
					 TYPE_ATTRIBUTES (type)))
	      ಭಙ್ಗ;
	  }
      ಯದಿ (!t)
	{
          ವೃಕ್ಷ domain = TYPE_DOMAIN (type);

	  t = build_variant_type_copy (type);
	  ವೃಕ್ಷ_TYPE (t) = element_type;
	  TYPE_ADDR_SPACE (t) = TYPE_ADDR_SPACE (element_type);

          ಯದಿ (TYPE_STRUCTURAL_EQUALITY_P (element_type)
              || (domain && TYPE_STRUCTURAL_EQUALITY_P (domain)))
            SET_TYPE_STRUCTURAL_EQUALITY (t);
          ಅನ್ಯಥಾ ಯದಿ (TYPE_CANONICAL (element_type) != element_type
                   || (domain && TYPE_CANONICAL (domain) != domain))
            {
              ವೃಕ್ಷ unqualified_canon
		= c_build_array_type (TYPE_CANONICAL (element_type),
				      domain ? TYPE_CANONICAL (domain)
					     : NULL_ವೃಕ್ಷ);
              ಯದಿ (TYPE_REVERSE_STORAGE_ORDER (type))
                {
                  unqualified_canon
		    = build_distinct_type_copy (unqualified_canon);
                  TYPE_REVERSE_STORAGE_ORDER (unqualified_canon) = 1;
                }
              TYPE_CANONICAL (t)
		= c_build_qualified_type (unqualified_canon, type_quals);
            }
          ಅನ್ಯಥಾ
            TYPE_CANONICAL (t) = t;
	}
      ಪ್ರತ್ಯಾಗಮ t;
    }

  /* A restrict-qualified pointer type must be a pointer to object or
     incomplete type.  Note that the use of POINTER_TYPE_P also allows
     REFERENCE_TYPEs, which is appropriate for C++.  */
  ಯದಿ ((type_quals & TYPE_QUAL_RESTRICT)
      && (!POINTER_TYPE_P (type)
	  || !C_TYPE_OBJECT_OR_INCOMPLETE_P (ವೃಕ್ಷ_TYPE (type))))
    {
      error ("invalid use of %<restrict%>");
      type_quals &= ~TYPE_QUAL_RESTRICT;
    }

  ವೃಕ್ಷ var_type = (orig_qual_type && orig_qual_indirect == 0
		   ? orig_qual_type
		   : build_qualified_type (type, type_quals));

  gcc_checking_assert (C_TYPE_VARIABLE_SIZE (var_type)
		       == C_TYPE_VARIABLE_SIZE (type));
  gcc_checking_assert (c_type_variably_modified_p (var_type)
		       == c_type_variably_modified_p (type));

  /* A variant type does not inherit the list of incomplete vars from the
     type main variant.  */
  ಯದಿ ((RECORD_OR_UNION_TYPE_P (var_type)
       || ವೃಕ್ಷ_CODE (var_type) == ENUMERAL_TYPE)
      && TYPE_MAIN_VARIANT (var_type) != var_type)
    C_TYPE_INCOMPLETE_VARS (var_type) = 0;
  ಪ್ರತ್ಯಾಗಮ var_type;
}

/* Build a VA_ARG_EXPR for the C parser.  */

ವೃಕ್ಷ
c_build_va_arg (location_t loc1, ವೃಕ್ಷ ಅಭಿವ್ಯಕ್ತಿ, location_t loc2, ವೃಕ್ಷ type,
		ವೃಕ್ಷ type_ಅಭಿವ್ಯಕ್ತಿ)
{
  ಯದಿ (error_operand_p (type))
    ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
  /* VA_ARG_EXPR cannot be used for a scalar va_list with reverse storage
     order because it takes the address of the expression.  */
  ಅನ್ಯಥಾ ಯದಿ (handled_component_p (ಅಭಿವ್ಯಕ್ತಿ)
	   && reverse_storage_order_for_component_p (ಅಭಿವ್ಯಕ್ತಿ))
    {
      error_at (loc1, "cannot use %<va_arg%> with reverse storage order");
      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
    }
  ಅನ್ಯಥಾ ಯದಿ (!COMPLETE_TYPE_P (type))
    {
      error_at (loc2, "second argument to %<va_arg%> is of incomplete "
		"type %qT", type);
      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
    }
  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (type) == FUNCTION_TYPE)
    {
      error_at (loc2, "second argument to %<va_arg%> is a function type %qT",
		type);
      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
    }
  ಅನ್ಯಥಾ ಯದಿ (ವೃಕ್ಷ_CODE (type) == ARRAY_TYPE && C_TYPE_VARIABLE_SIZE (type)
	   && !flag_isoc99)
    {
      error_at (loc2, "second argument to %<va_arg%> is an array type %qT",
		type);
      ಪ್ರತ್ಯಾಗಮ error_mark_ಗಂಟು;
    }
  ಅನ್ಯಥಾ ಯದಿ (warn_cxx_compat && ವೃಕ್ಷ_CODE (type) == ENUMERAL_TYPE)
    warning_at (loc2, OPT_Wc___compat,
		"C++ requires promoted type, not enum type, in %<va_arg%>");

  ಯದಿ (flag_isoc99 && ವೃಕ್ಷ_CODE (type) == ARRAY_TYPE)
    {
      warning_at (loc2, 0, "second argument to %<va_arg%> is an array type %qT",
		  type);
      /* We create a trap but evaluate side effects first.  */
      ವೃಕ್ಷ trapfn = builtin_decl_explicit (BUILT_IN_TRAP);
      trapfn = build_call_ಅಭಿವ್ಯಕ್ತಿ_loc (loc2, trapfn, 0);
      ವೃಕ್ಷ e2 = build2 (COMPOUND_ಅಭಿವ್ಯಕ್ತಿ, void_type_ಗಂಟು, ಅಭಿವ್ಯಕ್ತಿ, trapfn);
      /* Return a compound literal of the right type.  */
      ವೃಕ್ಷ e1 = build_compound_literal (loc2, type, ರಿಕ್ತ, ಸತ್ಯ, 0, ರಿಕ್ತ);
      ಅಭಿವ್ಯಕ್ತಿ = build2 (COMPOUND_ಅಭಿವ್ಯಕ್ತಿ, type, e2, e1);
    }
  ಅನ್ಯಥಾ
    ಅಭಿವ್ಯಕ್ತಿ = build_va_arg (loc2, ಅಭಿವ್ಯಕ್ತಿ, type);

  ಯದಿ (type_ಅಭಿವ್ಯಕ್ತಿ)
    ಅಭಿವ್ಯಕ್ತಿ = build2 (COMPOUND_ಅಭಿವ್ಯಕ್ತಿ, ವೃಕ್ಷ_TYPE (ಅಭಿವ್ಯಕ್ತಿ), type_ಅಭಿವ್ಯಕ್ತಿ, ಅಭಿವ್ಯಕ್ತಿ);

  ಪ್ರತ್ಯಾಗಮ ಅಭಿವ್ಯಕ್ತಿ;
}

/* Return truthvalue of whether T1 is the same tree structure as T2.
   Return 1 if they are the same. Return false if they are different.  */

ತಾರ್ಕಿಕ
c_ವೃಕ್ಷ_equal (ವೃಕ್ಷ t1, ವೃಕ್ಷ t2)
{
  ಗಣನಾ ವೃಕ್ಷ_code code1, code2;

  ಯದಿ (t1 == t2)
    ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
  ಯದಿ (!t1 || !t2)
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

  ಪ್ರತಿ (code1 = ವೃಕ್ಷ_CODE (t1); code1 == NON_LVALUE_ಅಭಿವ್ಯಕ್ತಿ;
       code1 = ವೃಕ್ಷ_CODE (t1))
    t1 = ವೃಕ್ಷ_OPERAND (t1, 0);
  ಪ್ರತಿ (code2 = ವೃಕ್ಷ_CODE (t2); code2 == NON_LVALUE_ಅಭಿವ್ಯಕ್ತಿ;
       code2 = ವೃಕ್ಷ_CODE (t2))
    t2 = ವೃಕ್ಷ_OPERAND (t2, 0);

  /* They might have become equal now.  */
  ಯದಿ (t1 == t2)
    ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;

  ಯದಿ (code1 != code2)
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

  ಯದಿ (CONSTANT_CLASS_P (t1) && !comptypes (ವೃಕ್ಷ_TYPE (t1), ವೃಕ್ಷ_TYPE (t2)))
    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

  ವಿಕಲ್ಪ (code1)
    {
    ಪಕ್ಷ INTEGER_CST:
      ಪ್ರತ್ಯಾಗಮ wi::to_wide (t1) == wi::to_wide (t2);

    ಪಕ್ಷ REAL_CST:
      ಪ್ರತ್ಯಾಗಮ real_equal (&ವೃಕ್ಷ_REAL_CST (t1), &ವೃಕ್ಷ_REAL_CST (t2));

    ಪಕ್ಷ STRING_CST:
      ಪ್ರತ್ಯಾಗಮ ವೃಕ್ಷ_STRING_LENGTH (t1) == ವೃಕ್ಷ_STRING_LENGTH (t2)
	&& !memcmp (ವೃಕ್ಷ_STRING_POINTER (t1), ವೃಕ್ಷ_STRING_POINTER (t2),
		    ವೃಕ್ಷ_STRING_LENGTH (t1));

    ಪಕ್ಷ FIXED_CST:
      ಪ್ರತ್ಯಾಗಮ FIXED_ಮೌಲ್ಯಗಳು_IDENTICAL (ವೃಕ್ಷ_FIXED_CST (t1),
				     ವೃಕ್ಷ_FIXED_CST (t2));

    ಪಕ್ಷ COMPLEX_CST:
      ಪ್ರತ್ಯಾಗಮ c_ವೃಕ್ಷ_equal (ವೃಕ್ಷ_REALPART (t1), ವೃಕ್ಷ_REALPART (t2))
	     && c_ವೃಕ್ಷ_equal (ವೃಕ್ಷ_IMAGPART (t1), ವೃಕ್ಷ_IMAGPART (t2));

    ಪಕ್ಷ VECTOR_CST:
      ಪ್ರತ್ಯಾಗಮ operand_equal_p (t1, t2, OEP_ONLY_CONST);

    ಪಕ್ಷ CONSTRUCTOR:
      /* We need to do this when determining whether or not two
	 non-type pointer to member function template arguments
	 are the same.  */
      ಯದಿ (!comptypes (ವೃಕ್ಷ_TYPE (t1), ವೃಕ್ಷ_TYPE (t2))
	  || CONSTRUCTOR_NELTS (t1) != CONSTRUCTOR_NELTS (t2))
	ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
      {
	ವೃಕ್ಷ field, ಮೌಲ್ಯ;
	unsigned ಪೂರ್ಣಾಙ್ಕ i;
	FOR_EACH_CONSTRUCTOR_ELT (CONSTRUCTOR_ELTS (t1), i, field, ಮೌಲ್ಯ)
	  {
	    constructor_elt *elt2 = CONSTRUCTOR_ELT (t2, i);
	    ಯದಿ (!c_ವೃಕ್ಷ_equal (field, elt2->index)
		|| !c_ವೃಕ್ಷ_equal (ಮೌಲ್ಯ, elt2->ಮೌಲ್ಯ))
	      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	  }
      }
      ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;

    ಪಕ್ಷ ವೃಕ್ಷ_LIST:
      ಯದಿ (!c_ವೃಕ್ಷ_equal (ವೃಕ್ಷ_PURPOSE (t1), ವೃಕ್ಷ_PURPOSE (t2)))
	ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
      ಯದಿ (!c_ವೃಕ್ಷ_equal (ವೃಕ್ಷ_ಮೌಲ್ಯ (t1), ವೃಕ್ಷ_ಮೌಲ್ಯ (t2)))
	ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
      ಪ್ರತ್ಯಾಗಮ c_ವೃಕ್ಷ_equal (ವೃಕ್ಷ_CHAIN (t1), ವೃಕ್ಷ_CHAIN (t2));

    ಪಕ್ಷ SAVE_ಅಭಿವ್ಯಕ್ತಿ:
      ಪ್ರತ್ಯಾಗಮ c_ವೃಕ್ಷ_equal (ವೃಕ್ಷ_OPERAND (t1, 0), ವೃಕ್ಷ_OPERAND (t2, 0));

    ಪಕ್ಷ CALL_ಅಭಿವ್ಯಕ್ತಿ:
      {
	ವೃಕ್ಷ arg1, arg2;
	call_ಅಭಿವ್ಯಕ್ತಿ_arg_iterator iter1, iter2;
	ಯದಿ (!c_ವೃಕ್ಷ_equal (CALL_ಅಭಿವ್ಯಕ್ತಿ_FN (t1), CALL_ಅಭಿವ್ಯಕ್ತಿ_FN (t2)))
	  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	ಪ್ರತಿ (arg1 = first_call_ಅಭಿವ್ಯಕ್ತಿ_arg (t1, &iter1),
	       arg2 = first_call_ಅಭಿವ್ಯಕ್ತಿ_arg (t2, &iter2);
	     arg1 && arg2;
	     arg1 = next_call_ಅಭಿವ್ಯಕ್ತಿ_arg (&iter1),
	       arg2 = next_call_ಅಭಿವ್ಯಕ್ತಿ_arg (&iter2))
	  ಯದಿ (!c_ವೃಕ್ಷ_equal (arg1, arg2))
	    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	ಯದಿ (arg1 || arg2)
	  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
      }

    ಪಕ್ಷ TARGET_ಅಭಿವ್ಯಕ್ತಿ:
      {
	ವೃಕ್ಷ o1 = ವೃಕ್ಷ_OPERAND (t1, 0);
	ವೃಕ್ಷ o2 = ವೃಕ್ಷ_OPERAND (t2, 0);

	/* Special case: if either target is an unallocated VAR_DECL,
	   it means that it's going to be unified with whatever the
	   TARGET_EXPR is really supposed to initialize, so treat it
	   as being equivalent to anything.  */
	ಯದಿ (VAR_P (o1) && DECL_NAME (o1) == NULL_ವೃಕ್ಷ
	    && !DECL_RTL_SET_P (o1))
	  /*Nop*/;
	ಅನ್ಯಥಾ ಯದಿ (VAR_P (o2) && DECL_NAME (o2) == NULL_ವೃಕ್ಷ
		 && !DECL_RTL_SET_P (o2))
	  /*Nop*/;
	ಅನ್ಯಥಾ ಯದಿ (!c_ವೃಕ್ಷ_equal (o1, o2))
	  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

	ಪ್ರತ್ಯಾಗಮ c_ವೃಕ್ಷ_equal (ವೃಕ್ಷ_OPERAND (t1, 1), ವೃಕ್ಷ_OPERAND (t2, 1));
      }

    ಪಕ್ಷ COMPONENT_REF:
      ಯದಿ (ವೃಕ್ಷ_OPERAND (t1, 1) != ವೃಕ್ಷ_OPERAND (t2, 1))
	ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
      ಪ್ರತ್ಯಾಗಮ c_ವೃಕ್ಷ_equal (ವೃಕ್ಷ_OPERAND (t1, 0), ವೃಕ್ಷ_OPERAND (t2, 0));

    ಪಕ್ಷ PARM_DECL:
    ಪಕ್ಷ VAR_DECL:
    ಪಕ್ಷ CONST_DECL:
    ಪಕ್ಷ FIELD_DECL:
    ಪಕ್ಷ FUNCTION_DECL:
    ಪಕ್ಷ IDENTIFIER_ಗಂಟು:
    ಪಕ್ಷ SSA_NAME:
      ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

    ಪಕ್ಷ ವೃಕ್ಷ_VEC:
      {
	unsigned ix;
	ಯದಿ (ವೃಕ್ಷ_VEC_LENGTH (t1) != ವೃಕ್ಷ_VEC_LENGTH (t2))
	  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	ಪ್ರತಿ (ix = ವೃಕ್ಷ_VEC_LENGTH (t1); ix--;)
	  ಯದಿ (!c_ವೃಕ್ಷ_equal (ವೃಕ್ಷ_VEC_ELT (t1, ix),
			     ವೃಕ್ಷ_VEC_ELT (t2, ix)))
	    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
	ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
      }

    CASE_CONVERT:
      ಯದಿ (!comptypes (ವೃಕ್ಷ_TYPE (t1), ವೃಕ್ಷ_TYPE (t2)))
	ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;
      ಭಙ್ಗ;

    ಸ್ವಭಾವ:
      ಭಙ್ಗ;
    }

  ವಿಕಲ್ಪ (ವೃಕ್ಷ_CODE_CLASS (code1))
    {
    ಪಕ್ಷ tcc_unary:
    ಪಕ್ಷ tcc_ದ್ವಿಮಾನ:
    ಪಕ್ಷ tcc_comparison:
    ಪಕ್ಷ tcc_expression:
    ಪಕ್ಷ tcc_vl_exp:
    ಪಕ್ಷ tcc_reference:
    ಪಕ್ಷ tcc_statement:
      {
	ಪೂರ್ಣಾಙ್ಕ i, n = ವೃಕ್ಷ_OPERAND_LENGTH (t1);

	ವಿಕಲ್ಪ (code1)
	  {
	  ಪಕ್ಷ PREINCREMENT_ಅಭಿವ್ಯಕ್ತಿ:
	  ಪಕ್ಷ PREDECREMENT_ಅಭಿವ್ಯಕ್ತಿ:
	  ಪಕ್ಷ POSTINCREMENT_ಅಭಿವ್ಯಕ್ತಿ:
	  ಪಕ್ಷ POSTDECREMENT_ಅಭಿವ್ಯಕ್ತಿ:
	    n = 1;
	    ಭಙ್ಗ;
	  ಪಕ್ಷ ARRAY_REF:
	    n = 2;
	    ಭಙ್ಗ;
	  ಸ್ವಭಾವ:
	    ಭಙ್ಗ;
	  }

	ಯದಿ (ವೃಕ್ಷ_CODE_CLASS (code1) == tcc_vl_exp
	    && n != ವೃಕ್ಷ_OPERAND_LENGTH (t2))
	  ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

	ಪ್ರತಿ (i = 0; i < n; ++i)
	  ಯದಿ (!c_ವೃಕ್ಷ_equal (ವೃಕ್ಷ_OPERAND (t1, i), ವೃಕ್ಷ_OPERAND (t2, i)))
	    ಪ್ರತ್ಯಾಗಮ ಅಸತ್ಯ;

	ಪ್ರತ್ಯಾಗಮ ಸತ್ಯ;
      }

    ಪಕ್ಷ tcc_type:
      ಪ್ರತ್ಯಾಗಮ comptypes (t1, t2);
    ಸ್ವಭಾವ:
      gcc_unreachable ();
    }
}

/* Returns true when the function declaration FNDECL is implicit,
   introduced as a result of a call to an otherwise undeclared
   function, and false otherwise.  */

ತಾರ್ಕಿಕ
c_decl_implicit (const_ವೃಕ್ಷ fndecl)
{
  ಪ್ರತ್ಯಾಗಮ C_DECL_IMPLICIT (fndecl);
}
